<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 * Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM पूर्णांकel_catpt

#अगर !defined(__SND_SOC_INTEL_CATPT_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __SND_SOC_INTEL_CATPT_TRACE_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(catpt_ipc_msg,

	TP_PROTO(u32 header),

	TP_ARGS(header),

	TP_STRUCT__entry(
		__field(u32, header)
	),

	TP_fast_assign(
		__entry->header = header;
	),

	TP_prपूर्णांकk("0x%08x", __entry->header)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_irq,
	TP_PROTO(u32 header),
	TP_ARGS(header)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_request,
	TP_PROTO(u32 header),
	TP_ARGS(header)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_reply,
	TP_PROTO(u32 header),
	TP_ARGS(header)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_notअगरy,
	TP_PROTO(u32 header),
	TP_ARGS(header)
);

TRACE_EVENT_CONDITION(catpt_ipc_payload,

	TP_PROTO(स्थिर u8 *data, माप_प्रकार size),

	TP_ARGS(data, size),

	TP_CONDITION(data && size),

	TP_STRUCT__entry(
		__dynamic_array(u8, buf, size)
	),

	TP_fast_assign(
		स_नकल(__get_dynamic_array(buf), data, size);
	),

	TP_prपूर्णांकk("%u byte(s)%s",
		  __get_dynamic_array_len(buf),
		  __prपूर्णांक_hex_dump("", DUMP_PREFIX_NONE, 16, 4,
				   __get_dynamic_array(buf),
				   __get_dynamic_array_len(buf), false))
);

#पूर्ण_अगर /* __SND_SOC_INTEL_CATPT_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
