<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_STRING_H__
#घोषणा __ALPHA_STRING_H__

#अगर_घोषित __KERNEL__

/*
 * GCC of any recent vपूर्णांकage करोesn't करो stupid things with bcopy.
 * EGCS 1.1 knows all about expanding स_नकल अंतरभूत, others करोn't.
 *
 * Similarly क्रम a स_रखो with data = 0.
 */

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम * स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);
#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम * स_हटाओ(व्योम *, स्थिर व्योम *, माप_प्रकार);

/* For backward compatibility with modules.  Unused otherwise.  */
बाह्य व्योम * __स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);

#घोषणा स_नकल __builtin_स_नकल

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम * __स्थिरant_c_स_रखो(व्योम *, अचिन्हित दीर्घ, माप_प्रकार);
बाह्य व्योम * ___स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
बाह्य व्योम * __स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
बाह्य व्योम * स_रखो(व्योम *, पूर्णांक, माप_प्रकार);

/* For gcc 3.x, we cannot have the अंतरभूत function named "memset" because
   the __builtin_स_रखो will attempt to resolve to the अंतरभूत as well,
   leading to a "sorry" about unimplemented recursive inlining.  */
बाह्य अंतरभूत व्योम *__स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	अगर (__builtin_स्थिरant_p(c)) अणु
		अगर (__builtin_स्थिरant_p(n)) अणु
			वापस __builtin_स_रखो(s, c, n);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ c8 = (c & 0xff) * 0x0101010101010101UL;
			वापस __स्थिरant_c_स_रखो(s, c8, n);
		पूर्ण
	पूर्ण
	वापस ___स_रखो(s, c, n);
पूर्ण

#घोषणा स_रखो __स_रखो

#घोषणा __HAVE_ARCH_STRCPY
बाह्य अक्षर * म_नकल(अक्षर *,स्थिर अक्षर *);
#घोषणा __HAVE_ARCH_STRNCPY
बाह्य अक्षर * म_नकलन(अक्षर *, स्थिर अक्षर *, माप_प्रकार);
#घोषणा __HAVE_ARCH_STRCAT
बाह्य अक्षर * म_जोड़ो(अक्षर *, स्थिर अक्षर *);
#घोषणा __HAVE_ARCH_STRNCAT
बाह्य अक्षर * म_जोड़न(अक्षर *, स्थिर अक्षर *, माप_प्रकार);
#घोषणा __HAVE_ARCH_STRCHR
बाह्य अक्षर * म_अक्षर(स्थिर अक्षर *,पूर्णांक);
#घोषणा __HAVE_ARCH_STRRCHR
बाह्य अक्षर * म_खोजप(स्थिर अक्षर *,पूर्णांक);
#घोषणा __HAVE_ARCH_STRLEN
बाह्य माप_प्रकार म_माप(स्थिर अक्षर *);
#घोषणा __HAVE_ARCH_MEMCHR
बाह्य व्योम * स_प्रथम(स्थिर व्योम *, पूर्णांक, माप_प्रकार);

/* The following routine is like स_रखो except that it ग_लिखोs 16-bit
   aligned values.  The DEST and COUNT parameters must be even क्रम 
   correct operation.  */

#घोषणा __HAVE_ARCH_MEMSET16
बाह्य व्योम * __स_रखो16(व्योम *dest, अचिन्हित लघु, माप_प्रकार count);
अटल अंतरभूत व्योम *स_रखो16(uपूर्णांक16_t *p, uपूर्णांक16_t v, माप_प्रकार n)
अणु
	अगर (__builtin_स्थिरant_p(v))
		वापस __स्थिरant_c_स_रखो(p, 0x0001000100010001UL * v, n * 2);
	वापस __स_रखो16(p, v, n * 2);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_STRING_H__ */
