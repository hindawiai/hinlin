<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mokvar-table.c
 *
 * Copyright (c) 2020 Red Hat
 * Author: Lenny Szubowicz <lszubowi@redhat.com>
 *
 * This module contains the kernel support क्रम the Linux EFI Machine
 * Owner Key (MOK) variable configuration table, which is identअगरied by
 * the LINUX_EFI_MOK_VARIABLE_TABLE_GUID.
 *
 * This EFI configuration table provides a more robust alternative to
 * EFI अस्थिर variables by which an EFI boot loader can pass the
 * contents of the Machine Owner Key (MOK) certअगरicate stores to the
 * kernel during boot. If both the EFI MOK config table and corresponding
 * EFI MOK variables are present, the table should be considered as
 * more authoritative.
 *
 * This module includes code that validates and maps the EFI MOK table,
 * अगर it's presence was detected very early in boot.
 *
 * Kernel पूर्णांकerface routines are provided to walk through all the
 * entries in the MOK config table or to search क्रम a specअगरic named
 * entry.
 *
 * The contents of the inभागidual named MOK config table entries are
 * made available to user space via पढ़ो-only sysfs binary files under:
 *
 * /sys/firmware/efi/mok-variables/
 *
 */
#घोषणा pr_fmt(fmt) "mokvar: " fmt

#समावेश <linux/capability.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/early_ioremap.h>

/*
 * The LINUX_EFI_MOK_VARIABLE_TABLE_GUID config table is a packed
 * sequence of काष्ठा efi_mokvar_table_entry, one क्रम each named
 * MOK variable. The sequence is terminated by an entry with a
 * completely शून्य name and 0 data size.
 *
 * efi_mokvar_table_size is set to the computed size of the
 * MOK config table by efi_mokvar_table_init(). This will be
 * non-zero अगर and only अगर the table अगर present and has been
 * validated by efi_mokvar_table_init().
 */
अटल माप_प्रकार efi_mokvar_table_size;

/*
 * efi_mokvar_table_va is the kernel भव address at which the
 * EFI MOK config table has been mapped by efi_mokvar_sysfs_init().
 */
अटल काष्ठा efi_mokvar_table_entry *efi_mokvar_table_va;

/*
 * Each /sys/firmware/efi/mok-variables/ sysfs file is represented by
 * an instance of काष्ठा efi_mokvar_sysfs_attr on efi_mokvar_sysfs_list.
 * bin_attr.निजी poपूर्णांकs to the associated EFI MOK config table entry.
 *
 * This list is created during boot and then reमुख्यs unchanged.
 * So no synchronization is currently required to walk the list.
 */
काष्ठा efi_mokvar_sysfs_attr अणु
	काष्ठा bin_attribute bin_attr;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(efi_mokvar_sysfs_list);
अटल काष्ठा kobject *mokvar_kobj;

/*
 * efi_mokvar_table_init() - Early boot validation of EFI MOK config table
 *
 * If present, validate and compute the size of the EFI MOK variable
 * configuration table. This table may be provided by an EFI boot loader
 * as an alternative to ordinary EFI variables, due to platक्रमm-dependent
 * limitations. The memory occupied by this table is marked as reserved.
 *
 * This routine must be called beक्रमe efi_मुक्त_boot_services() in order
 * to guarantee that it can mark the table as reserved.
 *
 * Implicit inमाला_दो:
 * efi.mokvar_table:	Physical address of EFI MOK variable config table
 *			or special value that indicates no such table.
 *
 * Implicit outमाला_दो:
 * efi_mokvar_table_size: Computed size of EFI MOK variable config table.
 *			The table is considered present and valid अगर this
 *			is non-zero.
 */
व्योम __init efi_mokvar_table_init(व्योम)
अणु
	efi_memory_desc_t md;
	व्योम *va = शून्य;
	अचिन्हित दीर्घ cur_offset = 0;
	अचिन्हित दीर्घ offset_limit;
	अचिन्हित दीर्घ map_size = 0;
	अचिन्हित दीर्घ map_size_needed = 0;
	अचिन्हित दीर्घ size;
	काष्ठा efi_mokvar_table_entry *mokvar_entry;
	पूर्णांक err;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	अगर (efi.mokvar_table == EFI_INVALID_TABLE_ADDR)
		वापस;
	/*
	 * The EFI MOK config table must fit within a single EFI memory
	 * descriptor range.
	 */
	err = efi_mem_desc_lookup(efi.mokvar_table, &md);
	अगर (err) अणु
		pr_warn("EFI MOKvar config table is not within the EFI memory map\n");
		वापस;
	पूर्ण

	offset_limit = efi_mem_desc_end(&md) - efi.mokvar_table;

	/*
	 * Validate the MOK config table. Since there is no table header
	 * from which we could get the total size of the MOK config table,
	 * we compute the total size as we validate each variably sized
	 * entry, remapping as necessary.
	 */
	err = -EINVAL;
	जबतक (cur_offset + माप(*mokvar_entry) <= offset_limit) अणु
		mokvar_entry = va + cur_offset;
		map_size_needed = cur_offset + माप(*mokvar_entry);
		अगर (map_size_needed > map_size) अणु
			अगर (va)
				early_memunmap(va, map_size);
			/*
			 * Map a little more than the fixed size entry
			 * header, anticipating some data. It's safe to
			 * करो so as दीर्घ as we stay within current memory
			 * descriptor.
			 */
			map_size = min(map_size_needed + 2*EFI_PAGE_SIZE,
				       offset_limit);
			va = early_memremap(efi.mokvar_table, map_size);
			अगर (!va) अणु
				pr_err("Failed to map EFI MOKvar config table pa=0x%lx, size=%lu.\n",
				       efi.mokvar_table, map_size);
				वापस;
			पूर्ण
			mokvar_entry = va + cur_offset;
		पूर्ण

		/* Check क्रम last sentinel entry */
		अगर (mokvar_entry->name[0] == '\0') अणु
			अगर (mokvar_entry->data_size != 0)
				अवरोध;
			err = 0;
			अवरोध;
		पूर्ण

		/* Sanity check that the name is null terminated */
		size = strnlen(mokvar_entry->name,
			       माप(mokvar_entry->name));
		अगर (size >= माप(mokvar_entry->name))
			अवरोध;

		/* Advance to the next entry */
		cur_offset = map_size_needed + mokvar_entry->data_size;
	पूर्ण

	अगर (va)
		early_memunmap(va, map_size);
	अगर (err) अणु
		pr_err("EFI MOKvar config table is not valid\n");
		वापस;
	पूर्ण
	efi_mem_reserve(efi.mokvar_table, map_size_needed);
	efi_mokvar_table_size = map_size_needed;
पूर्ण

/*
 * efi_mokvar_entry_next() - Get next entry in the EFI MOK config table
 *
 * mokvar_entry:	Poपूर्णांकer to current EFI MOK config table entry
 *			or null. Null indicates get first entry.
 *			Passed by reference. This is updated to the
 *			same value as the वापस value.
 *
 * Returns:		Poपूर्णांकer to next EFI MOK config table entry
 *			or null, अगर there are no more entries.
 *			Same value is वापसed in the mokvar_entry
 *			parameter.
 *
 * This routine depends on the EFI MOK config table being entirely
 * mapped with it's starting भव address in efi_mokvar_table_va.
 */
काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_next(
			काष्ठा efi_mokvar_table_entry **mokvar_entry)
अणु
	काष्ठा efi_mokvar_table_entry *mokvar_cur;
	काष्ठा efi_mokvar_table_entry *mokvar_next;
	माप_प्रकार size_cur;

	mokvar_cur = *mokvar_entry;
	*mokvar_entry = शून्य;

	अगर (efi_mokvar_table_va == शून्य)
		वापस शून्य;

	अगर (mokvar_cur == शून्य) अणु
		mokvar_next = efi_mokvar_table_va;
	पूर्ण अन्यथा अणु
		अगर (mokvar_cur->name[0] == '\0')
			वापस शून्य;
		size_cur = माप(*mokvar_cur) + mokvar_cur->data_size;
		mokvar_next = (व्योम *)mokvar_cur + size_cur;
	पूर्ण

	अगर (mokvar_next->name[0] == '\0')
		वापस शून्य;

	*mokvar_entry = mokvar_next;
	वापस mokvar_next;
पूर्ण

/*
 * efi_mokvar_entry_find() - Find EFI MOK config entry by name
 *
 * name:	Name of the entry to look क्रम.
 *
 * Returns:	Poपूर्णांकer to EFI MOK config table entry अगर found;
 *		null otherwise.
 *
 * This routine depends on the EFI MOK config table being entirely
 * mapped with it's starting भव address in efi_mokvar_table_va.
 */
काष्ठा efi_mokvar_table_entry *efi_mokvar_entry_find(स्थिर अक्षर *name)
अणु
	काष्ठा efi_mokvar_table_entry *mokvar_entry = शून्य;

	जबतक (efi_mokvar_entry_next(&mokvar_entry)) अणु
		अगर (!म_भेदन(name, mokvar_entry->name,
			     माप(mokvar_entry->name)))
			वापस mokvar_entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * efi_mokvar_sysfs_पढ़ो() - sysfs binary file पढ़ो routine
 *
 * Returns:	Count of bytes पढ़ो.
 *
 * Copy EFI MOK config table entry data क्रम this mokvar sysfs binary file
 * to the supplied buffer, starting at the specअगरied offset पूर्णांकo mokvar table
 * entry data, क्रम the specअगरied count bytes. The copy is limited by the
 * amount of data in this mokvar config table entry.
 */
अटल sमाप_प्रकार efi_mokvar_sysfs_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				 loff_t off, माप_प्रकार count)
अणु
	काष्ठा efi_mokvar_table_entry *mokvar_entry = bin_attr->निजी;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस 0;

	अगर (off >= mokvar_entry->data_size)
		वापस 0;
	अगर (count >  mokvar_entry->data_size - off)
		count = mokvar_entry->data_size - off;

	स_नकल(buf, mokvar_entry->data + off, count);
	वापस count;
पूर्ण

/*
 * efi_mokvar_sysfs_init() - Map EFI MOK config table and create sysfs
 *
 * Map the EFI MOK variable config table क्रम run-समय use by the kernel
 * and create the sysfs entries in /sys/firmware/efi/mok-variables/
 *
 * This routine just वापसs अगर a valid EFI MOK variable config table
 * was not found earlier during boot.
 *
 * This routine must be called during a "middle" initcall phase, i.e.
 * after efi_mokvar_table_init() but beक्रमe UEFI certs are loaded
 * during late init.
 *
 * Implicit inमाला_दो:
 * efi.mokvar_table:	Physical address of EFI MOK variable config table
 *			or special value that indicates no such table.
 *
 * efi_mokvar_table_size: Computed size of EFI MOK variable config table.
 *			The table is considered present and valid अगर this
 *			is non-zero.
 *
 * Implicit outमाला_दो:
 * efi_mokvar_table_va:	Start भव address of the EFI MOK config table.
 */
अटल पूर्णांक __init efi_mokvar_sysfs_init(व्योम)
अणु
	व्योम *config_va;
	काष्ठा efi_mokvar_table_entry *mokvar_entry = शून्य;
	काष्ठा efi_mokvar_sysfs_attr *mokvar_sysfs = शून्य;
	पूर्णांक err = 0;

	अगर (efi_mokvar_table_size == 0)
		वापस -ENOENT;

	config_va = memremap(efi.mokvar_table, efi_mokvar_table_size,
			     MEMREMAP_WB);
	अगर (!config_va) अणु
		pr_err("Failed to map EFI MOKvar config table\n");
		वापस -ENOMEM;
	पूर्ण
	efi_mokvar_table_va = config_va;

	mokvar_kobj = kobject_create_and_add("mok-variables", efi_kobj);
	अगर (!mokvar_kobj) अणु
		pr_err("Failed to create EFI mok-variables sysfs entry\n");
		वापस -ENOMEM;
	पूर्ण

	जबतक (efi_mokvar_entry_next(&mokvar_entry)) अणु
		mokvar_sysfs = kzalloc(माप(*mokvar_sysfs), GFP_KERNEL);
		अगर (!mokvar_sysfs) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		sysfs_bin_attr_init(&mokvar_sysfs->bin_attr);
		mokvar_sysfs->bin_attr.निजी = mokvar_entry;
		mokvar_sysfs->bin_attr.attr.name = mokvar_entry->name;
		mokvar_sysfs->bin_attr.attr.mode = 0400;
		mokvar_sysfs->bin_attr.size = mokvar_entry->data_size;
		mokvar_sysfs->bin_attr.पढ़ो = efi_mokvar_sysfs_पढ़ो;

		err = sysfs_create_bin_file(mokvar_kobj,
					   &mokvar_sysfs->bin_attr);
		अगर (err)
			अवरोध;

		list_add_tail(&mokvar_sysfs->node, &efi_mokvar_sysfs_list);
	पूर्ण

	अगर (err) अणु
		pr_err("Failed to create some EFI mok-variables sysfs entries\n");
		kमुक्त(mokvar_sysfs);
	पूर्ण
	वापस err;
पूर्ण
device_initcall(efi_mokvar_sysfs_init);
