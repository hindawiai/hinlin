<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Perf support क्रम the Statistical Profiling Extension, पूर्णांकroduced as
 * part of ARMv8.2.
 *
 * Copyright (C) 2016 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#घोषणा PMUNAME					"arm_spe"
#घोषणा DRVNAME					PMUNAME "_pmu"
#घोषणा pr_fmt(fmt)				DRVNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/capability.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sysreg.h>

#घोषणा ARM_SPE_BUF_PAD_BYTE			0

काष्ठा arm_spe_pmu_buf अणु
	पूर्णांक					nr_pages;
	bool					snapshot;
	व्योम					*base;
पूर्ण;

काष्ठा arm_spe_pmu अणु
	काष्ठा pmu				pmu;
	काष्ठा platक्रमm_device			*pdev;
	cpumask_t				supported_cpus;
	काष्ठा hlist_node			hotplug_node;

	पूर्णांक					irq; /* PPI */
	u16					pmsver;
	u16					min_period;
	u16					counter_sz;

#घोषणा SPE_PMU_FEAT_FILT_EVT			(1UL << 0)
#घोषणा SPE_PMU_FEAT_FILT_TYP			(1UL << 1)
#घोषणा SPE_PMU_FEAT_FILT_LAT			(1UL << 2)
#घोषणा SPE_PMU_FEAT_ARCH_INST			(1UL << 3)
#घोषणा SPE_PMU_FEAT_LDS			(1UL << 4)
#घोषणा SPE_PMU_FEAT_ERND			(1UL << 5)
#घोषणा SPE_PMU_FEAT_DEV_PROBED			(1UL << 63)
	u64					features;

	u16					max_record_sz;
	u16					align;
	काष्ठा perf_output_handle __percpu	*handle;
पूर्ण;

#घोषणा to_spe_pmu(p) (container_of(p, काष्ठा arm_spe_pmu, pmu))

/* Convert a मुक्त-running index from perf पूर्णांकo an SPE buffer offset */
#घोषणा PERF_IDX2OFF(idx, buf)	((idx) % ((buf)->nr_pages << PAGE_SHIFT))

/* Keep track of our dynamic hotplug state */
अटल क्रमागत cpuhp_state arm_spe_pmu_online;

क्रमागत arm_spe_pmu_buf_fault_action अणु
	SPE_PMU_BUF_FAULT_ACT_SPURIOUS,
	SPE_PMU_BUF_FAULT_ACT_FATAL,
	SPE_PMU_BUF_FAULT_ACT_OK,
पूर्ण;

/* This sysfs gunk was really good fun to ग_लिखो. */
क्रमागत arm_spe_pmu_capabilities अणु
	SPE_PMU_CAP_ARCH_INST = 0,
	SPE_PMU_CAP_ERND,
	SPE_PMU_CAP_FEAT_MAX,
	SPE_PMU_CAP_CNT_SZ = SPE_PMU_CAP_FEAT_MAX,
	SPE_PMU_CAP_MIN_IVAL,
पूर्ण;

अटल पूर्णांक arm_spe_pmu_feat_caps[SPE_PMU_CAP_FEAT_MAX] = अणु
	[SPE_PMU_CAP_ARCH_INST]	= SPE_PMU_FEAT_ARCH_INST,
	[SPE_PMU_CAP_ERND]	= SPE_PMU_FEAT_ERND,
पूर्ण;

अटल u32 arm_spe_pmu_cap_get(काष्ठा arm_spe_pmu *spe_pmu, पूर्णांक cap)
अणु
	अगर (cap < SPE_PMU_CAP_FEAT_MAX)
		वापस !!(spe_pmu->features & arm_spe_pmu_feat_caps[cap]);

	चयन (cap) अणु
	हाल SPE_PMU_CAP_CNT_SZ:
		वापस spe_pmu->counter_sz;
	हाल SPE_PMU_CAP_MIN_IVAL:
		वापस spe_pmu->min_period;
	शेष:
		WARN(1, "unknown cap %d\n", cap);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार arm_spe_pmu_cap_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = dev_get_drvdata(dev);
	काष्ठा dev_ext_attribute *ea =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	पूर्णांक cap = (दीर्घ)ea->var;

	वापस sysfs_emit(buf, "%u\n", arm_spe_pmu_cap_get(spe_pmu, cap));
पूर्ण

#घोषणा SPE_EXT_ATTR_ENTRY(_name, _func, _var)				\
	&((काष्ठा dev_ext_attribute[]) अणु				\
		अणु __ATTR(_name, S_IRUGO, _func, शून्य), (व्योम *)_var पूर्ण	\
	पूर्ण)[0].attr.attr

#घोषणा SPE_CAP_EXT_ATTR_ENTRY(_name, _var)				\
	SPE_EXT_ATTR_ENTRY(_name, arm_spe_pmu_cap_show, _var)

अटल काष्ठा attribute *arm_spe_pmu_cap_attr[] = अणु
	SPE_CAP_EXT_ATTR_ENTRY(arch_inst, SPE_PMU_CAP_ARCH_INST),
	SPE_CAP_EXT_ATTR_ENTRY(ernd, SPE_PMU_CAP_ERND),
	SPE_CAP_EXT_ATTR_ENTRY(count_size, SPE_PMU_CAP_CNT_SZ),
	SPE_CAP_EXT_ATTR_ENTRY(min_पूर्णांकerval, SPE_PMU_CAP_MIN_IVAL),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_spe_pmu_cap_group = अणु
	.name	= "caps",
	.attrs	= arm_spe_pmu_cap_attr,
पूर्ण;

/* User ABI */
#घोषणा ATTR_CFG_FLD_ts_enable_CFG		config	/* PMSCR_EL1.TS */
#घोषणा ATTR_CFG_FLD_ts_enable_LO		0
#घोषणा ATTR_CFG_FLD_ts_enable_HI		0
#घोषणा ATTR_CFG_FLD_pa_enable_CFG		config	/* PMSCR_EL1.PA */
#घोषणा ATTR_CFG_FLD_pa_enable_LO		1
#घोषणा ATTR_CFG_FLD_pa_enable_HI		1
#घोषणा ATTR_CFG_FLD_pct_enable_CFG		config	/* PMSCR_EL1.PCT */
#घोषणा ATTR_CFG_FLD_pct_enable_LO		2
#घोषणा ATTR_CFG_FLD_pct_enable_HI		2
#घोषणा ATTR_CFG_FLD_jitter_CFG			config	/* PMSIRR_EL1.RND */
#घोषणा ATTR_CFG_FLD_jitter_LO			16
#घोषणा ATTR_CFG_FLD_jitter_HI			16
#घोषणा ATTR_CFG_FLD_branch_filter_CFG		config	/* PMSFCR_EL1.B */
#घोषणा ATTR_CFG_FLD_branch_filter_LO		32
#घोषणा ATTR_CFG_FLD_branch_filter_HI		32
#घोषणा ATTR_CFG_FLD_load_filter_CFG		config	/* PMSFCR_EL1.LD */
#घोषणा ATTR_CFG_FLD_load_filter_LO		33
#घोषणा ATTR_CFG_FLD_load_filter_HI		33
#घोषणा ATTR_CFG_FLD_store_filter_CFG		config	/* PMSFCR_EL1.ST */
#घोषणा ATTR_CFG_FLD_store_filter_LO		34
#घोषणा ATTR_CFG_FLD_store_filter_HI		34

#घोषणा ATTR_CFG_FLD_event_filter_CFG		config1	/* PMSEVFR_EL1 */
#घोषणा ATTR_CFG_FLD_event_filter_LO		0
#घोषणा ATTR_CFG_FLD_event_filter_HI		63

#घोषणा ATTR_CFG_FLD_min_latency_CFG		config2	/* PMSLATFR_EL1.MINLAT */
#घोषणा ATTR_CFG_FLD_min_latency_LO		0
#घोषणा ATTR_CFG_FLD_min_latency_HI		11

/* Why करोes everything I करो descend पूर्णांकo this? */
#घोषणा __GEN_PMU_FORMAT_ATTR(cfg, lo, hi)				\
	(lo) == (hi) ? #cfg ":" #lo "\n" : #cfg ":" #lo "-" #hi

#घोषणा _GEN_PMU_FORMAT_ATTR(cfg, lo, hi)				\
	__GEN_PMU_FORMAT_ATTR(cfg, lo, hi)

#घोषणा GEN_PMU_FORMAT_ATTR(name)					\
	PMU_FORMAT_ATTR(name,						\
	_GEN_PMU_FORMAT_ATTR(ATTR_CFG_FLD_##name##_CFG,			\
			     ATTR_CFG_FLD_##name##_LO,			\
			     ATTR_CFG_FLD_##name##_HI))

#घोषणा _ATTR_CFG_GET_FLD(attr, cfg, lo, hi)				\
	((((attr)->cfg) >> lo) & GENMASK(hi - lo, 0))

#घोषणा ATTR_CFG_GET_FLD(attr, name)					\
	_ATTR_CFG_GET_FLD(attr,						\
			  ATTR_CFG_FLD_##name##_CFG,			\
			  ATTR_CFG_FLD_##name##_LO,			\
			  ATTR_CFG_FLD_##name##_HI)

GEN_PMU_FORMAT_ATTR(ts_enable);
GEN_PMU_FORMAT_ATTR(pa_enable);
GEN_PMU_FORMAT_ATTR(pct_enable);
GEN_PMU_FORMAT_ATTR(jitter);
GEN_PMU_FORMAT_ATTR(branch_filter);
GEN_PMU_FORMAT_ATTR(load_filter);
GEN_PMU_FORMAT_ATTR(store_filter);
GEN_PMU_FORMAT_ATTR(event_filter);
GEN_PMU_FORMAT_ATTR(min_latency);

अटल काष्ठा attribute *arm_spe_pmu_क्रमmats_attr[] = अणु
	&क्रमmat_attr_ts_enable.attr,
	&क्रमmat_attr_pa_enable.attr,
	&क्रमmat_attr_pct_enable.attr,
	&क्रमmat_attr_jitter.attr,
	&क्रमmat_attr_branch_filter.attr,
	&क्रमmat_attr_load_filter.attr,
	&क्रमmat_attr_store_filter.attr,
	&क्रमmat_attr_event_filter.attr,
	&क्रमmat_attr_min_latency.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_spe_pmu_क्रमmat_group = अणु
	.name	= "format",
	.attrs	= arm_spe_pmu_क्रमmats_attr,
पूर्ण;

अटल sमाप_प्रकार arm_spe_pmu_get_attr_cpumask(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = dev_get_drvdata(dev);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &spe_pmu->supported_cpus);
पूर्ण
अटल DEVICE_ATTR(cpumask, S_IRUGO, arm_spe_pmu_get_attr_cpumask, शून्य);

अटल काष्ठा attribute *arm_spe_pmu_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_spe_pmu_group = अणु
	.attrs	= arm_spe_pmu_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *arm_spe_pmu_attr_groups[] = अणु
	&arm_spe_pmu_group,
	&arm_spe_pmu_cap_group,
	&arm_spe_pmu_क्रमmat_group,
	शून्य,
पूर्ण;

/* Convert between user ABI and रेजिस्टर values */
अटल u64 arm_spe_event_to_pmscr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u64 reg = 0;

	reg |= ATTR_CFG_GET_FLD(attr, ts_enable) << SYS_PMSCR_EL1_TS_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, pa_enable) << SYS_PMSCR_EL1_PA_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, pct_enable) << SYS_PMSCR_EL1_PCT_SHIFT;

	अगर (!attr->exclude_user)
		reg |= BIT(SYS_PMSCR_EL1_E0SPE_SHIFT);

	अगर (!attr->exclude_kernel)
		reg |= BIT(SYS_PMSCR_EL1_E1SPE_SHIFT);

	अगर (IS_ENABLED(CONFIG_PID_IN_CONTEXTIDR) && perfmon_capable())
		reg |= BIT(SYS_PMSCR_EL1_CX_SHIFT);

	वापस reg;
पूर्ण

अटल व्योम arm_spe_event_sanitise_period(काष्ठा perf_event *event)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	u64 period = event->hw.sample_period;
	u64 max_period = SYS_PMSIRR_EL1_INTERVAL_MASK
			 << SYS_PMSIRR_EL1_INTERVAL_SHIFT;

	अगर (period < spe_pmu->min_period)
		period = spe_pmu->min_period;
	अन्यथा अगर (period > max_period)
		period = max_period;
	अन्यथा
		period &= max_period;

	event->hw.sample_period = period;
पूर्ण

अटल u64 arm_spe_event_to_pmsirr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u64 reg = 0;

	arm_spe_event_sanitise_period(event);

	reg |= ATTR_CFG_GET_FLD(attr, jitter) << SYS_PMSIRR_EL1_RND_SHIFT;
	reg |= event->hw.sample_period;

	वापस reg;
पूर्ण

अटल u64 arm_spe_event_to_pmsfcr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u64 reg = 0;

	reg |= ATTR_CFG_GET_FLD(attr, load_filter) << SYS_PMSFCR_EL1_LD_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, store_filter) << SYS_PMSFCR_EL1_ST_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, branch_filter) << SYS_PMSFCR_EL1_B_SHIFT;

	अगर (reg)
		reg |= BIT(SYS_PMSFCR_EL1_FT_SHIFT);

	अगर (ATTR_CFG_GET_FLD(attr, event_filter))
		reg |= BIT(SYS_PMSFCR_EL1_FE_SHIFT);

	अगर (ATTR_CFG_GET_FLD(attr, min_latency))
		reg |= BIT(SYS_PMSFCR_EL1_FL_SHIFT);

	वापस reg;
पूर्ण

अटल u64 arm_spe_event_to_pmsevfr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	वापस ATTR_CFG_GET_FLD(attr, event_filter);
पूर्ण

अटल u64 arm_spe_event_to_pmslatfr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	वापस ATTR_CFG_GET_FLD(attr, min_latency)
	       << SYS_PMSLATFR_EL1_MINLAT_SHIFT;
पूर्ण

अटल व्योम arm_spe_pmu_pad_buf(काष्ठा perf_output_handle *handle, पूर्णांक len)
अणु
	काष्ठा arm_spe_pmu_buf *buf = perf_get_aux(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	स_रखो(buf->base + head, ARM_SPE_BUF_PAD_BYTE, len);
	अगर (!buf->snapshot)
		perf_aux_output_skip(handle, len);
पूर्ण

अटल u64 arm_spe_pmu_next_snapshot_off(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा arm_spe_pmu_buf *buf = perf_get_aux(handle);
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(handle->event->pmu);
	u64 head = PERF_IDX2OFF(handle->head, buf);
	u64 limit = buf->nr_pages * PAGE_SIZE;

	/*
	 * The trace क्रमmat isn't parseable in reverse, so clamp
	 * the limit to half of the buffer size in snapshot mode
	 * so that the worst हाल is half a buffer of records, as
	 * opposed to a single record.
	 */
	अगर (head < limit >> 1)
		limit >>= 1;

	/*
	 * If we're within max_record_sz of the limit, we must
	 * pad, move the head index and recompute the limit.
	 */
	अगर (limit - head < spe_pmu->max_record_sz) अणु
		arm_spe_pmu_pad_buf(handle, limit - head);
		handle->head = PERF_IDX2OFF(limit, buf);
		limit = ((buf->nr_pages * PAGE_SIZE) >> 1) + handle->head;
	पूर्ण

	वापस limit;
पूर्ण

अटल u64 __arm_spe_pmu_next_off(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(handle->event->pmu);
	काष्ठा arm_spe_pmu_buf *buf = perf_get_aux(handle);
	स्थिर u64 bufsize = buf->nr_pages * PAGE_SIZE;
	u64 limit = bufsize;
	u64 head, tail, wakeup;

	/*
	 * The head can be misaligned क्रम two reasons:
	 *
	 * 1. The hardware left PMBPTR poपूर्णांकing to the first byte after
	 *    a record when generating a buffer management event.
	 *
	 * 2. We used perf_aux_output_skip to consume handle->size bytes
	 *    and CIRC_SPACE was used to compute the size, which always
	 *    leaves one entry मुक्त.
	 *
	 * Deal with this by padding to the next alignment boundary and
	 * moving the head index. If we run out of buffer space, we'll
	 * reduce handle->size to zero and end up reporting truncation.
	 */
	head = PERF_IDX2OFF(handle->head, buf);
	अगर (!IS_ALIGNED(head, spe_pmu->align)) अणु
		अचिन्हित दीर्घ delta = roundup(head, spe_pmu->align) - head;

		delta = min(delta, handle->size);
		arm_spe_pmu_pad_buf(handle, delta);
		head = PERF_IDX2OFF(handle->head, buf);
	पूर्ण

	/* If we've run out of मुक्त space, then nothing more to करो */
	अगर (!handle->size)
		जाओ no_space;

	/* Compute the tail and wakeup indices now that we've aligned head */
	tail = PERF_IDX2OFF(handle->head + handle->size, buf);
	wakeup = PERF_IDX2OFF(handle->wakeup, buf);

	/*
	 * Aव्योम clobbering unconsumed data. We know we have space, so
	 * अगर we see head == tail we know that the buffer is empty. If
	 * head > tail, then there's nothing to clobber prior to
	 * wrapping.
	 */
	अगर (head < tail)
		limit = round_करोwn(tail, PAGE_SIZE);

	/*
	 * Wakeup may be arbitrarily far पूर्णांकo the future. If it's not in
	 * the current generation, either we'll wrap beक्रमe hitting it,
	 * or it's in the past and has been handled alपढ़ोy.
	 *
	 * If there's a wakeup beक्रमe we wrap, arrange to be woken up by
	 * the page boundary following it. Keep the tail boundary अगर
	 * that's lower.
	 */
	अगर (handle->wakeup < (handle->head + handle->size) && head <= wakeup)
		limit = min(limit, round_up(wakeup, PAGE_SIZE));

	अगर (limit > head)
		वापस limit;

	arm_spe_pmu_pad_buf(handle, handle->size);
no_space:
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, 0);
	वापस 0;
पूर्ण

अटल u64 arm_spe_pmu_next_off(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा arm_spe_pmu_buf *buf = perf_get_aux(handle);
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(handle->event->pmu);
	u64 limit = __arm_spe_pmu_next_off(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	/*
	 * If the head has come too बंद to the end of the buffer,
	 * then pad to the end and recompute the limit.
	 */
	अगर (limit && (limit - head < spe_pmu->max_record_sz)) अणु
		arm_spe_pmu_pad_buf(handle, limit - head);
		limit = __arm_spe_pmu_next_off(handle);
	पूर्ण

	वापस limit;
पूर्ण

अटल व्योम arm_spe_perf_aux_output_begin(काष्ठा perf_output_handle *handle,
					  काष्ठा perf_event *event)
अणु
	u64 base, limit;
	काष्ठा arm_spe_pmu_buf *buf;

	/* Start a new aux session */
	buf = perf_aux_output_begin(handle, event);
	अगर (!buf) अणु
		event->hw.state |= PERF_HES_STOPPED;
		/*
		 * We still need to clear the limit poपूर्णांकer, since the
		 * profiler might only be disabled by virtue of a fault.
		 */
		limit = 0;
		जाओ out_ग_लिखो_limit;
	पूर्ण

	limit = buf->snapshot ? arm_spe_pmu_next_snapshot_off(handle)
			      : arm_spe_pmu_next_off(handle);
	अगर (limit)
		limit |= BIT(SYS_PMBLIMITR_EL1_E_SHIFT);

	limit += (u64)buf->base;
	base = (u64)buf->base + PERF_IDX2OFF(handle->head, buf);
	ग_लिखो_sysreg_s(base, SYS_PMBPTR_EL1);

out_ग_लिखो_limit:
	ग_लिखो_sysreg_s(limit, SYS_PMBLIMITR_EL1);
पूर्ण

अटल व्योम arm_spe_perf_aux_output_end(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा arm_spe_pmu_buf *buf = perf_get_aux(handle);
	u64 offset, size;

	offset = पढ़ो_sysreg_s(SYS_PMBPTR_EL1) - (u64)buf->base;
	size = offset - PERF_IDX2OFF(handle->head, buf);

	अगर (buf->snapshot)
		handle->head = offset;

	perf_aux_output_end(handle, size);
पूर्ण

अटल व्योम arm_spe_pmu_disable_and_drain_local(व्योम)
अणु
	/* Disable profiling at EL0 and EL1 */
	ग_लिखो_sysreg_s(0, SYS_PMSCR_EL1);
	isb();

	/* Drain any buffered data */
	psb_csync();
	dsb(nsh);

	/* Disable the profiling buffer */
	ग_लिखो_sysreg_s(0, SYS_PMBLIMITR_EL1);
	isb();
पूर्ण

/* IRQ handling */
अटल क्रमागत arm_spe_pmu_buf_fault_action
arm_spe_pmu_buf_get_fault_act(काष्ठा perf_output_handle *handle)
अणु
	स्थिर अक्षर *err_str;
	u64 pmbsr;
	क्रमागत arm_spe_pmu_buf_fault_action ret;

	/*
	 * Ensure new profiling data is visible to the CPU and any बाह्यal
	 * पातs have been resolved.
	 */
	psb_csync();
	dsb(nsh);

	/* Ensure hardware updates to PMBPTR_EL1 are visible */
	isb();

	/* Service required? */
	pmbsr = पढ़ो_sysreg_s(SYS_PMBSR_EL1);
	अगर (!(pmbsr & BIT(SYS_PMBSR_EL1_S_SHIFT)))
		वापस SPE_PMU_BUF_FAULT_ACT_SPURIOUS;

	/*
	 * If we've lost data, disable profiling and also set the PARTIAL
	 * flag to indicate that the last record is corrupted.
	 */
	अगर (pmbsr & BIT(SYS_PMBSR_EL1_DL_SHIFT))
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED |
					     PERF_AUX_FLAG_PARTIAL);

	/* Report collisions to userspace so that it can up the period */
	अगर (pmbsr & BIT(SYS_PMBSR_EL1_COLL_SHIFT))
		perf_aux_output_flag(handle, PERF_AUX_FLAG_COLLISION);

	/* We only expect buffer management events */
	चयन (pmbsr & (SYS_PMBSR_EL1_EC_MASK << SYS_PMBSR_EL1_EC_SHIFT)) अणु
	हाल SYS_PMBSR_EL1_EC_BUF:
		/* Handled below */
		अवरोध;
	हाल SYS_PMBSR_EL1_EC_FAULT_S1:
	हाल SYS_PMBSR_EL1_EC_FAULT_S2:
		err_str = "Unexpected buffer fault";
		जाओ out_err;
	शेष:
		err_str = "Unknown error code";
		जाओ out_err;
	पूर्ण

	/* Buffer management event */
	चयन (pmbsr &
		(SYS_PMBSR_EL1_BUF_BSC_MASK << SYS_PMBSR_EL1_BUF_BSC_SHIFT)) अणु
	हाल SYS_PMBSR_EL1_BUF_BSC_FULL:
		ret = SPE_PMU_BUF_FAULT_ACT_OK;
		जाओ out_stop;
	शेष:
		err_str = "Unknown buffer status code";
	पूर्ण

out_err:
	pr_err_ratelimited("%s on CPU %d [PMBSR=0x%016llx, PMBPTR=0x%016llx, PMBLIMITR=0x%016llx]\n",
			   err_str, smp_processor_id(), pmbsr,
			   पढ़ो_sysreg_s(SYS_PMBPTR_EL1),
			   पढ़ो_sysreg_s(SYS_PMBLIMITR_EL1));
	ret = SPE_PMU_BUF_FAULT_ACT_FATAL;

out_stop:
	arm_spe_perf_aux_output_end(handle);
	वापस ret;
पूर्ण

अटल irqवापस_t arm_spe_pmu_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा perf_output_handle *handle = dev;
	काष्ठा perf_event *event = handle->event;
	क्रमागत arm_spe_pmu_buf_fault_action act;

	अगर (!perf_get_aux(handle))
		वापस IRQ_NONE;

	act = arm_spe_pmu_buf_get_fault_act(handle);
	अगर (act == SPE_PMU_BUF_FAULT_ACT_SPURIOUS)
		वापस IRQ_NONE;

	/*
	 * Ensure perf callbacks have completed, which may disable the
	 * profiling buffer in response to a TRUNCATION flag.
	 */
	irq_work_run();

	चयन (act) अणु
	हाल SPE_PMU_BUF_FAULT_ACT_FATAL:
		/*
		 * If a fatal exception occurred then leaving the profiling
		 * buffer enabled is a recipe रुकोing to happen. Since
		 * fatal faults करोn't always imply truncation, make sure
		 * that the profiling buffer is disabled explicitly beक्रमe
		 * clearing the syndrome रेजिस्टर.
		 */
		arm_spe_pmu_disable_and_drain_local();
		अवरोध;
	हाल SPE_PMU_BUF_FAULT_ACT_OK:
		/*
		 * We handled the fault (the buffer was full), so resume
		 * profiling as दीर्घ as we didn't detect truncation.
		 * PMBPTR might be misaligned, but we'll burn that bridge
		 * when we get to it.
		 */
		अगर (!(handle->aux_flags & PERF_AUX_FLAG_TRUNCATED)) अणु
			arm_spe_perf_aux_output_begin(handle, event);
			isb();
		पूर्ण
		अवरोध;
	हाल SPE_PMU_BUF_FAULT_ACT_SPURIOUS:
		/* We've seen you beक्रमe, but GCC has the memory of a sieve. */
		अवरोध;
	पूर्ण

	/* The buffer poपूर्णांकers are now sane, so resume profiling. */
	ग_लिखो_sysreg_s(0, SYS_PMBSR_EL1);
	वापस IRQ_HANDLED;
पूर्ण

अटल u64 arm_spe_pmsevfr_res0(u16 pmsver)
अणु
	चयन (pmsver) अणु
	हाल ID_AA64DFR0_PMSVER_8_2:
		वापस SYS_PMSEVFR_EL1_RES0_8_2;
	हाल ID_AA64DFR0_PMSVER_8_3:
	/* Return the highest version we support in शेष */
	शेष:
		वापस SYS_PMSEVFR_EL1_RES0_8_3;
	पूर्ण
पूर्ण

/* Perf callbacks */
अटल पूर्णांक arm_spe_pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 reg;
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);

	/* This is, of course, deeply driver-specअगरic */
	अगर (attr->type != event->pmu->type)
		वापस -ENOENT;

	अगर (event->cpu >= 0 &&
	    !cpumask_test_cpu(event->cpu, &spe_pmu->supported_cpus))
		वापस -ENOENT;

	अगर (arm_spe_event_to_pmsevfr(event) & arm_spe_pmsevfr_res0(spe_pmu->pmsver))
		वापस -EOPNOTSUPP;

	अगर (attr->exclude_idle)
		वापस -EOPNOTSUPP;

	/*
	 * Feedback-directed frequency throttling करोesn't work when we
	 * have a buffer of samples. We'd need to manually count the
	 * samples in the buffer when it fills up and adjust the event
	 * count to reflect that. Instead, just क्रमce the user to specअगरy
	 * a sample period.
	 */
	अगर (attr->freq)
		वापस -EINVAL;

	reg = arm_spe_event_to_pmsfcr(event);
	अगर ((reg & BIT(SYS_PMSFCR_EL1_FE_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_EVT))
		वापस -EOPNOTSUPP;

	अगर ((reg & BIT(SYS_PMSFCR_EL1_FT_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_TYP))
		वापस -EOPNOTSUPP;

	अगर ((reg & BIT(SYS_PMSFCR_EL1_FL_SHIFT)) &&
	    !(spe_pmu->features & SPE_PMU_FEAT_FILT_LAT))
		वापस -EOPNOTSUPP;

	reg = arm_spe_event_to_pmscr(event);
	अगर (!perfmon_capable() &&
	    (reg & (BIT(SYS_PMSCR_EL1_PA_SHIFT) |
		    BIT(SYS_PMSCR_EL1_CX_SHIFT) |
		    BIT(SYS_PMSCR_EL1_PCT_SHIFT))))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल व्योम arm_spe_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u64 reg;
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_output_handle *handle = this_cpu_ptr(spe_pmu->handle);

	hwc->state = 0;
	arm_spe_perf_aux_output_begin(handle, event);
	अगर (hwc->state)
		वापस;

	reg = arm_spe_event_to_pmsfcr(event);
	ग_लिखो_sysreg_s(reg, SYS_PMSFCR_EL1);

	reg = arm_spe_event_to_pmsevfr(event);
	ग_लिखो_sysreg_s(reg, SYS_PMSEVFR_EL1);

	reg = arm_spe_event_to_pmslatfr(event);
	ग_लिखो_sysreg_s(reg, SYS_PMSLATFR_EL1);

	अगर (flags & PERF_EF_RELOAD) अणु
		reg = arm_spe_event_to_pmsirr(event);
		ग_लिखो_sysreg_s(reg, SYS_PMSIRR_EL1);
		isb();
		reg = local64_पढ़ो(&hwc->period_left);
		ग_लिखो_sysreg_s(reg, SYS_PMSICR_EL1);
	पूर्ण

	reg = arm_spe_event_to_pmscr(event);
	isb();
	ग_लिखो_sysreg_s(reg, SYS_PMSCR_EL1);
पूर्ण

अटल व्योम arm_spe_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_output_handle *handle = this_cpu_ptr(spe_pmu->handle);

	/* If we're alपढ़ोy stopped, then nothing to करो */
	अगर (hwc->state & PERF_HES_STOPPED)
		वापस;

	/* Stop all trace generation */
	arm_spe_pmu_disable_and_drain_local();

	अगर (flags & PERF_EF_UPDATE) अणु
		/*
		 * If there's a fault pending then ensure we contain it
		 * to this buffer, since we might be on the context-चयन
		 * path.
		 */
		अगर (perf_get_aux(handle)) अणु
			क्रमागत arm_spe_pmu_buf_fault_action act;

			act = arm_spe_pmu_buf_get_fault_act(handle);
			अगर (act == SPE_PMU_BUF_FAULT_ACT_SPURIOUS)
				arm_spe_perf_aux_output_end(handle);
			अन्यथा
				ग_लिखो_sysreg_s(0, SYS_PMBSR_EL1);
		पूर्ण

		/*
		 * This may also contain ECOUNT, but nobody अन्यथा should
		 * be looking at period_left, since we क्रमbid frequency
		 * based sampling.
		 */
		local64_set(&hwc->period_left, पढ़ो_sysreg_s(SYS_PMSICR_EL1));
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण

	hwc->state |= PERF_HES_STOPPED;
पूर्ण

अटल पूर्णांक arm_spe_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक ret = 0;
	काष्ठा arm_spe_pmu *spe_pmu = to_spe_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक cpu = event->cpu == -1 ? smp_processor_id() : event->cpu;

	अगर (!cpumask_test_cpu(cpu, &spe_pmu->supported_cpus))
		वापस -ENOENT;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START) अणु
		arm_spe_pmu_start(event, PERF_EF_RELOAD);
		अगर (hwc->state & PERF_HES_STOPPED)
			ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम arm_spe_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	arm_spe_pmu_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल व्योम arm_spe_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
पूर्ण

अटल व्योम *arm_spe_pmu_setup_aux(काष्ठा perf_event *event, व्योम **pages,
				   पूर्णांक nr_pages, bool snapshot)
अणु
	पूर्णांक i, cpu = event->cpu;
	काष्ठा page **pglist;
	काष्ठा arm_spe_pmu_buf *buf;

	/* We need at least two pages क्रम this to work. */
	अगर (nr_pages < 2)
		वापस शून्य;

	/*
	 * We require an even number of pages क्रम snapshot mode, so that
	 * we can effectively treat the buffer as consisting of two equal
	 * parts and give userspace a fighting chance of getting some
	 * useful data out of it.
	 */
	अगर (snapshot && (nr_pages & 1))
		वापस शून्य;

	अगर (cpu == -1)
		cpu = raw_smp_processor_id();

	buf = kzalloc_node(माप(*buf), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!buf)
		वापस शून्य;

	pglist = kसुस्मृति(nr_pages, माप(*pglist), GFP_KERNEL);
	अगर (!pglist)
		जाओ out_मुक्त_buf;

	क्रम (i = 0; i < nr_pages; ++i)
		pglist[i] = virt_to_page(pages[i]);

	buf->base = vmap(pglist, nr_pages, VM_MAP, PAGE_KERNEL);
	अगर (!buf->base)
		जाओ out_मुक्त_pglist;

	buf->nr_pages	= nr_pages;
	buf->snapshot	= snapshot;

	kमुक्त(pglist);
	वापस buf;

out_मुक्त_pglist:
	kमुक्त(pglist);
out_मुक्त_buf:
	kमुक्त(buf);
	वापस शून्य;
पूर्ण

अटल व्योम arm_spe_pmu_मुक्त_aux(व्योम *aux)
अणु
	काष्ठा arm_spe_pmu_buf *buf = aux;

	vunmap(buf->base);
	kमुक्त(buf);
पूर्ण

/* Initialisation and tearकरोwn functions */
अटल पूर्णांक arm_spe_pmu_perf_init(काष्ठा arm_spe_pmu *spe_pmu)
अणु
	अटल atomic_t pmu_idx = ATOMIC_INIT(-1);

	पूर्णांक idx;
	अक्षर *name;
	काष्ठा device *dev = &spe_pmu->pdev->dev;

	spe_pmu->pmu = (काष्ठा pmu) अणु
		.module = THIS_MODULE,
		.capabilities	= PERF_PMU_CAP_EXCLUSIVE | PERF_PMU_CAP_ITRACE,
		.attr_groups	= arm_spe_pmu_attr_groups,
		/*
		 * We hitch a ride on the software context here, so that
		 * we can support per-task profiling (which is not possible
		 * with the invalid context as it करोesn't get sched callbacks).
		 * This requires that userspace either uses a dummy event क्रम
		 * perf_event_खोलो, since the aux buffer is not setup until
		 * a subsequent mmap, or creates the profiling event in a
		 * disabled state and explicitly PERF_EVENT_IOC_ENABLEs it
		 * once the buffer has been created.
		 */
		.task_ctx_nr	= perf_sw_context,
		.event_init	= arm_spe_pmu_event_init,
		.add		= arm_spe_pmu_add,
		.del		= arm_spe_pmu_del,
		.start		= arm_spe_pmu_start,
		.stop		= arm_spe_pmu_stop,
		.पढ़ो		= arm_spe_pmu_पढ़ो,
		.setup_aux	= arm_spe_pmu_setup_aux,
		.मुक्त_aux	= arm_spe_pmu_मुक्त_aux,
	पूर्ण;

	idx = atomic_inc_वापस(&pmu_idx);
	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s_%d", PMUNAME, idx);
	अगर (!name) अणु
		dev_err(dev, "failed to allocate name for pmu %d\n", idx);
		वापस -ENOMEM;
	पूर्ण

	वापस perf_pmu_रेजिस्टर(&spe_pmu->pmu, name, -1);
पूर्ण

अटल व्योम arm_spe_pmu_perf_destroy(काष्ठा arm_spe_pmu *spe_pmu)
अणु
	perf_pmu_unरेजिस्टर(&spe_pmu->pmu);
पूर्ण

अटल व्योम __arm_spe_pmu_dev_probe(व्योम *info)
अणु
	पूर्णांक fld;
	u64 reg;
	काष्ठा arm_spe_pmu *spe_pmu = info;
	काष्ठा device *dev = &spe_pmu->pdev->dev;

	fld = cpuid_feature_extract_अचिन्हित_field(पढ़ो_cpuid(ID_AA64DFR0_EL1),
						   ID_AA64DFR0_PMSVER_SHIFT);
	अगर (!fld) अणु
		dev_err(dev,
			"unsupported ID_AA64DFR0_EL1.PMSVer [%d] on CPU %d\n",
			fld, smp_processor_id());
		वापस;
	पूर्ण
	spe_pmu->pmsver = (u16)fld;

	/* Read PMBIDR first to determine whether or not we have access */
	reg = पढ़ो_sysreg_s(SYS_PMBIDR_EL1);
	अगर (reg & BIT(SYS_PMBIDR_EL1_P_SHIFT)) अणु
		dev_err(dev,
			"profiling buffer owned by higher exception level\n");
		वापस;
	पूर्ण

	/* Minimum alignment. If it's out-of-range, then fail the probe */
	fld = reg >> SYS_PMBIDR_EL1_ALIGN_SHIFT & SYS_PMBIDR_EL1_ALIGN_MASK;
	spe_pmu->align = 1 << fld;
	अगर (spe_pmu->align > SZ_2K) अणु
		dev_err(dev, "unsupported PMBIDR.Align [%d] on CPU %d\n",
			fld, smp_processor_id());
		वापस;
	पूर्ण

	/* It's now safe to read PMSIDR and figure out what we've got */
	reg = पढ़ो_sysreg_s(SYS_PMSIDR_EL1);
	अगर (reg & BIT(SYS_PMSIDR_EL1_FE_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_EVT;

	अगर (reg & BIT(SYS_PMSIDR_EL1_FT_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_TYP;

	अगर (reg & BIT(SYS_PMSIDR_EL1_FL_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_FILT_LAT;

	अगर (reg & BIT(SYS_PMSIDR_EL1_ARCHINST_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_ARCH_INST;

	अगर (reg & BIT(SYS_PMSIDR_EL1_LDS_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_LDS;

	अगर (reg & BIT(SYS_PMSIDR_EL1_ERND_SHIFT))
		spe_pmu->features |= SPE_PMU_FEAT_ERND;

	/* This field has a spaced out encoding, so just use a look-up */
	fld = reg >> SYS_PMSIDR_EL1_INTERVAL_SHIFT & SYS_PMSIDR_EL1_INTERVAL_MASK;
	चयन (fld) अणु
	हाल 0:
		spe_pmu->min_period = 256;
		अवरोध;
	हाल 2:
		spe_pmu->min_period = 512;
		अवरोध;
	हाल 3:
		spe_pmu->min_period = 768;
		अवरोध;
	हाल 4:
		spe_pmu->min_period = 1024;
		अवरोध;
	हाल 5:
		spe_pmu->min_period = 1536;
		अवरोध;
	हाल 6:
		spe_pmu->min_period = 2048;
		अवरोध;
	हाल 7:
		spe_pmu->min_period = 3072;
		अवरोध;
	शेष:
		dev_warn(dev, "unknown PMSIDR_EL1.Interval [%d]; assuming 8\n",
			 fld);
		fallthrough;
	हाल 8:
		spe_pmu->min_period = 4096;
	पूर्ण

	/* Maximum record size. If it's out-of-range, then fail the probe */
	fld = reg >> SYS_PMSIDR_EL1_MAXSIZE_SHIFT & SYS_PMSIDR_EL1_MAXSIZE_MASK;
	spe_pmu->max_record_sz = 1 << fld;
	अगर (spe_pmu->max_record_sz > SZ_2K || spe_pmu->max_record_sz < 16) अणु
		dev_err(dev, "unsupported PMSIDR_EL1.MaxSize [%d] on CPU %d\n",
			fld, smp_processor_id());
		वापस;
	पूर्ण

	fld = reg >> SYS_PMSIDR_EL1_COUNTSIZE_SHIFT & SYS_PMSIDR_EL1_COUNTSIZE_MASK;
	चयन (fld) अणु
	शेष:
		dev_warn(dev, "unknown PMSIDR_EL1.CountSize [%d]; assuming 2\n",
			 fld);
		fallthrough;
	हाल 2:
		spe_pmu->counter_sz = 12;
	पूर्ण

	dev_info(dev,
		 "probed for CPUs %*pbl [max_record_sz %u, align %u, features 0x%llx]\n",
		 cpumask_pr_args(&spe_pmu->supported_cpus),
		 spe_pmu->max_record_sz, spe_pmu->align, spe_pmu->features);

	spe_pmu->features |= SPE_PMU_FEAT_DEV_PROBED;
	वापस;
पूर्ण

अटल व्योम __arm_spe_pmu_reset_local(व्योम)
अणु
	/*
	 * This is probably overसमाप्त, as we have no idea where we're
	 * draining any buffered data to...
	 */
	arm_spe_pmu_disable_and_drain_local();

	/* Reset the buffer base poपूर्णांकer */
	ग_लिखो_sysreg_s(0, SYS_PMBPTR_EL1);
	isb();

	/* Clear any pending management पूर्णांकerrupts */
	ग_लिखो_sysreg_s(0, SYS_PMBSR_EL1);
	isb();
पूर्ण

अटल व्योम __arm_spe_pmu_setup_one(व्योम *info)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = info;

	__arm_spe_pmu_reset_local();
	enable_percpu_irq(spe_pmu->irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम __arm_spe_pmu_stop_one(व्योम *info)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = info;

	disable_percpu_irq(spe_pmu->irq);
	__arm_spe_pmu_reset_local();
पूर्ण

अटल पूर्णांक arm_spe_pmu_cpu_startup(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_spe_pmu *spe_pmu;

	spe_pmu = hlist_entry_safe(node, काष्ठा arm_spe_pmu, hotplug_node);
	अगर (!cpumask_test_cpu(cpu, &spe_pmu->supported_cpus))
		वापस 0;

	__arm_spe_pmu_setup_one(spe_pmu);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_pmu_cpu_tearकरोwn(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_spe_pmu *spe_pmu;

	spe_pmu = hlist_entry_safe(node, काष्ठा arm_spe_pmu, hotplug_node);
	अगर (!cpumask_test_cpu(cpu, &spe_pmu->supported_cpus))
		वापस 0;

	__arm_spe_pmu_stop_one(spe_pmu);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_spe_pmu_dev_init(काष्ठा arm_spe_pmu *spe_pmu)
अणु
	पूर्णांक ret;
	cpumask_t *mask = &spe_pmu->supported_cpus;

	/* Make sure we probe the hardware on a relevant CPU */
	ret = smp_call_function_any(mask,  __arm_spe_pmu_dev_probe, spe_pmu, 1);
	अगर (ret || !(spe_pmu->features & SPE_PMU_FEAT_DEV_PROBED))
		वापस -ENXIO;

	/* Request our PPIs (note that the IRQ is still disabled) */
	ret = request_percpu_irq(spe_pmu->irq, arm_spe_pmu_irq_handler, DRVNAME,
				 spe_pmu->handle);
	अगर (ret)
		वापस ret;

	/*
	 * Register our hotplug notअगरier now so we करोn't miss any events.
	 * This will enable the IRQ क्रम any supported CPUs that are alपढ़ोy
	 * up.
	 */
	ret = cpuhp_state_add_instance(arm_spe_pmu_online,
				       &spe_pmu->hotplug_node);
	अगर (ret)
		मुक्त_percpu_irq(spe_pmu->irq, spe_pmu->handle);

	वापस ret;
पूर्ण

अटल व्योम arm_spe_pmu_dev_tearकरोwn(काष्ठा arm_spe_pmu *spe_pmu)
अणु
	cpuhp_state_हटाओ_instance(arm_spe_pmu_online, &spe_pmu->hotplug_node);
	मुक्त_percpu_irq(spe_pmu->irq, spe_pmu->handle);
पूर्ण

/* Driver and device probing */
अटल पूर्णांक arm_spe_pmu_irq_probe(काष्ठा arm_spe_pmu *spe_pmu)
अणु
	काष्ठा platक्रमm_device *pdev = spe_pmu->pdev;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (irq < 0)
		वापस -ENXIO;

	अगर (!irq_is_percpu(irq)) अणु
		dev_err(&pdev->dev, "expected PPI but got SPI (%d)\n", irq);
		वापस -EINVAL;
	पूर्ण

	अगर (irq_get_percpu_devid_partition(irq, &spe_pmu->supported_cpus)) अणु
		dev_err(&pdev->dev, "failed to get PPI partition (%d)\n", irq);
		वापस -EINVAL;
	पूर्ण

	spe_pmu->irq = irq;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arm_spe_pmu_of_match[] = अणु
	अणु .compatible = "arm,statistical-profiling-extension-v1", .data = (व्योम *)1 पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_spe_pmu_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id arm_spe_match[] = अणु
	अणु ARMV8_SPE_PDEV_NAME, 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, arm_spe_match);

अटल पूर्णांक arm_spe_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा arm_spe_pmu *spe_pmu;
	काष्ठा device *dev = &pdev->dev;

	/*
	 * If kernelspace is unmapped when running at EL0, then the SPE
	 * buffer will fault and prematurely terminate the AUX session.
	 */
	अगर (arm64_kernel_unmapped_at_el0()) अणु
		dev_warn_once(dev, "profiling buffer inaccessible. Try passing \"kpti=off\" on the kernel command line\n");
		वापस -EPERM;
	पूर्ण

	spe_pmu = devm_kzalloc(dev, माप(*spe_pmu), GFP_KERNEL);
	अगर (!spe_pmu) अणु
		dev_err(dev, "failed to allocate spe_pmu\n");
		वापस -ENOMEM;
	पूर्ण

	spe_pmu->handle = alloc_percpu(typeof(*spe_pmu->handle));
	अगर (!spe_pmu->handle)
		वापस -ENOMEM;

	spe_pmu->pdev = pdev;
	platक्रमm_set_drvdata(pdev, spe_pmu);

	ret = arm_spe_pmu_irq_probe(spe_pmu);
	अगर (ret)
		जाओ out_मुक्त_handle;

	ret = arm_spe_pmu_dev_init(spe_pmu);
	अगर (ret)
		जाओ out_मुक्त_handle;

	ret = arm_spe_pmu_perf_init(spe_pmu);
	अगर (ret)
		जाओ out_tearकरोwn_dev;

	वापस 0;

out_tearकरोwn_dev:
	arm_spe_pmu_dev_tearकरोwn(spe_pmu);
out_मुक्त_handle:
	मुक्त_percpu(spe_pmu->handle);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_spe_pmu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_spe_pmu *spe_pmu = platक्रमm_get_drvdata(pdev);

	arm_spe_pmu_perf_destroy(spe_pmu);
	arm_spe_pmu_dev_tearकरोwn(spe_pmu);
	मुक्त_percpu(spe_pmu->handle);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver arm_spe_pmu_driver = अणु
	.id_table = arm_spe_match,
	.driver	= अणु
		.name		= DRVNAME,
		.of_match_table	= of_match_ptr(arm_spe_pmu_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= arm_spe_pmu_device_probe,
	.हटाओ	= arm_spe_pmu_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init arm_spe_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, DRVNAME,
				      arm_spe_pmu_cpu_startup,
				      arm_spe_pmu_cpu_tearकरोwn);
	अगर (ret < 0)
		वापस ret;
	arm_spe_pmu_online = ret;

	ret = platक्रमm_driver_रेजिस्टर(&arm_spe_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(arm_spe_pmu_online);

	वापस ret;
पूर्ण

अटल व्योम __निकास arm_spe_pmu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arm_spe_pmu_driver);
	cpuhp_हटाओ_multi_state(arm_spe_pmu_online);
पूर्ण

module_init(arm_spe_pmu_init);
module_निकास(arm_spe_pmu_निकास);

MODULE_DESCRIPTION("Perf driver for the ARMv8.2 Statistical Profiling Extension");
MODULE_AUTHOR("Will Deacon <will.deacon@arm.com>");
MODULE_LICENSE("GPL v2");
