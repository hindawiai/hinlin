<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 06, 07 by Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_CMPXCHG_H
#घोषणा __ASM_CMPXCHG_H

#समावेश <linux/bug.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/llsc.h>
#समावेश <यंत्र/sync.h>
#समावेश <यंत्र/war.h>

/*
 * These functions करोesn't exist, so if they are called you'll either:
 *
 * - Get an error at compile-समय due to __compileसमय_error, अगर supported by
 *   your compiler.
 *
 * or:
 *
 * - Get an error at link-समय due to the call to the missing function.
 */
बाह्य अचिन्हित दीर्घ __cmpxchg_called_with_bad_poपूर्णांकer(व्योम)
	__compileसमय_error("Bad argument size for cmpxchg");
बाह्य अचिन्हित दीर्घ __cmpxchg64_unsupported(व्योम)
	__compileसमय_error("cmpxchg64 not available; cpu_has_64bits may be false");
बाह्य अचिन्हित दीर्घ __xchg_called_with_bad_poपूर्णांकer(व्योम)
	__compileसमय_error("Bad argument size for xchg");

#घोषणा __xchg_यंत्र(ld, st, m, val)					\
(अणु									\
	__typeof(*(m)) __ret;						\
									\
	अगर (kernel_uses_llsc) अणु						\
		__यंत्र__ __अस्थिर__(					\
		"	.set	push				\n"	\
		"	.set	noat				\n"	\
		"	.set	push				\n"	\
		"	.set	" MIPS_ISA_ARCH_LEVEL "		\n"	\
		"	" __SYNC(full, loongson3_war) "		\n"	\
		"1:	" ld "	%0, %2		# __xchg_asm	\n"	\
		"	.set	pop				\n"	\
		"	move	$1, %z3				\n"	\
		"	.set	" MIPS_ISA_ARCH_LEVEL "		\n"	\
		"	" st "	$1, %1				\n"	\
		"\t" __SC_BEQZ	"$1, 1b				\n"	\
		"	.set	pop				\n"	\
		: "=&r" (__ret), "=" GCC_OFF_SMALL_ASM() (*m)		\
		: GCC_OFF_SMALL_ASM() (*m), "Jr" (val)			\
		: __LLSC_CLOBBER);					\
	पूर्ण अन्यथा अणु							\
		अचिन्हित दीर्घ __flags;					\
									\
		raw_local_irq_save(__flags);				\
		__ret = *m;						\
		*m = val;						\
		raw_local_irq_restore(__flags);				\
	पूर्ण								\
									\
	__ret;								\
पूर्ण)

बाह्य अचिन्हित दीर्घ __xchg_small(अस्थिर व्योम *ptr, अचिन्हित दीर्घ val,
				  अचिन्हित पूर्णांक size);

अटल __always_अंतरभूत
अचिन्हित दीर्घ __xchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ x, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
	हाल 2:
		वापस __xchg_small(ptr, x, size);

	हाल 4:
		वापस __xchg_यंत्र("ll", "sc", (अस्थिर u32 *)ptr, x);

	हाल 8:
		अगर (!IS_ENABLED(CONFIG_64BIT))
			वापस __xchg_called_with_bad_poपूर्णांकer();

		वापस __xchg_यंत्र("lld", "scd", (अस्थिर u64 *)ptr, x);

	शेष:
		वापस __xchg_called_with_bad_poपूर्णांकer();
	पूर्ण
पूर्ण

#घोषणा xchg(ptr, x)							\
(अणु									\
	__typeof__(*(ptr)) __res;					\
									\
	/*								\
	 * In the Loongson3 workaround हाल __xchg_यंत्र() alपढ़ोy	\
	 * contains a completion barrier prior to the LL, so we करोn't	\
	 * need to emit an extra one here.				\
	 */								\
	अगर (__SYNC_loongson3_war == 0)					\
		smp_mb__beक्रमe_llsc();					\
									\
	__res = (__typeof__(*(ptr)))					\
		__xchg((ptr), (अचिन्हित दीर्घ)(x), माप(*(ptr)));	\
									\
	smp_llsc_mb();							\
									\
	__res;								\
पूर्ण)

#घोषणा __cmpxchg_यंत्र(ld, st, m, old, new)				\
(अणु									\
	__typeof(*(m)) __ret;						\
									\
	अगर (kernel_uses_llsc) अणु						\
		__यंत्र__ __अस्थिर__(					\
		"	.set	push				\n"	\
		"	.set	noat				\n"	\
		"	.set	push				\n"	\
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"	\
		"	" __SYNC(full, loongson3_war) "		\n"	\
		"1:	" ld "	%0, %2		# __cmpxchg_asm \n"	\
		"	bne	%0, %z3, 2f			\n"	\
		"	.set	pop				\n"	\
		"	move	$1, %z4				\n"	\
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"	\
		"	" st "	$1, %1				\n"	\
		"\t" __SC_BEQZ	"$1, 1b				\n"	\
		"	.set	pop				\n"	\
		"2:	" __SYNC(full, loongson3_war) "		\n"	\
		: "=&r" (__ret), "=" GCC_OFF_SMALL_ASM() (*m)		\
		: GCC_OFF_SMALL_ASM() (*m), "Jr" (old), "Jr" (new)	\
		: __LLSC_CLOBBER);					\
	पूर्ण अन्यथा अणु							\
		अचिन्हित दीर्घ __flags;					\
									\
		raw_local_irq_save(__flags);				\
		__ret = *m;						\
		अगर (__ret == old)					\
			*m = new;					\
		raw_local_irq_restore(__flags);				\
	पूर्ण								\
									\
	__ret;								\
पूर्ण)

बाह्य अचिन्हित दीर्घ __cmpxchg_small(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old,
				     अचिन्हित दीर्घ new, अचिन्हित पूर्णांक size);

अटल __always_अंतरभूत
अचिन्हित दीर्घ __cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old,
			अचिन्हित दीर्घ new, अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
	हाल 2:
		वापस __cmpxchg_small(ptr, old, new, size);

	हाल 4:
		वापस __cmpxchg_यंत्र("ll", "sc", (अस्थिर u32 *)ptr,
				     (u32)old, new);

	हाल 8:
		/* lld/scd are only available क्रम MIPS64 */
		अगर (!IS_ENABLED(CONFIG_64BIT))
			वापस __cmpxchg_called_with_bad_poपूर्णांकer();

		वापस __cmpxchg_यंत्र("lld", "scd", (अस्थिर u64 *)ptr,
				     (u64)old, new);

	शेष:
		वापस __cmpxchg_called_with_bad_poपूर्णांकer();
	पूर्ण
पूर्ण

#घोषणा cmpxchg_local(ptr, old, new)					\
	((__typeof__(*(ptr)))						\
		__cmpxchg((ptr),					\
			  (अचिन्हित दीर्घ)(__typeof__(*(ptr)))(old),	\
			  (अचिन्हित दीर्घ)(__typeof__(*(ptr)))(new),	\
			  माप(*(ptr))))

#घोषणा cmpxchg(ptr, old, new)						\
(अणु									\
	__typeof__(*(ptr)) __res;					\
									\
	/*								\
	 * In the Loongson3 workaround हाल __cmpxchg_यंत्र() alपढ़ोy	\
	 * contains a completion barrier prior to the LL, so we करोn't	\
	 * need to emit an extra one here.				\
	 */								\
	अगर (__SYNC_loongson3_war == 0)					\
		smp_mb__beक्रमe_llsc();					\
									\
	__res = cmpxchg_local((ptr), (old), (new));			\
									\
	/*								\
	 * In the Loongson3 workaround हाल __cmpxchg_यंत्र() alपढ़ोy	\
	 * contains a completion barrier after the SC, so we करोn't	\
	 * need to emit an extra one here.				\
	 */								\
	अगर (__SYNC_loongson3_war == 0)					\
		smp_llsc_mb();						\
									\
	__res;								\
पूर्ण)

#अगर_घोषित CONFIG_64BIT
#घोषणा cmpxchg64_local(ptr, o, n)					\
  (अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
  पूर्ण)

#घोषणा cmpxchg64(ptr, o, n)						\
  (अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg((ptr), (o), (n));					\
  पूर्ण)
#अन्यथा

# include <यंत्र-generic/cmpxchg-local.h>
# define cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

# अगरdef CONFIG_SMP

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg64(अस्थिर व्योम *ptr,
					अचिन्हित दीर्घ दीर्घ old,
					अचिन्हित दीर्घ दीर्घ new)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp, ret;
	अचिन्हित दीर्घ flags;

	/*
	 * The assembly below has to combine 32 bit values पूर्णांकo a 64 bit
	 * रेजिस्टर, and split 64 bit values from one रेजिस्टर पूर्णांकo two. If we
	 * were to take an पूर्णांकerrupt in the middle of this we'd only save the
	 * least signअगरicant 32 bits of each रेजिस्टर & probably clobber the
	 * most signअगरicant 32 bits of the 64 bit values we're using. In order
	 * to aव्योम this we must disable पूर्णांकerrupts.
	 */
	local_irq_save(flags);

	यंत्र अस्थिर(
	"	.set	push				\n"
	"	.set	" MIPS_ISA_ARCH_LEVEL "		\n"
	/* Load 64 bits from ptr */
	"	" __SYNC(full, loongson3_war) "		\n"
	"1:	lld	%L0, %3		# __cmpxchg64	\n"
	/*
	 * Split the 64 bit value we loaded पूर्णांकo the 2 रेजिस्टरs that hold the
	 * ret variable.
	 */
	"	dsra	%M0, %L0, 32			\n"
	"	sll	%L0, %L0, 0			\n"
	/*
	 * Compare ret against old, अवरोधing out of the loop अगर they करोn't
	 * match.
	 */
	"	bne	%M0, %M4, 2f			\n"
	"	bne	%L0, %L4, 2f			\n"
	/*
	 * Combine the 32 bit halves from the 2 रेजिस्टरs that hold the new
	 * variable पूर्णांकo a single 64 bit रेजिस्टर.
	 */
#  अगर MIPS_ISA_REV >= 2
	"	move	%L1, %L5			\n"
	"	dins	%L1, %M5, 32, 32		\n"
#  अन्यथा
	"	dsll	%L1, %L5, 32			\n"
	"	dsrl	%L1, %L1, 32			\n"
	"	.set	noat				\n"
	"	dsll	$at, %M5, 32			\n"
	"	or	%L1, %L1, $at			\n"
	"	.set	at				\n"
#  endअगर
	/* Attempt to store new at ptr */
	"	scd	%L1, %2				\n"
	/* If we failed, loop! */
	"\t" __SC_BEQZ "%L1, 1b				\n"
	"	.set	pop				\n"
	"2:	" __SYNC(full, loongson3_war) "		\n"
	: "=&r"(ret),
	  "=&r"(पंचांगp),
	  "=" GCC_OFF_SMALL_ASM() (*(अचिन्हित दीर्घ दीर्घ *)ptr)
	: GCC_OFF_SMALL_ASM() (*(अचिन्हित दीर्घ दीर्घ *)ptr),
	  "r" (old),
	  "r" (new)
	: "memory");

	local_irq_restore(flags);
	वापस ret;
पूर्ण

#  define cmpxchg64(ptr, o, n) (अणु					\
	अचिन्हित दीर्घ दीर्घ __old = (__typeof__(*(ptr)))(o);		\
	अचिन्हित दीर्घ दीर्घ __new = (__typeof__(*(ptr)))(n);		\
	__typeof__(*(ptr)) __res;					\
									\
	/*								\
	 * We can only use cmpxchg64 अगर we know that the CPU supports	\
	 * 64-bits, ie. lld & scd. Our call to __cmpxchg64_unsupported	\
	 * will cause a build error unless cpu_has_64bits is a		\
	 * compile-समय स्थिरant 1.					\
	 */								\
	अगर (cpu_has_64bits && kernel_uses_llsc) अणु			\
		smp_mb__beक्रमe_llsc();					\
		__res = __cmpxchg64((ptr), __old, __new);		\
		smp_llsc_mb();						\
	पूर्ण अन्यथा अणु							\
		__res = __cmpxchg64_unsupported();			\
	पूर्ण								\
									\
	__res;								\
पूर्ण)

# अन्यथा /* !CONFIG_SMP */
#  define cmpxchg64(ptr, o, n) cmpxchg64_local((ptr), (o), (n))
# endअगर /* !CONFIG_SMP */
#पूर्ण_अगर /* !CONFIG_64BIT */

#पूर्ण_अगर /* __ASM_CMPXCHG_H */
