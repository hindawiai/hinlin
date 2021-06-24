<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * derived from drivers/kvm/kvm_मुख्य.c
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright (C) 2008 Qumranet, Inc.
 * Copyright IBM Corporation, 2008
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Avi Kivity   <avi@qumranet.com>
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Amit Shah    <amit.shah@qumranet.com>
 *   Ben-Ami Yassour <benami@il.ibm.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश "irq.h"
#समावेश "ioapic.h"
#समावेश "mmu.h"
#समावेश "i8254.h"
#समावेश "tss.h"
#समावेश "kvm_cache_regs.h"
#समावेश "kvm_emulate.h"
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "pmu.h"
#समावेश "hyperv.h"
#समावेश "lapic.h"
#समावेश "xen.h"

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kvm.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mman.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/iommu.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/user-वापस-notअगरier.h>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hash.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/pvघड़ी_gtod.h>
#समावेश <linux/kvm_irqfd.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/entry-kvm.h>

#समावेश <trace/events/kvm.h>

#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/mce.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <यंत्र/fpu/पूर्णांकernal.h> /* Ugh! */
#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/पूर्णांकel_pt.h>
#समावेश <यंत्र/emulate_prefix.h>
#समावेश <यंत्र/sgx.h>
#समावेश <घड़ीsource/hyperv_समयr.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#घोषणा MAX_IO_MSRS 256
#घोषणा KVM_MAX_MCE_BANKS 32
u64 __पढ़ो_mostly kvm_mce_cap_supported = MCG_CTL_P | MCG_SER_P;
EXPORT_SYMBOL_GPL(kvm_mce_cap_supported);

#घोषणा emul_to_vcpu(ctxt) \
	((काष्ठा kvm_vcpu *)(ctxt)->vcpu)

/* EFER शेषs:
 * - enable syscall per शेष because its emulated by KVM
 * - enable LME and LMA per शेष on 64 bit KVM
 */
#अगर_घोषित CONFIG_X86_64
अटल
u64 __पढ़ो_mostly efer_reserved_bits = ~((u64)(EFER_SCE | EFER_LME | EFER_LMA));
#अन्यथा
अटल u64 __पढ़ो_mostly efer_reserved_bits = ~((u64)EFER_SCE);
#पूर्ण_अगर

अटल u64 __पढ़ो_mostly cr4_reserved_bits = CR4_RESERVED_BITS;

#घोषणा KVM_X2APIC_API_VALID_FLAGS (KVM_X2APIC_API_USE_32BIT_IDS | \
                                    KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK)

अटल व्योम update_cr8_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu);
अटल व्योम process_nmi(काष्ठा kvm_vcpu *vcpu);
अटल व्योम process_smi(काष्ठा kvm_vcpu *vcpu);
अटल व्योम enter_smm(काष्ठा kvm_vcpu *vcpu);
अटल व्योम __kvm_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags);
अटल व्योम store_regs(काष्ठा kvm_vcpu *vcpu);
अटल पूर्णांक sync_regs(काष्ठा kvm_vcpu *vcpu);

काष्ठा kvm_x86_ops kvm_x86_ops __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(kvm_x86_ops);

#घोषणा KVM_X86_OP(func)					     \
	DEFINE_STATIC_CALL_शून्य(kvm_x86_##func,			     \
				*(((काष्ठा kvm_x86_ops *)0)->func));
#घोषणा KVM_X86_OP_शून्य KVM_X86_OP
#समावेश <यंत्र/kvm-x86-ops.h>
EXPORT_STATIC_CALL_GPL(kvm_x86_get_cs_db_l_bits);
EXPORT_STATIC_CALL_GPL(kvm_x86_cache_reg);
EXPORT_STATIC_CALL_GPL(kvm_x86_tlb_flush_current);

अटल bool __पढ़ो_mostly ignore_msrs = 0;
module_param(ignore_msrs, bool, S_IRUGO | S_IWUSR);

bool __पढ़ो_mostly report_ignored_msrs = true;
module_param(report_ignored_msrs, bool, S_IRUGO | S_IWUSR);
EXPORT_SYMBOL_GPL(report_ignored_msrs);

अचिन्हित पूर्णांक min_समयr_period_us = 200;
module_param(min_समयr_period_us, uपूर्णांक, S_IRUGO | S_IWUSR);

अटल bool __पढ़ो_mostly kvmघड़ी_periodic_sync = true;
module_param(kvmघड़ी_periodic_sync, bool, S_IRUGO);

bool __पढ़ो_mostly kvm_has_tsc_control;
EXPORT_SYMBOL_GPL(kvm_has_tsc_control);
u32  __पढ़ो_mostly kvm_max_guest_tsc_khz;
EXPORT_SYMBOL_GPL(kvm_max_guest_tsc_khz);
u8   __पढ़ो_mostly kvm_tsc_scaling_ratio_frac_bits;
EXPORT_SYMBOL_GPL(kvm_tsc_scaling_ratio_frac_bits);
u64  __पढ़ो_mostly kvm_max_tsc_scaling_ratio;
EXPORT_SYMBOL_GPL(kvm_max_tsc_scaling_ratio);
u64 __पढ़ो_mostly kvm_शेष_tsc_scaling_ratio;
EXPORT_SYMBOL_GPL(kvm_शेष_tsc_scaling_ratio);
bool __पढ़ो_mostly kvm_has_bus_lock_निकास;
EXPORT_SYMBOL_GPL(kvm_has_bus_lock_निकास);

/* tsc tolerance in parts per million - शेष to 1/2 of the NTP threshold */
अटल u32 __पढ़ो_mostly tsc_tolerance_ppm = 250;
module_param(tsc_tolerance_ppm, uपूर्णांक, S_IRUGO | S_IWUSR);

/*
 * lapic समयr advance (tscdeadline mode only) in nanoseconds.  '-1' enables
 * adaptive tuning starting from शेष advancement of 1000ns.  '0' disables
 * advancement entirely.  Any other value is used as-is and disables adaptive
 * tuning, i.e. allows privileged userspace to set an exact advancement समय.
 */
अटल पूर्णांक __पढ़ो_mostly lapic_समयr_advance_ns = -1;
module_param(lapic_समयr_advance_ns, पूर्णांक, S_IRUGO | S_IWUSR);

अटल bool __पढ़ो_mostly vector_hashing = true;
module_param(vector_hashing, bool, S_IRUGO);

bool __पढ़ो_mostly enable_vmware_backकरोor = false;
module_param(enable_vmware_backकरोor, bool, S_IRUGO);
EXPORT_SYMBOL_GPL(enable_vmware_backकरोor);

अटल bool __पढ़ो_mostly क्रमce_emulation_prefix = false;
module_param(क्रमce_emulation_prefix, bool, S_IRUGO);

पूर्णांक __पढ़ो_mostly pi_inject_समयr = -1;
module_param(pi_inject_समयr, bपूर्णांक, S_IRUGO | S_IWUSR);

/*
 * Restoring the host value क्रम MSRs that are only consumed when running in
 * usermode, e.g. SYSCALL MSRs and TSC_AUX, can be deferred until the CPU
 * वापसs to userspace, i.e. the kernel can run with the guest's value.
 */
#घोषणा KVM_MAX_NR_USER_RETURN_MSRS 16

काष्ठा kvm_user_वापस_msrs अणु
	काष्ठा user_वापस_notअगरier urn;
	bool रेजिस्टरed;
	काष्ठा kvm_user_वापस_msr_values अणु
		u64 host;
		u64 curr;
	पूर्ण values[KVM_MAX_NR_USER_RETURN_MSRS];
पूर्ण;

u32 __पढ़ो_mostly kvm_nr_uret_msrs;
EXPORT_SYMBOL_GPL(kvm_nr_uret_msrs);
अटल u32 __पढ़ो_mostly kvm_uret_msrs_list[KVM_MAX_NR_USER_RETURN_MSRS];
अटल काष्ठा kvm_user_वापस_msrs __percpu *user_वापस_msrs;

#घोषणा KVM_SUPPORTED_XCR0     (XFEATURE_MASK_FP | XFEATURE_MASK_SSE \
				| XFEATURE_MASK_YMM | XFEATURE_MASK_BNDREGS \
				| XFEATURE_MASK_BNDCSR | XFEATURE_MASK_AVX512 \
				| XFEATURE_MASK_PKRU)

u64 __पढ़ो_mostly host_efer;
EXPORT_SYMBOL_GPL(host_efer);

bool __पढ़ो_mostly allow_smaller_maxphyaddr = 0;
EXPORT_SYMBOL_GPL(allow_smaller_maxphyaddr);

u64 __पढ़ो_mostly host_xss;
EXPORT_SYMBOL_GPL(host_xss);
u64 __पढ़ो_mostly supported_xss;
EXPORT_SYMBOL_GPL(supported_xss);

काष्ठा kvm_stats_debugfs_item debugfs_entries[] = अणु
	VCPU_STAT("pf_fixed", pf_fixed),
	VCPU_STAT("pf_guest", pf_guest),
	VCPU_STAT("tlb_flush", tlb_flush),
	VCPU_STAT("invlpg", invlpg),
	VCPU_STAT("exits", निकासs),
	VCPU_STAT("io_exits", io_निकासs),
	VCPU_STAT("mmio_exits", mmio_निकासs),
	VCPU_STAT("signal_exits", संकेत_निकासs),
	VCPU_STAT("irq_window", irq_winकरोw_निकासs),
	VCPU_STAT("nmi_window", nmi_winकरोw_निकासs),
	VCPU_STAT("halt_exits", halt_निकासs),
	VCPU_STAT("halt_successful_poll", halt_successful_poll),
	VCPU_STAT("halt_attempted_poll", halt_attempted_poll),
	VCPU_STAT("halt_poll_invalid", halt_poll_invalid),
	VCPU_STAT("halt_wakeup", halt_wakeup),
	VCPU_STAT("hypercalls", hypercalls),
	VCPU_STAT("request_irq", request_irq_निकासs),
	VCPU_STAT("irq_exits", irq_निकासs),
	VCPU_STAT("host_state_reload", host_state_reload),
	VCPU_STAT("fpu_reload", fpu_reload),
	VCPU_STAT("insn_emulation", insn_emulation),
	VCPU_STAT("insn_emulation_fail", insn_emulation_fail),
	VCPU_STAT("irq_injections", irq_injections),
	VCPU_STAT("nmi_injections", nmi_injections),
	VCPU_STAT("req_event", req_event),
	VCPU_STAT("l1d_flush", l1d_flush),
	VCPU_STAT("halt_poll_success_ns", halt_poll_success_ns),
	VCPU_STAT("halt_poll_fail_ns", halt_poll_fail_ns),
	VCPU_STAT("nested_run", nested_run),
	VCPU_STAT("directed_yield_attempted", directed_yield_attempted),
	VCPU_STAT("directed_yield_successful", directed_yield_successful),
	VM_STAT("mmu_shadow_zapped", mmu_shaकरोw_zapped),
	VM_STAT("mmu_pte_write", mmu_pte_ग_लिखो),
	VM_STAT("mmu_pde_zapped", mmu_pde_zapped),
	VM_STAT("mmu_flooded", mmu_flooded),
	VM_STAT("mmu_recycled", mmu_recycled),
	VM_STAT("mmu_cache_miss", mmu_cache_miss),
	VM_STAT("mmu_unsync", mmu_unsync),
	VM_STAT("remote_tlb_flush", remote_tlb_flush),
	VM_STAT("largepages", lpages, .mode = 0444),
	VM_STAT("nx_largepages_splitted", nx_lpage_splits, .mode = 0444),
	VM_STAT("max_mmu_page_hash_collisions", max_mmu_page_hash_collisions),
	अणु शून्य पूर्ण
पूर्ण;

u64 __पढ़ो_mostly host_xcr0;
u64 __पढ़ो_mostly supported_xcr0;
EXPORT_SYMBOL_GPL(supported_xcr0);

अटल काष्ठा kmem_cache *x86_fpu_cache;

अटल काष्ठा kmem_cache *x86_emulator_cache;

/*
 * When called, it means the previous get/set msr reached an invalid msr.
 * Return true अगर we want to ignore/silent this failed msr access.
 */
अटल bool kvm_msr_ignored_check(u32 msr, u64 data, bool ग_लिखो)
अणु
	स्थिर अक्षर *op = ग_लिखो ? "wrmsr" : "rdmsr";

	अगर (ignore_msrs) अणु
		अगर (report_ignored_msrs)
			kvm_pr_unimpl("ignored %s: 0x%x data 0x%llx\n",
				      op, msr, data);
		/* Mask the error */
		वापस true;
	पूर्ण अन्यथा अणु
		kvm_debug_ratelimited("unhandled %s: 0x%x data 0x%llx\n",
				      op, msr, data);
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा kmem_cache *kvm_alloc_emulator_cache(व्योम)
अणु
	अचिन्हित पूर्णांक useroffset = दुरत्व(काष्ठा x86_emulate_ctxt, src);
	अचिन्हित पूर्णांक size = माप(काष्ठा x86_emulate_ctxt);

	वापस kmem_cache_create_usercopy("x86_emulator", size,
					  __alignof__(काष्ठा x86_emulate_ctxt),
					  SLAB_ACCOUNT, useroffset,
					  size - useroffset, शून्य);
पूर्ण

अटल पूर्णांक emulator_fix_hypercall(काष्ठा x86_emulate_ctxt *ctxt);

अटल अंतरभूत व्योम kvm_async_pf_hash_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ASYNC_PF_PER_VCPU; i++)
		vcpu->arch.apf.gfns[i] = ~0;
पूर्ण

अटल व्योम kvm_on_user_वापस(काष्ठा user_वापस_notअगरier *urn)
अणु
	अचिन्हित slot;
	काष्ठा kvm_user_वापस_msrs *msrs
		= container_of(urn, काष्ठा kvm_user_वापस_msrs, urn);
	काष्ठा kvm_user_वापस_msr_values *values;
	अचिन्हित दीर्घ flags;

	/*
	 * Disabling irqs at this poपूर्णांक since the following code could be
	 * पूर्णांकerrupted and executed through kvm_arch_hardware_disable()
	 */
	local_irq_save(flags);
	अगर (msrs->रेजिस्टरed) अणु
		msrs->रेजिस्टरed = false;
		user_वापस_notअगरier_unरेजिस्टर(urn);
	पूर्ण
	local_irq_restore(flags);
	क्रम (slot = 0; slot < kvm_nr_uret_msrs; ++slot) अणु
		values = &msrs->values[slot];
		अगर (values->host != values->curr) अणु
			wrmsrl(kvm_uret_msrs_list[slot], values->host);
			values->curr = values->host;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_probe_user_वापस_msr(u32 msr)
अणु
	u64 val;
	पूर्णांक ret;

	preempt_disable();
	ret = rdmsrl_safe(msr, &val);
	अगर (ret)
		जाओ out;
	ret = wrmsrl_safe(msr, val);
out:
	preempt_enable();
	वापस ret;
पूर्ण

पूर्णांक kvm_add_user_वापस_msr(u32 msr)
अणु
	BUG_ON(kvm_nr_uret_msrs >= KVM_MAX_NR_USER_RETURN_MSRS);

	अगर (kvm_probe_user_वापस_msr(msr))
		वापस -1;

	kvm_uret_msrs_list[kvm_nr_uret_msrs] = msr;
	वापस kvm_nr_uret_msrs++;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_add_user_वापस_msr);

पूर्णांक kvm_find_user_वापस_msr(u32 msr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kvm_nr_uret_msrs; ++i) अणु
		अगर (kvm_uret_msrs_list[i] == msr)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_find_user_वापस_msr);

अटल व्योम kvm_user_वापस_msr_cpu_online(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा kvm_user_वापस_msrs *msrs = per_cpu_ptr(user_वापस_msrs, cpu);
	u64 value;
	पूर्णांक i;

	क्रम (i = 0; i < kvm_nr_uret_msrs; ++i) अणु
		rdmsrl_safe(kvm_uret_msrs_list[i], &value);
		msrs->values[i].host = value;
		msrs->values[i].curr = value;
	पूर्ण
पूर्ण

पूर्णांक kvm_set_user_वापस_msr(अचिन्हित slot, u64 value, u64 mask)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा kvm_user_वापस_msrs *msrs = per_cpu_ptr(user_वापस_msrs, cpu);
	पूर्णांक err;

	value = (value & mask) | (msrs->values[slot].host & ~mask);
	अगर (value == msrs->values[slot].curr)
		वापस 0;
	err = wrmsrl_safe(kvm_uret_msrs_list[slot], value);
	अगर (err)
		वापस 1;

	msrs->values[slot].curr = value;
	अगर (!msrs->रेजिस्टरed) अणु
		msrs->urn.on_user_वापस = kvm_on_user_वापस;
		user_वापस_notअगरier_रेजिस्टर(&msrs->urn);
		msrs->रेजिस्टरed = true;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_user_वापस_msr);

अटल व्योम drop_user_वापस_notअगरiers(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा kvm_user_वापस_msrs *msrs = per_cpu_ptr(user_वापस_msrs, cpu);

	अगर (msrs->रेजिस्टरed)
		kvm_on_user_वापस(&msrs->urn);
पूर्ण

u64 kvm_get_apic_base(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.apic_base;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_apic_base);

क्रमागत lapic_mode kvm_get_apic_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_apic_mode(kvm_get_apic_base(vcpu));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_apic_mode);

पूर्णांक kvm_set_apic_base(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	क्रमागत lapic_mode old_mode = kvm_get_apic_mode(vcpu);
	क्रमागत lapic_mode new_mode = kvm_apic_mode(msr_info->data);
	u64 reserved_bits = kvm_vcpu_reserved_gpa_bits_raw(vcpu) | 0x2ff |
		(guest_cpuid_has(vcpu, X86_FEATURE_X2APIC) ? 0 : X2APIC_ENABLE);

	अगर ((msr_info->data & reserved_bits) != 0 || new_mode == LAPIC_MODE_INVALID)
		वापस 1;
	अगर (!msr_info->host_initiated) अणु
		अगर (old_mode == LAPIC_MODE_X2APIC && new_mode == LAPIC_MODE_XAPIC)
			वापस 1;
		अगर (old_mode == LAPIC_MODE_DISABLED && new_mode == LAPIC_MODE_X2APIC)
			वापस 1;
	पूर्ण

	kvm_lapic_set_base(vcpu, msr_info->data);
	kvm_recalculate_apic_map(vcpu->kvm);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_apic_base);

यंत्रlinkage __visible noinstr व्योम kvm_spurious_fault(व्योम)
अणु
	/* Fault जबतक not rebooting.  We want the trace. */
	BUG_ON(!kvm_rebooting);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_spurious_fault);

#घोषणा EXCPT_BENIGN		0
#घोषणा EXCPT_CONTRIBUTORY	1
#घोषणा EXCPT_PF		2

अटल पूर्णांक exception_class(पूर्णांक vector)
अणु
	चयन (vector) अणु
	हाल PF_VECTOR:
		वापस EXCPT_PF;
	हाल DE_VECTOR:
	हाल TS_VECTOR:
	हाल NP_VECTOR:
	हाल SS_VECTOR:
	हाल GP_VECTOR:
		वापस EXCPT_CONTRIBUTORY;
	शेष:
		अवरोध;
	पूर्ण
	वापस EXCPT_BENIGN;
पूर्ण

#घोषणा EXCPT_FAULT		0
#घोषणा EXCPT_TRAP		1
#घोषणा EXCPT_ABORT		2
#घोषणा EXCPT_INTERRUPT		3

अटल पूर्णांक exception_type(पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक mask;

	अगर (WARN_ON(vector > 31 || vector == NMI_VECTOR))
		वापस EXCPT_INTERRUPT;

	mask = 1 << vector;

	/* #DB is trap, as inकाष्ठाion watchpoपूर्णांकs are handled अन्यथाwhere */
	अगर (mask & ((1 << DB_VECTOR) | (1 << BP_VECTOR) | (1 << OF_VECTOR)))
		वापस EXCPT_TRAP;

	अगर (mask & ((1 << DF_VECTOR) | (1 << MC_VECTOR)))
		वापस EXCPT_ABORT;

	/* Reserved exceptions will result in fault */
	वापस EXCPT_FAULT;
पूर्ण

व्योम kvm_deliver_exception_payload(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित nr = vcpu->arch.exception.nr;
	bool has_payload = vcpu->arch.exception.has_payload;
	अचिन्हित दीर्घ payload = vcpu->arch.exception.payload;

	अगर (!has_payload)
		वापस;

	चयन (nr) अणु
	हाल DB_VECTOR:
		/*
		 * "Certain debug exceptions may clear bit 0-3.  The
		 * reमुख्यing contents of the DR6 रेजिस्टर are never
		 * cleared by the processor".
		 */
		vcpu->arch.dr6 &= ~DR_TRAP_BITS;
		/*
		 * In order to reflect the #DB exception payload in guest
		 * dr6, three components need to be considered: active low
		 * bit, FIXED_1 bits and active high bits (e.g. DR6_BD,
		 * DR6_BS and DR6_BT)
		 * DR6_ACTIVE_LOW contains the FIXED_1 and active low bits.
		 * In the target guest dr6:
		 * FIXED_1 bits should always be set.
		 * Active low bits should be cleared अगर 1-setting in payload.
		 * Active high bits should be set अगर 1-setting in payload.
		 *
		 * Note, the payload is compatible with the pending debug
		 * exceptions/निकास qualअगरication under VMX, that active_low bits
		 * are active high in payload.
		 * So they need to be flipped क्रम DR6.
		 */
		vcpu->arch.dr6 |= DR6_ACTIVE_LOW;
		vcpu->arch.dr6 |= payload;
		vcpu->arch.dr6 ^= payload & DR6_ACTIVE_LOW;

		/*
		 * The #DB payload is defined as compatible with the 'pending
		 * debug exceptions' field under VMX, not DR6. While bit 12 is
		 * defined in the 'pending debug exceptions' field (enabled
		 * अवरोधpoपूर्णांक), it is reserved and must be zero in DR6.
		 */
		vcpu->arch.dr6 &= ~BIT(12);
		अवरोध;
	हाल PF_VECTOR:
		vcpu->arch.cr2 = payload;
		अवरोध;
	पूर्ण

	vcpu->arch.exception.has_payload = false;
	vcpu->arch.exception.payload = 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_deliver_exception_payload);

अटल व्योम kvm_multiple_exception(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित nr, bool has_error, u32 error_code,
	        bool has_payload, अचिन्हित दीर्घ payload, bool reinject)
अणु
	u32 prev_nr;
	पूर्णांक class1, class2;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	अगर (!vcpu->arch.exception.pending && !vcpu->arch.exception.injected) अणु
	queue:
		अगर (reinject) अणु
			/*
			 * On vmentry, vcpu->arch.exception.pending is only
			 * true अगर an event injection was blocked by
			 * nested_run_pending.  In that हाल, however,
			 * vcpu_enter_guest requests an immediate निकास,
			 * and the guest shouldn't proceed far enough to
			 * need reinjection.
			 */
			WARN_ON_ONCE(vcpu->arch.exception.pending);
			vcpu->arch.exception.injected = true;
			अगर (WARN_ON_ONCE(has_payload)) अणु
				/*
				 * A reinjected event has alपढ़ोy
				 * delivered its payload.
				 */
				has_payload = false;
				payload = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			vcpu->arch.exception.pending = true;
			vcpu->arch.exception.injected = false;
		पूर्ण
		vcpu->arch.exception.has_error_code = has_error;
		vcpu->arch.exception.nr = nr;
		vcpu->arch.exception.error_code = error_code;
		vcpu->arch.exception.has_payload = has_payload;
		vcpu->arch.exception.payload = payload;
		अगर (!is_guest_mode(vcpu))
			kvm_deliver_exception_payload(vcpu);
		वापस;
	पूर्ण

	/* to check exception */
	prev_nr = vcpu->arch.exception.nr;
	अगर (prev_nr == DF_VECTOR) अणु
		/* triple fault -> shutकरोwn */
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
		वापस;
	पूर्ण
	class1 = exception_class(prev_nr);
	class2 = exception_class(nr);
	अगर ((class1 == EXCPT_CONTRIBUTORY && class2 == EXCPT_CONTRIBUTORY)
		|| (class1 == EXCPT_PF && class2 != EXCPT_BENIGN)) अणु
		/*
		 * Generate द्विगुन fault per SDM Table 5-5.  Set
		 * exception.pending = true so that the द्विगुन fault
		 * can trigger a nested vmनिकास.
		 */
		vcpu->arch.exception.pending = true;
		vcpu->arch.exception.injected = false;
		vcpu->arch.exception.has_error_code = true;
		vcpu->arch.exception.nr = DF_VECTOR;
		vcpu->arch.exception.error_code = 0;
		vcpu->arch.exception.has_payload = false;
		vcpu->arch.exception.payload = 0;
	पूर्ण अन्यथा
		/* replace previous exception with a new one in a hope
		   that inकाष्ठाion re-execution will regenerate lost
		   exception */
		जाओ queue;
पूर्ण

व्योम kvm_queue_exception(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr)
अणु
	kvm_multiple_exception(vcpu, nr, false, 0, false, 0, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_queue_exception);

व्योम kvm_requeue_exception(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr)
अणु
	kvm_multiple_exception(vcpu, nr, false, 0, false, 0, true);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_requeue_exception);

व्योम kvm_queue_exception_p(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr,
			   अचिन्हित दीर्घ payload)
अणु
	kvm_multiple_exception(vcpu, nr, false, 0, true, payload, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_queue_exception_p);

अटल व्योम kvm_queue_exception_e_p(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr,
				    u32 error_code, अचिन्हित दीर्घ payload)
अणु
	kvm_multiple_exception(vcpu, nr, true, error_code,
			       true, payload, false);
पूर्ण

पूर्णांक kvm_complete_insn_gp(काष्ठा kvm_vcpu *vcpu, पूर्णांक err)
अणु
	अगर (err)
		kvm_inject_gp(vcpu, 0);
	अन्यथा
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_complete_insn_gp);

व्योम kvm_inject_page_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा x86_exception *fault)
अणु
	++vcpu->stat.pf_guest;
	vcpu->arch.exception.nested_apf =
		is_guest_mode(vcpu) && fault->async_page_fault;
	अगर (vcpu->arch.exception.nested_apf) अणु
		vcpu->arch.apf.nested_apf_token = fault->address;
		kvm_queue_exception_e(vcpu, PF_VECTOR, fault->error_code);
	पूर्ण अन्यथा अणु
		kvm_queue_exception_e_p(vcpu, PF_VECTOR, fault->error_code,
					fault->address);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_inject_page_fault);

bool kvm_inject_emulated_page_fault(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा x86_exception *fault)
अणु
	काष्ठा kvm_mmu *fault_mmu;
	WARN_ON_ONCE(fault->vector != PF_VECTOR);

	fault_mmu = fault->nested_page_fault ? vcpu->arch.mmu :
					       vcpu->arch.walk_mmu;

	/*
	 * Invalidate the TLB entry क्रम the faulting address, अगर it exists,
	 * अन्यथा the access will fault indefinitely (and to emulate hardware).
	 */
	अगर ((fault->error_code & PFERR_PRESENT_MASK) &&
	    !(fault->error_code & PFERR_RSVD_MASK))
		kvm_mmu_invalidate_gva(vcpu, fault_mmu, fault->address,
				       fault_mmu->root_hpa);

	fault_mmu->inject_page_fault(vcpu, fault);
	वापस fault->nested_page_fault;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_inject_emulated_page_fault);

व्योम kvm_inject_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	atomic_inc(&vcpu->arch.nmi_queued);
	kvm_make_request(KVM_REQ_NMI, vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_inject_nmi);

व्योम kvm_queue_exception_e(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr, u32 error_code)
अणु
	kvm_multiple_exception(vcpu, nr, true, error_code, false, 0, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_queue_exception_e);

व्योम kvm_requeue_exception_e(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr, u32 error_code)
अणु
	kvm_multiple_exception(vcpu, nr, true, error_code, false, 0, true);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_requeue_exception_e);

/*
 * Checks अगर cpl <= required_cpl; अगर true, वापस true.  Otherwise queue
 * a #GP and वापस false.
 */
bool kvm_require_cpl(काष्ठा kvm_vcpu *vcpu, पूर्णांक required_cpl)
अणु
	अगर (अटल_call(kvm_x86_get_cpl)(vcpu) <= required_cpl)
		वापस true;
	kvm_queue_exception_e(vcpu, GP_VECTOR, 0);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_require_cpl);

bool kvm_require_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr)
अणु
	अगर ((dr != 4 && dr != 5) || !kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_DE))
		वापस true;

	kvm_queue_exception(vcpu, UD_VECTOR);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_require_dr);

/*
 * This function will be used to पढ़ो from the physical memory of the currently
 * running guest. The dअगरference to kvm_vcpu_पढ़ो_guest_page is that this function
 * can पढ़ो from guest physical or from the guest's guest physical memory.
 */
पूर्णांक kvm_पढ़ो_guest_page_mmu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
			    gfn_t ngfn, व्योम *data, पूर्णांक offset, पूर्णांक len,
			    u32 access)
अणु
	काष्ठा x86_exception exception;
	gfn_t real_gfn;
	gpa_t ngpa;

	ngpa     = gfn_to_gpa(ngfn);
	real_gfn = mmu->translate_gpa(vcpu, ngpa, access, &exception);
	अगर (real_gfn == UNMAPPED_GVA)
		वापस -EFAULT;

	real_gfn = gpa_to_gfn(real_gfn);

	वापस kvm_vcpu_पढ़ो_guest_page(vcpu, real_gfn, data, offset, len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest_page_mmu);

अटल पूर्णांक kvm_पढ़ो_nested_guest_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			       व्योम *data, पूर्णांक offset, पूर्णांक len, u32 access)
अणु
	वापस kvm_पढ़ो_guest_page_mmu(vcpu, vcpu->arch.walk_mmu, gfn,
				       data, offset, len, access);
पूर्ण

अटल अंतरभूत u64 pdptr_rsvd_bits(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.reserved_gpa_bits | rsvd_bits(5, 8) | rsvd_bits(1, 2);
पूर्ण

/*
 * Load the pae pdptrs.  Return 1 अगर they are all valid, 0 otherwise.
 */
पूर्णांक load_pdptrs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu, अचिन्हित दीर्घ cr3)
अणु
	gfn_t pdpt_gfn = cr3 >> PAGE_SHIFT;
	अचिन्हित offset = ((cr3 & (PAGE_SIZE-1)) >> 5) << 2;
	पूर्णांक i;
	पूर्णांक ret;
	u64 pdpte[ARRAY_SIZE(mmu->pdptrs)];

	ret = kvm_पढ़ो_guest_page_mmu(vcpu, mmu, pdpt_gfn, pdpte,
				      offset * माप(u64), माप(pdpte),
				      PFERR_USER_MASK|PFERR_WRITE_MASK);
	अगर (ret < 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(pdpte); ++i) अणु
		अगर ((pdpte[i] & PT_PRESENT_MASK) &&
		    (pdpte[i] & pdptr_rsvd_bits(vcpu))) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = 1;

	स_नकल(mmu->pdptrs, pdpte, माप(mmu->pdptrs));
	kvm_रेजिस्टर_mark_dirty(vcpu, VCPU_EXREG_PDPTR);

out:

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(load_pdptrs);

bool pdptrs_changed(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 pdpte[ARRAY_SIZE(vcpu->arch.walk_mmu->pdptrs)];
	पूर्णांक offset;
	gfn_t gfn;
	पूर्णांक r;

	अगर (!is_pae_paging(vcpu))
		वापस false;

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_PDPTR))
		वापस true;

	gfn = (kvm_पढ़ो_cr3(vcpu) & 0xffffffe0ul) >> PAGE_SHIFT;
	offset = (kvm_पढ़ो_cr3(vcpu) & 0xffffffe0ul) & (PAGE_SIZE - 1);
	r = kvm_पढ़ो_nested_guest_page(vcpu, gfn, pdpte, offset, माप(pdpte),
				       PFERR_USER_MASK | PFERR_WRITE_MASK);
	अगर (r < 0)
		वापस true;

	वापस स_भेद(pdpte, vcpu->arch.walk_mmu->pdptrs, माप(pdpte)) != 0;
पूर्ण
EXPORT_SYMBOL_GPL(pdptrs_changed);

व्योम kvm_post_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ old_cr0, अचिन्हित दीर्घ cr0)
अणु
	अचिन्हित दीर्घ update_bits = X86_CR0_PG | X86_CR0_WP;

	अगर ((cr0 ^ old_cr0) & X86_CR0_PG) अणु
		kvm_clear_async_pf_completion_queue(vcpu);
		kvm_async_pf_hash_reset(vcpu);
	पूर्ण

	अगर ((cr0 ^ old_cr0) & update_bits)
		kvm_mmu_reset_context(vcpu);

	अगर (((cr0 ^ old_cr0) & X86_CR0_CD) &&
	    kvm_arch_has_noncoherent_dma(vcpu->kvm) &&
	    !kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_CD_NW_CLEARED))
		kvm_zap_gfn_range(vcpu->kvm, 0, ~0ULL);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_post_set_cr0);

पूर्णांक kvm_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0)
अणु
	अचिन्हित दीर्घ old_cr0 = kvm_पढ़ो_cr0(vcpu);
	अचिन्हित दीर्घ pdptr_bits = X86_CR0_CD | X86_CR0_NW | X86_CR0_PG;

	cr0 |= X86_CR0_ET;

#अगर_घोषित CONFIG_X86_64
	अगर (cr0 & 0xffffffff00000000UL)
		वापस 1;
#पूर्ण_अगर

	cr0 &= ~CR0_RESERVED_BITS;

	अगर ((cr0 & X86_CR0_NW) && !(cr0 & X86_CR0_CD))
		वापस 1;

	अगर ((cr0 & X86_CR0_PG) && !(cr0 & X86_CR0_PE))
		वापस 1;

#अगर_घोषित CONFIG_X86_64
	अगर ((vcpu->arch.efer & EFER_LME) && !is_paging(vcpu) &&
	    (cr0 & X86_CR0_PG)) अणु
		पूर्णांक cs_db, cs_l;

		अगर (!is_pae(vcpu))
			वापस 1;
		अटल_call(kvm_x86_get_cs_db_l_bits)(vcpu, &cs_db, &cs_l);
		अगर (cs_l)
			वापस 1;
	पूर्ण
#पूर्ण_अगर
	अगर (!(vcpu->arch.efer & EFER_LME) && (cr0 & X86_CR0_PG) &&
	    is_pae(vcpu) && ((cr0 ^ old_cr0) & pdptr_bits) &&
	    !load_pdptrs(vcpu, vcpu->arch.walk_mmu, kvm_पढ़ो_cr3(vcpu)))
		वापस 1;

	अगर (!(cr0 & X86_CR0_PG) && kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PCIDE))
		वापस 1;

	अटल_call(kvm_x86_set_cr0)(vcpu, cr0);

	kvm_post_set_cr0(vcpu, old_cr0, cr0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_cr0);

व्योम kvm_lmsw(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ msw)
अणु
	(व्योम)kvm_set_cr0(vcpu, kvm_पढ़ो_cr0_bits(vcpu, ~0x0eul) | (msw & 0x0f));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lmsw);

व्योम kvm_load_guest_xsave_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.guest_state_रक्षित)
		वापस;

	अगर (kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_OSXSAVE)) अणु

		अगर (vcpu->arch.xcr0 != host_xcr0)
			xsetbv(XCR_XFEATURE_ENABLED_MASK, vcpu->arch.xcr0);

		अगर (vcpu->arch.xsaves_enabled &&
		    vcpu->arch.ia32_xss != host_xss)
			wrmsrl(MSR_IA32_XSS, vcpu->arch.ia32_xss);
	पूर्ण

	अगर (अटल_cpu_has(X86_FEATURE_PKU) &&
	    (kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PKE) ||
	     (vcpu->arch.xcr0 & XFEATURE_MASK_PKRU)) &&
	    vcpu->arch.pkru != vcpu->arch.host_pkru)
		__ग_लिखो_pkru(vcpu->arch.pkru);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_load_guest_xsave_state);

व्योम kvm_load_host_xsave_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.guest_state_रक्षित)
		वापस;

	अगर (अटल_cpu_has(X86_FEATURE_PKU) &&
	    (kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PKE) ||
	     (vcpu->arch.xcr0 & XFEATURE_MASK_PKRU))) अणु
		vcpu->arch.pkru = rdpkru();
		अगर (vcpu->arch.pkru != vcpu->arch.host_pkru)
			__ग_लिखो_pkru(vcpu->arch.host_pkru);
	पूर्ण

	अगर (kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_OSXSAVE)) अणु

		अगर (vcpu->arch.xcr0 != host_xcr0)
			xsetbv(XCR_XFEATURE_ENABLED_MASK, host_xcr0);

		अगर (vcpu->arch.xsaves_enabled &&
		    vcpu->arch.ia32_xss != host_xss)
			wrmsrl(MSR_IA32_XSS, host_xss);
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(kvm_load_host_xsave_state);

अटल पूर्णांक __kvm_set_xcr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 xcr)
अणु
	u64 xcr0 = xcr;
	u64 old_xcr0 = vcpu->arch.xcr0;
	u64 valid_bits;

	/* Only support XCR_XFEATURE_ENABLED_MASK(xcr0) now  */
	अगर (index != XCR_XFEATURE_ENABLED_MASK)
		वापस 1;
	अगर (!(xcr0 & XFEATURE_MASK_FP))
		वापस 1;
	अगर ((xcr0 & XFEATURE_MASK_YMM) && !(xcr0 & XFEATURE_MASK_SSE))
		वापस 1;

	/*
	 * Do not allow the guest to set bits that we करो not support
	 * saving.  However, xcr0 bit 0 is always set, even अगर the
	 * emulated CPU करोes not support XSAVE (see fx_init).
	 */
	valid_bits = vcpu->arch.guest_supported_xcr0 | XFEATURE_MASK_FP;
	अगर (xcr0 & ~valid_bits)
		वापस 1;

	अगर ((!(xcr0 & XFEATURE_MASK_BNDREGS)) !=
	    (!(xcr0 & XFEATURE_MASK_BNDCSR)))
		वापस 1;

	अगर (xcr0 & XFEATURE_MASK_AVX512) अणु
		अगर (!(xcr0 & XFEATURE_MASK_YMM))
			वापस 1;
		अगर ((xcr0 & XFEATURE_MASK_AVX512) != XFEATURE_MASK_AVX512)
			वापस 1;
	पूर्ण
	vcpu->arch.xcr0 = xcr0;

	अगर ((xcr0 ^ old_xcr0) & XFEATURE_MASK_EXTEND)
		kvm_update_cpuid_runसमय(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_emulate_xsetbv(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (अटल_call(kvm_x86_get_cpl)(vcpu) != 0 ||
	    __kvm_set_xcr(vcpu, kvm_rcx_पढ़ो(vcpu), kvm_पढ़ो_edx_eax(vcpu))) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_xsetbv);

bool kvm_is_valid_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	अगर (cr4 & cr4_reserved_bits)
		वापस false;

	अगर (cr4 & vcpu->arch.cr4_guest_rsvd_bits)
		वापस false;

	वापस अटल_call(kvm_x86_is_valid_cr4)(vcpu, cr4);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_is_valid_cr4);

व्योम kvm_post_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ old_cr4, अचिन्हित दीर्घ cr4)
अणु
	अचिन्हित दीर्घ mmu_role_bits = X86_CR4_PGE | X86_CR4_PSE | X86_CR4_PAE |
				      X86_CR4_SMEP | X86_CR4_SMAP | X86_CR4_PKE;

	अगर (((cr4 ^ old_cr4) & mmu_role_bits) ||
	    (!(cr4 & X86_CR4_PCIDE) && (old_cr4 & X86_CR4_PCIDE)))
		kvm_mmu_reset_context(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_post_set_cr4);

पूर्णांक kvm_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	अचिन्हित दीर्घ old_cr4 = kvm_पढ़ो_cr4(vcpu);
	अचिन्हित दीर्घ pdptr_bits = X86_CR4_PGE | X86_CR4_PSE | X86_CR4_PAE |
				   X86_CR4_SMEP;

	अगर (!kvm_is_valid_cr4(vcpu, cr4))
		वापस 1;

	अगर (is_दीर्घ_mode(vcpu)) अणु
		अगर (!(cr4 & X86_CR4_PAE))
			वापस 1;
		अगर ((cr4 ^ old_cr4) & X86_CR4_LA57)
			वापस 1;
	पूर्ण अन्यथा अगर (is_paging(vcpu) && (cr4 & X86_CR4_PAE)
		   && ((cr4 ^ old_cr4) & pdptr_bits)
		   && !load_pdptrs(vcpu, vcpu->arch.walk_mmu,
				   kvm_पढ़ो_cr3(vcpu)))
		वापस 1;

	अगर ((cr4 & X86_CR4_PCIDE) && !(old_cr4 & X86_CR4_PCIDE)) अणु
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_PCID))
			वापस 1;

		/* PCID can not be enabled when cr3[11:0]!=000H or EFER.LMA=0 */
		अगर ((kvm_पढ़ो_cr3(vcpu) & X86_CR3_PCID_MASK) || !is_दीर्घ_mode(vcpu))
			वापस 1;
	पूर्ण

	अटल_call(kvm_x86_set_cr4)(vcpu, cr4);

	kvm_post_set_cr4(vcpu, old_cr4, cr4);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_cr4);

पूर्णांक kvm_set_cr3(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr3)
अणु
	bool skip_tlb_flush = false;
#अगर_घोषित CONFIG_X86_64
	bool pcid_enabled = kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PCIDE);

	अगर (pcid_enabled) अणु
		skip_tlb_flush = cr3 & X86_CR3_PCID_NOFLUSH;
		cr3 &= ~X86_CR3_PCID_NOFLUSH;
	पूर्ण
#पूर्ण_अगर

	अगर (cr3 == kvm_पढ़ो_cr3(vcpu) && !pdptrs_changed(vcpu)) अणु
		अगर (!skip_tlb_flush) अणु
			kvm_mmu_sync_roots(vcpu);
			kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Do not condition the GPA check on दीर्घ mode, this helper is used to
	 * stuff CR3, e.g. क्रम RSM emulation, and there is no guarantee that
	 * the current vCPU mode is accurate.
	 */
	अगर (kvm_vcpu_is_illegal_gpa(vcpu, cr3))
		वापस 1;

	अगर (is_pae_paging(vcpu) && !load_pdptrs(vcpu, vcpu->arch.walk_mmu, cr3))
		वापस 1;

	kvm_mmu_new_pgd(vcpu, cr3, skip_tlb_flush, skip_tlb_flush);
	vcpu->arch.cr3 = cr3;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR3);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_cr3);

पूर्णांक kvm_set_cr8(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr8)
अणु
	अगर (cr8 & CR8_RESERVED_BITS)
		वापस 1;
	अगर (lapic_in_kernel(vcpu))
		kvm_lapic_set_tpr(vcpu, cr8);
	अन्यथा
		vcpu->arch.cr8 = cr8;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_cr8);

अचिन्हित दीर्घ kvm_get_cr8(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (lapic_in_kernel(vcpu))
		वापस kvm_lapic_get_cr8(vcpu);
	अन्यथा
		वापस vcpu->arch.cr8;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_cr8);

अटल व्योम kvm_update_dr0123(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	अगर (!(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)) अणु
		क्रम (i = 0; i < KVM_NR_DB_REGS; i++)
			vcpu->arch.eff_db[i] = vcpu->arch.db[i];
		vcpu->arch.चयन_db_regs |= KVM_DEBUGREG_RELOAD;
	पूर्ण
पूर्ण

व्योम kvm_update_dr7(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ dr7;

	अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)
		dr7 = vcpu->arch.guest_debug_dr7;
	अन्यथा
		dr7 = vcpu->arch.dr7;
	अटल_call(kvm_x86_set_dr7)(vcpu, dr7);
	vcpu->arch.चयन_db_regs &= ~KVM_DEBUGREG_BP_ENABLED;
	अगर (dr7 & DR7_BP_EN_MASK)
		vcpu->arch.चयन_db_regs |= KVM_DEBUGREG_BP_ENABLED;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_update_dr7);

अटल u64 kvm_dr6_fixed(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 fixed = DR6_FIXED_1;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_RTM))
		fixed |= DR6_RTM;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_BUS_LOCK_DETECT))
		fixed |= DR6_BUS_LOCK;
	वापस fixed;
पूर्ण

पूर्णांक kvm_set_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr, अचिन्हित दीर्घ val)
अणु
	माप_प्रकार size = ARRAY_SIZE(vcpu->arch.db);

	चयन (dr) अणु
	हाल 0 ... 3:
		vcpu->arch.db[array_index_nospec(dr, size)] = val;
		अगर (!(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP))
			vcpu->arch.eff_db[dr] = val;
		अवरोध;
	हाल 4:
	हाल 6:
		अगर (!kvm_dr6_valid(val))
			वापस 1; /* #GP */
		vcpu->arch.dr6 = (val & DR6_VOLATILE) | kvm_dr6_fixed(vcpu);
		अवरोध;
	हाल 5:
	शेष: /* 7 */
		अगर (!kvm_dr7_valid(val))
			वापस 1; /* #GP */
		vcpu->arch.dr7 = (val & DR7_VOLATILE) | DR7_FIXED_1;
		kvm_update_dr7(vcpu);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_dr);

व्योम kvm_get_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr, अचिन्हित दीर्घ *val)
अणु
	माप_प्रकार size = ARRAY_SIZE(vcpu->arch.db);

	चयन (dr) अणु
	हाल 0 ... 3:
		*val = vcpu->arch.db[array_index_nospec(dr, size)];
		अवरोध;
	हाल 4:
	हाल 6:
		*val = vcpu->arch.dr6;
		अवरोध;
	हाल 5:
	शेष: /* 7 */
		*val = vcpu->arch.dr7;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_dr);

पूर्णांक kvm_emulate_rdpmc(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 ecx = kvm_rcx_पढ़ो(vcpu);
	u64 data;

	अगर (kvm_pmu_rdpmc(vcpu, ecx, &data)) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	kvm_rax_ग_लिखो(vcpu, (u32)data);
	kvm_rdx_ग_लिखो(vcpu, data >> 32);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_rdpmc);

/*
 * List of msr numbers which we expose to userspace through KVM_GET_MSRS
 * and KVM_SET_MSRS, and KVM_GET_MSR_INDEX_LIST.
 *
 * The three MSR lists(msrs_to_save, emulated_msrs, msr_based_features)
 * extract the supported MSRs from the related स्थिर lists.
 * msrs_to_save is selected from the msrs_to_save_all to reflect the
 * capabilities of the host cpu. This capabilities test skips MSRs that are
 * kvm-specअगरic. Those are put in emulated_msrs_all; filtering of emulated_msrs
 * may depend on host भवization features rather than host cpu features.
 */

अटल स्थिर u32 msrs_to_save_all[] = अणु
	MSR_IA32_SYSENTER_CS, MSR_IA32_SYSENTER_ESP, MSR_IA32_SYSENTER_EIP,
	MSR_STAR,
#अगर_घोषित CONFIG_X86_64
	MSR_CSTAR, MSR_KERNEL_GS_BASE, MSR_SYSCALL_MASK, MSR_LSTAR,
#पूर्ण_अगर
	MSR_IA32_TSC, MSR_IA32_CR_PAT, MSR_VM_HSAVE_PA,
	MSR_IA32_FEAT_CTL, MSR_IA32_BNDCFGS, MSR_TSC_AUX,
	MSR_IA32_SPEC_CTRL,
	MSR_IA32_RTIT_CTL, MSR_IA32_RTIT_STATUS, MSR_IA32_RTIT_CR3_MATCH,
	MSR_IA32_RTIT_OUTPUT_BASE, MSR_IA32_RTIT_OUTPUT_MASK,
	MSR_IA32_RTIT_ADDR0_A, MSR_IA32_RTIT_ADDR0_B,
	MSR_IA32_RTIT_ADDR1_A, MSR_IA32_RTIT_ADDR1_B,
	MSR_IA32_RTIT_ADDR2_A, MSR_IA32_RTIT_ADDR2_B,
	MSR_IA32_RTIT_ADDR3_A, MSR_IA32_RTIT_ADDR3_B,
	MSR_IA32_UMWAIT_CONTROL,

	MSR_ARCH_PERFMON_FIXED_CTR0, MSR_ARCH_PERFMON_FIXED_CTR1,
	MSR_ARCH_PERFMON_FIXED_CTR0 + 2, MSR_ARCH_PERFMON_FIXED_CTR0 + 3,
	MSR_CORE_PERF_FIXED_CTR_CTRL, MSR_CORE_PERF_GLOBAL_STATUS,
	MSR_CORE_PERF_GLOBAL_CTRL, MSR_CORE_PERF_GLOBAL_OVF_CTRL,
	MSR_ARCH_PERFMON_PERFCTR0, MSR_ARCH_PERFMON_PERFCTR1,
	MSR_ARCH_PERFMON_PERFCTR0 + 2, MSR_ARCH_PERFMON_PERFCTR0 + 3,
	MSR_ARCH_PERFMON_PERFCTR0 + 4, MSR_ARCH_PERFMON_PERFCTR0 + 5,
	MSR_ARCH_PERFMON_PERFCTR0 + 6, MSR_ARCH_PERFMON_PERFCTR0 + 7,
	MSR_ARCH_PERFMON_PERFCTR0 + 8, MSR_ARCH_PERFMON_PERFCTR0 + 9,
	MSR_ARCH_PERFMON_PERFCTR0 + 10, MSR_ARCH_PERFMON_PERFCTR0 + 11,
	MSR_ARCH_PERFMON_PERFCTR0 + 12, MSR_ARCH_PERFMON_PERFCTR0 + 13,
	MSR_ARCH_PERFMON_PERFCTR0 + 14, MSR_ARCH_PERFMON_PERFCTR0 + 15,
	MSR_ARCH_PERFMON_PERFCTR0 + 16, MSR_ARCH_PERFMON_PERFCTR0 + 17,
	MSR_ARCH_PERFMON_EVENTSEL0, MSR_ARCH_PERFMON_EVENTSEL1,
	MSR_ARCH_PERFMON_EVENTSEL0 + 2, MSR_ARCH_PERFMON_EVENTSEL0 + 3,
	MSR_ARCH_PERFMON_EVENTSEL0 + 4, MSR_ARCH_PERFMON_EVENTSEL0 + 5,
	MSR_ARCH_PERFMON_EVENTSEL0 + 6, MSR_ARCH_PERFMON_EVENTSEL0 + 7,
	MSR_ARCH_PERFMON_EVENTSEL0 + 8, MSR_ARCH_PERFMON_EVENTSEL0 + 9,
	MSR_ARCH_PERFMON_EVENTSEL0 + 10, MSR_ARCH_PERFMON_EVENTSEL0 + 11,
	MSR_ARCH_PERFMON_EVENTSEL0 + 12, MSR_ARCH_PERFMON_EVENTSEL0 + 13,
	MSR_ARCH_PERFMON_EVENTSEL0 + 14, MSR_ARCH_PERFMON_EVENTSEL0 + 15,
	MSR_ARCH_PERFMON_EVENTSEL0 + 16, MSR_ARCH_PERFMON_EVENTSEL0 + 17,
पूर्ण;

अटल u32 msrs_to_save[ARRAY_SIZE(msrs_to_save_all)];
अटल अचिन्हित num_msrs_to_save;

अटल स्थिर u32 emulated_msrs_all[] = अणु
	MSR_KVM_SYSTEM_TIME, MSR_KVM_WALL_CLOCK,
	MSR_KVM_SYSTEM_TIME_NEW, MSR_KVM_WALL_CLOCK_NEW,
	HV_X64_MSR_GUEST_OS_ID, HV_X64_MSR_HYPERCALL,
	HV_X64_MSR_TIME_REF_COUNT, HV_X64_MSR_REFERENCE_TSC,
	HV_X64_MSR_TSC_FREQUENCY, HV_X64_MSR_APIC_FREQUENCY,
	HV_X64_MSR_CRASH_P0, HV_X64_MSR_CRASH_P1, HV_X64_MSR_CRASH_P2,
	HV_X64_MSR_CRASH_P3, HV_X64_MSR_CRASH_P4, HV_X64_MSR_CRASH_CTL,
	HV_X64_MSR_RESET,
	HV_X64_MSR_VP_INDEX,
	HV_X64_MSR_VP_RUNTIME,
	HV_X64_MSR_SCONTROL,
	HV_X64_MSR_STIMER0_CONFIG,
	HV_X64_MSR_VP_ASSIST_PAGE,
	HV_X64_MSR_REENLIGHTENMENT_CONTROL, HV_X64_MSR_TSC_EMULATION_CONTROL,
	HV_X64_MSR_TSC_EMULATION_STATUS,
	HV_X64_MSR_SYNDBG_OPTIONS,
	HV_X64_MSR_SYNDBG_CONTROL, HV_X64_MSR_SYNDBG_STATUS,
	HV_X64_MSR_SYNDBG_SEND_BUFFER, HV_X64_MSR_SYNDBG_RECV_BUFFER,
	HV_X64_MSR_SYNDBG_PENDING_BUFFER,

	MSR_KVM_ASYNC_PF_EN, MSR_KVM_STEAL_TIME,
	MSR_KVM_PV_EOI_EN, MSR_KVM_ASYNC_PF_INT, MSR_KVM_ASYNC_PF_ACK,

	MSR_IA32_TSC_ADJUST,
	MSR_IA32_TSC_DEADLINE,
	MSR_IA32_ARCH_CAPABILITIES,
	MSR_IA32_PERF_CAPABILITIES,
	MSR_IA32_MISC_ENABLE,
	MSR_IA32_MCG_STATUS,
	MSR_IA32_MCG_CTL,
	MSR_IA32_MCG_EXT_CTL,
	MSR_IA32_SMBASE,
	MSR_SMI_COUNT,
	MSR_PLATFORM_INFO,
	MSR_MISC_FEATURES_ENABLES,
	MSR_AMD64_VIRT_SPEC_CTRL,
	MSR_IA32_POWER_CTL,
	MSR_IA32_UCODE_REV,

	/*
	 * The following list leaves out MSRs whose values are determined
	 * by arch/x86/kvm/vmx/nested.c based on CPUID or other MSRs.
	 * We always support the "true" VMX control MSRs, even अगर the host
	 * processor करोes not, so I am putting these रेजिस्टरs here rather
	 * than in msrs_to_save_all.
	 */
	MSR_IA32_VMX_BASIC,
	MSR_IA32_VMX_TRUE_PINBASED_CTLS,
	MSR_IA32_VMX_TRUE_PROCBASED_CTLS,
	MSR_IA32_VMX_TRUE_EXIT_CTLS,
	MSR_IA32_VMX_TRUE_ENTRY_CTLS,
	MSR_IA32_VMX_MISC,
	MSR_IA32_VMX_CR0_FIXED0,
	MSR_IA32_VMX_CR4_FIXED0,
	MSR_IA32_VMX_VMCS_ENUM,
	MSR_IA32_VMX_PROCBASED_CTLS2,
	MSR_IA32_VMX_EPT_VPID_CAP,
	MSR_IA32_VMX_VMFUNC,

	MSR_K7_HWCR,
	MSR_KVM_POLL_CONTROL,
पूर्ण;

अटल u32 emulated_msrs[ARRAY_SIZE(emulated_msrs_all)];
अटल अचिन्हित num_emulated_msrs;

/*
 * List of msr numbers which are used to expose MSR-based features that
 * can be used by a hypervisor to validate requested CPU features.
 */
अटल स्थिर u32 msr_based_features_all[] = अणु
	MSR_IA32_VMX_BASIC,
	MSR_IA32_VMX_TRUE_PINBASED_CTLS,
	MSR_IA32_VMX_PINBASED_CTLS,
	MSR_IA32_VMX_TRUE_PROCBASED_CTLS,
	MSR_IA32_VMX_PROCBASED_CTLS,
	MSR_IA32_VMX_TRUE_EXIT_CTLS,
	MSR_IA32_VMX_EXIT_CTLS,
	MSR_IA32_VMX_TRUE_ENTRY_CTLS,
	MSR_IA32_VMX_ENTRY_CTLS,
	MSR_IA32_VMX_MISC,
	MSR_IA32_VMX_CR0_FIXED0,
	MSR_IA32_VMX_CR0_FIXED1,
	MSR_IA32_VMX_CR4_FIXED0,
	MSR_IA32_VMX_CR4_FIXED1,
	MSR_IA32_VMX_VMCS_ENUM,
	MSR_IA32_VMX_PROCBASED_CTLS2,
	MSR_IA32_VMX_EPT_VPID_CAP,
	MSR_IA32_VMX_VMFUNC,

	MSR_F10H_DECFG,
	MSR_IA32_UCODE_REV,
	MSR_IA32_ARCH_CAPABILITIES,
	MSR_IA32_PERF_CAPABILITIES,
पूर्ण;

अटल u32 msr_based_features[ARRAY_SIZE(msr_based_features_all)];
अटल अचिन्हित पूर्णांक num_msr_based_features;

अटल u64 kvm_get_arch_capabilities(व्योम)
अणु
	u64 data = 0;

	अगर (boot_cpu_has(X86_FEATURE_ARCH_CAPABILITIES))
		rdmsrl(MSR_IA32_ARCH_CAPABILITIES, data);

	/*
	 * If nx_huge_pages is enabled, KVM's shaकरोw paging will ensure that
	 * the nested hypervisor runs with NX huge pages.  If it is not,
	 * L1 is anyway vulnerable to ITLB_MULTIHIT exploits from other
	 * L1 guests, so it need not worry about its own (L2) guests.
	 */
	data |= ARCH_CAP_PSCHANGE_MC_NO;

	/*
	 * If we're करोing cache flushes (either "always" or "cond")
	 * we will करो one whenever the guest करोes a vmlaunch/vmresume.
	 * If an outer hypervisor is करोing the cache flush क्रम us
	 * (VMENTER_L1D_FLUSH_NESTED_VM), we can safely pass that
	 * capability to the guest too, and अगर EPT is disabled we're not
	 * vulnerable.  Overall, only VMENTER_L1D_FLUSH_NEVER will
	 * require a nested hypervisor to करो a flush of its own.
	 */
	अगर (l1tf_vmx_mitigation != VMENTER_L1D_FLUSH_NEVER)
		data |= ARCH_CAP_SKIP_VMENTRY_L1DFLUSH;

	अगर (!boot_cpu_has_bug(X86_BUG_CPU_MELTDOWN))
		data |= ARCH_CAP_RDCL_NO;
	अगर (!boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS))
		data |= ARCH_CAP_SSB_NO;
	अगर (!boot_cpu_has_bug(X86_BUG_MDS))
		data |= ARCH_CAP_MDS_NO;

	अगर (!boot_cpu_has(X86_FEATURE_RTM)) अणु
		/*
		 * If RTM=0 because the kernel has disabled TSX, the host might
		 * have TAA_NO or TSX_CTRL.  Clear TAA_NO (the guest sees RTM=0
		 * and thereक्रमe knows that there cannot be TAA) but keep
		 * TSX_CTRL: some buggy userspaces leave it set on tsx=on hosts,
		 * and we want to allow migrating those guests to tsx=off hosts.
		 */
		data &= ~ARCH_CAP_TAA_NO;
	पूर्ण अन्यथा अगर (!boot_cpu_has_bug(X86_BUG_TAA)) अणु
		data |= ARCH_CAP_TAA_NO;
	पूर्ण अन्यथा अणु
		/*
		 * Nothing to करो here; we emulate TSX_CTRL अगर present on the
		 * host so the guest can choose between disabling TSX or
		 * using VERW to clear CPU buffers.
		 */
	पूर्ण

	वापस data;
पूर्ण

अटल पूर्णांक kvm_get_msr_feature(काष्ठा kvm_msr_entry *msr)
अणु
	चयन (msr->index) अणु
	हाल MSR_IA32_ARCH_CAPABILITIES:
		msr->data = kvm_get_arch_capabilities();
		अवरोध;
	हाल MSR_IA32_UCODE_REV:
		rdmsrl_safe(msr->index, &msr->data);
		अवरोध;
	शेष:
		वापस अटल_call(kvm_x86_get_msr_feature)(msr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_get_msr_feature(काष्ठा kvm_vcpu *vcpu, अचिन्हित index, u64 *data)
अणु
	काष्ठा kvm_msr_entry msr;
	पूर्णांक r;

	msr.index = index;
	r = kvm_get_msr_feature(&msr);

	अगर (r == KVM_MSR_RET_INVALID) अणु
		/* Unconditionally clear the output क्रम simplicity */
		*data = 0;
		अगर (kvm_msr_ignored_check(index, 0, false))
			r = 0;
	पूर्ण

	अगर (r)
		वापस r;

	*data = msr.data;

	वापस 0;
पूर्ण

अटल bool __kvm_valid_efer(काष्ठा kvm_vcpu *vcpu, u64 efer)
अणु
	अगर (efer & EFER_FFXSR && !guest_cpuid_has(vcpu, X86_FEATURE_FXSR_OPT))
		वापस false;

	अगर (efer & EFER_SVME && !guest_cpuid_has(vcpu, X86_FEATURE_SVM))
		वापस false;

	अगर (efer & (EFER_LME | EFER_LMA) &&
	    !guest_cpuid_has(vcpu, X86_FEATURE_LM))
		वापस false;

	अगर (efer & EFER_NX && !guest_cpuid_has(vcpu, X86_FEATURE_NX))
		वापस false;

	वापस true;

पूर्ण
bool kvm_valid_efer(काष्ठा kvm_vcpu *vcpu, u64 efer)
अणु
	अगर (efer & efer_reserved_bits)
		वापस false;

	वापस __kvm_valid_efer(vcpu, efer);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_valid_efer);

अटल पूर्णांक set_efer(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	u64 old_efer = vcpu->arch.efer;
	u64 efer = msr_info->data;
	पूर्णांक r;

	अगर (efer & efer_reserved_bits)
		वापस 1;

	अगर (!msr_info->host_initiated) अणु
		अगर (!__kvm_valid_efer(vcpu, efer))
			वापस 1;

		अगर (is_paging(vcpu) &&
		    (vcpu->arch.efer & EFER_LME) != (efer & EFER_LME))
			वापस 1;
	पूर्ण

	efer &= ~EFER_LMA;
	efer |= vcpu->arch.efer & EFER_LMA;

	r = अटल_call(kvm_x86_set_efer)(vcpu, efer);
	अगर (r) अणु
		WARN_ON(r > 0);
		वापस r;
	पूर्ण

	/* Update reserved bits */
	अगर ((efer ^ old_efer) & EFER_NX)
		kvm_mmu_reset_context(vcpu);

	वापस 0;
पूर्ण

व्योम kvm_enable_efer_bits(u64 mask)
अणु
       efer_reserved_bits &= ~mask;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_enable_efer_bits);

bool kvm_msr_allowed(काष्ठा kvm_vcpu *vcpu, u32 index, u32 type)
अणु
	काष्ठा kvm_x86_msr_filter *msr_filter;
	काष्ठा msr_biपंचांगap_range *ranges;
	काष्ठा kvm *kvm = vcpu->kvm;
	bool allowed;
	पूर्णांक idx;
	u32 i;

	/* x2APIC MSRs करो not support filtering. */
	अगर (index >= 0x800 && index <= 0x8ff)
		वापस true;

	idx = srcu_पढ़ो_lock(&kvm->srcu);

	msr_filter = srcu_dereference(kvm->arch.msr_filter, &kvm->srcu);
	अगर (!msr_filter) अणु
		allowed = true;
		जाओ out;
	पूर्ण

	allowed = msr_filter->शेष_allow;
	ranges = msr_filter->ranges;

	क्रम (i = 0; i < msr_filter->count; i++) अणु
		u32 start = ranges[i].base;
		u32 end = start + ranges[i].nmsrs;
		u32 flags = ranges[i].flags;
		अचिन्हित दीर्घ *biपंचांगap = ranges[i].biपंचांगap;

		अगर ((index >= start) && (index < end) && (flags & type)) अणु
			allowed = !!test_bit(index - start, biपंचांगap);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	srcu_पढ़ो_unlock(&kvm->srcu, idx);

	वापस allowed;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_msr_allowed);

/*
 * Write @data पूर्णांकo the MSR specअगरied by @index.  Select MSR specअगरic fault
 * checks are bypassed अगर @host_initiated is %true.
 * Returns 0 on success, non-0 otherwise.
 * Assumes vcpu_load() was alपढ़ोy called.
 */
अटल पूर्णांक __kvm_set_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 data,
			 bool host_initiated)
अणु
	काष्ठा msr_data msr;

	अगर (!host_initiated && !kvm_msr_allowed(vcpu, index, KVM_MSR_FILTER_WRITE))
		वापस KVM_MSR_RET_FILTERED;

	चयन (index) अणु
	हाल MSR_FS_BASE:
	हाल MSR_GS_BASE:
	हाल MSR_KERNEL_GS_BASE:
	हाल MSR_CSTAR:
	हाल MSR_LSTAR:
		अगर (is_noncanonical_address(data, vcpu))
			वापस 1;
		अवरोध;
	हाल MSR_IA32_SYSENTER_EIP:
	हाल MSR_IA32_SYSENTER_ESP:
		/*
		 * IA32_SYSENTER_ESP and IA32_SYSENTER_EIP cause #GP अगर
		 * non-canonical address is written on Intel but not on
		 * AMD (which ignores the top 32-bits, because it करोes
		 * not implement 64-bit SYSENTER).
		 *
		 * 64-bit code should hence be able to ग_लिखो a non-canonical
		 * value on AMD.  Making the address canonical ensures that
		 * vmentry करोes not fail on Intel after writing a non-canonical
		 * value, and that something deterministic happens अगर the guest
		 * invokes 64-bit SYSENTER.
		 */
		data = get_canonical(data, vcpu_virt_addr_bits(vcpu));
		अवरोध;
	हाल MSR_TSC_AUX:
		अगर (!kvm_is_supported_user_वापस_msr(MSR_TSC_AUX))
			वापस 1;

		अगर (!host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_RDTSCP) &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_RDPID))
			वापस 1;

		/*
		 * Per Intel's SDM, bits 63:32 are reserved, but AMD's APM has
		 * incomplete and conflicting architectural behavior.  Current
		 * AMD CPUs completely ignore bits 63:32, i.e. they aren't
		 * reserved and always पढ़ो as zeros.  Enक्रमce Intel's reserved
		 * bits check अगर and only अगर the guest CPU is Intel, and clear
		 * the bits in all other हालs.  This ensures cross-venकरोr
		 * migration will provide consistent behavior क्रम the guest.
		 */
		अगर (guest_cpuid_is_पूर्णांकel(vcpu) && (data >> 32) != 0)
			वापस 1;

		data = (u32)data;
		अवरोध;
	पूर्ण

	msr.data = data;
	msr.index = index;
	msr.host_initiated = host_initiated;

	वापस अटल_call(kvm_x86_set_msr)(vcpu, &msr);
पूर्ण

अटल पूर्णांक kvm_set_msr_ignored_check(काष्ठा kvm_vcpu *vcpu,
				     u32 index, u64 data, bool host_initiated)
अणु
	पूर्णांक ret = __kvm_set_msr(vcpu, index, data, host_initiated);

	अगर (ret == KVM_MSR_RET_INVALID)
		अगर (kvm_msr_ignored_check(index, data, true))
			ret = 0;

	वापस ret;
पूर्ण

/*
 * Read the MSR specअगरied by @index पूर्णांकo @data.  Select MSR specअगरic fault
 * checks are bypassed अगर @host_initiated is %true.
 * Returns 0 on success, non-0 otherwise.
 * Assumes vcpu_load() was alपढ़ोy called.
 */
पूर्णांक __kvm_get_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 *data,
		  bool host_initiated)
अणु
	काष्ठा msr_data msr;
	पूर्णांक ret;

	अगर (!host_initiated && !kvm_msr_allowed(vcpu, index, KVM_MSR_FILTER_READ))
		वापस KVM_MSR_RET_FILTERED;

	चयन (index) अणु
	हाल MSR_TSC_AUX:
		अगर (!kvm_is_supported_user_वापस_msr(MSR_TSC_AUX))
			वापस 1;

		अगर (!host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_RDTSCP) &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_RDPID))
			वापस 1;
		अवरोध;
	पूर्ण

	msr.index = index;
	msr.host_initiated = host_initiated;

	ret = अटल_call(kvm_x86_get_msr)(vcpu, &msr);
	अगर (!ret)
		*data = msr.data;
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_get_msr_ignored_check(काष्ठा kvm_vcpu *vcpu,
				     u32 index, u64 *data, bool host_initiated)
अणु
	पूर्णांक ret = __kvm_get_msr(vcpu, index, data, host_initiated);

	अगर (ret == KVM_MSR_RET_INVALID) अणु
		/* Unconditionally clear *data क्रम simplicity */
		*data = 0;
		अगर (kvm_msr_ignored_check(index, 0, false))
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक kvm_get_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 *data)
अणु
	वापस kvm_get_msr_ignored_check(vcpu, index, data, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_msr);

पूर्णांक kvm_set_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 data)
अणु
	वापस kvm_set_msr_ignored_check(vcpu, index, data, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_msr);

अटल पूर्णांक complete_emulated_rdmsr(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err = vcpu->run->msr.error;
	अगर (!err) अणु
		kvm_rax_ग_लिखो(vcpu, (u32)vcpu->run->msr.data);
		kvm_rdx_ग_लिखो(vcpu, vcpu->run->msr.data >> 32);
	पूर्ण

	वापस अटल_call(kvm_x86_complete_emulated_msr)(vcpu, err);
पूर्ण

अटल पूर्णांक complete_emulated_wrmsr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस अटल_call(kvm_x86_complete_emulated_msr)(vcpu, vcpu->run->msr.error);
पूर्ण

अटल u64 kvm_msr_reason(पूर्णांक r)
अणु
	चयन (r) अणु
	हाल KVM_MSR_RET_INVALID:
		वापस KVM_MSR_EXIT_REASON_UNKNOWN;
	हाल KVM_MSR_RET_FILTERED:
		वापस KVM_MSR_EXIT_REASON_FILTER;
	शेष:
		वापस KVM_MSR_EXIT_REASON_INVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kvm_msr_user_space(काष्ठा kvm_vcpu *vcpu, u32 index,
			      u32 निकास_reason, u64 data,
			      पूर्णांक (*completion)(काष्ठा kvm_vcpu *vcpu),
			      पूर्णांक r)
अणु
	u64 msr_reason = kvm_msr_reason(r);

	/* Check अगर the user wanted to know about this MSR fault */
	अगर (!(vcpu->kvm->arch.user_space_msr_mask & msr_reason))
		वापस 0;

	vcpu->run->निकास_reason = निकास_reason;
	vcpu->run->msr.error = 0;
	स_रखो(vcpu->run->msr.pad, 0, माप(vcpu->run->msr.pad));
	vcpu->run->msr.reason = msr_reason;
	vcpu->run->msr.index = index;
	vcpu->run->msr.data = data;
	vcpu->arch.complete_userspace_io = completion;

	वापस 1;
पूर्ण

अटल पूर्णांक kvm_get_msr_user_space(काष्ठा kvm_vcpu *vcpu, u32 index, पूर्णांक r)
अणु
	वापस kvm_msr_user_space(vcpu, index, KVM_EXIT_X86_RDMSR, 0,
				   complete_emulated_rdmsr, r);
पूर्ण

अटल पूर्णांक kvm_set_msr_user_space(काष्ठा kvm_vcpu *vcpu, u32 index, u64 data, पूर्णांक r)
अणु
	वापस kvm_msr_user_space(vcpu, index, KVM_EXIT_X86_WRMSR, data,
				   complete_emulated_wrmsr, r);
पूर्ण

पूर्णांक kvm_emulate_rdmsr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 ecx = kvm_rcx_पढ़ो(vcpu);
	u64 data;
	पूर्णांक r;

	r = kvm_get_msr(vcpu, ecx, &data);

	/* MSR पढ़ो failed? See अगर we should ask user space */
	अगर (r && kvm_get_msr_user_space(vcpu, ecx, r)) अणु
		/* Bounce to user space */
		वापस 0;
	पूर्ण

	अगर (!r) अणु
		trace_kvm_msr_पढ़ो(ecx, data);

		kvm_rax_ग_लिखो(vcpu, data & -1u);
		kvm_rdx_ग_लिखो(vcpu, (data >> 32) & -1u);
	पूर्ण अन्यथा अणु
		trace_kvm_msr_पढ़ो_ex(ecx);
	पूर्ण

	वापस अटल_call(kvm_x86_complete_emulated_msr)(vcpu, r);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_rdmsr);

पूर्णांक kvm_emulate_wrmsr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 ecx = kvm_rcx_पढ़ो(vcpu);
	u64 data = kvm_पढ़ो_edx_eax(vcpu);
	पूर्णांक r;

	r = kvm_set_msr(vcpu, ecx, data);

	/* MSR ग_लिखो failed? See अगर we should ask user space */
	अगर (r && kvm_set_msr_user_space(vcpu, ecx, data, r))
		/* Bounce to user space */
		वापस 0;

	/* Signal all other negative errors to userspace */
	अगर (r < 0)
		वापस r;

	अगर (!r)
		trace_kvm_msr_ग_लिखो(ecx, data);
	अन्यथा
		trace_kvm_msr_ग_लिखो_ex(ecx, data);

	वापस अटल_call(kvm_x86_complete_emulated_msr)(vcpu, r);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_wrmsr);

पूर्णांक kvm_emulate_as_nop(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_as_nop);

पूर्णांक kvm_emulate_invd(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Treat an INVD inकाष्ठाion as a NOP and just skip it. */
	वापस kvm_emulate_as_nop(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_invd);

पूर्णांक kvm_emulate_mरुको(काष्ठा kvm_vcpu *vcpu)
अणु
	pr_warn_once("kvm: MWAIT instruction emulated as NOP!\n");
	वापस kvm_emulate_as_nop(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_mरुको);

पूर्णांक kvm_handle_invalid_op(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_queue_exception(vcpu, UD_VECTOR);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_handle_invalid_op);

पूर्णांक kvm_emulate_monitor(काष्ठा kvm_vcpu *vcpu)
अणु
	pr_warn_once("kvm: MONITOR instruction emulated as NOP!\n");
	वापस kvm_emulate_as_nop(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_monitor);

अटल अंतरभूत bool kvm_vcpu_निकास_request(काष्ठा kvm_vcpu *vcpu)
अणु
	xfer_to_guest_mode_prepare();
	वापस vcpu->mode == EXITING_GUEST_MODE || kvm_request_pending(vcpu) ||
		xfer_to_guest_mode_work_pending();
पूर्ण

/*
 * The fast path क्रम frequent and perक्रमmance sensitive wrmsr emulation,
 * i.e. the sending of IPI, sending IPI early in the VM-Exit flow reduces
 * the latency of भव IPI by aव्योमing the expensive bits of transitioning
 * from guest to host, e.g. reacquiring KVM's SRCU lock. In contrast to the
 * other हालs which must be called after पूर्णांकerrupts are enabled on the host.
 */
अटल पूर्णांक handle_fastpath_set_x2apic_icr_irqoff(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	अगर (!lapic_in_kernel(vcpu) || !apic_x2apic_mode(vcpu->arch.apic))
		वापस 1;

	अगर (((data & APIC_SHORT_MASK) == APIC_DEST_NOSHORT) &&
		((data & APIC_DEST_MASK) == APIC_DEST_PHYSICAL) &&
		((data & APIC_MODE_MASK) == APIC_DM_FIXED) &&
		((u32)(data >> 32) != X2APIC_BROADCAST)) अणु

		data &= ~(1 << 12);
		kvm_apic_send_ipi(vcpu->arch.apic, (u32)data, (u32)(data >> 32));
		kvm_lapic_set_reg(vcpu->arch.apic, APIC_ICR2, (u32)(data >> 32));
		kvm_lapic_set_reg(vcpu->arch.apic, APIC_ICR, (u32)data);
		trace_kvm_apic_ग_लिखो(APIC_ICR, (u32)data);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक handle_fastpath_set_tscdeadline(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	अगर (!kvm_can_use_hv_समयr(vcpu))
		वापस 1;

	kvm_set_lapic_tscdeadline_msr(vcpu, data);
	वापस 0;
पूर्ण

fastpath_t handle_fastpath_set_msr_irqoff(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 msr = kvm_rcx_पढ़ो(vcpu);
	u64 data;
	fastpath_t ret = EXIT_FASTPATH_NONE;

	चयन (msr) अणु
	हाल APIC_BASE_MSR + (APIC_ICR >> 4):
		data = kvm_पढ़ो_edx_eax(vcpu);
		अगर (!handle_fastpath_set_x2apic_icr_irqoff(vcpu, data)) अणु
			kvm_skip_emulated_inकाष्ठाion(vcpu);
			ret = EXIT_FASTPATH_EXIT_HANDLED;
		पूर्ण
		अवरोध;
	हाल MSR_IA32_TSC_DEADLINE:
		data = kvm_पढ़ो_edx_eax(vcpu);
		अगर (!handle_fastpath_set_tscdeadline(vcpu, data)) अणु
			kvm_skip_emulated_inकाष्ठाion(vcpu);
			ret = EXIT_FASTPATH_REENTER_GUEST;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret != EXIT_FASTPATH_NONE)
		trace_kvm_msr_ग_लिखो(msr, data);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(handle_fastpath_set_msr_irqoff);

/*
 * Adapt set_msr() to msr_io()'s calling convention
 */
अटल पूर्णांक करो_get_msr(काष्ठा kvm_vcpu *vcpu, अचिन्हित index, u64 *data)
अणु
	वापस kvm_get_msr_ignored_check(vcpu, index, data, true);
पूर्ण

अटल पूर्णांक करो_set_msr(काष्ठा kvm_vcpu *vcpu, अचिन्हित index, u64 *data)
अणु
	वापस kvm_set_msr_ignored_check(vcpu, index, *data, true);
पूर्ण

#अगर_घोषित CONFIG_X86_64
काष्ठा pvघड़ी_घड़ी अणु
	पूर्णांक vघड़ी_mode;
	u64 cycle_last;
	u64 mask;
	u32 mult;
	u32 shअगरt;
	u64 base_cycles;
	u64 offset;
पूर्ण;

काष्ठा pvघड़ी_gtod_data अणु
	seqcount_t	seq;

	काष्ठा pvघड़ी_घड़ी घड़ी; /* extract of a घड़ीsource काष्ठा */
	काष्ठा pvघड़ी_घड़ी raw_घड़ी; /* extract of a घड़ीsource काष्ठा */

	kसमय_प्रकार		offs_boot;
	u64		wall_समय_sec;
पूर्ण;

अटल काष्ठा pvघड़ी_gtod_data pvघड़ी_gtod_data;

अटल व्योम update_pvघड़ी_gtod(काष्ठा समयkeeper *tk)
अणु
	काष्ठा pvघड़ी_gtod_data *vdata = &pvघड़ी_gtod_data;

	ग_लिखो_seqcount_begin(&vdata->seq);

	/* copy pvघड़ी gtod data */
	vdata->घड़ी.vघड़ी_mode	= tk->tkr_mono.घड़ी->vdso_घड़ी_mode;
	vdata->घड़ी.cycle_last		= tk->tkr_mono.cycle_last;
	vdata->घड़ी.mask		= tk->tkr_mono.mask;
	vdata->घड़ी.mult		= tk->tkr_mono.mult;
	vdata->घड़ी.shअगरt		= tk->tkr_mono.shअगरt;
	vdata->घड़ी.base_cycles	= tk->tkr_mono.xसमय_nsec;
	vdata->घड़ी.offset		= tk->tkr_mono.base;

	vdata->raw_घड़ी.vघड़ी_mode	= tk->tkr_raw.घड़ी->vdso_घड़ी_mode;
	vdata->raw_घड़ी.cycle_last	= tk->tkr_raw.cycle_last;
	vdata->raw_घड़ी.mask		= tk->tkr_raw.mask;
	vdata->raw_घड़ी.mult		= tk->tkr_raw.mult;
	vdata->raw_घड़ी.shअगरt		= tk->tkr_raw.shअगरt;
	vdata->raw_घड़ी.base_cycles	= tk->tkr_raw.xसमय_nsec;
	vdata->raw_घड़ी.offset		= tk->tkr_raw.base;

	vdata->wall_समय_sec            = tk->xसमय_sec;

	vdata->offs_boot		= tk->offs_boot;

	ग_लिखो_seqcount_end(&vdata->seq);
पूर्ण

अटल s64 get_kvmघड़ी_base_ns(व्योम)
अणु
	/* Count up from boot समय, but with the frequency of the raw घड़ी.  */
	वापस kसमय_प्रकारo_ns(kसमय_add(kसमय_get_raw(), pvघड़ी_gtod_data.offs_boot));
पूर्ण
#अन्यथा
अटल s64 get_kvmघड़ी_base_ns(व्योम)
अणु
	/* Master घड़ी not used, so we can just use CLOCK_BOOTTIME.  */
	वापस kसमय_get_bootसमय_ns();
पूर्ण
#पूर्ण_अगर

व्योम kvm_ग_लिखो_wall_घड़ी(काष्ठा kvm *kvm, gpa_t wall_घड़ी, पूर्णांक sec_hi_ofs)
अणु
	पूर्णांक version;
	पूर्णांक r;
	काष्ठा pvघड़ी_wall_घड़ी wc;
	u32 wc_sec_hi;
	u64 wall_nsec;

	अगर (!wall_घड़ी)
		वापस;

	r = kvm_पढ़ो_guest(kvm, wall_घड़ी, &version, माप(version));
	अगर (r)
		वापस;

	अगर (version & 1)
		++version;  /* first समय ग_लिखो, अक्रमom junk */

	++version;

	अगर (kvm_ग_लिखो_guest(kvm, wall_घड़ी, &version, माप(version)))
		वापस;

	/*
	 * The guest calculates current wall घड़ी समय by adding
	 * प्रणाली समय (updated by kvm_guest_समय_update below) to the
	 * wall घड़ी specअगरied here.  We करो the reverse here.
	 */
	wall_nsec = kसमय_get_real_ns() - get_kvmघड़ी_ns(kvm);

	wc.nsec = करो_भाग(wall_nsec, 1000000000);
	wc.sec = (u32)wall_nsec; /* overflow in 2106 guest समय */
	wc.version = version;

	kvm_ग_लिखो_guest(kvm, wall_घड़ी, &wc, माप(wc));

	अगर (sec_hi_ofs) अणु
		wc_sec_hi = wall_nsec >> 32;
		kvm_ग_लिखो_guest(kvm, wall_घड़ी + sec_hi_ofs,
				&wc_sec_hi, माप(wc_sec_hi));
	पूर्ण

	version++;
	kvm_ग_लिखो_guest(kvm, wall_घड़ी, &version, माप(version));
पूर्ण

अटल व्योम kvm_ग_लिखो_प्रणाली_समय(काष्ठा kvm_vcpu *vcpu, gpa_t प्रणाली_समय,
				  bool old_msr, bool host_initiated)
अणु
	काष्ठा kvm_arch *ka = &vcpu->kvm->arch;

	अगर (vcpu->vcpu_id == 0 && !host_initiated) अणु
		अगर (ka->boot_vcpu_runs_old_kvmघड़ी != old_msr)
			kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);

		ka->boot_vcpu_runs_old_kvmघड़ी = old_msr;
	पूर्ण

	vcpu->arch.समय = प्रणाली_समय;
	kvm_make_request(KVM_REQ_GLOBAL_CLOCK_UPDATE, vcpu);

	/* we verअगरy अगर the enable bit is set... */
	vcpu->arch.pv_समय_enabled = false;
	अगर (!(प्रणाली_समय & 1))
		वापस;

	अगर (!kvm_gfn_to_hva_cache_init(vcpu->kvm,
				       &vcpu->arch.pv_समय, प्रणाली_समय & ~1ULL,
				       माप(काष्ठा pvघड़ी_vcpu_समय_info)))
		vcpu->arch.pv_समय_enabled = true;

	वापस;
पूर्ण

अटल uपूर्णांक32_t भाग_frac(uपूर्णांक32_t भागidend, uपूर्णांक32_t भागisor)
अणु
	करो_shl32_भाग32(भागidend, भागisor);
	वापस भागidend;
पूर्ण

अटल व्योम kvm_get_समय_scale(uपूर्णांक64_t scaled_hz, uपूर्णांक64_t base_hz,
			       s8 *pshअगरt, u32 *pmultiplier)
अणु
	uपूर्णांक64_t scaled64;
	पूर्णांक32_t  shअगरt = 0;
	uपूर्णांक64_t tps64;
	uपूर्णांक32_t tps32;

	tps64 = base_hz;
	scaled64 = scaled_hz;
	जबतक (tps64 > scaled64*2 || tps64 & 0xffffffff00000000ULL) अणु
		tps64 >>= 1;
		shअगरt--;
	पूर्ण

	tps32 = (uपूर्णांक32_t)tps64;
	जबतक (tps32 <= scaled64 || scaled64 & 0xffffffff00000000ULL) अणु
		अगर (scaled64 & 0xffffffff00000000ULL || tps32 & 0x80000000)
			scaled64 >>= 1;
		अन्यथा
			tps32 <<= 1;
		shअगरt++;
	पूर्ण

	*pshअगरt = shअगरt;
	*pmultiplier = भाग_frac(scaled64, tps32);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल atomic_t kvm_guest_has_master_घड़ी = ATOMIC_INIT(0);
#पूर्ण_अगर

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_tsc_khz);
अटल अचिन्हित दीर्घ max_tsc_khz;

अटल u32 adjust_tsc_khz(u32 khz, s32 ppm)
अणु
	u64 v = (u64)khz * (1000000 + ppm);
	करो_भाग(v, 1000000);
	वापस v;
पूर्ण

अटल पूर्णांक set_tsc_khz(काष्ठा kvm_vcpu *vcpu, u32 user_tsc_khz, bool scale)
अणु
	u64 ratio;

	/* Guest TSC same frequency as host TSC? */
	अगर (!scale) अणु
		vcpu->arch.tsc_scaling_ratio = kvm_शेष_tsc_scaling_ratio;
		वापस 0;
	पूर्ण

	/* TSC scaling supported? */
	अगर (!kvm_has_tsc_control) अणु
		अगर (user_tsc_khz > tsc_khz) अणु
			vcpu->arch.tsc_catchup = 1;
			vcpu->arch.tsc_always_catchup = 1;
			वापस 0;
		पूर्ण अन्यथा अणु
			pr_warn_ratelimited("user requested TSC rate below hardware speed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* TSC scaling required  - calculate ratio */
	ratio = mul_u64_u32_भाग(1ULL << kvm_tsc_scaling_ratio_frac_bits,
				user_tsc_khz, tsc_khz);

	अगर (ratio == 0 || ratio >= kvm_max_tsc_scaling_ratio) अणु
		pr_warn_ratelimited("Invalid TSC scaling ratio - virtual-tsc-khz=%u\n",
			            user_tsc_khz);
		वापस -1;
	पूर्ण

	vcpu->arch.tsc_scaling_ratio = ratio;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_set_tsc_khz(काष्ठा kvm_vcpu *vcpu, u32 user_tsc_khz)
अणु
	u32 thresh_lo, thresh_hi;
	पूर्णांक use_scaling = 0;

	/* tsc_khz can be zero अगर TSC calibration fails */
	अगर (user_tsc_khz == 0) अणु
		/* set tsc_scaling_ratio to a safe value */
		vcpu->arch.tsc_scaling_ratio = kvm_शेष_tsc_scaling_ratio;
		वापस -1;
	पूर्ण

	/* Compute a scale to convert nanoseconds in TSC cycles */
	kvm_get_समय_scale(user_tsc_khz * 1000LL, NSEC_PER_SEC,
			   &vcpu->arch.भव_tsc_shअगरt,
			   &vcpu->arch.भव_tsc_mult);
	vcpu->arch.भव_tsc_khz = user_tsc_khz;

	/*
	 * Compute the variation in TSC rate which is acceptable
	 * within the range of tolerance and decide अगर the
	 * rate being applied is within that bounds of the hardware
	 * rate.  If so, no scaling or compensation need be करोne.
	 */
	thresh_lo = adjust_tsc_khz(tsc_khz, -tsc_tolerance_ppm);
	thresh_hi = adjust_tsc_khz(tsc_khz, tsc_tolerance_ppm);
	अगर (user_tsc_khz < thresh_lo || user_tsc_khz > thresh_hi) अणु
		pr_debug("kvm: requested TSC rate %u falls outside tolerance [%u,%u]\n", user_tsc_khz, thresh_lo, thresh_hi);
		use_scaling = 1;
	पूर्ण
	वापस set_tsc_khz(vcpu, user_tsc_khz, use_scaling);
पूर्ण

अटल u64 compute_guest_tsc(काष्ठा kvm_vcpu *vcpu, s64 kernel_ns)
अणु
	u64 tsc = pvघड़ी_scale_delta(kernel_ns-vcpu->arch.this_tsc_nsec,
				      vcpu->arch.भव_tsc_mult,
				      vcpu->arch.भव_tsc_shअगरt);
	tsc += vcpu->arch.this_tsc_ग_लिखो;
	वापस tsc;
पूर्ण

अटल अंतरभूत पूर्णांक gtod_is_based_on_tsc(पूर्णांक mode)
अणु
	वापस mode == VDSO_CLOCKMODE_TSC || mode == VDSO_CLOCKMODE_HVCLOCK;
पूर्ण

अटल व्योम kvm_track_tsc_matching(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_X86_64
	bool vcpus_matched;
	काष्ठा kvm_arch *ka = &vcpu->kvm->arch;
	काष्ठा pvघड़ी_gtod_data *gtod = &pvघड़ी_gtod_data;

	vcpus_matched = (ka->nr_vcpus_matched_tsc + 1 ==
			 atomic_पढ़ो(&vcpu->kvm->online_vcpus));

	/*
	 * Once the masterघड़ी is enabled, always perक्रमm request in
	 * order to update it.
	 *
	 * In order to enable masterघड़ी, the host घड़ीsource must be TSC
	 * and the vcpus need to have matched TSCs.  When that happens,
	 * perक्रमm request to enable masterघड़ी.
	 */
	अगर (ka->use_master_घड़ी ||
	    (gtod_is_based_on_tsc(gtod->घड़ी.vघड़ी_mode) && vcpus_matched))
		kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);

	trace_kvm_track_tsc(vcpu->vcpu_id, ka->nr_vcpus_matched_tsc,
			    atomic_पढ़ो(&vcpu->kvm->online_vcpus),
		            ka->use_master_घड़ी, gtod->घड़ी.vघड़ी_mode);
#पूर्ण_अगर
पूर्ण

/*
 * Multiply tsc by a fixed poपूर्णांक number represented by ratio.
 *
 * The most signअगरicant 64-N bits (mult) of ratio represent the
 * पूर्णांकegral part of the fixed poपूर्णांक number; the reमुख्यing N bits
 * (frac) represent the fractional part, ie. ratio represents a fixed
 * poपूर्णांक number (mult + frac * 2^(-N)).
 *
 * N equals to kvm_tsc_scaling_ratio_frac_bits.
 */
अटल अंतरभूत u64 __scale_tsc(u64 ratio, u64 tsc)
अणु
	वापस mul_u64_u64_shr(tsc, ratio, kvm_tsc_scaling_ratio_frac_bits);
पूर्ण

u64 kvm_scale_tsc(काष्ठा kvm_vcpu *vcpu, u64 tsc)
अणु
	u64 _tsc = tsc;
	u64 ratio = vcpu->arch.tsc_scaling_ratio;

	अगर (ratio != kvm_शेष_tsc_scaling_ratio)
		_tsc = __scale_tsc(ratio, tsc);

	वापस _tsc;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_scale_tsc);

अटल u64 kvm_compute_tsc_offset(काष्ठा kvm_vcpu *vcpu, u64 target_tsc)
अणु
	u64 tsc;

	tsc = kvm_scale_tsc(vcpu, rdtsc());

	वापस target_tsc - tsc;
पूर्ण

u64 kvm_पढ़ो_l1_tsc(काष्ठा kvm_vcpu *vcpu, u64 host_tsc)
अणु
	वापस vcpu->arch.l1_tsc_offset + kvm_scale_tsc(vcpu, host_tsc);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_l1_tsc);

अटल व्योम kvm_vcpu_ग_लिखो_tsc_offset(काष्ठा kvm_vcpu *vcpu, u64 offset)
अणु
	vcpu->arch.l1_tsc_offset = offset;
	vcpu->arch.tsc_offset = अटल_call(kvm_x86_ग_लिखो_l1_tsc_offset)(vcpu, offset);
पूर्ण

अटल अंतरभूत bool kvm_check_tsc_unstable(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	/*
	 * TSC is marked unstable when we're running on Hyper-V,
	 * 'TSC page' घड़ीsource is good.
	 */
	अगर (pvघड़ी_gtod_data.घड़ी.vघड़ी_mode == VDSO_CLOCKMODE_HVCLOCK)
		वापस false;
#पूर्ण_अगर
	वापस check_tsc_unstable();
पूर्ण

अटल व्योम kvm_synchronize_tsc(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u64 offset, ns, elapsed;
	अचिन्हित दीर्घ flags;
	bool matched;
	bool alपढ़ोy_matched;
	bool synchronizing = false;

	raw_spin_lock_irqsave(&kvm->arch.tsc_ग_लिखो_lock, flags);
	offset = kvm_compute_tsc_offset(vcpu, data);
	ns = get_kvmघड़ी_base_ns();
	elapsed = ns - kvm->arch.last_tsc_nsec;

	अगर (vcpu->arch.भव_tsc_khz) अणु
		अगर (data == 0) अणु
			/*
			 * detection of vcpu initialization -- need to sync
			 * with other vCPUs. This particularly helps to keep
			 * kvm_घड़ी stable after CPU hotplug
			 */
			synchronizing = true;
		पूर्ण अन्यथा अणु
			u64 tsc_exp = kvm->arch.last_tsc_ग_लिखो +
						nsec_to_cycles(vcpu, elapsed);
			u64 tsc_hz = vcpu->arch.भव_tsc_khz * 1000LL;
			/*
			 * Special हाल: TSC ग_लिखो with a small delta (1 second)
			 * of भव cycle समय against real समय is
			 * पूर्णांकerpreted as an attempt to synchronize the CPU.
			 */
			synchronizing = data < tsc_exp + tsc_hz &&
					data + tsc_hz > tsc_exp;
		पूर्ण
	पूर्ण

	/*
	 * For a reliable TSC, we can match TSC offsets, and क्रम an unstable
	 * TSC, we add elapsed समय in this computation.  We could let the
	 * compensation code attempt to catch up अगर we fall behind, but
	 * it's better to try to match offsets from the beginning.
         */
	अगर (synchronizing &&
	    vcpu->arch.भव_tsc_khz == kvm->arch.last_tsc_khz) अणु
		अगर (!kvm_check_tsc_unstable()) अणु
			offset = kvm->arch.cur_tsc_offset;
		पूर्ण अन्यथा अणु
			u64 delta = nsec_to_cycles(vcpu, elapsed);
			data += delta;
			offset = kvm_compute_tsc_offset(vcpu, data);
		पूर्ण
		matched = true;
		alपढ़ोy_matched = (vcpu->arch.this_tsc_generation == kvm->arch.cur_tsc_generation);
	पूर्ण अन्यथा अणु
		/*
		 * We split periods of matched TSC ग_लिखोs पूर्णांकo generations.
		 * For each generation, we track the original measured
		 * nanosecond समय, offset, and ग_लिखो, so अगर TSCs are in
		 * sync, we can match exact offset, and अगर not, we can match
		 * exact software computation in compute_guest_tsc()
		 *
		 * These values are tracked in kvm->arch.cur_xxx variables.
		 */
		kvm->arch.cur_tsc_generation++;
		kvm->arch.cur_tsc_nsec = ns;
		kvm->arch.cur_tsc_ग_लिखो = data;
		kvm->arch.cur_tsc_offset = offset;
		matched = false;
	पूर्ण

	/*
	 * We also track th most recent recorded KHZ, ग_लिखो and समय to
	 * allow the matching पूर्णांकerval to be extended at each ग_लिखो.
	 */
	kvm->arch.last_tsc_nsec = ns;
	kvm->arch.last_tsc_ग_लिखो = data;
	kvm->arch.last_tsc_khz = vcpu->arch.भव_tsc_khz;

	vcpu->arch.last_guest_tsc = data;

	/* Keep track of which generation this VCPU has synchronized to */
	vcpu->arch.this_tsc_generation = kvm->arch.cur_tsc_generation;
	vcpu->arch.this_tsc_nsec = kvm->arch.cur_tsc_nsec;
	vcpu->arch.this_tsc_ग_लिखो = kvm->arch.cur_tsc_ग_लिखो;

	kvm_vcpu_ग_लिखो_tsc_offset(vcpu, offset);
	raw_spin_unlock_irqrestore(&kvm->arch.tsc_ग_लिखो_lock, flags);

	spin_lock_irqsave(&kvm->arch.pvघड़ी_gtod_sync_lock, flags);
	अगर (!matched) अणु
		kvm->arch.nr_vcpus_matched_tsc = 0;
	पूर्ण अन्यथा अगर (!alपढ़ोy_matched) अणु
		kvm->arch.nr_vcpus_matched_tsc++;
	पूर्ण

	kvm_track_tsc_matching(vcpu);
	spin_unlock_irqrestore(&kvm->arch.pvघड़ी_gtod_sync_lock, flags);
पूर्ण

अटल अंतरभूत व्योम adjust_tsc_offset_guest(काष्ठा kvm_vcpu *vcpu,
					   s64 adjusपंचांगent)
अणु
	u64 tsc_offset = vcpu->arch.l1_tsc_offset;
	kvm_vcpu_ग_लिखो_tsc_offset(vcpu, tsc_offset + adjusपंचांगent);
पूर्ण

अटल अंतरभूत व्योम adjust_tsc_offset_host(काष्ठा kvm_vcpu *vcpu, s64 adjusपंचांगent)
अणु
	अगर (vcpu->arch.tsc_scaling_ratio != kvm_शेष_tsc_scaling_ratio)
		WARN_ON(adjusपंचांगent < 0);
	adjusपंचांगent = kvm_scale_tsc(vcpu, (u64) adjusपंचांगent);
	adjust_tsc_offset_guest(vcpu, adjusपंचांगent);
पूर्ण

#अगर_घोषित CONFIG_X86_64

अटल u64 पढ़ो_tsc(व्योम)
अणु
	u64 ret = (u64)rdtsc_ordered();
	u64 last = pvघड़ी_gtod_data.घड़ी.cycle_last;

	अगर (likely(ret >= last))
		वापस ret;

	/*
	 * GCC likes to generate cmov here, but this branch is extremely
	 * predictable (it's just a function of समय and the likely is
	 * very likely) and there's a data dependence, so क्रमce GCC
	 * to generate a branch instead.  I करोn't barrier() because
	 * we करोn't actually need a barrier, and अगर this function
	 * ever माला_लो अंतरभूतd it will generate worse code.
	 */
	यंत्र अस्थिर ("");
	वापस last;
पूर्ण

अटल अंतरभूत u64 vgettsc(काष्ठा pvघड़ी_घड़ी *घड़ी, u64 *tsc_बारtamp,
			  पूर्णांक *mode)
अणु
	दीर्घ v;
	u64 tsc_pg_val;

	चयन (घड़ी->vघड़ी_mode) अणु
	हाल VDSO_CLOCKMODE_HVCLOCK:
		tsc_pg_val = hv_पढ़ो_tsc_page_tsc(hv_get_tsc_page(),
						  tsc_बारtamp);
		अगर (tsc_pg_val != U64_MAX) अणु
			/* TSC page valid */
			*mode = VDSO_CLOCKMODE_HVCLOCK;
			v = (tsc_pg_val - घड़ी->cycle_last) &
				घड़ी->mask;
		पूर्ण अन्यथा अणु
			/* TSC page invalid */
			*mode = VDSO_CLOCKMODE_NONE;
		पूर्ण
		अवरोध;
	हाल VDSO_CLOCKMODE_TSC:
		*mode = VDSO_CLOCKMODE_TSC;
		*tsc_बारtamp = पढ़ो_tsc();
		v = (*tsc_बारtamp - घड़ी->cycle_last) &
			घड़ी->mask;
		अवरोध;
	शेष:
		*mode = VDSO_CLOCKMODE_NONE;
	पूर्ण

	अगर (*mode == VDSO_CLOCKMODE_NONE)
		*tsc_बारtamp = v = 0;

	वापस v * घड़ी->mult;
पूर्ण

अटल पूर्णांक करो_monotonic_raw(s64 *t, u64 *tsc_बारtamp)
अणु
	काष्ठा pvघड़ी_gtod_data *gtod = &pvघड़ी_gtod_data;
	अचिन्हित दीर्घ seq;
	पूर्णांक mode;
	u64 ns;

	करो अणु
		seq = पढ़ो_seqcount_begin(&gtod->seq);
		ns = gtod->raw_घड़ी.base_cycles;
		ns += vgettsc(&gtod->raw_घड़ी, tsc_बारtamp, &mode);
		ns >>= gtod->raw_घड़ी.shअगरt;
		ns += kसमय_प्रकारo_ns(kसमय_add(gtod->raw_घड़ी.offset, gtod->offs_boot));
	पूर्ण जबतक (unlikely(पढ़ो_seqcount_retry(&gtod->seq, seq)));
	*t = ns;

	वापस mode;
पूर्ण

अटल पूर्णांक करो_realसमय(काष्ठा बारpec64 *ts, u64 *tsc_बारtamp)
अणु
	काष्ठा pvघड़ी_gtod_data *gtod = &pvघड़ी_gtod_data;
	अचिन्हित दीर्घ seq;
	पूर्णांक mode;
	u64 ns;

	करो अणु
		seq = पढ़ो_seqcount_begin(&gtod->seq);
		ts->tv_sec = gtod->wall_समय_sec;
		ns = gtod->घड़ी.base_cycles;
		ns += vgettsc(&gtod->घड़ी, tsc_बारtamp, &mode);
		ns >>= gtod->घड़ी.shअगरt;
	पूर्ण जबतक (unlikely(पढ़ो_seqcount_retry(&gtod->seq, seq)));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस mode;
पूर्ण

/* वापसs true अगर host is using TSC based घड़ीsource */
अटल bool kvm_get_समय_and_घड़ीपढ़ो(s64 *kernel_ns, u64 *tsc_बारtamp)
अणु
	/* checked again under seqlock below */
	अगर (!gtod_is_based_on_tsc(pvघड़ी_gtod_data.घड़ी.vघड़ी_mode))
		वापस false;

	वापस gtod_is_based_on_tsc(करो_monotonic_raw(kernel_ns,
						      tsc_बारtamp));
पूर्ण

/* वापसs true अगर host is using TSC based घड़ीsource */
अटल bool kvm_get_wallसमय_and_घड़ीपढ़ो(काष्ठा बारpec64 *ts,
					   u64 *tsc_बारtamp)
अणु
	/* checked again under seqlock below */
	अगर (!gtod_is_based_on_tsc(pvघड़ी_gtod_data.घड़ी.vघड़ी_mode))
		वापस false;

	वापस gtod_is_based_on_tsc(करो_realसमय(ts, tsc_बारtamp));
पूर्ण
#पूर्ण_अगर

/*
 *
 * Assuming a stable TSC across physical CPUS, and a stable TSC
 * across भव CPUs, the following condition is possible.
 * Each numbered line represents an event visible to both
 * CPUs at the next numbered event.
 *
 * "timespecX" represents host monotonic समय. "tscX" represents
 * RDTSC value.
 *
 * 		VCPU0 on CPU0		|	VCPU1 on CPU1
 *
 * 1.  पढ़ो बारpec0,tsc0
 * 2.					| बारpec1 = बारpec0 + N
 * 					| tsc1 = tsc0 + M
 * 3. transition to guest		| transition to guest
 * 4. ret0 = बारpec0 + (rdtsc - tsc0) |
 * 5.				        | ret1 = बारpec1 + (rdtsc - tsc1)
 * 				        | ret1 = बारpec0 + N + (rdtsc - (tsc0 + M))
 *
 * Since ret0 update is visible to VCPU1 at समय 5, to obey monotonicity:
 *
 * 	- ret0 < ret1
 *	- बारpec0 + (rdtsc - tsc0) < बारpec0 + N + (rdtsc - (tsc0 + M))
 *		...
 *	- 0 < N - M => M < N
 *
 * That is, when बारpec0 != बारpec1, M < N. Unक्रमtunately that is not
 * always the हाल (the dअगरference between two distinct xसमय instances
 * might be smaller then the dअगरference between corresponding TSC पढ़ोs,
 * when updating guest vcpus pvघड़ी areas).
 *
 * To aव्योम that problem, करो not allow visibility of distinct
 * प्रणाली_बारtamp/tsc_बारtamp values simultaneously: use a master
 * copy of host monotonic समय values. Update that master copy
 * in lockstep.
 *
 * Rely on synchronization of host TSCs and guest TSCs क्रम monotonicity.
 *
 */

अटल व्योम pvघड़ी_update_vm_gtod_copy(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_X86_64
	काष्ठा kvm_arch *ka = &kvm->arch;
	पूर्णांक vघड़ी_mode;
	bool host_tsc_घड़ीsource, vcpus_matched;

	vcpus_matched = (ka->nr_vcpus_matched_tsc + 1 ==
			atomic_पढ़ो(&kvm->online_vcpus));

	/*
	 * If the host uses TSC घड़ी, then passthrough TSC as stable
	 * to the guest.
	 */
	host_tsc_घड़ीsource = kvm_get_समय_and_घड़ीपढ़ो(
					&ka->master_kernel_ns,
					&ka->master_cycle_now);

	ka->use_master_घड़ी = host_tsc_घड़ीsource && vcpus_matched
				&& !ka->backwards_tsc_observed
				&& !ka->boot_vcpu_runs_old_kvmघड़ी;

	अगर (ka->use_master_घड़ी)
		atomic_set(&kvm_guest_has_master_घड़ी, 1);

	vघड़ी_mode = pvघड़ी_gtod_data.घड़ी.vघड़ी_mode;
	trace_kvm_update_master_घड़ी(ka->use_master_घड़ी, vघड़ी_mode,
					vcpus_matched);
#पूर्ण_अगर
पूर्ण

व्योम kvm_make_mघड़ी_inprogress_request(काष्ठा kvm *kvm)
अणु
	kvm_make_all_cpus_request(kvm, KVM_REQ_MCLOCK_INPROGRESS);
पूर्ण

अटल व्योम kvm_gen_update_masterघड़ी(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_X86_64
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvm_arch *ka = &kvm->arch;
	अचिन्हित दीर्घ flags;

	kvm_hv_invalidate_tsc_page(kvm);

	kvm_make_mघड़ी_inprogress_request(kvm);

	/* no guest entries from this poपूर्णांक */
	spin_lock_irqsave(&ka->pvघड़ी_gtod_sync_lock, flags);
	pvघड़ी_update_vm_gtod_copy(kvm);
	spin_unlock_irqrestore(&ka->pvघड़ी_gtod_sync_lock, flags);

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);

	/* guest entries allowed */
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_clear_request(KVM_REQ_MCLOCK_INPROGRESS, vcpu);
#पूर्ण_अगर
पूर्ण

u64 get_kvmघड़ी_ns(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_arch *ka = &kvm->arch;
	काष्ठा pvघड़ी_vcpu_समय_info hv_घड़ी;
	अचिन्हित दीर्घ flags;
	u64 ret;

	spin_lock_irqsave(&ka->pvघड़ी_gtod_sync_lock, flags);
	अगर (!ka->use_master_घड़ी) अणु
		spin_unlock_irqrestore(&ka->pvघड़ी_gtod_sync_lock, flags);
		वापस get_kvmघड़ी_base_ns() + ka->kvmघड़ी_offset;
	पूर्ण

	hv_घड़ी.tsc_बारtamp = ka->master_cycle_now;
	hv_घड़ी.प्रणाली_समय = ka->master_kernel_ns + ka->kvmघड़ी_offset;
	spin_unlock_irqrestore(&ka->pvघड़ी_gtod_sync_lock, flags);

	/* both __this_cpu_पढ़ो() and rdtsc() should be on the same cpu */
	get_cpu();

	अगर (__this_cpu_पढ़ो(cpu_tsc_khz)) अणु
		kvm_get_समय_scale(NSEC_PER_SEC, __this_cpu_पढ़ो(cpu_tsc_khz) * 1000LL,
				   &hv_घड़ी.tsc_shअगरt,
				   &hv_घड़ी.tsc_to_प्रणाली_mul);
		ret = __pvघड़ी_पढ़ो_cycles(&hv_घड़ी, rdtsc());
	पूर्ण अन्यथा
		ret = get_kvmघड़ी_base_ns() + ka->kvmघड़ी_offset;

	put_cpu();

	वापस ret;
पूर्ण

अटल व्योम kvm_setup_pvघड़ी_page(काष्ठा kvm_vcpu *v,
				   काष्ठा gfn_to_hva_cache *cache,
				   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा kvm_vcpu_arch *vcpu = &v->arch;
	काष्ठा pvघड़ी_vcpu_समय_info guest_hv_घड़ी;

	अगर (unlikely(kvm_पढ़ो_guest_offset_cached(v->kvm, cache,
		&guest_hv_घड़ी, offset, माप(guest_hv_घड़ी))))
		वापस;

	/* This VCPU is छोड़ोd, but it's legal क्रम a guest to पढ़ो another
	 * VCPU's kvmघड़ी, so we really have to follow the specअगरication where
	 * it says that version is odd अगर data is being modअगरied, and even after
	 * it is consistent.
	 *
	 * Version field updates must be kept separate.  This is because
	 * kvm_ग_लिखो_guest_cached might use a "rep movs" inकाष्ठाion, and
	 * ग_लिखोs within a string inकाष्ठाion are weakly ordered.  So there
	 * are three ग_लिखोs overall.
	 *
	 * As a small optimization, only ग_लिखो the version field in the first
	 * and third ग_लिखो.  The vcpu->pv_समय cache is still valid, because the
	 * version field is the first in the काष्ठा.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा pvघड़ी_vcpu_समय_info, version) != 0);

	अगर (guest_hv_घड़ी.version & 1)
		++guest_hv_घड़ी.version;  /* first समय ग_लिखो, अक्रमom junk */

	vcpu->hv_घड़ी.version = guest_hv_घड़ी.version + 1;
	kvm_ग_लिखो_guest_offset_cached(v->kvm, cache,
				      &vcpu->hv_घड़ी, offset,
				      माप(vcpu->hv_घड़ी.version));

	smp_wmb();

	/* retain PVCLOCK_GUEST_STOPPED अगर set in guest copy */
	vcpu->hv_घड़ी.flags |= (guest_hv_घड़ी.flags & PVCLOCK_GUEST_STOPPED);

	अगर (vcpu->pvघड़ी_set_guest_stopped_request) अणु
		vcpu->hv_घड़ी.flags |= PVCLOCK_GUEST_STOPPED;
		vcpu->pvघड़ी_set_guest_stopped_request = false;
	पूर्ण

	trace_kvm_pvघड़ी_update(v->vcpu_id, &vcpu->hv_घड़ी);

	kvm_ग_लिखो_guest_offset_cached(v->kvm, cache,
				      &vcpu->hv_घड़ी, offset,
				      माप(vcpu->hv_घड़ी));

	smp_wmb();

	vcpu->hv_घड़ी.version++;
	kvm_ग_लिखो_guest_offset_cached(v->kvm, cache,
				     &vcpu->hv_घड़ी, offset,
				     माप(vcpu->hv_घड़ी.version));
पूर्ण

अटल पूर्णांक kvm_guest_समय_update(काष्ठा kvm_vcpu *v)
अणु
	अचिन्हित दीर्घ flags, tgt_tsc_khz;
	काष्ठा kvm_vcpu_arch *vcpu = &v->arch;
	काष्ठा kvm_arch *ka = &v->kvm->arch;
	s64 kernel_ns;
	u64 tsc_बारtamp, host_tsc;
	u8 pvघड़ी_flags;
	bool use_master_घड़ी;

	kernel_ns = 0;
	host_tsc = 0;

	/*
	 * If the host uses TSC घड़ी, then passthrough TSC as stable
	 * to the guest.
	 */
	spin_lock_irqsave(&ka->pvघड़ी_gtod_sync_lock, flags);
	use_master_घड़ी = ka->use_master_घड़ी;
	अगर (use_master_घड़ी) अणु
		host_tsc = ka->master_cycle_now;
		kernel_ns = ka->master_kernel_ns;
	पूर्ण
	spin_unlock_irqrestore(&ka->pvघड़ी_gtod_sync_lock, flags);

	/* Keep irq disabled to prevent changes to the घड़ी */
	local_irq_save(flags);
	tgt_tsc_khz = __this_cpu_पढ़ो(cpu_tsc_khz);
	अगर (unlikely(tgt_tsc_khz == 0)) अणु
		local_irq_restore(flags);
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, v);
		वापस 1;
	पूर्ण
	अगर (!use_master_घड़ी) अणु
		host_tsc = rdtsc();
		kernel_ns = get_kvmघड़ी_base_ns();
	पूर्ण

	tsc_बारtamp = kvm_पढ़ो_l1_tsc(v, host_tsc);

	/*
	 * We may have to catch up the TSC to match elapsed wall घड़ी
	 * समय क्रम two reasons, even अगर kvmघड़ी is used.
	 *   1) CPU could have been running below the maximum TSC rate
	 *   2) Broken TSC compensation resets the base at each VCPU
	 *      entry to aव्योम unknown leaps of TSC even when running
	 *      again on the same CPU.  This may cause apparent elapsed
	 *      समय to disappear, and the guest to stand still or run
	 *	very slowly.
	 */
	अगर (vcpu->tsc_catchup) अणु
		u64 tsc = compute_guest_tsc(v, kernel_ns);
		अगर (tsc > tsc_बारtamp) अणु
			adjust_tsc_offset_guest(v, tsc - tsc_बारtamp);
			tsc_बारtamp = tsc;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);

	/* With all the info we got, fill in the values */

	अगर (kvm_has_tsc_control)
		tgt_tsc_khz = kvm_scale_tsc(v, tgt_tsc_khz);

	अगर (unlikely(vcpu->hw_tsc_khz != tgt_tsc_khz)) अणु
		kvm_get_समय_scale(NSEC_PER_SEC, tgt_tsc_khz * 1000LL,
				   &vcpu->hv_घड़ी.tsc_shअगरt,
				   &vcpu->hv_घड़ी.tsc_to_प्रणाली_mul);
		vcpu->hw_tsc_khz = tgt_tsc_khz;
	पूर्ण

	vcpu->hv_घड़ी.tsc_बारtamp = tsc_बारtamp;
	vcpu->hv_घड़ी.प्रणाली_समय = kernel_ns + v->kvm->arch.kvmघड़ी_offset;
	vcpu->last_guest_tsc = tsc_बारtamp;

	/* If the host uses TSC घड़ीsource, then it is stable */
	pvघड़ी_flags = 0;
	अगर (use_master_घड़ी)
		pvघड़ी_flags |= PVCLOCK_TSC_STABLE_BIT;

	vcpu->hv_घड़ी.flags = pvघड़ी_flags;

	अगर (vcpu->pv_समय_enabled)
		kvm_setup_pvघड़ी_page(v, &vcpu->pv_समय, 0);
	अगर (vcpu->xen.vcpu_info_set)
		kvm_setup_pvघड़ी_page(v, &vcpu->xen.vcpu_info_cache,
				       दुरत्व(काष्ठा compat_vcpu_info, समय));
	अगर (vcpu->xen.vcpu_समय_info_set)
		kvm_setup_pvघड़ी_page(v, &vcpu->xen.vcpu_समय_info_cache, 0);
	अगर (v == kvm_get_vcpu(v->kvm, 0))
		kvm_hv_setup_tsc_page(v->kvm, &vcpu->hv_घड़ी);
	वापस 0;
पूर्ण

/*
 * kvmघड़ी updates which are isolated to a given vcpu, such as
 * vcpu->cpu migration, should not allow प्रणाली_बारtamp from
 * the rest of the vcpus to reमुख्य अटल. Otherwise ntp frequency
 * correction applies to one vcpu's प्रणाली_बारtamp but not
 * the others.
 *
 * So in those हालs, request a kvmघड़ी update क्रम all vcpus.
 * We need to rate-limit these requests though, as they can
 * considerably slow guests that have a large number of vcpus.
 * The समय क्रम a remote vcpu to update its kvmघड़ी is bound
 * by the delay we use to rate-limit the updates.
 */

#घोषणा KVMCLOCK_UPDATE_DELAY msecs_to_jअगरfies(100)

अटल व्योम kvmघड़ी_update_fn(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा kvm_arch *ka = container_of(dwork, काष्ठा kvm_arch,
					   kvmघड़ी_update_work);
	काष्ठा kvm *kvm = container_of(ka, काष्ठा kvm, arch);
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
		kvm_vcpu_kick(vcpu);
	पूर्ण
पूर्ण

अटल व्योम kvm_gen_kvmघड़ी_update(काष्ठा kvm_vcpu *v)
अणु
	काष्ठा kvm *kvm = v->kvm;

	kvm_make_request(KVM_REQ_CLOCK_UPDATE, v);
	schedule_delayed_work(&kvm->arch.kvmघड़ी_update_work,
					KVMCLOCK_UPDATE_DELAY);
पूर्ण

#घोषणा KVMCLOCK_SYNC_PERIOD (300 * HZ)

अटल व्योम kvmघड़ी_sync_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा kvm_arch *ka = container_of(dwork, काष्ठा kvm_arch,
					   kvmघड़ी_sync_work);
	काष्ठा kvm *kvm = container_of(ka, काष्ठा kvm, arch);

	अगर (!kvmघड़ी_periodic_sync)
		वापस;

	schedule_delayed_work(&kvm->arch.kvmघड़ी_update_work, 0);
	schedule_delayed_work(&kvm->arch.kvmघड़ी_sync_work,
					KVMCLOCK_SYNC_PERIOD);
पूर्ण

/*
 * On AMD, HWCR[McStatusWrEn] controls whether setting MCi_STATUS results in #GP.
 */
अटल bool can_set_mci_status(काष्ठा kvm_vcpu *vcpu)
अणु
	/* McStatusWrEn enabled? */
	अगर (guest_cpuid_is_amd_or_hygon(vcpu))
		वापस !!(vcpu->arch.msr_hwcr & BIT_ULL(18));

	वापस false;
पूर्ण

अटल पूर्णांक set_msr_mce(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	u64 mcg_cap = vcpu->arch.mcg_cap;
	अचिन्हित bank_num = mcg_cap & 0xff;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	चयन (msr) अणु
	हाल MSR_IA32_MCG_STATUS:
		vcpu->arch.mcg_status = data;
		अवरोध;
	हाल MSR_IA32_MCG_CTL:
		अगर (!(mcg_cap & MCG_CTL_P) &&
		    (data || !msr_info->host_initiated))
			वापस 1;
		अगर (data != 0 && data != ~(u64)0)
			वापस 1;
		vcpu->arch.mcg_ctl = data;
		अवरोध;
	शेष:
		अगर (msr >= MSR_IA32_MC0_CTL &&
		    msr < MSR_IA32_MCx_CTL(bank_num)) अणु
			u32 offset = array_index_nospec(
				msr - MSR_IA32_MC0_CTL,
				MSR_IA32_MCx_CTL(bank_num) - MSR_IA32_MC0_CTL);

			/* only 0 or all 1s can be written to IA32_MCi_CTL
			 * some Linux kernels though clear bit 10 in bank 4 to
			 * workaround a BIOS/GART TBL issue on AMD K8s, ignore
			 * this to aव्योम an uncatched #GP in the guest
			 */
			अगर ((offset & 0x3) == 0 &&
			    data != 0 && (data | (1 << 10)) != ~(u64)0)
				वापस -1;

			/* MCi_STATUS */
			अगर (!msr_info->host_initiated &&
			    (offset & 0x3) == 1 && data != 0) अणु
				अगर (!can_set_mci_status(vcpu))
					वापस -1;
			पूर्ण

			vcpu->arch.mce_banks[offset] = data;
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool kvm_pv_async_pf_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 mask = KVM_ASYNC_PF_ENABLED | KVM_ASYNC_PF_DELIVERY_AS_INT;

	वापस (vcpu->arch.apf.msr_en_val & mask) == mask;
पूर्ण

अटल पूर्णांक kvm_pv_enable_async_pf(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	gpa_t gpa = data & ~0x3f;

	/* Bits 4:5 are reserved, Should be zero */
	अगर (data & 0x30)
		वापस 1;

	अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF_VMEXIT) &&
	    (data & KVM_ASYNC_PF_DELIVERY_AS_PF_VMEXIT))
		वापस 1;

	अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF_INT) &&
	    (data & KVM_ASYNC_PF_DELIVERY_AS_INT))
		वापस 1;

	अगर (!lapic_in_kernel(vcpu))
		वापस data ? 1 : 0;

	vcpu->arch.apf.msr_en_val = data;

	अगर (!kvm_pv_async_pf_enabled(vcpu)) अणु
		kvm_clear_async_pf_completion_queue(vcpu);
		kvm_async_pf_hash_reset(vcpu);
		वापस 0;
	पूर्ण

	अगर (kvm_gfn_to_hva_cache_init(vcpu->kvm, &vcpu->arch.apf.data, gpa,
					माप(u64)))
		वापस 1;

	vcpu->arch.apf.send_user_only = !(data & KVM_ASYNC_PF_SEND_ALWAYS);
	vcpu->arch.apf.delivery_as_pf_vmनिकास = data & KVM_ASYNC_PF_DELIVERY_AS_PF_VMEXIT;

	kvm_async_pf_wakeup_all(vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_pv_enable_async_pf_पूर्णांक(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	/* Bits 8-63 are reserved */
	अगर (data >> 8)
		वापस 1;

	अगर (!lapic_in_kernel(vcpu))
		वापस 1;

	vcpu->arch.apf.msr_पूर्णांक_val = data;

	vcpu->arch.apf.vec = data & KVM_ASYNC_PF_VEC_MASK;

	वापस 0;
पूर्ण

अटल व्योम kvmघड़ी_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.pv_समय_enabled = false;
	vcpu->arch.समय = 0;
पूर्ण

अटल व्योम kvm_vcpu_flush_tlb_all(काष्ठा kvm_vcpu *vcpu)
अणु
	++vcpu->stat.tlb_flush;
	अटल_call(kvm_x86_tlb_flush_all)(vcpu);
पूर्ण

अटल व्योम kvm_vcpu_flush_tlb_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	++vcpu->stat.tlb_flush;

	अगर (!tdp_enabled) अणु
               /*
		 * A TLB flush on behalf of the guest is equivalent to
		 * INVPCID(all), toggling CR4.PGE, etc., which requires
		 * a क्रमced sync of the shaकरोw page tables.  Unload the
		 * entire MMU here and the subsequent load will sync the
		 * shaकरोw page tables, and also flush the TLB.
		 */
		kvm_mmu_unload(vcpu);
		वापस;
	पूर्ण

	अटल_call(kvm_x86_tlb_flush_guest)(vcpu);
पूर्ण

अटल व्योम record_steal_समय(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_host_map map;
	काष्ठा kvm_steal_समय *st;

	अगर (kvm_xen_msr_enabled(vcpu->kvm)) अणु
		kvm_xen_runstate_set_running(vcpu);
		वापस;
	पूर्ण

	अगर (!(vcpu->arch.st.msr_val & KVM_MSR_ENABLED))
		वापस;

	/* -EAGAIN is वापसed in atomic context so we can just वापस. */
	अगर (kvm_map_gfn(vcpu, vcpu->arch.st.msr_val >> PAGE_SHIFT,
			&map, &vcpu->arch.st.cache, false))
		वापस;

	st = map.hva +
		offset_in_page(vcpu->arch.st.msr_val & KVM_STEAL_VALID_BITS);

	/*
	 * Doing a TLB flush here, on the guest's behalf, can aव्योम
	 * expensive IPIs.
	 */
	अगर (guest_pv_has(vcpu, KVM_FEATURE_PV_TLB_FLUSH)) अणु
		u8 st_preempted = xchg(&st->preempted, 0);

		trace_kvm_pv_tlb_flush(vcpu->vcpu_id,
				       st_preempted & KVM_VCPU_FLUSH_TLB);
		अगर (st_preempted & KVM_VCPU_FLUSH_TLB)
			kvm_vcpu_flush_tlb_guest(vcpu);
	पूर्ण अन्यथा अणु
		st->preempted = 0;
	पूर्ण

	vcpu->arch.st.preempted = 0;

	अगर (st->version & 1)
		st->version += 1;  /* first समय ग_लिखो, अक्रमom junk */

	st->version += 1;

	smp_wmb();

	st->steal += current->sched_info.run_delay -
		vcpu->arch.st.last_steal;
	vcpu->arch.st.last_steal = current->sched_info.run_delay;

	smp_wmb();

	st->version += 1;

	kvm_unmap_gfn(vcpu, &map, &vcpu->arch.st.cache, true, false);
पूर्ण

पूर्णांक kvm_set_msr_common(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	bool pr = false;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	अगर (msr && msr == vcpu->kvm->arch.xen_hvm_config.msr)
		वापस kvm_xen_ग_लिखो_hypercall_page(vcpu, data);

	चयन (msr) अणु
	हाल MSR_AMD64_NB_CFG:
	हाल MSR_IA32_UCODE_WRITE:
	हाल MSR_VM_HSAVE_PA:
	हाल MSR_AMD64_PATCH_LOADER:
	हाल MSR_AMD64_BU_CFG2:
	हाल MSR_AMD64_DC_CFG:
	हाल MSR_F15H_EX_CFG:
		अवरोध;

	हाल MSR_IA32_UCODE_REV:
		अगर (msr_info->host_initiated)
			vcpu->arch.microcode_version = data;
		अवरोध;
	हाल MSR_IA32_ARCH_CAPABILITIES:
		अगर (!msr_info->host_initiated)
			वापस 1;
		vcpu->arch.arch_capabilities = data;
		अवरोध;
	हाल MSR_IA32_PERF_CAPABILITIES: अणु
		काष्ठा kvm_msr_entry msr_ent = अणु.index = msr, .data = 0पूर्ण;

		अगर (!msr_info->host_initiated)
			वापस 1;
		अगर (guest_cpuid_has(vcpu, X86_FEATURE_PDCM) && kvm_get_msr_feature(&msr_ent))
			वापस 1;
		अगर (data & ~msr_ent.data)
			वापस 1;

		vcpu->arch.perf_capabilities = data;

		वापस 0;
		पूर्ण
	हाल MSR_EFER:
		वापस set_efer(vcpu, msr_info);
	हाल MSR_K7_HWCR:
		data &= ~(u64)0x40;	/* ignore flush filter disable */
		data &= ~(u64)0x100;	/* ignore ignne emulation enable */
		data &= ~(u64)0x8;	/* ignore TLB cache disable */

		/* Handle McStatusWrEn */
		अगर (data == BIT_ULL(18)) अणु
			vcpu->arch.msr_hwcr = data;
		पूर्ण अन्यथा अगर (data != 0) अणु
			vcpu_unimpl(vcpu, "unimplemented HWCR wrmsr: 0x%llx\n",
				    data);
			वापस 1;
		पूर्ण
		अवरोध;
	हाल MSR_FAM10H_MMIO_CONF_BASE:
		अगर (data != 0) अणु
			vcpu_unimpl(vcpu, "unimplemented MMIO_CONF_BASE wrmsr: "
				    "0x%llx\n", data);
			वापस 1;
		पूर्ण
		अवरोध;
	हाल 0x200 ... 0x2ff:
		वापस kvm_mtrr_set_msr(vcpu, msr, data);
	हाल MSR_IA32_APICBASE:
		वापस kvm_set_apic_base(vcpu, msr_info);
	हाल APIC_BASE_MSR ... APIC_BASE_MSR + 0xff:
		वापस kvm_x2apic_msr_ग_लिखो(vcpu, msr, data);
	हाल MSR_IA32_TSC_DEADLINE:
		kvm_set_lapic_tscdeadline_msr(vcpu, data);
		अवरोध;
	हाल MSR_IA32_TSC_ADJUST:
		अगर (guest_cpuid_has(vcpu, X86_FEATURE_TSC_ADJUST)) अणु
			अगर (!msr_info->host_initiated) अणु
				s64 adj = data - vcpu->arch.ia32_tsc_adjust_msr;
				adjust_tsc_offset_guest(vcpu, adj);
			पूर्ण
			vcpu->arch.ia32_tsc_adjust_msr = data;
		पूर्ण
		अवरोध;
	हाल MSR_IA32_MISC_ENABLE:
		अगर (!kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_MISC_ENABLE_NO_MWAIT) &&
		    ((vcpu->arch.ia32_misc_enable_msr ^ data) & MSR_IA32_MISC_ENABLE_MWAIT)) अणु
			अगर (!guest_cpuid_has(vcpu, X86_FEATURE_XMM3))
				वापस 1;
			vcpu->arch.ia32_misc_enable_msr = data;
			kvm_update_cpuid_runसमय(vcpu);
		पूर्ण अन्यथा अणु
			vcpu->arch.ia32_misc_enable_msr = data;
		पूर्ण
		अवरोध;
	हाल MSR_IA32_SMBASE:
		अगर (!msr_info->host_initiated)
			वापस 1;
		vcpu->arch.smbase = data;
		अवरोध;
	हाल MSR_IA32_POWER_CTL:
		vcpu->arch.msr_ia32_घातer_ctl = data;
		अवरोध;
	हाल MSR_IA32_TSC:
		अगर (msr_info->host_initiated) अणु
			kvm_synchronize_tsc(vcpu, data);
		पूर्ण अन्यथा अणु
			u64 adj = kvm_compute_tsc_offset(vcpu, data) - vcpu->arch.l1_tsc_offset;
			adjust_tsc_offset_guest(vcpu, adj);
			vcpu->arch.ia32_tsc_adjust_msr += adj;
		पूर्ण
		अवरोध;
	हाल MSR_IA32_XSS:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_XSAVES))
			वापस 1;
		/*
		 * KVM supports exposing PT to the guest, but करोes not support
		 * IA32_XSS[bit 8]. Guests have to use RDMSR/WRMSR rather than
		 * XSAVES/XRSTORS to save/restore PT MSRs.
		 */
		अगर (data & ~supported_xss)
			वापस 1;
		vcpu->arch.ia32_xss = data;
		अवरोध;
	हाल MSR_SMI_COUNT:
		अगर (!msr_info->host_initiated)
			वापस 1;
		vcpu->arch.smi_count = data;
		अवरोध;
	हाल MSR_KVM_WALL_CLOCK_NEW:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE2))
			वापस 1;

		vcpu->kvm->arch.wall_घड़ी = data;
		kvm_ग_लिखो_wall_घड़ी(vcpu->kvm, data, 0);
		अवरोध;
	हाल MSR_KVM_WALL_CLOCK:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE))
			वापस 1;

		vcpu->kvm->arch.wall_घड़ी = data;
		kvm_ग_लिखो_wall_घड़ी(vcpu->kvm, data, 0);
		अवरोध;
	हाल MSR_KVM_SYSTEM_TIME_NEW:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE2))
			वापस 1;

		kvm_ग_लिखो_प्रणाली_समय(vcpu, data, false, msr_info->host_initiated);
		अवरोध;
	हाल MSR_KVM_SYSTEM_TIME:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE))
			वापस 1;

		kvm_ग_लिखो_प्रणाली_समय(vcpu, data, true,  msr_info->host_initiated);
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_EN:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF))
			वापस 1;

		अगर (kvm_pv_enable_async_pf(vcpu, data))
			वापस 1;
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_INT:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF_INT))
			वापस 1;

		अगर (kvm_pv_enable_async_pf_पूर्णांक(vcpu, data))
			वापस 1;
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_ACK:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF))
			वापस 1;
		अगर (data & 0x1) अणु
			vcpu->arch.apf.pageपढ़ोy_pending = false;
			kvm_check_async_pf_completion(vcpu);
		पूर्ण
		अवरोध;
	हाल MSR_KVM_STEAL_TIME:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_STEAL_TIME))
			वापस 1;

		अगर (unlikely(!sched_info_on()))
			वापस 1;

		अगर (data & KVM_STEAL_RESERVED_MASK)
			वापस 1;

		vcpu->arch.st.msr_val = data;

		अगर (!(data & KVM_MSR_ENABLED))
			अवरोध;

		kvm_make_request(KVM_REQ_STEAL_UPDATE, vcpu);

		अवरोध;
	हाल MSR_KVM_PV_EOI_EN:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_PV_EOI))
			वापस 1;

		अगर (kvm_lapic_enable_pv_eoi(vcpu, data, माप(u8)))
			वापस 1;
		अवरोध;

	हाल MSR_KVM_POLL_CONTROL:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_POLL_CONTROL))
			वापस 1;

		/* only enable bit supported */
		अगर (data & (-1ULL << 1))
			वापस 1;

		vcpu->arch.msr_kvm_poll_control = data;
		अवरोध;

	हाल MSR_IA32_MCG_CTL:
	हाल MSR_IA32_MCG_STATUS:
	हाल MSR_IA32_MC0_CTL ... MSR_IA32_MCx_CTL(KVM_MAX_MCE_BANKS) - 1:
		वापस set_msr_mce(vcpu, msr_info);

	हाल MSR_K7_PERFCTR0 ... MSR_K7_PERFCTR3:
	हाल MSR_P6_PERFCTR0 ... MSR_P6_PERFCTR1:
		pr = true;
		fallthrough;
	हाल MSR_K7_EVNTSEL0 ... MSR_K7_EVNTSEL3:
	हाल MSR_P6_EVNTSEL0 ... MSR_P6_EVNTSEL1:
		अगर (kvm_pmu_is_valid_msr(vcpu, msr))
			वापस kvm_pmu_set_msr(vcpu, msr_info);

		अगर (pr || data != 0)
			vcpu_unimpl(vcpu, "disabled perfctr wrmsr: "
				    "0x%x data 0x%llx\n", msr, data);
		अवरोध;
	हाल MSR_K7_CLK_CTL:
		/*
		 * Ignore all ग_लिखोs to this no दीर्घer करोcumented MSR.
		 * Writes are only relevant क्रम old K7 processors,
		 * all pre-dating SVM, but a recommended workaround from
		 * AMD क्रम these chips. It is possible to specअगरy the
		 * affected processor models on the command line, hence
		 * the need to ignore the workaround.
		 */
		अवरोध;
	हाल HV_X64_MSR_GUEST_OS_ID ... HV_X64_MSR_SINT15:
	हाल HV_X64_MSR_SYNDBG_CONTROL ... HV_X64_MSR_SYNDBG_PENDING_BUFFER:
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
	हाल HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:
	हाल HV_X64_MSR_CRASH_CTL:
	हाल HV_X64_MSR_STIMER0_CONFIG ... HV_X64_MSR_STIMER3_COUNT:
	हाल HV_X64_MSR_REENLIGHTENMENT_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_STATUS:
		वापस kvm_hv_set_msr_common(vcpu, msr, data,
					     msr_info->host_initiated);
	हाल MSR_IA32_BBL_CR_CTL3:
		/* Drop ग_लिखोs to this legacy MSR -- see rdmsr
		 * counterpart क्रम further detail.
		 */
		अगर (report_ignored_msrs)
			vcpu_unimpl(vcpu, "ignored wrmsr: 0x%x data 0x%llx\n",
				msr, data);
		अवरोध;
	हाल MSR_AMD64_OSVW_ID_LENGTH:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_OSVW))
			वापस 1;
		vcpu->arch.osvw.length = data;
		अवरोध;
	हाल MSR_AMD64_OSVW_STATUS:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_OSVW))
			वापस 1;
		vcpu->arch.osvw.status = data;
		अवरोध;
	हाल MSR_PLATFORM_INFO:
		अगर (!msr_info->host_initiated ||
		    (!(data & MSR_PLATFORM_INFO_CPUID_FAULT) &&
		     cpuid_fault_enabled(vcpu)))
			वापस 1;
		vcpu->arch.msr_platक्रमm_info = data;
		अवरोध;
	हाल MSR_MISC_FEATURES_ENABLES:
		अगर (data & ~MSR_MISC_FEATURES_ENABLES_CPUID_FAULT ||
		    (data & MSR_MISC_FEATURES_ENABLES_CPUID_FAULT &&
		     !supports_cpuid_fault(vcpu)))
			वापस 1;
		vcpu->arch.msr_misc_features_enables = data;
		अवरोध;
	शेष:
		अगर (kvm_pmu_is_valid_msr(vcpu, msr))
			वापस kvm_pmu_set_msr(vcpu, msr_info);
		वापस KVM_MSR_RET_INVALID;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_msr_common);

अटल पूर्णांक get_msr_mce(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata, bool host)
अणु
	u64 data;
	u64 mcg_cap = vcpu->arch.mcg_cap;
	अचिन्हित bank_num = mcg_cap & 0xff;

	चयन (msr) अणु
	हाल MSR_IA32_P5_MC_ADDR:
	हाल MSR_IA32_P5_MC_TYPE:
		data = 0;
		अवरोध;
	हाल MSR_IA32_MCG_CAP:
		data = vcpu->arch.mcg_cap;
		अवरोध;
	हाल MSR_IA32_MCG_CTL:
		अगर (!(mcg_cap & MCG_CTL_P) && !host)
			वापस 1;
		data = vcpu->arch.mcg_ctl;
		अवरोध;
	हाल MSR_IA32_MCG_STATUS:
		data = vcpu->arch.mcg_status;
		अवरोध;
	शेष:
		अगर (msr >= MSR_IA32_MC0_CTL &&
		    msr < MSR_IA32_MCx_CTL(bank_num)) अणु
			u32 offset = array_index_nospec(
				msr - MSR_IA32_MC0_CTL,
				MSR_IA32_MCx_CTL(bank_num) - MSR_IA32_MC0_CTL);

			data = vcpu->arch.mce_banks[offset];
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण
	*pdata = data;
	वापस 0;
पूर्ण

पूर्णांक kvm_get_msr_common(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	चयन (msr_info->index) अणु
	हाल MSR_IA32_PLATFORM_ID:
	हाल MSR_IA32_EBL_CR_POWERON:
	हाल MSR_IA32_LASTBRANCHFROMIP:
	हाल MSR_IA32_LASTBRANCHTOIP:
	हाल MSR_IA32_LASTINTFROMIP:
	हाल MSR_IA32_LASTINTTOIP:
	हाल MSR_AMD64_SYSCFG:
	हाल MSR_K8_TSEG_ADDR:
	हाल MSR_K8_TSEG_MASK:
	हाल MSR_VM_HSAVE_PA:
	हाल MSR_K8_INT_PENDING_MSG:
	हाल MSR_AMD64_NB_CFG:
	हाल MSR_FAM10H_MMIO_CONF_BASE:
	हाल MSR_AMD64_BU_CFG2:
	हाल MSR_IA32_PERF_CTL:
	हाल MSR_AMD64_DC_CFG:
	हाल MSR_F15H_EX_CFG:
	/*
	 * Intel Sandy Bridge CPUs must support the RAPL (running average घातer
	 * limit) MSRs. Just वापस 0, as we करो not want to expose the host
	 * data here. Do not conditionalize this on CPUID, as KVM करोes not करो
	 * so क्रम existing CPU-specअगरic MSRs.
	 */
	हाल MSR_RAPL_POWER_UNIT:
	हाल MSR_PP0_ENERGY_STATUS:	/* Power plane 0 (core) */
	हाल MSR_PP1_ENERGY_STATUS:	/* Power plane 1 (graphics uncore) */
	हाल MSR_PKG_ENERGY_STATUS:	/* Total package */
	हाल MSR_DRAM_ENERGY_STATUS:	/* DRAM controller */
		msr_info->data = 0;
		अवरोध;
	हाल MSR_F15H_PERF_CTL0 ... MSR_F15H_PERF_CTR5:
		अगर (kvm_pmu_is_valid_msr(vcpu, msr_info->index))
			वापस kvm_pmu_get_msr(vcpu, msr_info);
		अगर (!msr_info->host_initiated)
			वापस 1;
		msr_info->data = 0;
		अवरोध;
	हाल MSR_K7_EVNTSEL0 ... MSR_K7_EVNTSEL3:
	हाल MSR_K7_PERFCTR0 ... MSR_K7_PERFCTR3:
	हाल MSR_P6_PERFCTR0 ... MSR_P6_PERFCTR1:
	हाल MSR_P6_EVNTSEL0 ... MSR_P6_EVNTSEL1:
		अगर (kvm_pmu_is_valid_msr(vcpu, msr_info->index))
			वापस kvm_pmu_get_msr(vcpu, msr_info);
		msr_info->data = 0;
		अवरोध;
	हाल MSR_IA32_UCODE_REV:
		msr_info->data = vcpu->arch.microcode_version;
		अवरोध;
	हाल MSR_IA32_ARCH_CAPABILITIES:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_ARCH_CAPABILITIES))
			वापस 1;
		msr_info->data = vcpu->arch.arch_capabilities;
		अवरोध;
	हाल MSR_IA32_PERF_CAPABILITIES:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_PDCM))
			वापस 1;
		msr_info->data = vcpu->arch.perf_capabilities;
		अवरोध;
	हाल MSR_IA32_POWER_CTL:
		msr_info->data = vcpu->arch.msr_ia32_घातer_ctl;
		अवरोध;
	हाल MSR_IA32_TSC: अणु
		/*
		 * Intel SDM states that MSR_IA32_TSC पढ़ो adds the TSC offset
		 * even when not पूर्णांकercepted. AMD manual करोesn't explicitly
		 * state this but appears to behave the same.
		 *
		 * On userspace पढ़ोs and ग_लिखोs, however, we unconditionally
		 * वापस L1's TSC value to ensure backwards-compatible
		 * behavior क्रम migration.
		 */
		u64 tsc_offset = msr_info->host_initiated ? vcpu->arch.l1_tsc_offset :
							    vcpu->arch.tsc_offset;

		msr_info->data = kvm_scale_tsc(vcpu, rdtsc()) + tsc_offset;
		अवरोध;
	पूर्ण
	हाल MSR_MTRRcap:
	हाल 0x200 ... 0x2ff:
		वापस kvm_mtrr_get_msr(vcpu, msr_info->index, &msr_info->data);
	हाल 0xcd: /* fsb frequency */
		msr_info->data = 3;
		अवरोध;
		/*
		 * MSR_EBC_FREQUENCY_ID
		 * Conservative value valid क्रम even the basic CPU models.
		 * Models 0,1: 000 in bits 23:21 indicating a bus speed of
		 * 100MHz, model 2 000 in bits 18:16 indicating 100MHz,
		 * and 266MHz क्रम model 3, or 4. Set Core Clock
		 * Frequency to System Bus Frequency Ratio to 1 (bits
		 * 31:24) even though these are only valid क्रम CPU
		 * models > 2, however guests may end up भागiding or
		 * multiplying by zero otherwise.
		 */
	हाल MSR_EBC_FREQUENCY_ID:
		msr_info->data = 1 << 24;
		अवरोध;
	हाल MSR_IA32_APICBASE:
		msr_info->data = kvm_get_apic_base(vcpu);
		अवरोध;
	हाल APIC_BASE_MSR ... APIC_BASE_MSR + 0xff:
		वापस kvm_x2apic_msr_पढ़ो(vcpu, msr_info->index, &msr_info->data);
	हाल MSR_IA32_TSC_DEADLINE:
		msr_info->data = kvm_get_lapic_tscdeadline_msr(vcpu);
		अवरोध;
	हाल MSR_IA32_TSC_ADJUST:
		msr_info->data = (u64)vcpu->arch.ia32_tsc_adjust_msr;
		अवरोध;
	हाल MSR_IA32_MISC_ENABLE:
		msr_info->data = vcpu->arch.ia32_misc_enable_msr;
		अवरोध;
	हाल MSR_IA32_SMBASE:
		अगर (!msr_info->host_initiated)
			वापस 1;
		msr_info->data = vcpu->arch.smbase;
		अवरोध;
	हाल MSR_SMI_COUNT:
		msr_info->data = vcpu->arch.smi_count;
		अवरोध;
	हाल MSR_IA32_PERF_STATUS:
		/* TSC increment by tick */
		msr_info->data = 1000ULL;
		/* CPU multiplier */
		msr_info->data |= (((uपूर्णांक64_t)4ULL) << 40);
		अवरोध;
	हाल MSR_EFER:
		msr_info->data = vcpu->arch.efer;
		अवरोध;
	हाल MSR_KVM_WALL_CLOCK:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE))
			वापस 1;

		msr_info->data = vcpu->kvm->arch.wall_घड़ी;
		अवरोध;
	हाल MSR_KVM_WALL_CLOCK_NEW:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE2))
			वापस 1;

		msr_info->data = vcpu->kvm->arch.wall_घड़ी;
		अवरोध;
	हाल MSR_KVM_SYSTEM_TIME:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE))
			वापस 1;

		msr_info->data = vcpu->arch.समय;
		अवरोध;
	हाल MSR_KVM_SYSTEM_TIME_NEW:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_CLOCKSOURCE2))
			वापस 1;

		msr_info->data = vcpu->arch.समय;
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_EN:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF))
			वापस 1;

		msr_info->data = vcpu->arch.apf.msr_en_val;
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_INT:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF_INT))
			वापस 1;

		msr_info->data = vcpu->arch.apf.msr_पूर्णांक_val;
		अवरोध;
	हाल MSR_KVM_ASYNC_PF_ACK:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_ASYNC_PF))
			वापस 1;

		msr_info->data = 0;
		अवरोध;
	हाल MSR_KVM_STEAL_TIME:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_STEAL_TIME))
			वापस 1;

		msr_info->data = vcpu->arch.st.msr_val;
		अवरोध;
	हाल MSR_KVM_PV_EOI_EN:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_PV_EOI))
			वापस 1;

		msr_info->data = vcpu->arch.pv_eoi.msr_val;
		अवरोध;
	हाल MSR_KVM_POLL_CONTROL:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_POLL_CONTROL))
			वापस 1;

		msr_info->data = vcpu->arch.msr_kvm_poll_control;
		अवरोध;
	हाल MSR_IA32_P5_MC_ADDR:
	हाल MSR_IA32_P5_MC_TYPE:
	हाल MSR_IA32_MCG_CAP:
	हाल MSR_IA32_MCG_CTL:
	हाल MSR_IA32_MCG_STATUS:
	हाल MSR_IA32_MC0_CTL ... MSR_IA32_MCx_CTL(KVM_MAX_MCE_BANKS) - 1:
		वापस get_msr_mce(vcpu, msr_info->index, &msr_info->data,
				   msr_info->host_initiated);
	हाल MSR_IA32_XSS:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_XSAVES))
			वापस 1;
		msr_info->data = vcpu->arch.ia32_xss;
		अवरोध;
	हाल MSR_K7_CLK_CTL:
		/*
		 * Provide expected ramp-up count क्रम K7. All other
		 * are set to zero, indicating minimum भागisors क्रम
		 * every field.
		 *
		 * This prevents guest kernels on AMD host with CPU
		 * type 6, model 8 and higher from exploding due to
		 * the rdmsr failing.
		 */
		msr_info->data = 0x20000000;
		अवरोध;
	हाल HV_X64_MSR_GUEST_OS_ID ... HV_X64_MSR_SINT15:
	हाल HV_X64_MSR_SYNDBG_CONTROL ... HV_X64_MSR_SYNDBG_PENDING_BUFFER:
	हाल HV_X64_MSR_SYNDBG_OPTIONS:
	हाल HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:
	हाल HV_X64_MSR_CRASH_CTL:
	हाल HV_X64_MSR_STIMER0_CONFIG ... HV_X64_MSR_STIMER3_COUNT:
	हाल HV_X64_MSR_REENLIGHTENMENT_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_CONTROL:
	हाल HV_X64_MSR_TSC_EMULATION_STATUS:
		वापस kvm_hv_get_msr_common(vcpu,
					     msr_info->index, &msr_info->data,
					     msr_info->host_initiated);
	हाल MSR_IA32_BBL_CR_CTL3:
		/* This legacy MSR exists but isn't fully करोcumented in current
		 * silicon.  It is however accessed by winxp in very narrow
		 * scenarios where it sets bit #19, itself करोcumented as
		 * a "reserved" bit.  Best efक्रमt attempt to source coherent
		 * पढ़ो data here should the balance of the रेजिस्टर be
		 * पूर्णांकerpreted by the guest:
		 *
		 * L2 cache control रेजिस्टर 3: 64GB range, 256KB size,
		 * enabled, latency 0x1, configured
		 */
		msr_info->data = 0xbe702111;
		अवरोध;
	हाल MSR_AMD64_OSVW_ID_LENGTH:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_OSVW))
			वापस 1;
		msr_info->data = vcpu->arch.osvw.length;
		अवरोध;
	हाल MSR_AMD64_OSVW_STATUS:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_OSVW))
			वापस 1;
		msr_info->data = vcpu->arch.osvw.status;
		अवरोध;
	हाल MSR_PLATFORM_INFO:
		अगर (!msr_info->host_initiated &&
		    !vcpu->kvm->arch.guest_can_पढ़ो_msr_platक्रमm_info)
			वापस 1;
		msr_info->data = vcpu->arch.msr_platक्रमm_info;
		अवरोध;
	हाल MSR_MISC_FEATURES_ENABLES:
		msr_info->data = vcpu->arch.msr_misc_features_enables;
		अवरोध;
	हाल MSR_K7_HWCR:
		msr_info->data = vcpu->arch.msr_hwcr;
		अवरोध;
	शेष:
		अगर (kvm_pmu_is_valid_msr(vcpu, msr_info->index))
			वापस kvm_pmu_get_msr(vcpu, msr_info);
		वापस KVM_MSR_RET_INVALID;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_msr_common);

/*
 * Read or ग_लिखो a bunch of msrs. All parameters are kernel addresses.
 *
 * @वापस number of msrs set successfully.
 */
अटल पूर्णांक __msr_io(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_msrs *msrs,
		    काष्ठा kvm_msr_entry *entries,
		    पूर्णांक (*करो_msr)(काष्ठा kvm_vcpu *vcpu,
				  अचिन्हित index, u64 *data))
अणु
	पूर्णांक i;

	क्रम (i = 0; i < msrs->nmsrs; ++i)
		अगर (करो_msr(vcpu, entries[i].index, &entries[i].data))
			अवरोध;

	वापस i;
पूर्ण

/*
 * Read or ग_लिखो a bunch of msrs. Parameters are user addresses.
 *
 * @वापस number of msrs set successfully.
 */
अटल पूर्णांक msr_io(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_msrs __user *user_msrs,
		  पूर्णांक (*करो_msr)(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित index, u64 *data),
		  पूर्णांक ग_लिखोback)
अणु
	काष्ठा kvm_msrs msrs;
	काष्ठा kvm_msr_entry *entries;
	पूर्णांक r, n;
	अचिन्हित size;

	r = -EFAULT;
	अगर (copy_from_user(&msrs, user_msrs, माप(msrs)))
		जाओ out;

	r = -E2BIG;
	अगर (msrs.nmsrs >= MAX_IO_MSRS)
		जाओ out;

	size = माप(काष्ठा kvm_msr_entry) * msrs.nmsrs;
	entries = memdup_user(user_msrs->entries, size);
	अगर (IS_ERR(entries)) अणु
		r = PTR_ERR(entries);
		जाओ out;
	पूर्ण

	r = n = __msr_io(vcpu, &msrs, entries, करो_msr);
	अगर (r < 0)
		जाओ out_मुक्त;

	r = -EFAULT;
	अगर (ग_लिखोback && copy_to_user(user_msrs->entries, entries, size))
		जाओ out_मुक्त;

	r = n;

out_मुक्त:
	kमुक्त(entries);
out:
	वापस r;
पूर्ण

अटल अंतरभूत bool kvm_can_mरुको_in_guest(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_MWAIT) &&
		!boot_cpu_has_bug(X86_BUG_MONITOR) &&
		boot_cpu_has(X86_FEATURE_ARAT);
पूर्ण

अटल पूर्णांक kvm_ioctl_get_supported_hv_cpuid(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_cpuid2 __user *cpuid_arg)
अणु
	काष्ठा kvm_cpuid2 cpuid;
	पूर्णांक r;

	r = -EFAULT;
	अगर (copy_from_user(&cpuid, cpuid_arg, माप(cpuid)))
		वापस r;

	r = kvm_get_hv_cpuid(vcpu, &cpuid, cpuid_arg->entries);
	अगर (r)
		वापस r;

	r = -EFAULT;
	अगर (copy_to_user(cpuid_arg, &cpuid, माप(cpuid)))
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r = 0;

	चयन (ext) अणु
	हाल KVM_CAP_IRQCHIP:
	हाल KVM_CAP_HLT:
	हाल KVM_CAP_MMU_SHADOW_CACHE_CONTROL:
	हाल KVM_CAP_SET_TSS_ADDR:
	हाल KVM_CAP_EXT_CPUID:
	हाल KVM_CAP_EXT_EMUL_CPUID:
	हाल KVM_CAP_CLOCKSOURCE:
	हाल KVM_CAP_PIT:
	हाल KVM_CAP_NOP_IO_DELAY:
	हाल KVM_CAP_MP_STATE:
	हाल KVM_CAP_SYNC_MMU:
	हाल KVM_CAP_USER_NMI:
	हाल KVM_CAP_REINJECT_CONTROL:
	हाल KVM_CAP_IRQ_INJECT_STATUS:
	हाल KVM_CAP_IOEVENTFD:
	हाल KVM_CAP_IOEVENTFD_NO_LENGTH:
	हाल KVM_CAP_PIT2:
	हाल KVM_CAP_PIT_STATE2:
	हाल KVM_CAP_SET_IDENTITY_MAP_ADDR:
	हाल KVM_CAP_VCPU_EVENTS:
	हाल KVM_CAP_HYPERV:
	हाल KVM_CAP_HYPERV_VAPIC:
	हाल KVM_CAP_HYPERV_SPIN:
	हाल KVM_CAP_HYPERV_SYNIC:
	हाल KVM_CAP_HYPERV_SYNIC2:
	हाल KVM_CAP_HYPERV_VP_INDEX:
	हाल KVM_CAP_HYPERV_EVENTFD:
	हाल KVM_CAP_HYPERV_TLBFLUSH:
	हाल KVM_CAP_HYPERV_SEND_IPI:
	हाल KVM_CAP_HYPERV_CPUID:
	हाल KVM_CAP_SYS_HYPERV_CPUID:
	हाल KVM_CAP_PCI_SEGMENT:
	हाल KVM_CAP_DEBUGREGS:
	हाल KVM_CAP_X86_ROBUST_SINGLESTEP:
	हाल KVM_CAP_XSAVE:
	हाल KVM_CAP_ASYNC_PF:
	हाल KVM_CAP_ASYNC_PF_INT:
	हाल KVM_CAP_GET_TSC_KHZ:
	हाल KVM_CAP_KVMCLOCK_CTRL:
	हाल KVM_CAP_READONLY_MEM:
	हाल KVM_CAP_HYPERV_TIME:
	हाल KVM_CAP_IOAPIC_POLARITY_IGNORED:
	हाल KVM_CAP_TSC_DEADLINE_TIMER:
	हाल KVM_CAP_DISABLE_QUIRKS:
	हाल KVM_CAP_SET_BOOT_CPU_ID:
 	हाल KVM_CAP_SPLIT_IRQCHIP:
	हाल KVM_CAP_IMMEDIATE_EXIT:
	हाल KVM_CAP_PMU_EVENT_FILTER:
	हाल KVM_CAP_GET_MSR_FEATURES:
	हाल KVM_CAP_MSR_PLATFORM_INFO:
	हाल KVM_CAP_EXCEPTION_PAYLOAD:
	हाल KVM_CAP_SET_GUEST_DEBUG:
	हाल KVM_CAP_LAST_CPU:
	हाल KVM_CAP_X86_USER_SPACE_MSR:
	हाल KVM_CAP_X86_MSR_FILTER:
	हाल KVM_CAP_ENFORCE_PV_FEATURE_CPUID:
#अगर_घोषित CONFIG_X86_SGX_KVM
	हाल KVM_CAP_SGX_ATTRIBUTE:
#पूर्ण_अगर
	हाल KVM_CAP_VM_COPY_ENC_CONTEXT_FROM:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SET_GUEST_DEBUG2:
		वापस KVM_GUESTDBG_VALID_MASK;
#अगर_घोषित CONFIG_KVM_XEN
	हाल KVM_CAP_XEN_HVM:
		r = KVM_XEN_HVM_CONFIG_HYPERCALL_MSR |
		    KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL |
		    KVM_XEN_HVM_CONFIG_SHARED_INFO;
		अगर (sched_info_on())
			r |= KVM_XEN_HVM_CONFIG_RUNSTATE;
		अवरोध;
#पूर्ण_अगर
	हाल KVM_CAP_SYNC_REGS:
		r = KVM_SYNC_X86_VALID_FIELDS;
		अवरोध;
	हाल KVM_CAP_ADJUST_CLOCK:
		r = KVM_CLOCK_TSC_STABLE;
		अवरोध;
	हाल KVM_CAP_X86_DISABLE_EXITS:
		r |=  KVM_X86_DISABLE_EXITS_HLT | KVM_X86_DISABLE_EXITS_PAUSE |
		      KVM_X86_DISABLE_EXITS_CSTATE;
		अगर(kvm_can_mरुको_in_guest())
			r |= KVM_X86_DISABLE_EXITS_MWAIT;
		अवरोध;
	हाल KVM_CAP_X86_SMM:
		/* SMBASE is usually relocated above 1M on modern chipsets,
		 * and SMM handlers might indeed rely on 4G segment limits,
		 * so करो not report SMM to be available अगर real mode is
		 * emulated via vm86 mode.  Still, करो not go to great lengths
		 * to aव्योम userspace's usage of the feature, because it is a
		 * fringe हाल that is not enabled except via specअगरic settings
		 * of the module parameters.
		 */
		r = अटल_call(kvm_x86_has_emulated_msr)(kvm, MSR_IA32_SMBASE);
		अवरोध;
	हाल KVM_CAP_VAPIC:
		r = !अटल_call(kvm_x86_cpu_has_accelerated_tpr)();
		अवरोध;
	हाल KVM_CAP_NR_VCPUS:
		r = KVM_SOFT_MAX_VCPUS;
		अवरोध;
	हाल KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		अवरोध;
	हाल KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		अवरोध;
	हाल KVM_CAP_PV_MMU:	/* obsolete */
		r = 0;
		अवरोध;
	हाल KVM_CAP_MCE:
		r = KVM_MAX_MCE_BANKS;
		अवरोध;
	हाल KVM_CAP_XCRS:
		r = boot_cpu_has(X86_FEATURE_XSAVE);
		अवरोध;
	हाल KVM_CAP_TSC_CONTROL:
		r = kvm_has_tsc_control;
		अवरोध;
	हाल KVM_CAP_X2APIC_API:
		r = KVM_X2APIC_API_VALID_FLAGS;
		अवरोध;
	हाल KVM_CAP_NESTED_STATE:
		r = kvm_x86_ops.nested_ops->get_state ?
			kvm_x86_ops.nested_ops->get_state(शून्य, शून्य, 0) : 0;
		अवरोध;
	हाल KVM_CAP_HYPERV_सूचीECT_TLBFLUSH:
		r = kvm_x86_ops.enable_direct_tlbflush != शून्य;
		अवरोध;
	हाल KVM_CAP_HYPERV_ENLIGHTENED_VMCS:
		r = kvm_x86_ops.nested_ops->enable_evmcs != शून्य;
		अवरोध;
	हाल KVM_CAP_SMALLER_MAXPHYADDR:
		r = (पूर्णांक) allow_smaller_maxphyaddr;
		अवरोध;
	हाल KVM_CAP_STEAL_TIME:
		r = sched_info_on();
		अवरोध;
	हाल KVM_CAP_X86_BUS_LOCK_EXIT:
		अगर (kvm_has_bus_lock_निकास)
			r = KVM_BUS_LOCK_DETECTION_OFF |
			    KVM_BUS_LOCK_DETECTION_EXIT;
		अन्यथा
			r = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस r;

पूर्ण

दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp,
			अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ r;

	चयन (ioctl) अणु
	हाल KVM_GET_MSR_INDEX_LIST: अणु
		काष्ठा kvm_msr_list __user *user_msr_list = argp;
		काष्ठा kvm_msr_list msr_list;
		अचिन्हित n;

		r = -EFAULT;
		अगर (copy_from_user(&msr_list, user_msr_list, माप(msr_list)))
			जाओ out;
		n = msr_list.nmsrs;
		msr_list.nmsrs = num_msrs_to_save + num_emulated_msrs;
		अगर (copy_to_user(user_msr_list, &msr_list, माप(msr_list)))
			जाओ out;
		r = -E2BIG;
		अगर (n < msr_list.nmsrs)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(user_msr_list->indices, &msrs_to_save,
				 num_msrs_to_save * माप(u32)))
			जाओ out;
		अगर (copy_to_user(user_msr_list->indices + num_msrs_to_save,
				 &emulated_msrs,
				 num_emulated_msrs * माप(u32)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_GET_SUPPORTED_CPUID:
	हाल KVM_GET_EMULATED_CPUID: अणु
		काष्ठा kvm_cpuid2 __user *cpuid_arg = argp;
		काष्ठा kvm_cpuid2 cpuid;

		r = -EFAULT;
		अगर (copy_from_user(&cpuid, cpuid_arg, माप(cpuid)))
			जाओ out;

		r = kvm_dev_ioctl_get_cpuid(&cpuid, cpuid_arg->entries,
					    ioctl);
		अगर (r)
			जाओ out;

		r = -EFAULT;
		अगर (copy_to_user(cpuid_arg, &cpuid, माप(cpuid)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_X86_GET_MCE_CAP_SUPPORTED:
		r = -EFAULT;
		अगर (copy_to_user(argp, &kvm_mce_cap_supported,
				 माप(kvm_mce_cap_supported)))
			जाओ out;
		r = 0;
		अवरोध;
	हाल KVM_GET_MSR_FEATURE_INDEX_LIST: अणु
		काष्ठा kvm_msr_list __user *user_msr_list = argp;
		काष्ठा kvm_msr_list msr_list;
		अचिन्हित पूर्णांक n;

		r = -EFAULT;
		अगर (copy_from_user(&msr_list, user_msr_list, माप(msr_list)))
			जाओ out;
		n = msr_list.nmsrs;
		msr_list.nmsrs = num_msr_based_features;
		अगर (copy_to_user(user_msr_list, &msr_list, माप(msr_list)))
			जाओ out;
		r = -E2BIG;
		अगर (n < msr_list.nmsrs)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(user_msr_list->indices, &msr_based_features,
				 num_msr_based_features * माप(u32)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_GET_MSRS:
		r = msr_io(शून्य, argp, करो_get_msr_feature, 1);
		अवरोध;
	हाल KVM_GET_SUPPORTED_HV_CPUID:
		r = kvm_ioctl_get_supported_hv_cpuid(शून्य, argp);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
out:
	वापस r;
पूर्ण

अटल व्योम wbinvd_ipi(व्योम *garbage)
अणु
	wbinvd();
पूर्ण

अटल bool need_emulate_wbinvd(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_arch_has_noncoherent_dma(vcpu->kvm);
पूर्ण

व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	/* Address WBINVD may be executed by guest */
	अगर (need_emulate_wbinvd(vcpu)) अणु
		अगर (अटल_call(kvm_x86_has_wbinvd_निकास)())
			cpumask_set_cpu(cpu, vcpu->arch.wbinvd_dirty_mask);
		अन्यथा अगर (vcpu->cpu != -1 && vcpu->cpu != cpu)
			smp_call_function_single(vcpu->cpu,
					wbinvd_ipi, शून्य, 1);
	पूर्ण

	अटल_call(kvm_x86_vcpu_load)(vcpu, cpu);

	/* Save host pkru रेजिस्टर अगर supported */
	vcpu->arch.host_pkru = पढ़ो_pkru();

	/* Apply any बाह्यally detected TSC adjusपंचांगents (due to suspend) */
	अगर (unlikely(vcpu->arch.tsc_offset_adjusपंचांगent)) अणु
		adjust_tsc_offset_host(vcpu, vcpu->arch.tsc_offset_adjusपंचांगent);
		vcpu->arch.tsc_offset_adjusपंचांगent = 0;
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
	पूर्ण

	अगर (unlikely(vcpu->cpu != cpu) || kvm_check_tsc_unstable()) अणु
		s64 tsc_delta = !vcpu->arch.last_host_tsc ? 0 :
				rdtsc() - vcpu->arch.last_host_tsc;
		अगर (tsc_delta < 0)
			mark_tsc_unstable("KVM discovered backwards TSC");

		अगर (kvm_check_tsc_unstable()) अणु
			u64 offset = kvm_compute_tsc_offset(vcpu,
						vcpu->arch.last_guest_tsc);
			kvm_vcpu_ग_लिखो_tsc_offset(vcpu, offset);
			vcpu->arch.tsc_catchup = 1;
		पूर्ण

		अगर (kvm_lapic_hv_समयr_in_use(vcpu))
			kvm_lapic_restart_hv_समयr(vcpu);

		/*
		 * On a host with synchronized TSC, there is no need to update
		 * kvmघड़ी on vcpu->cpu migration
		 */
		अगर (!vcpu->kvm->arch.use_master_घड़ी || vcpu->cpu == -1)
			kvm_make_request(KVM_REQ_GLOBAL_CLOCK_UPDATE, vcpu);
		अगर (vcpu->cpu != cpu)
			kvm_make_request(KVM_REQ_MIGRATE_TIMER, vcpu);
		vcpu->cpu = cpu;
	पूर्ण

	kvm_make_request(KVM_REQ_STEAL_UPDATE, vcpu);
पूर्ण

अटल व्योम kvm_steal_समय_set_preempted(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_host_map map;
	काष्ठा kvm_steal_समय *st;

	अगर (!(vcpu->arch.st.msr_val & KVM_MSR_ENABLED))
		वापस;

	अगर (vcpu->arch.st.preempted)
		वापस;

	अगर (kvm_map_gfn(vcpu, vcpu->arch.st.msr_val >> PAGE_SHIFT, &map,
			&vcpu->arch.st.cache, true))
		वापस;

	st = map.hva +
		offset_in_page(vcpu->arch.st.msr_val & KVM_STEAL_VALID_BITS);

	st->preempted = vcpu->arch.st.preempted = KVM_VCPU_PREEMPTED;

	kvm_unmap_gfn(vcpu, &map, &vcpu->arch.st.cache, true, true);
पूर्ण

व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक idx;

	अगर (vcpu->preempted && !vcpu->arch.guest_state_रक्षित)
		vcpu->arch.preempted_in_kernel = !अटल_call(kvm_x86_get_cpl)(vcpu);

	/*
	 * Take the srcu lock as memslots will be accessed to check the gfn
	 * cache generation against the memslots generation.
	 */
	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	अगर (kvm_xen_msr_enabled(vcpu->kvm))
		kvm_xen_runstate_set_preempted(vcpu);
	अन्यथा
		kvm_steal_समय_set_preempted(vcpu);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	अटल_call(kvm_x86_vcpu_put)(vcpu);
	vcpu->arch.last_host_tsc = rdtsc();
	/*
	 * If userspace has set any अवरोधpoपूर्णांकs or watchpoपूर्णांकs, dr6 is restored
	 * on every vmनिकास, but अगर not, we might have a stale dr6 from the
	 * guest. करो_debug expects dr6 to be cleared after it runs, करो the same.
	 */
	set_debugreg(0, 6);
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_get_lapic(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_lapic_state *s)
अणु
	अगर (vcpu->arch.apicv_active)
		अटल_call(kvm_x86_sync_pir_to_irr)(vcpu);

	वापस kvm_apic_get_state(vcpu, s);
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_set_lapic(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_lapic_state *s)
अणु
	पूर्णांक r;

	r = kvm_apic_set_state(vcpu, s);
	अगर (r)
		वापस r;
	update_cr8_पूर्णांकercept(vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_cpu_accept_dm_पूर्णांकr(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * We can accept userspace's request क्रम पूर्णांकerrupt injection
	 * as दीर्घ as we have a place to store the पूर्णांकerrupt number.
	 * The actual injection will happen when the CPU is able to
	 * deliver the पूर्णांकerrupt.
	 */
	अगर (kvm_cpu_has_extपूर्णांक(vcpu))
		वापस false;

	/* Acknowledging ExtINT करोes not happen अगर LINT0 is masked.  */
	वापस (!lapic_in_kernel(vcpu) ||
		kvm_apic_accept_pic_पूर्णांकr(vcpu));
पूर्ण

अटल पूर्णांक kvm_vcpu_पढ़ोy_क्रम_पूर्णांकerrupt_injection(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_arch_पूर्णांकerrupt_allowed(vcpu) &&
		kvm_cpu_accept_dm_पूर्णांकr(vcpu);
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_पूर्णांकerrupt *irq)
अणु
	अगर (irq->irq >= KVM_NR_INTERRUPTS)
		वापस -EINVAL;

	अगर (!irqchip_in_kernel(vcpu->kvm)) अणु
		kvm_queue_पूर्णांकerrupt(vcpu, irq->irq, false);
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		वापस 0;
	पूर्ण

	/*
	 * With in-kernel LAPIC, we only use this to inject EXTINT, so
	 * fail क्रम in-kernel 8259.
	 */
	अगर (pic_in_kernel(vcpu->kvm))
		वापस -ENXIO;

	अगर (vcpu->arch.pending_बाह्यal_vector != -1)
		वापस -EEXIST;

	vcpu->arch.pending_बाह्यal_vector = irq->irq;
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_inject_nmi(vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_smi(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_make_request(KVM_REQ_SMI, vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक vcpu_ioctl_tpr_access_reporting(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा kvm_tpr_access_ctl *tac)
अणु
	अगर (tac->flags)
		वापस -EINVAL;
	vcpu->arch.tpr_access_reporting = !!tac->enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_x86_setup_mce(काष्ठा kvm_vcpu *vcpu,
					u64 mcg_cap)
अणु
	पूर्णांक r;
	अचिन्हित bank_num = mcg_cap & 0xff, bank;

	r = -EINVAL;
	अगर (!bank_num || bank_num > KVM_MAX_MCE_BANKS)
		जाओ out;
	अगर (mcg_cap & ~(kvm_mce_cap_supported | 0xff | 0xff0000))
		जाओ out;
	r = 0;
	vcpu->arch.mcg_cap = mcg_cap;
	/* Init IA32_MCG_CTL to all 1s */
	अगर (mcg_cap & MCG_CTL_P)
		vcpu->arch.mcg_ctl = ~(u64)0;
	/* Init IA32_MCi_CTL to all 1s */
	क्रम (bank = 0; bank < bank_num; bank++)
		vcpu->arch.mce_banks[bank*4] = ~(u64)0;

	अटल_call(kvm_x86_setup_mce)(vcpu);
out:
	वापस r;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_x86_set_mce(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_x86_mce *mce)
अणु
	u64 mcg_cap = vcpu->arch.mcg_cap;
	अचिन्हित bank_num = mcg_cap & 0xff;
	u64 *banks = vcpu->arch.mce_banks;

	अगर (mce->bank >= bank_num || !(mce->status & MCI_STATUS_VAL))
		वापस -EINVAL;
	/*
	 * अगर IA32_MCG_CTL is not all 1s, the uncorrected error
	 * reporting is disabled
	 */
	अगर ((mce->status & MCI_STATUS_UC) && (mcg_cap & MCG_CTL_P) &&
	    vcpu->arch.mcg_ctl != ~(u64)0)
		वापस 0;
	banks += 4 * mce->bank;
	/*
	 * अगर IA32_MCi_CTL is not all 1s, the uncorrected error
	 * reporting is disabled क्रम the bank
	 */
	अगर ((mce->status & MCI_STATUS_UC) && banks[0] != ~(u64)0)
		वापस 0;
	अगर (mce->status & MCI_STATUS_UC) अणु
		अगर ((vcpu->arch.mcg_status & MCG_STATUS_MCIP) ||
		    !kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_MCE)) अणु
			kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
			वापस 0;
		पूर्ण
		अगर (banks[1] & MCI_STATUS_VAL)
			mce->status |= MCI_STATUS_OVER;
		banks[2] = mce->addr;
		banks[3] = mce->misc;
		vcpu->arch.mcg_status = mce->mcg_status;
		banks[1] = mce->status;
		kvm_queue_exception(vcpu, MC_VECTOR);
	पूर्ण अन्यथा अगर (!(banks[1] & MCI_STATUS_VAL)
		   || !(banks[1] & MCI_STATUS_UC)) अणु
		अगर (banks[1] & MCI_STATUS_VAL)
			mce->status |= MCI_STATUS_OVER;
		banks[2] = mce->addr;
		banks[3] = mce->misc;
		banks[1] = mce->status;
	पूर्ण अन्यथा
		banks[1] |= MCI_STATUS_OVER;
	वापस 0;
पूर्ण

अटल व्योम kvm_vcpu_ioctl_x86_get_vcpu_events(काष्ठा kvm_vcpu *vcpu,
					       काष्ठा kvm_vcpu_events *events)
अणु
	process_nmi(vcpu);

	अगर (kvm_check_request(KVM_REQ_SMI, vcpu))
		process_smi(vcpu);

	/*
	 * In guest mode, payload delivery should be deferred,
	 * so that the L1 hypervisor can पूर्णांकercept #PF beक्रमe
	 * CR2 is modअगरied (or पूर्णांकercept #DB beक्रमe DR6 is
	 * modअगरied under nVMX). Unless the per-VM capability,
	 * KVM_CAP_EXCEPTION_PAYLOAD, is set, we may not defer the delivery of
	 * an exception payload and handle after a KVM_GET_VCPU_EVENTS. Since we
	 * opportunistically defer the exception payload, deliver it अगर the
	 * capability hasn't been requested beक्रमe processing a
	 * KVM_GET_VCPU_EVENTS.
	 */
	अगर (!vcpu->kvm->arch.exception_payload_enabled &&
	    vcpu->arch.exception.pending && vcpu->arch.exception.has_payload)
		kvm_deliver_exception_payload(vcpu);

	/*
	 * The API करोesn't provide the inकाष्ठाion length क्रम software
	 * exceptions, so करोn't report them. As दीर्घ as the guest RIP
	 * isn't advanced, we should expect to encounter the exception
	 * again.
	 */
	अगर (kvm_exception_is_soft(vcpu->arch.exception.nr)) अणु
		events->exception.injected = 0;
		events->exception.pending = 0;
	पूर्ण अन्यथा अणु
		events->exception.injected = vcpu->arch.exception.injected;
		events->exception.pending = vcpu->arch.exception.pending;
		/*
		 * For ABI compatibility, deliberately conflate
		 * pending and injected exceptions when
		 * KVM_CAP_EXCEPTION_PAYLOAD isn't enabled.
		 */
		अगर (!vcpu->kvm->arch.exception_payload_enabled)
			events->exception.injected |=
				vcpu->arch.exception.pending;
	पूर्ण
	events->exception.nr = vcpu->arch.exception.nr;
	events->exception.has_error_code = vcpu->arch.exception.has_error_code;
	events->exception.error_code = vcpu->arch.exception.error_code;
	events->exception_has_payload = vcpu->arch.exception.has_payload;
	events->exception_payload = vcpu->arch.exception.payload;

	events->पूर्णांकerrupt.injected =
		vcpu->arch.पूर्णांकerrupt.injected && !vcpu->arch.पूर्णांकerrupt.soft;
	events->पूर्णांकerrupt.nr = vcpu->arch.पूर्णांकerrupt.nr;
	events->पूर्णांकerrupt.soft = 0;
	events->पूर्णांकerrupt.shaकरोw = अटल_call(kvm_x86_get_पूर्णांकerrupt_shaकरोw)(vcpu);

	events->nmi.injected = vcpu->arch.nmi_injected;
	events->nmi.pending = vcpu->arch.nmi_pending != 0;
	events->nmi.masked = अटल_call(kvm_x86_get_nmi_mask)(vcpu);
	events->nmi.pad = 0;

	events->sipi_vector = 0; /* never valid when reporting to user space */

	events->smi.smm = is_smm(vcpu);
	events->smi.pending = vcpu->arch.smi_pending;
	events->smi.smm_inside_nmi =
		!!(vcpu->arch.hflags & HF_SMM_INSIDE_NMI_MASK);
	events->smi.latched_init = kvm_lapic_latched_init(vcpu);

	events->flags = (KVM_VCPUEVENT_VALID_NMI_PENDING
			 | KVM_VCPUEVENT_VALID_SHADOW
			 | KVM_VCPUEVENT_VALID_SMM);
	अगर (vcpu->kvm->arch.exception_payload_enabled)
		events->flags |= KVM_VCPUEVENT_VALID_PAYLOAD;

	स_रखो(&events->reserved, 0, माप(events->reserved));
पूर्ण

अटल व्योम kvm_smm_changed(काष्ठा kvm_vcpu *vcpu);

अटल पूर्णांक kvm_vcpu_ioctl_x86_set_vcpu_events(काष्ठा kvm_vcpu *vcpu,
					      काष्ठा kvm_vcpu_events *events)
अणु
	अगर (events->flags & ~(KVM_VCPUEVENT_VALID_NMI_PENDING
			      | KVM_VCPUEVENT_VALID_SIPI_VECTOR
			      | KVM_VCPUEVENT_VALID_SHADOW
			      | KVM_VCPUEVENT_VALID_SMM
			      | KVM_VCPUEVENT_VALID_PAYLOAD))
		वापस -EINVAL;

	अगर (events->flags & KVM_VCPUEVENT_VALID_PAYLOAD) अणु
		अगर (!vcpu->kvm->arch.exception_payload_enabled)
			वापस -EINVAL;
		अगर (events->exception.pending)
			events->exception.injected = 0;
		अन्यथा
			events->exception_has_payload = 0;
	पूर्ण अन्यथा अणु
		events->exception.pending = 0;
		events->exception_has_payload = 0;
	पूर्ण

	अगर ((events->exception.injected || events->exception.pending) &&
	    (events->exception.nr > 31 || events->exception.nr == NMI_VECTOR))
		वापस -EINVAL;

	/* INITs are latched जबतक in SMM */
	अगर (events->flags & KVM_VCPUEVENT_VALID_SMM &&
	    (events->smi.smm || events->smi.pending) &&
	    vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED)
		वापस -EINVAL;

	process_nmi(vcpu);
	vcpu->arch.exception.injected = events->exception.injected;
	vcpu->arch.exception.pending = events->exception.pending;
	vcpu->arch.exception.nr = events->exception.nr;
	vcpu->arch.exception.has_error_code = events->exception.has_error_code;
	vcpu->arch.exception.error_code = events->exception.error_code;
	vcpu->arch.exception.has_payload = events->exception_has_payload;
	vcpu->arch.exception.payload = events->exception_payload;

	vcpu->arch.पूर्णांकerrupt.injected = events->पूर्णांकerrupt.injected;
	vcpu->arch.पूर्णांकerrupt.nr = events->पूर्णांकerrupt.nr;
	vcpu->arch.पूर्णांकerrupt.soft = events->पूर्णांकerrupt.soft;
	अगर (events->flags & KVM_VCPUEVENT_VALID_SHADOW)
		अटल_call(kvm_x86_set_पूर्णांकerrupt_shaकरोw)(vcpu,
						events->पूर्णांकerrupt.shaकरोw);

	vcpu->arch.nmi_injected = events->nmi.injected;
	अगर (events->flags & KVM_VCPUEVENT_VALID_NMI_PENDING)
		vcpu->arch.nmi_pending = events->nmi.pending;
	अटल_call(kvm_x86_set_nmi_mask)(vcpu, events->nmi.masked);

	अगर (events->flags & KVM_VCPUEVENT_VALID_SIPI_VECTOR &&
	    lapic_in_kernel(vcpu))
		vcpu->arch.apic->sipi_vector = events->sipi_vector;

	अगर (events->flags & KVM_VCPUEVENT_VALID_SMM) अणु
		अगर (!!(vcpu->arch.hflags & HF_SMM_MASK) != events->smi.smm) अणु
			अगर (events->smi.smm)
				vcpu->arch.hflags |= HF_SMM_MASK;
			अन्यथा
				vcpu->arch.hflags &= ~HF_SMM_MASK;
			kvm_smm_changed(vcpu);
		पूर्ण

		vcpu->arch.smi_pending = events->smi.pending;

		अगर (events->smi.smm) अणु
			अगर (events->smi.smm_inside_nmi)
				vcpu->arch.hflags |= HF_SMM_INSIDE_NMI_MASK;
			अन्यथा
				vcpu->arch.hflags &= ~HF_SMM_INSIDE_NMI_MASK;
		पूर्ण

		अगर (lapic_in_kernel(vcpu)) अणु
			अगर (events->smi.latched_init)
				set_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
			अन्यथा
				clear_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
		पूर्ण
	पूर्ण

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	वापस 0;
पूर्ण

अटल व्योम kvm_vcpu_ioctl_x86_get_debugregs(काष्ठा kvm_vcpu *vcpu,
					     काष्ठा kvm_debugregs *dbgregs)
अणु
	अचिन्हित दीर्घ val;

	स_नकल(dbgregs->db, vcpu->arch.db, माप(vcpu->arch.db));
	kvm_get_dr(vcpu, 6, &val);
	dbgregs->dr6 = val;
	dbgregs->dr7 = vcpu->arch.dr7;
	dbgregs->flags = 0;
	स_रखो(&dbgregs->reserved, 0, माप(dbgregs->reserved));
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_x86_set_debugregs(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा kvm_debugregs *dbgregs)
अणु
	अगर (dbgregs->flags)
		वापस -EINVAL;

	अगर (!kvm_dr6_valid(dbgregs->dr6))
		वापस -EINVAL;
	अगर (!kvm_dr7_valid(dbgregs->dr7))
		वापस -EINVAL;

	स_नकल(vcpu->arch.db, dbgregs->db, माप(vcpu->arch.db));
	kvm_update_dr0123(vcpu);
	vcpu->arch.dr6 = dbgregs->dr6;
	vcpu->arch.dr7 = dbgregs->dr7;
	kvm_update_dr7(vcpu);

	वापस 0;
पूर्ण

#घोषणा XSTATE_COMPACTION_ENABLED (1ULL << 63)

अटल व्योम fill_xsave(u8 *dest, काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा xregs_state *xsave = &vcpu->arch.guest_fpu->state.xsave;
	u64 xstate_bv = xsave->header.xfeatures;
	u64 valid;

	/*
	 * Copy legacy XSAVE area, to aव्योम complications with CPUID
	 * leaves 0 and 1 in the loop below.
	 */
	स_नकल(dest, xsave, XSAVE_HDR_OFFSET);

	/* Set XSTATE_BV */
	xstate_bv &= vcpu->arch.guest_supported_xcr0 | XFEATURE_MASK_FPSSE;
	*(u64 *)(dest + XSAVE_HDR_OFFSET) = xstate_bv;

	/*
	 * Copy each region from the possibly compacted offset to the
	 * non-compacted offset.
	 */
	valid = xstate_bv & ~XFEATURE_MASK_FPSSE;
	जबतक (valid) अणु
		u64 xfeature_mask = valid & -valid;
		पूर्णांक xfeature_nr = fls64(xfeature_mask) - 1;
		व्योम *src = get_xsave_addr(xsave, xfeature_nr);

		अगर (src) अणु
			u32 size, offset, ecx, edx;
			cpuid_count(XSTATE_CPUID, xfeature_nr,
				    &size, &offset, &ecx, &edx);
			अगर (xfeature_nr == XFEATURE_PKRU)
				स_नकल(dest + offset, &vcpu->arch.pkru,
				       माप(vcpu->arch.pkru));
			अन्यथा
				स_नकल(dest + offset, src, size);

		पूर्ण

		valid -= xfeature_mask;
	पूर्ण
पूर्ण

अटल व्योम load_xsave(काष्ठा kvm_vcpu *vcpu, u8 *src)
अणु
	काष्ठा xregs_state *xsave = &vcpu->arch.guest_fpu->state.xsave;
	u64 xstate_bv = *(u64 *)(src + XSAVE_HDR_OFFSET);
	u64 valid;

	/*
	 * Copy legacy XSAVE area, to aव्योम complications with CPUID
	 * leaves 0 and 1 in the loop below.
	 */
	स_नकल(xsave, src, XSAVE_HDR_OFFSET);

	/* Set XSTATE_BV and possibly XCOMP_BV.  */
	xsave->header.xfeatures = xstate_bv;
	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		xsave->header.xcomp_bv = host_xcr0 | XSTATE_COMPACTION_ENABLED;

	/*
	 * Copy each region from the non-compacted offset to the
	 * possibly compacted offset.
	 */
	valid = xstate_bv & ~XFEATURE_MASK_FPSSE;
	जबतक (valid) अणु
		u64 xfeature_mask = valid & -valid;
		पूर्णांक xfeature_nr = fls64(xfeature_mask) - 1;
		व्योम *dest = get_xsave_addr(xsave, xfeature_nr);

		अगर (dest) अणु
			u32 size, offset, ecx, edx;
			cpuid_count(XSTATE_CPUID, xfeature_nr,
				    &size, &offset, &ecx, &edx);
			अगर (xfeature_nr == XFEATURE_PKRU)
				स_नकल(&vcpu->arch.pkru, src + offset,
				       माप(vcpu->arch.pkru));
			अन्यथा
				स_नकल(dest, src + offset, size);
		पूर्ण

		valid -= xfeature_mask;
	पूर्ण
पूर्ण

अटल व्योम kvm_vcpu_ioctl_x86_get_xsave(काष्ठा kvm_vcpu *vcpu,
					 काष्ठा kvm_xsave *guest_xsave)
अणु
	अगर (!vcpu->arch.guest_fpu)
		वापस;

	अगर (boot_cpu_has(X86_FEATURE_XSAVE)) अणु
		स_रखो(guest_xsave, 0, माप(काष्ठा kvm_xsave));
		fill_xsave((u8 *) guest_xsave->region, vcpu);
	पूर्ण अन्यथा अणु
		स_नकल(guest_xsave->region,
			&vcpu->arch.guest_fpu->state.fxsave,
			माप(काष्ठा fxregs_state));
		*(u64 *)&guest_xsave->region[XSAVE_HDR_OFFSET / माप(u32)] =
			XFEATURE_MASK_FPSSE;
	पूर्ण
पूर्ण

#घोषणा XSAVE_MXCSR_OFFSET 24

अटल पूर्णांक kvm_vcpu_ioctl_x86_set_xsave(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_xsave *guest_xsave)
अणु
	u64 xstate_bv;
	u32 mxcsr;

	अगर (!vcpu->arch.guest_fpu)
		वापस 0;

	xstate_bv = *(u64 *)&guest_xsave->region[XSAVE_HDR_OFFSET / माप(u32)];
	mxcsr = *(u32 *)&guest_xsave->region[XSAVE_MXCSR_OFFSET / माप(u32)];

	अगर (boot_cpu_has(X86_FEATURE_XSAVE)) अणु
		/*
		 * Here we allow setting states that are not present in
		 * CPUID leaf 0xD, index 0, EDX:EAX.  This is क्रम compatibility
		 * with old userspace.
		 */
		अगर (xstate_bv & ~supported_xcr0 || mxcsr & ~mxcsr_feature_mask)
			वापस -EINVAL;
		load_xsave(vcpu, (u8 *)guest_xsave->region);
	पूर्ण अन्यथा अणु
		अगर (xstate_bv & ~XFEATURE_MASK_FPSSE ||
			mxcsr & ~mxcsr_feature_mask)
			वापस -EINVAL;
		स_नकल(&vcpu->arch.guest_fpu->state.fxsave,
			guest_xsave->region, माप(काष्ठा fxregs_state));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kvm_vcpu_ioctl_x86_get_xcrs(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_xcrs *guest_xcrs)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_XSAVE)) अणु
		guest_xcrs->nr_xcrs = 0;
		वापस;
	पूर्ण

	guest_xcrs->nr_xcrs = 1;
	guest_xcrs->flags = 0;
	guest_xcrs->xcrs[0].xcr = XCR_XFEATURE_ENABLED_MASK;
	guest_xcrs->xcrs[0].value = vcpu->arch.xcr0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_x86_set_xcrs(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा kvm_xcrs *guest_xcrs)
अणु
	पूर्णांक i, r = 0;

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE))
		वापस -EINVAL;

	अगर (guest_xcrs->nr_xcrs > KVM_MAX_XCRS || guest_xcrs->flags)
		वापस -EINVAL;

	क्रम (i = 0; i < guest_xcrs->nr_xcrs; i++)
		/* Only support XCR0 currently */
		अगर (guest_xcrs->xcrs[i].xcr == XCR_XFEATURE_ENABLED_MASK) अणु
			r = __kvm_set_xcr(vcpu, XCR_XFEATURE_ENABLED_MASK,
				guest_xcrs->xcrs[i].value);
			अवरोध;
		पूर्ण
	अगर (r)
		r = -EINVAL;
	वापस r;
पूर्ण

/*
 * kvm_set_guest_छोड़ोd() indicates to the guest kernel that it has been
 * stopped by the hypervisor.  This function will be called from the host only.
 * EINVAL is वापसed when the host attempts to set the flag क्रम a guest that
 * करोes not support pv घड़ीs.
 */
अटल पूर्णांक kvm_set_guest_छोड़ोd(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->arch.pv_समय_enabled)
		वापस -EINVAL;
	vcpu->arch.pvघड़ी_set_guest_stopped_request = true;
	kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_enable_cap(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;
	uपूर्णांक16_t vmcs_version;
	व्योम __user *user_ptr;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_HYPERV_SYNIC2:
		अगर (cap->args[0])
			वापस -EINVAL;
		fallthrough;

	हाल KVM_CAP_HYPERV_SYNIC:
		अगर (!irqchip_in_kernel(vcpu->kvm))
			वापस -EINVAL;
		वापस kvm_hv_activate_synic(vcpu, cap->cap ==
					     KVM_CAP_HYPERV_SYNIC2);
	हाल KVM_CAP_HYPERV_ENLIGHTENED_VMCS:
		अगर (!kvm_x86_ops.nested_ops->enable_evmcs)
			वापस -ENOTTY;
		r = kvm_x86_ops.nested_ops->enable_evmcs(vcpu, &vmcs_version);
		अगर (!r) अणु
			user_ptr = (व्योम __user *)(uपूर्णांकptr_t)cap->args[0];
			अगर (copy_to_user(user_ptr, &vmcs_version,
					 माप(vmcs_version)))
				r = -EFAULT;
		पूर्ण
		वापस r;
	हाल KVM_CAP_HYPERV_सूचीECT_TLBFLUSH:
		अगर (!kvm_x86_ops.enable_direct_tlbflush)
			वापस -ENOTTY;

		वापस अटल_call(kvm_x86_enable_direct_tlbflush)(vcpu);

	हाल KVM_CAP_ENFORCE_PV_FEATURE_CPUID:
		vcpu->arch.pv_cpuid.enक्रमce = cap->args[0];
		अगर (vcpu->arch.pv_cpuid.enक्रमce)
			kvm_update_pv_runसमय(vcpu);

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp,
			 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक r;
	जोड़ अणु
		काष्ठा kvm_lapic_state *lapic;
		काष्ठा kvm_xsave *xsave;
		काष्ठा kvm_xcrs *xcrs;
		व्योम *buffer;
	पूर्ण u;

	vcpu_load(vcpu);

	u.buffer = शून्य;
	चयन (ioctl) अणु
	हाल KVM_GET_LAPIC: अणु
		r = -EINVAL;
		अगर (!lapic_in_kernel(vcpu))
			जाओ out;
		u.lapic = kzalloc(माप(काष्ठा kvm_lapic_state),
				GFP_KERNEL_ACCOUNT);

		r = -ENOMEM;
		अगर (!u.lapic)
			जाओ out;
		r = kvm_vcpu_ioctl_get_lapic(vcpu, u.lapic);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, u.lapic, माप(काष्ठा kvm_lapic_state)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_LAPIC: अणु
		r = -EINVAL;
		अगर (!lapic_in_kernel(vcpu))
			जाओ out;
		u.lapic = memdup_user(argp, माप(*u.lapic));
		अगर (IS_ERR(u.lapic)) अणु
			r = PTR_ERR(u.lapic);
			जाओ out_noमुक्त;
		पूर्ण

		r = kvm_vcpu_ioctl_set_lapic(vcpu, u.lapic);
		अवरोध;
	पूर्ण
	हाल KVM_INTERRUPT: अणु
		काष्ठा kvm_पूर्णांकerrupt irq;

		r = -EFAULT;
		अगर (copy_from_user(&irq, argp, माप(irq)))
			जाओ out;
		r = kvm_vcpu_ioctl_पूर्णांकerrupt(vcpu, &irq);
		अवरोध;
	पूर्ण
	हाल KVM_NMI: अणु
		r = kvm_vcpu_ioctl_nmi(vcpu);
		अवरोध;
	पूर्ण
	हाल KVM_SMI: अणु
		r = kvm_vcpu_ioctl_smi(vcpu);
		अवरोध;
	पूर्ण
	हाल KVM_SET_CPUID: अणु
		काष्ठा kvm_cpuid __user *cpuid_arg = argp;
		काष्ठा kvm_cpuid cpuid;

		r = -EFAULT;
		अगर (copy_from_user(&cpuid, cpuid_arg, माप(cpuid)))
			जाओ out;
		r = kvm_vcpu_ioctl_set_cpuid(vcpu, &cpuid, cpuid_arg->entries);
		अवरोध;
	पूर्ण
	हाल KVM_SET_CPUID2: अणु
		काष्ठा kvm_cpuid2 __user *cpuid_arg = argp;
		काष्ठा kvm_cpuid2 cpuid;

		r = -EFAULT;
		अगर (copy_from_user(&cpuid, cpuid_arg, माप(cpuid)))
			जाओ out;
		r = kvm_vcpu_ioctl_set_cpuid2(vcpu, &cpuid,
					      cpuid_arg->entries);
		अवरोध;
	पूर्ण
	हाल KVM_GET_CPUID2: अणु
		काष्ठा kvm_cpuid2 __user *cpuid_arg = argp;
		काष्ठा kvm_cpuid2 cpuid;

		r = -EFAULT;
		अगर (copy_from_user(&cpuid, cpuid_arg, माप(cpuid)))
			जाओ out;
		r = kvm_vcpu_ioctl_get_cpuid2(vcpu, &cpuid,
					      cpuid_arg->entries);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(cpuid_arg, &cpuid, माप(cpuid)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_GET_MSRS: अणु
		पूर्णांक idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = msr_io(vcpu, argp, करो_get_msr, 1);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण
	हाल KVM_SET_MSRS: अणु
		पूर्णांक idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = msr_io(vcpu, argp, करो_set_msr, 0);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण
	हाल KVM_TPR_ACCESS_REPORTING: अणु
		काष्ठा kvm_tpr_access_ctl tac;

		r = -EFAULT;
		अगर (copy_from_user(&tac, argp, माप(tac)))
			जाओ out;
		r = vcpu_ioctl_tpr_access_reporting(vcpu, &tac);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, &tac, माप(tac)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण;
	हाल KVM_SET_VAPIC_ADDR: अणु
		काष्ठा kvm_vapic_addr va;
		पूर्णांक idx;

		r = -EINVAL;
		अगर (!lapic_in_kernel(vcpu))
			जाओ out;
		r = -EFAULT;
		अगर (copy_from_user(&va, argp, माप(va)))
			जाओ out;
		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = kvm_lapic_set_vapic_addr(vcpu, va.vapic_addr);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण
	हाल KVM_X86_SETUP_MCE: अणु
		u64 mcg_cap;

		r = -EFAULT;
		अगर (copy_from_user(&mcg_cap, argp, माप(mcg_cap)))
			जाओ out;
		r = kvm_vcpu_ioctl_x86_setup_mce(vcpu, mcg_cap);
		अवरोध;
	पूर्ण
	हाल KVM_X86_SET_MCE: अणु
		काष्ठा kvm_x86_mce mce;

		r = -EFAULT;
		अगर (copy_from_user(&mce, argp, माप(mce)))
			जाओ out;
		r = kvm_vcpu_ioctl_x86_set_mce(vcpu, &mce);
		अवरोध;
	पूर्ण
	हाल KVM_GET_VCPU_EVENTS: अणु
		काष्ठा kvm_vcpu_events events;

		kvm_vcpu_ioctl_x86_get_vcpu_events(vcpu, &events);

		r = -EFAULT;
		अगर (copy_to_user(argp, &events, माप(काष्ठा kvm_vcpu_events)))
			अवरोध;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_VCPU_EVENTS: अणु
		काष्ठा kvm_vcpu_events events;

		r = -EFAULT;
		अगर (copy_from_user(&events, argp, माप(काष्ठा kvm_vcpu_events)))
			अवरोध;

		r = kvm_vcpu_ioctl_x86_set_vcpu_events(vcpu, &events);
		अवरोध;
	पूर्ण
	हाल KVM_GET_DEBUGREGS: अणु
		काष्ठा kvm_debugregs dbgregs;

		kvm_vcpu_ioctl_x86_get_debugregs(vcpu, &dbgregs);

		r = -EFAULT;
		अगर (copy_to_user(argp, &dbgregs,
				 माप(काष्ठा kvm_debugregs)))
			अवरोध;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_DEBUGREGS: अणु
		काष्ठा kvm_debugregs dbgregs;

		r = -EFAULT;
		अगर (copy_from_user(&dbgregs, argp,
				   माप(काष्ठा kvm_debugregs)))
			अवरोध;

		r = kvm_vcpu_ioctl_x86_set_debugregs(vcpu, &dbgregs);
		अवरोध;
	पूर्ण
	हाल KVM_GET_XSAVE: अणु
		u.xsave = kzalloc(माप(काष्ठा kvm_xsave), GFP_KERNEL_ACCOUNT);
		r = -ENOMEM;
		अगर (!u.xsave)
			अवरोध;

		kvm_vcpu_ioctl_x86_get_xsave(vcpu, u.xsave);

		r = -EFAULT;
		अगर (copy_to_user(argp, u.xsave, माप(काष्ठा kvm_xsave)))
			अवरोध;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_XSAVE: अणु
		u.xsave = memdup_user(argp, माप(*u.xsave));
		अगर (IS_ERR(u.xsave)) अणु
			r = PTR_ERR(u.xsave);
			जाओ out_noमुक्त;
		पूर्ण

		r = kvm_vcpu_ioctl_x86_set_xsave(vcpu, u.xsave);
		अवरोध;
	पूर्ण
	हाल KVM_GET_XCRS: अणु
		u.xcrs = kzalloc(माप(काष्ठा kvm_xcrs), GFP_KERNEL_ACCOUNT);
		r = -ENOMEM;
		अगर (!u.xcrs)
			अवरोध;

		kvm_vcpu_ioctl_x86_get_xcrs(vcpu, u.xcrs);

		r = -EFAULT;
		अगर (copy_to_user(argp, u.xcrs,
				 माप(काष्ठा kvm_xcrs)))
			अवरोध;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_XCRS: अणु
		u.xcrs = memdup_user(argp, माप(*u.xcrs));
		अगर (IS_ERR(u.xcrs)) अणु
			r = PTR_ERR(u.xcrs);
			जाओ out_noमुक्त;
		पूर्ण

		r = kvm_vcpu_ioctl_x86_set_xcrs(vcpu, u.xcrs);
		अवरोध;
	पूर्ण
	हाल KVM_SET_TSC_KHZ: अणु
		u32 user_tsc_khz;

		r = -EINVAL;
		user_tsc_khz = (u32)arg;

		अगर (kvm_has_tsc_control &&
		    user_tsc_khz >= kvm_max_guest_tsc_khz)
			जाओ out;

		अगर (user_tsc_khz == 0)
			user_tsc_khz = tsc_khz;

		अगर (!kvm_set_tsc_khz(vcpu, user_tsc_khz))
			r = 0;

		जाओ out;
	पूर्ण
	हाल KVM_GET_TSC_KHZ: अणु
		r = vcpu->arch.भव_tsc_khz;
		जाओ out;
	पूर्ण
	हाल KVM_KVMCLOCK_CTRL: अणु
		r = kvm_set_guest_छोड़ोd(vcpu);
		जाओ out;
	पूर्ण
	हाल KVM_ENABLE_CAP: अणु
		काष्ठा kvm_enable_cap cap;

		r = -EFAULT;
		अगर (copy_from_user(&cap, argp, माप(cap)))
			जाओ out;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		अवरोध;
	पूर्ण
	हाल KVM_GET_NESTED_STATE: अणु
		काष्ठा kvm_nested_state __user *user_kvm_nested_state = argp;
		u32 user_data_size;

		r = -EINVAL;
		अगर (!kvm_x86_ops.nested_ops->get_state)
			अवरोध;

		BUILD_BUG_ON(माप(user_data_size) != माप(user_kvm_nested_state->size));
		r = -EFAULT;
		अगर (get_user(user_data_size, &user_kvm_nested_state->size))
			अवरोध;

		r = kvm_x86_ops.nested_ops->get_state(vcpu, user_kvm_nested_state,
						     user_data_size);
		अगर (r < 0)
			अवरोध;

		अगर (r > user_data_size) अणु
			अगर (put_user(r, &user_kvm_nested_state->size))
				r = -EFAULT;
			अन्यथा
				r = -E2BIG;
			अवरोध;
		पूर्ण

		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_NESTED_STATE: अणु
		काष्ठा kvm_nested_state __user *user_kvm_nested_state = argp;
		काष्ठा kvm_nested_state kvm_state;
		पूर्णांक idx;

		r = -EINVAL;
		अगर (!kvm_x86_ops.nested_ops->set_state)
			अवरोध;

		r = -EFAULT;
		अगर (copy_from_user(&kvm_state, user_kvm_nested_state, माप(kvm_state)))
			अवरोध;

		r = -EINVAL;
		अगर (kvm_state.size < माप(kvm_state))
			अवरोध;

		अगर (kvm_state.flags &
		    ~(KVM_STATE_NESTED_RUN_PENDING | KVM_STATE_NESTED_GUEST_MODE
		      | KVM_STATE_NESTED_EVMCS | KVM_STATE_NESTED_MTF_PENDING
		      | KVM_STATE_NESTED_GIF_SET))
			अवरोध;

		/* nested_run_pending implies guest_mode.  */
		अगर ((kvm_state.flags & KVM_STATE_NESTED_RUN_PENDING)
		    && !(kvm_state.flags & KVM_STATE_NESTED_GUEST_MODE))
			अवरोध;

		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = kvm_x86_ops.nested_ops->set_state(vcpu, user_kvm_nested_state, &kvm_state);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अवरोध;
	पूर्ण
	हाल KVM_GET_SUPPORTED_HV_CPUID:
		r = kvm_ioctl_get_supported_hv_cpuid(vcpu, argp);
		अवरोध;
#अगर_घोषित CONFIG_KVM_XEN
	हाल KVM_XEN_VCPU_GET_ATTR: अणु
		काष्ठा kvm_xen_vcpu_attr xva;

		r = -EFAULT;
		अगर (copy_from_user(&xva, argp, माप(xva)))
			जाओ out;
		r = kvm_xen_vcpu_get_attr(vcpu, &xva);
		अगर (!r && copy_to_user(argp, &xva, माप(xva)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_XEN_VCPU_SET_ATTR: अणु
		काष्ठा kvm_xen_vcpu_attr xva;

		r = -EFAULT;
		अगर (copy_from_user(&xva, argp, माप(xva)))
			जाओ out;
		r = kvm_xen_vcpu_set_attr(vcpu, &xva);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		r = -EINVAL;
	पूर्ण
out:
	kमुक्त(u.buffer);
out_noमुक्त:
	vcpu_put(vcpu);
	वापस r;
पूर्ण

vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_tss_addr(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret;

	अगर (addr > (अचिन्हित पूर्णांक)(-3 * PAGE_SIZE))
		वापस -EINVAL;
	ret = अटल_call(kvm_x86_set_tss_addr)(kvm, addr);
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_identity_map_addr(काष्ठा kvm *kvm,
					      u64 ident_addr)
अणु
	वापस अटल_call(kvm_x86_set_identity_map_addr)(kvm, ident_addr);
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_nr_mmu_pages(काष्ठा kvm *kvm,
					 अचिन्हित दीर्घ kvm_nr_mmu_pages)
अणु
	अगर (kvm_nr_mmu_pages < KVM_MIN_ALLOC_MMU_PAGES)
		वापस -EINVAL;

	mutex_lock(&kvm->slots_lock);

	kvm_mmu_change_mmu_pages(kvm, kvm_nr_mmu_pages);
	kvm->arch.n_requested_mmu_pages = kvm_nr_mmu_pages;

	mutex_unlock(&kvm->slots_lock);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ kvm_vm_ioctl_get_nr_mmu_pages(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.n_max_mmu_pages;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_get_irqchip(काष्ठा kvm *kvm, काष्ठा kvm_irqchip *chip)
अणु
	काष्ठा kvm_pic *pic = kvm->arch.vpic;
	पूर्णांक r;

	r = 0;
	चयन (chip->chip_id) अणु
	हाल KVM_IRQCHIP_PIC_MASTER:
		स_नकल(&chip->chip.pic, &pic->pics[0],
			माप(काष्ठा kvm_pic_state));
		अवरोध;
	हाल KVM_IRQCHIP_PIC_SLAVE:
		स_नकल(&chip->chip.pic, &pic->pics[1],
			माप(काष्ठा kvm_pic_state));
		अवरोध;
	हाल KVM_IRQCHIP_IOAPIC:
		kvm_get_ioapic(kvm, &chip->chip.ioapic);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_irqchip(काष्ठा kvm *kvm, काष्ठा kvm_irqchip *chip)
अणु
	काष्ठा kvm_pic *pic = kvm->arch.vpic;
	पूर्णांक r;

	r = 0;
	चयन (chip->chip_id) अणु
	हाल KVM_IRQCHIP_PIC_MASTER:
		spin_lock(&pic->lock);
		स_नकल(&pic->pics[0], &chip->chip.pic,
			माप(काष्ठा kvm_pic_state));
		spin_unlock(&pic->lock);
		अवरोध;
	हाल KVM_IRQCHIP_PIC_SLAVE:
		spin_lock(&pic->lock);
		स_नकल(&pic->pics[1], &chip->chip.pic,
			माप(काष्ठा kvm_pic_state));
		spin_unlock(&pic->lock);
		अवरोध;
	हाल KVM_IRQCHIP_IOAPIC:
		kvm_set_ioapic(kvm, &chip->chip.ioapic);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
	kvm_pic_update_irq(pic);
	वापस r;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_get_pit(काष्ठा kvm *kvm, काष्ठा kvm_pit_state *ps)
अणु
	काष्ठा kvm_kpit_state *kps = &kvm->arch.vpit->pit_state;

	BUILD_BUG_ON(माप(*ps) != माप(kps->channels));

	mutex_lock(&kps->lock);
	स_नकल(ps, &kps->channels, माप(*ps));
	mutex_unlock(&kps->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_pit(काष्ठा kvm *kvm, काष्ठा kvm_pit_state *ps)
अणु
	पूर्णांक i;
	काष्ठा kvm_pit *pit = kvm->arch.vpit;

	mutex_lock(&pit->pit_state.lock);
	स_नकल(&pit->pit_state.channels, ps, माप(*ps));
	क्रम (i = 0; i < 3; i++)
		kvm_pit_load_count(pit, i, ps->channels[i].count, 0);
	mutex_unlock(&pit->pit_state.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_get_pit2(काष्ठा kvm *kvm, काष्ठा kvm_pit_state2 *ps)
अणु
	mutex_lock(&kvm->arch.vpit->pit_state.lock);
	स_नकल(ps->channels, &kvm->arch.vpit->pit_state.channels,
		माप(ps->channels));
	ps->flags = kvm->arch.vpit->pit_state.flags;
	mutex_unlock(&kvm->arch.vpit->pit_state.lock);
	स_रखो(&ps->reserved, 0, माप(ps->reserved));
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_pit2(काष्ठा kvm *kvm, काष्ठा kvm_pit_state2 *ps)
अणु
	पूर्णांक start = 0;
	पूर्णांक i;
	u32 prev_legacy, cur_legacy;
	काष्ठा kvm_pit *pit = kvm->arch.vpit;

	mutex_lock(&pit->pit_state.lock);
	prev_legacy = pit->pit_state.flags & KVM_PIT_FLAGS_HPET_LEGACY;
	cur_legacy = ps->flags & KVM_PIT_FLAGS_HPET_LEGACY;
	अगर (!prev_legacy && cur_legacy)
		start = 1;
	स_नकल(&pit->pit_state.channels, &ps->channels,
	       माप(pit->pit_state.channels));
	pit->pit_state.flags = ps->flags;
	क्रम (i = 0; i < 3; i++)
		kvm_pit_load_count(pit, i, pit->pit_state.channels[i].count,
				   start && i == 0);
	mutex_unlock(&pit->pit_state.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_reinject(काष्ठा kvm *kvm,
				 काष्ठा kvm_reinject_control *control)
अणु
	काष्ठा kvm_pit *pit = kvm->arch.vpit;

	/* pit->pit_state.lock was overloaded to prevent userspace from getting
	 * an inconsistent state after running multiple KVM_REINJECT_CONTROL
	 * ioctls in parallel.  Use a separate lock अगर that ioctl isn't rare.
	 */
	mutex_lock(&pit->pit_state.lock);
	kvm_pit_set_reinject(pit, control->pit_reinject);
	mutex_unlock(&pit->pit_state.lock);

	वापस 0;
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु

	/*
	 * Flush all CPUs' dirty log buffers to the  dirty_biपंचांगap.  Called
	 * beक्रमe reporting dirty_biपंचांगap to userspace.  KVM flushes the buffers
	 * on all VM-Exits, thus we only need to kick running vCPUs to क्रमce a
	 * VM-Exit.
	 */
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vcpu_kick(vcpu);
पूर्ण

पूर्णांक kvm_vm_ioctl_irq_line(काष्ठा kvm *kvm, काष्ठा kvm_irq_level *irq_event,
			bool line_status)
अणु
	अगर (!irqchip_in_kernel(kvm))
		वापस -ENXIO;

	irq_event->status = kvm_set_irq(kvm, KVM_USERSPACE_IRQ_SOURCE_ID,
					irq_event->irq, irq_event->level,
					line_status);
	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm,
			    काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_DISABLE_QUIRKS:
		kvm->arch.disabled_quirks = cap->args[0];
		r = 0;
		अवरोध;
	हाल KVM_CAP_SPLIT_IRQCHIP: अणु
		mutex_lock(&kvm->lock);
		r = -EINVAL;
		अगर (cap->args[0] > MAX_NR_RESERVED_IOAPIC_PINS)
			जाओ split_irqchip_unlock;
		r = -EEXIST;
		अगर (irqchip_in_kernel(kvm))
			जाओ split_irqchip_unlock;
		अगर (kvm->created_vcpus)
			जाओ split_irqchip_unlock;
		r = kvm_setup_empty_irq_routing(kvm);
		अगर (r)
			जाओ split_irqchip_unlock;
		/* Pairs with irqchip_in_kernel. */
		smp_wmb();
		kvm->arch.irqchip_mode = KVM_IRQCHIP_SPLIT;
		kvm->arch.nr_reserved_ioapic_pins = cap->args[0];
		r = 0;
split_irqchip_unlock:
		mutex_unlock(&kvm->lock);
		अवरोध;
	पूर्ण
	हाल KVM_CAP_X2APIC_API:
		r = -EINVAL;
		अगर (cap->args[0] & ~KVM_X2APIC_API_VALID_FLAGS)
			अवरोध;

		अगर (cap->args[0] & KVM_X2APIC_API_USE_32BIT_IDS)
			kvm->arch.x2apic_क्रमmat = true;
		अगर (cap->args[0] & KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK)
			kvm->arch.x2apic_broadcast_quirk_disabled = true;

		r = 0;
		अवरोध;
	हाल KVM_CAP_X86_DISABLE_EXITS:
		r = -EINVAL;
		अगर (cap->args[0] & ~KVM_X86_DISABLE_VALID_EXITS)
			अवरोध;

		अगर ((cap->args[0] & KVM_X86_DISABLE_EXITS_MWAIT) &&
			kvm_can_mरुको_in_guest())
			kvm->arch.mरुको_in_guest = true;
		अगर (cap->args[0] & KVM_X86_DISABLE_EXITS_HLT)
			kvm->arch.hlt_in_guest = true;
		अगर (cap->args[0] & KVM_X86_DISABLE_EXITS_PAUSE)
			kvm->arch.छोड़ो_in_guest = true;
		अगर (cap->args[0] & KVM_X86_DISABLE_EXITS_CSTATE)
			kvm->arch.cstate_in_guest = true;
		r = 0;
		अवरोध;
	हाल KVM_CAP_MSR_PLATFORM_INFO:
		kvm->arch.guest_can_पढ़ो_msr_platक्रमm_info = cap->args[0];
		r = 0;
		अवरोध;
	हाल KVM_CAP_EXCEPTION_PAYLOAD:
		kvm->arch.exception_payload_enabled = cap->args[0];
		r = 0;
		अवरोध;
	हाल KVM_CAP_X86_USER_SPACE_MSR:
		kvm->arch.user_space_msr_mask = cap->args[0];
		r = 0;
		अवरोध;
	हाल KVM_CAP_X86_BUS_LOCK_EXIT:
		r = -EINVAL;
		अगर (cap->args[0] & ~KVM_BUS_LOCK_DETECTION_VALID_MODE)
			अवरोध;

		अगर ((cap->args[0] & KVM_BUS_LOCK_DETECTION_OFF) &&
		    (cap->args[0] & KVM_BUS_LOCK_DETECTION_EXIT))
			अवरोध;

		अगर (kvm_has_bus_lock_निकास &&
		    cap->args[0] & KVM_BUS_LOCK_DETECTION_EXIT)
			kvm->arch.bus_lock_detection_enabled = true;
		r = 0;
		अवरोध;
#अगर_घोषित CONFIG_X86_SGX_KVM
	हाल KVM_CAP_SGX_ATTRIBUTE: अणु
		अचिन्हित दीर्घ allowed_attributes = 0;

		r = sgx_set_attribute(&allowed_attributes, cap->args[0]);
		अगर (r)
			अवरोध;

		/* KVM only supports the PROVISIONKEY privileged attribute. */
		अगर ((allowed_attributes & SGX_ATTR_PROVISIONKEY) &&
		    !(allowed_attributes & ~SGX_ATTR_PROVISIONKEY))
			kvm->arch.sgx_provisioning_allowed = true;
		अन्यथा
			r = -EINVAL;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_CAP_VM_COPY_ENC_CONTEXT_FROM:
		r = -EINVAL;
		अगर (kvm_x86_ops.vm_copy_enc_context_from)
			r = kvm_x86_ops.vm_copy_enc_context_from(kvm, cap->args[0]);
		वापस r;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल काष्ठा kvm_x86_msr_filter *kvm_alloc_msr_filter(bool शेष_allow)
अणु
	काष्ठा kvm_x86_msr_filter *msr_filter;

	msr_filter = kzalloc(माप(*msr_filter), GFP_KERNEL_ACCOUNT);
	अगर (!msr_filter)
		वापस शून्य;

	msr_filter->शेष_allow = शेष_allow;
	वापस msr_filter;
पूर्ण

अटल व्योम kvm_मुक्त_msr_filter(काष्ठा kvm_x86_msr_filter *msr_filter)
अणु
	u32 i;

	अगर (!msr_filter)
		वापस;

	क्रम (i = 0; i < msr_filter->count; i++)
		kमुक्त(msr_filter->ranges[i].biपंचांगap);

	kमुक्त(msr_filter);
पूर्ण

अटल पूर्णांक kvm_add_msr_filter(काष्ठा kvm_x86_msr_filter *msr_filter,
			      काष्ठा kvm_msr_filter_range *user_range)
अणु
	अचिन्हित दीर्घ *biपंचांगap = शून्य;
	माप_प्रकार biपंचांगap_size;

	अगर (!user_range->nmsrs)
		वापस 0;

	अगर (user_range->flags & ~(KVM_MSR_FILTER_READ | KVM_MSR_FILTER_WRITE))
		वापस -EINVAL;

	अगर (!user_range->flags)
		वापस -EINVAL;

	biपंचांगap_size = BITS_TO_LONGS(user_range->nmsrs) * माप(दीर्घ);
	अगर (!biपंचांगap_size || biपंचांगap_size > KVM_MSR_FILTER_MAX_BITMAP_SIZE)
		वापस -EINVAL;

	biपंचांगap = memdup_user((__user u8*)user_range->biपंचांगap, biपंचांगap_size);
	अगर (IS_ERR(biपंचांगap))
		वापस PTR_ERR(biपंचांगap);

	msr_filter->ranges[msr_filter->count] = (काष्ठा msr_biपंचांगap_range) अणु
		.flags = user_range->flags,
		.base = user_range->base,
		.nmsrs = user_range->nmsrs,
		.biपंचांगap = biपंचांगap,
	पूर्ण;

	msr_filter->count++;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_msr_filter(काष्ठा kvm *kvm, व्योम __user *argp)
अणु
	काष्ठा kvm_msr_filter __user *user_msr_filter = argp;
	काष्ठा kvm_x86_msr_filter *new_filter, *old_filter;
	काष्ठा kvm_msr_filter filter;
	bool शेष_allow;
	bool empty = true;
	पूर्णांक r = 0;
	u32 i;

	अगर (copy_from_user(&filter, user_msr_filter, माप(filter)))
		वापस -EFAULT;

	क्रम (i = 0; i < ARRAY_SIZE(filter.ranges); i++)
		empty &= !filter.ranges[i].nmsrs;

	शेष_allow = !(filter.flags & KVM_MSR_FILTER_DEFAULT_DENY);
	अगर (empty && !शेष_allow)
		वापस -EINVAL;

	new_filter = kvm_alloc_msr_filter(शेष_allow);
	अगर (!new_filter)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(filter.ranges); i++) अणु
		r = kvm_add_msr_filter(new_filter, &filter.ranges[i]);
		अगर (r) अणु
			kvm_मुक्त_msr_filter(new_filter);
			वापस r;
		पूर्ण
	पूर्ण

	mutex_lock(&kvm->lock);

	/* The per-VM filter is रक्षित by kvm->lock... */
	old_filter = srcu_dereference_check(kvm->arch.msr_filter, &kvm->srcu, 1);

	rcu_assign_poपूर्णांकer(kvm->arch.msr_filter, new_filter);
	synchronize_srcu(&kvm->srcu);

	kvm_मुक्त_msr_filter(old_filter);

	kvm_make_all_cpus_request(kvm, KVM_REQ_MSR_FILTER_CHANGED);
	mutex_unlock(&kvm->lock);

	वापस 0;
पूर्ण

दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp,
		       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक r = -ENOTTY;
	/*
	 * This जोड़ makes it completely explicit to gcc-3.x
	 * that these two variables' stack usage should be
	 * combined, not added together.
	 */
	जोड़ अणु
		काष्ठा kvm_pit_state ps;
		काष्ठा kvm_pit_state2 ps2;
		काष्ठा kvm_pit_config pit_config;
	पूर्ण u;

	चयन (ioctl) अणु
	हाल KVM_SET_TSS_ADDR:
		r = kvm_vm_ioctl_set_tss_addr(kvm, arg);
		अवरोध;
	हाल KVM_SET_IDENTITY_MAP_ADDR: अणु
		u64 ident_addr;

		mutex_lock(&kvm->lock);
		r = -EINVAL;
		अगर (kvm->created_vcpus)
			जाओ set_identity_unlock;
		r = -EFAULT;
		अगर (copy_from_user(&ident_addr, argp, माप(ident_addr)))
			जाओ set_identity_unlock;
		r = kvm_vm_ioctl_set_identity_map_addr(kvm, ident_addr);
set_identity_unlock:
		mutex_unlock(&kvm->lock);
		अवरोध;
	पूर्ण
	हाल KVM_SET_NR_MMU_PAGES:
		r = kvm_vm_ioctl_set_nr_mmu_pages(kvm, arg);
		अवरोध;
	हाल KVM_GET_NR_MMU_PAGES:
		r = kvm_vm_ioctl_get_nr_mmu_pages(kvm);
		अवरोध;
	हाल KVM_CREATE_IRQCHIP: अणु
		mutex_lock(&kvm->lock);

		r = -EEXIST;
		अगर (irqchip_in_kernel(kvm))
			जाओ create_irqchip_unlock;

		r = -EINVAL;
		अगर (kvm->created_vcpus)
			जाओ create_irqchip_unlock;

		r = kvm_pic_init(kvm);
		अगर (r)
			जाओ create_irqchip_unlock;

		r = kvm_ioapic_init(kvm);
		अगर (r) अणु
			kvm_pic_destroy(kvm);
			जाओ create_irqchip_unlock;
		पूर्ण

		r = kvm_setup_शेष_irq_routing(kvm);
		अगर (r) अणु
			kvm_ioapic_destroy(kvm);
			kvm_pic_destroy(kvm);
			जाओ create_irqchip_unlock;
		पूर्ण
		/* Write kvm->irq_routing beक्रमe enabling irqchip_in_kernel. */
		smp_wmb();
		kvm->arch.irqchip_mode = KVM_IRQCHIP_KERNEL;
	create_irqchip_unlock:
		mutex_unlock(&kvm->lock);
		अवरोध;
	पूर्ण
	हाल KVM_CREATE_PIT:
		u.pit_config.flags = KVM_PIT_SPEAKER_DUMMY;
		जाओ create_pit;
	हाल KVM_CREATE_PIT2:
		r = -EFAULT;
		अगर (copy_from_user(&u.pit_config, argp,
				   माप(काष्ठा kvm_pit_config)))
			जाओ out;
	create_pit:
		mutex_lock(&kvm->lock);
		r = -EEXIST;
		अगर (kvm->arch.vpit)
			जाओ create_pit_unlock;
		r = -ENOMEM;
		kvm->arch.vpit = kvm_create_pit(kvm, u.pit_config.flags);
		अगर (kvm->arch.vpit)
			r = 0;
	create_pit_unlock:
		mutex_unlock(&kvm->lock);
		अवरोध;
	हाल KVM_GET_IRQCHIP: अणु
		/* 0: PIC master, 1: PIC slave, 2: IOAPIC */
		काष्ठा kvm_irqchip *chip;

		chip = memdup_user(argp, माप(*chip));
		अगर (IS_ERR(chip)) अणु
			r = PTR_ERR(chip);
			जाओ out;
		पूर्ण

		r = -ENXIO;
		अगर (!irqchip_kernel(kvm))
			जाओ get_irqchip_out;
		r = kvm_vm_ioctl_get_irqchip(kvm, chip);
		अगर (r)
			जाओ get_irqchip_out;
		r = -EFAULT;
		अगर (copy_to_user(argp, chip, माप(*chip)))
			जाओ get_irqchip_out;
		r = 0;
	get_irqchip_out:
		kमुक्त(chip);
		अवरोध;
	पूर्ण
	हाल KVM_SET_IRQCHIP: अणु
		/* 0: PIC master, 1: PIC slave, 2: IOAPIC */
		काष्ठा kvm_irqchip *chip;

		chip = memdup_user(argp, माप(*chip));
		अगर (IS_ERR(chip)) अणु
			r = PTR_ERR(chip);
			जाओ out;
		पूर्ण

		r = -ENXIO;
		अगर (!irqchip_kernel(kvm))
			जाओ set_irqchip_out;
		r = kvm_vm_ioctl_set_irqchip(kvm, chip);
	set_irqchip_out:
		kमुक्त(chip);
		अवरोध;
	पूर्ण
	हाल KVM_GET_PIT: अणु
		r = -EFAULT;
		अगर (copy_from_user(&u.ps, argp, माप(काष्ठा kvm_pit_state)))
			जाओ out;
		r = -ENXIO;
		अगर (!kvm->arch.vpit)
			जाओ out;
		r = kvm_vm_ioctl_get_pit(kvm, &u.ps);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, &u.ps, माप(काष्ठा kvm_pit_state)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_PIT: अणु
		r = -EFAULT;
		अगर (copy_from_user(&u.ps, argp, माप(u.ps)))
			जाओ out;
		mutex_lock(&kvm->lock);
		r = -ENXIO;
		अगर (!kvm->arch.vpit)
			जाओ set_pit_out;
		r = kvm_vm_ioctl_set_pit(kvm, &u.ps);
set_pit_out:
		mutex_unlock(&kvm->lock);
		अवरोध;
	पूर्ण
	हाल KVM_GET_PIT2: अणु
		r = -ENXIO;
		अगर (!kvm->arch.vpit)
			जाओ out;
		r = kvm_vm_ioctl_get_pit2(kvm, &u.ps2);
		अगर (r)
			जाओ out;
		r = -EFAULT;
		अगर (copy_to_user(argp, &u.ps2, माप(u.ps2)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_SET_PIT2: अणु
		r = -EFAULT;
		अगर (copy_from_user(&u.ps2, argp, माप(u.ps2)))
			जाओ out;
		mutex_lock(&kvm->lock);
		r = -ENXIO;
		अगर (!kvm->arch.vpit)
			जाओ set_pit2_out;
		r = kvm_vm_ioctl_set_pit2(kvm, &u.ps2);
set_pit2_out:
		mutex_unlock(&kvm->lock);
		अवरोध;
	पूर्ण
	हाल KVM_REINJECT_CONTROL: अणु
		काष्ठा kvm_reinject_control control;
		r =  -EFAULT;
		अगर (copy_from_user(&control, argp, माप(control)))
			जाओ out;
		r = -ENXIO;
		अगर (!kvm->arch.vpit)
			जाओ out;
		r = kvm_vm_ioctl_reinject(kvm, &control);
		अवरोध;
	पूर्ण
	हाल KVM_SET_BOOT_CPU_ID:
		r = 0;
		mutex_lock(&kvm->lock);
		अगर (kvm->created_vcpus)
			r = -EBUSY;
		अन्यथा
			kvm->arch.bsp_vcpu_id = arg;
		mutex_unlock(&kvm->lock);
		अवरोध;
#अगर_घोषित CONFIG_KVM_XEN
	हाल KVM_XEN_HVM_CONFIG: अणु
		काष्ठा kvm_xen_hvm_config xhc;
		r = -EFAULT;
		अगर (copy_from_user(&xhc, argp, माप(xhc)))
			जाओ out;
		r = kvm_xen_hvm_config(kvm, &xhc);
		अवरोध;
	पूर्ण
	हाल KVM_XEN_HVM_GET_ATTR: अणु
		काष्ठा kvm_xen_hvm_attr xha;

		r = -EFAULT;
		अगर (copy_from_user(&xha, argp, माप(xha)))
			जाओ out;
		r = kvm_xen_hvm_get_attr(kvm, &xha);
		अगर (!r && copy_to_user(argp, &xha, माप(xha)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_XEN_HVM_SET_ATTR: अणु
		काष्ठा kvm_xen_hvm_attr xha;

		r = -EFAULT;
		अगर (copy_from_user(&xha, argp, माप(xha)))
			जाओ out;
		r = kvm_xen_hvm_set_attr(kvm, &xha);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल KVM_SET_CLOCK: अणु
		काष्ठा kvm_arch *ka = &kvm->arch;
		काष्ठा kvm_घड़ी_data user_ns;
		u64 now_ns;

		r = -EFAULT;
		अगर (copy_from_user(&user_ns, argp, माप(user_ns)))
			जाओ out;

		r = -EINVAL;
		अगर (user_ns.flags)
			जाओ out;

		r = 0;
		/*
		 * TODO: userspace has to take care of races with VCPU_RUN, so
		 * kvm_gen_update_masterघड़ी() can be cut करोwn to locked
		 * pvघड़ी_update_vm_gtod_copy().
		 */
		kvm_gen_update_masterघड़ी(kvm);

		/*
		 * This pairs with kvm_guest_समय_update(): when masterघड़ी is
		 * in use, we use master_kernel_ns + kvmघड़ी_offset to set
		 * अचिन्हित 'system_time' so अगर we use get_kvmघड़ी_ns() (which
		 * is slightly ahead) here we risk going negative on अचिन्हित
		 * 'system_time' when 'user_ns.clock' is very small.
		 */
		spin_lock_irq(&ka->pvघड़ी_gtod_sync_lock);
		अगर (kvm->arch.use_master_घड़ी)
			now_ns = ka->master_kernel_ns;
		अन्यथा
			now_ns = get_kvmघड़ी_base_ns();
		ka->kvmघड़ी_offset = user_ns.घड़ी - now_ns;
		spin_unlock_irq(&ka->pvघड़ी_gtod_sync_lock);

		kvm_make_all_cpus_request(kvm, KVM_REQ_CLOCK_UPDATE);
		अवरोध;
	पूर्ण
	हाल KVM_GET_CLOCK: अणु
		काष्ठा kvm_घड़ी_data user_ns;
		u64 now_ns;

		now_ns = get_kvmघड़ी_ns(kvm);
		user_ns.घड़ी = now_ns;
		user_ns.flags = kvm->arch.use_master_घड़ी ? KVM_CLOCK_TSC_STABLE : 0;
		स_रखो(&user_ns.pad, 0, माप(user_ns.pad));

		r = -EFAULT;
		अगर (copy_to_user(argp, &user_ns, माप(user_ns)))
			जाओ out;
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_MEMORY_ENCRYPT_OP: अणु
		r = -ENOTTY;
		अगर (kvm_x86_ops.mem_enc_op)
			r = अटल_call(kvm_x86_mem_enc_op)(kvm, argp);
		अवरोध;
	पूर्ण
	हाल KVM_MEMORY_ENCRYPT_REG_REGION: अणु
		काष्ठा kvm_enc_region region;

		r = -EFAULT;
		अगर (copy_from_user(&region, argp, माप(region)))
			जाओ out;

		r = -ENOTTY;
		अगर (kvm_x86_ops.mem_enc_reg_region)
			r = अटल_call(kvm_x86_mem_enc_reg_region)(kvm, &region);
		अवरोध;
	पूर्ण
	हाल KVM_MEMORY_ENCRYPT_UNREG_REGION: अणु
		काष्ठा kvm_enc_region region;

		r = -EFAULT;
		अगर (copy_from_user(&region, argp, माप(region)))
			जाओ out;

		r = -ENOTTY;
		अगर (kvm_x86_ops.mem_enc_unreg_region)
			r = अटल_call(kvm_x86_mem_enc_unreg_region)(kvm, &region);
		अवरोध;
	पूर्ण
	हाल KVM_HYPERV_EVENTFD: अणु
		काष्ठा kvm_hyperv_eventfd hvevfd;

		r = -EFAULT;
		अगर (copy_from_user(&hvevfd, argp, माप(hvevfd)))
			जाओ out;
		r = kvm_vm_ioctl_hv_eventfd(kvm, &hvevfd);
		अवरोध;
	पूर्ण
	हाल KVM_SET_PMU_EVENT_FILTER:
		r = kvm_vm_ioctl_set_pmu_event_filter(kvm, argp);
		अवरोध;
	हाल KVM_X86_SET_MSR_FILTER:
		r = kvm_vm_ioctl_set_msr_filter(kvm, argp);
		अवरोध;
	शेष:
		r = -ENOTTY;
	पूर्ण
out:
	वापस r;
पूर्ण

अटल व्योम kvm_init_msr_list(व्योम)
अणु
	काष्ठा x86_pmu_capability x86_pmu;
	u32 dummy[2];
	अचिन्हित i;

	BUILD_BUG_ON_MSG(INTEL_PMC_MAX_FIXED != 4,
			 "Please update the fixed PMCs in msrs_to_saved_all[]");

	perf_get_x86_pmu_capability(&x86_pmu);

	num_msrs_to_save = 0;
	num_emulated_msrs = 0;
	num_msr_based_features = 0;

	क्रम (i = 0; i < ARRAY_SIZE(msrs_to_save_all); i++) अणु
		अगर (rdmsr_safe(msrs_to_save_all[i], &dummy[0], &dummy[1]) < 0)
			जारी;

		/*
		 * Even MSRs that are valid in the host may not be exposed
		 * to the guests in some हालs.
		 */
		चयन (msrs_to_save_all[i]) अणु
		हाल MSR_IA32_BNDCFGS:
			अगर (!kvm_mpx_supported())
				जारी;
			अवरोध;
		हाल MSR_TSC_AUX:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_RDTSCP) &&
			    !kvm_cpu_cap_has(X86_FEATURE_RDPID))
				जारी;
			अवरोध;
		हाल MSR_IA32_UMWAIT_CONTROL:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_WAITPKG))
				जारी;
			अवरोध;
		हाल MSR_IA32_RTIT_CTL:
		हाल MSR_IA32_RTIT_STATUS:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_INTEL_PT))
				जारी;
			अवरोध;
		हाल MSR_IA32_RTIT_CR3_MATCH:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_INTEL_PT) ||
			    !पूर्णांकel_pt_validate_hw_cap(PT_CAP_cr3_filtering))
				जारी;
			अवरोध;
		हाल MSR_IA32_RTIT_OUTPUT_BASE:
		हाल MSR_IA32_RTIT_OUTPUT_MASK:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_INTEL_PT) ||
				(!पूर्णांकel_pt_validate_hw_cap(PT_CAP_topa_output) &&
				 !पूर्णांकel_pt_validate_hw_cap(PT_CAP_single_range_output)))
				जारी;
			अवरोध;
		हाल MSR_IA32_RTIT_ADDR0_A ... MSR_IA32_RTIT_ADDR3_B:
			अगर (!kvm_cpu_cap_has(X86_FEATURE_INTEL_PT) ||
				msrs_to_save_all[i] - MSR_IA32_RTIT_ADDR0_A >=
				पूर्णांकel_pt_validate_hw_cap(PT_CAP_num_address_ranges) * 2)
				जारी;
			अवरोध;
		हाल MSR_ARCH_PERFMON_PERFCTR0 ... MSR_ARCH_PERFMON_PERFCTR0 + 17:
			अगर (msrs_to_save_all[i] - MSR_ARCH_PERFMON_PERFCTR0 >=
			    min(INTEL_PMC_MAX_GENERIC, x86_pmu.num_counters_gp))
				जारी;
			अवरोध;
		हाल MSR_ARCH_PERFMON_EVENTSEL0 ... MSR_ARCH_PERFMON_EVENTSEL0 + 17:
			अगर (msrs_to_save_all[i] - MSR_ARCH_PERFMON_EVENTSEL0 >=
			    min(INTEL_PMC_MAX_GENERIC, x86_pmu.num_counters_gp))
				जारी;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		msrs_to_save[num_msrs_to_save++] = msrs_to_save_all[i];
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(emulated_msrs_all); i++) अणु
		अगर (!अटल_call(kvm_x86_has_emulated_msr)(शून्य, emulated_msrs_all[i]))
			जारी;

		emulated_msrs[num_emulated_msrs++] = emulated_msrs_all[i];
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(msr_based_features_all); i++) अणु
		काष्ठा kvm_msr_entry msr;

		msr.index = msr_based_features_all[i];
		अगर (kvm_get_msr_feature(&msr))
			जारी;

		msr_based_features[num_msr_based_features++] = msr_based_features_all[i];
	पूर्ण
पूर्ण

अटल पूर्णांक vcpu_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t addr, पूर्णांक len,
			   स्थिर व्योम *v)
अणु
	पूर्णांक handled = 0;
	पूर्णांक n;

	करो अणु
		n = min(len, 8);
		अगर (!(lapic_in_kernel(vcpu) &&
		      !kvm_iodevice_ग_लिखो(vcpu, &vcpu->arch.apic->dev, addr, n, v))
		    && kvm_io_bus_ग_लिखो(vcpu, KVM_MMIO_BUS, addr, n, v))
			अवरोध;
		handled += n;
		addr += n;
		len -= n;
		v += n;
	पूर्ण जबतक (len);

	वापस handled;
पूर्ण

अटल पूर्णांक vcpu_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, gpa_t addr, पूर्णांक len, व्योम *v)
अणु
	पूर्णांक handled = 0;
	पूर्णांक n;

	करो अणु
		n = min(len, 8);
		अगर (!(lapic_in_kernel(vcpu) &&
		      !kvm_iodevice_पढ़ो(vcpu, &vcpu->arch.apic->dev,
					 addr, n, v))
		    && kvm_io_bus_पढ़ो(vcpu, KVM_MMIO_BUS, addr, n, v))
			अवरोध;
		trace_kvm_mmio(KVM_TRACE_MMIO_READ, n, addr, v);
		handled += n;
		addr += n;
		len -= n;
		v += n;
	पूर्ण जबतक (len);

	वापस handled;
पूर्ण

अटल व्योम kvm_set_segment(काष्ठा kvm_vcpu *vcpu,
			काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	अटल_call(kvm_x86_set_segment)(vcpu, var, seg);
पूर्ण

व्योम kvm_get_segment(काष्ठा kvm_vcpu *vcpu,
		     काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	अटल_call(kvm_x86_get_segment)(vcpu, var, seg);
पूर्ण

gpa_t translate_nested_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 access,
			   काष्ठा x86_exception *exception)
अणु
	gpa_t t_gpa;

	BUG_ON(!mmu_is_nested(vcpu));

	/* NPT walks are always user-walks */
	access |= PFERR_USER_MASK;
	t_gpa  = vcpu->arch.mmu->gva_to_gpa(vcpu, gpa, access, exception);

	वापस t_gpa;
पूर्ण

gpa_t kvm_mmu_gva_to_gpa_पढ़ो(काष्ठा kvm_vcpu *vcpu, gva_t gva,
			      काष्ठा x86_exception *exception)
अणु
	u32 access = (अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0;
	वापस vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, exception);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mmu_gva_to_gpa_पढ़ो);

 gpa_t kvm_mmu_gva_to_gpa_fetch(काष्ठा kvm_vcpu *vcpu, gva_t gva,
				काष्ठा x86_exception *exception)
अणु
	u32 access = (अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0;
	access |= PFERR_FETCH_MASK;
	वापस vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, exception);
पूर्ण

gpa_t kvm_mmu_gva_to_gpa_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gva_t gva,
			       काष्ठा x86_exception *exception)
अणु
	u32 access = (अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0;
	access |= PFERR_WRITE_MASK;
	वापस vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, exception);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mmu_gva_to_gpa_ग_लिखो);

/* uses this to access any guest's mapped memory without checking CPL */
gpa_t kvm_mmu_gva_to_gpa_प्रणाली(काष्ठा kvm_vcpu *vcpu, gva_t gva,
				काष्ठा x86_exception *exception)
अणु
	वापस vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, 0, exception);
पूर्ण

अटल पूर्णांक kvm_पढ़ो_guest_virt_helper(gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
				      काष्ठा kvm_vcpu *vcpu, u32 access,
				      काष्ठा x86_exception *exception)
अणु
	व्योम *data = val;
	पूर्णांक r = X86EMUL_CONTINUE;

	जबतक (bytes) अणु
		gpa_t gpa = vcpu->arch.walk_mmu->gva_to_gpa(vcpu, addr, access,
							    exception);
		अचिन्हित offset = addr & (PAGE_SIZE-1);
		अचिन्हित toपढ़ो = min(bytes, (अचिन्हित)PAGE_SIZE - offset);
		पूर्णांक ret;

		अगर (gpa == UNMAPPED_GVA)
			वापस X86EMUL_PROPAGATE_FAULT;
		ret = kvm_vcpu_पढ़ो_guest_page(vcpu, gpa >> PAGE_SHIFT, data,
					       offset, toपढ़ो);
		अगर (ret < 0) अणु
			r = X86EMUL_IO_NEEDED;
			जाओ out;
		पूर्ण

		bytes -= toपढ़ो;
		data += toपढ़ो;
		addr += toपढ़ो;
	पूर्ण
out:
	वापस r;
पूर्ण

/* used क्रम inकाष्ठाion fetching */
अटल पूर्णांक kvm_fetch_guest_virt(काष्ठा x86_emulate_ctxt *ctxt,
				gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
				काष्ठा x86_exception *exception)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u32 access = (अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0;
	अचिन्हित offset;
	पूर्णांक ret;

	/* Inline kvm_पढ़ो_guest_virt_helper क्रम speed.  */
	gpa_t gpa = vcpu->arch.walk_mmu->gva_to_gpa(vcpu, addr, access|PFERR_FETCH_MASK,
						    exception);
	अगर (unlikely(gpa == UNMAPPED_GVA))
		वापस X86EMUL_PROPAGATE_FAULT;

	offset = addr & (PAGE_SIZE-1);
	अगर (WARN_ON(offset + bytes > PAGE_SIZE))
		bytes = (अचिन्हित)PAGE_SIZE - offset;
	ret = kvm_vcpu_पढ़ो_guest_page(vcpu, gpa >> PAGE_SHIFT, val,
				       offset, bytes);
	अगर (unlikely(ret < 0))
		वापस X86EMUL_IO_NEEDED;

	वापस X86EMUL_CONTINUE;
पूर्ण

पूर्णांक kvm_पढ़ो_guest_virt(काष्ठा kvm_vcpu *vcpu,
			       gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
			       काष्ठा x86_exception *exception)
अणु
	u32 access = (अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0;

	/*
	 * FIXME: this should call handle_emulation_failure अगर X86EMUL_IO_NEEDED
	 * is वापसed, but our callers are not पढ़ोy क्रम that and they blindly
	 * call kvm_inject_page_fault.  Ensure that they at least करो not leak
	 * uninitialized kernel stack memory पूर्णांकo cr2 and error code.
	 */
	स_रखो(exception, 0, माप(*exception));
	वापस kvm_पढ़ो_guest_virt_helper(addr, val, bytes, vcpu, access,
					  exception);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पढ़ो_guest_virt);

अटल पूर्णांक emulator_पढ़ो_std(काष्ठा x86_emulate_ctxt *ctxt,
			     gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
			     काष्ठा x86_exception *exception, bool प्रणाली)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u32 access = 0;

	अगर (!प्रणाली && अटल_call(kvm_x86_get_cpl)(vcpu) == 3)
		access |= PFERR_USER_MASK;

	वापस kvm_पढ़ो_guest_virt_helper(addr, val, bytes, vcpu, access, exception);
पूर्ण

अटल पूर्णांक kvm_पढ़ो_guest_phys_प्रणाली(काष्ठा x86_emulate_ctxt *ctxt,
		अचिन्हित दीर्घ addr, व्योम *val, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	पूर्णांक r = kvm_vcpu_पढ़ो_guest(vcpu, addr, val, bytes);

	वापस r < 0 ? X86EMUL_IO_NEEDED : X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक kvm_ग_लिखो_guest_virt_helper(gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
				      काष्ठा kvm_vcpu *vcpu, u32 access,
				      काष्ठा x86_exception *exception)
अणु
	व्योम *data = val;
	पूर्णांक r = X86EMUL_CONTINUE;

	जबतक (bytes) अणु
		gpa_t gpa =  vcpu->arch.walk_mmu->gva_to_gpa(vcpu, addr,
							     access,
							     exception);
		अचिन्हित offset = addr & (PAGE_SIZE-1);
		अचिन्हित toग_लिखो = min(bytes, (अचिन्हित)PAGE_SIZE - offset);
		पूर्णांक ret;

		अगर (gpa == UNMAPPED_GVA)
			वापस X86EMUL_PROPAGATE_FAULT;
		ret = kvm_vcpu_ग_लिखो_guest(vcpu, gpa, data, toग_लिखो);
		अगर (ret < 0) अणु
			r = X86EMUL_IO_NEEDED;
			जाओ out;
		पूर्ण

		bytes -= toग_लिखो;
		data += toग_लिखो;
		addr += toग_लिखो;
	पूर्ण
out:
	वापस r;
पूर्ण

अटल पूर्णांक emulator_ग_लिखो_std(काष्ठा x86_emulate_ctxt *ctxt, gva_t addr, व्योम *val,
			      अचिन्हित पूर्णांक bytes, काष्ठा x86_exception *exception,
			      bool प्रणाली)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u32 access = PFERR_WRITE_MASK;

	अगर (!प्रणाली && अटल_call(kvm_x86_get_cpl)(vcpu) == 3)
		access |= PFERR_USER_MASK;

	वापस kvm_ग_लिखो_guest_virt_helper(addr, val, bytes, vcpu,
					   access, exception);
पूर्ण

पूर्णांक kvm_ग_लिखो_guest_virt_प्रणाली(काष्ठा kvm_vcpu *vcpu, gva_t addr, व्योम *val,
				अचिन्हित पूर्णांक bytes, काष्ठा x86_exception *exception)
अणु
	/* kvm_ग_लिखो_guest_virt_प्रणाली can pull in tons of pages. */
	vcpu->arch.l1tf_flush_l1d = true;

	वापस kvm_ग_लिखो_guest_virt_helper(addr, val, bytes, vcpu,
					   PFERR_WRITE_MASK, exception);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_ग_लिखो_guest_virt_प्रणाली);

पूर्णांक handle_ud(काष्ठा kvm_vcpu *vcpu)
अणु
	अटल स्थिर अक्षर kvm_emulate_prefix[] = अणु __KVM_EMULATE_PREFIX पूर्ण;
	पूर्णांक emul_type = EMULTYPE_TRAP_UD;
	अक्षर sig[5]; /* ud2; .ascii "kvm" */
	काष्ठा x86_exception e;

	अगर (unlikely(!अटल_call(kvm_x86_can_emulate_inकाष्ठाion)(vcpu, शून्य, 0)))
		वापस 1;

	अगर (क्रमce_emulation_prefix &&
	    kvm_पढ़ो_guest_virt(vcpu, kvm_get_linear_rip(vcpu),
				sig, माप(sig), &e) == 0 &&
	    स_भेद(sig, kvm_emulate_prefix, माप(sig)) == 0) अणु
		kvm_rip_ग_लिखो(vcpu, kvm_rip_पढ़ो(vcpu) + माप(sig));
		emul_type = EMULTYPE_TRAP_UD_FORCED;
	पूर्ण

	वापस kvm_emulate_inकाष्ठाion(vcpu, emul_type);
पूर्ण
EXPORT_SYMBOL_GPL(handle_ud);

अटल पूर्णांक vcpu_is_mmio_gpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
			    gpa_t gpa, bool ग_लिखो)
अणु
	/* For APIC access vmनिकास */
	अगर ((gpa & PAGE_MASK) == APIC_DEFAULT_PHYS_BASE)
		वापस 1;

	अगर (vcpu_match_mmio_gpa(vcpu, gpa)) अणु
		trace_vcpu_match_mmio(gva, gpa, ग_लिखो, true);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcpu_mmio_gva_to_gpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
				gpa_t *gpa, काष्ठा x86_exception *exception,
				bool ग_लिखो)
अणु
	u32 access = ((अटल_call(kvm_x86_get_cpl)(vcpu) == 3) ? PFERR_USER_MASK : 0)
		| (ग_लिखो ? PFERR_WRITE_MASK : 0);

	/*
	 * currently PKRU is only applied to ept enabled guest so
	 * there is no pkey in EPT page table क्रम L1 guest or EPT
	 * shaकरोw page table क्रम L2 guest.
	 */
	अगर (vcpu_match_mmio_gva(vcpu, gva)
	    && !permission_fault(vcpu, vcpu->arch.walk_mmu,
				 vcpu->arch.mmio_access, 0, access)) अणु
		*gpa = vcpu->arch.mmio_gfn << PAGE_SHIFT |
					(gva & (PAGE_SIZE - 1));
		trace_vcpu_match_mmio(gva, *gpa, ग_लिखो, false);
		वापस 1;
	पूर्ण

	*gpa = vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, exception);

	अगर (*gpa == UNMAPPED_GVA)
		वापस -1;

	वापस vcpu_is_mmio_gpa(vcpu, gva, *gpa, ग_लिखो);
पूर्ण

पूर्णांक emulator_ग_लिखो_phys(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			स्थिर व्योम *val, पूर्णांक bytes)
अणु
	पूर्णांक ret;

	ret = kvm_vcpu_ग_लिखो_guest(vcpu, gpa, val, bytes);
	अगर (ret < 0)
		वापस 0;
	kvm_page_track_ग_लिखो(vcpu, gpa, val, bytes);
	वापस 1;
पूर्ण

काष्ठा पढ़ो_ग_लिखो_emulator_ops अणु
	पूर्णांक (*पढ़ो_ग_लिखो_prepare)(काष्ठा kvm_vcpu *vcpu, व्योम *val,
				  पूर्णांक bytes);
	पूर्णांक (*पढ़ो_ग_लिखो_emulate)(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
				  व्योम *val, पूर्णांक bytes);
	पूर्णांक (*पढ़ो_ग_लिखो_mmio)(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			       पूर्णांक bytes, व्योम *val);
	पूर्णांक (*पढ़ो_ग_लिखो_निकास_mmio)(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
				    व्योम *val, पूर्णांक bytes);
	bool ग_लिखो;
पूर्ण;

अटल पूर्णांक पढ़ो_prepare(काष्ठा kvm_vcpu *vcpu, व्योम *val, पूर्णांक bytes)
अणु
	अगर (vcpu->mmio_पढ़ो_completed) अणु
		trace_kvm_mmio(KVM_TRACE_MMIO_READ, bytes,
			       vcpu->mmio_fragments[0].gpa, val);
		vcpu->mmio_पढ़ो_completed = 0;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_emulate(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			व्योम *val, पूर्णांक bytes)
अणु
	वापस !kvm_vcpu_पढ़ो_guest(vcpu, gpa, val, bytes);
पूर्ण

अटल पूर्णांक ग_लिखो_emulate(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			 व्योम *val, पूर्णांक bytes)
अणु
	वापस emulator_ग_लिखो_phys(vcpu, gpa, val, bytes);
पूर्ण

अटल पूर्णांक ग_लिखो_mmio(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, पूर्णांक bytes, व्योम *val)
अणु
	trace_kvm_mmio(KVM_TRACE_MMIO_WRITE, bytes, gpa, val);
	वापस vcpu_mmio_ग_लिखो(vcpu, gpa, bytes, val);
पूर्ण

अटल पूर्णांक पढ़ो_निकास_mmio(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			  व्योम *val, पूर्णांक bytes)
अणु
	trace_kvm_mmio(KVM_TRACE_MMIO_READ_UNSATISFIED, bytes, gpa, शून्य);
	वापस X86EMUL_IO_NEEDED;
पूर्ण

अटल पूर्णांक ग_लिखो_निकास_mmio(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			   व्योम *val, पूर्णांक bytes)
अणु
	काष्ठा kvm_mmio_fragment *frag = &vcpu->mmio_fragments[0];

	स_नकल(vcpu->run->mmio.data, frag->data, min(8u, frag->len));
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल स्थिर काष्ठा पढ़ो_ग_लिखो_emulator_ops पढ़ो_emultor = अणु
	.पढ़ो_ग_लिखो_prepare = पढ़ो_prepare,
	.पढ़ो_ग_लिखो_emulate = पढ़ो_emulate,
	.पढ़ो_ग_लिखो_mmio = vcpu_mmio_पढ़ो,
	.पढ़ो_ग_लिखो_निकास_mmio = पढ़ो_निकास_mmio,
पूर्ण;

अटल स्थिर काष्ठा पढ़ो_ग_लिखो_emulator_ops ग_लिखो_emultor = अणु
	.पढ़ो_ग_लिखो_emulate = ग_लिखो_emulate,
	.पढ़ो_ग_लिखो_mmio = ग_लिखो_mmio,
	.पढ़ो_ग_लिखो_निकास_mmio = ग_लिखो_निकास_mmio,
	.ग_लिखो = true,
पूर्ण;

अटल पूर्णांक emulator_पढ़ो_ग_लिखो_onepage(अचिन्हित दीर्घ addr, व्योम *val,
				       अचिन्हित पूर्णांक bytes,
				       काष्ठा x86_exception *exception,
				       काष्ठा kvm_vcpu *vcpu,
				       स्थिर काष्ठा पढ़ो_ग_लिखो_emulator_ops *ops)
अणु
	gpa_t gpa;
	पूर्णांक handled, ret;
	bool ग_लिखो = ops->ग_लिखो;
	काष्ठा kvm_mmio_fragment *frag;
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;

	/*
	 * If the निकास was due to a NPF we may alपढ़ोy have a GPA.
	 * If the GPA is present, use it to aव्योम the GVA to GPA table walk.
	 * Note, this cannot be used on string operations since string
	 * operation using rep will only have the initial GPA from the NPF
	 * occurred.
	 */
	अगर (ctxt->gpa_available && emulator_can_use_gpa(ctxt) &&
	    (addr & ~PAGE_MASK) == (ctxt->gpa_val & ~PAGE_MASK)) अणु
		gpa = ctxt->gpa_val;
		ret = vcpu_is_mmio_gpa(vcpu, addr, gpa, ग_लिखो);
	पूर्ण अन्यथा अणु
		ret = vcpu_mmio_gva_to_gpa(vcpu, addr, &gpa, exception, ग_लिखो);
		अगर (ret < 0)
			वापस X86EMUL_PROPAGATE_FAULT;
	पूर्ण

	अगर (!ret && ops->पढ़ो_ग_लिखो_emulate(vcpu, gpa, val, bytes))
		वापस X86EMUL_CONTINUE;

	/*
	 * Is this MMIO handled locally?
	 */
	handled = ops->पढ़ो_ग_लिखो_mmio(vcpu, gpa, bytes, val);
	अगर (handled == bytes)
		वापस X86EMUL_CONTINUE;

	gpa += handled;
	bytes -= handled;
	val += handled;

	WARN_ON(vcpu->mmio_nr_fragments >= KVM_MAX_MMIO_FRAGMENTS);
	frag = &vcpu->mmio_fragments[vcpu->mmio_nr_fragments++];
	frag->gpa = gpa;
	frag->data = val;
	frag->len = bytes;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक emulator_पढ़ो_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt,
			अचिन्हित दीर्घ addr,
			व्योम *val, अचिन्हित पूर्णांक bytes,
			काष्ठा x86_exception *exception,
			स्थिर काष्ठा पढ़ो_ग_लिखो_emulator_ops *ops)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	gpa_t gpa;
	पूर्णांक rc;

	अगर (ops->पढ़ो_ग_लिखो_prepare &&
		  ops->पढ़ो_ग_लिखो_prepare(vcpu, val, bytes))
		वापस X86EMUL_CONTINUE;

	vcpu->mmio_nr_fragments = 0;

	/* Crossing a page boundary? */
	अगर (((addr + bytes - 1) ^ addr) & PAGE_MASK) अणु
		पूर्णांक now;

		now = -addr & ~PAGE_MASK;
		rc = emulator_पढ़ो_ग_लिखो_onepage(addr, val, now, exception,
						 vcpu, ops);

		अगर (rc != X86EMUL_CONTINUE)
			वापस rc;
		addr += now;
		अगर (ctxt->mode != X86EMUL_MODE_PROT64)
			addr = (u32)addr;
		val += now;
		bytes -= now;
	पूर्ण

	rc = emulator_पढ़ो_ग_लिखो_onepage(addr, val, bytes, exception,
					 vcpu, ops);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	अगर (!vcpu->mmio_nr_fragments)
		वापस rc;

	gpa = vcpu->mmio_fragments[0].gpa;

	vcpu->mmio_needed = 1;
	vcpu->mmio_cur_fragment = 0;

	vcpu->run->mmio.len = min(8u, vcpu->mmio_fragments[0].len);
	vcpu->run->mmio.is_ग_लिखो = vcpu->mmio_is_ग_लिखो = ops->ग_लिखो;
	vcpu->run->निकास_reason = KVM_EXIT_MMIO;
	vcpu->run->mmio.phys_addr = gpa;

	वापस ops->पढ़ो_ग_लिखो_निकास_mmio(vcpu, gpa, val, bytes);
पूर्ण

अटल पूर्णांक emulator_पढ़ो_emulated(काष्ठा x86_emulate_ctxt *ctxt,
				  अचिन्हित दीर्घ addr,
				  व्योम *val,
				  अचिन्हित पूर्णांक bytes,
				  काष्ठा x86_exception *exception)
अणु
	वापस emulator_पढ़ो_ग_लिखो(ctxt, addr, val, bytes,
				   exception, &पढ़ो_emultor);
पूर्ण

अटल पूर्णांक emulator_ग_लिखो_emulated(काष्ठा x86_emulate_ctxt *ctxt,
			    अचिन्हित दीर्घ addr,
			    स्थिर व्योम *val,
			    अचिन्हित पूर्णांक bytes,
			    काष्ठा x86_exception *exception)
अणु
	वापस emulator_पढ़ो_ग_लिखो(ctxt, addr, (व्योम *)val, bytes,
				   exception, &ग_लिखो_emultor);
पूर्ण

#घोषणा CMPXCHG_TYPE(t, ptr, old, new) \
	(cmpxchg((t *)(ptr), *(t *)(old), *(t *)(new)) == *(t *)(old))

#अगर_घोषित CONFIG_X86_64
#  define CMPXCHG64(ptr, old, new) CMPXCHG_TYPE(u64, ptr, old, new)
#अन्यथा
#  define CMPXCHG64(ptr, old, new) \
	(cmpxchg64((u64 *)(ptr), *(u64 *)(old), *(u64 *)(new)) == *(u64 *)(old))
#पूर्ण_अगर

अटल पूर्णांक emulator_cmpxchg_emulated(काष्ठा x86_emulate_ctxt *ctxt,
				     अचिन्हित दीर्घ addr,
				     स्थिर व्योम *old,
				     स्थिर व्योम *new,
				     अचिन्हित पूर्णांक bytes,
				     काष्ठा x86_exception *exception)
अणु
	काष्ठा kvm_host_map map;
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u64 page_line_mask;
	gpa_t gpa;
	अक्षर *kaddr;
	bool exchanged;

	/* guests cmpxchg8b have to be emulated atomically */
	अगर (bytes > 8 || (bytes & (bytes - 1)))
		जाओ emul_ग_लिखो;

	gpa = kvm_mmu_gva_to_gpa_ग_लिखो(vcpu, addr, शून्य);

	अगर (gpa == UNMAPPED_GVA ||
	    (gpa & PAGE_MASK) == APIC_DEFAULT_PHYS_BASE)
		जाओ emul_ग_लिखो;

	/*
	 * Emulate the atomic as a straight ग_लिखो to aव्योम #AC अगर SLD is
	 * enabled in the host and the access splits a cache line.
	 */
	अगर (boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT))
		page_line_mask = ~(cache_line_size() - 1);
	अन्यथा
		page_line_mask = PAGE_MASK;

	अगर (((gpa + bytes - 1) & page_line_mask) != (gpa & page_line_mask))
		जाओ emul_ग_लिखो;

	अगर (kvm_vcpu_map(vcpu, gpa_to_gfn(gpa), &map))
		जाओ emul_ग_लिखो;

	kaddr = map.hva + offset_in_page(gpa);

	चयन (bytes) अणु
	हाल 1:
		exchanged = CMPXCHG_TYPE(u8, kaddr, old, new);
		अवरोध;
	हाल 2:
		exchanged = CMPXCHG_TYPE(u16, kaddr, old, new);
		अवरोध;
	हाल 4:
		exchanged = CMPXCHG_TYPE(u32, kaddr, old, new);
		अवरोध;
	हाल 8:
		exchanged = CMPXCHG64(kaddr, old, new);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	kvm_vcpu_unmap(vcpu, &map, true);

	अगर (!exchanged)
		वापस X86EMUL_CMPXCHG_FAILED;

	kvm_page_track_ग_लिखो(vcpu, gpa, new, bytes);

	वापस X86EMUL_CONTINUE;

emul_ग_लिखो:
	prपूर्णांकk_once(KERN_WARNING "kvm: emulating exchange as write\n");

	वापस emulator_ग_लिखो_emulated(ctxt, addr, new, bytes, exception);
पूर्ण

अटल पूर्णांक kernel_pio(काष्ठा kvm_vcpu *vcpu, व्योम *pd)
अणु
	पूर्णांक r = 0, i;

	क्रम (i = 0; i < vcpu->arch.pio.count; i++) अणु
		अगर (vcpu->arch.pio.in)
			r = kvm_io_bus_पढ़ो(vcpu, KVM_PIO_BUS, vcpu->arch.pio.port,
					    vcpu->arch.pio.size, pd);
		अन्यथा
			r = kvm_io_bus_ग_लिखो(vcpu, KVM_PIO_BUS,
					     vcpu->arch.pio.port, vcpu->arch.pio.size,
					     pd);
		अगर (r)
			अवरोध;
		pd += vcpu->arch.pio.size;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक emulator_pio_in_out(काष्ठा kvm_vcpu *vcpu, पूर्णांक size,
			       अचिन्हित लघु port, व्योम *val,
			       अचिन्हित पूर्णांक count, bool in)
अणु
	vcpu->arch.pio.port = port;
	vcpu->arch.pio.in = in;
	vcpu->arch.pio.count  = count;
	vcpu->arch.pio.size = size;

	अगर (!kernel_pio(vcpu, vcpu->arch.pio_data)) अणु
		vcpu->arch.pio.count = 0;
		वापस 1;
	पूर्ण

	vcpu->run->निकास_reason = KVM_EXIT_IO;
	vcpu->run->io.direction = in ? KVM_EXIT_IO_IN : KVM_EXIT_IO_OUT;
	vcpu->run->io.size = size;
	vcpu->run->io.data_offset = KVM_PIO_PAGE_OFFSET * PAGE_SIZE;
	vcpu->run->io.count = count;
	vcpu->run->io.port = port;

	वापस 0;
पूर्ण

अटल पूर्णांक emulator_pio_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक size,
			   अचिन्हित लघु port, व्योम *val, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;

	अगर (vcpu->arch.pio.count)
		जाओ data_avail;

	स_रखो(vcpu->arch.pio_data, 0, size * count);

	ret = emulator_pio_in_out(vcpu, size, port, val, count, true);
	अगर (ret) अणु
data_avail:
		स_नकल(val, vcpu->arch.pio_data, size * count);
		trace_kvm_pio(KVM_PIO_IN, port, size, count, vcpu->arch.pio_data);
		vcpu->arch.pio.count = 0;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emulator_pio_in_emulated(काष्ठा x86_emulate_ctxt *ctxt,
				    पूर्णांक size, अचिन्हित लघु port, व्योम *val,
				    अचिन्हित पूर्णांक count)
अणु
	वापस emulator_pio_in(emul_to_vcpu(ctxt), size, port, val, count);

पूर्ण

अटल पूर्णांक emulator_pio_out(काष्ठा kvm_vcpu *vcpu, पूर्णांक size,
			    अचिन्हित लघु port, स्थिर व्योम *val,
			    अचिन्हित पूर्णांक count)
अणु
	स_नकल(vcpu->arch.pio_data, val, size * count);
	trace_kvm_pio(KVM_PIO_OUT, port, size, count, vcpu->arch.pio_data);
	वापस emulator_pio_in_out(vcpu, size, port, (व्योम *)val, count, false);
पूर्ण

अटल पूर्णांक emulator_pio_out_emulated(काष्ठा x86_emulate_ctxt *ctxt,
				     पूर्णांक size, अचिन्हित लघु port,
				     स्थिर व्योम *val, अचिन्हित पूर्णांक count)
अणु
	वापस emulator_pio_out(emul_to_vcpu(ctxt), size, port, val, count);
पूर्ण

अटल अचिन्हित दीर्घ get_segment_base(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	वापस अटल_call(kvm_x86_get_segment_base)(vcpu, seg);
पूर्ण

अटल व्योम emulator_invlpg(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ address)
अणु
	kvm_mmu_invlpg(emul_to_vcpu(ctxt), address);
पूर्ण

अटल पूर्णांक kvm_emulate_wbinvd_noskip(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!need_emulate_wbinvd(vcpu))
		वापस X86EMUL_CONTINUE;

	अगर (अटल_call(kvm_x86_has_wbinvd_निकास)()) अणु
		पूर्णांक cpu = get_cpu();

		cpumask_set_cpu(cpu, vcpu->arch.wbinvd_dirty_mask);
		on_each_cpu_mask(vcpu->arch.wbinvd_dirty_mask,
				wbinvd_ipi, शून्य, 1);
		put_cpu();
		cpumask_clear(vcpu->arch.wbinvd_dirty_mask);
	पूर्ण अन्यथा
		wbinvd();
	वापस X86EMUL_CONTINUE;
पूर्ण

पूर्णांक kvm_emulate_wbinvd(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_emulate_wbinvd_noskip(vcpu);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_wbinvd);



अटल व्योम emulator_wbinvd(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	kvm_emulate_wbinvd_noskip(emul_to_vcpu(ctxt));
पूर्ण

अटल व्योम emulator_get_dr(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक dr,
			    अचिन्हित दीर्घ *dest)
अणु
	kvm_get_dr(emul_to_vcpu(ctxt), dr, dest);
पूर्ण

अटल पूर्णांक emulator_set_dr(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक dr,
			   अचिन्हित दीर्घ value)
अणु

	वापस kvm_set_dr(emul_to_vcpu(ctxt), dr, value);
पूर्ण

अटल u64 mk_cr_64(u64 curr_cr, u32 new_val)
अणु
	वापस (curr_cr & ~((1ULL << 32) - 1)) | new_val;
पूर्ण

अटल अचिन्हित दीर्घ emulator_get_cr(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक cr)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	अचिन्हित दीर्घ value;

	चयन (cr) अणु
	हाल 0:
		value = kvm_पढ़ो_cr0(vcpu);
		अवरोध;
	हाल 2:
		value = vcpu->arch.cr2;
		अवरोध;
	हाल 3:
		value = kvm_पढ़ो_cr3(vcpu);
		अवरोध;
	हाल 4:
		value = kvm_पढ़ो_cr4(vcpu);
		अवरोध;
	हाल 8:
		value = kvm_get_cr8(vcpu);
		अवरोध;
	शेष:
		kvm_err("%s: unexpected cr %u\n", __func__, cr);
		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक emulator_set_cr(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक cr, uदीर्घ val)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	पूर्णांक res = 0;

	चयन (cr) अणु
	हाल 0:
		res = kvm_set_cr0(vcpu, mk_cr_64(kvm_पढ़ो_cr0(vcpu), val));
		अवरोध;
	हाल 2:
		vcpu->arch.cr2 = val;
		अवरोध;
	हाल 3:
		res = kvm_set_cr3(vcpu, val);
		अवरोध;
	हाल 4:
		res = kvm_set_cr4(vcpu, mk_cr_64(kvm_पढ़ो_cr4(vcpu), val));
		अवरोध;
	हाल 8:
		res = kvm_set_cr8(vcpu, val);
		अवरोध;
	शेष:
		kvm_err("%s: unexpected cr %u\n", __func__, cr);
		res = -1;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक emulator_get_cpl(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस अटल_call(kvm_x86_get_cpl)(emul_to_vcpu(ctxt));
पूर्ण

अटल व्योम emulator_get_gdt(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt)
अणु
	अटल_call(kvm_x86_get_gdt)(emul_to_vcpu(ctxt), dt);
पूर्ण

अटल व्योम emulator_get_idt(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt)
अणु
	अटल_call(kvm_x86_get_idt)(emul_to_vcpu(ctxt), dt);
पूर्ण

अटल व्योम emulator_set_gdt(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt)
अणु
	अटल_call(kvm_x86_set_gdt)(emul_to_vcpu(ctxt), dt);
पूर्ण

अटल व्योम emulator_set_idt(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा desc_ptr *dt)
अणु
	अटल_call(kvm_x86_set_idt)(emul_to_vcpu(ctxt), dt);
पूर्ण

अटल अचिन्हित दीर्घ emulator_get_cached_segment_base(
	काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक seg)
अणु
	वापस get_segment_base(emul_to_vcpu(ctxt), seg);
पूर्ण

अटल bool emulator_get_segment(काष्ठा x86_emulate_ctxt *ctxt, u16 *selector,
				 काष्ठा desc_काष्ठा *desc, u32 *base3,
				 पूर्णांक seg)
अणु
	काष्ठा kvm_segment var;

	kvm_get_segment(emul_to_vcpu(ctxt), &var, seg);
	*selector = var.selector;

	अगर (var.unusable) अणु
		स_रखो(desc, 0, माप(*desc));
		अगर (base3)
			*base3 = 0;
		वापस false;
	पूर्ण

	अगर (var.g)
		var.limit >>= 12;
	set_desc_limit(desc, var.limit);
	set_desc_base(desc, (अचिन्हित दीर्घ)var.base);
#अगर_घोषित CONFIG_X86_64
	अगर (base3)
		*base3 = var.base >> 32;
#पूर्ण_अगर
	desc->type = var.type;
	desc->s = var.s;
	desc->dpl = var.dpl;
	desc->p = var.present;
	desc->avl = var.avl;
	desc->l = var.l;
	desc->d = var.db;
	desc->g = var.g;

	वापस true;
पूर्ण

अटल व्योम emulator_set_segment(काष्ठा x86_emulate_ctxt *ctxt, u16 selector,
				 काष्ठा desc_काष्ठा *desc, u32 base3,
				 पूर्णांक seg)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	काष्ठा kvm_segment var;

	var.selector = selector;
	var.base = get_desc_base(desc);
#अगर_घोषित CONFIG_X86_64
	var.base |= ((u64)base3) << 32;
#पूर्ण_अगर
	var.limit = get_desc_limit(desc);
	अगर (desc->g)
		var.limit = (var.limit << 12) | 0xfff;
	var.type = desc->type;
	var.dpl = desc->dpl;
	var.db = desc->d;
	var.s = desc->s;
	var.l = desc->l;
	var.g = desc->g;
	var.avl = desc->avl;
	var.present = desc->p;
	var.unusable = !var.present;
	var.padding = 0;

	kvm_set_segment(vcpu, &var, seg);
	वापस;
पूर्ण

अटल पूर्णांक emulator_get_msr(काष्ठा x86_emulate_ctxt *ctxt,
			    u32 msr_index, u64 *pdata)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	पूर्णांक r;

	r = kvm_get_msr(vcpu, msr_index, pdata);

	अगर (r && kvm_get_msr_user_space(vcpu, msr_index, r)) अणु
		/* Bounce to user space */
		वापस X86EMUL_IO_NEEDED;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक emulator_set_msr(काष्ठा x86_emulate_ctxt *ctxt,
			    u32 msr_index, u64 data)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	पूर्णांक r;

	r = kvm_set_msr(vcpu, msr_index, data);

	अगर (r && kvm_set_msr_user_space(vcpu, msr_index, data, r)) अणु
		/* Bounce to user space */
		वापस X86EMUL_IO_NEEDED;
	पूर्ण

	वापस r;
पूर्ण

अटल u64 emulator_get_smbase(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);

	वापस vcpu->arch.smbase;
पूर्ण

अटल व्योम emulator_set_smbase(काष्ठा x86_emulate_ctxt *ctxt, u64 smbase)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);

	vcpu->arch.smbase = smbase;
पूर्ण

अटल पूर्णांक emulator_check_pmc(काष्ठा x86_emulate_ctxt *ctxt,
			      u32 pmc)
अणु
	वापस kvm_pmu_is_valid_rdpmc_ecx(emul_to_vcpu(ctxt), pmc);
पूर्ण

अटल पूर्णांक emulator_पढ़ो_pmc(काष्ठा x86_emulate_ctxt *ctxt,
			     u32 pmc, u64 *pdata)
अणु
	वापस kvm_pmu_rdpmc(emul_to_vcpu(ctxt), pmc, pdata);
पूर्ण

अटल व्योम emulator_halt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	emul_to_vcpu(ctxt)->arch.halt_request = 1;
पूर्ण

अटल पूर्णांक emulator_पूर्णांकercept(काष्ठा x86_emulate_ctxt *ctxt,
			      काष्ठा x86_inकाष्ठाion_info *info,
			      क्रमागत x86_पूर्णांकercept_stage stage)
अणु
	वापस अटल_call(kvm_x86_check_पूर्णांकercept)(emul_to_vcpu(ctxt), info, stage,
					    &ctxt->exception);
पूर्ण

अटल bool emulator_get_cpuid(काष्ठा x86_emulate_ctxt *ctxt,
			      u32 *eax, u32 *ebx, u32 *ecx, u32 *edx,
			      bool exact_only)
अणु
	वापस kvm_cpuid(emul_to_vcpu(ctxt), eax, ebx, ecx, edx, exact_only);
पूर्ण

अटल bool emulator_guest_has_दीर्घ_mode(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस guest_cpuid_has(emul_to_vcpu(ctxt), X86_FEATURE_LM);
पूर्ण

अटल bool emulator_guest_has_movbe(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस guest_cpuid_has(emul_to_vcpu(ctxt), X86_FEATURE_MOVBE);
पूर्ण

अटल bool emulator_guest_has_fxsr(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस guest_cpuid_has(emul_to_vcpu(ctxt), X86_FEATURE_FXSR);
पूर्ण

अटल uदीर्घ emulator_पढ़ो_gpr(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित reg)
अणु
	वापस kvm_रेजिस्टर_पढ़ो_raw(emul_to_vcpu(ctxt), reg);
पूर्ण

अटल व्योम emulator_ग_लिखो_gpr(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित reg, uदीर्घ val)
अणु
	kvm_रेजिस्टर_ग_लिखो_raw(emul_to_vcpu(ctxt), reg, val);
पूर्ण

अटल व्योम emulator_set_nmi_mask(काष्ठा x86_emulate_ctxt *ctxt, bool masked)
अणु
	अटल_call(kvm_x86_set_nmi_mask)(emul_to_vcpu(ctxt), masked);
पूर्ण

अटल अचिन्हित emulator_get_hflags(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emul_to_vcpu(ctxt)->arch.hflags;
पूर्ण

अटल व्योम emulator_set_hflags(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित emul_flags)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);

	vcpu->arch.hflags = emul_flags;
	kvm_mmu_reset_context(vcpu);
पूर्ण

अटल पूर्णांक emulator_pre_leave_smm(काष्ठा x86_emulate_ctxt *ctxt,
				  स्थिर अक्षर *smstate)
अणु
	वापस अटल_call(kvm_x86_pre_leave_smm)(emul_to_vcpu(ctxt), smstate);
पूर्ण

अटल व्योम emulator_post_leave_smm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	kvm_smm_changed(emul_to_vcpu(ctxt));
पूर्ण

अटल पूर्णांक emulator_set_xcr(काष्ठा x86_emulate_ctxt *ctxt, u32 index, u64 xcr)
अणु
	वापस __kvm_set_xcr(emul_to_vcpu(ctxt), index, xcr);
पूर्ण

अटल स्थिर काष्ठा x86_emulate_ops emulate_ops = अणु
	.पढ़ो_gpr            = emulator_पढ़ो_gpr,
	.ग_लिखो_gpr           = emulator_ग_लिखो_gpr,
	.पढ़ो_std            = emulator_पढ़ो_std,
	.ग_लिखो_std           = emulator_ग_लिखो_std,
	.पढ़ो_phys           = kvm_पढ़ो_guest_phys_प्रणाली,
	.fetch               = kvm_fetch_guest_virt,
	.पढ़ो_emulated       = emulator_पढ़ो_emulated,
	.ग_लिखो_emulated      = emulator_ग_लिखो_emulated,
	.cmpxchg_emulated    = emulator_cmpxchg_emulated,
	.invlpg              = emulator_invlpg,
	.pio_in_emulated     = emulator_pio_in_emulated,
	.pio_out_emulated    = emulator_pio_out_emulated,
	.get_segment         = emulator_get_segment,
	.set_segment         = emulator_set_segment,
	.get_cached_segment_base = emulator_get_cached_segment_base,
	.get_gdt             = emulator_get_gdt,
	.get_idt	     = emulator_get_idt,
	.set_gdt             = emulator_set_gdt,
	.set_idt	     = emulator_set_idt,
	.get_cr              = emulator_get_cr,
	.set_cr              = emulator_set_cr,
	.cpl                 = emulator_get_cpl,
	.get_dr              = emulator_get_dr,
	.set_dr              = emulator_set_dr,
	.get_smbase          = emulator_get_smbase,
	.set_smbase          = emulator_set_smbase,
	.set_msr             = emulator_set_msr,
	.get_msr             = emulator_get_msr,
	.check_pmc	     = emulator_check_pmc,
	.पढ़ो_pmc            = emulator_पढ़ो_pmc,
	.halt                = emulator_halt,
	.wbinvd              = emulator_wbinvd,
	.fix_hypercall       = emulator_fix_hypercall,
	.पूर्णांकercept           = emulator_पूर्णांकercept,
	.get_cpuid           = emulator_get_cpuid,
	.guest_has_दीर्घ_mode = emulator_guest_has_दीर्घ_mode,
	.guest_has_movbe     = emulator_guest_has_movbe,
	.guest_has_fxsr      = emulator_guest_has_fxsr,
	.set_nmi_mask        = emulator_set_nmi_mask,
	.get_hflags          = emulator_get_hflags,
	.set_hflags          = emulator_set_hflags,
	.pre_leave_smm       = emulator_pre_leave_smm,
	.post_leave_smm      = emulator_post_leave_smm,
	.set_xcr             = emulator_set_xcr,
पूर्ण;

अटल व्योम toggle_पूर्णांकerruptibility(काष्ठा kvm_vcpu *vcpu, u32 mask)
अणु
	u32 पूर्णांक_shaकरोw = अटल_call(kvm_x86_get_पूर्णांकerrupt_shaकरोw)(vcpu);
	/*
	 * an sti; sti; sequence only disable पूर्णांकerrupts क्रम the first
	 * inकाष्ठाion. So, अगर the last inकाष्ठाion, be it emulated or
	 * not, left the प्रणाली with the INT_STI flag enabled, it
	 * means that the last inकाष्ठाion is an sti. We should not
	 * leave the flag on in this हाल. The same goes क्रम mov ss
	 */
	अगर (पूर्णांक_shaकरोw & mask)
		mask = 0;
	अगर (unlikely(पूर्णांक_shaकरोw || mask)) अणु
		अटल_call(kvm_x86_set_पूर्णांकerrupt_shaकरोw)(vcpu, mask);
		अगर (!mask)
			kvm_make_request(KVM_REQ_EVENT, vcpu);
	पूर्ण
पूर्ण

अटल bool inject_emulated_exception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;
	अगर (ctxt->exception.vector == PF_VECTOR)
		वापस kvm_inject_emulated_page_fault(vcpu, &ctxt->exception);

	अगर (ctxt->exception.error_code_valid)
		kvm_queue_exception_e(vcpu, ctxt->exception.vector,
				      ctxt->exception.error_code);
	अन्यथा
		kvm_queue_exception(vcpu, ctxt->exception.vector);
	वापस false;
पूर्ण

अटल काष्ठा x86_emulate_ctxt *alloc_emulate_ctxt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा x86_emulate_ctxt *ctxt;

	ctxt = kmem_cache_zalloc(x86_emulator_cache, GFP_KERNEL_ACCOUNT);
	अगर (!ctxt) अणु
		pr_err("kvm: failed to allocate vcpu's emulator\n");
		वापस शून्य;
	पूर्ण

	ctxt->vcpu = vcpu;
	ctxt->ops = &emulate_ops;
	vcpu->arch.emulate_ctxt = ctxt;

	वापस ctxt;
पूर्ण

अटल व्योम init_emulate_ctxt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;
	पूर्णांक cs_db, cs_l;

	अटल_call(kvm_x86_get_cs_db_l_bits)(vcpu, &cs_db, &cs_l);

	ctxt->gpa_available = false;
	ctxt->eflags = kvm_get_rflags(vcpu);
	ctxt->tf = (ctxt->eflags & X86_EFLAGS_TF) != 0;

	ctxt->eip = kvm_rip_पढ़ो(vcpu);
	ctxt->mode = (!is_proपंचांगode(vcpu))		? X86EMUL_MODE_REAL :
		     (ctxt->eflags & X86_EFLAGS_VM)	? X86EMUL_MODE_VM86 :
		     (cs_l && is_दीर्घ_mode(vcpu))	? X86EMUL_MODE_PROT64 :
		     cs_db				? X86EMUL_MODE_PROT32 :
							  X86EMUL_MODE_PROT16;
	BUILD_BUG_ON(HF_GUEST_MASK != X86EMUL_GUEST_MASK);
	BUILD_BUG_ON(HF_SMM_MASK != X86EMUL_SMM_MASK);
	BUILD_BUG_ON(HF_SMM_INSIDE_NMI_MASK != X86EMUL_SMM_INSIDE_NMI_MASK);

	ctxt->पूर्णांकerruptibility = 0;
	ctxt->have_exception = false;
	ctxt->exception.vector = -1;
	ctxt->perm_ok = false;

	init_decode_cache(ctxt);
	vcpu->arch.emulate_regs_need_sync_from_vcpu = false;
पूर्ण

व्योम kvm_inject_realmode_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक irq, पूर्णांक inc_eip)
अणु
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;
	पूर्णांक ret;

	init_emulate_ctxt(vcpu);

	ctxt->op_bytes = 2;
	ctxt->ad_bytes = 2;
	ctxt->_eip = ctxt->eip + inc_eip;
	ret = emulate_पूर्णांक_real(ctxt, irq);

	अगर (ret != X86EMUL_CONTINUE) अणु
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	पूर्ण अन्यथा अणु
		ctxt->eip = ctxt->_eip;
		kvm_rip_ग_लिखो(vcpu, ctxt->eip);
		kvm_set_rflags(vcpu, ctxt->eflags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_inject_realmode_पूर्णांकerrupt);

अटल पूर्णांक handle_emulation_failure(काष्ठा kvm_vcpu *vcpu, पूर्णांक emulation_type)
अणु
	++vcpu->stat.insn_emulation_fail;
	trace_kvm_emulate_insn_failed(vcpu);

	अगर (emulation_type & EMULTYPE_VMWARE_GP) अणु
		kvm_queue_exception_e(vcpu, GP_VECTOR, 0);
		वापस 1;
	पूर्ण

	अगर (emulation_type & EMULTYPE_SKIP) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस 0;
	पूर्ण

	kvm_queue_exception(vcpu, UD_VECTOR);

	अगर (!is_guest_mode(vcpu) && अटल_call(kvm_x86_get_cpl)(vcpu) == 0) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल bool reexecute_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
				  bool ग_लिखो_fault_to_shaकरोw_pgtable,
				  पूर्णांक emulation_type)
अणु
	gpa_t gpa = cr2_or_gpa;
	kvm_pfn_t pfn;

	अगर (!(emulation_type & EMULTYPE_ALLOW_RETRY_PF))
		वापस false;

	अगर (WARN_ON_ONCE(is_guest_mode(vcpu)) ||
	    WARN_ON_ONCE(!(emulation_type & EMULTYPE_PF)))
		वापस false;

	अगर (!vcpu->arch.mmu->direct_map) अणु
		/*
		 * Write permission should be allowed since only
		 * ग_लिखो access need to be emulated.
		 */
		gpa = kvm_mmu_gva_to_gpa_ग_लिखो(vcpu, cr2_or_gpa, शून्य);

		/*
		 * If the mapping is invalid in guest, let cpu retry
		 * it to generate fault.
		 */
		अगर (gpa == UNMAPPED_GVA)
			वापस true;
	पूर्ण

	/*
	 * Do not retry the unhandleable inकाष्ठाion अगर it faults on the
	 * पढ़ोonly host memory, otherwise it will जाओ a infinite loop:
	 * retry inकाष्ठाion -> ग_लिखो #PF -> emulation fail -> retry
	 * inकाष्ठाion -> ...
	 */
	pfn = gfn_to_pfn(vcpu->kvm, gpa_to_gfn(gpa));

	/*
	 * If the inकाष्ठाion failed on the error pfn, it can not be fixed,
	 * report the error to userspace.
	 */
	अगर (is_error_noslot_pfn(pfn))
		वापस false;

	kvm_release_pfn_clean(pfn);

	/* The inकाष्ठाions are well-emulated on direct mmu. */
	अगर (vcpu->arch.mmu->direct_map) अणु
		अचिन्हित पूर्णांक indirect_shaकरोw_pages;

		ग_लिखो_lock(&vcpu->kvm->mmu_lock);
		indirect_shaकरोw_pages = vcpu->kvm->arch.indirect_shaकरोw_pages;
		ग_लिखो_unlock(&vcpu->kvm->mmu_lock);

		अगर (indirect_shaकरोw_pages)
			kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(gpa));

		वापस true;
	पूर्ण

	/*
	 * अगर emulation was due to access to shaकरोwed page table
	 * and it failed try to unshaकरोw page and re-enter the
	 * guest to let CPU execute the inकाष्ठाion.
	 */
	kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(gpa));

	/*
	 * If the access faults on its page table, it can not
	 * be fixed by unprotecting shaकरोw page and it should
	 * be reported to userspace.
	 */
	वापस !ग_लिखो_fault_to_shaकरोw_pgtable;
पूर्ण

अटल bool retry_inकाष्ठाion(काष्ठा x86_emulate_ctxt *ctxt,
			      gpa_t cr2_or_gpa,  पूर्णांक emulation_type)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	अचिन्हित दीर्घ last_retry_eip, last_retry_addr, gpa = cr2_or_gpa;

	last_retry_eip = vcpu->arch.last_retry_eip;
	last_retry_addr = vcpu->arch.last_retry_addr;

	/*
	 * If the emulation is caused by #PF and it is non-page_table
	 * writing inकाष्ठाion, it means the VM-EXIT is caused by shaकरोw
	 * page रक्षित, we can zap the shaकरोw page and retry this
	 * inकाष्ठाion directly.
	 *
	 * Note: अगर the guest uses a non-page-table modअगरying inकाष्ठाion
	 * on the PDE that poपूर्णांकs to the inकाष्ठाion, then we will unmap
	 * the inकाष्ठाion and go to an infinite loop. So, we cache the
	 * last retried eip and the last fault address, अगर we meet the eip
	 * and the address again, we can अवरोध out of the potential infinite
	 * loop.
	 */
	vcpu->arch.last_retry_eip = vcpu->arch.last_retry_addr = 0;

	अगर (!(emulation_type & EMULTYPE_ALLOW_RETRY_PF))
		वापस false;

	अगर (WARN_ON_ONCE(is_guest_mode(vcpu)) ||
	    WARN_ON_ONCE(!(emulation_type & EMULTYPE_PF)))
		वापस false;

	अगर (x86_page_table_writing_insn(ctxt))
		वापस false;

	अगर (ctxt->eip == last_retry_eip && last_retry_addr == cr2_or_gpa)
		वापस false;

	vcpu->arch.last_retry_eip = ctxt->eip;
	vcpu->arch.last_retry_addr = cr2_or_gpa;

	अगर (!vcpu->arch.mmu->direct_map)
		gpa = kvm_mmu_gva_to_gpa_ग_लिखो(vcpu, cr2_or_gpa, शून्य);

	kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(gpa));

	वापस true;
पूर्ण

अटल पूर्णांक complete_emulated_mmio(काष्ठा kvm_vcpu *vcpu);
अटल पूर्णांक complete_emulated_pio(काष्ठा kvm_vcpu *vcpu);

अटल व्योम kvm_smm_changed(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(vcpu->arch.hflags & HF_SMM_MASK)) अणु
		/* This is a good place to trace that we are निकासing SMM.  */
		trace_kvm_enter_smm(vcpu->vcpu_id, vcpu->arch.smbase, false);

		/* Process a latched INIT or SMI, अगर any.  */
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	पूर्ण

	kvm_mmu_reset_context(vcpu);
पूर्ण

अटल पूर्णांक kvm_vcpu_check_hw_bp(अचिन्हित दीर्घ addr, u32 type, u32 dr7,
				अचिन्हित दीर्घ *db)
अणु
	u32 dr6 = 0;
	पूर्णांक i;
	u32 enable, rwlen;

	enable = dr7;
	rwlen = dr7 >> 16;
	क्रम (i = 0; i < 4; i++, enable >>= 2, rwlen >>= 4)
		अगर ((enable & 3) && (rwlen & 15) == type && db[i] == addr)
			dr6 |= (1 << i);
	वापस dr6;
पूर्ण

अटल पूर्णांक kvm_vcpu_करो_singlestep(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;

	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) अणु
		kvm_run->debug.arch.dr6 = DR6_BS | DR6_ACTIVE_LOW;
		kvm_run->debug.arch.pc = kvm_get_linear_rip(vcpu);
		kvm_run->debug.arch.exception = DB_VECTOR;
		kvm_run->निकास_reason = KVM_EXIT_DEBUG;
		वापस 0;
	पूर्ण
	kvm_queue_exception_p(vcpu, DB_VECTOR, DR6_BS);
	वापस 1;
पूर्ण

पूर्णांक kvm_skip_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ rflags = अटल_call(kvm_x86_get_rflags)(vcpu);
	पूर्णांक r;

	r = अटल_call(kvm_x86_skip_emulated_inकाष्ठाion)(vcpu);
	अगर (unlikely(!r))
		वापस 0;

	/*
	 * rflags is the old, "raw" value of the flags.  The new value has
	 * not been saved yet.
	 *
	 * This is correct even क्रम TF set by the guest, because "the
	 * processor will not generate this exception after the inकाष्ठाion
	 * that sets the TF flag".
	 */
	अगर (unlikely(rflags & X86_EFLAGS_TF))
		r = kvm_vcpu_करो_singlestep(vcpu);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_skip_emulated_inकाष्ठाion);

अटल bool kvm_vcpu_check_अवरोधpoपूर्णांक(काष्ठा kvm_vcpu *vcpu, पूर्णांक *r)
अणु
	अगर (unlikely(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP) &&
	    (vcpu->arch.guest_debug_dr7 & DR7_BP_EN_MASK)) अणु
		काष्ठा kvm_run *kvm_run = vcpu->run;
		अचिन्हित दीर्घ eip = kvm_get_linear_rip(vcpu);
		u32 dr6 = kvm_vcpu_check_hw_bp(eip, 0,
					   vcpu->arch.guest_debug_dr7,
					   vcpu->arch.eff_db);

		अगर (dr6 != 0) अणु
			kvm_run->debug.arch.dr6 = dr6 | DR6_ACTIVE_LOW;
			kvm_run->debug.arch.pc = eip;
			kvm_run->debug.arch.exception = DB_VECTOR;
			kvm_run->निकास_reason = KVM_EXIT_DEBUG;
			*r = 0;
			वापस true;
		पूर्ण
	पूर्ण

	अगर (unlikely(vcpu->arch.dr7 & DR7_BP_EN_MASK) &&
	    !(kvm_get_rflags(vcpu) & X86_EFLAGS_RF)) अणु
		अचिन्हित दीर्घ eip = kvm_get_linear_rip(vcpu);
		u32 dr6 = kvm_vcpu_check_hw_bp(eip, 0,
					   vcpu->arch.dr7,
					   vcpu->arch.db);

		अगर (dr6 != 0) अणु
			kvm_queue_exception_p(vcpu, DB_VECTOR, dr6);
			*r = 1;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool is_vmware_backकरोor_opcode(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	चयन (ctxt->opcode_len) अणु
	हाल 1:
		चयन (ctxt->b) अणु
		हाल 0xe4:	/* IN */
		हाल 0xe5:
		हाल 0xec:
		हाल 0xed:
		हाल 0xe6:	/* OUT */
		हाल 0xe7:
		हाल 0xee:
		हाल 0xef:
		हाल 0x6c:	/* INS */
		हाल 0x6d:
		हाल 0x6e:	/* OUTS */
		हाल 0x6f:
			वापस true;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (ctxt->b) अणु
		हाल 0x33:	/* RDPMC */
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Decode to be emulated inकाष्ठाion. Return EMULATION_OK अगर success.
 */
पूर्णांक x86_decode_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, पूर्णांक emulation_type,
				    व्योम *insn, पूर्णांक insn_len)
अणु
	पूर्णांक r = EMULATION_OK;
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;

	init_emulate_ctxt(vcpu);

	/*
	 * We will reenter on the same inकाष्ठाion since we करो not set
	 * complete_userspace_io. This करोes not handle watchpoपूर्णांकs yet,
	 * those would be handled in the emulate_ops.
	 */
	अगर (!(emulation_type & EMULTYPE_SKIP) &&
	    kvm_vcpu_check_अवरोधpoपूर्णांक(vcpu, &r))
		वापस r;

	r = x86_decode_insn(ctxt, insn, insn_len, emulation_type);

	trace_kvm_emulate_insn_start(vcpu);
	++vcpu->stat.insn_emulation;

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(x86_decode_emulated_inकाष्ठाion);

पूर्णांक x86_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
			    पूर्णांक emulation_type, व्योम *insn, पूर्णांक insn_len)
अणु
	पूर्णांक r;
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;
	bool ग_लिखोback = true;
	bool ग_लिखो_fault_to_spt;

	अगर (unlikely(!अटल_call(kvm_x86_can_emulate_inकाष्ठाion)(vcpu, insn, insn_len)))
		वापस 1;

	vcpu->arch.l1tf_flush_l1d = true;

	/*
	 * Clear ग_लिखो_fault_to_shaकरोw_pgtable here to ensure it is
	 * never reused.
	 */
	ग_लिखो_fault_to_spt = vcpu->arch.ग_लिखो_fault_to_shaकरोw_pgtable;
	vcpu->arch.ग_लिखो_fault_to_shaकरोw_pgtable = false;

	अगर (!(emulation_type & EMULTYPE_NO_DECODE)) अणु
		kvm_clear_exception_queue(vcpu);

		r = x86_decode_emulated_inकाष्ठाion(vcpu, emulation_type,
						    insn, insn_len);
		अगर (r != EMULATION_OK)  अणु
			अगर ((emulation_type & EMULTYPE_TRAP_UD) ||
			    (emulation_type & EMULTYPE_TRAP_UD_FORCED)) अणु
				kvm_queue_exception(vcpu, UD_VECTOR);
				वापस 1;
			पूर्ण
			अगर (reexecute_inकाष्ठाion(vcpu, cr2_or_gpa,
						  ग_लिखो_fault_to_spt,
						  emulation_type))
				वापस 1;
			अगर (ctxt->have_exception) अणु
				/*
				 * #UD should result in just EMULATION_FAILED, and trap-like
				 * exception should not be encountered during decode.
				 */
				WARN_ON_ONCE(ctxt->exception.vector == UD_VECTOR ||
					     exception_type(ctxt->exception.vector) == EXCPT_TRAP);
				inject_emulated_exception(vcpu);
				वापस 1;
			पूर्ण
			वापस handle_emulation_failure(vcpu, emulation_type);
		पूर्ण
	पूर्ण

	अगर ((emulation_type & EMULTYPE_VMWARE_GP) &&
	    !is_vmware_backकरोor_opcode(ctxt)) अणु
		kvm_queue_exception_e(vcpu, GP_VECTOR, 0);
		वापस 1;
	पूर्ण

	/*
	 * Note, EMULTYPE_SKIP is पूर्णांकended क्रम use *only* by venकरोr callbacks
	 * क्रम kvm_skip_emulated_inकाष्ठाion().  The caller is responsible क्रम
	 * updating पूर्णांकerruptibility state and injecting single-step #DBs.
	 */
	अगर (emulation_type & EMULTYPE_SKIP) अणु
		kvm_rip_ग_लिखो(vcpu, ctxt->_eip);
		अगर (ctxt->eflags & X86_EFLAGS_RF)
			kvm_set_rflags(vcpu, ctxt->eflags & ~X86_EFLAGS_RF);
		वापस 1;
	पूर्ण

	अगर (retry_inकाष्ठाion(ctxt, cr2_or_gpa, emulation_type))
		वापस 1;

	/* this is needed क्रम vmware backकरोor पूर्णांकerface to work since it
	   changes रेजिस्टरs values  during IO operation */
	अगर (vcpu->arch.emulate_regs_need_sync_from_vcpu) अणु
		vcpu->arch.emulate_regs_need_sync_from_vcpu = false;
		emulator_invalidate_रेजिस्टर_cache(ctxt);
	पूर्ण

restart:
	अगर (emulation_type & EMULTYPE_PF) अणु
		/* Save the faulting GPA (cr2) in the address field */
		ctxt->exception.address = cr2_or_gpa;

		/* With shaकरोw page tables, cr2 contains a GVA or nGPA. */
		अगर (vcpu->arch.mmu->direct_map) अणु
			ctxt->gpa_available = true;
			ctxt->gpa_val = cr2_or_gpa;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Sanitize the address out of an abundance of paranoia. */
		ctxt->exception.address = 0;
	पूर्ण

	r = x86_emulate_insn(ctxt);

	अगर (r == EMULATION_INTERCEPTED)
		वापस 1;

	अगर (r == EMULATION_FAILED) अणु
		अगर (reexecute_inकाष्ठाion(vcpu, cr2_or_gpa, ग_लिखो_fault_to_spt,
					emulation_type))
			वापस 1;

		वापस handle_emulation_failure(vcpu, emulation_type);
	पूर्ण

	अगर (ctxt->have_exception) अणु
		r = 1;
		अगर (inject_emulated_exception(vcpu))
			वापस r;
	पूर्ण अन्यथा अगर (vcpu->arch.pio.count) अणु
		अगर (!vcpu->arch.pio.in) अणु
			/* FIXME: वापस पूर्णांकo emulator अगर single-stepping.  */
			vcpu->arch.pio.count = 0;
		पूर्ण अन्यथा अणु
			ग_लिखोback = false;
			vcpu->arch.complete_userspace_io = complete_emulated_pio;
		पूर्ण
		r = 0;
	पूर्ण अन्यथा अगर (vcpu->mmio_needed) अणु
		++vcpu->stat.mmio_निकासs;

		अगर (!vcpu->mmio_is_ग_लिखो)
			ग_लिखोback = false;
		r = 0;
		vcpu->arch.complete_userspace_io = complete_emulated_mmio;
	पूर्ण अन्यथा अगर (r == EMULATION_RESTART)
		जाओ restart;
	अन्यथा
		r = 1;

	अगर (ग_लिखोback) अणु
		अचिन्हित दीर्घ rflags = अटल_call(kvm_x86_get_rflags)(vcpu);
		toggle_पूर्णांकerruptibility(vcpu, ctxt->पूर्णांकerruptibility);
		vcpu->arch.emulate_regs_need_sync_to_vcpu = false;
		अगर (!ctxt->have_exception ||
		    exception_type(ctxt->exception.vector) == EXCPT_TRAP) अणु
			kvm_rip_ग_लिखो(vcpu, ctxt->eip);
			अगर (r && (ctxt->tf || (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)))
				r = kvm_vcpu_करो_singlestep(vcpu);
			अगर (kvm_x86_ops.update_emulated_inकाष्ठाion)
				अटल_call(kvm_x86_update_emulated_inकाष्ठाion)(vcpu);
			__kvm_set_rflags(vcpu, ctxt->eflags);
		पूर्ण

		/*
		 * For STI, पूर्णांकerrupts are shaकरोwed; so KVM_REQ_EVENT will
		 * करो nothing, and it will be requested again as soon as
		 * the shaकरोw expires.  But we still need to check here,
		 * because POPF has no पूर्णांकerrupt shaकरोw.
		 */
		अगर (unlikely((ctxt->eflags & ~rflags) & X86_EFLAGS_IF))
			kvm_make_request(KVM_REQ_EVENT, vcpu);
	पूर्ण अन्यथा
		vcpu->arch.emulate_regs_need_sync_to_vcpu = true;

	वापस r;
पूर्ण

पूर्णांक kvm_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, पूर्णांक emulation_type)
अणु
	वापस x86_emulate_inकाष्ठाion(vcpu, 0, emulation_type, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_inकाष्ठाion);

पूर्णांक kvm_emulate_inकाष्ठाion_from_buffer(काष्ठा kvm_vcpu *vcpu,
					व्योम *insn, पूर्णांक insn_len)
अणु
	वापस x86_emulate_inकाष्ठाion(vcpu, 0, 0, insn, insn_len);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_inकाष्ठाion_from_buffer);

अटल पूर्णांक complete_fast_pio_out_port_0x7e(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.pio.count = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक complete_fast_pio_out(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.pio.count = 0;

	अगर (unlikely(!kvm_is_linear_rip(vcpu, vcpu->arch.pio.linear_rip)))
		वापस 1;

	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक kvm_fast_pio_out(काष्ठा kvm_vcpu *vcpu, पूर्णांक size,
			    अचिन्हित लघु port)
अणु
	अचिन्हित दीर्घ val = kvm_rax_पढ़ो(vcpu);
	पूर्णांक ret = emulator_pio_out(vcpu, size, port, &val, 1);

	अगर (ret)
		वापस ret;

	/*
	 * Workaround userspace that relies on old KVM behavior of %rip being
	 * incremented prior to निकासing to userspace to handle "OUT 0x7e".
	 */
	अगर (port == 0x7e &&
	    kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_OUT_7E_INC_RIP)) अणु
		vcpu->arch.complete_userspace_io =
			complete_fast_pio_out_port_0x7e;
		kvm_skip_emulated_inकाष्ठाion(vcpu);
	पूर्ण अन्यथा अणु
		vcpu->arch.pio.linear_rip = kvm_get_linear_rip(vcpu);
		vcpu->arch.complete_userspace_io = complete_fast_pio_out;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक complete_fast_pio_in(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ val;

	/* We should only ever be called with arch.pio.count equal to 1 */
	BUG_ON(vcpu->arch.pio.count != 1);

	अगर (unlikely(!kvm_is_linear_rip(vcpu, vcpu->arch.pio.linear_rip))) अणु
		vcpu->arch.pio.count = 0;
		वापस 1;
	पूर्ण

	/* For size less than 4 we merge, अन्यथा we zero extend */
	val = (vcpu->arch.pio.size < 4) ? kvm_rax_पढ़ो(vcpu) : 0;

	/*
	 * Since vcpu->arch.pio.count == 1 let emulator_pio_in perक्रमm
	 * the copy and tracing
	 */
	emulator_pio_in(vcpu, vcpu->arch.pio.size, vcpu->arch.pio.port, &val, 1);
	kvm_rax_ग_लिखो(vcpu, val);

	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक kvm_fast_pio_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक size,
			   अचिन्हित लघु port)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	/* For size less than 4 we merge, अन्यथा we zero extend */
	val = (size < 4) ? kvm_rax_पढ़ो(vcpu) : 0;

	ret = emulator_pio_in(vcpu, size, port, &val, 1);
	अगर (ret) अणु
		kvm_rax_ग_लिखो(vcpu, val);
		वापस ret;
	पूर्ण

	vcpu->arch.pio.linear_rip = kvm_get_linear_rip(vcpu);
	vcpu->arch.complete_userspace_io = complete_fast_pio_in;

	वापस 0;
पूर्ण

पूर्णांक kvm_fast_pio(काष्ठा kvm_vcpu *vcpu, पूर्णांक size, अचिन्हित लघु port, पूर्णांक in)
अणु
	पूर्णांक ret;

	अगर (in)
		ret = kvm_fast_pio_in(vcpu, size, port);
	अन्यथा
		ret = kvm_fast_pio_out(vcpu, size, port);
	वापस ret && kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_fast_pio);

अटल पूर्णांक kvmघड़ी_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	__this_cpu_ग_लिखो(cpu_tsc_khz, 0);
	वापस 0;
पूर्ण

अटल व्योम tsc_khz_changed(व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	अचिन्हित दीर्घ khz = 0;

	अगर (data)
		khz = freq->new;
	अन्यथा अगर (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		khz = cpufreq_quick_get(raw_smp_processor_id());
	अगर (!khz)
		khz = tsc_khz;
	__this_cpu_ग_लिखो(cpu_tsc_khz, khz);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल व्योम kvm_hyperv_tsc_notअगरier(व्योम)
अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list)
		kvm_make_mघड़ी_inprogress_request(kvm);

	hyperv_stop_tsc_emulation();

	/* TSC frequency always matches when on Hyper-V */
	क्रम_each_present_cpu(cpu)
		per_cpu(cpu_tsc_khz, cpu) = tsc_khz;
	kvm_max_guest_tsc_khz = tsc_khz;

	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		काष्ठा kvm_arch *ka = &kvm->arch;

		spin_lock_irqsave(&ka->pvघड़ी_gtod_sync_lock, flags);
		pvघड़ी_update_vm_gtod_copy(kvm);
		spin_unlock_irqrestore(&ka->pvघड़ी_gtod_sync_lock, flags);

		kvm_क्रम_each_vcpu(cpu, vcpu, kvm)
			kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);

		kvm_क्रम_each_vcpu(cpu, vcpu, kvm)
			kvm_clear_request(KVM_REQ_MCLOCK_INPROGRESS, vcpu);
	पूर्ण
	mutex_unlock(&kvm_lock);
पूर्ण
#पूर्ण_अगर

अटल व्योम __kvmघड़ी_cpufreq_notअगरier(काष्ठा cpufreq_freqs *freq, पूर्णांक cpu)
अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, send_ipi = 0;

	/*
	 * We allow guests to temporarily run on slowing घड़ीs,
	 * provided we notअगरy them after, or to run on accelerating
	 * घड़ीs, provided we notअगरy them beक्रमe.  Thus समय never
	 * goes backwards.
	 *
	 * However, we have a problem.  We can't atomically update
	 * the frequency of a given CPU from this function; it is
	 * merely a notअगरier, which can be called from any CPU.
	 * Changing the TSC frequency at arbitrary poपूर्णांकs in समय
	 * requires a recomputation of local variables related to
	 * the TSC क्रम each VCPU.  We must flag these local variables
	 * to be updated and be sure the update takes place with the
	 * new frequency beक्रमe any guests proceed.
	 *
	 * Unक्रमtunately, the combination of hotplug CPU and frequency
	 * change creates an पूर्णांकractable locking scenario; the order
	 * of when these callouts happen is undefined with respect to
	 * CPU hotplug, and they can race with each other.  As such,
	 * merely setting per_cpu(cpu_tsc_khz) = X during a hotadd is
	 * undefined; you can actually have a CPU frequency change take
	 * place in between the computation of X and the setting of the
	 * variable.  To protect against this problem, all updates of
	 * the per_cpu tsc_khz variable are करोne in an पूर्णांकerrupt
	 * रक्षित IPI, and all callers wishing to update the value
	 * must रुको क्रम a synchronous IPI to complete (which is trivial
	 * अगर the caller is on the CPU alपढ़ोy).  This establishes the
	 * necessary total order on variable updates.
	 *
	 * Note that because a guest समय update may take place
	 * anyसमय after the setting of the VCPU's request bit, the
	 * correct TSC value must be set beक्रमe the request.  However,
	 * to ensure the update actually makes it to any guest which
	 * starts running in hardware भवization between the set
	 * and the acquisition of the spinlock, we must also ping the
	 * CPU after setting the request bit.
	 *
	 */

	smp_call_function_single(cpu, tsc_khz_changed, freq, 1);

	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			अगर (vcpu->cpu != cpu)
				जारी;
			kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
			अगर (vcpu->cpu != raw_smp_processor_id())
				send_ipi = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&kvm_lock);

	अगर (freq->old < freq->new && send_ipi) अणु
		/*
		 * We upscale the frequency.  Must make the guest
		 * करोesn't see old kvmघड़ी values जबतक running with
		 * the new frequency, otherwise we risk the guest sees
		 * समय go backwards.
		 *
		 * In हाल we update the frequency क्रम another cpu
		 * (which might be in guest context) send an पूर्णांकerrupt
		 * to kick the cpu out of guest context.  Next समय
		 * guest context is entered kvmघड़ी will be updated,
		 * so the guest will not see stale values.
		 */
		smp_call_function_single(cpu, tsc_khz_changed, freq, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmघड़ी_cpufreq_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				     व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	पूर्णांक cpu;

	अगर (val == CPUFREQ_PRECHANGE && freq->old > freq->new)
		वापस 0;
	अगर (val == CPUFREQ_POSTCHANGE && freq->old < freq->new)
		वापस 0;

	क्रम_each_cpu(cpu, freq->policy->cpus)
		__kvmघड़ी_cpufreq_notअगरier(freq, cpu);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block kvmघड़ी_cpufreq_notअगरier_block = अणु
	.notअगरier_call  = kvmघड़ी_cpufreq_notअगरier
पूर्ण;

अटल पूर्णांक kvmघड़ी_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	tsc_khz_changed(शून्य);
	वापस 0;
पूर्ण

अटल व्योम kvm_समयr_init(व्योम)
अणु
	max_tsc_khz = tsc_khz;

	अगर (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC)) अणु
#अगर_घोषित CONFIG_CPU_FREQ
		काष्ठा cpufreq_policy *policy;
		पूर्णांक cpu;

		cpu = get_cpu();
		policy = cpufreq_cpu_get(cpu);
		अगर (policy) अणु
			अगर (policy->cpuinfo.max_freq)
				max_tsc_khz = policy->cpuinfo.max_freq;
			cpufreq_cpu_put(policy);
		पूर्ण
		put_cpu();
#पूर्ण_अगर
		cpufreq_रेजिस्टर_notअगरier(&kvmघड़ी_cpufreq_notअगरier_block,
					  CPUFREQ_TRANSITION_NOTIFIER);
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_X86_KVM_CLK_ONLINE, "x86/kvm/clk:online",
			  kvmघड़ी_cpu_online, kvmघड़ी_cpu_करोwn_prep);
पूर्ण

DEFINE_PER_CPU(काष्ठा kvm_vcpu *, current_vcpu);
EXPORT_PER_CPU_SYMBOL_GPL(current_vcpu);

पूर्णांक kvm_is_in_guest(व्योम)
अणु
	वापस __this_cpu_पढ़ो(current_vcpu) != शून्य;
पूर्ण

अटल पूर्णांक kvm_is_user_mode(व्योम)
अणु
	पूर्णांक user_mode = 3;

	अगर (__this_cpu_पढ़ो(current_vcpu))
		user_mode = अटल_call(kvm_x86_get_cpl)(__this_cpu_पढ़ो(current_vcpu));

	वापस user_mode != 0;
पूर्ण

अटल अचिन्हित दीर्घ kvm_get_guest_ip(व्योम)
अणु
	अचिन्हित दीर्घ ip = 0;

	अगर (__this_cpu_पढ़ो(current_vcpu))
		ip = kvm_rip_पढ़ो(__this_cpu_पढ़ो(current_vcpu));

	वापस ip;
पूर्ण

अटल व्योम kvm_handle_पूर्णांकel_pt_पूर्णांकr(व्योम)
अणु
	काष्ठा kvm_vcpu *vcpu = __this_cpu_पढ़ो(current_vcpu);

	kvm_make_request(KVM_REQ_PMI, vcpu);
	__set_bit(MSR_CORE_PERF_GLOBAL_OVF_CTRL_TRACE_TOPA_PMI_BIT,
			(अचिन्हित दीर्घ *)&vcpu->arch.pmu.global_status);
पूर्ण

अटल काष्ठा perf_guest_info_callbacks kvm_guest_cbs = अणु
	.is_in_guest		= kvm_is_in_guest,
	.is_user_mode		= kvm_is_user_mode,
	.get_guest_ip		= kvm_get_guest_ip,
	.handle_पूर्णांकel_pt_पूर्णांकr	= kvm_handle_पूर्णांकel_pt_पूर्णांकr,
पूर्ण;

#अगर_घोषित CONFIG_X86_64
अटल व्योम pvघड़ी_gtod_update_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvm *kvm;

	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	mutex_lock(&kvm_lock);
	list_क्रम_each_entry(kvm, &vm_list, vm_list)
		kvm_क्रम_each_vcpu(i, vcpu, kvm)
			kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);
	atomic_set(&kvm_guest_has_master_घड़ी, 0);
	mutex_unlock(&kvm_lock);
पूर्ण

अटल DECLARE_WORK(pvघड़ी_gtod_work, pvघड़ी_gtod_update_fn);

/*
 * Indirection to move queue_work() out of the tk_core.seq ग_लिखो held
 * region to prevent possible deadlocks against समय accessors which
 * are invoked with work related locks held.
 */
अटल व्योम pvघड़ी_irq_work_fn(काष्ठा irq_work *w)
अणु
	queue_work(प्रणाली_दीर्घ_wq, &pvघड़ी_gtod_work);
पूर्ण

अटल DEFINE_IRQ_WORK(pvघड़ी_irq_work, pvघड़ी_irq_work_fn);

/*
 * Notअगरication about pvघड़ी gtod data update.
 */
अटल पूर्णांक pvघड़ी_gtod_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ unused,
			       व्योम *priv)
अणु
	काष्ठा pvघड़ी_gtod_data *gtod = &pvघड़ी_gtod_data;
	काष्ठा समयkeeper *tk = priv;

	update_pvघड़ी_gtod(tk);

	/*
	 * Disable master घड़ी अगर host करोes not trust, or करोes not use,
	 * TSC based घड़ीsource. Delegate queue_work() to irq_work as
	 * this is invoked with tk_core.seq ग_लिखो held.
	 */
	अगर (!gtod_is_based_on_tsc(gtod->घड़ी.vघड़ी_mode) &&
	    atomic_पढ़ो(&kvm_guest_has_master_घड़ी) != 0)
		irq_work_queue(&pvघड़ी_irq_work);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pvघड़ी_gtod_notअगरier = अणु
	.notअगरier_call = pvघड़ी_gtod_notअगरy,
पूर्ण;
#पूर्ण_अगर

पूर्णांक kvm_arch_init(व्योम *opaque)
अणु
	काष्ठा kvm_x86_init_ops *ops = opaque;
	पूर्णांक r;

	अगर (kvm_x86_ops.hardware_enable) अणु
		prपूर्णांकk(KERN_ERR "kvm: already loaded the other module\n");
		r = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (!ops->cpu_has_kvm_support()) अणु
		pr_err_ratelimited("kvm: no hardware support\n");
		r = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (ops->disabled_by_bios()) अणु
		pr_err_ratelimited("kvm: disabled by bios\n");
		r = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/*
	 * KVM explicitly assumes that the guest has an FPU and
	 * FXSAVE/FXRSTOR. For example, the KVM_GET_FPU explicitly casts the
	 * vCPU's FPU state as a fxregs_state काष्ठा.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_FPU) || !boot_cpu_has(X86_FEATURE_FXSR)) अणु
		prपूर्णांकk(KERN_ERR "kvm: inadequate fpu\n");
		r = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	r = -ENOMEM;
	x86_fpu_cache = kmem_cache_create("x86_fpu", माप(काष्ठा fpu),
					  __alignof__(काष्ठा fpu), SLAB_ACCOUNT,
					  शून्य);
	अगर (!x86_fpu_cache) अणु
		prपूर्णांकk(KERN_ERR "kvm: failed to allocate cache for x86 fpu\n");
		जाओ out;
	पूर्ण

	x86_emulator_cache = kvm_alloc_emulator_cache();
	अगर (!x86_emulator_cache) अणु
		pr_err("kvm: failed to allocate cache for x86 emulator\n");
		जाओ out_मुक्त_x86_fpu_cache;
	पूर्ण

	user_वापस_msrs = alloc_percpu(काष्ठा kvm_user_वापस_msrs);
	अगर (!user_वापस_msrs) अणु
		prपूर्णांकk(KERN_ERR "kvm: failed to allocate percpu kvm_user_return_msrs\n");
		जाओ out_मुक्त_x86_emulator_cache;
	पूर्ण
	kvm_nr_uret_msrs = 0;

	r = kvm_mmu_module_init();
	अगर (r)
		जाओ out_मुक्त_percpu;

	kvm_समयr_init();

	perf_रेजिस्टर_guest_info_callbacks(&kvm_guest_cbs);

	अगर (boot_cpu_has(X86_FEATURE_XSAVE)) अणु
		host_xcr0 = xgetbv(XCR_XFEATURE_ENABLED_MASK);
		supported_xcr0 = host_xcr0 & KVM_SUPPORTED_XCR0;
	पूर्ण

	अगर (pi_inject_समयr == -1)
		pi_inject_समयr = housekeeping_enabled(HK_FLAG_TIMER);
#अगर_घोषित CONFIG_X86_64
	pvघड़ी_gtod_रेजिस्टर_notअगरier(&pvघड़ी_gtod_notअगरier);

	अगर (hypervisor_is_type(X86_HYPER_MS_HYPERV))
		set_hv_tscchange_cb(kvm_hyperv_tsc_notअगरier);
#पूर्ण_अगर

	वापस 0;

out_मुक्त_percpu:
	मुक्त_percpu(user_वापस_msrs);
out_मुक्त_x86_emulator_cache:
	kmem_cache_destroy(x86_emulator_cache);
out_मुक्त_x86_fpu_cache:
	kmem_cache_destroy(x86_fpu_cache);
out:
	वापस r;
पूर्ण

व्योम kvm_arch_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	अगर (hypervisor_is_type(X86_HYPER_MS_HYPERV))
		clear_hv_tscchange_cb();
#पूर्ण_अगर
	kvm_lapic_निकास();
	perf_unरेजिस्टर_guest_info_callbacks(&kvm_guest_cbs);

	अगर (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		cpufreq_unरेजिस्टर_notअगरier(&kvmघड़ी_cpufreq_notअगरier_block,
					    CPUFREQ_TRANSITION_NOTIFIER);
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_X86_KVM_CLK_ONLINE);
#अगर_घोषित CONFIG_X86_64
	pvघड़ी_gtod_unरेजिस्टर_notअगरier(&pvघड़ी_gtod_notअगरier);
	irq_work_sync(&pvघड़ी_irq_work);
	cancel_work_sync(&pvघड़ी_gtod_work);
#पूर्ण_अगर
	kvm_x86_ops.hardware_enable = शून्य;
	kvm_mmu_module_निकास();
	मुक्त_percpu(user_वापस_msrs);
	kmem_cache_destroy(x86_emulator_cache);
	kmem_cache_destroy(x86_fpu_cache);
#अगर_घोषित CONFIG_KVM_XEN
	अटल_key_deferred_flush(&kvm_xen_enabled);
	WARN_ON(अटल_branch_unlikely(&kvm_xen_enabled.key));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __kvm_vcpu_halt(काष्ठा kvm_vcpu *vcpu, पूर्णांक state, पूर्णांक reason)
अणु
	++vcpu->स्थिति.सalt_निकासs;
	अगर (lapic_in_kernel(vcpu)) अणु
		vcpu->arch.mp_state = state;
		वापस 1;
	पूर्ण अन्यथा अणु
		vcpu->run->निकास_reason = reason;
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक kvm_vcpu_halt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस __kvm_vcpu_halt(vcpu, KVM_MP_STATE_HALTED, KVM_EXIT_HLT);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_halt);

पूर्णांक kvm_emulate_halt(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret = kvm_skip_emulated_inकाष्ठाion(vcpu);
	/*
	 * TODO: we might be squashing a GUESTDBG_SINGLESTEP-triggered
	 * KVM_EXIT_DEBUG here.
	 */
	वापस kvm_vcpu_halt(vcpu) && ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_halt);

पूर्णांक kvm_emulate_ap_reset_hold(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret = kvm_skip_emulated_inकाष्ठाion(vcpu);

	वापस __kvm_vcpu_halt(vcpu, KVM_MP_STATE_AP_RESET_HOLD, KVM_EXIT_AP_RESET_HOLD) && ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_ap_reset_hold);

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक kvm_pv_घड़ी_pairing(काष्ठा kvm_vcpu *vcpu, gpa_t paddr,
			        अचिन्हित दीर्घ घड़ी_प्रकारype)
अणु
	काष्ठा kvm_घड़ी_pairing घड़ी_pairing;
	काष्ठा बारpec64 ts;
	u64 cycle;
	पूर्णांक ret;

	अगर (घड़ी_प्रकारype != KVM_CLOCK_PAIRING_WALLCLOCK)
		वापस -KVM_EOPNOTSUPP;

	अगर (!kvm_get_wallसमय_and_घड़ीपढ़ो(&ts, &cycle))
		वापस -KVM_EOPNOTSUPP;

	घड़ी_pairing.sec = ts.tv_sec;
	घड़ी_pairing.nsec = ts.tv_nsec;
	घड़ी_pairing.tsc = kvm_पढ़ो_l1_tsc(vcpu, cycle);
	घड़ी_pairing.flags = 0;
	स_रखो(&घड़ी_pairing.pad, 0, माप(घड़ी_pairing.pad));

	ret = 0;
	अगर (kvm_ग_लिखो_guest(vcpu->kvm, paddr, &घड़ी_pairing,
			    माप(काष्ठा kvm_घड़ी_pairing)))
		ret = -KVM_EFAULT;

	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * kvm_pv_kick_cpu_op:  Kick a vcpu.
 *
 * @apicid - apicid of vcpu to be kicked.
 */
अटल व्योम kvm_pv_kick_cpu_op(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags, पूर्णांक apicid)
अणु
	काष्ठा kvm_lapic_irq lapic_irq;

	lapic_irq.लघुhand = APIC_DEST_NOSHORT;
	lapic_irq.dest_mode = APIC_DEST_PHYSICAL;
	lapic_irq.level = 0;
	lapic_irq.dest_id = apicid;
	lapic_irq.msi_redir_hपूर्णांक = false;

	lapic_irq.delivery_mode = APIC_DM_REMRD;
	kvm_irq_delivery_to_apic(kvm, शून्य, &lapic_irq, शून्य);
पूर्ण

bool kvm_apicv_activated(काष्ठा kvm *kvm)
अणु
	वापस (READ_ONCE(kvm->arch.apicv_inhibit_reasons) == 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apicv_activated);

व्योम kvm_apicv_init(काष्ठा kvm *kvm, bool enable)
अणु
	अगर (enable)
		clear_bit(APICV_INHIBIT_REASON_DISABLE,
			  &kvm->arch.apicv_inhibit_reasons);
	अन्यथा
		set_bit(APICV_INHIBIT_REASON_DISABLE,
			&kvm->arch.apicv_inhibit_reasons);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apicv_init);

अटल व्योम kvm_sched_yield(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ dest_id)
अणु
	काष्ठा kvm_vcpu *target = शून्य;
	काष्ठा kvm_apic_map *map;

	vcpu->stat.directed_yield_attempted++;

	अगर (single_task_running())
		जाओ no_yield;

	rcu_पढ़ो_lock();
	map = rcu_dereference(vcpu->kvm->arch.apic_map);

	अगर (likely(map) && dest_id <= map->max_apic_id && map->phys_map[dest_id])
		target = map->phys_map[dest_id]->vcpu;

	rcu_पढ़ो_unlock();

	अगर (!target || !READ_ONCE(target->पढ़ोy))
		जाओ no_yield;

	/* Ignore requests to yield to self */
	अगर (vcpu == target)
		जाओ no_yield;

	अगर (kvm_vcpu_yield_to(target) <= 0)
		जाओ no_yield;

	vcpu->stat.directed_yield_successful++;

no_yield:
	वापस;
पूर्ण

पूर्णांक kvm_emulate_hypercall(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ nr, a0, a1, a2, a3, ret;
	पूर्णांक op_64_bit;

	अगर (kvm_xen_hypercall_enabled(vcpu->kvm))
		वापस kvm_xen_hypercall(vcpu);

	अगर (kvm_hv_hypercall_enabled(vcpu))
		वापस kvm_hv_hypercall(vcpu);

	nr = kvm_rax_पढ़ो(vcpu);
	a0 = kvm_rbx_पढ़ो(vcpu);
	a1 = kvm_rcx_पढ़ो(vcpu);
	a2 = kvm_rdx_पढ़ो(vcpu);
	a3 = kvm_rsi_पढ़ो(vcpu);

	trace_kvm_hypercall(nr, a0, a1, a2, a3);

	op_64_bit = is_64_bit_mode(vcpu);
	अगर (!op_64_bit) अणु
		nr &= 0xFFFFFFFF;
		a0 &= 0xFFFFFFFF;
		a1 &= 0xFFFFFFFF;
		a2 &= 0xFFFFFFFF;
		a3 &= 0xFFFFFFFF;
	पूर्ण

	अगर (अटल_call(kvm_x86_get_cpl)(vcpu) != 0) अणु
		ret = -KVM_EPERM;
		जाओ out;
	पूर्ण

	ret = -KVM_ENOSYS;

	चयन (nr) अणु
	हाल KVM_HC_VAPIC_POLL_IRQ:
		ret = 0;
		अवरोध;
	हाल KVM_HC_KICK_CPU:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_PV_UNHALT))
			अवरोध;

		kvm_pv_kick_cpu_op(vcpu->kvm, a0, a1);
		kvm_sched_yield(vcpu, a1);
		ret = 0;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल KVM_HC_CLOCK_PAIRING:
		ret = kvm_pv_घड़ी_pairing(vcpu, a0, a1);
		अवरोध;
#पूर्ण_अगर
	हाल KVM_HC_SEND_IPI:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_PV_SEND_IPI))
			अवरोध;

		ret = kvm_pv_send_ipi(vcpu->kvm, a0, a1, a2, a3, op_64_bit);
		अवरोध;
	हाल KVM_HC_SCHED_YIELD:
		अगर (!guest_pv_has(vcpu, KVM_FEATURE_PV_SCHED_YIELD))
			अवरोध;

		kvm_sched_yield(vcpu, a0);
		ret = 0;
		अवरोध;
	शेष:
		ret = -KVM_ENOSYS;
		अवरोध;
	पूर्ण
out:
	अगर (!op_64_bit)
		ret = (u32)ret;
	kvm_rax_ग_लिखो(vcpu, ret);

	++vcpu->स्थिति.सypercalls;
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_hypercall);

अटल पूर्णांक emulator_fix_hypercall(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	काष्ठा kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	अक्षर inकाष्ठाion[3];
	अचिन्हित दीर्घ rip = kvm_rip_पढ़ो(vcpu);

	अटल_call(kvm_x86_patch_hypercall)(vcpu, inकाष्ठाion);

	वापस emulator_ग_लिखो_emulated(ctxt, rip, inकाष्ठाion, 3,
		&ctxt->exception);
पूर्ण

अटल पूर्णांक dm_request_क्रम_irq_injection(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->run->request_पूर्णांकerrupt_winकरोw &&
		likely(!pic_in_kernel(vcpu->kvm));
पूर्ण

अटल व्योम post_kvm_run_save(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;

	/*
	 * अगर_flag is obsolete and useless, so करो not bother
	 * setting it क्रम SEV-ES guests.  Userspace can just
	 * use kvm_run->पढ़ोy_क्रम_पूर्णांकerrupt_injection.
	 */
	kvm_run->अगर_flag = !vcpu->arch.guest_state_रक्षित
		&& (kvm_get_rflags(vcpu) & X86_EFLAGS_IF) != 0;

	kvm_run->cr8 = kvm_get_cr8(vcpu);
	kvm_run->apic_base = kvm_get_apic_base(vcpu);
	kvm_run->पढ़ोy_क्रम_पूर्णांकerrupt_injection =
		pic_in_kernel(vcpu->kvm) ||
		kvm_vcpu_पढ़ोy_क्रम_पूर्णांकerrupt_injection(vcpu);

	अगर (is_smm(vcpu))
		kvm_run->flags |= KVM_RUN_X86_SMM;
पूर्ण

अटल व्योम update_cr8_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक max_irr, tpr;

	अगर (!kvm_x86_ops.update_cr8_पूर्णांकercept)
		वापस;

	अगर (!lapic_in_kernel(vcpu))
		वापस;

	अगर (vcpu->arch.apicv_active)
		वापस;

	अगर (!vcpu->arch.apic->vapic_addr)
		max_irr = kvm_lapic_find_highest_irr(vcpu);
	अन्यथा
		max_irr = -1;

	अगर (max_irr != -1)
		max_irr >>= 4;

	tpr = kvm_lapic_get_cr8(vcpu);

	अटल_call(kvm_x86_update_cr8_पूर्णांकercept)(vcpu, tpr, max_irr);
पूर्ण


पूर्णांक kvm_check_nested_events(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (WARN_ON_ONCE(!is_guest_mode(vcpu)))
		वापस -EIO;

	अगर (kvm_check_request(KVM_REQ_TRIPLE_FAULT, vcpu)) अणु
		kvm_x86_ops.nested_ops->triple_fault(vcpu);
		वापस 1;
	पूर्ण

	वापस kvm_x86_ops.nested_ops->check_events(vcpu);
पूर्ण

अटल व्योम kvm_inject_exception(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.exception.error_code && !is_proपंचांगode(vcpu))
		vcpu->arch.exception.error_code = false;
	अटल_call(kvm_x86_queue_exception)(vcpu);
पूर्ण

अटल व्योम inject_pending_event(काष्ठा kvm_vcpu *vcpu, bool *req_immediate_निकास)
अणु
	पूर्णांक r;
	bool can_inject = true;

	/* try to reinject previous events अगर any */

	अगर (vcpu->arch.exception.injected) अणु
		kvm_inject_exception(vcpu);
		can_inject = false;
	पूर्ण
	/*
	 * Do not inject an NMI or पूर्णांकerrupt अगर there is a pending
	 * exception.  Exceptions and पूर्णांकerrupts are recognized at
	 * inकाष्ठाion boundaries, i.e. the start of an inकाष्ठाion.
	 * Trap-like exceptions, e.g. #DB, have higher priority than
	 * NMIs and पूर्णांकerrupts, i.e. traps are recognized beक्रमe an
	 * NMI/पूर्णांकerrupt that's pending on the same inकाष्ठाion.
	 * Fault-like exceptions, e.g. #GP and #PF, are the lowest
	 * priority, but are only generated (pended) during inकाष्ठाion
	 * execution, i.e. a pending fault-like exception means the
	 * fault occurred on the *previous* inकाष्ठाion and must be
	 * serviced prior to recognizing any new events in order to
	 * fully complete the previous inकाष्ठाion.
	 */
	अन्यथा अगर (!vcpu->arch.exception.pending) अणु
		अगर (vcpu->arch.nmi_injected) अणु
			अटल_call(kvm_x86_set_nmi)(vcpu);
			can_inject = false;
		पूर्ण अन्यथा अगर (vcpu->arch.पूर्णांकerrupt.injected) अणु
			अटल_call(kvm_x86_set_irq)(vcpu);
			can_inject = false;
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(vcpu->arch.exception.injected &&
		     vcpu->arch.exception.pending);

	/*
	 * Call check_nested_events() even अगर we reinjected a previous event
	 * in order क्रम caller to determine अगर it should require immediate-निकास
	 * from L2 to L1 due to pending L1 events which require निकास
	 * from L2 to L1.
	 */
	अगर (is_guest_mode(vcpu)) अणु
		r = kvm_check_nested_events(vcpu);
		अगर (r < 0)
			जाओ busy;
	पूर्ण

	/* try to inject new event अगर pending */
	अगर (vcpu->arch.exception.pending) अणु
		trace_kvm_inj_exception(vcpu->arch.exception.nr,
					vcpu->arch.exception.has_error_code,
					vcpu->arch.exception.error_code);

		vcpu->arch.exception.pending = false;
		vcpu->arch.exception.injected = true;

		अगर (exception_type(vcpu->arch.exception.nr) == EXCPT_FAULT)
			__kvm_set_rflags(vcpu, kvm_get_rflags(vcpu) |
					     X86_EFLAGS_RF);

		अगर (vcpu->arch.exception.nr == DB_VECTOR) अणु
			kvm_deliver_exception_payload(vcpu);
			अगर (vcpu->arch.dr7 & DR7_GD) अणु
				vcpu->arch.dr7 &= ~DR7_GD;
				kvm_update_dr7(vcpu);
			पूर्ण
		पूर्ण

		kvm_inject_exception(vcpu);
		can_inject = false;
	पूर्ण

	/*
	 * Finally, inject पूर्णांकerrupt events.  If an event cannot be injected
	 * due to architectural conditions (e.g. IF=0) a winकरोw-खोलो निकास
	 * will re-request KVM_REQ_EVENT.  Someबार however an event is pending
	 * and can architecturally be injected, but we cannot करो it right now:
	 * an पूर्णांकerrupt could have arrived just now and we have to inject it
	 * as a vmनिकास, or there could alपढ़ोy an event in the queue, which is
	 * indicated by can_inject.  In that हाल we request an immediate निकास
	 * in order to make progress and get back here क्रम another iteration.
	 * The kvm_x86_ops hooks communicate this by वापसing -EBUSY.
	 */
	अगर (vcpu->arch.smi_pending) अणु
		r = can_inject ? अटल_call(kvm_x86_smi_allowed)(vcpu, true) : -EBUSY;
		अगर (r < 0)
			जाओ busy;
		अगर (r) अणु
			vcpu->arch.smi_pending = false;
			++vcpu->arch.smi_count;
			enter_smm(vcpu);
			can_inject = false;
		पूर्ण अन्यथा
			अटल_call(kvm_x86_enable_smi_winकरोw)(vcpu);
	पूर्ण

	अगर (vcpu->arch.nmi_pending) अणु
		r = can_inject ? अटल_call(kvm_x86_nmi_allowed)(vcpu, true) : -EBUSY;
		अगर (r < 0)
			जाओ busy;
		अगर (r) अणु
			--vcpu->arch.nmi_pending;
			vcpu->arch.nmi_injected = true;
			अटल_call(kvm_x86_set_nmi)(vcpu);
			can_inject = false;
			WARN_ON(अटल_call(kvm_x86_nmi_allowed)(vcpu, true) < 0);
		पूर्ण
		अगर (vcpu->arch.nmi_pending)
			अटल_call(kvm_x86_enable_nmi_winकरोw)(vcpu);
	पूर्ण

	अगर (kvm_cpu_has_injectable_पूर्णांकr(vcpu)) अणु
		r = can_inject ? अटल_call(kvm_x86_पूर्णांकerrupt_allowed)(vcpu, true) : -EBUSY;
		अगर (r < 0)
			जाओ busy;
		अगर (r) अणु
			kvm_queue_पूर्णांकerrupt(vcpu, kvm_cpu_get_पूर्णांकerrupt(vcpu), false);
			अटल_call(kvm_x86_set_irq)(vcpu);
			WARN_ON(अटल_call(kvm_x86_पूर्णांकerrupt_allowed)(vcpu, true) < 0);
		पूर्ण
		अगर (kvm_cpu_has_injectable_पूर्णांकr(vcpu))
			अटल_call(kvm_x86_enable_irq_winकरोw)(vcpu);
	पूर्ण

	अगर (is_guest_mode(vcpu) &&
	    kvm_x86_ops.nested_ops->hv_समयr_pending &&
	    kvm_x86_ops.nested_ops->hv_समयr_pending(vcpu))
		*req_immediate_निकास = true;

	WARN_ON(vcpu->arch.exception.pending);
	वापस;

busy:
	*req_immediate_निकास = true;
	वापस;
पूर्ण

अटल व्योम process_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित limit = 2;

	/*
	 * x86 is limited to one NMI running, and one NMI pending after it.
	 * If an NMI is alपढ़ोy in progress, limit further NMIs to just one.
	 * Otherwise, allow two (and we'll inject the first one immediately).
	 */
	अगर (अटल_call(kvm_x86_get_nmi_mask)(vcpu) || vcpu->arch.nmi_injected)
		limit = 1;

	vcpu->arch.nmi_pending += atomic_xchg(&vcpu->arch.nmi_queued, 0);
	vcpu->arch.nmi_pending = min(vcpu->arch.nmi_pending, limit);
	kvm_make_request(KVM_REQ_EVENT, vcpu);
पूर्ण

अटल u32 enter_smm_get_segment_flags(काष्ठा kvm_segment *seg)
अणु
	u32 flags = 0;
	flags |= seg->g       << 23;
	flags |= seg->db      << 22;
	flags |= seg->l       << 21;
	flags |= seg->avl     << 20;
	flags |= seg->present << 15;
	flags |= seg->dpl     << 13;
	flags |= seg->s       << 12;
	flags |= seg->type    << 8;
	वापस flags;
पूर्ण

अटल व्योम enter_smm_save_seg_32(काष्ठा kvm_vcpu *vcpu, अक्षर *buf, पूर्णांक n)
अणु
	काष्ठा kvm_segment seg;
	पूर्णांक offset;

	kvm_get_segment(vcpu, &seg, n);
	put_smstate(u32, buf, 0x7fa8 + n * 4, seg.selector);

	अगर (n < 3)
		offset = 0x7f84 + n * 12;
	अन्यथा
		offset = 0x7f2c + (n - 3) * 12;

	put_smstate(u32, buf, offset + 8, seg.base);
	put_smstate(u32, buf, offset + 4, seg.limit);
	put_smstate(u32, buf, offset, enter_smm_get_segment_flags(&seg));
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल व्योम enter_smm_save_seg_64(काष्ठा kvm_vcpu *vcpu, अक्षर *buf, पूर्णांक n)
अणु
	काष्ठा kvm_segment seg;
	पूर्णांक offset;
	u16 flags;

	kvm_get_segment(vcpu, &seg, n);
	offset = 0x7e00 + n * 16;

	flags = enter_smm_get_segment_flags(&seg) >> 8;
	put_smstate(u16, buf, offset, seg.selector);
	put_smstate(u16, buf, offset + 2, flags);
	put_smstate(u32, buf, offset + 4, seg.limit);
	put_smstate(u64, buf, offset + 8, seg.base);
पूर्ण
#पूर्ण_अगर

अटल व्योम enter_smm_save_state_32(काष्ठा kvm_vcpu *vcpu, अक्षर *buf)
अणु
	काष्ठा desc_ptr dt;
	काष्ठा kvm_segment seg;
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	put_smstate(u32, buf, 0x7ffc, kvm_पढ़ो_cr0(vcpu));
	put_smstate(u32, buf, 0x7ff8, kvm_पढ़ो_cr3(vcpu));
	put_smstate(u32, buf, 0x7ff4, kvm_get_rflags(vcpu));
	put_smstate(u32, buf, 0x7ff0, kvm_rip_पढ़ो(vcpu));

	क्रम (i = 0; i < 8; i++)
		put_smstate(u32, buf, 0x7fd0 + i * 4, kvm_रेजिस्टर_पढ़ो_raw(vcpu, i));

	kvm_get_dr(vcpu, 6, &val);
	put_smstate(u32, buf, 0x7fcc, (u32)val);
	kvm_get_dr(vcpu, 7, &val);
	put_smstate(u32, buf, 0x7fc8, (u32)val);

	kvm_get_segment(vcpu, &seg, VCPU_SREG_TR);
	put_smstate(u32, buf, 0x7fc4, seg.selector);
	put_smstate(u32, buf, 0x7f64, seg.base);
	put_smstate(u32, buf, 0x7f60, seg.limit);
	put_smstate(u32, buf, 0x7f5c, enter_smm_get_segment_flags(&seg));

	kvm_get_segment(vcpu, &seg, VCPU_SREG_LDTR);
	put_smstate(u32, buf, 0x7fc0, seg.selector);
	put_smstate(u32, buf, 0x7f80, seg.base);
	put_smstate(u32, buf, 0x7f7c, seg.limit);
	put_smstate(u32, buf, 0x7f78, enter_smm_get_segment_flags(&seg));

	अटल_call(kvm_x86_get_gdt)(vcpu, &dt);
	put_smstate(u32, buf, 0x7f74, dt.address);
	put_smstate(u32, buf, 0x7f70, dt.size);

	अटल_call(kvm_x86_get_idt)(vcpu, &dt);
	put_smstate(u32, buf, 0x7f58, dt.address);
	put_smstate(u32, buf, 0x7f54, dt.size);

	क्रम (i = 0; i < 6; i++)
		enter_smm_save_seg_32(vcpu, buf, i);

	put_smstate(u32, buf, 0x7f14, kvm_पढ़ो_cr4(vcpu));

	/* revision id */
	put_smstate(u32, buf, 0x7efc, 0x00020000);
	put_smstate(u32, buf, 0x7ef8, vcpu->arch.smbase);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल व्योम enter_smm_save_state_64(काष्ठा kvm_vcpu *vcpu, अक्षर *buf)
अणु
	काष्ठा desc_ptr dt;
	काष्ठा kvm_segment seg;
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		put_smstate(u64, buf, 0x7ff8 - i * 8, kvm_रेजिस्टर_पढ़ो_raw(vcpu, i));

	put_smstate(u64, buf, 0x7f78, kvm_rip_पढ़ो(vcpu));
	put_smstate(u32, buf, 0x7f70, kvm_get_rflags(vcpu));

	kvm_get_dr(vcpu, 6, &val);
	put_smstate(u64, buf, 0x7f68, val);
	kvm_get_dr(vcpu, 7, &val);
	put_smstate(u64, buf, 0x7f60, val);

	put_smstate(u64, buf, 0x7f58, kvm_पढ़ो_cr0(vcpu));
	put_smstate(u64, buf, 0x7f50, kvm_पढ़ो_cr3(vcpu));
	put_smstate(u64, buf, 0x7f48, kvm_पढ़ो_cr4(vcpu));

	put_smstate(u32, buf, 0x7f00, vcpu->arch.smbase);

	/* revision id */
	put_smstate(u32, buf, 0x7efc, 0x00020064);

	put_smstate(u64, buf, 0x7ed0, vcpu->arch.efer);

	kvm_get_segment(vcpu, &seg, VCPU_SREG_TR);
	put_smstate(u16, buf, 0x7e90, seg.selector);
	put_smstate(u16, buf, 0x7e92, enter_smm_get_segment_flags(&seg) >> 8);
	put_smstate(u32, buf, 0x7e94, seg.limit);
	put_smstate(u64, buf, 0x7e98, seg.base);

	अटल_call(kvm_x86_get_idt)(vcpu, &dt);
	put_smstate(u32, buf, 0x7e84, dt.size);
	put_smstate(u64, buf, 0x7e88, dt.address);

	kvm_get_segment(vcpu, &seg, VCPU_SREG_LDTR);
	put_smstate(u16, buf, 0x7e70, seg.selector);
	put_smstate(u16, buf, 0x7e72, enter_smm_get_segment_flags(&seg) >> 8);
	put_smstate(u32, buf, 0x7e74, seg.limit);
	put_smstate(u64, buf, 0x7e78, seg.base);

	अटल_call(kvm_x86_get_gdt)(vcpu, &dt);
	put_smstate(u32, buf, 0x7e64, dt.size);
	put_smstate(u64, buf, 0x7e68, dt.address);

	क्रम (i = 0; i < 6; i++)
		enter_smm_save_seg_64(vcpu, buf, i);
पूर्ण
#पूर्ण_अगर

अटल व्योम enter_smm(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment cs, ds;
	काष्ठा desc_ptr dt;
	अक्षर buf[512];
	u32 cr0;

	trace_kvm_enter_smm(vcpu->vcpu_id, vcpu->arch.smbase, true);
	स_रखो(buf, 0, 512);
#अगर_घोषित CONFIG_X86_64
	अगर (guest_cpuid_has(vcpu, X86_FEATURE_LM))
		enter_smm_save_state_64(vcpu, buf);
	अन्यथा
#पूर्ण_अगर
		enter_smm_save_state_32(vcpu, buf);

	/*
	 * Give pre_enter_smm() a chance to make ISA-specअगरic changes to the
	 * vCPU state (e.g. leave guest mode) after we've saved the state पूर्णांकo
	 * the SMM state-save area.
	 */
	अटल_call(kvm_x86_pre_enter_smm)(vcpu, buf);

	vcpu->arch.hflags |= HF_SMM_MASK;
	kvm_vcpu_ग_लिखो_guest(vcpu, vcpu->arch.smbase + 0xfe00, buf, माप(buf));

	अगर (अटल_call(kvm_x86_get_nmi_mask)(vcpu))
		vcpu->arch.hflags |= HF_SMM_INSIDE_NMI_MASK;
	अन्यथा
		अटल_call(kvm_x86_set_nmi_mask)(vcpu, true);

	kvm_set_rflags(vcpu, X86_EFLAGS_FIXED);
	kvm_rip_ग_लिखो(vcpu, 0x8000);

	cr0 = vcpu->arch.cr0 & ~(X86_CR0_PE | X86_CR0_EM | X86_CR0_TS | X86_CR0_PG);
	अटल_call(kvm_x86_set_cr0)(vcpu, cr0);
	vcpu->arch.cr0 = cr0;

	अटल_call(kvm_x86_set_cr4)(vcpu, 0);

	/* Unकरोcumented: IDT limit is set to zero on entry to SMM.  */
	dt.address = dt.size = 0;
	अटल_call(kvm_x86_set_idt)(vcpu, &dt);

	kvm_set_dr(vcpu, 7, DR7_FIXED_1);

	cs.selector = (vcpu->arch.smbase >> 4) & 0xffff;
	cs.base = vcpu->arch.smbase;

	ds.selector = 0;
	ds.base = 0;

	cs.limit    = ds.limit = 0xffffffff;
	cs.type     = ds.type = 0x3;
	cs.dpl      = ds.dpl = 0;
	cs.db       = ds.db = 0;
	cs.s        = ds.s = 1;
	cs.l        = ds.l = 0;
	cs.g        = ds.g = 1;
	cs.avl      = ds.avl = 0;
	cs.present  = ds.present = 1;
	cs.unusable = ds.unusable = 0;
	cs.padding  = ds.padding = 0;

	kvm_set_segment(vcpu, &cs, VCPU_SREG_CS);
	kvm_set_segment(vcpu, &ds, VCPU_SREG_DS);
	kvm_set_segment(vcpu, &ds, VCPU_SREG_ES);
	kvm_set_segment(vcpu, &ds, VCPU_SREG_FS);
	kvm_set_segment(vcpu, &ds, VCPU_SREG_GS);
	kvm_set_segment(vcpu, &ds, VCPU_SREG_SS);

#अगर_घोषित CONFIG_X86_64
	अगर (guest_cpuid_has(vcpu, X86_FEATURE_LM))
		अटल_call(kvm_x86_set_efer)(vcpu, 0);
#पूर्ण_अगर

	kvm_update_cpuid_runसमय(vcpu);
	kvm_mmu_reset_context(vcpu);
पूर्ण

अटल व्योम process_smi(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.smi_pending = true;
	kvm_make_request(KVM_REQ_EVENT, vcpu);
पूर्ण

व्योम kvm_make_scan_ioapic_request_mask(काष्ठा kvm *kvm,
				       अचिन्हित दीर्घ *vcpu_biपंचांगap)
अणु
	cpumask_var_t cpus;

	zalloc_cpumask_var(&cpus, GFP_ATOMIC);

	kvm_make_vcpus_request_mask(kvm, KVM_REQ_SCAN_IOAPIC,
				    शून्य, vcpu_biपंचांगap, cpus);

	मुक्त_cpumask_var(cpus);
पूर्ण

व्योम kvm_make_scan_ioapic_request(काष्ठा kvm *kvm)
अणु
	kvm_make_all_cpus_request(kvm, KVM_REQ_SCAN_IOAPIC);
पूर्ण

व्योम kvm_vcpu_update_apicv(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!lapic_in_kernel(vcpu))
		वापस;

	vcpu->arch.apicv_active = kvm_apicv_activated(vcpu->kvm);
	kvm_apic_update_apicv(vcpu);
	अटल_call(kvm_x86_refresh_apicv_exec_ctrl)(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_update_apicv);

/*
 * NOTE: Do not hold any lock prior to calling this.
 *
 * In particular, kvm_request_apicv_update() expects kvm->srcu not to be
 * locked, because it calls __x86_set_memory_region() which करोes
 * synchronize_srcu(&kvm->srcu).
 */
व्योम kvm_request_apicv_update(काष्ठा kvm *kvm, bool activate, uदीर्घ bit)
अणु
	काष्ठा kvm_vcpu *except;
	अचिन्हित दीर्घ old, new, expected;

	अगर (!kvm_x86_ops.check_apicv_inhibit_reasons ||
	    !अटल_call(kvm_x86_check_apicv_inhibit_reasons)(bit))
		वापस;

	old = READ_ONCE(kvm->arch.apicv_inhibit_reasons);
	करो अणु
		expected = new = old;
		अगर (activate)
			__clear_bit(bit, &new);
		अन्यथा
			__set_bit(bit, &new);
		अगर (new == old)
			अवरोध;
		old = cmpxchg(&kvm->arch.apicv_inhibit_reasons, expected, new);
	पूर्ण जबतक (old != expected);

	अगर (!!old == !!new)
		वापस;

	trace_kvm_apicv_update_request(activate, bit);
	अगर (kvm_x86_ops.pre_update_apicv_exec_ctrl)
		अटल_call(kvm_x86_pre_update_apicv_exec_ctrl)(kvm, activate);

	/*
	 * Sending request to update APICV क्रम all other vcpus,
	 * जबतक update the calling vcpu immediately instead of
	 * रुकोing क्रम another #VMEXIT to handle the request.
	 */
	except = kvm_get_running_vcpu();
	kvm_make_all_cpus_request_except(kvm, KVM_REQ_APICV_UPDATE,
					 except);
	अगर (except)
		kvm_vcpu_update_apicv(except);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_request_apicv_update);

अटल व्योम vcpu_scan_ioapic(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_apic_present(vcpu))
		वापस;

	biपंचांगap_zero(vcpu->arch.ioapic_handled_vectors, 256);

	अगर (irqchip_split(vcpu->kvm))
		kvm_scan_ioapic_routes(vcpu, vcpu->arch.ioapic_handled_vectors);
	अन्यथा अणु
		अगर (vcpu->arch.apicv_active)
			अटल_call(kvm_x86_sync_pir_to_irr)(vcpu);
		अगर (ioapic_in_kernel(vcpu->kvm))
			kvm_ioapic_scan_entry(vcpu, vcpu->arch.ioapic_handled_vectors);
	पूर्ण

	अगर (is_guest_mode(vcpu))
		vcpu->arch.load_eoi_निकासmap_pending = true;
	अन्यथा
		kvm_make_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu);
पूर्ण

अटल व्योम vcpu_load_eoi_निकासmap(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 eoi_निकास_biपंचांगap[4];

	अगर (!kvm_apic_hw_enabled(vcpu->arch.apic))
		वापस;

	अगर (to_hv_vcpu(vcpu))
		biपंचांगap_or((uदीर्घ *)eoi_निकास_biपंचांगap,
			  vcpu->arch.ioapic_handled_vectors,
			  to_hv_synic(vcpu)->vec_biपंचांगap, 256);

	अटल_call(kvm_x86_load_eoi_निकासmap)(vcpu, eoi_निकास_biपंचांगap);
पूर्ण

व्योम kvm_arch_mmu_notअगरier_invalidate_range(काष्ठा kvm *kvm,
					    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ apic_address;

	/*
	 * The physical address of apic access page is stored in the VMCS.
	 * Update it when it becomes invalid.
	 */
	apic_address = gfn_to_hva(kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	अगर (start <= apic_address && apic_address < end)
		kvm_make_all_cpus_request(kvm, KVM_REQ_APIC_PAGE_RELOAD);
पूर्ण

व्योम kvm_vcpu_reload_apic_access_page(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!lapic_in_kernel(vcpu))
		वापस;

	अगर (!kvm_x86_ops.set_apic_access_page_addr)
		वापस;

	अटल_call(kvm_x86_set_apic_access_page_addr)(vcpu);
पूर्ण

व्योम __kvm_request_immediate_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	smp_send_reschedule(vcpu->cpu);
पूर्ण
EXPORT_SYMBOL_GPL(__kvm_request_immediate_निकास);

/*
 * Returns 1 to let vcpu_run() जारी the guest execution loop without
 * निकासing to the userspace.  Otherwise, the value will be वापसed to the
 * userspace.
 */
अटल पूर्णांक vcpu_enter_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;
	bool req_पूर्णांक_win =
		dm_request_क्रम_irq_injection(vcpu) &&
		kvm_cpu_accept_dm_पूर्णांकr(vcpu);
	fastpath_t निकास_fastpath;

	bool req_immediate_निकास = false;

	/* Forbid vmenter अगर vcpu dirty ring is soft-full */
	अगर (unlikely(vcpu->kvm->dirty_ring_size &&
		     kvm_dirty_ring_soft_full(&vcpu->dirty_ring))) अणु
		vcpu->run->निकास_reason = KVM_EXIT_सूचीTY_RING_FULL;
		trace_kvm_dirty_ring_निकास(vcpu);
		r = 0;
		जाओ out;
	पूर्ण

	अगर (kvm_request_pending(vcpu)) अणु
		अगर (kvm_check_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu)) अणु
			अगर (unlikely(!kvm_x86_ops.nested_ops->get_nested_state_pages(vcpu))) अणु
				r = 0;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_MMU_RELOAD, vcpu))
			kvm_mmu_unload(vcpu);
		अगर (kvm_check_request(KVM_REQ_MIGRATE_TIMER, vcpu))
			__kvm_migrate_समयrs(vcpu);
		अगर (kvm_check_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu))
			kvm_gen_update_masterघड़ी(vcpu->kvm);
		अगर (kvm_check_request(KVM_REQ_GLOBAL_CLOCK_UPDATE, vcpu))
			kvm_gen_kvmघड़ी_update(vcpu);
		अगर (kvm_check_request(KVM_REQ_CLOCK_UPDATE, vcpu)) अणु
			r = kvm_guest_समय_update(vcpu);
			अगर (unlikely(r))
				जाओ out;
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_MMU_SYNC, vcpu))
			kvm_mmu_sync_roots(vcpu);
		अगर (kvm_check_request(KVM_REQ_LOAD_MMU_PGD, vcpu))
			kvm_mmu_load_pgd(vcpu);
		अगर (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu)) अणु
			kvm_vcpu_flush_tlb_all(vcpu);

			/* Flushing all ASIDs flushes the current ASID... */
			kvm_clear_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu))
			kvm_vcpu_flush_tlb_current(vcpu);
		अगर (kvm_check_request(KVM_REQ_HV_TLB_FLUSH, vcpu))
			kvm_vcpu_flush_tlb_guest(vcpu);

		अगर (kvm_check_request(KVM_REQ_REPORT_TPR_ACCESS, vcpu)) अणु
			vcpu->run->निकास_reason = KVM_EXIT_TPR_ACCESS;
			r = 0;
			जाओ out;
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_TRIPLE_FAULT, vcpu)) अणु
			अगर (is_guest_mode(vcpu)) अणु
				kvm_x86_ops.nested_ops->triple_fault(vcpu);
			पूर्ण अन्यथा अणु
				vcpu->run->निकास_reason = KVM_EXIT_SHUTDOWN;
				vcpu->mmio_needed = 0;
				r = 0;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_APF_HALT, vcpu)) अणु
			/* Page is swapped out. Do synthetic halt */
			vcpu->arch.apf.halted = true;
			r = 1;
			जाओ out;
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_STEAL_UPDATE, vcpu))
			record_steal_समय(vcpu);
		अगर (kvm_check_request(KVM_REQ_SMI, vcpu))
			process_smi(vcpu);
		अगर (kvm_check_request(KVM_REQ_NMI, vcpu))
			process_nmi(vcpu);
		अगर (kvm_check_request(KVM_REQ_PMU, vcpu))
			kvm_pmu_handle_event(vcpu);
		अगर (kvm_check_request(KVM_REQ_PMI, vcpu))
			kvm_pmu_deliver_pmi(vcpu);
		अगर (kvm_check_request(KVM_REQ_IOAPIC_EOI_EXIT, vcpu)) अणु
			BUG_ON(vcpu->arch.pending_ioapic_eoi > 255);
			अगर (test_bit(vcpu->arch.pending_ioapic_eoi,
				     vcpu->arch.ioapic_handled_vectors)) अणु
				vcpu->run->निकास_reason = KVM_EXIT_IOAPIC_EOI;
				vcpu->run->eoi.vector =
						vcpu->arch.pending_ioapic_eoi;
				r = 0;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_SCAN_IOAPIC, vcpu))
			vcpu_scan_ioapic(vcpu);
		अगर (kvm_check_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu))
			vcpu_load_eoi_निकासmap(vcpu);
		अगर (kvm_check_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu))
			kvm_vcpu_reload_apic_access_page(vcpu);
		अगर (kvm_check_request(KVM_REQ_HV_CRASH, vcpu)) अणु
			vcpu->run->निकास_reason = KVM_EXIT_SYSTEM_EVENT;
			vcpu->run->प्रणाली_event.type = KVM_SYSTEM_EVENT_CRASH;
			r = 0;
			जाओ out;
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_HV_RESET, vcpu)) अणु
			vcpu->run->निकास_reason = KVM_EXIT_SYSTEM_EVENT;
			vcpu->run->प्रणाली_event.type = KVM_SYSTEM_EVENT_RESET;
			r = 0;
			जाओ out;
		पूर्ण
		अगर (kvm_check_request(KVM_REQ_HV_EXIT, vcpu)) अणु
			काष्ठा kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

			vcpu->run->निकास_reason = KVM_EXIT_HYPERV;
			vcpu->run->hyperv = hv_vcpu->निकास;
			r = 0;
			जाओ out;
		पूर्ण

		/*
		 * KVM_REQ_HV_STIMER has to be processed after
		 * KVM_REQ_CLOCK_UPDATE, because Hyper-V SynIC समयrs
		 * depend on the guest घड़ी being up-to-date
		 */
		अगर (kvm_check_request(KVM_REQ_HV_STIMER, vcpu))
			kvm_hv_process_sसमयrs(vcpu);
		अगर (kvm_check_request(KVM_REQ_APICV_UPDATE, vcpu))
			kvm_vcpu_update_apicv(vcpu);
		अगर (kvm_check_request(KVM_REQ_APF_READY, vcpu))
			kvm_check_async_pf_completion(vcpu);
		अगर (kvm_check_request(KVM_REQ_MSR_FILTER_CHANGED, vcpu))
			अटल_call(kvm_x86_msr_filter_changed)(vcpu);

		अगर (kvm_check_request(KVM_REQ_UPDATE_CPU_सूचीTY_LOGGING, vcpu))
			अटल_call(kvm_x86_update_cpu_dirty_logging)(vcpu);
	पूर्ण

	अगर (kvm_check_request(KVM_REQ_EVENT, vcpu) || req_पूर्णांक_win ||
	    kvm_xen_has_पूर्णांकerrupt(vcpu)) अणु
		++vcpu->stat.req_event;
		kvm_apic_accept_events(vcpu);
		अगर (vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED) अणु
			r = 1;
			जाओ out;
		पूर्ण

		inject_pending_event(vcpu, &req_immediate_निकास);
		अगर (req_पूर्णांक_win)
			अटल_call(kvm_x86_enable_irq_winकरोw)(vcpu);

		अगर (kvm_lapic_enabled(vcpu)) अणु
			update_cr8_पूर्णांकercept(vcpu);
			kvm_lapic_sync_to_vapic(vcpu);
		पूर्ण
	पूर्ण

	r = kvm_mmu_reload(vcpu);
	अगर (unlikely(r)) अणु
		जाओ cancel_injection;
	पूर्ण

	preempt_disable();

	अटल_call(kvm_x86_prepare_guest_चयन)(vcpu);

	/*
	 * Disable IRQs beक्रमe setting IN_GUEST_MODE.  Posted पूर्णांकerrupt
	 * IPI are then delayed after guest entry, which ensures that they
	 * result in भव पूर्णांकerrupt delivery.
	 */
	local_irq_disable();
	vcpu->mode = IN_GUEST_MODE;

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);

	/*
	 * 1) We should set ->mode beक्रमe checking ->requests.  Please see
	 * the comment in kvm_vcpu_निकासing_guest_mode().
	 *
	 * 2) For APICv, we should set ->mode beक्रमe checking PID.ON. This
	 * pairs with the memory barrier implicit in pi_test_and_set_on
	 * (see vmx_deliver_posted_पूर्णांकerrupt).
	 *
	 * 3) This also orders the ग_लिखो to mode from any पढ़ोs to the page
	 * tables करोne जबतक the VCPU is running.  Please see the comment
	 * in kvm_flush_remote_tlbs.
	 */
	smp_mb__after_srcu_पढ़ो_unlock();

	/*
	 * This handles the हाल where a posted पूर्णांकerrupt was
	 * notअगरied with kvm_vcpu_kick.
	 */
	अगर (kvm_lapic_enabled(vcpu) && vcpu->arch.apicv_active)
		अटल_call(kvm_x86_sync_pir_to_irr)(vcpu);

	अगर (kvm_vcpu_निकास_request(vcpu)) अणु
		vcpu->mode = OUTSIDE_GUEST_MODE;
		smp_wmb();
		local_irq_enable();
		preempt_enable();
		vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		r = 1;
		जाओ cancel_injection;
	पूर्ण

	अगर (req_immediate_निकास) अणु
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		अटल_call(kvm_x86_request_immediate_निकास)(vcpu);
	पूर्ण

	fpregs_निश्चित_state_consistent();
	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		चयन_fpu_वापस();

	अगर (unlikely(vcpu->arch.चयन_db_regs)) अणु
		set_debugreg(0, 7);
		set_debugreg(vcpu->arch.eff_db[0], 0);
		set_debugreg(vcpu->arch.eff_db[1], 1);
		set_debugreg(vcpu->arch.eff_db[2], 2);
		set_debugreg(vcpu->arch.eff_db[3], 3);
		set_debugreg(vcpu->arch.dr6, 6);
		vcpu->arch.चयन_db_regs &= ~KVM_DEBUGREG_RELOAD;
	पूर्ण

	क्रम (;;) अणु
		निकास_fastpath = अटल_call(kvm_x86_run)(vcpu);
		अगर (likely(निकास_fastpath != EXIT_FASTPATH_REENTER_GUEST))
			अवरोध;

                अगर (unlikely(kvm_vcpu_निकास_request(vcpu))) अणु
			निकास_fastpath = EXIT_FASTPATH_EXIT_HANDLED;
			अवरोध;
		पूर्ण

		अगर (vcpu->arch.apicv_active)
			अटल_call(kvm_x86_sync_pir_to_irr)(vcpu);
        पूर्ण

	/*
	 * Do this here beक्रमe restoring debug रेजिस्टरs on the host.  And
	 * since we करो this beक्रमe handling the vmनिकास, a DR access vmनिकास
	 * can (a) पढ़ो the correct value of the debug रेजिस्टरs, (b) set
	 * KVM_DEBUGREG_WONT_EXIT again.
	 */
	अगर (unlikely(vcpu->arch.चयन_db_regs & KVM_DEBUGREG_WONT_EXIT)) अणु
		WARN_ON(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP);
		अटल_call(kvm_x86_sync_dirty_debug_regs)(vcpu);
		kvm_update_dr0123(vcpu);
		kvm_update_dr7(vcpu);
		vcpu->arch.चयन_db_regs &= ~KVM_DEBUGREG_RELOAD;
	पूर्ण

	/*
	 * If the guest has used debug रेजिस्टरs, at least dr7
	 * will be disabled जबतक वापसing to the host.
	 * If we करोn't have active breakpoints in the host, we don't
	 * care about the messed up debug address रेजिस्टरs. But अगर
	 * we have some of them active, restore the old state.
	 */
	अगर (hw_अवरोधpoपूर्णांक_active())
		hw_अवरोधpoपूर्णांक_restore();

	vcpu->arch.last_vmentry_cpu = vcpu->cpu;
	vcpu->arch.last_guest_tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc());

	vcpu->mode = OUTSIDE_GUEST_MODE;
	smp_wmb();

	अटल_call(kvm_x86_handle_निकास_irqoff)(vcpu);

	/*
	 * Consume any pending पूर्णांकerrupts, including the possible source of
	 * VM-Exit on SVM and any ticks that occur between VM-Exit and now.
	 * An inकाष्ठाion is required after local_irq_enable() to fully unblock
	 * पूर्णांकerrupts on processors that implement an पूर्णांकerrupt shaकरोw, the
	 * stat.निकासs increment will करो nicely.
	 */
	kvm_beक्रमe_पूर्णांकerrupt(vcpu);
	local_irq_enable();
	++vcpu->stat.निकासs;
	local_irq_disable();
	kvm_after_पूर्णांकerrupt(vcpu);

	/*
	 * Wait until after servicing IRQs to account guest समय so that any
	 * ticks that occurred जबतक running the guest are properly accounted
	 * to the guest.  Waiting until IRQs are enabled degrades the accuracy
	 * of accounting via context tracking, but the loss of accuracy is
	 * acceptable क्रम all known use हालs.
	 */
	vसमय_account_guest_निकास();

	अगर (lapic_in_kernel(vcpu)) अणु
		s64 delta = vcpu->arch.apic->lapic_समयr.advance_expire_delta;
		अगर (delta != S64_MIN) अणु
			trace_kvm_रुको_lapic_expire(vcpu->vcpu_id, delta);
			vcpu->arch.apic->lapic_समयr.advance_expire_delta = S64_MIN;
		पूर्ण
	पूर्ण

	local_irq_enable();
	preempt_enable();

	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	/*
	 * Profile KVM निकास RIPs:
	 */
	अगर (unlikely(prof_on == KVM_PROFILING)) अणु
		अचिन्हित दीर्घ rip = kvm_rip_पढ़ो(vcpu);
		profile_hit(KVM_PROFILING, (व्योम *)rip);
	पूर्ण

	अगर (unlikely(vcpu->arch.tsc_always_catchup))
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);

	अगर (vcpu->arch.apic_attention)
		kvm_lapic_sync_from_vapic(vcpu);

	r = अटल_call(kvm_x86_handle_निकास)(vcpu, निकास_fastpath);
	वापस r;

cancel_injection:
	अगर (req_immediate_निकास)
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	अटल_call(kvm_x86_cancel_injection)(vcpu);
	अगर (unlikely(vcpu->arch.apic_attention))
		kvm_lapic_sync_from_vapic(vcpu);
out:
	वापस r;
पूर्ण

अटल अंतरभूत पूर्णांक vcpu_block(काष्ठा kvm *kvm, काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_arch_vcpu_runnable(vcpu) &&
	    (!kvm_x86_ops.pre_block || अटल_call(kvm_x86_pre_block)(vcpu) == 0)) अणु
		srcu_पढ़ो_unlock(&kvm->srcu, vcpu->srcu_idx);
		kvm_vcpu_block(vcpu);
		vcpu->srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);

		अगर (kvm_x86_ops.post_block)
			अटल_call(kvm_x86_post_block)(vcpu);

		अगर (!kvm_check_request(KVM_REQ_UNHALT, vcpu))
			वापस 1;
	पूर्ण

	kvm_apic_accept_events(vcpu);
	चयन(vcpu->arch.mp_state) अणु
	हाल KVM_MP_STATE_HALTED:
	हाल KVM_MP_STATE_AP_RESET_HOLD:
		vcpu->arch.pv.pv_unhalted = false;
		vcpu->arch.mp_state =
			KVM_MP_STATE_RUNNABLE;
		fallthrough;
	हाल KVM_MP_STATE_RUNNABLE:
		vcpu->arch.apf.halted = false;
		अवरोध;
	हाल KVM_MP_STATE_INIT_RECEIVED:
		अवरोध;
	शेष:
		वापस -EINTR;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_running(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_guest_mode(vcpu))
		kvm_check_nested_events(vcpu);

	वापस (vcpu->arch.mp_state == KVM_MP_STATE_RUNNABLE &&
		!vcpu->arch.apf.halted);
पूर्ण

अटल पूर्णांक vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;
	काष्ठा kvm *kvm = vcpu->kvm;

	vcpu->srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	vcpu->arch.l1tf_flush_l1d = true;

	क्रम (;;) अणु
		अगर (kvm_vcpu_running(vcpu)) अणु
			r = vcpu_enter_guest(vcpu);
		पूर्ण अन्यथा अणु
			r = vcpu_block(kvm, vcpu);
		पूर्ण

		अगर (r <= 0)
			अवरोध;

		kvm_clear_request(KVM_REQ_UNBLOCK, vcpu);
		अगर (kvm_cpu_has_pending_समयr(vcpu))
			kvm_inject_pending_समयr_irqs(vcpu);

		अगर (dm_request_क्रम_irq_injection(vcpu) &&
			kvm_vcpu_पढ़ोy_क्रम_पूर्णांकerrupt_injection(vcpu)) अणु
			r = 0;
			vcpu->run->निकास_reason = KVM_EXIT_IRQ_WINDOW_OPEN;
			++vcpu->stat.request_irq_निकासs;
			अवरोध;
		पूर्ण

		अगर (__xfer_to_guest_mode_work_pending()) अणु
			srcu_पढ़ो_unlock(&kvm->srcu, vcpu->srcu_idx);
			r = xfer_to_guest_mode_handle_work(vcpu);
			अगर (r)
				वापस r;
			vcpu->srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
		पूर्ण
	पूर्ण

	srcu_पढ़ो_unlock(&kvm->srcu, vcpu->srcu_idx);

	वापस r;
पूर्ण

अटल अंतरभूत पूर्णांक complete_emulated_io(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;

	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	r = kvm_emulate_inकाष्ठाion(vcpu, EMULTYPE_NO_DECODE);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	वापस r;
पूर्ण

अटल पूर्णांक complete_emulated_pio(काष्ठा kvm_vcpu *vcpu)
अणु
	BUG_ON(!vcpu->arch.pio.count);

	वापस complete_emulated_io(vcpu);
पूर्ण

/*
 * Implements the following, as a state machine:
 *
 * पढ़ो:
 *   क्रम each fragment
 *     क्रम each mmio piece in the fragment
 *       ग_लिखो gpa, len
 *       निकास
 *       copy data
 *   execute insn
 *
 * ग_लिखो:
 *   क्रम each fragment
 *     क्रम each mmio piece in the fragment
 *       ग_लिखो gpa, len
 *       copy data
 *       निकास
 */
अटल पूर्णांक complete_emulated_mmio(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	काष्ठा kvm_mmio_fragment *frag;
	अचिन्हित len;

	BUG_ON(!vcpu->mmio_needed);

	/* Complete previous fragment */
	frag = &vcpu->mmio_fragments[vcpu->mmio_cur_fragment];
	len = min(8u, frag->len);
	अगर (!vcpu->mmio_is_ग_लिखो)
		स_नकल(frag->data, run->mmio.data, len);

	अगर (frag->len <= 8) अणु
		/* Switch to the next fragment. */
		frag++;
		vcpu->mmio_cur_fragment++;
	पूर्ण अन्यथा अणु
		/* Go क्रमward to the next mmio piece. */
		frag->data += len;
		frag->gpa += len;
		frag->len -= len;
	पूर्ण

	अगर (vcpu->mmio_cur_fragment >= vcpu->mmio_nr_fragments) अणु
		vcpu->mmio_needed = 0;

		/* FIXME: वापस पूर्णांकo emulator अगर single-stepping.  */
		अगर (vcpu->mmio_is_ग_लिखो)
			वापस 1;
		vcpu->mmio_पढ़ो_completed = 1;
		वापस complete_emulated_io(vcpu);
	पूर्ण

	run->निकास_reason = KVM_EXIT_MMIO;
	run->mmio.phys_addr = frag->gpa;
	अगर (vcpu->mmio_is_ग_लिखो)
		स_नकल(run->mmio.data, frag->data, min(8u, frag->len));
	run->mmio.len = min(8u, frag->len);
	run->mmio.is_ग_लिखो = vcpu->mmio_is_ग_लिखो;
	vcpu->arch.complete_userspace_io = complete_emulated_mmio;
	वापस 0;
पूर्ण

अटल व्योम kvm_save_current_fpu(काष्ठा fpu *fpu)
अणु
	/*
	 * If the target FPU state is not resident in the CPU रेजिस्टरs, just
	 * स_नकल() from current, अन्यथा save CPU state directly to the target.
	 */
	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		स_नकल(&fpu->state, &current->thपढ़ो.fpu.state,
		       fpu_kernel_xstate_size);
	अन्यथा
		copy_fpregs_to_fpstate(fpu);
पूर्ण

/* Swap (qemu) user FPU context क्रम the guest FPU context. */
अटल व्योम kvm_load_guest_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	fpregs_lock();

	kvm_save_current_fpu(vcpu->arch.user_fpu);

	/*
	 * Guests with रक्षित state can't have it set by the hypervisor,
	 * so skip trying to set it.
	 */
	अगर (vcpu->arch.guest_fpu)
		/* PKRU is separately restored in kvm_x86_ops.run. */
		__copy_kernel_to_fpregs(&vcpu->arch.guest_fpu->state,
					~XFEATURE_MASK_PKRU);

	fpregs_mark_activate();
	fpregs_unlock();

	trace_kvm_fpu(1);
पूर्ण

/* When vcpu_run ends, restore user space FPU context. */
अटल व्योम kvm_put_guest_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	fpregs_lock();

	/*
	 * Guests with रक्षित state can't have it पढ़ो by the hypervisor,
	 * so skip trying to save it.
	 */
	अगर (vcpu->arch.guest_fpu)
		kvm_save_current_fpu(vcpu->arch.guest_fpu);

	copy_kernel_to_fpregs(&vcpu->arch.user_fpu->state);

	fpregs_mark_activate();
	fpregs_unlock();

	++vcpu->stat.fpu_reload;
	trace_kvm_fpu(0);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;
	पूर्णांक r;

	vcpu_load(vcpu);
	kvm_sigset_activate(vcpu);
	kvm_run->flags = 0;
	kvm_load_guest_fpu(vcpu);

	अगर (unlikely(vcpu->arch.mp_state == KVM_MP_STATE_UNINITIALIZED)) अणु
		अगर (kvm_run->immediate_निकास) अणु
			r = -EINTR;
			जाओ out;
		पूर्ण
		kvm_vcpu_block(vcpu);
		kvm_apic_accept_events(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		r = -EAGAIN;
		अगर (संकेत_pending(current)) अणु
			r = -EINTR;
			kvm_run->निकास_reason = KVM_EXIT_INTR;
			++vcpu->stat.संकेत_निकासs;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (kvm_run->kvm_valid_regs & ~KVM_SYNC_X86_VALID_FIELDS) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (kvm_run->kvm_dirty_regs) अणु
		r = sync_regs(vcpu);
		अगर (r != 0)
			जाओ out;
	पूर्ण

	/* re-sync apic's tpr */
	अगर (!lapic_in_kernel(vcpu)) अणु
		अगर (kvm_set_cr8(vcpu, kvm_run->cr8) != 0) अणु
			r = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (unlikely(vcpu->arch.complete_userspace_io)) अणु
		पूर्णांक (*cui)(काष्ठा kvm_vcpu *) = vcpu->arch.complete_userspace_io;
		vcpu->arch.complete_userspace_io = शून्य;
		r = cui(vcpu);
		अगर (r <= 0)
			जाओ out;
	पूर्ण अन्यथा
		WARN_ON(vcpu->arch.pio.count || vcpu->mmio_needed);

	अगर (kvm_run->immediate_निकास)
		r = -EINTR;
	अन्यथा
		r = vcpu_run(vcpu);

out:
	kvm_put_guest_fpu(vcpu);
	अगर (kvm_run->kvm_valid_regs)
		store_regs(vcpu);
	post_kvm_run_save(vcpu);
	kvm_sigset_deactivate(vcpu);

	vcpu_put(vcpu);
	वापस r;
पूर्ण

अटल व्योम __get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	अगर (vcpu->arch.emulate_regs_need_sync_to_vcpu) अणु
		/*
		 * We are here अगर userspace calls get_regs() in the middle of
		 * inकाष्ठाion emulation. Registers state needs to be copied
		 * back from emulation context to vcpu. Userspace shouldn't करो
		 * that usually, but some bad deचिन्हित PV devices (vmware
		 * backकरोor पूर्णांकerface) need this to work
		 */
		emulator_ग_लिखोback_रेजिस्टर_cache(vcpu->arch.emulate_ctxt);
		vcpu->arch.emulate_regs_need_sync_to_vcpu = false;
	पूर्ण
	regs->rax = kvm_rax_पढ़ो(vcpu);
	regs->rbx = kvm_rbx_पढ़ो(vcpu);
	regs->rcx = kvm_rcx_पढ़ो(vcpu);
	regs->rdx = kvm_rdx_पढ़ो(vcpu);
	regs->rsi = kvm_rsi_पढ़ो(vcpu);
	regs->rdi = kvm_rdi_पढ़ो(vcpu);
	regs->rsp = kvm_rsp_पढ़ो(vcpu);
	regs->rbp = kvm_rbp_पढ़ो(vcpu);
#अगर_घोषित CONFIG_X86_64
	regs->r8 = kvm_r8_पढ़ो(vcpu);
	regs->r9 = kvm_r9_पढ़ो(vcpu);
	regs->r10 = kvm_r10_पढ़ो(vcpu);
	regs->r11 = kvm_r11_पढ़ो(vcpu);
	regs->r12 = kvm_r12_पढ़ो(vcpu);
	regs->r13 = kvm_r13_पढ़ो(vcpu);
	regs->r14 = kvm_r14_पढ़ो(vcpu);
	regs->r15 = kvm_r15_पढ़ो(vcpu);
#पूर्ण_अगर

	regs->rip = kvm_rip_पढ़ो(vcpu);
	regs->rflags = kvm_get_rflags(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	vcpu_load(vcpu);
	__get_regs(vcpu, regs);
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

अटल व्योम __set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	vcpu->arch.emulate_regs_need_sync_from_vcpu = true;
	vcpu->arch.emulate_regs_need_sync_to_vcpu = false;

	kvm_rax_ग_लिखो(vcpu, regs->rax);
	kvm_rbx_ग_लिखो(vcpu, regs->rbx);
	kvm_rcx_ग_लिखो(vcpu, regs->rcx);
	kvm_rdx_ग_लिखो(vcpu, regs->rdx);
	kvm_rsi_ग_लिखो(vcpu, regs->rsi);
	kvm_rdi_ग_लिखो(vcpu, regs->rdi);
	kvm_rsp_ग_लिखो(vcpu, regs->rsp);
	kvm_rbp_ग_लिखो(vcpu, regs->rbp);
#अगर_घोषित CONFIG_X86_64
	kvm_r8_ग_लिखो(vcpu, regs->r8);
	kvm_r9_ग_लिखो(vcpu, regs->r9);
	kvm_r10_ग_लिखो(vcpu, regs->r10);
	kvm_r11_ग_लिखो(vcpu, regs->r11);
	kvm_r12_ग_लिखो(vcpu, regs->r12);
	kvm_r13_ग_लिखो(vcpu, regs->r13);
	kvm_r14_ग_लिखो(vcpu, regs->r14);
	kvm_r15_ग_लिखो(vcpu, regs->r15);
#पूर्ण_अगर

	kvm_rip_ग_लिखो(vcpu, regs->rip);
	kvm_set_rflags(vcpu, regs->rflags | X86_EFLAGS_FIXED);

	vcpu->arch.exception.pending = false;

	kvm_make_request(KVM_REQ_EVENT, vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs)
अणु
	vcpu_load(vcpu);
	__set_regs(vcpu, regs);
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

व्योम kvm_get_cs_db_l_bits(काष्ठा kvm_vcpu *vcpu, पूर्णांक *db, पूर्णांक *l)
अणु
	काष्ठा kvm_segment cs;

	kvm_get_segment(vcpu, &cs, VCPU_SREG_CS);
	*db = cs.db;
	*l = cs.l;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_cs_db_l_bits);

अटल व्योम __get_sregs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा desc_ptr dt;

	अगर (vcpu->arch.guest_state_रक्षित)
		जाओ skip_रक्षित_regs;

	kvm_get_segment(vcpu, &sregs->cs, VCPU_SREG_CS);
	kvm_get_segment(vcpu, &sregs->ds, VCPU_SREG_DS);
	kvm_get_segment(vcpu, &sregs->es, VCPU_SREG_ES);
	kvm_get_segment(vcpu, &sregs->fs, VCPU_SREG_FS);
	kvm_get_segment(vcpu, &sregs->gs, VCPU_SREG_GS);
	kvm_get_segment(vcpu, &sregs->ss, VCPU_SREG_SS);

	kvm_get_segment(vcpu, &sregs->tr, VCPU_SREG_TR);
	kvm_get_segment(vcpu, &sregs->ldt, VCPU_SREG_LDTR);

	अटल_call(kvm_x86_get_idt)(vcpu, &dt);
	sregs->idt.limit = dt.size;
	sregs->idt.base = dt.address;
	अटल_call(kvm_x86_get_gdt)(vcpu, &dt);
	sregs->gdt.limit = dt.size;
	sregs->gdt.base = dt.address;

	sregs->cr2 = vcpu->arch.cr2;
	sregs->cr3 = kvm_पढ़ो_cr3(vcpu);

skip_रक्षित_regs:
	sregs->cr0 = kvm_पढ़ो_cr0(vcpu);
	sregs->cr4 = kvm_पढ़ो_cr4(vcpu);
	sregs->cr8 = kvm_get_cr8(vcpu);
	sregs->efer = vcpu->arch.efer;
	sregs->apic_base = kvm_get_apic_base(vcpu);

	स_रखो(sregs->पूर्णांकerrupt_biपंचांगap, 0, माप(sregs->पूर्णांकerrupt_biपंचांगap));

	अगर (vcpu->arch.पूर्णांकerrupt.injected && !vcpu->arch.पूर्णांकerrupt.soft)
		set_bit(vcpu->arch.पूर्णांकerrupt.nr,
			(अचिन्हित दीर्घ *)sregs->पूर्णांकerrupt_biपंचांगap);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	vcpu_load(vcpu);
	__get_sregs(vcpu, sregs);
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	vcpu_load(vcpu);
	अगर (kvm_mpx_supported())
		kvm_load_guest_fpu(vcpu);

	kvm_apic_accept_events(vcpu);
	अगर ((vcpu->arch.mp_state == KVM_MP_STATE_HALTED ||
	     vcpu->arch.mp_state == KVM_MP_STATE_AP_RESET_HOLD) &&
	    vcpu->arch.pv.pv_unhalted)
		mp_state->mp_state = KVM_MP_STATE_RUNNABLE;
	अन्यथा
		mp_state->mp_state = vcpu->arch.mp_state;

	अगर (kvm_mpx_supported())
		kvm_put_guest_fpu(vcpu);
	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	पूर्णांक ret = -EINVAL;

	vcpu_load(vcpu);

	अगर (!lapic_in_kernel(vcpu) &&
	    mp_state->mp_state != KVM_MP_STATE_RUNNABLE)
		जाओ out;

	/*
	 * KVM_MP_STATE_INIT_RECEIVED means the processor is in
	 * INIT state; latched init should be reported using
	 * KVM_SET_VCPU_EVENTS, so reject it here.
	 */
	अगर ((kvm_vcpu_latch_init(vcpu) || vcpu->arch.smi_pending) &&
	    (mp_state->mp_state == KVM_MP_STATE_SIPI_RECEIVED ||
	     mp_state->mp_state == KVM_MP_STATE_INIT_RECEIVED))
		जाओ out;

	अगर (mp_state->mp_state == KVM_MP_STATE_SIPI_RECEIVED) अणु
		vcpu->arch.mp_state = KVM_MP_STATE_INIT_RECEIVED;
		set_bit(KVM_APIC_SIPI, &vcpu->arch.apic->pending_events);
	पूर्ण अन्यथा
		vcpu->arch.mp_state = mp_state->mp_state;
	kvm_make_request(KVM_REQ_EVENT, vcpu);

	ret = 0;
out:
	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_task_चयन(काष्ठा kvm_vcpu *vcpu, u16 tss_selector, पूर्णांक idt_index,
		    पूर्णांक reason, bool has_error_code, u32 error_code)
अणु
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;
	पूर्णांक ret;

	init_emulate_ctxt(vcpu);

	ret = emulator_task_चयन(ctxt, tss_selector, idt_index, reason,
				   has_error_code, error_code);
	अगर (ret) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस 0;
	पूर्ण

	kvm_rip_ग_लिखो(vcpu, ctxt->eip);
	kvm_set_rflags(vcpu, ctxt->eflags);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_task_चयन);

अटल bool kvm_is_valid_sregs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	अगर ((sregs->efer & EFER_LME) && (sregs->cr0 & X86_CR0_PG)) अणु
		/*
		 * When EFER.LME and CR0.PG are set, the processor is in
		 * 64-bit mode (though maybe in a 32-bit code segment).
		 * CR4.PAE and EFER.LMA must be set.
		 */
		अगर (!(sregs->cr4 & X86_CR4_PAE) || !(sregs->efer & EFER_LMA))
			वापस false;
		अगर (kvm_vcpu_is_illegal_gpa(vcpu, sregs->cr3))
			वापस false;
	पूर्ण अन्यथा अणु
		/*
		 * Not in 64-bit mode: EFER.LMA is clear and the code
		 * segment cannot be 64-bit.
		 */
		अगर (sregs->efer & EFER_LMA || sregs->cs.l)
			वापस false;
	पूर्ण

	वापस kvm_is_valid_cr4(vcpu, sregs->cr4);
पूर्ण

अटल पूर्णांक __set_sregs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा msr_data apic_base_msr;
	पूर्णांक mmu_reset_needed = 0;
	पूर्णांक pending_vec, max_bits, idx;
	काष्ठा desc_ptr dt;
	पूर्णांक ret = -EINVAL;

	अगर (!kvm_is_valid_sregs(vcpu, sregs))
		जाओ out;

	apic_base_msr.data = sregs->apic_base;
	apic_base_msr.host_initiated = true;
	अगर (kvm_set_apic_base(vcpu, &apic_base_msr))
		जाओ out;

	अगर (vcpu->arch.guest_state_रक्षित)
		जाओ skip_रक्षित_regs;

	dt.size = sregs->idt.limit;
	dt.address = sregs->idt.base;
	अटल_call(kvm_x86_set_idt)(vcpu, &dt);
	dt.size = sregs->gdt.limit;
	dt.address = sregs->gdt.base;
	अटल_call(kvm_x86_set_gdt)(vcpu, &dt);

	vcpu->arch.cr2 = sregs->cr2;
	mmu_reset_needed |= kvm_पढ़ो_cr3(vcpu) != sregs->cr3;
	vcpu->arch.cr3 = sregs->cr3;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR3);

	kvm_set_cr8(vcpu, sregs->cr8);

	mmu_reset_needed |= vcpu->arch.efer != sregs->efer;
	अटल_call(kvm_x86_set_efer)(vcpu, sregs->efer);

	mmu_reset_needed |= kvm_पढ़ो_cr0(vcpu) != sregs->cr0;
	अटल_call(kvm_x86_set_cr0)(vcpu, sregs->cr0);
	vcpu->arch.cr0 = sregs->cr0;

	mmu_reset_needed |= kvm_पढ़ो_cr4(vcpu) != sregs->cr4;
	अटल_call(kvm_x86_set_cr4)(vcpu, sregs->cr4);

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	अगर (is_pae_paging(vcpu)) अणु
		load_pdptrs(vcpu, vcpu->arch.walk_mmu, kvm_पढ़ो_cr3(vcpu));
		mmu_reset_needed = 1;
	पूर्ण
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	अगर (mmu_reset_needed)
		kvm_mmu_reset_context(vcpu);

	kvm_set_segment(vcpu, &sregs->cs, VCPU_SREG_CS);
	kvm_set_segment(vcpu, &sregs->ds, VCPU_SREG_DS);
	kvm_set_segment(vcpu, &sregs->es, VCPU_SREG_ES);
	kvm_set_segment(vcpu, &sregs->fs, VCPU_SREG_FS);
	kvm_set_segment(vcpu, &sregs->gs, VCPU_SREG_GS);
	kvm_set_segment(vcpu, &sregs->ss, VCPU_SREG_SS);

	kvm_set_segment(vcpu, &sregs->tr, VCPU_SREG_TR);
	kvm_set_segment(vcpu, &sregs->ldt, VCPU_SREG_LDTR);

	update_cr8_पूर्णांकercept(vcpu);

	/* Older userspace won't unhalt the vcpu on reset. */
	अगर (kvm_vcpu_is_bsp(vcpu) && kvm_rip_पढ़ो(vcpu) == 0xfff0 &&
	    sregs->cs.selector == 0xf000 && sregs->cs.base == 0xffff0000 &&
	    !is_proपंचांगode(vcpu))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;

skip_रक्षित_regs:
	max_bits = KVM_NR_INTERRUPTS;
	pending_vec = find_first_bit(
		(स्थिर अचिन्हित दीर्घ *)sregs->पूर्णांकerrupt_biपंचांगap, max_bits);
	अगर (pending_vec < max_bits) अणु
		kvm_queue_पूर्णांकerrupt(vcpu, pending_vec, false);
		pr_debug("Set back pending irq %d\n", pending_vec);
	पूर्ण

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	ret = 0;
out:
	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret;

	vcpu_load(vcpu);
	ret = __set_sregs(vcpu, sregs);
	vcpu_put(vcpu);
	वापस ret;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg)
अणु
	अचिन्हित दीर्घ rflags;
	पूर्णांक i, r;

	अगर (vcpu->arch.guest_state_रक्षित)
		वापस -EINVAL;

	vcpu_load(vcpu);

	अगर (dbg->control & (KVM_GUESTDBG_INJECT_DB | KVM_GUESTDBG_INJECT_BP)) अणु
		r = -EBUSY;
		अगर (vcpu->arch.exception.pending)
			जाओ out;
		अगर (dbg->control & KVM_GUESTDBG_INJECT_DB)
			kvm_queue_exception(vcpu, DB_VECTOR);
		अन्यथा
			kvm_queue_exception(vcpu, BP_VECTOR);
	पूर्ण

	/*
	 * Read rflags as दीर्घ as potentially injected trace flags are still
	 * filtered out.
	 */
	rflags = kvm_get_rflags(vcpu);

	vcpu->guest_debug = dbg->control;
	अगर (!(vcpu->guest_debug & KVM_GUESTDBG_ENABLE))
		vcpu->guest_debug = 0;

	अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP) अणु
		क्रम (i = 0; i < KVM_NR_DB_REGS; ++i)
			vcpu->arch.eff_db[i] = dbg->arch.debugreg[i];
		vcpu->arch.guest_debug_dr7 = dbg->arch.debugreg[7];
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < KVM_NR_DB_REGS; i++)
			vcpu->arch.eff_db[i] = vcpu->arch.db[i];
	पूर्ण
	kvm_update_dr7(vcpu);

	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		vcpu->arch.singlestep_rip = kvm_get_linear_rip(vcpu);

	/*
	 * Trigger an rflags update that will inject or हटाओ the trace
	 * flags.
	 */
	kvm_set_rflags(vcpu, rflags);

	अटल_call(kvm_x86_update_exception_biपंचांगap)(vcpu);

	r = 0;

out:
	vcpu_put(vcpu);
	वापस r;
पूर्ण

/*
 * Translate a guest भव address to a guest physical address.
 */
पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_translation *tr)
अणु
	अचिन्हित दीर्घ vaddr = tr->linear_address;
	gpa_t gpa;
	पूर्णांक idx;

	vcpu_load(vcpu);

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	gpa = kvm_mmu_gva_to_gpa_प्रणाली(vcpu, vaddr, शून्य);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
	tr->physical_address = gpa;
	tr->valid = gpa != UNMAPPED_GVA;
	tr->ग_लिखोable = 1;
	tr->usermode = 0;

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	काष्ठा fxregs_state *fxsave;

	अगर (!vcpu->arch.guest_fpu)
		वापस 0;

	vcpu_load(vcpu);

	fxsave = &vcpu->arch.guest_fpu->state.fxsave;
	स_नकल(fpu->fpr, fxsave->st_space, 128);
	fpu->fcw = fxsave->cwd;
	fpu->fsw = fxsave->swd;
	fpu->ftwx = fxsave->twd;
	fpu->last_opcode = fxsave->fop;
	fpu->last_ip = fxsave->rip;
	fpu->last_dp = fxsave->rdp;
	स_नकल(fpu->xmm, fxsave->xmm_space, माप(fxsave->xmm_space));

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu)
अणु
	काष्ठा fxregs_state *fxsave;

	अगर (!vcpu->arch.guest_fpu)
		वापस 0;

	vcpu_load(vcpu);

	fxsave = &vcpu->arch.guest_fpu->state.fxsave;

	स_नकल(fxsave->st_space, fpu->fpr, 128);
	fxsave->cwd = fpu->fcw;
	fxsave->swd = fpu->fsw;
	fxsave->twd = fpu->ftwx;
	fxsave->fop = fpu->last_opcode;
	fxsave->rip = fpu->last_ip;
	fxsave->rdp = fpu->last_dp;
	स_नकल(fxsave->xmm_space, fpu->xmm, माप(fxsave->xmm_space));

	vcpu_put(vcpu);
	वापस 0;
पूर्ण

अटल व्योम store_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	BUILD_BUG_ON(माप(काष्ठा kvm_sync_regs) > SYNC_REGS_SIZE_BYTES);

	अगर (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_REGS)
		__get_regs(vcpu, &vcpu->run->s.regs.regs);

	अगर (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_SREGS)
		__get_sregs(vcpu, &vcpu->run->s.regs.sregs);

	अगर (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_EVENTS)
		kvm_vcpu_ioctl_x86_get_vcpu_events(
				vcpu, &vcpu->run->s.regs.events);
पूर्ण

अटल पूर्णांक sync_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->run->kvm_dirty_regs & ~KVM_SYNC_X86_VALID_FIELDS)
		वापस -EINVAL;

	अगर (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_REGS) अणु
		__set_regs(vcpu, &vcpu->run->s.regs.regs);
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_REGS;
	पूर्ण
	अगर (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_SREGS) अणु
		अगर (__set_sregs(vcpu, &vcpu->run->s.regs.sregs))
			वापस -EINVAL;
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_SREGS;
	पूर्ण
	अगर (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_EVENTS) अणु
		अगर (kvm_vcpu_ioctl_x86_set_vcpu_events(
				vcpu, &vcpu->run->s.regs.events))
			वापस -EINVAL;
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_EVENTS;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fx_init(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->arch.guest_fpu)
		वापस;

	fpstate_init(&vcpu->arch.guest_fpu->state);
	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		vcpu->arch.guest_fpu->state.xsave.header.xcomp_bv =
			host_xcr0 | XSTATE_COMPACTION_ENABLED;

	/*
	 * Ensure guest xcr0 is valid क्रम loading
	 */
	vcpu->arch.xcr0 = XFEATURE_MASK_FP;

	vcpu->arch.cr0 |= X86_CR0_ET;
पूर्ण

व्योम kvm_मुक्त_guest_fpu(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.guest_fpu) अणु
		kmem_cache_मुक्त(x86_fpu_cache, vcpu->arch.guest_fpu);
		vcpu->arch.guest_fpu = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_मुक्त_guest_fpu);

पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	अगर (kvm_check_tsc_unstable() && atomic_पढ़ो(&kvm->online_vcpus) != 0)
		pr_warn_once("kvm: SMP vm created on host with unstable TSC; "
			     "guest TSC will not be reliable\n");

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा page *page;
	पूर्णांक r;

	अगर (!irqchip_in_kernel(vcpu->kvm) || kvm_vcpu_is_reset_bsp(vcpu))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
	अन्यथा
		vcpu->arch.mp_state = KVM_MP_STATE_UNINITIALIZED;

	kvm_set_tsc_khz(vcpu, max_tsc_khz);

	r = kvm_mmu_create(vcpu);
	अगर (r < 0)
		वापस r;

	अगर (irqchip_in_kernel(vcpu->kvm)) अणु
		r = kvm_create_lapic(vcpu, lapic_समयr_advance_ns);
		अगर (r < 0)
			जाओ fail_mmu_destroy;
		अगर (kvm_apicv_activated(vcpu->kvm))
			vcpu->arch.apicv_active = true;
	पूर्ण अन्यथा
		अटल_branch_inc(&kvm_has_noapic_vcpu);

	r = -ENOMEM;

	page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!page)
		जाओ fail_मुक्त_lapic;
	vcpu->arch.pio_data = page_address(page);

	vcpu->arch.mce_banks = kzalloc(KVM_MAX_MCE_BANKS * माप(u64) * 4,
				       GFP_KERNEL_ACCOUNT);
	अगर (!vcpu->arch.mce_banks)
		जाओ fail_मुक्त_pio_data;
	vcpu->arch.mcg_cap = KVM_MAX_MCE_BANKS;

	अगर (!zalloc_cpumask_var(&vcpu->arch.wbinvd_dirty_mask,
				GFP_KERNEL_ACCOUNT))
		जाओ fail_मुक्त_mce_banks;

	अगर (!alloc_emulate_ctxt(vcpu))
		जाओ मुक्त_wbinvd_dirty_mask;

	vcpu->arch.user_fpu = kmem_cache_zalloc(x86_fpu_cache,
						GFP_KERNEL_ACCOUNT);
	अगर (!vcpu->arch.user_fpu) अणु
		pr_err("kvm: failed to allocate userspace's fpu\n");
		जाओ मुक्त_emulate_ctxt;
	पूर्ण

	vcpu->arch.guest_fpu = kmem_cache_zalloc(x86_fpu_cache,
						 GFP_KERNEL_ACCOUNT);
	अगर (!vcpu->arch.guest_fpu) अणु
		pr_err("kvm: failed to allocate vcpu's fpu\n");
		जाओ मुक्त_user_fpu;
	पूर्ण
	fx_init(vcpu);

	vcpu->arch.maxphyaddr = cpuid_query_maxphyaddr(vcpu);
	vcpu->arch.reserved_gpa_bits = kvm_vcpu_reserved_gpa_bits_raw(vcpu);

	vcpu->arch.pat = MSR_IA32_CR_PAT_DEFAULT;

	kvm_async_pf_hash_reset(vcpu);
	kvm_pmu_init(vcpu);

	vcpu->arch.pending_बाह्यal_vector = -1;
	vcpu->arch.preempted_in_kernel = false;

	r = अटल_call(kvm_x86_vcpu_create)(vcpu);
	अगर (r)
		जाओ मुक्त_guest_fpu;

	vcpu->arch.arch_capabilities = kvm_get_arch_capabilities();
	vcpu->arch.msr_platक्रमm_info = MSR_PLATFORM_INFO_CPUID_FAULT;
	kvm_vcpu_mtrr_init(vcpu);
	vcpu_load(vcpu);
	kvm_vcpu_reset(vcpu, false);
	kvm_init_mmu(vcpu, false);
	vcpu_put(vcpu);
	वापस 0;

मुक्त_guest_fpu:
	kvm_मुक्त_guest_fpu(vcpu);
मुक्त_user_fpu:
	kmem_cache_मुक्त(x86_fpu_cache, vcpu->arch.user_fpu);
मुक्त_emulate_ctxt:
	kmem_cache_मुक्त(x86_emulator_cache, vcpu->arch.emulate_ctxt);
मुक्त_wbinvd_dirty_mask:
	मुक्त_cpumask_var(vcpu->arch.wbinvd_dirty_mask);
fail_मुक्त_mce_banks:
	kमुक्त(vcpu->arch.mce_banks);
fail_मुक्त_pio_data:
	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.pio_data);
fail_मुक्त_lapic:
	kvm_मुक्त_lapic(vcpu);
fail_mmu_destroy:
	kvm_mmu_destroy(vcpu);
	वापस r;
पूर्ण

व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;

	अगर (mutex_lock_समाप्तable(&vcpu->mutex))
		वापस;
	vcpu_load(vcpu);
	kvm_synchronize_tsc(vcpu, 0);
	vcpu_put(vcpu);

	/* poll control enabled by शेष */
	vcpu->arch.msr_kvm_poll_control = 1;

	mutex_unlock(&vcpu->mutex);

	अगर (kvmघड़ी_periodic_sync && vcpu->vcpu_idx == 0)
		schedule_delayed_work(&kvm->arch.kvmघड़ी_sync_work,
						KVMCLOCK_SYNC_PERIOD);
पूर्ण

व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा gfn_to_pfn_cache *cache = &vcpu->arch.st.cache;
	पूर्णांक idx;

	kvm_release_pfn(cache->pfn, cache->dirty, cache);

	kvmघड़ी_reset(vcpu);

	अटल_call(kvm_x86_vcpu_मुक्त)(vcpu);

	kmem_cache_मुक्त(x86_emulator_cache, vcpu->arch.emulate_ctxt);
	मुक्त_cpumask_var(vcpu->arch.wbinvd_dirty_mask);
	kmem_cache_मुक्त(x86_fpu_cache, vcpu->arch.user_fpu);
	kvm_मुक्त_guest_fpu(vcpu);

	kvm_hv_vcpu_uninit(vcpu);
	kvm_pmu_destroy(vcpu);
	kमुक्त(vcpu->arch.mce_banks);
	kvm_मुक्त_lapic(vcpu);
	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	kvm_mmu_destroy(vcpu);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
	मुक्त_page((अचिन्हित दीर्घ)vcpu->arch.pio_data);
	kvमुक्त(vcpu->arch.cpuid_entries);
	अगर (!lapic_in_kernel(vcpu))
		अटल_branch_dec(&kvm_has_noapic_vcpu);
पूर्ण

व्योम kvm_vcpu_reset(काष्ठा kvm_vcpu *vcpu, bool init_event)
अणु
	kvm_lapic_reset(vcpu, init_event);

	vcpu->arch.hflags = 0;

	vcpu->arch.smi_pending = 0;
	vcpu->arch.smi_count = 0;
	atomic_set(&vcpu->arch.nmi_queued, 0);
	vcpu->arch.nmi_pending = 0;
	vcpu->arch.nmi_injected = false;
	kvm_clear_पूर्णांकerrupt_queue(vcpu);
	kvm_clear_exception_queue(vcpu);

	स_रखो(vcpu->arch.db, 0, माप(vcpu->arch.db));
	kvm_update_dr0123(vcpu);
	vcpu->arch.dr6 = DR6_ACTIVE_LOW;
	vcpu->arch.dr7 = DR7_FIXED_1;
	kvm_update_dr7(vcpu);

	vcpu->arch.cr2 = 0;

	kvm_make_request(KVM_REQ_EVENT, vcpu);
	vcpu->arch.apf.msr_en_val = 0;
	vcpu->arch.apf.msr_पूर्णांक_val = 0;
	vcpu->arch.st.msr_val = 0;

	kvmघड़ी_reset(vcpu);

	kvm_clear_async_pf_completion_queue(vcpu);
	kvm_async_pf_hash_reset(vcpu);
	vcpu->arch.apf.halted = false;

	अगर (vcpu->arch.guest_fpu && kvm_mpx_supported()) अणु
		व्योम *mpx_state_buffer;

		/*
		 * To aव्योम have the INIT path from kvm_apic_has_events() that be
		 * called with loaded FPU and करोes not let userspace fix the state.
		 */
		अगर (init_event)
			kvm_put_guest_fpu(vcpu);
		mpx_state_buffer = get_xsave_addr(&vcpu->arch.guest_fpu->state.xsave,
					XFEATURE_BNDREGS);
		अगर (mpx_state_buffer)
			स_रखो(mpx_state_buffer, 0, माप(काष्ठा mpx_bndreg_state));
		mpx_state_buffer = get_xsave_addr(&vcpu->arch.guest_fpu->state.xsave,
					XFEATURE_BNDCSR);
		अगर (mpx_state_buffer)
			स_रखो(mpx_state_buffer, 0, माप(काष्ठा mpx_bndcsr));
		अगर (init_event)
			kvm_load_guest_fpu(vcpu);
	पूर्ण

	अगर (!init_event) अणु
		kvm_pmu_reset(vcpu);
		vcpu->arch.smbase = 0x30000;

		vcpu->arch.msr_misc_features_enables = 0;

		vcpu->arch.xcr0 = XFEATURE_MASK_FP;
	पूर्ण

	स_रखो(vcpu->arch.regs, 0, माप(vcpu->arch.regs));
	vcpu->arch.regs_avail = ~0;
	vcpu->arch.regs_dirty = ~0;

	vcpu->arch.ia32_xss = 0;

	अटल_call(kvm_x86_vcpu_reset)(vcpu, init_event);
पूर्ण

व्योम kvm_vcpu_deliver_sipi_vector(काष्ठा kvm_vcpu *vcpu, u8 vector)
अणु
	काष्ठा kvm_segment cs;

	kvm_get_segment(vcpu, &cs, VCPU_SREG_CS);
	cs.selector = vector << 8;
	cs.base = vector << 12;
	kvm_set_segment(vcpu, &cs, VCPU_SREG_CS);
	kvm_rip_ग_लिखो(vcpu, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_deliver_sipi_vector);

पूर्णांक kvm_arch_hardware_enable(व्योम)
अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;
	पूर्णांक ret;
	u64 local_tsc;
	u64 max_tsc = 0;
	bool stable, backwards_tsc = false;

	kvm_user_वापस_msr_cpu_online();
	ret = अटल_call(kvm_x86_hardware_enable)();
	अगर (ret != 0)
		वापस ret;

	local_tsc = rdtsc();
	stable = !kvm_check_tsc_unstable();
	list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			अगर (!stable && vcpu->cpu == smp_processor_id())
				kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
			अगर (stable && vcpu->arch.last_host_tsc > local_tsc) अणु
				backwards_tsc = true;
				अगर (vcpu->arch.last_host_tsc > max_tsc)
					max_tsc = vcpu->arch.last_host_tsc;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Someबार, even reliable TSCs go backwards.  This happens on
	 * platक्रमms that reset TSC during suspend or hibernate actions, but
	 * मुख्यtain synchronization.  We must compensate.  Fortunately, we can
	 * detect that condition here, which happens early in CPU bringup,
	 * beक्रमe any KVM thपढ़ोs can be running.  Unक्रमtunately, we can't
	 * bring the TSCs fully up to date with real समय, as we aren't yet far
	 * enough पूर्णांकo CPU bringup that we know how much real समय has actually
	 * elapsed; our helper function, kसमय_get_bootसमय_ns() will be using boot
	 * variables that haven't been updated yet.
	 *
	 * So we simply find the maximum observed TSC above, then record the
	 * adjusपंचांगent to TSC in each VCPU.  When the VCPU later माला_लो loaded,
	 * the adjusपंचांगent will be applied.  Note that we accumulate
	 * adjusपंचांगents, in हाल multiple suspend cycles happen beक्रमe some VCPU
	 * माला_लो a chance to run again.  In the event that no KVM thपढ़ोs get a
	 * chance to run, we will miss the entire elapsed period, as we'll have
	 * reset last_host_tsc, so VCPUs will not have the TSC adjusted and may
	 * loose cycle समय.  This isn't too big a deal, since the loss will be
	 * unअगरorm across all VCPUs (not to mention the scenario is extremely
	 * unlikely). It is possible that a second hibernate recovery happens
	 * much faster than a first, causing the observed TSC here to be
	 * smaller; this would require additional padding adjusपंचांगent, which is
	 * why we set last_host_tsc to the local tsc observed here.
	 *
	 * N.B. - this code below runs only on platक्रमms with reliable TSC,
	 * as that is the only way backwards_tsc is set above.  Also note
	 * that this runs क्रम ALL vcpus, which is not a bug; all VCPUs should
	 * have the same delta_cyc adjusपंचांगent applied अगर backwards_tsc
	 * is detected.  Note further, this adjusपंचांगent is only करोne once,
	 * as we reset last_host_tsc on all VCPUs to stop this from being
	 * called multiple बार (one क्रम each physical CPU bringup).
	 *
	 * Platक्रमms with unreliable TSCs करोn't have to deal with this, they
	 * will be compensated by the logic in vcpu_load, which sets the TSC to
	 * catchup mode.  This will catchup all VCPUs to real समय, but cannot
	 * guarantee that they stay in perfect synchronization.
	 */
	अगर (backwards_tsc) अणु
		u64 delta_cyc = max_tsc - local_tsc;
		list_क्रम_each_entry(kvm, &vm_list, vm_list) अणु
			kvm->arch.backwards_tsc_observed = true;
			kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
				vcpu->arch.tsc_offset_adjusपंचांगent += delta_cyc;
				vcpu->arch.last_host_tsc = local_tsc;
				kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);
			पूर्ण

			/*
			 * We have to disable TSC offset matching.. अगर you were
			 * booting a VM जबतक issuing an S4 host suspend....
			 * you may have some problem.  Solving this issue is
			 * left as an exercise to the पढ़ोer.
			 */
			kvm->arch.last_tsc_nsec = 0;
			kvm->arch.last_tsc_ग_लिखो = 0;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

व्योम kvm_arch_hardware_disable(व्योम)
अणु
	अटल_call(kvm_x86_hardware_disable)();
	drop_user_वापस_notअगरiers();
पूर्ण

पूर्णांक kvm_arch_hardware_setup(व्योम *opaque)
अणु
	काष्ठा kvm_x86_init_ops *ops = opaque;
	पूर्णांक r;

	rdmsrl_safe(MSR_EFER, &host_efer);

	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		rdmsrl(MSR_IA32_XSS, host_xss);

	r = ops->hardware_setup();
	अगर (r != 0)
		वापस r;

	स_नकल(&kvm_x86_ops, ops->runसमय_ops, माप(kvm_x86_ops));
	kvm_ops_अटल_call_update();

	अगर (!kvm_cpu_cap_has(X86_FEATURE_XSAVES))
		supported_xss = 0;

#घोषणा __kvm_cpu_cap_has(UNUSED_, f) kvm_cpu_cap_has(f)
	cr4_reserved_bits = __cr4_reserved_bits(__kvm_cpu_cap_has, UNUSED_);
#अघोषित __kvm_cpu_cap_has

	अगर (kvm_has_tsc_control) अणु
		/*
		 * Make sure the user can only configure tsc_khz values that
		 * fit पूर्णांकo a चिन्हित पूर्णांकeger.
		 * A min value is not calculated because it will always
		 * be 1 on all machines.
		 */
		u64 max = min(0x7fffffffULL,
			      __scale_tsc(kvm_max_tsc_scaling_ratio, tsc_khz));
		kvm_max_guest_tsc_khz = max;

		kvm_शेष_tsc_scaling_ratio = 1ULL << kvm_tsc_scaling_ratio_frac_bits;
	पूर्ण

	kvm_init_msr_list();
	वापस 0;
पूर्ण

व्योम kvm_arch_hardware_unsetup(व्योम)
अणु
	अटल_call(kvm_x86_hardware_unsetup)();
पूर्ण

पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(smp_processor_id());
	काष्ठा kvm_x86_init_ops *ops = opaque;

	WARN_ON(!irqs_disabled());

	अगर (__cr4_reserved_bits(cpu_has, c) !=
	    __cr4_reserved_bits(cpu_has, &boot_cpu_data))
		वापस -EIO;

	वापस ops->check_processor_compatibility();
पूर्ण

bool kvm_vcpu_is_reset_bsp(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->kvm->arch.bsp_vcpu_id == vcpu->vcpu_id;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vcpu_is_reset_bsp);

bool kvm_vcpu_is_bsp(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu->arch.apic_base & MSR_IA32_APICBASE_BSP) != 0;
पूर्ण

__पढ़ो_mostly DEFINE_STATIC_KEY_FALSE(kvm_has_noapic_vcpu);
EXPORT_SYMBOL_GPL(kvm_has_noapic_vcpu);

व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	vcpu->arch.l1tf_flush_l1d = true;
	अगर (pmu->version && unlikely(pmu->event_count)) अणु
		pmu->need_cleanup = true;
		kvm_make_request(KVM_REQ_PMU, vcpu);
	पूर्ण
	अटल_call(kvm_x86_sched_in)(vcpu, cpu);
पूर्ण

व्योम kvm_arch_मुक्त_vm(काष्ठा kvm *kvm)
अणु
	kमुक्त(to_kvm_hv(kvm)->hv_pa_pg);
	vमुक्त(kvm);
पूर्ण


पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	अगर (type)
		वापस -EINVAL;

	INIT_HLIST_HEAD(&kvm->arch.mask_notअगरier_list);
	INIT_LIST_HEAD(&kvm->arch.active_mmu_pages);
	INIT_LIST_HEAD(&kvm->arch.zapped_obsolete_pages);
	INIT_LIST_HEAD(&kvm->arch.lpage_disallowed_mmu_pages);
	INIT_LIST_HEAD(&kvm->arch.asचिन्हित_dev_head);
	atomic_set(&kvm->arch.noncoherent_dma_count, 0);

	/* Reserve bit 0 of irq_sources_biपंचांगap क्रम userspace irq source */
	set_bit(KVM_USERSPACE_IRQ_SOURCE_ID, &kvm->arch.irq_sources_biपंचांगap);
	/* Reserve bit 1 of irq_sources_biपंचांगap क्रम irqfd-resampler */
	set_bit(KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID,
		&kvm->arch.irq_sources_biपंचांगap);

	raw_spin_lock_init(&kvm->arch.tsc_ग_लिखो_lock);
	mutex_init(&kvm->arch.apic_map_lock);
	spin_lock_init(&kvm->arch.pvघड़ी_gtod_sync_lock);

	kvm->arch.kvmघड़ी_offset = -get_kvmघड़ी_base_ns();
	pvघड़ी_update_vm_gtod_copy(kvm);

	kvm->arch.guest_can_पढ़ो_msr_platक्रमm_info = true;

	INIT_DELAYED_WORK(&kvm->arch.kvmघड़ी_update_work, kvmघड़ी_update_fn);
	INIT_DELAYED_WORK(&kvm->arch.kvmघड़ी_sync_work, kvmघड़ी_sync_fn);

	kvm_hv_init_vm(kvm);
	kvm_page_track_init(kvm);
	kvm_mmu_init_vm(kvm);

	वापस अटल_call(kvm_x86_vm_init)(kvm);
पूर्ण

पूर्णांक kvm_arch_post_init_vm(काष्ठा kvm *kvm)
अणु
	वापस kvm_mmu_post_init_vm(kvm);
पूर्ण

अटल व्योम kvm_unload_vcpu_mmu(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu_load(vcpu);
	kvm_mmu_unload(vcpu);
	vcpu_put(vcpu);
पूर्ण

अटल व्योम kvm_मुक्त_vcpus(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	/*
	 * Unpin any mmu pages first.
	 */
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		kvm_clear_async_pf_completion_queue(vcpu);
		kvm_unload_vcpu_mmu(vcpu);
	पूर्ण
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vcpu_destroy(vcpu);

	mutex_lock(&kvm->lock);
	क्रम (i = 0; i < atomic_पढ़ो(&kvm->online_vcpus); i++)
		kvm->vcpus[i] = शून्य;

	atomic_set(&kvm->online_vcpus, 0);
	mutex_unlock(&kvm->lock);
पूर्ण

व्योम kvm_arch_sync_events(काष्ठा kvm *kvm)
अणु
	cancel_delayed_work_sync(&kvm->arch.kvmघड़ी_sync_work);
	cancel_delayed_work_sync(&kvm->arch.kvmघड़ी_update_work);
	kvm_मुक्त_pit(kvm);
पूर्ण

#घोषणा  ERR_PTR_USR(e)  ((व्योम __user *)ERR_PTR(e))

/**
 * __x86_set_memory_region: Setup KVM पूर्णांकernal memory slot
 *
 * @kvm: the kvm poपूर्णांकer to the VM.
 * @id: the slot ID to setup.
 * @gpa: the GPA to install the slot (unused when @size == 0).
 * @size: the size of the slot. Set to zero to uninstall a slot.
 *
 * This function helps to setup a KVM पूर्णांकernal memory slot.  Specअगरy
 * @size > 0 to install a new slot, जबतक @size == 0 to uninstall a
 * slot.  The वापस code can be one of the following:
 *
 *   HVA:           on success (uninstall will वापस a bogus HVA)
 *   -त्रुटि_सं:        on error
 *
 * The caller should always use IS_ERR() to check the वापस value
 * beक्रमe use.  Note, the KVM पूर्णांकernal memory slots are guaranteed to
 * reमुख्य valid and unchanged until the VM is destroyed, i.e., the
 * GPA->HVA translation will not change.  However, the HVA is a user
 * address, i.e. its accessibility is not guaranteed, and must be
 * accessed via __copy_अणुto,fromपूर्ण_user().
 */
व्योम __user * __x86_set_memory_region(काष्ठा kvm *kvm, पूर्णांक id, gpa_t gpa,
				      u32 size)
अणु
	पूर्णांक i, r;
	अचिन्हित दीर्घ hva, old_npages;
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	काष्ठा kvm_memory_slot *slot;

	/* Called with kvm->slots_lock held.  */
	अगर (WARN_ON(id >= KVM_MEM_SLOTS_NUM))
		वापस ERR_PTR_USR(-EINVAL);

	slot = id_to_memslot(slots, id);
	अगर (size) अणु
		अगर (slot && slot->npages)
			वापस ERR_PTR_USR(-EEXIST);

		/*
		 * MAP_SHARED to prevent पूर्णांकernal slot pages from being moved
		 * by विभाजन()/COW.
		 */
		hva = vm_mmap(शून्य, 0, size, PROT_READ | PROT_WRITE,
			      MAP_SHARED | MAP_ANONYMOUS, 0);
		अगर (IS_ERR((व्योम *)hva))
			वापस (व्योम __user *)hva;
	पूर्ण अन्यथा अणु
		अगर (!slot || !slot->npages)
			वापस शून्य;

		old_npages = slot->npages;
		hva = slot->userspace_addr;
	पूर्ण

	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) अणु
		काष्ठा kvm_userspace_memory_region m;

		m.slot = id | (i << 16);
		m.flags = 0;
		m.guest_phys_addr = gpa;
		m.userspace_addr = hva;
		m.memory_size = size;
		r = __kvm_set_memory_region(kvm, &m);
		अगर (r < 0)
			वापस ERR_PTR_USR(r);
	पूर्ण

	अगर (!size)
		vm_munmap(hva, old_npages * PAGE_SIZE);

	वापस (व्योम __user *)hva;
पूर्ण
EXPORT_SYMBOL_GPL(__x86_set_memory_region);

व्योम kvm_arch_pre_destroy_vm(काष्ठा kvm *kvm)
अणु
	kvm_mmu_pre_destroy_vm(kvm);
पूर्ण

व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm)
अणु
	अगर (current->mm == kvm->mm) अणु
		/*
		 * Free memory regions allocated on behalf of userspace,
		 * unless the the memory map has changed due to process निकास
		 * or fd copying.
		 */
		mutex_lock(&kvm->slots_lock);
		__x86_set_memory_region(kvm, APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
					0, 0);
		__x86_set_memory_region(kvm, IDENTITY_PAGETABLE_PRIVATE_MEMSLOT,
					0, 0);
		__x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, 0, 0);
		mutex_unlock(&kvm->slots_lock);
	पूर्ण
	अटल_call_cond(kvm_x86_vm_destroy)(kvm);
	kvm_मुक्त_msr_filter(srcu_dereference_check(kvm->arch.msr_filter, &kvm->srcu, 1));
	kvm_pic_destroy(kvm);
	kvm_ioapic_destroy(kvm);
	kvm_मुक्त_vcpus(kvm);
	kvमुक्त(rcu_dereference_check(kvm->arch.apic_map, 1));
	kमुक्त(srcu_dereference_check(kvm->arch.pmu_event_filter, &kvm->srcu, 1));
	kvm_mmu_uninit_vm(kvm);
	kvm_page_track_cleanup(kvm);
	kvm_xen_destroy_vm(kvm);
	kvm_hv_destroy_vm(kvm);
पूर्ण

व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVM_NR_PAGE_SIZES; ++i) अणु
		kvमुक्त(slot->arch.rmap[i]);
		slot->arch.rmap[i] = शून्य;

		अगर (i == 0)
			जारी;

		kvमुक्त(slot->arch.lpage_info[i - 1]);
		slot->arch.lpage_info[i - 1] = शून्य;
	पूर्ण

	kvm_page_track_मुक्त_memslot(slot);
पूर्ण

अटल पूर्णांक kvm_alloc_memslot_metadata(काष्ठा kvm_memory_slot *slot,
				      अचिन्हित दीर्घ npages)
अणु
	पूर्णांक i;

	/*
	 * Clear out the previous array poपूर्णांकers क्रम the KVM_MR_MOVE हाल.  The
	 * old arrays will be मुक्तd by __kvm_set_memory_region() अगर installing
	 * the new memslot is successful.
	 */
	स_रखो(&slot->arch, 0, माप(slot->arch));

	क्रम (i = 0; i < KVM_NR_PAGE_SIZES; ++i) अणु
		काष्ठा kvm_lpage_info *linfo;
		अचिन्हित दीर्घ ugfn;
		पूर्णांक lpages;
		पूर्णांक level = i + 1;

		lpages = gfn_to_index(slot->base_gfn + npages - 1,
				      slot->base_gfn, level) + 1;

		slot->arch.rmap[i] =
			kvसुस्मृति(lpages, माप(*slot->arch.rmap[i]),
				 GFP_KERNEL_ACCOUNT);
		अगर (!slot->arch.rmap[i])
			जाओ out_मुक्त;
		अगर (i == 0)
			जारी;

		linfo = kvसुस्मृति(lpages, माप(*linfo), GFP_KERNEL_ACCOUNT);
		अगर (!linfo)
			जाओ out_मुक्त;

		slot->arch.lpage_info[i - 1] = linfo;

		अगर (slot->base_gfn & (KVM_PAGES_PER_HPAGE(level) - 1))
			linfo[0].disallow_lpage = 1;
		अगर ((slot->base_gfn + npages) & (KVM_PAGES_PER_HPAGE(level) - 1))
			linfo[lpages - 1].disallow_lpage = 1;
		ugfn = slot->userspace_addr >> PAGE_SHIFT;
		/*
		 * If the gfn and userspace address are not aligned wrt each
		 * other, disable large page support क्रम this slot.
		 */
		अगर ((slot->base_gfn ^ ugfn) & (KVM_PAGES_PER_HPAGE(level) - 1)) अणु
			अचिन्हित दीर्घ j;

			क्रम (j = 0; j < lpages; ++j)
				linfo[j].disallow_lpage = 1;
		पूर्ण
	पूर्ण

	अगर (kvm_page_track_create_memslot(slot, npages))
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	क्रम (i = 0; i < KVM_NR_PAGE_SIZES; ++i) अणु
		kvमुक्त(slot->arch.rmap[i]);
		slot->arch.rmap[i] = शून्य;
		अगर (i == 0)
			जारी;

		kvमुक्त(slot->arch.lpage_info[i - 1]);
		slot->arch.lpage_info[i - 1] = शून्य;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	/*
	 * memslots->generation has been incremented.
	 * mmio generation may have reached its maximum value.
	 */
	kvm_mmu_invalidate_mmio_sptes(kvm, gen);

	/* Force re-initialization of steal_समय cache */
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vcpu_kick(vcpu);
पूर्ण

पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				काष्ठा kvm_memory_slot *memslot,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				क्रमागत kvm_mr_change change)
अणु
	अगर (change == KVM_MR_CREATE || change == KVM_MR_MOVE)
		वापस kvm_alloc_memslot_metadata(memslot,
						  mem->memory_size >> PAGE_SHIFT);
	वापस 0;
पूर्ण


अटल व्योम kvm_mmu_update_cpu_dirty_logging(काष्ठा kvm *kvm, bool enable)
अणु
	काष्ठा kvm_arch *ka = &kvm->arch;

	अगर (!kvm_x86_ops.cpu_dirty_log_size)
		वापस;

	अगर ((enable && ++ka->cpu_dirty_logging_count == 1) ||
	    (!enable && --ka->cpu_dirty_logging_count == 0))
		kvm_make_all_cpus_request(kvm, KVM_REQ_UPDATE_CPU_सूचीTY_LOGGING);

	WARN_ON_ONCE(ka->cpu_dirty_logging_count < 0);
पूर्ण

अटल व्योम kvm_mmu_slot_apply_flags(काष्ठा kvm *kvm,
				     काष्ठा kvm_memory_slot *old,
				     काष्ठा kvm_memory_slot *new,
				     क्रमागत kvm_mr_change change)
अणु
	bool log_dirty_pages = new->flags & KVM_MEM_LOG_सूचीTY_PAGES;

	/*
	 * Update CPU dirty logging अगर dirty logging is being toggled.  This
	 * applies to all operations.
	 */
	अगर ((old->flags ^ new->flags) & KVM_MEM_LOG_सूचीTY_PAGES)
		kvm_mmu_update_cpu_dirty_logging(kvm, log_dirty_pages);

	/*
	 * Nothing more to करो क्रम RO slots (which can't be dirtied and can't be
	 * made writable) or CREATE/MOVE/DELETE of a slot.
	 *
	 * For a memslot with dirty logging disabled:
	 * CREATE:      No dirty mappings will alपढ़ोy exist.
	 * MOVE/DELETE: The old mappings will alपढ़ोy have been cleaned up by
	 *		kvm_arch_flush_shaकरोw_memslot()
	 *
	 * For a memslot with dirty logging enabled:
	 * CREATE:      No shaकरोw pages exist, thus nothing to ग_लिखो-protect
	 *		and no dirty bits to clear.
	 * MOVE/DELETE: The old mappings will alपढ़ोy have been cleaned up by
	 *		kvm_arch_flush_shaकरोw_memslot().
	 */
	अगर ((change != KVM_MR_FLAGS_ONLY) || (new->flags & KVM_MEM_READONLY))
		वापस;

	/*
	 * READONLY and non-flags changes were filtered out above, and the only
	 * other flag is LOG_सूचीTY_PAGES, i.e. something is wrong अगर dirty
	 * logging isn't being toggled on or off.
	 */
	अगर (WARN_ON_ONCE(!((old->flags ^ new->flags) & KVM_MEM_LOG_सूचीTY_PAGES)))
		वापस;

	अगर (!log_dirty_pages) अणु
		/*
		 * Dirty logging tracks sptes in 4k granularity, meaning that
		 * large sptes have to be split.  If live migration succeeds,
		 * the guest in the source machine will be destroyed and large
		 * sptes will be created in the destination.  However, अगर the
		 * guest जारीs to run in the source machine (क्रम example अगर
		 * live migration fails), small sptes will reमुख्य around and
		 * cause bad perक्रमmance.
		 *
		 * Scan sptes अगर dirty logging has been stopped, dropping those
		 * which can be collapsed पूर्णांकo a single large-page spte.  Later
		 * page faults will create the large-page sptes.
		 */
		kvm_mmu_zap_collapsible_sptes(kvm, new);
	पूर्ण अन्यथा अणु
		/* By शेष, ग_लिखो-protect everything to log ग_लिखोs. */
		पूर्णांक level = PG_LEVEL_4K;

		अगर (kvm_x86_ops.cpu_dirty_log_size) अणु
			/*
			 * Clear all dirty bits, unless pages are treated as
			 * dirty from the get-go.
			 */
			अगर (!kvm_dirty_log_manual_protect_and_init_set(kvm))
				kvm_mmu_slot_leaf_clear_dirty(kvm, new);

			/*
			 * Write-protect large pages on ग_लिखो so that dirty
			 * logging happens at 4k granularity.  No need to
			 * ग_लिखो-protect small SPTEs since ग_लिखो accesses are
			 * logged by the CPU via dirty bits.
			 */
			level = PG_LEVEL_2M;
		पूर्ण अन्यथा अगर (kvm_dirty_log_manual_protect_and_init_set(kvm)) अणु
			/*
			 * If we're with initial-all-set, we don't need
			 * to ग_लिखो protect any small page because
			 * they're reported as dirty alपढ़ोy.  However
			 * we still need to ग_लिखो-protect huge pages
			 * so that the page split can happen lazily on
			 * the first ग_लिखो to the huge page.
			 */
			level = PG_LEVEL_2M;
		पूर्ण
		kvm_mmu_slot_हटाओ_ग_लिखो_access(kvm, new, level);
	पूर्ण
पूर्ण

व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change)
अणु
	अगर (!kvm->arch.n_requested_mmu_pages)
		kvm_mmu_change_mmu_pages(kvm,
				kvm_mmu_calculate_शेष_mmu_pages(kvm));

	/*
	 * FIXME: स्थिर-अगरy all uses of काष्ठा kvm_memory_slot.
	 */
	kvm_mmu_slot_apply_flags(kvm, old, (काष्ठा kvm_memory_slot *) new, change);

	/* Free the arrays associated with the old memslot. */
	अगर (change == KVM_MR_MOVE)
		kvm_arch_मुक्त_memslot(kvm, old);
पूर्ण

व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm)
अणु
	kvm_mmu_zap_all(kvm);
पूर्ण

व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot)
अणु
	kvm_page_track_flush_slot(kvm, slot);
पूर्ण

अटल अंतरभूत bool kvm_guest_apic_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (is_guest_mode(vcpu) &&
			kvm_x86_ops.guest_apic_has_पूर्णांकerrupt &&
			अटल_call(kvm_x86_guest_apic_has_पूर्णांकerrupt)(vcpu));
पूर्ण

अटल अंतरभूत bool kvm_vcpu_has_events(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!list_empty_careful(&vcpu->async_pf.करोne))
		वापस true;

	अगर (kvm_apic_has_events(vcpu))
		वापस true;

	अगर (vcpu->arch.pv.pv_unhalted)
		वापस true;

	अगर (vcpu->arch.exception.pending)
		वापस true;

	अगर (kvm_test_request(KVM_REQ_NMI, vcpu) ||
	    (vcpu->arch.nmi_pending &&
	     अटल_call(kvm_x86_nmi_allowed)(vcpu, false)))
		वापस true;

	अगर (kvm_test_request(KVM_REQ_SMI, vcpu) ||
	    (vcpu->arch.smi_pending &&
	     अटल_call(kvm_x86_smi_allowed)(vcpu, false)))
		वापस true;

	अगर (kvm_arch_पूर्णांकerrupt_allowed(vcpu) &&
	    (kvm_cpu_has_पूर्णांकerrupt(vcpu) ||
	    kvm_guest_apic_has_पूर्णांकerrupt(vcpu)))
		वापस true;

	अगर (kvm_hv_has_sसमयr_pending(vcpu))
		वापस true;

	अगर (is_guest_mode(vcpu) &&
	    kvm_x86_ops.nested_ops->hv_समयr_pending &&
	    kvm_x86_ops.nested_ops->hv_समयr_pending(vcpu))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_running(vcpu) || kvm_vcpu_has_events(vcpu);
पूर्ण

bool kvm_arch_dy_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.apicv_active && अटल_call(kvm_x86_dy_apicv_has_pending_पूर्णांकerrupt)(vcpu))
		वापस true;

	वापस false;
पूर्ण

bool kvm_arch_dy_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (READ_ONCE(vcpu->arch.pv.pv_unhalted))
		वापस true;

	अगर (kvm_test_request(KVM_REQ_NMI, vcpu) ||
		kvm_test_request(KVM_REQ_SMI, vcpu) ||
		 kvm_test_request(KVM_REQ_EVENT, vcpu))
		वापस true;

	वापस kvm_arch_dy_has_pending_पूर्णांकerrupt(vcpu);
पूर्ण

bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.guest_state_रक्षित)
		वापस true;

	वापस vcpu->arch.preempted_in_kernel;
पूर्ण

पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_निकासing_guest_mode(vcpu) == IN_GUEST_MODE;
पूर्ण

पूर्णांक kvm_arch_पूर्णांकerrupt_allowed(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस अटल_call(kvm_x86_पूर्णांकerrupt_allowed)(vcpu, false);
पूर्ण

अचिन्हित दीर्घ kvm_get_linear_rip(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Can't पढ़ो the RIP when guest state is रक्षित, just वापस 0 */
	अगर (vcpu->arch.guest_state_रक्षित)
		वापस 0;

	अगर (is_64_bit_mode(vcpu))
		वापस kvm_rip_पढ़ो(vcpu);
	वापस (u32)(get_segment_base(vcpu, VCPU_SREG_CS) +
		     kvm_rip_पढ़ो(vcpu));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_linear_rip);

bool kvm_is_linear_rip(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ linear_rip)
अणु
	वापस kvm_get_linear_rip(vcpu) == linear_rip;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_is_linear_rip);

अचिन्हित दीर्घ kvm_get_rflags(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ rflags;

	rflags = अटल_call(kvm_x86_get_rflags)(vcpu);
	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		rflags &= ~X86_EFLAGS_TF;
	वापस rflags;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_get_rflags);

अटल व्योम __kvm_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags)
अणु
	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP &&
	    kvm_is_linear_rip(vcpu, vcpu->arch.singlestep_rip))
		rflags |= X86_EFLAGS_TF;
	अटल_call(kvm_x86_set_rflags)(vcpu, rflags);
पूर्ण

व्योम kvm_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags)
अणु
	__kvm_set_rflags(vcpu, rflags);
	kvm_make_request(KVM_REQ_EVENT, vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_rflags);

व्योम kvm_arch_async_page_पढ़ोy(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_async_pf *work)
अणु
	पूर्णांक r;

	अगर ((vcpu->arch.mmu->direct_map != work->arch.direct_map) ||
	      work->wakeup_all)
		वापस;

	r = kvm_mmu_reload(vcpu);
	अगर (unlikely(r))
		वापस;

	अगर (!vcpu->arch.mmu->direct_map &&
	      work->arch.cr3 != vcpu->arch.mmu->get_guest_pgd(vcpu))
		वापस;

	kvm_mmu_करो_page_fault(vcpu, work->cr2_or_gpa, 0, true);
पूर्ण

अटल अंतरभूत u32 kvm_async_pf_hash_fn(gfn_t gfn)
अणु
	BUILD_BUG_ON(!is_घातer_of_2(ASYNC_PF_PER_VCPU));

	वापस hash_32(gfn & 0xffffffff, order_base_2(ASYNC_PF_PER_VCPU));
पूर्ण

अटल अंतरभूत u32 kvm_async_pf_next_probe(u32 key)
अणु
	वापस (key + 1) & (ASYNC_PF_PER_VCPU - 1);
पूर्ण

अटल व्योम kvm_add_async_pf_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	u32 key = kvm_async_pf_hash_fn(gfn);

	जबतक (vcpu->arch.apf.gfns[key] != ~0)
		key = kvm_async_pf_next_probe(key);

	vcpu->arch.apf.gfns[key] = gfn;
पूर्ण

अटल u32 kvm_async_pf_gfn_slot(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	पूर्णांक i;
	u32 key = kvm_async_pf_hash_fn(gfn);

	क्रम (i = 0; i < ASYNC_PF_PER_VCPU &&
		     (vcpu->arch.apf.gfns[key] != gfn &&
		      vcpu->arch.apf.gfns[key] != ~0); i++)
		key = kvm_async_pf_next_probe(key);

	वापस key;
पूर्ण

bool kvm_find_async_pf_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	वापस vcpu->arch.apf.gfns[kvm_async_pf_gfn_slot(vcpu, gfn)] == gfn;
पूर्ण

अटल व्योम kvm_del_async_pf_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	u32 i, j, k;

	i = j = kvm_async_pf_gfn_slot(vcpu, gfn);

	अगर (WARN_ON_ONCE(vcpu->arch.apf.gfns[i] != gfn))
		वापस;

	जबतक (true) अणु
		vcpu->arch.apf.gfns[i] = ~0;
		करो अणु
			j = kvm_async_pf_next_probe(j);
			अगर (vcpu->arch.apf.gfns[j] == ~0)
				वापस;
			k = kvm_async_pf_hash_fn(vcpu->arch.apf.gfns[j]);
			/*
			 * k lies cyclically in ]i,j]
			 * |    i.k.j |
			 * |....j i.k.| or  |.k..j i...|
			 */
		पूर्ण जबतक ((i <= j) ? (i < k && k <= j) : (i < k || k <= j));
		vcpu->arch.apf.gfns[i] = vcpu->arch.apf.gfns[j];
		i = j;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक apf_put_user_notpresent(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 reason = KVM_PV_REASON_PAGE_NOT_PRESENT;

	वापस kvm_ग_लिखो_guest_cached(vcpu->kvm, &vcpu->arch.apf.data, &reason,
				      माप(reason));
पूर्ण

अटल अंतरभूत पूर्णांक apf_put_user_पढ़ोy(काष्ठा kvm_vcpu *vcpu, u32 token)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा kvm_vcpu_pv_apf_data, token);

	वापस kvm_ग_लिखो_guest_offset_cached(vcpu->kvm, &vcpu->arch.apf.data,
					     &token, offset, माप(token));
पूर्ण

अटल अंतरभूत bool apf_pageपढ़ोy_slot_मुक्त(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा kvm_vcpu_pv_apf_data, token);
	u32 val;

	अगर (kvm_पढ़ो_guest_offset_cached(vcpu->kvm, &vcpu->arch.apf.data,
					 &val, offset, माप(val)))
		वापस false;

	वापस !val;
पूर्ण

अटल bool kvm_can_deliver_async_pf(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu->arch.apf.delivery_as_pf_vmनिकास && is_guest_mode(vcpu))
		वापस false;

	अगर (!kvm_pv_async_pf_enabled(vcpu) ||
	    (vcpu->arch.apf.send_user_only && अटल_call(kvm_x86_get_cpl)(vcpu) == 0))
		वापस false;

	वापस true;
पूर्ण

bool kvm_can_करो_async_pf(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (unlikely(!lapic_in_kernel(vcpu) ||
		     kvm_event_needs_reinjection(vcpu) ||
		     vcpu->arch.exception.pending))
		वापस false;

	अगर (kvm_hlt_in_guest(vcpu->kvm) && !kvm_can_deliver_async_pf(vcpu))
		वापस false;

	/*
	 * If पूर्णांकerrupts are off we cannot even use an artअगरicial
	 * halt state.
	 */
	वापस kvm_arch_पूर्णांकerrupt_allowed(vcpu);
पूर्ण

bool kvm_arch_async_page_not_present(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_async_pf *work)
अणु
	काष्ठा x86_exception fault;

	trace_kvm_async_pf_not_present(work->arch.token, work->cr2_or_gpa);
	kvm_add_async_pf_gfn(vcpu, work->arch.gfn);

	अगर (kvm_can_deliver_async_pf(vcpu) &&
	    !apf_put_user_notpresent(vcpu)) अणु
		fault.vector = PF_VECTOR;
		fault.error_code_valid = true;
		fault.error_code = 0;
		fault.nested_page_fault = false;
		fault.address = work->arch.token;
		fault.async_page_fault = true;
		kvm_inject_page_fault(vcpu, &fault);
		वापस true;
	पूर्ण अन्यथा अणु
		/*
		 * It is not possible to deliver a paraभवized asynchronous
		 * page fault, but putting the guest in an artअगरicial halt state
		 * can be beneficial nevertheless: अगर an पूर्णांकerrupt arrives, we
		 * can deliver it समयly and perhaps the guest will schedule
		 * another process.  When the inकाष्ठाion that triggered a page
		 * fault is retried, hopefully the page will be पढ़ोy in the host.
		 */
		kvm_make_request(KVM_REQ_APF_HALT, vcpu);
		वापस false;
	पूर्ण
पूर्ण

व्योम kvm_arch_async_page_present(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_async_pf *work)
अणु
	काष्ठा kvm_lapic_irq irq = अणु
		.delivery_mode = APIC_DM_FIXED,
		.vector = vcpu->arch.apf.vec
	पूर्ण;

	अगर (work->wakeup_all)
		work->arch.token = ~0; /* broadcast wakeup */
	अन्यथा
		kvm_del_async_pf_gfn(vcpu, work->arch.gfn);
	trace_kvm_async_pf_पढ़ोy(work->arch.token, work->cr2_or_gpa);

	अगर ((work->wakeup_all || work->notpresent_injected) &&
	    kvm_pv_async_pf_enabled(vcpu) &&
	    !apf_put_user_पढ़ोy(vcpu, work->arch.token)) अणु
		vcpu->arch.apf.pageपढ़ोy_pending = true;
		kvm_apic_set_irq(vcpu, &irq, शून्य);
	पूर्ण

	vcpu->arch.apf.halted = false;
	vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
पूर्ण

व्योम kvm_arch_async_page_present_queued(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_make_request(KVM_REQ_APF_READY, vcpu);
	अगर (!vcpu->arch.apf.pageपढ़ोy_pending)
		kvm_vcpu_kick(vcpu);
पूर्ण

bool kvm_arch_can_dequeue_async_page_present(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_pv_async_pf_enabled(vcpu))
		वापस true;
	अन्यथा
		वापस kvm_lapic_enabled(vcpu) && apf_pageपढ़ोy_slot_मुक्त(vcpu);
पूर्ण

व्योम kvm_arch_start_assignment(काष्ठा kvm *kvm)
अणु
	अगर (atomic_inc_वापस(&kvm->arch.asचिन्हित_device_count) == 1)
		अटल_call_cond(kvm_x86_start_assignment)(kvm);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_start_assignment);

व्योम kvm_arch_end_assignment(काष्ठा kvm *kvm)
अणु
	atomic_dec(&kvm->arch.asचिन्हित_device_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_end_assignment);

bool kvm_arch_has_asचिन्हित_device(काष्ठा kvm *kvm)
अणु
	वापस atomic_पढ़ो(&kvm->arch.asचिन्हित_device_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_has_asचिन्हित_device);

व्योम kvm_arch_रेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm)
अणु
	atomic_inc(&kvm->arch.noncoherent_dma_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_रेजिस्टर_noncoherent_dma);

व्योम kvm_arch_unरेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm)
अणु
	atomic_dec(&kvm->arch.noncoherent_dma_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_unरेजिस्टर_noncoherent_dma);

bool kvm_arch_has_noncoherent_dma(काष्ठा kvm *kvm)
अणु
	वापस atomic_पढ़ो(&kvm->arch.noncoherent_dma_count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_has_noncoherent_dma);

bool kvm_arch_has_irq_bypass(व्योम)
अणु
	वापस true;
पूर्ण

पूर्णांक kvm_arch_irq_bypass_add_producer(काष्ठा irq_bypass_consumer *cons,
				      काष्ठा irq_bypass_producer *prod)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);
	पूर्णांक ret;

	irqfd->producer = prod;
	kvm_arch_start_assignment(irqfd->kvm);
	ret = अटल_call(kvm_x86_update_pi_irte)(irqfd->kvm,
					 prod->irq, irqfd->gsi, 1);

	अगर (ret)
		kvm_arch_end_assignment(irqfd->kvm);

	वापस ret;
पूर्ण

व्योम kvm_arch_irq_bypass_del_producer(काष्ठा irq_bypass_consumer *cons,
				      काष्ठा irq_bypass_producer *prod)
अणु
	पूर्णांक ret;
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	WARN_ON(irqfd->producer != prod);
	irqfd->producer = शून्य;

	/*
	 * When producer of consumer is unरेजिस्टरed, we change back to
	 * remapped mode, so we can re-use the current implementation
	 * when the irq is masked/disabled or the consumer side (KVM
	 * पूर्णांक this हाल करोesn't want to receive the पूर्णांकerrupts.
	*/
	ret = अटल_call(kvm_x86_update_pi_irte)(irqfd->kvm, prod->irq, irqfd->gsi, 0);
	अगर (ret)
		prपूर्णांकk(KERN_INFO "irq bypass consumer (token %p) unregistration"
		       " fails: %d\n", irqfd->consumer.token, ret);

	kvm_arch_end_assignment(irqfd->kvm);
पूर्ण

पूर्णांक kvm_arch_update_irqfd_routing(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
				   uपूर्णांक32_t guest_irq, bool set)
अणु
	वापस अटल_call(kvm_x86_update_pi_irte)(kvm, host_irq, guest_irq, set);
पूर्ण

bool kvm_vector_hashing_enabled(व्योम)
अणु
	वापस vector_hashing;
पूर्ण

bool kvm_arch_no_poll(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu->arch.msr_kvm_poll_control & 1) == 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arch_no_poll);


पूर्णांक kvm_spec_ctrl_test_value(u64 value)
अणु
	/*
	 * test that setting IA32_SPEC_CTRL to given value
	 * is allowed by the host processor
	 */

	u64 saved_value;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	local_irq_save(flags);

	अगर (rdmsrl_safe(MSR_IA32_SPEC_CTRL, &saved_value))
		ret = 1;
	अन्यथा अगर (wrmsrl_safe(MSR_IA32_SPEC_CTRL, value))
		ret = 1;
	अन्यथा
		wrmsrl(MSR_IA32_SPEC_CTRL, saved_value);

	local_irq_restore(flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_spec_ctrl_test_value);

व्योम kvm_fixup_and_inject_pf_error(काष्ठा kvm_vcpu *vcpu, gva_t gva, u16 error_code)
अणु
	काष्ठा x86_exception fault;
	u32 access = error_code &
		(PFERR_WRITE_MASK | PFERR_FETCH_MASK | PFERR_USER_MASK);

	अगर (!(error_code & PFERR_PRESENT_MASK) ||
	    vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, &fault) != UNMAPPED_GVA) अणु
		/*
		 * If vcpu->arch.walk_mmu->gva_to_gpa succeeded, the page
		 * tables probably करो not match the TLB.  Just proceed
		 * with the error code that the processor gave.
		 */
		fault.vector = PF_VECTOR;
		fault.error_code_valid = true;
		fault.error_code = error_code;
		fault.nested_page_fault = false;
		fault.address = gva;
	पूर्ण
	vcpu->arch.walk_mmu->inject_page_fault(vcpu, &fault);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_fixup_and_inject_pf_error);

/*
 * Handles kvm_पढ़ो/ग_लिखो_guest_virt*() result and either injects #PF or वापसs
 * KVM_EXIT_INTERNAL_ERROR क्रम हालs not currently handled by KVM. Return value
 * indicates whether निकास to userspace is needed.
 */
पूर्णांक kvm_handle_memory_failure(काष्ठा kvm_vcpu *vcpu, पूर्णांक r,
			      काष्ठा x86_exception *e)
अणु
	अगर (r == X86EMUL_PROPAGATE_FAULT) अणु
		kvm_inject_emulated_page_fault(vcpu, e);
		वापस 1;
	पूर्ण

	/*
	 * In हाल kvm_पढ़ो/ग_लिखो_guest_virt*() failed with X86EMUL_IO_NEEDED
	 * जबतक handling a VMX inकाष्ठाion KVM could've handled the request
	 * correctly by निकासing to userspace and perक्रमming I/O but there
	 * करोesn't seem to be a real use-हाल behind such requests, just वापस
	 * KVM_EXIT_INTERNAL_ERROR क्रम now.
	 */
	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
	vcpu->run->पूर्णांकernal.ndata = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_handle_memory_failure);

पूर्णांक kvm_handle_invpcid(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ type, gva_t gva)
अणु
	bool pcid_enabled;
	काष्ठा x86_exception e;
	अचिन्हित i;
	अचिन्हित दीर्घ roots_to_मुक्त = 0;
	काष्ठा अणु
		u64 pcid;
		u64 gla;
	पूर्ण opeअक्रम;
	पूर्णांक r;

	r = kvm_पढ़ो_guest_virt(vcpu, gva, &opeअक्रम, माप(opeअक्रम), &e);
	अगर (r != X86EMUL_CONTINUE)
		वापस kvm_handle_memory_failure(vcpu, r, &e);

	अगर (opeअक्रम.pcid >> 12 != 0) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	pcid_enabled = kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PCIDE);

	चयन (type) अणु
	हाल INVPCID_TYPE_INDIV_ADDR:
		अगर ((!pcid_enabled && (opeअक्रम.pcid != 0)) ||
		    is_noncanonical_address(opeअक्रम.gla, vcpu)) अणु
			kvm_inject_gp(vcpu, 0);
			वापस 1;
		पूर्ण
		kvm_mmu_invpcid_gva(vcpu, opeअक्रम.gla, opeअक्रम.pcid);
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);

	हाल INVPCID_TYPE_SINGLE_CTXT:
		अगर (!pcid_enabled && (opeअक्रम.pcid != 0)) अणु
			kvm_inject_gp(vcpu, 0);
			वापस 1;
		पूर्ण

		अगर (kvm_get_active_pcid(vcpu) == opeअक्रम.pcid) अणु
			kvm_mmu_sync_roots(vcpu);
			kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
		पूर्ण

		क्रम (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++)
			अगर (kvm_get_pcid(vcpu, vcpu->arch.mmu->prev_roots[i].pgd)
			    == opeअक्रम.pcid)
				roots_to_मुक्त |= KVM_MMU_ROOT_PREVIOUS(i);

		kvm_mmu_मुक्त_roots(vcpu, vcpu->arch.mmu, roots_to_मुक्त);
		/*
		 * If neither the current cr3 nor any of the prev_roots use the
		 * given PCID, then nothing needs to be करोne here because a
		 * resync will happen anyway beक्रमe चयनing to any other CR3.
		 */

		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);

	हाल INVPCID_TYPE_ALL_NON_GLOBAL:
		/*
		 * Currently, KVM करोesn't mark global entries in the shaकरोw
		 * page tables, so a non-global flush just degenerates to a
		 * global flush. If needed, we could optimize this later by
		 * keeping track of global entries in shaकरोw page tables.
		 */

		fallthrough;
	हाल INVPCID_TYPE_ALL_INCL_GLOBAL:
		kvm_make_request(KVM_REQ_MMU_RELOAD, vcpu);
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);

	शेष:
		BUG(); /* We have alपढ़ोy checked above that type <= 3 */
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_handle_invpcid);

अटल पूर्णांक complete_sev_es_emulated_mmio(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	काष्ठा kvm_mmio_fragment *frag;
	अचिन्हित पूर्णांक len;

	BUG_ON(!vcpu->mmio_needed);

	/* Complete previous fragment */
	frag = &vcpu->mmio_fragments[vcpu->mmio_cur_fragment];
	len = min(8u, frag->len);
	अगर (!vcpu->mmio_is_ग_लिखो)
		स_नकल(frag->data, run->mmio.data, len);

	अगर (frag->len <= 8) अणु
		/* Switch to the next fragment. */
		frag++;
		vcpu->mmio_cur_fragment++;
	पूर्ण अन्यथा अणु
		/* Go क्रमward to the next mmio piece. */
		frag->data += len;
		frag->gpa += len;
		frag->len -= len;
	पूर्ण

	अगर (vcpu->mmio_cur_fragment >= vcpu->mmio_nr_fragments) अणु
		vcpu->mmio_needed = 0;

		// VMG change, at this poपूर्णांक, we're always करोne
		// RIP has alपढ़ोy been advanced
		वापस 1;
	पूर्ण

	// More MMIO is needed
	run->mmio.phys_addr = frag->gpa;
	run->mmio.len = min(8u, frag->len);
	run->mmio.is_ग_लिखो = vcpu->mmio_is_ग_लिखो;
	अगर (run->mmio.is_ग_लिखो)
		स_नकल(run->mmio.data, frag->data, min(8u, frag->len));
	run->निकास_reason = KVM_EXIT_MMIO;

	vcpu->arch.complete_userspace_io = complete_sev_es_emulated_mmio;

	वापस 0;
पूर्ण

पूर्णांक kvm_sev_es_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, अचिन्हित पूर्णांक bytes,
			  व्योम *data)
अणु
	पूर्णांक handled;
	काष्ठा kvm_mmio_fragment *frag;

	अगर (!data)
		वापस -EINVAL;

	handled = ग_लिखो_emultor.पढ़ो_ग_लिखो_mmio(vcpu, gpa, bytes, data);
	अगर (handled == bytes)
		वापस 1;

	bytes -= handled;
	gpa += handled;
	data += handled;

	/*TODO: Check अगर need to increment number of frags */
	frag = vcpu->mmio_fragments;
	vcpu->mmio_nr_fragments = 1;
	frag->len = bytes;
	frag->gpa = gpa;
	frag->data = data;

	vcpu->mmio_needed = 1;
	vcpu->mmio_cur_fragment = 0;

	vcpu->run->mmio.phys_addr = gpa;
	vcpu->run->mmio.len = min(8u, frag->len);
	vcpu->run->mmio.is_ग_लिखो = 1;
	स_नकल(vcpu->run->mmio.data, frag->data, min(8u, frag->len));
	vcpu->run->निकास_reason = KVM_EXIT_MMIO;

	vcpu->arch.complete_userspace_io = complete_sev_es_emulated_mmio;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_sev_es_mmio_ग_लिखो);

पूर्णांक kvm_sev_es_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, अचिन्हित पूर्णांक bytes,
			 व्योम *data)
अणु
	पूर्णांक handled;
	काष्ठा kvm_mmio_fragment *frag;

	अगर (!data)
		वापस -EINVAL;

	handled = पढ़ो_emultor.पढ़ो_ग_लिखो_mmio(vcpu, gpa, bytes, data);
	अगर (handled == bytes)
		वापस 1;

	bytes -= handled;
	gpa += handled;
	data += handled;

	/*TODO: Check अगर need to increment number of frags */
	frag = vcpu->mmio_fragments;
	vcpu->mmio_nr_fragments = 1;
	frag->len = bytes;
	frag->gpa = gpa;
	frag->data = data;

	vcpu->mmio_needed = 1;
	vcpu->mmio_cur_fragment = 0;

	vcpu->run->mmio.phys_addr = gpa;
	vcpu->run->mmio.len = min(8u, frag->len);
	vcpu->run->mmio.is_ग_लिखो = 0;
	vcpu->run->निकास_reason = KVM_EXIT_MMIO;

	vcpu->arch.complete_userspace_io = complete_sev_es_emulated_mmio;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_sev_es_mmio_पढ़ो);

अटल पूर्णांक complete_sev_es_emulated_ins(काष्ठा kvm_vcpu *vcpu)
अणु
	स_नकल(vcpu->arch.guest_ins_data, vcpu->arch.pio_data,
	       vcpu->arch.pio.count * vcpu->arch.pio.size);
	vcpu->arch.pio.count = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक kvm_sev_es_outs(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक size,
			   अचिन्हित पूर्णांक port, व्योम *data,  अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;

	ret = emulator_pio_out_emulated(vcpu->arch.emulate_ctxt, size, port,
					data, count);
	अगर (ret)
		वापस ret;

	vcpu->arch.pio.count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_sev_es_ins(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक size,
			  अचिन्हित पूर्णांक port, व्योम *data, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;

	ret = emulator_pio_in_emulated(vcpu->arch.emulate_ctxt, size, port,
				       data, count);
	अगर (ret) अणु
		vcpu->arch.pio.count = 0;
	पूर्ण अन्यथा अणु
		vcpu->arch.guest_ins_data = data;
		vcpu->arch.complete_userspace_io = complete_sev_es_emulated_ins;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvm_sev_es_string_io(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक size,
			 अचिन्हित पूर्णांक port, व्योम *data,  अचिन्हित पूर्णांक count,
			 पूर्णांक in)
अणु
	वापस in ? kvm_sev_es_ins(vcpu, size, port, data, count)
		  : kvm_sev_es_outs(vcpu, size, port, data, count);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_sev_es_string_io);

EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_entry);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_निकास);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_fast_mmio);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_inj_virq);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_page_fault);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_msr);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_cr);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_vmrun);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_vmनिकास);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_vmनिकास_inject);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_पूर्णांकr_vmनिकास);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_vmenter_failed);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_invlpga);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_skinit);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_nested_पूर्णांकercepts);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_ग_लिखो_tsc_offset);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_ple_winकरोw_update);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_pml_full);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_pi_irte_update);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_avic_unaccelerated_access);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_avic_incomplete_ipi);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_avic_ga_log);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_apicv_update_request);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_vmgनिकास_enter);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_vmgनिकास_निकास);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_vmgनिकास_msr_protocol_enter);
EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_vmgनिकास_msr_protocol_निकास);
