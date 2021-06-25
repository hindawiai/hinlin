<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KVM_PARA_H
#घोषणा _ASM_X86_KVM_PARA_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/alternative.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <uapi/यंत्र/kvm_para.h>

#अगर_घोषित CONFIG_KVM_GUEST
bool kvm_check_and_clear_guest_छोड़ोd(व्योम);
#अन्यथा
अटल अंतरभूत bool kvm_check_and_clear_guest_छोड़ोd(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_GUEST */

#घोषणा KVM_HYPERCALL \
        ALTERNATIVE("vmcall", "vmmcall", X86_FEATURE_VMMCALL)

/* For KVM hypercalls, a three-byte sequence of either the vmcall or the vmmcall
 * inकाष्ठाion.  The hypervisor may replace it with something अन्यथा but only the
 * inकाष्ठाions are guaranteed to be supported.
 *
 * Up to four arguments may be passed in rbx, rcx, rdx, and rsi respectively.
 * The hypercall number should be placed in rax and the वापस value will be
 * placed in rax.  No other रेजिस्टरs will be clobbered unless explicitly
 * noted by the particular hypercall.
 */

अटल अंतरभूत दीर्घ kvm_hypercall0(अचिन्हित पूर्णांक nr)
अणु
	दीर्घ ret;
	यंत्र अस्थिर(KVM_HYPERCALL
		     : "=a"(ret)
		     : "a"(nr)
		     : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ kvm_hypercall1(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1)
अणु
	दीर्घ ret;
	यंत्र अस्थिर(KVM_HYPERCALL
		     : "=a"(ret)
		     : "a"(nr), "b"(p1)
		     : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ kvm_hypercall2(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				  अचिन्हित दीर्घ p2)
अणु
	दीर्घ ret;
	यंत्र अस्थिर(KVM_HYPERCALL
		     : "=a"(ret)
		     : "a"(nr), "b"(p1), "c"(p2)
		     : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ kvm_hypercall3(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				  अचिन्हित दीर्घ p2, अचिन्हित दीर्घ p3)
अणु
	दीर्घ ret;
	यंत्र अस्थिर(KVM_HYPERCALL
		     : "=a"(ret)
		     : "a"(nr), "b"(p1), "c"(p2), "d"(p3)
		     : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ kvm_hypercall4(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				  अचिन्हित दीर्घ p2, अचिन्हित दीर्घ p3,
				  अचिन्हित दीर्घ p4)
अणु
	दीर्घ ret;
	यंत्र अस्थिर(KVM_HYPERCALL
		     : "=a"(ret)
		     : "a"(nr), "b"(p1), "c"(p2), "d"(p3), "S"(p4)
		     : "memory");
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_KVM_GUEST
व्योम kvmघड़ी_init(व्योम);
व्योम kvmघड़ी_disable(व्योम);
bool kvm_para_available(व्योम);
अचिन्हित पूर्णांक kvm_arch_para_features(व्योम);
अचिन्हित पूर्णांक kvm_arch_para_hपूर्णांकs(व्योम);
व्योम kvm_async_pf_task_रुको_schedule(u32 token);
व्योम kvm_async_pf_task_wake(u32 token);
u32 kvm_पढ़ो_and_reset_apf_flags(व्योम);
bool __kvm_handle_async_pf(काष्ठा pt_regs *regs, u32 token);

DECLARE_STATIC_KEY_FALSE(kvm_async_pf_enabled);

अटल __always_अंतरभूत bool kvm_handle_async_pf(काष्ठा pt_regs *regs, u32 token)
अणु
	अगर (अटल_branch_unlikely(&kvm_async_pf_enabled))
		वापस __kvm_handle_async_pf(regs, token);
	अन्यथा
		वापस false;
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
व्योम __init kvm_spinlock_init(व्योम);
#अन्यथा /* !CONFIG_PARAVIRT_SPINLOCKS */
अटल अंतरभूत व्योम kvm_spinlock_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PARAVIRT_SPINLOCKS */

#अन्यथा /* CONFIG_KVM_GUEST */
#घोषणा kvm_async_pf_task_रुको_schedule(T) करो अणुपूर्ण जबतक(0)
#घोषणा kvm_async_pf_task_wake(T) करो अणुपूर्ण जबतक(0)

अटल अंतरभूत bool kvm_para_available(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_arch_para_features(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kvm_arch_para_hपूर्णांकs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 kvm_पढ़ो_and_reset_apf_flags(व्योम)
अणु
	वापस 0;
पूर्ण

अटल __always_अंतरभूत bool kvm_handle_async_pf(काष्ठा pt_regs *regs, u32 token)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_KVM_PARA_H */
