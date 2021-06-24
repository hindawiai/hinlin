<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_WLAN_UTIL_C_

#समावेश <linux/ieee80211.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wअगरi.h>

अटल स्थिर u8 ARTHEROS_OUI1[] = अणु0x00, 0x03, 0x7fपूर्ण;
अटल स्थिर u8 ARTHEROS_OUI2[] = अणु0x00, 0x13, 0x74पूर्ण;

अटल स्थिर u8 BROADCOM_OUI1[] = अणु0x00, 0x10, 0x18पूर्ण;
अटल स्थिर u8 BROADCOM_OUI2[] = अणु0x00, 0x0a, 0xf7पूर्ण;

अटल स्थिर u8 CISCO_OUI[] = अणु0x00, 0x40, 0x96पूर्ण;
अटल स्थिर u8 MARVELL_OUI[] = अणु0x00, 0x50, 0x43पूर्ण;
अटल स्थिर u8 RALINK_OUI[] = अणु0x00, 0x0c, 0x43पूर्ण;
अटल स्थिर u8 REALTEK_OUI[] = अणु0x00, 0xe0, 0x4cपूर्ण;
अटल स्थिर u8 AIRGOCAP_OUI[] = अणु0x00, 0x0a, 0xf5पूर्ण;
अटल स्थिर u8 EPIGRAM_OUI[] = अणु0x00, 0x90, 0x4cपूर्ण;

u8 REALTEK_96B_IE[] = अणु0x00, 0xe0, 0x4c, 0x02, 0x01, 0x20पूर्ण;

#घोषणा WAIT_FOR_BCN_TO_MIN	(6000)
#घोषणा WAIT_FOR_BCN_TO_MAX	(20000)

अटल स्थिर u8 rtw_basic_rate_cck[4] = अणु
	IEEE80211_CCK_RATE_1MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_2MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_5MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_11MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

अटल स्थिर u8 rtw_basic_rate_ofdm[3] = अणु
	IEEE80211_OFDM_RATE_6MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_12MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_24MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

अटल स्थिर u8 rtw_basic_rate_mix[7] = अणु
	IEEE80211_CCK_RATE_1MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_2MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_5MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_11MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_6MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_12MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_24MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

अचिन्हित अक्षर networktype_to_raid(अचिन्हित अक्षर network_type)
अणु
	चयन (network_type) अणु
	हाल WIRELESS_11B:
		वापस RATR_INX_WIRELESS_B;
	हाल WIRELESS_11A:
	हाल WIRELESS_11G:
		वापस RATR_INX_WIRELESS_G;
	हाल WIRELESS_11BG:
		वापस RATR_INX_WIRELESS_GB;
	हाल WIRELESS_11_24N:
	हाल WIRELESS_11_5N:
		वापस RATR_INX_WIRELESS_N;
	हाल WIRELESS_11A_5N:
	हाल WIRELESS_11G_24N:
		वापस  RATR_INX_WIRELESS_NG;
	हाल WIRELESS_11BG_24N:
		वापस RATR_INX_WIRELESS_NGB;
	शेष:
		वापस RATR_INX_WIRELESS_GB;
	पूर्ण
पूर्ण

u8 judge_network_type(काष्ठा adapter *padapter, अचिन्हित अक्षर *rate)
अणु
	u8 network_type = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pmlmeinfo->HT_enable)
		network_type = WIRELESS_11_24N;

	अगर (rtw_is_cckratesonly_included(rate))
		network_type |= WIRELESS_11B;
	अन्यथा अगर (rtw_is_cckrates_included(rate))
		network_type |= WIRELESS_11BG;
	अन्यथा
		network_type |= WIRELESS_11G;

	वापस network_type;
पूर्ण

अटल अचिन्हित अक्षर ratetbl_val_2wअगरirate(अचिन्हित अक्षर rate)
अणु
	चयन (rate & 0x7f) अणु
	हाल 0:
		वापस IEEE80211_CCK_RATE_1MB;
	हाल 1:
		वापस IEEE80211_CCK_RATE_2MB;
	हाल 2:
		वापस IEEE80211_CCK_RATE_5MB;
	हाल 3:
		वापस IEEE80211_CCK_RATE_11MB;
	हाल 4:
		वापस IEEE80211_OFDM_RATE_6MB;
	हाल 5:
		वापस IEEE80211_OFDM_RATE_9MB;
	हाल 6:
		वापस IEEE80211_OFDM_RATE_12MB;
	हाल 7:
		वापस IEEE80211_OFDM_RATE_18MB;
	हाल 8:
		वापस IEEE80211_OFDM_RATE_24MB;
	हाल 9:
		वापस IEEE80211_OFDM_RATE_36MB;
	हाल 10:
		वापस IEEE80211_OFDM_RATE_48MB;
	हाल 11:
		वापस IEEE80211_OFDM_RATE_54MB;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool is_basicrate(काष्ठा adapter *padapter, अचिन्हित अक्षर rate)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर val;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	क्रम (i = 0; i < NumRates; i++) अणु
		val = pmlmeext->basicrate[i];

		अगर ((val != 0xff) && (val != 0xfe)) अणु
			अगर (rate == ratetbl_val_2wअगरirate(val))
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक ratetbl2rateset(काष्ठा adapter *padapter, अचिन्हित अक्षर *rateset)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर rate;
	अचिन्हित पूर्णांक len = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	क्रम (i = 0; i < NumRates; i++) अणु
		rate = pmlmeext->datarate[i];

		चयन (rate) अणु
		हाल 0xff:
			वापस len;
		हाल 0xfe:
			जारी;
		शेष:
			rate = ratetbl_val_2wअगरirate(rate);

			अगर (is_basicrate(padapter, rate))
				rate |= IEEE80211_BASIC_RATE_MASK;

			rateset[len] = rate;
			len++;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण

व्योम get_rate_set(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbssrate, पूर्णांक *bssrate_len)
अणु
	अचिन्हित अक्षर supportedrates[NumRates];

	स_रखो(supportedrates, 0, NumRates);
	*bssrate_len = ratetbl2rateset(padapter, supportedrates);
	स_नकल(pbssrate, supportedrates, *bssrate_len);
पूर्ण

व्योम UpdateBrateTbl(काष्ठा adapter *Adapter, u8 *mbrate)
अणु
	u8 i;
	u8 rate;

	/*  1M, 2M, 5.5M, 11M, 6M, 12M, 24M are mandatory. */
	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		rate = mbrate[i] & 0x7f;
		चयन (rate) अणु
		हाल IEEE80211_CCK_RATE_1MB:
		हाल IEEE80211_CCK_RATE_2MB:
		हाल IEEE80211_CCK_RATE_5MB:
		हाल IEEE80211_CCK_RATE_11MB:
		हाल IEEE80211_OFDM_RATE_6MB:
		हाल IEEE80211_OFDM_RATE_12MB:
		हाल IEEE80211_OFDM_RATE_24MB:
			mbrate[i] |= IEEE80211_BASIC_RATE_MASK;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम UpdateBrateTblForSoftAP(u8 *bssrateset, u32 bssratelen)
अणु
	u8 i;
	u8 rate;

	क्रम (i = 0; i < bssratelen; i++) अणु
		rate = bssrateset[i] & 0x7f;
		चयन (rate) अणु
		हाल IEEE80211_CCK_RATE_1MB:
		हाल IEEE80211_CCK_RATE_2MB:
		हाल IEEE80211_CCK_RATE_5MB:
		हाल IEEE80211_CCK_RATE_11MB:
			bssrateset[i] |= IEEE80211_BASIC_RATE_MASK;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम Save_DM_Func_Flag(काष्ठा adapter *padapter)
अणु
	u8 saveflag = true;

	rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_OP, (u8 *)(&saveflag));
पूर्ण

व्योम Restore_DM_Func_Flag(काष्ठा adapter *padapter)
अणु
	u8 saveflag = false;

	rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_OP, (u8 *)(&saveflag));
पूर्ण

व्योम Switch_DM_Func(काष्ठा adapter *padapter, u32 mode, u8 enable)
अणु
	अगर (enable)
		rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_SET, (u8 *)(&mode));
	अन्यथा
		rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_CLR, (u8 *)(&mode));
पूर्ण

व्योम Set_MSR(काष्ठा adapter *padapter, u8 type)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_MEDIA_STATUS, (u8 *)(&type));
पूर्ण

अंतरभूत u8 rtw_get_oper_ch(काष्ठा adapter *adapter)
अणु
	वापस adapter->mlmeextpriv.oper_channel;
पूर्ण

अंतरभूत व्योम rtw_set_oper_ch(काष्ठा adapter *adapter, u8 ch)
अणु
	adapter->mlmeextpriv.oper_channel = ch;
पूर्ण

अंतरभूत व्योम rtw_set_oper_bw(काष्ठा adapter *adapter, u8 bw)
अणु
	adapter->mlmeextpriv.oper_bwmode = bw;
पूर्ण

अंतरभूत व्योम rtw_set_oper_choffset(काष्ठा adapter *adapter, u8 offset)
अणु
	adapter->mlmeextpriv.oper_ch_offset = offset;
पूर्ण

व्योम SelectChannel(काष्ठा adapter *padapter, अचिन्हित अक्षर channel)
अणु
	/* saved channel info */
	rtw_set_oper_ch(padapter, channel);
	rtw_hal_set_chan(padapter, channel);
पूर्ण

व्योम SetBWMode(काष्ठा adapter *padapter, अचिन्हित लघु bwmode,
	       अचिन्हित अक्षर channel_offset)
अणु
	/* saved bw info */
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_bwmode(padapter, (क्रमागत ht_channel_width)bwmode, channel_offset);
पूर्ण

व्योम set_channel_bwmode(काष्ठा adapter *padapter, अचिन्हित अक्षर channel, अचिन्हित अक्षर channel_offset, अचिन्हित लघु bwmode)
अणु
	u8 center_ch;

	अगर ((bwmode == HT_CHANNEL_WIDTH_20) ||
	    (channel_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)) अणु
		/* SelectChannel(padapter, channel); */
		center_ch = channel;
	पूर्ण अन्यथा अणु
		/* चयन to the proper channel */
		अगर (channel_offset == HAL_PRIME_CHNL_OFFSET_LOWER) अणु
			/* SelectChannel(padapter, channel + 2); */
			center_ch = channel + 2;
		पूर्ण अन्यथा अणु
			/* SelectChannel(padapter, channel - 2); */
			center_ch = channel - 2;
		पूर्ण
	पूर्ण

	/* set Channel */
	/* saved channel/bw info */
	rtw_set_oper_ch(padapter, channel);
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_chan(padapter, center_ch); /*  set center channel */
	SetBWMode(padapter, bwmode, channel_offset);
पूर्ण

u16 get_beacon_पूर्णांकerval(काष्ठा wlan_bssid_ex *bss)
अणु
	__le16 val;

	स_नकल((अचिन्हित अक्षर *)&val, rtw_get_beacon_पूर्णांकerval_from_ie(bss->ies), 2);

	वापस le16_to_cpu(val);
पूर्ण

पूर्णांक is_client_associated_to_ap(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;

	अगर (!padapter)
		वापस _FAIL;

	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	अगर ((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) &&
	    (pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE)
		वापस true;
	अन्यथा
		वापस _FAIL;
पूर्ण

पूर्णांक is_client_associated_to_ibss(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर ((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) &&
	    (pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE)
		वापस true;
	अन्यथा
		वापस _FAIL;
पूर्ण

पूर्णांक is_IBSS_empty(काष्ठा adapter *padapter)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	क्रम (i = IBSS_START_MAC_ID; i < NUM_STA; i++) अणु
		अगर (pmlmeinfo->FW_sta_info[i].status == 1)
			वापस _FAIL;
	पूर्ण
	वापस true;
पूर्ण

अचिन्हित पूर्णांक decide_रुको_क्रम_beacon_समयout(अचिन्हित पूर्णांक bcn_पूर्णांकerval)
अणु
	अगर ((bcn_पूर्णांकerval << 2) < WAIT_FOR_BCN_TO_MIN)
		वापस WAIT_FOR_BCN_TO_MIN;
	अन्यथा अगर ((bcn_पूर्णांकerval << 2) > WAIT_FOR_BCN_TO_MAX)
		वापस WAIT_FOR_BCN_TO_MAX;
	अन्यथा
		वापस bcn_पूर्णांकerval << 2;
पूर्ण

व्योम invalidate_cam_all(काष्ठा adapter *padapter)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, शून्य);
पूर्ण

व्योम ग_लिखो_cam(काष्ठा adapter *padapter, u8 entry, u16 ctrl, u8 *mac, u8 *key)
अणु
	अचिन्हित पूर्णांक i, val, addr;
	पूर्णांक j;
	u32 cam_val[2];

	addr = entry << 3;

	क्रम (j = 5; j >= 0; j--) अणु
		चयन (j) अणु
		हाल 0:
			val = ctrl | (mac[0] << 16) | (mac[1] << 24);
			अवरोध;
		हाल 1:
			val = mac[2] | (mac[3] << 8) | (mac[4] << 16) | (mac[5] << 24);
			अवरोध;
		शेष:
			i = (j - 2) << 2;
			val = key[i] | (key[i + 1] << 8) | (key[i + 2] << 16) |
			      (key[i + 3] << 24);
			अवरोध;
		पूर्ण

		cam_val[0] = val;
		cam_val[1] = addr + (अचिन्हित पूर्णांक)j;

		rtw_hal_set_hwreg(padapter, HW_VAR_CAM_WRITE, (u8 *)cam_val);
	पूर्ण
पूर्ण

व्योम clear_cam_entry(काष्ठा adapter *padapter, u8 entry)
अणु
	u8 null_sta[ETH_ALEN] = अणुपूर्ण;
	u8 null_key[16] = अणुपूर्ण;

	ग_लिखो_cam(padapter, entry, 0, null_sta, null_key);
पूर्ण

पूर्णांक allocate_fw_sta_entry(काष्ठा adapter *padapter)
अणु
	अचिन्हित पूर्णांक mac_id;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	क्रम (mac_id = IBSS_START_MAC_ID; mac_id < NUM_STA; mac_id++) अणु
		अगर (pmlmeinfo->FW_sta_info[mac_id].status == 0) अणु
			pmlmeinfo->FW_sta_info[mac_id].status = 1;
			pmlmeinfo->FW_sta_info[mac_id].retry = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mac_id;
पूर्ण

व्योम flush_all_cam_entry(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, शून्य);

	स_रखो((u8 *)(pmlmeinfo->FW_sta_info), 0, माप(pmlmeinfo->FW_sta_info));
पूर्ण

पूर्णांक WMM_param_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pmlmepriv->qospriv.qos_option == 0) अणु
		pmlmeinfo->WMM_enable = 0;
		वापस _FAIL;
	पूर्ण

	pmlmeinfo->WMM_enable = 1;
	स_नकल(&pmlmeinfo->WMM_param, pIE->data + 6, माप(काष्ठा WMM_para_element));
	वापस true;
पूर्ण

व्योम WMMOnAssocRsp(काष्ठा adapter *padapter)
अणु
	u8 ACI, ACM, AIFS, ECWMin, ECWMax, aSअगरsTime;
	u8 acm_mask;
	u16 TXOP;
	u32 acParm, i;
	u32 edca[4], inx[4];
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;

	अगर (pmlmeinfo->WMM_enable == 0) अणु
		padapter->mlmepriv.acm_mask = 0;
		वापस;
	पूर्ण

	acm_mask = 0;

	अगर (pmlmeext->cur_wireless_mode == WIRELESS_11B)
		aSअगरsTime = 10;
	अन्यथा
		aSअगरsTime = 16;

	क्रम (i = 0; i < 4; i++) अणु
		ACI = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 5) & 0x03;
		ACM = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 4) & 0x01;

		/* AIFS = AIFSN * slot समय + SIFS - r2t phy delay */
		AIFS = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN & 0x0f) * pmlmeinfo->slotTime + aSअगरsTime;

		ECWMin = pmlmeinfo->WMM_param.ac_param[i].CW & 0x0f;
		ECWMax = (pmlmeinfo->WMM_param.ac_param[i].CW & 0xf0) >> 4;
		TXOP = le16_to_cpu(pmlmeinfo->WMM_param.ac_param[i].TXOP_limit);

		acParm = AIFS | (ECWMin << 8) | (ECWMax << 12) | (TXOP << 16);

		चयन (ACI) अणु
		हाल 0x0:
			rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acParm));
			acm_mask |= (ACM ? BIT(1) : 0);
			edca[XMIT_BE_QUEUE] = acParm;
			अवरोध;
		हाल 0x1:
			rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acParm));
			edca[XMIT_BK_QUEUE] = acParm;
			अवरोध;
		हाल 0x2:
			rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acParm));
			acm_mask |= (ACM ? BIT(2) : 0);
			edca[XMIT_VI_QUEUE] = acParm;
			अवरोध;
		हाल 0x3:
			rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acParm));
			acm_mask |= (ACM ? BIT(3) : 0);
			edca[XMIT_VO_QUEUE] = acParm;
			अवरोध;
		पूर्ण

		DBG_88E("WMM(%x): %x, %x\n", ACI, ACM, acParm);
	पूर्ण

	अगर (padapter->registrypriv.acm_method == 1)
		rtw_hal_set_hwreg(padapter, HW_VAR_ACM_CTRL, (u8 *)(&acm_mask));
	अन्यथा
		padapter->mlmepriv.acm_mask = acm_mask;

	inx[0] = 0; inx[1] = 1; inx[2] = 2; inx[3] = 3;

	अगर (pregpriv->wअगरi_spec == 1) अणु
		u32 j, change_inx = false;

		/* entry indx: 0->vo, 1->vi, 2->be, 3->bk. */
		क्रम (i = 0; i < 4; i++) अणु
			क्रम (j = i + 1; j < 4; j++) अणु
				/* compare CW and AIFS */
				अगर ((edca[j] & 0xFFFF) < (edca[i] & 0xFFFF)) अणु
					change_inx = true;
				पूर्ण अन्यथा अगर ((edca[j] & 0xFFFF) == (edca[i] & 0xFFFF)) अणु
					/* compare TXOP */
					अगर ((edca[j] >> 16) > (edca[i] >> 16))
						change_inx = true;
				पूर्ण

				अगर (change_inx) अणु
					swap(edca[i], edca[j]);
					swap(inx[i], inx[j]);
					change_inx = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		pxmitpriv->wmm_para_seq[i] = inx[i];
		DBG_88E("wmm_para_seq(%d): %d\n", i, pxmitpriv->wmm_para_seq[i]);
	पूर्ण
पूर्ण

अटल व्योम bwmode_update_check(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE)
अणु
	अचिन्हित अक्षर new_bwmode;
	अचिन्हित अक्षर new_ch_offset;
	काष्ठा HT_info_element *pHT_info;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	अगर (!pIE)
		वापस;

	अगर (!phtpriv)
		वापस;

	अगर (pIE->Length > माप(काष्ठा HT_info_element))
		वापस;

	pHT_info = (काष्ठा HT_info_element *)pIE->data;

	अगर ((pHT_info->infos[0] & BIT(2)) && pregistrypriv->cbw40_enable) अणु
		new_bwmode = HT_CHANNEL_WIDTH_40;

		चयन (pHT_info->infos[0] & 0x3) अणु
		हाल 1:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
			अवरोध;
		हाल 3:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
			अवरोध;
		शेष:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_bwmode = HT_CHANNEL_WIDTH_20;
		new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	पूर्ण

	अगर ((new_bwmode != pmlmeext->cur_bwmode) ||
	    (new_ch_offset != pmlmeext->cur_ch_offset)) अणु
		pmlmeinfo->bwmode_updated = true;

		pmlmeext->cur_bwmode = new_bwmode;
		pmlmeext->cur_ch_offset = new_ch_offset;

		/* update HT info also */
		HT_info_handler(padapter, pIE);
	पूर्ण अन्यथा अणु
		pmlmeinfo->bwmode_updated = false;
	पूर्ण

	अगर (pmlmeinfo->bwmode_updated) अणु
		काष्ठा sta_info *psta;
		काष्ठा wlan_bssid_ex	*cur_network = &pmlmeinfo->network;
		काष्ठा sta_priv	*pstapriv = &padapter->stapriv;

		/* update ap's stainfo */
		psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
		अगर (psta) अणु
			काष्ठा ht_priv	*phtpriv_sta = &psta->htpriv;

			अगर (phtpriv_sta->ht_option) अणु
				/*  bwmode */
				phtpriv_sta->bwmode = pmlmeext->cur_bwmode;
				phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;
			पूर्ण अन्यथा अणु
				phtpriv_sta->bwmode = HT_CHANNEL_WIDTH_20;
				phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम HT_caps_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE)
अणु
	अचिन्हित पूर्णांक i;
	u8 max_ampdu_len, min_mpdu_spacing;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	u8 *HT_cap = (u8 *)(&pmlmeinfo->HT_caps);

	अगर (!pIE)
		वापस;

	अगर (!phtpriv->ht_option)
		वापस;

	pmlmeinfo->HT_caps_enable = 1;

	क्रम (i = 0; i < (pIE->Length); i++) अणु
		अगर (i != 2) अणु
			/*	Got the endian issue here. */
			HT_cap[i] &= (pIE->data[i]);
		पूर्ण अन्यथा अणु
			/* modअगरy from  fw by Thomas 2010/11/17 */
			अगर ((pmlmeinfo->HT_caps.ampdu_params_info & 0x3) > (pIE->data[i] & 0x3))
				max_ampdu_len = pIE->data[i] & 0x3;
			अन्यथा
				max_ampdu_len = pmlmeinfo->HT_caps.ampdu_params_info & 0x3;

			अगर ((pmlmeinfo->HT_caps.ampdu_params_info & 0x1c) > (pIE->data[i] & 0x1c))
				min_mpdu_spacing = pmlmeinfo->HT_caps.ampdu_params_info & 0x1c;
			अन्यथा
				min_mpdu_spacing = pIE->data[i] & 0x1c;

			pmlmeinfo->HT_caps.ampdu_params_info = max_ampdu_len | min_mpdu_spacing;
		पूर्ण
	पूर्ण

	/* update the MCS rates */
	क्रम (i = 0; i < 16; i++)
		((u8 *)&pmlmeinfo->HT_caps.mcs)[i] &= MCS_rate_1R[i];
पूर्ण

व्योम HT_info_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	अगर (!pIE)
		वापस;

	अगर (!phtpriv->ht_option)
		वापस;

	अगर (pIE->Length > माप(काष्ठा HT_info_element))
		वापस;

	pmlmeinfo->HT_info_enable = 1;
	स_नकल(&pmlmeinfo->HT_info, pIE->data, pIE->Length);
पूर्ण

व्योम HTOnAssocRsp(काष्ठा adapter *padapter)
अणु
	u8 max_ampdu_len;
	u8 min_mpdu_spacing;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	DBG_88E("%s\n", __func__);

	अगर ((pmlmeinfo->HT_info_enable) && (pmlmeinfo->HT_caps_enable)) अणु
		pmlmeinfo->HT_enable = 1;
	पूर्ण अन्यथा अणु
		pmlmeinfo->HT_enable = 0;
		वापस;
	पूर्ण

	/* handle A-MPDU parameter field
	 *
	 * AMPDU_para [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
	 * AMPDU_para [4:2]:Min MPDU Start Spacing
	 */
	max_ampdu_len = pmlmeinfo->HT_caps.ampdu_params_info & 0x03;
	min_mpdu_spacing = (pmlmeinfo->HT_caps.ampdu_params_info & 0x1c) >> 2;

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_MIN_SPACE, &min_mpdu_spacing);
	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_FACTOR, &max_ampdu_len);
पूर्ण

व्योम ERP_IE_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pIE->Length > 1)
		वापस;

	pmlmeinfo->ERP_enable = 1;
	स_नकल(&pmlmeinfo->ERP_IE, pIE->data, pIE->Length);
पूर्ण

व्योम VCS_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	चयन (pregpriv->vrtl_carrier_sense) अणु /* 0:off 1:on 2:स्वतः */
	हाल 0: /* off */
		psta->rtsen = 0;
		psta->cts2self = 0;
		अवरोध;
	हाल 1: /* on */
		अगर (pregpriv->vcs_type == 1) अणु /* 1:RTS/CTS 2:CTS to self */
			psta->rtsen = 1;
			psta->cts2self = 0;
		पूर्ण अन्यथा अणु
			psta->rtsen = 0;
			psta->cts2self = 1;
		पूर्ण
		अवरोध;
	हाल 2: /* स्वतः */
	शेष:
		अगर ((pmlmeinfo->ERP_enable) && (pmlmeinfo->ERP_IE & BIT(1))) अणु
			अगर (pregpriv->vcs_type == 1) अणु
				psta->rtsen = 1;
				psta->cts2self = 0;
			पूर्ण अन्यथा अणु
				psta->rtsen = 0;
				psta->cts2self = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			psta->rtsen = 0;
			psta->cts2self = 0;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक rtw_check_bcn_info(काष्ठा adapter  *Adapter, u8 *pframe, u32 packet_len)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित अक्षर *p;
	अचिन्हित लघु val16, subtype;
	काष्ठा wlan_network *cur_network = &Adapter->mlmepriv.cur_network;
	u16 wpa_len = 0, rsn_len = 0;
	u8 encryp_protocol = 0;
	काष्ठा wlan_bssid_ex *bssid;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0, is_8021x = 0;
	अचिन्हित अक्षर *pbuf;
	u32 wpa_ielen = 0;
	u8 *pbssid = GetAddr3Ptr(pframe);
	काष्ठा HT_info_element *pht_info = शून्य;
	u32 bcn_channel;
	अचिन्हित लघु ht_cap_info;
	अचिन्हित अक्षर ht_info_infos_0;
	पूर्णांक ssid_len;

	अगर (!is_client_associated_to_ap(Adapter))
		वापस true;

	len = packet_len - माप(काष्ठा ieee80211_hdr_3addr);

	अगर (len > MAX_IE_SZ) अणु
		DBG_88E("%s IE too long for survey event\n", __func__);
		वापस _FAIL;
	पूर्ण

	अगर (स_भेद(cur_network->network.MacAddress, pbssid, 6)) अणु
		DBG_88E("Oops: rtw_check_network_encrypt linked but recv other bssid bcn\n%pM %pM\n",
			(pbssid), (cur_network->network.MacAddress));
		वापस true;
	पूर्ण

	bssid = kzalloc(माप(काष्ठा wlan_bssid_ex), GFP_ATOMIC);
	अगर (!bssid)
		वापस _FAIL;

	subtype = GetFrameSubType(pframe) >> 4;

	अगर (subtype == WIFI_BEACON)
		bssid->Reserved[0] = 1;

	bssid->Length = माप(काष्ठा wlan_bssid_ex) - MAX_IE_SZ + len;

	/* below is to copy the inक्रमmation element */
	bssid->ie_length = len;
	स_नकल(bssid->ies, (pframe + माप(काष्ठा ieee80211_hdr_3addr)), bssid->ie_length);

	/* check bw and channel offset */
	/* parsing HT_CAP_IE */
	p = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_CAPABILITY, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
		काष्ठा ieee80211_ht_cap *ht_cap =
			(काष्ठा ieee80211_ht_cap *)(p + 2);

		ht_cap_info = le16_to_cpu(ht_cap->cap_info);
	पूर्ण अन्यथा अणु
		ht_cap_info = 0;
	पूर्ण
	/* parsing HT_INFO_IE */
	p = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_OPERATION, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
		pht_info = (काष्ठा HT_info_element *)(p + 2);
		ht_info_infos_0 = pht_info->infos[0];
	पूर्ण अन्यथा अणु
		ht_info_infos_0 = 0;
	पूर्ण
	अगर (ht_cap_info != cur_network->BcnInfo.ht_cap_info ||
	    ((ht_info_infos_0 & 0x03) != (cur_network->BcnInfo.ht_info_infos_0 & 0x03))) अणु
		DBG_88E("%s bcn now: ht_cap_info:%x ht_info_infos_0:%x\n", __func__,
			ht_cap_info, ht_info_infos_0);
		DBG_88E("%s bcn link: ht_cap_info:%x ht_info_infos_0:%x\n", __func__,
			cur_network->BcnInfo.ht_cap_info, cur_network->BcnInfo.ht_info_infos_0);
		DBG_88E("%s bw mode change, disconnect\n", __func__);
		/* bcn_info_update */
		cur_network->BcnInfo.ht_cap_info = ht_cap_info;
		cur_network->BcnInfo.ht_info_infos_0 = ht_info_infos_0;
		/* to करो : need to check that whether modअगरy related रेजिस्टर of BB or not */
		/* जाओ _mismatch; */
	पूर्ण

	/* Checking क्रम channel */
	p = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_DS_PARAMS, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
	अगर (p) अणु
		bcn_channel = *(p + 2);
	पूर्ण अन्यथा अणु/* In 5G, some ap करो not have DSSET IE checking HT info क्रम channel */
		p = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_OPERATION, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
		अगर (pht_info) अणु
			bcn_channel = pht_info->primary_channel;
		पूर्ण अन्यथा अणु /* we करोn't find channel IE, so don't check it */
			DBG_88E("Oops: %s we don't find channel IE, so don't check it\n", __func__);
			bcn_channel = Adapter->mlmeextpriv.cur_channel;
		पूर्ण
	पूर्ण
	अगर (bcn_channel != Adapter->mlmeextpriv.cur_channel) अणु
		DBG_88E("%s beacon channel:%d cur channel:%d disconnect\n", __func__,
			bcn_channel, Adapter->mlmeextpriv.cur_channel);
		जाओ _mismatch;
	पूर्ण

	/* checking SSID */
	ssid_len = 0;
	p = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_SSID, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
	अगर (p) अणु
		ssid_len = *(p + 1);
		अगर (ssid_len > NDIS_802_11_LENGTH_SSID)
			ssid_len = 0;
	पूर्ण
	स_नकल(bssid->ssid.ssid, (p + 2), ssid_len);
	bssid->ssid.ssid_length = ssid_len;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s bssid.ssid.ssid:%s bssid.ssid.ssid_length:%d "
				"cur_network->network.ssid.ssid:%s len:%d\n", __func__, bssid->ssid.ssid,
				bssid->ssid.ssid_length, cur_network->network.ssid.ssid,
				cur_network->network.ssid.ssid_length));

	अगर (स_भेद(bssid->ssid.ssid, cur_network->network.ssid.ssid, 32) ||
	    bssid->ssid.ssid_length != cur_network->network.ssid.ssid_length) अणु
		अगर (bssid->ssid.ssid[0] != '\0' && bssid->ssid.ssid_length != 0) अणु /* not hidden ssid */
			DBG_88E("%s(), SSID is not match return FAIL\n", __func__);
			जाओ _mismatch;
		पूर्ण
	पूर्ण

	/* check encryption info */
	val16 = rtw_get_capability(bssid);

	अगर (val16 & BIT(4))
		bssid->Privacy = 1;
	अन्यथा
		bssid->Privacy = 0;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("%s(): cur_network->network.Privacy is %d, bssid.Privacy is %d\n",
		 __func__, cur_network->network.Privacy, bssid->Privacy));
	अगर (cur_network->network.Privacy != bssid->Privacy) अणु
		DBG_88E("%s(), privacy is not match return FAIL\n", __func__);
		जाओ _mismatch;
	पूर्ण

	rtw_get_sec_ie(bssid->ies, bssid->ie_length, शून्य, &rsn_len, शून्य, &wpa_len);

	अगर (rsn_len > 0) अणु
		encryp_protocol = ENCRYP_PROTOCOL_WPA2;
	पूर्ण अन्यथा अगर (wpa_len > 0) अणु
		encryp_protocol = ENCRYP_PROTOCOL_WPA;
	पूर्ण अन्यथा अणु
		अगर (bssid->Privacy)
			encryp_protocol = ENCRYP_PROTOCOL_WEP;
	पूर्ण

	अगर (cur_network->BcnInfo.encryp_protocol != encryp_protocol) अणु
		DBG_88E("%s(): encryption protocol is not match , return FAIL\n", __func__);
		जाओ _mismatch;
	पूर्ण

	अगर (encryp_protocol == ENCRYP_PROTOCOL_WPA || encryp_protocol == ENCRYP_PROTOCOL_WPA2) अणु
		pbuf = rtw_get_wpa_ie(&bssid->ies[12], &wpa_ielen,
				      bssid->ie_length - 12);
		अगर (pbuf && (wpa_ielen > 0)) अणु
			अगर (rtw_parse_wpa_ie(pbuf, wpa_ielen + 2, &group_cipher, &pairwise_cipher, &is_8021x) == _SUCCESS) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
					 ("%s pnetwork->pairwise_cipher: %d, group_cipher is %d, is_8021x is %d\n", __func__,
					 pairwise_cipher, group_cipher, is_8021x));
			पूर्ण
		पूर्ण अन्यथा अणु
			pbuf = rtw_get_wpa2_ie(&bssid->ies[12], &wpa_ielen,
					       bssid->ie_length - 12);

			अगर (pbuf && (wpa_ielen > 0)) अणु
				अगर (rtw_parse_wpa2_ie(pbuf, wpa_ielen + 2, &group_cipher, &pairwise_cipher, &is_8021x) == _SUCCESS) अणु
					RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
						 ("%s pnetwork->pairwise_cipher: %d, pnetwork->group_cipher is %d, is_802x is %d\n",
						  __func__, pairwise_cipher, group_cipher, is_8021x));
				पूर्ण
			पूर्ण
		पूर्ण

		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("%s cur_network->group_cipher is %d: %d\n", __func__, cur_network->BcnInfo.group_cipher, group_cipher));
		अगर (pairwise_cipher != cur_network->BcnInfo.pairwise_cipher || group_cipher != cur_network->BcnInfo.group_cipher) अणु
			DBG_88E("%s pairwise_cipher(%x:%x) or group_cipher(%x:%x) is not match , return FAIL\n", __func__,
				pairwise_cipher, cur_network->BcnInfo.pairwise_cipher,
				group_cipher, cur_network->BcnInfo.group_cipher);
			जाओ _mismatch;
		पूर्ण

		अगर (is_8021x != cur_network->BcnInfo.is_8021x) अणु
			DBG_88E("%s authentication is not match , return FAIL\n", __func__);
			जाओ _mismatch;
		पूर्ण
	पूर्ण

	kमुक्त(bssid);
	वापस _SUCCESS;

_mismatch:
	kमुक्त(bssid);
	वापस _FAIL;
पूर्ण

व्योम update_beacon_info(काष्ठा adapter *padapter, u8 *pframe, uपूर्णांक pkt_len, काष्ठा sta_info *psta)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len;
	काष्ठा ndis_802_11_var_ie *pIE;

	len = pkt_len - (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN);

	क्रम (i = 0; i < len;) अणु
		pIE = (काष्ठा ndis_802_11_var_ie *)(pframe + (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN) + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_HT_OPERATION:	/* HT info */
			bwmode_update_check(padapter, pIE);
			अवरोध;
		हाल WLAN_EID_ERP_INFO:
			ERP_IE_handler(padapter, pIE);
			VCS_update(padapter, psta);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक is_ap_in_tkip(काष्ठा adapter *padapter)
अणु
	u32 i;
	काष्ठा ndis_802_11_var_ie *pIE;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;

	अगर (rtw_get_capability(cur_network) & WLAN_CAPABILITY_PRIVACY) अणु
		क्रम (i = माप(काष्ठा ndis_802_11_fixed_ie); i < pmlmeinfo->network.ie_length;) अणु
			pIE = (काष्ठा ndis_802_11_var_ie *)(pmlmeinfo->network.ies + i);

			चयन (pIE->ElementID) अणु
			हाल WLAN_EID_VENDOR_SPECIFIC:
				अगर ((!स_भेद(pIE->data, RTW_WPA_OUI, 4)) && (!स_भेद((pIE->data + 12), WPA_TKIP_CIPHER, 4)))
					वापस true;
				अवरोध;
			हाल WLAN_EID_RSN:
				अगर (!स_भेद((pIE->data + 8), RSN_TKIP_CIPHER, 4))
					वापस true;
			शेष:
				अवरोध;
			पूर्ण

			i += (pIE->Length + 2);
		पूर्ण
		वापस false;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wअगरirate2_ratetbl_inx(अचिन्हित अक्षर rate)
अणु
	rate = rate & 0x7f;

	चयन (rate) अणु
	हाल 108:
		वापस 11;
	हाल 96:
		वापस 10;
	हाल 72:
		वापस 9;
	हाल 48:
		वापस 8;
	हाल 36:
		वापस 7;
	हाल 24:
		वापस 6;
	हाल 18:
		वापस 5;
	हाल 12:
		वापस 4;
	हाल 22:
		वापस 3;
	हाल 11:
		वापस 2;
	हाल 4:
		वापस 1;
	हाल 2:
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक update_basic_rate(अचिन्हित अक्षर *ptn, अचिन्हित पूर्णांक ptn_sz)
अणु
	अचिन्हित पूर्णांक i, num_of_rate;
	अचिन्हित पूर्णांक mask = 0;

	num_of_rate = min_t(अचिन्हित पूर्णांक, ptn_sz, NumRates);

	क्रम (i = 0; i < num_of_rate; i++) अणु
		अगर ((*(ptn + i)) & 0x80)
			mask |= 0x1 << wअगरirate2_ratetbl_inx(*(ptn + i));
	पूर्ण
	वापस mask;
पूर्ण

अचिन्हित पूर्णांक update_supported_rate(अचिन्हित अक्षर *ptn, अचिन्हित पूर्णांक ptn_sz)
अणु
	अचिन्हित पूर्णांक i, num_of_rate;
	अचिन्हित पूर्णांक mask = 0;

	num_of_rate = min_t(अचिन्हित पूर्णांक, ptn_sz, NumRates);

	क्रम (i = 0; i < num_of_rate; i++)
		mask |= 0x1 << wअगरirate2_ratetbl_inx(*(ptn + i));
	वापस mask;
पूर्ण

अचिन्हित पूर्णांक update_MSC_rate(काष्ठा ieee80211_ht_cap *pHT_caps)
अणु
	वापस (pHT_caps->mcs.rx_mask[0] << 12) |
	       (pHT_caps->mcs.rx_mask[1] << 20);
पूर्ण

पूर्णांक support_लघु_GI(काष्ठा adapter *padapter, काष्ठा ieee80211_ht_cap *pHT_caps)
अणु
	अचिन्हित अक्षर bit_offset;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (!(pmlmeinfo->HT_enable))
		वापस _FAIL;

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_RALINK)
		वापस _FAIL;

	bit_offset = (pmlmeext->cur_bwmode & HT_CHANNEL_WIDTH_40) ? 6 : 5;

	अगर (__le16_to_cpu(pHT_caps->cap_info) & (0x1 << bit_offset))
		वापस _SUCCESS;
	अन्यथा
		वापस _FAIL;
पूर्ण

अचिन्हित अक्षर get_highest_rate_idx(u32 mask)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर rate_idx = 0;

	क्रम (i = 27; i >= 0; i--) अणु
		अगर (mask & BIT(i)) अणु
			rate_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rate_idx;
पूर्ण

व्योम Update_RA_Entry(काष्ठा adapter *padapter, u32 mac_id)
अणु
	rtw_hal_update_ra_mask(padapter, mac_id, 0);
पूर्ण

व्योम set_sta_rate(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	/* rate adaptive */
	Update_RA_Entry(padapter, psta->mac_id);
पूर्ण

/*  Update RRSR and Rate क्रम USERATE */
व्योम update_tx_basic_rate(काष्ठा adapter *padapter, u8 wirelessmode)
अणु
	अचिन्हित अक्षर supported_rates[NDIS_802_11_LENGTH_RATES_EX];

	स_रखो(supported_rates, 0, NDIS_802_11_LENGTH_RATES_EX);

	अगर ((wirelessmode & WIRELESS_11B) && (wirelessmode == WIRELESS_11B))
		स_नकल(supported_rates, rtw_basic_rate_cck, 4);
	अन्यथा अगर (wirelessmode & WIRELESS_11B)
		स_नकल(supported_rates, rtw_basic_rate_mix, 7);
	अन्यथा
		स_नकल(supported_rates, rtw_basic_rate_ofdm, 3);

	अगर (wirelessmode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	अन्यथा
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);

	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, supported_rates);
पूर्ण

अचिन्हित अक्षर check_assoc_AP(u8 *pframe, uपूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ndis_802_11_var_ie *pIE;
	u8 epigram_venकरोr_flag;
	u8 ralink_venकरोr_flag;

	epigram_venकरोr_flag = 0;
	ralink_venकरोr_flag = 0;

	क्रम (i = माप(काष्ठा ndis_802_11_fixed_ie); i < len;) अणु
		pIE = (काष्ठा ndis_802_11_var_ie *)(pframe + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर ((!स_भेद(pIE->data, ARTHEROS_OUI1, 3)) ||
			    (!स_भेद(pIE->data, ARTHEROS_OUI2, 3))) अणु
				DBG_88E("link to Artheros AP\n");
				वापस HT_IOT_PEER_ATHEROS;
			पूर्ण अन्यथा अगर ((!स_भेद(pIE->data, BROADCOM_OUI1, 3)) ||
				   (!स_भेद(pIE->data, BROADCOM_OUI2, 3))) अणु
				DBG_88E("link to Broadcom AP\n");
				वापस HT_IOT_PEER_BROADCOM;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, MARVELL_OUI, 3)) अणु
				DBG_88E("link to Marvell AP\n");
				वापस HT_IOT_PEER_MARVELL;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, RALINK_OUI, 3)) अणु
				अगर (!ralink_venकरोr_flag) अणु
					ralink_venकरोr_flag = 1;
				पूर्ण अन्यथा अणु
					DBG_88E("link to Ralink AP\n");
					वापस HT_IOT_PEER_RALINK;
				पूर्ण
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, CISCO_OUI, 3)) अणु
				DBG_88E("link to Cisco AP\n");
				वापस HT_IOT_PEER_CISCO;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, REALTEK_OUI, 3)) अणु
				DBG_88E("link to Realtek 96B\n");
				वापस HT_IOT_PEER_REALTEK;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, AIRGOCAP_OUI, 3)) अणु
				DBG_88E("link to Airgo Cap\n");
				वापस HT_IOT_PEER_AIRGO;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, EPIGRAM_OUI, 3)) अणु
				epigram_venकरोr_flag = 1;
				अगर (ralink_venकरोr_flag) अणु
					DBG_88E("link to Tenda W311R AP\n");
					वापस HT_IOT_PEER_TENDA;
				पूर्ण
				DBG_88E("Capture EPIGRAM_OUI\n");
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण

		शेष:
			अवरोध;
		पूर्ण
		i += (pIE->Length + 2);
	पूर्ण

	अगर (ralink_venकरोr_flag && !epigram_venकरोr_flag) अणु
		DBG_88E("link to Ralink AP\n");
		वापस HT_IOT_PEER_RALINK;
	पूर्ण अन्यथा अगर (ralink_venकरोr_flag && epigram_venकरोr_flag) अणु
		DBG_88E("link to Tenda W311R AP\n");
		वापस HT_IOT_PEER_TENDA;
	पूर्ण
	DBG_88E("link to new AP\n");
	वापस HT_IOT_PEER_UNKNOWN;
पूर्ण

व्योम update_IOT_info(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	चयन (pmlmeinfo->assoc_AP_venकरोr) अणु
	हाल HT_IOT_PEER_MARVELL:
		pmlmeinfo->turboMode_cts2self = 1;
		pmlmeinfo->turboMode_rtsen = 0;
		अवरोध;
	हाल HT_IOT_PEER_RALINK:
		pmlmeinfo->turboMode_cts2self = 0;
		pmlmeinfo->turboMode_rtsen = 1;
		/* disable high घातer */
		Switch_DM_Func(padapter, (u32)(~DYNAMIC_BB_DYNAMIC_TXPWR),
			       false);
		अवरोध;
	हाल HT_IOT_PEER_REALTEK:
		/* disable high घातer */
		Switch_DM_Func(padapter, (u32)(~DYNAMIC_BB_DYNAMIC_TXPWR),
			       false);
		अवरोध;
	शेष:
		pmlmeinfo->turboMode_cts2self = 0;
		pmlmeinfo->turboMode_rtsen = 1;
		अवरोध;
	पूर्ण
पूर्ण

व्योम update_capinfo(काष्ठा adapter *Adapter, u16 updateCap)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &Adapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	bool ShortPreamble;

	/*  Check preamble mode, 2005.01.06, by rcnjko. */
	/*  Mark to update preamble value क्रमever, 2008.03.18 by lanhsin */

	अगर (updateCap & cShortPreamble) अणु /*  Short Preamble */
		अगर (pmlmeinfo->preamble_mode != PREAMBLE_SHORT) अणु /*  PREAMBLE_LONG or PREAMBLE_AUTO */
			ShortPreamble = true;
			pmlmeinfo->preamble_mode = PREAMBLE_SHORT;
			rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
		पूर्ण
	पूर्ण अन्यथा अणु /*  Long Preamble */
		अगर (pmlmeinfo->preamble_mode != PREAMBLE_LONG) अणु  /*  PREAMBLE_SHORT or PREAMBLE_AUTO */
			ShortPreamble = false;
			pmlmeinfo->preamble_mode = PREAMBLE_LONG;
			rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
		पूर्ण
	पूर्ण

	अगर (updateCap & cIBSS) अणु
		/* Filen: See 802.11-2007 p.91 */
		pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
	पूर्ण अन्यथा अणु /* Filen: See 802.11-2007 p.90 */
		अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11G | WIRELESS_11_24N)) अणु
			अगर (updateCap & cShortSlotTime) अणु /*  Short Slot Time */
				अगर (pmlmeinfo->slotTime != SHORT_SLOT_TIME)
					pmlmeinfo->slotTime = SHORT_SLOT_TIME;
			पूर्ण अन्यथा अणु /*  Long Slot Time */
				अगर (pmlmeinfo->slotTime != NON_SHORT_SLOT_TIME)
					pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
			पूर्ण
		पूर्ण अन्यथा अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11A | WIRELESS_11_5N)) अणु
			pmlmeinfo->slotTime = SHORT_SLOT_TIME;
		पूर्ण अन्यथा अणु
			/* B Mode */
			pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
		पूर्ण
	पूर्ण

	rtw_hal_set_hwreg(Adapter, HW_VAR_SLOT_TIME, &pmlmeinfo->slotTime);
पूर्ण

व्योम update_wireless_mode(काष्ठा adapter *padapter)
अणु
	पूर्णांक network_type = 0;
	u32 SIFS_Timer;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;
	अचिन्हित अक्षर *rate = cur_network->SupportedRates;

	अगर (pmlmeinfo->HT_info_enable && pmlmeinfo->HT_caps_enable)
		pmlmeinfo->HT_enable = 1;

	अगर (pmlmeinfo->HT_enable)
		network_type = WIRELESS_11_24N;

	अगर (rtw_is_cckratesonly_included(rate))
		network_type |= WIRELESS_11B;
	अन्यथा अगर (rtw_is_cckrates_included(rate))
		network_type |= WIRELESS_11BG;
	अन्यथा
		network_type |= WIRELESS_11G;

	pmlmeext->cur_wireless_mode = network_type & padapter->registrypriv.wireless_mode;

	SIFS_Timer = 0x0a0a0808;/* 0x0808 -> क्रम CCK, 0x0a0a -> क्रम OFDM */
				/* change this value अगर having IOT issues. */

	rtw_hal_set_hwreg(padapter, HW_VAR_RESP_SIFS,  (u8 *)&SIFS_Timer);

	update_mgnt_tx_rate(padapter,
			    pmlmeext->cur_wireless_mode & WIRELESS_11B ?
			    IEEE80211_CCK_RATE_1MB : IEEE80211_OFDM_RATE_6MB);
पूर्ण

व्योम update_bmc_sta_support_rate(काष्ठा adapter *padapter, u32 mac_id)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pmlmeext->cur_wireless_mode & WIRELESS_11B) अणु
		/*  Only B, B/G, and B/G/N AP could use CCK rate */
		स_नकल((pmlmeinfo->FW_sta_info[mac_id].SupportedRates), rtw_basic_rate_cck, 4);
	पूर्ण अन्यथा अणु
		स_नकल((pmlmeinfo->FW_sta_info[mac_id].SupportedRates), rtw_basic_rate_ofdm, 3);
	पूर्ण
पूर्ण

पूर्णांक update_sta_support_rate(काष्ठा adapter *padapter, u8 *pvar_ie, uपूर्णांक var_ie_len, पूर्णांक cam_idx)
अणु
	अचिन्हित पूर्णांक ie_len;
	काष्ठा ndis_802_11_var_ie *pIE;
	पूर्णांक supportRateNum = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	pIE = (काष्ठा ndis_802_11_var_ie *)rtw_get_ie(pvar_ie, WLAN_EID_SUPP_RATES, &ie_len, var_ie_len);
	अगर (!pIE)
		वापस _FAIL;
	अगर (ie_len > NDIS_802_11_LENGTH_RATES_EX)
		वापस _FAIL;

	स_नकल(pmlmeinfo->FW_sta_info[cam_idx].SupportedRates, pIE->data, ie_len);
	supportRateNum = ie_len;

	pIE = (काष्ठा ndis_802_11_var_ie *)rtw_get_ie(pvar_ie, WLAN_EID_EXT_SUPP_RATES, &ie_len, var_ie_len);
	अगर (pIE) अणु
		अगर (supportRateNum + ie_len > NDIS_802_11_LENGTH_RATES_EX)
			वापस _FAIL;
		स_नकल((pmlmeinfo->FW_sta_info[cam_idx].SupportedRates + supportRateNum), pIE->data, ie_len);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

व्योम process_addba_req(काष्ठा adapter *padapter, u8 *paddba_req, u8 *addr)
अणु
	काष्ठा sta_info *psta;
	u16 tid;
	u16 param;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा ADDBA_request *preq = (काष्ठा ADDBA_request *)paddba_req;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	psta = rtw_get_stainfo(pstapriv, addr);

	अगर (psta) अणु
		param = le16_to_cpu(preq->BA_para_set);
		tid = (param >> 2) & 0x0f;
		preorder_ctrl = &psta->recvreorder_ctrl[tid];
		preorder_ctrl->indicate_seq = 0xffff;
		preorder_ctrl->enable = pmlmeinfo->accept_addba_req;
	पूर्ण
पूर्ण

व्योम update_TSF(काष्ठा mlme_ext_priv *pmlmeext, u8 *pframe, uपूर्णांक len)
अणु
	u8 *pIE;
	__le32 *pbuf;

	pIE = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	pbuf = (__le32 *)pIE;

	pmlmeext->TSFValue = le32_to_cpu(*(pbuf + 1));

	pmlmeext->TSFValue = pmlmeext->TSFValue << 32;

	pmlmeext->TSFValue |= le32_to_cpu(*pbuf);
पूर्ण

व्योम correct_TSF(काष्ठा adapter *padapter, काष्ठा mlme_ext_priv *pmlmeext)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_CORRECT_TSF, शून्य);
पूर्ण
