<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#अगर_अघोषित __BNA_TYPES_H__
#घोषणा __BNA_TYPES_H__

#समावेश "cna.h"
#समावेश "bna_hw_defs.h"
#समावेश "bfa_cee.h"
#समावेश "bfa_msgq.h"

/* Forward declarations */

काष्ठा bna_mcam_handle;
काष्ठा bna_txq;
काष्ठा bna_tx;
काष्ठा bna_rxq;
काष्ठा bna_cq;
काष्ठा bna_rx;
काष्ठा bna_rxf;
काष्ठा bna_enet;
काष्ठा bna;
काष्ठा bnad;

/* Enums, primitive data types */

क्रमागत bna_status अणु
	BNA_STATUS_T_DISABLED	= 0,
	BNA_STATUS_T_ENABLED	= 1
पूर्ण;

क्रमागत bna_cleanup_type अणु
	BNA_HARD_CLEANUP	= 0,
	BNA_SOFT_CLEANUP	= 1
पूर्ण;

क्रमागत bna_cb_status अणु
	BNA_CB_SUCCESS		= 0,
	BNA_CB_FAIL		= 1,
	BNA_CB_INTERRUPT	= 2,
	BNA_CB_BUSY		= 3,
	BNA_CB_INVALID_MAC	= 4,
	BNA_CB_MCAST_LIST_FULL	= 5,
	BNA_CB_UCAST_CAM_FULL	= 6,
	BNA_CB_WAITING		= 7,
	BNA_CB_NOT_EXEC		= 8
पूर्ण;

क्रमागत bna_res_type अणु
	BNA_RES_T_MEM		= 1,
	BNA_RES_T_INTR		= 2
पूर्ण;

क्रमागत bna_mem_type अणु
	BNA_MEM_T_KVA		= 1,
	BNA_MEM_T_DMA		= 2
पूर्ण;

क्रमागत bna_पूर्णांकr_type अणु
	BNA_INTR_T_INTX		= 1,
	BNA_INTR_T_MSIX		= 2
पूर्ण;

क्रमागत bna_res_req_type अणु
	BNA_RES_MEM_T_COM		= 0,
	BNA_RES_MEM_T_ATTR		= 1,
	BNA_RES_MEM_T_FWTRC		= 2,
	BNA_RES_MEM_T_STATS		= 3,
	BNA_RES_T_MAX
पूर्ण;

क्रमागत bna_mod_res_req_type अणु
	BNA_MOD_RES_MEM_T_TX_ARRAY	= 0,
	BNA_MOD_RES_MEM_T_TXQ_ARRAY	= 1,
	BNA_MOD_RES_MEM_T_RX_ARRAY	= 2,
	BNA_MOD_RES_MEM_T_RXP_ARRAY	= 3,
	BNA_MOD_RES_MEM_T_RXQ_ARRAY	= 4,
	BNA_MOD_RES_MEM_T_UCMAC_ARRAY	= 5,
	BNA_MOD_RES_MEM_T_MCMAC_ARRAY	= 6,
	BNA_MOD_RES_MEM_T_MCHANDLE_ARRAY = 7,
	BNA_MOD_RES_T_MAX
पूर्ण;

क्रमागत bna_tx_res_req_type अणु
	BNA_TX_RES_MEM_T_TCB	= 0,
	BNA_TX_RES_MEM_T_UNMAPQ	= 1,
	BNA_TX_RES_MEM_T_QPT	= 2,
	BNA_TX_RES_MEM_T_SWQPT	= 3,
	BNA_TX_RES_MEM_T_PAGE	= 4,
	BNA_TX_RES_MEM_T_IBIDX	= 5,
	BNA_TX_RES_INTR_T_TXCMPL = 6,
	BNA_TX_RES_T_MAX,
पूर्ण;

क्रमागत bna_rx_mem_type अणु
	BNA_RX_RES_MEM_T_CCB		= 0,	/* CQ context */
	BNA_RX_RES_MEM_T_RCB		= 1,	/* CQ context */
	BNA_RX_RES_MEM_T_UNMAPHQ	= 2,
	BNA_RX_RES_MEM_T_UNMAPDQ	= 3,
	BNA_RX_RES_MEM_T_CQPT		= 4,
	BNA_RX_RES_MEM_T_CSWQPT		= 5,
	BNA_RX_RES_MEM_T_CQPT_PAGE	= 6,
	BNA_RX_RES_MEM_T_HQPT		= 7,
	BNA_RX_RES_MEM_T_DQPT		= 8,
	BNA_RX_RES_MEM_T_HSWQPT		= 9,
	BNA_RX_RES_MEM_T_DSWQPT		= 10,
	BNA_RX_RES_MEM_T_DPAGE		= 11,
	BNA_RX_RES_MEM_T_HPAGE		= 12,
	BNA_RX_RES_MEM_T_IBIDX		= 13,
	BNA_RX_RES_MEM_T_RIT		= 14,
	BNA_RX_RES_T_INTR		= 15,
	BNA_RX_RES_T_MAX		= 16
पूर्ण;

क्रमागत bna_tx_type अणु
	BNA_TX_T_REGULAR	= 0,
	BNA_TX_T_LOOPBACK	= 1,
पूर्ण;

क्रमागत bna_tx_flags अणु
	BNA_TX_F_ENET_STARTED	= 1,
	BNA_TX_F_ENABLED	= 2,
	BNA_TX_F_BW_UPDATED	= 8,
पूर्ण;

क्रमागत bna_tx_mod_flags अणु
	BNA_TX_MOD_F_ENET_STARTED	= 1,
	BNA_TX_MOD_F_ENET_LOOPBACK	= 2,
पूर्ण;

क्रमागत bna_rx_type अणु
	BNA_RX_T_REGULAR	= 0,
	BNA_RX_T_LOOPBACK	= 1,
पूर्ण;

क्रमागत bna_rxp_type अणु
	BNA_RXP_SINGLE		= 1,
	BNA_RXP_SLR		= 2,
	BNA_RXP_HDS		= 3
पूर्ण;

क्रमागत bna_rxmode अणु
	BNA_RXMODE_PROMISC	= 1,
	BNA_RXMODE_DEFAULT	= 2,
	BNA_RXMODE_ALLMULTI	= 4
पूर्ण;

क्रमागत bna_rx_event अणु
	RX_E_START			= 1,
	RX_E_STOP			= 2,
	RX_E_FAIL			= 3,
	RX_E_STARTED			= 4,
	RX_E_STOPPED			= 5,
	RX_E_RXF_STARTED		= 6,
	RX_E_RXF_STOPPED		= 7,
	RX_E_CLEANUP_DONE		= 8,
पूर्ण;

क्रमागत bna_rx_flags अणु
	BNA_RX_F_ENET_STARTED	= 1,
	BNA_RX_F_ENABLED	= 2,
पूर्ण;

क्रमागत bna_rx_mod_flags अणु
	BNA_RX_MOD_F_ENET_STARTED	= 1,
	BNA_RX_MOD_F_ENET_LOOPBACK	= 2,
पूर्ण;

क्रमागत bna_rxf_event अणु
	RXF_E_START			= 1,
	RXF_E_STOP			= 2,
	RXF_E_FAIL			= 3,
	RXF_E_CONFIG			= 4,
	RXF_E_FW_RESP			= 7,
पूर्ण;

क्रमागत bna_enet_type अणु
	BNA_ENET_T_REGULAR		= 0,
	BNA_ENET_T_LOOPBACK_INTERNAL	= 1,
	BNA_ENET_T_LOOPBACK_EXTERNAL	= 2,
पूर्ण;

क्रमागत bna_link_status अणु
	BNA_LINK_DOWN		= 0,
	BNA_LINK_UP		= 1,
	BNA_CEE_UP		= 2
पूर्ण;

क्रमागत bna_ethport_flags अणु
	BNA_ETHPORT_F_ADMIN_UP		= 1,
	BNA_ETHPORT_F_PORT_ENABLED	= 2,
	BNA_ETHPORT_F_RX_STARTED	= 4,
पूर्ण;

क्रमागत bna_enet_flags अणु
	BNA_ENET_F_IOCETH_READY		= 1,
	BNA_ENET_F_ENABLED		= 2,
	BNA_ENET_F_PAUSE_CHANGED	= 4,
	BNA_ENET_F_MTU_CHANGED		= 8
पूर्ण;

क्रमागत bna_rss_flags अणु
	BNA_RSS_F_RIT_PENDING		= 1,
	BNA_RSS_F_CFG_PENDING		= 2,
	BNA_RSS_F_STATUS_PENDING	= 4,
पूर्ण;

क्रमागत bna_mod_flags अणु
	BNA_MOD_F_INIT_DONE		= 1,
पूर्ण;

क्रमागत bna_pkt_rates अणु
	BNA_PKT_RATE_10K		= 10000,
	BNA_PKT_RATE_20K		= 20000,
	BNA_PKT_RATE_30K		= 30000,
	BNA_PKT_RATE_40K		= 40000,
	BNA_PKT_RATE_50K		= 50000,
	BNA_PKT_RATE_60K		= 60000,
	BNA_PKT_RATE_70K		= 70000,
	BNA_PKT_RATE_80K		= 80000,
पूर्ण;

क्रमागत bna_dim_load_types अणु
	BNA_LOAD_T_HIGH_4		= 0, /* 80K <= r */
	BNA_LOAD_T_HIGH_3		= 1, /* 60K <= r < 80K */
	BNA_LOAD_T_HIGH_2		= 2, /* 50K <= r < 60K */
	BNA_LOAD_T_HIGH_1		= 3, /* 40K <= r < 50K */
	BNA_LOAD_T_LOW_1		= 4, /* 30K <= r < 40K */
	BNA_LOAD_T_LOW_2		= 5, /* 20K <= r < 30K */
	BNA_LOAD_T_LOW_3		= 6, /* 10K <= r < 20K */
	BNA_LOAD_T_LOW_4		= 7, /* r < 10K */
	BNA_LOAD_T_MAX			= 8
पूर्ण;

क्रमागत bna_dim_bias_types अणु
	BNA_BIAS_T_SMALL		= 0, /* small pkts > (large pkts * 2) */
	BNA_BIAS_T_LARGE		= 1, /* Not BNA_BIAS_T_SMALL */
	BNA_BIAS_T_MAX			= 2
पूर्ण;

#घोषणा BNA_MAX_NAME_SIZE	64
काष्ठा bna_ident अणु
	पूर्णांक			id;
	अक्षर			name[BNA_MAX_NAME_SIZE];
पूर्ण;

काष्ठा bna_mac अणु
	/* This should be the first one */
	काष्ठा list_head			qe;
	u8			addr[ETH_ALEN];
	काष्ठा bna_mcam_handle *handle;
पूर्ण;

काष्ठा bna_mem_descr अणु
	u32		len;
	व्योम		*kva;
	काष्ठा bna_dma_addr dma;
पूर्ण;

काष्ठा bna_mem_info अणु
	क्रमागत bna_mem_type mem_type;
	u32		len;
	u32		num;
	u32		align_sz; /* 0/1 = no alignment */
	काष्ठा bna_mem_descr *mdl;
	व्योम			*cookie; /* For bnad to unmap dma later */
पूर्ण;

काष्ठा bna_पूर्णांकr_descr अणु
	पूर्णांक			vector;
पूर्ण;

काष्ठा bna_पूर्णांकr_info अणु
	क्रमागत bna_पूर्णांकr_type पूर्णांकr_type;
	पूर्णांक			num;
	काष्ठा bna_पूर्णांकr_descr *idl;
पूर्ण;

जोड़ bna_res_u अणु
	काष्ठा bna_mem_info mem_info;
	काष्ठा bna_पूर्णांकr_info पूर्णांकr_info;
पूर्ण;

काष्ठा bna_res_info अणु
	क्रमागत bna_res_type res_type;
	जोड़ bna_res_u		res_u;
पूर्ण;

/* HW QPT */
काष्ठा bna_qpt अणु
	काष्ठा bna_dma_addr hw_qpt_ptr;
	व्योम		*kv_qpt_ptr;
	u32		page_count;
	u32		page_size;
पूर्ण;

काष्ठा bna_attr अणु
	bool			fw_query_complete;
	पूर्णांक			num_txq;
	पूर्णांक			num_rxp;
	पूर्णांक			num_ucmac;
	पूर्णांक			num_mcmac;
	पूर्णांक			max_rit_size;
पूर्ण;

/* IOCEth */

काष्ठा bna_ioceth अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa_ioc ioc;

	काष्ठा bna_attr attr;
	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	काष्ठा bfi_enet_attr_req attr_req;

	व्योम (*stop_cbfn)(काष्ठा bnad *bnad);
	काष्ठा bnad *stop_cbarg;

	काष्ठा bna *bna;
पूर्ण;

/* Enet */

/* Pause configuration */
काष्ठा bna_छोड़ो_config अणु
	क्रमागत bna_status tx_छोड़ो;
	क्रमागत bna_status rx_छोड़ो;
पूर्ण;

काष्ठा bna_enet अणु
	bfa_fsm_t		fsm;
	क्रमागत bna_enet_flags flags;

	क्रमागत bna_enet_type type;

	काष्ठा bna_छोड़ो_config छोड़ो_config;
	पूर्णांक			mtu;

	/* Callback क्रम bna_enet_disable(), enet_stop() */
	व्योम (*stop_cbfn)(व्योम *);
	व्योम			*stop_cbarg;

	/* Callback क्रम bna_enet_mtu_set() */
	व्योम (*mtu_cbfn)(काष्ठा bnad *);

	काष्ठा bfa_wc		chld_stop_wc;

	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	काष्ठा bfi_enet_set_छोड़ो_req छोड़ो_req;

	काष्ठा bna *bna;
पूर्ण;

/* Ethport */

काष्ठा bna_ethport अणु
	bfa_fsm_t		fsm;
	क्रमागत bna_ethport_flags flags;

	क्रमागत bna_link_status link_status;

	पूर्णांक			rx_started_count;

	व्योम (*stop_cbfn)(काष्ठा bna_enet *);

	व्योम (*adminup_cbfn)(काष्ठा bnad *, क्रमागत bna_cb_status);

	व्योम (*link_cbfn)(काष्ठा bnad *, क्रमागत bna_link_status);

	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	जोड़ अणु
		काष्ठा bfi_enet_enable_req admin_req;
		काष्ठा bfi_enet_diag_lb_req lpbk_req;
	पूर्ण bfi_enet_cmd;

	काष्ठा bna *bna;
पूर्ण;

/* Interrupt Block */

/* Doorbell काष्ठाure */
काष्ठा bna_ib_dbell अणु
	व्योम __iomem   *करोorbell_addr;
	u32		करोorbell_ack;
पूर्ण;

/* IB काष्ठाure */
काष्ठा bna_ib अणु
	काष्ठा bna_dma_addr ib_seg_host_addr;
	व्योम		*ib_seg_host_addr_kva;

	काष्ठा bna_ib_dbell करोor_bell;

	क्रमागत bna_पूर्णांकr_type	पूर्णांकr_type;
	पूर्णांक			पूर्णांकr_vector;

	u8			coalescing_समयo;    /* Unit is 5usec. */

	पूर्णांक			पूर्णांकerpkt_count;
	पूर्णांक			पूर्णांकerpkt_समयo;
पूर्ण;

/* Tx object */

/* Tx datapath control काष्ठाure */
#घोषणा BNA_Q_NAME_SIZE		16
काष्ठा bna_tcb अणु
	/* Fast path */
	व्योम			**sw_qpt;
	व्योम			*sw_q;
	व्योम			*unmap_q;
	u32		producer_index;
	u32		consumer_index;
	अस्थिर u32	*hw_consumer_index;
	u32		q_depth;
	व्योम __iomem   *q_dbell;
	काष्ठा bna_ib_dbell *i_dbell;
	/* Control path */
	काष्ठा bna_txq *txq;
	काष्ठा bnad *bnad;
	व्योम			*priv; /* BNAD's cookie */
	क्रमागत bna_पूर्णांकr_type पूर्णांकr_type;
	पूर्णांक			पूर्णांकr_vector;
	u8			priority; /* Current priority */
	अचिन्हित दीर्घ		flags; /* Used by bnad as required */
	पूर्णांक			id;
	अक्षर			name[BNA_Q_NAME_SIZE];
पूर्ण;

/* TxQ QPT and configuration */
काष्ठा bna_txq अणु
	/* This should be the first one */
	काष्ठा list_head			qe;

	u8			priority;

	काष्ठा bna_qpt qpt;
	काष्ठा bna_tcb *tcb;
	काष्ठा bna_ib ib;

	काष्ठा bna_tx *tx;

	पूर्णांक			hw_id;

	u64		tx_packets;
	u64		tx_bytes;
पूर्ण;

/* Tx object */
काष्ठा bna_tx अणु
	/* This should be the first one */
	काष्ठा list_head			qe;
	पूर्णांक			rid;
	पूर्णांक			hw_id;

	bfa_fsm_t		fsm;
	क्रमागत bna_tx_flags flags;

	क्रमागत bna_tx_type type;
	पूर्णांक			num_txq;

	काष्ठा list_head			txq_q;
	u16			txf_vlan_id;

	/* Tx event handlers */
	व्योम (*tcb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_tcb *);
	व्योम (*tcb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_tcb *);
	व्योम (*tx_stall_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);
	व्योम (*tx_resume_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);
	व्योम (*tx_cleanup_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);

	/* callback क्रम bna_tx_disable(), bna_tx_stop() */
	व्योम (*stop_cbfn)(व्योम *arg, काष्ठा bna_tx *tx);
	व्योम			*stop_cbarg;

	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	जोड़ अणु
		काष्ठा bfi_enet_tx_cfg_req	cfg_req;
		काष्ठा bfi_enet_req		req;
		काष्ठा bfi_enet_tx_cfg_rsp	cfg_rsp;
	पूर्ण bfi_enet_cmd;

	काष्ठा bna *bna;
	व्योम			*priv;	/* bnad's cookie */
पूर्ण;

/* Tx object configuration used during creation */
काष्ठा bna_tx_config अणु
	पूर्णांक			num_txq;
	पूर्णांक			txq_depth;
	पूर्णांक			coalescing_समयo;
	क्रमागत bna_tx_type tx_type;
पूर्ण;

काष्ठा bna_tx_event_cbfn अणु
	/* Optional */
	व्योम (*tcb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_tcb *);
	व्योम (*tcb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_tcb *);
	/* Mandatory */
	व्योम (*tx_stall_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);
	व्योम (*tx_resume_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);
	व्योम (*tx_cleanup_cbfn)(काष्ठा bnad *, काष्ठा bna_tx *);
पूर्ण;

/* Tx module - keeps track of मुक्त, active tx objects */
काष्ठा bna_tx_mod अणु
	काष्ठा bna_tx *tx;		/* BFI_MAX_TXQ entries */
	काष्ठा bna_txq *txq;		/* BFI_MAX_TXQ entries */

	काष्ठा list_head			tx_मुक्त_q;
	काष्ठा list_head			tx_active_q;

	काष्ठा list_head			txq_मुक्त_q;

	/* callback क्रम bna_tx_mod_stop() */
	व्योम (*stop_cbfn)(काष्ठा bna_enet *enet);

	काष्ठा bfa_wc		tx_stop_wc;

	क्रमागत bna_tx_mod_flags flags;

	u8			prio_map;
	पूर्णांक			शेष_prio;
	पूर्णांक			iscsi_over_cee;
	पूर्णांक			iscsi_prio;
	पूर्णांक			prio_reconfigured;

	u32			rid_mask;

	काष्ठा bna *bna;
पूर्ण;

/* Rx object */

/* Rx datapath control काष्ठाure */
काष्ठा bna_rcb अणु
	/* Fast path */
	व्योम			**sw_qpt;
	व्योम			*sw_q;
	व्योम			*unmap_q;
	u32		producer_index;
	u32		consumer_index;
	u32		q_depth;
	व्योम __iomem   *q_dbell;
	/* Control path */
	काष्ठा bna_rxq *rxq;
	काष्ठा bna_ccb *ccb;
	काष्ठा bnad *bnad;
	व्योम			*priv; /* BNAD's cookie */
	अचिन्हित दीर्घ		flags;
	पूर्णांक			id;
पूर्ण;

/* RxQ काष्ठाure - QPT, configuration */
काष्ठा bna_rxq अणु
	काष्ठा list_head			qe;

	पूर्णांक			buffer_size;
	पूर्णांक			q_depth;
	u32			num_vecs;
	क्रमागत bna_status		multi_buffer;

	काष्ठा bna_qpt qpt;
	काष्ठा bna_rcb *rcb;

	काष्ठा bna_rxp *rxp;
	काष्ठा bna_rx *rx;

	पूर्णांक			hw_id;

	u64		rx_packets;
	u64		rx_bytes;
	u64		rx_packets_with_error;
	u64		rxbuf_alloc_failed;
	u64		rxbuf_map_failed;
पूर्ण;

/* RxQ pair */
जोड़ bna_rxq_u अणु
	काष्ठा अणु
		काष्ठा bna_rxq *hdr;
		काष्ठा bna_rxq *data;
	पूर्ण hds;
	काष्ठा अणु
		काष्ठा bna_rxq *small;
		काष्ठा bna_rxq *large;
	पूर्ण slr;
	काष्ठा अणु
		काष्ठा bna_rxq *only;
		काष्ठा bna_rxq *reserved;
	पूर्ण single;
पूर्ण;

/* Packet rate क्रम Dynamic Interrupt Moderation */
काष्ठा bna_pkt_rate अणु
	u32		small_pkt_cnt;
	u32		large_pkt_cnt;
पूर्ण;

/* Completion control काष्ठाure */
काष्ठा bna_ccb अणु
	/* Fast path */
	व्योम			**sw_qpt;
	व्योम			*sw_q;
	u32		producer_index;
	अस्थिर u32	*hw_producer_index;
	u32		q_depth;
	काष्ठा bna_ib_dbell *i_dbell;
	काष्ठा bna_rcb *rcb[2];
	व्योम			*ctrl; /* For bnad */
	काष्ठा bna_pkt_rate pkt_rate;
	u32			pkts_una;
	u32			bytes_per_पूर्णांकr;

	/* Control path */
	काष्ठा bna_cq *cq;
	काष्ठा bnad *bnad;
	व्योम			*priv; /* BNAD's cookie */
	क्रमागत bna_पूर्णांकr_type पूर्णांकr_type;
	पूर्णांक			पूर्णांकr_vector;
	u8			rx_coalescing_समयo; /* For NAPI */
	पूर्णांक			id;
	अक्षर			name[BNA_Q_NAME_SIZE];
पूर्ण;

/* CQ QPT, configuration  */
काष्ठा bna_cq अणु
	काष्ठा bna_qpt qpt;
	काष्ठा bna_ccb *ccb;

	काष्ठा bna_ib ib;

	काष्ठा bna_rx *rx;
पूर्ण;

काष्ठा bna_rss_config अणु
	क्रमागत bfi_enet_rss_type	hash_type;
	u8			hash_mask;
	u32		toeplitz_hash_key[BFI_ENET_RSS_KEY_LEN];
पूर्ण;

काष्ठा bna_hds_config अणु
	क्रमागत bfi_enet_hds_type	hdr_type;
	पूर्णांक			क्रमced_offset;
पूर्ण;

/* Rx object configuration used during creation */
काष्ठा bna_rx_config अणु
	क्रमागत bna_rx_type rx_type;
	पूर्णांक			num_paths;
	क्रमागत bna_rxp_type rxp_type;
	पूर्णांक			coalescing_समयo;
	/*
	 * Small/Large (or Header/Data) buffer size to be configured
	 * क्रम SLR and HDS queue type.
	 */
	u32			frame_size;

	/* header or small queue */
	u32			q1_depth;
	u32			q1_buf_size;

	/* data or large queue */
	u32			q0_depth;
	u32			q0_buf_size;
	u32			q0_num_vecs;
	क्रमागत bna_status		q0_multi_buf;

	क्रमागत bna_status rss_status;
	काष्ठा bna_rss_config rss_config;

	काष्ठा bna_hds_config hds_config;

	क्रमागत bna_status vlan_strip_status;
पूर्ण;

/* Rx Path काष्ठाure - one per MSIX vector/CPU */
काष्ठा bna_rxp अणु
	/* This should be the first one */
	काष्ठा list_head			qe;

	क्रमागत bna_rxp_type type;
	जोड़	bna_rxq_u	rxq;
	काष्ठा bna_cq cq;

	काष्ठा bna_rx *rx;

	/* MSI-x vector number क्रम configuring RSS */
	पूर्णांक			vector;
	पूर्णांक			hw_id;
पूर्ण;

/* RxF काष्ठाure (hardware Rx Function) */
काष्ठा bna_rxf अणु
	bfa_fsm_t		fsm;

	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	जोड़ अणु
		काष्ठा bfi_enet_enable_req req;
		काष्ठा bfi_enet_rss_cfg_req rss_req;
		काष्ठा bfi_enet_rit_req rit_req;
		काष्ठा bfi_enet_rx_vlan_req vlan_req;
		काष्ठा bfi_enet_mcast_add_req mcast_add_req;
		काष्ठा bfi_enet_mcast_del_req mcast_del_req;
		काष्ठा bfi_enet_ucast_req ucast_req;
	पूर्ण bfi_enet_cmd;

	/* callback क्रम bna_rxf_start() */
	व्योम (*start_cbfn) (काष्ठा bna_rx *rx);
	काष्ठा bna_rx *start_cbarg;

	/* callback क्रम bna_rxf_stop() */
	व्योम (*stop_cbfn) (काष्ठा bna_rx *rx);
	काष्ठा bna_rx *stop_cbarg;

	/**
	 * callback क्रम:
	 *	bna_rxf_ucast_set()
	 *	bna_rxf_अणुucast/mcastपूर्ण_add(),
	 *	bna_rxf_अणुucast/mcastपूर्ण_del(),
	 *	bna_rxf_mode_set()
	 */
	व्योम (*cam_fltr_cbfn)(काष्ठा bnad *bnad, काष्ठा bna_rx *rx);
	काष्ठा bnad *cam_fltr_cbarg;

	/* List of unicast addresses yet to be applied to h/w */
	काष्ठा list_head			ucast_pending_add_q;
	काष्ठा list_head			ucast_pending_del_q;
	काष्ठा bna_mac *ucast_pending_mac;
	पूर्णांक			ucast_pending_set;
	/* ucast addresses applied to the h/w */
	काष्ठा list_head			ucast_active_q;
	काष्ठा bna_mac ucast_active_mac;
	पूर्णांक			ucast_active_set;

	/* List of multicast addresses yet to be applied to h/w */
	काष्ठा list_head			mcast_pending_add_q;
	काष्ठा list_head			mcast_pending_del_q;
	/* multicast addresses applied to the h/w */
	काष्ठा list_head			mcast_active_q;
	काष्ठा list_head			mcast_handle_q;

	/* Rx modes yet to be applied to h/w */
	क्रमागत bna_rxmode rxmode_pending;
	क्रमागत bna_rxmode rxmode_pending_biपंचांगask;
	/* Rx modes applied to h/w */
	क्रमागत bna_rxmode rxmode_active;

	u8			vlan_pending_biपंचांगask;
	क्रमागत bna_status vlan_filter_status;
	u32	vlan_filter_table[(BFI_ENET_VLAN_ID_MAX) / 32];
	bool			vlan_strip_pending;
	क्रमागत bna_status		vlan_strip_status;

	क्रमागत bna_rss_flags	rss_pending;
	क्रमागत bna_status		rss_status;
	काष्ठा bna_rss_config	rss_cfg;
	u8			*rit;
	पूर्णांक			rit_size;

	काष्ठा bna_rx		*rx;
पूर्ण;

/* Rx object */
काष्ठा bna_rx अणु
	/* This should be the first one */
	काष्ठा list_head			qe;
	पूर्णांक			rid;
	पूर्णांक			hw_id;

	bfa_fsm_t		fsm;

	क्रमागत bna_rx_type type;

	पूर्णांक			num_paths;
	काष्ठा list_head			rxp_q;

	काष्ठा bna_hds_config	hds_cfg;

	काष्ठा bna_rxf rxf;

	क्रमागत bna_rx_flags rx_flags;

	काष्ठा bfa_msgq_cmd_entry msgq_cmd;
	जोड़ अणु
		काष्ठा bfi_enet_rx_cfg_req	cfg_req;
		काष्ठा bfi_enet_req		req;
		काष्ठा bfi_enet_rx_cfg_rsp	cfg_rsp;
	पूर्ण bfi_enet_cmd;

	/* Rx event handlers */
	व्योम (*rcb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_rcb *);
	व्योम (*rcb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_rcb *);
	व्योम (*ccb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_ccb *);
	व्योम (*ccb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_ccb *);
	व्योम (*rx_stall_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);
	व्योम (*rx_cleanup_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);
	व्योम (*rx_post_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);

	/* callback क्रम bna_rx_disable(), bna_rx_stop() */
	व्योम (*stop_cbfn)(व्योम *arg, काष्ठा bna_rx *rx);
	व्योम			*stop_cbarg;

	काष्ठा bna *bna;
	व्योम			*priv; /* bnad's cookie */
पूर्ण;

काष्ठा bna_rx_event_cbfn अणु
	/* Optional */
	व्योम (*rcb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_rcb *);
	व्योम (*rcb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_rcb *);
	व्योम (*ccb_setup_cbfn)(काष्ठा bnad *, काष्ठा bna_ccb *);
	व्योम (*ccb_destroy_cbfn)(काष्ठा bnad *, काष्ठा bna_ccb *);
	व्योम (*rx_stall_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);
	/* Mandatory */
	व्योम (*rx_cleanup_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);
	व्योम (*rx_post_cbfn)(काष्ठा bnad *, काष्ठा bna_rx *);
पूर्ण;

/* Rx module - keeps track of मुक्त, active rx objects */
काष्ठा bna_rx_mod अणु
	काष्ठा bna *bna;		/* back poपूर्णांकer to parent */
	काष्ठा bna_rx *rx;		/* BFI_MAX_RXQ entries */
	काष्ठा bna_rxp *rxp;		/* BFI_MAX_RXQ entries */
	काष्ठा bna_rxq *rxq;		/* BFI_MAX_RXQ entries */

	काष्ठा list_head			rx_मुक्त_q;
	काष्ठा list_head			rx_active_q;
	पूर्णांक			rx_मुक्त_count;

	काष्ठा list_head			rxp_मुक्त_q;
	पूर्णांक			rxp_मुक्त_count;

	काष्ठा list_head			rxq_मुक्त_q;
	पूर्णांक			rxq_मुक्त_count;

	क्रमागत bna_rx_mod_flags flags;

	/* callback क्रम bna_rx_mod_stop() */
	व्योम (*stop_cbfn)(काष्ठा bna_enet *enet);

	काष्ठा bfa_wc		rx_stop_wc;
	u32		dim_vector[BNA_LOAD_T_MAX][BNA_BIAS_T_MAX];
	u32		rid_mask;
पूर्ण;

/* CAM */

काष्ठा bna_ucam_mod अणु
	काष्ठा bna_mac *ucmac;		/* num_ucmac * 2 entries */
	काष्ठा list_head			मुक्त_q;
	काष्ठा list_head			del_q;

	काष्ठा bna *bna;
पूर्ण;

काष्ठा bna_mcam_handle अणु
	/* This should be the first one */
	काष्ठा list_head			qe;
	पूर्णांक			handle;
	पूर्णांक			refcnt;
पूर्ण;

काष्ठा bna_mcam_mod अणु
	काष्ठा bna_mac *mcmac;		/* num_mcmac * 2 entries */
	काष्ठा bna_mcam_handle *mchandle;	/* num_mcmac entries */
	काष्ठा list_head			मुक्त_q;
	काष्ठा list_head			del_q;
	काष्ठा list_head			मुक्त_handle_q;

	काष्ठा bna *bna;
पूर्ण;

/* Statistics */

काष्ठा bna_stats अणु
	काष्ठा bna_dma_addr	hw_stats_dma;
	काष्ठा bfi_enet_stats	*hw_stats_kva;
	काष्ठा bfi_enet_stats	hw_stats;
पूर्ण;

काष्ठा bna_stats_mod अणु
	bool		ioc_पढ़ोy;
	bool		stats_get_busy;
	bool		stats_clr_busy;
	काष्ठा bfa_msgq_cmd_entry stats_get_cmd;
	काष्ठा bfa_msgq_cmd_entry stats_clr_cmd;
	काष्ठा bfi_enet_stats_req stats_get;
	काष्ठा bfi_enet_stats_req stats_clr;
पूर्ण;

/* BNA */

काष्ठा bna अणु
	काष्ठा bna_ident ident;
	काष्ठा bfa_pcidev pcidev;

	काष्ठा bna_reg regs;
	काष्ठा bna_bit_defn bits;

	काष्ठा bna_stats stats;

	काष्ठा bna_ioceth ioceth;
	काष्ठा bfa_cee cee;
	काष्ठा bfa_flash flash;
	काष्ठा bfa_msgq msgq;

	काष्ठा bna_ethport ethport;
	काष्ठा bna_enet enet;
	काष्ठा bna_stats_mod stats_mod;

	काष्ठा bna_tx_mod tx_mod;
	काष्ठा bna_rx_mod rx_mod;
	काष्ठा bna_ucam_mod ucam_mod;
	काष्ठा bna_mcam_mod mcam_mod;

	क्रमागत bna_mod_flags mod_flags;

	पूर्णांक			शेष_mode_rid;
	पूर्णांक			promisc_rid;

	काष्ठा bnad *bnad;
पूर्ण;
#पूर्ण_अगर	/* __BNA_TYPES_H__ */
