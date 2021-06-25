<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MacBook (Pro) SPI keyboard and touchpad driver
 *
 * Copyright (c) 2015-2019 Federico Lorenzi
 * Copyright (c) 2017-2019 Ronald Tschalथअr
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM applespi

#अगर !defined(_APPLESPI_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _APPLESPI_TRACE_H_

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश "applespi.h"

DECLARE_EVENT_CLASS(dump_message_ढाँचा,
	TP_PROTO(क्रमागत applespi_evt_type evt_type,
		 क्रमागत applespi_pkt_type pkt_type,
		 u8 *buf,
		 माप_प्रकार len),

	TP_ARGS(evt_type, pkt_type, buf, len),

	TP_STRUCT__entry(
		__field(क्रमागत applespi_evt_type, evt_type)
		__field(क्रमागत applespi_pkt_type, pkt_type)
		__field(माप_प्रकार, len)
		__dynamic_array(u8, buf, len)
	),

	TP_fast_assign(
		__entry->evt_type = evt_type;
		__entry->pkt_type = pkt_type;
		__entry->len = len;
		स_नकल(__get_dynamic_array(buf), buf, len);
	),

	TP_prपूर्णांकk("%-6s: %s",
		  __prपूर्णांक_symbolic(__entry->pkt_type,
				   अणु PT_READ, "read" पूर्ण,
				   अणु PT_WRITE, "write" पूर्ण,
				   अणु PT_STATUS, "status" पूर्ण
		  ),
		  __prपूर्णांक_hex(__get_dynamic_array(buf), __entry->len))
);

#घोषणा DEFINE_DUMP_MESSAGE_EVENT(name)			\
DEFINE_EVENT(dump_message_ढाँचा, name,		\
	TP_PROTO(क्रमागत applespi_evt_type evt_type,	\
		 क्रमागत applespi_pkt_type pkt_type,	\
		 u8 *buf,				\
		 माप_प्रकार len),				\
	TP_ARGS(evt_type, pkt_type, buf, len)		\
)

DEFINE_DUMP_MESSAGE_EVENT(applespi_tp_ini_cmd);
DEFINE_DUMP_MESSAGE_EVENT(applespi_backlight_cmd);
DEFINE_DUMP_MESSAGE_EVENT(applespi_caps_lock_cmd);
DEFINE_DUMP_MESSAGE_EVENT(applespi_keyboard_data);
DEFINE_DUMP_MESSAGE_EVENT(applespi_touchpad_data);
DEFINE_DUMP_MESSAGE_EVENT(applespi_unknown_data);
DEFINE_DUMP_MESSAGE_EVENT(applespi_bad_crc);

TRACE_EVENT(applespi_irq_received,
	TP_PROTO(क्रमागत applespi_evt_type evt_type,
		 क्रमागत applespi_pkt_type pkt_type),

	TP_ARGS(evt_type, pkt_type),

	TP_STRUCT__entry(
		__field(क्रमागत applespi_evt_type, evt_type)
		__field(क्रमागत applespi_pkt_type, pkt_type)
	),

	TP_fast_assign(
		__entry->evt_type = evt_type;
		__entry->pkt_type = pkt_type;
	),

	"\n"
);

#पूर्ण_अगर /* _APPLESPI_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/input/keyboard
#घोषणा TRACE_INCLUDE_खाता applespi_trace
#समावेश <trace/define_trace.h>
