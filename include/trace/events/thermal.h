<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM thermal

#अगर !defined(_TRACE_THERMAL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_THERMAL_H

#समावेश <linux/devfreq.h>
#समावेश <linux/thermal.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(THERMAL_TRIP_CRITICAL);
TRACE_DEFINE_ENUM(THERMAL_TRIP_HOT);
TRACE_DEFINE_ENUM(THERMAL_TRIP_PASSIVE);
TRACE_DEFINE_ENUM(THERMAL_TRIP_ACTIVE);

#घोषणा show_tzt_type(type)					\
	__prपूर्णांक_symbolic(type,					\
			 अणु THERMAL_TRIP_CRITICAL, "CRITICAL"पूर्ण,	\
			 अणु THERMAL_TRIP_HOT,      "HOT"पूर्ण,	\
			 अणु THERMAL_TRIP_PASSIVE,  "PASSIVE"पूर्ण,	\
			 अणु THERMAL_TRIP_ACTIVE,   "ACTIVE"पूर्ण)

TRACE_EVENT(thermal_temperature,

	TP_PROTO(काष्ठा thermal_zone_device *tz),

	TP_ARGS(tz),

	TP_STRUCT__entry(
		__string(thermal_zone, tz->type)
		__field(पूर्णांक, id)
		__field(पूर्णांक, temp_prev)
		__field(पूर्णांक, temp)
	),

	TP_fast_assign(
		__assign_str(thermal_zone, tz->type);
		__entry->id = tz->id;
		__entry->temp_prev = tz->last_temperature;
		__entry->temp = tz->temperature;
	),

	TP_prपूर्णांकk("thermal_zone=%s id=%d temp_prev=%d temp=%d",
		__get_str(thermal_zone), __entry->id, __entry->temp_prev,
		__entry->temp)
);

TRACE_EVENT(cdev_update,

	TP_PROTO(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ target),

	TP_ARGS(cdev, target),

	TP_STRUCT__entry(
		__string(type, cdev->type)
		__field(अचिन्हित दीर्घ, target)
	),

	TP_fast_assign(
		__assign_str(type, cdev->type);
		__entry->target = target;
	),

	TP_prपूर्णांकk("type=%s target=%lu", __get_str(type), __entry->target)
);

TRACE_EVENT(thermal_zone_trip,

	TP_PROTO(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
		क्रमागत thermal_trip_type trip_type),

	TP_ARGS(tz, trip, trip_type),

	TP_STRUCT__entry(
		__string(thermal_zone, tz->type)
		__field(पूर्णांक, id)
		__field(पूर्णांक, trip)
		__field(क्रमागत thermal_trip_type, trip_type)
	),

	TP_fast_assign(
		__assign_str(thermal_zone, tz->type);
		__entry->id = tz->id;
		__entry->trip = trip;
		__entry->trip_type = trip_type;
	),

	TP_prपूर्णांकk("thermal_zone=%s id=%d trip=%d trip_type=%s",
		__get_str(thermal_zone), __entry->id, __entry->trip,
		show_tzt_type(__entry->trip_type))
);

#अगर_घोषित CONFIG_CPU_THERMAL
TRACE_EVENT(thermal_घातer_cpu_get_घातer,
	TP_PROTO(स्थिर काष्ठा cpumask *cpus, अचिन्हित दीर्घ freq, u32 *load,
		माप_प्रकार load_len, u32 dynamic_घातer),

	TP_ARGS(cpus, freq, load, load_len, dynamic_घातer),

	TP_STRUCT__entry(
		__biपंचांगask(cpumask, num_possible_cpus())
		__field(अचिन्हित दीर्घ, freq          )
		__dynamic_array(u32,   load, load_len)
		__field(माप_प्रकार,        load_len      )
		__field(u32,           dynamic_घातer )
	),

	TP_fast_assign(
		__assign_biपंचांगask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		स_नकल(__get_dynamic_array(load), load,
			load_len * माप(*load));
		__entry->load_len = load_len;
		__entry->dynamic_घातer = dynamic_घातer;
	),

	TP_prपूर्णांकk("cpus=%s freq=%lu load={%s} dynamic_power=%d",
		__get_biपंचांगask(cpumask), __entry->freq,
		__prपूर्णांक_array(__get_dynamic_array(load), __entry->load_len, 4),
		__entry->dynamic_घातer)
);

TRACE_EVENT(thermal_घातer_cpu_limit,
	TP_PROTO(स्थिर काष्ठा cpumask *cpus, अचिन्हित पूर्णांक freq,
		अचिन्हित दीर्घ cdev_state, u32 घातer),

	TP_ARGS(cpus, freq, cdev_state, घातer),

	TP_STRUCT__entry(
		__biपंचांगask(cpumask, num_possible_cpus())
		__field(अचिन्हित पूर्णांक,  freq      )
		__field(अचिन्हित दीर्घ, cdev_state)
		__field(u32,           घातer     )
	),

	TP_fast_assign(
		__assign_biपंचांगask(cpumask, cpumask_bits(cpus),
				num_possible_cpus());
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
		__entry->घातer = घातer;
	),

	TP_prपूर्णांकk("cpus=%s freq=%u cdev_state=%lu power=%u",
		__get_biपंचांगask(cpumask), __entry->freq, __entry->cdev_state,
		__entry->घातer)
);
#पूर्ण_अगर /* CONFIG_CPU_THERMAL */

#अगर_घोषित CONFIG_DEVFREQ_THERMAL
TRACE_EVENT(thermal_घातer_devfreq_get_घातer,
	TP_PROTO(काष्ठा thermal_cooling_device *cdev,
		 काष्ठा devfreq_dev_status *status, अचिन्हित दीर्घ freq,
		u32 घातer),

	TP_ARGS(cdev, status,  freq, घातer),

	TP_STRUCT__entry(
		__string(type,         cdev->type    )
		__field(अचिन्हित दीर्घ, freq          )
		__field(u32,           busy_समय)
		__field(u32,           total_समय)
		__field(u32,           घातer)
	),

	TP_fast_assign(
		__assign_str(type, cdev->type);
		__entry->freq = freq;
		__entry->busy_समय = status->busy_समय;
		__entry->total_समय = status->total_समय;
		__entry->घातer = घातer;
	),

	TP_prपूर्णांकk("type=%s freq=%lu load=%u power=%u",
		__get_str(type), __entry->freq,
		__entry->total_समय == 0 ? 0 :
			(100 * __entry->busy_समय) / __entry->total_समय,
		__entry->घातer)
);

TRACE_EVENT(thermal_घातer_devfreq_limit,
	TP_PROTO(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ freq,
		अचिन्हित दीर्घ cdev_state, u32 घातer),

	TP_ARGS(cdev, freq, cdev_state, घातer),

	TP_STRUCT__entry(
		__string(type,         cdev->type)
		__field(अचिन्हित पूर्णांक,  freq      )
		__field(अचिन्हित दीर्घ, cdev_state)
		__field(u32,           घातer     )
	),

	TP_fast_assign(
		__assign_str(type, cdev->type);
		__entry->freq = freq;
		__entry->cdev_state = cdev_state;
		__entry->घातer = घातer;
	),

	TP_prपूर्णांकk("type=%s freq=%u cdev_state=%lu power=%u",
		__get_str(type), __entry->freq, __entry->cdev_state,
		__entry->घातer)
);
#पूर्ण_अगर /* CONFIG_DEVFREQ_THERMAL */
#पूर्ण_अगर /* _TRACE_THERMAL_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
