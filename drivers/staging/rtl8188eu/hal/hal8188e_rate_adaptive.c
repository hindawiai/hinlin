<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) Realtek Semiconductor Corp. All rights reserved.
 */

#समावेश "odm_precomp.h"

/*  Rate adaptive parameters */

अटल u8 RETRY_PENALTY[PERENTRY][RETRYSIZE + 1] = अणु
		अणु5, 4, 3, 2, 0, 3पूर्ण,      /* 92 , idx = 0 */
		अणु6, 5, 4, 3, 0, 4पूर्ण,      /* 86 , idx = 1 */
		अणु6, 5, 4, 2, 0, 4पूर्ण,      /* 81 , idx = 2 */
		अणु8, 7, 6, 4, 0, 6पूर्ण,      /* 75 , idx = 3 */
		अणु10, 9, 8, 6, 0, 8पूर्ण,     /* 71	, idx = 4 */
		अणु10, 9, 8, 4, 0, 8पूर्ण,     /* 66	, idx = 5 */
		अणु10, 9, 8, 2, 0, 8पूर्ण,     /* 62	, idx = 6 */
		अणु10, 9, 8, 0, 0, 8पूर्ण,     /* 59	, idx = 7 */
		अणु18, 17, 16, 8, 0, 16पूर्ण,  /* 53 , idx = 8 */
		अणु26, 25, 24, 16, 0, 24पूर्ण, /* 50	, idx = 9 */
		अणु34, 33, 32, 24, 0, 32पूर्ण, /* 47	, idx = 0x0a */
		अणु34, 31, 28, 20, 0, 32पूर्ण, /* 43	, idx = 0x0b */
		अणु34, 31, 27, 18, 0, 32पूर्ण, /* 40 , idx = 0x0c */
		अणु34, 31, 26, 16, 0, 32पूर्ण, /* 37 , idx = 0x0d */
		अणु34, 30, 22, 16, 0, 32पूर्ण, /* 32 , idx = 0x0e */
		अणु34, 30, 24, 16, 0, 32पूर्ण, /* 26 , idx = 0x0f */
		अणु49, 46, 40, 16, 0, 48पूर्ण, /* 20	, idx = 0x10 */
		अणु49, 45, 32, 0, 0, 48पूर्ण,  /* 17 , idx = 0x11 */
		अणु49, 45, 22, 18, 0, 48पूर्ण, /* 15	, idx = 0x12 */
		अणु49, 40, 24, 16, 0, 48पूर्ण, /* 12	, idx = 0x13 */
		अणु49, 32, 18, 12, 0, 48पूर्ण, /* 9 , idx = 0x14 */
		अणु49, 22, 18, 14, 0, 48पूर्ण, /* 6 , idx = 0x15 */
		अणु49, 16, 16, 0, 0, 48पूर्ण
	पूर्ण; /* 3, idx = 0x16 */

अटल u8 PT_PENALTY[RETRYSIZE + 1] = अणु34, 31, 30, 24, 0, 32पूर्ण;

/*  wilson modअगरy */
अटल u8 RETRY_PENALTY_IDX[2][RATESIZE] = अणु
		अणु4, 4, 4, 5, 4, 4, 5, 7, 7, 7, 8, 0x0a,	       /*  SS>TH */
		4, 4, 4, 4, 6, 0x0a, 0x0b, 0x0d,
		5, 5, 7, 7, 8, 0x0b, 0x0d, 0x0fपूर्ण,			   /*  0329 R01 */
		अणु0x0a, 0x0a, 0x0b, 0x0c, 0x0a,
		0x0a, 0x0b, 0x0c, 0x0d, 0x10, 0x13, 0x14,	   /*  SS<TH */
		0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x11, 0x13, 0x15,
		9, 9, 9, 9, 0x0c, 0x0e, 0x11, 0x13पूर्ण
	पूर्ण;

अटल u8 RETRY_PENALTY_UP_IDX[RATESIZE] = अणु
		0x0c, 0x0d, 0x0d, 0x0f, 0x0d, 0x0e,
		0x0f, 0x0f, 0x10, 0x12, 0x13, 0x14,	       /*  SS>TH */
		0x0f, 0x10, 0x10, 0x12, 0x12, 0x13, 0x14, 0x15,
		0x11, 0x11, 0x12, 0x13, 0x13, 0x13, 0x14, 0x15पूर्ण;

अटल u8 RSSI_THRESHOLD[RATESIZE] = अणु
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0x24, 0x26, 0x2a,
		0x18, 0x1a, 0x1d, 0x1f, 0x21, 0x27, 0x29, 0x2a,
		0, 0, 0, 0x1f, 0x23, 0x28, 0x2a, 0x2cपूर्ण;

अटल u16 N_THRESHOLD_HIGH[RATESIZE] = अणु
		4, 4, 8, 16,
		24, 36, 48, 72, 96, 144, 192, 216,
		60, 80, 100, 160, 240, 400, 560, 640,
		300, 320, 480, 720, 1000, 1200, 1600, 2000पूर्ण;
अटल u16 N_THRESHOLD_LOW[RATESIZE] = अणु
		2, 2, 4, 8,
		12, 18, 24, 36, 48, 72, 96, 108,
		30, 40, 50, 80, 120, 200, 280, 320,
		150, 160, 240, 360, 500, 600, 800, 1000पूर्ण;

अटल u8 DROPING_NECESSARY[RATESIZE] = अणु
		1, 1, 1, 1,
		1, 2, 3, 4, 5, 6, 7, 8,
		1, 2, 3, 4, 5, 6, 7, 8,
		5, 6, 7, 8, 9, 10, 11, 12पूर्ण;

अटल u8 PendingForRateUpFail[5] = अणु2, 10, 24, 40, 60पूर्ण;
अटल u16 DynamicTxRPTTiming[6] = अणु
	0x186a, 0x30d4, 0x493e, 0x61a8, 0x7a12, 0x927cपूर्ण; /*  200ms-1200ms */

/*  End Rate adaptive parameters */

अटल व्योम odm_SetTxRPTTiming_8188E(काष्ठा odm_dm_काष्ठा *dm_odm,
				     काष्ठा odm_ra_info *pRaInfo, u8 extend)
अणु
	u8 idx = 0;

	क्रम (idx = 0; idx < 5; idx++)
		अगर (DynamicTxRPTTiming[idx] == pRaInfo->RptTime)
			अवरोध;

	अगर (extend == 0) अणु /*  back to शेष timing */
		idx = 0;  /* 200ms */
	पूर्ण अन्यथा अगर (extend == 1) अणु/*  increase the timing */
		idx += 1;
		अगर (idx > 5)
			idx = 5;
	पूर्ण अन्यथा अगर (extend == 2) अणु/*  decrease the timing */
		अगर (idx != 0)
			idx -= 1;
	पूर्ण
	pRaInfo->RptTime = DynamicTxRPTTiming[idx];

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("pRaInfo->RptTime = 0x%x\n", pRaInfo->RptTime));
पूर्ण

अटल पूर्णांक odm_RateDown_8188E(काष्ठा odm_dm_काष्ठा *dm_odm,
			      काष्ठा odm_ra_info *pRaInfo)
अणु
	u8 RateID, LowestRate, HighestRate;
	u8 i;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
		     ODM_DBG_TRACE, ("=====>%s()\n", __func__));
	अगर (!pRaInfo) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			     ("%s(): pRaInfo is NULL\n", __func__));
		वापस -1;
	पूर्ण
	RateID = pRaInfo->PreRate;
	LowestRate = pRaInfo->LowestRate;
	HighestRate = pRaInfo->HighestRate;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" RateID =%d LowestRate =%d HighestRate =%d RateSGI =%d\n",
		     RateID, LowestRate, HighestRate, pRaInfo->RateSGI));
	अगर (RateID > HighestRate) अणु
		RateID = HighestRate;
	पूर्ण अन्यथा अगर (pRaInfo->RateSGI) अणु
		pRaInfo->RateSGI = 0;
	पूर्ण अन्यथा अगर (RateID > LowestRate) अणु
		अगर (RateID > 0) अणु
			क्रम (i = RateID - 1; i > LowestRate; i--) अणु
				अगर (pRaInfo->RAUseRate & BIT(i)) अणु
					RateID = i;
					जाओ RateDownFinish;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (RateID <= LowestRate) अणु
		RateID = LowestRate;
	पूर्ण
RateDownFinish:
	अगर (pRaInfo->RAWaitingCounter == 1) अणु
		pRaInfo->RAWaitingCounter += 1;
		pRaInfo->RAPendingCounter += 1;
	पूर्ण अन्यथा अगर (pRaInfo->RAWaitingCounter == 0) अणु
		;
	पूर्ण अन्यथा अणु
		pRaInfo->RAWaitingCounter = 0;
		pRaInfo->RAPendingCounter = 0;
	पूर्ण

	अगर (pRaInfo->RAPendingCounter >= 4)
		pRaInfo->RAPendingCounter = 4;

	pRaInfo->DecisionRate = RateID;
	odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 2);
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
		     ODM_DBG_LOUD, ("Rate down, RPT Timing default\n"));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("RAWaitingCounter %d, RAPendingCounter %d",
			 pRaInfo->RAWaitingCounter, pRaInfo->RAPendingCounter));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("Rate down to RateID %d RateSGI %d\n", RateID, pRaInfo->RateSGI));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("<===== %s()\n", __func__));
	वापस 0;
पूर्ण

अटल पूर्णांक odm_RateUp_8188E(काष्ठा odm_dm_काष्ठा *dm_odm,
			    काष्ठा odm_ra_info *pRaInfo)
अणु
	u8 RateID, HighestRate;
	u8 i;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
		     ODM_DBG_TRACE, ("=====>%s()\n", __func__));
	अगर (!pRaInfo) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			     ("%s(): pRaInfo is NULL\n", __func__));
		वापस -1;
	पूर्ण
	RateID = pRaInfo->PreRate;
	HighestRate = pRaInfo->HighestRate;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" RateID =%d HighestRate =%d\n",
		     RateID, HighestRate));
	अगर (pRaInfo->RAWaitingCounter == 1) अणु
		pRaInfo->RAWaitingCounter = 0;
		pRaInfo->RAPendingCounter = 0;
	पूर्ण अन्यथा अगर (pRaInfo->RAWaitingCounter > 1) अणु
		pRaInfo->PreRssiStaRA = pRaInfo->RssiStaRA;
		जाओ RateUpfinish;
	पूर्ण
	odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 0);
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("%s():Decrease RPT Timing\n", __func__));

	अगर (RateID < HighestRate) अणु
		क्रम (i = RateID + 1; i <= HighestRate; i++) अणु
			अगर (pRaInfo->RAUseRate & BIT(i)) अणु
				RateID = i;
				जाओ RateUpfinish;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (RateID == HighestRate) अणु
		अगर (pRaInfo->SGIEnable && (pRaInfo->RateSGI != 1))
			pRaInfo->RateSGI = 1;
		अन्यथा अगर ((pRaInfo->SGIEnable) != 1)
			pRaInfo->RateSGI = 0;
	पूर्ण अन्यथा अणु
		RateID = HighestRate;
	पूर्ण
RateUpfinish:
	अगर (pRaInfo->RAWaitingCounter ==
		(4 + PendingForRateUpFail[pRaInfo->RAPendingCounter]))
		pRaInfo->RAWaitingCounter = 0;
	अन्यथा
		pRaInfo->RAWaitingCounter++;

	pRaInfo->DecisionRate = RateID;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("Rate up to RateID %d\n", RateID));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("RAWaitingCounter %d, RAPendingCounter %d",
		      pRaInfo->RAWaitingCounter, pRaInfo->RAPendingCounter));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
		     ODM_DBG_TRACE, ("<===== %s()\n", __func__));
	वापस 0;
पूर्ण

अटल व्योम odm_ResetRaCounter_8188E(काष्ठा odm_ra_info *pRaInfo)
अणु
	u8 RateID;

	RateID = pRaInfo->DecisionRate;
	pRaInfo->NscUp = (N_THRESHOLD_HIGH[RateID] +
			  N_THRESHOLD_LOW[RateID]) >> 1;
	pRaInfo->NscDown = (N_THRESHOLD_HIGH[RateID] +
			    N_THRESHOLD_LOW[RateID]) >> 1;
पूर्ण

अटल व्योम odm_RateDecision_8188E(काष्ठा odm_dm_काष्ठा *dm_odm,
				   काष्ठा odm_ra_info *pRaInfo)
अणु
	u8 RateID = 0, RtyPtID = 0, PenaltyID1 = 0, PenaltyID2 = 0, i = 0;
	/* u32 pool_retry; */
	अटल u8 DynamicTxRPTTimingCounter;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("=====>%s()\n", __func__));

	अगर (pRaInfo->Active && (pRaInfo->TOTAL > 0)) अणु /*  STA used and data packet निकासs */
		अगर ((pRaInfo->RssiStaRA < (pRaInfo->PreRssiStaRA - 3)) ||
		    (pRaInfo->RssiStaRA > (pRaInfo->PreRssiStaRA + 3))) अणु
			pRaInfo->RAWaitingCounter = 0;
			pRaInfo->RAPendingCounter = 0;
		पूर्ण
		/*  Start RA decision */
		अगर (pRaInfo->PreRate > pRaInfo->HighestRate)
			RateID = pRaInfo->HighestRate;
		अन्यथा
			RateID = pRaInfo->PreRate;
		अगर (pRaInfo->RssiStaRA > RSSI_THRESHOLD[RateID])
			RtyPtID = 0;
		अन्यथा
			RtyPtID = 1;
		PenaltyID1 = RETRY_PENALTY_IDX[RtyPtID][RateID]; /* TODO by page */

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscDown init is %d\n", pRaInfo->NscDown));

		क्रम (i = 0 ; i <= 4 ; i++)
			pRaInfo->NscDown += pRaInfo->RTY[i] * RETRY_PENALTY[PenaltyID1][i];

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscDown is %d, total*penalty[5] is %d\n", pRaInfo->NscDown,
			      (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5])));

		अगर (pRaInfo->NscDown > (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5]))
			pRaInfo->NscDown -= pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5];
		अन्यथा
			pRaInfo->NscDown = 0;

		/*  rate up */
		PenaltyID2 = RETRY_PENALTY_UP_IDX[RateID];
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscUp init is %d\n", pRaInfo->NscUp));

		क्रम (i = 0 ; i <= 4 ; i++)
			pRaInfo->NscUp += pRaInfo->RTY[i] * RETRY_PENALTY[PenaltyID2][i];

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     ("NscUp is %d, total*up[5] is %d\n",
			     pRaInfo->NscUp, (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5])));

		अगर (pRaInfo->NscUp > (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5]))
			pRaInfo->NscUp -= pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5];
		अन्यथा
			pRaInfo->NscUp = 0;

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE | ODM_COMP_INIT, ODM_DBG_LOUD,
			     (" RssiStaRa = %d RtyPtID =%d PenaltyID1 = 0x%x  PenaltyID2 = 0x%x RateID =%d NscDown =%d NscUp =%d SGI =%d\n",
			     pRaInfo->RssiStaRA, RtyPtID, PenaltyID1, PenaltyID2, RateID, pRaInfo->NscDown, pRaInfo->NscUp, pRaInfo->RateSGI));
		अगर ((pRaInfo->NscDown < N_THRESHOLD_LOW[RateID]) ||
		    (pRaInfo->DROP > DROPING_NECESSARY[RateID]))
			odm_RateDown_8188E(dm_odm, pRaInfo);
		अन्यथा अगर (pRaInfo->NscUp > N_THRESHOLD_HIGH[RateID])
			odm_RateUp_8188E(dm_odm, pRaInfo);

		अगर (pRaInfo->DecisionRate > pRaInfo->HighestRate)
			pRaInfo->DecisionRate = pRaInfo->HighestRate;

		अगर ((pRaInfo->DecisionRate) == (pRaInfo->PreRate))
			DynamicTxRPTTimingCounter += 1;
		अन्यथा
			DynamicTxRPTTimingCounter = 0;

		अगर (DynamicTxRPTTimingCounter >= 4) अणु
			odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 1);
			ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
				     ODM_DBG_LOUD, ("<===== Rate don't change 4 times, Extend RPT Timing\n"));
			DynamicTxRPTTimingCounter = 0;
		पूर्ण

		pRaInfo->PreRate = pRaInfo->DecisionRate;  /* YJ, add, 120120 */

		odm_ResetRaCounter_8188E(pRaInfo);
	पूर्ण
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("<===== %s()\n", __func__));
पूर्ण

अटल पूर्णांक odm_ARFBRefresh_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, काष्ठा odm_ra_info *pRaInfo)
अणु  /*  Wilson 2011/10/26 */
	काष्ठा adapter *adapt = dm_odm->Adapter;
	u32 MaskFromReg;
	s8 i;

	चयन (pRaInfo->RateID) अणु
	हाल RATR_INX_WIRELESS_NGB:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x0f8ff015;
		अवरोध;
	हाल RATR_INX_WIRELESS_NG:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x0f8ff010;
		अवरोध;
	हाल RATR_INX_WIRELESS_NB:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x0f8ff005;
		अवरोध;
	हाल RATR_INX_WIRELESS_N:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x0f8ff000;
		अवरोध;
	हाल RATR_INX_WIRELESS_GB:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x00000ff5;
		अवरोध;
	हाल RATR_INX_WIRELESS_G:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x00000ff0;
		अवरोध;
	हाल RATR_INX_WIRELESS_B:
		pRaInfo->RAUseRate = pRaInfo->RateMask & 0x0000000d;
		अवरोध;
	हाल 12:
		MaskFromReg = usb_पढ़ो32(adapt, REG_ARFR0);
		pRaInfo->RAUseRate = pRaInfo->RateMask & MaskFromReg;
		अवरोध;
	हाल 13:
		MaskFromReg = usb_पढ़ो32(adapt, REG_ARFR1);
		pRaInfo->RAUseRate = pRaInfo->RateMask & MaskFromReg;
		अवरोध;
	हाल 14:
		MaskFromReg = usb_पढ़ो32(adapt, REG_ARFR2);
		pRaInfo->RAUseRate = pRaInfo->RateMask & MaskFromReg;
		अवरोध;
	हाल 15:
		MaskFromReg = usb_पढ़ो32(adapt, REG_ARFR3);
		pRaInfo->RAUseRate = pRaInfo->RateMask & MaskFromReg;
		अवरोध;
	शेष:
		pRaInfo->RAUseRate = (pRaInfo->RateMask);
		अवरोध;
	पूर्ण
	/*  Highest rate */
	अगर (pRaInfo->RAUseRate) अणु
		क्रम (i = RATESIZE; i >= 0; i--) अणु
			अगर (pRaInfo->RAUseRate & BIT(i)) अणु
				pRaInfo->HighestRate = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pRaInfo->HighestRate = 0;
	पूर्ण
	/*  Lowest rate */
	अगर (pRaInfo->RAUseRate) अणु
		क्रम (i = 0; i < RATESIZE; i++) अणु
			अगर ((pRaInfo->RAUseRate) & BIT(i)) अणु
				pRaInfo->LowestRate = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pRaInfo->LowestRate = 0;
	पूर्ण

	अगर (pRaInfo->HighestRate > 0x13)
		pRaInfo->PTModeSS = 3;
	अन्यथा अगर (pRaInfo->HighestRate > 0x0b)
		pRaInfo->PTModeSS = 2;
	अन्यथा अगर (pRaInfo->HighestRate > 0x03)
		pRaInfo->PTModeSS = 1;
	अन्यथा
		pRaInfo->PTModeSS = 0;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("ODM_ARFBRefresh_8188E(): PTModeSS =%d\n", pRaInfo->PTModeSS));

	अगर (pRaInfo->DecisionRate > pRaInfo->HighestRate)
		pRaInfo->DecisionRate = pRaInfo->HighestRate;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("ODM_ARFBRefresh_8188E(): RateID =%d RateMask =%8.8x RAUseRate =%8.8x HighestRate =%d, DecisionRate =%d\n",
		     pRaInfo->RateID, pRaInfo->RateMask, pRaInfo->RAUseRate, pRaInfo->HighestRate, pRaInfo->DecisionRate));
	वापस 0;
पूर्ण

अटल व्योम odm_PTTryState_8188E(काष्ठा odm_ra_info *pRaInfo)
अणु
	pRaInfo->PTTryState = 0;
	चयन (pRaInfo->PTModeSS) अणु
	हाल 3:
		अगर (pRaInfo->DecisionRate >= 0x19)
			pRaInfo->PTTryState = 1;
		अवरोध;
	हाल 2:
		अगर (pRaInfo->DecisionRate >= 0x11)
			pRaInfo->PTTryState = 1;
		अवरोध;
	हाल 1:
		अगर (pRaInfo->DecisionRate >= 0x0a)
			pRaInfo->PTTryState = 1;
		अवरोध;
	हाल 0:
		अगर (pRaInfo->DecisionRate >= 0x03)
			pRaInfo->PTTryState = 1;
		अवरोध;
	शेष:
		pRaInfo->PTTryState = 0;
		अवरोध;
	पूर्ण

	अगर (pRaInfo->RssiStaRA < 48) अणु
		pRaInfo->PTStage = 0;
	पूर्ण अन्यथा अगर (pRaInfo->PTTryState == 1) अणु
		अगर ((pRaInfo->PTStopCount >= 10) ||
		    (pRaInfo->PTPreRssi > pRaInfo->RssiStaRA + 5) ||
		    (pRaInfo->PTPreRssi < pRaInfo->RssiStaRA - 5) ||
		    (pRaInfo->DecisionRate != pRaInfo->PTPreRate)) अणु
			अगर (pRaInfo->PTStage == 0)
				pRaInfo->PTStage = 1;
			अन्यथा अगर (pRaInfo->PTStage == 1)
				pRaInfo->PTStage = 3;
			अन्यथा
				pRaInfo->PTStage = 5;

			pRaInfo->PTPreRssi = pRaInfo->RssiStaRA;
			pRaInfo->PTStopCount = 0;
		पूर्ण अन्यथा अणु
			pRaInfo->RAstage = 0;
			pRaInfo->PTStopCount++;
		पूर्ण
	पूर्ण अन्यथा अणु
		pRaInfo->PTStage = 0;
		pRaInfo->RAstage = 0;
	पूर्ण
	pRaInfo->PTPreRate = pRaInfo->DecisionRate;
पूर्ण

अटल व्योम odm_PTDecision_8188E(काष्ठा odm_ra_info *pRaInfo)
अणु
	u8 j;
	u8 temp_stage;
	u32 numsc;
	u32 num_total;
	u8 stage_id;

	numsc  = 0;
	num_total = pRaInfo->TOTAL * PT_PENALTY[5];
	क्रम (j = 0; j <= 4; j++) अणु
		numsc += pRaInfo->RTY[j] * PT_PENALTY[j];
		अगर (numsc > num_total)
			अवरोध;
	पूर्ण

	j >>= 1;
	temp_stage = (pRaInfo->PTStage + 1) >> 1;
	अगर (temp_stage > j)
		stage_id = temp_stage - j;
	अन्यथा
		stage_id = 0;

	pRaInfo->PTSmoothFactor = (pRaInfo->PTSmoothFactor >> 1) +
				  (pRaInfo->PTSmoothFactor >> 2) +
				  stage_id * 16 + 2;
	अगर (pRaInfo->PTSmoothFactor > 192)
		pRaInfo->PTSmoothFactor = 192;
	stage_id = pRaInfo->PTSmoothFactor >> 6;
	temp_stage = stage_id * 2;
	अगर (temp_stage != 0)
		temp_stage -= 1;
	अगर (pRaInfo->DROP > 3)
		temp_stage = 0;
	pRaInfo->PTStage = temp_stage;
पूर्ण

अटल व्योम odm_RATxRPTTimerSetting(काष्ठा odm_dm_काष्ठा *dm_odm,
				    u16 minRptTime)
अणु
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" =====>%s()\n", __func__));

	अगर (dm_odm->CurrminRptTime != minRptTime) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			     (" CurrminRptTime = 0x%04x minRptTime = 0x%04x\n", dm_odm->CurrminRptTime, minRptTime));
		rtw_rpt_समयr_cfg_cmd(dm_odm->Adapter, minRptTime);
		dm_odm->CurrminRptTime = minRptTime;
	पूर्ण
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" <===== %s()\n", __func__));
पूर्ण

पूर्णांक ODM_RAInfo_Init(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid)
अणु
	काष्ठा odm_ra_info *pRaInfo = &dm_odm->RAInfo[macid];
	u8 WirelessMode = 0xFF; /* invalid value */
	u8 max_rate_idx = 0x13; /* MCS7 */

	अगर (dm_odm->pWirelessMode)
		WirelessMode = *dm_odm->pWirelessMode;

	अगर (WirelessMode != 0xFF) अणु
		अगर (WirelessMode & ODM_WM_N24G)
			max_rate_idx = 0x13;
		अन्यथा अगर (WirelessMode & ODM_WM_G)
			max_rate_idx = 0x0b;
		अन्यथा अगर (WirelessMode & ODM_WM_B)
			max_rate_idx = 0x03;
	पूर्ण

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("%s(): WirelessMode:0x%08x , max_raid_idx:0x%02x\n",
		      __func__, WirelessMode, max_rate_idx));

	pRaInfo->DecisionRate = max_rate_idx;
	pRaInfo->PreRate = max_rate_idx;
	pRaInfo->HighestRate = max_rate_idx;
	pRaInfo->LowestRate = 0;
	pRaInfo->RateID = 0;
	pRaInfo->RateMask = 0xffffffff;
	pRaInfo->RssiStaRA = 0;
	pRaInfo->PreRssiStaRA = 0;
	pRaInfo->SGIEnable = 0;
	pRaInfo->RAUseRate = 0xffffffff;
	pRaInfo->NscDown = (N_THRESHOLD_HIGH[0x13] + N_THRESHOLD_LOW[0x13]) / 2;
	pRaInfo->NscUp = (N_THRESHOLD_HIGH[0x13] + N_THRESHOLD_LOW[0x13]) / 2;
	pRaInfo->RateSGI = 0;
	pRaInfo->Active = 1;	/* Active is not used at present. by page, 110819 */
	pRaInfo->RptTime = 0x927c;
	pRaInfo->DROP = 0;
	pRaInfo->RTY[0] = 0;
	pRaInfo->RTY[1] = 0;
	pRaInfo->RTY[2] = 0;
	pRaInfo->RTY[3] = 0;
	pRaInfo->RTY[4] = 0;
	pRaInfo->TOTAL = 0;
	pRaInfo->RAWaitingCounter = 0;
	pRaInfo->RAPendingCounter = 0;
	pRaInfo->PTActive = 1;   /*  Active when this STA is use */
	pRaInfo->PTTryState = 0;
	pRaInfo->PTStage = 5; /*  Need to fill पूर्णांकo HW_PWR_STATUS */
	pRaInfo->PTSmoothFactor = 192;
	pRaInfo->PTStopCount = 0;
	pRaInfo->PTPreRate = 0;
	pRaInfo->PTPreRssi = 0;
	pRaInfo->PTModeSS = 0;
	pRaInfo->RAstage = 0;
	वापस 0;
पूर्ण

पूर्णांक ODM_RAInfo_Init_all(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	u8 macid = 0;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, ("=====>\n"));
	dm_odm->CurrminRptTime = 0;

	क्रम (macid = 0; macid < ODM_ASSOCIATE_ENTRY_NUM; macid++)
		ODM_RAInfo_Init(dm_odm, macid);

	वापस 0;
पूर्ण

u8 ODM_RA_GetShortGI_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid)
अणु
	अगर ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		वापस 0;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("macid =%d SGI =%d\n", macid, dm_odm->RAInfo[macid].RateSGI));
	वापस dm_odm->RAInfo[macid].RateSGI;
पूर्ण

u8 ODM_RA_GetDecisionRate_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid)
अणु
	u8 DecisionRate = 0;

	अगर ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		वापस 0;
	DecisionRate = dm_odm->RAInfo[macid].DecisionRate;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" macid =%d DecisionRate = 0x%x\n", macid, DecisionRate));
	वापस DecisionRate;
पूर्ण

u8 ODM_RA_GetHwPwrStatus_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid)
अणु
	u8 PTStage = 5;

	अगर ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		वापस 0;
	PTStage = dm_odm->RAInfo[macid].PTStage;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("macid =%d PTStage = 0x%x\n", macid, PTStage));
	वापस PTStage;
पूर्ण

व्योम ODM_RA_UpdateRateInfo_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid, u8 RateID, u32 RateMask, u8 SGIEnable)
अणु
	काष्ठा odm_ra_info *pRaInfo = शून्य;

	अगर ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		वापस;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("macid =%d RateID = 0x%x RateMask = 0x%x SGIEnable =%d\n",
		     macid, RateID, RateMask, SGIEnable));

	pRaInfo = &dm_odm->RAInfo[macid];
	pRaInfo->RateID = RateID;
	pRaInfo->RateMask = RateMask;
	pRaInfo->SGIEnable = SGIEnable;
	odm_ARFBRefresh_8188E(dm_odm, pRaInfo);
पूर्ण

व्योम ODM_RA_SetRSSI_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid, u8 Rssi)
अणु
	काष्ठा odm_ra_info *pRaInfo = शून्य;

	अगर ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		वापस;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" macid =%d Rssi =%d\n", macid, Rssi));

	pRaInfo = &dm_odm->RAInfo[macid];
	pRaInfo->RssiStaRA = Rssi;
पूर्ण

व्योम ODM_RA_Set_TxRPT_Time(काष्ठा odm_dm_काष्ठा *dm_odm, u16 minRptTime)
अणु
	काष्ठा adapter *adapt = dm_odm->Adapter;

	usb_ग_लिखो16(adapt, REG_TX_RPT_TIME, minRptTime);
पूर्ण

व्योम ODM_RA_TxRPT2Handle_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 *TxRPT_Buf, u16 TxRPT_Len, u32 macid_entry0, u32 macid_entry1)
अणु
	काष्ठा odm_ra_info *pRAInfo = शून्य;
	u8 MacId = 0;
	u8 *pBuffer = शून्य;
	u32 valid = 0, ItemNum = 0;
	u16 minRptTime = 0x927c;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("=====>%s(): valid0 =%d valid1 =%d BufferLength =%d\n",
		      __func__, macid_entry0, macid_entry1, TxRPT_Len));

	ItemNum = TxRPT_Len >> 3;
	pBuffer = TxRPT_Buf;

	करो अणु
		अगर (MacId >= ASSOCIATE_ENTRY_NUM)
			valid = 0;
		अन्यथा अगर (MacId >= 32)
			valid = (1 << (MacId - 32)) & macid_entry1;
		अन्यथा
			valid = (1 << MacId) & macid_entry0;

		pRAInfo = &dm_odm->RAInfo[MacId];
		अगर (valid) अणु
			pRAInfo->RTY[0] = (u16)GET_TX_REPORT_TYPE1_RERTY_0(pBuffer);
			pRAInfo->RTY[1] = (u16)GET_TX_REPORT_TYPE1_RERTY_1(pBuffer);
			pRAInfo->RTY[2] = (u16)GET_TX_REPORT_TYPE1_RERTY_2(pBuffer);
			pRAInfo->RTY[3] = (u16)GET_TX_REPORT_TYPE1_RERTY_3(pBuffer);
			pRAInfo->RTY[4] = (u16)GET_TX_REPORT_TYPE1_RERTY_4(pBuffer);
			pRAInfo->DROP =   (u16)GET_TX_REPORT_TYPE1_DROP_0(pBuffer);
			pRAInfo->TOTAL = pRAInfo->RTY[0] + pRAInfo->RTY[1] +
					 pRAInfo->RTY[2] + pRAInfo->RTY[3] +
					 pRAInfo->RTY[4] + pRAInfo->DROP;
			अगर (pRAInfo->TOTAL != 0) अणु
				ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
					     ("macid =%d Total =%d R0 =%d R1 =%d R2 =%d R3 =%d R4 =%d D0 =%d valid0 =%x valid1 =%x\n",
					     MacId, pRAInfo->TOTAL,
					     pRAInfo->RTY[0], pRAInfo->RTY[1],
					     pRAInfo->RTY[2], pRAInfo->RTY[3],
					     pRAInfo->RTY[4], pRAInfo->DROP,
					     macid_entry0, macid_entry1));
				अगर (pRAInfo->PTActive) अणु
					अगर (pRAInfo->RAstage < 5)
						odm_RateDecision_8188E(dm_odm, pRAInfo);
					अन्यथा अगर (pRAInfo->RAstage == 5) /*  Power training try state */
						odm_PTTryState_8188E(pRAInfo);
					अन्यथा /*  RAstage == 6 */
						odm_PTDecision_8188E(pRAInfo);

					/*  Stage_RA counter */
					अगर (pRAInfo->RAstage <= 5)
						pRAInfo->RAstage++;
					अन्यथा
						pRAInfo->RAstage = 0;
				पूर्ण अन्यथा अणु
					odm_RateDecision_8188E(dm_odm, pRAInfo);
				पूर्ण
				ODM_RT_TRACE(dm_odm, ODM_COMP_INIT, ODM_DBG_LOUD,
					     ("macid =%d R0 =%d R1 =%d R2 =%d R3 =%d R4 =%d drop =%d valid0 =%x RateID =%d SGI =%d\n",
					     MacId,
					     pRAInfo->RTY[0],
					     pRAInfo->RTY[1],
					     pRAInfo->RTY[2],
					     pRAInfo->RTY[3],
					     pRAInfo->RTY[4],
					     pRAInfo->DROP,
					     macid_entry0,
					     pRAInfo->DecisionRate,
					     pRAInfo->RateSGI));
			पूर्ण अन्यथा अणु
				ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, (" TOTAL = 0!!!!\n"));
			पूर्ण
		पूर्ण

		अगर (minRptTime > pRAInfo->RptTime)
			minRptTime = pRAInfo->RptTime;

		pBuffer += TX_RPT2_ITEM_SIZE;
		MacId++;
	पूर्ण जबतक (MacId < ItemNum);

	odm_RATxRPTTimerSetting(dm_odm, minRptTime);

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("<===== %s()\n", __func__));
पूर्ण
