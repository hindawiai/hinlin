<शैली गुरु>
/*
 * Perक्रमmance events x86 architecture code
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2009 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2009 Jaswinder Singh Rajput
 *  Copyright (C) 2009 Advanced Micro Devices, Inc., Robert Richter
 *  Copyright (C) 2008-2009 Red Hat, Inc., Peter Zijlstra
 *  Copyright (C) 2009 Intel Corporation, <markus.t.metzger@पूर्णांकel.com>
 *  Copyright (C) 2009 Google, Inc., Stephane Eranian
 *
 *  For licencing details see kernel-base/COPYING
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/capability.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/nospec.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/unwind.h>

#समावेश "perf_event.h"

काष्ठा x86_pmu x86_pmu __पढ़ो_mostly;
अटल काष्ठा pmu pmu;

DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events) = अणु
	.enabled = 1,
	.pmu = &pmu,
पूर्ण;

DEFINE_STATIC_KEY_FALSE(rdpmc_never_available_key);
DEFINE_STATIC_KEY_FALSE(rdpmc_always_available_key);
DEFINE_STATIC_KEY_FALSE(perf_is_hybrid);

/*
 * This here uses DEFINE_STATIC_CALL_शून्य() to get a अटल_call defined
 * from just a typename, as opposed to an actual function.
 */
DEFINE_STATIC_CALL_शून्य(x86_pmu_handle_irq,  *x86_pmu.handle_irq);
DEFINE_STATIC_CALL_शून्य(x86_pmu_disable_all, *x86_pmu.disable_all);
DEFINE_STATIC_CALL_शून्य(x86_pmu_enable_all,  *x86_pmu.enable_all);
DEFINE_STATIC_CALL_शून्य(x86_pmu_enable,	     *x86_pmu.enable);
DEFINE_STATIC_CALL_शून्य(x86_pmu_disable,     *x86_pmu.disable);

DEFINE_STATIC_CALL_शून्य(x86_pmu_add,  *x86_pmu.add);
DEFINE_STATIC_CALL_शून्य(x86_pmu_del,  *x86_pmu.del);
DEFINE_STATIC_CALL_शून्य(x86_pmu_पढ़ो, *x86_pmu.पढ़ो);

DEFINE_STATIC_CALL_शून्य(x86_pmu_schedule_events,       *x86_pmu.schedule_events);
DEFINE_STATIC_CALL_शून्य(x86_pmu_get_event_स्थिरraपूर्णांकs, *x86_pmu.get_event_स्थिरraपूर्णांकs);
DEFINE_STATIC_CALL_शून्य(x86_pmu_put_event_स्थिरraपूर्णांकs, *x86_pmu.put_event_स्थिरraपूर्णांकs);

DEFINE_STATIC_CALL_शून्य(x86_pmu_start_scheduling,  *x86_pmu.start_scheduling);
DEFINE_STATIC_CALL_शून्य(x86_pmu_commit_scheduling, *x86_pmu.commit_scheduling);
DEFINE_STATIC_CALL_शून्य(x86_pmu_stop_scheduling,   *x86_pmu.stop_scheduling);

DEFINE_STATIC_CALL_शून्य(x86_pmu_sched_task,    *x86_pmu.sched_task);
DEFINE_STATIC_CALL_शून्य(x86_pmu_swap_task_ctx, *x86_pmu.swap_task_ctx);

DEFINE_STATIC_CALL_शून्य(x86_pmu_drain_pebs,   *x86_pmu.drain_pebs);
DEFINE_STATIC_CALL_शून्य(x86_pmu_pebs_aliases, *x86_pmu.pebs_aliases);

/*
 * This one is magic, it will get called even when PMU init fails (because
 * there is no PMU), in which हाल it should simply वापस शून्य.
 */
DEFINE_STATIC_CALL_RET0(x86_pmu_guest_get_msrs, *x86_pmu.guest_get_msrs);

u64 __पढ़ो_mostly hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];
u64 __पढ़ो_mostly hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];

/*
 * Propagate event elapsed समय पूर्णांकo the generic event.
 * Can only be executed on the CPU where the event is active.
 * Returns the delta events processed.
 */
u64 x86_perf_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक shअगरt = 64 - x86_pmu.cntval_bits;
	u64 prev_raw_count, new_raw_count;
	u64 delta;

	अगर (unlikely(!hwc->event_base))
		वापस 0;

	अगर (unlikely(is_topकरोwn_count(event)) && x86_pmu.update_topकरोwn_event)
		वापस x86_pmu.update_topकरोwn_event(event);

	/*
	 * Careful: an NMI might modअगरy the previous event value.
	 *
	 * Our tactic to handle this is to first atomically पढ़ो and
	 * exchange a new raw count - then add that new-prev delta
	 * count to the generic event atomically:
	 */
again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	rdpmcl(hwc->event_base_rdpmc, new_raw_count);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
					new_raw_count) != prev_raw_count)
		जाओ again;

	/*
	 * Now we have the new raw value and have updated the prev
	 * बारtamp alपढ़ोy. We can now calculate the elapsed delta
	 * (event-)समय and add that to the generic event.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shअगरt) - (prev_raw_count << shअगरt);
	delta >>= shअगरt;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस new_raw_count;
पूर्ण

/*
 * Find and validate any extra रेजिस्टरs to set up.
 */
अटल पूर्णांक x86_pmu_extra_regs(u64 config, काष्ठा perf_event *event)
अणु
	काष्ठा extra_reg *extra_regs = hybrid(event->pmu, extra_regs);
	काष्ठा hw_perf_event_extra *reg;
	काष्ठा extra_reg *er;

	reg = &event->hw.extra_reg;

	अगर (!extra_regs)
		वापस 0;

	क्रम (er = extra_regs; er->msr; er++) अणु
		अगर (er->event != (config & er->config_mask))
			जारी;
		अगर (event->attr.config1 & ~er->valid_mask)
			वापस -EINVAL;
		/* Check अगर the extra msrs can be safely accessed*/
		अगर (!er->extra_msr_access)
			वापस -ENXIO;

		reg->idx = er->idx;
		reg->config = event->attr.config1;
		reg->reg = er->msr;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल atomic_t active_events;
अटल atomic_t pmc_refcount;
अटल DEFINE_MUTEX(pmc_reserve_mutex);

#अगर_घोषित CONFIG_X86_LOCAL_APIC

अटल अंतरभूत पूर्णांक get_possible_num_counters(व्योम)
अणु
	पूर्णांक i, num_counters = x86_pmu.num_counters;

	अगर (!is_hybrid())
		वापस num_counters;

	क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++)
		num_counters = max_t(पूर्णांक, num_counters, x86_pmu.hybrid_pmu[i].num_counters);

	वापस num_counters;
पूर्ण

अटल bool reserve_pmc_hardware(व्योम)
अणु
	पूर्णांक i, num_counters = get_possible_num_counters();

	क्रम (i = 0; i < num_counters; i++) अणु
		अगर (!reserve_perfctr_nmi(x86_pmu_event_addr(i)))
			जाओ perfctr_fail;
	पूर्ण

	क्रम (i = 0; i < num_counters; i++) अणु
		अगर (!reserve_evntsel_nmi(x86_pmu_config_addr(i)))
			जाओ eventsel_fail;
	पूर्ण

	वापस true;

eventsel_fail:
	क्रम (i--; i >= 0; i--)
		release_evntsel_nmi(x86_pmu_config_addr(i));

	i = num_counters;

perfctr_fail:
	क्रम (i--; i >= 0; i--)
		release_perfctr_nmi(x86_pmu_event_addr(i));

	वापस false;
पूर्ण

अटल व्योम release_pmc_hardware(व्योम)
अणु
	पूर्णांक i, num_counters = get_possible_num_counters();

	क्रम (i = 0; i < num_counters; i++) अणु
		release_perfctr_nmi(x86_pmu_event_addr(i));
		release_evntsel_nmi(x86_pmu_config_addr(i));
	पूर्ण
पूर्ण

#अन्यथा

अटल bool reserve_pmc_hardware(व्योम) अणु वापस true; पूर्ण
अटल व्योम release_pmc_hardware(व्योम) अणुपूर्ण

#पूर्ण_अगर

bool check_hw_exists(काष्ठा pmu *pmu, पूर्णांक num_counters, पूर्णांक num_counters_fixed)
अणु
	u64 val, val_fail = -1, val_new= ~0;
	पूर्णांक i, reg, reg_fail = -1, ret = 0;
	पूर्णांक bios_fail = 0;
	पूर्णांक reg_safe = -1;

	/*
	 * Check to see अगर the BIOS enabled any of the counters, अगर so
	 * complain and bail.
	 */
	क्रम (i = 0; i < num_counters; i++) अणु
		reg = x86_pmu_config_addr(i);
		ret = rdmsrl_safe(reg, &val);
		अगर (ret)
			जाओ msr_fail;
		अगर (val & ARCH_PERFMON_EVENTSEL_ENABLE) अणु
			bios_fail = 1;
			val_fail = val;
			reg_fail = reg;
		पूर्ण अन्यथा अणु
			reg_safe = i;
		पूर्ण
	पूर्ण

	अगर (num_counters_fixed) अणु
		reg = MSR_ARCH_PERFMON_FIXED_CTR_CTRL;
		ret = rdmsrl_safe(reg, &val);
		अगर (ret)
			जाओ msr_fail;
		क्रम (i = 0; i < num_counters_fixed; i++) अणु
			अगर (fixed_counter_disabled(i, pmu))
				जारी;
			अगर (val & (0x03ULL << i*4)) अणु
				bios_fail = 1;
				val_fail = val;
				reg_fail = reg;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If all the counters are enabled, the below test will always
	 * fail.  The tools will also become useless in this scenario.
	 * Just fail and disable the hardware counters.
	 */

	अगर (reg_safe == -1) अणु
		reg = reg_safe;
		जाओ msr_fail;
	पूर्ण

	/*
	 * Read the current value, change it and पढ़ो it back to see अगर it
	 * matches, this is needed to detect certain hardware emulators
	 * (qemu/kvm) that करोn't trap on the MSR access and always वापस 0s.
	 */
	reg = x86_pmu_event_addr(reg_safe);
	अगर (rdmsrl_safe(reg, &val))
		जाओ msr_fail;
	val ^= 0xffffUL;
	ret = wrmsrl_safe(reg, val);
	ret |= rdmsrl_safe(reg, &val_new);
	अगर (ret || val != val_new)
		जाओ msr_fail;

	/*
	 * We still allow the PMU driver to operate:
	 */
	अगर (bios_fail) अणु
		pr_cont("Broken BIOS detected, complain to your hardware vendor.\n");
		pr_err(FW_BUG "the BIOS has corrupted hw-PMU resources (MSR %x is %Lx)\n",
			      reg_fail, val_fail);
	पूर्ण

	वापस true;

msr_fail:
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		pr_cont("PMU not available due to virtualization, using software events only.\n");
	पूर्ण अन्यथा अणु
		pr_cont("Broken PMU hardware detected, using software events only.\n");
		pr_err("Failed to access perfctr msr (MSR %x is %Lx)\n",
		       reg, val_new);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	x86_release_hardware();
	atomic_dec(&active_events);
पूर्ण

व्योम hw_perf_lbr_event_destroy(काष्ठा perf_event *event)
अणु
	hw_perf_event_destroy(event);

	/* unकरो the lbr/bts event accounting */
	x86_del_exclusive(x86_lbr_exclusive_lbr);
पूर्ण

अटल अंतरभूत पूर्णांक x86_pmu_initialized(व्योम)
अणु
	वापस x86_pmu.handle_irq != शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
set_ext_hw_attr(काष्ठा hw_perf_event *hwc, काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;
	u64 config, val;

	config = attr->config;

	cache_type = (config >> 0) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस -EINVAL;
	cache_type = array_index_nospec(cache_type, PERF_COUNT_HW_CACHE_MAX);

	cache_op = (config >>  8) & 0xff;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस -EINVAL;
	cache_op = array_index_nospec(cache_op, PERF_COUNT_HW_CACHE_OP_MAX);

	cache_result = (config >> 16) & 0xff;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;
	cache_result = array_index_nospec(cache_result, PERF_COUNT_HW_CACHE_RESULT_MAX);

	val = hybrid_var(event->pmu, hw_cache_event_ids)[cache_type][cache_op][cache_result];
	अगर (val == 0)
		वापस -ENOENT;

	अगर (val == -1)
		वापस -EINVAL;

	hwc->config |= val;
	attr->config1 = hybrid_var(event->pmu, hw_cache_extra_regs)[cache_type][cache_op][cache_result];
	वापस x86_pmu_extra_regs(val, event);
पूर्ण

पूर्णांक x86_reserve_hardware(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (!atomic_inc_not_zero(&pmc_refcount)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&pmc_refcount) == 0) अणु
			अगर (!reserve_pmc_hardware()) अणु
				err = -EBUSY;
			पूर्ण अन्यथा अणु
				reserve_ds_buffers();
				reserve_lbr_buffers();
			पूर्ण
		पूर्ण
		अगर (!err)
			atomic_inc(&pmc_refcount);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण

	वापस err;
पूर्ण

व्योम x86_release_hardware(व्योम)
अणु
	अगर (atomic_dec_and_mutex_lock(&pmc_refcount, &pmc_reserve_mutex)) अणु
		release_pmc_hardware();
		release_ds_buffers();
		release_lbr_buffers();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

/*
 * Check अगर we can create event of a certain type (that no conflicting events
 * are present).
 */
पूर्णांक x86_add_exclusive(अचिन्हित पूर्णांक what)
अणु
	पूर्णांक i;

	/*
	 * When lbr_pt_coexist we allow PT to coexist with either LBR or BTS.
	 * LBR and BTS are still mutually exclusive.
	 */
	अगर (x86_pmu.lbr_pt_coexist && what == x86_lbr_exclusive_pt)
		जाओ out;

	अगर (!atomic_inc_not_zero(&x86_pmu.lbr_exclusive[what])) अणु
		mutex_lock(&pmc_reserve_mutex);
		क्रम (i = 0; i < ARRAY_SIZE(x86_pmu.lbr_exclusive); i++) अणु
			अगर (i != what && atomic_पढ़ो(&x86_pmu.lbr_exclusive[i]))
				जाओ fail_unlock;
		पूर्ण
		atomic_inc(&x86_pmu.lbr_exclusive[what]);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण

out:
	atomic_inc(&active_events);
	वापस 0;

fail_unlock:
	mutex_unlock(&pmc_reserve_mutex);
	वापस -EBUSY;
पूर्ण

व्योम x86_del_exclusive(अचिन्हित पूर्णांक what)
अणु
	atomic_dec(&active_events);

	/*
	 * See the comment in x86_add_exclusive().
	 */
	अगर (x86_pmu.lbr_pt_coexist && what == x86_lbr_exclusive_pt)
		वापस;

	atomic_dec(&x86_pmu.lbr_exclusive[what]);
पूर्ण

पूर्णांक x86_setup_perfctr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 config;

	अगर (!is_sampling_event(event)) अणु
		hwc->sample_period = x86_pmu.max_period;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	अगर (attr->type == event->pmu->type)
		वापस x86_pmu_extra_regs(event->attr.config, event);

	अगर (attr->type == PERF_TYPE_HW_CACHE)
		वापस set_ext_hw_attr(hwc, event);

	अगर (attr->config >= x86_pmu.max_events)
		वापस -EINVAL;

	attr->config = array_index_nospec((अचिन्हित दीर्घ)attr->config, x86_pmu.max_events);

	/*
	 * The generic map:
	 */
	config = x86_pmu.event_map(attr->config);

	अगर (config == 0)
		वापस -ENOENT;

	अगर (config == -1LL)
		वापस -EINVAL;

	hwc->config |= config;

	वापस 0;
पूर्ण

/*
 * check that branch_sample_type is compatible with
 * settings needed क्रम precise_ip > 1 which implies
 * using the LBR to capture ALL taken branches at the
 * priv levels of the measurement
 */
अटल अंतरभूत पूर्णांक precise_br_compat(काष्ठा perf_event *event)
अणु
	u64 m = event->attr.branch_sample_type;
	u64 b = 0;

	/* must capture all branches */
	अगर (!(m & PERF_SAMPLE_BRANCH_ANY))
		वापस 0;

	m &= PERF_SAMPLE_BRANCH_KERNEL | PERF_SAMPLE_BRANCH_USER;

	अगर (!event->attr.exclude_user)
		b |= PERF_SAMPLE_BRANCH_USER;

	अगर (!event->attr.exclude_kernel)
		b |= PERF_SAMPLE_BRANCH_KERNEL;

	/*
	 * ignore PERF_SAMPLE_BRANCH_HV, not supported on x86
	 */

	वापस m == b;
पूर्ण

पूर्णांक x86_pmu_max_precise(व्योम)
अणु
	पूर्णांक precise = 0;

	/* Support क्रम स्थिरant skid */
	अगर (x86_pmu.pebs_active && !x86_pmu.pebs_broken) अणु
		precise++;

		/* Support क्रम IP fixup */
		अगर (x86_pmu.lbr_nr || x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 2)
			precise++;

		अगर (x86_pmu.pebs_prec_dist)
			precise++;
	पूर्ण
	वापस precise;
पूर्ण

पूर्णांक x86_pmu_hw_config(काष्ठा perf_event *event)
अणु
	अगर (event->attr.precise_ip) अणु
		पूर्णांक precise = x86_pmu_max_precise();

		अगर (event->attr.precise_ip > precise)
			वापस -EOPNOTSUPP;

		/* There's no sense in having PEBS क्रम non sampling events: */
		अगर (!is_sampling_event(event))
			वापस -EINVAL;
	पूर्ण
	/*
	 * check that PEBS LBR correction करोes not conflict with
	 * whatever the user is asking with attr->branch_sample_type
	 */
	अगर (event->attr.precise_ip > 1 && x86_pmu.पूर्णांकel_cap.pebs_क्रमmat < 2) अणु
		u64 *br_type = &event->attr.branch_sample_type;

		अगर (has_branch_stack(event)) अणु
			अगर (!precise_br_compat(event))
				वापस -EOPNOTSUPP;

			/* branch_sample_type is compatible */

		पूर्ण अन्यथा अणु
			/*
			 * user did not specअगरy  branch_sample_type
			 *
			 * For PEBS fixups, we capture all
			 * the branches at the priv level of the
			 * event.
			 */
			*br_type = PERF_SAMPLE_BRANCH_ANY;

			अगर (!event->attr.exclude_user)
				*br_type |= PERF_SAMPLE_BRANCH_USER;

			अगर (!event->attr.exclude_kernel)
				*br_type |= PERF_SAMPLE_BRANCH_KERNEL;
		पूर्ण
	पूर्ण

	अगर (event->attr.branch_sample_type & PERF_SAMPLE_BRANCH_CALL_STACK)
		event->attach_state |= PERF_ATTACH_TASK_DATA;

	/*
	 * Generate PMC IRQs:
	 * (keep 'enabled' bit clear क्रम now)
	 */
	event->hw.config = ARCH_PERFMON_EVENTSEL_INT;

	/*
	 * Count user and OS events unless requested not to
	 */
	अगर (!event->attr.exclude_user)
		event->hw.config |= ARCH_PERFMON_EVENTSEL_USR;
	अगर (!event->attr.exclude_kernel)
		event->hw.config |= ARCH_PERFMON_EVENTSEL_OS;

	अगर (event->attr.type == event->pmu->type)
		event->hw.config |= event->attr.config & X86_RAW_EVENT_MASK;

	अगर (event->attr.sample_period && x86_pmu.limit_period) अणु
		अगर (x86_pmu.limit_period(event, event->attr.sample_period) >
				event->attr.sample_period)
			वापस -EINVAL;
	पूर्ण

	/* sample_regs_user never support XMM रेजिस्टरs */
	अगर (unlikely(event->attr.sample_regs_user & PERF_REG_EXTENDED_MASK))
		वापस -EINVAL;
	/*
	 * Besides the general purpose रेजिस्टरs, XMM रेजिस्टरs may
	 * be collected in PEBS on some platक्रमms, e.g. Icelake
	 */
	अगर (unlikely(event->attr.sample_regs_पूर्णांकr & PERF_REG_EXTENDED_MASK)) अणु
		अगर (!(event->pmu->capabilities & PERF_PMU_CAP_EXTENDED_REGS))
			वापस -EINVAL;

		अगर (!event->attr.precise_ip)
			वापस -EINVAL;
	पूर्ण

	वापस x86_setup_perfctr(event);
पूर्ण

/*
 * Setup the hardware configuration क्रम a given attr_type
 */
अटल पूर्णांक __x86_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;

	अगर (!x86_pmu_initialized())
		वापस -ENODEV;

	err = x86_reserve_hardware();
	अगर (err)
		वापस err;

	atomic_inc(&active_events);
	event->destroy = hw_perf_event_destroy;

	event->hw.idx = -1;
	event->hw.last_cpu = -1;
	event->hw.last_tag = ~0ULL;

	/* mark unused */
	event->hw.extra_reg.idx = EXTRA_REG_NONE;
	event->hw.branch_reg.idx = EXTRA_REG_NONE;

	वापस x86_pmu.hw_config(event);
पूर्ण

व्योम x86_pmu_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		काष्ठा hw_perf_event *hwc = &cpuc->events[idx]->hw;
		u64 val;

		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;
		rdmsrl(x86_pmu_config_addr(idx), val);
		अगर (!(val & ARCH_PERFMON_EVENTSEL_ENABLE))
			जारी;
		val &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
		wrmsrl(x86_pmu_config_addr(idx), val);
		अगर (is_counter_pair(hwc))
			wrmsrl(x86_pmu_config_addr(idx + 1), 0);
	पूर्ण
पूर्ण

काष्ठा perf_guest_चयन_msr *perf_guest_get_msrs(पूर्णांक *nr)
अणु
	वापस अटल_call(x86_pmu_guest_get_msrs)(nr);
पूर्ण
EXPORT_SYMBOL_GPL(perf_guest_get_msrs);

/*
 * There may be PMI landing after enabled=0. The PMI hitting could be beक्रमe or
 * after disable_all.
 *
 * If PMI hits beक्रमe disable_all, the PMU will be disabled in the NMI handler.
 * It will not be re-enabled in the NMI handler again, because enabled=0. After
 * handling the NMI, disable_all will be called, which will not change the
 * state either. If PMI hits after disable_all, the PMU is alपढ़ोy disabled
 * beक्रमe entering NMI handler. The NMI handler will not change the state
 * either.
 *
 * So either situation is harmless.
 */
अटल व्योम x86_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!x86_pmu_initialized())
		वापस;

	अगर (!cpuc->enabled)
		वापस;

	cpuc->n_added = 0;
	cpuc->enabled = 0;
	barrier();

	अटल_call(x86_pmu_disable_all)();
पूर्ण

व्योम x86_pmu_enable_all(पूर्णांक added)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		काष्ठा hw_perf_event *hwc = &cpuc->events[idx]->hw;

		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;

		__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_x86_event(काष्ठा perf_event *event)
अणु
	पूर्णांक i;

	अगर (!is_hybrid())
		वापस event->pmu == &pmu;

	क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++) अणु
		अगर (event->pmu == &x86_pmu.hybrid_pmu[i].pmu)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा pmu *x86_get_pmu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);

	/*
	 * All CPUs of the hybrid type have been offline.
	 * The x86_get_pmu() should not be invoked.
	 */
	अगर (WARN_ON_ONCE(!cpuc->pmu))
		वापस &pmu;

	वापस cpuc->pmu;
पूर्ण
/*
 * Event scheduler state:
 *
 * Assign events iterating over all events and counters, beginning
 * with events with least weights first. Keep the current iterator
 * state in काष्ठा sched_state.
 */
काष्ठा sched_state अणु
	पूर्णांक	weight;
	पूर्णांक	event;		/* event index */
	पूर्णांक	counter;	/* counter index */
	पूर्णांक	unasचिन्हित;	/* number of events to be asचिन्हित left */
	पूर्णांक	nr_gp;		/* number of GP counters used */
	u64	used;
पूर्ण;

/* Total max is X86_PMC_IDX_MAX, but we are O(n!) limited */
#घोषणा	SCHED_STATES_MAX	2

काष्ठा perf_sched अणु
	पूर्णांक			max_weight;
	पूर्णांक			max_events;
	पूर्णांक			max_gp;
	पूर्णांक			saved_states;
	काष्ठा event_स्थिरraपूर्णांक	**स्थिरraपूर्णांकs;
	काष्ठा sched_state	state;
	काष्ठा sched_state	saved[SCHED_STATES_MAX];
पूर्ण;

/*
 * Initialize iterator that runs through all events and counters.
 */
अटल व्योम perf_sched_init(काष्ठा perf_sched *sched, काष्ठा event_स्थिरraपूर्णांक **स्थिरraपूर्णांकs,
			    पूर्णांक num, पूर्णांक wmin, पूर्णांक wmax, पूर्णांक gpmax)
अणु
	पूर्णांक idx;

	स_रखो(sched, 0, माप(*sched));
	sched->max_events	= num;
	sched->max_weight	= wmax;
	sched->max_gp		= gpmax;
	sched->स्थिरraपूर्णांकs	= स्थिरraपूर्णांकs;

	क्रम (idx = 0; idx < num; idx++) अणु
		अगर (स्थिरraपूर्णांकs[idx]->weight == wmin)
			अवरोध;
	पूर्ण

	sched->state.event	= idx;		/* start with min weight */
	sched->state.weight	= wmin;
	sched->state.unasचिन्हित	= num;
पूर्ण

अटल व्योम perf_sched_save_state(काष्ठा perf_sched *sched)
अणु
	अगर (WARN_ON_ONCE(sched->saved_states >= SCHED_STATES_MAX))
		वापस;

	sched->saved[sched->saved_states] = sched->state;
	sched->saved_states++;
पूर्ण

अटल bool perf_sched_restore_state(काष्ठा perf_sched *sched)
अणु
	अगर (!sched->saved_states)
		वापस false;

	sched->saved_states--;
	sched->state = sched->saved[sched->saved_states];

	/* this assignment didn't work out */
	/* XXX broken vs EVENT_PAIR */
	sched->state.used &= ~BIT_ULL(sched->state.counter);

	/* try the next one */
	sched->state.counter++;

	वापस true;
पूर्ण

/*
 * Select a counter क्रम the current event to schedule. Return true on
 * success.
 */
अटल bool __perf_sched_find_counter(काष्ठा perf_sched *sched)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;
	पूर्णांक idx;

	अगर (!sched->state.unasचिन्हित)
		वापस false;

	अगर (sched->state.event >= sched->max_events)
		वापस false;

	c = sched->स्थिरraपूर्णांकs[sched->state.event];
	/* Prefer fixed purpose counters */
	अगर (c->idxmsk64 & (~0ULL << INTEL_PMC_IDX_FIXED)) अणु
		idx = INTEL_PMC_IDX_FIXED;
		क्रम_each_set_bit_from(idx, c->idxmsk, X86_PMC_IDX_MAX) अणु
			u64 mask = BIT_ULL(idx);

			अगर (sched->state.used & mask)
				जारी;

			sched->state.used |= mask;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* Grab the first unused counter starting with idx */
	idx = sched->state.counter;
	क्रम_each_set_bit_from(idx, c->idxmsk, INTEL_PMC_IDX_FIXED) अणु
		u64 mask = BIT_ULL(idx);

		अगर (c->flags & PERF_X86_EVENT_PAIR)
			mask |= mask << 1;

		अगर (sched->state.used & mask)
			जारी;

		अगर (sched->state.nr_gp++ >= sched->max_gp)
			वापस false;

		sched->state.used |= mask;
		जाओ करोne;
	पूर्ण

	वापस false;

करोne:
	sched->state.counter = idx;

	अगर (c->overlap)
		perf_sched_save_state(sched);

	वापस true;
पूर्ण

अटल bool perf_sched_find_counter(काष्ठा perf_sched *sched)
अणु
	जबतक (!__perf_sched_find_counter(sched)) अणु
		अगर (!perf_sched_restore_state(sched))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Go through all unasचिन्हित events and find the next one to schedule.
 * Take events with the least weight first. Return true on success.
 */
अटल bool perf_sched_next_event(काष्ठा perf_sched *sched)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (!sched->state.unasचिन्हित || !--sched->state.unasचिन्हित)
		वापस false;

	करो अणु
		/* next event */
		sched->state.event++;
		अगर (sched->state.event >= sched->max_events) अणु
			/* next weight */
			sched->state.event = 0;
			sched->state.weight++;
			अगर (sched->state.weight > sched->max_weight)
				वापस false;
		पूर्ण
		c = sched->स्थिरraपूर्णांकs[sched->state.event];
	पूर्ण जबतक (c->weight != sched->state.weight);

	sched->state.counter = 0;	/* start with first counter */

	वापस true;
पूर्ण

/*
 * Assign a counter क्रम each event.
 */
पूर्णांक perf_assign_events(काष्ठा event_स्थिरraपूर्णांक **स्थिरraपूर्णांकs, पूर्णांक n,
			पूर्णांक wmin, पूर्णांक wmax, पूर्णांक gpmax, पूर्णांक *assign)
अणु
	काष्ठा perf_sched sched;

	perf_sched_init(&sched, स्थिरraपूर्णांकs, n, wmin, wmax, gpmax);

	करो अणु
		अगर (!perf_sched_find_counter(&sched))
			अवरोध;	/* failed */
		अगर (assign)
			assign[sched.state.event] = sched.state.counter;
	पूर्ण जबतक (perf_sched_next_event(&sched));

	वापस sched.state.unasचिन्हित;
पूर्ण
EXPORT_SYMBOL_GPL(perf_assign_events);

पूर्णांक x86_schedule_events(काष्ठा cpu_hw_events *cpuc, पूर्णांक n, पूर्णांक *assign)
अणु
	पूर्णांक num_counters = hybrid(cpuc->pmu, num_counters);
	काष्ठा event_स्थिरraपूर्णांक *c;
	काष्ठा perf_event *e;
	पूर्णांक n0, i, wmin, wmax, unsched = 0;
	काष्ठा hw_perf_event *hwc;
	u64 used_mask = 0;

	/*
	 * Compute the number of events alपढ़ोy present; see x86_pmu_add(),
	 * validate_group() and x86_pmu_commit_txn(). For the क्रमmer two
	 * cpuc->n_events hasn't been updated yet, जबतक क्रम the latter
	 * cpuc->n_txn contains the number of events added in the current
	 * transaction.
	 */
	n0 = cpuc->n_events;
	अगर (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		n0 -= cpuc->n_txn;

	अटल_call_cond(x86_pmu_start_scheduling)(cpuc);

	क्रम (i = 0, wmin = X86_PMC_IDX_MAX, wmax = 0; i < n; i++) अणु
		c = cpuc->event_स्थिरraपूर्णांक[i];

		/*
		 * Previously scheduled events should have a cached स्थिरraपूर्णांक,
		 * जबतक new events should not have one.
		 */
		WARN_ON_ONCE((c && i >= n0) || (!c && i < n0));

		/*
		 * Request स्थिरraपूर्णांकs क्रम new events; or क्रम those events that
		 * have a dynamic स्थिरraपूर्णांक -- क्रम those the स्थिरraपूर्णांक can
		 * change due to बाह्यal factors (sibling state, allow_tfa).
		 */
		अगर (!c || (c->flags & PERF_X86_EVENT_DYNAMIC)) अणु
			c = अटल_call(x86_pmu_get_event_स्थिरraपूर्णांकs)(cpuc, i, cpuc->event_list[i]);
			cpuc->event_स्थिरraपूर्णांक[i] = c;
		पूर्ण

		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	पूर्ण

	/*
	 * fastpath, try to reuse previous रेजिस्टर
	 */
	क्रम (i = 0; i < n; i++) अणु
		u64 mask;

		hwc = &cpuc->event_list[i]->hw;
		c = cpuc->event_स्थिरraपूर्णांक[i];

		/* never asचिन्हित */
		अगर (hwc->idx == -1)
			अवरोध;

		/* स्थिरraपूर्णांक still honored */
		अगर (!test_bit(hwc->idx, c->idxmsk))
			अवरोध;

		mask = BIT_ULL(hwc->idx);
		अगर (is_counter_pair(hwc))
			mask |= mask << 1;

		/* not alपढ़ोy used */
		अगर (used_mask & mask)
			अवरोध;

		used_mask |= mask;

		अगर (assign)
			assign[i] = hwc->idx;
	पूर्ण

	/* slow path */
	अगर (i != n) अणु
		पूर्णांक gpmax = num_counters;

		/*
		 * Do not allow scheduling of more than half the available
		 * generic counters.
		 *
		 * This helps aव्योम counter starvation of sibling thपढ़ो by
		 * ensuring at most half the counters cannot be in exclusive
		 * mode. There is no designated counters क्रम the limits. Any
		 * N/2 counters can be used. This helps with events with
		 * specअगरic counter स्थिरraपूर्णांकs.
		 */
		अगर (is_ht_workaround_enabled() && !cpuc->is_fake &&
		    READ_ONCE(cpuc->excl_cntrs->exclusive_present))
			gpmax /= 2;

		/*
		 * Reduce the amount of available counters to allow fitting
		 * the extra Merge events needed by large increment events.
		 */
		अगर (x86_pmu.flags & PMU_FL_PAIR) अणु
			gpmax = num_counters - cpuc->n_pair;
			WARN_ON(gpmax <= 0);
		पूर्ण

		unsched = perf_assign_events(cpuc->event_स्थिरraपूर्णांक, n, wmin,
					     wmax, gpmax, assign);
	पूर्ण

	/*
	 * In हाल of success (unsched = 0), mark events as committed,
	 * so we करो not put_स्थिरraपूर्णांक() in हाल new events are added
	 * and fail to be scheduled
	 *
	 * We invoke the lower level commit callback to lock the resource
	 *
	 * We करो not need to करो all of this in हाल we are called to
	 * validate an event group (assign == शून्य)
	 */
	अगर (!unsched && assign) अणु
		क्रम (i = 0; i < n; i++) अणु
			e = cpuc->event_list[i];
			अटल_call_cond(x86_pmu_commit_scheduling)(cpuc, i, assign[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = n0; i < n; i++) अणु
			e = cpuc->event_list[i];

			/*
			 * release events that failed scheduling
			 */
			अटल_call_cond(x86_pmu_put_event_स्थिरraपूर्णांकs)(cpuc, e);

			cpuc->event_स्थिरraपूर्णांक[i] = शून्य;
		पूर्ण
	पूर्ण

	अटल_call_cond(x86_pmu_stop_scheduling)(cpuc);

	वापस unsched ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक add_nr_metric_event(काष्ठा cpu_hw_events *cpuc,
			       काष्ठा perf_event *event)
अणु
	अगर (is_metric_event(event)) अणु
		अगर (cpuc->n_metric == INTEL_TD_METRIC_NUM)
			वापस -EINVAL;
		cpuc->n_metric++;
		cpuc->n_txn_metric++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम del_nr_metric_event(काष्ठा cpu_hw_events *cpuc,
				काष्ठा perf_event *event)
अणु
	अगर (is_metric_event(event))
		cpuc->n_metric--;
पूर्ण

अटल पूर्णांक collect_event(काष्ठा cpu_hw_events *cpuc, काष्ठा perf_event *event,
			 पूर्णांक max_count, पूर्णांक n)
अणु
	जोड़ perf_capabilities पूर्णांकel_cap = hybrid(cpuc->pmu, पूर्णांकel_cap);

	अगर (पूर्णांकel_cap.perf_metrics && add_nr_metric_event(cpuc, event))
		वापस -EINVAL;

	अगर (n >= max_count + cpuc->n_metric)
		वापस -EINVAL;

	cpuc->event_list[n] = event;
	अगर (is_counter_pair(&event->hw)) अणु
		cpuc->n_pair++;
		cpuc->n_txn_pair++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * करोgrp: true अगर must collect siblings events (group)
 * वापसs total number of events and error code
 */
अटल पूर्णांक collect_events(काष्ठा cpu_hw_events *cpuc, काष्ठा perf_event *leader, bool करोgrp)
अणु
	पूर्णांक num_counters = hybrid(cpuc->pmu, num_counters);
	पूर्णांक num_counters_fixed = hybrid(cpuc->pmu, num_counters_fixed);
	काष्ठा perf_event *event;
	पूर्णांक n, max_count;

	max_count = num_counters + num_counters_fixed;

	/* current number of events alपढ़ोy accepted */
	n = cpuc->n_events;
	अगर (!cpuc->n_events)
		cpuc->pebs_output = 0;

	अगर (!cpuc->is_fake && leader->attr.precise_ip) अणु
		/*
		 * For PEBS->PT, अगर !aux_event, the group leader (PT) went
		 * away, the group was broken करोwn and this singleton event
		 * can't schedule any more.
		 */
		अगर (is_pebs_pt(leader) && !leader->aux_event)
			वापस -EINVAL;

		/*
		 * pebs_output: 0: no PEBS so far, 1: PT, 2: DS
		 */
		अगर (cpuc->pebs_output &&
		    cpuc->pebs_output != is_pebs_pt(leader) + 1)
			वापस -EINVAL;

		cpuc->pebs_output = is_pebs_pt(leader) + 1;
	पूर्ण

	अगर (is_x86_event(leader)) अणु
		अगर (collect_event(cpuc, leader, max_count, n))
			वापस -EINVAL;
		n++;
	पूर्ण

	अगर (!करोgrp)
		वापस n;

	क्रम_each_sibling_event(event, leader) अणु
		अगर (!is_x86_event(event) || event->state <= PERF_EVENT_STATE_OFF)
			जारी;

		अगर (collect_event(cpuc, event, max_count, n))
			वापस -EINVAL;

		n++;
	पूर्ण
	वापस n;
पूर्ण

अटल अंतरभूत व्योम x86_assign_hw_event(काष्ठा perf_event *event,
				काष्ठा cpu_hw_events *cpuc, पूर्णांक i)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;

	idx = hwc->idx = cpuc->assign[i];
	hwc->last_cpu = smp_processor_id();
	hwc->last_tag = ++cpuc->tags[i];

	चयन (hwc->idx) अणु
	हाल INTEL_PMC_IDX_FIXED_BTS:
	हाल INTEL_PMC_IDX_FIXED_VLBR:
		hwc->config_base = 0;
		hwc->event_base	= 0;
		अवरोध;

	हाल INTEL_PMC_IDX_METRIC_BASE ... INTEL_PMC_IDX_METRIC_END:
		/* All the metric events are mapped onto the fixed counter 3. */
		idx = INTEL_PMC_IDX_FIXED_SLOTS;
		fallthrough;
	हाल INTEL_PMC_IDX_FIXED ... INTEL_PMC_IDX_FIXED_BTS-1:
		hwc->config_base = MSR_ARCH_PERFMON_FIXED_CTR_CTRL;
		hwc->event_base = MSR_ARCH_PERFMON_FIXED_CTR0 +
				(idx - INTEL_PMC_IDX_FIXED);
		hwc->event_base_rdpmc = (idx - INTEL_PMC_IDX_FIXED) |
					INTEL_PMC_FIXED_RDPMC_BASE;
		अवरोध;

	शेष:
		hwc->config_base = x86_pmu_config_addr(hwc->idx);
		hwc->event_base  = x86_pmu_event_addr(hwc->idx);
		hwc->event_base_rdpmc = x86_pmu_rdpmc_index(hwc->idx);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * x86_perf_rdpmc_index - Return PMC counter used क्रम event
 * @event: the perf_event to which the PMC counter was asचिन्हित
 *
 * The counter asचिन्हित to this perक्रमmance event may change अगर पूर्णांकerrupts
 * are enabled. This counter should thus never be used जबतक पूर्णांकerrupts are
 * enabled. Beक्रमe this function is used to obtain the asचिन्हित counter the
 * event should be checked क्रम validity using, क्रम example,
 * perf_event_पढ़ो_local(), within the same पूर्णांकerrupt disabled section in
 * which this counter is planned to be used.
 *
 * Return: The index of the perक्रमmance monitoring counter asचिन्हित to
 * @perf_event.
 */
पूर्णांक x86_perf_rdpmc_index(काष्ठा perf_event *event)
अणु
	lockdep_निश्चित_irqs_disabled();

	वापस event->hw.event_base_rdpmc;
पूर्ण

अटल अंतरभूत पूर्णांक match_prev_assignment(काष्ठा hw_perf_event *hwc,
					काष्ठा cpu_hw_events *cpuc,
					पूर्णांक i)
अणु
	वापस hwc->idx == cpuc->assign[i] &&
		hwc->last_cpu == smp_processor_id() &&
		hwc->last_tag == cpuc->tags[i];
पूर्ण

अटल व्योम x86_pmu_start(काष्ठा perf_event *event, पूर्णांक flags);

अटल व्योम x86_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_event *event;
	काष्ठा hw_perf_event *hwc;
	पूर्णांक i, added = cpuc->n_added;

	अगर (!x86_pmu_initialized())
		वापस;

	अगर (cpuc->enabled)
		वापस;

	अगर (cpuc->n_added) अणु
		पूर्णांक n_running = cpuc->n_events - cpuc->n_added;
		/*
		 * apply assignment obtained either from
		 * hw_perf_group_sched_in() or x86_pmu_enable()
		 *
		 * step1: save events moving to new counters
		 */
		क्रम (i = 0; i < n_running; i++) अणु
			event = cpuc->event_list[i];
			hwc = &event->hw;

			/*
			 * we can aव्योम reprogramming counter अगर:
			 * - asचिन्हित same counter as last समय
			 * - running on same CPU as last समय
			 * - no other event has used the counter since
			 */
			अगर (hwc->idx == -1 ||
			    match_prev_assignment(hwc, cpuc, i))
				जारी;

			/*
			 * Ensure we करोn't accidentally enable a stopped
			 * counter simply because we rescheduled.
			 */
			अगर (hwc->state & PERF_HES_STOPPED)
				hwc->state |= PERF_HES_ARCH;

			x86_pmu_stop(event, PERF_EF_UPDATE);
		पूर्ण

		/*
		 * step2: reprogram moved events पूर्णांकo new counters
		 */
		क्रम (i = 0; i < cpuc->n_events; i++) अणु
			event = cpuc->event_list[i];
			hwc = &event->hw;

			अगर (!match_prev_assignment(hwc, cpuc, i))
				x86_assign_hw_event(event, cpuc, i);
			अन्यथा अगर (i < n_running)
				जारी;

			अगर (hwc->state & PERF_HES_ARCH)
				जारी;

			x86_pmu_start(event, PERF_EF_RELOAD);
		पूर्ण
		cpuc->n_added = 0;
		perf_events_lapic_init();
	पूर्ण

	cpuc->enabled = 1;
	barrier();

	अटल_call(x86_pmu_enable_all)(added);
पूर्ण

अटल DEFINE_PER_CPU(u64 [X86_PMC_IDX_MAX], pmc_prev_left);

/*
 * Set the next IRQ period, based on the hwc->period_left value.
 * To be called with the event disabled in hw:
 */
पूर्णांक x86_perf_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक ret = 0, idx = hwc->idx;

	अगर (unlikely(!hwc->event_base))
		वापस 0;

	अगर (unlikely(is_topकरोwn_count(event)) &&
	    x86_pmu.set_topकरोwn_event_period)
		वापस x86_pmu.set_topकरोwn_event_period(event);

	/*
	 * If we are way outside a reasonable range then just skip क्रमward:
	 */
	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (unlikely(left <= 0)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण
	/*
	 * Quirk: certain CPUs करोnt like it अगर just 1 hw_event is left:
	 */
	अगर (unlikely(left < 2))
		left = 2;

	अगर (left > x86_pmu.max_period)
		left = x86_pmu.max_period;

	अगर (x86_pmu.limit_period)
		left = x86_pmu.limit_period(event, left);

	per_cpu(pmc_prev_left[idx], smp_processor_id()) = left;

	/*
	 * The hw event starts counting from this event offset,
	 * mark it to be able to extra future deltas:
	 */
	local64_set(&hwc->prev_count, (u64)-left);

	wrmsrl(hwc->event_base, (u64)(-left) & x86_pmu.cntval_mask);

	/*
	 * Sign extend the Merge event counter's upper 16 bits since
	 * we currently declare a 48-bit counter width
	 */
	अगर (is_counter_pair(hwc))
		wrmsrl(x86_pmu_event_addr(idx + 1), 0xffff);

	/*
	 * Due to erratum on certan cpu we need
	 * a second ग_लिखो to be sure the रेजिस्टर
	 * is updated properly
	 */
	अगर (x86_pmu.perfctr_second_ग_लिखो) अणु
		wrmsrl(hwc->event_base,
			(u64)(-left) & x86_pmu.cntval_mask);
	पूर्ण

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

व्योम x86_pmu_enable_event(काष्ठा perf_event *event)
अणु
	अगर (__this_cpu_पढ़ो(cpu_hw_events.enabled))
		__x86_pmu_enable_event(&event->hw,
				       ARCH_PERFMON_EVENTSEL_ENABLE);
पूर्ण

/*
 * Add a single event to the PMU.
 *
 * The event is added to the group of enabled events
 * but only अगर it can be scheduled with existing events.
 */
अटल पूर्णांक x86_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc;
	पूर्णांक assign[X86_PMC_IDX_MAX];
	पूर्णांक n, n0, ret;

	hwc = &event->hw;

	n0 = cpuc->n_events;
	ret = n = collect_events(cpuc, event, false);
	अगर (ret < 0)
		जाओ out;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_ARCH;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be perक्रमmed
	 * at commit समय (->commit_txn) as a whole.
	 *
	 * If commit fails, we'll call ->del() on all events
	 * क्रम which ->add() was called.
	 */
	अगर (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		जाओ करोne_collect;

	ret = अटल_call(x86_pmu_schedule_events)(cpuc, n, assign);
	अगर (ret)
		जाओ out;
	/*
	 * copy new assignment, now we know it is possible
	 * will be used by hw_perf_enable()
	 */
	स_नकल(cpuc->assign, assign, n*माप(पूर्णांक));

करोne_collect:
	/*
	 * Commit the collect_events() state. See x86_pmu_del() and
	 * x86_pmu_*_txn().
	 */
	cpuc->n_events = n;
	cpuc->n_added += n - n0;
	cpuc->n_txn += n - n0;

	/*
	 * This is beक्रमe x86_pmu_enable() will call x86_pmu_start(),
	 * so we enable LBRs beक्रमe an event needs them etc..
	 */
	अटल_call_cond(x86_pmu_add)(event);

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम x86_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx = event->hw.idx;

	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	अगर (WARN_ON_ONCE(idx == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));
		x86_perf_event_set_period(event);
	पूर्ण

	event->hw.state = 0;

	cpuc->events[idx] = event;
	__set_bit(idx, cpuc->active_mask);
	अटल_call(x86_pmu_enable)(event);
	perf_event_update_userpage(event);
पूर्ण

व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	u64 ctrl, status, overflow, pmc_ctrl, pmc_count, prev_left, fixed;
	u64 pebs, debugctl;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	पूर्णांक num_counters = hybrid(cpuc->pmu, num_counters);
	पूर्णांक num_counters_fixed = hybrid(cpuc->pmu, num_counters_fixed);
	काष्ठा event_स्थिरraपूर्णांक *pebs_स्थिरraपूर्णांकs = hybrid(cpuc->pmu, pebs_स्थिरraपूर्णांकs);
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	अगर (!num_counters)
		वापस;

	local_irq_save(flags);

	अगर (x86_pmu.version >= 2) अणु
		rdmsrl(MSR_CORE_PERF_GLOBAL_CTRL, ctrl);
		rdmsrl(MSR_CORE_PERF_GLOBAL_STATUS, status);
		rdmsrl(MSR_CORE_PERF_GLOBAL_OVF_CTRL, overflow);
		rdmsrl(MSR_ARCH_PERFMON_FIXED_CTR_CTRL, fixed);

		pr_info("\n");
		pr_info("CPU#%d: ctrl:       %016llx\n", cpu, ctrl);
		pr_info("CPU#%d: status:     %016llx\n", cpu, status);
		pr_info("CPU#%d: overflow:   %016llx\n", cpu, overflow);
		pr_info("CPU#%d: fixed:      %016llx\n", cpu, fixed);
		अगर (pebs_स्थिरraपूर्णांकs) अणु
			rdmsrl(MSR_IA32_PEBS_ENABLE, pebs);
			pr_info("CPU#%d: pebs:       %016llx\n", cpu, pebs);
		पूर्ण
		अगर (x86_pmu.lbr_nr) अणु
			rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
			pr_info("CPU#%d: debugctl:   %016llx\n", cpu, debugctl);
		पूर्ण
	पूर्ण
	pr_info("CPU#%d: active:     %016llx\n", cpu, *(u64 *)cpuc->active_mask);

	क्रम (idx = 0; idx < num_counters; idx++) अणु
		rdmsrl(x86_pmu_config_addr(idx), pmc_ctrl);
		rdmsrl(x86_pmu_event_addr(idx), pmc_count);

		prev_left = per_cpu(pmc_prev_left[idx], cpu);

		pr_info("CPU#%d:   gen-PMC%d ctrl:  %016llx\n",
			cpu, idx, pmc_ctrl);
		pr_info("CPU#%d:   gen-PMC%d count: %016llx\n",
			cpu, idx, pmc_count);
		pr_info("CPU#%d:   gen-PMC%d left:  %016llx\n",
			cpu, idx, prev_left);
	पूर्ण
	क्रम (idx = 0; idx < num_counters_fixed; idx++) अणु
		अगर (fixed_counter_disabled(idx, cpuc->pmu))
			जारी;
		rdmsrl(MSR_ARCH_PERFMON_FIXED_CTR0 + idx, pmc_count);

		pr_info("CPU#%d: fixed-PMC%d count: %016llx\n",
			cpu, idx, pmc_count);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम x86_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (test_bit(hwc->idx, cpuc->active_mask)) अणु
		अटल_call(x86_pmu_disable)(event);
		__clear_bit(hwc->idx, cpuc->active_mask);
		cpuc->events[hwc->idx] = शून्य;
		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		/*
		 * Drain the reमुख्यing delta count out of a event
		 * that we are disabling:
		 */
		x86_perf_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम x86_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	जोड़ perf_capabilities पूर्णांकel_cap = hybrid(cpuc->pmu, पूर्णांकel_cap);
	पूर्णांक i;

	/*
	 * If we're called during a txn, we only need to unकरो x86_pmu.add.
	 * The events never got scheduled and ->cancel_txn will truncate
	 * the event_list.
	 *
	 * XXX assumes any ->del() called during a TXN will only be on
	 * an event added during that same TXN.
	 */
	अगर (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		जाओ करो_del;

	/*
	 * Not a TXN, thereक्रमe cleanup properly.
	 */
	x86_pmu_stop(event, PERF_EF_UPDATE);

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		अगर (event == cpuc->event_list[i])
			अवरोध;
	पूर्ण

	अगर (WARN_ON_ONCE(i == cpuc->n_events)) /* called ->del() without ->add() ? */
		वापस;

	/* If we have a newly added event; make sure to decrease n_added. */
	अगर (i >= cpuc->n_events - cpuc->n_added)
		--cpuc->n_added;

	अटल_call_cond(x86_pmu_put_event_स्थिरraपूर्णांकs)(cpuc, event);

	/* Delete the array entry. */
	जबतक (++i < cpuc->n_events) अणु
		cpuc->event_list[i-1] = cpuc->event_list[i];
		cpuc->event_स्थिरraपूर्णांक[i-1] = cpuc->event_स्थिरraपूर्णांक[i];
	पूर्ण
	cpuc->event_स्थिरraपूर्णांक[i-1] = शून्य;
	--cpuc->n_events;
	अगर (पूर्णांकel_cap.perf_metrics)
		del_nr_metric_event(cpuc, event);

	perf_event_update_userpage(event);

करो_del:

	/*
	 * This is after x86_pmu_stop(); so we disable LBRs after any
	 * event can need them etc..
	 */
	अटल_call_cond(x86_pmu_del)(event);
पूर्ण

पूर्णांक x86_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc;
	काष्ठा perf_event *event;
	पूर्णांक idx, handled = 0;
	u64 val;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * Some chipsets need to unmask the LVTPC in a particular spot
	 * inside the nmi handler.  As a result, the unmasking was pushed
	 * पूर्णांकo all the nmi handlers.
	 *
	 * This generic handler करोesn't seem to have any issues where the
	 * unmasking occurs so it was left at the top.
	 */
	apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;

		event = cpuc->events[idx];

		val = x86_perf_event_update(event);
		अगर (val & (1ULL << (x86_pmu.cntval_bits - 1)))
			जारी;

		/*
		 * event overflow
		 */
		handled++;
		perf_sample_data_init(&data, 0, event->hw.last_period);

		अगर (!x86_perf_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण

	अगर (handled)
		inc_irq_stat(apic_perf_irqs);

	वापस handled;
पूर्ण

व्योम perf_events_lapic_init(व्योम)
अणु
	अगर (!x86_pmu.apic || !x86_pmu_initialized())
		वापस;

	/*
	 * Always use NMI क्रम PMU
	 */
	apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);
पूर्ण

अटल पूर्णांक
perf_event_nmi_handler(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	u64 start_घड़ी;
	u64 finish_घड़ी;
	पूर्णांक ret;

	/*
	 * All PMUs/events that share this PMI handler should make sure to
	 * increment active_events क्रम their events.
	 */
	अगर (!atomic_पढ़ो(&active_events))
		वापस NMI_DONE;

	start_घड़ी = sched_घड़ी();
	ret = अटल_call(x86_pmu_handle_irq)(regs);
	finish_घड़ी = sched_घड़ी();

	perf_sample_event_took(finish_घड़ी - start_घड़ी);

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(perf_event_nmi_handler);

काष्ठा event_स्थिरraपूर्णांक emptyस्थिरraपूर्णांक;
काष्ठा event_स्थिरraपूर्णांक unस्थिरrained;

अटल पूर्णांक x86_pmu_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	पूर्णांक i;

	क्रम (i = 0 ; i < X86_PERF_KFREE_MAX; i++)
		cpuc->kमुक्त_on_online[i] = शून्य;
	अगर (x86_pmu.cpu_prepare)
		वापस x86_pmu.cpu_prepare(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (x86_pmu.cpu_dead)
		x86_pmu.cpu_dead(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	पूर्णांक i;

	क्रम (i = 0 ; i < X86_PERF_KFREE_MAX; i++) अणु
		kमुक्त(cpuc->kमुक्त_on_online[i]);
		cpuc->kमुक्त_on_online[i] = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (x86_pmu.cpu_starting)
		x86_pmu.cpu_starting(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (x86_pmu.cpu_dying)
		x86_pmu.cpu_dying(cpu);
	वापस 0;
पूर्ण

अटल व्योम __init pmu_check_apic(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_APIC))
		वापस;

	x86_pmu.apic = 0;
	pr_info("no APIC, boot with the \"lapic\" boot parameter to force-enable it.\n");
	pr_info("no hardware sampling interrupt available.\n");

	/*
	 * If we have a PMU initialized but no APIC
	 * पूर्णांकerrupts, we cannot sample hardware
	 * events (user-space has to fall back and
	 * sample via a hrसमयr based software event):
	 */
	pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

पूर्ण

अटल काष्ठा attribute_group x86_pmu_क्रमmat_group __ro_after_init = अणु
	.name = "format",
	.attrs = शून्य,
पूर्ण;

sमाप_प्रकार events_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	u64 config = 0;

	अगर (pmu_attr->id < x86_pmu.max_events)
		config = x86_pmu.event_map(pmu_attr->id);

	/* string trumps id */
	अगर (pmu_attr->event_str)
		वापस प्र_लिखो(page, "%s", pmu_attr->event_str);

	वापस x86_pmu.events_sysfs_show(page, config);
पूर्ण
EXPORT_SYMBOL_GPL(events_sysfs_show);

sमाप_प्रकार events_ht_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *page)
अणु
	काष्ठा perf_pmu_events_ht_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_ht_attr, attr);

	/*
	 * Report conditional events depending on Hyper-Thपढ़ोing.
	 *
	 * This is overly conservative as usually the HT special
	 * handling is not needed अगर the other CPU thपढ़ो is idle.
	 *
	 * Note this करोes not (and cannot) handle the हाल when thपढ़ो
	 * siblings are invisible, क्रम example with भवization
	 * अगर they are owned by some other guest.  The user tool
	 * has to re-पढ़ो when a thपढ़ो sibling माला_लो onlined later.
	 */
	वापस प्र_लिखो(page, "%s",
			topology_max_smt_thपढ़ोs() > 1 ?
			pmu_attr->event_str_ht :
			pmu_attr->event_str_noht);
पूर्ण

sमाप_प्रकार events_hybrid_sysfs_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *page)
अणु
	काष्ठा perf_pmu_events_hybrid_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_hybrid_attr, attr);
	काष्ठा x86_hybrid_pmu *pmu;
	स्थिर अक्षर *str, *next_str;
	पूर्णांक i;

	अगर (hweight64(pmu_attr->pmu_type) == 1)
		वापस प्र_लिखो(page, "%s", pmu_attr->event_str);

	/*
	 * Hybrid PMUs may support the same event name, but with dअगरferent
	 * event encoding, e.g., the mem-loads event on an Atom PMU has
	 * dअगरferent event encoding from a Core PMU.
	 *
	 * The event_str includes all event encodings. Each event encoding
	 * is भागided by ";". The order of the event encodings must follow
	 * the order of the hybrid PMU index.
	 */
	pmu = container_of(dev_get_drvdata(dev), काष्ठा x86_hybrid_pmu, pmu);

	str = pmu_attr->event_str;
	क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++) अणु
		अगर (!(x86_pmu.hybrid_pmu[i].cpu_type & pmu_attr->pmu_type))
			जारी;
		अगर (x86_pmu.hybrid_pmu[i].cpu_type & pmu->cpu_type) अणु
			next_str = म_अक्षर(str, ';');
			अगर (next_str)
				वापस snम_लिखो(page, next_str - str + 1, "%s", str);
			अन्यथा
				वापस प्र_लिखो(page, "%s", str);
		पूर्ण
		str = म_अक्षर(str, ';');
		str++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(events_hybrid_sysfs_show);

EVENT_ATTR(cpu-cycles,			CPU_CYCLES		);
EVENT_ATTR(inकाष्ठाions,		INSTRUCTIONS		);
EVENT_ATTR(cache-references,		CACHE_REFERENCES	);
EVENT_ATTR(cache-misses, 		CACHE_MISSES		);
EVENT_ATTR(branch-inकाष्ठाions,		BRANCH_INSTRUCTIONS	);
EVENT_ATTR(branch-misses,		BRANCH_MISSES		);
EVENT_ATTR(bus-cycles,			BUS_CYCLES		);
EVENT_ATTR(stalled-cycles-frontend,	STALLED_CYCLES_FRONTEND	);
EVENT_ATTR(stalled-cycles-backend,	STALLED_CYCLES_BACKEND	);
EVENT_ATTR(ref-cycles,			REF_CPU_CYCLES		);

अटल काष्ठा attribute *empty_attrs;

अटल काष्ठा attribute *events_attr[] = अणु
	EVENT_PTR(CPU_CYCLES),
	EVENT_PTR(INSTRUCTIONS),
	EVENT_PTR(CACHE_REFERENCES),
	EVENT_PTR(CACHE_MISSES),
	EVENT_PTR(BRANCH_INSTRUCTIONS),
	EVENT_PTR(BRANCH_MISSES),
	EVENT_PTR(BUS_CYCLES),
	EVENT_PTR(STALLED_CYCLES_FRONTEND),
	EVENT_PTR(STALLED_CYCLES_BACKEND),
	EVENT_PTR(REF_CPU_CYCLES),
	शून्य,
पूर्ण;

/*
 * Remove all undefined events (x86_pmu.event_map(id) == 0)
 * out of events_attr attributes.
 */
अटल umode_t
is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	अगर (idx >= x86_pmu.max_events)
		वापस 0;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr.attr);
	/* str trumps id */
	वापस pmu_attr->event_str || x86_pmu.event_map(idx) ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute_group x86_pmu_events_group __ro_after_init = अणु
	.name = "events",
	.attrs = events_attr,
	.is_visible = is_visible,
पूर्ण;

sमाप_प्रकार x86_event_sysfs_show(अक्षर *page, u64 config, u64 event)
अणु
	u64 umask  = (config & ARCH_PERFMON_EVENTSEL_UMASK) >> 8;
	u64 cmask  = (config & ARCH_PERFMON_EVENTSEL_CMASK) >> 24;
	bool edge  = (config & ARCH_PERFMON_EVENTSEL_EDGE);
	bool pc    = (config & ARCH_PERFMON_EVENTSEL_PIN_CONTROL);
	bool any   = (config & ARCH_PERFMON_EVENTSEL_ANY);
	bool inv   = (config & ARCH_PERFMON_EVENTSEL_INV);
	sमाप_प्रकार ret;

	/*
	* We have whole page size to spend and just little data
	* to ग_लिखो, so we can safely use प्र_लिखो.
	*/
	ret = प्र_लिखो(page, "event=0x%02llx", event);

	अगर (umask)
		ret += प्र_लिखो(page + ret, ",umask=0x%02llx", umask);

	अगर (edge)
		ret += प्र_लिखो(page + ret, ",edge");

	अगर (pc)
		ret += प्र_लिखो(page + ret, ",pc");

	अगर (any)
		ret += प्र_लिखो(page + ret, ",any");

	अगर (inv)
		ret += प्र_लिखो(page + ret, ",inv");

	अगर (cmask)
		ret += प्र_लिखो(page + ret, ",cmask=0x%02llx", cmask);

	ret += प्र_लिखो(page + ret, "\n");

	वापस ret;
पूर्ण

अटल काष्ठा attribute_group x86_pmu_attr_group;
अटल काष्ठा attribute_group x86_pmu_caps_group;

अटल व्योम x86_pmu_अटल_call_update(व्योम)
अणु
	अटल_call_update(x86_pmu_handle_irq, x86_pmu.handle_irq);
	अटल_call_update(x86_pmu_disable_all, x86_pmu.disable_all);
	अटल_call_update(x86_pmu_enable_all, x86_pmu.enable_all);
	अटल_call_update(x86_pmu_enable, x86_pmu.enable);
	अटल_call_update(x86_pmu_disable, x86_pmu.disable);

	अटल_call_update(x86_pmu_add, x86_pmu.add);
	अटल_call_update(x86_pmu_del, x86_pmu.del);
	अटल_call_update(x86_pmu_पढ़ो, x86_pmu.पढ़ो);

	अटल_call_update(x86_pmu_schedule_events, x86_pmu.schedule_events);
	अटल_call_update(x86_pmu_get_event_स्थिरraपूर्णांकs, x86_pmu.get_event_स्थिरraपूर्णांकs);
	अटल_call_update(x86_pmu_put_event_स्थिरraपूर्णांकs, x86_pmu.put_event_स्थिरraपूर्णांकs);

	अटल_call_update(x86_pmu_start_scheduling, x86_pmu.start_scheduling);
	अटल_call_update(x86_pmu_commit_scheduling, x86_pmu.commit_scheduling);
	अटल_call_update(x86_pmu_stop_scheduling, x86_pmu.stop_scheduling);

	अटल_call_update(x86_pmu_sched_task, x86_pmu.sched_task);
	अटल_call_update(x86_pmu_swap_task_ctx, x86_pmu.swap_task_ctx);

	अटल_call_update(x86_pmu_drain_pebs, x86_pmu.drain_pebs);
	अटल_call_update(x86_pmu_pebs_aliases, x86_pmu.pebs_aliases);

	अटल_call_update(x86_pmu_guest_get_msrs, x86_pmu.guest_get_msrs);
पूर्ण

अटल व्योम _x86_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	x86_perf_event_update(event);
पूर्ण

व्योम x86_pmu_show_pmu_cap(पूर्णांक num_counters, पूर्णांक num_counters_fixed,
			  u64 पूर्णांकel_ctrl)
अणु
	pr_info("... version:                %d\n",     x86_pmu.version);
	pr_info("... bit width:              %d\n",     x86_pmu.cntval_bits);
	pr_info("... generic registers:      %d\n",     num_counters);
	pr_info("... value mask:             %016Lx\n", x86_pmu.cntval_mask);
	pr_info("... max period:             %016Lx\n", x86_pmu.max_period);
	pr_info("... fixed-purpose events:   %lu\n",
			hweight64((((1ULL << num_counters_fixed) - 1)
					<< INTEL_PMC_IDX_FIXED) & पूर्णांकel_ctrl));
	pr_info("... event mask:             %016Lx\n", पूर्णांकel_ctrl);
पूर्ण

/*
 * The generic code is not hybrid मित्रly. The hybrid_pmu->pmu
 * of the first रेजिस्टरed PMU is unconditionally asचिन्हित to
 * each possible cpuctx->ctx.pmu.
 * Update the correct hybrid PMU to the cpuctx->ctx.pmu.
 */
व्योम x86_pmu_update_cpu_context(काष्ठा pmu *pmu, पूर्णांक cpu)
अणु
	काष्ठा perf_cpu_context *cpuctx;

	अगर (!pmu->pmu_cpu_context)
		वापस;

	cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
	cpuctx->ctx.pmu = pmu;
पूर्ण

अटल पूर्णांक __init init_hw_perf_events(व्योम)
अणु
	काष्ठा x86_pmu_quirk *quirk;
	पूर्णांक err;

	pr_info("Performance Events: ");

	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_INTEL:
		err = पूर्णांकel_pmu_init();
		अवरोध;
	हाल X86_VENDOR_AMD:
		err = amd_pmu_init();
		अवरोध;
	हाल X86_VENDOR_HYGON:
		err = amd_pmu_init();
		x86_pmu.name = "HYGON";
		अवरोध;
	हाल X86_VENDOR_ZHAOXIN:
	हाल X86_VENDOR_CENTAUR:
		err = zhaoxin_pmu_init();
		अवरोध;
	शेष:
		err = -ENOTSUPP;
	पूर्ण
	अगर (err != 0) अणु
		pr_cont("no PMU driver, software events only.\n");
		वापस 0;
	पूर्ण

	pmu_check_apic();

	/* sanity check that the hardware exists or is emulated */
	अगर (!check_hw_exists(&pmu, x86_pmu.num_counters, x86_pmu.num_counters_fixed))
		वापस 0;

	pr_cont("%s PMU driver.\n", x86_pmu.name);

	x86_pmu.attr_rdpmc = 1; /* enable userspace RDPMC usage by शेष */

	क्रम (quirk = x86_pmu.quirks; quirk; quirk = quirk->next)
		quirk->func();

	अगर (!x86_pmu.पूर्णांकel_ctrl)
		x86_pmu.पूर्णांकel_ctrl = (1 << x86_pmu.num_counters) - 1;

	perf_events_lapic_init();
	रेजिस्टर_nmi_handler(NMI_LOCAL, perf_event_nmi_handler, 0, "PMI");

	unस्थिरrained = (काष्ठा event_स्थिरraपूर्णांक)
		__EVENT_CONSTRAINT(0, (1ULL << x86_pmu.num_counters) - 1,
				   0, x86_pmu.num_counters, 0, 0);

	x86_pmu_क्रमmat_group.attrs = x86_pmu.क्रमmat_attrs;

	अगर (!x86_pmu.events_sysfs_show)
		x86_pmu_events_group.attrs = &empty_attrs;

	pmu.attr_update = x86_pmu.attr_update;

	अगर (!is_hybrid()) अणु
		x86_pmu_show_pmu_cap(x86_pmu.num_counters,
				     x86_pmu.num_counters_fixed,
				     x86_pmu.पूर्णांकel_ctrl);
	पूर्ण

	अगर (!x86_pmu.पढ़ो)
		x86_pmu.पढ़ो = _x86_pmu_पढ़ो;

	अगर (!x86_pmu.guest_get_msrs)
		x86_pmu.guest_get_msrs = (व्योम *)&__अटल_call_वापस0;

	x86_pmu_अटल_call_update();

	/*
	 * Install callbacks. Core will call them क्रम each online
	 * cpu.
	 */
	err = cpuhp_setup_state(CPUHP_PERF_X86_PREPARE, "perf/x86:prepare",
				x86_pmu_prepare_cpu, x86_pmu_dead_cpu);
	अगर (err)
		वापस err;

	err = cpuhp_setup_state(CPUHP_AP_PERF_X86_STARTING,
				"perf/x86:starting", x86_pmu_starting_cpu,
				x86_pmu_dying_cpu);
	अगर (err)
		जाओ out;

	err = cpuhp_setup_state(CPUHP_AP_PERF_X86_ONLINE, "perf/x86:online",
				x86_pmu_online_cpu, शून्य);
	अगर (err)
		जाओ out1;

	अगर (!is_hybrid()) अणु
		err = perf_pmu_रेजिस्टर(&pmu, "cpu", PERF_TYPE_RAW);
		अगर (err)
			जाओ out2;
	पूर्ण अन्यथा अणु
		u8 cpu_type = get_this_hybrid_cpu_type();
		काष्ठा x86_hybrid_pmu *hybrid_pmu;
		पूर्णांक i, j;

		अगर (!cpu_type && x86_pmu.get_hybrid_cpu_type)
			cpu_type = x86_pmu.get_hybrid_cpu_type();

		क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++) अणु
			hybrid_pmu = &x86_pmu.hybrid_pmu[i];

			hybrid_pmu->pmu = pmu;
			hybrid_pmu->pmu.type = -1;
			hybrid_pmu->pmu.attr_update = x86_pmu.attr_update;
			hybrid_pmu->pmu.capabilities |= PERF_PMU_CAP_HETEROGENEOUS_CPUS;
			hybrid_pmu->pmu.capabilities |= PERF_PMU_CAP_EXTENDED_HW_TYPE;

			err = perf_pmu_रेजिस्टर(&hybrid_pmu->pmu, hybrid_pmu->name,
						(hybrid_pmu->cpu_type == hybrid_big) ? PERF_TYPE_RAW : -1);
			अगर (err)
				अवरोध;

			अगर (cpu_type == hybrid_pmu->cpu_type)
				x86_pmu_update_cpu_context(&hybrid_pmu->pmu, raw_smp_processor_id());
		पूर्ण

		अगर (i < x86_pmu.num_hybrid_pmus) अणु
			क्रम (j = 0; j < i; j++)
				perf_pmu_unरेजिस्टर(&x86_pmu.hybrid_pmu[j].pmu);
			pr_warn("Failed to register hybrid PMUs\n");
			kमुक्त(x86_pmu.hybrid_pmu);
			x86_pmu.hybrid_pmu = शून्य;
			x86_pmu.num_hybrid_pmus = 0;
			जाओ out2;
		पूर्ण
	पूर्ण

	वापस 0;

out2:
	cpuhp_हटाओ_state(CPUHP_AP_PERF_X86_ONLINE);
out1:
	cpuhp_हटाओ_state(CPUHP_AP_PERF_X86_STARTING);
out:
	cpuhp_हटाओ_state(CPUHP_PERF_X86_PREPARE);
	वापस err;
पूर्ण
early_initcall(init_hw_perf_events);

अटल व्योम x86_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	अटल_call(x86_pmu_पढ़ो)(event);
पूर्ण

/*
 * Start group events scheduling transaction
 * Set the flag to make pmu::enable() not perक्रमm the
 * schedulability test, it will be perक्रमmed at commit समय
 *
 * We only support PERF_PMU_TXN_ADD transactions. Save the
 * transaction flags but otherwise ignore non-PERF_PMU_TXN_ADD
 * transactions.
 */
अटल व्योम x86_pmu_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक txn_flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(cpuc->txn_flags);		/* txn alपढ़ोy in flight */

	cpuc->txn_flags = txn_flags;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_disable(pmu);
	__this_cpu_ग_लिखो(cpu_hw_events.n_txn, 0);
	__this_cpu_ग_लिखो(cpu_hw_events.n_txn_pair, 0);
	__this_cpu_ग_लिखो(cpu_hw_events.n_txn_metric, 0);
पूर्ण

/*
 * Stop group events scheduling transaction
 * Clear the flag and pmu::enable() will perक्रमm the
 * schedulability test.
 */
अटल व्योम x86_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	अचिन्हित पूर्णांक txn_flags;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	txn_flags = cpuc->txn_flags;
	cpuc->txn_flags = 0;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	/*
	 * Truncate collected array by the number of events added in this
	 * transaction. See x86_pmu_add() and x86_pmu_*_txn().
	 */
	__this_cpu_sub(cpu_hw_events.n_added, __this_cpu_पढ़ो(cpu_hw_events.n_txn));
	__this_cpu_sub(cpu_hw_events.n_events, __this_cpu_पढ़ो(cpu_hw_events.n_txn));
	__this_cpu_sub(cpu_hw_events.n_pair, __this_cpu_पढ़ो(cpu_hw_events.n_txn_pair));
	__this_cpu_sub(cpu_hw_events.n_metric, __this_cpu_पढ़ो(cpu_hw_events.n_txn_metric));
	perf_pmu_enable(pmu);
पूर्ण

/*
 * Commit group events scheduling transaction
 * Perक्रमm the group schedulability test as a whole
 * Return 0 अगर success
 *
 * Does not cancel the transaction on failure; expects the caller to करो this.
 */
अटल पूर्णांक x86_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक assign[X86_PMC_IDX_MAX];
	पूर्णांक n, ret;

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	अगर (cpuc->txn_flags & ~PERF_PMU_TXN_ADD) अणु
		cpuc->txn_flags = 0;
		वापस 0;
	पूर्ण

	n = cpuc->n_events;

	अगर (!x86_pmu_initialized())
		वापस -EAGAIN;

	ret = अटल_call(x86_pmu_schedule_events)(cpuc, n, assign);
	अगर (ret)
		वापस ret;

	/*
	 * copy new assignment, now we know it is possible
	 * will be used by hw_perf_enable()
	 */
	स_नकल(cpuc->assign, assign, n*माप(पूर्णांक));

	cpuc->txn_flags = 0;
	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण
/*
 * a fake_cpuc is used to validate event groups. Due to
 * the extra reg logic, we need to also allocate a fake
 * per_core and per_cpu काष्ठाure. Otherwise, group events
 * using extra reg may conflict without the kernel being
 * able to catch this when the last event माला_लो added to
 * the group.
 */
अटल व्योम मुक्त_fake_cpuc(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांकel_cpuc_finish(cpuc);
	kमुक्त(cpuc);
पूर्ण

अटल काष्ठा cpu_hw_events *allocate_fake_cpuc(काष्ठा pmu *event_pmu)
अणु
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक cpu;

	cpuc = kzalloc(माप(*cpuc), GFP_KERNEL);
	अगर (!cpuc)
		वापस ERR_PTR(-ENOMEM);
	cpuc->is_fake = 1;

	अगर (is_hybrid()) अणु
		काष्ठा x86_hybrid_pmu *h_pmu;

		h_pmu = hybrid_pmu(event_pmu);
		अगर (cpumask_empty(&h_pmu->supported_cpus))
			जाओ error;
		cpu = cpumask_first(&h_pmu->supported_cpus);
	पूर्ण अन्यथा
		cpu = raw_smp_processor_id();
	cpuc->pmu = event_pmu;

	अगर (पूर्णांकel_cpuc_prepare(cpuc, cpu))
		जाओ error;

	वापस cpuc;
error:
	मुक्त_fake_cpuc(cpuc);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * validate that we can schedule this event
 */
अटल पूर्णांक validate_event(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *fake_cpuc;
	काष्ठा event_स्थिरraपूर्णांक *c;
	पूर्णांक ret = 0;

	fake_cpuc = allocate_fake_cpuc(event->pmu);
	अगर (IS_ERR(fake_cpuc))
		वापस PTR_ERR(fake_cpuc);

	c = x86_pmu.get_event_स्थिरraपूर्णांकs(fake_cpuc, 0, event);

	अगर (!c || !c->weight)
		ret = -EINVAL;

	अगर (x86_pmu.put_event_स्थिरraपूर्णांकs)
		x86_pmu.put_event_स्थिरraपूर्णांकs(fake_cpuc, event);

	मुक्त_fake_cpuc(fake_cpuc);

	वापस ret;
पूर्ण

/*
 * validate a single event group
 *
 * validation include:
 *	- check events are compatible which each other
 *	- events करो not compete क्रम the same counter
 *	- number of events <= number of counters
 *
 * validation ensures the group can be loaded onto the
 * PMU अगर it was the only group available.
 */
अटल पूर्णांक validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा cpu_hw_events *fake_cpuc;
	पूर्णांक ret = -EINVAL, n;

	/*
	 * Reject events from dअगरferent hybrid PMUs.
	 */
	अगर (is_hybrid()) अणु
		काष्ठा perf_event *sibling;
		काष्ठा pmu *pmu = शून्य;

		अगर (is_x86_event(leader))
			pmu = leader->pmu;

		क्रम_each_sibling_event(sibling, leader) अणु
			अगर (!is_x86_event(sibling))
				जारी;
			अगर (!pmu)
				pmu = sibling->pmu;
			अन्यथा अगर (pmu != sibling->pmu)
				वापस ret;
		पूर्ण
	पूर्ण

	fake_cpuc = allocate_fake_cpuc(event->pmu);
	अगर (IS_ERR(fake_cpuc))
		वापस PTR_ERR(fake_cpuc);
	/*
	 * the event is not yet connected with its
	 * siblings thereक्रमe we must first collect
	 * existing siblings, then add the new event
	 * beक्रमe we can simulate the scheduling
	 */
	n = collect_events(fake_cpuc, leader, true);
	अगर (n < 0)
		जाओ out;

	fake_cpuc->n_events = n;
	n = collect_events(fake_cpuc, event, false);
	अगर (n < 0)
		जाओ out;

	fake_cpuc->n_events = 0;
	ret = x86_pmu.schedule_events(fake_cpuc, n, शून्य);

out:
	मुक्त_fake_cpuc(fake_cpuc);
	वापस ret;
पूर्ण

अटल पूर्णांक x86_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = शून्य;
	पूर्णांक err;

	अगर ((event->attr.type != event->pmu->type) &&
	    (event->attr.type != PERF_TYPE_HARDWARE) &&
	    (event->attr.type != PERF_TYPE_HW_CACHE))
		वापस -ENOENT;

	अगर (is_hybrid() && (event->cpu != -1)) अणु
		pmu = hybrid_pmu(event->pmu);
		अगर (!cpumask_test_cpu(event->cpu, &pmu->supported_cpus))
			वापस -ENOENT;
	पूर्ण

	err = __x86_pmu_event_init(event);
	अगर (!err) अणु
		अगर (event->group_leader != event)
			err = validate_group(event);
		अन्यथा
			err = validate_event(event);
	पूर्ण
	अगर (err) अणु
		अगर (event->destroy)
			event->destroy(event);
	पूर्ण

	अगर (READ_ONCE(x86_pmu.attr_rdpmc) &&
	    !(event->hw.flags & PERF_X86_EVENT_LARGE_PEBS))
		event->hw.flags |= PERF_X86_EVENT_RDPMC_ALLOWED;

	वापस err;
पूर्ण

अटल व्योम x86_pmu_event_mapped(काष्ठा perf_event *event, काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!(event->hw.flags & PERF_X86_EVENT_RDPMC_ALLOWED))
		वापस;

	/*
	 * This function relies on not being called concurrently in two
	 * tasks in the same mm.  Otherwise one task could observe
	 * perf_rdpmc_allowed > 1 and वापस all the way back to
	 * userspace with CR4.PCE clear जबतक another task is still
	 * करोing on_each_cpu_mask() to propagate CR4.PCE.
	 *
	 * For now, this can't happen because all callers hold mmap_lock
	 * क्रम ग_लिखो.  If this changes, we'll need a dअगरferent solution.
	 */
	mmap_निश्चित_ग_लिखो_locked(mm);

	अगर (atomic_inc_वापस(&mm->context.perf_rdpmc_allowed) == 1)
		on_each_cpu_mask(mm_cpumask(mm), cr4_update_pce, शून्य, 1);
पूर्ण

अटल व्योम x86_pmu_event_unmapped(काष्ठा perf_event *event, काष्ठा mm_काष्ठा *mm)
अणु

	अगर (!(event->hw.flags & PERF_X86_EVENT_RDPMC_ALLOWED))
		वापस;

	अगर (atomic_dec_and_test(&mm->context.perf_rdpmc_allowed))
		on_each_cpu_mask(mm_cpumask(mm), cr4_update_pce, शून्य, 1);
पूर्ण

अटल पूर्णांक x86_pmu_event_idx(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!(hwc->flags & PERF_X86_EVENT_RDPMC_ALLOWED))
		वापस 0;

	अगर (is_metric_idx(hwc->idx))
		वापस INTEL_PMC_FIXED_RDPMC_METRICS + 1;
	अन्यथा
		वापस hwc->event_base_rdpmc + 1;
पूर्ण

अटल sमाप_प्रकार get_attr_rdpmc(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस snम_लिखो(buf, 40, "%d\n", x86_pmu.attr_rdpmc);
पूर्ण

अटल sमाप_प्रकार set_attr_rdpmc(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 2)
		वापस -EINVAL;

	अगर (x86_pmu.attr_rdpmc_broken)
		वापस -ENOTSUPP;

	अगर (val != x86_pmu.attr_rdpmc) अणु
		/*
		 * Changing पूर्णांकo or out of never available or always available,
		 * aka perf-event-bypassing mode. This path is extremely slow,
		 * but only root can trigger it, so it's okay.
		 */
		अगर (val == 0)
			अटल_branch_inc(&rdpmc_never_available_key);
		अन्यथा अगर (x86_pmu.attr_rdpmc == 0)
			अटल_branch_dec(&rdpmc_never_available_key);

		अगर (val == 2)
			अटल_branch_inc(&rdpmc_always_available_key);
		अन्यथा अगर (x86_pmu.attr_rdpmc == 2)
			अटल_branch_dec(&rdpmc_always_available_key);

		on_each_cpu(cr4_update_pce, शून्य, 1);
		x86_pmu.attr_rdpmc = val;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(rdpmc, S_IRUSR | S_IWUSR, get_attr_rdpmc, set_attr_rdpmc);

अटल काष्ठा attribute *x86_pmu_attrs[] = अणु
	&dev_attr_rdpmc.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group x86_pmu_attr_group __ro_after_init = अणु
	.attrs = x86_pmu_attrs,
पूर्ण;

अटल sमाप_प्रकार max_precise_show(काष्ठा device *cdev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", x86_pmu_max_precise());
पूर्ण

अटल DEVICE_ATTR_RO(max_precise);

अटल काष्ठा attribute *x86_pmu_caps_attrs[] = अणु
	&dev_attr_max_precise.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group x86_pmu_caps_group __ro_after_init = अणु
	.name = "caps",
	.attrs = x86_pmu_caps_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *x86_pmu_attr_groups[] = अणु
	&x86_pmu_attr_group,
	&x86_pmu_क्रमmat_group,
	&x86_pmu_events_group,
	&x86_pmu_caps_group,
	शून्य,
पूर्ण;

अटल व्योम x86_pmu_sched_task(काष्ठा perf_event_context *ctx, bool sched_in)
अणु
	अटल_call_cond(x86_pmu_sched_task)(ctx, sched_in);
पूर्ण

अटल व्योम x86_pmu_swap_task_ctx(काष्ठा perf_event_context *prev,
				  काष्ठा perf_event_context *next)
अणु
	अटल_call_cond(x86_pmu_swap_task_ctx)(prev, next);
पूर्ण

व्योम perf_check_microcode(व्योम)
अणु
	अगर (x86_pmu.check_microcode)
		x86_pmu.check_microcode();
पूर्ण

अटल पूर्णांक x86_pmu_check_period(काष्ठा perf_event *event, u64 value)
अणु
	अगर (x86_pmu.check_period && x86_pmu.check_period(event, value))
		वापस -EINVAL;

	अगर (value && x86_pmu.limit_period) अणु
		अगर (x86_pmu.limit_period(event, value) > value)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_aux_output_match(काष्ठा perf_event *event)
अणु
	अगर (!(pmu.capabilities & PERF_PMU_CAP_AUX_OUTPUT))
		वापस 0;

	अगर (x86_pmu.aux_output_match)
		वापस x86_pmu.aux_output_match(event);

	वापस 0;
पूर्ण

अटल पूर्णांक x86_pmu_filter_match(काष्ठा perf_event *event)
अणु
	अगर (x86_pmu.filter_match)
		वापस x86_pmu.filter_match(event);

	वापस 1;
पूर्ण

अटल काष्ठा pmu pmu = अणु
	.pmu_enable		= x86_pmu_enable,
	.pmu_disable		= x86_pmu_disable,

	.attr_groups		= x86_pmu_attr_groups,

	.event_init		= x86_pmu_event_init,

	.event_mapped		= x86_pmu_event_mapped,
	.event_unmapped		= x86_pmu_event_unmapped,

	.add			= x86_pmu_add,
	.del			= x86_pmu_del,
	.start			= x86_pmu_start,
	.stop			= x86_pmu_stop,
	.पढ़ो			= x86_pmu_पढ़ो,

	.start_txn		= x86_pmu_start_txn,
	.cancel_txn		= x86_pmu_cancel_txn,
	.commit_txn		= x86_pmu_commit_txn,

	.event_idx		= x86_pmu_event_idx,
	.sched_task		= x86_pmu_sched_task,
	.swap_task_ctx		= x86_pmu_swap_task_ctx,
	.check_period		= x86_pmu_check_period,

	.aux_output_match	= x86_pmu_aux_output_match,

	.filter_match		= x86_pmu_filter_match,
पूर्ण;

व्योम arch_perf_update_userpage(काष्ठा perf_event *event,
			       काष्ठा perf_event_mmap_page *userpg, u64 now)
अणु
	काष्ठा cyc2ns_data data;
	u64 offset;

	userpg->cap_user_समय = 0;
	userpg->cap_user_समय_zero = 0;
	userpg->cap_user_rdpmc =
		!!(event->hw.flags & PERF_X86_EVENT_RDPMC_ALLOWED);
	userpg->pmc_width = x86_pmu.cntval_bits;

	अगर (!using_native_sched_घड़ी() || !sched_घड़ी_stable())
		वापस;

	cyc2ns_पढ़ो_begin(&data);

	offset = data.cyc2ns_offset + __sched_घड़ी_offset;

	/*
	 * Internal समयkeeping क्रम enabled/running/stopped बार
	 * is always in the local_घड़ी करोमुख्य.
	 */
	userpg->cap_user_समय = 1;
	userpg->समय_mult = data.cyc2ns_mul;
	userpg->समय_shअगरt = data.cyc2ns_shअगरt;
	userpg->समय_offset = offset - now;

	/*
	 * cap_user_समय_zero करोesn't make sense when we're using a dअगरferent
	 * समय base क्रम the records.
	 */
	अगर (!event->attr.use_घड़ीid) अणु
		userpg->cap_user_समय_zero = 1;
		userpg->समय_zero = offset;
	पूर्ण

	cyc2ns_पढ़ो_end();
पूर्ण

/*
 * Determine whether the regs were taken from an irq/exception handler rather
 * than from perf_arch_fetch_caller_regs().
 */
अटल bool perf_hw_regs(काष्ठा pt_regs *regs)
अणु
	वापस regs->flags & X86_EFLAGS_FIXED;
पूर्ण

व्योम
perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ addr;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* TODO: We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	अगर (perf_callchain_store(entry, regs->ip))
		वापस;

	अगर (perf_hw_regs(regs))
		unwind_start(&state, current, regs, शून्य);
	अन्यथा
		unwind_start(&state, current, शून्य, (व्योम *)regs->sp);

	क्रम (; !unwind_करोne(&state); unwind_next_frame(&state)) अणु
		addr = unwind_get_वापस_address(&state);
		अगर (!addr || perf_callchain_store(entry, addr))
			वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
valid_user_frame(स्थिर व्योम __user *fp, अचिन्हित दीर्घ size)
अणु
	वापस (__range_not_ok(fp, size, TASK_SIZE) == 0);
पूर्ण

अटल अचिन्हित दीर्घ get_segment_base(अचिन्हित पूर्णांक segment)
अणु
	काष्ठा desc_काष्ठा *desc;
	अचिन्हित पूर्णांक idx = segment >> 3;

	अगर ((segment & SEGMENT_TI_MASK) == SEGMENT_LDT) अणु
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
		काष्ठा ldt_काष्ठा *ldt;

		/* IRQs are off, so this synchronizes with smp_store_release */
		ldt = READ_ONCE(current->active_mm->context.ldt);
		अगर (!ldt || idx >= ldt->nr_entries)
			वापस 0;

		desc = &ldt->entries[idx];
#अन्यथा
		वापस 0;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर (idx >= GDT_ENTRIES)
			वापस 0;

		desc = raw_cpu_ptr(gdt_page.gdt) + idx;
	पूर्ण

	वापस get_desc_base(desc);
पूर्ण

#अगर_घोषित CONFIG_IA32_EMULATION

#समावेश <linux/compat.h>

अटल अंतरभूत पूर्णांक
perf_callchain_user32(काष्ठा pt_regs *regs, काष्ठा perf_callchain_entry_ctx *entry)
अणु
	/* 32-bit process in 64-bit kernel. */
	अचिन्हित दीर्घ ss_base, cs_base;
	काष्ठा stack_frame_ia32 frame;
	स्थिर काष्ठा stack_frame_ia32 __user *fp;

	अगर (user_64bit_mode(regs))
		वापस 0;

	cs_base = get_segment_base(regs->cs);
	ss_base = get_segment_base(regs->ss);

	fp = compat_ptr(ss_base + regs->bp);
	pagefault_disable();
	जबतक (entry->nr < entry->max_stack) अणु
		अगर (!valid_user_frame(fp, माप(frame)))
			अवरोध;

		अगर (__get_user(frame.next_frame, &fp->next_frame))
			अवरोध;
		अगर (__get_user(frame.वापस_address, &fp->वापस_address))
			अवरोध;

		perf_callchain_store(entry, cs_base + frame.वापस_address);
		fp = compat_ptr(ss_base + frame.next_frame);
	पूर्ण
	pagefault_enable();
	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
perf_callchain_user32(काष्ठा pt_regs *regs, काष्ठा perf_callchain_entry_ctx *entry)
अणु
    वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम
perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	काष्ठा stack_frame frame;
	स्थिर काष्ठा stack_frame __user *fp;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* TODO: We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	/*
	 * We करोn't know what to करो with VM86 stacks.. ignore them क्रम now.
	 */
	अगर (regs->flags & (X86_VM_MASK | PERF_EFLAGS_VM))
		वापस;

	fp = (व्योम __user *)regs->bp;

	perf_callchain_store(entry, regs->ip);

	अगर (!nmi_uaccess_okay())
		वापस;

	अगर (perf_callchain_user32(regs, entry))
		वापस;

	pagefault_disable();
	जबतक (entry->nr < entry->max_stack) अणु
		अगर (!valid_user_frame(fp, माप(frame)))
			अवरोध;

		अगर (__get_user(frame.next_frame, &fp->next_frame))
			अवरोध;
		अगर (__get_user(frame.वापस_address, &fp->वापस_address))
			अवरोध;

		perf_callchain_store(entry, frame.वापस_address);
		fp = (व्योम __user *)frame.next_frame;
	पूर्ण
	pagefault_enable();
पूर्ण

/*
 * Deal with code segment offsets क्रम the various execution modes:
 *
 *   VM86 - the good olde 16 bit days, where the linear address is
 *          20 bits and we use regs->ip + 0x10 * regs->cs.
 *
 *   IA32 - Where we need to look at GDT/LDT segment descriptor tables
 *          to figure out what the 32bit base address is.
 *
 *    X32 - has TIF_X32 set, but is running in x86_64
 *
 * X86_64 - CS,DS,SS,ES are all zero based.
 */
अटल अचिन्हित दीर्घ code_segment_base(काष्ठा pt_regs *regs)
अणु
	/*
	 * For IA32 we look at the GDT/LDT segment base to convert the
	 * effective IP to a linear address.
	 */

#अगर_घोषित CONFIG_X86_32
	/*
	 * If we are in VM86 mode, add the segment offset to convert to a
	 * linear address.
	 */
	अगर (regs->flags & X86_VM_MASK)
		वापस 0x10 * regs->cs;

	अगर (user_mode(regs) && regs->cs != __USER_CS)
		वापस get_segment_base(regs->cs);
#अन्यथा
	अगर (user_mode(regs) && !user_64bit_mode(regs) &&
	    regs->cs != __USER32_CS)
		वापस get_segment_base(regs->cs);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		वापस perf_guest_cbs->get_guest_ip();

	वापस regs->ip + code_segment_base(regs);
पूर्ण

अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs)
अणु
	पूर्णांक misc = 0;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		अगर (perf_guest_cbs->is_user_mode())
			misc |= PERF_RECORD_MISC_GUEST_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_GUEST_KERNEL;
	पूर्ण अन्यथा अणु
		अगर (user_mode(regs))
			misc |= PERF_RECORD_MISC_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_KERNEL;
	पूर्ण

	अगर (regs->flags & PERF_EFLAGS_EXACT)
		misc |= PERF_RECORD_MISC_EXACT_IP;

	वापस misc;
पूर्ण

व्योम perf_get_x86_pmu_capability(काष्ठा x86_pmu_capability *cap)
अणु
	cap->version		= x86_pmu.version;
	/*
	 * KVM करोesn't support the hybrid PMU yet.
	 * Return the common value in global x86_pmu,
	 * which available क्रम all cores.
	 */
	cap->num_counters_gp	= x86_pmu.num_counters;
	cap->num_counters_fixed	= x86_pmu.num_counters_fixed;
	cap->bit_width_gp	= x86_pmu.cntval_bits;
	cap->bit_width_fixed	= x86_pmu.cntval_bits;
	cap->events_mask	= (अचिन्हित पूर्णांक)x86_pmu.events_maskl;
	cap->events_mask_len	= x86_pmu.events_mask_len;
पूर्ण
EXPORT_SYMBOL_GPL(perf_get_x86_pmu_capability);
