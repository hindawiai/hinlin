<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FUTEX_CAS_H
#घोषणा __ASM_SH_FUTEX_CAS_H

अटल अंतरभूत पूर्णांक atomic_futex_op_cmpxchg_inatomic(u32 *uval,
						   u32 __user *uaddr,
						   u32 oldval, u32 newval)
अणु
	पूर्णांक err = 0;
	__यंत्र__ __अस्थिर__(
		"1:\n\t"
		"cas.l	%2, %1, @r0\n"
		"2:\n\t"
#अगर_घोषित CONFIG_MMU
		".section	.fixup,\"ax\"\n"
		"3:\n\t"
		"mov.l	4f, %0\n\t"
		"jmp	@%0\n\t"
		" mov	%3, %0\n\t"
		".balign	4\n"
		"4:	.long	2b\n\t"
		".previous\n"
		".section	__ex_table,\"a\"\n\t"
		".long	1b, 3b\n\t"
		".previous"
#पूर्ण_अगर
		:"+r" (err), "+r" (newval)
		:"r" (oldval), "i" (-EFAULT), "z" (uaddr)
		:"t", "memory");
	अगर (err) वापस err;
	*uval = newval;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_FUTEX_CAS_H */
