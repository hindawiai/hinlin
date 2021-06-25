<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_UNCACHED_H
#घोषणा __ASM_SH_UNCACHED_H

#समावेश <linux/bug.h>

#अगर_घोषित CONFIG_UNCACHED_MAPPING
बाह्य अचिन्हित दीर्घ cached_to_uncached;
बाह्य अचिन्हित दीर्घ uncached_size;
बाह्य अचिन्हित दीर्घ uncached_start, uncached_end;

बाह्य पूर्णांक virt_addr_uncached(अचिन्हित दीर्घ kaddr);
बाह्य व्योम uncached_init(व्योम);
बाह्य व्योम uncached_resize(अचिन्हित दीर्घ size);

/*
 * Jump to uncached area.
 * When handling TLB or caches, we need to करो it from an uncached area.
 */
#घोषणा jump_to_uncached()			\
करो अणु						\
	अचिन्हित दीर्घ __dummy;			\
						\
	__यंत्र__ __अस्थिर__(			\
		"mova	1f, %0\n\t"		\
		"add	%1, %0\n\t"		\
		"jmp	@%0\n\t"		\
		" nop\n\t"			\
		".balign 4\n"			\
		"1:"				\
		: "=&z" (__dummy)		\
		: "r" (cached_to_uncached));	\
पूर्ण जबतक (0)

/*
 * Back to cached area.
 */
#घोषणा back_to_cached()				\
करो अणु							\
	अचिन्हित दीर्घ __dummy;				\
	ctrl_barrier();					\
	__यंत्र__ __अस्थिर__(				\
		"mov.l	1f, %0\n\t"			\
		"jmp	@%0\n\t"			\
		" nop\n\t"				\
		".balign 4\n"				\
		"1:	.long 2f\n"			\
		"2:"					\
		: "=&r" (__dummy));			\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा virt_addr_uncached(kaddr)	(0)
#घोषणा uncached_init()			करो अणु पूर्ण जबतक (0)
#घोषणा uncached_resize(size)		BUG()
#घोषणा jump_to_uncached()		करो अणु पूर्ण जबतक (0)
#घोषणा back_to_cached()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_UNCACHED_H */
