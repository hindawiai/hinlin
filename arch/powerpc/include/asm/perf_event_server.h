<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Perक्रमmance event support - PowerPC classic/server specअगरic definitions.
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <linux/device.h>
#समावेश <uapi/यंत्र/perf_event.h>

/* Update perf_event_prपूर्णांक_debug() अगर this changes */
#घोषणा MAX_HWEVENTS		8
#घोषणा MAX_EVENT_ALTERNATIVES	8
#घोषणा MAX_LIMITED_HWCOUNTERS	2

काष्ठा perf_event;

काष्ठा mmcr_regs अणु
	अचिन्हित दीर्घ mmcr0;
	अचिन्हित दीर्घ mmcr1;
	अचिन्हित दीर्घ mmcr2;
	अचिन्हित दीर्घ mmcra;
	अचिन्हित दीर्घ mmcr3;
पूर्ण;
/*
 * This काष्ठा provides the स्थिरants and functions needed to
 * describe the PMU on a particular POWER-family CPU.
 */
काष्ठा घातer_pmu अणु
	स्थिर अक्षर	*name;
	पूर्णांक		n_counter;
	पूर्णांक		max_alternatives;
	अचिन्हित दीर्घ	add_fields;
	अचिन्हित दीर्घ	test_adder;
	पूर्णांक		(*compute_mmcr)(u64 events[], पूर्णांक n_ev,
				अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
				काष्ठा perf_event *pevents[], u32 flags);
	पूर्णांक		(*get_स्थिरraपूर्णांक)(u64 event_id, अचिन्हित दीर्घ *mskp,
				अचिन्हित दीर्घ *valp, u64 event_config1);
	पूर्णांक		(*get_alternatives)(u64 event_id, अचिन्हित पूर्णांक flags,
				u64 alt[]);
	व्योम		(*get_mem_data_src)(जोड़ perf_mem_data_src *dsrc,
				u32 flags, काष्ठा pt_regs *regs);
	व्योम		(*get_mem_weight)(u64 *weight, u64 type);
	अचिन्हित दीर्घ	group_स्थिरraपूर्णांक_mask;
	अचिन्हित दीर्घ	group_स्थिरraपूर्णांक_val;
	u64             (*bhrb_filter_map)(u64 branch_sample_type);
	व्योम            (*config_bhrb)(u64 pmu_bhrb_filter);
	व्योम		(*disable_pmc)(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr);
	पूर्णांक		(*limited_pmc_event)(u64 event_id);
	u32		flags;
	स्थिर काष्ठा attribute_group	**attr_groups;
	पूर्णांक		n_generic;
	पूर्णांक		*generic_events;
	u64		(*cache_events)[PERF_COUNT_HW_CACHE_MAX]
			       [PERF_COUNT_HW_CACHE_OP_MAX]
			       [PERF_COUNT_HW_CACHE_RESULT_MAX];

	पूर्णांक		n_blacklist_ev;
	पूर्णांक 		*blacklist_ev;
	/* BHRB entries in the PMU */
	पूर्णांक		bhrb_nr;
	/*
	 * set this flag with `PERF_PMU_CAP_EXTENDED_REGS` अगर
	 * the pmu supports extended perf regs capability
	 */
	पूर्णांक		capabilities;
	/*
	 * Function to check event code क्रम values which are
	 * reserved. Function takes काष्ठा perf_event as input,
	 * since event code could be spपढ़ो in attr.config*
	 */
	पूर्णांक		(*check_attr_config)(काष्ठा perf_event *ev);
पूर्ण;

/*
 * Values क्रम घातer_pmu.flags
 */
#घोषणा PPMU_LIMITED_PMC5_6	0x00000001 /* PMC5/6 have limited function */
#घोषणा PPMU_ALT_SIPR		0x00000002 /* uses alternate posn क्रम SIPR/HV */
#घोषणा PPMU_NO_SIPR		0x00000004 /* no SIPR/HV in MMCRA at all */
#घोषणा PPMU_NO_CONT_SAMPLING	0x00000008 /* no continuous sampling */
#घोषणा PPMU_SIAR_VALID		0x00000010 /* Processor has SIAR Valid bit */
#घोषणा PPMU_HAS_SSLOT		0x00000020 /* Has sampled slot in MMCRA */
#घोषणा PPMU_HAS_SIER		0x00000040 /* Has SIER */
#घोषणा PPMU_ARCH_207S		0x00000080 /* PMC is architecture v2.07S */
#घोषणा PPMU_NO_SIAR		0x00000100 /* Do not use SIAR */
#घोषणा PPMU_ARCH_31		0x00000200 /* Has MMCR3, SIER2 and SIER3 */
#घोषणा PPMU_P10_DD1		0x00000400 /* Is घातer10 DD1 processor version */
#घोषणा PPMU_HAS_ATTR_CONFIG1	0x00000800 /* Using config1 attribute */

/*
 * Values क्रम flags to get_alternatives()
 */
#घोषणा PPMU_LIMITED_PMC_OK	1	/* can put this on a limited PMC */
#घोषणा PPMU_LIMITED_PMC_REQD	2	/* have to put this on a limited PMC */
#घोषणा PPMU_ONLY_COUNT_RUN	4	/* only counting in run state */

बाह्य पूर्णांक रेजिस्टर_घातer_pmu(काष्ठा घातer_pmu *);

काष्ठा pt_regs;
बाह्य अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ पूर्णांक पढ़ो_bhrb(पूर्णांक n);

/*
 * Only override the शेष definitions in include/linux/perf_event.h
 * अगर we have hardware PMU support.
 */
#अगर_घोषित CONFIG_PPC_PERF_CTRS
#घोषणा perf_misc_flags(regs)	perf_misc_flags(regs)
#पूर्ण_अगर

/*
 * The घातer_pmu.get_स्थिरraपूर्णांक function वापसs a 32/64-bit value and
 * a 32/64-bit mask that express the स्थिरraपूर्णांकs between this event_id and
 * other events.
 *
 * The value and mask are भागided up पूर्णांकo (non-overlapping) bitfields
 * of three dअगरferent types:
 *
 * Select field: this expresses the स्थिरraपूर्णांक that some set of bits
 * in MMCR* needs to be set to a specअगरic value क्रम this event_id.  For a
 * select field, the mask contains 1s in every bit of the field, and
 * the value contains a unique value क्रम each possible setting of the
 * MMCR* bits.  The स्थिरraपूर्णांक checking code will ensure that two events
 * that set the same field in their masks have the same value in their
 * value dwords.
 *
 * Add field: this expresses the स्थिरraपूर्णांक that there can be at most
 * N events in a particular class.  A field of k bits can be used क्रम
 * N <= 2^(k-1) - 1.  The mask has the most signअगरicant bit of the field
 * set (and the other bits 0), and the value has only the least signअगरicant
 * bit of the field set.  In addition, the 'add_fields' and 'test_adder'
 * in the काष्ठा घातer_pmu क्रम this processor come पूर्णांकo play.  The
 * add_fields value contains 1 in the LSB of the field, and the
 * test_adder contains 2^(k-1) - 1 - N in the field.
 *
 * न_अंकD field: this expresses the स्थिरraपूर्णांक that you may not have events
 * in all of a set of classes.  (For example, on PPC970, you can't select
 * events from the FPU, ISU and IDU simultaneously, although any two are
 * possible.)  For N classes, the field is N+1 bits wide, and each class
 * is asचिन्हित one bit from the least-signअगरicant N bits.  The mask has
 * only the most-signअगरicant bit set, and the value has only the bit
 * क्रम the event_id's class set.  The test_adder has the least signअगरicant
 * bit set in the field.
 *
 * If an event_id is not subject to the स्थिरraपूर्णांक expressed by a particular
 * field, then it will have 0 in both the mask and value क्रम that field.
 */

बाह्य sमाप_प्रकार घातer_events_sysfs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *page);

/*
 * EVENT_VAR() is same as PMU_EVENT_VAR with a suffix.
 *
 * Having a suffix allows us to have aliases in sysfs - eg: the generic
 * event 'cpu-cycles' can have two entries in sysfs: 'cpu-cycles' and
 * 'PM_CYC' where the latter is the name by which the event is known in
 * POWER CPU specअगरication.
 *
 * Similarly, some hardware and cache events use the same event code. Eg.
 * on POWER8, both "cache-references" and "L1-dcache-loads" events refer
 * to the same event, PM_LD_REF_L1.  The suffix, allows us to have two
 * sysfs objects क्रम the same event and thus two entries/aliases in sysfs.
 */
#घोषणा	EVENT_VAR(_id, _suffix)		event_attr_##_id##_suffix
#घोषणा	EVENT_PTR(_id, _suffix)		&EVENT_VAR(_id, _suffix).attr.attr

#घोषणा	EVENT_ATTR(_name, _id, _suffix)					\
	PMU_EVENT_ATTR(_name, EVENT_VAR(_id, _suffix), _id,		\
			घातer_events_sysfs_show)

#घोषणा	GENERIC_EVENT_ATTR(_name, _id)	EVENT_ATTR(_name, _id, _g)
#घोषणा	GENERIC_EVENT_PTR(_id)		EVENT_PTR(_id, _g)

#घोषणा	CACHE_EVENT_ATTR(_name, _id)	EVENT_ATTR(_name, _id, _c)
#घोषणा	CACHE_EVENT_PTR(_id)		EVENT_PTR(_id, _c)

#घोषणा	POWER_EVENT_ATTR(_name, _id)	EVENT_ATTR(_name, _id, _p)
#घोषणा	POWER_EVENT_PTR(_id)		EVENT_PTR(_id, _p)
