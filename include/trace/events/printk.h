<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM prपूर्णांकk

#अगर !defined(_TRACE_PRINTK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PRINTK_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(console,
	TP_PROTO(स्थिर अक्षर *text, माप_प्रकार len),

	TP_ARGS(text, len),

	TP_STRUCT__entry(
		__dynamic_array(अक्षर, msg, len + 1)
	),

	TP_fast_assign(
		/*
		 * Each trace entry is prपूर्णांकed in a new line.
		 * If the msg finishes with '\n', cut it off
		 * to aव्योम blank lines in the trace.
		 */
		अगर ((len > 0) && (text[len-1] == '\n'))
			len -= 1;

		स_नकल(__get_str(msg), text, len);
		__get_str(msg)[len] = 0;
	),

	TP_prपूर्णांकk("%s", __get_str(msg))
);
#पूर्ण_अगर /* _TRACE_PRINTK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
