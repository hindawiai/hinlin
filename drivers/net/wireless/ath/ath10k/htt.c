<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>

#समावेश "htt.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "hif.h"

अटल स्थिर क्रमागत htt_t2h_msg_type htt_मुख्य_t2h_msg_types[] = अणु
	[HTT_MAIN_T2H_MSG_TYPE_VERSION_CONF] = HTT_T2H_MSG_TYPE_VERSION_CONF,
	[HTT_MAIN_T2H_MSG_TYPE_RX_IND] = HTT_T2H_MSG_TYPE_RX_IND,
	[HTT_MAIN_T2H_MSG_TYPE_RX_FLUSH] = HTT_T2H_MSG_TYPE_RX_FLUSH,
	[HTT_MAIN_T2H_MSG_TYPE_PEER_MAP] = HTT_T2H_MSG_TYPE_PEER_MAP,
	[HTT_MAIN_T2H_MSG_TYPE_PEER_UNMAP] = HTT_T2H_MSG_TYPE_PEER_UNMAP,
	[HTT_MAIN_T2H_MSG_TYPE_RX_ADDBA] = HTT_T2H_MSG_TYPE_RX_ADDBA,
	[HTT_MAIN_T2H_MSG_TYPE_RX_DELBA] = HTT_T2H_MSG_TYPE_RX_DELBA,
	[HTT_MAIN_T2H_MSG_TYPE_TX_COMPL_IND] = HTT_T2H_MSG_TYPE_TX_COMPL_IND,
	[HTT_MAIN_T2H_MSG_TYPE_PKTLOG] = HTT_T2H_MSG_TYPE_PKTLOG,
	[HTT_MAIN_T2H_MSG_TYPE_STATS_CONF] = HTT_T2H_MSG_TYPE_STATS_CONF,
	[HTT_MAIN_T2H_MSG_TYPE_RX_FRAG_IND] = HTT_T2H_MSG_TYPE_RX_FRAG_IND,
	[HTT_MAIN_T2H_MSG_TYPE_SEC_IND] = HTT_T2H_MSG_TYPE_SEC_IND,
	[HTT_MAIN_T2H_MSG_TYPE_TX_INSPECT_IND] =
		HTT_T2H_MSG_TYPE_TX_INSPECT_IND,
	[HTT_MAIN_T2H_MSG_TYPE_MGMT_TX_COMPL_IND] =
		HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION,
	[HTT_MAIN_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND] =
		HTT_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND,
	[HTT_MAIN_T2H_MSG_TYPE_RX_PN_IND] = HTT_T2H_MSG_TYPE_RX_PN_IND,
	[HTT_MAIN_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND] =
		HTT_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND,
	[HTT_MAIN_T2H_MSG_TYPE_TEST] = HTT_T2H_MSG_TYPE_TEST,
पूर्ण;

अटल स्थिर क्रमागत htt_t2h_msg_type htt_10x_t2h_msg_types[] = अणु
	[HTT_10X_T2H_MSG_TYPE_VERSION_CONF] = HTT_T2H_MSG_TYPE_VERSION_CONF,
	[HTT_10X_T2H_MSG_TYPE_RX_IND] = HTT_T2H_MSG_TYPE_RX_IND,
	[HTT_10X_T2H_MSG_TYPE_RX_FLUSH] = HTT_T2H_MSG_TYPE_RX_FLUSH,
	[HTT_10X_T2H_MSG_TYPE_PEER_MAP] = HTT_T2H_MSG_TYPE_PEER_MAP,
	[HTT_10X_T2H_MSG_TYPE_PEER_UNMAP] = HTT_T2H_MSG_TYPE_PEER_UNMAP,
	[HTT_10X_T2H_MSG_TYPE_RX_ADDBA] = HTT_T2H_MSG_TYPE_RX_ADDBA,
	[HTT_10X_T2H_MSG_TYPE_RX_DELBA] = HTT_T2H_MSG_TYPE_RX_DELBA,
	[HTT_10X_T2H_MSG_TYPE_TX_COMPL_IND] = HTT_T2H_MSG_TYPE_TX_COMPL_IND,
	[HTT_10X_T2H_MSG_TYPE_PKTLOG] = HTT_T2H_MSG_TYPE_PKTLOG,
	[HTT_10X_T2H_MSG_TYPE_STATS_CONF] = HTT_T2H_MSG_TYPE_STATS_CONF,
	[HTT_10X_T2H_MSG_TYPE_RX_FRAG_IND] = HTT_T2H_MSG_TYPE_RX_FRAG_IND,
	[HTT_10X_T2H_MSG_TYPE_SEC_IND] = HTT_T2H_MSG_TYPE_SEC_IND,
	[HTT_10X_T2H_MSG_TYPE_RC_UPDATE_IND] = HTT_T2H_MSG_TYPE_RC_UPDATE_IND,
	[HTT_10X_T2H_MSG_TYPE_TX_INSPECT_IND] = HTT_T2H_MSG_TYPE_TX_INSPECT_IND,
	[HTT_10X_T2H_MSG_TYPE_TEST] = HTT_T2H_MSG_TYPE_TEST,
	[HTT_10X_T2H_MSG_TYPE_CHAN_CHANGE] = HTT_T2H_MSG_TYPE_CHAN_CHANGE,
	[HTT_10X_T2H_MSG_TYPE_AGGR_CONF] = HTT_T2H_MSG_TYPE_AGGR_CONF,
	[HTT_10X_T2H_MSG_TYPE_STATS_NOUPLOAD] = HTT_T2H_MSG_TYPE_STATS_NOUPLOAD,
	[HTT_10X_T2H_MSG_TYPE_MGMT_TX_COMPL_IND] =
		HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION,
पूर्ण;

अटल स्थिर क्रमागत htt_t2h_msg_type htt_tlv_t2h_msg_types[] = अणु
	[HTT_TLV_T2H_MSG_TYPE_VERSION_CONF] = HTT_T2H_MSG_TYPE_VERSION_CONF,
	[HTT_TLV_T2H_MSG_TYPE_RX_IND] = HTT_T2H_MSG_TYPE_RX_IND,
	[HTT_TLV_T2H_MSG_TYPE_RX_FLUSH] = HTT_T2H_MSG_TYPE_RX_FLUSH,
	[HTT_TLV_T2H_MSG_TYPE_PEER_MAP] = HTT_T2H_MSG_TYPE_PEER_MAP,
	[HTT_TLV_T2H_MSG_TYPE_PEER_UNMAP] = HTT_T2H_MSG_TYPE_PEER_UNMAP,
	[HTT_TLV_T2H_MSG_TYPE_RX_ADDBA] = HTT_T2H_MSG_TYPE_RX_ADDBA,
	[HTT_TLV_T2H_MSG_TYPE_RX_DELBA] = HTT_T2H_MSG_TYPE_RX_DELBA,
	[HTT_TLV_T2H_MSG_TYPE_TX_COMPL_IND] = HTT_T2H_MSG_TYPE_TX_COMPL_IND,
	[HTT_TLV_T2H_MSG_TYPE_PKTLOG] = HTT_T2H_MSG_TYPE_PKTLOG,
	[HTT_TLV_T2H_MSG_TYPE_STATS_CONF] = HTT_T2H_MSG_TYPE_STATS_CONF,
	[HTT_TLV_T2H_MSG_TYPE_RX_FRAG_IND] = HTT_T2H_MSG_TYPE_RX_FRAG_IND,
	[HTT_TLV_T2H_MSG_TYPE_SEC_IND] = HTT_T2H_MSG_TYPE_SEC_IND,
	[HTT_TLV_T2H_MSG_TYPE_RC_UPDATE_IND] = HTT_T2H_MSG_TYPE_RC_UPDATE_IND,
	[HTT_TLV_T2H_MSG_TYPE_TX_INSPECT_IND] = HTT_T2H_MSG_TYPE_TX_INSPECT_IND,
	[HTT_TLV_T2H_MSG_TYPE_MGMT_TX_COMPL_IND] =
		HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION,
	[HTT_TLV_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND] =
		HTT_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND,
	[HTT_TLV_T2H_MSG_TYPE_RX_PN_IND] = HTT_T2H_MSG_TYPE_RX_PN_IND,
	[HTT_TLV_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND] =
		HTT_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND,
	[HTT_TLV_T2H_MSG_TYPE_RX_IN_ORD_PADDR_IND] =
		HTT_T2H_MSG_TYPE_RX_IN_ORD_PADDR_IND,
	[HTT_TLV_T2H_MSG_TYPE_WDI_IPA_OP_RESPONSE] =
		HTT_T2H_MSG_TYPE_WDI_IPA_OP_RESPONSE,
	[HTT_TLV_T2H_MSG_TYPE_CHAN_CHANGE] = HTT_T2H_MSG_TYPE_CHAN_CHANGE,
	[HTT_TLV_T2H_MSG_TYPE_RX_OFLD_PKT_ERR] =
		HTT_T2H_MSG_TYPE_RX_OFLD_PKT_ERR,
	[HTT_TLV_T2H_MSG_TYPE_TEST] = HTT_T2H_MSG_TYPE_TEST,
पूर्ण;

अटल स्थिर क्रमागत htt_t2h_msg_type htt_10_4_t2h_msg_types[] = अणु
	[HTT_10_4_T2H_MSG_TYPE_VERSION_CONF] = HTT_T2H_MSG_TYPE_VERSION_CONF,
	[HTT_10_4_T2H_MSG_TYPE_RX_IND] = HTT_T2H_MSG_TYPE_RX_IND,
	[HTT_10_4_T2H_MSG_TYPE_RX_FLUSH] = HTT_T2H_MSG_TYPE_RX_FLUSH,
	[HTT_10_4_T2H_MSG_TYPE_PEER_MAP] = HTT_T2H_MSG_TYPE_PEER_MAP,
	[HTT_10_4_T2H_MSG_TYPE_PEER_UNMAP] = HTT_T2H_MSG_TYPE_PEER_UNMAP,
	[HTT_10_4_T2H_MSG_TYPE_RX_ADDBA] = HTT_T2H_MSG_TYPE_RX_ADDBA,
	[HTT_10_4_T2H_MSG_TYPE_RX_DELBA] = HTT_T2H_MSG_TYPE_RX_DELBA,
	[HTT_10_4_T2H_MSG_TYPE_TX_COMPL_IND] = HTT_T2H_MSG_TYPE_TX_COMPL_IND,
	[HTT_10_4_T2H_MSG_TYPE_PKTLOG] = HTT_T2H_MSG_TYPE_PKTLOG,
	[HTT_10_4_T2H_MSG_TYPE_STATS_CONF] = HTT_T2H_MSG_TYPE_STATS_CONF,
	[HTT_10_4_T2H_MSG_TYPE_RX_FRAG_IND] = HTT_T2H_MSG_TYPE_RX_FRAG_IND,
	[HTT_10_4_T2H_MSG_TYPE_SEC_IND] = HTT_T2H_MSG_TYPE_SEC_IND,
	[HTT_10_4_T2H_MSG_TYPE_RC_UPDATE_IND] = HTT_T2H_MSG_TYPE_RC_UPDATE_IND,
	[HTT_10_4_T2H_MSG_TYPE_TX_INSPECT_IND] =
				HTT_T2H_MSG_TYPE_TX_INSPECT_IND,
	[HTT_10_4_T2H_MSG_TYPE_MGMT_TX_COMPL_IND] =
				HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION,
	[HTT_10_4_T2H_MSG_TYPE_CHAN_CHANGE] = HTT_T2H_MSG_TYPE_CHAN_CHANGE,
	[HTT_10_4_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND] =
				HTT_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND,
	[HTT_10_4_T2H_MSG_TYPE_RX_PN_IND] = HTT_T2H_MSG_TYPE_RX_PN_IND,
	[HTT_10_4_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND] =
				HTT_T2H_MSG_TYPE_RX_OFFLOAD_DELIVER_IND,
	[HTT_10_4_T2H_MSG_TYPE_TEST] = HTT_T2H_MSG_TYPE_TEST,
	[HTT_10_4_T2H_MSG_TYPE_EN_STATS] = HTT_T2H_MSG_TYPE_EN_STATS,
	[HTT_10_4_T2H_MSG_TYPE_AGGR_CONF] = HTT_T2H_MSG_TYPE_AGGR_CONF,
	[HTT_10_4_T2H_MSG_TYPE_TX_FETCH_IND] =
				HTT_T2H_MSG_TYPE_TX_FETCH_IND,
	[HTT_10_4_T2H_MSG_TYPE_TX_FETCH_CONFIRM] =
				HTT_T2H_MSG_TYPE_TX_FETCH_CONFIRM,
	[HTT_10_4_T2H_MSG_TYPE_STATS_NOUPLOAD] =
				HTT_T2H_MSG_TYPE_STATS_NOUPLOAD,
	[HTT_10_4_T2H_MSG_TYPE_TX_MODE_SWITCH_IND] =
				HTT_T2H_MSG_TYPE_TX_MODE_SWITCH_IND,
	[HTT_10_4_T2H_MSG_TYPE_PEER_STATS] =
				HTT_T2H_MSG_TYPE_PEER_STATS,
पूर्ण;

पूर्णांक ath10k_htt_connect(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k_htc_svc_conn_req conn_req;
	काष्ठा ath10k_htc_svc_conn_resp conn_resp;
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ath10k_htc_ep *ep;
	पूर्णांक status;

	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));

	conn_req.ep_ops.ep_tx_complete = ath10k_htt_htc_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_htt_htc_t2h_msg_handler;
	conn_req.ep_ops.ep_tx_credits = ath10k_htt_op_ep_tx_credits;

	/* connect to control service */
	conn_req.service_id = ATH10K_HTC_SVC_ID_HTT_DATA_MSG;

	status = ath10k_htc_connect_service(&htt->ar->htc, &conn_req,
					    &conn_resp);

	अगर (status)
		वापस status;

	htt->eid = conn_resp.eid;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL) अणु
		ep = &ar->htc.endpoपूर्णांक[htt->eid];
		ath10k_htc_setup_tx_req(ep);
	पूर्ण

	htt->disable_tx_comp = ath10k_hअगर_get_htt_tx_complete(htt->ar);
	अगर (htt->disable_tx_comp)
		ath10k_htc_change_tx_credit_flow(&htt->ar->htc, htt->eid, true);

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;

	htt->ar = ar;

	/*
	 * Prefetch enough data to satisfy target
	 * classअगरication engine.
	 * This is क्रम LL chips. HL chips will probably
	 * transfer all frame in the tx fragment.
	 */
	htt->prefetch_len =
		36 + /* 802.11 + qos + ht */
		4 + /* 802.1q */
		8 + /* llc snap */
		2; /* ip4 dscp or ip6 priority */

	चयन (ar->running_fw->fw_file.htt_op_version) अणु
	हाल ATH10K_FW_HTT_OP_VERSION_10_4:
		ar->htt.t2h_msg_types = htt_10_4_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_10_4_T2H_NUM_MSGS;
		अवरोध;
	हाल ATH10K_FW_HTT_OP_VERSION_10_1:
		ar->htt.t2h_msg_types = htt_10x_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_10X_T2H_NUM_MSGS;
		अवरोध;
	हाल ATH10K_FW_HTT_OP_VERSION_TLV:
		ar->htt.t2h_msg_types = htt_tlv_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_TLV_T2H_NUM_MSGS;
		अवरोध;
	हाल ATH10K_FW_HTT_OP_VERSION_MAIN:
		ar->htt.t2h_msg_types = htt_मुख्य_t2h_msg_types;
		ar->htt.t2h_msg_types_max = HTT_MAIN_T2H_NUM_MSGS;
		अवरोध;
	हाल ATH10K_FW_HTT_OP_VERSION_MAX:
	हाल ATH10K_FW_HTT_OP_VERSION_UNSET:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	ath10k_htt_set_tx_ops(htt);
	ath10k_htt_set_rx_ops(htt);

	वापस 0;
पूर्ण

#घोषणा HTT_TARGET_VERSION_TIMEOUT_HZ (3 * HZ)

अटल पूर्णांक ath10k_htt_verअगरy_version(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "htt target version %d.%d\n",
		   htt->target_version_major, htt->target_version_minor);

	अगर (htt->target_version_major != 2 &&
	    htt->target_version_major != 3) अणु
		ath10k_err(ar, "unsupported htt major version %d. supported versions are 2 and 3\n",
			   htt->target_version_major);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_setup(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक status;

	init_completion(&htt->target_version_received);

	status = ath10k_htt_h2t_ver_req_msg(htt);
	अगर (status)
		वापस status;

	status = रुको_क्रम_completion_समयout(&htt->target_version_received,
					     HTT_TARGET_VERSION_TIMEOUT_HZ);
	अगर (status == 0) अणु
		ath10k_warn(ar, "htt version request timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	status = ath10k_htt_verअगरy_version(htt);
	अगर (status) अणु
		ath10k_warn(ar, "failed to verify htt version: %d\n",
			    status);
		वापस status;
	पूर्ण

	status = ath10k_htt_send_frag_desc_bank_cfg(htt);
	अगर (status)
		वापस status;

	status = ath10k_htt_send_rx_ring_cfg(htt);
	अगर (status) अणु
		ath10k_warn(ar, "failed to setup rx ring: %d\n",
			    status);
		वापस status;
	पूर्ण

	status = ath10k_htt_h2t_aggr_cfg_msg(htt,
					     htt->max_num_ampdu,
					     htt->max_num_amsdu);
	अगर (status) अणु
		ath10k_warn(ar, "failed to setup amsdu/ampdu limit: %d\n",
			    status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण
