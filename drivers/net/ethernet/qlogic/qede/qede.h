<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QEDE_H_
#घोषणा _QEDE_H_
#समावेश <linux/compiler.h>
#समावेश <linux/version.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bpf.h>
#समावेश <net/xdp.h>
#समावेश <linux/qed/qede_rdma.h>
#समावेश <linux/पन.स>
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर
#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/eth_common.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_eth_अगर.h>

#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>

#घोषणा QEDE_MAJOR_VERSION		8
#घोषणा QEDE_MINOR_VERSION		37
#घोषणा QEDE_REVISION_VERSION		0
#घोषणा QEDE_ENGINEERING_VERSION	20
#घोषणा DRV_MODULE_VERSION __stringअगरy(QEDE_MAJOR_VERSION) "."	\
		__stringअगरy(QEDE_MINOR_VERSION) "."		\
		__stringअगरy(QEDE_REVISION_VERSION) "."		\
		__stringअगरy(QEDE_ENGINEERING_VERSION)

#घोषणा DRV_MODULE_SYM		qede

काष्ठा qede_stats_common अणु
	u64 no_buff_discards;
	u64 packet_too_big_discard;
	u64 ttl0_discard;
	u64 rx_ucast_bytes;
	u64 rx_mcast_bytes;
	u64 rx_bcast_bytes;
	u64 rx_ucast_pkts;
	u64 rx_mcast_pkts;
	u64 rx_bcast_pkts;
	u64 mftag_filter_discards;
	u64 mac_filter_discards;
	u64 gft_filter_drop;
	u64 tx_ucast_bytes;
	u64 tx_mcast_bytes;
	u64 tx_bcast_bytes;
	u64 tx_ucast_pkts;
	u64 tx_mcast_pkts;
	u64 tx_bcast_pkts;
	u64 tx_err_drop_pkts;
	u64 coalesced_pkts;
	u64 coalesced_events;
	u64 coalesced_पातs_num;
	u64 non_coalesced_pkts;
	u64 coalesced_bytes;
	u64 link_change_count;
	u64 ptp_skip_txts;

	/* port */
	u64 rx_64_byte_packets;
	u64 rx_65_to_127_byte_packets;
	u64 rx_128_to_255_byte_packets;
	u64 rx_256_to_511_byte_packets;
	u64 rx_512_to_1023_byte_packets;
	u64 rx_1024_to_1518_byte_packets;
	u64 rx_crc_errors;
	u64 rx_mac_crtl_frames;
	u64 rx_छोड़ो_frames;
	u64 rx_pfc_frames;
	u64 rx_align_errors;
	u64 rx_carrier_errors;
	u64 rx_oversize_packets;
	u64 rx_jabbers;
	u64 rx_undersize_packets;
	u64 rx_fragments;
	u64 tx_64_byte_packets;
	u64 tx_65_to_127_byte_packets;
	u64 tx_128_to_255_byte_packets;
	u64 tx_256_to_511_byte_packets;
	u64 tx_512_to_1023_byte_packets;
	u64 tx_1024_to_1518_byte_packets;
	u64 tx_छोड़ो_frames;
	u64 tx_pfc_frames;
	u64 brb_truncates;
	u64 brb_discards;
	u64 tx_mac_ctrl_frames;
पूर्ण;

काष्ठा qede_stats_bb अणु
	u64 rx_1519_to_1522_byte_packets;
	u64 rx_1519_to_2047_byte_packets;
	u64 rx_2048_to_4095_byte_packets;
	u64 rx_4096_to_9216_byte_packets;
	u64 rx_9217_to_16383_byte_packets;
	u64 tx_1519_to_2047_byte_packets;
	u64 tx_2048_to_4095_byte_packets;
	u64 tx_4096_to_9216_byte_packets;
	u64 tx_9217_to_16383_byte_packets;
	u64 tx_lpi_entry_count;
	u64 tx_total_collisions;
पूर्ण;

काष्ठा qede_stats_ah अणु
	u64 rx_1519_to_max_byte_packets;
	u64 tx_1519_to_max_byte_packets;
पूर्ण;

काष्ठा qede_stats अणु
	काष्ठा qede_stats_common common;

	जोड़ अणु
		काष्ठा qede_stats_bb bb;
		काष्ठा qede_stats_ah ah;
	पूर्ण;
पूर्ण;

काष्ठा qede_vlan अणु
	काष्ठा list_head list;
	u16 vid;
	bool configured;
पूर्ण;

काष्ठा qede_rdma_dev अणु
	काष्ठा qedr_dev *qedr_dev;
	काष्ठा list_head entry;
	काष्ठा list_head rdma_event_list;
	काष्ठा workqueue_काष्ठा *rdma_wq;
	काष्ठा kref refcnt;
	काष्ठा completion event_comp;
	bool exp_recovery;
पूर्ण;

काष्ठा qede_ptp;

#घोषणा QEDE_RFS_MAX_FLTR	256

क्रमागत qede_flags_bit अणु
	QEDE_FLAGS_IS_VF = 0,
	QEDE_FLAGS_LINK_REQUESTED,
	QEDE_FLAGS_PTP_TX_IN_PRORGESS,
	QEDE_FLAGS_TX_TIMESTAMPING_EN
पूर्ण;

#घोषणा QEDE_DUMP_MAX_ARGS 4
क्रमागत qede_dump_cmd अणु
	QEDE_DUMP_CMD_NONE = 0,
	QEDE_DUMP_CMD_NVM_CFG,
	QEDE_DUMP_CMD_GRCDUMP,
	QEDE_DUMP_CMD_MAX
पूर्ण;

काष्ठा qede_dump_info अणु
	क्रमागत qede_dump_cmd cmd;
	u8 num_args;
	u32 args[QEDE_DUMP_MAX_ARGS];
पूर्ण;

काष्ठा qede_coalesce अणु
	bool isvalid;
	u16 rxc;
	u16 txc;
पूर्ण;

काष्ठा qede_dev अणु
	काष्ठा qed_dev			*cdev;
	काष्ठा net_device		*ndev;
	काष्ठा pci_dev			*pdev;
	काष्ठा devlink			*devlink;

	u32				dp_module;
	u8				dp_level;

	अचिन्हित दीर्घ			flags;
#घोषणा IS_VF(edev)			test_bit(QEDE_FLAGS_IS_VF, \
						 &(edev)->flags)

	स्थिर काष्ठा qed_eth_ops	*ops;
	काष्ठा qede_ptp			*ptp;
	u64				ptp_skip_txts;

	काष्ठा qed_dev_eth_info		dev_info;
#घोषणा QEDE_MAX_RSS_CNT(edev)		((edev)->dev_info.num_queues)
#घोषणा QEDE_MAX_TSS_CNT(edev)		((edev)->dev_info.num_queues)
#घोषणा QEDE_IS_BB(edev) \
	((edev)->dev_info.common.dev_type == QED_DEV_TYPE_BB)
#घोषणा QEDE_IS_AH(edev) \
	((edev)->dev_info.common.dev_type == QED_DEV_TYPE_AH)

	काष्ठा qede_fastpath		*fp_array;
	काष्ठा qede_coalesce            *coal_entry;
	u8				req_num_tx;
	u8				fp_num_tx;
	u8				req_num_rx;
	u8				fp_num_rx;
	u16				req_queues;
	u16				num_queues;
	u16				total_xdp_queues;

#घोषणा QEDE_QUEUE_CNT(edev)		((edev)->num_queues)
#घोषणा QEDE_RSS_COUNT(edev)		((edev)->num_queues - (edev)->fp_num_tx)
#घोषणा QEDE_RX_QUEUE_IDX(edev, i)	(i)
#घोषणा QEDE_TSS_COUNT(edev)		((edev)->num_queues - (edev)->fp_num_rx)

	काष्ठा qed_पूर्णांक_info		पूर्णांक_info;

	/* Smaller निजी variant of the RTNL lock */
	काष्ठा mutex			qede_lock;
	u32				state; /* Protected by qede_lock */
	u16				rx_buf_size;
	u32				rx_copyअवरोध;

	/* L2 header size + 2*VLANs (8 bytes) + LLC SNAP (8 bytes) */
#घोषणा ETH_OVERHEAD			(ETH_HLEN + 8 + 8)
	/* Max supported alignment is 256 (8 shअगरt)
	 * minimal alignment shअगरt 6 is optimal क्रम 57xxx HW perक्रमmance
	 */
#घोषणा QEDE_RX_ALIGN_SHIFT		max(6, min(8, L1_CACHE_SHIFT))
	/* We assume skb_build() uses माप(काष्ठा skb_shared_info) bytes
	 * at the end of skb->data, to aव्योम wasting a full cache line.
	 * This reduces memory use (skb->truesize).
	 */
#घोषणा QEDE_FW_RX_ALIGN_END					\
	max_t(u64, 1UL << QEDE_RX_ALIGN_SHIFT,			\
	      SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

	काष्ठा qede_stats		stats;

	/* Bitfield to track initialized RSS params */
	u32				rss_params_inited;
#घोषणा QEDE_RSS_INसूची_INITED		BIT(0)
#घोषणा QEDE_RSS_KEY_INITED		BIT(1)
#घोषणा QEDE_RSS_CAPS_INITED		BIT(2)

	u16				rss_ind_table[128];
	u32				rss_key[10];
	u8				rss_caps;

	/* Both must be a घातer of two */
	u16				q_num_rx_buffers;
	u16				q_num_tx_buffers;

	bool				gro_disable;

	काष्ठा list_head		vlan_list;
	u16				configured_vlans;
	u16				non_configured_vlans;
	bool				accept_any_vlan;

	काष्ठा delayed_work		sp_task;
	अचिन्हित दीर्घ			sp_flags;
	u16				vxlan_dst_port;
	u16				geneve_dst_port;

	काष्ठा qede_arfs		*arfs;
	bool				wol_enabled;

	काष्ठा qede_rdma_dev		rdma_info;

	काष्ठा bpf_prog			*xdp_prog;

	क्रमागत qed_hw_err_type		last_err_type;
	अचिन्हित दीर्घ			err_flags;
#घोषणा QEDE_ERR_IS_HANDLED		31
#घोषणा QEDE_ERR_ATTN_CLR_EN		0
#घोषणा QEDE_ERR_GET_DBG_INFO		1
#घोषणा QEDE_ERR_IS_RECOVERABLE		2
#घोषणा QEDE_ERR_WARN			3

	काष्ठा qede_dump_info		dump_info;
पूर्ण;

क्रमागत QEDE_STATE अणु
	QEDE_STATE_CLOSED,
	QEDE_STATE_OPEN,
	QEDE_STATE_RECOVERY,
पूर्ण;

#घोषणा HILO_U64(hi, lo)		((((u64)(hi)) << 32) + (lo))

#घोषणा	MAX_NUM_TC	8
#घोषणा	MAX_NUM_PRI	8

/* The driver supports the new build_skb() API:
 * RX ring buffer contains poपूर्णांकer to kदो_स्मृति() data only,
 * skb are built only after the frame was DMA-ed.
 */
काष्ठा sw_rx_data अणु
	काष्ठा page *data;
	dma_addr_t mapping;
	अचिन्हित पूर्णांक page_offset;
पूर्ण;

क्रमागत qede_agg_state अणु
	QEDE_AGG_STATE_NONE  = 0,
	QEDE_AGG_STATE_START = 1,
	QEDE_AGG_STATE_ERROR = 2
पूर्ण;

काष्ठा qede_agg_info अणु
	/* rx_buf is a data buffer that can be placed / consumed from rx bd
	 * chain. It has two purposes: We will pपुनः_स्मृतिate the data buffer
	 * क्रम each aggregation when we खोलो the पूर्णांकerface and will place this
	 * buffer on the rx-bd-ring when we receive TPA_START. We करोn't want
	 * to be in a state where allocation fails, as we can't reuse the
	 * consumer buffer in the rx-chain since FW may still be writing to it
	 * (since header needs to be modअगरied क्रम TPA).
	 * The second purpose is to keep a poपूर्णांकer to the bd buffer during
	 * aggregation.
	 */
	काष्ठा sw_rx_data buffer;
	काष्ठा sk_buff *skb;

	/* We need some काष्ठाs from the start cookie until termination */
	u16 vlan_tag;

	bool tpa_start_fail;
	u8 state;
	u8 frag_id;

	u8 tunnel_type;
पूर्ण;

काष्ठा qede_rx_queue अणु
	__le16 *hw_cons_ptr;
	व्योम __iomem *hw_rxq_prod_addr;

	/* Required क्रम the allocation of replacement buffers */
	काष्ठा device *dev;

	काष्ठा bpf_prog *xdp_prog;

	u16 sw_rx_cons;
	u16 sw_rx_prod;

	u16 filled_buffers;
	u8 data_direction;
	u8 rxq_id;

	/* Used once per each NAPI run */
	u16 num_rx_buffers;

	u16 rx_headroom;

	u32 rx_buf_size;
	u32 rx_buf_seg_size;

	काष्ठा sw_rx_data *sw_rx_ring;
	काष्ठा qed_chain rx_bd_ring;
	काष्ठा qed_chain rx_comp_ring ____cacheline_aligned;

	/* GRO */
	काष्ठा qede_agg_info tpa_info[ETH_TPA_MAX_AGGS_NUM];

	/* Used once per each NAPI run */
	u64 rcv_pkts;

	u64 rx_hw_errors;
	u64 rx_alloc_errors;
	u64 rx_ip_frags;

	u64 xdp_no_pass;

	व्योम *handle;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

जोड़ db_prod अणु
	काष्ठा eth_db_data data;
	u32		raw;
पूर्ण;

काष्ठा sw_tx_bd अणु
	काष्ठा sk_buff *skb;
	u8 flags;
/* Set on the first BD descriptor when there is a split BD */
#घोषणा QEDE_TSO_SPLIT_BD		BIT(0)
पूर्ण;

काष्ठा sw_tx_xdp अणु
	काष्ठा page			*page;
	काष्ठा xdp_frame		*xdpf;
	dma_addr_t			mapping;
पूर्ण;

काष्ठा qede_tx_queue अणु
	u8				is_xdp;
	bool				is_legacy;
	u16				sw_tx_cons;
	u16				sw_tx_prod;
	u16				num_tx_buffers; /* Slowpath only */

	u64				xmit_pkts;
	u64				stopped_cnt;
	u64				tx_mem_alloc_err;

	__le16				*hw_cons_ptr;

	/* Needed क्रम the mapping of packets */
	काष्ठा device			*dev;

	व्योम __iomem			*करोorbell_addr;
	जोड़ db_prod			tx_db;

	/* Spinlock क्रम XDP queues in हाल of XDP_REसूचीECT */
	spinlock_t			xdp_tx_lock;

	पूर्णांक				index; /* Slowpath only */
#घोषणा QEDE_TXQ_XDP_TO_IDX(edev, txq)	((txq)->index - \
					 QEDE_MAX_TSS_CNT(edev))
#घोषणा QEDE_TXQ_IDX_TO_XDP(edev, idx)	((idx) + QEDE_MAX_TSS_CNT(edev))
#घोषणा QEDE_NDEV_TXQ_ID_TO_FP_ID(edev, idx)	((edev)->fp_num_rx + \
						 ((idx) % QEDE_TSS_COUNT(edev)))
#घोषणा QEDE_NDEV_TXQ_ID_TO_TXQ_COS(edev, idx)	((idx) / QEDE_TSS_COUNT(edev))
#घोषणा QEDE_TXQ_TO_NDEV_TXQ_ID(edev, txq)	((QEDE_TSS_COUNT(edev) * \
						 (txq)->cos) + (txq)->index)
#घोषणा QEDE_NDEV_TXQ_ID_TO_TXQ(edev, idx)	\
	(&((edev)->fp_array[QEDE_NDEV_TXQ_ID_TO_FP_ID(edev, idx)].txq \
	[QEDE_NDEV_TXQ_ID_TO_TXQ_COS(edev, idx)]))
#घोषणा QEDE_FP_TC0_TXQ(fp)		(&((fp)->txq[0]))

	/* Regular Tx requires skb + metadata क्रम release purpose,
	 * जबतक XDP requires the pages and the mapped address.
	 */
	जोड़ अणु
		काष्ठा sw_tx_bd		*skbs;
		काष्ठा sw_tx_xdp	*xdp;
	पूर्ण				sw_tx_ring;

	काष्ठा qed_chain		tx_pbl;

	/* Slowpath; Should be kept in end [unless missing padding] */
	व्योम				*handle;
	u16				cos;
	u16				ndev_txq_id;
पूर्ण;

#घोषणा BD_UNMAP_ADDR(bd)		HILO_U64(le32_to_cpu((bd)->addr.hi), \
						 le32_to_cpu((bd)->addr.lo))
#घोषणा BD_SET_UNMAP_ADDR_LEN(bd, maddr, len)				\
	करो अणु								\
		(bd)->addr.hi = cpu_to_le32(upper_32_bits(maddr));	\
		(bd)->addr.lo = cpu_to_le32(lower_32_bits(maddr));	\
		(bd)->nbytes = cpu_to_le16(len);			\
	पूर्ण जबतक (0)
#घोषणा BD_UNMAP_LEN(bd)		(le16_to_cpu((bd)->nbytes))

काष्ठा qede_fastpath अणु
	काष्ठा qede_dev			*edev;

	u8				type;
#घोषणा QEDE_FASTPATH_TX		BIT(0)
#घोषणा QEDE_FASTPATH_RX		BIT(1)
#घोषणा QEDE_FASTPATH_XDP		BIT(2)
#घोषणा QEDE_FASTPATH_COMBINED		(QEDE_FASTPATH_TX | QEDE_FASTPATH_RX)

	u8				id;

	u8				xdp_xmit;
#घोषणा QEDE_XDP_TX			BIT(0)
#घोषणा QEDE_XDP_REसूचीECT		BIT(1)

	काष्ठा napi_काष्ठा		napi;
	काष्ठा qed_sb_info		*sb_info;
	काष्ठा qede_rx_queue		*rxq;
	काष्ठा qede_tx_queue		*txq;
	काष्ठा qede_tx_queue		*xdp_tx;

	अक्षर				name[IFNAMSIZ + 8];
पूर्ण;

/* Debug prपूर्णांक definitions */
#घोषणा DP_NAME(edev)			netdev_name((edev)->ndev)

#घोषणा XMIT_PLAIN			0
#घोषणा XMIT_L4_CSUM			BIT(0)
#घोषणा XMIT_LSO			BIT(1)
#घोषणा XMIT_ENC			BIT(2)
#घोषणा XMIT_ENC_GSO_L4_CSUM		BIT(3)

#घोषणा QEDE_CSUM_ERROR			BIT(0)
#घोषणा QEDE_CSUM_UNNECESSARY		BIT(1)
#घोषणा QEDE_TUNN_CSUM_UNNECESSARY	BIT(2)

#घोषणा QEDE_SP_RECOVERY		0
#घोषणा QEDE_SP_RX_MODE			1
#घोषणा QEDE_SP_RSVD1                   2
#घोषणा QEDE_SP_RSVD2                   3
#घोषणा QEDE_SP_HW_ERR                  4
#घोषणा QEDE_SP_ARFS_CONFIG             5
#घोषणा QEDE_SP_AER			7

#अगर_घोषित CONFIG_RFS_ACCEL
पूर्णांक qede_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
		       u16 rxq_index, u32 flow_id);
#घोषणा QEDE_SP_TASK_POLL_DELAY	(5 * HZ)
#पूर्ण_अगर

व्योम qede_process_arfs_filters(काष्ठा qede_dev *edev, bool मुक्त_fltr);
व्योम qede_poll_क्रम_मुक्तing_arfs_filters(काष्ठा qede_dev *edev);
व्योम qede_arfs_filter_op(व्योम *dev, व्योम *filter, u8 fw_rc);
व्योम qede_मुक्त_arfs(काष्ठा qede_dev *edev);
पूर्णांक qede_alloc_arfs(काष्ठा qede_dev *edev);
पूर्णांक qede_add_cls_rule(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info);
पूर्णांक qede_delete_flow_filter(काष्ठा qede_dev *edev, u64 cookie);
पूर्णांक qede_get_cls_rule_entry(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक qede_get_cls_rule_all(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info,
			  u32 *rule_locs);
पूर्णांक qede_get_arfs_filter_count(काष्ठा qede_dev *edev);

काष्ठा qede_reload_args अणु
	व्योम (*func)(काष्ठा qede_dev *edev, काष्ठा qede_reload_args *args);
	जोड़ अणु
		netdev_features_t features;
		काष्ठा bpf_prog *new_prog;
		u16 mtu;
	पूर्ण u;
पूर्ण;

/* Datapath functions definition */
netdev_tx_t qede_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev);
पूर्णांक qede_xdp_transmit(काष्ठा net_device *dev, पूर्णांक n_frames,
		      काष्ठा xdp_frame **frames, u32 flags);
u16 qede_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		      काष्ठा net_device *sb_dev);
netdev_features_t qede_features_check(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      netdev_features_t features);
पूर्णांक qede_alloc_rx_buffer(काष्ठा qede_rx_queue *rxq, bool allow_lazy);
पूर्णांक qede_मुक्त_tx_pkt(काष्ठा qede_dev *edev,
		     काष्ठा qede_tx_queue *txq, पूर्णांक *len);
पूर्णांक qede_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
irqवापस_t qede_msix_fp_पूर्णांक(पूर्णांक irq, व्योम *fp_cookie);

/* Filtering function definitions */
व्योम qede_क्रमce_mac(व्योम *dev, u8 *mac, bool क्रमced);
व्योम qede_udp_ports_update(व्योम *dev, u16 vxlan_port, u16 geneve_port);
पूर्णांक qede_set_mac_addr(काष्ठा net_device *ndev, व्योम *p);

पूर्णांक qede_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid);
पूर्णांक qede_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid);
व्योम qede_vlan_mark_nonconfigured(काष्ठा qede_dev *edev);
पूर्णांक qede_configure_vlan_filters(काष्ठा qede_dev *edev);

netdev_features_t qede_fix_features(काष्ठा net_device *dev,
				    netdev_features_t features);
पूर्णांक qede_set_features(काष्ठा net_device *dev, netdev_features_t features);
व्योम qede_set_rx_mode(काष्ठा net_device *ndev);
व्योम qede_config_rx_mode(काष्ठा net_device *ndev);
व्योम qede_fill_rss_params(काष्ठा qede_dev *edev,
			  काष्ठा qed_update_vport_rss_params *rss, u8 *update);

व्योम qede_udp_tunnel_add(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti);
व्योम qede_udp_tunnel_del(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti);

पूर्णांक qede_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp);

#अगर_घोषित CONFIG_DCB
व्योम qede_set_dcbnl_ops(काष्ठा net_device *ndev);
#पूर्ण_अगर

व्योम qede_config_debug(uपूर्णांक debug, u32 *p_dp_module, u8 *p_dp_level);
व्योम qede_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम qede_set_udp_tunnels(काष्ठा qede_dev *edev);
व्योम qede_reload(काष्ठा qede_dev *edev,
		 काष्ठा qede_reload_args *args, bool is_locked);
पूर्णांक qede_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);
व्योम qede_fill_by_demand_stats(काष्ठा qede_dev *edev);
व्योम __qede_lock(काष्ठा qede_dev *edev);
व्योम __qede_unlock(काष्ठा qede_dev *edev);
bool qede_has_rx_work(काष्ठा qede_rx_queue *rxq);
पूर्णांक qede_txq_has_work(काष्ठा qede_tx_queue *txq);
व्योम qede_recycle_rx_bd_ring(काष्ठा qede_rx_queue *rxq, u8 count);
व्योम qede_update_rx_prod(काष्ठा qede_dev *edev, काष्ठा qede_rx_queue *rxq);
पूर्णांक qede_add_tc_flower_fltr(काष्ठा qede_dev *edev, __be16 proto,
			    काष्ठा flow_cls_offload *f);

व्योम qede_क्रमced_speed_maps_init(व्योम);
पूर्णांक qede_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *coal);
पूर्णांक qede_set_per_coalesce(काष्ठा net_device *dev, u32 queue,
			  काष्ठा ethtool_coalesce *coal);

#घोषणा RX_RING_SIZE_POW	13
#घोषणा RX_RING_SIZE		((u16)BIT(RX_RING_SIZE_POW))
#घोषणा NUM_RX_BDS_MAX		(RX_RING_SIZE - 1)
#घोषणा NUM_RX_BDS_MIN		128
#घोषणा NUM_RX_BDS_KDUMP_MIN	63
#घोषणा NUM_RX_BDS_DEF		((u16)BIT(10) - 1)

#घोषणा TX_RING_SIZE_POW	13
#घोषणा TX_RING_SIZE		((u16)BIT(TX_RING_SIZE_POW))
#घोषणा NUM_TX_BDS_MAX		(TX_RING_SIZE - 1)
#घोषणा NUM_TX_BDS_MIN		128
#घोषणा NUM_TX_BDS_KDUMP_MIN	63
#घोषणा NUM_TX_BDS_DEF		NUM_TX_BDS_MAX

#घोषणा QEDE_MIN_PKT_LEN		64
#घोषणा QEDE_RX_HDR_SIZE		256
#घोषणा QEDE_MAX_JUMBO_PACKET_SIZE	9600
#घोषणा	क्रम_each_queue(i) क्रम (i = 0; i < edev->num_queues; i++)
#घोषणा क्रम_each_cos_in_txq(edev, var) \
	क्रम ((var) = 0; (var) < (edev)->dev_info.num_tc; (var)++)

#पूर्ण_अगर /* _QEDE_H_ */
