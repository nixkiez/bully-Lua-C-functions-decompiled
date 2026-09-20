#include <LuaParam.h>
#include <CollectiblesMgr.h>


int cmdCollectiblesSetTypeAvailable(lua_State *lua)
{
  bool setAvailable = 1;
  
  if (lua_gettop(lua) >= 2)
  {
    bool setAvailable = LuaParam::GetBool(lua, 1);
  }
  
  int collectibleType = LuaParam::GetInt(lua, 0);
  CCollectiblesMgr::SetAllTypeAvailable(g_CollectiblesMgr, collectibleType, setAvailable);
  return 0;
}

int cmdCollectiblesOnCollectedCallback(lua_State *lua)
{
  LuaParam::GetFunctionAllowNil(lua, 0, g_CollectiblesMgr.onCollectedCallback);
  return 0;
}

int cmdCollectiblesSetAllAsCollected(lua_State *lua)
{
  int collectibleType = LuaParam::GetInt(lua, 0);
  bool collectedAll = 1;
  
  if (lua_gettop(lua) >= 2)
  {
    bool collectedAll = LuaParam::GetBool(lua, 1);
  }
  
  CCollectiblesMgr::SetAllTypeCollected(g_CollectiblesMgr, collectibleType, collectedAll);
  return 0;
}

int cmdCollectiblesGetNumCollectable(lua_State *lua)
{
  int collectibleType = LuaParam::GetInt(lua, 0);
  int16_t maxCollectable = CCollectiblesMgr::GetMaxCollectable(g_CollectiblesMgr, collectibleType);
  LuaParam::PushInt(lua, maxCollectable);
  return 1;
}

int cmdCollectiblesGetNumCollected(lua_State *lua)
{
  int collectibleType = LuaParam::GetInt(lua, 0);
  int16_t numCollected = CCollectiblesMgr::GetNumCollected(g_CollectiblesMgr, collectibleType);
  LuaParam::PushInt(lua, numCollected);
  return 1;
}

int cmdCollectibleOnMapEnable(lua_State *lua)
{
  int collectibleType = LuaParam::GetInt(lua, 0);
  bool enableCollectibles = LuaParam::GetBool(lua, 1);
  CCollectiblesMgr::CollectibleOnMapEnable(g_CollectiblesMgr, collectibleType, enableCollectibles);
  return 0;
}