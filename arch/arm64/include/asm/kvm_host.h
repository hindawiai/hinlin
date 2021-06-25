<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/include/यंत्र/kvm_host.h:
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#अगर_अघोषित __ARM64_KVM_HOST_H__
#घोषणा __ARM64_KVM_HOST_H__

#समावेश <linux/arm-smccc.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/percpu.h>
#समावेश <linux/psci.h>
#समावेश <यंत्र/arch_gicv3.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/thपढ़ो_info.h>

#घोषणा __KVM_HAVE_ARCH_INTC_INITIALIZED

#घोषणा KVM_HALT_POLL_NS_DEFAULT 500000

#समावेश <kvm/arm_vgic.h>
#समावेश <kvm/arm_arch_समयr.h>
#समावेश <kvm/arm_pmu.h>

#घोषणा KVM_MAX_VCPUS VGIC_V3_MAX_CPUS

#घोषणा KVM_VCPU_MAX_FEATURES 7

#घोषणा KVM_REQ_SLEEP \
	KVM_ARCH_REQ_FLAGS(0, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_IRQ_PENDING	KVM_ARCH_REQ(1)
#घोषणा KVM_REQ_VCPU_RESET	KVM_ARCH_REQ(2)
#घोषणा KVM_REQ_RECORD_STEAL	KVM_ARCH_REQ(3)
#घोषणा KVM_REQ_RELOAD_GICv4	KVM_ARCH_REQ(4)

#घोषणा KVM_सूचीTY_LOG_MANUAL_CAPS   (KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE | \
				     KVM_सूचीTY_LOG_INITIALLY_SET)

/*
 * Mode of operation configurable with kvm-arm.mode early param.
 * See Documentation/admin-guide/kernel-parameters.txt क्रम more inक्रमmation.
 */
क्रमागत kvm_mode अणु
	KVM_MODE_DEFAULT,
	KVM_MODE_PROTECTED,
पूर्ण;
क्रमागत kvm_mode kvm_get_mode(व्योम);

DECLARE_STATIC_KEY_FALSE(userspace_irqchip_in_use);

बाह्य अचिन्हित पूर्णांक kvm_sve_max_vl;
पूर्णांक kvm_arm_init_sve(व्योम);

पूर्णांक __attribute_स्थिर__ kvm_target_cpu(व्योम);
पूर्णांक kvm_reset_vcpu(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arm_vcpu_destroy(काष्ठा kvm_vcpu *vcpu);

काष्ठा kvm_vmid अणु
	/* The VMID generation used क्रम the virt. memory प्रणाली */
	u64    vmid_gen;
	u32    vmid;
पूर्ण;

काष्ठा kvm_s2_mmu अणु
	काष्ठा kvm_vmid vmid;

	/*
	 * stage2 entry level table
	 *
	 * Two kvm_s2_mmu काष्ठाures in the same VM can poपूर्णांक to the same
	 * pgd here.  This happens when running a guest using a
	 * translation regime that isn't affected by its own stage-2
	 * translation, such as a non-VHE hypervisor running at vEL2, or
	 * क्रम vEL1/EL0 with vHCR_EL2.VM == 0.  In that हाल, we use the
	 * canonical stage-2 page tables.
	 */
	phys_addr_t	pgd_phys;
	काष्ठा kvm_pgtable *pgt;

	/* The last vcpu id that ran on each physical CPU */
	पूर्णांक __percpu *last_vcpu_ran;

	काष्ठा kvm_arch *arch;
पूर्ण;

काष्ठा kvm_arch_memory_slot अणु
पूर्ण;

काष्ठा kvm_arch अणु
	काष्ठा kvm_s2_mmu mmu;

	/* VTCR_EL2 value क्रम this VM */
	u64    vtcr;

	/* The maximum number of vCPUs depends on the used GIC model */
	पूर्णांक max_vcpus;

	/* Interrupt controller */
	काष्ठा vgic_dist	vgic;

	/* Mandated version of PSCI */
	u32 psci_version;

	/*
	 * If we encounter a data पात without valid inकाष्ठाion syndrome
	 * inक्रमmation, report this to user space.  User space can (and
	 * should) opt in to this feature अगर KVM_CAP_ARM_NISV_TO_USER is
	 * supported.
	 */
	bool वापस_nisv_io_पात_to_user;

	/*
	 * VM-wide PMU filter, implemented as a biपंचांगap and big enough क्रम
	 * up to 2^10 events (ARMv8.0) or 2^16 events (ARMv8.1+).
	 */
	अचिन्हित दीर्घ *pmu_filter;
	अचिन्हित पूर्णांक pmuver;

	u8 pfr0_csv2;
	u8 pfr0_csv3;
पूर्ण;

काष्ठा kvm_vcpu_fault_info अणु
	u32 esr_el2;		/* Hyp Syndrom Register */
	u64 far_el2;		/* Hyp Fault Address Register */
	u64 hpfar_el2;		/* Hyp IPA Fault Address Register */
	u64 disr_el1;		/* Deferred [SError] Status Register */
पूर्ण;

क्रमागत vcpu_sysreg अणु
	__INVALID_SYSREG__,   /* 0 is reserved as an invalid value */
	MPIDR_EL1,	/* MultiProcessor Affinity Register */
	CSSELR_EL1,	/* Cache Size Selection Register */
	SCTLR_EL1,	/* System Control Register */
	ACTLR_EL1,	/* Auxiliary Control Register */
	CPACR_EL1,	/* Coprocessor Access Control */
	ZCR_EL1,	/* SVE Control */
	TTBR0_EL1,	/* Translation Table Base Register 0 */
	TTBR1_EL1,	/* Translation Table Base Register 1 */
	TCR_EL1,	/* Translation Control Register */
	ESR_EL1,	/* Exception Syndrome Register */
	AFSR0_EL1,	/* Auxiliary Fault Status Register 0 */
	AFSR1_EL1,	/* Auxiliary Fault Status Register 1 */
	FAR_EL1,	/* Fault Address Register */
	MAIR_EL1,	/* Memory Attribute Indirection Register */
	VBAR_EL1,	/* Vector Base Address Register */
	CONTEXTIDR_EL1,	/* Context ID Register */
	TPIDR_EL0,	/* Thपढ़ो ID, User R/W */
	TPIDRRO_EL0,	/* Thपढ़ो ID, User R/O */
	TPIDR_EL1,	/* Thपढ़ो ID, Privileged */
	AMAIR_EL1,	/* Aux Memory Attribute Indirection Register */
	CNTKCTL_EL1,	/* Timer Control Register (EL1) */
	PAR_EL1,	/* Physical Address Register */
	MDSCR_EL1,	/* Monitor Debug System Control Register */
	MDCCINT_EL1,	/* Monitor Debug Comms Channel Interrupt Enable Reg */
	DISR_EL1,	/* Deferred Interrupt Status Register */

	/* Perक्रमmance Monitors Registers */
	PMCR_EL0,	/* Control Register */
	PMSELR_EL0,	/* Event Counter Selection Register */
	PMEVCNTR0_EL0,	/* Event Counter Register (0-30) */
	PMEVCNTR30_EL0 = PMEVCNTR0_EL0 + 30,
	PMCCNTR_EL0,	/* Cycle Counter Register */
	PMEVTYPER0_EL0,	/* Event Type Register (0-30) */
	PMEVTYPER30_EL0 = PMEVTYPER0_EL0 + 30,
	PMCCFILTR_EL0,	/* Cycle Count Filter Register */
	PMCNTENSET_EL0,	/* Count Enable Set Register */
	PMINTENSET_EL1,	/* Interrupt Enable Set Register */
	PMOVSSET_EL0,	/* Overflow Flag Status Set Register */
	PMSWINC_EL0,	/* Software Increment Register */
	PMUSERENR_EL0,	/* User Enable Register */

	/* Poपूर्णांकer Authentication Registers in a strict increasing order. */
	APIAKEYLO_EL1,
	APIAKEYHI_EL1,
	APIBKEYLO_EL1,
	APIBKEYHI_EL1,
	APDAKEYLO_EL1,
	APDAKEYHI_EL1,
	APDBKEYLO_EL1,
	APDBKEYHI_EL1,
	APGAKEYLO_EL1,
	APGAKEYHI_EL1,

	ELR_EL1,
	SP_EL1,
	SPSR_EL1,

	CNTVOFF_EL2,
	CNTV_CVAL_EL0,
	CNTV_CTL_EL0,
	CNTP_CVAL_EL0,
	CNTP_CTL_EL0,

	/* 32bit specअगरic रेजिस्टरs. Keep them at the end of the range */
	DACR32_EL2,	/* Doमुख्य Access Control Register */
	IFSR32_EL2,	/* Inकाष्ठाion Fault Status Register */
	FPEXC32_EL2,	/* Floating-Poपूर्णांक Exception Control Register */
	DBGVCR32_EL2,	/* Debug Vector Catch Register */

	NR_SYS_REGS	/* Nothing after this line! */
पूर्ण;

काष्ठा kvm_cpu_context अणु
	काष्ठा user_pt_regs regs;	/* sp = sp_el0 */

	u64	spsr_abt;
	u64	spsr_und;
	u64	spsr_irq;
	u64	spsr_fiq;

	काष्ठा user_fpsimd_state fp_regs;

	u64 sys_regs[NR_SYS_REGS];

	काष्ठा kvm_vcpu *__hyp_running_vcpu;
पूर्ण;

काष्ठा kvm_pmu_events अणु
	u32 events_host;
	u32 events_guest;
पूर्ण;

काष्ठा kvm_host_data अणु
	काष्ठा kvm_cpu_context host_ctxt;
	काष्ठा kvm_pmu_events pmu_events;
पूर्ण;

काष्ठा kvm_host_psci_config अणु
	/* PSCI version used by host. */
	u32 version;

	/* Function IDs used by host अगर version is v0.1. */
	काष्ठा psci_0_1_function_ids function_ids_0_1;

	bool psci_0_1_cpu_suspend_implemented;
	bool psci_0_1_cpu_on_implemented;
	bool psci_0_1_cpu_off_implemented;
	bool psci_0_1_migrate_implemented;
पूर्ण;

बाह्य काष्ठा kvm_host_psci_config kvm_nvhe_sym(kvm_host_psci_config);
#घोषणा kvm_host_psci_config CHOOSE_NVHE_SYM(kvm_host_psci_config)

बाह्य s64 kvm_nvhe_sym(hyp_physvirt_offset);
#घोषणा hyp_physvirt_offset CHOOSE_NVHE_SYM(hyp_physvirt_offset)

बाह्य u64 kvm_nvhe_sym(hyp_cpu_logical_map)[NR_CPUS];
#घोषणा hyp_cpu_logical_map CHOOSE_NVHE_SYM(hyp_cpu_logical_map)

काष्ठा vcpu_reset_state अणु
	अचिन्हित दीर्घ	pc;
	अचिन्हित दीर्घ	r0;
	bool		be;
	bool		reset;
पूर्ण;

काष्ठा kvm_vcpu_arch अणु
	काष्ठा kvm_cpu_context ctxt;
	व्योम *sve_state;
	अचिन्हित पूर्णांक sve_max_vl;

	/* Stage 2 paging state used by the hardware on next चयन */
	काष्ठा kvm_s2_mmu *hw_mmu;

	/* HYP configuration */
	u64 hcr_el2;
	u32 mdcr_el2;

	/* Exception Inक्रमmation */
	काष्ठा kvm_vcpu_fault_info fault;

	/* State of various workarounds, see kvm_यंत्र.h क्रम bit assignment */
	u64 workaround_flags;

	/* Miscellaneous vcpu state flags */
	u64 flags;

	/*
	 * We मुख्यtain more than a single set of debug रेजिस्टरs to support
	 * debugging the guest from the host and to मुख्यtain separate host and
	 * guest state during world चयनes. vcpu_debug_state are the debug
	 * रेजिस्टरs of the vcpu as the guest sees them.  host_debug_state are
	 * the host रेजिस्टरs which are saved and restored during
	 * world चयनes. बाह्यal_debug_state contains the debug
	 * values we want to debug the guest. This is set via the
	 * KVM_SET_GUEST_DEBUG ioctl.
	 *
	 * debug_ptr poपूर्णांकs to the set of debug रेजिस्टरs that should be loaded
	 * onto the hardware when running the guest.
	 */
	काष्ठा kvm_guest_debug_arch *debug_ptr;
	काष्ठा kvm_guest_debug_arch vcpu_debug_state;
	काष्ठा kvm_guest_debug_arch बाह्यal_debug_state;

	काष्ठा thपढ़ो_info *host_thपढ़ो_info;	/* hyp VA */
	काष्ठा user_fpsimd_state *host_fpsimd_state;	/* hyp VA */

	काष्ठा अणु
		/* अणुBreak,watchपूर्णpoपूर्णांक रेजिस्टरs */
		काष्ठा kvm_guest_debug_arch regs;
		/* Statistical profiling extension */
		u64 pmscr_el1;
		/* Self-hosted trace */
		u64 trfcr_el1;
	पूर्ण host_debug_state;

	/* VGIC state */
	काष्ठा vgic_cpu vgic_cpu;
	काष्ठा arch_समयr_cpu समयr_cpu;
	काष्ठा kvm_pmu pmu;

	/*
	 * Anything that is not used directly from assembly code goes
	 * here.
	 */

	/*
	 * Guest रेजिस्टरs we preserve during guest debugging.
	 *
	 * These shaकरोw रेजिस्टरs are updated by the kvm_handle_sys_reg
	 * trap handler अगर the guest accesses or updates them जबतक we
	 * are using guest debug.
	 */
	काष्ठा अणु
		u32	mdscr_el1;
	पूर्ण guest_debug_preserved;

	/* vcpu घातer-off state */
	bool घातer_off;

	/* Don't run the guest (पूर्णांकernal implementation need) */
	bool छोड़ो;

	/* Cache some mmu pages needed inside spinlock regions */
	काष्ठा kvm_mmu_memory_cache mmu_page_cache;

	/* Target CPU and feature flags */
	पूर्णांक target;
	DECLARE_BITMAP(features, KVM_VCPU_MAX_FEATURES);

	/* Detect first run of a vcpu */
	bool has_run_once;

	/* Virtual SError ESR to restore when HCR_EL2.VSE is set */
	u64 vsesr_el2;

	/* Additional reset state */
	काष्ठा vcpu_reset_state	reset_state;

	/* True when deferrable sysregs are loaded on the physical CPU,
	 * see kvm_vcpu_load_sysregs_vhe and kvm_vcpu_put_sysregs_vhe. */
	bool sysregs_loaded_on_cpu;

	/* Guest PV state */
	काष्ठा अणु
		u64 last_steal;
		gpa_t base;
	पूर्ण steal;
पूर्ण;

/* Poपूर्णांकer to the vcpu's SVE FFR क्रम sve_अणुsave,loadपूर्ण_state() */
#घोषणा vcpu_sve_pffr(vcpu) (kern_hyp_va((vcpu)->arch.sve_state) +	\
			     sve_ffr_offset((vcpu)->arch.sve_max_vl))

#घोषणा vcpu_sve_max_vq(vcpu)	sve_vq_from_vl((vcpu)->arch.sve_max_vl)

#घोषणा vcpu_sve_state_size(vcpu) (अणु					\
	माप_प्रकार __size_ret;						\
	अचिन्हित पूर्णांक __vcpu_vq;						\
									\
	अगर (WARN_ON(!sve_vl_valid((vcpu)->arch.sve_max_vl))) अणु		\
		__size_ret = 0;						\
	पूर्ण अन्यथा अणु							\
		__vcpu_vq = vcpu_sve_max_vq(vcpu);			\
		__size_ret = SVE_SIG_REGS_SIZE(__vcpu_vq);		\
	पूर्ण								\
									\
	__size_ret;							\
पूर्ण)

/* vcpu_arch flags field values: */
#घोषणा KVM_ARM64_DEBUG_सूचीTY		(1 << 0)
#घोषणा KVM_ARM64_FP_ENABLED		(1 << 1) /* guest FP regs loaded */
#घोषणा KVM_ARM64_FP_HOST		(1 << 2) /* host FP regs loaded */
#घोषणा KVM_ARM64_HOST_SVE_IN_USE	(1 << 3) /* backup क्रम host TIF_SVE */
#घोषणा KVM_ARM64_HOST_SVE_ENABLED	(1 << 4) /* SVE enabled क्रम EL0 */
#घोषणा KVM_ARM64_GUEST_HAS_SVE		(1 << 5) /* SVE exposed to guest */
#घोषणा KVM_ARM64_VCPU_SVE_FINALIZED	(1 << 6) /* SVE config completed */
#घोषणा KVM_ARM64_GUEST_HAS_PTRAUTH	(1 << 7) /* PTRAUTH exposed to guest */
#घोषणा KVM_ARM64_PENDING_EXCEPTION	(1 << 8) /* Exception pending */
#घोषणा KVM_ARM64_EXCEPT_MASK		(7 << 9) /* Target EL/MODE */
#घोषणा KVM_ARM64_DEBUG_STATE_SAVE_SPE	(1 << 12) /* Save SPE context अगर active  */
#घोषणा KVM_ARM64_DEBUG_STATE_SAVE_TRBE	(1 << 13) /* Save TRBE context अगर active  */

#घोषणा KVM_GUESTDBG_VALID_MASK (KVM_GUESTDBG_ENABLE | \
				 KVM_GUESTDBG_USE_SW_BP | \
				 KVM_GUESTDBG_USE_HW | \
				 KVM_GUESTDBG_SINGLESTEP)
/*
 * When KVM_ARM64_PENDING_EXCEPTION is set, KVM_ARM64_EXCEPT_MASK can
 * take the following values:
 *
 * For AArch32 EL1:
 */
#घोषणा KVM_ARM64_EXCEPT_AA32_UND	(0 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA32_IABT	(1 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA32_DABT	(2 << 9)
/* For AArch64: */
#घोषणा KVM_ARM64_EXCEPT_AA64_ELx_SYNC	(0 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA64_ELx_IRQ	(1 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA64_ELx_FIQ	(2 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA64_ELx_SERR	(3 << 9)
#घोषणा KVM_ARM64_EXCEPT_AA64_EL1	(0 << 11)
#घोषणा KVM_ARM64_EXCEPT_AA64_EL2	(1 << 11)

/*
 * Overlaps with KVM_ARM64_EXCEPT_MASK on purpose so that it can't be
 * set together with an exception...
 */
#घोषणा KVM_ARM64_INCREMENT_PC		(1 << 9) /* Increment PC */

#घोषणा vcpu_has_sve(vcpu) (प्रणाली_supports_sve() &&			\
			    ((vcpu)->arch.flags & KVM_ARM64_GUEST_HAS_SVE))

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
#घोषणा vcpu_has_ptrauth(vcpu)						\
	((cpus_have_final_cap(ARM64_HAS_ADDRESS_AUTH) ||		\
	  cpus_have_final_cap(ARM64_HAS_GENERIC_AUTH)) &&		\
	 (vcpu)->arch.flags & KVM_ARM64_GUEST_HAS_PTRAUTH)
#अन्यथा
#घोषणा vcpu_has_ptrauth(vcpu)		false
#पूर्ण_अगर

#घोषणा vcpu_gp_regs(v)		(&(v)->arch.ctxt.regs)

/*
 * Only use __vcpu_sys_reg/ctxt_sys_reg अगर you know you want the
 * memory backed version of a रेजिस्टर, and not the one most recently
 * accessed by a running VCPU.  For example, क्रम userspace access or
 * क्रम प्रणाली रेजिस्टरs that are never context चयनed, but only
 * emulated.
 */
#घोषणा __ctxt_sys_reg(c,r)	(&(c)->sys_regs[(r)])

#घोषणा ctxt_sys_reg(c,r)	(*__ctxt_sys_reg(c,r))

#घोषणा __vcpu_sys_reg(v,r)	(ctxt_sys_reg(&(v)->arch.ctxt, (r)))

u64 vcpu_पढ़ो_sys_reg(स्थिर काष्ठा kvm_vcpu *vcpu, पूर्णांक reg);
व्योम vcpu_ग_लिखो_sys_reg(काष्ठा kvm_vcpu *vcpu, u64 val, पूर्णांक reg);

अटल अंतरभूत bool __vcpu_पढ़ो_sys_reg_from_cpu(पूर्णांक reg, u64 *val)
अणु
	/*
	 * *** VHE ONLY ***
	 *
	 * System रेजिस्टरs listed in the चयन are not saved on every
	 * निकास from the guest but are only saved on vcpu_put.
	 *
	 * Note that MPIDR_EL1 क्रम the guest is set by KVM via VMPIDR_EL2 but
	 * should never be listed below, because the guest cannot modअगरy its
	 * own MPIDR_EL1 and MPIDR_EL1 is accessed क्रम VCPU A from VCPU B's
	 * thपढ़ो when emulating cross-VCPU communication.
	 */
	अगर (!has_vhe())
		वापस false;

	चयन (reg) अणु
	हाल CSSELR_EL1:	*val = पढ़ो_sysreg_s(SYS_CSSELR_EL1);	अवरोध;
	हाल SCTLR_EL1:		*val = पढ़ो_sysreg_s(SYS_SCTLR_EL12);	अवरोध;
	हाल CPACR_EL1:		*val = पढ़ो_sysreg_s(SYS_CPACR_EL12);	अवरोध;
	हाल TTBR0_EL1:		*val = पढ़ो_sysreg_s(SYS_TTBR0_EL12);	अवरोध;
	हाल TTBR1_EL1:		*val = पढ़ो_sysreg_s(SYS_TTBR1_EL12);	अवरोध;
	हाल TCR_EL1:		*val = पढ़ो_sysreg_s(SYS_TCR_EL12);	अवरोध;
	हाल ESR_EL1:		*val = पढ़ो_sysreg_s(SYS_ESR_EL12);	अवरोध;
	हाल AFSR0_EL1:		*val = पढ़ो_sysreg_s(SYS_AFSR0_EL12);	अवरोध;
	हाल AFSR1_EL1:		*val = पढ़ो_sysreg_s(SYS_AFSR1_EL12);	अवरोध;
	हाल FAR_EL1:		*val = पढ़ो_sysreg_s(SYS_FAR_EL12);	अवरोध;
	हाल MAIR_EL1:		*val = पढ़ो_sysreg_s(SYS_MAIR_EL12);	अवरोध;
	हाल VBAR_EL1:		*val = पढ़ो_sysreg_s(SYS_VBAR_EL12);	अवरोध;
	हाल CONTEXTIDR_EL1:	*val = पढ़ो_sysreg_s(SYS_CONTEXTIDR_EL12);अवरोध;
	हाल TPIDR_EL0:		*val = पढ़ो_sysreg_s(SYS_TPIDR_EL0);	अवरोध;
	हाल TPIDRRO_EL0:	*val = पढ़ो_sysreg_s(SYS_TPIDRRO_EL0);	अवरोध;
	हाल TPIDR_EL1:		*val = पढ़ो_sysreg_s(SYS_TPIDR_EL1);	अवरोध;
	हाल AMAIR_EL1:		*val = पढ़ो_sysreg_s(SYS_AMAIR_EL12);	अवरोध;
	हाल CNTKCTL_EL1:	*val = पढ़ो_sysreg_s(SYS_CNTKCTL_EL12);	अवरोध;
	हाल ELR_EL1:		*val = पढ़ो_sysreg_s(SYS_ELR_EL12);	अवरोध;
	हाल PAR_EL1:		*val = पढ़ो_sysreg_par();		अवरोध;
	हाल DACR32_EL2:	*val = पढ़ो_sysreg_s(SYS_DACR32_EL2);	अवरोध;
	हाल IFSR32_EL2:	*val = पढ़ो_sysreg_s(SYS_IFSR32_EL2);	अवरोध;
	हाल DBGVCR32_EL2:	*val = पढ़ो_sysreg_s(SYS_DBGVCR32_EL2);	अवरोध;
	शेष:		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool __vcpu_ग_लिखो_sys_reg_to_cpu(u64 val, पूर्णांक reg)
अणु
	/*
	 * *** VHE ONLY ***
	 *
	 * System रेजिस्टरs listed in the चयन are not restored on every
	 * entry to the guest but are only restored on vcpu_load.
	 *
	 * Note that MPIDR_EL1 क्रम the guest is set by KVM via VMPIDR_EL2 but
	 * should never be listed below, because the MPIDR should only be set
	 * once, beक्रमe running the VCPU, and never changed later.
	 */
	अगर (!has_vhe())
		वापस false;

	चयन (reg) अणु
	हाल CSSELR_EL1:	ग_लिखो_sysreg_s(val, SYS_CSSELR_EL1);	अवरोध;
	हाल SCTLR_EL1:		ग_लिखो_sysreg_s(val, SYS_SCTLR_EL12);	अवरोध;
	हाल CPACR_EL1:		ग_लिखो_sysreg_s(val, SYS_CPACR_EL12);	अवरोध;
	हाल TTBR0_EL1:		ग_लिखो_sysreg_s(val, SYS_TTBR0_EL12);	अवरोध;
	हाल TTBR1_EL1:		ग_लिखो_sysreg_s(val, SYS_TTBR1_EL12);	अवरोध;
	हाल TCR_EL1:		ग_लिखो_sysreg_s(val, SYS_TCR_EL12);	अवरोध;
	हाल ESR_EL1:		ग_लिखो_sysreg_s(val, SYS_ESR_EL12);	अवरोध;
	हाल AFSR0_EL1:		ग_लिखो_sysreg_s(val, SYS_AFSR0_EL12);	अवरोध;
	हाल AFSR1_EL1:		ग_लिखो_sysreg_s(val, SYS_AFSR1_EL12);	अवरोध;
	हाल FAR_EL1:		ग_लिखो_sysreg_s(val, SYS_FAR_EL12);	अवरोध;
	हाल MAIR_EL1:		ग_लिखो_sysreg_s(val, SYS_MAIR_EL12);	अवरोध;
	हाल VBAR_EL1:		ग_लिखो_sysreg_s(val, SYS_VBAR_EL12);	अवरोध;
	हाल CONTEXTIDR_EL1:	ग_लिखो_sysreg_s(val, SYS_CONTEXTIDR_EL12);अवरोध;
	हाल TPIDR_EL0:		ग_लिखो_sysreg_s(val, SYS_TPIDR_EL0);	अवरोध;
	हाल TPIDRRO_EL0:	ग_लिखो_sysreg_s(val, SYS_TPIDRRO_EL0);	अवरोध;
	हाल TPIDR_EL1:		ग_लिखो_sysreg_s(val, SYS_TPIDR_EL1);	अवरोध;
	हाल AMAIR_EL1:		ग_लिखो_sysreg_s(val, SYS_AMAIR_EL12);	अवरोध;
	हाल CNTKCTL_EL1:	ग_लिखो_sysreg_s(val, SYS_CNTKCTL_EL12);	अवरोध;
	हाल ELR_EL1:		ग_लिखो_sysreg_s(val, SYS_ELR_EL12);	अवरोध;
	हाल PAR_EL1:		ग_लिखो_sysreg_s(val, SYS_PAR_EL1);	अवरोध;
	हाल DACR32_EL2:	ग_लिखो_sysreg_s(val, SYS_DACR32_EL2);	अवरोध;
	हाल IFSR32_EL2:	ग_लिखो_sysreg_s(val, SYS_IFSR32_EL2);	अवरोध;
	हाल DBGVCR32_EL2:	ग_लिखो_sysreg_s(val, SYS_DBGVCR32_EL2);	अवरोध;
	शेष:		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा kvm_vm_stat अणु
	uदीर्घ remote_tlb_flush;
पूर्ण;

काष्ठा kvm_vcpu_stat अणु
	u64 halt_successful_poll;
	u64 halt_attempted_poll;
	u64 halt_poll_success_ns;
	u64 halt_poll_fail_ns;
	u64 halt_poll_invalid;
	u64 halt_wakeup;
	u64 hvc_निकास_stat;
	u64 wfe_निकास_stat;
	u64 wfi_निकास_stat;
	u64 mmio_निकास_user;
	u64 mmio_निकास_kernel;
	u64 निकासs;
पूर्ण;

पूर्णांक kvm_vcpu_preferred_target(काष्ठा kvm_vcpu_init *init);
अचिन्हित दीर्घ kvm_arm_num_regs(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arm_copy_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *indices);
पूर्णांक kvm_arm_get_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg);
पूर्णांक kvm_arm_set_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg);

अचिन्हित दीर्घ kvm_arm_num_sys_reg_descs(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arm_copy_sys_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices);
पूर्णांक kvm_arm_sys_reg_get_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *);
पूर्णांक kvm_arm_sys_reg_set_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *);

पूर्णांक __kvm_arm_vcpu_get_events(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_vcpu_events *events);

पूर्णांक __kvm_arm_vcpu_set_events(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_vcpu_events *events);

#घोषणा KVM_ARCH_WANT_MMU_NOTIFIER

व्योम kvm_arm_halt_guest(काष्ठा kvm *kvm);
व्योम kvm_arm_resume_guest(काष्ठा kvm *kvm);

#अगर_अघोषित __KVM_NVHE_HYPERVISOR__
#घोषणा kvm_call_hyp_nvhe(f, ...)						\
	(अणु								\
		काष्ठा arm_smccc_res res;				\
									\
		arm_smccc_1_1_hvc(KVM_HOST_SMCCC_FUNC(f),		\
				  ##__VA_ARGS__, &res);			\
		WARN_ON(res.a0 != SMCCC_RET_SUCCESS);			\
									\
		res.a1;							\
	पूर्ण)

/*
 * The couple of isb() below are there to guarantee the same behaviour
 * on VHE as on !VHE, where the eret to EL1 acts as a context
 * synchronization event.
 */
#घोषणा kvm_call_hyp(f, ...)						\
	करो अणु								\
		अगर (has_vhe()) अणु					\
			f(__VA_ARGS__);					\
			isb();						\
		पूर्ण अन्यथा अणु						\
			kvm_call_hyp_nvhe(f, ##__VA_ARGS__);		\
		पूर्ण							\
	पूर्ण जबतक(0)

#घोषणा kvm_call_hyp_ret(f, ...)					\
	(अणु								\
		typeof(f(__VA_ARGS__)) ret;				\
									\
		अगर (has_vhe()) अणु					\
			ret = f(__VA_ARGS__);				\
			isb();						\
		पूर्ण अन्यथा अणु						\
			ret = kvm_call_hyp_nvhe(f, ##__VA_ARGS__);	\
		पूर्ण							\
									\
		ret;							\
	पूर्ण)
#अन्यथा /* __KVM_NVHE_HYPERVISOR__ */
#घोषणा kvm_call_hyp(f, ...) f(__VA_ARGS__)
#घोषणा kvm_call_hyp_ret(f, ...) f(__VA_ARGS__)
#घोषणा kvm_call_hyp_nvhe(f, ...) f(__VA_ARGS__)
#पूर्ण_अगर /* __KVM_NVHE_HYPERVISOR__ */

व्योम क्रमce_vm_निकास(स्थिर cpumask_t *mask);

पूर्णांक handle_निकास(काष्ठा kvm_vcpu *vcpu, पूर्णांक exception_index);
व्योम handle_निकास_early(काष्ठा kvm_vcpu *vcpu, पूर्णांक exception_index);

पूर्णांक kvm_handle_cp14_load_store(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_cp14_32(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_cp14_64(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_cp15_32(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_cp15_64(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_sys_reg(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_reset_sys_regs(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_sys_reg_table_init(व्योम);

/* MMIO helpers */
व्योम kvm_mmio_ग_लिखो_buf(व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ data);
अचिन्हित दीर्घ kvm_mmio_पढ़ो_buf(स्थिर व्योम *buf, अचिन्हित पूर्णांक len);

पूर्णांक kvm_handle_mmio_वापस(काष्ठा kvm_vcpu *vcpu);
पूर्णांक io_mem_पात(काष्ठा kvm_vcpu *vcpu, phys_addr_t fault_ipa);

पूर्णांक kvm_perf_init(व्योम);
पूर्णांक kvm_perf_tearकरोwn(व्योम);

दीर्घ kvm_hypercall_pv_features(काष्ठा kvm_vcpu *vcpu);
gpa_t kvm_init_stolen_समय(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_update_stolen_समय(काष्ठा kvm_vcpu *vcpu);

bool kvm_arm_pvसमय_supported(व्योम);
पूर्णांक kvm_arm_pvसमय_set_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_pvसमय_get_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_pvसमय_has_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);

अटल अंतरभूत व्योम kvm_arm_pvसमय_vcpu_init(काष्ठा kvm_vcpu_arch *vcpu_arch)
अणु
	vcpu_arch->steal.base = GPA_INVALID;
पूर्ण

अटल अंतरभूत bool kvm_arm_is_pvसमय_enabled(काष्ठा kvm_vcpu_arch *vcpu_arch)
अणु
	वापस (vcpu_arch->steal.base != GPA_INVALID);
पूर्ण

व्योम kvm_set_sei_esr(काष्ठा kvm_vcpu *vcpu, u64 syndrome);

काष्ठा kvm_vcpu *kvm_mpidr_to_vcpu(काष्ठा kvm *kvm, अचिन्हित दीर्घ mpidr);

DECLARE_KVM_HYP_PER_CPU(काष्ठा kvm_host_data, kvm_host_data);

अटल अंतरभूत व्योम kvm_init_host_cpu_context(काष्ठा kvm_cpu_context *cpu_ctxt)
अणु
	/* The host's MPIDR is immutable, so let's set it up at boot समय */
	ctxt_sys_reg(cpu_ctxt, MPIDR_EL1) = पढ़ो_cpuid_mpidr();
पूर्ण

व्योम kvm_arm_vcpu_ptrauth_trap(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत व्योम kvm_arch_hardware_unsetup(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sync_events(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

व्योम kvm_arm_init_debug(व्योम);
व्योम kvm_arm_vcpu_init_debug(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arm_setup_debug(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arm_clear_debug(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arm_reset_debug_ptr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arm_vcpu_arch_set_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_vcpu_arch_get_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_vcpu_arch_has_attr(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_device_attr *attr);

/* Guest/host FPSIMD coordination helpers */
पूर्णांक kvm_arch_vcpu_run_map_fp(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_load_fp(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_ctxsync_fp(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_put_fp(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत bool kvm_pmu_counter_deferred(काष्ठा perf_event_attr *attr)
अणु
	वापस (!has_vhe() && attr->exclude_host);
पूर्ण

/* Flags क्रम host debug state */
व्योम kvm_arch_vcpu_load_debug_state_flags(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_put_debug_state_flags(काष्ठा kvm_vcpu *vcpu);

#अगर_घोषित CONFIG_KVM /* Aव्योम conflicts with core headers अगर CONFIG_KVM=n */
अटल अंतरभूत पूर्णांक kvm_arch_vcpu_run_pid_change(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_arch_vcpu_run_map_fp(vcpu);
पूर्ण

व्योम kvm_set_pmu_events(u32 set, काष्ठा perf_event_attr *attr);
व्योम kvm_clr_pmu_events(u32 clr);

व्योम kvm_vcpu_pmu_restore_guest(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vcpu_pmu_restore_host(काष्ठा kvm_vcpu *vcpu);
#अन्यथा
अटल अंतरभूत व्योम kvm_set_pmu_events(u32 set, काष्ठा perf_event_attr *attr) अणुपूर्ण
अटल अंतरभूत व्योम kvm_clr_pmu_events(u32 clr) अणुपूर्ण
#पूर्ण_अगर

व्योम kvm_vcpu_load_sysregs_vhe(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vcpu_put_sysregs_vhe(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_set_ipa_limit(व्योम);

#घोषणा __KVM_HAVE_ARCH_VM_ALLOC
काष्ठा kvm *kvm_arch_alloc_vm(व्योम);
व्योम kvm_arch_मुक्त_vm(काष्ठा kvm *kvm);

पूर्णांक kvm_arm_setup_stage2(काष्ठा kvm *kvm, अचिन्हित दीर्घ type);

पूर्णांक kvm_arm_vcpu_finalize(काष्ठा kvm_vcpu *vcpu, पूर्णांक feature);
bool kvm_arm_vcpu_is_finalized(काष्ठा kvm_vcpu *vcpu);

#घोषणा kvm_arm_vcpu_sve_finalized(vcpu) \
	((vcpu)->arch.flags & KVM_ARM64_VCPU_SVE_FINALIZED)

#घोषणा kvm_vcpu_has_pmu(vcpu)					\
	(test_bit(KVM_ARM_VCPU_PMU_V3, (vcpu)->arch.features))

पूर्णांक kvm_trng_call(काष्ठा kvm_vcpu *vcpu);
#अगर_घोषित CONFIG_KVM
बाह्य phys_addr_t hyp_mem_base;
बाह्य phys_addr_t hyp_mem_size;
व्योम __init kvm_hyp_reserve(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kvm_hyp_reserve(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ARM64_KVM_HOST_H__ */
