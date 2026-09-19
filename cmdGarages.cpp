#include <LuaParam.h>
#include <Garages.h>
#include <TriggerManager.h>
#include <PointListManager.h>
#include <CGeneral.h>


int cmdGarageClearAll(lua_State *pLuaState)
{
  CGarages::RemoveAllGarages();
  return 0;
}

int cmdGarageAdd(lua_State *pLuaState)
{
  int triggerID = LuaParam::GetInt(pLuaState, 0);
  int pointlistID = LuaParam::GetInt(pLuaState, 1);
  
  CTriggerManager *pTrigger = TriggerManager::GetTrigger(triggerID);
  
  CTriggerManager *pAreaPerimeter = pTrigger->GetAreaPerimeter();
  PointListManager *pPointlist = PointListManager::GetPointList(pointlistID);
  
  /*
  v12 = v4[9] + *(v3 + 8);
  v14 = *(v3 + 12) - v4[3];
  v19[0] = v4[8] + *(v3 + 4);
  v19[1] = v12;
  v19[2] = v14;
  v15 = v4[11] + *(v3 + 8);
  v13 = v4[2] + *(v3 + 12);
  v6 = v4[10];
  v7 = 0;
  v18[0] = v6 + *(v3 + 4);
  v18[1] = v15;
  v18[2] = v13;
  v20[0] = 0.0;
  v20[1] = 0.0;
  v20[2] = 0.0;
  v20[3] = 0.0;
  v20[4] = 0.0;
  v20[5] = 0.0;
  */
  
  /*
  PointList *pPointlistStart = PointList::Begin(PointList);
  if ( v8 )
  {
    v9 = v20;
    do
    {
      *v9 = *v8;
      v9[1] = *(v8 + 4);
      v9[2] = *(v8 + 8);
      float fHeading = pPointlistStart->m_fHeading * 3.141592741012573 / 180.0;
      CGeneral::GetHeadingFromWorldEditorHeading(fHeading);
      v17[v7++] = fHeading;
      v9 += 3;
      PointList *pPointlistNext = PointList::Next(PointList);
    }
    while ( v8 );
  }
  */
  
  int garageAdd = CGarages::Add(v1, v2, v3, v4, v5);
  LuaParam::PushInt(pLuaState, garageAdd);
  return 1;
}

int cmdGarageSetIsDeactivated(lua_State *pLuaState)
{
  bool deactivate = LuaParam::GetBool(pLuaState, 0);
  CGarages::SetAllIsDeactivated(deactivate);
  return 0;
}

int cmdGarageSetStoredVehicle(lua_State *pLuaState)
{
  int garageIndex = LuaParam::GetInt(pLuaState, 0);
  int modelID = LuaParam::GetInt(pLuaState, 1);
  CGarages::SetStoredVehicle(garageIndex, modelID);
  return 0;
}

int cmdGarageHasStoredVehicle(lua_State *pLuaState)
{
  bool bIsGarageEmpty = CGarages::IsGarageEmpty();
  LuaParam::PushBool(pLuaState, !bIsGarageEmpty);
  return 1;
}
	