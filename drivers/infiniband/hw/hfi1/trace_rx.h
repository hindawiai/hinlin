<शैली गुरु>
/*
 * Copyright(c) 2015 - 2018 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_RX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_RX_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#घोषणा tidtype_name(type) अणु PT_##type, #type पूर्ण
#घोषणा show_tidtype(type)                   \
__prपूर्णांक_symbolic(type,                       \
	tidtype_name(EXPECTED),              \
	tidtype_name(EAGER),                 \
	tidtype_name(INVALID))               \

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_rx

TRACE_EVENT(hfi1_rcvhdr,
	    TP_PROTO(काष्ठा hfi1_packet *packet),
	    TP_ARGS(packet),
	    TP_STRUCT__entry(DD_DEV_ENTRY(packet->rcd->dd)
			     __field(u64, eflags)
			     __field(u32, ctxt)
			     __field(u32, etype)
			     __field(u32, hlen)
			     __field(u32, tlen)
			     __field(u32, updegr)
			     __field(u32, etail)
			     ),
	     TP_fast_assign(DD_DEV_ASSIGN(packet->rcd->dd);
			    __entry->eflags = rhf_err_flags(packet->rhf);
			    __entry->ctxt = packet->rcd->ctxt;
			    __entry->etype = packet->etype;
			    __entry->hlen = packet->hlen;
			    __entry->tlen = packet->tlen;
			    __entry->updegr = packet->updegr;
			    __entry->etail = rhf_egr_index(packet->rhf);
			    ),
	     TP_prपूर्णांकk(
		"[%s] ctxt %d eflags 0x%llx etype %d,%s hlen %d tlen %d updegr %d etail %d",
		__get_str(dev),
		__entry->ctxt,
		__entry->eflags,
		__entry->etype, show_packettype(__entry->etype),
		__entry->hlen,
		__entry->tlen,
		__entry->updegr,
		__entry->etail
		)
);

TRACE_EVENT(hfi1_receive_पूर्णांकerrupt,
	    TP_PROTO(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd),
	    TP_ARGS(dd, rcd),
	    TP_STRUCT__entry(DD_DEV_ENTRY(dd)
			     __field(u32, ctxt)
			     __field(u8, slow_path)
			     __field(u8, dma_rtail)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			__entry->ctxt = rcd->ctxt;
			__entry->slow_path = hfi1_is_slowpath(rcd);
			__entry->dma_rtail = get_dma_rtail_setting(rcd);
			),
	    TP_prपूर्णांकk("[%s] ctxt %d SlowPath: %d DmaRtail: %d",
		      __get_str(dev),
		      __entry->ctxt,
		      __entry->slow_path,
		      __entry->dma_rtail
		      )
);

TRACE_EVENT(hfi1_mmu_invalidate,
	    TP_PROTO(अचिन्हित पूर्णांक ctxt, u16 subctxt, स्थिर अक्षर *type,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end),
	    TP_ARGS(ctxt, subctxt, type, start, end),
	    TP_STRUCT__entry(
			     __field(अचिन्हित पूर्णांक, ctxt)
			     __field(u16, subctxt)
			     __string(type, type)
			     __field(अचिन्हित दीर्घ, start)
			     __field(अचिन्हित दीर्घ, end)
			     ),
	    TP_fast_assign(
			__entry->ctxt = ctxt;
			__entry->subctxt = subctxt;
			__assign_str(type, type);
			__entry->start = start;
			__entry->end = end;
	    ),
	    TP_prपूर्णांकk("[%3u:%02u] MMU Invalidate (%s) 0x%lx - 0x%lx",
		      __entry->ctxt,
		      __entry->subctxt,
		      __get_str(type),
		      __entry->start,
		      __entry->end
		      )
	    );

#पूर्ण_अगर /* __HFI1_TRACE_RX_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_rx
#समावेश <trace/define_trace.h>
