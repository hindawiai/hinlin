<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 */

#अगर_अघोषित _QED_VF_H
#घोषणा _QED_VF_H

#समावेश "qed_l2.h"
#समावेश "qed_mcp.h"

#घोषणा T_ETH_INसूचीECTION_TABLE_SIZE 128
#घोषणा T_ETH_RSS_KEY_SIZE 10

काष्ठा vf_pf_resc_request अणु
	u8 num_rxqs;
	u8 num_txqs;
	u8 num_sbs;
	u8 num_mac_filters;
	u8 num_vlan_filters;
	u8 num_mc_filters;
	u8 num_cids;
	u8 padding;
पूर्ण;

काष्ठा hw_sb_info अणु
	u16 hw_sb_id;
	u8 sb_qid;
	u8 padding[5];
पूर्ण;

#घोषणा TLV_BUFFER_SIZE                 1024

क्रमागत अणु
	PFVF_STATUS_WAITING,
	PFVF_STATUS_SUCCESS,
	PFVF_STATUS_FAILURE,
	PFVF_STATUS_NOT_SUPPORTED,
	PFVF_STATUS_NO_RESOURCE,
	PFVF_STATUS_FORCED,
	PFVF_STATUS_MALICIOUS,
पूर्ण;

/* vf pf channel tlvs */
/* general tlv header (used क्रम both vf->pf request and pf->vf response) */
काष्ठा channel_tlv अणु
	u16 type;
	u16 length;
पूर्ण;

/* header of first vf->pf tlv carries the offset used to calculate reponse
 * buffer address
 */
काष्ठा vfpf_first_tlv अणु
	काष्ठा channel_tlv tl;
	u32 padding;
	u64 reply_address;
पूर्ण;

/* header of pf->vf tlvs, carries the status of handling the request */
काष्ठा pfvf_tlv अणु
	काष्ठा channel_tlv tl;
	u8 status;
	u8 padding[3];
पूर्ण;

/* response tlv used क्रम most tlvs */
काष्ठा pfvf_def_resp_tlv अणु
	काष्ठा pfvf_tlv hdr;
पूर्ण;

/* used to terminate and pad a tlv list */
काष्ठा channel_list_end_tlv अणु
	काष्ठा channel_tlv tl;
	u8 padding[4];
पूर्ण;

#घोषणा VFPF_ACQUIRE_OS_LINUX (0)
#घोषणा VFPF_ACQUIRE_OS_WINDOWS (1)
#घोषणा VFPF_ACQUIRE_OS_ESX (2)
#घोषणा VFPF_ACQUIRE_OS_SOLARIS (3)
#घोषणा VFPF_ACQUIRE_OS_LINUX_USERSPACE (4)

काष्ठा vfpf_acquire_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	काष्ठा vf_pf_vfdev_info अणु
#घोषणा VFPF_ACQUIRE_CAP_PRE_FP_HSI     (1 << 0) /* VF pre-FP hsi version */
#घोषणा VFPF_ACQUIRE_CAP_100G		(1 << 1) /* VF can support 100g */
	/* A requirement क्रम supporting multi-Tx queues on a single queue-zone,
	 * VF would pass qids as additional inक्रमmation whenever passing queue
	 * references.
	 */
#घोषणा VFPF_ACQUIRE_CAP_QUEUE_QIDS     BIT(2)

	/* The VF is using the physical bar. While this is mostly पूर्णांकernal
	 * to the VF, might affect the number of CIDs supported assuming
	 * QUEUE_QIDS is set.
	 */
#घोषणा VFPF_ACQUIRE_CAP_PHYSICAL_BAR   BIT(3)
		u64 capabilities;
		u8 fw_major;
		u8 fw_minor;
		u8 fw_revision;
		u8 fw_engineering;
		u32 driver_version;
		u16 opaque_fid;	/* ME रेजिस्टर value */
		u8 os_type;	/* VFPF_ACQUIRE_OS_* value */
		u8 eth_fp_hsi_major;
		u8 eth_fp_hsi_minor;
		u8 padding[3];
	पूर्ण vfdev_info;

	काष्ठा vf_pf_resc_request resc_request;

	u64 bulletin_addr;
	u32 bulletin_size;
	u32 padding;
पूर्ण;

/* receive side scaling tlv */
काष्ठा vfpf_vport_update_rss_tlv अणु
	काष्ठा channel_tlv tl;

	u8 update_rss_flags;
#घोषणा VFPF_UPDATE_RSS_CONFIG_FLAG       BIT(0)
#घोषणा VFPF_UPDATE_RSS_CAPS_FLAG         BIT(1)
#घोषणा VFPF_UPDATE_RSS_IND_TABLE_FLAG    BIT(2)
#घोषणा VFPF_UPDATE_RSS_KEY_FLAG          BIT(3)

	u8 rss_enable;
	u8 rss_caps;
	u8 rss_table_size_log;	/* The table size is 2 ^ rss_table_size_log */
	u16 rss_ind_table[T_ETH_INसूचीECTION_TABLE_SIZE];
	u32 rss_key[T_ETH_RSS_KEY_SIZE];
पूर्ण;

काष्ठा pfvf_storm_stats अणु
	u32 address;
	u32 len;
पूर्ण;

काष्ठा pfvf_stats_info अणु
	काष्ठा pfvf_storm_stats mstats;
	काष्ठा pfvf_storm_stats pstats;
	काष्ठा pfvf_storm_stats tstats;
	काष्ठा pfvf_storm_stats ustats;
पूर्ण;

काष्ठा pfvf_acquire_resp_tlv अणु
	काष्ठा pfvf_tlv hdr;

	काष्ठा pf_vf_pfdev_info अणु
		u32 chip_num;
		u32 mfw_ver;

		u16 fw_major;
		u16 fw_minor;
		u16 fw_rev;
		u16 fw_eng;

		u64 capabilities;
#घोषणा PFVF_ACQUIRE_CAP_DEFAULT_UNTAGGED	BIT(0)
#घोषणा PFVF_ACQUIRE_CAP_100G			BIT(1)	/* If set, 100g PF */
/* There are old PF versions where the PF might mistakenly override the sanity
 * mechanism [version-based] and allow a VF that can't be supported to pass
 * the acquisition phase.
 * To overcome this, PFs now indicate that they're past that poपूर्णांक and the new
 * VFs would fail probe on the older PFs that fail to करो so.
 */
#घोषणा PFVF_ACQUIRE_CAP_POST_FW_OVERRIDE	BIT(2)

	/* PF expects queues to be received with additional qids */
#घोषणा PFVF_ACQUIRE_CAP_QUEUE_QIDS             BIT(3)

		u16 db_size;
		u8 indices_per_sb;
		u8 os_type;

		/* These should match the PF's qed_dev values */
		u16 chip_rev;
		u8 dev_type;

		/* Doorbell bar size configured in HW: log(size) or 0 */
		u8 bar_size;

		काष्ठा pfvf_stats_info stats_info;

		u8 port_mac[ETH_ALEN];

		/* It's possible PF had to configure an older fastpath HSI
		 * [in हाल VF is newer than PF]. This is communicated back
		 * to the VF. It can also be used in हाल of error due to
		 * non-matching versions to shed light in VF about failure.
		 */
		u8 major_fp_hsi;
		u8 minor_fp_hsi;
	पूर्ण pfdev_info;

	काष्ठा pf_vf_resc अणु
#घोषणा PFVF_MAX_QUEUES_PER_VF		16
#घोषणा PFVF_MAX_SBS_PER_VF		16
		काष्ठा hw_sb_info hw_sbs[PFVF_MAX_SBS_PER_VF];
		u8 hw_qid[PFVF_MAX_QUEUES_PER_VF];
		u8 cid[PFVF_MAX_QUEUES_PER_VF];

		u8 num_rxqs;
		u8 num_txqs;
		u8 num_sbs;
		u8 num_mac_filters;
		u8 num_vlan_filters;
		u8 num_mc_filters;
		u8 num_cids;
		u8 padding;
	पूर्ण resc;

	u32 bulletin_size;
	u32 padding;
पूर्ण;

काष्ठा pfvf_start_queue_resp_tlv अणु
	काष्ठा pfvf_tlv hdr;
	u32 offset;		/* offset to consumer/producer of queue */
	u8 padding[4];
पूर्ण;

/* Extended queue inक्रमmation - additional index क्रम reference inside qzone.
 * If commmunicated between VF/PF, each TLV relating to queues should be
 * extended by one such [or have a future base TLV that alपढ़ोy contains info].
 */
काष्ठा vfpf_qid_tlv अणु
	काष्ठा channel_tlv tl;
	u8 qid;
	u8 padding[3];
पूर्ण;

/* Setup Queue */
काष्ठा vfpf_start_rxq_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	/* physical addresses */
	u64 rxq_addr;
	u64 deprecated_sge_addr;
	u64 cqe_pbl_addr;

	u16 cqe_pbl_size;
	u16 hw_sb;
	u16 rx_qid;
	u16 hc_rate;		/* desired पूर्णांकerrupts per sec. */

	u16 bd_max_bytes;
	u16 stat_id;
	u8 sb_index;
	u8 padding[3];
पूर्ण;

काष्ठा vfpf_start_txq_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	/* physical addresses */
	u64 pbl_addr;
	u16 pbl_size;
	u16 stat_id;
	u16 tx_qid;
	u16 hw_sb;

	u32 flags;		/* VFPF_QUEUE_FLG_X flags */
	u16 hc_rate;		/* desired पूर्णांकerrupts per sec. */
	u8 sb_index;
	u8 padding[3];
पूर्ण;

/* Stop RX Queue */
काष्ठा vfpf_stop_rxqs_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u16 rx_qid;

	/* this field is deprecated and should *always* be set to '1' */
	u8 num_rxqs;
	u8 cqe_completion;
	u8 padding[4];
पूर्ण;

/* Stop TX Queues */
काष्ठा vfpf_stop_txqs_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u16 tx_qid;

	/* this field is deprecated and should *always* be set to '1' */
	u8 num_txqs;
	u8 padding[5];
पूर्ण;

काष्ठा vfpf_update_rxq_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u64 deprecated_sge_addr[PFVF_MAX_QUEUES_PER_VF];

	u16 rx_qid;
	u8 num_rxqs;
	u8 flags;
#घोषणा VFPF_RXQ_UPD_INIT_SGE_DEPRECATE_FLAG    BIT(0)
#घोषणा VFPF_RXQ_UPD_COMPLETE_CQE_FLAG          BIT(1)
#घोषणा VFPF_RXQ_UPD_COMPLETE_EVENT_FLAG        BIT(2)

	u8 padding[4];
पूर्ण;

/* Set Queue Filters */
काष्ठा vfpf_q_mac_vlan_filter अणु
	u32 flags;
#घोषणा VFPF_Q_FILTER_DEST_MAC_VALID    0x01
#घोषणा VFPF_Q_FILTER_VLAN_TAG_VALID    0x02
#घोषणा VFPF_Q_FILTER_SET_MAC           0x100	/* set/clear */

	u8 mac[ETH_ALEN];
	u16 vlan_tag;

	u8 padding[4];
पूर्ण;

/* Start a vport */
काष्ठा vfpf_vport_start_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u64 sb_addr[PFVF_MAX_SBS_PER_VF];

	u32 tpa_mode;
	u16 dep1;
	u16 mtu;

	u8 vport_id;
	u8 inner_vlan_removal;

	u8 only_untagged;
	u8 max_buffers_per_cqe;

	u8 padding[4];
पूर्ण;

/* Extended tlvs - need to add rss, mcast, accept mode tlvs */
काष्ठा vfpf_vport_update_activate_tlv अणु
	काष्ठा channel_tlv tl;
	u8 update_rx;
	u8 update_tx;
	u8 active_rx;
	u8 active_tx;
पूर्ण;

काष्ठा vfpf_vport_update_tx_चयन_tlv अणु
	काष्ठा channel_tlv tl;
	u8 tx_चयनing;
	u8 padding[3];
पूर्ण;

काष्ठा vfpf_vport_update_vlan_strip_tlv अणु
	काष्ठा channel_tlv tl;
	u8 हटाओ_vlan;
	u8 padding[3];
पूर्ण;

काष्ठा vfpf_vport_update_mcast_bin_tlv अणु
	काष्ठा channel_tlv tl;
	u8 padding[4];

	/* There are only 256 approx bins, and in HSI they're भागided पूर्णांकo
	 * 32-bit values. As old VFs used to set-bit to the values on its side,
	 * the upper half of the array is never expected to contain any data.
	 */
	u64 bins[4];
	u64 obsolete_bins[4];
पूर्ण;

काष्ठा vfpf_vport_update_accept_param_tlv अणु
	काष्ठा channel_tlv tl;
	u8 update_rx_mode;
	u8 update_tx_mode;
	u8 rx_accept_filter;
	u8 tx_accept_filter;
पूर्ण;

काष्ठा vfpf_vport_update_accept_any_vlan_tlv अणु
	काष्ठा channel_tlv tl;
	u8 update_accept_any_vlan_flg;
	u8 accept_any_vlan;

	u8 padding[2];
पूर्ण;

काष्ठा vfpf_vport_update_sge_tpa_tlv अणु
	काष्ठा channel_tlv tl;

	u16 sge_tpa_flags;
#घोषणा VFPF_TPA_IPV4_EN_FLAG		BIT(0)
#घोषणा VFPF_TPA_IPV6_EN_FLAG		BIT(1)
#घोषणा VFPF_TPA_PKT_SPLIT_FLAG		BIT(2)
#घोषणा VFPF_TPA_HDR_DATA_SPLIT_FLAG	BIT(3)
#घोषणा VFPF_TPA_GRO_CONSIST_FLAG	BIT(4)

	u8 update_sge_tpa_flags;
#घोषणा VFPF_UPDATE_SGE_DEPRECATED_FLAG	BIT(0)
#घोषणा VFPF_UPDATE_TPA_EN_FLAG		BIT(1)
#घोषणा VFPF_UPDATE_TPA_PARAM_FLAG	BIT(2)

	u8 max_buffers_per_cqe;

	u16 deprecated_sge_buff_size;
	u16 tpa_max_size;
	u16 tpa_min_माप_प्रकारo_start;
	u16 tpa_min_माप_प्रकारo_cont;

	u8 tpa_max_aggs_num;
	u8 padding[7];
पूर्ण;

/* Primary tlv as a header क्रम various extended tlvs क्रम
 * various functionalities in vport update ramrod.
 */
काष्ठा vfpf_vport_update_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;
पूर्ण;

काष्ठा vfpf_ucast_filter_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u8 opcode;
	u8 type;

	u8 mac[ETH_ALEN];

	u16 vlan;
	u16 padding[3];
पूर्ण;

/* tunnel update param tlv */
काष्ठा vfpf_update_tunn_param_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;

	u8 tun_mode_update_mask;
	u8 tunn_mode;
	u8 update_tun_cls;
	u8 vxlan_clss;
	u8 l2gre_clss;
	u8 ipgre_clss;
	u8 l2geneve_clss;
	u8 ipgeneve_clss;
	u8 update_geneve_port;
	u8 update_vxlan_port;
	u16 geneve_port;
	u16 vxlan_port;
	u8 padding[2];
पूर्ण;

काष्ठा pfvf_update_tunn_param_tlv अणु
	काष्ठा pfvf_tlv hdr;

	u16 tunn_feature_mask;
	u8 vxlan_mode;
	u8 l2geneve_mode;
	u8 ipgeneve_mode;
	u8 l2gre_mode;
	u8 ipgre_mode;
	u8 vxlan_clss;
	u8 l2gre_clss;
	u8 ipgre_clss;
	u8 l2geneve_clss;
	u8 ipgeneve_clss;
	u16 vxlan_udp_port;
	u16 geneve_udp_port;
पूर्ण;

काष्ठा tlv_buffer_size अणु
	u8 tlv_buffer[TLV_BUFFER_SIZE];
पूर्ण;

काष्ठा vfpf_update_coalesce अणु
	काष्ठा vfpf_first_tlv first_tlv;
	u16 rx_coal;
	u16 tx_coal;
	u16 qid;
	u8 padding[2];
पूर्ण;

काष्ठा vfpf_पढ़ो_coal_req_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;
	u16 qid;
	u8 is_rx;
	u8 padding[5];
पूर्ण;

काष्ठा pfvf_पढ़ो_coal_resp_tlv अणु
	काष्ठा pfvf_tlv hdr;
	u16 coal;
	u8 padding[6];
पूर्ण;

काष्ठा vfpf_bulletin_update_mac_tlv अणु
	काष्ठा vfpf_first_tlv first_tlv;
	u8 mac[ETH_ALEN];
	u8 padding[2];
पूर्ण;

जोड़ vfpf_tlvs अणु
	काष्ठा vfpf_first_tlv first_tlv;
	काष्ठा vfpf_acquire_tlv acquire;
	काष्ठा vfpf_start_rxq_tlv start_rxq;
	काष्ठा vfpf_start_txq_tlv start_txq;
	काष्ठा vfpf_stop_rxqs_tlv stop_rxqs;
	काष्ठा vfpf_stop_txqs_tlv stop_txqs;
	काष्ठा vfpf_update_rxq_tlv update_rxq;
	काष्ठा vfpf_vport_start_tlv start_vport;
	काष्ठा vfpf_vport_update_tlv vport_update;
	काष्ठा vfpf_ucast_filter_tlv ucast_filter;
	काष्ठा vfpf_update_tunn_param_tlv tunn_param_update;
	काष्ठा vfpf_update_coalesce update_coalesce;
	काष्ठा vfpf_पढ़ो_coal_req_tlv पढ़ो_coal_req;
	काष्ठा vfpf_bulletin_update_mac_tlv bulletin_update_mac;
	काष्ठा tlv_buffer_size tlv_buf_size;
पूर्ण;

जोड़ pfvf_tlvs अणु
	काष्ठा pfvf_def_resp_tlv शेष_resp;
	काष्ठा pfvf_acquire_resp_tlv acquire_resp;
	काष्ठा tlv_buffer_size tlv_buf_size;
	काष्ठा pfvf_start_queue_resp_tlv queue_start;
	काष्ठा pfvf_update_tunn_param_tlv tunn_param_resp;
	काष्ठा pfvf_पढ़ो_coal_resp_tlv पढ़ो_coal_resp;
पूर्ण;

क्रमागत qed_bulletin_bit अणु
	/* Alert the VF that a क्रमced MAC was set by the PF */
	MAC_ADDR_FORCED = 0,
	/* Alert the VF that a क्रमced VLAN was set by the PF */
	VLAN_ADDR_FORCED = 2,

	/* Indicate that `शेष_only_untagged' contains actual data */
	VFPF_BULLETIN_UNTAGGED_DEFAULT = 3,
	VFPF_BULLETIN_UNTAGGED_DEFAULT_FORCED = 4,

	/* Alert the VF that suggested mac was sent by the PF.
	 * MAC_ADDR will be disabled in हाल MAC_ADDR_FORCED is set.
	 */
	VFPF_BULLETIN_MAC_ADDR = 5
पूर्ण;

काष्ठा qed_bulletin_content अणु
	/* crc of काष्ठाure to ensure is not in mid-update */
	u32 crc;

	u32 version;

	/* biपंचांगap indicating which fields hold valid values */
	u64 valid_biपंचांगap;

	/* used क्रम MAC_ADDR or MAC_ADDR_FORCED */
	u8 mac[ETH_ALEN];

	/* If valid, 1 => only untagged Rx अगर no vlan is configured */
	u8 शेष_only_untagged;
	u8 padding;

	/* The following is a 'copy' of qed_mcp_link_state,
	 * qed_mcp_link_params and qed_mcp_link_capabilities. Since it's
	 * possible the काष्ठाs will increase further aदीर्घ the road we cannot
	 * have it here; Instead we need to have all of its fields.
	 */
	u8 req_स्वतःneg;
	u8 req_स्वतःneg_छोड़ो;
	u8 req_क्रमced_rx;
	u8 req_क्रमced_tx;
	u8 padding2[4];

	u32 req_adv_speed;
	u32 req_क्रमced_speed;
	u32 req_loopback;
	u32 padding3;

	u8 link_up;
	u8 full_duplex;
	u8 स्वतःneg;
	u8 स्वतःneg_complete;
	u8 parallel_detection;
	u8 pfc_enabled;
	u8 partner_tx_flow_ctrl_en;
	u8 partner_rx_flow_ctrl_en;
	u8 partner_adv_छोड़ो;
	u8 sfp_tx_fault;
	u16 vxlan_udp_port;
	u16 geneve_udp_port;
	u8 padding4[2];

	u32 speed;
	u32 partner_adv_speed;

	u32 capability_speed;

	/* Forced vlan */
	u16 pvid;
	u16 padding5;
पूर्ण;

काष्ठा qed_bulletin अणु
	dma_addr_t phys;
	काष्ठा qed_bulletin_content *p_virt;
	u32 size;
पूर्ण;

क्रमागत अणु
	CHANNEL_TLV_NONE,	/* ends tlv sequence */
	CHANNEL_TLV_ACQUIRE,
	CHANNEL_TLV_VPORT_START,
	CHANNEL_TLV_VPORT_UPDATE,
	CHANNEL_TLV_VPORT_TEARDOWN,
	CHANNEL_TLV_START_RXQ,
	CHANNEL_TLV_START_TXQ,
	CHANNEL_TLV_STOP_RXQS,
	CHANNEL_TLV_STOP_TXQS,
	CHANNEL_TLV_UPDATE_RXQ,
	CHANNEL_TLV_INT_CLEANUP,
	CHANNEL_TLV_CLOSE,
	CHANNEL_TLV_RELEASE,
	CHANNEL_TLV_LIST_END,
	CHANNEL_TLV_UCAST_FILTER,
	CHANNEL_TLV_VPORT_UPDATE_ACTIVATE,
	CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH,
	CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP,
	CHANNEL_TLV_VPORT_UPDATE_MCAST,
	CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM,
	CHANNEL_TLV_VPORT_UPDATE_RSS,
	CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN,
	CHANNEL_TLV_VPORT_UPDATE_SGE_TPA,
	CHANNEL_TLV_UPDATE_TUNN_PARAM,
	CHANNEL_TLV_COALESCE_UPDATE,
	CHANNEL_TLV_QID,
	CHANNEL_TLV_COALESCE_READ,
	CHANNEL_TLV_BULLETIN_UPDATE_MAC,
	CHANNEL_TLV_MAX,

	/* Required क्रम iterating over vport-update tlvs.
	 * Will अवरोध in हाल non-sequential vport-update tlvs.
	 */
	CHANNEL_TLV_VPORT_UPDATE_MAX = CHANNEL_TLV_VPORT_UPDATE_SGE_TPA + 1,
पूर्ण;

/* Default number of CIDs [total of both Rx and Tx] to be requested
 * by शेष, and maximum possible number.
 */
#घोषणा QED_ETH_VF_DEFAULT_NUM_CIDS (32)
#घोषणा QED_ETH_VF_MAX_NUM_CIDS (250)

/* This data is held in the qed_hwfn काष्ठाure क्रम VFs only. */
काष्ठा qed_vf_iov अणु
	जोड़ vfpf_tlvs *vf2pf_request;
	dma_addr_t vf2pf_request_phys;
	जोड़ pfvf_tlvs *pf2vf_reply;
	dma_addr_t pf2vf_reply_phys;

	/* Should be taken whenever the mailbox buffers are accessed */
	काष्ठा mutex mutex;
	u8 *offset;

	/* Bulletin Board */
	काष्ठा qed_bulletin bulletin;
	काष्ठा qed_bulletin_content bulletin_shaकरोw;

	/* we set aside a copy of the acquire response */
	काष्ठा pfvf_acquire_resp_tlv acquire_resp;

	/* In हाल PF originates prior to the fp-hsi version comparison,
	 * this has to be propagated as it affects the fastpath.
	 */
	bool b_pre_fp_hsi;

	/* Current day VFs are passing the SBs physical address on vport
	 * start, and as they lack an IGU mapping they need to store the
	 * addresses of previously रेजिस्टरed SBs.
	 * Even अगर we were to change configuration flow, due to backward
	 * compatibility [with older PFs] we'd still need to store these.
	 */
	काष्ठा qed_sb_info *sbs_info[PFVF_MAX_SBS_PER_VF];

	/* Determines whether VF utilizes करोorbells via limited रेजिस्टर
	 * bar or via the करोorbell bar.
	 */
	bool b_करोorbell_bar;
पूर्ण;

/**
 * @brief VF - Set Rx/Tx coalesce per VF's relative queue.
 *             Coalesce value '0' will omit the configuration.
 *
 * @param p_hwfn
 * @param rx_coal - coalesce value in micro second क्रम rx queue
 * @param tx_coal - coalesce value in micro second क्रम tx queue
 * @param p_cid   - queue cid
 *
 **/
पूर्णांक qed_vf_pf_set_coalesce(काष्ठा qed_hwfn *p_hwfn,
			   u16 rx_coal,
			   u16 tx_coal, काष्ठा qed_queue_cid *p_cid);

/**
 * @brief VF - Get coalesce per VF's relative queue.
 *
 * @param p_hwfn
 * @param p_coal - coalesce value in micro second क्रम VF queues.
 * @param p_cid  - queue cid
 *
 **/
पूर्णांक qed_vf_pf_get_coalesce(काष्ठा qed_hwfn *p_hwfn,
			   u16 *p_coal, काष्ठा qed_queue_cid *p_cid);

#अगर_घोषित CONFIG_QED_SRIOV
/**
 * @brief Read the VF bulletin and act on it अगर needed
 *
 * @param p_hwfn
 * @param p_change - qed fills 1 अगरf bulletin board has changed, 0 otherwise.
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_पढ़ो_bulletin(काष्ठा qed_hwfn *p_hwfn, u8 *p_change);

/**
 * @brief Get link paramters क्रम VF from qed
 *
 * @param p_hwfn
 * @param params - the link params काष्ठाure to be filled क्रम the VF
 */
व्योम qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_mcp_link_params *params);

/**
 * @brief Get link state क्रम VF from qed
 *
 * @param p_hwfn
 * @param link - the link state काष्ठाure to be filled क्रम the VF
 */
व्योम qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_mcp_link_state *link);

/**
 * @brief Get link capabilities क्रम VF from qed
 *
 * @param p_hwfn
 * @param p_link_caps - the link capabilities काष्ठाure to be filled क्रम the VF
 */
व्योम qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_mcp_link_capabilities *p_link_caps);

/**
 * @brief Get number of Rx queues allocated क्रम VF by qed
 *
 *  @param p_hwfn
 *  @param num_rxqs - allocated RX queues
 */
व्योम qed_vf_get_num_rxqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_rxqs);

/**
 * @brief Get number of Rx queues allocated क्रम VF by qed
 *
 *  @param p_hwfn
 *  @param num_txqs - allocated RX queues
 */
व्योम qed_vf_get_num_txqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_txqs);

/**
 * @brief Get number of available connections [both Rx and Tx] क्रम VF
 *
 * @param p_hwfn
 * @param num_cids - allocated number of connections
 */
व्योम qed_vf_get_num_cids(काष्ठा qed_hwfn *p_hwfn, u8 *num_cids);

/**
 * @brief Get port mac address क्रम VF
 *
 * @param p_hwfn
 * @param port_mac - destination location क्रम port mac
 */
व्योम qed_vf_get_port_mac(काष्ठा qed_hwfn *p_hwfn, u8 *port_mac);

/**
 * @brief Get number of VLAN filters allocated क्रम VF by qed
 *
 *  @param p_hwfn
 *  @param num_rxqs - allocated VLAN filters
 */
व्योम qed_vf_get_num_vlan_filters(काष्ठा qed_hwfn *p_hwfn,
				 u8 *num_vlan_filters);

/**
 * @brief Get number of MAC filters allocated क्रम VF by qed
 *
 *  @param p_hwfn
 *  @param num_rxqs - allocated MAC filters
 */
व्योम qed_vf_get_num_mac_filters(काष्ठा qed_hwfn *p_hwfn, u8 *num_mac_filters);

/**
 * @brief Check अगर VF can set a MAC address
 *
 * @param p_hwfn
 * @param mac
 *
 * @वापस bool
 */
bool qed_vf_check_mac(काष्ठा qed_hwfn *p_hwfn, u8 *mac);

/**
 * @brief Set firmware version inक्रमmation in dev_info from VFs acquire response tlv
 *
 * @param p_hwfn
 * @param fw_major
 * @param fw_minor
 * @param fw_rev
 * @param fw_eng
 */
व्योम qed_vf_get_fw_version(काष्ठा qed_hwfn *p_hwfn,
			   u16 *fw_major, u16 *fw_minor,
			   u16 *fw_rev, u16 *fw_eng);

/**
 * @brief hw preparation क्रम VF
 *      sends ACQUIRE message
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_vf_hw_prepare(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief VF - start the RX Queue by sending a message to the PF
 * @param p_hwfn
 * @param p_cid			- Only relative fields are relevant
 * @param bd_max_bytes          - maximum number of bytes per bd
 * @param bd_chain_phys_addr    - physical address of bd chain
 * @param cqe_pbl_addr          - physical address of pbl
 * @param cqe_pbl_size          - pbl size
 * @param pp_prod               - poपूर्णांकer to the producer to be
 *				  used in fastpath
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_vf_pf_rxq_start(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_queue_cid *p_cid,
			u16 bd_max_bytes,
			dma_addr_t bd_chain_phys_addr,
			dma_addr_t cqe_pbl_addr,
			u16 cqe_pbl_size, व्योम __iomem **pp_prod);

/**
 * @brief VF - start the TX queue by sending a message to the
 *        PF.
 *
 * @param p_hwfn
 * @param tx_queue_id           - zero based within the VF
 * @param sb                    - status block क्रम this queue
 * @param sb_index              - index within the status block
 * @param bd_chain_phys_addr    - physical address of tx chain
 * @param pp_करोorbell           - poपूर्णांकer to address to which to
 *                      ग_लिखो the करोorbell too..
 *
 * @वापस पूर्णांक
 */
पूर्णांक
qed_vf_pf_txq_start(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_queue_cid *p_cid,
		    dma_addr_t pbl_addr,
		    u16 pbl_size, व्योम __iomem **pp_करोorbell);

/**
 * @brief VF - stop the RX queue by sending a message to the PF
 *
 * @param p_hwfn
 * @param p_cid
 * @param cqe_completion
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_vf_pf_rxq_stop(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_queue_cid *p_cid, bool cqe_completion);

/**
 * @brief VF - stop the TX queue by sending a message to the PF
 *
 * @param p_hwfn
 * @param tx_qid
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_vf_pf_txq_stop(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_queue_cid *p_cid);

/**
 * @brief VF - send a vport update command
 *
 * @param p_hwfn
 * @param params
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_vf_pf_vport_update(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_sp_vport_update_params *p_params);

/**
 *
 * @brief VF - send a बंद message to PF
 *
 * @param p_hwfn
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_pf_reset(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief VF - मुक्त vf`s memories
 *
 * @param p_hwfn
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_pf_release(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_vf_get_igu_sb_id - Get the IGU SB ID क्रम a given
 *        sb_id. For VFs igu sbs करोn't have to be contiguous
 *
 * @param p_hwfn
 * @param sb_id
 *
 * @वापस INLINE u16
 */
u16 qed_vf_get_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 sb_id);

/**
 * @brief Stores [or हटाओs] a configured sb_info.
 *
 * @param p_hwfn
 * @param sb_id - zero-based SB index [क्रम fastpath]
 * @param sb_info - may be शून्य [during removal].
 */
व्योम qed_vf_set_sb_info(काष्ठा qed_hwfn *p_hwfn,
			u16 sb_id, काष्ठा qed_sb_info *p_sb);

/**
 * @brief qed_vf_pf_vport_start - perक्रमm vport start क्रम VF.
 *
 * @param p_hwfn
 * @param vport_id
 * @param mtu
 * @param inner_vlan_removal
 * @param tpa_mode
 * @param max_buffers_per_cqe,
 * @param only_untagged - शेष behavior regarding vlan acceptance
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_pf_vport_start(काष्ठा qed_hwfn *p_hwfn,
			  u8 vport_id,
			  u16 mtu,
			  u8 inner_vlan_removal,
			  क्रमागत qed_tpa_mode tpa_mode,
			  u8 max_buffers_per_cqe, u8 only_untagged);

/**
 * @brief qed_vf_pf_vport_stop - stop the VF's vport
 *
 * @param p_hwfn
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_pf_vport_stop(काष्ठा qed_hwfn *p_hwfn);

पूर्णांक qed_vf_pf_filter_ucast(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_filter_ucast *p_param);

व्योम qed_vf_pf_filter_mcast(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_filter_mcast *p_filter_cmd);

/**
 * @brief qed_vf_pf_पूर्णांक_cleanup - clean the SB of the VF
 *
 * @param p_hwfn
 *
 * @वापस क्रमागत _qed_status
 */
पूर्णांक qed_vf_pf_पूर्णांक_cleanup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief - वापस the link params in a given bulletin board
 *
 * @param p_hwfn
 * @param p_params - poपूर्णांकer to a काष्ठा to fill with link params
 * @param p_bulletin
 */
व्योम __qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_mcp_link_params *p_params,
			      काष्ठा qed_bulletin_content *p_bulletin);

/**
 * @brief - वापस the link state in a given bulletin board
 *
 * @param p_hwfn
 * @param p_link - poपूर्णांकer to a काष्ठा to fill with link state
 * @param p_bulletin
 */
व्योम __qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_mcp_link_state *p_link,
			     काष्ठा qed_bulletin_content *p_bulletin);

/**
 * @brief - वापस the link capabilities in a given bulletin board
 *
 * @param p_hwfn
 * @param p_link - poपूर्णांकer to a काष्ठा to fill with link capabilities
 * @param p_bulletin
 */
व्योम __qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_mcp_link_capabilities *p_link_caps,
			    काष्ठा qed_bulletin_content *p_bulletin);

व्योम qed_iov_vf_task(काष्ठा work_काष्ठा *work);
व्योम qed_vf_set_vf_start_tunn_update_param(काष्ठा qed_tunnel_info *p_tun);
पूर्णांक qed_vf_pf_tunnel_param_update(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_tunnel_info *p_tunn);

u32 qed_vf_hw_bar_size(काष्ठा qed_hwfn *p_hwfn, क्रमागत BAR_ID bar_id);
/**
 * @brief - Ask PF to update the MAC address in it's bulletin board
 *
 * @param p_mac - mac address to be updated in bulletin board
 */
पूर्णांक qed_vf_pf_bulletin_update_mac(काष्ठा qed_hwfn *p_hwfn, u8 *p_mac);

#अन्यथा
अटल अंतरभूत व्योम qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_mcp_link_params *params)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_mcp_link_state *link)
अणु
पूर्ण

अटल अंतरभूत व्योम
qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_mcp_link_capabilities *p_link_caps)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_num_rxqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_rxqs)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_num_txqs(काष्ठा qed_hwfn *p_hwfn, u8 *num_txqs)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_num_cids(काष्ठा qed_hwfn *p_hwfn, u8 *num_cids)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_port_mac(काष्ठा qed_hwfn *p_hwfn, u8 *port_mac)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_num_vlan_filters(काष्ठा qed_hwfn *p_hwfn,
					       u8 *num_vlan_filters)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_num_mac_filters(काष्ठा qed_hwfn *p_hwfn,
					      u8 *num_mac_filters)
अणु
पूर्ण

अटल अंतरभूत bool qed_vf_check_mac(काष्ठा qed_hwfn *p_hwfn, u8 *mac)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम qed_vf_get_fw_version(काष्ठा qed_hwfn *p_hwfn,
					 u16 *fw_major, u16 *fw_minor,
					 u16 *fw_rev, u16 *fw_eng)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_hw_prepare(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_rxq_start(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_queue_cid *p_cid,
				      u16 bd_max_bytes,
				      dma_addr_t bd_chain_phys_adr,
				      dma_addr_t cqe_pbl_addr,
				      u16 cqe_pbl_size, व्योम __iomem **pp_prod)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_txq_start(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_queue_cid *p_cid,
				      dma_addr_t pbl_addr,
				      u16 pbl_size, व्योम __iomem **pp_करोorbell)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_rxq_stop(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_queue_cid *p_cid,
				     bool cqe_completion)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_txq_stop(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_queue_cid *p_cid)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
qed_vf_pf_vport_update(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_sp_vport_update_params *p_params)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_reset(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_release(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत u16 qed_vf_get_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 sb_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qed_vf_set_sb_info(काष्ठा qed_hwfn *p_hwfn, u16 sb_id,
				      काष्ठा qed_sb_info *p_sb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_vport_start(काष्ठा qed_hwfn *p_hwfn,
					u8 vport_id,
					u16 mtu,
					u8 inner_vlan_removal,
					क्रमागत qed_tpa_mode tpa_mode,
					u8 max_buffers_per_cqe,
					u8 only_untagged)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_vport_stop(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_filter_ucast(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_filter_ucast *p_param)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम qed_vf_pf_filter_mcast(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_filter_mcast *p_filter_cmd)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_पूर्णांक_cleanup(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम __qed_vf_get_link_params(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_mcp_link_params
					    *p_params,
					    काष्ठा qed_bulletin_content
					    *p_bulletin)
अणु
पूर्ण

अटल अंतरभूत व्योम __qed_vf_get_link_state(काष्ठा qed_hwfn *p_hwfn,
					   काष्ठा qed_mcp_link_state *p_link,
					   काष्ठा qed_bulletin_content
					   *p_bulletin)
अणु
पूर्ण

अटल अंतरभूत व्योम
__qed_vf_get_link_caps(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_mcp_link_capabilities *p_link_caps,
		       काष्ठा qed_bulletin_content *p_bulletin)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_iov_vf_task(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

अटल अंतरभूत व्योम
qed_vf_set_vf_start_tunn_update_param(काष्ठा qed_tunnel_info *p_tun)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_tunnel_param_update(काष्ठा qed_hwfn *p_hwfn,
						काष्ठा qed_tunnel_info *p_tunn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qed_vf_pf_bulletin_update_mac(काष्ठा qed_hwfn *p_hwfn,
						u8 *p_mac)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत u32
qed_vf_hw_bar_size(काष्ठा qed_hwfn  *p_hwfn,
		   क्रमागत BAR_ID bar_id)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
