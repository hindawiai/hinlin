<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */
#अगर !defined(__HFI1_TRACE_IOWAIT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_IOWAIT_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "iowait.h"
#समावेश "verbs.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_ioरुको

DECLARE_EVENT_CLASS(hfi1_ioरुको_ढाँचा,
		    TP_PROTO(काष्ठा ioरुको *रुको, u32 flag),
		    TP_ARGS(रुको, flag),
		    TP_STRUCT__entry(/* entry */
			    __field(अचिन्हित दीर्घ, addr)
			    __field(अचिन्हित दीर्घ, flags)
			    __field(u32, flag)
			    __field(u32, qpn)
			    ),
		    TP_fast_assign(/* assign */
			    __entry->addr = (अचिन्हित दीर्घ)रुको;
			    __entry->flags = रुको->flags;
			    __entry->flag = (1 << flag);
			    __entry->qpn = ioरुको_to_qp(रुको)->ibqp.qp_num;
			    ),
		    TP_prपूर्णांकk(/* prपूर्णांक */
			    "iowait 0x%lx qp %u flags 0x%lx flag 0x%x",
			    __entry->addr,
			    __entry->qpn,
			    __entry->flags,
			    __entry->flag
			    )
	);

DEFINE_EVENT(hfi1_ioरुको_ढाँचा, hfi1_ioरुको_set,
	     TP_PROTO(काष्ठा ioरुको *रुको, u32 flag),
	     TP_ARGS(रुको, flag));

DEFINE_EVENT(hfi1_ioरुको_ढाँचा, hfi1_ioरुको_clear,
	     TP_PROTO(काष्ठा ioरुको *रुको, u32 flag),
	     TP_ARGS(रुको, flag));

#पूर्ण_अगर /* __HFI1_TRACE_IOWAIT_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_ioरुको
#समावेश <trace/define_trace.h>
