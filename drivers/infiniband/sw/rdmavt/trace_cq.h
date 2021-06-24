<शैली गुरु>
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#अगर !defined(__RVT_TRACE_CQ_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __RVT_TRACE_CQ_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdmavt_cq.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rvt_cq

#घोषणा wc_opcode_name(opcode) अणु IB_WC_##opcode, #opcode  पूर्ण
#घोषणा show_wc_opcode(opcode)                                \
__prपूर्णांक_symbolic(opcode,                                      \
	wc_opcode_name(SEND),                                 \
	wc_opcode_name(RDMA_WRITE),                           \
	wc_opcode_name(RDMA_READ),                            \
	wc_opcode_name(COMP_SWAP),                            \
	wc_opcode_name(FETCH_ADD),                            \
	wc_opcode_name(LSO),                                  \
	wc_opcode_name(LOCAL_INV),                            \
	wc_opcode_name(REG_MR),                               \
	wc_opcode_name(MASKED_COMP_SWAP),                     \
	wc_opcode_name(RECV),                                 \
	wc_opcode_name(RECV_RDMA_WITH_IMM))

#घोषणा CQ_ATTR_PRINT \
"[%s] user cq %s cqe %u comp_vector %d comp_vector_cpu %d flags %x"

DECLARE_EVENT_CLASS(rvt_cq_ढाँचा,
		    TP_PROTO(काष्ठा rvt_cq *cq,
			     स्थिर काष्ठा ib_cq_init_attr *attr),
		    TP_ARGS(cq, attr),
		    TP_STRUCT__entry(RDI_DEV_ENTRY(cq->rdi)
				     __field(काष्ठा rvt_mmap_info *, ip)
				     __field(अचिन्हित पूर्णांक, cqe)
				     __field(पूर्णांक, comp_vector)
				     __field(पूर्णांक, comp_vector_cpu)
				     __field(u32, flags)
				     ),
		    TP_fast_assign(RDI_DEV_ASSIGN(cq->rdi)
				   __entry->ip = cq->ip;
				   __entry->cqe = attr->cqe;
				   __entry->comp_vector = attr->comp_vector;
				   __entry->comp_vector_cpu =
							cq->comp_vector_cpu;
				   __entry->flags = attr->flags;
				   ),
		    TP_prपूर्णांकk(CQ_ATTR_PRINT, __get_str(dev),
			      __entry->ip ? "true" : "false", __entry->cqe,
			      __entry->comp_vector, __entry->comp_vector_cpu,
			      __entry->flags
			      )
);

DEFINE_EVENT(rvt_cq_ढाँचा, rvt_create_cq,
	     TP_PROTO(काष्ठा rvt_cq *cq, स्थिर काष्ठा ib_cq_init_attr *attr),
	     TP_ARGS(cq, attr));

#घोषणा CQ_PRN \
"[%s] idx %u wr_id %llx status %u opcode %u,%s length %u qpn %x flags %x imm %x"

DECLARE_EVENT_CLASS(
	rvt_cq_entry_ढाँचा,
	TP_PROTO(काष्ठा rvt_cq *cq, काष्ठा ib_wc *wc, u32 idx),
	TP_ARGS(cq, wc, idx),
	TP_STRUCT__entry(
		RDI_DEV_ENTRY(cq->rdi)
		__field(u64, wr_id)
		__field(u32, status)
		__field(u32, opcode)
		__field(u32, qpn)
		__field(u32, length)
		__field(u32, idx)
		__field(u32, flags)
		__field(u32, imm)
	),
	TP_fast_assign(
		RDI_DEV_ASSIGN(cq->rdi)
		__entry->wr_id = wc->wr_id;
		__entry->status = wc->status;
		__entry->opcode = wc->opcode;
		__entry->length = wc->byte_len;
		__entry->qpn = wc->qp->qp_num;
		__entry->idx = idx;
		__entry->flags = wc->wc_flags;
		__entry->imm = be32_to_cpu(wc->ex.imm_data);
	),
	TP_prपूर्णांकk(
		CQ_PRN,
		__get_str(dev),
		__entry->idx,
		__entry->wr_id,
		__entry->status,
		__entry->opcode, show_wc_opcode(__entry->opcode),
		__entry->length,
		__entry->qpn,
		__entry->flags,
		__entry->imm
	)
);

DEFINE_EVENT(
	rvt_cq_entry_ढाँचा, rvt_cq_enter,
	TP_PROTO(काष्ठा rvt_cq *cq, काष्ठा ib_wc *wc, u32 idx),
	TP_ARGS(cq, wc, idx));

DEFINE_EVENT(
	rvt_cq_entry_ढाँचा, rvt_cq_poll,
	TP_PROTO(काष्ठा rvt_cq *cq, काष्ठा ib_wc *wc, u32 idx),
	TP_ARGS(cq, wc, idx));

#पूर्ण_अगर /* __RVT_TRACE_CQ_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_cq
#समावेश <trace/define_trace.h>
