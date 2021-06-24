<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/include/यंत्र/pmu.h
 *
 *  Copyright (C) 2009 picoChip Designs Ltd, Jamie Iles
 */

#अगर_अघोषित __ARM_PMU_H__
#घोषणा __ARM_PMU_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/cputype.h>

#अगर_घोषित CONFIG_ARM_PMU

/*
 * The ARMv7 CPU PMU supports up to 32 event counters.
 */
#घोषणा ARMPMU_MAX_HWEVENTS		32

/*
 * ARM PMU hw_event flags
 */
/* Event uses a 64bit counter */
#घोषणा ARMPMU_EVT_64BIT		1

#घोषणा HW_OP_UNSUPPORTED		0xFFFF
#घोषणा C(_x)				PERF_COUNT_HW_CACHE_##_x
#घोषणा CACHE_OP_UNSUPPORTED		0xFFFF

#घोषणा PERF_MAP_ALL_UNSUPPORTED					\
	[0 ... PERF_COUNT_HW_MAX - 1] = HW_OP_UNSUPPORTED

#घोषणा PERF_CACHE_MAP_ALL_UNSUPPORTED					\
[0 ... C(MAX) - 1] = अणु							\
	[0 ... C(OP_MAX) - 1] = अणु					\
		[0 ... C(RESULT_MAX) - 1] = CACHE_OP_UNSUPPORTED,	\
	पूर्ण,								\
पूर्ण

/* The events क्रम a given PMU रेजिस्टर set. */
काष्ठा pmu_hw_events अणु
	/*
	 * The events that are active on the PMU क्रम the given index.
	 */
	काष्ठा perf_event	*events[ARMPMU_MAX_HWEVENTS];

	/*
	 * A 1 bit क्रम an index indicates that the counter is being used क्रम
	 * an event. A 0 means that the counter can be used.
	 */
	DECLARE_BITMAP(used_mask, ARMPMU_MAX_HWEVENTS);

	/*
	 * Hardware lock to serialize accesses to PMU रेजिस्टरs. Needed क्रम the
	 * पढ़ो/modअगरy/ग_लिखो sequences.
	 */
	raw_spinlock_t		pmu_lock;

	/*
	 * When using percpu IRQs, we need a percpu dev_id. Place it here as we
	 * alपढ़ोy have to allocate this काष्ठा per cpu.
	 */
	काष्ठा arm_pmu		*percpu_pmu;

	पूर्णांक irq;
पूर्ण;

क्रमागत armpmu_attr_groups अणु
	ARMPMU_ATTR_GROUP_COMMON,
	ARMPMU_ATTR_GROUP_EVENTS,
	ARMPMU_ATTR_GROUP_FORMATS,
	ARMPMU_ATTR_GROUP_CAPS,
	ARMPMU_NR_ATTR_GROUPS
पूर्ण;

काष्ठा arm_pmu अणु
	काष्ठा pmu	pmu;
	cpumask_t	supported_cpus;
	अक्षर		*name;
	पूर्णांक		pmuver;
	irqवापस_t	(*handle_irq)(काष्ठा arm_pmu *pmu);
	व्योम		(*enable)(काष्ठा perf_event *event);
	व्योम		(*disable)(काष्ठा perf_event *event);
	पूर्णांक		(*get_event_idx)(काष्ठा pmu_hw_events *hw_events,
					 काष्ठा perf_event *event);
	व्योम		(*clear_event_idx)(काष्ठा pmu_hw_events *hw_events,
					 काष्ठा perf_event *event);
	पूर्णांक		(*set_event_filter)(काष्ठा hw_perf_event *evt,
					    काष्ठा perf_event_attr *attr);
	u64		(*पढ़ो_counter)(काष्ठा perf_event *event);
	व्योम		(*ग_लिखो_counter)(काष्ठा perf_event *event, u64 val);
	व्योम		(*start)(काष्ठा arm_pmu *);
	व्योम		(*stop)(काष्ठा arm_pmu *);
	व्योम		(*reset)(व्योम *);
	पूर्णांक		(*map_event)(काष्ठा perf_event *event);
	पूर्णांक		(*filter_match)(काष्ठा perf_event *event);
	पूर्णांक		num_events;
	bool		secure_access; /* 32-bit ARM only */
#घोषणा ARMV8_PMUV3_MAX_COMMON_EVENTS		0x40
	DECLARE_BITMAP(pmceid_biपंचांगap, ARMV8_PMUV3_MAX_COMMON_EVENTS);
#घोषणा ARMV8_PMUV3_EXT_COMMON_EVENT_BASE	0x4000
	DECLARE_BITMAP(pmceid_ext_biपंचांगap, ARMV8_PMUV3_MAX_COMMON_EVENTS);
	काष्ठा platक्रमm_device	*plat_device;
	काष्ठा pmu_hw_events	__percpu *hw_events;
	काष्ठा hlist_node	node;
	काष्ठा notअगरier_block	cpu_pm_nb;
	/* the attr_groups array must be शून्य-terminated */
	स्थिर काष्ठा attribute_group *attr_groups[ARMPMU_NR_ATTR_GROUPS + 1];
	/* store the PMMIR_EL1 to expose slots */
	u64		reg_pmmir;

	/* Only to be used by ACPI probing code */
	अचिन्हित दीर्घ acpi_cpuid;
पूर्ण;

#घोषणा to_arm_pmu(p) (container_of(p, काष्ठा arm_pmu, pmu))

u64 armpmu_event_update(काष्ठा perf_event *event);

पूर्णांक armpmu_event_set_period(काष्ठा perf_event *event);

पूर्णांक armpmu_map_event(काष्ठा perf_event *event,
		     स्थिर अचिन्हित (*event_map)[PERF_COUNT_HW_MAX],
		     स्थिर अचिन्हित (*cache_map)[PERF_COUNT_HW_CACHE_MAX]
						[PERF_COUNT_HW_CACHE_OP_MAX]
						[PERF_COUNT_HW_CACHE_RESULT_MAX],
		     u32 raw_event_mask);

प्रकार पूर्णांक (*armpmu_init_fn)(काष्ठा arm_pmu *);

काष्ठा pmu_probe_info अणु
	अचिन्हित पूर्णांक cpuid;
	अचिन्हित पूर्णांक mask;
	armpmu_init_fn init;
पूर्ण;

#घोषणा PMU_PROBE(_cpuid, _mask, _fn)	\
अणु					\
	.cpuid = (_cpuid),		\
	.mask = (_mask),		\
	.init = (_fn),			\
पूर्ण

#घोषणा ARM_PMU_PROBE(_cpuid, _fn) \
	PMU_PROBE(_cpuid, ARM_CPU_PART_MASK, _fn)

#घोषणा ARM_PMU_XSCALE_MASK	((0xff << 24) | ARM_CPU_XSCALE_ARCH_MASK)

#घोषणा XSCALE_PMU_PROBE(_version, _fn) \
	PMU_PROBE(ARM_CPU_IMP_INTEL << 24 | _version, ARM_PMU_XSCALE_MASK, _fn)

पूर्णांक arm_pmu_device_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा of_device_id *of_table,
			 स्थिर काष्ठा pmu_probe_info *probe_table);

#अगर_घोषित CONFIG_ACPI
पूर्णांक arm_pmu_acpi_probe(armpmu_init_fn init_fn);
#अन्यथा
अटल अंतरभूत पूर्णांक arm_pmu_acpi_probe(armpmu_init_fn init_fn) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Internal functions only क्रम core arm_pmu code */
काष्ठा arm_pmu *armpmu_alloc(व्योम);
काष्ठा arm_pmu *armpmu_alloc_atomic(व्योम);
व्योम armpmu_मुक्त(काष्ठा arm_pmu *pmu);
पूर्णांक armpmu_रेजिस्टर(काष्ठा arm_pmu *pmu);
पूर्णांक armpmu_request_irq(पूर्णांक irq, पूर्णांक cpu);
व्योम armpmu_मुक्त_irq(पूर्णांक irq, पूर्णांक cpu);

#घोषणा ARMV8_PMU_PDEV_NAME "armv8-pmu"

#पूर्ण_अगर /* CONFIG_ARM_PMU */

#घोषणा ARMV8_SPE_PDEV_NAME "arm,spe-v1"

#पूर्ण_अगर /* __ARM_PMU_H__ */
