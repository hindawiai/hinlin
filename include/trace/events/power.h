<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM घातer

#अगर !defined(_TRACE_POWER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_POWER_H

#समावेश <linux/cpufreq.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_events.h>

#घोषणा TPS(x)  tracepoपूर्णांक_string(x)

DECLARE_EVENT_CLASS(cpu,

	TP_PROTO(अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(state, cpu_id),

	TP_STRUCT__entry(
		__field(	u32,		state		)
		__field(	u32,		cpu_id		)
	),

	TP_fast_assign(
		__entry->state = state;
		__entry->cpu_id = cpu_id;
	),

	TP_prपूर्णांकk("state=%lu cpu_id=%lu", (अचिन्हित दीर्घ)__entry->state,
		  (अचिन्हित दीर्घ)__entry->cpu_id)
);

DEFINE_EVENT(cpu, cpu_idle,

	TP_PROTO(अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(state, cpu_id)
);

TRACE_EVENT(घातernv_throttle,

	TP_PROTO(पूर्णांक chip_id, स्थिर अक्षर *reason, पूर्णांक pmax),

	TP_ARGS(chip_id, reason, pmax),

	TP_STRUCT__entry(
		__field(पूर्णांक, chip_id)
		__string(reason, reason)
		__field(पूर्णांक, pmax)
	),

	TP_fast_assign(
		__entry->chip_id = chip_id;
		__assign_str(reason, reason);
		__entry->pmax = pmax;
	),

	TP_prपूर्णांकk("Chip %d Pmax %d %s", __entry->chip_id,
		  __entry->pmax, __get_str(reason))
);

TRACE_EVENT(pstate_sample,

	TP_PROTO(u32 core_busy,
		u32 scaled_busy,
		u32 from,
		u32 to,
		u64 mperf,
		u64 aperf,
		u64 tsc,
		u32 freq,
		u32 io_boost
		),

	TP_ARGS(core_busy,
		scaled_busy,
		from,
		to,
		mperf,
		aperf,
		tsc,
		freq,
		io_boost
		),

	TP_STRUCT__entry(
		__field(u32, core_busy)
		__field(u32, scaled_busy)
		__field(u32, from)
		__field(u32, to)
		__field(u64, mperf)
		__field(u64, aperf)
		__field(u64, tsc)
		__field(u32, freq)
		__field(u32, io_boost)
		),

	TP_fast_assign(
		__entry->core_busy = core_busy;
		__entry->scaled_busy = scaled_busy;
		__entry->from = from;
		__entry->to = to;
		__entry->mperf = mperf;
		__entry->aperf = aperf;
		__entry->tsc = tsc;
		__entry->freq = freq;
		__entry->io_boost = io_boost;
		),

	TP_prपूर्णांकk("core_busy=%lu scaled=%lu from=%lu to=%lu mperf=%llu aperf=%llu tsc=%llu freq=%lu io_boost=%lu",
		(अचिन्हित दीर्घ)__entry->core_busy,
		(अचिन्हित दीर्घ)__entry->scaled_busy,
		(अचिन्हित दीर्घ)__entry->from,
		(अचिन्हित दीर्घ)__entry->to,
		(अचिन्हित दीर्घ दीर्घ)__entry->mperf,
		(अचिन्हित दीर्घ दीर्घ)__entry->aperf,
		(अचिन्हित दीर्घ दीर्घ)__entry->tsc,
		(अचिन्हित दीर्घ)__entry->freq,
		(अचिन्हित दीर्घ)__entry->io_boost
		)

);

/* This file can get included multiple बार, TRACE_HEADER_MULTI_READ at top */
#अगर_अघोषित _PWR_EVENT_AVOID_DOUBLE_DEFINING
#घोषणा _PWR_EVENT_AVOID_DOUBLE_DEFINING

#घोषणा PWR_EVENT_EXIT -1
#पूर्ण_अगर

#घोषणा pm_verb_symbolic(event) \
	__prपूर्णांक_symbolic(event, \
		अणु PM_EVENT_SUSPEND, "suspend" पूर्ण, \
		अणु PM_EVENT_RESUME, "resume" पूर्ण, \
		अणु PM_EVENT_FREEZE, "freeze" पूर्ण, \
		अणु PM_EVENT_QUIESCE, "quiesce" पूर्ण, \
		अणु PM_EVENT_HIBERNATE, "hibernate" पूर्ण, \
		अणु PM_EVENT_THAW, "thaw" पूर्ण, \
		अणु PM_EVENT_RESTORE, "restore" पूर्ण, \
		अणु PM_EVENT_RECOVER, "recover" पूर्ण)

DEFINE_EVENT(cpu, cpu_frequency,

	TP_PROTO(अचिन्हित पूर्णांक frequency, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(frequency, cpu_id)
);

TRACE_EVENT(cpu_frequency_limits,

	TP_PROTO(काष्ठा cpufreq_policy *policy),

	TP_ARGS(policy),

	TP_STRUCT__entry(
		__field(u32, min_freq)
		__field(u32, max_freq)
		__field(u32, cpu_id)
	),

	TP_fast_assign(
		__entry->min_freq = policy->min;
		__entry->max_freq = policy->max;
		__entry->cpu_id = policy->cpu;
	),

	TP_prपूर्णांकk("min=%lu max=%lu cpu_id=%lu",
		  (अचिन्हित दीर्घ)__entry->min_freq,
		  (अचिन्हित दीर्घ)__entry->max_freq,
		  (अचिन्हित दीर्घ)__entry->cpu_id)
);

TRACE_EVENT(device_pm_callback_start,

	TP_PROTO(काष्ठा device *dev, स्थिर अक्षर *pm_ops, पूर्णांक event),

	TP_ARGS(dev, pm_ops, event),

	TP_STRUCT__entry(
		__string(device, dev_name(dev))
		__string(driver, dev_driver_string(dev))
		__string(parent, dev->parent ? dev_name(dev->parent) : "none")
		__string(pm_ops, pm_ops ? pm_ops : "none ")
		__field(पूर्णांक, event)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(dev));
		__assign_str(driver, dev_driver_string(dev));
		__assign_str(parent,
			dev->parent ? dev_name(dev->parent) : "none");
		__assign_str(pm_ops, pm_ops ? pm_ops : "none ");
		__entry->event = event;
	),

	TP_prपूर्णांकk("%s %s, parent: %s, %s[%s]", __get_str(driver),
		__get_str(device), __get_str(parent), __get_str(pm_ops),
		pm_verb_symbolic(__entry->event))
);

TRACE_EVENT(device_pm_callback_end,

	TP_PROTO(काष्ठा device *dev, पूर्णांक error),

	TP_ARGS(dev, error),

	TP_STRUCT__entry(
		__string(device, dev_name(dev))
		__string(driver, dev_driver_string(dev))
		__field(पूर्णांक, error)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(dev));
		__assign_str(driver, dev_driver_string(dev));
		__entry->error = error;
	),

	TP_prपूर्णांकk("%s %s, err=%d",
		__get_str(driver), __get_str(device), __entry->error)
);

TRACE_EVENT(suspend_resume,

	TP_PROTO(स्थिर अक्षर *action, पूर्णांक val, bool start),

	TP_ARGS(action, val, start),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, action)
		__field(पूर्णांक, val)
		__field(bool, start)
	),

	TP_fast_assign(
		__entry->action = action;
		__entry->val = val;
		__entry->start = start;
	),

	TP_prपूर्णांकk("%s[%u] %s", __entry->action, (अचिन्हित पूर्णांक)__entry->val,
		(__entry->start)?"begin":"end")
);

DECLARE_EVENT_CLASS(wakeup_source,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state),

	TP_ARGS(name, state),

	TP_STRUCT__entry(
		__string(       name,           name            )
		__field(        u64,            state           )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->state = state;
	),

	TP_prपूर्णांकk("%s state=0x%lx", __get_str(name),
		(अचिन्हित दीर्घ)__entry->state)
);

DEFINE_EVENT(wakeup_source, wakeup_source_activate,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state),

	TP_ARGS(name, state)
);

DEFINE_EVENT(wakeup_source, wakeup_source_deactivate,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state),

	TP_ARGS(name, state)
);

/*
 * The घड़ी events are used क्रम घड़ी enable/disable and क्रम
 *  घड़ी rate change
 */
DECLARE_EVENT_CLASS(घड़ी,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id),

	TP_STRUCT__entry(
		__string(       name,           name            )
		__field(        u64,            state           )
		__field(        u64,            cpu_id          )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->state = state;
		__entry->cpu_id = cpu_id;
	),

	TP_prपूर्णांकk("%s state=%lu cpu_id=%lu", __get_str(name),
		(अचिन्हित दीर्घ)__entry->state, (अचिन्हित दीर्घ)__entry->cpu_id)
);

DEFINE_EVENT(घड़ी, घड़ी_enable,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id)
);

DEFINE_EVENT(घड़ी, घड़ी_disable,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id)
);

DEFINE_EVENT(घड़ी, घड़ी_set_rate,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id)
);

/*
 * The घातer करोमुख्य events are used क्रम घातer करोमुख्यs transitions
 */
DECLARE_EVENT_CLASS(घातer_करोमुख्य,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id),

	TP_STRUCT__entry(
		__string(       name,           name            )
		__field(        u64,            state           )
		__field(        u64,            cpu_id          )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->state = state;
		__entry->cpu_id = cpu_id;
),

	TP_prपूर्णांकk("%s state=%lu cpu_id=%lu", __get_str(name),
		(अचिन्हित दीर्घ)__entry->state, (अचिन्हित दीर्घ)__entry->cpu_id)
);

DEFINE_EVENT(घातer_करोमुख्य, घातer_करोमुख्य_target,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक cpu_id),

	TP_ARGS(name, state, cpu_id)
);

/*
 * CPU latency QoS events used क्रम global CPU latency QoS list updates
 */
DECLARE_EVENT_CLASS(cpu_latency_qos_request,

	TP_PROTO(s32 value),

	TP_ARGS(value),

	TP_STRUCT__entry(
		__field( s32,                    value          )
	),

	TP_fast_assign(
		__entry->value = value;
	),

	TP_prपूर्णांकk("CPU_DMA_LATENCY value=%d",
		  __entry->value)
);

DEFINE_EVENT(cpu_latency_qos_request, pm_qos_add_request,

	TP_PROTO(s32 value),

	TP_ARGS(value)
);

DEFINE_EVENT(cpu_latency_qos_request, pm_qos_update_request,

	TP_PROTO(s32 value),

	TP_ARGS(value)
);

DEFINE_EVENT(cpu_latency_qos_request, pm_qos_हटाओ_request,

	TP_PROTO(s32 value),

	TP_ARGS(value)
);

/*
 * General PM QoS events used क्रम updates of PM QoS request lists
 */
DECLARE_EVENT_CLASS(pm_qos_update,

	TP_PROTO(क्रमागत pm_qos_req_action action, पूर्णांक prev_value, पूर्णांक curr_value),

	TP_ARGS(action, prev_value, curr_value),

	TP_STRUCT__entry(
		__field( क्रमागत pm_qos_req_action, action         )
		__field( पूर्णांक,                    prev_value     )
		__field( पूर्णांक,                    curr_value     )
	),

	TP_fast_assign(
		__entry->action = action;
		__entry->prev_value = prev_value;
		__entry->curr_value = curr_value;
	),

	TP_prपूर्णांकk("action=%s prev_value=%d curr_value=%d",
		  __prपूर्णांक_symbolic(__entry->action,
			अणु PM_QOS_ADD_REQ,	"ADD_REQ" पूर्ण,
			अणु PM_QOS_UPDATE_REQ,	"UPDATE_REQ" पूर्ण,
			अणु PM_QOS_REMOVE_REQ,	"REMOVE_REQ" पूर्ण),
		  __entry->prev_value, __entry->curr_value)
);

DEFINE_EVENT(pm_qos_update, pm_qos_update_target,

	TP_PROTO(क्रमागत pm_qos_req_action action, पूर्णांक prev_value, पूर्णांक curr_value),

	TP_ARGS(action, prev_value, curr_value)
);

DEFINE_EVENT_PRINT(pm_qos_update, pm_qos_update_flags,

	TP_PROTO(क्रमागत pm_qos_req_action action, पूर्णांक prev_value, पूर्णांक curr_value),

	TP_ARGS(action, prev_value, curr_value),

	TP_prपूर्णांकk("action=%s prev_value=0x%x curr_value=0x%x",
		  __prपूर्णांक_symbolic(__entry->action,
			अणु PM_QOS_ADD_REQ,	"ADD_REQ" पूर्ण,
			अणु PM_QOS_UPDATE_REQ,	"UPDATE_REQ" पूर्ण,
			अणु PM_QOS_REMOVE_REQ,	"REMOVE_REQ" पूर्ण),
		  __entry->prev_value, __entry->curr_value)
);

DECLARE_EVENT_CLASS(dev_pm_qos_request,

	TP_PROTO(स्थिर अक्षर *name, क्रमागत dev_pm_qos_req_type type,
		 s32 new_value),

	TP_ARGS(name, type, new_value),

	TP_STRUCT__entry(
		__string( name,                    name         )
		__field( क्रमागत dev_pm_qos_req_type, type         )
		__field( s32,                      new_value    )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->type = type;
		__entry->new_value = new_value;
	),

	TP_prपूर्णांकk("device=%s type=%s new_value=%d",
		  __get_str(name),
		  __prपूर्णांक_symbolic(__entry->type,
			अणु DEV_PM_QOS_RESUME_LATENCY, "DEV_PM_QOS_RESUME_LATENCY" पूर्ण,
			अणु DEV_PM_QOS_FLAGS, "DEV_PM_QOS_FLAGS" पूर्ण),
		  __entry->new_value)
);

DEFINE_EVENT(dev_pm_qos_request, dev_pm_qos_add_request,

	TP_PROTO(स्थिर अक्षर *name, क्रमागत dev_pm_qos_req_type type,
		 s32 new_value),

	TP_ARGS(name, type, new_value)
);

DEFINE_EVENT(dev_pm_qos_request, dev_pm_qos_update_request,

	TP_PROTO(स्थिर अक्षर *name, क्रमागत dev_pm_qos_req_type type,
		 s32 new_value),

	TP_ARGS(name, type, new_value)
);

DEFINE_EVENT(dev_pm_qos_request, dev_pm_qos_हटाओ_request,

	TP_PROTO(स्थिर अक्षर *name, क्रमागत dev_pm_qos_req_type type,
		 s32 new_value),

	TP_ARGS(name, type, new_value)
);
#पूर्ण_अगर /* _TRACE_POWER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
