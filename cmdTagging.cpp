#include <LuaParam.h>
#include <Tagging.h>
#include <TriggerManager.h>


int cmdTaggingPedHasJustFinished(lua_State *lua)
{
  bool pedHasJustFinished = 0;
  int triggerIndex = 0;
  int triggerHash = 0;
  int pedIndex = 0;
  if (Tagging::GetTagCompleted(g_Tagging, triggerHash, pedIndex))
  {
    int triggerIndexFromHash = TriggerManager::GetTriggerIndexFromHash(triggerHash);
    if (lua_gettop(lua) != 1 || (LuaParam::GetInt(lua, 0) == pedIndex)
    {
      triggerIndex = TriggerIndexFromHash;
      pedHasJustFinished = 1;
    }
  }
  LuaParam::PushBool(lua, pedHasJustFinished);
  LuaParam::PushInt(lua, triggerIndex);
  return 2;
}

int cmdTaggingOnlyShowMissionTags(lua_State *lua)
{
  g_Tagging.m_bOnlyShowMissionTags = LuaParam::GetBool(lua, 0);
  return 0;
}

int cmdTaggingSetTVsState(lua_State *lua)
{
  g_Tagging.m_bTVsState = LuaParam::GetBool(lua, 0);
  return 0;
}

int cmdTaggingStartPersistentTag(lua_State *lua)
{
  Tagging::StartSemiPersistentTag(g_Tagging);
  return 0;
}

int cmdTaggingStopPersistentTag(lua_State *lua)
{
  Tagging::StopSemiPersistentTag(g_Tagging);
  return 0;
}