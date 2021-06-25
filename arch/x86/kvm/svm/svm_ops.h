<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_SVM_OPS_H
#घोषणा __KVM_X86_SVM_OPS_H

#समावेश <linux/compiler_types.h>

#समावेश <यंत्र/kvm_host.h>

#घोषणा svm_यंत्र(insn, clobber...)				\
करो अणु								\
	यंत्र_अस्थिर_जाओ("1: " __stringअगरy(insn) "\n\t"	\
			  _ASM_EXTABLE(1b, %l[fault])		\
			  ::: clobber : fault);			\
	वापस;							\
fault:								\
	kvm_spurious_fault();					\
पूर्ण जबतक (0)

#घोषणा svm_यंत्र1(insn, op1, clobber...)				\
करो अणु								\
	यंत्र_अस्थिर_जाओ("1: "  __stringअगरy(insn) " %0\n\t"	\
			  _ASM_EXTABLE(1b, %l[fault])		\
			  :: op1 : clobber : fault);		\
	वापस;							\
fault:								\
	kvm_spurious_fault();					\
पूर्ण जबतक (0)

#घोषणा svm_यंत्र2(insn, op1, op2, clobber...)				\
करो अणु									\
	यंत्र_अस्थिर_जाओ("1: "  __stringअगरy(insn) " %1, %0\n\t"	\
			  _ASM_EXTABLE(1b, %l[fault])			\
			  :: op1, op2 : clobber : fault);		\
	वापस;								\
fault:									\
	kvm_spurious_fault();						\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम clgi(व्योम)
अणु
	svm_यंत्र(clgi);
पूर्ण

अटल अंतरभूत व्योम stgi(व्योम)
अणु
	svm_यंत्र(stgi);
पूर्ण

अटल अंतरभूत व्योम invlpga(अचिन्हित दीर्घ addr, u32 asid)
अणु
	svm_यंत्र2(invlpga, "c"(asid), "a"(addr));
पूर्ण

/*
 * Despite being a physical address, the portion of rAX that is consumed by
 * VMSAVE, VMLOAD, etc... is still controlled by the effective address size,
 * hence 'unsigned long' instead of 'hpa_t'.
 */
अटल अंतरभूत व्योम vmsave(अचिन्हित दीर्घ pa)
अणु
	svm_यंत्र1(vmsave, "a" (pa), "memory");
पूर्ण

अटल अंतरभूत व्योम vmload(अचिन्हित दीर्घ pa)
अणु
	svm_यंत्र1(vmload, "a" (pa), "memory");
पूर्ण

#पूर्ण_अगर /* __KVM_X86_SVM_OPS_H */
