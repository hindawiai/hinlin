<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__ODM_PRECOMP_H__
#घोषणा __ODM_PRECOMP_H__

#समावेश "odm_types.h"

#घोषणा		TEST_FALG___		1

/* 2 Config Flags and Structs - defined by each ODM Type */

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <usb_ops_linux.h>

/* 2 OutSrc Header Files */

#समावेश "odm.h"
#समावेश "odm_hwconfig.h"
#समावेश "odm_debug.h"
#समावेश "phydm_regdefine11n.h"

#समावेश "hal8188e_rate_adaptive.h" /* क्रम RA,Power training */
#समावेश "rtl8188e_hal.h"

#समावेश "phydm_reg.h"

#समावेश "odm_rtl8188e.h"

व्योम odm_CmnInfoHook_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_CmnInfoInit_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DIGInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RateAdaptiveMaskInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DynamicBBPowerSavingInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DynamicTxPowerInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_TXPowerTrackingInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम ODM_EdcaTurboInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_SwAntDivInit_NIC(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_CmnInfoUpdate_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_CommonInfoSelfUpdate(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_FalseAlarmCounterStatistics(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DIG(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_CCKPacketDetectionThresh(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RefreshRateAdaptiveMaskMP(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DynamicBBPowerSaving(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_SwAntDivChkAntSwitch(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 Step);
व्योम odm_EdcaTurboCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_CommonInfoSelfInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RSSIMonitorCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RefreshRateAdaptiveMask(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_1R_CCA(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RefreshRateAdaptiveMaskCE(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RefreshRateAdaptiveMaskAPADSL(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_DynamicTxPowerNIC(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_RSSIMonitorCheckCE(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_EdcaTurboCheckCE(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_SwAntDivChkAntSwitchCallback(व्योम *FunctionContext);
व्योम odm_InitHybridAntDiv(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम odm_HwAntDiv(काष्ठा odm_dm_काष्ठा *pDM_Odm);

#पूर्ण_अगर	/*  __ODM_PRECOMP_H__ */
