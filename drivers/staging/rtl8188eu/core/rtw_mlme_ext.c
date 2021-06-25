<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_MLME_EXT_C_

#समावेश <linux/ieee80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wअगरi.h>
#समावेश <rtw_mlme_ext.h>
#समावेश <wlan_bssdef.h>
#समावेश <mlme_osdep.h>
#समावेश <recv_osdep.h>

अटल u8 null_addr[ETH_ALEN] = अणुपूर्ण;

/* OUI definitions क्रम the venकरोr specअगरic IE */
स्थिर u8 RTW_WPA_OUI[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
स्थिर u8 WPS_OUI[] = अणु0x00, 0x50, 0xf2, 0x04पूर्ण;
अटल स्थिर u8 WMM_OUI[] = अणु0x00, 0x50, 0xf2, 0x02पूर्ण;
अटल स्थिर u8 P2P_OUI[] = अणु0x50, 0x6F, 0x9A, 0x09पूर्ण;

अटल स्थिर u8 WMM_PARA_OUI[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;

स्थिर u8 WPA_TKIP_CIPHER[4] = अणु0x00, 0x50, 0xf2, 0x02पूर्ण;
स्थिर u8 RSN_TKIP_CIPHER[4] = अणु0x00, 0x0f, 0xac, 0x02पूर्ण;

/* MCS rate definitions */
स्थिर u8 MCS_rate_1R[16] = अणु
	0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

/* ChannelPlan definitions */
अटल काष्ठा rt_channel_plan_2g RTW_ChannelPlan2G[RT_CHANNEL_DOMAIN_2G_MAX] = अणु
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,		/*  0x00, RT_CHANNEL_DOMAIN_2G_WORLD , Passive scan CH 12, 13 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,		/*  0x01, RT_CHANNEL_DOMAIN_2G_ETSI1 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11पूर्ण, 11पूर्ण,			/*  0x02, RT_CHANNEL_DOMAIN_2G_FCC1 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14पूर्ण, 14पूर्ण,	/*  0x03, RT_CHANNEL_DOMAIN_2G_MIKK1 */
	अणुअणु10, 11, 12, 13पूर्ण, 4पूर्ण,					/*  0x04, RT_CHANNEL_DOMAIN_2G_ETSI2 */
	अणुअणुपूर्ण, 0पूर्ण,									/*  0x05, RT_CHANNEL_DOMAIN_2G_शून्य */
पूर्ण;

अटल काष्ठा rt_channel_plan_map RTW_ChannelPlanMap[RT_CHANNEL_DOMAIN_MAX] = अणु
	/*  0x00 ~ 0x1F , Old Define ===== */
	अणु0x02पूर्ण,	/* 0x00, RT_CHANNEL_DOMAIN_FCC */
	अणु0x02पूर्ण,	/* 0x01, RT_CHANNEL_DOMAIN_IC */
	अणु0x01पूर्ण,	/* 0x02, RT_CHANNEL_DOMAIN_ETSI */
	अणु0x01पूर्ण,	/* 0x03, RT_CHANNEL_DOMAIN_SPAIN */
	अणु0x01पूर्ण,	/* 0x04, RT_CHANNEL_DOMAIN_FRANCE */
	अणु0x03पूर्ण,	/* 0x05, RT_CHANNEL_DOMAIN_MKK */
	अणु0x03पूर्ण,	/* 0x06, RT_CHANNEL_DOMAIN_MKK1 */
	अणु0x01पूर्ण,	/* 0x07, RT_CHANNEL_DOMAIN_ISRAEL */
	अणु0x03पूर्ण,	/* 0x08, RT_CHANNEL_DOMAIN_TELEC */
	अणु0x03पूर्ण,	/* 0x09, RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN */
	अणु0x00पूर्ण,	/* 0x0A, RT_CHANNEL_DOMAIN_WORLD_WIDE_13 */
	अणु0x02पूर्ण,	/* 0x0B, RT_CHANNEL_DOMAIN_TAIWAN */
	अणु0x01पूर्ण,	/* 0x0C, RT_CHANNEL_DOMAIN_CHINA */
	अणु0x02पूर्ण,	/* 0x0D, RT_CHANNEL_DOMAIN_SINGAPORE_INDIA_MEXICO */
	अणु0x02पूर्ण,	/* 0x0E, RT_CHANNEL_DOMAIN_KOREA */
	अणु0x02पूर्ण,	/* 0x0F, RT_CHANNEL_DOMAIN_TURKEY */
	अणु0x01पूर्ण,	/* 0x10, RT_CHANNEL_DOMAIN_JAPAN */
	अणु0x02पूर्ण,	/* 0x11, RT_CHANNEL_DOMAIN_FCC_NO_DFS */
	अणु0x01पूर्ण,	/* 0x12, RT_CHANNEL_DOMAIN_JAPAN_NO_DFS */
	अणु0x00पूर्ण,	/* 0x13, RT_CHANNEL_DOMAIN_WORLD_WIDE_5G */
	अणु0x02पूर्ण,	/* 0x14, RT_CHANNEL_DOMAIN_TAIWAN_NO_DFS */
	अणु0x00पूर्ण,	/* 0x15, RT_CHANNEL_DOMAIN_ETSI_NO_DFS */
	अणु0x00पूर्ण,	/* 0x16, RT_CHANNEL_DOMAIN_KOREA_NO_DFS */
	अणु0x03पूर्ण,	/* 0x17, RT_CHANNEL_DOMAIN_JAPAN_NO_DFS */
	अणु0x05पूर्ण,	/* 0x18, RT_CHANNEL_DOMAIN_PAKISTAN_NO_DFS */
	अणु0x02पूर्ण,	/* 0x19, RT_CHANNEL_DOMAIN_TAIWAN2_NO_DFS */
	अणु0x00पूर्ण,	/* 0x1A, */
	अणु0x00पूर्ण,	/* 0x1B, */
	अणु0x00पूर्ण,	/* 0x1C, */
	अणु0x00पूर्ण,	/* 0x1D, */
	अणु0x00पूर्ण,	/* 0x1E, */
	अणु0x05पूर्ण,	/* 0x1F, RT_CHANNEL_DOMAIN_WORLD_WIDE_ONLY_5G */
	/*  0x20 ~ 0x7F , New Define ===== */
	अणु0x00पूर्ण,	/* 0x20, RT_CHANNEL_DOMAIN_WORLD_शून्य */
	अणु0x01पूर्ण,	/* 0x21, RT_CHANNEL_DOMAIN_ETSI1_शून्य */
	अणु0x02पूर्ण,	/* 0x22, RT_CHANNEL_DOMAIN_FCC1_शून्य */
	अणु0x03पूर्ण,	/* 0x23, RT_CHANNEL_DOMAIN_MKK1_शून्य */
	अणु0x04पूर्ण,	/* 0x24, RT_CHANNEL_DOMAIN_ETSI2_शून्य */
	अणु0x02पूर्ण,	/* 0x25, RT_CHANNEL_DOMAIN_FCC1_FCC1 */
	अणु0x00पूर्ण,	/* 0x26, RT_CHANNEL_DOMAIN_WORLD_ETSI1 */
	अणु0x03पूर्ण,	/* 0x27, RT_CHANNEL_DOMAIN_MKK1_MKK1 */
	अणु0x00पूर्ण,	/* 0x28, RT_CHANNEL_DOMAIN_WORLD_KCC1 */
	अणु0x00पूर्ण,	/* 0x29, RT_CHANNEL_DOMAIN_WORLD_FCC2 */
	अणु0x00पूर्ण,	/* 0x2A, */
	अणु0x00पूर्ण,	/* 0x2B, */
	अणु0x00पूर्ण,	/* 0x2C, */
	अणु0x00पूर्ण,	/* 0x2D, */
	अणु0x00पूर्ण,	/* 0x2E, */
	अणु0x00पूर्ण,	/* 0x2F, */
	अणु0x00पूर्ण,	/* 0x30, RT_CHANNEL_DOMAIN_WORLD_FCC3 */
	अणु0x00पूर्ण,	/* 0x31, RT_CHANNEL_DOMAIN_WORLD_FCC4 */
	अणु0x00पूर्ण,	/* 0x32, RT_CHANNEL_DOMAIN_WORLD_FCC5 */
	अणु0x00पूर्ण,	/* 0x33, RT_CHANNEL_DOMAIN_WORLD_FCC6 */
	अणु0x02पूर्ण,	/* 0x34, RT_CHANNEL_DOMAIN_FCC1_FCC7 */
	अणु0x00पूर्ण,	/* 0x35, RT_CHANNEL_DOMAIN_WORLD_ETSI2 */
	अणु0x00पूर्ण,	/* 0x36, RT_CHANNEL_DOMAIN_WORLD_ETSI3 */
	अणु0x03पूर्ण,	/* 0x37, RT_CHANNEL_DOMAIN_MKK1_MKK2 */
	अणु0x03पूर्ण,	/* 0x38, RT_CHANNEL_DOMAIN_MKK1_MKK3 */
	अणु0x02पूर्ण,	/* 0x39, RT_CHANNEL_DOMAIN_FCC1_NCC1 */
	अणु0x00पूर्ण,	/* 0x3A, */
	अणु0x00पूर्ण,	/* 0x3B, */
	अणु0x00पूर्ण,	/* 0x3C, */
	अणु0x00पूर्ण,	/* 0x3D, */
	अणु0x00पूर्ण,	/* 0x3E, */
	अणु0x00पूर्ण,	/* 0x3F, */
	अणु0x02पूर्ण,	/* 0x40, RT_CHANNEL_DOMAIN_FCC1_NCC2 */
	अणु0x03पूर्ण,	/* 0x41, RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN_2G */
पूर्ण;

अटल स्थिर काष्ठा rt_channel_plan_map RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE = अणु
	0x03
पूर्ण; /* use the combination क्रम max channel numbers */

/*
 * Search the @param channel_num in given @param channel_set
 * @ch_set: the given channel set
 * @ch: the given channel number
 *
 * वापस the index of channel_num in channel_set, -1 अगर not found
 */
पूर्णांक rtw_ch_set_search_ch(काष्ठा rt_channel_info *ch_set, स्थिर u32 ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; ch_set[i].ChannelNum != 0; i++) अणु
		अगर (ch == ch_set[i].ChannelNum)
			अवरोध;
	पूर्ण

	अगर (i >= ch_set[i].ChannelNum)
		वापस -1;
	वापस i;
पूर्ण

काष्ठा xmit_frame *alloc_mgtxmitframe(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा xmit_buf *pxmitbuf;

	pmgntframe = rtw_alloc_xmitframe(pxmitpriv);
	अगर (!pmgntframe) अणु
		DBG_88E("%s, alloc xmitframe fail\n", __func__);
		वापस शून्य;
	पूर्ण

	pxmitbuf = rtw_alloc_xmitbuf_ext(pxmitpriv);
	अगर (!pxmitbuf) अणु
		DBG_88E("%s, alloc xmitbuf fail\n", __func__);
		rtw_मुक्त_xmitframe(pxmitpriv, pmgntframe);
		वापस शून्य;
	पूर्ण
	pmgntframe->frame_tag = MGNT_FRAMETAG;
	pmgntframe->pxmitbuf = pxmitbuf;
	pmgntframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pmgntframe;
	वापस pmgntframe;
पूर्ण

/****************************************************************************

Following are some TX functions क्रम WiFi MLME

*****************************************************************************/

व्योम update_mgnt_tx_rate(काष्ठा adapter *padapter, u8 rate)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	pmlmeext->tx_rate = rate;
	DBG_88E("%s(): rate = %x\n", __func__, rate);
पूर्ण

व्योम update_mgntframe_attrib(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	स_रखो((u8 *)(pattrib), 0, माप(काष्ठा pkt_attrib));

	pattrib->hdrlen = 24;
	pattrib->nr_frags = 1;
	pattrib->priority = 7;
	pattrib->mac_id = 0;
	pattrib->qsel = 0x12;

	pattrib->pktlen = 0;

	अगर (pmlmeext->cur_wireless_mode & WIRELESS_11B)
		pattrib->raid = 6;/* b mode */
	अन्यथा
		pattrib->raid = 5;/* a/g mode */

	pattrib->encrypt = _NO_PRIVACY_;
	pattrib->bswenc = false;

	pattrib->qos_en = false;
	pattrib->ht_en = false;
	pattrib->bwmode = HT_CHANNEL_WIDTH_20;
	pattrib->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pattrib->sgi = false;

	pattrib->seqnum = pmlmeext->mgnt_seq;

	pattrib->retry_ctrl = true;
पूर्ण

अटल व्योम dump_mgntframe(काष्ठा adapter *padapter,
			   काष्ठा xmit_frame *pmgntframe)
अणु
	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस;

	rtw_hal_mgnt_xmit(padapter, pmgntframe);
पूर्ण

अटल s32 dump_mgntframe_and_रुको(काष्ठा adapter *padapter,
				   काष्ठा xmit_frame *pmgntframe,
				   पूर्णांक समयout_ms)
अणु
	s32 ret = _FAIL;
	काष्ठा xmit_buf *pxmitbuf = pmgntframe->pxmitbuf;
	काष्ठा submit_ctx sctx;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस ret;

	rtw_sctx_init(&sctx, समयout_ms);
	pxmitbuf->sctx = &sctx;

	ret = rtw_hal_mgnt_xmit(padapter, pmgntframe);

	अगर (ret == _SUCCESS)
		ret = rtw_sctx_रुको(&sctx);

	वापस ret;
पूर्ण

अटल s32 dump_mgntframe_and_रुको_ack(काष्ठा adapter *padapter,
				       काष्ठा xmit_frame *pmgntframe)
अणु
	s32 ret = _FAIL;
	u32 समयout_ms = 500;/*   500ms */
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस -1;

	अगर (mutex_lock_पूर्णांकerruptible(&pxmitpriv->ack_tx_mutex))
		वापस _FAIL;
	pxmitpriv->ack_tx = true;

	pmgntframe->ack_report = 1;
	अगर (rtw_hal_mgnt_xmit(padapter, pmgntframe) == _SUCCESS)
		ret = rtw_ack_tx_रुको(pxmitpriv, समयout_ms);

	pxmitpriv->ack_tx = false;
	mutex_unlock(&pxmitpriv->ack_tx_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक update_hidden_ssid(u8 *ies, u32 ies_len, u8 hidden_ssid_mode)
अणु
	u8 *ssid_ie;
	uपूर्णांक ssid_len_ori;
	पूर्णांक len_dअगरf = 0;

	ssid_ie = rtw_get_ie(ies,  WLAN_EID_SSID, &ssid_len_ori, ies_len);

	अगर (ssid_ie && ssid_len_ori > 0) अणु
		चयन (hidden_ssid_mode) अणु
		हाल 1: अणु
			u8 *next_ie = ssid_ie + 2 + ssid_len_ori;
			u32 reमुख्य_len = 0;

			reमुख्य_len = ies_len - (next_ie - ies);

			ssid_ie[1] = 0;
			स_नकल(ssid_ie + 2, next_ie, reमुख्य_len);
			len_dअगरf -= ssid_len_ori;

			अवरोध;
		पूर्ण
		हाल 2:
			स_रखो(&ssid_ie[2], 0, ssid_len_ori);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस len_dअगरf;
पूर्ण

अटल व्योम issue_beacon(काष्ठा adapter *padapter, पूर्णांक समयout_ms)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित पूर्णांक rate_len;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe) अणु
		DBG_88E("%s, alloc mgnt frame fail\n", __func__);
		वापस;
	पूर्ण
#अगर defined(CONFIG_88EU_AP_MODE)
	spin_lock_bh(&pmlmepriv->bcn_update_lock);
#पूर्ण_अगर

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->qsel = 0x10;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, bc_addr);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, cur_network->MacAddress);

	SetSeqNum(pwlanhdr, 0/*pmlmeext->mgnt_seq*/);
	/* pmlmeext->mgnt_seq++; */
	SetFrameSubType(pframe, WIFI_BEACON);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE) अणु
		पूर्णांक len_dअगरf;
		u8 *wps_ie;
		uपूर्णांक wps_ielen;
		u8 sr = 0;

		स_नकल(pframe, cur_network->ies, cur_network->ie_length);
		len_dअगरf = update_hidden_ssid(
			pframe + _BEACON_IE_OFFSET_
			, cur_network->ie_length - _BEACON_IE_OFFSET_
			, pmlmeinfo->hidden_ssid_mode
			);
		pframe += (cur_network->ie_length + len_dअगरf);
		pattrib->pktlen += (cur_network->ie_length + len_dअगरf);
		wps_ie = rtw_get_wps_ie(pmgntframe->buf_addr + TXDESC_OFFSET + माप(काष्ठा ieee80211_hdr_3addr) + _BEACON_IE_OFFSET_,
					pattrib->pktlen - माप(काष्ठा ieee80211_hdr_3addr) - _BEACON_IE_OFFSET_, शून्य, &wps_ielen);
		अगर (wps_ie && wps_ielen > 0)
			rtw_get_wps_attr_content(wps_ie,  wps_ielen, WPS_ATTR_SELECTED_REGISTRAR, (u8 *)(&sr), शून्य);
		अगर (sr != 0)
			set_fwstate(pmlmepriv, WIFI_UNDER_WPS);
		अन्यथा
			_clr_fwstate_(pmlmepriv, WIFI_UNDER_WPS);

		जाओ _issue_bcn;
	पूर्ण

	/* below क्रम ad-hoc mode */

	/* बारtamp will be inserted by hardware */
	pframe += 8;
	pattrib->pktlen += 8;

	/*  beacon पूर्णांकerval: 2 bytes */

	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->ies)), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/*  capability info: 2 bytes */

	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->ies)), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/*  SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->ssid.ssid_length, cur_network->ssid.ssid, &pattrib->pktlen);

	/*  supported rates... */
	rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
	pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, min_t(अचिन्हित पूर्णांक, rate_len, 8), cur_network->SupportedRates, &pattrib->pktlen);

	/*  DS parameter set */
	pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&cur_network->Configuration.DSConfig, &pattrib->pktlen);

	अणु
		u8 erpinfo = 0;
		u32 ATIMWinकरोw;
		/*  IBSS Parameter Set... */
		ATIMWinकरोw = 0;
		pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pattrib->pktlen);

		/* ERP IE */
		pframe = rtw_set_ie(pframe, WLAN_EID_ERP_INFO, 1, &erpinfo, &pattrib->pktlen);
	पूर्ण

	/*  EXTERNDED SUPPORTED RATE */
	अगर (rate_len > 8)
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pattrib->pktlen);
	/* toकरो:HT क्रम adhoc */
_issue_bcn:

#अगर defined(CONFIG_88EU_AP_MODE)
	pmlmepriv->update_bcn = false;

	spin_unlock_bh(&pmlmepriv->bcn_update_lock);
#पूर्ण_अगर

	अगर ((pattrib->pktlen + TXDESC_SIZE) > 512) अणु
		DBG_88E("beacon frame too large\n");
		वापस;
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	/* DBG_88E("issue bcn_sz=%d\n", pattrib->last_txcmdsz); */
	अगर (समयout_ms > 0)
		dump_mgntframe_and_रुको(padapter, pmgntframe, समयout_ms);
	अन्यथा
		dump_mgntframe(padapter, pmgntframe);
पूर्ण

अटल व्योम issue_probersp(काष्ठा adapter *padapter, अचिन्हित अक्षर *da)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित अक्षर *mac, *bssid;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
#अगर defined(CONFIG_88EU_AP_MODE)
	u8 *pwps_ie;
	uपूर्णांक wps_ielen;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
#पूर्ण_अगर
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;
	अचिन्हित पूर्णांक rate_len;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe) अणु
		DBG_88E("%s, alloc mgnt frame fail\n", __func__);
		वापस;
	पूर्ण

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	mac = myid(&padapter->eeprompriv);
	bssid = cur_network->MacAddress;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, mac);
	ether_addr_copy(pwlanhdr->addr3, bssid);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(fctrl, WIFI_PROBERSP);

	pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = pattrib->hdrlen;
	pframe += pattrib->hdrlen;

	अगर (cur_network->ie_length > MAX_IE_SZ)
		वापस;

#अगर defined(CONFIG_88EU_AP_MODE)
	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE) अणु
		pwps_ie = rtw_get_wps_ie(cur_network->ies + _FIXED_IE_LENGTH_, cur_network->ie_length - _FIXED_IE_LENGTH_, शून्य, &wps_ielen);

		/* inerset & update wps_probe_resp_ie */
		अगर (pmlmepriv->wps_probe_resp_ie && pwps_ie && wps_ielen > 0) अणु
			uपूर्णांक wps_offset, reमुख्यder_ielen;
			u8 *preमुख्यder_ie;

			wps_offset = (uपूर्णांक)(pwps_ie - cur_network->ies);

			preमुख्यder_ie = pwps_ie + wps_ielen;

			reमुख्यder_ielen = cur_network->ie_length - wps_offset - wps_ielen;

			स_नकल(pframe, cur_network->ies, wps_offset);
			pframe += wps_offset;
			pattrib->pktlen += wps_offset;

			wps_ielen = (uपूर्णांक)pmlmepriv->wps_probe_resp_ie[1];/* to get ie data len */
			अगर ((wps_offset + wps_ielen + 2) <= MAX_IE_SZ) अणु
				स_नकल(pframe, pmlmepriv->wps_probe_resp_ie, wps_ielen + 2);
				pframe += wps_ielen + 2;
				pattrib->pktlen += wps_ielen + 2;
			पूर्ण

			अगर ((wps_offset + wps_ielen + 2 + reमुख्यder_ielen) <= MAX_IE_SZ) अणु
				स_नकल(pframe, preमुख्यder_ie, reमुख्यder_ielen);
				pframe += reमुख्यder_ielen;
				pattrib->pktlen += reमुख्यder_ielen;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(pframe, cur_network->ies, cur_network->ie_length);
			pframe += cur_network->ie_length;
			pattrib->pktlen += cur_network->ie_length;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* बारtamp will be inserted by hardware */
		pframe += 8;
		pattrib->pktlen += 8;

		/*  beacon पूर्णांकerval: 2 bytes */

		स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->ies)), 2);

		pframe += 2;
		pattrib->pktlen += 2;

		/*  capability info: 2 bytes */

		स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->ies)), 2);

		pframe += 2;
		pattrib->pktlen += 2;

		/* below क्रम ad-hoc mode */

		/*  SSID */
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->ssid.ssid_length, cur_network->ssid.ssid, &pattrib->pktlen);

		/*  supported rates... */
		rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, min_t(अचिन्हित पूर्णांक, rate_len, 8), cur_network->SupportedRates, &pattrib->pktlen);

		/*  DS parameter set */
		pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&cur_network->Configuration.DSConfig, &pattrib->pktlen);

		अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) अणु
			u8 erpinfo = 0;
			u32 ATIMWinकरोw;
			/*  IBSS Parameter Set... */
			/* ATIMWinकरोw = cur->Configuration.ATIMWinकरोw; */
			ATIMWinकरोw = 0;
			pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pattrib->pktlen);

			/* ERP IE */
			pframe = rtw_set_ie(pframe, WLAN_EID_ERP_INFO, 1, &erpinfo, &pattrib->pktlen);
		पूर्ण

		/*  EXTERNDED SUPPORTED RATE */
		अगर (rate_len > 8)
			pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pattrib->pktlen);
		/* toकरो:HT क्रम adhoc */
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

अटल पूर्णांक issue_probereq(काष्ठा adapter *padapter,
			  काष्ठा ndis_802_11_ssid *pssid, u8 *da,
			  bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित अक्षर *mac;
	अचिन्हित अक्षर bssrate[NumRates];
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	पूर्णांक bssrate_len = 0;
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+%s\n", __func__));

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	mac = myid(&padapter->eeprompriv);

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	अगर (da) अणु
		/*	unicast probe request frame */
		ether_addr_copy(pwlanhdr->addr1, da);
		ether_addr_copy(pwlanhdr->addr3, da);
	पूर्ण अन्यथा अणु
		/*	broadcast probe request frame */
		ether_addr_copy(pwlanhdr->addr1, bc_addr);
		ether_addr_copy(pwlanhdr->addr3, bc_addr);
	पूर्ण

	ether_addr_copy(pwlanhdr->addr2, mac);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_PROBEREQ);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	अगर (pssid)
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, pssid->ssid_length, pssid->ssid, &pattrib->pktlen);
	अन्यथा
		pframe = rtw_set_ie(pframe, WLAN_EID_SSID, 0, शून्य, &pattrib->pktlen);

	get_rate_set(padapter, bssrate, &bssrate_len);

	अगर (bssrate_len > 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, bssrate, &pattrib->pktlen);
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, bssrate_len - 8, bssrate + 8, &pattrib->pktlen);
	पूर्ण अन्यथा अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, bssrate_len, bssrate, &pattrib->pktlen);
	पूर्ण

	/* add wps_ie क्रम wps2.0 */
	अगर (pmlmepriv->wps_probe_req_ie_len > 0 && pmlmepriv->wps_probe_req_ie) अणु
		स_नकल(pframe, pmlmepriv->wps_probe_req_ie, pmlmepriv->wps_probe_req_ie_len);
		pframe += pmlmepriv->wps_probe_req_ie_len;
		pattrib->pktlen += pmlmepriv->wps_probe_req_ie_len;
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
		 ("issuing probe_req, tx_len=%d\n", pattrib->last_txcmdsz));

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक issue_probereq_ex(काष्ठा adapter *padapter,
			     काष्ठा ndis_802_11_ssid *pssid, u8 *da,
			     पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ start = jअगरfies;

	करो अणु
		ret = issue_probereq(padapter, pssid, da, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);

	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण

	अगर (try_cnt && रुको_ms) अणु
		अगर (da)
			DBG_88E(FUNC_ADPT_FMT" to %pM, ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), da, rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
		अन्यथा
			DBG_88E(FUNC_ADPT_FMT", ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
	पूर्ण
निकास:
	वापस ret;
पूर्ण

/*  अगर psta == शून्य, indicate we are station(client) now... */
अटल व्योम issue_auth(काष्ठा adapter *padapter, काष्ठा sta_info *psta,
		       अचिन्हित लघु status)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित पूर्णांक val32;
	u16 val16;
#अगर_घोषित CONFIG_88EU_AP_MODE
	__le16 le_val16;
#पूर्ण_अगर
	पूर्णांक use_shared_key = 0;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_AUTH);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	अगर (psta) अणु/*  क्रम AP mode */
#अगर_घोषित CONFIG_88EU_AP_MODE

		ether_addr_copy(pwlanhdr->addr1, psta->hwaddr);
		ether_addr_copy(pwlanhdr->addr2,
				myid(&padapter->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3,
				myid(&padapter->eeprompriv));

		/*  setting auth algo number */
		val16 = (u16)psta->authalg;

		अगर (status != WLAN_STATUS_SUCCESS)
			val16 = 0;

		अगर (val16) अणु
			le_val16 = cpu_to_le16(val16);
			use_shared_key = 1;
		पूर्ण अन्यथा अणु
			le_val16 = 0;
		पूर्ण

		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, &le_val16,
					  &pattrib->pktlen);

		/*  setting auth seq number */
		val16 = (u16)psta->auth_seq;
		le_val16 = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, &le_val16,
					  &pattrib->pktlen);

		/*  setting status code... */
		val16 = status;
		le_val16 = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_,
					  &le_val16, &pattrib->pktlen);

		/*  added challenging text... */
		अगर ((psta->auth_seq == 2) && (psta->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1))
			pframe = rtw_set_ie(pframe, WLAN_EID_CHALLENGE, 128, psta->chg_txt, &pattrib->pktlen);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		__le32 le_पंचांगp32;
		__le16 le_पंचांगp16;

		ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);
		ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

		/*  setting auth algo number */
		val16 = (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared) ? 1 : 0;/*  0:OPEN System, 1:Shared key */
		अगर (val16)
			use_shared_key = 1;

		/* setting IV क्रम auth seq #3 */
		अगर ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1)) अणु
			val32 = (pmlmeinfo->iv++) | (pmlmeinfo->key_index << 30);
			le_पंचांगp32 = cpu_to_le32(val32);
			pframe = rtw_set_fixed_ie(pframe, 4, &le_पंचांगp32,
						  &pattrib->pktlen);

			pattrib->iv_len = 4;
		पूर्ण

		le_पंचांगp16 = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _AUTH_ALGM_NUM_, &le_पंचांगp16,
					  &pattrib->pktlen);

		/*  setting auth seq number */
		val16 = pmlmeinfo->auth_seq;
		le_पंचांगp16 = cpu_to_le16(val16);
		pframe = rtw_set_fixed_ie(pframe, _AUTH_SEQ_NUM_, &le_पंचांगp16,
					  &pattrib->pktlen);

		/*  setting status code... */
		le_पंचांगp16 = cpu_to_le16(status);
		pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, &le_पंचांगp16,
					  &pattrib->pktlen);

		/*  then checking to see अगर sending challenging text... */
		अगर ((pmlmeinfo->auth_seq == 3) && (pmlmeinfo->state & WIFI_FW_AUTH_STATE) && (use_shared_key == 1)) अणु
			pframe = rtw_set_ie(pframe, WLAN_EID_CHALLENGE, 128, pmlmeinfo->chg_txt, &pattrib->pktlen);

			SetPrivacy(fctrl);

			pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);

			pattrib->encrypt = _WEP40_;

			pattrib->icv_len = 4;

			pattrib->pktlen += pattrib->icv_len;
		पूर्ण
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	rtw_wep_encrypt(padapter, pmgntframe);
	DBG_88E("%s\n", __func__);
	dump_mgntframe(padapter, pmgntframe);
पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE
अटल व्योम issue_asocrsp(काष्ठा adapter *padapter, अचिन्हित लघु status,
			  काष्ठा sta_info *pstat, पूर्णांक pkt_type)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pbuf, *pframe;
	अचिन्हित लघु val;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	u8 *ie = pnetwork->ies;
	__le16 lestatus, leval;

	DBG_88E("%s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy((व्योम *)GetAddr1Ptr(pwlanhdr), pstat->hwaddr);
	ether_addr_copy((व्योम *)GetAddr2Ptr(pwlanhdr),
			myid(&padapter->eeprompriv));
	ether_addr_copy((व्योम *)GetAddr3Ptr(pwlanhdr), pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	अगर ((pkt_type == WIFI_ASSOCRSP) || (pkt_type == WIFI_REASSOCRSP))
		SetFrameSubType(pwlanhdr, pkt_type);
	अन्यथा
		वापस;

	pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen += pattrib->hdrlen;
	pframe += pattrib->hdrlen;

	/* capability */
	val = *(अचिन्हित लघु *)rtw_get_capability_from_ie(ie);

	pframe = rtw_set_fixed_ie(pframe, _CAPABILITY_, &val, &pattrib->pktlen);

	lestatus = cpu_to_le16(status);
	pframe = rtw_set_fixed_ie(pframe, _STATUS_CODE_, &lestatus,
				  &pattrib->pktlen);

	leval = cpu_to_le16(pstat->aid | BIT(14) | BIT(15));
	pframe = rtw_set_fixed_ie(pframe, _ASOC_ID_, &leval, &pattrib->pktlen);

	अगर (pstat->bssratelen <= 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, pstat->bssratelen, pstat->bssrateset, &pattrib->pktlen);
	पूर्ण अन्यथा अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, pstat->bssrateset, &pattrib->pktlen);
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, pstat->bssratelen - 8, pstat->bssrateset + 8, &pattrib->pktlen);
	पूर्ण

	अगर ((pstat->flags & WLAN_STA_HT) && (pmlmepriv->htpriv.ht_option)) अणु
		uपूर्णांक ie_len = 0;

		/* FILL HT CAP INFO IE */
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_CAPABILITY, &ie_len, (pnetwork->ie_length - _BEACON_IE_OFFSET_));
		अगर (pbuf && ie_len > 0) अणु
			स_नकल(pframe, pbuf, ie_len + 2);
			pframe += (ie_len + 2);
			pattrib->pktlen += (ie_len + 2);
		पूर्ण

		/* FILL HT ADD INFO IE */
		pbuf = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_OPERATION, &ie_len, (pnetwork->ie_length - _BEACON_IE_OFFSET_));
		अगर (pbuf && ie_len > 0) अणु
			स_नकल(pframe, pbuf, ie_len + 2);
			pframe += (ie_len + 2);
			pattrib->pktlen += (ie_len + 2);
		पूर्ण
	पूर्ण

	/* FILL WMM IE */
	अगर ((pstat->flags & WLAN_STA_WME) && (pmlmepriv->qospriv.qos_option)) अणु
		uपूर्णांक ie_len = 0;
		अचिन्हित अक्षर WMM_PARA_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;

		क्रम (pbuf = ie + _BEACON_IE_OFFSET_;; pbuf += (ie_len + 2)) अणु
			pbuf = rtw_get_ie(pbuf, WLAN_EID_VENDOR_SPECIFIC, &ie_len, (pnetwork->ie_length - _BEACON_IE_OFFSET_ - (ie_len + 2)));
			अगर (pbuf && !स_भेद(pbuf + 2, WMM_PARA_IE, 6)) अणु
				स_नकल(pframe, pbuf, ie_len + 2);
				pframe += (ie_len + 2);
				pattrib->pktlen += (ie_len + 2);
				अवरोध;
			पूर्ण

			अगर (!pbuf || ie_len == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_REALTEK)
		pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, 6, REALTEK_96B_IE, &pattrib->pktlen);

	/* add WPS IE ie क्रम wps 2.0 */
	अगर (pmlmepriv->wps_assoc_resp_ie && pmlmepriv->wps_assoc_resp_ie_len > 0) अणु
		स_नकल(pframe, pmlmepriv->wps_assoc_resp_ie, pmlmepriv->wps_assoc_resp_ie_len);

		pframe += pmlmepriv->wps_assoc_resp_ie_len;
		pattrib->pktlen += pmlmepriv->wps_assoc_resp_ie_len;
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;
	dump_mgntframe(padapter, pmgntframe);
पूर्ण
#पूर्ण_अगर /* CONFIG_88EU_AP_MODE */

अटल व्योम issue_assocreq(काष्ठा adapter *padapter)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe, *p;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित पूर्णांक i, j, ie_len, index = 0;
	अचिन्हित अक्षर bssrate[NumRates], sta_bssrate[NumRates];
	काष्ठा ndis_802_11_var_ie *pIE;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	पूर्णांक bssrate_len = 0, sta_bssrate_len = 0;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);
	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ASSOCREQ);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	/* caps */

	स_नकल(pframe, rtw_get_capability_from_ie(pmlmeinfo->network.ies), 2);

	pframe += 2;
	pattrib->pktlen += 2;

	/* listen पूर्णांकerval */
	/* toकरो: listen पूर्णांकerval क्रम घातer saving */
	put_unaligned_le16(3, pframe);
	pframe += 2;
	pattrib->pktlen += 2;

	/* SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID,  pmlmeinfo->network.ssid.ssid_length, pmlmeinfo->network.ssid.ssid, &pattrib->pktlen);

	/* supported rate & extended supported rate */

	/*  Check अगर the AP's supported rates are also supported by STA. */
	get_rate_set(padapter, sta_bssrate, &sta_bssrate_len);

	अगर (pmlmeext->cur_channel == 14)/*  क्रम JAPAN, channel 14 can only uses B Mode(CCK) */
		sta_bssrate_len = 4;

	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		अगर (pmlmeinfo->network.SupportedRates[i] == 0)
			अवरोध;
		DBG_88E("network.SupportedRates[%d]=%02X\n", i, pmlmeinfo->network.SupportedRates[i]);
	पूर्ण

	क्रम (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) अणु
		अगर (pmlmeinfo->network.SupportedRates[i] == 0)
			अवरोध;

		/*  Check अगर the AP's supported rates are also supported by STA. */
		क्रम (j = 0; j < sta_bssrate_len; j++) अणु
			/*  Aव्योम the proprietary data rate (22Mbps) of Handlink WSG-4000 AP */
			अगर ((pmlmeinfo->network.SupportedRates[i] | IEEE80211_BASIC_RATE_MASK)
					== (sta_bssrate[j] | IEEE80211_BASIC_RATE_MASK))
				अवरोध;
		पूर्ण

		अगर (j == sta_bssrate_len) अणु
			/*  the rate is not supported by STA */
			DBG_88E("%s(): the rate[%d]=%02X is not supported by STA!\n", __func__, i, pmlmeinfo->network.SupportedRates[i]);
		पूर्ण अन्यथा अणु
			/*  the rate is supported by STA */
			bssrate[index++] = pmlmeinfo->network.SupportedRates[i];
		पूर्ण
	पूर्ण

	bssrate_len = index;
	DBG_88E("bssrate_len=%d\n", bssrate_len);

	अगर (bssrate_len == 0) अणु
		rtw_मुक्त_xmitbuf(pxmitpriv, pmgntframe->pxmitbuf);
		rtw_मुक्त_xmitframe(pxmitpriv, pmgntframe);
		जाओ निकास; /* करोn't connect to AP अगर no joपूर्णांक supported rate */
	पूर्ण

	अगर (bssrate_len > 8) अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, 8, bssrate, &pattrib->pktlen);
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, bssrate_len - 8, bssrate + 8, &pattrib->pktlen);
	पूर्ण अन्यथा अणु
		pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, bssrate_len, bssrate, &pattrib->pktlen);
	पूर्ण

	/* RSN */
	p = rtw_get_ie((pmlmeinfo->network.ies + माप(काष्ठा ndis_802_11_fixed_ie)), WLAN_EID_RSN, &ie_len, (pmlmeinfo->network.ie_length - माप(काष्ठा ndis_802_11_fixed_ie)));
	अगर (p)
		pframe = rtw_set_ie(pframe, WLAN_EID_RSN, ie_len, p + 2, &pattrib->pktlen);

	/* HT caps */
	अगर (padapter->mlmepriv.htpriv.ht_option) अणु
		p = rtw_get_ie((pmlmeinfo->network.ies + माप(काष्ठा ndis_802_11_fixed_ie)), WLAN_EID_HT_CAPABILITY, &ie_len, (pmlmeinfo->network.ie_length - माप(काष्ठा ndis_802_11_fixed_ie)));
		अगर (p && !is_ap_in_tkip(padapter)) अणु
			स_नकल(&pmlmeinfo->HT_caps, p + 2, माप(काष्ठा ieee80211_ht_cap));

			/* to disable 40M Hz support जबतक gd_bw_40MHz_en = 0 */
			अगर (pregpriv->cbw40_enable == 0)
				pmlmeinfo->HT_caps.cap_info &= cpu_to_le16(~(BIT(6) | BIT(1)));
			अन्यथा
				pmlmeinfo->HT_caps.cap_info |= cpu_to_le16(BIT(1));

			/* toकरो: disable SM घातer save mode */
			pmlmeinfo->HT_caps.cap_info |= cpu_to_le16(0x000c);

			अगर (pregpriv->rx_stbc)
				pmlmeinfo->HT_caps.cap_info |= cpu_to_le16(0x0100);/* RX STBC One spatial stream */
			स_नकल((u8 *)&pmlmeinfo->HT_caps.mcs, MCS_rate_1R, 16);
			pframe = rtw_set_ie(pframe, WLAN_EID_HT_CAPABILITY, ie_len, (u8 *)(&pmlmeinfo->HT_caps), &pattrib->pktlen);
		पूर्ण
	पूर्ण

	/* venकरोr specअगरic IE, such as WPA, WMM, WPS */
	क्रम (i = माप(काष्ठा ndis_802_11_fixed_ie); i < pmlmeinfo->network.ie_length; i += (pIE->Length + 2)) अणु
		pIE = (काष्ठा ndis_802_11_var_ie *)(pmlmeinfo->network.ies + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर ((!स_भेद(pIE->data, RTW_WPA_OUI, 4)) ||
			    (!स_भेद(pIE->data, WMM_OUI, 4)) ||
			    (!स_भेद(pIE->data, WPS_OUI, 4))) अणु
				अगर (!padapter->registrypriv.wअगरi_spec) अणु
					/* Commented by Kurt 20110629 */
					/* In some older APs, WPS handshake */
					/* would be fail अगर we append vender extensions inक्रमmation to AP */
					अगर (!स_भेद(pIE->data, WPS_OUI, 4))
						pIE->Length = 14;
				पूर्ण
				pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, pIE->Length, pIE->data, &pattrib->pktlen);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_REALTEK)
		pframe = rtw_set_ie(pframe, WLAN_EID_VENDOR_SPECIFIC, 6, REALTEK_96B_IE, &pattrib->pktlen);

	pattrib->last_txcmdsz = pattrib->pktlen;
	dump_mgntframe(padapter, pmgntframe);

	ret = _SUCCESS;

निकास:
	अगर (ret == _SUCCESS)
		rtw_buf_update(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len, (u8 *)pwlanhdr, pattrib->pktlen);
	अन्यथा
		rtw_buf_मुक्त(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len);
पूर्ण

/* when रुको_ack is true, this function should be called at process context */
अटल पूर्णांक _issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			   अचिन्हित पूर्णांक घातer_mode, bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;
	काष्ठा wlan_bssid_ex *pnetwork;

	अगर (!padapter)
		जाओ निकास;

	pxmitpriv = &padapter->xmitpriv;
	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;
	pnetwork = &pmlmeinfo->network;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE)
		SetFrDs(fctrl);
	अन्यथा अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE)
		SetToDs(fctrl);

	अगर (घातer_mode)
		SetPwrMgt(fctrl);

	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DATA_शून्य);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/* when रुको_ms > 0 , this function should be called at process context */
/* da == शून्य क्रम station mode */
पूर्णांक issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		   अचिन्हित पूर्णांक घातer_mode, पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ start = jअगरfies;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	/* da == शून्य, assume it's null data क्रम sta to ap*/
	अगर (!da)
		da = pnetwork->MacAddress;

	करो अणु
		ret = _issue_nulldata(padapter, da, घातer_mode, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);
	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण

	अगर (try_cnt && रुको_ms) अणु
		अगर (da)
			DBG_88E(FUNC_ADPT_FMT" to %pM, ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), da, rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
		अन्यथा
			DBG_88E(FUNC_ADPT_FMT", ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
	पूर्ण
निकास:
	वापस ret;
पूर्ण

/* when रुको_ack is true, this function should be called at process context */
अटल पूर्णांक _issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			       u16 tid, bool रुको_ack)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	अचिन्हित लघु *qc;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	DBG_88E("%s\n", __func__);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	pattrib->hdrlen += 2;
	pattrib->qos_en = true;
	pattrib->eosp = 1;
	pattrib->ack_policy = 0;
	pattrib->mdata = 0;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE)
		SetFrDs(fctrl);
	अन्यथा अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE)
		SetToDs(fctrl);

	अगर (pattrib->mdata)
		SetMData(fctrl);

	qc = (अचिन्हित लघु *)(pframe + pattrib->hdrlen - 2);

	SetPriority(qc, tid);

	SetEOSP(qc, pattrib->eosp);

	SetAckpolicy(qc, pattrib->ack_policy);

	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_QOS_DATA_शून्य);

	pframe += माप(काष्ठा ieee80211_qos_hdr);
	pattrib->pktlen = माप(काष्ठा ieee80211_qos_hdr);

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

/* when रुको_ms > 0 , this function should be called at process context */
/* da == शून्य क्रम station mode */
पूर्णांक issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		       u16 tid, पूर्णांक try_cnt, पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ start = jअगरfies;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	/* da == शून्य, assume it's null data क्रम sta to ap*/
	अगर (!da)
		da = pnetwork->MacAddress;

	करो अणु
		ret = _issue_qos_nulldata(padapter, da, tid, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			msleep(रुको_ms);
	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण

	अगर (try_cnt && रुको_ms) अणु
		अगर (da)
			DBG_88E(FUNC_ADPT_FMT" to %pM, ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), da, rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
		अन्यथा
			DBG_88E(FUNC_ADPT_FMT", ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
	पूर्ण
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक _issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
			 अचिन्हित लघु reason, bool रुको_ack)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	पूर्णांक ret = _FAIL;
	__le16 le_पंचांगp;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, da);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_DEAUTH);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	le_पंचांगp = cpu_to_le16(reason);
	pframe = rtw_set_fixed_ie(pframe, _RSON_CODE_, &le_पंचांगp,
				  &pattrib->pktlen);

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (रुको_ack) अणु
		ret = dump_mgntframe_and_रुको_ack(padapter, pmgntframe);
	पूर्ण अन्यथा अणु
		dump_mgntframe(padapter, pmgntframe);
		ret = _SUCCESS;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		 अचिन्हित लघु reason)
अणु
	DBG_88E("%s to %pM\n", __func__, da);
	वापस _issue_deauth(padapter, da, reason, false);
पूर्ण

अटल पूर्णांक issue_deauth_ex(काष्ठा adapter *padapter, u8 *da,
			   अचिन्हित लघु reason, पूर्णांक try_cnt,
			   पूर्णांक रुको_ms)
अणु
	पूर्णांक ret;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ start = jअगरfies;

	करो अणु
		ret = _issue_deauth(padapter, da, reason, रुको_ms > 0);

		i++;

		अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
			अवरोध;

		अगर (i < try_cnt && रुको_ms > 0 && ret == _FAIL)
			mdelay(रुको_ms);
	पूर्ण जबतक ((i < try_cnt) && ((ret == _FAIL) || (रुको_ms == 0)));

	अगर (ret != _FAIL) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण

	अगर (try_cnt && रुको_ms) अणु
		अगर (da)
			DBG_88E(FUNC_ADPT_FMT" to %pM, ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), da, rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
		अन्यथा
			DBG_88E(FUNC_ADPT_FMT", ch:%u%s, %d/%d in %u ms\n",
				FUNC_ADPT_ARG(padapter), rtw_get_oper_ch(padapter),
				ret == _SUCCESS ? ", acked" : "", i, try_cnt,
				jअगरfies_to_msecs(jअगरfies - start));
	पूर्ण
निकास:
	वापस ret;
पूर्ण

अटल व्योम issue_action_BA(काष्ठा adapter *padapter, अचिन्हित अक्षर *raddr,
			    अचिन्हित अक्षर action, अचिन्हित लघु status)
अणु
	u8 category = RTW_WLAN_CATEGORY_BACK;
	u16 start_seq;
	u16 BA_para_set;
	u16 reason_code;
	u16 BA_समयout_value;
	__le16 le_पंचांगp;
	u16 BA_starting_seqctrl = 0;
	क्रमागत ht_cap_ampdu_factor max_rx_ampdu_factor;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	u8 *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा sta_info *psta;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	DBG_88E("%s, category=%d, action=%d, status=%d\n", __func__, category, action, status);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, raddr);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ACTION);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pframe = rtw_set_fixed_ie(pframe, 1, &category, &pattrib->pktlen);
	pframe = rtw_set_fixed_ie(pframe, 1, &action, &pattrib->pktlen);

	अगर (category == 3) अणु
		चयन (action) अणु
		हाल 0: /* ADDBA req */
			करो अणु
				pmlmeinfo->dialogToken++;
			पूर्ण जबतक (pmlmeinfo->dialogToken == 0);
			pframe = rtw_set_fixed_ie(pframe, 1, &pmlmeinfo->dialogToken, &pattrib->pktlen);

			BA_para_set = 0x1002 | ((status & 0xf) << 2); /* immediate ack & 64 buffer size */
			le_पंचांगp = cpu_to_le16(BA_para_set);
			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);

			BA_समयout_value = 5000;/*  5ms */
			le_पंचांगp = cpu_to_le16(BA_समयout_value);
			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);

			psta = rtw_get_stainfo(pstapriv, raddr);
			अगर (psta) अणु
				start_seq = (psta->sta_xmitpriv.txseq_tid[status & 0x07] & 0xfff) + 1;

				DBG_88E("BA_starting_seqctrl=%d for TID=%d\n", start_seq, status & 0x07);

				psta->BA_starting_seqctrl[status & 0x07] = start_seq;

				BA_starting_seqctrl = start_seq << 4;
			पूर्ण
			le_पंचांगp = cpu_to_le16(BA_starting_seqctrl);
			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);
			अवरोध;
		हाल 1: /* ADDBA rsp */
		अणु
			काष्ठा ADDBA_request *ADDBA_req = &pmlmeinfo->ADDBA_req;

			pframe = rtw_set_fixed_ie(pframe, 1,
						  &ADDBA_req->dialog_token,
						  &pattrib->pktlen);
			pframe = rtw_set_fixed_ie(pframe, 2, &status,
						  &pattrib->pktlen);

			BA_para_set = le16_to_cpu(ADDBA_req->BA_para_set) &
				      0x3f;
			rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor);
			चयन (max_rx_ampdu_factor) अणु
			हाल MAX_AMPDU_FACTOR_64K:
				BA_para_set |= 0x1000; /* 64 buffer size */
				अवरोध;
			हाल MAX_AMPDU_FACTOR_32K:
				BA_para_set |= 0x0800; /* 32 buffer size */
				अवरोध;
			हाल MAX_AMPDU_FACTOR_16K:
				BA_para_set |= 0x0400; /* 16 buffer size */
				अवरोध;
			हाल MAX_AMPDU_FACTOR_8K:
				BA_para_set |= 0x0200; /* 8 buffer size */
				अवरोध;
			शेष:
				BA_para_set |= 0x1000; /* 64 buffer size */
				अवरोध;
			पूर्ण

			अगर (pregpriv->ampdu_amsdu == 0)/* disabled */
				BA_para_set = BA_para_set & ~BIT(0);
			अन्यथा अगर (pregpriv->ampdu_amsdu == 1)/* enabled */
				BA_para_set = BA_para_set | BIT(0);
			le_पंचांगp = cpu_to_le16(BA_para_set);

			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);
			pframe = rtw_set_fixed_ie(pframe, 2,
						  &ADDBA_req->BA_समयout_value,
						  &pattrib->pktlen);
			अवरोध;
		पूर्ण
		हाल 2:/* DELBA */
			BA_para_set = (status & 0x1F) << 3;
			le_पंचांगp = cpu_to_le16(BA_para_set);
			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);

			reason_code = 37;/* Requested from peer STA as it करोes not want to use the mechanism */
			le_पंचांगp = cpu_to_le16(reason_code);
			pframe = rtw_set_fixed_ie(pframe, 2, &(le_पंचांगp),
						  &pattrib->pktlen);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

अटल व्योम issue_action_BSSCoexistPacket(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *plist, *phead;
	अचिन्हित अक्षर category, action;
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	अचिन्हित अक्षर *pframe;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	u8 InfoContent[16] = अणु0पूर्ण;
	u8 ICS[8][15];
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;

	अगर ((pmlmepriv->num_FortyMHzIntolerant == 0) || (pmlmepriv->num_sta_no_ht == 0))
		वापस;

	अगर (pmlmeinfo->bwmode_updated)
		वापस;

	DBG_88E("%s\n", __func__);

	category = RTW_WLAN_CATEGORY_PUBLIC;
	action = ACT_PUBLIC_BSSCOEXIST;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		वापस;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, cur_network->MacAddress);
	ether_addr_copy(pwlanhdr->addr2, myid(&padapter->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, cur_network->MacAddress);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	SetFrameSubType(pframe, WIFI_ACTION);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pattrib->pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	pframe = rtw_set_fixed_ie(pframe, 1, &category, &pattrib->pktlen);
	pframe = rtw_set_fixed_ie(pframe, 1, &action, &pattrib->pktlen);

	/*  */
	अगर (pmlmepriv->num_FortyMHzIntolerant > 0) अणु
		u8 iedata = 0;

		iedata |= BIT(2);/* 20 MHz BSS Width Request */

		pframe = rtw_set_ie(pframe, WLAN_EID_BSS_COEX_2040,  1, &iedata, &pattrib->pktlen);
	पूर्ण

	/*  */
	स_रखो(ICS, 0, माप(ICS));
	अगर (pmlmepriv->num_sta_no_ht > 0) अणु
		पूर्णांक i;

		spin_lock_bh(&pmlmepriv->scanned_queue.lock);

		phead = get_list_head(queue);
		plist = phead->next;

		जबतक (phead != plist) अणु
			uपूर्णांक len;
			u8 *p;
			काष्ठा wlan_bssid_ex *pbss_network;

			pnetwork = container_of(plist, काष्ठा wlan_network, list);

			plist = plist->next;

			pbss_network = &pnetwork->network;

			p = rtw_get_ie(pbss_network->ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_CAPABILITY, &len, pbss_network->ie_length - _FIXED_IE_LENGTH_);
			अगर (!p || len == 0) अणु /* non-HT */
				अगर (pbss_network->Configuration.DSConfig <= 0)
					जारी;

				ICS[0][pbss_network->Configuration.DSConfig] = 1;

				अगर (ICS[0][0] == 0)
					ICS[0][0] = 1;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);

		क्रम (i = 0; i < 8; i++) अणु
			अगर (ICS[i][0] == 1) अणु
				पूर्णांक j, k = 0;

				InfoContent[k] = i;
				/* SET_BSS_INTOLERANT_ELE_REG_CLASS(InfoContent, i); */
				k++;

				क्रम (j = 1; j <= 14; j++) अणु
					अगर (ICS[i][j] == 1) अणु
						अगर (k < 16) अणु
							InfoContent[k] = j; /* channel number */
							/* SET_BSS_INTOLERANT_ELE_CHANNEL(InfoContent+k, j); */
							k++;
						पूर्ण
					पूर्ण
				पूर्ण

				pframe = rtw_set_ie(pframe, WLAN_EID_BSS_INTOLERANT_CHL_REPORT, k, InfoContent, &pattrib->pktlen);
			पूर्ण
		पूर्ण
	पूर्ण

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(padapter, pmgntframe);
पूर्ण

अचिन्हित पूर्णांक send_delba(काष्ठा adapter *padapter, u8 initiator, u8 *addr)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u16 tid;

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		अगर (!(pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
			वापस _SUCCESS;

	psta = rtw_get_stainfo(pstapriv, addr);
	अगर (!psta)
		वापस _SUCCESS;

	अगर (initiator == 0) अणु /*  recipient */
		क्रम (tid = 0; tid < MAXTID; tid++) अणु
			अगर (psta->recvreorder_ctrl[tid].enable) अणु
				DBG_88E("rx agg disable tid(%d)\n", tid);
				issue_action_BA(padapter, addr, RTW_WLAN_ACTION_DELBA, (((tid << 1) | initiator) & 0x1F));
				psta->recvreorder_ctrl[tid].enable = false;
				psta->recvreorder_ctrl[tid].indicate_seq = 0xffff;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (initiator == 1) अणु /*  originator */
		क्रम (tid = 0; tid < MAXTID; tid++) अणु
			अगर (psta->htpriv.agg_enable_biपंचांगap & BIT(tid)) अणु
				DBG_88E("tx agg disable tid(%d)\n", tid);
				issue_action_BA(padapter, addr, RTW_WLAN_ACTION_DELBA, (((tid << 1) | initiator) & 0x1F));
				psta->htpriv.agg_enable_biपंचांगap &= ~BIT(tid);
				psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(tid);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक send_beacon(काष्ठा adapter *padapter)
अणु
	u8 bxmitok = false;
	पूर्णांक issue = 0;
	पूर्णांक poll = 0;
	अचिन्हित दीर्घ start = jअगरfies;
	u32 passing_समय;

	rtw_hal_set_hwreg(padapter, HW_VAR_BCN_VALID, शून्य);
	करो अणु
		issue_beacon(padapter, 100);
		issue++;
		करो अणु
			yield();
			rtw_hal_get_hwreg(padapter, HW_VAR_BCN_VALID, (u8 *)(&bxmitok));
			poll++;
		पूर्ण जबतक ((poll % 10) != 0 && !bxmitok && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);
	पूर्ण जबतक (!bxmitok && issue < 100 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		वापस _FAIL;
	अगर (!bxmitok) अणु
		DBG_88E("%s fail! %u ms\n", __func__,
			jअगरfies_to_msecs(jअगरfies - start));
		वापस _FAIL;
	पूर्ण
	passing_समय = jअगरfies_to_msecs(jअगरfies - start);

	अगर (passing_समय > 100 || issue > 3)
		DBG_88E("%s success, issue:%d, poll:%d, %u ms\n",
			__func__, issue, poll,
			jअगरfies_to_msecs(jअगरfies - start));
	वापस _SUCCESS;
पूर्ण

/****************************************************************************

Following are some utility functions क्रम WiFi MLME

*****************************************************************************/

अटल व्योम site_survey(काष्ठा adapter *padapter)
अणु
	अचिन्हित अक्षर survey_channel = 0, val8;
	क्रमागत rt_scan_type ScanType = SCAN_PASSIVE;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u32 initialgain = 0;
	काष्ठा rtw_ieee80211_channel *ch;

	अगर (pmlmeext->sitesurvey_res.channel_idx < pmlmeext->sitesurvey_res.ch_num) अणु
		ch = &pmlmeext->sitesurvey_res.ch[pmlmeext->sitesurvey_res.channel_idx];
		survey_channel = ch->hw_value;
		ScanType = (ch->flags & RTW_IEEE80211_CHAN_PASSIVE_SCAN) ? SCAN_PASSIVE : SCAN_ACTIVE;
	पूर्ण

	अगर (survey_channel != 0) अणु
		/* PAUSE 4-AC Queue when site_survey */
		/* rtw_hal_get_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		/* val8 |= 0x0f; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */
		अगर (pmlmeext->sitesurvey_res.channel_idx == 0)
			set_channel_bwmode(padapter, survey_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);
		अन्यथा
			SelectChannel(padapter, survey_channel);

		अगर (ScanType == SCAN_ACTIVE) अणु /* obey the channel plan setting... */
			पूर्णांक i;

			क्रम (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) अणु
				अगर (pmlmeext->sitesurvey_res.ssid[i].ssid_length) अणु
					/* toकरो: to issue two probe req??? */
					issue_probereq(padapter,
						       &pmlmeext->sitesurvey_res.ssid[i],
						       शून्य, false);
					/* msleep(SURVEY_TO>>1); */
					issue_probereq(padapter,
						       &pmlmeext->sitesurvey_res.ssid[i],
						       शून्य, false);
				पूर्ण
			पूर्ण

			अगर (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) अणु
				/* toकरो: to issue two probe req??? */
				issue_probereq(padapter, शून्य, शून्य, false);
				/* msleep(SURVEY_TO>>1); */
				issue_probereq(padapter, शून्य, शून्य, false);
			पूर्ण

			अगर (pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) अणु
				/* toकरो: to issue two probe req??? */
				issue_probereq(padapter, शून्य, शून्य, false);
				/* msleep(SURVEY_TO>>1); */
				issue_probereq(padapter, शून्य, शून्य, false);
			पूर्ण
		पूर्ण

		set_survey_समयr(pmlmeext, pmlmeext->chan_scan_समय);
	पूर्ण अन्यथा अणु
		/*  20100721:Interrupt scan operation here. */
		/*  For SW antenna भागersity beक्रमe link, it needs to चयन to another antenna and scan again. */
		/*  It compares the scan result and select better one to करो connection. */
		अगर (rtw_hal_antभाग_beक्रमe_linked(padapter)) अणु
			pmlmeext->sitesurvey_res.bss_cnt = 0;
			pmlmeext->sitesurvey_res.channel_idx = -1;
			pmlmeext->chan_scan_समय = SURVEY_TO / 2;
			set_survey_समयr(pmlmeext, pmlmeext->chan_scan_समय);
			वापस;
		पूर्ण

		pmlmeext->sitesurvey_res.state = SCAN_COMPLETE;

		/* चयन back to the original channel */

		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		/* flush 4-AC Queue after site_survey */
		/* val8 = 0; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, (u8 *)(&val8)); */

		/* config MSR */
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		initialgain = 0xff; /* restore RX GAIN */
		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));
		/* turn on dynamic functions */
		Restore_DM_Func_Flag(padapter);
		/* Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true); */

		अगर (is_client_associated_to_ap(padapter))
			issue_nulldata(padapter, शून्य, 0, 3, 500);

		val8 = 0; /* survey करोne */
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		report_surveyकरोne_event(padapter);

		pmlmeext->chan_scan_समय = SURVEY_TO;
		pmlmeext->sitesurvey_res.state = SCAN_DISABLE;

		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
		issue_action_BSSCoexistPacket(padapter);
	पूर्ण
पूर्ण

/* collect bss info from Beacon and Probe request/response frames. */
अटल u8 collect_bss_info(काष्ठा adapter *padapter,
			   काष्ठा recv_frame *precv_frame,
			   काष्ठा wlan_bssid_ex *bssid)
अणु
	पूर्णांक i;
	u32 len;
	u8 *p;
	u16 val16, subtype;
	u8 *pframe = precv_frame->pkt->data;
	u32 packet_len = precv_frame->pkt->len;
	u8 ie_offset;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	len = packet_len - माप(काष्ठा ieee80211_hdr_3addr);

	अगर (len > MAX_IE_SZ)
		वापस _FAIL;

	स_रखो(bssid, 0, माप(काष्ठा wlan_bssid_ex));

	subtype = GetFrameSubType(pframe);

	अगर (subtype == WIFI_BEACON) अणु
		bssid->Reserved[0] = 1;
		ie_offset = _BEACON_IE_OFFSET_;
	पूर्ण अन्यथा अणु
		/*  FIXME : more type */
		अगर (subtype == WIFI_PROBEREQ) अणु
			ie_offset = _PROBEREQ_IE_OFFSET_;
			bssid->Reserved[0] = 2;
		पूर्ण अन्यथा अगर (subtype == WIFI_PROBERSP) अणु
			ie_offset = _PROBERSP_IE_OFFSET_;
			bssid->Reserved[0] = 3;
		पूर्ण अन्यथा अणु
			bssid->Reserved[0] = 0;
			ie_offset = _FIXED_IE_LENGTH_;
		पूर्ण
	पूर्ण

	bssid->Length = माप(काष्ठा wlan_bssid_ex) - MAX_IE_SZ + len;

	/* below is to copy the inक्रमmation element */
	bssid->ie_length = len;
	स_नकल(bssid->ies, (pframe + माप(काष्ठा ieee80211_hdr_3addr)), bssid->ie_length);

	/* get the संकेत strength in dBM.raw data */
	bssid->Rssi = precv_frame->attrib.phy_info.recvघातer;
	bssid->PhyInfo.SignalQuality = precv_frame->attrib.phy_info.SignalQuality;/* in percentage */
	bssid->PhyInfo.SignalStrength = precv_frame->attrib.phy_info.SignalStrength;/* in percentage */
	rtw_hal_get_def_var(padapter, HAL_DEF_CURRENT_ANTENNA,  &bssid->PhyInfo.Optimum_antenna);

	/*  checking SSID */
	p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_SSID, &len, bssid->ie_length - ie_offset);
	अगर (!p) अणु
		DBG_88E("marc: cannot find SSID for survey event\n");
		वापस _FAIL;
	पूर्ण

	अगर (len) अणु
		अगर (len > NDIS_802_11_LENGTH_SSID) अणु
			DBG_88E("%s()-%d: IE too long (%d) for survey event\n", __func__, __LINE__, len);
			वापस _FAIL;
		पूर्ण
		स_नकल(bssid->ssid.ssid, (p + 2), len);
		bssid->ssid.ssid_length = len;
	पूर्ण अन्यथा अणु
		bssid->ssid.ssid_length = 0;
	पूर्ण

	स_रखो(bssid->SupportedRates, 0, NDIS_802_11_LENGTH_RATES_EX);

	/* checking rate info... */
	i = 0;
	p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_SUPP_RATES, &len, bssid->ie_length - ie_offset);
	अगर (p) अणु
		अगर (len > NDIS_802_11_LENGTH_RATES_EX) अणु
			DBG_88E("%s()-%d: IE too long (%d) for survey event\n", __func__, __LINE__, len);
			वापस _FAIL;
		पूर्ण
		स_नकल(bssid->SupportedRates, (p + 2), len);
		i = len;
	पूर्ण

	p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_EXT_SUPP_RATES, &len, bssid->ie_length - ie_offset);
	अगर (p) अणु
		अगर (len > (NDIS_802_11_LENGTH_RATES_EX - i)) अणु
			DBG_88E("%s()-%d: IE too long (%d) for survey event\n", __func__, __LINE__, len);
			वापस _FAIL;
		पूर्ण
		स_नकल(bssid->SupportedRates + i, (p + 2), len);
	पूर्ण

	/* toकरो: */
	bssid->NetworkTypeInUse = Ndis802_11OFDM24;

	अगर (bssid->ie_length < 12)
		वापस _FAIL;

	/*  Checking क्रम DSConfig */
	p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_DS_PARAMS, &len, bssid->ie_length - ie_offset);

	bssid->Configuration.DSConfig = 0;
	bssid->Configuration.Length = 0;

	अगर (p) अणु
		bssid->Configuration.DSConfig = *(p + 2);
	पूर्ण अन्यथा अणु/*  In 5G, some ap करो not have DSSET IE */
		/*  checking HT info क्रम channel */
		p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_HT_OPERATION, &len, bssid->ie_length - ie_offset);
		अगर (p) अणु
			काष्ठा HT_info_element *HT_info = (काष्ठा HT_info_element *)(p + 2);

			bssid->Configuration.DSConfig = HT_info->primary_channel;
		पूर्ण अन्यथा अणु /*  use current channel */
			bssid->Configuration.DSConfig = rtw_get_oper_ch(padapter);
		पूर्ण
	पूर्ण

	अगर (subtype == WIFI_PROBEREQ) अणु
		/*  FIXME */
		bssid->Infraकाष्ठाureMode = Ndis802_11Infraकाष्ठाure;
		ether_addr_copy(bssid->MacAddress, GetAddr2Ptr(pframe));
		bssid->Privacy = 1;
		वापस _SUCCESS;
	पूर्ण

	bssid->Configuration.BeaconPeriod =
		get_unaligned_le16(rtw_get_beacon_पूर्णांकerval_from_ie(bssid->ies));

	val16 = rtw_get_capability(bssid);

	अगर (val16 & BIT(0)) अणु
		bssid->Infraकाष्ठाureMode = Ndis802_11Infraकाष्ठाure;
		ether_addr_copy(bssid->MacAddress, GetAddr2Ptr(pframe));
	पूर्ण अन्यथा अणु
		bssid->Infraकाष्ठाureMode = Ndis802_11IBSS;
		ether_addr_copy(bssid->MacAddress, GetAddr3Ptr(pframe));
	पूर्ण

	अगर (val16 & BIT(4))
		bssid->Privacy = 1;
	अन्यथा
		bssid->Privacy = 0;

	bssid->Configuration.ATIMWinकरोw = 0;

	/* 20/40 BSS Coexistence check */
	अगर ((pregistrypriv->wअगरi_spec == 1) && (!pmlmeinfo->bwmode_updated)) अणु
		काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

		p = rtw_get_ie(bssid->ies + ie_offset, WLAN_EID_HT_CAPABILITY, &len, bssid->ie_length - ie_offset);
		अगर (p && len > 0) अणु
			काष्ठा ieee80211_ht_cap *pHT_caps =
				(काष्ठा ieee80211_ht_cap *)(p + 2);

			अगर (le16_to_cpu(pHT_caps->cap_info) & BIT(14))
				pmlmepriv->num_FortyMHzIntolerant++;
		पूर्ण अन्यथा अणु
			pmlmepriv->num_sta_no_ht++;
		पूर्ण
	पूर्ण

	/*  mark bss info receiving from nearby channel as SignalQuality 101 */
	अगर (bssid->Configuration.DSConfig != rtw_get_oper_ch(padapter))
		bssid->PhyInfo.SignalQuality = 101;
	वापस _SUCCESS;
पूर्ण

अटल व्योम start_create_ibss(काष्ठा adapter *padapter)
अणु
	अचिन्हित लघु caps;
	u8 val8;
	u8 join_type;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_पूर्णांकerval = get_beacon_पूर्णांकerval(pnetwork);

	/* update wireless mode */
	update_wireless_mode(padapter);

	/* update capability */
	caps = rtw_get_capability(pnetwork);
	update_capinfo(padapter, caps);
	अगर (caps & WLAN_CAPABILITY_IBSS) अणु/* adhoc master */
		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		/* चयन channel */
		/* SelectChannel(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE); */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);

		beacon_timing_control(padapter);

		/* set msr to WIFI_FW_ADHOC_STATE */
		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		/* issue beacon */
		अगर (send_beacon(padapter) == _FAIL) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("issuing beacon frame fail....\n"));

			report_join_res(padapter, -1);
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		पूर्ण अन्यथा अणु
			rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, padapter->registrypriv.dev_network.MacAddress);
			join_type = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

			report_join_res(padapter, 1);
			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		DBG_88E("%s, invalid cap:%x\n", __func__, caps);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम start_clnt_join(काष्ठा adapter *padapter)
अणु
	अचिन्हित लघु caps;
	u8 val8;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	पूर्णांक beacon_समयout;

	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_पूर्णांकerval = get_beacon_पूर्णांकerval(pnetwork);

	/* update wireless mode */
	update_wireless_mode(padapter);

	/* update capability */
	caps = rtw_get_capability(pnetwork);
	update_capinfo(padapter, caps);
	अगर (caps & WLAN_CAPABILITY_ESS) अणु
		Set_MSR(padapter, WIFI_FW_STATION_STATE);

		val8 = (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_8021X) ? 0xcc : 0xcf;

		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		/* चयन channel */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		/* here रुको क्रम receiving the beacon to start auth */
		/* and enable a समयr */
		beacon_समयout = decide_रुको_क्रम_beacon_समयout(pmlmeinfo->bcn_पूर्णांकerval);
		set_link_समयr(pmlmeext, beacon_समयout);
		mod_समयr(&padapter->mlmepriv.assoc_समयr, jअगरfies +
			  msecs_to_jअगरfies((REAUTH_TO * REAUTH_LIMIT) + (REASSOC_TO * REASSOC_LIMIT) + beacon_समयout));

		pmlmeinfo->state = WIFI_FW_AUTH_शून्य | WIFI_FW_STATION_STATE;
	पूर्ण अन्यथा अगर (caps & WLAN_CAPABILITY_IBSS) अणु /* adhoc client */
		Set_MSR(padapter, WIFI_FW_ADHOC_STATE);

		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		/* चयन channel */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		beacon_timing_control(padapter);

		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;

		report_join_res(padapter, 1);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

अटल व्योम start_clnt_auth(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	del_समयr_sync(&pmlmeext->link_समयr);

	pmlmeinfo->state &= (~WIFI_FW_AUTH_शून्य);
	pmlmeinfo->state |= WIFI_FW_AUTH_STATE;

	pmlmeinfo->auth_seq = 1;
	pmlmeinfo->reauth_count = 0;
	pmlmeinfo->reassoc_count = 0;
	pmlmeinfo->link_count = 0;
	pmlmeext->retry = 0;

	/*  Because of AP's not receiving deauth beक्रमe */
	/*  AP may: 1)not response auth or 2)deauth us after link is complete */
	/*  issue deauth beक्रमe issuing auth to deal with the situation */
	/*	Commented by Albert 2012/07/21 */
	/*	For the Win8 P2P connection, it will be hard to have a successful connection अगर this Wi-Fi करोesn't connect to it. */
	issue_deauth(padapter, (&pmlmeinfo->network)->MacAddress, WLAN_REASON_DEAUTH_LEAVING);

	DBG_88E_LEVEL(_drv_info_, "start auth\n");
	issue_auth(padapter, शून्य, 0);

	set_link_समयr(pmlmeext, REAUTH_TO);
पूर्ण

अटल व्योम start_clnt_assoc(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	del_समयr_sync(&pmlmeext->link_समयr);

	pmlmeinfo->state &= (~(WIFI_FW_AUTH_शून्य | WIFI_FW_AUTH_STATE));
	pmlmeinfo->state |= (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE);

	issue_assocreq(padapter);

	set_link_समयr(pmlmeext, REASSOC_TO);
पूर्ण

अटल अचिन्हित पूर्णांक receive_disconnect(काष्ठा adapter *padapter,
				       अचिन्हित अक्षर *MacAddr,
				       अचिन्हित लघु reason)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	/* check A3 */
	अगर (स_भेद(MacAddr, pnetwork->MacAddress, ETH_ALEN))
		वापस _SUCCESS;

	DBG_88E("%s\n", __func__);

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE) अणु
		अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_del_sta_event(padapter, MacAddr, reason);
		पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_LINKING_STATE) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_join_res(padapter, -2);
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल व्योम process_80211d(काष्ठा adapter *padapter, काष्ठा wlan_bssid_ex *bssid)
अणु
	काष्ठा registry_priv *pregistrypriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा rt_channel_info *chplan_new;
	u8 channel;
	u8 i;

	pregistrypriv = &padapter->registrypriv;
	pmlmeext = &padapter->mlmeextpriv;

	/*  Adjust channel plan by AP Country IE */
	अगर (pregistrypriv->enable80211d &&
	    (!pmlmeext->update_channel_plan_by_ap_करोne)) अणु
		u8 *ie, *p;
		u32 len;
		काष्ठा rt_channel_plan chplan_ap;
		काष्ठा rt_channel_info chplan_sta[MAX_CHANNEL_NUM];
		u8 country[4];
		u8 fcn; /*  first channel number */
		u8 noc; /*  number of channel */
		u8 j, k;

		ie = rtw_get_ie(bssid->ies + _FIXED_IE_LENGTH_, WLAN_EID_COUNTRY, &len, bssid->ie_length - _FIXED_IE_LENGTH_);
		अगर (!ie)
			वापस;
		अगर (len < 6)
			वापस;
		ie += 2;
		p = ie;
		ie += len;

		स_रखो(country, 0, 4);
		स_नकल(country, p, 3);
		p += 3;
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
			 ("%s: 802.11d country =%s\n", __func__, country));

		i = 0;
		जबतक ((ie - p) >= 3) अणु
			fcn = *(p++);
			noc = *(p++);
			p++;

			क्रम (j = 0; j < noc; j++) अणु
				channel = fcn + j;

				chplan_ap.Channel[i++] = channel;
			पूर्ण
		पूर्ण
		chplan_ap.Len = i;

		स_नकल(chplan_sta, pmlmeext->channel_set, माप(chplan_sta));

		स_रखो(pmlmeext->channel_set, 0, माप(pmlmeext->channel_set));
		chplan_new = pmlmeext->channel_set;

		i = 0;
		j = 0;
		k = 0;
		अगर (pregistrypriv->wireless_mode & WIRELESS_11G) अणु
			करो अणु
				अगर ((i == MAX_CHANNEL_NUM) ||
				    (chplan_sta[i].ChannelNum == 0) ||
				    (chplan_sta[i].ChannelNum > 14))
					अवरोध;

				अगर ((j == chplan_ap.Len) || (chplan_ap.Channel[j] > 14))
					अवरोध;

				अगर (chplan_sta[i].ChannelNum == chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					i++;
					j++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum < chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
					chplan_new[k].ScanType = SCAN_PASSIVE;
					i++;
					k++;
				पूर्ण अन्यथा अगर (chplan_sta[i].ChannelNum > chplan_ap.Channel[j]) अणु
					chplan_new[k].ChannelNum = chplan_ap.Channel[j];
					chplan_new[k].ScanType = SCAN_ACTIVE;
					j++;
					k++;
				पूर्ण
			पूर्ण जबतक (1);

			/*  change AP not support channel to Passive scan */
			जबतक ((i < MAX_CHANNEL_NUM) &&
			       (chplan_sta[i].ChannelNum != 0) &&
			       (chplan_sta[i].ChannelNum <= 14)) अणु
				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
				chplan_new[k].ScanType = SCAN_PASSIVE;
				i++;
				k++;
			पूर्ण

			/*  add channel AP supported */
			जबतक ((j < chplan_ap.Len) && (chplan_ap.Channel[j] <= 14)) अणु
				chplan_new[k].ChannelNum = chplan_ap.Channel[j];
				chplan_new[k].ScanType = SCAN_ACTIVE;
				j++;
				k++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  keep original STA 2.4G channel plan */
			जबतक ((i < MAX_CHANNEL_NUM) &&
			       (chplan_sta[i].ChannelNum != 0) &&
			       (chplan_sta[i].ChannelNum <= 14)) अणु
				chplan_new[k].ChannelNum = chplan_sta[i].ChannelNum;
				chplan_new[k].ScanType = chplan_sta[i].ScanType;
				i++;
				k++;
			पूर्ण

			/*  skip AP 2.4G channel plan */
			जबतक ((j < chplan_ap.Len) && (chplan_ap.Channel[j] <= 14))
				j++;
		पूर्ण

		pmlmeext->update_channel_plan_by_ap_करोne = 1;
	पूर्ण

	/*  If channel is used by AP, set channel scan type to active */
	channel = bssid->Configuration.DSConfig;
	chplan_new = pmlmeext->channel_set;
	i = 0;
	जबतक ((i < MAX_CHANNEL_NUM) && (chplan_new[i].ChannelNum != 0)) अणु
		अगर (chplan_new[i].ChannelNum == channel) अणु
			अगर (chplan_new[i].ScanType == SCAN_PASSIVE) अणु
				chplan_new[i].ScanType = SCAN_ACTIVE;
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
					 ("%s: change channel %d scan type from passive to active\n",
					 __func__, channel));
			पूर्ण
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
पूर्ण

/****************************************************************************

Following are the callback functions क्रम each subtype of the management frames

*****************************************************************************/

अटल अचिन्हित पूर्णांक OnProbeReq(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक ielen;
	अचिन्हित अक्षर *p;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur = &pmlmeinfo->network;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक len = precv_frame->pkt->len;

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		वापस _SUCCESS;

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED) &&
	    !check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE | WIFI_AP_STATE))
		वापस _SUCCESS;

	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, WLAN_EID_SSID, &ielen,
		       len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);

	/* check (wildcard) SSID */
	अगर (p) अणु
		अगर ((ielen != 0 && स_भेद((व्योम *)(p + 2), (व्योम *)cur->ssid.ssid, cur->ssid.ssid_length)) ||
		    (ielen == 0 && pmlmeinfo->hidden_ssid_mode))
			वापस _SUCCESS;

		अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
		    pmlmepriv->cur_network.join_res)
			issue_probersp(padapter, ieee80211_get_SA((काष्ठा ieee80211_hdr *)pframe));
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnProbeRsp(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		report_survey_event(padapter, precv_frame);
		वापस _SUCCESS;
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnBeacon(काष्ठा adapter *padapter,
			     काष्ठा recv_frame *precv_frame)
अणु
	पूर्णांक cam_idx;
	काष्ठा sta_info *psta;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक len = precv_frame->pkt->len;
	काष्ठा wlan_bssid_ex *pbss;
	पूर्णांक ret = _SUCCESS;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		report_survey_event(padapter, precv_frame);
		वापस _SUCCESS;
	पूर्ण

	अगर (!स_भेद(GetAddr3Ptr(pframe), pnetwork->MacAddress, ETH_ALEN)) अणु
		अगर (pmlmeinfo->state & WIFI_FW_AUTH_शून्य) अणु
			/* we should update current network beक्रमe auth, or some IE is wrong */
			pbss = (काष्ठा wlan_bssid_ex *)rtw_दो_स्मृति(माप(काष्ठा wlan_bssid_ex));
			अगर (pbss) अणु
				अगर (collect_bss_info(padapter, precv_frame, pbss) == _SUCCESS) अणु
					update_network(&pmlmepriv->cur_network.network, pbss, padapter, true);
					rtw_get_bcn_info(&pmlmepriv->cur_network);
				पूर्ण
				kमुक्त(pbss);
			पूर्ण

			/* check the venकरोr of the assoc AP */
			pmlmeinfo->assoc_AP_venकरोr = check_assoc_AP(pframe + माप(काष्ठा ieee80211_hdr_3addr), len - माप(काष्ठा ieee80211_hdr_3addr));

			/* update TSF Value */
			update_TSF(pmlmeext, pframe, len);

			/* start auth */
			start_clnt_auth(padapter);

			वापस _SUCCESS;
		पूर्ण

		अगर (((pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE) && (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)) अणु
			psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
			अगर (psta) अणु
				ret = rtw_check_bcn_info(padapter, pframe, len);
				अगर (!ret) अणु
					DBG_88E_LEVEL(_drv_info_, "ap has changed, disconnect now\n ");
					receive_disconnect(padapter, pmlmeinfo->network.MacAddress, 65535);
					वापस _SUCCESS;
				पूर्ण
				/* update WMM, ERP in the beacon */
				/* toकरो: the समयr is used instead of the number of the beacon received */
				अगर ((sta_rx_pkts(psta) & 0xf) == 0)
					update_beacon_info(padapter, pframe, len, psta);
			पूर्ण
		पूर्ण अन्यथा अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) अणु
			psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
			अगर (psta) अणु
				/* update WMM, ERP in the beacon */
				/* toकरो: the समयr is used instead of the number of the beacon received */
				अगर ((sta_rx_pkts(psta) & 0xf) == 0)
					update_beacon_info(padapter, pframe, len, psta);
			पूर्ण अन्यथा अणु
				/* allocate a new CAM entry क्रम IBSS station */
				cam_idx = allocate_fw_sta_entry(padapter);
				अगर (cam_idx == NUM_STA)
					जाओ _END_ONBEACON_;

				/* get supported rate */
				अगर (update_sta_support_rate(padapter, (pframe + WLAN_HDR_A3_LEN + _BEACON_IE_OFFSET_), (len - WLAN_HDR_A3_LEN - _BEACON_IE_OFFSET_), cam_idx) == _FAIL) अणु
					pmlmeinfo->FW_sta_info[cam_idx].status = 0;
					जाओ _END_ONBEACON_;
				पूर्ण

				/* update TSF Value */
				update_TSF(pmlmeext, pframe, len);

				/* report sta add event */
				report_add_sta_event(padapter, GetAddr2Ptr(pframe), cam_idx);
			पूर्ण
		पूर्ण
	पूर्ण

_END_ONBEACON_:

	वापस _SUCCESS;
पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE
अटल अचिन्हित पूर्णांक OnAuth(काष्ठा adapter *padapter,
			   काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक auth_mode, ie_len;
	u16 seq;
	अचिन्हित अक्षर *sa, *p;
	u16 algorithm;
	पूर्णांक status;
	अटल काष्ठा sta_info stat;
	काष्ठा sta_info *pstat = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक len = precv_frame->pkt->len;

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		वापस _FAIL;

	DBG_88E("+%s\n", __func__);

	sa = GetAddr2Ptr(pframe);

	auth_mode = psecuritypriv->करोt11AuthAlgrthm;
	seq = le16_to_cpu(*(__le16 *)((माप_प्रकार)pframe + WLAN_HDR_A3_LEN + 2));
	algorithm = le16_to_cpu(*(__le16 *)((माप_प्रकार)pframe + WLAN_HDR_A3_LEN));

	DBG_88E("auth alg=%x, seq=%X\n", algorithm, seq);

	अगर (auth_mode == 2 && psecuritypriv->करोt11PrivacyAlgrthm != _WEP40_ &&
	    psecuritypriv->करोt11PrivacyAlgrthm != _WEP104_)
		auth_mode = 0;

	अगर ((algorithm > 0 && auth_mode == 0) ||	/*  rx a shared-key auth but shared not enabled */
	    (algorithm == 0 && auth_mode == 1)) अणु	/*  rx a खोलो-प्रणाली auth but shared-key is enabled */
		DBG_88E("auth rejected due to bad alg [alg=%d, auth_mib=%d] %02X%02X%02X%02X%02X%02X\n",
			algorithm, auth_mode, sa[0], sa[1], sa[2], sa[3], sa[4], sa[5]);

		status = WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;

		जाओ auth_fail;
	पूर्ण

	अगर (!rtw_access_ctrl(padapter, sa)) अणु
		status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
		जाओ auth_fail;
	पूर्ण

	pstat = rtw_get_stainfo(pstapriv, sa);
	अगर (!pstat) अणु
		/*  allocate a new one */
		DBG_88E("going to alloc stainfo for sa=%pM\n", sa);
		pstat = rtw_alloc_stainfo(pstapriv, sa);
		अगर (!pstat) अणु
			DBG_88E(" Exceed the upper limit of supported clients...\n");
			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
			जाओ auth_fail;
		पूर्ण

		pstat->state = WIFI_FW_AUTH_शून्य;
		pstat->auth_seq = 0;
	पूर्ण अन्यथा अणु
		spin_lock_bh(&pstapriv->asoc_list_lock);
		अगर (!list_empty(&pstat->asoc_list)) अणु
			list_del_init(&pstat->asoc_list);
			pstapriv->asoc_list_cnt--;
		पूर्ण
		spin_unlock_bh(&pstapriv->asoc_list_lock);

		अगर (seq == 1) अणु
			/* TODO: STA re_auth and auth समयout */
		पूर्ण
	पूर्ण

	spin_lock_bh(&pstapriv->auth_list_lock);
	अगर (list_empty(&pstat->auth_list)) अणु
		list_add_tail(&pstat->auth_list, &pstapriv->auth_list);
		pstapriv->auth_list_cnt++;
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	अगर (pstat->auth_seq == 0)
		pstat->expire_to = pstapriv->auth_to;

	अगर ((pstat->auth_seq + 1) != seq) अणु
		DBG_88E("(1)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
			seq, pstat->auth_seq + 1);
		status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
		जाओ auth_fail;
	पूर्ण

	अगर (algorithm == 0 && (auth_mode == 0 || auth_mode == 2)) अणु
		अगर (seq == 1) अणु
			pstat->state &= ~WIFI_FW_AUTH_शून्य;
			pstat->state |= WIFI_FW_AUTH_SUCCESS;
			pstat->expire_to = pstapriv->assoc_to;
			pstat->authalg = algorithm;
		पूर्ण अन्यथा अणु
			DBG_88E("(2)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
				seq, pstat->auth_seq + 1);
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			जाओ auth_fail;
		पूर्ण
	पूर्ण अन्यथा अणु /*  shared प्रणाली or स्वतः authentication */
		अगर (seq == 1) अणु
			/* prepare क्रम the challenging txt... */

			pstat->state &= ~WIFI_FW_AUTH_शून्य;
			pstat->state |= WIFI_FW_AUTH_STATE;
			pstat->authalg = algorithm;
			pstat->auth_seq = 2;
		पूर्ण अन्यथा अगर (seq == 3) अणु
			/* checking क्रम challenging txt... */
			DBG_88E("checking for challenging txt...\n");

			p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + 4 + _AUTH_IE_OFFSET_, WLAN_EID_CHALLENGE, &ie_len,
				       len - WLAN_HDR_A3_LEN - _AUTH_IE_OFFSET_ - 4);

			अगर (!p || ie_len <= 0) अणु
				DBG_88E("auth rejected because challenge failure!(1)\n");
				status = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ auth_fail;
			पूर्ण

			अगर (!स_भेद((व्योम *)(p + 2), pstat->chg_txt, 128)) अणु
				pstat->state &= (~WIFI_FW_AUTH_STATE);
				pstat->state |= WIFI_FW_AUTH_SUCCESS;
				/*  challenging txt is correct... */
				pstat->expire_to =  pstapriv->assoc_to;
			पूर्ण अन्यथा अणु
				DBG_88E("auth rejected because challenge failure!\n");
				status = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ auth_fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			DBG_88E("(3)auth rejected because out of seq [rx_seq=%d, exp_seq=%d]!\n",
				seq, pstat->auth_seq + 1);
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			जाओ auth_fail;
		पूर्ण
	पूर्ण

	/*  Now, we are going to issue_auth... */
	pstat->auth_seq = seq + 1;

	issue_auth(padapter, pstat, (अचिन्हित लघु)(WLAN_STATUS_SUCCESS));

	अगर (pstat->state & WIFI_FW_AUTH_SUCCESS)
		pstat->auth_seq = 0;

	वापस _SUCCESS;

auth_fail:

	अगर (pstat)
		rtw_मुक्त_stainfo(padapter, pstat);

	pstat = &stat;
	स_रखो((अक्षर *)pstat, '\0', माप(stat));
	pstat->auth_seq = 2;
	स_नकल(pstat->hwaddr, sa, 6);

	issue_auth(padapter, pstat, (अचिन्हित लघु)status);

	वापस _FAIL;
पूर्ण
#पूर्ण_अगर /* CONFIG_88EU_AP_MODE */

अटल अचिन्हित पूर्णांक OnAuthClient(काष्ठा adapter *padapter,
				 काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक seq, len, status, offset;
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक go2asoc = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक pkt_len = precv_frame->pkt->len;

	DBG_88E("%s\n", __func__);

	/* check A1 matches or not */
	अगर (स_भेद(myid(&padapter->eeprompriv), ieee80211_get_DA((काष्ठा ieee80211_hdr *)pframe), ETH_ALEN))
		वापस _SUCCESS;

	अगर (!(pmlmeinfo->state & WIFI_FW_AUTH_STATE))
		वापस _SUCCESS;

	offset = (GetPrivacy(pframe)) ? 4 : 0;

	seq	= le16_to_cpu(*(__le16 *)((माप_प्रकार)pframe + WLAN_HDR_A3_LEN + offset + 2));
	status	= le16_to_cpu(*(__le16 *)((माप_प्रकार)pframe + WLAN_HDR_A3_LEN + offset + 4));

	अगर (status != 0) अणु
		DBG_88E("clnt auth fail, status: %d\n", status);
		अगर (status == 13) अणु /*  pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Auto) */
			अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared)
				pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Open;
			अन्यथा
				pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Shared;
		पूर्ण

		set_link_समयr(pmlmeext, 1);
		जाओ authclnt_fail;
	पूर्ण

	अगर (seq == 2) अणु
		अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared) अणु
			/*  legendary shared प्रणाली */
			p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _AUTH_IE_OFFSET_, WLAN_EID_CHALLENGE, &len,
				       pkt_len - WLAN_HDR_A3_LEN - _AUTH_IE_OFFSET_);

			अगर (!p)
				जाओ authclnt_fail;

			स_नकल((व्योम *)(pmlmeinfo->chg_txt), (व्योम *)(p + 2), len);
			pmlmeinfo->auth_seq = 3;
			issue_auth(padapter, शून्य, 0);
			set_link_समयr(pmlmeext, REAUTH_TO);

			वापस _SUCCESS;
		पूर्ण
		/*  खोलो प्रणाली */
		go2asoc = 1;
	पूर्ण अन्यथा अगर (seq == 4) अणु
		अगर (pmlmeinfo->auth_algo == करोt11AuthAlgrthm_Shared)
			go2asoc = 1;
		अन्यथा
			जाओ authclnt_fail;
	पूर्ण अन्यथा अणु
		/*  this is also illegal */
		जाओ authclnt_fail;
	पूर्ण

	अगर (go2asoc) अणु
		DBG_88E_LEVEL(_drv_info_, "auth success, start assoc\n");
		start_clnt_assoc(padapter);
		वापस _SUCCESS;
	पूर्ण
authclnt_fail:
	वापस _FAIL;
पूर्ण

अटल अचिन्हित पूर्णांक OnAssocReq(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
#अगर_घोषित CONFIG_88EU_AP_MODE
	u16 capab_info;
	काष्ठा rtw_ieee802_11_elems elems;
	काष्ठा sta_info *pstat;
	अचिन्हित अक्षर reassoc, *p, *pos, *wpa_ie;
	अचिन्हित अक्षर WMM_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01पूर्ण;
	पूर्णांक i, wpa_ie_len, left;
	अचिन्हित अक्षर supportRate[16];
	पूर्णांक supportRateNum;
	अचिन्हित लघु status = WLAN_STATUS_SUCCESS;
	अचिन्हित लघु frame_type, ie_offset = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur = &pmlmeinfo->network;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक ie_len, pkt_len = precv_frame->pkt->len;

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		वापस _FAIL;

	frame_type = GetFrameSubType(pframe);
	अगर (frame_type == WIFI_ASSOCREQ) अणु
		reassoc = 0;
		ie_offset = _ASOCREQ_IE_OFFSET_;
	पूर्ण अन्यथा अणु /*  WIFI_REASSOCREQ */
		reassoc = 1;
		ie_offset = _REASOCREQ_IE_OFFSET_;
	पूर्ण

	अगर (pkt_len < IEEE80211_3ADDR_LEN + ie_offset) अणु
		DBG_88E("handle_assoc(reassoc=%d) - too short payload (len=%lu)"
		       "\n", reassoc, (अचिन्हित दीर्घ)pkt_len);
		वापस _FAIL;
	पूर्ण

	pstat = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
	अगर (!pstat) अणु
		status = WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA;
		जाओ asoc_class2_error;
	पूर्ण

	capab_info = get_unaligned_le16(pframe + WLAN_HDR_A3_LEN);

	left = pkt_len - (IEEE80211_3ADDR_LEN + ie_offset);
	pos = pframe + (IEEE80211_3ADDR_LEN + ie_offset);

	DBG_88E("%s\n", __func__);

	/*  check अगर this stat has been successfully authenticated/assocated */
	अगर (!((pstat->state) & WIFI_FW_AUTH_SUCCESS)) अणु
		अगर (!((pstat->state) & WIFI_FW_ASSOC_SUCCESS)) अणु
			status = WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA;
			जाओ asoc_class2_error;
		पूर्ण अन्यथा अणु
			pstat->state &= (~WIFI_FW_ASSOC_SUCCESS);
			pstat->state |= WIFI_FW_ASSOC_STATE;
		पूर्ण
	पूर्ण अन्यथा अणु
		pstat->state &= (~WIFI_FW_AUTH_SUCCESS);
		pstat->state |= WIFI_FW_ASSOC_STATE;
	पूर्ण
	pstat->capability = capab_info;
	/* now parse all ieee802_11 ie to poपूर्णांक to elems */
	अगर (rtw_ieee802_11_parse_elems(pos, left, &elems, 1) == ParseFailed ||
	    !elems.ssid) अणु
		DBG_88E("STA %pM sent invalid association request\n",
			pstat->hwaddr);
		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ OnAssocReqFail;
	पूर्ण

	/*  now we should check all the fields... */
	/*  checking SSID */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_SSID, &ie_len,
		       pkt_len - WLAN_HDR_A3_LEN - ie_offset);

	अगर (!p || ie_len == 0) अणु
		/*  broadcast ssid, however it is not allowed in assocreq */
		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ OnAssocReqFail;
	पूर्ण अन्यथा अणु
		/*  check अगर ssid match */
		अगर (स_भेद((व्योम *)(p + 2), cur->ssid.ssid, cur->ssid.ssid_length))
			status = WLAN_STATUS_UNSPECIFIED_FAILURE;

		अगर (ie_len != cur->ssid.ssid_length)
			status = WLAN_STATUS_UNSPECIFIED_FAILURE;
	पूर्ण

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	/*  check अगर the supported rate is ok */
	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_SUPP_RATES, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
	अगर (!p) अणु
		DBG_88E("Rx a sta assoc-req which supported rate is empty!\n");
		/*  use our own rate set as stम_से_पn used */
		/* स_नकल(supportRate, AP_BSSRATE, AP_BSSRATE_LEN); */
		/* supportRateNum = AP_BSSRATE_LEN; */

		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ OnAssocReqFail;
	पूर्ण अन्यथा अणु
		स_नकल(supportRate, p + 2, ie_len);
		supportRateNum = ie_len;

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + ie_offset, WLAN_EID_EXT_SUPP_RATES, &ie_len,
			       pkt_len - WLAN_HDR_A3_LEN - ie_offset);
		अगर (p) अणु
			अगर (supportRateNum <= माप(supportRate)) अणु
				स_नकल(supportRate + supportRateNum,
				       p + 2, ie_len);
				supportRateNum += ie_len;
			पूर्ण
		पूर्ण
	पूर्ण

	/* toकरो: mask supportRate between AP & STA -> move to update raid */
	/* get_matched_rate(pmlmeext, supportRate, &supportRateNum, 0); */

	/* update station supportRate */
	pstat->bssratelen = supportRateNum;
	स_नकल(pstat->bssrateset, supportRate, supportRateNum);
	UpdateBrateTblForSoftAP(pstat->bssrateset, pstat->bssratelen);

	/* check RSN/WPA/WPS */
	pstat->करोt8021xalg = 0;
	pstat->wpa_psk = 0;
	pstat->wpa_group_cipher = 0;
	pstat->wpa2_group_cipher = 0;
	pstat->wpa_pairwise_cipher = 0;
	pstat->wpa2_pairwise_cipher = 0;
	स_रखो(pstat->wpa_ie, 0, माप(pstat->wpa_ie));
	अगर ((psecuritypriv->wpa_psk & BIT(1)) && elems.rsn_ie) अणु
		पूर्णांक group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.rsn_ie;
		wpa_ie_len = elems.rsn_ie_len;

		अगर (rtw_parse_wpa2_ie(wpa_ie - 2, wpa_ie_len + 2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			pstat->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			pstat->wpa_psk |= BIT(1);

			pstat->wpa2_group_cipher = group_cipher & psecuritypriv->wpa2_group_cipher;
			pstat->wpa2_pairwise_cipher = pairwise_cipher & psecuritypriv->wpa2_pairwise_cipher;

			अगर (!pstat->wpa2_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			अगर (!pstat->wpa2_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;
		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_INVALID_IE;
		पूर्ण
	पूर्ण अन्यथा अगर ((psecuritypriv->wpa_psk & BIT(0)) && elems.wpa_ie) अणु
		पूर्णांक group_cipher = 0, pairwise_cipher = 0;

		wpa_ie = elems.wpa_ie;
		wpa_ie_len = elems.wpa_ie_len;

		अगर (rtw_parse_wpa_ie(wpa_ie - 2, wpa_ie_len + 2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			pstat->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			pstat->wpa_psk |= BIT(0);

			pstat->wpa_group_cipher = group_cipher & psecuritypriv->wpa_group_cipher;
			pstat->wpa_pairwise_cipher = pairwise_cipher & psecuritypriv->wpa_pairwise_cipher;

			अगर (!pstat->wpa_group_cipher)
				status = WLAN_STATUS_INVALID_GROUP_CIPHER;

			अगर (!pstat->wpa_pairwise_cipher)
				status = WLAN_STATUS_INVALID_PAIRWISE_CIPHER;
		पूर्ण अन्यथा अणु
			status = WLAN_STATUS_INVALID_IE;
		पूर्ण
	पूर्ण अन्यथा अणु
		wpa_ie = शून्य;
		wpa_ie_len = 0;
	पूर्ण

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	pstat->flags &= ~(WLAN_STA_WPS | WLAN_STA_MAYBE_WPS);
	अगर (!wpa_ie) अणु
		अगर (elems.wps_ie) अणु
			DBG_88E("STA included WPS IE in "
				   "(Re)Association Request - assume WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			/* wpabuf_मुक्त(sta->wps_ie); */
			/* sta->wps_ie = wpabuf_alloc_copy(elems.wps_ie + 4, */
			/*				elems.wps_ie_len - 4); */
		पूर्ण अन्यथा अणु
			DBG_88E("STA did not include WPA/RSN IE "
				   "in (Re)Association Request - possible WPS "
				   "use\n");
			pstat->flags |= WLAN_STA_MAYBE_WPS;
		पूर्ण

		/*  AP support WPA/RSN, and sta is going to करो WPS, but AP is not पढ़ोy */
		/*  that the selected registrar of AP is _FLASE */
		अगर ((psecuritypriv->wpa_psk > 0) && (pstat->flags & (WLAN_STA_WPS | WLAN_STA_MAYBE_WPS))) अणु
			अगर (pmlmepriv->wps_beacon_ie) अणु
				u8 selected_registrar = 0;

				rtw_get_wps_attr_content(pmlmepriv->wps_beacon_ie, pmlmepriv->wps_beacon_ie_len, WPS_ATTR_SELECTED_REGISTRAR, &selected_registrar, शून्य);

				अगर (!selected_registrar) अणु
					DBG_88E("selected_registrar is false , or AP is not ready to do WPS\n");

					status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;

					जाओ OnAssocReqFail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक copy_len;

		अगर (psecuritypriv->wpa_psk == 0) अणु
			DBG_88E("STA %pM: WPA/RSN IE in association "
			"request, but AP don't support WPA/RSN\n", pstat->hwaddr);

			status = WLAN_STATUS_INVALID_IE;

			जाओ OnAssocReqFail;
		पूर्ण

		अगर (elems.wps_ie) अणु
			DBG_88E("STA included WPS IE in "
				   "(Re)Association Request - WPS is "
				   "used\n");
			pstat->flags |= WLAN_STA_WPS;
			copy_len = 0;
		पूर्ण अन्यथा अणु
			copy_len = min_t(पूर्णांक, wpa_ie_len + 2, माप(pstat->wpa_ie));
		पूर्ण
		अगर (copy_len > 0)
			स_नकल(pstat->wpa_ie, wpa_ie - 2, copy_len);
	पूर्ण
	/*  check अगर there is WMM IE & support WWM-PS */
	pstat->flags &= ~WLAN_STA_WME;
	pstat->qos_option = 0;
	pstat->qos_info = 0;
	pstat->has_legacy_ac = true;
	pstat->uapsd_vo = 0;
	pstat->uapsd_vi = 0;
	pstat->uapsd_be = 0;
	pstat->uapsd_bk = 0;
	अगर (pmlmepriv->qospriv.qos_option) अणु
		p = pframe + WLAN_HDR_A3_LEN + ie_offset; ie_len = 0;
		क्रम (;;) अणु
			p = rtw_get_ie(p, WLAN_EID_VENDOR_SPECIFIC, &ie_len, pkt_len - WLAN_HDR_A3_LEN - ie_offset);
			अगर (p) अणु
				अगर (!स_भेद(p + 2, WMM_IE, 6)) अणु
					pstat->flags |= WLAN_STA_WME;

					pstat->qos_option = 1;
					pstat->qos_info = *(p + 8);

					pstat->max_sp_len = (pstat->qos_info >> 5) & 0x3;

					अगर ((pstat->qos_info & 0xf) != 0xf)
						pstat->has_legacy_ac = true;
					अन्यथा
						pstat->has_legacy_ac = false;

					अगर (pstat->qos_info & 0xf) अणु
						अगर (pstat->qos_info & BIT(0))
							pstat->uapsd_vo = BIT(0) | BIT(1);
						अन्यथा
							pstat->uapsd_vo = 0;

						अगर (pstat->qos_info & BIT(1))
							pstat->uapsd_vi = BIT(0) | BIT(1);
						अन्यथा
							pstat->uapsd_vi = 0;

						अगर (pstat->qos_info & BIT(2))
							pstat->uapsd_bk = BIT(0) | BIT(1);
						अन्यथा
							pstat->uapsd_bk = 0;

						अगर (pstat->qos_info & BIT(3))
							pstat->uapsd_be = BIT(0) | BIT(1);
						अन्यथा
							pstat->uapsd_be = 0;
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
			p = p + ie_len + 2;
		पूर्ण
	पूर्ण

	/* save HT capabilities in the sta object */
	स_रखो(&pstat->htpriv.ht_cap, 0, माप(काष्ठा ieee80211_ht_cap));
	अगर (elems.ht_capabilities &&
	    elems.ht_capabilities_len >= माप(काष्ठा ieee80211_ht_cap)) अणु
		pstat->flags |= WLAN_STA_HT;

		pstat->flags |= WLAN_STA_WME;

		स_नकल(&pstat->htpriv.ht_cap,
		       elems.ht_capabilities, माप(काष्ठा ieee80211_ht_cap));
	पूर्ण अन्यथा अणु
		pstat->flags &= ~WLAN_STA_HT;
	पूर्ण
	अगर ((!pmlmepriv->htpriv.ht_option) && (pstat->flags & WLAN_STA_HT)) अणु
		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ OnAssocReqFail;
	पूर्ण

	अगर ((pstat->flags & WLAN_STA_HT) &&
	    ((pstat->wpa2_pairwise_cipher & WPA_CIPHER_TKIP) ||
	    (pstat->wpa_pairwise_cipher & WPA_CIPHER_TKIP))) अणु
		DBG_88E("HT: %pM tried to "
			"use TKIP with HT association\n", pstat->hwaddr);

		/* status = WLAN_STATUS_CIPHER_REJECTED_PER_POLICY; */
		/* जाओ OnAssocReqFail; */
	पूर्ण

	pstat->flags |= WLAN_STA_NONERP;
	क्रम (i = 0; i < pstat->bssratelen; i++) अणु
		अगर ((pstat->bssrateset[i] & 0x7f) > 22) अणु
			pstat->flags &= ~WLAN_STA_NONERP;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pstat->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		pstat->flags |= WLAN_STA_SHORT_PREAMBLE;
	अन्यथा
		pstat->flags &= ~WLAN_STA_SHORT_PREAMBLE;

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ OnAssocReqFail;

	/* TODO: identअगरy_proprietary_venकरोr_ie(); */
	/*  Realtek proprietary IE */
	/*  identअगरy अगर this is Broadcom sta */
	/*  identअगरy अगर this is ralink sta */
	/*  Customer proprietary IE */

	/* get a unique AID */
	अगर (pstat->aid > 0) अणु
		DBG_88E("  old AID %d\n", pstat->aid);
	पूर्ण अन्यथा अणु
		क्रम (pstat->aid = 1; pstat->aid <= NUM_STA; pstat->aid++)
			अगर (!pstapriv->sta_aid[pstat->aid - 1])
				अवरोध;

		/* अगर (pstat->aid > NUM_STA) अणु */
		अगर (pstat->aid > pstapriv->max_num_sta) अणु
			pstat->aid = 0;

			DBG_88E("  no room for more AIDs\n");

			status = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;

			जाओ OnAssocReqFail;
		पूर्ण अन्यथा अणु
			pstapriv->sta_aid[pstat->aid - 1] = pstat;
			DBG_88E("allocate new AID=(%d)\n", pstat->aid);
		पूर्ण
	पूर्ण

	pstat->state &= (~WIFI_FW_ASSOC_STATE);
	pstat->state |= WIFI_FW_ASSOC_SUCCESS;

	spin_lock_bh(&pstapriv->auth_list_lock);
	अगर (!list_empty(&pstat->auth_list)) अणु
		list_del_init(&pstat->auth_list);
		pstapriv->auth_list_cnt--;
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	spin_lock_bh(&pstapriv->asoc_list_lock);
	अगर (list_empty(&pstat->asoc_list)) अणु
		pstat->expire_to = pstapriv->expire_to;
		list_add_tail(&pstat->asoc_list, &pstapriv->asoc_list);
		pstapriv->asoc_list_cnt++;
	पूर्ण
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	/*  now the station is qualअगरied to join our BSS... */
	अगर ((pstat->state & WIFI_FW_ASSOC_SUCCESS) && (status == WLAN_STATUS_SUCCESS)) अणु
		/* 1 bss_cap_update & sta_info_update */
		bss_cap_update_on_sta_join(padapter, pstat);
		sta_info_update(padapter, pstat);

		/* issue assoc rsp beक्रमe notअगरy station join event. */
		अगर (frame_type == WIFI_ASSOCREQ)
			issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
		अन्यथा
			issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

		/* 2 - report to upper layer */
		DBG_88E("indicate_sta_join_event to upper layer - hostapd\n");
		rtw_indicate_sta_assoc_event(padapter, pstat);

		/* 3-(1) report sta add event */
		report_add_sta_event(padapter, pstat->hwaddr, pstat->aid);
	पूर्ण

	वापस _SUCCESS;

asoc_class2_error:

	issue_deauth(padapter, (व्योम *)GetAddr2Ptr(pframe), status);

	वापस _FAIL;

OnAssocReqFail:

	pstat->aid = 0;
	अगर (frame_type == WIFI_ASSOCREQ)
		issue_asocrsp(padapter, status, pstat, WIFI_ASSOCRSP);
	अन्यथा
		issue_asocrsp(padapter, status, pstat, WIFI_REASSOCRSP);

#पूर्ण_अगर /* CONFIG_88EU_AP_MODE */

	वापस _FAIL;
पूर्ण

अटल अचिन्हित पूर्णांक OnAssocRsp(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	uपूर्णांक i;
	पूर्णांक res;
	अचिन्हित लघु status;
	काष्ठा ndis_802_11_var_ie *pIE;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	uपूर्णांक pkt_len = precv_frame->pkt->len;

	DBG_88E("%s\n", __func__);

	/* check A1 matches or not */
	अगर (स_भेद(myid(&padapter->eeprompriv), ieee80211_get_DA((काष्ठा ieee80211_hdr *)pframe), ETH_ALEN))
		वापस _SUCCESS;

	अगर (!(pmlmeinfo->state & (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE)))
		वापस _SUCCESS;

	अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)
		वापस _SUCCESS;

	del_समयr_sync(&pmlmeext->link_समयr);

	/* status */
	status = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN + 2));
	अगर (status > 0) अणु
		DBG_88E("assoc reject, status code: %d\n", status);
		pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		res = -4;
		जाओ report_assoc_result;
	पूर्ण

	/* get capabilities */
	pmlmeinfo->capability = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	/* set slot समय */
	pmlmeinfo->slotTime = (pmlmeinfo->capability & BIT(10)) ? 9 : 20;

	/* AID */
	pmlmeinfo->aid = (पूर्णांक)(le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN + 4)) & 0x3fff);
	res = pmlmeinfo->aid;

	/* following are moved to join event callback function */
	/* to handle HT, WMM, rate adaptive, update MAC reg */
	/* क्रम not to handle the synchronous IO in the tasklet */
	क्रम (i = 6 + WLAN_HDR_A3_LEN; i < pkt_len;) अणु
		pIE = (काष्ठा ndis_802_11_var_ie *)(pframe + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (!स_भेद(pIE->data, WMM_PARA_OUI, 6)) /* WMM */
				WMM_param_handler(padapter, pIE);
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:	/* HT caps */
			HT_caps_handler(padapter, pIE);
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:	/* HT info */
			HT_info_handler(padapter, pIE);
			अवरोध;
		हाल WLAN_EID_ERP_INFO:
			ERP_IE_handler(padapter, pIE);
		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण

	pmlmeinfo->state &= (~WIFI_FW_ASSOC_STATE);
	pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;

	UpdateBrateTbl(padapter, pmlmeinfo->network.SupportedRates);

report_assoc_result:
	अगर (res > 0)
		rtw_buf_update(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len, pframe, pkt_len);
	अन्यथा
		rtw_buf_मुक्त(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len);

	report_join_res(padapter, res);

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnDeAuth(काष्ठा adapter *padapter,
			     काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित लघु reason;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	/* check A3 */
	अगर (स_भेद(GetAddr3Ptr(pframe), pnetwork->MacAddress, ETH_ALEN))
		वापस _SUCCESS;

	reason = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	DBG_88E("%s Reason code(%d)\n", __func__, reason);

#अगर_घोषित CONFIG_88EU_AP_MODE
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		DBG_88E_LEVEL(_drv_always_, "ap recv deauth reason code(%d) sta:%pM\n",
			      reason, GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		अगर (psta) अणु
			u8 updated = 0;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			अगर (!list_empty(&psta->asoc_list)) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_मुक्त_sta(padapter, psta, false, reason);
			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update(padapter, updated);
		पूर्ण

		वापस _SUCCESS;
	पूर्ण
#पूर्ण_अगर
	DBG_88E_LEVEL(_drv_always_, "sta recv deauth reason code(%d) sta:%pM\n",
		      reason, GetAddr3Ptr(pframe));

	receive_disconnect(padapter, GetAddr3Ptr(pframe), reason);

	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnDisassoc(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	u16 reason;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	/* check A3 */
	अगर (स_भेद(GetAddr3Ptr(pframe), pnetwork->MacAddress, ETH_ALEN))
		वापस _SUCCESS;

	reason = le16_to_cpu(*(__le16 *)(pframe + WLAN_HDR_A3_LEN));

	DBG_88E("%s Reason code(%d)\n", __func__, reason);

#अगर_घोषित CONFIG_88EU_AP_MODE
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		DBG_88E_LEVEL(_drv_always_, "ap recv disassoc reason code(%d) sta:%pM\n",
			      reason, GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		अगर (psta) अणु
			u8 updated = 0;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			अगर (!list_empty(&psta->asoc_list)) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_मुक्त_sta(padapter, psta, false, reason);
			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update(padapter, updated);
		पूर्ण

		वापस _SUCCESS;
	पूर्ण
#पूर्ण_अगर
	DBG_88E_LEVEL(_drv_always_, "ap recv disassoc reason code(%d) sta:%pM\n",
		      reason, GetAddr3Ptr(pframe));

	receive_disconnect(padapter, GetAddr3Ptr(pframe), reason);

	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnAtim(काष्ठा adapter *padapter,
			   काष्ठा recv_frame *precv_frame)
अणु
	DBG_88E("%s\n", __func__);
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_spct(काष्ठा adapter *padapter,
				   काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 category;
	u8 action;

	DBG_88E(FUNC_NDEV_FMT"\n", FUNC_NDEV_ARG(padapter->pnetdev));

	psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));

	अगर (!psta)
		जाओ निकास;

	category = frame_body[0];
	अगर (category != RTW_WLAN_CATEGORY_SPECTRUM_MGMT)
		जाओ निकास;

	action = frame_body[1];
	चयन (action) अणु
	हाल WLAN_ACTION_SPCT_MSR_REQ:
	हाल WLAN_ACTION_SPCT_MSR_RPRT:
	हाल WLAN_ACTION_SPCT_TPC_REQ:
	हाल WLAN_ACTION_SPCT_TPC_RPRT:
		अवरोध;
	हाल WLAN_ACTION_SPCT_CHL_SWITCH:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

निकास:
	वापस _FAIL;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_qos(काष्ठा adapter *padapter,
				 काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_dls(काष्ठा adapter *padapter,
				 काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_back(काष्ठा adapter *padapter,
				  काष्ठा recv_frame *precv_frame)
अणु
	u8 *addr;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	अचिन्हित अक्षर *frame_body;
	अचिन्हित अक्षर category, action;
	अचिन्हित लघु tid, status, reason_code = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 *pframe = precv_frame->pkt->data;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	/* check RA matches or not */
	अगर (स_भेद(myid(&padapter->eeprompriv), GetAddr1Ptr(pframe),
		   ETH_ALEN))/* क्रम अगर1, sta/ap mode */
		वापस _SUCCESS;

	DBG_88E("%s\n", __func__);

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		अगर (!(pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
			वापस _SUCCESS;

	addr = GetAddr2Ptr(pframe);
	psta = rtw_get_stainfo(pstapriv, addr);

	अगर (!psta)
		वापस _SUCCESS;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));

	category = frame_body[0];
	अगर (category == RTW_WLAN_CATEGORY_BACK) अणु /*  representing Block Ack */
		अगर (!pmlmeinfo->HT_enable)
			वापस _SUCCESS;
		action = frame_body[1];
		DBG_88E("%s, action=%d\n", __func__, action);
		चयन (action) अणु
		हाल RTW_WLAN_ACTION_ADDBA_REQ: /* ADDBA request */
			स_नकल(&pmlmeinfo->ADDBA_req, &frame_body[2], माप(काष्ठा ADDBA_request));
			process_addba_req(padapter, (u8 *)&pmlmeinfo->ADDBA_req, addr);

			/* 37 = reject ADDBA Req */
			issue_action_BA(padapter, addr,
					RTW_WLAN_ACTION_ADDBA_RESP,
					pmlmeinfo->accept_addba_req ? 0 : 37);
			अवरोध;
		हाल RTW_WLAN_ACTION_ADDBA_RESP: /* ADDBA response */
			status = get_unaligned_le16(&frame_body[3]);
			tid = (frame_body[5] >> 2) & 0x7;
			अगर (status == 0) अणु	/* successful */
				DBG_88E("agg_enable for TID=%d\n", tid);
				psta->htpriv.agg_enable_biपंचांगap |= 1 << tid;
				psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(tid);
			पूर्ण अन्यथा अणु
				psta->htpriv.agg_enable_biपंचांगap &= ~BIT(tid);
			पूर्ण
			अवरोध;
		हाल RTW_WLAN_ACTION_DELBA: /* DELBA */
			अगर ((frame_body[3] & BIT(3)) == 0) अणु
				psta->htpriv.agg_enable_biपंचांगap &= ~(1 << ((frame_body[3] >> 4) & 0xf));
				psta->htpriv.candidate_tid_biपंचांगap &= ~(1 << ((frame_body[3] >> 4) & 0xf));
				reason_code = get_unaligned_le16(&frame_body[4]);
			पूर्ण अन्यथा अगर ((frame_body[3] & BIT(3)) == BIT(3)) अणु
				tid = (frame_body[3] >> 4) & 0x0F;
				preorder_ctrl =  &psta->recvreorder_ctrl[tid];
				preorder_ctrl->enable = false;
				preorder_ctrl->indicate_seq = 0xffff;
			पूर्ण
			DBG_88E("%s(): DELBA: %x(%x)\n", __func__, pmlmeinfo->agg_enable_biपंचांगap, reason_code);
			/* toकरो: how to notअगरy the host जबतक receiving DELETE BA */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल s32 rtw_action_खुला_decache(काष्ठा recv_frame *recv_frame, s32 token)
अणु
	काष्ठा adapter *adapter = recv_frame->adapter;
	काष्ठा mlme_ext_priv *mlmeext = &adapter->mlmeextpriv;
	u8 *frame = recv_frame->pkt->data;
	u16 seq_ctrl = ((recv_frame->attrib.seq_num & 0xffff) << 4) |
		(recv_frame->attrib.frag_num & 0xf);

	अगर (GetRetry(frame)) अणु
		अगर (token >= 0) अणु
			अगर ((seq_ctrl == mlmeext->action_खुला_rxseq) && (token == mlmeext->action_खुला_dialog_token)) अणु
				DBG_88E(FUNC_ADPT_FMT" seq_ctrl = 0x%x, rxseq = 0x%x, token:%d\n",
					FUNC_ADPT_ARG(adapter), seq_ctrl, mlmeext->action_खुला_rxseq, token);
				वापस _FAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (seq_ctrl == mlmeext->action_खुला_rxseq) अणु
				DBG_88E(FUNC_ADPT_FMT" seq_ctrl = 0x%x, rxseq = 0x%x\n",
					FUNC_ADPT_ARG(adapter), seq_ctrl, mlmeext->action_खुला_rxseq);
				वापस _FAIL;
			पूर्ण
		पूर्ण
	पूर्ण

	mlmeext->action_खुला_rxseq = seq_ctrl;

	अगर (token >= 0)
		mlmeext->action_खुला_dialog_token = token;

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_p2p(काष्ठा recv_frame *precv_frame)
अणु
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body;
	u8 dialogToken = 0;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));
	dialogToken = frame_body[7];

	अगर (rtw_action_खुला_decache(precv_frame, dialogToken) == _FAIL)
		वापस _FAIL;

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_venकरोr(काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);

	अगर (!स_भेद(frame_body + 2, P2P_OUI, 4))
		ret = on_action_खुला_p2p(precv_frame);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला_शेष(काष्ठा recv_frame *precv_frame,
					     u8 action)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 token;

	token = frame_body[2];

	अगर (rtw_action_खुला_decache(precv_frame, token) == _FAIL)
		जाओ निकास;

	ret = _SUCCESS;

निकास:
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक on_action_खुला(काष्ठा adapter *padapter,
				     काष्ठा recv_frame *precv_frame)
अणु
	अचिन्हित पूर्णांक ret = _FAIL;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
	u8 category, action;

	/* check RA matches or not */
	अगर (स_भेद(myid(&padapter->eeprompriv), GetAddr1Ptr(pframe), ETH_ALEN))
		जाओ निकास;

	category = frame_body[0];
	अगर (category != RTW_WLAN_CATEGORY_PUBLIC)
		जाओ निकास;

	action = frame_body[1];
	चयन (action) अणु
	हाल ACT_PUBLIC_VENDOR:
		ret = on_action_खुला_venकरोr(precv_frame);
		अवरोध;
	शेष:
		ret = on_action_खुला_शेष(precv_frame, action);
		अवरोध;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_ht(काष्ठा adapter *padapter,
				काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_wmm(काष्ठा adapter *padapter,
				 काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक OnAction_p2p(काष्ठा adapter *padapter,
				 काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक DoReserved(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	वापस _SUCCESS;
पूर्ण

अटल काष्ठा action_handler OnAction_tbl[] = अणु
	अणुRTW_WLAN_CATEGORY_SPECTRUM_MGMT,	 "ACTION_SPECTRUM_MGMT", on_action_spctपूर्ण,
	अणुRTW_WLAN_CATEGORY_QOS, "ACTION_QOS", &OnAction_qosपूर्ण,
	अणुRTW_WLAN_CATEGORY_DLS, "ACTION_DLS", &OnAction_dlsपूर्ण,
	अणुRTW_WLAN_CATEGORY_BACK, "ACTION_BACK", &OnAction_backपूर्ण,
	अणुRTW_WLAN_CATEGORY_PUBLIC, "ACTION_PUBLIC", on_action_खुलापूर्ण,
	अणुRTW_WLAN_CATEGORY_RADIO_MEASUREMENT, "ACTION_RADIO_MEASUREMENT", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_FT, "ACTION_FT",	&DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_HT,	"ACTION_HT",	&OnAction_htपूर्ण,
	अणुRTW_WLAN_CATEGORY_SA_QUERY, "ACTION_SA_QUERY", &DoReservedपूर्ण,
	अणुRTW_WLAN_CATEGORY_WMM, "ACTION_WMM", &OnAction_wmmपूर्ण,
	अणुRTW_WLAN_CATEGORY_P2P, "ACTION_P2P", &OnAction_p2pपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक OnAction(काष्ठा adapter *padapter,
			     काष्ठा recv_frame *precv_frame)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर category;
	काष्ठा action_handler *ptable;
	अचिन्हित अक्षर *frame_body;
	u8 *pframe = precv_frame->pkt->data;

	frame_body = (अचिन्हित अक्षर *)(pframe + माप(काष्ठा ieee80211_hdr_3addr));

	category = frame_body[0];

	क्रम (i = 0; i < ARRAY_SIZE(OnAction_tbl); i++) अणु
		ptable = &OnAction_tbl[i];
		अगर (category == ptable->num)
			ptable->func(padapter, precv_frame);
	पूर्ण
	वापस _SUCCESS;
पूर्ण

/****************************************************************************

Following are the initialization functions क्रम WiFi MLME

*****************************************************************************/

अटल काष्ठा mlme_handler mlme_sta_tbl[] = अणु
	अणुWIFI_ASSOCREQ,	  "OnAssocReq",	  &OnAssocReqपूर्ण,
	अणुWIFI_ASSOCRSP,	  "OnAssocRsp",	  &OnAssocRspपूर्ण,
	अणुWIFI_REASSOCREQ, "OnReAssocReq", &OnAssocReqपूर्ण,
	अणुWIFI_REASSOCRSP, "OnReAssocRsp", &OnAssocRspपूर्ण,
	अणुWIFI_PROBEREQ,	  "OnProbeReq",	  &OnProbeReqपूर्ण,
	अणुWIFI_PROBERSP,	  "OnProbeRsp",	  &OnProbeRspपूर्ण,
	अणु0,		  "DoReserved",	  &DoReservedपूर्ण,
	अणु0,		  "DoReserved",	  &DoReservedपूर्ण,
	अणुWIFI_BEACON,	  "OnBeacon",	  &OnBeaconपूर्ण,
	अणुWIFI_ATIM,	  "OnATIM",	  &OnAtimपूर्ण,
	अणुWIFI_DISASSOC,	  "OnDisassoc",	  &OnDisassocपूर्ण,
	अणुWIFI_AUTH,	  "OnAuth",	  &OnAuthClientपूर्ण,
	अणुWIFI_DEAUTH,	  "OnDeAuth",	  &OnDeAuthपूर्ण,
	अणुWIFI_ACTION,	  "OnAction",	  &OnActionपूर्ण,
पूर्ण;

पूर्णांक init_hw_mlme_ext(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
	वापस _SUCCESS;
पूर्ण

अटल व्योम init_mlme_ext_priv_value(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	अचिन्हित अक्षर mixed_datarate[NumRates] = अणु
		_1M_RATE_, _2M_RATE_, _5M_RATE_, _11M_RATE_, _6M_RATE_,
		_9M_RATE_, _12M_RATE_, _18M_RATE_, _24M_RATE_, _36M_RATE_,
		_48M_RATE_, _54M_RATE_, 0xff
	पूर्ण;
	अचिन्हित अक्षर mixed_basicrate[NumRates] = अणु
		_1M_RATE_, _2M_RATE_, _5M_RATE_, _11M_RATE_, _6M_RATE_,
		_12M_RATE_, _24M_RATE_, 0xff,
	पूर्ण;

	atomic_set(&pmlmeext->event_seq, 0);
	pmlmeext->mgnt_seq = 0;/* reset to zero when disconnect at client mode */

	pmlmeext->cur_channel = padapter->registrypriv.channel;
	pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pmlmeext->oper_channel = pmlmeext->cur_channel;
	pmlmeext->oper_bwmode = pmlmeext->cur_bwmode;
	pmlmeext->oper_ch_offset = pmlmeext->cur_ch_offset;
	pmlmeext->retry = 0;

	pmlmeext->cur_wireless_mode = padapter->registrypriv.wireless_mode;

	स_नकल(pmlmeext->datarate, mixed_datarate, NumRates);
	स_नकल(pmlmeext->basicrate, mixed_basicrate, NumRates);

	pmlmeext->tx_rate = IEEE80211_CCK_RATE_1MB;

	pmlmeext->sitesurvey_res.state = SCAN_DISABLE;
	pmlmeext->sitesurvey_res.channel_idx = 0;
	pmlmeext->sitesurvey_res.bss_cnt = 0;
	pmlmeext->scan_पात = false;

	pmlmeinfo->state = WIFI_FW_शून्य_STATE;
	pmlmeinfo->reauth_count = 0;
	pmlmeinfo->reassoc_count = 0;
	pmlmeinfo->link_count = 0;
	pmlmeinfo->auth_seq = 0;
	pmlmeinfo->auth_algo = करोt11AuthAlgrthm_Open;
	pmlmeinfo->key_index = 0;
	pmlmeinfo->iv = 0;

	pmlmeinfo->enc_algo = _NO_PRIVACY_;
	pmlmeinfo->authModeToggle = 0;

	स_रखो(pmlmeinfo->chg_txt, 0, 128);

	pmlmeinfo->slotTime = SHORT_SLOT_TIME;
	pmlmeinfo->preamble_mode = PREAMBLE_AUTO;

	pmlmeinfo->dialogToken = 0;

	pmlmeext->action_खुला_rxseq = 0xffff;
	pmlmeext->action_खुला_dialog_token = 0xff;
पूर्ण

अटल पूर्णांक has_channel(काष्ठा rt_channel_info *channel_set,
		       u8 chanset_size, u8 chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chanset_size; i++) अणु
		अगर (channel_set[i].ChannelNum == chan)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_channel_list(काष्ठा adapter *padapter,
			      काष्ठा rt_channel_info *channel_set,
			      u8 chanset_size,
			      काष्ठा p2p_channels *channel_list)
अणु
	काष्ठा p2p_oper_class_map op_class[] = अणु
		अणु IEEE80211G,  81,   1,  13,  1, BW20 पूर्ण,
		अणु IEEE80211G,  82,  14,  14,  1, BW20 पूर्ण,
		अणु -1, 0, 0, 0, 0, BW20 पूर्ण
	पूर्ण;

	पूर्णांक cla, op;

	cla = 0;

	क्रम (op = 0; op_class[op].op_class; op++) अणु
		u8 ch;
		काष्ठा p2p_oper_class_map *o = &op_class[op];
		काष्ठा p2p_reg_class *reg = शून्य;

		क्रम (ch = o->min_chan; ch <= o->max_chan; ch += o->inc) अणु
			अगर (!has_channel(channel_set, chanset_size, ch))
				जारी;

			अगर (!padapter->registrypriv.ht_enable && o->inc == 8)
				जारी;

			अगर ((0 == (padapter->registrypriv.cbw40_enable & BIT(1))) &&
			    ((o->bw == BW40MINUS) || (o->bw == BW40PLUS)))
				जारी;

			अगर (!reg) अणु
				reg = &channel_list->reg_class[cla];
				cla++;
				reg->reg_class = o->op_class;
				reg->channels = 0;
			पूर्ण
			reg->channel[reg->channels] = ch;
			reg->channels++;
		पूर्ण
	पूर्ण
	channel_list->reg_classes = cla;
पूर्ण

अटल u8 init_channel_set(काष्ठा adapter *padapter, u8 ChannelPlan,
			   काष्ठा rt_channel_info *channel_set)
अणु
	u8 index, chanset_size = 0;
	u8 b2_4GBand = false;
	u8 Index2G = 0;

	स_रखो(channel_set, 0, माप(काष्ठा rt_channel_info) * MAX_CHANNEL_NUM);

	अगर (ChannelPlan >= RT_CHANNEL_DOMAIN_MAX && ChannelPlan != RT_CHANNEL_DOMAIN_REALTEK_DEFINE) अणु
		DBG_88E("ChannelPlan ID %x error !!!!!\n", ChannelPlan);
		वापस chanset_size;
	पूर्ण

	अगर (padapter->registrypriv.wireless_mode & WIRELESS_11G) अणु
		b2_4GBand = true;
		अगर (ChannelPlan == RT_CHANNEL_DOMAIN_REALTEK_DEFINE)
			Index2G = RTW_CHANNEL_PLAN_MAP_REALTEK_DEFINE.Index2G;
		अन्यथा
			Index2G = RTW_ChannelPlanMap[ChannelPlan].Index2G;
	पूर्ण

	अगर (b2_4GBand) अणु
		क्रम (index = 0; index < RTW_ChannelPlan2G[Index2G].Len; index++) अणु
			channel_set[chanset_size].ChannelNum = RTW_ChannelPlan2G[Index2G].Channel[index];

			अगर ((ChannelPlan == RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN) ||/* Channel 1~11 is active, and 12~14 is passive */
			    (ChannelPlan == RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN_2G)) अणु
				अगर (channel_set[chanset_size].ChannelNum >= 1 && channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				अन्यथा अगर ((channel_set[chanset_size].ChannelNum  >= 12 && channel_set[chanset_size].ChannelNum  <= 14))
					channel_set[chanset_size].ScanType  = SCAN_PASSIVE;
			पूर्ण अन्यथा अगर (ChannelPlan == RT_CHANNEL_DOMAIN_WORLD_WIDE_13 ||
				   Index2G == RT_CHANNEL_DOMAIN_2G_WORLD) अणु/*  channel 12~13, passive scan */
				अगर (channel_set[chanset_size].ChannelNum <= 11)
					channel_set[chanset_size].ScanType = SCAN_ACTIVE;
				अन्यथा
					channel_set[chanset_size].ScanType = SCAN_PASSIVE;
			पूर्ण अन्यथा अणु
				channel_set[chanset_size].ScanType = SCAN_ACTIVE;
			पूर्ण

			chanset_size++;
		पूर्ण
	पूर्ण
	वापस chanset_size;
पूर्ण

पूर्णांक init_mlme_ext_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	pmlmeext->padapter = padapter;

	init_mlme_ext_priv_value(padapter);
	pmlmeinfo->accept_addba_req = pregistrypriv->accept_addba_req;

	init_mlme_ext_समयr(padapter);

#अगर_घोषित CONFIG_88EU_AP_MODE
	init_mlme_ap_info(padapter);
#पूर्ण_अगर

	pmlmeext->max_chan_nums = init_channel_set(padapter, pmlmepriv->ChannelPlan, pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);

	pmlmeext->chan_scan_समय = SURVEY_TO;
	pmlmeext->mlmeext_init = true;

	pmlmeext->active_keep_alive_check = true;

	वापस _SUCCESS;
पूर्ण

व्योम मुक्त_mlme_ext_priv(काष्ठा mlme_ext_priv *pmlmeext)
अणु
	काष्ठा adapter *padapter = pmlmeext->padapter;

	अगर (!padapter)
		वापस;

	अगर (padapter->bDriverStopped) अणु
		del_समयr_sync(&pmlmeext->survey_समयr);
		del_समयr_sync(&pmlmeext->link_समयr);
	पूर्ण
पूर्ण

अटल व्योम _mgt_dispatcher(काष्ठा adapter *padapter,
			    काष्ठा mlme_handler *ptable,
			    काष्ठा recv_frame *precv_frame)
अणु
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 *pframe = precv_frame->pkt->data;

	अगर (ptable->func) अणु
		/* receive the frames that ra(a1) is my address or ra(a1) is bc address. */
		अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN) &&
		    स_भेद(GetAddr1Ptr(pframe), bc_addr, ETH_ALEN))
			वापस;
		ptable->func(padapter, precv_frame);
	पूर्ण
पूर्ण

व्योम mgt_dispatcher(काष्ठा adapter *padapter, काष्ठा recv_frame *precv_frame)
अणु
	पूर्णांक index;
	काष्ठा mlme_handler *ptable;
#अगर_घोषित CONFIG_88EU_AP_MODE
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
#पूर्ण_अगर
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 *pframe = precv_frame->pkt->data;
	काष्ठा sta_info *psta = rtw_get_stainfo(&padapter->stapriv, GetAddr2Ptr(pframe));

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("+%s: type(0x%x) subtype(0x%x)\n", __func__,
		  (अचिन्हित पूर्णांक)GetFrameType(pframe),
		  (अचिन्हित पूर्णांक)GetFrameSubType(pframe)));

	अगर (GetFrameType(pframe) != WIFI_MGT_TYPE) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("%s: type(0x%x) error!\n", __func__,
			  (अचिन्हित पूर्णांक)GetFrameType(pframe)));
		वापस;
	पूर्ण

	/* receive the frames that ra(a1) is my address or ra(a1) is bc address. */
	अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN) &&
	    स_भेद(GetAddr1Ptr(pframe), bc_addr, ETH_ALEN))
		वापस;

	ptable = mlme_sta_tbl;

	index = GetFrameSubType(pframe) >> 4;

	अगर (index > 13) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Currently we do not support reserved sub-fr-type=%d\n", index));
		वापस;
	पूर्ण
	ptable += index;

	अगर (psta) अणु
		अगर (GetRetry(pframe)) अणु
			अगर (precv_frame->attrib.seq_num ==
			    psta->RxMgmtFrameSeqNum) अणु
				/* drop the duplicate management frame */
				DBG_88E("Drop duplicate management frame with seq_num=%d.\n",
					precv_frame->attrib.seq_num);
				वापस;
			पूर्ण
		पूर्ण
		psta->RxMgmtFrameSeqNum = precv_frame->attrib.seq_num;
	पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE
	चयन (GetFrameSubType(pframe)) अणु
	हाल WIFI_AUTH:
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
			ptable->func = &OnAuth;
		अन्यथा
			ptable->func = &OnAuthClient;
		fallthrough;
	हाल WIFI_ASSOCREQ:
	हाल WIFI_REASSOCREQ:
	हाल WIFI_PROBEREQ:
	हाल WIFI_BEACON:
	हाल WIFI_ACTION:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	शेष:
		_mgt_dispatcher(padapter, ptable, precv_frame);
		अवरोध;
	पूर्ण
#अन्यथा
	_mgt_dispatcher(padapter, ptable, precv_frame);
#पूर्ण_अगर
पूर्ण

/****************************************************************************

Following are the functions to report events

*****************************************************************************/

व्योम report_survey_event(काष्ठा adapter *padapter,
			 काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा survey_event *psurvey_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा cmd_priv *pcmdpriv;

	अगर (!padapter)
		वापस;

	pmlmeext = &padapter->mlmeextpriv;
	pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = kzalloc(माप(काष्ठा cmd_obj), GFP_ATOMIC);
	अगर (!pcmd_obj)
		वापस;

	cmdsz = माप(काष्ठा survey_event) + माप(काष्ठा C2HEvent_Header);
	pevtcmd = kzalloc(cmdsz, GFP_ATOMIC);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = _Set_MLME_EVT_CMD_;
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा survey_event);
	pc2h_evt_hdr->ID = _Survey_EVT_;
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	psurvey_evt = (काष्ठा survey_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));

	अगर (collect_bss_info(padapter, precv_frame, &psurvey_evt->bss) == _FAIL) अणु
		kमुक्त(pcmd_obj);
		kमुक्त(pevtcmd);
		वापस;
	पूर्ण

	process_80211d(padapter, &psurvey_evt->bss);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	pmlmeext->sitesurvey_res.bss_cnt++;
पूर्ण

व्योम report_surveyकरोne_event(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा surveyकरोne_event *psurveyकरोne_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!pcmd_obj)
		वापस;

	cmdsz = माप(काष्ठा surveyकरोne_event) + माप(काष्ठा C2HEvent_Header);
	pevtcmd = kzalloc(cmdsz, GFP_KERNEL);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = _Set_MLME_EVT_CMD_;
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा surveyकरोne_event);
	pc2h_evt_hdr->ID = _SurveyDone_EVT_;
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	psurveyकरोne_evt = (काष्ठा surveyकरोne_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	psurveyकरोne_evt->bss_cnt = pmlmeext->sitesurvey_res.bss_cnt;

	DBG_88E("survey done event(%x)\n", psurveyकरोne_evt->bss_cnt);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

व्योम report_join_res(काष्ठा adapter *padapter, पूर्णांक res)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा joinbss_event *pjoinbss_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = kzalloc(माप(काष्ठा cmd_obj), GFP_ATOMIC);
	अगर (!pcmd_obj)
		वापस;

	cmdsz = माप(काष्ठा joinbss_event) + माप(काष्ठा C2HEvent_Header);
	pevtcmd = kzalloc(cmdsz, GFP_ATOMIC);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = _Set_MLME_EVT_CMD_;
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा joinbss_event);
	pc2h_evt_hdr->ID = _JoinBss_EVT_;
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	pjoinbss_evt = (काष्ठा joinbss_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	स_नकल((अचिन्हित अक्षर *)(&pjoinbss_evt->network.network), &pmlmeinfo->network, माप(काष्ठा wlan_bssid_ex));
	pjoinbss_evt->network.join_res	= res;
	pjoinbss_evt->network.aid = res;

	DBG_88E("%s(%d)\n", __func__, res);

	rtw_joinbss_event_prehandle(padapter, (u8 *)&pjoinbss_evt->network);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

व्योम report_del_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr,
			  अचिन्हित लघु reason)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा sta_info *psta;
	पूर्णांक mac_id;
	काष्ठा stadel_event *pdel_sta_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!pcmd_obj)
		वापस;

	cmdsz = माप(काष्ठा stadel_event) + माप(काष्ठा C2HEvent_Header);
	pevtcmd = kzalloc(cmdsz, GFP_KERNEL);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = _Set_MLME_EVT_CMD_;
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा stadel_event);
	pc2h_evt_hdr->ID = _DelSTA_EVT_;
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	pdel_sta_evt = (काष्ठा stadel_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	ether_addr_copy((अचिन्हित अक्षर *)(&pdel_sta_evt->macaddr), MacAddr);
	स_नकल((अचिन्हित अक्षर *)(pdel_sta_evt->rsvd), (अचिन्हित अक्षर *)(&reason), 2);

	psta = rtw_get_stainfo(&padapter->stapriv, MacAddr);
	अगर (psta)
		mac_id = (पूर्णांक)psta->mac_id;
	अन्यथा
		mac_id = -1;

	pdel_sta_evt->mac_id = mac_id;

	DBG_88E("%s: delete STA, mac_id =%d\n", __func__, mac_id);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

व्योम report_add_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr,
			  पूर्णांक cam_idx)
अणु
	काष्ठा cmd_obj *pcmd_obj;
	u8 *pevtcmd;
	u32 cmdsz;
	काष्ठा stassoc_event *padd_sta_evt;
	काष्ठा C2HEvent_Header *pc2h_evt_hdr;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pcmd_obj = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!pcmd_obj)
		वापस;

	cmdsz = माप(काष्ठा stassoc_event) + माप(काष्ठा C2HEvent_Header);
	pevtcmd = kzalloc(cmdsz, GFP_KERNEL);
	अगर (!pevtcmd) अणु
		kमुक्त(pcmd_obj);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&pcmd_obj->list);

	pcmd_obj->cmdcode = _Set_MLME_EVT_CMD_;
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = शून्य;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (काष्ठा C2HEvent_Header *)(pevtcmd);
	pc2h_evt_hdr->len = माप(काष्ठा stassoc_event);
	pc2h_evt_hdr->ID = _AddSTA_EVT_;
	pc2h_evt_hdr->seq = atomic_inc_वापस(&pmlmeext->event_seq);

	padd_sta_evt = (काष्ठा stassoc_event *)(pevtcmd + माप(काष्ठा C2HEvent_Header));
	ether_addr_copy((अचिन्हित अक्षर *)(&padd_sta_evt->macaddr), MacAddr);
	padd_sta_evt->cam_id = cam_idx;

	DBG_88E("%s: add STA\n", __func__);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);
पूर्ण

/****************************************************************************

Following are the event callback functions

*****************************************************************************/

/* क्रम sta/adhoc mode */
व्योम update_sta_info(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	/* ERP */
	VCS_update(padapter, psta);

	/* HT */
	अगर (pmlmepriv->htpriv.ht_option) अणु
		psta->htpriv.ht_option = true;

		psta->htpriv.ampdu_enable = pmlmepriv->htpriv.ampdu_enable;

		अगर (support_लघु_GI(padapter, &pmlmeinfo->HT_caps))
			psta->htpriv.sgi = true;

		psta->qos_option = true;
	पूर्ण अन्यथा अणु
		psta->htpriv.ht_option = false;

		psta->htpriv.ampdu_enable = false;

		psta->htpriv.sgi = false;
		psta->qos_option = false;
	पूर्ण
	psta->htpriv.bwmode = pmlmeext->cur_bwmode;
	psta->htpriv.ch_offset = pmlmeext->cur_ch_offset;

	psta->htpriv.agg_enable_biपंचांगap = 0x0;/* reset */
	psta->htpriv.candidate_tid_biपंचांगap = 0x0;/* reset */

	/* QoS */
	अगर (pmlmepriv->qospriv.qos_option)
		psta->qos_option = true;

	psta->state = _FW_LINKED;
पूर्ण

व्योम mlmeext_joinbss_event_callback(काष्ठा adapter *padapter, पूर्णांक join_res)
अणु
	काष्ठा sta_info *psta, *psta_bmc;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 join_type;
	u16 media_status;

	अगर (join_res < 0) अणु
		join_type = 1;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
		rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

		/* restore to initial setting. */
		update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

		जाओ निकास_mlmeext_joinbss_event_callback;
	पूर्ण

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) अणु
		/* क्रम bc/mc */
		psta_bmc = rtw_get_bcmc_stainfo(padapter);
		अगर (psta_bmc) अणु
			pmlmeinfo->FW_sta_info[psta_bmc->mac_id].psta = psta_bmc;
			update_bmc_sta_support_rate(padapter, psta_bmc->mac_id);
			Update_RA_Entry(padapter, psta_bmc->mac_id);
		पूर्ण
	पूर्ण

	/* turn on dynamic functions */
	Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true);

	/*  update IOT-related issue */
	update_IOT_info(padapter);

	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, cur_network->SupportedRates);

	/* BCN पूर्णांकerval */
	rtw_hal_set_hwreg(padapter, HW_VAR_BEACON_INTERVAL, (u8 *)(&pmlmeinfo->bcn_पूर्णांकerval));

	/* update capability */
	update_capinfo(padapter, pmlmeinfo->capability);

	/* WMM, Update EDCA param */
	WMMOnAssocRsp(padapter);

	/* HT */
	HTOnAssocRsp(padapter);

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
	अगर (psta) अणु /* only क्रम infra. mode */
		pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

		psta->wireless_mode = pmlmeext->cur_wireless_mode;

		/* set per sta rate after updating HT cap. */
		set_sta_rate(padapter, psta);
		rtw_hal_set_hwreg(padapter, HW_VAR_TX_RPT_MAX_MACID, (u8 *)&psta->mac_id);
		media_status = (psta->mac_id << 8) | 1; /*   MACID|OPMODE: 1 means connect */
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status);
	पूर्ण

	join_type = 2;
	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_STATION_STATE) अणु
		/*  correcting TSF */
		correct_TSF(padapter, pmlmeext);
	पूर्ण
	rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_CONNECT, 0);

निकास_mlmeext_joinbss_event_callback:

	DBG_88E("=>%s\n", __func__);
पूर्ण

व्योम mlmeext_sta_add_event_callback(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 join_type;

	DBG_88E("%s\n", __func__);

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) अणु
		अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु/* adhoc master or sta_count>1 */
			/* nothing to करो */
		पूर्ण अन्यथा अणु /* adhoc client */
			/*  correcting TSF */
			correct_TSF(padapter, pmlmeext);

			/* start beacon */
			अगर (send_beacon(padapter) == _FAIL) अणु
				pmlmeinfo->FW_sta_info[psta->mac_id].status = 0;
				pmlmeinfo->state ^= WIFI_FW_ADHOC_STATE;
				वापस;
			पूर्ण
			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;
		पूर्ण

		join_type = 2;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
	पूर्ण

	pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

	/* rate radaptive */
	Update_RA_Entry(padapter, psta->mac_id);

	/* update adhoc sta_info */
	update_sta_info(padapter, psta);
पूर्ण

व्योम mlmeext_sta_del_event_callback(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (is_client_associated_to_ap(padapter) || is_IBSS_empty(padapter)) अणु
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, शून्य);
		rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

		/* restore to initial setting. */
		update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

		/* चयन to the 20M Hz mode after disconnect */
		pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

		/* SelectChannel(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset); */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		flush_all_cam_entry(padapter);

		pmlmeinfo->state = WIFI_FW_शून्य_STATE;

		/* set MSR to no link state -> infra. mode */
		Set_MSR(padapter, _HW_STATE_STATION_);

		del_समयr_sync(&pmlmeext->link_समयr);
	पूर्ण
पूर्ण

/****************************************************************************

Following are the functions क्रम the समयr handlers

*****************************************************************************/

अटल u8 chk_ap_is_alive(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 ret = false;

	अगर ((sta_rx_data_pkts(psta) == sta_last_rx_data_pkts(psta)) &&
	    sta_rx_beacon_pkts(psta) == sta_last_rx_beacon_pkts(psta) &&
	    sta_rx_probersp_pkts(psta) == sta_last_rx_probersp_pkts(psta))
		ret = false;
	अन्यथा
		ret = true;

	sta_update_last_rx_pkts(psta);

	वापस ret;
पूर्ण

व्योम linked_status_chk(काष्ठा adapter *padapter)
अणु
	u32 i;
	काष्ठा sta_info *psta;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (is_client_associated_to_ap(padapter)) अणु
		/* linked infraकाष्ठाure client mode */

		पूर्णांक tx_chk = _SUCCESS, rx_chk = _SUCCESS;
		पूर्णांक rx_chk_limit;

		rx_chk_limit = 4;
		psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress);
		अगर (psta) अणु
			bool is_p2p_enable = false;

			अगर (!chk_ap_is_alive(padapter, psta))
				rx_chk = _FAIL;

			अगर (pxmitpriv->last_tx_pkts == pxmitpriv->tx_pkts)
				tx_chk = _FAIL;

			अगर (pmlmeext->active_keep_alive_check && (rx_chk == _FAIL || tx_chk == _FAIL)) अणु
				u8 backup_oper_channel = 0;

				/* चयन to correct channel of current network  beक्रमe issue keep-alive frames */
				अगर (rtw_get_oper_ch(padapter) != pmlmeext->cur_channel) अणु
					backup_oper_channel = rtw_get_oper_ch(padapter);
					SelectChannel(padapter, pmlmeext->cur_channel);
				पूर्ण

				अगर (rx_chk != _SUCCESS)
					issue_probereq_ex(padapter, &pmlmeinfo->network.ssid, psta->hwaddr, 3, 1);

				अगर ((tx_chk != _SUCCESS && pmlmeinfo->link_count++ == 0xf) || rx_chk != _SUCCESS) अणु
					tx_chk = issue_nulldata(padapter, psta->hwaddr, 0, 3, 1);
					/* अगर tx acked and p2p disabled, set rx_chk _SUCCESS to reset retry count */
					अगर (tx_chk == _SUCCESS && !is_p2p_enable)
						rx_chk = _SUCCESS;
				पूर्ण

				/* back to the original operation channel */
				अगर (backup_oper_channel > 0)
					SelectChannel(padapter, backup_oper_channel);
			पूर्ण अन्यथा अणु
				अगर (rx_chk != _SUCCESS) अणु
					अगर (pmlmeext->retry == 0) अणु
						issue_probereq(padapter, &pmlmeinfo->network.ssid,
							       pmlmeinfo->network.MacAddress,
							       false);
						issue_probereq(padapter, &pmlmeinfo->network.ssid,
							       pmlmeinfo->network.MacAddress,
							       false);
						issue_probereq(padapter, &pmlmeinfo->network.ssid,
							       pmlmeinfo->network.MacAddress,
							       false);
					पूर्ण
				पूर्ण

				अगर (tx_chk != _SUCCESS && pmlmeinfo->link_count++ == 0xf)
					tx_chk = issue_nulldata(padapter, शून्य, 0, 1, 0);
			पूर्ण

			अगर (rx_chk == _FAIL) अणु
				pmlmeext->retry++;
				अगर (pmlmeext->retry > rx_chk_limit) अणु
					DBG_88E_LEVEL(_drv_always_, FUNC_ADPT_FMT" disconnect or roaming\n",
						      FUNC_ADPT_ARG(padapter));
					receive_disconnect(padapter, pmlmeinfo->network.MacAddress,
							   WLAN_REASON_EXPIRATION_CHK);
					वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				pmlmeext->retry = 0;
			पूर्ण

			अगर (tx_chk == _FAIL) अणु
				pmlmeinfo->link_count &= 0xf;
			पूर्ण अन्यथा अणु
				pxmitpriv->last_tx_pkts = pxmitpriv->tx_pkts;
				pmlmeinfo->link_count = 0;
			पूर्ण
		पूर्ण /* end of अगर ((psta = rtw_get_stainfo(pstapriv, passoc_res->network.MacAddress)) != शून्य) */
	पूर्ण अन्यथा अगर (is_client_associated_to_ibss(padapter)) अणु
		/* linked IBSS mode */
		/* क्रम each assoc list entry to check the rx pkt counter */
		क्रम (i = IBSS_START_MAC_ID; i < NUM_STA; i++) अणु
			अगर (pmlmeinfo->FW_sta_info[i].status == 1) अणु
				psta = pmlmeinfo->FW_sta_info[i].psta;

				अगर (!psta)
					जारी;
				अगर (pmlmeinfo->FW_sta_info[i].rx_pkt == sta_rx_pkts(psta)) अणु
					अगर (pmlmeinfo->FW_sta_info[i].retry < 3) अणु
						pmlmeinfo->FW_sta_info[i].retry++;
					पूर्ण अन्यथा अणु
						pmlmeinfo->FW_sta_info[i].retry = 0;
						pmlmeinfo->FW_sta_info[i].status = 0;
						report_del_sta_event(padapter, psta->hwaddr
							, 65535/*  indicate disconnect caused by no rx */
					);
					पूर्ण
				पूर्ण अन्यथा अणु
					pmlmeinfo->FW_sta_info[i].retry = 0;
					pmlmeinfo->FW_sta_info[i].rx_pkt = (u32)sta_rx_pkts(psta);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम survey_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter = from_समयr(padapter, t,
					      mlmeextpriv.survey_समयr);
	काष्ठा cmd_obj *ph2c;
	काष्ठा sitesurvey_parm *psurveyPara;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	/* issue rtw_sitesurvey_cmd */
	अगर (pmlmeext->sitesurvey_res.state > SCAN_START) अणु
		अगर (pmlmeext->sitesurvey_res.state ==  SCAN_PROCESS)
			pmlmeext->sitesurvey_res.channel_idx++;

		अगर (pmlmeext->scan_पात) अणु
			pmlmeext->sitesurvey_res.channel_idx = pmlmeext->sitesurvey_res.ch_num;
			DBG_88E("%s idx:%d\n", __func__
				, pmlmeext->sitesurvey_res.channel_idx);

			pmlmeext->scan_पात = false;/* reset */
		पूर्ण

		ph2c = kzalloc(माप(काष्ठा cmd_obj), GFP_ATOMIC);
		अगर (!ph2c)
			जाओ निकास_survey_समयr_hdl;

		psurveyPara = kzalloc(माप(काष्ठा sitesurvey_parm), GFP_ATOMIC);
		अगर (!psurveyPara) अणु
			kमुक्त(ph2c);
			जाओ निकास_survey_समयr_hdl;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psurveyPara, _SiteSurvey_CMD_);
		rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण

निकास_survey_समयr_hdl:
	वापस;
पूर्ण

व्योम link_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter = from_समयr(padapter, t,
					    mlmeextpriv.link_समयr);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pmlmeinfo->state & WIFI_FW_AUTH_शून्य) अणु
		DBG_88E("%s:no beacon while connecting\n", __func__);
		pmlmeinfo->state = WIFI_FW_शून्य_STATE;
		report_join_res(padapter, -3);
	पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_AUTH_STATE) अणु
		/* re-auth समयr */
		अगर (++pmlmeinfo->reauth_count > REAUTH_LIMIT) अणु
			pmlmeinfo->state = 0;
			report_join_res(padapter, -1);
			वापस;
		पूर्ण

		DBG_88E("%s: auth timeout and try again\n", __func__);
		pmlmeinfo->auth_seq = 1;
		issue_auth(padapter, शून्य, 0);
		set_link_समयr(pmlmeext, REAUTH_TO);
	पूर्ण अन्यथा अगर (pmlmeinfo->state & WIFI_FW_ASSOC_STATE) अणु
		/* re-assoc समयr */
		अगर (++pmlmeinfo->reassoc_count > REASSOC_LIMIT) अणु
			pmlmeinfo->state = WIFI_FW_शून्य_STATE;
			report_join_res(padapter, -2);
			वापस;
		पूर्ण

		DBG_88E("%s: assoc timeout and try again\n", __func__);
		issue_assocreq(padapter);
		set_link_समयr(pmlmeext, REASSOC_TO);
	पूर्ण
पूर्ण

व्योम addba_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा sta_info *psta = from_समयr(psta, t, addba_retry_समयr);
	काष्ठा ht_priv *phtpriv;

	अगर (!psta)
		वापस;

	phtpriv = &psta->htpriv;

	अगर ((phtpriv->ht_option) && (phtpriv->ampdu_enable)) अणु
		अगर (phtpriv->candidate_tid_biपंचांगap)
			phtpriv->candidate_tid_biपंचांगap = 0x0;
	पूर्ण
पूर्ण

u8 setopmode_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 type;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा setopmode_parm *psetop = (काष्ठा setopmode_parm *)pbuf;

	अगर (psetop->mode == Ndis802_11APMode) अणु
		pmlmeinfo->state = WIFI_FW_AP_STATE;
		type = _HW_STATE_AP_;
	पूर्ण अन्यथा अगर (psetop->mode == Ndis802_11Infraकाष्ठाure) अणु
		pmlmeinfo->state &= ~(BIT(0) | BIT(1));/*  clear state */
		pmlmeinfo->state |= WIFI_FW_STATION_STATE;/* set to	STATION_STATE */
		type = _HW_STATE_STATION_;
	पूर्ण अन्यथा अगर (psetop->mode == Ndis802_11IBSS) अणु
		type = _HW_STATE_ADHOC_;
	पूर्ण अन्यथा अणु
		type = _HW_STATE_NOLINK_;
	पूर्ण

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_OPMODE, (u8 *)(&type));
	/* Set_MSR(padapter, type); */

	वापस H2C_SUCCESS;
पूर्ण

u8 createbss_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	काष्ठा wlan_bssid_ex *pparm = (काष्ठा wlan_bssid_ex *)pbuf;

	अगर (pparm->Infraकाष्ठाureMode == Ndis802_11APMode) अणु
#अगर_घोषित CONFIG_88EU_AP_MODE

		अगर (pmlmeinfo->state == WIFI_FW_AP_STATE) अणु
			/* toकरो: */
			वापस H2C_SUCCESS;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* below is क्रम ad-hoc master */
	अगर (pparm->Infraकाष्ठाureMode == Ndis802_11IBSS) अणु
		rtw_joinbss_reset(padapter);

		pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
		pmlmeinfo->ERP_enable = 0;
		pmlmeinfo->WMM_enable = 0;
		pmlmeinfo->HT_enable = 0;
		pmlmeinfo->HT_caps_enable = 0;
		pmlmeinfo->HT_info_enable = 0;
		pmlmeinfo->agg_enable_biपंचांगap = 0;
		pmlmeinfo->candidate_tid_biपंचांगap = 0;

		/* disable dynamic functions, such as high घातer, DIG */
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false);

		/* config the initial gain under linking, need to ग_लिखो the BB रेजिस्टरs */
		/* initialgain = 0x1E; */
		/* rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain)); */

		/* cancel link समयr */
		del_समयr_sync(&pmlmeext->link_समयr);

		/* clear CAM */
		flush_all_cam_entry(padapter);

		स_नकल(pnetwork, pbuf, दुरत्व(काष्ठा wlan_bssid_ex, ie_length));
		pnetwork->ie_length = ((काष्ठा wlan_bssid_ex *)pbuf)->ie_length;

		अगर (pnetwork->ie_length > MAX_IE_SZ)/* Check pbuf->ie_length */
			वापस H2C_PARAMETERS_ERROR;

		स_नकल(pnetwork->ies, ((काष्ठा wlan_bssid_ex *)pbuf)->ies, pnetwork->ie_length);

		start_create_ibss(padapter);
	पूर्ण

	वापस H2C_SUCCESS;
पूर्ण

u8 join_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 join_type;
	काष्ठा ndis_802_11_var_ie *pIE;
	काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	काष्ठा wlan_bssid_ex *pparm = (काष्ठा wlan_bssid_ex *)pbuf;
	u32 i;

	/* check alपढ़ोy connecting to AP or not */
	अगर (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) अणु
		अगर (pmlmeinfo->state & WIFI_FW_STATION_STATE)
			issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, 5, 100);

		pmlmeinfo->state = WIFI_FW_शून्य_STATE;

		/* clear CAM */
		flush_all_cam_entry(padapter);

		del_समयr_sync(&pmlmeext->link_समयr);

		/* set MSR to nolink -> infra. mode */
		Set_MSR(padapter, _HW_STATE_STATION_);

		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, शून्य);
	पूर्ण

	rtw_antenna_select_cmd(padapter, pparm->PhyInfo.Optimum_antenna, false);

	rtw_joinbss_reset(padapter);

	pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pmlmeinfo->ERP_enable = 0;
	pmlmeinfo->WMM_enable = 0;
	pmlmeinfo->HT_enable = 0;
	pmlmeinfo->HT_caps_enable = 0;
	pmlmeinfo->HT_info_enable = 0;
	pmlmeinfo->agg_enable_biपंचांगap = 0;
	pmlmeinfo->candidate_tid_biपंचांगap = 0;
	pmlmeinfo->bwmode_updated = false;

	स_नकल(pnetwork, pbuf, दुरत्व(काष्ठा wlan_bssid_ex, ie_length));
	pnetwork->ie_length = ((काष्ठा wlan_bssid_ex *)pbuf)->ie_length;

	अगर (pnetwork->ie_length > MAX_IE_SZ)/* Check pbuf->ie_length */
		वापस H2C_PARAMETERS_ERROR;

	स_नकल(pnetwork->ies, ((काष्ठा wlan_bssid_ex *)pbuf)->ies, pnetwork->ie_length);

	/* Check AP venकरोr to move rtw_joinbss_cmd() */

	क्रम (i = माप(काष्ठा ndis_802_11_fixed_ie); i < pnetwork->ie_length;) अणु
		pIE = (काष्ठा ndis_802_11_var_ie *)(pnetwork->ies + i);

		चयन (pIE->ElementID) अणु
		हाल WLAN_EID_VENDOR_SPECIFIC:/* Get WMM IE. */
			अगर (!स_भेद(pIE->data, WMM_OUI, 4))
				pmlmeinfo->WMM_enable = 1;
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:	/* Get HT Cap IE. */
			pmlmeinfo->HT_caps_enable = 1;
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:	/* Get HT Info IE. */
			pmlmeinfo->HT_info_enable = 1;

			/* spec हाल only क्रम cisco's ap because cisco's ap issue assoc rsp using mcs rate @40MHz or @20MHz */
			अणु
				काष्ठा HT_info_element *pht_info = (काष्ठा HT_info_element *)(pIE->data);

				अगर ((pregpriv->cbw40_enable) &&	 (pht_info->infos[0] & BIT(2))) अणु
					/* चयन to the 40M Hz mode according to the AP */
					pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_40;
					चयन (pht_info->infos[0] & 0x3) अणु
					हाल 1:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
						अवरोध;
					हाल 3:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
						अवरोध;
					शेष:
						pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
						अवरोध;
				पूर्ण

					DBG_88E("set ch/bw before connected\n");
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		i += (pIE->Length + 2);
	पूर्ण
	/* disable dynamic functions, such as high घातer, DIG */

	/* config the initial gain under linking, need to ग_लिखो the BB रेजिस्टरs */

	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pmlmeinfo->network.MacAddress);
	join_type = 0;
	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

	/* cancel link समयr */
	del_समयr_sync(&pmlmeext->link_समयr);

	start_clnt_join(padapter);

	वापस H2C_SUCCESS;
पूर्ण

u8 disconnect_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा disconnect_parm *param = (काष्ठा disconnect_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	u8 val8;

	अगर (is_client_associated_to_ap(padapter))
		issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, param->deauth_समयout_ms / 100, 100);

	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, शून्य);
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

	/* restore to initial setting. */
	update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

	अगर (((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE)) अणु
		/* Stop BCN */
		val8 = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_BCN_FUNC, (u8 *)(&val8));
	पूर्ण

	/* set MSR to no link state -> infra. mode */
	Set_MSR(padapter, _HW_STATE_STATION_);

	pmlmeinfo->state = WIFI_FW_शून्य_STATE;

	/* चयन to the 20M Hz mode after disconnect */
	pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	flush_all_cam_entry(padapter);

	del_समयr_sync(&pmlmeext->link_समयr);

	rtw_मुक्त_uc_swdec_pending_queue(padapter);

	वापस	H2C_SUCCESS;
पूर्ण

अटल पूर्णांक rtw_scan_ch_decision(काष्ठा adapter *padapter,
				काष्ठा rtw_ieee80211_channel *out,
				u32 out_num,
				काष्ठा rtw_ieee80211_channel *in, u32 in_num)
अणु
	पूर्णांक i, j;
	पूर्णांक set_idx;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	/* clear out first */
	स_रखो(out, 0, माप(काष्ठा rtw_ieee80211_channel) * out_num);

	/* acquire channels from in */
	j = 0;
	क्रम (i = 0; i < in_num; i++) अणु
		set_idx = rtw_ch_set_search_ch(pmlmeext->channel_set, in[i].hw_value);
		अगर (in[i].hw_value && !(in[i].flags & RTW_IEEE80211_CHAN_DISABLED) &&
		    set_idx >= 0) अणु
			out[j] = in[i];

			अगर (pmlmeext->channel_set[set_idx].ScanType == SCAN_PASSIVE)
				out[j].flags &= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

			j++;
		पूर्ण
		अगर (j >= out_num)
			अवरोध;
	पूर्ण

	/* अगर out is empty, use channel_set as शेष */
	अगर (j == 0) अणु
		क्रम (i = 0; i < pmlmeext->max_chan_nums; i++) अणु
			out[i].hw_value = pmlmeext->channel_set[i].ChannelNum;

			अगर (pmlmeext->channel_set[i].ScanType == SCAN_PASSIVE)
				out[i].flags &= RTW_IEEE80211_CHAN_PASSIVE_SCAN;

			j++;
		पूर्ण
	पूर्ण

	वापस j;
पूर्ण

u8 sitesurvey_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा sitesurvey_parm *pparm = (काष्ठा sitesurvey_parm *)pbuf;
	u8 bdelayscan = false;
	u8 val8;
	u32 initialgain;
	u32 i;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_DISABLE) अणु
		/* क्रम first समय sitesurvey_cmd */
		rtw_hal_set_hwreg(padapter, HW_VAR_CHECK_TXBUF, शून्य);

		pmlmeext->sitesurvey_res.state = SCAN_START;
		pmlmeext->sitesurvey_res.bss_cnt = 0;
		pmlmeext->sitesurvey_res.channel_idx = 0;

		क्रम (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) अणु
			अगर (pparm->ssid[i].ssid_length) अणु
				स_नकल(pmlmeext->sitesurvey_res.ssid[i].ssid, pparm->ssid[i].ssid, IW_ESSID_MAX_SIZE);
				pmlmeext->sitesurvey_res.ssid[i].ssid_length = pparm->ssid[i].ssid_length;
			पूर्ण अन्यथा अणु
				pmlmeext->sitesurvey_res.ssid[i].ssid_length = 0;
			पूर्ण
		पूर्ण

		pmlmeext->sitesurvey_res.ch_num = rtw_scan_ch_decision(padapter
			, pmlmeext->sitesurvey_res.ch, RTW_CHANNEL_SCAN_AMOUNT
			, pparm->ch, pparm->ch_num
	);

		pmlmeext->sitesurvey_res.scan_mode = pparm->scan_mode;

		/* issue null data अगर associating to the AP */
		अगर (is_client_associated_to_ap(padapter)) अणु
			pmlmeext->sitesurvey_res.state = SCAN_TXशून्य;

			issue_nulldata(padapter, शून्य, 1, 3, 500);

			bdelayscan = true;
		पूर्ण
		अगर (bdelayscan) अणु
			/* delay 50ms to protect nulldata(1). */
			set_survey_समयr(pmlmeext, 50);
			वापस H2C_SUCCESS;
		पूर्ण
	पूर्ण

	अगर ((pmlmeext->sitesurvey_res.state == SCAN_START) || (pmlmeext->sitesurvey_res.state == SCAN_TXशून्य)) अणु
		/* disable dynamic functions, such as high घातer, DIG */
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false);

		/* config the initial gain under scanning, need to ग_लिखो the BB रेजिस्टरs */
		initialgain = 0x1E;

		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));

		/* set MSR to no link state */
		Set_MSR(padapter, _HW_STATE_NOLINK_);

		val8 = 1; /* under site survey */
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		pmlmeext->sitesurvey_res.state = SCAN_PROCESS;
	पूर्ण

	site_survey(padapter);

	वापस H2C_SUCCESS;
पूर्ण

u8 setauth_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा setauth_parm *pparm = (काष्ठा setauth_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pparm->mode < 4)
		pmlmeinfo->auth_algo = pparm->mode;
	वापस H2C_SUCCESS;
पूर्ण

u8 setkey_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	अचिन्हित लघु ctrl;
	काष्ठा setkey_parm *pparm = (काष्ठा setkey_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 null_sta[ETH_ALEN] = अणुपूर्ण;

	/* मुख्य tx key क्रम wep. */
	अगर (pparm->set_tx)
		pmlmeinfo->key_index = pparm->keyid;

	/* ग_लिखो cam */
	ctrl = BIT(15) | ((pparm->algorithm) << 2) | pparm->keyid;

	DBG_88E_LEVEL(_drv_info_, "set group key to hw: alg:%d(WEP40-1 WEP104-5 TKIP-2 AES-4) "
			"keyid:%d\n", pparm->algorithm, pparm->keyid);
	ग_लिखो_cam(padapter, pparm->keyid, ctrl, null_sta, pparm->key);

	वापस H2C_SUCCESS;
पूर्ण

u8 set_stakey_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u16 ctrl = 0;
	u8 cam_id;/* cam_entry */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा set_stakey_parm *pparm = (काष्ठा set_stakey_parm *)pbuf;

	/* cam_entry: */
	/* 0~3 क्रम शेष key */

	/* क्रम concurrent mode (ap+sta): */
	/* शेष key is disable, using sw encrypt/decrypt */
	/* cam_entry = 4 क्रम sta mode (macid = 0) */
	/* cam_entry(macid+3) = 5 ~ N क्रम ap mode (aid = 1~N, macid = 2 ~N) */

	/* क्रम concurrent mode (sta+sta): */
	/* शेष key is disable, using sw encrypt/decrypt */
	/* cam_entry = 4 mapping to macid = 0 */
	/* cam_entry = 5 mapping to macid = 2 */

	cam_id = 4;

	DBG_88E_LEVEL(_drv_info_, "set pairwise key to hw: alg:%d(WEP40-1 WEP104-5 TKIP-2 AES-4) camid:%d\n",
		      pparm->algorithm, cam_id);
	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE) अणु
		काष्ठा sta_info *psta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		अगर (pparm->algorithm == _NO_PRIVACY_)	/*  clear cam entry */ अणु
			clear_cam_entry(padapter, pparm->id);
			वापस H2C_SUCCESS_RSP;
		पूर्ण

		psta = rtw_get_stainfo(pstapriv, pparm->addr);
		अगर (psta) अणु
			ctrl = BIT(15) | ((pparm->algorithm) << 2);

			DBG_88E("r871x_set_stakey_hdl(): enc_algorithm=%d\n", pparm->algorithm);

			अगर ((psta->mac_id < 1) || (psta->mac_id > (NUM_STA - 4))) अणु
				DBG_88E("r871x_set_stakey_hdl():set_stakey failed, mac_id(aid)=%d\n", psta->mac_id);
				वापस H2C_REJECTED;
			पूर्ण

			cam_id = psta->mac_id + 3;/* 0~3 क्रम शेष key, cmd_id = macid + 3, macid = aid+1; */

			DBG_88E("Write CAM, mac_addr =%pM, cam_entry=%d\n",
				pparm->addr, cam_id);

			ग_लिखो_cam(padapter, cam_id, ctrl, pparm->addr, pparm->key);

			वापस H2C_SUCCESS_RSP;
		पूर्ण

		DBG_88E("r871x_set_stakey_hdl(): sta has been free\n");
		वापस H2C_REJECTED;
	पूर्ण

	/* below क्रम sta mode */

	अगर (pparm->algorithm == _NO_PRIVACY_) अणु	/*  clear cam entry */
		clear_cam_entry(padapter, pparm->id);
		वापस H2C_SUCCESS;
	पूर्ण
	ctrl = BIT(15) | ((pparm->algorithm) << 2);
	ग_लिखो_cam(padapter, cam_id, ctrl, pparm->addr, pparm->key);
	pmlmeinfo->enc_algo = pparm->algorithm;
	वापस H2C_SUCCESS;
पूर्ण

u8 add_ba_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा addBaReq_parm *pparm = (काष्ठा addBaReq_parm *)pbuf;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा sta_info *psta = rtw_get_stainfo(&padapter->stapriv, pparm->addr);

	अगर (!psta)
		वापस H2C_SUCCESS;

	अगर (((pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) && (pmlmeinfo->HT_enable)) ||
	    ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE)) अणु
		issue_action_BA(padapter, pparm->addr, RTW_WLAN_ACTION_ADDBA_REQ, (u16)pparm->tid);
		mod_समयr(&psta->addba_retry_समयr,
			  jअगरfies + msecs_to_jअगरfies(ADDBA_TO));
	पूर्ण अन्यथा अणु
		psta->htpriv.candidate_tid_biपंचांगap &= ~BIT(pparm->tid);
	पूर्ण
	वापस H2C_SUCCESS;
पूर्ण

u8 set_tx_beacon_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा wlan_bssid_ex *ptxBeacon_parm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 res;
	पूर्णांक len_dअगरf = 0;

	ph2c = kzalloc(माप(काष्ठा cmd_obj), GFP_ATOMIC);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	ptxBeacon_parm = kmemdup(&pmlmeinfo->network,
				 माप(काष्ठा wlan_bssid_ex), GFP_ATOMIC);
	अगर (!ptxBeacon_parm) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	len_dअगरf = update_hidden_ssid(ptxBeacon_parm->ies + _BEACON_IE_OFFSET_,
				      ptxBeacon_parm->ie_length - _BEACON_IE_OFFSET_,
				      pmlmeinfo->hidden_ssid_mode);
	ptxBeacon_parm->ie_length += len_dअगरf;

	init_h2fwcmd_w_parm_no_rsp(ph2c, ptxBeacon_parm, _TX_Beacon_CMD_);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:
	वापस res;
पूर्ण

u8 mlme_evt_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	u8 evt_code;
	u16 evt_sz;
	uपूर्णांक *peventbuf;
	व्योम (*event_callback)(काष्ठा adapter *dev, u8 *pbuf);

	peventbuf = (uपूर्णांक *)pbuf;
	evt_sz = (u16)(*peventbuf & 0xffff);
	evt_code = (u8)((*peventbuf >> 16) & 0xff);

	/*  checking अगर event code is valid */
	अगर (evt_code >= MAX_C2HEVT) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\nEvent Code(%d) mismatch!\n", evt_code));
		जाओ _पात_event_;
	पूर्ण

	/*  checking अगर event size match the event parm size */
	अगर ((wlanevents[evt_code].parmsize != 0) &&
	    (wlanevents[evt_code].parmsize != evt_sz)) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\nEvent(%d) Parm Size mismatch (%d vs %d)!\n",
			 evt_code, wlanevents[evt_code].parmsize, evt_sz));
		जाओ _पात_event_;
	पूर्ण

	peventbuf += 2;

	अगर (peventbuf) अणु
		event_callback = wlanevents[evt_code].event_callback;
		event_callback(padapter, (u8 *)peventbuf);
	पूर्ण

_पात_event_:
	वापस H2C_SUCCESS;
पूर्ण

u8 tx_beacon_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	अगर (send_beacon(padapter) == _FAIL) अणु
		DBG_88E("issue_beacon, fail!\n");
		वापस H2C_PARAMETERS_ERROR;
	पूर्ण
#अगर_घोषित CONFIG_88EU_AP_MODE
	अन्यथा अणु /* tx bc/mc frames after update TIM */
		काष्ठा sta_info *psta_bmc;
		काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
		काष्ठा xmit_frame *pxmitframe = शून्य;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		/* क्रम BC/MC Frames */
		psta_bmc = rtw_get_bcmc_stainfo(padapter);
		अगर (!psta_bmc)
			वापस H2C_SUCCESS;

		अगर ((pstapriv->tim_biपंचांगap & BIT(0)) && (psta_bmc->sleepq_len > 0)) अणु
			msleep(10);/*  10ms, ATIM(HIQ) Winकरोws */
			spin_lock_bh(&psta_bmc->sleep_q.lock);

			xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
			xmitframe_plist = xmitframe_phead->next;

			जबतक (xmitframe_phead != xmitframe_plist) अणु
				pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

				xmitframe_plist = xmitframe_plist->next;

				list_del_init(&pxmitframe->list);

				psta_bmc->sleepq_len--;
				अगर (psta_bmc->sleepq_len > 0)
					pxmitframe->attrib.mdata = 1;
				अन्यथा
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

				pxmitframe->attrib.qsel = 0x11;/* HIQ */

				spin_unlock_bh(&psta_bmc->sleep_q.lock);
				अगर (rtw_hal_xmit(padapter, pxmitframe))
					rtw_os_xmit_complete(padapter, pxmitframe);
				spin_lock_bh(&psta_bmc->sleep_q.lock);
			पूर्ण
			spin_unlock_bh(&psta_bmc->sleep_q.lock);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस H2C_SUCCESS;
पूर्ण

u8 set_ch_hdl(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा set_ch_parm *set_ch_parm;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	set_ch_parm = (काष्ठा set_ch_parm *)pbuf;

	DBG_88E(FUNC_NDEV_FMT" ch:%u, bw:%u, ch_offset:%u\n",
		FUNC_NDEV_ARG(padapter->pnetdev),
		set_ch_parm->ch, set_ch_parm->bw, set_ch_parm->ch_offset);

	pmlmeext->cur_channel = set_ch_parm->ch;
	pmlmeext->cur_ch_offset = set_ch_parm->ch_offset;
	pmlmeext->cur_bwmode = set_ch_parm->bw;

	set_channel_bwmode(padapter, set_ch_parm->ch, set_ch_parm->ch_offset, set_ch_parm->bw);

	वापस H2C_SUCCESS;
पूर्ण

u8 set_chplan_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा SetChannelPlan_param *setChannelPlan_param;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	setChannelPlan_param = (काष्ठा SetChannelPlan_param *)pbuf;

	pmlmeext->max_chan_nums = init_channel_set(padapter, setChannelPlan_param->channel_plan, pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);

	वापस H2C_SUCCESS;
पूर्ण
