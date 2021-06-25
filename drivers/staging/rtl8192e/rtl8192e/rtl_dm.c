<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "rtl_dm.h"
#समावेश "r8192E_hw.h"
#समावेश "r8192E_phy.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h"
#समावेश "r8192E_cmdpkt.h"

/*---------------------------Define Local Constant---------------------------*/
अटल u32 edca_setting_DL[HT_IOT_PEER_MAX] = अणु
	0x5e4322,
	0x5e4322,
	0x5ea44f,
	0x5e4322,
	0x604322,
	0xa44f,
	0x5e4322,
	0x5e4332
पूर्ण;

अटल u32 edca_setting_DL_GMode[HT_IOT_PEER_MAX] = अणु
	0x5e4322,
	0x5e4322,
	0x5e4322,
	0x5e4322,
	0x604322,
	0xa44f,
	0x5e4322,
	0x5e4322
पूर्ण;

अटल u32 edca_setting_UL[HT_IOT_PEER_MAX] = अणु
	0x5e4322,
	0xa44f,
	0x5ea44f,
	0x5e4322,
	0x604322,
	0x5e4322,
	0x5e4322,
	0x5e4332
पूर्ण;

स्थिर u32 dm_tx_bb_gain[TxBBGainTableLength] = अणु
	0x7f8001fe, /* 12 dB */
	0x788001e2, /* 11 dB */
	0x71c001c7,
	0x6b8001ae,
	0x65400195,
	0x5fc0017f,
	0x5a400169,
	0x55400155,
	0x50800142,
	0x4c000130,
	0x47c0011f,
	0x43c0010f,
	0x40000100,
	0x3c8000f2,
	0x390000e4,
	0x35c000d7,
	0x32c000cb,
	0x300000c0,
	0x2d4000b5,
	0x2ac000ab,
	0x288000a2,
	0x26000098,
	0x24000090,
	0x22000088,
	0x20000080,
	0x1a00006c,
	0x1c800072,
	0x18000060,
	0x19800066,
	0x15800056,
	0x26c0005b,
	0x14400051,
	0x24400051,
	0x1300004c,
	0x12000048,
	0x11000044,
	0x10000040, /* -24 dB */
पूर्ण;

स्थिर u8 dm_cck_tx_bb_gain[CCKTxBBGainTableLength][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण,
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण,
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण,
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण,
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण,
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण,
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण,
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण,
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण,
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण,
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण,
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण,
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण
पूर्ण;

स्थिर u8 dm_cck_tx_bb_gain_ch14[CCKTxBBGainTableLength][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x2d, 0x2d, 0x27, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x28, 0x28, 0x22, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

/*---------------------------Define Local Constant---------------------------*/


/*------------------------Define global variable-----------------------------*/
काष्ठा dig_t dm_digtable;

काष्ठा drx_path_sel DM_RxPathSelTable;
/*------------------------Define global variable-----------------------------*/


/*------------------------Define local variable------------------------------*/
/*------------------------Define local variable------------------------------*/



/*---------------------Define local function prototype-----------------------*/
अटल व्योम _rtl92e_dm_check_rate_adaptive(काष्ठा net_device *dev);

अटल व्योम _rtl92e_dm_init_bandwidth_स्वतःचयन(काष्ठा net_device *dev);
अटल	व्योम	_rtl92e_dm_bandwidth_स्वतःचयन(काष्ठा net_device *dev);


अटल	व्योम	_rtl92e_dm_check_tx_घातer_tracking(काष्ठा net_device *dev);

अटल व्योम _rtl92e_dm_bb_initialgain_restore(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_dig_init(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_highpwr(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_driver(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_false_alarm(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_initial_gain(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_pd_th(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_cs_ratio(काष्ठा net_device *dev);

अटल	व्योम _rtl92e_dm_init_cts_to_self(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_init_wa_broadcom_iot(काष्ठा net_device *dev);

अटल व्योम _rtl92e_dm_check_edca_turbo(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_check_rx_path_selection(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_init_rx_path_selection(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_rx_path_sel_byrssi(काष्ठा net_device *dev);


अटल व्योम _rtl92e_dm_init_fsync(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_deinit_fsync(काष्ठा net_device *dev);

अटल	व्योम _rtl92e_dm_check_txrateandretrycount(काष्ठा net_device *dev);
अटल  व्योम _rtl92e_dm_check_ac_dc_घातer(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_check_fsync(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_check_rf_ctrl_gpio(व्योम *data);
अटल व्योम _rtl92e_dm_fsync_समयr_callback(काष्ठा समयr_list *t);

/*---------------------Define local function prototype-----------------------*/

अटल	व्योम	_rtl92e_dm_init_dynamic_tx_घातer(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_dynamic_tx_घातer(काष्ठा net_device *dev);

अटल व्योम _rtl92e_dm_send_rssi_to_fw(काष्ठा net_device *dev);
अटल व्योम _rtl92e_dm_cts_to_self(काष्ठा net_device *dev);
/*---------------------------Define function prototype------------------------*/

व्योम rtl92e_dm_init(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->DM_Type = DM_Type_ByDriver;

	priv->undecorated_smoothed_pwdb = -1;

	_rtl92e_dm_init_dynamic_tx_घातer(dev);

	rtl92e_init_adaptive_rate(dev);

	_rtl92e_dm_dig_init(dev);
	rtl92e_dm_init_edca_turbo(dev);
	_rtl92e_dm_init_bandwidth_स्वतःचयन(dev);
	_rtl92e_dm_init_fsync(dev);
	_rtl92e_dm_init_rx_path_selection(dev);
	_rtl92e_dm_init_cts_to_self(dev);
	अगर (IS_HARDWARE_TYPE_8192SE(dev))
		_rtl92e_dm_init_wa_broadcom_iot(dev);

	INIT_DELAYED_WORK_RSL(&priv->gpio_change_rf_wq,
			      (व्योम *)_rtl92e_dm_check_rf_ctrl_gpio, dev);
पूर्ण

व्योम rtl92e_dm_deinit(काष्ठा net_device *dev)
अणु

	_rtl92e_dm_deinit_fsync(dev);

पूर्ण

व्योम rtl92e_dm_watchकरोg(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->being_init_adapter)
		वापस;

	_rtl92e_dm_check_ac_dc_घातer(dev);

	_rtl92e_dm_check_txrateandretrycount(dev);
	_rtl92e_dm_check_edca_turbo(dev);

	_rtl92e_dm_check_rate_adaptive(dev);
	_rtl92e_dm_dynamic_tx_घातer(dev);
	_rtl92e_dm_check_tx_घातer_tracking(dev);

	_rtl92e_dm_ctrl_initgain_byrssi(dev);
	_rtl92e_dm_bandwidth_स्वतःचयन(dev);

	_rtl92e_dm_check_rx_path_selection(dev);
	_rtl92e_dm_check_fsync(dev);

	_rtl92e_dm_send_rssi_to_fw(dev);
	_rtl92e_dm_cts_to_self(dev);
पूर्ण

अटल व्योम _rtl92e_dm_check_ac_dc_घातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल स्थिर अक्षर ac_dc_script[] = "/etc/acpi/wireless-rtl-ac-dc-power.sh";
	अक्षर *argv[] = अणु(अक्षर *)ac_dc_script, DRV_NAME, शून्यपूर्ण;
	अटल अक्षर *envp[] = अणु"HOME=/",
			"TERM=linux",
			"PATH=/usr/bin:/bin",
			 शून्यपूर्ण;

	अगर (priv->ResetProgress == RESET_TYPE_SILENT) अणु
		RT_TRACE((COMP_INIT | COMP_POWER | COMP_RF),
			 "GPIOChangeRFWorkItemCallBack(): Silent Reset!!!!!!!\n");
		वापस;
	पूर्ण

	अगर (priv->rtllib->state != RTLLIB_LINKED)
		वापस;
	call_usermodehelper(ac_dc_script, argv, envp, UMH_WAIT_PROC);

	वापस;
पूर्ण;


व्योम rtl92e_init_adaptive_rate(काष्ठा net_device *dev)
अणु

	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rate_adaptive *pra = &priv->rate_adaptive;

	pra->ratr_state = DM_RATR_STA_MAX;
	pra->high2low_rssi_thresh_क्रम_ra = RateAdaptiveTH_High;
	pra->low2high_rssi_thresh_क्रम_ra20M = RateAdaptiveTH_Low_20M+5;
	pra->low2high_rssi_thresh_क्रम_ra40M = RateAdaptiveTH_Low_40M+5;

	pra->high_rssi_thresh_क्रम_ra = RateAdaptiveTH_High+5;
	pra->low_rssi_thresh_क्रम_ra20M = RateAdaptiveTH_Low_20M;
	pra->low_rssi_thresh_क्रम_ra40M = RateAdaptiveTH_Low_40M;

	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		pra->ping_rssi_enable = 1;
	अन्यथा
		pra->ping_rssi_enable = 0;
	pra->ping_rssi_thresh_क्रम_ra = 15;


	अगर (priv->rf_type == RF_2T4R) अणु
		pra->upper_rssi_threshold_ratr		=	0x8f0f0000;
		pra->middle_rssi_threshold_ratr		=	0x8f0ff000;
		pra->low_rssi_threshold_ratr		=	0x8f0ff001;
		pra->low_rssi_threshold_ratr_40M	=	0x8f0ff005;
		pra->low_rssi_threshold_ratr_20M	=	0x8f0ff001;
		pra->ping_rssi_ratr	=	0x0000000d;
	पूर्ण अन्यथा अगर (priv->rf_type == RF_1T2R) अणु
		pra->upper_rssi_threshold_ratr		=	0x000fc000;
		pra->middle_rssi_threshold_ratr		=	0x000ff000;
		pra->low_rssi_threshold_ratr		=	0x000ff001;
		pra->low_rssi_threshold_ratr_40M	=	0x000ff005;
		pra->low_rssi_threshold_ratr_20M	=	0x000ff001;
		pra->ping_rssi_ratr	=	0x0000000d;
	पूर्ण

पूर्ण


अटल व्योम _rtl92e_dm_check_rate_adaptive(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;
	काष्ठा rate_adaptive *pra = &priv->rate_adaptive;
	u32 currentRATR, targetRATR = 0;
	u32 LowRSSIThreshForRA = 0, HighRSSIThreshForRA = 0;
	bool bलघु_gi_enabled = false;
	अटल u8 ping_rssi_state;

	अगर (!priv->up) अणु
		RT_TRACE(COMP_RATE,
			 "<---- %s: driver is going to unload\n", __func__);
		वापस;
	पूर्ण

	अगर (pra->rate_adaptive_disabled)
		वापस;

	अगर (!(priv->rtllib->mode == WIRELESS_MODE_N_24G ||
	    priv->rtllib->mode == WIRELESS_MODE_N_5G))
		वापस;

	अगर (priv->rtllib->state == RTLLIB_LINKED) अणु

		bलघु_gi_enabled = (pHTInfo->bCurTxBW40MHz &&
				     pHTInfo->bCurShortGI40MHz) ||
				    (!pHTInfo->bCurTxBW40MHz &&
				     pHTInfo->bCurShortGI20MHz);

		pra->upper_rssi_threshold_ratr =
				(pra->upper_rssi_threshold_ratr & (~BIT31)) |
				((bलघु_gi_enabled) ? BIT31 : 0);

		pra->middle_rssi_threshold_ratr =
				(pra->middle_rssi_threshold_ratr & (~BIT31)) |
				((bलघु_gi_enabled) ? BIT31 : 0);

		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) अणु
			pra->low_rssi_threshold_ratr =
				(pra->low_rssi_threshold_ratr_40M & (~BIT31)) |
				((bलघु_gi_enabled) ? BIT31 : 0);
		पूर्ण अन्यथा अणु
			pra->low_rssi_threshold_ratr =
				(pra->low_rssi_threshold_ratr_20M & (~BIT31)) |
				((bलघु_gi_enabled) ? BIT31 : 0);
		पूर्ण
		pra->ping_rssi_ratr =
				(pra->ping_rssi_ratr & (~BIT31)) |
				((bलघु_gi_enabled) ? BIT31 : 0);

		अगर (pra->ratr_state == DM_RATR_STA_HIGH) अणु
			HighRSSIThreshForRA = pra->high2low_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA = (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low_rssi_thresh_क्रम_ra40M) : (pra->low_rssi_thresh_क्रम_ra20M);
		पूर्ण अन्यथा अगर (pra->ratr_state == DM_RATR_STA_LOW) अणु
			HighRSSIThreshForRA = pra->high_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA = (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low2high_rssi_thresh_क्रम_ra40M) : (pra->low2high_rssi_thresh_क्रम_ra20M);
		पूर्ण अन्यथा अणु
			HighRSSIThreshForRA = pra->high_rssi_thresh_क्रम_ra;
			LowRSSIThreshForRA = (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) ?
					(pra->low_rssi_thresh_क्रम_ra40M) : (pra->low_rssi_thresh_क्रम_ra20M);
		पूर्ण

		अगर (priv->undecorated_smoothed_pwdb >=
		    (दीर्घ)HighRSSIThreshForRA) अणु
			pra->ratr_state = DM_RATR_STA_HIGH;
			targetRATR = pra->upper_rssi_threshold_ratr;
		पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb >=
			   (दीर्घ)LowRSSIThreshForRA) अणु
			pra->ratr_state = DM_RATR_STA_MIDDLE;
			targetRATR = pra->middle_rssi_threshold_ratr;
		पूर्ण अन्यथा अणु
			pra->ratr_state = DM_RATR_STA_LOW;
			targetRATR = pra->low_rssi_threshold_ratr;
		पूर्ण

		अगर (pra->ping_rssi_enable) अणु
			अगर (priv->undecorated_smoothed_pwdb <
			    (दीर्घ)(pra->ping_rssi_thresh_क्रम_ra+5)) अणु
				अगर ((priv->undecorated_smoothed_pwdb <
				     (दीर्घ)pra->ping_rssi_thresh_क्रम_ra) ||
				    ping_rssi_state) अणु
					pra->ratr_state = DM_RATR_STA_LOW;
					targetRATR = pra->ping_rssi_ratr;
					ping_rssi_state = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				ping_rssi_state = 0;
			पूर्ण
		पूर्ण

		अगर (priv->rtllib->GetHalfNmodeSupportByAPsHandler(dev))
			targetRATR &=  0xf00fffff;

		currentRATR = rtl92e_पढ़ोl(dev, RATR0);
		अगर (targetRATR !=  currentRATR) अणु
			u32 ratr_value;

			ratr_value = targetRATR;
			RT_TRACE(COMP_RATE,
				 "currentRATR = %x, targetRATR = %x\n",
				 currentRATR, targetRATR);
			अगर (priv->rf_type == RF_1T2R)
				ratr_value &= ~(RATE_ALL_OFDM_2SS);
			rtl92e_ग_लिखोl(dev, RATR0, ratr_value);
			rtl92e_ग_लिखोb(dev, UFWP, 1);

			pra->last_ratr = targetRATR;
		पूर्ण

	पूर्ण अन्यथा अणु
		pra->ratr_state = DM_RATR_STA_MAX;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_init_bandwidth_स्वतःचयन(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->rtllib->bandwidth_स्वतः_चयन.threshold_20Mhzto40Mhz = BW_AUTO_SWITCH_LOW_HIGH;
	priv->rtllib->bandwidth_स्वतः_चयन.threshold_40Mhzto20Mhz = BW_AUTO_SWITCH_HIGH_LOW;
	priv->rtllib->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = false;
	priv->rtllib->bandwidth_स्वतः_चयन.bस्वतःचयन_enable = false;
पूर्ण

अटल व्योम _rtl92e_dm_bandwidth_स्वतःचयन(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 ||
	   !priv->rtllib->bandwidth_स्वतः_चयन.bस्वतःचयन_enable)
		वापस;
	अगर (!priv->rtllib->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz) अणु
		अगर (priv->undecorated_smoothed_pwdb <=
		    priv->rtllib->bandwidth_स्वतः_चयन.threshold_40Mhzto20Mhz)
			priv->rtllib->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = true;
	पूर्ण अन्यथा अणु
		अगर (priv->undecorated_smoothed_pwdb >=
		    priv->rtllib->bandwidth_स्वतः_चयन.threshold_20Mhzto40Mhz)
			priv->rtllib->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz = false;
	पूर्ण
पूर्ण

अटल u32 OFDMSwingTable[OFDM_Table_Length] = अणु
	0x7f8001fe,
	0x71c001c7,
	0x65400195,
	0x5a400169,
	0x50800142,
	0x47c0011f,
	0x40000100,
	0x390000e4,
	0x32c000cb,
	0x2d4000b5,
	0x288000a2,
	0x24000090,
	0x20000080,
	0x1c800072,
	0x19800066,
	0x26c0005b,
	0x24400051,
	0x12000048,
	0x10000040
पूर्ण;

अटल u8	CCKSwingTable_Ch1_Ch13[CCK_Table_length][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण,
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण,
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण
पूर्ण;

अटल u8	CCKSwingTable_Ch14[CCK_Table_length][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

#घोषणा		Pw_Track_Flag				0x11d
#घोषणा		Tssi_Mea_Value				0x13c
#घोषणा		Tssi_Report_Value1			0x134
#घोषणा		Tssi_Report_Value2			0x13e
#घोषणा		FW_Busy_Flag				0x13f

अटल व्योम _rtl92e_dm_tx_update_tssi_weak_संकेत(काष्ठा net_device *dev,
						  u8 RF_Type)
अणु
	काष्ठा r8192_priv *p = rtllib_priv(dev);

	अगर (RF_Type == RF_2T4R) अणु
		अगर ((p->rfa_txघातertrackingindex > 0) &&
		    (p->rfc_txघातertrackingindex > 0)) अणु
			p->rfa_txघातertrackingindex--;
			अगर (p->rfa_txघातertrackingindex_real > 4) अणु
				p->rfa_txघातertrackingindex_real--;
				rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
						  bMaskDWord,
						  dm_tx_bb_gain[p->rfa_txघातertrackingindex_real]);
			पूर्ण

			p->rfc_txघातertrackingindex--;
			अगर (p->rfc_txघातertrackingindex_real > 4) अणु
				p->rfc_txघातertrackingindex_real--;
				rtl92e_set_bb_reg(dev,
						  rOFDM0_XCTxIQImbalance,
						  bMaskDWord,
						  dm_tx_bb_gain[p->rfc_txघातertrackingindex_real]);
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[4]);
			rtl92e_set_bb_reg(dev,
					  rOFDM0_XCTxIQImbalance,
					  bMaskDWord, dm_tx_bb_gain[4]);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (p->rfa_txघातertrackingindex > 0) अणु
			p->rfa_txघातertrackingindex--;
			अगर (p->rfa_txघातertrackingindex_real > 4) अणु
				p->rfa_txघातertrackingindex_real--;
				rtl92e_set_bb_reg(dev,
						  rOFDM0_XATxIQImbalance,
						  bMaskDWord,
						  dm_tx_bb_gain[p->rfa_txघातertrackingindex_real]);
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord, dm_tx_bb_gain[4]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_tx_update_tssi_strong_संकेत(काष्ठा net_device *dev,
						    u8 RF_Type)
अणु
	काष्ठा r8192_priv *p = rtllib_priv(dev);

	अगर (RF_Type == RF_2T4R) अणु
		अगर ((p->rfa_txघातertrackingindex < TxBBGainTableLength - 1) &&
		    (p->rfc_txघातertrackingindex < TxBBGainTableLength - 1)) अणु
			p->rfa_txघातertrackingindex++;
			p->rfa_txघातertrackingindex_real++;
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[p->rfa_txघातertrackingindex_real]);
			p->rfc_txघातertrackingindex++;
			p->rfc_txघातertrackingindex_real++;
			rtl92e_set_bb_reg(dev, rOFDM0_XCTxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[p->rfc_txघातertrackingindex_real]);
		पूर्ण अन्यथा अणु
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[TxBBGainTableLength - 1]);
			rtl92e_set_bb_reg(dev, rOFDM0_XCTxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[TxBBGainTableLength - 1]);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (p->rfa_txघातertrackingindex < (TxBBGainTableLength - 1)) अणु
			p->rfa_txघातertrackingindex++;
			p->rfa_txघातertrackingindex_real++;
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[p->rfa_txघातertrackingindex_real]);
		पूर्ण अन्यथा अणु
			rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance,
					  bMaskDWord,
					  dm_tx_bb_gain[TxBBGainTableLength - 1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_tx_घातer_tracking_callback_tssi(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	bool	vivअगरlag = false;
	काष्ठा dcmd_txcmd tx_cmd;
	u8	घातerlevelOFDM24G;
	पूर्णांक	i = 0, j = 0, k = 0;
	u8	RF_Type, पंचांगp_report[5] = अणु0, 0, 0, 0, 0पूर्ण;
	u32	Value;
	u8	Pwr_Flag;
	u16	Avg_TSSI_Meas, TSSI_13dBm, Avg_TSSI_Meas_from_driver = 0;
	u32	delta = 0;

	RT_TRACE(COMP_POWER_TRACKING, "%s()\n", __func__);
	rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
	rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
	priv->rtllib->bdynamic_txघातer_enable = false;

	घातerlevelOFDM24G = (u8)(priv->Pwr_Track>>24);
	RF_Type = priv->rf_type;
	Value = (RF_Type<<8) | घातerlevelOFDM24G;

	RT_TRACE(COMP_POWER_TRACKING, "powerlevelOFDM24G = %x\n",
		 घातerlevelOFDM24G);


	क्रम (j = 0; j <= 30; j++) अणु

		tx_cmd.Op		= TXCMD_SET_TX_PWR_TRACKING;
		tx_cmd.Length	= 4;
		tx_cmd.Value		= Value;
		rtl92e_send_cmd_pkt(dev, DESC_PACKET_TYPE_NORMAL, (u8 *)&tx_cmd,
				    माप(काष्ठा dcmd_txcmd));
		mdelay(1);
		क्रम (i = 0; i <= 30; i++) अणु
			Pwr_Flag = rtl92e_पढ़ोb(dev, Pw_Track_Flag);

			अगर (Pwr_Flag == 0) अणु
				mdelay(1);

				अगर (priv->bResetInProgress) अणु
					RT_TRACE(COMP_POWER_TRACKING,
						 "we are in silent reset progress, so return\n");
					rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
					rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
					वापस;
				पूर्ण
				अगर (priv->rtllib->eRFPowerState != eRfOn) अणु
					RT_TRACE(COMP_POWER_TRACKING,
						 "we are in power save, so return\n");
					rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
					rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
					वापस;
				पूर्ण

				जारी;
			पूर्ण

			Avg_TSSI_Meas = rtl92e_पढ़ोw(dev, Tssi_Mea_Value);

			अगर (Avg_TSSI_Meas == 0) अणु
				rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
				rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
				वापस;
			पूर्ण

			क्रम (k = 0; k < 5; k++) अणु
				अगर (k != 4)
					पंचांगp_report[k] = rtl92e_पढ़ोb(dev,
							 Tssi_Report_Value1+k);
				अन्यथा
					पंचांगp_report[k] = rtl92e_पढ़ोb(dev,
							 Tssi_Report_Value2);

				RT_TRACE(COMP_POWER_TRACKING,
					 "TSSI_report_value = %d\n",
					 पंचांगp_report[k]);

				अगर (पंचांगp_report[k] <= 20) अणु
					vivअगरlag = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (vivअगरlag) अणु
				rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
				vivअगरlag = false;
				RT_TRACE(COMP_POWER_TRACKING,
					 "we filted this data\n");
				क्रम (k = 0; k < 5; k++)
					पंचांगp_report[k] = 0;
				अवरोध;
			पूर्ण

			क्रम (k = 0; k < 5; k++)
				Avg_TSSI_Meas_from_driver += पंचांगp_report[k];

			Avg_TSSI_Meas_from_driver *= 100 / 5;
			RT_TRACE(COMP_POWER_TRACKING,
				 "Avg_TSSI_Meas_from_driver = %d\n",
				 Avg_TSSI_Meas_from_driver);
			TSSI_13dBm = priv->TSSI_13dBm;
			RT_TRACE(COMP_POWER_TRACKING, "TSSI_13dBm = %d\n",
				 TSSI_13dBm);

			अगर (Avg_TSSI_Meas_from_driver > TSSI_13dBm)
				delta = Avg_TSSI_Meas_from_driver - TSSI_13dBm;
			अन्यथा
				delta = TSSI_13dBm - Avg_TSSI_Meas_from_driver;

			अगर (delta <= E_FOR_TX_POWER_TRACK) अणु
				priv->rtllib->bdynamic_txघातer_enable = true;
				rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
				rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
				RT_TRACE(COMP_POWER_TRACKING,
					 "tx power track is done\n");
				RT_TRACE(COMP_POWER_TRACKING,
					 "priv->rfa_txpowertrackingindex = %d\n",
					 priv->rfa_txघातertrackingindex);
				RT_TRACE(COMP_POWER_TRACKING,
					 "priv->rfa_txpowertrackingindex_real = %d\n",
					 priv->rfa_txघातertrackingindex_real);
				RT_TRACE(COMP_POWER_TRACKING,
					 "priv->CCKPresentAttentuation_difference = %d\n",
					 priv->CCKPresentAttentuation_dअगरference);
				RT_TRACE(COMP_POWER_TRACKING,
					 "priv->CCKPresentAttentuation = %d\n",
					 priv->CCKPresentAttentuation);
				वापस;
			पूर्ण
			अगर (Avg_TSSI_Meas_from_driver < TSSI_13dBm - E_FOR_TX_POWER_TRACK)
				_rtl92e_dm_tx_update_tssi_weak_संकेत(dev,
								      RF_Type);
			अन्यथा
				_rtl92e_dm_tx_update_tssi_strong_संकेत(dev, RF_Type);

			अगर (RF_Type == RF_2T4R) अणु
				priv->CCKPresentAttentuation_dअगरference
					= priv->rfa_txघातertrackingindex - priv->rfa_txघातertracking_शेष;
			पूर्ण अन्यथा अणु
				priv->CCKPresentAttentuation_dअगरference
					= priv->rfa_txघातertrackingindex_real - priv->rfa_txघातertracking_शेष;
			पूर्ण

			अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				priv->CCKPresentAttentuation =
					 priv->CCKPresentAttentuation_20Mशेष +
					 priv->CCKPresentAttentuation_dअगरference;
			अन्यथा
				priv->CCKPresentAttentuation =
					 priv->CCKPresentAttentuation_40Mशेष +
					 priv->CCKPresentAttentuation_dअगरference;

			अगर (priv->CCKPresentAttentuation > (CCKTxBBGainTableLength-1))
				priv->CCKPresentAttentuation = CCKTxBBGainTableLength-1;
			अगर (priv->CCKPresentAttentuation < 0)
				priv->CCKPresentAttentuation = 0;

			अगर (priv->CCKPresentAttentuation > -1 &&
			    priv->CCKPresentAttentuation < CCKTxBBGainTableLength) अणु
				अगर (priv->rtllib->current_network.channel == 14 &&
				    !priv->bcck_in_ch14) अणु
					priv->bcck_in_ch14 = true;
					rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
				पूर्ण अन्यथा अगर (priv->rtllib->current_network.channel != 14 && priv->bcck_in_ch14) अणु
					priv->bcck_in_ch14 = false;
					rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
				पूर्ण अन्यथा
					rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
			पूर्ण
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->rfa_txpowertrackingindex = %d\n",
				 priv->rfa_txघातertrackingindex);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->rfa_txpowertrackingindex_real = %d\n",
				 priv->rfa_txघातertrackingindex_real);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->CCKPresentAttentuation_difference = %d\n",
				 priv->CCKPresentAttentuation_dअगरference);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->CCKPresentAttentuation = %d\n",
				 priv->CCKPresentAttentuation);

			अगर (priv->CCKPresentAttentuation_dअगरference <= -12 ||
			    priv->CCKPresentAttentuation_dअगरference >= 24) अणु
				priv->rtllib->bdynamic_txघातer_enable = true;
				rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
				rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
				RT_TRACE(COMP_POWER_TRACKING,
					 "tx power track--->limited\n");
				वापस;
			पूर्ण

			rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
			Avg_TSSI_Meas_from_driver = 0;
			क्रम (k = 0; k < 5; k++)
				पंचांगp_report[k] = 0;
			अवरोध;
		पूर्ण
		rtl92e_ग_लिखोb(dev, FW_Busy_Flag, 0);
	पूर्ण
	priv->rtllib->bdynamic_txघातer_enable = true;
	rtl92e_ग_लिखोb(dev, Pw_Track_Flag, 0);
पूर्ण

अटल व्योम _rtl92e_dm_tx_घातer_tracking_cb_thermal(काष्ठा net_device *dev)
अणु
#घोषणा ThermalMeterVal	9
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 पंचांगpRegA, TempCCk;
	u8 पंचांगpOFDMindex, पंचांगpCCKindex, पंचांगpCCK20Mindex, पंचांगpCCK40Mindex, पंचांगpval;
	पूर्णांक i = 0, CCKSwingNeedUpdate = 0;

	अगर (!priv->btxघातer_trackingInit) अणु
		पंचांगpRegA = rtl92e_get_bb_reg(dev, rOFDM0_XATxIQImbalance,
					    bMaskDWord);
		क्रम (i = 0; i < OFDM_Table_Length; i++) अणु
			अगर (पंचांगpRegA == OFDMSwingTable[i]) अणु
				priv->OFDM_index[0] = (u8)i;
				RT_TRACE(COMP_POWER_TRACKING,
					 "Initial reg0x%x = 0x%x, OFDM_index = 0x%x\n",
					 rOFDM0_XATxIQImbalance, पंचांगpRegA,
					 priv->OFDM_index[0]);
			पूर्ण
		पूर्ण

		TempCCk = rtl92e_get_bb_reg(dev, rCCK0_TxFilter1, bMaskByte2);
		क्रम (i = 0; i < CCK_Table_length; i++) अणु
			अगर (TempCCk == (u32)CCKSwingTable_Ch1_Ch13[i][0]) अणु
				priv->CCK_index = (u8) i;
				RT_TRACE(COMP_POWER_TRACKING,
					 "Initial reg0x%x = 0x%x, CCK_index = 0x%x\n",
					 rCCK0_TxFilter1, TempCCk,
					 priv->CCK_index);
				अवरोध;
			पूर्ण
		पूर्ण
		priv->btxघातer_trackingInit = true;
		वापस;
	पूर्ण

	पंचांगpRegA = rtl92e_get_rf_reg(dev, RF90_PATH_A, 0x12, 0x078);
	RT_TRACE(COMP_POWER_TRACKING, "Readback ThermalMeterA = %d\n", पंचांगpRegA);
	अगर (पंचांगpRegA < 3 || पंचांगpRegA > 13)
		वापस;
	अगर (पंचांगpRegA >= 12)
		पंचांगpRegA = 12;
	RT_TRACE(COMP_POWER_TRACKING, "Valid ThermalMeterA = %d\n", पंचांगpRegA);
	priv->ThermalMeter[0] = ThermalMeterVal;
	priv->ThermalMeter[1] = ThermalMeterVal;

	अगर (priv->ThermalMeter[0] >= (u8)पंचांगpRegA) अणु
		पंचांगpOFDMindex = पंचांगpCCK20Mindex = 6+(priv->ThermalMeter[0] -
			      (u8)पंचांगpRegA);
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
			पंचांगpOFDMindex = 0;
			पंचांगpCCK20Mindex = 0;
		पूर्ण अन्यथा अणु
			पंचांगpOFDMindex = 6 - पंचांगpval;
			पंचांगpCCK20Mindex = 6 - पंचांगpval;
		पूर्ण
		पंचांगpCCK40Mindex = 0;
	पूर्ण
	अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
		पंचांगpCCKindex = पंचांगpCCK40Mindex;
	अन्यथा
		पंचांगpCCKindex = पंचांगpCCK20Mindex;

	priv->Record_CCK_20Mindex = पंचांगpCCK20Mindex;
	priv->Record_CCK_40Mindex = पंचांगpCCK40Mindex;
	RT_TRACE(COMP_POWER_TRACKING,
		 "Record_CCK_20Mindex / Record_CCK_40Mindex = %d / %d.\n",
		 priv->Record_CCK_20Mindex, priv->Record_CCK_40Mindex);

	अगर (priv->rtllib->current_network.channel == 14 &&
	    !priv->bcck_in_ch14) अणु
		priv->bcck_in_ch14 = true;
		CCKSwingNeedUpdate = 1;
	पूर्ण अन्यथा अगर (priv->rtllib->current_network.channel != 14 &&
		   priv->bcck_in_ch14) अणु
		priv->bcck_in_ch14 = false;
		CCKSwingNeedUpdate = 1;
	पूर्ण

	अगर (priv->CCK_index != पंचांगpCCKindex) अणु
		priv->CCK_index = पंचांगpCCKindex;
		CCKSwingNeedUpdate = 1;
	पूर्ण

	अगर (CCKSwingNeedUpdate)
		rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
	अगर (priv->OFDM_index[0] != पंचांगpOFDMindex) अणु
		priv->OFDM_index[0] = पंचांगpOFDMindex;
		rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance, bMaskDWord,
				  OFDMSwingTable[priv->OFDM_index[0]]);
		RT_TRACE(COMP_POWER_TRACKING, "Update OFDMSwing[%d] = 0x%x\n",
			 priv->OFDM_index[0],
			 OFDMSwingTable[priv->OFDM_index[0]]);
	पूर्ण
	priv->txघातer_count = 0;
पूर्ण

व्योम rtl92e_dm_txघातer_tracking_wq(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_dwork_rsl(data,
				  काष्ठा r8192_priv, txघातer_tracking_wq);
	काष्ठा net_device *dev = priv->rtllib->dev;

	अगर (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_dm_tx_घातer_tracking_callback_tssi(dev);
	अन्यथा
		_rtl92e_dm_tx_घातer_tracking_cb_thermal(dev);
पूर्ण

अटल व्योम _rtl92e_dm_initialize_tx_घातer_tracking_tssi(काष्ठा net_device *dev)
अणु

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->btxघातer_tracking = true;
	priv->txघातer_count       = 0;
	priv->btxघातer_trackingInit = false;

पूर्ण

अटल व्योम _rtl92e_dm_init_tx_घातer_tracking_thermal(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);


	अगर (priv->rtllib->FwRWRF)
		priv->btxघातer_tracking = true;
	अन्यथा
		priv->btxघातer_tracking = false;
	priv->txघातer_count       = 0;
	priv->btxघातer_trackingInit = false;
	RT_TRACE(COMP_POWER_TRACKING, "pMgntInfo->bTXPowerTracking = %d\n",
		 priv->btxघातer_tracking);
पूर्ण

व्योम rtl92e_dm_init_txघातer_tracking(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_dm_initialize_tx_घातer_tracking_tssi(dev);
	अन्यथा
		_rtl92e_dm_init_tx_घातer_tracking_thermal(dev);
पूर्ण

अटल व्योम _rtl92e_dm_check_tx_घातer_tracking_tssi(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u32 tx_घातer_track_counter;

	RT_TRACE(COMP_POWER_TRACKING, "%s()\n", __func__);
	अगर (rtl92e_पढ़ोb(dev, 0x11e) == 1)
		वापस;
	अगर (!priv->btxघातer_tracking)
		वापस;
	tx_घातer_track_counter++;


	अगर (tx_घातer_track_counter >= 180) अणु
		schedule_delayed_work(&priv->txघातer_tracking_wq, 0);
		tx_घातer_track_counter = 0;
	पूर्ण

पूर्ण

अटल व्योम _rtl92e_dm_check_tx_घातer_tracking_thermal(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u8	TM_Trigger;
	u8		TxPowerCheckCnt = 0;

	अगर (IS_HARDWARE_TYPE_8192SE(dev))
		TxPowerCheckCnt = 5;
	अन्यथा
		TxPowerCheckCnt = 2;
	अगर (!priv->btxघातer_tracking)
		वापस;

	अगर (priv->txघातer_count  <= TxPowerCheckCnt) अणु
		priv->txघातer_count++;
		वापस;
	पूर्ण

	अगर (!TM_Trigger) अणु
		rtl92e_set_rf_reg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4d);
		rtl92e_set_rf_reg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4f);
		rtl92e_set_rf_reg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4d);
		rtl92e_set_rf_reg(dev, RF90_PATH_A, 0x02, bMask12Bits, 0x4f);
		TM_Trigger = 1;
		वापस;
	पूर्ण
	netdev_info(dev, "===============>Schedule TxPowerTrackingWorkItem\n");
	schedule_delayed_work(&priv->txघातer_tracking_wq, 0);
	TM_Trigger = 0;

पूर्ण

अटल व्योम _rtl92e_dm_check_tx_घातer_tracking(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_dm_check_tx_घातer_tracking_tssi(dev);
	अन्यथा
		_rtl92e_dm_check_tx_घातer_tracking_thermal(dev);
पूर्ण

अटल व्योम _rtl92e_dm_cck_tx_घातer_adjust_tssi(काष्ठा net_device *dev,
						bool bInCH14)
अणु
	u32 TempVal;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 attenuation = (u8)priv->CCKPresentAttentuation;

	TempVal = 0;
	अगर (!bInCH14) अणु
		TempVal = (u32)(dm_cck_tx_bb_gain[attenuation][0] +
			  (dm_cck_tx_bb_gain[attenuation][1] << 8));

		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		TempVal = (u32)((dm_cck_tx_bb_gain[attenuation][2]) +
			  (dm_cck_tx_bb_gain[attenuation][3] << 8) +
			  (dm_cck_tx_bb_gain[attenuation][4] << 16)+
			  (dm_cck_tx_bb_gain[attenuation][5] << 24));
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		TempVal = (u32)(dm_cck_tx_bb_gain[attenuation][6] +
			  (dm_cck_tx_bb_gain[attenuation][7] << 8));

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
	पूर्ण अन्यथा अणु
		TempVal = (u32)((dm_cck_tx_bb_gain_ch14[attenuation][0]) +
			  (dm_cck_tx_bb_gain_ch14[attenuation][1] << 8));

		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		TempVal = (u32)((dm_cck_tx_bb_gain_ch14[attenuation][2]) +
			  (dm_cck_tx_bb_gain_ch14[attenuation][3] << 8) +
			  (dm_cck_tx_bb_gain_ch14[attenuation][4] << 16)+
			  (dm_cck_tx_bb_gain_ch14[attenuation][5] << 24));
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		TempVal = (u32)((dm_cck_tx_bb_gain_ch14[attenuation][6]) +
			  (dm_cck_tx_bb_gain_ch14[attenuation][7] << 8));

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_cck_tx_घातer_adjust_thermal_meter(काष्ठा net_device *dev,
							 bool bInCH14)
अणु
	u32 TempVal;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	TempVal = 0;
	अगर (!bInCH14) अणु
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][0] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][1] << 8);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_TxFilter1,
			 TempVal);
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][2] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][3] << 8) +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][4] << 16)+
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][5] << 24);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_TxFilter2,
			 TempVal);
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][6] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][7] << 8);

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_DebugPort,
			 TempVal);
	पूर्ण अन्यथा अणु
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][0] +
			  (CCKSwingTable_Ch14[priv->CCK_index][1] << 8);

		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter1, TempVal);
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][2] +
			  (CCKSwingTable_Ch14[priv->CCK_index][3] << 8) +
			  (CCKSwingTable_Ch14[priv->CCK_index][4] << 16)+
			  (CCKSwingTable_Ch14[priv->CCK_index][5] << 24);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter2, TempVal);
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][6] +
			  (CCKSwingTable_Ch14[priv->CCK_index][7]<<8);

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_DebugPort, TempVal);
	पूर्ण
पूर्ण

व्योम rtl92e_dm_cck_txघातer_adjust(काष्ठा net_device *dev, bool binch14)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_dm_cck_tx_घातer_adjust_tssi(dev, binch14);
	अन्यथा
		_rtl92e_dm_cck_tx_घातer_adjust_thermal_meter(dev, binch14);
पूर्ण

अटल व्योम _rtl92e_dm_tx_घातer_reset_recovery(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_POWER_TRACKING, "Start Reset Recovery ==>\n");
	rtl92e_set_bb_reg(dev, rOFDM0_XATxIQImbalance, bMaskDWord,
			  dm_tx_bb_gain[priv->rfa_txघातertrackingindex]);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in 0xc80 is %08x\n",
		 dm_tx_bb_gain[priv->rfa_txघातertrackingindex]);
	RT_TRACE(COMP_POWER_TRACKING,
		 "Reset Recovery: Fill in RFA_txPowerTrackingIndex is %x\n",
		 priv->rfa_txघातertrackingindex);
	RT_TRACE(COMP_POWER_TRACKING,
		 "Reset Recovery : RF A I/Q Amplify Gain is %d\n",
		 dm_tx_bb_gain_idx_to_amplअगरy(priv->rfa_txघातertrackingindex));
	RT_TRACE(COMP_POWER_TRACKING,
		 "Reset Recovery: CCK Attenuation is %d dB\n",
		 priv->CCKPresentAttentuation);
	rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);

	rtl92e_set_bb_reg(dev, rOFDM0_XCTxIQImbalance, bMaskDWord,
			  dm_tx_bb_gain[priv->rfc_txघातertrackingindex]);
	RT_TRACE(COMP_POWER_TRACKING, "Reset Recovery: Fill in 0xc90 is %08x\n",
		 dm_tx_bb_gain[priv->rfc_txघातertrackingindex]);
	RT_TRACE(COMP_POWER_TRACKING,
		 "Reset Recovery: Fill in RFC_txPowerTrackingIndex is %x\n",
		 priv->rfc_txघातertrackingindex);
	RT_TRACE(COMP_POWER_TRACKING,
		 "Reset Recovery : RF C I/Q Amplify Gain is %d\n",
		 dm_tx_bb_gain_idx_to_amplअगरy(priv->rfc_txघातertrackingindex));
पूर्ण

व्योम rtl92e_dm_restore_state(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32	reg_ratr = priv->rate_adaptive.last_ratr;
	u32 ratr_value;

	अगर (!priv->up) अणु
		RT_TRACE(COMP_RATE,
			 "<---- %s: driver is going to unload\n", __func__);
		वापस;
	पूर्ण

	अगर (priv->rate_adaptive.rate_adaptive_disabled)
		वापस;
	अगर (!(priv->rtllib->mode == WIRELESS_MODE_N_24G ||
	      priv->rtllib->mode == WIRELESS_MODE_N_5G))
		वापस;
	ratr_value = reg_ratr;
	अगर (priv->rf_type == RF_1T2R)
		ratr_value &= ~(RATE_ALL_OFDM_2SS);
	rtl92e_ग_लिखोl(dev, RATR0, ratr_value);
	rtl92e_ग_लिखोb(dev, UFWP, 1);
	अगर (priv->btxघातer_trackingInit && priv->btxघातer_tracking)
		_rtl92e_dm_tx_घातer_reset_recovery(dev);

	_rtl92e_dm_bb_initialgain_restore(dev);

पूर्ण

अटल व्योम _rtl92e_dm_bb_initialgain_restore(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 bit_mask = 0x7f;

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		वापस;

	rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);
	rtl92e_set_bb_reg(dev, rOFDM0_XAAGCCore1, bit_mask,
			  (u32)priv->initgain_backup.xaagccore1);
	rtl92e_set_bb_reg(dev, rOFDM0_XBAGCCore1, bit_mask,
			  (u32)priv->initgain_backup.xbagccore1);
	rtl92e_set_bb_reg(dev, rOFDM0_XCAGCCore1, bit_mask,
			  (u32)priv->initgain_backup.xcagccore1);
	rtl92e_set_bb_reg(dev, rOFDM0_XDAGCCore1, bit_mask,
			  (u32)priv->initgain_backup.xdagccore1);
	bit_mask  = bMaskByte2;
	rtl92e_set_bb_reg(dev, rCCK0_CCA, bit_mask,
			  (u32)priv->initgain_backup.cca);

	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc50 is %x\n",
		 priv->initgain_backup.xaagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc58 is %x\n",
		 priv->initgain_backup.xbagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc60 is %x\n",
		 priv->initgain_backup.xcagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc68 is %x\n",
		 priv->initgain_backup.xdagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xa0a is %x\n",
		 priv->initgain_backup.cca);
	rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);

पूर्ण

व्योम rtl92e_dm_backup_state(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 bit_mask = bMaskByte0;

	priv->bचयन_fsync  = false;
	priv->bfsync_processing = false;

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		वापस;

	rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);
	priv->initgain_backup.xaagccore1 = (u8)rtl92e_get_bb_reg(dev, rOFDM0_XAAGCCore1, bit_mask);
	priv->initgain_backup.xbagccore1 = (u8)rtl92e_get_bb_reg(dev, rOFDM0_XBAGCCore1, bit_mask);
	priv->initgain_backup.xcagccore1 = (u8)rtl92e_get_bb_reg(dev, rOFDM0_XCAGCCore1, bit_mask);
	priv->initgain_backup.xdagccore1 = (u8)rtl92e_get_bb_reg(dev, rOFDM0_XDAGCCore1, bit_mask);
	bit_mask  = bMaskByte2;
	priv->initgain_backup.cca = (u8)rtl92e_get_bb_reg(dev, rCCK0_CCA, bit_mask);

	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc50 is %x\n",
		 priv->initgain_backup.xaagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc58 is %x\n",
		 priv->initgain_backup.xbagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc60 is %x\n",
		 priv->initgain_backup.xcagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xc68 is %x\n",
		 priv->initgain_backup.xdagccore1);
	RT_TRACE(COMP_DIG, "BBInitialGainBackup 0xa0a is %x\n",
		 priv->initgain_backup.cca);
पूर्ण

अटल व्योम _rtl92e_dm_dig_init(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	dm_digtable.dig_enable_flag	= true;

	dm_digtable.dig_algorithm = DIG_ALGO_BY_RSSI;

	dm_digtable.dig_algorithm_चयन = 0;

	dm_digtable.dig_state		= DM_STA_DIG_MAX;
	dm_digtable.dig_highpwr_state	= DM_STA_DIG_MAX;
	dm_digtable.CurSTAConnectState = DIG_STA_DISCONNECT;
	dm_digtable.PreSTAConnectState = DIG_STA_DISCONNECT;

	dm_digtable.rssi_low_thresh	= DM_DIG_THRESH_LOW;
	dm_digtable.rssi_high_thresh	= DM_DIG_THRESH_HIGH;

	dm_digtable.rssi_high_घातer_lowthresh = DM_DIG_HIGH_PWR_THRESH_LOW;
	dm_digtable.rssi_high_घातer_highthresh = DM_DIG_HIGH_PWR_THRESH_HIGH;

	dm_digtable.rssi_val = 50;
	dm_digtable.backoff_val = DM_DIG_BACKOFF;
	dm_digtable.rx_gain_range_max = DM_DIG_MAX;
	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		dm_digtable.rx_gain_range_min = DM_DIG_MIN_Netcore;
	अन्यथा
		dm_digtable.rx_gain_range_min = DM_DIG_MIN;
पूर्ण

अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi(काष्ठा net_device *dev)
अणु

	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
		_rtl92e_dm_ctrl_initgain_byrssi_false_alarm(dev);
	अन्यथा अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		_rtl92e_dm_ctrl_initgain_byrssi_driver(dev);
	अन्यथा
		वापस;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	dm_CtrlInitGainBeक्रमeConnectByRssiAndFalseAlarm()
 *
 * Overview:	Driver monitor RSSI and False Alarm to change initial gain.
			Only change initial gain during link in progress.
 *
 * Input:		IN	PADAPTER	pAdapter
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	03/04/2009	hpfan	Create Version 0.
 *
 ******************************************************************************/

अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_driver(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 i;
	अटल u8	fw_dig;

	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	अगर (dm_digtable.dig_algorithm_चयन)
		fw_dig = 0;
	अगर (fw_dig <= 3) अणु
		क्रम (i = 0; i < 3; i++)
			rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);
		fw_dig++;
		dm_digtable.dig_state = DM_STA_DIG_OFF;
	पूर्ण

	अगर (priv->rtllib->state == RTLLIB_LINKED)
		dm_digtable.CurSTAConnectState = DIG_STA_CONNECT;
	अन्यथा
		dm_digtable.CurSTAConnectState = DIG_STA_DISCONNECT;


	dm_digtable.rssi_val = priv->undecorated_smoothed_pwdb;
	_rtl92e_dm_initial_gain(dev);
	_rtl92e_dm_pd_th(dev);
	_rtl92e_dm_cs_ratio(dev);
	अगर (dm_digtable.dig_algorithm_चयन)
		dm_digtable.dig_algorithm_चयन = 0;
	dm_digtable.PreSTAConnectState = dm_digtable.CurSTAConnectState;

पूर्ण

अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_false_alarm(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u32 reset_cnt;
	u8 i;

	अगर (!dm_digtable.dig_enable_flag)
		वापस;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		dm_digtable.dig_state = DM_STA_DIG_MAX;
		क्रम (i = 0; i < 3; i++)
			rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);
		dm_digtable.dig_algorithm_चयन = 0;
	पूर्ण

	अगर (priv->rtllib->state != RTLLIB_LINKED)
		वापस;

	अगर ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_low_thresh) &&
		(priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_thresh))
		वापस;
	अगर (priv->undecorated_smoothed_pwdb <= dm_digtable.rssi_low_thresh) अणु
		अगर (dm_digtable.dig_state == DM_STA_DIG_OFF &&
			(priv->reset_count == reset_cnt))
			वापस;
		reset_cnt = priv->reset_count;

		dm_digtable.dig_highpwr_state = DM_STA_DIG_MAX;
		dm_digtable.dig_state = DM_STA_DIG_OFF;

		rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);

		rtl92e_ग_लिखोb(dev, rOFDM0_XAAGCCore1, 0x17);
		rtl92e_ग_लिखोb(dev, rOFDM0_XBAGCCore1, 0x17);
		rtl92e_ग_लिखोb(dev, rOFDM0_XCAGCCore1, 0x17);
		rtl92e_ग_लिखोb(dev, rOFDM0_XDAGCCore1, 0x17);

		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x00);
		अन्यथा
			rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x42);

		rtl92e_ग_लिखोb(dev, 0xa0a, 0x08);

		वापस;
	पूर्ण

	अगर (priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh) अणु
		u8 reset_flag = 0;

		अगर (dm_digtable.dig_state == DM_STA_DIG_ON &&
		    (priv->reset_count == reset_cnt)) अणु
			_rtl92e_dm_ctrl_initgain_byrssi_highpwr(dev);
			वापस;
		पूर्ण
		अगर (priv->reset_count != reset_cnt)
			reset_flag = 1;

		reset_cnt = priv->reset_count;

		dm_digtable.dig_state = DM_STA_DIG_ON;

		अगर (reset_flag == 1) अणु
			rtl92e_ग_लिखोb(dev, rOFDM0_XAAGCCore1, 0x2c);
			rtl92e_ग_लिखोb(dev, rOFDM0_XBAGCCore1, 0x2c);
			rtl92e_ग_लिखोb(dev, rOFDM0_XCAGCCore1, 0x2c);
			rtl92e_ग_लिखोb(dev, rOFDM0_XDAGCCore1, 0x2c);
		पूर्ण अन्यथा अणु
			rtl92e_ग_लिखोb(dev, rOFDM0_XAAGCCore1, 0x20);
			rtl92e_ग_लिखोb(dev, rOFDM0_XBAGCCore1, 0x20);
			rtl92e_ग_लिखोb(dev, rOFDM0_XCAGCCore1, 0x20);
			rtl92e_ग_लिखोb(dev, rOFDM0_XDAGCCore1, 0x20);
		पूर्ण

		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x20);
		अन्यथा
			rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x44);

		rtl92e_ग_लिखोb(dev, 0xa0a, 0xcd);

		rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);
	पूर्ण
	_rtl92e_dm_ctrl_initgain_byrssi_highpwr(dev);
पूर्ण


अटल व्योम _rtl92e_dm_ctrl_initgain_byrssi_highpwr(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u32 reset_cnt_highpwr;

	अगर ((priv->undecorated_smoothed_pwdb >
	     dm_digtable.rssi_high_घातer_lowthresh) &&
	    (priv->undecorated_smoothed_pwdb <
	     dm_digtable.rssi_high_घातer_highthresh))
		वापस;

	अगर (priv->undecorated_smoothed_pwdb >=
	    dm_digtable.rssi_high_घातer_highthresh) अणु
		अगर (dm_digtable.dig_highpwr_state == DM_STA_DIG_ON &&
			(priv->reset_count == reset_cnt_highpwr))
			वापस;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_ON;

		अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x10);
		अन्यथा
			rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x43);
	पूर्ण अन्यथा अणु
		अगर (dm_digtable.dig_highpwr_state == DM_STA_DIG_OFF &&
			(priv->reset_count == reset_cnt_highpwr))
			वापस;
		dm_digtable.dig_highpwr_state = DM_STA_DIG_OFF;

		अगर ((priv->undecorated_smoothed_pwdb <
		     dm_digtable.rssi_high_घातer_lowthresh) &&
		    (priv->undecorated_smoothed_pwdb >=
		    dm_digtable.rssi_high_thresh)) अणु
			अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x20);
			अन्यथा
				rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x44);
		पूर्ण
	पूर्ण
	reset_cnt_highpwr = priv->reset_count;
पूर्ण

अटल व्योम _rtl92e_dm_initial_gain(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 initial_gain = 0;
	अटल u8 initialized, क्रमce_ग_लिखो;
	अटल u32 reset_cnt;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (rtllib_act_scanning(priv->rtllib, true)) अणु
		क्रमce_ग_लिखो = 1;
		वापस;
	पूर्ण

	अगर (dm_digtable.PreSTAConnectState == dm_digtable.CurSTAConnectState) अणु
		अगर (dm_digtable.CurSTAConnectState == DIG_STA_CONNECT) अणु
			दीर्घ gain_range = dm_digtable.rssi_val + 10 -
					  dm_digtable.backoff_val;
			gain_range = clamp_t(दीर्घ, gain_range,
					     dm_digtable.rx_gain_range_min,
					     dm_digtable.rx_gain_range_max);
			dm_digtable.cur_ig_value = gain_range;
		पूर्ण अन्यथा अणु
			अगर (dm_digtable.cur_ig_value == 0)
				dm_digtable.cur_ig_value = priv->DefaultInitialGain[0];
			अन्यथा
				dm_digtable.cur_ig_value = dm_digtable.pre_ig_value;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable.cur_ig_value = priv->DefaultInitialGain[0];
		dm_digtable.pre_ig_value = 0;
	पूर्ण

	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण

	अगर (dm_digtable.pre_ig_value != rtl92e_पढ़ोb(dev, rOFDM0_XAAGCCore1))
		क्रमce_ग_लिखो = 1;

	अगर ((dm_digtable.pre_ig_value != dm_digtable.cur_ig_value)
	    || !initialized || क्रमce_ग_लिखो) अणु
		initial_gain = (u8)dm_digtable.cur_ig_value;
		rtl92e_ग_लिखोb(dev, rOFDM0_XAAGCCore1, initial_gain);
		rtl92e_ग_लिखोb(dev, rOFDM0_XBAGCCore1, initial_gain);
		rtl92e_ग_लिखोb(dev, rOFDM0_XCAGCCore1, initial_gain);
		rtl92e_ग_लिखोb(dev, rOFDM0_XDAGCCore1, initial_gain);
		dm_digtable.pre_ig_value = dm_digtable.cur_ig_value;
		initialized = 1;
		क्रमce_ग_लिखो = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_pd_th(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u8 initialized, क्रमce_ग_लिखो;
	अटल u32 reset_cnt;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (dm_digtable.PreSTAConnectState == dm_digtable.CurSTAConnectState) अणु
		अगर (dm_digtable.CurSTAConnectState == DIG_STA_CONNECT) अणु
			अगर (dm_digtable.rssi_val >=
			    dm_digtable.rssi_high_घातer_highthresh)
				dm_digtable.curpd_thstate =
							DIG_PD_AT_HIGH_POWER;
			अन्यथा अगर (dm_digtable.rssi_val <=
				 dm_digtable.rssi_low_thresh)
				dm_digtable.curpd_thstate =
							DIG_PD_AT_LOW_POWER;
			अन्यथा अगर ((dm_digtable.rssi_val >=
				  dm_digtable.rssi_high_thresh) &&
				 (dm_digtable.rssi_val <
				  dm_digtable.rssi_high_घातer_lowthresh))
				dm_digtable.curpd_thstate =
							DIG_PD_AT_NORMAL_POWER;
			अन्यथा
				dm_digtable.curpd_thstate =
						dm_digtable.prepd_thstate;
		पूर्ण अन्यथा अणु
			dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable.curpd_thstate = DIG_PD_AT_LOW_POWER;
	पूर्ण

	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण

	अगर ((dm_digtable.prepd_thstate != dm_digtable.curpd_thstate) ||
	    (initialized <= 3) || क्रमce_ग_लिखो) अणु
		अगर (dm_digtable.curpd_thstate == DIG_PD_AT_LOW_POWER) अणु
			अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x00);
			अन्यथा
				rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x42);
		पूर्ण अन्यथा अगर (dm_digtable.curpd_thstate ==
			   DIG_PD_AT_NORMAL_POWER) अणु
			अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x20);
			अन्यथा
				rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x44);
		पूर्ण अन्यथा अगर (dm_digtable.curpd_thstate == DIG_PD_AT_HIGH_POWER) अणु
			अगर (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
				rtl92e_ग_लिखोb(dev, (rOFDM0_XATxAFE+3), 0x10);
			अन्यथा
				rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector1, 0x43);
		पूर्ण
		dm_digtable.prepd_thstate = dm_digtable.curpd_thstate;
		अगर (initialized <= 3)
			initialized++;
		क्रमce_ग_लिखो = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_cs_ratio(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u8 initialized, क्रमce_ग_लिखो;
	अटल u32 reset_cnt;

	अगर (dm_digtable.dig_algorithm_चयन) अणु
		initialized = 0;
		reset_cnt = 0;
	पूर्ण

	अगर (dm_digtable.PreSTAConnectState == dm_digtable.CurSTAConnectState) अणु
		अगर (dm_digtable.CurSTAConnectState == DIG_STA_CONNECT) अणु
			अगर (dm_digtable.rssi_val <= dm_digtable.rssi_low_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
			अन्यथा अगर (dm_digtable.rssi_val >= dm_digtable.rssi_high_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_HIGHER;
			अन्यथा
				dm_digtable.curcs_ratio_state = dm_digtable.precs_ratio_state;
		पूर्ण अन्यथा अणु
			dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
	पूर्ण

	अगर (priv->reset_count != reset_cnt) अणु
		क्रमce_ग_लिखो = 1;
		reset_cnt = priv->reset_count;
	पूर्ण


	अगर ((dm_digtable.precs_ratio_state != dm_digtable.curcs_ratio_state) ||
	    !initialized || क्रमce_ग_लिखो) अणु
		अगर (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_LOWER)
			rtl92e_ग_लिखोb(dev, 0xa0a, 0x08);
		अन्यथा अगर (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_HIGHER)
			rtl92e_ग_लिखोb(dev, 0xa0a, 0xcd);
		dm_digtable.precs_ratio_state = dm_digtable.curcs_ratio_state;
		initialized = 1;
		क्रमce_ग_लिखो = 0;
	पूर्ण
पूर्ण

व्योम rtl92e_dm_init_edca_turbo(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->bcurrent_turbo_EDCA = false;
	priv->rtllib->bis_any_nonbepkts = false;
	priv->bis_cur_rdlstate = false;
पूर्ण

अटल व्योम _rtl92e_dm_check_edca_turbo(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;

	अटल अचिन्हित दीर्घ lastTxOkCnt;
	अटल अचिन्हित दीर्घ lastRxOkCnt;
	अचिन्हित दीर्घ curTxOkCnt = 0;
	अचिन्हित दीर्घ curRxOkCnt = 0;

	अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC)
		जाओ dm_CheckEdcaTurbo_EXIT;
	अगर (priv->rtllib->state != RTLLIB_LINKED)
		जाओ dm_CheckEdcaTurbo_EXIT;
	अगर (priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		जाओ dm_CheckEdcaTurbo_EXIT;

	अगर (!priv->rtllib->bis_any_nonbepkts) अणु
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		अगर (pHTInfo->IOTAction & HT_IOT_ACT_EDCA_BIAS_ON_RX) अणु
			अगर (curTxOkCnt > 4*curRxOkCnt) अणु
				अगर (priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) अणु
					rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
						      edca_setting_UL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) अणु
					अगर (priv->rtllib->mode == WIRELESS_MODE_G)
						rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
							      edca_setting_DL_GMode[pHTInfo->IOTPeer]);
					अन्यथा
						rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
							      edca_setting_DL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = true;
				पूर्ण
			पूर्ण
			priv->bcurrent_turbo_EDCA = true;
		पूर्ण अन्यथा अणु
			अगर (curRxOkCnt > 4*curTxOkCnt) अणु
				अगर (!priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) अणु
					अगर (priv->rtllib->mode == WIRELESS_MODE_G)
						rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
							      edca_setting_DL_GMode[pHTInfo->IOTPeer]);
					अन्यथा
						rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
							      edca_setting_DL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (priv->bis_cur_rdlstate ||
				    !priv->bcurrent_turbo_EDCA) अणु
					rtl92e_ग_लिखोl(dev, EDCAPARA_BE,
						      edca_setting_UL[pHTInfo->IOTPeer]);
					priv->bis_cur_rdlstate = false;
				पूर्ण

			पूर्ण

			priv->bcurrent_turbo_EDCA = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		 अगर (priv->bcurrent_turbo_EDCA) अणु
			u8 पंचांगp = AC0_BE;

			priv->rtllib->SetHwRegHandler(dev, HW_VAR_AC_PARAM,
						      (u8 *)(&पंचांगp));
			priv->bcurrent_turbo_EDCA = false;
		पूर्ण
	पूर्ण


dm_CheckEdcaTurbo_EXIT:
	priv->rtllib->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
पूर्ण

अटल व्योम _rtl92e_dm_init_cts_to_self(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv((काष्ठा net_device *)dev);

	priv->rtllib->bCTSToSelfEnable = true;
पूर्ण

अटल व्योम _rtl92e_dm_cts_to_self(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv((काष्ठा net_device *)dev);
	काष्ठा rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;
	अटल अचिन्हित दीर्घ lastTxOkCnt;
	अटल अचिन्हित दीर्घ lastRxOkCnt;
	अचिन्हित दीर्घ curTxOkCnt = 0;
	अचिन्हित दीर्घ curRxOkCnt = 0;

	अगर (!priv->rtllib->bCTSToSelfEnable) अणु
		pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		वापस;
	पूर्ण
	अगर (pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) अणु
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		अगर (curRxOkCnt > 4*curTxOkCnt)
			pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		अन्यथा
			pHTInfo->IOTAction |= HT_IOT_ACT_FORCED_CTS2SELF;

		lastTxOkCnt = priv->stats.txbytesunicast;
		lastRxOkCnt = priv->stats.rxbytesunicast;
	पूर्ण
पूर्ण


अटल व्योम _rtl92e_dm_init_wa_broadcom_iot(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv((काष्ठा net_device *)dev);
	काष्ठा rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;

	pHTInfo->bWAIotBroadcom = false;
	pHTInfo->WAIotTH = WAIotTHVal;
पूर्ण

अटल व्योम _rtl92e_dm_check_rf_ctrl_gpio(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_dwork_rsl(data,
				  काष्ठा r8192_priv, gpio_change_rf_wq);
	काष्ठा net_device *dev = priv->rtllib->dev;
	u8 पंचांगp1byte;
	क्रमागत rt_rf_घातer_state eRfPowerStateToSet;
	bool bActuallySet = false;
	अक्षर *argv[3];
	अटल स्थिर अक्षर RadioPowerPath[] = "/etc/acpi/events/RadioPower.sh";
	अटल अक्षर *envp[] = अणु"HOME=/", "TERM=linux", "PATH=/usr/bin:/bin",
			       शून्यपूर्ण;

	bActuallySet = false;

	अगर ((priv->up_first_समय == 1) || (priv->being_init_adapter))
		वापस;

	अगर (priv->bfirst_after_करोwn) अणु
		priv->bfirst_after_करोwn = true;
		वापस;
	पूर्ण

	पंचांगp1byte = rtl92e_पढ़ोb(dev, GPI);

	eRfPowerStateToSet = (पंचांगp1byte&BIT1) ?  eRfOn : eRfOff;

	अगर (priv->bHwRadioOff && (eRfPowerStateToSet == eRfOn)) अणु
		RT_TRACE(COMP_RF, "gpiochangeRF  - HW Radio ON\n");
		netdev_info(dev, "gpiochangeRF  - HW Radio ON\n");
		priv->bHwRadioOff = false;
		bActuallySet = true;
	पूर्ण अन्यथा अगर (!priv->bHwRadioOff && (eRfPowerStateToSet == eRfOff)) अणु
		RT_TRACE(COMP_RF, "gpiochangeRF  - HW Radio OFF\n");
		netdev_info(dev, "gpiochangeRF  - HW Radio OFF\n");
		priv->bHwRadioOff = true;
		bActuallySet = true;
	पूर्ण

	अगर (bActuallySet) अणु
		mdelay(1000);
		priv->bHwRfOffAction = 1;
		rtl92e_set_rf_state(dev, eRfPowerStateToSet, RF_CHANGE_BY_HW);
		अगर (priv->bHwRadioOff)
			argv[1] = "RFOFF";
		अन्यथा
			argv[1] = "RFON";

		argv[0] = (अक्षर *)RadioPowerPath;
		argv[2] = शून्य;
		call_usermodehelper(RadioPowerPath, argv, envp, UMH_WAIT_PROC);
	पूर्ण
पूर्ण

व्योम rtl92e_dm_rf_pathcheck_wq(व्योम *data)
अणु
	काष्ठा r8192_priv *priv = container_of_dwork_rsl(data,
				  काष्ठा r8192_priv,
				  rfpath_check_wq);
	काष्ठा net_device *dev = priv->rtllib->dev;
	u8 rfpath, i;

	rfpath = rtl92e_पढ़ोb(dev, 0xc04);

	क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
		अगर (rfpath & (0x01<<i))
			priv->brfpath_rxenable[i] = true;
		अन्यथा
			priv->brfpath_rxenable[i] = false;
	पूर्ण
	अगर (!DM_RxPathSelTable.Enable)
		वापस;

	_rtl92e_dm_rx_path_sel_byrssi(dev);
पूर्ण

अटल व्योम _rtl92e_dm_init_rx_path_selection(काष्ठा net_device *dev)
अणु
	u8 i;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	DM_RxPathSelTable.Enable = 1;
	DM_RxPathSelTable.SS_TH_low = RxPathSelection_SS_TH_low;
	DM_RxPathSelTable.dअगरf_TH = RxPathSelection_dअगरf_TH;
	अगर (priv->CustomerID == RT_CID_819x_Netcore)
		DM_RxPathSelTable.cck_method = CCK_Rx_Version_2;
	अन्यथा
		DM_RxPathSelTable.cck_method = CCK_Rx_Version_1;
	DM_RxPathSelTable.disabledRF = 0;
	क्रम (i = 0; i < 4; i++) अणु
		DM_RxPathSelTable.rf_rssi[i] = 50;
		DM_RxPathSelTable.cck_pwdb_sta[i] = -64;
		DM_RxPathSelTable.rf_enable_rssi_th[i] = 100;
	पूर्ण
पूर्ण

#घोषणा PWDB_IN_RANGE	((cur_cck_pwdb < पंचांगp_cck_max_pwdb) &&	\
			(cur_cck_pwdb > पंचांगp_cck_sec_pwdb))

अटल व्योम _rtl92e_dm_rx_path_sel_byrssi(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 i, max_rssi_index = 0, min_rssi_index = 0;
	u8 sec_rssi_index = 0, rf_num = 0;
	u8 पंचांगp_max_rssi = 0, पंचांगp_min_rssi = 0, पंचांगp_sec_rssi = 0;
	u8 cck_शेष_Rx = 0x2;
	u8 cck_optional_Rx = 0x3;
	दीर्घ पंचांगp_cck_max_pwdb = 0, पंचांगp_cck_min_pwdb = 0, पंचांगp_cck_sec_pwdb = 0;
	u8 cck_rx_ver2_max_index = 0;
	u8 cck_rx_ver2_sec_index = 0;
	u8 cur_rf_rssi;
	दीर्घ cur_cck_pwdb;
	अटल u8 disabled_rf_cnt, cck_Rx_Path_initialized;
	u8 update_cck_rx_path;

	अगर (priv->rf_type != RF_2T4R)
		वापस;

	अगर (!cck_Rx_Path_initialized) अणु
		DM_RxPathSelTable.cck_Rx_path = (rtl92e_पढ़ोb(dev, 0xa07)&0xf);
		cck_Rx_Path_initialized = 1;
	पूर्ण

	DM_RxPathSelTable.disabledRF = 0xf;
	DM_RxPathSelTable.disabledRF &= ~(rtl92e_पढ़ोb(dev, 0xc04));

	अगर (priv->rtllib->mode == WIRELESS_MODE_B)
		DM_RxPathSelTable.cck_method = CCK_Rx_Version_2;

	क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
		DM_RxPathSelTable.rf_rssi[i] = priv->stats.rx_rssi_percentage[i];

		अगर (priv->brfpath_rxenable[i]) अणु
			rf_num++;
			cur_rf_rssi = DM_RxPathSelTable.rf_rssi[i];

			अगर (rf_num == 1) अणु
				max_rssi_index = min_rssi_index = sec_rssi_index = i;
				पंचांगp_max_rssi = पंचांगp_min_rssi = पंचांगp_sec_rssi = cur_rf_rssi;
			पूर्ण अन्यथा अगर (rf_num == 2) अणु
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
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_max_rssi) अणु
					पंचांगp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				पूर्ण अन्यथा अगर ((cur_rf_rssi < पंचांगp_max_rssi) &&
					   (cur_rf_rssi > पंचांगp_sec_rssi)) अणु
					पंचांगp_sec_rssi = cur_rf_rssi;
					sec_rssi_index = i;
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_sec_rssi) अणु
					अगर (पंचांगp_sec_rssi == पंचांगp_min_rssi) अणु
						पंचांगp_sec_rssi = cur_rf_rssi;
						sec_rssi_index = i;
					पूर्ण
				पूर्ण अन्यथा अगर ((cur_rf_rssi < पंचांगp_sec_rssi) &&
					   (cur_rf_rssi > पंचांगp_min_rssi)) अणु
					;
				पूर्ण अन्यथा अगर (cur_rf_rssi == पंचांगp_min_rssi) अणु
					अगर (पंचांगp_sec_rssi == पंचांगp_min_rssi) अणु
						पंचांगp_min_rssi = cur_rf_rssi;
						min_rssi_index = i;
					पूर्ण
				पूर्ण अन्यथा अगर (cur_rf_rssi < पंचांगp_min_rssi) अणु
					पंचांगp_min_rssi = cur_rf_rssi;
					min_rssi_index = i;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	rf_num = 0;
	अगर (DM_RxPathSelTable.cck_method == CCK_Rx_Version_2) अणु
		क्रम (i = 0; i < RF90_PATH_MAX; i++) अणु
			अगर (priv->brfpath_rxenable[i]) अणु
				rf_num++;
				cur_cck_pwdb =
					 DM_RxPathSelTable.cck_pwdb_sta[i];

				अगर (rf_num == 1) अणु
					cck_rx_ver2_max_index = i;
					cck_rx_ver2_sec_index = i;
					पंचांगp_cck_max_pwdb = cur_cck_pwdb;
					पंचांगp_cck_min_pwdb = cur_cck_pwdb;
					पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
				पूर्ण अन्यथा अगर (rf_num == 2) अणु
					अगर (cur_cck_pwdb >= पंचांगp_cck_max_pwdb) अणु
						पंचांगp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					पूर्ण अन्यथा अणु
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						पंचांगp_cck_min_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (cur_cck_pwdb > पंचांगp_cck_max_pwdb) अणु
						पंचांगp_cck_sec_pwdb =
							 पंचांगp_cck_max_pwdb;
						cck_rx_ver2_sec_index =
							 cck_rx_ver2_max_index;
						पंचांगp_cck_max_pwdb = cur_cck_pwdb;
						cck_rx_ver2_max_index = i;
					पूर्ण अन्यथा अगर (cur_cck_pwdb ==
						   पंचांगp_cck_max_pwdb) अणु
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					पूर्ण अन्यथा अगर (PWDB_IN_RANGE) अणु
						पंचांगp_cck_sec_pwdb = cur_cck_pwdb;
						cck_rx_ver2_sec_index = i;
					पूर्ण अन्यथा अगर (cur_cck_pwdb ==
						   पंचांगp_cck_sec_pwdb) अणु
						अगर (पंचांगp_cck_sec_pwdb ==
						    पंचांगp_cck_min_pwdb) अणु
							पंचांगp_cck_sec_pwdb =
								 cur_cck_pwdb;
							cck_rx_ver2_sec_index =
								 i;
						पूर्ण
					पूर्ण अन्यथा अगर ((cur_cck_pwdb < पंचांगp_cck_sec_pwdb) &&
						   (cur_cck_pwdb > पंचांगp_cck_min_pwdb)) अणु
						;
					पूर्ण अन्यथा अगर (cur_cck_pwdb == पंचांगp_cck_min_pwdb) अणु
						अगर (पंचांगp_cck_sec_pwdb == पंचांगp_cck_min_pwdb)
							पंचांगp_cck_min_pwdb = cur_cck_pwdb;
					पूर्ण अन्यथा अगर (cur_cck_pwdb < पंचांगp_cck_min_pwdb) अणु
						पंचांगp_cck_min_pwdb = cur_cck_pwdb;
					पूर्ण
				पूर्ण

			पूर्ण
		पूर्ण
	पूर्ण

	update_cck_rx_path = 0;
	अगर (DM_RxPathSelTable.cck_method == CCK_Rx_Version_2) अणु
		cck_शेष_Rx = cck_rx_ver2_max_index;
		cck_optional_Rx = cck_rx_ver2_sec_index;
		अगर (पंचांगp_cck_max_pwdb != -64)
			update_cck_rx_path = 1;
	पूर्ण

	अगर (पंचांगp_min_rssi < DM_RxPathSelTable.SS_TH_low && disabled_rf_cnt < 2) अणु
		अगर ((पंचांगp_max_rssi - पंचांगp_min_rssi) >=
		     DM_RxPathSelTable.dअगरf_TH) अणु
			DM_RxPathSelTable.rf_enable_rssi_th[min_rssi_index] =
				 पंचांगp_max_rssi+5;
			rtl92e_set_bb_reg(dev, rOFDM0_TRxPathEnable,
					  0x1<<min_rssi_index, 0x0);
			rtl92e_set_bb_reg(dev, rOFDM1_TRxPathEnable,
					  0x1<<min_rssi_index, 0x0);
			disabled_rf_cnt++;
		पूर्ण
		अगर (DM_RxPathSelTable.cck_method == CCK_Rx_Version_1) अणु
			cck_शेष_Rx = max_rssi_index;
			cck_optional_Rx = sec_rssi_index;
			अगर (पंचांगp_max_rssi)
				update_cck_rx_path = 1;
		पूर्ण
	पूर्ण

	अगर (update_cck_rx_path) अणु
		DM_RxPathSelTable.cck_Rx_path = (cck_शेष_Rx<<2) |
						(cck_optional_Rx);
		rtl92e_set_bb_reg(dev, rCCK0_AFESetting, 0x0f000000,
				  DM_RxPathSelTable.cck_Rx_path);
	पूर्ण

	अगर (DM_RxPathSelTable.disabledRF) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर ((DM_RxPathSelTable.disabledRF>>i) & 0x1) अणु
				अगर (पंचांगp_max_rssi >=
				    DM_RxPathSelTable.rf_enable_rssi_th[i]) अणु
					rtl92e_set_bb_reg(dev,
							  rOFDM0_TRxPathEnable,
							  0x1 << i, 0x1);
					rtl92e_set_bb_reg(dev,
							  rOFDM1_TRxPathEnable,
							  0x1 << i, 0x1);
					DM_RxPathSelTable.rf_enable_rssi_th[i]
						 = 100;
					disabled_rf_cnt--;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_dm_check_rx_path_selection(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	schedule_delayed_work(&priv->rfpath_check_wq, 0);
पूर्ण


अटल व्योम _rtl92e_dm_init_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->rtllib->fsync_समय_पूर्णांकerval = 500;
	priv->rtllib->fsync_rate_biपंचांगap = 0x0f000800;
	priv->rtllib->fsync_rssi_threshold = 30;
	priv->rtllib->bfsync_enable = false;
	priv->rtllib->fsync_multiple_समयपूर्णांकerval = 3;
	priv->rtllib->fsync_firstdअगरf_ratethreshold = 100;
	priv->rtllib->fsync_seconddअगरf_ratethreshold = 200;
	priv->rtllib->fsync_state = Default_Fsync;
	priv->framesyncMonitor = 1;

	समयr_setup(&priv->fsync_समयr, _rtl92e_dm_fsync_समयr_callback, 0);
पूर्ण


अटल व्योम _rtl92e_dm_deinit_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	del_समयr_sync(&priv->fsync_समयr);
पूर्ण

अटल व्योम _rtl92e_dm_fsync_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा r8192_priv *priv = from_समयr(priv, t, fsync_समयr);
	काष्ठा net_device *dev = priv->rtllib->dev;
	u32 rate_index, rate_count = 0, rate_count_dअगरf = 0;
	bool		bSwitchFromCountDअगरf = false;
	bool		bDoubleTimeInterval = false;

	अगर (priv->rtllib->state == RTLLIB_LINKED &&
	    priv->rtllib->bfsync_enable &&
	    (priv->rtllib->pHTInfo->IOTAction & HT_IOT_ACT_CDD_FSYNC)) अणु
		u32 rate_biपंचांगap;

		क्रम (rate_index = 0; rate_index <= 27; rate_index++) अणु
			rate_biपंचांगap  = 1 << rate_index;
			अगर (priv->rtllib->fsync_rate_biपंचांगap &  rate_biपंचांगap)
				rate_count +=
				   priv->stats.received_rate_histogram[1]
				   [rate_index];
		पूर्ण

		अगर (rate_count < priv->rate_record)
			rate_count_dअगरf = 0xffffffff - rate_count +
					  priv->rate_record;
		अन्यथा
			rate_count_dअगरf = rate_count - priv->rate_record;
		अगर (rate_count_dअगरf < priv->rateCountDअगरfRecord) अणु

			u32 DअगरfNum = priv->rateCountDअगरfRecord -
				      rate_count_dअगरf;
			अगर (DअगरfNum >=
			    priv->rtllib->fsync_seconddअगरf_ratethreshold)
				priv->ContinueDअगरfCount++;
			अन्यथा
				priv->ContinueDअगरfCount = 0;

			अगर (priv->ContinueDअगरfCount >= 2) अणु
				bSwitchFromCountDअगरf = true;
				priv->ContinueDअगरfCount = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->ContinueDअगरfCount = 0;
		पूर्ण

		अगर (rate_count_dअगरf <=
		    priv->rtllib->fsync_firstdअगरf_ratethreshold) अणु
			bSwitchFromCountDअगरf = true;
			priv->ContinueDअगरfCount = 0;
		पूर्ण
		priv->rate_record = rate_count;
		priv->rateCountDअगरfRecord = rate_count_dअगरf;
		RT_TRACE(COMP_HALDM,
			 "rateRecord %d rateCount %d, rateCountdiff %d bSwitchFsync %d\n",
			 priv->rate_record, rate_count, rate_count_dअगरf,
			 priv->bचयन_fsync);
		अगर (priv->undecorated_smoothed_pwdb >
		    priv->rtllib->fsync_rssi_threshold &&
		    bSwitchFromCountDअगरf) अणु
			bDoubleTimeInterval = true;
			priv->bचयन_fsync = !priv->bचयन_fsync;
			अगर (priv->bचयन_fsync) अणु
				rtl92e_ग_लिखोb(dev, 0xC36, 0x1c);
				rtl92e_ग_लिखोb(dev, 0xC3e, 0x90);
			पूर्ण अन्यथा अणु
				rtl92e_ग_लिखोb(dev, 0xC36, 0x5c);
				rtl92e_ग_लिखोb(dev, 0xC3e, 0x96);
			पूर्ण
		पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb <=
			   priv->rtllib->fsync_rssi_threshold) अणु
			अगर (priv->bचयन_fsync) अणु
				priv->bचयन_fsync  = false;
				rtl92e_ग_लिखोb(dev, 0xC36, 0x5c);
				rtl92e_ग_लिखोb(dev, 0xC3e, 0x96);
			पूर्ण
		पूर्ण
		अगर (bDoubleTimeInterval) अणु
			अगर (समयr_pending(&priv->fsync_समयr))
				del_समयr_sync(&priv->fsync_समयr);
			priv->fsync_समयr.expires = jअगरfies +
				 msecs_to_jअगरfies(priv->rtllib->fsync_समय_पूर्णांकerval *
				 priv->rtllib->fsync_multiple_समयपूर्णांकerval);
			add_समयr(&priv->fsync_समयr);
		पूर्ण अन्यथा अणु
			अगर (समयr_pending(&priv->fsync_समयr))
				del_समयr_sync(&priv->fsync_समयr);
			priv->fsync_समयr.expires = jअगरfies +
				 msecs_to_jअगरfies(priv->rtllib->fsync_समय_पूर्णांकerval);
			add_समयr(&priv->fsync_समयr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->bचयन_fsync) अणु
			priv->bचयन_fsync  = false;
			rtl92e_ग_लिखोb(dev, 0xC36, 0x5c);
			rtl92e_ग_लिखोb(dev, 0xC3e, 0x96);
		पूर्ण
		priv->ContinueDअगरfCount = 0;
		rtl92e_ग_लिखोl(dev, rOFDM0_RxDetector2, 0x465c52cd);
	पूर्ण
	RT_TRACE(COMP_HALDM, "ContinueDiffCount %d\n", priv->ContinueDअगरfCount);
	RT_TRACE(COMP_HALDM,
		 "rateRecord %d rateCount %d, rateCountdiff %d bSwitchFsync %d\n",
		 priv->rate_record, rate_count, rate_count_dअगरf,
		 priv->bचयन_fsync);
पूर्ण

अटल व्योम _rtl92e_dm_start_hw_fsync(काष्ठा net_device *dev)
अणु
	u8 rf_timing = 0x77;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	rtl92e_ग_लिखोl(dev, rOFDM0_RxDetector2, 0x465c12cf);
	priv->rtllib->SetHwRegHandler(dev, HW_VAR_RF_TIMING,
				      (u8 *)(&rf_timing));
	rtl92e_ग_लिखोb(dev, 0xc3b, 0x41);
पूर्ण

अटल व्योम _rtl92e_dm_end_hw_fsync(काष्ठा net_device *dev)
अणु
	u8 rf_timing = 0xaa;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	rtl92e_ग_लिखोl(dev, rOFDM0_RxDetector2, 0x465c52cd);
	priv->rtllib->SetHwRegHandler(dev, HW_VAR_RF_TIMING, (u8 *)
				     (&rf_timing));
	rtl92e_ग_लिखोb(dev, 0xc3b, 0x49);
पूर्ण

अटल व्योम _rtl92e_dm_end_sw_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	del_समयr_sync(&(priv->fsync_समयr));

	अगर (priv->bचयन_fsync) अणु
		priv->bचयन_fsync  = false;

		rtl92e_ग_लिखोb(dev, 0xC36, 0x5c);

		rtl92e_ग_लिखोb(dev, 0xC3e, 0x96);
	पूर्ण

	priv->ContinueDअगरfCount = 0;
	rtl92e_ग_लिखोl(dev, rOFDM0_RxDetector2, 0x465c52cd);
पूर्ण

अटल व्योम _rtl92e_dm_start_sw_fsync(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32			rateIndex;
	u32			rateBiपंचांगap;

	RT_TRACE(COMP_HALDM, "%s\n", __func__);
	priv->rate_record = 0;
	priv->ContinueDअगरfCount = 0;
	priv->rateCountDअगरfRecord = 0;
	priv->bचयन_fsync  = false;

	अगर (priv->rtllib->mode == WIRELESS_MODE_N_24G) अणु
		priv->rtllib->fsync_firstdअगरf_ratethreshold = 600;
		priv->rtllib->fsync_seconddअगरf_ratethreshold = 0xffff;
	पूर्ण अन्यथा अणु
		priv->rtllib->fsync_firstdअगरf_ratethreshold = 200;
		priv->rtllib->fsync_seconddअगरf_ratethreshold = 200;
	पूर्ण
	क्रम (rateIndex = 0; rateIndex <= 27; rateIndex++) अणु
		rateBiपंचांगap  = 1 << rateIndex;
		अगर (priv->rtllib->fsync_rate_biपंचांगap & rateBiपंचांगap)
			priv->rate_record +=
				 priv->stats.received_rate_histogram[1]
				[rateIndex];
	पूर्ण
	अगर (समयr_pending(&priv->fsync_समयr))
		del_समयr_sync(&priv->fsync_समयr);
	priv->fsync_समयr.expires = jअगरfies +
				    msecs_to_jअगरfies(priv->rtllib->fsync_समय_पूर्णांकerval);
	add_समयr(&priv->fsync_समयr);

	rtl92e_ग_लिखोl(dev, rOFDM0_RxDetector2, 0x465c12cd);

पूर्ण

अटल व्योम _rtl92e_dm_check_fsync(काष्ठा net_device *dev)
अणु
#घोषणा	RegC38_Default			0
#घोषणा	RegC38_NonFsync_Other_AP	1
#घोषणा	RegC38_Fsync_AP_BCM		2
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अटल u8 reg_c38_State = RegC38_Default;
	अटल u32 reset_cnt;

	RT_TRACE(COMP_HALDM,
		 "RSSI %d TimeInterval %d MultipleTimeInterval %d\n",
		 priv->rtllib->fsync_rssi_threshold,
		 priv->rtllib->fsync_समय_पूर्णांकerval,
		 priv->rtllib->fsync_multiple_समयपूर्णांकerval);
	RT_TRACE(COMP_HALDM,
		 "RateBitmap 0x%x FirstDiffRateThreshold %d SecondDiffRateThreshold %d\n",
		 priv->rtllib->fsync_rate_biपंचांगap,
		 priv->rtllib->fsync_firstdअगरf_ratethreshold,
		 priv->rtllib->fsync_seconddअगरf_ratethreshold);

	अगर (priv->rtllib->state == RTLLIB_LINKED &&
	    priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) अणु
		अगर (priv->rtllib->bfsync_enable == 0) अणु
			चयन (priv->rtllib->fsync_state) अणु
			हाल Default_Fsync:
				_rtl92e_dm_start_hw_fsync(dev);
				priv->rtllib->fsync_state = HW_Fsync;
				अवरोध;
			हाल SW_Fsync:
				_rtl92e_dm_end_sw_fsync(dev);
				_rtl92e_dm_start_hw_fsync(dev);
				priv->rtllib->fsync_state = HW_Fsync;
				अवरोध;
			हाल HW_Fsync:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (priv->rtllib->fsync_state) अणु
			हाल Default_Fsync:
				_rtl92e_dm_start_sw_fsync(dev);
				priv->rtllib->fsync_state = SW_Fsync;
				अवरोध;
			हाल HW_Fsync:
				_rtl92e_dm_end_hw_fsync(dev);
				_rtl92e_dm_start_sw_fsync(dev);
				priv->rtllib->fsync_state = SW_Fsync;
				अवरोध;
			हाल SW_Fsync:
			शेष:
				अवरोध;

			पूर्ण
		पूर्ण
		अगर (priv->framesyncMonitor) अणु
			अगर (reg_c38_State != RegC38_Fsync_AP_BCM) अणु
				rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector3, 0x95);

				reg_c38_State = RegC38_Fsync_AP_BCM;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (priv->rtllib->fsync_state) अणु
		हाल HW_Fsync:
			_rtl92e_dm_end_hw_fsync(dev);
			priv->rtllib->fsync_state = Default_Fsync;
			अवरोध;
		हाल SW_Fsync:
			_rtl92e_dm_end_sw_fsync(dev);
			priv->rtllib->fsync_state = Default_Fsync;
			अवरोध;
		हाल Default_Fsync:
		शेष:
			अवरोध;
		पूर्ण

		अगर (priv->framesyncMonitor) अणु
			अगर (priv->rtllib->state == RTLLIB_LINKED) अणु
				अगर (priv->undecorated_smoothed_pwdb <=
				    RegC38_TH) अणु
					अगर (reg_c38_State !=
					    RegC38_NonFsync_Other_AP) अणु
						rtl92e_ग_लिखोb(dev,
							      rOFDM0_RxDetector3,
							      0x90);

						reg_c38_State =
						     RegC38_NonFsync_Other_AP;
					पूर्ण
				पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb >=
					   (RegC38_TH+5)) अणु
					अगर (reg_c38_State) अणु
						rtl92e_ग_लिखोb(dev,
							rOFDM0_RxDetector3,
							priv->framesync);
						reg_c38_State = RegC38_Default;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (reg_c38_State) अणु
					rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector3,
						      priv->framesync);
					reg_c38_State = RegC38_Default;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (priv->framesyncMonitor) अणु
		अगर (priv->reset_count != reset_cnt) अणु
			rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector3,
				       priv->framesync);
			reg_c38_State = RegC38_Default;
			reset_cnt = priv->reset_count;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (reg_c38_State) अणु
			rtl92e_ग_लिखोb(dev, rOFDM0_RxDetector3,
				       priv->framesync);
			reg_c38_State = RegC38_Default;
		पूर्ण
	पूर्ण
पूर्ण

/*---------------------------Define function prototype------------------------*/
अटल व्योम _rtl92e_dm_init_dynamic_tx_घातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->rtllib->bdynamic_txघातer_enable = true;
	priv->bLastDTPFlag_High = false;
	priv->bLastDTPFlag_Low = false;
	priv->bDynamicTxHighPower = false;
	priv->bDynamicTxLowPower = false;
पूर्ण

अटल व्योम _rtl92e_dm_dynamic_tx_घातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	अचिन्हित पूर्णांक txhiघातer_threshold = 0;
	अचिन्हित पूर्णांक txlowघातer_threshold = 0;

	अगर (!priv->rtllib->bdynamic_txघातer_enable) अणु
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
		वापस;
	पूर्ण
	अगर ((priv->rtllib->pHTInfo->IOTPeer == HT_IOT_PEER_ATHEROS) &&
	    (priv->rtllib->mode == IEEE_G)) अणु
		txhiघातer_threshold = TX_POWER_ATHEROAP_THRESH_HIGH;
		txlowघातer_threshold = TX_POWER_ATHEROAP_THRESH_LOW;
	पूर्ण अन्यथा अणु
		txhiघातer_threshold = TX_POWER_NEAR_FIELD_THRESH_HIGH;
		txlowघातer_threshold = TX_POWER_NEAR_FIELD_THRESH_LOW;
	पूर्ण

	RT_TRACE(COMP_TXAGC, "priv->undecorated_smoothed_pwdb = %ld\n",
		 priv->undecorated_smoothed_pwdb);

	अगर (priv->rtllib->state == RTLLIB_LINKED) अणु
		अगर (priv->undecorated_smoothed_pwdb >= txhiघातer_threshold) अणु
			priv->bDynamicTxHighPower = true;
			priv->bDynamicTxLowPower = false;
		पूर्ण अन्यथा अणु
			अगर (priv->undecorated_smoothed_pwdb <
			    txlowघातer_threshold && priv->bDynamicTxHighPower)
				priv->bDynamicTxHighPower = false;
			अगर (priv->undecorated_smoothed_pwdb < 35)
				priv->bDynamicTxLowPower = true;
			अन्यथा अगर (priv->undecorated_smoothed_pwdb >= 40)
				priv->bDynamicTxLowPower = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
	पूर्ण

	अगर ((priv->bDynamicTxHighPower != priv->bLastDTPFlag_High) ||
	    (priv->bDynamicTxLowPower != priv->bLastDTPFlag_Low)) अणु
		RT_TRACE(COMP_TXAGC, "SetTxPowerLevel8190()  channel = %d\n",
			 priv->rtllib->current_network.channel);

		rtl92e_set_tx_घातer(dev, priv->rtllib->current_network.channel);
	पूर्ण
	priv->bLastDTPFlag_High = priv->bDynamicTxHighPower;
	priv->bLastDTPFlag_Low = priv->bDynamicTxLowPower;

पूर्ण

अटल व्योम _rtl92e_dm_check_txrateandretrycount(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	ieee->sofपंचांगac_stats.CurrentShowTxate = rtl92e_पढ़ोb(dev,
						 Current_Tx_Rate_Reg);

	ieee->sofपंचांगac_stats.last_packet_rate = rtl92e_पढ़ोb(dev,
						 Initial_Tx_Rate_Reg);

	ieee->sofपंचांगac_stats.txretrycount = rtl92e_पढ़ोl(dev,
						 Tx_Retry_Count_Reg);
पूर्ण

अटल व्योम _rtl92e_dm_send_rssi_to_fw(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	rtl92e_ग_लिखोb(dev, DRIVER_RSSI, (u8)priv->undecorated_smoothed_pwdb);
पूर्ण
