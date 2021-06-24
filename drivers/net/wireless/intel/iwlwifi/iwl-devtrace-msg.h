<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर !defined(__IWLWIFI_DEVICE_TRACE_MSG) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __IWLWIFI_DEVICE_TRACE_MSG

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iwlwअगरi_msg

#घोषणा MAX_MSG_LEN	110

DECLARE_EVENT_CLASS(iwlwअगरi_msg_event,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, msg, MAX_MSG_LEN)
	),
	TP_fast_assign(
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       MAX_MSG_LEN, vaf->fmt,
				       *vaf->va) >= MAX_MSG_LEN);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

DEFINE_EVENT(iwlwअगरi_msg_event, iwlwअगरi_err,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(iwlwअगरi_msg_event, iwlwअगरi_warn,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(iwlwअगरi_msg_event, iwlwअगरi_info,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(iwlwअगरi_msg_event, iwlwअगरi_crit,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

TRACE_EVENT(iwlwअगरi_dbg,
	TP_PROTO(u32 level, स्थिर अक्षर *function,
		 काष्ठा va_क्रमmat *vaf),
	TP_ARGS(level, function, vaf),
	TP_STRUCT__entry(
		__field(u32, level)
		__string(function, function)
		__dynamic_array(अक्षर, msg, MAX_MSG_LEN)
	),
	TP_fast_assign(
		__entry->level = level;
		__assign_str(function, function);
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       MAX_MSG_LEN, vaf->fmt,
				       *vaf->va) >= MAX_MSG_LEN);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);
#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE_MSG */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता iwl-devtrace-msg
#समावेश <trace/define_trace.h>
