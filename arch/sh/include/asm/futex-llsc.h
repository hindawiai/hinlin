<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_FUTEX_LLSC_H
#घोषणा __ASM_SH_FUTEX_LLSC_H

अटल अंतरभूत पूर्णांक atomic_futex_op_cmpxchg_inatomic(u32 *uval,
						   u32 __user *uaddr,
						   u32 oldval, u32 newval)
अणु
	पूर्णांक err = 0;
	__यंत्र__ __अस्थिर__(
		"synco\n"
		"1:\n\t"
		"movli.l	@%2, r0\n\t"
		"mov	r0, %1\n\t"
		"cmp/eq	%1, %4\n\t"
		"bf	2f\n\t"
		"mov	%5, r0\n\t"
		"movco.l	r0, @%2\n\t"
		"bf	1b\n"
		"2:\n\t"
		"synco\n\t"
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
		:"+r" (err), "=&r" (*uval)
		:"r" (uaddr), "i" (-EFAULT), "r" (oldval), "r" (newval)
		:"t", "memory", "r0");
	अगर (err) वापस err;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_FUTEX_LLSC_H */
