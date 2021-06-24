<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_VM86_H
#घोषणा _ASM_X86_VM86_H

#समावेश <यंत्र/ptrace.h>
#समावेश <uapi/यंत्र/vm86.h>

/*
 * This is the (kernel) stack-layout when we have करोne a "SAVE_ALL" from vm86
 * mode - the मुख्य change is that the old segment descriptors aren't
 * useful any more and are क्रमced to be zero by the kernel (and the
 * hardware when a trap occurs), and the real segment descriptors are
 * at the end of the काष्ठाure. Look at ptrace.h to see the "normal"
 * setup. For user space layout see 'struct vm86_regs' above.
 */

काष्ठा kernel_vm86_regs अणु
/*
 * normal regs, with special meaning क्रम the segment descriptors..
 */
	काष्ठा pt_regs pt;
/*
 * these are specअगरic to v86 mode:
 */
	अचिन्हित लघु es, __esh;
	अचिन्हित लघु ds, __dsh;
	अचिन्हित लघु fs, __fsh;
	अचिन्हित लघु gs, __gsh;
पूर्ण;

काष्ठा vm86 अणु
	काष्ठा vm86plus_काष्ठा __user *user_vm86;
	काष्ठा pt_regs regs32;
	अचिन्हित दीर्घ veflags;
	अचिन्हित दीर्घ veflags_mask;
	अचिन्हित दीर्घ saved_sp0;

	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ cpu_type;
	काष्ठा revectored_काष्ठा पूर्णांक_revectored;
	काष्ठा revectored_काष्ठा पूर्णांक21_revectored;
	काष्ठा vm86plus_info_काष्ठा vm86plus;
पूर्ण;

#अगर_घोषित CONFIG_VM86

व्योम handle_vm86_fault(काष्ठा kernel_vm86_regs *, दीर्घ);
पूर्णांक handle_vm86_trap(काष्ठा kernel_vm86_regs *, दीर्घ, पूर्णांक);
व्योम save_v86_state(काष्ठा kernel_vm86_regs *, पूर्णांक);

काष्ठा task_काष्ठा;

#घोषणा मुक्त_vm86(t) करो अणु				\
	काष्ठा thपढ़ो_काष्ठा *__t = (t);		\
	अगर (__t->vm86 != शून्य) अणु			\
		kमुक्त(__t->vm86);			\
		__t->vm86 = शून्य;			\
	पूर्ण						\
पूर्ण जबतक (0)

/*
 * Support क्रम VM86 programs to request पूर्णांकerrupts क्रम
 * real mode hardware drivers:
 */
#घोषणा FIRST_VM86_IRQ		 3
#घोषणा LAST_VM86_IRQ		15

अटल अंतरभूत पूर्णांक invalid_vm86_irq(पूर्णांक irq)
अणु
	वापस irq < FIRST_VM86_IRQ || irq > LAST_VM86_IRQ;
पूर्ण

व्योम release_vm86_irqs(काष्ठा task_काष्ठा *);

#अन्यथा

#घोषणा handle_vm86_fault(a, b)
#घोषणा release_vm86_irqs(a)

अटल अंतरभूत पूर्णांक handle_vm86_trap(काष्ठा kernel_vm86_regs *a, दीर्घ b, पूर्णांक c)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम save_v86_state(काष्ठा kernel_vm86_regs *a, पूर्णांक b) अणु पूर्ण

#घोषणा मुक्त_vm86(t) करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर /* CONFIG_VM86 */

#पूर्ण_अगर /* _ASM_X86_VM86_H */
