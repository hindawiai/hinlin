<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/cpuhotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/pm.h>
#समावेश <यंत्र/pm-cps.h>
#समावेश <यंत्र/smp-cps.h>
#समावेश <यंत्र/uयंत्र.h>

/*
 * cps_nc_entry_fn - type of a generated non-coherent state entry function
 * @online: the count of online coupled VPEs
 * @nc_पढ़ोy_count: poपूर्णांकer to a non-coherent mapping of the core पढ़ोy_count
 *
 * The code entering & निकासing non-coherent states is generated at runसमय
 * using uयंत्र, in order to ensure that the compiler cannot insert a stray
 * memory access at an unक्रमtunate समय and to allow the generation of optimal
 * core-specअगरic code particularly क्रम cache routines. If coupled_coherence
 * is non-zero and this is the entry function क्रम the CPS_PM_NC_WAIT state,
 * वापसs the number of VPEs that were in the रुको state at the poपूर्णांक this
 * VPE left it. Returns garbage अगर coupled_coherence is zero or this is not
 * the entry function क्रम CPS_PM_NC_WAIT.
 */
प्रकार अचिन्हित (*cps_nc_entry_fn)(अचिन्हित online, u32 *nc_पढ़ोy_count);

/*
 * The entry poपूर्णांक of the generated non-coherent idle state entry/निकास
 * functions. Actually per-core rather than per-CPU.
 */
अटल DEFINE_PER_CPU_READ_MOSTLY(cps_nc_entry_fn[CPS_PM_STATE_COUNT],
				  nc_यंत्र_enter);

/* Biपंचांगap indicating which states are supported by the प्रणाली */
अटल DECLARE_BITMAP(state_support, CPS_PM_STATE_COUNT);

/*
 * Indicates the number of coupled VPEs पढ़ोy to operate in a non-coherent
 * state. Actually per-core rather than per-CPU.
 */
अटल DEFINE_PER_CPU_ALIGNED(u32*, पढ़ोy_count);

/* Indicates online CPUs coupled with the current CPU */
अटल DEFINE_PER_CPU_ALIGNED(cpumask_t, online_coupled);

/*
 * Used to synchronize entry to deep idle states. Actually per-core rather
 * than per-CPU.
 */
अटल DEFINE_PER_CPU_ALIGNED(atomic_t, pm_barrier);

/* Saved CPU state across the CPS_PM_POWER_GATED state */
DEFINE_PER_CPU_ALIGNED(काष्ठा mips_अटल_suspend_state, cps_cpu_state);

/* A somewhat arbitrary number of labels & relocs क्रम uयंत्र */
अटल काष्ठा uयंत्र_label labels[32];
अटल काष्ठा uयंत्र_reloc relocs[32];

क्रमागत mips_reg अणु
	zero, at, v0, v1, a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9, k0, k1, gp, sp, fp, ra,
पूर्ण;

bool cps_pm_support_state(क्रमागत cps_pm_state state)
अणु
	वापस test_bit(state, state_support);
पूर्ण

अटल व्योम coupled_barrier(atomic_t *a, अचिन्हित online)
अणु
	/*
	 * This function is effectively the same as
	 * cpuidle_coupled_parallel_barrier, which can't be used here since
	 * there's no cpuidle device.
	 */

	अगर (!coupled_coherence)
		वापस;

	smp_mb__beक्रमe_atomic();
	atomic_inc(a);

	जबतक (atomic_पढ़ो(a) < online)
		cpu_relax();

	अगर (atomic_inc_वापस(a) == online * 2) अणु
		atomic_set(a, 0);
		वापस;
	पूर्ण

	जबतक (atomic_पढ़ो(a) > online)
		cpu_relax();
पूर्ण

पूर्णांक cps_pm_enter_state(क्रमागत cps_pm_state state)
अणु
	अचिन्हित cpu = smp_processor_id();
	अचिन्हित core = cpu_core(&current_cpu_data);
	अचिन्हित online, left;
	cpumask_t *coupled_mask = this_cpu_ptr(&online_coupled);
	u32 *core_पढ़ोy_count, *nc_core_पढ़ोy_count;
	व्योम *nc_addr;
	cps_nc_entry_fn entry;
	काष्ठा core_boot_config *core_cfg;
	काष्ठा vpe_boot_config *vpe_cfg;

	/* Check that there is an entry function क्रम this state */
	entry = per_cpu(nc_यंत्र_enter, core)[state];
	अगर (!entry)
		वापस -EINVAL;

	/* Calculate which coupled CPUs (VPEs) are online */
#अगर defined(CONFIG_MIPS_MT) || defined(CONFIG_CPU_MIPSR6)
	अगर (cpu_online(cpu)) अणु
		cpumask_and(coupled_mask, cpu_online_mask,
			    &cpu_sibling_map[cpu]);
		online = cpumask_weight(coupled_mask);
		cpumask_clear_cpu(cpu, coupled_mask);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		cpumask_clear(coupled_mask);
		online = 1;
	पूर्ण

	/* Setup the VPE to run mips_cps_pm_restore when started again */
	अगर (IS_ENABLED(CONFIG_CPU_PM) && state == CPS_PM_POWER_GATED) अणु
		/* Power gating relies upon CPS SMP */
		अगर (!mips_cps_smp_in_use())
			वापस -EINVAL;

		core_cfg = &mips_cps_core_bootcfg[core];
		vpe_cfg = &core_cfg->vpe_config[cpu_vpe_id(&current_cpu_data)];
		vpe_cfg->pc = (अचिन्हित दीर्घ)mips_cps_pm_restore;
		vpe_cfg->gp = (अचिन्हित दीर्घ)current_thपढ़ो_info();
		vpe_cfg->sp = 0;
	पूर्ण

	/* Indicate that this CPU might not be coherent */
	cpumask_clear_cpu(cpu, &cpu_coherent_mask);
	smp_mb__after_atomic();

	/* Create a non-coherent mapping of the core पढ़ोy_count */
	core_पढ़ोy_count = per_cpu(पढ़ोy_count, core);
	nc_addr = kmap_noncoherent(virt_to_page(core_पढ़ोy_count),
				   (अचिन्हित दीर्घ)core_पढ़ोy_count);
	nc_addr += ((अचिन्हित दीर्घ)core_पढ़ोy_count & ~PAGE_MASK);
	nc_core_पढ़ोy_count = nc_addr;

	/* Ensure पढ़ोy_count is zero-initialised beक्रमe the assembly runs */
	WRITE_ONCE(*nc_core_पढ़ोy_count, 0);
	coupled_barrier(&per_cpu(pm_barrier, core), online);

	/* Run the generated entry code */
	left = entry(online, nc_core_पढ़ोy_count);

	/* Remove the non-coherent mapping of पढ़ोy_count */
	kunmap_noncoherent();

	/* Indicate that this CPU is definitely coherent */
	cpumask_set_cpu(cpu, &cpu_coherent_mask);

	/*
	 * If this VPE is the first to leave the non-coherent रुको state then
	 * it needs to wake up any coupled VPEs still running their रुको
	 * inकाष्ठाion so that they वापस to cpuidle, which can then complete
	 * coordination between the coupled VPEs & provide the governor with
	 * a chance to reflect on the length of समय the VPEs were in the
	 * idle state.
	 */
	अगर (coupled_coherence && (state == CPS_PM_NC_WAIT) && (left == online))
		arch_send_call_function_ipi_mask(coupled_mask);

	वापस 0;
पूर्ण

अटल व्योम cps_gen_cache_routine(u32 **pp, काष्ठा uयंत्र_label **pl,
				  काष्ठा uयंत्र_reloc **pr,
				  स्थिर काष्ठा cache_desc *cache,
				  अचिन्हित op, पूर्णांक lbl)
अणु
	अचिन्हित cache_size = cache->ways << cache->waybit;
	अचिन्हित i;
	स्थिर अचिन्हित unroll_lines = 32;

	/* If the cache isn't present this function has it easy */
	अगर (cache->flags & MIPS_CACHE_NOT_PRESENT)
		वापस;

	/* Load base address */
	UASM_i_LA(pp, t0, (दीर्घ)CKSEG0);

	/* Calculate end address */
	अगर (cache_size < 0x8000)
		uयंत्र_i_addiu(pp, t1, t0, cache_size);
	अन्यथा
		UASM_i_LA(pp, t1, (दीर्घ)(CKSEG0 + cache_size));

	/* Start of cache op loop */
	uयंत्र_build_label(pl, *pp, lbl);

	/* Generate the cache ops */
	क्रम (i = 0; i < unroll_lines; i++) अणु
		अगर (cpu_has_mips_r6) अणु
			uयंत्र_i_cache(pp, op, 0, t0);
			uयंत्र_i_addiu(pp, t0, t0, cache->linesz);
		पूर्ण अन्यथा अणु
			uयंत्र_i_cache(pp, op, i * cache->linesz, t0);
		पूर्ण
	पूर्ण

	अगर (!cpu_has_mips_r6)
		/* Update the base address */
		uयंत्र_i_addiu(pp, t0, t0, unroll_lines * cache->linesz);

	/* Loop अगर we haven't reached the end address yet */
	uयंत्र_il_bne(pp, pr, t0, t1, lbl);
	uयंत्र_i_nop(pp);
पूर्ण

अटल पूर्णांक cps_gen_flush_fsb(u32 **pp, काष्ठा uयंत्र_label **pl,
			     काष्ठा uयंत्र_reloc **pr,
			     स्थिर काष्ठा cpuinfo_mips *cpu_info,
			     पूर्णांक lbl)
अणु
	अचिन्हित i, fsb_size = 8;
	अचिन्हित num_loads = (fsb_size * 3) / 2;
	अचिन्हित line_stride = 2;
	अचिन्हित line_size = cpu_info->dcache.linesz;
	अचिन्हित perf_counter, perf_event;
	अचिन्हित revision = cpu_info->processor_id & PRID_REV_MASK;

	/*
	 * Determine whether this CPU requires an FSB flush, and अगर so which
	 * perक्रमmance counter/event reflect stalls due to a full FSB.
	 */
	चयन (__get_cpu_type(cpu_info->cputype)) अणु
	हाल CPU_INTERAPTIV:
		perf_counter = 1;
		perf_event = 51;
		अवरोध;

	हाल CPU_PROAPTIV:
		/* Newer proAptiv cores करोn't require this workaround */
		अगर (revision >= PRID_REV_ENCODE_332(1, 1, 0))
			वापस 0;

		/* On older ones it's unavailable */
		वापस -1;

	शेष:
		/* Assume that the CPU करोes not need this workaround */
		वापस 0;
	पूर्ण

	/*
	 * Ensure that the fill/store buffer (FSB) is not holding the results
	 * of a prefetch, since अगर it is then the CPC sequencer may become
	 * stuck in the D3 (ClrBus) state whilst entering a low घातer state.
	 */

	/* Preserve perf counter setup */
	uयंत्र_i_mfc0(pp, t2, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uयंत्र_i_mfc0(pp, t3, 25, (perf_counter * 2) + 1); /* PerfCntN */

	/* Setup perf counter to count FSB full pipeline stalls */
	uयंत्र_i_addiu(pp, t0, zero, (perf_event << 5) | 0xf);
	uयंत्र_i_mtc0(pp, t0, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uयंत्र_i_ehb(pp);
	uयंत्र_i_mtc0(pp, zero, 25, (perf_counter * 2) + 1); /* PerfCntN */
	uयंत्र_i_ehb(pp);

	/* Base address क्रम loads */
	UASM_i_LA(pp, t0, (दीर्घ)CKSEG0);

	/* Start of clear loop */
	uयंत्र_build_label(pl, *pp, lbl);

	/* Perक्रमm some loads to fill the FSB */
	क्रम (i = 0; i < num_loads; i++)
		uयंत्र_i_lw(pp, zero, i * line_size * line_stride, t0);

	/*
	 * Invalidate the new D-cache entries so that the cache will need
	 * refilling (via the FSB) अगर the loop is executed again.
	 */
	क्रम (i = 0; i < num_loads; i++) अणु
		uयंत्र_i_cache(pp, Hit_Invalidate_D,
			     i * line_size * line_stride, t0);
		uयंत्र_i_cache(pp, Hit_Writeback_Inv_SD,
			     i * line_size * line_stride, t0);
	पूर्ण

	/* Barrier ensuring previous cache invalidates are complete */
	uयंत्र_i_sync(pp, __SYNC_full);
	uयंत्र_i_ehb(pp);

	/* Check whether the pipeline stalled due to the FSB being full */
	uयंत्र_i_mfc0(pp, t1, 25, (perf_counter * 2) + 1); /* PerfCntN */

	/* Loop अगर it didn't */
	uयंत्र_il_beqz(pp, pr, t1, lbl);
	uयंत्र_i_nop(pp);

	/* Restore perf counter 1. The count may well now be wrong... */
	uयंत्र_i_mtc0(pp, t2, 25, (perf_counter * 2) + 0); /* PerfCtlN */
	uयंत्र_i_ehb(pp);
	uयंत्र_i_mtc0(pp, t3, 25, (perf_counter * 2) + 1); /* PerfCntN */
	uयंत्र_i_ehb(pp);

	वापस 0;
पूर्ण

अटल व्योम cps_gen_set_top_bit(u32 **pp, काष्ठा uयंत्र_label **pl,
				काष्ठा uयंत्र_reloc **pr,
				अचिन्हित r_addr, पूर्णांक lbl)
अणु
	uयंत्र_i_lui(pp, t0, uयंत्र_rel_hi(0x80000000));
	uयंत्र_build_label(pl, *pp, lbl);
	uयंत्र_i_ll(pp, t1, 0, r_addr);
	uयंत्र_i_or(pp, t1, t1, t0);
	uयंत्र_i_sc(pp, t1, 0, r_addr);
	uयंत्र_il_beqz(pp, pr, t1, lbl);
	uयंत्र_i_nop(pp);
पूर्ण

अटल व्योम *cps_gen_entry_code(अचिन्हित cpu, क्रमागत cps_pm_state state)
अणु
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	u32 *buf, *p;
	स्थिर अचिन्हित r_online = a0;
	स्थिर अचिन्हित r_nc_count = a1;
	स्थिर अचिन्हित r_pcohctl = t7;
	स्थिर अचिन्हित max_instrs = 256;
	अचिन्हित cpc_cmd;
	पूर्णांक err;
	क्रमागत अणु
		lbl_incपढ़ोy = 1,
		lbl_poll_cont,
		lbl_secondary_hang,
		lbl_disable_coherence,
		lbl_flush_fsb,
		lbl_invicache,
		lbl_flushdcache,
		lbl_hang,
		lbl_set_cont,
		lbl_secondary_cont,
		lbl_decपढ़ोy,
	पूर्ण;

	/* Allocate a buffer to hold the generated code */
	p = buf = kसुस्मृति(max_instrs, माप(u32), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	/* Clear labels & relocs पढ़ोy क्रम (re)use */
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	अगर (IS_ENABLED(CONFIG_CPU_PM) && state == CPS_PM_POWER_GATED) अणु
		/* Power gating relies upon CPS SMP */
		अगर (!mips_cps_smp_in_use())
			जाओ out_err;

		/*
		 * Save CPU state. Note the non-standard calling convention
		 * with the वापस address placed in v0 to aव्योम clobbering
		 * the ra रेजिस्टर beक्रमe it is saved.
		 */
		UASM_i_LA(&p, t0, (दीर्घ)mips_cps_pm_save);
		uयंत्र_i_jalr(&p, v0, t0);
		uयंत्र_i_nop(&p);
	पूर्ण

	/*
	 * Load addresses of required CM & CPC रेजिस्टरs. This is करोne early
	 * because they're needed in both the enable & disable coherence steps
	 * but in the coupled हाल the enable step will only run on one VPE.
	 */
	UASM_i_LA(&p, r_pcohctl, (दीर्घ)addr_gcr_cl_coherence());

	अगर (coupled_coherence) अणु
		/* Increment पढ़ोy_count */
		uयंत्र_i_sync(&p, __SYNC_mb);
		uयंत्र_build_label(&l, p, lbl_incपढ़ोy);
		uयंत्र_i_ll(&p, t1, 0, r_nc_count);
		uयंत्र_i_addiu(&p, t2, t1, 1);
		uयंत्र_i_sc(&p, t2, 0, r_nc_count);
		uयंत्र_il_beqz(&p, &r, t2, lbl_incपढ़ोy);
		uयंत्र_i_addiu(&p, t1, t1, 1);

		/* Barrier ensuring all CPUs see the updated r_nc_count value */
		uयंत्र_i_sync(&p, __SYNC_mb);

		/*
		 * If this is the last VPE to become पढ़ोy क्रम non-coherence
		 * then it should branch below.
		 */
		uयंत्र_il_beq(&p, &r, t1, r_online, lbl_disable_coherence);
		uयंत्र_i_nop(&p);

		अगर (state < CPS_PM_POWER_GATED) अणु
			/*
			 * Otherwise this is not the last VPE to become पढ़ोy
			 * क्रम non-coherence. It needs to रुको until coherence
			 * has been disabled beक्रमe proceeding, which it will करो
			 * by polling क्रम the top bit of पढ़ोy_count being set.
			 */
			uयंत्र_i_addiu(&p, t1, zero, -1);
			uयंत्र_build_label(&l, p, lbl_poll_cont);
			uयंत्र_i_lw(&p, t0, 0, r_nc_count);
			uयंत्र_il_bltz(&p, &r, t0, lbl_secondary_cont);
			uयंत्र_i_ehb(&p);
			अगर (cpu_has_mipsmt)
				uयंत्र_i_yield(&p, zero, t1);
			uयंत्र_il_b(&p, &r, lbl_poll_cont);
			uयंत्र_i_nop(&p);
		पूर्ण अन्यथा अणु
			/*
			 * The core will lose घातer & this VPE will not जारी
			 * so it can simply halt here.
			 */
			अगर (cpu_has_mipsmt) अणु
				/* Halt the VPE via C0 tchalt रेजिस्टर */
				uयंत्र_i_addiu(&p, t0, zero, TCHALT_H);
				uयंत्र_i_mtc0(&p, t0, 2, 4);
			पूर्ण अन्यथा अगर (cpu_has_vp) अणु
				/* Halt the VP via the CPC VP_STOP रेजिस्टर */
				अचिन्हित पूर्णांक vpe_id;

				vpe_id = cpu_vpe_id(&cpu_data[cpu]);
				uयंत्र_i_addiu(&p, t0, zero, 1 << vpe_id);
				UASM_i_LA(&p, t1, (दीर्घ)addr_cpc_cl_vp_stop());
				uयंत्र_i_sw(&p, t0, 0, t1);
			पूर्ण अन्यथा अणु
				BUG();
			पूर्ण
			uयंत्र_build_label(&l, p, lbl_secondary_hang);
			uयंत्र_il_b(&p, &r, lbl_secondary_hang);
			uयंत्र_i_nop(&p);
		पूर्ण
	पूर्ण

	/*
	 * This is the poपूर्णांक of no वापस - this VPE will now proceed to
	 * disable coherence. At this poपूर्णांक we *must* be sure that no other
	 * VPE within the core will पूर्णांकerfere with the L1 dcache.
	 */
	uयंत्र_build_label(&l, p, lbl_disable_coherence);

	/* Invalidate the L1 icache */
	cps_gen_cache_routine(&p, &l, &r, &cpu_data[cpu].icache,
			      Index_Invalidate_I, lbl_invicache);

	/* Writeback & invalidate the L1 dcache */
	cps_gen_cache_routine(&p, &l, &r, &cpu_data[cpu].dcache,
			      Index_Writeback_Inv_D, lbl_flushdcache);

	/* Barrier ensuring previous cache invalidates are complete */
	uयंत्र_i_sync(&p, __SYNC_full);
	uयंत्र_i_ehb(&p);

	अगर (mips_cm_revision() < CM_REV_CM3) अणु
		/*
		* Disable all but self पूर्णांकerventions. The load from COHCTL is
		* defined by the पूर्णांकerAptiv & proAptiv SUMs as ensuring that the
		*  operation resulting from the preceding store is complete.
		*/
		uयंत्र_i_addiu(&p, t0, zero, 1 << cpu_core(&cpu_data[cpu]));
		uयंत्र_i_sw(&p, t0, 0, r_pcohctl);
		uयंत्र_i_lw(&p, t0, 0, r_pcohctl);

		/* Barrier to ensure ग_लिखो to coherence control is complete */
		uयंत्र_i_sync(&p, __SYNC_full);
		uयंत्र_i_ehb(&p);
	पूर्ण

	/* Disable coherence */
	uयंत्र_i_sw(&p, zero, 0, r_pcohctl);
	uयंत्र_i_lw(&p, t0, 0, r_pcohctl);

	अगर (state >= CPS_PM_CLOCK_GATED) अणु
		err = cps_gen_flush_fsb(&p, &l, &r, &cpu_data[cpu],
					lbl_flush_fsb);
		अगर (err)
			जाओ out_err;

		/* Determine the CPC command to issue */
		चयन (state) अणु
		हाल CPS_PM_CLOCK_GATED:
			cpc_cmd = CPC_Cx_CMD_CLOCKOFF;
			अवरोध;
		हाल CPS_PM_POWER_GATED:
			cpc_cmd = CPC_Cx_CMD_PWRDOWN;
			अवरोध;
		शेष:
			BUG();
			जाओ out_err;
		पूर्ण

		/* Issue the CPC command */
		UASM_i_LA(&p, t0, (दीर्घ)addr_cpc_cl_cmd());
		uयंत्र_i_addiu(&p, t1, zero, cpc_cmd);
		uयंत्र_i_sw(&p, t1, 0, t0);

		अगर (state == CPS_PM_POWER_GATED) अणु
			/* If anything goes wrong just hang */
			uयंत्र_build_label(&l, p, lbl_hang);
			uयंत्र_il_b(&p, &r, lbl_hang);
			uयंत्र_i_nop(&p);

			/*
			 * There's no poपूर्णांक generating more code, the core is
			 * घातered करोwn & अगर घातered back up will run from the
			 * reset vector not from here.
			 */
			जाओ gen_करोne;
		पूर्ण

		/* Barrier to ensure ग_लिखो to CPC command is complete */
		uयंत्र_i_sync(&p, __SYNC_full);
		uयंत्र_i_ehb(&p);
	पूर्ण

	अगर (state == CPS_PM_NC_WAIT) अणु
		/*
		 * At this poपूर्णांक it is safe क्रम all VPEs to proceed with
		 * execution. This VPE will set the top bit of पढ़ोy_count
		 * to indicate to the other VPEs that they may जारी.
		 */
		अगर (coupled_coherence)
			cps_gen_set_top_bit(&p, &l, &r, r_nc_count,
					    lbl_set_cont);

		/*
		 * VPEs which did not disable coherence will जारी
		 * executing, after coherence has been disabled, from this
		 * poपूर्णांक.
		 */
		uयंत्र_build_label(&l, p, lbl_secondary_cont);

		/* Now perक्रमm our रुको */
		uयंत्र_i_रुको(&p, 0);
	पूर्ण

	/*
	 * Re-enable coherence. Note that क्रम CPS_PM_NC_WAIT all coupled VPEs
	 * will run this. The first will actually re-enable coherence & the
	 * rest will just be perक्रमming a rather unusual nop.
	 */
	uयंत्र_i_addiu(&p, t0, zero, mips_cm_revision() < CM_REV_CM3
				? CM_GCR_Cx_COHERENCE_COHDOMAINEN
				: CM3_GCR_Cx_COHERENCE_COHEN);

	uयंत्र_i_sw(&p, t0, 0, r_pcohctl);
	uयंत्र_i_lw(&p, t0, 0, r_pcohctl);

	/* Barrier to ensure ग_लिखो to coherence control is complete */
	uयंत्र_i_sync(&p, __SYNC_full);
	uयंत्र_i_ehb(&p);

	अगर (coupled_coherence && (state == CPS_PM_NC_WAIT)) अणु
		/* Decrement पढ़ोy_count */
		uयंत्र_build_label(&l, p, lbl_decपढ़ोy);
		uयंत्र_i_sync(&p, __SYNC_mb);
		uयंत्र_i_ll(&p, t1, 0, r_nc_count);
		uयंत्र_i_addiu(&p, t2, t1, -1);
		uयंत्र_i_sc(&p, t2, 0, r_nc_count);
		uयंत्र_il_beqz(&p, &r, t2, lbl_decपढ़ोy);
		uयंत्र_i_andi(&p, v0, t1, (1 << fls(smp_num_siblings)) - 1);

		/* Barrier ensuring all CPUs see the updated r_nc_count value */
		uयंत्र_i_sync(&p, __SYNC_mb);
	पूर्ण

	अगर (coupled_coherence && (state == CPS_PM_CLOCK_GATED)) अणु
		/*
		 * At this poपूर्णांक it is safe क्रम all VPEs to proceed with
		 * execution. This VPE will set the top bit of पढ़ोy_count
		 * to indicate to the other VPEs that they may जारी.
		 */
		cps_gen_set_top_bit(&p, &l, &r, r_nc_count, lbl_set_cont);

		/*
		 * This core will be reliant upon another core sending a
		 * घातer-up command to the CPC in order to resume operation.
		 * Thus an arbitrary VPE can't trigger the core leaving the
		 * idle state and the one that disables coherence might as well
		 * be the one to re-enable it. The rest will जारी from here
		 * after that has been करोne.
		 */
		uयंत्र_build_label(&l, p, lbl_secondary_cont);

		/* Barrier ensuring all CPUs see the updated r_nc_count value */
		uयंत्र_i_sync(&p, __SYNC_mb);
	पूर्ण

	/* The core is coherent, समय to वापस to C code */
	uयंत्र_i_jr(&p, ra);
	uयंत्र_i_nop(&p);

gen_करोne:
	/* Ensure the code didn't exceed the resources allocated क्रम it */
	BUG_ON((p - buf) > max_instrs);
	BUG_ON((l - labels) > ARRAY_SIZE(labels));
	BUG_ON((r - relocs) > ARRAY_SIZE(relocs));

	/* Patch branch offsets */
	uयंत्र_resolve_relocs(relocs, labels);

	/* Flush the icache */
	local_flush_icache_range((अचिन्हित दीर्घ)buf, (अचिन्हित दीर्घ)p);

	वापस buf;
out_err:
	kमुक्त(buf);
	वापस शून्य;
पूर्ण

अटल पूर्णांक cps_pm_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	क्रमागत cps_pm_state state;
	अचिन्हित core = cpu_core(&cpu_data[cpu]);
	व्योम *entry_fn, *core_rc;

	क्रम (state = CPS_PM_NC_WAIT; state < CPS_PM_STATE_COUNT; state++) अणु
		अगर (per_cpu(nc_यंत्र_enter, core)[state])
			जारी;
		अगर (!test_bit(state, state_support))
			जारी;

		entry_fn = cps_gen_entry_code(cpu, state);
		अगर (!entry_fn) अणु
			pr_err("Failed to generate core %u state %u entry\n",
			       core, state);
			clear_bit(state, state_support);
		पूर्ण

		per_cpu(nc_यंत्र_enter, core)[state] = entry_fn;
	पूर्ण

	अगर (!per_cpu(पढ़ोy_count, core)) अणु
		core_rc = kदो_स्मृति(माप(u32), GFP_KERNEL);
		अगर (!core_rc) अणु
			pr_err("Failed allocate core %u ready_count\n", core);
			वापस -ENOMEM;
		पूर्ण
		per_cpu(पढ़ोy_count, core) = core_rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cps_pm_घातer_notअगरier(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	अचिन्हित पूर्णांक stat;

	चयन (event) अणु
	हाल PM_SUSPEND_PREPARE:
		stat = पढ़ो_cpc_cl_stat_conf();
		/*
		 * If we're attempting to suspend the प्रणाली and घातer करोwn all
		 * of the cores, the JTAG detect bit indicates that the CPC will
		 * instead put the cores पूर्णांकo घड़ी-off state. In this state
		 * a connected debugger can cause the CPU to attempt
		 * पूर्णांकeractions with the घातered करोwn प्रणाली. At best this will
		 * fail. At worst, it can hang the NoC, requiring a hard reset.
		 * To aव्योम this, just block प्रणाली suspend अगर a JTAG probe
		 * is detected.
		 */
		अगर (stat & CPC_Cx_STAT_CONF_EJTAG_PROBE) अणु
			pr_warn("JTAG probe is connected - abort suspend\n");
			वापस NOTIFY_BAD;
		पूर्ण
		वापस NOTIFY_DONE;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल पूर्णांक __init cps_pm_init(व्योम)
अणु
	/* A CM is required क्रम all non-coherent states */
	अगर (!mips_cm_present()) अणु
		pr_warn("pm-cps: no CM, non-coherent states unavailable\n");
		वापस 0;
	पूर्ण

	/*
	 * If पूर्णांकerrupts were enabled whilst running a रुको inकाष्ठाion on a
	 * non-coherent core then the VPE may end up processing पूर्णांकerrupts
	 * whilst non-coherent. That would be bad.
	 */
	अगर (cpu_रुको == r4k_रुको_irqoff)
		set_bit(CPS_PM_NC_WAIT, state_support);
	अन्यथा
		pr_warn("pm-cps: non-coherent wait unavailable\n");

	/* Detect whether a CPC is present */
	अगर (mips_cpc_present()) अणु
		/* Detect whether घड़ी gating is implemented */
		अगर (पढ़ो_cpc_cl_stat_conf() & CPC_Cx_STAT_CONF_CLKGAT_IMPL)
			set_bit(CPS_PM_CLOCK_GATED, state_support);
		अन्यथा
			pr_warn("pm-cps: CPC does not support clock gating\n");

		/* Power gating is available with CPS SMP & any CPC */
		अगर (mips_cps_smp_in_use())
			set_bit(CPS_PM_POWER_GATED, state_support);
		अन्यथा
			pr_warn("pm-cps: CPS SMP not in use, power gating unavailable\n");
	पूर्ण अन्यथा अणु
		pr_warn("pm-cps: no CPC, clock & power gating unavailable\n");
	पूर्ण

	pm_notअगरier(cps_pm_घातer_notअगरier, 0);

	वापस cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "mips/cps_pm:online",
				 cps_pm_online_cpu, शून्य);
पूर्ण
arch_initcall(cps_pm_init);
