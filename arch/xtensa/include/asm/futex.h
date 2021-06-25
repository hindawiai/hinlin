<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Atomic futex routines
 *
 * Based on the PowerPC implementataion
 *
 * Copyright (C) 2013 TangoTec Ltd.
 *
 * Baruch Siach <baruch@tkos.co.il>
 */

#अगर_अघोषित _ASM_XTENSA_FUTEX_H
#घोषणा _ASM_XTENSA_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>

#अगर XCHAL_HAVE_EXCLUSIVE
#घोषणा __futex_atomic_op(insn, ret, old, uaddr, arg)	\
	__यंत्र__ __अस्थिर(				\
	"1:	l32ex	%[oldval], %[addr]\n"		\
		insn "\n"				\
	"2:	s32ex	%[newval], %[addr]\n"		\
	"	getex	%[newval]\n"			\
	"	beqz	%[newval], 1b\n"		\
	"	movi	%[newval], 0\n"			\
	"3:\n"						\
	"	.section .fixup,\"ax\"\n"		\
	"	.align 4\n"				\
	"	.literal_position\n"			\
	"5:	movi	%[oldval], 3b\n"		\
	"	movi	%[newval], %[fault]\n"		\
	"	jx	%[oldval]\n"			\
	"	.previous\n"				\
	"	.section __ex_table,\"a\"\n"		\
	"	.long 1b, 5b, 2b, 5b\n"			\
	"	.previous\n"				\
	: [oldval] "=&r" (old), [newval] "=&r" (ret)	\
	: [addr] "r" (uaddr), [oparg] "r" (arg),	\
	  [fault] "I" (-EFAULT)				\
	: "memory")
#या_अगर XCHAL_HAVE_S32C1I
#घोषणा __futex_atomic_op(insn, ret, old, uaddr, arg)	\
	__यंत्र__ __अस्थिर(				\
	"1:	l32i	%[oldval], %[mem]\n"		\
		insn "\n"				\
	"	wsr	%[oldval], scompare1\n"		\
	"2:	s32c1i	%[newval], %[mem]\n"		\
	"	bne	%[newval], %[oldval], 1b\n"	\
	"	movi	%[newval], 0\n"			\
	"3:\n"						\
	"	.section .fixup,\"ax\"\n"		\
	"	.align 4\n"				\
	"	.literal_position\n"			\
	"5:	movi	%[oldval], 3b\n"		\
	"	movi	%[newval], %[fault]\n"		\
	"	jx	%[oldval]\n"			\
	"	.previous\n"				\
	"	.section __ex_table,\"a\"\n"		\
	"	.long 1b, 5b, 2b, 5b\n"			\
	"	.previous\n"				\
	: [oldval] "=&r" (old), [newval] "=&r" (ret),	\
	  [mem] "+m" (*(uaddr))				\
	: [oparg] "r" (arg), [fault] "I" (-EFAULT)	\
	: "memory")
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval,
		u32 __user *uaddr)
अणु
#अगर XCHAL_HAVE_S32C1I || XCHAL_HAVE_EXCLUSIVE
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("mov %[newval], %[oparg]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add %[newval], %[oldval], %[oparg]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or %[newval], %[oldval], %[oparg]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and %[newval], %[oldval], %[oparg]",
				  ret, oldval, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor %[newval], %[oldval], %[oparg]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
#अन्यथा
	वापस -ENOSYS;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
#अगर XCHAL_HAVE_S32C1I || XCHAL_HAVE_EXCLUSIVE
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret = 0;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__यंत्र__ __अस्थिर__ (
	"	# futex_atomic_cmpxchg_inatomic\n"
#अगर XCHAL_HAVE_EXCLUSIVE
	"1:	l32ex	%[tmp], %[addr]\n"
	"	s32i	%[tmp], %[uval], 0\n"
	"	bne	%[tmp], %[oldval], 2f\n"
	"	mov	%[tmp], %[newval]\n"
	"3:	s32ex	%[tmp], %[addr]\n"
	"	getex	%[tmp]\n"
	"	beqz	%[tmp], 1b\n"
#या_अगर XCHAL_HAVE_S32C1I
	"	wsr	%[oldval], scompare1\n"
	"1:	s32c1i	%[newval], %[addr], 0\n"
	"	s32i	%[newval], %[uval], 0\n"
#पूर्ण_अगर
	"2:\n"
	"	.section .fixup,\"ax\"\n"
	"	.align 4\n"
	"	.literal_position\n"
	"4:	movi	%[tmp], 2b\n"
	"	movi	%[ret], %[fault]\n"
	"	jx	%[tmp]\n"
	"	.previous\n"
	"	.section __ex_table,\"a\"\n"
	"	.long 1b, 4b\n"
#अगर XCHAL_HAVE_EXCLUSIVE
	"	.long 3b, 4b\n"
#पूर्ण_अगर
	"	.previous\n"
	: [ret] "+r" (ret), [newval] "+r" (newval), [पंचांगp] "=&r" (पंचांगp)
	: [addr] "r" (uaddr), [oldval] "r" (oldval), [uval] "r" (uval),
	  [fault] "I" (-EFAULT)
	: "memory");

	वापस ret;
#अन्यथा
	वापस -ENOSYS;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_XTENSA_FUTEX_H */
