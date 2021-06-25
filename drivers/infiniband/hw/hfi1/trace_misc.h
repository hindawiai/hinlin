<शैली गुरु>
/*
* Copyright(c) 2015, 2016 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_MISC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_MISC_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_misc

TRACE_EVENT(hfi1_पूर्णांकerrupt,
	    TP_PROTO(काष्ठा hfi1_devdata *dd, स्थिर काष्ठा is_table *is_entry,
		     पूर्णांक src),
	    TP_ARGS(dd, is_entry, src),
	    TP_STRUCT__entry(DD_DEV_ENTRY(dd)
			     __array(अक्षर, buf, 64)
			     __field(पूर्णांक, src)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd)
			   is_entry->is_name(__entry->buf, 64,
					     src - is_entry->start);
			   __entry->src = src;
			   ),
	    TP_prपूर्णांकk("[%s] source: %s [%d]", __get_str(dev), __entry->buf,
		      __entry->src)
);

DECLARE_EVENT_CLASS(
	hfi1_csr_ढाँचा,
	TP_PROTO(व्योम __iomem *addr, u64 value),
	TP_ARGS(addr, value),
	TP_STRUCT__entry(
		__field(व्योम __iomem *, addr)
		__field(u64, value)
	),
	TP_fast_assign(
		__entry->addr = addr;
		__entry->value = value;
	),
	TP_prपूर्णांकk("addr %p value %llx", __entry->addr, __entry->value)
);

DEFINE_EVENT(
	hfi1_csr_ढाँचा, hfi1_ग_लिखो_rcvarray,
	TP_PROTO(व्योम __iomem *addr, u64 value),
	TP_ARGS(addr, value));

#अगर_घोषित CONFIG_FAULT_INJECTION
TRACE_EVENT(hfi1_fault_opcode,
	    TP_PROTO(काष्ठा rvt_qp *qp, u8 opcode),
	    TP_ARGS(qp, opcode),
	    TP_STRUCT__entry(DD_DEV_ENTRY(dd_from_ibdev(qp->ibqp.device))
			     __field(u32, qpn)
			     __field(u8, opcode)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd_from_ibdev(qp->ibqp.device))
			   __entry->qpn = qp->ibqp.qp_num;
			   __entry->opcode = opcode;
			   ),
	    TP_prपूर्णांकk("[%s] qpn 0x%x opcode 0x%x",
		      __get_str(dev), __entry->qpn, __entry->opcode)
);

TRACE_EVENT(hfi1_fault_packet,
	    TP_PROTO(काष्ठा hfi1_packet *packet),
	    TP_ARGS(packet),
	    TP_STRUCT__entry(DD_DEV_ENTRY(packet->rcd->ppd->dd)
			     __field(u64, eflags)
			     __field(u32, ctxt)
			     __field(u32, hlen)
			     __field(u32, tlen)
			     __field(u32, updegr)
			     __field(u32, etail)
			     ),
	     TP_fast_assign(DD_DEV_ASSIGN(packet->rcd->ppd->dd);
			    __entry->eflags = rhf_err_flags(packet->rhf);
			    __entry->ctxt = packet->rcd->ctxt;
			    __entry->hlen = packet->hlen;
			    __entry->tlen = packet->tlen;
			    __entry->updegr = packet->updegr;
			    __entry->etail = rhf_egr_index(packet->rhf);
			    ),
	     TP_prपूर्णांकk(
		"[%s] ctxt %d eflags 0x%llx hlen %d tlen %d updegr %d etail %d",
		__get_str(dev),
		__entry->ctxt,
		__entry->eflags,
		__entry->hlen,
		__entry->tlen,
		__entry->updegr,
		__entry->etail
		)
);
#पूर्ण_अगर

#पूर्ण_अगर /* __HFI1_TRACE_MISC_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_misc
#समावेश <trace/define_trace.h>
