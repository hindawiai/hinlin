<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM thermal_घातer_allocator

#अगर !defined(_TRACE_THERMAL_POWER_ALLOCATOR_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_THERMAL_POWER_ALLOCATOR_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(thermal_घातer_allocator,
	TP_PROTO(काष्ठा thermal_zone_device *tz, u32 *req_घातer,
		 u32 total_req_घातer, u32 *granted_घातer,
		 u32 total_granted_घातer, माप_प्रकार num_actors,
		 u32 घातer_range, u32 max_allocatable_घातer,
		 पूर्णांक current_temp, s32 delta_temp),
	TP_ARGS(tz, req_घातer, total_req_घातer, granted_घातer,
		total_granted_घातer, num_actors, घातer_range,
		max_allocatable_घातer, current_temp, delta_temp),
	TP_STRUCT__entry(
		__field(पूर्णांक,           tz_id          )
		__dynamic_array(u32,   req_घातer, num_actors    )
		__field(u32,           total_req_घातer          )
		__dynamic_array(u32,   granted_घातer, num_actors)
		__field(u32,           total_granted_घातer      )
		__field(माप_प्रकार,        num_actors               )
		__field(u32,           घातer_range              )
		__field(u32,           max_allocatable_घातer    )
		__field(पूर्णांक,           current_temp             )
		__field(s32,           delta_temp               )
	),
	TP_fast_assign(
		__entry->tz_id = tz->id;
		स_नकल(__get_dynamic_array(req_घातer), req_घातer,
			num_actors * माप(*req_घातer));
		__entry->total_req_घातer = total_req_घातer;
		स_नकल(__get_dynamic_array(granted_घातer), granted_घातer,
			num_actors * माप(*granted_घातer));
		__entry->total_granted_घातer = total_granted_घातer;
		__entry->num_actors = num_actors;
		__entry->घातer_range = घातer_range;
		__entry->max_allocatable_घातer = max_allocatable_घातer;
		__entry->current_temp = current_temp;
		__entry->delta_temp = delta_temp;
	),

	TP_prपूर्णांकk("thermal_zone_id=%d req_power={%s} total_req_power=%u granted_power={%s} total_granted_power=%u power_range=%u max_allocatable_power=%u current_temperature=%d delta_temperature=%d",
		__entry->tz_id,
		__prपूर्णांक_array(__get_dynamic_array(req_घातer),
                              __entry->num_actors, 4),
		__entry->total_req_घातer,
		__prपूर्णांक_array(__get_dynamic_array(granted_घातer),
                              __entry->num_actors, 4),
		__entry->total_granted_घातer, __entry->घातer_range,
		__entry->max_allocatable_घातer, __entry->current_temp,
		__entry->delta_temp)
);

TRACE_EVENT(thermal_घातer_allocator_pid,
	TP_PROTO(काष्ठा thermal_zone_device *tz, s32 err, s32 err_पूर्णांकegral,
		 s64 p, s64 i, s64 d, s32 output),
	TP_ARGS(tz, err, err_पूर्णांकegral, p, i, d, output),
	TP_STRUCT__entry(
		__field(पूर्णांक, tz_id       )
		__field(s32, err         )
		__field(s32, err_पूर्णांकegral)
		__field(s64, p           )
		__field(s64, i           )
		__field(s64, d           )
		__field(s32, output      )
	),
	TP_fast_assign(
		__entry->tz_id = tz->id;
		__entry->err = err;
		__entry->err_पूर्णांकegral = err_पूर्णांकegral;
		__entry->p = p;
		__entry->i = i;
		__entry->d = d;
		__entry->output = output;
	),

	TP_prपूर्णांकk("thermal_zone_id=%d err=%d err_integral=%d p=%lld i=%lld d=%lld output=%d",
		  __entry->tz_id, __entry->err, __entry->err_पूर्णांकegral,
		  __entry->p, __entry->i, __entry->d, __entry->output)
);
#पूर्ण_अगर /* _TRACE_THERMAL_POWER_ALLOCATOR_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
