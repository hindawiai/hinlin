<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 - Google LLC
 * Author: David Brazdil <dbrazdil@google.com>
 */

#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>
#समावेश <uapi/linux/psci.h>

#समावेश <nvhe/memory.h>
#समावेश <nvhe/trap_handler.h>

व्योम kvm_hyp_cpu_entry(अचिन्हित दीर्घ r0);
व्योम kvm_hyp_cpu_resume(अचिन्हित दीर्घ r0);

व्योम __noवापस __host_enter(काष्ठा kvm_cpu_context *host_ctxt);

/* Config options set by the host. */
काष्ठा kvm_host_psci_config __ro_after_init kvm_host_psci_config;

#घोषणा INVALID_CPU_ID	अच_पूर्णांक_उच्च

काष्ठा psci_boot_args अणु
	atomic_t lock;
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ r0;
पूर्ण;

#घोषणा PSCI_BOOT_ARGS_UNLOCKED		0
#घोषणा PSCI_BOOT_ARGS_LOCKED		1

#घोषणा PSCI_BOOT_ARGS_INIT					\
	((काष्ठा psci_boot_args)अणु				\
		.lock = ATOMIC_INIT(PSCI_BOOT_ARGS_UNLOCKED),	\
	पूर्ण)

अटल DEFINE_PER_CPU(काष्ठा psci_boot_args, cpu_on_args) = PSCI_BOOT_ARGS_INIT;
अटल DEFINE_PER_CPU(काष्ठा psci_boot_args, suspend_args) = PSCI_BOOT_ARGS_INIT;

#घोषणा	is_psci_0_1(what, func_id)					\
	(kvm_host_psci_config.psci_0_1_ ## what ## _implemented &&	\
	 (func_id) == kvm_host_psci_config.function_ids_0_1.what)

अटल bool is_psci_0_1_call(u64 func_id)
अणु
	वापस (is_psci_0_1(cpu_suspend, func_id) ||
		is_psci_0_1(cpu_on, func_id) ||
		is_psci_0_1(cpu_off, func_id) ||
		is_psci_0_1(migrate, func_id));
पूर्ण

अटल bool is_psci_0_2_call(u64 func_id)
अणु
	/* SMCCC reserves IDs 0x00-1F with the given 32/64-bit base क्रम PSCI. */
	वापस (PSCI_0_2_FN(0) <= func_id && func_id <= PSCI_0_2_FN(31)) ||
	       (PSCI_0_2_FN64(0) <= func_id && func_id <= PSCI_0_2_FN64(31));
पूर्ण

अटल अचिन्हित दीर्घ psci_call(अचिन्हित दीर्घ fn, अचिन्हित दीर्घ arg0,
			       अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_1_1_smc(fn, arg0, arg1, arg2, &res);
	वापस res.a0;
पूर्ण

अटल अचिन्हित दीर्घ psci_क्रमward(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	वापस psci_call(cpu_reg(host_ctxt, 0), cpu_reg(host_ctxt, 1),
			 cpu_reg(host_ctxt, 2), cpu_reg(host_ctxt, 3));
पूर्ण

अटल अचिन्हित पूर्णांक find_cpu_id(u64 mpidr)
अणु
	अचिन्हित पूर्णांक i;

	/* Reject invalid MPIDRs */
	अगर (mpidr & ~MPIDR_HWID_BITMASK)
		वापस INVALID_CPU_ID;

	क्रम (i = 0; i < NR_CPUS; i++) अणु
		अगर (cpu_logical_map(i) == mpidr)
			वापस i;
	पूर्ण

	वापस INVALID_CPU_ID;
पूर्ण

अटल __always_अंतरभूत bool try_acquire_boot_args(काष्ठा psci_boot_args *args)
अणु
	वापस atomic_cmpxchg_acquire(&args->lock,
				      PSCI_BOOT_ARGS_UNLOCKED,
				      PSCI_BOOT_ARGS_LOCKED) ==
		PSCI_BOOT_ARGS_UNLOCKED;
पूर्ण

अटल __always_अंतरभूत व्योम release_boot_args(काष्ठा psci_boot_args *args)
अणु
	atomic_set_release(&args->lock, PSCI_BOOT_ARGS_UNLOCKED);
पूर्ण

अटल पूर्णांक psci_cpu_on(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(u64, mpidr, host_ctxt, 1);
	DECLARE_REG(अचिन्हित दीर्घ, pc, host_ctxt, 2);
	DECLARE_REG(अचिन्हित दीर्घ, r0, host_ctxt, 3);

	अचिन्हित पूर्णांक cpu_id;
	काष्ठा psci_boot_args *boot_args;
	काष्ठा kvm_nvhe_init_params *init_params;
	पूर्णांक ret;

	/*
	 * Find the logical CPU ID क्रम the given MPIDR. The search set is
	 * the set of CPUs that were online at the poपूर्णांक of KVM initialization.
	 * Booting other CPUs is rejected because their cpufeatures were not
	 * checked against the finalized capabilities. This could be relaxed
	 * by करोing the feature checks in hyp.
	 */
	cpu_id = find_cpu_id(mpidr);
	अगर (cpu_id == INVALID_CPU_ID)
		वापस PSCI_RET_INVALID_PARAMS;

	boot_args = per_cpu_ptr(&cpu_on_args, cpu_id);
	init_params = per_cpu_ptr(&kvm_init_params, cpu_id);

	/* Check अगर the target CPU is alपढ़ोy being booted. */
	अगर (!try_acquire_boot_args(boot_args))
		वापस PSCI_RET_ALREADY_ON;

	boot_args->pc = pc;
	boot_args->r0 = r0;
	wmb();

	ret = psci_call(func_id, mpidr,
			__hyp_pa(&kvm_hyp_cpu_entry),
			__hyp_pa(init_params));

	/* If successful, the lock will be released by the target CPU. */
	अगर (ret != PSCI_RET_SUCCESS)
		release_boot_args(boot_args);

	वापस ret;
पूर्ण

अटल पूर्णांक psci_cpu_suspend(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(u64, घातer_state, host_ctxt, 1);
	DECLARE_REG(अचिन्हित दीर्घ, pc, host_ctxt, 2);
	DECLARE_REG(अचिन्हित दीर्घ, r0, host_ctxt, 3);

	काष्ठा psci_boot_args *boot_args;
	काष्ठा kvm_nvhe_init_params *init_params;

	boot_args = this_cpu_ptr(&suspend_args);
	init_params = this_cpu_ptr(&kvm_init_params);

	/*
	 * No need to acquire a lock beक्रमe writing to boot_args because a core
	 * can only suspend itself. Racy CPU_ON calls use a separate काष्ठा.
	 */
	boot_args->pc = pc;
	boot_args->r0 = r0;

	/*
	 * Will either वापस अगर shallow sleep state, or wake up पूर्णांकo the entry
	 * poपूर्णांक अगर it is a deep sleep state.
	 */
	वापस psci_call(func_id, घातer_state,
			 __hyp_pa(&kvm_hyp_cpu_resume),
			 __hyp_pa(init_params));
पूर्ण

अटल पूर्णांक psci_प्रणाली_suspend(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(अचिन्हित दीर्घ, pc, host_ctxt, 1);
	DECLARE_REG(अचिन्हित दीर्घ, r0, host_ctxt, 2);

	काष्ठा psci_boot_args *boot_args;
	काष्ठा kvm_nvhe_init_params *init_params;

	boot_args = this_cpu_ptr(&suspend_args);
	init_params = this_cpu_ptr(&kvm_init_params);

	/*
	 * No need to acquire a lock beक्रमe writing to boot_args because a core
	 * can only suspend itself. Racy CPU_ON calls use a separate काष्ठा.
	 */
	boot_args->pc = pc;
	boot_args->r0 = r0;

	/* Will only वापस on error. */
	वापस psci_call(func_id,
			 __hyp_pa(&kvm_hyp_cpu_resume),
			 __hyp_pa(init_params), 0);
पूर्ण

यंत्रlinkage व्योम __noवापस kvm_host_psci_cpu_entry(bool is_cpu_on)
अणु
	काष्ठा psci_boot_args *boot_args;
	काष्ठा kvm_cpu_context *host_ctxt;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;

	अगर (is_cpu_on)
		boot_args = this_cpu_ptr(&cpu_on_args);
	अन्यथा
		boot_args = this_cpu_ptr(&suspend_args);

	cpu_reg(host_ctxt, 0) = boot_args->r0;
	ग_लिखो_sysreg_el2(boot_args->pc, SYS_ELR);

	अगर (is_cpu_on)
		release_boot_args(boot_args);

	__host_enter(host_ctxt);
पूर्ण

अटल अचिन्हित दीर्घ psci_0_1_handler(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	अगर (is_psci_0_1(cpu_off, func_id) || is_psci_0_1(migrate, func_id))
		वापस psci_क्रमward(host_ctxt);
	अगर (is_psci_0_1(cpu_on, func_id))
		वापस psci_cpu_on(func_id, host_ctxt);
	अगर (is_psci_0_1(cpu_suspend, func_id))
		वापस psci_cpu_suspend(func_id, host_ctxt);

	वापस PSCI_RET_NOT_SUPPORTED;
पूर्ण

अटल अचिन्हित दीर्घ psci_0_2_handler(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	चयन (func_id) अणु
	हाल PSCI_0_2_FN_PSCI_VERSION:
	हाल PSCI_0_2_FN_CPU_OFF:
	हाल PSCI_0_2_FN64_AFFINITY_INFO:
	हाल PSCI_0_2_FN64_MIGRATE:
	हाल PSCI_0_2_FN_MIGRATE_INFO_TYPE:
	हाल PSCI_0_2_FN64_MIGRATE_INFO_UP_CPU:
		वापस psci_क्रमward(host_ctxt);
	/*
	 * SYSTEM_OFF/RESET should not वापस according to the spec.
	 * Allow it so as to stay robust to broken firmware.
	 */
	हाल PSCI_0_2_FN_SYSTEM_OFF:
	हाल PSCI_0_2_FN_SYSTEM_RESET:
		वापस psci_क्रमward(host_ctxt);
	हाल PSCI_0_2_FN64_CPU_SUSPEND:
		वापस psci_cpu_suspend(func_id, host_ctxt);
	हाल PSCI_0_2_FN64_CPU_ON:
		वापस psci_cpu_on(func_id, host_ctxt);
	शेष:
		वापस PSCI_RET_NOT_SUPPORTED;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ psci_1_0_handler(u64 func_id, काष्ठा kvm_cpu_context *host_ctxt)
अणु
	चयन (func_id) अणु
	हाल PSCI_1_0_FN_PSCI_FEATURES:
	हाल PSCI_1_0_FN_SET_SUSPEND_MODE:
	हाल PSCI_1_1_FN64_SYSTEM_RESET2:
		वापस psci_क्रमward(host_ctxt);
	हाल PSCI_1_0_FN64_SYSTEM_SUSPEND:
		वापस psci_प्रणाली_suspend(func_id, host_ctxt);
	शेष:
		वापस psci_0_2_handler(func_id, host_ctxt);
	पूर्ण
पूर्ण

bool kvm_host_psci_handler(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(u64, func_id, host_ctxt, 0);
	अचिन्हित दीर्घ ret;

	चयन (kvm_host_psci_config.version) अणु
	हाल PSCI_VERSION(0, 1):
		अगर (!is_psci_0_1_call(func_id))
			वापस false;
		ret = psci_0_1_handler(func_id, host_ctxt);
		अवरोध;
	हाल PSCI_VERSION(0, 2):
		अगर (!is_psci_0_2_call(func_id))
			वापस false;
		ret = psci_0_2_handler(func_id, host_ctxt);
		अवरोध;
	शेष:
		अगर (!is_psci_0_2_call(func_id))
			वापस false;
		ret = psci_1_0_handler(func_id, host_ctxt);
		अवरोध;
	पूर्ण

	cpu_reg(host_ctxt, 0) = ret;
	cpu_reg(host_ctxt, 1) = 0;
	cpu_reg(host_ctxt, 2) = 0;
	cpu_reg(host_ctxt, 3) = 0;
	वापस true;
पूर्ण
