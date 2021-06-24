<शैली गुरु>
/*
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/cpuinfo.h>

/* pteaddr:
 *   ptbase | vpn* | zero
 *   31-22  | 21-2 | 1-0
 *
 *   *vpn is preserved on द्विगुन fault
 *
 * tlbacc:
 *   IG   |*flags| pfn
 *   31-25|24-20 | 19-0
 *
 *   *crwxg
 *
 * tlbmisc:
 *   resv  |way   |rd | we|pid |dbl|bad|perm|d
 *   31-24 |23-20 |19 | 20|17-4|3  |2  |1   |0
 *
 */

/*
 * Initialize a new pgd / pmd table with invalid poपूर्णांकers.
 */
अटल व्योम pgd_init(pgd_t *pgd)
अणु
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *) pgd;
	पूर्णांक i;

	क्रम (i = 0; i < USER_PTRS_PER_PGD; i += 8) अणु
		p[i + 0] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 1] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 2] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 3] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 4] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 5] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 6] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 7] = (अचिन्हित दीर्घ) invalid_pte_table;
	पूर्ण
पूर्ण

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *ret, *init;

	ret = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, PGD_ORDER);
	अगर (ret) अणु
		init = pgd_offset(&init_mm, 0UL);
		pgd_init(ret);
		स_नकल(ret + USER_PTRS_PER_PGD, init + USER_PTRS_PER_PGD,
		       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
	पूर्ण

	वापस ret;
पूर्ण

व्योम __init pagetable_init(व्योम)
अणु
	/* Initialize the entire pgd.  */
	pgd_init(swapper_pg_dir);
	pgd_init(swapper_pg_dir + USER_PTRS_PER_PGD);
पूर्ण
