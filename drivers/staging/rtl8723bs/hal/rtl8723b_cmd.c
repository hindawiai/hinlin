<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8723B_CMD_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>
#समावेश "hal_com_h2c.h"

#घोषणा MAX_H2C_BOX_NUMS	4
#घोषणा MESSAGE_BOX_SIZE	4

#घोषणा RTL8723B_MAX_CMD_LEN	7
#घोषणा RTL8723B_EX_MESSAGE_BOX_SIZE	4

अटल u8 _is_fw_पढ़ो_cmd_करोwn(काष्ठा adapter *padapter, u8 msgbox_num)
अणु
	u8 पढ़ो_करोwn = false;
	पूर्णांक retry_cnts = 100;

	u8 valid;

	करो अणु
		valid = rtw_पढ़ो8(padapter, REG_HMETFR) & BIT(msgbox_num);
		अगर (0 == valid) अणु
			पढ़ो_करोwn = true;
		पूर्ण
	पूर्ण जबतक ((!पढ़ो_करोwn) && (retry_cnts--));

	वापस पढ़ो_करोwn;

पूर्ण


/*****************************************
* H2C Msg क्रमmat :
*| 31 - 8		|7-5	| 4 - 0	|
*| h2c_msg	|Class	|CMD_ID	|
*| 31-0						|
*| Ext msg					|
*
******************************************/
s32 FillH2CCmd8723B(काष्ठा adapter *padapter, u8 ElementID, u32 CmdLen, u8 *pCmdBuffer)
अणु
	u8 h2c_box_num;
	u32 msgbox_addr;
	u32 msgbox_ex_addr = 0;
	काष्ठा hal_com_data *pHalData;
	u32 h2c_cmd = 0;
	u32 h2c_cmd_ex = 0;
	s32 ret = _FAIL;

	padapter = GET_PRIMARY_ADAPTER(padapter);
	pHalData = GET_HAL_DATA(padapter);
	अगर (mutex_lock_पूर्णांकerruptible(&(adapter_to_dvobj(padapter)->h2c_fwcmd_mutex)))
		वापस ret;

	अगर (!pCmdBuffer) अणु
		जाओ निकास;
	पूर्ण

	अगर (CmdLen > RTL8723B_MAX_CMD_LEN) अणु
		जाओ निकास;
	पूर्ण

	अगर (padapter->bSurpriseRemoved)
		जाओ निकास;

	/* pay attention to अगर  race condition happened in  H2C cmd setting. */
	करो अणु
		h2c_box_num = pHalData->LastHMEBoxNum;

		अगर (!_is_fw_पढ़ो_cmd_करोwn(padapter, h2c_box_num))
			जाओ निकास;

		अगर (CmdLen <= 3)
			स_नकल((u8 *)(&h2c_cmd)+1, pCmdBuffer, CmdLen);
		अन्यथा अणु
			स_नकल((u8 *)(&h2c_cmd)+1, pCmdBuffer, 3);
			स_नकल((u8 *)(&h2c_cmd_ex), pCmdBuffer+3, CmdLen-3);
/* 			*(u8 *)(&h2c_cmd) |= BIT(7); */
		पूर्ण

		*(u8 *)(&h2c_cmd) |= ElementID;

		अगर (CmdLen > 3) अणु
			msgbox_ex_addr = REG_HMEBOX_EXT0_8723B + (h2c_box_num*RTL8723B_EX_MESSAGE_BOX_SIZE);
			rtw_ग_लिखो32(padapter, msgbox_ex_addr, h2c_cmd_ex);
		पूर्ण
		msgbox_addr = REG_HMEBOX_0 + (h2c_box_num*MESSAGE_BOX_SIZE);
		rtw_ग_लिखो32(padapter, msgbox_addr, h2c_cmd);

		pHalData->LastHMEBoxNum = (h2c_box_num+1) % MAX_H2C_BOX_NUMS;

	पूर्ण जबतक (0);

	ret = _SUCCESS;

निकास:

	mutex_unlock(&(adapter_to_dvobj(padapter)->h2c_fwcmd_mutex));
	वापस ret;
पूर्ण

अटल व्योम Conकाष्ठाBeacon(काष्ठा adapter *padapter, u8 *pframe, u32 *pLength)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 rate_len, pktlen;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *cur_network = &(pmlmeinfo->network);
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	स_नकल(pwlanhdr->addr1, bc_addr, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, get_my_bssid(cur_network), ETH_ALEN);

	SetSeqNum(pwlanhdr, 0/*pmlmeext->mgnt_seq*/);
	/* pmlmeext->mgnt_seq++; */
	SetFrameSubType(pframe, WIFI_BEACON);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	/* बारtamp will be inserted by hardware */
	pframe += 8;
	pktlen += 8;

	/*  beacon पूर्णांकerval: 2 bytes */
	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->IEs)), 2);

	pframe += 2;
	pktlen += 2;

	/*  capability info: 2 bytes */
	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->IEs)), 2);

	pframe += 2;
	pktlen += 2;

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) अणु
		pktlen += cur_network->IELength - माप(काष्ठा ndis_802_11_fix_ie);
		स_नकल(pframe, cur_network->IEs+माप(काष्ठा ndis_802_11_fix_ie), pktlen);

		जाओ _Conकाष्ठाBeacon;
	पूर्ण

	/* below क्रम ad-hoc mode */

	/*  SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->Ssid.SsidLength, cur_network->Ssid.Ssid, &pktlen);

	/*  supported rates... */
	rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
	pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, ((rate_len > 8) ? 8 : rate_len), cur_network->SupportedRates, &pktlen);

	/*  DS parameter set */
	pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&(cur_network->Configuration.DSConfig), &pktlen);

	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) अणु
		u32 ATIMWinकरोw;
		/*  IBSS Parameter Set... */
		/* ATIMWinकरोw = cur->Configuration.ATIMWinकरोw; */
		ATIMWinकरोw = 0;
		pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pktlen);
	पूर्ण


	/* toकरो: ERP IE */


	/*  EXTERNDED SUPPORTED RATE */
	अगर (rate_len > 8)
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pktlen);


	/* toकरो:HT क्रम adhoc */

_Conकाष्ठाBeacon:

	अगर ((pktlen + TXDESC_SIZE) > 512)
		वापस;

	*pLength = pktlen;

पूर्ण

अटल व्योम Conकाष्ठाPSPoll(काष्ठा adapter *padapter, u8 *pframe, u32 *pLength)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	/*  Frame control. */
	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;
	SetPwrMgt(fctrl);
	SetFrameSubType(pframe, WIFI_PSPOLL);

	/*  AID. */
	SetDuration(pframe, (pmlmeinfo->aid | 0xc000));

	/*  BSSID. */
	स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	/*  TA. */
	स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);

	*pLength = 16;
पूर्ण

अटल व्योम Conकाष्ठाNullFunctionData(
	काष्ठा adapter *padapter,
	u8 *pframe,
	u32 *pLength,
	u8 *StaAddr,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bForcePowerSave
)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 pktlen;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	अगर (bForcePowerSave)
		SetPwrMgt(fctrl);

	चयन (cur_network->network.Infraकाष्ठाureMode) अणु
	हाल Ndis802_11Infraकाष्ठाure:
		SetToDs(fctrl);
		स_नकल(pwlanhdr->addr1, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
		स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
		स_नकल(pwlanhdr->addr3, StaAddr, ETH_ALEN);
		अवरोध;
	हाल Ndis802_11APMode:
		SetFrDs(fctrl);
		स_नकल(pwlanhdr->addr1, StaAddr, ETH_ALEN);
		स_नकल(pwlanhdr->addr2, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
		स_नकल(pwlanhdr->addr3, myid(&(padapter->eeprompriv)), ETH_ALEN);
		अवरोध;
	हाल Ndis802_11IBSS:
	शेष:
		स_नकल(pwlanhdr->addr1, StaAddr, ETH_ALEN);
		स_नकल(pwlanhdr->addr2, myid(&(padapter->eeprompriv)), ETH_ALEN);
		स_नकल(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);
		अवरोध;
	पूर्ण

	SetSeqNum(pwlanhdr, 0);

	अगर (bQoS) अणु
		काष्ठा ieee80211_qos_hdr *pwlanqoshdr;

		SetFrameSubType(pframe, WIFI_QOS_DATA_शून्य);

		pwlanqoshdr = (काष्ठा ieee80211_qos_hdr *)pframe;
		SetPriority(&pwlanqoshdr->qos_ctrl, AC);
		SetEOSP(&pwlanqoshdr->qos_ctrl, bEosp);

		pktlen = माप(काष्ठा ieee80211_qos_hdr);
	पूर्ण अन्यथा अणु
		SetFrameSubType(pframe, WIFI_DATA_शून्य);

		pktlen = माप(काष्ठा ieee80211_hdr_3addr);
	पूर्ण

	*pLength = pktlen;
पूर्ण

/*
 * To check अगर reserved page content is destroyed by beacon because beacon
 * is too large.
 */
/* 2010.06.23. Added by tynli. */
व्योम CheckFwRsvdPageContent(काष्ठा adapter *Adapter)
अणु
पूर्ण

अटल व्योम rtl8723b_set_FwRsvdPage_cmd(काष्ठा adapter *padapter, काष्ठा rsvdpage_loc *rsvdpageloc)
अणु
	u8 u1H2CRsvdPageParm[H2C_RSVDPAGE_LOC_LEN] = अणु0पूर्ण;

	SET_8723B_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(u1H2CRsvdPageParm, rsvdpageloc->LocProbeRsp);
	SET_8723B_H2CCMD_RSVDPAGE_LOC_PSPOLL(u1H2CRsvdPageParm, rsvdpageloc->LocPsPoll);
	SET_8723B_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(u1H2CRsvdPageParm, rsvdpageloc->LocNullData);
	SET_8723B_H2CCMD_RSVDPAGE_LOC_QOS_शून्य_DATA(u1H2CRsvdPageParm, rsvdpageloc->LocQosNull);
	SET_8723B_H2CCMD_RSVDPAGE_LOC_BT_QOS_शून्य_DATA(u1H2CRsvdPageParm, rsvdpageloc->LocBTQosNull);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CRsvdPageParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CRsvdPageParm, H2C_RSVDPAGE_LOC_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_RSVD_PAGE, H2C_RSVDPAGE_LOC_LEN, u1H2CRsvdPageParm);
पूर्ण

अटल व्योम rtl8723b_set_FwAoacRsvdPage_cmd(काष्ठा adapter *padapter, काष्ठा rsvdpage_loc *rsvdpageloc)
अणु
पूर्ण

व्योम rtl8723b_set_FwMediaStatusRpt_cmd(काष्ठा adapter *padapter, u8 mstatus, u8 macid)
अणु
	u8 u1H2CMediaStatusRptParm[H2C_MEDIA_STATUS_RPT_LEN] = अणु0पूर्ण;
	u8 macid_end = 0;

	SET_8723B_H2CCMD_MSRRPT_PARM_OPMODE(u1H2CMediaStatusRptParm, mstatus);
	SET_8723B_H2CCMD_MSRRPT_PARM_MACID_IND(u1H2CMediaStatusRptParm, 0);
	SET_8723B_H2CCMD_MSRRPT_PARM_MACID(u1H2CMediaStatusRptParm, macid);
	SET_8723B_H2CCMD_MSRRPT_PARM_MACID_END(u1H2CMediaStatusRptParm, macid_end);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CMediaStatusRptParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CMediaStatusRptParm, H2C_MEDIA_STATUS_RPT_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_MEDIA_STATUS_RPT, H2C_MEDIA_STATUS_RPT_LEN, u1H2CMediaStatusRptParm);
पूर्ण

व्योम rtl8723b_set_FwMacIdConfig_cmd(काष्ठा adapter *padapter, u8 mac_id, u8 raid, u8 bw, u8 sgi, u32 mask)
अणु
	u8 u1H2CMacIdConfigParm[H2C_MACID_CFG_LEN] = अणु0पूर्ण;

	SET_8723B_H2CCMD_MACID_CFG_MACID(u1H2CMacIdConfigParm, mac_id);
	SET_8723B_H2CCMD_MACID_CFG_RAID(u1H2CMacIdConfigParm, raid);
	SET_8723B_H2CCMD_MACID_CFG_SGI_EN(u1H2CMacIdConfigParm, sgi ? 1 : 0);
	SET_8723B_H2CCMD_MACID_CFG_BW(u1H2CMacIdConfigParm, bw);
	SET_8723B_H2CCMD_MACID_CFG_RATE_MASK0(u1H2CMacIdConfigParm, (u8)(mask & 0x000000ff));
	SET_8723B_H2CCMD_MACID_CFG_RATE_MASK1(u1H2CMacIdConfigParm, (u8)((mask & 0x0000ff00) >> 8));
	SET_8723B_H2CCMD_MACID_CFG_RATE_MASK2(u1H2CMacIdConfigParm, (u8)((mask & 0x00ff0000) >> 16));
	SET_8723B_H2CCMD_MACID_CFG_RATE_MASK3(u1H2CMacIdConfigParm, (u8)((mask & 0xff000000) >> 24));

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CMacIdConfigParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CMacIdConfigParm, H2C_MACID_CFG_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_MACID_CFG, H2C_MACID_CFG_LEN, u1H2CMacIdConfigParm);
पूर्ण

व्योम rtl8723b_set_rssi_cmd(काष्ठा adapter *padapter, u8 *param)
अणु
	u8 u1H2CRssiSettingParm[H2C_RSSI_SETTING_LEN] = अणु0पूर्ण;
	u8 mac_id = *param;
	u8 rssi = *(param+2);
	u8 uldl_state = 0;

	SET_8723B_H2CCMD_RSSI_SETTING_MACID(u1H2CRssiSettingParm, mac_id);
	SET_8723B_H2CCMD_RSSI_SETTING_RSSI(u1H2CRssiSettingParm, rssi);
	SET_8723B_H2CCMD_RSSI_SETTING_ULDL_STATE(u1H2CRssiSettingParm, uldl_state);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CRssiSettingParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CRssiSettingParm, H2C_RSSI_SETTING_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_RSSI_SETTING, H2C_RSSI_SETTING_LEN, u1H2CRssiSettingParm);
पूर्ण

व्योम rtl8723b_set_FwPwrMode_cmd(काष्ठा adapter *padapter, u8 psmode)
अणु
	पूर्णांक i;
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	u8 u1H2CPwrModeParm[H2C_PWRMODE_LEN] = अणु0पूर्ण;
	u8 PowerState = 0, awake_पूर्णांकvl = 1, byte5 = 0, rlbm = 0;

	अगर (pwrpriv->dtim > 0 && pwrpriv->dtim < 16)
		awake_पूर्णांकvl = pwrpriv->dtim+1;/* DTIM = (awake_पूर्णांकvl - 1) */
	अन्यथा
		awake_पूर्णांकvl = 3;/* DTIM =2 */

	rlbm = 2;

	अगर (padapter->registrypriv.wअगरi_spec == 1) अणु
		awake_पूर्णांकvl = 2;
		rlbm = 2;
	पूर्ण

	अगर (psmode > 0) अणु
		अगर (hal_btcoex_IsBtControlLps(padapter) == true) अणु
			PowerState = hal_btcoex_RpwmVal(padapter);
			byte5 = hal_btcoex_LpsVal(padapter);

			अगर ((rlbm == 2) && (byte5 & BIT(4))) अणु
				/*  Keep awake पूर्णांकerval to 1 to prevent from */
				/*  decreasing coex perक्रमmance */
				awake_पूर्णांकvl = 2;
				rlbm = 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			PowerState = 0x00;/*  AllON(0x0C), RFON(0x04), RFOFF(0x00) */
			byte5 = 0x40;
		पूर्ण
	पूर्ण अन्यथा अणु
		PowerState = 0x0C;/*  AllON(0x0C), RFON(0x04), RFOFF(0x00) */
		byte5 = 0x40;
	पूर्ण

	SET_8723B_H2CCMD_PWRMODE_PARM_MODE(u1H2CPwrModeParm, (psmode > 0) ? 1 : 0);
	SET_8723B_H2CCMD_PWRMODE_PARM_SMART_PS(u1H2CPwrModeParm, pwrpriv->smart_ps);
	SET_8723B_H2CCMD_PWRMODE_PARM_RLBM(u1H2CPwrModeParm, rlbm);
	SET_8723B_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(u1H2CPwrModeParm, awake_पूर्णांकvl);
	SET_8723B_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(u1H2CPwrModeParm, padapter->registrypriv.uapsd_enable);
	SET_8723B_H2CCMD_PWRMODE_PARM_PWR_STATE(u1H2CPwrModeParm, PowerState);
	SET_8723B_H2CCMD_PWRMODE_PARM_BYTE5(u1H2CPwrModeParm, byte5);
	अगर (psmode != PS_MODE_ACTIVE) अणु
		अगर (!pmlmeext->adaptive_tsf_करोne && pmlmeext->bcn_cnt > 0) अणु
			u8 ratio_20_delay, ratio_80_delay;

			/* byte 6 क्रम adaptive_early_32k */
			/* 0:3] = DrvBcnEarly  (ms) , [4:7] = DrvBcnTimeOut  (ms) */
			/*  20% क्रम DrvBcnEarly, 80% क्रम DrvBcnTimeOut */
			ratio_20_delay = 0;
			ratio_80_delay = 0;
			pmlmeext->DrvBcnEarly = 0xff;
			pmlmeext->DrvBcnTimeOut = 0xff;

			क्रम (i = 0; i < 9; i++) अणु
				pmlmeext->bcn_delay_ratio[i] = (pmlmeext->bcn_delay_cnt[i]*100)/pmlmeext->bcn_cnt;

				ratio_20_delay += pmlmeext->bcn_delay_ratio[i];
				ratio_80_delay += pmlmeext->bcn_delay_ratio[i];

				अगर (ratio_20_delay > 20 && pmlmeext->DrvBcnEarly == 0xff)
					pmlmeext->DrvBcnEarly = i;

				अगर (ratio_80_delay > 80 && pmlmeext->DrvBcnTimeOut == 0xff)
					pmlmeext->DrvBcnTimeOut = i;

				/* reset adaptive_early_32k cnt */
				pmlmeext->bcn_delay_cnt[i] = 0;
				pmlmeext->bcn_delay_ratio[i] = 0;

			पूर्ण

			pmlmeext->bcn_cnt = 0;
			pmlmeext->adaptive_tsf_करोne = true;

		पूर्ण

/* offload to FW अगर fw version > v15.10
		pmlmeext->DrvBcnEarly = 0;
		pmlmeext->DrvBcnTimeOut =7;

		अगर ((pmlmeext->DrvBcnEarly!= 0Xff) && (pmlmeext->DrvBcnTimeOut!= 0xff))
			u1H2CPwrModeParm[H2C_PWRMODE_LEN-1] = BIT(0) | ((pmlmeext->DrvBcnEarly<<1)&0x0E) |((pmlmeext->DrvBcnTimeOut<<4)&0xf0) ;
*/

	पूर्ण

	hal_btcoex_RecordPwrMode(padapter, u1H2CPwrModeParm, H2C_PWRMODE_LEN);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CPwrModeParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CPwrModeParm, H2C_PWRMODE_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_SET_PWR_MODE, H2C_PWRMODE_LEN, u1H2CPwrModeParm);
पूर्ण

व्योम rtl8723b_set_FwPsTuneParam_cmd(काष्ठा adapter *padapter)
अणु
	u8 u1H2CPsTuneParm[H2C_PSTUNEPARAM_LEN] = अणु0पूर्ण;
	u8 bcn_to_limit = 10; /* 10 * 100 * awakeपूर्णांकerval (ms) */
	u8 dtim_समयout = 5; /* ms रुको broadcast data समयr */
	u8 ps_समयout = 20;  /* ms Keep awake when tx */
	u8 dtim_period = 3;

	SET_8723B_H2CCMD_PSTUNE_PARM_BCN_TO_LIMIT(u1H2CPsTuneParm, bcn_to_limit);
	SET_8723B_H2CCMD_PSTUNE_PARM_DTIM_TIMEOUT(u1H2CPsTuneParm, dtim_समयout);
	SET_8723B_H2CCMD_PSTUNE_PARM_PS_TIMEOUT(u1H2CPsTuneParm, ps_समयout);
	SET_8723B_H2CCMD_PSTUNE_PARM_ADOPT(u1H2CPsTuneParm, 1);
	SET_8723B_H2CCMD_PSTUNE_PARM_DTIM_PERIOD(u1H2CPsTuneParm, dtim_period);

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": u1H2CPsTuneParm:", DUMP_PREFIX_NONE,
			     16, 1, u1H2CPsTuneParm, H2C_PSTUNEPARAM_LEN, false);

	FillH2CCmd8723B(padapter, H2C_8723B_PS_TUNING_PARA, H2C_PSTUNEPARAM_LEN, u1H2CPsTuneParm);
पूर्ण

व्योम rtl8723b_set_FwPwrModeInIPS_cmd(काष्ठा adapter *padapter, u8 cmd_param)
अणु

	FillH2CCmd8723B(padapter, H2C_8723B_FWLPS_IN_IPS_, 1, &cmd_param);
पूर्ण

/*
 * Description: Fill the reserved packets that FW will use to RSVD page.
 * Now we just send 4 types packet to rsvd page.
 * (1)Beacon, (2)Ps-poll, (3)Null data, (4)ProbeRsp.
 *
 * Input:
 *
 * bDLFinished - false: At the first समय we will send all the packets as
 * a large packet to Hw, so we need to set the packet length to total length.
 *
 * true: At the second समय, we should send the first packet (शेष:beacon)
 * to Hw again and set the length in descriptor to the real beacon length.
 */
/* 2009.10.15 by tynli. */
अटल व्योम rtl8723b_set_FwRsvdPagePkt(
	काष्ठा adapter *padapter, bool bDLFinished
)
अणु
	काष्ठा xmit_frame *pcmdframe;
	काष्ठा pkt_attrib *pattrib;
	काष्ठा xmit_priv *pxmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u32 BeaconLength = 0, PSPollLength = 0;
	u32 NullDataLength = 0, QosNullLength = 0, BTQosNullLength = 0;
	u8 *ReservedPagePacket;
	u8 TxDescLen = TXDESC_SIZE, TxDescOffset = TXDESC_OFFSET;
	u8 TotalPageNum = 0, CurtPktPageNum = 0, RsvdPageNum = 0;
	u16 BufIndex, PageSize = 128;
	u32 TotalPacketLen, MaxRsvdPageBufSize = 0;

	काष्ठा rsvdpage_loc RsvdPageLoc;

	pxmitpriv = &padapter->xmitpriv;
	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	RsvdPageNum = BCNQ_PAGE_NUM_8723B + WOWLAN_PAGE_NUM_8723B;
	MaxRsvdPageBufSize = RsvdPageNum*PageSize;

	pcmdframe = rtw_alloc_cmdxmitframe(pxmitpriv);
	अगर (!pcmdframe)
		वापस;

	ReservedPagePacket = pcmdframe->buf_addr;
	स_रखो(&RsvdPageLoc, 0, माप(काष्ठा rsvdpage_loc));

	/* 3 (1) beacon */
	BufIndex = TxDescOffset;
	Conकाष्ठाBeacon(padapter, &ReservedPagePacket[BufIndex], &BeaconLength);

	/*  When we count the first page size, we need to reserve description size क्रम the RSVD */
	/*  packet, it will be filled in front of the packet in TXPKTBUF. */
	CurtPktPageNum = (u8)PageNum_128(TxDescLen + BeaconLength);
	/* If we करोn't add 1 more page, the WOWLAN function has a problem. Baron thinks it's a bug of firmware */
	अगर (CurtPktPageNum == 1)
		CurtPktPageNum += 1;

	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	/* 3 (2) ps-poll */
	RsvdPageLoc.LocPsPoll = TotalPageNum;
	Conकाष्ठाPSPoll(padapter, &ReservedPagePacket[BufIndex], &PSPollLength);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], PSPollLength, true, false, false);

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + PSPollLength);

	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	/* 3 (3) null data */
	RsvdPageLoc.LocNullData = TotalPageNum;
	Conकाष्ठाNullFunctionData(
		padapter,
		&ReservedPagePacket[BufIndex],
		&NullDataLength,
		get_my_bssid(&pmlmeinfo->network),
		false, 0, 0, false
	);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], NullDataLength, false, false, false);

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + NullDataLength);

	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	/* 3 (5) Qos null data */
	RsvdPageLoc.LocQosNull = TotalPageNum;
	Conकाष्ठाNullFunctionData(
		padapter,
		&ReservedPagePacket[BufIndex],
		&QosNullLength,
		get_my_bssid(&pmlmeinfo->network),
		true, 0, 0, false
	);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], QosNullLength, false, false, false);

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + QosNullLength);

	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	/* 3 (6) BT Qos null data */
	RsvdPageLoc.LocBTQosNull = TotalPageNum;
	Conकाष्ठाNullFunctionData(
		padapter,
		&ReservedPagePacket[BufIndex],
		&BTQosNullLength,
		get_my_bssid(&pmlmeinfo->network),
		true, 0, 0, false
	);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], BTQosNullLength, false, true, false);

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + BTQosNullLength);

	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	TotalPacketLen = BufIndex + BTQosNullLength;

	अगर (TotalPacketLen > MaxRsvdPageBufSize) अणु
		जाओ error;
	पूर्ण अन्यथा अणु
		/*  update attribute */
		pattrib = &pcmdframe->attrib;
		update_mgntframe_attrib(padapter, pattrib);
		pattrib->qsel = 0x10;
		pattrib->pktlen = pattrib->last_txcmdsz = TotalPacketLen - TxDescOffset;
		dump_mgntframe_and_रुको(padapter, pcmdframe, 100);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		rtl8723b_set_FwRsvdPage_cmd(padapter, &RsvdPageLoc);
		rtl8723b_set_FwAoacRsvdPage_cmd(padapter, &RsvdPageLoc);
	पूर्ण अन्यथा अणु
		rtl8723b_set_FwAoacRsvdPage_cmd(padapter, &RsvdPageLoc);
	पूर्ण
	वापस;

error:

	rtw_मुक्त_xmitframe(pxmitpriv, pcmdframe);
पूर्ण

व्योम rtl8723b_करोwnload_rsvd_page(काष्ठा adapter *padapter, u8 mstatus)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	bool bcn_valid = false;
	u8 DLBcnCount = 0;
	u32 poll = 0;
	u8 val8;

	अगर (mstatus == RT_MEDIA_CONNECT) अणु
		bool bRecover = false;
		u8 v8;

		/*  We should set AID, correct TSF, HW seq enable beक्रमe set JoinBssReport to Fw in 88/92C. */
		/*  Suggested by filen. Added by tynli. */
		rtw_ग_लिखो16(padapter, REG_BCN_PSR_RPT, (0xC000|pmlmeinfo->aid));

		/*  set REG_CR bit 8 */
		v8 = rtw_पढ़ो8(padapter, REG_CR+1);
		v8 |= BIT(0); /*  ENSWBCN */
		rtw_ग_लिखो8(padapter, REG_CR+1, v8);

		/*  Disable Hw protection क्रम a समय which revserd क्रम Hw sending beacon. */
		/*  Fix करोwnload reserved page packet fail that access collision with the protection समय. */
		/*  2010.05.11. Added by tynli. */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 &= ~EN_BCN_FUNCTION;
		val8 |= DIS_TSF_UDT;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

		/*  Set FWHW_TXQ_CTRL 0x422[6]= 0 to tell Hw the packet is not a real beacon frame. */
		अगर (pHalData->RegFwHwTxQCtrl & BIT(6))
			bRecover = true;

		/*  To tell Hw the packet is not a real beacon frame. */
		rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl & ~BIT(6));
		pHalData->RegFwHwTxQCtrl &= ~BIT(6);

		/*  Clear beacon valid check bit. */
		rtw_hal_set_hwreg(padapter, HW_VAR_BCN_VALID, शून्य);
		rtw_hal_set_hwreg(padapter, HW_VAR_DL_BCN_SEL, शून्य);

		DLBcnCount = 0;
		poll = 0;
		करो अणु
			/*  करोwnload rsvd page. */
			rtl8723b_set_FwRsvdPagePkt(padapter, 0);
			DLBcnCount++;
			करो अणु
				yield();
				/* mdelay(10); */
				/*  check rsvd page करोwnload OK. */
				rtw_hal_get_hwreg(padapter, HW_VAR_BCN_VALID, (u8 *)(&bcn_valid));
				poll++;
			पूर्ण जबतक (!bcn_valid && (poll%10) != 0 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

		पूर्ण जबतक (!bcn_valid && DLBcnCount <= 100 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

		अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped) अणु
		पूर्ण अन्यथा अणु
			काष्ठा pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);
			pwrctl->fw_psmode_अगरace_id = padapter->अगरace_id;
		पूर्ण

		/*  2010.05.11. Added by tynli. */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 |= EN_BCN_FUNCTION;
		val8 &= ~DIS_TSF_UDT;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

		/*  To make sure that अगर there exists an adapter which would like to send beacon. */
		/*  If exists, the origianl value of 0x422[6] will be 1, we should check this to */
		/*  prevent from setting 0x422[6] to 0 after करोwnload reserved page, or it will cause */
		/*  the beacon cannot be sent by HW. */
		/*  2010.06.23. Added by tynli. */
		अगर (bRecover) अणु
			rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl | BIT(6));
			pHalData->RegFwHwTxQCtrl |= BIT(6);
		पूर्ण

		/*  Clear CR[8] or beacon packet will not be send to TxBuf anymore. */
		v8 = rtw_पढ़ो8(padapter, REG_CR+1);
		v8 &= ~BIT(0); /*  ~ENSWBCN */
		rtw_ग_लिखो8(padapter, REG_CR+1, v8);
	पूर्ण
पूर्ण

व्योम rtl8723b_set_FwJoinBssRpt_cmd(काष्ठा adapter *padapter, u8 mstatus)
अणु
	अगर (mstatus == 1)
		rtl8723b_करोwnload_rsvd_page(padapter, RT_MEDIA_CONNECT);
पूर्ण

/* arg[0] = macid */
/* arg[1] = raid */
/* arg[2] = लघुGIrate */
/* arg[3] = init_rate */
व्योम rtl8723b_Add_RateATid(
	काष्ठा adapter *padapter,
	u32 biपंचांगap,
	u8 *arg,
	u8 rssi_level
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा sta_info *psta;
	u8 mac_id = arg[0];
	u8 raid = arg[1];
	u8 लघुGI = arg[2];
	u8 bw;
	u32 mask = biपंचांगap&0x0FFFFFFF;

	psta = pmlmeinfo->FW_sta_info[mac_id].psta;
	अगर (!psta)
		वापस;

	bw = psta->bw_mode;

	अगर (rssi_level != DM_RATR_STA_INIT)
		mask = ODM_Get_Rate_Biपंचांगap(&pHalData->odmpriv, mac_id, mask, rssi_level);

	rtl8723b_set_FwMacIdConfig_cmd(padapter, mac_id, raid, bw, लघुGI, mask);
पूर्ण

अटल व्योम Conकाष्ठाBtNullFunctionData(
	काष्ठा adapter *padapter,
	u8 *pframe,
	u32 *pLength,
	u8 *StaAddr,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bForcePowerSave
)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 pktlen;
	u8 bssid[ETH_ALEN];

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	अगर (!StaAddr) अणु
		स_नकल(bssid, myid(&padapter->eeprompriv), ETH_ALEN);
		StaAddr = bssid;
	पूर्ण

	fctrl = &pwlanhdr->frame_control;
	*fctrl = 0;
	अगर (bForcePowerSave)
		SetPwrMgt(fctrl);

	SetFrDs(fctrl);
	स_नकल(pwlanhdr->addr1, StaAddr, ETH_ALEN);
	स_नकल(pwlanhdr->addr2, myid(&padapter->eeprompriv), ETH_ALEN);
	स_नकल(pwlanhdr->addr3, myid(&padapter->eeprompriv), ETH_ALEN);

	SetDuration(pwlanhdr, 0);
	SetSeqNum(pwlanhdr, 0);

	अगर (bQoS) अणु
		काष्ठा ieee80211_qos_hdr *pwlanqoshdr;

		SetFrameSubType(pframe, WIFI_QOS_DATA_शून्य);

		pwlanqoshdr = (काष्ठा ieee80211_qos_hdr *)pframe;
		SetPriority(&pwlanqoshdr->qos_ctrl, AC);
		SetEOSP(&pwlanqoshdr->qos_ctrl, bEosp);

		pktlen = माप(काष्ठा ieee80211_qos_hdr);
	पूर्ण अन्यथा अणु
		SetFrameSubType(pframe, WIFI_DATA_शून्य);

		pktlen = माप(काष्ठा ieee80211_hdr_3addr);
	पूर्ण

	*pLength = pktlen;
पूर्ण

अटल व्योम SetFwRsvdPagePkt_BTCoex(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_frame *pcmdframe;
	काष्ठा pkt_attrib *pattrib;
	काष्ठा xmit_priv *pxmitpriv;
	u32 BeaconLength = 0;
	u32 BTQosNullLength = 0;
	u8 *ReservedPagePacket;
	u8 TxDescLen, TxDescOffset;
	u8 TotalPageNum = 0, CurtPktPageNum = 0, RsvdPageNum = 0;
	u16 BufIndex, PageSize;
	u32 TotalPacketLen, MaxRsvdPageBufSize = 0;
	काष्ठा rsvdpage_loc RsvdPageLoc;

	pxmitpriv = &padapter->xmitpriv;
	TxDescLen = TXDESC_SIZE;
	TxDescOffset = TXDESC_OFFSET;
	PageSize = PAGE_SIZE_TX_8723B;

	RsvdPageNum = BCNQ_PAGE_NUM_8723B;
	MaxRsvdPageBufSize = RsvdPageNum*PageSize;

	pcmdframe = rtw_alloc_cmdxmitframe(pxmitpriv);
	अगर (!pcmdframe)
		वापस;

	ReservedPagePacket = pcmdframe->buf_addr;
	स_रखो(&RsvdPageLoc, 0, माप(काष्ठा rsvdpage_loc));

	/* 3 (1) beacon */
	BufIndex = TxDescOffset;
	Conकाष्ठाBeacon(padapter, &ReservedPagePacket[BufIndex], &BeaconLength);

	/*  When we count the first page size, we need to reserve description size क्रम the RSVD */
	/*  packet, it will be filled in front of the packet in TXPKTBUF. */
	CurtPktPageNum = (u8)PageNum_128(TxDescLen + BeaconLength);
	/* If we करोn't add 1 more page, the WOWLAN function has a problem. Baron thinks it's a bug of firmware */
	अगर (CurtPktPageNum == 1)
		CurtPktPageNum += 1;
	TotalPageNum += CurtPktPageNum;

	BufIndex += (CurtPktPageNum*PageSize);

	/*  Jump to lastest page */
	अगर (BufIndex < (MaxRsvdPageBufSize - PageSize)) अणु
		BufIndex = TxDescOffset + (MaxRsvdPageBufSize - PageSize);
		TotalPageNum = BCNQ_PAGE_NUM_8723B - 1;
	पूर्ण

	/* 3 (6) BT Qos null data */
	RsvdPageLoc.LocBTQosNull = TotalPageNum;
	Conकाष्ठाBtNullFunctionData(
		padapter,
		&ReservedPagePacket[BufIndex],
		&BTQosNullLength,
		शून्य,
		true, 0, 0, false
	);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], BTQosNullLength, false, true, false);

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + BTQosNullLength);

	TotalPageNum += CurtPktPageNum;

	TotalPacketLen = BufIndex + BTQosNullLength;
	अगर (TotalPacketLen > MaxRsvdPageBufSize)
		जाओ error;

	/*  update attribute */
	pattrib = &pcmdframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->qsel = 0x10;
	pattrib->pktlen = pattrib->last_txcmdsz = TotalPacketLen - TxDescOffset;
	dump_mgntframe_and_रुको(padapter, pcmdframe, 100);

	rtl8723b_set_FwRsvdPage_cmd(padapter, &RsvdPageLoc);
	rtl8723b_set_FwAoacRsvdPage_cmd(padapter, &RsvdPageLoc);

	वापस;

error:
	rtw_मुक्त_xmitframe(pxmitpriv, pcmdframe);
पूर्ण

व्योम rtl8723b_करोwnload_BTCoex_AP_mode_rsvd_page(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;
	u8 bRecover = false;
	u8 bcn_valid = false;
	u8 DLBcnCount = 0;
	u32 poll = 0;
	u8 val8;

	pHalData = GET_HAL_DATA(padapter);
	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	/*  We should set AID, correct TSF, HW seq enable beक्रमe set JoinBssReport to Fw in 88/92C. */
	/*  Suggested by filen. Added by tynli. */
	rtw_ग_लिखो16(padapter, REG_BCN_PSR_RPT, (0xC000|pmlmeinfo->aid));

	/*  set REG_CR bit 8 */
	val8 = rtw_पढ़ो8(padapter, REG_CR+1);
	val8 |= BIT(0); /*  ENSWBCN */
	rtw_ग_लिखो8(padapter,  REG_CR+1, val8);

	/*  Disable Hw protection क्रम a समय which revserd क्रम Hw sending beacon. */
	/*  Fix करोwnload reserved page packet fail that access collision with the protection समय. */
	/*  2010.05.11. Added by tynli. */
	val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
	val8 &= ~EN_BCN_FUNCTION;
	val8 |= DIS_TSF_UDT;
	rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

	/*  Set FWHW_TXQ_CTRL 0x422[6]= 0 to tell Hw the packet is not a real beacon frame. */
	अगर (pHalData->RegFwHwTxQCtrl & BIT(6))
		bRecover = true;

	/*  To tell Hw the packet is not a real beacon frame. */
	pHalData->RegFwHwTxQCtrl &= ~BIT(6);
	rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl);

	/*  Clear beacon valid check bit. */
	rtw_hal_set_hwreg(padapter, HW_VAR_BCN_VALID, शून्य);
	rtw_hal_set_hwreg(padapter, HW_VAR_DL_BCN_SEL, शून्य);

	DLBcnCount = 0;
	poll = 0;
	करो अणु
		SetFwRsvdPagePkt_BTCoex(padapter);
		DLBcnCount++;
		करो अणु
			yield();
/* 			mdelay(10); */
			/*  check rsvd page करोwnload OK. */
			rtw_hal_get_hwreg(padapter, HW_VAR_BCN_VALID, &bcn_valid);
			poll++;
		पूर्ण जबतक (!bcn_valid && (poll%10) != 0 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);
	पूर्ण जबतक (!bcn_valid && (DLBcnCount <= 100) && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	अगर (bcn_valid) अणु
		काष्ठा pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);
		pwrctl->fw_psmode_अगरace_id = padapter->अगरace_id;
	पूर्ण

	/*  2010.05.11. Added by tynli. */
	val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
	val8 |= EN_BCN_FUNCTION;
	val8 &= ~DIS_TSF_UDT;
	rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

	/*  To make sure that अगर there exists an adapter which would like to send beacon. */
	/*  If exists, the origianl value of 0x422[6] will be 1, we should check this to */
	/*  prevent from setting 0x422[6] to 0 after करोwnload reserved page, or it will cause */
	/*  the beacon cannot be sent by HW. */
	/*  2010.06.23. Added by tynli. */
	अगर (bRecover) अणु
		pHalData->RegFwHwTxQCtrl |= BIT(6);
		rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl);
	पूर्ण

	/*  Clear CR[8] or beacon packet will not be send to TxBuf anymore. */
	val8 = rtw_पढ़ो8(padapter, REG_CR+1);
	val8 &= ~BIT(0); /*  ~ENSWBCN */
	rtw_ग_लिखो8(padapter, REG_CR+1, val8);
पूर्ण
