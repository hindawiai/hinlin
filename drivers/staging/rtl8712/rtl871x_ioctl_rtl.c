<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_ioctl_rtl.c
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

#घोषणा  _RTL871X_IOCTL_RTL_C_

#समावेश <linux/rndis.h>
#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wlan_bssdef.h"
#समावेश "wifi.h"
#समावेश "rtl871x_ioctl.h"
#समावेश "rtl871x_ioctl_set.h"
#समावेश "rtl871x_ioctl_rtl.h"
#समावेश "mp_custom_oid.h"
#समावेश "rtl871x_mp.h"
#समावेश "rtl871x_mp_ioctl.h"

uपूर्णांक oid_rt_get_संकेत_quality_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_small_packet_crc_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >=  माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
				padapter->recvpriv.rx_smallpacket_crcerr;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_middle_packet_crc_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >=  माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
				padapter->recvpriv.rx_middlepacket_crcerr;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_large_packet_crc_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >=  माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
				 padapter->recvpriv.rx_largepacket_crcerr;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_tx_retry_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_rx_retry_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_rx_total_packet_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >=  माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
					 padapter->recvpriv.rx_pkts +
					 padapter->recvpriv.rx_drop;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_tx_beacon_ok_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_tx_beacon_err_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_rx_icv_err_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		*(uपूर्णांक *)poid_par_priv->inक्रमmation_buf =
					 padapter->recvpriv.rx_icv_err;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_encryption_algorithm_hdl(काष्ठा oid_par_priv
						*poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_preamble_mode_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	u32 preamblemode = 0;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		अगर (padapter->registrypriv.preamble == PREAMBLE_LONG)
			preamblemode = 0;
		अन्यथा अगर (padapter->registrypriv.preamble == PREAMBLE_AUTO)
			preamblemode = 1;
		अन्यथा अगर (padapter->registrypriv.preamble == PREAMBLE_SHORT)
			preamblemode = 2;
		*(u32 *)poid_par_priv->inक्रमmation_buf = preamblemode;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_ap_ip_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_channelplan_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	काष्ठा eeprom_priv *peeprompriv = &padapter->eeprompriv;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	*(u16 *)poid_par_priv->inक्रमmation_buf = peeprompriv->channel_plan;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_channelplan_hdl(काष्ठा oid_par_priv
				       *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	काष्ठा eeprom_priv *peeprompriv = &padapter->eeprompriv;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	peeprompriv->channel_plan = *(u16 *)poid_par_priv->inक्रमmation_buf;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_preamble_mode_hdl(काष्ठा oid_par_priv
					 *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	u32 preamblemode = 0;

	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		preamblemode = *(u32 *)poid_par_priv->inक्रमmation_buf;
		अगर (preamblemode == 0)
			padapter->registrypriv.preamble = PREAMBLE_LONG;
		अन्यथा अगर (preamblemode == 1)
			padapter->registrypriv.preamble = PREAMBLE_AUTO;
		अन्यथा अगर (preamblemode == 2)
			padapter->registrypriv.preamble = PREAMBLE_SHORT;
		*(u32 *)poid_par_priv->inक्रमmation_buf = preamblemode;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_bcn_पूर्णांकvl_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_dedicate_probe_hdl(काष्ठा oid_par_priv
				      *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_total_tx_bytes_hdl(काष्ठा oid_par_priv
					  *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
						 padapter->xmitpriv.tx_bytes;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_total_rx_bytes_hdl(काष्ठा oid_par_priv
					  *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		*(u32 *)poid_par_priv->inक्रमmation_buf =
					   padapter->recvpriv.rx_bytes;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_current_tx_घातer_level_hdl(काष्ठा oid_par_priv
					      *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_enc_key_mismatch_count_hdl(काष्ठा oid_par_priv
						  *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_enc_key_match_count_hdl(काष्ठा oid_par_priv
					       *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_channel_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा NDIS_802_11_CONFIGURATION *pnic_Config;
	u32   channelnum;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
		pnic_Config = &pmlmepriv->cur_network.network.Configuration;
	अन्यथा
		pnic_Config = &padapter->registrypriv.dev_network.Configuration;
	channelnum = pnic_Config->DSConfig;
	*(u32 *)poid_par_priv->inक्रमmation_buf = channelnum;
	*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_hardware_radio_off_hdl(काष्ठा oid_par_priv
			 *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_key_mismatch_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_supported_wireless_mode_hdl(काष्ठा oid_par_priv
					       *poid_par_priv)
अणु
	u32 ulInfo = 0;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len >= माप(u32)) अणु
		ulInfo |= 0x0100; /* WIRELESS_MODE_B */
		ulInfo |= 0x0200; /* WIRELESS_MODE_G */
		ulInfo |= 0x0400; /* WIRELESS_MODE_A */
		*(u32 *) poid_par_priv->inक्रमmation_buf = ulInfo;
		*poid_par_priv->bytes_rw = poid_par_priv->inक्रमmation_buf_len;
	पूर्ण अन्यथा अणु
		वापस RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_channel_list_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_scan_in_progress_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण


uपूर्णांक oid_rt_क्रमced_data_rate_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_wireless_mode_क्रम_scan_list_hdl(काष्ठा oid_par_priv
						   *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_get_bss_wireless_mode_hdl(काष्ठा oid_par_priv
					     *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_scan_with_magic_packet_hdl(काष्ठा oid_par_priv
					      *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_ap_get_associated_station_list_hdl(काष्ठा oid_par_priv
						      *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_ap_चयन_पूर्णांकo_ap_mode_hdl(काष्ठा oid_par_priv*
					      poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_ap_supported_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_ap_set_passphrase_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_pro_rf_ग_लिखो_registry_hdl(काष्ठा oid_par_priv*
					     poid_par_priv)
अणु
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	काष्ठा _adapter *Adapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != SET_OID) /* QUERY_OID */
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len ==
	   (माप(अचिन्हित दीर्घ) * 3)) अणु
		अगर (r8712_setrfreg_cmd(Adapter,
			*(अचिन्हित अक्षर *)poid_par_priv->inक्रमmation_buf,
			(अचिन्हित दीर्घ)(*((अचिन्हित दीर्घ *)
					poid_par_priv->inक्रमmation_buf + 2))))
			status = RNDIS_STATUS_NOT_ACCEPTED;
	पूर्ण अन्यथा अणु
		status = RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस status;
पूर्ण

uपूर्णांक oid_rt_pro_rf_पढ़ो_registry_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	uपूर्णांक status = RNDIS_STATUS_SUCCESS;
	काष्ठा _adapter *Adapter = poid_par_priv->adapter_context;

	अगर (poid_par_priv->type_of_oid != SET_OID) /* QUERY_OID */
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	अगर (poid_par_priv->inक्रमmation_buf_len == (माप(अचिन्हित दीर्घ) *
						   3)) अणु
		अगर (Adapter->mppriv.act_in_progress) अणु
			status = RNDIS_STATUS_NOT_ACCEPTED;
		पूर्ण अन्यथा अणु
			/* init workparam */
			Adapter->mppriv.act_in_progress = true;
			Adapter->mppriv.workparam.bcompleted = false;
			Adapter->mppriv.workparam.act_type = MPT_READ_RF;
			Adapter->mppriv.workparam.io_offset = *(अचिन्हित दीर्घ *)
						poid_par_priv->inक्रमmation_buf;
			Adapter->mppriv.workparam.io_value = 0xcccccccc;

		/* RegOffsetValue	- The offset of RF रेजिस्टर to पढ़ो.
		 * RegDataWidth	- The data width of RF रेजिस्टर to पढ़ो.
		 * RegDataValue	- The value to पढ़ो.
		 * RegOffsetValue = *((अचिन्हित दीर्घ *)Inक्रमmationBuffer);
		 * RegDataWidth = *((अचिन्हित दीर्घ *)Inक्रमmationBuffer+1);
		 * RegDataValue =  *((अचिन्हित दीर्घ *)Inक्रमmationBuffer+2);
		 */
			अगर (r8712_getrfreg_cmd(Adapter,
			    *(अचिन्हित अक्षर *)poid_par_priv->inक्रमmation_buf,
			    (अचिन्हित अक्षर *)&Adapter->mppriv.workparam.io_value
			    ))
				status = RNDIS_STATUS_NOT_ACCEPTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = RNDIS_STATUS_INVALID_LENGTH;
	पूर्ण
	वापस status;
पूर्ण

क्रमागत _CONNECT_STATE_ अणु
	CHECKINGSTATUS,
	ASSOCIATED,
	ADHOCMODE,
	NOTASSOCIATED
पूर्ण;

uपूर्णांक oid_rt_get_connect_state_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	काष्ठा _adapter *padapter = poid_par_priv->adapter_context;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	u32 ulInfo;

	अगर (poid_par_priv->type_of_oid != QUERY_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	/* nStatus==0	CheckingStatus
	 * nStatus==1	Associated
	 * nStatus==2	AdHocMode
	 * nStatus==3	NotAssociated
	 */
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		ulInfo = CHECKINGSTATUS;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		ulInfo = ASSOCIATED;
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE))
		ulInfo = ADHOCMODE;
	अन्यथा
		ulInfo = NOTASSOCIATED;
	*(u32 *)poid_par_priv->inक्रमmation_buf = ulInfo;
	*poid_par_priv->bytes_rw =  poid_par_priv->inक्रमmation_buf_len;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण

uपूर्णांक oid_rt_set_शेष_key_id_hdl(काष्ठा oid_par_priv *poid_par_priv)
अणु
	अगर (poid_par_priv->type_of_oid != SET_OID)
		वापस RNDIS_STATUS_NOT_ACCEPTED;
	वापस RNDIS_STATUS_SUCCESS;
पूर्ण
