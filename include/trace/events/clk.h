<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM clk

#अगर !defined(_TRACE_CLK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CLK_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा clk_core;

DECLARE_EVENT_CLASS(clk,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core),

	TP_STRUCT__entry(
		__string(        name,           core->name       )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
	),

	TP_prपूर्णांकk("%s", __get_str(name))
);

DEFINE_EVENT(clk, clk_enable,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_enable_complete,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_disable,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_disable_complete,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_prepare,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_prepare_complete,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_unprepare,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DEFINE_EVENT(clk, clk_unprepare_complete,

	TP_PROTO(काष्ठा clk_core *core),

	TP_ARGS(core)
);

DECLARE_EVENT_CLASS(clk_rate,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ rate),

	TP_ARGS(core, rate),

	TP_STRUCT__entry(
		__string(        name,           core->name                )
		__field(अचिन्हित दीर्घ,           rate                      )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
		__entry->rate = rate;
	),

	TP_prपूर्णांकk("%s %lu", __get_str(name), (अचिन्हित दीर्घ)__entry->rate)
);

DEFINE_EVENT(clk_rate, clk_set_rate,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ rate),

	TP_ARGS(core, rate)
);

DEFINE_EVENT(clk_rate, clk_set_rate_complete,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ rate),

	TP_ARGS(core, rate)
);

DEFINE_EVENT(clk_rate, clk_set_min_rate,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ rate),

	TP_ARGS(core, rate)
);

DEFINE_EVENT(clk_rate, clk_set_max_rate,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ rate),

	TP_ARGS(core, rate)
);

DECLARE_EVENT_CLASS(clk_rate_range,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ min, अचिन्हित दीर्घ max),

	TP_ARGS(core, min, max),

	TP_STRUCT__entry(
		__string(        name,           core->name                )
		__field(अचिन्हित दीर्घ,           min                       )
		__field(अचिन्हित दीर्घ,           max                       )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
		__entry->min = min;
		__entry->max = max;
	),

	TP_prपूर्णांकk("%s min %lu max %lu", __get_str(name),
		  (अचिन्हित दीर्घ)__entry->min,
		  (अचिन्हित दीर्घ)__entry->max)
);

DEFINE_EVENT(clk_rate_range, clk_set_rate_range,

	TP_PROTO(काष्ठा clk_core *core, अचिन्हित दीर्घ min, अचिन्हित दीर्घ max),

	TP_ARGS(core, min, max)
);

DECLARE_EVENT_CLASS(clk_parent,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_core *parent),

	TP_ARGS(core, parent),

	TP_STRUCT__entry(
		__string(        name,           core->name                )
		__string(        pname, parent ? parent->name : "none"     )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
		__assign_str(pname, parent ? parent->name : "none");
	),

	TP_prपूर्णांकk("%s %s", __get_str(name), __get_str(pname))
);

DEFINE_EVENT(clk_parent, clk_set_parent,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_core *parent),

	TP_ARGS(core, parent)
);

DEFINE_EVENT(clk_parent, clk_set_parent_complete,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_core *parent),

	TP_ARGS(core, parent)
);

DECLARE_EVENT_CLASS(clk_phase,

	TP_PROTO(काष्ठा clk_core *core, पूर्णांक phase),

	TP_ARGS(core, phase),

	TP_STRUCT__entry(
		__string(        name,           core->name                )
		__field(	  पूर्णांक,           phase                     )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
		__entry->phase = phase;
	),

	TP_prपूर्णांकk("%s %d", __get_str(name), (पूर्णांक)__entry->phase)
);

DEFINE_EVENT(clk_phase, clk_set_phase,

	TP_PROTO(काष्ठा clk_core *core, पूर्णांक phase),

	TP_ARGS(core, phase)
);

DEFINE_EVENT(clk_phase, clk_set_phase_complete,

	TP_PROTO(काष्ठा clk_core *core, पूर्णांक phase),

	TP_ARGS(core, phase)
);

DECLARE_EVENT_CLASS(clk_duty_cycle,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_duty *duty),

	TP_ARGS(core, duty),

	TP_STRUCT__entry(
		__string(        name,           core->name              )
		__field( अचिन्हित पूर्णांक,           num                     )
		__field( अचिन्हित पूर्णांक,           den                     )
	),

	TP_fast_assign(
		__assign_str(name, core->name);
		__entry->num = duty->num;
		__entry->den = duty->den;
	),

	TP_prपूर्णांकk("%s %u/%u", __get_str(name), (अचिन्हित पूर्णांक)__entry->num,
		  (अचिन्हित पूर्णांक)__entry->den)
);

DEFINE_EVENT(clk_duty_cycle, clk_set_duty_cycle,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_duty *duty),

	TP_ARGS(core, duty)
);

DEFINE_EVENT(clk_duty_cycle, clk_set_duty_cycle_complete,

	TP_PROTO(काष्ठा clk_core *core, काष्ठा clk_duty *duty),

	TP_ARGS(core, duty)
);

#पूर्ण_अगर /* _TRACE_CLK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
