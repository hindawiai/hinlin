<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_H_
#घोषणा _ICE_H_

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/compiler.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/रुको.h>
#समावेश <linux/aer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/log2.h>
#समावेश <linux/ip.h>
#समावेश <linux/sctp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/bpf.h>
#समावेश <linux/avf/virtchnl.h>
#समावेश <linux/cpu_rmap.h>
#समावेश <linux/dim.h>
#समावेश <net/devlink.h>
#समावेश <net/ipv6.h>
#समावेश <net/xdp_sock.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/geneve.h>
#समावेश <net/gre.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/vxlan.h>
#अगर IS_ENABLED(CONFIG_DCB)
#समावेश <scsi/iscsi_proto.h>
#पूर्ण_अगर /* CONFIG_DCB */
#समावेश "ice_devids.h"
#समावेश "ice_type.h"
#समावेश "ice_txrx.h"
#समावेश "ice_dcb.h"
#समावेश "ice_switch.h"
#समावेश "ice_common.h"
#समावेश "ice_sched.h"
#समावेश "ice_virtchnl_pf.h"
#समावेश "ice_sriov.h"
#समावेश "ice_fdir.h"
#समावेश "ice_xsk.h"
#समावेश "ice_arfs.h"
#समावेश "ice_lag.h"

#घोषणा ICE_BAR0		0
#घोषणा ICE_REQ_DESC_MULTIPLE	32
#घोषणा ICE_MIN_NUM_DESC	64
#घोषणा ICE_MAX_NUM_DESC	8160
#घोषणा ICE_Dभग्न_न्यून_RX_DESC	512
#घोषणा ICE_DFLT_NUM_TX_DESC	256
#घोषणा ICE_DFLT_NUM_RX_DESC	2048

#घोषणा ICE_DFLT_TRAFFIC_CLASS	BIT(0)
#घोषणा ICE_INT_NAME_STR_LEN	(IFNAMSIZ + 16)
#घोषणा ICE_AQ_LEN		64
#घोषणा ICE_MBXSQ_LEN		64
#घोषणा ICE_MIN_LAN_TXRX_MSIX	1
#घोषणा ICE_MIN_LAN_OICR_MSIX	1
#घोषणा ICE_MIN_MSIX		(ICE_MIN_LAN_TXRX_MSIX + ICE_MIN_LAN_OICR_MSIX)
#घोषणा ICE_Fसूची_MSIX		2
#घोषणा ICE_NO_VSI		0xffff
#घोषणा ICE_VSI_MAP_CONTIG	0
#घोषणा ICE_VSI_MAP_SCATTER	1
#घोषणा ICE_MAX_SCATTER_TXQS	16
#घोषणा ICE_MAX_SCATTER_RXQS	16
#घोषणा ICE_Q_WAIT_RETRY_LIMIT	10
#घोषणा ICE_Q_WAIT_MAX_RETRY	(5 * ICE_Q_WAIT_RETRY_LIMIT)
#घोषणा ICE_MAX_LG_RSS_QS	256
#घोषणा ICE_RES_VALID_BIT	0x8000
#घोषणा ICE_RES_MISC_VEC_ID	(ICE_RES_VALID_BIT - 1)
/* All VF control VSIs share the same IRQ, so assign a unique ID क्रम them */
#घोषणा ICE_RES_VF_CTRL_VEC_ID	(ICE_RES_MISC_VEC_ID - 1)
#घोषणा ICE_INVAL_Q_INDEX	0xffff
#घोषणा ICE_INVAL_VFID		256

#घोषणा ICE_MAX_RXQS_PER_TC		256	/* Used when setting VSI context per TC Rx queues */
#घोषणा ICE_MAX_RESET_WAIT		20

#घोषणा ICE_VSIQF_HKEY_ARRAY_SIZE	((VSIQF_HKEY_MAX_INDEX + 1) *	4)

#घोषणा ICE_DFLT_NETIF_M (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

#घोषणा ICE_MAX_MTU	(ICE_AQ_SET_MAC_FRAME_SIZE_MAX - ICE_ETH_PKT_HDR_PAD)

#घोषणा ICE_UP_TABLE_TRANSLATE(val, i) \
		(((val) << ICE_AQ_VSI_UP_TABLE_UP##i##_S) & \
		  ICE_AQ_VSI_UP_TABLE_UP##i##_M)

#घोषणा ICE_TX_DESC(R, i) (&(((काष्ठा ice_tx_desc *)((R)->desc))[i]))
#घोषणा ICE_RX_DESC(R, i) (&(((जोड़ ice_32b_rx_flex_desc *)((R)->desc))[i]))
#घोषणा ICE_TX_CTX_DESC(R, i) (&(((काष्ठा ice_tx_ctx_desc *)((R)->desc))[i]))
#घोषणा ICE_TX_FसूचीDESC(R, i) (&(((काष्ठा ice_fltr_desc *)((R)->desc))[i]))

/* Macro क्रम each VSI in a PF */
#घोषणा ice_क्रम_each_vsi(pf, i) \
	क्रम ((i) = 0; (i) < (pf)->num_alloc_vsi; (i)++)

/* Macros क्रम each Tx/Rx ring in a VSI */
#घोषणा ice_क्रम_each_txq(vsi, i) \
	क्रम ((i) = 0; (i) < (vsi)->num_txq; (i)++)

#घोषणा ice_क्रम_each_rxq(vsi, i) \
	क्रम ((i) = 0; (i) < (vsi)->num_rxq; (i)++)

/* Macros क्रम each allocated Tx/Rx ring whether used or not in a VSI */
#घोषणा ice_क्रम_each_alloc_txq(vsi, i) \
	क्रम ((i) = 0; (i) < (vsi)->alloc_txq; (i)++)

#घोषणा ice_क्रम_each_alloc_rxq(vsi, i) \
	क्रम ((i) = 0; (i) < (vsi)->alloc_rxq; (i)++)

#घोषणा ice_क्रम_each_q_vector(vsi, i) \
	क्रम ((i) = 0; (i) < (vsi)->num_q_vectors; (i)++)

#घोषणा ICE_UCAST_PROMISC_BITS (ICE_PROMISC_UCAST_TX | ICE_PROMISC_MCAST_TX | \
				ICE_PROMISC_UCAST_RX | ICE_PROMISC_MCAST_RX)

#घोषणा ICE_UCAST_VLAN_PROMISC_BITS (ICE_PROMISC_UCAST_TX | \
				     ICE_PROMISC_MCAST_TX | \
				     ICE_PROMISC_UCAST_RX | \
				     ICE_PROMISC_MCAST_RX | \
				     ICE_PROMISC_VLAN_TX  | \
				     ICE_PROMISC_VLAN_RX)

#घोषणा ICE_MCAST_PROMISC_BITS (ICE_PROMISC_MCAST_TX | ICE_PROMISC_MCAST_RX)

#घोषणा ICE_MCAST_VLAN_PROMISC_BITS (ICE_PROMISC_MCAST_TX | \
				     ICE_PROMISC_MCAST_RX | \
				     ICE_PROMISC_VLAN_TX  | \
				     ICE_PROMISC_VLAN_RX)

#घोषणा ice_pf_to_dev(pf) (&((pf)->pdev->dev))

काष्ठा ice_txq_meta अणु
	u32 q_teid;	/* Tx-scheduler element identअगरier */
	u16 q_id;	/* Entry in VSI's txq_map biपंचांगap */
	u16 q_handle;	/* Relative index of Tx queue within TC */
	u16 vsi_idx;	/* VSI index that Tx queue beदीर्घs to */
	u8 tc;		/* TC number that Tx queue beदीर्घs to */
पूर्ण;

काष्ठा ice_tc_info अणु
	u16 qoffset;
	u16 qcount_tx;
	u16 qcount_rx;
	u8 netdev_tc;
पूर्ण;

काष्ठा ice_tc_cfg अणु
	u8 numtc; /* Total number of enabled TCs */
	u8 ena_tc; /* Tx map */
	काष्ठा ice_tc_info tc_info[ICE_MAX_TRAFFIC_CLASS];
पूर्ण;

काष्ठा ice_res_tracker अणु
	u16 num_entries;
	u16 end;
	u16 list[];
पूर्ण;

काष्ठा ice_qs_cfg अणु
	काष्ठा mutex *qs_mutex;  /* will be asचिन्हित to &pf->avail_q_mutex */
	अचिन्हित दीर्घ *pf_map;
	अचिन्हित दीर्घ pf_map_size;
	अचिन्हित पूर्णांक q_count;
	अचिन्हित पूर्णांक scatter_count;
	u16 *vsi_map;
	u16 vsi_map_offset;
	u8 mapping_mode;
पूर्ण;

काष्ठा ice_sw अणु
	काष्ठा ice_pf *pf;
	u16 sw_id;		/* चयन ID क्रम this चयन */
	u16 bridge_mode;	/* VEB/VEPA/Port Virtualizer */
	काष्ठा ice_vsi *dflt_vsi;	/* शेष VSI क्रम this चयन */
	u8 dflt_vsi_ena:1;	/* true अगर above dflt_vsi is enabled */
पूर्ण;

क्रमागत ice_pf_state अणु
	ICE_TESTING,
	ICE_DOWN,
	ICE_NEEDS_RESTART,
	ICE_PREPARED_FOR_RESET,	/* set by driver when prepared */
	ICE_RESET_OICR_RECV,		/* set by driver after rcv reset OICR */
	ICE_PFR_REQ,			/* set by driver and peers */
	ICE_CORER_REQ,		/* set by driver and peers */
	ICE_GLOBR_REQ,		/* set by driver and peers */
	ICE_CORER_RECV,		/* set by OICR handler */
	ICE_GLOBR_RECV,		/* set by OICR handler */
	ICE_EMPR_RECV,		/* set by OICR handler */
	ICE_SUSPENDED,		/* set on module हटाओ path */
	ICE_RESET_FAILED,		/* set by reset/rebuild */
	/* When checking क्रम the PF to be in a nominal operating state, the
	 * bits that are grouped at the beginning of the list need to be
	 * checked. Bits occurring beक्रमe ICE_STATE_NOMINAL_CHECK_BITS will
	 * be checked. If you need to add a bit पूर्णांकo consideration क्रम nominal
	 * operating state, it must be added beक्रमe
	 * ICE_STATE_NOMINAL_CHECK_BITS. Do not move this entry's position
	 * without appropriate consideration.
	 */
	ICE_STATE_NOMINAL_CHECK_BITS,
	ICE_ADMINQ_EVENT_PENDING,
	ICE_MAILBOXQ_EVENT_PENDING,
	ICE_MDD_EVENT_PENDING,
	ICE_VFLR_EVENT_PENDING,
	ICE_FLTR_OVERFLOW_PROMISC,
	ICE_VF_DIS,
	ICE_CFG_BUSY,
	ICE_SERVICE_SCHED,
	ICE_SERVICE_DIS,
	ICE_FD_FLUSH_REQ,
	ICE_OICR_INTR_DIS,		/* Global OICR पूर्णांकerrupt disabled */
	ICE_MDD_VF_PRINT_PENDING,	/* set when MDD event handle */
	ICE_VF_RESETS_DISABLED,	/* disable resets during ice_हटाओ */
	ICE_LINK_DEFAULT_OVERRIDE_PENDING,
	ICE_PHY_INIT_COMPLETE,
	ICE_FD_VF_FLUSH_CTX,		/* set at FD Rx IRQ or समयout */
	ICE_STATE_NBITS		/* must be last */
पूर्ण;

क्रमागत ice_vsi_state अणु
	ICE_VSI_DOWN,
	ICE_VSI_NEEDS_RESTART,
	ICE_VSI_NETDEV_ALLOCD,
	ICE_VSI_NETDEV_REGISTERED,
	ICE_VSI_UMAC_FLTR_CHANGED,
	ICE_VSI_MMAC_FLTR_CHANGED,
	ICE_VSI_VLAN_FLTR_CHANGED,
	ICE_VSI_PROMISC_CHANGED,
	ICE_VSI_STATE_NBITS		/* must be last */
पूर्ण;

/* काष्ठा that defines a VSI, associated with a dev */
काष्ठा ice_vsi अणु
	काष्ठा net_device *netdev;
	काष्ठा ice_sw *vsw;		 /* चयन this VSI is on */
	काष्ठा ice_pf *back;		 /* back poपूर्णांकer to PF */
	काष्ठा ice_port_info *port_info; /* back poपूर्णांकer to port_info */
	काष्ठा ice_ring **rx_rings;	 /* Rx ring array */
	काष्ठा ice_ring **tx_rings;	 /* Tx ring array */
	काष्ठा ice_q_vector **q_vectors; /* q_vector array */

	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *data);

	u64 tx_linearize;
	DECLARE_BITMAP(state, ICE_VSI_STATE_NBITS);
	अचिन्हित पूर्णांक current_netdev_flags;
	u32 tx_restart;
	u32 tx_busy;
	u32 rx_buf_failed;
	u32 rx_page_failed;
	u16 num_q_vectors;
	u16 base_vector;		/* IRQ base क्रम OS reserved vectors */
	क्रमागत ice_vsi_type type;
	u16 vsi_num;			/* HW (असलolute) index of this VSI */
	u16 idx;			/* software index in pf->vsi[] */

	s16 vf_id;			/* VF ID क्रम SR-IOV VSIs */

	u16 ethtype;			/* Ethernet protocol क्रम छोड़ो frame */
	u16 num_gfltr;
	u16 num_bfltr;

	/* RSS config */
	u16 rss_table_size;	/* HW RSS table size */
	u16 rss_size;		/* Allocated RSS queues */
	u8 *rss_hkey_user;	/* User configured hash keys */
	u8 *rss_lut_user;	/* User configured lookup table entries */
	u8 rss_lut_type;	/* used to configure Get/Set RSS LUT AQ call */

	/* aRFS members only allocated क्रम the PF VSI */
#घोषणा ICE_MAX_ARFS_LIST	1024
#घोषणा ICE_ARFS_LST_MASK	(ICE_MAX_ARFS_LIST - 1)
	काष्ठा hlist_head *arfs_fltr_list;
	काष्ठा ice_arfs_active_fltr_cntrs *arfs_fltr_cntrs;
	spinlock_t arfs_lock;	/* protects aRFS hash table and filter state */
	atomic_t *arfs_last_fltr_id;

	/* devlink port data */
	काष्ठा devlink_port devlink_port;
	bool devlink_port_रेजिस्टरed;

	u16 max_frame;
	u16 rx_buf_len;

	काष्ठा ice_aqc_vsi_props info;	 /* VSI properties */

	/* VSI stats */
	काष्ठा rtnl_link_stats64 net_stats;
	काष्ठा ice_eth_stats eth_stats;
	काष्ठा ice_eth_stats eth_stats_prev;

	काष्ठा list_head पंचांगp_sync_list;		/* MAC filters to be synced */
	काष्ठा list_head पंचांगp_unsync_list;	/* MAC filters to be unsynced */

	u8 irqs_पढ़ोy:1;
	u8 current_isup:1;		 /* Sync 'link up' logging */
	u8 stat_offsets_loaded:1;
	u16 num_vlan;

	/* queue inक्रमmation */
	u8 tx_mapping_mode;		 /* ICE_MAP_MODE_[CONTIG|SCATTER] */
	u8 rx_mapping_mode;		 /* ICE_MAP_MODE_[CONTIG|SCATTER] */
	u16 *txq_map;			 /* index in pf->avail_txqs */
	u16 *rxq_map;			 /* index in pf->avail_rxqs */
	u16 alloc_txq;			 /* Allocated Tx queues */
	u16 num_txq;			 /* Used Tx queues */
	u16 alloc_rxq;			 /* Allocated Rx queues */
	u16 num_rxq;			 /* Used Rx queues */
	u16 req_txq;			 /* User requested Tx queues */
	u16 req_rxq;			 /* User requested Rx queues */
	u16 num_rx_desc;
	u16 num_tx_desc;
	काष्ठा ice_tc_cfg tc_cfg;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा ice_ring **xdp_rings;	 /* XDP ring array */
	अचिन्हित दीर्घ *af_xdp_zc_qps;	 /* tracks AF_XDP ZC enabled qps */
	u16 num_xdp_txq;		 /* Used XDP queues */
	u8 xdp_mapping_mode;		 /* ICE_MAP_MODE_[CONTIG|SCATTER] */

	/* setup back reference, to which aggregator node this VSI
	 * corresponds to
	 */
	काष्ठा ice_agg_node *agg_node;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/* काष्ठा that defines an पूर्णांकerrupt vector */
काष्ठा ice_q_vector अणु
	काष्ठा ice_vsi *vsi;

	u16 v_idx;			/* index in the vsi->q_vector array. */
	u16 reg_idx;
	u8 num_ring_rx;			/* total number of Rx rings in vector */
	u8 num_ring_tx;			/* total number of Tx rings in vector */
	u8 wb_on_itr:1;			/* अगर true, WB on ITR is enabled */
	/* in usecs, need to use ice_पूर्णांकrl_to_usecs_reg() beक्रमe writing this
	 * value to the device
	 */
	u8 पूर्णांकrl;

	काष्ठा napi_काष्ठा napi;

	काष्ठा ice_ring_container rx;
	काष्ठा ice_ring_container tx;

	cpumask_t affinity_mask;
	काष्ठा irq_affinity_notअगरy affinity_notअगरy;

	अक्षर name[ICE_INT_NAME_STR_LEN];

	u16 total_events;	/* net_dim(): number of पूर्णांकerrupts processed */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

क्रमागत ice_pf_flags अणु
	ICE_FLAG_FLTR_SYNC,
	ICE_FLAG_RSS_ENA,
	ICE_FLAG_SRIOV_ENA,
	ICE_FLAG_SRIOV_CAPABLE,
	ICE_FLAG_DCB_CAPABLE,
	ICE_FLAG_DCB_ENA,
	ICE_FLAG_FD_ENA,
	ICE_FLAG_ADV_FEATURES,
	ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA,
	ICE_FLAG_TOTAL_PORT_SHUTDOWN_ENA,
	ICE_FLAG_NO_MEDIA,
	ICE_FLAG_FW_LLDP_AGENT,
	ICE_FLAG_ETHTOOL_CTXT,		/* set when ethtool holds RTNL lock */
	ICE_FLAG_LEGACY_RX,
	ICE_FLAG_VF_TRUE_PROMISC_ENA,
	ICE_FLAG_MDD_AUTO_RESET_VF,
	ICE_FLAG_LINK_LENIENT_MODE_ENA,
	ICE_PF_FLAGS_NBITS		/* must be last */
पूर्ण;

काष्ठा ice_agg_node अणु
	u32 agg_id;
#घोषणा ICE_MAX_VSIS_IN_AGG_NODE	64
	u32 num_vsis;
	u8 valid;
पूर्ण;

काष्ठा ice_pf अणु
	काष्ठा pci_dev *pdev;

	काष्ठा devlink_region *nvm_region;
	काष्ठा devlink_region *devcaps_region;

	/* OS reserved IRQ details */
	काष्ठा msix_entry *msix_entries;
	काष्ठा ice_res_tracker *irq_tracker;
	/* First MSIX vector used by SR-IOV VFs. Calculated by subtracting the
	 * number of MSIX vectors needed क्रम all SR-IOV VFs from the number of
	 * MSIX vectors allowed on this PF.
	 */
	u16 sriov_base_vector;

	u16 ctrl_vsi_idx;		/* control VSI index in pf->vsi array */

	काष्ठा ice_vsi **vsi;		/* VSIs created by the driver */
	काष्ठा ice_sw *first_sw;	/* first चयन created by firmware */
	/* Virtchnl/SR-IOV config info */
	काष्ठा ice_vf *vf;
	u16 num_alloc_vfs;		/* actual number of VFs allocated */
	u16 num_vfs_supported;		/* num VFs supported क्रम this PF */
	u16 num_qps_per_vf;
	u16 num_msix_per_vf;
	/* used to ratelimit the MDD event logging */
	अचिन्हित दीर्घ last_prपूर्णांकed_mdd_jअगरfies;
	DECLARE_BITMAP(malvfs, ICE_MAX_VF_COUNT);
	DECLARE_BITMAP(state, ICE_STATE_NBITS);
	DECLARE_BITMAP(flags, ICE_PF_FLAGS_NBITS);
	अचिन्हित दीर्घ *avail_txqs;	/* biपंचांगap to track PF Tx queue usage */
	अचिन्हित दीर्घ *avail_rxqs;	/* biपंचांगap to track PF Rx queue usage */
	अचिन्हित दीर्घ serv_पंचांगr_period;
	अचिन्हित दीर्घ serv_पंचांगr_prev;
	काष्ठा समयr_list serv_पंचांगr;
	काष्ठा work_काष्ठा serv_task;
	काष्ठा mutex avail_q_mutex;	/* protects access to avail_[rx|tx]qs */
	काष्ठा mutex sw_mutex;		/* lock क्रम protecting VSI alloc flow */
	काष्ठा mutex tc_mutex;		/* lock to protect TC changes */
	u32 msg_enable;

	/* spinlock to protect the AdminQ रुको list */
	spinlock_t aq_रुको_lock;
	काष्ठा hlist_head aq_रुको_list;
	रुको_queue_head_t aq_रुको_queue;

	u32 hw_csum_rx_error;
	u16 oicr_idx;		/* Other पूर्णांकerrupt cause MSIX vector index */
	u16 num_avail_sw_msix;	/* reमुख्यing MSIX SW vectors left unclaimed */
	u16 max_pf_txqs;	/* Total Tx queues PF wide */
	u16 max_pf_rxqs;	/* Total Rx queues PF wide */
	u16 num_lan_msix;	/* Total MSIX vectors क्रम base driver */
	u16 num_lan_tx;		/* num LAN Tx queues setup */
	u16 num_lan_rx;		/* num LAN Rx queues setup */
	u16 next_vsi;		/* Next मुक्त slot in pf->vsi[] - 0-based! */
	u16 num_alloc_vsi;
	u16 corer_count;	/* Core reset count */
	u16 globr_count;	/* Global reset count */
	u16 empr_count;		/* EMP reset count */
	u16 pfr_count;		/* PF reset count */

	u8 wol_ena : 1;		/* software state of WoL */
	u32 wakeup_reason;	/* last wakeup reason */
	काष्ठा ice_hw_port_stats stats;
	काष्ठा ice_hw_port_stats stats_prev;
	काष्ठा ice_hw hw;
	u8 stat_prev_loaded:1; /* has previous stats been loaded */
	u16 dcbx_cap;
	u32 tx_समयout_count;
	अचिन्हित दीर्घ tx_समयout_last_recovery;
	u32 tx_समयout_recovery_level;
	अक्षर पूर्णांक_name[ICE_INT_NAME_STR_LEN];
	u32 sw_पूर्णांक_count;

	__le64 nvm_phy_type_lo; /* NVM PHY type low */
	__le64 nvm_phy_type_hi; /* NVM PHY type high */
	काष्ठा ice_link_शेष_override_tlv link_dflt_override;
	काष्ठा ice_lag *lag; /* Link Aggregation inक्रमmation */

#घोषणा ICE_INVALID_AGG_NODE_ID		0
#घोषणा ICE_PF_AGG_NODE_ID_START	1
#घोषणा ICE_MAX_PF_AGG_NODES		32
	काष्ठा ice_agg_node pf_agg_node[ICE_MAX_PF_AGG_NODES];
#घोषणा ICE_VF_AGG_NODE_ID_START	65
#घोषणा ICE_MAX_VF_AGG_NODES		32
	काष्ठा ice_agg_node vf_agg_node[ICE_MAX_VF_AGG_NODES];
पूर्ण;

काष्ठा ice_netdev_priv अणु
	काष्ठा ice_vsi *vsi;
पूर्ण;

/**
 * ice_irq_dynamic_ena - Enable शेष पूर्णांकerrupt generation settings
 * @hw: poपूर्णांकer to HW काष्ठा
 * @vsi: poपूर्णांकer to VSI काष्ठा, can be शून्य
 * @q_vector: poपूर्णांकer to q_vector, can be शून्य
 */
अटल अंतरभूत व्योम
ice_irq_dynamic_ena(काष्ठा ice_hw *hw, काष्ठा ice_vsi *vsi,
		    काष्ठा ice_q_vector *q_vector)
अणु
	u32 vector = (vsi && q_vector) ? q_vector->reg_idx :
				((काष्ठा ice_pf *)hw->back)->oicr_idx;
	पूर्णांक itr = ICE_ITR_NONE;
	u32 val;

	/* clear the PBA here, as this function is meant to clean out all
	 * previous पूर्णांकerrupts and enable the पूर्णांकerrupt
	 */
	val = GLINT_DYN_CTL_INTENA_M | GLINT_DYN_CTL_CLEARPBA_M |
	      (itr << GLINT_DYN_CTL_ITR_INDX_S);
	अगर (vsi)
		अगर (test_bit(ICE_VSI_DOWN, vsi->state))
			वापस;
	wr32(hw, GLINT_DYN_CTL(vector), val);
पूर्ण

/**
 * ice_netdev_to_pf - Retrieve the PF काष्ठा associated with a netdev
 * @netdev: poपूर्णांकer to the netdev काष्ठा
 */
अटल अंतरभूत काष्ठा ice_pf *ice_netdev_to_pf(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);

	वापस np->vsi->back;
पूर्ण

अटल अंतरभूत bool ice_is_xdp_ena_vsi(काष्ठा ice_vsi *vsi)
अणु
	वापस !!vsi->xdp_prog;
पूर्ण

अटल अंतरभूत व्योम ice_set_ring_xdp(काष्ठा ice_ring *ring)
अणु
	ring->flags |= ICE_TX_FLAGS_RING_XDP;
पूर्ण

/**
 * ice_xsk_pool - get XSK buffer pool bound to a ring
 * @ring: ring to use
 *
 * Returns a poपूर्णांकer to xdp_umem काष्ठाure अगर there is a buffer pool present,
 * शून्य otherwise.
 */
अटल अंतरभूत काष्ठा xsk_buff_pool *ice_xsk_pool(काष्ठा ice_ring *ring)
अणु
	काष्ठा ice_vsi *vsi = ring->vsi;
	u16 qid = ring->q_index;

	अगर (ice_ring_is_xdp(ring))
		qid -= vsi->num_xdp_txq;

	अगर (!ice_is_xdp_ena_vsi(vsi) || !test_bit(qid, vsi->af_xdp_zc_qps))
		वापस शून्य;

	वापस xsk_get_pool_from_qid(vsi->netdev, qid);
पूर्ण

/**
 * ice_get_मुख्य_vsi - Get the PF VSI
 * @pf: PF instance
 *
 * वापसs pf->vsi[0], which by definition is the PF VSI
 */
अटल अंतरभूत काष्ठा ice_vsi *ice_get_मुख्य_vsi(काष्ठा ice_pf *pf)
अणु
	अगर (pf->vsi)
		वापस pf->vsi[0];

	वापस शून्य;
पूर्ण

/**
 * ice_get_ctrl_vsi - Get the control VSI
 * @pf: PF instance
 */
अटल अंतरभूत काष्ठा ice_vsi *ice_get_ctrl_vsi(काष्ठा ice_pf *pf)
अणु
	/* अगर pf->ctrl_vsi_idx is ICE_NO_VSI, control VSI was not set up */
	अगर (!pf->vsi || pf->ctrl_vsi_idx == ICE_NO_VSI)
		वापस शून्य;

	वापस pf->vsi[pf->ctrl_vsi_idx];
पूर्ण

/**
 * ice_set_sriov_cap - enable SRIOV in PF flags
 * @pf: PF काष्ठा
 */
अटल अंतरभूत व्योम ice_set_sriov_cap(काष्ठा ice_pf *pf)
अणु
	अगर (pf->hw.func_caps.common_cap.sr_iov_1_1)
		set_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags);
पूर्ण

/**
 * ice_clear_sriov_cap - disable SRIOV in PF flags
 * @pf: PF काष्ठा
 */
अटल अंतरभूत व्योम ice_clear_sriov_cap(काष्ठा ice_pf *pf)
अणु
	clear_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags);
पूर्ण

#घोषणा ICE_FD_STAT_CTR_BLOCK_COUNT	256
#घोषणा ICE_FD_STAT_PF_IDX(base_idx) \
			((base_idx) * ICE_FD_STAT_CTR_BLOCK_COUNT)
#घोषणा ICE_FD_SB_STAT_IDX(base_idx) ICE_FD_STAT_PF_IDX(base_idx)

bool netअगर_is_ice(काष्ठा net_device *dev);
पूर्णांक ice_vsi_setup_tx_rings(काष्ठा ice_vsi *vsi);
पूर्णांक ice_vsi_setup_rx_rings(काष्ठा ice_vsi *vsi);
पूर्णांक ice_vsi_खोलो_ctrl(काष्ठा ice_vsi *vsi);
व्योम ice_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम ice_set_ethtool_safe_mode_ops(काष्ठा net_device *netdev);
u16 ice_get_avail_txq_count(काष्ठा ice_pf *pf);
u16 ice_get_avail_rxq_count(काष्ठा ice_pf *pf);
पूर्णांक ice_vsi_recfg_qs(काष्ठा ice_vsi *vsi, पूर्णांक new_rx, पूर्णांक new_tx);
व्योम ice_update_vsi_stats(काष्ठा ice_vsi *vsi);
व्योम ice_update_pf_stats(काष्ठा ice_pf *pf);
पूर्णांक ice_up(काष्ठा ice_vsi *vsi);
पूर्णांक ice_करोwn(काष्ठा ice_vsi *vsi);
पूर्णांक ice_vsi_cfg(काष्ठा ice_vsi *vsi);
काष्ठा ice_vsi *ice_lb_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi);
पूर्णांक ice_prepare_xdp_rings(काष्ठा ice_vsi *vsi, काष्ठा bpf_prog *prog);
पूर्णांक ice_destroy_xdp_rings(काष्ठा ice_vsi *vsi);
पूर्णांक
ice_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
	     u32 flags);
पूर्णांक ice_set_rss_lut(काष्ठा ice_vsi *vsi, u8 *lut, u16 lut_size);
पूर्णांक ice_get_rss_lut(काष्ठा ice_vsi *vsi, u8 *lut, u16 lut_size);
पूर्णांक ice_set_rss_key(काष्ठा ice_vsi *vsi, u8 *seed);
पूर्णांक ice_get_rss_key(काष्ठा ice_vsi *vsi, u8 *seed);
व्योम ice_fill_rss_lut(u8 *lut, u16 rss_table_size, u16 rss_size);
पूर्णांक ice_schedule_reset(काष्ठा ice_pf *pf, क्रमागत ice_reset_req reset);
व्योम ice_prपूर्णांक_link_msg(काष्ठा ice_vsi *vsi, bool isup);
स्थिर अक्षर *ice_stat_str(क्रमागत ice_status stat_err);
स्थिर अक्षर *ice_aq_str(क्रमागत ice_aq_err aq_err);
bool ice_is_wol_supported(काष्ठा ice_hw *hw);
पूर्णांक
ice_fdir_ग_लिखो_fltr(काष्ठा ice_pf *pf, काष्ठा ice_fdir_fltr *input, bool add,
		    bool is_tun);
व्योम ice_vsi_manage_fdir(काष्ठा ice_vsi *vsi, bool ena);
पूर्णांक ice_add_fdir_ethtool(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक ice_del_fdir_ethtool(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक ice_get_ethtool_fdir_entry(काष्ठा ice_hw *hw, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक
ice_get_fdir_fltr_ids(काष्ठा ice_hw *hw, काष्ठा ethtool_rxnfc *cmd,
		      u32 *rule_locs);
व्योम ice_fdir_release_flows(काष्ठा ice_hw *hw);
व्योम ice_fdir_replay_flows(काष्ठा ice_hw *hw);
व्योम ice_fdir_replay_fltrs(काष्ठा ice_pf *pf);
पूर्णांक ice_fdir_create_dflt_rules(काष्ठा ice_pf *pf);
पूर्णांक ice_aq_रुको_क्रम_event(काष्ठा ice_pf *pf, u16 opcode, अचिन्हित दीर्घ समयout,
			  काष्ठा ice_rq_event_info *event);
पूर्णांक ice_खोलो(काष्ठा net_device *netdev);
पूर्णांक ice_खोलो_पूर्णांकernal(काष्ठा net_device *netdev);
पूर्णांक ice_stop(काष्ठा net_device *netdev);
व्योम ice_service_task_schedule(काष्ठा ice_pf *pf);

#पूर्ण_अगर /* _ICE_H_ */
