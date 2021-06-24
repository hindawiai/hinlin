<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2006  Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित _ASM_FUTEX_H
#घोषणा _ASM_FUTEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/futex.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/यंत्र-eva.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/sync.h>
#समावेश <यंत्र/war.h>

#घोषणा __futex_atomic_op(insn, ret, oldval, uaddr, oparg)		\
अणु									\
	अगर (cpu_has_llsc && IS_ENABLED(CONFIG_WAR_R10000_LLSC)) अणु	\
		__यंत्र__ __अस्थिर__(					\
		"	.set	push				\n"	\
		"	.set	noat				\n"	\
		"	.set	push				\n"	\
		"	.set	arch=r4000			\n"	\
		"1:	ll	%1, %4	# __futex_atomic_op	\n"	\
		"	.set	pop				\n"	\
		"	" insn	"				\n"	\
		"	.set	arch=r4000			\n"	\
		"2:	sc	$1, %2				\n"	\
		"	beqzl	$1, 1b				\n"	\
		__stringअगरy(__WEAK_LLSC_MB) "			\n"	\
		"3:						\n"	\
		"	.insn					\n"	\
		"	.set	pop				\n"	\
		"	.section .fixup,\"ax\"			\n"	\
		"4:	li	%0, %6				\n"	\
		"	j	3b				\n"	\
		"	.previous				\n"	\
		"	.section __ex_table,\"a\"		\n"	\
		"	"__UA_ADDR "\t1b, 4b			\n"	\
		"	"__UA_ADDR "\t2b, 4b			\n"	\
		"	.previous				\n"	\
		: "=r" (ret), "=&r" (oldval),				\
		  "=" GCC_OFF_SMALL_ASM() (*uaddr)				\
		: "0" (0), GCC_OFF_SMALL_ASM() (*uaddr), "Jr" (oparg),	\
		  "i" (-EFAULT)						\
		: "memory");						\
	पूर्ण अन्यथा अगर (cpu_has_llsc) अणु					\
		__यंत्र__ __अस्थिर__(					\
		"	.set	push				\n"	\
		"	.set	noat				\n"	\
		"	.set	push				\n"	\
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"	\
		"	" __SYNC(full, loongson3_war) "		\n"	\
		"1:	"user_ll("%1", "%4")" # __futex_atomic_op\n"	\
		"	.set	pop				\n"	\
		"	" insn	"				\n"	\
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"	\
		"2:	"user_sc("$1", "%2")"			\n"	\
		"	beqz	$1, 1b				\n"	\
		__stringअगरy(__WEAK_LLSC_MB) "			\n"	\
		"3:						\n"	\
		"	.insn					\n"	\
		"	.set	pop				\n"	\
		"	.section .fixup,\"ax\"			\n"	\
		"4:	li	%0, %6				\n"	\
		"	j	3b				\n"	\
		"	.previous				\n"	\
		"	.section __ex_table,\"a\"		\n"	\
		"	"__UA_ADDR "\t1b, 4b			\n"	\
		"	"__UA_ADDR "\t2b, 4b			\n"	\
		"	.previous				\n"	\
		: "=r" (ret), "=&r" (oldval),				\
		  "=" GCC_OFF_SMALL_ASM() (*uaddr)				\
		: "0" (0), GCC_OFF_SMALL_ASM() (*uaddr), "Jr" (oparg),	\
		  "i" (-EFAULT)						\
		: "memory");						\
	पूर्ण अन्यथा								\
		ret = -ENOSYS;						\
पूर्ण

अटल अंतरभूत पूर्णांक
arch_futex_atomic_op_inuser(पूर्णांक op, पूर्णांक oparg, पूर्णांक *oval, u32 __user *uaddr)
अणु
	पूर्णांक oldval = 0, ret;

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	चयन (op) अणु
	हाल FUTEX_OP_SET:
		__futex_atomic_op("move $1, %z5", ret, oldval, uaddr, oparg);
		अवरोध;

	हाल FUTEX_OP_ADD:
		__futex_atomic_op("addu $1, %1, %z5",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_OR:
		__futex_atomic_op("or	$1, %1, %z5",
				  ret, oldval, uaddr, oparg);
		अवरोध;
	हाल FUTEX_OP_ANDN:
		__futex_atomic_op("and	$1, %1, %z5",
				  ret, oldval, uaddr, ~oparg);
		अवरोध;
	हाल FUTEX_OP_XOR:
		__futex_atomic_op("xor	$1, %1, %z5",
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

	अगर (!access_ok(uaddr, माप(u32)))
		वापस -EFAULT;

	अगर (cpu_has_llsc && IS_ENABLED(CONFIG_WAR_R10000_LLSC)) अणु
		__यंत्र__ __अस्थिर__(
		"# futex_atomic_cmpxchg_inatomic			\n"
		"	.set	push					\n"
		"	.set	noat					\n"
		"	.set	push					\n"
		"	.set	arch=r4000				\n"
		"1:	ll	%1, %3					\n"
		"	bne	%1, %z4, 3f				\n"
		"	.set	pop					\n"
		"	move	$1, %z5					\n"
		"	.set	arch=r4000				\n"
		"2:	sc	$1, %2					\n"
		"	beqzl	$1, 1b					\n"
		__stringअगरy(__WEAK_LLSC_MB) "				\n"
		"3:							\n"
		"	.insn						\n"
		"	.set	pop					\n"
		"	.section .fixup,\"ax\"				\n"
		"4:	li	%0, %6					\n"
		"	j	3b					\n"
		"	.previous					\n"
		"	.section __ex_table,\"a\"			\n"
		"	"__UA_ADDR "\t1b, 4b				\n"
		"	"__UA_ADDR "\t2b, 4b				\n"
		"	.previous					\n"
		: "+r" (ret), "=&r" (val), "=" GCC_OFF_SMALL_ASM() (*uaddr)
		: GCC_OFF_SMALL_ASM() (*uaddr), "Jr" (oldval), "Jr" (newval),
		  "i" (-EFAULT)
		: "memory");
	पूर्ण अन्यथा अगर (cpu_has_llsc) अणु
		__यंत्र__ __अस्थिर__(
		"# futex_atomic_cmpxchg_inatomic			\n"
		"	.set	push					\n"
		"	.set	noat					\n"
		"	.set	push					\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"			\n"
		"	" __SYNC(full, loongson3_war) "			\n"
		"1:	"user_ll("%1", "%3")"				\n"
		"	bne	%1, %z4, 3f				\n"
		"	.set	pop					\n"
		"	move	$1, %z5					\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"			\n"
		"2:	"user_sc("$1", "%2")"				\n"
		"	beqz	$1, 1b					\n"
		"3:	" __SYNC_ELSE(full, loongson3_war, __WEAK_LLSC_MB) "\n"
		"	.insn						\n"
		"	.set	pop					\n"
		"	.section .fixup,\"ax\"				\n"
		"4:	li	%0, %6					\n"
		"	j	3b					\n"
		"	.previous					\n"
		"	.section __ex_table,\"a\"			\n"
		"	"__UA_ADDR "\t1b, 4b				\n"
		"	"__UA_ADDR "\t2b, 4b				\n"
		"	.previous					\n"
		: "+r" (ret), "=&r" (val), "=" GCC_OFF_SMALL_ASM() (*uaddr)
		: GCC_OFF_SMALL_ASM() (*uaddr), "Jr" (oldval), "Jr" (newval),
		  "i" (-EFAULT)
		: "memory");
	पूर्ण अन्यथा
		वापस -ENOSYS;

	*uval = val;
	वापस ret;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_FUTEX_H */
