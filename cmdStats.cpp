#include <LuaParam.h>
#include <CPed.h>
#include <EntityTypeEnum.h>
#include <Stats.h>
#include <GameCompletionMgr.h>


int cmdGameGetPedStat(lua_State *lua)
{
  int ped = LuaParam::GetInt(lua, 0);
  CPed *pPed = GetPed(ped, ENTITY_TYPE_PED);
  
  if (pPed)
  {
    int stat = LuaParam::GetInt(lua, 1);
    int pedStat = CPed::GetStat(pPed, stat);
    LuaParam::PushInt(lua, pedStat);
  }
  else
  {
    LuaParam::PushInt(lua, 0);
  }
  return 1;
}

int cmdGameSetPedStat(lua_State *lua)
{
  int ped = LuaParam::GetInt(lua, 0);
  CPed *pPed = GetPed(Int, ENTITY_TYPE_PED);
  
  if (pPed)
  {
    int stat = LuaParam::GetInt(lua, 1);
    int value = LuaParam::GetInt(lua, 2);
    CPed::SetStat(pPed, stat, value);
  }
  return 0;
}

int cmdStatSetAsInt(lua_State *lua)
{
  int value = LuaParam::GetInt(lua, 0);
  int stat = LuaParam::GetInt(lua, 1);
  CStats::SetAsInt(value, stat);
  return 0;
}

int cmdStatSetAsFloat(lua_State *lua)
{
  int stat = LuaParam::GetInt(lua, 0);
  float value = LuaParam::GetFloat(lua, 1);
  CStats::SetAsFloat(value, stat);
  return 0;
}

int cmdStatAddToInt(lua_State *lua)
{
  int value = 1;
  
  if (lua_gettop(lua) >= 2)
  {
    int value = LuaParam::GetInt(lua, 1);
  }
  
  int stat = LuaParam::GetInt(lua, 0);
  CStats::AddToInt(stat, value);
  return 0;
}

int cmdStatAddToFloat(lua_State *lua)
{
  float value = 1.0f;
  
  if (lua_gettop(lua) >= 2)
  {
    float value = LuaParam::GetFloat(lua, 1);
  }
  
  int stat = LuaParam::GetInt(lua, 0);
  CStats::AddToFloat(stat, value);
  return 0;
}

int cmdStatGetAsInt(lua_State *lua)
{
  int stat = LuaParam::GetInt(lua, 0);
  int statValue = CStats::GetAsInt(stat);
  LuaParam::PushInt(lua, statValue);
  return 1;
}

int cmdStatGetAsFloat(lua_State *lua)
{
  int stat = LuaParam::GetInt(lua, 0);
  float statValue = CStats::GetAsFloat(stat);
  LuaParam::PushFloat(lua, statValue);
  return 1;
}

int cmdStatLayoutAddGroup(lua_State *lua)
{
  const char *group = LuaParam::GetString(lua, 0);
  CStats::LayoutAddGroup(group);
  return 0;
}

int cmdStatLayoutAddHeading(lua_State *lua)
{
  const char *heading = LuaParam::GetString(lua, 0);
  CStats::LayoutAddHeading(heading);
  return 0;
}

int cmdStatLayoutAddStat(lua_State *lua)
{
  const char *stat = LuaParam::GetString(lua, 0);
  int statSlot = LuaParam::GetInt(lua, 1);
  CStats::LayoutAddStat(stat, statSlot);
  return 0;
}

int cmdStatGetPrincipalDiffAsInt(lua_State *lua)
{
  int stat = LuaParam::GetInt(lua, 0);
  int principalDiffStat = CStats::GetPrincipalDiffStatAsInt(stat);
  LuaParam::PushInt(lua, principalDiffStat);
  return 1;
}

int cmdStatGetPrincipalDiffAsFloat(lua_State *lua)
{
  int stat = LuaParam::GetInt(lua, 0);
  float principalDiffStat = CStats::GetPrincipalDiffStatAsInt(stat);
  LuaParam::PushFloat(lua, principalDiffStat);
  return 1;
}

int cmdStatUpdatePrincipalStats(lua_State *lua)
{
  CStats::UpdatePrincipalStats();
  return 0;
}

int cmdStatGetNumLayoutItems(lua_State *lua)
{
  LuaParam::PushInt(lua, CStats::ms_iNumLayoutItems);
  return 1;
}

int cmdStatSetIsTrackingEnabled(lua_State *lua)
{
  CStats::ms_bIsTrackingEnabled = LuaParam::GetBool(lua, 0);
  return 0;
}

int cmdStatResetAll(lua_State *lua)
{
  CStats::Initialise();
  return 0;
}

int cmdStatGetGameCompletion(lua_State *lua)
{
  float completedPct = CGameCompletionMgr::GetCompletedPct();
  LuaParam::PushFloat(lua, completedPct);
  return 1;
}


