<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Portions of this file
 * Copyright (C) 2019 Intel Corporation
 */

#अगर_घोषित CONFIG_MAC80211_MESSAGE_TRACING

#अगर !defined(__MAC80211_MSG_DRIVER_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MAC80211_MSG_DRIVER_TRACE

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mac80211_msg

#घोषणा MAX_MSG_LEN	120

DECLARE_EVENT_CLASS(mac80211_msg_event,
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

DEFINE_EVENT(mac80211_msg_event, mac80211_info,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);
DEFINE_EVENT(mac80211_msg_event, mac80211_dbg,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);
DEFINE_EVENT(mac80211_msg_event, mac80211_err,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);
#पूर्ण_अगर /* !__MAC80211_MSG_DRIVER_TRACE || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace_msg
#समावेश <trace/define_trace.h>

#पूर्ण_अगर
