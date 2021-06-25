<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nvs.c - Routines क्रम saving and restoring ACPI NVS memory region
 *
 * Copyright (C) 2008-2011 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#समावेश "internal.h"

/* ACPI NVS regions, APEI may use it */

काष्ठा nvs_region अणु
	__u64 phys_start;
	__u64 size;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(nvs_region_list);

#अगर_घोषित CONFIG_ACPI_SLEEP
अटल पूर्णांक suspend_nvs_रेजिस्टर(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
#अन्यथा
अटल अंतरभूत पूर्णांक suspend_nvs_रेजिस्टर(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक acpi_nvs_रेजिस्टर(__u64 start, __u64 size)
अणु
	काष्ठा nvs_region *region;

	region = kदो_स्मृति(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;
	region->phys_start = start;
	region->size = size;
	list_add_tail(&region->node, &nvs_region_list);

	वापस suspend_nvs_रेजिस्टर(start, size);
पूर्ण

पूर्णांक acpi_nvs_क्रम_each_region(पूर्णांक (*func)(__u64 start, __u64 size, व्योम *data),
			     व्योम *data)
अणु
	पूर्णांक rc;
	काष्ठा nvs_region *region;

	list_क्रम_each_entry(region, &nvs_region_list, node) अणु
		rc = func(region->phys_start, region->size, data);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_ACPI_SLEEP
/*
 * Platक्रमms, like ACPI, may want us to save some memory used by them during
 * suspend and to restore the contents of this memory during the subsequent
 * resume.  The code below implements a mechanism allowing us to करो that.
 */

काष्ठा nvs_page अणु
	अचिन्हित दीर्घ phys_start;
	अचिन्हित पूर्णांक size;
	व्योम *kaddr;
	व्योम *data;
	bool unmap;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(nvs_list);

/**
 *	suspend_nvs_रेजिस्टर - रेजिस्टर platक्रमm NVS memory region to save
 *	@start - physical address of the region
 *	@size - size of the region
 *
 *	The NVS region need not be page-aligned (both ends) and we arrange
 *	things so that the data from page-aligned addresses in this region will
 *	be copied पूर्णांकo separate RAM pages.
 */
अटल पूर्णांक suspend_nvs_रेजिस्टर(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	काष्ठा nvs_page *entry, *next;

	pr_info("PM: Registering ACPI NVS region [mem %#010lx-%#010lx] (%ld bytes)\n",
		start, start + size - 1, size);

	जबतक (size > 0) अणु
		अचिन्हित पूर्णांक nr_bytes;

		entry = kzalloc(माप(काष्ठा nvs_page), GFP_KERNEL);
		अगर (!entry)
			जाओ Error;

		list_add_tail(&entry->node, &nvs_list);
		entry->phys_start = start;
		nr_bytes = PAGE_SIZE - (start & ~PAGE_MASK);
		entry->size = (size < nr_bytes) ? size : nr_bytes;

		start += entry->size;
		size -= entry->size;
	पूर्ण
	वापस 0;

 Error:
	list_क्रम_each_entry_safe(entry, next, &nvs_list, node) अणु
		list_del(&entry->node);
		kमुक्त(entry);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/**
 *	suspend_nvs_मुक्त - मुक्त data pages allocated क्रम saving NVS regions
 */
व्योम suspend_nvs_मुक्त(व्योम)
अणु
	काष्ठा nvs_page *entry;

	list_क्रम_each_entry(entry, &nvs_list, node)
		अगर (entry->data) अणु
			मुक्त_page((अचिन्हित दीर्घ)entry->data);
			entry->data = शून्य;
			अगर (entry->kaddr) अणु
				अगर (entry->unmap) अणु
					iounmap(entry->kaddr);
					entry->unmap = false;
				पूर्ण अन्यथा अणु
					acpi_os_unmap_iomem(entry->kaddr,
							    entry->size);
				पूर्ण
				entry->kaddr = शून्य;
			पूर्ण
		पूर्ण
पूर्ण

/**
 *	suspend_nvs_alloc - allocate memory necessary क्रम saving NVS regions
 */
पूर्णांक suspend_nvs_alloc(व्योम)
अणु
	काष्ठा nvs_page *entry;

	list_क्रम_each_entry(entry, &nvs_list, node) अणु
		entry->data = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!entry->data) अणु
			suspend_nvs_मुक्त();
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	suspend_nvs_save - save NVS memory regions
 */
पूर्णांक suspend_nvs_save(व्योम)
अणु
	काष्ठा nvs_page *entry;

	prपूर्णांकk(KERN_INFO "PM: Saving platform NVS memory\n");

	list_क्रम_each_entry(entry, &nvs_list, node)
		अगर (entry->data) अणु
			अचिन्हित दीर्घ phys = entry->phys_start;
			अचिन्हित पूर्णांक size = entry->size;

			entry->kaddr = acpi_os_get_iomem(phys, size);
			अगर (!entry->kaddr) अणु
				entry->kaddr = acpi_os_ioremap(phys, size);
				entry->unmap = !!entry->kaddr;
			पूर्ण
			अगर (!entry->kaddr) अणु
				suspend_nvs_मुक्त();
				वापस -ENOMEM;
			पूर्ण
			स_नकल(entry->data, entry->kaddr, entry->size);
		पूर्ण

	वापस 0;
पूर्ण

/**
 *	suspend_nvs_restore - restore NVS memory regions
 *
 *	This function is going to be called with पूर्णांकerrupts disabled, so it
 *	cannot iounmap the भव addresses used to access the NVS region.
 */
व्योम suspend_nvs_restore(व्योम)
अणु
	काष्ठा nvs_page *entry;

	prपूर्णांकk(KERN_INFO "PM: Restoring platform NVS memory\n");

	list_क्रम_each_entry(entry, &nvs_list, node)
		अगर (entry->data)
			स_नकल(entry->kaddr, entry->data, entry->size);
पूर्ण
#पूर्ण_अगर
