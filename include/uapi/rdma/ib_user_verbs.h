<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 PathScale, Inc.  All rights reserved.
 * Copyright (c) 2006 Mellanox Technologies.  All rights reserved.
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

#अगर_अघोषित IB_USER_VERBS_H
#घोषणा IB_USER_VERBS_H

#समावेश <linux/types.h>

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा IB_USER_VERBS_ABI_VERSION	6
#घोषणा IB_USER_VERBS_CMD_THRESHOLD    50

क्रमागत ib_uverbs_ग_लिखो_cmds अणु
	IB_USER_VERBS_CMD_GET_CONTEXT,
	IB_USER_VERBS_CMD_QUERY_DEVICE,
	IB_USER_VERBS_CMD_QUERY_PORT,
	IB_USER_VERBS_CMD_ALLOC_PD,
	IB_USER_VERBS_CMD_DEALLOC_PD,
	IB_USER_VERBS_CMD_CREATE_AH,
	IB_USER_VERBS_CMD_MODIFY_AH,
	IB_USER_VERBS_CMD_QUERY_AH,
	IB_USER_VERBS_CMD_DESTROY_AH,
	IB_USER_VERBS_CMD_REG_MR,
	IB_USER_VERBS_CMD_REG_SMR,
	IB_USER_VERBS_CMD_REREG_MR,
	IB_USER_VERBS_CMD_QUERY_MR,
	IB_USER_VERBS_CMD_DEREG_MR,
	IB_USER_VERBS_CMD_ALLOC_MW,
	IB_USER_VERBS_CMD_BIND_MW,
	IB_USER_VERBS_CMD_DEALLOC_MW,
	IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL,
	IB_USER_VERBS_CMD_CREATE_CQ,
	IB_USER_VERBS_CMD_RESIZE_CQ,
	IB_USER_VERBS_CMD_DESTROY_CQ,
	IB_USER_VERBS_CMD_POLL_CQ,
	IB_USER_VERBS_CMD_PEEK_CQ,
	IB_USER_VERBS_CMD_REQ_NOTIFY_CQ,
	IB_USER_VERBS_CMD_CREATE_QP,
	IB_USER_VERBS_CMD_QUERY_QP,
	IB_USER_VERBS_CMD_MODIFY_QP,
	IB_USER_VERBS_CMD_DESTROY_QP,
	IB_USER_VERBS_CMD_POST_SEND,
	IB_USER_VERBS_CMD_POST_RECV,
	IB_USER_VERBS_CMD_ATTACH_MCAST,
	IB_USER_VERBS_CMD_DETACH_MCAST,
	IB_USER_VERBS_CMD_CREATE_SRQ,
	IB_USER_VERBS_CMD_MODIFY_SRQ,
	IB_USER_VERBS_CMD_QUERY_SRQ,
	IB_USER_VERBS_CMD_DESTROY_SRQ,
	IB_USER_VERBS_CMD_POST_SRQ_RECV,
	IB_USER_VERBS_CMD_OPEN_XRCD,
	IB_USER_VERBS_CMD_CLOSE_XRCD,
	IB_USER_VERBS_CMD_CREATE_XSRQ,
	IB_USER_VERBS_CMD_OPEN_QP,
पूर्ण;

क्रमागत अणु
	IB_USER_VERBS_EX_CMD_QUERY_DEVICE = IB_USER_VERBS_CMD_QUERY_DEVICE,
	IB_USER_VERBS_EX_CMD_CREATE_CQ = IB_USER_VERBS_CMD_CREATE_CQ,
	IB_USER_VERBS_EX_CMD_CREATE_QP = IB_USER_VERBS_CMD_CREATE_QP,
	IB_USER_VERBS_EX_CMD_MODIFY_QP = IB_USER_VERBS_CMD_MODIFY_QP,
	IB_USER_VERBS_EX_CMD_CREATE_FLOW = IB_USER_VERBS_CMD_THRESHOLD,
	IB_USER_VERBS_EX_CMD_DESTROY_FLOW,
	IB_USER_VERBS_EX_CMD_CREATE_WQ,
	IB_USER_VERBS_EX_CMD_MODIFY_WQ,
	IB_USER_VERBS_EX_CMD_DESTROY_WQ,
	IB_USER_VERBS_EX_CMD_CREATE_RWQ_IND_TBL,
	IB_USER_VERBS_EX_CMD_DESTROY_RWQ_IND_TBL,
	IB_USER_VERBS_EX_CMD_MODIFY_CQ
पूर्ण;

/*
 * Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 * Specअगरically:
 *  - Do not use poपूर्णांकer types -- pass poपूर्णांकers in __u64 instead.
 *  - Make sure that any काष्ठाure larger than 4 bytes is padded to a
 *    multiple of 8 bytes.  Otherwise the काष्ठाure size will be
 *    dअगरferent between 32-bit and 64-bit architectures.
 */

काष्ठा ib_uverbs_async_event_desc अणु
	__aligned_u64 element;
	__u32 event_type;	/* क्रमागत ib_event_type */
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_comp_event_desc अणु
	__aligned_u64 cq_handle;
पूर्ण;

काष्ठा ib_uverbs_cq_moderation_caps अणु
	__u16     max_cq_moderation_count;
	__u16     max_cq_moderation_period;
	__u32     reserved;
पूर्ण;

/*
 * All commands from userspace should start with a __u32 command field
 * followed by __u16 in_words and out_words fields (which give the
 * length of the command block and response buffer अगर any in 32-bit
 * words).  The kernel driver will पढ़ो these fields first and पढ़ो
 * the rest of the command काष्ठा based on these value.
 */

#घोषणा IB_USER_VERBS_CMD_COMMAND_MASK 0xff
#घोषणा IB_USER_VERBS_CMD_FLAG_EXTENDED 0x80000000u

काष्ठा ib_uverbs_cmd_hdr अणु
	__u32 command;
	__u16 in_words;
	__u16 out_words;
पूर्ण;

काष्ठा ib_uverbs_ex_cmd_hdr अणु
	__aligned_u64 response;
	__u16 provider_in_words;
	__u16 provider_out_words;
	__u32 cmd_hdr_reserved;
पूर्ण;

काष्ठा ib_uverbs_get_context अणु
	__aligned_u64 response;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_get_context_resp अणु
	__u32 async_fd;
	__u32 num_comp_vectors;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_device अणु
	__aligned_u64 response;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_device_resp अणु
	__aligned_u64 fw_ver;
	__be64 node_guid;
	__be64 sys_image_guid;
	__aligned_u64 max_mr_size;
	__aligned_u64 page_size_cap;
	__u32 venकरोr_id;
	__u32 venकरोr_part_id;
	__u32 hw_ver;
	__u32 max_qp;
	__u32 max_qp_wr;
	__u32 device_cap_flags;
	__u32 max_sge;
	__u32 max_sge_rd;
	__u32 max_cq;
	__u32 max_cqe;
	__u32 max_mr;
	__u32 max_pd;
	__u32 max_qp_rd_atom;
	__u32 max_ee_rd_atom;
	__u32 max_res_rd_atom;
	__u32 max_qp_init_rd_atom;
	__u32 max_ee_init_rd_atom;
	__u32 atomic_cap;
	__u32 max_ee;
	__u32 max_rdd;
	__u32 max_mw;
	__u32 max_raw_ipv6_qp;
	__u32 max_raw_ethy_qp;
	__u32 max_mcast_grp;
	__u32 max_mcast_qp_attach;
	__u32 max_total_mcast_qp_attach;
	__u32 max_ah;
	__u32 max_fmr;
	__u32 max_map_per_fmr;
	__u32 max_srq;
	__u32 max_srq_wr;
	__u32 max_srq_sge;
	__u16 max_pkeys;
	__u8  local_ca_ack_delay;
	__u8  phys_port_cnt;
	__u8  reserved[4];
पूर्ण;

काष्ठा ib_uverbs_ex_query_device अणु
	__u32 comp_mask;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_odp_caps अणु
	__aligned_u64 general_caps;
	काष्ठा अणु
		__u32 rc_odp_caps;
		__u32 uc_odp_caps;
		__u32 ud_odp_caps;
	पूर्ण per_transport_caps;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_rss_caps अणु
	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported, e.g.
	 * supported_qpts |= 1 << IB_QPT_UD
	 */
	__u32 supported_qpts;
	__u32 max_rwq_indirection_tables;
	__u32 max_rwq_indirection_table_size;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_पंचांग_caps अणु
	/* Max size of rendezvous request message */
	__u32 max_rndv_hdr_size;
	/* Max number of entries in tag matching list */
	__u32 max_num_tags;
	/* TM flags */
	__u32 flags;
	/* Max number of outstanding list operations */
	__u32 max_ops;
	/* Max number of SGE in tag matching entry */
	__u32 max_sge;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_ex_query_device_resp अणु
	काष्ठा ib_uverbs_query_device_resp base;
	__u32 comp_mask;
	__u32 response_length;
	काष्ठा ib_uverbs_odp_caps odp_caps;
	__aligned_u64 बारtamp_mask;
	__aligned_u64 hca_core_घड़ी; /* in KHZ */
	__aligned_u64 device_cap_flags_ex;
	काष्ठा ib_uverbs_rss_caps rss_caps;
	__u32  max_wq_type_rq;
	__u32 raw_packet_caps;
	काष्ठा ib_uverbs_पंचांग_caps पंचांग_caps;
	काष्ठा ib_uverbs_cq_moderation_caps cq_moderation_caps;
	__aligned_u64 max_dm_size;
	__u32 xrc_odp_caps;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_query_port अणु
	__aligned_u64 response;
	__u8  port_num;
	__u8  reserved[7];
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_port_resp अणु
	__u32 port_cap_flags;		/* see ib_uverbs_query_port_cap_flags */
	__u32 max_msg_sz;
	__u32 bad_pkey_cntr;
	__u32 qkey_viol_cntr;
	__u32 gid_tbl_len;
	__u16 pkey_tbl_len;
	__u16 lid;
	__u16 sm_lid;
	__u8  state;
	__u8  max_mtu;
	__u8  active_mtu;
	__u8  lmc;
	__u8  max_vl_num;
	__u8  sm_sl;
	__u8  subnet_समयout;
	__u8  init_type_reply;
	__u8  active_width;
	__u8  active_speed;
	__u8  phys_state;
	__u8  link_layer;
	__u8  flags;			/* see ib_uverbs_query_port_flags */
	__u8  reserved;
पूर्ण;

काष्ठा ib_uverbs_alloc_pd अणु
	__aligned_u64 response;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_alloc_pd_resp अणु
	__u32 pd_handle;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_dealloc_pd अणु
	__u32 pd_handle;
पूर्ण;

काष्ठा ib_uverbs_खोलो_xrcd अणु
	__aligned_u64 response;
	__u32 fd;
	__u32 oflags;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_खोलो_xrcd_resp अणु
	__u32 xrcd_handle;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_बंद_xrcd अणु
	__u32 xrcd_handle;
पूर्ण;

काष्ठा ib_uverbs_reg_mr अणु
	__aligned_u64 response;
	__aligned_u64 start;
	__aligned_u64 length;
	__aligned_u64 hca_va;
	__u32 pd_handle;
	__u32 access_flags;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_reg_mr_resp अणु
	__u32 mr_handle;
	__u32 lkey;
	__u32 rkey;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_rereg_mr अणु
	__aligned_u64 response;
	__u32 mr_handle;
	__u32 flags;
	__aligned_u64 start;
	__aligned_u64 length;
	__aligned_u64 hca_va;
	__u32 pd_handle;
	__u32 access_flags;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_rereg_mr_resp अणु
	__u32 lkey;
	__u32 rkey;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_dereg_mr अणु
	__u32 mr_handle;
पूर्ण;

काष्ठा ib_uverbs_alloc_mw अणु
	__aligned_u64 response;
	__u32 pd_handle;
	__u8  mw_type;
	__u8  reserved[3];
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_alloc_mw_resp अणु
	__u32 mw_handle;
	__u32 rkey;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_dealloc_mw अणु
	__u32 mw_handle;
पूर्ण;

काष्ठा ib_uverbs_create_comp_channel अणु
	__aligned_u64 response;
पूर्ण;

काष्ठा ib_uverbs_create_comp_channel_resp अणु
	__u32 fd;
पूर्ण;

काष्ठा ib_uverbs_create_cq अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 cqe;
	__u32 comp_vector;
	__s32 comp_channel;
	__u32 reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

क्रमागत ib_uverbs_ex_create_cq_flags अणु
	IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION = 1 << 0,
	IB_UVERBS_CQ_FLAGS_IGNORE_OVERRUN = 1 << 1,
पूर्ण;

काष्ठा ib_uverbs_ex_create_cq अणु
	__aligned_u64 user_handle;
	__u32 cqe;
	__u32 comp_vector;
	__s32 comp_channel;
	__u32 comp_mask;
	__u32 flags;  /* biपंचांगask of ib_uverbs_ex_create_cq_flags */
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_create_cq_resp अणु
	__u32 cq_handle;
	__u32 cqe;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_ex_create_cq_resp अणु
	काष्ठा ib_uverbs_create_cq_resp base;
	__u32 comp_mask;
	__u32 response_length;
पूर्ण;

काष्ठा ib_uverbs_resize_cq अणु
	__aligned_u64 response;
	__u32 cq_handle;
	__u32 cqe;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_resize_cq_resp अणु
	__u32 cqe;
	__u32 reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_poll_cq अणु
	__aligned_u64 response;
	__u32 cq_handle;
	__u32 ne;
पूर्ण;

क्रमागत ib_uverbs_wc_opcode अणु
	IB_UVERBS_WC_SEND = 0,
	IB_UVERBS_WC_RDMA_WRITE = 1,
	IB_UVERBS_WC_RDMA_READ = 2,
	IB_UVERBS_WC_COMP_SWAP = 3,
	IB_UVERBS_WC_FETCH_ADD = 4,
	IB_UVERBS_WC_BIND_MW = 5,
	IB_UVERBS_WC_LOCAL_INV = 6,
	IB_UVERBS_WC_TSO = 7,
पूर्ण;

काष्ठा ib_uverbs_wc अणु
	__aligned_u64 wr_id;
	__u32 status;
	__u32 opcode;
	__u32 venकरोr_err;
	__u32 byte_len;
	जोड़ अणु
		__be32 imm_data;
		__u32 invalidate_rkey;
	पूर्ण ex;
	__u32 qp_num;
	__u32 src_qp;
	__u32 wc_flags;
	__u16 pkey_index;
	__u16 slid;
	__u8 sl;
	__u8 dlid_path_bits;
	__u8 port_num;
	__u8 reserved;
पूर्ण;

काष्ठा ib_uverbs_poll_cq_resp अणु
	__u32 count;
	__u32 reserved;
	काष्ठा ib_uverbs_wc wc[0];
पूर्ण;

काष्ठा ib_uverbs_req_notअगरy_cq अणु
	__u32 cq_handle;
	__u32 solicited_only;
पूर्ण;

काष्ठा ib_uverbs_destroy_cq अणु
	__aligned_u64 response;
	__u32 cq_handle;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_destroy_cq_resp अणु
	__u32 comp_events_reported;
	__u32 async_events_reported;
पूर्ण;

काष्ठा ib_uverbs_global_route अणु
	__u8  dgid[16];
	__u32 flow_label;
	__u8  sgid_index;
	__u8  hop_limit;
	__u8  traffic_class;
	__u8  reserved;
पूर्ण;

काष्ठा ib_uverbs_ah_attr अणु
	काष्ठा ib_uverbs_global_route grh;
	__u16 dlid;
	__u8  sl;
	__u8  src_path_bits;
	__u8  अटल_rate;
	__u8  is_global;
	__u8  port_num;
	__u8  reserved;
पूर्ण;

काष्ठा ib_uverbs_qp_attr अणु
	__u32	qp_attr_mask;
	__u32	qp_state;
	__u32	cur_qp_state;
	__u32	path_mtu;
	__u32	path_mig_state;
	__u32	qkey;
	__u32	rq_psn;
	__u32	sq_psn;
	__u32	dest_qp_num;
	__u32	qp_access_flags;

	काष्ठा ib_uverbs_ah_attr ah_attr;
	काष्ठा ib_uverbs_ah_attr alt_ah_attr;

	/* ib_qp_cap */
	__u32	max_send_wr;
	__u32	max_recv_wr;
	__u32	max_send_sge;
	__u32	max_recv_sge;
	__u32	max_अंतरभूत_data;

	__u16	pkey_index;
	__u16	alt_pkey_index;
	__u8	en_sqd_async_notअगरy;
	__u8	sq_draining;
	__u8	max_rd_atomic;
	__u8	max_dest_rd_atomic;
	__u8	min_rnr_समयr;
	__u8	port_num;
	__u8	समयout;
	__u8	retry_cnt;
	__u8	rnr_retry;
	__u8	alt_port_num;
	__u8	alt_समयout;
	__u8	reserved[5];
पूर्ण;

काष्ठा ib_uverbs_create_qp अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 send_cq_handle;
	__u32 recv_cq_handle;
	__u32 srq_handle;
	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_send_sge;
	__u32 max_recv_sge;
	__u32 max_अंतरभूत_data;
	__u8  sq_sig_all;
	__u8  qp_type;
	__u8  is_srq;
	__u8  reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

क्रमागत ib_uverbs_create_qp_mask अणु
	IB_UVERBS_CREATE_QP_MASK_IND_TABLE = 1UL << 0,
पूर्ण;

क्रमागत अणु
	IB_UVERBS_CREATE_QP_SUP_COMP_MASK = IB_UVERBS_CREATE_QP_MASK_IND_TABLE,
पूर्ण;

काष्ठा ib_uverbs_ex_create_qp अणु
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 send_cq_handle;
	__u32 recv_cq_handle;
	__u32 srq_handle;
	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_send_sge;
	__u32 max_recv_sge;
	__u32 max_अंतरभूत_data;
	__u8  sq_sig_all;
	__u8  qp_type;
	__u8  is_srq;
	__u8 reserved;
	__u32 comp_mask;
	__u32 create_flags;
	__u32 rwq_ind_tbl_handle;
	__u32  source_qpn;
पूर्ण;

काष्ठा ib_uverbs_खोलो_qp अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 qpn;
	__u8  qp_type;
	__u8  reserved[7];
	__aligned_u64 driver_data[0];
पूर्ण;

/* also used क्रम खोलो response */
काष्ठा ib_uverbs_create_qp_resp अणु
	__u32 qp_handle;
	__u32 qpn;
	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_send_sge;
	__u32 max_recv_sge;
	__u32 max_अंतरभूत_data;
	__u32 reserved;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_ex_create_qp_resp अणु
	काष्ठा ib_uverbs_create_qp_resp base;
	__u32 comp_mask;
	__u32 response_length;
पूर्ण;

/*
 * This काष्ठा needs to reमुख्य a multiple of 8 bytes to keep the
 * alignment of the modअगरy QP parameters.
 */
काष्ठा ib_uverbs_qp_dest अणु
	__u8  dgid[16];
	__u32 flow_label;
	__u16 dlid;
	__u16 reserved;
	__u8  sgid_index;
	__u8  hop_limit;
	__u8  traffic_class;
	__u8  sl;
	__u8  src_path_bits;
	__u8  अटल_rate;
	__u8  is_global;
	__u8  port_num;
पूर्ण;

काष्ठा ib_uverbs_query_qp अणु
	__aligned_u64 response;
	__u32 qp_handle;
	__u32 attr_mask;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_qp_resp अणु
	काष्ठा ib_uverbs_qp_dest dest;
	काष्ठा ib_uverbs_qp_dest alt_dest;
	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_send_sge;
	__u32 max_recv_sge;
	__u32 max_अंतरभूत_data;
	__u32 qkey;
	__u32 rq_psn;
	__u32 sq_psn;
	__u32 dest_qp_num;
	__u32 qp_access_flags;
	__u16 pkey_index;
	__u16 alt_pkey_index;
	__u8  qp_state;
	__u8  cur_qp_state;
	__u8  path_mtu;
	__u8  path_mig_state;
	__u8  sq_draining;
	__u8  max_rd_atomic;
	__u8  max_dest_rd_atomic;
	__u8  min_rnr_समयr;
	__u8  port_num;
	__u8  समयout;
	__u8  retry_cnt;
	__u8  rnr_retry;
	__u8  alt_port_num;
	__u8  alt_समयout;
	__u8  sq_sig_all;
	__u8  reserved[5];
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_modअगरy_qp अणु
	काष्ठा ib_uverbs_qp_dest dest;
	काष्ठा ib_uverbs_qp_dest alt_dest;
	__u32 qp_handle;
	__u32 attr_mask;
	__u32 qkey;
	__u32 rq_psn;
	__u32 sq_psn;
	__u32 dest_qp_num;
	__u32 qp_access_flags;
	__u16 pkey_index;
	__u16 alt_pkey_index;
	__u8  qp_state;
	__u8  cur_qp_state;
	__u8  path_mtu;
	__u8  path_mig_state;
	__u8  en_sqd_async_notअगरy;
	__u8  max_rd_atomic;
	__u8  max_dest_rd_atomic;
	__u8  min_rnr_समयr;
	__u8  port_num;
	__u8  समयout;
	__u8  retry_cnt;
	__u8  rnr_retry;
	__u8  alt_port_num;
	__u8  alt_समयout;
	__u8  reserved[2];
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_ex_modअगरy_qp अणु
	काष्ठा ib_uverbs_modअगरy_qp base;
	__u32	rate_limit;
	__u32	reserved;
पूर्ण;

काष्ठा ib_uverbs_ex_modअगरy_qp_resp अणु
	__u32  comp_mask;
	__u32  response_length;
पूर्ण;

काष्ठा ib_uverbs_destroy_qp अणु
	__aligned_u64 response;
	__u32 qp_handle;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_destroy_qp_resp अणु
	__u32 events_reported;
पूर्ण;

/*
 * The ib_uverbs_sge काष्ठाure isn't used anywhere, since we assume
 * the ib_sge काष्ठाure is packed the same way on 32-bit and 64-bit
 * architectures in both kernel and user space.  It's just here to
 * करोcument the ABI.
 */
काष्ठा ib_uverbs_sge अणु
	__aligned_u64 addr;
	__u32 length;
	__u32 lkey;
पूर्ण;

क्रमागत ib_uverbs_wr_opcode अणु
	IB_UVERBS_WR_RDMA_WRITE = 0,
	IB_UVERBS_WR_RDMA_WRITE_WITH_IMM = 1,
	IB_UVERBS_WR_SEND = 2,
	IB_UVERBS_WR_SEND_WITH_IMM = 3,
	IB_UVERBS_WR_RDMA_READ = 4,
	IB_UVERBS_WR_ATOMIC_CMP_AND_SWP = 5,
	IB_UVERBS_WR_ATOMIC_FETCH_AND_ADD = 6,
	IB_UVERBS_WR_LOCAL_INV = 7,
	IB_UVERBS_WR_BIND_MW = 8,
	IB_UVERBS_WR_SEND_WITH_INV = 9,
	IB_UVERBS_WR_TSO = 10,
	IB_UVERBS_WR_RDMA_READ_WITH_INV = 11,
	IB_UVERBS_WR_MASKED_ATOMIC_CMP_AND_SWP = 12,
	IB_UVERBS_WR_MASKED_ATOMIC_FETCH_AND_ADD = 13,
	/* Review क्रमागत ib_wr_opcode beक्रमe modअगरying this */
पूर्ण;

काष्ठा ib_uverbs_send_wr अणु
	__aligned_u64 wr_id;
	__u32 num_sge;
	__u32 opcode;		/* see क्रमागत ib_uverbs_wr_opcode */
	__u32 send_flags;
	जोड़ अणु
		__be32 imm_data;
		__u32 invalidate_rkey;
	पूर्ण ex;
	जोड़ अणु
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__u32 rkey;
			__u32 reserved;
		पूर्ण rdma;
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__aligned_u64 compare_add;
			__aligned_u64 swap;
			__u32 rkey;
			__u32 reserved;
		पूर्ण atomic;
		काष्ठा अणु
			__u32 ah;
			__u32 remote_qpn;
			__u32 remote_qkey;
			__u32 reserved;
		पूर्ण ud;
	पूर्ण wr;
पूर्ण;

काष्ठा ib_uverbs_post_send अणु
	__aligned_u64 response;
	__u32 qp_handle;
	__u32 wr_count;
	__u32 sge_count;
	__u32 wqe_size;
	काष्ठा ib_uverbs_send_wr send_wr[0];
पूर्ण;

काष्ठा ib_uverbs_post_send_resp अणु
	__u32 bad_wr;
पूर्ण;

काष्ठा ib_uverbs_recv_wr अणु
	__aligned_u64 wr_id;
	__u32 num_sge;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_post_recv अणु
	__aligned_u64 response;
	__u32 qp_handle;
	__u32 wr_count;
	__u32 sge_count;
	__u32 wqe_size;
	काष्ठा ib_uverbs_recv_wr recv_wr[0];
पूर्ण;

काष्ठा ib_uverbs_post_recv_resp अणु
	__u32 bad_wr;
पूर्ण;

काष्ठा ib_uverbs_post_srq_recv अणु
	__aligned_u64 response;
	__u32 srq_handle;
	__u32 wr_count;
	__u32 sge_count;
	__u32 wqe_size;
	काष्ठा ib_uverbs_recv_wr recv[0];
पूर्ण;

काष्ठा ib_uverbs_post_srq_recv_resp अणु
	__u32 bad_wr;
पूर्ण;

काष्ठा ib_uverbs_create_ah अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 reserved;
	काष्ठा ib_uverbs_ah_attr attr;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_create_ah_resp अणु
	__u32 ah_handle;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_destroy_ah अणु
	__u32 ah_handle;
पूर्ण;

काष्ठा ib_uverbs_attach_mcast अणु
	__u8  gid[16];
	__u32 qp_handle;
	__u16 mlid;
	__u16 reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_detach_mcast अणु
	__u8  gid[16];
	__u32 qp_handle;
	__u16 mlid;
	__u16 reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_flow_spec_hdr अणु
	__u32 type;
	__u16 size;
	__u16 reserved;
	/* followed by flow_spec */
	__aligned_u64 flow_spec_data[0];
पूर्ण;

काष्ठा ib_uverbs_flow_eth_filter अणु
	__u8  dst_mac[6];
	__u8  src_mac[6];
	__be16 ether_type;
	__be16 vlan_tag;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_eth अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_eth_filter val;
	काष्ठा ib_uverbs_flow_eth_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_ipv4_filter अणु
	__be32 src_ip;
	__be32 dst_ip;
	__u8	proto;
	__u8	tos;
	__u8	ttl;
	__u8	flags;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_ipv4 अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_ipv4_filter val;
	काष्ठा ib_uverbs_flow_ipv4_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_tcp_udp_filter अणु
	__be16 dst_port;
	__be16 src_port;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_tcp_udp अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_tcp_udp_filter val;
	काष्ठा ib_uverbs_flow_tcp_udp_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_ipv6_filter अणु
	__u8    src_ip[16];
	__u8    dst_ip[16];
	__be32	flow_label;
	__u8	next_hdr;
	__u8	traffic_class;
	__u8	hop_limit;
	__u8	reserved;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_ipv6 अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_ipv6_filter val;
	काष्ठा ib_uverbs_flow_ipv6_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_action_tag अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	__u32			      tag_id;
	__u32			      reserved1;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_action_drop अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_action_handle अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	__u32			      handle;
	__u32			      reserved1;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_action_count अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	__u32			      handle;
	__u32			      reserved1;
पूर्ण;

काष्ठा ib_uverbs_flow_tunnel_filter अणु
	__be32 tunnel_id;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_tunnel अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_tunnel_filter val;
	काष्ठा ib_uverbs_flow_tunnel_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_esp_filter अणु
	__u32 spi;
	__u32 seq;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_esp अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_spec_esp_filter val;
	काष्ठा ib_uverbs_flow_spec_esp_filter mask;
पूर्ण;

काष्ठा ib_uverbs_flow_gre_filter अणु
	/* c_ks_res0_ver field is bits 0-15 in offset 0 of a standard GRE header:
	 * bit 0 - C - checksum bit.
	 * bit 1 - reserved. set to 0.
	 * bit 2 - key bit.
	 * bit 3 - sequence number bit.
	 * bits 4:12 - reserved. set to 0.
	 * bits 13:15 - GRE version.
	 */
	__be16 c_ks_res0_ver;
	__be16 protocol;
	__be32 key;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_gre अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_gre_filter     val;
	काष्ठा ib_uverbs_flow_gre_filter     mask;
पूर्ण;

काष्ठा ib_uverbs_flow_mpls_filter अणु
	/* The field includes the entire MPLS label:
	 * bits 0:19 - label field.
	 * bits 20:22 - traffic class field.
	 * bits 23 - bottom of stack bit.
	 * bits 24:31 - ttl field.
	 */
	__be32 label;
पूर्ण;

काष्ठा ib_uverbs_flow_spec_mpls अणु
	जोड़ अणु
		काष्ठा ib_uverbs_flow_spec_hdr hdr;
		काष्ठा अणु
			__u32 type;
			__u16 size;
			__u16 reserved;
		पूर्ण;
	पूर्ण;
	काष्ठा ib_uverbs_flow_mpls_filter     val;
	काष्ठा ib_uverbs_flow_mpls_filter     mask;
पूर्ण;

काष्ठा ib_uverbs_flow_attr अणु
	__u32 type;
	__u16 size;
	__u16 priority;
	__u8  num_of_specs;
	__u8  reserved[2];
	__u8  port;
	__u32 flags;
	/* Following are the optional layers according to user request
	 * काष्ठा ib_flow_spec_xxx
	 * काष्ठा ib_flow_spec_yyy
	 */
	काष्ठा ib_uverbs_flow_spec_hdr flow_specs[0];
पूर्ण;

काष्ठा ib_uverbs_create_flow  अणु
	__u32 comp_mask;
	__u32 qp_handle;
	काष्ठा ib_uverbs_flow_attr flow_attr;
पूर्ण;

काष्ठा ib_uverbs_create_flow_resp अणु
	__u32 comp_mask;
	__u32 flow_handle;
पूर्ण;

काष्ठा ib_uverbs_destroy_flow  अणु
	__u32 comp_mask;
	__u32 flow_handle;
पूर्ण;

काष्ठा ib_uverbs_create_srq अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 max_wr;
	__u32 max_sge;
	__u32 srq_limit;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_create_xsrq अणु
	__aligned_u64 response;
	__aligned_u64 user_handle;
	__u32 srq_type;
	__u32 pd_handle;
	__u32 max_wr;
	__u32 max_sge;
	__u32 srq_limit;
	__u32 max_num_tags;
	__u32 xrcd_handle;
	__u32 cq_handle;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_create_srq_resp अणु
	__u32 srq_handle;
	__u32 max_wr;
	__u32 max_sge;
	__u32 srqn;
	__u32 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_modअगरy_srq अणु
	__u32 srq_handle;
	__u32 attr_mask;
	__u32 max_wr;
	__u32 srq_limit;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_srq अणु
	__aligned_u64 response;
	__u32 srq_handle;
	__u32 reserved;
	__aligned_u64 driver_data[0];
पूर्ण;

काष्ठा ib_uverbs_query_srq_resp अणु
	__u32 max_wr;
	__u32 max_sge;
	__u32 srq_limit;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_destroy_srq अणु
	__aligned_u64 response;
	__u32 srq_handle;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_destroy_srq_resp अणु
	__u32 events_reported;
पूर्ण;

काष्ठा ib_uverbs_ex_create_wq  अणु
	__u32 comp_mask;
	__u32 wq_type;
	__aligned_u64 user_handle;
	__u32 pd_handle;
	__u32 cq_handle;
	__u32 max_wr;
	__u32 max_sge;
	__u32 create_flags; /* Use क्रमागत ib_wq_flags */
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_ex_create_wq_resp अणु
	__u32 comp_mask;
	__u32 response_length;
	__u32 wq_handle;
	__u32 max_wr;
	__u32 max_sge;
	__u32 wqn;
पूर्ण;

काष्ठा ib_uverbs_ex_destroy_wq  अणु
	__u32 comp_mask;
	__u32 wq_handle;
पूर्ण;

काष्ठा ib_uverbs_ex_destroy_wq_resp अणु
	__u32 comp_mask;
	__u32 response_length;
	__u32 events_reported;
	__u32 reserved;
पूर्ण;

काष्ठा ib_uverbs_ex_modअगरy_wq  अणु
	__u32 attr_mask;
	__u32 wq_handle;
	__u32 wq_state;
	__u32 curr_wq_state;
	__u32 flags; /* Use क्रमागत ib_wq_flags */
	__u32 flags_mask; /* Use क्रमागत ib_wq_flags */
पूर्ण;

/* Prevent memory allocation rather than max expected size */
#घोषणा IB_USER_VERBS_MAX_LOG_IND_TBL_SIZE 0x0d
काष्ठा ib_uverbs_ex_create_rwq_ind_table  अणु
	__u32 comp_mask;
	__u32 log_ind_tbl_size;
	/* Following are the wq handles according to log_ind_tbl_size
	 * wq_handle1
	 * wq_handle2
	 */
	__u32 wq_handles[0];
पूर्ण;

काष्ठा ib_uverbs_ex_create_rwq_ind_table_resp अणु
	__u32 comp_mask;
	__u32 response_length;
	__u32 ind_tbl_handle;
	__u32 ind_tbl_num;
पूर्ण;

काष्ठा ib_uverbs_ex_destroy_rwq_ind_table  अणु
	__u32 comp_mask;
	__u32 ind_tbl_handle;
पूर्ण;

काष्ठा ib_uverbs_cq_moderation अणु
	__u16 cq_count;
	__u16 cq_period;
पूर्ण;

काष्ठा ib_uverbs_ex_modअगरy_cq अणु
	__u32 cq_handle;
	__u32 attr_mask;
	काष्ठा ib_uverbs_cq_moderation attr;
	__u32 reserved;
पूर्ण;

#घोषणा IB_DEVICE_NAME_MAX 64

#पूर्ण_अगर /* IB_USER_VERBS_H */
