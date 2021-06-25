<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bपन.स>
#समावेश <linux/export.h>
#समावेश <xen/xen.h>
#समावेश <xen/page.h>

/* check अगर @page can be merged with 'vec1' */
bool xen_biovec_phys_mergeable(स्थिर काष्ठा bio_vec *vec1,
			       स्थिर काष्ठा page *page)
अणु
#अगर XEN_PAGE_SIZE == PAGE_SIZE
	अचिन्हित दीर्घ bfn1 = pfn_to_bfn(page_to_pfn(vec1->bv_page));
	अचिन्हित दीर्घ bfn2 = pfn_to_bfn(page_to_pfn(page));

	वापस bfn1 + PFN_DOWN(vec1->bv_offset + vec1->bv_len) == bfn2;
#अन्यथा
	/*
	 * XXX: Add support क्रम merging bio_vec when using dअगरferent page
	 * size in Xen and Linux.
	 */
	वापस false;
#पूर्ण_अगर
पूर्ण
