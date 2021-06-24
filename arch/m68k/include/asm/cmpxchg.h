<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_M68K_CMPXCHG__
#घोषणा __ARCH_M68K_CMPXCHG__

#समावेश <linux/irqflags.h>

काष्ठा __xchg_dummy अणु अचिन्हित दीर्घ a[100]; पूर्ण;
#घोषणा __xg(x) ((अस्थिर काष्ठा __xchg_dummy *)(x))

बाह्य अचिन्हित दीर्घ __invalid_xchg_size(अचिन्हित दीर्घ, अस्थिर व्योम *, पूर्णांक);

#अगर_अघोषित CONFIG_RMW_INSNS
अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, अस्थिर व्योम * ptr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags, पंचांगp;

	local_irq_save(flags);

	चयन (size) अणु
	हाल 1:
		पंचांगp = *(u8 *)ptr;
		*(u8 *)ptr = x;
		x = पंचांगp;
		अवरोध;
	हाल 2:
		पंचांगp = *(u16 *)ptr;
		*(u16 *)ptr = x;
		x = पंचांगp;
		अवरोध;
	हाल 4:
		पंचांगp = *(u32 *)ptr;
		*(u32 *)ptr = x;
		x = पंचांगp;
		अवरोध;
	शेष:
		पंचांगp = __invalid_xchg_size(x, ptr, size);
		अवरोध;
	पूर्ण

	local_irq_restore(flags);
	वापस x;
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, अस्थिर व्योम * ptr, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		__यंत्र__ __अस्थिर__
			("moveb %2,%0\n\t"
			 "1:\n\t"
			 "casb %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(ptr)) : "memory");
		अवरोध;
	हाल 2:
		__यंत्र__ __अस्थिर__
			("movew %2,%0\n\t"
			 "1:\n\t"
			 "casw %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(ptr)) : "memory");
		अवरोध;
	हाल 4:
		__यंत्र__ __अस्थिर__
			("movel %2,%0\n\t"
			 "1:\n\t"
			 "casl %0,%1,%2\n\t"
			 "jne 1b"
			 : "=&d" (x) : "d" (x), "m" (*__xg(ptr)) : "memory");
		अवरोध;
	शेष:
		x = __invalid_xchg_size(x, ptr, size);
		अवरोध;
	पूर्ण
	वापस x;
पूर्ण
#पूर्ण_अगर

#घोषणा xchg(ptr,x) (अणु(__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(x),(ptr),माप(*(ptr)));पूर्ण)

#समावेश <यंत्र-generic/cmpxchg-local.h>

#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

बाह्य अचिन्हित दीर्घ __invalid_cmpxchg_size(अस्थिर व्योम *,
					    अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक);

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */
#अगर_घोषित CONFIG_RMW_INSNS

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg(अस्थिर व्योम *p, अचिन्हित दीर्घ old,
				      अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		__यंत्र__ __अस्थिर__ ("casb %0,%2,%1"
				      : "=d" (old), "=m" (*(अक्षर *)p)
				      : "d" (new), "0" (old), "m" (*(अक्षर *)p));
		अवरोध;
	हाल 2:
		__यंत्र__ __अस्थिर__ ("casw %0,%2,%1"
				      : "=d" (old), "=m" (*(लघु *)p)
				      : "d" (new), "0" (old), "m" (*(लघु *)p));
		अवरोध;
	हाल 4:
		__यंत्र__ __अस्थिर__ ("casl %0,%2,%1"
				      : "=d" (old), "=m" (*(पूर्णांक *)p)
				      : "d" (new), "0" (old), "m" (*(पूर्णांक *)p));
		अवरोध;
	शेष:
		old = __invalid_cmpxchg_size(p, old, new, size);
		अवरोध;
	पूर्ण
	वापस old;
पूर्ण

#घोषणा cmpxchg(ptr, o, n)						    \
	(अणु(__typeof__(*(ptr)))__cmpxchg((ptr), (अचिन्हित दीर्घ)(o),	    \
			(अचिन्हित दीर्घ)(n), माप(*(ptr)));पूर्ण)
#घोषणा cmpxchg_local(ptr, o, n)					    \
	(अणु(__typeof__(*(ptr)))__cmpxchg((ptr), (अचिन्हित दीर्घ)(o),	    \
			(अचिन्हित दीर्घ)(n), माप(*(ptr)));पूर्ण)

#घोषणा cmpxchg64(ptr, o, n)	cmpxchg64_local((ptr), (o), (n))

#अन्यथा

#समावेश <यंत्र-generic/cmpxchg.h>

#पूर्ण_अगर

#पूर्ण_अगर /* __ARCH_M68K_CMPXCHG__ */
