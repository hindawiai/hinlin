<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV setup code.
 *
 * Copyright 2011 IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bug.h>
#समावेश <linux/pci.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/security_features.h>

#समावेश "powernv.h"


अटल bool fw_feature_is(स्थिर अक्षर *state, स्थिर अक्षर *name,
			  काष्ठा device_node *fw_features)
अणु
	काष्ठा device_node *np;
	bool rc = false;

	np = of_get_child_by_name(fw_features, name);
	अगर (np) अणु
		rc = of_property_पढ़ो_bool(np, state);
		of_node_put(np);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम init_fw_feat_flags(काष्ठा device_node *np)
अणु
	अगर (fw_feature_is("enabled", "inst-spec-barrier-ori31,31,0", np))
		security_ftr_set(SEC_FTR_SPEC_BAR_ORI31);

	अगर (fw_feature_is("enabled", "fw-bcctrl-serialized", np))
		security_ftr_set(SEC_FTR_BCCTRL_SERIALISED);

	अगर (fw_feature_is("enabled", "inst-l1d-flush-ori30,30,0", np))
		security_ftr_set(SEC_FTR_L1D_FLUSH_ORI30);

	अगर (fw_feature_is("enabled", "inst-l1d-flush-trig2", np))
		security_ftr_set(SEC_FTR_L1D_FLUSH_TRIG2);

	अगर (fw_feature_is("enabled", "fw-l1d-thread-split", np))
		security_ftr_set(SEC_FTR_L1D_THREAD_PRIV);

	अगर (fw_feature_is("enabled", "fw-count-cache-disabled", np))
		security_ftr_set(SEC_FTR_COUNT_CACHE_DISABLED);

	अगर (fw_feature_is("enabled", "fw-count-cache-flush-bcctr2,0,0", np))
		security_ftr_set(SEC_FTR_BCCTR_FLUSH_ASSIST);

	अगर (fw_feature_is("enabled", "needs-count-cache-flush-on-context-switch", np))
		security_ftr_set(SEC_FTR_FLUSH_COUNT_CACHE);

	/*
	 * The features below are enabled by शेष, so we instead look to see
	 * अगर firmware has *disabled* them, and clear them अगर so.
	 */
	अगर (fw_feature_is("disabled", "speculation-policy-favor-security", np))
		security_ftr_clear(SEC_FTR_FAVOUR_SECURITY);

	अगर (fw_feature_is("disabled", "needs-l1d-flush-msr-pr-0-to-1", np))
		security_ftr_clear(SEC_FTR_L1D_FLUSH_PR);

	अगर (fw_feature_is("disabled", "needs-l1d-flush-msr-hv-1-to-0", np))
		security_ftr_clear(SEC_FTR_L1D_FLUSH_HV);

	अगर (fw_feature_is("disabled", "needs-spec-barrier-for-bound-checks", np))
		security_ftr_clear(SEC_FTR_BNDS_CHK_SPEC_BAR);
पूर्ण

अटल व्योम pnv_setup_security_mitigations(व्योम)
अणु
	काष्ठा device_node *np, *fw_features;
	क्रमागत l1d_flush_type type;
	bool enable;

	/* Default to fallback in हाल fw-features are not available */
	type = L1D_FLUSH_FALLBACK;

	np = of_find_node_by_name(शून्य, "ibm,opal");
	fw_features = of_get_child_by_name(np, "fw-features");
	of_node_put(np);

	अगर (fw_features) अणु
		init_fw_feat_flags(fw_features);
		of_node_put(fw_features);

		अगर (security_ftr_enabled(SEC_FTR_L1D_FLUSH_TRIG2))
			type = L1D_FLUSH_MTTRIG;

		अगर (security_ftr_enabled(SEC_FTR_L1D_FLUSH_ORI30))
			type = L1D_FLUSH_ORI;
	पूर्ण

	/*
	 * If we are non-Power9 bare metal, we करोn't need to flush on kernel
	 * entry or after user access: they fix a P9 specअगरic vulnerability.
	 */
	अगर (!pvr_version_is(PVR_POWER9)) अणु
		security_ftr_clear(SEC_FTR_L1D_FLUSH_ENTRY);
		security_ftr_clear(SEC_FTR_L1D_FLUSH_UACCESS);
	पूर्ण

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) && \
		 (security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR)   || \
		  security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV));

	setup_rfi_flush(type, enable);
	setup_count_cache_flush();

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_L1D_FLUSH_ENTRY);
	setup_entry_flush(enable);

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_L1D_FLUSH_UACCESS);
	setup_uaccess_flush(enable);

	setup_stf_barrier();
पूर्ण

अटल व्योम __init pnv_check_guarded_cores(व्योम)
अणु
	काष्ठा device_node *dn;
	पूर्णांक bad_count = 0;

	क्रम_each_node_by_type(dn, "cpu") अणु
		अगर (of_property_match_string(dn, "status", "bad") >= 0)
			bad_count++;
	पूर्ण

	अगर (bad_count) अणु
		prपूर्णांकk("  _     _______________\n");
		pr_cont(" | |   /               \\\n");
		pr_cont(" | |   |    WARNING!   |\n");
		pr_cont(" | |   |               |\n");
		pr_cont(" | |   | It looks like |\n");
		pr_cont(" |_|   |  you have %*d |\n", 3, bad_count);
		pr_cont("  _    | guarded cores |\n");
		pr_cont(" (_)   \\_______________/\n");
	पूर्ण
पूर्ण

अटल व्योम __init pnv_setup_arch(व्योम)
अणु
	set_arch_panic_समयout(10, ARCH_PANIC_TIMEOUT);

	pnv_setup_security_mitigations();

	/* Initialize SMP */
	pnv_smp_init();

	/* Setup RTC and NVRAM callbacks */
	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		opal_nvram_init();

	/* Enable NAP mode */
	घातersave_nap = 1;

	pnv_check_guarded_cores();

	/* XXX PMCS */
पूर्ण

अटल व्योम __init pnv_init(व्योम)
अणु
	/*
	 * Initialize the LPC bus now so that legacy serial
	 * ports can be found on it
	 */
	opal_lpc_init();

#अगर_घोषित CONFIG_HVC_OPAL
	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		hvc_opal_init_early();
	अन्यथा
#पूर्ण_अगर
		add_preferred_console("hvc", 0, शून्य);

	अगर (!radix_enabled()) अणु
		माप_प्रकार size = माप(काष्ठा slb_entry) * mmu_slb_size;
		पूर्णांक i;

		/* Allocate per cpu area to save old slb contents during MCE */
		क्रम_each_possible_cpu(i) अणु
			paca_ptrs[i]->mce_faulty_slbs =
					memblock_alloc_node(size,
						__alignof__(काष्ठा slb_entry),
						cpu_to_node(i));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init pnv_init_IRQ(व्योम)
अणु
	/* Try using a XIVE अगर available, otherwise use a XICS */
	अगर (!xive_native_init())
		xics_init();

	WARN_ON(!ppc_md.get_irq);
पूर्ण

अटल व्योम pnv_show_cpuinfo(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model = "";

	root = of_find_node_by_path("/");
	अगर (root)
		model = of_get_property(root, "model", शून्य);
	seq_म_लिखो(m, "machine\t\t: PowerNV %s\n", model);
	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		seq_म_लिखो(m, "firmware\t: OPAL\n");
	अन्यथा
		seq_म_लिखो(m, "firmware\t: BML\n");
	of_node_put(root);
	अगर (radix_enabled())
		seq_म_लिखो(m, "MMU\t\t: Radix\n");
	अन्यथा
		seq_म_लिखो(m, "MMU\t\t: Hash\n");
पूर्ण

अटल व्योम pnv_prepare_going_करोwn(व्योम)
अणु
	/*
	 * Disable all notअगरiers from OPAL, we can't
	 * service पूर्णांकerrupts anymore anyway
	 */
	opal_event_shutकरोwn();

	/* Prपूर्णांक flash update message अगर one is scheduled. */
	opal_flash_update_prपूर्णांक_message();

	smp_send_stop();

	hard_irq_disable();
पूर्ण

अटल व्योम  __noवापस pnv_restart(अक्षर *cmd)
अणु
	दीर्घ rc;

	pnv_prepare_going_करोwn();

	करो अणु
		अगर (!cmd || !म_माप(cmd))
			rc = opal_cec_reboot();
		अन्यथा अगर (म_भेद(cmd, "full") == 0)
			rc = opal_cec_reboot2(OPAL_REBOOT_FULL_IPL, शून्य);
		अन्यथा अगर (म_भेद(cmd, "mpipl") == 0)
			rc = opal_cec_reboot2(OPAL_REBOOT_MPIPL, शून्य);
		अन्यथा अगर (म_भेद(cmd, "error") == 0)
			rc = opal_cec_reboot2(OPAL_REBOOT_PLATFORM_ERROR, शून्य);
		अन्यथा अगर (म_भेद(cmd, "fast") == 0)
			rc = opal_cec_reboot2(OPAL_REBOOT_FAST, शून्य);
		अन्यथा
			rc = OPAL_UNSUPPORTED;

		अगर (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
			/* Opal is busy रुको क्रम some समय and retry */
			opal_poll_events(शून्य);
			mdelay(10);

		पूर्ण अन्यथा	अगर (cmd && rc) अणु
			/* Unknown error जबतक issuing reboot */
			अगर (rc == OPAL_UNSUPPORTED)
				pr_err("Unsupported '%s' reboot.\n", cmd);
			अन्यथा
				pr_err("Unable to issue '%s' reboot. Err=%ld\n",
				       cmd, rc);
			pr_info("Forcing a cec-reboot\n");
			cmd = शून्य;
			rc = OPAL_BUSY;

		पूर्ण अन्यथा अगर (rc != OPAL_SUCCESS) अणु
			/* Unknown error जबतक issuing cec-reboot */
			pr_err("Unable to reboot. Err=%ld\n", rc);
		पूर्ण

	पूर्ण जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT);

	क्रम (;;)
		opal_poll_events(शून्य);
पूर्ण

अटल व्योम __noवापस pnv_घातer_off(व्योम)
अणु
	दीर्घ rc = OPAL_BUSY;

	pnv_prepare_going_करोwn();

	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_cec_घातer_करोwn(0);
		अगर (rc == OPAL_BUSY_EVENT)
			opal_poll_events(शून्य);
		अन्यथा
			mdelay(10);
	पूर्ण
	क्रम (;;)
		opal_poll_events(शून्य);
पूर्ण

अटल व्योम __noवापस pnv_halt(व्योम)
अणु
	pnv_घातer_off();
पूर्ण

अटल व्योम pnv_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
पूर्ण

अटल व्योम pnv_shutकरोwn(व्योम)
अणु
	/* Let the PCI code clear up IODA tables */
	pnv_pci_shutकरोwn();

	/*
	 * Stop OPAL activity: Unरेजिस्टर all OPAL पूर्णांकerrupts so they
	 * करोn't fire up जबतक we kexec and make sure all potentially
	 * DMA'ing ops are complete (such as dump retrieval).
	 */
	opal_shutकरोwn();
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम pnv_kexec_रुको_secondaries_करोwn(व्योम)
अणु
	पूर्णांक my_cpu, i, notअगरied = -1;

	my_cpu = get_cpu();

	क्रम_each_online_cpu(i) अणु
		uपूर्णांक8_t status;
		पूर्णांक64_t rc, समयout = 1000;

		अगर (i == my_cpu)
			जारी;

		क्रम (;;) अणु
			rc = opal_query_cpu_status(get_hard_smp_processor_id(i),
						   &status);
			अगर (rc != OPAL_SUCCESS || status != OPAL_THREAD_STARTED)
				अवरोध;
			barrier();
			अगर (i != notअगरied) अणु
				prपूर्णांकk(KERN_INFO "kexec: waiting for cpu %d "
				       "(physical %d) to enter OPAL\n",
				       i, paca_ptrs[i]->hw_cpu_id);
				notअगरied = i;
			पूर्ण

			/*
			 * On crash secondaries might be unreachable or hung,
			 * so समयout अगर we've रुकोed too दीर्घ
			 * */
			mdelay(1);
			अगर (समयout-- == 0) अणु
				prपूर्णांकk(KERN_ERR "kexec: timed out waiting for "
				       "cpu %d (physical %d) to enter OPAL\n",
				       i, paca_ptrs[i]->hw_cpu_id);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pnv_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary)
अणु
	u64 reinit_flags;

	अगर (xive_enabled())
		xive_tearकरोwn_cpu();
	अन्यथा
		xics_kexec_tearकरोwn_cpu(secondary);

	/* On OPAL, we वापस all CPUs to firmware */
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस;

	अगर (secondary) अणु
		/* Return secondary CPUs to firmware on OPAL v3 */
		mb();
		get_paca()->kexec_state = KEXEC_STATE_REAL_MODE;
		mb();

		/* Return the CPU to OPAL */
		opal_वापस_cpu();
	पूर्ण अन्यथा अणु
		/* Primary रुकोs क्रम the secondaries to have reached OPAL */
		pnv_kexec_रुको_secondaries_करोwn();

		/* Switch XIVE back to emulation mode */
		अगर (xive_enabled())
			xive_shutकरोwn();

		/*
		 * We might be running as little-endian - now that पूर्णांकerrupts
		 * are disabled, reset the HILE bit to big-endian so we करोn't
		 * take पूर्णांकerrupts in the wrong endian later
		 *
		 * We reinit to enable both radix and hash on P9 to ensure
		 * the mode used by the next kernel is always supported.
		 */
		reinit_flags = OPAL_REINIT_CPUS_HILE_BE;
		अगर (cpu_has_feature(CPU_FTR_ARCH_300))
			reinit_flags |= OPAL_REINIT_CPUS_MMU_RADIX |
				OPAL_REINIT_CPUS_MMU_HASH;
		opal_reinit_cpus(reinit_flags);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
अटल अचिन्हित दीर्घ pnv_memory_block_size(व्योम)
अणु
	/*
	 * We map the kernel linear region with 1GB large pages on radix. For
	 * memory hot unplug to work our memory block size must be at least
	 * this size.
	 */
	अगर (radix_enabled())
		वापस radix_mem_block_size;
	अन्यथा
		वापस 256UL * 1024 * 1024;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init pnv_setup_machdep_opal(व्योम)
अणु
	ppc_md.get_boot_समय = opal_get_boot_समय;
	ppc_md.restart = pnv_restart;
	pm_घातer_off = pnv_घातer_off;
	ppc_md.halt = pnv_halt;
	/* ppc_md.प्रणाली_reset_exception माला_लो filled in by pnv_smp_init() */
	ppc_md.machine_check_exception = opal_machine_check;
	ppc_md.mce_check_early_recovery = opal_mce_check_early_recovery;
	अगर (opal_check_token(OPAL_HANDLE_HMI2))
		ppc_md.hmi_exception_early = opal_hmi_exception_early2;
	अन्यथा
		ppc_md.hmi_exception_early = opal_hmi_exception_early;
	ppc_md.handle_hmi_exception = opal_handle_hmi_exception;
पूर्ण

अटल पूर्णांक __init pnv_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("ibm,powernv"))
		वापस 0;

	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		pnv_setup_machdep_opal();

	pr_debug("PowerNV detected !\n");

	pnv_init();

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
व्योम __init pnv_पंचांग_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_OPAL) ||
	    !pvr_version_is(PVR_POWER9) ||
	    early_cpu_has_feature(CPU_FTR_TM))
		वापस;

	अगर (opal_reinit_cpus(OPAL_REINIT_CPUS_TM_SUSPEND_DISABLED) != OPAL_SUCCESS)
		वापस;

	pr_info("Enabling TM (Transactional Memory) with Suspend Disabled\n");
	cur_cpu_spec->cpu_features |= CPU_FTR_TM;
	/* Make sure "normal" HTM is off (it should be) */
	cur_cpu_spec->cpu_user_features2 &= ~PPC_FEATURE2_HTM;
	/* Turn on no suspend mode, and HTM no SC */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_HTM_NO_SUSPEND | \
					    PPC_FEATURE2_HTM_NOSC;
	पंचांग_suspend_disabled = true;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

/*
 * Returns the cpu frequency क्रम 'cpu' in Hz. This is used by
 * /proc/cpuinfo
 */
अटल अचिन्हित दीर्घ pnv_get_proc_freq(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ ret_freq;

	ret_freq = cpufreq_get(cpu) * 1000ul;

	/*
	 * If the backend cpufreq driver करोes not exist,
         * then fallback to old way of reporting the घड़ीrate.
	 */
	अगर (!ret_freq)
		ret_freq = ppc_proc_freq;
	वापस ret_freq;
पूर्ण

अटल दीर्घ pnv_machine_check_early(काष्ठा pt_regs *regs)
अणु
	दीर्घ handled = 0;

	अगर (cur_cpu_spec && cur_cpu_spec->machine_check_early)
		handled = cur_cpu_spec->machine_check_early(regs);

	वापस handled;
पूर्ण

define_machine(घातernv) अणु
	.name			= "PowerNV",
	.probe			= pnv_probe,
	.setup_arch		= pnv_setup_arch,
	.init_IRQ		= pnv_init_IRQ,
	.show_cpuinfo		= pnv_show_cpuinfo,
	.get_proc_freq          = pnv_get_proc_freq,
	.discover_phbs		= pnv_pci_init,
	.progress		= pnv_progress,
	.machine_shutकरोwn	= pnv_shutकरोwn,
	.घातer_save             = शून्य,
	.calibrate_decr		= generic_calibrate_decr,
	.machine_check_early	= pnv_machine_check_early,
#अगर_घोषित CONFIG_KEXEC_CORE
	.kexec_cpu_करोwn		= pnv_kexec_cpu_करोwn,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
	.memory_block_size	= pnv_memory_block_size,
#पूर्ण_अगर
पूर्ण;
