<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate यंत्र statements containing #घोषणाs,
 * compile this file to assembler, and then extract the
 * #घोषणाs from the assembly-language output.
 */

#घोषणा GENERATING_ASM_OFFSETS	/* यंत्र/smp.h */

#समावेश <linux/compat.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/hrसमयr.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <linux/समय.स>
#समावेश <linux/hardirq.h>
#पूर्ण_अगर
#समावेश <linux/kbuild.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/dbell.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xics.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_POWERNV
#समावेश <यंत्र/opal.h>
#पूर्ण_अगर
#अगर defined(CONFIG_KVM) || defined(CONFIG_KVM_GUEST)
#समावेश <linux/kvm_host.h>
#पूर्ण_अगर
#अगर defined(CONFIG_KVM) && defined(CONFIG_PPC_BOOK3S)
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC32
#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
#समावेश "head_booke.h"
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_FSL_BOOK3E)
#समावेश "../mm/mmu_decl.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
#समावेश <यंत्र/fixmap.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_XMON
#समावेश "../xmon/xmon_bpts.h"
#पूर्ण_अगर

#घोषणा STACK_PT_REGS_OFFSET(sym, val)	\
	DEFINE(sym, STACK_FRAME_OVERHEAD + दुरत्व(काष्ठा pt_regs, val))

पूर्णांक मुख्य(व्योम)
अणु
	OFFSET(THREAD, task_काष्ठा, thपढ़ो);
	OFFSET(MM, task_काष्ठा, mm);
#अगर_घोषित CONFIG_STACKPROTECTOR
	OFFSET(TASK_CANARY, task_काष्ठा, stack_canary);
#अगर_घोषित CONFIG_PPC64
	OFFSET(PACA_CANARY, paca_काष्ठा, canary);
#पूर्ण_अगर
#पूर्ण_अगर
	OFFSET(MMCONTEXTID, mm_काष्ठा, context.id);
#अगर_घोषित CONFIG_PPC64
	DEFINE(संक_अंश, संक_अंश);
	DEFINE(NMI_MASK, NMI_MASK);
#अन्यथा
#अगर_घोषित CONFIG_PPC_RTAS
	OFFSET(RTAS_SP, thपढ़ो_काष्ठा, rtas_sp);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC64 */
	OFFSET(TASK_STACK, task_काष्ठा, stack);
#अगर_घोषित CONFIG_SMP
	OFFSET(TASK_CPU, task_काष्ठा, cpu);
#पूर्ण_अगर

#अगर_घोषित CONFIG_LIVEPATCH
	OFFSET(TI_livepatch_sp, thपढ़ो_info, livepatch_sp);
#पूर्ण_अगर

	OFFSET(KSP, thपढ़ो_काष्ठा, ksp);
	OFFSET(PT_REGS, thपढ़ो_काष्ठा, regs);
#अगर_घोषित CONFIG_BOOKE
	OFFSET(THREAD_NORMSAVES, thपढ़ो_काष्ठा, normsave[0]);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_FPU
	OFFSET(THREAD_FPEXC_MODE, thपढ़ो_काष्ठा, fpexc_mode);
	OFFSET(THREAD_FPSTATE, thपढ़ो_काष्ठा, fp_state.fpr);
	OFFSET(THREAD_FPSAVEAREA, thपढ़ो_काष्ठा, fp_save_area);
#पूर्ण_अगर
	OFFSET(FPSTATE_FPSCR, thपढ़ो_fp_state, fpscr);
	OFFSET(THREAD_LOAD_FP, thपढ़ो_काष्ठा, load_fp);
#अगर_घोषित CONFIG_ALTIVEC
	OFFSET(THREAD_VRSTATE, thपढ़ो_काष्ठा, vr_state.vr);
	OFFSET(THREAD_VRSAVEAREA, thपढ़ो_काष्ठा, vr_save_area);
	OFFSET(THREAD_VRSAVE, thपढ़ो_काष्ठा, vrsave);
	OFFSET(THREAD_USED_VR, thपढ़ो_काष्ठा, used_vr);
	OFFSET(VRSTATE_VSCR, thपढ़ो_vr_state, vscr);
	OFFSET(THREAD_LOAD_VEC, thपढ़ो_काष्ठा, load_vec);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
#अगर_घोषित CONFIG_VSX
	OFFSET(THREAD_USED_VSR, thपढ़ो_काष्ठा, used_vsr);
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_PPC64
	OFFSET(KSP_VSID, thपढ़ो_काष्ठा, ksp_vsid);
#अन्यथा /* CONFIG_PPC64 */
	OFFSET(PGसूची, thपढ़ो_काष्ठा, pgdir);
	OFFSET(SRR0, thपढ़ो_काष्ठा, srr0);
	OFFSET(SRR1, thपढ़ो_काष्ठा, srr1);
	OFFSET(DAR, thपढ़ो_काष्ठा, dar);
	OFFSET(DSISR, thपढ़ो_काष्ठा, dsisr);
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	OFFSET(THR0, thपढ़ो_काष्ठा, r0);
	OFFSET(THR3, thपढ़ो_काष्ठा, r3);
	OFFSET(THR4, thपढ़ो_काष्ठा, r4);
	OFFSET(THR5, thपढ़ो_काष्ठा, r5);
	OFFSET(THR6, thपढ़ो_काष्ठा, r6);
	OFFSET(THR8, thपढ़ो_काष्ठा, r8);
	OFFSET(THR9, thपढ़ो_काष्ठा, r9);
	OFFSET(THR11, thपढ़ो_काष्ठा, r11);
	OFFSET(THLR, thपढ़ो_काष्ठा, lr);
	OFFSET(THCTR, thपढ़ो_काष्ठा, ctr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	OFFSET(THREAD_EVR0, thपढ़ो_काष्ठा, evr[0]);
	OFFSET(THREAD_ACC, thपढ़ो_काष्ठा, acc);
	OFFSET(THREAD_SPEFSCR, thपढ़ो_काष्ठा, spefscr);
	OFFSET(THREAD_USED_SPE, thपढ़ो_काष्ठा, used_spe);
#पूर्ण_अगर /* CONFIG_SPE */
#पूर्ण_अगर /* CONFIG_PPC64 */
#अगर defined(CONFIG_4xx) || defined(CONFIG_BOOKE)
	OFFSET(THREAD_DBCR0, thपढ़ो_काष्ठा, debug.dbcr0);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	OFFSET(THREAD_KVM_SVCPU, thपढ़ो_काष्ठा, kvm_shaकरोw_vcpu);
#पूर्ण_अगर
#अगर defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	OFFSET(THREAD_KVM_VCPU, thपढ़ो_काष्ठा, kvm_vcpu);
#पूर्ण_अगर
#अगर defined(CONFIG_PPC_BOOK3S_32) && defined(CONFIG_PPC_KUAP)
	OFFSET(KUAP, thपढ़ो_काष्ठा, kuap);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	OFFSET(PACATMSCRATCH, paca_काष्ठा, पंचांग_scratch);
	OFFSET(THREAD_TM_TFHAR, thपढ़ो_काष्ठा, पंचांग_tfhar);
	OFFSET(THREAD_TM_TEXASR, thपढ़ो_काष्ठा, पंचांग_texasr);
	OFFSET(THREAD_TM_TFIAR, thपढ़ो_काष्ठा, पंचांग_tfiar);
	OFFSET(THREAD_TM_TAR, thपढ़ो_काष्ठा, पंचांग_tar);
	OFFSET(THREAD_TM_PPR, thपढ़ो_काष्ठा, पंचांग_ppr);
	OFFSET(THREAD_TM_DSCR, thपढ़ो_काष्ठा, पंचांग_dscr);
	OFFSET(THREAD_TM_AMR, thपढ़ो_काष्ठा, पंचांग_amr);
	OFFSET(PT_CKPT_REGS, thपढ़ो_काष्ठा, ckpt_regs);
	OFFSET(THREAD_CKVRSTATE, thपढ़ो_काष्ठा, ckvr_state.vr);
	OFFSET(THREAD_CKVRSAVE, thपढ़ो_काष्ठा, ckvrsave);
	OFFSET(THREAD_CKFPSTATE, thपढ़ो_काष्ठा, ckfp_state.fpr);
	/* Local pt_regs on stack क्रम Transactional Memory funcs. */
	DEFINE(TM_FRAME_SIZE, STACK_FRAME_OVERHEAD +
	       माप(काष्ठा pt_regs) + 16);
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

	OFFSET(TI_FLAGS, thपढ़ो_info, flags);
	OFFSET(TI_LOCAL_FLAGS, thपढ़ो_info, local_flags);
	OFFSET(TI_PREEMPT, thपढ़ो_info, preempt_count);

#अगर_घोषित CONFIG_PPC64
	OFFSET(DCACHEL1BLOCKSIZE, ppc64_caches, l1d.block_size);
	OFFSET(DCACHEL1LOGBLOCKSIZE, ppc64_caches, l1d.log_block_size);
	OFFSET(DCACHEL1BLOCKSPERPAGE, ppc64_caches, l1d.blocks_per_page);
	OFFSET(ICACHEL1BLOCKSIZE, ppc64_caches, l1i.block_size);
	OFFSET(ICACHEL1LOGBLOCKSIZE, ppc64_caches, l1i.log_block_size);
	OFFSET(ICACHEL1BLOCKSPERPAGE, ppc64_caches, l1i.blocks_per_page);
	/* paca */
	DEFINE(PACA_SIZE, माप(काष्ठा paca_काष्ठा));
	OFFSET(PACAPACAINDEX, paca_काष्ठा, paca_index);
	OFFSET(PACAPROCSTART, paca_काष्ठा, cpu_start);
	OFFSET(PACAKSAVE, paca_काष्ठा, kstack);
	OFFSET(PACACURRENT, paca_काष्ठा, __current);
	DEFINE(PACA_THREAD_INFO, दुरत्व(काष्ठा paca_काष्ठा, __current) +
				 दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info));
	OFFSET(PACASAVEDMSR, paca_काष्ठा, saved_msr);
	OFFSET(PACAR1, paca_काष्ठा, saved_r1);
	OFFSET(PACATOC, paca_काष्ठा, kernel_toc);
	OFFSET(PACAKBASE, paca_काष्ठा, kernelbase);
	OFFSET(PACAKMSR, paca_काष्ठा, kernel_msr);
	OFFSET(PACAIRQSOFTMASK, paca_काष्ठा, irq_soft_mask);
	OFFSET(PACAIRQHAPPENED, paca_काष्ठा, irq_happened);
	OFFSET(PACA_FTRACE_ENABLED, paca_काष्ठा, ftrace_enabled);
#अगर_घोषित CONFIG_PPC_BOOK3S
	OFFSET(PACACONTEXTID, paca_काष्ठा, mm_ctx_id);
#अगर_घोषित CONFIG_PPC_MM_SLICES
	OFFSET(PACALOWSLICESPSIZE, paca_काष्ठा, mm_ctx_low_slices_psize);
	OFFSET(PACAHIGHSLICEPSIZE, paca_काष्ठा, mm_ctx_high_slices_psize);
	OFFSET(PACA_SLB_ADDR_LIMIT, paca_काष्ठा, mm_ctx_slb_addr_limit);
	DEFINE(MMUPSIZEDEFSIZE, माप(काष्ठा mmu_psize_def));
#पूर्ण_अगर /* CONFIG_PPC_MM_SLICES */
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3E
	OFFSET(PACAPGD, paca_काष्ठा, pgd);
	OFFSET(PACA_KERNELPGD, paca_काष्ठा, kernel_pgd);
	OFFSET(PACA_EXGEN, paca_काष्ठा, exgen);
	OFFSET(PACA_EXTLB, paca_काष्ठा, extlb);
	OFFSET(PACA_EXMC, paca_काष्ठा, exmc);
	OFFSET(PACA_EXCRIT, paca_काष्ठा, excrit);
	OFFSET(PACA_EXDBG, paca_काष्ठा, exdbg);
	OFFSET(PACA_MC_STACK, paca_काष्ठा, mc_kstack);
	OFFSET(PACA_CRIT_STACK, paca_काष्ठा, crit_kstack);
	OFFSET(PACA_DBG_STACK, paca_काष्ठा, dbg_kstack);
	OFFSET(PACA_TCD_PTR, paca_काष्ठा, tcd_ptr);

	OFFSET(TCD_ESEL_NEXT, tlb_core_data, esel_next);
	OFFSET(TCD_ESEL_MAX, tlb_core_data, esel_max);
	OFFSET(TCD_ESEL_FIRST, tlb_core_data, esel_first);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	OFFSET(PACASLBCACHE, paca_काष्ठा, slb_cache);
	OFFSET(PACASLBCACHEPTR, paca_काष्ठा, slb_cache_ptr);
	OFFSET(PACASTABRR, paca_काष्ठा, stab_rr);
	OFFSET(PACAVMALLOCSLLP, paca_काष्ठा, vदो_स्मृति_sllp);
#अगर_घोषित CONFIG_PPC_MM_SLICES
	OFFSET(MMUPSIZESLLP, mmu_psize_def, sllp);
#अन्यथा
	OFFSET(PACACONTEXTSLLP, paca_काष्ठा, mm_ctx_sllp);
#पूर्ण_अगर /* CONFIG_PPC_MM_SLICES */
	OFFSET(PACA_EXGEN, paca_काष्ठा, exgen);
	OFFSET(PACA_EXMC, paca_काष्ठा, exmc);
	OFFSET(PACA_EXNMI, paca_काष्ठा, exnmi);
#अगर_घोषित CONFIG_PPC_PSERIES
	OFFSET(PACALPPACAPTR, paca_काष्ठा, lppaca_ptr);
#पूर्ण_अगर
	OFFSET(PACA_SLBSHADOWPTR, paca_काष्ठा, slb_shaकरोw_ptr);
	OFFSET(SLBSHADOW_STACKVSID, slb_shaकरोw, save_area[SLB_NUM_BOLTED - 1].vsid);
	OFFSET(SLBSHADOW_STACKESID, slb_shaकरोw, save_area[SLB_NUM_BOLTED - 1].esid);
	OFFSET(SLBSHADOW_SAVEAREA, slb_shaकरोw, save_area);
	OFFSET(LPPACA_PMCINUSE, lppaca, pmcregs_in_use);
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	OFFSET(PACA_PMCINUSE, paca_काष्ठा, pmcregs_in_use);
#पूर्ण_अगर
	OFFSET(LPPACA_DTLIDX, lppaca, dtl_idx);
	OFFSET(LPPACA_YIELDCOUNT, lppaca, yield_count);
	OFFSET(PACA_DTL_RIDX, paca_काष्ठा, dtl_ridx);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
	OFFSET(PACAEMERGSP, paca_काष्ठा, emergency_sp);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	OFFSET(PACAMCEMERGSP, paca_काष्ठा, mc_emergency_sp);
	OFFSET(PACA_NMI_EMERG_SP, paca_काष्ठा, nmi_emergency_sp);
	OFFSET(PACA_IN_MCE, paca_काष्ठा, in_mce);
	OFFSET(PACA_IN_NMI, paca_काष्ठा, in_nmi);
	OFFSET(PACA_RFI_FLUSH_FALLBACK_AREA, paca_काष्ठा, rfi_flush_fallback_area);
	OFFSET(PACA_EXRFI, paca_काष्ठा, exrfi);
	OFFSET(PACA_L1D_FLUSH_SIZE, paca_काष्ठा, l1d_flush_size);

#पूर्ण_अगर
	OFFSET(PACAHWCPUID, paca_काष्ठा, hw_cpu_id);
	OFFSET(PACAKEXECSTATE, paca_काष्ठा, kexec_state);
	OFFSET(PACA_DSCR_DEFAULT, paca_काष्ठा, dscr_शेष);
#अगर_घोषित CONFIG_PPC_BOOK3E
	OFFSET(PACA_TRAP_SAVE, paca_काष्ठा, trap_save);
#पूर्ण_अगर
	OFFSET(PACA_SPRG_VDSO, paca_काष्ठा, sprg_vdso);
#अन्यथा /* CONFIG_PPC64 */
#पूर्ण_अगर /* CONFIG_PPC64 */

	/* RTAS */
	OFFSET(RTASBASE, rtas_t, base);
	OFFSET(RTASENTRY, rtas_t, entry);

	/* Interrupt रेजिस्टर frame */
	DEFINE(INT_FRAME_SIZE, STACK_INT_FRAME_SIZE);
	DEFINE(SWITCH_FRAME_SIZE, STACK_FRAME_WITH_PT_REGS);
	STACK_PT_REGS_OFFSET(GPR0, gpr[0]);
	STACK_PT_REGS_OFFSET(GPR1, gpr[1]);
	STACK_PT_REGS_OFFSET(GPR2, gpr[2]);
	STACK_PT_REGS_OFFSET(GPR3, gpr[3]);
	STACK_PT_REGS_OFFSET(GPR4, gpr[4]);
	STACK_PT_REGS_OFFSET(GPR5, gpr[5]);
	STACK_PT_REGS_OFFSET(GPR6, gpr[6]);
	STACK_PT_REGS_OFFSET(GPR7, gpr[7]);
	STACK_PT_REGS_OFFSET(GPR8, gpr[8]);
	STACK_PT_REGS_OFFSET(GPR9, gpr[9]);
	STACK_PT_REGS_OFFSET(GPR10, gpr[10]);
	STACK_PT_REGS_OFFSET(GPR11, gpr[11]);
	STACK_PT_REGS_OFFSET(GPR12, gpr[12]);
	STACK_PT_REGS_OFFSET(GPR13, gpr[13]);
	/*
	 * Note: these symbols include _ because they overlap with special
	 * रेजिस्टर names
	 */
	STACK_PT_REGS_OFFSET(_NIP, nip);
	STACK_PT_REGS_OFFSET(_MSR, msr);
	STACK_PT_REGS_OFFSET(_CTR, ctr);
	STACK_PT_REGS_OFFSET(_LINK, link);
	STACK_PT_REGS_OFFSET(_CCR, ccr);
	STACK_PT_REGS_OFFSET(_XER, xer);
	STACK_PT_REGS_OFFSET(_DAR, dar);
	STACK_PT_REGS_OFFSET(_DSISR, dsisr);
	STACK_PT_REGS_OFFSET(ORIG_GPR3, orig_gpr3);
	STACK_PT_REGS_OFFSET(RESULT, result);
	STACK_PT_REGS_OFFSET(_TRAP, trap);
#अगर_अघोषित CONFIG_PPC64
	/*
	 * The PowerPC 400-class & Book-E processors have neither the DAR
	 * nor the DSISR SPRs. Hence, we overload them to hold the similar
	 * DEAR and ESR SPRs क्रम such processors.  For critical पूर्णांकerrupts
	 * we use them to hold SRR0 and SRR1.
	 */
	STACK_PT_REGS_OFFSET(_DEAR, dar);
	STACK_PT_REGS_OFFSET(_ESR, dsisr);
#अन्यथा /* CONFIG_PPC64 */
	STACK_PT_REGS_OFFSET(SOFTE, softe);
	STACK_PT_REGS_OFFSET(_PPR, ppr);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_PKEY
	STACK_PT_REGS_OFFSET(STACK_REGS_AMR, amr);
	STACK_PT_REGS_OFFSET(STACK_REGS_IAMR, iamr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_KUAP
	STACK_PT_REGS_OFFSET(STACK_REGS_KUAP, kuap);
#पूर्ण_अगर


#अगर defined(CONFIG_PPC32)
#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
	DEFINE(EXC_LVL_SIZE, STACK_EXC_LVL_FRAME_SIZE);
	DEFINE(MAS0, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas0));
	/* we overload MMUCR क्रम 44x on MAS0 since they are mutually exclusive */
	DEFINE(MMUCR, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas0));
	DEFINE(MAS1, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas1));
	DEFINE(MAS2, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas2));
	DEFINE(MAS3, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas3));
	DEFINE(MAS6, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas6));
	DEFINE(MAS7, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, mas7));
	DEFINE(_SRR0, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, srr0));
	DEFINE(_SRR1, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, srr1));
	DEFINE(_CSRR0, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, csrr0));
	DEFINE(_CSRR1, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, csrr1));
	DEFINE(_DSRR0, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, dsrr0));
	DEFINE(_DSRR1, STACK_INT_FRAME_SIZE+दुरत्व(काष्ठा exception_regs, dsrr1));
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PPC64
	OFFSET(MM_PGD, mm_काष्ठा, pgd);
#पूर्ण_अगर /* ! CONFIG_PPC64 */

	/* About the CPU features table */
	OFFSET(CPU_SPEC_FEATURES, cpu_spec, cpu_features);
	OFFSET(CPU_SPEC_SETUP, cpu_spec, cpu_setup);
	OFFSET(CPU_SPEC_RESTORE, cpu_spec, cpu_restore);

	OFFSET(pbe_address, pbe, address);
	OFFSET(pbe_orig_address, pbe, orig_address);
	OFFSET(pbe_next, pbe, next);

#अगर_अघोषित CONFIG_PPC64
	DEFINE(TASK_SIZE, TASK_SIZE);
	DEFINE(NUM_USER_SEGMENTS, TASK_SIZE>>28);
#पूर्ण_अगर /* ! CONFIG_PPC64 */

	/* datapage offsets क्रम use by vdso */
	OFFSET(VDSO_DATA_OFFSET, vdso_arch_data, data);
	OFFSET(CFG_TB_TICKS_PER_SEC, vdso_arch_data, tb_ticks_per_sec);
#अगर_घोषित CONFIG_PPC64
	OFFSET(CFG_ICACHE_BLOCKSZ, vdso_arch_data, icache_block_size);
	OFFSET(CFG_DCACHE_BLOCKSZ, vdso_arch_data, dcache_block_size);
	OFFSET(CFG_ICACHE_LOGBLOCKSZ, vdso_arch_data, icache_log_block_size);
	OFFSET(CFG_DCACHE_LOGBLOCKSZ, vdso_arch_data, dcache_log_block_size);
	OFFSET(CFG_SYSCALL_MAP64, vdso_arch_data, syscall_map);
	OFFSET(CFG_SYSCALL_MAP32, vdso_arch_data, compat_syscall_map);
#अन्यथा
	OFFSET(CFG_SYSCALL_MAP32, vdso_arch_data, syscall_map);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BUG
	DEFINE(BUG_ENTRY_SIZE, माप(काष्ठा bug_entry));
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	DEFINE(PGD_TABLE_SIZE, (माप(pgd_t) << max(RADIX_PGD_INDEX_SIZE, H_PGD_INDEX_SIZE)));
#अन्यथा
	DEFINE(PGD_TABLE_SIZE, PGD_TABLE_SIZE);
#पूर्ण_अगर
	DEFINE(PTE_SIZE, माप(pte_t));

#अगर_घोषित CONFIG_KVM
	OFFSET(VCPU_HOST_STACK, kvm_vcpu, arch.host_stack);
	OFFSET(VCPU_HOST_PID, kvm_vcpu, arch.host_pid);
	OFFSET(VCPU_GUEST_PID, kvm_vcpu, arch.pid);
	OFFSET(VCPU_GPRS, kvm_vcpu, arch.regs.gpr);
	OFFSET(VCPU_VRSAVE, kvm_vcpu, arch.vrsave);
	OFFSET(VCPU_FPRS, kvm_vcpu, arch.fp.fpr);
#अगर_घोषित CONFIG_ALTIVEC
	OFFSET(VCPU_VRS, kvm_vcpu, arch.vr.vr);
#पूर्ण_अगर
	OFFSET(VCPU_XER, kvm_vcpu, arch.regs.xer);
	OFFSET(VCPU_CTR, kvm_vcpu, arch.regs.ctr);
	OFFSET(VCPU_LR, kvm_vcpu, arch.regs.link);
#अगर_घोषित CONFIG_PPC_BOOK3S
	OFFSET(VCPU_TAR, kvm_vcpu, arch.tar);
#पूर्ण_अगर
	OFFSET(VCPU_CR, kvm_vcpu, arch.regs.ccr);
	OFFSET(VCPU_PC, kvm_vcpu, arch.regs.nip);
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	OFFSET(VCPU_MSR, kvm_vcpu, arch.shregs.msr);
	OFFSET(VCPU_SRR0, kvm_vcpu, arch.shregs.srr0);
	OFFSET(VCPU_SRR1, kvm_vcpu, arch.shregs.srr1);
	OFFSET(VCPU_SPRG0, kvm_vcpu, arch.shregs.sprg0);
	OFFSET(VCPU_SPRG1, kvm_vcpu, arch.shregs.sprg1);
	OFFSET(VCPU_SPRG2, kvm_vcpu, arch.shregs.sprg2);
	OFFSET(VCPU_SPRG3, kvm_vcpu, arch.shregs.sprg3);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_EXIT_TIMING
	OFFSET(VCPU_TB_RMENTRY, kvm_vcpu, arch.rm_entry);
	OFFSET(VCPU_TB_RMINTR, kvm_vcpu, arch.rm_पूर्णांकr);
	OFFSET(VCPU_TB_RMEXIT, kvm_vcpu, arch.rm_निकास);
	OFFSET(VCPU_TB_GUEST, kvm_vcpu, arch.guest_समय);
	OFFSET(VCPU_TB_CEDE, kvm_vcpu, arch.cede_समय);
	OFFSET(VCPU_CUR_ACTIVITY, kvm_vcpu, arch.cur_activity);
	OFFSET(VCPU_ACTIVITY_START, kvm_vcpu, arch.cur_tb_start);
	OFFSET(TAS_SEQCOUNT, kvmhv_tb_accumulator, seqcount);
	OFFSET(TAS_TOTAL, kvmhv_tb_accumulator, tb_total);
	OFFSET(TAS_MIN, kvmhv_tb_accumulator, tb_min);
	OFFSET(TAS_MAX, kvmhv_tb_accumulator, tb_max);
#पूर्ण_अगर
	OFFSET(VCPU_SHARED_SPRG3, kvm_vcpu_arch_shared, sprg3);
	OFFSET(VCPU_SHARED_SPRG4, kvm_vcpu_arch_shared, sprg4);
	OFFSET(VCPU_SHARED_SPRG5, kvm_vcpu_arch_shared, sprg5);
	OFFSET(VCPU_SHARED_SPRG6, kvm_vcpu_arch_shared, sprg6);
	OFFSET(VCPU_SHARED_SPRG7, kvm_vcpu_arch_shared, sprg7);
	OFFSET(VCPU_SHADOW_PID, kvm_vcpu, arch.shaकरोw_pid);
	OFFSET(VCPU_SHADOW_PID1, kvm_vcpu, arch.shaकरोw_pid1);
	OFFSET(VCPU_SHARED, kvm_vcpu, arch.shared);
	OFFSET(VCPU_SHARED_MSR, kvm_vcpu_arch_shared, msr);
	OFFSET(VCPU_SHADOW_MSR, kvm_vcpu, arch.shaकरोw_msr);
#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PR_POSSIBLE)
	OFFSET(VCPU_SHAREDBE, kvm_vcpu, arch.shared_big_endian);
#पूर्ण_अगर

	OFFSET(VCPU_SHARED_MAS0, kvm_vcpu_arch_shared, mas0);
	OFFSET(VCPU_SHARED_MAS1, kvm_vcpu_arch_shared, mas1);
	OFFSET(VCPU_SHARED_MAS2, kvm_vcpu_arch_shared, mas2);
	OFFSET(VCPU_SHARED_MAS7_3, kvm_vcpu_arch_shared, mas7_3);
	OFFSET(VCPU_SHARED_MAS4, kvm_vcpu_arch_shared, mas4);
	OFFSET(VCPU_SHARED_MAS6, kvm_vcpu_arch_shared, mas6);

	OFFSET(VCPU_KVM, kvm_vcpu, kvm);
	OFFSET(KVM_LPID, kvm, arch.lpid);

	/* book3s */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	OFFSET(KVM_TLB_SETS, kvm, arch.tlb_sets);
	OFFSET(KVM_SDR1, kvm, arch.sdr1);
	OFFSET(KVM_HOST_LPID, kvm, arch.host_lpid);
	OFFSET(KVM_HOST_LPCR, kvm, arch.host_lpcr);
	OFFSET(KVM_HOST_SDR1, kvm, arch.host_sdr1);
	OFFSET(KVM_NEED_FLUSH, kvm, arch.need_tlb_flush.bits);
	OFFSET(KVM_ENABLED_HCALLS, kvm, arch.enabled_hcalls);
	OFFSET(KVM_VRMA_SLB_V, kvm, arch.vrma_slb_v);
	OFFSET(KVM_RADIX, kvm, arch.radix);
	OFFSET(KVM_FWNMI, kvm, arch.fwnmi_enabled);
	OFFSET(KVM_SECURE_GUEST, kvm, arch.secure_guest);
	OFFSET(VCPU_DSISR, kvm_vcpu, arch.shregs.dsisr);
	OFFSET(VCPU_DAR, kvm_vcpu, arch.shregs.dar);
	OFFSET(VCPU_VPA, kvm_vcpu, arch.vpa.pinned_addr);
	OFFSET(VCPU_VPA_सूचीTY, kvm_vcpu, arch.vpa.dirty);
	OFFSET(VCPU_HEIR, kvm_vcpu, arch.emul_inst);
	OFFSET(VCPU_NESTED, kvm_vcpu, arch.nested);
	OFFSET(VCPU_CPU, kvm_vcpu, cpu);
	OFFSET(VCPU_THREAD_CPU, kvm_vcpu, arch.thपढ़ो_cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S
	OFFSET(VCPU_PURR, kvm_vcpu, arch.purr);
	OFFSET(VCPU_SPURR, kvm_vcpu, arch.spurr);
	OFFSET(VCPU_IC, kvm_vcpu, arch.ic);
	OFFSET(VCPU_DSCR, kvm_vcpu, arch.dscr);
	OFFSET(VCPU_AMR, kvm_vcpu, arch.amr);
	OFFSET(VCPU_UAMOR, kvm_vcpu, arch.uamor);
	OFFSET(VCPU_IAMR, kvm_vcpu, arch.iamr);
	OFFSET(VCPU_CTRL, kvm_vcpu, arch.ctrl);
	OFFSET(VCPU_DABR, kvm_vcpu, arch.dabr);
	OFFSET(VCPU_DABRX, kvm_vcpu, arch.dabrx);
	OFFSET(VCPU_DAWR0, kvm_vcpu, arch.dawr0);
	OFFSET(VCPU_DAWRX0, kvm_vcpu, arch.dawrx0);
	OFFSET(VCPU_DAWR1, kvm_vcpu, arch.dawr1);
	OFFSET(VCPU_DAWRX1, kvm_vcpu, arch.dawrx1);
	OFFSET(VCPU_CIABR, kvm_vcpu, arch.ciabr);
	OFFSET(VCPU_HFLAGS, kvm_vcpu, arch.hflags);
	OFFSET(VCPU_DEC, kvm_vcpu, arch.dec);
	OFFSET(VCPU_DEC_EXPIRES, kvm_vcpu, arch.dec_expires);
	OFFSET(VCPU_PENDING_EXC, kvm_vcpu, arch.pending_exceptions);
	OFFSET(VCPU_CEDED, kvm_vcpu, arch.ceded);
	OFFSET(VCPU_PRODDED, kvm_vcpu, arch.prodded);
	OFFSET(VCPU_IRQ_PENDING, kvm_vcpu, arch.irq_pending);
	OFFSET(VCPU_DBELL_REQ, kvm_vcpu, arch.करोorbell_request);
	OFFSET(VCPU_MMCR, kvm_vcpu, arch.mmcr);
	OFFSET(VCPU_MMCRA, kvm_vcpu, arch.mmcra);
	OFFSET(VCPU_MMCRS, kvm_vcpu, arch.mmcrs);
	OFFSET(VCPU_PMC, kvm_vcpu, arch.pmc);
	OFFSET(VCPU_SPMC, kvm_vcpu, arch.spmc);
	OFFSET(VCPU_SIAR, kvm_vcpu, arch.siar);
	OFFSET(VCPU_SDAR, kvm_vcpu, arch.sdar);
	OFFSET(VCPU_SIER, kvm_vcpu, arch.sier);
	OFFSET(VCPU_SLB, kvm_vcpu, arch.slb);
	OFFSET(VCPU_SLB_MAX, kvm_vcpu, arch.slb_max);
	OFFSET(VCPU_SLB_NR, kvm_vcpu, arch.slb_nr);
	OFFSET(VCPU_FAULT_DSISR, kvm_vcpu, arch.fault_dsisr);
	OFFSET(VCPU_FAULT_DAR, kvm_vcpu, arch.fault_dar);
	OFFSET(VCPU_FAULT_GPA, kvm_vcpu, arch.fault_gpa);
	OFFSET(VCPU_INTR_MSR, kvm_vcpu, arch.पूर्णांकr_msr);
	OFFSET(VCPU_LAST_INST, kvm_vcpu, arch.last_inst);
	OFFSET(VCPU_TRAP, kvm_vcpu, arch.trap);
	OFFSET(VCPU_CFAR, kvm_vcpu, arch.cfar);
	OFFSET(VCPU_PPR, kvm_vcpu, arch.ppr);
	OFFSET(VCPU_FSCR, kvm_vcpu, arch.fscr);
	OFFSET(VCPU_PSPB, kvm_vcpu, arch.pspb);
	OFFSET(VCPU_EBBHR, kvm_vcpu, arch.ebbhr);
	OFFSET(VCPU_EBBRR, kvm_vcpu, arch.ebbrr);
	OFFSET(VCPU_BESCR, kvm_vcpu, arch.bescr);
	OFFSET(VCPU_CSIGR, kvm_vcpu, arch.csigr);
	OFFSET(VCPU_TACR, kvm_vcpu, arch.tacr);
	OFFSET(VCPU_TCSCR, kvm_vcpu, arch.tcscr);
	OFFSET(VCPU_ACOP, kvm_vcpu, arch.acop);
	OFFSET(VCPU_WORT, kvm_vcpu, arch.wort);
	OFFSET(VCPU_TID, kvm_vcpu, arch.tid);
	OFFSET(VCPU_PSSCR, kvm_vcpu, arch.psscr);
	OFFSET(VCPU_HFSCR, kvm_vcpu, arch.hfscr);
	OFFSET(VCORE_ENTRY_EXIT, kvmppc_vcore, entry_निकास_map);
	OFFSET(VCORE_IN_GUEST, kvmppc_vcore, in_guest);
	OFFSET(VCORE_NAPPING_THREADS, kvmppc_vcore, napping_thपढ़ोs);
	OFFSET(VCORE_KVM, kvmppc_vcore, kvm);
	OFFSET(VCORE_TB_OFFSET, kvmppc_vcore, tb_offset);
	OFFSET(VCORE_TB_OFFSET_APPL, kvmppc_vcore, tb_offset_applied);
	OFFSET(VCORE_LPCR, kvmppc_vcore, lpcr);
	OFFSET(VCORE_PCR, kvmppc_vcore, pcr);
	OFFSET(VCORE_DPDES, kvmppc_vcore, dpdes);
	OFFSET(VCORE_VTB, kvmppc_vcore, vtb);
	OFFSET(VCPU_SLB_E, kvmppc_slb, orige);
	OFFSET(VCPU_SLB_V, kvmppc_slb, origv);
	DEFINE(VCPU_SLB_SIZE, माप(काष्ठा kvmppc_slb));
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	OFFSET(VCPU_TFHAR, kvm_vcpu, arch.tfhar);
	OFFSET(VCPU_TFIAR, kvm_vcpu, arch.tfiar);
	OFFSET(VCPU_TEXASR, kvm_vcpu, arch.texasr);
	OFFSET(VCPU_ORIG_TEXASR, kvm_vcpu, arch.orig_texasr);
	OFFSET(VCPU_GPR_TM, kvm_vcpu, arch.gpr_पंचांग);
	OFFSET(VCPU_FPRS_TM, kvm_vcpu, arch.fp_पंचांग.fpr);
	OFFSET(VCPU_VRS_TM, kvm_vcpu, arch.vr_पंचांग.vr);
	OFFSET(VCPU_VRSAVE_TM, kvm_vcpu, arch.vrsave_पंचांग);
	OFFSET(VCPU_CR_TM, kvm_vcpu, arch.cr_पंचांग);
	OFFSET(VCPU_XER_TM, kvm_vcpu, arch.xer_पंचांग);
	OFFSET(VCPU_LR_TM, kvm_vcpu, arch.lr_पंचांग);
	OFFSET(VCPU_CTR_TM, kvm_vcpu, arch.ctr_पंचांग);
	OFFSET(VCPU_AMR_TM, kvm_vcpu, arch.amr_पंचांग);
	OFFSET(VCPU_PPR_TM, kvm_vcpu, arch.ppr_पंचांग);
	OFFSET(VCPU_DSCR_TM, kvm_vcpu, arch.dscr_पंचांग);
	OFFSET(VCPU_TAR_TM, kvm_vcpu, arch.tar_पंचांग);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
	OFFSET(PACA_SVCPU, paca_काष्ठा, shaकरोw_vcpu);
# define SVCPU_FIELD(x, f)	DEFINE(x, दुरत्व(काष्ठा paca_काष्ठा, shaकरोw_vcpu.f))
#अन्यथा
# define SVCPU_FIELD(x, f)
#पूर्ण_अगर
# define HSTATE_FIELD(x, f)	DEFINE(x, दुरत्व(काष्ठा paca_काष्ठा, kvm_hstate.f))
#अन्यथा	/* 32-bit */
# define SVCPU_FIELD(x, f)	DEFINE(x, दुरत्व(काष्ठा kvmppc_book3s_shaकरोw_vcpu, f))
# define HSTATE_FIELD(x, f)	DEFINE(x, दुरत्व(काष्ठा kvmppc_book3s_shaकरोw_vcpu, hstate.f))
#पूर्ण_अगर

	SVCPU_FIELD(SVCPU_CR, cr);
	SVCPU_FIELD(SVCPU_XER, xer);
	SVCPU_FIELD(SVCPU_CTR, ctr);
	SVCPU_FIELD(SVCPU_LR, lr);
	SVCPU_FIELD(SVCPU_PC, pc);
	SVCPU_FIELD(SVCPU_R0, gpr[0]);
	SVCPU_FIELD(SVCPU_R1, gpr[1]);
	SVCPU_FIELD(SVCPU_R2, gpr[2]);
	SVCPU_FIELD(SVCPU_R3, gpr[3]);
	SVCPU_FIELD(SVCPU_R4, gpr[4]);
	SVCPU_FIELD(SVCPU_R5, gpr[5]);
	SVCPU_FIELD(SVCPU_R6, gpr[6]);
	SVCPU_FIELD(SVCPU_R7, gpr[7]);
	SVCPU_FIELD(SVCPU_R8, gpr[8]);
	SVCPU_FIELD(SVCPU_R9, gpr[9]);
	SVCPU_FIELD(SVCPU_R10, gpr[10]);
	SVCPU_FIELD(SVCPU_R11, gpr[11]);
	SVCPU_FIELD(SVCPU_R12, gpr[12]);
	SVCPU_FIELD(SVCPU_R13, gpr[13]);
	SVCPU_FIELD(SVCPU_FAULT_DSISR, fault_dsisr);
	SVCPU_FIELD(SVCPU_FAULT_DAR, fault_dar);
	SVCPU_FIELD(SVCPU_LAST_INST, last_inst);
	SVCPU_FIELD(SVCPU_SHADOW_SRR1, shaकरोw_srr1);
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	SVCPU_FIELD(SVCPU_SR, sr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	SVCPU_FIELD(SVCPU_SLB, slb);
	SVCPU_FIELD(SVCPU_SLB_MAX, slb_max);
	SVCPU_FIELD(SVCPU_SHADOW_FSCR, shaकरोw_fscr);
#पूर्ण_अगर

	HSTATE_FIELD(HSTATE_HOST_R1, host_r1);
	HSTATE_FIELD(HSTATE_HOST_R2, host_r2);
	HSTATE_FIELD(HSTATE_HOST_MSR, host_msr);
	HSTATE_FIELD(HSTATE_VMHANDLER, vmhandler);
	HSTATE_FIELD(HSTATE_SCRATCH0, scratch0);
	HSTATE_FIELD(HSTATE_SCRATCH1, scratch1);
	HSTATE_FIELD(HSTATE_SCRATCH2, scratch2);
	HSTATE_FIELD(HSTATE_IN_GUEST, in_guest);
	HSTATE_FIELD(HSTATE_RESTORE_HID5, restore_hid5);
	HSTATE_FIELD(HSTATE_NAPPING, napping);

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	HSTATE_FIELD(HSTATE_HWTHREAD_REQ, hwthपढ़ो_req);
	HSTATE_FIELD(HSTATE_HWTHREAD_STATE, hwthपढ़ो_state);
	HSTATE_FIELD(HSTATE_KVM_VCPU, kvm_vcpu);
	HSTATE_FIELD(HSTATE_KVM_VCORE, kvm_vcore);
	HSTATE_FIELD(HSTATE_XICS_PHYS, xics_phys);
	HSTATE_FIELD(HSTATE_XIVE_TIMA_PHYS, xive_tima_phys);
	HSTATE_FIELD(HSTATE_XIVE_TIMA_VIRT, xive_tima_virt);
	HSTATE_FIELD(HSTATE_SAVED_XIRR, saved_xirr);
	HSTATE_FIELD(HSTATE_HOST_IPI, host_ipi);
	HSTATE_FIELD(HSTATE_PTID, ptid);
	HSTATE_FIELD(HSTATE_FAKE_SUSPEND, fake_suspend);
	HSTATE_FIELD(HSTATE_MMCR0, host_mmcr[0]);
	HSTATE_FIELD(HSTATE_MMCR1, host_mmcr[1]);
	HSTATE_FIELD(HSTATE_MMCRA, host_mmcr[2]);
	HSTATE_FIELD(HSTATE_SIAR, host_mmcr[3]);
	HSTATE_FIELD(HSTATE_SDAR, host_mmcr[4]);
	HSTATE_FIELD(HSTATE_MMCR2, host_mmcr[5]);
	HSTATE_FIELD(HSTATE_SIER, host_mmcr[6]);
	HSTATE_FIELD(HSTATE_MMCR3, host_mmcr[7]);
	HSTATE_FIELD(HSTATE_SIER2, host_mmcr[8]);
	HSTATE_FIELD(HSTATE_SIER3, host_mmcr[9]);
	HSTATE_FIELD(HSTATE_PMC1, host_pmc[0]);
	HSTATE_FIELD(HSTATE_PMC2, host_pmc[1]);
	HSTATE_FIELD(HSTATE_PMC3, host_pmc[2]);
	HSTATE_FIELD(HSTATE_PMC4, host_pmc[3]);
	HSTATE_FIELD(HSTATE_PMC5, host_pmc[4]);
	HSTATE_FIELD(HSTATE_PMC6, host_pmc[5]);
	HSTATE_FIELD(HSTATE_PURR, host_purr);
	HSTATE_FIELD(HSTATE_SPURR, host_spurr);
	HSTATE_FIELD(HSTATE_DSCR, host_dscr);
	HSTATE_FIELD(HSTATE_DABR, dabr);
	HSTATE_FIELD(HSTATE_DECEXP, dec_expires);
	HSTATE_FIELD(HSTATE_SPLIT_MODE, kvm_split_mode);
	DEFINE(IPI_PRIORITY, IPI_PRIORITY);
	OFFSET(KVM_SPLIT_RPR, kvm_split_mode, rpr);
	OFFSET(KVM_SPLIT_PMMAR, kvm_split_mode, pmmar);
	OFFSET(KVM_SPLIT_LDBAR, kvm_split_mode, ldbar);
	OFFSET(KVM_SPLIT_DO_NAP, kvm_split_mode, करो_nap);
	OFFSET(KVM_SPLIT_NAPPED, kvm_split_mode, napped);
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	HSTATE_FIELD(HSTATE_CFAR, cfar);
	HSTATE_FIELD(HSTATE_PPR, ppr);
	HSTATE_FIELD(HSTATE_HOST_FSCR, host_fscr);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अन्यथा /* CONFIG_PPC_BOOK3S */
	OFFSET(VCPU_CR, kvm_vcpu, arch.regs.ccr);
	OFFSET(VCPU_XER, kvm_vcpu, arch.regs.xer);
	OFFSET(VCPU_LR, kvm_vcpu, arch.regs.link);
	OFFSET(VCPU_CTR, kvm_vcpu, arch.regs.ctr);
	OFFSET(VCPU_PC, kvm_vcpu, arch.regs.nip);
	OFFSET(VCPU_SPRG9, kvm_vcpu, arch.sprg9);
	OFFSET(VCPU_LAST_INST, kvm_vcpu, arch.last_inst);
	OFFSET(VCPU_FAULT_DEAR, kvm_vcpu, arch.fault_dear);
	OFFSET(VCPU_FAULT_ESR, kvm_vcpu, arch.fault_esr);
	OFFSET(VCPU_CRIT_SAVE, kvm_vcpu, arch.crit_save);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */
#पूर्ण_अगर /* CONFIG_KVM */

#अगर_घोषित CONFIG_KVM_GUEST
	OFFSET(KVM_MAGIC_SCRATCH1, kvm_vcpu_arch_shared, scratch1);
	OFFSET(KVM_MAGIC_SCRATCH2, kvm_vcpu_arch_shared, scratch2);
	OFFSET(KVM_MAGIC_SCRATCH3, kvm_vcpu_arch_shared, scratch3);
	OFFSET(KVM_MAGIC_INT, kvm_vcpu_arch_shared, पूर्णांक_pending);
	OFFSET(KVM_MAGIC_MSR, kvm_vcpu_arch_shared, msr);
	OFFSET(KVM_MAGIC_CRITICAL, kvm_vcpu_arch_shared, critical);
	OFFSET(KVM_MAGIC_SR, kvm_vcpu_arch_shared, sr);
#पूर्ण_अगर

#अगर_घोषित CONFIG_44x
	DEFINE(PGD_T_LOG2, PGD_T_LOG2);
	DEFINE(PTE_T_LOG2, PTE_T_LOG2);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	DEFINE(TLBCAM_SIZE, माप(काष्ठा tlbcam));
	OFFSET(TLBCAM_MAS0, tlbcam, MAS0);
	OFFSET(TLBCAM_MAS1, tlbcam, MAS1);
	OFFSET(TLBCAM_MAS2, tlbcam, MAS2);
	OFFSET(TLBCAM_MAS3, tlbcam, MAS3);
	OFFSET(TLBCAM_MAS7, tlbcam, MAS7);
#पूर्ण_अगर

#अगर defined(CONFIG_KVM) && defined(CONFIG_SPE)
	OFFSET(VCPU_EVR, kvm_vcpu, arch.evr[0]);
	OFFSET(VCPU_ACC, kvm_vcpu, arch.acc);
	OFFSET(VCPU_SPEFSCR, kvm_vcpu, arch.spefscr);
	OFFSET(VCPU_HOST_SPEFSCR, kvm_vcpu, arch.host_spefscr);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	OFFSET(VCPU_HOST_MAS4, kvm_vcpu, arch.host_mas4);
	OFFSET(VCPU_HOST_MAS6, kvm_vcpu, arch.host_mas6);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_XICS
	DEFINE(VCPU_XIVE_SAVED_STATE, दुरत्व(काष्ठा kvm_vcpu,
					       arch.xive_saved_state));
	DEFINE(VCPU_XIVE_CAM_WORD, दुरत्व(काष्ठा kvm_vcpu,
					    arch.xive_cam_word));
	DEFINE(VCPU_XIVE_PUSHED, दुरत्व(काष्ठा kvm_vcpu, arch.xive_pushed));
	DEFINE(VCPU_XIVE_ESC_ON, दुरत्व(काष्ठा kvm_vcpu, arch.xive_esc_on));
	DEFINE(VCPU_XIVE_ESC_RADDR, दुरत्व(काष्ठा kvm_vcpu, arch.xive_esc_raddr));
	DEFINE(VCPU_XIVE_ESC_VADDR, दुरत्व(काष्ठा kvm_vcpu, arch.xive_esc_vaddr));
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_EXIT_TIMING
	OFFSET(VCPU_TIMING_EXIT_TBU, kvm_vcpu, arch.timing_निकास.tv32.tbu);
	OFFSET(VCPU_TIMING_EXIT_TBL, kvm_vcpu, arch.timing_निकास.tv32.tbl);
	OFFSET(VCPU_TIMING_LAST_ENTER_TBU, kvm_vcpu, arch.timing_last_enter.tv32.tbu);
	OFFSET(VCPU_TIMING_LAST_ENTER_TBL, kvm_vcpu, arch.timing_last_enter.tv32.tbl);
#पूर्ण_अगर

	DEFINE(PPC_DBELL_SERVER, PPC_DBELL_SERVER);
	DEFINE(PPC_DBELL_MSGTYPE, PPC_DBELL_MSGTYPE);

#अगर_घोषित CONFIG_PPC_8xx
	DEFINE(VIRT_IMMR_BASE, (u64)__fix_to_virt(FIX_IMMR_BASE));
#पूर्ण_अगर

#अगर_घोषित CONFIG_XMON
	DEFINE(BPT_SIZE, BPT_SIZE);
#पूर्ण_अगर

	वापस 0;
पूर्ण
