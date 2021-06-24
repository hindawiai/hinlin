<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FORTIFY_STRING_H_
#घोषणा _LINUX_FORTIFY_STRING_H_


#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
बाह्य व्योम *__underlying_स_प्रथम(स्थिर व्योम *p, पूर्णांक c, __kernel_माप_प्रकार size) __RENAME(स_प्रथम);
बाह्य पूर्णांक __underlying_स_भेद(स्थिर व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size) __RENAME(स_भेद);
बाह्य व्योम *__underlying_स_नकल(व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size) __RENAME(स_नकल);
बाह्य व्योम *__underlying_स_हटाओ(व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size) __RENAME(स_हटाओ);
बाह्य व्योम *__underlying_स_रखो(व्योम *p, पूर्णांक c, __kernel_माप_प्रकार size) __RENAME(स_रखो);
बाह्य अक्षर *__underlying_म_जोड़ो(अक्षर *p, स्थिर अक्षर *q) __RENAME(म_जोड़ो);
बाह्य अक्षर *__underlying_म_नकल(अक्षर *p, स्थिर अक्षर *q) __RENAME(म_नकल);
बाह्य __kernel_माप_प्रकार __underlying_म_माप(स्थिर अक्षर *p) __RENAME(म_माप);
बाह्य अक्षर *__underlying_म_जोड़न(अक्षर *p, स्थिर अक्षर *q, __kernel_माप_प्रकार count) __RENAME(म_जोड़न);
बाह्य अक्षर *__underlying_म_नकलन(अक्षर *p, स्थिर अक्षर *q, __kernel_माप_प्रकार size) __RENAME(म_नकलन);
#अन्यथा
#घोषणा __underlying_स_प्रथम	__builtin_स_प्रथम
#घोषणा __underlying_स_भेद	__builtin_स_भेद
#घोषणा __underlying_स_नकल	__builtin_स_नकल
#घोषणा __underlying_स_हटाओ	__builtin_स_हटाओ
#घोषणा __underlying_स_रखो	__builtin_स_रखो
#घोषणा __underlying_म_जोड़ो	__builtin_म_जोड़ो
#घोषणा __underlying_म_नकल	__builtin_म_नकल
#घोषणा __underlying_म_माप	__builtin_म_माप
#घोषणा __underlying_म_जोड़न	__builtin_म_जोड़न
#घोषणा __underlying_म_नकलन	__builtin_म_नकलन
#पूर्ण_अगर

__FORTIFY_INLINE अक्षर *म_नकलन(अक्षर *p, स्थिर अक्षर *q, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 1);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__ग_लिखो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_म_नकलन(p, q, size);
पूर्ण

__FORTIFY_INLINE अक्षर *म_जोड़ो(अक्षर *p, स्थिर अक्षर *q)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 1);

	अगर (p_size == (माप_प्रकार)-1)
		वापस __underlying_म_जोड़ो(p, q);
	अगर (strlcat(p, q, p_size) >= p_size)
		क्रमtअगरy_panic(__func__);
	वापस p;
पूर्ण

__FORTIFY_INLINE __kernel_माप_प्रकार म_माप(स्थिर अक्षर *p)
अणु
	__kernel_माप_प्रकार ret;
	माप_प्रकार p_size = __builtin_object_size(p, 1);

	/* Work around gcc excess stack consumption issue */
	अगर (p_size == (माप_प्रकार)-1 ||
		(__builtin_स्थिरant_p(p[p_size - 1]) && p[p_size - 1] == '\0'))
		वापस __underlying_म_माप(p);
	ret = strnlen(p, p_size);
	अगर (p_size <= ret)
		क्रमtअगरy_panic(__func__);
	वापस ret;
पूर्ण

बाह्य __kernel_माप_प्रकार __real_strnlen(स्थिर अक्षर *, __kernel_माप_प्रकार) __RENAME(strnlen);
__FORTIFY_INLINE __kernel_माप_प्रकार strnlen(स्थिर अक्षर *p, __kernel_माप_प्रकार maxlen)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 1);
	__kernel_माप_प्रकार ret = __real_strnlen(p, maxlen < p_size ? maxlen : p_size);

	अगर (p_size <= ret && maxlen != ret)
		क्रमtअगरy_panic(__func__);
	वापस ret;
पूर्ण

/* defined after क्रमtअगरied म_माप to reuse it */
बाह्य माप_प्रकार __real_strlcpy(अक्षर *, स्थिर अक्षर *, माप_प्रकार) __RENAME(strlcpy);
__FORTIFY_INLINE माप_प्रकार strlcpy(अक्षर *p, स्थिर अक्षर *q, माप_प्रकार size)
अणु
	माप_प्रकार ret;
	माप_प्रकार p_size = __builtin_object_size(p, 1);
	माप_प्रकार q_size = __builtin_object_size(q, 1);

	अगर (p_size == (माप_प्रकार)-1 && q_size == (माप_प्रकार)-1)
		वापस __real_strlcpy(p, q, size);
	ret = म_माप(q);
	अगर (size) अणु
		माप_प्रकार len = (ret >= size) ? size - 1 : ret;

		अगर (__builtin_स्थिरant_p(len) && len >= p_size)
			__ग_लिखो_overflow();
		अगर (len >= p_size)
			क्रमtअगरy_panic(__func__);
		__underlying_स_नकल(p, q, len);
		p[len] = '\0';
	पूर्ण
	वापस ret;
पूर्ण

/* defined after क्रमtअगरied strnlen to reuse it */
बाह्य sमाप_प्रकार __real_strscpy(अक्षर *, स्थिर अक्षर *, माप_प्रकार) __RENAME(strscpy);
__FORTIFY_INLINE sमाप_प्रकार strscpy(अक्षर *p, स्थिर अक्षर *q, माप_प्रकार size)
अणु
	माप_प्रकार len;
	/* Use string size rather than possible enclosing काष्ठा size. */
	माप_प्रकार p_size = __builtin_object_size(p, 1);
	माप_प्रकार q_size = __builtin_object_size(q, 1);

	/* If we cannot get size of p and q शेष to call strscpy. */
	अगर (p_size == (माप_प्रकार) -1 && q_size == (माप_प्रकार) -1)
		वापस __real_strscpy(p, q, size);

	/*
	 * If size can be known at compile समय and is greater than
	 * p_size, generate a compile समय ग_लिखो overflow error.
	 */
	अगर (__builtin_स्थिरant_p(size) && size > p_size)
		__ग_लिखो_overflow();

	/*
	 * This call protects from पढ़ो overflow, because len will शेष to q
	 * length अगर it smaller than size.
	 */
	len = strnlen(q, size);
	/*
	 * If len equals size, we will copy only size bytes which leads to
	 * -E2BIG being वापसed.
	 * Otherwise we will copy len + 1 because of the final '\O'.
	 */
	len = len == size ? size : len + 1;

	/*
	 * Generate a runसमय ग_लिखो overflow error अगर len is greater than
	 * p_size.
	 */
	अगर (len > p_size)
		क्रमtअगरy_panic(__func__);

	/*
	 * We can now safely call vanilla strscpy because we are रक्षित from:
	 * 1. Read overflow thanks to call to strnlen().
	 * 2. Write overflow thanks to above अगरs.
	 */
	वापस __real_strscpy(p, q, len);
पूर्ण

/* defined after क्रमtअगरied म_माप and strnlen to reuse them */
__FORTIFY_INLINE अक्षर *म_जोड़न(अक्षर *p, स्थिर अक्षर *q, __kernel_माप_प्रकार count)
अणु
	माप_प्रकार p_len, copy_len;
	माप_प्रकार p_size = __builtin_object_size(p, 1);
	माप_प्रकार q_size = __builtin_object_size(q, 1);

	अगर (p_size == (माप_प्रकार)-1 && q_size == (माप_प्रकार)-1)
		वापस __underlying_म_जोड़न(p, q, count);
	p_len = म_माप(p);
	copy_len = strnlen(q, count);
	अगर (p_size < p_len + copy_len + 1)
		क्रमtअगरy_panic(__func__);
	__underlying_स_नकल(p + p_len, q, copy_len);
	p[p_len + copy_len] = '\0';
	वापस p;
पूर्ण

__FORTIFY_INLINE व्योम *स_रखो(व्योम *p, पूर्णांक c, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__ग_लिखो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_स_रखो(p, c, size);
पूर्ण

__FORTIFY_INLINE व्योम *स_नकल(व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);
	माप_प्रकार q_size = __builtin_object_size(q, 0);

	अगर (__builtin_स्थिरant_p(size)) अणु
		अगर (p_size < size)
			__ग_लिखो_overflow();
		अगर (q_size < size)
			__पढ़ो_overflow2();
	पूर्ण
	अगर (p_size < size || q_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_स_नकल(p, q, size);
पूर्ण

__FORTIFY_INLINE व्योम *स_हटाओ(व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);
	माप_प्रकार q_size = __builtin_object_size(q, 0);

	अगर (__builtin_स्थिरant_p(size)) अणु
		अगर (p_size < size)
			__ग_लिखो_overflow();
		अगर (q_size < size)
			__पढ़ो_overflow2();
	पूर्ण
	अगर (p_size < size || q_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_स_हटाओ(p, q, size);
पूर्ण

बाह्य व्योम *__real_memscan(व्योम *, पूर्णांक, __kernel_माप_प्रकार) __RENAME(memscan);
__FORTIFY_INLINE व्योम *memscan(व्योम *p, पूर्णांक c, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__पढ़ो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __real_memscan(p, c, size);
पूर्ण

__FORTIFY_INLINE पूर्णांक स_भेद(स्थिर व्योम *p, स्थिर व्योम *q, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);
	माप_प्रकार q_size = __builtin_object_size(q, 0);

	अगर (__builtin_स्थिरant_p(size)) अणु
		अगर (p_size < size)
			__पढ़ो_overflow();
		अगर (q_size < size)
			__पढ़ो_overflow2();
	पूर्ण
	अगर (p_size < size || q_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_स_भेद(p, q, size);
पूर्ण

__FORTIFY_INLINE व्योम *स_प्रथम(स्थिर व्योम *p, पूर्णांक c, __kernel_माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__पढ़ो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __underlying_स_प्रथम(p, c, size);
पूर्ण

व्योम *__real_स_प्रथम_inv(स्थिर व्योम *s, पूर्णांक c, माप_प्रकार n) __RENAME(स_प्रथम_inv);
__FORTIFY_INLINE व्योम *स_प्रथम_inv(स्थिर व्योम *p, पूर्णांक c, माप_प्रकार size)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__पढ़ो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __real_स_प्रथम_inv(p, c, size);
पूर्ण

बाह्य व्योम *__real_kmemdup(स्थिर व्योम *src, माप_प्रकार len, gfp_t gfp) __RENAME(kmemdup);
__FORTIFY_INLINE व्योम *kmemdup(स्थिर व्योम *p, माप_प्रकार size, gfp_t gfp)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 0);

	अगर (__builtin_स्थिरant_p(size) && p_size < size)
		__पढ़ो_overflow();
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	वापस __real_kmemdup(p, size, gfp);
पूर्ण

/* defined after क्रमtअगरied म_माप and स_नकल to reuse them */
__FORTIFY_INLINE अक्षर *म_नकल(अक्षर *p, स्थिर अक्षर *q)
अणु
	माप_प्रकार p_size = __builtin_object_size(p, 1);
	माप_प्रकार q_size = __builtin_object_size(q, 1);
	माप_प्रकार size;

	अगर (p_size == (माप_प्रकार)-1 && q_size == (माप_प्रकार)-1)
		वापस __underlying_म_नकल(p, q);
	size = म_माप(q) + 1;
	/* test here to use the more stringent object size */
	अगर (p_size < size)
		क्रमtअगरy_panic(__func__);
	स_नकल(p, q, size);
	वापस p;
पूर्ण

/* Don't use these outside the FORITFY_SOURCE implementation */
#अघोषित __underlying_स_प्रथम
#अघोषित __underlying_स_भेद
#अघोषित __underlying_स_नकल
#अघोषित __underlying_स_हटाओ
#अघोषित __underlying_स_रखो
#अघोषित __underlying_म_जोड़ो
#अघोषित __underlying_म_नकल
#अघोषित __underlying_म_माप
#अघोषित __underlying_म_जोड़न
#अघोषित __underlying_म_नकलन

#पूर्ण_अगर /* _LINUX_FORTIFY_STRING_H_ */
