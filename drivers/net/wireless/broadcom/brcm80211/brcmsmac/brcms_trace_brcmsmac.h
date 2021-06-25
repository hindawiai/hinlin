<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर !defined(__TRACE_BRCMSMAC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __TRACE_BRCMSMAC_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM brcmsmac

/*
 * We define a tracepoपूर्णांक, its arguments, its prपूर्णांकk क्रमmat and its
 * 'fast binary record' layout.
 */
TRACE_EVENT(brcms_समयr,
	/* TPPROTO is the prototype of the function called by this tracepoपूर्णांक */
	TP_PROTO(काष्ठा brcms_समयr *t),
	/*
	 * TPARGS(firstarg, p) are the parameters names, same as found in the
	 * prototype.
	 */
	TP_ARGS(t),
	/*
	 * Fast binary tracing: define the trace record via TP_STRUCT__entry().
	 * You can think about it like a regular C काष्ठाure local variable
	 * definition.
	 */
	TP_STRUCT__entry(
		__field(uपूर्णांक, ms)
		__field(uपूर्णांक, set)
		__field(uपूर्णांक, periodic)
	),
	TP_fast_assign(
		__entry->ms = t->ms;
		__entry->set = t->set;
		__entry->periodic = t->periodic;
	),
	TP_prपूर्णांकk(
		"ms=%u set=%u periodic=%u",
		__entry->ms, __entry->set, __entry->periodic
	)
);

TRACE_EVENT(brcms_dpc,
	TP_PROTO(अचिन्हित दीर्घ data),
	TP_ARGS(data),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, data)
	),
	TP_fast_assign(
		__entry->data = data;
	),
	TP_prपूर्णांकk(
		"data=%p",
		(व्योम *)__entry->data
	)
);

TRACE_EVENT(brcms_macपूर्णांकstatus,
	TP_PROTO(स्थिर काष्ठा device *dev, पूर्णांक in_isr, u32 macपूर्णांकstatus,
		 u32 mask),
	TP_ARGS(dev, in_isr, macपूर्णांकstatus, mask),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(पूर्णांक, in_isr)
		__field(u32, macपूर्णांकstatus)
		__field(u32, mask)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev));
		__entry->in_isr = in_isr;
		__entry->macपूर्णांकstatus = macपूर्णांकstatus;
		__entry->mask = mask;
	),
	TP_prपूर्णांकk("[%s] in_isr=%d macintstatus=%#x mask=%#x", __get_str(dev),
		  __entry->in_isr, __entry->macपूर्णांकstatus, __entry->mask)
);
#पूर्ण_अगर /* __TRACE_BRCMSMAC_H */

#अगर_घोषित CONFIG_BRCM_TRACING

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता brcms_trace_brcmsmac
#समावेश <trace/define_trace.h>

#पूर्ण_अगर /* CONFIG_BRCM_TRACING */
