<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_CMPXCHG_LOCAL_H
#घोषणा __ASM_GENERIC_CMPXCHG_LOCAL_H

#समावेश <linux/types.h>
#समावेश <linux/irqflags.h>

बाह्य अचिन्हित दीर्घ wrong_size_cmpxchg(अस्थिर व्योम *ptr)
	__noवापस;

/*
 * Generic version of __cmpxchg_local (disables पूर्णांकerrupts). Takes an अचिन्हित
 * दीर्घ parameter, supporting various types of architectures.
 */
अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_local_generic(अस्थिर व्योम *ptr,
		अचिन्हित दीर्घ old, अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags, prev;

	/*
	 * Sanity checking, compile-समय.
	 */
	अगर (size == 8 && माप(अचिन्हित दीर्घ) != 8)
		wrong_size_cmpxchg(ptr);

	raw_local_irq_save(flags);
	चयन (size) अणु
	हाल 1: prev = *(u8 *)ptr;
		अगर (prev == old)
			*(u8 *)ptr = (u8)new;
		अवरोध;
	हाल 2: prev = *(u16 *)ptr;
		अगर (prev == old)
			*(u16 *)ptr = (u16)new;
		अवरोध;
	हाल 4: prev = *(u32 *)ptr;
		अगर (prev == old)
			*(u32 *)ptr = (u32)new;
		अवरोध;
	हाल 8: prev = *(u64 *)ptr;
		अगर (prev == old)
			*(u64 *)ptr = (u64)new;
		अवरोध;
	शेष:
		wrong_size_cmpxchg(ptr);
	पूर्ण
	raw_local_irq_restore(flags);
	वापस prev;
पूर्ण

/*
 * Generic version of __cmpxchg64_local. Takes an u64 parameter.
 */
अटल अंतरभूत u64 __cmpxchg64_local_generic(अस्थिर व्योम *ptr,
		u64 old, u64 new)
अणु
	u64 prev;
	अचिन्हित दीर्घ flags;

	raw_local_irq_save(flags);
	prev = *(u64 *)ptr;
	अगर (prev == old)
		*(u64 *)ptr = new;
	raw_local_irq_restore(flags);
	वापस prev;
पूर्ण

#पूर्ण_अगर
