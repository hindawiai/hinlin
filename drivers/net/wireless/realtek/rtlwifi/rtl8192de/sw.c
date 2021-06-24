<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../core.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "hw.h"
#समावेश "sw.h"
#समावेश "trx.h"
#समावेश "led.h"

#समावेश <linux/module.h>

अटल व्योम rtl92d_init_aspm_vars(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	/*बंद ASPM क्रम AMD शेषly */
	rtlpci->स्थिर_amdpci_aspm = 0;

	/*
	 * ASPM PS mode.
	 * 0 - Disable ASPM,
	 * 1 - Enable ASPM without Clock Req,
	 * 2 - Enable ASPM with Clock Req,
	 * 3 - Alwyas Enable ASPM with Clock Req,
	 * 4 - Always Enable ASPM without Clock Req.
	 * set defult to RTL8192CE:3 RTL8192E:2
	 * */
	rtlpci->स्थिर_pci_aspm = 3;

	/*Setting क्रम PCI-E device */
	rtlpci->स्थिर_devicepci_aspm_setting = 0x03;

	/*Setting क्रम PCI-E bridge */
	rtlpci->स्थिर_hostpci_aspm_setting = 0x02;

	/*
	 * In Hw/Sw Radio Off situation.
	 * 0 - Default,
	 * 1 - From ASPM setting without low Mac Pwr,
	 * 2 - From ASPM setting with low Mac Pwr,
	 * 3 - Bus D3
	 * set शेष to RTL8192CE:0 RTL8192SE:2
	 */
	rtlpci->स्थिर_hwsw_rfoff_d3 = 0;

	/*
	 * This setting works क्रम those device with
	 * backकरोor ASPM setting such as EPHY setting.
	 * 0 - Not support ASPM,
	 * 1 - Support ASPM,
	 * 2 - According to chipset.
	 */
	rtlpci->स्थिर_support_pciaspm = rtlpriv->cfg->mod_params->aspm_support;
पूर्ण

अटल पूर्णांक rtl92d_init_sw_vars(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक err;
	u8 tid;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	अक्षर *fw_name = "rtlwifi/rtl8192defw.bin";

	rtlpriv->dm.dm_initialgain_enable = true;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = false;
	rtlpriv->dm.thermalvalue = 0;
	rtlpriv->dm.useramask = true;

	/* dual mac */
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G)
		rtlpriv->phy.current_channel = 36;
	अन्यथा
		rtlpriv->phy.current_channel = 1;

	अगर (rtlpriv->rtlhal.macphymode != SINGLEMAC_SINGLEPHY) अणु
		rtlpriv->rtlhal.disable_amsdu_8k = true;
		/* No दीर्घ RX - reduce fragmentation */
		rtlpci->rxbuffersize = 4096;
	पूर्ण

	rtlpci->transmit_config = CFENDFORM | BIT(12) | BIT(13);

	rtlpci->receive_config = (
			RCR_APPFCS
			| RCR_AMF
			| RCR_ADF
			| RCR_APP_MIC
			| RCR_APP_ICV
			| RCR_AICV
			| RCR_ACRC32
			| RCR_AB
			| RCR_AM
			| RCR_APM
			| RCR_APP_PHYST_RXFF
			| RCR_HTC_LOC_CTRL
	);

	rtlpci->irq_mask[0] = (u32) (
			IMR_ROK
			| IMR_VODOK
			| IMR_VIDOK
			| IMR_BEDOK
			| IMR_BKDOK
			| IMR_MGNTDOK
			| IMR_HIGHDOK
			| IMR_BDOK
			| IMR_RDU
			| IMR_RXFOVW
	);

	rtlpci->irq_mask[1] = (u32) (IMR_CPWM | IMR_C2HCMD);

	/* क्रम LPS & IPS */
	rtlpriv->psc.inactiveps = rtlpriv->cfg->mod_params->inactiveps;
	rtlpriv->psc.swctrl_lps = rtlpriv->cfg->mod_params->swctrl_lps;
	rtlpriv->psc.fwctrl_lps = rtlpriv->cfg->mod_params->fwctrl_lps;
	अगर (!rtlpriv->psc.inactiveps)
		pr_info("Power Save off (module option)\n");
	अगर (!rtlpriv->psc.fwctrl_lps)
		pr_info("FW Power Save off (module option)\n");
	rtlpriv->psc.reg_fwctrl_lps = 3;
	rtlpriv->psc.reg_max_lps_awakeपूर्णांकvl = 5;
	/* क्रम ASPM, you can बंद aspm through
	 * set स्थिर_support_pciaspm = 0 */
	rtl92d_init_aspm_vars(hw);

	अगर (rtlpriv->psc.reg_fwctrl_lps == 1)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MIN_MODE;
	अन्यथा अगर (rtlpriv->psc.reg_fwctrl_lps == 2)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MAX_MODE;
	अन्यथा अगर (rtlpriv->psc.reg_fwctrl_lps == 3)
		rtlpriv->psc.fwctrl_psmode = FW_PS_DTIM_MODE;

	/* क्रम early mode */
	rtlpriv->rtlhal.earlymode_enable = false;
	क्रम (tid = 0; tid < 8; tid++)
		skb_queue_head_init(&rtlpriv->mac80211.skb_रुकोq[tid]);

	/* क्रम firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(0x8000);
	अगर (!rtlpriv->rtlhal.pfirmware) अणु
		pr_err("Can't alloc buffer for fw\n");
		वापस 1;
	पूर्ण

	rtlpriv->max_fw_size = 0x8000;
	pr_info("Driver for Realtek RTL8192DE WLAN interface\n");
	pr_info("Loading firmware file %s\n", fw_name);

	/* request fw */
	err = request_firmware_noरुको(THIS_MODULE, 1, fw_name,
				      rtlpriv->io.dev, GFP_KERNEL, hw,
				      rtl_fw_cb);
	अगर (err) अणु
		pr_err("Failed to request firmware!\n");
		vमुक्त(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = शून्य;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtl92d_deinit_sw_vars(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tid;

	अगर (rtlpriv->rtlhal.pfirmware) अणु
		vमुक्त(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = शून्य;
	पूर्ण
	क्रम (tid = 0; tid < 8; tid++)
		skb_queue_purge(&rtlpriv->mac80211.skb_रुकोq[tid]);
पूर्ण

अटल काष्ठा rtl_hal_ops rtl8192de_hal_ops = अणु
	.init_sw_vars = rtl92d_init_sw_vars,
	.deinit_sw_vars = rtl92d_deinit_sw_vars,
	.पढ़ो_eeprom_info = rtl92de_पढ़ो_eeprom_info,
	.पूर्णांकerrupt_recognized = rtl92de_पूर्णांकerrupt_recognized,
	.hw_init = rtl92de_hw_init,
	.hw_disable = rtl92de_card_disable,
	.hw_suspend = rtl92de_suspend,
	.hw_resume = rtl92de_resume,
	.enable_पूर्णांकerrupt = rtl92de_enable_पूर्णांकerrupt,
	.disable_पूर्णांकerrupt = rtl92de_disable_पूर्णांकerrupt,
	.set_network_type = rtl92de_set_network_type,
	.set_chk_bssid = rtl92de_set_check_bssid,
	.set_qos = rtl92de_set_qos,
	.set_bcn_reg = rtl92de_set_beacon_related_रेजिस्टरs,
	.set_bcn_पूर्णांकv = rtl92de_set_beacon_पूर्णांकerval,
	.update_पूर्णांकerrupt_mask = rtl92de_update_पूर्णांकerrupt_mask,
	.get_hw_reg = rtl92de_get_hw_reg,
	.set_hw_reg = rtl92de_set_hw_reg,
	.update_rate_tbl = rtl92de_update_hal_rate_tbl,
	.fill_tx_desc = rtl92de_tx_fill_desc,
	.fill_tx_cmddesc = rtl92de_tx_fill_cmddesc,
	.query_rx_desc = rtl92de_rx_query_desc,
	.set_channel_access = rtl92de_update_channel_access_setting,
	.radio_onoff_checking = rtl92de_gpio_radio_on_off_checking,
	.set_bw_mode = rtl92d_phy_set_bw_mode,
	.चयन_channel = rtl92d_phy_sw_chnl,
	.dm_watchकरोg = rtl92d_dm_watchकरोg,
	.scan_operation_backup = rtl_phy_scan_operation_backup,
	.set_rf_घातer_state = rtl92d_phy_set_rf_घातer_state,
	.led_control = rtl92de_led_control,
	.set_desc = rtl92de_set_desc,
	.get_desc = rtl92de_get_desc,
	.is_tx_desc_बंदd = rtl92de_is_tx_desc_बंदd,
	.tx_polling = rtl92de_tx_polling,
	.enable_hw_sec = rtl92de_enable_hw_security_config,
	.set_key = rtl92de_set_key,
	.init_sw_leds = rtl92de_init_sw_leds,
	.get_bbreg = rtl92d_phy_query_bb_reg,
	.set_bbreg = rtl92d_phy_set_bb_reg,
	.get_rfreg = rtl92d_phy_query_rf_reg,
	.set_rfreg = rtl92d_phy_set_rf_reg,
	.linked_set_reg = rtl92d_linked_set_reg,
	.get_btc_status = rtl_btc_status_false,
पूर्ण;

अटल काष्ठा rtl_mod_params rtl92de_mod_params = अणु
	.sw_crypto = false,
	.inactiveps = true,
	.swctrl_lps = true,
	.fwctrl_lps = false,
	.aspm_support = 1,
	.debug_level = 0,
	.debug_mask = 0,
पूर्ण;

अटल स्थिर काष्ठा rtl_hal_cfg rtl92de_hal_cfg = अणु
	.bar_id = 2,
	.ग_लिखो_पढ़ोback = true,
	.name = "rtl8192de",
	.ops = &rtl8192de_hal_ops,
	.mod_params = &rtl92de_mod_params,

	.maps[SYS_ISO_CTRL] = REG_SYS_ISO_CTRL,
	.maps[SYS_FUNC_EN] = REG_SYS_FUNC_EN,
	.maps[SYS_CLK] = REG_SYS_CLKR,
	.maps[MAC_RCR_AM] = RCR_AM,
	.maps[MAC_RCR_AB] = RCR_AB,
	.maps[MAC_RCR_ACRC32] = RCR_ACRC32,
	.maps[MAC_RCR_ACF] = RCR_ACF,
	.maps[MAC_RCR_AAP] = RCR_AAP,

	.maps[EFUSE_TEST] = REG_EFUSE_TEST,
	.maps[EFUSE_CTRL] = REG_EFUSE_CTRL,
	.maps[EFUSE_CLK] = 0,	/* just क्रम 92se */
	.maps[EFUSE_CLK_CTRL] = REG_EFUSE_CTRL,
	.maps[EFUSE_PWC_EV12V] = PWC_EV12V,
	.maps[EFUSE_FEN_ELDR] = FEN_ELDR,
	.maps[EFUSE_LOADER_CLK_EN] = LOADER_CLK_EN,
	.maps[EFUSE_ANA8M] = 0,	/* just क्रम 92se */
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

अटल स्थिर काष्ठा pci_device_id rtl92de_pci_ids[] = अणु
	अणुRTL_PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x8193, rtl92de_hal_cfg)पूर्ण,
	अणुRTL_PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x002B, rtl92de_hal_cfg)पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtl92de_pci_ids);

MODULE_AUTHOR("lizhaoming	<chaoming_li@realsil.com.cn>");
MODULE_AUTHOR("Realtek WlanFAE	<wlanfae@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.Finger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek 8192DE 802.11n Dual Mac PCI wireless");
MODULE_FIRMWARE("rtlwifi/rtl8192defw.bin");

module_param_named(swenc, rtl92de_mod_params.sw_crypto, bool, 0444);
module_param_named(debug_level, rtl92de_mod_params.debug_level, पूर्णांक, 0644);
module_param_named(ips, rtl92de_mod_params.inactiveps, bool, 0444);
module_param_named(swlps, rtl92de_mod_params.swctrl_lps, bool, 0444);
module_param_named(fwlps, rtl92de_mod_params.fwctrl_lps, bool, 0444);
module_param_named(aspm, rtl92de_mod_params.aspm_support, पूर्णांक, 0444);
module_param_named(debug_mask, rtl92de_mod_params.debug_mask, ulदीर्घ, 0644);
MODULE_PARM_DESC(swenc, "Set to 1 for software crypto (default 0)\n");
MODULE_PARM_DESC(ips, "Set to 0 to not use link power save (default 1)\n");
MODULE_PARM_DESC(swlps, "Set to 1 to use SW control power save (default 1)\n");
MODULE_PARM_DESC(fwlps, "Set to 1 to use FW control power save (default 0)\n");
MODULE_PARM_DESC(aspm, "Set to 1 to enable ASPM (default 1)\n");
MODULE_PARM_DESC(debug_level, "Set debug level (0-5) (default 0)");
MODULE_PARM_DESC(debug_mask, "Set debug mask (default 0)");

अटल SIMPLE_DEV_PM_OPS(rtlwअगरi_pm_ops, rtl_pci_suspend, rtl_pci_resume);

अटल काष्ठा pci_driver rtl92de_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = rtl92de_pci_ids,
	.probe = rtl_pci_probe,
	.हटाओ = rtl_pci_disconnect,
	.driver.pm = &rtlwअगरi_pm_ops,
पूर्ण;

/* add global spin lock to solve the problem that
 * Dul mac रेजिस्टर operation on the same समय */
DEFINE_SPINLOCK(globalmutex_घातer);
DEFINE_SPINLOCK(globalmutex_क्रम_fwकरोwnload);
DEFINE_SPINLOCK(globalmutex_क्रम_घातer_and_efuse);

अटल पूर्णांक __init rtl92de_module_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = pci_रेजिस्टर_driver(&rtl92de_driver);
	अगर (ret)
		WARN_ONCE(true, "rtl8192de: No device found\n");
	वापस ret;
पूर्ण

अटल व्योम __निकास rtl92de_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rtl92de_driver);
पूर्ण

module_init(rtl92de_module_init);
module_निकास(rtl92de_module_निकास);
