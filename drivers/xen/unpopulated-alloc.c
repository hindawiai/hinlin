<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memremap.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/page.h>

#समावेश <xen/page.h>
#समावेश <xen/xen.h>

अटल DEFINE_MUTEX(list_lock);
अटल काष्ठा page *page_list;
अटल अचिन्हित पूर्णांक list_count;

अटल पूर्णांक fill_list(अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा dev_pagemap *pgmap;
	काष्ठा resource *res;
	व्योम *vaddr;
	अचिन्हित पूर्णांक i, alloc_pages = round_up(nr_pages, PAGES_PER_SECTION);
	पूर्णांक ret = -ENOMEM;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	res->name = "Xen scratch";
	res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;

	ret = allocate_resource(&iomem_resource, res,
				alloc_pages * PAGE_SIZE, 0, -1,
				PAGES_PER_SECTION * PAGE_SIZE, शून्य, शून्य);
	अगर (ret < 0) अणु
		pr_err("Cannot allocate new IOMEM resource\n");
		जाओ err_resource;
	पूर्ण

	pgmap = kzalloc(माप(*pgmap), GFP_KERNEL);
	अगर (!pgmap) अणु
		ret = -ENOMEM;
		जाओ err_pgmap;
	पूर्ण

	pgmap->type = MEMORY_DEVICE_GENERIC;
	pgmap->range = (काष्ठा range) अणु
		.start = res->start,
		.end = res->end,
	पूर्ण;
	pgmap->nr_range = 1;
	pgmap->owner = res;

#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
        /*
         * memremap will build page tables क्रम the new memory so
         * the p2m must contain invalid entries so the correct
         * non-present PTEs will be written.
         *
         * If a failure occurs, the original (identity) p2m entries
         * are not restored since this region is now known not to
         * conflict with any devices.
         */
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
		xen_pfn_t pfn = PFN_DOWN(res->start);

		क्रम (i = 0; i < alloc_pages; i++) अणु
			अगर (!set_phys_to_machine(pfn + i, INVALID_P2M_ENTRY)) अणु
				pr_warn("set_phys_to_machine() failed, no memory added\n");
				ret = -ENOMEM;
				जाओ err_memremap;
			पूर्ण
                पूर्ण
	पूर्ण
#पूर्ण_अगर

	vaddr = memremap_pages(pgmap, NUMA_NO_NODE);
	अगर (IS_ERR(vaddr)) अणु
		pr_err("Cannot remap memory range\n");
		ret = PTR_ERR(vaddr);
		जाओ err_memremap;
	पूर्ण

	क्रम (i = 0; i < alloc_pages; i++) अणु
		काष्ठा page *pg = virt_to_page(vaddr + PAGE_SIZE * i);

		BUG_ON(!virt_addr_valid(vaddr + PAGE_SIZE * i));
		pg->zone_device_data = page_list;
		page_list = pg;
		list_count++;
	पूर्ण

	वापस 0;

err_memremap:
	kमुक्त(pgmap);
err_pgmap:
	release_resource(res);
err_resource:
	kमुक्त(res);
	वापस ret;
पूर्ण

/**
 * xen_alloc_unpopulated_pages - alloc unpopulated pages
 * @nr_pages: Number of pages
 * @pages: pages वापसed
 * @वापस 0 on success, error otherwise
 */
पूर्णांक xen_alloc_unpopulated_pages(अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock(&list_lock);
	अगर (list_count < nr_pages) अणु
		ret = fill_list(nr_pages - list_count);
		अगर (ret)
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *pg = page_list;

		BUG_ON(!pg);
		page_list = pg->zone_device_data;
		list_count--;
		pages[i] = pg;

#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
		अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
			ret = xen_alloc_p2m_entry(page_to_pfn(pg));
			अगर (ret < 0) अणु
				अचिन्हित पूर्णांक j;

				क्रम (j = 0; j <= i; j++) अणु
					pages[j]->zone_device_data = page_list;
					page_list = pages[j];
					list_count++;
				पूर्ण
				जाओ out;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

out:
	mutex_unlock(&list_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(xen_alloc_unpopulated_pages);

/**
 * xen_मुक्त_unpopulated_pages - वापस unpopulated pages
 * @nr_pages: Number of pages
 * @pages: pages to वापस
 */
व्योम xen_मुक्त_unpopulated_pages(अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&list_lock);
	क्रम (i = 0; i < nr_pages; i++) अणु
		pages[i]->zone_device_data = page_list;
		page_list = pages[i];
		list_count++;
	पूर्ण
	mutex_unlock(&list_lock);
पूर्ण
EXPORT_SYMBOL(xen_मुक्त_unpopulated_pages);

#अगर_घोषित CONFIG_XEN_PV
अटल पूर्णांक __init init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_pv_करोमुख्य())
		वापस 0;

	/*
	 * Initialize with pages from the extra memory regions (see
	 * arch/x86/xen/setup.c).
	 */
	क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) अणु
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < xen_extra_mem[i].n_pfns; j++) अणु
			काष्ठा page *pg =
				pfn_to_page(xen_extra_mem[i].start_pfn + j);

			pg->zone_device_data = page_list;
			page_list = pg;
			list_count++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(init);
#पूर्ण_अगर
