<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_FUTEX_H
#घोषणा _ASM_X86_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/smap.h>

#घोषणा unsafe_atomic_op1(insn, oval, uaddr, oparg, label)	\
करो अणु								\
	पूर्णांक oldval = 0, ret;					\
	यंत्र अस्थिर("1:\t" insn "\n"				\
		     "2:\n"					\
		     "\t.section .fixup,\"ax\"\n"		\
		     "3:\tmov\t%3, %1\n"			\
		     "\tjmp\t2b\n"				\
		     "\t.previous\n"				\
		     _ASM_EXTABLE_UA(1b, 3b)			\
		     : "=r" (oldval), "=r" (ret), "+m" (*uaddr)	\
		     : "i" (-EFAULT), "0" (oparg), "1" (0));	\
	अगर (ret)						\
		जाओ label;					\
	*oval = oldval;						\
पूर्ण जबतक(0)


#घोषणा unsafe_atomic_op2(insn, oval, uaddr, oparg, label)	\
करो अणु								\
	पूर्णांक oldval = 0, ret, tem;				\
	यंत्र अस्थिर("1:\tmovl	%2, %0\n"			\
		     "2:\tmovl\t%0, %3\n"			\
		     "\t" insn "\n"				\
		     "3:\t" LOCK_PREFIX "cmpxchgl %3, %2\n"	\
		     "\tjnz\t2b\n"				\
		     "4:\n"					\
		     "\t.section .fixup,\"ax\"\n"		\
		     "5:\tmov\t%5, %1\n"			\
		     "\tjmp\t4b\n"				\
		     "\t.previous\n"				\
		     _ASM_EXTABLE_UA(1b, 5b)			\
		     _ASM_EXTABLE_UA(3b, 5b)			\
		     : "=&a" (oldval), "=&r" (ret),		\
		       "+m" (*uaddr), "=&r" (tem)		\
		     : "r" (oparg), "i" (-EFAULT), "1" (0));	\
	अगर (ret)						\
		जाओ label;					\
	*oval = oldval;						\
पूर्ण जबतक(0)

अटल __always_अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
	अगर (!user_access_begin(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		unsafe_atomic_op1("xchgl %0, %2", oval, uaddr, oparg, Efault);
		अवरोध;
	हाल FUTEX_OP_ADD:
		unsafe_atomic_op1(LOCK_PREFIX "xaddl %0, %2", oval,
				   uaddr, oparg, Efault);
		अवरोध;
	हाल FUTEX_OP_OR:
		unsafe_atomic_op2("orl %4, %3", oval, uaddr, oparg, Efault);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		unsafe_atomic_op2("andl %4, %3", oval, uaddr, ~oparg, Efault);
		अवरोध;
	हाल FUTEX_OP_XOR:
		unsafe_atomic_op2("xorl %4, %3", oval, uaddr, oparg, Efault);
		अवरोध;
	शेष:
		user_access_end();
		वापस -ENOSYS;
	पूर्ण
	user_access_end();
	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण

अटल अंतरभूत पूर्णांक futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
						u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0;

	अगर (!user_access_begin(uaddr, माप(u32)))
		वापस -EFAULT;
	यंत्र अस्थिर("\n"
		"1:\t" LOCK_PREFIX "cmpxchgl %4, %2\n"
		"2:\n"
		"\t.section .fixup, \"ax\"\n"
		"3:\tmov     %3, %0\n"
		"\tjmp     2b\n"
		"\t.previous\n"
		_ASM_EXTABLE_UA(1b, 3b)
		: "+r" (ret), "=a" (oldval), "+m" (*uaddr)
		: "i" (-EFAULT), "r" (newval), "1" (oldval)
		: "memory"
	);
	user_access_end();
	*uval = oldval;
	वापस ret;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_FUTEX_H */
