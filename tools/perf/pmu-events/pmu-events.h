<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PMU_EVENTS_H
#घोषणा PMU_EVENTS_H

क्रमागत aggr_mode_class अणु
	PerChip = 1,
	PerCore
पूर्ण;

/*
 * Describe each PMU event. Each CPU has a table of PMU events.
 */
काष्ठा pmu_event अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *compat;
	स्थिर अक्षर *event;
	स्थिर अक्षर *desc;
	स्थिर अक्षर *topic;
	स्थिर अक्षर *दीर्घ_desc;
	स्थिर अक्षर *pmu;
	स्थिर अक्षर *unit;
	स्थिर अक्षर *perpkg;
	स्थिर अक्षर *aggr_mode;
	स्थिर अक्षर *metric_expr;
	स्थिर अक्षर *metric_name;
	स्थिर अक्षर *metric_group;
	स्थिर अक्षर *deprecated;
	स्थिर अक्षर *metric_स्थिरraपूर्णांक;
पूर्ण;

/*
 *
 * Map a CPU to its table of PMU events. The CPU is identअगरied by the
 * cpuid field, which is an arch-specअगरic identअगरier क्रम the CPU.
 * The identअगरier specअगरied in tools/perf/pmu-events/arch/xxx/mapfile
 * must match the get_cpuid_str() in tools/perf/arch/xxx/util/header.c)
 *
 * The  cpuid can contain any अक्षरacter other than the comma.
 */
काष्ठा pmu_events_map अणु
	स्थिर अक्षर *cpuid;
	स्थिर अक्षर *version;
	स्थिर अक्षर *type;		/* core, uncore etc */
	काष्ठा pmu_event *table;
पूर्ण;

काष्ठा pmu_sys_events अणु
	काष्ठा pmu_event *table;
पूर्ण;

/*
 * Global table mapping each known CPU क्रम the architecture to its
 * table of PMU events.
 */
बाह्य काष्ठा pmu_events_map pmu_events_map[];
बाह्य काष्ठा pmu_sys_events pmu_sys_event_tables[];

#पूर्ण_अगर
