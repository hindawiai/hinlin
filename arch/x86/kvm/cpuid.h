<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_X86_KVM_CPUID_H
#घोषणा ARCH_X86_KVM_CPUID_H

#समावेश "x86.h"
#समावेश "reverse_cpuid.h"
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/processor.h>
#समावेश <uapi/यंत्र/kvm_para.h>

बाह्य u32 kvm_cpu_caps[NR_KVM_CPU_CAPS] __पढ़ो_mostly;
व्योम kvm_set_cpu_caps(व्योम);

व्योम kvm_update_cpuid_runसमय(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_update_pv_runसमय(काष्ठा kvm_vcpu *vcpu);
काष्ठा kvm_cpuid_entry2 *kvm_find_cpuid_entry(काष्ठा kvm_vcpu *vcpu,
					      u32 function, u32 index);
पूर्णांक kvm_dev_ioctl_get_cpuid(काष्ठा kvm_cpuid2 *cpuid,
			    काष्ठा kvm_cpuid_entry2 __user *entries,
			    अचिन्हित पूर्णांक type);
पूर्णांक kvm_vcpu_ioctl_set_cpuid(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_cpuid *cpuid,
			     काष्ठा kvm_cpuid_entry __user *entries);
पूर्णांक kvm_vcpu_ioctl_set_cpuid2(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_cpuid2 *cpuid,
			      काष्ठा kvm_cpuid_entry2 __user *entries);
पूर्णांक kvm_vcpu_ioctl_get_cpuid2(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_cpuid2 *cpuid,
			      काष्ठा kvm_cpuid_entry2 __user *entries);
bool kvm_cpuid(काष्ठा kvm_vcpu *vcpu, u32 *eax, u32 *ebx,
	       u32 *ecx, u32 *edx, bool exact_only);

पूर्णांक cpuid_query_maxphyaddr(काष्ठा kvm_vcpu *vcpu);
u64 kvm_vcpu_reserved_gpa_bits_raw(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत पूर्णांक cpuid_maxphyaddr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.maxphyaddr;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_is_legal_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	वापस !(gpa & vcpu->arch.reserved_gpa_bits);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_is_illegal_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	वापस !kvm_vcpu_is_legal_gpa(vcpu, gpa);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_is_legal_aligned_gpa(काष्ठा kvm_vcpu *vcpu,
						 gpa_t gpa, gpa_t alignment)
अणु
	वापस IS_ALIGNED(gpa, alignment) && kvm_vcpu_is_legal_gpa(vcpu, gpa);
पूर्ण

अटल अंतरभूत bool page_address_valid(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	वापस kvm_vcpu_is_legal_aligned_gpa(vcpu, gpa, PAGE_SIZE);
पूर्ण

अटल __always_अंतरभूत व्योम cpuid_entry_override(काष्ठा kvm_cpuid_entry2 *entry,
						 अचिन्हित पूर्णांक leaf)
अणु
	u32 *reg = cpuid_entry_get_reg(entry, leaf * 32);

	BUILD_BUG_ON(leaf >= ARRAY_SIZE(kvm_cpu_caps));
	*reg = kvm_cpu_caps[leaf];
पूर्ण

अटल __always_अंतरभूत u32 *guest_cpuid_get_रेजिस्टर(काष्ठा kvm_vcpu *vcpu,
						     अचिन्हित पूर्णांक x86_feature)
अणु
	स्थिर काष्ठा cpuid_reg cpuid = x86_feature_cpuid(x86_feature);
	काष्ठा kvm_cpuid_entry2 *entry;

	entry = kvm_find_cpuid_entry(vcpu, cpuid.function, cpuid.index);
	अगर (!entry)
		वापस शून्य;

	वापस __cpuid_entry_get_reg(entry, cpuid.reg);
पूर्ण

अटल __always_अंतरभूत bool guest_cpuid_has(काष्ठा kvm_vcpu *vcpu,
					    अचिन्हित पूर्णांक x86_feature)
अणु
	u32 *reg;

	reg = guest_cpuid_get_रेजिस्टर(vcpu, x86_feature);
	अगर (!reg)
		वापस false;

	वापस *reg & __feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम guest_cpuid_clear(काष्ठा kvm_vcpu *vcpu,
					      अचिन्हित पूर्णांक x86_feature)
अणु
	u32 *reg;

	reg = guest_cpuid_get_रेजिस्टर(vcpu, x86_feature);
	अगर (reg)
		*reg &= ~__feature_bit(x86_feature);
पूर्ण

अटल अंतरभूत bool guest_cpuid_is_amd_or_hygon(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0, 0);
	वापस best &&
	       (is_guest_venकरोr_amd(best->ebx, best->ecx, best->edx) ||
		is_guest_venकरोr_hygon(best->ebx, best->ecx, best->edx));
पूर्ण

अटल अंतरभूत bool guest_cpuid_is_पूर्णांकel(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0, 0);
	वापस best && is_guest_venकरोr_पूर्णांकel(best->ebx, best->ecx, best->edx);
पूर्ण

अटल अंतरभूत पूर्णांक guest_cpuid_family(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0x1, 0);
	अगर (!best)
		वापस -1;

	वापस x86_family(best->eax);
पूर्ण

अटल अंतरभूत पूर्णांक guest_cpuid_model(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0x1, 0);
	अगर (!best)
		वापस -1;

	वापस x86_model(best->eax);
पूर्ण

अटल अंतरभूत पूर्णांक guest_cpuid_stepping(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0x1, 0);
	अगर (!best)
		वापस -1;

	वापस x86_stepping(best->eax);
पूर्ण

अटल अंतरभूत bool guest_has_spec_ctrl_msr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (guest_cpuid_has(vcpu, X86_FEATURE_SPEC_CTRL) ||
		guest_cpuid_has(vcpu, X86_FEATURE_AMD_STIBP) ||
		guest_cpuid_has(vcpu, X86_FEATURE_AMD_IBRS) ||
		guest_cpuid_has(vcpu, X86_FEATURE_AMD_SSBD));
पूर्ण

अटल अंतरभूत bool guest_has_pred_cmd_msr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (guest_cpuid_has(vcpu, X86_FEATURE_SPEC_CTRL) ||
		guest_cpuid_has(vcpu, X86_FEATURE_AMD_IBPB));
पूर्ण

अटल अंतरभूत bool supports_cpuid_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.msr_platक्रमm_info & MSR_PLATFORM_INFO_CPUID_FAULT;
पूर्ण

अटल अंतरभूत bool cpuid_fault_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.msr_misc_features_enables &
		  MSR_MISC_FEATURES_ENABLES_CPUID_FAULT;
पूर्ण

अटल __always_अंतरभूत व्योम kvm_cpu_cap_clear(अचिन्हित पूर्णांक x86_feature)
अणु
	अचिन्हित पूर्णांक x86_leaf = __feature_leaf(x86_feature);

	reverse_cpuid_check(x86_leaf);
	kvm_cpu_caps[x86_leaf] &= ~__feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_cpu_cap_set(अचिन्हित पूर्णांक x86_feature)
अणु
	अचिन्हित पूर्णांक x86_leaf = __feature_leaf(x86_feature);

	reverse_cpuid_check(x86_leaf);
	kvm_cpu_caps[x86_leaf] |= __feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत u32 kvm_cpu_cap_get(अचिन्हित पूर्णांक x86_feature)
अणु
	अचिन्हित पूर्णांक x86_leaf = __feature_leaf(x86_feature);

	reverse_cpuid_check(x86_leaf);
	वापस kvm_cpu_caps[x86_leaf] & __feature_bit(x86_feature);
पूर्ण

अटल __always_अंतरभूत bool kvm_cpu_cap_has(अचिन्हित पूर्णांक x86_feature)
अणु
	वापस !!kvm_cpu_cap_get(x86_feature);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_cpu_cap_check_and_set(अचिन्हित पूर्णांक x86_feature)
अणु
	अगर (boot_cpu_has(x86_feature))
		kvm_cpu_cap_set(x86_feature);
पूर्ण

अटल __always_अंतरभूत bool guest_pv_has(काष्ठा kvm_vcpu *vcpu,
					 अचिन्हित पूर्णांक kvm_feature)
अणु
	अगर (!vcpu->arch.pv_cpuid.enक्रमce)
		वापस true;

	वापस vcpu->arch.pv_cpuid.features & (1u << kvm_feature);
पूर्ण

#पूर्ण_अगर
