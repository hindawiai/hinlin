<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/pm-cps.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/smp-cps.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uयंत्र.h>

अटल bool thपढ़ोs_disabled;
अटल DECLARE_BITMAP(core_घातer, NR_CPUS);

काष्ठा core_boot_config *mips_cps_core_bootcfg;

अटल पूर्णांक __init setup_nothपढ़ोs(अक्षर *s)
अणु
	thपढ़ोs_disabled = true;
	वापस 0;
पूर्ण
early_param("nothreads", setup_nothपढ़ोs);

अटल अचिन्हित core_vpe_count(अचिन्हित पूर्णांक cluster, अचिन्हित core)
अणु
	अगर (thपढ़ोs_disabled)
		वापस 1;

	वापस mips_cps_numvps(cluster, core);
पूर्ण

अटल व्योम __init cps_smp_setup(व्योम)
अणु
	अचिन्हित पूर्णांक nclusters, ncores, nvpes, core_vpes;
	अचिन्हित दीर्घ core_entry;
	पूर्णांक cl, c, v;

	/* Detect & record VPE topology */
	nvpes = 0;
	nclusters = mips_cps_numclusters();
	pr_info("%s topology ", cpu_has_mips_r6 ? "VP" : "VPE");
	क्रम (cl = 0; cl < nclusters; cl++) अणु
		अगर (cl > 0)
			pr_cont(",");
		pr_cont("{");

		ncores = mips_cps_numcores(cl);
		क्रम (c = 0; c < ncores; c++) अणु
			core_vpes = core_vpe_count(cl, c);

			अगर (c > 0)
				pr_cont(",");
			pr_cont("%u", core_vpes);

			/* Use the number of VPEs in cluster 0 core 0 क्रम smp_num_siblings */
			अगर (!cl && !c)
				smp_num_siblings = core_vpes;

			क्रम (v = 0; v < min_t(पूर्णांक, core_vpes, NR_CPUS - nvpes); v++) अणु
				cpu_set_cluster(&cpu_data[nvpes + v], cl);
				cpu_set_core(&cpu_data[nvpes + v], c);
				cpu_set_vpe_id(&cpu_data[nvpes + v], v);
			पूर्ण

			nvpes += core_vpes;
		पूर्ण

		pr_cont("}");
	पूर्ण
	pr_cont(" total %u\n", nvpes);

	/* Indicate present CPUs (CPU being synonymous with VPE) */
	क्रम (v = 0; v < min_t(अचिन्हित, nvpes, NR_CPUS); v++) अणु
		set_cpu_possible(v, cpu_cluster(&cpu_data[v]) == 0);
		set_cpu_present(v, cpu_cluster(&cpu_data[v]) == 0);
		__cpu_number_map[v] = v;
		__cpu_logical_map[v] = v;
	पूर्ण

	/* Set a coherent शेष CCA (CWB) */
	change_c0_config(CONF_CM_CMASK, 0x5);

	/* Core 0 is घातered up (we're running on it) */
	biपंचांगap_set(core_घातer, 0, 1);

	/* Initialise core 0 */
	mips_cps_core_init();

	/* Make core 0 coherent with everything */
	ग_लिखो_gcr_cl_coherence(0xff);

	अगर (mips_cm_revision() >= CM_REV_CM3) अणु
		core_entry = CKSEG1ADDR((अचिन्हित दीर्घ)mips_cps_core_entry);
		ग_लिखो_gcr_bev_base(core_entry);
	पूर्ण

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	/* If we have an FPU, enroll ourselves in the FPU-full mask */
	अगर (cpu_has_fpu)
		cpumask_set_cpu(0, &mt_fpu_cpumask);
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */
पूर्ण

अटल व्योम __init cps_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित ncores, core_vpes, c, cca;
	bool cca_unsuitable, cores_limited;
	u32 *entry_code;

	mips_mt_set_cpuoptions();

	/* Detect whether the CCA is unsuited to multi-core SMP */
	cca = पढ़ो_c0_config() & CONF_CM_CMASK;
	चयन (cca) अणु
	हाल 0x4: /* CWBE */
	हाल 0x5: /* CWB */
		/* The CCA is coherent, multi-core is fine */
		cca_unsuitable = false;
		अवरोध;

	शेष:
		/* CCA is not coherent, multi-core is not usable */
		cca_unsuitable = true;
	पूर्ण

	/* Warn the user अगर the CCA prevents multi-core */
	cores_limited = false;
	अगर (cca_unsuitable || cpu_has_dc_aliases) अणु
		क्रम_each_present_cpu(c) अणु
			अगर (cpus_are_siblings(smp_processor_id(), c))
				जारी;

			set_cpu_present(c, false);
			cores_limited = true;
		पूर्ण
	पूर्ण
	अगर (cores_limited)
		pr_warn("Using only one core due to %s%s%s\n",
			cca_unsuitable ? "unsuitable CCA" : "",
			(cca_unsuitable && cpu_has_dc_aliases) ? " & " : "",
			cpu_has_dc_aliases ? "dcache aliasing" : "");

	/*
	 * Patch the start of mips_cps_core_entry to provide:
	 *
	 * s0 = kseg0 CCA
	 */
	entry_code = (u32 *)&mips_cps_core_entry;
	uयंत्र_i_addiu(&entry_code, 16, 0, cca);
	blast_dcache_range((अचिन्हित दीर्घ)&mips_cps_core_entry,
			   (अचिन्हित दीर्घ)entry_code);
	bc_wback_inv((अचिन्हित दीर्घ)&mips_cps_core_entry,
		     (व्योम *)entry_code - (व्योम *)&mips_cps_core_entry);
	__sync();

	/* Allocate core boot configuration काष्ठाs */
	ncores = mips_cps_numcores(0);
	mips_cps_core_bootcfg = kसुस्मृति(ncores, माप(*mips_cps_core_bootcfg),
					GFP_KERNEL);
	अगर (!mips_cps_core_bootcfg) अणु
		pr_err("Failed to allocate boot config for %u cores\n", ncores);
		जाओ err_out;
	पूर्ण

	/* Allocate VPE boot configuration काष्ठाs */
	क्रम (c = 0; c < ncores; c++) अणु
		core_vpes = core_vpe_count(0, c);
		mips_cps_core_bootcfg[c].vpe_config = kसुस्मृति(core_vpes,
				माप(*mips_cps_core_bootcfg[c].vpe_config),
				GFP_KERNEL);
		अगर (!mips_cps_core_bootcfg[c].vpe_config) अणु
			pr_err("Failed to allocate %u VPE boot configs\n",
			       core_vpes);
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Mark this CPU as booted */
	atomic_set(&mips_cps_core_bootcfg[cpu_core(&current_cpu_data)].vpe_mask,
		   1 << cpu_vpe_id(&current_cpu_data));

	वापस;
err_out:
	/* Clean up allocations */
	अगर (mips_cps_core_bootcfg) अणु
		क्रम (c = 0; c < ncores; c++)
			kमुक्त(mips_cps_core_bootcfg[c].vpe_config);
		kमुक्त(mips_cps_core_bootcfg);
		mips_cps_core_bootcfg = शून्य;
	पूर्ण

	/* Effectively disable SMP by declaring CPUs not present */
	क्रम_each_possible_cpu(c) अणु
		अगर (c == 0)
			जारी;
		set_cpu_present(c, false);
	पूर्ण
पूर्ण

अटल व्योम boot_core(अचिन्हित पूर्णांक core, अचिन्हित पूर्णांक vpe_id)
अणु
	u32 stat, seq_state;
	अचिन्हित समयout;

	/* Select the appropriate core */
	mips_cm_lock_other(0, core, 0, CM_GCR_Cx_OTHER_BLOCK_LOCAL);

	/* Set its reset vector */
	ग_लिखो_gcr_co_reset_base(CKSEG1ADDR((अचिन्हित दीर्घ)mips_cps_core_entry));

	/* Ensure its coherency is disabled */
	ग_लिखो_gcr_co_coherence(0);

	/* Start it with the legacy memory map and exception base */
	ग_लिखो_gcr_co_reset_ext_base(CM_GCR_Cx_RESET_EXT_BASE_UEB);

	/* Ensure the core can access the GCRs */
	set_gcr_access(1 << core);

	अगर (mips_cpc_present()) अणु
		/* Reset the core */
		mips_cpc_lock_other(core);

		अगर (mips_cm_revision() >= CM_REV_CM3) अणु
			/* Run only the requested VP following the reset */
			ग_लिखो_cpc_co_vp_stop(0xf);
			ग_लिखो_cpc_co_vp_run(1 << vpe_id);

			/*
			 * Ensure that the VP_RUN रेजिस्टर is written beक्रमe the
			 * core leaves reset.
			 */
			wmb();
		पूर्ण

		ग_लिखो_cpc_co_cmd(CPC_Cx_CMD_RESET);

		समयout = 100;
		जबतक (true) अणु
			stat = पढ़ो_cpc_co_stat_conf();
			seq_state = stat & CPC_Cx_STAT_CONF_SEQSTATE;
			seq_state >>= __ffs(CPC_Cx_STAT_CONF_SEQSTATE);

			/* U6 == coherent execution, ie. the core is up */
			अगर (seq_state == CPC_Cx_STAT_CONF_SEQSTATE_U6)
				अवरोध;

			/* Delay a little जबतक beक्रमe we start warning */
			अगर (समयout) अणु
				समयout--;
				mdelay(10);
				जारी;
			पूर्ण

			pr_warn("Waiting for core %u to start... STAT_CONF=0x%x\n",
				core, stat);
			mdelay(1000);
		पूर्ण

		mips_cpc_unlock_other();
	पूर्ण अन्यथा अणु
		/* Take the core out of reset */
		ग_लिखो_gcr_co_reset_release(0);
	पूर्ण

	mips_cm_unlock_other();

	/* The core is now घातered up */
	biपंचांगap_set(core_घातer, core, 1);
पूर्ण

अटल व्योम remote_vpe_boot(व्योम *dummy)
अणु
	अचिन्हित core = cpu_core(&current_cpu_data);
	काष्ठा core_boot_config *core_cfg = &mips_cps_core_bootcfg[core];

	mips_cps_boot_vpes(core_cfg, cpu_vpe_id(&current_cpu_data));
पूर्ण

अटल पूर्णांक cps_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित core = cpu_core(&cpu_data[cpu]);
	अचिन्हित vpe_id = cpu_vpe_id(&cpu_data[cpu]);
	काष्ठा core_boot_config *core_cfg = &mips_cps_core_bootcfg[core];
	काष्ठा vpe_boot_config *vpe_cfg = &core_cfg->vpe_config[vpe_id];
	अचिन्हित दीर्घ core_entry;
	अचिन्हित पूर्णांक remote;
	पूर्णांक err;

	/* We करोn't yet support booting CPUs in other clusters */
	अगर (cpu_cluster(&cpu_data[cpu]) != cpu_cluster(&raw_current_cpu_data))
		वापस -ENOSYS;

	vpe_cfg->pc = (अचिन्हित दीर्घ)&smp_bootstrap;
	vpe_cfg->sp = __KSTK_TOS(idle);
	vpe_cfg->gp = (अचिन्हित दीर्घ)task_thपढ़ो_info(idle);

	atomic_or(1 << cpu_vpe_id(&cpu_data[cpu]), &core_cfg->vpe_mask);

	preempt_disable();

	अगर (!test_bit(core, core_घातer)) अणु
		/* Boot a VPE on a घातered करोwn core */
		boot_core(core, vpe_id);
		जाओ out;
	पूर्ण

	अगर (cpu_has_vp) अणु
		mips_cm_lock_other(0, core, vpe_id, CM_GCR_Cx_OTHER_BLOCK_LOCAL);
		core_entry = CKSEG1ADDR((अचिन्हित दीर्घ)mips_cps_core_entry);
		ग_लिखो_gcr_co_reset_base(core_entry);
		mips_cm_unlock_other();
	पूर्ण

	अगर (!cpus_are_siblings(cpu, smp_processor_id())) अणु
		/* Boot a VPE on another घातered up core */
		क्रम (remote = 0; remote < NR_CPUS; remote++) अणु
			अगर (!cpus_are_siblings(cpu, remote))
				जारी;
			अगर (cpu_online(remote))
				अवरोध;
		पूर्ण
		अगर (remote >= NR_CPUS) अणु
			pr_crit("No online CPU in core %u to start CPU%d\n",
				core, cpu);
			जाओ out;
		पूर्ण

		err = smp_call_function_single(remote, remote_vpe_boot,
					       शून्य, 1);
		अगर (err)
			panic("Failed to call remote CPU\n");
		जाओ out;
	पूर्ण

	BUG_ON(!cpu_has_mipsmt && !cpu_has_vp);

	/* Boot a VPE on this core */
	mips_cps_boot_vpes(core_cfg, vpe_id);
out:
	preempt_enable();
	वापस 0;
पूर्ण

अटल व्योम cps_init_secondary(व्योम)
अणु
	/* Disable MT - we only want to run 1 TC per VPE */
	अगर (cpu_has_mipsmt)
		dmt();

	अगर (mips_cm_revision() >= CM_REV_CM3) अणु
		अचिन्हित पूर्णांक ident = पढ़ो_gic_vl_ident();

		/*
		 * Ensure that our calculation of the VP ID matches up with
		 * what the GIC reports, otherwise we'll have configured
		 * पूर्णांकerrupts incorrectly.
		 */
		BUG_ON(ident != mips_cm_vp_id(smp_processor_id()));
	पूर्ण

	अगर (cpu_has_veic)
		clear_c0_status(ST0_IM);
	अन्यथा
		change_c0_status(ST0_IM, STATUSF_IP2 | STATUSF_IP3 |
					 STATUSF_IP4 | STATUSF_IP5 |
					 STATUSF_IP6 | STATUSF_IP7);
पूर्ण

अटल व्योम cps_smp_finish(व्योम)
अणु
	ग_लिखो_c0_compare(पढ़ो_c0_count() + (8 * mips_hpt_frequency / HZ));

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	/* If we have an FPU, enroll ourselves in the FPU-full mask */
	अगर (cpu_has_fpu)
		cpumask_set_cpu(smp_processor_id(), &mt_fpu_cpumask);
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */

	local_irq_enable();
पूर्ण

#अगर defined(CONFIG_HOTPLUG_CPU) || defined(CONFIG_KEXEC)

क्रमागत cpu_death अणु
	CPU_DEATH_HALT,
	CPU_DEATH_POWER,
पूर्ण;

अटल व्योम cps_shutकरोwn_this_cpu(क्रमागत cpu_death death)
अणु
	अचिन्हित पूर्णांक cpu, core, vpe_id;

	cpu = smp_processor_id();
	core = cpu_core(&cpu_data[cpu]);

	अगर (death == CPU_DEATH_HALT) अणु
		vpe_id = cpu_vpe_id(&cpu_data[cpu]);

		pr_debug("Halting core %d VP%d\n", core, vpe_id);
		अगर (cpu_has_mipsmt) अणु
			/* Halt this TC */
			ग_लिखो_c0_tchalt(TCHALT_H);
			inकाष्ठाion_hazard();
		पूर्ण अन्यथा अगर (cpu_has_vp) अणु
			ग_लिखो_cpc_cl_vp_stop(1 << vpe_id);

			/* Ensure that the VP_STOP रेजिस्टर is written */
			wmb();
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("Gating power to core %d\n", core);
		/* Power करोwn the core */
		cps_pm_enter_state(CPS_PM_POWER_GATED);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KEXEC

अटल व्योम cps_kexec_nonboot_cpu(व्योम)
अणु
	अगर (cpu_has_mipsmt || cpu_has_vp)
		cps_shutकरोwn_this_cpu(CPU_DEATH_HALT);
	अन्यथा
		cps_shutकरोwn_this_cpu(CPU_DEATH_POWER);
पूर्ण

#पूर्ण_अगर /* CONFIG_KEXEC */

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU || CONFIG_KEXEC */

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक cps_cpu_disable(व्योम)
अणु
	अचिन्हित cpu = smp_processor_id();
	काष्ठा core_boot_config *core_cfg;

	अगर (!cps_pm_support_state(CPS_PM_POWER_GATED))
		वापस -EINVAL;

	core_cfg = &mips_cps_core_bootcfg[cpu_core(&current_cpu_data)];
	atomic_sub(1 << cpu_vpe_id(&current_cpu_data), &core_cfg->vpe_mask);
	smp_mb__after_atomic();
	set_cpu_online(cpu, false);
	calculate_cpu_क्रमeign_map();
	irq_migrate_all_off_this_cpu();

	वापस 0;
पूर्ण

अटल अचिन्हित cpu_death_sibling;
अटल क्रमागत cpu_death cpu_death;

व्योम play_dead(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	local_irq_disable();
	idle_task_निकास();
	cpu = smp_processor_id();
	cpu_death = CPU_DEATH_POWER;

	pr_debug("CPU%d going offline\n", cpu);

	अगर (cpu_has_mipsmt || cpu_has_vp) अणु
		/* Look क्रम another online VPE within the core */
		क्रम_each_online_cpu(cpu_death_sibling) अणु
			अगर (!cpus_are_siblings(cpu, cpu_death_sibling))
				जारी;

			/*
			 * There is an online VPE within the core. Just halt
			 * this TC and leave the core alone.
			 */
			cpu_death = CPU_DEATH_HALT;
			अवरोध;
		पूर्ण
	पूर्ण

	/* This CPU has chosen its way out */
	(व्योम)cpu_report_death();

	cps_shutकरोwn_this_cpu(cpu_death);

	/* This should never be reached */
	panic("Failed to offline CPU %u", cpu);
पूर्ण

अटल व्योम रुको_क्रम_sibling_halt(व्योम *ptr_cpu)
अणु
	अचिन्हित cpu = (अचिन्हित दीर्घ)ptr_cpu;
	अचिन्हित vpe_id = cpu_vpe_id(&cpu_data[cpu]);
	अचिन्हित halted;
	अचिन्हित दीर्घ flags;

	करो अणु
		local_irq_save(flags);
		settc(vpe_id);
		halted = पढ़ो_tc_c0_tchalt();
		local_irq_restore(flags);
	पूर्ण जबतक (!(halted & TCHALT_H));
पूर्ण

अटल व्योम cps_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित core = cpu_core(&cpu_data[cpu]);
	अचिन्हित पूर्णांक vpe_id = cpu_vpe_id(&cpu_data[cpu]);
	kसमय_प्रकार fail_समय;
	अचिन्हित stat;
	पूर्णांक err;

	/* Wait क्रम the cpu to choose its way out */
	अगर (!cpu_रुको_death(cpu, 5)) अणु
		pr_err("CPU%u: didn't offline\n", cpu);
		वापस;
	पूर्ण

	/*
	 * Now रुको क्रम the CPU to actually offline. Without करोing this that
	 * offlining may race with one or more of:
	 *
	 *   - Onlining the CPU again.
	 *   - Powering करोwn the core अगर another VPE within it is offlined.
	 *   - A sibling VPE entering a non-coherent state.
	 *
	 * In the non-MT halt हाल (ie. infinite loop) the CPU is करोing nothing
	 * with which we could race, so करो nothing.
	 */
	अगर (cpu_death == CPU_DEATH_POWER) अणु
		/*
		 * Wait क्रम the core to enter a घातered करोwn or घड़ी gated
		 * state, the latter happening when a JTAG probe is connected
		 * in which हाल the CPC will refuse to घातer करोwn the core.
		 */
		fail_समय = kसमय_add_ms(kसमय_get(), 2000);
		करो अणु
			mips_cm_lock_other(0, core, 0, CM_GCR_Cx_OTHER_BLOCK_LOCAL);
			mips_cpc_lock_other(core);
			stat = पढ़ो_cpc_co_stat_conf();
			stat &= CPC_Cx_STAT_CONF_SEQSTATE;
			stat >>= __ffs(CPC_Cx_STAT_CONF_SEQSTATE);
			mips_cpc_unlock_other();
			mips_cm_unlock_other();

			अगर (stat == CPC_Cx_STAT_CONF_SEQSTATE_D0 ||
			    stat == CPC_Cx_STAT_CONF_SEQSTATE_D2 ||
			    stat == CPC_Cx_STAT_CONF_SEQSTATE_U2)
				अवरोध;

			/*
			 * The core ought to have घातered करोwn, but didn't &
			 * now we करोn't really know what state it's in. It's
			 * likely that its _pwr_up pin has been wired to logic
			 * 1 & it घातered back up as soon as we घातered it
			 * करोwn...
			 *
			 * The best we can करो is warn the user & जारी in
			 * the hope that the core is करोing nothing harmful &
			 * might behave properly अगर we online it later.
			 */
			अगर (WARN(kसमय_after(kसमय_get(), fail_समय),
				 "CPU%u hasn't powered down, seq. state %u\n",
				 cpu, stat))
				अवरोध;
		पूर्ण जबतक (1);

		/* Indicate the core is घातered off */
		biपंचांगap_clear(core_घातer, core, 1);
	पूर्ण अन्यथा अगर (cpu_has_mipsmt) अणु
		/*
		 * Have a CPU with access to the offlined CPUs रेजिस्टरs रुको
		 * क्रम its TC to halt.
		 */
		err = smp_call_function_single(cpu_death_sibling,
					       रुको_क्रम_sibling_halt,
					       (व्योम *)(अचिन्हित दीर्घ)cpu, 1);
		अगर (err)
			panic("Failed to call remote sibling CPU\n");
	पूर्ण अन्यथा अगर (cpu_has_vp) अणु
		करो अणु
			mips_cm_lock_other(0, core, vpe_id, CM_GCR_Cx_OTHER_BLOCK_LOCAL);
			stat = पढ़ो_cpc_co_vp_running();
			mips_cm_unlock_other();
		पूर्ण जबतक (stat & (1 << vpe_id));
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल स्थिर काष्ठा plat_smp_ops cps_smp_ops = अणु
	.smp_setup		= cps_smp_setup,
	.prepare_cpus		= cps_prepare_cpus,
	.boot_secondary		= cps_boot_secondary,
	.init_secondary		= cps_init_secondary,
	.smp_finish		= cps_smp_finish,
	.send_ipi_single	= mips_smp_send_ipi_single,
	.send_ipi_mask		= mips_smp_send_ipi_mask,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= cps_cpu_disable,
	.cpu_die		= cps_cpu_die,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	.kexec_nonboot_cpu	= cps_kexec_nonboot_cpu,
#पूर्ण_अगर
पूर्ण;

bool mips_cps_smp_in_use(व्योम)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;
	वापस mp_ops == &cps_smp_ops;
पूर्ण

पूर्णांक रेजिस्टर_cps_smp_ops(व्योम)
अणु
	अगर (!mips_cm_present()) अणु
		pr_warn("MIPS CPS SMP unable to proceed without a CM\n");
		वापस -ENODEV;
	पूर्ण

	/* check we have a GIC - we need one क्रम IPIs */
	अगर (!(पढ़ो_gcr_gic_status() & CM_GCR_GIC_STATUS_EX)) अणु
		pr_warn("MIPS CPS SMP unable to proceed without a GIC\n");
		वापस -ENODEV;
	पूर्ण

	रेजिस्टर_smp_ops(&cps_smp_ops);
	वापस 0;
पूर्ण
