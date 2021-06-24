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
#अगर !defined(__HFI1_TRACE_EXTRA_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_EXTRA_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

/*
 * Note:
 * This produces a REALLY ugly trace in the console output when the string is
 * too दीर्घ.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_dbg

#घोषणा MAX_MSG_LEN 512

DECLARE_EVENT_CLASS(hfi1_trace_ढाँचा,
		    TP_PROTO(स्थिर अक्षर *function, काष्ठा va_क्रमmat *vaf),
		    TP_ARGS(function, vaf),
		    TP_STRUCT__entry(__string(function, function)
				     __dynamic_array(अक्षर, msg, MAX_MSG_LEN)
				     ),
		    TP_fast_assign(__assign_str(function, function);
				   WARN_ON_ONCE(vsnम_लिखो
						(__get_dynamic_array(msg),
						 MAX_MSG_LEN, vaf->fmt,
						 *vaf->va) >=
						MAX_MSG_LEN);
				   ),
		    TP_prपूर्णांकk("(%s) %s",
			      __get_str(function),
			      __get_str(msg))
);

/*
 * It may be nice to macroize the __hfi1_trace but the va_* stuff requires an
 * actual function to work and can not be in a macro.
 */
#घोषणा __hfi1_trace_def(lvl) \
व्योम __म_लिखो(2, 3) __hfi1_trace_##lvl(स्थिर अक्षर *funct, अक्षर *fmt, ...); \
									\
DEFINE_EVENT(hfi1_trace_ढाँचा, hfi1_ ##lvl,				\
	TP_PROTO(स्थिर अक्षर *function, काष्ठा va_क्रमmat *vaf),		\
	TP_ARGS(function, vaf))

#घोषणा __hfi1_trace_fn(lvl) \
व्योम __म_लिखो(2, 3) __hfi1_trace_##lvl(स्थिर अक्षर *func, अक्षर *fmt, ...)\
अणु									\
	काष्ठा va_क्रमmat vaf = अणु					\
		.fmt = fmt,						\
	पूर्ण;								\
	बहु_सूची args;							\
									\
	बहु_शुरू(args, fmt);						\
	vaf.va = &args;							\
	trace_hfi1_ ##lvl(func, &vaf);					\
	बहु_पूर्ण(args);							\
	वापस;								\
पूर्ण

/*
 * To create a new trace level simply define it below and as a __hfi1_trace_fn
 * in trace.c. This will create all the hooks क्रम calling
 * hfi1_cdbg(LVL, fmt, ...); as well as take care of all
 * the debugfs stuff.
 */
__hfi1_trace_def(AFFINITY);
__hfi1_trace_def(PKT);
__hfi1_trace_def(PROC);
__hfi1_trace_def(SDMA);
__hfi1_trace_def(LINKVERB);
__hfi1_trace_def(DEBUG);
__hfi1_trace_def(SNOOP);
__hfi1_trace_def(CNTR);
__hfi1_trace_def(PIO);
__hfi1_trace_def(DC8051);
__hfi1_trace_def(FIRMWARE);
__hfi1_trace_def(RCVCTRL);
__hfi1_trace_def(TID);
__hfi1_trace_def(MMU);
__hfi1_trace_def(IOCTL);

#घोषणा hfi1_cdbg(which, fmt, ...) \
	__hfi1_trace_##which(__func__, fmt, ##__VA_ARGS__)

#घोषणा hfi1_dbg(fmt, ...) \
	hfi1_cdbg(DEBUG, fmt, ##__VA_ARGS__)

/*
 * Define HFI1_EARLY_DBG at compile समय or here to enable early trace
 * messages. Do not check in an enablement क्रम this.
 */

#अगर_घोषित HFI1_EARLY_DBG
#घोषणा hfi1_dbg_early(fmt, ...) \
	trace_prपूर्णांकk(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा hfi1_dbg_early(fmt, ...)
#पूर्ण_अगर

#पूर्ण_अगर /* __HFI1_TRACE_EXTRA_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_dbg
#समावेश <trace/define_trace.h>
