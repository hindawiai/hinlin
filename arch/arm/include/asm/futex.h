<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_FUTEX_H
#घोषणा _ASM_ARM_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_ex_table(err_reg)			\
	"3:\n"							\
	"	.pushsection __ex_table,\"a\"\n"		\
	"	.align	3\n"					\
	"	.long	1b, 4f, 2b, 4f\n"			\
	"	.popsection\n"					\
	"	.pushsection .text.fixup,\"ax\"\n"		\
	"	.align	2\n"					\
	"4:	mov	%0, " err_reg "\n"			\
	"	b	3b\n"					\
	"	.popsection"

#अगर_घोषित CONFIG_SMP

#घोषणा __futex_atomic_op(insn, ret, oldval, पंचांगp, uaddr, oparg)	\
(अणु								\
	अचिन्हित पूर्णांक __ua_flags;				\
	smp_mb();						\
	prefetchw(uaddr);					\
	__ua_flags = uaccess_save_and_enable();			\
	__यंत्र__ __अस्थिर__(					\
	"1:	ldrex	%1, [%3]\n"				\
	"	" insn "\n"					\
	"2:	strex	%2, %0, [%3]\n"				\
	"	teq	%2, #0\n"				\
	"	bne	1b\n"					\
	"	mov	%0, #0\n"				\
	__futex_atomic_ex_table("%5")				\
	: "=&r" (ret), "=&r" (oldval), "=&r" (पंचांगp)		\
	: "r" (uaddr), "r" (oparg), "Ir" (-EFAULT)		\
	: "cc", "memory");					\
	uaccess_restore(__ua_flags);				\
पूर्ण)

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	अचिन्हित पूर्णांक __ua_flags;
	पूर्णांक ret;
	u32 val;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	smp_mb();
	/* Prefetching cannot fault */
	prefetchw(uaddr);
	__ua_flags = uaccess_save_and_enable();
	__यंत्र__ __अस्थिर__("@futex_atomic_cmpxchg_inatomic\n"
	"1:	ldrex	%1, [%4]\n"
	"	teq	%1, %2\n"
	"	ite	eq	@ explicit IT needed for the 2b label\n"
	"2:	strexeq	%0, %3, [%4]\n"
	"	movne	%0, #0\n"
	"	teq	%0, #0\n"
	"	bne	1b\n"
	__futex_atomic_ex_table("%5")
	: "=&r" (ret), "=&r" (val)
	: "r" (oldval), "r" (newval), "r" (uaddr), "Ir" (-EFAULT)
	: "cc", "memory");
	uaccess_restore(__ua_flags);
	smp_mb();

	*uval = val;
	वापस ret;
पूर्ण

#अन्यथा /* !SMP, we can work around lack of atomic ops by disabling preemption */

#समावेश <linux/preempt.h>
#समावेश <यंत्र/करोमुख्य.h>

#घोषणा __futex_atomic_op(insn, ret, oldval, पंचांगp, uaddr, oparg)	\
(अणु								\
	अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();	\
	__यंत्र__ __अस्थिर__(					\
	"1:	" TUSER(ldr) "	%1, [%3]\n"			\
	"	" insn "\n"					\
	"2:	" TUSER(str) "	%0, [%3]\n"			\
	"	mov	%0, #0\n"				\
	__futex_atomic_ex_table("%5")				\
	: "=&r" (ret), "=&r" (oldval), "=&r" (पंचांगp)		\
	: "r" (uaddr), "r" (oparg), "Ir" (-EFAULT)		\
	: "cc", "memory");					\
	uaccess_restore(__ua_flags);				\
पूर्ण)

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	अचिन्हित पूर्णांक __ua_flags;
	पूर्णांक ret = 0;
	u32 val;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	preempt_disable();
	__ua_flags = uaccess_save_and_enable();
	__यंत्र__ __अस्थिर__("@futex_atomic_cmpxchg_inatomic\n"
	"	.syntax unified\n"
	"1:	" TUSER(ldr) "	%1, [%4]\n"
	"	teq	%1, %2\n"
	"	it	eq	@ explicit IT needed for the 2b label\n"
	"2:	" TUSERCOND(str, eq) "	%3, [%4]\n"
	__futex_atomic_ex_table("%5")
	: "+r" (ret), "=&r" (val)
	: "r" (oldval), "r" (newval), "r" (uaddr), "Ir" (-EFAULT)
	: "cc", "memory");
	uaccess_restore(__ua_flags);

	*uval = val;
	preempt_enable();

	वापस ret;
पूर्ण

#पूर्ण_अगर /* !SMP */

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret, पंचांगp;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

#अगर_अघोषित CONFIG_SMP
	preempt_disable();
#पूर्ण_अगर

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov	%0, %4", ret, oldval, पंचांगp, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add	%0, %1, %4", ret, oldval, पंचांगp, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("orr	%0, %1, %4", ret, oldval, पंचांगp, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and	%0, %1, %4", ret, oldval, पंचांगp, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("eor	%0, %1, %4", ret, oldval, पंचांगp, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

#अगर_अघोषित CONFIG_SMP
	preempt_enable();
#पूर्ण_अगर

	/*
	 * Store unconditionally. If ret != 0 the extra store is the least
	 * of the worries but GCC cannot figure out that __futex_atomic_op()
	 * is either setting ret to -EFAULT or storing the old value in
	 * oldval which results in a uninitialized warning at the call site.
	 */
	*oval = oldval;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_ARM_FUTEX_H */
