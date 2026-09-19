#include <LuaParam.h>
#include <BulletinBoardMgr.h>


int cmdBulletinSetupTexture(lua_State *pLuaState)
{
	const char *pTexture = LuaParam::GetString(pLuaState, 0);
	CBulletinBoardMgr::AddBulletinTexture(g_BulletinBoardMgr, pTexture);
	return 0;
}

int cmdBulletinSetupMessage(lua_State *pLuaState)
{
	const char *pMessage1 = LuaParam::GetString(pLuaState, 0);
	const char *pMessage2 = LuaParam::GetString(pLuaState, 1);
	
	int message = CBulletinBoardMgr::AddBulletinMessage(g_BulletinBoardMgr, pMessage1, pMessage2);
	LuaParam::PushInt(pLuaState, message);
	return 1;
}
	