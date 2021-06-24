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
#अगर_अघोषित __BNAD_H__
#घोषणा __BNAD_H__

#समावेश <linux/rtnetlink.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/अगर_vlan.h>

/* Fix क्रम IA64 */
#समावेश <यंत्र/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश <net/ip.h>
#समावेश <net/tcp.h>

#समावेश "bna.h"

#घोषणा BNAD_TXQ_DEPTH		2048
#घोषणा BNAD_RXQ_DEPTH		2048

#घोषणा BNAD_MAX_TX		1
#घोषणा BNAD_MAX_TXQ_PER_TX	8	/* 8 priority queues */
#घोषणा BNAD_TXQ_NUM		1

#घोषणा BNAD_MAX_RX		1
#घोषणा BNAD_MAX_RXP_PER_RX	16
#घोषणा BNAD_MAX_RXQ_PER_RXP	2

/*
 * Control काष्ठाure poपूर्णांकed to ccb->ctrl, which
 * determines the NAPI / LRO behavior CCB
 * There is 1:1 corres. between ccb & ctrl
 */
काष्ठा bnad_rx_ctrl अणु
	काष्ठा bna_ccb *ccb;
	काष्ठा bnad *bnad;
	अचिन्हित दीर्घ  flags;
	काष्ठा napi_काष्ठा	napi;
	u64		rx_पूर्णांकr_ctr;
	u64		rx_poll_ctr;
	u64		rx_schedule;
	u64		rx_keep_poll;
	u64		rx_complete;
पूर्ण;

#घोषणा BNAD_RXMODE_PROMISC_DEFAULT	BNA_RXMODE_PROMISC

/*
 * GLOBAL #घोषणाs (CONSTANTS)
 */
#घोषणा BNAD_NAME			"bna"
#घोषणा BNAD_NAME_LEN			64

#घोषणा BNAD_MAILBOX_MSIX_INDEX		0
#घोषणा BNAD_MAILBOX_MSIX_VECTORS	1
#घोषणा BNAD_INTX_TX_IB_BITMASK		0x1
#घोषणा BNAD_INTX_RX_IB_BITMASK		0x2

#घोषणा BNAD_STATS_TIMER_FREQ		1000	/* in msecs */
#घोषणा BNAD_DIM_TIMER_FREQ		1000	/* in msecs */

#घोषणा BNAD_IOCETH_TIMEOUT	     10000

#घोषणा BNAD_MIN_Q_DEPTH		512
#घोषणा BNAD_MAX_RXQ_DEPTH		16384
#घोषणा BNAD_MAX_TXQ_DEPTH		2048

#घोषणा BNAD_JUMBO_MTU			9000

#घोषणा BNAD_NETIF_WAKE_THRESHOLD	8

#घोषणा BNAD_RXQ_REFILL_THRESHOLD_SHIFT	3

/* Bit positions क्रम tcb->flags */
#घोषणा BNAD_TXQ_FREE_SENT		0
#घोषणा BNAD_TXQ_TX_STARTED		1

/* Bit positions क्रम rcb->flags */
#घोषणा BNAD_RXQ_STARTED		0
#घोषणा BNAD_RXQ_POST_OK		1

/* Resource limits */
#घोषणा BNAD_NUM_TXQ			(bnad->num_tx * bnad->num_txq_per_tx)
#घोषणा BNAD_NUM_RXP			(bnad->num_rx * bnad->num_rxp_per_rx)

#घोषणा BNAD_FRAME_SIZE(_mtu) \
	(ETH_HLEN + VLAN_HLEN + (_mtu) + ETH_FCS_LEN)

/*
 * DATA STRUCTURES
 */

/* क्रमागतs */
क्रमागत bnad_पूर्णांकr_source अणु
	BNAD_INTR_TX		= 1,
	BNAD_INTR_RX		= 2
पूर्ण;

क्रमागत bnad_link_state अणु
	BNAD_LS_DOWN		= 0,
	BNAD_LS_UP		= 1
पूर्ण;

काष्ठा bnad_iocmd_comp अणु
	काष्ठा bnad		*bnad;
	काष्ठा completion	comp;
	पूर्णांक			comp_status;
पूर्ण;

काष्ठा bnad_completion अणु
	काष्ठा completion	ioc_comp;
	काष्ठा completion	ucast_comp;
	काष्ठा completion	mcast_comp;
	काष्ठा completion	tx_comp;
	काष्ठा completion	rx_comp;
	काष्ठा completion	stats_comp;
	काष्ठा completion	enet_comp;
	काष्ठा completion	mtu_comp;

	u8			ioc_comp_status;
	u8			ucast_comp_status;
	u8			mcast_comp_status;
	u8			tx_comp_status;
	u8			rx_comp_status;
	u8			stats_comp_status;
	u8			port_comp_status;
	u8			mtu_comp_status;
पूर्ण;

/* Tx Rx Control Stats */
काष्ठा bnad_drv_stats अणु
	u64		netअगर_queue_stop;
	u64		netअगर_queue_wakeup;
	u64		netअगर_queue_stopped;
	u64		tso4;
	u64		tso6;
	u64		tso_err;
	u64		tcpcsum_offload;
	u64		udpcsum_offload;
	u64		csum_help;
	u64		tx_skb_too_लघु;
	u64		tx_skb_stopping;
	u64		tx_skb_max_vectors;
	u64		tx_skb_mss_too_दीर्घ;
	u64		tx_skb_tso_too_लघु;
	u64		tx_skb_tso_prepare;
	u64		tx_skb_non_tso_too_दीर्घ;
	u64		tx_skb_tcp_hdr;
	u64		tx_skb_udp_hdr;
	u64		tx_skb_csum_err;
	u64		tx_skb_headlen_too_दीर्घ;
	u64		tx_skb_headlen_zero;
	u64		tx_skb_frag_zero;
	u64		tx_skb_len_mismatch;
	u64		tx_skb_map_failed;

	u64		hw_stats_updates;
	u64		netअगर_rx_dropped;

	u64		link_toggle;
	u64		cee_toggle;

	u64		rxp_info_alloc_failed;
	u64		mbox_पूर्णांकr_disabled;
	u64		mbox_पूर्णांकr_enabled;
	u64		tx_unmap_q_alloc_failed;
	u64		rx_unmap_q_alloc_failed;

	u64		rxbuf_alloc_failed;
	u64		rxbuf_map_failed;
पूर्ण;

/* Complete driver stats */
काष्ठा bnad_stats अणु
	काष्ठा bnad_drv_stats drv_stats;
	काष्ठा bna_stats *bna_stats;
पूर्ण;

/* Tx / Rx Resources */
काष्ठा bnad_tx_res_info अणु
	काष्ठा bna_res_info res_info[BNA_TX_RES_T_MAX];
पूर्ण;

काष्ठा bnad_rx_res_info अणु
	काष्ठा bna_res_info res_info[BNA_RX_RES_T_MAX];
पूर्ण;

काष्ठा bnad_tx_info अणु
	काष्ठा bna_tx *tx; /* 1:1 between tx_info & tx */
	काष्ठा bna_tcb *tcb[BNAD_MAX_TXQ_PER_TX];
	u32 tx_id;
	काष्ठा delayed_work tx_cleanup_work;
पूर्ण ____cacheline_aligned;

काष्ठा bnad_rx_info अणु
	काष्ठा bna_rx *rx; /* 1:1 between rx_info & rx */

	काष्ठा bnad_rx_ctrl rx_ctrl[BNAD_MAX_RXP_PER_RX];
	u32 rx_id;
	काष्ठा work_काष्ठा rx_cleanup_work;
पूर्ण ____cacheline_aligned;

काष्ठा bnad_tx_vector अणु
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	DEFINE_DMA_UNMAP_LEN(dma_len);
पूर्ण;

काष्ठा bnad_tx_unmap अणु
	काष्ठा sk_buff		*skb;
	u32			nvecs;
	काष्ठा bnad_tx_vector	vectors[BFI_TX_MAX_VECTORS_PER_WI];
पूर्ण;

काष्ठा bnad_rx_vector अणु
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	u32			len;
पूर्ण;

काष्ठा bnad_rx_unmap अणु
	काष्ठा page		*page;
	काष्ठा sk_buff		*skb;
	काष्ठा bnad_rx_vector	vector;
	u32			page_offset;
पूर्ण;

क्रमागत bnad_rxbuf_type अणु
	BNAD_RXBUF_NONE		= 0,
	BNAD_RXBUF_SK_BUFF	= 1,
	BNAD_RXBUF_PAGE		= 2,
	BNAD_RXBUF_MULTI_BUFF	= 3
पूर्ण;

#घोषणा BNAD_RXBUF_IS_SK_BUFF(_type)	((_type) == BNAD_RXBUF_SK_BUFF)
#घोषणा BNAD_RXBUF_IS_MULTI_BUFF(_type)	((_type) == BNAD_RXBUF_MULTI_BUFF)

काष्ठा bnad_rx_unmap_q अणु
	पूर्णांक			reuse_pi;
	पूर्णांक			alloc_order;
	u32			map_size;
	क्रमागत bnad_rxbuf_type	type;
	काष्ठा bnad_rx_unmap	unmap[] ____cacheline_aligned;
पूर्ण;

#घोषणा BNAD_PCI_DEV_IS_CAT2(_bnad) \
	((_bnad)->pcidev->device == BFA_PCI_DEVICE_ID_CT2)

/* Bit mask values क्रम bnad->cfg_flags */
#घोषणा	BNAD_CF_DIM_ENABLED		0x01	/* DIM */
#घोषणा	BNAD_CF_PROMISC			0x02
#घोषणा BNAD_CF_ALLMULTI		0x04
#घोषणा	BNAD_CF_DEFAULT			0x08
#घोषणा	BNAD_CF_MSIX			0x10	/* If in MSIx mode */

/* Defines क्रम run_flags bit-mask */
/* Set, tested & cleared using xxx_bit() functions */
/* Values indicated bit positions */
#घोषणा BNAD_RF_CEE_RUNNING		0
#घोषणा BNAD_RF_MTU_SET		1
#घोषणा BNAD_RF_MBOX_IRQ_DISABLED	2
#घोषणा BNAD_RF_NETDEV_REGISTERED	3
#घोषणा BNAD_RF_DIM_TIMER_RUNNING	4
#घोषणा BNAD_RF_STATS_TIMER_RUNNING	5
#घोषणा BNAD_RF_TX_PRIO_SET		6

काष्ठा bnad अणु
	काष्ठा net_device	*netdev;
	u32			id;

	/* Data path */
	काष्ठा bnad_tx_info tx_info[BNAD_MAX_TX];
	काष्ठा bnad_rx_info rx_info[BNAD_MAX_RX];

	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	/*
	 * These q numbers are global only because
	 * they are used to calculate MSIx vectors.
	 * Actually the exact # of queues are per Tx/Rx
	 * object.
	 */
	u32		num_tx;
	u32		num_rx;
	u32		num_txq_per_tx;
	u32		num_rxp_per_rx;

	u32		txq_depth;
	u32		rxq_depth;

	u8			tx_coalescing_समयo;
	u8			rx_coalescing_समयo;

	काष्ठा bna_rx_config rx_config[BNAD_MAX_RX] ____cacheline_aligned;
	काष्ठा bna_tx_config tx_config[BNAD_MAX_TX] ____cacheline_aligned;

	व्योम __iomem		*bar0;	/* BAR0 address */

	काष्ठा bna bna;

	u32		cfg_flags;
	अचिन्हित दीर्घ		run_flags;

	काष्ठा pci_dev		*pcidev;
	u64		mmio_start;
	u64		mmio_len;

	u32		msix_num;
	काष्ठा msix_entry	*msix_table;

	काष्ठा mutex		conf_mutex;
	spinlock_t		bna_lock ____cacheline_aligned;

	/* Timers */
	काष्ठा समयr_list	ioc_समयr;
	काष्ठा समयr_list	dim_समयr;
	काष्ठा समयr_list	stats_समयr;

	/* Control path resources, memory & irq */
	काष्ठा bna_res_info res_info[BNA_RES_T_MAX];
	काष्ठा bna_res_info mod_res_info[BNA_MOD_RES_T_MAX];
	काष्ठा bnad_tx_res_info tx_res_info[BNAD_MAX_TX];
	काष्ठा bnad_rx_res_info rx_res_info[BNAD_MAX_RX];

	काष्ठा bnad_completion bnad_completions;

	/* Burnt in MAC address */
	u8			perm_addr[ETH_ALEN];

	काष्ठा workqueue_काष्ठा *work_q;

	/* Statistics */
	काष्ठा bnad_stats stats;

	काष्ठा bnad_diag *diag;

	अक्षर			adapter_name[BNAD_NAME_LEN];
	अक्षर			port_name[BNAD_NAME_LEN];
	अक्षर			mbox_irq_name[BNAD_NAME_LEN];
	अक्षर			wq_name[BNAD_NAME_LEN];

	/* debugfs specअगरic data */
	अक्षर	*regdata;
	u32	reglen;
	काष्ठा dentry *bnad_dentry_files[5];
	काष्ठा dentry *port_debugfs_root;
पूर्ण;

काष्ठा bnad_drvinfo अणु
	काष्ठा bfa_ioc_attr  ioc_attr;
	काष्ठा bfa_cee_attr  cee_attr;
	काष्ठा bfa_flash_attr flash_attr;
	u32	cee_status;
	u32	flash_status;
पूर्ण;

/*
 * EXTERN VARIABLES
 */
बाह्य स्थिर काष्ठा firmware *bfi_fw;

/*
 * EXTERN PROTOTYPES
 */
u32 *cna_get_firmware_buf(काष्ठा pci_dev *pdev);
/* Netdev entry poपूर्णांक prototypes */
व्योम bnad_set_rx_mode(काष्ठा net_device *netdev);
काष्ठा net_device_stats *bnad_get_netdev_stats(काष्ठा net_device *netdev);
पूर्णांक bnad_mac_addr_set_locked(काष्ठा bnad *bnad, स्थिर u8 *mac_addr);
पूर्णांक bnad_enable_शेष_bcast(काष्ठा bnad *bnad);
व्योम bnad_restore_vlans(काष्ठा bnad *bnad, u32 rx_id);
व्योम bnad_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम bnad_cb_completion(व्योम *arg, क्रमागत bfa_status status);

/* Configuration & setup */
व्योम bnad_tx_coalescing_समयo_set(काष्ठा bnad *bnad);
व्योम bnad_rx_coalescing_समयo_set(काष्ठा bnad *bnad);

पूर्णांक bnad_setup_rx(काष्ठा bnad *bnad, u32 rx_id);
पूर्णांक bnad_setup_tx(काष्ठा bnad *bnad, u32 tx_id);
व्योम bnad_destroy_tx(काष्ठा bnad *bnad, u32 tx_id);
व्योम bnad_destroy_rx(काष्ठा bnad *bnad, u32 rx_id);

/* Timer start/stop protos */
व्योम bnad_dim_समयr_start(काष्ठा bnad *bnad);

/* Statistics */
व्योम bnad_netdev_qstats_fill(काष्ठा bnad *bnad,
			     काष्ठा rtnl_link_stats64 *stats);
व्योम bnad_netdev_hwstats_fill(काष्ठा bnad *bnad,
			      काष्ठा rtnl_link_stats64 *stats);

/* Debugfs */
व्योम bnad_debugfs_init(काष्ठा bnad *bnad);
व्योम bnad_debugfs_uninit(काष्ठा bnad *bnad);

/* MACROS */
/* To set & get the stats counters */
#घोषणा BNAD_UPDATE_CTR(_bnad, _ctr)				\
				(((_bnad)->stats.drv_stats._ctr)++)

#घोषणा BNAD_GET_CTR(_bnad, _ctr) ((_bnad)->stats.drv_stats._ctr)

#घोषणा bnad_enable_rx_irq_unsafe(_ccb)			\
अणु							\
	अगर (likely(test_bit(BNAD_RXQ_STARTED, &(_ccb)->rcb[0]->flags))) अणु\
		bna_ib_coalescing_समयr_set((_ccb)->i_dbell,	\
			(_ccb)->rx_coalescing_समयo);		\
		bna_ib_ack((_ccb)->i_dbell, 0);			\
	पूर्ण							\
पूर्ण

#पूर्ण_अगर /* __BNAD_H__ */
