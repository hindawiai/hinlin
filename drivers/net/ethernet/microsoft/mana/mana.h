<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2021, Microsoft Corporation. */

#अगर_अघोषित _MANA_H
#घोषणा _MANA_H

#समावेश "gdma.h"
#समावेश "hw_channel.h"

/* Microsoft Azure Network Adapter (MANA)'s definitions
 *
 * Structures labeled with "HW DATA" are exchanged with the hardware. All of
 * them are naturally aligned and hence करोn't need __packed.
 */

/* MANA protocol version */
#घोषणा MANA_MAJOR_VERSION	0
#घोषणा MANA_MINOR_VERSION	1
#घोषणा MANA_MICRO_VERSION	1

प्रकार u64 mana_handle_t;
#घोषणा INVALID_MANA_HANDLE ((mana_handle_t)-1)

क्रमागत TRI_STATE अणु
	TRI_STATE_UNKNOWN = -1,
	TRI_STATE_FALSE = 0,
	TRI_STATE_TRUE = 1
पूर्ण;

/* Number of entries क्रम hardware indirection table must be in घातer of 2 */
#घोषणा MANA_INसूचीECT_TABLE_SIZE 64
#घोषणा MANA_INसूचीECT_TABLE_MASK (MANA_INसूचीECT_TABLE_SIZE - 1)

/* The Toeplitz hash key's length in bytes: should be multiple of 8 */
#घोषणा MANA_HASH_KEY_SIZE 40

#घोषणा COMP_ENTRY_SIZE 64

#घोषणा ADAPTER_MTU_SIZE 1500
#घोषणा MAX_FRAME_SIZE (ADAPTER_MTU_SIZE + 14)

#घोषणा RX_BUFFERS_PER_QUEUE 512

#घोषणा MAX_SEND_BUFFERS_PER_QUEUE 256

#घोषणा EQ_SIZE (8 * PAGE_SIZE)
#घोषणा LOG2_EQ_THROTTLE 3

#घोषणा MAX_PORTS_IN_MANA_DEV 16

काष्ठा mana_stats अणु
	u64 packets;
	u64 bytes;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा mana_txq अणु
	काष्ठा gdma_queue *gdma_sq;

	जोड़ अणु
		u32 gdma_txq_id;
		काष्ठा अणु
			u32 reserved1	: 10;
			u32 vsq_frame	: 14;
			u32 reserved2	: 8;
		पूर्ण;
	पूर्ण;

	u16 vp_offset;

	काष्ठा net_device *ndev;

	/* The SKBs are sent to the HW and we are रुकोing क्रम the CQEs. */
	काष्ठा sk_buff_head pending_skbs;
	काष्ठा netdev_queue *net_txq;

	atomic_t pending_sends;

	काष्ठा mana_stats stats;
पूर्ण;

/* skb data and frags dma mappings */
काष्ठा mana_skb_head अणु
	dma_addr_t dma_handle[MAX_SKB_FRAGS + 1];

	u32 size[MAX_SKB_FRAGS + 1];
पूर्ण;

#घोषणा MANA_HEADROOM माप(काष्ठा mana_skb_head)

क्रमागत mana_tx_pkt_क्रमmat अणु
	MANA_SHORT_PKT_FMT	= 0,
	MANA_LONG_PKT_FMT	= 1,
पूर्ण;

काष्ठा mana_tx_लघु_oob अणु
	u32 pkt_fmt		: 2;
	u32 is_outer_ipv4	: 1;
	u32 is_outer_ipv6	: 1;
	u32 comp_iphdr_csum	: 1;
	u32 comp_tcp_csum	: 1;
	u32 comp_udp_csum	: 1;
	u32 supress_txcqe_gen	: 1;
	u32 vcq_num		: 24;

	u32 trans_off		: 10; /* Transport header offset */
	u32 vsq_frame		: 14;
	u32 लघु_vp_offset	: 8;
पूर्ण; /* HW DATA */

काष्ठा mana_tx_दीर्घ_oob अणु
	u32 is_encap		: 1;
	u32 inner_is_ipv6	: 1;
	u32 inner_tcp_opt	: 1;
	u32 inject_vlan_pri_tag : 1;
	u32 reserved1		: 12;
	u32 pcp			: 3;  /* 802.1Q */
	u32 dei			: 1;  /* 802.1Q */
	u32 vlan_id		: 12; /* 802.1Q */

	u32 inner_frame_offset	: 10;
	u32 inner_ip_rel_offset : 6;
	u32 दीर्घ_vp_offset	: 12;
	u32 reserved2		: 4;

	u32 reserved3;
	u32 reserved4;
पूर्ण; /* HW DATA */

काष्ठा mana_tx_oob अणु
	काष्ठा mana_tx_लघु_oob s_oob;
	काष्ठा mana_tx_दीर्घ_oob l_oob;
पूर्ण; /* HW DATA */

क्रमागत mana_cq_type अणु
	MANA_CQ_TYPE_RX,
	MANA_CQ_TYPE_TX,
पूर्ण;

क्रमागत mana_cqe_type अणु
	CQE_INVALID			= 0,
	CQE_RX_OKAY			= 1,
	CQE_RX_COALESCED_4		= 2,
	CQE_RX_OBJECT_FENCE		= 3,
	CQE_RX_TRUNCATED		= 4,

	CQE_TX_OKAY			= 32,
	CQE_TX_SA_DROP			= 33,
	CQE_TX_MTU_DROP			= 34,
	CQE_TX_INVALID_OOB		= 35,
	CQE_TX_INVALID_ETH_TYPE		= 36,
	CQE_TX_HDR_PROCESSING_ERROR	= 37,
	CQE_TX_VF_DISABLED		= 38,
	CQE_TX_VPORT_IDX_OUT_OF_RANGE	= 39,
	CQE_TX_VPORT_DISABLED		= 40,
	CQE_TX_VLAN_TAGGING_VIOLATION	= 41,
पूर्ण;

#घोषणा MANA_CQE_COMPLETION 1

काष्ठा mana_cqe_header अणु
	u32 cqe_type	: 6;
	u32 client_type	: 2;
	u32 venकरोr_err	: 24;
पूर्ण; /* HW DATA */

/* NDIS HASH Types */
#घोषणा NDIS_HASH_IPV4		BIT(0)
#घोषणा NDIS_HASH_TCP_IPV4	BIT(1)
#घोषणा NDIS_HASH_UDP_IPV4	BIT(2)
#घोषणा NDIS_HASH_IPV6		BIT(3)
#घोषणा NDIS_HASH_TCP_IPV6	BIT(4)
#घोषणा NDIS_HASH_UDP_IPV6	BIT(5)
#घोषणा NDIS_HASH_IPV6_EX	BIT(6)
#घोषणा NDIS_HASH_TCP_IPV6_EX	BIT(7)
#घोषणा NDIS_HASH_UDP_IPV6_EX	BIT(8)

#घोषणा MANA_HASH_L3 (NDIS_HASH_IPV4 | NDIS_HASH_IPV6 | NDIS_HASH_IPV6_EX)
#घोषणा MANA_HASH_L4                                                         \
	(NDIS_HASH_TCP_IPV4 | NDIS_HASH_UDP_IPV4 | NDIS_HASH_TCP_IPV6 |      \
	 NDIS_HASH_UDP_IPV6 | NDIS_HASH_TCP_IPV6_EX | NDIS_HASH_UDP_IPV6_EX)

काष्ठा mana_rxcomp_perpkt_info अणु
	u32 pkt_len	: 16;
	u32 reserved1	: 16;
	u32 reserved2;
	u32 pkt_hash;
पूर्ण; /* HW DATA */

#घोषणा MANA_RXCOMP_OOB_NUM_PPI 4

/* Receive completion OOB */
काष्ठा mana_rxcomp_oob अणु
	काष्ठा mana_cqe_header cqe_hdr;

	u32 rx_vlan_id			: 12;
	u32 rx_vlantag_present		: 1;
	u32 rx_outer_iphdr_csum_succeed	: 1;
	u32 rx_outer_iphdr_csum_fail	: 1;
	u32 reserved1			: 1;
	u32 rx_hashtype			: 9;
	u32 rx_iphdr_csum_succeed	: 1;
	u32 rx_iphdr_csum_fail		: 1;
	u32 rx_tcp_csum_succeed		: 1;
	u32 rx_tcp_csum_fail		: 1;
	u32 rx_udp_csum_succeed		: 1;
	u32 rx_udp_csum_fail		: 1;
	u32 reserved2			: 1;

	काष्ठा mana_rxcomp_perpkt_info ppi[MANA_RXCOMP_OOB_NUM_PPI];

	u32 rx_wqe_offset;
पूर्ण; /* HW DATA */

काष्ठा mana_tx_comp_oob अणु
	काष्ठा mana_cqe_header cqe_hdr;

	u32 tx_data_offset;

	u32 tx_sgl_offset	: 5;
	u32 tx_wqe_offset	: 27;

	u32 reserved[12];
पूर्ण; /* HW DATA */

काष्ठा mana_rxq;

काष्ठा mana_cq अणु
	काष्ठा gdma_queue *gdma_cq;

	/* Cache the CQ id (used to verअगरy अगर each CQE comes to the right CQ. */
	u32 gdma_id;

	/* Type of the CQ: TX or RX */
	क्रमागत mana_cq_type type;

	/* Poपूर्णांकer to the mana_rxq that is pushing RX CQEs to the queue.
	 * Only and must be non-शून्य अगर type is MANA_CQ_TYPE_RX.
	 */
	काष्ठा mana_rxq *rxq;

	/* Poपूर्णांकer to the mana_txq that is pushing TX CQEs to the queue.
	 * Only and must be non-शून्य अगर type is MANA_CQ_TYPE_TX.
	 */
	काष्ठा mana_txq *txq;

	/* Poपूर्णांकer to a buffer which the CQ handler can copy the CQE's पूर्णांकo. */
	काष्ठा gdma_comp *gdma_comp_buf;
पूर्ण;

#घोषणा GDMA_MAX_RQE_SGES 15

काष्ठा mana_recv_buf_oob अणु
	/* A valid GDMA work request representing the data buffer. */
	काष्ठा gdma_wqe_request wqe_req;

	व्योम *buf_va;
	dma_addr_t buf_dma_addr;

	/* SGL of the buffer going to be sent has part of the work request. */
	u32 num_sge;
	काष्ठा gdma_sge sgl[GDMA_MAX_RQE_SGES];

	/* Required to store the result of mana_gd_post_work_request.
	 * gdma_posted_wqe_info.wqe_size_in_bu is required क्रम progressing the
	 * work queue when the WQE is consumed.
	 */
	काष्ठा gdma_posted_wqe_info wqe_inf;
पूर्ण;

काष्ठा mana_rxq अणु
	काष्ठा gdma_queue *gdma_rq;
	/* Cache the gdma receive queue id */
	u32 gdma_id;

	/* Index of RQ in the vPort, not gdma receive queue id */
	u32 rxq_idx;

	u32 datasize;

	mana_handle_t rxobj;

	काष्ठा mana_cq rx_cq;

	काष्ठा net_device *ndev;

	/* Total number of receive buffers to be allocated */
	u32 num_rx_buf;

	u32 buf_index;

	काष्ठा mana_stats stats;

	/* MUST BE THE LAST MEMBER:
	 * Each receive buffer has an associated mana_recv_buf_oob.
	 */
	काष्ठा mana_recv_buf_oob rx_oobs[];
पूर्ण;

काष्ठा mana_tx_qp अणु
	काष्ठा mana_txq txq;

	काष्ठा mana_cq tx_cq;

	mana_handle_t tx_object;
पूर्ण;

काष्ठा mana_ethtool_stats अणु
	u64 stop_queue;
	u64 wake_queue;
पूर्ण;

काष्ठा mana_context अणु
	काष्ठा gdma_dev *gdma_dev;

	u16 num_ports;

	काष्ठा net_device *ports[MAX_PORTS_IN_MANA_DEV];
पूर्ण;

काष्ठा mana_port_context अणु
	काष्ठा mana_context *ac;
	काष्ठा net_device *ndev;

	u8 mac_addr[ETH_ALEN];

	काष्ठा mana_eq *eqs;

	क्रमागत TRI_STATE rss_state;

	mana_handle_t शेष_rxobj;
	bool tx_लघुक्रमm_allowed;
	u16 tx_vp_offset;

	काष्ठा mana_tx_qp *tx_qp;

	/* Indirection Table क्रम RX & TX. The values are queue indexes */
	u32 indir_table[MANA_INसूचीECT_TABLE_SIZE];

	/* Indirection table containing RxObject Handles */
	mana_handle_t rxobj_table[MANA_INसूचीECT_TABLE_SIZE];

	/*  Hash key used by the NIC */
	u8 hashkey[MANA_HASH_KEY_SIZE];

	/* This poपूर्णांकs to an array of num_queues of RQ poपूर्णांकers. */
	काष्ठा mana_rxq **rxqs;

	/* Create num_queues EQs, SQs, SQ-CQs, RQs and RQ-CQs, respectively. */
	अचिन्हित पूर्णांक max_queues;
	अचिन्हित पूर्णांक num_queues;

	mana_handle_t port_handle;

	u16 port_idx;

	bool port_is_up;
	bool port_st_save; /* Saved port state */

	काष्ठा mana_ethtool_stats eth_stats;
पूर्ण;

पूर्णांक mana_config_rss(काष्ठा mana_port_context *ac, क्रमागत TRI_STATE rx,
		    bool update_hash, bool update_tab);

पूर्णांक mana_alloc_queues(काष्ठा net_device *ndev);
पूर्णांक mana_attach(काष्ठा net_device *ndev);
पूर्णांक mana_detach(काष्ठा net_device *ndev, bool from_बंद);

पूर्णांक mana_probe(काष्ठा gdma_dev *gd);
व्योम mana_हटाओ(काष्ठा gdma_dev *gd);

बाह्य स्थिर काष्ठा ethtool_ops mana_ethtool_ops;

काष्ठा mana_obj_spec अणु
	u32 queue_index;
	u64 gdma_region;
	u32 queue_size;
	u32 attached_eq;
	u32 modr_ctx_id;
पूर्ण;

क्रमागत mana_command_code अणु
	MANA_QUERY_DEV_CONFIG	= 0x20001,
	MANA_QUERY_GF_STAT	= 0x20002,
	MANA_CONFIG_VPORT_TX	= 0x20003,
	MANA_CREATE_WQ_OBJ	= 0x20004,
	MANA_DESTROY_WQ_OBJ	= 0x20005,
	MANA_FENCE_RQ		= 0x20006,
	MANA_CONFIG_VPORT_RX	= 0x20007,
	MANA_QUERY_VPORT_CONFIG	= 0x20008,
पूर्ण;

/* Query Device Configuration */
काष्ठा mana_query_device_cfg_req अणु
	काष्ठा gdma_req_hdr hdr;

	/* Driver Capability flags */
	u64 drv_cap_flags1;
	u64 drv_cap_flags2;
	u64 drv_cap_flags3;
	u64 drv_cap_flags4;

	u32 proto_major_ver;
	u32 proto_minor_ver;
	u32 proto_micro_ver;

	u32 reserved;
पूर्ण; /* HW DATA */

काष्ठा mana_query_device_cfg_resp अणु
	काष्ठा gdma_resp_hdr hdr;

	u64 pf_cap_flags1;
	u64 pf_cap_flags2;
	u64 pf_cap_flags3;
	u64 pf_cap_flags4;

	u16 max_num_vports;
	u16 reserved;
	u32 max_num_eqs;
पूर्ण; /* HW DATA */

/* Query vPort Configuration */
काष्ठा mana_query_vport_cfg_req अणु
	काष्ठा gdma_req_hdr hdr;
	u32 vport_index;
पूर्ण; /* HW DATA */

काष्ठा mana_query_vport_cfg_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 max_num_sq;
	u32 max_num_rq;
	u32 num_indirection_ent;
	u32 reserved1;
	u8 mac_addr[6];
	u8 reserved2[2];
	mana_handle_t vport;
पूर्ण; /* HW DATA */

/* Configure vPort */
काष्ठा mana_config_vport_req अणु
	काष्ठा gdma_req_hdr hdr;
	mana_handle_t vport;
	u32 pdid;
	u32 करोorbell_pageid;
पूर्ण; /* HW DATA */

काष्ठा mana_config_vport_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u16 tx_vport_offset;
	u8 लघु_क्रमm_allowed;
	u8 reserved;
पूर्ण; /* HW DATA */

/* Create WQ Object */
काष्ठा mana_create_wqobj_req अणु
	काष्ठा gdma_req_hdr hdr;
	mana_handle_t vport;
	u32 wq_type;
	u32 reserved;
	u64 wq_gdma_region;
	u64 cq_gdma_region;
	u32 wq_size;
	u32 cq_size;
	u32 cq_moderation_ctx_id;
	u32 cq_parent_qid;
पूर्ण; /* HW DATA */

काष्ठा mana_create_wqobj_resp अणु
	काष्ठा gdma_resp_hdr hdr;
	u32 wq_id;
	u32 cq_id;
	mana_handle_t wq_obj;
पूर्ण; /* HW DATA */

/* Destroy WQ Object */
काष्ठा mana_destroy_wqobj_req अणु
	काष्ठा gdma_req_hdr hdr;
	u32 wq_type;
	u32 reserved;
	mana_handle_t wq_obj_handle;
पूर्ण; /* HW DATA */

काष्ठा mana_destroy_wqobj_resp अणु
	काष्ठा gdma_resp_hdr hdr;
पूर्ण; /* HW DATA */

/* Fence RQ */
काष्ठा mana_fence_rq_req अणु
	काष्ठा gdma_req_hdr hdr;
	mana_handle_t wq_obj_handle;
पूर्ण; /* HW DATA */

काष्ठा mana_fence_rq_resp अणु
	काष्ठा gdma_resp_hdr hdr;
पूर्ण; /* HW DATA */

/* Configure vPort Rx Steering */
काष्ठा mana_cfg_rx_steer_req अणु
	काष्ठा gdma_req_hdr hdr;
	mana_handle_t vport;
	u16 num_indir_entries;
	u16 indir_tab_offset;
	u32 rx_enable;
	u32 rss_enable;
	u8 update_शेष_rxobj;
	u8 update_hashkey;
	u8 update_indir_tab;
	u8 reserved;
	mana_handle_t शेष_rxobj;
	u8 hashkey[MANA_HASH_KEY_SIZE];
पूर्ण; /* HW DATA */

काष्ठा mana_cfg_rx_steer_resp अणु
	काष्ठा gdma_resp_hdr hdr;
पूर्ण; /* HW DATA */

#घोषणा MANA_MAX_NUM_QUEUES 16

#घोषणा MANA_SHORT_VPORT_OFFSET_MAX ((1U << 8) - 1)

काष्ठा mana_tx_package अणु
	काष्ठा gdma_wqe_request wqe_req;
	काष्ठा gdma_sge sgl_array[5];
	काष्ठा gdma_sge *sgl_ptr;

	काष्ठा mana_tx_oob tx_oob;

	काष्ठा gdma_posted_wqe_info wqe_info;
पूर्ण;

#पूर्ण_अगर /* _MANA_H */
