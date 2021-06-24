<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Tracepoपूर्णांकs क्रम vfio_ccw driver
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Halil Pasic <pasic@linux.vnet.ibm.com>
 */

#समावेश "cio.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vfio_ccw

#अगर !defined(_VFIO_CCW_TRACE_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _VFIO_CCW_TRACE_

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(vfio_ccw_chp_event,
	TP_PROTO(काष्ठा subchannel_id schid,
		 पूर्णांक mask,
		 पूर्णांक event),
	TP_ARGS(schid, mask, event),

	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, sch_no)
		__field(पूर्णांक, mask)
		__field(पूर्णांक, event)
	),

	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->sch_no = schid.sch_no;
		__entry->mask = mask;
		__entry->event = event;
	),

	TP_prपूर्णांकk("schid=%x.%x.%04x mask=0x%x event=%d",
		  __entry->cssid,
		  __entry->ssid,
		  __entry->sch_no,
		  __entry->mask,
		  __entry->event)
);

TRACE_EVENT(vfio_ccw_fsm_async_request,
	TP_PROTO(काष्ठा subchannel_id schid,
		 पूर्णांक command,
		 पूर्णांक त्रुटि_सं),
	TP_ARGS(schid, command, त्रुटि_सं),

	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, sch_no)
		__field(पूर्णांक, command)
		__field(पूर्णांक, त्रुटि_सं)
	),

	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->sch_no = schid.sch_no;
		__entry->command = command;
		__entry->त्रुटि_सं = त्रुटि_सं;
	),

	TP_prपूर्णांकk("schid=%x.%x.%04x command=0x%x errno=%d",
		  __entry->cssid,
		  __entry->ssid,
		  __entry->sch_no,
		  __entry->command,
		  __entry->त्रुटि_सं)
);

TRACE_EVENT(vfio_ccw_fsm_event,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक state, पूर्णांक event),
	TP_ARGS(schid, state, event),

	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field(पूर्णांक, state)
		__field(पूर्णांक, event)
	),

	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->schno = schid.sch_no;
		__entry->state = state;
		__entry->event = event;
	),

	TP_prपूर्णांकk("schid=%x.%x.%04x state=%d event=%d",
		__entry->cssid, __entry->ssid, __entry->schno,
		__entry->state,
		__entry->event)
);

TRACE_EVENT(vfio_ccw_fsm_io_request,
	TP_PROTO(पूर्णांक fctl, काष्ठा subchannel_id schid, पूर्णांक त्रुटि_सं, अक्षर *errstr),
	TP_ARGS(fctl, schid, त्रुटि_सं, errstr),

	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, sch_no)
		__field(पूर्णांक, fctl)
		__field(पूर्णांक, त्रुटि_सं)
		__field(अक्षर*, errstr)
	),

	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->sch_no = schid.sch_no;
		__entry->fctl = fctl;
		__entry->त्रुटि_सं = त्रुटि_सं;
		__entry->errstr = errstr;
	),

	TP_prपूर्णांकk("schid=%x.%x.%04x fctl=0x%x errno=%d info=%s",
		  __entry->cssid,
		  __entry->ssid,
		  __entry->sch_no,
		  __entry->fctl,
		  __entry->त्रुटि_सं,
		  __entry->errstr)
);

#पूर्ण_अगर /* _VFIO_CCW_TRACE_ */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता vfio_ccw_trace

#समावेश <trace/define_trace.h>
