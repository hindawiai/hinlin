<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../core.h"
#समावेश "../usb.h"
#समावेश "../efuse.h"
#समावेश "../base.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "mac.h"
#समावेश "dm.h"
#समावेश "rf.h"
#समावेश "trx.h"
#समावेश "led.h"
#समावेश "hw.h"
#समावेश "../rtl8192c/fw_common.h"
#समावेश <linux/module.h>

MODULE_AUTHOR("Georgia		<georgia@realtek.com>");
MODULE_AUTHOR("Ziv Huang	<ziv_huang@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.Finger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek 8192C/8188C 802.11n USB wireless");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_A.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_B.bin");
MODULE_FIRMWARE("rtlwifi/rtl8192cufw_TMSC.bin");

अटल पूर्णांक rtl92cu_init_sw_vars(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक err;
	अक्षर *fw_name;

	rtlpriv->dm.dm_initialgain_enable = true;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = false;
	rtlpriv->dm.thermalvalue = 0;

	/* क्रम firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(0x4000);
	अगर (!rtlpriv->rtlhal.pfirmware) अणु
		pr_err("Can't alloc buffer for fw\n");
		वापस 1;
	पूर्ण
	अगर (IS_VENDOR_UMC_A_CUT(rtlpriv->rtlhal.version) &&
	    !IS_92C_SERIAL(rtlpriv->rtlhal.version)) अणु
		fw_name = "rtlwifi/rtl8192cufw_A.bin";
	पूर्ण अन्यथा अगर (IS_81XXC_VENDOR_UMC_B_CUT(rtlpriv->rtlhal.version)) अणु
		fw_name = "rtlwifi/rtl8192cufw_B.bin";
	पूर्ण अन्यथा अणु
		fw_name = "rtlwifi/rtl8192cufw_TMSC.bin";
	पूर्ण
	/* provide name of alternative file */
	rtlpriv->cfg->alt_fw_name = "rtlwifi/rtl8192cufw.bin";
	pr_info("Loading firmware %s\n", fw_name);
	rtlpriv->max_fw_size = 0x4000;
	err = request_firmware_noरुको(THIS_MODULE, 1,
				      fw_name, rtlpriv->io.dev,
				      GFP_KERNEL, hw, rtl_fw_cb);
	अगर (err) अणु
		vमुक्त(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम rtl92cu_deinit_sw_vars(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->rtlhal.pfirmware) अणु
		vमुक्त(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = शून्य;
	पूर्ण
पूर्ण

/* get bt coexist status */
अटल bool rtl92cu_get_btc_status(व्योम)
अणु
	वापस false;
पूर्ण

अटल काष्ठा rtl_hal_ops rtl8192cu_hal_ops = अणु
	.init_sw_vars = rtl92cu_init_sw_vars,
	.deinit_sw_vars = rtl92cu_deinit_sw_vars,
	.पढ़ो_chip_version = rtl92c_पढ़ो_chip_version,
	.पढ़ो_eeprom_info = rtl92cu_पढ़ो_eeprom_info,
	.enable_पूर्णांकerrupt = rtl92c_enable_पूर्णांकerrupt,
	.disable_पूर्णांकerrupt = rtl92c_disable_पूर्णांकerrupt,
	.hw_init = rtl92cu_hw_init,
	.hw_disable = rtl92cu_card_disable,
	.set_network_type = rtl92cu_set_network_type,
	.set_chk_bssid = rtl92cu_set_check_bssid,
	.set_qos = rtl92c_set_qos,
	.set_bcn_reg = rtl92cu_set_beacon_related_रेजिस्टरs,
	.set_bcn_पूर्णांकv = rtl92cu_set_beacon_पूर्णांकerval,
	.update_पूर्णांकerrupt_mask = rtl92cu_update_पूर्णांकerrupt_mask,
	.get_hw_reg = rtl92cu_get_hw_reg,
	.set_hw_reg = rtl92cu_set_hw_reg,
	.update_rate_tbl = rtl92cu_update_hal_rate_tbl,
	.fill_tx_desc = rtl92cu_tx_fill_desc,
	.fill_fake_txdesc = rtl92cu_fill_fake_txdesc,
	.fill_tx_cmddesc = rtl92cu_tx_fill_cmddesc,
	.query_rx_desc = rtl92cu_rx_query_desc,
	.set_channel_access = rtl92cu_update_channel_access_setting,
	.radio_onoff_checking = rtl92cu_gpio_radio_on_off_checking,
	.set_bw_mode = rtl92c_phy_set_bw_mode,
	.चयन_channel = rtl92c_phy_sw_chnl,
	.dm_watchकरोg = rtl92c_dm_watchकरोg,
	.scan_operation_backup = rtl_phy_scan_operation_backup,
	.set_rf_घातer_state = rtl92cu_phy_set_rf_घातer_state,
	.led_control = rtl92cu_led_control,
	.enable_hw_sec = rtl92cu_enable_hw_security_config,
	.set_key = rtl92c_set_key,
	.init_sw_leds = rtl92cu_init_sw_leds,
	.deinit_sw_leds = rtl92cu_deinit_sw_leds,
	.get_bbreg = rtl92c_phy_query_bb_reg,
	.set_bbreg = rtl92c_phy_set_bb_reg,
	.get_rfreg = rtl92cu_phy_query_rf_reg,
	.set_rfreg = rtl92cu_phy_set_rf_reg,
	.phy_rf6052_config = rtl92cu_phy_rf6052_config,
	.phy_rf6052_set_cck_txघातer = rtl92cu_phy_rf6052_set_cck_txघातer,
	.phy_rf6052_set_ofdm_txघातer = rtl92cu_phy_rf6052_set_ofdm_txघातer,
	.config_bb_with_headerfile = _rtl92cu_phy_config_bb_with_headerfile,
	.config_bb_with_pgheaderfile = _rtl92cu_phy_config_bb_with_pgheaderfile,
	.phy_lc_calibrate = _rtl92cu_phy_lc_calibrate,
	.phy_set_bw_mode_callback = rtl92cu_phy_set_bw_mode_callback,
	.dm_dynamic_txघातer = rtl92cu_dm_dynamic_txघातer,
	.fill_h2c_cmd = rtl92c_fill_h2c_cmd,
	.get_btc_status = rtl92cu_get_btc_status,
पूर्ण;

अटल काष्ठा rtl_mod_params rtl92cu_mod_params = अणु
	.sw_crypto = 0,
	.debug_level = 0,
	.debug_mask = 0,
पूर्ण;

module_param_named(swenc, rtl92cu_mod_params.sw_crypto, bool, 0444);
module_param_named(debug_level, rtl92cu_mod_params.debug_level, पूर्णांक, 0644);
module_param_named(debug_mask, rtl92cu_mod_params.debug_mask, ulदीर्घ, 0644);
MODULE_PARM_DESC(swenc, "Set to 1 for software crypto (default 0)\n");
MODULE_PARM_DESC(debug_level, "Set debug level (0-5) (default 0)");
MODULE_PARM_DESC(debug_mask, "Set debug mask (default 0)");

अटल काष्ठा rtl_hal_usbपूर्णांक_cfg rtl92cu_पूर्णांकerface_cfg = अणु
	/* rx */
	.in_ep_num = RTL92C_USB_BULK_IN_NUM,
	.rx_urb_num = RTL92C_NUM_RX_URBS,
	.rx_max_size = RTL92C_SIZE_MAX_RX_BUFFER,
	.usb_rx_hdl = rtl8192cu_rx_hdl,
	.usb_rx_segregate_hdl = शून्य,
	/* tx */
	.usb_tx_cleanup = rtl8192c_tx_cleanup,
	.usb_tx_post_hdl = rtl8192c_tx_post_hdl,
	.usb_tx_aggregate_hdl = rtl8192c_tx_aggregate_hdl,
	/* endpoपूर्णांक mapping */
	.usb_endpoपूर्णांक_mapping = rtl8192cu_endpoपूर्णांक_mapping,
	.usb_mq_to_hwq = rtl8192cu_mq_to_hwq,
पूर्ण;

अटल काष्ठा rtl_hal_cfg rtl92cu_hal_cfg = अणु
	.name = "rtl92c_usb",
	.ops = &rtl8192cu_hal_ops,
	.mod_params = &rtl92cu_mod_params,
	.usb_पूर्णांकerface_cfg = &rtl92cu_पूर्णांकerface_cfg,

	.maps[SYS_ISO_CTRL] = REG_SYS_ISO_CTRL,
	.maps[SYS_FUNC_EN] = REG_SYS_FUNC_EN,
	.maps[SYS_CLK] = REG_SYS_CLKR,
	.maps[MAC_RCR_AM] = AM,
	.maps[MAC_RCR_AB] = AB,
	.maps[MAC_RCR_ACRC32] = ACRC32,
	.maps[MAC_RCR_ACF] = ACF,
	.maps[MAC_RCR_AAP] = AAP,

	.maps[EFUSE_TEST] = REG_EFUSE_TEST,
	.maps[EFUSE_CTRL] = REG_EFUSE_CTRL,
	.maps[EFUSE_CLK] = 0,
	.maps[EFUSE_CLK_CTRL] = REG_EFUSE_CTRL,
	.maps[EFUSE_PWC_EV12V] = PWC_EV12V,
	.maps[EFUSE_FEN_ELDR] = FEN_ELDR,
	.maps[EFUSE_LOADER_CLK_EN] = LOADER_CLK_EN,
	.maps[EFUSE_ANA8M] = EFUSE_ANA8M,
	.maps[EFUSE_HWSET_MAX_SIZE] = HWSET_MAX_SIZE,
	.maps[EFUSE_MAX_SECTION_MAP] = EFUSE_MAX_SECTION,
	.maps[EFUSE_REAL_CONTENT_SIZE] = EFUSE_REAL_CONTENT_LEN,

	.maps[RWCAM] = REG_CAMCMD,
	.maps[WCAMI] = REG_CAMWRITE,
	.maps[RCAMO] = REG_CAMREAD,
	.maps[CAMDBG] = REG_CAMDBG,
	.maps[SECR] = REG_SECCFG,
	.maps[SEC_CAM_NONE] = CAM_NONE,
	.maps[SEC_CAM_WEP40] = CAM_WEP40,
	.maps[SEC_CAM_TKIP] = CAM_TKIP,
	.maps[SEC_CAM_AES] = CAM_AES,
	.maps[SEC_CAM_WEP104] = CAM_WEP104,

	.maps[RTL_IMR_BCNDMAINT6] = IMR_BCNDMAINT6,
	.maps[RTL_IMR_BCNDMAINT5] = IMR_BCNDMAINT5,
	.maps[RTL_IMR_BCNDMAINT4] = IMR_BCNDMAINT4,
	.maps[RTL_IMR_BCNDMAINT3] = IMR_BCNDMAINT3,
	.maps[RTL_IMR_BCNDMAINT2] = IMR_BCNDMAINT2,
	.maps[RTL_IMR_BCNDMAINT1] = IMR_BCNDMAINT1,
	.maps[RTL_IMR_BCNDOK8] = IMR_BCNDOK8,
	.maps[RTL_IMR_BCNDOK7] = IMR_BCNDOK7,
	.maps[RTL_IMR_BCNDOK6] = IMR_BCNDOK6,
	.maps[RTL_IMR_BCNDOK5] = IMR_BCNDOK5,
	.maps[RTL_IMR_BCNDOK4] = IMR_BCNDOK4,
	.maps[RTL_IMR_BCNDOK3] = IMR_BCNDOK3,
	.maps[RTL_IMR_BCNDOK2] = IMR_BCNDOK2,
	.maps[RTL_IMR_BCNDOK1] = IMR_BCNDOK1,
	.maps[RTL_IMR_TIMEOUT2] = IMR_TIMEOUT2,
	.maps[RTL_IMR_TIMEOUT1] = IMR_TIMEOUT1,

	.maps[RTL_IMR_TXFOVW] = IMR_TXFOVW,
	.maps[RTL_IMR_PSTIMEOUT] = IMR_PSTIMEOUT,
	.maps[RTL_IMR_BCNINT] = IMR_BCNINT,
	.maps[RTL_IMR_RXFOVW] = IMR_RXFOVW,
	.maps[RTL_IMR_RDU] = IMR_RDU,
	.maps[RTL_IMR_ATIMEND] = IMR_ATIMEND,
	.maps[RTL_IMR_BDOK] = IMR_BDOK,
	.maps[RTL_IMR_MGNTDOK] = IMR_MGNTDOK,
	.maps[RTL_IMR_TBDER] = IMR_TBDER,
	.maps[RTL_IMR_HIGHDOK] = IMR_HIGHDOK,
	.maps[RTL_IMR_TBDOK] = IMR_TBDOK,
	.maps[RTL_IMR_BKDOK] = IMR_BKDOK,
	.maps[RTL_IMR_BEDOK] = IMR_BEDOK,
	.maps[RTL_IMR_VIDOK] = IMR_VIDOK,
	.maps[RTL_IMR_VODOK] = IMR_VODOK,
	.maps[RTL_IMR_ROK] = IMR_ROK,
	.maps[RTL_IBSS_INT_MASKS] = (IMR_BCNINT | IMR_TBDOK | IMR_TBDER),

	.maps[RTL_RC_CCK_RATE1M] = DESC_RATE1M,
	.maps[RTL_RC_CCK_RATE2M] = DESC_RATE2M,
	.maps[RTL_RC_CCK_RATE5_5M] = DESC_RATE5_5M,
	.maps[RTL_RC_CCK_RATE11M] = DESC_RATE11M,
	.maps[RTL_RC_OFDM_RATE6M] = DESC_RATE6M,
	.maps[RTL_RC_OFDM_RATE9M] = DESC_RATE9M,
	.maps[RTL_RC_OFDM_RATE12M] = DESC_RATE12M,
	.maps[RTL_RC_OFDM_RATE18M] = DESC_RATE18M,
	.maps[RTL_RC_OFDM_RATE24M] = DESC_RATE24M,
	.maps[RTL_RC_OFDM_RATE36M] = DESC_RATE36M,
	.maps[RTL_RC_OFDM_RATE48M] = DESC_RATE48M,
	.maps[RTL_RC_OFDM_RATE54M] = DESC_RATE54M,
	.maps[RTL_RC_HT_RATEMCS7] = DESC_RATEMCS7,
	.maps[RTL_RC_HT_RATEMCS15] = DESC_RATEMCS15,
पूर्ण;

#घोषणा USB_VENDOR_ID_REALTEK		0x0bda

/* 2010-10-19 DID_USB_V3.4 */
अटल स्थिर काष्ठा usb_device_id rtl8192c_usb_ids[] = अणु

	/*=== Realtek demoboard ===*/
	/* Default ID */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8191, rtl92cu_hal_cfg)पूर्ण,

	/****** 8188CU ********/
	/* RTL8188CTV */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x018a, rtl92cu_hal_cfg)पूर्ण,
	/* 8188CE-VAU USB minCard */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8170, rtl92cu_hal_cfg)पूर्ण,
	/* 8188cu 1*1 करोngle */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8176, rtl92cu_hal_cfg)पूर्ण,
	/* 8188cu 1*1 करोngle, (b/g mode only) */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8177, rtl92cu_hal_cfg)पूर्ण,
	/* 8188cu Slim Solo */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817a, rtl92cu_hal_cfg)पूर्ण,
	/* 8188cu Slim Combo */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817b, rtl92cu_hal_cfg)पूर्ण,
	/* 8188RU High-घातer USB Dongle */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817d, rtl92cu_hal_cfg)पूर्ण,
	/* 8188CE-VAU USB minCard (b/g mode only) */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817e, rtl92cu_hal_cfg)पूर्ण,
	/* 8188RU in Alfa AWUS036NHR */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817f, rtl92cu_hal_cfg)पूर्ण,
	/* RTL8188CUS-VL */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x818a, rtl92cu_hal_cfg)पूर्ण,
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x819a, rtl92cu_hal_cfg)पूर्ण,
	/* 8188 Combo क्रम BC4 */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8754, rtl92cu_hal_cfg)पूर्ण,

	/****** 8192CU ********/
	/* 8192cu 2*2 */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x8178, rtl92cu_hal_cfg)पूर्ण,
	/* 8192CE-VAU USB minCard */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x817c, rtl92cu_hal_cfg)पूर्ण,

	/*=== Customer ID ===*/
	/****** 8188CU ********/
	अणुRTL_USB_DEVICE(0x050d, 0x1102, rtl92cu_hal_cfg)पूर्ण, /*Belkin - Edimax*/
	अणुRTL_USB_DEVICE(0x050d, 0x11f2, rtl92cu_hal_cfg)पूर्ण, /*Belkin - ISY*/
	अणुRTL_USB_DEVICE(0x06f8, 0xe033, rtl92cu_hal_cfg)पूर्ण, /*Hercules - Edimax*/
	अणुRTL_USB_DEVICE(0x07b8, 0x8188, rtl92cu_hal_cfg)पूर्ण, /*Abocom - Abocom*/
	अणुRTL_USB_DEVICE(0x07b8, 0x8189, rtl92cu_hal_cfg)पूर्ण, /*Funai - Abocom*/
	अणुRTL_USB_DEVICE(0x0846, 0x9041, rtl92cu_hal_cfg)पूर्ण, /*NetGear WNA1000M*/
	अणुRTL_USB_DEVICE(0x0846, 0x9043, rtl92cu_hal_cfg)पूर्ण, /*NG WNA1000Mv2*/
	अणुRTL_USB_DEVICE(0x0b05, 0x17ba, rtl92cu_hal_cfg)पूर्ण, /*ASUS-Edimax*/
	अणुRTL_USB_DEVICE(0x0bda, 0x5088, rtl92cu_hal_cfg)पूर्ण, /*Thinkware-CC&C*/
	अणुRTL_USB_DEVICE(0x0df6, 0x0052, rtl92cu_hal_cfg)पूर्ण, /*Sitecom - Edimax*/
	अणुRTL_USB_DEVICE(0x0df6, 0x005c, rtl92cu_hal_cfg)पूर्ण, /*Sitecom - Edimax*/
	अणुRTL_USB_DEVICE(0x0df6, 0x0070, rtl92cu_hal_cfg)पूर्ण, /*Sitecom - 150N */
	अणुRTL_USB_DEVICE(0x0df6, 0x0077, rtl92cu_hal_cfg)पूर्ण, /*Sitecom-WLA2100V2*/
	अणुRTL_USB_DEVICE(0x0eb0, 0x9071, rtl92cu_hal_cfg)पूर्ण, /*NO Bअक्रम - Etop*/
	अणुRTL_USB_DEVICE(0x4856, 0x0091, rtl92cu_hal_cfg)पूर्ण, /*NetweeN - Feixun*/
	/* HP - Lite-On ,8188CUS Slim Combo */
	अणुRTL_USB_DEVICE(0x103c, 0x1629, rtl92cu_hal_cfg)पूर्ण,
	अणुRTL_USB_DEVICE(0x13d3, 0x3357, rtl92cu_hal_cfg)पूर्ण, /* AzureWave */
	अणुRTL_USB_DEVICE(0x2001, 0x3308, rtl92cu_hal_cfg)पूर्ण, /*D-Link - Alpha*/
	अणुRTL_USB_DEVICE(0x2019, 0x4902, rtl92cu_hal_cfg)पूर्ण, /*Planex - Etop*/
	अणुRTL_USB_DEVICE(0x2019, 0xab2a, rtl92cu_hal_cfg)पूर्ण, /*Planex - Abocom*/
	/*SW-WF02-AD15 -Abocom*/
	अणुRTL_USB_DEVICE(0x2019, 0xab2e, rtl92cu_hal_cfg)पूर्ण,
	अणुRTL_USB_DEVICE(0x2019, 0xed17, rtl92cu_hal_cfg)पूर्ण, /*PCI - Edimax*/
	अणुRTL_USB_DEVICE(0x20f4, 0x648b, rtl92cu_hal_cfg)पूर्ण, /*TRENDnet - Cameo*/
	अणुRTL_USB_DEVICE(0x7392, 0x7811, rtl92cu_hal_cfg)पूर्ण, /*Edimax - Edimax*/
	अणुRTL_USB_DEVICE(0x13d3, 0x3358, rtl92cu_hal_cfg)पूर्ण, /*Azwave 8188CE-VAU*/
	/* Russian customer -Azwave (8188CE-VAU  b/g mode only) */
	अणुRTL_USB_DEVICE(0x13d3, 0x3359, rtl92cu_hal_cfg)पूर्ण,
	अणुRTL_USB_DEVICE(0x4855, 0x0090, rtl92cu_hal_cfg)पूर्ण, /* Feixun */
	अणुRTL_USB_DEVICE(0x4855, 0x0091, rtl92cu_hal_cfg)पूर्ण, /* NetweeN-Feixun */
	अणुRTL_USB_DEVICE(0x9846, 0x9041, rtl92cu_hal_cfg)पूर्ण, /* Netgear Cameo */

	/****** 8188 RU ********/
	/* Netcore */
	अणुRTL_USB_DEVICE(USB_VENDOR_ID_REALTEK, 0x317f, rtl92cu_hal_cfg)पूर्ण,

	/****** 8188CUS Slim Solo********/
	अणुRTL_USB_DEVICE(0x04f2, 0xaff7, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/
	अणुRTL_USB_DEVICE(0x04f2, 0xaff9, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/
	अणुRTL_USB_DEVICE(0x04f2, 0xaffa, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/

	/****** 8188CUS Slim Combo ********/
	अणुRTL_USB_DEVICE(0x04f2, 0xaff8, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/
	अणुRTL_USB_DEVICE(0x04f2, 0xaffb, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/
	अणुRTL_USB_DEVICE(0x04f2, 0xaffc, rtl92cu_hal_cfg)पूर्ण, /*Xavi*/
	अणुRTL_USB_DEVICE(0x2019, 0x1201, rtl92cu_hal_cfg)पूर्ण, /*Planex-Vencer*/

	/****** 8192CU ********/
	अणुRTL_USB_DEVICE(0x050d, 0x1004, rtl92cu_hal_cfg)पूर्ण, /*Belcom-SurfN300*/
	अणुRTL_USB_DEVICE(0x050d, 0x2102, rtl92cu_hal_cfg)पूर्ण, /*Belcom-Sercomm*/
	अणुRTL_USB_DEVICE(0x050d, 0x2103, rtl92cu_hal_cfg)पूर्ण, /*Belcom-Edimax*/
	अणुRTL_USB_DEVICE(0x0586, 0x341f, rtl92cu_hal_cfg)पूर्ण, /*Zyxel -Abocom*/
	अणुRTL_USB_DEVICE(0x07aa, 0x0056, rtl92cu_hal_cfg)पूर्ण, /*ATKK-Gemtek*/
	अणुRTL_USB_DEVICE(0x07b8, 0x8178, rtl92cu_hal_cfg)पूर्ण, /*Funai -Abocom*/
	अणुRTL_USB_DEVICE(0x0846, 0x9021, rtl92cu_hal_cfg)पूर्ण, /*Netgear-Sercomm*/
	अणुRTL_USB_DEVICE(0x0846, 0xf001, rtl92cu_hal_cfg)पूर्ण, /*On Netwrks N300MA*/
	अणुRTL_USB_DEVICE(0x0b05, 0x17ab, rtl92cu_hal_cfg)पूर्ण, /*ASUS-Edimax*/
	अणुRTL_USB_DEVICE(0x0bda, 0x8186, rtl92cu_hal_cfg)पूर्ण, /*Realtek 92CE-VAU*/
	अणुRTL_USB_DEVICE(0x0df6, 0x0061, rtl92cu_hal_cfg)पूर्ण, /*Sitecom-Edimax*/
	अणुRTL_USB_DEVICE(0x0e66, 0x0019, rtl92cu_hal_cfg)पूर्ण, /*Hawking-Edimax*/
	अणुRTL_USB_DEVICE(0x2001, 0x3307, rtl92cu_hal_cfg)पूर्ण, /*D-Link-Cameo*/
	अणुRTL_USB_DEVICE(0x2001, 0x3309, rtl92cu_hal_cfg)पूर्ण, /*D-Link-Alpha*/
	अणुRTL_USB_DEVICE(0x2001, 0x330a, rtl92cu_hal_cfg)पूर्ण, /*D-Link-Alpha*/
	अणुRTL_USB_DEVICE(0x2001, 0x330d, rtl92cu_hal_cfg)पूर्ण, /*D-Link DWA-131 */
	अणुRTL_USB_DEVICE(0x2019, 0xab2b, rtl92cu_hal_cfg)पूर्ण, /*Planex -Abocom*/
	अणुRTL_USB_DEVICE(0x20f4, 0x624d, rtl92cu_hal_cfg)पूर्ण, /*TRENDNet*/
	अणुRTL_USB_DEVICE(0x2357, 0x0100, rtl92cu_hal_cfg)पूर्ण, /*TP-Link WN8200ND*/
	अणुRTL_USB_DEVICE(0x7392, 0x7822, rtl92cu_hal_cfg)पूर्ण, /*Edimax -Edimax*/
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, rtl8192c_usb_ids);

अटल पूर्णांक rtl8192cu_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	वापस rtl_usb_probe(पूर्णांकf, id, &rtl92cu_hal_cfg);
पूर्ण

अटल काष्ठा usb_driver rtl8192cu_driver = अणु
	.name = "rtl8192cu",
	.probe = rtl8192cu_probe,
	.disconnect = rtl_usb_disconnect,
	.id_table = rtl8192c_usb_ids,

#अगर_घोषित CONFIG_PM
	/* .suspend = rtl_usb_suspend, */
	/* .resume = rtl_usb_resume, */
	/* .reset_resume = rtl8192c_resume, */
#पूर्ण_अगर /* CONFIG_PM */
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rtl8192cu_driver);
