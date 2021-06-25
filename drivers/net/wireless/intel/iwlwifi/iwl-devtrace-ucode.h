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

#अगर !defined(__IWLWIFI_DEVICE_TRACE_UCODE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __IWLWIFI_DEVICE_TRACE_UCODE

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iwlwअगरi_ucode

TRACE_EVENT(iwlwअगरi_dev_ucode_cont_event,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 समय, u32 data, u32 ev),
	TP_ARGS(dev, समय, data, ev),
	TP_STRUCT__entry(
		DEV_ENTRY

		__field(u32, समय)
		__field(u32, data)
		__field(u32, ev)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->समय = समय;
		__entry->data = data;
		__entry->ev = ev;
	),
	TP_prपूर्णांकk("[%s] EVT_LOGT:%010u:0x%08x:%04u",
		  __get_str(dev), __entry->समय, __entry->data, __entry->ev)
);

TRACE_EVENT(iwlwअगरi_dev_ucode_wrap_event,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 wraps, u32 n_entry, u32 p_entry),
	TP_ARGS(dev, wraps, n_entry, p_entry),
	TP_STRUCT__entry(
		DEV_ENTRY

		__field(u32, wraps)
		__field(u32, n_entry)
		__field(u32, p_entry)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->wraps = wraps;
		__entry->n_entry = n_entry;
		__entry->p_entry = p_entry;
	),
	TP_prपूर्णांकk("[%s] wraps=#%02d n=0x%X p=0x%X",
		  __get_str(dev), __entry->wraps, __entry->n_entry,
		  __entry->p_entry)
);
#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE_UCODE */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता iwl-devtrace-ucode
#समावेश <trace/define_trace.h>
