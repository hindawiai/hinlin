<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM घातer

#अगर !defined(_TRACE_POWER_CPU_MIGRATE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_POWER_CPU_MIGRATE_H

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा __cpu_migrate_proto			\
	TP_PROTO(u64 बारtamp,			\
		 u32 cpu_hwid)
#घोषणा __cpu_migrate_args			\
	TP_ARGS(बारtamp,			\
		cpu_hwid)

DECLARE_EVENT_CLASS(cpu_migrate,

	__cpu_migrate_proto,
	__cpu_migrate_args,

	TP_STRUCT__entry(
		__field(u64,	बारtamp		)
		__field(u32,	cpu_hwid		)
	),

	TP_fast_assign(
		__entry->बारtamp = बारtamp;
		__entry->cpu_hwid = cpu_hwid;
	),

	TP_prपूर्णांकk("timestamp=%llu cpu_hwid=0x%08lX",
		(अचिन्हित दीर्घ दीर्घ)__entry->बारtamp,
		(अचिन्हित दीर्घ)__entry->cpu_hwid
	)
);

#घोषणा __define_cpu_migrate_event(name)		\
	DEFINE_EVENT(cpu_migrate, cpu_migrate_##name,	\
		__cpu_migrate_proto,			\
		__cpu_migrate_args			\
	)

__define_cpu_migrate_event(begin);
__define_cpu_migrate_event(finish);
__define_cpu_migrate_event(current);

#अघोषित __define_cpu_migrate
#अघोषित __cpu_migrate_proto
#अघोषित __cpu_migrate_args

/* This file can get included multiple बार, TRACE_HEADER_MULTI_READ at top */
#अगर_अघोषित _PWR_CPU_MIGRATE_EVENT_AVOID_DOUBLE_DEFINING
#घोषणा _PWR_CPU_MIGRATE_EVENT_AVOID_DOUBLE_DEFINING

/*
 * Set from_phys_cpu and to_phys_cpu to CPU_MIGRATE_ALL_CPUS to indicate
 * a whole-cluster migration:
 */
#घोषणा CPU_MIGRATE_ALL_CPUS 0x80000000U
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_POWER_CPU_MIGRATE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता घातer_cpu_migrate
#समावेश <trace/define_trace.h>
