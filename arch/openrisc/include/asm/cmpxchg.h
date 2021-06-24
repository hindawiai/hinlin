<शैली गुरु>
/*
 * 1,2 and 4 byte cmpxchg and xchg implementations क्रम OpenRISC.
 *
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * Note:
 * The portable implementations of 1 and 2 byte xchg and cmpxchg using a 4
 * byte cmpxchg is sourced heavily from the sh and mips implementations.
 */

#अगर_अघोषित __ASM_OPENRISC_CMPXCHG_H
#घोषणा __ASM_OPENRISC_CMPXCHG_H

#समावेश  <linux/bits.h>
#समावेश  <linux/compiler.h>
#समावेश  <linux/types.h>

#घोषणा __HAVE_ARCH_CMPXCHG 1

अटल अंतरभूत अचिन्हित दीर्घ cmpxchg_u32(अस्थिर व्योम *ptr,
		अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	l.lwa %0, 0(%1)		\n"
		"	l.sfeq %0, %2		\n"
		"	l.bnf 2f		\n"
		"	 l.nop			\n"
		"	l.swa 0(%1), %3		\n"
		"	l.bnf 1b		\n"
		"	 l.nop			\n"
		"2:				\n"
		: "=&r"(old)
		: "r"(ptr), "r"(old), "r"(new)
		: "cc", "memory");

	वापस old;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर व्योम *ptr,
		अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	l.lwa %0, 0(%1)		\n"
		"	l.swa 0(%1), %2		\n"
		"	l.bnf 1b		\n"
		"	 l.nop			\n"
		: "=&r"(val)
		: "r"(ptr), "r"(val)
		: "cc", "memory");

	वापस val;
पूर्ण

अटल अंतरभूत u32 cmpxchg_small(अस्थिर व्योम *ptr, u32 old, u32 new,
				पूर्णांक size)
अणु
	पूर्णांक off = (अचिन्हित दीर्घ)ptr % माप(u32);
	अस्थिर u32 *p = ptr - off;
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक bitoff = (माप(u32) - size - off) * BITS_PER_BYTE;
#अन्यथा
	पूर्णांक bitoff = off * BITS_PER_BYTE;
#पूर्ण_अगर
	u32 biपंचांगask = ((0x1 << size * BITS_PER_BYTE) - 1) << bitoff;
	u32 load32, old32, new32;
	u32 ret;

	load32 = READ_ONCE(*p);

	जबतक (true) अणु
		ret = (load32 & biपंचांगask) >> bitoff;
		अगर (old != ret)
			वापस ret;

		old32 = (load32 & ~biपंचांगask) | (old << bitoff);
		new32 = (load32 & ~biपंचांगask) | (new << bitoff);

		/* Do 32 bit cmpxchg */
		load32 = cmpxchg_u32(p, old32, new32);
		अगर (load32 == old32)
			वापस old;
	पूर्ण
पूर्ण

/* xchg */

अटल अंतरभूत u32 xchg_small(अस्थिर व्योम *ptr, u32 x, पूर्णांक size)
अणु
	पूर्णांक off = (अचिन्हित दीर्घ)ptr % माप(u32);
	अस्थिर u32 *p = ptr - off;
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक bitoff = (माप(u32) - size - off) * BITS_PER_BYTE;
#अन्यथा
	पूर्णांक bitoff = off * BITS_PER_BYTE;
#पूर्ण_अगर
	u32 biपंचांगask = ((0x1 << size * BITS_PER_BYTE) - 1) << bitoff;
	u32 oldv, newv;
	u32 ret;

	करो अणु
		oldv = READ_ONCE(*p);
		ret = (oldv & biपंचांगask) >> bitoff;
		newv = (oldv & ~biपंचांगask) | (x << bitoff);
	पूर्ण जबतक (cmpxchg_u32(p, oldv, newv) != oldv);

	वापस ret;
पूर्ण

/*
 * This function करोesn't exist, so you'll get a linker error
 * अगर something tries to करो an invalid cmpxchg().
 */
बाह्य अचिन्हित दीर्घ __cmpxchg_called_with_bad_poपूर्णांकer(व्योम)
	__compileसमय_error("Bad argument size for cmpxchg");

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old,
		अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
	हाल 2:
		वापस cmpxchg_small(ptr, old, new, size);
	हाल 4:
		वापस cmpxchg_u32(ptr, old, new);
	शेष:
		वापस __cmpxchg_called_with_bad_poपूर्णांकer();
	पूर्ण
पूर्ण

#घोषणा cmpxchg(ptr, o, n)						\
	(अणु								\
		(__typeof__(*(ptr))) __cmpxchg((ptr),			\
					       (अचिन्हित दीर्घ)(o),	\
					       (अचिन्हित दीर्घ)(n),	\
					       माप(*(ptr)));		\
	पूर्ण)

/*
 * This function करोesn't exist, so you'll get a linker error अगर
 * something tries to करो an invalidly-sized xchg().
 */
बाह्य अचिन्हित दीर्घ __xchg_called_with_bad_poपूर्णांकer(व्योम)
	__compileसमय_error("Bad argument size for xchg");

अटल अंतरभूत अचिन्हित दीर्घ __xchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ with,
		पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
	हाल 2:
		वापस xchg_small(ptr, with, size);
	हाल 4:
		वापस xchg_u32(ptr, with);
	शेष:
		वापस __xchg_called_with_bad_poपूर्णांकer();
	पूर्ण
पूर्ण

#घोषणा xchg(ptr, with) 						\
	(अणु								\
		(__typeof__(*(ptr))) __xchg((ptr),			\
					    (अचिन्हित दीर्घ)(with),	\
					    माप(*(ptr)));		\
	पूर्ण)

#पूर्ण_अगर /* __ASM_OPENRISC_CMPXCHG_H */
