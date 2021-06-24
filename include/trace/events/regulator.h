<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM regulator

#अगर !defined(_TRACE_REGULATOR_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_REGULATOR_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Events which just log themselves and the regulator name क्रम enable/disable
 * type tracking.
 */
DECLARE_EVENT_CLASS(regulator_basic,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name),

	TP_STRUCT__entry(
		__string(	name,	name	)
	),

	TP_fast_assign(
		__assign_str(name, name);
	),

	TP_prपूर्णांकk("name=%s", __get_str(name))

);

DEFINE_EVENT(regulator_basic, regulator_enable,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_enable_delay,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_enable_complete,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_disable,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_disable_complete,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_bypass_enable,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_bypass_enable_complete,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_bypass_disable,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

DEFINE_EVENT(regulator_basic, regulator_bypass_disable_complete,

	TP_PROTO(स्थिर अक्षर *name),

	TP_ARGS(name)

);

/*
 * Events that take a range of numerical values, mostly क्रम voltages
 * and so on.
 */
DECLARE_EVENT_CLASS(regulator_range,

	TP_PROTO(स्थिर अक्षर *name, पूर्णांक min, पूर्णांक max),

	TP_ARGS(name, min, max),

	TP_STRUCT__entry(
		__string(	name,		name		)
		__field(        पूर्णांक,            min             )
		__field(        पूर्णांक,            max             )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->min  = min;
		__entry->max  = max;
	),

	TP_prपूर्णांकk("name=%s (%d-%d)", __get_str(name),
		  (पूर्णांक)__entry->min, (पूर्णांक)__entry->max)
);

DEFINE_EVENT(regulator_range, regulator_set_voltage,

	TP_PROTO(स्थिर अक्षर *name, पूर्णांक min, पूर्णांक max),

	TP_ARGS(name, min, max)

);


/*
 * Events that take a single value, mostly क्रम पढ़ोback and refcounts.
 */
DECLARE_EVENT_CLASS(regulator_value,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक val),

	TP_ARGS(name, val),

	TP_STRUCT__entry(
		__string(	name,		name		)
		__field(        अचिन्हित पूर्णांक,   val             )
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->val  = val;
	),

	TP_prपूर्णांकk("name=%s, val=%u", __get_str(name),
		  (पूर्णांक)__entry->val)
);

DEFINE_EVENT(regulator_value, regulator_set_voltage_complete,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित पूर्णांक value),

	TP_ARGS(name, value)

);

#पूर्ण_अगर /* _TRACE_POWER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
