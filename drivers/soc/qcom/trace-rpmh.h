<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर !defined(_TRACE_RPMH_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RPMH_H

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rpmh

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "rpmh-internal.h"

TRACE_EVENT(rpmh_tx_करोne,

	TP_PROTO(काष्ठा rsc_drv *d, पूर्णांक m, स्थिर काष्ठा tcs_request *r, पूर्णांक e),

	TP_ARGS(d, m, r, e),

	TP_STRUCT__entry(
			 __string(name, d->name)
			 __field(पूर्णांक, m)
			 __field(u32, addr)
			 __field(u32, data)
			 __field(पूर्णांक, err)
	),

	TP_fast_assign(
		       __assign_str(name, d->name);
		       __entry->m = m;
		       __entry->addr = r->cmds[0].addr;
		       __entry->data = r->cmds[0].data;
		       __entry->err = e;
	),

	TP_prपूर्णांकk("%s: ack: tcs-m: %d addr: %#x data: %#x errno: %d",
		  __get_str(name), __entry->m, __entry->addr, __entry->data,
		  __entry->err)
);

TRACE_EVENT(rpmh_send_msg,

	TP_PROTO(काष्ठा rsc_drv *d, पूर्णांक m, पूर्णांक n, u32 h,
		 स्थिर काष्ठा tcs_cmd *c),

	TP_ARGS(d, m, n, h, c),

	TP_STRUCT__entry(
			 __string(name, d->name)
			 __field(पूर्णांक, m)
			 __field(पूर्णांक, n)
			 __field(u32, hdr)
			 __field(u32, addr)
			 __field(u32, data)
			 __field(bool, रुको)
	),

	TP_fast_assign(
		       __assign_str(name, d->name);
		       __entry->m = m;
		       __entry->n = n;
		       __entry->hdr = h;
		       __entry->addr = c->addr;
		       __entry->data = c->data;
		       __entry->रुको = c->रुको;
	),

	TP_prपूर्णांकk("%s: send-msg: tcs(m): %d cmd(n): %d msgid: %#x addr: %#x data: %#x complete: %d",
		  __get_str(name), __entry->m, __entry->n, __entry->hdr,
		  __entry->addr, __entry->data, __entry->रुको)
);

#पूर्ण_अगर /* _TRACE_RPMH_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace-rpmh

#समावेश <trace/define_trace.h>
