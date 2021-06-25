<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * This module enables machines with Intel VT-x extensions to run भव
 * machines without emulation or binary translation.
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Avi Kivity   <avi@qumranet.com>
 *   Yaniv Kamay  <yaniv@qumranet.com>
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mm.h>
#समावेश <linux/objtool.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/smt.h>
#समावेश <linux/slab.h>
#समावेश <linux/tboot.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/entry-kvm.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/virtext.h>
#समावेश <यंत्र/vmx.h>

#समावेश "capabilities.h"
#समावेश "cpuid.h"
#समावेश "evmcs.h"
#समावेश "hyperv.h"
#समावेश "irq.h"
#समावेश "kvm_cache_regs.h"
#समावेश "lapic.h"
#समावेश "mmu.h"
#समावेश "nested.h"
#समावेश "pmu.h"
#समावेश "sgx.h"
#समावेश "trace.h"
#समावेश "vmcs.h"
#समावेश "vmcs12.h"
#समावेश "vmx.h"
#समावेश "x86.h"

MODULE_AUTHOR("Qumranet");
MODULE_LICENSE("GPL");

#अगर_घोषित MODULE
अटल स्थिर काष्ठा x86_cpu_id vmx_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_VMX, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, vmx_cpu_id);
#पूर्ण_अगर

bool __पढ़ो_mostly enable_vpid = 1;
module_param_named(vpid, enable_vpid, bool, 0444);

अटल bool __पढ़ो_mostly enable_vnmi = 1;
module_param_named(vnmi, enable_vnmi, bool, S_IRUGO);

bool __पढ़ो_mostly flexpriority_enabled = 1;
module_param_named(flexpriority, flexpriority_enabled, bool, S_IRUGO);

bool __पढ़ो_mostly enable_ept = 1;
module_param_named(ept, enable_ept, bool, S_IRUGO);

bool __पढ़ो_mostly enable_unrestricted_guest = 1;
module_param_named(unrestricted_guest,
			enable_unrestricted_guest, bool, S_IRUGO);

bool __पढ़ो_mostly enable_ept_ad_bits = 1;
module_param_named(eptad, enable_ept_ad_bits, bool, S_IRUGO);

अटल bool __पढ़ो_mostly emulate_invalid_guest_state = true;
module_param(emulate_invalid_guest_state, bool, S_IRUGO);

अटल bool __पढ़ो_mostly fasteoi = 1;
module_param(fasteoi, bool, S_IRUGO);

bool __पढ़ो_mostly enable_apicv = 1;
module_param(enable_apicv, bool, S_IRUGO);

/*
 * If nested=1, nested भवization is supported, i.e., guests may use
 * VMX and be a hypervisor क्रम its own guests. If nested=0, guests may not
 * use VMX inकाष्ठाions.
 */
अटल bool __पढ़ो_mostly nested = 1;
module_param(nested, bool, S_IRUGO);

bool __पढ़ो_mostly enable_pml = 1;
module_param_named(pml, enable_pml, bool, S_IRUGO);

अटल bool __पढ़ो_mostly dump_invalid_vmcs = 0;
module_param(dump_invalid_vmcs, bool, 0644);

#घोषणा MSR_BITMAP_MODE_X2APIC		1
#घोषणा MSR_BITMAP_MODE_X2APIC_APICV	2

#घोषणा KVM_VMX_TSC_MULTIPLIER_MAX     0xffffffffffffffffULL

/* Guest_tsc -> host_tsc conversion requires 64-bit भागision.  */
अटल पूर्णांक __पढ़ो_mostly cpu_preemption_समयr_multi;
अटल bool __पढ़ो_mostly enable_preemption_समयr = 1;
#अगर_घोषित CONFIG_X86_64
module_param_named(preemption_समयr, enable_preemption_समयr, bool, S_IRUGO);
#पूर्ण_अगर

बाह्य bool __पढ़ो_mostly allow_smaller_maxphyaddr;
module_param(allow_smaller_maxphyaddr, bool, S_IRUGO);

#घोषणा KVM_VM_CR0_ALWAYS_OFF (X86_CR0_NW | X86_CR0_CD)
#घोषणा KVM_VM_CR0_ALWAYS_ON_UNRESTRICTED_GUEST X86_CR0_NE
#घोषणा KVM_VM_CR0_ALWAYS_ON				\
	(KVM_VM_CR0_ALWAYS_ON_UNRESTRICTED_GUEST | 	\
	 X86_CR0_WP | X86_CR0_PG | X86_CR0_PE)

#घोषणा KVM_VM_CR4_ALWAYS_ON_UNRESTRICTED_GUEST X86_CR4_VMXE
#घोषणा KVM_PMODE_VM_CR4_ALWAYS_ON (X86_CR4_PAE | X86_CR4_VMXE)
#घोषणा KVM_RMODE_VM_CR4_ALWAYS_ON (X86_CR4_VME | X86_CR4_PAE | X86_CR4_VMXE)

#घोषणा RMODE_GUEST_OWNED_EFLAGS_BITS (~(X86_EFLAGS_IOPL | X86_EFLAGS_VM))

#घोषणा MSR_IA32_RTIT_STATUS_MASK (~(RTIT_STATUS_FILTEREN | \
	RTIT_STATUS_CONTEXTEN | RTIT_STATUS_TRIGGEREN | \
	RTIT_STATUS_ERROR | RTIT_STATUS_STOPPED | \
	RTIT_STATUS_BYTECNT))

/*
 * List of MSRs that can be directly passed to the guest.
 * In addition to these x2apic and PT MSRs are handled specially.
 */
अटल u32 vmx_possible_passthrough_msrs[MAX_POSSIBLE_PASSTHROUGH_MSRS] = अणु
	MSR_IA32_SPEC_CTRL,
	MSR_IA32_PRED_CMD,
	MSR_IA32_TSC,
#अगर_घोषित CONFIG_X86_64
	MSR_FS_BASE,
	MSR_GS_BASE,
	MSR_KERNEL_GS_BASE,
#पूर्ण_अगर
	MSR_IA32_SYSENTER_CS,
	MSR_IA32_SYSENTER_ESP,
	MSR_IA32_SYSENTER_EIP,
	MSR_CORE_C1_RES,
	MSR_CORE_C3_RESIDENCY,
	MSR_CORE_C6_RESIDENCY,
	MSR_CORE_C7_RESIDENCY,
पूर्ण;

/*
 * These 2 parameters are used to config the controls क्रम Pause-Loop Exiting:
 * ple_gap:    upper bound on the amount of समय between two successive
 *             executions of PAUSE in a loop. Also indicate अगर ple enabled.
 *             According to test, this समय is usually smaller than 128 cycles.
 * ple_winकरोw: upper bound on the amount of समय a guest is allowed to execute
 *             in a PAUSE loop. Tests indicate that most spinlocks are held क्रम
 *             less than 2^12 cycles
 * Time is measured based on a counter that runs at the same rate as the TSC,
 * refer SDM volume 3b section 21.6.13 & 22.1.3.
 */
अटल अचिन्हित पूर्णांक ple_gap = KVM_DEFAULT_PLE_GAP;
module_param(ple_gap, uपूर्णांक, 0444);

अटल अचिन्हित पूर्णांक ple_winकरोw = KVM_VMX_DEFAULT_PLE_WINDOW;
module_param(ple_winकरोw, uपूर्णांक, 0444);

/* Default द्विगुनs per-vcpu winकरोw every निकास. */
अटल अचिन्हित पूर्णांक ple_winकरोw_grow = KVM_DEFAULT_PLE_WINDOW_GROW;
module_param(ple_winकरोw_grow, uपूर्णांक, 0444);

/* Default resets per-vcpu winकरोw every निकास to ple_winकरोw. */
अटल अचिन्हित पूर्णांक ple_winकरोw_shrink = KVM_DEFAULT_PLE_WINDOW_SHRINK;
module_param(ple_winकरोw_shrink, uपूर्णांक, 0444);

/* Default is to compute the maximum so we can never overflow. */
अटल अचिन्हित पूर्णांक ple_winकरोw_max        = KVM_VMX_DEFAULT_PLE_WINDOW_MAX;
module_param(ple_winकरोw_max, uपूर्णांक, 0444);

/* Default is SYSTEM mode, 1 क्रम host-guest mode */
पूर्णांक __पढ़ो_mostly pt_mode = PT_MODE_SYSTEM;
module_param(pt_mode, पूर्णांक, S_IRUGO);

अटल DEFINE_STATIC_KEY_FALSE(vmx_l1d_should_flush);
अटल DEFINE_STATIC_KEY_FALSE(vmx_l1d_flush_cond);
अटल DEFINE_MUTEX(vmx_l1d_flush_mutex);

/* Storage क्रम pre module init parameter parsing */
अटल क्रमागत vmx_l1d_flush_state __पढ़ो_mostly vmentry_l1d_flush_param = VMENTER_L1D_FLUSH_AUTO;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *option;
	bool क्रम_parse;
पूर्ण vmentry_l1d_param[] = अणु
	[VMENTER_L1D_FLUSH_AUTO]	 = अणु"auto", trueपूर्ण,
	[VMENTER_L1D_FLUSH_NEVER]	 = अणु"never", trueपूर्ण,
	[VMENTER_L1D_FLUSH_COND]	 = अणु"cond", trueपूर्ण,
	[VMENTER_L1D_FLUSH_ALWAYS]	 = अणु"always", trueपूर्ण,
	[VMENTER_L1D_FLUSH_EPT_DISABLED] = अणु"EPT disabled", falseपूर्ण,
	[VMENTER_L1D_FLUSH_NOT_REQUIRED] = अणु"not required", falseपूर्ण,
पूर्ण;

#घोषणा L1D_CACHE_ORDER 4
अटल व्योम *vmx_l1d_flush_pages;

अटल पूर्णांक vmx_setup_l1d_flush(क्रमागत vmx_l1d_flush_state l1tf)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक i;

	अगर (!boot_cpu_has_bug(X86_BUG_L1TF)) अणु
		l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_NOT_REQUIRED;
		वापस 0;
	पूर्ण

	अगर (!enable_ept) अणु
		l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_EPT_DISABLED;
		वापस 0;
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_ARCH_CAPABILITIES)) अणु
		u64 msr;

		rdmsrl(MSR_IA32_ARCH_CAPABILITIES, msr);
		अगर (msr & ARCH_CAP_SKIP_VMENTRY_L1DFLUSH) अणु
			l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_NOT_REQUIRED;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If set to स्वतः use the शेष l1tf mitigation method */
	अगर (l1tf == VMENTER_L1D_FLUSH_AUTO) अणु
		चयन (l1tf_mitigation) अणु
		हाल L1TF_MITIGATION_OFF:
			l1tf = VMENTER_L1D_FLUSH_NEVER;
			अवरोध;
		हाल L1TF_MITIGATION_FLUSH_NOWARN:
		हाल L1TF_MITIGATION_FLUSH:
		हाल L1TF_MITIGATION_FLUSH_NOSMT:
			l1tf = VMENTER_L1D_FLUSH_COND;
			अवरोध;
		हाल L1TF_MITIGATION_FULL:
		हाल L1TF_MITIGATION_FULL_FORCE:
			l1tf = VMENTER_L1D_FLUSH_ALWAYS;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (l1tf_mitigation == L1TF_MITIGATION_FULL_FORCE) अणु
		l1tf = VMENTER_L1D_FLUSH_ALWAYS;
	पूर्ण

	अगर (l1tf != VMENTER_L1D_FLUSH_NEVER && !vmx_l1d_flush_pages &&
	    !boot_cpu_has(X86_FEATURE_FLUSH_L1D)) अणु
		/*
		 * This allocation क्रम vmx_l1d_flush_pages is not tied to a VM
		 * lअगरeसमय and so should not be अक्षरged to a memcg.
		 */
		page = alloc_pages(GFP_KERNEL, L1D_CACHE_ORDER);
		अगर (!page)
			वापस -ENOMEM;
		vmx_l1d_flush_pages = page_address(page);

		/*
		 * Initialize each page with a dअगरferent pattern in
		 * order to protect against KSM in the nested
		 * भवization हाल.
		 */
		क्रम (i = 0; i < 1u << L1D_CACHE_ORDER; ++i) अणु
			स_रखो(vmx_l1d_flush_pages + i * PAGE_SIZE, i + 1,
			       PAGE_SIZE);
		पूर्ण
	पूर्ण

	l1tf_vmx_mitigation = l1tf;

	अगर (l1tf != VMENTER_L1D_FLUSH_NEVER)
		अटल_branch_enable(&vmx_l1d_should_flush);
	अन्यथा
		अटल_branch_disable(&vmx_l1d_should_flush);

	अगर (l1tf == VMENTER_L1D_FLUSH_COND)
		अटल_branch_enable(&vmx_l1d_flush_cond);
	अन्यथा
		अटल_branch_disable(&vmx_l1d_flush_cond);
	वापस 0;
पूर्ण

अटल पूर्णांक vmentry_l1d_flush_parse(स्थिर अक्षर *s)
अणु
	अचिन्हित पूर्णांक i;

	अगर (s) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vmentry_l1d_param); i++) अणु
			अगर (vmentry_l1d_param[i].क्रम_parse &&
			    sysfs_streq(s, vmentry_l1d_param[i].option))
				वापस i;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vmentry_l1d_flush_set(स्थिर अक्षर *s, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक l1tf, ret;

	l1tf = vmentry_l1d_flush_parse(s);
	अगर (l1tf < 0)
		वापस l1tf;

	अगर (!boot_cpu_has(X86_BUG_L1TF))
		वापस 0;

	/*
	 * Has vmx_init() run alपढ़ोy? If not then this is the pre init
	 * parameter parsing. In that हाल just store the value and let
	 * vmx_init() करो the proper setup after enable_ept has been
	 * established.
	 */
	अगर (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_AUTO) अणु
		vmentry_l1d_flush_param = l1tf;
		वापस 0;
	पूर्ण

	mutex_lock(&vmx_l1d_flush_mutex);
	ret = vmx_setup_l1d_flush(l1tf);
	mutex_unlock(&vmx_l1d_flush_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vmentry_l1d_flush_get(अक्षर *s, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (WARN_ON_ONCE(l1tf_vmx_mitigation >= ARRAY_SIZE(vmentry_l1d_param)))
		वापस प्र_लिखो(s, "???\n");

	वापस प्र_लिखो(s, "%s\n", vmentry_l1d_param[l1tf_vmx_mitigation].option);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops vmentry_l1d_flush_ops = अणु
	.set = vmentry_l1d_flush_set,
	.get = vmentry_l1d_flush_get,
पूर्ण;
module_param_cb(vmentry_l1d_flush, &vmentry_l1d_flush_ops, शून्य, 0644);

अटल u32 vmx_segment_access_rights(काष्ठा kvm_segment *var);

व्योम vmx_vmनिकास(व्योम);

#घोषणा vmx_insn_failed(fmt...)		\
करो अणु					\
	WARN_ONCE(1, fmt);		\
	pr_warn_ratelimited(fmt);	\
पूर्ण जबतक (0)

यंत्रlinkage व्योम vmपढ़ो_error(अचिन्हित दीर्घ field, bool fault)
अणु
	अगर (fault)
		kvm_spurious_fault();
	अन्यथा
		vmx_insn_failed("kvm: vmread failed: field=%lx\n", field);
पूर्ण

noअंतरभूत व्योम vmग_लिखो_error(अचिन्हित दीर्घ field, अचिन्हित दीर्घ value)
अणु
	vmx_insn_failed("kvm: vmwrite failed: field=%lx val=%lx err=%d\n",
			field, value, vmcs_पढ़ो32(VM_INSTRUCTION_ERROR));
पूर्ण

noअंतरभूत व्योम vmclear_error(काष्ठा vmcs *vmcs, u64 phys_addr)
अणु
	vmx_insn_failed("kvm: vmclear failed: %p/%llx\n", vmcs, phys_addr);
पूर्ण

noअंतरभूत व्योम vmptrld_error(काष्ठा vmcs *vmcs, u64 phys_addr)
अणु
	vmx_insn_failed("kvm: vmptrld failed: %p/%llx\n", vmcs, phys_addr);
पूर्ण

noअंतरभूत व्योम invvpid_error(अचिन्हित दीर्घ ext, u16 vpid, gva_t gva)
अणु
	vmx_insn_failed("kvm: invvpid failed: ext=0x%lx vpid=%u gva=0x%lx\n",
			ext, vpid, gva);
पूर्ण

noअंतरभूत व्योम invept_error(अचिन्हित दीर्घ ext, u64 eptp, gpa_t gpa)
अणु
	vmx_insn_failed("kvm: invept failed: ext=0x%lx eptp=%llx gpa=0x%llx\n",
			ext, eptp, gpa);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा vmcs *, vmxarea);
DEFINE_PER_CPU(काष्ठा vmcs *, current_vmcs);
/*
 * We मुख्यtain a per-CPU linked-list of VMCS loaded on that CPU. This is needed
 * when a CPU is brought करोwn, and we need to VMCLEAR all VMCSs loaded on it.
 */
अटल DEFINE_PER_CPU(काष्ठा list_head, loaded_vmcss_on_cpu);

अटल DECLARE_BITMAP(vmx_vpid_biपंचांगap, VMX_NR_VPIDS);
अटल DEFINE_SPINLOCK(vmx_vpid_lock);

काष्ठा vmcs_config vmcs_config;
काष्ठा vmx_capability vmx_capability;

#घोषणा VMX_SEGMENT_FIELD(seg)					\
	[VCPU_SREG_##seg] = अणु                                   \
		.selector = GUEST_##seg##_SELECTOR,		\
		.base = GUEST_##seg##_BASE,		   	\
		.limit = GUEST_##seg##_LIMIT,		   	\
		.ar_bytes = GUEST_##seg##_AR_BYTES,	   	\
	पूर्ण

अटल स्थिर काष्ठा kvm_vmx_segment_field अणु
	अचिन्हित selector;
	अचिन्हित base;
	अचिन्हित limit;
	अचिन्हित ar_bytes;
पूर्ण kvm_vmx_segment_fields[] = अणु
	VMX_SEGMENT_FIELD(CS),
	VMX_SEGMENT_FIELD(DS),
	VMX_SEGMENT_FIELD(ES),
	VMX_SEGMENT_FIELD(FS),
	VMX_SEGMENT_FIELD(GS),
	VMX_SEGMENT_FIELD(SS),
	VMX_SEGMENT_FIELD(TR),
	VMX_SEGMENT_FIELD(LDTR),
पूर्ण;

अटल अंतरभूत व्योम vmx_segment_cache_clear(काष्ठा vcpu_vmx *vmx)
अणु
	vmx->segment_cache.biपंचांगask = 0;
पूर्ण

अटल अचिन्हित दीर्घ host_idt_base;

#अगर IS_ENABLED(CONFIG_HYPERV)
अटल bool __पढ़ो_mostly enlightened_vmcs = true;
module_param(enlightened_vmcs, bool, 0444);

अटल पूर्णांक kvm_fill_hv_flush_list_func(काष्ठा hv_guest_mapping_flush_list *flush,
		व्योम *data)
अणु
	काष्ठा kvm_tlb_range *range = data;

	वापस hyperv_fill_flush_guest_mapping_list(flush, range->start_gfn,
			range->pages);
पूर्ण

अटल अंतरभूत पूर्णांक hv_remote_flush_root_ept(hpa_t root_ept,
					   काष्ठा kvm_tlb_range *range)
अणु
	अगर (range)
		वापस hyperv_flush_guest_mapping_range(root_ept,
				kvm_fill_hv_flush_list_func, (व्योम *)range);
	अन्यथा
		वापस hyperv_flush_guest_mapping(root_ept);
पूर्ण

अटल पूर्णांक hv_remote_flush_tlb_with_range(काष्ठा kvm *kvm,
		काष्ठा kvm_tlb_range *range)
अणु
	काष्ठा kvm_vmx *kvm_vmx = to_kvm_vmx(kvm);
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक ret = 0, i, nr_unique_valid_roots;
	hpa_t root;

	spin_lock(&kvm_vmx->hv_root_ept_lock);

	अगर (!VALID_PAGE(kvm_vmx->hv_root_ept)) अणु
		nr_unique_valid_roots = 0;

		/*
		 * Flush all valid roots, and see अगर all vCPUs have converged
		 * on a common root, in which हाल future flushes can skip the
		 * loop and flush the common root.
		 */
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			root = to_vmx(vcpu)->hv_root_ept;
			अगर (!VALID_PAGE(root) || root == kvm_vmx->hv_root_ept)
				जारी;

			/*
			 * Set the tracked root to the first valid root.  Keep
			 * this root क्रम the entirety of the loop even अगर more
			 * roots are encountered as a low efक्रमt optimization
			 * to aव्योम flushing the same (first) root again.
			 */
			अगर (++nr_unique_valid_roots == 1)
				kvm_vmx->hv_root_ept = root;

			अगर (!ret)
				ret = hv_remote_flush_root_ept(root, range);

			/*
			 * Stop processing roots अगर a failure occurred and
			 * multiple valid roots have alपढ़ोy been detected.
			 */
			अगर (ret && nr_unique_valid_roots > 1)
				अवरोध;
		पूर्ण

		/*
		 * The optimized flush of a single root can't be used अगर there
		 * are multiple valid roots (obviously).
		 */
		अगर (nr_unique_valid_roots > 1)
			kvm_vmx->hv_root_ept = INVALID_PAGE;
	पूर्ण अन्यथा अणु
		ret = hv_remote_flush_root_ept(kvm_vmx->hv_root_ept, range);
	पूर्ण

	spin_unlock(&kvm_vmx->hv_root_ept_lock);
	वापस ret;
पूर्ण
अटल पूर्णांक hv_remote_flush_tlb(काष्ठा kvm *kvm)
अणु
	वापस hv_remote_flush_tlb_with_range(kvm, शून्य);
पूर्ण

अटल पूर्णांक hv_enable_direct_tlbflush(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा hv_enlightened_vmcs *evmcs;
	काष्ठा hv_partition_assist_pg **p_hv_pa_pg =
			&to_kvm_hv(vcpu->kvm)->hv_pa_pg;
	/*
	 * Synthetic VM-Exit is not enabled in current code and so All
	 * evmcs in singe VM shares same assist page.
	 */
	अगर (!*p_hv_pa_pg)
		*p_hv_pa_pg = kzalloc(PAGE_SIZE, GFP_KERNEL_ACCOUNT);

	अगर (!*p_hv_pa_pg)
		वापस -ENOMEM;

	evmcs = (काष्ठा hv_enlightened_vmcs *)to_vmx(vcpu)->loaded_vmcs->vmcs;

	evmcs->partition_assist_page =
		__pa(*p_hv_pa_pg);
	evmcs->hv_vm_id = (अचिन्हित दीर्घ)vcpu->kvm;
	evmcs->hv_enlightenments_control.nested_flush_hypercall = 1;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_HYPERV) */

अटल व्योम hv_track_root_ept(काष्ठा kvm_vcpu *vcpu, hpa_t root_ept)
अणु
#अगर IS_ENABLED(CONFIG_HYPERV)
	काष्ठा kvm_vmx *kvm_vmx = to_kvm_vmx(vcpu->kvm);

	अगर (kvm_x86_ops.tlb_remote_flush == hv_remote_flush_tlb) अणु
		spin_lock(&kvm_vmx->hv_root_ept_lock);
		to_vmx(vcpu)->hv_root_ept = root_ept;
		अगर (root_ept != kvm_vmx->hv_root_ept)
			kvm_vmx->hv_root_ept = INVALID_PAGE;
		spin_unlock(&kvm_vmx->hv_root_ept_lock);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Comment's क्रमmat: करोcument - errata name - stepping - processor name.
 * Refer from
 * https://www.भवbox.org/svn/vbox/trunk/src/VBox/VMM/VMMR0/HMR0.cpp
 */
अटल u32 vmx_preemption_cpu_tfms[] = अणु
/* 323344.pdf - BA86   - D0 - Xeon 7500 Series */
0x000206E6,
/* 323056.pdf - AAX65  - C2 - Xeon L3406 */
/* 322814.pdf - AAT59  - C2 - i7-600, i5-500, i5-400 and i3-300 Mobile */
/* 322911.pdf - AAU65  - C2 - i5-600, i3-500 Desktop and Pentium G6950 */
0x00020652,
/* 322911.pdf - AAU65  - K0 - i5-600, i3-500 Desktop and Pentium G6950 */
0x00020655,
/* 322373.pdf - AAO95  - B1 - Xeon 3400 Series */
/* 322166.pdf - AAN92  - B1 - i7-800 and i5-700 Desktop */
/*
 * 320767.pdf - AAP86  - B1 -
 * i7-900 Mobile Extreme, i7-800 and i7-700 Mobile
 */
0x000106E5,
/* 321333.pdf - AAM126 - C0 - Xeon 3500 */
0x000106A0,
/* 321333.pdf - AAM126 - C1 - Xeon 3500 */
0x000106A1,
/* 320836.pdf - AAJ124 - C0 - i7-900 Desktop Extreme and i7-900 Desktop */
0x000106A4,
 /* 321333.pdf - AAM126 - D0 - Xeon 3500 */
 /* 321324.pdf - AAK139 - D0 - Xeon 5500 */
 /* 320836.pdf - AAJ124 - D0 - i7-900 Extreme and i7-900 Desktop */
0x000106A5,
 /* Xeon E3-1220 V2 */
0x000306A8,
पूर्ण;

अटल अंतरभूत bool cpu_has_broken_vmx_preemption_समयr(व्योम)
अणु
	u32 eax = cpuid_eax(0x00000001), i;

	/* Clear the reserved bits */
	eax &= ~(0x3U << 14 | 0xfU << 28);
	क्रम (i = 0; i < ARRAY_SIZE(vmx_preemption_cpu_tfms); i++)
		अगर (eax == vmx_preemption_cpu_tfms[i])
			वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool cpu_need_भवize_apic_accesses(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस flexpriority_enabled && lapic_in_kernel(vcpu);
पूर्ण

अटल अंतरभूत bool report_flexpriority(व्योम)
अणु
	वापस flexpriority_enabled;
पूर्ण

अटल पूर्णांक possible_passthrough_msr_slot(u32 msr)
अणु
	u32 i;

	क्रम (i = 0; i < ARRAY_SIZE(vmx_possible_passthrough_msrs); i++)
		अगर (vmx_possible_passthrough_msrs[i] == msr)
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल bool is_valid_passthrough_msr(u32 msr)
अणु
	bool r;

	चयन (msr) अणु
	हाल 0x800 ... 0x8ff:
		/* x2APIC MSRs. These are handled in vmx_update_msr_biपंचांगap_x2apic() */
		वापस true;
	हाल MSR_IA32_RTIT_STATUS:
	हाल MSR_IA32_RTIT_OUTPUT_BASE:
	हाल MSR_IA32_RTIT_OUTPUT_MASK:
	हाल MSR_IA32_RTIT_CR3_MATCH:
	हाल MSR_IA32_RTIT_ADDR0_A ... MSR_IA32_RTIT_ADDR3_B:
		/* PT MSRs. These are handled in pt_update_पूर्णांकercept_क्रम_msr() */
	हाल MSR_LBR_SELECT:
	हाल MSR_LBR_TOS:
	हाल MSR_LBR_INFO_0 ... MSR_LBR_INFO_0 + 31:
	हाल MSR_LBR_NHM_FROM ... MSR_LBR_NHM_FROM + 31:
	हाल MSR_LBR_NHM_TO ... MSR_LBR_NHM_TO + 31:
	हाल MSR_LBR_CORE_FROM ... MSR_LBR_CORE_FROM + 8:
	हाल MSR_LBR_CORE_TO ... MSR_LBR_CORE_TO + 8:
		/* LBR MSRs. These are handled in vmx_update_पूर्णांकercept_क्रम_lbr_msrs() */
		वापस true;
	पूर्ण

	r = possible_passthrough_msr_slot(msr) != -ENOENT;

	WARN(!r, "Invalid MSR %x, please adapt vmx_possible_passthrough_msrs[]", msr);

	वापस r;
पूर्ण

काष्ठा vmx_uret_msr *vmx_find_uret_msr(काष्ठा vcpu_vmx *vmx, u32 msr)
अणु
	पूर्णांक i;

	i = kvm_find_user_वापस_msr(msr);
	अगर (i >= 0)
		वापस &vmx->guest_uret_msrs[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक vmx_set_guest_uret_msr(काष्ठा vcpu_vmx *vmx,
				  काष्ठा vmx_uret_msr *msr, u64 data)
अणु
	अचिन्हित पूर्णांक slot = msr - vmx->guest_uret_msrs;
	पूर्णांक ret = 0;

	u64 old_msr_data = msr->data;
	msr->data = data;
	अगर (msr->load_पूर्णांकo_hardware) अणु
		preempt_disable();
		ret = kvm_set_user_वापस_msr(slot, msr->data, msr->mask);
		preempt_enable();
		अगर (ret)
			msr->data = old_msr_data;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम crash_vmclear_local_loaded_vmcss(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा loaded_vmcs *v;

	list_क्रम_each_entry(v, &per_cpu(loaded_vmcss_on_cpu, cpu),
			    loaded_vmcss_on_cpu_link)
		vmcs_clear(v->vmcs);
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

अटल व्योम __loaded_vmcs_clear(व्योम *arg)
अणु
	काष्ठा loaded_vmcs *loaded_vmcs = arg;
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (loaded_vmcs->cpu != cpu)
		वापस; /* vcpu migration can race with cpu offline */
	अगर (per_cpu(current_vmcs, cpu) == loaded_vmcs->vmcs)
		per_cpu(current_vmcs, cpu) = शून्य;

	vmcs_clear(loaded_vmcs->vmcs);
	अगर (loaded_vmcs->shaकरोw_vmcs && loaded_vmcs->launched)
		vmcs_clear(loaded_vmcs->shaकरोw_vmcs);

	list_del(&loaded_vmcs->loaded_vmcss_on_cpu_link);

	/*
	 * Ensure all ग_लिखोs to loaded_vmcs, including deleting it from its
	 * current percpu list, complete beक्रमe setting loaded_vmcs->vcpu to
	 * -1, otherwise a dअगरferent cpu can see vcpu == -1 first and add
	 * loaded_vmcs to its percpu list beक्रमe it's deleted from this cpu's
	 * list. Pairs with the smp_rmb() in vmx_vcpu_load_vmcs().
	 */
	smp_wmb();

	loaded_vmcs->cpu = -1;
	loaded_vmcs->launched = 0;
पूर्ण

व्योम loaded_vmcs_clear(काष्ठा loaded_vmcs *loaded_vmcs)
अणु
	पूर्णांक cpu = loaded_vmcs->cpu;

	अगर (cpu != -1)
		smp_call_function_single(cpu,
			 __loaded_vmcs_clear, loaded_vmcs, 1);
पूर्ण

अटल bool vmx_segment_cache_test_set(काष्ठा vcpu_vmx *vmx, अचिन्हित seg,
				       अचिन्हित field)
अणु
	bool ret;
	u32 mask = 1 << (seg * SEG_FIELD_NR + field);

	अगर (!kvm_रेजिस्टर_is_available(&vmx->vcpu, VCPU_EXREG_SEGMENTS)) अणु
		kvm_रेजिस्टर_mark_available(&vmx->vcpu, VCPU_EXREG_SEGMENTS);
		vmx->segment_cache.biपंचांगask = 0;
	पूर्ण
	ret = vmx->segment_cache.biपंचांगask & mask;
	vmx->segment_cache.biपंचांगask |= mask;
	वापस ret;
पूर्ण

अटल u16 vmx_पढ़ो_guest_seg_selector(काष्ठा vcpu_vmx *vmx, अचिन्हित seg)
अणु
	u16 *p = &vmx->segment_cache.seg[seg].selector;

	अगर (!vmx_segment_cache_test_set(vmx, seg, SEG_FIELD_SEL))
		*p = vmcs_पढ़ो16(kvm_vmx_segment_fields[seg].selector);
	वापस *p;
पूर्ण

अटल uदीर्घ vmx_पढ़ो_guest_seg_base(काष्ठा vcpu_vmx *vmx, अचिन्हित seg)
अणु
	uदीर्घ *p = &vmx->segment_cache.seg[seg].base;

	अगर (!vmx_segment_cache_test_set(vmx, seg, SEG_FIELD_BASE))
		*p = vmcs_पढ़ोl(kvm_vmx_segment_fields[seg].base);
	वापस *p;
पूर्ण

अटल u32 vmx_पढ़ो_guest_seg_limit(काष्ठा vcpu_vmx *vmx, अचिन्हित seg)
अणु
	u32 *p = &vmx->segment_cache.seg[seg].limit;

	अगर (!vmx_segment_cache_test_set(vmx, seg, SEG_FIELD_LIMIT))
		*p = vmcs_पढ़ो32(kvm_vmx_segment_fields[seg].limit);
	वापस *p;
पूर्ण

अटल u32 vmx_पढ़ो_guest_seg_ar(काष्ठा vcpu_vmx *vmx, अचिन्हित seg)
अणु
	u32 *p = &vmx->segment_cache.seg[seg].ar;

	अगर (!vmx_segment_cache_test_set(vmx, seg, SEG_FIELD_AR))
		*p = vmcs_पढ़ो32(kvm_vmx_segment_fields[seg].ar_bytes);
	वापस *p;
पूर्ण

व्योम vmx_update_exception_biपंचांगap(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 eb;

	eb = (1u << PF_VECTOR) | (1u << UD_VECTOR) | (1u << MC_VECTOR) |
	     (1u << DB_VECTOR) | (1u << AC_VECTOR);
	/*
	 * Guest access to VMware backकरोor ports could legitimately
	 * trigger #GP because of TSS I/O permission biपंचांगap.
	 * We पूर्णांकercept those #GP and allow access to them anyway
	 * as VMware करोes.
	 */
	अगर (enable_vmware_backकरोor)
		eb |= (1u << GP_VECTOR);
	अगर ((vcpu->guest_debug &
	     (KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_SW_BP)) ==
	    (KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_SW_BP))
		eb |= 1u << BP_VECTOR;
	अगर (to_vmx(vcpu)->rmode.vm86_active)
		eb = ~0;
	अगर (!vmx_need_pf_पूर्णांकercept(vcpu))
		eb &= ~(1u << PF_VECTOR);

	/* When we are running a nested L2 guest and L1 specअगरied क्रम it a
	 * certain exception biपंचांगap, we must trap the same exceptions and pass
	 * them to L1. When running L2, we will only handle the exceptions
	 * specअगरied above अगर L1 did not want them.
	 */
	अगर (is_guest_mode(vcpu))
		eb |= get_vmcs12(vcpu)->exception_biपंचांगap;
        अन्यथा अणु
		/*
		 * If EPT is enabled, #PF is only trapped अगर MAXPHYADDR is mismatched
		 * between guest and host.  In that हाल we only care about present
		 * faults.  For vmcs02, however, PFEC_MASK and PFEC_MATCH are set in
		 * prepare_vmcs02_rare.
		 */
		bool selective_pf_trap = enable_ept && (eb & (1u << PF_VECTOR));
		पूर्णांक mask = selective_pf_trap ? PFERR_PRESENT_MASK : 0;
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MASK, mask);
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MATCH, mask);
	पूर्ण

	vmcs_ग_लिखो32(EXCEPTION_BITMAP, eb);
पूर्ण

/*
 * Check अगर MSR is पूर्णांकercepted क्रम currently loaded MSR biपंचांगap.
 */
अटल bool msr_ग_लिखो_पूर्णांकercepted(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	अचिन्हित दीर्घ *msr_biपंचांगap;
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (!cpu_has_vmx_msr_biपंचांगap())
		वापस true;

	msr_biपंचांगap = to_vmx(vcpu)->loaded_vmcs->msr_biपंचांगap;

	अगर (msr <= 0x1fff) अणु
		वापस !!test_bit(msr, msr_biपंचांगap + 0x800 / f);
	पूर्ण अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) अणु
		msr &= 0x1fff;
		वापस !!test_bit(msr, msr_biपंचांगap + 0xc00 / f);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम clear_atomic_चयन_msr_special(काष्ठा vcpu_vmx *vmx,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ निकास)
अणु
	vm_entry_controls_clearbit(vmx, entry);
	vm_निकास_controls_clearbit(vmx, निकास);
पूर्ण

पूर्णांक vmx_find_loadstore_msr_slot(काष्ठा vmx_msrs *m, u32 msr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < m->nr; ++i) अणु
		अगर (m->val[i].index == msr)
			वापस i;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल व्योम clear_atomic_चयन_msr(काष्ठा vcpu_vmx *vmx, अचिन्हित msr)
अणु
	पूर्णांक i;
	काष्ठा msr_स्वतःload *m = &vmx->msr_स्वतःload;

	चयन (msr) अणु
	हाल MSR_EFER:
		अगर (cpu_has_load_ia32_efer()) अणु
			clear_atomic_चयन_msr_special(vmx,
					VM_ENTRY_LOAD_IA32_EFER,
					VM_EXIT_LOAD_IA32_EFER);
			वापस;
		पूर्ण
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
		अगर (cpu_has_load_perf_global_ctrl()) अणु
			clear_atomic_चयन_msr_special(vmx,
					VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL,
					VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL);
			वापस;
		पूर्ण
		अवरोध;
	पूर्ण
	i = vmx_find_loadstore_msr_slot(&m->guest, msr);
	अगर (i < 0)
		जाओ skip_guest;
	--m->guest.nr;
	m->guest.val[i] = m->guest.val[m->guest.nr];
	vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, m->guest.nr);

skip_guest:
	i = vmx_find_loadstore_msr_slot(&m->host, msr);
	अगर (i < 0)
		वापस;

	--m->host.nr;
	m->host.val[i] = m->host.val[m->host.nr];
	vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, m->host.nr);
पूर्ण

अटल व्योम add_atomic_चयन_msr_special(काष्ठा vcpu_vmx *vmx,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ निकास,
		अचिन्हित दीर्घ guest_val_vmcs, अचिन्हित दीर्घ host_val_vmcs,
		u64 guest_val, u64 host_val)
अणु
	vmcs_ग_लिखो64(guest_val_vmcs, guest_val);
	अगर (host_val_vmcs != HOST_IA32_EFER)
		vmcs_ग_लिखो64(host_val_vmcs, host_val);
	vm_entry_controls_setbit(vmx, entry);
	vm_निकास_controls_setbit(vmx, निकास);
पूर्ण

अटल व्योम add_atomic_चयन_msr(काष्ठा vcpu_vmx *vmx, अचिन्हित msr,
				  u64 guest_val, u64 host_val, bool entry_only)
अणु
	पूर्णांक i, j = 0;
	काष्ठा msr_स्वतःload *m = &vmx->msr_स्वतःload;

	चयन (msr) अणु
	हाल MSR_EFER:
		अगर (cpu_has_load_ia32_efer()) अणु
			add_atomic_चयन_msr_special(vmx,
					VM_ENTRY_LOAD_IA32_EFER,
					VM_EXIT_LOAD_IA32_EFER,
					GUEST_IA32_EFER,
					HOST_IA32_EFER,
					guest_val, host_val);
			वापस;
		पूर्ण
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
		अगर (cpu_has_load_perf_global_ctrl()) अणु
			add_atomic_चयन_msr_special(vmx,
					VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL,
					VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL,
					GUEST_IA32_PERF_GLOBAL_CTRL,
					HOST_IA32_PERF_GLOBAL_CTRL,
					guest_val, host_val);
			वापस;
		पूर्ण
		अवरोध;
	हाल MSR_IA32_PEBS_ENABLE:
		/* PEBS needs a quiescent period after being disabled (to ग_लिखो
		 * a record).  Disabling PEBS through VMX MSR swapping करोesn't
		 * provide that period, so a CPU could ग_लिखो host's record पूर्णांकo
		 * guest's memory.
		 */
		wrmsrl(MSR_IA32_PEBS_ENABLE, 0);
	पूर्ण

	i = vmx_find_loadstore_msr_slot(&m->guest, msr);
	अगर (!entry_only)
		j = vmx_find_loadstore_msr_slot(&m->host, msr);

	अगर ((i < 0 && m->guest.nr == MAX_NR_LOADSTORE_MSRS) ||
	    (j < 0 &&  m->host.nr == MAX_NR_LOADSTORE_MSRS)) अणु
		prपूर्णांकk_once(KERN_WARNING "Not enough msr switch entries. "
				"Can't add msr %x\n", msr);
		वापस;
	पूर्ण
	अगर (i < 0) अणु
		i = m->guest.nr++;
		vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, m->guest.nr);
	पूर्ण
	m->guest.val[i].index = msr;
	m->guest.val[i].value = guest_val;

	अगर (entry_only)
		वापस;

	अगर (j < 0) अणु
		j = m->host.nr++;
		vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, m->host.nr);
	पूर्ण
	m->host.val[j].index = msr;
	m->host.val[j].value = host_val;
पूर्ण

अटल bool update_transition_efer(काष्ठा vcpu_vmx *vmx)
अणु
	u64 guest_efer = vmx->vcpu.arch.efer;
	u64 ignore_bits = 0;
	पूर्णांक i;

	/* Shaकरोw paging assumes NX to be available.  */
	अगर (!enable_ept)
		guest_efer |= EFER_NX;

	/*
	 * LMA and LME handled by hardware; SCE meaningless outside दीर्घ mode.
	 */
	ignore_bits |= EFER_SCE;
#अगर_घोषित CONFIG_X86_64
	ignore_bits |= EFER_LMA | EFER_LME;
	/* SCE is meaningful only in दीर्घ mode on Intel */
	अगर (guest_efer & EFER_LMA)
		ignore_bits &= ~(u64)EFER_SCE;
#पूर्ण_अगर

	/*
	 * On EPT, we can't emulate NX, so we must चयन EFER atomically.
	 * On CPUs that support "load IA32_EFER", always चयन EFER
	 * atomically, since it's faster than चयनing it manually.
	 */
	अगर (cpu_has_load_ia32_efer() ||
	    (enable_ept && ((vmx->vcpu.arch.efer ^ host_efer) & EFER_NX))) अणु
		अगर (!(guest_efer & EFER_LMA))
			guest_efer &= ~EFER_LME;
		अगर (guest_efer != host_efer)
			add_atomic_चयन_msr(vmx, MSR_EFER,
					      guest_efer, host_efer, false);
		अन्यथा
			clear_atomic_चयन_msr(vmx, MSR_EFER);
		वापस false;
	पूर्ण

	i = kvm_find_user_वापस_msr(MSR_EFER);
	अगर (i < 0)
		वापस false;

	clear_atomic_चयन_msr(vmx, MSR_EFER);

	guest_efer &= ~ignore_bits;
	guest_efer |= host_efer & ignore_bits;

	vmx->guest_uret_msrs[i].data = guest_efer;
	vmx->guest_uret_msrs[i].mask = ~ignore_bits;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_X86_32
/*
 * On 32-bit kernels, VM निकासs still load the FS and GS bases from the
 * VMCS rather than the segment table.  KVM uses this helper to figure
 * out the current bases to poke them पूर्णांकo the VMCS beक्रमe entry.
 */
अटल अचिन्हित दीर्घ segment_base(u16 selector)
अणु
	काष्ठा desc_काष्ठा *table;
	अचिन्हित दीर्घ v;

	अगर (!(selector & ~SEGMENT_RPL_MASK))
		वापस 0;

	table = get_current_gdt_ro();

	अगर ((selector & SEGMENT_TI_MASK) == SEGMENT_LDT) अणु
		u16 ldt_selector = kvm_पढ़ो_ldt();

		अगर (!(ldt_selector & ~SEGMENT_RPL_MASK))
			वापस 0;

		table = (काष्ठा desc_काष्ठा *)segment_base(ldt_selector);
	पूर्ण
	v = get_desc_base(&table[selector >> 3]);
	वापस v;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool pt_can_ग_लिखो_msr(काष्ठा vcpu_vmx *vmx)
अणु
	वापस vmx_pt_mode_is_host_guest() &&
	       !(vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN);
पूर्ण

अटल अंतरभूत bool pt_output_base_valid(काष्ठा kvm_vcpu *vcpu, u64 base)
अणु
	/* The base must be 128-byte aligned and a legal physical address. */
	वापस kvm_vcpu_is_legal_aligned_gpa(vcpu, base, 128);
पूर्ण

अटल अंतरभूत व्योम pt_load_msr(काष्ठा pt_ctx *ctx, u32 addr_range)
अणु
	u32 i;

	wrmsrl(MSR_IA32_RTIT_STATUS, ctx->status);
	wrmsrl(MSR_IA32_RTIT_OUTPUT_BASE, ctx->output_base);
	wrmsrl(MSR_IA32_RTIT_OUTPUT_MASK, ctx->output_mask);
	wrmsrl(MSR_IA32_RTIT_CR3_MATCH, ctx->cr3_match);
	क्रम (i = 0; i < addr_range; i++) अणु
		wrmsrl(MSR_IA32_RTIT_ADDR0_A + i * 2, ctx->addr_a[i]);
		wrmsrl(MSR_IA32_RTIT_ADDR0_B + i * 2, ctx->addr_b[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pt_save_msr(काष्ठा pt_ctx *ctx, u32 addr_range)
अणु
	u32 i;

	rdmsrl(MSR_IA32_RTIT_STATUS, ctx->status);
	rdmsrl(MSR_IA32_RTIT_OUTPUT_BASE, ctx->output_base);
	rdmsrl(MSR_IA32_RTIT_OUTPUT_MASK, ctx->output_mask);
	rdmsrl(MSR_IA32_RTIT_CR3_MATCH, ctx->cr3_match);
	क्रम (i = 0; i < addr_range; i++) अणु
		rdmsrl(MSR_IA32_RTIT_ADDR0_A + i * 2, ctx->addr_a[i]);
		rdmsrl(MSR_IA32_RTIT_ADDR0_B + i * 2, ctx->addr_b[i]);
	पूर्ण
पूर्ण

अटल व्योम pt_guest_enter(काष्ठा vcpu_vmx *vmx)
अणु
	अगर (vmx_pt_mode_is_प्रणाली())
		वापस;

	/*
	 * GUEST_IA32_RTIT_CTL is alपढ़ोy set in the VMCS.
	 * Save host state beक्रमe VM entry.
	 */
	rdmsrl(MSR_IA32_RTIT_CTL, vmx->pt_desc.host.ctl);
	अगर (vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN) अणु
		wrmsrl(MSR_IA32_RTIT_CTL, 0);
		pt_save_msr(&vmx->pt_desc.host, vmx->pt_desc.addr_range);
		pt_load_msr(&vmx->pt_desc.guest, vmx->pt_desc.addr_range);
	पूर्ण
पूर्ण

अटल व्योम pt_guest_निकास(काष्ठा vcpu_vmx *vmx)
अणु
	अगर (vmx_pt_mode_is_प्रणाली())
		वापस;

	अगर (vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN) अणु
		pt_save_msr(&vmx->pt_desc.guest, vmx->pt_desc.addr_range);
		pt_load_msr(&vmx->pt_desc.host, vmx->pt_desc.addr_range);
	पूर्ण

	/* Reload host state (IA32_RTIT_CTL will be cleared on VM निकास). */
	wrmsrl(MSR_IA32_RTIT_CTL, vmx->pt_desc.host.ctl);
पूर्ण

व्योम vmx_set_host_fs_gs(काष्ठा vmcs_host_state *host, u16 fs_sel, u16 gs_sel,
			अचिन्हित दीर्घ fs_base, अचिन्हित दीर्घ gs_base)
अणु
	अगर (unlikely(fs_sel != host->fs_sel)) अणु
		अगर (!(fs_sel & 7))
			vmcs_ग_लिखो16(HOST_FS_SELECTOR, fs_sel);
		अन्यथा
			vmcs_ग_लिखो16(HOST_FS_SELECTOR, 0);
		host->fs_sel = fs_sel;
	पूर्ण
	अगर (unlikely(gs_sel != host->gs_sel)) अणु
		अगर (!(gs_sel & 7))
			vmcs_ग_लिखो16(HOST_GS_SELECTOR, gs_sel);
		अन्यथा
			vmcs_ग_लिखो16(HOST_GS_SELECTOR, 0);
		host->gs_sel = gs_sel;
	पूर्ण
	अगर (unlikely(fs_base != host->fs_base)) अणु
		vmcs_ग_लिखोl(HOST_FS_BASE, fs_base);
		host->fs_base = fs_base;
	पूर्ण
	अगर (unlikely(gs_base != host->gs_base)) अणु
		vmcs_ग_लिखोl(HOST_GS_BASE, gs_base);
		host->gs_base = gs_base;
	पूर्ण
पूर्ण

व्योम vmx_prepare_चयन_to_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs_host_state *host_state;
#अगर_घोषित CONFIG_X86_64
	पूर्णांक cpu = raw_smp_processor_id();
#पूर्ण_अगर
	अचिन्हित दीर्घ fs_base, gs_base;
	u16 fs_sel, gs_sel;
	पूर्णांक i;

	vmx->req_immediate_निकास = false;

	/*
	 * Note that guest MSRs to be saved/restored can also be changed
	 * when guest state is loaded. This happens when guest transitions
	 * to/from दीर्घ-mode by setting MSR_EFER.LMA.
	 */
	अगर (!vmx->guest_uret_msrs_loaded) अणु
		vmx->guest_uret_msrs_loaded = true;
		क्रम (i = 0; i < kvm_nr_uret_msrs; ++i) अणु
			अगर (!vmx->guest_uret_msrs[i].load_पूर्णांकo_hardware)
				जारी;

			kvm_set_user_वापस_msr(i,
						vmx->guest_uret_msrs[i].data,
						vmx->guest_uret_msrs[i].mask);
		पूर्ण
	पूर्ण

    	अगर (vmx->nested.need_vmcs12_to_shaकरोw_sync)
		nested_sync_vmcs12_to_shaकरोw(vcpu);

	अगर (vmx->guest_state_loaded)
		वापस;

	host_state = &vmx->loaded_vmcs->host_state;

	/*
	 * Set host fs and gs selectors.  Unक्रमtunately, 22.2.3 करोes not
	 * allow segment selectors with cpl > 0 or ti == 1.
	 */
	host_state->ldt_sel = kvm_पढ़ो_ldt();

#अगर_घोषित CONFIG_X86_64
	savesegment(ds, host_state->ds_sel);
	savesegment(es, host_state->es_sel);

	gs_base = cpu_kernelmode_gs_base(cpu);
	अगर (likely(is_64bit_mm(current->mm))) अणु
		current_save_fsgs();
		fs_sel = current->thपढ़ो.fsindex;
		gs_sel = current->thपढ़ो.gsindex;
		fs_base = current->thपढ़ो.fsbase;
		vmx->msr_host_kernel_gs_base = current->thपढ़ो.gsbase;
	पूर्ण अन्यथा अणु
		savesegment(fs, fs_sel);
		savesegment(gs, gs_sel);
		fs_base = पढ़ो_msr(MSR_FS_BASE);
		vmx->msr_host_kernel_gs_base = पढ़ो_msr(MSR_KERNEL_GS_BASE);
	पूर्ण

	wrmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
#अन्यथा
	savesegment(fs, fs_sel);
	savesegment(gs, gs_sel);
	fs_base = segment_base(fs_sel);
	gs_base = segment_base(gs_sel);
#पूर्ण_अगर

	vmx_set_host_fs_gs(host_state, fs_sel, gs_sel, fs_base, gs_base);
	vmx->guest_state_loaded = true;
पूर्ण

अटल व्योम vmx_prepare_चयन_to_host(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा vmcs_host_state *host_state;

	अगर (!vmx->guest_state_loaded)
		वापस;

	host_state = &vmx->loaded_vmcs->host_state;

	++vmx->vcpu.स्थिति.सost_state_reload;

#अगर_घोषित CONFIG_X86_64
	rdmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
#पूर्ण_अगर
	अगर (host_state->ldt_sel || (host_state->gs_sel & 7)) अणु
		kvm_load_ldt(host_state->ldt_sel);
#अगर_घोषित CONFIG_X86_64
		load_gs_index(host_state->gs_sel);
#अन्यथा
		loadsegment(gs, host_state->gs_sel);
#पूर्ण_अगर
	पूर्ण
	अगर (host_state->fs_sel & 7)
		loadsegment(fs, host_state->fs_sel);
#अगर_घोषित CONFIG_X86_64
	अगर (unlikely(host_state->ds_sel | host_state->es_sel)) अणु
		loadsegment(ds, host_state->ds_sel);
		loadsegment(es, host_state->es_sel);
	पूर्ण
#पूर्ण_अगर
	invalidate_tss_limit();
#अगर_घोषित CONFIG_X86_64
	wrmsrl(MSR_KERNEL_GS_BASE, vmx->msr_host_kernel_gs_base);
#पूर्ण_अगर
	load_fixmap_gdt(raw_smp_processor_id());
	vmx->guest_state_loaded = false;
	vmx->guest_uret_msrs_loaded = false;
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल u64 vmx_पढ़ो_guest_kernel_gs_base(काष्ठा vcpu_vmx *vmx)
अणु
	preempt_disable();
	अगर (vmx->guest_state_loaded)
		rdmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
	preempt_enable();
	वापस vmx->msr_guest_kernel_gs_base;
पूर्ण

अटल व्योम vmx_ग_लिखो_guest_kernel_gs_base(काष्ठा vcpu_vmx *vmx, u64 data)
अणु
	preempt_disable();
	अगर (vmx->guest_state_loaded)
		wrmsrl(MSR_KERNEL_GS_BASE, data);
	preempt_enable();
	vmx->msr_guest_kernel_gs_base = data;
पूर्ण
#पूर्ण_अगर

व्योम vmx_vcpu_load_vmcs(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu,
			काष्ठा loaded_vmcs *buddy)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	bool alपढ़ोy_loaded = vmx->loaded_vmcs->cpu == cpu;
	काष्ठा vmcs *prev;

	अगर (!alपढ़ोy_loaded) अणु
		loaded_vmcs_clear(vmx->loaded_vmcs);
		local_irq_disable();

		/*
		 * Ensure loaded_vmcs->cpu is पढ़ो beक्रमe adding loaded_vmcs to
		 * this cpu's percpu list, otherwise it may not yet be deleted
		 * from its previous cpu's percpu list.  Pairs with the
		 * smb_wmb() in __loaded_vmcs_clear().
		 */
		smp_rmb();

		list_add(&vmx->loaded_vmcs->loaded_vmcss_on_cpu_link,
			 &per_cpu(loaded_vmcss_on_cpu, cpu));
		local_irq_enable();
	पूर्ण

	prev = per_cpu(current_vmcs, cpu);
	अगर (prev != vmx->loaded_vmcs->vmcs) अणु
		per_cpu(current_vmcs, cpu) = vmx->loaded_vmcs->vmcs;
		vmcs_load(vmx->loaded_vmcs->vmcs);

		/*
		 * No indirect branch prediction barrier needed when चयनing
		 * the active VMCS within a guest, e.g. on nested VM-Enter.
		 * The L1 VMM can protect itself with retpolines, IBPB or IBRS.
		 */
		अगर (!buddy || WARN_ON_ONCE(buddy->vmcs != prev))
			indirect_branch_prediction_barrier();
	पूर्ण

	अगर (!alपढ़ोy_loaded) अणु
		व्योम *gdt = get_current_gdt_ro();
		अचिन्हित दीर्घ sysenter_esp;

		/*
		 * Flush all EPTP/VPID contexts, the new pCPU may have stale
		 * TLB entries from its previous association with the vCPU.
		 */
		kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);

		/*
		 * Linux uses per-cpu TSS and GDT, so set these when चयनing
		 * processors.  See 22.2.4.
		 */
		vmcs_ग_लिखोl(HOST_TR_BASE,
			    (अचिन्हित दीर्घ)&get_cpu_entry_area(cpu)->tss.x86_tss);
		vmcs_ग_लिखोl(HOST_GDTR_BASE, (अचिन्हित दीर्घ)gdt);   /* 22.2.4 */

		rdmsrl(MSR_IA32_SYSENTER_ESP, sysenter_esp);
		vmcs_ग_लिखोl(HOST_IA32_SYSENTER_ESP, sysenter_esp); /* 22.2.3 */

		vmx->loaded_vmcs->cpu = cpu;
	पूर्ण

	/* Setup TSC multiplier */
	अगर (kvm_has_tsc_control &&
	    vmx->current_tsc_ratio != vcpu->arch.tsc_scaling_ratio)
		decache_tsc_multiplier(vmx);
पूर्ण

/*
 * Switches to specअगरied vcpu, until a matching vcpu_put(), but assumes
 * vcpu mutex is alपढ़ोy taken.
 */
अटल व्योम vmx_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	vmx_vcpu_load_vmcs(vcpu, cpu, शून्य);

	vmx_vcpu_pi_load(vcpu, cpu);

	vmx->host_debugctlmsr = get_debugctlmsr();
पूर्ण

अटल व्योम vmx_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	vmx_vcpu_pi_put(vcpu);

	vmx_prepare_चयन_to_host(to_vmx(vcpu));
पूर्ण

अटल bool emulation_required(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस emulate_invalid_guest_state && !vmx_guest_state_valid(vcpu);
पूर्ण

अचिन्हित दीर्घ vmx_get_rflags(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ rflags, save_rflags;

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_RFLAGS)) अणु
		kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_RFLAGS);
		rflags = vmcs_पढ़ोl(GUEST_RFLAGS);
		अगर (vmx->rmode.vm86_active) अणु
			rflags &= RMODE_GUEST_OWNED_EFLAGS_BITS;
			save_rflags = vmx->rmode.save_rflags;
			rflags |= save_rflags & ~RMODE_GUEST_OWNED_EFLAGS_BITS;
		पूर्ण
		vmx->rflags = rflags;
	पूर्ण
	वापस vmx->rflags;
पूर्ण

व्योम vmx_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ old_rflags;

	अगर (is_unrestricted_guest(vcpu)) अणु
		kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_RFLAGS);
		vmx->rflags = rflags;
		vmcs_ग_लिखोl(GUEST_RFLAGS, rflags);
		वापस;
	पूर्ण

	old_rflags = vmx_get_rflags(vcpu);
	vmx->rflags = rflags;
	अगर (vmx->rmode.vm86_active) अणु
		vmx->rmode.save_rflags = rflags;
		rflags |= X86_EFLAGS_IOPL | X86_EFLAGS_VM;
	पूर्ण
	vmcs_ग_लिखोl(GUEST_RFLAGS, rflags);

	अगर ((old_rflags ^ vmx->rflags) & X86_EFLAGS_VM)
		vmx->emulation_required = emulation_required(vcpu);
पूर्ण

u32 vmx_get_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 पूर्णांकerruptibility = vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO);
	पूर्णांक ret = 0;

	अगर (पूर्णांकerruptibility & GUEST_INTR_STATE_STI)
		ret |= KVM_X86_SHADOW_INT_STI;
	अगर (पूर्णांकerruptibility & GUEST_INTR_STATE_MOV_SS)
		ret |= KVM_X86_SHADOW_INT_MOV_SS;

	वापस ret;
पूर्ण

व्योम vmx_set_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu, पूर्णांक mask)
अणु
	u32 पूर्णांकerruptibility_old = vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO);
	u32 पूर्णांकerruptibility = पूर्णांकerruptibility_old;

	पूर्णांकerruptibility &= ~(GUEST_INTR_STATE_STI | GUEST_INTR_STATE_MOV_SS);

	अगर (mask & KVM_X86_SHADOW_INT_MOV_SS)
		पूर्णांकerruptibility |= GUEST_INTR_STATE_MOV_SS;
	अन्यथा अगर (mask & KVM_X86_SHADOW_INT_STI)
		पूर्णांकerruptibility |= GUEST_INTR_STATE_STI;

	अगर ((पूर्णांकerruptibility != पूर्णांकerruptibility_old))
		vmcs_ग_लिखो32(GUEST_INTERRUPTIBILITY_INFO, पूर्णांकerruptibility);
पूर्ण

अटल पूर्णांक vmx_rtit_ctl_check(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ value;

	/*
	 * Any MSR ग_लिखो that attempts to change bits marked reserved will
	 * हाल a #GP fault.
	 */
	अगर (data & vmx->pt_desc.ctl_biपंचांगask)
		वापस 1;

	/*
	 * Any attempt to modअगरy IA32_RTIT_CTL जबतक TraceEn is set will
	 * result in a #GP unless the same ग_लिखो also clears TraceEn.
	 */
	अगर ((vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN) &&
		((vmx->pt_desc.guest.ctl ^ data) & ~RTIT_CTL_TRACEEN))
		वापस 1;

	/*
	 * WRMSR to IA32_RTIT_CTL that sets TraceEn but clears this bit
	 * and FabricEn would cause #GP, अगर
	 * CPUID.(EAX=14H, ECX=0):ECX.SNGLRGNOUT[bit 2] = 0
	 */
	अगर ((data & RTIT_CTL_TRACEEN) && !(data & RTIT_CTL_TOPA) &&
		!(data & RTIT_CTL_FABRIC_EN) &&
		!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_single_range_output))
		वापस 1;

	/*
	 * MTCFreq, CycThresh and PSBFreq encodings check, any MSR ग_लिखो that
	 * utilize encodings marked reserved will cause a #GP fault.
	 */
	value = पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_mtc_periods);
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_mtc) &&
			!test_bit((data & RTIT_CTL_MTC_RANGE) >>
			RTIT_CTL_MTC_RANGE_OFFSET, &value))
		वापस 1;
	value = पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
						PT_CAP_cycle_thresholds);
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_psb_cyc) &&
			!test_bit((data & RTIT_CTL_CYC_THRESH) >>
			RTIT_CTL_CYC_THRESH_OFFSET, &value))
		वापस 1;
	value = पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_psb_periods);
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_psb_cyc) &&
			!test_bit((data & RTIT_CTL_PSB_FREQ) >>
			RTIT_CTL_PSB_FREQ_OFFSET, &value))
		वापस 1;

	/*
	 * If ADDRx_CFG is reserved or the encodings is >2 will
	 * cause a #GP fault.
	 */
	value = (data & RTIT_CTL_ADDR0) >> RTIT_CTL_ADDR0_OFFSET;
	अगर ((value && (vmx->pt_desc.addr_range < 1)) || (value > 2))
		वापस 1;
	value = (data & RTIT_CTL_ADDR1) >> RTIT_CTL_ADDR1_OFFSET;
	अगर ((value && (vmx->pt_desc.addr_range < 2)) || (value > 2))
		वापस 1;
	value = (data & RTIT_CTL_ADDR2) >> RTIT_CTL_ADDR2_OFFSET;
	अगर ((value && (vmx->pt_desc.addr_range < 3)) || (value > 2))
		वापस 1;
	value = (data & RTIT_CTL_ADDR3) >> RTIT_CTL_ADDR3_OFFSET;
	अगर ((value && (vmx->pt_desc.addr_range < 4)) || (value > 2))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool vmx_can_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, व्योम *insn, पूर्णांक insn_len)
अणु
	/*
	 * Emulation of inकाष्ठाions in SGX enclaves is impossible as RIP करोes
	 * not poपूर्णांक  tthe failing inकाष्ठाion, and even अगर it did, the code
	 * stream is inaccessible.  Inject #UD instead of निकासing to userspace
	 * so that guest userspace can't DoS the guest simply by triggering
	 * emulation (enclaves are CPL3 only).
	 */
	अगर (to_vmx(vcpu)->निकास_reason.enclave_mode) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक skip_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ vmx_निकास_reason निकास_reason = to_vmx(vcpu)->निकास_reason;
	अचिन्हित दीर्घ rip, orig_rip;
	u32 instr_len;

	/*
	 * Using VMCS.VM_EXIT_INSTRUCTION_LEN on EPT misconfig depends on
	 * undefined behavior: Intel's SDM doesn't mandate the VMCS field be
	 * set when EPT misconfig occurs.  In practice, real hardware updates
	 * VM_EXIT_INSTRUCTION_LEN on EPT misconfig, but other hypervisors
	 * (namely Hyper-V) करोn't set it due to it being undefined behavior,
	 * i.e. we end up advancing IP with some अक्रमom value.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_HYPERVISOR) ||
	    निकास_reason.basic != EXIT_REASON_EPT_MISCONFIG) अणु
		instr_len = vmcs_पढ़ो32(VM_EXIT_INSTRUCTION_LEN);

		/*
		 * Emulating an enclave's instructions isn't supported as KVM
		 * cannot access the enclave's memory or its true RIP, e.g. the
		 * vmcs.GUEST_RIP poपूर्णांकs at the निकास poपूर्णांक of the enclave, not
		 * the RIP that actually triggered the VM-Exit.  But, because
		 * most inकाष्ठाions that cause VM-Exit will #UD in an enclave,
		 * most inकाष्ठाion-based VM-Exits simply करो not occur.
		 *
		 * There are a few exceptions, notably the debug inकाष्ठाions
		 * INT1ICEBRK and INT3, as they are allowed in debug enclaves
		 * and generate #DB/#BP as expected, which KVM might पूर्णांकercept.
		 * But again, the CPU करोes the dirty work and saves an instr
		 * length of zero so VMMs करोn't shoot themselves in the foot.
		 * WARN अगर KVM tries to skip a non-zero length inकाष्ठाion on
		 * a VM-Exit from an enclave.
		 */
		अगर (!instr_len)
			जाओ rip_updated;

		WARN(निकास_reason.enclave_mode,
		     "KVM: skipping instruction after SGX enclave VM-Exit");

		orig_rip = kvm_rip_पढ़ो(vcpu);
		rip = orig_rip + instr_len;
#अगर_घोषित CONFIG_X86_64
		/*
		 * We need to mask out the high 32 bits of RIP अगर not in 64-bit
		 * mode, but just finding out that we are in 64-bit mode is
		 * quite expensive.  Only करो it अगर there was a carry.
		 */
		अगर (unlikely(((rip ^ orig_rip) >> 31) == 3) && !is_64_bit_mode(vcpu))
			rip = (u32)rip;
#पूर्ण_अगर
		kvm_rip_ग_लिखो(vcpu, rip);
	पूर्ण अन्यथा अणु
		अगर (!kvm_emulate_inकाष्ठाion(vcpu, EMULTYPE_SKIP))
			वापस 0;
	पूर्ण

rip_updated:
	/* skipping an emulated inकाष्ठाion also counts */
	vmx_set_पूर्णांकerrupt_shaकरोw(vcpu, 0);

	वापस 1;
पूर्ण

/*
 * Recognizes a pending MTF VM-निकास and records the nested state क्रम later
 * delivery.
 */
अटल व्योम vmx_update_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!is_guest_mode(vcpu))
		वापस;

	/*
	 * Per the SDM, MTF takes priority over debug-trap exceptions besides
	 * T-bit traps. As inकाष्ठाion emulation is completed (i.e. at the
	 * inकाष्ठाion boundary), any #DB exception pending delivery must be a
	 * debug-trap. Record the pending MTF state to be delivered in
	 * vmx_check_nested_events().
	 */
	अगर (nested_cpu_has_mtf(vmcs12) &&
	    (!vcpu->arch.exception.pending ||
	     vcpu->arch.exception.nr == DB_VECTOR))
		vmx->nested.mtf_pending = true;
	अन्यथा
		vmx->nested.mtf_pending = false;
पूर्ण

अटल पूर्णांक vmx_skip_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	vmx_update_emulated_inकाष्ठाion(vcpu);
	वापस skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल व्योम vmx_clear_hlt(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Ensure that we clear the HLT state in the VMCS.  We करोn't need to
	 * explicitly skip the inकाष्ठाion because अगर the HLT state is set,
	 * then the inकाष्ठाion is alपढ़ोy executing and RIP has alपढ़ोy been
	 * advanced.
	 */
	अगर (kvm_hlt_in_guest(vcpu->kvm) &&
			vmcs_पढ़ो32(GUEST_ACTIVITY_STATE) == GUEST_ACTIVITY_HLT)
		vmcs_ग_लिखो32(GUEST_ACTIVITY_STATE, GUEST_ACTIVITY_ACTIVE);
पूर्ण

अटल व्योम vmx_queue_exception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित nr = vcpu->arch.exception.nr;
	bool has_error_code = vcpu->arch.exception.has_error_code;
	u32 error_code = vcpu->arch.exception.error_code;
	u32 पूर्णांकr_info = nr | INTR_INFO_VALID_MASK;

	kvm_deliver_exception_payload(vcpu);

	अगर (has_error_code) अणु
		vmcs_ग_लिखो32(VM_ENTRY_EXCEPTION_ERROR_CODE, error_code);
		पूर्णांकr_info |= INTR_INFO_DELIVER_CODE_MASK;
	पूर्ण

	अगर (vmx->rmode.vm86_active) अणु
		पूर्णांक inc_eip = 0;
		अगर (kvm_exception_is_soft(nr))
			inc_eip = vcpu->arch.event_निकास_inst_len;
		kvm_inject_realmode_पूर्णांकerrupt(vcpu, nr, inc_eip);
		वापस;
	पूर्ण

	WARN_ON_ONCE(vmx->emulation_required);

	अगर (kvm_exception_is_soft(nr)) अणु
		vmcs_ग_लिखो32(VM_ENTRY_INSTRUCTION_LEN,
			     vmx->vcpu.arch.event_निकास_inst_len);
		पूर्णांकr_info |= INTR_TYPE_SOFT_EXCEPTION;
	पूर्ण अन्यथा
		पूर्णांकr_info |= INTR_TYPE_HARD_EXCEPTION;

	vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD, पूर्णांकr_info);

	vmx_clear_hlt(vcpu);
पूर्ण

अटल व्योम vmx_setup_uret_msr(काष्ठा vcpu_vmx *vmx, अचिन्हित पूर्णांक msr,
			       bool load_पूर्णांकo_hardware)
अणु
	काष्ठा vmx_uret_msr *uret_msr;

	uret_msr = vmx_find_uret_msr(vmx, msr);
	अगर (!uret_msr)
		वापस;

	uret_msr->load_पूर्णांकo_hardware = load_पूर्णांकo_hardware;
पूर्ण

/*
 * Set up the vmcs to स्वतःmatically save and restore प्रणाली
 * msrs.  Don't touch the 64-bit msrs अगर the guest is in legacy
 * mode, as fiddling with msrs is very expensive.
 */
अटल व्योम setup_msrs(काष्ठा vcpu_vmx *vmx)
अणु
#अगर_घोषित CONFIG_X86_64
	bool load_syscall_msrs;

	/*
	 * The SYSCALL MSRs are only needed on दीर्घ mode guests, and only
	 * when EFER.SCE is set.
	 */
	load_syscall_msrs = is_दीर्घ_mode(&vmx->vcpu) &&
			    (vmx->vcpu.arch.efer & EFER_SCE);

	vmx_setup_uret_msr(vmx, MSR_STAR, load_syscall_msrs);
	vmx_setup_uret_msr(vmx, MSR_LSTAR, load_syscall_msrs);
	vmx_setup_uret_msr(vmx, MSR_SYSCALL_MASK, load_syscall_msrs);
#पूर्ण_अगर
	vmx_setup_uret_msr(vmx, MSR_EFER, update_transition_efer(vmx));

	vmx_setup_uret_msr(vmx, MSR_TSC_AUX,
			   guest_cpuid_has(&vmx->vcpu, X86_FEATURE_RDTSCP) ||
			   guest_cpuid_has(&vmx->vcpu, X86_FEATURE_RDPID));

	/*
	 * hle=0, rपंचांग=0, tsx_ctrl=1 can be found with some combinations of new
	 * kernel and old userspace.  If those guests run on a tsx=off host, करो
	 * allow guests to use TSX_CTRL, but करोn't change the value in hardware
	 * so that TSX reमुख्यs always disabled.
	 */
	vmx_setup_uret_msr(vmx, MSR_IA32_TSX_CTRL, boot_cpu_has(X86_FEATURE_RTM));

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmx_update_msr_biपंचांगap(&vmx->vcpu);

	/*
	 * The set of MSRs to load may have changed, reload MSRs beक्रमe the
	 * next VM-Enter.
	 */
	vmx->guest_uret_msrs_loaded = false;
पूर्ण

अटल u64 vmx_ग_लिखो_l1_tsc_offset(काष्ठा kvm_vcpu *vcpu, u64 offset)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	u64 g_tsc_offset = 0;

	/*
	 * We're here अगर L1 chose not to trap WRMSR to TSC. According
	 * to the spec, this should set L1's TSC; The offset that L1
	 * set क्रम L2 reमुख्यs unchanged, and still needs to be added
	 * to the newly set TSC to get L2's TSC.
	 */
	अगर (is_guest_mode(vcpu) &&
	    (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETTING))
		g_tsc_offset = vmcs12->tsc_offset;

	trace_kvm_ग_लिखो_tsc_offset(vcpu->vcpu_id,
				   vcpu->arch.tsc_offset - g_tsc_offset,
				   offset);
	vmcs_ग_लिखो64(TSC_OFFSET, offset + g_tsc_offset);
	वापस offset + g_tsc_offset;
पूर्ण

/*
 * nested_vmx_allowed() checks whether a guest should be allowed to use VMX
 * inकाष्ठाions and MSRs (i.e., nested VMX). Nested VMX is disabled क्रम
 * all guests अगर the "nested" module option is off, and can also be disabled
 * क्रम a single guest by disabling its VMX cpuid bit.
 */
bool nested_vmx_allowed(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस nested && guest_cpuid_has(vcpu, X86_FEATURE_VMX);
पूर्ण

अटल अंतरभूत bool vmx_feature_control_msr_valid(काष्ठा kvm_vcpu *vcpu,
						 uपूर्णांक64_t val)
अणु
	uपूर्णांक64_t valid_bits = to_vmx(vcpu)->msr_ia32_feature_control_valid_bits;

	वापस !(val & ~valid_bits);
पूर्ण

अटल पूर्णांक vmx_get_msr_feature(काष्ठा kvm_msr_entry *msr)
अणु
	चयन (msr->index) अणु
	हाल MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		अगर (!nested)
			वापस 1;
		वापस vmx_get_vmx_msr(&vmcs_config.nested, msr->index, &msr->data);
	हाल MSR_IA32_PERF_CAPABILITIES:
		msr->data = vmx_get_perf_capabilities();
		वापस 0;
	शेष:
		वापस KVM_MSR_RET_INVALID;
	पूर्ण
पूर्ण

/*
 * Reads an msr value (of 'msr_index') into 'pdata'.
 * Returns 0 on success, non-0 otherwise.
 * Assumes vcpu_load() was alपढ़ोy called.
 */
अटल पूर्णांक vmx_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmx_uret_msr *msr;
	u32 index;

	चयन (msr_info->index) अणु
#अगर_घोषित CONFIG_X86_64
	हाल MSR_FS_BASE:
		msr_info->data = vmcs_पढ़ोl(GUEST_FS_BASE);
		अवरोध;
	हाल MSR_GS_BASE:
		msr_info->data = vmcs_पढ़ोl(GUEST_GS_BASE);
		अवरोध;
	हाल MSR_KERNEL_GS_BASE:
		msr_info->data = vmx_पढ़ो_guest_kernel_gs_base(vmx);
		अवरोध;
#पूर्ण_अगर
	हाल MSR_EFER:
		वापस kvm_get_msr_common(vcpu, msr_info);
	हाल MSR_IA32_TSX_CTRL:
		अगर (!msr_info->host_initiated &&
		    !(vcpu->arch.arch_capabilities & ARCH_CAP_TSX_CTRL_MSR))
			वापस 1;
		जाओ find_uret_msr;
	हाल MSR_IA32_UMWAIT_CONTROL:
		अगर (!msr_info->host_initiated && !vmx_has_रुकोpkg(vmx))
			वापस 1;

		msr_info->data = vmx->msr_ia32_umरुको_control;
		अवरोध;
	हाल MSR_IA32_SPEC_CTRL:
		अगर (!msr_info->host_initiated &&
		    !guest_has_spec_ctrl_msr(vcpu))
			वापस 1;

		msr_info->data = to_vmx(vcpu)->spec_ctrl;
		अवरोध;
	हाल MSR_IA32_SYSENTER_CS:
		msr_info->data = vmcs_पढ़ो32(GUEST_SYSENTER_CS);
		अवरोध;
	हाल MSR_IA32_SYSENTER_EIP:
		msr_info->data = vmcs_पढ़ोl(GUEST_SYSENTER_EIP);
		अवरोध;
	हाल MSR_IA32_SYSENTER_ESP:
		msr_info->data = vmcs_पढ़ोl(GUEST_SYSENTER_ESP);
		अवरोध;
	हाल MSR_IA32_BNDCFGS:
		अगर (!kvm_mpx_supported() ||
		    (!msr_info->host_initiated &&
		     !guest_cpuid_has(vcpu, X86_FEATURE_MPX)))
			वापस 1;
		msr_info->data = vmcs_पढ़ो64(GUEST_BNDCFGS);
		अवरोध;
	हाल MSR_IA32_MCG_EXT_CTL:
		अगर (!msr_info->host_initiated &&
		    !(vmx->msr_ia32_feature_control &
		      FEAT_CTL_LMCE_ENABLED))
			वापस 1;
		msr_info->data = vcpu->arch.mcg_ext_ctl;
		अवरोध;
	हाल MSR_IA32_FEAT_CTL:
		msr_info->data = vmx->msr_ia32_feature_control;
		अवरोध;
	हाल MSR_IA32_SGXLEPUBKEYHASH0 ... MSR_IA32_SGXLEPUBKEYHASH3:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_SGX_LC))
			वापस 1;
		msr_info->data = to_vmx(vcpu)->msr_ia32_sgxlepubkeyhash
			[msr_info->index - MSR_IA32_SGXLEPUBKEYHASH0];
		अवरोध;
	हाल MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		अगर (!nested_vmx_allowed(vcpu))
			वापस 1;
		अगर (vmx_get_vmx_msr(&vmx->nested.msrs, msr_info->index,
				    &msr_info->data))
			वापस 1;
		/*
		 * Enlightened VMCS v1 करोesn't have certain fields, but buggy
		 * Hyper-V versions are still trying to use corresponding
		 * features when they are exposed. Filter out the essential
		 * minimum.
		 */
		अगर (!msr_info->host_initiated &&
		    vmx->nested.enlightened_vmcs_enabled)
			nested_evmcs_filter_control_msr(msr_info->index,
							&msr_info->data);
		अवरोध;
	हाल MSR_IA32_RTIT_CTL:
		अगर (!vmx_pt_mode_is_host_guest())
			वापस 1;
		msr_info->data = vmx->pt_desc.guest.ctl;
		अवरोध;
	हाल MSR_IA32_RTIT_STATUS:
		अगर (!vmx_pt_mode_is_host_guest())
			वापस 1;
		msr_info->data = vmx->pt_desc.guest.status;
		अवरोध;
	हाल MSR_IA32_RTIT_CR3_MATCH:
		अगर (!vmx_pt_mode_is_host_guest() ||
			!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
						PT_CAP_cr3_filtering))
			वापस 1;
		msr_info->data = vmx->pt_desc.guest.cr3_match;
		अवरोध;
	हाल MSR_IA32_RTIT_OUTPUT_BASE:
		अगर (!vmx_pt_mode_is_host_guest() ||
			(!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_topa_output) &&
			 !पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_single_range_output)))
			वापस 1;
		msr_info->data = vmx->pt_desc.guest.output_base;
		अवरोध;
	हाल MSR_IA32_RTIT_OUTPUT_MASK:
		अगर (!vmx_pt_mode_is_host_guest() ||
			(!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_topa_output) &&
			 !पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_single_range_output)))
			वापस 1;
		msr_info->data = vmx->pt_desc.guest.output_mask;
		अवरोध;
	हाल MSR_IA32_RTIT_ADDR0_A ... MSR_IA32_RTIT_ADDR3_B:
		index = msr_info->index - MSR_IA32_RTIT_ADDR0_A;
		अगर (!vmx_pt_mode_is_host_guest() ||
			(index >= 2 * पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					PT_CAP_num_address_ranges)))
			वापस 1;
		अगर (index % 2)
			msr_info->data = vmx->pt_desc.guest.addr_b[index / 2];
		अन्यथा
			msr_info->data = vmx->pt_desc.guest.addr_a[index / 2];
		अवरोध;
	हाल MSR_IA32_DEBUGCTLMSR:
		msr_info->data = vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL);
		अवरोध;
	शेष:
	find_uret_msr:
		msr = vmx_find_uret_msr(vmx, msr_info->index);
		अगर (msr) अणु
			msr_info->data = msr->data;
			अवरोध;
		पूर्ण
		वापस kvm_get_msr_common(vcpu, msr_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 nested_vmx_truncate_sysenter_addr(काष्ठा kvm_vcpu *vcpu,
						    u64 data)
अणु
#अगर_घोषित CONFIG_X86_64
	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_LM))
		वापस (u32)data;
#पूर्ण_अगर
	वापस (अचिन्हित दीर्घ)data;
पूर्ण

अटल u64 vcpu_supported_debugctl(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 debugctl = vmx_supported_debugctl();

	अगर (!पूर्णांकel_pmu_lbr_is_enabled(vcpu))
		debugctl &= ~DEBUGCTLMSR_LBR_MASK;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_BUS_LOCK_DETECT))
		debugctl &= ~DEBUGCTLMSR_BUS_LOCK_DETECT;

	वापस debugctl;
पूर्ण

/*
 * Writes msr value पूर्णांकo the appropriate "register".
 * Returns 0 on success, non-0 otherwise.
 * Assumes vcpu_load() was alपढ़ोy called.
 */
अटल पूर्णांक vmx_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmx_uret_msr *msr;
	पूर्णांक ret = 0;
	u32 msr_index = msr_info->index;
	u64 data = msr_info->data;
	u32 index;

	चयन (msr_index) अणु
	हाल MSR_EFER:
		ret = kvm_set_msr_common(vcpu, msr_info);
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल MSR_FS_BASE:
		vmx_segment_cache_clear(vmx);
		vmcs_ग_लिखोl(GUEST_FS_BASE, data);
		अवरोध;
	हाल MSR_GS_BASE:
		vmx_segment_cache_clear(vmx);
		vmcs_ग_लिखोl(GUEST_GS_BASE, data);
		अवरोध;
	हाल MSR_KERNEL_GS_BASE:
		vmx_ग_लिखो_guest_kernel_gs_base(vmx, data);
		अवरोध;
#पूर्ण_अगर
	हाल MSR_IA32_SYSENTER_CS:
		अगर (is_guest_mode(vcpu))
			get_vmcs12(vcpu)->guest_sysenter_cs = data;
		vmcs_ग_लिखो32(GUEST_SYSENTER_CS, data);
		अवरोध;
	हाल MSR_IA32_SYSENTER_EIP:
		अगर (is_guest_mode(vcpu)) अणु
			data = nested_vmx_truncate_sysenter_addr(vcpu, data);
			get_vmcs12(vcpu)->guest_sysenter_eip = data;
		पूर्ण
		vmcs_ग_लिखोl(GUEST_SYSENTER_EIP, data);
		अवरोध;
	हाल MSR_IA32_SYSENTER_ESP:
		अगर (is_guest_mode(vcpu)) अणु
			data = nested_vmx_truncate_sysenter_addr(vcpu, data);
			get_vmcs12(vcpu)->guest_sysenter_esp = data;
		पूर्ण
		vmcs_ग_लिखोl(GUEST_SYSENTER_ESP, data);
		अवरोध;
	हाल MSR_IA32_DEBUGCTLMSR: अणु
		u64 invalid = data & ~vcpu_supported_debugctl(vcpu);
		अगर (invalid & (DEBUGCTLMSR_BTF|DEBUGCTLMSR_LBR)) अणु
			अगर (report_ignored_msrs)
				vcpu_unimpl(vcpu, "%s: BTF|LBR in IA32_DEBUGCTLMSR 0x%llx, nop\n",
					    __func__, data);
			data &= ~(DEBUGCTLMSR_BTF|DEBUGCTLMSR_LBR);
			invalid &= ~(DEBUGCTLMSR_BTF|DEBUGCTLMSR_LBR);
		पूर्ण

		अगर (invalid)
			वापस 1;

		अगर (is_guest_mode(vcpu) && get_vmcs12(vcpu)->vm_निकास_controls &
						VM_EXIT_SAVE_DEBUG_CONTROLS)
			get_vmcs12(vcpu)->guest_ia32_debugctl = data;

		vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, data);
		अगर (पूर्णांकel_pmu_lbr_is_enabled(vcpu) && !to_vmx(vcpu)->lbr_desc.event &&
		    (data & DEBUGCTLMSR_LBR))
			पूर्णांकel_pmu_create_guest_lbr_event(vcpu);
		वापस 0;
	पूर्ण
	हाल MSR_IA32_BNDCFGS:
		अगर (!kvm_mpx_supported() ||
		    (!msr_info->host_initiated &&
		     !guest_cpuid_has(vcpu, X86_FEATURE_MPX)))
			वापस 1;
		अगर (is_noncanonical_address(data & PAGE_MASK, vcpu) ||
		    (data & MSR_IA32_BNDCFGS_RSVD))
			वापस 1;
		vmcs_ग_लिखो64(GUEST_BNDCFGS, data);
		अवरोध;
	हाल MSR_IA32_UMWAIT_CONTROL:
		अगर (!msr_info->host_initiated && !vmx_has_रुकोpkg(vmx))
			वापस 1;

		/* The reserved bit 1 and non-32 bit [63:32] should be zero */
		अगर (data & (BIT_ULL(1) | GENMASK_ULL(63, 32)))
			वापस 1;

		vmx->msr_ia32_umरुको_control = data;
		अवरोध;
	हाल MSR_IA32_SPEC_CTRL:
		अगर (!msr_info->host_initiated &&
		    !guest_has_spec_ctrl_msr(vcpu))
			वापस 1;

		अगर (kvm_spec_ctrl_test_value(data))
			वापस 1;

		vmx->spec_ctrl = data;
		अगर (!data)
			अवरोध;

		/*
		 * For non-nested:
		 * When it's written (to non-zero) क्रम the first समय, pass
		 * it through.
		 *
		 * For nested:
		 * The handling of the MSR biपंचांगap क्रम L2 guests is करोne in
		 * nested_vmx_prepare_msr_biपंचांगap. We should not touch the
		 * vmcs02.msr_biपंचांगap here since it माला_लो completely overwritten
		 * in the merging. We update the vmcs01 here क्रम L1 as well
		 * since it will end up touching the MSR anyway now.
		 */
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu,
					      MSR_IA32_SPEC_CTRL,
					      MSR_TYPE_RW);
		अवरोध;
	हाल MSR_IA32_TSX_CTRL:
		अगर (!msr_info->host_initiated &&
		    !(vcpu->arch.arch_capabilities & ARCH_CAP_TSX_CTRL_MSR))
			वापस 1;
		अगर (data & ~(TSX_CTRL_RTM_DISABLE | TSX_CTRL_CPUID_CLEAR))
			वापस 1;
		जाओ find_uret_msr;
	हाल MSR_IA32_PRED_CMD:
		अगर (!msr_info->host_initiated &&
		    !guest_has_pred_cmd_msr(vcpu))
			वापस 1;

		अगर (data & ~PRED_CMD_IBPB)
			वापस 1;
		अगर (!boot_cpu_has(X86_FEATURE_IBPB))
			वापस 1;
		अगर (!data)
			अवरोध;

		wrmsrl(MSR_IA32_PRED_CMD, PRED_CMD_IBPB);

		/*
		 * For non-nested:
		 * When it's written (to non-zero) क्रम the first समय, pass
		 * it through.
		 *
		 * For nested:
		 * The handling of the MSR biपंचांगap क्रम L2 guests is करोne in
		 * nested_vmx_prepare_msr_biपंचांगap. We should not touch the
		 * vmcs02.msr_biपंचांगap here since it माला_लो completely overwritten
		 * in the merging.
		 */
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_PRED_CMD, MSR_TYPE_W);
		अवरोध;
	हाल MSR_IA32_CR_PAT:
		अगर (!kvm_pat_valid(data))
			वापस 1;

		अगर (is_guest_mode(vcpu) &&
		    get_vmcs12(vcpu)->vm_निकास_controls & VM_EXIT_SAVE_IA32_PAT)
			get_vmcs12(vcpu)->guest_ia32_pat = data;

		अगर (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) अणु
			vmcs_ग_लिखो64(GUEST_IA32_PAT, data);
			vcpu->arch.pat = data;
			अवरोध;
		पूर्ण
		ret = kvm_set_msr_common(vcpu, msr_info);
		अवरोध;
	हाल MSR_IA32_TSC_ADJUST:
		ret = kvm_set_msr_common(vcpu, msr_info);
		अवरोध;
	हाल MSR_IA32_MCG_EXT_CTL:
		अगर ((!msr_info->host_initiated &&
		     !(to_vmx(vcpu)->msr_ia32_feature_control &
		       FEAT_CTL_LMCE_ENABLED)) ||
		    (data & ~MCG_EXT_CTL_LMCE_EN))
			वापस 1;
		vcpu->arch.mcg_ext_ctl = data;
		अवरोध;
	हाल MSR_IA32_FEAT_CTL:
		अगर (!vmx_feature_control_msr_valid(vcpu, data) ||
		    (to_vmx(vcpu)->msr_ia32_feature_control &
		     FEAT_CTL_LOCKED && !msr_info->host_initiated))
			वापस 1;
		vmx->msr_ia32_feature_control = data;
		अगर (msr_info->host_initiated && data == 0)
			vmx_leave_nested(vcpu);

		/* SGX may be enabled/disabled by guest's firmware */
		vmx_ग_लिखो_encls_biपंचांगap(vcpu, शून्य);
		अवरोध;
	हाल MSR_IA32_SGXLEPUBKEYHASH0 ... MSR_IA32_SGXLEPUBKEYHASH3:
		/*
		 * On real hardware, the LE hash MSRs are writable beक्रमe
		 * the firmware sets bit 0 in MSR 0x7a ("activating" SGX),
		 * at which poपूर्णांक SGX related bits in IA32_FEATURE_CONTROL
		 * become writable.
		 *
		 * KVM करोes not emulate SGX activation क्रम simplicity, so
		 * allow ग_लिखोs to the LE hash MSRs अगर IA32_FEATURE_CONTROL
		 * is unlocked.  This is technically not architectural
		 * behavior, but it's बंद enough.
		 */
		अगर (!msr_info->host_initiated &&
		    (!guest_cpuid_has(vcpu, X86_FEATURE_SGX_LC) ||
		    ((vmx->msr_ia32_feature_control & FEAT_CTL_LOCKED) &&
		    !(vmx->msr_ia32_feature_control & FEAT_CTL_SGX_LC_ENABLED))))
			वापस 1;
		vmx->msr_ia32_sgxlepubkeyhash
			[msr_index - MSR_IA32_SGXLEPUBKEYHASH0] = data;
		अवरोध;
	हाल MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		अगर (!msr_info->host_initiated)
			वापस 1; /* they are पढ़ो-only */
		अगर (!nested_vmx_allowed(vcpu))
			वापस 1;
		वापस vmx_set_vmx_msr(vcpu, msr_index, data);
	हाल MSR_IA32_RTIT_CTL:
		अगर (!vmx_pt_mode_is_host_guest() ||
			vmx_rtit_ctl_check(vcpu, data) ||
			vmx->nested.vmxon)
			वापस 1;
		vmcs_ग_लिखो64(GUEST_IA32_RTIT_CTL, data);
		vmx->pt_desc.guest.ctl = data;
		pt_update_पूर्णांकercept_क्रम_msr(vcpu);
		अवरोध;
	हाल MSR_IA32_RTIT_STATUS:
		अगर (!pt_can_ग_लिखो_msr(vmx))
			वापस 1;
		अगर (data & MSR_IA32_RTIT_STATUS_MASK)
			वापस 1;
		vmx->pt_desc.guest.status = data;
		अवरोध;
	हाल MSR_IA32_RTIT_CR3_MATCH:
		अगर (!pt_can_ग_लिखो_msr(vmx))
			वापस 1;
		अगर (!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					   PT_CAP_cr3_filtering))
			वापस 1;
		vmx->pt_desc.guest.cr3_match = data;
		अवरोध;
	हाल MSR_IA32_RTIT_OUTPUT_BASE:
		अगर (!pt_can_ग_लिखो_msr(vmx))
			वापस 1;
		अगर (!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					   PT_CAP_topa_output) &&
		    !पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					   PT_CAP_single_range_output))
			वापस 1;
		अगर (!pt_output_base_valid(vcpu, data))
			वापस 1;
		vmx->pt_desc.guest.output_base = data;
		अवरोध;
	हाल MSR_IA32_RTIT_OUTPUT_MASK:
		अगर (!pt_can_ग_लिखो_msr(vmx))
			वापस 1;
		अगर (!पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					   PT_CAP_topa_output) &&
		    !पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
					   PT_CAP_single_range_output))
			वापस 1;
		vmx->pt_desc.guest.output_mask = data;
		अवरोध;
	हाल MSR_IA32_RTIT_ADDR0_A ... MSR_IA32_RTIT_ADDR3_B:
		अगर (!pt_can_ग_लिखो_msr(vmx))
			वापस 1;
		index = msr_info->index - MSR_IA32_RTIT_ADDR0_A;
		अगर (index >= 2 * पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
						       PT_CAP_num_address_ranges))
			वापस 1;
		अगर (is_noncanonical_address(data, vcpu))
			वापस 1;
		अगर (index % 2)
			vmx->pt_desc.guest.addr_b[index / 2] = data;
		अन्यथा
			vmx->pt_desc.guest.addr_a[index / 2] = data;
		अवरोध;
	हाल MSR_IA32_PERF_CAPABILITIES:
		अगर (data && !vcpu_to_pmu(vcpu)->version)
			वापस 1;
		अगर (data & PMU_CAP_LBR_FMT) अणु
			अगर ((data & PMU_CAP_LBR_FMT) !=
			    (vmx_get_perf_capabilities() & PMU_CAP_LBR_FMT))
				वापस 1;
			अगर (!पूर्णांकel_pmu_lbr_is_compatible(vcpu))
				वापस 1;
		पूर्ण
		ret = kvm_set_msr_common(vcpu, msr_info);
		अवरोध;

	शेष:
	find_uret_msr:
		msr = vmx_find_uret_msr(vmx, msr_index);
		अगर (msr)
			ret = vmx_set_guest_uret_msr(vmx, msr, data);
		अन्यथा
			ret = kvm_set_msr_common(vcpu, msr_info);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vmx_cache_reg(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_reg reg)
अणु
	अचिन्हित दीर्घ guest_owned_bits;

	kvm_रेजिस्टर_mark_available(vcpu, reg);

	चयन (reg) अणु
	हाल VCPU_REGS_RSP:
		vcpu->arch.regs[VCPU_REGS_RSP] = vmcs_पढ़ोl(GUEST_RSP);
		अवरोध;
	हाल VCPU_REGS_RIP:
		vcpu->arch.regs[VCPU_REGS_RIP] = vmcs_पढ़ोl(GUEST_RIP);
		अवरोध;
	हाल VCPU_EXREG_PDPTR:
		अगर (enable_ept)
			ept_save_pdptrs(vcpu);
		अवरोध;
	हाल VCPU_EXREG_CR0:
		guest_owned_bits = vcpu->arch.cr0_guest_owned_bits;

		vcpu->arch.cr0 &= ~guest_owned_bits;
		vcpu->arch.cr0 |= vmcs_पढ़ोl(GUEST_CR0) & guest_owned_bits;
		अवरोध;
	हाल VCPU_EXREG_CR3:
		अगर (is_unrestricted_guest(vcpu) ||
		    (enable_ept && is_paging(vcpu)))
			vcpu->arch.cr3 = vmcs_पढ़ोl(GUEST_CR3);
		अवरोध;
	हाल VCPU_EXREG_CR4:
		guest_owned_bits = vcpu->arch.cr4_guest_owned_bits;

		vcpu->arch.cr4 &= ~guest_owned_bits;
		vcpu->arch.cr4 |= vmcs_पढ़ोl(GUEST_CR4) & guest_owned_bits;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल __init पूर्णांक cpu_has_kvm_support(व्योम)
अणु
	वापस cpu_has_vmx();
पूर्ण

अटल __init पूर्णांक vmx_disabled_by_bios(व्योम)
अणु
	वापस !boot_cpu_has(X86_FEATURE_MSR_IA32_FEAT_CTL) ||
	       !boot_cpu_has(X86_FEATURE_VMX);
पूर्ण

अटल पूर्णांक kvm_cpu_vmxon(u64 vmxon_poपूर्णांकer)
अणु
	u64 msr;

	cr4_set_bits(X86_CR4_VMXE);

	यंत्र_अस्थिर_जाओ("1: vmxon %[vmxon_pointer]\n\t"
			  _ASM_EXTABLE(1b, %l[fault])
			  : : [vmxon_poपूर्णांकer] "m"(vmxon_poपूर्णांकer)
			  : : fault);
	वापस 0;

fault:
	WARN_ONCE(1, "VMXON faulted, MSR_IA32_FEAT_CTL (0x3a) = 0x%llx\n",
		  rdmsrl_safe(MSR_IA32_FEAT_CTL, &msr) ? 0xdeadbeef : msr);
	cr4_clear_bits(X86_CR4_VMXE);

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक hardware_enable(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	u64 phys_addr = __pa(per_cpu(vmxarea, cpu));
	पूर्णांक r;

	अगर (cr4_पढ़ो_shaकरोw() & X86_CR4_VMXE)
		वापस -EBUSY;

	/*
	 * This can happen अगर we hot-added a CPU but failed to allocate
	 * VP assist page क्रम it.
	 */
	अगर (अटल_branch_unlikely(&enable_evmcs) &&
	    !hv_get_vp_assist_page(cpu))
		वापस -EFAULT;

	पूर्णांकel_pt_handle_vmx(1);

	r = kvm_cpu_vmxon(phys_addr);
	अगर (r) अणु
		पूर्णांकel_pt_handle_vmx(0);
		वापस r;
	पूर्ण

	अगर (enable_ept)
		ept_sync_global();

	वापस 0;
पूर्ण

अटल व्योम vmclear_local_loaded_vmcss(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा loaded_vmcs *v, *n;

	list_क्रम_each_entry_safe(v, n, &per_cpu(loaded_vmcss_on_cpu, cpu),
				 loaded_vmcss_on_cpu_link)
		__loaded_vmcs_clear(v);
पूर्ण

अटल व्योम hardware_disable(व्योम)
अणु
	vmclear_local_loaded_vmcss();

	अगर (cpu_vmxoff())
		kvm_spurious_fault();

	पूर्णांकel_pt_handle_vmx(0);
पूर्ण

/*
 * There is no X86_FEATURE क्रम SGX yet, but anyway we need to query CPUID
 * directly instead of going through cpu_has(), to ensure KVM is trapping
 * ENCLS whenever it's supported in hardware.  It करोes not matter whether
 * the host OS supports or has enabled SGX.
 */
अटल bool cpu_has_sgx(व्योम)
अणु
	वापस cpuid_eax(0) >= 0x12 && (cpuid_eax(0x12) & BIT(0));
पूर्ण

अटल __init पूर्णांक adjust_vmx_controls(u32 ctl_min, u32 ctl_opt,
				      u32 msr, u32 *result)
अणु
	u32 vmx_msr_low, vmx_msr_high;
	u32 ctl = ctl_min | ctl_opt;

	rdmsr(msr, vmx_msr_low, vmx_msr_high);

	ctl &= vmx_msr_high; /* bit == 0 in high word ==> must be zero */
	ctl |= vmx_msr_low;  /* bit == 1 in low word  ==> must be one  */

	/* Ensure minimum (required) set of control bits are supported. */
	अगर (ctl_min & ~ctl)
		वापस -EIO;

	*result = ctl;
	वापस 0;
पूर्ण

अटल __init पूर्णांक setup_vmcs_config(काष्ठा vmcs_config *vmcs_conf,
				    काष्ठा vmx_capability *vmx_cap)
अणु
	u32 vmx_msr_low, vmx_msr_high;
	u32 min, opt, min2, opt2;
	u32 _pin_based_exec_control = 0;
	u32 _cpu_based_exec_control = 0;
	u32 _cpu_based_2nd_exec_control = 0;
	u32 _vmनिकास_control = 0;
	u32 _vmentry_control = 0;

	स_रखो(vmcs_conf, 0, माप(*vmcs_conf));
	min = CPU_BASED_HLT_EXITING |
#अगर_घोषित CONFIG_X86_64
	      CPU_BASED_CR8_LOAD_EXITING |
	      CPU_BASED_CR8_STORE_EXITING |
#पूर्ण_अगर
	      CPU_BASED_CR3_LOAD_EXITING |
	      CPU_BASED_CR3_STORE_EXITING |
	      CPU_BASED_UNCOND_IO_EXITING |
	      CPU_BASED_MOV_DR_EXITING |
	      CPU_BASED_USE_TSC_OFFSETTING |
	      CPU_BASED_MWAIT_EXITING |
	      CPU_BASED_MONITOR_EXITING |
	      CPU_BASED_INVLPG_EXITING |
	      CPU_BASED_RDPMC_EXITING;

	opt = CPU_BASED_TPR_SHADOW |
	      CPU_BASED_USE_MSR_BITMAPS |
	      CPU_BASED_ACTIVATE_SECONDARY_CONTROLS;
	अगर (adjust_vmx_controls(min, opt, MSR_IA32_VMX_PROCBASED_CTLS,
				&_cpu_based_exec_control) < 0)
		वापस -EIO;
#अगर_घोषित CONFIG_X86_64
	अगर ((_cpu_based_exec_control & CPU_BASED_TPR_SHADOW))
		_cpu_based_exec_control &= ~CPU_BASED_CR8_LOAD_EXITING &
					   ~CPU_BASED_CR8_STORE_EXITING;
#पूर्ण_अगर
	अगर (_cpu_based_exec_control & CPU_BASED_ACTIVATE_SECONDARY_CONTROLS) अणु
		min2 = 0;
		opt2 = SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
			SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE |
			SECONDARY_EXEC_WBINVD_EXITING |
			SECONDARY_EXEC_ENABLE_VPID |
			SECONDARY_EXEC_ENABLE_EPT |
			SECONDARY_EXEC_UNRESTRICTED_GUEST |
			SECONDARY_EXEC_PAUSE_LOOP_EXITING |
			SECONDARY_EXEC_DESC |
			SECONDARY_EXEC_ENABLE_RDTSCP |
			SECONDARY_EXEC_ENABLE_INVPCID |
			SECONDARY_EXEC_APIC_REGISTER_VIRT |
			SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |
			SECONDARY_EXEC_SHADOW_VMCS |
			SECONDARY_EXEC_XSAVES |
			SECONDARY_EXEC_RDSEED_EXITING |
			SECONDARY_EXEC_RDRAND_EXITING |
			SECONDARY_EXEC_ENABLE_PML |
			SECONDARY_EXEC_TSC_SCALING |
			SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE |
			SECONDARY_EXEC_PT_USE_GPA |
			SECONDARY_EXEC_PT_CONCEAL_VMX |
			SECONDARY_EXEC_ENABLE_VMFUNC |
			SECONDARY_EXEC_BUS_LOCK_DETECTION;
		अगर (cpu_has_sgx())
			opt2 |= SECONDARY_EXEC_ENCLS_EXITING;
		अगर (adjust_vmx_controls(min2, opt2,
					MSR_IA32_VMX_PROCBASED_CTLS2,
					&_cpu_based_2nd_exec_control) < 0)
			वापस -EIO;
	पूर्ण
#अगर_अघोषित CONFIG_X86_64
	अगर (!(_cpu_based_2nd_exec_control &
				SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES))
		_cpu_based_exec_control &= ~CPU_BASED_TPR_SHADOW;
#पूर्ण_अगर

	अगर (!(_cpu_based_exec_control & CPU_BASED_TPR_SHADOW))
		_cpu_based_2nd_exec_control &= ~(
				SECONDARY_EXEC_APIC_REGISTER_VIRT |
				SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE |
				SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);

	rdmsr_safe(MSR_IA32_VMX_EPT_VPID_CAP,
		&vmx_cap->ept, &vmx_cap->vpid);

	अगर (_cpu_based_2nd_exec_control & SECONDARY_EXEC_ENABLE_EPT) अणु
		/* CR3 accesses and invlpg करोn't need to cause VM Exits when EPT
		   enabled */
		_cpu_based_exec_control &= ~(CPU_BASED_CR3_LOAD_EXITING |
					     CPU_BASED_CR3_STORE_EXITING |
					     CPU_BASED_INVLPG_EXITING);
	पूर्ण अन्यथा अगर (vmx_cap->ept) अणु
		vmx_cap->ept = 0;
		pr_warn_once("EPT CAP should not exist if not support "
				"1-setting enable EPT VM-execution control\n");
	पूर्ण
	अगर (!(_cpu_based_2nd_exec_control & SECONDARY_EXEC_ENABLE_VPID) &&
		vmx_cap->vpid) अणु
		vmx_cap->vpid = 0;
		pr_warn_once("VPID CAP should not exist if not support "
				"1-setting enable VPID VM-execution control\n");
	पूर्ण

	min = VM_EXIT_SAVE_DEBUG_CONTROLS | VM_EXIT_ACK_INTR_ON_EXIT;
#अगर_घोषित CONFIG_X86_64
	min |= VM_EXIT_HOST_ADDR_SPACE_SIZE;
#पूर्ण_अगर
	opt = VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL |
	      VM_EXIT_LOAD_IA32_PAT |
	      VM_EXIT_LOAD_IA32_EFER |
	      VM_EXIT_CLEAR_BNDCFGS |
	      VM_EXIT_PT_CONCEAL_PIP |
	      VM_EXIT_CLEAR_IA32_RTIT_CTL;
	अगर (adjust_vmx_controls(min, opt, MSR_IA32_VMX_EXIT_CTLS,
				&_vmनिकास_control) < 0)
		वापस -EIO;

	min = PIN_BASED_EXT_INTR_MASK | PIN_BASED_NMI_EXITING;
	opt = PIN_BASED_VIRTUAL_NMIS | PIN_BASED_POSTED_INTR |
		 PIN_BASED_VMX_PREEMPTION_TIMER;
	अगर (adjust_vmx_controls(min, opt, MSR_IA32_VMX_PINBASED_CTLS,
				&_pin_based_exec_control) < 0)
		वापस -EIO;

	अगर (cpu_has_broken_vmx_preemption_समयr())
		_pin_based_exec_control &= ~PIN_BASED_VMX_PREEMPTION_TIMER;
	अगर (!(_cpu_based_2nd_exec_control &
		SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY))
		_pin_based_exec_control &= ~PIN_BASED_POSTED_INTR;

	min = VM_ENTRY_LOAD_DEBUG_CONTROLS;
	opt = VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL |
	      VM_ENTRY_LOAD_IA32_PAT |
	      VM_ENTRY_LOAD_IA32_EFER |
	      VM_ENTRY_LOAD_BNDCFGS |
	      VM_ENTRY_PT_CONCEAL_PIP |
	      VM_ENTRY_LOAD_IA32_RTIT_CTL;
	अगर (adjust_vmx_controls(min, opt, MSR_IA32_VMX_ENTRY_CTLS,
				&_vmentry_control) < 0)
		वापस -EIO;

	/*
	 * Some cpus support VM_अणुENTRY,EXITपूर्ण_IA32_PERF_GLOBAL_CTRL but they
	 * can't be used due to an errata where VM Exit may incorrectly clear
	 * IA32_PERF_GLOBAL_CTRL[34:32].  Workaround the errata by using the
	 * MSR load mechanism to चयन IA32_PERF_GLOBAL_CTRL.
	 */
	अगर (boot_cpu_data.x86 == 0x6) अणु
		चयन (boot_cpu_data.x86_model) अणु
		हाल 26: /* AAK155 */
		हाल 30: /* AAP115 */
		हाल 37: /* AAT100 */
		हाल 44: /* BC86,AAY89,BD102 */
		हाल 46: /* BA97 */
			_vmentry_control &= ~VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL;
			_vmनिकास_control &= ~VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL;
			pr_warn_once("kvm: VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL "
					"does not work properly. Using workaround\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण


	rdmsr(MSR_IA32_VMX_BASIC, vmx_msr_low, vmx_msr_high);

	/* IA-32 SDM Vol 3B: VMCS size is never greater than 4kB. */
	अगर ((vmx_msr_high & 0x1fff) > PAGE_SIZE)
		वापस -EIO;

#अगर_घोषित CONFIG_X86_64
	/* IA-32 SDM Vol 3B: 64-bit CPUs always have VMX_BASIC_MSR[48]==0. */
	अगर (vmx_msr_high & (1u<<16))
		वापस -EIO;
#पूर्ण_अगर

	/* Require Write-Back (WB) memory type क्रम VMCS accesses. */
	अगर (((vmx_msr_high >> 18) & 15) != 6)
		वापस -EIO;

	vmcs_conf->size = vmx_msr_high & 0x1fff;
	vmcs_conf->order = get_order(vmcs_conf->size);
	vmcs_conf->basic_cap = vmx_msr_high & ~0x1fff;

	vmcs_conf->revision_id = vmx_msr_low;

	vmcs_conf->pin_based_exec_ctrl = _pin_based_exec_control;
	vmcs_conf->cpu_based_exec_ctrl = _cpu_based_exec_control;
	vmcs_conf->cpu_based_2nd_exec_ctrl = _cpu_based_2nd_exec_control;
	vmcs_conf->vmनिकास_ctrl         = _vmनिकास_control;
	vmcs_conf->vmentry_ctrl        = _vmentry_control;

#अगर IS_ENABLED(CONFIG_HYPERV)
	अगर (enlightened_vmcs)
		evmcs_sanitize_exec_ctrls(vmcs_conf);
#पूर्ण_अगर

	वापस 0;
पूर्ण

काष्ठा vmcs *alloc_vmcs_cpu(bool shaकरोw, पूर्णांक cpu, gfp_t flags)
अणु
	पूर्णांक node = cpu_to_node(cpu);
	काष्ठा page *pages;
	काष्ठा vmcs *vmcs;

	pages = __alloc_pages_node(node, flags, vmcs_config.order);
	अगर (!pages)
		वापस शून्य;
	vmcs = page_address(pages);
	स_रखो(vmcs, 0, vmcs_config.size);

	/* KVM supports Enlightened VMCS v1 only */
	अगर (अटल_branch_unlikely(&enable_evmcs))
		vmcs->hdr.revision_id = KVM_EVMCS_VERSION;
	अन्यथा
		vmcs->hdr.revision_id = vmcs_config.revision_id;

	अगर (shaकरोw)
		vmcs->hdr.shaकरोw_vmcs = 1;
	वापस vmcs;
पूर्ण

व्योम मुक्त_vmcs(काष्ठा vmcs *vmcs)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)vmcs, vmcs_config.order);
पूर्ण

/*
 * Free a VMCS, but beक्रमe that VMCLEAR it on the CPU where it was last loaded
 */
व्योम मुक्त_loaded_vmcs(काष्ठा loaded_vmcs *loaded_vmcs)
अणु
	अगर (!loaded_vmcs->vmcs)
		वापस;
	loaded_vmcs_clear(loaded_vmcs);
	मुक्त_vmcs(loaded_vmcs->vmcs);
	loaded_vmcs->vmcs = शून्य;
	अगर (loaded_vmcs->msr_biपंचांगap)
		मुक्त_page((अचिन्हित दीर्घ)loaded_vmcs->msr_biपंचांगap);
	WARN_ON(loaded_vmcs->shaकरोw_vmcs != शून्य);
पूर्ण

पूर्णांक alloc_loaded_vmcs(काष्ठा loaded_vmcs *loaded_vmcs)
अणु
	loaded_vmcs->vmcs = alloc_vmcs(false);
	अगर (!loaded_vmcs->vmcs)
		वापस -ENOMEM;

	vmcs_clear(loaded_vmcs->vmcs);

	loaded_vmcs->shaकरोw_vmcs = शून्य;
	loaded_vmcs->hv_समयr_soft_disabled = false;
	loaded_vmcs->cpu = -1;
	loaded_vmcs->launched = 0;

	अगर (cpu_has_vmx_msr_biपंचांगap()) अणु
		loaded_vmcs->msr_biपंचांगap = (अचिन्हित दीर्घ *)
				__get_मुक्त_page(GFP_KERNEL_ACCOUNT);
		अगर (!loaded_vmcs->msr_biपंचांगap)
			जाओ out_vmcs;
		स_रखो(loaded_vmcs->msr_biपंचांगap, 0xff, PAGE_SIZE);

		अगर (IS_ENABLED(CONFIG_HYPERV) &&
		    अटल_branch_unlikely(&enable_evmcs) &&
		    (ms_hyperv.nested_features & HV_X64_NESTED_MSR_BITMAP)) अणु
			काष्ठा hv_enlightened_vmcs *evmcs =
				(काष्ठा hv_enlightened_vmcs *)loaded_vmcs->vmcs;

			evmcs->hv_enlightenments_control.msr_biपंचांगap = 1;
		पूर्ण
	पूर्ण

	स_रखो(&loaded_vmcs->host_state, 0, माप(काष्ठा vmcs_host_state));
	स_रखो(&loaded_vmcs->controls_shaकरोw, 0,
		माप(काष्ठा vmcs_controls_shaकरोw));

	वापस 0;

out_vmcs:
	मुक्त_loaded_vmcs(loaded_vmcs);
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_kvm_area(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		मुक्त_vmcs(per_cpu(vmxarea, cpu));
		per_cpu(vmxarea, cpu) = शून्य;
	पूर्ण
पूर्ण

अटल __init पूर्णांक alloc_kvm_area(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा vmcs *vmcs;

		vmcs = alloc_vmcs_cpu(false, cpu, GFP_KERNEL);
		अगर (!vmcs) अणु
			मुक्त_kvm_area();
			वापस -ENOMEM;
		पूर्ण

		/*
		 * When eVMCS is enabled, alloc_vmcs_cpu() sets
		 * vmcs->revision_id to KVM_EVMCS_VERSION instead of
		 * revision_id reported by MSR_IA32_VMX_BASIC.
		 *
		 * However, even though not explicitly करोcumented by
		 * TLFS, VMXArea passed as VMXON argument should
		 * still be marked with revision_id reported by
		 * physical CPU.
		 */
		अगर (अटल_branch_unlikely(&enable_evmcs))
			vmcs->hdr.revision_id = vmcs_config.revision_id;

		per_cpu(vmxarea, cpu) = vmcs;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fix_pmode_seg(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg,
		काष्ठा kvm_segment *save)
अणु
	अगर (!emulate_invalid_guest_state) अणु
		/*
		 * CS and SS RPL should be equal during guest entry according
		 * to VMX spec, but in reality it is not always so. Since vcpu
		 * is in the middle of the transition from real mode to
		 * रक्षित mode it is safe to assume that RPL 0 is a good
		 * शेष value.
		 */
		अगर (seg == VCPU_SREG_CS || seg == VCPU_SREG_SS)
			save->selector &= ~SEGMENT_RPL_MASK;
		save->dpl = save->selector & SEGMENT_RPL_MASK;
		save->s = 1;
	पूर्ण
	vmx_set_segment(vcpu, save, seg);
पूर्ण

अटल व्योम enter_pmode(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * Update real mode segment cache. It may be not up-to-date अगर segment
	 * रेजिस्टर was written जबतक vcpu was in a guest mode.
	 */
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_ES], VCPU_SREG_ES);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_DS], VCPU_SREG_DS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_FS], VCPU_SREG_FS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_GS], VCPU_SREG_GS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_SS], VCPU_SREG_SS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_CS], VCPU_SREG_CS);

	vmx->rmode.vm86_active = 0;

	vmx_set_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_TR], VCPU_SREG_TR);

	flags = vmcs_पढ़ोl(GUEST_RFLAGS);
	flags &= RMODE_GUEST_OWNED_EFLAGS_BITS;
	flags |= vmx->rmode.save_rflags & ~RMODE_GUEST_OWNED_EFLAGS_BITS;
	vmcs_ग_लिखोl(GUEST_RFLAGS, flags);

	vmcs_ग_लिखोl(GUEST_CR4, (vmcs_पढ़ोl(GUEST_CR4) & ~X86_CR4_VME) |
			(vmcs_पढ़ोl(CR4_READ_SHADOW) & X86_CR4_VME));

	vmx_update_exception_biपंचांगap(vcpu);

	fix_pmode_seg(vcpu, VCPU_SREG_CS, &vmx->rmode.segs[VCPU_SREG_CS]);
	fix_pmode_seg(vcpu, VCPU_SREG_SS, &vmx->rmode.segs[VCPU_SREG_SS]);
	fix_pmode_seg(vcpu, VCPU_SREG_ES, &vmx->rmode.segs[VCPU_SREG_ES]);
	fix_pmode_seg(vcpu, VCPU_SREG_DS, &vmx->rmode.segs[VCPU_SREG_DS]);
	fix_pmode_seg(vcpu, VCPU_SREG_FS, &vmx->rmode.segs[VCPU_SREG_FS]);
	fix_pmode_seg(vcpu, VCPU_SREG_GS, &vmx->rmode.segs[VCPU_SREG_GS]);
पूर्ण

अटल व्योम fix_rmode_seg(पूर्णांक seg, काष्ठा kvm_segment *save)
अणु
	स्थिर काष्ठा kvm_vmx_segment_field *sf = &kvm_vmx_segment_fields[seg];
	काष्ठा kvm_segment var = *save;

	var.dpl = 0x3;
	अगर (seg == VCPU_SREG_CS)
		var.type = 0x3;

	अगर (!emulate_invalid_guest_state) अणु
		var.selector = var.base >> 4;
		var.base = var.base & 0xffff0;
		var.limit = 0xffff;
		var.g = 0;
		var.db = 0;
		var.present = 1;
		var.s = 1;
		var.l = 0;
		var.unusable = 0;
		var.type = 0x3;
		var.avl = 0;
		अगर (save->base & 0xf)
			prपूर्णांकk_once(KERN_WARNING "kvm: segment base is not "
					"paragraph aligned when entering "
					"protected mode (seg=%d)", seg);
	पूर्ण

	vmcs_ग_लिखो16(sf->selector, var.selector);
	vmcs_ग_लिखोl(sf->base, var.base);
	vmcs_ग_लिखो32(sf->limit, var.limit);
	vmcs_ग_लिखो32(sf->ar_bytes, vmx_segment_access_rights(&var));
पूर्ण

अटल व्योम enter_rmode(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा kvm_vmx *kvm_vmx = to_kvm_vmx(vcpu->kvm);

	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_TR], VCPU_SREG_TR);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_ES], VCPU_SREG_ES);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_DS], VCPU_SREG_DS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_FS], VCPU_SREG_FS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_GS], VCPU_SREG_GS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_SS], VCPU_SREG_SS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_CS], VCPU_SREG_CS);

	vmx->rmode.vm86_active = 1;

	/*
	 * Very old userspace करोes not call KVM_SET_TSS_ADDR beक्रमe entering
	 * vcpu. Warn the user that an update is overdue.
	 */
	अगर (!kvm_vmx->tss_addr)
		prपूर्णांकk_once(KERN_WARNING "kvm: KVM_SET_TSS_ADDR need to be "
			     "called before entering vcpu\n");

	vmx_segment_cache_clear(vmx);

	vmcs_ग_लिखोl(GUEST_TR_BASE, kvm_vmx->tss_addr);
	vmcs_ग_लिखो32(GUEST_TR_LIMIT, RMODE_TSS_SIZE - 1);
	vmcs_ग_लिखो32(GUEST_TR_AR_BYTES, 0x008b);

	flags = vmcs_पढ़ोl(GUEST_RFLAGS);
	vmx->rmode.save_rflags = flags;

	flags |= X86_EFLAGS_IOPL | X86_EFLAGS_VM;

	vmcs_ग_लिखोl(GUEST_RFLAGS, flags);
	vmcs_ग_लिखोl(GUEST_CR4, vmcs_पढ़ोl(GUEST_CR4) | X86_CR4_VME);
	vmx_update_exception_biपंचांगap(vcpu);

	fix_rmode_seg(VCPU_SREG_SS, &vmx->rmode.segs[VCPU_SREG_SS]);
	fix_rmode_seg(VCPU_SREG_CS, &vmx->rmode.segs[VCPU_SREG_CS]);
	fix_rmode_seg(VCPU_SREG_ES, &vmx->rmode.segs[VCPU_SREG_ES]);
	fix_rmode_seg(VCPU_SREG_DS, &vmx->rmode.segs[VCPU_SREG_DS]);
	fix_rmode_seg(VCPU_SREG_GS, &vmx->rmode.segs[VCPU_SREG_GS]);
	fix_rmode_seg(VCPU_SREG_FS, &vmx->rmode.segs[VCPU_SREG_FS]);

	kvm_mmu_reset_context(vcpu);
पूर्ण

पूर्णांक vmx_set_efer(काष्ठा kvm_vcpu *vcpu, u64 efer)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmx_uret_msr *msr = vmx_find_uret_msr(vmx, MSR_EFER);

	/* Nothing to करो अगर hardware करोesn't support EFER. */
	अगर (!msr)
		वापस 0;

	vcpu->arch.efer = efer;
	अगर (efer & EFER_LMA) अणु
		vm_entry_controls_setbit(to_vmx(vcpu), VM_ENTRY_IA32E_MODE);
		msr->data = efer;
	पूर्ण अन्यथा अणु
		vm_entry_controls_clearbit(to_vmx(vcpu), VM_ENTRY_IA32E_MODE);

		msr->data = efer & ~EFER_LME;
	पूर्ण
	setup_msrs(vmx);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64

अटल व्योम enter_lmode(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 guest_tr_ar;

	vmx_segment_cache_clear(to_vmx(vcpu));

	guest_tr_ar = vmcs_पढ़ो32(GUEST_TR_AR_BYTES);
	अगर ((guest_tr_ar & VMX_AR_TYPE_MASK) != VMX_AR_TYPE_BUSY_64_TSS) अणु
		pr_debug_ratelimited("%s: tss fixup for long mode. \n",
				     __func__);
		vmcs_ग_लिखो32(GUEST_TR_AR_BYTES,
			     (guest_tr_ar & ~VMX_AR_TYPE_MASK)
			     | VMX_AR_TYPE_BUSY_64_TSS);
	पूर्ण
	vmx_set_efer(vcpu, vcpu->arch.efer | EFER_LMA);
पूर्ण

अटल व्योम निकास_lmode(काष्ठा kvm_vcpu *vcpu)
अणु
	vm_entry_controls_clearbit(to_vmx(vcpu), VM_ENTRY_IA32E_MODE);
	vmx_set_efer(vcpu, vcpu->arch.efer & ~EFER_LMA);
पूर्ण

#पूर्ण_अगर

अटल व्योम vmx_flush_tlb_all(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * INVEPT must be issued when EPT is enabled, irrespective of VPID, as
	 * the CPU is not required to invalidate guest-physical mappings on
	 * VM-Entry, even अगर VPID is disabled.  Guest-physical mappings are
	 * associated with the root EPT काष्ठाure and not any particular VPID
	 * (INVVPID also isn't required to invalidate guest-physical mappings).
	 */
	अगर (enable_ept) अणु
		ept_sync_global();
	पूर्ण अन्यथा अगर (enable_vpid) अणु
		अगर (cpu_has_vmx_invvpid_global()) अणु
			vpid_sync_vcpu_global();
		पूर्ण अन्यथा अणु
			vpid_sync_vcpu_single(vmx->vpid);
			vpid_sync_vcpu_single(vmx->nested.vpid02);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vmx_flush_tlb_current(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_mmu *mmu = vcpu->arch.mmu;
	u64 root_hpa = mmu->root_hpa;

	/* No flush required अगर the current context is invalid. */
	अगर (!VALID_PAGE(root_hpa))
		वापस;

	अगर (enable_ept)
		ept_sync_context(स्थिरruct_eptp(vcpu, root_hpa,
						mmu->shaकरोw_root_level));
	अन्यथा अगर (!is_guest_mode(vcpu))
		vpid_sync_context(to_vmx(vcpu)->vpid);
	अन्यथा
		vpid_sync_context(nested_get_vpid02(vcpu));
पूर्ण

अटल व्योम vmx_flush_tlb_gva(काष्ठा kvm_vcpu *vcpu, gva_t addr)
अणु
	/*
	 * vpid_sync_vcpu_addr() is a nop अगर vmx->vpid==0, see the comment in
	 * vmx_flush_tlb_guest() क्रम an explanation of why this is ok.
	 */
	vpid_sync_vcpu_addr(to_vmx(vcpu)->vpid, addr);
पूर्ण

अटल व्योम vmx_flush_tlb_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * vpid_sync_context() is a nop अगर vmx->vpid==0, e.g. अगर enable_vpid==0
	 * or a vpid couldn't be allocated क्रम this vCPU.  VM-Enter and VM-Exit
	 * are required to flush GVA->अणुG,Hपूर्णPA mappings from the TLB अगर vpid is
	 * disabled (VM-Enter with vpid enabled and vpid==0 is disallowed),
	 * i.e. no explicit INVVPID is necessary.
	 */
	vpid_sync_context(to_vmx(vcpu)->vpid);
पूर्ण

व्योम vmx_ept_load_pdptrs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_mmu *mmu = vcpu->arch.walk_mmu;

	अगर (!kvm_रेजिस्टर_is_dirty(vcpu, VCPU_EXREG_PDPTR))
		वापस;

	अगर (is_pae_paging(vcpu)) अणु
		vmcs_ग_लिखो64(GUEST_PDPTR0, mmu->pdptrs[0]);
		vmcs_ग_लिखो64(GUEST_PDPTR1, mmu->pdptrs[1]);
		vmcs_ग_लिखो64(GUEST_PDPTR2, mmu->pdptrs[2]);
		vmcs_ग_लिखो64(GUEST_PDPTR3, mmu->pdptrs[3]);
	पूर्ण
पूर्ण

व्योम ept_save_pdptrs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_mmu *mmu = vcpu->arch.walk_mmu;

	अगर (WARN_ON_ONCE(!is_pae_paging(vcpu)))
		वापस;

	mmu->pdptrs[0] = vmcs_पढ़ो64(GUEST_PDPTR0);
	mmu->pdptrs[1] = vmcs_पढ़ो64(GUEST_PDPTR1);
	mmu->pdptrs[2] = vmcs_पढ़ो64(GUEST_PDPTR2);
	mmu->pdptrs[3] = vmcs_पढ़ो64(GUEST_PDPTR3);

	kvm_रेजिस्टर_mark_dirty(vcpu, VCPU_EXREG_PDPTR);
पूर्ण

अटल व्योम ept_update_paging_mode_cr0(अचिन्हित दीर्घ *hw_cr0,
					अचिन्हित दीर्घ cr0,
					काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_CR3))
		vmx_cache_reg(vcpu, VCPU_EXREG_CR3);
	अगर (!(cr0 & X86_CR0_PG)) अणु
		/* From paging/starting to nonpaging */
		exec_controls_setbit(vmx, CPU_BASED_CR3_LOAD_EXITING |
					  CPU_BASED_CR3_STORE_EXITING);
		vcpu->arch.cr0 = cr0;
		vmx_set_cr4(vcpu, kvm_पढ़ो_cr4(vcpu));
	पूर्ण अन्यथा अगर (!is_paging(vcpu)) अणु
		/* From nonpaging to paging */
		exec_controls_clearbit(vmx, CPU_BASED_CR3_LOAD_EXITING |
					    CPU_BASED_CR3_STORE_EXITING);
		vcpu->arch.cr0 = cr0;
		vmx_set_cr4(vcpu, kvm_पढ़ो_cr4(vcpu));
	पूर्ण

	अगर (!(cr0 & X86_CR0_WP))
		*hw_cr0 &= ~X86_CR0_WP;
पूर्ण

व्योम vmx_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ hw_cr0;

	hw_cr0 = (cr0 & ~KVM_VM_CR0_ALWAYS_OFF);
	अगर (is_unrestricted_guest(vcpu))
		hw_cr0 |= KVM_VM_CR0_ALWAYS_ON_UNRESTRICTED_GUEST;
	अन्यथा अणु
		hw_cr0 |= KVM_VM_CR0_ALWAYS_ON;

		अगर (vmx->rmode.vm86_active && (cr0 & X86_CR0_PE))
			enter_pmode(vcpu);

		अगर (!vmx->rmode.vm86_active && !(cr0 & X86_CR0_PE))
			enter_rmode(vcpu);
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	अगर (vcpu->arch.efer & EFER_LME) अणु
		अगर (!is_paging(vcpu) && (cr0 & X86_CR0_PG))
			enter_lmode(vcpu);
		अगर (is_paging(vcpu) && !(cr0 & X86_CR0_PG))
			निकास_lmode(vcpu);
	पूर्ण
#पूर्ण_अगर

	अगर (enable_ept && !is_unrestricted_guest(vcpu))
		ept_update_paging_mode_cr0(&hw_cr0, cr0, vcpu);

	vmcs_ग_लिखोl(CR0_READ_SHADOW, cr0);
	vmcs_ग_लिखोl(GUEST_CR0, hw_cr0);
	vcpu->arch.cr0 = cr0;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR0);

	/* depends on vcpu->arch.cr0 to be set to a new value */
	vmx->emulation_required = emulation_required(vcpu);
पूर्ण

अटल पूर्णांक vmx_get_max_tdp_level(व्योम)
अणु
	अगर (cpu_has_vmx_ept_5levels())
		वापस 5;
	वापस 4;
पूर्ण

u64 स्थिरruct_eptp(काष्ठा kvm_vcpu *vcpu, hpa_t root_hpa, पूर्णांक root_level)
अणु
	u64 eptp = VMX_EPTP_MT_WB;

	eptp |= (root_level == 5) ? VMX_EPTP_PWL_5 : VMX_EPTP_PWL_4;

	अगर (enable_ept_ad_bits &&
	    (!is_guest_mode(vcpu) || nested_ept_ad_enabled(vcpu)))
		eptp |= VMX_EPTP_AD_ENABLE_BIT;
	eptp |= root_hpa;

	वापस eptp;
पूर्ण

अटल व्योम vmx_load_mmu_pgd(काष्ठा kvm_vcpu *vcpu, hpa_t root_hpa,
			     पूर्णांक root_level)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	bool update_guest_cr3 = true;
	अचिन्हित दीर्घ guest_cr3;
	u64 eptp;

	अगर (enable_ept) अणु
		eptp = स्थिरruct_eptp(vcpu, root_hpa, root_level);
		vmcs_ग_लिखो64(EPT_POINTER, eptp);

		hv_track_root_ept(vcpu, root_hpa);

		अगर (!enable_unrestricted_guest && !is_paging(vcpu))
			guest_cr3 = to_kvm_vmx(kvm)->ept_identity_map_addr;
		अन्यथा अगर (test_bit(VCPU_EXREG_CR3, (uदीर्घ *)&vcpu->arch.regs_avail))
			guest_cr3 = vcpu->arch.cr3;
		अन्यथा /* vmcs01.GUEST_CR3 is alपढ़ोy up-to-date. */
			update_guest_cr3 = false;
		vmx_ept_load_pdptrs(vcpu);
	पूर्ण अन्यथा अणु
		guest_cr3 = root_hpa | kvm_get_active_pcid(vcpu);
	पूर्ण

	अगर (update_guest_cr3)
		vmcs_ग_लिखोl(GUEST_CR3, guest_cr3);
पूर्ण

अटल bool vmx_is_valid_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	/*
	 * We operate under the शेष treaपंचांगent of SMM, so VMX cannot be
	 * enabled under SMM.  Note, whether or not VMXE is allowed at all is
	 * handled by kvm_is_valid_cr4().
	 */
	अगर ((cr4 & X86_CR4_VMXE) && is_smm(vcpu))
		वापस false;

	अगर (to_vmx(vcpu)->nested.vmxon && !nested_cr4_valid(vcpu, cr4))
		वापस false;

	वापस true;
पूर्ण

व्योम vmx_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	अचिन्हित दीर्घ old_cr4 = vcpu->arch.cr4;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	/*
	 * Pass through host's Machine Check Enable value to hw_cr4, which
	 * is in क्रमce जबतक we are in guest mode.  Do not let guests control
	 * this bit, even अगर host CR4.MCE == 0.
	 */
	अचिन्हित दीर्घ hw_cr4;

	hw_cr4 = (cr4_पढ़ो_shaकरोw() & X86_CR4_MCE) | (cr4 & ~X86_CR4_MCE);
	अगर (is_unrestricted_guest(vcpu))
		hw_cr4 |= KVM_VM_CR4_ALWAYS_ON_UNRESTRICTED_GUEST;
	अन्यथा अगर (vmx->rmode.vm86_active)
		hw_cr4 |= KVM_RMODE_VM_CR4_ALWAYS_ON;
	अन्यथा
		hw_cr4 |= KVM_PMODE_VM_CR4_ALWAYS_ON;

	अगर (!boot_cpu_has(X86_FEATURE_UMIP) && vmx_umip_emulated()) अणु
		अगर (cr4 & X86_CR4_UMIP) अणु
			secondary_exec_controls_setbit(vmx, SECONDARY_EXEC_DESC);
			hw_cr4 &= ~X86_CR4_UMIP;
		पूर्ण अन्यथा अगर (!is_guest_mode(vcpu) ||
			!nested_cpu_has2(get_vmcs12(vcpu), SECONDARY_EXEC_DESC)) अणु
			secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_DESC);
		पूर्ण
	पूर्ण

	vcpu->arch.cr4 = cr4;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR4);

	अगर (!is_unrestricted_guest(vcpu)) अणु
		अगर (enable_ept) अणु
			अगर (!is_paging(vcpu)) अणु
				hw_cr4 &= ~X86_CR4_PAE;
				hw_cr4 |= X86_CR4_PSE;
			पूर्ण अन्यथा अगर (!(cr4 & X86_CR4_PAE)) अणु
				hw_cr4 &= ~X86_CR4_PAE;
			पूर्ण
		पूर्ण

		/*
		 * SMEP/SMAP/PKU is disabled अगर CPU is in non-paging mode in
		 * hardware.  To emulate this behavior, SMEP/SMAP/PKU needs
		 * to be manually disabled when guest चयनes to non-paging
		 * mode.
		 *
		 * If !enable_unrestricted_guest, the CPU is always running
		 * with CR0.PG=1 and CR4 needs to be modअगरied.
		 * If enable_unrestricted_guest, the CPU स्वतःmatically
		 * disables SMEP/SMAP/PKU when the guest sets CR0.PG=0.
		 */
		अगर (!is_paging(vcpu))
			hw_cr4 &= ~(X86_CR4_SMEP | X86_CR4_SMAP | X86_CR4_PKE);
	पूर्ण

	vmcs_ग_लिखोl(CR4_READ_SHADOW, cr4);
	vmcs_ग_लिखोl(GUEST_CR4, hw_cr4);

	अगर ((cr4 ^ old_cr4) & (X86_CR4_OSXSAVE | X86_CR4_PKE))
		kvm_update_cpuid_runसमय(vcpu);
पूर्ण

व्योम vmx_get_segment(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 ar;

	अगर (vmx->rmode.vm86_active && seg != VCPU_SREG_LDTR) अणु
		*var = vmx->rmode.segs[seg];
		अगर (seg == VCPU_SREG_TR
		    || var->selector == vmx_पढ़ो_guest_seg_selector(vmx, seg))
			वापस;
		var->base = vmx_पढ़ो_guest_seg_base(vmx, seg);
		var->selector = vmx_पढ़ो_guest_seg_selector(vmx, seg);
		वापस;
	पूर्ण
	var->base = vmx_पढ़ो_guest_seg_base(vmx, seg);
	var->limit = vmx_पढ़ो_guest_seg_limit(vmx, seg);
	var->selector = vmx_पढ़ो_guest_seg_selector(vmx, seg);
	ar = vmx_पढ़ो_guest_seg_ar(vmx, seg);
	var->unusable = (ar >> 16) & 1;
	var->type = ar & 15;
	var->s = (ar >> 4) & 1;
	var->dpl = (ar >> 5) & 3;
	/*
	 * Some userspaces करो not preserve unusable property. Since usable
	 * segment has to be present according to VMX spec we can use present
	 * property to amend userspace bug by making unusable segment always
	 * nonpresent. vmx_segment_access_rights() alपढ़ोy marks nonpresent
	 * segment as unusable.
	 */
	var->present = !var->unusable;
	var->avl = (ar >> 12) & 1;
	var->l = (ar >> 13) & 1;
	var->db = (ar >> 14) & 1;
	var->g = (ar >> 15) & 1;
पूर्ण

अटल u64 vmx_get_segment_base(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	काष्ठा kvm_segment s;

	अगर (to_vmx(vcpu)->rmode.vm86_active) अणु
		vmx_get_segment(vcpu, &s, seg);
		वापस s.base;
	पूर्ण
	वापस vmx_पढ़ो_guest_seg_base(to_vmx(vcpu), seg);
पूर्ण

पूर्णांक vmx_get_cpl(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (unlikely(vmx->rmode.vm86_active))
		वापस 0;
	अन्यथा अणु
		पूर्णांक ar = vmx_पढ़ो_guest_seg_ar(vmx, VCPU_SREG_SS);
		वापस VMX_AR_DPL(ar);
	पूर्ण
पूर्ण

अटल u32 vmx_segment_access_rights(काष्ठा kvm_segment *var)
अणु
	u32 ar;

	अगर (var->unusable || !var->present)
		ar = 1 << 16;
	अन्यथा अणु
		ar = var->type & 15;
		ar |= (var->s & 1) << 4;
		ar |= (var->dpl & 3) << 5;
		ar |= (var->present & 1) << 7;
		ar |= (var->avl & 1) << 12;
		ar |= (var->l & 1) << 13;
		ar |= (var->db & 1) << 14;
		ar |= (var->g & 1) << 15;
	पूर्ण

	वापस ar;
पूर्ण

व्योम vmx_set_segment(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	स्थिर काष्ठा kvm_vmx_segment_field *sf = &kvm_vmx_segment_fields[seg];

	vmx_segment_cache_clear(vmx);

	अगर (vmx->rmode.vm86_active && seg != VCPU_SREG_LDTR) अणु
		vmx->rmode.segs[seg] = *var;
		अगर (seg == VCPU_SREG_TR)
			vmcs_ग_लिखो16(sf->selector, var->selector);
		अन्यथा अगर (var->s)
			fix_rmode_seg(seg, &vmx->rmode.segs[seg]);
		जाओ out;
	पूर्ण

	vmcs_ग_लिखोl(sf->base, var->base);
	vmcs_ग_लिखो32(sf->limit, var->limit);
	vmcs_ग_लिखो16(sf->selector, var->selector);

	/*
	 *   Fix the "Accessed" bit in AR field of segment रेजिस्टरs क्रम older
	 * qemu binaries.
	 *   IA32 arch specअगरies that at the समय of processor reset the
	 * "Accessed" bit in the AR field of segment रेजिस्टरs is 1. And qemu
	 * is setting it to 0 in the userland code. This causes invalid guest
	 * state vmनिकास when "unrestricted guest" mode is turned on.
	 *    Fix क्रम this setup issue in cpu_reset is being pushed in the qemu
	 * tree. Newer qemu binaries with that qemu fix would not need this
	 * kvm hack.
	 */
	अगर (is_unrestricted_guest(vcpu) && (seg != VCPU_SREG_LDTR))
		var->type |= 0x1; /* Accessed */

	vmcs_ग_लिखो32(sf->ar_bytes, vmx_segment_access_rights(var));

out:
	vmx->emulation_required = emulation_required(vcpu);
पूर्ण

अटल व्योम vmx_get_cs_db_l_bits(काष्ठा kvm_vcpu *vcpu, पूर्णांक *db, पूर्णांक *l)
अणु
	u32 ar = vmx_पढ़ो_guest_seg_ar(to_vmx(vcpu), VCPU_SREG_CS);

	*db = (ar >> 14) & 1;
	*l = (ar >> 13) & 1;
पूर्ण

अटल व्योम vmx_get_idt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	dt->size = vmcs_पढ़ो32(GUEST_IDTR_LIMIT);
	dt->address = vmcs_पढ़ोl(GUEST_IDTR_BASE);
पूर्ण

अटल व्योम vmx_set_idt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	vmcs_ग_लिखो32(GUEST_IDTR_LIMIT, dt->size);
	vmcs_ग_लिखोl(GUEST_IDTR_BASE, dt->address);
पूर्ण

अटल व्योम vmx_get_gdt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	dt->size = vmcs_पढ़ो32(GUEST_GDTR_LIMIT);
	dt->address = vmcs_पढ़ोl(GUEST_GDTR_BASE);
पूर्ण

अटल व्योम vmx_set_gdt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	vmcs_ग_लिखो32(GUEST_GDTR_LIMIT, dt->size);
	vmcs_ग_लिखोl(GUEST_GDTR_BASE, dt->address);
पूर्ण

अटल bool rmode_segment_valid(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	काष्ठा kvm_segment var;
	u32 ar;

	vmx_get_segment(vcpu, &var, seg);
	var.dpl = 0x3;
	अगर (seg == VCPU_SREG_CS)
		var.type = 0x3;
	ar = vmx_segment_access_rights(&var);

	अगर (var.base != (var.selector << 4))
		वापस false;
	अगर (var.limit != 0xffff)
		वापस false;
	अगर (ar != 0xf3)
		वापस false;

	वापस true;
पूर्ण

अटल bool code_segment_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment cs;
	अचिन्हित पूर्णांक cs_rpl;

	vmx_get_segment(vcpu, &cs, VCPU_SREG_CS);
	cs_rpl = cs.selector & SEGMENT_RPL_MASK;

	अगर (cs.unusable)
		वापस false;
	अगर (~cs.type & (VMX_AR_TYPE_CODE_MASK|VMX_AR_TYPE_ACCESSES_MASK))
		वापस false;
	अगर (!cs.s)
		वापस false;
	अगर (cs.type & VMX_AR_TYPE_WRITEABLE_MASK) अणु
		अगर (cs.dpl > cs_rpl)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (cs.dpl != cs_rpl)
			वापस false;
	पूर्ण
	अगर (!cs.present)
		वापस false;

	/* TODO: Add Reserved field check, this'll require a new member in the kvm_segment_field काष्ठाure */
	वापस true;
पूर्ण

अटल bool stack_segment_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment ss;
	अचिन्हित पूर्णांक ss_rpl;

	vmx_get_segment(vcpu, &ss, VCPU_SREG_SS);
	ss_rpl = ss.selector & SEGMENT_RPL_MASK;

	अगर (ss.unusable)
		वापस true;
	अगर (ss.type != 3 && ss.type != 7)
		वापस false;
	अगर (!ss.s)
		वापस false;
	अगर (ss.dpl != ss_rpl) /* DPL != RPL */
		वापस false;
	अगर (!ss.present)
		वापस false;

	वापस true;
पूर्ण

अटल bool data_segment_valid(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	काष्ठा kvm_segment var;
	अचिन्हित पूर्णांक rpl;

	vmx_get_segment(vcpu, &var, seg);
	rpl = var.selector & SEGMENT_RPL_MASK;

	अगर (var.unusable)
		वापस true;
	अगर (!var.s)
		वापस false;
	अगर (!var.present)
		वापस false;
	अगर (~var.type & (VMX_AR_TYPE_CODE_MASK|VMX_AR_TYPE_WRITEABLE_MASK)) अणु
		अगर (var.dpl < rpl) /* DPL < RPL */
			वापस false;
	पूर्ण

	/* TODO: Add other members to kvm_segment_field to allow checking क्रम other access
	 * rights flags
	 */
	वापस true;
पूर्ण

अटल bool tr_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment tr;

	vmx_get_segment(vcpu, &tr, VCPU_SREG_TR);

	अगर (tr.unusable)
		वापस false;
	अगर (tr.selector & SEGMENT_TI_MASK)	/* TI = 1 */
		वापस false;
	अगर (tr.type != 3 && tr.type != 11) /* TODO: Check अगर guest is in IA32e mode */
		वापस false;
	अगर (!tr.present)
		वापस false;

	वापस true;
पूर्ण

अटल bool ldtr_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment ldtr;

	vmx_get_segment(vcpu, &ldtr, VCPU_SREG_LDTR);

	अगर (ldtr.unusable)
		वापस true;
	अगर (ldtr.selector & SEGMENT_TI_MASK)	/* TI = 1 */
		वापस false;
	अगर (ldtr.type != 2)
		वापस false;
	अगर (!ldtr.present)
		वापस false;

	वापस true;
पूर्ण

अटल bool cs_ss_rpl_check(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_segment cs, ss;

	vmx_get_segment(vcpu, &cs, VCPU_SREG_CS);
	vmx_get_segment(vcpu, &ss, VCPU_SREG_SS);

	वापस ((cs.selector & SEGMENT_RPL_MASK) ==
		 (ss.selector & SEGMENT_RPL_MASK));
पूर्ण

/*
 * Check अगर guest state is valid. Returns true अगर valid, false अगर
 * not.
 * We assume that रेजिस्टरs are always usable
 */
bool __vmx_guest_state_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	/* real mode guest state checks */
	अगर (!is_proपंचांगode(vcpu) || (vmx_get_rflags(vcpu) & X86_EFLAGS_VM)) अणु
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_CS))
			वापस false;
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_SS))
			वापस false;
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_DS))
			वापस false;
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_ES))
			वापस false;
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_FS))
			वापस false;
		अगर (!rmode_segment_valid(vcpu, VCPU_SREG_GS))
			वापस false;
	पूर्ण अन्यथा अणु
	/* रक्षित mode guest state checks */
		अगर (!cs_ss_rpl_check(vcpu))
			वापस false;
		अगर (!code_segment_valid(vcpu))
			वापस false;
		अगर (!stack_segment_valid(vcpu))
			वापस false;
		अगर (!data_segment_valid(vcpu, VCPU_SREG_DS))
			वापस false;
		अगर (!data_segment_valid(vcpu, VCPU_SREG_ES))
			वापस false;
		अगर (!data_segment_valid(vcpu, VCPU_SREG_FS))
			वापस false;
		अगर (!data_segment_valid(vcpu, VCPU_SREG_GS))
			वापस false;
		अगर (!tr_valid(vcpu))
			वापस false;
		अगर (!ldtr_valid(vcpu))
			वापस false;
	पूर्ण
	/* TODO:
	 * - Add checks on RIP
	 * - Add checks on RFLAGS
	 */

	वापस true;
पूर्ण

अटल पूर्णांक init_rmode_tss(काष्ठा kvm *kvm, व्योम __user *ua)
अणु
	स्थिर व्योम *zero_page = (स्थिर व्योम *) __va(page_to_phys(ZERO_PAGE(0)));
	u16 data;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (__copy_to_user(ua + PAGE_SIZE * i, zero_page, PAGE_SIZE))
			वापस -EFAULT;
	पूर्ण

	data = TSS_BASE_SIZE + TSS_REसूचीECTION_SIZE;
	अगर (__copy_to_user(ua + TSS_IOPB_BASE_OFFSET, &data, माप(u16)))
		वापस -EFAULT;

	data = ~0;
	अगर (__copy_to_user(ua + RMODE_TSS_SIZE - 1, &data, माप(u8)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक init_rmode_identity_map(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vmx *kvm_vmx = to_kvm_vmx(kvm);
	पूर्णांक i, r = 0;
	व्योम __user *uaddr;
	u32 पंचांगp;

	/* Protect kvm_vmx->ept_identity_pagetable_करोne. */
	mutex_lock(&kvm->slots_lock);

	अगर (likely(kvm_vmx->ept_identity_pagetable_करोne))
		जाओ out;

	अगर (!kvm_vmx->ept_identity_map_addr)
		kvm_vmx->ept_identity_map_addr = VMX_EPT_IDENTITY_PAGETABLE_ADDR;

	uaddr = __x86_set_memory_region(kvm,
					IDENTITY_PAGETABLE_PRIVATE_MEMSLOT,
					kvm_vmx->ept_identity_map_addr,
					PAGE_SIZE);
	अगर (IS_ERR(uaddr)) अणु
		r = PTR_ERR(uaddr);
		जाओ out;
	पूर्ण

	/* Set up identity-mapping pagetable क्रम EPT in real mode */
	क्रम (i = 0; i < PT32_ENT_PER_PAGE; i++) अणु
		पंचांगp = (i << 22) + (_PAGE_PRESENT | _PAGE_RW | _PAGE_USER |
			_PAGE_ACCESSED | _PAGE_सूचीTY | _PAGE_PSE);
		अगर (__copy_to_user(uaddr + i * माप(पंचांगp), &पंचांगp, माप(पंचांगp))) अणु
			r = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
	kvm_vmx->ept_identity_pagetable_करोne = true;

out:
	mutex_unlock(&kvm->slots_lock);
	वापस r;
पूर्ण

अटल व्योम seg_setup(पूर्णांक seg)
अणु
	स्थिर काष्ठा kvm_vmx_segment_field *sf = &kvm_vmx_segment_fields[seg];
	अचिन्हित पूर्णांक ar;

	vmcs_ग_लिखो16(sf->selector, 0);
	vmcs_ग_लिखोl(sf->base, 0);
	vmcs_ग_लिखो32(sf->limit, 0xffff);
	ar = 0x93;
	अगर (seg == VCPU_SREG_CS)
		ar |= 0x08; /* code segment */

	vmcs_ग_लिखो32(sf->ar_bytes, ar);
पूर्ण

अटल पूर्णांक alloc_apic_access_page(काष्ठा kvm *kvm)
अणु
	काष्ठा page *page;
	व्योम __user *hva;
	पूर्णांक ret = 0;

	mutex_lock(&kvm->slots_lock);
	अगर (kvm->arch.apic_access_page_करोne)
		जाओ out;
	hva = __x86_set_memory_region(kvm, APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
				      APIC_DEFAULT_PHYS_BASE, PAGE_SIZE);
	अगर (IS_ERR(hva)) अणु
		ret = PTR_ERR(hva);
		जाओ out;
	पूर्ण

	page = gfn_to_page(kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	अगर (is_error_page(page)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/*
	 * Do not pin the page in memory, so that memory hot-unplug
	 * is able to migrate it.
	 */
	put_page(page);
	kvm->arch.apic_access_page_करोne = true;
out:
	mutex_unlock(&kvm->slots_lock);
	वापस ret;
पूर्ण

पूर्णांक allocate_vpid(व्योम)
अणु
	पूर्णांक vpid;

	अगर (!enable_vpid)
		वापस 0;
	spin_lock(&vmx_vpid_lock);
	vpid = find_first_zero_bit(vmx_vpid_biपंचांगap, VMX_NR_VPIDS);
	अगर (vpid < VMX_NR_VPIDS)
		__set_bit(vpid, vmx_vpid_biपंचांगap);
	अन्यथा
		vpid = 0;
	spin_unlock(&vmx_vpid_lock);
	वापस vpid;
पूर्ण

व्योम मुक्त_vpid(पूर्णांक vpid)
अणु
	अगर (!enable_vpid || vpid == 0)
		वापस;
	spin_lock(&vmx_vpid_lock);
	__clear_bit(vpid, vmx_vpid_biपंचांगap);
	spin_unlock(&vmx_vpid_lock);
पूर्ण

अटल व्योम vmx_clear_msr_biपंचांगap_पढ़ो(uदीर्घ *msr_biपंचांगap, u32 msr)
अणु
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (msr <= 0x1fff)
		__clear_bit(msr, msr_biपंचांगap + 0x000 / f);
	अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff))
		__clear_bit(msr & 0x1fff, msr_biपंचांगap + 0x400 / f);
पूर्ण

अटल व्योम vmx_clear_msr_biपंचांगap_ग_लिखो(uदीर्घ *msr_biपंचांगap, u32 msr)
अणु
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (msr <= 0x1fff)
		__clear_bit(msr, msr_biपंचांगap + 0x800 / f);
	अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff))
		__clear_bit(msr & 0x1fff, msr_biपंचांगap + 0xc00 / f);
पूर्ण

अटल व्योम vmx_set_msr_biपंचांगap_पढ़ो(uदीर्घ *msr_biपंचांगap, u32 msr)
अणु
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (msr <= 0x1fff)
		__set_bit(msr, msr_biपंचांगap + 0x000 / f);
	अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff))
		__set_bit(msr & 0x1fff, msr_biपंचांगap + 0x400 / f);
पूर्ण

अटल व्योम vmx_set_msr_biपंचांगap_ग_लिखो(uदीर्घ *msr_biपंचांगap, u32 msr)
अणु
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (msr <= 0x1fff)
		__set_bit(msr, msr_biपंचांगap + 0x800 / f);
	अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff))
		__set_bit(msr & 0x1fff, msr_biपंचांगap + 0xc00 / f);
पूर्ण

व्योम vmx_disable_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, पूर्णांक type)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ *msr_biपंचांगap = vmx->vmcs01.msr_biपंचांगap;

	अगर (!cpu_has_vmx_msr_biपंचांगap())
		वापस;

	अगर (अटल_branch_unlikely(&enable_evmcs))
		evmcs_touch_msr_biपंचांगap();

	/*
	 * Mark the desired पूर्णांकercept state in shaकरोw biपंचांगap, this is needed
	 * क्रम resync when the MSR filters change.
	*/
	अगर (is_valid_passthrough_msr(msr)) अणु
		पूर्णांक idx = possible_passthrough_msr_slot(msr);

		अगर (idx != -ENOENT) अणु
			अगर (type & MSR_TYPE_R)
				clear_bit(idx, vmx->shaकरोw_msr_पूर्णांकercept.पढ़ो);
			अगर (type & MSR_TYPE_W)
				clear_bit(idx, vmx->shaकरोw_msr_पूर्णांकercept.ग_लिखो);
		पूर्ण
	पूर्ण

	अगर ((type & MSR_TYPE_R) &&
	    !kvm_msr_allowed(vcpu, msr, KVM_MSR_FILTER_READ)) अणु
		vmx_set_msr_biपंचांगap_पढ़ो(msr_biपंचांगap, msr);
		type &= ~MSR_TYPE_R;
	पूर्ण

	अगर ((type & MSR_TYPE_W) &&
	    !kvm_msr_allowed(vcpu, msr, KVM_MSR_FILTER_WRITE)) अणु
		vmx_set_msr_biपंचांगap_ग_लिखो(msr_biपंचांगap, msr);
		type &= ~MSR_TYPE_W;
	पूर्ण

	अगर (type & MSR_TYPE_R)
		vmx_clear_msr_biपंचांगap_पढ़ो(msr_biपंचांगap, msr);

	अगर (type & MSR_TYPE_W)
		vmx_clear_msr_biपंचांगap_ग_लिखो(msr_biपंचांगap, msr);
पूर्ण

व्योम vmx_enable_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, पूर्णांक type)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ *msr_biपंचांगap = vmx->vmcs01.msr_biपंचांगap;

	अगर (!cpu_has_vmx_msr_biपंचांगap())
		वापस;

	अगर (अटल_branch_unlikely(&enable_evmcs))
		evmcs_touch_msr_biपंचांगap();

	/*
	 * Mark the desired पूर्णांकercept state in shaकरोw biपंचांगap, this is needed
	 * क्रम resync when the MSR filter changes.
	*/
	अगर (is_valid_passthrough_msr(msr)) अणु
		पूर्णांक idx = possible_passthrough_msr_slot(msr);

		अगर (idx != -ENOENT) अणु
			अगर (type & MSR_TYPE_R)
				set_bit(idx, vmx->shaकरोw_msr_पूर्णांकercept.पढ़ो);
			अगर (type & MSR_TYPE_W)
				set_bit(idx, vmx->shaकरोw_msr_पूर्णांकercept.ग_लिखो);
		पूर्ण
	पूर्ण

	अगर (type & MSR_TYPE_R)
		vmx_set_msr_biपंचांगap_पढ़ो(msr_biपंचांगap, msr);

	अगर (type & MSR_TYPE_W)
		vmx_set_msr_biपंचांगap_ग_लिखो(msr_biपंचांगap, msr);
पूर्ण

अटल u8 vmx_msr_biपंचांगap_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	u8 mode = 0;

	अगर (cpu_has_secondary_exec_ctrls() &&
	    (secondary_exec_controls_get(to_vmx(vcpu)) &
	     SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE)) अणु
		mode |= MSR_BITMAP_MODE_X2APIC;
		अगर (enable_apicv && kvm_vcpu_apicv_active(vcpu))
			mode |= MSR_BITMAP_MODE_X2APIC_APICV;
	पूर्ण

	वापस mode;
पूर्ण

अटल व्योम vmx_reset_x2apic_msrs(काष्ठा kvm_vcpu *vcpu, u8 mode)
अणु
	अचिन्हित दीर्घ *msr_biपंचांगap = to_vmx(vcpu)->vmcs01.msr_biपंचांगap;
	अचिन्हित दीर्घ पढ़ो_पूर्णांकercept;
	पूर्णांक msr;

	पढ़ो_पूर्णांकercept = (mode & MSR_BITMAP_MODE_X2APIC_APICV) ? 0 : ~0;

	क्रम (msr = 0x800; msr <= 0x8ff; msr += BITS_PER_LONG) अणु
		अचिन्हित पूर्णांक पढ़ो_idx = msr / BITS_PER_LONG;
		अचिन्हित पूर्णांक ग_लिखो_idx = पढ़ो_idx + (0x800 / माप(दीर्घ));

		msr_biपंचांगap[पढ़ो_idx] = पढ़ो_पूर्णांकercept;
		msr_biपंचांगap[ग_लिखो_idx] = ~0ul;
	पूर्ण
पूर्ण

अटल व्योम vmx_update_msr_biपंचांगap_x2apic(काष्ठा kvm_vcpu *vcpu, u8 mode)
अणु
	अगर (!cpu_has_vmx_msr_biपंचांगap())
		वापस;

	vmx_reset_x2apic_msrs(vcpu, mode);

	/*
	 * TPR पढ़ोs and ग_लिखोs can be भवized even अगर भव पूर्णांकerrupt
	 * delivery is not in use.
	 */
	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, X2APIC_MSR(APIC_TASKPRI), MSR_TYPE_RW,
				  !(mode & MSR_BITMAP_MODE_X2APIC));

	अगर (mode & MSR_BITMAP_MODE_X2APIC_APICV) अणु
		vmx_enable_पूर्णांकercept_क्रम_msr(vcpu, X2APIC_MSR(APIC_TMCCT), MSR_TYPE_RW);
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, X2APIC_MSR(APIC_EOI), MSR_TYPE_W);
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, X2APIC_MSR(APIC_SELF_IPI), MSR_TYPE_W);
	पूर्ण
पूर्ण

व्योम vmx_update_msr_biपंचांगap(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u8 mode = vmx_msr_biपंचांगap_mode(vcpu);
	u8 changed = mode ^ vmx->msr_biपंचांगap_mode;

	अगर (!changed)
		वापस;

	अगर (changed & (MSR_BITMAP_MODE_X2APIC | MSR_BITMAP_MODE_X2APIC_APICV))
		vmx_update_msr_biपंचांगap_x2apic(vcpu, mode);

	vmx->msr_biपंचांगap_mode = mode;
पूर्ण

व्योम pt_update_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	bool flag = !(vmx->pt_desc.guest.ctl & RTIT_CTL_TRACEEN);
	u32 i;

	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_STATUS, MSR_TYPE_RW, flag);
	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_OUTPUT_BASE, MSR_TYPE_RW, flag);
	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_OUTPUT_MASK, MSR_TYPE_RW, flag);
	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_CR3_MATCH, MSR_TYPE_RW, flag);
	क्रम (i = 0; i < vmx->pt_desc.addr_range; i++) अणु
		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_ADDR0_A + i * 2, MSR_TYPE_RW, flag);
		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_RTIT_ADDR0_B + i * 2, MSR_TYPE_RW, flag);
	पूर्ण
पूर्ण

अटल bool vmx_guest_apic_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	व्योम *vapic_page;
	u32 vppr;
	पूर्णांक rvi;

	अगर (WARN_ON_ONCE(!is_guest_mode(vcpu)) ||
		!nested_cpu_has_vid(get_vmcs12(vcpu)) ||
		WARN_ON_ONCE(!vmx->nested.भव_apic_map.gfn))
		वापस false;

	rvi = vmx_get_rvi();

	vapic_page = vmx->nested.भव_apic_map.hva;
	vppr = *((u32 *)(vapic_page + APIC_PROCPRI));

	वापस ((rvi & 0xf0) > (vppr & 0xf0));
पूर्ण

अटल व्योम vmx_msr_filter_changed(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 i;

	/*
	 * Set पूर्णांकercept permissions क्रम all potentially passed through MSRs
	 * again. They will स्वतःmatically get filtered through the MSR filter,
	 * so we are back in sync after this.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(vmx_possible_passthrough_msrs); i++) अणु
		u32 msr = vmx_possible_passthrough_msrs[i];
		bool पढ़ो = test_bit(i, vmx->shaकरोw_msr_पूर्णांकercept.पढ़ो);
		bool ग_लिखो = test_bit(i, vmx->shaकरोw_msr_पूर्णांकercept.ग_लिखो);

		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, msr, MSR_TYPE_R, पढ़ो);
		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, msr, MSR_TYPE_W, ग_लिखो);
	पूर्ण

	pt_update_पूर्णांकercept_क्रम_msr(vcpu);
	vmx_update_msr_biपंचांगap_x2apic(vcpu, vmx_msr_biपंचांगap_mode(vcpu));
पूर्ण

अटल अंतरभूत bool kvm_vcpu_trigger_posted_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
						     bool nested)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक pi_vec = nested ? POSTED_INTR_NESTED_VECTOR : POSTED_INTR_VECTOR;

	अगर (vcpu->mode == IN_GUEST_MODE) अणु
		/*
		 * The vector of पूर्णांकerrupt to be delivered to vcpu had
		 * been set in PIR beक्रमe this function.
		 *
		 * Following हालs will be reached in this block, and
		 * we always send a notअगरication event in all हालs as
		 * explained below.
		 *
		 * Case 1: vcpu keeps in non-root mode. Sending a
		 * notअगरication event posts the पूर्णांकerrupt to vcpu.
		 *
		 * Case 2: vcpu निकासs to root mode and is still
		 * runnable. PIR will be synced to vIRR beक्रमe the
		 * next vcpu entry. Sending a notअगरication event in
		 * this हाल has no effect, as vcpu is not in root
		 * mode.
		 *
		 * Case 3: vcpu निकासs to root mode and is blocked.
		 * vcpu_block() has alपढ़ोy synced PIR to vIRR and
		 * never blocks vcpu अगर vIRR is not cleared. Thereक्रमe,
		 * a blocked vcpu here करोes not रुको क्रम any requested
		 * पूर्णांकerrupts in PIR, and sending a notअगरication event
		 * which has no effect is safe here.
		 */

		apic->send_IPI_mask(get_cpu_mask(vcpu->cpu), pi_vec);
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक vmx_deliver_nested_posted_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
						पूर्णांक vector)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (is_guest_mode(vcpu) &&
	    vector == vmx->nested.posted_पूर्णांकr_nv) अणु
		/*
		 * If a posted पूर्णांकr is not recognized by hardware,
		 * we will accomplish it in the next vmentry.
		 */
		vmx->nested.pi_pending = true;
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		/* the PIR and ON have been set by L1. */
		अगर (!kvm_vcpu_trigger_posted_पूर्णांकerrupt(vcpu, true))
			kvm_vcpu_kick(vcpu);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
/*
 * Send पूर्णांकerrupt to vcpu via posted पूर्णांकerrupt way.
 * 1. If target vcpu is running(non-root mode), send posted पूर्णांकerrupt
 * notअगरication to vcpu and hardware will sync PIR to vIRR atomically.
 * 2. If target vcpu isn't running(root mode), kick it to pick up the
 * पूर्णांकerrupt from PIR in next vmentry.
 */
अटल पूर्णांक vmx_deliver_posted_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक r;

	r = vmx_deliver_nested_posted_पूर्णांकerrupt(vcpu, vector);
	अगर (!r)
		वापस 0;

	अगर (!vcpu->arch.apicv_active)
		वापस -1;

	अगर (pi_test_and_set_pir(vector, &vmx->pi_desc))
		वापस 0;

	/* If a previous notअगरication has sent the IPI, nothing to करो.  */
	अगर (pi_test_and_set_on(&vmx->pi_desc))
		वापस 0;

	अगर (vcpu != kvm_get_running_vcpu() &&
	    !kvm_vcpu_trigger_posted_पूर्णांकerrupt(vcpu, false))
		kvm_vcpu_kick(vcpu);

	वापस 0;
पूर्ण

/*
 * Set up the vmcs's स्थिरant host-state fields, i.e., host-state fields that
 * will not change in the lअगरeसमय of the guest.
 * Note that host-state that करोes change is set अन्यथाwhere. E.g., host-state
 * that is set dअगरferently क्रम each CPU is set in vmx_vcpu_load(), not here.
 */
व्योम vmx_set_स्थिरant_host_state(काष्ठा vcpu_vmx *vmx)
अणु
	u32 low32, high32;
	अचिन्हित दीर्घ पंचांगpl;
	अचिन्हित दीर्घ cr0, cr3, cr4;

	cr0 = पढ़ो_cr0();
	WARN_ON(cr0 & X86_CR0_TS);
	vmcs_ग_लिखोl(HOST_CR0, cr0);  /* 22.2.3 */

	/*
	 * Save the most likely value क्रम this task's CR3 in the VMCS.
	 * We can't use __get_current_cr3_fast() because we're not atomic.
	 */
	cr3 = __पढ़ो_cr3();
	vmcs_ग_लिखोl(HOST_CR3, cr3);		/* 22.2.3  FIXME: shaकरोw tables */
	vmx->loaded_vmcs->host_state.cr3 = cr3;

	/* Save the most likely value क्रम this task's CR4 in the VMCS. */
	cr4 = cr4_पढ़ो_shaकरोw();
	vmcs_ग_लिखोl(HOST_CR4, cr4);			/* 22.2.3, 22.2.5 */
	vmx->loaded_vmcs->host_state.cr4 = cr4;

	vmcs_ग_लिखो16(HOST_CS_SELECTOR, __KERNEL_CS);  /* 22.2.4 */
#अगर_घोषित CONFIG_X86_64
	/*
	 * Load null selectors, so we can aव्योम reloading them in
	 * vmx_prepare_चयन_to_host(), in हाल userspace uses
	 * the null selectors too (the expected हाल).
	 */
	vmcs_ग_लिखो16(HOST_DS_SELECTOR, 0);
	vmcs_ग_लिखो16(HOST_ES_SELECTOR, 0);
#अन्यथा
	vmcs_ग_लिखो16(HOST_DS_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
	vmcs_ग_लिखो16(HOST_ES_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
#पूर्ण_अगर
	vmcs_ग_लिखो16(HOST_SS_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
	vmcs_ग_लिखो16(HOST_TR_SELECTOR, GDT_ENTRY_TSS*8);  /* 22.2.4 */

	vmcs_ग_लिखोl(HOST_IDTR_BASE, host_idt_base);   /* 22.2.4 */

	vmcs_ग_लिखोl(HOST_RIP, (अचिन्हित दीर्घ)vmx_vmनिकास); /* 22.2.5 */

	rdmsr(MSR_IA32_SYSENTER_CS, low32, high32);
	vmcs_ग_लिखो32(HOST_IA32_SYSENTER_CS, low32);
	rdmsrl(MSR_IA32_SYSENTER_EIP, पंचांगpl);
	vmcs_ग_लिखोl(HOST_IA32_SYSENTER_EIP, पंचांगpl);   /* 22.2.3 */

	अगर (vmcs_config.vmनिकास_ctrl & VM_EXIT_LOAD_IA32_PAT) अणु
		rdmsr(MSR_IA32_CR_PAT, low32, high32);
		vmcs_ग_लिखो64(HOST_IA32_PAT, low32 | ((u64) high32 << 32));
	पूर्ण

	अगर (cpu_has_load_ia32_efer())
		vmcs_ग_लिखो64(HOST_IA32_EFER, host_efer);
पूर्ण

व्योम set_cr4_guest_host_mask(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा kvm_vcpu *vcpu = &vmx->vcpu;

	vcpu->arch.cr4_guest_owned_bits = KVM_POSSIBLE_CR4_GUEST_BITS &
					  ~vcpu->arch.cr4_guest_rsvd_bits;
	अगर (!enable_ept)
		vcpu->arch.cr4_guest_owned_bits &= ~X86_CR4_PGE;
	अगर (is_guest_mode(&vmx->vcpu))
		vcpu->arch.cr4_guest_owned_bits &=
			~get_vmcs12(vcpu)->cr4_guest_host_mask;
	vmcs_ग_लिखोl(CR4_GUEST_HOST_MASK, ~vcpu->arch.cr4_guest_owned_bits);
पूर्ण

u32 vmx_pin_based_exec_ctrl(काष्ठा vcpu_vmx *vmx)
अणु
	u32 pin_based_exec_ctrl = vmcs_config.pin_based_exec_ctrl;

	अगर (!kvm_vcpu_apicv_active(&vmx->vcpu))
		pin_based_exec_ctrl &= ~PIN_BASED_POSTED_INTR;

	अगर (!enable_vnmi)
		pin_based_exec_ctrl &= ~PIN_BASED_VIRTUAL_NMIS;

	अगर (!enable_preemption_समयr)
		pin_based_exec_ctrl &= ~PIN_BASED_VMX_PREEMPTION_TIMER;

	वापस pin_based_exec_ctrl;
पूर्ण

अटल व्योम vmx_refresh_apicv_exec_ctrl(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	pin_controls_set(vmx, vmx_pin_based_exec_ctrl(vmx));
	अगर (cpu_has_secondary_exec_ctrls()) अणु
		अगर (kvm_vcpu_apicv_active(vcpu))
			secondary_exec_controls_setbit(vmx,
				      SECONDARY_EXEC_APIC_REGISTER_VIRT |
				      SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
		अन्यथा
			secondary_exec_controls_clearbit(vmx,
					SECONDARY_EXEC_APIC_REGISTER_VIRT |
					SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
	पूर्ण

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmx_update_msr_biपंचांगap(vcpu);
पूर्ण

u32 vmx_exec_control(काष्ठा vcpu_vmx *vmx)
अणु
	u32 exec_control = vmcs_config.cpu_based_exec_ctrl;

	अगर (vmx->vcpu.arch.चयन_db_regs & KVM_DEBUGREG_WONT_EXIT)
		exec_control &= ~CPU_BASED_MOV_DR_EXITING;

	अगर (!cpu_need_tpr_shaकरोw(&vmx->vcpu)) अणु
		exec_control &= ~CPU_BASED_TPR_SHADOW;
#अगर_घोषित CONFIG_X86_64
		exec_control |= CPU_BASED_CR8_STORE_EXITING |
				CPU_BASED_CR8_LOAD_EXITING;
#पूर्ण_अगर
	पूर्ण
	अगर (!enable_ept)
		exec_control |= CPU_BASED_CR3_STORE_EXITING |
				CPU_BASED_CR3_LOAD_EXITING  |
				CPU_BASED_INVLPG_EXITING;
	अगर (kvm_mरुको_in_guest(vmx->vcpu.kvm))
		exec_control &= ~(CPU_BASED_MWAIT_EXITING |
				CPU_BASED_MONITOR_EXITING);
	अगर (kvm_hlt_in_guest(vmx->vcpu.kvm))
		exec_control &= ~CPU_BASED_HLT_EXITING;
	वापस exec_control;
पूर्ण

/*
 * Adjust a single secondary execution control bit to पूर्णांकercept/allow an
 * inकाष्ठाion in the guest.  This is usually करोne based on whether or not a
 * feature has been exposed to the guest in order to correctly emulate faults.
 */
अटल अंतरभूत व्योम
vmx_adjust_secondary_exec_control(काष्ठा vcpu_vmx *vmx, u32 *exec_control,
				  u32 control, bool enabled, bool निकासing)
अणु
	/*
	 * If the control is क्रम an opt-in feature, clear the control अगर the
	 * feature is not exposed to the guest, i.e. not enabled.  If the
	 * control is opt-out, i.e. an निकासing control, clear the control अगर
	 * the feature _is_ exposed to the guest, i.e. निकासing/पूर्णांकerception is
	 * disabled क्रम the associated inकाष्ठाion.  Note, the caller is
	 * responsible presetting exec_control to set all supported bits.
	 */
	अगर (enabled == निकासing)
		*exec_control &= ~control;

	/*
	 * Update the nested MSR settings so that a nested VMM can/can't set
	 * controls क्रम features that are/aren't exposed to the guest.
	 */
	अगर (nested) अणु
		अगर (enabled)
			vmx->nested.msrs.secondary_ctls_high |= control;
		अन्यथा
			vmx->nested.msrs.secondary_ctls_high &= ~control;
	पूर्ण
पूर्ण

/*
 * Wrapper macro क्रम the common हाल of adjusting a secondary execution control
 * based on a single guest CPUID bit, with a dedicated feature bit.  This also
 * verअगरies that the control is actually supported by KVM and hardware.
 */
#घोषणा vmx_adjust_sec_exec_control(vmx, exec_control, name, feat_name, ctrl_name, निकासing) \
(अणु									 \
	bool __enabled;							 \
									 \
	अगर (cpu_has_vmx_##name()) अणु					 \
		__enabled = guest_cpuid_has(&(vmx)->vcpu,		 \
					    X86_FEATURE_##feat_name);	 \
		vmx_adjust_secondary_exec_control(vmx, exec_control,	 \
			SECONDARY_EXEC_##ctrl_name, __enabled, निकासing); \
	पूर्ण								 \
पूर्ण)

/* More macro magic क्रम ENABLE_/opt-in versus _EXITING/opt-out controls. */
#घोषणा vmx_adjust_sec_exec_feature(vmx, exec_control, lname, uname) \
	vmx_adjust_sec_exec_control(vmx, exec_control, lname, uname, ENABLE_##uname, false)

#घोषणा vmx_adjust_sec_exec_निकासing(vmx, exec_control, lname, uname) \
	vmx_adjust_sec_exec_control(vmx, exec_control, lname, uname, uname##_EXITING, true)

अटल व्योम vmx_compute_secondary_exec_control(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा kvm_vcpu *vcpu = &vmx->vcpu;

	u32 exec_control = vmcs_config.cpu_based_2nd_exec_ctrl;

	अगर (vmx_pt_mode_is_प्रणाली())
		exec_control &= ~(SECONDARY_EXEC_PT_USE_GPA | SECONDARY_EXEC_PT_CONCEAL_VMX);
	अगर (!cpu_need_भवize_apic_accesses(vcpu))
		exec_control &= ~SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
	अगर (vmx->vpid == 0)
		exec_control &= ~SECONDARY_EXEC_ENABLE_VPID;
	अगर (!enable_ept) अणु
		exec_control &= ~SECONDARY_EXEC_ENABLE_EPT;
		enable_unrestricted_guest = 0;
	पूर्ण
	अगर (!enable_unrestricted_guest)
		exec_control &= ~SECONDARY_EXEC_UNRESTRICTED_GUEST;
	अगर (kvm_छोड़ो_in_guest(vmx->vcpu.kvm))
		exec_control &= ~SECONDARY_EXEC_PAUSE_LOOP_EXITING;
	अगर (!kvm_vcpu_apicv_active(vcpu))
		exec_control &= ~(SECONDARY_EXEC_APIC_REGISTER_VIRT |
				  SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
	exec_control &= ~SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE;

	/* SECONDARY_EXEC_DESC is enabled/disabled on ग_लिखोs to CR4.UMIP,
	 * in vmx_set_cr4.  */
	exec_control &= ~SECONDARY_EXEC_DESC;

	/* SECONDARY_EXEC_SHADOW_VMCS is enabled when L1 executes VMPTRLD
	   (handle_vmptrld).
	   We can NOT enable shaकरोw_vmcs here because we करोn't have yet
	   a current VMCS12
	*/
	exec_control &= ~SECONDARY_EXEC_SHADOW_VMCS;

	/*
	 * PML is enabled/disabled when dirty logging of memsmlots changes, but
	 * it needs to be set here when dirty logging is alपढ़ोy active, e.g.
	 * अगर this vCPU was created after dirty logging was enabled.
	 */
	अगर (!vcpu->kvm->arch.cpu_dirty_logging_count)
		exec_control &= ~SECONDARY_EXEC_ENABLE_PML;

	अगर (cpu_has_vmx_xsaves()) अणु
		/* Exposing XSAVES only when XSAVE is exposed */
		bool xsaves_enabled =
			boot_cpu_has(X86_FEATURE_XSAVE) &&
			guest_cpuid_has(vcpu, X86_FEATURE_XSAVE) &&
			guest_cpuid_has(vcpu, X86_FEATURE_XSAVES);

		vcpu->arch.xsaves_enabled = xsaves_enabled;

		vmx_adjust_secondary_exec_control(vmx, &exec_control,
						  SECONDARY_EXEC_XSAVES,
						  xsaves_enabled, false);
	पूर्ण

	/*
	 * RDPID is also gated by ENABLE_RDTSCP, turn on the control अगर either
	 * feature is exposed to the guest.  This creates a भवization hole
	 * अगर both are supported in hardware but only one is exposed to the
	 * guest, but letting the guest execute RDTSCP or RDPID when either one
	 * is advertised is preferable to emulating the advertised inकाष्ठाion
	 * in KVM on #UD, and obviously better than incorrectly injecting #UD.
	 */
	अगर (cpu_has_vmx_rdtscp()) अणु
		bool rdpid_or_rdtscp_enabled =
			guest_cpuid_has(vcpu, X86_FEATURE_RDTSCP) ||
			guest_cpuid_has(vcpu, X86_FEATURE_RDPID);

		vmx_adjust_secondary_exec_control(vmx, &exec_control,
						  SECONDARY_EXEC_ENABLE_RDTSCP,
						  rdpid_or_rdtscp_enabled, false);
	पूर्ण
	vmx_adjust_sec_exec_feature(vmx, &exec_control, invpcid, INVPCID);

	vmx_adjust_sec_exec_निकासing(vmx, &exec_control, rdअक्रम, RDRAND);
	vmx_adjust_sec_exec_निकासing(vmx, &exec_control, rdseed, RDSEED);

	vmx_adjust_sec_exec_control(vmx, &exec_control, रुकोpkg, WAITPKG,
				    ENABLE_USR_WAIT_PAUSE, false);

	अगर (!vcpu->kvm->arch.bus_lock_detection_enabled)
		exec_control &= ~SECONDARY_EXEC_BUS_LOCK_DETECTION;

	vmx->secondary_exec_control = exec_control;
पूर्ण

#घोषणा VMX_XSS_EXIT_BITMAP 0

/*
 * Noting that the initialization of Guest-state Area of VMCS is in
 * vmx_vcpu_reset().
 */
अटल व्योम init_vmcs(काष्ठा vcpu_vmx *vmx)
अणु
	अगर (nested)
		nested_vmx_set_vmcs_shaकरोwing_biपंचांगap();

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmcs_ग_लिखो64(MSR_BITMAP, __pa(vmx->vmcs01.msr_biपंचांगap));

	vmcs_ग_लिखो64(VMCS_LINK_POINTER, -1ull); /* 22.3.1.5 */

	/* Control */
	pin_controls_set(vmx, vmx_pin_based_exec_ctrl(vmx));

	exec_controls_set(vmx, vmx_exec_control(vmx));

	अगर (cpu_has_secondary_exec_ctrls()) अणु
		vmx_compute_secondary_exec_control(vmx);
		secondary_exec_controls_set(vmx, vmx->secondary_exec_control);
	पूर्ण

	अगर (kvm_vcpu_apicv_active(&vmx->vcpu)) अणु
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP0, 0);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP1, 0);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP2, 0);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP3, 0);

		vmcs_ग_लिखो16(GUEST_INTR_STATUS, 0);

		vmcs_ग_लिखो16(POSTED_INTR_NV, POSTED_INTR_VECTOR);
		vmcs_ग_लिखो64(POSTED_INTR_DESC_ADDR, __pa((&vmx->pi_desc)));
	पूर्ण

	अगर (!kvm_छोड़ो_in_guest(vmx->vcpu.kvm)) अणु
		vmcs_ग_लिखो32(PLE_GAP, ple_gap);
		vmx->ple_winकरोw = ple_winकरोw;
		vmx->ple_winकरोw_dirty = true;
	पूर्ण

	vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MASK, 0);
	vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MATCH, 0);
	vmcs_ग_लिखो32(CR3_TARGET_COUNT, 0);           /* 22.2.1 */

	vmcs_ग_लिखो16(HOST_FS_SELECTOR, 0);            /* 22.2.4 */
	vmcs_ग_लिखो16(HOST_GS_SELECTOR, 0);            /* 22.2.4 */
	vmx_set_स्थिरant_host_state(vmx);
	vmcs_ग_लिखोl(HOST_FS_BASE, 0); /* 22.2.4 */
	vmcs_ग_लिखोl(HOST_GS_BASE, 0); /* 22.2.4 */

	अगर (cpu_has_vmx_vmfunc())
		vmcs_ग_लिखो64(VM_FUNCTION_CONTROL, 0);

	vmcs_ग_लिखो32(VM_EXIT_MSR_STORE_COUNT, 0);
	vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, 0);
	vmcs_ग_लिखो64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_स्वतःload.host.val));
	vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, 0);
	vmcs_ग_लिखो64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_स्वतःload.guest.val));

	अगर (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT)
		vmcs_ग_लिखो64(GUEST_IA32_PAT, vmx->vcpu.arch.pat);

	vm_निकास_controls_set(vmx, vmx_vmनिकास_ctrl());

	/* 22.2.1, 20.8.1 */
	vm_entry_controls_set(vmx, vmx_vmentry_ctrl());

	vmx->vcpu.arch.cr0_guest_owned_bits = KVM_POSSIBLE_CR0_GUEST_BITS;
	vmcs_ग_लिखोl(CR0_GUEST_HOST_MASK, ~vmx->vcpu.arch.cr0_guest_owned_bits);

	set_cr4_guest_host_mask(vmx);

	अगर (vmx->vpid != 0)
		vmcs_ग_लिखो16(VIRTUAL_PROCESSOR_ID, vmx->vpid);

	अगर (cpu_has_vmx_xsaves())
		vmcs_ग_लिखो64(XSS_EXIT_BITMAP, VMX_XSS_EXIT_BITMAP);

	अगर (enable_pml) अणु
		vmcs_ग_लिखो64(PML_ADDRESS, page_to_phys(vmx->pml_pg));
		vmcs_ग_लिखो16(GUEST_PML_INDEX, PML_ENTITY_NUM - 1);
	पूर्ण

	vmx_ग_लिखो_encls_biपंचांगap(&vmx->vcpu, शून्य);

	अगर (vmx_pt_mode_is_host_guest()) अणु
		स_रखो(&vmx->pt_desc, 0, माप(vmx->pt_desc));
		/* Bit[6~0] are क्रमced to 1, ग_लिखोs are ignored. */
		vmx->pt_desc.guest.output_mask = 0x7F;
		vmcs_ग_लिखो64(GUEST_IA32_RTIT_CTL, 0);
	पूर्ण
पूर्ण

अटल व्योम vmx_vcpu_reset(काष्ठा kvm_vcpu *vcpu, bool init_event)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा msr_data apic_base_msr;
	u64 cr0;

	vmx->rmode.vm86_active = 0;
	vmx->spec_ctrl = 0;

	vmx->msr_ia32_umरुको_control = 0;

	vmx->vcpu.arch.regs[VCPU_REGS_RDX] = get_rdx_init_val();
	vmx->hv_deadline_tsc = -1;
	kvm_set_cr8(vcpu, 0);

	अगर (!init_event) अणु
		apic_base_msr.data = APIC_DEFAULT_PHYS_BASE |
				     MSR_IA32_APICBASE_ENABLE;
		अगर (kvm_vcpu_is_reset_bsp(vcpu))
			apic_base_msr.data |= MSR_IA32_APICBASE_BSP;
		apic_base_msr.host_initiated = true;
		kvm_set_apic_base(vcpu, &apic_base_msr);
	पूर्ण

	vmx_segment_cache_clear(vmx);

	seg_setup(VCPU_SREG_CS);
	vmcs_ग_लिखो16(GUEST_CS_SELECTOR, 0xf000);
	vmcs_ग_लिखोl(GUEST_CS_BASE, 0xffff0000ul);

	seg_setup(VCPU_SREG_DS);
	seg_setup(VCPU_SREG_ES);
	seg_setup(VCPU_SREG_FS);
	seg_setup(VCPU_SREG_GS);
	seg_setup(VCPU_SREG_SS);

	vmcs_ग_लिखो16(GUEST_TR_SELECTOR, 0);
	vmcs_ग_लिखोl(GUEST_TR_BASE, 0);
	vmcs_ग_लिखो32(GUEST_TR_LIMIT, 0xffff);
	vmcs_ग_लिखो32(GUEST_TR_AR_BYTES, 0x008b);

	vmcs_ग_लिखो16(GUEST_LDTR_SELECTOR, 0);
	vmcs_ग_लिखोl(GUEST_LDTR_BASE, 0);
	vmcs_ग_लिखो32(GUEST_LDTR_LIMIT, 0xffff);
	vmcs_ग_लिखो32(GUEST_LDTR_AR_BYTES, 0x00082);

	अगर (!init_event) अणु
		vmcs_ग_लिखो32(GUEST_SYSENTER_CS, 0);
		vmcs_ग_लिखोl(GUEST_SYSENTER_ESP, 0);
		vmcs_ग_लिखोl(GUEST_SYSENTER_EIP, 0);
		vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, 0);
	पूर्ण

	kvm_set_rflags(vcpu, X86_EFLAGS_FIXED);
	kvm_rip_ग_लिखो(vcpu, 0xfff0);

	vmcs_ग_लिखोl(GUEST_GDTR_BASE, 0);
	vmcs_ग_लिखो32(GUEST_GDTR_LIMIT, 0xffff);

	vmcs_ग_लिखोl(GUEST_IDTR_BASE, 0);
	vmcs_ग_लिखो32(GUEST_IDTR_LIMIT, 0xffff);

	vmcs_ग_लिखो32(GUEST_ACTIVITY_STATE, GUEST_ACTIVITY_ACTIVE);
	vmcs_ग_लिखो32(GUEST_INTERRUPTIBILITY_INFO, 0);
	vmcs_ग_लिखोl(GUEST_PENDING_DBG_EXCEPTIONS, 0);
	अगर (kvm_mpx_supported())
		vmcs_ग_लिखो64(GUEST_BNDCFGS, 0);

	setup_msrs(vmx);

	vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD, 0);  /* 22.2.1 */

	अगर (cpu_has_vmx_tpr_shaकरोw() && !init_event) अणु
		vmcs_ग_लिखो64(VIRTUAL_APIC_PAGE_ADDR, 0);
		अगर (cpu_need_tpr_shaकरोw(vcpu))
			vmcs_ग_लिखो64(VIRTUAL_APIC_PAGE_ADDR,
				     __pa(vcpu->arch.apic->regs));
		vmcs_ग_लिखो32(TPR_THRESHOLD, 0);
	पूर्ण

	kvm_make_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu);

	cr0 = X86_CR0_NW | X86_CR0_CD | X86_CR0_ET;
	vmx->vcpu.arch.cr0 = cr0;
	vmx_set_cr0(vcpu, cr0); /* enter rmode */
	vmx_set_cr4(vcpu, 0);
	vmx_set_efer(vcpu, 0);

	vmx_update_exception_biपंचांगap(vcpu);

	vpid_sync_context(vmx->vpid);
	अगर (init_event)
		vmx_clear_hlt(vcpu);
पूर्ण

अटल व्योम vmx_enable_irq_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	exec_controls_setbit(to_vmx(vcpu), CPU_BASED_INTR_WINDOW_EXITING);
पूर्ण

अटल व्योम vmx_enable_nmi_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!enable_vnmi ||
	    vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO) & GUEST_INTR_STATE_STI) अणु
		vmx_enable_irq_winकरोw(vcpu);
		वापस;
	पूर्ण

	exec_controls_setbit(to_vmx(vcpu), CPU_BASED_NMI_WINDOW_EXITING);
पूर्ण

अटल व्योम vmx_inject_irq(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	uपूर्णांक32_t पूर्णांकr;
	पूर्णांक irq = vcpu->arch.पूर्णांकerrupt.nr;

	trace_kvm_inj_virq(irq);

	++vcpu->stat.irq_injections;
	अगर (vmx->rmode.vm86_active) अणु
		पूर्णांक inc_eip = 0;
		अगर (vcpu->arch.पूर्णांकerrupt.soft)
			inc_eip = vcpu->arch.event_निकास_inst_len;
		kvm_inject_realmode_पूर्णांकerrupt(vcpu, irq, inc_eip);
		वापस;
	पूर्ण
	पूर्णांकr = irq | INTR_INFO_VALID_MASK;
	अगर (vcpu->arch.पूर्णांकerrupt.soft) अणु
		पूर्णांकr |= INTR_TYPE_SOFT_INTR;
		vmcs_ग_लिखो32(VM_ENTRY_INSTRUCTION_LEN,
			     vmx->vcpu.arch.event_निकास_inst_len);
	पूर्ण अन्यथा
		पूर्णांकr |= INTR_TYPE_EXT_INTR;
	vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD, पूर्णांकr);

	vmx_clear_hlt(vcpu);
पूर्ण

अटल व्योम vmx_inject_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!enable_vnmi) अणु
		/*
		 * Tracking the NMI-blocked state in software is built upon
		 * finding the next खोलो IRQ winकरोw. This, in turn, depends on
		 * well-behaving guests: They have to keep IRQs disabled at
		 * least as दीर्घ as the NMI handler runs. Otherwise we may
		 * cause NMI nesting, maybe अवरोधing the guest. But as this is
		 * highly unlikely, we can live with the residual risk.
		 */
		vmx->loaded_vmcs->soft_vnmi_blocked = 1;
		vmx->loaded_vmcs->vnmi_blocked_समय = 0;
	पूर्ण

	++vcpu->stat.nmi_injections;
	vmx->loaded_vmcs->nmi_known_unmasked = false;

	अगर (vmx->rmode.vm86_active) अणु
		kvm_inject_realmode_पूर्णांकerrupt(vcpu, NMI_VECTOR, 0);
		वापस;
	पूर्ण

	vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD,
			INTR_TYPE_NMI_INTR | INTR_INFO_VALID_MASK | NMI_VECTOR);

	vmx_clear_hlt(vcpu);
पूर्ण

bool vmx_get_nmi_mask(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	bool masked;

	अगर (!enable_vnmi)
		वापस vmx->loaded_vmcs->soft_vnmi_blocked;
	अगर (vmx->loaded_vmcs->nmi_known_unmasked)
		वापस false;
	masked = vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO) & GUEST_INTR_STATE_NMI;
	vmx->loaded_vmcs->nmi_known_unmasked = !masked;
	वापस masked;
पूर्ण

व्योम vmx_set_nmi_mask(काष्ठा kvm_vcpu *vcpu, bool masked)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!enable_vnmi) अणु
		अगर (vmx->loaded_vmcs->soft_vnmi_blocked != masked) अणु
			vmx->loaded_vmcs->soft_vnmi_blocked = masked;
			vmx->loaded_vmcs->vnmi_blocked_समय = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		vmx->loaded_vmcs->nmi_known_unmasked = !masked;
		अगर (masked)
			vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO,
				      GUEST_INTR_STATE_NMI);
		अन्यथा
			vmcs_clear_bits(GUEST_INTERRUPTIBILITY_INFO,
					GUEST_INTR_STATE_NMI);
	पूर्ण
पूर्ण

bool vmx_nmi_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_guest_mode(vcpu) && nested_निकास_on_nmi(vcpu))
		वापस false;

	अगर (!enable_vnmi && to_vmx(vcpu)->loaded_vmcs->soft_vnmi_blocked)
		वापस true;

	वापस (vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO) &
		(GUEST_INTR_STATE_MOV_SS | GUEST_INTR_STATE_STI |
		 GUEST_INTR_STATE_NMI));
पूर्ण

अटल पूर्णांक vmx_nmi_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	अगर (to_vmx(vcpu)->nested.nested_run_pending)
		वापस -EBUSY;

	/* An NMI must not be injected पूर्णांकo L2 अगर it's supposed to VM-Exit.  */
	अगर (क्रम_injection && is_guest_mode(vcpu) && nested_निकास_on_nmi(vcpu))
		वापस -EBUSY;

	वापस !vmx_nmi_blocked(vcpu);
पूर्ण

bool vmx_पूर्णांकerrupt_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_guest_mode(vcpu) && nested_निकास_on_पूर्णांकr(vcpu))
		वापस false;

	वापस !(vmx_get_rflags(vcpu) & X86_EFLAGS_IF) ||
	       (vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO) &
		(GUEST_INTR_STATE_STI | GUEST_INTR_STATE_MOV_SS));
पूर्ण

अटल पूर्णांक vmx_पूर्णांकerrupt_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	अगर (to_vmx(vcpu)->nested.nested_run_pending)
		वापस -EBUSY;

       /*
        * An IRQ must not be injected पूर्णांकo L2 अगर it's supposed to VM-Exit,
        * e.g. अगर the IRQ arrived asynchronously after checking nested events.
        */
	अगर (क्रम_injection && is_guest_mode(vcpu) && nested_निकास_on_पूर्णांकr(vcpu))
		वापस -EBUSY;

	वापस !vmx_पूर्णांकerrupt_blocked(vcpu);
पूर्ण

अटल पूर्णांक vmx_set_tss_addr(काष्ठा kvm *kvm, अचिन्हित पूर्णांक addr)
अणु
	व्योम __user *ret;

	अगर (enable_unrestricted_guest)
		वापस 0;

	mutex_lock(&kvm->slots_lock);
	ret = __x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, addr,
				      PAGE_SIZE * 3);
	mutex_unlock(&kvm->slots_lock);

	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	to_kvm_vmx(kvm)->tss_addr = addr;

	वापस init_rmode_tss(kvm, ret);
पूर्ण

अटल पूर्णांक vmx_set_identity_map_addr(काष्ठा kvm *kvm, u64 ident_addr)
अणु
	to_kvm_vmx(kvm)->ept_identity_map_addr = ident_addr;
	वापस 0;
पूर्ण

अटल bool rmode_exception(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec)
अणु
	चयन (vec) अणु
	हाल BP_VECTOR:
		/*
		 * Update inकाष्ठाion length as we may reinject the exception
		 * from user space जबतक in guest debugging mode.
		 */
		to_vmx(vcpu)->vcpu.arch.event_निकास_inst_len =
			vmcs_पढ़ो32(VM_EXIT_INSTRUCTION_LEN);
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			वापस false;
		fallthrough;
	हाल DB_VECTOR:
		वापस !(vcpu->guest_debug &
			(KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP));
	हाल DE_VECTOR:
	हाल OF_VECTOR:
	हाल BR_VECTOR:
	हाल UD_VECTOR:
	हाल DF_VECTOR:
	हाल SS_VECTOR:
	हाल GP_VECTOR:
	हाल MF_VECTOR:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक handle_rmode_exception(काष्ठा kvm_vcpu *vcpu,
				  पूर्णांक vec, u32 err_code)
अणु
	/*
	 * Inकाष्ठाion with address size override prefix opcode 0x67
	 * Cause the #SS fault with 0 error code in VM86 mode.
	 */
	अगर (((vec == GP_VECTOR) || (vec == SS_VECTOR)) && err_code == 0) अणु
		अगर (kvm_emulate_inकाष्ठाion(vcpu, 0)) अणु
			अगर (vcpu->arch.halt_request) अणु
				vcpu->arch.halt_request = 0;
				वापस kvm_vcpu_halt(vcpu);
			पूर्ण
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Forward all other exceptions that are valid in real mode.
	 * FIXME: Breaks guest debugging in real mode, needs to be fixed with
	 *        the required debugging infraकाष्ठाure rework.
	 */
	kvm_queue_exception(vcpu, vec);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_machine_check(काष्ठा kvm_vcpu *vcpu)
अणु
	/* handled by vmx_vcpu_run() */
	वापस 1;
पूर्ण

/*
 * If the host has split lock detection disabled, then #AC is
 * unconditionally injected पूर्णांकo the guest, which is the pre split lock
 * detection behaviour.
 *
 * If the host has split lock detection enabled then #AC is
 * only injected पूर्णांकo the guest when:
 *  - Guest CPL == 3 (user mode)
 *  - Guest has #AC detection enabled in CR0
 *  - Guest EFLAGS has AC bit set
 */
अटल अंतरभूत bool guest_inject_ac(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_SPLIT_LOCK_DETECT))
		वापस true;

	वापस vmx_get_cpl(vcpu) == 3 && kvm_पढ़ो_cr0_bits(vcpu, X86_CR0_AM) &&
	       (kvm_get_rflags(vcpu) & X86_EFLAGS_AC);
पूर्ण

अटल पूर्णांक handle_exception_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा kvm_run *kvm_run = vcpu->run;
	u32 पूर्णांकr_info, ex_no, error_code;
	अचिन्हित दीर्घ cr2, dr6;
	u32 vect_info;

	vect_info = vmx->idt_vectoring_info;
	पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);

	अगर (is_machine_check(पूर्णांकr_info) || is_nmi(पूर्णांकr_info))
		वापस 1; /* handled by handle_exception_nmi_irqoff() */

	अगर (is_invalid_opcode(पूर्णांकr_info))
		वापस handle_ud(vcpu);

	error_code = 0;
	अगर (पूर्णांकr_info & INTR_INFO_DELIVER_CODE_MASK)
		error_code = vmcs_पढ़ो32(VM_EXIT_INTR_ERROR_CODE);

	अगर (!vmx->rmode.vm86_active && is_gp_fault(पूर्णांकr_info)) अणु
		WARN_ON_ONCE(!enable_vmware_backकरोor);

		/*
		 * VMware backकरोor emulation on #GP पूर्णांकerception only handles
		 * INअणुSपूर्ण, OUTअणुSपूर्ण, and RDPMC, none of which generate a non-zero
		 * error code on #GP.
		 */
		अगर (error_code) अणु
			kvm_queue_exception_e(vcpu, GP_VECTOR, error_code);
			वापस 1;
		पूर्ण
		वापस kvm_emulate_inकाष्ठाion(vcpu, EMULTYPE_VMWARE_GP);
	पूर्ण

	/*
	 * The #PF with PFEC.RSVD = 1 indicates the guest is accessing
	 * MMIO, it is better to report an पूर्णांकernal error.
	 * See the comments in vmx_handle_निकास.
	 */
	अगर ((vect_info & VECTORING_INFO_VALID_MASK) &&
	    !(is_page_fault(पूर्णांकr_info) && !(error_code & PFERR_RSVD_MASK))) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_SIMUL_EX;
		vcpu->run->पूर्णांकernal.ndata = 4;
		vcpu->run->पूर्णांकernal.data[0] = vect_info;
		vcpu->run->पूर्णांकernal.data[1] = पूर्णांकr_info;
		vcpu->run->पूर्णांकernal.data[2] = error_code;
		vcpu->run->पूर्णांकernal.data[3] = vcpu->arch.last_vmentry_cpu;
		वापस 0;
	पूर्ण

	अगर (is_page_fault(पूर्णांकr_info)) अणु
		cr2 = vmx_get_निकास_qual(vcpu);
		अगर (enable_ept && !vcpu->arch.apf.host_apf_flags) अणु
			/*
			 * EPT will cause page fault only अगर we need to
			 * detect illegal GPAs.
			 */
			WARN_ON_ONCE(!allow_smaller_maxphyaddr);
			kvm_fixup_and_inject_pf_error(vcpu, cr2, error_code);
			वापस 1;
		पूर्ण अन्यथा
			वापस kvm_handle_page_fault(vcpu, error_code, cr2, शून्य, 0);
	पूर्ण

	ex_no = पूर्णांकr_info & INTR_INFO_VECTOR_MASK;

	अगर (vmx->rmode.vm86_active && rmode_exception(vcpu, ex_no))
		वापस handle_rmode_exception(vcpu, ex_no, error_code);

	चयन (ex_no) अणु
	हाल DB_VECTOR:
		dr6 = vmx_get_निकास_qual(vcpu);
		अगर (!(vcpu->guest_debug &
		      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))) अणु
			अगर (is_icebp(पूर्णांकr_info))
				WARN_ON(!skip_emulated_inकाष्ठाion(vcpu));

			kvm_queue_exception_p(vcpu, DB_VECTOR, dr6);
			वापस 1;
		पूर्ण
		kvm_run->debug.arch.dr6 = dr6 | DR6_ACTIVE_LOW;
		kvm_run->debug.arch.dr7 = vmcs_पढ़ोl(GUEST_DR7);
		fallthrough;
	हाल BP_VECTOR:
		/*
		 * Update inकाष्ठाion length as we may reinject #BP from
		 * user space जबतक in guest debugging mode. Reading it क्रम
		 * #DB as well causes no harm, it is not used in that हाल.
		 */
		vmx->vcpu.arch.event_निकास_inst_len =
			vmcs_पढ़ो32(VM_EXIT_INSTRUCTION_LEN);
		kvm_run->निकास_reason = KVM_EXIT_DEBUG;
		kvm_run->debug.arch.pc = kvm_get_linear_rip(vcpu);
		kvm_run->debug.arch.exception = ex_no;
		अवरोध;
	हाल AC_VECTOR:
		अगर (guest_inject_ac(vcpu)) अणु
			kvm_queue_exception_e(vcpu, AC_VECTOR, error_code);
			वापस 1;
		पूर्ण

		/*
		 * Handle split lock. Depending on detection mode this will
		 * either warn and disable split lock detection क्रम this
		 * task or क्रमce SIGBUS on it.
		 */
		अगर (handle_guest_split_lock(kvm_rip_पढ़ो(vcpu)))
			वापस 1;
		fallthrough;
	शेष:
		kvm_run->निकास_reason = KVM_EXIT_EXCEPTION;
		kvm_run->ex.exception = ex_no;
		kvm_run->ex.error_code = error_code;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक handle_बाह्यal_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	++vcpu->stat.irq_निकासs;
	वापस 1;
पूर्ण

अटल पूर्णांक handle_triple_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_SHUTDOWN;
	vcpu->mmio_needed = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_io(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication;
	पूर्णांक size, in, string;
	अचिन्हित port;

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	string = (निकास_qualअगरication & 16) != 0;

	++vcpu->stat.io_निकासs;

	अगर (string)
		वापस kvm_emulate_inकाष्ठाion(vcpu, 0);

	port = निकास_qualअगरication >> 16;
	size = (निकास_qualअगरication & 7) + 1;
	in = (निकास_qualअगरication & 8) != 0;

	वापस kvm_fast_pio(vcpu, size, port, in);
पूर्ण

अटल व्योम
vmx_patch_hypercall(काष्ठा kvm_vcpu *vcpu, अचिन्हित अक्षर *hypercall)
अणु
	/*
	 * Patch in the VMCALL inकाष्ठाion:
	 */
	hypercall[0] = 0x0f;
	hypercall[1] = 0x01;
	hypercall[2] = 0xc1;
पूर्ण

/* called to set cr0 as appropriate क्रम a mov-to-cr0 निकास. */
अटल पूर्णांक handle_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	अगर (is_guest_mode(vcpu)) अणु
		काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
		अचिन्हित दीर्घ orig_val = val;

		/*
		 * We get here when L2 changed cr0 in a way that did not change
		 * any of L1's shaकरोwed bits (see nested_vmx_निकास_handled_cr),
		 * but did change L0 shaकरोwed bits. So we first calculate the
		 * effective cr0 value that L1 would like to ग_लिखो पूर्णांकo the
		 * hardware. It consists of the L2-owned bits from the new
		 * value combined with the L1-owned bits from L1's guest_cr0.
		 */
		val = (val & ~vmcs12->cr0_guest_host_mask) |
			(vmcs12->guest_cr0 & vmcs12->cr0_guest_host_mask);

		अगर (!nested_guest_cr0_valid(vcpu, val))
			वापस 1;

		अगर (kvm_set_cr0(vcpu, val))
			वापस 1;
		vmcs_ग_लिखोl(CR0_READ_SHADOW, orig_val);
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (to_vmx(vcpu)->nested.vmxon &&
		    !nested_host_cr0_valid(vcpu, val))
			वापस 1;

		वापस kvm_set_cr0(vcpu, val);
	पूर्ण
पूर्ण

अटल पूर्णांक handle_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	अगर (is_guest_mode(vcpu)) अणु
		काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
		अचिन्हित दीर्घ orig_val = val;

		/* analogously to handle_set_cr0 */
		val = (val & ~vmcs12->cr4_guest_host_mask) |
			(vmcs12->guest_cr4 & vmcs12->cr4_guest_host_mask);
		अगर (kvm_set_cr4(vcpu, val))
			वापस 1;
		vmcs_ग_लिखोl(CR4_READ_SHADOW, orig_val);
		वापस 0;
	पूर्ण अन्यथा
		वापस kvm_set_cr4(vcpu, val);
पूर्ण

अटल पूर्णांक handle_desc(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON(!(vcpu->arch.cr4 & X86_CR4_UMIP));
	वापस kvm_emulate_inकाष्ठाion(vcpu, 0);
पूर्ण

अटल पूर्णांक handle_cr(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication, val;
	पूर्णांक cr;
	पूर्णांक reg;
	पूर्णांक err;
	पूर्णांक ret;

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	cr = निकास_qualअगरication & 15;
	reg = (निकास_qualअगरication >> 8) & 15;
	चयन ((निकास_qualअगरication >> 4) & 3) अणु
	हाल 0: /* mov to cr */
		val = kvm_रेजिस्टर_पढ़ो(vcpu, reg);
		trace_kvm_cr_ग_लिखो(cr, val);
		चयन (cr) अणु
		हाल 0:
			err = handle_set_cr0(vcpu, val);
			वापस kvm_complete_insn_gp(vcpu, err);
		हाल 3:
			WARN_ON_ONCE(enable_unrestricted_guest);
			err = kvm_set_cr3(vcpu, val);
			वापस kvm_complete_insn_gp(vcpu, err);
		हाल 4:
			err = handle_set_cr4(vcpu, val);
			वापस kvm_complete_insn_gp(vcpu, err);
		हाल 8: अणु
				u8 cr8_prev = kvm_get_cr8(vcpu);
				u8 cr8 = (u8)val;
				err = kvm_set_cr8(vcpu, cr8);
				ret = kvm_complete_insn_gp(vcpu, err);
				अगर (lapic_in_kernel(vcpu))
					वापस ret;
				अगर (cr8_prev <= cr8)
					वापस ret;
				/*
				 * TODO: we might be squashing a
				 * KVM_GUESTDBG_SINGLESTEP-triggered
				 * KVM_EXIT_DEBUG here.
				 */
				vcpu->run->निकास_reason = KVM_EXIT_SET_TPR;
				वापस 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2: /* clts */
		WARN_ONCE(1, "Guest should always own CR0.TS");
		vmx_set_cr0(vcpu, kvm_पढ़ो_cr0_bits(vcpu, ~X86_CR0_TS));
		trace_kvm_cr_ग_लिखो(0, kvm_पढ़ो_cr0(vcpu));
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	हाल 1: /*mov from cr*/
		चयन (cr) अणु
		हाल 3:
			WARN_ON_ONCE(enable_unrestricted_guest);
			val = kvm_पढ़ो_cr3(vcpu);
			kvm_रेजिस्टर_ग_लिखो(vcpu, reg, val);
			trace_kvm_cr_पढ़ो(cr, val);
			वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
		हाल 8:
			val = kvm_get_cr8(vcpu);
			kvm_रेजिस्टर_ग_लिखो(vcpu, reg, val);
			trace_kvm_cr_पढ़ो(cr, val);
			वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
		पूर्ण
		अवरोध;
	हाल 3: /* lmsw */
		val = (निकास_qualअगरication >> LMSW_SOURCE_DATA_SHIFT) & 0x0f;
		trace_kvm_cr_ग_लिखो(0, (kvm_पढ़ो_cr0(vcpu) & ~0xful) | val);
		kvm_lmsw(vcpu, val);

		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	शेष:
		अवरोध;
	पूर्ण
	vcpu->run->निकास_reason = 0;
	vcpu_unimpl(vcpu, "unhandled control register: op %d cr %d\n",
	       (पूर्णांक)(निकास_qualअगरication >> 4) & 3, cr);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_dr(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication;
	पूर्णांक dr, dr7, reg;
	पूर्णांक err = 1;

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	dr = निकास_qualअगरication & DEBUG_REG_ACCESS_NUM;

	/* First, अगर DR करोes not exist, trigger UD */
	अगर (!kvm_require_dr(vcpu, dr))
		वापस 1;

	अगर (kvm_x86_ops.get_cpl(vcpu) > 0)
		जाओ out;

	dr7 = vmcs_पढ़ोl(GUEST_DR7);
	अगर (dr7 & DR7_GD) अणु
		/*
		 * As the vm-निकास takes precedence over the debug trap, we
		 * need to emulate the latter, either क्रम the host or the
		 * guest debugging itself.
		 */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP) अणु
			vcpu->run->debug.arch.dr6 = DR6_BD | DR6_ACTIVE_LOW;
			vcpu->run->debug.arch.dr7 = dr7;
			vcpu->run->debug.arch.pc = kvm_get_linear_rip(vcpu);
			vcpu->run->debug.arch.exception = DB_VECTOR;
			vcpu->run->निकास_reason = KVM_EXIT_DEBUG;
			वापस 0;
		पूर्ण अन्यथा अणु
			kvm_queue_exception_p(vcpu, DB_VECTOR, DR6_BD);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (vcpu->guest_debug == 0) अणु
		exec_controls_clearbit(to_vmx(vcpu), CPU_BASED_MOV_DR_EXITING);

		/*
		 * No more DR vmनिकासs; क्रमce a reload of the debug रेजिस्टरs
		 * and reenter on this inकाष्ठाion.  The next vmनिकास will
		 * retrieve the full state of the debug रेजिस्टरs.
		 */
		vcpu->arch.चयन_db_regs |= KVM_DEBUGREG_WONT_EXIT;
		वापस 1;
	पूर्ण

	reg = DEBUG_REG_ACCESS_REG(निकास_qualअगरication);
	अगर (निकास_qualअगरication & TYPE_MOV_FROM_DR) अणु
		अचिन्हित दीर्घ val;

		kvm_get_dr(vcpu, dr, &val);
		kvm_रेजिस्टर_ग_लिखो(vcpu, reg, val);
		err = 0;
	पूर्ण अन्यथा अणु
		err = kvm_set_dr(vcpu, dr, kvm_रेजिस्टर_पढ़ो(vcpu, reg));
	पूर्ण

out:
	वापस kvm_complete_insn_gp(vcpu, err);
पूर्ण

अटल व्योम vmx_sync_dirty_debug_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	get_debugreg(vcpu->arch.db[0], 0);
	get_debugreg(vcpu->arch.db[1], 1);
	get_debugreg(vcpu->arch.db[2], 2);
	get_debugreg(vcpu->arch.db[3], 3);
	get_debugreg(vcpu->arch.dr6, 6);
	vcpu->arch.dr7 = vmcs_पढ़ोl(GUEST_DR7);

	vcpu->arch.चयन_db_regs &= ~KVM_DEBUGREG_WONT_EXIT;
	exec_controls_setbit(to_vmx(vcpu), CPU_BASED_MOV_DR_EXITING);
पूर्ण

अटल व्योम vmx_set_dr7(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	vmcs_ग_लिखोl(GUEST_DR7, val);
पूर्ण

अटल पूर्णांक handle_tpr_below_threshold(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_apic_update_ppr(vcpu);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_पूर्णांकerrupt_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	exec_controls_clearbit(to_vmx(vcpu), CPU_BASED_INTR_WINDOW_EXITING);

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	++vcpu->stat.irq_winकरोw_निकासs;
	वापस 1;
पूर्ण

अटल पूर्णांक handle_invlpg(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);

	kvm_mmu_invlpg(vcpu, निकास_qualअगरication);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक handle_apic_access(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (likely(fasteoi)) अणु
		अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
		पूर्णांक access_type, offset;

		access_type = निकास_qualअगरication & APIC_ACCESS_TYPE;
		offset = निकास_qualअगरication & APIC_ACCESS_OFFSET;
		/*
		 * Sane guest uses MOV to ग_लिखो EOI, with written value
		 * not cared. So make a लघु-circuit here by aव्योमing
		 * heavy inकाष्ठाion emulation.
		 */
		अगर ((access_type == TYPE_LINEAR_APIC_INST_WRITE) &&
		    (offset == APIC_EOI)) अणु
			kvm_lapic_set_eoi(vcpu);
			वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
		पूर्ण
	पूर्ण
	वापस kvm_emulate_inकाष्ठाion(vcpu, 0);
पूर्ण

अटल पूर्णांक handle_apic_eoi_induced(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	पूर्णांक vector = निकास_qualअगरication & 0xff;

	/* EOI-induced VM निकास is trap-like and thus no need to adjust IP */
	kvm_apic_set_eoi_accelerated(vcpu, vector);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_apic_ग_लिखो(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	u32 offset = निकास_qualअगरication & 0xfff;

	/* APIC-ग_लिखो VM निकास is trap-like and thus no need to adjust IP */
	kvm_apic_ग_लिखो_nodecode(vcpu, offset);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_task_चयन(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ निकास_qualअगरication;
	bool has_error_code = false;
	u32 error_code = 0;
	u16 tss_selector;
	पूर्णांक reason, type, idt_v, idt_index;

	idt_v = (vmx->idt_vectoring_info & VECTORING_INFO_VALID_MASK);
	idt_index = (vmx->idt_vectoring_info & VECTORING_INFO_VECTOR_MASK);
	type = (vmx->idt_vectoring_info & VECTORING_INFO_TYPE_MASK);

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);

	reason = (u32)निकास_qualअगरication >> 30;
	अगर (reason == TASK_SWITCH_GATE && idt_v) अणु
		चयन (type) अणु
		हाल INTR_TYPE_NMI_INTR:
			vcpu->arch.nmi_injected = false;
			vmx_set_nmi_mask(vcpu, true);
			अवरोध;
		हाल INTR_TYPE_EXT_INTR:
		हाल INTR_TYPE_SOFT_INTR:
			kvm_clear_पूर्णांकerrupt_queue(vcpu);
			अवरोध;
		हाल INTR_TYPE_HARD_EXCEPTION:
			अगर (vmx->idt_vectoring_info &
			    VECTORING_INFO_DELIVER_CODE_MASK) अणु
				has_error_code = true;
				error_code =
					vmcs_पढ़ो32(IDT_VECTORING_ERROR_CODE);
			पूर्ण
			fallthrough;
		हाल INTR_TYPE_SOFT_EXCEPTION:
			kvm_clear_exception_queue(vcpu);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	tss_selector = निकास_qualअगरication;

	अगर (!idt_v || (type != INTR_TYPE_HARD_EXCEPTION &&
		       type != INTR_TYPE_EXT_INTR &&
		       type != INTR_TYPE_NMI_INTR))
		WARN_ON(!skip_emulated_inकाष्ठाion(vcpu));

	/*
	 * TODO: What about debug traps on tss चयन?
	 *       Are we supposed to inject them and update dr6?
	 */
	वापस kvm_task_चयन(vcpu, tss_selector,
			       type == INTR_TYPE_SOFT_INTR ? idt_index : -1,
			       reason, has_error_code, error_code);
पूर्ण

अटल पूर्णांक handle_ept_violation(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication;
	gpa_t gpa;
	u64 error_code;

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);

	/*
	 * EPT violation happened जबतक executing iret from NMI,
	 * "blocked by NMI" bit has to be set beक्रमe next VM entry.
	 * There are errata that may cause this bit to not be set:
	 * AAK134, BY25.
	 */
	अगर (!(to_vmx(vcpu)->idt_vectoring_info & VECTORING_INFO_VALID_MASK) &&
			enable_vnmi &&
			(निकास_qualअगरication & INTR_INFO_UNBLOCK_NMI))
		vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO, GUEST_INTR_STATE_NMI);

	gpa = vmcs_पढ़ो64(GUEST_PHYSICAL_ADDRESS);
	trace_kvm_page_fault(gpa, निकास_qualअगरication);

	/* Is it a पढ़ो fault? */
	error_code = (निकास_qualअगरication & EPT_VIOLATION_ACC_READ)
		     ? PFERR_USER_MASK : 0;
	/* Is it a ग_लिखो fault? */
	error_code |= (निकास_qualअगरication & EPT_VIOLATION_ACC_WRITE)
		      ? PFERR_WRITE_MASK : 0;
	/* Is it a fetch fault? */
	error_code |= (निकास_qualअगरication & EPT_VIOLATION_ACC_INSTR)
		      ? PFERR_FETCH_MASK : 0;
	/* ept page table entry is present? */
	error_code |= (निकास_qualअगरication &
		       (EPT_VIOLATION_READABLE | EPT_VIOLATION_WRITABLE |
			EPT_VIOLATION_EXECUTABLE))
		      ? PFERR_PRESENT_MASK : 0;

	error_code |= (निकास_qualअगरication & EPT_VIOLATION_GVA_TRANSLATED) != 0 ?
	       PFERR_GUEST_FINAL_MASK : PFERR_GUEST_PAGE_MASK;

	vcpu->arch.निकास_qualअगरication = निकास_qualअगरication;

	/*
	 * Check that the GPA करोesn't exceed physical memory limits, as that is
	 * a guest page fault.  We have to emulate the inकाष्ठाion here, because
	 * अगर the illegal address is that of a paging काष्ठाure, then
	 * EPT_VIOLATION_ACC_WRITE bit is set.  Alternatively, अगर supported we
	 * would also use advanced VM-निकास inक्रमmation क्रम EPT violations to
	 * reस्थिरruct the page fault error code.
	 */
	अगर (unlikely(allow_smaller_maxphyaddr && kvm_vcpu_is_illegal_gpa(vcpu, gpa)))
		वापस kvm_emulate_inकाष्ठाion(vcpu, 0);

	वापस kvm_mmu_page_fault(vcpu, gpa, error_code, शून्य, 0);
पूर्ण

अटल पूर्णांक handle_ept_misconfig(काष्ठा kvm_vcpu *vcpu)
अणु
	gpa_t gpa;

	अगर (!vmx_can_emulate_inकाष्ठाion(vcpu, शून्य, 0))
		वापस 1;

	/*
	 * A nested guest cannot optimize MMIO vmनिकासs, because we have an
	 * nGPA here instead of the required GPA.
	 */
	gpa = vmcs_पढ़ो64(GUEST_PHYSICAL_ADDRESS);
	अगर (!is_guest_mode(vcpu) &&
	    !kvm_io_bus_ग_लिखो(vcpu, KVM_FAST_MMIO_BUS, gpa, 0, शून्य)) अणु
		trace_kvm_fast_mmio(gpa);
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	पूर्ण

	वापस kvm_mmu_page_fault(vcpu, gpa, PFERR_RSVD_MASK, शून्य, 0);
पूर्ण

अटल पूर्णांक handle_nmi_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON_ONCE(!enable_vnmi);
	exec_controls_clearbit(to_vmx(vcpu), CPU_BASED_NMI_WINDOW_EXITING);
	++vcpu->stat.nmi_winकरोw_निकासs;
	kvm_make_request(KVM_REQ_EVENT, vcpu);

	वापस 1;
पूर्ण

अटल पूर्णांक handle_invalid_guest_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	bool पूर्णांकr_winकरोw_requested;
	अचिन्हित count = 130;

	पूर्णांकr_winकरोw_requested = exec_controls_get(vmx) &
				CPU_BASED_INTR_WINDOW_EXITING;

	जबतक (vmx->emulation_required && count-- != 0) अणु
		अगर (पूर्णांकr_winकरोw_requested && !vmx_पूर्णांकerrupt_blocked(vcpu))
			वापस handle_पूर्णांकerrupt_winकरोw(&vmx->vcpu);

		अगर (kvm_test_request(KVM_REQ_EVENT, vcpu))
			वापस 1;

		अगर (!kvm_emulate_inकाष्ठाion(vcpu, 0))
			वापस 0;

		अगर (vmx->emulation_required && !vmx->rmode.vm86_active &&
		    vcpu->arch.exception.pending) अणु
			vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			vcpu->run->पूर्णांकernal.suberror =
						KVM_INTERNAL_ERROR_EMULATION;
			vcpu->run->पूर्णांकernal.ndata = 0;
			वापस 0;
		पूर्ण

		अगर (vcpu->arch.halt_request) अणु
			vcpu->arch.halt_request = 0;
			वापस kvm_vcpu_halt(vcpu);
		पूर्ण

		/*
		 * Note, वापस 1 and not 0, vcpu_run() will invoke
		 * xfer_to_guest_mode() which will create a proper वापस
		 * code.
		 */
		अगर (__xfer_to_guest_mode_work_pending())
			वापस 1;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम grow_ple_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित पूर्णांक old = vmx->ple_winकरोw;

	vmx->ple_winकरोw = __grow_ple_winकरोw(old, ple_winकरोw,
					    ple_winकरोw_grow,
					    ple_winकरोw_max);

	अगर (vmx->ple_winकरोw != old) अणु
		vmx->ple_winकरोw_dirty = true;
		trace_kvm_ple_winकरोw_update(vcpu->vcpu_id,
					    vmx->ple_winकरोw, old);
	पूर्ण
पूर्ण

अटल व्योम shrink_ple_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित पूर्णांक old = vmx->ple_winकरोw;

	vmx->ple_winकरोw = __shrink_ple_winकरोw(old, ple_winकरोw,
					      ple_winकरोw_shrink,
					      ple_winकरोw);

	अगर (vmx->ple_winकरोw != old) अणु
		vmx->ple_winकरोw_dirty = true;
		trace_kvm_ple_winकरोw_update(vcpu->vcpu_id,
					    vmx->ple_winकरोw, old);
	पूर्ण
पूर्ण

/*
 * Indicate a busy-रुकोing vcpu in spinlock. We करो not enable the PAUSE
 * निकासing, so only get here on cpu with PAUSE-Loop-Exiting.
 */
अटल पूर्णांक handle_छोड़ो(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_छोड़ो_in_guest(vcpu->kvm))
		grow_ple_winकरोw(vcpu);

	/*
	 * Intel sdm vol3 ch-25.1.3 says: The "PAUSE-loop exiting"
	 * VM-execution control is ignored अगर CPL > 0. OTOH, KVM
	 * never set PAUSE_EXITING and just set PLE अगर supported,
	 * so the vcpu must be CPL=0 अगर it माला_लो a PAUSE निकास.
	 */
	kvm_vcpu_on_spin(vcpu, true);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक handle_monitor_trap(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक handle_invpcid(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 vmx_inकाष्ठाion_info;
	अचिन्हित दीर्घ type;
	gva_t gva;
	काष्ठा अणु
		u64 pcid;
		u64 gla;
	पूर्ण opeअक्रम;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_INVPCID)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	vmx_inकाष्ठाion_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	type = kvm_रेजिस्टर_पढ़ो(vcpu, (vmx_inकाष्ठाion_info >> 28) & 0xf);

	अगर (type > 3) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	/* According to the Intel inकाष्ठाion reference, the memory opeअक्रम
	 * is पढ़ो even अगर it isn't needed (e.g., क्रम type==all)
	 */
	अगर (get_vmx_mem_address(vcpu, vmx_get_निकास_qual(vcpu),
				vmx_inकाष्ठाion_info, false,
				माप(opeअक्रम), &gva))
		वापस 1;

	वापस kvm_handle_invpcid(vcpu, type, gva);
पूर्ण

अटल पूर्णांक handle_pml_full(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication;

	trace_kvm_pml_full(vcpu->vcpu_id);

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);

	/*
	 * PML buffer FULL happened जबतक executing iret from NMI,
	 * "blocked by NMI" bit has to be set beक्रमe next VM entry.
	 */
	अगर (!(to_vmx(vcpu)->idt_vectoring_info & VECTORING_INFO_VALID_MASK) &&
			enable_vnmi &&
			(निकास_qualअगरication & INTR_INFO_UNBLOCK_NMI))
		vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO,
				GUEST_INTR_STATE_NMI);

	/*
	 * PML buffer alपढ़ोy flushed at beginning of VMEXIT. Nothing to करो
	 * here.., and there's no userspace involvement needed क्रम PML.
	 */
	वापस 1;
पूर्ण

अटल fastpath_t handle_fastpath_preemption_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!vmx->req_immediate_निकास &&
	    !unlikely(vmx->loaded_vmcs->hv_समयr_soft_disabled)) अणु
		kvm_lapic_expired_hv_समयr(vcpu);
		वापस EXIT_FASTPATH_REENTER_GUEST;
	पूर्ण

	वापस EXIT_FASTPATH_NONE;
पूर्ण

अटल पूर्णांक handle_preemption_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	handle_fastpath_preemption_समयr(vcpu);
	वापस 1;
पूर्ण

/*
 * When nested=0, all VMX inकाष्ठाion VM Exits filter here.  The handlers
 * are overwritten by nested_vmx_setup() when nested=1.
 */
अटल पूर्णांक handle_vmx_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_queue_exception(vcpu, UD_VECTOR);
	वापस 1;
पूर्ण

#अगर_अघोषित CONFIG_X86_SGX_KVM
अटल पूर्णांक handle_encls(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * SGX भवization is disabled.  There is no software enable bit क्रम
	 * SGX, so KVM पूर्णांकercepts all ENCLS leafs and injects a #UD to prevent
	 * the guest from executing ENCLS (when SGX is supported by hardware).
	 */
	kvm_queue_exception(vcpu, UD_VECTOR);
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_SGX_KVM */

अटल पूर्णांक handle_bus_lock_vmनिकास(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_X86_BUS_LOCK;
	vcpu->run->flags |= KVM_RUN_X86_BUS_LOCK;
	वापस 0;
पूर्ण

/*
 * The निकास handlers वापस 1 अगर the निकास was handled fully and guest execution
 * may resume.  Otherwise they set the kvm_run parameter to indicate what needs
 * to be करोne to userspace and वापस 0.
 */
अटल पूर्णांक (*kvm_vmx_निकास_handlers[])(काष्ठा kvm_vcpu *vcpu) = अणु
	[EXIT_REASON_EXCEPTION_NMI]           = handle_exception_nmi,
	[EXIT_REASON_EXTERNAL_INTERRUPT]      = handle_बाह्यal_पूर्णांकerrupt,
	[EXIT_REASON_TRIPLE_FAULT]            = handle_triple_fault,
	[EXIT_REASON_NMI_WINDOW]	      = handle_nmi_winकरोw,
	[EXIT_REASON_IO_INSTRUCTION]          = handle_io,
	[EXIT_REASON_CR_ACCESS]               = handle_cr,
	[EXIT_REASON_DR_ACCESS]               = handle_dr,
	[EXIT_REASON_CPUID]                   = kvm_emulate_cpuid,
	[EXIT_REASON_MSR_READ]                = kvm_emulate_rdmsr,
	[EXIT_REASON_MSR_WRITE]               = kvm_emulate_wrmsr,
	[EXIT_REASON_INTERRUPT_WINDOW]        = handle_पूर्णांकerrupt_winकरोw,
	[EXIT_REASON_HLT]                     = kvm_emulate_halt,
	[EXIT_REASON_INVD]		      = kvm_emulate_invd,
	[EXIT_REASON_INVLPG]		      = handle_invlpg,
	[EXIT_REASON_RDPMC]                   = kvm_emulate_rdpmc,
	[EXIT_REASON_VMCALL]                  = kvm_emulate_hypercall,
	[EXIT_REASON_VMCLEAR]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMLAUNCH]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMPTRLD]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMPTRST]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMREAD]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMRESUME]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMWRITE]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMOFF]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_VMON]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_TPR_BELOW_THRESHOLD]     = handle_tpr_below_threshold,
	[EXIT_REASON_APIC_ACCESS]             = handle_apic_access,
	[EXIT_REASON_APIC_WRITE]              = handle_apic_ग_लिखो,
	[EXIT_REASON_EOI_INDUCED]             = handle_apic_eoi_induced,
	[EXIT_REASON_WBINVD]                  = kvm_emulate_wbinvd,
	[EXIT_REASON_XSETBV]                  = kvm_emulate_xsetbv,
	[EXIT_REASON_TASK_SWITCH]             = handle_task_चयन,
	[EXIT_REASON_MCE_DURING_VMENTRY]      = handle_machine_check,
	[EXIT_REASON_GDTR_IDTR]		      = handle_desc,
	[EXIT_REASON_LDTR_TR]		      = handle_desc,
	[EXIT_REASON_EPT_VIOLATION]	      = handle_ept_violation,
	[EXIT_REASON_EPT_MISCONFIG]           = handle_ept_misconfig,
	[EXIT_REASON_PAUSE_INSTRUCTION]       = handle_छोड़ो,
	[EXIT_REASON_MWAIT_INSTRUCTION]	      = kvm_emulate_mरुको,
	[EXIT_REASON_MONITOR_TRAP_FLAG]       = handle_monitor_trap,
	[EXIT_REASON_MONITOR_INSTRUCTION]     = kvm_emulate_monitor,
	[EXIT_REASON_INVEPT]                  = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_INVVPID]                 = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_RDRAND]                  = kvm_handle_invalid_op,
	[EXIT_REASON_RDSEED]                  = kvm_handle_invalid_op,
	[EXIT_REASON_PML_FULL]		      = handle_pml_full,
	[EXIT_REASON_INVPCID]                 = handle_invpcid,
	[EXIT_REASON_VMFUNC]		      = handle_vmx_inकाष्ठाion,
	[EXIT_REASON_PREEMPTION_TIMER]	      = handle_preemption_समयr,
	[EXIT_REASON_ENCLS]		      = handle_encls,
	[EXIT_REASON_BUS_LOCK]                = handle_bus_lock_vmनिकास,
पूर्ण;

अटल स्थिर पूर्णांक kvm_vmx_max_निकास_handlers =
	ARRAY_SIZE(kvm_vmx_निकास_handlers);

अटल व्योम vmx_get_निकास_info(काष्ठा kvm_vcpu *vcpu, u64 *info1, u64 *info2,
			      u32 *पूर्णांकr_info, u32 *error_code)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	*info1 = vmx_get_निकास_qual(vcpu);
	अगर (!(vmx->निकास_reason.failed_vmentry)) अणु
		*info2 = vmx->idt_vectoring_info;
		*पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);
		अगर (is_exception_with_error_code(*पूर्णांकr_info))
			*error_code = vmcs_पढ़ो32(VM_EXIT_INTR_ERROR_CODE);
		अन्यथा
			*error_code = 0;
	पूर्ण अन्यथा अणु
		*info2 = 0;
		*पूर्णांकr_info = 0;
		*error_code = 0;
	पूर्ण
पूर्ण

अटल व्योम vmx_destroy_pml_buffer(काष्ठा vcpu_vmx *vmx)
अणु
	अगर (vmx->pml_pg) अणु
		__मुक्त_page(vmx->pml_pg);
		vmx->pml_pg = शून्य;
	पूर्ण
पूर्ण

अटल व्योम vmx_flush_pml_buffer(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u64 *pml_buf;
	u16 pml_idx;

	pml_idx = vmcs_पढ़ो16(GUEST_PML_INDEX);

	/* Do nothing अगर PML buffer is empty */
	अगर (pml_idx == (PML_ENTITY_NUM - 1))
		वापस;

	/* PML index always poपूर्णांकs to next available PML buffer entity */
	अगर (pml_idx >= PML_ENTITY_NUM)
		pml_idx = 0;
	अन्यथा
		pml_idx++;

	pml_buf = page_address(vmx->pml_pg);
	क्रम (; pml_idx < PML_ENTITY_NUM; pml_idx++) अणु
		u64 gpa;

		gpa = pml_buf[pml_idx];
		WARN_ON(gpa & (PAGE_SIZE - 1));
		kvm_vcpu_mark_page_dirty(vcpu, gpa >> PAGE_SHIFT);
	पूर्ण

	/* reset PML index */
	vmcs_ग_लिखो16(GUEST_PML_INDEX, PML_ENTITY_NUM - 1);
पूर्ण

अटल व्योम vmx_dump_sel(अक्षर *name, uपूर्णांक32_t sel)
अणु
	pr_err("%s sel=0x%04x, attr=0x%05x, limit=0x%08x, base=0x%016lx\n",
	       name, vmcs_पढ़ो16(sel),
	       vmcs_पढ़ो32(sel + GUEST_ES_AR_BYTES - GUEST_ES_SELECTOR),
	       vmcs_पढ़ो32(sel + GUEST_ES_LIMIT - GUEST_ES_SELECTOR),
	       vmcs_पढ़ोl(sel + GUEST_ES_BASE - GUEST_ES_SELECTOR));
पूर्ण

अटल व्योम vmx_dump_dtsel(अक्षर *name, uपूर्णांक32_t limit)
अणु
	pr_err("%s                           limit=0x%08x, base=0x%016lx\n",
	       name, vmcs_पढ़ो32(limit),
	       vmcs_पढ़ोl(limit + GUEST_GDTR_BASE - GUEST_GDTR_LIMIT));
पूर्ण

अटल व्योम vmx_dump_msrs(अक्षर *name, काष्ठा vmx_msrs *m)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा vmx_msr_entry *e;

	pr_err("MSR %s:\n", name);
	क्रम (i = 0, e = m->val; i < m->nr; ++i, ++e)
		pr_err("  %2d: msr=0x%08x value=0x%016llx\n", i, e->index, e->value);
पूर्ण

व्योम dump_vmcs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 vmentry_ctl, vmनिकास_ctl;
	u32 cpu_based_exec_ctrl, pin_based_exec_ctrl, secondary_exec_control;
	अचिन्हित दीर्घ cr4;
	पूर्णांक efer_slot;

	अगर (!dump_invalid_vmcs) अणु
		pr_warn_ratelimited("set kvm_intel.dump_invalid_vmcs=1 to dump internal KVM state.\n");
		वापस;
	पूर्ण

	vmentry_ctl = vmcs_पढ़ो32(VM_ENTRY_CONTROLS);
	vmनिकास_ctl = vmcs_पढ़ो32(VM_EXIT_CONTROLS);
	cpu_based_exec_ctrl = vmcs_पढ़ो32(CPU_BASED_VM_EXEC_CONTROL);
	pin_based_exec_ctrl = vmcs_पढ़ो32(PIN_BASED_VM_EXEC_CONTROL);
	cr4 = vmcs_पढ़ोl(GUEST_CR4);
	secondary_exec_control = 0;
	अगर (cpu_has_secondary_exec_ctrls())
		secondary_exec_control = vmcs_पढ़ो32(SECONDARY_VM_EXEC_CONTROL);

	pr_err("*** Guest State ***\n");
	pr_err("CR0: actual=0x%016lx, shadow=0x%016lx, gh_mask=%016lx\n",
	       vmcs_पढ़ोl(GUEST_CR0), vmcs_पढ़ोl(CR0_READ_SHADOW),
	       vmcs_पढ़ोl(CR0_GUEST_HOST_MASK));
	pr_err("CR4: actual=0x%016lx, shadow=0x%016lx, gh_mask=%016lx\n",
	       cr4, vmcs_पढ़ोl(CR4_READ_SHADOW), vmcs_पढ़ोl(CR4_GUEST_HOST_MASK));
	pr_err("CR3 = 0x%016lx\n", vmcs_पढ़ोl(GUEST_CR3));
	अगर (cpu_has_vmx_ept()) अणु
		pr_err("PDPTR0 = 0x%016llx  PDPTR1 = 0x%016llx\n",
		       vmcs_पढ़ो64(GUEST_PDPTR0), vmcs_पढ़ो64(GUEST_PDPTR1));
		pr_err("PDPTR2 = 0x%016llx  PDPTR3 = 0x%016llx\n",
		       vmcs_पढ़ो64(GUEST_PDPTR2), vmcs_पढ़ो64(GUEST_PDPTR3));
	पूर्ण
	pr_err("RSP = 0x%016lx  RIP = 0x%016lx\n",
	       vmcs_पढ़ोl(GUEST_RSP), vmcs_पढ़ोl(GUEST_RIP));
	pr_err("RFLAGS=0x%08lx         DR7 = 0x%016lx\n",
	       vmcs_पढ़ोl(GUEST_RFLAGS), vmcs_पढ़ोl(GUEST_DR7));
	pr_err("Sysenter RSP=%016lx CS:RIP=%04x:%016lx\n",
	       vmcs_पढ़ोl(GUEST_SYSENTER_ESP),
	       vmcs_पढ़ो32(GUEST_SYSENTER_CS), vmcs_पढ़ोl(GUEST_SYSENTER_EIP));
	vmx_dump_sel("CS:  ", GUEST_CS_SELECTOR);
	vmx_dump_sel("DS:  ", GUEST_DS_SELECTOR);
	vmx_dump_sel("SS:  ", GUEST_SS_SELECTOR);
	vmx_dump_sel("ES:  ", GUEST_ES_SELECTOR);
	vmx_dump_sel("FS:  ", GUEST_FS_SELECTOR);
	vmx_dump_sel("GS:  ", GUEST_GS_SELECTOR);
	vmx_dump_dtsel("GDTR:", GUEST_GDTR_LIMIT);
	vmx_dump_sel("LDTR:", GUEST_LDTR_SELECTOR);
	vmx_dump_dtsel("IDTR:", GUEST_IDTR_LIMIT);
	vmx_dump_sel("TR:  ", GUEST_TR_SELECTOR);
	efer_slot = vmx_find_loadstore_msr_slot(&vmx->msr_स्वतःload.guest, MSR_EFER);
	अगर (vmentry_ctl & VM_ENTRY_LOAD_IA32_EFER)
		pr_err("EFER= 0x%016llx\n", vmcs_पढ़ो64(GUEST_IA32_EFER));
	अन्यथा अगर (efer_slot >= 0)
		pr_err("EFER= 0x%016llx (autoload)\n",
		       vmx->msr_स्वतःload.guest.val[efer_slot].value);
	अन्यथा अगर (vmentry_ctl & VM_ENTRY_IA32E_MODE)
		pr_err("EFER= 0x%016llx (effective)\n",
		       vcpu->arch.efer | (EFER_LMA | EFER_LME));
	अन्यथा
		pr_err("EFER= 0x%016llx (effective)\n",
		       vcpu->arch.efer & ~(EFER_LMA | EFER_LME));
	अगर (vmentry_ctl & VM_ENTRY_LOAD_IA32_PAT)
		pr_err("PAT = 0x%016llx\n", vmcs_पढ़ो64(GUEST_IA32_PAT));
	pr_err("DebugCtl = 0x%016llx  DebugExceptions = 0x%016lx\n",
	       vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL),
	       vmcs_पढ़ोl(GUEST_PENDING_DBG_EXCEPTIONS));
	अगर (cpu_has_load_perf_global_ctrl() &&
	    vmentry_ctl & VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL)
		pr_err("PerfGlobCtl = 0x%016llx\n",
		       vmcs_पढ़ो64(GUEST_IA32_PERF_GLOBAL_CTRL));
	अगर (vmentry_ctl & VM_ENTRY_LOAD_BNDCFGS)
		pr_err("BndCfgS = 0x%016llx\n", vmcs_पढ़ो64(GUEST_BNDCFGS));
	pr_err("Interruptibility = %08x  ActivityState = %08x\n",
	       vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO),
	       vmcs_पढ़ो32(GUEST_ACTIVITY_STATE));
	अगर (secondary_exec_control & SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY)
		pr_err("InterruptStatus = %04x\n",
		       vmcs_पढ़ो16(GUEST_INTR_STATUS));
	अगर (vmcs_पढ़ो32(VM_ENTRY_MSR_LOAD_COUNT) > 0)
		vmx_dump_msrs("guest autoload", &vmx->msr_स्वतःload.guest);
	अगर (vmcs_पढ़ो32(VM_EXIT_MSR_STORE_COUNT) > 0)
		vmx_dump_msrs("guest autostore", &vmx->msr_स्वतःstore.guest);

	pr_err("*** Host State ***\n");
	pr_err("RIP = 0x%016lx  RSP = 0x%016lx\n",
	       vmcs_पढ़ोl(HOST_RIP), vmcs_पढ़ोl(HOST_RSP));
	pr_err("CS=%04x SS=%04x DS=%04x ES=%04x FS=%04x GS=%04x TR=%04x\n",
	       vmcs_पढ़ो16(HOST_CS_SELECTOR), vmcs_पढ़ो16(HOST_SS_SELECTOR),
	       vmcs_पढ़ो16(HOST_DS_SELECTOR), vmcs_पढ़ो16(HOST_ES_SELECTOR),
	       vmcs_पढ़ो16(HOST_FS_SELECTOR), vmcs_पढ़ो16(HOST_GS_SELECTOR),
	       vmcs_पढ़ो16(HOST_TR_SELECTOR));
	pr_err("FSBase=%016lx GSBase=%016lx TRBase=%016lx\n",
	       vmcs_पढ़ोl(HOST_FS_BASE), vmcs_पढ़ोl(HOST_GS_BASE),
	       vmcs_पढ़ोl(HOST_TR_BASE));
	pr_err("GDTBase=%016lx IDTBase=%016lx\n",
	       vmcs_पढ़ोl(HOST_GDTR_BASE), vmcs_पढ़ोl(HOST_IDTR_BASE));
	pr_err("CR0=%016lx CR3=%016lx CR4=%016lx\n",
	       vmcs_पढ़ोl(HOST_CR0), vmcs_पढ़ोl(HOST_CR3),
	       vmcs_पढ़ोl(HOST_CR4));
	pr_err("Sysenter RSP=%016lx CS:RIP=%04x:%016lx\n",
	       vmcs_पढ़ोl(HOST_IA32_SYSENTER_ESP),
	       vmcs_पढ़ो32(HOST_IA32_SYSENTER_CS),
	       vmcs_पढ़ोl(HOST_IA32_SYSENTER_EIP));
	अगर (vmनिकास_ctl & VM_EXIT_LOAD_IA32_EFER)
		pr_err("EFER= 0x%016llx\n", vmcs_पढ़ो64(HOST_IA32_EFER));
	अगर (vmनिकास_ctl & VM_EXIT_LOAD_IA32_PAT)
		pr_err("PAT = 0x%016llx\n", vmcs_पढ़ो64(HOST_IA32_PAT));
	अगर (cpu_has_load_perf_global_ctrl() &&
	    vmनिकास_ctl & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL)
		pr_err("PerfGlobCtl = 0x%016llx\n",
		       vmcs_पढ़ो64(HOST_IA32_PERF_GLOBAL_CTRL));
	अगर (vmcs_पढ़ो32(VM_EXIT_MSR_LOAD_COUNT) > 0)
		vmx_dump_msrs("host autoload", &vmx->msr_स्वतःload.host);

	pr_err("*** Control State ***\n");
	pr_err("PinBased=%08x CPUBased=%08x SecondaryExec=%08x\n",
	       pin_based_exec_ctrl, cpu_based_exec_ctrl, secondary_exec_control);
	pr_err("EntryControls=%08x ExitControls=%08x\n", vmentry_ctl, vmनिकास_ctl);
	pr_err("ExceptionBitmap=%08x PFECmask=%08x PFECmatch=%08x\n",
	       vmcs_पढ़ो32(EXCEPTION_BITMAP),
	       vmcs_पढ़ो32(PAGE_FAULT_ERROR_CODE_MASK),
	       vmcs_पढ़ो32(PAGE_FAULT_ERROR_CODE_MATCH));
	pr_err("VMEntry: intr_info=%08x errcode=%08x ilen=%08x\n",
	       vmcs_पढ़ो32(VM_ENTRY_INTR_INFO_FIELD),
	       vmcs_पढ़ो32(VM_ENTRY_EXCEPTION_ERROR_CODE),
	       vmcs_पढ़ो32(VM_ENTRY_INSTRUCTION_LEN));
	pr_err("VMExit: intr_info=%08x errcode=%08x ilen=%08x\n",
	       vmcs_पढ़ो32(VM_EXIT_INTR_INFO),
	       vmcs_पढ़ो32(VM_EXIT_INTR_ERROR_CODE),
	       vmcs_पढ़ो32(VM_EXIT_INSTRUCTION_LEN));
	pr_err("        reason=%08x qualification=%016lx\n",
	       vmcs_पढ़ो32(VM_EXIT_REASON), vmcs_पढ़ोl(EXIT_QUALIFICATION));
	pr_err("IDTVectoring: info=%08x errcode=%08x\n",
	       vmcs_पढ़ो32(IDT_VECTORING_INFO_FIELD),
	       vmcs_पढ़ो32(IDT_VECTORING_ERROR_CODE));
	pr_err("TSC Offset = 0x%016llx\n", vmcs_पढ़ो64(TSC_OFFSET));
	अगर (secondary_exec_control & SECONDARY_EXEC_TSC_SCALING)
		pr_err("TSC Multiplier = 0x%016llx\n",
		       vmcs_पढ़ो64(TSC_MULTIPLIER));
	अगर (cpu_based_exec_ctrl & CPU_BASED_TPR_SHADOW) अणु
		अगर (secondary_exec_control & SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY) अणु
			u16 status = vmcs_पढ़ो16(GUEST_INTR_STATUS);
			pr_err("SVI|RVI = %02x|%02x ", status >> 8, status & 0xff);
		पूर्ण
		pr_cont("TPR Threshold = 0x%02x\n", vmcs_पढ़ो32(TPR_THRESHOLD));
		अगर (secondary_exec_control & SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)
			pr_err("APIC-access addr = 0x%016llx ", vmcs_पढ़ो64(APIC_ACCESS_ADDR));
		pr_cont("virt-APIC addr = 0x%016llx\n", vmcs_पढ़ो64(VIRTUAL_APIC_PAGE_ADDR));
	पूर्ण
	अगर (pin_based_exec_ctrl & PIN_BASED_POSTED_INTR)
		pr_err("PostedIntrVec = 0x%02x\n", vmcs_पढ़ो16(POSTED_INTR_NV));
	अगर ((secondary_exec_control & SECONDARY_EXEC_ENABLE_EPT))
		pr_err("EPT pointer = 0x%016llx\n", vmcs_पढ़ो64(EPT_POINTER));
	अगर (secondary_exec_control & SECONDARY_EXEC_PAUSE_LOOP_EXITING)
		pr_err("PLE Gap=%08x Window=%08x\n",
		       vmcs_पढ़ो32(PLE_GAP), vmcs_पढ़ो32(PLE_WINDOW));
	अगर (secondary_exec_control & SECONDARY_EXEC_ENABLE_VPID)
		pr_err("Virtual processor ID = 0x%04x\n",
		       vmcs_पढ़ो16(VIRTUAL_PROCESSOR_ID));
पूर्ण

/*
 * The guest has निकासed.  See अगर we can fix it or अगर we need userspace
 * assistance.
 */
अटल पूर्णांक __vmx_handle_निकास(काष्ठा kvm_vcpu *vcpu, fastpath_t निकास_fastpath)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	जोड़ vmx_निकास_reason निकास_reason = vmx->निकास_reason;
	u32 vectoring_info = vmx->idt_vectoring_info;
	u16 निकास_handler_index;

	/*
	 * Flush logged GPAs PML buffer, this will make dirty_biपंचांगap more
	 * updated. Another good is, in kvm_vm_ioctl_get_dirty_log, beक्रमe
	 * querying dirty_biपंचांगap, we only need to kick all vcpus out of guest
	 * mode as अगर vcpus is in root mode, the PML buffer must has been
	 * flushed alपढ़ोy.  Note, PML is never enabled in hardware जबतक
	 * running L2.
	 */
	अगर (enable_pml && !is_guest_mode(vcpu))
		vmx_flush_pml_buffer(vcpu);

	/*
	 * We should never reach this poपूर्णांक with a pending nested VM-Enter, and
	 * more specअगरically emulation of L2 due to invalid guest state (see
	 * below) should never happen as that means we incorrectly allowed a
	 * nested VM-Enter with an invalid vmcs12.
	 */
	WARN_ON_ONCE(vmx->nested.nested_run_pending);

	/* If guest state is invalid, start emulating */
	अगर (vmx->emulation_required)
		वापस handle_invalid_guest_state(vcpu);

	अगर (is_guest_mode(vcpu)) अणु
		/*
		 * PML is never enabled when running L2, bail immediately अगर a
		 * PML full निकास occurs as something is horribly wrong.
		 */
		अगर (निकास_reason.basic == EXIT_REASON_PML_FULL)
			जाओ unexpected_vmनिकास;

		/*
		 * The host physical addresses of some pages of guest memory
		 * are loaded पूर्णांकo the vmcs02 (e.g. vmcs12's Virtual APIC
		 * Page). The CPU may ग_लिखो to these pages via their host
		 * physical address जबतक L2 is running, bypassing any
		 * address-translation-based dirty tracking (e.g. EPT ग_लिखो
		 * protection).
		 *
		 * Mark them dirty on every निकास from L2 to prevent them from
		 * getting out of sync with dirty tracking.
		 */
		nested_mark_vmcs12_pages_dirty(vcpu);

		अगर (nested_vmx_reflect_vmनिकास(vcpu))
			वापस 1;
	पूर्ण

	अगर (निकास_reason.failed_vmentry) अणु
		dump_vmcs(vcpu);
		vcpu->run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
		vcpu->run->fail_entry.hardware_entry_failure_reason
			= निकास_reason.full;
		vcpu->run->fail_entry.cpu = vcpu->arch.last_vmentry_cpu;
		वापस 0;
	पूर्ण

	अगर (unlikely(vmx->fail)) अणु
		dump_vmcs(vcpu);
		vcpu->run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
		vcpu->run->fail_entry.hardware_entry_failure_reason
			= vmcs_पढ़ो32(VM_INSTRUCTION_ERROR);
		vcpu->run->fail_entry.cpu = vcpu->arch.last_vmentry_cpu;
		वापस 0;
	पूर्ण

	/*
	 * Note:
	 * Do not try to fix EXIT_REASON_EPT_MISCONFIG अगर it caused by
	 * delivery event since it indicates guest is accessing MMIO.
	 * The vm-निकास can be triggered again after वापस to guest that
	 * will cause infinite loop.
	 */
	अगर ((vectoring_info & VECTORING_INFO_VALID_MASK) &&
	    (निकास_reason.basic != EXIT_REASON_EXCEPTION_NMI &&
	     निकास_reason.basic != EXIT_REASON_EPT_VIOLATION &&
	     निकास_reason.basic != EXIT_REASON_PML_FULL &&
	     निकास_reason.basic != EXIT_REASON_APIC_ACCESS &&
	     निकास_reason.basic != EXIT_REASON_TASK_SWITCH)) अणु
		पूर्णांक ndata = 3;

		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_DELIVERY_EV;
		vcpu->run->पूर्णांकernal.data[0] = vectoring_info;
		vcpu->run->पूर्णांकernal.data[1] = निकास_reason.full;
		vcpu->run->पूर्णांकernal.data[2] = vcpu->arch.निकास_qualअगरication;
		अगर (निकास_reason.basic == EXIT_REASON_EPT_MISCONFIG) अणु
			vcpu->run->पूर्णांकernal.data[ndata++] =
				vmcs_पढ़ो64(GUEST_PHYSICAL_ADDRESS);
		पूर्ण
		vcpu->run->पूर्णांकernal.data[ndata++] = vcpu->arch.last_vmentry_cpu;
		vcpu->run->पूर्णांकernal.ndata = ndata;
		वापस 0;
	पूर्ण

	अगर (unlikely(!enable_vnmi &&
		     vmx->loaded_vmcs->soft_vnmi_blocked)) अणु
		अगर (!vmx_पूर्णांकerrupt_blocked(vcpu)) अणु
			vmx->loaded_vmcs->soft_vnmi_blocked = 0;
		पूर्ण अन्यथा अगर (vmx->loaded_vmcs->vnmi_blocked_समय > 1000000000LL &&
			   vcpu->arch.nmi_pending) अणु
			/*
			 * This CPU करोn't support us in finding the end of an
			 * NMI-blocked winकरोw अगर the guest runs with IRQs
			 * disabled. So we pull the trigger after 1 s of
			 * futile रुकोing, but inक्रमm the user about this.
			 */
			prपूर्णांकk(KERN_WARNING "%s: Breaking out of NMI-blocked "
			       "state on VCPU %d after 1 s timeout\n",
			       __func__, vcpu->vcpu_id);
			vmx->loaded_vmcs->soft_vnmi_blocked = 0;
		पूर्ण
	पूर्ण

	अगर (निकास_fastpath != EXIT_FASTPATH_NONE)
		वापस 1;

	अगर (निकास_reason.basic >= kvm_vmx_max_निकास_handlers)
		जाओ unexpected_vmनिकास;
#अगर_घोषित CONFIG_RETPOLINE
	अगर (निकास_reason.basic == EXIT_REASON_MSR_WRITE)
		वापस kvm_emulate_wrmsr(vcpu);
	अन्यथा अगर (निकास_reason.basic == EXIT_REASON_PREEMPTION_TIMER)
		वापस handle_preemption_समयr(vcpu);
	अन्यथा अगर (निकास_reason.basic == EXIT_REASON_INTERRUPT_WINDOW)
		वापस handle_पूर्णांकerrupt_winकरोw(vcpu);
	अन्यथा अगर (निकास_reason.basic == EXIT_REASON_EXTERNAL_INTERRUPT)
		वापस handle_बाह्यal_पूर्णांकerrupt(vcpu);
	अन्यथा अगर (निकास_reason.basic == EXIT_REASON_HLT)
		वापस kvm_emulate_halt(vcpu);
	अन्यथा अगर (निकास_reason.basic == EXIT_REASON_EPT_MISCONFIG)
		वापस handle_ept_misconfig(vcpu);
#पूर्ण_अगर

	निकास_handler_index = array_index_nospec((u16)निकास_reason.basic,
						kvm_vmx_max_निकास_handlers);
	अगर (!kvm_vmx_निकास_handlers[निकास_handler_index])
		जाओ unexpected_vmनिकास;

	वापस kvm_vmx_निकास_handlers[निकास_handler_index](vcpu);

unexpected_vmनिकास:
	vcpu_unimpl(vcpu, "vmx: unexpected exit reason 0x%x\n",
		    निकास_reason.full);
	dump_vmcs(vcpu);
	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->पूर्णांकernal.suberror =
			KVM_INTERNAL_ERROR_UNEXPECTED_EXIT_REASON;
	vcpu->run->पूर्णांकernal.ndata = 2;
	vcpu->run->पूर्णांकernal.data[0] = निकास_reason.full;
	vcpu->run->पूर्णांकernal.data[1] = vcpu->arch.last_vmentry_cpu;
	वापस 0;
पूर्ण

अटल पूर्णांक vmx_handle_निकास(काष्ठा kvm_vcpu *vcpu, fastpath_t निकास_fastpath)
अणु
	पूर्णांक ret = __vmx_handle_निकास(vcpu, निकास_fastpath);

	/*
	 * Even when current निकास reason is handled by KVM पूर्णांकernally, we
	 * still need to निकास to user space when bus lock detected to inक्रमm
	 * that there is a bus lock in guest.
	 */
	अगर (to_vmx(vcpu)->निकास_reason.bus_lock_detected) अणु
		अगर (ret > 0)
			vcpu->run->निकास_reason = KVM_EXIT_X86_BUS_LOCK;

		vcpu->run->flags |= KVM_RUN_X86_BUS_LOCK;
		वापस 0;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Software based L1D cache flush which is used when microcode providing
 * the cache control MSR is not loaded.
 *
 * The L1D cache is 32 KiB on Nehalem and later microarchitectures, but to
 * flush it is required to पढ़ो in 64 KiB because the replacement algorithm
 * is not exactly LRU. This could be sized at runसमय via topology
 * inक्रमmation but as all relevant affected CPUs have 32KiB L1D cache size
 * there is no poपूर्णांक in करोing so.
 */
अटल noinstr व्योम vmx_l1d_flush(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक size = PAGE_SIZE << L1D_CACHE_ORDER;

	/*
	 * This code is only executed when the the flush mode is 'cond' or
	 * 'always'
	 */
	अगर (अटल_branch_likely(&vmx_l1d_flush_cond)) अणु
		bool flush_l1d;

		/*
		 * Clear the per-vcpu flush bit, it माला_लो set again
		 * either from vcpu_run() or from one of the unsafe
		 * VMEXIT handlers.
		 */
		flush_l1d = vcpu->arch.l1tf_flush_l1d;
		vcpu->arch.l1tf_flush_l1d = false;

		/*
		 * Clear the per-cpu flush bit, it माला_लो set again from
		 * the पूर्णांकerrupt handlers.
		 */
		flush_l1d |= kvm_get_cpu_l1tf_flush_l1d();
		kvm_clear_cpu_l1tf_flush_l1d();

		अगर (!flush_l1d)
			वापस;
	पूर्ण

	vcpu->stat.l1d_flush++;

	अगर (अटल_cpu_has(X86_FEATURE_FLUSH_L1D)) अणु
		native_wrmsrl(MSR_IA32_FLUSH_CMD, L1D_FLUSH);
		वापस;
	पूर्ण

	यंत्र अस्थिर(
		/* First ensure the pages are in the TLB */
		"xorl	%%eax, %%eax\n"
		".Lpopulate_tlb:\n\t"
		"movzbl	(%[flush_pages], %%" _ASM_AX "), %%ecx\n\t"
		"addl	$4096, %%eax\n\t"
		"cmpl	%%eax, %[size]\n\t"
		"jne	.Lpopulate_tlb\n\t"
		"xorl	%%eax, %%eax\n\t"
		"cpuid\n\t"
		/* Now fill the cache */
		"xorl	%%eax, %%eax\n"
		".Lfill_cache:\n"
		"movzbl	(%[flush_pages], %%" _ASM_AX "), %%ecx\n\t"
		"addl	$64, %%eax\n\t"
		"cmpl	%%eax, %[size]\n\t"
		"jne	.Lfill_cache\n\t"
		"lfence\n"
		:: [flush_pages] "r" (vmx_l1d_flush_pages),
		    [size] "r" (size)
		: "eax", "ebx", "ecx", "edx");
पूर्ण

अटल व्योम vmx_update_cr8_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu, पूर्णांक tpr, पूर्णांक irr)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	पूर्णांक tpr_threshold;

	अगर (is_guest_mode(vcpu) &&
		nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW))
		वापस;

	tpr_threshold = (irr == -1 || tpr < irr) ? 0 : irr;
	अगर (is_guest_mode(vcpu))
		to_vmx(vcpu)->nested.l1_tpr_threshold = tpr_threshold;
	अन्यथा
		vmcs_ग_लिखो32(TPR_THRESHOLD, tpr_threshold);
पूर्ण

व्योम vmx_set_भव_apic_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 sec_exec_control;

	अगर (!lapic_in_kernel(vcpu))
		वापस;

	अगर (!flexpriority_enabled &&
	    !cpu_has_vmx_भवize_x2apic_mode())
		वापस;

	/* Postpone execution until vmcs01 is the current VMCS. */
	अगर (is_guest_mode(vcpu)) अणु
		vmx->nested.change_vmcs01_भव_apic_mode = true;
		वापस;
	पूर्ण

	sec_exec_control = secondary_exec_controls_get(vmx);
	sec_exec_control &= ~(SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
			      SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE);

	चयन (kvm_get_apic_mode(vcpu)) अणु
	हाल LAPIC_MODE_INVALID:
		WARN_ONCE(true, "Invalid local APIC state");
		अवरोध;
	हाल LAPIC_MODE_DISABLED:
		अवरोध;
	हाल LAPIC_MODE_XAPIC:
		अगर (flexpriority_enabled) अणु
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
			kvm_make_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu);

			/*
			 * Flush the TLB, reloading the APIC access page will
			 * only करो so अगर its physical address has changed, but
			 * the guest may have inserted a non-APIC mapping पूर्णांकo
			 * the TLB जबतक the APIC access page was disabled.
			 */
			kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
		पूर्ण
		अवरोध;
	हाल LAPIC_MODE_X2APIC:
		अगर (cpu_has_vmx_भवize_x2apic_mode())
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE;
		अवरोध;
	पूर्ण
	secondary_exec_controls_set(vmx, sec_exec_control);

	vmx_update_msr_biपंचांगap(vcpu);
पूर्ण

अटल व्योम vmx_set_apic_access_page_addr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा page *page;

	/* Defer reload until vmcs01 is the current VMCS. */
	अगर (is_guest_mode(vcpu)) अणु
		to_vmx(vcpu)->nested.reload_vmcs01_apic_access_page = true;
		वापस;
	पूर्ण

	अगर (!(secondary_exec_controls_get(to_vmx(vcpu)) &
	    SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES))
		वापस;

	page = gfn_to_page(vcpu->kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	अगर (is_error_page(page))
		वापस;

	vmcs_ग_लिखो64(APIC_ACCESS_ADDR, page_to_phys(page));
	vmx_flush_tlb_current(vcpu);

	/*
	 * Do not pin apic access page in memory, the MMU notअगरier
	 * will call us again अगर it is migrated or swapped out.
	 */
	put_page(page);
पूर्ण

अटल व्योम vmx_hwapic_isr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_isr)
अणु
	u16 status;
	u8 old;

	अगर (max_isr == -1)
		max_isr = 0;

	status = vmcs_पढ़ो16(GUEST_INTR_STATUS);
	old = status >> 8;
	अगर (max_isr != old) अणु
		status &= 0xff;
		status |= max_isr << 8;
		vmcs_ग_लिखो16(GUEST_INTR_STATUS, status);
	पूर्ण
पूर्ण

अटल व्योम vmx_set_rvi(पूर्णांक vector)
अणु
	u16 status;
	u8 old;

	अगर (vector == -1)
		vector = 0;

	status = vmcs_पढ़ो16(GUEST_INTR_STATUS);
	old = (u8)status & 0xff;
	अगर ((u8)vector != old) अणु
		status &= ~0xff;
		status |= (u8)vector;
		vmcs_ग_लिखो16(GUEST_INTR_STATUS, status);
	पूर्ण
पूर्ण

अटल व्योम vmx_hwapic_irr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_irr)
अणु
	/*
	 * When running L2, updating RVI is only relevant when
	 * vmcs12 भव-पूर्णांकerrupt-delivery enabled.
	 * However, it can be enabled only when L1 also
	 * पूर्णांकercepts बाह्यal-पूर्णांकerrupts and in that हाल
	 * we should not update vmcs02 RVI but instead पूर्णांकercept
	 * पूर्णांकerrupt. Thereक्रमe, करो nothing when running L2.
	 */
	अगर (!is_guest_mode(vcpu))
		vmx_set_rvi(max_irr);
पूर्ण

अटल पूर्णांक vmx_sync_pir_to_irr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक max_irr;
	bool max_irr_updated;

	WARN_ON(!vcpu->arch.apicv_active);
	अगर (pi_test_on(&vmx->pi_desc)) अणु
		pi_clear_on(&vmx->pi_desc);
		/*
		 * IOMMU can ग_लिखो to PID.ON, so the barrier matters even on UP.
		 * But on x86 this is just a compiler barrier anyway.
		 */
		smp_mb__after_atomic();
		max_irr_updated =
			kvm_apic_update_irr(vcpu, vmx->pi_desc.pir, &max_irr);

		/*
		 * If we are running L2 and L1 has a new pending पूर्णांकerrupt
		 * which can be injected, we should re-evaluate
		 * what should be करोne with this new L1 पूर्णांकerrupt.
		 * If L1 पूर्णांकercepts बाह्यal-पूर्णांकerrupts, we should
		 * निकास from L2 to L1. Otherwise, पूर्णांकerrupt should be
		 * delivered directly to L2.
		 */
		अगर (is_guest_mode(vcpu) && max_irr_updated) अणु
			अगर (nested_निकास_on_पूर्णांकr(vcpu))
				kvm_vcpu_निकासing_guest_mode(vcpu);
			अन्यथा
				kvm_make_request(KVM_REQ_EVENT, vcpu);
		पूर्ण
	पूर्ण अन्यथा अणु
		max_irr = kvm_lapic_find_highest_irr(vcpu);
	पूर्ण
	vmx_hwapic_irr_update(vcpu, max_irr);
	वापस max_irr;
पूर्ण

अटल व्योम vmx_load_eoi_निकासmap(काष्ठा kvm_vcpu *vcpu, u64 *eoi_निकास_biपंचांगap)
अणु
	अगर (!kvm_vcpu_apicv_active(vcpu))
		वापस;

	vmcs_ग_लिखो64(EOI_EXIT_BITMAP0, eoi_निकास_biपंचांगap[0]);
	vmcs_ग_लिखो64(EOI_EXIT_BITMAP1, eoi_निकास_biपंचांगap[1]);
	vmcs_ग_लिखो64(EOI_EXIT_BITMAP2, eoi_निकास_biपंचांगap[2]);
	vmcs_ग_लिखो64(EOI_EXIT_BITMAP3, eoi_निकास_biपंचांगap[3]);
पूर्ण

अटल व्योम vmx_apicv_post_state_restore(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	pi_clear_on(&vmx->pi_desc);
	स_रखो(vmx->pi_desc.pir, 0, माप(vmx->pi_desc.pir));
पूर्ण

व्योम vmx_करो_पूर्णांकerrupt_nmi_irqoff(अचिन्हित दीर्घ entry);

अटल व्योम handle_पूर्णांकerrupt_nmi_irqoff(काष्ठा kvm_vcpu *vcpu,
					अचिन्हित दीर्घ entry)
अणु
	kvm_beक्रमe_पूर्णांकerrupt(vcpu);
	vmx_करो_पूर्णांकerrupt_nmi_irqoff(entry);
	kvm_after_पूर्णांकerrupt(vcpu);
पूर्ण

अटल व्योम handle_exception_nmi_irqoff(काष्ठा vcpu_vmx *vmx)
अणु
	स्थिर अचिन्हित दीर्घ nmi_entry = (अचिन्हित दीर्घ)यंत्र_exc_nmi_noist;
	u32 पूर्णांकr_info = vmx_get_पूर्णांकr_info(&vmx->vcpu);

	/* अगर निकास due to PF check क्रम async PF */
	अगर (is_page_fault(पूर्णांकr_info))
		vmx->vcpu.arch.apf.host_apf_flags = kvm_पढ़ो_and_reset_apf_flags();
	/* Handle machine checks beक्रमe पूर्णांकerrupts are enabled */
	अन्यथा अगर (is_machine_check(पूर्णांकr_info))
		kvm_machine_check();
	/* We need to handle NMIs beक्रमe पूर्णांकerrupts are enabled */
	अन्यथा अगर (is_nmi(पूर्णांकr_info))
		handle_पूर्णांकerrupt_nmi_irqoff(&vmx->vcpu, nmi_entry);
पूर्ण

अटल व्योम handle_बाह्यal_पूर्णांकerrupt_irqoff(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);
	अचिन्हित पूर्णांक vector = पूर्णांकr_info & INTR_INFO_VECTOR_MASK;
	gate_desc *desc = (gate_desc *)host_idt_base + vector;

	अगर (WARN_ONCE(!is_बाह्यal_पूर्णांकr(पूर्णांकr_info),
	    "KVM: unexpected VM-Exit interrupt info: 0x%x", पूर्णांकr_info))
		वापस;

	handle_पूर्णांकerrupt_nmi_irqoff(vcpu, gate_offset(desc));
पूर्ण

अटल व्योम vmx_handle_निकास_irqoff(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (vmx->निकास_reason.basic == EXIT_REASON_EXTERNAL_INTERRUPT)
		handle_बाह्यal_पूर्णांकerrupt_irqoff(vcpu);
	अन्यथा अगर (vmx->निकास_reason.basic == EXIT_REASON_EXCEPTION_NMI)
		handle_exception_nmi_irqoff(vmx);
पूर्ण

/*
 * The kvm parameter can be शून्य (module initialization, or invocation beक्रमe
 * VM creation). Be sure to check the kvm parameter beक्रमe using it.
 */
अटल bool vmx_has_emulated_msr(काष्ठा kvm *kvm, u32 index)
अणु
	चयन (index) अणु
	हाल MSR_IA32_SMBASE:
		/*
		 * We cannot करो SMM unless we can run the guest in big
		 * real mode.
		 */
		वापस enable_unrestricted_guest || emulate_invalid_guest_state;
	हाल MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		वापस nested;
	हाल MSR_AMD64_VIRT_SPEC_CTRL:
		/* This is AMD only.  */
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम vmx_recover_nmi_blocking(काष्ठा vcpu_vmx *vmx)
अणु
	u32 निकास_पूर्णांकr_info;
	bool unblock_nmi;
	u8 vector;
	bool idtv_info_valid;

	idtv_info_valid = vmx->idt_vectoring_info & VECTORING_INFO_VALID_MASK;

	अगर (enable_vnmi) अणु
		अगर (vmx->loaded_vmcs->nmi_known_unmasked)
			वापस;

		निकास_पूर्णांकr_info = vmx_get_पूर्णांकr_info(&vmx->vcpu);
		unblock_nmi = (निकास_पूर्णांकr_info & INTR_INFO_UNBLOCK_NMI) != 0;
		vector = निकास_पूर्णांकr_info & INTR_INFO_VECTOR_MASK;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Re-set bit "block by NMI" beक्रमe VM entry अगर vmनिकास caused by
		 * a guest IRET fault.
		 * SDM 3: 23.2.2 (September 2008)
		 * Bit 12 is undefined in any of the following हालs:
		 *  If the VM निकास sets the valid bit in the IDT-vectoring
		 *   inक्रमmation field.
		 *  If the VM निकास is due to a द्विगुन fault.
		 */
		अगर ((निकास_पूर्णांकr_info & INTR_INFO_VALID_MASK) && unblock_nmi &&
		    vector != DF_VECTOR && !idtv_info_valid)
			vmcs_set_bits(GUEST_INTERRUPTIBILITY_INFO,
				      GUEST_INTR_STATE_NMI);
		अन्यथा
			vmx->loaded_vmcs->nmi_known_unmasked =
				!(vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO)
				  & GUEST_INTR_STATE_NMI);
	पूर्ण अन्यथा अगर (unlikely(vmx->loaded_vmcs->soft_vnmi_blocked))
		vmx->loaded_vmcs->vnmi_blocked_समय +=
			kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(),
					      vmx->loaded_vmcs->entry_समय));
पूर्ण

अटल व्योम __vmx_complete_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu,
				      u32 idt_vectoring_info,
				      पूर्णांक instr_len_field,
				      पूर्णांक error_code_field)
अणु
	u8 vector;
	पूर्णांक type;
	bool idtv_info_valid;

	idtv_info_valid = idt_vectoring_info & VECTORING_INFO_VALID_MASK;

	vcpu->arch.nmi_injected = false;
	kvm_clear_exception_queue(vcpu);
	kvm_clear_पूर्णांकerrupt_queue(vcpu);

	अगर (!idtv_info_valid)
		वापस;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	vector = idt_vectoring_info & VECTORING_INFO_VECTOR_MASK;
	type = idt_vectoring_info & VECTORING_INFO_TYPE_MASK;

	चयन (type) अणु
	हाल INTR_TYPE_NMI_INTR:
		vcpu->arch.nmi_injected = true;
		/*
		 * SDM 3: 27.7.1.2 (September 2008)
		 * Clear bit "block by NMI" beक्रमe VM entry अगर a NMI
		 * delivery faulted.
		 */
		vmx_set_nmi_mask(vcpu, false);
		अवरोध;
	हाल INTR_TYPE_SOFT_EXCEPTION:
		vcpu->arch.event_निकास_inst_len = vmcs_पढ़ो32(instr_len_field);
		fallthrough;
	हाल INTR_TYPE_HARD_EXCEPTION:
		अगर (idt_vectoring_info & VECTORING_INFO_DELIVER_CODE_MASK) अणु
			u32 err = vmcs_पढ़ो32(error_code_field);
			kvm_requeue_exception_e(vcpu, vector, err);
		पूर्ण अन्यथा
			kvm_requeue_exception(vcpu, vector);
		अवरोध;
	हाल INTR_TYPE_SOFT_INTR:
		vcpu->arch.event_निकास_inst_len = vmcs_पढ़ो32(instr_len_field);
		fallthrough;
	हाल INTR_TYPE_EXT_INTR:
		kvm_queue_पूर्णांकerrupt(vcpu, vector, type == INTR_TYPE_SOFT_INTR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vmx_complete_पूर्णांकerrupts(काष्ठा vcpu_vmx *vmx)
अणु
	__vmx_complete_पूर्णांकerrupts(&vmx->vcpu, vmx->idt_vectoring_info,
				  VM_EXIT_INSTRUCTION_LEN,
				  IDT_VECTORING_ERROR_CODE);
पूर्ण

अटल व्योम vmx_cancel_injection(काष्ठा kvm_vcpu *vcpu)
अणु
	__vmx_complete_पूर्णांकerrupts(vcpu,
				  vmcs_पढ़ो32(VM_ENTRY_INTR_INFO_FIELD),
				  VM_ENTRY_INSTRUCTION_LEN,
				  VM_ENTRY_EXCEPTION_ERROR_CODE);

	vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD, 0);
पूर्ण

अटल व्योम atomic_चयन_perf_msrs(काष्ठा vcpu_vmx *vmx)
अणु
	पूर्णांक i, nr_msrs;
	काष्ठा perf_guest_चयन_msr *msrs;

	/* Note, nr_msrs may be garbage अगर perf_guest_get_msrs() वापसs शून्य. */
	msrs = perf_guest_get_msrs(&nr_msrs);
	अगर (!msrs)
		वापस;

	क्रम (i = 0; i < nr_msrs; i++)
		अगर (msrs[i].host == msrs[i].guest)
			clear_atomic_चयन_msr(vmx, msrs[i].msr);
		अन्यथा
			add_atomic_चयन_msr(vmx, msrs[i].msr, msrs[i].guest,
					msrs[i].host, false);
पूर्ण

अटल व्योम vmx_update_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u64 tscl;
	u32 delta_tsc;

	अगर (vmx->req_immediate_निकास) अणु
		vmcs_ग_लिखो32(VMX_PREEMPTION_TIMER_VALUE, 0);
		vmx->loaded_vmcs->hv_समयr_soft_disabled = false;
	पूर्ण अन्यथा अगर (vmx->hv_deadline_tsc != -1) अणु
		tscl = rdtsc();
		अगर (vmx->hv_deadline_tsc > tscl)
			/* set_hv_समयr ensures the delta fits in 32-bits */
			delta_tsc = (u32)((vmx->hv_deadline_tsc - tscl) >>
				cpu_preemption_समयr_multi);
		अन्यथा
			delta_tsc = 0;

		vmcs_ग_लिखो32(VMX_PREEMPTION_TIMER_VALUE, delta_tsc);
		vmx->loaded_vmcs->hv_समयr_soft_disabled = false;
	पूर्ण अन्यथा अगर (!vmx->loaded_vmcs->hv_समयr_soft_disabled) अणु
		vmcs_ग_लिखो32(VMX_PREEMPTION_TIMER_VALUE, -1);
		vmx->loaded_vmcs->hv_समयr_soft_disabled = true;
	पूर्ण
पूर्ण

व्योम noinstr vmx_update_host_rsp(काष्ठा vcpu_vmx *vmx, अचिन्हित दीर्घ host_rsp)
अणु
	अगर (unlikely(host_rsp != vmx->loaded_vmcs->host_state.rsp)) अणु
		vmx->loaded_vmcs->host_state.rsp = host_rsp;
		vmcs_ग_लिखोl(HOST_RSP, host_rsp);
	पूर्ण
पूर्ण

अटल fastpath_t vmx_निकास_handlers_fastpath(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (to_vmx(vcpu)->निकास_reason.basic) अणु
	हाल EXIT_REASON_MSR_WRITE:
		वापस handle_fastpath_set_msr_irqoff(vcpu);
	हाल EXIT_REASON_PREEMPTION_TIMER:
		वापस handle_fastpath_preemption_समयr(vcpu);
	शेष:
		वापस EXIT_FASTPATH_NONE;
	पूर्ण
पूर्ण

अटल noinstr व्योम vmx_vcpu_enter_निकास(काष्ठा kvm_vcpu *vcpu,
					काष्ठा vcpu_vmx *vmx)
अणु
	kvm_guest_enter_irqoff();

	/* L1D Flush includes CPU buffer clear to mitigate MDS */
	अगर (अटल_branch_unlikely(&vmx_l1d_should_flush))
		vmx_l1d_flush(vcpu);
	अन्यथा अगर (अटल_branch_unlikely(&mds_user_clear))
		mds_clear_cpu_buffers();

	अगर (vcpu->arch.cr2 != native_पढ़ो_cr2())
		native_ग_लिखो_cr2(vcpu->arch.cr2);

	vmx->fail = __vmx_vcpu_run(vmx, (अचिन्हित दीर्घ *)&vcpu->arch.regs,
				   vmx->loaded_vmcs->launched);

	vcpu->arch.cr2 = native_पढ़ो_cr2();

	kvm_guest_निकास_irqoff();
पूर्ण

अटल fastpath_t vmx_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ cr3, cr4;

	/* Record the guest's net vcpu समय क्रम enक्रमced NMI injections. */
	अगर (unlikely(!enable_vnmi &&
		     vmx->loaded_vmcs->soft_vnmi_blocked))
		vmx->loaded_vmcs->entry_समय = kसमय_get();

	/* Don't enter VMX अगर guest state is invalid, let the निकास handler
	   start emulation until we arrive back to a valid state */
	अगर (vmx->emulation_required)
		वापस EXIT_FASTPATH_NONE;

	trace_kvm_entry(vcpu);

	अगर (vmx->ple_winकरोw_dirty) अणु
		vmx->ple_winकरोw_dirty = false;
		vmcs_ग_लिखो32(PLE_WINDOW, vmx->ple_winकरोw);
	पूर्ण

	/*
	 * We did this in prepare_चयन_to_guest, because it needs to
	 * be within srcu_पढ़ो_lock.
	 */
	WARN_ON_ONCE(vmx->nested.need_vmcs12_to_shaकरोw_sync);

	अगर (kvm_रेजिस्टर_is_dirty(vcpu, VCPU_REGS_RSP))
		vmcs_ग_लिखोl(GUEST_RSP, vcpu->arch.regs[VCPU_REGS_RSP]);
	अगर (kvm_रेजिस्टर_is_dirty(vcpu, VCPU_REGS_RIP))
		vmcs_ग_लिखोl(GUEST_RIP, vcpu->arch.regs[VCPU_REGS_RIP]);

	cr3 = __get_current_cr3_fast();
	अगर (unlikely(cr3 != vmx->loaded_vmcs->host_state.cr3)) अणु
		vmcs_ग_लिखोl(HOST_CR3, cr3);
		vmx->loaded_vmcs->host_state.cr3 = cr3;
	पूर्ण

	cr4 = cr4_पढ़ो_shaकरोw();
	अगर (unlikely(cr4 != vmx->loaded_vmcs->host_state.cr4)) अणु
		vmcs_ग_लिखोl(HOST_CR4, cr4);
		vmx->loaded_vmcs->host_state.cr4 = cr4;
	पूर्ण

	/* When single-stepping over STI and MOV SS, we must clear the
	 * corresponding पूर्णांकerruptibility bits in the guest state. Otherwise
	 * vmentry fails as it then expects bit 14 (BS) in pending debug
	 * exceptions being set, but that's not correct क्रम the guest debugging
	 * हाल. */
	अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		vmx_set_पूर्णांकerrupt_shaकरोw(vcpu, 0);

	kvm_load_guest_xsave_state(vcpu);

	pt_guest_enter(vmx);

	atomic_चयन_perf_msrs(vmx);
	अगर (पूर्णांकel_pmu_lbr_is_enabled(vcpu))
		vmx_passthrough_lbr_msrs(vcpu);

	अगर (enable_preemption_समयr)
		vmx_update_hv_समयr(vcpu);

	kvm_रुको_lapic_expire(vcpu);

	/*
	 * If this vCPU has touched SPEC_CTRL, restore the guest's value अगर
	 * it's non-zero. Since vmentry is serialising on affected CPUs, there
	 * is no need to worry about the conditional branch over the wrmsr
	 * being speculatively taken.
	 */
	x86_spec_ctrl_set_guest(vmx->spec_ctrl, 0);

	/* The actual VMENTER/EXIT is in the .noinstr.text section. */
	vmx_vcpu_enter_निकास(vcpu, vmx);

	/*
	 * We करो not use IBRS in the kernel. If this vCPU has used the
	 * SPEC_CTRL MSR it may have left it on; save the value and
	 * turn it off. This is much more efficient than blindly adding
	 * it to the atomic save/restore list. Especially as the क्रमmer
	 * (Saving guest MSRs on vmनिकास) करोesn't even exist in KVM.
	 *
	 * For non-nested हाल:
	 * If the L01 MSR biपंचांगap करोes not पूर्णांकercept the MSR, then we need to
	 * save it.
	 *
	 * For nested हाल:
	 * If the L02 MSR biपंचांगap करोes not पूर्णांकercept the MSR, then we need to
	 * save it.
	 */
	अगर (unlikely(!msr_ग_लिखो_पूर्णांकercepted(vcpu, MSR_IA32_SPEC_CTRL)))
		vmx->spec_ctrl = native_पढ़ो_msr(MSR_IA32_SPEC_CTRL);

	x86_spec_ctrl_restore_host(vmx->spec_ctrl, 0);

	/* All fields are clean at this poपूर्णांक */
	अगर (अटल_branch_unlikely(&enable_evmcs)) अणु
		current_evmcs->hv_clean_fields |=
			HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;

		current_evmcs->hv_vp_id = kvm_hv_get_vpindex(vcpu);
	पूर्ण

	/* MSR_IA32_DEBUGCTLMSR is zeroed on vmनिकास. Restore it अगर needed */
	अगर (vmx->host_debugctlmsr)
		update_debugctlmsr(vmx->host_debugctlmsr);

#अगर_अघोषित CONFIG_X86_64
	/*
	 * The sysनिकास path करोes not restore ds/es, so we must set them to
	 * a reasonable value ourselves.
	 *
	 * We can't defer this to vmx_prepare_चयन_to_host() since that
	 * function may be executed in पूर्णांकerrupt context, which saves and
	 * restore segments around it, nullअगरying its effect.
	 */
	loadsegment(ds, __USER_DS);
	loadsegment(es, __USER_DS);
#पूर्ण_अगर

	vmx_रेजिस्टर_cache_reset(vcpu);

	pt_guest_निकास(vmx);

	kvm_load_host_xsave_state(vcpu);

	vmx->nested.nested_run_pending = 0;
	vmx->idt_vectoring_info = 0;

	अगर (unlikely(vmx->fail)) अणु
		vmx->निकास_reason.full = 0xdead;
		वापस EXIT_FASTPATH_NONE;
	पूर्ण

	vmx->निकास_reason.full = vmcs_पढ़ो32(VM_EXIT_REASON);
	अगर (unlikely((u16)vmx->निकास_reason.basic == EXIT_REASON_MCE_DURING_VMENTRY))
		kvm_machine_check();

	अगर (likely(!vmx->निकास_reason.failed_vmentry))
		vmx->idt_vectoring_info = vmcs_पढ़ो32(IDT_VECTORING_INFO_FIELD);

	trace_kvm_निकास(vmx->निकास_reason.full, vcpu, KVM_ISA_VMX);

	अगर (unlikely(vmx->निकास_reason.failed_vmentry))
		वापस EXIT_FASTPATH_NONE;

	vmx->loaded_vmcs->launched = 1;

	vmx_recover_nmi_blocking(vmx);
	vmx_complete_पूर्णांकerrupts(vmx);

	अगर (is_guest_mode(vcpu))
		वापस EXIT_FASTPATH_NONE;

	वापस vmx_निकास_handlers_fastpath(vcpu);
पूर्ण

अटल व्योम vmx_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (enable_pml)
		vmx_destroy_pml_buffer(vmx);
	मुक्त_vpid(vmx->vpid);
	nested_vmx_मुक्त_vcpu(vcpu);
	मुक्त_loaded_vmcs(vmx->loaded_vmcs);
पूर्ण

अटल पूर्णांक vmx_create_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmx_uret_msr *tsx_ctrl;
	काष्ठा vcpu_vmx *vmx;
	पूर्णांक i, cpu, err;

	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_vmx, vcpu) != 0);
	vmx = to_vmx(vcpu);

	err = -ENOMEM;

	vmx->vpid = allocate_vpid();

	/*
	 * If PML is turned on, failure on enabling PML just results in failure
	 * of creating the vcpu, thereक्रमe we can simplअगरy PML logic (by
	 * aव्योमing dealing with हालs, such as enabling PML partially on vcpus
	 * क्रम the guest), etc.
	 */
	अगर (enable_pml) अणु
		vmx->pml_pg = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
		अगर (!vmx->pml_pg)
			जाओ मुक्त_vpid;
	पूर्ण

	क्रम (i = 0; i < kvm_nr_uret_msrs; ++i) अणु
		vmx->guest_uret_msrs[i].data = 0;
		vmx->guest_uret_msrs[i].mask = -1ull;
	पूर्ण
	अगर (boot_cpu_has(X86_FEATURE_RTM)) अणु
		/*
		 * TSX_CTRL_CPUID_CLEAR is handled in the CPUID पूर्णांकerception.
		 * Keep the host value unchanged to aव्योम changing CPUID bits
		 * under the host kernel's feet.
		 */
		tsx_ctrl = vmx_find_uret_msr(vmx, MSR_IA32_TSX_CTRL);
		अगर (tsx_ctrl)
			vmx->guest_uret_msrs[i].mask = ~(u64)TSX_CTRL_CPUID_CLEAR;
	पूर्ण

	err = alloc_loaded_vmcs(&vmx->vmcs01);
	अगर (err < 0)
		जाओ मुक्त_pml;

	/* The MSR biपंचांगap starts with all ones */
	biपंचांगap_fill(vmx->shaकरोw_msr_पूर्णांकercept.पढ़ो, MAX_POSSIBLE_PASSTHROUGH_MSRS);
	biपंचांगap_fill(vmx->shaकरोw_msr_पूर्णांकercept.ग_लिखो, MAX_POSSIBLE_PASSTHROUGH_MSRS);

	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_TSC, MSR_TYPE_R);
#अगर_घोषित CONFIG_X86_64
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_FS_BASE, MSR_TYPE_RW);
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_GS_BASE, MSR_TYPE_RW);
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_KERNEL_GS_BASE, MSR_TYPE_RW);
#पूर्ण_अगर
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_SYSENTER_CS, MSR_TYPE_RW);
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_SYSENTER_ESP, MSR_TYPE_RW);
	vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_IA32_SYSENTER_EIP, MSR_TYPE_RW);
	अगर (kvm_cstate_in_guest(vcpu->kvm)) अणु
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_CORE_C1_RES, MSR_TYPE_R);
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_CORE_C3_RESIDENCY, MSR_TYPE_R);
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_CORE_C6_RESIDENCY, MSR_TYPE_R);
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, MSR_CORE_C7_RESIDENCY, MSR_TYPE_R);
	पूर्ण
	vmx->msr_biपंचांगap_mode = 0;

	vmx->loaded_vmcs = &vmx->vmcs01;
	cpu = get_cpu();
	vmx_vcpu_load(vcpu, cpu);
	vcpu->cpu = cpu;
	init_vmcs(vmx);
	vmx_vcpu_put(vcpu);
	put_cpu();
	अगर (cpu_need_भवize_apic_accesses(vcpu)) अणु
		err = alloc_apic_access_page(vcpu->kvm);
		अगर (err)
			जाओ मुक्त_vmcs;
	पूर्ण

	अगर (enable_ept && !enable_unrestricted_guest) अणु
		err = init_rmode_identity_map(vcpu->kvm);
		अगर (err)
			जाओ मुक्त_vmcs;
	पूर्ण

	अगर (nested)
		स_नकल(&vmx->nested.msrs, &vmcs_config.nested, माप(vmx->nested.msrs));
	अन्यथा
		स_रखो(&vmx->nested.msrs, 0, माप(vmx->nested.msrs));

	vcpu_setup_sgx_lepubkeyhash(vcpu);

	vmx->nested.posted_पूर्णांकr_nv = -1;
	vmx->nested.current_vmptr = -1ull;

	vcpu->arch.microcode_version = 0x100000000ULL;
	vmx->msr_ia32_feature_control_valid_bits = FEAT_CTL_LOCKED;

	/*
	 * Enक्रमce invariant: pi_desc.nv is always either POSTED_INTR_VECTOR
	 * or POSTED_INTR_WAKEUP_VECTOR.
	 */
	vmx->pi_desc.nv = POSTED_INTR_VECTOR;
	vmx->pi_desc.sn = 1;

#अगर IS_ENABLED(CONFIG_HYPERV)
	vmx->hv_root_ept = INVALID_PAGE;
#पूर्ण_अगर
	वापस 0;

मुक्त_vmcs:
	मुक्त_loaded_vmcs(vmx->loaded_vmcs);
मुक्त_pml:
	vmx_destroy_pml_buffer(vmx);
मुक्त_vpid:
	मुक्त_vpid(vmx->vpid);
	वापस err;
पूर्ण

#घोषणा L1TF_MSG_SMT "L1TF CPU bug present and SMT on, data leak possible. See CVE-2018-3646 and https://www.kernel.org/doc/html/latest/admin-guide/hw-vuln/l1tf.html for details.\n"
#घोषणा L1TF_MSG_L1D "L1TF CPU bug present and virtualization mitigation disabled, data leak possible. See CVE-2018-3646 and https://www.kernel.org/doc/html/latest/admin-guide/hw-vuln/l1tf.html for details.\n"

अटल पूर्णांक vmx_vm_init(काष्ठा kvm *kvm)
अणु
#अगर IS_ENABLED(CONFIG_HYPERV)
	spin_lock_init(&to_kvm_vmx(kvm)->hv_root_ept_lock);
#पूर्ण_अगर

	अगर (!ple_gap)
		kvm->arch.छोड़ो_in_guest = true;

	अगर (boot_cpu_has(X86_BUG_L1TF) && enable_ept) अणु
		चयन (l1tf_mitigation) अणु
		हाल L1TF_MITIGATION_OFF:
		हाल L1TF_MITIGATION_FLUSH_NOWARN:
			/* 'I explicitly don't care' is set */
			अवरोध;
		हाल L1TF_MITIGATION_FLUSH:
		हाल L1TF_MITIGATION_FLUSH_NOSMT:
		हाल L1TF_MITIGATION_FULL:
			/*
			 * Warn upon starting the first VM in a potentially
			 * insecure environment.
			 */
			अगर (sched_smt_active())
				pr_warn_once(L1TF_MSG_SMT);
			अगर (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_NEVER)
				pr_warn_once(L1TF_MSG_L1D);
			अवरोध;
		हाल L1TF_MITIGATION_FULL_FORCE:
			/* Flush is enक्रमced */
			अवरोध;
		पूर्ण
	पूर्ण
	kvm_apicv_init(kvm, enable_apicv);
	वापस 0;
पूर्ण

अटल पूर्णांक __init vmx_check_processor_compat(व्योम)
अणु
	काष्ठा vmcs_config vmcs_conf;
	काष्ठा vmx_capability vmx_cap;

	अगर (!this_cpu_has(X86_FEATURE_MSR_IA32_FEAT_CTL) ||
	    !this_cpu_has(X86_FEATURE_VMX)) अणु
		pr_err("kvm: VMX is disabled on CPU %d\n", smp_processor_id());
		वापस -EIO;
	पूर्ण

	अगर (setup_vmcs_config(&vmcs_conf, &vmx_cap) < 0)
		वापस -EIO;
	अगर (nested)
		nested_vmx_setup_ctls_msrs(&vmcs_conf.nested, vmx_cap.ept);
	अगर (स_भेद(&vmcs_config, &vmcs_conf, माप(काष्ठा vmcs_config)) != 0) अणु
		prपूर्णांकk(KERN_ERR "kvm: CPU %d feature inconsistency!\n",
				smp_processor_id());
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 vmx_get_mt_mask(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio)
अणु
	u8 cache;
	u64 ipat = 0;

	/* We wanted to honor guest CD/MTRR/PAT, but करोing so could result in
	 * memory aliases with conflicting memory types and someबार MCEs.
	 * We have to be careful as to what are honored and when.
	 *
	 * For MMIO, guest CD/MTRR are ignored.  The EPT memory type is set to
	 * UC.  The effective memory type is UC or WC depending on guest PAT.
	 * This was historically the source of MCEs and we want to be
	 * conservative.
	 *
	 * When there is no need to deal with noncoherent DMA (e.g., no VT-d
	 * or VT-d has snoop control), guest CD/MTRR/PAT are all ignored.  The
	 * EPT memory type is set to WB.  The effective memory type is क्रमced
	 * WB.
	 *
	 * Otherwise, we trust guest.  Guest CD/MTRR/PAT are all honored.  The
	 * EPT memory type is used to emulate guest CD/MTRR.
	 */

	अगर (is_mmio) अणु
		cache = MTRR_TYPE_UNCACHABLE;
		जाओ निकास;
	पूर्ण

	अगर (!kvm_arch_has_noncoherent_dma(vcpu->kvm)) अणु
		ipat = VMX_EPT_IPAT_BIT;
		cache = MTRR_TYPE_WRBACK;
		जाओ निकास;
	पूर्ण

	अगर (kvm_पढ़ो_cr0(vcpu) & X86_CR0_CD) अणु
		ipat = VMX_EPT_IPAT_BIT;
		अगर (kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_CD_NW_CLEARED))
			cache = MTRR_TYPE_WRBACK;
		अन्यथा
			cache = MTRR_TYPE_UNCACHABLE;
		जाओ निकास;
	पूर्ण

	cache = kvm_mtrr_get_guest_memory_type(vcpu, gfn);

निकास:
	वापस (cache << VMX_EPT_MT_EPTE_SHIFT) | ipat;
पूर्ण

अटल व्योम vmcs_set_secondary_exec_control(काष्ठा vcpu_vmx *vmx)
अणु
	/*
	 * These bits in the secondary execution controls field
	 * are dynamic, the others are mostly based on the hypervisor
	 * architecture and the guest's CPUID.  Do not touch the
	 * dynamic bits.
	 */
	u32 mask =
		SECONDARY_EXEC_SHADOW_VMCS |
		SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE |
		SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
		SECONDARY_EXEC_DESC;

	u32 new_ctl = vmx->secondary_exec_control;
	u32 cur_ctl = secondary_exec_controls_get(vmx);

	secondary_exec_controls_set(vmx, (new_ctl & ~mask) | (cur_ctl & mask));
पूर्ण

/*
 * Generate MSR_IA32_VMX_CRअणु0,4पूर्ण_FIXED1 according to CPUID. Only set bits
 * (indicating "allowed-1") अगर they are supported in the guest's CPUID.
 */
अटल व्योम nested_vmx_cr_fixed1_bits_update(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा kvm_cpuid_entry2 *entry;

	vmx->nested.msrs.cr0_fixed1 = 0xffffffff;
	vmx->nested.msrs.cr4_fixed1 = X86_CR4_PCE;

#घोषणा cr4_fixed1_update(_cr4_mask, _reg, _cpuid_mask) करो अणु		\
	अगर (entry && (entry->_reg & (_cpuid_mask)))			\
		vmx->nested.msrs.cr4_fixed1 |= (_cr4_mask);	\
पूर्ण जबतक (0)

	entry = kvm_find_cpuid_entry(vcpu, 0x1, 0);
	cr4_fixed1_update(X86_CR4_VME,        edx, feature_bit(VME));
	cr4_fixed1_update(X86_CR4_PVI,        edx, feature_bit(VME));
	cr4_fixed1_update(X86_CR4_TSD,        edx, feature_bit(TSC));
	cr4_fixed1_update(X86_CR4_DE,         edx, feature_bit(DE));
	cr4_fixed1_update(X86_CR4_PSE,        edx, feature_bit(PSE));
	cr4_fixed1_update(X86_CR4_PAE,        edx, feature_bit(PAE));
	cr4_fixed1_update(X86_CR4_MCE,        edx, feature_bit(MCE));
	cr4_fixed1_update(X86_CR4_PGE,        edx, feature_bit(PGE));
	cr4_fixed1_update(X86_CR4_OSFXSR,     edx, feature_bit(FXSR));
	cr4_fixed1_update(X86_CR4_OSXMMEXCPT, edx, feature_bit(XMM));
	cr4_fixed1_update(X86_CR4_VMXE,       ecx, feature_bit(VMX));
	cr4_fixed1_update(X86_CR4_SMXE,       ecx, feature_bit(SMX));
	cr4_fixed1_update(X86_CR4_PCIDE,      ecx, feature_bit(PCID));
	cr4_fixed1_update(X86_CR4_OSXSAVE,    ecx, feature_bit(XSAVE));

	entry = kvm_find_cpuid_entry(vcpu, 0x7, 0);
	cr4_fixed1_update(X86_CR4_FSGSBASE,   ebx, feature_bit(FSGSBASE));
	cr4_fixed1_update(X86_CR4_SMEP,       ebx, feature_bit(SMEP));
	cr4_fixed1_update(X86_CR4_SMAP,       ebx, feature_bit(SMAP));
	cr4_fixed1_update(X86_CR4_PKE,        ecx, feature_bit(PKU));
	cr4_fixed1_update(X86_CR4_UMIP,       ecx, feature_bit(UMIP));
	cr4_fixed1_update(X86_CR4_LA57,       ecx, feature_bit(LA57));

#अघोषित cr4_fixed1_update
पूर्ण

अटल व्योम nested_vmx_entry_निकास_ctls_update(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (kvm_mpx_supported()) अणु
		bool mpx_enabled = guest_cpuid_has(vcpu, X86_FEATURE_MPX);

		अगर (mpx_enabled) अणु
			vmx->nested.msrs.entry_ctls_high |= VM_ENTRY_LOAD_BNDCFGS;
			vmx->nested.msrs.निकास_ctls_high |= VM_EXIT_CLEAR_BNDCFGS;
		पूर्ण अन्यथा अणु
			vmx->nested.msrs.entry_ctls_high &= ~VM_ENTRY_LOAD_BNDCFGS;
			vmx->nested.msrs.निकास_ctls_high &= ~VM_EXIT_CLEAR_BNDCFGS;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम update_पूर्णांकel_pt_cfg(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा kvm_cpuid_entry2 *best = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < PT_CPUID_LEAVES; i++) अणु
		best = kvm_find_cpuid_entry(vcpu, 0x14, i);
		अगर (!best)
			वापस;
		vmx->pt_desc.caps[CPUID_EAX + i*PT_CPUID_REGS_NUM] = best->eax;
		vmx->pt_desc.caps[CPUID_EBX + i*PT_CPUID_REGS_NUM] = best->ebx;
		vmx->pt_desc.caps[CPUID_ECX + i*PT_CPUID_REGS_NUM] = best->ecx;
		vmx->pt_desc.caps[CPUID_EDX + i*PT_CPUID_REGS_NUM] = best->edx;
	पूर्ण

	/* Get the number of configurable Address Ranges क्रम filtering */
	vmx->pt_desc.addr_range = पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps,
						PT_CAP_num_address_ranges);

	/* Initialize and clear the no dependency bits */
	vmx->pt_desc.ctl_biपंचांगask = ~(RTIT_CTL_TRACEEN | RTIT_CTL_OS |
			RTIT_CTL_USR | RTIT_CTL_TSC_EN | RTIT_CTL_DISRETC);

	/*
	 * If CPUID.(EAX=14H,ECX=0):EBX[0]=1 CR3Filter can be set otherwise
	 * will inject an #GP
	 */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_cr3_filtering))
		vmx->pt_desc.ctl_biपंचांगask &= ~RTIT_CTL_CR3EN;

	/*
	 * If CPUID.(EAX=14H,ECX=0):EBX[1]=1 CYCEn, CycThresh and
	 * PSBFreq can be set
	 */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_psb_cyc))
		vmx->pt_desc.ctl_biपंचांगask &= ~(RTIT_CTL_CYCLEACC |
				RTIT_CTL_CYC_THRESH | RTIT_CTL_PSB_FREQ);

	/*
	 * If CPUID.(EAX=14H,ECX=0):EBX[3]=1 MTCEn BranchEn and
	 * MTCFreq can be set
	 */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_mtc))
		vmx->pt_desc.ctl_biपंचांगask &= ~(RTIT_CTL_MTC_EN |
				RTIT_CTL_BRANCH_EN | RTIT_CTL_MTC_RANGE);

	/* If CPUID.(EAX=14H,ECX=0):EBX[4]=1 FUPonPTW and PTWEn can be set */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_ptग_लिखो))
		vmx->pt_desc.ctl_biपंचांगask &= ~(RTIT_CTL_FUP_ON_PTW |
							RTIT_CTL_PTW_EN);

	/* If CPUID.(EAX=14H,ECX=0):EBX[5]=1 PwrEvEn can be set */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_घातer_event_trace))
		vmx->pt_desc.ctl_biपंचांगask &= ~RTIT_CTL_PWR_EVT_EN;

	/* If CPUID.(EAX=14H,ECX=0):ECX[0]=1 ToPA can be set */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_topa_output))
		vmx->pt_desc.ctl_biपंचांगask &= ~RTIT_CTL_TOPA;

	/* If CPUID.(EAX=14H,ECX=0):ECX[3]=1 FabricEn can be set */
	अगर (पूर्णांकel_pt_validate_cap(vmx->pt_desc.caps, PT_CAP_output_subsys))
		vmx->pt_desc.ctl_biपंचांगask &= ~RTIT_CTL_FABRIC_EN;

	/* unmask address range configure area */
	क्रम (i = 0; i < vmx->pt_desc.addr_range; i++)
		vmx->pt_desc.ctl_biपंचांगask &= ~(0xfULL << (32 + i * 4));
पूर्ण

अटल व्योम vmx_vcpu_after_set_cpuid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/* xsaves_enabled is recomputed in vmx_compute_secondary_exec_control(). */
	vcpu->arch.xsaves_enabled = false;

	अगर (cpu_has_secondary_exec_ctrls()) अणु
		vmx_compute_secondary_exec_control(vmx);
		vmcs_set_secondary_exec_control(vmx);
	पूर्ण

	अगर (nested_vmx_allowed(vcpu))
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits |=
			FEAT_CTL_VMX_ENABLED_INSIDE_SMX |
			FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX;
	अन्यथा
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits &=
			~(FEAT_CTL_VMX_ENABLED_INSIDE_SMX |
			  FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX);

	अगर (nested_vmx_allowed(vcpu)) अणु
		nested_vmx_cr_fixed1_bits_update(vcpu);
		nested_vmx_entry_निकास_ctls_update(vcpu);
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_INTEL_PT) &&
			guest_cpuid_has(vcpu, X86_FEATURE_INTEL_PT))
		update_पूर्णांकel_pt_cfg(vcpu);

	अगर (boot_cpu_has(X86_FEATURE_RTM)) अणु
		काष्ठा vmx_uret_msr *msr;
		msr = vmx_find_uret_msr(vmx, MSR_IA32_TSX_CTRL);
		अगर (msr) अणु
			bool enabled = guest_cpuid_has(vcpu, X86_FEATURE_RTM);
			vmx_set_guest_uret_msr(vmx, msr, enabled ? 0 : TSX_CTRL_RTM_DISABLE);
		पूर्ण
	पूर्ण

	set_cr4_guest_host_mask(vmx);

	vmx_ग_लिखो_encls_biपंचांगap(vcpu, शून्य);
	अगर (guest_cpuid_has(vcpu, X86_FEATURE_SGX))
		vmx->msr_ia32_feature_control_valid_bits |= FEAT_CTL_SGX_ENABLED;
	अन्यथा
		vmx->msr_ia32_feature_control_valid_bits &= ~FEAT_CTL_SGX_ENABLED;

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_SGX_LC))
		vmx->msr_ia32_feature_control_valid_bits |=
			FEAT_CTL_SGX_LC_ENABLED;
	अन्यथा
		vmx->msr_ia32_feature_control_valid_bits &=
			~FEAT_CTL_SGX_LC_ENABLED;

	/* Refresh #PF पूर्णांकerception to account क्रम MAXPHYADDR changes. */
	vmx_update_exception_biपंचांगap(vcpu);
पूर्ण

अटल __init व्योम vmx_set_cpu_caps(व्योम)
अणु
	kvm_set_cpu_caps();

	/* CPUID 0x1 */
	अगर (nested)
		kvm_cpu_cap_set(X86_FEATURE_VMX);

	/* CPUID 0x7 */
	अगर (kvm_mpx_supported())
		kvm_cpu_cap_check_and_set(X86_FEATURE_MPX);
	अगर (!cpu_has_vmx_invpcid())
		kvm_cpu_cap_clear(X86_FEATURE_INVPCID);
	अगर (vmx_pt_mode_is_host_guest())
		kvm_cpu_cap_check_and_set(X86_FEATURE_INTEL_PT);

	अगर (!enable_sgx) अणु
		kvm_cpu_cap_clear(X86_FEATURE_SGX);
		kvm_cpu_cap_clear(X86_FEATURE_SGX_LC);
		kvm_cpu_cap_clear(X86_FEATURE_SGX1);
		kvm_cpu_cap_clear(X86_FEATURE_SGX2);
	पूर्ण

	अगर (vmx_umip_emulated())
		kvm_cpu_cap_set(X86_FEATURE_UMIP);

	/* CPUID 0xD.1 */
	supported_xss = 0;
	अगर (!cpu_has_vmx_xsaves())
		kvm_cpu_cap_clear(X86_FEATURE_XSAVES);

	/* CPUID 0x80000001 and 0x7 (RDPID) */
	अगर (!cpu_has_vmx_rdtscp()) अणु
		kvm_cpu_cap_clear(X86_FEATURE_RDTSCP);
		kvm_cpu_cap_clear(X86_FEATURE_RDPID);
	पूर्ण

	अगर (cpu_has_vmx_रुकोpkg())
		kvm_cpu_cap_check_and_set(X86_FEATURE_WAITPKG);
पूर्ण

अटल व्योम vmx_request_immediate_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	to_vmx(vcpu)->req_immediate_निकास = true;
पूर्ण

अटल पूर्णांक vmx_check_पूर्णांकercept_io(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा x86_inकाष्ठाion_info *info)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	अचिन्हित लघु port;
	bool पूर्णांकercept;
	पूर्णांक size;

	अगर (info->पूर्णांकercept == x86_पूर्णांकercept_in ||
	    info->पूर्णांकercept == x86_पूर्णांकercept_ins) अणु
		port = info->src_val;
		size = info->dst_bytes;
	पूर्ण अन्यथा अणु
		port = info->dst_val;
		size = info->src_bytes;
	पूर्ण

	/*
	 * If the 'use IO bitmaps' VM-execution control is 0, IO inकाष्ठाion
	 * VM-निकासs depend on the 'unconditional IO exiting' VM-execution
	 * control.
	 *
	 * Otherwise, IO inकाष्ठाion VM-निकासs are controlled by the IO biपंचांगaps.
	 */
	अगर (!nested_cpu_has(vmcs12, CPU_BASED_USE_IO_BITMAPS))
		पूर्णांकercept = nested_cpu_has(vmcs12,
					   CPU_BASED_UNCOND_IO_EXITING);
	अन्यथा
		पूर्णांकercept = nested_vmx_check_io_biपंचांगaps(vcpu, port, size);

	/* FIXME: produce nested vmनिकास and वापस X86EMUL_INTERCEPTED.  */
	वापस पूर्णांकercept ? X86EMUL_UNHANDLEABLE : X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक vmx_check_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा x86_inकाष्ठाion_info *info,
			       क्रमागत x86_पूर्णांकercept_stage stage,
			       काष्ठा x86_exception *exception)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	चयन (info->पूर्णांकercept) अणु
	/*
	 * RDPID causes #UD अगर disabled through secondary execution controls.
	 * Because it is marked as EmulateOnUD, we need to पूर्णांकercept it here.
	 * Note, RDPID is hidden behind ENABLE_RDTSCP.
	 */
	हाल x86_पूर्णांकercept_rdpid:
		अगर (!nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_RDTSCP)) अणु
			exception->vector = UD_VECTOR;
			exception->error_code_valid = false;
			वापस X86EMUL_PROPAGATE_FAULT;
		पूर्ण
		अवरोध;

	हाल x86_पूर्णांकercept_in:
	हाल x86_पूर्णांकercept_ins:
	हाल x86_पूर्णांकercept_out:
	हाल x86_पूर्णांकercept_outs:
		वापस vmx_check_पूर्णांकercept_io(vcpu, info);

	हाल x86_पूर्णांकercept_lgdt:
	हाल x86_पूर्णांकercept_lidt:
	हाल x86_पूर्णांकercept_lldt:
	हाल x86_पूर्णांकercept_ltr:
	हाल x86_पूर्णांकercept_sgdt:
	हाल x86_पूर्णांकercept_sidt:
	हाल x86_पूर्णांकercept_sldt:
	हाल x86_पूर्णांकercept_str:
		अगर (!nested_cpu_has2(vmcs12, SECONDARY_EXEC_DESC))
			वापस X86EMUL_CONTINUE;

		/* FIXME: produce nested vmनिकास and वापस X86EMUL_INTERCEPTED.  */
		अवरोध;

	/* TODO: check more पूर्णांकercepts... */
	शेष:
		अवरोध;
	पूर्ण

	वापस X86EMUL_UNHANDLEABLE;
पूर्ण

#अगर_घोषित CONFIG_X86_64
/* (a << shअगरt) / भागisor, वापस 1 अगर overflow otherwise 0 */
अटल अंतरभूत पूर्णांक u64_shl_भाग_u64(u64 a, अचिन्हित पूर्णांक shअगरt,
				  u64 भागisor, u64 *result)
अणु
	u64 low = a << shअगरt, high = a >> (64 - shअगरt);

	/* To aव्योम the overflow on भागq */
	अगर (high >= भागisor)
		वापस 1;

	/* Low hold the result, high hold rem which is discarded */
	यंत्र("divq %2\n\t" : "=a" (low), "=d" (high) :
	    "rm" (भागisor), "0" (low), "1" (high));
	*result = low;

	वापस 0;
पूर्ण

अटल पूर्णांक vmx_set_hv_समयr(काष्ठा kvm_vcpu *vcpu, u64 guest_deadline_tsc,
			    bool *expired)
अणु
	काष्ठा vcpu_vmx *vmx;
	u64 tscl, guest_tscl, delta_tsc, lapic_समयr_advance_cycles;
	काष्ठा kvm_समयr *kसमयr = &vcpu->arch.apic->lapic_समयr;

	vmx = to_vmx(vcpu);
	tscl = rdtsc();
	guest_tscl = kvm_पढ़ो_l1_tsc(vcpu, tscl);
	delta_tsc = max(guest_deadline_tsc, guest_tscl) - guest_tscl;
	lapic_समयr_advance_cycles = nsec_to_cycles(vcpu,
						    kसमयr->समयr_advance_ns);

	अगर (delta_tsc > lapic_समयr_advance_cycles)
		delta_tsc -= lapic_समयr_advance_cycles;
	अन्यथा
		delta_tsc = 0;

	/* Convert to host delta tsc अगर tsc scaling is enabled */
	अगर (vcpu->arch.tsc_scaling_ratio != kvm_शेष_tsc_scaling_ratio &&
	    delta_tsc && u64_shl_भाग_u64(delta_tsc,
				kvm_tsc_scaling_ratio_frac_bits,
				vcpu->arch.tsc_scaling_ratio, &delta_tsc))
		वापस -दुस्फल;

	/*
	 * If the delta tsc can't fit in the 32 bit after the multi shअगरt,
	 * we can't use the preemption समयr.
	 * It's possible that it fits on later vmentries, but checking
	 * on every vmentry is costly so we just use an hrसमयr.
	 */
	अगर (delta_tsc >> (cpu_preemption_समयr_multi + 32))
		वापस -दुस्फल;

	vmx->hv_deadline_tsc = tscl + delta_tsc;
	*expired = !delta_tsc;
	वापस 0;
पूर्ण

अटल व्योम vmx_cancel_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	to_vmx(vcpu)->hv_deadline_tsc = -1;
पूर्ण
#पूर्ण_अगर

अटल व्योम vmx_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	अगर (!kvm_छोड़ो_in_guest(vcpu->kvm))
		shrink_ple_winकरोw(vcpu);
पूर्ण

व्योम vmx_update_cpu_dirty_logging(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (is_guest_mode(vcpu)) अणु
		vmx->nested.update_vmcs01_cpu_dirty_logging = true;
		वापस;
	पूर्ण

	/*
	 * Note, cpu_dirty_logging_count can be changed concurrent with this
	 * code, but in that हाल another update request will be made and so
	 * the guest will never run with a stale PML value.
	 */
	अगर (vcpu->kvm->arch.cpu_dirty_logging_count)
		secondary_exec_controls_setbit(vmx, SECONDARY_EXEC_ENABLE_PML);
	अन्यथा
		secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_ENABLE_PML);
पूर्ण

अटल पूर्णांक vmx_pre_block(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (pi_pre_block(vcpu))
		वापस 1;

	अगर (kvm_lapic_hv_समयr_in_use(vcpu))
		kvm_lapic_चयन_to_sw_समयr(vcpu);

	वापस 0;
पूर्ण

अटल व्योम vmx_post_block(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_x86_ops.set_hv_समयr)
		kvm_lapic_चयन_to_hv_समयr(vcpu);

	pi_post_block(vcpu);
पूर्ण

अटल व्योम vmx_setup_mce(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.mcg_cap & MCG_LMCE_P)
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits |=
			FEAT_CTL_LMCE_ENABLED;
	अन्यथा
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits &=
			~FEAT_CTL_LMCE_ENABLED;
पूर्ण

अटल पूर्णांक vmx_smi_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	/* we need a nested vmनिकास to enter SMM, postpone अगर run is pending */
	अगर (to_vmx(vcpu)->nested.nested_run_pending)
		वापस -EBUSY;
	वापस !is_smm(vcpu);
पूर्ण

अटल पूर्णांक vmx_pre_enter_smm(काष्ठा kvm_vcpu *vcpu, अक्षर *smstate)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	vmx->nested.smm.guest_mode = is_guest_mode(vcpu);
	अगर (vmx->nested.smm.guest_mode)
		nested_vmx_vmनिकास(vcpu, -1, 0, 0);

	vmx->nested.smm.vmxon = vmx->nested.vmxon;
	vmx->nested.vmxon = false;
	vmx_clear_hlt(vcpu);
	वापस 0;
पूर्ण

अटल पूर्णांक vmx_pre_leave_smm(काष्ठा kvm_vcpu *vcpu, स्थिर अक्षर *smstate)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक ret;

	अगर (vmx->nested.smm.vmxon) अणु
		vmx->nested.vmxon = true;
		vmx->nested.smm.vmxon = false;
	पूर्ण

	अगर (vmx->nested.smm.guest_mode) अणु
		ret = nested_vmx_enter_non_root_mode(vcpu, false);
		अगर (ret)
			वापस ret;

		vmx->nested.smm.guest_mode = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vmx_enable_smi_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	/* RSM will cause a vmनिकास anyway.  */
पूर्ण

अटल bool vmx_apic_init_संकेत_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.vmxon && !is_guest_mode(vcpu);
पूर्ण

अटल व्योम vmx_migrate_समयrs(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_guest_mode(vcpu)) अणु
		काष्ठा hrसमयr *समयr = &to_vmx(vcpu)->nested.preemption_समयr;

		अगर (hrसमयr_try_to_cancel(समयr) == 1)
			hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS_PINNED);
	पूर्ण
पूर्ण

अटल व्योम hardware_unsetup(व्योम)
अणु
	अगर (nested)
		nested_vmx_hardware_unsetup();

	मुक्त_kvm_area();
पूर्ण

अटल bool vmx_check_apicv_inhibit_reasons(uदीर्घ bit)
अणु
	uदीर्घ supported = BIT(APICV_INHIBIT_REASON_DISABLE) |
			  BIT(APICV_INHIBIT_REASON_HYPERV);

	वापस supported & BIT(bit);
पूर्ण

अटल काष्ठा kvm_x86_ops vmx_x86_ops __initdata = अणु
	.hardware_unsetup = hardware_unsetup,

	.hardware_enable = hardware_enable,
	.hardware_disable = hardware_disable,
	.cpu_has_accelerated_tpr = report_flexpriority,
	.has_emulated_msr = vmx_has_emulated_msr,

	.vm_size = माप(काष्ठा kvm_vmx),
	.vm_init = vmx_vm_init,

	.vcpu_create = vmx_create_vcpu,
	.vcpu_मुक्त = vmx_मुक्त_vcpu,
	.vcpu_reset = vmx_vcpu_reset,

	.prepare_guest_चयन = vmx_prepare_चयन_to_guest,
	.vcpu_load = vmx_vcpu_load,
	.vcpu_put = vmx_vcpu_put,

	.update_exception_biपंचांगap = vmx_update_exception_biपंचांगap,
	.get_msr_feature = vmx_get_msr_feature,
	.get_msr = vmx_get_msr,
	.set_msr = vmx_set_msr,
	.get_segment_base = vmx_get_segment_base,
	.get_segment = vmx_get_segment,
	.set_segment = vmx_set_segment,
	.get_cpl = vmx_get_cpl,
	.get_cs_db_l_bits = vmx_get_cs_db_l_bits,
	.set_cr0 = vmx_set_cr0,
	.is_valid_cr4 = vmx_is_valid_cr4,
	.set_cr4 = vmx_set_cr4,
	.set_efer = vmx_set_efer,
	.get_idt = vmx_get_idt,
	.set_idt = vmx_set_idt,
	.get_gdt = vmx_get_gdt,
	.set_gdt = vmx_set_gdt,
	.set_dr7 = vmx_set_dr7,
	.sync_dirty_debug_regs = vmx_sync_dirty_debug_regs,
	.cache_reg = vmx_cache_reg,
	.get_rflags = vmx_get_rflags,
	.set_rflags = vmx_set_rflags,

	.tlb_flush_all = vmx_flush_tlb_all,
	.tlb_flush_current = vmx_flush_tlb_current,
	.tlb_flush_gva = vmx_flush_tlb_gva,
	.tlb_flush_guest = vmx_flush_tlb_guest,

	.run = vmx_vcpu_run,
	.handle_निकास = vmx_handle_निकास,
	.skip_emulated_inकाष्ठाion = vmx_skip_emulated_inकाष्ठाion,
	.update_emulated_inकाष्ठाion = vmx_update_emulated_inकाष्ठाion,
	.set_पूर्णांकerrupt_shaकरोw = vmx_set_पूर्णांकerrupt_shaकरोw,
	.get_पूर्णांकerrupt_shaकरोw = vmx_get_पूर्णांकerrupt_shaकरोw,
	.patch_hypercall = vmx_patch_hypercall,
	.set_irq = vmx_inject_irq,
	.set_nmi = vmx_inject_nmi,
	.queue_exception = vmx_queue_exception,
	.cancel_injection = vmx_cancel_injection,
	.पूर्णांकerrupt_allowed = vmx_पूर्णांकerrupt_allowed,
	.nmi_allowed = vmx_nmi_allowed,
	.get_nmi_mask = vmx_get_nmi_mask,
	.set_nmi_mask = vmx_set_nmi_mask,
	.enable_nmi_winकरोw = vmx_enable_nmi_winकरोw,
	.enable_irq_winकरोw = vmx_enable_irq_winकरोw,
	.update_cr8_पूर्णांकercept = vmx_update_cr8_पूर्णांकercept,
	.set_भव_apic_mode = vmx_set_भव_apic_mode,
	.set_apic_access_page_addr = vmx_set_apic_access_page_addr,
	.refresh_apicv_exec_ctrl = vmx_refresh_apicv_exec_ctrl,
	.load_eoi_निकासmap = vmx_load_eoi_निकासmap,
	.apicv_post_state_restore = vmx_apicv_post_state_restore,
	.check_apicv_inhibit_reasons = vmx_check_apicv_inhibit_reasons,
	.hwapic_irr_update = vmx_hwapic_irr_update,
	.hwapic_isr_update = vmx_hwapic_isr_update,
	.guest_apic_has_पूर्णांकerrupt = vmx_guest_apic_has_पूर्णांकerrupt,
	.sync_pir_to_irr = vmx_sync_pir_to_irr,
	.deliver_posted_पूर्णांकerrupt = vmx_deliver_posted_पूर्णांकerrupt,
	.dy_apicv_has_pending_पूर्णांकerrupt = pi_has_pending_पूर्णांकerrupt,

	.set_tss_addr = vmx_set_tss_addr,
	.set_identity_map_addr = vmx_set_identity_map_addr,
	.get_mt_mask = vmx_get_mt_mask,

	.get_निकास_info = vmx_get_निकास_info,

	.vcpu_after_set_cpuid = vmx_vcpu_after_set_cpuid,

	.has_wbinvd_निकास = cpu_has_vmx_wbinvd_निकास,

	.ग_लिखो_l1_tsc_offset = vmx_ग_लिखो_l1_tsc_offset,

	.load_mmu_pgd = vmx_load_mmu_pgd,

	.check_पूर्णांकercept = vmx_check_पूर्णांकercept,
	.handle_निकास_irqoff = vmx_handle_निकास_irqoff,

	.request_immediate_निकास = vmx_request_immediate_निकास,

	.sched_in = vmx_sched_in,

	.cpu_dirty_log_size = PML_ENTITY_NUM,
	.update_cpu_dirty_logging = vmx_update_cpu_dirty_logging,

	.pre_block = vmx_pre_block,
	.post_block = vmx_post_block,

	.pmu_ops = &पूर्णांकel_pmu_ops,
	.nested_ops = &vmx_nested_ops,

	.update_pi_irte = pi_update_irte,
	.start_assignment = vmx_pi_start_assignment,

#अगर_घोषित CONFIG_X86_64
	.set_hv_समयr = vmx_set_hv_समयr,
	.cancel_hv_समयr = vmx_cancel_hv_समयr,
#पूर्ण_अगर

	.setup_mce = vmx_setup_mce,

	.smi_allowed = vmx_smi_allowed,
	.pre_enter_smm = vmx_pre_enter_smm,
	.pre_leave_smm = vmx_pre_leave_smm,
	.enable_smi_winकरोw = vmx_enable_smi_winकरोw,

	.can_emulate_inकाष्ठाion = vmx_can_emulate_inकाष्ठाion,
	.apic_init_संकेत_blocked = vmx_apic_init_संकेत_blocked,
	.migrate_समयrs = vmx_migrate_समयrs,

	.msr_filter_changed = vmx_msr_filter_changed,
	.complete_emulated_msr = kvm_complete_insn_gp,

	.vcpu_deliver_sipi_vector = kvm_vcpu_deliver_sipi_vector,
पूर्ण;

अटल __init व्योम vmx_setup_user_वापस_msrs(व्योम)
अणु

	/*
	 * Though SYSCALL is only supported in 64-bit mode on Intel CPUs, kvm
	 * will emulate SYSCALL in legacy mode अगर the venकरोr string in guest
	 * CPUID.0:अणुEBX,ECX,EDXपूर्ण is "AuthenticAMD" or "AMDisbetter!" To
	 * support this emulation, MSR_STAR is included in the list क्रम i386,
	 * but is never loaded पूर्णांकo hardware.  MSR_CSTAR is also never loaded
	 * पूर्णांकo hardware and is here purely क्रम emulation purposes.
	 */
	स्थिर u32 vmx_uret_msrs_list[] = अणु
	#अगर_घोषित CONFIG_X86_64
		MSR_SYSCALL_MASK, MSR_LSTAR, MSR_CSTAR,
	#पूर्ण_अगर
		MSR_EFER, MSR_TSC_AUX, MSR_STAR,
		MSR_IA32_TSX_CTRL,
	पूर्ण;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(vmx_uret_msrs_list) != MAX_NR_USER_RETURN_MSRS);

	क्रम (i = 0; i < ARRAY_SIZE(vmx_uret_msrs_list); ++i)
		kvm_add_user_वापस_msr(vmx_uret_msrs_list[i]);
पूर्ण

अटल __init पूर्णांक hardware_setup(व्योम)
अणु
	अचिन्हित दीर्घ host_bndcfgs;
	काष्ठा desc_ptr dt;
	पूर्णांक r, ept_lpage_level;

	store_idt(&dt);
	host_idt_base = dt.address;

	vmx_setup_user_वापस_msrs();

	अगर (setup_vmcs_config(&vmcs_config, &vmx_capability) < 0)
		वापस -EIO;

	अगर (boot_cpu_has(X86_FEATURE_NX))
		kvm_enable_efer_bits(EFER_NX);

	अगर (boot_cpu_has(X86_FEATURE_MPX)) अणु
		rdmsrl(MSR_IA32_BNDCFGS, host_bndcfgs);
		WARN_ONCE(host_bndcfgs, "KVM: BNDCFGS in host will be lost");
	पूर्ण

	अगर (!cpu_has_vmx_mpx())
		supported_xcr0 &= ~(XFEATURE_MASK_BNDREGS |
				    XFEATURE_MASK_BNDCSR);

	अगर (!cpu_has_vmx_vpid() || !cpu_has_vmx_invvpid() ||
	    !(cpu_has_vmx_invvpid_single() || cpu_has_vmx_invvpid_global()))
		enable_vpid = 0;

	अगर (!cpu_has_vmx_ept() ||
	    !cpu_has_vmx_ept_4levels() ||
	    !cpu_has_vmx_ept_mt_wb() ||
	    !cpu_has_vmx_invept_global())
		enable_ept = 0;

	अगर (!cpu_has_vmx_ept_ad_bits() || !enable_ept)
		enable_ept_ad_bits = 0;

	अगर (!cpu_has_vmx_unrestricted_guest() || !enable_ept)
		enable_unrestricted_guest = 0;

	अगर (!cpu_has_vmx_flexpriority())
		flexpriority_enabled = 0;

	अगर (!cpu_has_भव_nmis())
		enable_vnmi = 0;

	/*
	 * set_apic_access_page_addr() is used to reload apic access
	 * page upon invalidation.  No need to करो anything अगर not
	 * using the APIC_ACCESS_ADDR VMCS field.
	 */
	अगर (!flexpriority_enabled)
		vmx_x86_ops.set_apic_access_page_addr = शून्य;

	अगर (!cpu_has_vmx_tpr_shaकरोw())
		vmx_x86_ops.update_cr8_पूर्णांकercept = शून्य;

#अगर IS_ENABLED(CONFIG_HYPERV)
	अगर (ms_hyperv.nested_features & HV_X64_NESTED_GUEST_MAPPING_FLUSH
	    && enable_ept) अणु
		vmx_x86_ops.tlb_remote_flush = hv_remote_flush_tlb;
		vmx_x86_ops.tlb_remote_flush_with_range =
				hv_remote_flush_tlb_with_range;
	पूर्ण
#पूर्ण_अगर

	अगर (!cpu_has_vmx_ple()) अणु
		ple_gap = 0;
		ple_winकरोw = 0;
		ple_winकरोw_grow = 0;
		ple_winकरोw_max = 0;
		ple_winकरोw_shrink = 0;
	पूर्ण

	अगर (!cpu_has_vmx_apicv()) अणु
		enable_apicv = 0;
		vmx_x86_ops.sync_pir_to_irr = शून्य;
	पूर्ण

	अगर (cpu_has_vmx_tsc_scaling()) अणु
		kvm_has_tsc_control = true;
		kvm_max_tsc_scaling_ratio = KVM_VMX_TSC_MULTIPLIER_MAX;
		kvm_tsc_scaling_ratio_frac_bits = 48;
	पूर्ण

	kvm_has_bus_lock_निकास = cpu_has_vmx_bus_lock_detection();

	set_bit(0, vmx_vpid_biपंचांगap); /* 0 is reserved क्रम host */

	अगर (enable_ept)
		kvm_mmu_set_ept_masks(enable_ept_ad_bits,
				      cpu_has_vmx_ept_execute_only());

	अगर (!enable_ept)
		ept_lpage_level = 0;
	अन्यथा अगर (cpu_has_vmx_ept_1g_page())
		ept_lpage_level = PG_LEVEL_1G;
	अन्यथा अगर (cpu_has_vmx_ept_2m_page())
		ept_lpage_level = PG_LEVEL_2M;
	अन्यथा
		ept_lpage_level = PG_LEVEL_4K;
	kvm_configure_mmu(enable_ept, vmx_get_max_tdp_level(), ept_lpage_level);

	/*
	 * Only enable PML when hardware supports PML feature, and both EPT
	 * and EPT A/D bit features are enabled -- PML depends on them to work.
	 */
	अगर (!enable_ept || !enable_ept_ad_bits || !cpu_has_vmx_pml())
		enable_pml = 0;

	अगर (!enable_pml)
		vmx_x86_ops.cpu_dirty_log_size = 0;

	अगर (!cpu_has_vmx_preemption_समयr())
		enable_preemption_समयr = false;

	अगर (enable_preemption_समयr) अणु
		u64 use_समयr_freq = 5000ULL * 1000 * 1000;
		u64 vmx_msr;

		rdmsrl(MSR_IA32_VMX_MISC, vmx_msr);
		cpu_preemption_समयr_multi =
			vmx_msr & VMX_MISC_PREEMPTION_TIMER_RATE_MASK;

		अगर (tsc_khz)
			use_समयr_freq = (u64)tsc_khz * 1000;
		use_समयr_freq >>= cpu_preemption_समयr_multi;

		/*
		 * KVM "disables" the preemption समयr by setting it to its max
		 * value.  Don't use the समयr अगर it might cause spurious निकासs
		 * at a rate faster than 0.1 Hz (of unपूर्णांकerrupted guest समय).
		 */
		अगर (use_समयr_freq > 0xffffffffu / 10)
			enable_preemption_समयr = false;
	पूर्ण

	अगर (!enable_preemption_समयr) अणु
		vmx_x86_ops.set_hv_समयr = शून्य;
		vmx_x86_ops.cancel_hv_समयr = शून्य;
		vmx_x86_ops.request_immediate_निकास = __kvm_request_immediate_निकास;
	पूर्ण

	kvm_set_posted_पूर्णांकr_wakeup_handler(pi_wakeup_handler);

	kvm_mce_cap_supported |= MCG_LMCE_P;

	अगर (pt_mode != PT_MODE_SYSTEM && pt_mode != PT_MODE_HOST_GUEST)
		वापस -EINVAL;
	अगर (!enable_ept || !cpu_has_vmx_पूर्णांकel_pt())
		pt_mode = PT_MODE_SYSTEM;

	setup_शेष_sgx_lepubkeyhash();

	अगर (nested) अणु
		nested_vmx_setup_ctls_msrs(&vmcs_config.nested,
					   vmx_capability.ept);

		r = nested_vmx_hardware_setup(kvm_vmx_निकास_handlers);
		अगर (r)
			वापस r;
	पूर्ण

	vmx_set_cpu_caps();

	r = alloc_kvm_area();
	अगर (r)
		nested_vmx_hardware_unsetup();
	वापस r;
पूर्ण

अटल काष्ठा kvm_x86_init_ops vmx_init_ops __initdata = अणु
	.cpu_has_kvm_support = cpu_has_kvm_support,
	.disabled_by_bios = vmx_disabled_by_bios,
	.check_processor_compatibility = vmx_check_processor_compat,
	.hardware_setup = hardware_setup,

	.runसमय_ops = &vmx_x86_ops,
पूर्ण;

अटल व्योम vmx_cleanup_l1d_flush(व्योम)
अणु
	अगर (vmx_l1d_flush_pages) अणु
		मुक्त_pages((अचिन्हित दीर्घ)vmx_l1d_flush_pages, L1D_CACHE_ORDER);
		vmx_l1d_flush_pages = शून्य;
	पूर्ण
	/* Restore state so sysfs ignores VMX */
	l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_AUTO;
पूर्ण

अटल व्योम vmx_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_KEXEC_CORE
	RCU_INIT_POINTER(crash_vmclear_loaded_vmcss, शून्य);
	synchronize_rcu();
#पूर्ण_अगर

	kvm_निकास();

#अगर IS_ENABLED(CONFIG_HYPERV)
	अगर (अटल_branch_unlikely(&enable_evmcs)) अणु
		पूर्णांक cpu;
		काष्ठा hv_vp_assist_page *vp_ap;
		/*
		 * Reset everything to support using non-enlightened VMCS
		 * access later (e.g. when we reload the module with
		 * enlightened_vmcs=0)
		 */
		क्रम_each_online_cpu(cpu) अणु
			vp_ap =	hv_get_vp_assist_page(cpu);

			अगर (!vp_ap)
				जारी;

			vp_ap->nested_control.features.directhypercall = 0;
			vp_ap->current_nested_vmcs = 0;
			vp_ap->enlighten_vmentry = 0;
		पूर्ण

		अटल_branch_disable(&enable_evmcs);
	पूर्ण
#पूर्ण_अगर
	vmx_cleanup_l1d_flush();
पूर्ण
module_निकास(vmx_निकास);

अटल पूर्णांक __init vmx_init(व्योम)
अणु
	पूर्णांक r, cpu;

#अगर IS_ENABLED(CONFIG_HYPERV)
	/*
	 * Enlightened VMCS usage should be recommended and the host needs
	 * to support eVMCS v1 or above. We can also disable eVMCS support
	 * with module parameter.
	 */
	अगर (enlightened_vmcs &&
	    ms_hyperv.hपूर्णांकs & HV_X64_ENLIGHTENED_VMCS_RECOMMENDED &&
	    (ms_hyperv.nested_features & HV_X64_ENLIGHTENED_VMCS_VERSION) >=
	    KVM_EVMCS_VERSION) अणु
		पूर्णांक cpu;

		/* Check that we have assist pages on all online CPUs */
		क्रम_each_online_cpu(cpu) अणु
			अगर (!hv_get_vp_assist_page(cpu)) अणु
				enlightened_vmcs = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (enlightened_vmcs) अणु
			pr_info("KVM: vmx: using Hyper-V Enlightened VMCS\n");
			अटल_branch_enable(&enable_evmcs);
		पूर्ण

		अगर (ms_hyperv.nested_features & HV_X64_NESTED_सूचीECT_FLUSH)
			vmx_x86_ops.enable_direct_tlbflush
				= hv_enable_direct_tlbflush;

	पूर्ण अन्यथा अणु
		enlightened_vmcs = false;
	पूर्ण
#पूर्ण_अगर

	r = kvm_init(&vmx_init_ops, माप(काष्ठा vcpu_vmx),
		     __alignof__(काष्ठा vcpu_vmx), THIS_MODULE);
	अगर (r)
		वापस r;

	/*
	 * Must be called after kvm_init() so enable_ept is properly set
	 * up. Hand the parameter mitigation value in which was stored in
	 * the pre module init parser. If no parameter was given, it will
	 * contain 'auto' which will be turned into the default 'cond'
	 * mitigation mode.
	 */
	r = vmx_setup_l1d_flush(vmentry_l1d_flush_param);
	अगर (r) अणु
		vmx_निकास();
		वापस r;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		INIT_LIST_HEAD(&per_cpu(loaded_vmcss_on_cpu, cpu));

		pi_init_cpu(cpu);
	पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
	rcu_assign_poपूर्णांकer(crash_vmclear_loaded_vmcss,
			   crash_vmclear_local_loaded_vmcss);
#पूर्ण_अगर
	vmx_check_vmcs12_offsets();

	/*
	 * Shaकरोw paging करोesn't have a (further) perक्रमmance penalty
	 * from GUEST_MAXPHYADDR < HOST_MAXPHYADDR so enable it
	 * by शेष
	 */
	अगर (!enable_ept)
		allow_smaller_maxphyaddr = true;

	वापस 0;
पूर्ण
module_init(vmx_init);
