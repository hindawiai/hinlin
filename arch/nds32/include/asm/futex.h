<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_FUTEX_H__
#घोषणा __NDS32_FUTEX_H__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा __futex_atomic_ex_table(err_reg)			\
	"	.pushsection __ex_table,\"a\"\n"		\
	"	.align	3\n"					\
	"	.long	1b, 4f\n"				\
	"	.long	2b, 4f\n"				\
	"	.popsection\n"					\
	"	.pushsection .fixup,\"ax\"\n"			\
	"4:	move	%0, " err_reg "\n"			\
	"	b	3b\n"					\
	"	.popsection"

#घोषणा __futex_atomic_op(insn, ret, oldval, पंचांगp, uaddr, oparg)	\
	smp_mb();						\
	यंत्र अस्थिर(					\
	"	movi	$ta, #0\n"				\
	"1:	llw	%1, [%2+$ta]\n"				\
	"	" insn "\n"					\
	"2:	scw	%0, [%2+$ta]\n"				\
	"	beqz	%0, 1b\n"				\
	"	movi	%0, #0\n"				\
	"3:\n"							\
	__futex_atomic_ex_table("%4")				\
	: "=&r" (ret), "=&r" (oldval)				\
	: "r" (uaddr), "r" (oparg), "i" (-EFAULT)		\
	: "cc", "memory")
अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 * uval, u32 __user * uaddr,
			      u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0;
	u32 val, पंचांगp, flags;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	smp_mb();
	यंत्र अस्थिर ("       movi    $ta, #0\n"
		      "1:     llw     %1, [%6 + $ta]\n"
		      "       sub     %3, %1, %4\n"
		      "       cmovz   %2, %5, %3\n"
		      "       cmovn   %2, %1, %3\n"
		      "2:     scw     %2, [%6 + $ta]\n"
		      "       beqz    %2, 1b\n"
		      "3:\n                   " __futex_atomic_ex_table("%7")
		      :"+&r"(ret), "=&r"(val), "=&r"(पंचांगp), "=&r"(flags)
		      :"r"(oldval), "r"(newval), "r"(uaddr), "i"(-EFAULT)
		      :"$ta", "memory");
	smp_mb();

	*uval = val;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;
	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("move	%0, %3", ret, oldval, पंचांगp, uaddr,
				  oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("add	%0, %1, %3", ret, oldval, पंचांगp, uaddr,
				  oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or	%0, %1, %3", ret, oldval, पंचांगp, uaddr,
				  oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and	%0, %1, %3", ret, oldval, पंचांगp, uaddr,
				  ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor	%0, %1, %3", ret, oldval, पंचांगp, uaddr,
				  oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण
#पूर्ण_अगर /* __NDS32_FUTEX_H__ */
