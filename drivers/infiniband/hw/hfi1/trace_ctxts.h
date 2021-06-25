<शैली गुरु>
/*
* Copyright(c) 2015 - 2020 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_CTXTS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_CTXTS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_ctxts

#घोषणा UCTXT_FMT \
	"cred:%u, credaddr:0x%llx, piobase:0x%p, rcvhdr_cnt:%u, "	\
	"rcvbase:0x%llx, rcvegrc:%u, rcvegrb:0x%llx, subctxt_cnt:%u"
TRACE_EVENT(hfi1_uctxtdata,
	    TP_PROTO(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *uctxt,
		     अचिन्हित पूर्णांक subctxt),
	    TP_ARGS(dd, uctxt, subctxt),
	    TP_STRUCT__entry(DD_DEV_ENTRY(dd)
			     __field(अचिन्हित पूर्णांक, ctxt)
			     __field(अचिन्हित पूर्णांक, subctxt)
			     __field(u32, credits)
			     __field(u64, hw_मुक्त)
			     __field(व्योम __iomem *, piobase)
			     __field(u16, rcvhdrq_cnt)
			     __field(u64, rcvhdrq_dma)
			     __field(u32, eager_cnt)
			     __field(u64, rcvegr_dma)
			     __field(अचिन्हित पूर्णांक, subctxt_cnt)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			   __entry->ctxt = uctxt->ctxt;
			   __entry->subctxt = subctxt;
			   __entry->credits = uctxt->sc->credits;
			   __entry->hw_मुक्त = le64_to_cpu(*uctxt->sc->hw_मुक्त);
			   __entry->piobase = uctxt->sc->base_addr;
			   __entry->rcvhdrq_cnt = get_hdrq_cnt(uctxt);
			   __entry->rcvhdrq_dma = uctxt->rcvhdrq_dma;
			   __entry->eager_cnt = uctxt->egrbufs.alloced;
			   __entry->rcvegr_dma = uctxt->egrbufs.rcvtids[0].dma;
			   __entry->subctxt_cnt = uctxt->subctxt_cnt;
			   ),
	    TP_prपूर्णांकk("[%s] ctxt %u:%u " UCTXT_FMT,
		      __get_str(dev),
		      __entry->ctxt,
		      __entry->subctxt,
		      __entry->credits,
		      __entry->hw_मुक्त,
		      __entry->piobase,
		      __entry->rcvhdrq_cnt,
		      __entry->rcvhdrq_dma,
		      __entry->eager_cnt,
		      __entry->rcvegr_dma,
		      __entry->subctxt_cnt
		      )
);

#घोषणा CINFO_FMT \
	"egrtids:%u, egr_size:%u, hdrq_cnt:%u, hdrq_size:%u, sdma_ring_size:%u"
TRACE_EVENT(hfi1_ctxt_info,
	    TP_PROTO(काष्ठा hfi1_devdata *dd, अचिन्हित पूर्णांक ctxt,
		     अचिन्हित पूर्णांक subctxt,
		     काष्ठा hfi1_ctxt_info *cinfo),
	    TP_ARGS(dd, ctxt, subctxt, cinfo),
	    TP_STRUCT__entry(DD_DEV_ENTRY(dd)
			     __field(अचिन्हित पूर्णांक, ctxt)
			     __field(अचिन्हित पूर्णांक, subctxt)
			     __field(u16, egrtids)
			     __field(u16, rcvhdrq_cnt)
			     __field(u16, rcvhdrq_size)
			     __field(u16, sdma_ring_size)
			     __field(u32, rcvegr_size)
			     ),
	    TP_fast_assign(DD_DEV_ASSIGN(dd);
			    __entry->ctxt = ctxt;
			    __entry->subctxt = subctxt;
			    __entry->egrtids = cinfo->egrtids;
			    __entry->rcvhdrq_cnt = cinfo->rcvhdrq_cnt;
			    __entry->rcvhdrq_size = cinfo->rcvhdrq_entsize;
			    __entry->sdma_ring_size = cinfo->sdma_ring_size;
			    __entry->rcvegr_size = cinfo->rcvegr_size;
			    ),
	    TP_prपूर्णांकk("[%s] ctxt %u:%u " CINFO_FMT,
		      __get_str(dev),
		      __entry->ctxt,
		      __entry->subctxt,
		      __entry->egrtids,
		      __entry->rcvegr_size,
		      __entry->rcvhdrq_cnt,
		      __entry->rcvhdrq_size,
		      __entry->sdma_ring_size
		      )
);

स्थिर अक्षर *hfi1_trace_prपूर्णांक_rsm_hist(काष्ठा trace_seq *p, अचिन्हित पूर्णांक ctxt);
TRACE_EVENT(ctxt_rsm_hist,
	    TP_PROTO(अचिन्हित पूर्णांक ctxt),
	    TP_ARGS(ctxt),
	    TP_STRUCT__entry(__field(अचिन्हित पूर्णांक, ctxt)),
	    TP_fast_assign(__entry->ctxt = ctxt;),
	    TP_prपूर्णांकk("%s", hfi1_trace_prपूर्णांक_rsm_hist(p, __entry->ctxt))
);

#पूर्ण_अगर /* __HFI1_TRACE_CTXTS_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_ctxts
#समावेश <trace/define_trace.h>
