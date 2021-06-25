<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_mp_ioctl.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#समावेश <linux/rndis.h>
#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "mlme_osdep.h"
#समावेश "rtl871x_mp.h"
#समावेश "rtl871x_mp_ioctl.h"

uपूर्णांक oid_null_function(काष्ठा oid_par_priv *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_wireless_mode_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid == SET_OID) अणु
		अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u8))
			Adapter->registrypriv.wireless_mode =
					*(u8 *)poid_par_priv->inक्रमmation_buf;
		अन्यथा
			status = RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण अन्यथा अगर (poid_par_priv->type_of_oid == QUERY_OID) अणु
		अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u8)) अणु
			*(u8 *)poid_par_priv->inक्रमmation_buf =
					 Adapter->registrypriv.wireless_mode;
			*poid_par_priv->bytes_rw =
					poid_par_priv->inक्रमmation_buf_len;
		पूर्ण अन्यथा अणु
			status = RNDIS_STATUS_INVALID_LENGTH;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = RNDIS_STATUS_NOT_ACCEPTED;
	पूर्ण
	वापस status;
पूर्ण

uपूर्णांक oid_rt_pro_ग_लिखो_bb_reg_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	काष्ठा bb_reg_param *pbbreg;
	u16 offset;
	u32 value;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(काष्ठा bb_reg_param))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (काष्ठा bb_reg_param *)(poid_par_priv->inक्रमmation_buf);
	offset = (u16)(pbbreg->offset) & 0xFFF; /*0ffset :0x800~0xfff*/
	अगर (offset < BB_REG_BASE_ADDR)
		offset |= BB_REG_BASE_ADDR;
	value = pbbreg->value;
	r8712_bb_reg_ग_लिखो(Adapter, offset, value);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_पढ़ो_bb_reg_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	काष्ठा bb_reg_param *pbbreg;
	u16 offset;
	u32 value;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(काष्ठा bb_reg_param))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (काष्ठा bb_reg_param *)(poid_par_priv->inक्रमmation_buf);
	offset = (u16)(pbbreg->offset) & 0xFFF; /*0ffset :0x800~0xfff*/
	अगर (offset < BB_REG_BASE_ADDR)
		offset |= BB_REG_BASE_ADDR;
	value = r8712_bb_reg_पढ़ो(Adapter, offset);
	pbbreg->value = value;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_ग_लिखो_rf_reg_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	काष्ठा rf_reg_param *pbbreg;
	u8 path;
	u8 offset;
	u32 value;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(काष्ठा rf_reg_param))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (काष्ठा rf_reg_param *)(poid_par_priv->inक्रमmation_buf);
	path = (u8)pbbreg->path;
	अगर (path > RF_PATH_B)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	offset = (u8)pbbreg->offset;
	value = pbbreg->value;
	r8712_rf_reg_ग_लिखो(Adapter, path, offset, value);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_पढ़ो_rf_reg_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	काष्ठा rf_reg_param *pbbreg;
	u8 path;
	u8 offset;
	u32 value;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(काष्ठा rf_reg_param))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	pbbreg = (काष्ठा rf_reg_param *)(poid_par_priv->inक्रमmation_buf);
	path = (u8)pbbreg->path;
	अगर (path > RF_PATH_B) /* 1T2R  path_a /path_b */
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	offset = (u8)pbbreg->offset;
	value = r8712_rf_reg_पढ़ो(Adapter, path, offset);
	pbbreg->value = value;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

/*This function initializes the DUT to the MP test mode*/
अटल पूर्णांक mp_start_test(काष्ठा _adapter *padapter)
अणु
	काष्ठा mp_priv *pmppriv = &padapter->mppriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;
	काष्ठा wlan_bssid_ex bssid;
	काष्ठा sta_info *psta;
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ irqL;
	पूर्णांक res = 0;

	/* 3 1. initialize a new काष्ठा wlan_bssid_ex */
	स_नकल(bssid.MacAddress, pmppriv->network_macaddr, ETH_ALEN);
	bssid.Ssid.SsidLength = 16;
	स_नकल(bssid.Ssid.Ssid, (अचिन्हित अक्षर *)"mp_pseudo_adhoc",
		bssid.Ssid.SsidLength);
	bssid.Infraकाष्ठाureMode = Ndis802_11IBSS;
	bssid.NetworkTypeInUse = Ndis802_11DS;
	bssid.IELength = 0;
	length = r8712_get_wlan_bssid_ex_sz(&bssid);
	अगर (length % 4) अणु
		/*round up to multiple of 4 bytes.*/
		bssid.Length = ((length >> 2) + 1) << 2;
	पूर्ण अन्यथा अणु
		bssid.Length = length;
	पूर्ण
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE))
		जाओ end_of_mp_start_test;
	/*init mp_start_test status*/
	pmppriv->prev_fw_state = get_fwstate(pmlmepriv);
	pmlmepriv->fw_state = WIFI_MP_STATE;
	अगर (pmppriv->mode == _LOOPBOOK_MODE_)
		set_fwstate(pmlmepriv, WIFI_MP_LPBK_STATE); /*append txdesc*/
	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
	/* 3 2. create a new psta क्रम mp driver */
	/* clear psta in the cur_network, अगर any */
	psta = r8712_get_stainfo(&padapter->stapriv,
				 tgt_network->network.MacAddress);
	अगर (psta)
		r8712_मुक्त_stainfo(padapter, psta);
	psta = r8712_alloc_stainfo(&padapter->stapriv, bssid.MacAddress);
	अगर (!psta) अणु
		res = -ENOMEM;
		जाओ end_of_mp_start_test;
	पूर्ण
	/* 3 3. join pseuकरो AdHoc */
	tgt_network->join_res = 1;
	tgt_network->aid = psta->aid = 1;
	स_नकल(&tgt_network->network, &bssid, length);
	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
	r8712_os_indicate_connect(padapter);
	/* Set to LINKED STATE क्रम MP TRX Testing */
	set_fwstate(pmlmepriv, _FW_LINKED);
end_of_mp_start_test:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	वापस res;
पूर्ण

/*This function change the DUT from the MP test mode पूर्णांकo normal mode */
अटल पूर्णांक mp_stop_test(काष्ठा _adapter *padapter)
अणु
	काष्ठा mp_priv *pmppriv = &padapter->mppriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;
	काष्ठा sta_info *psta;
	अचिन्हित दीर्घ irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (!check_fwstate(pmlmepriv, WIFI_MP_STATE))
		जाओ end_of_mp_stop_test;
	/* 3 1. disconnect pseuकरो AdHoc */
	r8712_os_indicate_disconnect(padapter);
	/* 3 2. clear psta used in mp test mode. */
	psta = r8712_get_stainfo(&padapter->stapriv,
				 tgt_network->network.MacAddress);
	अगर (psta)
		r8712_मुक्त_stainfo(padapter, psta);
	/* 3 3. वापस to normal state (शेष:station mode) */
	pmlmepriv->fw_state = pmppriv->prev_fw_state; /* WIFI_STATION_STATE;*/
	/*flush the cur_network*/
	स_रखो(tgt_network, 0, माप(काष्ठा wlan_network));
end_of_mp_stop_test:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	वापस _SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_data_rate_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32 ratevalue;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	ratevalue = *((u32 *)poid_par_priv->inक्रमmation_buf);
	अगर (ratevalue >= MPT_RATE_LAST)
		वापस RNDIS_STATUS_INVALID_DATA;
	Adapter->mppriv.curr_rateidx = ratevalue;
	r8712_SetDataRate(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_start_test_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	u32 mode;
	u8 val8;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस  RNDIS_STATUS_NOT_ACCEPTED;
	mode = *((u32 *)poid_par_priv->inक्रमmation_buf);
	Adapter->mppriv.mode = mode;/* 1 क्रम loopback*/
	अगर (mp_start_test(Adapter))
		status = RNDIS_STATUS_NOT_ACCEPTED;
	r8712_ग_लिखो8(Adapter, MSR, 1); /* Link in ad hoc network, 0x1025004C */
	r8712_ग_लिखो8(Adapter, RCR, 0); /* RCR : disable all pkt, 0x10250048 */
	/* RCR disable Check BSSID, 0x1025004a */
	r8712_ग_लिखो8(Adapter, RCR + 2, 0x57);
	/* disable RX filter map , mgt frames will put in RX FIFO 0 */
	r8712_ग_लिखो16(Adapter, RXFLTMAP0, 0x0);
	val8 = r8712_पढ़ो8(Adapter, EE_9346CR);
	अगर (!(val8 & _9356SEL)) अणु /*boot from EFUSE*/
		r8712_efuse_reg_init(Adapter);
		r8712_efuse_change_max_size(Adapter);
		r8712_efuse_reg_uninit(Adapter);
	पूर्ण
	वापस status;
पूर्ण

uपूर्णांक oid_rt_pro_stop_test_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (mp_stop_test(Adapter) == _FAIL)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_channel_direct_call_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		Channel;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	Channel = *((u32 *)poid_par_priv->inक्रमmation_buf);
	अगर (Channel > 14)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	Adapter->mppriv.curr_ch = Channel;
	r8712_SetChannel(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_antenna_bb_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32 antenna;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	antenna = *((u32 *)poid_par_priv->inक्रमmation_buf);
	Adapter->mppriv.antenna_tx = (u16)((antenna & 0xFFFF0000) >> 16);
	Adapter->mppriv.antenna_rx = (u16)(antenna & 0x0000FFFF);
	r8712_SwitchAntenna(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_tx_घातer_control_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32 tx_pwr_idx;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	tx_pwr_idx = *((u32 *)poid_par_priv->inक्रमmation_buf);
	अगर (tx_pwr_idx > MAX_TX_PWR_INDEX_N_MODE)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	Adapter->mppriv.curr_txघातeridx = (u8)tx_pwr_idx;
	r8712_SetTxPower(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_query_tx_packet_sent_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	अगर (poid_par_priv->inक्रमmation_buf_len == माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
					Adapter->mppriv.tx_pktcount;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_query_rx_packet_received_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	अगर (poid_par_priv->inक्रमmation_buf_len == माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
					Adapter->mppriv.rx_pktcount;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_query_rx_packet_crc32_error_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	अगर (poid_par_priv->inक्रमmation_buf_len == माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
					Adapter->mppriv.rx_crcerrpktcount;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_reset_tx_packet_sent_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	Adapter->mppriv.tx_pktcount = 0;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_reset_rx_packet_received_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len == माप(u32)) अणु
		Adapter->mppriv.rx_pktcount = 0;
		Adapter->mppriv.rx_crcerrpktcount = 0;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_reset_phy_rx_packet_count_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	r8712_ResetPhyRxPktCount(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_phy_rx_packet_received_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	*(u32 *)poid_par_priv->inक्रमmation_buf =
					 r8712_GetPhyRxPktReceived(Adapter);
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_phy_rx_packet_crc32_error_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len != माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	*(u32 *)poid_par_priv->inक्रमmation_buf =
					 r8712_GetPhyRxPktCRC32Error(Adapter);
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_modulation_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	Adapter->mppriv.curr_modem = *((u8 *)poid_par_priv->inक्रमmation_buf);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_continuous_tx_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bStartTest;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	bStartTest = *((u32 *)poid_par_priv->inक्रमmation_buf);
	r8712_SetContinuousTx(Adapter, (u8)bStartTest);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_single_carrier_tx_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bStartTest;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	bStartTest = *((u32 *)poid_par_priv->inक्रमmation_buf);
	r8712_SetSingleCarrierTx(Adapter, (u8)bStartTest);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_carrier_suppression_tx_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bStartTest;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	bStartTest = *((u32 *)poid_par_priv->inक्रमmation_buf);
	r8712_SetCarrierSuppressionTx(Adapter, (u8)bStartTest);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_set_single_tone_tx_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bStartTest;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	bStartTest = *((u32 *)poid_par_priv->inक्रमmation_buf);
	r8712_SetSingleToneTx(Adapter, (u8)bStartTest);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_पढ़ो_रेजिस्टर_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	काष्ठा mp_rw_reg *RegRWStruct;
	u16		offset;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	RegRWStruct = (काष्ठा mp_rw_reg *)poid_par_priv->inक्रमmation_buf;
	अगर ((RegRWStruct->offset >= 0x10250800) &&
	    (RegRWStruct->offset <= 0x10250FFF)) अणु
		/*baseband रेजिस्टर*/
		/*0ffset :0x800~0xfff*/
		offset = (u16)(RegRWStruct->offset) & 0xFFF;
		RegRWStruct->value = r8712_bb_reg_पढ़ो(Adapter, offset);
	पूर्ण अन्यथा अणु
		चयन (RegRWStruct->width) अणु
		हाल 1:
			RegRWStruct->value = r8712_पढ़ो8(Adapter,
						   RegRWStruct->offset);
			अवरोध;
		हाल 2:
			RegRWStruct->value = r8712_पढ़ो16(Adapter,
						    RegRWStruct->offset);
			अवरोध;
		हाल 4:
			RegRWStruct->value = r8712_पढ़ो32(Adapter,
						    RegRWStruct->offset);
			अवरोध;
		शेष:
			status = RNDIS_STATUS_NOT_ACCEPTED;
			अवरोध;
		पूर्ण
	पूर्ण
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस status;
पूर्ण

uपूर्णांक oid_rt_pro_ग_लिखो_रेजिस्टर_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	काष्ठा mp_rw_reg *RegRWStruct;
	u16		offset;
	u32		value;
	u32 oldValue = 0;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	RegRWStruct = (काष्ठा mp_rw_reg *)poid_par_priv->inक्रमmation_buf;
	अगर ((RegRWStruct->offset >= 0x10250800) &&
	    (RegRWStruct->offset <= 0x10250FFF)) अणु
		/*baseband रेजिस्टर*/
		offset = (u16)(RegRWStruct->offset) & 0xFFF;
		value = RegRWStruct->value;
		चयन (RegRWStruct->width) अणु
		हाल 1:
			oldValue = r8712_bb_reg_पढ़ो(Adapter, offset);
			oldValue &= 0xFFFFFF00;
			value &= 0x000000FF;
			value |= oldValue;
			अवरोध;
		हाल 2:
			oldValue = r8712_bb_reg_पढ़ो(Adapter, offset);
			oldValue &= 0xFFFF0000;
			value &= 0x0000FFFF;
			value |= oldValue;
			अवरोध;
		पूर्ण
		r8712_bb_reg_ग_लिखो(Adapter, offset, value);
	पूर्ण अन्यथा अणु
		चयन (RegRWStruct->width) अणु
		हाल 1:
			r8712_ग_लिखो8(Adapter, RegRWStruct->offset,
			       (अचिन्हित अक्षर)RegRWStruct->value);
			अवरोध;
		हाल 2:
			r8712_ग_लिखो16(Adapter, RegRWStruct->offset,
				(अचिन्हित लघु)RegRWStruct->value);
			अवरोध;
		हाल 4:
			r8712_ग_लिखो32(Adapter, RegRWStruct->offset,
				(अचिन्हित पूर्णांक)RegRWStruct->value);
			अवरोध;
		शेष:
			status = RNDIS_STATUS_NOT_ACCEPTED;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

uपूर्णांक oid_rt_get_thermal_meter_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	अगर (Adapter->mppriv.act_in_progress)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	अगर (poid_par_priv->inक्रमmation_buf_len < माप(u8))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	/*init workparam*/
	Adapter->mppriv.act_in_progress = true;
	Adapter->mppriv.workparam.bcompleted = false;
	Adapter->mppriv.workparam.act_type = MPT_GET_THERMAL_METER;
	Adapter->mppriv.workparam.io_offset = 0;
	Adapter->mppriv.workparam.io_value = 0xFFFFFFFF;
	r8712_GetThermalMeter(Adapter, &Adapter->mppriv.workparam.io_value);
	Adapter->mppriv.workparam.bcompleted = true;
	Adapter->mppriv.act_in_progress = false;
	*(u32 *)poid_par_priv->inक्रमmation_buf =
				 Adapter->mppriv.workparam.io_value;
	*poid_par_priv->bytes_rw = माप(u32);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_पढ़ो_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	uपूर्णांक status = RNDIS_STATUS_SUCCESS;

	काष्ठा EFUSE_ACCESS_STRUCT *pefuse;
	u8 *data;
	u16 addr = 0, cnts = 0;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len <
	    माप(काष्ठा EFUSE_ACCESS_STRUCT))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	pefuse = (काष्ठा EFUSE_ACCESS_STRUCT *)poid_par_priv->inक्रमmation_buf;
	addr = pefuse->start_addr;
	cnts = pefuse->cnts;
	data = pefuse->data;
	स_रखो(data, 0xFF, cnts);
	अगर ((addr > 511) || (cnts < 1) || (cnts > 512) || (addr + cnts) >
	     EFUSE_MAX_SIZE)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (!r8712_efuse_access(Adapter, true, addr, cnts, data))
		status = RNDIS_STATUS_FAILURE;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस status;
पूर्ण

/*------------------------------------------------------------------------*/
uपूर्णांक oid_rt_pro_ग_लिखो_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	uपूर्णांक status = RNDIS_STATUS_SUCCESS;

	काष्ठा EFUSE_ACCESS_STRUCT *pefuse;
	u8 *data;
	u16 addr = 0, cnts = 0;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;

	pefuse = (काष्ठा EFUSE_ACCESS_STRUCT *)poid_par_priv->inक्रमmation_buf;
	addr = pefuse->start_addr;
	cnts = pefuse->cnts;
	data = pefuse->data;

	अगर ((addr > 511) || (cnts < 1) || (cnts > 512) ||
	    (addr + cnts) > r8712_efuse_get_max_size(Adapter))
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (!r8712_efuse_access(Adapter, false, addr, cnts, data))
		status = RNDIS_STATUS_FAILURE;
	वापस status;
पूर्ण

/*----------------------------------------------------------------------*/

uपूर्णांक oid_rt_get_efuse_current_size_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(पूर्णांक))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	r8712_efuse_reg_init(Adapter);
	*(पूर्णांक *)poid_par_priv->inक्रमmation_buf =
				 r8712_efuse_get_current_size(Adapter);
	r8712_efuse_reg_uninit(Adapter);
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_efuse_max_size_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	*(पूर्णांक *)poid_par_priv->inक्रमmation_buf =
					 r8712_efuse_get_max_size(Adapter);
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_efuse_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;

	अगर (poid_par_priv->type_of_oid == QUERY_OID)
		status = oid_rt_pro_पढ़ो_efuse_hdl(poid_par_priv);
	अन्यथा
		status = oid_rt_pro_ग_लिखो_efuse_hdl(poid_par_priv);
	वापस status;
पूर्ण

uपूर्णांक oid_rt_pro_efuse_map_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	u8		*data;

	*poid_par_priv->bytes_rw = 0;
	अगर (poid_par_priv->inक्रमmation_buf_len < EFUSE_MAP_MAX_SIZE)
		वापस RNDIS_STATUS_INVALID_LENGTH;
	data = (u8 *)poid_par_priv->inक्रमmation_buf;
	अगर (poid_par_priv->type_of_oid == QUERY_OID) अणु
		अगर (r8712_efuse_map_पढ़ो(Adapter, 0, EFUSE_MAP_MAX_SIZE, data))
			*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
		अन्यथा
			status = RNDIS_STATUS_FAILURE;
	पूर्ण अन्यथा अणु
		/* SET_OID */
		अगर (r8712_efuse_reg_init(Adapter)) अणु
			अगर (r8712_efuse_map_ग_लिखो(Adapter, 0,
			    EFUSE_MAP_MAX_SIZE, data))
				*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
			अन्यथा
				status = RNDIS_STATUS_FAILURE;
			r8712_efuse_reg_uninit(Adapter);
		पूर्ण अन्यथा अणु
			status = RNDIS_STATUS_FAILURE;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

uपूर्णांक oid_rt_set_bandwidth_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u32		bandwidth;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	bandwidth = *((u32 *)poid_par_priv->inक्रमmation_buf);/*4*/
	अगर (bandwidth != HT_CHANNEL_WIDTH_20)
		bandwidth = HT_CHANNEL_WIDTH_40;
	Adapter->mppriv.curr_bandwidth = (u8)bandwidth;
	r8712_SwitchBandwidth(Adapter);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_rx_packet_type_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);
	u8		rx_pkt_type;
	u32		rcr_val32;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(u8))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	rx_pkt_type = *((u8 *)poid_par_priv->inक्रमmation_buf);/*4*/
	rcr_val32 = r8712_पढ़ो32(Adapter, RCR);/*RCR = 0x10250048*/
	rcr_val32 &= ~(RCR_CBSSID | RCR_AB | RCR_AM | RCR_APM | RCR_AAP);
	चयन (rx_pkt_type) अणु
	हाल RX_PKT_BROADCAST:
		rcr_val32 |= (RCR_AB | RCR_AM | RCR_APM | RCR_AAP | RCR_ACRC32);
		अवरोध;
	हाल RX_PKT_DEST_ADDR:
		rcr_val32 |= (RCR_AB | RCR_AM | RCR_APM | RCR_AAP | RCR_ACRC32);
		अवरोध;
	हाल RX_PKT_PHY_MATCH:
		rcr_val32 |= (RCR_APM | RCR_ACRC32);
		अवरोध;
	शेष:
		rcr_val32 &= ~(RCR_AAP |
			       RCR_APM |
			       RCR_AM |
			       RCR_AB |
			       RCR_ACRC32);
		अवरोध;
	पूर्ण
	अगर (rx_pkt_type == RX_PKT_DEST_ADDR)
		Adapter->mppriv.check_mp_pkt = 1;
	अन्यथा
		Adapter->mppriv.check_mp_pkt = 0;
	r8712_ग_लिखो32(Adapter, RCR, rcr_val32);
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

/*--------------------------------------------------------------------------*/
/*Linux*/
अचिन्हित पूर्णांक mp_ioctl_xmit_packet_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	वापस _SUCCESS;
पूर्ण

/*-------------------------------------------------------------------------*/
uपूर्णांक oid_rt_set_घातer_करोwn_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	/*CALL  the घातer_करोwn function*/
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

/*-------------------------------------------------------------------------- */
uपूर्णांक oid_rt_get_घातer_mode_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *Adapter = (काष्ठा _adapter *)
				   (poid_par_priv->adapter_context);

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len < माप(u32))
		वापस RNDIS_STATUS_INVALID_LENGTH;
	*(पूर्णांक *)poid_par_priv->inक्रमmation_buf =
		 Adapter->registrypriv.low_घातer ? POWER_LOW : POWER_NORMAL;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण
