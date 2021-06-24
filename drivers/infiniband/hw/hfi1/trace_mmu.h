<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_MMU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_MMU_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_mmu

DECLARE_EVENT_CLASS(hfi1_mmu_rb_ढाँचा,
		    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len),
		    TP_ARGS(addr, len),
		    TP_STRUCT__entry(__field(अचिन्हित दीर्घ, addr)
				     __field(अचिन्हित दीर्घ, len)
			    ),
		    TP_fast_assign(__entry->addr = addr;
				   __entry->len = len;
			    ),
		    TP_prपूर्णांकk("MMU node addr 0x%lx, len %lu",
			      __entry->addr,
			      __entry->len
			    )
);

DEFINE_EVENT(hfi1_mmu_rb_ढाँचा, hfi1_mmu_rb_insert,
	     TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len),
	     TP_ARGS(addr, len));

DEFINE_EVENT(hfi1_mmu_rb_ढाँचा, hfi1_mmu_rb_search,
	     TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len),
	     TP_ARGS(addr, len));

DEFINE_EVENT(hfi1_mmu_rb_ढाँचा, hfi1_mmu_rb_हटाओ,
	     TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len),
	     TP_ARGS(addr, len));

DEFINE_EVENT(hfi1_mmu_rb_ढाँचा, hfi1_mmu_mem_invalidate,
	     TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len),
	     TP_ARGS(addr, len));

#पूर्ण_अगर /* __HFI1_TRACE_RC_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_mmu
#समावेश <trace/define_trace.h>
