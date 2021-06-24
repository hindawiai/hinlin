<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_L2_H
#घोषणा _QED_L2_H
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/qed_eth_अगर.h>
#समावेश "qed.h"
#समावेश "qed_hw.h"
#समावेश "qed_sp.h"
काष्ठा qed_rss_params अणु
	u8 update_rss_config;
	u8 rss_enable;
	u8 rss_eng_id;
	u8 update_rss_capabilities;
	u8 update_rss_ind_table;
	u8 update_rss_key;
	u8 rss_caps;
	u8 rss_table_size_log;

	/* Indirection table consist of rx queue handles */
	व्योम *rss_ind_table[QED_RSS_IND_TABLE_SIZE];
	u32 rss_key[QED_RSS_KEY_SIZE];
पूर्ण;

काष्ठा qed_sge_tpa_params अणु
	u8 max_buffers_per_cqe;

	u8 update_tpa_en_flg;
	u8 tpa_ipv4_en_flg;
	u8 tpa_ipv6_en_flg;
	u8 tpa_ipv4_tunn_en_flg;
	u8 tpa_ipv6_tunn_en_flg;

	u8 update_tpa_param_flg;
	u8 tpa_pkt_split_flg;
	u8 tpa_hdr_data_split_flg;
	u8 tpa_gro_consistent_flg;
	u8 tpa_max_aggs_num;
	u16 tpa_max_size;
	u16 tpa_min_माप_प्रकारo_start;
	u16 tpa_min_माप_प्रकारo_cont;
पूर्ण;

क्रमागत qed_filter_opcode अणु
	QED_FILTER_ADD,
	QED_FILTER_REMOVE,
	QED_FILTER_MOVE,
	QED_FILTER_REPLACE,	/* Delete all MACs and add new one instead */
	QED_FILTER_FLUSH,	/* Removes all filters */
पूर्ण;

क्रमागत qed_filter_ucast_type अणु
	QED_FILTER_MAC,
	QED_FILTER_VLAN,
	QED_FILTER_MAC_VLAN,
	QED_FILTER_INNER_MAC,
	QED_FILTER_INNER_VLAN,
	QED_FILTER_INNER_PAIR,
	QED_FILTER_INNER_MAC_VNI_PAIR,
	QED_FILTER_MAC_VNI_PAIR,
	QED_FILTER_VNI,
पूर्ण;

काष्ठा qed_filter_ucast अणु
	क्रमागत qed_filter_opcode opcode;
	क्रमागत qed_filter_ucast_type type;
	u8 is_rx_filter;
	u8 is_tx_filter;
	u8 vport_to_add_to;
	u8 vport_to_हटाओ_from;
	अचिन्हित अक्षर mac[ETH_ALEN];
	u8 निश्चित_on_error;
	u16 vlan;
	u32 vni;
पूर्ण;

काष्ठा qed_filter_mcast अणु
	/* MOVE is not supported क्रम multicast */
	क्रमागत qed_filter_opcode opcode;
	u8 vport_to_add_to;
	u8 vport_to_हटाओ_from;
	u8 num_mc_addrs;
#घोषणा QED_MAX_MC_ADDRS        64
	अचिन्हित अक्षर mac[QED_MAX_MC_ADDRS][ETH_ALEN];
पूर्ण;

/**
 * @brief qed_eth_rx_queue_stop - This ramrod बंदs an Rx queue
 *
 * @param p_hwfn
 * @param p_rxq			Handler of queue to बंद
 * @param eq_completion_only	If True completion will be on
 *				EQe, अगर False completion will be
 *				on EQe अगर p_hwfn opaque
 *				dअगरferent from the RXQ opaque
 *				otherwise on CQe.
 * @param cqe_completion	If True completion will be
 *				receive on CQe.
 * @वापस पूर्णांक
 */
पूर्णांक
qed_eth_rx_queue_stop(काष्ठा qed_hwfn *p_hwfn,
		      व्योम *p_rxq,
		      bool eq_completion_only, bool cqe_completion);

/**
 * @brief qed_eth_tx_queue_stop - बंदs a Tx queue
 *
 * @param p_hwfn
 * @param p_txq - handle to Tx queue needed to be बंदd
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_eth_tx_queue_stop(काष्ठा qed_hwfn *p_hwfn, व्योम *p_txq);

क्रमागत qed_tpa_mode अणु
	QED_TPA_MODE_NONE,
	QED_TPA_MODE_UNUSED,
	QED_TPA_MODE_GRO,
	QED_TPA_MODE_MAX
पूर्ण;

काष्ठा qed_sp_vport_start_params अणु
	क्रमागत qed_tpa_mode tpa_mode;
	bool हटाओ_inner_vlan;
	bool tx_चयनing;
	bool handle_ptp_pkts;
	bool only_untagged;
	bool drop_ttl0;
	u8 max_buffers_per_cqe;
	u32 concrete_fid;
	u16 opaque_fid;
	u8 vport_id;
	u16 mtu;
	bool check_mac;
	bool check_ethtype;
पूर्ण;

पूर्णांक qed_sp_eth_vport_start(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_sp_vport_start_params *p_params);


काष्ठा qed_filter_accept_flags अणु
	u8	update_rx_mode_config;
	u8	update_tx_mode_config;
	u8	rx_accept_filter;
	u8	tx_accept_filter;
#घोषणा QED_ACCEPT_NONE         0x01
#घोषणा QED_ACCEPT_UCAST_MATCHED        0x02
#घोषणा QED_ACCEPT_UCAST_UNMATCHED      0x04
#घोषणा QED_ACCEPT_MCAST_MATCHED        0x08
#घोषणा QED_ACCEPT_MCAST_UNMATCHED      0x10
#घोषणा QED_ACCEPT_BCAST                0x20
#घोषणा QED_ACCEPT_ANY_VNI              0x40
पूर्ण;

काष्ठा qed_arfs_config_params अणु
	bool tcp;
	bool udp;
	bool ipv4;
	bool ipv6;
	क्रमागत qed_filter_config_mode mode;
पूर्ण;

काष्ठा qed_sp_vport_update_params अणु
	u16				opaque_fid;
	u8				vport_id;
	u8				update_vport_active_rx_flg;
	u8				vport_active_rx_flg;
	u8				update_vport_active_tx_flg;
	u8				vport_active_tx_flg;
	u8				update_inner_vlan_removal_flg;
	u8				inner_vlan_removal_flg;
	u8				silent_vlan_removal_flg;
	u8				update_शेष_vlan_enable_flg;
	u8				शेष_vlan_enable_flg;
	u8				update_शेष_vlan_flg;
	u16				शेष_vlan;
	u8				update_tx_चयनing_flg;
	u8				tx_चयनing_flg;
	u8				update_approx_mcast_flg;
	u8				update_anti_spoofing_en_flg;
	u8				anti_spoofing_en;
	u8				update_accept_any_vlan_flg;
	u8				accept_any_vlan;
	u32				bins[8];
	काष्ठा qed_rss_params		*rss_params;
	काष्ठा qed_filter_accept_flags	accept_flags;
	काष्ठा qed_sge_tpa_params	*sge_tpa_params;
	u8				update_ctl_frame_check;
	u8				mac_chk_en;
	u8				ethtype_chk_en;
पूर्ण;

पूर्णांक qed_sp_vport_update(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_sp_vport_update_params *p_params,
			क्रमागत spq_mode comp_mode,
			काष्ठा qed_spq_comp_cb *p_comp_data);

/**
 * @brief qed_sp_vport_stop -
 *
 * This ramrod बंदs a VPort after all its RX and TX queues are terminated.
 * An Assert is generated अगर any queues are left खोलो.
 *
 * @param p_hwfn
 * @param opaque_fid
 * @param vport_id VPort ID
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_sp_vport_stop(काष्ठा qed_hwfn *p_hwfn, u16 opaque_fid, u8 vport_id);

पूर्णांक qed_sp_eth_filter_ucast(काष्ठा qed_hwfn *p_hwfn,
			    u16 opaque_fid,
			    काष्ठा qed_filter_ucast *p_filter_cmd,
			    क्रमागत spq_mode comp_mode,
			    काष्ठा qed_spq_comp_cb *p_comp_data);

/**
 * @brief qed_sp_rx_eth_queues_update -
 *
 * This ramrod updates an RX queue. It is used क्रम setting the active state
 * of the queue and updating the TPA and SGE parameters.
 *
 * @note At the moment - only used by non-linux VFs.
 *
 * @param p_hwfn
 * @param pp_rxq_handlers	An array of queue handlers to be updated.
 * @param num_rxqs              number of queues to update.
 * @param complete_cqe_flg	Post completion to the CQE Ring अगर set
 * @param complete_event_flg	Post completion to the Event Ring अगर set
 * @param comp_mode
 * @param p_comp_data
 *
 * @वापस पूर्णांक
 */

पूर्णांक
qed_sp_eth_rx_queues_update(काष्ठा qed_hwfn *p_hwfn,
			    व्योम **pp_rxq_handlers,
			    u8 num_rxqs,
			    u8 complete_cqe_flg,
			    u8 complete_event_flg,
			    क्रमागत spq_mode comp_mode,
			    काष्ठा qed_spq_comp_cb *p_comp_data);

व्योम qed_get_vport_stats(काष्ठा qed_dev *cdev, काष्ठा qed_eth_stats *stats);

व्योम qed_reset_vport_stats(काष्ठा qed_dev *cdev);

/**
 * *@brief qed_arfs_mode_configure -
 *
 **Enable or disable rfs mode. It must accept atleast one of tcp or udp true
 **and atleast one of ipv4 or ipv6 true to enable rfs mode.
 *
 **@param p_hwfn
 **@param p_ptt
 **@param p_cfg_params - arfs mode configuration parameters.
 *
 */
व्योम qed_arfs_mode_configure(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt,
			     काष्ठा qed_arfs_config_params *p_cfg_params);

/**
 * @brief - qed_configure_rfs_ntuple_filter
 *
 * This ramrod should be used to add or हटाओ arfs hw filter
 *
 * @params p_hwfn
 * @params p_cb - Used क्रम QED_SPQ_MODE_CB,where client would initialize
 *		  it with cookie and callback function address, अगर not
 *		  using this mode then client must pass शून्य.
 * @params p_params
 */
पूर्णांक
qed_configure_rfs_ntuple_filter(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_spq_comp_cb *p_cb,
				काष्ठा qed_ntuple_filter_params *p_params);

#घोषणा MAX_QUEUES_PER_QZONE    (माप(अचिन्हित दीर्घ) * 8)
#घोषणा QED_QUEUE_CID_SELF	(0xff)

/* Almost identical to the qed_queue_start_common_params,
 * but here we मुख्यtain the SB index in IGU CAM.
 */
काष्ठा qed_queue_cid_params अणु
	u8 vport_id;
	u16 queue_id;
	u8 stats_id;
पूर्ण;

/* Additional parameters required क्रम initialization of the queue_cid
 * and are relevant only क्रम a PF initializing one क्रम its VFs.
 */
काष्ठा qed_queue_cid_vf_params अणु
	/* Should match the VF's relative index */
	u8 vfid;

	/* 0-based queue index. Should reflect the relative qzone the
	 * VF thinks is associated with it [in its range].
	 */
	u8 vf_qid;

	/* Indicates a VF is legacy, making it dअगरfer in several things:
	 *  - Producers would be placed in a dअगरferent place.
	 *  - Makes assumptions regarding the CIDs.
	 */
	u8 vf_legacy;

	u8 qid_usage_idx;
पूर्ण;

काष्ठा qed_queue_cid अणु
	/* For stats-id, the `rel' is actually असलolute as well */
	काष्ठा qed_queue_cid_params rel;
	काष्ठा qed_queue_cid_params असल;

	/* These have no 'relative' meaning */
	u16 sb_igu_id;
	u8 sb_idx;

	u32 cid;
	u16 opaque_fid;

	bool b_is_rx;

	/* VFs queues are mapped dअगरferently, so we need to know the
	 * relative queue associated with them [0-based].
	 * Notice this is relevant on the *PF* queue-cid of its VF's queues,
	 * and not on the VF itself.
	 */
	u8 vfid;
	u8 vf_qid;

	/* We need an additional index to dअगरferentiate between queues खोलोed
	 * क्रम same queue-zone, as VFs would have to communicate the info
	 * to the PF [otherwise PF has no way to dअगरferentiate].
	 */
	u8 qid_usage_idx;

	u8 vf_legacy;
#घोषणा QED_QCID_LEGACY_VF_RX_PROD	(BIT(0))
#घोषणा QED_QCID_LEGACY_VF_CID		(BIT(1))

	काष्ठा qed_hwfn *p_owner;
पूर्ण;

पूर्णांक qed_l2_alloc(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_l2_setup(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_l2_मुक्त(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_eth_queue_cid_release(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_queue_cid *p_cid);

काष्ठा qed_queue_cid *
qed_eth_queue_to_cid(काष्ठा qed_hwfn *p_hwfn,
		     u16 opaque_fid,
		     काष्ठा qed_queue_start_common_params *p_params,
		     bool b_is_rx,
		     काष्ठा qed_queue_cid_vf_params *p_vf_params);

पूर्णांक
qed_sp_eth_vport_start(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_sp_vport_start_params *p_params);

/**
 * @brief - Starts an Rx queue, when queue_cid is alपढ़ोy prepared
 *
 * @param p_hwfn
 * @param p_cid
 * @param bd_max_bytes
 * @param bd_chain_phys_addr
 * @param cqe_pbl_addr
 * @param cqe_pbl_size
 *
 * @वापस पूर्णांक
 */
पूर्णांक
qed_eth_rxq_start_ramrod(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_queue_cid *p_cid,
			 u16 bd_max_bytes,
			 dma_addr_t bd_chain_phys_addr,
			 dma_addr_t cqe_pbl_addr, u16 cqe_pbl_size);

/**
 * @brief - Starts a Tx queue, where queue_cid is alपढ़ोy prepared
 *
 * @param p_hwfn
 * @param p_cid
 * @param pbl_addr
 * @param pbl_size
 * @param p_pq_params - parameters क्रम choosing the PQ क्रम this Tx queue
 *
 * @वापस पूर्णांक
 */
पूर्णांक
qed_eth_txq_start_ramrod(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_queue_cid *p_cid,
			 dma_addr_t pbl_addr, u16 pbl_size, u16 pq_id);

u8 qed_mcast_bin_from_mac(u8 *mac);

पूर्णांक qed_set_rxq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 u16 coalesce, काष्ठा qed_queue_cid *p_cid);

पूर्णांक qed_set_txq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 u16 coalesce, काष्ठा qed_queue_cid *p_cid);

पूर्णांक qed_get_rxq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_queue_cid *p_cid, u16 *p_hw_coal);

पूर्णांक qed_get_txq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 काष्ठा qed_queue_cid *p_cid, u16 *p_hw_coal);

#पूर्ण_अगर
