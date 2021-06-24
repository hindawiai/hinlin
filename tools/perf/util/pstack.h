<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_PSTACK_
#घोषणा _PERF_PSTACK_

#समावेश <stdbool.h>

काष्ठा pstack;
काष्ठा pstack *pstack__new(अचिन्हित लघु max_nr_entries);
व्योम pstack__delete(काष्ठा pstack *pstack);
bool pstack__empty(स्थिर काष्ठा pstack *pstack);
व्योम pstack__हटाओ(काष्ठा pstack *pstack, व्योम *key);
व्योम pstack__push(काष्ठा pstack *pstack, व्योम *key);
व्योम *pstack__pop(काष्ठा pstack *pstack);
व्योम *pstack__peek(काष्ठा pstack *pstack);

#पूर्ण_अगर /* _PERF_PSTACK_ */
