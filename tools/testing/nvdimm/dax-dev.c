<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Intel Corporation.
 */
#समावेश "test/nfit_test.h"
#समावेश <linux/mm.h>
#समावेश "../../../drivers/dax/dax-private.h"

phys_addr_t dax_pgoff_to_phys(काष्ठा dev_dax *dev_dax, pgoff_t pgoff,
		अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		काष्ठा dev_dax_range *dax_range = &dev_dax->ranges[i];
		काष्ठा range *range = &dax_range->range;
		अचिन्हित दीर्घ दीर्घ pgoff_end;
		phys_addr_t addr;

		pgoff_end = dax_range->pgoff + PHYS_PFN(range_len(range)) - 1;
		अगर (pgoff < dax_range->pgoff || pgoff > pgoff_end)
			जारी;
		addr = PFN_PHYS(pgoff - dax_range->pgoff) + range->start;
		अगर (addr + size - 1 <= range->end) अणु
			अगर (get_nfit_res(addr)) अणु
				काष्ठा page *page;

				अगर (dev_dax->region->align > PAGE_SIZE)
					वापस -1;

				page = vदो_स्मृति_to_page((व्योम *)addr);
				वापस PFN_PHYS(page_to_pfn(page));
			पूर्ण
			वापस addr;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण
