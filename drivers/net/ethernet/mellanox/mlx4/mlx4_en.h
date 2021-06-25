<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित _MLX4_EN_H_
#घोषणा _MLX4_EN_H_

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/net_tstamp.h>
#अगर_घोषित CONFIG_MLX4_EN_DCB
#समावेश <linux/dcbnl.h>
#पूर्ण_अगर
#समावेश <linux/cpu_rmap.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/irq.h>
#समावेश <net/xdp.h>

#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/mlx4/cq.h>
#समावेश <linux/mlx4/srq.h>
#समावेश <linux/mlx4/करोorbell.h>
#समावेश <linux/mlx4/cmd.h>

#समावेश "en_port.h"
#समावेश "mlx4_stats.h"

#घोषणा DRV_NAME	"mlx4_en"
#घोषणा DRV_VERSION	"4.0-0"

#घोषणा MLX4_EN_MSG_LEVEL	(NETIF_MSG_LINK | NETIF_MSG_IFDOWN)

/*
 * Device स्थिरants
 */


#घोषणा MLX4_EN_PAGE_SHIFT	12
#घोषणा MLX4_EN_PAGE_SIZE	(1 << MLX4_EN_PAGE_SHIFT)
#घोषणा DEF_RX_RINGS		16
#घोषणा MAX_RX_RINGS		128
#घोषणा MIN_RX_RINGS		1
#घोषणा LOG_TXBB_SIZE		6
#घोषणा TXBB_SIZE		BIT(LOG_TXBB_SIZE)
#घोषणा HEADROOM		(2048 / TXBB_SIZE + 1)
#घोषणा STAMP_STRIDE		64
#घोषणा STAMP_DWORDS		(STAMP_STRIDE / 4)
#घोषणा STAMP_SHIFT		31
#घोषणा STAMP_VAL		0x7fffffff
#घोषणा STATS_DELAY		(HZ / 4)
#घोषणा SERVICE_TASK_DELAY	(HZ / 4)
#घोषणा MAX_NUM_OF_FS_RULES	256

#घोषणा MLX4_EN_FILTER_HASH_SHIFT 4
#घोषणा MLX4_EN_FILTER_EXPIRY_QUOTA 60

/* Typical TSO descriptor with 16 gather entries is 352 bytes... */
#घोषणा MAX_DESC_SIZE		512
#घोषणा MAX_DESC_TXBBS		(MAX_DESC_SIZE / TXBB_SIZE)

/*
 * OS related स्थिरants and tunables
 */

#घोषणा MLX4_EN_PRIV_FLAGS_BLUEFLAME 1
#घोषणा MLX4_EN_PRIV_FLAGS_PHV	     2

#घोषणा MLX4_EN_WATCHDOG_TIMEOUT	(15 * HZ)

/* Use the maximum between 16384 and a single page */
#घोषणा MLX4_EN_ALLOC_SIZE	PAGE_ALIGN(16384)

#घोषणा MLX4_EN_MAX_RX_FRAGS	4

/* Maximum ring sizes */
#घोषणा MLX4_EN_MAX_TX_SIZE	8192
#घोषणा MLX4_EN_MAX_RX_SIZE	8192

/* Minimum ring size क्रम our page-allocation scheme to work */
#घोषणा MLX4_EN_MIN_RX_SIZE	(MLX4_EN_ALLOC_SIZE / SMP_CACHE_BYTES)
#घोषणा MLX4_EN_MIN_TX_SIZE	(4096 / TXBB_SIZE)

#घोषणा MLX4_EN_SMALL_PKT_SIZE		64
#घोषणा MLX4_EN_MIN_TX_RING_P_UP	1
#घोषणा MLX4_EN_MAX_TX_RING_P_UP	32
#घोषणा MLX4_EN_NUM_UP_LOW		1
#घोषणा MLX4_EN_NUM_UP_HIGH		8
#घोषणा MLX4_EN_DEF_RX_RING_SIZE  	1024
#घोषणा MLX4_EN_DEF_TX_RING_SIZE	MLX4_EN_DEF_RX_RING_SIZE
#घोषणा MAX_TX_RINGS			(MLX4_EN_MAX_TX_RING_P_UP * \
					 MLX4_EN_NUM_UP_HIGH)

#घोषणा MLX4_EN_DEFAULT_TX_WORK		256

/* Target number of packets to coalesce with पूर्णांकerrupt moderation */
#घोषणा MLX4_EN_RX_COAL_TARGET	44
#घोषणा MLX4_EN_RX_COAL_TIME	0x10

#घोषणा MLX4_EN_TX_COAL_PKTS	16
#घोषणा MLX4_EN_TX_COAL_TIME	0x10

#घोषणा MLX4_EN_MAX_COAL_PKTS	U16_MAX
#घोषणा MLX4_EN_MAX_COAL_TIME	U16_MAX

#घोषणा MLX4_EN_RX_RATE_LOW		400000
#घोषणा MLX4_EN_RX_COAL_TIME_LOW	0
#घोषणा MLX4_EN_RX_RATE_HIGH		450000
#घोषणा MLX4_EN_RX_COAL_TIME_HIGH	128
#घोषणा MLX4_EN_RX_SIZE_THRESH		1024
#घोषणा MLX4_EN_RX_RATE_THRESH		(1000000 / MLX4_EN_RX_COAL_TIME_HIGH)
#घोषणा MLX4_EN_SAMPLE_INTERVAL		0
#घोषणा MLX4_EN_AVG_PKT_SMALL		256

#घोषणा MLX4_EN_AUTO_CONF	0xffff

#घोषणा MLX4_EN_DEF_RX_PAUSE	1
#घोषणा MLX4_EN_DEF_TX_PAUSE	1

/* Interval between successive polls in the Tx routine when polling is used
   instead of पूर्णांकerrupts (in per-core Tx rings) - should be घातer of 2 */
#घोषणा MLX4_EN_TX_POLL_MODER	16
#घोषणा MLX4_EN_TX_POLL_TIMEOUT	(HZ / 4)

#घोषणा SMALL_PACKET_SIZE      (256 - NET_IP_ALIGN)
#घोषणा HEADER_COPY_SIZE       (128 - NET_IP_ALIGN)
#घोषणा MLX4_LOOPBACK_TEST_PAYLOAD (HEADER_COPY_SIZE - ETH_HLEN)
#घोषणा PREAMBLE_LEN           8
#घोषणा MLX4_SELFTEST_LB_MIN_MTU (MLX4_LOOPBACK_TEST_PAYLOAD + NET_IP_ALIGN + \
				  ETH_HLEN + PREAMBLE_LEN)

/* VLAN_HLEN is added twice,to support skb vlan tagged with multiple
 * headers. (For example: ETH_P_8021Q and ETH_P_8021AD).
 */
#घोषणा MLX4_EN_EFF_MTU(mtu)	((mtu) + ETH_HLEN + (2 * VLAN_HLEN))
#घोषणा ETH_BCAST		0xffffffffffffULL

#घोषणा MLX4_EN_LOOPBACK_RETRIES	5
#घोषणा MLX4_EN_LOOPBACK_TIMEOUT	100

/* Constants क्रम TX flow */
क्रमागत अणु
	MAX_INLINE = 104, /* 128 - 16 - 4 - 4 */
	MAX_BF = 256,
	MIN_PKT_LEN = 17,
पूर्ण;

/*
 * Configurables
 */

क्रमागत cq_type अणु
	/* keep tx types first */
	TX,
	TX_XDP,
#घोषणा MLX4_EN_NUM_TX_TYPES (TX_XDP + 1)
	RX,
पूर्ण;


/*
 * Useful macros
 */
#घोषणा ROUNDUP_LOG2(x)		ilog2(roundup_घात_of_two(x))
#घोषणा XNOR(x, y)		(!(x) == !(y))


काष्ठा mlx4_en_tx_info अणु
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा page *page;
	पूर्ण;
	dma_addr_t	map0_dma;
	u32		map0_byte_count;
	u32		nr_txbb;
	u32		nr_bytes;
	u8		linear;
	u8		data_offset;
	u8		inl;
	u8		ts_requested;
	u8		nr_maps;
पूर्ण ____cacheline_aligned_in_smp;


#घोषणा MLX4_EN_BIT_DESC_OWN	0x80000000
#घोषणा CTRL_SIZE	माप(काष्ठा mlx4_wqe_ctrl_seg)
#घोषणा MLX4_EN_MEMTYPE_PAD	0x100
#घोषणा DS_SIZE		माप(काष्ठा mlx4_wqe_data_seg)


काष्ठा mlx4_en_tx_desc अणु
	काष्ठा mlx4_wqe_ctrl_seg ctrl;
	जोड़ अणु
		काष्ठा mlx4_wqe_data_seg data; /* at least one data segment */
		काष्ठा mlx4_wqe_lso_seg lso;
		काष्ठा mlx4_wqe_अंतरभूत_seg inl;
	पूर्ण;
पूर्ण;

#घोषणा MLX4_EN_USE_SRQ		0x01000000

#घोषणा MLX4_EN_CX3_LOW_ID	0x1000
#घोषणा MLX4_EN_CX3_HIGH_ID	0x1005

काष्ठा mlx4_en_rx_alloc अणु
	काष्ठा page	*page;
	dma_addr_t	dma;
	u32		page_offset;
पूर्ण;

#घोषणा MLX4_EN_CACHE_SIZE (2 * NAPI_POLL_WEIGHT)

काष्ठा mlx4_en_page_cache अणु
	u32 index;
	काष्ठा अणु
		काष्ठा page	*page;
		dma_addr_t	dma;
	पूर्ण buf[MLX4_EN_CACHE_SIZE];
पूर्ण;

क्रमागत अणु
	MLX4_EN_TX_RING_STATE_RECOVERING,
पूर्ण;

काष्ठा mlx4_en_priv;

काष्ठा mlx4_en_tx_ring अणु
	/* cache line used and dirtied in tx completion
	 * (mlx4_en_मुक्त_tx_buf())
	 */
	u32			last_nr_txbb;
	u32			cons;
	अचिन्हित दीर्घ		wake_queue;
	काष्ठा netdev_queue	*tx_queue;
	u32			(*मुक्त_tx_desc)(काष्ठा mlx4_en_priv *priv,
						काष्ठा mlx4_en_tx_ring *ring,
						पूर्णांक index,
						u64 बारtamp, पूर्णांक napi_mode);
	काष्ठा mlx4_en_rx_ring	*recycle_ring;

	/* cache line used and dirtied in mlx4_en_xmit() */
	u32			prod ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक		tx_dropped;
	अचिन्हित दीर्घ		bytes;
	अचिन्हित दीर्घ		packets;
	अचिन्हित दीर्घ		tx_csum;
	अचिन्हित दीर्घ		tso_packets;
	अचिन्हित दीर्घ		xmit_more;
	काष्ठा mlx4_bf		bf;

	/* Following part should be mostly पढ़ो */
	__be32			करोorbell_qpn;
	__be32			mr_key;
	u32			size; /* number of TXBBs */
	u32			size_mask;
	u32			full_size;
	u32			buf_size;
	व्योम			*buf;
	काष्ठा mlx4_en_tx_info	*tx_info;
	पूर्णांक			qpn;
	u8			queue_index;
	bool			bf_enabled;
	bool			bf_alloced;
	u8			hwtstamp_tx_type;
	u8			*bounce_buf;

	/* Not used in fast path
	 * Only queue_stopped might be used अगर BQL is not properly working.
	 */
	अचिन्हित दीर्घ		queue_stopped;
	अचिन्हित दीर्घ		state;
	काष्ठा mlx4_hwq_resources sp_wqres;
	काष्ठा mlx4_qp		sp_qp;
	काष्ठा mlx4_qp_context	sp_context;
	cpumask_t		sp_affinity_mask;
	क्रमागत mlx4_qp_state	sp_qp_state;
	u16			sp_stride;
	u16			sp_cqn;	/* index of port CQ associated with this ring */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx4_en_rx_desc अणु
	/* actual number of entries depends on rx ring stride */
	काष्ठा mlx4_wqe_data_seg data[0];
पूर्ण;

काष्ठा mlx4_en_rx_ring अणु
	काष्ठा mlx4_hwq_resources wqres;
	u32 size ;	/* number of Rx descs*/
	u32 actual_size;
	u32 size_mask;
	u16 stride;
	u16 log_stride;
	u16 cqn;	/* index of port CQ associated with this ring */
	u32 prod;
	u32 cons;
	u32 buf_size;
	u8  fcs_del;
	व्योम *buf;
	व्योम *rx_info;
	काष्ठा bpf_prog __rcu *xdp_prog;
	काष्ठा mlx4_en_page_cache page_cache;
	अचिन्हित दीर्घ bytes;
	अचिन्हित दीर्घ packets;
	अचिन्हित दीर्घ csum_ok;
	अचिन्हित दीर्घ csum_none;
	अचिन्हित दीर्घ csum_complete;
	अचिन्हित दीर्घ rx_alloc_pages;
	अचिन्हित दीर्घ xdp_drop;
	अचिन्हित दीर्घ xdp_tx;
	अचिन्हित दीर्घ xdp_tx_full;
	अचिन्हित दीर्घ dropped;
	पूर्णांक hwtstamp_rx_filter;
	cpumask_var_t affinity_mask;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

काष्ठा mlx4_en_cq अणु
	काष्ठा mlx4_cq          mcq;
	काष्ठा mlx4_hwq_resources wqres;
	पूर्णांक                     ring;
	काष्ठा net_device      *dev;
	जोड़ अणु
		काष्ठा napi_काष्ठा napi;
		bool               xdp_busy;
	पूर्ण;
	पूर्णांक size;
	पूर्णांक buf_size;
	पूर्णांक vector;
	क्रमागत cq_type type;
	u16 moder_समय;
	u16 moder_cnt;
	काष्ठा mlx4_cqe *buf;
#घोषणा MLX4_EN_OPCODE_ERROR	0x1e

	स्थिर काष्ठा cpumask *aff_mask;
पूर्ण;

काष्ठा mlx4_en_port_profile अणु
	u32 flags;
	u32 tx_ring_num[MLX4_EN_NUM_TX_TYPES];
	u32 rx_ring_num;
	u32 tx_ring_size;
	u32 rx_ring_size;
	u8 num_tx_rings_p_up;
	u8 rx_छोड़ो;
	u8 rx_ppp;
	u8 tx_छोड़ो;
	u8 tx_ppp;
	u8 num_up;
	पूर्णांक rss_rings;
	पूर्णांक अंतरभूत_thold;
	काष्ठा hwtstamp_config hwtstamp_config;
पूर्ण;

काष्ठा mlx4_en_profile अणु
	पूर्णांक udp_rss;
	u8 rss_mask;
	u32 active_ports;
	u32 small_pkt_पूर्णांक;
	u8 no_reset;
	u8 max_num_tx_rings_p_up;
	काष्ठा mlx4_en_port_profile prof[MLX4_MAX_PORTS + 1];
पूर्ण;

काष्ठा mlx4_en_dev अणु
	काष्ठा mlx4_dev         *dev;
	काष्ठा pci_dev		*pdev;
	काष्ठा mutex		state_lock;
	काष्ठा net_device       *pndev[MLX4_MAX_PORTS + 1];
	काष्ठा net_device       *upper[MLX4_MAX_PORTS + 1];
	u32                     port_cnt;
	bool			device_up;
	काष्ठा mlx4_en_profile  profile;
	u32			LSO_support;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा device           *dma_device;
	व्योम __iomem            *uar_map;
	काष्ठा mlx4_uar         priv_uar;
	काष्ठा mlx4_mr		mr;
	u32                     priv_pdn;
	spinlock_t              uar_lock;
	u8			mac_हटाओd[MLX4_MAX_PORTS + 1];
	u32			nominal_c_mult;
	काष्ठा cyclecounter	cycles;
	seqlock_t		घड़ी_lock;
	काष्ठा समयcounter	घड़ी;
	अचिन्हित दीर्घ		last_overflow_check;
	काष्ठा ptp_घड़ी	*ptp_घड़ी;
	काष्ठा ptp_घड़ी_info	ptp_घड़ी_info;
	काष्ठा notअगरier_block	nb;
पूर्ण;


काष्ठा mlx4_en_rss_map अणु
	पूर्णांक base_qpn;
	काष्ठा mlx4_qp qps[MAX_RX_RINGS];
	क्रमागत mlx4_qp_state state[MAX_RX_RINGS];
	काष्ठा mlx4_qp *indir_qp;
	क्रमागत mlx4_qp_state indir_state;
पूर्ण;

क्रमागत mlx4_en_port_flag अणु
	MLX4_EN_PORT_ANC = 1<<0, /* Auto-negotiation complete */
	MLX4_EN_PORT_ANE = 1<<1, /* Auto-negotiation enabled */
पूर्ण;

काष्ठा mlx4_en_port_state अणु
	पूर्णांक link_state;
	पूर्णांक link_speed;
	पूर्णांक transceiver;
	u32 flags;
पूर्ण;

क्रमागत mlx4_en_mclist_act अणु
	MCLIST_NONE,
	MCLIST_REM,
	MCLIST_ADD,
पूर्ण;

काष्ठा mlx4_en_mc_list अणु
	काष्ठा list_head	list;
	क्रमागत mlx4_en_mclist_act	action;
	u8			addr[ETH_ALEN];
	u64			reg_id;
	u64			tunnel_reg_id;
पूर्ण;

काष्ठा mlx4_en_frag_info अणु
	u16 frag_size;
	u32 frag_stride;
पूर्ण;

#अगर_घोषित CONFIG_MLX4_EN_DCB
/* Minimal TC BW - setting to 0 will block traffic */
#घोषणा MLX4_EN_BW_MIN 1
#घोषणा MLX4_EN_BW_MAX 100 /* Utilize 100% of the line */

#घोषणा MLX4_EN_TC_VENDOR 0
#घोषणा MLX4_EN_TC_ETS 7

क्रमागत dcb_pfc_type अणु
	pfc_disabled = 0,
	pfc_enabled_full,
	pfc_enabled_tx,
	pfc_enabled_rx
पूर्ण;

काष्ठा mlx4_en_cee_config अणु
	bool	pfc_state;
	क्रमागत	dcb_pfc_type dcb_pfc[MLX4_EN_NUM_UP_HIGH];
पूर्ण;
#पूर्ण_अगर

काष्ठा ethtool_flow_id अणु
	काष्ठा list_head list;
	काष्ठा ethtool_rx_flow_spec flow_spec;
	u64 id;
पूर्ण;

क्रमागत अणु
	MLX4_EN_FLAG_PROMISC		= (1 << 0),
	MLX4_EN_FLAG_MC_PROMISC		= (1 << 1),
	/* whether we need to enable hardware loopback by putting dmac
	 * in Tx WQE
	 */
	MLX4_EN_FLAG_ENABLE_HW_LOOPBACK	= (1 << 2),
	/* whether we need to drop packets that hardware loopback-ed */
	MLX4_EN_FLAG_RX_FILTER_NEEDED	= (1 << 3),
	MLX4_EN_FLAG_FORCE_PROMISC	= (1 << 4),
	MLX4_EN_FLAG_RX_CSUM_NON_TCP_UDP	= (1 << 5),
#अगर_घोषित CONFIG_MLX4_EN_DCB
	MLX4_EN_FLAG_DCB_ENABLED        = (1 << 6),
#पूर्ण_अगर
पूर्ण;

#घोषणा PORT_BEACON_MAX_LIMIT (65535)
#घोषणा MLX4_EN_MAC_HASH_SIZE (1 << BITS_PER_BYTE)
#घोषणा MLX4_EN_MAC_HASH_IDX 5

काष्ठा mlx4_en_stats_biपंचांगap अणु
	DECLARE_BITMAP(biपंचांगap, NUM_ALL_STATS);
	काष्ठा mutex mutex; /* क्रम mutual access to stats biपंचांगap */
पूर्ण;

क्रमागत अणु
	MLX4_EN_STATE_FLAG_RESTARTING,
पूर्ण;

काष्ठा mlx4_en_priv अणु
	काष्ठा mlx4_en_dev *mdev;
	काष्ठा mlx4_en_port_profile *prof;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	काष्ठा mlx4_en_port_state port_state;
	spinlock_t stats_lock;
	काष्ठा ethtool_flow_id ethtool_rules[MAX_NUM_OF_FS_RULES];
	/* To allow rules removal जबतक port is going करोwn */
	काष्ठा list_head ethtool_list;

	अचिन्हित दीर्घ last_moder_packets[MAX_RX_RINGS];
	अचिन्हित दीर्घ last_moder_tx_packets;
	अचिन्हित दीर्घ last_moder_bytes[MAX_RX_RINGS];
	अचिन्हित दीर्घ last_moder_jअगरfies;
	पूर्णांक last_moder_समय[MAX_RX_RINGS];
	u16 rx_usecs;
	u16 rx_frames;
	u16 tx_usecs;
	u16 tx_frames;
	u32 pkt_rate_low;
	u16 rx_usecs_low;
	u32 pkt_rate_high;
	u16 rx_usecs_high;
	u32 sample_पूर्णांकerval;
	u32 adaptive_rx_coal;
	u32 msg_enable;
	u32 loopback_ok;
	u32 validate_loopback;

	काष्ठा mlx4_hwq_resources res;
	पूर्णांक link_state;
	पूर्णांक last_link_state;
	bool port_up;
	पूर्णांक port;
	पूर्णांक रेजिस्टरed;
	पूर्णांक allocated;
	पूर्णांक stride;
	अचिन्हित अक्षर current_mac[ETH_ALEN + 2];
	पूर्णांक mac_index;
	अचिन्हित max_mtu;
	पूर्णांक base_qpn;
	पूर्णांक cqe_factor;
	पूर्णांक cqe_size;

	काष्ठा mlx4_en_rss_map rss_map;
	__be32 ctrl_flags;
	u32 flags;
	u8 num_tx_rings_p_up;
	u32 tx_work_limit;
	u32 tx_ring_num[MLX4_EN_NUM_TX_TYPES];
	u32 rx_ring_num;
	u32 rx_skb_size;
	काष्ठा mlx4_en_frag_info frag_info[MLX4_EN_MAX_RX_FRAGS];
	u8 num_frags;
	u8 log_rx_info;
	u8 dma_dir;
	u16 rx_headroom;

	काष्ठा mlx4_en_tx_ring **tx_ring[MLX4_EN_NUM_TX_TYPES];
	काष्ठा mlx4_en_rx_ring *rx_ring[MAX_RX_RINGS];
	काष्ठा mlx4_en_cq **tx_cq[MLX4_EN_NUM_TX_TYPES];
	काष्ठा mlx4_en_cq *rx_cq[MAX_RX_RINGS];
	काष्ठा mlx4_qp drop_qp;
	काष्ठा work_काष्ठा rx_mode_task;
	काष्ठा work_काष्ठा restart_task;
	काष्ठा work_काष्ठा linkstate_task;
	काष्ठा delayed_work stats_task;
	काष्ठा delayed_work service_task;
	काष्ठा mlx4_en_pkt_stats pkstats;
	काष्ठा mlx4_en_counter_stats pf_stats;
	काष्ठा mlx4_en_flow_stats_rx rx_priority_flowstats[MLX4_NUM_PRIORITIES];
	काष्ठा mlx4_en_flow_stats_tx tx_priority_flowstats[MLX4_NUM_PRIORITIES];
	काष्ठा mlx4_en_flow_stats_rx rx_flowstats;
	काष्ठा mlx4_en_flow_stats_tx tx_flowstats;
	काष्ठा mlx4_en_port_stats port_stats;
	काष्ठा mlx4_en_xdp_stats xdp_stats;
	काष्ठा mlx4_en_phy_stats phy_stats;
	काष्ठा mlx4_en_stats_biपंचांगap stats_biपंचांगap;
	काष्ठा list_head mc_list;
	काष्ठा list_head curr_list;
	u64 broadcast_id;
	काष्ठा mlx4_en_stat_out_mbox hw_stats;
	पूर्णांक vids[128];
	bool wol;
	काष्ठा device *ddev;
	काष्ठा hlist_head mac_hash[MLX4_EN_MAC_HASH_SIZE];
	काष्ठा hwtstamp_config hwtstamp_config;
	u32 counter_index;

#अगर_घोषित CONFIG_MLX4_EN_DCB
#घोषणा MLX4_EN_DCB_ENABLED	0x3
	काष्ठा ieee_ets ets;
	u16 maxrate[IEEE_8021QAZ_MAX_TCS];
	क्रमागत dcbnl_cndd_states cndd_state[IEEE_8021QAZ_MAX_TCS];
	काष्ठा mlx4_en_cee_config cee_config;
	u8 dcbx_cap;
#पूर्ण_अगर
#अगर_घोषित CONFIG_RFS_ACCEL
	spinlock_t filters_lock;
	पूर्णांक last_filter_id;
	काष्ठा list_head filters;
	काष्ठा hlist_head filter_hash[1 << MLX4_EN_FILTER_HASH_SHIFT];
#पूर्ण_अगर
	u64 tunnel_reg_id;
	__be16 vxlan_port;

	u32 pflags;
	u8 rss_key[MLX4_EN_RSS_KEY_SIZE];
	u8 rss_hash_fn;
	अचिन्हित दीर्घ state;
पूर्ण;

क्रमागत mlx4_en_wol अणु
	MLX4_EN_WOL_MAGIC = (1ULL << 61),
	MLX4_EN_WOL_ENABLED = (1ULL << 62),
पूर्ण;

काष्ठा mlx4_mac_entry अणु
	काष्ठा hlist_node hlist;
	अचिन्हित अक्षर mac[ETH_ALEN + 2];
	u64 reg_id;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत काष्ठा mlx4_cqe *mlx4_en_get_cqe(व्योम *buf, पूर्णांक idx, पूर्णांक cqe_sz)
अणु
	वापस buf + idx * cqe_sz;
पूर्ण

#घोषणा MLX4_EN_WOL_DO_MODIFY (1ULL << 63)

व्योम mlx4_en_init_ptys2ethtool_map(व्योम);
व्योम mlx4_en_update_loopback_state(काष्ठा net_device *dev,
				   netdev_features_t features);

व्योम mlx4_en_destroy_netdev(काष्ठा net_device *dev);
पूर्णांक mlx4_en_init_netdev(काष्ठा mlx4_en_dev *mdev, पूर्णांक port,
			काष्ठा mlx4_en_port_profile *prof);

पूर्णांक mlx4_en_start_port(काष्ठा net_device *dev);
व्योम mlx4_en_stop_port(काष्ठा net_device *dev, पूर्णांक detach);

व्योम mlx4_en_set_stats_biपंचांगap(काष्ठा mlx4_dev *dev,
			      काष्ठा mlx4_en_stats_biपंचांगap *stats_biपंचांगap,
			      u8 rx_ppp, u8 rx_छोड़ो,
			      u8 tx_ppp, u8 tx_छोड़ो);

पूर्णांक mlx4_en_try_alloc_resources(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_priv *पंचांगp,
				काष्ठा mlx4_en_port_profile *prof,
				bool carry_xdp_prog);
व्योम mlx4_en_safe_replace_resources(काष्ठा mlx4_en_priv *priv,
				    काष्ठा mlx4_en_priv *पंचांगp);

पूर्णांक mlx4_en_create_cq(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq **pcq,
		      पूर्णांक entries, पूर्णांक ring, क्रमागत cq_type mode, पूर्णांक node);
व्योम mlx4_en_destroy_cq(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq **pcq);
पूर्णांक mlx4_en_activate_cq(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq *cq,
			पूर्णांक cq_idx);
व्योम mlx4_en_deactivate_cq(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq *cq);
पूर्णांक mlx4_en_set_cq_moder(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq *cq);
व्योम mlx4_en_arm_cq(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_en_cq *cq);

व्योम mlx4_en_tx_irq(काष्ठा mlx4_cq *mcq);
u16 mlx4_en_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			 काष्ठा net_device *sb_dev);
netdev_tx_t mlx4_en_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
netdev_tx_t mlx4_en_xmit_frame(काष्ठा mlx4_en_rx_ring *rx_ring,
			       काष्ठा mlx4_en_rx_alloc *frame,
			       काष्ठा mlx4_en_priv *priv, अचिन्हित पूर्णांक length,
			       पूर्णांक tx_ind, bool *करोorbell_pending);
व्योम mlx4_en_xmit_करोorbell(काष्ठा mlx4_en_tx_ring *ring);
bool mlx4_en_rx_recycle(काष्ठा mlx4_en_rx_ring *ring,
			काष्ठा mlx4_en_rx_alloc *frame);

पूर्णांक mlx4_en_create_tx_ring(काष्ठा mlx4_en_priv *priv,
			   काष्ठा mlx4_en_tx_ring **pring,
			   u32 size, u16 stride,
			   पूर्णांक node, पूर्णांक queue_index);
व्योम mlx4_en_destroy_tx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_tx_ring **pring);
व्योम mlx4_en_init_tx_xdp_ring_descs(काष्ठा mlx4_en_priv *priv,
				    काष्ठा mlx4_en_tx_ring *ring);
पूर्णांक mlx4_en_activate_tx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_tx_ring *ring,
			     पूर्णांक cq, पूर्णांक user_prio);
व्योम mlx4_en_deactivate_tx_ring(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_tx_ring *ring);
व्योम mlx4_en_set_num_rx_rings(काष्ठा mlx4_en_dev *mdev);
व्योम mlx4_en_recover_from_oom(काष्ठा mlx4_en_priv *priv);
पूर्णांक mlx4_en_create_rx_ring(काष्ठा mlx4_en_priv *priv,
			   काष्ठा mlx4_en_rx_ring **pring,
			   u32 size, u16 stride, पूर्णांक node, पूर्णांक queue_index);
व्योम mlx4_en_destroy_rx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_rx_ring **pring,
			     u32 size, u16 stride);
पूर्णांक mlx4_en_activate_rx_rings(काष्ठा mlx4_en_priv *priv);
व्योम mlx4_en_deactivate_rx_ring(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_rx_ring *ring);
पूर्णांक mlx4_en_process_rx_cq(काष्ठा net_device *dev,
			  काष्ठा mlx4_en_cq *cq,
			  पूर्णांक budget);
पूर्णांक mlx4_en_poll_rx_cq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक mlx4_en_poll_tx_cq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक mlx4_en_process_tx_cq(काष्ठा net_device *dev,
			  काष्ठा mlx4_en_cq *cq, पूर्णांक napi_budget);
u32 mlx4_en_मुक्त_tx_desc(काष्ठा mlx4_en_priv *priv,
			 काष्ठा mlx4_en_tx_ring *ring,
			 पूर्णांक index, u64 बारtamp,
			 पूर्णांक napi_mode);
u32 mlx4_en_recycle_tx_desc(काष्ठा mlx4_en_priv *priv,
			    काष्ठा mlx4_en_tx_ring *ring,
			    पूर्णांक index, u64 बारtamp,
			    पूर्णांक napi_mode);
व्योम mlx4_en_fill_qp_context(काष्ठा mlx4_en_priv *priv, पूर्णांक size, पूर्णांक stride,
		पूर्णांक is_tx, पूर्णांक rss, पूर्णांक qpn, पूर्णांक cqn, पूर्णांक user_prio,
		काष्ठा mlx4_qp_context *context);
व्योम mlx4_en_sqp_event(काष्ठा mlx4_qp *qp, क्रमागत mlx4_event event);
पूर्णांक mlx4_en_change_mcast_lb(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_qp *qp,
			    पूर्णांक loopback);
व्योम mlx4_en_calc_rx_buf(काष्ठा net_device *dev);
पूर्णांक mlx4_en_config_rss_steer(काष्ठा mlx4_en_priv *priv);
व्योम mlx4_en_release_rss_steer(काष्ठा mlx4_en_priv *priv);
पूर्णांक mlx4_en_create_drop_qp(काष्ठा mlx4_en_priv *priv);
व्योम mlx4_en_destroy_drop_qp(काष्ठा mlx4_en_priv *priv);
पूर्णांक mlx4_en_मुक्त_tx_buf(काष्ठा net_device *dev, काष्ठा mlx4_en_tx_ring *ring);
व्योम mlx4_en_rx_irq(काष्ठा mlx4_cq *mcq);

पूर्णांक mlx4_SET_MCAST_FLTR(काष्ठा mlx4_dev *dev, u8 port, u64 mac, u64 clear, u8 mode);
पूर्णांक mlx4_SET_VLAN_FLTR(काष्ठा mlx4_dev *dev, काष्ठा mlx4_en_priv *priv);

व्योम mlx4_en_fold_software_stats(काष्ठा net_device *dev);
पूर्णांक mlx4_en_DUMP_ETH_STATS(काष्ठा mlx4_en_dev *mdev, u8 port, u8 reset);
पूर्णांक mlx4_en_QUERY_PORT(काष्ठा mlx4_en_dev *mdev, u8 port);

#अगर_घोषित CONFIG_MLX4_EN_DCB
बाह्य स्थिर काष्ठा dcbnl_rtnl_ops mlx4_en_dcbnl_ops;
बाह्य स्थिर काष्ठा dcbnl_rtnl_ops mlx4_en_dcbnl_pfc_ops;
#पूर्ण_अगर

पूर्णांक mlx4_en_setup_tc(काष्ठा net_device *dev, u8 up);
पूर्णांक mlx4_en_alloc_tx_queue_per_tc(काष्ठा net_device *dev, u8 tc);

#अगर_घोषित CONFIG_RFS_ACCEL
व्योम mlx4_en_cleanup_filters(काष्ठा mlx4_en_priv *priv);
#पूर्ण_अगर

#घोषणा MLX4_EN_NUM_SELF_TEST	5
व्योम mlx4_en_ex_selftest(काष्ठा net_device *dev, u32 *flags, u64 *buf);
व्योम mlx4_en_ptp_overflow_check(काष्ठा mlx4_en_dev *mdev);

#घोषणा DEV_FEATURE_CHANGED(dev, new_features, feature) \
	((dev->features & feature) ^ (new_features & feature))

पूर्णांक mlx4_en_moderation_update(काष्ठा mlx4_en_priv *priv);
पूर्णांक mlx4_en_reset_config(काष्ठा net_device *dev,
			 काष्ठा hwtstamp_config ts_config,
			 netdev_features_t new_features);
व्योम mlx4_en_update_pfc_stats_biपंचांगap(काष्ठा mlx4_dev *dev,
				     काष्ठा mlx4_en_stats_biपंचांगap *stats_biपंचांगap,
				     u8 rx_ppp, u8 rx_छोड़ो,
				     u8 tx_ppp, u8 tx_छोड़ो);
पूर्णांक mlx4_en_netdev_event(काष्ठा notअगरier_block *this,
			 अचिन्हित दीर्घ event, व्योम *ptr);

/*
 * Functions क्रम समय stamping
 */
u64 mlx4_en_get_cqe_ts(काष्ठा mlx4_cqe *cqe);
व्योम mlx4_en_fill_hwtstamps(काष्ठा mlx4_en_dev *mdev,
			    काष्ठा skb_shared_hwtstamps *hwts,
			    u64 बारtamp);
व्योम mlx4_en_init_बारtamp(काष्ठा mlx4_en_dev *mdev);
व्योम mlx4_en_हटाओ_बारtamp(काष्ठा mlx4_en_dev *mdev);

/* Globals
 */
बाह्य स्थिर काष्ठा ethtool_ops mlx4_en_ethtool_ops;



/*
 * prपूर्णांकk / logging functions
 */

__म_लिखो(3, 4)
व्योम en_prपूर्णांक(स्थिर अक्षर *level, स्थिर काष्ठा mlx4_en_priv *priv,
	      स्थिर अक्षर *क्रमmat, ...);

#घोषणा en_dbg(mlevel, priv, क्रमmat, ...)				\
करो अणु									\
	अगर (NETIF_MSG_##mlevel & (priv)->msg_enable)			\
		en_prपूर्णांक(KERN_DEBUG, priv, क्रमmat, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#घोषणा en_warn(priv, क्रमmat, ...)					\
	en_prपूर्णांक(KERN_WARNING, priv, क्रमmat, ##__VA_ARGS__)
#घोषणा en_err(priv, क्रमmat, ...)					\
	en_prपूर्णांक(KERN_ERR, priv, क्रमmat, ##__VA_ARGS__)
#घोषणा en_info(priv, क्रमmat, ...)					\
	en_prपूर्णांक(KERN_INFO, priv, क्रमmat, ##__VA_ARGS__)

#घोषणा mlx4_err(mdev, क्रमmat, ...)					\
	pr_err(DRV_NAME " %s: " क्रमmat,					\
	       dev_name(&(mdev)->pdev->dev), ##__VA_ARGS__)
#घोषणा mlx4_info(mdev, क्रमmat, ...)					\
	pr_info(DRV_NAME " %s: " क्रमmat,				\
		dev_name(&(mdev)->pdev->dev), ##__VA_ARGS__)
#घोषणा mlx4_warn(mdev, क्रमmat, ...)					\
	pr_warn(DRV_NAME " %s: " क्रमmat,				\
		dev_name(&(mdev)->pdev->dev), ##__VA_ARGS__)

#पूर्ण_अगर
