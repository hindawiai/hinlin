<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#घोषणा _HAL_INTF_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>

व्योम rtw_hal_chip_configure(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.पूर्णांकf_chip_configure)
		padapter->HalFunc.पूर्णांकf_chip_configure(padapter);
पूर्ण

व्योम rtw_hal_पढ़ो_chip_info(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.पढ़ो_adapter_info)
		padapter->HalFunc.पढ़ो_adapter_info(padapter);
पूर्ण

व्योम rtw_hal_पढ़ो_chip_version(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.पढ़ो_chip_version)
		padapter->HalFunc.पढ़ो_chip_version(padapter);
पूर्ण

व्योम rtw_hal_def_value_init(काष्ठा adapter *padapter)
अणु
	अगर (is_primary_adapter(padapter))
		अगर (padapter->HalFunc.init_शेष_value)
			padapter->HalFunc.init_शेष_value(padapter);
पूर्ण

व्योम rtw_hal_मुक्त_data(काष्ठा adapter *padapter)
अणु
	/* मुक्त HAL Data */
	rtw_hal_data_deinit(padapter);

	अगर (is_primary_adapter(padapter))
		अगर (padapter->HalFunc.मुक्त_hal_data)
			padapter->HalFunc.मुक्त_hal_data(padapter);
पूर्ण

व्योम rtw_hal_dm_init(काष्ठा adapter *padapter)
अणु
	अगर (is_primary_adapter(padapter))
		अगर (padapter->HalFunc.dm_init)
			padapter->HalFunc.dm_init(padapter);
पूर्ण

व्योम rtw_hal_dm_deinit(काष्ठा adapter *padapter)
अणु
	/*  cancel dm  समयr */
	अगर (is_primary_adapter(padapter))
		अगर (padapter->HalFunc.dm_deinit)
			padapter->HalFunc.dm_deinit(padapter);
पूर्ण

अटल व्योम rtw_hal_init_opmode(काष्ठा adapter *padapter)
अणु
	क्रमागत ndis_802_11_network_infraकाष्ठाure networkType = Ndis802_11Infraकाष्ठाureMax;
	काष्ठा  mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	चिन्हित पूर्णांक fw_state;

	fw_state = get_fwstate(pmlmepriv);

	अगर (fw_state & WIFI_ADHOC_STATE)
		networkType = Ndis802_11IBSS;
	अन्यथा अगर (fw_state & WIFI_STATION_STATE)
		networkType = Ndis802_11Infraकाष्ठाure;
	अन्यथा अगर (fw_state & WIFI_AP_STATE)
		networkType = Ndis802_11APMode;
	अन्यथा
		वापस;

	rtw_setopmode_cmd(padapter, networkType, false);
पूर्ण

uपूर्णांक rtw_hal_init(काष्ठा adapter *padapter)
अणु
	uपूर्णांक status;
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);

	status = padapter->HalFunc.hal_init(padapter);

	अगर (status == _SUCCESS) अणु
		rtw_hal_init_opmode(padapter);

		dvobj->padapters->hw_init_completed = true;

		अगर (padapter->registrypriv.notch_filter == 1)
			rtw_hal_notch_filter(padapter, 1);

		rtw_hal_reset_security_engine(padapter);

		rtw_sec_restore_wep_key(dvobj->padapters);

		init_hw_mlme_ext(padapter);

		rtw_bb_rf_gain_offset(padapter);
	पूर्ण अन्यथा अणु
		dvobj->padapters->hw_init_completed = false;
	पूर्ण

	वापस status;
पूर्ण

uपूर्णांक rtw_hal_deinit(काष्ठा adapter *padapter)
अणु
	uपूर्णांक status = _SUCCESS;
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);

	status = padapter->HalFunc.hal_deinit(padapter);

	अगर (status == _SUCCESS) अणु
		padapter = dvobj->padapters;
		padapter->hw_init_completed = false;
	पूर्ण

	वापस status;
पूर्ण

व्योम rtw_hal_set_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	अगर (padapter->HalFunc.SetHwRegHandler)
		padapter->HalFunc.SetHwRegHandler(padapter, variable, val);
पूर्ण

व्योम rtw_hal_get_hwreg(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	अगर (padapter->HalFunc.GetHwRegHandler)
		padapter->HalFunc.GetHwRegHandler(padapter, variable, val);
पूर्ण

व्योम rtw_hal_set_hwreg_with_buf(काष्ठा adapter *padapter, u8 variable, u8 *pbuf, पूर्णांक len)
अणु
	अगर (padapter->HalFunc.SetHwRegHandlerWithBuf)
		padapter->HalFunc.SetHwRegHandlerWithBuf(padapter, variable, pbuf, len);
पूर्ण

u8 rtw_hal_set_def_var(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue)
अणु
	अगर (padapter->HalFunc.SetHalDefVarHandler)
		वापस padapter->HalFunc.SetHalDefVarHandler(padapter, eVariable, pValue);
	वापस _FAIL;
पूर्ण

u8 rtw_hal_get_def_var(काष्ठा adapter *padapter, क्रमागत hal_def_variable eVariable, व्योम *pValue)
अणु
	अगर (padapter->HalFunc.GetHalDefVarHandler)
		वापस padapter->HalFunc.GetHalDefVarHandler(padapter, eVariable, pValue);
	वापस _FAIL;
पूर्ण

व्योम rtw_hal_set_odm_var(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, bool bSet)
अणु
	अगर (padapter->HalFunc.SetHalODMVarHandler)
		padapter->HalFunc.SetHalODMVarHandler(padapter, eVariable, pValue1, bSet);
पूर्ण

व्योम rtw_hal_get_odm_var(काष्ठा adapter *padapter, क्रमागत hal_odm_variable eVariable, व्योम *pValue1, व्योम *pValue2)
अणु
	अगर (padapter->HalFunc.GetHalODMVarHandler)
		padapter->HalFunc.GetHalODMVarHandler(padapter, eVariable, pValue1, pValue2);
पूर्ण

व्योम rtw_hal_enable_पूर्णांकerrupt(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.enable_पूर्णांकerrupt)
		padapter->HalFunc.enable_पूर्णांकerrupt(padapter);
पूर्ण

व्योम rtw_hal_disable_पूर्णांकerrupt(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.disable_पूर्णांकerrupt)
		padapter->HalFunc.disable_पूर्णांकerrupt(padapter);
पूर्ण

u8 rtw_hal_check_ips_status(काष्ठा adapter *padapter)
अणु
	u8 val = false;
	अगर (padapter->HalFunc.check_ips_status)
		val = padapter->HalFunc.check_ips_status(padapter);

	वापस val;
पूर्ण

s32	rtw_hal_xmitframe_enqueue(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (padapter->HalFunc.hal_xmitframe_enqueue)
		वापस padapter->HalFunc.hal_xmitframe_enqueue(padapter, pxmitframe);

	वापस false;
पूर्ण

s32	rtw_hal_xmit(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (padapter->HalFunc.hal_xmit)
		वापस padapter->HalFunc.hal_xmit(padapter, pxmitframe);

	वापस false;
पूर्ण

/*
 * [IMPORTANT] This function would be run in पूर्णांकerrupt context.
 */
s32	rtw_hal_mgnt_xmit(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe)
अणु
	s32 ret = _FAIL;
	update_mgntframe_attrib_addr(padapter, pmgntframe);
	/* pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET; */
	/* pwlanhdr = (काष्ठा rtw_ieee80211_hdr *)pframe; */
	/* स_नकल(pmgntframe->attrib.ra, pwlanhdr->addr1, ETH_ALEN); */

	अगर (padapter->securitypriv.binstallBIPkey == true) अणु
		अगर (IS_MCAST(pmgntframe->attrib.ra)) अणु
			pmgntframe->attrib.encrypt = _BIP_;
			/* pmgntframe->attrib.bswenc = true; */
		पूर्ण अन्यथा अणु
			pmgntframe->attrib.encrypt = _AES_;
			pmgntframe->attrib.bswenc = true;
		पूर्ण
		rtw_mgmt_xmitframe_coalesce(padapter, pmgntframe->pkt, pmgntframe);
	पूर्ण

	अगर (padapter->HalFunc.mgnt_xmit)
		ret = padapter->HalFunc.mgnt_xmit(padapter, pmgntframe);
	वापस ret;
पूर्ण

s32	rtw_hal_init_xmit_priv(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.init_xmit_priv)
		वापस padapter->HalFunc.init_xmit_priv(padapter);
	वापस _FAIL;
पूर्ण

व्योम rtw_hal_मुक्त_xmit_priv(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.मुक्त_xmit_priv)
		padapter->HalFunc.मुक्त_xmit_priv(padapter);
पूर्ण

s32	rtw_hal_init_recv_priv(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.init_recv_priv)
		वापस padapter->HalFunc.init_recv_priv(padapter);

	वापस _FAIL;
पूर्ण

व्योम rtw_hal_मुक्त_recv_priv(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.मुक्त_recv_priv)
		padapter->HalFunc.मुक्त_recv_priv(padapter);
पूर्ण

व्योम rtw_hal_update_ra_mask(काष्ठा sta_info *psta, u8 rssi_level)
अणु
	काष्ठा adapter *padapter;
	काष्ठा mlme_priv *pmlmepriv;

	अगर (!psta)
		वापस;

	padapter = psta->padapter;

	pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
		add_RATid(padapter, psta, rssi_level);
	अन्यथा अणु
		अगर (padapter->HalFunc.UpdateRAMaskHandler)
			padapter->HalFunc.UpdateRAMaskHandler(padapter, psta->mac_id, rssi_level);
	पूर्ण
पूर्ण

व्योम rtw_hal_add_ra_tid(काष्ठा adapter *padapter, u32 biपंचांगap, u8 *arg, u8 rssi_level)
अणु
	अगर (padapter->HalFunc.Add_RateATid)
		padapter->HalFunc.Add_RateATid(padapter, biपंचांगap, arg, rssi_level);
पूर्ण

/*Start specअगरical पूर्णांकerface thपढ़ो		*/
व्योम rtw_hal_start_thपढ़ो(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.run_thपढ़ो)
		padapter->HalFunc.run_thपढ़ो(padapter);
पूर्ण
/*Start specअगरical पूर्णांकerface thपढ़ो		*/
व्योम rtw_hal_stop_thपढ़ो(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.cancel_thपढ़ो)
		padapter->HalFunc.cancel_thपढ़ो(padapter);
पूर्ण

u32 rtw_hal_पढ़ो_bbreg(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask)
अणु
	u32 data = 0;
	अगर (padapter->HalFunc.पढ़ो_bbreg)
		 data = padapter->HalFunc.पढ़ो_bbreg(padapter, RegAddr, BitMask);
	वापस data;
पूर्ण
व्योम rtw_hal_ग_लिखो_bbreg(काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask, u32 Data)
अणु
	अगर (padapter->HalFunc.ग_लिखो_bbreg)
		padapter->HalFunc.ग_लिखो_bbreg(padapter, RegAddr, BitMask, Data);
पूर्ण

u32 rtw_hal_पढ़ो_rfreg(काष्ठा adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask)
अणु
	u32 data = 0;
	अगर (padapter->HalFunc.पढ़ो_rfreg)
		data = padapter->HalFunc.पढ़ो_rfreg(padapter, eRFPath, RegAddr, BitMask);
	वापस data;
पूर्ण
व्योम rtw_hal_ग_लिखो_rfreg(काष्ठा adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask, u32 Data)
अणु
	अगर (padapter->HalFunc.ग_लिखो_rfreg)
		padapter->HalFunc.ग_लिखो_rfreg(padapter, eRFPath, RegAddr, BitMask, Data);
पूर्ण

व्योम rtw_hal_set_chan(काष्ठा adapter *padapter, u8 channel)
अणु
	अगर (padapter->HalFunc.set_channel_handler)
		padapter->HalFunc.set_channel_handler(padapter, channel);
पूर्ण

व्योम rtw_hal_set_chnl_bw(काष्ठा adapter *padapter, u8 channel,
			 क्रमागत channel_width Bandwidth, u8 Offset40, u8 Offset80)
अणु
	अगर (padapter->HalFunc.set_chnl_bw_handler)
		padapter->HalFunc.set_chnl_bw_handler(padapter, channel,
						      Bandwidth, Offset40,
						      Offset80);
पूर्ण

व्योम rtw_hal_dm_watchकरोg(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.hal_dm_watchकरोg)
		padapter->HalFunc.hal_dm_watchकरोg(padapter);
पूर्ण

व्योम rtw_hal_dm_watchकरोg_in_lps(काष्ठा adapter *padapter)
अणु
	अगर (adapter_to_pwrctl(padapter)->fw_current_in_ps_mode) अणु
		अगर (padapter->HalFunc.hal_dm_watchकरोg_in_lps)
			padapter->HalFunc.hal_dm_watchकरोg_in_lps(padapter); /* this function caller is in पूर्णांकerrupt context */
	पूर्ण
पूर्ण

व्योम beacon_timing_control(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.SetBeaconRelatedRegistersHandler)
		padapter->HalFunc.SetBeaconRelatedRegistersHandler(padapter);
पूर्ण


s32 rtw_hal_xmit_thपढ़ो_handler(काष्ठा adapter *padapter)
अणु
	अगर (padapter->HalFunc.xmit_thपढ़ो_handler)
		वापस padapter->HalFunc.xmit_thपढ़ो_handler(padapter);
	वापस _FAIL;
पूर्ण

व्योम rtw_hal_notch_filter(काष्ठा adapter *adapter, bool enable)
अणु
	अगर (adapter->HalFunc.hal_notch_filter)
		adapter->HalFunc.hal_notch_filter(adapter, enable);
पूर्ण

व्योम rtw_hal_reset_security_engine(काष्ठा adapter *adapter)
अणु
	अगर (adapter->HalFunc.hal_reset_security_engine)
		adapter->HalFunc.hal_reset_security_engine(adapter);
पूर्ण

bool rtw_hal_c2h_valid(काष्ठा adapter *adapter, u8 *buf)
अणु
	वापस c2h_evt_valid((काष्ठा c2h_evt_hdr_88xx *)buf);
पूर्ण

s32 rtw_hal_c2h_handler(काष्ठा adapter *adapter, u8 *c2h_evt)
अणु
	s32 ret = _FAIL;
	अगर (adapter->HalFunc.c2h_handler)
		ret = adapter->HalFunc.c2h_handler(adapter, c2h_evt);
	वापस ret;
पूर्ण

c2h_id_filter rtw_hal_c2h_id_filter_ccx(काष्ठा adapter *adapter)
अणु
	वापस adapter->HalFunc.c2h_id_filter_ccx;
पूर्ण

s32 rtw_hal_is_disable_sw_channel_plan(काष्ठा adapter *padapter)
अणु
	वापस GET_HAL_DATA(padapter)->bDisableSWChannelPlan;
पूर्ण

s32 rtw_hal_macid_sleep(काष्ठा adapter *padapter, u32 macid)
अणु
	u8 support;

	support = false;
	rtw_hal_get_def_var(padapter, HAL_DEF_MACID_SLEEP, &support);
	अगर (false == support)
		वापस _FAIL;

	rtw_hal_set_hwreg(padapter, HW_VAR_MACID_SLEEP, (u8 *)&macid);

	वापस _SUCCESS;
पूर्ण

s32 rtw_hal_macid_wakeup(काष्ठा adapter *padapter, u32 macid)
अणु
	u8 support;

	support = false;
	rtw_hal_get_def_var(padapter, HAL_DEF_MACID_SLEEP, &support);
	अगर (false == support)
		वापस _FAIL;

	rtw_hal_set_hwreg(padapter, HW_VAR_MACID_WAKEUP, (u8 *)&macid);

	वापस _SUCCESS;
पूर्ण

s32 rtw_hal_fill_h2c_cmd(काष्ठा adapter *padapter, u8 ElementID, u32 CmdLen, u8 *pCmdBuffer)
अणु
	s32 ret = _FAIL;

	अगर (padapter->HalFunc.fill_h2c_cmd)
		ret = padapter->HalFunc.fill_h2c_cmd(padapter, ElementID, CmdLen, pCmdBuffer);

	वापस ret;
पूर्ण
