#include <LuaParam.h>
#include <Clock.h>
#include <CompressedActionTree.h>
#include <MissionMgr.h>
#include <Weather.h>
#include <Timer.h>
#include <PlayerInfo.h>
#include <UserInputManager.h>
#include <ActionIntention.h>
#include <Ped.h>


int cmdClockSet(lua_State *lua)
{
  int hour = LuaParam::GetInt(lua, 0);
  int minute = LuaParam::GetInt(lua, 1);
  Clock::SetGameClock(hour, minute);
  return 0;
}

int cmdClockGet(lua_State *lua)
{
  LuaParam::PushInt(lua, Clock::ms_nGameClockHours);
  LuaParam::PushInt(lua, Clock::ms_nGameClockMinutes);
  return 2;
}

int cmdClockSetTickRate(lua_State *lua)
{
  float tickRate = LuaParam::GetFloat(lua, 0);
  float onMissionTickRate = tickRate;
  
  if (LuaParam::GetParamCount(lua) >= 2)
  {
    onMissionTickRate = LuaParam::GetFloat(lua, 1);
  }
  
  int milPerGameMinute = 60000.0 / tickRate;
  Clock::ms_nMillisecondsPerGameMinuteOffMission = milPerGameMinute;
  Clock::ms_nMillisecondsPerGameMinute = milPerGameMinute;
  Clock::ms_nMillisecondsPerGameMinuteOnMission = (60000.0 / onMissionTickRate);
  if (!Clock::ms_nMillisecondsPerGameMinuteOnMission)
  {
    Clock::ms_nMillisecondsPerGameMinuteOnMission = milPerGameMinute;
  }
  return 0;
}

int cmdClockSetEnableMission(lua_State *lua)
{
  const char *missionId = LuaParam::GetString(lua, 0);
  char actionTree[4];
  ActionTreeName::ActionTreeName(actionTree, missionId);
  Clock::ms_nEnableMissionIndex = CMissionMgr::FindMission(CMissionMgr, actionTree);
  return 0;
}

int cmdWeatherSet(lua_State *lua)
{
  bool rainWithThunder = 0;
  if (lua_gettop(lua) == 2)
  {
    bool rainWithThunder = LuaParam::GetBool(lua, 1);
  }
  int weatherType = LuaParam::GetInt(lua, 0);
  Weather::ForceWeatherNow(weatherType, rainWithThunder);
  return 0;
}

int cmdWeatherGet(lua_State *lua)
{
  LuaParam::PushInt(lua, Weather::InterpolationValue);
  return 1;
}

int cmdWeatherRelease(lua_State *lua)
{
  Weather::ForcedWeatherType = -1;
  Weather::WithThunder = 0;
  return 0;
}

int cmdPauseGameClock(lua_State *lua)
{
  Clock::ForcePauseThroughLua(1);
  return 0;
}

int cmdUnpauseGameClock(lua_State *lua)
{
  Clock::ForcePauseThroughLua(0);
  return 0;
}

int cmdClockIsPaused(lua_State *lua)
{
  LuaParam::PushBool(lua, Clock::m_bPaused);
  return 1;
}

int cmdPauseSimulation(lua_State *lua)
{
  CTimer::ms_fTimeScale = 0.0f;
  CPlayerInfo::MakePlayerSafe(CWorld::Player, 1);
  UserInputManager::SetInputEnabledFromScripts(g_UserInputManager, 0);
  ActionIntention::Clear(CWorld::Player.m_pPed->m_pForwardVec);
  CPed::ResetMotionIntentionDirection(CWorld::Player.m_pPed);
  ActionIntention *pDirection = CWorld::Player.m_pPed->m_pForwardVec;
  pDirection->m_fPreviousDirection = pDirection->m_fDirection;
  return 0;
}

int cmdUnpauseSimulation(lua_State *lua)
{
  CTimer::ms_fTimeScale = 1.0f;
  CPlayerInfo::MakePlayerSafe(CWorld::Player, 0);
  UserInputManager::SetInputEnabledFromScripts(g_UserInputManager, 1);
  return 0;
}

int cmdNormalizedTimeOverride(lua_State *lua)
{
  gOverrideNormalizedTime = LuaParam::GetBool(lua, 0);
  return 0;
}

int cmdNormalizedTimeOverrideSet(lua_State *lua)
{
  gOverridNormalizedTime = LuaParam::GetFloat(lua, 0);
  return 0;
}

int cmdWeatherForceSnow(lua_State *lua)
{
  Weather::ForcedSnow = LuaParam::GetBool(lua, 0);
  return 0;
}
	