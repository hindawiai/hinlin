<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Trace support header file क्रम device mode
 *
 * Copyright (C) 2020 NXP
 *
 * Author: Peter Chen <peter.chen@nxp.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM chipidea

#अगर !defined(__LINUX_CHIPIDEA_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __LINUX_CHIPIDEA_TRACE

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/usb/chipidea.h>
#समावेश "ci.h"
#समावेश "udc.h"

#घोषणा CHIPIDEA_MSG_MAX	500

व्योम ci_log(काष्ठा ci_hdrc *ci, स्थिर अक्षर *fmt, ...);

TRACE_EVENT(ci_log,
	TP_PROTO(काष्ठा ci_hdrc *ci, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(ci, vaf),
	TP_STRUCT__entry(
		__string(name, dev_name(ci->dev))
		__dynamic_array(अक्षर, msg, CHIPIDEA_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(name, dev_name(ci->dev));
		vsnम_लिखो(__get_str(msg), CHIPIDEA_MSG_MAX, vaf->fmt, *vaf->va);
	),
	TP_prपूर्णांकk("%s: %s", __get_str(name), __get_str(msg))
);

DECLARE_EVENT_CLASS(ci_log_trb,
	TP_PROTO(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq, काष्ठा td_node *td),
	TP_ARGS(hwep, hwreq, td),
	TP_STRUCT__entry(
		__string(name, hwep->name)
		__field(काष्ठा td_node *, td)
		__field(काष्ठा usb_request *, req)
		__field(dma_addr_t, dma)
		__field(s32, td_reमुख्यing_size)
		__field(u32, next)
		__field(u32, token)
		__field(u32, type)
	),
	TP_fast_assign(
		__assign_str(name, hwep->name);
		__entry->req = &hwreq->req;
		__entry->td = td;
		__entry->dma = td->dma;
		__entry->td_reमुख्यing_size = td->td_reमुख्यing_size;
		__entry->next = le32_to_cpu(td->ptr->next);
		__entry->token = le32_to_cpu(td->ptr->token);
		__entry->type = usb_endpoपूर्णांक_type(hwep->ep.desc);
	),
	TP_prपूर्णांकk("%s: req: %p, td: %p, td_dma_address: %pad, remaining_size: %d, "
	       "next: %x, total bytes: %d, status: %lx",
		__get_str(name), __entry->req, __entry->td, &__entry->dma,
		__entry->td_reमुख्यing_size, __entry->next,
		(पूर्णांक)((__entry->token & TD_TOTAL_BYTES) >> __ffs(TD_TOTAL_BYTES)),
		__entry->token & TD_STATUS
	)
);

DEFINE_EVENT(ci_log_trb, ci_prepare_td,
	TP_PROTO(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq, काष्ठा td_node *td),
	TP_ARGS(hwep, hwreq, td)
);

DEFINE_EVENT(ci_log_trb, ci_complete_td,
	TP_PROTO(काष्ठा ci_hw_ep *hwep, काष्ठा ci_hw_req *hwreq, काष्ठा td_node *td),
	TP_ARGS(hwep, hwreq, td)
);

#पूर्ण_अगर /* __LINUX_CHIPIDEA_TRACE */

/* this part must be outside header guard */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
