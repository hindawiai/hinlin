<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017-2018 Intel Corporation
 */

#अगर_अघोषित __I915_PMU_H__
#घोषणा __I915_PMU_H__

#समावेश <linux/hrसमयr.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/spinlock_types.h>
#समावेश <uapi/drm/i915_drm.h>

काष्ठा drm_i915_निजी;

/**
 * Non-engine events that we need to track enabled-disabled transition and
 * current state.
 */
क्रमागत i915_pmu_tracked_events अणु
	__I915_PMU_ACTUAL_FREQUENCY_ENABLED = 0,
	__I915_PMU_REQUESTED_FREQUENCY_ENABLED,
	__I915_PMU_RC6_RESIDENCY_ENABLED,
	__I915_PMU_TRACKED_EVENT_COUNT, /* count marker */
पूर्ण;

/**
 * Slots used from the sampling समयr (non-engine events) with some extras क्रम
 * convenience.
 */
क्रमागत अणु
	__I915_SAMPLE_FREQ_ACT = 0,
	__I915_SAMPLE_FREQ_REQ,
	__I915_SAMPLE_RC6,
	__I915_SAMPLE_RC6_LAST_REPORTED,
	__I915_NUM_PMU_SAMPLERS
पूर्ण;

/**
 * How many dअगरferent events we track in the global PMU mask.
 *
 * It is also used to know to needed number of event reference counters.
 */
#घोषणा I915_PMU_MASK_BITS \
	(I915_ENGINE_SAMPLE_COUNT + __I915_PMU_TRACKED_EVENT_COUNT)

#घोषणा I915_ENGINE_SAMPLE_COUNT (I915_SAMPLE_SEMA + 1)

काष्ठा i915_pmu_sample अणु
	u64 cur;
पूर्ण;

काष्ठा i915_pmu अणु
	/**
	 * @cpuhp: Struct used क्रम CPU hotplug handling.
	 */
	काष्ठा अणु
		काष्ठा hlist_node node;
		अचिन्हित पूर्णांक cpu;
	पूर्ण cpuhp;
	/**
	 * @base: PMU base.
	 */
	काष्ठा pmu base;
	/**
	 * @बंदd: i915 is unरेजिस्टरing.
	 */
	bool बंदd;
	/**
	 * @name: Name as रेजिस्टरed with perf core.
	 */
	स्थिर अक्षर *name;
	/**
	 * @lock: Lock protecting enable mask and ref count handling.
	 */
	spinlock_t lock;
	/**
	 * @समयr: Timer क्रम पूर्णांकernal i915 PMU sampling.
	 */
	काष्ठा hrसमयr समयr;
	/**
	 * @enable: Biपंचांगask of specअगरic enabled events.
	 *
	 * For some events we need to track their state and करो some पूर्णांकernal
	 * house keeping.
	 *
	 * Each engine event sampler type and event listed in क्रमागत
	 * i915_pmu_tracked_events माला_लो a bit in this field.
	 *
	 * Low bits are engine samplers and other events जारी from there.
	 */
	u32 enable;

	/**
	 * @समयr_last:
	 *
	 * Timesपंचांगap of the previous समयr invocation.
	 */
	kसमय_प्रकार समयr_last;

	/**
	 * @enable_count: Reference counts क्रम the enabled events.
	 *
	 * Array indices are mapped in the same way as bits in the @enable field
	 * and they are used to control sampling on/off when multiple clients
	 * are using the PMU API.
	 */
	अचिन्हित पूर्णांक enable_count[I915_PMU_MASK_BITS];
	/**
	 * @समयr_enabled: Should the पूर्णांकernal sampling समयr be running.
	 */
	bool समयr_enabled;
	/**
	 * @sample: Current and previous (raw) counters क्रम sampling events.
	 *
	 * These counters are updated from the i915 PMU sampling समयr.
	 *
	 * Only global counters are held here, जबतक the per-engine ones are in
	 * काष्ठा पूर्णांकel_engine_cs.
	 */
	काष्ठा i915_pmu_sample sample[__I915_NUM_PMU_SAMPLERS];
	/**
	 * @sleep_last: Last समय GT parked क्रम RC6 estimation.
	 */
	kसमय_प्रकार sleep_last;
	/**
	 * @irq_count: Number of पूर्णांकerrupts
	 *
	 * Intentionally अचिन्हित दीर्घ to aव्योम atomics or heuristics on 32bit.
	 * 4e9 पूर्णांकerrupts are a lot and postprocessing can really deal with an
	 * occasional wraparound easily. It's 32bit after all.
	 */
	अचिन्हित दीर्घ irq_count;
	/**
	 * @events_attr_group: Device events attribute group.
	 */
	काष्ठा attribute_group events_attr_group;
	/**
	 * @i915_attr: Memory block holding device attributes.
	 */
	व्योम *i915_attr;
	/**
	 * @pmu_attr: Memory block holding device attributes.
	 */
	व्योम *pmu_attr;
पूर्ण;

#अगर_घोषित CONFIG_PERF_EVENTS
व्योम i915_pmu_init(व्योम);
व्योम i915_pmu_निकास(व्योम);
व्योम i915_pmu_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम i915_pmu_unरेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम i915_pmu_gt_parked(काष्ठा drm_i915_निजी *i915);
व्योम i915_pmu_gt_unparked(काष्ठा drm_i915_निजी *i915);
#अन्यथा
अटल अंतरभूत व्योम i915_pmu_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम i915_pmu_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम i915_pmu_रेजिस्टर(काष्ठा drm_i915_निजी *i915) अणुपूर्ण
अटल अंतरभूत व्योम i915_pmu_unरेजिस्टर(काष्ठा drm_i915_निजी *i915) अणुपूर्ण
अटल अंतरभूत व्योम i915_pmu_gt_parked(काष्ठा drm_i915_निजी *i915) अणुपूर्ण
अटल अंतरभूत व्योम i915_pmu_gt_unparked(काष्ठा drm_i915_निजी *i915) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
