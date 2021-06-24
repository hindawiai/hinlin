<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (c) 2018  Jim Wilson (jimw@sअगरive.com)
 */

#अगर_अघोषित _ASM_RISCV_FUTEX_H
#घोषणा _ASM_RISCV_FUTEX_H

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/यंत्र.h>

/* We करोn't even really need the extable code, but क्रम now keep it simple */
#अगर_अघोषित CONFIG_MMU
#घोषणा __enable_user_access()		करो अणु पूर्ण जबतक (0)
#घोषणा __disable_user_access()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)	\
अणु								\
	uपूर्णांकptr_t पंचांगp;						\
	__enable_user_access();					\
	__यंत्र__ __अस्थिर__ (					\
	"1:	" insn "				\n"	\
	"2:						\n"	\
	"	.section .fixup,\"ax\"			\n"	\
	"	.balign 4				\n"	\
	"3:	li %[r],%[e]				\n"	\
	"	jump 2b,%[t]				\n"	\
	"	.previous				\n"	\
	"	.section __ex_table,\"a\"		\n"	\
	"	.balign " RISCV_SZPTR "			\n"	\
	"	" RISCV_PTR " 1b, 3b			\n"	\
	"	.previous				\n"	\
	: [r] "+r" (ret), [ov] "=&r" (oldval),			\
	  [u] "+m" (*uaddr), [t] "=&r" (पंचांगp)			\
	: [op] "Jr" (oparg), [e] "i" (-EFAULT)			\
	: "memory");						\
	__disable_user_access();				\
पूर्ण

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret = 0;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("amoswap.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ADD:
		__futex_atomic_op("amoadd.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("amoor.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("amoand.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("amoxor.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	अगर (!ret)
		*oval = oldval;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
अणु
	पूर्णांक ret = 0;
	u32 val;
	uपूर्णांकptr_t पंचांगp;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	__enable_user_access();
	__यंत्र__ __अस्थिर__ (
	"1:	lr.w.aqrl %[v],%[u]			\n"
	"	bne %[v],%z[ov],3f			\n"
	"2:	sc.w.aqrl %[t],%z[nv],%[u]		\n"
	"	bnez %[t],1b				\n"
	"3:						\n"
	"	.section .fixup,\"ax\"			\n"
	"	.balign 4				\n"
	"4:	li %[r],%[e]				\n"
	"	jump 3b,%[t]				\n"
	"	.previous				\n"
	"	.section __ex_table,\"a\"		\n"
	"	.balign " RISCV_SZPTR "			\n"
	"	" RISCV_PTR " 1b, 4b			\n"
	"	" RISCV_PTR " 2b, 4b			\n"
	"	.previous				\n"
	: [r] "+r" (ret), [v] "=&r" (val), [u] "+m" (*uaddr), [t] "=&r" (पंचांगp)
	: [ov] "Jr" (oldval), [nv] "Jr" (newval), [e] "i" (-EFAULT)
	: "memory");
	__disable_user_access();

	*uval = val;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_FUTEX_H */
