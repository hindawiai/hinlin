<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/tboot.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/vmx.h>
#समावेश "cpu.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"x86/cpu: " fmt

#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
क्रमागत vmx_feature_leafs अणु
	MISC_FEATURES = 0,
	PRIMARY_CTLS,
	SECONDARY_CTLS,
	NR_VMX_FEATURE_WORDS,
पूर्ण;

#घोषणा VMX_F(x) BIT(VMX_FEATURE_##x & 0x1f)

अटल व्योम init_vmx_capabilities(काष्ठा cpuinfo_x86 *c)
अणु
	u32 supported, funcs, ept, vpid, ign;

	BUILD_BUG_ON(NVMXINTS != NR_VMX_FEATURE_WORDS);

	/*
	 * The high bits contain the allowed-1 settings, i.e. features that can
	 * be turned on.  The low bits contain the allowed-0 settings, i.e.
	 * features that can be turned off.  Ignore the allowed-0 settings,
	 * अगर a feature can be turned on then it's supported.
	 *
	 * Use raw rdmsr() क्रम primary processor controls and pin controls MSRs
	 * as they exist on any CPU that supports VMX, i.e. we want the WARN अगर
	 * the RDMSR faults.
	 */
	rdmsr(MSR_IA32_VMX_PROCBASED_CTLS, ign, supported);
	c->vmx_capability[PRIMARY_CTLS] = supported;

	rdmsr_safe(MSR_IA32_VMX_PROCBASED_CTLS2, &ign, &supported);
	c->vmx_capability[SECONDARY_CTLS] = supported;

	rdmsr(MSR_IA32_VMX_PINBASED_CTLS, ign, supported);
	rdmsr_safe(MSR_IA32_VMX_VMFUNC, &ign, &funcs);

	/*
	 * Except क्रम EPT+VPID, which क्रमागतerates support क्रम both in a single
	 * MSR, low क्रम EPT, high क्रम VPID.
	 */
	rdmsr_safe(MSR_IA32_VMX_EPT_VPID_CAP, &ept, &vpid);

	/* Pin, EPT, VPID and VM-Func are merged पूर्णांकo a single word. */
	WARN_ON_ONCE(supported >> 16);
	WARN_ON_ONCE(funcs >> 4);
	c->vmx_capability[MISC_FEATURES] = (supported & 0xffff) |
					   ((vpid & 0x1) << 16) |
					   ((funcs & 0xf) << 28);

	/* EPT bits are full on scattered and must be manually handled. */
	अगर (ept & VMX_EPT_EXECUTE_ONLY_BIT)
		c->vmx_capability[MISC_FEATURES] |= VMX_F(EPT_EXECUTE_ONLY);
	अगर (ept & VMX_EPT_AD_BIT)
		c->vmx_capability[MISC_FEATURES] |= VMX_F(EPT_AD);
	अगर (ept & VMX_EPT_1GB_PAGE_BIT)
		c->vmx_capability[MISC_FEATURES] |= VMX_F(EPT_1GB);

	/* Synthetic APIC features that are aggregates of multiple features. */
	अगर ((c->vmx_capability[PRIMARY_CTLS] & VMX_F(VIRTUAL_TPR)) &&
	    (c->vmx_capability[SECONDARY_CTLS] & VMX_F(VIRT_APIC_ACCESSES)))
		c->vmx_capability[MISC_FEATURES] |= VMX_F(FLEXPRIORITY);

	अगर ((c->vmx_capability[PRIMARY_CTLS] & VMX_F(VIRTUAL_TPR)) &&
	    (c->vmx_capability[SECONDARY_CTLS] & VMX_F(APIC_REGISTER_VIRT)) &&
	    (c->vmx_capability[SECONDARY_CTLS] & VMX_F(VIRT_INTR_DELIVERY)) &&
	    (c->vmx_capability[MISC_FEATURES] & VMX_F(POSTED_INTR)))
		c->vmx_capability[MISC_FEATURES] |= VMX_F(APICV);

	/* Set the synthetic cpufeatures to preserve /proc/cpuinfo's ABI. */
	अगर (c->vmx_capability[PRIMARY_CTLS] & VMX_F(VIRTUAL_TPR))
		set_cpu_cap(c, X86_FEATURE_TPR_SHADOW);
	अगर (c->vmx_capability[MISC_FEATURES] & VMX_F(FLEXPRIORITY))
		set_cpu_cap(c, X86_FEATURE_FLEXPRIORITY);
	अगर (c->vmx_capability[MISC_FEATURES] & VMX_F(VIRTUAL_NMIS))
		set_cpu_cap(c, X86_FEATURE_VNMI);
	अगर (c->vmx_capability[SECONDARY_CTLS] & VMX_F(EPT))
		set_cpu_cap(c, X86_FEATURE_EPT);
	अगर (c->vmx_capability[MISC_FEATURES] & VMX_F(EPT_AD))
		set_cpu_cap(c, X86_FEATURE_EPT_AD);
	अगर (c->vmx_capability[MISC_FEATURES] & VMX_F(VPID))
		set_cpu_cap(c, X86_FEATURE_VPID);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_VMX_FEATURE_NAMES */

अटल पूर्णांक __init nosgx(अक्षर *str)
अणु
	setup_clear_cpu_cap(X86_FEATURE_SGX);

	वापस 0;
पूर्ण

early_param("nosgx", nosgx);

व्योम init_ia32_feat_ctl(काष्ठा cpuinfo_x86 *c)
अणु
	bool enable_sgx_kvm = false, enable_sgx_driver = false;
	bool tboot = tboot_enabled();
	bool enable_vmx;
	u64 msr;

	अगर (rdmsrl_safe(MSR_IA32_FEAT_CTL, &msr)) अणु
		clear_cpu_cap(c, X86_FEATURE_VMX);
		clear_cpu_cap(c, X86_FEATURE_SGX);
		वापस;
	पूर्ण

	enable_vmx = cpu_has(c, X86_FEATURE_VMX) &&
		     IS_ENABLED(CONFIG_KVM_INTEL);

	अगर (cpu_has(c, X86_FEATURE_SGX) && IS_ENABLED(CONFIG_X86_SGX)) अणु
		/*
		 * Separate out SGX driver enabling from KVM.  This allows KVM
		 * guests to use SGX even अगर the kernel SGX driver refuses to
		 * use it.  This happens अगर flexible Launch Control is not
		 * available.
		 */
		enable_sgx_driver = cpu_has(c, X86_FEATURE_SGX_LC);
		enable_sgx_kvm = enable_vmx && IS_ENABLED(CONFIG_X86_SGX_KVM);
	पूर्ण

	अगर (msr & FEAT_CTL_LOCKED)
		जाओ update_caps;

	/*
	 * Ignore whatever value BIOS left in the MSR to aव्योम enabling अक्रमom
	 * features or faulting on the WRMSR.
	 */
	msr = FEAT_CTL_LOCKED;

	/*
	 * Enable VMX अगर and only अगर the kernel may करो VMXON at some poपूर्णांक,
	 * i.e. KVM is enabled, to aव्योम unnecessarily adding an attack vector
	 * क्रम the kernel, e.g. using VMX to hide malicious code.
	 */
	अगर (enable_vmx) अणु
		msr |= FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX;

		अगर (tboot)
			msr |= FEAT_CTL_VMX_ENABLED_INSIDE_SMX;
	पूर्ण

	अगर (enable_sgx_kvm || enable_sgx_driver) अणु
		msr |= FEAT_CTL_SGX_ENABLED;
		अगर (enable_sgx_driver)
			msr |= FEAT_CTL_SGX_LC_ENABLED;
	पूर्ण

	wrmsrl(MSR_IA32_FEAT_CTL, msr);

update_caps:
	set_cpu_cap(c, X86_FEATURE_MSR_IA32_FEAT_CTL);

	अगर (!cpu_has(c, X86_FEATURE_VMX))
		जाओ update_sgx;

	अगर ( (tboot && !(msr & FEAT_CTL_VMX_ENABLED_INSIDE_SMX)) ||
	    (!tboot && !(msr & FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX))) अणु
		अगर (IS_ENABLED(CONFIG_KVM_INTEL))
			pr_err_once("VMX (%s TXT) disabled by BIOS\n",
				    tboot ? "inside" : "outside");
		clear_cpu_cap(c, X86_FEATURE_VMX);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
		init_vmx_capabilities(c);
#पूर्ण_अगर
	पूर्ण

update_sgx:
	अगर (!(msr & FEAT_CTL_SGX_ENABLED)) अणु
		अगर (enable_sgx_kvm || enable_sgx_driver)
			pr_err_once("SGX disabled by BIOS.\n");
		clear_cpu_cap(c, X86_FEATURE_SGX);
		वापस;
	पूर्ण

	/*
	 * VMX feature bit may be cleared due to being disabled in BIOS,
	 * in which हाल SGX भवization cannot be supported either.
	 */
	अगर (!cpu_has(c, X86_FEATURE_VMX) && enable_sgx_kvm) अणु
		pr_err_once("SGX virtualization disabled due to lack of VMX.\n");
		enable_sgx_kvm = 0;
	पूर्ण

	अगर (!(msr & FEAT_CTL_SGX_LC_ENABLED) && enable_sgx_driver) अणु
		अगर (!enable_sgx_kvm) अणु
			pr_err_once("SGX Launch Control is locked. Disable SGX.\n");
			clear_cpu_cap(c, X86_FEATURE_SGX);
		पूर्ण अन्यथा अणु
			pr_err_once("SGX Launch Control is locked. Support SGX virtualization only.\n");
			clear_cpu_cap(c, X86_FEATURE_SGX_LC);
		पूर्ण
	पूर्ण
पूर्ण
