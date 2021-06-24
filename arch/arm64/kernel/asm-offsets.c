<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/यंत्र-offsets.c
 *
 * Copyright (C) 1995-2003 Russell King
 *               2001-2002 Keith Owens
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/arm_sdei.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/preempt.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/संकेत32.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/arm-smccc.h>

पूर्णांक मुख्य(व्योम)
अणु
  DEFINE(TSK_ACTIVE_MM,		दुरत्व(काष्ठा task_काष्ठा, active_mm));
  BLANK();
  DEFINE(TSK_TI_FLAGS,		दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.flags));
  DEFINE(TSK_TI_PREEMPT,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.preempt_count));
#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
  DEFINE(TSK_TI_TTBR0,		दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.ttbr0));
#पूर्ण_अगर
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
  DEFINE(TSK_TI_SCS_BASE,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.scs_base));
  DEFINE(TSK_TI_SCS_SP,		दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.scs_sp));
#पूर्ण_अगर
  DEFINE(TSK_STACK,		दुरत्व(काष्ठा task_काष्ठा, stack));
#अगर_घोषित CONFIG_STACKPROTECTOR
  DEFINE(TSK_STACK_CANARY,	दुरत्व(काष्ठा task_काष्ठा, stack_canary));
#पूर्ण_अगर
  BLANK();
  DEFINE(THREAD_CPU_CONTEXT,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.cpu_context));
  DEFINE(THREAD_SCTLR_USER,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.sctlr_user));
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
  DEFINE(THREAD_KEYS_USER,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.keys_user));
  DEFINE(THREAD_KEYS_KERNEL,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.keys_kernel));
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_MTE
  DEFINE(THREAD_GCR_EL1_USER,	दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.gcr_user_excl));
#पूर्ण_अगर
  BLANK();
  DEFINE(S_X0,			दुरत्व(काष्ठा pt_regs, regs[0]));
  DEFINE(S_X2,			दुरत्व(काष्ठा pt_regs, regs[2]));
  DEFINE(S_X4,			दुरत्व(काष्ठा pt_regs, regs[4]));
  DEFINE(S_X6,			दुरत्व(काष्ठा pt_regs, regs[6]));
  DEFINE(S_X8,			दुरत्व(काष्ठा pt_regs, regs[8]));
  DEFINE(S_X10,			दुरत्व(काष्ठा pt_regs, regs[10]));
  DEFINE(S_X12,			दुरत्व(काष्ठा pt_regs, regs[12]));
  DEFINE(S_X14,			दुरत्व(काष्ठा pt_regs, regs[14]));
  DEFINE(S_X16,			दुरत्व(काष्ठा pt_regs, regs[16]));
  DEFINE(S_X18,			दुरत्व(काष्ठा pt_regs, regs[18]));
  DEFINE(S_X20,			दुरत्व(काष्ठा pt_regs, regs[20]));
  DEFINE(S_X22,			दुरत्व(काष्ठा pt_regs, regs[22]));
  DEFINE(S_X24,			दुरत्व(काष्ठा pt_regs, regs[24]));
  DEFINE(S_X26,			दुरत्व(काष्ठा pt_regs, regs[26]));
  DEFINE(S_X28,			दुरत्व(काष्ठा pt_regs, regs[28]));
  DEFINE(S_FP,			दुरत्व(काष्ठा pt_regs, regs[29]));
  DEFINE(S_LR,			दुरत्व(काष्ठा pt_regs, regs[30]));
  DEFINE(S_SP,			दुरत्व(काष्ठा pt_regs, sp));
  DEFINE(S_PSTATE,		दुरत्व(काष्ठा pt_regs, pstate));
  DEFINE(S_PC,			दुरत्व(काष्ठा pt_regs, pc));
  DEFINE(S_SYSCALLNO,		दुरत्व(काष्ठा pt_regs, syscallno));
  DEFINE(S_SDEI_TTBR1,		दुरत्व(काष्ठा pt_regs, sdei_ttbr1));
  DEFINE(S_PMR_SAVE,		दुरत्व(काष्ठा pt_regs, pmr_save));
  DEFINE(S_STACKFRAME,		दुरत्व(काष्ठा pt_regs, stackframe));
  DEFINE(PT_REGS_SIZE,		माप(काष्ठा pt_regs));
  BLANK();
#अगर_घोषित CONFIG_COMPAT
  DEFINE(COMPAT_SIGFRAME_REGS_OFFSET,		दुरत्व(काष्ठा compat_sigframe, uc.uc_mcontext.arm_r0));
  DEFINE(COMPAT_RT_SIGFRAME_REGS_OFFSET,	दुरत्व(काष्ठा compat_rt_sigframe, sig.uc.uc_mcontext.arm_r0));
  BLANK();
#पूर्ण_अगर
  DEFINE(MM_CONTEXT_ID,		दुरत्व(काष्ठा mm_काष्ठा, context.id.counter));
  BLANK();
  DEFINE(VMA_VM_MM,		दुरत्व(काष्ठा vm_area_काष्ठा, vm_mm));
  DEFINE(VMA_VM_FLAGS,		दुरत्व(काष्ठा vm_area_काष्ठा, vm_flags));
  BLANK();
  DEFINE(VM_EXEC,	       	VM_EXEC);
  BLANK();
  DEFINE(PAGE_SZ,	       	PAGE_SIZE);
  BLANK();
  DEFINE(DMA_TO_DEVICE,		DMA_TO_DEVICE);
  DEFINE(DMA_FROM_DEVICE,	DMA_FROM_DEVICE);
  BLANK();
  DEFINE(PREEMPT_DISABLE_OFFSET, PREEMPT_DISABLE_OFFSET);
  DEFINE(SOFTIRQ_SHIFT, SOFTIRQ_SHIFT);
  DEFINE(IRQ_CPUSTAT_SOFTIRQ_PENDING, दुरत्व(irq_cpustat_t, __softirq_pending));
  BLANK();
  DEFINE(CPU_BOOT_STACK,	दुरत्व(काष्ठा secondary_data, stack));
  DEFINE(CPU_BOOT_TASK,		दुरत्व(काष्ठा secondary_data, task));
  BLANK();
  DEFINE(FTR_OVR_VAL_OFFSET,	दुरत्व(काष्ठा arm64_ftr_override, val));
  DEFINE(FTR_OVR_MASK_OFFSET,	दुरत्व(काष्ठा arm64_ftr_override, mask));
  BLANK();
#अगर_घोषित CONFIG_KVM
  DEFINE(VCPU_CONTEXT,		दुरत्व(काष्ठा kvm_vcpu, arch.ctxt));
  DEFINE(VCPU_FAULT_DISR,	दुरत्व(काष्ठा kvm_vcpu, arch.fault.disr_el1));
  DEFINE(VCPU_WORKAROUND_FLAGS,	दुरत्व(काष्ठा kvm_vcpu, arch.workaround_flags));
  DEFINE(VCPU_HCR_EL2,		दुरत्व(काष्ठा kvm_vcpu, arch.hcr_el2));
  DEFINE(CPU_USER_PT_REGS,	दुरत्व(काष्ठा kvm_cpu_context, regs));
  DEFINE(CPU_APIAKEYLO_EL1,	दुरत्व(काष्ठा kvm_cpu_context, sys_regs[APIAKEYLO_EL1]));
  DEFINE(CPU_APIBKEYLO_EL1,	दुरत्व(काष्ठा kvm_cpu_context, sys_regs[APIBKEYLO_EL1]));
  DEFINE(CPU_APDAKEYLO_EL1,	दुरत्व(काष्ठा kvm_cpu_context, sys_regs[APDAKEYLO_EL1]));
  DEFINE(CPU_APDBKEYLO_EL1,	दुरत्व(काष्ठा kvm_cpu_context, sys_regs[APDBKEYLO_EL1]));
  DEFINE(CPU_APGAKEYLO_EL1,	दुरत्व(काष्ठा kvm_cpu_context, sys_regs[APGAKEYLO_EL1]));
  DEFINE(HOST_CONTEXT_VCPU,	दुरत्व(काष्ठा kvm_cpu_context, __hyp_running_vcpu));
  DEFINE(HOST_DATA_CONTEXT,	दुरत्व(काष्ठा kvm_host_data, host_ctxt));
  DEFINE(NVHE_INIT_MAIR_EL2,	दुरत्व(काष्ठा kvm_nvhe_init_params, mair_el2));
  DEFINE(NVHE_INIT_TCR_EL2,	दुरत्व(काष्ठा kvm_nvhe_init_params, tcr_el2));
  DEFINE(NVHE_INIT_TPIDR_EL2,	दुरत्व(काष्ठा kvm_nvhe_init_params, tpidr_el2));
  DEFINE(NVHE_INIT_STACK_HYP_VA,	दुरत्व(काष्ठा kvm_nvhe_init_params, stack_hyp_va));
  DEFINE(NVHE_INIT_PGD_PA,	दुरत्व(काष्ठा kvm_nvhe_init_params, pgd_pa));
  DEFINE(NVHE_INIT_HCR_EL2,	दुरत्व(काष्ठा kvm_nvhe_init_params, hcr_el2));
  DEFINE(NVHE_INIT_VTTBR,	दुरत्व(काष्ठा kvm_nvhe_init_params, vttbr));
  DEFINE(NVHE_INIT_VTCR,	दुरत्व(काष्ठा kvm_nvhe_init_params, vtcr));
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_PM
  DEFINE(CPU_CTX_SP,		दुरत्व(काष्ठा cpu_suspend_ctx, sp));
  DEFINE(MPIDR_HASH_MASK,	दुरत्व(काष्ठा mpidr_hash, mask));
  DEFINE(MPIDR_HASH_SHIFTS,	दुरत्व(काष्ठा mpidr_hash, shअगरt_aff));
  DEFINE(SLEEP_STACK_DATA_SYSTEM_REGS,	दुरत्व(काष्ठा sleep_stack_data, प्रणाली_regs));
  DEFINE(SLEEP_STACK_DATA_CALLEE_REGS,	दुरत्व(काष्ठा sleep_stack_data, callee_saved_regs));
#पूर्ण_अगर
  DEFINE(ARM_SMCCC_RES_X0_OFFS,		दुरत्व(काष्ठा arm_smccc_res, a0));
  DEFINE(ARM_SMCCC_RES_X2_OFFS,		दुरत्व(काष्ठा arm_smccc_res, a2));
  DEFINE(ARM_SMCCC_QUIRK_ID_OFFS,	दुरत्व(काष्ठा arm_smccc_quirk, id));
  DEFINE(ARM_SMCCC_QUIRK_STATE_OFFS,	दुरत्व(काष्ठा arm_smccc_quirk, state));
  BLANK();
  DEFINE(HIBERN_PBE_ORIG,	दुरत्व(काष्ठा pbe, orig_address));
  DEFINE(HIBERN_PBE_ADDR,	दुरत्व(काष्ठा pbe, address));
  DEFINE(HIBERN_PBE_NEXT,	दुरत्व(काष्ठा pbe, next));
  DEFINE(ARM64_FTR_SYSVAL,	दुरत्व(काष्ठा arm64_ftr_reg, sys_val));
  BLANK();
#अगर_घोषित CONFIG_UNMAP_KERNEL_AT_EL0
  DEFINE(TRAMP_VALIAS,		TRAMP_VALIAS);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_SDE_INTERFACE
  DEFINE(SDEI_EVENT_INTREGS,	दुरत्व(काष्ठा sdei_रेजिस्टरed_event, पूर्णांकerrupted_regs));
  DEFINE(SDEI_EVENT_PRIORITY,	दुरत्व(काष्ठा sdei_रेजिस्टरed_event, priority));
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
  DEFINE(PTRAUTH_USER_KEY_APIA,		दुरत्व(काष्ठा ptrauth_keys_user, apia));
  DEFINE(PTRAUTH_KERNEL_KEY_APIA,	दुरत्व(काष्ठा ptrauth_keys_kernel, apia));
  BLANK();
#पूर्ण_अगर
  वापस 0;
पूर्ण
