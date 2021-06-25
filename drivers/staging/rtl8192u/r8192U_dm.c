<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*++
Copyright-c Realtek Semiconductor Corp. All rights reserved.

Module Name:
	r8192U_dm.c

Abstract:
	HW dynamic mechanism.

Major Change History:
	When		Who				What
	----------	--------------- -------------------------------
	2008-05-14	amy                     create version 0 porting from winकरोws code.

--*/
#समावेश "r8192U.h"
#समावेश "r8192U_dm.h"
#समावेश "r8192U_hw.h"
#समावेश "r819xU_phy.h"
#समावेश "r819xU_phyreg.h"
#समावेश "r8190_rtl8256.h"
#समावेश "r819xU_cmdpkt.h"
/*---------------------------Define Local Constant---------------------------*/
/* Indicate dअगरferent AP venकरोr क्रम IOT issue. */
अटल u32 edca_setting_DL[HT_IOT_PEER_MAX] = अणु
	0x5e4322, 0x5e4322, 0x5e4322, 0x604322, 0x00a44f, 0x5ea44f
पूर्ण;

अटल u32 edca_setting_UL[HT_IOT_PEER_MAX] = अणु
	0x5e4322, 0x00a44f, 0x5e4322, 0x604322, 0x5ea44f, 0x5ea44f
पूर्ण;

#घोषणा RTK_UL_EDCA 0xa44f
#घोषणा RTK_DL_EDCA 0x5e4322
/*---------------------------Define Local Constant---------------------------*/


/*------------------------Define global variable-----------------------------*/
/* Debug variable ? */
काष्ठा dig dm_digtable;
/* Store current software ग_लिखो रेजिस्टर content क्रम MAC PHY. */
u8		dm_shaकरोw[16][256] = अणु अणु0पूर्ण पूर्ण;
/* For Dynamic Rx Path Selection by Signal Strength */
अटल काष्ठा dynamic_rx_path_sel DM_RxPathSelTable;

बाह्य	व्योम dm_check_fsync(काष्ठा net_device *dev);

/* DM --> Rate Adaptive */
अटल	व्योम	dm_check_rate_adaptive(काष्ठा net_device *dev);

/* DM --> Bandwidth चयन */
अटल	व्योम	dm_init_bandwidth_स्वतःचयन(काष्ठा net_device *dev);
अटल	व्योम	dm_bandwidth_स्वतःचयन(काष्ठा net_device *dev);

/* DM --> TX घातer control */
/*अटल	व्योम	dm_initialize_txघातer_tracking(काष्ठा net_device *dev);*/

अटल	व्योम	dm_check_txघातer_tracking(काष्ठा net_device *dev);

/*अटल	व्योम	dm_txघातer_reset_recovery(काष्ठा net_device *dev);*/

/* DM --> Dynamic Init Gain by RSSI */
अटल	व्योम	dm_dig_init(काष्ठा net_device *dev);
अटल	व्योम	dm_ctrl_initgain_byrssi(काष्ठा net_device *dev);
अटल	व्योम	dm_ctrl_initgain_byrssi_highpwr(काष्ठा net_device *dev);
अटल	व्योम	dm_ctrl_initgain_byrssi_by_driverrssi(काष्ठा net_device *dev);
अटल	व्योम	dm_ctrl_initgain_byrssi_by_fwfalse_alarm(काष्ठा net_device *dev);
अटल	व्योम	dm_initial_gain(काष्ठा net_device *dev);
अटल	व्योम	dm_pd_th(काष्ठा net_device *dev);
अटल	व्योम	dm_cs_ratio(काष्ठा net_device *dev);

अटल	व्योम dm_init_ctstoself(काष्ठा net_device *dev);
/* DM --> EDCA turbo mode control */
अटल	व्योम	dm_check_edca_turbo(काष्ठा net_device *dev);

/*अटल	व्योम	dm_gpio_change_rf(काष्ठा net_device *dev);*/
/* DM --> Check PBC */
अटल	व्योम dm_check_pbc_gpio(काष्ठा net_device *dev);

/* DM --> Check current RX RF path state */
अटल	व्योम	dm_check_rx_path_selection(काष्ठा net_device *dev);
अटल	व्योम dm_init_rxpath_selection(काष्ठा net_device *dev);
अटल	व्योम dm_rxpath_sel_byrssi(काष्ठा net_device *dev);

/* DM --> Fsync क्रम broadcom ap */
अटल व्योम dm_init_fsync(काष्ठा net_device *dev);
अटल व्योम dm_deInit_fsync(काष्ठा net_device *dev);

/* Added by vivi, 20080522 */
अटल	व्योम	dm_check_txrateandretrycount(काष्ठा net_device *dev);

/*---------------------Define local function prototype-----------------------*/

/*---------------------Define of Tx Power Control For Near/Far Range --------*/   /*Add by Jacken 2008/02/18 */
अटल	व्योम	dm_init_dynamic_txघातer(काष्ठा net_device *dev);
अटल	व्योम	dm_dynamic_txघातer(काष्ठा net_device *dev);

/* DM --> For rate adaptive and DIG, we must send RSSI to firmware */
अटल	व्योम dm_send_rssi_tofw(काष्ठा net_device *dev);
अटल	व्योम	dm_ctstoself(काष्ठा net_device *dev);
/*---------------------------Define function prototype------------------------*/
/* ================================================================================
 *	HW Dynamic mechanism पूर्णांकerface.
 * ================================================================================
 *
 *
 *	Description:
 *		Prepare SW resource क्रम HW dynamic mechanism.
 *
 *	Assumption:
 *		This function is only invoked at driver initialization once.
 */
व्योम init_hal_dm(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Undecorated Smoothed Signal Strength, it can utilized to dynamic mechanism. */
	priv->undecorated_smoothed_pwdb = -1;

	/* Initial TX Power Control क्रम near/far range , add by amy 2008/05/15, porting from winकरोws code. */
	dm_init_dynamic_txघातer(dev);
	init_rate_adaptive(dev);
	/*dm_initialize_txघातer_tracking(dev);*/
	dm_dig_init(dev);
	dm_init_edca_turbo(dev);
	dm_init_bandwidth_स्वतःचयन(dev);
	dm_init_fsync(dev);
	dm_init_rxpath_selection(dev);
	dm_init_ctstoself(dev);

पूर्ण	/* InitHalDm */

व्योम deinit_hal_dm(काष्ठा net_device *dev)
अणु
	dm_deInit_fsync(dev);
पूर्ण

#अगर_घोषित USB_RX_AGGREGATION_SUPPORT
व्योम dm_CheckRxAggregation(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	अटल अचिन्हित दीर्घ	lastTxOkCnt;
	अटल अचिन्हित दीर्घ	lastRxOkCnt;
	अचिन्हित दीर्घ		curTxOkCnt = 0;
	अचिन्हित दीर्घ		curRxOkCnt = 0;

/*
	अगर (pHalData->bForcedUsbRxAggr) अणु
		अगर (pHalData->ForcedUsbRxAggrInfo == 0) अणु
			अगर (pHalData->bCurrentRxAggrEnable) अणु
				Adapter->HalFunc.HalUsbRxAggrHandler(Adapter, FALSE);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!pHalData->bCurrentRxAggrEnable || (pHalData->ForcedUsbRxAggrInfo != pHalData->LastUsbRxAggrInfoSetting)) अणु
				Adapter->HalFunc.HalUsbRxAggrHandler(Adapter, TRUE);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

*/
	curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
	curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;

	अगर ((curTxOkCnt + curRxOkCnt) < 15000000)
		वापस;

	अगर (curTxOkCnt > 4*curRxOkCnt) अणु
		अगर (priv->bCurrentRxAggrEnable) अणु
			ग_लिखो_nic_dword(dev, 0x1a8, 0);
			priv->bCurrentRxAggrEnable = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!priv->bCurrentRxAggrEnable && !pHTInfo->bCurrentRT2RTAggregation) अणु
			u32 ulValue;

			ulValue = (pHTInfo->UsbRxFwAggrEn<<24) | (pHTInfo->UsbRxFwAggrPageNum<<16) |
				(pHTInfo->UsbRxFwAggrPacketNum<<8) | (pHTInfo->UsbRxFwAggrTimeout);
			/* If usb rx firmware aggregation is enabled,
			 * when anyone of three threshold conditions above is reached,
			 * firmware will send aggregated packet to driver.
			 */
			ग_लिखो_nic_dword(dev, 0x1a8, ulValue);
			priv->bCurrentRxAggrEnable = true;
		पूर्ण
	पूर्ण

	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
पूर्ण	/* dm_CheckEdcaTurbo */
#पूर्ण_अगर

व्योम hal_dm_watchकरोg(काष्ठा net_device *dev)
अणु
	/*काष्ठा r8192_priv *priv = ieee80211_priv(dev);*/

	/*अटल u8	previous_bssid[6] =अणु0पूर्ण;*/

	/*Add by amy 2008/05/15 ,porting from winकरोws code.*/
	dm_check_rate_adaptive(dev);
	dm_dynamic_txघातer(dev);
	dm_check_txrateandretrycount(dev);
	dm_check_txघातer_tracking(dev);
	dm_ctrl_initgain_byrssi(dev);
	dm_check_edca_turbo(dev);
	dm_bandwidth_स्वतःचयन(dev);
	dm_check_rx_path_selection(dev);
	dm_check_fsync(dev);

	/* Add by amy 2008-05-15 porting from winकरोws code. */
	dm_check_pbc_gpio(dev);
	dm_send_rssi_tofw(dev);
	dm_ctstoself(dev);
#अगर_घोषित USB_RX_AGGREGATION_SUPPORT
	dm_CheckRxAggregation(dev);
#पूर्ण_अगर
पूर्ण	/* HalDmWatchDog */

/* Decide Rate Adaptive Set according to distance (संकेत strength)
 *	01/11/2008	MHC		Modअगरy input arguments and RATR table level.
 *	01/16/2008	MHC		RF_Type is asचिन्हित in ReadAdapterInfo(). We must call
 *						the function after making sure RF_Type.
 */
व्योम init_rate_adaptive(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	prate_adaptive	pra = (prate_adaptive)&priv->rate_adaptive;

	pra->ratr_state = DM_RATR_STA_MAX;
	pra->high2low_rssi_thresh_क्रम_ra = RATE_ADAPTIVE_TH_HIGH;
	pra->low2high_rssi_thresh_क्रम_ra20M = RATE_ADAPTIVE_TH_LOW_20M + 5;
	pra->low2high_rssi_thresh_क्रम_ra40M = RATE_ADAPTIVE_TH_LOW_40M + 5;

	pra->high_rssi_thresh_क्रम_ra = RATE_ADAPTIVE_TH_HIGH + 5;
	pra->low_rssi_thresh_क्रम_ra20M = RATE_ADAPTIVE_TH_LOW_20M;
	pra->low_rssi_thresh_क्रम_ra40M = RATE_ADAPTIVE_TH_LOW_40M;

	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		pra->ping_rssi_enable = 1;
	अन्यथा
		pra->ping_rssi_enable = 0;
	pra->ping_rssi_thresh_क्रम_ra = 15;

	अगर (priv->rf_type == RF_2T4R) अणु
		/* 07/10/08 MH Modअगरy क्रम RA smooth scheme.
		 * 2008/01/11 MH Modअगरy 2T RATR table क्रम dअगरferent RSSI. 080515 porting by amy from winकरोws code.
		 */
		pra->upper_rssi_threshold_ratr		=	0x8f0f0000;
		pra->middle_rssi_threshold_ratr		=	0x8f0ff000;
		pra->low_rssi_threshold_ratr		=	0x8f0ff001;
		pra->low_rssi_threshold_ratr_40M	=	0x8f0ff005;
		pra->low_rssi_threshold_ratr_20M	=	0x8f0ff001;
		pra->ping_rssi_ratr	=	0x0000000d;/* cosa add क्रम test */
	पूर्ण अन्यथा अगर (priv->rf_type == RF_1T2R) अणु
		pra->upper_rssi_threshold_ratr		=	0x000f0000;
		pra->middle_rssi_threshold_ratr		=	0x000ff000;
		pra->low_rssi_threshold_ratr		=	0x000ff001;
		pra->low_rssi_threshold_ratr_40M	=	0x000ff005;
		pra->low_rssi_threshold_ratr_20M	=	0x000ff001;
		pra->ping_rssi_ratr	=	0x0000000d;/* cosa add क्रम test */
	पूर्ण

पूर्ण	/* InitRateAdaptive */

/*-----------------------------------------------------------------------------
 * Function:	dm_check_rate_adaptive()
 *
 * Overview:
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/26/08	amy	Create version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम dm_check_rate_adaptive(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	prate_adaptive			pra = (prate_adaptive)&priv->rate_adaptive;
	u32						currentRATR, targetRATR = 0;
	u32						LowRSSIThreshForRA = 0, HighRSSIThreshForRA = 0;
	bool						bलघु_gi_enabled = false;
	अटल u8					ping_rssi_state;

	अगर (!priv->up) अणु
		RT_TRACE(COMP_RATE, "<---- dm_check_rate_adaptive(): driver is going to unload\n");
		वापस;
	पूर्ण

	अगर (pra->rate_adaptive_disabled) /* this variable is set by ioctl. */
		वापस;

	/* TODO: Only 11n mode is implemented currently, */
	अगर (!(priv->ieee80211->mode == WIRELESS_MODE_N_24G ||
	      priv->ieee80211->mode == WIRELESS_MODE_N_5G))
		वापस;

	अगर (priv->ieee80211->state == IEEE80211_LINKED) अणु
		/*RT_TRACE(COMP_RATE, "dm_CheckRateAdaptive(): \t");*/

		/* Check whether Short GI is enabled */
		bलघु_gi_enabled = (pHTInfo->bCurTxBW40MHz && pHTInfo->bCurShortGI40MHz) ||
			(!pHTInfo->bCurTxBW40MHz && pHTInfo->bCurShortGI20MHz);

		pra->upper_rssi_threshold_ratr =
				(pra->upper_rssi_threshold_ratr & (~BIT(31))) |
				((bलघु_gi_enabled) ? BIT(31) : 0);

		pra->middle_rssi_threshold_ratr =
				(pra->middle_rssi_threshold_ratr & (~BIT(31))) |
				((bलघु_gi_enabled) ? BIT(31) : 0);

		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
			pra->low_rssi_threshold_ratr =
			      (pra->low_rssi_threshold_ratr_40M & (~BIT(31))) |
			      ((bलघु_gi_enabled) ? BIT(31) : 0);
		पूर्ण अन्यथा अणु
			pra->low_rssi_threshold_ratr =
			(pra->low_rssi_threshold_ratr_20M & (~BIT(31))) |
			((bलघु_gi_enabled) ? BIT(31) : 0);
		पूर्ण
		/* cosa add क्रम test */
		pra->ping_rssi_ratr =
				(pra->ping_rssi_ratr & (~BIT(31))) |
				((bलघु_gi_enabled) ? BIT(31) : 0);

		/* 2007/10/08 MH We support RA smooth scheme now. When it is the first
		 * समय to link with AP. We will not change upper/lower threshold. If
		 * STA stay in high or low level, we must change two dअगरferent threshold
		 * to prevent jumping frequently.
		 */
		अगर (pra->ratr_state == DM_RATR_STA_HIGH) अणु
			HighRSSIThreshForRA	= pra->high2low_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA	= (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low_rssi_thresh_क्रम_ra40M):(pra->low_rssi_thresh_क्रम_ra20M);
		पूर्ण अन्यथा अगर (pra->ratr_state == DM_RATR_STA_LOW) अणु
			HighRSSIThreshForRA	= pra->high_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA	= (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low2high_rssi_thresh_क्रम_ra40M):(pra->low2high_rssi_thresh_क्रम_ra20M);
		पूर्ण अन्यथा अणु
			HighRSSIThreshForRA	= pra->high_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA	= (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low_rssi_thresh_क्रम_ra40M):(pra->low_rssi_thresh_क्रम_ra20M);
		पूर्ण

		/*DbgPrपूर्णांक("[DM] THresh H/L=%d/%d\n\r", RATR.HighRSSIThreshForRA, RATR.LowRSSIThreshForRA);*/
		अगर (priv->undecorated_smoothed_pwdb >= (दीर्घ)HighRSSIThreshForRA) अणु
			/*DbgPrपूर्णांक("[DM] RSSI=%d STA=HIGH\n\r", pHalData->UndecoratedSmoothedPWDB);*/
			pra->ratr_state = DM_RATR_STA_HIGH;
			targetRATR = pra->upper_rssi_threshold_ratr;
		पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb >= (दीर्घ)LowRSSIThreshForRA) अणु
			/*DbgPrपूर्णांक("[DM] RSSI=%d STA=Middle\n\r", pHalData->UndecoratedSmoothedPWDB);*/
			pra->ratr_state = DM_RATR_STA_MIDDLE;
			targetRATR = pra->middle_rssi_threshold_ratr;
		पूर्ण अन्यथा अणु
			/*DbgPrपूर्णांक("[DM] RSSI=%d STA=LOW\n\r", pHalData->UndecoratedSmoothedPWDB);*/
			pra->ratr_state = DM_RATR_STA_LOW;
			targetRATR = pra->low_rssi_threshold_ratr;
		पूर्ण

		/* cosa add क्रम test */
		अगर (pra->ping_rssi_enable) अणु
			/*pHalData->UndecoratedSmoothedPWDB = 19;*/
			अगर (priv->undecorated_smoothed_pwdb < (दीर्घ)(pra->ping_rssi_thresh_क्रम_ra+5)) अणु
				अगर ((priv->undecorated_smoothed_pwdb < (दीर्घ)pra->ping_rssi_thresh_क्रम_ra) ||
					ping_rssi_state) अणु
					/*DbgPrपूर्णांक("TestRSSI = %d, set RATR to 0x%x\n", pHalData->UndecoratedSmoothedPWDB, pRA->TestRSSIRATR);*/
					pra->ratr_state = DM_RATR_STA_LOW;
					targetRATR = pra->ping_rssi_ratr;
					ping_rssi_state = 1;
				पूर्ण
				/*अन्यथा
					DbgPrपूर्णांक("TestRSSI is between the range.\n");*/
			पूर्ण अन्यथा अणु
				/*DbgPrपूर्णांक("TestRSSI Recover to 0x%x\n", targetRATR);*/
				ping_rssi_state = 0;
			पूर्ण
		पूर्ण

		/* 2008.04.01
		 * For RTL819X, अगर pairwisekey = wep/tkip, we support only MCS0~7.
		 */
		अगर (priv->ieee80211->GetHalfNmodeSupportByAPsHandler(dev))
			targetRATR &= 0xf00fffff;

		/* Check whether updating of RATR0 is required */
		पढ़ो_nic_dword(dev, RATR0, &currentRATR);
		अगर (targetRATR !=  currentRATR) अणु
			u32 ratr_value;

			ratr_value = targetRATR;
			RT_TRACE(COMP_RATE, "currentRATR = %x, targetRATR = %x\n", currentRATR, targetRATR);
			अगर (priv->rf_type == RF_1T2R)
				ratr_value &= ~(RATE_ALL_OFDM_2SS);
			ग_लिखो_nic_dword(dev, RATR0, ratr_value);
			ग_लिखो_nic_byte(dev, UFWP, 1);

			pra->last_ratr = targetRATR;
		पूर्ण

	पूर्ण अन्यथा अणु
		pra->ratr_state = DM_RATR_STA_MAX;
	पूर्ण

पूर्ण	/* dm_CheckRateAdaptive */

अटल व्योम dm_init_bandwidth_स्वतःचयन(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->ieee80211->bandwidth_स्वतः_चयन.threshold_20Mhzto40Mhz = BW_AUTO_SWITCH_LOW_HIGH;
	priv->ieee80211->bandwidth_स्वतः_चयन.threshold_40Mhzto20Mhz = BW_AUTO_SWITCH_HIGH_LOW;
	priv->ieee80211->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = false;
	priv->ieee80211->bandwidth_स्वतः_चयन.bस्वतःचयन_enable = false;

पूर्ण	/* dm_init_bandwidth_स्वतःचयन */

अटल व्योम dm_bandwidth_स्वतःचयन(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 || !priv->ieee80211->bandwidth_स्वतः_चयन.bस्वतःचयन_enable)
		वापस;
	अगर (!priv->ieee80211->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz) अणु /* If send packets in 40 Mhz in 20/40 */
		अगर (priv->undecorated_smoothed_pwdb <= priv->ieee80211->bandwidth_स्वतः_चयन.threshold_40Mhzto20Mhz)
			priv->ieee80211->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = true;
	पूर्ण अन्यथा अणु /* in क्रमce send packets in 20 Mhz in 20/40 */
		अगर (priv->undecorated_smoothed_pwdb >= priv->ieee80211->bandwidth_स्वतः_चयन.threshold_20Mhzto40Mhz)
			priv->ieee80211->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = false;
	पूर्ण
पूर्ण	/* dm_BandwidthAutoSwitch */

/* OFDM शेष at 0db, index=6. */
अटल u32 OFDMSwingTable[OFDM_Table_Length] = अणु
	0x7f8001fe,	/* 0, +6db */
	0x71c001c7,	/* 1, +5db */
	0x65400195,	/* 2, +4db */
	0x5a400169,	/* 3, +3db */
	0x50800142,	/* 4, +2db */
	0x47c0011f,	/* 5, +1db */
	0x40000100,	/* 6, +0db ===> शेष, upper क्रम higher temperature, lower क्रम low temperature */
	0x390000e4,	/* 7, -1db */
	0x32c000cb,	/* 8, -2db */
	0x2d4000b5,	/* 9, -3db */
	0x288000a2,	/* 10, -4db */
	0x24000090,	/* 11, -5db */
	0x20000080,	/* 12, -6db */
	0x1c800072,	/* 13, -7db */
	0x19800066,	/* 14, -8db */
	0x26c0005b,	/* 15, -9db */
	0x24400051,	/* 16, -10db */
	0x12000048,	/* 17, -11db */
	0x10000040	/* 18, -12db */
पूर्ण;

अटल u8	CCKSwingTable_Ch1_Ch13[CCK_Table_length][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण,	/* 0, +0db ===> CCK40M शेष */
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण,	/* 1, -1db */
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण,	/* 2, -2db */
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण,	/* 3, -3db */
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण,	/* 4, -4db */
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण,	/* 5, -5db */
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण,	/* 6, -6db ===> CCK20M शेष */
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण,	/* 7, -7db */
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण,	/* 8, -8db */
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण,	/* 9, -9db */
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,	/* 10, -10db */
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण	/* 11, -11db */
पूर्ण;

अटल u8	CCKSwingTable_Ch14[CCK_Table_length][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 0, +0db  ===> CCK40M शेष */
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 1, -1db */
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 2, -2db */
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 3, -3db */
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 4, -4db */
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 5, -5db */
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 6, -6db  ===> CCK20M शेष */
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 7, -7db */
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 8, -8db */
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 9, -9db */
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,	/* 10, -10db */
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण	/* 11, -11db */
पूर्ण;

अटल व्योम dm_TXPowerTrackingCallback_TSSI(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	bool						vivअगरlag = false;
	काष्ठा tx_config_cmd			        tx_cmd;
	u8						घातerlevelOFDM24G;
	पूर्णांक						i = 0, j = 0, k = 0;
	u8						RF_Type, पंचांगp_report[5] = अणु0, 0, 0, 0, 0पूर्ण;
	u32						Value;
	u8						Pwr_Flag;
	u16						Avg_TSSI_Meas, TSSI_13dBm, Avg_TSSI_Meas_from_driver = 0;
	/*RT_STATUS				rtStatus = RT_STATUS_SUCCESS;*/
	bool rtStatus = true;
	u32						delta = 0;

	ग_लिखो_nic_byte(dev, 0x1ba, 0);

	priv->ieee80211->bdynamic_txघातer_enable = false;

	घातerlevelOFDM24G = (u8)(priv->Pwr_Track>>24);
	RF_Type = priv->rf_type;
	Value = (RF_Type<<8) | घातerlevelOFDM24G;

	RT_TRACE(COMP_POWER_TRACKING, "powerlevelOFDM24G = %x\n", घातerlevelOFDM24G);

	क्रम (j = 0; j <= 30; j++) अणु /* fill tx_cmd */
		tx_cmd.cmd_op = TXCMD_SET_TX_PWR_TRACKING;
		tx_cmd.cmd_length = माप(tx_cmd.cmd_op);
		tx_cmd.cmd_value = Value;
		rtStatus = SendTxCommandPacket(dev, &tx_cmd, माप(काष्ठा tx_config_cmd));
		अगर (rtStatus == RT_STATUS_FAILURE)
			RT_TRACE(COMP_POWER_TRACKING, "Set configuration with tx cmd queue fail!\n");
		usleep_range(1000, 2000);
		/*DbgPrपूर्णांक("hi, vivi, strange\n");*/
		क्रम (i = 0; i <= 30; i++) अणु
			पढ़ो_nic_byte(dev, 0x1ba, &Pwr_Flag);

			अगर (Pwr_Flag == 0) अणु
				usleep_range(1000, 2000);
				जारी;
			पूर्ण
			पढ़ो_nic_word(dev, 0x13c, &Avg_TSSI_Meas);
			अगर (Avg_TSSI_Meas == 0) अणु
				ग_लिखो_nic_byte(dev, 0x1ba, 0);
				अवरोध;
			पूर्ण

			क्रम (k = 0; k < 5; k++) अणु
				अगर (k != 4)
					पढ़ो_nic_byte(dev, 0x134+k, &पंचांगp_report[k]);
				अन्यथा
					पढ़ो_nic_byte(dev, 0x13e, &पंचांगp_report[k]);
				RT_TRACE(COMP_POWER_TRACKING, "TSSI_report_value = %d\n", पंचांगp_report[k]);
			पूर्ण

			/* check अगर the report value is right */
			क्रम (k = 0; k < 5; k++) अणु
				अगर (पंचांगp_report[k] <= 20) अणु
					vivअगरlag = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (vivअगरlag) अणु
				ग_लिखो_nic_byte(dev, 0x1ba, 0);
				vivअगरlag = false;
				RT_TRACE(COMP_POWER_TRACKING, "we filtered the data\n");
				क्रम (k = 0; k < 5; k++)
					पंचांगp_report[k] = 0;
				अवरोध;
			पूर्ण

			क्रम (k = 0; k < 5; k++)
				Avg_TSSI_Meas_from_driver += पंचांगp_report[k];

			Avg_TSSI_Meas_from_driver = Avg_TSSI_Meas_from_driver*100/5;
			RT_TRACE(COMP_POWER_TRACKING, "Avg_TSSI_Meas_from_driver = %d\n", Avg_TSSI_Meas_from_driver);
			TSSI_13dBm = priv->TSSI_13dBm;
			RT_TRACE(COMP_POWER_TRACKING, "TSSI_13dBm = %d\n", TSSI_13dBm);

			/*अगर (असल(Avg_TSSI_Meas_from_driver - TSSI_13dBm) <= E_FOR_TX_POWER_TRACK)*/
			/* For MacOS-compatible */
			अगर (Avg_TSSI_Meas_from_driver > TSSI_13dBm)
				delta = Avg_TSSI_Meas_from_driver - TSSI_13dBm;
			अन्यथा
				delta = TSSI_13dBm - Avg_TSSI_Meas_from_driver;

			अगर (delta <= E_FOR_TX_POWER_TRACK) अणु
				priv->ieee80211->bdynamic_txघातer_enable = true;
				ग_लिखो_nic_byte(dev, 0x1ba, 0);
				RT_TRACE(COMP_POWER_TRACKING, "tx power track is done\n");
				RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex = %d\n", priv->rfa_txघातertrackingindex);
				RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex_real = %d\n", priv->rfa_txघातertrackingindex_real);
				RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation_difference = %d\n", priv->cck_present_attenuation_dअगरference);
				RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation = %d\n", priv->cck_present_attenuation);
				वापस;
			पूर्ण
			अगर (Avg_TSSI_Meas_from_driver < TSSI_13dBm - E_FOR_TX_POWER_TRACK) अणु
				अगर (priv->rfa_txघातertrackingindex > 0) अणु
					priv->rfa_txघातertrackingindex--;
					अगर (priv->rfa_txघातertrackingindex_real > 4) अणु
						priv->rfa_txघातertrackingindex_real--;
						rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txघातertrackingindex_real].txbbgain_value);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (priv->rfa_txघातertrackingindex < 36) अणु
					priv->rfa_txघातertrackingindex++;
					priv->rfa_txघातertrackingindex_real++;
					rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txघातertrackingindex_real].txbbgain_value);
				पूर्ण
			पूर्ण
			priv->cck_present_attenuation_dअगरference
				= priv->rfa_txघातertrackingindex - priv->rfa_txघातertracking_शेष;

			अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				priv->cck_present_attenuation
					= priv->cck_present_attenuation_20Mशेष + priv->cck_present_attenuation_dअगरference;
			अन्यथा
				priv->cck_present_attenuation
					= priv->cck_present_attenuation_40Mशेष + priv->cck_present_attenuation_dअगरference;

			अगर (priv->cck_present_attenuation > -1 && priv->cck_present_attenuation < 23) अणु
				अगर (priv->ieee80211->current_network.channel == 14 && !priv->bcck_in_ch14) अणु
					priv->bcck_in_ch14 = true;
					dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
				पूर्ण अन्यथा अगर (priv->ieee80211->current_network.channel != 14 && priv->bcck_in_ch14) अणु
					priv->bcck_in_ch14 = false;
					dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
				पूर्ण अन्यथा
					dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
			पूर्ण
			RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex = %d\n", priv->rfa_txघातertrackingindex);
			RT_TRACE(COMP_POWER_TRACKING, "priv->rfa_txpowertrackingindex_real = %d\n", priv->rfa_txघातertrackingindex_real);
			RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation_difference = %d\n", priv->cck_present_attenuation_dअगरference);
			RT_TRACE(COMP_POWER_TRACKING, "priv->cck_present_attenuation = %d\n", priv->cck_present_attenuation);

			अगर (priv->cck_present_attenuation_dअगरference <= -12 || priv->cck_present_attenuation_dअगरference >= 24) अणु
				priv->ieee80211->bdynamic_txघातer_enable = true;
				ग_लिखो_nic_byte(dev, 0x1ba, 0);
				RT_TRACE(COMP_POWER_TRACKING, "tx power track--->limited\n");
				वापस;
			पूर्ण

			ग_लिखो_nic_byte(dev, 0x1ba, 0);
			Avg_TSSI_Meas_from_driver = 0;
			क्रम (k = 0; k < 5; k++)
				पंचांगp_report[k] = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	priv->ieee80211->bdynamic_txघातer_enable = true;
	ग_लिखो_nic_byte(dev, 0x1ba, 0);
पूर्ण

अटल व्योम dm_TXPowerTrackingCallback_ThermalMeter(काष्ठा net_device *dev)
अणु
#घोषणा ThermalMeterVal	9
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 पंचांगpRegA, TempCCk;
	u8 पंचांगpOFDMindex, पंचांगpCCKindex, पंचांगpCCK20Mindex, पंचांगpCCK40Mindex, पंचांगpval;
	पूर्णांक i = 0, CCKSwingNeedUpdate = 0;

	अगर (!priv->btxघातer_trackingInit) अणु
		/* Query OFDM शेष setting */
		पंचांगpRegA = rtl8192_QueryBBReg(dev, rOFDM0_XATxIQImbalance, bMaskDWord);
		क्रम (i = 0; i < OFDM_Table_Length; i++) अणु /* find the index */
			अगर (पंचांगpRegA == OFDMSwingTable[i]) अणु
				priv->OFDM_index = (u8)i;
				RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%x, OFDM_index=0x%x\n",
					rOFDM0_XATxIQImbalance, पंचांगpRegA, priv->OFDM_index);
			पूर्ण
		पूर्ण

		/* Query CCK शेष setting From 0xa22 */
		TempCCk = rtl8192_QueryBBReg(dev, rCCK0_TxFilter1, bMaskByte2);
		क्रम (i = 0; i < CCK_Table_length; i++) अणु
			अगर (TempCCk == (u32)CCKSwingTable_Ch1_Ch13[i][0]) अणु
				priv->CCK_index = (u8) i;
				RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%x, CCK_index=0x%x\n",
					rCCK0_TxFilter1, TempCCk, priv->CCK_index);
				अवरोध;
			पूर्ण
		पूर्ण
		priv->btxघातer_trackingInit = true;
		/*pHalData->TXPowercount = 0;*/
		वापस;
	पूर्ण

	/* ==========================
	 * this is only क्रम test, should be masked
	 * ==========================
	 */

	/* पढ़ो and filter out unreasonable value */
	पंचांगpRegA = rtl8192_phy_QueryRFReg(dev, RF90_PATH_A, 0x12, 0x078);	/* 0x12: RF Reg[10:7] */
	RT_TRACE(COMP_POWER_TRACKING, "Readback ThermalMeterA = %d\n", पंचांगpRegA);
	अगर (पंचांगpRegA < 3 || पंचांगpRegA > 13)
		वापस;
	अगर (पंचांगpRegA >= 12)	/* अगर over 12, TP will be bad when high temperature */
		पंचांगpRegA = 12;
	RT_TRACE(COMP_POWER_TRACKING, "Valid ThermalMeterA = %d\n", पंचांगpRegA);
	priv->ThermalMeter[0] = ThermalMeterVal;	/* We use fixed value by Bryant's suggestion */
	priv->ThermalMeter[1] = ThermalMeterVal;	/* We use fixed value by Bryant's suggestion */

	/* Get current RF-A temperature index */
	अगर (priv->ThermalMeter[0] >= (u8)पंचांगpRegA) अणु	/* lower temperature */
		पंचांगpOFDMindex = पंचांगpCCK20Mindex = 6+(priv->ThermalMeter[0]-(u8)पंचांगpRegA);
		पंचांगpCCK40Mindex = पंचांगpCCK20Mindex - 6;
		अगर (पंचांगpOFDMindex >= OFDM_Table_Length)
			पंचांगpOFDMindex = OFDM_Table_Length-1;
		अगर (पंचांगpCCK20Mindex >= CCK_Table_length)
			पंचांगpCCK20Mindex = CCK_Table_length-1;
		अगर (पंचांगpCCK40Mindex >= CCK_Table_length)
			पंचांगpCCK40Mindex = CCK_Table_length-1;
	पूर्ण अन्यथा अणु
		पंचांगpval = (u8)पंचांगpRegA - priv->ThermalMeter[0];

		अगर (पंचांगpval >= 6) अणु
			/* higher temperature */
			पंचांगpOFDMindex = 0;
			पंचांगpCCK20Mindex = 0;
		पूर्ण अन्यथा अणु
			/* max to +6dB */
			पंचांगpOFDMindex = 6 - पंचांगpval;
			पंचांगpCCK20Mindex = 6 - पंचांगpval;
		पूर्ण
		पंचांगpCCK40Mindex = 0;
	पूर्ण
	/*DbgPrपूर्णांक("%ddb, tmpOFDMindex = %d, tmpCCK20Mindex = %d, tmpCCK40Mindex = %d",
		((u1Byte)पंचांगpRegA - pHalData->ThermalMeter[0]),
		पंचांगpOFDMindex, पंचांगpCCK20Mindex, पंचांगpCCK40Mindex);*/
	अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)	/* 40M */
		पंचांगpCCKindex = पंचांगpCCK40Mindex;
	अन्यथा
		पंचांगpCCKindex = पंचांगpCCK20Mindex;

	अगर (priv->ieee80211->current_network.channel == 14 && !priv->bcck_in_ch14) अणु
		priv->bcck_in_ch14 = true;
		CCKSwingNeedUpdate = 1;
	पूर्ण अन्यथा अगर (priv->ieee80211->current_network.channel != 14 && priv->bcck_in_ch14) अणु
		priv->bcck_in_ch14 = false;
		CCKSwingNeedUpdate = 1;
	पूर्ण

	अगर (priv->CCK_index != पंचांगpCCKindex) अणु
		priv->CCK_index = पंचांगpCCKindex;
		CCKSwingNeedUpdate = 1;
	पूर्ण

	अगर (CCKSwingNeedUpdate) अणु
		/*DbgPrपूर्णांक("Update CCK Swing, CCK_index = %d\n", pHalData->CCK_index);*/
		dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
	पूर्ण
	अगर (priv->OFDM_index != पंचांगpOFDMindex) अणु
		priv->OFDM_index = पंचांगpOFDMindex;
		rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, OFDMSwingTable[priv->OFDM_index]);
		RT_TRACE(COMP_POWER_TRACKING, "Update OFDMSwing[%d] = 0x%x\n",
			priv->OFDM_index, OFDMSwingTable[priv->OFDM_index]);
	पूर्ण
	priv->txघातer_count = 0;
पूर्ण

व्योम dm_txघातer_trackingcallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा r8192_priv *priv = container_of(dwork, काष्ठा r8192_priv, txघातer_tracking_wq);
	काष्ठा net_device *dev = priv->ieee80211->dev;

	अगर (priv->bDcut)
		dm_TXPowerTrackingCallback_TSSI(dev);
	अन्यथा
		dm_TXPowerTrackingCallback_ThermalMeter(dev);
पूर्ण

अटल व्योम dm_InitializeTXPowerTracking_TSSI(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Initial the Tx BB index and mapping value */
	priv->txbbgain_table[0].txbb_iq_amplअगरygain =			12;
	priv->txbbgain_table[0].txbbgain_value = 0x7f8001fe;
	priv->txbbgain_table[1].txbb_iq_amplअगरygain =			11;
	priv->txbbgain_table[1].txbbgain_value = 0x788001e2;
	priv->txbbgain_table[2].txbb_iq_amplअगरygain =			10;
	priv->txbbgain_table[2].txbbgain_value = 0x71c001c7;
	priv->txbbgain_table[3].txbb_iq_amplअगरygain =			9;
	priv->txbbgain_table[3].txbbgain_value = 0x6b8001ae;
	priv->txbbgain_table[4].txbb_iq_amplअगरygain =		       8;
	priv->txbbgain_table[4].txbbgain_value = 0x65400195;
	priv->txbbgain_table[5].txbb_iq_amplअगरygain =		       7;
	priv->txbbgain_table[5].txbbgain_value = 0x5fc0017f;
	priv->txbbgain_table[6].txbb_iq_amplअगरygain =		       6;
	priv->txbbgain_table[6].txbbgain_value = 0x5a400169;
	priv->txbbgain_table[7].txbb_iq_amplअगरygain =		       5;
	priv->txbbgain_table[7].txbbgain_value = 0x55400155;
	priv->txbbgain_table[8].txbb_iq_amplअगरygain =		       4;
	priv->txbbgain_table[8].txbbgain_value = 0x50800142;
	priv->txbbgain_table[9].txbb_iq_amplअगरygain =		       3;
	priv->txbbgain_table[9].txbbgain_value = 0x4c000130;
	priv->txbbgain_table[10].txbb_iq_amplअगरygain =		       2;
	priv->txbbgain_table[10].txbbgain_value = 0x47c0011f;
	priv->txbbgain_table[11].txbb_iq_amplअगरygain =		       1;
	priv->txbbgain_table[11].txbbgain_value = 0x43c0010f;
	priv->txbbgain_table[12].txbb_iq_amplअगरygain =		       0;
	priv->txbbgain_table[12].txbbgain_value = 0x40000100;
	priv->txbbgain_table[13].txbb_iq_amplअगरygain =		       -1;
	priv->txbbgain_table[13].txbbgain_value = 0x3c8000f2;
	priv->txbbgain_table[14].txbb_iq_amplअगरygain =		     -2;
	priv->txbbgain_table[14].txbbgain_value = 0x390000e4;
	priv->txbbgain_table[15].txbb_iq_amplअगरygain =		     -3;
	priv->txbbgain_table[15].txbbgain_value = 0x35c000d7;
	priv->txbbgain_table[16].txbb_iq_amplअगरygain =		     -4;
	priv->txbbgain_table[16].txbbgain_value = 0x32c000cb;
	priv->txbbgain_table[17].txbb_iq_amplअगरygain =		     -5;
	priv->txbbgain_table[17].txbbgain_value = 0x300000c0;
	priv->txbbgain_table[18].txbb_iq_amplअगरygain =			    -6;
	priv->txbbgain_table[18].txbbgain_value = 0x2d4000b5;
	priv->txbbgain_table[19].txbb_iq_amplअगरygain =		     -7;
	priv->txbbgain_table[19].txbbgain_value = 0x2ac000ab;
	priv->txbbgain_table[20].txbb_iq_amplअगरygain =		     -8;
	priv->txbbgain_table[20].txbbgain_value = 0x288000a2;
	priv->txbbgain_table[21].txbb_iq_amplअगरygain =		     -9;
	priv->txbbgain_table[21].txbbgain_value = 0x26000098;
	priv->txbbgain_table[22].txbb_iq_amplअगरygain =		     -10;
	priv->txbbgain_table[22].txbbgain_value = 0x24000090;
	priv->txbbgain_table[23].txbb_iq_amplअगरygain =		     -11;
	priv->txbbgain_table[23].txbbgain_value = 0x22000088;
	priv->txbbgain_table[24].txbb_iq_amplअगरygain =		     -12;
	priv->txbbgain_table[24].txbbgain_value = 0x20000080;
	priv->txbbgain_table[25].txbb_iq_amplअगरygain =		     -13;
	priv->txbbgain_table[25].txbbgain_value = 0x1a00006c;
	priv->txbbgain_table[26].txbb_iq_amplअगरygain =		     -14;
	priv->txbbgain_table[26].txbbgain_value = 0x1c800072;
	priv->txbbgain_table[27].txbb_iq_amplअगरygain =		     -15;
	priv->txbbgain_table[27].txbbgain_value = 0x18000060;
	priv->txbbgain_table[28].txbb_iq_amplअगरygain =		     -16;
	priv->txbbgain_table[28].txbbgain_value = 0x19800066;
	priv->txbbgain_table[29].txbb_iq_amplअगरygain =		     -17;
	priv->txbbgain_table[29].txbbgain_value = 0x15800056;
	priv->txbbgain_table[30].txbb_iq_amplअगरygain =		     -18;
	priv->txbbgain_table[30].txbbgain_value = 0x26c0005b;
	priv->txbbgain_table[31].txbb_iq_amplअगरygain =		     -19;
	priv->txbbgain_table[31].txbbgain_value = 0x14400051;
	priv->txbbgain_table[32].txbb_iq_amplअगरygain =		     -20;
	priv->txbbgain_table[32].txbbgain_value = 0x24400051;
	priv->txbbgain_table[33].txbb_iq_amplअगरygain =		     -21;
	priv->txbbgain_table[33].txbbgain_value = 0x1300004c;
	priv->txbbgain_table[34].txbb_iq_amplअगरygain =		     -22;
	priv->txbbgain_table[34].txbbgain_value = 0x12000048;
	priv->txbbgain_table[35].txbb_iq_amplअगरygain =		     -23;
	priv->txbbgain_table[35].txbbgain_value = 0x11000044;
	priv->txbbgain_table[36].txbb_iq_amplअगरygain =		     -24;
	priv->txbbgain_table[36].txbbgain_value = 0x10000040;

	/* ccktxbb_valuearray[0] is 0xA22 [1] is 0xA24 ...[7] is 0xA29
	 * This Table is क्रम CH1~CH13
	 */
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[0] = 0x36;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[1] = 0x35;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[2] = 0x2e;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[3] = 0x25;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[4] = 0x1c;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[5] = 0x12;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[6] = 0x09;
	priv->cck_txbbgain_table[0].ccktxbb_valuearray[7] = 0x04;

	priv->cck_txbbgain_table[1].ccktxbb_valuearray[0] = 0x33;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[1] = 0x32;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[2] = 0x2b;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[3] = 0x23;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[4] = 0x1a;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[5] = 0x11;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[6] = 0x08;
	priv->cck_txbbgain_table[1].ccktxbb_valuearray[7] = 0x04;

	priv->cck_txbbgain_table[2].ccktxbb_valuearray[0] = 0x30;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[1] = 0x2f;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[2] = 0x29;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[3] = 0x21;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[4] = 0x19;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[5] = 0x10;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[6] = 0x08;
	priv->cck_txbbgain_table[2].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[3].ccktxbb_valuearray[0] = 0x2d;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[1] = 0x2d;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[2] = 0x27;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[3] = 0x1f;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[4] = 0x18;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[5] = 0x0f;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[6] = 0x08;
	priv->cck_txbbgain_table[3].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[4].ccktxbb_valuearray[0] = 0x2b;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[1] = 0x2a;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[2] = 0x25;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[3] = 0x1e;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[4] = 0x16;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[5] = 0x0e;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[6] = 0x07;
	priv->cck_txbbgain_table[4].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[5].ccktxbb_valuearray[0] = 0x28;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[1] = 0x28;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[2] = 0x22;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[3] = 0x1c;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[4] = 0x15;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[5] = 0x0d;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[6] = 0x07;
	priv->cck_txbbgain_table[5].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[6].ccktxbb_valuearray[0] = 0x26;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[1] = 0x25;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[2] = 0x21;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[3] = 0x1b;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[4] = 0x14;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[5] = 0x0d;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[6] = 0x06;
	priv->cck_txbbgain_table[6].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[7].ccktxbb_valuearray[0] = 0x24;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[1] = 0x23;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[2] = 0x1f;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[3] = 0x19;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[4] = 0x13;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[5] = 0x0c;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[6] = 0x06;
	priv->cck_txbbgain_table[7].ccktxbb_valuearray[7] = 0x03;

	priv->cck_txbbgain_table[8].ccktxbb_valuearray[0] = 0x22;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[1] = 0x21;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[2] = 0x1d;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[3] = 0x18;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[4] = 0x11;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[5] = 0x0b;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[6] = 0x06;
	priv->cck_txbbgain_table[8].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[9].ccktxbb_valuearray[0] = 0x20;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[1] = 0x20;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[2] = 0x1b;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[3] = 0x16;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[4] = 0x11;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[5] = 0x08;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[6] = 0x05;
	priv->cck_txbbgain_table[9].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[10].ccktxbb_valuearray[0] = 0x1f;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[1] = 0x1e;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[2] = 0x1a;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[3] = 0x15;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[4] = 0x10;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[5] = 0x0a;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[6] = 0x05;
	priv->cck_txbbgain_table[10].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[11].ccktxbb_valuearray[0] = 0x1d;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[1] = 0x1c;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[2] = 0x18;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[3] = 0x14;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[4] = 0x0f;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[5] = 0x0a;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[6] = 0x05;
	priv->cck_txbbgain_table[11].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[12].ccktxbb_valuearray[0] = 0x1b;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[1] = 0x1a;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[2] = 0x17;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[3] = 0x13;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[4] = 0x0e;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[5] = 0x09;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[6] = 0x04;
	priv->cck_txbbgain_table[12].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[13].ccktxbb_valuearray[0] = 0x1a;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[1] = 0x19;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[2] = 0x16;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[3] = 0x12;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[4] = 0x0d;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[5] = 0x09;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[6] = 0x04;
	priv->cck_txbbgain_table[13].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[14].ccktxbb_valuearray[0] = 0x18;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[1] = 0x17;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[2] = 0x15;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[3] = 0x11;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[4] = 0x0c;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[5] = 0x08;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[6] = 0x04;
	priv->cck_txbbgain_table[14].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[15].ccktxbb_valuearray[0] = 0x17;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[1] = 0x16;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[2] = 0x13;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[3] = 0x10;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[4] = 0x0c;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[5] = 0x08;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[6] = 0x04;
	priv->cck_txbbgain_table[15].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[16].ccktxbb_valuearray[0] = 0x16;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[1] = 0x15;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[2] = 0x12;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[3] = 0x0f;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[4] = 0x0b;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[5] = 0x07;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[6] = 0x04;
	priv->cck_txbbgain_table[16].ccktxbb_valuearray[7] = 0x01;

	priv->cck_txbbgain_table[17].ccktxbb_valuearray[0] = 0x14;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[1] = 0x14;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[2] = 0x11;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[3] = 0x0e;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[4] = 0x0b;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[5] = 0x07;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[17].ccktxbb_valuearray[7] = 0x02;

	priv->cck_txbbgain_table[18].ccktxbb_valuearray[0] = 0x13;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[1] = 0x13;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[2] = 0x10;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[3] = 0x0d;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[4] = 0x0a;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[5] = 0x06;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[18].ccktxbb_valuearray[7] = 0x01;

	priv->cck_txbbgain_table[19].ccktxbb_valuearray[0] = 0x12;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[1] = 0x12;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[2] = 0x0f;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[3] = 0x0c;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[4] = 0x09;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[5] = 0x06;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[19].ccktxbb_valuearray[7] = 0x01;

	priv->cck_txbbgain_table[20].ccktxbb_valuearray[0] = 0x11;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[1] = 0x11;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[2] = 0x0f;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[3] = 0x0c;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[4] = 0x09;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[5] = 0x06;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[20].ccktxbb_valuearray[7] = 0x01;

	priv->cck_txbbgain_table[21].ccktxbb_valuearray[0] = 0x10;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[1] = 0x10;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[2] = 0x0e;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[3] = 0x0b;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[4] = 0x08;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[5] = 0x05;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[21].ccktxbb_valuearray[7] = 0x01;

	priv->cck_txbbgain_table[22].ccktxbb_valuearray[0] = 0x0f;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[1] = 0x0f;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[2] = 0x0d;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[3] = 0x0b;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[4] = 0x08;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[5] = 0x05;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[6] = 0x03;
	priv->cck_txbbgain_table[22].ccktxbb_valuearray[7] = 0x01;

	/* ccktxbb_valuearray[0] is 0xA22 [1] is 0xA24 ...[7] is 0xA29
	 * This Table is क्रम CH14
	 */
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[0] = 0x36;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[1] = 0x35;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[2] = 0x2e;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[3] = 0x1b;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[0].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[0] = 0x33;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[1] = 0x32;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[2] = 0x2b;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[3] = 0x19;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[1].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[0] = 0x30;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[1] = 0x2f;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[2] = 0x29;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[3] = 0x18;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[2].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[0] = 0x2d;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[1] = 0x2d;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[2] = 0x27;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[3] = 0x17;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[3].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[0] = 0x2b;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[1] = 0x2a;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[2] = 0x25;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[3] = 0x15;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[4].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[0] = 0x28;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[1] = 0x28;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[2] = 0x22;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[3] = 0x14;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[5].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[0] = 0x26;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[1] = 0x25;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[2] = 0x21;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[3] = 0x13;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[6].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[0] = 0x24;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[1] = 0x23;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[2] = 0x1f;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[3] = 0x12;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[7].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[0] = 0x22;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[1] = 0x21;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[2] = 0x1d;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[3] = 0x11;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[8].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[0] = 0x20;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[1] = 0x20;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[2] = 0x1b;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[3] = 0x10;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[9].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[0] = 0x1f;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[1] = 0x1e;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[2] = 0x1a;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[3] = 0x0f;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[10].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[0] = 0x1d;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[1] = 0x1c;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[2] = 0x18;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[3] = 0x0e;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[11].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[0] = 0x1b;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[1] = 0x1a;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[2] = 0x17;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[3] = 0x0e;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[12].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[0] = 0x1a;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[1] = 0x19;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[2] = 0x16;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[3] = 0x0d;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[13].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[0] = 0x18;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[1] = 0x17;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[2] = 0x15;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[3] = 0x0c;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[14].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[0] = 0x17;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[1] = 0x16;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[2] = 0x13;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[3] = 0x0b;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[15].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[0] = 0x16;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[1] = 0x15;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[2] = 0x12;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[3] = 0x0b;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[16].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[0] = 0x14;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[1] = 0x14;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[2] = 0x11;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[3] = 0x0a;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[17].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[0] = 0x13;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[1] = 0x13;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[2] = 0x10;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[3] = 0x0a;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[18].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[0] = 0x12;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[1] = 0x12;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[2] = 0x0f;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[3] = 0x09;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[19].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[0] = 0x11;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[1] = 0x11;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[2] = 0x0f;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[3] = 0x09;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[20].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[0] = 0x10;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[1] = 0x10;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[2] = 0x0e;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[3] = 0x08;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[21].ccktxbb_valuearray[7] = 0x00;

	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[0] = 0x0f;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[1] = 0x0f;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[2] = 0x0d;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[3] = 0x08;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[4] = 0x00;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[5] = 0x00;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[6] = 0x00;
	priv->cck_txbbgain_ch14_table[22].ccktxbb_valuearray[7] = 0x00;

	priv->btxघातer_tracking = true;
	priv->txघातer_count       = 0;
	priv->btxघातer_trackingInit = false;
पूर्ण

अटल व्योम dm_InitializeTXPowerTracking_ThermalMeter(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Tx Power tracking by Thermal Meter requires Firmware R/W 3-wire. This mechanism
	 * can be enabled only when Firmware R/W 3-wire is enabled. Otherwise, frequent r/w
	 * 3-wire by driver causes RF to go पूर्णांकo a wrong state.
	 */
	अगर (priv->ieee80211->FwRWRF)
		priv->btxघातer_tracking = true;
	अन्यथा
		priv->btxघातer_tracking = false;
	priv->txघातer_count       = 0;
	priv->btxघातer_trackingInit = false;
पूर्ण

व्योम dm_initialize_txघातer_tracking(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->bDcut)
		dm_InitializeTXPowerTracking_TSSI(dev);
	अन्यथा
		dm_InitializeTXPowerTracking_ThermalMeter(dev);
पूर्ण /* dm_InitializeTXPowerTracking */

अटल व्योम dm_CheckTXPowerTracking_TSSI(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u32 tx_घातer_track_counter;

	अगर (!priv->btxघातer_tracking)
		वापस;
	अगर ((tx_घातer_track_counter % 30 == 0) && (tx_घातer_track_counter != 0))
		queue_delayed_work(priv->priv_wq, &priv->txघातer_tracking_wq, 0);
	tx_घातer_track_counter++;
पूर्ण

अटल व्योम dm_CheckTXPowerTracking_ThermalMeter(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u8	TM_Trigger;
	/*DbgPrपूर्णांक("dm_CheckTXPowerTracking()\n");*/
	अगर (!priv->btxघातer_tracking)
		वापस;
	अगर (priv->txघातer_count  <= 2) अणु
		priv->txघातer_count++;
		वापस;
	पूर्ण

	अगर (!TM_Trigger) अणु
		/* Attention!! You have to ग_लिखो all 12bits of data to RF, or it may cause RF to crash
		 * actually ग_लिखो reg0x02 bit1=0, then bit1=1.
		 * DbgPrपूर्णांक("Trigger ThermalMeter, write RF reg0x2 = 0x4d to 0x4f\n");
		 */
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4d);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4f);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4d);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4f);
		TM_Trigger = 1;
		वापस;
	पूर्ण
	/*DbgPrपूर्णांक("Schedule TxPowerTrackingWorkItem\n");*/
	queue_delayed_work(priv->priv_wq, &priv->txघातer_tracking_wq, 0);
	TM_Trigger = 0;
पूर्ण

अटल व्योम dm_check_txघातer_tracking(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/*अटल u32 tx_घातer_track_counter = 0;*/

#अगर_घोषित RTL8190P
	dm_CheckTXPowerTracking_TSSI(dev);
#अन्यथा
	अगर (priv->bDcut)
		dm_CheckTXPowerTracking_TSSI(dev);
	अन्यथा
		dm_CheckTXPowerTracking_ThermalMeter(dev);
#पूर्ण_अगर

पूर्ण	/* dm_CheckTXPowerTracking */

अटल व्योम dm_CCKTxPowerAdjust_TSSI(काष्ठा net_device *dev, bool  bInCH14)
अणु
	u32 TempVal;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Write 0xa22 0xa23 */
	TempVal = 0;
	अगर (!bInCH14) अणु
		/* Write 0xa22 0xa23 */
		TempVal =	priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[0] +
					(priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[1]<<8);

		rtl8192_setBBreg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		/* Write 0xa24 ~ 0xa27 */
		TempVal =	priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[2] +
					(priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[3]<<8) +
					(priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[4]<<16)+
					(priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[5]<<24);
		rtl8192_setBBreg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		/* Write 0xa28  0xa29 */
		TempVal =	priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[6] +
					(priv->cck_txbbgain_table[priv->cck_present_attenuation].ccktxbb_valuearray[7]<<8);

		rtl8192_setBBreg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
	पूर्ण अन्यथा अणु
		TempVal =	priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[0] +
					(priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[1]<<8);

		rtl8192_setBBreg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		/* Write 0xa24 ~ 0xa27 */
		TempVal =	priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[2] +
					(priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[3]<<8) +
					(priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[4]<<16)+
					(priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[5]<<24);
		rtl8192_setBBreg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		/* Write 0xa28  0xa29 */
		TempVal =	priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[6] +
					(priv->cck_txbbgain_ch14_table[priv->cck_present_attenuation].ccktxbb_valuearray[7]<<8);

		rtl8192_setBBreg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
	पूर्ण
पूर्ण

अटल व्योम dm_CCKTxPowerAdjust_ThermalMeter(काष्ठा net_device *dev, bool  bInCH14)
अणु
	u32 TempVal;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	TempVal = 0;
	अगर (!bInCH14) अणु
		/* Write 0xa22 0xa23 */
		TempVal =	CCKSwingTable_Ch1_Ch13[priv->CCK_index][0] +
					(CCKSwingTable_Ch1_Ch13[priv->CCK_index][1]<<8);
		rtl8192_setBBreg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK not chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter1, TempVal);
		/* Write 0xa24 ~ 0xa27 */
		TempVal =	CCKSwingTable_Ch1_Ch13[priv->CCK_index][2] +
					(CCKSwingTable_Ch1_Ch13[priv->CCK_index][3]<<8) +
					(CCKSwingTable_Ch1_Ch13[priv->CCK_index][4]<<16)+
					(CCKSwingTable_Ch1_Ch13[priv->CCK_index][5]<<24);
		rtl8192_setBBreg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK not chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter2, TempVal);
		/* Write 0xa28  0xa29 */
		TempVal =	CCKSwingTable_Ch1_Ch13[priv->CCK_index][6] +
					(CCKSwingTable_Ch1_Ch13[priv->CCK_index][7]<<8);

		rtl8192_setBBreg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK not chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_DebugPort, TempVal);
	पूर्ण अन्यथा अणु
		/*priv->CCKTxPowerAdjustCntNotCh14++;	cosa add क्रम debug.*/
		/* Write 0xa22 0xa23 */
		TempVal =	CCKSwingTable_Ch14[priv->CCK_index][0] +
					(CCKSwingTable_Ch14[priv->CCK_index][1]<<8);

		rtl8192_setBBreg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			 rCCK0_TxFilter1, TempVal);
		/* Write 0xa24 ~ 0xa27 */
		TempVal =	CCKSwingTable_Ch14[priv->CCK_index][2] +
					(CCKSwingTable_Ch14[priv->CCK_index][3]<<8) +
					(CCKSwingTable_Ch14[priv->CCK_index][4]<<16)+
					(CCKSwingTable_Ch14[priv->CCK_index][5]<<24);
		rtl8192_setBBreg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			 rCCK0_TxFilter2, TempVal);
		/* Write 0xa28  0xa29 */
		TempVal =	CCKSwingTable_Ch14[priv->CCK_index][6] +
					(CCKSwingTable_Ch14[priv->CCK_index][7]<<8);

		rtl8192_setBBreg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			 rCCK0_DebugPort, TempVal);
	पूर्ण
पूर्ण

व्योम dm_cck_txघातer_adjust(काष्ठा net_device *dev, bool binch14)
अणु	/*  dm_CCKTxPowerAdjust */
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->bDcut)
		dm_CCKTxPowerAdjust_TSSI(dev, binch14);
	अन्यथा
		dm_CCKTxPowerAdjust_ThermalMeter(dev, binch14);
पूर्ण

#अगर_अघोषित RTL8192U
अटल व्योम dm_txघातer_reset_recovery(
	काष्ठा net_device *dev
)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_POWER_TRACKING, "Start Reset Recovery ==>\n");
	rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txघातertrackingindex].txbbgain_value);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in 0xc80 is %08x\n", priv->txbbgain_table[priv->rfa_txघातertrackingindex].txbbgain_value);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in RFA_txPowerTrackingIndex is %x\n", priv->rfa_txघातertrackingindex);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery : RF A I/Q Amplify Gain is %ld\n", priv->txbbgain_table[priv->rfa_txघातertrackingindex].txbb_iq_amplअगरygain);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: CCK Attenuation is %d dB\n", priv->cck_present_attenuation);
	dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);

	rtl8192_setBBreg(dev, rOFDM0_XCTxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfc_txघातertrackingindex].txbbgain_value);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in 0xc90 is %08x\n", priv->txbbgain_table[priv->rfc_txघातertrackingindex].txbbgain_value);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in RFC_txPowerTrackingIndex is %x\n", priv->rfc_txघातertrackingindex);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery : RF C I/Q Amplify Gain is %ld\n", priv->txbbgain_table[priv->rfc_txघातertrackingindex].txbb_iq_amplअगरygain);

पूर्ण	/* dm_TXPowerResetRecovery */

व्योम dm_restore_dynamic_mechanism_state(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32	reg_ratr = priv->rate_adaptive.last_ratr;

	अगर (!priv->up) अणु
		RT_TRACE(COMP_RATE, "<---- dm_restore_dynamic_mechanism_state(): driver is going to unload\n");
		वापस;
	पूर्ण

	/* Restore previous state क्रम rate adaptive */
	अगर (priv->rate_adaptive.rate_adaptive_disabled)
		वापस;
	/* TODO: Only 11n mode is implemented currently, */
	अगर (!(priv->ieee80211->mode == WIRELESS_MODE_N_24G ||
	      priv->ieee80211->mode == WIRELESS_MODE_N_5G))
		वापस;

	अणु
			/* 2007/11/15 MH Copy from 8190PCI. */
			u32 ratr_value;

			ratr_value = reg_ratr;
			अगर (priv->rf_type == RF_1T2R) अणु	/* 1T2R, Spatial Stream 2 should be disabled */
				ratr_value &= ~(RATE_ALL_OFDM_2SS);
				/*DbgPrपूर्णांक("HW_VAR_TATR_0 from 0x%x ==> 0x%x\n", ((pu4Byte)(val))[0], ratr_value);*/
			पूर्ण
			/*DbgPrपूर्णांक("set HW_VAR_TATR_0 = 0x%x\n", ratr_value);*/
			/*cosa Platक्रमmEFIOWrite4Byte(Adapter, RATR0, ((pu4Byte)(val))[0]);*/
			ग_लिखो_nic_dword(dev, RATR0, ratr_value);
			ग_लिखो_nic_byte(dev, UFWP, 1);
	पूर्ण
	/* Restore TX Power Tracking Index */
	अगर (priv->btxघातer_trackingInit && priv->btxघातer_tracking)
		dm_txघातer_reset_recovery(dev);

	/* Restore BB Initial Gain */
	dm_bb_initialgain_restore(dev);

पूर्ण	/* DM_RestoreDynamicMechanismState */

अटल व्योम dm_bb_initialgain_restore(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 bit_mask = 0x7f; /* Bit0~ Bit6 */

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		वापस;

	/* Disable Initial Gain */
	/*PHY_SetBBReg(Adapter, UFWP, bMaskLWord, 0x800);*/
	rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	/* Only clear byte 1 and reग_लिखो. */
	rtl8192_setBBreg(dev, rOFDM0_XAAGCCore1, bit_mask, (u32)priv->initgain_backup.xaagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XBAGCCore1, bit_mask, (u32)priv->initgain_backup.xbagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XCAGCCore1, bit_mask, (u32)priv->initgain_backup.xcagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XDAGCCore1, bit_mask, (u32)priv->initgain_backup.xdagccore1);
	bit_mask  = bMaskByte2;
	rtl8192_setBBreg(dev, rCCK0_CCA, bit_mask, (u32)priv->initgain_backup.cca);

	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc50 is %x\n", priv->initgain_backup.xaagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc58 is %x\n", priv->initgain_backup.xbagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc60 is %x\n", priv->initgain_backup.xcagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc68 is %x\n", priv->initgain_backup.xdagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xa0a is %x\n", priv->initgain_backup.cca);
	/* Enable Initial Gain */
	/*PHY_SetBBReg(Adapter, UFWP, bMaskLWord, 0x100);*/
	rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	/* Only clear byte 1 and reग_लिखो. */

पूर्ण	/* dm_BBInitialGainRestore */

अटल व्योम dm_bb_initialgain_backup(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 bit_mask = bMaskByte0; /* Bit0~ Bit6 */

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		वापस;

	/*PHY_SetBBReg(Adapter, UFWP, bMaskLWord, 0x800);*/
	rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	/* Only clear byte 1 and reग_लिखो. */
	priv->initgain_backup.xaagccore1 = (u8)rtl8192_QueryBBReg(dev, rOFDM0_XAAGCCore1, bit_mask);
	priv->initgain_backup.xbagccore1 = (u8)rtl8192_QueryBBReg(dev, rOFDM0_XBAGCCore1, bit_mask);
	priv->initgain_backup.xcagccore1 = (u8)rtl8192_QueryBBReg(dev, rOFDM0_XCAGCCore1, bit_mask);
	priv->initgain_backup.xdagccore1 = (u8)rtl8192_QueryBBReg(dev, rOFDM0_XDAGCCore1, bit_mask);
	bit_mask  = bMaskByte2;
	priv->initgain_backup.cca = (u8)rtl8192_QueryBBReg(dev, rCCK0_CCA, bit_mask);

	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc50 is %x\n", priv->initgain_backup.xaagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc58 is %x\n", priv->initgain_backup.xbagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc60 is %x\n", priv->initgain_backup.xcagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc68 is %x\n", priv->initgain_backup.xdagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xa0a is %x\n", priv->initgain_backup.cca);

पूर्ण   /* dm_BBInitialGainBakcup */

#पूर्ण_अगर
/*-----------------------------------------------------------------------------
 * Function:	dm_dig_init()
 *
 * Overview:	Set DIG scheme init value.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/15/2008	amy		Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम dm_dig_init(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/* 2007/10/05 MH Disable DIG scheme now. Not tested. */
	dm_digtable.dig_enable_flag	= true;
	dm_digtable.dig_algorithm = DIG_ALGO_BY_RSSI;
	dm_digtable.dig_algorithm_चयन = 0;

	/* 2007/10/04 MH Define init gain threshold. */
	dm_digtable.dig_state		= DM_STA_DIG_MAX;
	dm_digtable.dig_highpwr_state	= DM_STA_DIG_MAX;

	dm_digtable.rssi_low_thresh	= DM_DIG_THRESH_LOW;
	dm_digtable.rssi_high_thresh	= DM_DIG_THRESH_HIGH;

	dm_digtable.rssi_high_घातer_lowthresh = DM_DIG_HIGH_PWR_THRESH_LOW;
	dm_digtable.rssi_high_घातer_highthresh = DM_DIG_HIGH_PWR_THRESH_HIGH;

	dm_digtable.rssi_val = 50;	/* क्रम new dig debug rssi value */
	dm_digtable.backoff_val = DM_DIG_BACKOFF;
	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		dm_digtable.rx_gain_range_min = DM_DIG_MIN_NETCORE;
	अन्यथा
		dm_digtable.rx_gain_range_min = DM_DIG_MIN;

पूर्ण	/* dm_dig_init */

/*-----------------------------------------------------------------------------
 * Function:	dm_ctrl_initgain_byrssi()
 *
 * Overview:	Driver must monitor RSSI and notअगरy firmware to change initial
 *				gain according to dअगरferent threshold. BB team provide the
 *				suggested solution.
 *
 * Input:			काष्ठा net_device *dev
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/27/2008	amy		Create Version 0 porting from winकरोws code.
 *---------------------------------------------------------------------------*/
अटल व्योम dm_ctrl_initgain_byrssi(काष्ठा net_device *dev)
अणु
	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
		dm_ctrl_initgain_byrssi_by_fwfalse_alarm(dev);
	अन्यथा अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		dm_ctrl_initgain_byrssi_by_driverrssi(dev);
	/* ; */
	अन्यथा
		वापस;
पूर्ण

अटल व्योम dm_ctrl_initgain_byrssi_by_driverrssi(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 i;
	अटल u8	fw_dig;

	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	/*DbgPrपूर्णांक("Dig by Sw Rssi\n");*/
	अगर (dm_digtable.dig_algorithm_चयन)	/* अगर चयनed algorithm, we have to disable FW Dig. */
		fw_dig = 0;

	अगर (fw_dig <= 3) अणु /* execute several बार to make sure the FW Dig is disabled */
		/* FW DIG Off */
		क्रम (i = 0; i < 3; i++)
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	/* Only clear byte 1 and reग_लिखो. */
		fw_dig++;
		dm_digtable.dig_state = DM_STA_DIG_OFF;	/* fw dig off. */
	पूर्ण

	अगर (priv->ieee80211->state == IEEE80211_LINKED)
		dm_digtable.cur_connect_state = DIG_CONNECT;
	अन्यथा
		dm_digtable.cur_connect_state = DIG_DISCONNECT;

	/*DbgPrपूर्णांक("DM_DigTable.PreConnectState = %d, DM_DigTable.CurConnectState = %d\n",
		DM_DigTable.PreConnectState, DM_DigTable.CurConnectState);*/

	dm_digtable.rssi_val = priv->undecorated_smoothed_pwdb;
	/*DbgPrपूर्णांक("DM_DigTable.Rssi_val = %d\n", DM_DigTable.Rssi_val);*/
	dm_initial_gain(dev);
	dm_pd_th(dev);
	dm_cs_ratio(dev);
	अगर (dm_digtable.dig_algorithm_चयन)
		dm_digtable.dig_algorithm_चयन = 0;
	dm_digtable.pre_connect_state = dm_digtable.cur_connect_state;

पूर्ण	/* dm_CtrlInitGainByRssi */

अटल व्योम dm_ctrl_initgain_byrssi_by_fwfalse_alarm(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u32 reset_cnt;
	u8 i;

	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		dm_digtable.dig_state = DM_STA_DIG_MAX;
		/* Fw DIG On. */
		क्रम (i = 0; i < 3; i++)
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	/* Only clear byte 1 and reग_लिखो.*/
		dm_digtable.dig_algorithm_चयन = 0;
	पूर्ण

	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		वापस;

	/* For smooth, we can not change DIG state. */
	अगर ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_low_thresh) &&
	    (priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_thresh))
		वापस;

	/*DbgPrपूर्णांक("Dig by Fw False Alarm\n");*/
	/*अगर (DM_DigTable.Dig_State == DM_STA_DIG_OFF)*/
	/*DbgPrपूर्णांक("DIG Check\n\r RSSI=%d LOW=%d HIGH=%d STATE=%d",
	pHalData->UndecoratedSmoothedPWDB, DM_DigTable.RssiLowThresh,
	DM_DigTable.RssiHighThresh, DM_DigTable.Dig_State);*/
	/* 1. When RSSI decrease, We have to judge अगर it is smaller than a threshold
	 * and then execute the step below.
	 */
	अगर (priv->undecorated_smoothed_pwdb <= dm_digtable.rssi_low_thresh) अणु
		/* 2008/02/05 MH When we execute silent reset, the DIG PHY parameters
		 * will be reset to init value. We must prevent the condition.
		 */
		अगर (dm_digtable.dig_state == DM_STA_DIG_OFF &&
		    (priv->reset_count == reset_cnt)) अणु
			वापस;
		पूर्ण
		reset_cnt = priv->reset_count;

		/* If DIG is off, DIG high घातer state must reset. */
		dm_digtable.dig_highpwr_state = DM_STA_DIG_MAX;
		dm_digtable.dig_state = DM_STA_DIG_OFF;

		/*  1.1 DIG Off. */
		rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	/*  Only clear byte 1 and reग_लिखो. */

		/*  1.2 Set initial gain. */
		ग_लिखो_nic_byte(dev, rOFDM0_XAAGCCore1, 0x17);
		ग_लिखो_nic_byte(dev, rOFDM0_XBAGCCore1, 0x17);
		ग_लिखो_nic_byte(dev, rOFDM0_XCAGCCore1, 0x17);
		ग_लिखो_nic_byte(dev, rOFDM0_XDAGCCore1, 0x17);

		/*  1.3 Lower PD_TH क्रम OFDM. */
		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
			/* 2008/01/11 MH 40MHZ 90/92 रेजिस्टर are not the same.
			 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
			 */
			ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x00);
			/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				ग_लिखो_nic_byte(pAdapter, rOFDM0_RxDetector1, 0x40);
			अन्यथा अगर (pAdapter->HardwareType == HARDWARE_TYPE_RTL8192E)
			अन्यथा
				Platक्रमmEFIOWrite1Byte(pAdapter, rOFDM0_RxDetector1, 0x40);
			*/
		पूर्ण अन्यथा
			ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x42);

		/* 1.4 Lower CS ratio क्रम CCK. */
		ग_लिखो_nic_byte(dev, 0xa0a, 0x08);

		/* 1.5 Higher EDCCA. */
		/*Platक्रमmEFIOWrite4Byte(pAdapter, rOFDM0_ECCAThreshold, 0x325);*/
		वापस;
	पूर्ण

	/* 2. When RSSI increase, We have to judge अगर it is larger than a threshold
	 * and then execute the step below.
	 */
	अगर (priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh) अणु
		u8 reset_flag = 0;

		अगर (dm_digtable.dig_state == DM_STA_DIG_ON &&
		    (priv->reset_count == reset_cnt)) अणु
			dm_ctrl_initgain_byrssi_highpwr(dev);
			वापस;
		पूर्ण
		अगर (priv->reset_count != reset_cnt)
			reset_flag = 1;

		reset_cnt = priv->reset_count;

		dm_digtable.dig_state = DM_STA_DIG_ON;
		/*DbgPrपूर्णांक("DIG ON\n\r");*/

		/* 2.1 Set initial gain.
		 * 2008/02/26 MH SD3-Jerry suggest to prevent dirty environment.
		 */
		अगर (reset_flag == 1) अणु
			ग_लिखो_nic_byte(dev, rOFDM0_XAAGCCore1, 0x2c);
			ग_लिखो_nic_byte(dev, rOFDM0_XBAGCCore1, 0x2c);
			ग_लिखो_nic_byte(dev, rOFDM0_XCAGCCore1, 0x2c);
			ग_लिखो_nic_byte(dev, rOFDM0_XDAGCCore1, 0x2c);
		पूर्ण अन्यथा अणु
			ग_लिखो_nic_byte(dev, rOFDM0_XAAGCCore1, 0x20);
			ग_लिखो_nic_byte(dev, rOFDM0_XBAGCCore1, 0x20);
			ग_लिखो_nic_byte(dev, rOFDM0_XCAGCCore1, 0x20);
			ग_लिखो_nic_byte(dev, rOFDM0_XDAGCCore1, 0x20);
		पूर्ण

		/* 2.2 Higher PD_TH क्रम OFDM. */
		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
			/* 2008/01/11 MH 40MHZ 90/92 रेजिस्टर are not the same.
			 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
			 */
			ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
			/*
			अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
			अन्यथा अगर (pAdapter->HardwareType == HARDWARE_TYPE_RTL8192E)
			अन्यथा
				Platक्रमmEFIOWrite1Byte(pAdapter, rOFDM0_RxDetector1, 0x42);
			*/
		पूर्ण अन्यथा
			ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x44);

		/* 2.3 Higher CS ratio क्रम CCK. */
		ग_लिखो_nic_byte(dev, 0xa0a, 0xcd);

		/* 2.4 Lower EDCCA.
		 * 2008/01/11 MH 90/92 series are the same.
		 */
		/*Platक्रमmEFIOWrite4Byte(pAdapter, rOFDM0_ECCAThreshold, 0x346);*/

		/* 2.5 DIG On. */
		rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	/*  Only clear byte 1 and reग_लिखो. */
	पूर्ण

	dm_ctrl_initgain_byrssi_highpwr(dev);

पूर्ण	/* dm_CtrlInitGainByRssi */

/*-----------------------------------------------------------------------------
 * Function:	dm_ctrl_initgain_byrssi_highpwr()
 *
 * Overview:
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/28/2008	amy		Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम dm_ctrl_initgain_byrssi_highpwr(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u32 reset_cnt_highpwr;

	/*  For smooth, we can not change high घातer DIG state in the range. */
	अगर ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_high_घातer_lowthresh) &&
		(priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_घातer_highthresh))
		वापस;

	/* 3. When RSSI >75% or <70%, it is a high घातer issue. We have to judge अगर
	 *    it is larger than a threshold and then execute the step below.
	 *
	 * 2008/02/05 MH SD3-Jerry Modअगरy PD_TH क्रम high घातer issue.
	 */
	अगर (priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_घातer_highthresh) अणु
		अगर (dm_digtable.dig_highpwr_state == DM_STA_DIG_ON &&
		    (priv->reset_count == reset_cnt_highpwr))
			वापस;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_ON;

		/* 3.1 Higher PD_TH क्रम OFDM क्रम high घातer state. */
		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
			ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x10);

			/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x41);
			*/

		पूर्ण अन्यथा
			ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x43);
	पूर्ण अन्यथा अणु
		अगर (dm_digtable.dig_highpwr_state == DM_STA_DIG_OFF &&
		    (priv->reset_count == reset_cnt_highpwr))
			वापस;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_OFF;

		अगर (priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_घातer_lowthresh &&
			 priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh) अणु
			/*  3.2 Recover PD_TH क्रम OFDM क्रम normal घातer region. */
			अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
				ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
				/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
					ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
				*/

			पूर्ण अन्यथा
				ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x44);
		पूर्ण
	पूर्ण

	reset_cnt_highpwr = priv->reset_count;

पूर्ण	/* dm_CtrlInitGainByRssiHighPwr */

अटल व्योम dm_initial_gain(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8					initial_gain = 0;
	अटल u8				initialized, क्रमce_ग_लिखो;
	अटल u32			reset_cnt;
	u8				पंचांगp;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (dm_digtable.pre_connect_state == dm_digtable.cur_connect_state) अणु
		अगर (dm_digtable.cur_connect_state == DIG_CONNECT) अणु
			अगर ((dm_digtable.rssi_val + 10 - dm_digtable.backoff_val) > DM_DIG_MAX)
				dm_digtable.cur_ig_value = DM_DIG_MAX;
			अन्यथा अगर ((dm_digtable.rssi_val+10-dm_digtable.backoff_val) < dm_digtable.rx_gain_range_min)
				dm_digtable.cur_ig_value = dm_digtable.rx_gain_range_min;
			अन्यथा
				dm_digtable.cur_ig_value = dm_digtable.rssi_val+10-dm_digtable.backoff_val;
		पूर्ण अन्यथा अणु	/* current state is disconnected */
			अगर (dm_digtable.cur_ig_value == 0)
				dm_digtable.cur_ig_value = priv->DefaultInitialGain[0];
			अन्यथा
				dm_digtable.cur_ig_value = dm_digtable.pre_ig_value;
		पूर्ण
	पूर्ण अन्यथा अणु /*  disconnected -> connected or connected -> disconnected */
		dm_digtable.cur_ig_value = priv->DefaultInitialGain[0];
		dm_digtable.pre_ig_value = 0;
	पूर्ण
	/*DbgPrपूर्णांक("DM_DigTable.CurIGValue = 0x%x, DM_DigTable.PreIGValue = 0x%x\n", DM_DigTable.CurIGValue, DM_DigTable.PreIGValue);*/

	/* अगर silent reset happened, we should reग_लिखो the values back */
	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण

	पढ़ो_nic_byte(dev, rOFDM0_XAAGCCore1, &पंचांगp);
	अगर (dm_digtable.pre_ig_value != पंचांगp)
		क्रमce_ग_लिखो = 1;

	अणु
		अगर ((dm_digtable.pre_ig_value != dm_digtable.cur_ig_value)
			|| !initialized || क्रमce_ग_लिखो) अणु
			initial_gain = (u8)dm_digtable.cur_ig_value;
			/*DbgPrपूर्णांक("Write initial gain = 0x%x\n", initial_gain);*/
			/*  Set initial gain. */
			ग_लिखो_nic_byte(dev, rOFDM0_XAAGCCore1, initial_gain);
			ग_लिखो_nic_byte(dev, rOFDM0_XBAGCCore1, initial_gain);
			ग_लिखो_nic_byte(dev, rOFDM0_XCAGCCore1, initial_gain);
			ग_लिखो_nic_byte(dev, rOFDM0_XDAGCCore1, initial_gain);
			dm_digtable.pre_ig_value = dm_digtable.cur_ig_value;
			initialized = 1;
			क्रमce_ग_लिखो = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dm_pd_th(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u8				initialized, क्रमce_ग_लिखो;
	अटल u32			reset_cnt;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (dm_digtable.pre_connect_state == dm_digtable.cur_connect_state) अणु
		अगर (dm_digtable.cur_connect_state == DIG_CONNECT) अणु
			अगर (dm_digtable.rssi_val >= dm_digtable.rssi_high_घातer_highthresh)
				dm_digtable.curpd_thstate = DIG_PD_AT_HIGH_POWER;
			अन्यथा अगर (dm_digtable.rssi_val <= dm_digtable.rssi_low_thresh)
				dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
			अन्यथा अगर ((dm_digtable.rssi_val >= dm_digtable.rssi_high_thresh) &&
					(dm_digtable.rssi_val < dm_digtable.rssi_high_घातer_lowthresh))
				dm_digtable.curpd_thstate = DIG_PD_AT_NORMAL_POWER;
			अन्यथा
				dm_digtable.curpd_thstate = dm_digtable.prepd_thstate;
		पूर्ण अन्यथा अणु
			dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
		पूर्ण
	पूर्ण अन्यथा अणु /* disconnected -> connected or connected -> disconnected */
		dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
	पूर्ण

	/*  अगर silent reset happened, we should reग_लिखो the values back */
	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण

	अणु
		अगर ((dm_digtable.prepd_thstate != dm_digtable.curpd_thstate) ||
		    (initialized <= 3) || क्रमce_ग_लिखो) अणु
			/*DbgPrपूर्णांक("Write PD_TH state = %d\n", DM_DigTable.CurPD_THState);*/
			अगर (dm_digtable.curpd_thstate == DIG_PD_AT_LOW_POWER) अणु
				/*  Lower PD_TH क्रम OFDM. */
				अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
					/* 2008/01/11 MH 40MHZ 90/92 रेजिस्टर are not the same.
					 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
					 */
					ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x00);
					/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x40);
					*/
				पूर्ण अन्यथा
					ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
			पूर्ण अन्यथा अगर (dm_digtable.curpd_thstate == DIG_PD_AT_NORMAL_POWER) अणु
				/* Higher PD_TH क्रम OFDM. */
				अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
					/* 2008/01/11 MH 40MHZ 90/92 रेजिस्टर are not the same.
					 * 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
					 */
					ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
					/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
					*/
				पूर्ण अन्यथा
					ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x44);
			पूर्ण अन्यथा अगर (dm_digtable.curpd_thstate == DIG_PD_AT_HIGH_POWER) अणु
				/* Higher PD_TH क्रम OFDM क्रम high घातer state. */
				अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
					ग_लिखो_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x10);
					/*अन्यथा अगर (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
						ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x41);
					*/
				पूर्ण अन्यथा
					ग_लिखो_nic_byte(dev, rOFDM0_RxDetector1, 0x43);
			पूर्ण
			dm_digtable.prepd_thstate = dm_digtable.curpd_thstate;
			अगर (initialized <= 3)
				initialized++;
			क्रमce_ग_लिखो = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल	व्योम dm_cs_ratio(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अटल u8				initialized, क्रमce_ग_लिखो;
	अटल u32			reset_cnt;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (dm_digtable.pre_connect_state == dm_digtable.cur_connect_state) अणु
		अगर (dm_digtable.cur_connect_state == DIG_CONNECT) अणु
			अगर (dm_digtable.rssi_val <= dm_digtable.rssi_low_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
			अन्यथा अगर (dm_digtable.rssi_val >= dm_digtable.rssi_high_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_HIGHER;
			अन्यथा
				dm_digtable.curcs_ratio_state = dm_digtable.precs_ratio_state;
		पूर्ण अन्यथा अणु
			dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
		पूर्ण
	पूर्ण अन्यथा	/* disconnected -> connected or connected -> disconnected */
		dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;

	/* अगर silent reset happened, we should reग_लिखो the values back */
	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण

	अणु
		अगर ((dm_digtable.precs_ratio_state != dm_digtable.curcs_ratio_state) ||
		    !initialized || क्रमce_ग_लिखो) अणु
			/*DbgPrपूर्णांक("Write CS_ratio state = %d\n", DM_DigTable.CurCS_ratioState);*/
			अगर (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_LOWER) अणु
				/*  Lower CS ratio क्रम CCK. */
				ग_लिखो_nic_byte(dev, 0xa0a, 0x08);
			पूर्ण अन्यथा अगर (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_HIGHER) अणु
				/*  Higher CS ratio क्रम CCK. */
				ग_लिखो_nic_byte(dev, 0xa0a, 0xcd);
			पूर्ण
			dm_digtable.precs_ratio_state = dm_digtable.curcs_ratio_state;
			initialized = 1;
			क्रमce_ग_लिखो = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dm_init_edca_turbo(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->bcurrent_turbo_EDCA = false;
	priv->ieee80211->bis_any_nonbepkts = false;
	priv->bis_cur_rdlstate = false;
पूर्ण	/* dm_init_edca_turbo */

अटल व्योम dm_check_edca_turbo(
	काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	/*PSTA_QOS			pStaQos = pMgntInfo->pStaQos;*/

	/* Keep past Tx/Rx packet count क्रम RT-to-RT EDCA turbo. */
	अटल अचिन्हित दीर्घ			lastTxOkCnt;
	अटल अचिन्हित दीर्घ			lastRxOkCnt;
	अचिन्हित दीर्घ				curTxOkCnt = 0;
	अचिन्हित दीर्घ				curRxOkCnt = 0;

	/* Do not be Turbo अगर it's under WiFi config and Qos Enabled, because the EDCA parameters
	 * should follow the settings from QAP. By Bruce, 2007-12-07.
	 */
	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		जाओ dm_CheckEdcaTurbo_EXIT;
	/* We करो not turn on EDCA turbo mode क्रम some AP that has IOT issue */
	अगर (priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		जाओ dm_CheckEdcaTurbo_EXIT;

	/*prपूर्णांकk("========>%s():bis_any_nonbepkts is %d\n", __func__, priv->bis_any_nonbepkts);*/
	/* Check the status क्रम current condition. */
	अगर (!priv->ieee80211->bis_any_nonbepkts) अणु
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		/* For RT-AP, we needs to turn it on when Rx>Tx */
		अगर (curRxOkCnt > 4*curTxOkCnt) अणु
			/*prपूर्णांकk("%s():curRxOkCnt > 4*curTxOkCnt\n");*/
			अगर (!priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA) अणु
				ग_लिखो_nic_dword(dev, EDCAPARA_BE, edca_setting_DL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*prपूर्णांकk("%s():curRxOkCnt < 4*curTxOkCnt\n");*/
			अगर (priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA) अणु
				ग_लिखो_nic_dword(dev, EDCAPARA_BE, edca_setting_UL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = false;
			पूर्ण
		पूर्ण

		priv->bcurrent_turbo_EDCA = true;
	पूर्ण अन्यथा अणु
		/* Turn Off EDCA turbo here.
		 * Restore original EDCA according to the declaration of AP.
		 */
		अगर (priv->bcurrent_turbo_EDCA) अणु
			u8	u1bAIFS;
			u32	u4bAcParam, op_limit, cw_max, cw_min;

			काष्ठा ieee80211_qos_parameters *qos_parameters = &priv->ieee80211->current_network.qos_data.parameters;
			u8 mode = priv->ieee80211->mode;

			/*  For Each समय updating EDCA parameter, reset EDCA turbo mode status. */
			dm_init_edca_turbo(dev);

			u1bAIFS = qos_parameters->aअगरs[0] * ((mode & (IEEE_G | IEEE_N_24G)) ? 9 : 20) + aSअगरsTime;

			op_limit = (u32)le16_to_cpu(qos_parameters->tx_op_limit[0]);
			cw_max   = (u32)le16_to_cpu(qos_parameters->cw_max[0]);
			cw_min   = (u32)le16_to_cpu(qos_parameters->cw_min[0]);

			op_limit <<= AC_PARAM_TXOP_LIMIT_OFFSET;
			cw_max   <<= AC_PARAM_ECW_MAX_OFFSET;
			cw_min   <<= AC_PARAM_ECW_MIN_OFFSET;
			u1bAIFS  <<= AC_PARAM_AIFS_OFFSET;

			u4bAcParam = op_limit | cw_max | cw_min | u1bAIFS;
			cpu_to_le32s(&u4bAcParam);

			ग_लिखो_nic_dword(dev, EDCAPARA_BE, u4bAcParam);

			/* Check ACM bit.
			 * If it is set, immediately set ACM control bit to करोwngrading AC क्रम passing WMM testplan. Annie, 2005-12-13.
			 */
			अणु
				/*  TODO:  Modअगरied this part and try to set acm control in only 1 IO processing!! */

				काष्ठा aci_aअगरsn *pAciAअगरsn = (काष्ठा aci_aअगरsn *)&(qos_parameters->aअगरs[0]);
				u8		AcmCtrl;

				पढ़ो_nic_byte(dev, AcmHwCtrl, &AcmCtrl);

				अगर (pAciAअगरsn->acm) अणु /*  acm bit is 1. */
					AcmCtrl |= AcmHw_BeqEn;
				पूर्ण अन्यथा अणु	/* ACM bit is 0. */
					AcmCtrl &= (~AcmHw_BeqEn);
				पूर्ण

				RT_TRACE(COMP_QOS, "SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n", AcmCtrl);
				ग_लिखो_nic_byte(dev, AcmHwCtrl, AcmCtrl);
			पूर्ण
			priv->bcurrent_turbo_EDCA = false;
		पूर्ण
	पूर्ण

dm_CheckEdcaTurbo_EXIT:
	/* Set variables क्रम next समय. */
	priv->ieee80211->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
पूर्ण	/* dm_CheckEdcaTurbo */

अटल व्योम dm_init_ctstoself(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->ieee80211->bCTSToSelfEnable = true;
	priv->ieee80211->CTSToSelfTH = CTS_TO_SELF_TH_VAL;
पूर्ण

अटल व्योम dm_ctstoself(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	अटल अचिन्हित दीर्घ				lastTxOkCnt;
	अटल अचिन्हित दीर्घ				lastRxOkCnt;
	अचिन्हित दीर्घ						curTxOkCnt = 0;
	अचिन्हित दीर्घ						curRxOkCnt = 0;

	अगर (!priv->ieee80211->bCTSToSelfEnable) अणु
		pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		वापस;
	पूर्ण
	/* 1. Uplink
	 * 2. Linksys350/Linksys300N
	 * 3. <50 disable, >55 enable
	 */

	अगर (pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) अणु
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		अगर (curRxOkCnt > 4*curTxOkCnt) अणु /* करोwnlink, disable CTS to self */
			pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
			/*DbgPrपूर्णांक("dm_CTSToSelf() ==> CTS to self disabled -- downlink\n");*/
		पूर्ण अन्यथा अणु /* uplink */
			pHTInfo->IOTAction |= HT_IOT_ACT_FORCED_CTS2SELF;
		पूर्ण

		lastTxOkCnt = priv->stats.txbytesunicast;
		lastRxOkCnt = priv->stats.rxbytesunicast;
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	dm_check_pbc_gpio()
 *
 * Overview:	Check अगर PBC button is pressed.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/28/2008	amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
अटल	व्योम	dm_check_pbc_gpio(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 पंचांगp1byte;

	पढ़ो_nic_byte(dev, GPI, &पंचांगp1byte);
	अगर (पंचांगp1byte == 0xff)
		वापस;

	अगर (पंचांगp1byte & BIT(6) || पंचांगp1byte & BIT(0)) अणु
		/* Here we only set bPbcPressed to TRUE
		 * After trigger PBC, the variable will be set to FALSE
		 */
		RT_TRACE(COMP_IO, "CheckPbcGPIO - PBC is pressed\n");
		priv->bpbc_pressed = true;
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	DM_RFPathCheckWorkItemCallBack()
 *
 * Overview:	Check अगर Current RF RX path is enabled
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	01/30/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम dm_rf_pathcheck_workitemcallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा r8192_priv *priv = container_of(dwork, काष्ठा r8192_priv, rfpath_check_wq);
	काष्ठा net_device *dev = priv->ieee80211->dev;
	/*bool bactually_set = false;*/
	u8 rfpath = 0, i;

	/* 2008/01/30 MH After discussing with SD3 Jerry, 0xc04/0xd04 रेजिस्टर will
	 * always be the same. We only पढ़ो 0xc04 now.
	 */
	पढ़ो_nic_byte(dev, 0xc04, &rfpath);

	/* Check Bit 0-3, it means अगर RF A-D is enabled. */
	क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
		अगर (rfpath & (0x01<<i))
			priv->brfpath_rxenable[i] = true;
		अन्यथा
			priv->brfpath_rxenable[i] = false;
	पूर्ण

	dm_rxpath_sel_byrssi(dev);
पूर्ण	/* DM_RFPathCheckWorkItemCallBack */

अटल व्योम dm_init_rxpath_selection(काष्ठा net_device *dev)
अणु
	u8 i;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		DM_RxPathSelTable.cck_method = CCK_RX_VERSION_2;
	अन्यथा
		DM_RxPathSelTable.cck_method = CCK_RX_VERSION_1;
	DM_RxPathSelTable.disabled_rf = 0;
	क्रम (i = 0; i < 4; i++) अणु
		DM_RxPathSelTable.rf_rssi[i] = 50;
		DM_RxPathSelTable.cck_pwdb_sta[i] = -64;
		DM_RxPathSelTable.rf_enable_rssi_th[i] = 100;
	पूर्ण
पूर्ण

अटल व्योम dm_rxpath_sel_byrssi(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8				i, max_rssi_index = 0, min_rssi_index = 0, sec_rssi_index = 0, rf_num = 0;
	u8				पंचांगp_max_rssi = 0, पंचांगp_min_rssi = 0, पंचांगp_sec_rssi = 0;
	u8				cck_शेष_Rx = 0x2;  /* RF-C */
	u8				cck_optional_Rx = 0x3; /* RF-D */
	दीर्घ				पंचांगp_cck_max_pwdb = 0, पंचांगp_cck_min_pwdb = 0, पंचांगp_cck_sec_pwdb = 0;
	u8				cck_rx_ver2_max_index = 0, cck_rx_ver2_min_index = 0, cck_rx_ver2_sec_index = 0;
	u8				cur_rf_rssi;
	दीर्घ				cur_cck_pwdb;
	अटल u8			disabled_rf_cnt, cck_Rx_Path_initialized;
	u8				update_cck_rx_path;

	अगर (priv->rf_type != RF_2T4R)
		वापस;

	अगर (!cck_Rx_Path_initialized) अणु
		पढ़ो_nic_byte(dev, 0xa07, &DM_RxPathSelTable.cck_rx_path);
		DM_RxPathSelTable.cck_rx_path &= 0xf;
		cck_Rx_Path_initialized = 1;
	पूर्ण

	पढ़ो_nic_byte(dev, 0xc04, &DM_RxPathSelTable.disabled_rf);
	DM_RxPathSelTable.disabled_rf = ~DM_RxPathSelTable.disabled_rf & 0xf;

	अगर (priv->ieee80211->mode == WIRELESS_MODE_B) अणु
		DM_RxPathSelTable.cck_method = CCK_RX_VERSION_2;	/* pure B mode, fixed cck version2 */
		/*DbgPrपूर्णांक("Pure B mode, use cck rx version2\n");*/
	पूर्ण

	/* decide max/sec/min rssi index */
	क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
		DM_RxPathSelTable.rf_rssi[i] = priv->stats.rx_rssi_percentage[i];

		अगर (priv->brfpath_rxenable[i]) अणु
			rf_num++;
			cur_rf_rssi = DM_RxPathSelTable.rf_rssi[i];

			अगर (rf_num == 1) अणु /* find first enabled rf path and the rssi values */
				/* initialize, set all rssi index to the same one */
				max_rssi_index = min_rssi_index = sec_rssi_index = i;
				पंचांगp_max_rssi = पंचांगp_min_rssi = पंचांगp_sec_rssi = cur_rf_rssi;
			पूर्ण अन्यथा अगर (rf_num == 2) अणु /* we pick up the max index first, and let sec and min to be the same one */
				अगर (cur_rf_rssi >= पंचांगp_max_rssi) अणु
					पंचांगp_max_rssi = cur_rf_rssi;
					max_rssi_index = i;
				पूर्ण अन्यथा अणु
					पंचांगp_sec_rssi = पंचांगp_min_rssi = cur_rf_rssi;
					sec_rssi_index = min_rssi_index = i;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (cur_rf_rssi > पंचांगp_max_rssi) अणु
					पंचांगp_sec_rssi = पंचांगp_max_rssi;
					sec_rssi_index = max_rssi_index;
					पंचांगp_max_rssi = cur_rf_rssi;
					max_rssi_index = i;
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_max_rssi) अणु	/* let sec and min poपूर्णांक to the dअगरferent index */
					पंचांगp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				पूर्ण अन्यथा अगर ((cur_rf_rssi < पंचांगp_max_rssi) && (cur_rf_rssi > पंचांगp_sec_rssi)) अणु
					पंचांगp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_sec_rssi) अणु
					अगर (पंचांगp_sec_rssi == पंचांगp_min_rssi) अणु
						/* let sec and min poपूर्णांक to the dअगरferent index */
						पंचांगp_sec_rssi = cur_rf_rssi;
						sec_rssi_index = i;
					पूर्ण अन्यथा अणु
						/* This हाल we करोn't need to set any index */
					पूर्ण
				पूर्ण अन्यथा अगर ((cur_rf_rssi < पंचांगp_sec_rssi) && (cur_rf_rssi > पंचांगp_min_rssi)) अणु
					/* This हाल we करोn't need to set any index */
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_min_rssi) अणु
					अगर (पंचांगp_sec_rssi == पंचांगp_min_rssi) अणु
						/* let sec and min poपूर्णांक to the dअगरferent index */
						पंचांगp_min_rssi = cur_rf_rssi;
						min_rssi_index = i;
					पूर्ण अन्यथा अणु
						/* This हाल we करोn't need to set any index */
					पूर्ण
				पूर्ण अन्यथा अगर (cur_rf_rssi < पंचांगp_min_rssi) अणु
					पंचांगp_min_rssi = cur_rf_rssi;
					min_rssi_index = i;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	rf_num = 0;
	/* decide max/sec/min cck pwdb index */
	अगर (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_2) अणु
		क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
			अगर (priv->brfpath_rxenable[i]) अणु
				rf_num++;
				cur_cck_pwdb =  DM_RxPathSelTable.cck_pwdb_sta[i];

				अगर (rf_num == 1) अणु	/* find first enabled rf path and the rssi values */
					/* initialize, set all rssi index to the same one */
					cck_rx_ver2_max_index = cck_rx_ver2_min_index = cck_rx_ver2_sec_index = i;
					पंचांगp_cck_max_pwdb = पंचांगp_cck_min_pwdb = पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
				पूर्ण अन्यथा अगर (rf_num == 2) अणु	/* we pick up the max index first, and let sec and min to be the same one */
					अगर (cur_cck_pwdb >= पंचांगp_cck_max_pwdb) अणु
						पंचांगp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					पूर्ण अन्यथा अणु
						पंचांगp_cck_sec_pwdb = पंचांगp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = cck_rx_ver2_min_index = i;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (cur_cck_pwdb > पंचांगp_cck_max_pwdb) अणु
						पंचांगp_cck_sec_pwdb = पंचांगp_cck_max_pwdb;
						cck_rx_ver2_sec_index = cck_rx_ver2_max_index;
						पंचांगp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					पूर्ण अन्यथा अगर (cur_cck_pwdb == पंचांगp_cck_max_pwdb) अणु
						/* let sec and min poपूर्णांक to the dअगरferent index */
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					पूर्ण अन्यथा अगर ((cur_cck_pwdb < पंचांगp_cck_max_pwdb) && (cur_cck_pwdb > पंचांगp_cck_sec_pwdb)) अणु
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					पूर्ण अन्यथा अगर (cur_cck_pwdb == पंचांगp_cck_sec_pwdb && पंचांगp_cck_sec_pwdb == पंचांगp_cck_min_pwdb) अणु
						/* let sec and min poपूर्णांक to the dअगरferent index */
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
						/* otherwise we करोn't need to set any index */
					पूर्ण अन्यथा अगर ((cur_cck_pwdb < पंचांगp_cck_sec_pwdb) && (cur_cck_pwdb > पंचांगp_cck_min_pwdb)) अणु
						/*  This हाल we करोn't need to set any index */
					पूर्ण अन्यथा अगर (cur_cck_pwdb == पंचांगp_cck_min_pwdb && पंचांगp_cck_sec_pwdb == पंचांगp_cck_min_pwdb) अणु
						/*  let sec and min poपूर्णांक to the dअगरferent index */
						पंचांगp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_min_index = i;
						/* otherwise we करोn't need to set any index */
					पूर्ण अन्यथा अगर (cur_cck_pwdb < पंचांगp_cck_min_pwdb) अणु
						पंचांगp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_min_index = i;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set CCK Rx path
	 * reg0xA07[3:2]=cck शेष rx path, reg0xa07[1:0]=cck optional rx path.
	 */
	update_cck_rx_path = 0;
	अगर (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_2) अणु
		cck_शेष_Rx = cck_rx_ver2_max_index;
		cck_optional_Rx = cck_rx_ver2_sec_index;
		अगर (पंचांगp_cck_max_pwdb != -64)
			update_cck_rx_path = 1;
	पूर्ण

	अगर (पंचांगp_min_rssi < RX_PATH_SELECTION_SS_TH_LOW && disabled_rf_cnt < 2) अणु
		अगर ((पंचांगp_max_rssi - पंचांगp_min_rssi) >= RX_PATH_SELECTION_DIFF_TH) अणु
			/* record the enabled rssi threshold */
			DM_RxPathSelTable.rf_enable_rssi_th[min_rssi_index] = पंचांगp_max_rssi+5;
			/* disable the BB Rx path, OFDM */
			rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0x1<<min_rssi_index, 0x0);	/* 0xc04[3:0] */
			rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0x1<<min_rssi_index, 0x0);	/* 0xd04[3:0] */
			disabled_rf_cnt++;
		पूर्ण
		अगर (DM_RxPathSelTable.cck_method == CCK_RX_VERSION_1) अणु
			cck_शेष_Rx = max_rssi_index;
			cck_optional_Rx = sec_rssi_index;
			अगर (पंचांगp_max_rssi)
				update_cck_rx_path = 1;
		पूर्ण
	पूर्ण

	अगर (update_cck_rx_path) अणु
		DM_RxPathSelTable.cck_rx_path = (cck_शेष_Rx<<2)|(cck_optional_Rx);
		rtl8192_setBBreg(dev, rCCK0_AFESetting, 0x0f000000, DM_RxPathSelTable.cck_rx_path);
	पूर्ण

	अगर (DM_RxPathSelTable.disabled_rf) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर ((DM_RxPathSelTable.disabled_rf >> i) & 0x1) अणु	/* disabled rf */
				अगर (पंचांगp_max_rssi >= DM_RxPathSelTable.rf_enable_rssi_th[i]) अणु
					/* enable the BB Rx path */
					/*DbgPrपूर्णांक("RF-%d is enabled.\n", 0x1<<i);*/
					rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0x1<<i, 0x1);	/* 0xc04[3:0] */
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0x1<<i, 0x1);	/* 0xd04[3:0] */
					DM_RxPathSelTable.rf_enable_rssi_th[i] = 100;
					disabled_rf_cnt--;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	dm_check_rx_path_selection()
 *
 * Overview:	Call a workitem to check current RXRF path and Rx Path selection by RSSI.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/28/2008	amy		Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम dm_check_rx_path_selection(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	queue_delayed_work(priv->priv_wq, &priv->rfpath_check_wq, 0);
पूर्ण	/* dm_CheckRxRFPath */

अटल व्योम dm_init_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->ieee80211->fsync_समय_पूर्णांकerval = 500;
	priv->ieee80211->fsync_rate_biपंचांगap = 0x0f000800;
	priv->ieee80211->fsync_rssi_threshold = 30;
	priv->ieee80211->bfsync_enable = false;
	priv->ieee80211->fsync_multiple_समयपूर्णांकerval = 3;
	priv->ieee80211->fsync_firstdअगरf_ratethreshold = 100;
	priv->ieee80211->fsync_seconddअगरf_ratethreshold = 200;
	priv->ieee80211->fsync_state = Default_Fsync;
	priv->framesyncMonitor = 1;	/* current शेष 0xc38 monitor on */
	समयr_setup(&priv->fsync_समयr, dm_fsync_समयr_callback, 0);
पूर्ण

अटल व्योम dm_deInit_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	del_समयr_sync(&priv->fsync_समयr);
पूर्ण

व्योम dm_fsync_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा r8192_priv *priv = from_समयr(priv, t, fsync_समयr);
	काष्ठा net_device *dev = priv->ieee80211->dev;
	u32 rate_index, rate_count = 0, rate_count_dअगरf = 0;
	bool		bSwitchFromCountDअगरf = false;
	bool		bDoubleTimeInterval = false;

	अगर (priv->ieee80211->state == IEEE80211_LINKED &&
	    priv->ieee80211->bfsync_enable &&
		(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_CDD_FSYNC)) अणु
		/* Count rate 54, MCS [7], [12, 13, 14, 15] */
		u32 rate_biपंचांगap;

		क्रम (rate_index = 0; rate_index <= 27; rate_index++) अणु
			rate_biपंचांगap  = 1 << rate_index;
			अगर (priv->ieee80211->fsync_rate_biपंचांगap &  rate_biपंचांगap)
				rate_count += priv->stats.received_rate_histogram[1][rate_index];
		पूर्ण

		अगर (rate_count < priv->rate_record)
			rate_count_dअगरf = 0xffffffff - rate_count + priv->rate_record;
		अन्यथा
			rate_count_dअगरf = rate_count - priv->rate_record;
		अगर (rate_count_dअगरf < priv->rateCountDअगरfRecord) अणु
			u32 DअगरfNum = priv->rateCountDअगरfRecord - rate_count_dअगरf;
			/* Continue count */
			अगर (DअगरfNum >= priv->ieee80211->fsync_seconddअगरf_ratethreshold)
				priv->ContinueDअगरfCount++;
			अन्यथा
				priv->ContinueDअगरfCount = 0;

			/* Continue count over */
			अगर (priv->ContinueDअगरfCount >= 2) अणु
				bSwitchFromCountDअगरf = true;
				priv->ContinueDअगरfCount = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Stop the जारीd count */
			priv->ContinueDअगरfCount = 0;
		पूर्ण

		/* If Count dअगरf <= FsyncRateCountThreshold */
		अगर (rate_count_dअगरf <= priv->ieee80211->fsync_firstdअगरf_ratethreshold) अणु
			bSwitchFromCountDअगरf = true;
			priv->ContinueDअगरfCount = 0;
		पूर्ण
		priv->rate_record = rate_count;
		priv->rateCountDअगरfRecord = rate_count_dअगरf;
		RT_TRACE(COMP_HALDM, "rateRecord %d rateCount %d, rateCountdiff %d bSwitchFsync %d\n", priv->rate_record, rate_count, rate_count_dअगरf, priv->bचयन_fsync);
		/* अगर we never receive those mcs rate and rssi > 30 % then चयन fsyn */
		अगर (priv->undecorated_smoothed_pwdb > priv->ieee80211->fsync_rssi_threshold && bSwitchFromCountDअगरf) अणु
			bDoubleTimeInterval = true;
			priv->bचयन_fsync = !priv->bचयन_fsync;
			अगर (priv->bचयन_fsync) अणु
				ग_लिखो_nic_byte(dev, 0xC36, 0x1c);
				ग_लिखो_nic_byte(dev, 0xC3e, 0x90);
			पूर्ण अन्यथा अणु
				ग_लिखो_nic_byte(dev, 0xC36, 0x5c);
				ग_लिखो_nic_byte(dev, 0xC3e, 0x96);
			पूर्ण
		पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb <= priv->ieee80211->fsync_rssi_threshold) अणु
			अगर (priv->bचयन_fsync) अणु
				priv->bचयन_fsync  = false;
				ग_लिखो_nic_byte(dev, 0xC36, 0x5c);
				ग_लिखो_nic_byte(dev, 0xC3e, 0x96);
			पूर्ण
		पूर्ण
		अगर (bDoubleTimeInterval) अणु
			अगर (समयr_pending(&priv->fsync_समयr))
				del_समयr_sync(&priv->fsync_समयr);
			priv->fsync_समयr.expires = jअगरfies +
				msecs_to_jअगरfies(priv->ieee80211->fsync_समय_पूर्णांकerval*priv->ieee80211->fsync_multiple_समयपूर्णांकerval);
			add_समयr(&priv->fsync_समयr);
		पूर्ण अन्यथा अणु
			अगर (समयr_pending(&priv->fsync_समयr))
				del_समयr_sync(&priv->fsync_समयr);
			priv->fsync_समयr.expires = jअगरfies +
				msecs_to_jअगरfies(priv->ieee80211->fsync_समय_पूर्णांकerval);
			add_समयr(&priv->fsync_समयr);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Let Register वापस to शेष value; */
		अगर (priv->bचयन_fsync) अणु
			priv->bचयन_fsync  = false;
			ग_लिखो_nic_byte(dev, 0xC36, 0x5c);
			ग_लिखो_nic_byte(dev, 0xC3e, 0x96);
		पूर्ण
		priv->ContinueDअगरfCount = 0;
		ग_लिखो_nic_dword(dev, rOFDM0_RxDetector2, 0x465c52cd);
	पूर्ण
	RT_TRACE(COMP_HALDM, "ContinueDiffCount %d\n", priv->ContinueDअगरfCount);
	RT_TRACE(COMP_HALDM, "rateRecord %d rateCount %d, rateCountdiff %d bSwitchFsync %d\n", priv->rate_record, rate_count, rate_count_dअगरf, priv->bचयन_fsync);
पूर्ण

अटल व्योम dm_StartHWFsync(काष्ठा net_device *dev)
अणु
	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	ग_लिखो_nic_dword(dev, rOFDM0_RxDetector2, 0x465c12cf);
	ग_लिखो_nic_byte(dev, 0xc3b, 0x41);
पूर्ण

अटल व्योम dm_EndSWFsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	del_समयr_sync(&(priv->fsync_समयr));

	/* Let Register वापस to शेष value; */
	अगर (priv->bचयन_fsync) अणु
		priv->bचयन_fsync  = false;

		ग_लिखो_nic_byte(dev, 0xC36, 0x5c);

		ग_लिखो_nic_byte(dev, 0xC3e, 0x96);
	पूर्ण

	priv->ContinueDअगरfCount = 0;
	ग_लिखो_nic_dword(dev, rOFDM0_RxDetector2, 0x465c52cd);
पूर्ण

अटल व्योम dm_StartSWFsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32			rateIndex;
	u32			rateBiपंचांगap;

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	/* Initial rate record to zero, start to record. */
	priv->rate_record = 0;
	/* Initialize जारी dअगरf count to zero, start to record. */
	priv->ContinueDअगरfCount = 0;
	priv->rateCountDअगरfRecord = 0;
	priv->bचयन_fsync  = false;

	अगर (priv->ieee80211->mode == WIRELESS_MODE_N_24G) अणु
		priv->ieee80211->fsync_firstdअगरf_ratethreshold = 600;
		priv->ieee80211->fsync_seconddअगरf_ratethreshold = 0xffff;
	पूर्ण अन्यथा अणु
		priv->ieee80211->fsync_firstdअगरf_ratethreshold = 200;
		priv->ieee80211->fsync_seconddअगरf_ratethreshold = 200;
	पूर्ण
	क्रम (rateIndex = 0; rateIndex <= 27; rateIndex++) अणु
		rateBiपंचांगap = 1 << rateIndex;
		अगर (priv->ieee80211->fsync_rate_biपंचांगap &  rateBiपंचांगap)
			priv->rate_record += priv->stats.received_rate_histogram[1][rateIndex];
	पूर्ण
	अगर (समयr_pending(&priv->fsync_समयr))
		del_समयr_sync(&priv->fsync_समयr);
	priv->fsync_समयr.expires = jअगरfies +
			msecs_to_jअगरfies(priv->ieee80211->fsync_समय_पूर्णांकerval);
	add_समयr(&priv->fsync_समयr);

	ग_लिखो_nic_dword(dev, rOFDM0_RxDetector2, 0x465c12cd);
पूर्ण

अटल व्योम dm_EndHWFsync(काष्ठा net_device *dev)
अणु
	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	ग_लिखो_nic_dword(dev, rOFDM0_RxDetector2, 0x465c52cd);
	ग_लिखो_nic_byte(dev, 0xc3b, 0x49);
पूर्ण

व्योम dm_check_fsync(काष्ठा net_device *dev)
अणु
#घोषणा	RegC38_Default				0
#घोषणा	RegC38_NonFsync_Other_AP		1
#घोषणा	RegC38_Fsync_AP_BCM			2
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/*u32			framesyncC34;*/
	अटल u8		reg_c38_State = RegC38_Default;
	अटल u32	reset_cnt;

	RT_TRACE(COMP_HALDM, "RSSI %d TimeInterval %d MultipleTimeInterval %d\n", priv->ieee80211->fsync_rssi_threshold, priv->ieee80211->fsync_समय_पूर्णांकerval, priv->ieee80211->fsync_multiple_समयपूर्णांकerval);
	RT_TRACE(COMP_HALDM, "RateBitmap 0x%x FirstDiffRateThreshold %d SecondDiffRateThreshold %d\n", priv->ieee80211->fsync_rate_biपंचांगap, priv->ieee80211->fsync_firstdअगरf_ratethreshold, priv->ieee80211->fsync_seconddअगरf_ratethreshold);

	अगर (priv->ieee80211->state == IEEE80211_LINKED &&
		(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_CDD_FSYNC)) अणु
		अगर (priv->ieee80211->bfsync_enable == 0) अणु
			चयन (priv->ieee80211->fsync_state) अणु
			हाल Default_Fsync:
				dm_StartHWFsync(dev);
				priv->ieee80211->fsync_state = HW_Fsync;
				अवरोध;
			हाल SW_Fsync:
				dm_EndSWFsync(dev);
				dm_StartHWFsync(dev);
				priv->ieee80211->fsync_state = HW_Fsync;
				अवरोध;
			हाल HW_Fsync:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (priv->ieee80211->fsync_state) अणु
			हाल Default_Fsync:
				dm_StartSWFsync(dev);
				priv->ieee80211->fsync_state = SW_Fsync;
				अवरोध;
			हाल HW_Fsync:
				dm_EndHWFsync(dev);
				dm_StartSWFsync(dev);
				priv->ieee80211->fsync_state = SW_Fsync;
				अवरोध;
			हाल SW_Fsync:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (priv->framesyncMonitor) अणु
			अगर (reg_c38_State != RegC38_Fsync_AP_BCM) अणु
				/* For broadcom AP we ग_लिखो dअगरferent शेष value */
				ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, 0x95);

				reg_c38_State = RegC38_Fsync_AP_BCM;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (priv->ieee80211->fsync_state) अणु
		हाल HW_Fsync:
			dm_EndHWFsync(dev);
			priv->ieee80211->fsync_state = Default_Fsync;
			अवरोध;
		हाल SW_Fsync:
			dm_EndSWFsync(dev);
			priv->ieee80211->fsync_state = Default_Fsync;
			अवरोध;
		हाल Default_Fsync:
		शेष:
			अवरोध;
		पूर्ण

		अगर (priv->framesyncMonitor) अणु
			अगर (priv->ieee80211->state == IEEE80211_LINKED) अणु
				अगर (priv->undecorated_smoothed_pwdb <= REG_C38_TH) अणु
					अगर (reg_c38_State != RegC38_NonFsync_Other_AP) अणु
						ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, 0x90);

						reg_c38_State = RegC38_NonFsync_Other_AP;
					पूर्ण
				पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb >= (REG_C38_TH + 5)) अणु
					अगर (reg_c38_State) अणु
						ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
						reg_c38_State = RegC38_Default;
						/*DbgPrपूर्णांक("Fsync is idle, rssi>=40, write 0xc38 = 0x%x\n", pHalData->framesync);*/
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (reg_c38_State) अणु
					ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
					reg_c38_State = RegC38_Default;
					/*DbgPrपूर्णांक("Fsync is idle, not connected, write 0xc38 = 0x%x\n", pHalData->framesync);*/
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (priv->framesyncMonitor) अणु
		अगर (priv->reset_count != reset_cnt) अणु /* After silent reset, the reg_c38_State will be वापसed to शेष value */
			ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
			reg_c38_State = RegC38_Default;
			reset_cnt = priv->reset_count;
			/*DbgPrपूर्णांक("reg_c38_State = 0 for silent reset.\n");*/
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (reg_c38_State) अणु
			ग_लिखो_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
			reg_c38_State = RegC38_Default;
			/*DbgPrपूर्णांक("framesync no monitor, write 0xc38 = 0x%x\n", pHalData->framesync);*/
		पूर्ण
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	dm_shaकरोw_init()
 *
 * Overview:	Store all NIC MAC/BB रेजिस्टर content.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	05/29/2008	amy		Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------*/
व्योम dm_shaकरोw_init(काष्ठा net_device *dev)
अणु
	u8	page;
	u16	offset;

	क्रम (page = 0; page < 5; page++)
		क्रम (offset = 0; offset < 256; offset++) अणु
			पढ़ो_nic_byte(dev, offset + page * 256, &dm_shaकरोw[page][offset]);
			/*DbgPrपूर्णांक("P-%d/O-%02x=%02x\r\n", page, offset, DM_Shaकरोw[page][offset]);*/
		पूर्ण

	क्रम (page = 8; page < 11; page++)
		क्रम (offset = 0; offset < 256; offset++)
			पढ़ो_nic_byte(dev, offset + page * 256, &dm_shaकरोw[page][offset]);

	क्रम (page = 12; page < 15; page++)
		क्रम (offset = 0; offset < 256; offset++)
			पढ़ो_nic_byte(dev, offset + page * 256, &dm_shaकरोw[page][offset]);

पूर्ण   /* dm_shaकरोw_init */

/*---------------------------Define function prototype------------------------*/
/*-----------------------------------------------------------------------------
 * Function:	DM_DynamicTxPower()
 *
 * Overview:	Detect Signal strength to control TX Registry
			Tx Power Control For Near/Far Range
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	03/06/2008	Jacken	Create Version 0.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम dm_init_dynamic_txघातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Initial TX Power Control क्रम near/far range , add by amy 2008/05/15, porting from winकरोws code. */
	priv->ieee80211->bdynamic_txघातer_enable = true;    /* Default to enable Tx Power Control */
	priv->bLastDTPFlag_High = false;
	priv->bLastDTPFlag_Low = false;
	priv->bDynamicTxHighPower = false;
	priv->bDynamicTxLowPower = false;
पूर्ण

अटल व्योम dm_dynamic_txघातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	अचिन्हित पूर्णांक txhiघातer_threshold = 0;
	अचिन्हित पूर्णांक txlowघातer_threshold = 0;

	अगर (!priv->ieee80211->bdynamic_txघातer_enable) अणु
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
		वापस;
	पूर्ण
	/*prपूर्णांकk("priv->ieee80211->current_network.unknown_cap_exist is %d , priv->ieee80211->current_network.broadcom_cap_exist is %d\n", priv->ieee80211->current_network.unknown_cap_exist, priv->ieee80211->current_network.broadcom_cap_exist);*/
	अगर ((priv->ieee80211->current_network.atheros_cap_exist) && (priv->ieee80211->mode == IEEE_G)) अणु
		txhiघातer_threshold = TX_POWER_ATHEROAP_THRESH_HIGH;
		txlowघातer_threshold = TX_POWER_ATHEROAP_THRESH_LOW;
	पूर्ण अन्यथा अणु
		txhiघातer_threshold = TX_POWER_NEAR_FIELD_THRESH_HIGH;
		txlowघातer_threshold = TX_POWER_NEAR_FIELD_THRESH_LOW;
	पूर्ण

	/*prपूर्णांकk("=======>%s(): txhipower_threshold is %d, txlowpower_threshold is %d\n", __func__, txhiघातer_threshold, txlowघातer_threshold);*/
	RT_TRACE(COMP_TXAGC, "priv->undecorated_smoothed_pwdb = %ld\n", priv->undecorated_smoothed_pwdb);

	अगर (priv->ieee80211->state == IEEE80211_LINKED) अणु
		अगर (priv->undecorated_smoothed_pwdb >= txhiघातer_threshold) अणु
			priv->bDynamicTxHighPower = true;
			priv->bDynamicTxLowPower = false;
		पूर्ण अन्यथा अणु
			/* high घातer state check */
			अगर (priv->undecorated_smoothed_pwdb < txlowघातer_threshold && priv->bDynamicTxHighPower)
				priv->bDynamicTxHighPower = false;

			/* low घातer state check */
			अगर (priv->undecorated_smoothed_pwdb < 35)
				priv->bDynamicTxLowPower = true;
			अन्यथा अगर (priv->undecorated_smoothed_pwdb >= 40)
				priv->bDynamicTxLowPower = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*pHalData->bTXPowerCtrlक्रमNearFarRange = !pHalData->bTXPowerCtrlक्रमNearFarRange;*/
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
	पूर्ण

	अगर ((priv->bDynamicTxHighPower != priv->bLastDTPFlag_High) ||
		(priv->bDynamicTxLowPower != priv->bLastDTPFlag_Low)) अणु
		RT_TRACE(COMP_TXAGC, "SetTxPowerLevel8190()  channel = %d\n", priv->ieee80211->current_network.channel);

#अगर  defined(RTL8190P) || defined(RTL8192E)
		SetTxPowerLevel8190(Adapter, pHalData->CurrentChannel);
#पूर्ण_अगर

		rtl8192_phy_setTxPower(dev, priv->ieee80211->current_network.channel);
		/*pHalData->bStartTxCtrlByTPCNFR = FALSE;    Clear th flag of Set TX Power from Sitesurvey*/
	पूर्ण
	priv->bLastDTPFlag_High = priv->bDynamicTxHighPower;
	priv->bLastDTPFlag_Low = priv->bDynamicTxLowPower;

पूर्ण	/* dm_dynamic_txघातer */

/* added by vivi, क्रम पढ़ो tx rate and retrycount */
अटल व्योम dm_check_txrateandretrycount(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	/* क्रम 11n tx rate */
	/*priv->stats.CurrentShowTxate = पढ़ो_nic_byte(dev, CURRENT_TX_RATE_REG);*/
	पढ़ो_nic_byte(dev, CURRENT_TX_RATE_REG, &ieee->sofपंचांगac_stats.CurrentShowTxate);
	/*prपूर्णांकk("=============>tx_rate_reg:%x\n", ieee->sofपंचांगac_stats.CurrentShowTxate);*/
	/* क्रम initial tx rate */
	/*priv->stats.last_packet_rate = पढ़ो_nic_byte(dev, INITIAL_TX_RATE_REG);*/
	पढ़ो_nic_byte(dev, INITIAL_TX_RATE_REG, &ieee->sofपंचांगac_stats.last_packet_rate);
	/* क्रम tx tx retry count */
	/*priv->stats.txretrycount = पढ़ो_nic_dword(dev, TX_RETRY_COUNT_REG);*/
	पढ़ो_nic_dword(dev, TX_RETRY_COUNT_REG, &ieee->sofपंचांगac_stats.txretrycount);
पूर्ण

अटल व्योम dm_send_rssi_tofw(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* If we test अक्षरiot, we should stop the TX command ?
	 * Because 92E will always silent reset when we send tx command. We use रेजिस्टर
	 * 0x1e0(byte) to notअगरy driver.
	 */
	ग_लिखो_nic_byte(dev, DRIVER_RSSI, (u8)priv->undecorated_smoothed_pwdb);
पूर्ण

/*---------------------------Define function prototype------------------------*/
