<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 
 * Common boot and setup code.
 *
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/initrd.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ioport.h>
#समावेश <linux/console.h>
#समावेश <linux/utsname.h>
#समावेश <linux/tty.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/unistd.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pci.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/memory.h>
#समावेश <linux/nmi.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/dt_cpu_ftrs.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/serial.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/xmon.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/livepatch.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/feature-fixups.h>
#समावेश <यंत्र/kup.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/यंत्र-prototypes.h>

#समावेश "setup.h"

पूर्णांक spinning_secondaries;
u64 ppc64_pft_size;

काष्ठा ppc64_caches ppc64_caches = अणु
	.l1d = अणु
		.block_size = 0x40,
		.log_block_size = 6,
	पूर्ण,
	.l1i = अणु
		.block_size = 0x40,
		.log_block_size = 6
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(ppc64_caches);

#अगर defined(CONFIG_PPC_BOOK3E) && defined(CONFIG_SMP)
व्योम __init setup_tlb_core_data(व्योम)
अणु
	पूर्णांक cpu;

	BUILD_BUG_ON(दुरत्व(काष्ठा tlb_core_data, lock) != 0);

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक first = cpu_first_thपढ़ो_sibling(cpu);

		/*
		 * If we boot via kdump on a non-primary thपढ़ो,
		 * make sure we poपूर्णांक at the thपढ़ो that actually
		 * set up this TLB.
		 */
		अगर (cpu_first_thपढ़ो_sibling(boot_cpuid) == first)
			first = boot_cpuid;

		paca_ptrs[cpu]->tcd_ptr = &paca_ptrs[first]->tcd;

		/*
		 * If we have thपढ़ोs, we need either tlbsrx.
		 * or e6500 tablewalk mode, or अन्यथा TLB handlers
		 * will be racy and could produce duplicate entries.
		 * Should we panic instead?
		 */
		WARN_ONCE(smt_enabled_at_boot >= 2 &&
			  !mmu_has_feature(MMU_FTR_USE_TLBRSRV) &&
			  book3e_htw_mode != PPC_HTW_E6500,
			  "%s: unsupported MMU configuration\n", __func__);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

अटल अक्षर *smt_enabled_cmdline;

/* Look क्रम ibm,smt-enabled OF option */
व्योम __init check_smt_enabled(व्योम)
अणु
	काष्ठा device_node *dn;
	स्थिर अक्षर *smt_option;

	/* Default to enabling all thपढ़ोs */
	smt_enabled_at_boot = thपढ़ोs_per_core;

	/* Allow the command line to overrule the OF option */
	अगर (smt_enabled_cmdline) अणु
		अगर (!म_भेद(smt_enabled_cmdline, "on"))
			smt_enabled_at_boot = thपढ़ोs_per_core;
		अन्यथा अगर (!म_भेद(smt_enabled_cmdline, "off"))
			smt_enabled_at_boot = 0;
		अन्यथा अणु
			पूर्णांक smt;
			पूर्णांक rc;

			rc = kstrtoपूर्णांक(smt_enabled_cmdline, 10, &smt);
			अगर (!rc)
				smt_enabled_at_boot =
					min(thपढ़ोs_per_core, smt);
		पूर्ण
	पूर्ण अन्यथा अणु
		dn = of_find_node_by_path("/options");
		अगर (dn) अणु
			smt_option = of_get_property(dn, "ibm,smt-enabled",
						     शून्य);

			अगर (smt_option) अणु
				अगर (!म_भेद(smt_option, "on"))
					smt_enabled_at_boot = thपढ़ोs_per_core;
				अन्यथा अगर (!म_भेद(smt_option, "off"))
					smt_enabled_at_boot = 0;
			पूर्ण

			of_node_put(dn);
		पूर्ण
	पूर्ण
पूर्ण

/* Look क्रम smt-enabled= cmdline option */
अटल पूर्णांक __init early_smt_enabled(अक्षर *p)
अणु
	smt_enabled_cmdline = p;
	वापस 0;
पूर्ण
early_param("smt-enabled", early_smt_enabled);

#पूर्ण_अगर /* CONFIG_SMP */

/** Fix up paca fields required क्रम the boot cpu */
अटल व्योम __init fixup_boot_paca(व्योम)
अणु
	/* The boot cpu is started */
	get_paca()->cpu_start = 1;
	/* Allow percpu accesses to work until we setup percpu data */
	get_paca()->data_offset = 0;
	/* Mark पूर्णांकerrupts disabled in PACA */
	irq_soft_mask_set(IRQS_DISABLED);
पूर्ण

अटल व्योम __init configure_exceptions(व्योम)
अणु
	/*
	 * Setup the trampolines from the lowmem exception vectors
	 * to the kdump kernel when not using a relocatable kernel.
	 */
	setup_kdump_trampoline();

	/* Under a PAPR hypervisor, we need hypercalls */
	अगर (firmware_has_feature(FW_FEATURE_SET_MODE)) अणु
		/* Enable AIL अगर possible */
		अगर (!pseries_enable_reloc_on_exc()) अणु
			init_task.thपढ़ो.fscr &= ~FSCR_SCV;
			cur_cpu_spec->cpu_user_features2 &= ~PPC_FEATURE2_SCV;
		पूर्ण

		/*
		 * Tell the hypervisor that we want our exceptions to
		 * be taken in little endian mode.
		 *
		 * We करोn't call this क्रम big endian as our calling convention
		 * makes us always enter in BE, and the call may fail under
		 * some circumstances with kdump.
		 */
#अगर_घोषित __LITTLE_ENDIAN__
		pseries_little_endian_exceptions();
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* Set endian mode using OPAL */
		अगर (firmware_has_feature(FW_FEATURE_OPAL))
			opal_configure_cores();

		/* AIL on native is करोne in cpu_पढ़ोy_क्रम_पूर्णांकerrupts() */
	पूर्ण
पूर्ण

अटल व्योम cpu_पढ़ोy_क्रम_पूर्णांकerrupts(व्योम)
अणु
	/*
	 * Enable AIL अगर supported, and we are in hypervisor mode. This
	 * is called once क्रम every processor.
	 *
	 * If we are not in hypervisor mode the job is करोne once क्रम
	 * the whole partition in configure_exceptions().
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		अचिन्हित दीर्घ lpcr = mfspr(SPRN_LPCR);
		अचिन्हित दीर्घ new_lpcr = lpcr;

		अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			/* P10 DD1 करोes not have HAIL */
			अगर (pvr_version_is(PVR_POWER10) &&
					(mfspr(SPRN_PVR) & 0xf00) == 0x100)
				new_lpcr |= LPCR_AIL_3;
			अन्यथा
				new_lpcr |= LPCR_HAIL;
		पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
			new_lpcr |= LPCR_AIL_3;
		पूर्ण

		अगर (new_lpcr != lpcr)
			mtspr(SPRN_LPCR, new_lpcr);
	पूर्ण

	/*
	 * Set HFSCR:TM based on CPU features:
	 * In the special हाल of TM no suspend (P9N DD2.1), Linux is
	 * told TM is off via the dt-ftrs but told to (partially) use
	 * it via OPAL_REINIT_CPUS_TM_SUSPEND_DISABLED. So HFSCR[TM]
	 * will be off from dt-ftrs but we need to turn it on क्रम the
	 * no suspend हाल.
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		अगर (cpu_has_feature(CPU_FTR_TM_COMP))
			mtspr(SPRN_HFSCR, mfspr(SPRN_HFSCR) | HFSCR_TM);
		अन्यथा
			mtspr(SPRN_HFSCR, mfspr(SPRN_HFSCR) & ~HFSCR_TM);
	पूर्ण

	/* Set IR and DR in PACA MSR */
	get_paca()->kernel_msr = MSR_KERNEL;
पूर्ण

अचिन्हित दीर्घ spr_शेष_dscr = 0;

अटल व्योम __init record_spr_शेषs(व्योम)
अणु
	अगर (early_cpu_has_feature(CPU_FTR_DSCR))
		spr_शेष_dscr = mfspr(SPRN_DSCR);
पूर्ण

/*
 * Early initialization entry poपूर्णांक. This is called by head.S
 * with MMU translation disabled. We rely on the "feature" of
 * the CPU that ignores the top 2 bits of the address in real
 * mode so we can access kernel globals normally provided we
 * only toy with things in the RMO region. From here, we करो
 * some early parsing of the device-tree to setup out MEMBLOCK
 * data काष्ठाures, and allocate & initialize the hash table
 * and segment tables so we can start running with translation
 * enabled.
 *
 * It is this function which will call the probe() callback of
 * the various platक्रमm types and copy the matching one to the
 * global ppc_md काष्ठाure. Your platक्रमm can eventually करो
 * some very early initializations from the probe() routine, but
 * this is not recommended, be very careful as, क्रम example, the
 * device-tree is not accessible via normal means at this poपूर्णांक.
 */

व्योम __init early_setup(अचिन्हित दीर्घ dt_ptr)
अणु
	अटल __initdata काष्ठा paca_काष्ठा boot_paca;

	/* -------- prपूर्णांकk is _NOT_ safe to use here ! ------- */

	/*
	 * Assume we're on cpu 0 क्रम now.
	 *
	 * We need to load a PACA very early क्रम a few reasons.
	 *
	 * The stack protector canary is stored in the paca, so as soon as we
	 * call any stack रक्षित code we need r13 poपूर्णांकing somewhere valid.
	 *
	 * If we are using kcov it will call in_task() in its instrumentation,
	 * which relies on the current task from the PACA.
	 *
	 * dt_cpu_ftrs_init() calls पूर्णांकo generic OF/fdt code, as well as
	 * prपूर्णांकk(), which can trigger both stack protector and kcov.
	 *
	 * percpu variables and spin locks also use the paca.
	 *
	 * So set up a temporary paca. It will be replaced below once we know
	 * what CPU we are on.
	 */
	initialise_paca(&boot_paca, 0);
	setup_paca(&boot_paca);
	fixup_boot_paca();

	/* -------- prपूर्णांकk is now safe to use ------- */

	/* Try new device tree based feature discovery ... */
	अगर (!dt_cpu_ftrs_init(__va(dt_ptr)))
		/* Otherwise use the old style CPU table */
		identअगरy_cpu(0, mfspr(SPRN_PVR));

	/* Enable early debugging अगर any specअगरied (see udbg.h) */
	udbg_early_init();

	udbg_म_लिखो(" -> %s(), dt_ptr: 0x%lx\n", __func__, dt_ptr);

	/*
	 * Do early initialization using the flattened device
	 * tree, such as retrieving the physical memory map or
	 * calculating/retrieving the hash table size.
	 */
	early_init_devtree(__va(dt_ptr));

	/* Now we know the logical id of our boot cpu, setup the paca. */
	अगर (boot_cpuid != 0) अणु
		/* Poison paca_ptrs[0] again अगर it's not the boot cpu */
		स_रखो(&paca_ptrs[0], 0x88, माप(paca_ptrs[0]));
	पूर्ण
	setup_paca(paca_ptrs[boot_cpuid]);
	fixup_boot_paca();

	/*
	 * Configure exception handlers. This include setting up trampolines
	 * अगर needed, setting exception endian mode, etc...
	 */
	configure_exceptions();

	/*
	 * Configure Kernel Userspace Protection. This needs to happen beक्रमe
	 * feature fixups क्रम platक्रमms that implement this using features.
	 */
	setup_kup();

	/* Apply all the dynamic patching */
	apply_feature_fixups();
	setup_feature_keys();

	/* Initialize the hash table or TLB handling */
	early_init_mmu();

	early_ioremap_setup();

	/*
	 * After firmware and early platक्रमm setup code has set things up,
	 * we note the SPR values क्रम configurable control/perक्रमmance
	 * रेजिस्टरs, and use those as initial शेषs.
	 */
	record_spr_शेषs();

	/*
	 * At this poपूर्णांक, we can let पूर्णांकerrupts चयन to भव mode
	 * (the MMU has been setup), so adjust the MSR in the PACA to
	 * have IR and DR set and enable AIL अगर it exists
	 */
	cpu_पढ़ोy_क्रम_पूर्णांकerrupts();

	/*
	 * We enable ftrace here, but since we only support DYNAMIC_FTRACE, it
	 * will only actually get enabled on the boot cpu much later once
	 * ftrace itself has been initialized.
	 */
	this_cpu_enable_ftrace();

	udbg_म_लिखो(" <- %s()\n", __func__);

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_BOOTX
	/*
	 * This needs to be करोne *last* (after the above udbg_म_लिखो() even)
	 *
	 * Right after we वापस from this function, we turn on the MMU
	 * which means the real-mode access trick that btext करोes will
	 * no दीर्घer work, it needs to चयन to using a real MMU
	 * mapping. This call will ensure that it करोes
	 */
	btext_map();
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_BOOTX */
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम early_setup_secondary(व्योम)
अणु
	/* Mark पूर्णांकerrupts disabled in PACA */
	irq_soft_mask_set(IRQS_DISABLED);

	/* Initialize the hash table or TLB handling */
	early_init_mmu_secondary();

	/* Perक्रमm any KUP setup that is per-cpu */
	setup_kup();

	/*
	 * At this poपूर्णांक, we can let पूर्णांकerrupts चयन to भव mode
	 * (the MMU has been setup), so adjust the MSR in the PACA to
	 * have IR and DR set.
	 */
	cpu_पढ़ोy_क्रम_पूर्णांकerrupts();
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

व्योम panic_smp_self_stop(व्योम)
अणु
	hard_irq_disable();
	spin_begin();
	जबतक (1)
		spin_cpu_relax();
पूर्ण

#अगर defined(CONFIG_SMP) || defined(CONFIG_KEXEC_CORE)
अटल bool use_spinloop(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S)) अणु
		/*
		 * See comments in head_64.S -- not all platक्रमms insert
		 * secondaries at __secondary_hold and रुको at the spin
		 * loop.
		 */
		अगर (firmware_has_feature(FW_FEATURE_OPAL))
			वापस false;
		वापस true;
	पूर्ण

	/*
	 * When book3e boots from kexec, the ePAPR spin table करोes
	 * not get used.
	 */
	वापस of_property_पढ़ो_bool(of_chosen, "linux,booted-from-kexec");
पूर्ण

व्योम smp_release_cpus(व्योम)
अणु
	अचिन्हित दीर्घ *ptr;
	पूर्णांक i;

	अगर (!use_spinloop())
		वापस;

	/* All secondary cpus are spinning on a common spinloop, release them
	 * all now so they can start to spin on their inभागidual paca
	 * spinloops. For non SMP kernels, the secondary cpus never get out
	 * of the common spinloop.
	 */

	ptr  = (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)&__secondary_hold_spinloop
			- PHYSICAL_START);
	*ptr = ppc_function_entry(generic_secondary_smp_init);

	/* And रुको a bit क्रम them to catch up */
	क्रम (i = 0; i < 100000; i++) अणु
		mb();
		HMT_low();
		अगर (spinning_secondaries == 0)
			अवरोध;
		udelay(1);
	पूर्ण
	pr_debug("spinning_secondaries = %d\n", spinning_secondaries);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP || CONFIG_KEXEC_CORE */

/*
 * Initialize some reमुख्यing members of the ppc64_caches and प्रणालीcfg
 * काष्ठाures
 * (at least until we get rid of them completely). This is mostly some
 * cache inक्रमmations about the CPU that will be used by cache flush
 * routines and/or provided to userland
 */

अटल व्योम init_cache_info(काष्ठा ppc_cache_info *info, u32 size, u32 lsize,
			    u32 bsize, u32 sets)
अणु
	info->size = size;
	info->sets = sets;
	info->line_size = lsize;
	info->block_size = bsize;
	info->log_block_size = __ilog2(bsize);
	अगर (bsize)
		info->blocks_per_page = PAGE_SIZE / bsize;
	अन्यथा
		info->blocks_per_page = 0;

	अगर (sets == 0)
		info->assoc = 0xffff;
	अन्यथा
		info->assoc = size / (sets * lsize);
पूर्ण

अटल bool __init parse_cache_info(काष्ठा device_node *np,
				    bool icache,
				    काष्ठा ppc_cache_info *info)
अणु
	अटल स्थिर अक्षर *ipropnames[] __initdata = अणु
		"i-cache-size",
		"i-cache-sets",
		"i-cache-block-size",
		"i-cache-line-size",
	पूर्ण;
	अटल स्थिर अक्षर *dpropnames[] __initdata = अणु
		"d-cache-size",
		"d-cache-sets",
		"d-cache-block-size",
		"d-cache-line-size",
	पूर्ण;
	स्थिर अक्षर **propnames = icache ? ipropnames : dpropnames;
	स्थिर __be32 *sizep, *lsizep, *bsizep, *setsp;
	u32 size, lsize, bsize, sets;
	bool success = true;

	size = 0;
	sets = -1u;
	lsize = bsize = cur_cpu_spec->dcache_bsize;
	sizep = of_get_property(np, propnames[0], शून्य);
	अगर (sizep != शून्य)
		size = be32_to_cpu(*sizep);
	setsp = of_get_property(np, propnames[1], शून्य);
	अगर (setsp != शून्य)
		sets = be32_to_cpu(*setsp);
	bsizep = of_get_property(np, propnames[2], शून्य);
	lsizep = of_get_property(np, propnames[3], शून्य);
	अगर (bsizep == शून्य)
		bsizep = lsizep;
	अगर (lsizep == शून्य)
		lsizep = bsizep;
	अगर (lsizep != शून्य)
		lsize = be32_to_cpu(*lsizep);
	अगर (bsizep != शून्य)
		bsize = be32_to_cpu(*bsizep);
	अगर (sizep == शून्य || bsizep == शून्य || lsizep == शून्य)
		success = false;

	/*
	 * OF is weird .. it represents fully associative caches
	 * as "1 way" which करोesn't make much sense and doesn't
	 * leave room क्रम direct mapped. We'll assume that 0
	 * in OF means direct mapped क्रम that reason.
	 */
	अगर (sets == 1)
		sets = 0;
	अन्यथा अगर (sets == 0)
		sets = 1;

	init_cache_info(info, size, lsize, bsize, sets);

	वापस success;
पूर्ण

व्योम __init initialize_cache_info(व्योम)
अणु
	काष्ठा device_node *cpu = शून्य, *l2, *l3 = शून्य;
	u32 pvr;

	/*
	 * All shipping POWER8 machines have a firmware bug that
	 * माला_दो incorrect inक्रमmation in the device-tree. This will
	 * be (hopefully) fixed क्रम future chips but क्रम now hard
	 * code the values अगर we are running on one of these
	 */
	pvr = PVR_VER(mfspr(SPRN_PVR));
	अगर (pvr == PVR_POWER8 || pvr == PVR_POWER8E ||
	    pvr == PVR_POWER8NVL) अणु
						/* size    lsize   blk  sets */
		init_cache_info(&ppc64_caches.l1i, 0x8000,   128,  128, 32);
		init_cache_info(&ppc64_caches.l1d, 0x10000,  128,  128, 64);
		init_cache_info(&ppc64_caches.l2,  0x80000,  128,  0,   512);
		init_cache_info(&ppc64_caches.l3,  0x800000, 128,  0,   8192);
	पूर्ण अन्यथा
		cpu = of_find_node_by_type(शून्य, "cpu");

	/*
	 * We're assuming *all* of the CPUs have the same
	 * d-cache and i-cache sizes... -Peter
	 */
	अगर (cpu) अणु
		अगर (!parse_cache_info(cpu, false, &ppc64_caches.l1d))
			pr_warn("Argh, can't find dcache properties !\n");

		अगर (!parse_cache_info(cpu, true, &ppc64_caches.l1i))
			pr_warn("Argh, can't find icache properties !\n");

		/*
		 * Try to find the L2 and L3 अगर any. Assume they are
		 * unअगरied and use the D-side properties.
		 */
		l2 = of_find_next_cache_node(cpu);
		of_node_put(cpu);
		अगर (l2) अणु
			parse_cache_info(l2, false, &ppc64_caches.l2);
			l3 = of_find_next_cache_node(l2);
			of_node_put(l2);
		पूर्ण
		अगर (l3) अणु
			parse_cache_info(l3, false, &ppc64_caches.l3);
			of_node_put(l3);
		पूर्ण
	पूर्ण

	/* For use by binfmt_elf */
	dcache_bsize = ppc64_caches.l1d.block_size;
	icache_bsize = ppc64_caches.l1i.block_size;

	cur_cpu_spec->dcache_bsize = dcache_bsize;
	cur_cpu_spec->icache_bsize = icache_bsize;
पूर्ण

/*
 * This वापसs the limit below which memory accesses to the linear
 * mapping are guarnateed not to cause an architectural exception (e.g.,
 * TLB or SLB miss fault).
 *
 * This is used to allocate PACAs and various पूर्णांकerrupt stacks that
 * that are accessed early in पूर्णांकerrupt handlers that must not cause
 * re-entrant पूर्णांकerrupts.
 */
__init u64 ppc64_bolted_size(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3E
	/* Freescale BookE bolts the entire linear mapping */
	/* XXX: BookE ppc64_rma_limit setup seems to disagree? */
	अगर (early_mmu_has_feature(MMU_FTR_TYPE_FSL_E))
		वापस linear_map_top;
	/* Other BookE, we assume the first GB is bolted */
	वापस 1ul << 30;
#अन्यथा
	/* BookS radix, करोes not take faults on linear mapping */
	अगर (early_radix_enabled())
		वापस अच_दीर्घ_उच्च;

	/* BookS hash, the first segment is bolted */
	अगर (early_mmu_has_feature(MMU_FTR_1T_SEGMENT))
		वापस 1UL << SID_SHIFT_1T;
	वापस 1UL << SID_SHIFT;
#पूर्ण_अगर
पूर्ण

अटल व्योम *__init alloc_stack(अचिन्हित दीर्घ limit, पूर्णांक cpu)
अणु
	व्योम *ptr;

	BUILD_BUG_ON(STACK_INT_FRAME_SIZE % 16);

	ptr = memblock_alloc_try_nid(THREAD_SIZE, THREAD_ALIGN,
				     MEMBLOCK_LOW_LIMIT, limit,
				     early_cpu_to_node(cpu));
	अगर (!ptr)
		panic("cannot allocate stacks");

	वापस ptr;
पूर्ण

व्योम __init irqstack_early_init(व्योम)
अणु
	u64 limit = ppc64_bolted_size();
	अचिन्हित पूर्णांक i;

	/*
	 * Interrupt stacks must be in the first segment since we
	 * cannot afक्रमd to take SLB misses on them. They are not
	 * accessed in realmode.
	 */
	क्रम_each_possible_cpu(i) अणु
		softirq_ctx[i] = alloc_stack(limit, i);
		hardirq_ctx[i] = alloc_stack(limit, i);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3E
व्योम __init exc_lvl_early_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		व्योम *sp;

		sp = alloc_stack(अच_दीर्घ_उच्च, i);
		critirq_ctx[i] = sp;
		paca_ptrs[i]->crit_kstack = sp + THREAD_SIZE;

		sp = alloc_stack(अच_दीर्घ_उच्च, i);
		dbgirq_ctx[i] = sp;
		paca_ptrs[i]->dbg_kstack = sp + THREAD_SIZE;

		sp = alloc_stack(अच_दीर्घ_उच्च, i);
		mcheckirq_ctx[i] = sp;
		paca_ptrs[i]->mc_kstack = sp + THREAD_SIZE;
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_DEBUG_LVL_EXC))
		patch_exception(0x040, exc_debug_debug_book3e);
पूर्ण
#पूर्ण_अगर

/*
 * Stack space used when we detect a bad kernel stack poपूर्णांकer, and
 * early in SMP boots beक्रमe relocation is enabled. Exclusive emergency
 * stack क्रम machine checks.
 */
व्योम __init emergency_stack_init(व्योम)
अणु
	u64 limit, mce_limit;
	अचिन्हित पूर्णांक i;

	/*
	 * Emergency stacks must be under 256MB, we cannot afक्रमd to take
	 * SLB misses on them. The ABI also requires them to be 128-byte
	 * aligned.
	 *
	 * Since we use these as temporary stacks during secondary CPU
	 * bringup, machine check, प्रणाली reset, and HMI, we need to get
	 * at them in real mode. This means they must also be within the RMO
	 * region.
	 *
	 * The IRQ stacks allocated अन्यथाwhere in this file are zeroed and
	 * initialized in kernel/irq.c. These are initialized here in order
	 * to have emergency stacks available as early as possible.
	 */
	limit = mce_limit = min(ppc64_bolted_size(), ppc64_rma_size);

	/*
	 * Machine check on pseries calls rtas, but can't use the अटल
	 * rtas_args due to a machine check hitting जबतक the lock is held.
	 * rtas args have to be under 4GB, so the machine check stack is
	 * limited to 4GB so args can be put on stack.
	 */
	अगर (firmware_has_feature(FW_FEATURE_LPAR) && mce_limit > SZ_4G)
		mce_limit = SZ_4G;

	क्रम_each_possible_cpu(i) अणु
		paca_ptrs[i]->emergency_sp = alloc_stack(limit, i) + THREAD_SIZE;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
		/* emergency stack क्रम NMI exception handling. */
		paca_ptrs[i]->nmi_emergency_sp = alloc_stack(limit, i) + THREAD_SIZE;

		/* emergency stack क्रम machine check exception handling. */
		paca_ptrs[i]->mc_emergency_sp = alloc_stack(mce_limit, i) + THREAD_SIZE;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
/**
 * pcpu_alloc_booपंचांगem - NUMA मित्रly alloc_booपंचांगem wrapper क्रम percpu
 * @cpu: cpu to allocate क्रम
 * @size: size allocation in bytes
 * @align: alignment
 *
 * Allocate @size bytes aligned at @align क्रम cpu @cpu.  This wrapper
 * करोes the right thing क्रम NUMA regardless of the current
 * configuration.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
अटल व्योम * __init pcpu_alloc_booपंचांगem(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
					माप_प्रकार align)
अणु
	स्थिर अचिन्हित दीर्घ goal = __pa(MAX_DMA_ADDRESS);
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक node = early_cpu_to_node(cpu);
	व्योम *ptr;

	अगर (!node_online(node) || !NODE_DATA(node)) अणु
		ptr = memblock_alloc_from(size, align, goal);
		pr_info("cpu %d has no node %d or node-local memory\n",
			cpu, node);
		pr_debug("per cpu data for cpu%d %lu bytes at %016lx\n",
			 cpu, size, __pa(ptr));
	पूर्ण अन्यथा अणु
		ptr = memblock_alloc_try_nid(size, align, goal,
					     MEMBLOCK_ALLOC_ACCESSIBLE, node);
		pr_debug("per cpu data for cpu%d %lu bytes on node%d at "
			 "%016lx\n", cpu, size, node, __pa(ptr));
	पूर्ण
	वापस ptr;
#अन्यथा
	वापस memblock_alloc_from(size, align, goal);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init pcpu_मुक्त_booपंचांगem(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त(__pa(ptr), size);
पूर्ण

अटल पूर्णांक pcpu_cpu_distance(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अगर (early_cpu_to_node(from) == early_cpu_to_node(to))
		वापस LOCAL_DISTANCE;
	अन्यथा
		वापस REMOTE_DISTANCE;
पूर्ण

अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(__per_cpu_offset);

अटल व्योम __init pcpu_populate_pte(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd = pgd_offset_k(addr);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d)) अणु
		pud_t *new;

		new = memblock_alloc(PUD_TABLE_SIZE, PUD_TABLE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		p4d_populate(&init_mm, p4d, new);
	पूर्ण

	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud)) अणु
		pmd_t *new;

		new = memblock_alloc(PMD_TABLE_SIZE, PMD_TABLE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		pud_populate(&init_mm, pud, new);
	पूर्ण

	pmd = pmd_offset(pud, addr);
	अगर (!pmd_present(*pmd)) अणु
		pte_t *new;

		new = memblock_alloc(PTE_TABLE_SIZE, PTE_TABLE_SIZE);
		अगर (!new)
			जाओ err_alloc;
		pmd_populate_kernel(&init_mm, pmd, new);
	पूर्ण

	वापस;

err_alloc:
	panic("%s: Failed to allocate %lu bytes align=%lx from=%lx\n",
	      __func__, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
पूर्ण


व्योम __init setup_per_cpu_areas(व्योम)
अणु
	स्थिर माप_प्रकार dyn_size = PERCPU_MODULE_RESERVE + PERCPU_DYNAMIC_RESERVE;
	माप_प्रकार atom_size;
	अचिन्हित दीर्घ delta;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc = -EINVAL;

	/*
	 * Linear mapping is one of 4K, 1M and 16M.  For 4K, no need
	 * to group units.  For larger mappings, use 1M atom which
	 * should be large enough to contain a number of units.
	 */
	अगर (mmu_linear_psize == MMU_PAGE_4K)
		atom_size = PAGE_SIZE;
	अन्यथा
		atom_size = 1 << 20;

	अगर (pcpu_chosen_fc != PCPU_FC_PAGE) अणु
		rc = pcpu_embed_first_chunk(0, dyn_size, atom_size, pcpu_cpu_distance,
					    pcpu_alloc_booपंचांगem, pcpu_मुक्त_booपंचांगem);
		अगर (rc)
			pr_warn("PERCPU: %s allocator failed (%d), "
				"falling back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], rc);
	पूर्ण

	अगर (rc < 0)
		rc = pcpu_page_first_chunk(0, pcpu_alloc_booपंचांगem, pcpu_मुक्त_booपंचांगem,
					   pcpu_populate_pte);
	अगर (rc < 0)
		panic("cannot initialize percpu area (err=%d)", rc);

	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu) अणु
                __per_cpu_offset[cpu] = delta + pcpu_unit_offsets[cpu];
		paca_ptrs[cpu]->data_offset = __per_cpu_offset[cpu];
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
अचिन्हित दीर्घ memory_block_size_bytes(व्योम)
अणु
	अगर (ppc_md.memory_block_size)
		वापस ppc_md.memory_block_size();

	वापस MIN_MEMORY_BLOCK_SIZE;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_INसूचीECT_PIO) || defined(CONFIG_PPC_INसूचीECT_MMIO)
काष्ठा ppc_pci_io ppc_pci_io;
EXPORT_SYMBOL(ppc_pci_io);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR_PERF
u64 hw_nmi_get_sample_period(पूर्णांक watchकरोg_thresh)
अणु
	वापस ppc_proc_freq * watchकरोg_thresh;
पूर्ण
#पूर्ण_अगर

/*
 * The perf based hardlockup detector अवरोधs PMU event based branches, so
 * disable it by शेष. Book3S has a soft-nmi hardlockup detector based
 * on the decrementer पूर्णांकerrupt, so it करोes not suffer from this problem.
 *
 * It is likely to get false positives in VM guests, so disable it there
 * by शेष too.
 */
अटल पूर्णांक __init disable_hardlockup_detector(व्योम)
अणु
#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR_PERF
	hardlockup_detector_disable();
#अन्यथा
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		hardlockup_detector_disable();
#पूर्ण_अगर

	वापस 0;
पूर्ण
early_initcall(disable_hardlockup_detector);
