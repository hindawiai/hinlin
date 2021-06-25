<शैली गुरु>
/*
* Copyright(c) 2015, 2016, 2017 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_RC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_RC_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_rc

DECLARE_EVENT_CLASS(hfi1_rc_ढाँचा,
		    TP_PROTO(काष्ठा rvt_qp *qp, u32 psn),
		    TP_ARGS(qp, psn),
		    TP_STRUCT__entry(
			DD_DEV_ENTRY(dd_from_ibdev(qp->ibqp.device))
			__field(u32, qpn)
			__field(u32, s_flags)
			__field(u32, psn)
			__field(u32, s_psn)
			__field(u32, s_next_psn)
			__field(u32, s_sending_psn)
			__field(u32, s_sending_hpsn)
			__field(u32, r_psn)
			),
		    TP_fast_assign(
			DD_DEV_ASSIGN(dd_from_ibdev(qp->ibqp.device))
			__entry->qpn = qp->ibqp.qp_num;
			__entry->s_flags = qp->s_flags;
			__entry->psn = psn;
			__entry->s_psn = qp->s_psn;
			__entry->s_next_psn = qp->s_next_psn;
			__entry->s_sending_psn = qp->s_sending_psn;
			__entry->s_sending_hpsn = qp->s_sending_hpsn;
			__entry->r_psn = qp->r_psn;
			),
		    TP_prपूर्णांकk(
			"[%s] qpn 0x%x s_flags 0x%x psn 0x%x s_psn 0x%x s_next_psn 0x%x s_sending_psn 0x%x sending_hpsn 0x%x r_psn 0x%x",
			__get_str(dev),
			__entry->qpn,
			__entry->s_flags,
			__entry->psn,
			__entry->s_psn,
			__entry->s_next_psn,
			__entry->s_sending_psn,
			__entry->s_sending_hpsn,
			__entry->r_psn
			)
);

DEFINE_EVENT(hfi1_rc_ढाँचा, hfi1_sendcomplete,
	     TP_PROTO(काष्ठा rvt_qp *qp, u32 psn),
	     TP_ARGS(qp, psn)
);

DEFINE_EVENT(hfi1_rc_ढाँचा, hfi1_ack,
	     TP_PROTO(काष्ठा rvt_qp *qp, u32 psn),
	     TP_ARGS(qp, psn)
);

DEFINE_EVENT(hfi1_rc_ढाँचा, hfi1_rcv_error,
	     TP_PROTO(काष्ठा rvt_qp *qp, u32 psn),
	     TP_ARGS(qp, psn)
);

DEFINE_EVENT(/* event */
	hfi1_rc_ढाँचा, hfi1_rc_completion,
	TP_PROTO(काष्ठा rvt_qp *qp, u32 psn),
	TP_ARGS(qp, psn)
);

DECLARE_EVENT_CLASS(/* rc_ack */
	hfi1_rc_ack_ढाँचा,
	TP_PROTO(काष्ठा rvt_qp *qp, u32 aeth, u32 psn,
		 काष्ठा rvt_swqe *wqe),
	TP_ARGS(qp, aeth, psn, wqe),
	TP_STRUCT__entry(/* entry */
		DD_DEV_ENTRY(dd_from_ibdev(qp->ibqp.device))
		__field(u32, qpn)
		__field(u32, aeth)
		__field(u32, psn)
		__field(u8, opcode)
		__field(u32, spsn)
		__field(u32, lpsn)
	),
	TP_fast_assign(/* assign */
		DD_DEV_ASSIGN(dd_from_ibdev(qp->ibqp.device))
		__entry->qpn = qp->ibqp.qp_num;
		__entry->aeth = aeth;
		__entry->psn = psn;
		__entry->opcode = wqe->wr.opcode;
		__entry->spsn = wqe->psn;
		__entry->lpsn = wqe->lpsn;
	),
	TP_prपूर्णांकk(/* prपूर्णांक */
		"[%s] qpn 0x%x aeth 0x%x psn 0x%x opcode 0x%x spsn 0x%x lpsn 0x%x",
		__get_str(dev),
		__entry->qpn,
		__entry->aeth,
		__entry->psn,
		__entry->opcode,
		__entry->spsn,
		__entry->lpsn
	)
);

DEFINE_EVENT(/* करो_rc_ack */
	hfi1_rc_ack_ढाँचा, hfi1_rc_ack_करो,
	TP_PROTO(काष्ठा rvt_qp *qp, u32 aeth, u32 psn,
		 काष्ठा rvt_swqe *wqe),
	TP_ARGS(qp, aeth, psn, wqe)
);

#पूर्ण_अगर /* __HFI1_TRACE_RC_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_rc
#समावेश <trace/define_trace.h>
