<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_STRING_32_H
#घोषणा _ASM_X86_STRING_32_H

#अगर_घोषित __KERNEL__

/* Let gcc decide whether to अंतरभूत or use the out of line functions */

#घोषणा __HAVE_ARCH_STRCPY
बाह्य अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src);

#घोषणा __HAVE_ARCH_STRNCPY
बाह्य अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count);

#घोषणा __HAVE_ARCH_STRCAT
बाह्य अक्षर *म_जोड़ो(अक्षर *dest, स्थिर अक्षर *src);

#घोषणा __HAVE_ARCH_STRNCAT
बाह्य अक्षर *म_जोड़न(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count);

#घोषणा __HAVE_ARCH_STRCMP
बाह्य पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct);

#घोषणा __HAVE_ARCH_STRNCMP
बाह्य पूर्णांक म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count);

#घोषणा __HAVE_ARCH_STRCHR
बाह्य अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c);

#घोषणा __HAVE_ARCH_STRLEN
बाह्य माप_प्रकार म_माप(स्थिर अक्षर *s);

अटल __always_अंतरभूत व्योम *__स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	पूर्णांक d0, d1, d2;
	यंत्र अस्थिर("rep ; movsl\n\t"
		     "movl %4,%%ecx\n\t"
		     "andl $3,%%ecx\n\t"
		     "jz 1f\n\t"
		     "rep ; movsb\n\t"
		     "1:"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (n / 4), "g" (n), "1" ((दीर्घ)to), "2" ((दीर्घ)from)
		     : "memory");
	वापस to;
पूर्ण

/*
 * This looks ugly, but the compiler can optimize it totally,
 * as the count is स्थिरant.
 */
अटल __always_अंतरभूत व्योम *__स्थिरant_स_नकल(व्योम *to, स्थिर व्योम *from,
					       माप_प्रकार n)
अणु
	दीर्घ esi, edi;
	अगर (!n)
		वापस to;

	चयन (n) अणु
	हाल 1:
		*(अक्षर *)to = *(अक्षर *)from;
		वापस to;
	हाल 2:
		*(लघु *)to = *(लघु *)from;
		वापस to;
	हाल 4:
		*(पूर्णांक *)to = *(पूर्णांक *)from;
		वापस to;
	हाल 3:
		*(लघु *)to = *(लघु *)from;
		*((अक्षर *)to + 2) = *((अक्षर *)from + 2);
		वापस to;
	हाल 5:
		*(पूर्णांक *)to = *(पूर्णांक *)from;
		*((अक्षर *)to + 4) = *((अक्षर *)from + 4);
		वापस to;
	हाल 6:
		*(पूर्णांक *)to = *(पूर्णांक *)from;
		*((लघु *)to + 2) = *((लघु *)from + 2);
		वापस to;
	हाल 8:
		*(पूर्णांक *)to = *(पूर्णांक *)from;
		*((पूर्णांक *)to + 1) = *((पूर्णांक *)from + 1);
		वापस to;
	पूर्ण

	esi = (दीर्घ)from;
	edi = (दीर्घ)to;
	अगर (n >= 5 * 4) अणु
		/* large block: use rep prefix */
		पूर्णांक ecx;
		यंत्र अस्थिर("rep ; movsl"
			     : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
			     : "0" (n / 4), "1" (edi), "2" (esi)
			     : "memory"
		);
	पूर्ण अन्यथा अणु
		/* small block: करोn't clobber ecx + smaller code */
		अगर (n >= 4 * 4)
			यंत्र अस्थिर("movsl"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memory");
		अगर (n >= 3 * 4)
			यंत्र अस्थिर("movsl"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memory");
		अगर (n >= 2 * 4)
			यंत्र अस्थिर("movsl"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memory");
		अगर (n >= 1 * 4)
			यंत्र अस्थिर("movsl"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memory");
	पूर्ण
	चयन (n % 4) अणु
		/* tail */
	हाल 0:
		वापस to;
	हाल 1:
		यंत्र अस्थिर("movsb"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memory");
		वापस to;
	हाल 2:
		यंत्र अस्थिर("movsw"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memory");
		वापस to;
	शेष:
		यंत्र अस्थिर("movsw\n\tmovsb"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memory");
		वापस to;
	पूर्ण
पूर्ण

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम *स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);

#अगर_अघोषित CONFIG_FORTIFY_SOURCE
#अगर_घोषित CONFIG_X86_USE_3DNOW

#समावेश <यंत्र/mmx.h>

/*
 *	This CPU favours 3DNow strongly (eg AMD Athlon)
 */

अटल अंतरभूत व्योम *__स्थिरant_स_नकल3d(व्योम *to, स्थिर व्योम *from, माप_प्रकार len)
अणु
	अगर (len < 512)
		वापस __स्थिरant_स_नकल(to, from, len);
	वापस _mmx_स_नकल(to, from, len);
पूर्ण

अटल अंतरभूत व्योम *__स_नकल3d(व्योम *to, स्थिर व्योम *from, माप_प्रकार len)
अणु
	अगर (len < 512)
		वापस __स_नकल(to, from, len);
	वापस _mmx_स_नकल(to, from, len);
पूर्ण

#घोषणा स_नकल(t, f, n)				\
	(__builtin_स्थिरant_p((n))		\
	 ? __स्थिरant_स_नकल3d((t), (f), (n))	\
	 : __स_नकल3d((t), (f), (n)))

#अन्यथा

/*
 *	No 3D Now!
 */

#घोषणा स_नकल(t, f, n) __builtin_स_नकल(t, f, n)

#पूर्ण_अगर
#पूर्ण_अगर /* !CONFIG_FORTIFY_SOURCE */

#घोषणा __HAVE_ARCH_MEMMOVE
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);

बाह्य पूर्णांक स_भेद(स्थिर व्योम *, स्थिर व्योम *, माप_प्रकार);
#अगर_अघोषित CONFIG_FORTIFY_SOURCE
#घोषणा स_भेद __builtin_स_भेद
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_MEMCHR
बाह्य व्योम *स_प्रथम(स्थिर व्योम *cs, पूर्णांक c, माप_प्रकार count);

अटल अंतरभूत व्योम *__स_रखो_generic(व्योम *s, अक्षर c, माप_प्रकार count)
अणु
	पूर्णांक d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosb"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (c), "1" (s), "0" (count)
		     : "memory");
	वापस s;
पूर्ण

/* we might want to ग_लिखो optimized versions of these later */
#घोषणा __स्थिरant_count_स_रखो(s, c, count) __स_रखो_generic((s), (c), (count))

/* Added by Gertjan van Wingerde to make minix and sysv module work */
#घोषणा __HAVE_ARCH_STRNLEN
बाह्य माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार count);
/* end of additional stuff */

#घोषणा __HAVE_ARCH_STRSTR
बाह्य अक्षर *म_माला(स्थिर अक्षर *cs, स्थिर अक्षर *ct);

#घोषणा __स_रखो(s, c, count)				\
	(__builtin_स्थिरant_p(count)			\
	 ? __स्थिरant_count_स_रखो((s), (c), (count))	\
	 : __स_रखो_generic((s), (c), (count)))

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम *स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
#अगर_अघोषित CONFIG_FORTIFY_SOURCE
#घोषणा स_रखो(s, c, count) __builtin_स_रखो(s, c, count)
#पूर्ण_अगर /* !CONFIG_FORTIFY_SOURCE */

#घोषणा __HAVE_ARCH_MEMSET16
अटल अंतरभूत व्योम *स_रखो16(uपूर्णांक16_t *s, uपूर्णांक16_t v, माप_प्रकार n)
अणु
	पूर्णांक d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosw"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memory");
	वापस s;
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET32
अटल अंतरभूत व्योम *स_रखो32(uपूर्णांक32_t *s, uपूर्णांक32_t v, माप_प्रकार n)
अणु
	पूर्णांक d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosl"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memory");
	वापस s;
पूर्ण

/*
 * find the first occurrence of byte 'c', or 1 past the area अगर none
 */
#घोषणा __HAVE_ARCH_MEMSCAN
बाह्य व्योम *memscan(व्योम *addr, पूर्णांक c, माप_प्रकार size);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_X86_STRING_32_H */
