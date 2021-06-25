<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_KVM_CACHE_REGS_H
#घोषणा ASM_KVM_CACHE_REGS_H

#समावेश <linux/kvm_host.h>

#घोषणा KVM_POSSIBLE_CR0_GUEST_BITS X86_CR0_TS
#घोषणा KVM_POSSIBLE_CR4_GUEST_BITS				  \
	(X86_CR4_PVI | X86_CR4_DE | X86_CR4_PCE | X86_CR4_OSFXSR  \
	 | X86_CR4_OSXMMEXCPT | X86_CR4_PGE | X86_CR4_TSD | X86_CR4_FSGSBASE)

#घोषणा BUILD_KVM_GPR_ACCESSORS(lname, uname)				      \
अटल __always_अंतरभूत अचिन्हित दीर्घ kvm_##lname##_पढ़ो(काष्ठा kvm_vcpu *vcpu)\
अणु									      \
	वापस vcpu->arch.regs[VCPU_REGS_##uname];			      \
पूर्ण									      \
अटल __always_अंतरभूत व्योम kvm_##lname##_ग_लिखो(काष्ठा kvm_vcpu *vcpu,	      \
						अचिन्हित दीर्घ val)	      \
अणु									      \
	vcpu->arch.regs[VCPU_REGS_##uname] = val;			      \
पूर्ण
BUILD_KVM_GPR_ACCESSORS(rax, RAX)
BUILD_KVM_GPR_ACCESSORS(rbx, RBX)
BUILD_KVM_GPR_ACCESSORS(rcx, RCX)
BUILD_KVM_GPR_ACCESSORS(rdx, RDX)
BUILD_KVM_GPR_ACCESSORS(rbp, RBP)
BUILD_KVM_GPR_ACCESSORS(rsi, RSI)
BUILD_KVM_GPR_ACCESSORS(rdi, RDI)
#अगर_घोषित CONFIG_X86_64
BUILD_KVM_GPR_ACCESSORS(r8,  R8)
BUILD_KVM_GPR_ACCESSORS(r9,  R9)
BUILD_KVM_GPR_ACCESSORS(r10, R10)
BUILD_KVM_GPR_ACCESSORS(r11, R11)
BUILD_KVM_GPR_ACCESSORS(r12, R12)
BUILD_KVM_GPR_ACCESSORS(r13, R13)
BUILD_KVM_GPR_ACCESSORS(r14, R14)
BUILD_KVM_GPR_ACCESSORS(r15, R15)
#पूर्ण_अगर

अटल अंतरभूत bool kvm_रेजिस्टर_is_available(काष्ठा kvm_vcpu *vcpu,
					     क्रमागत kvm_reg reg)
अणु
	वापस test_bit(reg, (अचिन्हित दीर्घ *)&vcpu->arch.regs_avail);
पूर्ण

अटल अंतरभूत bool kvm_रेजिस्टर_is_dirty(काष्ठा kvm_vcpu *vcpu,
					 क्रमागत kvm_reg reg)
अणु
	वापस test_bit(reg, (अचिन्हित दीर्घ *)&vcpu->arch.regs_dirty);
पूर्ण

अटल अंतरभूत व्योम kvm_रेजिस्टर_mark_available(काष्ठा kvm_vcpu *vcpu,
					       क्रमागत kvm_reg reg)
अणु
	__set_bit(reg, (अचिन्हित दीर्घ *)&vcpu->arch.regs_avail);
पूर्ण

अटल अंतरभूत व्योम kvm_रेजिस्टर_mark_dirty(काष्ठा kvm_vcpu *vcpu,
					   क्रमागत kvm_reg reg)
अणु
	__set_bit(reg, (अचिन्हित दीर्घ *)&vcpu->arch.regs_avail);
	__set_bit(reg, (अचिन्हित दीर्घ *)&vcpu->arch.regs_dirty);
पूर्ण

/*
 * The "raw" रेजिस्टर helpers are only क्रम हालs where the full 64 bits of a
 * रेजिस्टर are पढ़ो/written irrespective of current vCPU mode.  In other words,
 * odds are good you shouldn't be using the raw variants.
 */
अटल अंतरभूत अचिन्हित दीर्घ kvm_रेजिस्टर_पढ़ो_raw(काष्ठा kvm_vcpu *vcpu, पूर्णांक reg)
अणु
	अगर (WARN_ON_ONCE((अचिन्हित पूर्णांक)reg >= NR_VCPU_REGS))
		वापस 0;

	अगर (!kvm_रेजिस्टर_is_available(vcpu, reg))
		अटल_call(kvm_x86_cache_reg)(vcpu, reg);

	वापस vcpu->arch.regs[reg];
पूर्ण

अटल अंतरभूत व्योम kvm_रेजिस्टर_ग_लिखो_raw(काष्ठा kvm_vcpu *vcpu, पूर्णांक reg,
					  अचिन्हित दीर्घ val)
अणु
	अगर (WARN_ON_ONCE((अचिन्हित पूर्णांक)reg >= NR_VCPU_REGS))
		वापस;

	vcpu->arch.regs[reg] = val;
	kvm_रेजिस्टर_mark_dirty(vcpu, reg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_rip_पढ़ो(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_रेजिस्टर_पढ़ो_raw(vcpu, VCPU_REGS_RIP);
पूर्ण

अटल अंतरभूत व्योम kvm_rip_ग_लिखो(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	kvm_रेजिस्टर_ग_लिखो_raw(vcpu, VCPU_REGS_RIP, val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_rsp_पढ़ो(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_रेजिस्टर_पढ़ो_raw(vcpu, VCPU_REGS_RSP);
पूर्ण

अटल अंतरभूत व्योम kvm_rsp_ग_लिखो(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	kvm_रेजिस्टर_ग_लिखो_raw(vcpu, VCPU_REGS_RSP, val);
पूर्ण

अटल अंतरभूत u64 kvm_pdptr_पढ़ो(काष्ठा kvm_vcpu *vcpu, पूर्णांक index)
अणु
	might_sleep();  /* on svm */

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_PDPTR))
		अटल_call(kvm_x86_cache_reg)(vcpu, VCPU_EXREG_PDPTR);

	वापस vcpu->arch.walk_mmu->pdptrs[index];
पूर्ण

अटल अंतरभूत uदीर्घ kvm_पढ़ो_cr0_bits(काष्ठा kvm_vcpu *vcpu, uदीर्घ mask)
अणु
	uदीर्घ पंचांगask = mask & KVM_POSSIBLE_CR0_GUEST_BITS;
	अगर ((पंचांगask & vcpu->arch.cr0_guest_owned_bits) &&
	    !kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_CR0))
		अटल_call(kvm_x86_cache_reg)(vcpu, VCPU_EXREG_CR0);
	वापस vcpu->arch.cr0 & mask;
पूर्ण

अटल अंतरभूत uदीर्घ kvm_पढ़ो_cr0(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr0_bits(vcpu, ~0UL);
पूर्ण

अटल अंतरभूत uदीर्घ kvm_पढ़ो_cr4_bits(काष्ठा kvm_vcpu *vcpu, uदीर्घ mask)
अणु
	uदीर्घ पंचांगask = mask & KVM_POSSIBLE_CR4_GUEST_BITS;
	अगर ((पंचांगask & vcpu->arch.cr4_guest_owned_bits) &&
	    !kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_CR4))
		अटल_call(kvm_x86_cache_reg)(vcpu, VCPU_EXREG_CR4);
	वापस vcpu->arch.cr4 & mask;
पूर्ण

अटल अंतरभूत uदीर्घ kvm_पढ़ो_cr3(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_CR3))
		अटल_call(kvm_x86_cache_reg)(vcpu, VCPU_EXREG_CR3);
	वापस vcpu->arch.cr3;
पूर्ण

अटल अंतरभूत uदीर्घ kvm_पढ़ो_cr4(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr4_bits(vcpu, ~0UL);
पूर्ण

अटल अंतरभूत u64 kvm_पढ़ो_edx_eax(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (kvm_rax_पढ़ो(vcpu) & -1u)
		| ((u64)(kvm_rdx_पढ़ो(vcpu) & -1u) << 32);
पूर्ण

अटल अंतरभूत व्योम enter_guest_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hflags |= HF_GUEST_MASK;
पूर्ण

अटल अंतरभूत व्योम leave_guest_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.hflags &= ~HF_GUEST_MASK;

	अगर (vcpu->arch.load_eoi_निकासmap_pending) अणु
		vcpu->arch.load_eoi_निकासmap_pending = false;
		kvm_make_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu);
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_guest_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.hflags & HF_GUEST_MASK;
पूर्ण

अटल अंतरभूत bool is_smm(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.hflags & HF_SMM_MASK;
पूर्ण

#पूर्ण_अगर
