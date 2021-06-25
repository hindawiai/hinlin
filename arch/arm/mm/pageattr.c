<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/set_memory.h>

काष्ठा page_change_data अणु
	pgprot_t set_mask;
	pgprot_t clear_mask;
पूर्ण;

अटल पूर्णांक change_page_range(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा page_change_data *cdata = data;
	pte_t pte = *ptep;

	pte = clear_pte_bit(pte, cdata->clear_mask);
	pte = set_pte_bit(pte, cdata->set_mask);

	set_pte_ext(ptep, pte, 0);
	वापस 0;
पूर्ण

अटल bool in_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ range_start, अचिन्हित दीर्घ range_end)
अणु
	वापस start >= range_start && start < range_end &&
		size <= range_end - start;
पूर्ण

अटल पूर्णांक change_memory_common(अचिन्हित दीर्घ addr, पूर्णांक numpages,
				pgprot_t set_mask, pgprot_t clear_mask)
अणु
	अचिन्हित दीर्घ start = addr & PAGE_MASK;
	अचिन्हित दीर्घ end = PAGE_ALIGN(addr) + numpages * PAGE_SIZE;
	अचिन्हित दीर्घ size = end - start;
	पूर्णांक ret;
	काष्ठा page_change_data data;

	WARN_ON_ONCE(start != addr);

	अगर (!size)
		वापस 0;

	अगर (!in_range(start, size, MODULES_VADDR, MODULES_END) &&
	    !in_range(start, size, VMALLOC_START, VMALLOC_END))
		वापस -EINVAL;

	data.set_mask = set_mask;
	data.clear_mask = clear_mask;

	ret = apply_to_page_range(&init_mm, start, size, change_page_range,
					&data);

	flush_tlb_kernel_range(start, end);
	वापस ret;
पूर्ण

पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(L_PTE_RDONLY),
					__pgprot(0));
पूर्ण

पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(0),
					__pgprot(L_PTE_RDONLY));
पूर्ण

पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(L_PTE_XN),
					__pgprot(0));
पूर्ण

पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(0),
					__pgprot(L_PTE_XN));
पूर्ण
