<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_WLAN_UTIL_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_com_h2c.h>

अटल अचिन्हित अक्षर ARTHEROS_OUI1[] = अणु0x00, 0x03, 0x7fपूर्ण;
अटल अचिन्हित अक्षर ARTHEROS_OUI2[] = अणु0x00, 0x13, 0x74पूर्ण;

अटल अचिन्हित अक्षर BROADCOM_OUI1[] = अणु0x00, 0x10, 0x18पूर्ण;
अटल अचिन्हित अक्षर BROADCOM_OUI2[] = अणु0x00, 0x0a, 0xf7पूर्ण;
अटल अचिन्हित अक्षर BROADCOM_OUI3[] = अणु0x00, 0x05, 0xb5पूर्ण;

अटल अचिन्हित अक्षर CISCO_OUI[] = अणु0x00, 0x40, 0x96पूर्ण;
अटल अचिन्हित अक्षर MARVELL_OUI[] = अणु0x00, 0x50, 0x43पूर्ण;
अटल अचिन्हित अक्षर RALINK_OUI[] = अणु0x00, 0x0c, 0x43पूर्ण;
अटल अचिन्हित अक्षर REALTEK_OUI[] = अणु0x00, 0xe0, 0x4cपूर्ण;
अटल अचिन्हित अक्षर AIRGOCAP_OUI[] = अणु0x00, 0x0a, 0xf5पूर्ण;
अटल अचिन्हित अक्षर RSN_TKIP_CIPHER[4] = अणु0x00, 0x0f, 0xac, 0x02पूर्ण;
अटल अचिन्हित अक्षर WPA_TKIP_CIPHER[4] = अणु0x00, 0x50, 0xf2, 0x02पूर्ण;

#घोषणा R2T_PHY_DELAY	(0)

/* define WAIT_FOR_BCN_TO_MIN	(3000) */
#घोषणा WAIT_FOR_BCN_TO_MIN	(6000)
#घोषणा WAIT_FOR_BCN_TO_MAX	(20000)

#घोषणा DISCONNECT_BY_CHK_BCN_FAIL_OBSERV_PERIOD_IN_MS 1000
#घोषणा DISCONNECT_BY_CHK_BCN_FAIL_THRESHOLD 3

अटल u8 rtw_basic_rate_cck[4] = अणु
	IEEE80211_CCK_RATE_1MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_2MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_5MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_11MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

अटल u8 rtw_basic_rate_ofdm[3] = अणु
	IEEE80211_OFDM_RATE_6MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_12MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_OFDM_RATE_24MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

u8 networktype_to_raid_ex(काष्ठा adapter *adapter, काष्ठा sta_info *psta)
अणु
	u8 raid, cur_rf_type, rf_type = RF_1T1R;

	rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&cur_rf_type));

	अगर (cur_rf_type == RF_1T1R) अणु
		rf_type = RF_1T1R;
	पूर्ण अन्यथा अगर (IsSupportedVHT(psta->wireless_mode)) अणु
		अगर (psta->ra_mask & 0xffc00000)
			rf_type = RF_2T2R;
	पूर्ण अन्यथा अगर (IsSupportedHT(psta->wireless_mode)) अणु
		अगर (psta->ra_mask & 0xfff00000)
			rf_type = RF_2T2R;
	पूर्ण

	चयन (psta->wireless_mode) अणु
	हाल WIRELESS_11B:
		raid = RATEID_IDX_B;
		अवरोध;
	हाल WIRELESS_11A:
	हाल WIRELESS_11G:
		raid = RATEID_IDX_G;
		अवरोध;
	हाल WIRELESS_11BG:
		raid = RATEID_IDX_BG;
		अवरोध;
	हाल WIRELESS_11_24N:
	हाल WIRELESS_11_5N:
	हाल WIRELESS_11A_5N:
	हाल WIRELESS_11G_24N:
		अगर (rf_type == RF_2T2R)
			raid = RATEID_IDX_GN_N2SS;
		अन्यथा
			raid = RATEID_IDX_GN_N1SS;
		अवरोध;
	हाल WIRELESS_11B_24N:
	हाल WIRELESS_11BG_24N:
		अगर (psta->bw_mode == CHANNEL_WIDTH_20) अणु
			अगर (rf_type == RF_2T2R)
				raid = RATEID_IDX_BGN_20M_2SS_BN;
			अन्यथा
				raid = RATEID_IDX_BGN_20M_1SS_BN;
		पूर्ण अन्यथा अणु
			अगर (rf_type == RF_2T2R)
				raid = RATEID_IDX_BGN_40M_2SS;
			अन्यथा
				raid = RATEID_IDX_BGN_40M_1SS;
		पूर्ण
		अवरोध;
	शेष:
		raid = RATEID_IDX_BGN_40M_2SS;
		अवरोध;
	पूर्ण
	वापस raid;
पूर्ण

अचिन्हित अक्षर ratetbl_val_2wअगरirate(अचिन्हित अक्षर rate);
अचिन्हित अक्षर ratetbl_val_2wअगरirate(अचिन्हित अक्षर rate)
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

पूर्णांक is_basicrate(काष्ठा adapter *padapter, अचिन्हित अक्षर rate);
पूर्णांक is_basicrate(काष्ठा adapter *padapter, अचिन्हित अक्षर rate)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर val;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	क्रम (i = 0; i < NumRates; i++) अणु
		val = pmlmeext->basicrate[i];

		अगर ((val != 0xff) && (val != 0xfe))
			अगर (rate == ratetbl_val_2wअगरirate(val))
				वापस true;
	पूर्ण

	वापस false;
पूर्ण

अचिन्हित पूर्णांक ratetbl2rateset(काष्ठा adapter *padapter, अचिन्हित अक्षर *rateset);
अचिन्हित पूर्णांक ratetbl2rateset(काष्ठा adapter *padapter, अचिन्हित अक्षर *rateset)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर rate;
	अचिन्हित पूर्णांक	len = 0;
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

			अगर (is_basicrate(padapter, rate) == true)
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

व्योम set_mcs_rate_by_mask(u8 *mcs_set, u32 mask)
अणु
	u8 mcs_rate_1r = (u8)(mask&0xff);
	u8 mcs_rate_2r = (u8)((mask>>8)&0xff);
	u8 mcs_rate_3r = (u8)((mask>>16)&0xff);
	u8 mcs_rate_4r = (u8)((mask>>24)&0xff);

	mcs_set[0] &= mcs_rate_1r;
	mcs_set[1] &= mcs_rate_2r;
	mcs_set[2] &= mcs_rate_3r;
	mcs_set[3] &= mcs_rate_4r;
पूर्ण

व्योम UpdateBrateTbl(काष्ठा adapter *Adapter, u8 *mBratesOS)
अणु
	u8 i;
	u8 rate;

	/*  1M, 2M, 5.5M, 11M, 6M, 12M, 24M are mandatory. */
	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		rate = mBratesOS[i] & 0x7f;
		चयन (rate) अणु
		हाल IEEE80211_CCK_RATE_1MB:
		हाल IEEE80211_CCK_RATE_2MB:
		हाल IEEE80211_CCK_RATE_5MB:
		हाल IEEE80211_CCK_RATE_11MB:
		हाल IEEE80211_OFDM_RATE_6MB:
		हाल IEEE80211_OFDM_RATE_12MB:
		हाल IEEE80211_OFDM_RATE_24MB:
			mBratesOS[i] |= IEEE80211_BASIC_RATE_MASK;
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
	u8 bSaveFlag = true;

	rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_OP, (u8 *)(&bSaveFlag));
पूर्ण

व्योम Restore_DM_Func_Flag(काष्ठा adapter *padapter)
अणु
	u8 bSaveFlag = false;

	rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_OP, (u8 *)(&bSaveFlag));
पूर्ण

व्योम Switch_DM_Func(काष्ठा adapter *padapter, u32 mode, u8 enable)
अणु
	अगर (enable == true)
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
	वापस adapter_to_dvobj(adapter)->oper_channel;
पूर्ण

अंतरभूत व्योम rtw_set_oper_ch(काष्ठा adapter *adapter, u8 ch)
अणु
#अगर_घोषित DBG_CH_SWITCH
	स्थिर पूर्णांक len = 128;
	अक्षर msg[128] = अणु0पूर्ण;
	पूर्णांक cnt = 0;
	पूर्णांक i = 0;
#पूर्ण_अगर  /* DBG_CH_SWITCH */
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);

	अगर (dvobj->oper_channel != ch) अणु
		dvobj->on_oper_ch_समय = jअगरfies;

#अगर_घोषित DBG_CH_SWITCH
		cnt += scnम_लिखो(msg+cnt, len-cnt, "switch to ch %3u", ch);

		क्रम (i = 0; i < dvobj->अगरace_nums; i++) अणु
			काष्ठा adapter *अगरace = dvobj->padapters[i];

			cnt += scnम_लिखो(msg+cnt, len-cnt, " [%s:", ADPT_ARG(अगरace));
			अगर (अगरace->mlmeextpriv.cur_channel == ch)
				cnt += scnम_लिखो(msg+cnt, len-cnt, "C");
			अन्यथा
				cnt += scnम_लिखो(msg+cnt, len-cnt, "_");
			अगर (अगरace->wdinfo.listen_channel == ch && !rtw_p2p_chk_state(&अगरace->wdinfo, P2P_STATE_NONE))
				cnt += scnम_लिखो(msg+cnt, len-cnt, "L");
			अन्यथा
				cnt += scnम_लिखो(msg+cnt, len-cnt, "_");
			cnt += scnम_लिखो(msg+cnt, len-cnt, "]");
		पूर्ण

#पूर्ण_अगर /* DBG_CH_SWITCH */
	पूर्ण

	dvobj->oper_channel = ch;
पूर्ण

अंतरभूत u8 rtw_get_oper_bw(काष्ठा adapter *adapter)
अणु
	वापस adapter_to_dvobj(adapter)->oper_bwmode;
पूर्ण

अंतरभूत व्योम rtw_set_oper_bw(काष्ठा adapter *adapter, u8 bw)
अणु
	adapter_to_dvobj(adapter)->oper_bwmode = bw;
पूर्ण

अंतरभूत u8 rtw_get_oper_choffset(काष्ठा adapter *adapter)
अणु
	वापस adapter_to_dvobj(adapter)->oper_ch_offset;
पूर्ण

अंतरभूत व्योम rtw_set_oper_choffset(काष्ठा adapter *adapter, u8 offset)
अणु
	adapter_to_dvobj(adapter)->oper_ch_offset = offset;
पूर्ण

u8 rtw_get_center_ch(u8 channel, u8 chnl_bw, u8 chnl_offset)
अणु
	u8 center_ch = channel;

	अगर (chnl_bw == CHANNEL_WIDTH_80) अणु
		center_ch = 7;
	पूर्ण अन्यथा अगर (chnl_bw == CHANNEL_WIDTH_40) अणु
		अगर (chnl_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			center_ch = channel + 2;
		अन्यथा
			center_ch = channel - 2;
	पूर्ण

	वापस center_ch;
पूर्ण

अंतरभूत अचिन्हित दीर्घ rtw_get_on_cur_ch_समय(काष्ठा adapter *adapter)
अणु
	अगर (adapter->mlmeextpriv.cur_channel == adapter_to_dvobj(adapter)->oper_channel)
		वापस adapter_to_dvobj(adapter)->on_oper_ch_समय;
	अन्यथा
		वापस 0;
पूर्ण

व्योम SelectChannel(काष्ठा adapter *padapter, अचिन्हित अक्षर channel)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&(adapter_to_dvobj(padapter)->setch_mutex)))
		वापस;

	/* saved channel info */
	rtw_set_oper_ch(padapter, channel);

	rtw_hal_set_chan(padapter, channel);

	mutex_unlock(&(adapter_to_dvobj(padapter)->setch_mutex));
पूर्ण

व्योम set_channel_bwmode(काष्ठा adapter *padapter, अचिन्हित अक्षर channel, अचिन्हित अक्षर channel_offset, अचिन्हित लघु bwmode)
अणु
	u8 center_ch, chnl_offset80 = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	center_ch = rtw_get_center_ch(channel, bwmode, channel_offset);

	अगर (bwmode == CHANNEL_WIDTH_80) अणु
		अगर (center_ch > channel)
			chnl_offset80 = HAL_PRIME_CHNL_OFFSET_LOWER;
		अन्यथा अगर (center_ch < channel)
			chnl_offset80 = HAL_PRIME_CHNL_OFFSET_UPPER;
		अन्यथा
			chnl_offset80 = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	पूर्ण

	/* set Channel */
	अगर (mutex_lock_पूर्णांकerruptible(&(adapter_to_dvobj(padapter)->setch_mutex)))
		वापस;

	/* saved channel/bw info */
	rtw_set_oper_ch(padapter, channel);
	rtw_set_oper_bw(padapter, bwmode);
	rtw_set_oper_choffset(padapter, channel_offset);

	rtw_hal_set_chnl_bw(padapter, center_ch, bwmode, channel_offset, chnl_offset80); /*  set center channel */

	mutex_unlock(&(adapter_to_dvobj(padapter)->setch_mutex));
पूर्ण

अंतरभूत u8 *get_my_bssid(काष्ठा wlan_bssid_ex *pnetwork)
अणु
	वापस pnetwork->MacAddress;
पूर्ण

u16 get_beacon_पूर्णांकerval(काष्ठा wlan_bssid_ex *bss)
अणु
	__le16 val;

	स_नकल((अचिन्हित अक्षर *)&val, rtw_get_beacon_पूर्णांकerval_from_ie(bss->IEs), 2);

	वापस le16_to_cpu(val);
पूर्ण

पूर्णांक is_client_associated_to_ap(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;

	अगर (!padapter)
		वापस _FAIL;

	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर ((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) && ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE))
		वापस true;
	अन्यथा
		वापस _FAIL;
पूर्ण

पूर्णांक is_client_associated_to_ibss(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर ((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) && ((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE))
		वापस true;
	अन्यथा
		वापस _FAIL;
पूर्ण

पूर्णांक is_IBSS_empty(काष्ठा adapter *padapter)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

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
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, शून्य);

	spin_lock_bh(&cam_ctl->lock);
	cam_ctl->biपंचांगap = 0;
	स_रखो(dvobj->cam_cache, 0, माप(काष्ठा cam_entry_cache)*TOTAL_CAM_ENTRY);
	spin_unlock_bh(&cam_ctl->lock);
पूर्ण

अटल u32 _ReadCAM(काष्ठा adapter *padapter, u32 addr)
अणु
	u32 count = 0, cmd;

	cmd = CAM_POLLINIG | addr;
	rtw_ग_लिखो32(padapter, RWCAM, cmd);

	करो अणु
		अगर (0 == (rtw_पढ़ो32(padapter, REG_CAMCMD) & CAM_POLLINIG))
			अवरोध;
	पूर्ण जबतक (count++ < 100);

	वापस rtw_पढ़ो32(padapter, REG_CAMREAD);
पूर्ण

व्योम पढ़ो_cam(काष्ठा adapter *padapter, u8 entry, u8 *get_key)
अणु
	u32 j, addr, cmd;

	addr = entry << 3;

	क्रम (j = 0; j < 6; j++) अणु
		cmd = _ReadCAM(padapter, addr+j);
		अगर (j > 1) /* get key from cam */
			स_नकल(get_key+(j-2)*4, &cmd, 4);
	पूर्ण
पूर्ण

व्योम _ग_लिखो_cam(काष्ठा adapter *padapter, u8 entry, u16 ctrl, u8 *mac, u8 *key)
अणु
	अचिन्हित पूर्णांक i, val, addr;
	पूर्णांक j;
	u32 cam_val[2];

	addr = entry << 3;

	क्रम (j = 5; j >= 0; j--) अणु
		चयन (j) अणु
		हाल 0:
			val = (ctrl | (mac[0] << 16) | (mac[1] << 24));
			अवरोध;
		हाल 1:
			val = (mac[2] | (mac[3] << 8) | (mac[4] << 16) | (mac[5] << 24));
			अवरोध;
		शेष:
			i = (j - 2) << 2;
			val = (key[i] | (key[i+1] << 8) | (key[i+2] << 16) | (key[i+3] << 24));
			अवरोध;
		पूर्ण

		cam_val[0] = val;
		cam_val[1] = addr + (अचिन्हित पूर्णांक)j;

		rtw_hal_set_hwreg(padapter, HW_VAR_CAM_WRITE, (u8 *)cam_val);
	पूर्ण
पूर्ण

व्योम _clear_cam_entry(काष्ठा adapter *padapter, u8 entry)
अणु
	अचिन्हित अक्षर null_sta[] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	अचिन्हित अक्षर null_key[] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

	_ग_लिखो_cam(padapter, entry, 0, null_sta, null_key);
पूर्ण

अंतरभूत व्योम ग_लिखो_cam(काष्ठा adapter *adapter, u8 id, u16 ctrl, u8 *mac, u8 *key)
अणु
	_ग_लिखो_cam(adapter, id, ctrl, mac, key);
	ग_लिखो_cam_cache(adapter, id, ctrl, mac, key);
पूर्ण

अंतरभूत व्योम clear_cam_entry(काष्ठा adapter *adapter, u8 id)
अणु
	_clear_cam_entry(adapter, id);
	clear_cam_cache(adapter, id);
पूर्ण

व्योम ग_लिखो_cam_cache(काष्ठा adapter *adapter, u8 id, u16 ctrl, u8 *mac, u8 *key)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	dvobj->cam_cache[id].ctrl = ctrl;
	स_नकल(dvobj->cam_cache[id].mac, mac, ETH_ALEN);
	स_नकल(dvobj->cam_cache[id].key, key, 16);

	spin_unlock_bh(&cam_ctl->lock);
पूर्ण

व्योम clear_cam_cache(काष्ठा adapter *adapter, u8 id)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	स_रखो(&(dvobj->cam_cache[id]), 0, माप(काष्ठा cam_entry_cache));

	spin_unlock_bh(&cam_ctl->lock);
पूर्ण

अटल bool _rtw_camid_is_gk(काष्ठा adapter *adapter, u8 cam_id)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	bool ret = false;

	अगर (cam_id >= TOTAL_CAM_ENTRY)
		जाओ निकास;

	अगर (!(cam_ctl->biपंचांगap & BIT(cam_id)))
		जाओ निकास;

	ret = (dvobj->cam_cache[cam_id].ctrl&BIT6)?true:false;

निकास:
	वापस ret;
पूर्ण

अटल s16 _rtw_camid_search(काष्ठा adapter *adapter, u8 *addr, s16 kid)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	पूर्णांक i;
	s16 cam_id = -1;

	क्रम (i = 0; i < TOTAL_CAM_ENTRY; i++) अणु
		अगर (addr && स_भेद(dvobj->cam_cache[i].mac, addr, ETH_ALEN))
			जारी;
		अगर (kid >= 0 && kid != (dvobj->cam_cache[i].ctrl&0x03))
			जारी;

		cam_id = i;
		अवरोध;
	पूर्ण

	वापस cam_id;
पूर्ण

s16 rtw_camid_search(काष्ठा adapter *adapter, u8 *addr, s16 kid)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	s16 cam_id = -1;

	spin_lock_bh(&cam_ctl->lock);
	cam_id = _rtw_camid_search(adapter, addr, kid);
	spin_unlock_bh(&cam_ctl->lock);

	वापस cam_id;
पूर्ण

s16 rtw_camid_alloc(काष्ठा adapter *adapter, काष्ठा sta_info *sta, u8 kid)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;
	s16 cam_id = -1;
	काष्ठा mlme_ext_info *mlmeinfo;

	spin_lock_bh(&cam_ctl->lock);

	mlmeinfo = &adapter->mlmeextpriv.mlmext_info;

	अगर ((((mlmeinfo->state&0x03) == WIFI_FW_AP_STATE) || ((mlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE))
		&& !sta) अणु
		/* AP/Ad-hoc mode group key: अटल alloction to शेष key by key ID */
		अगर (kid > 3) अणु
			netdev_dbg(adapter->pnetdev,
				   FUNC_ADPT_FMT " group key with invalid key id:%u\n",
				   FUNC_ADPT_ARG(adapter), kid);
			rtw_warn_on(1);
			जाओ biपंचांगap_handle;
		पूर्ण

		cam_id = kid;
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		u8 *addr = sta?sta->hwaddr:शून्य;

		अगर (!sta) अणु
			अगर (!(mlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)) अणु
				/* bypass STA mode group key setting beक्रमe connected(ex:WEP) because bssid is not पढ़ोy */
				जाओ biपंचांगap_handle;
			पूर्ण

			addr = get_bssid(&adapter->mlmepriv);
		पूर्ण

		i = _rtw_camid_search(adapter, addr, kid);
		अगर (i >= 0) अणु
			/* Fix issue that pairwise and group key have same key id. Pairwise key first, group key can overwirte group only(ex: rekey) */
			अगर (sta || _rtw_camid_is_gk(adapter, i))
				cam_id = i;
			अन्यथा
				netdev_dbg(adapter->pnetdev,
					   FUNC_ADPT_FMT " group key id:%u the same key id as pairwise key\n",
					   FUNC_ADPT_ARG(adapter), kid);
			जाओ biपंचांगap_handle;
		पूर्ण

		क्रम (i = 4; i < TOTAL_CAM_ENTRY; i++)
			अगर (!(cam_ctl->biपंचांगap & BIT(i)))
				अवरोध;

		अगर (i == TOTAL_CAM_ENTRY) अणु
			अगर (sta)
				netdev_dbg(adapter->pnetdev,
					   FUNC_ADPT_FMT " pairwise key with %pM id:%u no room\n",
					   FUNC_ADPT_ARG(adapter),
					   MAC_ARG(sta->hwaddr), kid);
			अन्यथा
				netdev_dbg(adapter->pnetdev,
					   FUNC_ADPT_FMT " group key id:%u no room\n",
					   FUNC_ADPT_ARG(adapter), kid);
			rtw_warn_on(1);
			जाओ biपंचांगap_handle;
		पूर्ण

		cam_id = i;
	पूर्ण

biपंचांगap_handle:
	अगर (cam_id >= 0 && cam_id < 32)
		cam_ctl->biपंचांगap |= BIT(cam_id);

	spin_unlock_bh(&cam_ctl->lock);

	वापस cam_id;
पूर्ण

व्योम rtw_camid_मुक्त(काष्ठा adapter *adapter, u8 cam_id)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	काष्ठा cam_ctl_t *cam_ctl = &dvobj->cam_ctl;

	spin_lock_bh(&cam_ctl->lock);

	अगर (cam_id < TOTAL_CAM_ENTRY)
		cam_ctl->biपंचांगap &= ~(BIT(cam_id));

	spin_unlock_bh(&cam_ctl->lock);
पूर्ण

पूर्णांक allocate_fw_sta_entry(काष्ठा adapter *padapter)
अणु
	अचिन्हित पूर्णांक mac_id;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

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
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	invalidate_cam_all(padapter);
	/* clear शेष key related key search setting */
	rtw_hal_set_hwreg(padapter, HW_VAR_SEC_DK_CFG, (u8 *)false);

	स_रखो((u8 *)(pmlmeinfo->FW_sta_info), 0, माप(pmlmeinfo->FW_sta_info));
पूर्ण

पूर्णांक WMM_param_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE)
अणु
	/* काष्ठा registry_priv *pregpriv = &padapter->registrypriv; */
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (pmlmepriv->qospriv.qos_option == 0) अणु
		pmlmeinfo->WMM_enable = 0;
		वापस false;
	पूर्ण

	अगर (!स_भेद(&(pmlmeinfo->WMM_param), (pIE->data + 6), माप(काष्ठा WMM_para_element)))
		वापस false;
	अन्यथा
		स_नकल(&(pmlmeinfo->WMM_param), (pIE->data + 6), माप(काष्ठा WMM_para_element));

	pmlmeinfo->WMM_enable = 1;
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
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;

	acm_mask = 0;

	अगर (pmlmeext->cur_wireless_mode & WIRELESS_11_24N)
		aSअगरsTime = 16;
	अन्यथा
		aSअगरsTime = 10;

	अगर (pmlmeinfo->WMM_enable == 0) अणु
		padapter->mlmepriv.acm_mask = 0;

		AIFS = aSअगरsTime + (2 * pmlmeinfo->slotTime);

		अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11G | WIRELESS_11A)) अणु
			ECWMin = 4;
			ECWMax = 10;
		पूर्ण अन्यथा अगर (pmlmeext->cur_wireless_mode & WIRELESS_11B) अणु
			ECWMin = 5;
			ECWMax = 10;
		पूर्ण अन्यथा अणु
			ECWMin = 4;
			ECWMax = 10;
		पूर्ण

		TXOP = 0;
		acParm = AIFS | (ECWMin << 8) | (ECWMax << 12) | (TXOP << 16);
		rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acParm));
		rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acParm));
		rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acParm));

		ECWMin = 2;
		ECWMax = 3;
		TXOP = 0x2f;
		acParm = AIFS | (ECWMin << 8) | (ECWMax << 12) | (TXOP << 16);
		rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acParm));
	पूर्ण अन्यथा अणु
		edca[0] = edca[1] = edca[2] = edca[3] = 0;

		क्रम (i = 0; i < 4; i++) अणु
			ACI = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 5) & 0x03;
			ACM = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 4) & 0x01;

			/* AIFS = AIFSN * slot समय + SIFS - r2t phy delay */
			AIFS = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN & 0x0f) * pmlmeinfo->slotTime + aSअगरsTime;

			ECWMin = (pmlmeinfo->WMM_param.ac_param[i].CW & 0x0f);
			ECWMax = (pmlmeinfo->WMM_param.ac_param[i].CW & 0xf0) >> 4;
			TXOP = le16_to_cpu(pmlmeinfo->WMM_param.ac_param[i].TXOP_limit);

			acParm = AIFS | (ECWMin << 8) | (ECWMax << 12) | (TXOP << 16);

			चयन (ACI) अणु
			हाल 0x0:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acParm));
				acm_mask |= (ACM ? BIT(1):0);
				edca[XMIT_BE_QUEUE] = acParm;
				अवरोध;

			हाल 0x1:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acParm));
				/* acm_mask |= (ACM? BIT(0):0); */
				edca[XMIT_BK_QUEUE] = acParm;
				अवरोध;

			हाल 0x2:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acParm));
				acm_mask |= (ACM ? BIT(2):0);
				edca[XMIT_VI_QUEUE] = acParm;
				अवरोध;

			हाल 0x3:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acParm));
				acm_mask |= (ACM ? BIT(3):0);
				edca[XMIT_VO_QUEUE] = acParm;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (padapter->registrypriv.acm_method == 1)
			rtw_hal_set_hwreg(padapter, HW_VAR_ACM_CTRL, (u8 *)(&acm_mask));
		अन्यथा
			padapter->mlmepriv.acm_mask = acm_mask;

		inx[0] = 0; inx[1] = 1; inx[2] = 2; inx[3] = 3;

		अगर (pregpriv->wअगरi_spec == 1) अणु
			u32 j, पंचांगp, change_inx = false;

			/* entry indx: 0->vo, 1->vi, 2->be, 3->bk. */
			क्रम (i = 0; i < 4; i++) अणु
				क्रम (j = i+1; j < 4; j++) अणु
					/* compare CW and AIFS */
					अगर ((edca[j] & 0xFFFF) < (edca[i] & 0xFFFF)) अणु
						change_inx = true;
					पूर्ण अन्यथा अगर ((edca[j] & 0xFFFF) == (edca[i] & 0xFFFF)) अणु
						/* compare TXOP */
						अगर ((edca[j] >> 16) > (edca[i] >> 16))
							change_inx = true;
					पूर्ण

					अगर (change_inx) अणु
						पंचांगp = edca[i];
						edca[i] = edca[j];
						edca[j] = पंचांगp;

						पंचांगp = inx[i];
						inx[i] = inx[j];
						inx[j] = पंचांगp;

						change_inx = false;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < 4; i++)
			pxmitpriv->wmm_para_seq[i] = inx[i];
	पूर्ण
पूर्ण

अटल व्योम bwmode_update_check(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE)
अणु
	अचिन्हित अक्षर  new_bwmode;
	अचिन्हित अक्षर  new_ch_offset;
	काष्ठा HT_info_element	 *pHT_info;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	u8 cbw40_enable = 0;

	अगर (!pIE)
		वापस;

	अगर (phtpriv->ht_option == false)
		वापस;

	अगर (pmlmeext->cur_bwmode >= CHANNEL_WIDTH_80)
		वापस;

	अगर (pIE->Length > माप(काष्ठा HT_info_element))
		वापस;

	pHT_info = (काष्ठा HT_info_element *)pIE->data;

	अगर (pmlmeext->cur_channel > 14) अणु
		अगर ((pregistrypriv->bw_mode & 0xf0) > 0)
			cbw40_enable = 1;
	पूर्ण अन्यथा अणु
		अगर ((pregistrypriv->bw_mode & 0x0f) > 0)
			cbw40_enable = 1;
	पूर्ण

	अगर ((pHT_info->infos[0] & BIT(2)) && cbw40_enable) अणु
		new_bwmode = CHANNEL_WIDTH_40;

		चयन (pHT_info->infos[0] & 0x3) अणु
		हाल 1:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
			अवरोध;

		हाल 3:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
			अवरोध;

		शेष:
			new_bwmode = CHANNEL_WIDTH_20;
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_bwmode = CHANNEL_WIDTH_20;
		new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	पूर्ण

	अगर ((new_bwmode != pmlmeext->cur_bwmode) || (new_ch_offset != pmlmeext->cur_ch_offset)) अणु
		pmlmeinfo->bwmode_updated = true;

		pmlmeext->cur_bwmode = new_bwmode;
		pmlmeext->cur_ch_offset = new_ch_offset;

		/* update HT info also */
		HT_info_handler(padapter, pIE);
	पूर्ण अन्यथा अणु
		pmlmeinfo->bwmode_updated = false;
	पूर्ण

	अगर (true == pmlmeinfo->bwmode_updated) अणु
		काष्ठा sta_info *psta;
		काष्ठा wlan_bssid_ex	*cur_network = &(pmlmeinfo->network);
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		/* set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode); */

		/* update ap's stainfo */
		psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
		अगर (psta) अणु
			काष्ठा ht_priv *phtpriv_sta = &psta->htpriv;

			अगर (phtpriv_sta->ht_option) अणु
				/*  bwmode */
				psta->bw_mode = pmlmeext->cur_bwmode;
				phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;
			पूर्ण अन्यथा अणु
				psta->bw_mode = CHANNEL_WIDTH_20;
				phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			पूर्ण

			rtw_dm_ra_mask_wk_cmd(padapter, (u8 *)psta);
		पूर्ण
	पूर्ण
पूर्ण

व्योम HT_caps_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE)
अणु
	अचिन्हित पूर्णांक	i;
	u8 rf_type;
	u8 max_AMPDU_len, min_MPDU_spacing;
	u8 cur_ldpc_cap = 0, cur_stbc_cap = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	अगर (!pIE)
		वापस;

	अगर (phtpriv->ht_option == false)
		वापस;

	pmlmeinfo->HT_caps_enable = 1;

	क्रम (i = 0; i < (pIE->Length); i++) अणु
		अगर (i != 2) अणु
			/* Commented by Albert 2010/07/12 */
			/* Got the endian issue here. */
			pmlmeinfo->HT_caps.u.HT_cap[i] &= (pIE->data[i]);
		पूर्ण अन्यथा अणु
			/* modअगरy from  fw by Thomas 2010/11/17 */
			अगर ((pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x3) > (pIE->data[i] & 0x3))
				max_AMPDU_len = (pIE->data[i] & 0x3);
			अन्यथा
				max_AMPDU_len = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x3);

			अगर ((pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c) > (pIE->data[i] & 0x1c))
				min_MPDU_spacing = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c);
			अन्यथा
				min_MPDU_spacing = (pIE->data[i] & 0x1c);

			pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para = max_AMPDU_len | min_MPDU_spacing;
		पूर्ण
	पूर्ण
	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

	/* update the MCS set */
	क्रम (i = 0; i < 16; i++)
		pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= pmlmeext->शेष_supported_mcs_set[i];

	/* update the MCS rates */
	चयन (rf_type) अणु
	हाल RF_1T1R:
	हाल RF_1T2R:
		set_mcs_rate_by_mask(pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate, MCS_RATE_1R);
		अवरोध;
	हाल RF_2T2R:
	शेष:
		set_mcs_rate_by_mask(pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate, MCS_RATE_2R);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		/*  Config STBC setting */
		अगर (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX) &&
		    GET_HT_CAPABILITY_ELE_TX_STBC(pIE->data))
			SET_FLAG(cur_stbc_cap, STBC_HT_ENABLE_TX);

		phtpriv->stbc_cap = cur_stbc_cap;
	पूर्ण अन्यथा अणु
		/*  Config LDPC Coding Capability */
		अगर (TEST_FLAG(phtpriv->ldpc_cap, LDPC_HT_ENABLE_TX) &&
		    GET_HT_CAPABILITY_ELE_LDPC_CAP(pIE->data))
			SET_FLAG(cur_ldpc_cap, (LDPC_HT_ENABLE_TX | LDPC_HT_CAP_TX));

		phtpriv->ldpc_cap = cur_ldpc_cap;

		/*  Config STBC setting */
		अगर (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX) &&
		    GET_HT_CAPABILITY_ELE_RX_STBC(pIE->data))
			SET_FLAG(cur_stbc_cap, (STBC_HT_ENABLE_TX | STBC_HT_CAP_TX));

		phtpriv->stbc_cap = cur_stbc_cap;
	पूर्ण
पूर्ण

व्योम HT_info_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	अगर (!pIE)
		वापस;

	अगर (phtpriv->ht_option == false)
		वापस;

	अगर (pIE->Length > माप(काष्ठा HT_info_element))
		वापस;

	pmlmeinfo->HT_info_enable = 1;
	स_नकल(&(pmlmeinfo->HT_info), pIE->data, pIE->Length);
पूर्ण

व्योम HTOnAssocRsp(काष्ठा adapter *padapter)
अणु
	अचिन्हित अक्षर max_AMPDU_len;
	अचिन्हित अक्षर min_MPDU_spacing;
	/* काष्ठा registry_priv  *pregpriv = &padapter->registrypriv; */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर ((pmlmeinfo->HT_info_enable) && (pmlmeinfo->HT_caps_enable)) अणु
		pmlmeinfo->HT_enable = 1;
	पूर्ण अन्यथा अणु
		pmlmeinfo->HT_enable = 0;
		/* set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode); */
		वापस;
	पूर्ण

	/* handle A-MPDU parameter field */
	/*
		AMPDU_para [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
		AMPDU_para [4:2]:Min MPDU Start Spacing
	*/
	max_AMPDU_len = pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x03;

	min_MPDU_spacing = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c) >> 2;

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_MIN_SPACE, (u8 *)(&min_MPDU_spacing));

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_FACTOR, (u8 *)(&max_AMPDU_len));
पूर्ण

व्योम ERP_IE_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (pIE->Length > 1)
		वापस;

	pmlmeinfo->ERP_enable = 1;
	स_नकल(&(pmlmeinfo->ERP_IE), pIE->data, pIE->Length);
पूर्ण

व्योम VCS_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा registry_priv  *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	चयन (pregpriv->vrtl_carrier_sense) अणु/* 0:off 1:on 2:स्वतः */
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

व्योम update_ldpc_stbc_cap(काष्ठा sta_info *psta)
अणु
	अगर (psta->htpriv.ht_option) अणु
		अगर (TEST_FLAG(psta->htpriv.ldpc_cap, LDPC_HT_ENABLE_TX))
			psta->ldpc = 1;

		अगर (TEST_FLAG(psta->htpriv.stbc_cap, STBC_HT_ENABLE_TX))
			psta->stbc = 1;
	पूर्ण अन्यथा अणु
		psta->ldpc = 0;
		psta->stbc = 0;
	पूर्ण
पूर्ण

पूर्णांक rtw_check_bcn_info(काष्ठा adapter *Adapter, u8 *pframe, u32 packet_len)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित अक्षर *p;
	अचिन्हित लघु	val16, subtype;
	काष्ठा wlan_network *cur_network = &(Adapter->mlmepriv.cur_network);
	/* u8 wpa_ie[255], rsn_ie[255]; */
	u16 wpa_len = 0, rsn_len = 0;
	u8 encryp_protocol = 0;
	काष्ठा wlan_bssid_ex *bssid;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0, is_8021x = 0;
	अचिन्हित अक्षर *pbuf;
	u32 wpa_ielen = 0;
	u8 *pbssid = GetAddr3Ptr(pframe);
	काष्ठा HT_info_element *pht_info = शून्य;
	काष्ठा ieee80211_ht_cap *pht_cap = शून्य;
	u32 bcn_channel;
	अचिन्हित लघु	ht_cap_info;
	अचिन्हित अक्षर ht_info_infos_0;
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	पूर्णांक ssid_len;

	अगर (is_client_associated_to_ap(Adapter) == false)
		वापस true;

	len = packet_len - माप(काष्ठा ieee80211_hdr_3addr);

	अगर (len > MAX_IE_SZ)
		वापस _FAIL;

	अगर (स_भेद(cur_network->network.MacAddress, pbssid, 6))
		वापस true;

	bssid = rtw_zदो_स्मृति(माप(काष्ठा wlan_bssid_ex));
	अगर (!bssid)
		वापस true;

	अगर ((pmlmepriv->समयBcnInfoChkStart != 0) && (jअगरfies_to_msecs(jअगरfies - pmlmepriv->समयBcnInfoChkStart) > DISCONNECT_BY_CHK_BCN_FAIL_OBSERV_PERIOD_IN_MS)) अणु
		pmlmepriv->समयBcnInfoChkStart = 0;
		pmlmepriv->NumOfBcnInfoChkFail = 0;
	पूर्ण

	subtype = GetFrameSubType(pframe) >> 4;

	अगर (subtype == WIFI_BEACON)
		bssid->Reserved[0] = 1;

	bssid->Length = माप(काष्ठा wlan_bssid_ex) - MAX_IE_SZ + len;

	/* below is to copy the inक्रमmation element */
	bssid->IELength = len;
	स_नकल(bssid->IEs, (pframe + माप(काष्ठा ieee80211_hdr_3addr)), bssid->IELength);

	/* check bw and channel offset */
	/* parsing HT_CAP_IE */
	p = rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_HT_CAPABILITY, &len, bssid->IELength - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
			pht_cap = (काष्ठा ieee80211_ht_cap *)(p + 2);
			ht_cap_info = le16_to_cpu(pht_cap->cap_info);
	पूर्ण अन्यथा अणु
			ht_cap_info = 0;
	पूर्ण
	/* parsing HT_INFO_IE */
	p = rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_HT_OPERATION, &len, bssid->IELength - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
			pht_info = (काष्ठा HT_info_element *)(p + 2);
			ht_info_infos_0 = pht_info->infos[0];
	पूर्ण अन्यथा अणु
			ht_info_infos_0 = 0;
	पूर्ण
	अगर (ht_cap_info != cur_network->BcnInfo.ht_cap_info ||
		((ht_info_infos_0&0x03) != (cur_network->BcnInfo.ht_info_infos_0&0x03))) अणु
			अणु
				/* bcn_info_update */
				cur_network->BcnInfo.ht_cap_info = ht_cap_info;
				cur_network->BcnInfo.ht_info_infos_0 = ht_info_infos_0;
				/* to करो : need to check that whether modअगरy related रेजिस्टर of BB or not */
			पूर्ण
			/* जाओ _mismatch; */
	पूर्ण

	/* Checking क्रम channel */
	p = rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_DS_PARAMS, &len, bssid->IELength - _FIXED_IE_LENGTH_);
	अगर (p) अणु
			bcn_channel = *(p + 2);
	पूर्ण अन्यथा अणु/* In 5G, some ap करो not have DSSET IE checking HT info क्रम channel */
		rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_HT_OPERATION,
			   &len, bssid->IELength - _FIXED_IE_LENGTH_);
		अगर (pht_info)
			bcn_channel = pht_info->primary_channel;
		अन्यथा /* we करोn't find channel IE, so don't check it */
			bcn_channel = Adapter->mlmeextpriv.cur_channel;
	पूर्ण

	अगर (bcn_channel != Adapter->mlmeextpriv.cur_channel)
			जाओ _mismatch;

	/* checking SSID */
	ssid_len = 0;
	p = rtw_get_ie(bssid->IEs + _FIXED_IE_LENGTH_, WLAN_EID_SSID, &len, bssid->IELength - _FIXED_IE_LENGTH_);
	अगर (p) अणु
		ssid_len = *(p + 1);
		अगर (ssid_len > NDIS_802_11_LENGTH_SSID)
			ssid_len = 0;
	पूर्ण
	स_नकल(bssid->Ssid.Ssid, (p + 2), ssid_len);
	bssid->Ssid.SsidLength = ssid_len;

	अगर (स_भेद(bssid->Ssid.Ssid, cur_network->network.Ssid.Ssid, 32) ||
			bssid->Ssid.SsidLength != cur_network->network.Ssid.SsidLength)
		अगर (bssid->Ssid.Ssid[0] != '\0' &&
		    bssid->Ssid.SsidLength != 0) /* not hidden ssid */
			जाओ _mismatch;

	/* check encryption info */
	val16 = rtw_get_capability((काष्ठा wlan_bssid_ex *)bssid);

	अगर (val16 & BIT(4))
		bssid->Privacy = 1;
	अन्यथा
		bssid->Privacy = 0;

	अगर (cur_network->network.Privacy != bssid->Privacy)
		जाओ _mismatch;

	rtw_get_sec_ie(bssid->IEs, bssid->IELength, शून्य, &rsn_len, शून्य, &wpa_len);

	अगर (rsn_len > 0)
		encryp_protocol = ENCRYP_PROTOCOL_WPA2;
	अन्यथा अगर (wpa_len > 0)
		encryp_protocol = ENCRYP_PROTOCOL_WPA;
	अन्यथा
		अगर (bssid->Privacy)
			encryp_protocol = ENCRYP_PROTOCOL_WEP;

	अगर (cur_network->BcnInfo.encryp_protocol != encryp_protocol)
		जाओ _mismatch;

	अगर (encryp_protocol == ENCRYP_PROTOCOL_WPA || encryp_protocol == ENCRYP_PROTOCOL_WPA2) अणु
		pbuf = rtw_get_wpa_ie(&bssid->IEs[12], &wpa_ielen, bssid->IELength-12);
		अगर (pbuf && (wpa_ielen > 0)) अणु
			rtw_parse_wpa_ie(pbuf, wpa_ielen + 2, &group_cipher,
					 &pairwise_cipher, &is_8021x);
		पूर्ण अन्यथा अणु
			pbuf = rtw_get_wpa2_ie(&bssid->IEs[12], &wpa_ielen, bssid->IELength-12);

			अगर (pbuf && (wpa_ielen > 0))
				rtw_parse_wpa2_ie(pbuf, wpa_ielen + 2, &group_cipher,
						  &pairwise_cipher, &is_8021x);
		पूर्ण

		अगर (pairwise_cipher != cur_network->BcnInfo.pairwise_cipher ||
		    group_cipher != cur_network->BcnInfo.group_cipher)
			जाओ _mismatch;

		अगर (is_8021x != cur_network->BcnInfo.is_8021x)
			जाओ _mismatch;
	पूर्ण

	kमुक्त(bssid);
	वापस _SUCCESS;

_mismatch:
	kमुक्त(bssid);

	अगर (pmlmepriv->NumOfBcnInfoChkFail == 0)
		pmlmepriv->समयBcnInfoChkStart = jअगरfies;

	pmlmepriv->NumOfBcnInfoChkFail++;

	अगर ((pmlmepriv->समयBcnInfoChkStart != 0) && (jअगरfies_to_msecs(jअगरfies - pmlmepriv->समयBcnInfoChkStart) <= DISCONNECT_BY_CHK_BCN_FAIL_OBSERV_PERIOD_IN_MS)
		&& (pmlmepriv->NumOfBcnInfoChkFail >= DISCONNECT_BY_CHK_BCN_FAIL_THRESHOLD)) अणु
		pmlmepriv->समयBcnInfoChkStart = 0;
		pmlmepriv->NumOfBcnInfoChkFail = 0;
		वापस _FAIL;
	पूर्ण

	वापस _SUCCESS;
पूर्ण

व्योम update_beacon_info(काष्ठा adapter *padapter, u8 *pframe, uपूर्णांक pkt_len, काष्ठा sta_info *psta)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len;
	काष्ठा ndis_80211_var_ie *pIE;

	len = pkt_len - (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN);

	क्रम (i = 0; i < len;) अणु
		pIE = (काष्ठा ndis_80211_var_ie *)(pframe + (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN) + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			/* to update WMM parameter set जबतक receiving beacon */
			अगर (!स_भेद(pIE->data, WMM_PARA_OUI, 6) && pIE->Length == WLAN_WMM_LEN)	/* WMM */
				अगर (WMM_param_handler(padapter, pIE))
					report_wmm_edca_update(padapter);

			अवरोध;

		हाल WLAN_EID_HT_OPERATION:	/* HT info */
			/* HT_info_handler(padapter, pIE); */
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
	काष्ठा ndis_80211_var_ie *pIE;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);

	अगर (rtw_get_capability((काष्ठा wlan_bssid_ex *)cur_network) & WLAN_CAPABILITY_PRIVACY) अणु
		क्रम (i = माप(काष्ठा ndis_802_11_fix_ie); i < pmlmeinfo->network.IELength;) अणु
			pIE = (काष्ठा ndis_80211_var_ie *)(pmlmeinfo->network.IEs + i);

			चयन (pIE->ElementID) अणु
			हाल WLAN_EID_VENDOR_SPECIFIC:
				अगर ((!स_भेद(pIE->data, RTW_WPA_OUI, 4)) && (!स_भेद((pIE->data + 12), WPA_TKIP_CIPHER, 4)))
					वापस true;

				अवरोध;

			हाल WLAN_EID_RSN:
				अगर (!स_भेद((pIE->data + 8), RSN_TKIP_CIPHER, 4))
					वापस true;
				अवरोध;

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

पूर्णांक support_लघु_GI(काष्ठा adapter *padapter, काष्ठा HT_caps_element *pHT_caps, u8 bwmode)
अणु
	अचिन्हित अक्षर bit_offset;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (!(pmlmeinfo->HT_enable))
		वापस _FAIL;

	bit_offset = (bwmode & CHANNEL_WIDTH_40) ? 6 : 5;

	अगर (le16_to_cpu(pHT_caps->u.HT_cap_element.HT_caps_info) & (0x1 << bit_offset))
		वापस _SUCCESS;
	अन्यथा
		वापस _FAIL;
पूर्ण

अचिन्हित अक्षर get_highest_rate_idx(u32 mask)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर rate_idx = 0;

	क्रम (i = 31; i >= 0; i--) अणु
		अगर (mask & BIT(i)) अणु
			rate_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rate_idx;
पूर्ण

व्योम Update_RA_Entry(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	rtw_hal_update_ra_mask(psta, 0);
पूर्ण

व्योम set_sta_rate(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	/* rate adaptive */
	Update_RA_Entry(padapter, psta);
पूर्ण

अचिन्हित अक्षर check_assoc_AP(u8 *pframe, uपूर्णांक len)
अणु
	अचिन्हित पूर्णांक	i;
	काष्ठा ndis_80211_var_ie *pIE;

	क्रम (i = माप(काष्ठा ndis_802_11_fix_ie); i < len;) अणु
		pIE = (काष्ठा ndis_80211_var_ie *)(pframe + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर ((!स_भेद(pIE->data, ARTHEROS_OUI1, 3)) || (!स_भेद(pIE->data, ARTHEROS_OUI2, 3))) अणु
				वापस HT_IOT_PEER_ATHEROS;
			पूर्ण अन्यथा अगर ((!स_भेद(pIE->data, BROADCOM_OUI1, 3)) ||
				   (!स_भेद(pIE->data, BROADCOM_OUI2, 3)) ||
				   (!स_भेद(pIE->data, BROADCOM_OUI3, 3))) अणु
				वापस HT_IOT_PEER_BROADCOM;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, MARVELL_OUI, 3)) अणु
				वापस HT_IOT_PEER_MARVELL;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, RALINK_OUI, 3)) अणु
				वापस HT_IOT_PEER_RALINK;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, CISCO_OUI, 3)) अणु
				वापस HT_IOT_PEER_CISCO;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, REALTEK_OUI, 3)) अणु
				u32 Vender = HT_IOT_PEER_REALTEK;

				अगर (pIE->Length >= 5) अणु
					अगर (pIE->data[4] == 1)
						/* अगर (pIE->data[5] & RT_HT_CAP_USE_LONG_PREAMBLE) */
						/* bssDesc->BssHT.RT2RT_HT_Mode |= RT_HT_CAP_USE_LONG_PREAMBLE; */
						अगर (pIE->data[5] & RT_HT_CAP_USE_92SE)
							/* bssDesc->BssHT.RT2RT_HT_Mode |= RT_HT_CAP_USE_92SE; */
							Vender = HT_IOT_PEER_REALTEK_92SE;

					अगर (pIE->data[5] & RT_HT_CAP_USE_SOFTAP)
						Vender = HT_IOT_PEER_REALTEK_SOFTAP;

					अगर (pIE->data[4] == 2) अणु
						अगर (pIE->data[6] & RT_HT_CAP_USE_JAGUAR_BCUT)
							Vender = HT_IOT_PEER_REALTEK_JAGUAR_BCUTAP;

						अगर (pIE->data[6] & RT_HT_CAP_USE_JAGUAR_CCUT)
							Vender = HT_IOT_PEER_REALTEK_JAGUAR_CCUTAP;
					पूर्ण
				पूर्ण

				वापस Vender;
			पूर्ण अन्यथा अगर (!स_भेद(pIE->data, AIRGOCAP_OUI, 3)) अणु
				वापस HT_IOT_PEER_AIRGO;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण

		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण

	वापस HT_IOT_PEER_UNKNOWN;
पूर्ण

व्योम update_IOT_info(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	चयन (pmlmeinfo->assoc_AP_venकरोr) अणु
	हाल HT_IOT_PEER_MARVELL:
		pmlmeinfo->turboMode_cts2self = 1;
		pmlmeinfo->turboMode_rtsen = 0;
		अवरोध;

	हाल HT_IOT_PEER_RALINK:
		pmlmeinfo->turboMode_cts2self = 0;
		pmlmeinfo->turboMode_rtsen = 1;
		/* disable high घातer */
		Switch_DM_Func(padapter, (~DYNAMIC_BB_DYNAMIC_TXPWR), false);
		अवरोध;
	हाल HT_IOT_PEER_REALTEK:
		/* rtw_ग_लिखो16(padapter, 0x4cc, 0xffff); */
		/* rtw_ग_लिखो16(padapter, 0x546, 0x01c0); */
		/* disable high घातer */
		Switch_DM_Func(padapter, (~DYNAMIC_BB_DYNAMIC_TXPWR), false);
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
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	bool		ShortPreamble;

	/*  Check preamble mode, 2005.01.06, by rcnjko. */
	/*  Mark to update preamble value क्रमever, 2008.03.18 by lanhsin */
	/* अगर (pMgntInfo->RegPreambleMode == PREAMBLE_AUTO) */
	अणु
		अगर (updateCap & cShortPreamble) अणु
			/*  Short Preamble */
			अगर (pmlmeinfo->preamble_mode != PREAMBLE_SHORT) अणु /*  PREAMBLE_LONG or PREAMBLE_AUTO */
				ShortPreamble = true;
				pmlmeinfo->preamble_mode = PREAMBLE_SHORT;
				rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  Long Preamble */
			अगर (pmlmeinfo->preamble_mode != PREAMBLE_LONG) अणु /*  PREAMBLE_SHORT or PREAMBLE_AUTO */
				ShortPreamble = false;
				pmlmeinfo->preamble_mode = PREAMBLE_LONG;
				rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (updateCap & cIBSS) अणु
		/* Filen: See 802.11-2007 p.91 */
		pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
	पूर्ण अन्यथा अणु
		/* Filen: See 802.11-2007 p.90 */
		अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11_24N | WIRELESS_11A | WIRELESS_11_5N | WIRELESS_11AC)) अणु
			pmlmeinfo->slotTime = SHORT_SLOT_TIME;
		पूर्ण अन्यथा अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11G)) अणु
			अगर ((updateCap & cShortSlotTime) /* && (!(pMgntInfo->pHTInfo->RT2RT_HT_Mode & RT_HT_CAP_USE_LONG_PREAMBLE)) */)
				/*  Short Slot Time */
				pmlmeinfo->slotTime = SHORT_SLOT_TIME;
			अन्यथा
				/*  Long Slot Time */
				pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
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
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *cur_network = &(pmlmeinfo->network);
	अचिन्हित अक्षर *rate = cur_network->SupportedRates;

	अगर ((pmlmeinfo->HT_info_enable) && (pmlmeinfo->HT_caps_enable))
		pmlmeinfo->HT_enable = 1;

	अगर (pmlmeinfo->VHT_enable)
		network_type = WIRELESS_11AC;
	अन्यथा अगर (pmlmeinfo->HT_enable)
		network_type = WIRELESS_11_24N;

	अगर (rtw_is_cckratesonly_included(rate))
		network_type |= WIRELESS_11B;
	अन्यथा अगर (rtw_is_cckrates_included(rate))
		network_type |= WIRELESS_11BG;
	अन्यथा
		network_type |= WIRELESS_11G;

	pmlmeext->cur_wireless_mode = network_type & padapter->registrypriv.wireless_mode;

	SIFS_Timer = 0x0a0a0808; /* 0x0808 -> क्रम CCK, 0x0a0a -> क्रम OFDM */
													/* change this value अगर having IOT issues. */

	padapter->HalFunc.SetHwRegHandler(padapter, HW_VAR_RESP_SIFS,  (u8 *)&SIFS_Timer);

	padapter->HalFunc.SetHwRegHandler(padapter, HW_VAR_WIRELESS_MODE,  (u8 *)&(pmlmeext->cur_wireless_mode));

	अगर (pmlmeext->cur_wireless_mode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	अन्यथा
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);
पूर्ण

व्योम update_sta_basic_rate(काष्ठा sta_info *psta, u8 wireless_mode)
अणु
	अगर (IsSupportedTxCCK(wireless_mode)) अणु
		/*  Only B, B/G, and B/G/N AP could use CCK rate */
		स_नकल(psta->bssrateset, rtw_basic_rate_cck, 4);
		psta->bssratelen = 4;
	पूर्ण अन्यथा अणु
		स_नकल(psta->bssrateset, rtw_basic_rate_ofdm, 3);
		psta->bssratelen = 3;
	पूर्ण
पूर्ण

पूर्णांक update_sta_support_rate(काष्ठा adapter *padapter, u8 *pvar_ie, uपूर्णांक var_ie_len, पूर्णांक cam_idx)
अणु
	अचिन्हित पूर्णांक	ie_len;
	काष्ठा ndis_80211_var_ie *pIE;
	पूर्णांक	supportRateNum = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pIE = (काष्ठा ndis_80211_var_ie *)rtw_get_ie(pvar_ie, WLAN_EID_SUPP_RATES, &ie_len, var_ie_len);
	अगर (!pIE)
		वापस _FAIL;
	अगर (ie_len > माप(pmlmeinfo->FW_sta_info[cam_idx].SupportedRates))
		वापस _FAIL;

	स_नकल(pmlmeinfo->FW_sta_info[cam_idx].SupportedRates, pIE->data, ie_len);
	supportRateNum = ie_len;

	pIE = (काष्ठा ndis_80211_var_ie *)rtw_get_ie(pvar_ie, WLAN_EID_EXT_SUPP_RATES, &ie_len, var_ie_len);
	अगर (pIE && (ie_len <= माप(pmlmeinfo->FW_sta_info[cam_idx].SupportedRates) - supportRateNum))
		स_नकल((pmlmeinfo->FW_sta_info[cam_idx].SupportedRates + supportRateNum), pIE->data, ie_len);

	वापस _SUCCESS;
पूर्ण

व्योम process_addba_req(काष्ठा adapter *padapter, u8 *paddba_req, u8 *addr)
अणु
	काष्ठा sta_info *psta;
	u16 tid, start_seq, param;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा ADDBA_request *preq = (काष्ठा ADDBA_request *)paddba_req;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	psta = rtw_get_stainfo(pstapriv, addr);

	अगर (psta) अणु
		start_seq = le16_to_cpu(preq->BA_starting_seqctrl) >> 4;

		param = le16_to_cpu(preq->BA_para_set);
		tid = (param>>2)&0x0f;

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

	pmlmeext->TSFValue = le32_to_cpu(*(pbuf+1));

	pmlmeext->TSFValue = pmlmeext->TSFValue << 32;

	pmlmeext->TSFValue |= le32_to_cpu(*pbuf);
पूर्ण

व्योम correct_TSF(काष्ठा adapter *padapter, काष्ठा mlme_ext_priv *pmlmeext)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_CORRECT_TSF, शून्य);
पूर्ण

व्योम adaptive_early_32k(काष्ठा mlme_ext_priv *pmlmeext, u8 *pframe, uपूर्णांक len)
अणु
	पूर्णांक i;
	u8 *pIE;
	__le32 *pbuf;
	u64 tsf = 0;
	u32 delay_ms;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pmlmeext->bcn_cnt++;

	pIE = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	pbuf = (__le32 *)pIE;

	tsf = le32_to_cpu(*(pbuf+1));
	tsf = tsf << 32;
	tsf |= le32_to_cpu(*pbuf);

	/* delay = (बारtamp mod 1024*100)/1000 (unit: ms) */
	/* delay_ms = करो_भाग(tsf, (pmlmeinfo->bcn_पूर्णांकerval*1024))/1000; */
	delay_ms = करो_भाग(tsf, (pmlmeinfo->bcn_पूर्णांकerval*1024));
	delay_ms = delay_ms/1000;

	अगर (delay_ms >= 8)
		pmlmeext->bcn_delay_cnt[8]++;
		/* pmlmeext->bcn_delay_ratio[8] = (pmlmeext->bcn_delay_cnt[8] * 100) /pmlmeext->bcn_cnt; */
	अन्यथा
		pmlmeext->bcn_delay_cnt[delay_ms]++;
		/* pmlmeext->bcn_delay_ratio[delay_ms] = (pmlmeext->bcn_delay_cnt[delay_ms] * 100) /pmlmeext->bcn_cnt; */

/*

	क्रम (i = 0; i<9; i++)
	अणु
			pmlmeext->bcn_delay_cnt[i] , i, pmlmeext->bcn_delay_ratio[i]);
	पूर्ण
*/

	/* dump क्रम  adaptive_early_32k */
	अगर (pmlmeext->bcn_cnt > 100 && (pmlmeext->adaptive_tsf_करोne == true)) अणु
		u8 ratio_20_delay, ratio_80_delay;
		u8 DrvBcnEarly, DrvBcnTimeOut;

		ratio_20_delay = 0;
		ratio_80_delay = 0;
		DrvBcnEarly = 0xff;
		DrvBcnTimeOut = 0xff;

		क्रम (i = 0; i < 9; i++) अणु
			pmlmeext->bcn_delay_ratio[i] = (pmlmeext->bcn_delay_cnt[i] * 100) / pmlmeext->bcn_cnt;

			ratio_20_delay += pmlmeext->bcn_delay_ratio[i];
			ratio_80_delay += pmlmeext->bcn_delay_ratio[i];

			अगर (ratio_20_delay > 20 && DrvBcnEarly == 0xff)
				DrvBcnEarly = i;

			अगर (ratio_80_delay > 80 && DrvBcnTimeOut == 0xff)
				DrvBcnTimeOut = i;

			/* reset adaptive_early_32k cnt */
			pmlmeext->bcn_delay_cnt[i] = 0;
			pmlmeext->bcn_delay_ratio[i] = 0;
		पूर्ण

		pmlmeext->DrvBcnEarly = DrvBcnEarly;
		pmlmeext->DrvBcnTimeOut = DrvBcnTimeOut;

		pmlmeext->bcn_cnt = 0;
	पूर्ण
पूर्ण

व्योम rtw_alloc_macid(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक i;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(padapter);

	अगर (!स_भेद(psta->hwaddr, bc_addr, ETH_ALEN))
		वापस;

	अगर (!स_भेद(psta->hwaddr, myid(&padapter->eeprompriv), ETH_ALEN)) अणु
		psta->mac_id = NUM_STA;
		वापस;
	पूर्ण

	spin_lock_bh(&pdvobj->lock);
	क्रम (i = 0; i < NUM_STA; i++) अणु
		अगर (pdvobj->macid[i] == false) अणु
			pdvobj->macid[i]  = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pdvobj->lock);

	अगर (i > (NUM_STA - 1))
		psta->mac_id = NUM_STA;
	अन्यथा
		psta->mac_id = i;
पूर्ण

व्योम rtw_release_macid(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(padapter);

	अगर (!स_भेद(psta->hwaddr, bc_addr, ETH_ALEN))
		वापस;

	अगर (!स_भेद(psta->hwaddr, myid(&padapter->eeprompriv), ETH_ALEN))
		वापस;

	spin_lock_bh(&pdvobj->lock);
	अगर (psta->mac_id < NUM_STA && psta->mac_id != 1) अणु
		अगर (pdvobj->macid[psta->mac_id] == true) अणु
			pdvobj->macid[psta->mac_id] = false;
			psta->mac_id = NUM_STA;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pdvobj->lock);
पूर्ण

/* For 8188E RA */
u8 rtw_search_max_mac_id(काष्ठा adapter *padapter)
अणु
	u8 max_mac_id = 0;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(padapter);
	पूर्णांक i;

	spin_lock_bh(&pdvobj->lock);
	क्रम (i = (NUM_STA-1); i >= 0 ; i--) अणु
		अगर (pdvobj->macid[i] == true)
			अवरोध;
	पूर्ण
	max_mac_id = i;
	spin_unlock_bh(&pdvobj->lock);

	वापस max_mac_id;
पूर्ण

काष्ठा adapter *dvobj_get_port0_adapter(काष्ठा dvobj_priv *dvobj)
अणु
	अगर (get_अगरace_type(dvobj->padapters[i]) != IFACE_PORT0)
		वापस शून्य;

	वापस dvobj->padapters;
पूर्ण
