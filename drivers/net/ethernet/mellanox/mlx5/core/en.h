<शैली गुरु>
/*
 * Copyright (c) 2015-2016, Mellanox Technologies. All rights reserved.
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
 */
#अगर_अघोषित __MLX5_EN_H__
#घोषणा __MLX5_EN_H__

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/port.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/transobj.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/चयनdev.h>
#समावेश <net/xdp.h>
#समावेश <linux/dim.h>
#समावेश <linux/bits.h>
#समावेश "wq.h"
#समावेश "mlx5_core.h"
#समावेश "en_stats.h"
#समावेश "en/dcbnl.h"
#समावेश "en/fs.h"
#समावेश "en/qos.h"
#समावेश "lib/hv_vhca.h"
#समावेश "lib/clock.h"

बाह्य स्थिर काष्ठा net_device_ops mlx5e_netdev_ops;
काष्ठा page_pool;

#घोषणा MLX5E_METADATA_ETHER_TYPE (0x8CE4)
#घोषणा MLX5E_METADATA_ETHER_LEN 8

#घोषणा MLX5_SET_CFG(p, f, v) MLX5_SET(create_flow_group_in, p, f, v)

#घोषणा MLX5E_ETH_HARD_MTU (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN)

#घोषणा MLX5E_HW2SW_MTU(params, hwmtu) ((hwmtu) - ((params)->hard_mtu))
#घोषणा MLX5E_SW2HW_MTU(params, swmtu) ((swmtu) + ((params)->hard_mtu))

#घोषणा MLX5E_MAX_NUM_TC	8

#घोषणा MLX5_RX_HEADROOM NET_SKB_PAD
#घोषणा MLX5_SKB_FRAG_SZ(len)	(SKB_DATA_ALIGN(len) +	\
				 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

#घोषणा MLX5E_RX_MAX_HEAD (256)

#घोषणा MLX5_MPWRQ_MIN_LOG_STRIDE_SZ(mdev) \
	(6 + MLX5_CAP_GEN(mdev, cache_line_128byte)) /* HW restriction */
#घोषणा MLX5_MPWRQ_LOG_STRIDE_SZ(mdev, req) \
	max_t(u32, MLX5_MPWRQ_MIN_LOG_STRIDE_SZ(mdev), req)
#घोषणा MLX5_MPWRQ_DEF_LOG_STRIDE_SZ(mdev) \
	MLX5_MPWRQ_LOG_STRIDE_SZ(mdev, order_base_2(MLX5E_RX_MAX_HEAD))

#घोषणा MLX5_MPWRQ_LOG_WQE_SZ			18
#घोषणा MLX5_MPWRQ_WQE_PAGE_ORDER  (MLX5_MPWRQ_LOG_WQE_SZ - PAGE_SHIFT > 0 ? \
				    MLX5_MPWRQ_LOG_WQE_SZ - PAGE_SHIFT : 0)
#घोषणा MLX5_MPWRQ_PAGES_PER_WQE		BIT(MLX5_MPWRQ_WQE_PAGE_ORDER)

#घोषणा MLX5_ALIGN_MTTS(mtts)		(ALIGN(mtts, 8))
#घोषणा MLX5_ALIGNED_MTTS_OCTW(mtts)	((mtts) / 2)
#घोषणा MLX5_MTT_OCTW(mtts)		(MLX5_ALIGNED_MTTS_OCTW(MLX5_ALIGN_MTTS(mtts)))
/* Add another page to MLX5E_REQUIRED_WQE_MTTS as a buffer between
 * WQEs, This page will असलorb ग_लिखो overflow by the hardware, when
 * receiving packets larger than MTU. These oversize packets are
 * dropped by the driver at a later stage.
 */
#घोषणा MLX5E_REQUIRED_WQE_MTTS		(MLX5_ALIGN_MTTS(MLX5_MPWRQ_PAGES_PER_WQE + 1))
#घोषणा MLX5E_REQUIRED_MTTS(wqes)	(wqes * MLX5E_REQUIRED_WQE_MTTS)
#घोषणा MLX5E_MAX_RQ_NUM_MTTS	\
	((1 << 16) * 2) /* So that MLX5_MTT_OCTW(num_mtts) fits पूर्णांकo u16 */
#घोषणा MLX5E_ORDER2_MAX_PACKET_MTU (order_base_2(10 * 1024))
#घोषणा MLX5E_PARAMS_MAXIMUM_LOG_RQ_SIZE_MPW	\
		(ilog2(MLX5E_MAX_RQ_NUM_MTTS / MLX5E_REQUIRED_WQE_MTTS))
#घोषणा MLX5E_LOG_MAX_RQ_NUM_PACKETS_MPW \
	(MLX5E_PARAMS_MAXIMUM_LOG_RQ_SIZE_MPW + \
	 (MLX5_MPWRQ_LOG_WQE_SZ - MLX5E_ORDER2_MAX_PACKET_MTU))

#घोषणा MLX5E_MIN_SKB_FRAG_SZ		(MLX5_SKB_FRAG_SZ(MLX5_RX_HEADROOM))
#घोषणा MLX5E_LOG_MAX_RX_WQE_BULK	\
	(ilog2(PAGE_SIZE / roundup_घात_of_two(MLX5E_MIN_SKB_FRAG_SZ)))

#घोषणा MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE                0x6
#घोषणा MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE                0xa
#घोषणा MLX5E_PARAMS_MAXIMUM_LOG_SQ_SIZE                0xd

#घोषणा MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE (1 + MLX5E_LOG_MAX_RX_WQE_BULK)
#घोषणा MLX5E_PARAMS_DEFAULT_LOG_RQ_SIZE                0xa
#घोषणा MLX5E_PARAMS_MAXIMUM_LOG_RQ_SIZE min_t(u8, 0xd,	\
					       MLX5E_LOG_MAX_RQ_NUM_PACKETS_MPW)

#घोषणा MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE_MPW            0x2

#घोषणा MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ                 (64 * 1024)
#घोषणा MLX5E_DEFAULT_LRO_TIMEOUT                       32
#घोषणा MLX5E_LRO_TIMEOUT_ARR_SIZE                      4

#घोषणा MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_USEC      0x10
#घोषणा MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_USEC_FROM_CQE 0x3
#घोषणा MLX5E_PARAMS_DEFAULT_RX_CQ_MODERATION_PKTS      0x20
#घोषणा MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC      0x10
#घोषणा MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC_FROM_CQE 0x10
#घोषणा MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_PKTS      0x20
#घोषणा MLX5E_PARAMS_DEFAULT_MIN_RX_WQES                0x80
#घोषणा MLX5E_PARAMS_DEFAULT_MIN_RX_WQES_MPW            0x2

#घोषणा MLX5E_LOG_INसूची_RQT_SIZE       0x8
#घोषणा MLX5E_INसूची_RQT_SIZE           BIT(MLX5E_LOG_INसूची_RQT_SIZE)
#घोषणा MLX5E_MIN_NUM_CHANNELS         0x1
#घोषणा MLX5E_MAX_NUM_CHANNELS         (MLX5E_INसूची_RQT_SIZE / 2)
#घोषणा MLX5E_MAX_NUM_SQS              (MLX5E_MAX_NUM_CHANNELS * MLX5E_MAX_NUM_TC)
#घोषणा MLX5E_TX_CQ_POLL_BUDGET        128
#घोषणा MLX5E_TX_XSK_POLL_BUDGET       64
#घोषणा MLX5E_SQ_RECOVER_MIN_INTERVAL  500 /* msecs */

#घोषणा MLX5E_UMR_WQE_INLINE_SZ \
	(माप(काष्ठा mlx5e_umr_wqe) + \
	 ALIGN(MLX5_MPWRQ_PAGES_PER_WQE * माप(काष्ठा mlx5_mtt), \
	       MLX5_UMR_MTT_ALIGNMENT))
#घोषणा MLX5E_UMR_WQEBBS \
	(DIV_ROUND_UP(MLX5E_UMR_WQE_INLINE_SZ, MLX5_SEND_WQE_BB))

#घोषणा MLX5E_MSG_LEVEL			NETIF_MSG_LINK

#घोषणा mlx5e_dbg(mlevel, priv, क्रमmat, ...)                    \
करो अणु                                                            \
	अगर (NETIF_MSG_##mlevel & (priv)->msglevel)              \
		netdev_warn(priv->netdev, क्रमmat,               \
			    ##__VA_ARGS__);                     \
पूर्ण जबतक (0)

#घोषणा mlx5e_state_dereference(priv, p) \
	rcu_dereference_रक्षित((p), lockdep_is_held(&(priv)->state_lock))

क्रमागत mlx5e_rq_group अणु
	MLX5E_RQ_GROUP_REGULAR,
	MLX5E_RQ_GROUP_XSK,
#घोषणा MLX5E_NUM_RQ_GROUPS(g) (1 + MLX5E_RQ_GROUP_##g)
पूर्ण;

अटल अंतरभूत u8 mlx5e_get_num_lag_ports(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (mlx5_lag_is_lacp_owner(mdev))
		वापस 1;

	वापस clamp_t(u8, MLX5_CAP_GEN(mdev, num_lag_ports), 1, MLX5_MAX_PORTS);
पूर्ण

अटल अंतरभूत u16 mlx5_min_rx_wqes(पूर्णांक wq_type, u32 wq_size)
अणु
	चयन (wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस min_t(u16, MLX5E_PARAMS_DEFAULT_MIN_RX_WQES_MPW,
			     wq_size / 2);
	शेष:
		वापस min_t(u16, MLX5E_PARAMS_DEFAULT_MIN_RX_WQES,
			     wq_size / 2);
	पूर्ण
पूर्ण

/* Use this function to get max num channels (rxqs/txqs) only to create netdev */
अटल अंतरभूत पूर्णांक mlx5e_get_max_num_channels(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस is_kdump_kernel() ?
		MLX5E_MIN_NUM_CHANNELS :
		min_t(पूर्णांक, mlx5_comp_vectors_count(mdev), MLX5E_MAX_NUM_CHANNELS);
पूर्ण

काष्ठा mlx5e_tx_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg ctrl;
	काष्ठा mlx5_wqe_eth_seg  eth;
	काष्ठा mlx5_wqe_data_seg data[0];
पूर्ण;

काष्ठा mlx5e_rx_wqe_ll अणु
	काष्ठा mlx5_wqe_srq_next_seg  next;
	काष्ठा mlx5_wqe_data_seg      data[];
पूर्ण;

काष्ठा mlx5e_rx_wqe_cyc अणु
	काष्ठा mlx5_wqe_data_seg      data[0];
पूर्ण;

काष्ठा mlx5e_umr_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg       ctrl;
	काष्ठा mlx5_wqe_umr_ctrl_seg   uctrl;
	काष्ठा mlx5_mkey_seg           mkc;
	काष्ठा mlx5_mtt                अंतरभूत_mtts[0];
पूर्ण;

बाह्य स्थिर अक्षर mlx5e_self_tests[][ETH_GSTRING_LEN];

क्रमागत mlx5e_priv_flag अणु
	MLX5E_PFLAG_RX_CQE_BASED_MODER,
	MLX5E_PFLAG_TX_CQE_BASED_MODER,
	MLX5E_PFLAG_RX_CQE_COMPRESS,
	MLX5E_PFLAG_RX_STRIDING_RQ,
	MLX5E_PFLAG_RX_NO_CSUM_COMPLETE,
	MLX5E_PFLAG_XDP_TX_MPWQE,
	MLX5E_PFLAG_SKB_TX_MPWQE,
	MLX5E_PFLAG_TX_PORT_TS,
	MLX5E_NUM_PFLAGS, /* Keep last */
पूर्ण;

#घोषणा MLX5E_SET_PFLAG(params, pflag, enable)			\
	करो अणु							\
		अगर (enable)					\
			(params)->pflags |= BIT(pflag);		\
		अन्यथा						\
			(params)->pflags &= ~(BIT(pflag));	\
	पूर्ण जबतक (0)

#घोषणा MLX5E_GET_PFLAG(params, pflag) (!!((params)->pflags & (BIT(pflag))))

काष्ठा mlx5e_params अणु
	u8  log_sq_size;
	u8  rq_wq_type;
	u8  log_rq_mtu_frames;
	u16 num_channels;
	u8  num_tc;
	bool rx_cqe_compress_def;
	bool tunneled_offload_en;
	काष्ठा dim_cq_moder rx_cq_moderation;
	काष्ठा dim_cq_moder tx_cq_moderation;
	bool lro_en;
	u8  tx_min_अंतरभूत_mode;
	bool vlan_strip_disable;
	bool scatter_fcs_en;
	bool rx_dim_enabled;
	bool tx_dim_enabled;
	u32 lro_समयout;
	u32 pflags;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा mlx5e_xsk *xsk;
	अचिन्हित पूर्णांक sw_mtu;
	पूर्णांक hard_mtu;
	bool ptp_rx;
पूर्ण;

क्रमागत अणु
	MLX5E_RQ_STATE_ENABLED,
	MLX5E_RQ_STATE_RECOVERING,
	MLX5E_RQ_STATE_AM,
	MLX5E_RQ_STATE_NO_CSUM_COMPLETE,
	MLX5E_RQ_STATE_CSUM_FULL, /* cqe_csum_full hw bit is set */
	MLX5E_RQ_STATE_FPGA_TLS, /* FPGA TLS enabled */
	MLX5E_RQ_STATE_MINI_CQE_HW_STRIDX /* set when mini_cqe_resp_stride_index cap is used */
पूर्ण;

काष्ठा mlx5e_cq अणु
	/* data path - accessed per cqe */
	काष्ठा mlx5_cqwq           wq;

	/* data path - accessed per napi poll */
	u16                        event_ctr;
	काष्ठा napi_काष्ठा        *napi;
	काष्ठा mlx5_core_cq        mcq;
	काष्ठा mlx5e_ch_stats     *ch_stats;

	/* control */
	काष्ठा net_device         *netdev;
	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा mlx5e_priv         *priv;
	काष्ठा mlx5_wq_ctrl        wq_ctrl;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx5e_cq_decomp अणु
	/* cqe decompression */
	काष्ठा mlx5_cqe64          title;
	काष्ठा mlx5_mini_cqe8      mini_arr[MLX5_MINI_CQE_ARRAY_SIZE];
	u8                         mini_arr_idx;
	u16                        left;
	u16                        wqe_counter;
पूर्ण ____cacheline_aligned_in_smp;

क्रमागत mlx5e_dma_map_type अणु
	MLX5E_DMA_MAP_SINGLE,
	MLX5E_DMA_MAP_PAGE
पूर्ण;

काष्ठा mlx5e_sq_dma अणु
	dma_addr_t              addr;
	u32                     size;
	क्रमागत mlx5e_dma_map_type type;
पूर्ण;

क्रमागत अणु
	MLX5E_SQ_STATE_ENABLED,
	MLX5E_SQ_STATE_MPWQE,
	MLX5E_SQ_STATE_RECOVERING,
	MLX5E_SQ_STATE_IPSEC,
	MLX5E_SQ_STATE_AM,
	MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE,
	MLX5E_SQ_STATE_PENDING_XSK_TX,
	MLX5E_SQ_STATE_PENDING_TLS_RX_RESYNC,
पूर्ण;

काष्ठा mlx5e_tx_mpwqe अणु
	/* Current MPWQE session */
	काष्ठा mlx5e_tx_wqe *wqe;
	u32 bytes_count;
	u8 ds_count;
	u8 pkt_count;
	u8 अंतरभूत_on;
पूर्ण;

काष्ठा mlx5e_skb_fअगरo अणु
	काष्ठा sk_buff **fअगरo;
	u16 *pc;
	u16 *cc;
	u16 mask;
पूर्ण;

काष्ठा mlx5e_ptpsq;

काष्ठा mlx5e_txqsq अणु
	/* data path */

	/* dirtied @completion */
	u16                        cc;
	u16                        skb_fअगरo_cc;
	u32                        dma_fअगरo_cc;
	काष्ठा dim                 dim; /* Adaptive Moderation */

	/* dirtied @xmit */
	u16                        pc ____cacheline_aligned_in_smp;
	u16                        skb_fअगरo_pc;
	u32                        dma_fअगरo_pc;
	काष्ठा mlx5e_tx_mpwqe      mpwqe;

	काष्ठा mlx5e_cq            cq;

	/* पढ़ो only */
	काष्ठा mlx5_wq_cyc         wq;
	u32                        dma_fअगरo_mask;
	काष्ठा mlx5e_sq_stats     *stats;
	काष्ठा अणु
		काष्ठा mlx5e_sq_dma       *dma_fअगरo;
		काष्ठा mlx5e_skb_fअगरo      skb_fअगरo;
		काष्ठा mlx5e_tx_wqe_info  *wqe_info;
	पूर्ण db;
	व्योम __iomem              *uar_map;
	काष्ठा netdev_queue       *txq;
	u32                        sqn;
	u16                        stop_room;
	u8                         min_अंतरभूत_mode;
	काष्ठा device             *pdev;
	__be32                     mkey_be;
	अचिन्हित दीर्घ              state;
	अचिन्हित पूर्णांक               hw_mtu;
	काष्ठा hwtstamp_config    *tstamp;
	काष्ठा mlx5_घड़ी         *घड़ी;
	काष्ठा net_device         *netdev;
	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा mlx5e_priv         *priv;

	/* control path */
	काष्ठा mlx5_wq_ctrl        wq_ctrl;
	पूर्णांक                        ch_ix;
	पूर्णांक                        txq_ix;
	u32                        rate_limit;
	काष्ठा work_काष्ठा         recover_work;
	काष्ठा mlx5e_ptpsq        *ptpsq;
	cqe_ts_to_ns               ptp_cyc2समय;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx5e_dma_info अणु
	dma_addr_t addr;
	जोड़ अणु
		काष्ठा page *page;
		काष्ठा xdp_buff *xsk;
	पूर्ण;
पूर्ण;

/* XDP packets can be transmitted in dअगरferent ways. On completion, we need to
 * distinguish between them to clean up things in a proper way.
 */
क्रमागत mlx5e_xdp_xmit_mode अणु
	/* An xdp_frame was transmitted due to either XDP_REसूचीECT from another
	 * device or XDP_TX from an XSK RQ. The frame has to be unmapped and
	 * वापसed.
	 */
	MLX5E_XDP_XMIT_MODE_FRAME,

	/* The xdp_frame was created in place as a result of XDP_TX from a
	 * regular RQ. No DMA remapping happened, and the page beदीर्घs to us.
	 */
	MLX5E_XDP_XMIT_MODE_PAGE,

	/* No xdp_frame was created at all, the transmit happened from a UMEM
	 * page. The UMEM Completion Ring producer poपूर्णांकer has to be increased.
	 */
	MLX5E_XDP_XMIT_MODE_XSK,
पूर्ण;

काष्ठा mlx5e_xdp_info अणु
	क्रमागत mlx5e_xdp_xmit_mode mode;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा xdp_frame *xdpf;
			dma_addr_t dma_addr;
		पूर्ण frame;
		काष्ठा अणु
			काष्ठा mlx5e_rq *rq;
			काष्ठा mlx5e_dma_info di;
		पूर्ण page;
	पूर्ण;
पूर्ण;

काष्ठा mlx5e_xmit_data अणु
	dma_addr_t  dma_addr;
	व्योम       *data;
	u32         len;
पूर्ण;

काष्ठा mlx5e_xdp_info_fअगरo अणु
	काष्ठा mlx5e_xdp_info *xi;
	u32 *cc;
	u32 *pc;
	u32 mask;
पूर्ण;

काष्ठा mlx5e_xdpsq;
प्रकार पूर्णांक (*mlx5e_fp_xmit_xdp_frame_check)(काष्ठा mlx5e_xdpsq *);
प्रकार bool (*mlx5e_fp_xmit_xdp_frame)(काष्ठा mlx5e_xdpsq *,
					काष्ठा mlx5e_xmit_data *,
					काष्ठा mlx5e_xdp_info *,
					पूर्णांक);

काष्ठा mlx5e_xdpsq अणु
	/* data path */

	/* dirtied @completion */
	u32                        xdpi_fअगरo_cc;
	u16                        cc;

	/* dirtied @xmit */
	u32                        xdpi_fअगरo_pc ____cacheline_aligned_in_smp;
	u16                        pc;
	काष्ठा mlx5_wqe_ctrl_seg   *करोorbell_cseg;
	काष्ठा mlx5e_tx_mpwqe      mpwqe;

	काष्ठा mlx5e_cq            cq;

	/* पढ़ो only */
	काष्ठा xsk_buff_pool      *xsk_pool;
	काष्ठा mlx5_wq_cyc         wq;
	काष्ठा mlx5e_xdpsq_stats  *stats;
	mlx5e_fp_xmit_xdp_frame_check xmit_xdp_frame_check;
	mlx5e_fp_xmit_xdp_frame    xmit_xdp_frame;
	काष्ठा अणु
		काष्ठा mlx5e_xdp_wqe_info *wqe_info;
		काष्ठा mlx5e_xdp_info_fअगरo xdpi_fअगरo;
	पूर्ण db;
	व्योम __iomem              *uar_map;
	u32                        sqn;
	काष्ठा device             *pdev;
	__be32                     mkey_be;
	u8                         min_अंतरभूत_mode;
	अचिन्हित दीर्घ              state;
	अचिन्हित पूर्णांक               hw_mtu;

	/* control path */
	काष्ठा mlx5_wq_ctrl        wq_ctrl;
	काष्ठा mlx5e_channel      *channel;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx5e_ktls_resync_resp;

काष्ठा mlx5e_icosq अणु
	/* data path */
	u16                        cc;
	u16                        pc;

	काष्ठा mlx5_wqe_ctrl_seg  *करोorbell_cseg;
	काष्ठा mlx5e_cq            cq;

	/* ग_लिखो@xmit, पढ़ो@completion */
	काष्ठा अणु
		काष्ठा mlx5e_icosq_wqe_info *wqe_info;
	पूर्ण db;

	/* पढ़ो only */
	काष्ठा mlx5_wq_cyc         wq;
	व्योम __iomem              *uar_map;
	u32                        sqn;
	u16                        reserved_room;
	अचिन्हित दीर्घ              state;
	काष्ठा mlx5e_ktls_resync_resp *ktls_resync;

	/* control path */
	काष्ठा mlx5_wq_ctrl        wq_ctrl;
	काष्ठा mlx5e_channel      *channel;

	काष्ठा work_काष्ठा         recover_work;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx5e_wqe_frag_info अणु
	काष्ठा mlx5e_dma_info *di;
	u32 offset;
	bool last_in_page;
पूर्ण;

काष्ठा mlx5e_umr_dma_info अणु
	काष्ठा mlx5e_dma_info  dma_info[MLX5_MPWRQ_PAGES_PER_WQE];
पूर्ण;

काष्ठा mlx5e_mpw_info अणु
	काष्ठा mlx5e_umr_dma_info umr;
	u16 consumed_strides;
	DECLARE_BITMAP(xdp_xmit_biपंचांगap, MLX5_MPWRQ_PAGES_PER_WQE);
पूर्ण;

#घोषणा MLX5E_MAX_RX_FRAGS 4

/* a single cache unit is capable to serve one napi call (क्रम non-striding rq)
 * or a MPWQE (क्रम striding rq).
 */
#घोषणा MLX5E_CACHE_UNIT	(MLX5_MPWRQ_PAGES_PER_WQE > NAPI_POLL_WEIGHT ? \
				 MLX5_MPWRQ_PAGES_PER_WQE : NAPI_POLL_WEIGHT)
#घोषणा MLX5E_CACHE_SIZE	(4 * roundup_घात_of_two(MLX5E_CACHE_UNIT))
काष्ठा mlx5e_page_cache अणु
	u32 head;
	u32 tail;
	काष्ठा mlx5e_dma_info page_cache[MLX5E_CACHE_SIZE];
पूर्ण;

काष्ठा mlx5e_rq;
प्रकार व्योम (*mlx5e_fp_handle_rx_cqe)(काष्ठा mlx5e_rq*, काष्ठा mlx5_cqe64*);
प्रकार काष्ठा sk_buff *
(*mlx5e_fp_skb_from_cqe_mpwrq)(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi,
			       u16 cqe_bcnt, u32 head_offset, u32 page_idx);
प्रकार काष्ठा sk_buff *
(*mlx5e_fp_skb_from_cqe)(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe,
			 काष्ठा mlx5e_wqe_frag_info *wi, u32 cqe_bcnt);
प्रकार bool (*mlx5e_fp_post_rx_wqes)(काष्ठा mlx5e_rq *rq);
प्रकार व्योम (*mlx5e_fp_dealloc_wqe)(काष्ठा mlx5e_rq*, u16);

पूर्णांक mlx5e_rq_set_handlers(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_params *params, bool xsk);
व्योम mlx5e_rq_set_trap_handlers(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_params *params);

क्रमागत mlx5e_rq_flag अणु
	MLX5E_RQ_FLAG_XDP_XMIT,
	MLX5E_RQ_FLAG_XDP_REसूचीECT,
पूर्ण;

काष्ठा mlx5e_rq_frag_info अणु
	पूर्णांक frag_size;
	पूर्णांक frag_stride;
पूर्ण;

काष्ठा mlx5e_rq_frags_info अणु
	काष्ठा mlx5e_rq_frag_info arr[MLX5E_MAX_RX_FRAGS];
	u8 num_frags;
	u8 log_num_frags;
	u8 wqe_bulk;
पूर्ण;

काष्ठा mlx5e_rq अणु
	/* data path */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा mlx5_wq_cyc          wq;
			काष्ठा mlx5e_wqe_frag_info *frags;
			काष्ठा mlx5e_dma_info      *di;
			काष्ठा mlx5e_rq_frags_info  info;
			mlx5e_fp_skb_from_cqe       skb_from_cqe;
		पूर्ण wqe;
		काष्ठा अणु
			काष्ठा mlx5_wq_ll      wq;
			काष्ठा mlx5e_umr_wqe   umr_wqe;
			काष्ठा mlx5e_mpw_info *info;
			mlx5e_fp_skb_from_cqe_mpwrq skb_from_cqe_mpwrq;
			u16                    num_strides;
			u16                    actual_wq_head;
			u8                     log_stride_sz;
			u8                     umr_in_progress;
			u8                     umr_last_bulk;
			u8                     umr_completed;
		पूर्ण mpwqe;
	पूर्ण;
	काष्ठा अणु
		u16            headroom;
		u32            frame0_sz;
		u8             map_dir;   /* dma map direction */
	पूर्ण buff;

	काष्ठा device         *pdev;
	काष्ठा net_device     *netdev;
	काष्ठा mlx5e_rq_stats *stats;
	काष्ठा mlx5e_cq        cq;
	काष्ठा mlx5e_cq_decomp cqd;
	काष्ठा mlx5e_page_cache page_cache;
	काष्ठा hwtstamp_config *tstamp;
	काष्ठा mlx5_घड़ी      *घड़ी;
	काष्ठा mlx5e_icosq    *icosq;
	काष्ठा mlx5e_priv     *priv;

	mlx5e_fp_handle_rx_cqe handle_rx_cqe;
	mlx5e_fp_post_rx_wqes  post_wqes;
	mlx5e_fp_dealloc_wqe   dealloc_wqe;

	अचिन्हित दीर्घ          state;
	पूर्णांक                    ix;
	अचिन्हित पूर्णांक           hw_mtu;

	काष्ठा dim         dim; /* Dynamic Interrupt Moderation */

	/* XDP */
	काष्ठा bpf_prog __rcu *xdp_prog;
	काष्ठा mlx5e_xdpsq    *xdpsq;
	DECLARE_BITMAP(flags, 8);
	काष्ठा page_pool      *page_pool;

	/* AF_XDP zero-copy */
	काष्ठा xsk_buff_pool  *xsk_pool;

	काष्ठा work_काष्ठा     recover_work;

	/* control */
	काष्ठा mlx5_wq_ctrl    wq_ctrl;
	__be32                 mkey_be;
	u8                     wq_type;
	u32                    rqn;
	काष्ठा mlx5_core_dev  *mdev;
	काष्ठा mlx5_core_mkey  umr_mkey;
	काष्ठा mlx5e_dma_info  wqe_overflow;

	/* XDP पढ़ो-mostly */
	काष्ठा xdp_rxq_info    xdp_rxq;
	cqe_ts_to_ns           ptp_cyc2समय;
पूर्ण ____cacheline_aligned_in_smp;

क्रमागत mlx5e_channel_state अणु
	MLX5E_CHANNEL_STATE_XSK,
	MLX5E_CHANNEL_NUM_STATES
पूर्ण;

काष्ठा mlx5e_channel अणु
	/* data path */
	काष्ठा mlx5e_rq            rq;
	काष्ठा mlx5e_xdpsq         rq_xdpsq;
	काष्ठा mlx5e_txqsq         sq[MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_icosq         icosq;   /* पूर्णांकernal control operations */
	काष्ठा mlx5e_txqsq __rcu * __rcu *qos_sqs;
	bool                       xdp;
	काष्ठा napi_काष्ठा         napi;
	काष्ठा device             *pdev;
	काष्ठा net_device         *netdev;
	__be32                     mkey_be;
	u16                        qos_sqs_size;
	u8                         num_tc;
	u8                         lag_port;

	/* XDP_REसूचीECT */
	काष्ठा mlx5e_xdpsq         xdpsq;

	/* AF_XDP zero-copy */
	काष्ठा mlx5e_rq            xskrq;
	काष्ठा mlx5e_xdpsq         xsksq;

	/* Async ICOSQ */
	काष्ठा mlx5e_icosq         async_icosq;
	/* async_icosq can be accessed from any CPU - the spinlock protects it. */
	spinlock_t                 async_icosq_lock;

	/* data path - accessed per napi poll */
	स्थिर काष्ठा cpumask	  *aff_mask;
	काष्ठा mlx5e_ch_stats     *stats;

	/* control */
	काष्ठा mlx5e_priv         *priv;
	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा hwtstamp_config    *tstamp;
	DECLARE_BITMAP(state, MLX5E_CHANNEL_NUM_STATES);
	पूर्णांक                        ix;
	पूर्णांक                        cpu;
पूर्ण;

काष्ठा mlx5e_ptp;

काष्ठा mlx5e_channels अणु
	काष्ठा mlx5e_channel **c;
	काष्ठा mlx5e_ptp      *ptp;
	अचिन्हित पूर्णांक           num;
	काष्ठा mlx5e_params    params;
पूर्ण;

काष्ठा mlx5e_channel_stats अणु
	काष्ठा mlx5e_ch_stats ch;
	काष्ठा mlx5e_sq_stats sq[MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_rq_stats rq;
	काष्ठा mlx5e_rq_stats xskrq;
	काष्ठा mlx5e_xdpsq_stats rq_xdpsq;
	काष्ठा mlx5e_xdpsq_stats xdpsq;
	काष्ठा mlx5e_xdpsq_stats xsksq;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा mlx5e_ptp_stats अणु
	काष्ठा mlx5e_ch_stats ch;
	काष्ठा mlx5e_sq_stats sq[MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_ptp_cq_stats cq[MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_rq_stats rq;
पूर्ण ____cacheline_aligned_in_smp;

क्रमागत अणु
	MLX5E_STATE_OPENED,
	MLX5E_STATE_DESTROYING,
	MLX5E_STATE_XDP_TX_ENABLED,
	MLX5E_STATE_XDP_ACTIVE,
पूर्ण;

काष्ठा mlx5e_rqt अणु
	u32              rqtn;
	bool		 enabled;
पूर्ण;

काष्ठा mlx5e_tir अणु
	u32		  tirn;
	काष्ठा mlx5e_rqt  rqt;
	काष्ठा list_head  list;
पूर्ण;

क्रमागत अणु
	MLX5E_TC_PRIO = 0,
	MLX5E_NIC_PRIO
पूर्ण;

काष्ठा mlx5e_rss_params अणु
	u32	indirection_rqt[MLX5E_INसूची_RQT_SIZE];
	u32	rx_hash_fields[MLX5E_NUM_INसूची_TIRS];
	u8	toeplitz_hash_key[40];
	u8	hfunc;
पूर्ण;

काष्ठा mlx5e_modअगरy_sq_param अणु
	पूर्णांक curr_state;
	पूर्णांक next_state;
	पूर्णांक rl_update;
	पूर्णांक rl_index;
	bool qos_update;
	u16 qos_queue_group_id;
पूर्ण;

#अगर IS_ENABLED(CONFIG_PCI_HYPERV_INTERFACE)
काष्ठा mlx5e_hv_vhca_stats_agent अणु
	काष्ठा mlx5_hv_vhca_agent *agent;
	काष्ठा delayed_work        work;
	u16                        delay;
	व्योम                      *buf;
पूर्ण;
#पूर्ण_अगर

काष्ठा mlx5e_xsk अणु
	/* XSK buffer pools are stored separately from channels,
	 * because we करोn't want to lose them when channels are
	 * recreated. The kernel also stores buffer pool, but it करोesn't
	 * distinguish between zero-copy and non-zero-copy UMEMs, so
	 * rely on our mechanism.
	 */
	काष्ठा xsk_buff_pool **pools;
	u16 refcnt;
	bool ever_used;
पूर्ण;

/* Temporary storage क्रम variables that are allocated when काष्ठा mlx5e_priv is
 * initialized, and used where we can't allocate them because that functions
 * must not fail. Use with care and make sure the same variable is not used
 * simultaneously by multiple users.
 */
काष्ठा mlx5e_scratchpad अणु
	cpumask_var_t cpumask;
पूर्ण;

काष्ठा mlx5e_htb अणु
	DECLARE_HASHTABLE(qos_tc2node, order_base_2(MLX5E_QOS_MAX_LEAF_NODES));
	DECLARE_BITMAP(qos_used_qids, MLX5E_QOS_MAX_LEAF_NODES);
	काष्ठा mlx5e_sq_stats **qos_sq_stats;
	u16 max_qos_sqs;
	u16 maj_id;
	u16 defcls;
पूर्ण;

काष्ठा mlx5e_trap;

काष्ठा mlx5e_priv अणु
	/* priv data path fields - start */
	/* +1 क्रम port ptp ts */
	काष्ठा mlx5e_txqsq *txq2sq[(MLX5E_MAX_NUM_CHANNELS + 1) * MLX5E_MAX_NUM_TC +
				   MLX5E_QOS_MAX_LEAF_NODES];
	पूर्णांक channel_tc2realtxq[MLX5E_MAX_NUM_CHANNELS][MLX5E_MAX_NUM_TC];
	पूर्णांक port_ptp_tc2realtxq[MLX5E_MAX_NUM_TC];
#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
	काष्ठा mlx5e_dcbx_dp       dcbx_dp;
#पूर्ण_अगर
	/* priv data path fields - end */

	u32                        msglevel;
	अचिन्हित दीर्घ              state;
	काष्ठा mutex               state_lock; /* Protects Interface state */
	काष्ठा mlx5e_rq            drop_rq;

	काष्ठा mlx5e_channels      channels;
	u32                        tisn[MLX5_MAX_PORTS][MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_rqt           indir_rqt;
	काष्ठा mlx5e_tir           indir_tir[MLX5E_NUM_INसूची_TIRS];
	काष्ठा mlx5e_tir           inner_indir_tir[MLX5E_NUM_INसूची_TIRS];
	काष्ठा mlx5e_tir           direct_tir[MLX5E_MAX_NUM_CHANNELS];
	काष्ठा mlx5e_tir           xsk_tir[MLX5E_MAX_NUM_CHANNELS];
	काष्ठा mlx5e_tir           ptp_tir;
	काष्ठा mlx5e_rss_params    rss_params;
	u32                        tx_rates[MLX5E_MAX_NUM_SQS];

	काष्ठा mlx5e_flow_steering fs;

	काष्ठा workqueue_काष्ठा    *wq;
	काष्ठा work_काष्ठा         update_carrier_work;
	काष्ठा work_काष्ठा         set_rx_mode_work;
	काष्ठा work_काष्ठा         tx_समयout_work;
	काष्ठा work_काष्ठा         update_stats_work;
	काष्ठा work_काष्ठा         monitor_counters_work;
	काष्ठा mlx5_nb             monitor_counters_nb;

	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा net_device         *netdev;
	काष्ठा mlx5e_trap         *en_trap;
	काष्ठा mlx5e_stats         stats;
	काष्ठा mlx5e_channel_stats channel_stats[MLX5E_MAX_NUM_CHANNELS];
	काष्ठा mlx5e_channel_stats trap_stats;
	काष्ठा mlx5e_ptp_stats     ptp_stats;
	u16                        max_nch;
	u8                         max_खोलोed_tc;
	bool                       tx_ptp_खोलोed;
	bool                       rx_ptp_खोलोed;
	काष्ठा hwtstamp_config     tstamp;
	u16                        q_counter;
	u16                        drop_rq_q_counter;
	काष्ठा notअगरier_block      events_nb;
	काष्ठा notअगरier_block      blocking_events_nb;
	पूर्णांक                        num_tc_x_num_ch;

	काष्ठा udp_tunnel_nic_info nic_info;
#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
	काष्ठा mlx5e_dcbx          dcbx;
#पूर्ण_अगर

	स्थिर काष्ठा mlx5e_profile *profile;
	व्योम                      *ppriv;
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	काष्ठा mlx5e_ipsec        *ipsec;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_TLS
	काष्ठा mlx5e_tls          *tls;
#पूर्ण_अगर
	काष्ठा devlink_health_reporter *tx_reporter;
	काष्ठा devlink_health_reporter *rx_reporter;
	काष्ठा mlx5e_xsk           xsk;
#अगर IS_ENABLED(CONFIG_PCI_HYPERV_INTERFACE)
	काष्ठा mlx5e_hv_vhca_stats_agent stats_agent;
#पूर्ण_अगर
	काष्ठा mlx5e_scratchpad    scratchpad;
	काष्ठा mlx5e_htb           htb;
पूर्ण;

काष्ठा mlx5e_rx_handlers अणु
	mlx5e_fp_handle_rx_cqe handle_rx_cqe;
	mlx5e_fp_handle_rx_cqe handle_rx_cqe_mpwqe;
पूर्ण;

बाह्य स्थिर काष्ठा mlx5e_rx_handlers mlx5e_rx_handlers_nic;

काष्ठा mlx5e_profile अणु
	पूर्णांक	(*init)(काष्ठा mlx5_core_dev *mdev,
			काष्ठा net_device *netdev);
	व्योम	(*cleanup)(काष्ठा mlx5e_priv *priv);
	पूर्णांक	(*init_rx)(काष्ठा mlx5e_priv *priv);
	व्योम	(*cleanup_rx)(काष्ठा mlx5e_priv *priv);
	पूर्णांक	(*init_tx)(काष्ठा mlx5e_priv *priv);
	व्योम	(*cleanup_tx)(काष्ठा mlx5e_priv *priv);
	व्योम	(*enable)(काष्ठा mlx5e_priv *priv);
	व्योम	(*disable)(काष्ठा mlx5e_priv *priv);
	पूर्णांक	(*update_rx)(काष्ठा mlx5e_priv *priv);
	व्योम	(*update_stats)(काष्ठा mlx5e_priv *priv);
	व्योम	(*update_carrier)(काष्ठा mlx5e_priv *priv);
	अचिन्हित पूर्णांक (*stats_grps_num)(काष्ठा mlx5e_priv *priv);
	mlx5e_stats_grp_t *stats_grps;
	स्थिर काष्ठा mlx5e_rx_handlers *rx_handlers;
	पूर्णांक	max_tc;
	u8	rq_groups;
	bool	rx_ptp_support;
पूर्ण;

व्योम mlx5e_build_ptys2ethtool_map(व्योम);

bool mlx5e_check_fragmented_striding_rq_cap(काष्ठा mlx5_core_dev *mdev);

व्योम mlx5e_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats);
व्योम mlx5e_fold_sw_stats64(काष्ठा mlx5e_priv *priv, काष्ठा rtnl_link_stats64 *s);

व्योम mlx5e_init_l2_addr(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_self_test_num(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_self_test(काष्ठा net_device *ndev, काष्ठा ethtool_test *etest,
		     u64 *buf);
व्योम mlx5e_set_rx_mode_work(काष्ठा work_काष्ठा *work);

पूर्णांक mlx5e_hwstamp_set(काष्ठा mlx5e_priv *priv, काष्ठा अगरreq *अगरr);
पूर्णांक mlx5e_hwstamp_get(काष्ठा mlx5e_priv *priv, काष्ठा अगरreq *अगरr);
पूर्णांक mlx5e_modअगरy_rx_cqe_compression_locked(काष्ठा mlx5e_priv *priv, bool val);

पूर्णांक mlx5e_vlan_rx_add_vid(काष्ठा net_device *dev, __always_unused __be16 proto,
			  u16 vid);
पूर्णांक mlx5e_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __always_unused __be16 proto,
			   u16 vid);
व्योम mlx5e_बारtamp_init(काष्ठा mlx5e_priv *priv);

काष्ठा mlx5e_redirect_rqt_param अणु
	bool is_rss;
	जोड़ अणु
		u32 rqn; /* Direct RQN (Non-RSS) */
		काष्ठा अणु
			u8 hfunc;
			काष्ठा mlx5e_channels *channels;
		पूर्ण rss; /* RSS data */
	पूर्ण;
पूर्ण;

पूर्णांक mlx5e_redirect_rqt(काष्ठा mlx5e_priv *priv, u32 rqtn, पूर्णांक sz,
		       काष्ठा mlx5e_redirect_rqt_param rrp);
व्योम mlx5e_build_indir_tir_ctx_hash(काष्ठा mlx5e_rss_params *rss_params,
				    स्थिर काष्ठा mlx5e_tirc_config *ttconfig,
				    व्योम *tirc, bool inner);
व्योम mlx5e_modअगरy_tirs_hash(काष्ठा mlx5e_priv *priv, व्योम *in);
काष्ठा mlx5e_tirc_config mlx5e_tirc_get_शेष_config(क्रमागत mlx5e_traffic_types tt);

काष्ठा mlx5e_xsk_param;

काष्ठा mlx5e_rq_param;
पूर्णांक mlx5e_खोलो_rq(काष्ठा mlx5e_params *params, काष्ठा mlx5e_rq_param *param,
		  काष्ठा mlx5e_xsk_param *xsk, पूर्णांक node,
		  काष्ठा mlx5e_rq *rq);
पूर्णांक mlx5e_रुको_क्रम_min_rx_wqes(काष्ठा mlx5e_rq *rq, पूर्णांक रुको_समय);
व्योम mlx5e_deactivate_rq(काष्ठा mlx5e_rq *rq);
व्योम mlx5e_बंद_rq(काष्ठा mlx5e_rq *rq);
पूर्णांक mlx5e_create_rq(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_rq_param *param);
व्योम mlx5e_destroy_rq(काष्ठा mlx5e_rq *rq);

काष्ठा mlx5e_sq_param;
पूर्णांक mlx5e_खोलो_icosq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
		     काष्ठा mlx5e_sq_param *param, काष्ठा mlx5e_icosq *sq);
व्योम mlx5e_बंद_icosq(काष्ठा mlx5e_icosq *sq);
पूर्णांक mlx5e_खोलो_xdpsq(काष्ठा mlx5e_channel *c, काष्ठा mlx5e_params *params,
		     काष्ठा mlx5e_sq_param *param, काष्ठा xsk_buff_pool *xsk_pool,
		     काष्ठा mlx5e_xdpsq *sq, bool is_redirect);
व्योम mlx5e_बंद_xdpsq(काष्ठा mlx5e_xdpsq *sq);

काष्ठा mlx5e_create_cq_param अणु
	काष्ठा napi_काष्ठा *napi;
	काष्ठा mlx5e_ch_stats *ch_stats;
	पूर्णांक node;
	पूर्णांक ix;
पूर्ण;

काष्ठा mlx5e_cq_param;
पूर्णांक mlx5e_खोलो_cq(काष्ठा mlx5e_priv *priv, काष्ठा dim_cq_moder moder,
		  काष्ठा mlx5e_cq_param *param, काष्ठा mlx5e_create_cq_param *ccp,
		  काष्ठा mlx5e_cq *cq);
व्योम mlx5e_बंद_cq(काष्ठा mlx5e_cq *cq);

पूर्णांक mlx5e_खोलो_locked(काष्ठा net_device *netdev);
पूर्णांक mlx5e_बंद_locked(काष्ठा net_device *netdev);

पूर्णांक mlx5e_खोलो_channels(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_channels *chs);
व्योम mlx5e_बंद_channels(काष्ठा mlx5e_channels *chs);

/* Function poपूर्णांकer to be used to modअगरy HW or kernel settings जबतक
 * चयनing channels
 */
प्रकार पूर्णांक (*mlx5e_fp_preactivate)(काष्ठा mlx5e_priv *priv, व्योम *context);
#घोषणा MLX5E_DEFINE_PREACTIVATE_WRAPPER_CTX(fn) \
पूर्णांक fn##_ctx(काष्ठा mlx5e_priv *priv, व्योम *context) \
अणु \
	वापस fn(priv); \
पूर्ण
पूर्णांक mlx5e_safe_reखोलो_channels(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_safe_चयन_params(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_params *new_params,
			     mlx5e_fp_preactivate preactivate,
			     व्योम *context, bool reset);
पूर्णांक mlx5e_update_tx_netdev_queues(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_num_channels_changed(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_num_channels_changed_ctx(काष्ठा mlx5e_priv *priv, व्योम *context);
व्योम mlx5e_activate_priv_channels(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_deactivate_priv_channels(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ptp_rx_manage_fs_ctx(काष्ठा mlx5e_priv *priv, व्योम *ctx);

व्योम mlx5e_build_शेष_indir_rqt(u32 *indirection_rqt, पूर्णांक len,
				   पूर्णांक num_channels);

पूर्णांक mlx5e_modअगरy_rq_state(काष्ठा mlx5e_rq *rq, पूर्णांक curr_state, पूर्णांक next_state);
व्योम mlx5e_activate_rq(काष्ठा mlx5e_rq *rq);
व्योम mlx5e_deactivate_rq(काष्ठा mlx5e_rq *rq);
व्योम mlx5e_activate_icosq(काष्ठा mlx5e_icosq *icosq);
व्योम mlx5e_deactivate_icosq(काष्ठा mlx5e_icosq *icosq);

पूर्णांक mlx5e_modअगरy_sq(काष्ठा mlx5_core_dev *mdev, u32 sqn,
		    काष्ठा mlx5e_modअगरy_sq_param *p);
पूर्णांक mlx5e_खोलो_txqsq(काष्ठा mlx5e_channel *c, u32 tisn, पूर्णांक txq_ix,
		     काष्ठा mlx5e_params *params, काष्ठा mlx5e_sq_param *param,
		     काष्ठा mlx5e_txqsq *sq, पूर्णांक tc, u16 qos_queue_group_id, u16 qos_qid);
व्योम mlx5e_activate_txqsq(काष्ठा mlx5e_txqsq *sq);
व्योम mlx5e_deactivate_txqsq(काष्ठा mlx5e_txqsq *sq);
व्योम mlx5e_मुक्त_txqsq(काष्ठा mlx5e_txqsq *sq);
व्योम mlx5e_tx_disable_queue(काष्ठा netdev_queue *txq);
पूर्णांक mlx5e_alloc_txqsq_db(काष्ठा mlx5e_txqsq *sq, पूर्णांक numa);
व्योम mlx5e_मुक्त_txqsq_db(काष्ठा mlx5e_txqsq *sq);
काष्ठा mlx5e_create_sq_param;
पूर्णांक mlx5e_create_sq_rdy(काष्ठा mlx5_core_dev *mdev,
			काष्ठा mlx5e_sq_param *param,
			काष्ठा mlx5e_create_sq_param *csp,
			u16 qos_queue_group_id,
			u32 *sqn);
व्योम mlx5e_tx_err_cqe_work(काष्ठा work_काष्ठा *recover_work);
व्योम mlx5e_बंद_txqsq(काष्ठा mlx5e_txqsq *sq);

अटल अंतरभूत bool mlx5_tx_swp_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_ETH(mdev, swp) &&
		MLX5_CAP_ETH(mdev, swp_csum) && MLX5_CAP_ETH(mdev, swp_lso);
पूर्ण

बाह्य स्थिर काष्ठा ethtool_ops mlx5e_ethtool_ops;

पूर्णांक mlx5e_create_tir(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_tir *tir,
		     u32 *in);
व्योम mlx5e_destroy_tir(काष्ठा mlx5_core_dev *mdev,
		       काष्ठा mlx5e_tir *tir);
पूर्णांक mlx5e_create_mdev_resources(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5e_destroy_mdev_resources(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5e_refresh_tirs(काष्ठा mlx5e_priv *priv, bool enable_uc_lb,
		       bool enable_mc_lb);
व्योम mlx5e_mkey_set_relaxed_ordering(काष्ठा mlx5_core_dev *mdev, व्योम *mkc);

/* common netdev helpers */
व्योम mlx5e_create_q_counters(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_destroy_q_counters(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_खोलो_drop_rq(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_rq *drop_rq);
व्योम mlx5e_बंद_drop_rq(काष्ठा mlx5e_rq *drop_rq);
पूर्णांक mlx5e_init_di_list(काष्ठा mlx5e_rq *rq, पूर्णांक wq_sz, पूर्णांक node);
व्योम mlx5e_मुक्त_di_list(काष्ठा mlx5e_rq *rq);

पूर्णांक mlx5e_create_indirect_rqt(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_create_indirect_tirs(काष्ठा mlx5e_priv *priv, bool inner_ttc);
व्योम mlx5e_destroy_indirect_tirs(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_create_direct_rqts(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n);
व्योम mlx5e_destroy_direct_rqts(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n);
पूर्णांक mlx5e_create_direct_tirs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n);
व्योम mlx5e_destroy_direct_tirs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tir *tirs, पूर्णांक n);
व्योम mlx5e_destroy_rqt(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_rqt *rqt);

पूर्णांक mlx5e_create_tis(काष्ठा mlx5_core_dev *mdev, व्योम *in, u32 *tisn);
व्योम mlx5e_destroy_tis(काष्ठा mlx5_core_dev *mdev, u32 tisn);

पूर्णांक mlx5e_create_tises(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_destroy_tises(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_update_nic_rx(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_update_carrier(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_बंद(काष्ठा net_device *netdev);
पूर्णांक mlx5e_खोलो(काष्ठा net_device *netdev);

व्योम mlx5e_queue_update_stats(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_bits_invert(अचिन्हित दीर्घ a, पूर्णांक size);

पूर्णांक mlx5e_set_dev_port_mtu(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_set_dev_port_mtu_ctx(काष्ठा mlx5e_priv *priv, व्योम *context);
पूर्णांक mlx5e_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu,
		     mlx5e_fp_preactivate preactivate);
व्योम mlx5e_vxlan_set_netdev_info(काष्ठा mlx5e_priv *priv);

/* ethtool helpers */
व्योम mlx5e_ethtool_get_drvinfo(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_drvinfo *drvinfo);
व्योम mlx5e_ethtool_get_strings(काष्ठा mlx5e_priv *priv,
			       uपूर्णांक32_t stringset, uपूर्णांक8_t *data);
पूर्णांक mlx5e_ethtool_get_sset_count(काष्ठा mlx5e_priv *priv, पूर्णांक sset);
व्योम mlx5e_ethtool_get_ethtool_stats(काष्ठा mlx5e_priv *priv,
				     काष्ठा ethtool_stats *stats, u64 *data);
व्योम mlx5e_ethtool_get_ringparam(काष्ठा mlx5e_priv *priv,
				 काष्ठा ethtool_ringparam *param);
पूर्णांक mlx5e_ethtool_set_ringparam(काष्ठा mlx5e_priv *priv,
				काष्ठा ethtool_ringparam *param);
व्योम mlx5e_ethtool_get_channels(काष्ठा mlx5e_priv *priv,
				काष्ठा ethtool_channels *ch);
पूर्णांक mlx5e_ethtool_set_channels(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_channels *ch);
पूर्णांक mlx5e_ethtool_get_coalesce(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_coalesce *coal);
पूर्णांक mlx5e_ethtool_set_coalesce(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_coalesce *coal);
पूर्णांक mlx5e_ethtool_get_link_ksettings(काष्ठा mlx5e_priv *priv,
				     काष्ठा ethtool_link_ksettings *link_ksettings);
पूर्णांक mlx5e_ethtool_set_link_ksettings(काष्ठा mlx5e_priv *priv,
				     स्थिर काष्ठा ethtool_link_ksettings *link_ksettings);
पूर्णांक mlx5e_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key, u8 *hfunc);
पूर्णांक mlx5e_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir, स्थिर u8 *key,
		   स्थिर u8 hfunc);
पूर्णांक mlx5e_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
		    u32 *rule_locs);
पूर्णांक mlx5e_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd);
u32 mlx5e_ethtool_get_rxfh_key_size(काष्ठा mlx5e_priv *priv);
u32 mlx5e_ethtool_get_rxfh_indir_size(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ethtool_get_ts_info(काष्ठा mlx5e_priv *priv,
			      काष्ठा ethtool_ts_info *info);
पूर्णांक mlx5e_ethtool_flash_device(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_flash *flash);
व्योम mlx5e_ethtool_get_छोड़ोparam(काष्ठा mlx5e_priv *priv,
				  काष्ठा ethtool_छोड़ोparam *छोड़ोparam);
पूर्णांक mlx5e_ethtool_set_छोड़ोparam(काष्ठा mlx5e_priv *priv,
				 काष्ठा ethtool_छोड़ोparam *छोड़ोparam);

/* mlx5e generic netdev management API */
अटल अंतरभूत अचिन्हित पूर्णांक
mlx5e_calc_max_nch(काष्ठा mlx5e_priv *priv, स्थिर काष्ठा mlx5e_profile *profile)
अणु
	वापस priv->netdev->num_rx_queues / max_t(u8, profile->rq_groups, 1);
पूर्ण

पूर्णांक mlx5e_priv_init(काष्ठा mlx5e_priv *priv,
		    काष्ठा net_device *netdev,
		    काष्ठा mlx5_core_dev *mdev);
व्योम mlx5e_priv_cleanup(काष्ठा mlx5e_priv *priv);
काष्ठा net_device *
mlx5e_create_netdev(काष्ठा mlx5_core_dev *mdev, अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs);
पूर्णांक mlx5e_attach_netdev(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_detach_netdev(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_destroy_netdev(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_netdev_change_profile(काष्ठा mlx5e_priv *priv,
				स्थिर काष्ठा mlx5e_profile *new_profile, व्योम *new_ppriv);
व्योम mlx5e_netdev_attach_nic_profile(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_set_netdev_mtu_boundaries(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_build_nic_params(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_xsk *xsk, u16 mtu);
व्योम mlx5e_build_rss_params(काष्ठा mlx5e_rss_params *rss_params,
			    u16 num_channels);
व्योम mlx5e_rx_dim_work(काष्ठा work_काष्ठा *work);
व्योम mlx5e_tx_dim_work(काष्ठा work_काष्ठा *work);

netdev_features_t mlx5e_features_check(काष्ठा sk_buff *skb,
				       काष्ठा net_device *netdev,
				       netdev_features_t features);
पूर्णांक mlx5e_set_features(काष्ठा net_device *netdev, netdev_features_t features);
#अगर_घोषित CONFIG_MLX5_ESWITCH
पूर्णांक mlx5e_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vf, u8 *mac);
पूर्णांक mlx5e_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक min_tx_rate, पूर्णांक max_tx_rate);
पूर्णांक mlx5e_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf, काष्ठा अगरla_vf_info *ivi);
पूर्णांक mlx5e_get_vf_stats(काष्ठा net_device *dev, पूर्णांक vf, काष्ठा अगरla_vf_stats *vf_stats);
#पूर्ण_अगर
#पूर्ण_अगर /* __MLX5_EN_H__ */
