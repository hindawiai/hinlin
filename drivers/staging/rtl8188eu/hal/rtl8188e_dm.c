<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*  */
/*  Description: */
/*  */
/*  This file is क्रम 92CE/92CU dynamic mechanism only */
/*  */
/*  */
/*  */
#घोषणा _RTL8188E_DM_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#समावेश <rtl8188e_hal.h>

/*  Initialize GPIO setting रेजिस्टरs */
अटल व्योम dm_InitGPIOSetting(काष्ठा adapter *Adapter)
अणु
	u8 पंचांगp1byte;

	पंचांगp1byte = usb_पढ़ो8(Adapter, REG_GPIO_MUXCFG);
	पंचांगp1byte &= (GPIOSEL_GPIO | ~GPIOSEL_ENBT);

	usb_ग_लिखो8(Adapter, REG_GPIO_MUXCFG, पंचांगp1byte);
पूर्ण

अटल व्योम Init_ODM_ComInfo_88E(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *hal_data = Adapter->HalData;
	काष्ठा dm_priv *pdmpriv = &hal_data->dmpriv;
	काष्ठा odm_dm_काष्ठा *dm_odm = &hal_data->odmpriv;

	/*  Init Value */
	स_रखो(dm_odm, 0, माप(*dm_odm));

	dm_odm->Adapter = Adapter;
	dm_odm->SupportPlatक्रमm = ODM_CE;
	dm_odm->SupportICType = ODM_RTL8188E;
	dm_odm->CutVersion = ODM_CUT_A;
	dm_odm->bIsMPChip = hal_data->VersionID.ChipType == NORMAL_CHIP;
	dm_odm->PatchID = hal_data->CustomerID;
	dm_odm->bWIFITest = Adapter->registrypriv.wअगरi_spec;

	dm_odm->AntDivType = hal_data->TRxAntDivType;

	/* Tx घातer tracking BB swing table.
	 * The base index =
	 * 12. +((12-n)/2)dB 13~?? = decrease tx pwr by -((n-12)/2)dB
	 */
	dm_odm->BbSwingIdxOfdm = 12; /*  Set शेष value as index 12. */
	dm_odm->BbSwingIdxOfdmCurrent = 12;
	dm_odm->BbSwingFlagOfdm = false;

	pdmpriv->InitODMFlag = ODM_RF_CALIBRATION |
			       ODM_RF_TX_PWR_TRACK;

	dm_odm->SupportAbility = pdmpriv->InitODMFlag;
पूर्ण

अटल व्योम Update_ODM_ComInfo_88E(काष्ठा adapter *Adapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &Adapter->mlmeextpriv;
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	काष्ठा pwrctrl_priv *pwrctrlpriv = &Adapter->pwrctrlpriv;
	काष्ठा hal_data_8188e *hal_data = Adapter->HalData;
	काष्ठा odm_dm_काष्ठा *dm_odm = &hal_data->odmpriv;
	काष्ठा dm_priv *pdmpriv = &hal_data->dmpriv;
	पूर्णांक i;

	pdmpriv->InitODMFlag = ODM_BB_DIG |
			       ODM_BB_RA_MASK |
			       ODM_BB_DYNAMIC_TXPWR |
			       ODM_BB_FA_CNT |
			       ODM_BB_RSSI_MONITOR |
			       ODM_BB_CCK_PD |
			       ODM_BB_PWR_SAVE |
			       ODM_MAC_EDCA_TURBO |
			       ODM_RF_CALIBRATION |
			       ODM_RF_TX_PWR_TRACK;
	अगर (hal_data->AntDivCfg)
		pdmpriv->InitODMFlag |= ODM_BB_ANT_DIV;

	अगर (Adapter->registrypriv.mp_mode == 1) अणु
		pdmpriv->InitODMFlag = ODM_RF_CALIBRATION |
				       ODM_RF_TX_PWR_TRACK;
	पूर्ण

	dm_odm->SupportAbility = pdmpriv->InitODMFlag;

	dm_odm->pNumTxBytesUnicast = &Adapter->xmitpriv.tx_bytes;
	dm_odm->pNumRxBytesUnicast = &Adapter->recvpriv.rx_bytes;
	dm_odm->pWirelessMode = &pmlmeext->cur_wireless_mode;
	dm_odm->pSecChOffset = &hal_data->nCur40MhzPrimeSC;
	dm_odm->pSecurity = (u8 *)&Adapter->securitypriv.करोt11PrivacyAlgrthm;
	dm_odm->pBandWidth = (u8 *)&hal_data->CurrentChannelBW;
	dm_odm->pChannel = &hal_data->CurrentChannel;
	dm_odm->pbNet_बंदd = (bool *)&Adapter->net_बंदd;
	dm_odm->mp_mode = &Adapter->registrypriv.mp_mode;
	dm_odm->pbScanInProcess = (bool *)&pmlmepriv->bScanInProcess;
	dm_odm->pbPowerSaving = (bool *)&pwrctrlpriv->bघातer_saving;
	dm_odm->AntDivType = hal_data->TRxAntDivType;

	/* Tx घातer tracking BB swing table.
	 * The base index =
	 * 12. +((12-n)/2)dB 13~?? = decrease tx pwr by -((n-12)/2)dB
	 */
	dm_odm->BbSwingIdxOfdm = 12; /*  Set शेष value as index 12. */
	dm_odm->BbSwingIdxOfdmCurrent = 12;
	dm_odm->BbSwingFlagOfdm = false;

	क्रम (i = 0; i < NUM_STA; i++)
		ODM_CmnInfoPtrArrayHook(dm_odm, ODM_CMNINFO_STA_STATUS, i,
					शून्य);
पूर्ण

व्योम rtl8188e_InitHalDm(काष्ठा adapter *Adapter)
अणु
	काष्ठा dm_priv *pdmpriv = &Adapter->HalData->dmpriv;
	काष्ठा odm_dm_काष्ठा *dm_odm = &Adapter->HalData->odmpriv;

	dm_InitGPIOSetting(Adapter);
	pdmpriv->DM_Type = DM_Type_ByDriver;
	pdmpriv->DMFlag = DYNAMIC_FUNC_DISABLE;
	Update_ODM_ComInfo_88E(Adapter);
	ODM_DMInit(dm_odm);
पूर्ण

व्योम rtw_hal_dm_watchकरोg(काष्ठा adapter *Adapter)
अणु
	u8 hw_init_completed = false;
	काष्ठा mlme_priv *pmlmepriv = शून्य;
	u8 bLinked = false;

	hw_init_completed = Adapter->hw_init_completed;

	अगर (!hw_init_completed)
		जाओ skip_dm;

	/* ODM */
	pmlmepriv = &Adapter->mlmepriv;

	अगर ((check_fwstate(pmlmepriv, WIFI_AP_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE |
			   WIFI_ADHOC_MASTER_STATE))) अणु
		अगर (Adapter->stapriv.asoc_sta_count > 2)
			bLinked = true;
	पूर्ण अन्यथा अणु/* Station mode */
		अगर (check_fwstate(pmlmepriv, _FW_LINKED))
			bLinked = true;
	पूर्ण

	Adapter->HalData->odmpriv.bLinked = bLinked;
	ODM_DMWatchकरोg(&Adapter->HalData->odmpriv);
skip_dm:
	/*  Check GPIO to determine current RF on/off and Pbc status. */
	/*  Check Hardware Radio ON/OFF or not */
	वापस;
पूर्ण

व्योम rtw_hal_dm_init(काष्ठा adapter *Adapter)
अणु
	काष्ठा dm_priv *pdmpriv = &Adapter->HalData->dmpriv;
	काष्ठा odm_dm_काष्ठा *podmpriv = &Adapter->HalData->odmpriv;

	स_रखो(pdmpriv, 0, माप(काष्ठा dm_priv));
	Init_ODM_ComInfo_88E(Adapter);
	ODM_InitDebugSetting(podmpriv);
पूर्ण

/*  Add new function to reset the state of antenna भागersity beक्रमe link. */
/*  Compare RSSI क्रम deciding antenna */
व्योम rtw_hal_antभाग_rssi_compared(काष्ठा adapter *Adapter,
				  काष्ठा wlan_bssid_ex *dst,
				  काष्ठा wlan_bssid_ex *src)
अणु
	अगर (Adapter->HalData->AntDivCfg != 0) अणु
		/* select optimum_antenna क्रम beक्रमe linked => For antenna
		 * भागersity
		 */
		अगर (dst->Rssi >= src->Rssi) अणु/* keep org parameter */
			src->Rssi = dst->Rssi;
			src->PhyInfo.Optimum_antenna =
				dst->PhyInfo.Optimum_antenna;
		पूर्ण
	पूर्ण
पूर्ण

/*  Add new function to reset the state of antenna भागersity beक्रमe link. */
bool rtw_hal_antभाग_beक्रमe_linked(काष्ठा adapter *Adapter)
अणु
	काष्ठा odm_dm_काष्ठा *dm_odm = &Adapter->HalData->odmpriv;
	काष्ठा sw_ant_चयन *dm_swat_tbl = &dm_odm->DM_SWAT_Table;
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;

	/*  Condition that करोes not need to use antenna भागersity. */
	अगर (Adapter->HalData->AntDivCfg == 0)
		वापस false;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		वापस false;

	अगर (dm_swat_tbl->SWAS_NoLink_State != 0) अणु
		dm_swat_tbl->SWAS_NoLink_State = 0;
		वापस false;
	पूर्ण

	/* चयन channel */
	dm_swat_tbl->SWAS_NoLink_State = 1;
	dm_swat_tbl->CurAntenna = (dm_swat_tbl->CurAntenna == Antenna_A) ?
				  Antenna_B : Antenna_A;

	rtw_antenna_select_cmd(Adapter, dm_swat_tbl->CurAntenna, false);
	वापस true;
पूर्ण
