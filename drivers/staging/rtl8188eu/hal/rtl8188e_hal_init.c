<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HAL_INIT_C_

#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <drv_types.h>
#समावेश <rtw_efuse.h>
#समावेश <phy.h>
#समावेश <rtl8188e_hal.h>

#समावेश <rtw_iol.h>

व्योम iol_mode_enable(काष्ठा adapter *padapter, u8 enable)
अणु
	u8 reg_0xf0 = 0;

	अगर (enable) अणु
		/* Enable initial offload */
		reg_0xf0 = usb_पढ़ो8(padapter, REG_SYS_CFG);
		usb_ग_लिखो8(padapter, REG_SYS_CFG, reg_0xf0 | SW_OFFLOAD_EN);

		अगर (!padapter->bFWReady) अणु
			DBG_88E("bFWReady == false call reset 8051...\n");
			_8051Reset88E(padapter);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* disable initial offload */
		reg_0xf0 = usb_पढ़ो8(padapter, REG_SYS_CFG);
		usb_ग_लिखो8(padapter, REG_SYS_CFG, reg_0xf0 & ~SW_OFFLOAD_EN);
	पूर्ण
पूर्ण

s32 iol_execute(काष्ठा adapter *padapter, u8 control)
अणु
	s32 status = _FAIL;
	u8 reg_0x88 = 0;
	अचिन्हित दीर्घ start = 0;

	control = control & 0x0f;
	reg_0x88 = usb_पढ़ो8(padapter, REG_HMEBOX_E0);
	usb_ग_लिखो8(padapter, REG_HMEBOX_E0,  reg_0x88 | control);

	start = jअगरfies;
	जबतक ((reg_0x88 = usb_पढ़ो8(padapter, REG_HMEBOX_E0)) & control &&
	       jअगरfies_to_msecs(jअगरfies - start) < 1000) अणु
		udelay(5);
	पूर्ण

	reg_0x88 = usb_पढ़ो8(padapter, REG_HMEBOX_E0);
	status = (reg_0x88 & control) ? _FAIL : _SUCCESS;
	अगर (reg_0x88 & control << 4)
		status = _FAIL;
	वापस status;
पूर्ण

अटल s32 iol_InitLLTTable(काष्ठा adapter *padapter, u8 txpktbuf_bndy)
अणु
	s32 rst = _SUCCESS;

	iol_mode_enable(padapter, 1);
	usb_ग_लिखो8(padapter, REG_TDECTRL + 1, txpktbuf_bndy);
	rst = iol_execute(padapter, CMD_INIT_LLT);
	iol_mode_enable(padapter, 0);
	वापस rst;
पूर्ण

s32 rtl8188e_iol_efuse_patch(काष्ठा adapter *padapter)
अणु
	s32	result = _SUCCESS;

	DBG_88E("==> %s\n", __func__);
	अगर (rtw_iol_applied(padapter)) अणु
		iol_mode_enable(padapter, 1);
		result = iol_execute(padapter, CMD_READ_EFUSE_MAP);
		अगर (result == _SUCCESS)
			result = iol_execute(padapter, CMD_EFUSE_PATCH);

		iol_mode_enable(padapter, 0);
	पूर्ण
	वापस result;
पूर्ण

#घोषणा MAX_REG_BOLCK_SIZE	196

व्योम _8051Reset88E(काष्ठा adapter *padapter)
अणु
	u8 u1bTmp;

	u1bTmp = usb_पढ़ो8(padapter, REG_SYS_FUNC_EN + 1);
	usb_ग_लिखो8(padapter, REG_SYS_FUNC_EN + 1, u1bTmp & (~BIT(2)));
	usb_ग_लिखो8(padapter, REG_SYS_FUNC_EN + 1, u1bTmp | (BIT(2)));
	DBG_88E("=====> %s(): 8051 reset success .\n", __func__);
पूर्ण

व्योम rtl8188e_InitializeFirmwareVars(काष्ठा adapter *padapter)
अणु
	/*  Init Fw LPS related. */
	padapter->pwrctrlpriv.bFwCurrentInPSMode = false;

	/*  Init H2C counter. by tynli. 2009.12.09. */
	padapter->HalData->LastHMEBoxNum = 0;
पूर्ण

व्योम rtw_hal_मुक्त_data(काष्ठा adapter *padapter)
अणु
	kमुक्त(padapter->HalData);
	padapter->HalData = शून्य;
पूर्ण

व्योम rtw_hal_पढ़ो_chip_version(काष्ठा adapter *padapter)
अणु
	u32				value32;
	काष्ठा HAL_VERSION		ChipVersion;
	काष्ठा hal_data_8188e *pHalData = padapter->HalData;

	value32 = usb_पढ़ो32(padapter, REG_SYS_CFG);
	ChipVersion.ChipType = ((value32 & RTL_ID) ? TEST_CHIP : NORMAL_CHIP);
	ChipVersion.VenकरोrType = ((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : CHIP_VENDOR_TSMC);
	ChipVersion.CUTVersion = (value32 & CHIP_VER_RTL_MASK) >> CHIP_VER_RTL_SHIFT; /*  IC version (CUT) */

	dump_chip_info(ChipVersion);

	pHalData->VersionID = ChipVersion;
पूर्ण

व्योम rtw_hal_set_odm_var(काष्ठा adapter *Adapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, bool bSet)
अणु
	काष्ठा odm_dm_काष्ठा *podmpriv = &Adapter->HalData->odmpriv;

	चयन (eVariable) अणु
	हाल HAL_ODM_STA_INFO:
		अणु
			काष्ठा sta_info *psta = pValue1;

			अगर (bSet) अणु
				DBG_88E("### Set STA_(%d) info\n", psta->mac_id);
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, psta);
				ODM_RAInfo_Init(podmpriv, psta->mac_id);
			पूर्ण अन्यथा अणु
				DBG_88E("### Clean STA_(%d) info\n", psta->mac_id);
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, शून्य);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HAL_ODM_P2P_STATE:
		podmpriv->bWIFI_Direct = bSet;
		अवरोध;
	हाल HAL_ODM_WIFI_DISPLAY_STATE:
		podmpriv->bWIFI_Display = bSet;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtw_hal_notch_filter(काष्ठा adapter *adapter, bool enable)
अणु
	अगर (enable) अणु
		DBG_88E("Enable notch filter\n");
		usb_ग_लिखो8(adapter, rOFDM0_RxDSP + 1, usb_पढ़ो8(adapter, rOFDM0_RxDSP + 1) | BIT(1));
	पूर्ण अन्यथा अणु
		DBG_88E("Disable notch filter\n");
		usb_ग_लिखो8(adapter, rOFDM0_RxDSP + 1, usb_पढ़ो8(adapter, rOFDM0_RxDSP + 1) & ~BIT(1));
	पूर्ण
पूर्ण

/*  */
/*  */
/*  LLT R/W/Init function */
/*  */
/*  */
अटल s32 _LLTWrite(काष्ठा adapter *padapter, u32 address, u32 data)
अणु
	s32	status = _SUCCESS;
	s32	count = 0;
	u32	value = _LLT_INIT_ADDR(address) | _LLT_INIT_DATA(data) | _LLT_OP(_LLT_WRITE_ACCESS);
	u16	LLTReg = REG_LLT_INIT;

	usb_ग_लिखो32(padapter, LLTReg, value);

	/* polling */
	करो अणु
		value = usb_पढ़ो32(padapter, LLTReg);
		अगर (_LLT_OP_VALUE(value) == _LLT_NO_ACTIVE)
			अवरोध;

		अगर (count > POLLING_LLT_THRESHOLD) अणु
			RT_TRACE(_module_hal_init_c_, _drv_err_, ("Failed to polling write LLT done at address %d!\n", address));
			status = _FAIL;
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण जबतक (count++);

	वापस status;
पूर्ण

s32 InitLLTTable(काष्ठा adapter *padapter, u8 txpktbuf_bndy)
अणु
	s32	status = _FAIL;
	u32	i;
	u32	Last_Entry_Of_TxPktBuf = LAST_ENTRY_OF_TX_PKT_BUFFER;/*  176, 22k */

	अगर (rtw_iol_applied(padapter)) अणु
		status = iol_InitLLTTable(padapter, txpktbuf_bndy);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (txpktbuf_bndy - 1); i++) अणु
			status = _LLTWrite(padapter, i, i + 1);
			अगर (status != _SUCCESS)
				वापस status;
		पूर्ण

		/*  end of list */
		status = _LLTWrite(padapter, (txpktbuf_bndy - 1), 0xFF);
		अगर (status != _SUCCESS)
			वापस status;

		/*  Make the other pages as ring buffer */
		/*  This ring buffer is used as beacon buffer अगर we config this MAC as two MAC transfer. */
		/*  Otherwise used as local loopback buffer. */
		क्रम (i = txpktbuf_bndy; i < Last_Entry_Of_TxPktBuf; i++) अणु
			status = _LLTWrite(padapter, i, (i + 1));
			अगर (status != _SUCCESS)
				वापस status;
		पूर्ण

		/*  Let last entry poपूर्णांक to the start entry of ring buffer */
		status = _LLTWrite(padapter, Last_Entry_Of_TxPktBuf, txpktbuf_bndy);
		अगर (status != _SUCCESS)
			वापस status;
	पूर्ण

	वापस status;
पूर्ण

व्योम Hal_InitPGData88E(काष्ठा adapter *padapter)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	अगर (!pEEPROM->bस्वतःload_fail_flag) अणु /*  स्वतःload OK. */
		अगर (!is_boot_from_eeprom(padapter)) अणु
			/*  Read EFUSE real map to shaकरोw. */
			EFUSE_ShaकरोwMapUpdate(padapter, EFUSE_WIFI);
		पूर्ण
	पूर्ण अन्यथा अणु/* स्वतःload fail */
		RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("AutoLoad Fail reported from CR9346!!\n"));
		/* update to शेष value 0xFF */
		अगर (!is_boot_from_eeprom(padapter))
			EFUSE_ShaकरोwMapUpdate(padapter, EFUSE_WIFI);
	पूर्ण
पूर्ण

व्योम Hal_EfuseParseIDCode88E(काष्ठा adapter *padapter, u8 *hwinfo)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
	u16			EEPROMId;

	/*  Checl 0x8129 again क्रम making sure स्वतःload status!! */
	EEPROMId = le16_to_cpu(*((__le16 *)hwinfo));
	अगर (EEPROMId != RTL_EEPROM_ID) अणु
		DBG_88E("EEPROM ID(%#x) is invalid!!\n", EEPROMId);
		pEEPROM->bस्वतःload_fail_flag = true;
	पूर्ण अन्यथा अणु
		pEEPROM->bस्वतःload_fail_flag = false;
	पूर्ण

	DBG_88E("EEPROM ID = 0x%04x\n", EEPROMId);
पूर्ण

अटल व्योम Hal_ReadPowerValueFromPROM_8188E(काष्ठा txघातerinfo24g *pwrInfo24G, u8 *PROMContent, bool AutoLoadFail)
अणु
	u32 rfPath, eeAddr = EEPROM_TX_PWR_INX_88E, group, TxCount = 0;

	स_रखो(pwrInfo24G, 0, माप(काष्ठा txघातerinfo24g));

	अगर (AutoLoadFail) अणु
		क्रम (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) अणु
			/* 2.4G शेष value */
			क्रम (group = 0; group < MAX_CHNL_GROUP_24G; group++) अणु
				pwrInfo24G->IndexCCK_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
				pwrInfo24G->IndexBW40_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
			पूर्ण
			क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
				अगर (TxCount == 0) अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][0] = EEPROM_DEFAULT_24G_HT20_DIFF;
					pwrInfo24G->OFDM_Dअगरf[rfPath][0] = EEPROM_DEFAULT_24G_OFDM_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	क्रम (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) अणु
		/* 2.4G शेष value */
		क्रम (group = 0; group < MAX_CHNL_GROUP_24G; group++) अणु
			pwrInfo24G->IndexCCK_Base[rfPath][group] =	PROMContent[eeAddr++];
			अगर (pwrInfo24G->IndexCCK_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexCCK_Base[rfPath][group] = EEPROM_DEFAULT_24G_INDEX;
		पूर्ण
		क्रम (group = 0; group < MAX_CHNL_GROUP_24G - 1; group++) अणु
			pwrInfo24G->IndexBW40_Base[rfPath][group] =	PROMContent[eeAddr++];
			अगर (pwrInfo24G->IndexBW40_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexBW40_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
		पूर्ण
		क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
			अगर (TxCount == 0) अणु
				pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = 0;
				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_24G_HT20_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr] & 0xf0) >> 4;
					अगर (pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_24G_OFDM_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr] & 0x0f);
					अगर (pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] = 0;
				eeAddr++;
			पूर्ण अन्यथा अणु
				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr] & 0xf0) >> 4;
					अगर (pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr] & 0x0f);
					अगर (pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				eeAddr++;

				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr] & 0xf0) >> 4;
					अगर (pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF) अणु
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr] & 0x0f);
					अगर (pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				eeAddr++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम Hal_GetChnlGroup88E(u8 chnl, u8 *group)
अणु
	अगर (chnl < 3)			/*  Channel 1-2 */
		*group = 0;
	अन्यथा अगर (chnl < 6)		/*  Channel 3-5 */
		*group = 1;
	अन्यथा अगर (chnl < 9)		/*  Channel 6-8 */
		*group = 2;
	अन्यथा अगर (chnl < 12)		/*  Channel 9-11 */
		*group = 3;
	अन्यथा अगर (chnl < 14)		/*  Channel 12-13 */
		*group = 4;
	अन्यथा अगर (chnl == 14)		/*  Channel 14 */
		*group = 5;
पूर्ण

व्योम Hal_ReadPowerSavingMode88E(काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	अगर (AutoLoadFail) अणु
		padapter->pwrctrlpriv.bHWPowerकरोwn = false;
		padapter->pwrctrlpriv.bSupportRemoteWakeup = false;
	पूर्ण अन्यथा अणु
		/* hw घातer करोwn mode selection , 0:rf-off / 1:घातer करोwn */

		अगर (padapter->registrypriv.hwpdn_mode == 2)
			padapter->pwrctrlpriv.bHWPowerकरोwn = (hwinfo[EEPROM_RF_FEATURE_OPTION_88E] & BIT(4));
		अन्यथा
			padapter->pwrctrlpriv.bHWPowerकरोwn = padapter->registrypriv.hwpdn_mode;

		/*  decide hw अगर support remote wakeup function */
		/*  अगर hw supported, 8051 (SIE) will generate WeakUP संकेत(D+/D- toggle) when स्वतःresume */
		padapter->pwrctrlpriv.bSupportRemoteWakeup = (hwinfo[EEPROM_USB_OPTIONAL_FUNCTION0] & BIT(1)) ? true : false;

		DBG_88E("%s...bHWPwrPindetect(%x)-bHWPowerdown(%x) , bSupportRemoteWakeup(%x)\n", __func__,
			padapter->pwrctrlpriv.bHWPwrPindetect, padapter->pwrctrlpriv.bHWPowerकरोwn, padapter->pwrctrlpriv.bSupportRemoteWakeup);

		DBG_88E("### PS params =>  power_mgnt(%x), usbss_enable(%x) ###\n", padapter->registrypriv.घातer_mgnt, padapter->registrypriv.usbss_enable);
	पूर्ण
पूर्ण

व्योम Hal_ReadTxPowerInfo88E(काष्ठा adapter *padapter, u8 *PROMContent, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = padapter->HalData;
	काष्ठा txघातerinfo24g pwrInfo24G;
	u8 ch, group;
	u8 TxCount;

	Hal_ReadPowerValueFromPROM_8188E(&pwrInfo24G, PROMContent, AutoLoadFail);

	अगर (!AutoLoadFail)
		pHalData->bTXPowerDataReadFromEEPORM = true;

	क्रम (ch = 0; ch < CHANNEL_MAX_NUMBER; ch++) अणु
		Hal_GetChnlGroup88E(ch, &group);
		pHalData->Index24G_CCK_Base[0][ch] = pwrInfo24G.IndexCCK_Base[0][group];
		अगर (ch == 14)
			pHalData->Index24G_BW40_Base[0][ch] = pwrInfo24G.IndexBW40_Base[0][4];
		अन्यथा
			pHalData->Index24G_BW40_Base[0][ch] = pwrInfo24G.IndexBW40_Base[0][group];

		DBG_88E("======= Path %d, Channel %d =======\n", 0, ch);
		DBG_88E("Index24G_CCK_Base[%d][%d] = 0x%x\n", 0, ch, pHalData->Index24G_CCK_Base[0][ch]);
		DBG_88E("Index24G_BW40_Base[%d][%d] = 0x%x\n", 0, ch, pHalData->Index24G_BW40_Base[0][ch]);
	पूर्ण
	क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
		pHalData->CCK_24G_Dअगरf[0][TxCount] = pwrInfo24G.CCK_Dअगरf[0][TxCount];
		pHalData->OFDM_24G_Dअगरf[0][TxCount] = pwrInfo24G.OFDM_Dअगरf[0][TxCount];
		pHalData->BW20_24G_Dअगरf[0][TxCount] = pwrInfo24G.BW20_Dअगरf[0][TxCount];
		pHalData->BW40_24G_Dअगरf[0][TxCount] = pwrInfo24G.BW40_Dअगरf[0][TxCount];
		DBG_88E("======= TxCount %d =======\n", TxCount);
		DBG_88E("CCK_24G_Diff[%d][%d] = %d\n", 0, TxCount, pHalData->CCK_24G_Dअगरf[0][TxCount]);
		DBG_88E("OFDM_24G_Diff[%d][%d] = %d\n", 0, TxCount, pHalData->OFDM_24G_Dअगरf[0][TxCount]);
		DBG_88E("BW20_24G_Diff[%d][%d] = %d\n", 0, TxCount, pHalData->BW20_24G_Dअगरf[0][TxCount]);
		DBG_88E("BW40_24G_Diff[%d][%d] = %d\n", 0, TxCount, pHalData->BW40_24G_Dअगरf[0][TxCount]);
	पूर्ण

	/*  2010/10/19 MH Add Regulator recognize क्रम CU. */
	अगर (!AutoLoadFail) अणु
		pHalData->EEPROMRegulatory = (PROMContent[EEPROM_RF_BOARD_OPTION_88E] & 0x7);	/* bit0~2 */
		अगर (PROMContent[EEPROM_RF_BOARD_OPTION_88E] == 0xFF)
			pHalData->EEPROMRegulatory = (EEPROM_DEFAULT_BOARD_OPTION & 0x7);	/* bit0~2 */
	पूर्ण अन्यथा अणु
		pHalData->EEPROMRegulatory = 0;
	पूर्ण
	DBG_88E("EEPROMRegulatory = 0x%x\n", pHalData->EEPROMRegulatory);
पूर्ण

व्योम Hal_EfuseParseXtal_8188E(काष्ठा adapter *pAdapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = pAdapter->HalData;

	अगर (!AutoLoadFail) अणु
		pHalData->CrystalCap = hwinfo[EEPROM_XTAL_88E];
		अगर (pHalData->CrystalCap == 0xFF)
			pHalData->CrystalCap = EEPROM_Default_CrystalCap_88E;
	पूर्ण अन्यथा अणु
		pHalData->CrystalCap = EEPROM_Default_CrystalCap_88E;
	पूर्ण
	DBG_88E("CrystalCap: 0x%2x\n", pHalData->CrystalCap);
पूर्ण

व्योम Hal_EfuseParseBoardType88E(काष्ठा adapter *pAdapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = pAdapter->HalData;

	अगर (!AutoLoadFail)
		pHalData->BoardType = (hwinfo[EEPROM_RF_BOARD_OPTION_88E]
					& 0xE0) >> 5;
	अन्यथा
		pHalData->BoardType = 0;
	DBG_88E("Board Type: 0x%2x\n", pHalData->BoardType);
पूर्ण

व्योम Hal_EfuseParseEEPROMVer88E(काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = padapter->HalData;

	अगर (!AutoLoadFail) अणु
		pHalData->EEPROMVersion = hwinfo[EEPROM_VERSION_88E];
		अगर (pHalData->EEPROMVersion == 0xFF)
			pHalData->EEPROMVersion = EEPROM_Default_Version;
	पूर्ण अन्यथा अणु
		pHalData->EEPROMVersion = 1;
	पूर्ण
	RT_TRACE(_module_hci_hal_init_c_, _drv_info_,
		 ("Hal_EfuseParseEEPROMVer(), EEVer = %d\n",
		 pHalData->EEPROMVersion));
पूर्ण

व्योम rtl8188e_EfuseParseChnlPlan(काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	padapter->mlmepriv.ChannelPlan =
		 hal_com_get_channel_plan(hwinfo ? hwinfo[EEPROM_ChannelPlan_88E] : 0xFF,
					  padapter->registrypriv.channel_plan,
					  RT_CHANNEL_DOMAIN_WORLD_WIDE_13, AutoLoadFail);

	DBG_88E("mlmepriv.ChannelPlan = 0x%02x\n", padapter->mlmepriv.ChannelPlan);
पूर्ण

व्योम Hal_EfuseParseCustomerID88E(काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e	*pHalData = padapter->HalData;

	अगर (!AutoLoadFail) अणु
		pHalData->EEPROMCustomerID = hwinfo[EEPROM_CUSTOMERID_88E];
	पूर्ण अन्यथा अणु
		pHalData->EEPROMCustomerID = 0;
		pHalData->EEPROMSubCustomerID = 0;
	पूर्ण
	DBG_88E("EEPROM Customer ID: 0x%2x\n", pHalData->EEPROMCustomerID);
पूर्ण

व्योम Hal_ReadAntennaDiversity88E(काष्ठा adapter *pAdapter, u8 *PROMContent, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = pAdapter->HalData;
	काष्ठा registry_priv	*registry_par = &pAdapter->registrypriv;

	अगर (!AutoLoadFail) अणु
		/*  Antenna Diversity setting. */
		अगर (registry_par->antभाग_cfg == 2) अणु /*  2:By EFUSE */
			pHalData->AntDivCfg = (PROMContent[EEPROM_RF_BOARD_OPTION_88E] & 0x18) >> 3;
			अगर (PROMContent[EEPROM_RF_BOARD_OPTION_88E] == 0xFF)
				pHalData->AntDivCfg = (EEPROM_DEFAULT_BOARD_OPTION & 0x18) >> 3;
		पूर्ण अन्यथा अणु
			pHalData->AntDivCfg = registry_par->antभाग_cfg;  /*  0:OFF , 1:ON, 2:By EFUSE */
		पूर्ण

		अगर (registry_par->antभाग_प्रकारype == 0) अणु
			/* If TRxAntDivType is AUTO in advanced setting, use EFUSE value instead. */
			pHalData->TRxAntDivType = PROMContent[EEPROM_RF_ANTENNA_OPT_88E];
			अगर (pHalData->TRxAntDivType == 0xFF)
				pHalData->TRxAntDivType = CG_TRX_HW_ANTDIV; /*  For 88EE, 1Tx and 1RxCG are fixed.(1Ant, Tx and RxCG are both on aux port) */
		पूर्ण अन्यथा अणु
			pHalData->TRxAntDivType = registry_par->antभाग_प्रकारype;
		पूर्ण

		अगर (pHalData->TRxAntDivType == CG_TRX_HW_ANTDIV || pHalData->TRxAntDivType == CGCS_RX_HW_ANTDIV)
			pHalData->AntDivCfg = 1; /*  0xC1[3] is ignored. */
	पूर्ण अन्यथा अणु
		pHalData->AntDivCfg = 0;
	पूर्ण
	DBG_88E("EEPROM : AntDivCfg = %x, TRxAntDivType = %x\n", pHalData->AntDivCfg, pHalData->TRxAntDivType);
पूर्ण

व्योम Hal_ReadThermalMeter_88E(काष्ठा adapter *Adapter, u8 *PROMContent, bool AutoloadFail)
अणु
	काष्ठा hal_data_8188e *pHalData = Adapter->HalData;

	/*  ThermalMeter from EEPROM */
	अगर (!AutoloadFail)
		pHalData->EEPROMThermalMeter = PROMContent[EEPROM_THERMAL_METER_88E];
	अन्यथा
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_88E;

	अगर (pHalData->EEPROMThermalMeter == 0xff || AutoloadFail) अणु
		pHalData->bAPKThermalMeterIgnore = true;
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_88E;
	पूर्ण
	DBG_88E("ThermalMeter = 0x%x\n", pHalData->EEPROMThermalMeter);
पूर्ण
