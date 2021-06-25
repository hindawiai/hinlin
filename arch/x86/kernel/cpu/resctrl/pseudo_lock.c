<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Resource Director Technology (RDT)
 *
 * Pseuकरो-locking support built on top of Cache Allocation Technology (CAT)
 *
 * Copyright (C) 2018 Intel Corporation
 *
 * Author: Reinette Chatre <reinette.chatre@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mman.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/resctrl.h>
#समावेश <यंत्र/perf_event.h>

#समावेश "../../events/perf_event.h" /* For X86_CONFIG() */
#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "pseudo_lock_event.h"

/*
 * The bits needed to disable hardware prefetching varies based on the
 * platक्रमm. During initialization we will discover which bits to use.
 */
अटल u64 prefetch_disable_bits;

/*
 * Major number asचिन्हित to and shared by all devices exposing
 * pseuकरो-locked regions.
 */
अटल अचिन्हित पूर्णांक pseuकरो_lock_major;
अटल अचिन्हित दीर्घ pseuकरो_lock_minor_avail = GENMASK(MINORBITS, 0);
अटल काष्ठा class *pseuकरो_lock_class;

/**
 * get_prefetch_disable_bits - prefetch disable bits of supported platक्रमms
 *
 * Capture the list of platक्रमms that have been validated to support
 * pseuकरो-locking. This includes testing to ensure pseuकरो-locked regions
 * with low cache miss rates can be created under variety of load conditions
 * as well as that these pseuकरो-locked regions can मुख्यtain their low cache
 * miss rates under variety of load conditions क्रम signअगरicant lengths of समय.
 *
 * After a platक्रमm has been validated to support pseuकरो-locking its
 * hardware prefetch disable bits are included here as they are करोcumented
 * in the SDM.
 *
 * When adding a platक्रमm here also add support क्रम its cache events to
 * measure_cycles_perf_fn()
 *
 * Return:
 * If platक्रमm is supported, the bits to disable hardware prefetchers, 0
 * अगर platक्रमm is not supported.
 */
अटल u64 get_prefetch_disable_bits(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL ||
	    boot_cpu_data.x86 != 6)
		वापस 0;

	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_BROADWELL_X:
		/*
		 * SDM defines bits of MSR_MISC_FEATURE_CONTROL रेजिस्टर
		 * as:
		 * 0    L2 Hardware Prefetcher Disable (R/W)
		 * 1    L2 Adjacent Cache Line Prefetcher Disable (R/W)
		 * 2    DCU Hardware Prefetcher Disable (R/W)
		 * 3    DCU IP Prefetcher Disable (R/W)
		 * 63:4 Reserved
		 */
		वापस 0xF;
	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		/*
		 * SDM defines bits of MSR_MISC_FEATURE_CONTROL रेजिस्टर
		 * as:
		 * 0     L2 Hardware Prefetcher Disable (R/W)
		 * 1     Reserved
		 * 2     DCU Hardware Prefetcher Disable (R/W)
		 * 63:3  Reserved
		 */
		वापस 0x5;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pseuकरो_lock_minor_get - Obtain available minor number
 * @minor: Poपूर्णांकer to where new minor number will be stored
 *
 * A biपंचांगask is used to track available minor numbers. Here the next मुक्त
 * minor number is marked as unavailable and वापसed.
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक pseuकरो_lock_minor_get(अचिन्हित पूर्णांक *minor)
अणु
	अचिन्हित दीर्घ first_bit;

	first_bit = find_first_bit(&pseuकरो_lock_minor_avail, MINORBITS);

	अगर (first_bit == MINORBITS)
		वापस -ENOSPC;

	__clear_bit(first_bit, &pseuकरो_lock_minor_avail);
	*minor = first_bit;

	वापस 0;
पूर्ण

/**
 * pseuकरो_lock_minor_release - Return minor number to available
 * @minor: The minor number made available
 */
अटल व्योम pseuकरो_lock_minor_release(अचिन्हित पूर्णांक minor)
अणु
	__set_bit(minor, &pseuकरो_lock_minor_avail);
पूर्ण

/**
 * region_find_by_minor - Locate a pseuकरो-lock region by inode minor number
 * @minor: The minor number of the device representing pseuकरो-locked region
 *
 * When the अक्षरacter device is accessed we need to determine which
 * pseuकरो-locked region it beदीर्घs to. This is करोne by matching the minor
 * number of the device to the pseuकरो-locked region it beदीर्घs.
 *
 * Minor numbers are asचिन्हित at the समय a pseuकरो-locked region is associated
 * with a cache instance.
 *
 * Return: On success वापस poपूर्णांकer to resource group owning the pseuकरो-locked
 *         region, शून्य on failure.
 */
अटल काष्ठा rdtgroup *region_find_by_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा rdtgroup *rdtgrp, *rdtgrp_match = शून्य;

	list_क्रम_each_entry(rdtgrp, &rdt_all_groups, rdtgroup_list) अणु
		अगर (rdtgrp->plr && rdtgrp->plr->minor == minor) अणु
			rdtgrp_match = rdtgrp;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rdtgrp_match;
पूर्ण

/**
 * pseuकरो_lock_pm_req - A घातer management QoS request list entry
 * @list:	Entry within the @pm_reqs list क्रम a pseuकरो-locked region
 * @req:	PM QoS request
 */
काष्ठा pseuकरो_lock_pm_req अणु
	काष्ठा list_head list;
	काष्ठा dev_pm_qos_request req;
पूर्ण;

अटल व्योम pseuकरो_lock_cstates_relax(काष्ठा pseuकरो_lock_region *plr)
अणु
	काष्ठा pseuकरो_lock_pm_req *pm_req, *next;

	list_क्रम_each_entry_safe(pm_req, next, &plr->pm_reqs, list) अणु
		dev_pm_qos_हटाओ_request(&pm_req->req);
		list_del(&pm_req->list);
		kमुक्त(pm_req);
	पूर्ण
पूर्ण

/**
 * pseuकरो_lock_cstates_स्थिरrain - Restrict cores from entering C6
 *
 * To prevent the cache from being affected by घातer management entering
 * C6 has to be aव्योमed. This is accomplished by requesting a latency
 * requirement lower than lowest C6 निकास latency of all supported
 * platक्रमms as found in the cpuidle state tables in the पूर्णांकel_idle driver.
 * At this समय it is possible to करो so with a single latency requirement
 * क्रम all supported platक्रमms.
 *
 * Since Goldmont is supported, which is affected by X86_BUG_MONITOR,
 * the ACPI latencies need to be considered जबतक keeping in mind that C2
 * may be set to map to deeper sleep states. In this हाल the latency
 * requirement needs to prevent entering C2 also.
 */
अटल पूर्णांक pseuकरो_lock_cstates_स्थिरrain(काष्ठा pseuकरो_lock_region *plr)
अणु
	काष्ठा pseuकरो_lock_pm_req *pm_req;
	पूर्णांक cpu;
	पूर्णांक ret;

	क्रम_each_cpu(cpu, &plr->d->cpu_mask) अणु
		pm_req = kzalloc(माप(*pm_req), GFP_KERNEL);
		अगर (!pm_req) अणु
			rdt_last_cmd_माला_दो("Failure to allocate memory for PM QoS\n");
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
		ret = dev_pm_qos_add_request(get_cpu_device(cpu),
					     &pm_req->req,
					     DEV_PM_QOS_RESUME_LATENCY,
					     30);
		अगर (ret < 0) अणु
			rdt_last_cmd_म_लिखो("Failed to add latency req CPU%d\n",
					    cpu);
			kमुक्त(pm_req);
			ret = -1;
			जाओ out_err;
		पूर्ण
		list_add(&pm_req->list, &plr->pm_reqs);
	पूर्ण

	वापस 0;

out_err:
	pseuकरो_lock_cstates_relax(plr);
	वापस ret;
पूर्ण

/**
 * pseuकरो_lock_region_clear - Reset pseuकरो-lock region data
 * @plr: pseuकरो-lock region
 *
 * All content of the pseuकरो-locked region is reset - any memory allocated
 * मुक्तd.
 *
 * Return: व्योम
 */
अटल व्योम pseuकरो_lock_region_clear(काष्ठा pseuकरो_lock_region *plr)
अणु
	plr->size = 0;
	plr->line_size = 0;
	kमुक्त(plr->kmem);
	plr->kmem = शून्य;
	plr->r = शून्य;
	अगर (plr->d)
		plr->d->plr = शून्य;
	plr->d = शून्य;
	plr->cbm = 0;
	plr->debugfs_dir = शून्य;
पूर्ण

/**
 * pseuकरो_lock_region_init - Initialize pseuकरो-lock region inक्रमmation
 * @plr: pseuकरो-lock region
 *
 * Called after user provided a schemata to be pseuकरो-locked. From the
 * schemata the &काष्ठा pseuकरो_lock_region is on entry alपढ़ोy initialized
 * with the resource, करोमुख्य, and capacity biपंचांगask. Here the inक्रमmation
 * required क्रम pseuकरो-locking is deduced from this data and &काष्ठा
 * pseuकरो_lock_region initialized further. This inक्रमmation includes:
 * - size in bytes of the region to be pseuकरो-locked
 * - cache line size to know the stride with which data needs to be accessed
 *   to be pseuकरो-locked
 * - a cpu associated with the cache instance on which the pseuकरो-locking
 *   flow can be executed
 *
 * Return: 0 on success, <0 on failure. Descriptive error will be written
 * to last_cmd_status buffer.
 */
अटल पूर्णांक pseuकरो_lock_region_init(काष्ठा pseuकरो_lock_region *plr)
अणु
	काष्ठा cpu_cacheinfo *ci;
	पूर्णांक ret;
	पूर्णांक i;

	/* Pick the first cpu we find that is associated with the cache. */
	plr->cpu = cpumask_first(&plr->d->cpu_mask);

	अगर (!cpu_online(plr->cpu)) अणु
		rdt_last_cmd_म_लिखो("CPU %u associated with cache not online\n",
				    plr->cpu);
		ret = -ENODEV;
		जाओ out_region;
	पूर्ण

	ci = get_cpu_cacheinfo(plr->cpu);

	plr->size = rdtgroup_cbm_to_size(plr->r, plr->d, plr->cbm);

	क्रम (i = 0; i < ci->num_leaves; i++) अणु
		अगर (ci->info_list[i].level == plr->r->cache_level) अणु
			plr->line_size = ci->info_list[i].coherency_line_size;
			वापस 0;
		पूर्ण
	पूर्ण

	ret = -1;
	rdt_last_cmd_माला_दो("Unable to determine cache line size\n");
out_region:
	pseuकरो_lock_region_clear(plr);
	वापस ret;
पूर्ण

/**
 * pseuकरो_lock_init - Initialize a pseuकरो-lock region
 * @rdtgrp: resource group to which new pseuकरो-locked region will beदीर्घ
 *
 * A pseuकरो-locked region is associated with a resource group. When this
 * association is created the pseuकरो-locked region is initialized. The
 * details of the pseuकरो-locked region are not known at this समय so only
 * allocation is करोne and association established.
 *
 * Return: 0 on success, <0 on failure
 */
अटल पूर्णांक pseuकरो_lock_init(काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा pseuकरो_lock_region *plr;

	plr = kzalloc(माप(*plr), GFP_KERNEL);
	अगर (!plr)
		वापस -ENOMEM;

	init_रुकोqueue_head(&plr->lock_thपढ़ो_wq);
	INIT_LIST_HEAD(&plr->pm_reqs);
	rdtgrp->plr = plr;
	वापस 0;
पूर्ण

/**
 * pseuकरो_lock_region_alloc - Allocate kernel memory that will be pseuकरो-locked
 * @plr: pseuकरो-lock region
 *
 * Initialize the details required to set up the pseuकरो-locked region and
 * allocate the contiguous memory that will be pseuकरो-locked to the cache.
 *
 * Return: 0 on success, <0 on failure.  Descriptive error will be written
 * to last_cmd_status buffer.
 */
अटल पूर्णांक pseuकरो_lock_region_alloc(काष्ठा pseuकरो_lock_region *plr)
अणु
	पूर्णांक ret;

	ret = pseuकरो_lock_region_init(plr);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We करो not yet support contiguous regions larger than
	 * KMALLOC_MAX_SIZE.
	 */
	अगर (plr->size > KMALLOC_MAX_SIZE) अणु
		rdt_last_cmd_माला_दो("Requested region exceeds maximum size\n");
		ret = -E2BIG;
		जाओ out_region;
	पूर्ण

	plr->kmem = kzalloc(plr->size, GFP_KERNEL);
	अगर (!plr->kmem) अणु
		rdt_last_cmd_माला_दो("Unable to allocate memory\n");
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	ret = 0;
	जाओ out;
out_region:
	pseuकरो_lock_region_clear(plr);
out:
	वापस ret;
पूर्ण

/**
 * pseuकरो_lock_मुक्त - Free a pseuकरो-locked region
 * @rdtgrp: resource group to which pseuकरो-locked region beदीर्घed
 *
 * The pseuकरो-locked region's resources have alपढ़ोy been released, or not
 * yet created at this poपूर्णांक. Now it can be मुक्तd and disassociated from the
 * resource group.
 *
 * Return: व्योम
 */
अटल व्योम pseuकरो_lock_मुक्त(काष्ठा rdtgroup *rdtgrp)
अणु
	pseuकरो_lock_region_clear(rdtgrp->plr);
	kमुक्त(rdtgrp->plr);
	rdtgrp->plr = शून्य;
पूर्ण

/**
 * pseuकरो_lock_fn - Load kernel memory पूर्णांकo cache
 * @_rdtgrp: resource group to which pseuकरो-lock region beदीर्घs
 *
 * This is the core pseuकरो-locking flow.
 *
 * First we ensure that the kernel memory cannot be found in the cache.
 * Then, जबतक taking care that there will be as little पूर्णांकerference as
 * possible, the memory to be loaded is accessed जबतक core is running
 * with class of service set to the biपंचांगask of the pseuकरो-locked region.
 * After this is complete no future CAT allocations will be allowed to
 * overlap with this biपंचांगask.
 *
 * Local रेजिस्टर variables are utilized to ensure that the memory region
 * to be locked is the only memory access made during the critical locking
 * loop.
 *
 * Return: 0. Waiter on रुकोqueue will be woken on completion.
 */
अटल पूर्णांक pseuकरो_lock_fn(व्योम *_rdtgrp)
अणु
	काष्ठा rdtgroup *rdtgrp = _rdtgrp;
	काष्ठा pseuकरो_lock_region *plr = rdtgrp->plr;
	u32 rmid_p, closid_p;
	अचिन्हित दीर्घ i;
#अगर_घोषित CONFIG_KASAN
	/*
	 * The रेजिस्टरs used क्रम local रेजिस्टर variables are also used
	 * when KASAN is active. When KASAN is active we use a regular
	 * variable to ensure we always use a valid poपूर्णांकer, but the cost
	 * is that this variable will enter the cache through evicting the
	 * memory we are trying to lock पूर्णांकo the cache. Thus expect lower
	 * pseuकरो-locking success rate when KASAN is active.
	 */
	अचिन्हित पूर्णांक line_size;
	अचिन्हित पूर्णांक size;
	व्योम *mem_r;
#अन्यथा
	रेजिस्टर अचिन्हित पूर्णांक line_size यंत्र("esi");
	रेजिस्टर अचिन्हित पूर्णांक size यंत्र("edi");
	रेजिस्टर व्योम *mem_r यंत्र(_ASM_BX);
#पूर्ण_अगर /* CONFIG_KASAN */

	/*
	 * Make sure none of the allocated memory is cached. If it is we
	 * will get a cache hit in below loop from outside of pseuकरो-locked
	 * region.
	 * wbinvd (as opposed to clflush/clflushopt) is required to
	 * increase likelihood that allocated cache portion will be filled
	 * with associated memory.
	 */
	native_wbinvd();

	/*
	 * Always called with पूर्णांकerrupts enabled. By disabling पूर्णांकerrupts
	 * ensure that we will not be preempted during this critical section.
	 */
	local_irq_disable();

	/*
	 * Call wrmsr and rdmsr as directly as possible to aव्योम tracing
	 * clobbering local रेजिस्टर variables or affecting cache accesses.
	 *
	 * Disable the hardware prefetcher so that when the end of the memory
	 * being pseuकरो-locked is reached the hardware will not पढ़ो beyond
	 * the buffer and evict pseuकरो-locked memory पढ़ो earlier from the
	 * cache.
	 */
	__wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);
	closid_p = this_cpu_पढ़ो(pqr_state.cur_closid);
	rmid_p = this_cpu_पढ़ो(pqr_state.cur_rmid);
	mem_r = plr->kmem;
	size = plr->size;
	line_size = plr->line_size;
	/*
	 * Critical section begin: start by writing the closid associated
	 * with the capacity biपंचांगask of the cache region being
	 * pseuकरो-locked followed by पढ़ोing of kernel memory to load it
	 * पूर्णांकo the cache.
	 */
	__wrmsr(IA32_PQR_ASSOC, rmid_p, rdtgrp->closid);
	/*
	 * Cache was flushed earlier. Now access kernel memory to पढ़ो it
	 * पूर्णांकo cache region associated with just activated plr->closid.
	 * Loop over data twice:
	 * - In first loop the cache region is shared with the page walker
	 *   as it populates the paging काष्ठाure caches (including TLB).
	 * - In the second loop the paging काष्ठाure caches are used and
	 *   cache region is populated with the memory being referenced.
	 */
	क्रम (i = 0; i < size; i += PAGE_SIZE) अणु
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop पढ़ोing beyond the end of the buffer.
		 */
		rmb();
		यंत्र अस्थिर("mov (%0,%1,1), %%eax\n\t"
			:
			: "r" (mem_r), "r" (i)
			: "%eax", "memory");
	पूर्ण
	क्रम (i = 0; i < size; i += line_size) अणु
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop पढ़ोing beyond the end of the buffer.
		 */
		rmb();
		यंत्र अस्थिर("mov (%0,%1,1), %%eax\n\t"
			:
			: "r" (mem_r), "r" (i)
			: "%eax", "memory");
	पूर्ण
	/*
	 * Critical section end: restore closid with capacity biपंचांगask that
	 * करोes not overlap with pseuकरो-locked region.
	 */
	__wrmsr(IA32_PQR_ASSOC, rmid_p, closid_p);

	/* Re-enable the hardware prefetcher(s) */
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();

	plr->thपढ़ो_करोne = 1;
	wake_up_पूर्णांकerruptible(&plr->lock_thपढ़ो_wq);
	वापस 0;
पूर्ण

/**
 * rdtgroup_monitor_in_progress - Test अगर monitoring in progress
 * @r: resource group being queried
 *
 * Return: 1 अगर monitor groups have been created क्रम this resource
 * group, 0 otherwise.
 */
अटल पूर्णांक rdtgroup_monitor_in_progress(काष्ठा rdtgroup *rdtgrp)
अणु
	वापस !list_empty(&rdtgrp->mon.crdtgrp_list);
पूर्ण

/**
 * rdtgroup_locksetup_user_restrict - Restrict user access to group
 * @rdtgrp: resource group needing access restricted
 *
 * A resource group used क्रम cache pseuकरो-locking cannot have cpus or tasks
 * asचिन्हित to it. This is communicated to the user by restricting access
 * to all the files that can be used to make such changes.
 *
 * Permissions restored with rdtgroup_locksetup_user_restore()
 *
 * Return: 0 on success, <0 on failure. If a failure occurs during the
 * restriction of access an attempt will be made to restore permissions but
 * the state of the mode of these files will be uncertain when a failure
 * occurs.
 */
अटल पूर्णांक rdtgroup_locksetup_user_restrict(काष्ठा rdtgroup *rdtgrp)
अणु
	पूर्णांक ret;

	ret = rdtgroup_kn_mode_restrict(rdtgrp, "tasks");
	अगर (ret)
		वापस ret;

	ret = rdtgroup_kn_mode_restrict(rdtgrp, "cpus");
	अगर (ret)
		जाओ err_tasks;

	ret = rdtgroup_kn_mode_restrict(rdtgrp, "cpus_list");
	अगर (ret)
		जाओ err_cpus;

	अगर (rdt_mon_capable) अणु
		ret = rdtgroup_kn_mode_restrict(rdtgrp, "mon_groups");
		अगर (ret)
			जाओ err_cpus_list;
	पूर्ण

	ret = 0;
	जाओ out;

err_cpus_list:
	rdtgroup_kn_mode_restore(rdtgrp, "cpus_list", 0777);
err_cpus:
	rdtgroup_kn_mode_restore(rdtgrp, "cpus", 0777);
err_tasks:
	rdtgroup_kn_mode_restore(rdtgrp, "tasks", 0777);
out:
	वापस ret;
पूर्ण

/**
 * rdtgroup_locksetup_user_restore - Restore user access to group
 * @rdtgrp: resource group needing access restored
 *
 * Restore all file access previously हटाओd using
 * rdtgroup_locksetup_user_restrict()
 *
 * Return: 0 on success, <0 on failure.  If a failure occurs during the
 * restoration of access an attempt will be made to restrict permissions
 * again but the state of the mode of these files will be uncertain when
 * a failure occurs.
 */
अटल पूर्णांक rdtgroup_locksetup_user_restore(काष्ठा rdtgroup *rdtgrp)
अणु
	पूर्णांक ret;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "tasks", 0777);
	अगर (ret)
		वापस ret;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "cpus", 0777);
	अगर (ret)
		जाओ err_tasks;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "cpus_list", 0777);
	अगर (ret)
		जाओ err_cpus;

	अगर (rdt_mon_capable) अणु
		ret = rdtgroup_kn_mode_restore(rdtgrp, "mon_groups", 0777);
		अगर (ret)
			जाओ err_cpus_list;
	पूर्ण

	ret = 0;
	जाओ out;

err_cpus_list:
	rdtgroup_kn_mode_restrict(rdtgrp, "cpus_list");
err_cpus:
	rdtgroup_kn_mode_restrict(rdtgrp, "cpus");
err_tasks:
	rdtgroup_kn_mode_restrict(rdtgrp, "tasks");
out:
	वापस ret;
पूर्ण

/**
 * rdtgroup_locksetup_enter - Resource group enters locksetup mode
 * @rdtgrp: resource group requested to enter locksetup mode
 *
 * A resource group enters locksetup mode to reflect that it would be used
 * to represent a pseuकरो-locked region and is in the process of being set
 * up to करो so. A resource group used क्रम a pseuकरो-locked region would
 * lose the closid associated with it so we cannot allow it to have any
 * tasks or cpus asचिन्हित nor permit tasks or cpus to be asचिन्हित in the
 * future. Monitoring of a pseuकरो-locked region is not allowed either.
 *
 * The above and more restrictions on a pseuकरो-locked region are checked
 * क्रम and enक्रमced beक्रमe the resource group enters the locksetup mode.
 *
 * Returns: 0 अगर the resource group successfully entered locksetup mode, <0
 * on failure. On failure the last_cmd_status buffer is updated with text to
 * communicate details of failure to the user.
 */
पूर्णांक rdtgroup_locksetup_enter(काष्ठा rdtgroup *rdtgrp)
अणु
	पूर्णांक ret;

	/*
	 * The शेष resource group can neither be हटाओd nor lose the
	 * शेष closid associated with it.
	 */
	अगर (rdtgrp == &rdtgroup_शेष) अणु
		rdt_last_cmd_माला_दो("Cannot pseudo-lock default group\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Cache Pseuकरो-locking not supported when CDP is enabled.
	 *
	 * Some things to consider अगर you would like to enable this
	 * support (using L3 CDP as example):
	 * - When CDP is enabled two separate resources are exposed,
	 *   L3DATA and L3CODE, but they are actually on the same cache.
	 *   The implication क्रम pseuकरो-locking is that अगर a
	 *   pseuकरो-locked region is created on a करोमुख्य of one
	 *   resource (eg. L3CODE), then a pseuकरो-locked region cannot
	 *   be created on that same करोमुख्य of the other resource
	 *   (eg. L3DATA). This is because the creation of a
	 *   pseuकरो-locked region involves a call to wbinvd that will
	 *   affect all cache allocations on particular करोमुख्य.
	 * - Considering the previous, it may be possible to only
	 *   expose one of the CDP resources to pseuकरो-locking and
	 *   hide the other. For example, we could consider to only
	 *   expose L3DATA and since the L3 cache is unअगरied it is
	 *   still possible to place inकाष्ठाions there are execute it.
	 * - If only one region is exposed to pseuकरो-locking we should
	 *   still keep in mind that availability of a portion of cache
	 *   क्रम pseuकरो-locking should take पूर्णांकo account both resources.
	 *   Similarly, अगर a pseuकरो-locked region is created in one
	 *   resource, the portion of cache used by it should be made
	 *   unavailable to all future allocations from both resources.
	 */
	अगर (rdt_resources_all[RDT_RESOURCE_L3DATA].alloc_enabled ||
	    rdt_resources_all[RDT_RESOURCE_L2DATA].alloc_enabled) अणु
		rdt_last_cmd_माला_दो("CDP enabled\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Not knowing the bits to disable prefetching implies that this
	 * platक्रमm करोes not support Cache Pseuकरो-Locking.
	 */
	prefetch_disable_bits = get_prefetch_disable_bits();
	अगर (prefetch_disable_bits == 0) अणु
		rdt_last_cmd_माला_दो("Pseudo-locking not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rdtgroup_monitor_in_progress(rdtgrp)) अणु
		rdt_last_cmd_माला_दो("Monitoring in progress\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rdtgroup_tasks_asचिन्हित(rdtgrp)) अणु
		rdt_last_cmd_माला_दो("Tasks assigned to resource group\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cpumask_empty(&rdtgrp->cpu_mask)) अणु
		rdt_last_cmd_माला_दो("CPUs assigned to resource group\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rdtgroup_locksetup_user_restrict(rdtgrp)) अणु
		rdt_last_cmd_माला_दो("Unable to modify resctrl permissions\n");
		वापस -EIO;
	पूर्ण

	ret = pseuकरो_lock_init(rdtgrp);
	अगर (ret) अणु
		rdt_last_cmd_माला_दो("Unable to init pseudo-lock region\n");
		जाओ out_release;
	पूर्ण

	/*
	 * If this प्रणाली is capable of monitoring a rmid would have been
	 * allocated when the control group was created. This is not needed
	 * anymore when this group would be used क्रम pseuकरो-locking. This
	 * is safe to call on platक्रमms not capable of monitoring.
	 */
	मुक्त_rmid(rdtgrp->mon.rmid);

	ret = 0;
	जाओ out;

out_release:
	rdtgroup_locksetup_user_restore(rdtgrp);
out:
	वापस ret;
पूर्ण

/**
 * rdtgroup_locksetup_निकास - resource group exist locksetup mode
 * @rdtgrp: resource group
 *
 * When a resource group निकासs locksetup mode the earlier restrictions are
 * lअगरted.
 *
 * Return: 0 on success, <0 on failure
 */
पूर्णांक rdtgroup_locksetup_निकास(काष्ठा rdtgroup *rdtgrp)
अणु
	पूर्णांक ret;

	अगर (rdt_mon_capable) अणु
		ret = alloc_rmid();
		अगर (ret < 0) अणु
			rdt_last_cmd_माला_दो("Out of RMIDs\n");
			वापस ret;
		पूर्ण
		rdtgrp->mon.rmid = ret;
	पूर्ण

	ret = rdtgroup_locksetup_user_restore(rdtgrp);
	अगर (ret) अणु
		मुक्त_rmid(rdtgrp->mon.rmid);
		वापस ret;
	पूर्ण

	pseuकरो_lock_मुक्त(rdtgrp);
	वापस 0;
पूर्ण

/**
 * rdtgroup_cbm_overlaps_pseuकरो_locked - Test अगर CBM or portion is pseuकरो-locked
 * @d: RDT करोमुख्य
 * @cbm: CBM to test
 *
 * @d represents a cache instance and @cbm a capacity biपंचांगask that is
 * considered क्रम it. Determine अगर @cbm overlaps with any existing
 * pseuकरो-locked region on @d.
 *
 * @cbm is अचिन्हित दीर्घ, even अगर only 32 bits are used, to make the
 * biपंचांगap functions work correctly.
 *
 * Return: true अगर @cbm overlaps with pseuकरो-locked region on @d, false
 * otherwise.
 */
bool rdtgroup_cbm_overlaps_pseuकरो_locked(काष्ठा rdt_करोमुख्य *d, अचिन्हित दीर्घ cbm)
अणु
	अचिन्हित पूर्णांक cbm_len;
	अचिन्हित दीर्घ cbm_b;

	अगर (d->plr) अणु
		cbm_len = d->plr->r->cache.cbm_len;
		cbm_b = d->plr->cbm;
		अगर (biपंचांगap_पूर्णांकersects(&cbm, &cbm_b, cbm_len))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * rdtgroup_pseuकरो_locked_in_hierarchy - Pseuकरो-locked region in cache hierarchy
 * @d: RDT करोमुख्य under test
 *
 * The setup of a pseuकरो-locked region affects all cache instances within
 * the hierarchy of the region. It is thus essential to know अगर any
 * pseuकरो-locked regions exist within a cache hierarchy to prevent any
 * attempts to create new pseuकरो-locked regions in the same hierarchy.
 *
 * Return: true अगर a pseuकरो-locked region exists in the hierarchy of @d or
 *         अगर it is not possible to test due to memory allocation issue,
 *         false otherwise.
 */
bool rdtgroup_pseuकरो_locked_in_hierarchy(काष्ठा rdt_करोमुख्य *d)
अणु
	cpumask_var_t cpu_with_psl;
	काष्ठा rdt_resource *r;
	काष्ठा rdt_करोमुख्य *d_i;
	bool ret = false;

	अगर (!zalloc_cpumask_var(&cpu_with_psl, GFP_KERNEL))
		वापस true;

	/*
	 * First determine which cpus have pseuकरो-locked regions
	 * associated with them.
	 */
	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		list_क्रम_each_entry(d_i, &r->करोमुख्यs, list) अणु
			अगर (d_i->plr)
				cpumask_or(cpu_with_psl, cpu_with_psl,
					   &d_i->cpu_mask);
		पूर्ण
	पूर्ण

	/*
	 * Next test अगर new pseuकरो-locked region would पूर्णांकersect with
	 * existing region.
	 */
	अगर (cpumask_पूर्णांकersects(&d->cpu_mask, cpu_with_psl))
		ret = true;

	मुक्त_cpumask_var(cpu_with_psl);
	वापस ret;
पूर्ण

/**
 * measure_cycles_lat_fn - Measure cycle latency to पढ़ो pseuकरो-locked memory
 * @_plr: pseuकरो-lock region to measure
 *
 * There is no deterministic way to test अगर a memory region is cached. One
 * way is to measure how दीर्घ it takes to पढ़ो the memory, the speed of
 * access is a good way to learn how बंद to the cpu the data was. Even
 * more, अगर the prefetcher is disabled and the memory is पढ़ो at a stride
 * of half the cache line, then a cache miss will be easy to spot since the
 * पढ़ो of the first half would be signअगरicantly slower than the पढ़ो of
 * the second half.
 *
 * Return: 0. Waiter on रुकोqueue will be woken on completion.
 */
अटल पूर्णांक measure_cycles_lat_fn(व्योम *_plr)
अणु
	काष्ठा pseuकरो_lock_region *plr = _plr;
	अचिन्हित दीर्घ i;
	u64 start, end;
	व्योम *mem_r;

	local_irq_disable();
	/*
	 * Disable hardware prefetchers.
	 */
	wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);
	mem_r = READ_ONCE(plr->kmem);
	/*
	 * Dummy execute of the समय measurement to load the needed
	 * inकाष्ठाions पूर्णांकo the L1 inकाष्ठाion cache.
	 */
	start = rdtsc_ordered();
	क्रम (i = 0; i < plr->size; i += 32) अणु
		start = rdtsc_ordered();
		यंत्र अस्थिर("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "r" (mem_r), "r" (i)
			     : "%eax", "memory");
		end = rdtsc_ordered();
		trace_pseuकरो_lock_mem_latency((u32)(end - start));
	पूर्ण
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();
	plr->thपढ़ो_करोne = 1;
	wake_up_पूर्णांकerruptible(&plr->lock_thपढ़ो_wq);
	वापस 0;
पूर्ण

/*
 * Create a perf_event_attr क्रम the hit and miss perf events that will
 * be used during the perक्रमmance measurement. A perf_event मुख्यtains
 * a poपूर्णांकer to its perf_event_attr so a unique attribute काष्ठाure is
 * created क्रम each perf_event.
 *
 * The actual configuration of the event is set right beक्रमe use in order
 * to use the X86_CONFIG macro.
 */
अटल काष्ठा perf_event_attr perf_miss_attr = अणु
	.type		= PERF_TYPE_RAW,
	.size		= माप(काष्ठा perf_event_attr),
	.pinned		= 1,
	.disabled	= 0,
	.exclude_user	= 1,
पूर्ण;

अटल काष्ठा perf_event_attr perf_hit_attr = अणु
	.type		= PERF_TYPE_RAW,
	.size		= माप(काष्ठा perf_event_attr),
	.pinned		= 1,
	.disabled	= 0,
	.exclude_user	= 1,
पूर्ण;

काष्ठा residency_counts अणु
	u64 miss_beक्रमe, hits_beक्रमe;
	u64 miss_after,  hits_after;
पूर्ण;

अटल पूर्णांक measure_residency_fn(काष्ठा perf_event_attr *miss_attr,
				काष्ठा perf_event_attr *hit_attr,
				काष्ठा pseuकरो_lock_region *plr,
				काष्ठा residency_counts *counts)
अणु
	u64 hits_beक्रमe = 0, hits_after = 0, miss_beक्रमe = 0, miss_after = 0;
	काष्ठा perf_event *miss_event, *hit_event;
	पूर्णांक hit_pmcnum, miss_pmcnum;
	अचिन्हित पूर्णांक line_size;
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ i;
	व्योम *mem_r;
	u64 पंचांगp;

	miss_event = perf_event_create_kernel_counter(miss_attr, plr->cpu,
						      शून्य, शून्य, शून्य);
	अगर (IS_ERR(miss_event))
		जाओ out;

	hit_event = perf_event_create_kernel_counter(hit_attr, plr->cpu,
						     शून्य, शून्य, शून्य);
	अगर (IS_ERR(hit_event))
		जाओ out_miss;

	local_irq_disable();
	/*
	 * Check any possible error state of events used by perक्रमming
	 * one local पढ़ो.
	 */
	अगर (perf_event_पढ़ो_local(miss_event, &पंचांगp, शून्य, शून्य)) अणु
		local_irq_enable();
		जाओ out_hit;
	पूर्ण
	अगर (perf_event_पढ़ो_local(hit_event, &पंचांगp, शून्य, शून्य)) अणु
		local_irq_enable();
		जाओ out_hit;
	पूर्ण

	/*
	 * Disable hardware prefetchers.
	 */
	wrmsr(MSR_MISC_FEATURE_CONTROL, prefetch_disable_bits, 0x0);

	/* Initialize rest of local variables */
	/*
	 * Perक्रमmance event has been validated right beक्रमe this with
	 * पूर्णांकerrupts disabled - it is thus safe to पढ़ो the counter index.
	 */
	miss_pmcnum = x86_perf_rdpmc_index(miss_event);
	hit_pmcnum = x86_perf_rdpmc_index(hit_event);
	line_size = READ_ONCE(plr->line_size);
	mem_r = READ_ONCE(plr->kmem);
	size = READ_ONCE(plr->size);

	/*
	 * Read counter variables twice - first to load the inकाष्ठाions
	 * used in L1 cache, second to capture accurate value that करोes not
	 * include cache misses incurred because of inकाष्ठाion loads.
	 */
	rdpmcl(hit_pmcnum, hits_beक्रमe);
	rdpmcl(miss_pmcnum, miss_beक्रमe);
	/*
	 * From SDM: Perक्रमming back-to-back fast पढ़ोs are not guaranteed
	 * to be monotonic.
	 * Use LFENCE to ensure all previous inकाष्ठाions are retired
	 * beक्रमe proceeding.
	 */
	rmb();
	rdpmcl(hit_pmcnum, hits_beक्रमe);
	rdpmcl(miss_pmcnum, miss_beक्रमe);
	/*
	 * Use LFENCE to ensure all previous inकाष्ठाions are retired
	 * beक्रमe proceeding.
	 */
	rmb();
	क्रम (i = 0; i < size; i += line_size) अणु
		/*
		 * Add a barrier to prevent speculative execution of this
		 * loop पढ़ोing beyond the end of the buffer.
		 */
		rmb();
		यंत्र अस्थिर("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "r" (mem_r), "r" (i)
			     : "%eax", "memory");
	पूर्ण
	/*
	 * Use LFENCE to ensure all previous inकाष्ठाions are retired
	 * beक्रमe proceeding.
	 */
	rmb();
	rdpmcl(hit_pmcnum, hits_after);
	rdpmcl(miss_pmcnum, miss_after);
	/*
	 * Use LFENCE to ensure all previous inकाष्ठाions are retired
	 * beक्रमe proceeding.
	 */
	rmb();
	/* Re-enable hardware prefetchers */
	wrmsr(MSR_MISC_FEATURE_CONTROL, 0x0, 0x0);
	local_irq_enable();
out_hit:
	perf_event_release_kernel(hit_event);
out_miss:
	perf_event_release_kernel(miss_event);
out:
	/*
	 * All counts will be zero on failure.
	 */
	counts->miss_beक्रमe = miss_beक्रमe;
	counts->hits_beक्रमe = hits_beक्रमe;
	counts->miss_after  = miss_after;
	counts->hits_after  = hits_after;
	वापस 0;
पूर्ण

अटल पूर्णांक measure_l2_residency(व्योम *_plr)
अणु
	काष्ठा pseuकरो_lock_region *plr = _plr;
	काष्ठा residency_counts counts = अणु0पूर्ण;

	/*
	 * Non-architectural event क्रम the Goldmont Microarchitecture
	 * from Intel x86 Architecture Software Developer Manual (SDM):
	 * MEM_LOAD_UOPS_RETIRED D1H (event number)
	 * Umask values:
	 *     L2_HIT   02H
	 *     L2_MISS  10H
	 */
	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		perf_miss_attr.config = X86_CONFIG(.event = 0xd1,
						   .umask = 0x10);
		perf_hit_attr.config = X86_CONFIG(.event = 0xd1,
						  .umask = 0x2);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	measure_residency_fn(&perf_miss_attr, &perf_hit_attr, plr, &counts);
	/*
	 * If a failure prevented the measurements from succeeding
	 * tracepoपूर्णांकs will still be written and all counts will be zero.
	 */
	trace_pseuकरो_lock_l2(counts.hits_after - counts.hits_beक्रमe,
			     counts.miss_after - counts.miss_beक्रमe);
out:
	plr->thपढ़ो_करोne = 1;
	wake_up_पूर्णांकerruptible(&plr->lock_thपढ़ो_wq);
	वापस 0;
पूर्ण

अटल पूर्णांक measure_l3_residency(व्योम *_plr)
अणु
	काष्ठा pseuकरो_lock_region *plr = _plr;
	काष्ठा residency_counts counts = अणु0पूर्ण;

	/*
	 * On Broadwell Microarchitecture the MEM_LOAD_UOPS_RETIRED event
	 * has two "no fix" errata associated with it: BDM35 and BDM100. On
	 * this platक्रमm the following events are used instead:
	 * LONGEST_LAT_CACHE 2EH (Documented in SDM)
	 *       REFERENCE 4FH
	 *       MISS      41H
	 */

	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_BROADWELL_X:
		/* On BDW the hit event counts references, not hits */
		perf_hit_attr.config = X86_CONFIG(.event = 0x2e,
						  .umask = 0x4f);
		perf_miss_attr.config = X86_CONFIG(.event = 0x2e,
						   .umask = 0x41);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	measure_residency_fn(&perf_miss_attr, &perf_hit_attr, plr, &counts);
	/*
	 * If a failure prevented the measurements from succeeding
	 * tracepoपूर्णांकs will still be written and all counts will be zero.
	 */

	counts.miss_after -= counts.miss_beक्रमe;
	अगर (boot_cpu_data.x86_model == INTEL_FAM6_BROADWELL_X) अणु
		/*
		 * On BDW references and misses are counted, need to adjust.
		 * Someबार the "hits" counter is a bit more than the
		 * references, क्रम example, x references but x + 1 hits.
		 * To not report invalid hit values in this हाल we treat
		 * that as misses equal to references.
		 */
		/* First compute the number of cache references measured */
		counts.hits_after -= counts.hits_beक्रमe;
		/* Next convert references to cache hits */
		counts.hits_after -= min(counts.miss_after, counts.hits_after);
	पूर्ण अन्यथा अणु
		counts.hits_after -= counts.hits_beक्रमe;
	पूर्ण

	trace_pseuकरो_lock_l3(counts.hits_after, counts.miss_after);
out:
	plr->thपढ़ो_करोne = 1;
	wake_up_पूर्णांकerruptible(&plr->lock_thपढ़ो_wq);
	वापस 0;
पूर्ण

/**
 * pseuकरो_lock_measure_cycles - Trigger latency measure to pseuकरो-locked region
 *
 * The measurement of latency to access a pseuकरो-locked region should be
 * करोne from a cpu that is associated with that pseuकरो-locked region.
 * Determine which cpu is associated with this region and start a thपढ़ो on
 * that cpu to perक्रमm the measurement, रुको क्रम that thपढ़ो to complete.
 *
 * Return: 0 on success, <0 on failure
 */
अटल पूर्णांक pseuकरो_lock_measure_cycles(काष्ठा rdtgroup *rdtgrp, पूर्णांक sel)
अणु
	काष्ठा pseuकरो_lock_region *plr = rdtgrp->plr;
	काष्ठा task_काष्ठा *thपढ़ो;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret = -1;

	cpus_पढ़ो_lock();
	mutex_lock(&rdtgroup_mutex);

	अगर (rdtgrp->flags & RDT_DELETED) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!plr->d) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	plr->thपढ़ो_करोne = 0;
	cpu = cpumask_first(&plr->d->cpu_mask);
	अगर (!cpu_online(cpu)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	plr->cpu = cpu;

	अगर (sel == 1)
		thपढ़ो = kthपढ़ो_create_on_node(measure_cycles_lat_fn, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	अन्यथा अगर (sel == 2)
		thपढ़ो = kthपढ़ो_create_on_node(measure_l2_residency, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	अन्यथा अगर (sel == 3)
		thपढ़ो = kthपढ़ो_create_on_node(measure_l3_residency, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	अन्यथा
		जाओ out;

	अगर (IS_ERR(thपढ़ो)) अणु
		ret = PTR_ERR(thपढ़ो);
		जाओ out;
	पूर्ण
	kthपढ़ो_bind(thपढ़ो, cpu);
	wake_up_process(thपढ़ो);

	ret = रुको_event_पूर्णांकerruptible(plr->lock_thपढ़ो_wq,
				       plr->thपढ़ो_करोne == 1);
	अगर (ret < 0)
		जाओ out;

	ret = 0;

out:
	mutex_unlock(&rdtgroup_mutex);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pseuकरो_lock_measure_trigger(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rdtgroup *rdtgrp = file->निजी_data;
	माप_प्रकार buf_size;
	अक्षर buf[32];
	पूर्णांक ret;
	पूर्णांक sel;

	buf_size = min(count, (माप(buf) - 1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';
	ret = kstrtoपूर्णांक(buf, 10, &sel);
	अगर (ret == 0) अणु
		अगर (sel != 1 && sel != 2 && sel != 3)
			वापस -EINVAL;
		ret = debugfs_file_get(file->f_path.dentry);
		अगर (ret)
			वापस ret;
		ret = pseuकरो_lock_measure_cycles(rdtgrp, sel);
		अगर (ret == 0)
			ret = count;
		debugfs_file_put(file->f_path.dentry);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations pseuकरो_measure_fops = अणु
	.ग_लिखो = pseuकरो_lock_measure_trigger,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

/**
 * rdtgroup_pseuकरो_lock_create - Create a pseuकरो-locked region
 * @rdtgrp: resource group to which pseuकरो-lock region beदीर्घs
 *
 * Called when a resource group in the pseuकरो-locksetup mode receives a
 * valid schemata that should be pseuकरो-locked. Since the resource group is
 * in pseuकरो-locksetup mode the &काष्ठा pseuकरो_lock_region has alपढ़ोy been
 * allocated and initialized with the essential inक्रमmation. If a failure
 * occurs the resource group reमुख्यs in the pseuकरो-locksetup mode with the
 * &काष्ठा pseuकरो_lock_region associated with it, but cleared from all
 * inक्रमmation and पढ़ोy क्रम the user to re-attempt pseuकरो-locking by
 * writing the schemata again.
 *
 * Return: 0 अगर the pseuकरो-locked region was successfully pseuकरो-locked, <0
 * on failure. Descriptive error will be written to last_cmd_status buffer.
 */
पूर्णांक rdtgroup_pseuकरो_lock_create(काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा pseuकरो_lock_region *plr = rdtgrp->plr;
	काष्ठा task_काष्ठा *thपढ़ो;
	अचिन्हित पूर्णांक new_minor;
	काष्ठा device *dev;
	पूर्णांक ret;

	ret = pseuकरो_lock_region_alloc(plr);
	अगर (ret < 0)
		वापस ret;

	ret = pseuकरो_lock_cstates_स्थिरrain(plr);
	अगर (ret < 0) अणु
		ret = -EINVAL;
		जाओ out_region;
	पूर्ण

	plr->thपढ़ो_करोne = 0;

	thपढ़ो = kthपढ़ो_create_on_node(pseuकरो_lock_fn, rdtgrp,
					cpu_to_node(plr->cpu),
					"pseudo_lock/%u", plr->cpu);
	अगर (IS_ERR(thपढ़ो)) अणु
		ret = PTR_ERR(thपढ़ो);
		rdt_last_cmd_म_लिखो("Locking thread returned error %d\n", ret);
		जाओ out_cstates;
	पूर्ण

	kthपढ़ो_bind(thपढ़ो, plr->cpu);
	wake_up_process(thपढ़ो);

	ret = रुको_event_पूर्णांकerruptible(plr->lock_thपढ़ो_wq,
				       plr->thपढ़ो_करोne == 1);
	अगर (ret < 0) अणु
		/*
		 * If the thपढ़ो करोes not get on the CPU क्रम whatever
		 * reason and the process which sets up the region is
		 * पूर्णांकerrupted then this will leave the thपढ़ो in runnable
		 * state and once it माला_लो on the CPU it will dereference
		 * the cleared, but not मुक्तd, plr काष्ठा resulting in an
		 * empty pseuकरो-locking loop.
		 */
		rdt_last_cmd_माला_दो("Locking thread interrupted\n");
		जाओ out_cstates;
	पूर्ण

	ret = pseuकरो_lock_minor_get(&new_minor);
	अगर (ret < 0) अणु
		rdt_last_cmd_माला_दो("Unable to obtain a new minor number\n");
		जाओ out_cstates;
	पूर्ण

	/*
	 * Unlock access but करो not release the reference. The
	 * pseuकरो-locked region will still be here on वापस.
	 *
	 * The mutex has to be released temporarily to aव्योम a potential
	 * deadlock with the mm->mmap_lock which is obtained in the
	 * device_create() and debugfs_create_dir() callpath below as well as
	 * beक्रमe the mmap() callback is called.
	 */
	mutex_unlock(&rdtgroup_mutex);

	अगर (!IS_ERR_OR_शून्य(debugfs_resctrl)) अणु
		plr->debugfs_dir = debugfs_create_dir(rdtgrp->kn->name,
						      debugfs_resctrl);
		अगर (!IS_ERR_OR_शून्य(plr->debugfs_dir))
			debugfs_create_file("pseudo_lock_measure", 0200,
					    plr->debugfs_dir, rdtgrp,
					    &pseuकरो_measure_fops);
	पूर्ण

	dev = device_create(pseuकरो_lock_class, शून्य,
			    MKDEV(pseuकरो_lock_major, new_minor),
			    rdtgrp, "%s", rdtgrp->kn->name);

	mutex_lock(&rdtgroup_mutex);

	अगर (IS_ERR(dev)) अणु
		ret = PTR_ERR(dev);
		rdt_last_cmd_म_लिखो("Failed to create character device: %d\n",
				    ret);
		जाओ out_debugfs;
	पूर्ण

	/* We released the mutex - check अगर group was हटाओd जबतक we did so */
	अगर (rdtgrp->flags & RDT_DELETED) अणु
		ret = -ENODEV;
		जाओ out_device;
	पूर्ण

	plr->minor = new_minor;

	rdtgrp->mode = RDT_MODE_PSEUDO_LOCKED;
	closid_मुक्त(rdtgrp->closid);
	rdtgroup_kn_mode_restore(rdtgrp, "cpus", 0444);
	rdtgroup_kn_mode_restore(rdtgrp, "cpus_list", 0444);

	ret = 0;
	जाओ out;

out_device:
	device_destroy(pseuकरो_lock_class, MKDEV(pseuकरो_lock_major, new_minor));
out_debugfs:
	debugfs_हटाओ_recursive(plr->debugfs_dir);
	pseuकरो_lock_minor_release(new_minor);
out_cstates:
	pseuकरो_lock_cstates_relax(plr);
out_region:
	pseuकरो_lock_region_clear(plr);
out:
	वापस ret;
पूर्ण

/**
 * rdtgroup_pseuकरो_lock_हटाओ - Remove a pseuकरो-locked region
 * @rdtgrp: resource group to which the pseuकरो-locked region beदीर्घs
 *
 * The removal of a pseuकरो-locked region can be initiated when the resource
 * group is हटाओd from user space via a "rmdir" from userspace or the
 * unmount of the resctrl fileप्रणाली. On removal the resource group करोes
 * not go back to pseuकरो-locksetup mode beक्रमe it is हटाओd, instead it is
 * हटाओd directly. There is thus asymmetry with the creation where the
 * &काष्ठा pseuकरो_lock_region is हटाओd here जबतक it was not created in
 * rdtgroup_pseuकरो_lock_create().
 *
 * Return: व्योम
 */
व्योम rdtgroup_pseuकरो_lock_हटाओ(काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा pseuकरो_lock_region *plr = rdtgrp->plr;

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
		/*
		 * Default group cannot be a pseuकरो-locked region so we can
		 * मुक्त closid here.
		 */
		closid_मुक्त(rdtgrp->closid);
		जाओ मुक्त;
	पूर्ण

	pseuकरो_lock_cstates_relax(plr);
	debugfs_हटाओ_recursive(rdtgrp->plr->debugfs_dir);
	device_destroy(pseuकरो_lock_class, MKDEV(pseuकरो_lock_major, plr->minor));
	pseuकरो_lock_minor_release(plr->minor);

मुक्त:
	pseuकरो_lock_मुक्त(rdtgrp);
पूर्ण

अटल पूर्णांक pseuकरो_lock_dev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rdtgroup *rdtgrp;

	mutex_lock(&rdtgroup_mutex);

	rdtgrp = region_find_by_minor(iminor(inode));
	अगर (!rdtgrp) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENODEV;
	पूर्ण

	filp->निजी_data = rdtgrp;
	atomic_inc(&rdtgrp->रुकोcount);
	/* Perक्रमm a non-seekable खोलो - llseek is not supported */
	filp->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);

	mutex_unlock(&rdtgroup_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pseuकरो_lock_dev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rdtgroup *rdtgrp;

	mutex_lock(&rdtgroup_mutex);
	rdtgrp = filp->निजी_data;
	WARN_ON(!rdtgrp);
	अगर (!rdtgrp) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENODEV;
	पूर्ण
	filp->निजी_data = शून्य;
	atomic_dec(&rdtgrp->रुकोcount);
	mutex_unlock(&rdtgroup_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pseuकरो_lock_dev_mremap(काष्ठा vm_area_काष्ठा *area)
अणु
	/* Not supported */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा pseuकरो_mmap_ops = अणु
	.mremap = pseuकरो_lock_dev_mremap,
पूर्ण;

अटल पूर्णांक pseuकरो_lock_dev_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vsize = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ off = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा pseuकरो_lock_region *plr;
	काष्ठा rdtgroup *rdtgrp;
	अचिन्हित दीर्घ physical;
	अचिन्हित दीर्घ psize;

	mutex_lock(&rdtgroup_mutex);

	rdtgrp = filp->निजी_data;
	WARN_ON(!rdtgrp);
	अगर (!rdtgrp) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENODEV;
	पूर्ण

	plr = rdtgrp->plr;

	अगर (!plr->d) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Task is required to run with affinity to the cpus associated
	 * with the pseuकरो-locked region. If this is not the हाल the task
	 * may be scheduled अन्यथाwhere and invalidate entries in the
	 * pseuकरो-locked region.
	 */
	अगर (!cpumask_subset(current->cpus_ptr, &plr->d->cpu_mask)) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -EINVAL;
	पूर्ण

	physical = __pa(plr->kmem) >> PAGE_SHIFT;
	psize = plr->size - off;

	अगर (off > plr->size) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENOSPC;
	पूर्ण

	/*
	 * Ensure changes are carried directly to the memory being mapped,
	 * करो not allow copy-on-ग_लिखो mapping.
	 */
	अगर (!(vma->vm_flags & VM_SHARED)) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (vsize > psize) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -ENOSPC;
	पूर्ण

	स_रखो(plr->kmem + off, 0, vsize);

	अगर (remap_pfn_range(vma, vma->vm_start, physical + vma->vm_pgoff,
			    vsize, vma->vm_page_prot)) अणु
		mutex_unlock(&rdtgroup_mutex);
		वापस -EAGAIN;
	पूर्ण
	vma->vm_ops = &pseuकरो_mmap_ops;
	mutex_unlock(&rdtgroup_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations pseuकरो_lock_dev_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.पढ़ो =		शून्य,
	.ग_लिखो =	शून्य,
	.खोलो =		pseuकरो_lock_dev_खोलो,
	.release =	pseuकरो_lock_dev_release,
	.mmap =		pseuकरो_lock_dev_mmap,
पूर्ण;

अटल अक्षर *pseuकरो_lock_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	काष्ठा rdtgroup *rdtgrp;

	rdtgrp = dev_get_drvdata(dev);
	अगर (mode)
		*mode = 0600;
	वापस kaप्र_लिखो(GFP_KERNEL, "pseudo_lock/%s", rdtgrp->kn->name);
पूर्ण

पूर्णांक rdt_pseuकरो_lock_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_chrdev(0, "pseudo_lock", &pseuकरो_lock_dev_fops);
	अगर (ret < 0)
		वापस ret;

	pseuकरो_lock_major = ret;

	pseuकरो_lock_class = class_create(THIS_MODULE, "pseudo_lock");
	अगर (IS_ERR(pseuकरो_lock_class)) अणु
		ret = PTR_ERR(pseuकरो_lock_class);
		unरेजिस्टर_chrdev(pseuकरो_lock_major, "pseudo_lock");
		वापस ret;
	पूर्ण

	pseuकरो_lock_class->devnode = pseuकरो_lock_devnode;
	वापस 0;
पूर्ण

व्योम rdt_pseuकरो_lock_release(व्योम)
अणु
	class_destroy(pseuकरो_lock_class);
	pseuकरो_lock_class = शून्य;
	unरेजिस्टर_chrdev(pseuकरो_lock_major, "pseudo_lock");
	pseuकरो_lock_major = 0;
पूर्ण
