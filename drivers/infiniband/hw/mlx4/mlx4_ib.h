<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems.  All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX4_IB_H
#घोषणा MLX4_IB_H

#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_sa.h>

#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/करोorbell.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/mlx4/cq.h>

#घोषणा MLX4_IB_DRV_NAME	"mlx4_ib"

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर
#घोषणा pr_fmt(fmt)	"<" MLX4_IB_DRV_NAME "> %s: " fmt, __func__

#घोषणा mlx4_ib_warn(ibdev, क्रमmat, arg...) \
	dev_warn((ibdev)->dev.parent, MLX4_IB_DRV_NAME ": " क्रमmat, ## arg)

क्रमागत अणु
	MLX4_IB_SQ_MIN_WQE_SHIFT = 6,
	MLX4_IB_MAX_HEADROOM	 = 2048
पूर्ण;

#घोषणा MLX4_IB_SQ_HEADROOM(shअगरt)	((MLX4_IB_MAX_HEADROOM >> (shअगरt)) + 1)
#घोषणा MLX4_IB_SQ_MAX_SPARE		(MLX4_IB_SQ_HEADROOM(MLX4_IB_SQ_MIN_WQE_SHIFT))

/*module param to indicate अगर SM assigns the alias_GUID*/
बाह्य पूर्णांक mlx4_ib_sm_guid_assign;

#घोषणा MLX4_IB_UC_STEER_QPN_ALIGN 1
#घोषणा MLX4_IB_UC_MAX_NUM_QPS     256

क्रमागत hw_bar_type अणु
	HW_BAR_BF,
	HW_BAR_DB,
	HW_BAR_CLOCK,
	HW_BAR_COUNT
पूर्ण;

काष्ठा mlx4_ib_ucontext अणु
	काष्ठा ib_ucontext	ibucontext;
	काष्ठा mlx4_uar		uar;
	काष्ठा list_head	db_page_list;
	काष्ठा mutex		db_page_mutex;
	काष्ठा list_head	wqn_ranges_list;
	काष्ठा mutex		wqn_ranges_mutex; /* protect wqn_ranges_list */
पूर्ण;

काष्ठा mlx4_ib_pd अणु
	काष्ठा ib_pd		ibpd;
	u32			pdn;
पूर्ण;

काष्ठा mlx4_ib_xrcd अणु
	काष्ठा ib_xrcd		ibxrcd;
	u32			xrcdn;
	काष्ठा ib_pd	       *pd;
	काष्ठा ib_cq	       *cq;
पूर्ण;

काष्ठा mlx4_ib_cq_buf अणु
	काष्ठा mlx4_buf		buf;
	काष्ठा mlx4_mtt		mtt;
	पूर्णांक			entry_size;
पूर्ण;

काष्ठा mlx4_ib_cq_resize अणु
	काष्ठा mlx4_ib_cq_buf	buf;
	पूर्णांक			cqe;
पूर्ण;

काष्ठा mlx4_ib_cq अणु
	काष्ठा ib_cq		ibcq;
	काष्ठा mlx4_cq		mcq;
	काष्ठा mlx4_ib_cq_buf	buf;
	काष्ठा mlx4_ib_cq_resize *resize_buf;
	काष्ठा mlx4_db		db;
	spinlock_t		lock;
	काष्ठा mutex		resize_mutex;
	काष्ठा ib_umem	       *umem;
	काष्ठा ib_umem	       *resize_umem;
	पूर्णांक			create_flags;
	/* List of qps that it serves.*/
	काष्ठा list_head		send_qp_list;
	काष्ठा list_head		recv_qp_list;
पूर्ण;

#घोषणा MLX4_MR_PAGES_ALIGN 0x40

काष्ठा mlx4_ib_mr अणु
	काष्ठा ib_mr		ibmr;
	__be64			*pages;
	dma_addr_t		page_map;
	u32			npages;
	u32			max_pages;
	काष्ठा mlx4_mr		mmr;
	काष्ठा ib_umem	       *umem;
	माप_प्रकार			page_map_size;
पूर्ण;

काष्ठा mlx4_ib_mw अणु
	काष्ठा ib_mw		ibmw;
	काष्ठा mlx4_mw		mmw;
पूर्ण;

#घोषणा MAX_REGS_PER_FLOW 2

काष्ठा mlx4_flow_reg_id अणु
	u64 id;
	u64 mirror;
पूर्ण;

काष्ठा mlx4_ib_flow अणु
	काष्ठा ib_flow ibflow;
	/* translating DMFS verbs snअगरfer rule to FW API requires two reg IDs */
	काष्ठा mlx4_flow_reg_id reg_id[MAX_REGS_PER_FLOW];
पूर्ण;

काष्ठा mlx4_ib_wq अणु
	u64		       *wrid;
	spinlock_t		lock;
	पूर्णांक			wqe_cnt;
	पूर्णांक			max_post;
	पूर्णांक			max_gs;
	पूर्णांक			offset;
	पूर्णांक			wqe_shअगरt;
	अचिन्हित		head;
	अचिन्हित		tail;
पूर्ण;

क्रमागत अणु
	MLX4_IB_QP_CREATE_ROCE_V2_GSI = IB_QP_CREATE_RESERVED_START
पूर्ण;

क्रमागत mlx4_ib_qp_flags अणु
	MLX4_IB_QP_LSO = IB_QP_CREATE_IPOIB_UD_LSO,
	MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK = IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK,
	MLX4_IB_QP_NETIF = IB_QP_CREATE_NETIF_QP,
	MLX4_IB_QP_SCATTER_FCS = IB_QP_CREATE_SCATTER_FCS,

	/* Mellanox specअगरic flags start from IB_QP_CREATE_RESERVED_START */
	MLX4_IB_ROCE_V2_GSI_QP = MLX4_IB_QP_CREATE_ROCE_V2_GSI,
	MLX4_IB_SRIOV_TUNNEL_QP = 1 << 30,
	MLX4_IB_SRIOV_SQP = 1 << 31,
पूर्ण;

काष्ठा mlx4_ib_gid_entry अणु
	काष्ठा list_head	list;
	जोड़ ib_gid		gid;
	पूर्णांक			added;
	u8			port;
पूर्ण;

क्रमागत mlx4_ib_qp_type अणु
	/*
	 * IB_QPT_SMI and IB_QPT_GSI have to be the first two entries
	 * here (and in that order) since the MAD layer uses them as
	 * indices पूर्णांकo a 2-entry table.
	 */
	MLX4_IB_QPT_SMI = IB_QPT_SMI,
	MLX4_IB_QPT_GSI = IB_QPT_GSI,

	MLX4_IB_QPT_RC = IB_QPT_RC,
	MLX4_IB_QPT_UC = IB_QPT_UC,
	MLX4_IB_QPT_UD = IB_QPT_UD,
	MLX4_IB_QPT_RAW_IPV6 = IB_QPT_RAW_IPV6,
	MLX4_IB_QPT_RAW_ETHERTYPE = IB_QPT_RAW_ETHERTYPE,
	MLX4_IB_QPT_RAW_PACKET = IB_QPT_RAW_PACKET,
	MLX4_IB_QPT_XRC_INI = IB_QPT_XRC_INI,
	MLX4_IB_QPT_XRC_TGT = IB_QPT_XRC_TGT,

	MLX4_IB_QPT_PROXY_SMI_OWNER	= 1 << 16,
	MLX4_IB_QPT_PROXY_SMI		= 1 << 17,
	MLX4_IB_QPT_PROXY_GSI		= 1 << 18,
	MLX4_IB_QPT_TUN_SMI_OWNER	= 1 << 19,
	MLX4_IB_QPT_TUN_SMI		= 1 << 20,
	MLX4_IB_QPT_TUN_GSI		= 1 << 21,
पूर्ण;

#घोषणा MLX4_IB_QPT_ANY_SRIOV	(MLX4_IB_QPT_PROXY_SMI_OWNER | \
	MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI | MLX4_IB_QPT_TUN_SMI_OWNER | \
	MLX4_IB_QPT_TUN_SMI | MLX4_IB_QPT_TUN_GSI)

क्रमागत mlx4_ib_mad_अगरc_flags अणु
	MLX4_MAD_IFC_IGNORE_MKEY	= 1,
	MLX4_MAD_IFC_IGNORE_BKEY	= 2,
	MLX4_MAD_IFC_IGNORE_KEYS	= (MLX4_MAD_IFC_IGNORE_MKEY |
					   MLX4_MAD_IFC_IGNORE_BKEY),
	MLX4_MAD_IFC_NET_VIEW		= 4,
पूर्ण;

क्रमागत अणु
	MLX4_NUM_TUNNEL_BUFS		= 512,
	MLX4_NUM_WIRE_BUFS		= 2048,
पूर्ण;

काष्ठा mlx4_ib_tunnel_header अणु
	काष्ठा mlx4_av av;
	__be32 remote_qpn;
	__be32 qkey;
	__be16 vlan;
	u8 mac[6];
	__be16 pkey_index;
	u8 reserved[6];
पूर्ण;

काष्ठा mlx4_ib_buf अणु
	व्योम *addr;
	dma_addr_t map;
पूर्ण;

काष्ठा mlx4_rcv_tunnel_hdr अणु
	__be32 flags_src_qp; /* flags[6:5] is defined क्रम VLANs:
			      * 0x0 - no vlan was in the packet
			      * 0x01 - C-VLAN was in the packet */
	u8 g_ml_path; /* gid bit stands क्रम ipv6/4 header in RoCE */
	u8 reserved;
	__be16 pkey_index;
	__be16 sl_vid;
	__be16 slid_mac_47_32;
	__be32 mac_31_0;
पूर्ण;

काष्ठा mlx4_ib_proxy_sqp_hdr अणु
	काष्ठा ib_grh grh;
	काष्ठा mlx4_rcv_tunnel_hdr tun;
पूर्ण  __packed;

काष्ठा mlx4_roce_smac_vlan_info अणु
	u64 smac;
	पूर्णांक smac_index;
	पूर्णांक smac_port;
	u64 candidate_smac;
	पूर्णांक candidate_smac_index;
	पूर्णांक candidate_smac_port;
	u16 vid;
	पूर्णांक vlan_index;
	पूर्णांक vlan_port;
	u16 candidate_vid;
	पूर्णांक candidate_vlan_index;
	पूर्णांक candidate_vlan_port;
	पूर्णांक update_vid;
पूर्ण;

काष्ठा mlx4_wqn_range अणु
	पूर्णांक			base_wqn;
	पूर्णांक			size;
	पूर्णांक			refcount;
	bool			dirty;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा mlx4_ib_rss अणु
	अचिन्हित पूर्णांक		base_qpn_tbl_sz;
	u8			flags;
	u8			rss_key[MLX4_EN_RSS_KEY_SIZE];
पूर्ण;

क्रमागत अणु
	/*
	 * Largest possible UD header: send with GRH and immediate
	 * data plus 18 bytes क्रम an Ethernet header with VLAN/802.1Q
	 * tag.  (LRH would only use 8 bytes, so Ethernet is the
	 * biggest हाल)
	 */
	MLX4_IB_UD_HEADER_SIZE		= 82,
	MLX4_IB_LSO_HEADER_SPARE	= 128,
पूर्ण;

काष्ठा mlx4_ib_sqp अणु
	पूर्णांक pkey_index;
	u32 qkey;
	u32 send_psn;
	काष्ठा ib_ud_header ud_header;
	u8 header_buf[MLX4_IB_UD_HEADER_SIZE];
	काष्ठा ib_qp *roce_v2_gsi;
पूर्ण;

काष्ठा mlx4_ib_qp अणु
	जोड़ अणु
		काष्ठा ib_qp	ibqp;
		काष्ठा ib_wq	ibwq;
	पूर्ण;
	काष्ठा mlx4_qp		mqp;
	काष्ठा mlx4_buf		buf;

	काष्ठा mlx4_db		db;
	काष्ठा mlx4_ib_wq	rq;

	u32			करोorbell_qpn;
	__be32			sq_संकेत_bits;
	अचिन्हित		sq_next_wqe;
	पूर्णांक			sq_spare_wqes;
	काष्ठा mlx4_ib_wq	sq;

	क्रमागत mlx4_ib_qp_type	mlx4_ib_qp_type;
	काष्ठा ib_umem	       *umem;
	काष्ठा mlx4_mtt		mtt;
	पूर्णांक			buf_size;
	काष्ठा mutex		mutex;
	u16			xrcdn;
	u32			flags;
	u8			port;
	u8			alt_port;
	u8			atomic_rd_en;
	u8			resp_depth;
	u8			sq_no_prefetch;
	u8			state;
	पूर्णांक			mlx_type;
	u32			inl_recv_sz;
	काष्ठा list_head	gid_list;
	काष्ठा list_head	steering_rules;
	काष्ठा mlx4_ib_buf	*sqp_proxy_rcv;
	काष्ठा mlx4_roce_smac_vlan_info pri;
	काष्ठा mlx4_roce_smac_vlan_info alt;
	u64			reg_id;
	काष्ठा list_head	qps_list;
	काष्ठा list_head	cq_recv_list;
	काष्ठा list_head	cq_send_list;
	काष्ठा counter_index	*counter_index;
	काष्ठा mlx4_wqn_range	*wqn_range;
	/* Number of RSS QP parents that uses this WQ */
	u32			rss_usecnt;
	जोड़ अणु
		काष्ठा mlx4_ib_rss *rss_ctx;
		काष्ठा mlx4_ib_sqp *sqp;
	पूर्ण;
पूर्ण;

काष्ठा mlx4_ib_srq अणु
	काष्ठा ib_srq		ibsrq;
	काष्ठा mlx4_srq		msrq;
	काष्ठा mlx4_buf		buf;
	काष्ठा mlx4_db		db;
	u64		       *wrid;
	spinlock_t		lock;
	पूर्णांक			head;
	पूर्णांक			tail;
	u16			wqe_ctr;
	काष्ठा ib_umem	       *umem;
	काष्ठा mlx4_mtt		mtt;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा mlx4_ib_ah अणु
	काष्ठा ib_ah		ibah;
	जोड़ mlx4_ext_av       av;
पूर्ण;

काष्ठा mlx4_ib_rwq_ind_table अणु
	काष्ठा ib_rwq_ind_table ib_rwq_ind_tbl;
पूर्ण;

/****************************************/
/* alias guid support */
/****************************************/
#घोषणा NUM_PORT_ALIAS_GUID		2
#घोषणा NUM_ALIAS_GUID_IN_REC		8
#घोषणा NUM_ALIAS_GUID_REC_IN_PORT	16
#घोषणा GUID_REC_SIZE			8
#घोषणा NUM_ALIAS_GUID_PER_PORT		128
#घोषणा MLX4_NOT_SET_GUID		(0x00LL)
#घोषणा MLX4_GUID_FOR_DELETE_VAL	(~(0x00LL))

क्रमागत mlx4_guid_alias_rec_status अणु
	MLX4_GUID_INFO_STATUS_IDLE,
	MLX4_GUID_INFO_STATUS_SET,
पूर्ण;

#घोषणा GUID_STATE_NEED_PORT_INIT 0x01

क्रमागत mlx4_guid_alias_rec_method अणु
	MLX4_GUID_INFO_RECORD_SET	= IB_MGMT_METHOD_SET,
	MLX4_GUID_INFO_RECORD_DELETE	= IB_SA_METHOD_DELETE,
पूर्ण;

काष्ठा mlx4_sriov_alias_guid_info_rec_det अणु
	u8 all_recs[GUID_REC_SIZE * NUM_ALIAS_GUID_IN_REC];
	ib_sa_comp_mask guid_indexes; /*indicates what from the 8 records are valid*/
	क्रमागत mlx4_guid_alias_rec_status status; /*indicates the administraively status of the record.*/
	अचिन्हित पूर्णांक guids_retry_schedule[NUM_ALIAS_GUID_IN_REC];
	u64 समय_प्रकारo_run;
पूर्ण;

काष्ठा mlx4_sriov_alias_guid_port_rec_det अणु
	काष्ठा mlx4_sriov_alias_guid_info_rec_det all_rec_per_port[NUM_ALIAS_GUID_REC_IN_PORT];
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work alias_guid_work;
	u32 port;
	u32 state_flags;
	काष्ठा mlx4_sriov_alias_guid *parent;
	काष्ठा list_head cb_list;
पूर्ण;

काष्ठा mlx4_sriov_alias_guid अणु
	काष्ठा mlx4_sriov_alias_guid_port_rec_det ports_guid[MLX4_MAX_PORTS];
	spinlock_t ag_work_lock;
	काष्ठा ib_sa_client *sa_client;
पूर्ण;

काष्ठा mlx4_ib_demux_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा mlx4_ib_dev     *dev;
	पूर्णांक			slave;
	पूर्णांक			करो_init;
	u8			port;

पूर्ण;

काष्ठा mlx4_ib_tun_tx_buf अणु
	काष्ठा mlx4_ib_buf buf;
	काष्ठा ib_ah *ah;
पूर्ण;

काष्ठा mlx4_ib_demux_pv_qp अणु
	काष्ठा ib_qp *qp;
	क्रमागत ib_qp_type proxy_qpt;
	काष्ठा mlx4_ib_buf *ring;
	काष्ठा mlx4_ib_tun_tx_buf *tx_ring;
	spinlock_t tx_lock;
	अचिन्हित tx_ix_head;
	अचिन्हित tx_ix_tail;
पूर्ण;

क्रमागत mlx4_ib_demux_pv_state अणु
	DEMUX_PV_STATE_DOWN,
	DEMUX_PV_STATE_STARTING,
	DEMUX_PV_STATE_ACTIVE,
	DEMUX_PV_STATE_DOWNING,
पूर्ण;

काष्ठा mlx4_ib_demux_pv_ctx अणु
	पूर्णांक port;
	पूर्णांक slave;
	क्रमागत mlx4_ib_demux_pv_state state;
	पूर्णांक has_smi;
	काष्ठा ib_device *ib_dev;
	काष्ठा ib_cq *cq;
	काष्ठा ib_pd *pd;
	काष्ठा work_काष्ठा work;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा workqueue_काष्ठा *wi_wq;
	काष्ठा mlx4_ib_demux_pv_qp qp[2];
पूर्ण;

काष्ठा mlx4_ib_demux_ctx अणु
	काष्ठा ib_device *ib_dev;
	पूर्णांक port;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा workqueue_काष्ठा *wi_wq;
	काष्ठा workqueue_काष्ठा *ud_wq;
	spinlock_t ud_lock;
	atomic64_t subnet_prefix;
	__be64 guid_cache[128];
	काष्ठा mlx4_ib_dev *dev;
	/* the following lock protects both mcg_table and mcg_mgid0_list */
	काष्ठा mutex		mcg_table_lock;
	काष्ठा rb_root		mcg_table;
	काष्ठा list_head	mcg_mgid0_list;
	काष्ठा workqueue_काष्ठा	*mcg_wq;
	काष्ठा mlx4_ib_demux_pv_ctx **tun;
	atomic_t tid;
	पूर्णांक    flushing; /* flushing the work queue */
पूर्ण;

काष्ठा mlx4_ib_sriov अणु
	काष्ठा mlx4_ib_demux_ctx demux[MLX4_MAX_PORTS];
	काष्ठा mlx4_ib_demux_pv_ctx *sqps[MLX4_MAX_PORTS];
	/* when using this spinlock you should use "irq" because
	 * it may be called from पूर्णांकerrupt context.*/
	spinlock_t going_करोwn_lock;
	पूर्णांक is_going_करोwn;

	काष्ठा mlx4_sriov_alias_guid alias_guid;

	/* CM paraभवization fields */
	काष्ठा xarray pv_id_table;
	u32 pv_id_next;
	spinlock_t id_map_lock;
	काष्ठा rb_root sl_id_map;
	काष्ठा list_head cm_list;
	काष्ठा xarray xa_rej_पंचांगout;
पूर्ण;

काष्ठा gid_cache_context अणु
	पूर्णांक real_index;
	पूर्णांक refcount;
पूर्ण;

काष्ठा gid_entry अणु
	जोड़ ib_gid	gid;
	क्रमागत ib_gid_type gid_type;
	काष्ठा gid_cache_context *ctx;
	u16 vlan_id;
पूर्ण;

काष्ठा mlx4_port_gid_table अणु
	काष्ठा gid_entry gids[MLX4_MAX_PORT_GIDS];
पूर्ण;

काष्ठा mlx4_ib_iboe अणु
	spinlock_t		lock;
	काष्ठा net_device      *netdevs[MLX4_MAX_PORTS];
	atomic64_t		mac[MLX4_MAX_PORTS];
	काष्ठा notअगरier_block 	nb;
	काष्ठा mlx4_port_gid_table gids[MLX4_MAX_PORTS];
	क्रमागत ib_port_state	last_port_state[MLX4_MAX_PORTS];
पूर्ण;

काष्ठा pkey_mgt अणु
	u8			virt2phys_pkey[MLX4_MFUNC_MAX][MLX4_MAX_PORTS][MLX4_MAX_PORT_PKEYS];
	u16			phys_pkey_cache[MLX4_MAX_PORTS][MLX4_MAX_PORT_PKEYS];
	काष्ठा list_head	pkey_port_list[MLX4_MFUNC_MAX];
	काष्ठा kobject	       *device_parent[MLX4_MFUNC_MAX];
पूर्ण;

काष्ठा mlx4_ib_iov_sysfs_attr अणु
	व्योम *ctx;
	काष्ठा kobject *kobj;
	अचिन्हित दीर्घ data;
	u32 entry_num;
	अक्षर name[15];
	काष्ठा device_attribute dentry;
	काष्ठा device *dev;
पूर्ण;

काष्ठा mlx4_ib_iov_sysfs_attr_ar अणु
	काष्ठा mlx4_ib_iov_sysfs_attr dentries[3 * NUM_ALIAS_GUID_PER_PORT + 1];
पूर्ण;

काष्ठा mlx4_ib_iov_port अणु
	अक्षर name[100];
	u8 num;
	काष्ठा mlx4_ib_dev *dev;
	काष्ठा list_head list;
	काष्ठा mlx4_ib_iov_sysfs_attr_ar *dentr_ar;
	काष्ठा ib_port_attr attr;
	काष्ठा kobject	*cur_port;
	काष्ठा kobject	*admin_alias_parent;
	काष्ठा kobject	*gids_parent;
	काष्ठा kobject	*pkeys_parent;
	काष्ठा kobject	*mcgs_parent;
	काष्ठा mlx4_ib_iov_sysfs_attr mcg_dentry;
पूर्ण;

काष्ठा counter_index अणु
	काष्ठा  list_head       list;
	u32		index;
	u8		allocated;
पूर्ण;

काष्ठा mlx4_ib_counters अणु
	काष्ठा list_head        counters_list;
	काष्ठा mutex            mutex; /* mutex क्रम accessing counters list */
	u32			शेष_counter;
पूर्ण;

#घोषणा MLX4_DIAG_COUNTERS_TYPES 2

काष्ठा mlx4_ib_diag_counters अणु
	स्थिर अक्षर **name;
	u32 *offset;
	u32 num_counters;
पूर्ण;

काष्ठा mlx4_ib_dev अणु
	काष्ठा ib_device	ib_dev;
	काष्ठा mlx4_dev	       *dev;
	पूर्णांक			num_ports;
	व्योम __iomem	       *uar_map;

	काष्ठा mlx4_uar		priv_uar;
	u32			priv_pdn;
	MLX4_DECLARE_DOORBELL_LOCK(uar_lock);

	काष्ठा ib_mad_agent    *send_agent[MLX4_MAX_PORTS][2];
	काष्ठा ib_ah	       *sm_ah[MLX4_MAX_PORTS];
	spinlock_t		sm_lock;
	atomic64_t		sl2vl[MLX4_MAX_PORTS];
	काष्ठा mlx4_ib_sriov	sriov;

	काष्ठा mutex		cap_mask_mutex;
	bool			ib_active;
	काष्ठा mlx4_ib_iboe	iboe;
	काष्ठा mlx4_ib_counters counters_table[MLX4_MAX_PORTS];
	पूर्णांक		       *eq_table;
	काष्ठा kobject	       *iov_parent;
	काष्ठा kobject	       *ports_parent;
	काष्ठा kobject	       *dev_ports_parent[MLX4_MFUNC_MAX];
	काष्ठा mlx4_ib_iov_port	iov_ports[MLX4_MAX_PORTS];
	काष्ठा pkey_mgt		pkeys;
	अचिन्हित दीर्घ *ib_uc_qpns_biपंचांगap;
	पूर्णांक steer_qpn_count;
	पूर्णांक steer_qpn_base;
	पूर्णांक steering_support;
	काष्ठा mlx4_ib_qp      *qp1_proxy[MLX4_MAX_PORTS];
	/* lock when destroying qp1_proxy and getting netdev events */
	काष्ठा mutex		qp1_proxy_lock[MLX4_MAX_PORTS];
	u8			bond_next_port;
	/* protect resources needed as part of reset flow */
	spinlock_t		reset_flow_resource_lock;
	काष्ठा list_head		qp_list;
	काष्ठा mlx4_ib_diag_counters diag_counters[MLX4_DIAG_COUNTERS_TYPES];
पूर्ण;

काष्ठा ib_event_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा mlx4_ib_dev	*ib_dev;
	काष्ठा mlx4_eqe		ib_eqe;
	पूर्णांक			port;
पूर्ण;

काष्ठा mlx4_ib_qp_tunnel_init_attr अणु
	काष्ठा ib_qp_init_attr init_attr;
	पूर्णांक slave;
	क्रमागत ib_qp_type proxy_qp_type;
	u32 port;
पूर्ण;

काष्ठा mlx4_uverbs_ex_query_device अणु
	__u32 comp_mask;
	__u32 reserved;
पूर्ण;

अटल अंतरभूत काष्ठा mlx4_ib_dev *to_mdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा mlx4_ib_dev, ib_dev);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_ucontext *to_mucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा mlx4_ib_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_pd *to_mpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा mlx4_ib_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_xrcd *to_mxrcd(काष्ठा ib_xrcd *ibxrcd)
अणु
	वापस container_of(ibxrcd, काष्ठा mlx4_ib_xrcd, ibxrcd);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_cq *to_mcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा mlx4_ib_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_cq *to_mibcq(काष्ठा mlx4_cq *mcq)
अणु
	वापस container_of(mcq, काष्ठा mlx4_ib_cq, mcq);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_mr *to_mmr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा mlx4_ib_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_mw *to_mmw(काष्ठा ib_mw *ibmw)
अणु
	वापस container_of(ibmw, काष्ठा mlx4_ib_mw, ibmw);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_flow *to_mflow(काष्ठा ib_flow *ibflow)
अणु
	वापस container_of(ibflow, काष्ठा mlx4_ib_flow, ibflow);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_qp *to_mqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा mlx4_ib_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_qp *to_mibqp(काष्ठा mlx4_qp *mqp)
अणु
	वापस container_of(mqp, काष्ठा mlx4_ib_qp, mqp);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_srq *to_msrq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा mlx4_ib_srq, ibsrq);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_srq *to_mibsrq(काष्ठा mlx4_srq *msrq)
अणु
	वापस container_of(msrq, काष्ठा mlx4_ib_srq, msrq);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_ib_ah *to_mah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा mlx4_ib_ah, ibah);
पूर्ण

अटल अंतरभूत u8 mlx4_ib_bond_next_port(काष्ठा mlx4_ib_dev *dev)
अणु
	dev->bond_next_port = (dev->bond_next_port + 1) % dev->num_ports;

	वापस dev->bond_next_port + 1;
पूर्ण

पूर्णांक mlx4_ib_init_sriov(काष्ठा mlx4_ib_dev *dev);
व्योम mlx4_ib_बंद_sriov(काष्ठा mlx4_ib_dev *dev);

पूर्णांक mlx4_ib_db_map_user(काष्ठा ib_udata *udata, अचिन्हित दीर्घ virt,
			काष्ठा mlx4_db *db);
व्योम mlx4_ib_db_unmap_user(काष्ठा mlx4_ib_ucontext *context, काष्ठा mlx4_db *db);

काष्ठा ib_mr *mlx4_ib_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
पूर्णांक mlx4_ib_umem_ग_लिखो_mtt(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_mtt *mtt,
			   काष्ठा ib_umem *umem);
काष्ठा ib_mr *mlx4_ib_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, पूर्णांक access_flags,
				  काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_dereg_mr(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_alloc_mw(काष्ठा ib_mw *mw, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_dealloc_mw(काष्ठा ib_mw *mw);
काष्ठा ib_mr *mlx4_ib_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			       u32 max_num_sg);
पूर्णांक mlx4_ib_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset);
पूर्णांक mlx4_ib_modअगरy_cq(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period);
पूर्णांक mlx4_ib_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक entries, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक mlx4_ib_arm_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
व्योम __mlx4_ib_cq_clean(काष्ठा mlx4_ib_cq *cq, u32 qpn, काष्ठा mlx4_ib_srq *srq);
व्योम mlx4_ib_cq_clean(काष्ठा mlx4_ib_cq *cq, u32 qpn, काष्ठा mlx4_ib_srq *srq);

पूर्णांक mlx4_ib_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_create_ah_slave(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr,
			    पूर्णांक slave_sgid_index, u8 *s_mac, u16 vlan_tag);
पूर्णांक mlx4_ib_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr);
अटल अंतरभूत पूर्णांक mlx4_ib_destroy_ah(काष्ठा ib_ah *ah, u32 flags)
अणु
	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_create_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_init_attr *init_attr,
		       काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		       क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_query_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr);
पूर्णांक mlx4_ib_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);
व्योम mlx4_ib_मुक्त_srq_wqe(काष्ठा mlx4_ib_srq *srq, पूर्णांक wqe_index);
पूर्णांक mlx4_ib_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr);

काष्ठा ib_qp *mlx4_ib_create_qp(काष्ठा ib_pd *pd,
				काष्ठा ib_qp_init_attr *init_attr,
				काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
व्योम mlx4_ib_drain_sq(काष्ठा ib_qp *qp);
व्योम mlx4_ib_drain_rq(काष्ठा ib_qp *qp);
पूर्णांक mlx4_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
		     काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक mlx4_ib_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		      स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक mlx4_ib_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr);

पूर्णांक mlx4_MAD_IFC(काष्ठा mlx4_ib_dev *dev, पूर्णांक mad_अगरc_flags,
		 पूर्णांक port, स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		 स्थिर व्योम *in_mad, व्योम *response_mad);
पूर्णांक mlx4_ib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
			स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
			स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
			माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);
पूर्णांक mlx4_ib_mad_init(काष्ठा mlx4_ib_dev *dev);
व्योम mlx4_ib_mad_cleanup(काष्ठा mlx4_ib_dev *dev);

पूर्णांक __mlx4_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
			 काष्ठा ib_port_attr *props, पूर्णांक netw_view);
पूर्णांक __mlx4_ib_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			 u16 *pkey, पूर्णांक netw_view);

पूर्णांक __mlx4_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			जोड़ ib_gid *gid, पूर्णांक netw_view);

अटल अंतरभूत bool mlx4_ib_ah_grh_present(काष्ठा mlx4_ib_ah *ah)
अणु
	u32 port = be32_to_cpu(ah->av.ib.port_pd) >> 24 & 3;

	अगर (rdma_port_get_link_layer(ah->ibah.device, port) == IB_LINK_LAYER_ETHERNET)
		वापस true;

	वापस !!(ah->av.ib.g_slid & 0x80);
पूर्ण

पूर्णांक mlx4_ib_mcg_port_init(काष्ठा mlx4_ib_demux_ctx *ctx);
व्योम mlx4_ib_mcg_port_cleanup(काष्ठा mlx4_ib_demux_ctx *ctx, पूर्णांक destroy_wq);
व्योम clean_vf_mcast(काष्ठा mlx4_ib_demux_ctx *ctx, पूर्णांक slave);
पूर्णांक mlx4_ib_mcg_init(व्योम);
व्योम mlx4_ib_mcg_destroy(व्योम);

पूर्णांक mlx4_ib_find_real_gid(काष्ठा ib_device *ibdev, u32 port, __be64 guid);

पूर्णांक mlx4_ib_mcg_multiplex_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave,
				  काष्ठा ib_sa_mad *sa_mad);
पूर्णांक mlx4_ib_mcg_demux_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave,
			      काष्ठा ib_sa_mad *mad);

पूर्णांक mlx4_ib_add_mc(काष्ठा mlx4_ib_dev *mdev, काष्ठा mlx4_ib_qp *mqp,
		   जोड़ ib_gid *gid);

व्योम mlx4_ib_dispatch_event(काष्ठा mlx4_ib_dev *dev, u32 port_num,
			    क्रमागत ib_event_type type);

व्योम mlx4_ib_tunnels_update_work(काष्ठा work_काष्ठा *work);

पूर्णांक mlx4_ib_send_to_slave(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, u32 port,
			  क्रमागत ib_qp_type qpt, काष्ठा ib_wc *wc,
			  काष्ठा ib_grh *grh, काष्ठा ib_mad *mad);

पूर्णांक mlx4_ib_send_to_wire(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, u32 port,
			 क्रमागत ib_qp_type dest_qpt, u16 pkey_index, u32 remote_qpn,
			 u32 qkey, काष्ठा rdma_ah_attr *attr, u8 *s_mac,
			 u16 vlan_id, काष्ठा ib_mad *mad);

__be64 mlx4_ib_get_new_demux_tid(काष्ठा mlx4_ib_demux_ctx *ctx);

पूर्णांक mlx4_ib_demux_cm_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक *slave,
		काष्ठा ib_mad *mad);

पूर्णांक mlx4_ib_multiplex_cm_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave_id,
		काष्ठा ib_mad *mad);

व्योम mlx4_ib_cm_paravirt_init(काष्ठा mlx4_ib_dev *dev);
व्योम mlx4_ib_cm_paravirt_clean(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave_id);

/* alias guid support */
व्योम mlx4_ib_init_alias_guid_work(काष्ठा mlx4_ib_dev *dev, पूर्णांक port);
पूर्णांक mlx4_ib_init_alias_guid_service(काष्ठा mlx4_ib_dev *dev);
व्योम mlx4_ib_destroy_alias_guid_service(काष्ठा mlx4_ib_dev *dev);
व्योम mlx4_ib_invalidate_all_guid_record(काष्ठा mlx4_ib_dev *dev, पूर्णांक port);

व्योम mlx4_ib_notअगरy_slaves_on_guid_change(काष्ठा mlx4_ib_dev *dev,
					  पूर्णांक block_num,
					  u32 port_num, u8 *p_data);

व्योम mlx4_ib_update_cache_on_guid_change(काष्ठा mlx4_ib_dev *dev,
					 पूर्णांक block_num, u32 port_num,
					 u8 *p_data);

पूर्णांक add_sysfs_port_mcg_attr(काष्ठा mlx4_ib_dev *device, पूर्णांक port_num,
			    काष्ठा attribute *attr);
व्योम del_sysfs_port_mcg_attr(काष्ठा mlx4_ib_dev *device, पूर्णांक port_num,
			     काष्ठा attribute *attr);
ib_sa_comp_mask mlx4_ib_get_aguid_comp_mask_from_ix(पूर्णांक index);
व्योम mlx4_ib_slave_alias_guid_event(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave,
				    पूर्णांक port, पूर्णांक slave_init);

पूर्णांक mlx4_ib_device_रेजिस्टर_sysfs(काष्ठा mlx4_ib_dev *device) ;

व्योम mlx4_ib_device_unरेजिस्टर_sysfs(काष्ठा mlx4_ib_dev *device);

__be64 mlx4_ib_gen_node_guid(व्योम);

पूर्णांक mlx4_ib_steer_qp_alloc(काष्ठा mlx4_ib_dev *dev, पूर्णांक count, पूर्णांक *qpn);
व्योम mlx4_ib_steer_qp_मुक्त(काष्ठा mlx4_ib_dev *dev, u32 qpn, पूर्णांक count);
पूर्णांक mlx4_ib_steer_qp_reg(काष्ठा mlx4_ib_dev *mdev, काष्ठा mlx4_ib_qp *mqp,
			 पूर्णांक is_attach);
काष्ठा ib_mr *mlx4_ib_rereg_user_mr(काष्ठा ib_mr *mr, पूर्णांक flags, u64 start,
				    u64 length, u64 virt_addr,
				    पूर्णांक mr_access_flags, काष्ठा ib_pd *pd,
				    काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_gid_index_to_real_index(काष्ठा mlx4_ib_dev *ibdev,
				    स्थिर काष्ठा ib_gid_attr *attr);

व्योम mlx4_sched_ib_sl2vl_update_work(काष्ठा mlx4_ib_dev *ibdev,
				     पूर्णांक port);

व्योम mlx4_ib_sl2vl_update(काष्ठा mlx4_ib_dev *mdev, पूर्णांक port);

काष्ठा ib_wq *mlx4_ib_create_wq(काष्ठा ib_pd *pd,
				काष्ठा ib_wq_init_attr *init_attr,
				काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_destroy_wq(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata);
पूर्णांक mlx4_ib_modअगरy_wq(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *wq_attr,
		      u32 wq_attr_mask, काष्ठा ib_udata *udata);

पूर्णांक mlx4_ib_create_rwq_ind_table(काष्ठा ib_rwq_ind_table *ib_rwq_ind_tbl,
				 काष्ठा ib_rwq_ind_table_init_attr *init_attr,
				 काष्ठा ib_udata *udata);
अटल अंतरभूत पूर्णांक
mlx4_ib_destroy_rwq_ind_table(काष्ठा ib_rwq_ind_table *wq_ind_table)
अणु
	वापस 0;
पूर्ण
पूर्णांक mlx4_ib_umem_calc_optimal_mtt_size(काष्ठा ib_umem *umem, u64 start_va,
				       पूर्णांक *num_of_mtts);

#पूर्ण_अगर /* MLX4_IB_H */
