<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL871X_IOCTL_RTL_H
#घोषणा _RTL871X_IOCTL_RTL_H

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

/*************** oid_rtl_seg_01_01 **************/
uपूर्णांक oid_rt_get_संकेत_quality_hdl(
			काष्ठा oid_par_priv *poid_par_priv);/*84*/
uपूर्णांक oid_rt_get_small_packet_crc_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_middle_packet_crc_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_large_packet_crc_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_tx_retry_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_rx_retry_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_rx_total_packet_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_tx_beacon_ok_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_tx_beacon_err_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_rx_icv_err_hdl(
			काष्ठा oid_par_priv *poid_par_priv);/*93*/
uपूर्णांक oid_rt_set_encryption_algorithm_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_preamble_mode_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_ap_ip_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_channelplan_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_channelplan_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_preamble_mode_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_bcn_पूर्णांकvl_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_dedicate_probe_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_total_tx_bytes_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_total_rx_bytes_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_current_tx_घातer_level_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_enc_key_mismatch_count_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_enc_key_match_count_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_channel_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_hardware_radio_off_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_key_mismatch_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_supported_wireless_mode_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_channel_list_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_scan_in_progress_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_क्रमced_data_rate_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_wireless_mode_क्रम_scan_list_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_get_bss_wireless_mode_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_scan_with_magic_packet_hdl(
			काष्ठा oid_par_priv *poid_par_priv);

/**************  oid_rtl_seg_01_03 section start **************/
uपूर्णांक oid_rt_ap_get_associated_station_list_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_ap_चयन_पूर्णांकo_ap_mode_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_ap_supported_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_ap_set_passphrase_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
/* oid_rtl_seg_01_11 */
uपूर्णांक oid_rt_pro_rf_ग_लिखो_registry_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_pro_rf_पढ़ो_registry_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
/***************  oid_rtl_seg_03_00 section start **************/
uपूर्णांक oid_rt_get_connect_state_hdl(
			काष्ठा oid_par_priv *poid_par_priv);
uपूर्णांक oid_rt_set_शेष_key_id_hdl(
			काष्ठा oid_par_priv *poid_par_priv);

#पूर्ण_अगर

