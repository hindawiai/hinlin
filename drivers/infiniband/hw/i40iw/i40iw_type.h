<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#अगर_अघोषित I40IW_TYPE_H
#घोषणा I40IW_TYPE_H
#समावेश "i40iw_user.h"
#समावेश "i40iw_hmc.h"
#समावेश "i40iw_vf.h"
#समावेश "i40iw_virtchnl.h"

काष्ठा i40iw_cqp_sq_wqe अणु
	u64 buf[I40IW_CQP_WQE_SIZE];
पूर्ण;

काष्ठा i40iw_sc_aeqe अणु
	u64 buf[I40IW_AEQE_SIZE];
पूर्ण;

काष्ठा i40iw_ceqe अणु
	u64 buf[I40IW_CEQE_SIZE];
पूर्ण;

काष्ठा i40iw_cqp_ctx अणु
	u64 buf[I40IW_CQP_CTX_SIZE];
पूर्ण;

काष्ठा i40iw_cq_shaकरोw_area अणु
	u64 buf[I40IW_SHADOW_AREA_SIZE];
पूर्ण;

काष्ठा i40iw_sc_dev;
काष्ठा i40iw_hmc_info;
काष्ठा i40iw_vsi_pestat;

काष्ठा i40iw_cqp_ops;
काष्ठा i40iw_ccq_ops;
काष्ठा i40iw_ceq_ops;
काष्ठा i40iw_aeq_ops;
काष्ठा i40iw_mr_ops;
काष्ठा i40iw_cqp_misc_ops;
काष्ठा i40iw_pd_ops;
काष्ठा i40iw_priv_qp_ops;
काष्ठा i40iw_priv_cq_ops;
काष्ठा i40iw_hmc_ops;
काष्ठा pci_dev;

क्रमागत i40iw_page_size अणु
	I40IW_PAGE_SIZE_4K,
	I40IW_PAGE_SIZE_2M
पूर्ण;

क्रमागत i40iw_resource_indicator_type अणु
	I40IW_RSRC_INDICATOR_TYPE_ADAPTER = 0,
	I40IW_RSRC_INDICATOR_TYPE_CQ,
	I40IW_RSRC_INDICATOR_TYPE_QP,
	I40IW_RSRC_INDICATOR_TYPE_SRQ
पूर्ण;

क्रमागत i40iw_hdrct_flags अणु
	DDP_LEN_FLAG = 0x80,
	DDP_HDR_FLAG = 0x40,
	RDMA_HDR_FLAG = 0x20
पूर्ण;

क्रमागत i40iw_term_layers अणु
	LAYER_RDMA = 0,
	LAYER_DDP = 1,
	LAYER_MPA = 2
पूर्ण;

क्रमागत i40iw_term_error_types अणु
	RDMAP_REMOTE_PROT = 1,
	RDMAP_REMOTE_OP = 2,
	DDP_CATASTROPHIC = 0,
	DDP_TAGGED_BUFFER = 1,
	DDP_UNTAGGED_BUFFER = 2,
	DDP_LLP = 3
पूर्ण;

क्रमागत i40iw_term_rdma_errors अणु
	RDMAP_INV_STAG = 0x00,
	RDMAP_INV_BOUNDS = 0x01,
	RDMAP_ACCESS = 0x02,
	RDMAP_UNASSOC_STAG = 0x03,
	RDMAP_TO_WRAP = 0x04,
	RDMAP_INV_RDMAP_VER = 0x05,
	RDMAP_UNEXPECTED_OP = 0x06,
	RDMAP_CATASTROPHIC_LOCAL = 0x07,
	RDMAP_CATASTROPHIC_GLOBAL = 0x08,
	RDMAP_CANT_INV_STAG = 0x09,
	RDMAP_UNSPECIFIED = 0xff
पूर्ण;

क्रमागत i40iw_term_ddp_errors अणु
	DDP_CATASTROPHIC_LOCAL = 0x00,
	DDP_TAGGED_INV_STAG = 0x00,
	DDP_TAGGED_BOUNDS = 0x01,
	DDP_TAGGED_UNASSOC_STAG = 0x02,
	DDP_TAGGED_TO_WRAP = 0x03,
	DDP_TAGGED_INV_DDP_VER = 0x04,
	DDP_UNTAGGED_INV_QN = 0x01,
	DDP_UNTAGGED_INV_MSN_NO_BUF = 0x02,
	DDP_UNTAGGED_INV_MSN_RANGE = 0x03,
	DDP_UNTAGGED_INV_MO = 0x04,
	DDP_UNTAGGED_INV_TOO_LONG = 0x05,
	DDP_UNTAGGED_INV_DDP_VER = 0x06
पूर्ण;

क्रमागत i40iw_term_mpa_errors अणु
	MPA_CLOSED = 0x01,
	MPA_CRC = 0x02,
	MPA_MARKER = 0x03,
	MPA_REQ_RSP = 0x04,
पूर्ण;

क्रमागत i40iw_flush_opcode अणु
	FLUSH_INVALID = 0,
	FLUSH_PROT_ERR,
	FLUSH_REM_ACCESS_ERR,
	FLUSH_LOC_QP_OP_ERR,
	FLUSH_REM_OP_ERR,
	FLUSH_LOC_LEN_ERR,
	FLUSH_GENERAL_ERR,
	FLUSH_FATAL_ERR
पूर्ण;

क्रमागत i40iw_term_eventtypes अणु
	TERM_EVENT_QP_FATAL,
	TERM_EVENT_QP_ACCESS_ERR
पूर्ण;

काष्ठा i40iw_terminate_hdr अणु
	u8 layer_etype;
	u8 error_code;
	u8 hdrct;
	u8 rsvd;
पूर्ण;

क्रमागत i40iw_debug_flag अणु
	I40IW_DEBUG_NONE	= 0x00000000,
	I40IW_DEBUG_ERR		= 0x00000001,
	I40IW_DEBUG_INIT	= 0x00000002,
	I40IW_DEBUG_DEV		= 0x00000004,
	I40IW_DEBUG_CM		= 0x00000008,
	I40IW_DEBUG_VERBS	= 0x00000010,
	I40IW_DEBUG_PUDA	= 0x00000020,
	I40IW_DEBUG_ILQ		= 0x00000040,
	I40IW_DEBUG_IEQ		= 0x00000080,
	I40IW_DEBUG_QP		= 0x00000100,
	I40IW_DEBUG_CQ		= 0x00000200,
	I40IW_DEBUG_MR		= 0x00000400,
	I40IW_DEBUG_PBLE	= 0x00000800,
	I40IW_DEBUG_WQE		= 0x00001000,
	I40IW_DEBUG_AEQ		= 0x00002000,
	I40IW_DEBUG_CQP		= 0x00004000,
	I40IW_DEBUG_HMC		= 0x00008000,
	I40IW_DEBUG_USER	= 0x00010000,
	I40IW_DEBUG_VIRT	= 0x00020000,
	I40IW_DEBUG_DCB		= 0x00040000,
	I40IW_DEBUG_CQE		= 0x00800000,
	I40IW_DEBUG_ALL		= 0xFFFFFFFF
पूर्ण;

क्रमागत i40iw_hw_stats_index_32b अणु
	I40IW_HW_STAT_INDEX_IP4RXDISCARD = 0,
	I40IW_HW_STAT_INDEX_IP4RXTRUNC,
	I40IW_HW_STAT_INDEX_IP4TXNOROUTE,
	I40IW_HW_STAT_INDEX_IP6RXDISCARD,
	I40IW_HW_STAT_INDEX_IP6RXTRUNC,
	I40IW_HW_STAT_INDEX_IP6TXNOROUTE,
	I40IW_HW_STAT_INDEX_TCPRTXSEG,
	I40IW_HW_STAT_INDEX_TCPRXOPTERR,
	I40IW_HW_STAT_INDEX_TCPRXPROTOERR,
	I40IW_HW_STAT_INDEX_MAX_32
पूर्ण;

क्रमागत i40iw_hw_stats_index_64b अणु
	I40IW_HW_STAT_INDEX_IP4RXOCTS = 0,
	I40IW_HW_STAT_INDEX_IP4RXPKTS,
	I40IW_HW_STAT_INDEX_IP4RXFRAGS,
	I40IW_HW_STAT_INDEX_IP4RXMCPKTS,
	I40IW_HW_STAT_INDEX_IP4TXOCTS,
	I40IW_HW_STAT_INDEX_IP4TXPKTS,
	I40IW_HW_STAT_INDEX_IP4TXFRAGS,
	I40IW_HW_STAT_INDEX_IP4TXMCPKTS,
	I40IW_HW_STAT_INDEX_IP6RXOCTS,
	I40IW_HW_STAT_INDEX_IP6RXPKTS,
	I40IW_HW_STAT_INDEX_IP6RXFRAGS,
	I40IW_HW_STAT_INDEX_IP6RXMCPKTS,
	I40IW_HW_STAT_INDEX_IP6TXOCTS,
	I40IW_HW_STAT_INDEX_IP6TXPKTS,
	I40IW_HW_STAT_INDEX_IP6TXFRAGS,
	I40IW_HW_STAT_INDEX_IP6TXMCPKTS,
	I40IW_HW_STAT_INDEX_TCPRXSEGS,
	I40IW_HW_STAT_INDEX_TCPTXSEG,
	I40IW_HW_STAT_INDEX_RDMARXRDS,
	I40IW_HW_STAT_INDEX_RDMARXSNDS,
	I40IW_HW_STAT_INDEX_RDMARXWRS,
	I40IW_HW_STAT_INDEX_RDMATXRDS,
	I40IW_HW_STAT_INDEX_RDMATXSNDS,
	I40IW_HW_STAT_INDEX_RDMATXWRS,
	I40IW_HW_STAT_INDEX_RDMAVBND,
	I40IW_HW_STAT_INDEX_RDMAVINV,
	I40IW_HW_STAT_INDEX_MAX_64
पूर्ण;

क्रमागत i40iw_feature_type अणु
	I40IW_FEATURE_FW_INFO = 0,
	I40IW_MAX_FEATURES
पूर्ण;

काष्ठा i40iw_dev_hw_stats_offsets अणु
	u32 stats_offset_32[I40IW_HW_STAT_INDEX_MAX_32];
	u32 stats_offset_64[I40IW_HW_STAT_INDEX_MAX_64];
पूर्ण;

काष्ठा i40iw_dev_hw_stats अणु
	u64 stats_value_32[I40IW_HW_STAT_INDEX_MAX_32];
	u64 stats_value_64[I40IW_HW_STAT_INDEX_MAX_64];
पूर्ण;

काष्ठा i40iw_vsi_pestat अणु
	काष्ठा i40iw_hw *hw;
	काष्ठा i40iw_dev_hw_stats hw_stats;
	काष्ठा i40iw_dev_hw_stats last_पढ़ो_hw_stats;
	काष्ठा i40iw_dev_hw_stats_offsets hw_stats_offsets;
	काष्ठा समयr_list stats_समयr;
	काष्ठा i40iw_sc_vsi *vsi;
	spinlock_t lock; /* rdma stats lock */
पूर्ण;

काष्ठा i40iw_hw अणु
	u8 __iomem *hw_addr;
	काष्ठा pci_dev *pcidev;
	काष्ठा i40iw_hmc_info hmc;
पूर्ण;

काष्ठा i40iw_pfpdu अणु
	काष्ठा list_head rxlist;
	u32 rcv_nxt;
	u32 fps;
	u32 max_fpdu_data;
	bool mode;
	bool mpa_crc_err;
	u64 total_ieq_bufs;
	u64 fpdu_processed;
	u64 bad_seq_num;
	u64 crc_err;
	u64 no_tx_bufs;
	u64 tx_err;
	u64 out_of_order;
	u64 pmode_count;
पूर्ण;

काष्ठा i40iw_sc_pd अणु
	u32 size;
	काष्ठा i40iw_sc_dev *dev;
	u16 pd_id;
	पूर्णांक abi_ver;
पूर्ण;

काष्ठा i40iw_cqp_quanta अणु
	u64 elem[I40IW_CQP_WQE_SIZE];
पूर्ण;

काष्ठा i40iw_sc_cqp अणु
	u32 size;
	u64 sq_pa;
	u64 host_ctx_pa;
	व्योम *back_cqp;
	काष्ठा i40iw_sc_dev *dev;
	क्रमागत i40iw_status_code (*process_cqp_sds)(काष्ठा i40iw_sc_dev *,
						  काष्ठा i40iw_update_sds_info *);
	काष्ठा i40iw_dma_mem sdbuf;
	काष्ठा i40iw_ring sq_ring;
	काष्ठा i40iw_cqp_quanta *sq_base;
	u64 *host_ctx;
	u64 *scratch_array;
	u32 cqp_id;
	u32 sq_size;
	u32 hw_sq_size;
	u8 काष्ठा_ver;
	u8 polarity;
	bool en_datacenter_tcp;
	u8 hmc_profile;
	u8 enabled_vf_count;
	u8 समयout_count;
पूर्ण;

काष्ठा i40iw_sc_aeq अणु
	u32 size;
	u64 aeq_elem_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_sc_aeqe *aeqe_base;
	व्योम *pbl_list;
	u32 elem_cnt;
	काष्ठा i40iw_ring aeq_ring;
	bool भव_map;
	u8 pbl_chunk_size;
	u32 first_pm_pbl_idx;
	u8 polarity;
पूर्ण;

काष्ठा i40iw_sc_ceq अणु
	u32 size;
	u64 ceq_elem_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_ceqe *ceqe_base;
	व्योम *pbl_list;
	u32 ceq_id;
	u32 elem_cnt;
	काष्ठा i40iw_ring ceq_ring;
	bool भव_map;
	u8 pbl_chunk_size;
	bool tph_en;
	u8 tph_val;
	u32 first_pm_pbl_idx;
	u8 polarity;
पूर्ण;

काष्ठा i40iw_sc_cq अणु
	काष्ठा i40iw_cq_uk cq_uk;
	u64 cq_pa;
	u64 shaकरोw_area_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_sc_vsi *vsi;
	व्योम *pbl_list;
	व्योम *back_cq;
	u32 ceq_id;
	u32 shaकरोw_पढ़ो_threshold;
	bool ceqe_mask;
	bool भव_map;
	u8 pbl_chunk_size;
	u8 cq_type;
	bool ceq_id_valid;
	bool tph_en;
	u8 tph_val;
	u32 first_pm_pbl_idx;
	bool check_overflow;
पूर्ण;

काष्ठा i40iw_sc_qp अणु
	काष्ठा i40iw_qp_uk qp_uk;
	u64 sq_pa;
	u64 rq_pa;
	u64 hw_host_ctx_pa;
	u64 shaकरोw_area_pa;
	u64 q2_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_sc_vsi *vsi;
	काष्ठा i40iw_sc_pd *pd;
	u64 *hw_host_ctx;
	व्योम *llp_stream_handle;
	व्योम *back_qp;
	काष्ठा i40iw_pfpdu pfpdu;
	u8 *q2_buf;
	u64 qp_compl_ctx;
	u16 qs_handle;
	u8 sq_tph_val;
	u8 rq_tph_val;
	u8 qp_state;
	u8 qp_type;
	u8 hw_sq_size;
	u8 hw_rq_size;
	u8 src_mac_addr_idx;
	bool sq_tph_en;
	bool rq_tph_en;
	bool rcv_tph_en;
	bool xmit_tph_en;
	bool भव_map;
	bool flush_sq;
	bool flush_rq;
	u8 user_pri;
	काष्ठा list_head list;
	bool on_qoslist;
	bool sq_flush;
	क्रमागत i40iw_flush_opcode flush_code;
	क्रमागत i40iw_term_eventtypes eventtype;
	u8 term_flags;
पूर्ण;

काष्ठा i40iw_hmc_fpm_misc अणु
	u32 max_ceqs;
	u32 max_sds;
	u32 xf_block_size;
	u32 q1_block_size;
	u32 ht_multiplier;
	u32 समयr_bucket;
पूर्ण;

काष्ठा i40iw_vchnl_अगर अणु
	क्रमागत i40iw_status_code (*vchnl_recv)(काष्ठा i40iw_sc_dev *, u32, u8 *, u16);
	क्रमागत i40iw_status_code (*vchnl_send)(काष्ठा i40iw_sc_dev *dev, u32, u8 *, u16);
पूर्ण;

#घोषणा I40IW_VCHNL_MAX_VF_MSG_SIZE 512

काष्ठा i40iw_vchnl_vf_msg_buffer अणु
	काष्ठा i40iw_virtchnl_op_buf vchnl_msg;
	अक्षर parm_buffer[I40IW_VCHNL_MAX_VF_MSG_SIZE - 1];
पूर्ण;

काष्ठा i40iw_qos अणु
	काष्ठा list_head qplist;
	spinlock_t lock;	/* qos list */
	u16 qs_handle;
पूर्ण;

काष्ठा i40iw_vfdev अणु
	काष्ठा i40iw_sc_dev *pf_dev;
	u8 *hmc_info_mem;
	काष्ठा i40iw_vsi_pestat pestat;
	काष्ठा i40iw_hmc_pble_info *pble_info;
	काष्ठा i40iw_hmc_info hmc_info;
	काष्ठा i40iw_vchnl_vf_msg_buffer vf_msg_buffer;
	u64 fpm_query_buf_pa;
	u64 *fpm_query_buf;
	u32 vf_id;
	u32 msg_count;
	bool pf_hmc_initialized;
	u16 pmf_index;
	u16 iw_vf_idx;		/* VF Device table index */
	bool stats_initialized;
पूर्ण;

#घोषणा I40IW_INVALID_FCN_ID 0xff
काष्ठा i40iw_sc_vsi अणु
	काष्ठा i40iw_sc_dev *dev;
	व्योम *back_vsi; /* Owned by OS */
	u32 ilq_count;
	काष्ठा i40iw_virt_mem ilq_mem;
	काष्ठा i40iw_puda_rsrc *ilq;
	u32 ieq_count;
	काष्ठा i40iw_virt_mem ieq_mem;
	काष्ठा i40iw_puda_rsrc *ieq;
	u16 exception_lan_queue;
	u16 mtu;
	u8 fcn_id;
	bool stats_fcn_id_alloc;
	काष्ठा i40iw_qos qos[I40IW_MAX_USER_PRIORITY];
	काष्ठा i40iw_vsi_pestat *pestat;
पूर्ण;

काष्ठा i40iw_sc_dev अणु
	काष्ठा list_head cqp_cmd_head;	/* head of the CQP command list */
	spinlock_t cqp_lock; /* cqp list sync */
	काष्ठा i40iw_dev_uk dev_uk;
	bool fcn_id_array[I40IW_MAX_STATS_COUNT];
	काष्ठा i40iw_dma_mem vf_fpm_query_buf[I40IW_MAX_PE_ENABLED_VF_COUNT];
	u64 fpm_query_buf_pa;
	u64 fpm_commit_buf_pa;
	u64 *fpm_query_buf;
	u64 *fpm_commit_buf;
	व्योम *back_dev;
	काष्ठा i40iw_hw *hw;
	u8 __iomem *db_addr;
	काष्ठा i40iw_hmc_info *hmc_info;
	काष्ठा i40iw_hmc_pble_info *pble_info;
	काष्ठा i40iw_vfdev *vf_dev[I40IW_MAX_PE_ENABLED_VF_COUNT];
	काष्ठा i40iw_sc_cqp *cqp;
	काष्ठा i40iw_sc_aeq *aeq;
	काष्ठा i40iw_sc_ceq *ceq[I40IW_CEQ_MAX_COUNT];
	काष्ठा i40iw_sc_cq *ccq;
	स्थिर काष्ठा i40iw_cqp_ops *cqp_ops;
	स्थिर काष्ठा i40iw_ccq_ops *ccq_ops;
	स्थिर काष्ठा i40iw_ceq_ops *ceq_ops;
	स्थिर काष्ठा i40iw_aeq_ops *aeq_ops;
	स्थिर काष्ठा i40iw_pd_ops *iw_pd_ops;
	स्थिर काष्ठा i40iw_priv_qp_ops *iw_priv_qp_ops;
	स्थिर काष्ठा i40iw_priv_cq_ops *iw_priv_cq_ops;
	स्थिर काष्ठा i40iw_mr_ops *mr_ops;
	स्थिर काष्ठा i40iw_cqp_misc_ops *cqp_misc_ops;
	स्थिर काष्ठा i40iw_hmc_ops *hmc_ops;
	काष्ठा i40iw_vchnl_अगर vchnl_अगर;
	स्थिर काष्ठा i40iw_vf_cqp_ops *iw_vf_cqp_ops;

	काष्ठा i40iw_hmc_fpm_misc hmc_fpm_misc;
	u64 feature_info[I40IW_MAX_FEATURES];
	u32 debug_mask;
	u8 hmc_fn_id;
	bool is_pf;
	bool vchnl_up;
	bool ceq_valid;
	u8 vf_id;
	रुको_queue_head_t vf_reqs;
	u64 cqp_cmd_stats[OP_SIZE_CQP_STAT_ARRAY];
	काष्ठा i40iw_vchnl_vf_msg_buffer vchnl_vf_msg_buf;
	u8 hw_rev;
पूर्ण;

काष्ठा i40iw_modअगरy_cq_info अणु
	u64 cq_pa;
	काष्ठा i40iw_cqe *cq_base;
	व्योम *pbl_list;
	u32 ceq_id;
	u32 cq_size;
	u32 shaकरोw_पढ़ो_threshold;
	bool भव_map;
	u8 pbl_chunk_size;
	bool check_overflow;
	bool cq_resize;
	bool ceq_change;
	bool check_overflow_change;
	u32 first_pm_pbl_idx;
	bool ceq_valid;
पूर्ण;

काष्ठा i40iw_create_qp_info अणु
	u8 next_iwarp_state;
	bool ord_valid;
	bool tcp_ctx_valid;
	bool cq_num_valid;
	bool arp_cache_idx_valid;
पूर्ण;

काष्ठा i40iw_modअगरy_qp_info अणु
	u64 rx_win0;
	u64 rx_win1;
	u8 next_iwarp_state;
	u8 termlen;
	bool ord_valid;
	bool tcp_ctx_valid;
	bool cq_num_valid;
	bool arp_cache_idx_valid;
	bool reset_tcp_conn;
	bool हटाओ_hash_idx;
	bool करोnt_send_term;
	bool करोnt_send_fin;
	bool cached_var_valid;
	bool क्रमce_loopback;
पूर्ण;

काष्ठा i40iw_ccq_cqe_info अणु
	काष्ठा i40iw_sc_cqp *cqp;
	u64 scratch;
	u32 op_ret_val;
	u16 maj_err_code;
	u16 min_err_code;
	u8 op_code;
	bool error;
पूर्ण;

काष्ठा i40iw_l2params अणु
	u16 qs_handle_list[I40IW_MAX_USER_PRIORITY];
	u16 mtu;
पूर्ण;

काष्ठा i40iw_vsi_init_info अणु
	काष्ठा i40iw_sc_dev *dev;
	व्योम  *back_vsi;
	काष्ठा i40iw_l2params *params;
	u16 exception_lan_queue;
पूर्ण;

काष्ठा i40iw_vsi_stats_info अणु
	काष्ठा i40iw_vsi_pestat *pestat;
	u8 fcn_id;
	bool alloc_fcn_id;
	bool stats_initialize;
पूर्ण;

काष्ठा i40iw_device_init_info अणु
	u64 fpm_query_buf_pa;
	u64 fpm_commit_buf_pa;
	u64 *fpm_query_buf;
	u64 *fpm_commit_buf;
	काष्ठा i40iw_hw *hw;
	व्योम __iomem *bar0;
	क्रमागत i40iw_status_code (*vchnl_send)(काष्ठा i40iw_sc_dev *, u32, u8 *, u16);
	u8 hmc_fn_id;
	bool is_pf;
	u32 debug_mask;
पूर्ण;

क्रमागत i40iw_cqp_hmc_profile अणु
	I40IW_HMC_PROखाता_DEFAULT = 1,
	I40IW_HMC_PROखाता_FAVOR_VF = 2,
	I40IW_HMC_PROखाता_EQUAL = 3,
पूर्ण;

काष्ठा i40iw_cqp_init_info अणु
	u64 cqp_compl_ctx;
	u64 host_ctx_pa;
	u64 sq_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_cqp_quanta *sq;
	u64 *host_ctx;
	u64 *scratch_array;
	u32 sq_size;
	u8 काष्ठा_ver;
	bool en_datacenter_tcp;
	u8 hmc_profile;
	u8 enabled_vf_count;
पूर्ण;

काष्ठा i40iw_ceq_init_info अणु
	u64 ceqe_pa;
	काष्ठा i40iw_sc_dev *dev;
	u64 *ceqe_base;
	व्योम *pbl_list;
	u32 elem_cnt;
	u32 ceq_id;
	bool भव_map;
	u8 pbl_chunk_size;
	bool tph_en;
	u8 tph_val;
	u32 first_pm_pbl_idx;
पूर्ण;

काष्ठा i40iw_aeq_init_info अणु
	u64 aeq_elem_pa;
	काष्ठा i40iw_sc_dev *dev;
	u32 *aeqe_base;
	व्योम *pbl_list;
	u32 elem_cnt;
	bool भव_map;
	u8 pbl_chunk_size;
	u32 first_pm_pbl_idx;
पूर्ण;

काष्ठा i40iw_ccq_init_info अणु
	u64 cq_pa;
	u64 shaकरोw_area_pa;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_cqe *cq_base;
	u64 *shaकरोw_area;
	व्योम *pbl_list;
	u32 num_elem;
	u32 ceq_id;
	u32 shaकरोw_पढ़ो_threshold;
	bool ceqe_mask;
	bool ceq_id_valid;
	bool tph_en;
	u8 tph_val;
	bool aव्योम_mem_cflct;
	bool भव_map;
	u8 pbl_chunk_size;
	u32 first_pm_pbl_idx;
पूर्ण;

काष्ठा i40iwarp_offload_info अणु
	u16 rcv_mark_offset;
	u16 snd_mark_offset;
	u16 pd_id;
	u8 ddp_ver;
	u8 rdmap_ver;
	u8 ord_size;
	u8 ird_size;
	bool wr_rdresp_en;
	bool rd_enable;
	bool snd_mark_en;
	bool rcv_mark_en;
	bool bind_en;
	bool fast_reg_en;
	bool priv_mode_en;
	bool lsmm_present;
	u8 iwarp_mode;
	bool align_hdrs;
	bool rcv_no_mpa_crc;

	u8 last_byte_sent;
पूर्ण;

काष्ठा i40iw_tcp_offload_info अणु
	bool ipv4;
	bool no_nagle;
	bool insert_vlan_tag;
	bool समय_stamp;
	u8 cwnd_inc_limit;
	bool drop_ooo_seg;
	u8 dup_ack_thresh;
	u8 ttl;
	u8 src_mac_addr_idx;
	bool aव्योम_stretch_ack;
	u8 tos;
	u16 src_port;
	u16 dst_port;
	u32 dest_ip_addr0;
	u32 dest_ip_addr1;
	u32 dest_ip_addr2;
	u32 dest_ip_addr3;
	u32 snd_mss;
	u16 vlan_tag;
	u16 arp_idx;
	u32 flow_label;
	bool wscale;
	u8 tcp_state;
	u8 snd_wscale;
	u8 rcv_wscale;
	u32 समय_stamp_recent;
	u32 समय_stamp_age;
	u32 snd_nxt;
	u32 snd_wnd;
	u32 rcv_nxt;
	u32 rcv_wnd;
	u32 snd_max;
	u32 snd_una;
	u32 srtt;
	u32 rtt_var;
	u32 ss_thresh;
	u32 cwnd;
	u32 snd_wl1;
	u32 snd_wl2;
	u32 max_snd_winकरोw;
	u8 rexmit_thresh;
	u32 local_ipaddr0;
	u32 local_ipaddr1;
	u32 local_ipaddr2;
	u32 local_ipaddr3;
	bool ignore_tcp_opt;
	bool ignore_tcp_uns_opt;
पूर्ण;

काष्ठा i40iw_qp_host_ctx_info अणु
	u64 qp_compl_ctx;
	काष्ठा i40iw_tcp_offload_info *tcp_info;
	काष्ठा i40iwarp_offload_info *iwarp_info;
	u32 send_cq_num;
	u32 rcv_cq_num;
	bool tcp_info_valid;
	bool iwarp_info_valid;
	bool err_rq_idx_valid;
	u16 err_rq_idx;
	bool add_to_qoslist;
	u8 user_pri;
पूर्ण;

काष्ठा i40iw_aeqe_info अणु
	u64 compl_ctx;
	u32 qp_cq_id;
	u16 ae_id;
	u16 wqe_idx;
	u8 tcp_state;
	u8 iwarp_state;
	bool qp;
	bool cq;
	bool sq;
	bool in_rdrsp_wr;
	bool out_rdrsp;
	u8 q2_data_written;
	bool aeqe_overflow;
पूर्ण;

काष्ठा i40iw_allocate_stag_info अणु
	u64 total_len;
	u32 chunk_size;
	u32 stag_idx;
	u32 page_size;
	u16 pd_id;
	u16 access_rights;
	bool remote_access;
	bool use_hmc_fcn_index;
	u8 hmc_fcn_index;
	bool use_pf_rid;
पूर्ण;

काष्ठा i40iw_reg_ns_stag_info अणु
	u64 reg_addr_pa;
	u64 fbo;
	व्योम *va;
	u64 total_len;
	u32 page_size;
	u32 chunk_size;
	u32 first_pm_pbl_index;
	क्रमागत i40iw_addressing_type addr_type;
	i40iw_stag_index stag_idx;
	u16 access_rights;
	u16 pd_id;
	i40iw_stag_key stag_key;
	bool use_hmc_fcn_index;
	u8 hmc_fcn_index;
	bool use_pf_rid;
पूर्ण;

काष्ठा i40iw_fast_reg_stag_info अणु
	u64 wr_id;
	u64 reg_addr_pa;
	u64 fbo;
	व्योम *va;
	u64 total_len;
	u32 page_size;
	u32 chunk_size;
	u32 first_pm_pbl_index;
	क्रमागत i40iw_addressing_type addr_type;
	i40iw_stag_index stag_idx;
	u16 access_rights;
	u16 pd_id;
	i40iw_stag_key stag_key;
	bool local_fence;
	bool पढ़ो_fence;
	bool संकेतed;
	bool use_hmc_fcn_index;
	u8 hmc_fcn_index;
	bool use_pf_rid;
	bool defer_flag;
पूर्ण;

काष्ठा i40iw_dealloc_stag_info अणु
	u32 stag_idx;
	u16 pd_id;
	bool mr;
	bool dealloc_pbl;
पूर्ण;

काष्ठा i40iw_रेजिस्टर_shared_stag अणु
	व्योम *va;
	क्रमागत i40iw_addressing_type addr_type;
	i40iw_stag_index new_stag_idx;
	i40iw_stag_index parent_stag_idx;
	u32 access_rights;
	u16 pd_id;
	i40iw_stag_key new_stag_key;
पूर्ण;

काष्ठा i40iw_qp_init_info अणु
	काष्ठा i40iw_qp_uk_init_info qp_uk_init_info;
	काष्ठा i40iw_sc_pd *pd;
	काष्ठा i40iw_sc_vsi *vsi;
	u64 *host_ctx;
	u8 *q2;
	u64 sq_pa;
	u64 rq_pa;
	u64 host_ctx_pa;
	u64 q2_pa;
	u64 shaकरोw_area_pa;
	पूर्णांक abi_ver;
	u8 sq_tph_val;
	u8 rq_tph_val;
	u8 type;
	bool sq_tph_en;
	bool rq_tph_en;
	bool rcv_tph_en;
	bool xmit_tph_en;
	bool भव_map;
पूर्ण;

काष्ठा i40iw_cq_init_info अणु
	काष्ठा i40iw_sc_dev *dev;
	u64 cq_base_pa;
	u64 shaकरोw_area_pa;
	u32 ceq_id;
	u32 shaकरोw_पढ़ो_threshold;
	bool भव_map;
	bool ceqe_mask;
	u8 pbl_chunk_size;
	u32 first_pm_pbl_idx;
	bool ceq_id_valid;
	bool tph_en;
	u8 tph_val;
	u8 type;
	काष्ठा i40iw_cq_uk_init_info cq_uk_init_info;
पूर्ण;

काष्ठा i40iw_upload_context_info अणु
	u64 buf_pa;
	bool मुक्तze_qp;
	bool raw_क्रमmat;
	u32 qp_id;
	u8 qp_type;
पूर्ण;

काष्ठा i40iw_add_arp_cache_entry_info अणु
	u8 mac_addr[6];
	u32 reach_max;
	u16 arp_index;
	bool permanent;
पूर्ण;

काष्ठा i40iw_apbvt_info अणु
	u16 port;
	bool add;
पूर्ण;

क्रमागत i40iw_quad_entry_type अणु
	I40IW_QHASH_TYPE_TCP_ESTABLISHED = 1,
	I40IW_QHASH_TYPE_TCP_SYN,
पूर्ण;

क्रमागत i40iw_quad_hash_manage_type अणु
	I40IW_QHASH_MANAGE_TYPE_DELETE = 0,
	I40IW_QHASH_MANAGE_TYPE_ADD,
	I40IW_QHASH_MANAGE_TYPE_MODIFY
पूर्ण;

काष्ठा i40iw_qhash_table_info अणु
	काष्ठा i40iw_sc_vsi *vsi;
	क्रमागत i40iw_quad_hash_manage_type manage;
	क्रमागत i40iw_quad_entry_type entry_type;
	bool vlan_valid;
	bool ipv4_valid;
	u8 mac_addr[6];
	u16 vlan_id;
	u8 user_pri;
	u32 qp_num;
	u32 dest_ip[4];
	u32 src_ip[4];
	u16 dest_port;
	u16 src_port;
पूर्ण;

काष्ठा i40iw_local_mac_ipaddr_entry_info अणु
	u8 mac_addr[6];
	u8 entry_idx;
पूर्ण;

काष्ठा i40iw_qp_flush_info अणु
	u16 sq_minor_code;
	u16 sq_major_code;
	u16 rq_minor_code;
	u16 rq_major_code;
	u16 ae_code;
	u8 ae_source;
	bool sq;
	bool rq;
	bool userflushcode;
	bool generate_ae;
पूर्ण;

काष्ठा i40iw_cqp_commit_fpm_values अणु
	u64 qp_base;
	u64 cq_base;
	u32 hte_base;
	u32 arp_base;
	u32 apbvt_inuse_base;
	u32 mr_base;
	u32 xf_base;
	u32 xffl_base;
	u32 q1_base;
	u32 q1fl_base;
	u32 fsimc_base;
	u32 fsiav_base;
	u32 pbl_base;

	u32 qp_cnt;
	u32 cq_cnt;
	u32 hte_cnt;
	u32 arp_cnt;
	u32 mr_cnt;
	u32 xf_cnt;
	u32 xffl_cnt;
	u32 q1_cnt;
	u32 q1fl_cnt;
	u32 fsimc_cnt;
	u32 fsiav_cnt;
	u32 pbl_cnt;
पूर्ण;

काष्ठा i40iw_cqp_query_fpm_values अणु
	u16 first_pe_sd_index;
	u32 qp_objsize;
	u32 cq_objsize;
	u32 hte_objsize;
	u32 arp_objsize;
	u32 mr_objsize;
	u32 xf_objsize;
	u32 q1_objsize;
	u32 fsimc_objsize;
	u32 fsiav_objsize;

	u32 qp_max;
	u32 cq_max;
	u32 hte_max;
	u32 arp_max;
	u32 mr_max;
	u32 xf_max;
	u32 xffl_max;
	u32 q1_max;
	u32 q1fl_max;
	u32 fsimc_max;
	u32 fsiav_max;
	u32 pbl_max;
पूर्ण;

काष्ठा i40iw_gen_ae_info अणु
	u16 ae_code;
	u8 ae_source;
पूर्ण;

काष्ठा i40iw_cqp_ops अणु
	क्रमागत i40iw_status_code (*cqp_init)(काष्ठा i40iw_sc_cqp *,
					   काष्ठा i40iw_cqp_init_info *);
	क्रमागत i40iw_status_code (*cqp_create)(काष्ठा i40iw_sc_cqp *, u16 *, u16 *);
	व्योम (*cqp_post_sq)(काष्ठा i40iw_sc_cqp *);
	u64 *(*cqp_get_next_send_wqe)(काष्ठा i40iw_sc_cqp *, u64 scratch);
	क्रमागत i40iw_status_code (*cqp_destroy)(काष्ठा i40iw_sc_cqp *);
	क्रमागत i40iw_status_code (*poll_क्रम_cqp_op_करोne)(काष्ठा i40iw_sc_cqp *, u8,
						       काष्ठा i40iw_ccq_cqe_info *);
पूर्ण;

काष्ठा i40iw_ccq_ops अणु
	क्रमागत i40iw_status_code (*ccq_init)(काष्ठा i40iw_sc_cq *,
					   काष्ठा i40iw_ccq_init_info *);
	क्रमागत i40iw_status_code (*ccq_create)(काष्ठा i40iw_sc_cq *, u64, bool, bool);
	क्रमागत i40iw_status_code (*ccq_destroy)(काष्ठा i40iw_sc_cq *, u64, bool);
	क्रमागत i40iw_status_code (*ccq_create_करोne)(काष्ठा i40iw_sc_cq *);
	क्रमागत i40iw_status_code (*ccq_get_cqe_info)(काष्ठा i40iw_sc_cq *,
						   काष्ठा i40iw_ccq_cqe_info *);
	व्योम (*ccq_arm)(काष्ठा i40iw_sc_cq *);
पूर्ण;

काष्ठा i40iw_ceq_ops अणु
	क्रमागत i40iw_status_code (*ceq_init)(काष्ठा i40iw_sc_ceq *,
					   काष्ठा i40iw_ceq_init_info *);
	क्रमागत i40iw_status_code (*ceq_create)(काष्ठा i40iw_sc_ceq *, u64, bool);
	क्रमागत i40iw_status_code (*cceq_create_करोne)(काष्ठा i40iw_sc_ceq *);
	क्रमागत i40iw_status_code (*cceq_destroy_करोne)(काष्ठा i40iw_sc_ceq *);
	क्रमागत i40iw_status_code (*cceq_create)(काष्ठा i40iw_sc_ceq *, u64);
	क्रमागत i40iw_status_code (*ceq_destroy)(काष्ठा i40iw_sc_ceq *, u64, bool);
	व्योम *(*process_ceq)(काष्ठा i40iw_sc_dev *, काष्ठा i40iw_sc_ceq *);
पूर्ण;

काष्ठा i40iw_aeq_ops अणु
	क्रमागत i40iw_status_code (*aeq_init)(काष्ठा i40iw_sc_aeq *,
					   काष्ठा i40iw_aeq_init_info *);
	क्रमागत i40iw_status_code (*aeq_create)(काष्ठा i40iw_sc_aeq *, u64, bool);
	क्रमागत i40iw_status_code (*aeq_destroy)(काष्ठा i40iw_sc_aeq *, u64, bool);
	क्रमागत i40iw_status_code (*get_next_aeqe)(काष्ठा i40iw_sc_aeq *,
						काष्ठा i40iw_aeqe_info *);
	क्रमागत i40iw_status_code (*repost_aeq_entries)(काष्ठा i40iw_sc_dev *, u32);
	क्रमागत i40iw_status_code (*aeq_create_करोne)(काष्ठा i40iw_sc_aeq *);
	क्रमागत i40iw_status_code (*aeq_destroy_करोne)(काष्ठा i40iw_sc_aeq *);
पूर्ण;

काष्ठा i40iw_pd_ops अणु
	व्योम (*pd_init)(काष्ठा i40iw_sc_dev *, काष्ठा i40iw_sc_pd *, u16, पूर्णांक);
पूर्ण;

काष्ठा i40iw_priv_qp_ops अणु
	क्रमागत i40iw_status_code (*qp_init)(काष्ठा i40iw_sc_qp *, काष्ठा i40iw_qp_init_info *);
	क्रमागत i40iw_status_code (*qp_create)(काष्ठा i40iw_sc_qp *,
					    काष्ठा i40iw_create_qp_info *, u64, bool);
	क्रमागत i40iw_status_code (*qp_modअगरy)(काष्ठा i40iw_sc_qp *,
					    काष्ठा i40iw_modअगरy_qp_info *, u64, bool);
	क्रमागत i40iw_status_code (*qp_destroy)(काष्ठा i40iw_sc_qp *, u64, bool, bool, bool);
	क्रमागत i40iw_status_code (*qp_flush_wqes)(काष्ठा i40iw_sc_qp *,
						काष्ठा i40iw_qp_flush_info *, u64, bool);
	क्रमागत i40iw_status_code (*qp_upload_context)(काष्ठा i40iw_sc_dev *,
						    काष्ठा i40iw_upload_context_info *,
						    u64, bool);
	क्रमागत i40iw_status_code (*qp_setctx)(काष्ठा i40iw_sc_qp *, u64 *,
					    काष्ठा i40iw_qp_host_ctx_info *);

	व्योम (*qp_send_lsmm)(काष्ठा i40iw_sc_qp *, व्योम *, u32, i40iw_stag);
	व्योम (*qp_send_lsmm_nostag)(काष्ठा i40iw_sc_qp *, व्योम *, u32);
	व्योम (*qp_send_rtt)(काष्ठा i40iw_sc_qp *, bool);
	क्रमागत i40iw_status_code (*qp_post_wqe0)(काष्ठा i40iw_sc_qp *, u8);
	क्रमागत i40iw_status_code (*iw_mr_fast_रेजिस्टर)(काष्ठा i40iw_sc_qp *,
						      काष्ठा i40iw_fast_reg_stag_info *,
						      bool);
पूर्ण;

काष्ठा i40iw_priv_cq_ops अणु
	क्रमागत i40iw_status_code (*cq_init)(काष्ठा i40iw_sc_cq *, काष्ठा i40iw_cq_init_info *);
	क्रमागत i40iw_status_code (*cq_create)(काष्ठा i40iw_sc_cq *, u64, bool, bool);
	क्रमागत i40iw_status_code (*cq_destroy)(काष्ठा i40iw_sc_cq *, u64, bool);
	क्रमागत i40iw_status_code (*cq_modअगरy)(काष्ठा i40iw_sc_cq *,
					    काष्ठा i40iw_modअगरy_cq_info *, u64, bool);
पूर्ण;

काष्ठा i40iw_mr_ops अणु
	क्रमागत i40iw_status_code (*alloc_stag)(काष्ठा i40iw_sc_dev *,
					     काष्ठा i40iw_allocate_stag_info *, u64, bool);
	क्रमागत i40iw_status_code (*mr_reg_non_shared)(काष्ठा i40iw_sc_dev *,
						    काष्ठा i40iw_reg_ns_stag_info *,
						    u64, bool);
	क्रमागत i40iw_status_code (*mr_reg_shared)(काष्ठा i40iw_sc_dev *,
						काष्ठा i40iw_रेजिस्टर_shared_stag *,
						u64, bool);
	क्रमागत i40iw_status_code (*dealloc_stag)(काष्ठा i40iw_sc_dev *,
					       काष्ठा i40iw_dealloc_stag_info *,
					       u64, bool);
	क्रमागत i40iw_status_code (*query_stag)(काष्ठा i40iw_sc_dev *, u64, u32, bool);
	क्रमागत i40iw_status_code (*mw_alloc)(काष्ठा i40iw_sc_dev *, u64, u32, u16, bool);
पूर्ण;

काष्ठा i40iw_cqp_misc_ops अणु
	क्रमागत i40iw_status_code (*manage_hmc_pm_func_table)(काष्ठा i40iw_sc_cqp *,
							   u64, u8, bool, bool);
	क्रमागत i40iw_status_code (*set_hmc_resource_profile)(काष्ठा i40iw_sc_cqp *,
							   u64, u8, u8, bool, bool);
	क्रमागत i40iw_status_code (*commit_fpm_values)(काष्ठा i40iw_sc_cqp *, u64, u8,
						    काष्ठा i40iw_dma_mem *, bool, u8);
	क्रमागत i40iw_status_code (*query_fpm_values)(काष्ठा i40iw_sc_cqp *, u64, u8,
						   काष्ठा i40iw_dma_mem *, bool, u8);
	क्रमागत i40iw_status_code (*अटल_hmc_pages_allocated)(काष्ठा i40iw_sc_cqp *,
							     u64, u8, bool, bool);
	क्रमागत i40iw_status_code (*add_arp_cache_entry)(काष्ठा i40iw_sc_cqp *,
						      काष्ठा i40iw_add_arp_cache_entry_info *,
						      u64, bool);
	क्रमागत i40iw_status_code (*del_arp_cache_entry)(काष्ठा i40iw_sc_cqp *, u64, u16, bool);
	क्रमागत i40iw_status_code (*query_arp_cache_entry)(काष्ठा i40iw_sc_cqp *, u64, u16, bool);
	क्रमागत i40iw_status_code (*manage_apbvt_entry)(काष्ठा i40iw_sc_cqp *,
						     काष्ठा i40iw_apbvt_info *, u64, bool);
	क्रमागत i40iw_status_code (*manage_qhash_table_entry)(काष्ठा i40iw_sc_cqp *,
							   काष्ठा i40iw_qhash_table_info *, u64, bool);
	क्रमागत i40iw_status_code (*alloc_local_mac_ipaddr_table_entry)(काष्ठा i40iw_sc_cqp *, u64, bool);
	क्रमागत i40iw_status_code (*add_local_mac_ipaddr_entry)(काष्ठा i40iw_sc_cqp *,
							     काष्ठा i40iw_local_mac_ipaddr_entry_info *,
							     u64, bool);
	क्रमागत i40iw_status_code (*del_local_mac_ipaddr_entry)(काष्ठा i40iw_sc_cqp *, u64, u8, u8, bool);
	क्रमागत i40iw_status_code (*cqp_nop)(काष्ठा i40iw_sc_cqp *, u64, bool);
	क्रमागत i40iw_status_code (*commit_fpm_values_करोne)(काष्ठा i40iw_sc_cqp
							  *);
	क्रमागत i40iw_status_code (*query_fpm_values_करोne)(काष्ठा i40iw_sc_cqp *);
	क्रमागत i40iw_status_code (*manage_hmc_pm_func_table_करोne)(काष्ठा i40iw_sc_cqp *);
	क्रमागत i40iw_status_code (*update_suspend_qp)(काष्ठा i40iw_sc_cqp *, काष्ठा i40iw_sc_qp *, u64);
	क्रमागत i40iw_status_code (*update_resume_qp)(काष्ठा i40iw_sc_cqp *, काष्ठा i40iw_sc_qp *, u64);
पूर्ण;

काष्ठा i40iw_hmc_ops अणु
	क्रमागत i40iw_status_code (*init_iw_hmc)(काष्ठा i40iw_sc_dev *, u8);
	क्रमागत i40iw_status_code (*parse_fpm_query_buf)(u64 *, काष्ठा i40iw_hmc_info *,
						      काष्ठा i40iw_hmc_fpm_misc *);
	क्रमागत i40iw_status_code (*configure_iw_fpm)(काष्ठा i40iw_sc_dev *, u8);
	क्रमागत i40iw_status_code (*parse_fpm_commit_buf)(u64 *, काष्ठा i40iw_hmc_obj_info *, u32 *sd);
	क्रमागत i40iw_status_code (*create_hmc_object)(काष्ठा i40iw_sc_dev *dev,
						    काष्ठा i40iw_hmc_create_obj_info *);
	क्रमागत i40iw_status_code (*del_hmc_object)(काष्ठा i40iw_sc_dev *dev,
						 काष्ठा i40iw_hmc_del_obj_info *,
						 bool reset);
	क्रमागत i40iw_status_code (*pf_init_vfhmc)(काष्ठा i40iw_sc_dev *, u8, u32 *);
	क्रमागत i40iw_status_code (*vf_configure_vffpm)(काष्ठा i40iw_sc_dev *, u32 *);
पूर्ण;

काष्ठा cqp_info अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा i40iw_sc_qp *qp;
			काष्ठा i40iw_create_qp_info info;
			u64 scratch;
		पूर्ण qp_create;

		काष्ठा अणु
			काष्ठा i40iw_sc_qp *qp;
			काष्ठा i40iw_modअगरy_qp_info info;
			u64 scratch;
		पूर्ण qp_modअगरy;

		काष्ठा अणु
			काष्ठा i40iw_sc_qp *qp;
			u64 scratch;
			bool हटाओ_hash_idx;
			bool ignore_mw_bnd;
		पूर्ण qp_destroy;

		काष्ठा अणु
			काष्ठा i40iw_sc_cq *cq;
			u64 scratch;
			bool check_overflow;
		पूर्ण cq_create;

		काष्ठा अणु
			काष्ठा i40iw_sc_cq *cq;
			u64 scratch;
		पूर्ण cq_destroy;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_allocate_stag_info info;
			u64 scratch;
		पूर्ण alloc_stag;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			u64 scratch;
			u32 mw_stag_index;
			u16 pd_id;
		पूर्ण mw_alloc;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_reg_ns_stag_info info;
			u64 scratch;
		पूर्ण mr_reg_non_shared;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_dealloc_stag_info info;
			u64 scratch;
		पूर्ण dealloc_stag;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_local_mac_ipaddr_entry_info info;
			u64 scratch;
		पूर्ण add_local_mac_ipaddr_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_add_arp_cache_entry_info info;
			u64 scratch;
		पूर्ण add_arp_cache_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			u64 scratch;
			u8 entry_idx;
			u8 ignore_ref_count;
		पूर्ण del_local_mac_ipaddr_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			u64 scratch;
			u16 arp_index;
		पूर्ण del_arp_cache_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_manage_vf_pble_info info;
			u64 scratch;
		पूर्ण manage_vf_pble_bp;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_upload_context_info info;
			u64 scratch;
		पूर्ण qp_upload_context;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			u64 scratch;
		पूर्ण alloc_local_mac_ipaddr_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_hmc_fcn_info info;
			u64 scratch;
		पूर्ण manage_hmc_pm;

		काष्ठा अणु
			काष्ठा i40iw_sc_ceq *ceq;
			u64 scratch;
		पूर्ण ceq_create;

		काष्ठा अणु
			काष्ठा i40iw_sc_ceq *ceq;
			u64 scratch;
		पूर्ण ceq_destroy;

		काष्ठा अणु
			काष्ठा i40iw_sc_aeq *aeq;
			u64 scratch;
		पूर्ण aeq_create;

		काष्ठा अणु
			काष्ठा i40iw_sc_aeq *aeq;
			u64 scratch;
		पूर्ण aeq_destroy;

		काष्ठा अणु
			काष्ठा i40iw_sc_qp *qp;
			काष्ठा i40iw_qp_flush_info info;
			u64 scratch;
		पूर्ण qp_flush_wqes;

		काष्ठा अणु
			काष्ठा i40iw_sc_qp *qp;
			काष्ठा i40iw_gen_ae_info info;
			u64 scratch;
		पूर्ण gen_ae;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			व्योम *fpm_values_va;
			u64 fpm_values_pa;
			u8 hmc_fn_id;
			u64 scratch;
		पूर्ण query_fpm_values;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			व्योम *fpm_values_va;
			u64 fpm_values_pa;
			u8 hmc_fn_id;
			u64 scratch;
		पूर्ण commit_fpm_values;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_apbvt_info info;
			u64 scratch;
		पूर्ण manage_apbvt_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_qhash_table_info info;
			u64 scratch;
		पूर्ण manage_qhash_table_entry;

		काष्ठा अणु
			काष्ठा i40iw_sc_dev *dev;
			काष्ठा i40iw_update_sds_info info;
			u64 scratch;
		पूर्ण update_pe_sds;

		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			काष्ठा i40iw_sc_qp *qp;
			u64 scratch;
		पूर्ण suspend_resume;
		काष्ठा अणु
			काष्ठा i40iw_sc_cqp *cqp;
			व्योम *cap_va;
			u64 cap_pa;
			u64 scratch;
		पूर्ण query_rdma_features;
	पूर्ण u;
पूर्ण;

काष्ठा cqp_commands_info अणु
	काष्ठा list_head cqp_cmd_entry;
	u8 cqp_cmd;
	u8 post_sq;
	काष्ठा cqp_info in;
पूर्ण;

काष्ठा i40iw_virtchnl_work_info अणु
	व्योम (*callback_fcn)(व्योम *vf_dev);
	व्योम *worker_vf_dev;
पूर्ण;

काष्ठा i40iw_cqp_समयout अणु
	u64 compl_cqp_cmds;
	u8 count;
पूर्ण;

#पूर्ण_अगर
