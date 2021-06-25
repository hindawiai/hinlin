<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"
#समावेश "phy.h"

u32 GlobalDebugLevel;

/* aव्योम to warn in FreeBSD ==> To DO modअगरy */
अटल u32 EDCAParam[HT_IOT_PEER_MAX][3] = अणु
	/*  UL			DL */
	अणु0x5ea42b, 0x5ea42b, 0x5ea42bपूर्ण, /* 0:unknown AP */
	अणु0xa44f, 0x5ea44f, 0x5e431cपूर्ण, /*  1:realtek AP */
	अणु0x5ea42b, 0x5ea42b, 0x5ea42bपूर्ण, /*  2:unknown AP => realtek_92SE */
	अणु0x5ea32b, 0x5ea42b, 0x5e4322पूर्ण, /*  3:broadcom AP */
	अणु0x5ea422, 0x00a44f, 0x00a44fपूर्ण, /*  4:ralink AP */
	अणु0x5ea322, 0x00a630, 0x00a44fपूर्ण, /*  5:atheros AP */
	अणु0x5e4322, 0x5e4322, 0x5e4322पूर्ण,/*  6:cisco AP */
	अणु0x5ea44f, 0x00a44f, 0x5ea42bपूर्ण, /*  8:marvell AP */
	अणु0x5ea42b, 0x5ea42b, 0x5ea42bपूर्ण, /*  10:unknown AP=> 92U AP */
	अणु0x5ea42b, 0xa630, 0x5e431cपूर्ण, /*  11:airgocap AP */
पूर्ण;

/*  Global var */
u32 OFDMSwingTable[OFDM_TABLE_SIZE_92D] = अणु
	0x7f8001fe, /*  0, +6.0dB */
	0x788001e2, /*  1, +5.5dB */
	0x71c001c7, /*  2, +5.0dB */
	0x6b8001ae, /*  3, +4.5dB */
	0x65400195, /*  4, +4.0dB */
	0x5fc0017f, /*  5, +3.5dB */
	0x5a400169, /*  6, +3.0dB */
	0x55400155, /*  7, +2.5dB */
	0x50800142, /*  8, +2.0dB */
	0x4c000130, /*  9, +1.5dB */
	0x47c0011f, /*  10, +1.0dB */
	0x43c0010f, /*  11, +0.5dB */
	0x40000100, /*  12, +0dB */
	0x3c8000f2, /*  13, -0.5dB */
	0x390000e4, /*  14, -1.0dB */
	0x35c000d7, /*  15, -1.5dB */
	0x32c000cb, /*  16, -2.0dB */
	0x300000c0, /*  17, -2.5dB */
	0x2d4000b5, /*  18, -3.0dB */
	0x2ac000ab, /*  19, -3.5dB */
	0x288000a2, /*  20, -4.0dB */
	0x26000098, /*  21, -4.5dB */
	0x24000090, /*  22, -5.0dB */
	0x22000088, /*  23, -5.5dB */
	0x20000080, /*  24, -6.0dB */
	0x1e400079, /*  25, -6.5dB */
	0x1c800072, /*  26, -7.0dB */
	0x1b00006c, /*  27. -7.5dB */
	0x19800066, /*  28, -8.0dB */
	0x18000060, /*  29, -8.5dB */
	0x16c0005b, /*  30, -9.0dB */
	0x15800056, /*  31, -9.5dB */
	0x14400051, /*  32, -10.0dB */
	0x1300004c, /*  33, -10.5dB */
	0x12000048, /*  34, -11.0dB */
	0x11000044, /*  35, -11.5dB */
	0x10000040, /*  36, -12.0dB */
	0x0f00003c,/*  37, -12.5dB */
	0x0e400039,/*  38, -13.0dB */
	0x0d800036,/*  39, -13.5dB */
	0x0cc00033,/*  40, -14.0dB */
	0x0c000030,/*  41, -14.5dB */
	0x0b40002d,/*  42, -15.0dB */
पूर्ण;

u8 CCKSwingTable_Ch1_Ch13[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण, /*  0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण, /*  1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण, /*  2, -1.0dB */
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण, /*  3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण, /*  4, -2.0dB */
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण, /*  5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण, /*  6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण, /*  7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण, /*  8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण, /*  9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण, /*  10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण, /*  11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण, /*  12, -6.0dB */
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण, /*  13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण, /*  15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण, /*  16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण, /*  17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण, /*  18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण, /*  20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण, /*  22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01पूर्ण, /*  23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01पूर्ण, /*  24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01पूर्ण, /*  25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण, /*  28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*  29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण, /*  30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01पूर्ण, /*  31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01पूर्ण  /*  32, -16.0dB */
पूर्ण;

u8 CCKSwingTable_Ch14[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  2, -1.0dB */
	अणु0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  4, -2.0dB */
	अणु0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  12, -6.0dB */
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण, /*  31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00पूर्ण  /*  32, -16.0dB */
पूर्ण;

#घोषणा		RxDefaultAnt1		0x65a9
#घोषणा	RxDefaultAnt2		0x569a

व्योम ODM_InitDebugSetting(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	pDM_Odm->DebugLevel = ODM_DBG_TRACE;

	pDM_Odm->DebugComponents = 0;
पूर्ण

/* 3 Export Interface */

/*  2011/09/21 MH Add to describe dअगरferent team necessary resource allocate?? */
व्योम ODM_DMInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	/* 2012.05.03 Luke: For all IC series */
	odm_CommonInfoSelfInit(pDM_Odm);
	odm_CmnInfoInit_Debug(pDM_Odm);
	odm_DIGInit(pDM_Odm);
	odm_RateAdaptiveMaskInit(pDM_Odm);

	odm_DynamicTxPowerInit(pDM_Odm);
	odm_TXPowerTrackingInit(pDM_Odm);
	ODM_EdcaTurboInit(pDM_Odm);
	ODM_RAInfo_Init_all(pDM_Odm);
	अगर ((pDM_Odm->AntDivType == CG_TRX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CGCS_RX_HW_ANTDIV) ||
	    (pDM_Odm->AntDivType == CG_TRX_SMART_ANTDIV))
		odm_InitHybridAntDiv(pDM_Odm);
पूर्ण

/*  2011/09/20 MH This is the entry poपूर्णांकer क्रम all team to execute HW out source DM. */
/*  You can not add any dummy function here, be care, you can only use DM काष्ठाure */
/*  to perक्रमm any new ODM_DM. */
व्योम ODM_DMWatchकरोg(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	/* 2012.05.03 Luke: For all IC series */
	odm_CmnInfoHook_Debug(pDM_Odm);
	odm_CmnInfoUpdate_Debug(pDM_Odm);
	odm_CommonInfoSelfUpdate(pDM_Odm);
	odm_FalseAlarmCounterStatistics(pDM_Odm);
	odm_RSSIMonitorCheck(pDM_Odm);

	/* Fix Leave LPS issue */
	odm_DIG(pDM_Odm);
	odm_CCKPacketDetectionThresh(pDM_Odm);

	अगर (*pDM_Odm->pbPowerSaving)
		वापस;

	odm_RefreshRateAdaptiveMask(pDM_Odm);

	अगर ((pDM_Odm->AntDivType ==  CG_TRX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CGCS_RX_HW_ANTDIV)	||
	    (pDM_Odm->AntDivType == CG_TRX_SMART_ANTDIV))
		odm_HwAntDiv(pDM_Odm);

	ODM_TXPowerTrackingCheck(pDM_Odm);
	odm_EdcaTurboCheck(pDM_Odm);
पूर्ण

व्योम ODM_CmnInfoPtrArrayHook(काष्ठा odm_dm_काष्ठा *pDM_Odm, क्रमागत odm_common_info_def CmnInfo, u16 Index, व्योम *pValue)
अणु
	अगर (CmnInfo == ODM_CMNINFO_STA_STATUS)
		pDM_Odm->pODM_StaInfo[Index] = (काष्ठा sta_info *)pValue;
पूर्ण

व्योम odm_CommonInfoSelfInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *adapter = pDM_Odm->Adapter;

	pDM_Odm->bCckHighPower = (bool)phy_query_bb_reg(adapter, 0x824, BIT(9));
	pDM_Odm->RFPathRxEnable = (u8)phy_query_bb_reg(adapter, 0xc04, 0x0F);

	ODM_InitDebugSetting(pDM_Odm);
पूर्ण

व्योम odm_CommonInfoSelfUpdate(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	u8 EntryCnt = 0;
	u8 i;
	काष्ठा sta_info *pEntry;

	अगर (*pDM_Odm->pBandWidth == ODM_BW40M) अणु
		अगर (*pDM_Odm->pSecChOffset == 1)
			pDM_Odm->ControlChannel = *pDM_Odm->pChannel - 2;
		अन्यथा अगर (*pDM_Odm->pSecChOffset == 2)
			pDM_Odm->ControlChannel = *pDM_Odm->pChannel + 2;
	पूर्ण अन्यथा अणु
		pDM_Odm->ControlChannel = *pDM_Odm->pChannel;
	पूर्ण

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		pEntry = pDM_Odm->pODM_StaInfo[i];
		अगर (IS_STA_VALID(pEntry))
			EntryCnt++;
	पूर्ण
	अगर (EntryCnt == 1)
		pDM_Odm->bOneEntryOnly = true;
	अन्यथा
		pDM_Odm->bOneEntryOnly = false;
पूर्ण

व्योम odm_CmnInfoInit_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("%s==>\n", __func__));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportPlatform=%d\n", pDM_Odm->SupportPlatक्रमm));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportAbility=0x%x\n", pDM_Odm->SupportAbility));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportInterface=%d\n", pDM_Odm->SupportInterface));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("SupportICType=0x%x\n", pDM_Odm->SupportICType));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("CutVersion=%d\n", pDM_Odm->CutVersion));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("BoardType=%d\n", pDM_Odm->BoardType));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtLNA=%d\n", pDM_Odm->ExtLNA));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtPA=%d\n", pDM_Odm->ExtPA));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("ExtTRSW=%d\n", pDM_Odm->ExtTRSW));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("PatchID=%d\n", pDM_Odm->PatchID));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bInHctTest=%d\n", pDM_Odm->bInHctTest));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFITest=%d\n", pDM_Odm->bWIFITest));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bDualMacSmartConcurrent=%d\n", pDM_Odm->bDualMacSmartConcurrent));
पूर्ण

व्योम odm_CmnInfoHook_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("%s==>\n", __func__));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pNumTxBytesUnicast=%llu\n", *pDM_Odm->pNumTxBytesUnicast));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pNumRxBytesUnicast=%llu\n", *pDM_Odm->pNumRxBytesUnicast));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pWirelessMode=0x%x\n", *pDM_Odm->pWirelessMode));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pSecChOffset=%d\n", *pDM_Odm->pSecChOffset));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pSecurity=%d\n", *pDM_Odm->pSecurity));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pBandWidth=%d\n", *pDM_Odm->pBandWidth));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pChannel=%d\n", *pDM_Odm->pChannel));

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pbScanInProcess=%d\n", *pDM_Odm->pbScanInProcess));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("pbPowerSaving=%d\n", *pDM_Odm->pbPowerSaving));
पूर्ण

व्योम odm_CmnInfoUpdate_Debug(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("%s==>\n", __func__));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFI_Direct=%d\n", pDM_Odm->bWIFI_Direct));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFI_Display=%d\n", pDM_Odm->bWIFI_Display));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bLinked=%d\n", pDM_Odm->bLinked));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("RSSI_Min=%d\n", pDM_Odm->RSSI_Min));
पूर्ण

व्योम ODM_Write_DIG(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 CurrentIGI)
अणु
	काष्ठा rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	काष्ठा adapter *adapter = pDM_Odm->Adapter;

	अगर (pDM_DigTable->CurIGValue != CurrentIGI) अणु
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, ODM_BIT_IGI_11N, CurrentIGI);
		pDM_DigTable->CurIGValue = CurrentIGI;
	पूर्ण
पूर्ण

व्योम odm_DIGInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *adapter = pDM_Odm->Adapter;
	काष्ठा rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;

	pDM_DigTable->CurIGValue = (u8)phy_query_bb_reg(adapter, ODM_REG_IGI_A_11N, ODM_BIT_IGI_11N);
	pDM_DigTable->RssiLowThresh	= DM_DIG_THRESH_LOW;
	pDM_DigTable->RssiHighThresh	= DM_DIG_THRESH_HIGH;
	pDM_DigTable->FALowThresh	= DM_false_ALARM_THRESH_LOW;
	pDM_DigTable->FAHighThresh	= DM_false_ALARM_THRESH_HIGH;
	pDM_DigTable->rx_gain_range_max = DM_DIG_MAX_NIC;
	pDM_DigTable->rx_gain_range_min = DM_DIG_MIN_NIC;
	pDM_DigTable->BackoffVal = DM_DIG_BACKOFF_DEFAULT;
	pDM_DigTable->BackoffVal_range_max = DM_DIG_BACKOFF_MAX;
	pDM_DigTable->BackoffVal_range_min = DM_DIG_BACKOFF_MIN;
	pDM_DigTable->PreCCK_CCAThres = 0xFF;
	pDM_DigTable->CurCCK_CCAThres = 0x83;
	pDM_DigTable->ForbiddenIGI = DM_DIG_MIN_NIC;
	pDM_DigTable->LargeFAHit = 0;
	pDM_DigTable->Recover_cnt = 0;
	pDM_DigTable->DIG_Dynamic_MIN_0 = DM_DIG_MIN_NIC;
	pDM_DigTable->DIG_Dynamic_MIN_1 = DM_DIG_MIN_NIC;
	pDM_DigTable->bMediaConnect_0 = false;
	pDM_DigTable->bMediaConnect_1 = false;

	/* To Initialize pDM_Odm->bDMInitialGainEnable == false to aव्योम DIG error */
	pDM_Odm->bDMInitialGainEnable = true;
पूर्ण

व्योम odm_DIG(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	काष्ठा false_alarm_stats *pFalseAlmCnt = &pDM_Odm->FalseAlmCnt;
	u8 DIG_Dynamic_MIN;
	u8 DIG_MaxOfMin;
	bool FirstConnect, FirstDisConnect;
	u8 dm_dig_max, dm_dig_min;
	u8 CurrentIGI = pDM_DigTable->CurIGValue;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s()==>\n", __func__));
	अगर ((!(pDM_Odm->SupportAbility & ODM_BB_DIG)) || (!(pDM_Odm->SupportAbility & ODM_BB_FA_CNT))) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
			     ("%s() Return: SupportAbility ODM_BB_DIG or ODM_BB_FA_CNT is disabled\n", __func__));
		वापस;
	पूर्ण

	अगर (*pDM_Odm->pbScanInProcess) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s() Return: In Scan Progress\n", __func__));
		वापस;
	पूर्ण

	/* add by Neil Chen to aव्योम PSD is processing */
	अगर (!pDM_Odm->bDMInitialGainEnable) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s() Return: PSD is Processing\n", __func__));
		वापस;
	पूर्ण

	DIG_Dynamic_MIN = pDM_DigTable->DIG_Dynamic_MIN_0;
	FirstConnect = (pDM_Odm->bLinked) && (!pDM_DigTable->bMediaConnect_0);
	FirstDisConnect = (!pDM_Odm->bLinked) && (pDM_DigTable->bMediaConnect_0);

	/* 1 Boundary Decision */
	dm_dig_max = DM_DIG_MAX_NIC;
	dm_dig_min = DM_DIG_MIN_NIC;
	DIG_MaxOfMin = DM_DIG_MAX_AP;

	अगर (pDM_Odm->bLinked) अणु
		/* 2 Modअगरy DIG upper bound */
		अगर ((pDM_Odm->RSSI_Min + 20) > dm_dig_max)
			pDM_DigTable->rx_gain_range_max = dm_dig_max;
		अन्यथा अगर ((pDM_Odm->RSSI_Min + 20) < dm_dig_min)
			pDM_DigTable->rx_gain_range_max = dm_dig_min;
		अन्यथा
			pDM_DigTable->rx_gain_range_max = pDM_Odm->RSSI_Min + 20;
		/* 2 Modअगरy DIG lower bound */
		अगर (pDM_Odm->bOneEntryOnly) अणु
			अगर (pDM_Odm->RSSI_Min < dm_dig_min)
				DIG_Dynamic_MIN = dm_dig_min;
			अन्यथा अगर (pDM_Odm->RSSI_Min > DIG_MaxOfMin)
				DIG_Dynamic_MIN = DIG_MaxOfMin;
			अन्यथा
				DIG_Dynamic_MIN = pDM_Odm->RSSI_Min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
				     ("%s() : bOneEntryOnly=true,  DIG_Dynamic_MIN=0x%x\n",
				      __func__, DIG_Dynamic_MIN));
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
				     ("%s() : pDM_Odm->RSSI_Min=%d\n",
				      __func__, pDM_Odm->RSSI_Min));
		पूर्ण अन्यथा अगर (pDM_Odm->SupportAbility & ODM_BB_ANT_DIV) अणु
			/* 1 Lower Bound क्रम 88E AntDiv */
			अगर (pDM_Odm->AntDivType == CG_TRX_HW_ANTDIV) अणु
				DIG_Dynamic_MIN = (u8)pDM_DigTable->AntDiv_RSSI_max;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
					     ("%s(): pDM_DigTable->AntDiv_RSSI_max=%d\n",
					      __func__, pDM_DigTable->AntDiv_RSSI_max));
			पूर्ण
		पूर्ण अन्यथा अणु
			DIG_Dynamic_MIN = dm_dig_min;
		पूर्ण
	पूर्ण अन्यथा अणु
		pDM_DigTable->rx_gain_range_max = dm_dig_max;
		DIG_Dynamic_MIN = dm_dig_min;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s() : No Link\n", __func__));
	पूर्ण

	/* 1 Modअगरy DIG lower bound, deal with abnormally large false alarm */
	अगर (pFalseAlmCnt->Cnt_all > 10000) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("dm_DIG(): Abnormally false alarm case.\n"));

		अगर (pDM_DigTable->LargeFAHit != 3)
			pDM_DigTable->LargeFAHit++;
		अगर (pDM_DigTable->ForbiddenIGI < CurrentIGI) अणु
			pDM_DigTable->ForbiddenIGI = CurrentIGI;
			pDM_DigTable->LargeFAHit = 1;
		पूर्ण

		अगर (pDM_DigTable->LargeFAHit >= 3) अणु
			अगर ((pDM_DigTable->ForbiddenIGI + 1) > pDM_DigTable->rx_gain_range_max)
				pDM_DigTable->rx_gain_range_min = pDM_DigTable->rx_gain_range_max;
			अन्यथा
				pDM_DigTable->rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 1);
			pDM_DigTable->Recover_cnt = 3600; /* 3600=2hr */
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Recovery mechanism क्रम IGI lower bound */
		अगर (pDM_DigTable->Recover_cnt != 0) अणु
			pDM_DigTable->Recover_cnt--;
		पूर्ण अन्यथा अणु
			अगर (pDM_DigTable->LargeFAHit < 3) अणु
				अगर ((pDM_DigTable->ForbiddenIGI - 1) < DIG_Dynamic_MIN) अणु /* DM_DIG_MIN) */
					pDM_DigTable->ForbiddenIGI = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					pDM_DigTable->rx_gain_range_min = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): Normal Case: At Lower Bound\n", __func__));
				पूर्ण अन्यथा अणु
					pDM_DigTable->ForbiddenIGI--;
					pDM_DigTable->rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 1);
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): Normal Case: Approach Lower Bound\n", __func__));
				पूर्ण
			पूर्ण अन्यथा अणु
				pDM_DigTable->LargeFAHit = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
		     ("%s(): pDM_DigTable->LargeFAHit=%d\n",
		      __func__, pDM_DigTable->LargeFAHit));

	/* 1 Adjust initial gain by false alarm */
	अगर (pDM_Odm->bLinked) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): DIG AfterLink\n", __func__));
		अगर (FirstConnect) अणु
			CurrentIGI = pDM_Odm->RSSI_Min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("DIG: First Connect\n"));
		पूर्ण अन्यथा अणु
			अगर (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH2)
				CurrentIGI = CurrentIGI + 4;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+2; */
			अन्यथा अगर (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH1)
				CurrentIGI = CurrentIGI + 2;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+1; */
			अन्यथा अगर (pFalseAlmCnt->Cnt_all < DM_DIG_FA_TH0)
				CurrentIGI = CurrentIGI - 2;/* pDM_DigTable->CurIGValue =pDM_DigTable->PreIGValue-1; */
		पूर्ण
	पूर्ण अन्यथा अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): DIG BeforeLink\n", __func__));
		अगर (FirstDisConnect) अणु
			CurrentIGI = pDM_DigTable->rx_gain_range_min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): First DisConnect\n", __func__));
		पूर्ण अन्यथा अणु
			/* 2012.03.30 LukeLee: enable DIG beक्रमe link but with very high thresholds */
			अगर (pFalseAlmCnt->Cnt_all > 10000)
				CurrentIGI = CurrentIGI + 2;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+2; */
			अन्यथा अगर (pFalseAlmCnt->Cnt_all > 8000)
				CurrentIGI = CurrentIGI + 1;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+1; */
			अन्यथा अगर (pFalseAlmCnt->Cnt_all < 500)
				CurrentIGI = CurrentIGI - 1;/* pDM_DigTable->CurIGValue =pDM_DigTable->PreIGValue-1; */
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): England DIG\n", __func__));
		पूर्ण
	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): DIG End Adjust IGI\n", __func__));
	/* 1 Check initial gain by upper/lower bound */
	अगर (CurrentIGI > pDM_DigTable->rx_gain_range_max)
		CurrentIGI = pDM_DigTable->rx_gain_range_max;
	अगर (CurrentIGI < pDM_DigTable->rx_gain_range_min)
		CurrentIGI = pDM_DigTable->rx_gain_range_min;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
		     ("%s(): rx_gain_range_max=0x%x, rx_gain_range_min=0x%x\n",
		      __func__, pDM_DigTable->rx_gain_range_max, pDM_DigTable->rx_gain_range_min));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): TotalFA=%d\n", __func__, pFalseAlmCnt->Cnt_all));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("%s(): CurIGValue=0x%x\n", __func__, CurrentIGI));

	/* 2 High घातer RSSI threshold */

	ODM_Write_DIG(pDM_Odm, CurrentIGI);/* ODM_Write_DIG(pDM_Odm, pDM_DigTable->CurIGValue); */
	pDM_DigTable->bMediaConnect_0 = pDM_Odm->bLinked;
	pDM_DigTable->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
पूर्ण

/* 3============================================================ */
/* 3 FASLE ALARM CHECK */
/* 3============================================================ */

व्योम odm_FalseAlarmCounterStatistics(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *adapter = pDM_Odm->Adapter;
	u32 ret_value;
	काष्ठा false_alarm_stats *FalseAlmCnt = &pDM_Odm->FalseAlmCnt;

	अगर (!(pDM_Odm->SupportAbility & ODM_BB_FA_CNT))
		वापस;

	/* hold ofdm counter */
	phy_set_bb_reg(adapter, ODM_REG_OFDM_FA_HOLDC_11N, BIT(31), 1); /* hold page C counter */
	phy_set_bb_reg(adapter, ODM_REG_OFDM_FA_RSTD_11N, BIT(31), 1); /* hold page D counter */

	ret_value = phy_query_bb_reg(adapter, ODM_REG_OFDM_FA_TYPE1_11N, bMaskDWord);
	FalseAlmCnt->Cnt_Fast_Fsync = (ret_value & 0xffff);
	FalseAlmCnt->Cnt_SB_Search_fail = (ret_value & 0xffff0000) >> 16;
	ret_value = phy_query_bb_reg(adapter, ODM_REG_OFDM_FA_TYPE2_11N, bMaskDWord);
	FalseAlmCnt->Cnt_OFDM_CCA = (ret_value & 0xffff);
	FalseAlmCnt->Cnt_Parity_Fail = (ret_value & 0xffff0000) >> 16;
	ret_value = phy_query_bb_reg(adapter, ODM_REG_OFDM_FA_TYPE3_11N, bMaskDWord);
	FalseAlmCnt->Cnt_Rate_Illegal = (ret_value & 0xffff);
	FalseAlmCnt->Cnt_Crc8_fail = (ret_value & 0xffff0000) >> 16;
	ret_value = phy_query_bb_reg(adapter, ODM_REG_OFDM_FA_TYPE4_11N, bMaskDWord);
	FalseAlmCnt->Cnt_Mcs_fail = (ret_value & 0xffff);

	FalseAlmCnt->Cnt_Ofdm_fail = FalseAlmCnt->Cnt_Parity_Fail + FalseAlmCnt->Cnt_Rate_Illegal +
				     FalseAlmCnt->Cnt_Crc8_fail + FalseAlmCnt->Cnt_Mcs_fail +
				     FalseAlmCnt->Cnt_Fast_Fsync + FalseAlmCnt->Cnt_SB_Search_fail;

	ret_value = phy_query_bb_reg(adapter, ODM_REG_SC_CNT_11N, bMaskDWord);
	FalseAlmCnt->Cnt_BW_LSC = (ret_value & 0xffff);
	FalseAlmCnt->Cnt_BW_USC = (ret_value & 0xffff0000) >> 16;

	/* hold cck counter */
	phy_set_bb_reg(adapter, ODM_REG_CCK_FA_RST_11N, BIT(12), 1);
	phy_set_bb_reg(adapter, ODM_REG_CCK_FA_RST_11N, BIT(14), 1);

	ret_value = phy_query_bb_reg(adapter, ODM_REG_CCK_FA_LSB_11N, bMaskByte0);
	FalseAlmCnt->Cnt_Cck_fail = ret_value;
	ret_value = phy_query_bb_reg(adapter, ODM_REG_CCK_FA_MSB_11N, bMaskByte3);
	FalseAlmCnt->Cnt_Cck_fail +=  (ret_value & 0xff) << 8;

	ret_value = phy_query_bb_reg(adapter, ODM_REG_CCK_CCA_CNT_11N, bMaskDWord);
	FalseAlmCnt->Cnt_CCK_CCA = ((ret_value & 0xFF) << 8) | ((ret_value & 0xFF00) >> 8);

	FalseAlmCnt->Cnt_all = (FalseAlmCnt->Cnt_Fast_Fsync +
				FalseAlmCnt->Cnt_SB_Search_fail +
				FalseAlmCnt->Cnt_Parity_Fail +
				FalseAlmCnt->Cnt_Rate_Illegal +
				FalseAlmCnt->Cnt_Crc8_fail +
				FalseAlmCnt->Cnt_Mcs_fail +
				FalseAlmCnt->Cnt_Cck_fail);

	FalseAlmCnt->Cnt_CCA_all = FalseAlmCnt->Cnt_OFDM_CCA + FalseAlmCnt->Cnt_CCK_CCA;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD, ("Enter %s\n", __func__));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD,
		     ("Cnt_Fast_Fsync=%d, Cnt_SB_Search_fail=%d\n",
		     FalseAlmCnt->Cnt_Fast_Fsync, FalseAlmCnt->Cnt_SB_Search_fail));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD,
		     ("Cnt_Parity_Fail=%d, Cnt_Rate_Illegal=%d\n",
		     FalseAlmCnt->Cnt_Parity_Fail, FalseAlmCnt->Cnt_Rate_Illegal));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD,
		     ("Cnt_Crc8_fail=%d, Cnt_Mcs_fail=%d\n",
		     FalseAlmCnt->Cnt_Crc8_fail, FalseAlmCnt->Cnt_Mcs_fail));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD, ("Cnt_Cck_fail=%d\n", FalseAlmCnt->Cnt_Cck_fail));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD, ("Cnt_Ofdm_fail=%d\n", FalseAlmCnt->Cnt_Ofdm_fail));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_FA_CNT, ODM_DBG_LOUD, ("Total False Alarm=%d\n", FalseAlmCnt->Cnt_all));
पूर्ण

/* 3============================================================ */
/* 3 CCK Packet Detect Threshold */
/* 3============================================================ */

व्योम odm_CCKPacketDetectionThresh(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	u8 CurCCK_CCAThres;
	काष्ठा false_alarm_stats *FalseAlmCnt = &pDM_Odm->FalseAlmCnt;

	अगर (!(pDM_Odm->SupportAbility & (ODM_BB_CCK_PD | ODM_BB_FA_CNT)))
		वापस;
	अगर (pDM_Odm->ExtLNA)
		वापस;
	अगर (pDM_Odm->bLinked) अणु
		अगर (pDM_Odm->RSSI_Min > 25) अणु
			CurCCK_CCAThres = 0xcd;
		पूर्ण अन्यथा अगर (pDM_Odm->RSSI_Min > 10) अणु
			CurCCK_CCAThres = 0x83;
		पूर्ण अन्यथा अणु
			अगर (FalseAlmCnt->Cnt_Cck_fail > 1000)
				CurCCK_CCAThres = 0x83;
			अन्यथा
				CurCCK_CCAThres = 0x40;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (FalseAlmCnt->Cnt_Cck_fail > 1000)
			CurCCK_CCAThres = 0x83;
		अन्यथा
			CurCCK_CCAThres = 0x40;
	पूर्ण
	ODM_Write_CCK_CCA_Thres(pDM_Odm, CurCCK_CCAThres);
पूर्ण

व्योम ODM_Write_CCK_CCA_Thres(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 CurCCK_CCAThres)
अणु
	काष्ठा rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	काष्ठा adapter *adapt = pDM_Odm->Adapter;

	अगर (pDM_DigTable->CurCCK_CCAThres != CurCCK_CCAThres)		/* modअगरy by Guo.Mingzhi 2012-01-03 */
		usb_ग_लिखो8(adapt, ODM_REG_CCK_CCA_11N, CurCCK_CCAThres);
	pDM_DigTable->PreCCK_CCAThres = pDM_DigTable->CurCCK_CCAThres;
	pDM_DigTable->CurCCK_CCAThres = CurCCK_CCAThres;
पूर्ण

व्योम ODM_RF_Saving(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 bForceInNormal)
अणु
	काष्ठा adapter *adapter = pDM_Odm->Adapter;
	काष्ठा rtl_ps *pDM_PSTable = &pDM_Odm->DM_PSTable;
	u8 Rssi_Up_bound = 30;
	u8 Rssi_Low_bound = 25;

	अगर (pDM_Odm->PatchID == 40) अणु /* RT_CID_819x_FUNAI_TV */
		Rssi_Up_bound = 50;
		Rssi_Low_bound = 45;
	पूर्ण
	अगर (pDM_PSTable->initialize == 0) अणु
		pDM_PSTable->Reg874 = (phy_query_bb_reg(adapter, 0x874, bMaskDWord) & 0x1CC000) >> 14;
		pDM_PSTable->RegC70 = (phy_query_bb_reg(adapter, 0xc70, bMaskDWord) & BIT(3)) >> 3;
		pDM_PSTable->Reg85C = (phy_query_bb_reg(adapter, 0x85c, bMaskDWord) & 0xFF000000) >> 24;
		pDM_PSTable->RegA74 = (phy_query_bb_reg(adapter, 0xa74, bMaskDWord) & 0xF000) >> 12;
		pDM_PSTable->initialize = 1;
	पूर्ण

	अगर (!bForceInNormal) अणु
		अगर (pDM_Odm->RSSI_Min != 0xFF) अणु
			अगर (pDM_PSTable->PreRFState == RF_Normal) अणु
				अगर (pDM_Odm->RSSI_Min >= Rssi_Up_bound)
					pDM_PSTable->CurRFState = RF_Save;
				अन्यथा
					pDM_PSTable->CurRFState = RF_Normal;
			पूर्ण अन्यथा अणु
				अगर (pDM_Odm->RSSI_Min <= Rssi_Low_bound)
					pDM_PSTable->CurRFState = RF_Normal;
				अन्यथा
					pDM_PSTable->CurRFState = RF_Save;
			पूर्ण
		पूर्ण अन्यथा अणु
			pDM_PSTable->CurRFState = RF_MAX;
		पूर्ण
	पूर्ण अन्यथा अणु
		pDM_PSTable->CurRFState = RF_Normal;
	पूर्ण

	अगर (pDM_PSTable->PreRFState != pDM_PSTable->CurRFState) अणु
		अगर (pDM_PSTable->CurRFState == RF_Save) अणु
			phy_set_bb_reg(adapter, 0x874, 0x1C0000, 0x2); /* Reg874[20:18]=3'b010 */
			phy_set_bb_reg(adapter, 0xc70, BIT(3), 0); /* RegC70[3]=1'b0 */
			phy_set_bb_reg(adapter, 0x85c, 0xFF000000, 0x63); /* Reg85C[31:24]=0x63 */
			phy_set_bb_reg(adapter, 0x874, 0xC000, 0x2); /* Reg874[15:14]=2'b10 */
			phy_set_bb_reg(adapter, 0xa74, 0xF000, 0x3); /* RegA75[7:4]=0x3 */
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x0); /* Reg818[28]=1'b0 */
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x1); /* Reg818[28]=1'b1 */
		पूर्ण अन्यथा अणु
			phy_set_bb_reg(adapter, 0x874, 0x1CC000, pDM_PSTable->Reg874);
			phy_set_bb_reg(adapter, 0xc70, BIT(3), pDM_PSTable->RegC70);
			phy_set_bb_reg(adapter, 0x85c, 0xFF000000, pDM_PSTable->Reg85C);
			phy_set_bb_reg(adapter, 0xa74, 0xF000, pDM_PSTable->RegA74);
			phy_set_bb_reg(adapter, 0x818, BIT(28), 0x0);
		पूर्ण
		pDM_PSTable->PreRFState = pDM_PSTable->CurRFState;
	पूर्ण
पूर्ण

/* 3============================================================ */
/* 3 RATR MASK */
/* 3============================================================ */
/* 3============================================================ */
/* 3 Rate Adaptive */
/* 3============================================================ */

व्योम odm_RateAdaptiveMaskInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा odm_rate_adapt *pOdmRA = &pDM_Odm->RateAdaptive;

	pOdmRA->Type = DM_Type_ByDriver;
	अगर (pOdmRA->Type == DM_Type_ByDriver)
		pDM_Odm->bUseRAMask = true;
	अन्यथा
		pDM_Odm->bUseRAMask = false;

	pOdmRA->RATRState = DM_RATR_STA_INIT;
	pOdmRA->HighRSSIThresh = 50;
	pOdmRA->LowRSSIThresh = 20;
पूर्ण

u32 ODM_Get_Rate_Biपंचांगap(काष्ठा odm_dm_काष्ठा *pDM_Odm, u32 macid, u32 ra_mask, u8 rssi_level)
अणु
	काष्ठा sta_info *pEntry;
	u32 rate_biपंचांगap = 0x0fffffff;
	u8 WirelessMode;

	pEntry = pDM_Odm->pODM_StaInfo[macid];
	अगर (!IS_STA_VALID(pEntry))
		वापस ra_mask;

	WirelessMode = pEntry->wireless_mode;

	चयन (WirelessMode) अणु
	हाल ODM_WM_B:
		अगर (ra_mask & 0x0000000c)		/* 11M or 5.5M enable */
			rate_biपंचांगap = 0x0000000d;
		अन्यथा
			rate_biपंचांगap = 0x0000000f;
		अवरोध;
	हाल (ODM_WM_A | ODM_WM_G):
		अगर (rssi_level == DM_RATR_STA_HIGH)
			rate_biपंचांगap = 0x00000f00;
		अन्यथा
			rate_biपंचांगap = 0x00000ff0;
		अवरोध;
	हाल (ODM_WM_B | ODM_WM_G):
		अगर (rssi_level == DM_RATR_STA_HIGH)
			rate_biपंचांगap = 0x00000f00;
		अन्यथा अगर (rssi_level == DM_RATR_STA_MIDDLE)
			rate_biपंचांगap = 0x00000ff0;
		अन्यथा
			rate_biपंचांगap = 0x00000ff5;
		अवरोध;
	हाल (ODM_WM_B | ODM_WM_G | ODM_WM_N24G):
	हाल (ODM_WM_A | ODM_WM_B | ODM_WM_G | ODM_WM_N24G):
		अगर (rssi_level == DM_RATR_STA_HIGH) अणु
			rate_biपंचांगap = 0x000f0000;
		पूर्ण अन्यथा अगर (rssi_level == DM_RATR_STA_MIDDLE) अणु
			rate_biपंचांगap = 0x000ff000;
		पूर्ण अन्यथा अणु
			अगर (*pDM_Odm->pBandWidth == ODM_BW40M)
				rate_biपंचांगap = 0x000ff015;
			अन्यथा
				rate_biपंचांगap = 0x000ff005;
		पूर्ण
		अवरोध;
	शेष:
		/* हाल WIRELESS_11_24N: */
		/* हाल WIRELESS_11_5N: */
		rate_biपंचांगap = 0x0fffffff;
		अवरोध;
	पूर्ण

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD,
		     (" ==> rssi_level:0x%02x, WirelessMode:0x%02x, rate_bitmap:0x%08x\n",
		     rssi_level, WirelessMode, rate_biपंचांगap));

	वापस rate_biपंचांगap;
पूर्ण

/* Update rate table mask according to rssi */
व्योम odm_RefreshRateAdaptiveMask(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_RA_MASK))
		वापस;
	/*  */
	/*  2011/09/29 MH In HW पूर्णांकegration first stage, we provide 4 dअगरferent handle to operate */
	/*  at the same समय. In the stage2/3, we need to prive universal पूर्णांकerface and merge all */
	/*  HW dynamic mechanism. */
	/*  */
	odm_RefreshRateAdaptiveMaskCE(pDM_Odm);
पूर्ण

व्योम odm_RefreshRateAdaptiveMaskCE(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	u8 i;
	काष्ठा adapter *pAdapter = pDM_Odm->Adapter;

	अगर (pAdapter->bDriverStopped) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_TRACE, ("<---- odm_RefreshRateAdaptiveMask(): driver is going to unload\n"));
		वापस;
	पूर्ण

	अगर (!pDM_Odm->bUseRAMask) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("<---- odm_RefreshRateAdaptiveMask(): driver does not control rate adaptive mask\n"));
		वापस;
	पूर्ण

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		काष्ठा sta_info *pstat = pDM_Odm->pODM_StaInfo[i];

		अगर (IS_STA_VALID(pstat)) अणु
			अगर (ODM_RAStateCheck(pDM_Odm, pstat->rssi_stat.UndecoratedSmoothedPWDB, false, &pstat->rssi_level)) अणु
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD,
					     ("RSSI:%d, RSSI_LEVEL:%d\n",
					     pstat->rssi_stat.UndecoratedSmoothedPWDB, pstat->rssi_level));
				rtw_hal_update_ra_mask(pAdapter, i, pstat->rssi_level);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*  Return Value: bool */
/*  - true: RATRState is changed. */
bool ODM_RAStateCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm, s32 RSSI, bool bForceUpdate, u8 *pRATRState)
अणु
	काष्ठा odm_rate_adapt *pRA = &pDM_Odm->RateAdaptive;
	स्थिर u8 GoUpGap = 5;
	u8 HighRSSIThreshForRA = pRA->HighRSSIThresh;
	u8 LowRSSIThreshForRA = pRA->LowRSSIThresh;
	u8 RATRState;

	/*  Threshold Adjusपंचांगent: */
	/*  when RSSI state trends to go up one or two levels, make sure RSSI is high enough. */
	/*  Here GoUpGap is added to solve the boundary's level alternation issue. */
	चयन (*pRATRState) अणु
	हाल DM_RATR_STA_INIT:
	हाल DM_RATR_STA_HIGH:
		अवरोध;
	हाल DM_RATR_STA_MIDDLE:
		HighRSSIThreshForRA += GoUpGap;
		अवरोध;
	हाल DM_RATR_STA_LOW:
		HighRSSIThreshForRA += GoUpGap;
		LowRSSIThreshForRA += GoUpGap;
		अवरोध;
	शेष:
		ODM_RT_ASSERT(pDM_Odm, false, ("wrong rssi level setting %d !", *pRATRState));
		अवरोध;
	पूर्ण

	/*  Decide RATRState by RSSI. */
	अगर (HighRSSIThreshForRA < RSSI)
		RATRState = DM_RATR_STA_HIGH;
	अन्यथा अगर (LowRSSIThreshForRA < RSSI)
		RATRState = DM_RATR_STA_MIDDLE;
	अन्यथा
		RATRState = DM_RATR_STA_LOW;

	अगर (*pRATRState != RATRState || bForceUpdate) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("RSSI Level %d -> %d\n", *pRATRState, RATRState));
		*pRATRState = RATRState;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* 3============================================================ */
/* 3 Dynamic Tx Power */
/* 3============================================================ */

व्योम odm_DynamicTxPowerInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा dm_priv	*pdmpriv = &Adapter->HalData->dmpriv;

	pdmpriv->bDynamicTxPowerEnable = false;
	pdmpriv->LastDTPLvl = TxHighPwrLevel_Normal;
	pdmpriv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
पूर्ण

/* 3============================================================ */
/* 3 RSSI Monitor */
/* 3============================================================ */

व्योम odm_RSSIMonitorCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_RSSI_MONITOR))
		वापस;

	/*  */
	/*  2011/09/29 MH In HW पूर्णांकegration first stage, we provide 4 dअगरferent handle to operate */
	/*  at the same समय. In the stage2/3, we need to prive universal पूर्णांकerface and merge all */
	/*  HW dynamic mechanism. */
	/*  */
	odm_RSSIMonitorCheckCE(pDM_Odm);
पूर्ण	/*  odm_RSSIMonitorCheck */

अटल व्योम FindMinimumRSSI(काष्ठा adapter *pAdapter)
अणु
	काष्ठा dm_priv	*pdmpriv = &pAdapter->HalData->dmpriv;

	/* 1 1.Unconditionally set RSSI */
	pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;
पूर्ण

व्योम odm_RSSIMonitorCheckCE(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा dm_priv	*pdmpriv = &Adapter->HalData->dmpriv;
	पूर्णांक	i;
	पूर्णांक	पंचांगpEntryMaxPWDB = 0, पंचांगpEntryMinPWDB = 0xff;
	u8	sta_cnt = 0;
	u32 PWDB_rssi[NUM_STA] = अणु0पूर्ण;/* 0~15]:MACID, [16~31]:PWDB_rssi */
	काष्ठा sta_info *psta;
	u8 bcast_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	अगर (!check_fwstate(&Adapter->mlmepriv, _FW_LINKED))
		वापस;

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		psta = pDM_Odm->pODM_StaInfo[i];
		अगर (IS_STA_VALID(psta) &&
		    (psta->state & WIFI_ASOC_STATE) &&
		    स_भेद(psta->hwaddr, bcast_addr, ETH_ALEN) &&
		    स_भेद(psta->hwaddr, myid(&Adapter->eeprompriv), ETH_ALEN)) अणु
			अगर (psta->rssi_stat.UndecoratedSmoothedPWDB < पंचांगpEntryMinPWDB)
				पंचांगpEntryMinPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

			अगर (psta->rssi_stat.UndecoratedSmoothedPWDB > पंचांगpEntryMaxPWDB)
				पंचांगpEntryMaxPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;
			अगर (psta->rssi_stat.UndecoratedSmoothedPWDB != (-1))
				PWDB_rssi[sta_cnt++] = (psta->mac_id | (psta->rssi_stat.UndecoratedSmoothedPWDB << 16));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sta_cnt; i++) अणु
		अगर (PWDB_rssi[i] != 0) अणु
			ODM_RA_SetRSSI_8188E(&Adapter->HalData->odmpriv,
					     PWDB_rssi[i] & 0xFF,
					     (PWDB_rssi[i] >> 16) & 0xFF);
		पूर्ण
	पूर्ण

	अगर (पंचांगpEntryMaxPWDB != 0)	/*  If associated entry is found */
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = पंचांगpEntryMaxPWDB;
	अन्यथा
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = 0;

	अगर (पंचांगpEntryMinPWDB != 0xff) /*  If associated entry is found */
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = पंचांगpEntryMinPWDB;
	अन्यथा
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = 0;

	FindMinimumRSSI(Adapter);
	Adapter->HalData->odmpriv.RSSI_Min = pdmpriv->MinUndecoratedPWDBForDM;
पूर्ण

/* 3============================================================ */
/* 3 Tx Power Tracking */
/* 3============================================================ */

व्योम odm_TXPowerTrackingInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	pDM_Odm->RFCalibrateInfo.bTXPowerTracking = true;
	pDM_Odm->RFCalibrateInfo.TXPowercount = 0;
	अगर (*pDM_Odm->mp_mode != 1)
		pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true;
	MSG_88E("pDM_Odm TxPowerTrackControl = %d\n", pDM_Odm->RFCalibrateInfo.TxPowerTrackControl);

	pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true;
पूर्ण

व्योम ODM_TXPowerTrackingCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	/*  2011/09/29 MH In HW पूर्णांकegration first stage, we provide 4 dअगरferent handle to operate */
	/*  at the same समय. In the stage2/3, we need to prive universal पूर्णांकerface and merge all */
	/*  HW dynamic mechanism. */
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;

	अगर (!(pDM_Odm->SupportAbility & ODM_RF_TX_PWR_TRACK))
		वापस;

	अगर (!pDM_Odm->RFCalibrateInfo.TM_Trigger) अणु		/* at least delay 1 sec */
		phy_set_rf_reg(Adapter, RF_PATH_A, RF_T_METER_88E, BIT(17) | BIT(16), 0x03);

		pDM_Odm->RFCalibrateInfo.TM_Trigger = 1;
		वापस;
	पूर्ण

	rtl88eu_dm_txघातer_tracking_callback_thermalmeter(Adapter);
	pDM_Odm->RFCalibrateInfo.TM_Trigger = 0;
पूर्ण

/* 3============================================================ */
/* 3 SW Antenna Diversity */
/* 3============================================================ */

व्योम odm_InitHybridAntDiv(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_ANT_DIV)) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD, ("Return: Not Support HW AntDiv\n"));
		वापस;
	पूर्ण

	rtl88eu_dm_antenna_भाग_init(pDM_Odm);
पूर्ण

व्योम odm_HwAntDiv(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_ANT_DIV)) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD, ("Return: Not Support HW AntDiv\n"));
		वापस;
	पूर्ण

	rtl88eu_dm_antenna_भागersity(pDM_Odm);
पूर्ण

/* EDCA Turbo */
व्योम ODM_EdcaTurboInit(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;

	pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
	pDM_Odm->DM_EDCA_Table.bIsCurRDLState = false;
	Adapter->recvpriv.bIsAnyNonBEPkts = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original VO PARAM: 0x%x\n", usb_पढ़ो32(Adapter, ODM_EDCA_VO_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original VI PARAM: 0x%x\n", usb_पढ़ो32(Adapter, ODM_EDCA_VI_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original BE PARAM: 0x%x\n", usb_पढ़ो32(Adapter, ODM_EDCA_BE_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original BK PARAM: 0x%x\n", usb_पढ़ो32(Adapter, ODM_EDCA_BK_PARAM)));
पूर्ण	/*  ODM_InitEdcaTurbo */

व्योम odm_EdcaTurboCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	/*  2011/09/29 MH In HW पूर्णांकegration first stage, we provide 4 dअगरferent handle to operate */
	/*  at the same समय. In the stage2/3, we need to prive universal पूर्णांकerface and merge all */
	/*  HW dynamic mechanism. */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("%s========================>\n", __func__));

	अगर (!(pDM_Odm->SupportAbility & ODM_MAC_EDCA_TURBO))
		वापस;

	odm_EdcaTurboCheckCE(pDM_Odm);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("<========================%s\n", __func__));
पूर्ण	/*  odm_CheckEdcaTurbo */

व्योम odm_EdcaTurboCheckCE(काष्ठा odm_dm_काष्ठा *pDM_Odm)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	u32	trafficIndex;
	u32	edca_param;
	u64	cur_tx_bytes = 0;
	u64	cur_rx_bytes = 0;
	u8	bbtchange = false;
	काष्ठा xmit_priv		*pxmitpriv = &Adapter->xmitpriv;
	काष्ठा recv_priv		*precvpriv = &Adapter->recvpriv;
	काष्ठा registry_priv	*pregpriv = &Adapter->registrypriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &Adapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pregpriv->wअगरi_spec == 1) /*  (pmlmeinfo->HT_enable == 0)) */
		जाओ dm_CheckEdcaTurbo_EXIT;

	अगर (pmlmeinfo->assoc_AP_venकरोr >=  HT_IOT_PEER_MAX)
		जाओ dm_CheckEdcaTurbo_EXIT;

	/*  Check अगर the status needs to be changed. */
	अगर ((bbtchange) || (!precvpriv->bIsAnyNonBEPkts)) अणु
		cur_tx_bytes = pxmitpriv->tx_bytes - pxmitpriv->last_tx_bytes;
		cur_rx_bytes = precvpriv->rx_bytes - precvpriv->last_rx_bytes;

		/* traffic, TX or RX */
		अगर ((pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_RALINK) ||
		    (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_ATHEROS)) अणु
			अगर (cur_tx_bytes > (cur_rx_bytes << 2)) अणु
				/*  Uplink TP is present. */
				trafficIndex = UP_LINK;
			पूर्ण अन्यथा अणु
				/*  Balance TP is present. */
				trafficIndex = DOWN_LINK;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cur_rx_bytes > (cur_tx_bytes << 2)) अणु
				/*  Downlink TP is present. */
				trafficIndex = DOWN_LINK;
			पूर्ण अन्यथा अणु
				/*  Balance TP is present. */
				trafficIndex = UP_LINK;
			पूर्ण
		पूर्ण

		अगर ((pDM_Odm->DM_EDCA_Table.prv_traffic_idx != trafficIndex) || (!pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA)) अणु
			अगर ((pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_CISCO) && (pmlmeext->cur_wireless_mode & WIRELESS_11_24N))
				edca_param = EDCAParam[pmlmeinfo->assoc_AP_venकरोr][trafficIndex];
			अन्यथा
				edca_param = EDCAParam[HT_IOT_PEER_UNKNOWN][trafficIndex];

			usb_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM, edca_param);

			pDM_Odm->DM_EDCA_Table.prv_traffic_idx = trafficIndex;
		पूर्ण

		pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = true;
	पूर्ण अन्यथा अणु
		/*  Turn Off EDCA turbo here. */
		/*  Restore original EDCA according to the declaration of AP. */
		अगर (pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA) अणु
			usb_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM,
				    Adapter->HalData->AcParam_BE);
			pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
		पूर्ण
	पूर्ण

dm_CheckEdcaTurbo_EXIT:
	/*  Set variables क्रम next समय. */
	precvpriv->bIsAnyNonBEPkts = false;
	pxmitpriv->last_tx_bytes = pxmitpriv->tx_bytes;
	precvpriv->last_rx_bytes = precvpriv->rx_bytes;
पूर्ण
