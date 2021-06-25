<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1995-2003 Russell King
 *               2001-2002 Keith Owens
 *     
 * Generate definitions needed by assembly language modules.
 * This code generates raw यंत्र output which is post-processed to extract
 * and क्रमmat the required data.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kexec-पूर्णांकernal.h>
#समावेश <यंत्र/glue-df.h>
#समावेश <यंत्र/glue-pf.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mpu.h>
#समावेश <यंत्र/procinfo.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/arm-smccc.h>
#समावेश "signal.h"

/*
 * Make sure that the compiler and target are compatible.
 */
#अगर defined(__APCS_26__)
#त्रुटि Sorry, your compiler tarमाला_लो APCS-26 but this kernel requires APCS-32
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
  DEFINE(TSK_ACTIVE_MM,		दुरत्व(काष्ठा task_काष्ठा, active_mm));
#अगर_घोषित CONFIG_STACKPROTECTOR
  DEFINE(TSK_STACK_CANARY,	दुरत्व(काष्ठा task_काष्ठा, stack_canary));
#पूर्ण_अगर
  BLANK();
  DEFINE(TI_FLAGS,		दुरत्व(काष्ठा thपढ़ो_info, flags));
  DEFINE(TI_PREEMPT,		दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
  DEFINE(TI_ADDR_LIMIT,		दुरत्व(काष्ठा thपढ़ो_info, addr_limit));
  DEFINE(TI_TASK,		दुरत्व(काष्ठा thपढ़ो_info, task));
  DEFINE(TI_CPU,		दुरत्व(काष्ठा thपढ़ो_info, cpu));
  DEFINE(TI_CPU_DOMAIN,		दुरत्व(काष्ठा thपढ़ो_info, cpu_करोमुख्य));
  DEFINE(TI_CPU_SAVE,		दुरत्व(काष्ठा thपढ़ो_info, cpu_context));
  DEFINE(TI_USED_CP,		दुरत्व(काष्ठा thपढ़ो_info, used_cp));
  DEFINE(TI_TP_VALUE,		दुरत्व(काष्ठा thपढ़ो_info, tp_value));
  DEFINE(TI_FPSTATE,		दुरत्व(काष्ठा thपढ़ो_info, fpstate));
#अगर_घोषित CONFIG_VFP
  DEFINE(TI_VFPSTATE,		दुरत्व(काष्ठा thपढ़ो_info, vfpstate));
#अगर_घोषित CONFIG_SMP
  DEFINE(VFP_CPU,		दुरत्व(जोड़ vfp_state, hard.cpu));
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_THUMBEE
  DEFINE(TI_THUMBEE_STATE,	दुरत्व(काष्ठा thपढ़ो_info, thumbee_state));
#पूर्ण_अगर
#अगर_घोषित CONFIG_IWMMXT
  DEFINE(TI_IWMMXT_STATE,	दुरत्व(काष्ठा thपढ़ो_info, fpstate.iwmmxt));
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRUNCH
  DEFINE(TI_CRUNCH_STATE,	दुरत्व(काष्ठा thपढ़ो_info, crunchstate));
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKPROTECTOR_PER_TASK
  DEFINE(TI_STACK_CANARY,	दुरत्व(काष्ठा thपढ़ो_info, stack_canary));
#पूर्ण_अगर
  DEFINE(THREAD_SZ_ORDER,	THREAD_SIZE_ORDER);
  BLANK();
  DEFINE(S_R0,			दुरत्व(काष्ठा pt_regs, ARM_r0));
  DEFINE(S_R1,			दुरत्व(काष्ठा pt_regs, ARM_r1));
  DEFINE(S_R2,			दुरत्व(काष्ठा pt_regs, ARM_r2));
  DEFINE(S_R3,			दुरत्व(काष्ठा pt_regs, ARM_r3));
  DEFINE(S_R4,			दुरत्व(काष्ठा pt_regs, ARM_r4));
  DEFINE(S_R5,			दुरत्व(काष्ठा pt_regs, ARM_r5));
  DEFINE(S_R6,			दुरत्व(काष्ठा pt_regs, ARM_r6));
  DEFINE(S_R7,			दुरत्व(काष्ठा pt_regs, ARM_r7));
  DEFINE(S_R8,			दुरत्व(काष्ठा pt_regs, ARM_r8));
  DEFINE(S_R9,			दुरत्व(काष्ठा pt_regs, ARM_r9));
  DEFINE(S_R10,			दुरत्व(काष्ठा pt_regs, ARM_r10));
  DEFINE(S_FP,			दुरत्व(काष्ठा pt_regs, ARM_fp));
  DEFINE(S_IP,			दुरत्व(काष्ठा pt_regs, ARM_ip));
  DEFINE(S_SP,			दुरत्व(काष्ठा pt_regs, ARM_sp));
  DEFINE(S_LR,			दुरत्व(काष्ठा pt_regs, ARM_lr));
  DEFINE(S_PC,			दुरत्व(काष्ठा pt_regs, ARM_pc));
  DEFINE(S_PSR,			दुरत्व(काष्ठा pt_regs, ARM_cpsr));
  DEFINE(S_OLD_R0,		दुरत्व(काष्ठा pt_regs, ARM_ORIG_r0));
  DEFINE(PT_REGS_SIZE,		माप(काष्ठा pt_regs));
  DEFINE(SVC_DACR,		दुरत्व(काष्ठा svc_pt_regs, dacr));
  DEFINE(SVC_ADDR_LIMIT,	दुरत्व(काष्ठा svc_pt_regs, addr_limit));
  DEFINE(SVC_REGS_SIZE,		माप(काष्ठा svc_pt_regs));
  BLANK();
  DEFINE(SIGFRAME_RC3_OFFSET,	दुरत्व(काष्ठा sigframe, retcode[3]));
  DEFINE(RT_SIGFRAME_RC3_OFFSET, दुरत्व(काष्ठा rt_sigframe, sig.retcode[3]));
  BLANK();
#अगर_घोषित CONFIG_CACHE_L2X0
  DEFINE(L2X0_R_PHY_BASE,	दुरत्व(काष्ठा l2x0_regs, phy_base));
  DEFINE(L2X0_R_AUX_CTRL,	दुरत्व(काष्ठा l2x0_regs, aux_ctrl));
  DEFINE(L2X0_R_TAG_LATENCY,	दुरत्व(काष्ठा l2x0_regs, tag_latency));
  DEFINE(L2X0_R_DATA_LATENCY,	दुरत्व(काष्ठा l2x0_regs, data_latency));
  DEFINE(L2X0_R_FILTER_START,	दुरत्व(काष्ठा l2x0_regs, filter_start));
  DEFINE(L2X0_R_FILTER_END,	दुरत्व(काष्ठा l2x0_regs, filter_end));
  DEFINE(L2X0_R_PREFETCH_CTRL,	दुरत्व(काष्ठा l2x0_regs, prefetch_ctrl));
  DEFINE(L2X0_R_PWR_CTRL,	दुरत्व(काष्ठा l2x0_regs, pwr_ctrl));
  BLANK();
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_ASID
  DEFINE(MM_CONTEXT_ID,		दुरत्व(काष्ठा mm_काष्ठा, context.id.counter));
  BLANK();
#पूर्ण_अगर
  DEFINE(VMA_VM_MM,		दुरत्व(काष्ठा vm_area_काष्ठा, vm_mm));
  DEFINE(VMA_VM_FLAGS,		दुरत्व(काष्ठा vm_area_काष्ठा, vm_flags));
  BLANK();
  DEFINE(VM_EXEC,	       	VM_EXEC);
  BLANK();
  DEFINE(PAGE_SZ,	       	PAGE_SIZE);
  BLANK();
  DEFINE(SYS_ERROR0,		0x9f0000);
  BLANK();
  DEFINE(SIZखातापूर्ण_MACHINE_DESC,	माप(काष्ठा machine_desc));
  DEFINE(MACHINFO_TYPE,		दुरत्व(काष्ठा machine_desc, nr));
  DEFINE(MACHINFO_NAME,		दुरत्व(काष्ठा machine_desc, name));
  BLANK();
  DEFINE(PROC_INFO_SZ,		माप(काष्ठा proc_info_list));
  DEFINE(PROCINFO_INITFUNC,	दुरत्व(काष्ठा proc_info_list, __cpu_flush));
  DEFINE(PROCINFO_MM_MMUFLAGS,	दुरत्व(काष्ठा proc_info_list, __cpu_mm_mmu_flags));
  DEFINE(PROCINFO_IO_MMUFLAGS,	दुरत्व(काष्ठा proc_info_list, __cpu_io_mmu_flags));
  BLANK();
#अगर_घोषित MULTI_DABORT
  DEFINE(PROCESSOR_DABT_FUNC,	दुरत्व(काष्ठा processor, _data_पात));
#पूर्ण_अगर
#अगर_घोषित MULTI_PABORT
  DEFINE(PROCESSOR_PABT_FUNC,	दुरत्व(काष्ठा processor, _prefetch_पात));
#पूर्ण_अगर
#अगर_घोषित MULTI_CPU
  DEFINE(CPU_SLEEP_SIZE,	दुरत्व(काष्ठा processor, suspend_size));
  DEFINE(CPU_DO_SUSPEND,	दुरत्व(काष्ठा processor, करो_suspend));
  DEFINE(CPU_DO_RESUME,		दुरत्व(काष्ठा processor, करो_resume));
#पूर्ण_अगर
#अगर_घोषित MULTI_CACHE
  DEFINE(CACHE_FLUSH_KERN_ALL,	दुरत्व(काष्ठा cpu_cache_fns, flush_kern_all));
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_CPU_SUSPEND
  DEFINE(SLEEP_SAVE_SP_SZ,	माप(काष्ठा sleep_save_sp));
  DEFINE(SLEEP_SAVE_SP_PHYS,	दुरत्व(काष्ठा sleep_save_sp, save_ptr_stash_phys));
  DEFINE(SLEEP_SAVE_SP_VIRT,	दुरत्व(काष्ठा sleep_save_sp, save_ptr_stash));
#पूर्ण_अगर
  DEFINE(ARM_SMCCC_QUIRK_ID_OFFS,	दुरत्व(काष्ठा arm_smccc_quirk, id));
  DEFINE(ARM_SMCCC_QUIRK_STATE_OFFS,	दुरत्व(काष्ठा arm_smccc_quirk, state));
  BLANK();
  DEFINE(DMA_BIसूचीECTIONAL,	DMA_BIसूचीECTIONAL);
  DEFINE(DMA_TO_DEVICE,		DMA_TO_DEVICE);
  DEFINE(DMA_FROM_DEVICE,	DMA_FROM_DEVICE);
  BLANK();
  DEFINE(CACHE_WRITEBACK_ORDER, __CACHE_WRITEBACK_ORDER);
  DEFINE(CACHE_WRITEBACK_GRANULE, __CACHE_WRITEBACK_GRANULE);
  BLANK();
#अगर_घोषित CONFIG_VDSO
  DEFINE(VDSO_DATA_SIZE,	माप(जोड़ vdso_data_store));
#पूर्ण_अगर
  BLANK();
#अगर_घोषित CONFIG_ARM_MPU
  DEFINE(MPU_RNG_INFO_RNGS,	दुरत्व(काष्ठा mpu_rgn_info, rgns));
  DEFINE(MPU_RNG_INFO_USED,	दुरत्व(काष्ठा mpu_rgn_info, used));

  DEFINE(MPU_RNG_SIZE,		माप(काष्ठा mpu_rgn));
  DEFINE(MPU_RGN_DRBAR,	दुरत्व(काष्ठा mpu_rgn, drbar));
  DEFINE(MPU_RGN_DRSR,	दुरत्व(काष्ठा mpu_rgn, drsr));
  DEFINE(MPU_RGN_DRACR,	दुरत्व(काष्ठा mpu_rgn, dracr));
  DEFINE(MPU_RGN_PRBAR,	दुरत्व(काष्ठा mpu_rgn, prbar));
  DEFINE(MPU_RGN_PRLAR,	दुरत्व(काष्ठा mpu_rgn, prlar));
#पूर्ण_अगर
  DEFINE(KEXEC_START_ADDR,	दुरत्व(काष्ठा kexec_relocate_data, kexec_start_address));
  DEFINE(KEXEC_INसूची_PAGE,	दुरत्व(काष्ठा kexec_relocate_data, kexec_indirection_page));
  DEFINE(KEXEC_MACH_TYPE,	दुरत्व(काष्ठा kexec_relocate_data, kexec_mach_type));
  DEFINE(KEXEC_R2,		दुरत्व(काष्ठा kexec_relocate_data, kexec_r2));
  वापस 0; 
पूर्ण
