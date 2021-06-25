<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple poपूर्णांकer stack
 *
 * (c) 2010 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "pstack.h"
#समावेश "debug.h"
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

काष्ठा pstack अणु
	अचिन्हित लघु	top;
	अचिन्हित लघु	max_nr_entries;
	व्योम		*entries[];
पूर्ण;

काष्ठा pstack *pstack__new(अचिन्हित लघु max_nr_entries)
अणु
	काष्ठा pstack *pstack = zalloc((माप(*pstack) +
				       max_nr_entries * माप(व्योम *)));
	अगर (pstack != शून्य)
		pstack->max_nr_entries = max_nr_entries;
	वापस pstack;
पूर्ण

व्योम pstack__delete(काष्ठा pstack *pstack)
अणु
	मुक्त(pstack);
पूर्ण

bool pstack__empty(स्थिर काष्ठा pstack *pstack)
अणु
	वापस pstack->top == 0;
पूर्ण

व्योम pstack__हटाओ(काष्ठा pstack *pstack, व्योम *key)
अणु
	अचिन्हित लघु i = pstack->top, last_index = pstack->top - 1;

	जबतक (i-- != 0) अणु
		अगर (pstack->entries[i] == key) अणु
			अगर (i < last_index)
				स_हटाओ(pstack->entries + i,
					pstack->entries + i + 1,
					(last_index - i) * माप(व्योम *));
			--pstack->top;
			वापस;
		पूर्ण
	पूर्ण
	pr_err("%s: %p not on the pstack!\n", __func__, key);
पूर्ण

व्योम pstack__push(काष्ठा pstack *pstack, व्योम *key)
अणु
	अगर (pstack->top == pstack->max_nr_entries) अणु
		pr_err("%s: top=%d, overflow!\n", __func__, pstack->top);
		वापस;
	पूर्ण
	pstack->entries[pstack->top++] = key;
पूर्ण

व्योम *pstack__pop(काष्ठा pstack *pstack)
अणु
	व्योम *ret;

	अगर (pstack->top == 0) अणु
		pr_err("%s: underflow!\n", __func__);
		वापस शून्य;
	पूर्ण

	ret = pstack->entries[--pstack->top];
	pstack->entries[pstack->top] = शून्य;
	वापस ret;
पूर्ण

व्योम *pstack__peek(काष्ठा pstack *pstack)
अणु
	अगर (pstack->top == 0)
		वापस शून्य;
	वापस pstack->entries[pstack->top - 1];
पूर्ण
