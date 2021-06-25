<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

अटल व्योम odm_SetCrystalCap(व्योम *pDM_VOID, u8 CrystalCap)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;

	अगर (pCfoTrack->CrystalCap == CrystalCap)
		वापस;

	pCfoTrack->CrystalCap = CrystalCap;

	/*  0x2C[23:18] = 0x2C[17:12] = CrystalCap */
	CrystalCap = CrystalCap & 0x3F;
	PHY_SetBBReg(
		pDM_Odm->Adapter,
		REG_MAC_PHY_CTRL,
		0x00FFF000,
		(CrystalCap | (CrystalCap << 6))
	);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		(
			"odm_SetCrystalCap(): CrystalCap = 0x%x\n",
			CrystalCap
		)
	);
पूर्ण

अटल u8 odm_GetDefaultCrytaltalCap(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	वापस pHalData->CrystalCap & 0x3f;
पूर्ण

अटल व्योम odm_SetATCStatus(व्योम *pDM_VOID, bool ATCStatus)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;

	अगर (pCfoTrack->bATCStatus == ATCStatus)
		वापस;

	PHY_SetBBReg(
		pDM_Odm->Adapter,
		ODM_REG(BB_ATC, pDM_Odm),
		ODM_BIT(BB_ATC, pDM_Odm),
		ATCStatus
	);
	pCfoTrack->bATCStatus = ATCStatus;
पूर्ण

अटल bool odm_GetATCStatus(व्योम *pDM_VOID)
अणु
	bool ATCStatus;
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	ATCStatus = (bool)PHY_QueryBBReg(
		pDM_Odm->Adapter,
		ODM_REG(BB_ATC, pDM_Odm),
		ODM_BIT(BB_ATC, pDM_Odm)
	);
	वापस ATCStatus;
पूर्ण

व्योम ODM_CfoTrackingReset(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;

	pCfoTrack->DefXCap = odm_GetDefaultCrytaltalCap(pDM_Odm);
	pCfoTrack->bAdjust = true;

	odm_SetCrystalCap(pDM_Odm, pCfoTrack->DefXCap);
	odm_SetATCStatus(pDM_Odm, true);
पूर्ण

व्योम ODM_CfoTrackingInit(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;

	pCfoTrack->DefXCap =
		pCfoTrack->CrystalCap = odm_GetDefaultCrytaltalCap(pDM_Odm);
	pCfoTrack->bATCStatus = odm_GetATCStatus(pDM_Odm);
	pCfoTrack->bAdjust = true;
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		("ODM_CfoTracking_init() =========>\n")
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		(
			"ODM_CfoTracking_init(): bATCStatus = %d, CrystalCap = 0x%x\n",
			pCfoTrack->bATCStatus,
			pCfoTrack->DefXCap
		)
	);
पूर्ण

व्योम ODM_CfoTracking(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;
	पूर्णांक CFO_kHz_A, CFO_kHz_B, CFO_ave = 0;
	पूर्णांक CFO_ave_dअगरf;
	पूर्णांक CrystalCap = (पूर्णांक)pCfoTrack->CrystalCap;
	u8 Adjust_Xtal = 1;

	/* 4 Support ability */
	अगर (!(pDM_Odm->SupportAbility & ODM_BB_CFO_TRACKING)) अणु
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_CFO_TRACKING,
			ODM_DBG_LOUD,
			("ODM_CfoTracking(): Return: SupportAbility ODM_BB_CFO_TRACKING is disabled\n")
		);
		वापस;
	पूर्ण

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		("ODM_CfoTracking() =========>\n")
	);

	अगर (!pDM_Odm->bLinked || !pDM_Odm->bOneEntryOnly) अणु
		/* 4 No link or more than one entry */
		ODM_CfoTrackingReset(pDM_Odm);
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_CFO_TRACKING,
			ODM_DBG_LOUD,
			(
				"ODM_CfoTracking(): Reset: bLinked = %d, bOneEntryOnly = %d\n",
				pDM_Odm->bLinked,
				pDM_Odm->bOneEntryOnly
			)
		);
	पूर्ण अन्यथा अणु
		/* 3 1. CFO Tracking */
		/* 4 1.1 No new packet */
		अगर (pCfoTrack->packetCount == pCfoTrack->packetCount_pre) अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_CFO_TRACKING,
				ODM_DBG_LOUD,
				(
					"ODM_CfoTracking(): packet counter doesn't change\n"
				)
			);
			वापस;
		पूर्ण
		pCfoTrack->packetCount_pre = pCfoTrack->packetCount;

		/* 4 1.2 Calculate CFO */
		CFO_kHz_A =  (पूर्णांक)(pCfoTrack->CFO_tail[0] * 3125)  / 1280;
		CFO_kHz_B =  (पूर्णांक)(pCfoTrack->CFO_tail[1] * 3125)  / 1280;

		अगर (pDM_Odm->RFType < ODM_2T2R)
			CFO_ave = CFO_kHz_A;
		अन्यथा
			CFO_ave = (पूर्णांक)(CFO_kHz_A + CFO_kHz_B) >> 1;
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_CFO_TRACKING,
			ODM_DBG_LOUD,
			(
				"ODM_CfoTracking(): CFO_kHz_A = %dkHz, CFO_kHz_B = %dkHz, CFO_ave = %dkHz\n",
				CFO_kHz_A,
				CFO_kHz_B,
				CFO_ave
			)
		);

		/* 4 1.3 Aव्योम abnormal large CFO */
		CFO_ave_dअगरf =
			(pCfoTrack->CFO_ave_pre >= CFO_ave) ?
			(pCfoTrack->CFO_ave_pre-CFO_ave) :
			(CFO_ave-pCfoTrack->CFO_ave_pre);

		अगर (
			CFO_ave_dअगरf > 20 &&
			pCfoTrack->largeCFOHit == 0 &&
			!pCfoTrack->bAdjust
		) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CFO_TRACKING, ODM_DBG_LOUD, ("ODM_CfoTracking(): first large CFO hit\n"));
			pCfoTrack->largeCFOHit = 1;
			वापस;
		पूर्ण अन्यथा
			pCfoTrack->largeCFOHit = 0;
		pCfoTrack->CFO_ave_pre = CFO_ave;

		/* 4 1.4 Dynamic Xtal threshold */
		अगर (pCfoTrack->bAdjust == false) अणु
			अगर (CFO_ave > CFO_TH_XTAL_HIGH || CFO_ave < (-CFO_TH_XTAL_HIGH))
				pCfoTrack->bAdjust = true;
		पूर्ण अन्यथा अणु
			अगर (CFO_ave < CFO_TH_XTAL_LOW && CFO_ave > (-CFO_TH_XTAL_LOW))
				pCfoTrack->bAdjust = false;
		पूर्ण

		/* 4 1.5 BT हाल: Disable CFO tracking */
		अगर (pDM_Odm->bBtEnabled) अणु
			pCfoTrack->bAdjust = false;
			odm_SetCrystalCap(pDM_Odm, pCfoTrack->DefXCap);
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_CFO_TRACKING,
				ODM_DBG_LOUD,
				("ODM_CfoTracking(): Disable CFO tracking for BT!!\n")
			);
		पूर्ण

		/* 4 1.6 Big jump */
		अगर (pCfoTrack->bAdjust) अणु
			अगर (CFO_ave > CFO_TH_XTAL_LOW)
				Adjust_Xtal = Adjust_Xtal+((CFO_ave-CFO_TH_XTAL_LOW)>>2);
			अन्यथा अगर (CFO_ave < (-CFO_TH_XTAL_LOW))
				Adjust_Xtal = Adjust_Xtal+((CFO_TH_XTAL_LOW-CFO_ave)>>2);

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_CFO_TRACKING,
				ODM_DBG_LOUD,
				(
					"ODM_CfoTracking(): Crystal cap offset = %d\n",
					Adjust_Xtal
				)
			);
		पूर्ण

		/* 4 1.7 Adjust Crystal Cap. */
		अगर (pCfoTrack->bAdjust) अणु
			अगर (CFO_ave > CFO_TH_XTAL_LOW)
				CrystalCap = CrystalCap + Adjust_Xtal;
			अन्यथा अगर (CFO_ave < (-CFO_TH_XTAL_LOW))
				CrystalCap = CrystalCap - Adjust_Xtal;

			अगर (CrystalCap > 0x3f)
				CrystalCap = 0x3f;
			अन्यथा अगर (CrystalCap < 0)
				CrystalCap = 0;

			odm_SetCrystalCap(pDM_Odm, (u8)CrystalCap);
		पूर्ण
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_CFO_TRACKING,
			ODM_DBG_LOUD,
			(
				"ODM_CfoTracking(): Crystal cap = 0x%x, Default Crystal cap = 0x%x\n",
				pCfoTrack->CrystalCap,
				pCfoTrack->DefXCap
			)
		);

		/* 3 2. Dynamic ATC चयन */
		अगर (CFO_ave < CFO_TH_ATC && CFO_ave > -CFO_TH_ATC) अणु
			odm_SetATCStatus(pDM_Odm, false);
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_CFO_TRACKING,
				ODM_DBG_LOUD,
				("ODM_CfoTracking(): Disable ATC!!\n")
			);
		पूर्ण अन्यथा अणु
			odm_SetATCStatus(pDM_Odm, true);
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_CFO_TRACKING,
				ODM_DBG_LOUD,
				("ODM_CfoTracking(): Enable ATC!!\n")
			);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ODM_ParsingCFO(व्योम *pDM_VOID, व्योम *pPktinfo_VOID, s8 *pcfotail)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा odm_packet_info *pPktinfo = pPktinfo_VOID;
	काष्ठा cfo_tracking *pCfoTrack = &pDM_Odm->DM_CfoTrack;
	u8 i;

	अगर (!(pDM_Odm->SupportAbility & ODM_BB_CFO_TRACKING))
		वापस;

	अगर (pPktinfo->station_id != 0) अणु
		/* 3 Update CFO report क्रम path-A & path-B */
		/*  Only paht-A and path-B have CFO tail and लघु CFO */
		क्रम (i = ODM_RF_PATH_A; i <= ODM_RF_PATH_B; i++)
			pCfoTrack->CFO_tail[i] = (पूर्णांक)pcfotail[i];

		/* 3 Update packet counter */
		अगर (pCfoTrack->packetCount == 0xffffffff)
			pCfoTrack->packetCount = 0;
		अन्यथा
			pCfoTrack->packetCount++;
	पूर्ण
पूर्ण
