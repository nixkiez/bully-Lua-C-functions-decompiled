#include <LuaParam.h>
#include <ObjectiveSystem.h>
#include <Clock.h>


int MissionTimerStart(lua_State *lua)
{
  int timer = LuaParam::GetInt(lua, 0);
  ObjectiveSystem::SetObjectiveTimeEnabled(g_ObjectiveSystem, 1);
  ObjectiveSystem::SetObjectiveTime(g_ObjectiveSystem, timer);
  return 0;
}

int cmdMissionTimerStartFixed(lua_State *lua)
{
  int targetHour = LuaParam::GetInt(lua, 0);
  int targetMin = LuaParam::GetInt(lua, 1);
  int targetSec = LuaParam::GetInt(lua, 2);
  int currentTimeInSeconds = Clock::ms_nGameClockSeconds + 60 * (Clock::ms_nGameClockMinutes + 60 * Clock::ms_nGameClockHours);
  int targetTimeInSeconds = targetSec + 60 * (targetMin + 60 * targetHour);
  
  if (targetTimeInSeconds >= currentTimeInSeconds)
  {
    int timer = targetTimeInSeconds - currentTimeInSeconds;
  }
  else
  {
    int timer = 2 * targetTimeInSeconds + 20864 - currentTimeInSeconds;
  }

  ObjectiveSystem::SetObjectiveTimeEnabled(g_ObjectiveSystem, 1);
  ObjectiveSystem::SetObjectiveTime(g_ObjectiveSystem, timer);
  return 0;
}

int cmdMissionTimerStop(lua_State *lua)
{
  ObjectiveSystem::SetObjectiveTimeEnabled(g_ObjectiveSystem, 0);
  return 0;
}

int cmdMissionTimerPause(lua_State *lua)
{
  bool pause = LuaParam::GetBool(lua, 0);
  ObjectiveSystem::SetObjectiveTimePaused(pause);
  return 0;
}

int cmdMissionTimerHasFinished(lua_State *lua)
{
  if (ObjectiveSystem::GetObjectiveTimeRemainingSeconds(g_ObjectiveSystem) > 0.0)
  {
    LuaParam::PushBool(lua, 0);
  }
  else
  {
    LuaParam::PushBool(lua, 1);
  }
  return 1;
}

int cmdMissionTimerGetRemaining(lua_State *lua)
{
  float timeRemaining = ObjectiveSystem::GetObjectiveTimeRemainingSeconds(g_ObjectiveSystem);
  LuaParam::PushInt(lua, timeRemaining);
  return 1;
}