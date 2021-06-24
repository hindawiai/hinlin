<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Implementation of host-to-chip MIBs of WFxxx Split Mac (WSM) API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (C) 2010, ST-Ericsson SA
 */
#अगर_अघोषित WFX_HIF_TX_MIB_H
#घोषणा WFX_HIF_TX_MIB_H

काष्ठा wfx_vअगर;
काष्ठा sk_buff;

पूर्णांक hअगर_set_output_घातer(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val);
पूर्णांक hअगर_set_beacon_wakeup_period(काष्ठा wfx_vअगर *wvअगर,
				 अचिन्हित पूर्णांक dtim_पूर्णांकerval,
				 अचिन्हित पूर्णांक listen_पूर्णांकerval);
पूर्णांक hअगर_set_rcpi_rssi_threshold(काष्ठा wfx_vअगर *wvअगर,
				पूर्णांक rssi_thold, पूर्णांक rssi_hyst);
पूर्णांक hअगर_get_counters_table(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id,
			   काष्ठा hअगर_mib_extended_count_table *arg);
पूर्णांक hअगर_set_macaddr(काष्ठा wfx_vअगर *wvअगर, u8 *mac);
पूर्णांक hअगर_set_rx_filter(काष्ठा wfx_vअगर *wvअगर,
		      bool filter_bssid, bool fwd_probe_req);
पूर्णांक hअगर_set_beacon_filter_table(काष्ठा wfx_vअगर *wvअगर, पूर्णांक tbl_len,
				स्थिर काष्ठा hअगर_ie_table_entry *tbl);
पूर्णांक hअगर_beacon_filter_control(काष्ठा wfx_vअगर *wvअगर,
			      पूर्णांक enable, पूर्णांक beacon_count);
पूर्णांक hअगर_set_operational_mode(काष्ठा wfx_dev *wdev, क्रमागत hअगर_op_घातer_mode mode);
पूर्णांक hअगर_set_ढाँचा_frame(काष्ठा wfx_vअगर *wvअगर, काष्ठा sk_buff *skb,
			   u8 frame_type, पूर्णांक init_rate);
पूर्णांक hअगर_set_mfp(काष्ठा wfx_vअगर *wvअगर, bool capable, bool required);
पूर्णांक hअगर_set_block_ack_policy(काष्ठा wfx_vअगर *wvअगर,
			     u8 tx_tid_policy, u8 rx_tid_policy);
पूर्णांक hअगर_set_association_mode(काष्ठा wfx_vअगर *wvअगर, पूर्णांक ampdu_density,
			     bool greenfield, bool लघु_preamble);
पूर्णांक hअगर_set_tx_rate_retry_policy(काष्ठा wfx_vअगर *wvअगर,
				 पूर्णांक policy_index, u8 *rates);
पूर्णांक hअगर_keep_alive_period(काष्ठा wfx_vअगर *wvअगर, पूर्णांक period);
पूर्णांक hअगर_set_arp_ipv4_filter(काष्ठा wfx_vअगर *wvअगर, पूर्णांक idx, __be32 *addr);
पूर्णांक hअगर_use_multi_tx_conf(काष्ठा wfx_dev *wdev, bool enable);
पूर्णांक hअगर_set_uapsd_info(काष्ठा wfx_vअगर *wvअगर, अचिन्हित दीर्घ val);
पूर्णांक hअगर_erp_use_protection(काष्ठा wfx_vअगर *wvअगर, bool enable);
पूर्णांक hअगर_slot_समय(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val);
पूर्णांक hअगर_wep_शेष_key_id(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val);
पूर्णांक hअगर_rts_threshold(काष्ठा wfx_vअगर *wvअगर, पूर्णांक val);

#पूर्ण_अगर
