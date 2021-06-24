<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/slab.h>

/*
 * Merge two शून्य-terminated poपूर्णांकer arrays पूर्णांकo a newly allocated
 * array, which is also शून्य-terminated. Nomenclature is inspired by
 * स_रखो_p() and memcat() found अन्यथाwhere in the kernel source tree.
 */
व्योम **__memcat_p(व्योम **a, व्योम **b)
अणु
	व्योम **p = a, **new;
	पूर्णांक nr;

	/* count the elements in both arrays */
	क्रम (nr = 0, p = a; *p; nr++, p++)
		;
	क्रम (p = b; *p; nr++, p++)
		;
	/* one क्रम the शून्य-terminator */
	nr++;

	new = kदो_स्मृति_array(nr, माप(व्योम *), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	/* nr -> last index; p poपूर्णांकs to शून्य in b[] */
	क्रम (nr--; nr >= 0; nr--, p = p == b ? &a[nr] : p - 1)
		new[nr] = *p;

	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(__memcat_p);

