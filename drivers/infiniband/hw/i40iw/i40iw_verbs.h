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

#अगर_अघोषित I40IW_VERBS_H
#घोषणा I40IW_VERBS_H

काष्ठा i40iw_ucontext अणु
	काष्ठा ib_ucontext ibucontext;
	काष्ठा i40iw_device *iwdev;
	काष्ठा list_head cq_reg_mem_list;
	spinlock_t cq_reg_mem_list_lock; /* memory list क्रम cq's */
	काष्ठा list_head qp_reg_mem_list;
	spinlock_t qp_reg_mem_list_lock; /* memory list क्रम qp's */
	पूर्णांक abi_ver;
पूर्ण;

काष्ठा i40iw_pd अणु
	काष्ठा ib_pd ibpd;
	काष्ठा i40iw_sc_pd sc_pd;
	atomic_t usecount;
पूर्ण;

काष्ठा i40iw_hmc_pble अणु
	जोड़ अणु
		u32 idx;
		dma_addr_t addr;
	पूर्ण;
पूर्ण;

काष्ठा i40iw_cq_mr अणु
	काष्ठा i40iw_hmc_pble cq_pbl;
	dma_addr_t shaकरोw;
पूर्ण;

काष्ठा i40iw_qp_mr अणु
	काष्ठा i40iw_hmc_pble sq_pbl;
	काष्ठा i40iw_hmc_pble rq_pbl;
	dma_addr_t shaकरोw;
	काष्ठा page *sq_page;
पूर्ण;

काष्ठा i40iw_pbl अणु
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा i40iw_qp_mr qp_mr;
		काष्ठा i40iw_cq_mr cq_mr;
	पूर्ण;

	bool pbl_allocated;
	bool on_list;
	u64 user_base;
	काष्ठा i40iw_pble_alloc pble_alloc;
	काष्ठा i40iw_mr *iwmr;
पूर्ण;

#घोषणा MAX_SAVE_PAGE_ADDRS     4
काष्ठा i40iw_mr अणु
	जोड़ अणु
		काष्ठा ib_mr ibmr;
		काष्ठा ib_mw ibmw;
	पूर्ण;
	काष्ठा ib_umem *region;
	u16 type;
	u32 page_cnt;
	u64 page_size;
	u32 npages;
	u32 stag;
	u64 length;
	u64 pgaddrmem[MAX_SAVE_PAGE_ADDRS];
	काष्ठा i40iw_pbl iwpbl;
पूर्ण;

काष्ठा i40iw_cq अणु
	काष्ठा ib_cq ibcq;
	काष्ठा i40iw_sc_cq sc_cq;
	u16 cq_head;
	u16 cq_size;
	u16 cq_number;
	bool user_mode;
	u32 polled_completions;
	u32 cq_mem_size;
	काष्ठा i40iw_dma_mem kmem;
	spinlock_t lock; /* क्रम poll cq */
	काष्ठा i40iw_pbl *iwpbl;
पूर्ण;

काष्ठा disconn_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा i40iw_qp *iwqp;
पूर्ण;

काष्ठा iw_cm_id;
काष्ठा ietf_mpa_frame;
काष्ठा i40iw_ud_file;

काष्ठा i40iw_qp_kmode अणु
	काष्ठा i40iw_dma_mem dma_mem;
	u64 *wrid_mem;
पूर्ण;

काष्ठा i40iw_qp अणु
	काष्ठा ib_qp ibqp;
	काष्ठा i40iw_sc_qp sc_qp;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_cq *iwscq;
	काष्ठा i40iw_cq *iwrcq;
	काष्ठा i40iw_pd *iwpd;
	काष्ठा i40iw_qp_host_ctx_info ctx_info;
	काष्ठा i40iwarp_offload_info iwarp_info;
	व्योम *allocated_buffer;
	refcount_t refcount;
	काष्ठा iw_cm_id *cm_id;
	व्योम *cm_node;
	काष्ठा ib_mr *lsmm_mr;
	काष्ठा work_काष्ठा work;
	क्रमागत ib_qp_state ibqp_state;
	u32 iwarp_state;
	u32 qp_mem_size;
	u32 last_aeq;
	atomic_t बंद_समयr_started;
	spinlock_t lock; /* क्रम post work requests */
	काष्ठा i40iw_qp_context *iwqp_context;
	व्योम *pbl_vbase;
	dma_addr_t pbl_pbase;
	काष्ठा page *page;
	u8 active_conn:1;
	u8 user_mode:1;
	u8 hte_added:1;
	u8 flush_issued:1;
	u8 destroyed:1;
	u8 sig_all:1;
	u8 pau_mode:1;
	u8 rsvd:1;
	u16 term_sq_flush_code;
	u16 term_rq_flush_code;
	u8 hw_iwarp_state;
	u8 hw_tcp_state;
	काष्ठा i40iw_qp_kmode kqp;
	काष्ठा i40iw_dma_mem host_ctx;
	काष्ठा समयr_list terminate_समयr;
	काष्ठा i40iw_pbl iwpbl;
	काष्ठा i40iw_dma_mem q2_ctx_mem;
	काष्ठा i40iw_dma_mem ietf_mem;
	काष्ठा completion sq_drained;
	काष्ठा completion rq_drained;
	काष्ठा completion मुक्त_qp;
पूर्ण;
#पूर्ण_अगर
