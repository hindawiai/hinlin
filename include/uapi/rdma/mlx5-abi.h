<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX5_ABI_USER_H
#घोषणा MLX5_ABI_USER_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>	/* For ETH_ALEN. */
#समावेश <rdma/ib_user_ioctl_verbs.h>

क्रमागत अणु
	MLX5_QP_FLAG_SIGNATURE		= 1 << 0,
	MLX5_QP_FLAG_SCATTER_CQE	= 1 << 1,
	MLX5_QP_FLAG_TUNNEL_OFFLOADS	= 1 << 2,
	MLX5_QP_FLAG_BFREG_INDEX	= 1 << 3,
	MLX5_QP_FLAG_TYPE_DCT		= 1 << 4,
	MLX5_QP_FLAG_TYPE_DCI		= 1 << 5,
	MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC = 1 << 6,
	MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC = 1 << 7,
	MLX5_QP_FLAG_ALLOW_SCATTER_CQE	= 1 << 8,
	MLX5_QP_FLAG_PACKET_BASED_CREDIT_MODE	= 1 << 9,
	MLX5_QP_FLAG_UAR_PAGE_INDEX = 1 << 10,
पूर्ण;

क्रमागत अणु
	MLX5_SRQ_FLAG_SIGNATURE		= 1 << 0,
पूर्ण;

क्रमागत अणु
	MLX5_WQ_FLAG_SIGNATURE		= 1 << 0,
पूर्ण;

/* Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा MLX5_IB_UVERBS_ABI_VERSION	1

/* Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular करो not use poपूर्णांकer types -- pass poपूर्णांकers in __u64
 * instead.
 */

काष्ठा mlx5_ib_alloc_ucontext_req अणु
	__u32	total_num_bfregs;
	__u32	num_low_latency_bfregs;
पूर्ण;

क्रमागत mlx5_lib_caps अणु
	MLX5_LIB_CAP_4K_UAR	= (__u64)1 << 0,
	MLX5_LIB_CAP_DYN_UAR	= (__u64)1 << 1,
पूर्ण;

क्रमागत mlx5_ib_alloc_uctx_v2_flags अणु
	MLX5_IB_ALLOC_UCTX_DEVX	= 1 << 0,
पूर्ण;
काष्ठा mlx5_ib_alloc_ucontext_req_v2 अणु
	__u32	total_num_bfregs;
	__u32	num_low_latency_bfregs;
	__u32	flags;
	__u32	comp_mask;
	__u8	max_cqe_version;
	__u8	reserved0;
	__u16	reserved1;
	__u32	reserved2;
	__aligned_u64 lib_caps;
पूर्ण;

क्रमागत mlx5_ib_alloc_ucontext_resp_mask अणु
	MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_CORE_CLOCK_OFFSET = 1UL << 0,
	MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_DUMP_FILL_MKEY    = 1UL << 1,
	MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_ECE               = 1UL << 2,
पूर्ण;

क्रमागत mlx5_user_cmds_supp_uhw अणु
	MLX5_USER_CMDS_SUPP_UHW_QUERY_DEVICE = 1 << 0,
	MLX5_USER_CMDS_SUPP_UHW_CREATE_AH    = 1 << 1,
पूर्ण;

/* The eth_min_अंतरभूत response value is set to off-by-one vs the FW
 * वापसed value to allow user-space to deal with older kernels.
 */
क्रमागत mlx5_user_अंतरभूत_mode अणु
	MLX5_USER_INLINE_MODE_NA,
	MLX5_USER_INLINE_MODE_NONE,
	MLX5_USER_INLINE_MODE_L2,
	MLX5_USER_INLINE_MODE_IP,
	MLX5_USER_INLINE_MODE_TCP_UDP,
पूर्ण;

क्रमागत अणु
	MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM = 1 << 0,
	MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_REQ_METADATA = 1 << 1,
	MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_SPI_STEERING = 1 << 2,
	MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_FULL_OFFLOAD = 1 << 3,
	MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_TX_IV_IS_ESN = 1 << 4,
पूर्ण;

काष्ठा mlx5_ib_alloc_ucontext_resp अणु
	__u32	qp_tab_size;
	__u32	bf_reg_size;
	__u32	tot_bfregs;
	__u32	cache_line_size;
	__u16	max_sq_desc_sz;
	__u16	max_rq_desc_sz;
	__u32	max_send_wqebb;
	__u32	max_recv_wr;
	__u32	max_srq_recv_wr;
	__u16	num_ports;
	__u16	flow_action_flags;
	__u32	comp_mask;
	__u32	response_length;
	__u8	cqe_version;
	__u8	cmds_supp_uhw;
	__u8	eth_min_अंतरभूत;
	__u8	घड़ी_info_versions;
	__aligned_u64 hca_core_घड़ी_offset;
	__u32	log_uar_size;
	__u32	num_uars_per_page;
	__u32	num_dyn_bfregs;
	__u32	dump_fill_mkey;
पूर्ण;

काष्ठा mlx5_ib_alloc_pd_resp अणु
	__u32	pdn;
पूर्ण;

काष्ठा mlx5_ib_tso_caps अणु
	__u32 max_tso; /* Maximum tso payload size in bytes */

	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_UD
	 */
	__u32 supported_qpts;
पूर्ण;

काष्ठा mlx5_ib_rss_caps अणु
	__aligned_u64 rx_hash_fields_mask; /* क्रमागत mlx5_rx_hash_fields */
	__u8 rx_hash_function; /* क्रमागत mlx5_rx_hash_function_flags */
	__u8 reserved[7];
पूर्ण;

क्रमागत mlx5_ib_cqe_comp_res_क्रमmat अणु
	MLX5_IB_CQE_RES_FORMAT_HASH	= 1 << 0,
	MLX5_IB_CQE_RES_FORMAT_CSUM	= 1 << 1,
	MLX5_IB_CQE_RES_FORMAT_CSUM_STRIDX = 1 << 2,
पूर्ण;

काष्ठा mlx5_ib_cqe_comp_caps अणु
	__u32 max_num;
	__u32 supported_क्रमmat; /* क्रमागत mlx5_ib_cqe_comp_res_क्रमmat */
पूर्ण;

क्रमागत mlx5_ib_packet_pacing_cap_flags अणु
	MLX5_IB_PP_SUPPORT_BURST	= 1 << 0,
पूर्ण;

काष्ठा mlx5_packet_pacing_caps अणु
	__u32 qp_rate_limit_min;
	__u32 qp_rate_limit_max; /* In kpbs */

	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_RAW_PACKET
	 */
	__u32 supported_qpts;
	__u8  cap_flags; /* क्रमागत mlx5_ib_packet_pacing_cap_flags */
	__u8  reserved[3];
पूर्ण;

क्रमागत mlx5_ib_mpw_caps अणु
	MPW_RESERVED		= 1 << 0,
	MLX5_IB_ALLOW_MPW	= 1 << 1,
	MLX5_IB_SUPPORT_EMPW	= 1 << 2,
पूर्ण;

क्रमागत mlx5_ib_sw_parsing_offloads अणु
	MLX5_IB_SW_PARSING = 1 << 0,
	MLX5_IB_SW_PARSING_CSUM = 1 << 1,
	MLX5_IB_SW_PARSING_LSO = 1 << 2,
पूर्ण;

काष्ठा mlx5_ib_sw_parsing_caps अणु
	__u32 sw_parsing_offloads; /* क्रमागत mlx5_ib_sw_parsing_offloads */

	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_RAW_PACKET
	 */
	__u32 supported_qpts;
पूर्ण;

काष्ठा mlx5_ib_striding_rq_caps अणु
	__u32 min_single_stride_log_num_of_bytes;
	__u32 max_single_stride_log_num_of_bytes;
	__u32 min_single_wqe_log_num_of_strides;
	__u32 max_single_wqe_log_num_of_strides;

	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_RAW_PACKET
	 */
	__u32 supported_qpts;
	__u32 reserved;
पूर्ण;

क्रमागत mlx5_ib_query_dev_resp_flags अणु
	/* Support 128B CQE compression */
	MLX5_IB_QUERY_DEV_RESP_FLAGS_CQE_128B_COMP = 1 << 0,
	MLX5_IB_QUERY_DEV_RESP_FLAGS_CQE_128B_PAD  = 1 << 1,
	MLX5_IB_QUERY_DEV_RESP_PACKET_BASED_CREDIT_MODE = 1 << 2,
	MLX5_IB_QUERY_DEV_RESP_FLAGS_SCAT2CQE_DCT = 1 << 3,
पूर्ण;

क्रमागत mlx5_ib_tunnel_offloads अणु
	MLX5_IB_TUNNELED_OFFLOADS_VXLAN  = 1 << 0,
	MLX5_IB_TUNNELED_OFFLOADS_GRE    = 1 << 1,
	MLX5_IB_TUNNELED_OFFLOADS_GENEVE = 1 << 2,
	MLX5_IB_TUNNELED_OFFLOADS_MPLS_GRE = 1 << 3,
	MLX5_IB_TUNNELED_OFFLOADS_MPLS_UDP = 1 << 4,
पूर्ण;

काष्ठा mlx5_ib_query_device_resp अणु
	__u32	comp_mask;
	__u32	response_length;
	काष्ठा	mlx5_ib_tso_caps tso_caps;
	काष्ठा	mlx5_ib_rss_caps rss_caps;
	काष्ठा	mlx5_ib_cqe_comp_caps cqe_comp_caps;
	काष्ठा	mlx5_packet_pacing_caps packet_pacing_caps;
	__u32	mlx5_ib_support_multi_pkt_send_wqes;
	__u32	flags; /* Use क्रमागत mlx5_ib_query_dev_resp_flags */
	काष्ठा mlx5_ib_sw_parsing_caps sw_parsing_caps;
	काष्ठा mlx5_ib_striding_rq_caps striding_rq_caps;
	__u32	tunnel_offloads_caps; /* क्रमागत mlx5_ib_tunnel_offloads */
	__u32	reserved;
पूर्ण;

क्रमागत mlx5_ib_create_cq_flags अणु
	MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD	= 1 << 0,
	MLX5_IB_CREATE_CQ_FLAGS_UAR_PAGE_INDEX  = 1 << 1,
पूर्ण;

काष्ठा mlx5_ib_create_cq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u32	cqe_size;
	__u8    cqe_comp_en;
	__u8    cqe_comp_res_क्रमmat;
	__u16	flags;
	__u16	uar_page_index;
	__u16	reserved0;
	__u32	reserved1;
पूर्ण;

काष्ठा mlx5_ib_create_cq_resp अणु
	__u32	cqn;
	__u32	reserved;
पूर्ण;

काष्ठा mlx5_ib_resize_cq अणु
	__aligned_u64 buf_addr;
	__u16	cqe_size;
	__u16	reserved0;
	__u32	reserved1;
पूर्ण;

काष्ठा mlx5_ib_create_srq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u32	flags;
	__u32	reserved0; /* explicit padding (optional on i386) */
	__u32	uidx;
	__u32	reserved1;
पूर्ण;

काष्ठा mlx5_ib_create_srq_resp अणु
	__u32	srqn;
	__u32	reserved;
पूर्ण;

काष्ठा mlx5_ib_create_qp अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u32	sq_wqe_count;
	__u32	rq_wqe_count;
	__u32	rq_wqe_shअगरt;
	__u32	flags;
	__u32	uidx;
	__u32	bfreg_index;
	जोड़ अणु
		__aligned_u64 sq_buf_addr;
		__aligned_u64 access_key;
	पूर्ण;
	__u32  ece_options;
	__u32  reserved;
पूर्ण;

/* RX Hash function flags */
क्रमागत mlx5_rx_hash_function_flags अणु
	MLX5_RX_HASH_FUNC_TOEPLITZ	= 1 << 0,
पूर्ण;

/*
 * RX Hash flags, these flags allows to set which incoming packet's field should
 * participates in RX Hash. Each flag represent certain packet's field,
 * when the flag is set the field that is represented by the flag will
 * participate in RX Hash calculation.
 * Note: *IPV4 and *IPV6 flags can't be enabled together on the same QP
 * and *TCP and *UDP flags can't be enabled together on the same QP.
*/
क्रमागत mlx5_rx_hash_fields अणु
	MLX5_RX_HASH_SRC_IPV4	= 1 << 0,
	MLX5_RX_HASH_DST_IPV4	= 1 << 1,
	MLX5_RX_HASH_SRC_IPV6	= 1 << 2,
	MLX5_RX_HASH_DST_IPV6	= 1 << 3,
	MLX5_RX_HASH_SRC_PORT_TCP	= 1 << 4,
	MLX5_RX_HASH_DST_PORT_TCP	= 1 << 5,
	MLX5_RX_HASH_SRC_PORT_UDP	= 1 << 6,
	MLX5_RX_HASH_DST_PORT_UDP	= 1 << 7,
	MLX5_RX_HASH_IPSEC_SPI		= 1 << 8,
	/* Save bits क्रम future fields */
	MLX5_RX_HASH_INNER		= (1UL << 31),
पूर्ण;

काष्ठा mlx5_ib_create_qp_rss अणु
	__aligned_u64 rx_hash_fields_mask; /* क्रमागत mlx5_rx_hash_fields */
	__u8 rx_hash_function; /* क्रमागत mlx5_rx_hash_function_flags */
	__u8 rx_key_len; /* valid only क्रम Toeplitz */
	__u8 reserved[6];
	__u8 rx_hash_key[128]; /* valid only क्रम Toeplitz */
	__u32   comp_mask;
	__u32	flags;
पूर्ण;

क्रमागत mlx5_ib_create_qp_resp_mask अणु
	MLX5_IB_CREATE_QP_RESP_MASK_TIRN = 1UL << 0,
	MLX5_IB_CREATE_QP_RESP_MASK_TISN = 1UL << 1,
	MLX5_IB_CREATE_QP_RESP_MASK_RQN  = 1UL << 2,
	MLX5_IB_CREATE_QP_RESP_MASK_SQN  = 1UL << 3,
	MLX5_IB_CREATE_QP_RESP_MASK_TIR_ICM_ADDR  = 1UL << 4,
पूर्ण;

काष्ठा mlx5_ib_create_qp_resp अणु
	__u32	bfreg_index;
	__u32   ece_options;
	__u32	comp_mask;
	__u32	tirn;
	__u32	tisn;
	__u32	rqn;
	__u32	sqn;
	__u32   reserved1;
	__u64	tir_icm_addr;
पूर्ण;

काष्ठा mlx5_ib_alloc_mw अणु
	__u32	comp_mask;
	__u8	num_klms;
	__u8	reserved1;
	__u16	reserved2;
पूर्ण;

क्रमागत mlx5_ib_create_wq_mask अणु
	MLX5_IB_CREATE_WQ_STRIDING_RQ	= (1 << 0),
पूर्ण;

काष्ठा mlx5_ib_create_wq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u32   rq_wqe_count;
	__u32   rq_wqe_shअगरt;
	__u32   user_index;
	__u32   flags;
	__u32   comp_mask;
	__u32	single_stride_log_num_of_bytes;
	__u32	single_wqe_log_num_of_strides;
	__u32	two_byte_shअगरt_en;
पूर्ण;

काष्ठा mlx5_ib_create_ah_resp अणु
	__u32	response_length;
	__u8	dmac[ETH_ALEN];
	__u8	reserved[6];
पूर्ण;

काष्ठा mlx5_ib_burst_info अणु
	__u32       max_burst_sz;
	__u16       typical_pkt_sz;
	__u16       reserved;
पूर्ण;

काष्ठा mlx5_ib_modअगरy_qp अणु
	__u32			   comp_mask;
	काष्ठा mlx5_ib_burst_info  burst_info;
	__u32			   ece_options;
पूर्ण;

काष्ठा mlx5_ib_modअगरy_qp_resp अणु
	__u32	response_length;
	__u32	dctn;
	__u32   ece_options;
	__u32   reserved;
पूर्ण;

काष्ठा mlx5_ib_create_wq_resp अणु
	__u32	response_length;
	__u32	reserved;
पूर्ण;

काष्ठा mlx5_ib_create_rwq_ind_tbl_resp अणु
	__u32	response_length;
	__u32	reserved;
पूर्ण;

काष्ठा mlx5_ib_modअगरy_wq अणु
	__u32	comp_mask;
	__u32	reserved;
पूर्ण;

काष्ठा mlx5_ib_घड़ी_info अणु
	__u32 sign;
	__u32 resv;
	__aligned_u64 nsec;
	__aligned_u64 cycles;
	__aligned_u64 frac;
	__u32 mult;
	__u32 shअगरt;
	__aligned_u64 mask;
	__aligned_u64 overflow_period;
पूर्ण;

क्रमागत mlx5_ib_mmap_cmd अणु
	MLX5_IB_MMAP_REGULAR_PAGE               = 0,
	MLX5_IB_MMAP_GET_CONTIGUOUS_PAGES       = 1,
	MLX5_IB_MMAP_WC_PAGE                    = 2,
	MLX5_IB_MMAP_NC_PAGE                    = 3,
	/* 5 is chosen in order to be compatible with old versions of libmlx5 */
	MLX5_IB_MMAP_CORE_CLOCK                 = 5,
	MLX5_IB_MMAP_ALLOC_WC                   = 6,
	MLX5_IB_MMAP_CLOCK_INFO                 = 7,
	MLX5_IB_MMAP_DEVICE_MEM                 = 8,
पूर्ण;

क्रमागत अणु
	MLX5_IB_CLOCK_INFO_KERNEL_UPDATING = 1,
पूर्ण;

/* Bit indexes क्रम the mlx5_alloc_ucontext_resp.घड़ी_info_versions biपंचांगap */
क्रमागत अणु
	MLX5_IB_CLOCK_INFO_V1              = 0,
पूर्ण;

काष्ठा mlx5_ib_flow_counters_desc अणु
	__u32	description;
	__u32	index;
पूर्ण;

काष्ठा mlx5_ib_flow_counters_data अणु
	RDMA_UAPI_PTR(काष्ठा mlx5_ib_flow_counters_desc *, counters_data);
	__u32   ncounters;
	__u32   reserved;
पूर्ण;

काष्ठा mlx5_ib_create_flow अणु
	__u32   ncounters_data;
	__u32   reserved;
	/*
	 * Following are counters data based on ncounters_data, each
	 * entry in the data[] should match a corresponding counter object
	 * that was poपूर्णांकed by a counters spec upon the flow creation
	 */
	काष्ठा mlx5_ib_flow_counters_data data[];
पूर्ण;

#पूर्ण_अगर /* MLX5_ABI_USER_H */
