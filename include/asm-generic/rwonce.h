<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Prevent the compiler from merging or refetching पढ़ोs or ग_लिखोs. The
 * compiler is also क्रमbidden from reordering successive instances of
 * READ_ONCE and WRITE_ONCE, but only when the compiler is aware of some
 * particular ordering. One way to make the compiler aware of ordering is to
 * put the two invocations of READ_ONCE or WRITE_ONCE in dअगरferent C
 * statements.
 *
 * These two macros will also work on aggregate data types like काष्ठाs or
 * जोड़s.
 *
 * Their two major use हालs are: (1) Mediating communication between
 * process-level code and irq/NMI handlers, all running on the same CPU,
 * and (2) Ensuring that the compiler करोes not fold, spindle, or otherwise
 * mutilate accesses that either करो not require ordering or that पूर्णांकeract
 * with an explicit memory barrier or atomic inकाष्ठाion that provides the
 * required ordering.
 */
#अगर_अघोषित __ASM_GENERIC_RWONCE_H
#घोषणा __ASM_GENERIC_RWONCE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler_types.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/kcsan-checks.h>

/*
 * Yes, this permits 64-bit accesses on 32-bit architectures. These will
 * actually be atomic in some हालs (namely Armv7 + LPAE), but क्रम others we
 * rely on the access being split पूर्णांकo 2x32-bit accesses क्रम a 32-bit quantity
 * (e.g. a भव address) and a strong prevailing wind.
 */
#घोषणा compileसमय_निश्चित_rwonce_type(t)					\
	compileसमय_निश्चित(__native_word(t) || माप(t) == माप(दीर्घ दीर्घ),	\
		"Unsupported access size for {READ,WRITE}_ONCE().")

/*
 * Use __READ_ONCE() instead of READ_ONCE() अगर you करो not require any
 * atomicity. Note that this may result in tears!
 */
#अगर_अघोषित __READ_ONCE
#घोषणा __READ_ONCE(x)	(*(स्थिर अस्थिर __unqual_scalar_typeof(x) *)&(x))
#पूर्ण_अगर

#घोषणा READ_ONCE(x)							\
(अणु									\
	compileसमय_निश्चित_rwonce_type(x);				\
	__READ_ONCE(x);							\
पूर्ण)

#घोषणा __WRITE_ONCE(x, val)						\
करो अणु									\
	*(अस्थिर typeof(x) *)&(x) = (val);				\
पूर्ण जबतक (0)

#घोषणा WRITE_ONCE(x, val)						\
करो अणु									\
	compileसमय_निश्चित_rwonce_type(x);				\
	__WRITE_ONCE(x, val);						\
पूर्ण जबतक (0)

अटल __no_sanitize_or_अंतरभूत
अचिन्हित दीर्घ __पढ़ो_once_word_nocheck(स्थिर व्योम *addr)
अणु
	वापस __READ_ONCE(*(अचिन्हित दीर्घ *)addr);
पूर्ण

/*
 * Use READ_ONCE_NOCHECK() instead of READ_ONCE() अगर you need to load a
 * word from memory atomically but without telling KASAN/KCSAN. This is
 * usually used by unwinding code when walking the stack of a running process.
 */
#घोषणा READ_ONCE_NOCHECK(x)						\
(अणु									\
	compileसमय_निश्चित(माप(x) == माप(अचिन्हित दीर्घ),		\
		"Unsupported access size for READ_ONCE_NOCHECK().");	\
	(typeof(x))__पढ़ो_once_word_nocheck(&(x));			\
पूर्ण)

अटल __no_kasan_or_अंतरभूत
अचिन्हित दीर्घ पढ़ो_word_at_a_समय(स्थिर व्योम *addr)
अणु
	kasan_check_पढ़ो(addr, 1);
	वापस *(अचिन्हित दीर्घ *)addr;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_GENERIC_RWONCE_H */
