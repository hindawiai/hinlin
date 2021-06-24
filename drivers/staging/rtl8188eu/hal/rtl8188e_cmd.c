<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188E_CMD_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <mlme_osdep.h>
#समावेश <rtw_ioctl_set.h>

#समावेश <rtl8188e_hal.h>

#घोषणा RTL88E_MAX_H2C_BOX_NUMS		4
#घोषणा RTL88E_MAX_CMD_LEN		7
#घोषणा RTL88E_MESSAGE_BOX_SIZE		4
#घोषणा RTL88E_EX_MESSAGE_BOX_SIZE	4

अटल u8 _is_fw_पढ़ो_cmd_करोwn(काष्ठा adapter *adapt, u8 msgbox_num)
अणु
	u8 पढ़ो_करोwn = false;
	पूर्णांक retry_cnts = 100;

	u8 valid;

	करो अणु
		valid = usb_पढ़ो8(adapt, REG_HMETFR) & BIT(msgbox_num);
		अगर (valid == 0)
			पढ़ो_करोwn = true;
	पूर्ण जबतक ((!पढ़ो_करोwn) && (retry_cnts--));

	वापस पढ़ो_करोwn;
पूर्ण

/*****************************************
* H2C Msg क्रमmat :
* 0x1DF - 0x1D0
*| 31 - 8	| 7-5	 4 - 0	|
*| h2c_msg	|Class_ID CMD_ID	|
*
* Extend 0x1FF - 0x1F0
*|31 - 0	  |
*|ext_msg|
******************************************/
अटल s32 FillH2CCmd_88E(काष्ठा adapter *adapt, u8 ElementID, u32 CmdLen, u8 *pCmdBuffer)
अणु
	u8 h2c_box_num;
	u32 msgbox_addr;
	u32 msgbox_ex_addr;
	u8 cmd_idx, ext_cmd_len;
	u32 h2c_cmd = 0;
	u32 h2c_cmd_ex = 0;
	s32 ret = _FAIL;

	अगर (!adapt->bFWReady) अणु
		DBG_88E("%s(): return H2C cmd because fw is not ready\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर (!pCmdBuffer)
		जाओ निकास;
	अगर (CmdLen > RTL88E_MAX_CMD_LEN)
		जाओ निकास;
	अगर (adapt->bSurpriseRemoved)
		जाओ निकास;

	/* pay attention to अगर  race condition happened in  H2C cmd setting. */
	h2c_box_num = adapt->HalData->LastHMEBoxNum;

	अगर (!_is_fw_पढ़ो_cmd_करोwn(adapt, h2c_box_num)) अणु
		DBG_88E(" fw read cmd failed...\n");
		जाओ निकास;
	पूर्ण

	*(u8 *)(&h2c_cmd) = ElementID;

	अगर (CmdLen <= 3) अणु
		स_नकल((u8 *)(&h2c_cmd) + 1, pCmdBuffer, CmdLen);
	पूर्ण अन्यथा अणु
		स_नकल((u8 *)(&h2c_cmd) + 1, pCmdBuffer, 3);
		ext_cmd_len = CmdLen - 3;
		स_नकल((u8 *)(&h2c_cmd_ex), pCmdBuffer + 3, ext_cmd_len);

		/* Write Ext command */
		msgbox_ex_addr = REG_HMEBOX_EXT_0 + (h2c_box_num * RTL88E_EX_MESSAGE_BOX_SIZE);
		क्रम (cmd_idx = 0; cmd_idx < ext_cmd_len; cmd_idx++)
			usb_ग_लिखो8(adapt, msgbox_ex_addr + cmd_idx, *((u8 *)(&h2c_cmd_ex) + cmd_idx));
	पूर्ण
	/*  Write command */
	msgbox_addr = REG_HMEBOX_0 + (h2c_box_num * RTL88E_MESSAGE_BOX_SIZE);
	क्रम (cmd_idx = 0; cmd_idx < RTL88E_MESSAGE_BOX_SIZE; cmd_idx++)
		usb_ग_लिखो8(adapt, msgbox_addr + cmd_idx, *((u8 *)(&h2c_cmd) + cmd_idx));

	adapt->HalData->LastHMEBoxNum =
		(h2c_box_num + 1) % RTL88E_MAX_H2C_BOX_NUMS;

	ret = _SUCCESS;

निकास:
	वापस ret;
पूर्ण

/* biपंचांगap[0:27] = tx_rate_biपंचांगap */
/* biपंचांगap[28:31]= Rate Adaptive id */
/* arg[0:4] = macid */
/* arg[5] = Short GI */
व्योम rtw_hal_add_ra_tid(काष्ठा adapter *pAdapter, u32 biपंचांगap, u8 arg, u8 rssi_level)
अणु
	काष्ठा odm_dm_काष्ठा *odmpriv = &pAdapter->HalData->odmpriv;
	u8 macid, init_rate, raid, लघुGIrate = false;

	macid = arg & 0x1f;

	raid = (biपंचांगap >> 28) & 0x0f;
	biपंचांगap &= 0x0fffffff;

	अगर (rssi_level != DM_RATR_STA_INIT)
		biपंचांगap = ODM_Get_Rate_Biपंचांगap(odmpriv, macid, biपंचांगap, rssi_level);

	biपंचांगap |= ((raid << 28) & 0xf0000000);

	init_rate = get_highest_rate_idx(biपंचांगap & 0x0fffffff) & 0x3f;

	लघुGIrate = (arg & BIT(5)) ? true : false;

	अगर (लघुGIrate)
		init_rate |= BIT(6);

	raid = (biपंचांगap >> 28) & 0x0f;

	biपंचांगap &= 0x0fffffff;

	DBG_88E("%s=> mac_id:%d, raid:%d, ra_bitmap=0x%x, shortGIrate=0x%02x\n",
		__func__, macid, raid, biपंचांगap, लघुGIrate);

	ODM_RA_UpdateRateInfo_8188E(odmpriv, macid, raid, biपंचांगap, लघुGIrate);
पूर्ण

व्योम rtl8188e_set_FwPwrMode_cmd(काष्ठा adapter *adapt, u8 Mode)
अणु
	काष्ठा setpwrmode_parm H2CSetPwrMode;
	काष्ठा pwrctrl_priv *pwrpriv = &adapt->pwrctrlpriv;
	u8 RLBM = 0; /*  0:Min, 1:Max, 2:User define */

	DBG_88E("%s: Mode=%d SmartPS=%d UAPSD=%d\n", __func__,
		Mode, pwrpriv->smart_ps, adapt->registrypriv.uapsd_enable);

	चयन (Mode) अणु
	हाल PS_MODE_ACTIVE:
		H2CSetPwrMode.Mode = 0;
		अवरोध;
	हाल PS_MODE_MIN:
		H2CSetPwrMode.Mode = 1;
		अवरोध;
	हाल PS_MODE_MAX:
		RLBM = 1;
		H2CSetPwrMode.Mode = 1;
		अवरोध;
	हाल PS_MODE_DTIM:
		RLBM = 2;
		H2CSetPwrMode.Mode = 1;
		अवरोध;
	हाल PS_MODE_UAPSD_WMM:
		H2CSetPwrMode.Mode = 2;
		अवरोध;
	शेष:
		H2CSetPwrMode.Mode = 0;
		अवरोध;
	पूर्ण

	H2CSetPwrMode.SmartPS_RLBM = (((pwrpriv->smart_ps << 4) & 0xf0) | (RLBM & 0x0f));

	H2CSetPwrMode.AwakeInterval = 1;

	H2CSetPwrMode.bAllQueueUAPSD = adapt->registrypriv.uapsd_enable;

	अगर (Mode > 0)
		H2CSetPwrMode.PwrState = 0x00;/*  AllON(0x0C), RFON(0x04), RFOFF(0x00) */
	अन्यथा
		H2CSetPwrMode.PwrState = 0x0C;/*  AllON(0x0C), RFON(0x04), RFOFF(0x00) */

	FillH2CCmd_88E(adapt, H2C_PS_PWR_MODE, माप(H2CSetPwrMode), (u8 *)&H2CSetPwrMode);
पूर्ण

व्योम rtl8188e_set_FwMediaStatus_cmd(काष्ठा adapter *adapt, __le16 mstatus_rpt)
अणु
	u8 opmode, macid;
	u16 mst_rpt = le16_to_cpu(mstatus_rpt);

	opmode = (u8)mst_rpt;
	macid = (u8)(mst_rpt >> 8);

	DBG_88E("### %s: MStatus=%x MACID=%d\n", __func__, opmode, macid);
	FillH2CCmd_88E(adapt, H2C_COM_MEDIA_STATUS_RPT, माप(mst_rpt), (u8 *)&mst_rpt);
पूर्ण

अटल व्योम Conकाष्ठाBeacon(काष्ठा adapter *adapt, u8 *pframe, u32 *pLength)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 rate_len, pktlen;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;

	ether_addr_copy(pwlanhdr->addr1, bc_addr);
	ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));
	ether_addr_copy(pwlanhdr->addr3, cur_network->MacAddress);

	SetSeqNum(pwlanhdr, 0/*pmlmeext->mgnt_seq*/);
	SetFrameSubType(pframe, WIFI_BEACON);

	pframe += माप(काष्ठा ieee80211_hdr_3addr);
	pktlen = माप(काष्ठा ieee80211_hdr_3addr);

	/* बारtamp will be inserted by hardware */
	pframe += 8;
	pktlen += 8;

	/*  beacon पूर्णांकerval: 2 bytes */
	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_beacon_पूर्णांकerval_from_ie(cur_network->ies)), 2);

	pframe += 2;
	pktlen += 2;

	/*  capability info: 2 bytes */
	स_नकल(pframe, (अचिन्हित अक्षर *)(rtw_get_capability_from_ie(cur_network->ies)), 2);

	pframe += 2;
	pktlen += 2;

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE) अणु
		pktlen += cur_network->ie_length - माप(काष्ठा ndis_802_11_fixed_ie);
		स_नकल(pframe, cur_network->ies + माप(काष्ठा ndis_802_11_fixed_ie), pktlen);

		जाओ _Conकाष्ठाBeacon;
	पूर्ण

	/* below क्रम ad-hoc mode */

	/*  SSID */
	pframe = rtw_set_ie(pframe, WLAN_EID_SSID, cur_network->ssid.ssid_length, cur_network->ssid.ssid, &pktlen);

	/*  supported rates... */
	rate_len = rtw_get_rateset_len(cur_network->SupportedRates);
	pframe = rtw_set_ie(pframe, WLAN_EID_SUPP_RATES, min_t(u32, rate_len, 8), cur_network->SupportedRates, &pktlen);

	/*  DS parameter set */
	pframe = rtw_set_ie(pframe, WLAN_EID_DS_PARAMS, 1, (अचिन्हित अक्षर *)&cur_network->Configuration.DSConfig, &pktlen);

	अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) अणु
		u32 ATIMWinकरोw;
		/*  IBSS Parameter Set... */
		ATIMWinकरोw = 0;
		pframe = rtw_set_ie(pframe, WLAN_EID_IBSS_PARAMS, 2, (अचिन्हित अक्षर *)(&ATIMWinकरोw), &pktlen);
	पूर्ण

	/* toकरो: ERP IE */

	/*  EXTERNDED SUPPORTED RATE */
	अगर (rate_len > 8)
		pframe = rtw_set_ie(pframe, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8), (cur_network->SupportedRates + 8), &pktlen);

	/* toकरो:HT क्रम adhoc */

_Conकाष्ठाBeacon:

	अगर ((pktlen + TXDESC_SIZE) > 512) अणु
		DBG_88E("beacon frame too large\n");
		वापस;
	पूर्ण

	*pLength = pktlen;
पूर्ण

अटल व्योम Conकाष्ठाPSPoll(काष्ठा adapter *adapt, u8 *pframe, u32 *pLength)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	__le16 *fctrl;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	/*  Frame control. */
	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	SetPwrMgt(fctrl);
	SetFrameSubType(pframe, WIFI_PSPOLL);

	/*  AID. */
	SetDuration(pframe, (pmlmeinfo->aid | 0xc000));

	/*  BSSID. */
	ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);

	/*  TA. */
	ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));

	*pLength = 16;
पूर्ण

अटल व्योम Conकाष्ठाNullFunctionData(काष्ठा adapter *adapt, u8 *pframe,
	u32 *pLength,
	u8 *StaAddr,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bForcePowerSave)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 pktlen;
	काष्ठा mlme_priv *pmlmepriv = &adapt->mlmepriv;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	अगर (bForcePowerSave)
		SetPwrMgt(fctrl);

	चयन (cur_network->network.Infraकाष्ठाureMode) अणु
	हाल Ndis802_11Infraकाष्ठाure:
		SetToDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);
		ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3, StaAddr);
		अवरोध;
	हाल Ndis802_11APMode:
		SetFrDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, StaAddr);
		ether_addr_copy(pwlanhdr->addr2, pnetwork->MacAddress);
		ether_addr_copy(pwlanhdr->addr3, myid(&adapt->eeprompriv));
		अवरोध;
	हाल Ndis802_11IBSS:
	शेष:
		ether_addr_copy(pwlanhdr->addr1, StaAddr);
		ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);
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

अटल व्योम Conकाष्ठाProbeRsp(काष्ठा adapter *adapt, u8 *pframe, u32 *pLength, u8 *StaAddr, bool bHideSSID)
अणु
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u8 *mac, *bssid;
	u32 pktlen;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *cur_network = &pmlmeinfo->network;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	mac = myid(&adapt->eeprompriv);
	bssid = cur_network->MacAddress;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	ether_addr_copy(pwlanhdr->addr1, StaAddr);
	ether_addr_copy(pwlanhdr->addr2, mac);
	ether_addr_copy(pwlanhdr->addr3, bssid);

	SetSeqNum(pwlanhdr, 0);
	SetFrameSubType(fctrl, WIFI_PROBERSP);

	pktlen = माप(काष्ठा ieee80211_hdr_3addr);
	pframe += pktlen;

	अगर (cur_network->ie_length > MAX_IE_SZ)
		वापस;

	स_नकल(pframe, cur_network->ies, cur_network->ie_length);
	pframe += cur_network->ie_length;
	pktlen += cur_network->ie_length;

	*pLength = pktlen;
पूर्ण

/*  */
/*  Description: Fill the reserved packets that FW will use to RSVD page. */
/*			Now we just send 4 types packet to rsvd page. */
/*			(1)Beacon, (2)Ps-poll, (3)Null data, (4)ProbeRsp. */
/*	Input: */
/*	    bDLFinished - false: At the first समय we will send all the packets as a large packet to Hw, */
/*						so we need to set the packet length to total length. */
/*			      true: At the second समय, we should send the first packet (शेष:beacon) */
/*						to Hw again and set the length in descriptor to the real beacon length. */
/*  2009.10.15 by tynli. */
अटल व्योम SetFwRsvdPagePkt(काष्ठा adapter *adapt, bool bDLFinished)
अणु
	काष्ठा xmit_frame *pmgntframe;
	काष्ठा pkt_attrib *pattrib;
	काष्ठा xmit_priv *pxmitpriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;
	u32 BeaconLength = 0, ProbeRspLength = 0, PSPollLength;
	u32 NullDataLength, QosNullLength;
	u8 *ReservedPagePacket;
	u8 PageNum, PageNeed, TxDescLen;
	u16 BufIndex;
	u32 TotalPacketLen;
	काष्ठा rsvdpage_loc RsvdPageLoc;
	काष्ठा wlan_bssid_ex *pnetwork;

	DBG_88E("%s\n", __func__);
	ReservedPagePacket = kzalloc(1000, GFP_KERNEL);
	अगर (!ReservedPagePacket) अणु
		DBG_88E("%s: alloc ReservedPagePacket fail!\n", __func__);
		वापस;
	पूर्ण

	pxmitpriv = &adapt->xmitpriv;
	pmlmeext = &adapt->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;
	pnetwork = &pmlmeinfo->network;

	TxDescLen = TXDESC_SIZE;
	PageNum = 0;

	/* 3 (1) beacon * 2 pages */
	BufIndex = TXDESC_OFFSET;
	Conकाष्ठाBeacon(adapt, &ReservedPagePacket[BufIndex], &BeaconLength);

	/*  When we count the first page size, we need to reserve description size क्रम the RSVD */
	/*  packet, it will be filled in front of the packet in TXPKTBUF. */
	PageNeed = (u8)PageNum_128(TxDescLen + BeaconLength);
	/*  To reserved 2 pages क्रम beacon buffer. 2010.06.24. */
	अगर (PageNeed == 1)
		PageNeed += 1;
	PageNum += PageNeed;
	adapt->HalData->FwRsvdPageStartOffset = PageNum;

	BufIndex += PageNeed * 128;

	/* 3 (2) ps-poll *1 page */
	RsvdPageLoc.LocPsPoll = PageNum;
	Conकाष्ठाPSPoll(adapt, &ReservedPagePacket[BufIndex], &PSPollLength);
	rtl8188e_fill_fake_txdesc(adapt, &ReservedPagePacket[BufIndex - TxDescLen], PSPollLength, true, false);

	PageNeed = (u8)PageNum_128(TxDescLen + PSPollLength);
	PageNum += PageNeed;

	BufIndex += PageNeed * 128;

	/* 3 (3) null data * 1 page */
	RsvdPageLoc.LocNullData = PageNum;
	Conकाष्ठाNullFunctionData(adapt, &ReservedPagePacket[BufIndex], &NullDataLength, pnetwork->MacAddress, false, 0, 0, false);
	rtl8188e_fill_fake_txdesc(adapt, &ReservedPagePacket[BufIndex - TxDescLen], NullDataLength, false, false);

	PageNeed = (u8)PageNum_128(TxDescLen + NullDataLength);
	PageNum += PageNeed;

	BufIndex += PageNeed * 128;

	/* 3 (4) probe response * 1page */
	RsvdPageLoc.LocProbeRsp = PageNum;
	Conकाष्ठाProbeRsp(adapt, &ReservedPagePacket[BufIndex], &ProbeRspLength, pnetwork->MacAddress, false);
	rtl8188e_fill_fake_txdesc(adapt, &ReservedPagePacket[BufIndex - TxDescLen], ProbeRspLength, false, false);

	PageNeed = (u8)PageNum_128(TxDescLen + ProbeRspLength);
	PageNum += PageNeed;

	BufIndex += PageNeed * 128;

	/* 3 (5) Qos null data */
	RsvdPageLoc.LocQosNull = PageNum;
	Conकाष्ठाNullFunctionData(adapt, &ReservedPagePacket[BufIndex],
				  &QosNullLength, pnetwork->MacAddress, true, 0, 0, false);
	rtl8188e_fill_fake_txdesc(adapt, &ReservedPagePacket[BufIndex - TxDescLen], QosNullLength, false, false);

	PageNeed = (u8)PageNum_128(TxDescLen + QosNullLength);
	PageNum += PageNeed;

	TotalPacketLen = BufIndex + QosNullLength;
	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe)
		जाओ निकास;

	/*  update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(adapt, pattrib);
	pattrib->qsel = 0x10;
	pattrib->last_txcmdsz = TotalPacketLen - TXDESC_OFFSET;
	pattrib->pktlen = pattrib->last_txcmdsz;
	स_नकल(pmgntframe->buf_addr, ReservedPagePacket, TotalPacketLen);

	rtw_hal_mgnt_xmit(adapt, pmgntframe);

	DBG_88E("%s: Set RSVD page location to Fw\n", __func__);
	FillH2CCmd_88E(adapt, H2C_COM_RSVD_PAGE, माप(RsvdPageLoc), (u8 *)&RsvdPageLoc);

निकास:
	kमुक्त(ReservedPagePacket);
पूर्ण

व्योम rtl8188e_set_FwJoinBssReport_cmd(काष्ठा adapter *adapt, u8 mstatus)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	bool bSendBeacon = false;
	bool bcn_valid = false;
	u8 DLBcnCount = 0;
	u32 poll = 0;

	DBG_88E("%s mstatus(%x)\n", __func__, mstatus);

	अगर (mstatus == 1) अणु
		/*  We should set AID, correct TSF, HW seq enable beक्रमe set JoinBssReport to Fw in 88/92C. */
		/*  Suggested by filen. Added by tynli. */
		usb_ग_लिखो16(adapt, REG_BCN_PSR_RPT, (0xC000 | pmlmeinfo->aid));
		/*  Do not set TSF again here or vWiFi beacon DMA INT will not work. */

		/* Set REG_CR bit 8. DMA beacon by SW. */
		haldata->RegCR_1 |= BIT(0);
		usb_ग_लिखो8(adapt,  REG_CR + 1, haldata->RegCR_1);

		/*  Disable Hw protection क्रम a समय which revserd क्रम Hw sending beacon. */
		/*  Fix करोwnload reserved page packet fail that access collision with the protection समय. */
		/*  2010.05.11. Added by tynli. */
		usb_ग_लिखो8(adapt, REG_BCN_CTRL, usb_पढ़ो8(adapt, REG_BCN_CTRL) & (~BIT(3)));
		usb_ग_लिखो8(adapt, REG_BCN_CTRL, usb_पढ़ो8(adapt, REG_BCN_CTRL) | BIT(4));

		अगर (haldata->RegFwHwTxQCtrl & BIT(6)) अणु
			DBG_88E("HalDownloadRSVDPage(): There is an Adapter is sending beacon.\n");
			bSendBeacon = true;
		पूर्ण

		/*  Set FWHW_TXQ_CTRL 0x422[6]=0 to tell Hw the packet is not a real beacon frame. */
		usb_ग_लिखो8(adapt, REG_FWHW_TXQ_CTRL + 2, (haldata->RegFwHwTxQCtrl & (~BIT(6))));
		haldata->RegFwHwTxQCtrl &= (~BIT(6));

		/*  Clear beacon valid check bit. */
		rtw_hal_set_hwreg(adapt, HW_VAR_BCN_VALID, शून्य);
		DLBcnCount = 0;
		poll = 0;
		करो अणु
			/*  करोwnload rsvd page. */
			SetFwRsvdPagePkt(adapt, false);
			DLBcnCount++;
			करो अणु
				yield();
				/* mdelay(10); */
				/*  check rsvd page करोwnload OK. */
				rtw_hal_get_hwreg(adapt, HW_VAR_BCN_VALID, (u8 *)(&bcn_valid));
				poll++;
			पूर्ण जबतक (!bcn_valid && (poll % 10) != 0 && !adapt->bSurpriseRemoved && !adapt->bDriverStopped);
		पूर्ण जबतक (!bcn_valid && DLBcnCount <= 100 && !adapt->bSurpriseRemoved && !adapt->bDriverStopped);

		अगर (adapt->bSurpriseRemoved || adapt->bDriverStopped)
			;
		अन्यथा अगर (!bcn_valid)
			DBG_88E("%s: 1 Download RSVD page failed! DLBcnCount:%u, poll:%u\n", __func__, DLBcnCount, poll);
		अन्यथा
			DBG_88E("%s: 1 Download RSVD success! DLBcnCount:%u, poll:%u\n", __func__, DLBcnCount, poll);
		/*  */
		/*  We just can send the reserved page twice during the समय that Tx thपढ़ो is stopped (e.g. pnpsetघातer) */
		/*  because we need to मुक्त the Tx BCN Desc which is used by the first reserved page packet. */
		/*  At run समय, we cannot get the Tx Desc until it is released in TxHandleInterrupt() so we will वापस */
		/*  the beacon TCB in the following code. 2011.11.23. by tynli. */
		/*  */

		/*  Enable Bcn */
		usb_ग_लिखो8(adapt, REG_BCN_CTRL, usb_पढ़ो8(adapt, REG_BCN_CTRL) | BIT(3));
		usb_ग_लिखो8(adapt, REG_BCN_CTRL, usb_पढ़ो8(adapt, REG_BCN_CTRL) & (~BIT(4)));

		/*  To make sure that अगर there exists an adapter which would like to send beacon. */
		/*  If exists, the origianl value of 0x422[6] will be 1, we should check this to */
		/*  prevent from setting 0x422[6] to 0 after करोwnload reserved page, or it will cause */
		/*  the beacon cannot be sent by HW. */
		/*  2010.06.23. Added by tynli. */
		अगर (bSendBeacon) अणु
			usb_ग_लिखो8(adapt, REG_FWHW_TXQ_CTRL + 2, (haldata->RegFwHwTxQCtrl | BIT(6)));
			haldata->RegFwHwTxQCtrl |= BIT(6);
		पूर्ण

		/*  Update RSVD page location H2C to Fw. */
		अगर (bcn_valid) अणु
			rtw_hal_set_hwreg(adapt, HW_VAR_BCN_VALID, शून्य);
			DBG_88E("Set RSVD page location to Fw.\n");
		पूर्ण

		/*  Do not enable HW DMA BCN or it will cause Pcie पूर्णांकerface hang by timing issue. 2011.11.24. by tynli. */
		/*  Clear CR[8] or beacon packet will not be send to TxBuf anymore. */
		haldata->RegCR_1 &= (~BIT(0));
		usb_ग_लिखो8(adapt,  REG_CR + 1, haldata->RegCR_1);
	पूर्ण
पूर्ण
