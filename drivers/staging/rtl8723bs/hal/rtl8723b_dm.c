<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*  Description: */
/*  This file is क्रम 92CE/92CU dynamic mechanism only */

#घोषणा _RTL8723B_DM_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>

/*  Global var */

अटल व्योम dm_CheckStatistics(काष्ठा adapter *Adapter)
अणु
पूर्ण
/*  */
/*  functions */
/*  */
अटल व्योम Init_ODM_ComInfo_8723b(काष्ठा adapter *Adapter)
अणु

	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	u8 cut_ver, fab_ver;

	/*  */
	/*  Init Value */
	/*  */
	स_रखो(pDM_Odm, 0, माप(*pDM_Odm));

	pDM_Odm->Adapter = Adapter;
#घोषणा ODM_CE 0x04
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PLATFORM, ODM_CE);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_INTERFACE, RTW_SDIO);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PACKAGE_TYPE, pHalData->PackageType);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_IC_TYPE, ODM_RTL8723B);

	fab_ver = ODM_TSMC;
	cut_ver = ODM_CUT_A;

	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_FAB_VER, fab_ver);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_CUT_VER, cut_ver);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_MP_TEST_CHIP, IS_NORMAL_CHIP(pHalData->VersionID));

	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PATCH_ID, pHalData->CustomerID);
	/* 	ODM_CMNINFO_BINHCT_TEST only क्रम MP Team */
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_BWIFI_TEST, Adapter->registrypriv.wअगरi_spec);


	अगर (pHalData->rf_type == RF_1T1R) अणु
		ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_RF_TYPE, ODM_1T1R);
	पूर्ण अन्यथा अगर (pHalData->rf_type == RF_2T2R) अणु
		ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_RF_TYPE, ODM_2T2R);
	पूर्ण अन्यथा अगर (pHalData->rf_type == RF_1T2R) अणु
		ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_RF_TYPE, ODM_1T2R);
	पूर्ण

	pdmpriv->InitODMFlag = ODM_RF_CALIBRATION|ODM_RF_TX_PWR_TRACK;

	ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_ABILITY, pdmpriv->InitODMFlag);
पूर्ण

अटल व्योम Update_ODM_ComInfo_8723b(काष्ठा adapter *Adapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &Adapter->mlmeextpriv;
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(Adapter);
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(Adapter);
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	पूर्णांक i;
	u8 zero = 0;

	pdmpriv->InitODMFlag = 0
		| ODM_BB_DIG
		| ODM_BB_RA_MASK
		| ODM_BB_DYNAMIC_TXPWR
		| ODM_BB_FA_CNT
		| ODM_BB_RSSI_MONITOR
		| ODM_BB_CCK_PD
		| ODM_BB_PWR_SAVE
		| ODM_BB_CFO_TRACKING
		| ODM_MAC_EDCA_TURBO
		| ODM_RF_TX_PWR_TRACK
		| ODM_RF_CALIBRATION
		;

	/*  */
	/*  Poपूर्णांकer reference */
	/*  */
	/* ODM_CMNINFO_MAC_PHY_MODE pHalData->MacPhyMode92D */
	/* 	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MAC_PHY_MODE,&(pDM_Odm->u8_temp)); */

	ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_ABILITY, pdmpriv->InitODMFlag);

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_TX_UNI, &(dvobj->traffic_stat.tx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_RX_UNI, &(dvobj->traffic_stat.rx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_WM_MODE, &(pmlmeext->cur_wireless_mode));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_CHNL_OFFSET, &(pHalData->nCur40MhzPrimeSC));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_MODE, &(Adapter->securitypriv.करोt11PrivacyAlgrthm));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_BW, &(pHalData->CurrentChannelBW));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_CHNL, &(pHalData->CurrentChannel));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_NET_CLOSED, &(Adapter->net_बंदd));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MP_MODE, &zero);
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_BAND, &(pHalData->CurrentBandType));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FORCED_IGI_LB, &(pHalData->u1ForcedIgiLb));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FORCED_RATE, &(pHalData->ForcedDataRate));

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SCAN, &(pmlmepriv->bScanInProcess));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_POWER_SAVING, &(pwrctrlpriv->bघातer_saving));


	क्रम (i = 0; i < NUM_STA; i++)
		ODM_CmnInfoPtrArrayHook(pDM_Odm, ODM_CMNINFO_STA_STATUS, i, शून्य);
पूर्ण

व्योम rtl8723b_InitHalDm(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	pdmpriv->DM_Type = DM_Type_ByDriver;
	pdmpriv->DMFlag = DYNAMIC_FUNC_DISABLE;

	pdmpriv->DMFlag |= DYNAMIC_FUNC_BT;

	pdmpriv->InitDMFlag = pdmpriv->DMFlag;

	Update_ODM_ComInfo_8723b(Adapter);

	ODM_DMInit(pDM_Odm);
पूर्ण

व्योम rtl8723b_HalDmWatchDog(काष्ठा adapter *Adapter)
अणु
	bool fw_current_in_ps_mode = false;
	bool bFwPSAwake = true;
	u8 hw_init_completed = false;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	hw_init_completed = Adapter->hw_init_completed;

	अगर (hw_init_completed == false)
		जाओ skip_dm;

	fw_current_in_ps_mode = adapter_to_pwrctl(Adapter)->fw_current_in_ps_mode;
	rtw_hal_get_hwreg(Adapter, HW_VAR_FWLPS_RF_ON, (u8 *)(&bFwPSAwake));

	अगर (
		(hw_init_completed == true) &&
		((!fw_current_in_ps_mode) && bFwPSAwake)
	) अणु
		/*  */
		/*  Calculate Tx/Rx statistics. */
		/*  */
		dm_CheckStatistics(Adapter);
		rtw_hal_check_rxfअगरo_full(Adapter);
	पूर्ण

	/* ODM */
	अगर (hw_init_completed == true) अणु
		u8 bLinked = false;
		u8 bsta_state = false;
		bool bBtDisabled = true;

		अगर (rtw_linked_check(Adapter)) अणु
			bLinked = true;
			अगर (check_fwstate(&Adapter->mlmepriv, WIFI_STATION_STATE))
				bsta_state = true;
		पूर्ण

		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_LINK, bLinked);
		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_STATION_STATE, bsta_state);

		/* ODM_CmnInfoUpdate(&pHalData->odmpriv , ODM_CMNINFO_RSSI_MIN, pdmpriv->MinUndecoratedPWDBForDM); */

		bBtDisabled = hal_btcoex_IsBtDisabled(Adapter);

		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_BT_ENABLED,
				  !bBtDisabled);

		ODM_DMWatchकरोg(&pHalData->odmpriv);
	पूर्ण

skip_dm:
	वापस;
पूर्ण

व्योम rtl8723b_hal_dm_in_lps(काष्ठा adapter *padapter)
अणु
	u32 PWDB_rssi = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	/* update IGI */
	ODM_Write_DIG(pDM_Odm, pDM_Odm->RSSI_Min);


	/* set rssi to fw */
	psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
	अगर (psta && (psta->rssi_stat.UndecoratedSmoothedPWDB > 0)) अणु
		PWDB_rssi = (psta->mac_id | (psta->rssi_stat.UndecoratedSmoothedPWDB<<16));

		rtl8723b_set_rssi_cmd(padapter, (u8 *)&PWDB_rssi);
	पूर्ण

पूर्ण

व्योम rtl8723b_HalDmWatchDog_in_LPS(काष्ठा adapter *Adapter)
अणु
	u8 bLinked = false;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	काष्ठा dig_t *pDM_DigTable = &pDM_Odm->DM_DigTable;
	काष्ठा sta_priv *pstapriv = &Adapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	अगर (Adapter->hw_init_completed == false)
		जाओ skip_lps_dm;


	अगर (rtw_linked_check(Adapter))
		bLinked = true;

	ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_LINK, bLinked);

	अगर (bLinked == false)
		जाओ skip_lps_dm;

	अगर (!(pDM_Odm->SupportAbility & ODM_BB_RSSI_MONITOR))
		जाओ skip_lps_dm;


	/* ODM_DMWatchकरोg(&pHalData->odmpriv); */
	/* Do DIG by RSSI In LPS-32K */

      /* 1 Find MIN-RSSI */
	psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
	अगर (!psta)
		जाओ skip_lps_dm;

	pdmpriv->EntryMinUndecoratedSmoothedPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

	अगर (pdmpriv->EntryMinUndecoratedSmoothedPWDB <= 0)
		जाओ skip_lps_dm;

	pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;

	pDM_Odm->RSSI_Min = pdmpriv->MinUndecoratedPWDBForDM;

	/* अगर (pDM_DigTable->CurIGValue != pDM_Odm->RSSI_Min) */
	अगर (
		(pDM_DigTable->CurIGValue > pDM_Odm->RSSI_Min + 5) ||
		(pDM_DigTable->CurIGValue < pDM_Odm->RSSI_Min - 5)
	)
		rtw_dm_in_lps_wk_cmd(Adapter);


skip_lps_dm:

	वापस;

पूर्ण

व्योम rtl8723b_init_dm_priv(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;

	स_रखो(pdmpriv, 0, माप(काष्ठा dm_priv));
	Init_ODM_ComInfo_8723b(Adapter);
पूर्ण
