<शैली गुरु>
#अगर_घोषित CONFIG_PREEMPTIRQ_TRACEPOINTS

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM preemptirq

#अगर !defined(_TRACE_PREEMPTIRQ_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PREEMPTIRQ_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/sections.h>

DECLARE_EVENT_CLASS(preemptirq_ढाँचा,

	TP_PROTO(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip),

	TP_ARGS(ip, parent_ip),

	TP_STRUCT__entry(
		__field(s32, caller_offs)
		__field(s32, parent_offs)
	),

	TP_fast_assign(
		__entry->caller_offs = (s32)(ip - (अचिन्हित दीर्घ)_stext);
		__entry->parent_offs = (s32)(parent_ip - (अचिन्हित दीर्घ)_stext);
	),

	TP_prपूर्णांकk("caller=%pS parent=%pS",
		  (व्योम *)((अचिन्हित दीर्घ)(_stext) + __entry->caller_offs),
		  (व्योम *)((अचिन्हित दीर्घ)(_stext) + __entry->parent_offs))
);

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
DEFINE_EVENT(preemptirq_ढाँचा, irq_disable,
	     TP_PROTO(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip),
	     TP_ARGS(ip, parent_ip));

DEFINE_EVENT(preemptirq_ढाँचा, irq_enable,
	     TP_PROTO(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip),
	     TP_ARGS(ip, parent_ip));
#अन्यथा
#घोषणा trace_irq_enable(...)
#घोषणा trace_irq_disable(...)
#घोषणा trace_irq_enable_rcuidle(...)
#घोषणा trace_irq_disable_rcuidle(...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACE_PREEMPT_TOGGLE
DEFINE_EVENT(preemptirq_ढाँचा, preempt_disable,
	     TP_PROTO(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip),
	     TP_ARGS(ip, parent_ip));

DEFINE_EVENT(preemptirq_ढाँचा, preempt_enable,
	     TP_PROTO(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip),
	     TP_ARGS(ip, parent_ip));
#अन्यथा
#घोषणा trace_preempt_enable(...)
#घोषणा trace_preempt_disable(...)
#घोषणा trace_preempt_enable_rcuidle(...)
#घोषणा trace_preempt_disable_rcuidle(...)
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_PREEMPTIRQ_H */

#समावेश <trace/define_trace.h>

#अन्यथा /* !CONFIG_PREEMPTIRQ_TRACEPOINTS */
#घोषणा trace_irq_enable(...)
#घोषणा trace_irq_disable(...)
#घोषणा trace_irq_enable_rcuidle(...)
#घोषणा trace_irq_disable_rcuidle(...)
#घोषणा trace_preempt_enable(...)
#घोषणा trace_preempt_disable(...)
#घोषणा trace_preempt_enable_rcuidle(...)
#घोषणा trace_preempt_disable_rcuidle(...)
#पूर्ण_अगर
