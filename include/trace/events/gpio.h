<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gpio

#अगर !defined(_TRACE_GPIO_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_GPIO_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(gpio_direction,

	TP_PROTO(अचिन्हित gpio, पूर्णांक in, पूर्णांक err),

	TP_ARGS(gpio, in, err),

	TP_STRUCT__entry(
		__field(अचिन्हित, gpio)
		__field(पूर्णांक, in)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->gpio = gpio;
		__entry->in = in;
		__entry->err = err;
	),

	TP_prपूर्णांकk("%u %3s (%d)", __entry->gpio,
		__entry->in ? "in" : "out", __entry->err)
);

TRACE_EVENT(gpio_value,

	TP_PROTO(अचिन्हित gpio, पूर्णांक get, पूर्णांक value),

	TP_ARGS(gpio, get, value),

	TP_STRUCT__entry(
		__field(अचिन्हित, gpio)
		__field(पूर्णांक, get)
		__field(पूर्णांक, value)
	),

	TP_fast_assign(
		__entry->gpio = gpio;
		__entry->get = get;
		__entry->value = value;
	),

	TP_prपूर्णांकk("%u %3s %d", __entry->gpio,
		__entry->get ? "get" : "set", __entry->value)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_GPIO_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
