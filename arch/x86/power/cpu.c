<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Suspend support specअगरic क्रम i386/x86-64.
 *
 * Copyright (c) 2007 Rafael J. Wysocki <rjw@sisk.pl>
 * Copyright (c) 2002 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2001 Patrick Mochel <mochel@osdl.org>
 */

#समावेश <linux/suspend.h>
#समावेश <linux/export.h>
#समावेश <linux/smp.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/tboot.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpu_device_id.h>

#अगर_घोषित CONFIG_X86_32
__visible अचिन्हित दीर्घ saved_context_ebx;
__visible अचिन्हित दीर्घ saved_context_esp, saved_context_ebp;
__visible अचिन्हित दीर्घ saved_context_esi, saved_context_edi;
__visible अचिन्हित दीर्घ saved_context_eflags;
#पूर्ण_अगर
काष्ठा saved_context saved_context;

अटल व्योम msr_save_context(काष्ठा saved_context *ctxt)
अणु
	काष्ठा saved_msr *msr = ctxt->saved_msrs.array;
	काष्ठा saved_msr *end = msr + ctxt->saved_msrs.num;

	जबतक (msr < end) अणु
		msr->valid = !rdmsrl_safe(msr->info.msr_no, &msr->info.reg.q);
		msr++;
	पूर्ण
पूर्ण

अटल व्योम msr_restore_context(काष्ठा saved_context *ctxt)
अणु
	काष्ठा saved_msr *msr = ctxt->saved_msrs.array;
	काष्ठा saved_msr *end = msr + ctxt->saved_msrs.num;

	जबतक (msr < end) अणु
		अगर (msr->valid)
			wrmsrl(msr->info.msr_no, msr->info.reg.q);
		msr++;
	पूर्ण
पूर्ण

/**
 *	__save_processor_state - save CPU रेजिस्टरs beक्रमe creating a
 *		hibernation image and beक्रमe restoring the memory state from it
 *	@ctxt - काष्ठाure to store the रेजिस्टरs contents in
 *
 *	NOTE: If there is a CPU रेजिस्टर the modअगरication of which by the
 *	boot kernel (ie. the kernel used क्रम loading the hibernation image)
 *	might affect the operations of the restored target kernel (ie. the one
 *	saved in the hibernation image), then its contents must be saved by this
 *	function.  In other words, अगर kernel A is hibernated and dअगरferent
 *	kernel B is used क्रम loading the hibernation image पूर्णांकo memory, the
 *	kernel A's __save_processor_state() function must save all रेजिस्टरs
 *	needed by kernel A, so that it can operate correctly after the resume
 *	regardless of what kernel B करोes in the meanसमय.
 */
अटल व्योम __save_processor_state(काष्ठा saved_context *ctxt)
अणु
#अगर_घोषित CONFIG_X86_32
	mtrr_save_fixed_ranges(शून्य);
#पूर्ण_अगर
	kernel_fpu_begin();

	/*
	 * descriptor tables
	 */
	store_idt(&ctxt->idt);

	/*
	 * We save it here, but restore it only in the hibernate हाल.
	 * For ACPI S3 resume, this is loaded via 'early_gdt_desc' in 64-bit
	 * mode in "secondary_startup_64". In 32-bit mode it is करोne via
	 * 'pmode_gdt' in wakeup_start.
	 */
	ctxt->gdt_desc.size = GDT_SIZE - 1;
	ctxt->gdt_desc.address = (अचिन्हित दीर्घ)get_cpu_gdt_rw(smp_processor_id());

	store_tr(ctxt->tr);

	/* XMM0..XMM15 should be handled by kernel_fpu_begin(). */
	/*
	 * segment रेजिस्टरs
	 */
	savesegment(gs, ctxt->gs);
#अगर_घोषित CONFIG_X86_64
	savesegment(fs, ctxt->fs);
	savesegment(ds, ctxt->ds);
	savesegment(es, ctxt->es);

	rdmsrl(MSR_FS_BASE, ctxt->fs_base);
	rdmsrl(MSR_GS_BASE, ctxt->kernelmode_gs_base);
	rdmsrl(MSR_KERNEL_GS_BASE, ctxt->usermode_gs_base);
	mtrr_save_fixed_ranges(शून्य);

	rdmsrl(MSR_EFER, ctxt->efer);
#पूर्ण_अगर

	/*
	 * control रेजिस्टरs
	 */
	ctxt->cr0 = पढ़ो_cr0();
	ctxt->cr2 = पढ़ो_cr2();
	ctxt->cr3 = __पढ़ो_cr3();
	ctxt->cr4 = __पढ़ो_cr4();
	ctxt->misc_enable_saved = !rdmsrl_safe(MSR_IA32_MISC_ENABLE,
					       &ctxt->misc_enable);
	msr_save_context(ctxt);
पूर्ण

/* Needed by apm.c */
व्योम save_processor_state(व्योम)
अणु
	__save_processor_state(&saved_context);
	x86_platक्रमm.save_sched_घड़ी_state();
पूर्ण
#अगर_घोषित CONFIG_X86_32
EXPORT_SYMBOL(save_processor_state);
#पूर्ण_अगर

अटल व्योम करो_fpu_end(व्योम)
अणु
	/*
	 * Restore FPU regs अगर necessary.
	 */
	kernel_fpu_end();
पूर्ण

अटल व्योम fix_processor_context(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
#अगर_घोषित CONFIG_X86_64
	काष्ठा desc_काष्ठा *desc = get_cpu_gdt_rw(cpu);
	tss_desc tss;
#पूर्ण_अगर

	/*
	 * We need to reload TR, which requires that we change the
	 * GDT entry to indicate "available" first.
	 *
	 * XXX: This could probably all be replaced by a call to
	 * क्रमce_reload_TR().
	 */
	set_tss_desc(cpu, &get_cpu_entry_area(cpu)->tss.x86_tss);

#अगर_घोषित CONFIG_X86_64
	स_नकल(&tss, &desc[GDT_ENTRY_TSS], माप(tss_desc));
	tss.type = 0x9; /* The available 64-bit TSS (see AMD vol 2, pg 91 */
	ग_लिखो_gdt_entry(desc, GDT_ENTRY_TSS, &tss, DESC_TSS);

	syscall_init();				/* This sets MSR_*STAR and related */
#अन्यथा
	अगर (boot_cpu_has(X86_FEATURE_SEP))
		enable_sep_cpu();
#पूर्ण_अगर
	load_TR_desc();				/* This करोes ltr */
	load_mm_ldt(current->active_mm);	/* This करोes lldt */
	initialize_tlbstate_and_flush();

	fpu__resume_cpu();

	/* The processor is back on the direct GDT, load back the fixmap */
	load_fixmap_gdt(cpu);
पूर्ण

/**
 * __restore_processor_state - restore the contents of CPU रेजिस्टरs saved
 *                             by __save_processor_state()
 * @ctxt - काष्ठाure to load the रेजिस्टरs contents from
 *
 * The यंत्र code that माला_लो us here will have restored a usable GDT, although
 * it will be poपूर्णांकing to the wrong alias.
 */
अटल व्योम notrace __restore_processor_state(काष्ठा saved_context *ctxt)
अणु
	काष्ठा cpuinfo_x86 *c;

	अगर (ctxt->misc_enable_saved)
		wrmsrl(MSR_IA32_MISC_ENABLE, ctxt->misc_enable);
	/*
	 * control रेजिस्टरs
	 */
	/* cr4 was पूर्णांकroduced in the Pentium CPU */
#अगर_घोषित CONFIG_X86_32
	अगर (ctxt->cr4)
		__ग_लिखो_cr4(ctxt->cr4);
#अन्यथा
/* CONFIG X86_64 */
	wrmsrl(MSR_EFER, ctxt->efer);
	__ग_लिखो_cr4(ctxt->cr4);
#पूर्ण_अगर
	ग_लिखो_cr3(ctxt->cr3);
	ग_लिखो_cr2(ctxt->cr2);
	ग_लिखो_cr0(ctxt->cr0);

	/* Restore the IDT. */
	load_idt(&ctxt->idt);

	/*
	 * Just in हाल the यंत्र code got us here with the SS, DS, or ES
	 * out of sync with the GDT, update them.
	 */
	loadsegment(ss, __KERNEL_DS);
	loadsegment(ds, __USER_DS);
	loadsegment(es, __USER_DS);

	/*
	 * Restore percpu access.  Percpu access can happen in exception
	 * handlers or in complicated helpers like load_gs_index().
	 */
#अगर_घोषित CONFIG_X86_64
	wrmsrl(MSR_GS_BASE, ctxt->kernelmode_gs_base);
#अन्यथा
	loadsegment(fs, __KERNEL_PERCPU);
#पूर्ण_अगर

	/* Restore the TSS, RO GDT, LDT, and usermode-relevant MSRs. */
	fix_processor_context();

	/*
	 * Now that we have descriptor tables fully restored and working
	 * exception handling, restore the usermode segments.
	 */
#अगर_घोषित CONFIG_X86_64
	loadsegment(ds, ctxt->es);
	loadsegment(es, ctxt->es);
	loadsegment(fs, ctxt->fs);
	load_gs_index(ctxt->gs);

	/*
	 * Restore FSBASE and GSBASE after restoring the selectors, since
	 * restoring the selectors clobbers the bases.  Keep in mind
	 * that MSR_KERNEL_GS_BASE is horribly misnamed.
	 */
	wrmsrl(MSR_FS_BASE, ctxt->fs_base);
	wrmsrl(MSR_KERNEL_GS_BASE, ctxt->usermode_gs_base);
#अन्यथा
	loadsegment(gs, ctxt->gs);
#पूर्ण_अगर

	करो_fpu_end();
	tsc_verअगरy_tsc_adjust(true);
	x86_platक्रमm.restore_sched_घड़ी_state();
	mtrr_bp_restore();
	perf_restore_debug_store();
	msr_restore_context(ctxt);

	c = &cpu_data(smp_processor_id());
	अगर (cpu_has(c, X86_FEATURE_MSR_IA32_FEAT_CTL))
		init_ia32_feat_ctl(c);
पूर्ण

/* Needed by apm.c */
व्योम notrace restore_processor_state(व्योम)
अणु
	__restore_processor_state(&saved_context);
पूर्ण
#अगर_घोषित CONFIG_X86_32
EXPORT_SYMBOL(restore_processor_state);
#पूर्ण_अगर

#अगर defined(CONFIG_HIBERNATION) && defined(CONFIG_HOTPLUG_CPU)
अटल व्योम resume_play_dead(व्योम)
अणु
	play_dead_common();
	tboot_shutकरोwn(TB_SHUTDOWN_WFS);
	hlt_play_dead();
पूर्ण

पूर्णांक hibernate_resume_nonboot_cpu_disable(व्योम)
अणु
	व्योम (*play_dead)(व्योम) = smp_ops.play_dead;
	पूर्णांक ret;

	/*
	 * Ensure that MONITOR/MWAIT will not be used in the "play dead" loop
	 * during hibernate image restoration, because it is likely that the
	 * monitored address will be actually written to at that समय and then
	 * the "dead" CPU will attempt to execute inकाष्ठाions again, but the
	 * address in its inकाष्ठाion poपूर्णांकer may not be possible to resolve
	 * any more at that poपूर्णांक (the page tables used by it previously may
	 * have been overwritten by hibernate image data).
	 *
	 * First, make sure that we wake up all the potentially disabled SMT
	 * thपढ़ोs which have been initially brought up and then put पूर्णांकo
	 * mरुको/cpuidle sleep.
	 * Those will be put to proper (not पूर्णांकerfering with hibernation
	 * resume) sleep afterwards, and the resumed kernel will decide itself
	 * what to करो with them.
	 */
	ret = cpuhp_smt_enable();
	अगर (ret)
		वापस ret;
	smp_ops.play_dead = resume_play_dead;
	ret = मुक्तze_secondary_cpus(0);
	smp_ops.play_dead = play_dead;
	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * When bsp_check() is called in hibernate and suspend, cpu hotplug
 * is disabled alपढ़ोy. So it's unnecessary to handle race condition between
 * cpumask query and cpu hotplug.
 */
अटल पूर्णांक bsp_check(व्योम)
अणु
	अगर (cpumask_first(cpu_online_mask) != 0) अणु
		pr_warn("CPU0 is offline.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bsp_pm_callback(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			   व्योम *ptr)
अणु
	पूर्णांक ret = 0;

	चयन (action) अणु
	हाल PM_SUSPEND_PREPARE:
	हाल PM_HIBERNATION_PREPARE:
		ret = bsp_check();
		अवरोध;
#अगर_घोषित CONFIG_DEBUG_HOTPLUG_CPU0
	हाल PM_RESTORE_PREPARE:
		/*
		 * When प्रणाली resumes from hibernation, online CPU0 because
		 * 1. it's required क्रम resume and
		 * 2. the CPU was online beक्रमe hibernation
		 */
		अगर (!cpu_online(0))
			_debug_hotplug_cpu(0, 1);
		अवरोध;
	हाल PM_POST_RESTORE:
		/*
		 * When a resume really happens, this code won't be called.
		 *
		 * This code is called only when user space hibernation software
		 * prepares क्रम snapshot device during boot समय. So we just
		 * call _debug_hotplug_cpu() to restore to CPU0's state prior to
		 * preparing the snapshot device.
		 *
		 * This works क्रम normal boot हाल in our CPU0 hotplug debug
		 * mode, i.e. CPU0 is offline and user mode hibernation
		 * software initializes during boot समय.
		 *
		 * If CPU0 is online and user application accesses snapshot
		 * device after boot समय, this will offline CPU0 and user may
		 * see dअगरferent CPU0 state beक्रमe and after accessing
		 * the snapshot device. But hopefully this is not a हाल when
		 * user debugging CPU0 hotplug. Even अगर users hit this हाल,
		 * they can easily online CPU0 back.
		 *
		 * To simplअगरy this debug code, we only consider normal boot
		 * हाल. Otherwise we need to remember CPU0's state and restore
		 * to that state and resolve racy conditions etc.
		 */
		_debug_hotplug_cpu(0, 0);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक __init bsp_pm_check_init(व्योम)
अणु
	/*
	 * Set this bsp_pm_callback as lower priority than
	 * cpu_hotplug_pm_callback. So cpu_hotplug_pm_callback will be called
	 * earlier to disable cpu hotplug beक्रमe bsp online check.
	 */
	pm_notअगरier(bsp_pm_callback, -पूर्णांक_उच्च);
	वापस 0;
पूर्ण

core_initcall(bsp_pm_check_init);

अटल पूर्णांक msr_build_context(स्थिर u32 *msr_id, स्थिर पूर्णांक num)
अणु
	काष्ठा saved_msrs *saved_msrs = &saved_context.saved_msrs;
	काष्ठा saved_msr *msr_array;
	पूर्णांक total_num;
	पूर्णांक i, j;

	total_num = saved_msrs->num + num;

	msr_array = kदो_स्मृति_array(total_num, माप(काष्ठा saved_msr), GFP_KERNEL);
	अगर (!msr_array) अणु
		pr_err("x86/pm: Can not allocate memory to save/restore MSRs during suspend.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (saved_msrs->array) अणु
		/*
		 * Multiple callbacks can invoke this function, so copy any
		 * MSR save requests from previous invocations.
		 */
		स_नकल(msr_array, saved_msrs->array,
		       माप(काष्ठा saved_msr) * saved_msrs->num);

		kमुक्त(saved_msrs->array);
	पूर्ण

	क्रम (i = saved_msrs->num, j = 0; i < total_num; i++, j++) अणु
		msr_array[i].info.msr_no	= msr_id[j];
		msr_array[i].valid		= false;
		msr_array[i].info.reg.q		= 0;
	पूर्ण
	saved_msrs->num   = total_num;
	saved_msrs->array = msr_array;

	वापस 0;
पूर्ण

/*
 * The following sections are a quirk framework क्रम problematic BIOSen:
 * Someबार MSRs are modअगरied by the BIOSen after suspended to
 * RAM, this might cause unexpected behavior after wakeup.
 * Thus we save/restore these specअगरied MSRs across suspend/resume
 * in order to work around it.
 *
 * For any further problematic BIOSen/platक्रमms,
 * please add your own function similar to msr_initialize_bdw.
 */
अटल पूर्णांक msr_initialize_bdw(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	/* Add any extra MSR ids पूर्णांकo this array. */
	u32 bdw_msr_id[] = अणु MSR_IA32_THERM_CONTROL पूर्ण;

	pr_info("x86/pm: %s detected, MSR saving is needed during suspending.\n", d->ident);
	वापस msr_build_context(bdw_msr_id, ARRAY_SIZE(bdw_msr_id));
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id msr_save_dmi_table[] = अणु
	अणु
	 .callback = msr_initialize_bdw,
	 .ident = "BROADWELL BDX_EP",
	 .matches = अणु
		DMI_MATCH(DMI_PRODUCT_NAME, "GRANTLEY"),
		DMI_MATCH(DMI_PRODUCT_VERSION, "E63448-400"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक msr_save_cpuid_features(स्थिर काष्ठा x86_cpu_id *c)
अणु
	u32 cpuid_msr_id[] = अणु
		MSR_AMD64_CPUID_FN_1,
	पूर्ण;

	pr_info("x86/pm: family %#hx cpu detected, MSR saving is needed during suspending.\n",
		c->family);

	वापस msr_build_context(cpuid_msr_id, ARRAY_SIZE(cpuid_msr_id));
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id msr_save_cpu_table[] = अणु
	X86_MATCH_VENDOR_FAM(AMD, 0x15, &msr_save_cpuid_features),
	X86_MATCH_VENDOR_FAM(AMD, 0x16, &msr_save_cpuid_features),
	अणुपूर्ण
पूर्ण;

प्रकार पूर्णांक (*pm_cpu_match_t)(स्थिर काष्ठा x86_cpu_id *);
अटल पूर्णांक pm_cpu_check(स्थिर काष्ठा x86_cpu_id *c)
अणु
	स्थिर काष्ठा x86_cpu_id *m;
	पूर्णांक ret = 0;

	m = x86_match_cpu(msr_save_cpu_table);
	अगर (m) अणु
		pm_cpu_match_t fn;

		fn = (pm_cpu_match_t)m->driver_data;
		ret = fn(m);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pm_check_save_msr(व्योम)
अणु
	dmi_check_प्रणाली(msr_save_dmi_table);
	pm_cpu_check(msr_save_cpu_table);

	वापस 0;
पूर्ण

device_initcall(pm_check_save_msr);
