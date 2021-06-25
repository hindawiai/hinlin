<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Resource Director Technology(RDT)
 * - Cache Allocation code.
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Authors:
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *    Tony Luck <tony.luck@पूर्णांकel.com>
 *    Vikas Shivappa <vikas.shivappa@पूर्णांकel.com>
 *
 * More inक्रमmation about RDT be found in the Intel (R) x86 Architecture
 * Software Developer Manual June 2016, volume 3, section 17.17.
 */

#घोषणा pr_fmt(fmt)	"resctrl: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpuhotplug.h>

#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/resctrl.h>
#समावेश "internal.h"

/* Mutex to protect rdtgroup access. */
DEFINE_MUTEX(rdtgroup_mutex);

/*
 * The cached resctrl_pqr_state is strictly per CPU and can never be
 * updated from a remote CPU. Functions which modअगरy the state
 * are called with पूर्णांकerrupts disabled and no preemption, which
 * is sufficient क्रम the protection.
 */
DEFINE_PER_CPU(काष्ठा resctrl_pqr_state, pqr_state);

/*
 * Used to store the max resource name width and max resource data width
 * to display the schemata in a tabular क्रमmat
 */
पूर्णांक max_name_width, max_data_width;

/*
 * Global boolean क्रम rdt_alloc which is true अगर any
 * resource allocation is enabled.
 */
bool rdt_alloc_capable;

अटल व्योम
mba_wrmsr_पूर्णांकel(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m,
		काष्ठा rdt_resource *r);
अटल व्योम
cat_wrmsr(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m, काष्ठा rdt_resource *r);
अटल व्योम
mba_wrmsr_amd(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m,
	      काष्ठा rdt_resource *r);

#घोषणा करोमुख्य_init(id) LIST_HEAD_INIT(rdt_resources_all[id].करोमुख्यs)

काष्ठा rdt_resource rdt_resources_all[] = अणु
	[RDT_RESOURCE_L3] =
	अणु
		.rid			= RDT_RESOURCE_L3,
		.name			= "L3",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L3),
		.msr_base		= MSR_IA32_L3_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 3,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 1,
			.cbm_idx_offset	= 0,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_L3DATA] =
	अणु
		.rid			= RDT_RESOURCE_L3DATA,
		.name			= "L3DATA",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L3DATA),
		.msr_base		= MSR_IA32_L3_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 3,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 2,
			.cbm_idx_offset	= 0,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_L3CODE] =
	अणु
		.rid			= RDT_RESOURCE_L3CODE,
		.name			= "L3CODE",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L3CODE),
		.msr_base		= MSR_IA32_L3_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 3,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 2,
			.cbm_idx_offset	= 1,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_L2] =
	अणु
		.rid			= RDT_RESOURCE_L2,
		.name			= "L2",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L2),
		.msr_base		= MSR_IA32_L2_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 2,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 1,
			.cbm_idx_offset	= 0,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_L2DATA] =
	अणु
		.rid			= RDT_RESOURCE_L2DATA,
		.name			= "L2DATA",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L2DATA),
		.msr_base		= MSR_IA32_L2_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 2,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 2,
			.cbm_idx_offset	= 0,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_L2CODE] =
	अणु
		.rid			= RDT_RESOURCE_L2CODE,
		.name			= "L2CODE",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_L2CODE),
		.msr_base		= MSR_IA32_L2_CBM_BASE,
		.msr_update		= cat_wrmsr,
		.cache_level		= 2,
		.cache = अणु
			.min_cbm_bits	= 1,
			.cbm_idx_mult	= 2,
			.cbm_idx_offset	= 1,
		पूर्ण,
		.parse_ctrlval		= parse_cbm,
		.क्रमmat_str		= "%d=%0*x",
		.fflags			= RFTYPE_RES_CACHE,
	पूर्ण,
	[RDT_RESOURCE_MBA] =
	अणु
		.rid			= RDT_RESOURCE_MBA,
		.name			= "MB",
		.करोमुख्यs		= करोमुख्य_init(RDT_RESOURCE_MBA),
		.cache_level		= 3,
		.parse_ctrlval		= parse_bw,
		.क्रमmat_str		= "%d=%*u",
		.fflags			= RFTYPE_RES_MB,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक cbm_idx(काष्ठा rdt_resource *r, अचिन्हित पूर्णांक closid)
अणु
	वापस closid * r->cache.cbm_idx_mult + r->cache.cbm_idx_offset;
पूर्ण

/*
 * cache_alloc_hsw_probe() - Have to probe क्रम Intel haswell server CPUs
 * as they करो not have CPUID क्रमागतeration support क्रम Cache allocation.
 * The check क्रम Venकरोr/Family/Model is not enough to guarantee that
 * the MSRs won't #GP fault because only the following SKUs support
 * CAT:
 *	Intel(R) Xeon(R)  CPU E5-2658  v3  @  2.20GHz
 *	Intel(R) Xeon(R)  CPU E5-2648L v3  @  1.80GHz
 *	Intel(R) Xeon(R)  CPU E5-2628L v3  @  2.00GHz
 *	Intel(R) Xeon(R)  CPU E5-2618L v3  @  2.30GHz
 *	Intel(R) Xeon(R)  CPU E5-2608L v3  @  2.00GHz
 *	Intel(R) Xeon(R)  CPU E5-2658A v3  @  2.20GHz
 *
 * Probe by trying to ग_लिखो the first of the L3 cache mask रेजिस्टरs
 * and checking that the bits stick. Max CLOSids is always 4 and max cbm length
 * is always 20 on hsw server parts. The minimum cache biपंचांगask length
 * allowed क्रम HSW server is always 2 bits. Hardcode all of them.
 */
अटल अंतरभूत व्योम cache_alloc_hsw_probe(व्योम)
अणु
	काष्ठा rdt_resource *r  = &rdt_resources_all[RDT_RESOURCE_L3];
	u32 l, h, max_cbm = BIT_MASK(20) - 1;

	अगर (wrmsr_safe(MSR_IA32_L3_CBM_BASE, max_cbm, 0))
		वापस;

	rdmsr(MSR_IA32_L3_CBM_BASE, l, h);

	/* If all the bits were set in MSR, वापस success */
	अगर (l != max_cbm)
		वापस;

	r->num_closid = 4;
	r->शेष_ctrl = max_cbm;
	r->cache.cbm_len = 20;
	r->cache.shareable_bits = 0xc0000;
	r->cache.min_cbm_bits = 2;
	r->alloc_capable = true;
	r->alloc_enabled = true;

	rdt_alloc_capable = true;
पूर्ण

bool is_mba_sc(काष्ठा rdt_resource *r)
अणु
	अगर (!r)
		वापस rdt_resources_all[RDT_RESOURCE_MBA].membw.mba_sc;

	वापस r->membw.mba_sc;
पूर्ण

/*
 * rdt_get_mb_table() - get a mapping of bandwidth(b/w) percentage values
 * exposed to user पूर्णांकerface and the h/w understandable delay values.
 *
 * The non-linear delay values have the granularity of घातer of two
 * and also the h/w करोes not guarantee a curve क्रम configured delay
 * values vs. actual b/w enक्रमced.
 * Hence we need a mapping that is pre calibrated so the user can
 * express the memory b/w as a percentage value.
 */
अटल अंतरभूत bool rdt_get_mb_table(काष्ठा rdt_resource *r)
अणु
	/*
	 * There are no Intel SKUs as of now to support non-linear delay.
	 */
	pr_info("MBA b/w map not implemented for cpu:%d, model:%d",
		boot_cpu_data.x86, boot_cpu_data.x86_model);

	वापस false;
पूर्ण

अटल bool __get_mem_config_पूर्णांकel(काष्ठा rdt_resource *r)
अणु
	जोड़ cpuid_0x10_3_eax eax;
	जोड़ cpuid_0x10_x_edx edx;
	u32 ebx, ecx, max_delay;

	cpuid_count(0x00000010, 3, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	max_delay = eax.split.max_delay + 1;
	r->शेष_ctrl = MAX_MBA_BW;
	r->membw.arch_needs_linear = true;
	अगर (ecx & MBA_IS_LINEAR) अणु
		r->membw.delay_linear = true;
		r->membw.min_bw = MAX_MBA_BW - max_delay;
		r->membw.bw_gran = MAX_MBA_BW - max_delay;
	पूर्ण अन्यथा अणु
		अगर (!rdt_get_mb_table(r))
			वापस false;
		r->membw.arch_needs_linear = false;
	पूर्ण
	r->data_width = 3;

	अगर (boot_cpu_has(X86_FEATURE_PER_THREAD_MBA))
		r->membw.throttle_mode = THREAD_THROTTLE_PER_THREAD;
	अन्यथा
		r->membw.throttle_mode = THREAD_THROTTLE_MAX;
	thपढ़ो_throttle_mode_init();

	r->alloc_capable = true;
	r->alloc_enabled = true;

	वापस true;
पूर्ण

अटल bool __rdt_get_mem_config_amd(काष्ठा rdt_resource *r)
अणु
	जोड़ cpuid_0x10_3_eax eax;
	जोड़ cpuid_0x10_x_edx edx;
	u32 ebx, ecx;

	cpuid_count(0x80000020, 1, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	r->शेष_ctrl = MAX_MBA_BW_AMD;

	/* AMD करोes not use delay */
	r->membw.delay_linear = false;
	r->membw.arch_needs_linear = false;

	/*
	 * AMD करोes not use memory delay throttle model to control
	 * the allocation like Intel करोes.
	 */
	r->membw.throttle_mode = THREAD_THROTTLE_UNDEFINED;
	r->membw.min_bw = 0;
	r->membw.bw_gran = 1;
	/* Max value is 2048, Data width should be 4 in decimal */
	r->data_width = 4;

	r->alloc_capable = true;
	r->alloc_enabled = true;

	वापस true;
पूर्ण

अटल व्योम rdt_get_cache_alloc_cfg(पूर्णांक idx, काष्ठा rdt_resource *r)
अणु
	जोड़ cpuid_0x10_1_eax eax;
	जोड़ cpuid_0x10_x_edx edx;
	u32 ebx, ecx;

	cpuid_count(0x00000010, idx, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	r->cache.cbm_len = eax.split.cbm_len + 1;
	r->शेष_ctrl = BIT_MASK(eax.split.cbm_len + 1) - 1;
	r->cache.shareable_bits = ebx & r->शेष_ctrl;
	r->data_width = (r->cache.cbm_len + 3) / 4;
	r->alloc_capable = true;
	r->alloc_enabled = true;
पूर्ण

अटल व्योम rdt_get_cdp_config(पूर्णांक level, पूर्णांक type)
अणु
	काष्ठा rdt_resource *r_l = &rdt_resources_all[level];
	काष्ठा rdt_resource *r = &rdt_resources_all[type];

	r->num_closid = r_l->num_closid / 2;
	r->cache.cbm_len = r_l->cache.cbm_len;
	r->शेष_ctrl = r_l->शेष_ctrl;
	r->cache.shareable_bits = r_l->cache.shareable_bits;
	r->data_width = (r->cache.cbm_len + 3) / 4;
	r->alloc_capable = true;
	/*
	 * By शेष, CDP is disabled. CDP can be enabled by mount parameter
	 * "cdp" during resctrl file प्रणाली mount समय.
	 */
	r->alloc_enabled = false;
पूर्ण

अटल व्योम rdt_get_cdp_l3_config(व्योम)
अणु
	rdt_get_cdp_config(RDT_RESOURCE_L3, RDT_RESOURCE_L3DATA);
	rdt_get_cdp_config(RDT_RESOURCE_L3, RDT_RESOURCE_L3CODE);
पूर्ण

अटल व्योम rdt_get_cdp_l2_config(व्योम)
अणु
	rdt_get_cdp_config(RDT_RESOURCE_L2, RDT_RESOURCE_L2DATA);
	rdt_get_cdp_config(RDT_RESOURCE_L2, RDT_RESOURCE_L2CODE);
पूर्ण

अटल व्योम
mba_wrmsr_amd(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m, काष्ठा rdt_resource *r)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = m->low; i < m->high; i++)
		wrmsrl(r->msr_base + i, d->ctrl_val[i]);
पूर्ण

/*
 * Map the memory b/w percentage value to delay values
 * that can be written to QOS_MSRs.
 * There are currently no SKUs which support non linear delay values.
 */
u32 delay_bw_map(अचिन्हित दीर्घ bw, काष्ठा rdt_resource *r)
अणु
	अगर (r->membw.delay_linear)
		वापस MAX_MBA_BW - bw;

	pr_warn_once("Non Linear delay-bw map not supported but queried\n");
	वापस r->शेष_ctrl;
पूर्ण

अटल व्योम
mba_wrmsr_पूर्णांकel(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m,
		काष्ठा rdt_resource *r)
अणु
	अचिन्हित पूर्णांक i;

	/*  Write the delay values क्रम mba. */
	क्रम (i = m->low; i < m->high; i++)
		wrmsrl(r->msr_base + i, delay_bw_map(d->ctrl_val[i], r));
पूर्ण

अटल व्योम
cat_wrmsr(काष्ठा rdt_करोमुख्य *d, काष्ठा msr_param *m, काष्ठा rdt_resource *r)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = m->low; i < m->high; i++)
		wrmsrl(r->msr_base + cbm_idx(r, i), d->ctrl_val[i]);
पूर्ण

काष्ठा rdt_करोमुख्य *get_करोमुख्य_from_cpu(पूर्णांक cpu, काष्ठा rdt_resource *r)
अणु
	काष्ठा rdt_करोमुख्य *d;

	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		/* Find the करोमुख्य that contains this CPU */
		अगर (cpumask_test_cpu(cpu, &d->cpu_mask))
			वापस d;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम rdt_ctrl_update(व्योम *arg)
अणु
	काष्ठा msr_param *m = arg;
	काष्ठा rdt_resource *r = m->res;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा rdt_करोमुख्य *d;

	d = get_करोमुख्य_from_cpu(cpu, r);
	अगर (d) अणु
		r->msr_update(d, m, r);
		वापस;
	पूर्ण
	pr_warn_once("cpu %d not found in any domain for resource %s\n",
		     cpu, r->name);
पूर्ण

/*
 * rdt_find_करोमुख्य - Find a करोमुख्य in a resource that matches input resource id
 *
 * Search resource r's करोमुख्य list to find the resource id. If the resource
 * id is found in a करोमुख्य, वापस the करोमुख्य. Otherwise, अगर requested by
 * caller, वापस the first करोमुख्य whose id is bigger than the input id.
 * The करोमुख्य list is sorted by id in ascending order.
 */
काष्ठा rdt_करोमुख्य *rdt_find_करोमुख्य(काष्ठा rdt_resource *r, पूर्णांक id,
				   काष्ठा list_head **pos)
अणु
	काष्ठा rdt_करोमुख्य *d;
	काष्ठा list_head *l;

	अगर (id < 0)
		वापस ERR_PTR(-ENODEV);

	list_क्रम_each(l, &r->करोमुख्यs) अणु
		d = list_entry(l, काष्ठा rdt_करोमुख्य, list);
		/* When id is found, वापस its करोमुख्य. */
		अगर (id == d->id)
			वापस d;
		/* Stop searching when finding id's position in sorted list. */
		अगर (id < d->id)
			अवरोध;
	पूर्ण

	अगर (pos)
		*pos = l;

	वापस शून्य;
पूर्ण

व्योम setup_शेष_ctrlval(काष्ठा rdt_resource *r, u32 *dc, u32 *dm)
अणु
	पूर्णांक i;

	/*
	 * Initialize the Control MSRs to having no control.
	 * For Cache Allocation: Set all bits in cbm
	 * For Memory Allocation: Set b/w requested to 100%
	 * and the bandwidth in MBps to U32_MAX
	 */
	क्रम (i = 0; i < r->num_closid; i++, dc++, dm++) अणु
		*dc = r->शेष_ctrl;
		*dm = MBA_MAX_MBPS;
	पूर्ण
पूर्ण

अटल पूर्णांक करोमुख्य_setup_ctrlval(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d)
अणु
	काष्ठा msr_param m;
	u32 *dc, *dm;

	dc = kदो_स्मृति_array(r->num_closid, माप(*d->ctrl_val), GFP_KERNEL);
	अगर (!dc)
		वापस -ENOMEM;

	dm = kदो_स्मृति_array(r->num_closid, माप(*d->mbps_val), GFP_KERNEL);
	अगर (!dm) अणु
		kमुक्त(dc);
		वापस -ENOMEM;
	पूर्ण

	d->ctrl_val = dc;
	d->mbps_val = dm;
	setup_शेष_ctrlval(r, dc, dm);

	m.low = 0;
	m.high = r->num_closid;
	r->msr_update(d, &m, r);
	वापस 0;
पूर्ण

अटल पूर्णांक करोमुख्य_setup_mon_state(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d)
अणु
	माप_प्रकार tsize;

	अगर (is_llc_occupancy_enabled()) अणु
		d->rmid_busy_llc = biपंचांगap_zalloc(r->num_rmid, GFP_KERNEL);
		अगर (!d->rmid_busy_llc)
			वापस -ENOMEM;
		INIT_DELAYED_WORK(&d->cqm_limbo, cqm_handle_limbo);
	पूर्ण
	अगर (is_mbm_total_enabled()) अणु
		tsize = माप(*d->mbm_total);
		d->mbm_total = kसुस्मृति(r->num_rmid, tsize, GFP_KERNEL);
		अगर (!d->mbm_total) अणु
			biपंचांगap_मुक्त(d->rmid_busy_llc);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (is_mbm_local_enabled()) अणु
		tsize = माप(*d->mbm_local);
		d->mbm_local = kसुस्मृति(r->num_rmid, tsize, GFP_KERNEL);
		अगर (!d->mbm_local) अणु
			biपंचांगap_मुक्त(d->rmid_busy_llc);
			kमुक्त(d->mbm_total);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (is_mbm_enabled()) अणु
		INIT_DELAYED_WORK(&d->mbm_over, mbm_handle_overflow);
		mbm_setup_overflow_handler(d, MBM_OVERFLOW_INTERVAL);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * करोमुख्य_add_cpu - Add a cpu to a resource's करोमुख्य list.
 *
 * If an existing करोमुख्य in the resource r's domain list matches the cpu's
 * resource id, add the cpu in the करोमुख्य.
 *
 * Otherwise, a new करोमुख्य is allocated and inserted पूर्णांकo the right position
 * in the करोमुख्य list sorted by id in ascending order.
 *
 * The order in the करोमुख्य list is visible to users when we prपूर्णांक entries
 * in the schemata file and schemata input is validated to have the same order
 * as this list.
 */
अटल व्योम करोमुख्य_add_cpu(पूर्णांक cpu, काष्ठा rdt_resource *r)
अणु
	पूर्णांक id = get_cpu_cacheinfo_id(cpu, r->cache_level);
	काष्ठा list_head *add_pos = शून्य;
	काष्ठा rdt_करोमुख्य *d;

	d = rdt_find_करोमुख्य(r, id, &add_pos);
	अगर (IS_ERR(d)) अणु
		pr_warn("Couldn't find cache id for CPU %d\n", cpu);
		वापस;
	पूर्ण

	अगर (d) अणु
		cpumask_set_cpu(cpu, &d->cpu_mask);
		अगर (r->cache.arch_has_per_cpu_cfg)
			rdt_करोमुख्य_reconfigure_cdp(r);
		वापस;
	पूर्ण

	d = kzalloc_node(माप(*d), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!d)
		वापस;

	d->id = id;
	cpumask_set_cpu(cpu, &d->cpu_mask);

	rdt_करोमुख्य_reconfigure_cdp(r);

	अगर (r->alloc_capable && करोमुख्य_setup_ctrlval(r, d)) अणु
		kमुक्त(d);
		वापस;
	पूर्ण

	अगर (r->mon_capable && करोमुख्य_setup_mon_state(r, d)) अणु
		kमुक्त(d);
		वापस;
	पूर्ण

	list_add_tail(&d->list, add_pos);

	/*
	 * If resctrl is mounted, add
	 * per करोमुख्य monitor data directories.
	 */
	अगर (अटल_branch_unlikely(&rdt_mon_enable_key))
		सूची_गढ़ो_mondata_subdir_allrdtgrp(r, d);
पूर्ण

अटल व्योम करोमुख्य_हटाओ_cpu(पूर्णांक cpu, काष्ठा rdt_resource *r)
अणु
	पूर्णांक id = get_cpu_cacheinfo_id(cpu, r->cache_level);
	काष्ठा rdt_करोमुख्य *d;

	d = rdt_find_करोमुख्य(r, id, शून्य);
	अगर (IS_ERR_OR_शून्य(d)) अणु
		pr_warn("Couldn't find cache id for CPU %d\n", cpu);
		वापस;
	पूर्ण

	cpumask_clear_cpu(cpu, &d->cpu_mask);
	अगर (cpumask_empty(&d->cpu_mask)) अणु
		/*
		 * If resctrl is mounted, हटाओ all the
		 * per करोमुख्य monitor data directories.
		 */
		अगर (अटल_branch_unlikely(&rdt_mon_enable_key))
			सूची_हटाओ_mondata_subdir_allrdtgrp(r, d->id);
		list_del(&d->list);
		अगर (r->mon_capable && is_mbm_enabled())
			cancel_delayed_work(&d->mbm_over);
		अगर (is_llc_occupancy_enabled() &&  has_busy_rmid(r, d)) अणु
			/*
			 * When a package is going करोwn, क्रमcefully
			 * decrement rmid->ebusy. There is no way to know
			 * that the L3 was flushed and hence may lead to
			 * incorrect counts in rare scenarios, but leaving
			 * the RMID as busy creates RMID leaks अगर the
			 * package never comes back.
			 */
			__check_limbo(d, true);
			cancel_delayed_work(&d->cqm_limbo);
		पूर्ण

		/*
		 * rdt_करोमुख्य "d" is going to be मुक्तd below, so clear
		 * its poपूर्णांकer from pseuकरो_lock_region काष्ठा.
		 */
		अगर (d->plr)
			d->plr->d = शून्य;

		kमुक्त(d->ctrl_val);
		kमुक्त(d->mbps_val);
		biपंचांगap_मुक्त(d->rmid_busy_llc);
		kमुक्त(d->mbm_total);
		kमुक्त(d->mbm_local);
		kमुक्त(d);
		वापस;
	पूर्ण

	अगर (r == &rdt_resources_all[RDT_RESOURCE_L3]) अणु
		अगर (is_mbm_enabled() && cpu == d->mbm_work_cpu) अणु
			cancel_delayed_work(&d->mbm_over);
			mbm_setup_overflow_handler(d, 0);
		पूर्ण
		अगर (is_llc_occupancy_enabled() && cpu == d->cqm_work_cpu &&
		    has_busy_rmid(r, d)) अणु
			cancel_delayed_work(&d->cqm_limbo);
			cqm_setup_limbo_handler(d, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clear_closid_rmid(पूर्णांक cpu)
अणु
	काष्ठा resctrl_pqr_state *state = this_cpu_ptr(&pqr_state);

	state->शेष_closid = 0;
	state->शेष_rmid = 0;
	state->cur_closid = 0;
	state->cur_rmid = 0;
	wrmsr(IA32_PQR_ASSOC, 0, 0);
पूर्ण

अटल पूर्णांक resctrl_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rdt_resource *r;

	mutex_lock(&rdtgroup_mutex);
	क्रम_each_capable_rdt_resource(r)
		करोमुख्य_add_cpu(cpu, r);
	/* The cpu is set in शेष rdtgroup after online. */
	cpumask_set_cpu(cpu, &rdtgroup_शेष.cpu_mask);
	clear_closid_rmid(cpu);
	mutex_unlock(&rdtgroup_mutex);

	वापस 0;
पूर्ण

अटल व्योम clear_childcpus(काष्ठा rdtgroup *r, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rdtgroup *cr;

	list_क्रम_each_entry(cr, &r->mon.crdtgrp_list, mon.crdtgrp_list) अणु
		अगर (cpumask_test_and_clear_cpu(cpu, &cr->cpu_mask)) अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक resctrl_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा rdt_resource *r;

	mutex_lock(&rdtgroup_mutex);
	क्रम_each_capable_rdt_resource(r)
		करोमुख्य_हटाओ_cpu(cpu, r);
	list_क्रम_each_entry(rdtgrp, &rdt_all_groups, rdtgroup_list) अणु
		अगर (cpumask_test_and_clear_cpu(cpu, &rdtgrp->cpu_mask)) अणु
			clear_childcpus(rdtgrp, cpu);
			अवरोध;
		पूर्ण
	पूर्ण
	clear_closid_rmid(cpu);
	mutex_unlock(&rdtgroup_mutex);

	वापस 0;
पूर्ण

/*
 * Choose a width क्रम the resource name and resource data based on the
 * resource that has widest name and cbm.
 */
अटल __init व्योम rdt_init_padding(व्योम)
अणु
	काष्ठा rdt_resource *r;
	पूर्णांक cl;

	क्रम_each_alloc_capable_rdt_resource(r) अणु
		cl = म_माप(r->name);
		अगर (cl > max_name_width)
			max_name_width = cl;

		अगर (r->data_width > max_data_width)
			max_data_width = r->data_width;
	पूर्ण
पूर्ण

क्रमागत अणु
	RDT_FLAG_CMT,
	RDT_FLAG_MBM_TOTAL,
	RDT_FLAG_MBM_LOCAL,
	RDT_FLAG_L3_CAT,
	RDT_FLAG_L3_CDP,
	RDT_FLAG_L2_CAT,
	RDT_FLAG_L2_CDP,
	RDT_FLAG_MBA,
पूर्ण;

#घोषणा RDT_OPT(idx, n, f)	\
[idx] = अणु			\
	.name = n,		\
	.flag = f		\
पूर्ण

काष्ठा rdt_options अणु
	अक्षर	*name;
	पूर्णांक	flag;
	bool	क्रमce_off, क्रमce_on;
पूर्ण;

अटल काष्ठा rdt_options rdt_options[]  __initdata = अणु
	RDT_OPT(RDT_FLAG_CMT,	    "cmt",	X86_FEATURE_CQM_OCCUP_LLC),
	RDT_OPT(RDT_FLAG_MBM_TOTAL, "mbmtotal", X86_FEATURE_CQM_MBM_TOTAL),
	RDT_OPT(RDT_FLAG_MBM_LOCAL, "mbmlocal", X86_FEATURE_CQM_MBM_LOCAL),
	RDT_OPT(RDT_FLAG_L3_CAT,    "l3cat",	X86_FEATURE_CAT_L3),
	RDT_OPT(RDT_FLAG_L3_CDP,    "l3cdp",	X86_FEATURE_CDP_L3),
	RDT_OPT(RDT_FLAG_L2_CAT,    "l2cat",	X86_FEATURE_CAT_L2),
	RDT_OPT(RDT_FLAG_L2_CDP,    "l2cdp",	X86_FEATURE_CDP_L2),
	RDT_OPT(RDT_FLAG_MBA,	    "mba",	X86_FEATURE_MBA),
पूर्ण;
#घोषणा NUM_RDT_OPTIONS ARRAY_SIZE(rdt_options)

अटल पूर्णांक __init set_rdt_options(अक्षर *str)
अणु
	काष्ठा rdt_options *o;
	bool क्रमce_off;
	अक्षर *tok;

	अगर (*str == '=')
		str++;
	जबतक ((tok = strsep(&str, ",")) != शून्य) अणु
		क्रमce_off = *tok == '!';
		अगर (क्रमce_off)
			tok++;
		क्रम (o = rdt_options; o < &rdt_options[NUM_RDT_OPTIONS]; o++) अणु
			अगर (म_भेद(tok, o->name) == 0) अणु
				अगर (क्रमce_off)
					o->क्रमce_off = true;
				अन्यथा
					o->क्रमce_on = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
__setup("rdt", set_rdt_options);

अटल bool __init rdt_cpu_has(पूर्णांक flag)
अणु
	bool ret = boot_cpu_has(flag);
	काष्ठा rdt_options *o;

	अगर (!ret)
		वापस ret;

	क्रम (o = rdt_options; o < &rdt_options[NUM_RDT_OPTIONS]; o++) अणु
		अगर (flag == o->flag) अणु
			अगर (o->क्रमce_off)
				ret = false;
			अगर (o->क्रमce_on)
				ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल __init bool get_mem_config(व्योम)
अणु
	अगर (!rdt_cpu_has(X86_FEATURE_MBA))
		वापस false;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		वापस __get_mem_config_पूर्णांकel(&rdt_resources_all[RDT_RESOURCE_MBA]);
	अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		वापस __rdt_get_mem_config_amd(&rdt_resources_all[RDT_RESOURCE_MBA]);

	वापस false;
पूर्ण

अटल __init bool get_rdt_alloc_resources(व्योम)
अणु
	bool ret = false;

	अगर (rdt_alloc_capable)
		वापस true;

	अगर (!boot_cpu_has(X86_FEATURE_RDT_A))
		वापस false;

	अगर (rdt_cpu_has(X86_FEATURE_CAT_L3)) अणु
		rdt_get_cache_alloc_cfg(1, &rdt_resources_all[RDT_RESOURCE_L3]);
		अगर (rdt_cpu_has(X86_FEATURE_CDP_L3))
			rdt_get_cdp_l3_config();
		ret = true;
	पूर्ण
	अगर (rdt_cpu_has(X86_FEATURE_CAT_L2)) अणु
		/* CPUID 0x10.2 fields are same क्रमmat at 0x10.1 */
		rdt_get_cache_alloc_cfg(2, &rdt_resources_all[RDT_RESOURCE_L2]);
		अगर (rdt_cpu_has(X86_FEATURE_CDP_L2))
			rdt_get_cdp_l2_config();
		ret = true;
	पूर्ण

	अगर (get_mem_config())
		ret = true;

	वापस ret;
पूर्ण

अटल __init bool get_rdt_mon_resources(व्योम)
अणु
	अगर (rdt_cpu_has(X86_FEATURE_CQM_OCCUP_LLC))
		rdt_mon_features |= (1 << QOS_L3_OCCUP_EVENT_ID);
	अगर (rdt_cpu_has(X86_FEATURE_CQM_MBM_TOTAL))
		rdt_mon_features |= (1 << QOS_L3_MBM_TOTAL_EVENT_ID);
	अगर (rdt_cpu_has(X86_FEATURE_CQM_MBM_LOCAL))
		rdt_mon_features |= (1 << QOS_L3_MBM_LOCAL_EVENT_ID);

	अगर (!rdt_mon_features)
		वापस false;

	वापस !rdt_get_mon_l3_config(&rdt_resources_all[RDT_RESOURCE_L3]);
पूर्ण

अटल __init व्योम __check_quirks_पूर्णांकel(व्योम)
अणु
	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_HASWELL_X:
		अगर (!rdt_options[RDT_FLAG_L3_CAT].क्रमce_off)
			cache_alloc_hsw_probe();
		अवरोध;
	हाल INTEL_FAM6_SKYLAKE_X:
		अगर (boot_cpu_data.x86_stepping <= 4)
			set_rdt_options("!cmt,!mbmtotal,!mbmlocal,!l3cat");
		अन्यथा
			set_rdt_options("!l3cat");
		fallthrough;
	हाल INTEL_FAM6_BROADWELL_X:
		पूर्णांकel_rdt_mbm_apply_quirk();
		अवरोध;
	पूर्ण
पूर्ण

अटल __init व्योम check_quirks(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		__check_quirks_पूर्णांकel();
पूर्ण

अटल __init bool get_rdt_resources(व्योम)
अणु
	rdt_alloc_capable = get_rdt_alloc_resources();
	rdt_mon_capable = get_rdt_mon_resources();

	वापस (rdt_mon_capable || rdt_alloc_capable);
पूर्ण

अटल __init व्योम rdt_init_res_defs_पूर्णांकel(व्योम)
अणु
	काष्ठा rdt_resource *r;

	क्रम_each_rdt_resource(r) अणु
		अगर (r->rid == RDT_RESOURCE_L3 ||
		    r->rid == RDT_RESOURCE_L3DATA ||
		    r->rid == RDT_RESOURCE_L3CODE ||
		    r->rid == RDT_RESOURCE_L2 ||
		    r->rid == RDT_RESOURCE_L2DATA ||
		    r->rid == RDT_RESOURCE_L2CODE) अणु
			r->cache.arch_has_sparse_biपंचांगaps = false;
			r->cache.arch_has_empty_biपंचांगaps = false;
			r->cache.arch_has_per_cpu_cfg = false;
		पूर्ण अन्यथा अगर (r->rid == RDT_RESOURCE_MBA) अणु
			r->msr_base = MSR_IA32_MBA_THRTL_BASE;
			r->msr_update = mba_wrmsr_पूर्णांकel;
		पूर्ण
	पूर्ण
पूर्ण

अटल __init व्योम rdt_init_res_defs_amd(व्योम)
अणु
	काष्ठा rdt_resource *r;

	क्रम_each_rdt_resource(r) अणु
		अगर (r->rid == RDT_RESOURCE_L3 ||
		    r->rid == RDT_RESOURCE_L3DATA ||
		    r->rid == RDT_RESOURCE_L3CODE ||
		    r->rid == RDT_RESOURCE_L2 ||
		    r->rid == RDT_RESOURCE_L2DATA ||
		    r->rid == RDT_RESOURCE_L2CODE) अणु
			r->cache.arch_has_sparse_biपंचांगaps = true;
			r->cache.arch_has_empty_biपंचांगaps = true;
			r->cache.arch_has_per_cpu_cfg = true;
		पूर्ण अन्यथा अगर (r->rid == RDT_RESOURCE_MBA) अणु
			r->msr_base = MSR_IA32_MBA_BW_BASE;
			r->msr_update = mba_wrmsr_amd;
		पूर्ण
	पूर्ण
पूर्ण

अटल __init व्योम rdt_init_res_defs(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		rdt_init_res_defs_पूर्णांकel();
	अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		rdt_init_res_defs_amd();
पूर्ण

अटल क्रमागत cpuhp_state rdt_online;

/* Runs once on the BSP during boot. */
व्योम resctrl_cpu_detect(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (!cpu_has(c, X86_FEATURE_CQM_LLC)) अणु
		c->x86_cache_max_rmid  = -1;
		c->x86_cache_occ_scale = -1;
		c->x86_cache_mbm_width_offset = -1;
		वापस;
	पूर्ण

	/* will be overridden अगर occupancy monitoring exists */
	c->x86_cache_max_rmid = cpuid_ebx(0xf);

	अगर (cpu_has(c, X86_FEATURE_CQM_OCCUP_LLC) ||
	    cpu_has(c, X86_FEATURE_CQM_MBM_TOTAL) ||
	    cpu_has(c, X86_FEATURE_CQM_MBM_LOCAL)) अणु
		u32 eax, ebx, ecx, edx;

		/* QoS sub-leaf, EAX=0Fh, ECX=1 */
		cpuid_count(0xf, 1, &eax, &ebx, &ecx, &edx);

		c->x86_cache_max_rmid  = ecx;
		c->x86_cache_occ_scale = ebx;
		c->x86_cache_mbm_width_offset = eax & 0xff;

		अगर (c->x86_venकरोr == X86_VENDOR_AMD && !c->x86_cache_mbm_width_offset)
			c->x86_cache_mbm_width_offset = MBM_CNTR_WIDTH_OFFSET_AMD;
	पूर्ण
पूर्ण

अटल पूर्णांक __init resctrl_late_init(व्योम)
अणु
	काष्ठा rdt_resource *r;
	पूर्णांक state, ret;

	/*
	 * Initialize functions(or definitions) that are dअगरferent
	 * between venकरोrs here.
	 */
	rdt_init_res_defs();

	check_quirks();

	अगर (!get_rdt_resources())
		वापस -ENODEV;

	rdt_init_padding();

	state = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
				  "x86/resctrl/cat:online:",
				  resctrl_online_cpu, resctrl_offline_cpu);
	अगर (state < 0)
		वापस state;

	ret = rdtgroup_init();
	अगर (ret) अणु
		cpuhp_हटाओ_state(state);
		वापस ret;
	पूर्ण
	rdt_online = state;

	क्रम_each_alloc_capable_rdt_resource(r)
		pr_info("%s allocation detected\n", r->name);

	क्रम_each_mon_capable_rdt_resource(r)
		pr_info("%s monitoring detected\n", r->name);

	वापस 0;
पूर्ण

late_initcall(resctrl_late_init);

अटल व्योम __निकास resctrl_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(rdt_online);
	rdtgroup_निकास();
पूर्ण

__निकासcall(resctrl_निकास);
