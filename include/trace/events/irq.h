<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM irq

#अगर !defined(_TRACE_IRQ_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IRQ_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा irqaction;
काष्ठा softirq_action;

#घोषणा SOFTIRQ_NAME_LIST				\
			 softirq_name(HI)		\
			 softirq_name(TIMER)		\
			 softirq_name(NET_TX)		\
			 softirq_name(NET_RX)		\
			 softirq_name(BLOCK)		\
			 softirq_name(IRQ_POLL)		\
			 softirq_name(TASKLET)		\
			 softirq_name(SCHED)		\
			 softirq_name(HRTIMER)		\
			 softirq_name_end(RCU)

#अघोषित softirq_name
#अघोषित softirq_name_end

#घोषणा softirq_name(sirq) TRACE_DEFINE_ENUM(sirq##_SOFTIRQ);
#घोषणा softirq_name_end(sirq)  TRACE_DEFINE_ENUM(sirq##_SOFTIRQ);

SOFTIRQ_NAME_LIST

#अघोषित softirq_name
#अघोषित softirq_name_end

#घोषणा softirq_name(sirq) अणु sirq##_SOFTIRQ, #sirq पूर्ण,
#घोषणा softirq_name_end(sirq) अणु sirq##_SOFTIRQ, #sirq पूर्ण

#घोषणा show_softirq_name(val)				\
	__prपूर्णांक_symbolic(val, SOFTIRQ_NAME_LIST)

/**
 * irq_handler_entry - called immediately beक्रमe the irq action handler
 * @irq: irq number
 * @action: poपूर्णांकer to काष्ठा irqaction
 *
 * The काष्ठा irqaction poपूर्णांकed to by @action contains various
 * inक्रमmation about the handler, including the device name,
 * @action->name, and the device id, @action->dev_id. When used in
 * conjunction with the irq_handler_निकास tracepoपूर्णांक, we can figure
 * out irq handler latencies.
 */
TRACE_EVENT(irq_handler_entry,

	TP_PROTO(पूर्णांक irq, काष्ठा irqaction *action),

	TP_ARGS(irq, action),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	irq		)
		__string(	name,	action->name	)
	),

	TP_fast_assign(
		__entry->irq = irq;
		__assign_str(name, action->name);
	),

	TP_prपूर्णांकk("irq=%d name=%s", __entry->irq, __get_str(name))
);

/**
 * irq_handler_निकास - called immediately after the irq action handler वापसs
 * @irq: irq number
 * @action: poपूर्णांकer to काष्ठा irqaction
 * @ret: वापस value
 *
 * If the @ret value is set to IRQ_HANDLED, then we know that the corresponding
 * @action->handler successfully handled this irq. Otherwise, the irq might be
 * a shared irq line, or the irq was not handled successfully. Can be used in
 * conjunction with the irq_handler_entry to understand irq handler latencies.
 */
TRACE_EVENT(irq_handler_निकास,

	TP_PROTO(पूर्णांक irq, काष्ठा irqaction *action, पूर्णांक ret),

	TP_ARGS(irq, action, ret),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	irq	)
		__field(	पूर्णांक,	ret	)
	),

	TP_fast_assign(
		__entry->irq	= irq;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("irq=%d ret=%s",
		  __entry->irq, __entry->ret ? "handled" : "unhandled")
);

DECLARE_EVENT_CLASS(softirq,

	TP_PROTO(अचिन्हित पूर्णांक vec_nr),

	TP_ARGS(vec_nr),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vec	)
	),

	TP_fast_assign(
		__entry->vec = vec_nr;
	),

	TP_prपूर्णांकk("vec=%u [action=%s]", __entry->vec,
		  show_softirq_name(__entry->vec))
);

/**
 * softirq_entry - called immediately beक्रमe the softirq handler
 * @vec_nr:  softirq vector number
 *
 * When used in combination with the softirq_निकास tracepoपूर्णांक
 * we can determine the softirq handler routine.
 */
DEFINE_EVENT(softirq, softirq_entry,

	TP_PROTO(अचिन्हित पूर्णांक vec_nr),

	TP_ARGS(vec_nr)
);

/**
 * softirq_निकास - called immediately after the softirq handler वापसs
 * @vec_nr:  softirq vector number
 *
 * When used in combination with the softirq_entry tracepoपूर्णांक
 * we can determine the softirq handler routine.
 */
DEFINE_EVENT(softirq, softirq_निकास,

	TP_PROTO(अचिन्हित पूर्णांक vec_nr),

	TP_ARGS(vec_nr)
);

/**
 * softirq_उठाओ - called immediately when a softirq is उठाओd
 * @vec_nr:  softirq vector number
 *
 * When used in combination with the softirq_entry tracepoपूर्णांक
 * we can determine the softirq उठाओ to run latency.
 */
DEFINE_EVENT(softirq, softirq_उठाओ,

	TP_PROTO(अचिन्हित पूर्णांक vec_nr),

	TP_ARGS(vec_nr)
);

#पूर्ण_अगर /*  _TRACE_IRQ_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
