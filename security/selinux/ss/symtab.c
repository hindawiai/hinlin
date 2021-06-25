<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the symbol table type.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश "symtab.h"

अटल अचिन्हित पूर्णांक symhash(स्थिर व्योम *key)
अणु
	स्थिर अक्षर *p, *keyp;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक val;

	val = 0;
	keyp = key;
	size = म_माप(keyp);
	क्रम (p = keyp; (p - keyp) < size; p++)
		val = (val << 4 | (val >> (8*माप(अचिन्हित पूर्णांक)-4))) ^ (*p);
	वापस val;
पूर्ण

अटल पूर्णांक symcmp(स्थिर व्योम *key1, स्थिर व्योम *key2)
अणु
	स्थिर अक्षर *keyp1, *keyp2;

	keyp1 = key1;
	keyp2 = key2;
	वापस म_भेद(keyp1, keyp2);
पूर्ण

अटल स्थिर काष्ठा hashtab_key_params symtab_key_params = अणु
	.hash = symhash,
	.cmp = symcmp,
पूर्ण;

पूर्णांक symtab_init(काष्ठा symtab *s, अचिन्हित पूर्णांक size)
अणु
	s->nprim = 0;
	वापस hashtab_init(&s->table, size);
पूर्ण

पूर्णांक symtab_insert(काष्ठा symtab *s, अक्षर *name, व्योम *datum)
अणु
	वापस hashtab_insert(&s->table, name, datum, symtab_key_params);
पूर्ण

व्योम *symtab_search(काष्ठा symtab *s, स्थिर अक्षर *name)
अणु
	वापस hashtab_search(&s->table, name, symtab_key_params);
पूर्ण
