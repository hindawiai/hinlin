<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fake_mem.c
 *
 * Copyright (C) 2015 FUJITSU LIMITED
 * Author: Taku Izumi <izumi.taku@jp.fujitsu.com>
 *
 * This code पूर्णांकroduces new boot option named "efi_fake_mem"
 * By specअगरying this parameter, you can add arbitrary attribute to
 * specअगरic memory range by updating original (firmware provided) EFI
 * memmap.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/types.h>
#समावेश <linux/sort.h>
#समावेश "fake_mem.h"

काष्ठा efi_mem_range efi_fake_mems[EFI_MAX_FAKEMEM];
पूर्णांक nr_fake_mem;

अटल पूर्णांक __init cmp_fake_mem(स्थिर व्योम *x1, स्थिर व्योम *x2)
अणु
	स्थिर काष्ठा efi_mem_range *m1 = x1;
	स्थिर काष्ठा efi_mem_range *m2 = x2;

	अगर (m1->range.start < m2->range.start)
		वापस -1;
	अगर (m1->range.start > m2->range.start)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम __init efi_fake_range(काष्ठा efi_mem_range *efi_range)
अणु
	काष्ठा efi_memory_map_data data = अणु 0 पूर्ण;
	पूर्णांक new_nr_map = efi.memmap.nr_map;
	efi_memory_desc_t *md;
	व्योम *new_memmap;

	/* count up the number of EFI memory descriptor */
	क्रम_each_efi_memory_desc(md)
		new_nr_map += efi_memmap_split_count(md, &efi_range->range);

	/* allocate memory क्रम new EFI memmap */
	अगर (efi_memmap_alloc(new_nr_map, &data) != 0)
		वापस;

	/* create new EFI memmap */
	new_memmap = early_memremap(data.phys_map, data.size);
	अगर (!new_memmap) अणु
		__efi_memmap_मुक्त(data.phys_map, data.size, data.flags);
		वापस;
	पूर्ण

	efi_memmap_insert(&efi.memmap, new_memmap, efi_range);

	/* swap पूर्णांकo new EFI memmap */
	early_memunmap(new_memmap, data.size);

	efi_memmap_install(&data);
पूर्ण

व्योम __init efi_fake_memmap(व्योम)
अणु
	पूर्णांक i;

	अगर (!efi_enabled(EFI_MEMMAP) || !nr_fake_mem)
		वापस;

	क्रम (i = 0; i < nr_fake_mem; i++)
		efi_fake_range(&efi_fake_mems[i]);

	/* prपूर्णांक new EFI memmap */
	efi_prपूर्णांक_memmap();
पूर्ण

अटल पूर्णांक __init setup_fake_mem(अक्षर *p)
अणु
	u64 start = 0, mem_size = 0, attribute = 0;
	पूर्णांक i;

	अगर (!p)
		वापस -EINVAL;

	जबतक (*p != '\0') अणु
		mem_size = memparse(p, &p);
		अगर (*p == '@')
			start = memparse(p+1, &p);
		अन्यथा
			अवरोध;

		अगर (*p == ':')
			attribute = simple_म_से_अदीर्घl(p+1, &p, 0);
		अन्यथा
			अवरोध;

		अगर (nr_fake_mem >= EFI_MAX_FAKEMEM)
			अवरोध;

		efi_fake_mems[nr_fake_mem].range.start = start;
		efi_fake_mems[nr_fake_mem].range.end = start + mem_size - 1;
		efi_fake_mems[nr_fake_mem].attribute = attribute;
		nr_fake_mem++;

		अगर (*p == ',')
			p++;
	पूर्ण

	sort(efi_fake_mems, nr_fake_mem, माप(काष्ठा efi_mem_range),
	     cmp_fake_mem, शून्य);

	क्रम (i = 0; i < nr_fake_mem; i++)
		pr_info("efi_fake_mem: add attr=0x%016llx to [mem 0x%016llx-0x%016llx]",
			efi_fake_mems[i].attribute, efi_fake_mems[i].range.start,
			efi_fake_mems[i].range.end);

	वापस *p == '\0' ? 0 : -EINVAL;
पूर्ण

early_param("efi_fake_mem", setup_fake_mem);
