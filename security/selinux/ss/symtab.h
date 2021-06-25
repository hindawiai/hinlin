<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * A symbol table (symtab) मुख्यtains associations between symbol
 * strings and datum values.  The type of the datum values
 * is arbitrary.  The symbol table type is implemented
 * using the hash table type (hashtab).
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_SYMTAB_H_
#घोषणा _SS_SYMTAB_H_

#समावेश "hashtab.h"

काष्ठा symtab अणु
	काष्ठा hashtab table;	/* hash table (keyed on a string) */
	u32 nprim;		/* number of primary names in table */
पूर्ण;

पूर्णांक symtab_init(काष्ठा symtab *s, अचिन्हित पूर्णांक size);

पूर्णांक symtab_insert(काष्ठा symtab *s, अक्षर *name, व्योम *datum);
व्योम *symtab_search(काष्ठा symtab *s, स्थिर अक्षर *name);

#पूर्ण_अगर	/* _SS_SYMTAB_H_ */


