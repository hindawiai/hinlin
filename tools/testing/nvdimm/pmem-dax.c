<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2016, Intel Corporation.
 */
#समावेश "test/nfit_test.h"
#समावेश <linux/blkdev.h>
#समावेश <pस्मृति.स>
#समावेश <nd.h>

दीर्घ __pmem_direct_access(काष्ठा pmem_device *pmem, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	resource_माप_प्रकार offset = PFN_PHYS(pgoff) + pmem->data_offset;

	अगर (unlikely(is_bad_pmem(&pmem->bb, PFN_PHYS(pgoff) / 512,
					PFN_PHYS(nr_pages))))
		वापस -EIO;

	/*
	 * Limit dax to a single page at a समय given vदो_स्मृति()-backed
	 * in the nfit_test हाल.
	 */
	अगर (get_nfit_res(pmem->phys_addr + offset)) अणु
		काष्ठा page *page;

		अगर (kaddr)
			*kaddr = pmem->virt_addr + offset;
		page = vदो_स्मृति_to_page(pmem->virt_addr + offset);
		अगर (pfn)
			*pfn = page_to_pfn_t(page);
		pr_debug_ratelimited("%s: pmem: %p pgoff: %#lx pfn: %#lx\n",
				__func__, pmem, pgoff, page_to_pfn(page));

		वापस 1;
	पूर्ण

	अगर (kaddr)
		*kaddr = pmem->virt_addr + offset;
	अगर (pfn)
		*pfn = phys_to_pfn_t(pmem->phys_addr + offset, pmem->pfn_flags);

	/*
	 * If badblocks are present, limit known good range to the
	 * requested range.
	 */
	अगर (unlikely(pmem->bb.count))
		वापस nr_pages;
	वापस PHYS_PFN(pmem->size - pmem->pfn_pad - offset);
पूर्ण
