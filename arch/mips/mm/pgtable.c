<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/pgभाग.स>

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *ret, *init;

	ret = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, PGD_ORDER);
	अगर (ret) अणु
		init = pgd_offset(&init_mm, 0UL);
		pgd_init((अचिन्हित दीर्घ)ret);
		स_नकल(ret + USER_PTRS_PER_PGD, init + USER_PTRS_PER_PGD,
		       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pgd_alloc);
