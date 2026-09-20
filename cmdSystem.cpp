#include <LuaParam.h>
#include <Game.h>
#include <MissionMgr.h>
#include <ScriptManager.h>
#include <ColStore.h>
#include <Frontend.h>
#include <GameLogic.h>
#include <Stats.h>
#include <MultiplayerMgr.h>

int cmdSystemShouldMovePlayer(lua_State *lua)
{
  LuaParam::PushBool(lua, CGame::ShouldMovePlayer());
  LuaParam::PushInt(lua, CGame::m_sPlayerPositioningMechanism);
  return 2;
}

int cmdSystemResetShouldMovePlayer(lua_State *lua)
{
  CGame::ResetShouldMovePlayer();
  return 0;
}

int cmdSystemGetSavedPositionInformation(lua_State *lua)
{
  LuaParam::PushFloat(lua, CGame::m_sSavedPosition[0]);
  LuaParam::PushFloat(lua, CGame::m_sSavedPosition[1]);
  LuaParam::PushFloat(lua, CGame::m_sSavedPosition[2]);
  LuaParam::PushFloat(lua, CGame::m_sSavedHeadingInRadians * RADIANS_TO_DEGREES);
  LuaParam::PushInt(lua, CGame::m_sSavedAreaCode);
  LuaParam::PushBool(lua, CGame::m_sbRestartMission);
  return 6;
}

int cmdSystemAllowMissionManagerToForceRunMissions(lua_State *lua)
{
  g_MissionMgr.m_bCanForceRunMissions = 1;
  return 0;
}

int cmdSystemShouldEndScript(lua_State *lua)
{
  ScriptManager *pCurrScript = ScriptManager::GetScriptByState(lua);
  bool shouldEndScript = 0;
  if (pCurrScript)
  {
    bool shouldEndScript = pCurrScript->m_bShouldEndScript;
  }
  LuaParam::PushBool(lua, shouldEndScript);
  return 1;
}

int cmdSystemMarkCollisionForExclusion(lua_State *lua)
{
  const char *colModel = LuaParam::GetString(lua, 0);
  CColStore::AddCollisionModelToExcludeFromSpecialHasCollisionLoaded(colModel);
  return 0;
}

int cmdReadyToLoad(lua_State *lua)
{
  CGame::ms_bReadyToLoad = 1;
  return 0;
}

int cmdSystemIsReady(lua_State *lua)
{
  LuaParam::PushBool(lua, CGame::ms_bSystemReady);
  return 1;
}

int cmdIsInTitleMenu(lua_State *lua)
{
  if (FrontEnd::m_bGameTitleMenuActive || FrontEnd::m_bTitleScreenFlag)
  {
    LuaParam::PushBool(lua, 1);
    return 1;
  }
  else
  {
    LuaParam::PushBool(lua, 0);
    return 1;
  }
}

int cmdSystemBustedAreaTransitionHandled(lua_State *lua)
{
  g_GameLogic.m_bBustedAreaTransitionHandled = true;
  return 0;
}

int cmdSystemEnableFrontEndAndSelectScreens(lua_State *lua)
{
  FrontEnd::m_bFrontEndAndSelectScreensEnabled = LuaParam::GetBool(lua, 0);
  return 0;
}

int cmdIsDemoBuildEnabled(lua_State *lua)
{
  LuaParam::PushBool(lua, 0);
  return 1;
}

int cmdDemoBuildGetSelectedMission(lua_State *lua)
{
  LuaParam::PushBool(lua, -1);
  return 1;
}

int cmdDemoBuildReturnToMain(lua_State *lua)
{
  FrontEnd::m_bRestartRequested = 1;
  CStats::Shutdown();
  CStats::Initialise();
  return 0;
}

int cmdHasStoryModeBeenSelected(lua_State *lua)
{
  LuaParam::PushBool(lua, FrontEnd::m_bStoryModeActive);
  return 1;
}

int cmdReturnFromMPGame(lua_State *lua)
{
  return 0;
}

int cmdSetPlayer1Win(lua_State *lua)
{
  FrontEnd::SetPlayer1WonMatch(lua); // only calls this on Wii/X360
  return 0;
}

int cmdSetPlayer2Win(lua_State *lua)
{
  FrontEnd::SetPlayer2WonMatch(lua); // only calls this on Wii/X360
  return 0;
}

int cmdGetRequestedSubMPGame(lua_State *lua)
{
  LuaParam::PushInt(lua, g_MultiplayerMgr->m_nSlots[g_MultiplayerMgr->m_CurrentSlot].m_nRequestedSubMPGame); // only calls this on Wii/X360
  return 1;
}

