<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CMPXCHG_32_H
#घोषणा _ASM_X86_CMPXCHG_32_H

/*
 * Note: अगर you use set64_bit(), __cmpxchg64(), or their variants,
 *       you need to test क्रम the feature in boot_cpu_data.
 */

/*
 * CMPXCHG8B only ग_लिखोs to the target अगर we had the previous
 * value in रेजिस्टरs, otherwise it acts as a पढ़ो and gives us the
 * "new previous" value.  That is why there is a loop.  Preloading
 * EDX:EAX is a perक्रमmance optimization: in the common हाल it means
 * we need only one locked operation.
 *
 * A SIMD/3DNOW!/MMX/FPU 64-bit store here would require at the very
 * least an FPU save and/or %cr0.ts manipulation.
 *
 * cmpxchg8b must be used with the lock prefix here to allow the
 * inकाष्ठाion to be executed atomically.  We need to have the पढ़ोer
 * side to see the coherent 64bit value.
 */
अटल अंतरभूत व्योम set_64bit(अस्थिर u64 *ptr, u64 value)
अणु
	u32 low  = value;
	u32 high = value >> 32;
	u64 prev = *ptr;

	यंत्र अस्थिर("\n1:\t"
		     LOCK_PREFIX "cmpxchg8b %0\n\t"
		     "jnz 1b"
		     : "=m" (*ptr), "+A" (prev)
		     : "b" (low), "c" (high)
		     : "memory");
पूर्ण

#अगर_घोषित CONFIG_X86_CMPXCHG64
#घोषणा arch_cmpxchg64(ptr, o, n)					\
	((__typeof__(*(ptr)))__cmpxchg64((ptr), (अचिन्हित दीर्घ दीर्घ)(o), \
					 (अचिन्हित दीर्घ दीर्घ)(n)))
#घोषणा arch_cmpxchg64_local(ptr, o, n)					\
	((__typeof__(*(ptr)))__cmpxchg64_local((ptr), (अचिन्हित दीर्घ दीर्घ)(o), \
					       (अचिन्हित दीर्घ दीर्घ)(n)))
#पूर्ण_अगर

अटल अंतरभूत u64 __cmpxchg64(अस्थिर u64 *ptr, u64 old, u64 new)
अणु
	u64 prev;
	यंत्र अस्थिर(LOCK_PREFIX "cmpxchg8b %1"
		     : "=A" (prev),
		       "+m" (*ptr)
		     : "b" ((u32)new),
		       "c" ((u32)(new >> 32)),
		       "0" (old)
		     : "memory");
	वापस prev;
पूर्ण

अटल अंतरभूत u64 __cmpxchg64_local(अस्थिर u64 *ptr, u64 old, u64 new)
अणु
	u64 prev;
	यंत्र अस्थिर("cmpxchg8b %1"
		     : "=A" (prev),
		       "+m" (*ptr)
		     : "b" ((u32)new),
		       "c" ((u32)(new >> 32)),
		       "0" (old)
		     : "memory");
	वापस prev;
पूर्ण

#अगर_अघोषित CONFIG_X86_CMPXCHG64
/*
 * Building a kernel capable running on 80386 and 80486. It may be necessary
 * to simulate the cmpxchg8b on the 80386 and 80486 CPU.
 */

#घोषणा arch_cmpxchg64(ptr, o, n)				\
(अणु								\
	__typeof__(*(ptr)) __ret;				\
	__typeof__(*(ptr)) __old = (o);				\
	__typeof__(*(ptr)) __new = (n);				\
	alternative_io(LOCK_PREFIX_HERE				\
			"call cmpxchg8b_emu",			\
			"lock; cmpxchg8b (%%esi)" ,		\
		       X86_FEATURE_CX8,				\
		       "=A" (__ret),				\
		       "S" ((ptr)), "0" (__old),		\
		       "b" ((अचिन्हित पूर्णांक)__new),		\
		       "c" ((अचिन्हित पूर्णांक)(__new>>32))		\
		       : "memory");				\
	__ret; पूर्ण)


#घोषणा arch_cmpxchg64_local(ptr, o, n)				\
(अणु								\
	__typeof__(*(ptr)) __ret;				\
	__typeof__(*(ptr)) __old = (o);				\
	__typeof__(*(ptr)) __new = (n);				\
	alternative_io("call cmpxchg8b_emu",			\
		       "cmpxchg8b (%%esi)" ,			\
		       X86_FEATURE_CX8,				\
		       "=A" (__ret),				\
		       "S" ((ptr)), "0" (__old),		\
		       "b" ((अचिन्हित पूर्णांक)__new),		\
		       "c" ((अचिन्हित पूर्णांक)(__new>>32))		\
		       : "memory");				\
	__ret; पूर्ण)

#पूर्ण_अगर

#घोषणा प्रणाली_has_cmpxchg_द्विगुन() boot_cpu_has(X86_FEATURE_CX8)

#पूर्ण_अगर /* _ASM_X86_CMPXCHG_32_H */
