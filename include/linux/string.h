<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STRING_H_
#घोषणा _LINUX_STRING_H_


#समावेश <linux/compiler.h>	/* क्रम अंतरभूत */
#समावेश <linux/types.h>	/* क्रम माप_प्रकार */
#समावेश <linux/मानकघोष.स>	/* क्रम शून्य */
#समावेश <linux/त्रुटिसं.स>	/* क्रम E2BIG */
#समावेश <मानकतर्क.स>
#समावेश <uapi/linux/माला.स>

बाह्य अक्षर *strndup_user(स्थिर अक्षर __user *, दीर्घ);
बाह्य व्योम *memdup_user(स्थिर व्योम __user *, माप_प्रकार);
बाह्य व्योम *vmemdup_user(स्थिर व्योम __user *, माप_प्रकार);
बाह्य व्योम *memdup_user_nul(स्थिर व्योम __user *, माप_प्रकार);

/*
 * Include machine specअगरic अंतरभूत routines
 */
#समावेश <यंत्र/माला.स>

#अगर_अघोषित __HAVE_ARCH_STRCPY
बाह्य अक्षर * म_नकल(अक्षर *,स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNCPY
बाह्य अक्षर * म_नकलन(अक्षर *,स्थिर अक्षर *, __kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRLCPY
माप_प्रकार strlcpy(अक्षर *, स्थिर अक्षर *, माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRSCPY
sमाप_प्रकार strscpy(अक्षर *, स्थिर अक्षर *, माप_प्रकार);
#पूर्ण_अगर

/* Wraps calls to strscpy()/स_रखो(), no arch specअगरic code required */
sमाप_प्रकार strscpy_pad(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count);

#अगर_अघोषित __HAVE_ARCH_STRCAT
बाह्य अक्षर * म_जोड़ो(अक्षर *, स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNCAT
बाह्य अक्षर * म_जोड़न(अक्षर *, स्थिर अक्षर *, __kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRLCAT
बाह्य माप_प्रकार strlcat(अक्षर *, स्थिर अक्षर *, __kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRCMP
बाह्य पूर्णांक म_भेद(स्थिर अक्षर *,स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNCMP
बाह्य पूर्णांक म_भेदन(स्थिर अक्षर *,स्थिर अक्षर *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRCASECMP
बाह्य पूर्णांक strहालcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNCASECMP
बाह्य पूर्णांक strnहालcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2, माप_प्रकार n);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRCHR
बाह्य अक्षर * म_अक्षर(स्थिर अक्षर *,पूर्णांक);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRCHRNUL
बाह्य अक्षर * म_अक्षरnul(स्थिर अक्षर *,पूर्णांक);
#पूर्ण_अगर
बाह्य अक्षर * strnchrnul(स्थिर अक्षर *, माप_प्रकार, पूर्णांक);
#अगर_अघोषित __HAVE_ARCH_STRNCHR
बाह्य अक्षर * strnchr(स्थिर अक्षर *, माप_प्रकार, पूर्णांक);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRRCHR
बाह्य अक्षर * म_खोजप(स्थिर अक्षर *,पूर्णांक);
#पूर्ण_अगर
बाह्य अक्षर * __must_check skip_spaces(स्थिर अक्षर *);

बाह्य अक्षर *strim(अक्षर *);

अटल अंतरभूत __must_check अक्षर *म_मालाip(अक्षर *str)
अणु
	वापस strim(str);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_STRSTR
बाह्य अक्षर * म_माला(स्थिर अक्षर *, स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNSTR
बाह्य अक्षर * strnstr(स्थिर अक्षर *, स्थिर अक्षर *, माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRLEN
बाह्य __kernel_माप_प्रकार म_माप(स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRNLEN
बाह्य __kernel_माप_प्रकार strnlen(स्थिर अक्षर *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRPBRK
बाह्य अक्षर * strpbrk(स्थिर अक्षर *,स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRSEP
बाह्य अक्षर * strsep(अक्षर **,स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRSPN
बाह्य __kernel_माप_प्रकार म_अखोज(स्थिर अक्षर *,स्थिर अक्षर *);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_STRCSPN
बाह्य __kernel_माप_प्रकार म_खोज(स्थिर अक्षर *,स्थिर अक्षर *);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET
बाह्य व्योम * स_रखो(व्योम *,पूर्णांक,__kernel_माप_प्रकार);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET16
बाह्य व्योम *स_रखो16(uपूर्णांक16_t *, uपूर्णांक16_t, __kernel_माप_प्रकार);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET32
बाह्य व्योम *स_रखो32(uपूर्णांक32_t *, uपूर्णांक32_t, __kernel_माप_प्रकार);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET64
बाह्य व्योम *स_रखो64(uपूर्णांक64_t *, uपूर्णांक64_t, __kernel_माप_प्रकार);
#पूर्ण_अगर

अटल अंतरभूत व्योम *स_रखो_l(अचिन्हित दीर्घ *p, अचिन्हित दीर्घ v,
		__kernel_माप_प्रकार n)
अणु
	अगर (BITS_PER_LONG == 32)
		वापस स_रखो32((uपूर्णांक32_t *)p, v, n);
	अन्यथा
		वापस स_रखो64((uपूर्णांक64_t *)p, v, n);
पूर्ण

अटल अंतरभूत व्योम *स_रखो_p(व्योम **p, व्योम *v, __kernel_माप_प्रकार n)
अणु
	अगर (BITS_PER_LONG == 32)
		वापस स_रखो32((uपूर्णांक32_t *)p, (uपूर्णांकptr_t)v, n);
	अन्यथा
		वापस स_रखो64((uपूर्णांक64_t *)p, (uपूर्णांकptr_t)v, n);
पूर्ण

बाह्य व्योम **__memcat_p(व्योम **a, व्योम **b);
#घोषणा memcat_p(a, b) (अणु					\
	BUILD_BUG_ON_MSG(!__same_type(*(a), *(b)),		\
			 "type mismatch in memcat_p()");	\
	(typeof(*a) *)__memcat_p((व्योम **)(a), (व्योम **)(b));	\
पूर्ण)

#अगर_अघोषित __HAVE_ARCH_MEMCPY
बाह्य व्योम * स_नकल(व्योम *,स्थिर व्योम *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_MEMMOVE
बाह्य व्योम * स_हटाओ(व्योम *,स्थिर व्योम *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_MEMSCAN
बाह्य व्योम * memscan(व्योम *,पूर्णांक,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_MEMCMP
बाह्य पूर्णांक स_भेद(स्थिर व्योम *,स्थिर व्योम *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_BCMP
बाह्य पूर्णांक bcmp(स्थिर व्योम *,स्थिर व्योम *,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_MEMCHR
बाह्य व्योम * स_प्रथम(स्थिर व्योम *,पूर्णांक,__kernel_माप_प्रकार);
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_MEMCPY_FLUSHCACHE
अटल अंतरभूत व्योम स_नकल_flushcache(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt)
अणु
	स_नकल(dst, src, cnt);
पूर्ण
#पूर्ण_अगर

व्योम *स_प्रथम_inv(स्थिर व्योम *s, पूर्णांक c, माप_प्रकार n);
अक्षर *strreplace(अक्षर *s, अक्षर old, अक्षर new);

बाह्य व्योम kमुक्त_स्थिर(स्थिर व्योम *x);

बाह्य अक्षर *kstrdup(स्थिर अक्षर *s, gfp_t gfp) __दो_स्मृति;
बाह्य स्थिर अक्षर *kstrdup_स्थिर(स्थिर अक्षर *s, gfp_t gfp);
बाह्य अक्षर *kstrndup(स्थिर अक्षर *s, माप_प्रकार len, gfp_t gfp);
बाह्य व्योम *kmemdup(स्थिर व्योम *src, माप_प्रकार len, gfp_t gfp);
बाह्य अक्षर *kmemdup_nul(स्थिर अक्षर *s, माप_प्रकार len, gfp_t gfp);

बाह्य अक्षर **argv_split(gfp_t gfp, स्थिर अक्षर *str, पूर्णांक *argcp);
बाह्य व्योम argv_मुक्त(अक्षर **argv);

बाह्य bool sysfs_streq(स्थिर अक्षर *s1, स्थिर अक्षर *s2);
बाह्य पूर्णांक kstrtobool(स्थिर अक्षर *s, bool *res);
अटल अंतरभूत पूर्णांक strtobool(स्थिर अक्षर *s, bool *res)
अणु
	वापस kstrtobool(s, res);
पूर्ण

पूर्णांक match_string(स्थिर अक्षर * स्थिर *array, माप_प्रकार n, स्थिर अक्षर *string);
पूर्णांक __sysfs_match_string(स्थिर अक्षर * स्थिर *array, माप_प्रकार n, स्थिर अक्षर *s);

/**
 * sysfs_match_string - matches given string in an array
 * @_a: array of strings
 * @_s: string to match with
 *
 * Helper क्रम __sysfs_match_string(). Calculates the size of @a स्वतःmatically.
 */
#घोषणा sysfs_match_string(_a, _s) __sysfs_match_string(_a, ARRAY_SIZE(_a), _s)

#अगर_घोषित CONFIG_BINARY_PRINTF
पूर्णांक vbin_म_लिखो(u32 *bin_buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक bstr_म_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, स्थिर u32 *bin_buf);
पूर्णांक bम_लिखो(u32 *bin_buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...) __म_लिखो(3, 4);
#पूर्ण_अगर

बाह्य sमाप_प्रकार memory_पढ़ो_from_buffer(व्योम *to, माप_प्रकार count, loff_t *ppos,
				       स्थिर व्योम *from, माप_प्रकार available);

पूर्णांक ptr_to_hashval(स्थिर व्योम *ptr, अचिन्हित दीर्घ *hashval_out);

/**
 * strstarts - करोes @str start with @prefix?
 * @str: string to examine
 * @prefix: prefix to look क्रम.
 */
अटल अंतरभूत bool strstarts(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	वापस म_भेदन(str, prefix, म_माप(prefix)) == 0;
पूर्ण

माप_प्रकार memweight(स्थिर व्योम *ptr, माप_प्रकार bytes);

/**
 * memzero_explicit - Fill a region of memory (e.g. sensitive
 *		      keying data) with 0s.
 * @s: Poपूर्णांकer to the start of the area.
 * @count: The size of the area.
 *
 * Note: usually using स_रखो() is just fine (!), but in हालs
 * where clearing out _local_ data at the end of a scope is
 * necessary, memzero_explicit() should be used instead in
 * order to prevent the compiler from optimising away zeroing.
 *
 * memzero_explicit() करोesn't need an arch-specअगरic version as
 * it just invokes the one of स_रखो() implicitly.
 */
अटल अंतरभूत व्योम memzero_explicit(व्योम *s, माप_प्रकार count)
अणु
	स_रखो(s, 0, count);
	barrier_data(s);
पूर्ण

/**
 * kbasename - वापस the last part of a pathname.
 *
 * @path: path to extract the filename from.
 */
अटल अंतरभूत स्थिर अक्षर *kbasename(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *tail = म_खोजप(path, '/');
	वापस tail ? tail + 1 : path;
पूर्ण

#घोषणा __FORTIFY_INLINE बाह्य __always_अंतरभूत __attribute__((gnu_अंतरभूत))
#घोषणा __RENAME(x) __यंत्र__(#x)

व्योम क्रमtअगरy_panic(स्थिर अक्षर *name) __noवापस __cold;
व्योम __पढ़ो_overflow(व्योम) __compileसमय_error("detected read beyond size of object passed as 1st parameter");
व्योम __पढ़ो_overflow2(व्योम) __compileसमय_error("detected read beyond size of object passed as 2nd parameter");
व्योम __पढ़ो_overflow3(व्योम) __compileसमय_error("detected read beyond size of object passed as 3rd parameter");
व्योम __ग_लिखो_overflow(व्योम) __compileसमय_error("detected write beyond size of object passed as 1st parameter");

#अगर !defined(__NO_FORTIFY) && defined(__OPTIMIZE__) && defined(CONFIG_FORTIFY_SOURCE)
#समावेश <linux/क्रमtअगरy-माला.स>
#पूर्ण_अगर

/**
 * स_नकल_and_pad - Copy one buffer to another with padding
 * @dest: Where to copy to
 * @dest_len: The destination buffer size
 * @src: Where to copy from
 * @count: The number of bytes to copy
 * @pad: Character to use क्रम padding अगर space is left in destination.
 */
अटल अंतरभूत व्योम स_नकल_and_pad(व्योम *dest, माप_प्रकार dest_len,
				  स्थिर व्योम *src, माप_प्रकार count, पूर्णांक pad)
अणु
	अगर (dest_len > count) अणु
		स_नकल(dest, src, count);
		स_रखो(dest + count, pad,  dest_len - count);
	पूर्ण अन्यथा
		स_नकल(dest, src, dest_len);
पूर्ण

/**
 * str_has_prefix - Test अगर a string has a given prefix
 * @str: The string to test
 * @prefix: The string to see अगर @str starts with
 *
 * A common way to test a prefix of a string is to करो:
 *  म_भेदन(str, prefix, माप(prefix) - 1)
 *
 * But this can lead to bugs due to typos, or अगर prefix is a poपूर्णांकer
 * and not a स्थिरant. Instead use str_has_prefix().
 *
 * Returns:
 * * म_माप(@prefix) अगर @str starts with @prefix
 * * 0 अगर @str करोes not start with @prefix
 */
अटल __always_अंतरभूत माप_प्रकार str_has_prefix(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	माप_प्रकार len = म_माप(prefix);
	वापस म_भेदन(str, prefix, len) == 0 ? len : 0;
पूर्ण

#पूर्ण_अगर /* _LINUX_STRING_H_ */
