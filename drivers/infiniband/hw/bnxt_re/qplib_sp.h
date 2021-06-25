<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Slow Path Operators (header)
 *
 */

#अगर_अघोषित __BNXT_QPLIB_SP_H__
#घोषणा __BNXT_QPLIB_SP_H__

#घोषणा BNXT_QPLIB_RESERVED_QP_WRS	128

#घोषणा PCI_EXP_DEVCTL2_ATOMIC_REQ      0x0040

काष्ठा bnxt_qplib_dev_attr अणु
#घोषणा FW_VER_ARR_LEN			4
	u8				fw_ver[FW_VER_ARR_LEN];
#घोषणा BNXT_QPLIB_NUM_GIDS_SUPPORTED	256
	u16				max_sgid;
	u16				max_mrw;
	u32				max_qp;
#घोषणा BNXT_QPLIB_MAX_OUT_RD_ATOM	126
	u32				max_qp_rd_atom;
	u32				max_qp_init_rd_atom;
	u32				max_qp_wqes;
	u32				max_qp_sges;
	u32				max_cq;
	u32				max_cq_wqes;
	u32				max_cq_sges;
	u32				max_mr;
	u64				max_mr_size;
	u32				max_pd;
	u32				max_mw;
	u32				max_raw_ethy_qp;
	u32				max_ah;
	u32				max_srq;
	u32				max_srq_wqes;
	u32				max_srq_sges;
	u32				max_pkey;
	u32				max_अंतरभूत_data;
	u32				l2_db_size;
	u8				tqm_alloc_reqs[MAX_TQM_ALLOC_REQ];
	bool				is_atomic;
पूर्ण;

काष्ठा bnxt_qplib_pd अणु
	u32				id;
पूर्ण;

काष्ठा bnxt_qplib_gid अणु
	u8				data[16];
पूर्ण;

काष्ठा bnxt_qplib_gid_info अणु
	काष्ठा bnxt_qplib_gid gid;
	u16 vlan_id;
पूर्ण;

काष्ठा bnxt_qplib_ah अणु
	काष्ठा bnxt_qplib_gid		dgid;
	काष्ठा bnxt_qplib_pd		*pd;
	u32				id;
	u8				sgid_index;
	/* For Query AH अगर the hw table and SW table are dअगरfernt */
	u8				host_sgid_index;
	u8				traffic_class;
	u32				flow_label;
	u8				hop_limit;
	u8				sl;
	u8				dmac[6];
	u16				vlan_id;
	u8				nw_type;
पूर्ण;

काष्ठा bnxt_qplib_mrw अणु
	काष्ठा bnxt_qplib_pd		*pd;
	पूर्णांक				type;
	u32				flags;
#घोषणा BNXT_QPLIB_FR_PMR		0x80000000
	u32				lkey;
	u32				rkey;
#घोषणा BNXT_QPLIB_RSVD_LKEY		0xFFFFFFFF
	u64				va;
	u64				total_size;
	u32				npages;
	u64				mr_handle;
	काष्ठा bnxt_qplib_hwq		hwq;
पूर्ण;

काष्ठा bnxt_qplib_frpl अणु
	पूर्णांक				max_pg_ptrs;
	काष्ठा bnxt_qplib_hwq		hwq;
पूर्ण;

#घोषणा BNXT_QPLIB_ACCESS_LOCAL_WRITE	BIT(0)
#घोषणा BNXT_QPLIB_ACCESS_REMOTE_READ	BIT(1)
#घोषणा BNXT_QPLIB_ACCESS_REMOTE_WRITE	BIT(2)
#घोषणा BNXT_QPLIB_ACCESS_REMOTE_ATOMIC	BIT(3)
#घोषणा BNXT_QPLIB_ACCESS_MW_BIND	BIT(4)
#घोषणा BNXT_QPLIB_ACCESS_ZERO_BASED	BIT(5)
#घोषणा BNXT_QPLIB_ACCESS_ON_DEMAND	BIT(6)

काष्ठा bnxt_qplib_roce_stats अणु
	u64 to_retransmits;
	u64 seq_err_naks_rcvd;
	/* seq_err_naks_rcvd is 64 b */
	u64 max_retry_exceeded;
	/* max_retry_exceeded is 64 b */
	u64 rnr_naks_rcvd;
	/* rnr_naks_rcvd is 64 b */
	u64 missing_resp;
	u64 unrecoverable_err;
	/* unrecoverable_err is 64 b */
	u64 bad_resp_err;
	/* bad_resp_err is 64 b */
	u64 local_qp_op_err;
	/* local_qp_op_err is 64 b */
	u64 local_protection_err;
	/* local_protection_err is 64 b */
	u64 mem_mgmt_op_err;
	/* mem_mgmt_op_err is 64 b */
	u64 remote_invalid_req_err;
	/* remote_invalid_req_err is 64 b */
	u64 remote_access_err;
	/* remote_access_err is 64 b */
	u64 remote_op_err;
	/* remote_op_err is 64 b */
	u64 dup_req;
	/* dup_req is 64 b */
	u64 res_exceed_max;
	/* res_exceed_max is 64 b */
	u64 res_length_mismatch;
	/* res_length_mismatch is 64 b */
	u64 res_exceeds_wqe;
	/* res_exceeds_wqe is 64 b */
	u64 res_opcode_err;
	/* res_opcode_err is 64 b */
	u64 res_rx_invalid_rkey;
	/* res_rx_invalid_rkey is 64 b */
	u64 res_rx_करोमुख्य_err;
	/* res_rx_करोमुख्य_err is 64 b */
	u64 res_rx_no_perm;
	/* res_rx_no_perm is 64 b */
	u64 res_rx_range_err;
	/* res_rx_range_err is 64 b */
	u64 res_tx_invalid_rkey;
	/* res_tx_invalid_rkey is 64 b */
	u64 res_tx_करोमुख्य_err;
	/* res_tx_करोमुख्य_err is 64 b */
	u64 res_tx_no_perm;
	/* res_tx_no_perm is 64 b */
	u64 res_tx_range_err;
	/* res_tx_range_err is 64 b */
	u64 res_irrq_oflow;
	/* res_irrq_oflow is 64 b */
	u64 res_unsup_opcode;
	/* res_unsup_opcode is 64 b */
	u64 res_unaligned_atomic;
	/* res_unaligned_atomic is 64 b */
	u64 res_rem_inv_err;
	/* res_rem_inv_err is 64 b */
	u64 res_mem_error;
	/* res_mem_error is 64 b */
	u64 res_srq_err;
	/* res_srq_err is 64 b */
	u64 res_cmp_err;
	/* res_cmp_err is 64 b */
	u64 res_invalid_dup_rkey;
	/* res_invalid_dup_rkey is 64 b */
	u64 res_wqe_क्रमmat_err;
	/* res_wqe_क्रमmat_err is 64 b */
	u64 res_cq_load_err;
	/* res_cq_load_err is 64 b */
	u64 res_srq_load_err;
	/* res_srq_load_err is 64 b */
	u64 res_tx_pci_err;
	/* res_tx_pci_err is 64 b */
	u64 res_rx_pci_err;
	/* res_rx_pci_err is 64 b */
	u64 res_oos_drop_count;
	/* res_oos_drop_count */
	u64     active_qp_count_p0;
	/* port 0 active qps */
	u64     active_qp_count_p1;
	/* port 1 active qps */
	u64     active_qp_count_p2;
	/* port 2 active qps */
	u64     active_qp_count_p3;
	/* port 3 active qps */
पूर्ण;

पूर्णांक bnxt_qplib_get_sgid(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl, पूर्णांक index,
			काष्ठा bnxt_qplib_gid *gid);
पूर्णांक bnxt_qplib_del_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			काष्ठा bnxt_qplib_gid *gid, u16 vlan_id, bool update);
पूर्णांक bnxt_qplib_add_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			काष्ठा bnxt_qplib_gid *gid, u8 *mac, u16 vlan_id,
			bool update, u32 *index);
पूर्णांक bnxt_qplib_update_sgid(काष्ठा bnxt_qplib_sgid_tbl *sgid_tbl,
			   काष्ठा bnxt_qplib_gid *gid, u16 gid_idx, u8 *smac);
पूर्णांक bnxt_qplib_get_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 index,
			u16 *pkey);
पूर्णांक bnxt_qplib_del_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 *pkey,
			bool update);
पूर्णांक bnxt_qplib_add_pkey(काष्ठा bnxt_qplib_res *res,
			काष्ठा bnxt_qplib_pkey_tbl *pkey_tbl, u16 *pkey,
			bool update);
पूर्णांक bnxt_qplib_get_dev_attr(काष्ठा bnxt_qplib_rcfw *rcfw,
			    काष्ठा bnxt_qplib_dev_attr *attr, bool vf);
पूर्णांक bnxt_qplib_set_func_resources(काष्ठा bnxt_qplib_res *res,
				  काष्ठा bnxt_qplib_rcfw *rcfw,
				  काष्ठा bnxt_qplib_ctx *ctx);
पूर्णांक bnxt_qplib_create_ah(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_ah *ah,
			 bool block);
व्योम bnxt_qplib_destroy_ah(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_ah *ah,
			   bool block);
पूर्णांक bnxt_qplib_alloc_mrw(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_mrw *mrw);
पूर्णांक bnxt_qplib_dereg_mrw(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mrw,
			 bool block);
पूर्णांक bnxt_qplib_reg_mr(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mr,
		      काष्ठा ib_umem *umem, पूर्णांक num_pbls, u32 buf_pg_size);
पूर्णांक bnxt_qplib_मुक्त_mrw(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_mrw *mr);
पूर्णांक bnxt_qplib_alloc_fast_reg_mr(काष्ठा bnxt_qplib_res *res,
				 काष्ठा bnxt_qplib_mrw *mr, पूर्णांक max);
पूर्णांक bnxt_qplib_alloc_fast_reg_page_list(काष्ठा bnxt_qplib_res *res,
					काष्ठा bnxt_qplib_frpl *frpl, पूर्णांक max);
पूर्णांक bnxt_qplib_मुक्त_fast_reg_page_list(काष्ठा bnxt_qplib_res *res,
				       काष्ठा bnxt_qplib_frpl *frpl);
पूर्णांक bnxt_qplib_map_tc2cos(काष्ठा bnxt_qplib_res *res, u16 *cids);
पूर्णांक bnxt_qplib_get_roce_stats(काष्ठा bnxt_qplib_rcfw *rcfw,
			      काष्ठा bnxt_qplib_roce_stats *stats);
#पूर्ण_अगर /* __BNXT_QPLIB_SP_H__*/
