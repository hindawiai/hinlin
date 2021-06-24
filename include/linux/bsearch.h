<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BSEARCH_H
#घोषणा _LINUX_BSEARCH_H

#समावेश <linux/types.h>

अटल __always_अंतरभूत
व्योम *__अंतरभूत_द्वा_खोज(स्थिर व्योम *key, स्थिर व्योम *base, माप_प्रकार num, माप_प्रकार size, cmp_func_t cmp)
अणु
	स्थिर अक्षर *pivot;
	पूर्णांक result;

	जबतक (num > 0) अणु
		pivot = base + (num >> 1) * size;
		result = cmp(key, pivot);

		अगर (result == 0)
			वापस (व्योम *)pivot;

		अगर (result > 0) अणु
			base = pivot + size;
			num--;
		पूर्ण
		num >>= 1;
	पूर्ण

	वापस शून्य;
पूर्ण

बाह्य व्योम *द्वा_खोज(स्थिर व्योम *key, स्थिर व्योम *base, माप_प्रकार num, माप_प्रकार size, cmp_func_t cmp);

#पूर्ण_अगर /* _LINUX_BSEARCH_H */
