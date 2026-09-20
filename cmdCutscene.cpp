#include <LuaParam.h>
#include <CutsceneMgr.h>
#include <CheatCodeManager.h>
#include <TriggerManager.h>
#include <Pools.h>
#include <Ped.h>
#include <Objectives.h>
#include <Placeable.h>
#include <PedSocial.h>
#include <Vehicle.h>

int cmdLoadCutscene(lua_State *lua)
{
  const char *cutsceneID = LuaParam::GetString(lua, 0);
  bool loadCutsceneSound = LuaParam::GetBool(lua, 1);
  CCutsceneMgr::LoadCutsceneData(cutsceneID, loadCutsceneSound);
  return 0;
}

int cmdLoadCutsceneSound(lua_State *lua)
{
  const char *cutsceneID = LuaParam::GetString(lua, 0);
  CCutsceneMgr::LoadCutsceneSound(cutsceneID);
  return 0;
}

int cmdStartCutscene(lua_State *lua)
{
  CCutsceneMgr::StartCutscene();
  return 0;
}

int cmdStopCutscene(lua_State *lua)
{
  CCutsceneMgr::DeleteCutsceneData();
  return 0;
}

int cmdGetCutsceneTime(lua_State *lua)
{
  int currTimeInMil = CCutsceneMgr::GetCutsceneTimeInMilleseconds();
  LuaParam::PushInt(lua, currTimeInMil);
  return 1;
}

int cmdGetCutsceneRunning(lua_State *lua)
{
  LuaParam::PushInt(lua, CCutsceneMgr::ms_running);
  return 1;
}

int cmdCutSceneSetActionNode(lua_State *lua)
{
  const char *cutsceneID = LuaParam::GetString(lua, 0);
  bool success = CCutsceneMgr::SetActionNode(cutsceneID, 0);
  LuaParam::PushBool(lua, success);
  return 1;
}

int cmdCutSetCutsceneTableSize(lua_State *lua)
{
  int cutsceneTableSize = LuaParam::GetInt(lua, 0);
  CheatJumpToCutscene::SetNumCutscenes(cutsceneTableSize);
  return 0;
}

int cmdCutSetCutsceneName(lua_State *lua)
{
  const char *cutsceneID = LuaParam::GetString(lua, 0);
  CheatJumpToCutscene::SetCutsceneName(cutsceneID);
  return 0;
}

int cmdAddPAnimToNextCutscene(lua_State *lua)
{
  if (LuaParam::IsInt(lua, 1))
  {
    int animIndex = LuaParam::GetInt(lua, 0);
    TriggerManager *pTrigger = TriggerManager::GetTrigger(g_TriggerManager, animIndex);
	
    if (pTrigger && pTrigger->pAnim)
	{
      CCutsceneMgr::AddPAnimToNextCutscene(pTrigger->pAnim);
	}
  }
  return 0;
}

int cmdStopAmbientPedAttacks(lua_State *lua)
{
  CPools *pPedPool = CPools::ms_pPedPool;
  for (int i = pPedPool->m_nSize - 1; i >= 0; --i)
  {
    CPed* pPed = pPedPool->GetSlot(i);
	if (pPed)
	{
      if (CPed::CanBeDeleted(pPed))
      {
		AttackPedObjective *pAttacker = ObjectiveCast(ObjectiveQueue::GetCurrentObjective(pPed->m_nCurrObjective));
        if (pAttacker)
        {
          CPed *matrix = CPlaceable::GetMatrix(pAttacker);
          if (matrix)
          {
            if matrix->m_ePedType == PEDTYPE_PLAYER || matrix->m_nFactionId == 13 )
            {
              ObjectiveQueue::RemoveObjectiveOfType(7);
              CPedSocial::ClearAnyStimulusFromTarget(pPed->m_nStimuliQueue);
              CPedSocial::StopSocializing(pPed->m_nSocialQueue);
              CPed::SetTarget(0);
            }
          }
        }
      }
    }
  }
  return 0;
}

int cmdSetAmbientPedsIgnoreStimuli(lua_State *lua)
{
  bool ignoreStimuli = LuaParam::GetBool(lua, 0);
  CPools *pPedPool = CPools::ms_pPedPool;
  
  for (int i = pPedPool->m_nSize - 1; i >= 0; --i)
  {
    CPed *pPed = pPedPool->GetSlot(i);
 
    if (pPed && CPed::CanBeDeleted(pPed))
    {
      pPed->m_nFlags.IgnoreAmbientStimuli = ignoreStimuli;
    }
  }
  return 0;
}

int cmdEnterNIS(lua_State *lua)
{
  bNISIsRunning = true;
  CPools *pVehiclePool = CPools::ms_pVehiclePool;

  for (int i = 0; i < pVehiclePool->m_nSize; ++i)
  {
    CVehicle *pVehicle = pVehiclePool->GetSlot(i);
    if (pVehicle)
    {
      CVehicle::NISStateChange(true);
    }
  }
  return 0;
}

int cmdExitNIS(lua_State *lua)
{
  bNISIsRunning = false;
  CPools *pVehiclePool = CPools::ms_pVehiclePool;

  for (int i = 0; i < pVehiclePool->m_nSize; ++i)
  {
    CVehicle *pVehicle = pVehiclePool->GetSlot(i);
    if (pVehicle)
    {
      CVehicle::NISStateChange(false);
    }
  }
  return 0;
}

int cmdIsCutsceneLoaded(lua_State *lua)
{
  LuaParam::PushBool(lua, CCutsceneMgr::ms_loadStatus);
  return 1;
}


