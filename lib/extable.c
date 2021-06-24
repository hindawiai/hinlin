<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Derived from arch/ppc/mm/extable.c and arch/i386/mm/extable.c.
 *
 * Copyright (C) 2004 Paul Mackerras, IBM Corp.
 */

#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sort.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/extable.h>

#अगर_अघोषित ARCH_HAS_RELATIVE_EXTABLE
#घोषणा ex_to_insn(x)	((x)->insn)
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ ex_to_insn(स्थिर काष्ठा exception_table_entry *x)
अणु
	वापस (अचिन्हित दीर्घ)&x->insn + x->insn;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_RELATIVE_EXTABLE
#घोषणा swap_ex		शून्य
#अन्यथा
अटल व्योम swap_ex(व्योम *a, व्योम *b, पूर्णांक size)
अणु
	काष्ठा exception_table_entry *x = a, *y = b, पंचांगp;
	पूर्णांक delta = b - a;

	पंचांगp = *x;
	x->insn = y->insn + delta;
	y->insn = पंचांगp.insn - delta;

#अगर_घोषित swap_ex_entry_fixup
	swap_ex_entry_fixup(x, y, पंचांगp, delta);
#अन्यथा
	x->fixup = y->fixup + delta;
	y->fixup = पंचांगp.fixup - delta;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* ARCH_HAS_RELATIVE_EXTABLE */

/*
 * The exception table needs to be sorted so that the binary
 * search that we use to find entries in it works properly.
 * This is used both क्रम the kernel exception table and क्रम
 * the exception tables of modules that get loaded.
 */
अटल पूर्णांक cmp_ex_sort(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा exception_table_entry *x = a, *y = b;

	/* aव्योम overflow */
	अगर (ex_to_insn(x) > ex_to_insn(y))
		वापस 1;
	अगर (ex_to_insn(x) < ex_to_insn(y))
		वापस -1;
	वापस 0;
पूर्ण

व्योम sort_extable(काष्ठा exception_table_entry *start,
		  काष्ठा exception_table_entry *finish)
अणु
	sort(start, finish - start, माप(काष्ठा exception_table_entry),
	     cmp_ex_sort, swap_ex);
पूर्ण

#अगर_घोषित CONFIG_MODULES
/*
 * If the exception table is sorted, any referring to the module init
 * will be at the beginning or the end.
 */
व्योम trim_init_extable(काष्ठा module *m)
अणु
	/*trim the beginning*/
	जबतक (m->num_exentries &&
	       within_module_init(ex_to_insn(&m->extable[0]), m)) अणु
		m->extable++;
		m->num_exentries--;
	पूर्ण
	/*trim the end*/
	जबतक (m->num_exentries &&
	       within_module_init(ex_to_insn(&m->extable[m->num_exentries - 1]),
				  m))
		m->num_exentries--;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

अटल पूर्णांक cmp_ex_search(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	स्थिर काष्ठा exception_table_entry *_elt = elt;
	अचिन्हित दीर्घ _key = *(अचिन्हित दीर्घ *)key;

	/* aव्योम overflow */
	अगर (_key > ex_to_insn(_elt))
		वापस 1;
	अगर (_key < ex_to_insn(_elt))
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Search one exception table क्रम an entry corresponding to the
 * given inकाष्ठाion address, and वापस the address of the entry,
 * or शून्य अगर none is found.
 * We use a binary search, and thus we assume that the table is
 * alपढ़ोy sorted.
 */
स्थिर काष्ठा exception_table_entry *
search_extable(स्थिर काष्ठा exception_table_entry *base,
	       स्थिर माप_प्रकार num,
	       अचिन्हित दीर्घ value)
अणु
	वापस द्वा_खोज(&value, base, num,
		       माप(काष्ठा exception_table_entry), cmp_ex_search);
पूर्ण
