<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Manage a cache of file names' existence */
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <linux/list.h>
#समावेश "fncache.h"

काष्ठा fncache अणु
	काष्ठा hlist_node nd;
	bool res;
	अक्षर name[];
पूर्ण;

#घोषणा FNHSIZE 61

अटल काष्ठा hlist_head fncache_hash[FNHSIZE];

अचिन्हित shash(स्थिर अचिन्हित अक्षर *s)
अणु
	अचिन्हित h = 0;
	जबतक (*s)
		h = 65599 * h + *s++;
	वापस h ^ (h >> 16);
पूर्ण

अटल bool lookup_fncache(स्थिर अक्षर *name, bool *res)
अणु
	पूर्णांक h = shash((स्थिर अचिन्हित अक्षर *)name) % FNHSIZE;
	काष्ठा fncache *n;

	hlist_क्रम_each_entry(n, &fncache_hash[h], nd) अणु
		अगर (!म_भेद(n->name, name)) अणु
			*res = n->res;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम update_fncache(स्थिर अक्षर *name, bool res)
अणु
	काष्ठा fncache *n = दो_स्मृति(माप(काष्ठा fncache) + म_माप(name) + 1);
	पूर्णांक h = shash((स्थिर अचिन्हित अक्षर *)name) % FNHSIZE;

	अगर (!n)
		वापस;
	म_नकल(n->name, name);
	n->res = res;
	hlist_add_head(&n->nd, &fncache_hash[h]);
पूर्ण

/* No LRU, only use when bounded in some other way. */
bool file_available(स्थिर अक्षर *name)
अणु
	bool res;

	अगर (lookup_fncache(name, &res))
		वापस res;
	res = access(name, R_OK) == 0;
	update_fncache(name, res);
	वापस res;
पूर्ण
