<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel(R) Processor Trace PMU driver क्रम perf
 * Copyright (c) 2013-2014, Intel Corporation.
 *
 * Intel PT is specअगरied in the Intel Architecture Inकाष्ठाion Set Extensions
 * Programming Reference:
 * http://software.पूर्णांकel.com/en-us/पूर्णांकel-isa-extensions
 */

#अघोषित DEBUG

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/पूर्णांकel_pt.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#समावेश "../perf_event.h"
#समावेश "pt.h"

अटल DEFINE_PER_CPU(काष्ठा pt, pt_ctx);

अटल काष्ठा pt_pmu pt_pmu;

/*
 * Capabilities of Intel PT hardware, such as number of address bits or
 * supported output schemes, are cached and exported to userspace as "caps"
 * attribute group of pt pmu device
 * (/sys/bus/event_source/devices/पूर्णांकel_pt/caps/) so that userspace can store
 * relevant bits together with पूर्णांकel_pt traces.
 *
 * These are necessary क्रम both trace decoding (payloads_lip, contains address
 * width encoded in IP-related packets), and event configuration (biपंचांगasks with
 * permitted values क्रम certain bit fields).
 */
#घोषणा PT_CAP(_n, _l, _r, _m)						\
	[PT_CAP_ ## _n] = अणु .name = __stringअगरy(_n), .leaf = _l,	\
			    .reg = _r, .mask = _m पूर्ण

अटल काष्ठा pt_cap_desc अणु
	स्थिर अक्षर	*name;
	u32		leaf;
	u8		reg;
	u32		mask;
पूर्ण pt_caps[] = अणु
	PT_CAP(max_subleaf,		0, CPUID_EAX, 0xffffffff),
	PT_CAP(cr3_filtering,		0, CPUID_EBX, BIT(0)),
	PT_CAP(psb_cyc,			0, CPUID_EBX, BIT(1)),
	PT_CAP(ip_filtering,		0, CPUID_EBX, BIT(2)),
	PT_CAP(mtc,			0, CPUID_EBX, BIT(3)),
	PT_CAP(ptग_लिखो,			0, CPUID_EBX, BIT(4)),
	PT_CAP(घातer_event_trace,	0, CPUID_EBX, BIT(5)),
	PT_CAP(topa_output,		0, CPUID_ECX, BIT(0)),
	PT_CAP(topa_multiple_entries,	0, CPUID_ECX, BIT(1)),
	PT_CAP(single_range_output,	0, CPUID_ECX, BIT(2)),
	PT_CAP(output_subsys,		0, CPUID_ECX, BIT(3)),
	PT_CAP(payloads_lip,		0, CPUID_ECX, BIT(31)),
	PT_CAP(num_address_ranges,	1, CPUID_EAX, 0x3),
	PT_CAP(mtc_periods,		1, CPUID_EAX, 0xffff0000),
	PT_CAP(cycle_thresholds,	1, CPUID_EBX, 0xffff),
	PT_CAP(psb_periods,		1, CPUID_EBX, 0xffff0000),
पूर्ण;

u32 पूर्णांकel_pt_validate_cap(u32 *caps, क्रमागत pt_capabilities capability)
अणु
	काष्ठा pt_cap_desc *cd = &pt_caps[capability];
	u32 c = caps[cd->leaf * PT_CPUID_REGS_NUM + cd->reg];
	अचिन्हित पूर्णांक shअगरt = __ffs(cd->mask);

	वापस (c & cd->mask) >> shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pt_validate_cap);

u32 पूर्णांकel_pt_validate_hw_cap(क्रमागत pt_capabilities cap)
अणु
	वापस पूर्णांकel_pt_validate_cap(pt_pmu.caps, cap);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pt_validate_hw_cap);

अटल sमाप_प्रकार pt_cap_show(काष्ठा device *cdev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	क्रमागत pt_capabilities cap = (दीर्घ)ea->var;

	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", पूर्णांकel_pt_validate_hw_cap(cap));
पूर्ण

अटल काष्ठा attribute_group pt_cap_group __ro_after_init = अणु
	.name	= "caps",
पूर्ण;

PMU_FORMAT_ATTR(pt,		"config:0"	);
PMU_FORMAT_ATTR(cyc,		"config:1"	);
PMU_FORMAT_ATTR(pwr_evt,	"config:4"	);
PMU_FORMAT_ATTR(fup_on_ptw,	"config:5"	);
PMU_FORMAT_ATTR(mtc,		"config:9"	);
PMU_FORMAT_ATTR(tsc,		"config:10"	);
PMU_FORMAT_ATTR(noretcomp,	"config:11"	);
PMU_FORMAT_ATTR(ptw,		"config:12"	);
PMU_FORMAT_ATTR(branch,		"config:13"	);
PMU_FORMAT_ATTR(mtc_period,	"config:14-17"	);
PMU_FORMAT_ATTR(cyc_thresh,	"config:19-22"	);
PMU_FORMAT_ATTR(psb_period,	"config:24-27"	);

अटल काष्ठा attribute *pt_क्रमmats_attr[] = अणु
	&क्रमmat_attr_pt.attr,
	&क्रमmat_attr_cyc.attr,
	&क्रमmat_attr_pwr_evt.attr,
	&क्रमmat_attr_fup_on_ptw.attr,
	&क्रमmat_attr_mtc.attr,
	&क्रमmat_attr_tsc.attr,
	&क्रमmat_attr_noretcomp.attr,
	&क्रमmat_attr_ptw.attr,
	&क्रमmat_attr_branch.attr,
	&क्रमmat_attr_mtc_period.attr,
	&क्रमmat_attr_cyc_thresh.attr,
	&क्रमmat_attr_psb_period.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pt_क्रमmat_group = अणु
	.name	= "format",
	.attrs	= pt_क्रमmats_attr,
पूर्ण;

अटल sमाप_प्रकार
pt_timing_attr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_attr, attr);

	चयन (pmu_attr->id) अणु
	हाल 0:
		वापस प्र_लिखो(page, "%lu\n", pt_pmu.max_nonturbo_ratio);
	हाल 1:
		वापस प्र_लिखो(page, "%u:%u\n",
			       pt_pmu.tsc_art_num,
			       pt_pmu.tsc_art_den);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

PMU_EVENT_ATTR(max_nonturbo_ratio, timing_attr_max_nonturbo_ratio, 0,
	       pt_timing_attr_show);
PMU_EVENT_ATTR(tsc_art_ratio, timing_attr_tsc_art_ratio, 1,
	       pt_timing_attr_show);

अटल काष्ठा attribute *pt_timing_attr[] = अणु
	&timing_attr_max_nonturbo_ratio.attr.attr,
	&timing_attr_tsc_art_ratio.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pt_timing_group = अणु
	.attrs	= pt_timing_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pt_attr_groups[] = अणु
	&pt_cap_group,
	&pt_क्रमmat_group,
	&pt_timing_group,
	शून्य,
पूर्ण;

अटल पूर्णांक __init pt_pmu_hw_init(व्योम)
अणु
	काष्ठा dev_ext_attribute *de_attrs;
	काष्ठा attribute **attrs;
	माप_प्रकार size;
	u64 reg;
	पूर्णांक ret;
	दीर्घ i;

	rdmsrl(MSR_PLATFORM_INFO, reg);
	pt_pmu.max_nonturbo_ratio = (reg & 0xff00) >> 8;

	/*
	 * अगर available, पढ़ो in TSC to core crystal घड़ी ratio,
	 * otherwise, zero क्रम numerator stands क्रम "not enumerated"
	 * as per SDM
	 */
	अगर (boot_cpu_data.cpuid_level >= CPUID_TSC_LEAF) अणु
		u32 eax, ebx, ecx, edx;

		cpuid(CPUID_TSC_LEAF, &eax, &ebx, &ecx, &edx);

		pt_pmu.tsc_art_num = ebx;
		pt_pmu.tsc_art_den = eax;
	पूर्ण

	/* model-specअगरic quirks */
	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_BROADWELL:
	हाल INTEL_FAM6_BROADWELL_D:
	हाल INTEL_FAM6_BROADWELL_G:
	हाल INTEL_FAM6_BROADWELL_X:
		/* not setting BRANCH_EN will #GP, erratum BDM106 */
		pt_pmu.branch_en_always_on = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_VMX)) अणु
		/*
		 * Intel SDM, 36.5 "Tracing post-VMXON" says that
		 * "IA32_VMX_MISC[bit 14]" being 1 means PT can trace
		 * post-VMXON.
		 */
		rdmsrl(MSR_IA32_VMX_MISC, reg);
		अगर (reg & BIT(14))
			pt_pmu.vmx = true;
	पूर्ण

	क्रम (i = 0; i < PT_CPUID_LEAVES; i++) अणु
		cpuid_count(20, i,
			    &pt_pmu.caps[CPUID_EAX + i*PT_CPUID_REGS_NUM],
			    &pt_pmu.caps[CPUID_EBX + i*PT_CPUID_REGS_NUM],
			    &pt_pmu.caps[CPUID_ECX + i*PT_CPUID_REGS_NUM],
			    &pt_pmu.caps[CPUID_EDX + i*PT_CPUID_REGS_NUM]);
	पूर्ण

	ret = -ENOMEM;
	size = माप(काष्ठा attribute *) * (ARRAY_SIZE(pt_caps)+1);
	attrs = kzalloc(size, GFP_KERNEL);
	अगर (!attrs)
		जाओ fail;

	size = माप(काष्ठा dev_ext_attribute) * (ARRAY_SIZE(pt_caps)+1);
	de_attrs = kzalloc(size, GFP_KERNEL);
	अगर (!de_attrs)
		जाओ fail;

	क्रम (i = 0; i < ARRAY_SIZE(pt_caps); i++) अणु
		काष्ठा dev_ext_attribute *de_attr = de_attrs + i;

		de_attr->attr.attr.name = pt_caps[i].name;

		sysfs_attr_init(&de_attr->attr.attr);

		de_attr->attr.attr.mode		= S_IRUGO;
		de_attr->attr.show		= pt_cap_show;
		de_attr->var			= (व्योम *)i;

		attrs[i] = &de_attr->attr.attr;
	पूर्ण

	pt_cap_group.attrs = attrs;

	वापस 0;

fail:
	kमुक्त(attrs);

	वापस ret;
पूर्ण

#घोषणा RTIT_CTL_CYC_PSB (RTIT_CTL_CYCLEACC	| \
			  RTIT_CTL_CYC_THRESH	| \
			  RTIT_CTL_PSB_FREQ)

#घोषणा RTIT_CTL_MTC	(RTIT_CTL_MTC_EN	| \
			 RTIT_CTL_MTC_RANGE)

#घोषणा RTIT_CTL_PTW	(RTIT_CTL_PTW_EN	| \
			 RTIT_CTL_FUP_ON_PTW)

/*
 * Bit 0 (TraceEn) in the attr.config is meaningless as the
 * corresponding bit in the RTIT_CTL can only be controlled
 * by the driver; thereक्रमe, repurpose it to mean: pass
 * through the bit that was previously assumed to be always
 * on क्रम PT, thereby allowing the user to *not* set it अगर
 * they so wish. See also pt_event_valid() and pt_config().
 */
#घोषणा RTIT_CTL_PASSTHROUGH RTIT_CTL_TRACEEN

#घोषणा PT_CONFIG_MASK (RTIT_CTL_TRACEEN	| \
			RTIT_CTL_TSC_EN		| \
			RTIT_CTL_DISRETC	| \
			RTIT_CTL_BRANCH_EN	| \
			RTIT_CTL_CYC_PSB	| \
			RTIT_CTL_MTC		| \
			RTIT_CTL_PWR_EVT_EN	| \
			RTIT_CTL_FUP_ON_PTW	| \
			RTIT_CTL_PTW_EN)

अटल bool pt_event_valid(काष्ठा perf_event *event)
अणु
	u64 config = event->attr.config;
	u64 allowed, requested;

	अगर ((config & PT_CONFIG_MASK) != config)
		वापस false;

	अगर (config & RTIT_CTL_CYC_PSB) अणु
		अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_psb_cyc))
			वापस false;

		allowed = पूर्णांकel_pt_validate_hw_cap(PT_CAP_psb_periods);
		requested = (config & RTIT_CTL_PSB_FREQ) >>
			RTIT_CTL_PSB_FREQ_OFFSET;
		अगर (requested && (!(allowed & BIT(requested))))
			वापस false;

		allowed = पूर्णांकel_pt_validate_hw_cap(PT_CAP_cycle_thresholds);
		requested = (config & RTIT_CTL_CYC_THRESH) >>
			RTIT_CTL_CYC_THRESH_OFFSET;
		अगर (requested && (!(allowed & BIT(requested))))
			वापस false;
	पूर्ण

	अगर (config & RTIT_CTL_MTC) अणु
		/*
		 * In the unlikely हाल that CPUID lists valid mtc periods,
		 * but not the mtc capability, drop out here.
		 *
		 * Spec says that setting mtc period bits जबतक mtc bit in
		 * CPUID is 0 will #GP, so better safe than sorry.
		 */
		अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_mtc))
			वापस false;

		allowed = पूर्णांकel_pt_validate_hw_cap(PT_CAP_mtc_periods);
		अगर (!allowed)
			वापस false;

		requested = (config & RTIT_CTL_MTC_RANGE) >>
			RTIT_CTL_MTC_RANGE_OFFSET;

		अगर (!(allowed & BIT(requested)))
			वापस false;
	पूर्ण

	अगर (config & RTIT_CTL_PWR_EVT_EN &&
	    !पूर्णांकel_pt_validate_hw_cap(PT_CAP_घातer_event_trace))
		वापस false;

	अगर (config & RTIT_CTL_PTW) अणु
		अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_ptग_लिखो))
			वापस false;

		/* FUPonPTW without PTW करोesn't make sense */
		अगर ((config & RTIT_CTL_FUP_ON_PTW) &&
		    !(config & RTIT_CTL_PTW_EN))
			वापस false;
	पूर्ण

	/*
	 * Setting bit 0 (TraceEn in RTIT_CTL MSR) in the attr.config
	 * clears the assumption that BranchEn must always be enabled,
	 * as was the हाल with the first implementation of PT.
	 * If this bit is not set, the legacy behavior is preserved
	 * क्रम compatibility with the older userspace.
	 *
	 * Re-using bit 0 क्रम this purpose is fine because it is never
	 * directly set by the user; previous attempts at setting it in
	 * the attr.config resulted in -EINVAL.
	 */
	अगर (config & RTIT_CTL_PASSTHROUGH) अणु
		/*
		 * Disallow not setting BRANCH_EN where BRANCH_EN is
		 * always required.
		 */
		अगर (pt_pmu.branch_en_always_on &&
		    !(config & RTIT_CTL_BRANCH_EN))
			वापस false;
	पूर्ण अन्यथा अणु
		/*
		 * Disallow BRANCH_EN without the PASSTHROUGH.
		 */
		अगर (config & RTIT_CTL_BRANCH_EN)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * PT configuration helpers
 * These all are cpu affine and operate on a local PT
 */

अटल व्योम pt_config_start(काष्ठा perf_event *event)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	u64 ctl = event->hw.config;

	ctl |= RTIT_CTL_TRACEEN;
	अगर (READ_ONCE(pt->vmx_on))
		perf_aux_output_flag(&pt->handle, PERF_AUX_FLAG_PARTIAL);
	अन्यथा
		wrmsrl(MSR_IA32_RTIT_CTL, ctl);

	WRITE_ONCE(event->hw.config, ctl);
पूर्ण

/* Address ranges and their corresponding msr configuration रेजिस्टरs */
अटल स्थिर काष्ठा pt_address_range अणु
	अचिन्हित दीर्घ	msr_a;
	अचिन्हित दीर्घ	msr_b;
	अचिन्हित पूर्णांक	reg_off;
पूर्ण pt_address_ranges[] = अणु
	अणु
		.msr_a	 = MSR_IA32_RTIT_ADDR0_A,
		.msr_b	 = MSR_IA32_RTIT_ADDR0_B,
		.reg_off = RTIT_CTL_ADDR0_OFFSET,
	पूर्ण,
	अणु
		.msr_a	 = MSR_IA32_RTIT_ADDR1_A,
		.msr_b	 = MSR_IA32_RTIT_ADDR1_B,
		.reg_off = RTIT_CTL_ADDR1_OFFSET,
	पूर्ण,
	अणु
		.msr_a	 = MSR_IA32_RTIT_ADDR2_A,
		.msr_b	 = MSR_IA32_RTIT_ADDR2_B,
		.reg_off = RTIT_CTL_ADDR2_OFFSET,
	पूर्ण,
	अणु
		.msr_a	 = MSR_IA32_RTIT_ADDR3_A,
		.msr_b	 = MSR_IA32_RTIT_ADDR3_B,
		.reg_off = RTIT_CTL_ADDR3_OFFSET,
	पूर्ण
पूर्ण;

अटल u64 pt_config_filters(काष्ठा perf_event *event)
अणु
	काष्ठा pt_filters *filters = event->hw.addr_filters;
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	अचिन्हित पूर्णांक range = 0;
	u64 rtit_ctl = 0;

	अगर (!filters)
		वापस 0;

	perf_event_addr_filters_sync(event);

	क्रम (range = 0; range < filters->nr_filters; range++) अणु
		काष्ठा pt_filter *filter = &filters->filter[range];

		/*
		 * Note, अगर the range has zero start/end addresses due
		 * to its dynamic object not being loaded yet, we just
		 * go ahead and program zeroed range, which will simply
		 * produce no data. Note^2: अगर executable code at 0x0
		 * is a concern, we can set up an "invalid" configuration
		 * such as msr_b < msr_a.
		 */

		/* aव्योम redundant msr ग_लिखोs */
		अगर (pt->filters.filter[range].msr_a != filter->msr_a) अणु
			wrmsrl(pt_address_ranges[range].msr_a, filter->msr_a);
			pt->filters.filter[range].msr_a = filter->msr_a;
		पूर्ण

		अगर (pt->filters.filter[range].msr_b != filter->msr_b) अणु
			wrmsrl(pt_address_ranges[range].msr_b, filter->msr_b);
			pt->filters.filter[range].msr_b = filter->msr_b;
		पूर्ण

		rtit_ctl |= filter->config << pt_address_ranges[range].reg_off;
	पूर्ण

	वापस rtit_ctl;
पूर्ण

अटल व्योम pt_config(काष्ठा perf_event *event)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा pt_buffer *buf = perf_get_aux(&pt->handle);
	u64 reg;

	/* First round: clear STATUS, in particular the PSB byte counter. */
	अगर (!event->hw.config) अणु
		perf_event_itrace_started(event);
		wrmsrl(MSR_IA32_RTIT_STATUS, 0);
	पूर्ण

	reg = pt_config_filters(event);
	reg |= RTIT_CTL_TRACEEN;
	अगर (!buf->single)
		reg |= RTIT_CTL_TOPA;

	/*
	 * Previously, we had BRANCH_EN on by शेष, but now that PT has
	 * grown features outside of branch tracing, it is useful to allow
	 * the user to disable it. Setting bit 0 in the event's attr.config
	 * allows BRANCH_EN to pass through instead of being always on. See
	 * also the comment in pt_event_valid().
	 */
	अगर (event->attr.config & BIT(0)) अणु
		reg |= event->attr.config & RTIT_CTL_BRANCH_EN;
	पूर्ण अन्यथा अणु
		reg |= RTIT_CTL_BRANCH_EN;
	पूर्ण

	अगर (!event->attr.exclude_kernel)
		reg |= RTIT_CTL_OS;
	अगर (!event->attr.exclude_user)
		reg |= RTIT_CTL_USR;

	reg |= (event->attr.config & PT_CONFIG_MASK);

	event->hw.config = reg;
	pt_config_start(event);
पूर्ण

अटल व्योम pt_config_stop(काष्ठा perf_event *event)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	u64 ctl = READ_ONCE(event->hw.config);

	/* may be alपढ़ोy stopped by a PMI */
	अगर (!(ctl & RTIT_CTL_TRACEEN))
		वापस;

	ctl &= ~RTIT_CTL_TRACEEN;
	अगर (!READ_ONCE(pt->vmx_on))
		wrmsrl(MSR_IA32_RTIT_CTL, ctl);

	WRITE_ONCE(event->hw.config, ctl);

	/*
	 * A wrmsr that disables trace generation serializes other PT
	 * रेजिस्टरs and causes all data packets to be written to memory,
	 * but a fence is required क्रम the data to become globally visible.
	 *
	 * The below WMB, separating data store and aux_head store matches
	 * the consumer's RMB that separates aux_head load and data load.
	 */
	wmb();
पूर्ण

/**
 * काष्ठा topa - ToPA metadata
 * @list:	linkage to काष्ठा pt_buffer's list of tables
 * @offset:	offset of the first entry in this table in the buffer
 * @size:	total size of all entries in this table
 * @last:	index of the last initialized entry in this table
 * @z_count:	how many बार the first entry repeats
 */
काष्ठा topa अणु
	काष्ठा list_head	list;
	u64			offset;
	माप_प्रकार			size;
	पूर्णांक			last;
	अचिन्हित पूर्णांक		z_count;
पूर्ण;

/*
 * Keep ToPA table-related metadata on the same page as the actual table,
 * taking up a few words from the top
 */

#घोषणा TENTS_PER_PAGE	\
	((PAGE_SIZE - माप(काष्ठा topa)) / माप(काष्ठा topa_entry))

/**
 * काष्ठा topa_page - page-sized ToPA table with metadata at the top
 * @table:	actual ToPA table entries, as understood by PT hardware
 * @topa:	metadata
 */
काष्ठा topa_page अणु
	काष्ठा topa_entry	table[TENTS_PER_PAGE];
	काष्ठा topa		topa;
पूर्ण;

अटल अंतरभूत काष्ठा topa_page *topa_to_page(काष्ठा topa *topa)
अणु
	वापस container_of(topa, काष्ठा topa_page, topa);
पूर्ण

अटल अंतरभूत काष्ठा topa_page *topa_entry_to_page(काष्ठा topa_entry *te)
अणु
	वापस (काष्ठा topa_page *)((अचिन्हित दीर्घ)te & PAGE_MASK);
पूर्ण

अटल अंतरभूत phys_addr_t topa_pfn(काष्ठा topa *topa)
अणु
	वापस PFN_DOWN(virt_to_phys(topa_to_page(topa)));
पूर्ण

/* make -1 stand क्रम the last table entry */
#घोषणा TOPA_ENTRY(t, i)				\
	((i) == -1					\
		? &topa_to_page(t)->table[(t)->last]	\
		: &topa_to_page(t)->table[(i)])
#घोषणा TOPA_ENTRY_SIZE(t, i) (sizes(TOPA_ENTRY((t), (i))->size))
#घोषणा TOPA_ENTRY_PAGES(t, i) (1 << TOPA_ENTRY((t), (i))->size)

अटल व्योम pt_config_buffer(काष्ठा pt_buffer *buf)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	u64 reg, mask;
	व्योम *base;

	अगर (buf->single) अणु
		base = buf->data_pages[0];
		mask = (buf->nr_pages * PAGE_SIZE - 1) >> 7;
	पूर्ण अन्यथा अणु
		base = topa_to_page(buf->cur)->table;
		mask = (u64)buf->cur_idx;
	पूर्ण

	reg = virt_to_phys(base);
	अगर (pt->output_base != reg) अणु
		pt->output_base = reg;
		wrmsrl(MSR_IA32_RTIT_OUTPUT_BASE, reg);
	पूर्ण

	reg = 0x7f | (mask << 7) | ((u64)buf->output_off << 32);
	अगर (pt->output_mask != reg) अणु
		pt->output_mask = reg;
		wrmsrl(MSR_IA32_RTIT_OUTPUT_MASK, reg);
	पूर्ण
पूर्ण

/**
 * topa_alloc() - allocate page-sized ToPA table
 * @cpu:	CPU on which to allocate.
 * @gfp:	Allocation flags.
 *
 * Return:	On success, वापस the poपूर्णांकer to ToPA table page.
 */
अटल काष्ठा topa *topa_alloc(पूर्णांक cpu, gfp_t gfp)
अणु
	पूर्णांक node = cpu_to_node(cpu);
	काष्ठा topa_page *tp;
	काष्ठा page *p;

	p = alloc_pages_node(node, gfp | __GFP_ZERO, 0);
	अगर (!p)
		वापस शून्य;

	tp = page_address(p);
	tp->topa.last = 0;

	/*
	 * In हाल of singe-entry ToPA, always put the self-referencing END
	 * link as the 2nd entry in the table
	 */
	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries)) अणु
		TOPA_ENTRY(&tp->topa, 1)->base = page_to_phys(p) >> TOPA_SHIFT;
		TOPA_ENTRY(&tp->topa, 1)->end = 1;
	पूर्ण

	वापस &tp->topa;
पूर्ण

/**
 * topa_मुक्त() - मुक्त a page-sized ToPA table
 * @topa:	Table to deallocate.
 */
अटल व्योम topa_मुक्त(काष्ठा topa *topa)
अणु
	मुक्त_page((अचिन्हित दीर्घ)topa);
पूर्ण

/**
 * topa_insert_table() - insert a ToPA table पूर्णांकo a buffer
 * @buf:	 PT buffer that's being extended.
 * @topa:	 New topa table to be inserted.
 *
 * If it's the first table in this buffer, set up buffer's poपूर्णांकers
 * accordingly; otherwise, add a END=1 link entry to @topa to the current
 * "last" table and adjust the last table poपूर्णांकer to @topa.
 */
अटल व्योम topa_insert_table(काष्ठा pt_buffer *buf, काष्ठा topa *topa)
अणु
	काष्ठा topa *last = buf->last;

	list_add_tail(&topa->list, &buf->tables);

	अगर (!buf->first) अणु
		buf->first = buf->last = buf->cur = topa;
		वापस;
	पूर्ण

	topa->offset = last->offset + last->size;
	buf->last = topa;

	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		वापस;

	BUG_ON(last->last != TENTS_PER_PAGE - 1);

	TOPA_ENTRY(last, -1)->base = topa_pfn(topa);
	TOPA_ENTRY(last, -1)->end = 1;
पूर्ण

/**
 * topa_table_full() - check अगर a ToPA table is filled up
 * @topa:	ToPA table.
 */
अटल bool topa_table_full(काष्ठा topa *topa)
अणु
	/* single-entry ToPA is a special हाल */
	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		वापस !!topa->last;

	वापस topa->last == TENTS_PER_PAGE - 1;
पूर्ण

/**
 * topa_insert_pages() - create a list of ToPA tables
 * @buf:	PT buffer being initialized.
 * @gfp:	Allocation flags.
 *
 * This initializes a list of ToPA tables with entries from
 * the data_pages provided by rb_alloc_aux().
 *
 * Return:	0 on success or error code.
 */
अटल पूर्णांक topa_insert_pages(काष्ठा pt_buffer *buf, पूर्णांक cpu, gfp_t gfp)
अणु
	काष्ठा topa *topa = buf->last;
	पूर्णांक order = 0;
	काष्ठा page *p;

	p = virt_to_page(buf->data_pages[buf->nr_pages]);
	अगर (PagePrivate(p))
		order = page_निजी(p);

	अगर (topa_table_full(topa)) अणु
		topa = topa_alloc(cpu, gfp);
		अगर (!topa)
			वापस -ENOMEM;

		topa_insert_table(buf, topa);
	पूर्ण

	अगर (topa->z_count == topa->last - 1) अणु
		अगर (order == TOPA_ENTRY(topa, topa->last - 1)->size)
			topa->z_count++;
	पूर्ण

	TOPA_ENTRY(topa, -1)->base = page_to_phys(p) >> TOPA_SHIFT;
	TOPA_ENTRY(topa, -1)->size = order;
	अगर (!buf->snapshot &&
	    !पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries)) अणु
		TOPA_ENTRY(topa, -1)->पूर्णांकr = 1;
		TOPA_ENTRY(topa, -1)->stop = 1;
	पूर्ण

	topa->last++;
	topa->size += sizes(order);

	buf->nr_pages += 1ul << order;

	वापस 0;
पूर्ण

/**
 * pt_topa_dump() - prपूर्णांक ToPA tables and their entries
 * @buf:	PT buffer.
 */
अटल व्योम pt_topa_dump(काष्ठा pt_buffer *buf)
अणु
	काष्ठा topa *topa;

	list_क्रम_each_entry(topa, &buf->tables, list) अणु
		काष्ठा topa_page *tp = topa_to_page(topa);
		पूर्णांक i;

		pr_debug("# table @%p, off %llx size %zx\n", tp->table,
			 topa->offset, topa->size);
		क्रम (i = 0; i < TENTS_PER_PAGE; i++) अणु
			pr_debug("# entry @%p (%lx sz %u %c%c%c) raw=%16llx\n",
				 &tp->table[i],
				 (अचिन्हित दीर्घ)tp->table[i].base << TOPA_SHIFT,
				 sizes(tp->table[i].size),
				 tp->table[i].end ?  'E' : ' ',
				 tp->table[i].पूर्णांकr ? 'I' : ' ',
				 tp->table[i].stop ? 'S' : ' ',
				 *(u64 *)&tp->table[i]);
			अगर ((पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries) &&
			     tp->table[i].stop) ||
			    tp->table[i].end)
				अवरोध;
			अगर (!i && topa->z_count)
				i += topa->z_count;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pt_buffer_advance() - advance to the next output region
 * @buf:	PT buffer.
 *
 * Advance the current poपूर्णांकers in the buffer to the next ToPA entry.
 */
अटल व्योम pt_buffer_advance(काष्ठा pt_buffer *buf)
अणु
	buf->output_off = 0;
	buf->cur_idx++;

	अगर (buf->cur_idx == buf->cur->last) अणु
		अगर (buf->cur == buf->last)
			buf->cur = buf->first;
		अन्यथा
			buf->cur = list_entry(buf->cur->list.next, काष्ठा topa,
					      list);
		buf->cur_idx = 0;
	पूर्ण
पूर्ण

/**
 * pt_update_head() - calculate current offsets and sizes
 * @pt:		Per-cpu pt context.
 *
 * Update buffer's current ग_लिखो poपूर्णांकer position and data size.
 */
अटल व्योम pt_update_head(काष्ठा pt *pt)
अणु
	काष्ठा pt_buffer *buf = perf_get_aux(&pt->handle);
	u64 topa_idx, base, old;

	अगर (buf->single) अणु
		local_set(&buf->data_size, buf->output_off);
		वापस;
	पूर्ण

	/* offset of the first region in this table from the beginning of buf */
	base = buf->cur->offset + buf->output_off;

	/* offset of the current output region within this table */
	क्रम (topa_idx = 0; topa_idx < buf->cur_idx; topa_idx++)
		base += TOPA_ENTRY_SIZE(buf->cur, topa_idx);

	अगर (buf->snapshot) अणु
		local_set(&buf->data_size, base);
	पूर्ण अन्यथा अणु
		old = (local64_xchg(&buf->head, base) &
		       ((buf->nr_pages << PAGE_SHIFT) - 1));
		अगर (base < old)
			base += buf->nr_pages << PAGE_SHIFT;

		local_add(base - old, &buf->data_size);
	पूर्ण
पूर्ण

/**
 * pt_buffer_region() - obtain current output region's address
 * @buf:	PT buffer.
 */
अटल व्योम *pt_buffer_region(काष्ठा pt_buffer *buf)
अणु
	वापस phys_to_virt(TOPA_ENTRY(buf->cur, buf->cur_idx)->base << TOPA_SHIFT);
पूर्ण

/**
 * pt_buffer_region_size() - obtain current output region's size
 * @buf:	PT buffer.
 */
अटल माप_प्रकार pt_buffer_region_size(काष्ठा pt_buffer *buf)
अणु
	वापस TOPA_ENTRY_SIZE(buf->cur, buf->cur_idx);
पूर्ण

/**
 * pt_handle_status() - take care of possible status conditions
 * @pt:		Per-cpu pt context.
 */
अटल व्योम pt_handle_status(काष्ठा pt *pt)
अणु
	काष्ठा pt_buffer *buf = perf_get_aux(&pt->handle);
	पूर्णांक advance = 0;
	u64 status;

	rdmsrl(MSR_IA32_RTIT_STATUS, status);

	अगर (status & RTIT_STATUS_ERROR) अणु
		pr_err_ratelimited("ToPA ERROR encountered, trying to recover\n");
		pt_topa_dump(buf);
		status &= ~RTIT_STATUS_ERROR;
	पूर्ण

	अगर (status & RTIT_STATUS_STOPPED) अणु
		status &= ~RTIT_STATUS_STOPPED;

		/*
		 * On प्रणालीs that only करो single-entry ToPA, hitting STOP
		 * means we are alपढ़ोy losing data; need to let the decoder
		 * know.
		 */
		अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries) ||
		    buf->output_off == pt_buffer_region_size(buf)) अणु
			perf_aux_output_flag(&pt->handle,
			                     PERF_AUX_FLAG_TRUNCATED);
			advance++;
		पूर्ण
	पूर्ण

	/*
	 * Also on single-entry ToPA implementations, पूर्णांकerrupt will come
	 * beक्रमe the output reaches its output region's boundary.
	 */
	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries) &&
	    !buf->snapshot &&
	    pt_buffer_region_size(buf) - buf->output_off <= TOPA_PMI_MARGIN) अणु
		व्योम *head = pt_buffer_region(buf);

		/* everything within this margin needs to be zeroed out */
		स_रखो(head + buf->output_off, 0,
		       pt_buffer_region_size(buf) -
		       buf->output_off);
		advance++;
	पूर्ण

	अगर (advance)
		pt_buffer_advance(buf);

	wrmsrl(MSR_IA32_RTIT_STATUS, status);
पूर्ण

/**
 * pt_पढ़ो_offset() - translate रेजिस्टरs पूर्णांकo buffer poपूर्णांकers
 * @buf:	PT buffer.
 *
 * Set buffer's output poपूर्णांकers from MSR values.
 */
अटल व्योम pt_पढ़ो_offset(काष्ठा pt_buffer *buf)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा topa_page *tp;

	अगर (!buf->single) अणु
		rdmsrl(MSR_IA32_RTIT_OUTPUT_BASE, pt->output_base);
		tp = phys_to_virt(pt->output_base);
		buf->cur = &tp->topa;
	पूर्ण

	rdmsrl(MSR_IA32_RTIT_OUTPUT_MASK, pt->output_mask);
	/* offset within current output region */
	buf->output_off = pt->output_mask >> 32;
	/* index of current output region within this table */
	अगर (!buf->single)
		buf->cur_idx = (pt->output_mask & 0xffffff80) >> 7;
पूर्ण

अटल काष्ठा topa_entry *
pt_topa_entry_क्रम_page(काष्ठा pt_buffer *buf, अचिन्हित पूर्णांक pg)
अणु
	काष्ठा topa_page *tp;
	काष्ठा topa *topa;
	अचिन्हित पूर्णांक idx, cur_pg = 0, z_pg = 0, start_idx = 0;

	/*
	 * Indicates a bug in the caller.
	 */
	अगर (WARN_ON_ONCE(pg >= buf->nr_pages))
		वापस शून्य;

	/*
	 * First, find the ToPA table where @pg fits. With high
	 * order allocations, there shouldn't be many of these.
	 */
	list_क्रम_each_entry(topa, &buf->tables, list) अणु
		अगर (topa->offset + topa->size > pg << PAGE_SHIFT)
			जाओ found;
	पूर्ण

	/*
	 * Hitting this means we have a problem in the ToPA
	 * allocation code.
	 */
	WARN_ON_ONCE(1);

	वापस शून्य;

found:
	/*
	 * Indicates a problem in the ToPA allocation code.
	 */
	अगर (WARN_ON_ONCE(topa->last == -1))
		वापस शून्य;

	tp = topa_to_page(topa);
	cur_pg = PFN_DOWN(topa->offset);
	अगर (topa->z_count) अणु
		z_pg = TOPA_ENTRY_PAGES(topa, 0) * (topa->z_count + 1);
		start_idx = topa->z_count + 1;
	पूर्ण

	/*
	 * Multiple entries at the beginning of the table have the same size,
	 * ideally all of them; अगर @pg falls there, the search is करोne.
	 */
	अगर (pg >= cur_pg && pg < cur_pg + z_pg) अणु
		idx = (pg - cur_pg) / TOPA_ENTRY_PAGES(topa, 0);
		वापस &tp->table[idx];
	पूर्ण

	/*
	 * Otherwise, slow path: iterate through the reमुख्यing entries.
	 */
	क्रम (idx = start_idx, cur_pg += z_pg; idx < topa->last; idx++) अणु
		अगर (cur_pg + TOPA_ENTRY_PAGES(topa, idx) > pg)
			वापस &tp->table[idx];

		cur_pg += TOPA_ENTRY_PAGES(topa, idx);
	पूर्ण

	/*
	 * Means we couldn't find a ToPA entry in the table that करोes match.
	 */
	WARN_ON_ONCE(1);

	वापस शून्य;
पूर्ण

अटल काष्ठा topa_entry *
pt_topa_prev_entry(काष्ठा pt_buffer *buf, काष्ठा topa_entry *te)
अणु
	अचिन्हित दीर्घ table = (अचिन्हित दीर्घ)te & ~(PAGE_SIZE - 1);
	काष्ठा topa_page *tp;
	काष्ठा topa *topa;

	tp = (काष्ठा topa_page *)table;
	अगर (tp->table != te)
		वापस --te;

	topa = &tp->topa;
	अगर (topa == buf->first)
		topa = buf->last;
	अन्यथा
		topa = list_prev_entry(topa, list);

	tp = topa_to_page(topa);

	वापस &tp->table[topa->last - 1];
पूर्ण

/**
 * pt_buffer_reset_markers() - place पूर्णांकerrupt and stop bits in the buffer
 * @buf:	PT buffer.
 * @handle:	Current output handle.
 *
 * Place INT and STOP marks to prevent overwriting old data that the consumer
 * hasn't yet collected and waking up the consumer after a certain fraction of
 * the buffer has filled up. Only needed and sensible क्रम non-snapshot counters.
 *
 * This obviously relies on buf::head to figure out buffer markers, so it has
 * to be called after pt_buffer_reset_offsets() and beक्रमe the hardware tracing
 * is enabled.
 */
अटल पूर्णांक pt_buffer_reset_markers(काष्ठा pt_buffer *buf,
				   काष्ठा perf_output_handle *handle)

अणु
	अचिन्हित दीर्घ head = local64_पढ़ो(&buf->head);
	अचिन्हित दीर्घ idx, npages, wakeup;

	अगर (buf->single)
		वापस 0;

	/* can't stop in the middle of an output region */
	अगर (buf->output_off + handle->size + 1 < pt_buffer_region_size(buf)) अणु
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
		वापस -EINVAL;
	पूर्ण


	/* single entry ToPA is handled by marking all regions STOP=1 INT=1 */
	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		वापस 0;

	/* clear STOP and INT from current entry */
	अगर (buf->stop_te) अणु
		buf->stop_te->stop = 0;
		buf->stop_te->पूर्णांकr = 0;
	पूर्ण

	अगर (buf->पूर्णांकr_te)
		buf->पूर्णांकr_te->पूर्णांकr = 0;

	/* how many pages till the STOP marker */
	npages = handle->size >> PAGE_SHIFT;

	/* अगर it's on a page boundary, fill up one more page */
	अगर (!offset_in_page(head + handle->size + 1))
		npages++;

	idx = (head >> PAGE_SHIFT) + npages;
	idx &= buf->nr_pages - 1;

	अगर (idx != buf->stop_pos) अणु
		buf->stop_pos = idx;
		buf->stop_te = pt_topa_entry_क्रम_page(buf, idx);
		buf->stop_te = pt_topa_prev_entry(buf, buf->stop_te);
	पूर्ण

	wakeup = handle->wakeup >> PAGE_SHIFT;

	/* in the worst हाल, wake up the consumer one page beक्रमe hard stop */
	idx = (head >> PAGE_SHIFT) + npages - 1;
	अगर (idx > wakeup)
		idx = wakeup;

	idx &= buf->nr_pages - 1;
	अगर (idx != buf->पूर्णांकr_pos) अणु
		buf->पूर्णांकr_pos = idx;
		buf->पूर्णांकr_te = pt_topa_entry_क्रम_page(buf, idx);
		buf->पूर्णांकr_te = pt_topa_prev_entry(buf, buf->पूर्णांकr_te);
	पूर्ण

	buf->stop_te->stop = 1;
	buf->stop_te->पूर्णांकr = 1;
	buf->पूर्णांकr_te->पूर्णांकr = 1;

	वापस 0;
पूर्ण

/**
 * pt_buffer_reset_offsets() - adjust buffer's ग_लिखो poपूर्णांकers from aux_head
 * @buf:	PT buffer.
 * @head:	Write poपूर्णांकer (aux_head) from AUX buffer.
 *
 * Find the ToPA table and entry corresponding to given @head and set buffer's
 * "current" poपूर्णांकers accordingly. This is करोne after we have obtained the
 * current aux_head position from a successful call to perf_aux_output_begin()
 * to make sure the hardware is writing to the right place.
 *
 * This function modअगरies buf::अणुcur,cur_idx,output_offपूर्ण that will be programmed
 * पूर्णांकo PT msrs when the tracing is enabled and buf::head and buf::data_size,
 * which are used to determine INT and STOP markers' locations by a subsequent
 * call to pt_buffer_reset_markers().
 */
अटल व्योम pt_buffer_reset_offsets(काष्ठा pt_buffer *buf, अचिन्हित दीर्घ head)
अणु
	काष्ठा topa_page *cur_tp;
	काष्ठा topa_entry *te;
	पूर्णांक pg;

	अगर (buf->snapshot)
		head &= (buf->nr_pages << PAGE_SHIFT) - 1;

	अगर (!buf->single) अणु
		pg = (head >> PAGE_SHIFT) & (buf->nr_pages - 1);
		te = pt_topa_entry_क्रम_page(buf, pg);

		cur_tp = topa_entry_to_page(te);
		buf->cur = &cur_tp->topa;
		buf->cur_idx = te - TOPA_ENTRY(buf->cur, 0);
		buf->output_off = head & (pt_buffer_region_size(buf) - 1);
	पूर्ण अन्यथा अणु
		buf->output_off = head;
	पूर्ण

	local64_set(&buf->head, head);
	local_set(&buf->data_size, 0);
पूर्ण

/**
 * pt_buffer_fini_topa() - deallocate ToPA काष्ठाure of a buffer
 * @buf:	PT buffer.
 */
अटल व्योम pt_buffer_fini_topa(काष्ठा pt_buffer *buf)
अणु
	काष्ठा topa *topa, *iter;

	अगर (buf->single)
		वापस;

	list_क्रम_each_entry_safe(topa, iter, &buf->tables, list) अणु
		/*
		 * right now, this is in मुक्त_aux() path only, so
		 * no need to unlink this table from the list
		 */
		topa_मुक्त(topa);
	पूर्ण
पूर्ण

/**
 * pt_buffer_init_topa() - initialize ToPA table क्रम pt buffer
 * @buf:	PT buffer.
 * @size:	Total size of all regions within this ToPA.
 * @gfp:	Allocation flags.
 */
अटल पूर्णांक pt_buffer_init_topa(काष्ठा pt_buffer *buf, पूर्णांक cpu,
			       अचिन्हित दीर्घ nr_pages, gfp_t gfp)
अणु
	काष्ठा topa *topa;
	पूर्णांक err;

	topa = topa_alloc(cpu, gfp);
	अगर (!topa)
		वापस -ENOMEM;

	topa_insert_table(buf, topa);

	जबतक (buf->nr_pages < nr_pages) अणु
		err = topa_insert_pages(buf, cpu, gfp);
		अगर (err) अणु
			pt_buffer_fini_topa(buf);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* link last table to the first one, unless we're द्विगुन buffering */
	अगर (पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries)) अणु
		TOPA_ENTRY(buf->last, -1)->base = topa_pfn(buf->first);
		TOPA_ENTRY(buf->last, -1)->end = 1;
	पूर्ण

	pt_topa_dump(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक pt_buffer_try_single(काष्ठा pt_buffer *buf, पूर्णांक nr_pages)
अणु
	काष्ठा page *p = virt_to_page(buf->data_pages[0]);
	पूर्णांक ret = -ENOTSUPP, order = 0;

	/*
	 * We can use single range output mode
	 * + in snapshot mode, where we करोn't need पूर्णांकerrupts;
	 * + अगर the hardware supports it;
	 * + अगर the entire buffer is one contiguous allocation.
	 */
	अगर (!buf->snapshot)
		जाओ out;

	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_single_range_output))
		जाओ out;

	अगर (PagePrivate(p))
		order = page_निजी(p);

	अगर (1 << order != nr_pages)
		जाओ out;

	buf->single = true;
	buf->nr_pages = nr_pages;
	ret = 0;
out:
	वापस ret;
पूर्ण

/**
 * pt_buffer_setup_aux() - set up topa tables क्रम a PT buffer
 * @cpu:	Cpu on which to allocate, -1 means current.
 * @pages:	Array of poपूर्णांकers to buffer pages passed from perf core.
 * @nr_pages:	Number of pages in the buffer.
 * @snapshot:	If this is a snapshot/overग_लिखो counter.
 *
 * This is a pmu::setup_aux callback that sets up ToPA tables and all the
 * bookkeeping क्रम an AUX buffer.
 *
 * Return:	Our निजी PT buffer काष्ठाure.
 */
अटल व्योम *
pt_buffer_setup_aux(काष्ठा perf_event *event, व्योम **pages,
		    पूर्णांक nr_pages, bool snapshot)
अणु
	काष्ठा pt_buffer *buf;
	पूर्णांक node, ret, cpu = event->cpu;

	अगर (!nr_pages)
		वापस शून्य;

	/*
	 * Only support AUX sampling in snapshot mode, where we करोn't
	 * generate NMIs.
	 */
	अगर (event->attr.aux_sample_size && !snapshot)
		वापस शून्य;

	अगर (cpu == -1)
		cpu = raw_smp_processor_id();
	node = cpu_to_node(cpu);

	buf = kzalloc_node(माप(काष्ठा pt_buffer), GFP_KERNEL, node);
	अगर (!buf)
		वापस शून्य;

	buf->snapshot = snapshot;
	buf->data_pages = pages;
	buf->stop_pos = -1;
	buf->पूर्णांकr_pos = -1;

	INIT_LIST_HEAD(&buf->tables);

	ret = pt_buffer_try_single(buf, nr_pages);
	अगर (!ret)
		वापस buf;

	ret = pt_buffer_init_topa(buf, cpu, nr_pages, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण

	वापस buf;
पूर्ण

/**
 * pt_buffer_मुक्त_aux() - perf AUX deallocation path callback
 * @data:	PT buffer.
 */
अटल व्योम pt_buffer_मुक्त_aux(व्योम *data)
अणु
	काष्ठा pt_buffer *buf = data;

	pt_buffer_fini_topa(buf);
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक pt_addr_filters_init(काष्ठा perf_event *event)
अणु
	काष्ठा pt_filters *filters;
	पूर्णांक node = event->cpu == -1 ? -1 : cpu_to_node(event->cpu);

	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_num_address_ranges))
		वापस 0;

	filters = kzalloc_node(माप(काष्ठा pt_filters), GFP_KERNEL, node);
	अगर (!filters)
		वापस -ENOMEM;

	अगर (event->parent)
		स_नकल(filters, event->parent->hw.addr_filters,
		       माप(*filters));

	event->hw.addr_filters = filters;

	वापस 0;
पूर्ण

अटल व्योम pt_addr_filters_fini(काष्ठा perf_event *event)
अणु
	kमुक्त(event->hw.addr_filters);
	event->hw.addr_filters = शून्य;
पूर्ण

अटल अंतरभूत bool valid_kernel_ip(अचिन्हित दीर्घ ip)
अणु
	वापस virt_addr_valid(ip) && kernel_ip(ip);
पूर्ण

अटल पूर्णांक pt_event_addr_filters_validate(काष्ठा list_head *filters)
अणु
	काष्ठा perf_addr_filter *filter;
	पूर्णांक range = 0;

	list_क्रम_each_entry(filter, filters, entry) अणु
		/*
		 * PT करोesn't support single address triggers and
		 * 'start' filters.
		 */
		अगर (!filter->size ||
		    filter->action == PERF_ADDR_FILTER_ACTION_START)
			वापस -EOPNOTSUPP;

		अगर (!filter->path.dentry) अणु
			अगर (!valid_kernel_ip(filter->offset))
				वापस -EINVAL;

			अगर (!valid_kernel_ip(filter->offset + filter->size))
				वापस -EINVAL;
		पूर्ण

		अगर (++range > पूर्णांकel_pt_validate_hw_cap(PT_CAP_num_address_ranges))
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pt_event_addr_filters_sync(काष्ठा perf_event *event)
अणु
	काष्ठा perf_addr_filters_head *head = perf_event_addr_filters(event);
	अचिन्हित दीर्घ msr_a, msr_b;
	काष्ठा perf_addr_filter_range *fr = event->addr_filter_ranges;
	काष्ठा pt_filters *filters = event->hw.addr_filters;
	काष्ठा perf_addr_filter *filter;
	पूर्णांक range = 0;

	अगर (!filters)
		वापस;

	list_क्रम_each_entry(filter, &head->list, entry) अणु
		अगर (filter->path.dentry && !fr[range].start) अणु
			msr_a = msr_b = 0;
		पूर्ण अन्यथा अणु
			/* apply the offset */
			msr_a = fr[range].start;
			msr_b = msr_a + fr[range].size - 1;
		पूर्ण

		filters->filter[range].msr_a  = msr_a;
		filters->filter[range].msr_b  = msr_b;
		अगर (filter->action == PERF_ADDR_FILTER_ACTION_FILTER)
			filters->filter[range].config = 1;
		अन्यथा
			filters->filter[range].config = 2;
		range++;
	पूर्ण

	filters->nr_filters = range;
पूर्ण

/**
 * पूर्णांकel_pt_पूर्णांकerrupt() - PT PMI handler
 */
व्योम पूर्णांकel_pt_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा pt_buffer *buf;
	काष्ठा perf_event *event = pt->handle.event;

	/*
	 * There may be a dangling PT bit in the पूर्णांकerrupt status रेजिस्टर
	 * after PT has been disabled by pt_event_stop(). Make sure we करोn't
	 * करो anything (particularly, re-enable) क्रम this event here.
	 */
	अगर (!READ_ONCE(pt->handle_nmi))
		वापस;

	अगर (!event)
		वापस;

	pt_config_stop(event);

	buf = perf_get_aux(&pt->handle);
	अगर (!buf)
		वापस;

	pt_पढ़ो_offset(buf);

	pt_handle_status(pt);

	pt_update_head(pt);

	perf_aux_output_end(&pt->handle, local_xchg(&buf->data_size, 0));

	अगर (!event->hw.state) अणु
		पूर्णांक ret;

		buf = perf_aux_output_begin(&pt->handle, event);
		अगर (!buf) अणु
			event->hw.state = PERF_HES_STOPPED;
			वापस;
		पूर्ण

		pt_buffer_reset_offsets(buf, pt->handle.head);
		/* snapshot counters करोn't use PMI, so it's safe */
		ret = pt_buffer_reset_markers(buf, &pt->handle);
		अगर (ret) अणु
			perf_aux_output_end(&pt->handle, 0);
			वापस;
		पूर्ण

		pt_config_buffer(buf);
		pt_config_start(event);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pt_handle_vmx(पूर्णांक on)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ flags;

	/* PT plays nice with VMX, करो nothing */
	अगर (pt_pmu.vmx)
		वापस;

	/*
	 * VMXON will clear RTIT_CTL.TraceEn; we need to make
	 * sure to not try to set it जबतक VMX is on. Disable
	 * पूर्णांकerrupts to aव्योम racing with pmu callbacks;
	 * concurrent PMI should be handled fine.
	 */
	local_irq_save(flags);
	WRITE_ONCE(pt->vmx_on, on);

	/*
	 * If an AUX transaction is in progress, it will contain
	 * gap(s), so flag it PARTIAL to inक्रमm the user.
	 */
	event = pt->handle.event;
	अगर (event)
		perf_aux_output_flag(&pt->handle,
		                     PERF_AUX_FLAG_PARTIAL);

	/* Turn PTs back on */
	अगर (!on && event)
		wrmsrl(MSR_IA32_RTIT_CTL, event->hw.config);

	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pt_handle_vmx);

/*
 * PMU callbacks
 */

अटल व्योम pt_event_start(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा pt_buffer *buf;

	buf = perf_aux_output_begin(&pt->handle, event);
	अगर (!buf)
		जाओ fail_stop;

	pt_buffer_reset_offsets(buf, pt->handle.head);
	अगर (!buf->snapshot) अणु
		अगर (pt_buffer_reset_markers(buf, &pt->handle))
			जाओ fail_end_stop;
	पूर्ण

	WRITE_ONCE(pt->handle_nmi, 1);
	hwc->state = 0;

	pt_config_buffer(buf);
	pt_config(event);

	वापस;

fail_end_stop:
	perf_aux_output_end(&pt->handle, 0);
fail_stop:
	hwc->state = PERF_HES_STOPPED;
पूर्ण

अटल व्योम pt_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);

	/*
	 * Protect against the PMI racing with disabling wrmsr,
	 * see comment in पूर्णांकel_pt_पूर्णांकerrupt().
	 */
	WRITE_ONCE(pt->handle_nmi, 0);

	pt_config_stop(event);

	अगर (event->hw.state == PERF_HES_STOPPED)
		वापस;

	event->hw.state = PERF_HES_STOPPED;

	अगर (mode & PERF_EF_UPDATE) अणु
		काष्ठा pt_buffer *buf = perf_get_aux(&pt->handle);

		अगर (!buf)
			वापस;

		अगर (WARN_ON_ONCE(pt->handle.event != event))
			वापस;

		pt_पढ़ो_offset(buf);

		pt_handle_status(pt);

		pt_update_head(pt);

		अगर (buf->snapshot)
			pt->handle.head =
				local_xchg(&buf->data_size,
					   buf->nr_pages << PAGE_SHIFT);
		perf_aux_output_end(&pt->handle, local_xchg(&buf->data_size, 0));
	पूर्ण
पूर्ण

अटल दीर्घ pt_event_snapshot_aux(काष्ठा perf_event *event,
				  काष्ठा perf_output_handle *handle,
				  अचिन्हित दीर्घ size)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा pt_buffer *buf = perf_get_aux(&pt->handle);
	अचिन्हित दीर्घ from = 0, to;
	दीर्घ ret;

	अगर (WARN_ON_ONCE(!buf))
		वापस 0;

	/*
	 * Sampling is only allowed on snapshot events;
	 * see pt_buffer_setup_aux().
	 */
	अगर (WARN_ON_ONCE(!buf->snapshot))
		वापस 0;

	/*
	 * Here, handle_nmi tells us अगर the tracing is on
	 */
	अगर (READ_ONCE(pt->handle_nmi))
		pt_config_stop(event);

	pt_पढ़ो_offset(buf);
	pt_update_head(pt);

	to = local_पढ़ो(&buf->data_size);
	अगर (to < size)
		from = buf->nr_pages << PAGE_SHIFT;
	from += to - size;

	ret = perf_output_copy_aux(&pt->handle, handle, from, to);

	/*
	 * If the tracing was on when we turned up, restart it.
	 * Compiler barrier not needed as we couldn't have been
	 * preempted by anything that touches pt->handle_nmi.
	 */
	अगर (pt->handle_nmi)
		pt_config_start(event);

	वापस ret;
पूर्ण

अटल व्योम pt_event_del(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	pt_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक pt_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक ret = -EBUSY;

	अगर (pt->handle.event)
		जाओ fail;

	अगर (mode & PERF_EF_START) अणु
		pt_event_start(event, 0);
		ret = -EINVAL;
		अगर (hwc->state == PERF_HES_STOPPED)
			जाओ fail;
	पूर्ण अन्यथा अणु
		hwc->state = PERF_HES_STOPPED;
	पूर्ण

	ret = 0;
fail:

	वापस ret;
पूर्ण

अटल व्योम pt_event_पढ़ो(काष्ठा perf_event *event)
अणु
पूर्ण

अटल व्योम pt_event_destroy(काष्ठा perf_event *event)
अणु
	pt_addr_filters_fini(event);
	x86_del_exclusive(x86_lbr_exclusive_pt);
पूर्ण

अटल पूर्णांक pt_event_init(काष्ठा perf_event *event)
अणु
	अगर (event->attr.type != pt_pmu.pmu.type)
		वापस -ENOENT;

	अगर (!pt_event_valid(event))
		वापस -EINVAL;

	अगर (x86_add_exclusive(x86_lbr_exclusive_pt))
		वापस -EBUSY;

	अगर (pt_addr_filters_init(event)) अणु
		x86_del_exclusive(x86_lbr_exclusive_pt);
		वापस -ENOMEM;
	पूर्ण

	event->destroy = pt_event_destroy;

	वापस 0;
पूर्ण

व्योम cpu_emergency_stop_pt(व्योम)
अणु
	काष्ठा pt *pt = this_cpu_ptr(&pt_ctx);

	अगर (pt->handle.event)
		pt_event_stop(pt->handle.event, PERF_EF_UPDATE);
पूर्ण

पूर्णांक is_पूर्णांकel_pt_event(काष्ठा perf_event *event)
अणु
	वापस event->pmu == &pt_pmu.pmu;
पूर्ण

अटल __init पूर्णांक pt_init(व्योम)
अणु
	पूर्णांक ret, cpu, prior_warn = 0;

	BUILD_BUG_ON(माप(काष्ठा topa) > PAGE_SIZE);

	अगर (!boot_cpu_has(X86_FEATURE_INTEL_PT))
		वापस -ENODEV;

	get_online_cpus();
	क्रम_each_online_cpu(cpu) अणु
		u64 ctl;

		ret = rdmsrl_safe_on_cpu(cpu, MSR_IA32_RTIT_CTL, &ctl);
		अगर (!ret && (ctl & RTIT_CTL_TRACEEN))
			prior_warn++;
	पूर्ण
	put_online_cpus();

	अगर (prior_warn) अणु
		x86_add_exclusive(x86_lbr_exclusive_pt);
		pr_warn("PT is enabled at boot time, doing nothing\n");

		वापस -EBUSY;
	पूर्ण

	ret = pt_pmu_hw_init();
	अगर (ret)
		वापस ret;

	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_output)) अणु
		pr_warn("ToPA output is not supported on this CPU\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries))
		pt_pmu.pmu.capabilities = PERF_PMU_CAP_AUX_NO_SG;

	pt_pmu.pmu.capabilities	|= PERF_PMU_CAP_EXCLUSIVE | PERF_PMU_CAP_ITRACE;
	pt_pmu.pmu.attr_groups		 = pt_attr_groups;
	pt_pmu.pmu.task_ctx_nr		 = perf_sw_context;
	pt_pmu.pmu.event_init		 = pt_event_init;
	pt_pmu.pmu.add			 = pt_event_add;
	pt_pmu.pmu.del			 = pt_event_del;
	pt_pmu.pmu.start		 = pt_event_start;
	pt_pmu.pmu.stop			 = pt_event_stop;
	pt_pmu.pmu.snapshot_aux		 = pt_event_snapshot_aux;
	pt_pmu.pmu.पढ़ो			 = pt_event_पढ़ो;
	pt_pmu.pmu.setup_aux		 = pt_buffer_setup_aux;
	pt_pmu.pmu.मुक्त_aux		 = pt_buffer_मुक्त_aux;
	pt_pmu.pmu.addr_filters_sync     = pt_event_addr_filters_sync;
	pt_pmu.pmu.addr_filters_validate = pt_event_addr_filters_validate;
	pt_pmu.pmu.nr_addr_filters       =
		पूर्णांकel_pt_validate_hw_cap(PT_CAP_num_address_ranges);

	ret = perf_pmu_रेजिस्टर(&pt_pmu.pmu, "intel_pt", -1);

	वापस ret;
पूर्ण
arch_initcall(pt_init);
