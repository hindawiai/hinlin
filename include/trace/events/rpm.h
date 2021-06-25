<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rpm

#अगर !defined(_TRACE_RUNTIME_POWER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RUNTIME_POWER_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा device;

/*
 * The rpm_पूर्णांकernal events are used क्रम tracing some important
 * runसमय pm पूर्णांकernal functions.
 */
DECLARE_EVENT_CLASS(rpm_पूर्णांकernal,

	TP_PROTO(काष्ठा device *dev, पूर्णांक flags),

	TP_ARGS(dev, flags),

	TP_STRUCT__entry(
		__string(       name,		dev_name(dev)	)
		__field(        पूर्णांक,            flags           )
		__field(        पूर्णांक ,   	usage_count	)
		__field(        पूर्णांक ,   	disable_depth   )
		__field(        पूर्णांक ,   	runसमय_स्वतः	)
		__field(        पूर्णांक ,   	request_pending	)
		__field(        पूर्णांक ,   	irq_safe	)
		__field(        पूर्णांक ,   	child_count 	)
	),

	TP_fast_assign(
		__assign_str(name, dev_name(dev));
		__entry->flags = flags;
		__entry->usage_count = atomic_पढ़ो(
			&dev->घातer.usage_count);
		__entry->disable_depth = dev->घातer.disable_depth;
		__entry->runसमय_स्वतः = dev->घातer.runसमय_स्वतः;
		__entry->request_pending = dev->घातer.request_pending;
		__entry->irq_safe = dev->घातer.irq_safe;
		__entry->child_count = atomic_पढ़ो(
			&dev->घातer.child_count);
	),

	TP_prपूर्णांकk("%s flags-%x cnt-%-2d dep-%-2d auto-%-1d p-%-1d"
			" irq-%-1d child-%d",
			__get_str(name), __entry->flags,
			__entry->usage_count,
			__entry->disable_depth,
			__entry->runसमय_स्वतः,
			__entry->request_pending,
			__entry->irq_safe,
			__entry->child_count
		 )
);
DEFINE_EVENT(rpm_पूर्णांकernal, rpm_suspend,

	TP_PROTO(काष्ठा device *dev, पूर्णांक flags),

	TP_ARGS(dev, flags)
);
DEFINE_EVENT(rpm_पूर्णांकernal, rpm_resume,

	TP_PROTO(काष्ठा device *dev, पूर्णांक flags),

	TP_ARGS(dev, flags)
);
DEFINE_EVENT(rpm_पूर्णांकernal, rpm_idle,

	TP_PROTO(काष्ठा device *dev, पूर्णांक flags),

	TP_ARGS(dev, flags)
);
DEFINE_EVENT(rpm_पूर्णांकernal, rpm_usage,

	TP_PROTO(काष्ठा device *dev, पूर्णांक flags),

	TP_ARGS(dev, flags)
);

TRACE_EVENT(rpm_वापस_पूर्णांक,
	TP_PROTO(काष्ठा device *dev, अचिन्हित दीर्घ ip, पूर्णांक ret),
	TP_ARGS(dev, ip, ret),

	TP_STRUCT__entry(
		__string(       name,		dev_name(dev))
		__field(	अचिन्हित दीर्घ,		ip	)
		__field(	पूर्णांक,			ret	)
	),

	TP_fast_assign(
		__assign_str(name, dev_name(dev));
		__entry->ip = ip;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("%pS:%s ret=%d", (व्योम *)__entry->ip, __get_str(name),
		__entry->ret)
);

#पूर्ण_अगर /* _TRACE_RUNTIME_POWER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
