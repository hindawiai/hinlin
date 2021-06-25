<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic UP xchg and cmpxchg using पूर्णांकerrupt disablement.  Does not
 * support SMP.
 */

#अगर_अघोषित __ASM_GENERIC_CMPXCHG_H
#घोषणा __ASM_GENERIC_CMPXCHG_H

#अगर_घोषित CONFIG_SMP
#त्रुटि "Cannot use generic cmpxchg on SMP"
#पूर्ण_अगर

#समावेश <linux/types.h>
#समावेश <linux/irqflags.h>

#अगर_अघोषित xchg

/*
 * This function करोesn't exist, so you'll get a linker error अगर
 * something tries to करो an invalidly-sized xchg().
 */
बाह्य व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

अटल अंतरभूत
अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, अस्थिर व्योम *ptr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ ret, flags;

	चयन (size) अणु
	हाल 1:
#अगर_घोषित __xchg_u8
		वापस __xchg_u8(x, ptr);
#अन्यथा
		local_irq_save(flags);
		ret = *(अस्थिर u8 *)ptr;
		*(अस्थिर u8 *)ptr = x;
		local_irq_restore(flags);
		वापस ret;
#पूर्ण_अगर /* __xchg_u8 */

	हाल 2:
#अगर_घोषित __xchg_u16
		वापस __xchg_u16(x, ptr);
#अन्यथा
		local_irq_save(flags);
		ret = *(अस्थिर u16 *)ptr;
		*(अस्थिर u16 *)ptr = x;
		local_irq_restore(flags);
		वापस ret;
#पूर्ण_अगर /* __xchg_u16 */

	हाल 4:
#अगर_घोषित __xchg_u32
		वापस __xchg_u32(x, ptr);
#अन्यथा
		local_irq_save(flags);
		ret = *(अस्थिर u32 *)ptr;
		*(अस्थिर u32 *)ptr = x;
		local_irq_restore(flags);
		वापस ret;
#पूर्ण_अगर /* __xchg_u32 */

#अगर_घोषित CONFIG_64BIT
	हाल 8:
#अगर_घोषित __xchg_u64
		वापस __xchg_u64(x, ptr);
#अन्यथा
		local_irq_save(flags);
		ret = *(अस्थिर u64 *)ptr;
		*(अस्थिर u64 *)ptr = x;
		local_irq_restore(flags);
		वापस ret;
#पूर्ण_अगर /* __xchg_u64 */
#पूर्ण_अगर /* CONFIG_64BIT */

	शेष:
		__xchg_called_with_bad_poपूर्णांकer();
		वापस x;
	पूर्ण
पूर्ण

#घोषणा xchg(ptr, x) (अणु							\
	((__typeof__(*(ptr)))						\
		__xchg((अचिन्हित दीर्घ)(x), (ptr), माप(*(ptr))));	\
पूर्ण)

#पूर्ण_अगर /* xchg */

/*
 * Atomic compare and exchange.
 */
#समावेश <यंत्र-generic/cmpxchg-local.h>

#अगर_अघोषित cmpxchg_local
#घोषणा cmpxchg_local(ptr, o, n) (अणु					       \
	((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr), (अचिन्हित दीर्घ)(o),\
			(अचिन्हित दीर्घ)(n), माप(*(ptr))));		       \
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित cmpxchg64_local
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))
#पूर्ण_अगर

#घोषणा cmpxchg(ptr, o, n)	cmpxchg_local((ptr), (o), (n))
#घोषणा cmpxchg64(ptr, o, n)	cmpxchg64_local((ptr), (o), (n))

#पूर्ण_अगर /* __ASM_GENERIC_CMPXCHG_H */
