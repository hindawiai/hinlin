<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
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
#अगर !defined(__RVT_TRACE_RVT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __RVT_TRACE_RVT_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_vt.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rvt

TRACE_EVENT(rvt_dbg,
	TP_PROTO(काष्ठा rvt_dev_info *rdi,
		 स्थिर अक्षर *msg),
	TP_ARGS(rdi, msg),
	TP_STRUCT__entry(
		RDI_DEV_ENTRY(rdi)
		__string(msg, msg)
	),
	TP_fast_assign(
		RDI_DEV_ASSIGN(rdi);
		__assign_str(msg, msg);
	),
	TP_prपूर्णांकk("[%s]: %s", __get_str(dev), __get_str(msg))
);

#पूर्ण_अगर /* __RVT_TRACE_MISC_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_rvt
#समावेश <trace/define_trace.h>

