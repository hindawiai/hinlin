<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CMPXCHG_64_H
#घोषणा _ASM_X86_CMPXCHG_64_H

अटल अंतरभूत व्योम set_64bit(अस्थिर u64 *ptr, u64 val)
अणु
	*ptr = val;
पूर्ण

#घोषणा arch_cmpxchg64(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	arch_cmpxchg((ptr), (o), (n));					\
पूर्ण)

#घोषणा arch_cmpxchg64_local(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	arch_cmpxchg_local((ptr), (o), (n));				\
पूर्ण)

#घोषणा प्रणाली_has_cmpxchg_द्विगुन() boot_cpu_has(X86_FEATURE_CX16)

#पूर्ण_अगर /* _ASM_X86_CMPXCHG_64_H */
