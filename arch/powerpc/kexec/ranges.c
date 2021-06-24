<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * घातerpc code to implement the kexec_file_load syscall
 *
 * Copyright (C) 2004  Adam Litke (agl@us.ibm.com)
 * Copyright (C) 2004  IBM Corp.
 * Copyright (C) 2004,2005  Milton D Miller II, IBM Corporation
 * Copyright (C) 2005  R Sharada (sharada@in.ibm.com)
 * Copyright (C) 2006  Mohan Kumar M (mohan@in.ibm.com)
 * Copyright (C) 2020  IBM Corporation
 *
 * Based on kexec-tools' kexec-ppc64.c, fs2dt.c.
 * Heavily modअगरied क्रम the kernel by
 * Hari Bathini, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "kexec ranges: " fmt

#समावेश <linux/sort.h>
#समावेश <linux/kexec.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/kexec_ranges.h>

/**
 * get_max_nr_ranges - Get the max no. of ranges crash_mem काष्ठाure
 *                     could hold, given the size allocated क्रम it.
 * @size:              Allocation size of crash_mem काष्ठाure.
 *
 * Returns the maximum no. of ranges.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_max_nr_ranges(माप_प्रकार size)
अणु
	वापस ((size - माप(काष्ठा crash_mem)) /
		माप(काष्ठा crash_mem_range));
पूर्ण

/**
 * get_mem_rngs_size - Get the allocated size of mem_rngs based on
 *                     max_nr_ranges and chunk size.
 * @mem_rngs:          Memory ranges.
 *
 * Returns the maximum size of @mem_rngs.
 */
अटल अंतरभूत माप_प्रकार get_mem_rngs_size(काष्ठा crash_mem *mem_rngs)
अणु
	माप_प्रकार size;

	अगर (!mem_rngs)
		वापस 0;

	size = (माप(काष्ठा crash_mem) +
		(mem_rngs->max_nr_ranges * माप(काष्ठा crash_mem_range)));

	/*
	 * Memory is allocated in size multiple of MEM_RANGE_CHUNK_SZ.
	 * So, align to get the actual length.
	 */
	वापस ALIGN(size, MEM_RANGE_CHUNK_SZ);
पूर्ण

/**
 * __add_mem_range - add a memory range to memory ranges list.
 * @mem_ranges:      Range list to add the memory range to.
 * @base:            Base address of the range to add.
 * @size:            Size of the memory range to add.
 *
 * (Re)allocates memory, अगर needed.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक __add_mem_range(काष्ठा crash_mem **mem_ranges, u64 base, u64 size)
अणु
	काष्ठा crash_mem *mem_rngs = *mem_ranges;

	अगर (!mem_rngs || (mem_rngs->nr_ranges == mem_rngs->max_nr_ranges)) अणु
		mem_rngs = पुनः_स्मृति_mem_ranges(mem_ranges);
		अगर (!mem_rngs)
			वापस -ENOMEM;
	पूर्ण

	mem_rngs->ranges[mem_rngs->nr_ranges].start = base;
	mem_rngs->ranges[mem_rngs->nr_ranges].end = base + size - 1;
	pr_debug("Added memory range [%#016llx - %#016llx] at index %d\n",
		 base, base + size - 1, mem_rngs->nr_ranges);
	mem_rngs->nr_ranges++;
	वापस 0;
पूर्ण

/**
 * __merge_memory_ranges - Merges the given memory ranges list.
 * @mem_rngs:              Range list to merge.
 *
 * Assumes a sorted range list.
 *
 * Returns nothing.
 */
अटल व्योम __merge_memory_ranges(काष्ठा crash_mem *mem_rngs)
अणु
	काष्ठा crash_mem_range *ranges;
	पूर्णांक i, idx;

	अगर (!mem_rngs)
		वापस;

	idx = 0;
	ranges = &(mem_rngs->ranges[0]);
	क्रम (i = 1; i < mem_rngs->nr_ranges; i++) अणु
		अगर (ranges[i].start <= (ranges[i-1].end + 1))
			ranges[idx].end = ranges[i].end;
		अन्यथा अणु
			idx++;
			अगर (i == idx)
				जारी;

			ranges[idx] = ranges[i];
		पूर्ण
	पूर्ण
	mem_rngs->nr_ranges = idx + 1;
पूर्ण

/* cmp_func_t callback to sort ranges with sort() */
अटल पूर्णांक rngcmp(स्थिर व्योम *_x, स्थिर व्योम *_y)
अणु
	स्थिर काष्ठा crash_mem_range *x = _x, *y = _y;

	अगर (x->start > y->start)
		वापस 1;
	अगर (x->start < y->start)
		वापस -1;
	वापस 0;
पूर्ण

/**
 * sort_memory_ranges - Sorts the given memory ranges list.
 * @mem_rngs:           Range list to sort.
 * @merge:              If true, merge the list after sorting.
 *
 * Returns nothing.
 */
व्योम sort_memory_ranges(काष्ठा crash_mem *mem_rngs, bool merge)
अणु
	पूर्णांक i;

	अगर (!mem_rngs)
		वापस;

	/* Sort the ranges in-place */
	sort(&(mem_rngs->ranges[0]), mem_rngs->nr_ranges,
	     माप(mem_rngs->ranges[0]), rngcmp, शून्य);

	अगर (merge)
		__merge_memory_ranges(mem_rngs);

	/* For debugging purpose */
	pr_debug("Memory ranges:\n");
	क्रम (i = 0; i < mem_rngs->nr_ranges; i++) अणु
		pr_debug("\t[%03d][%#016llx - %#016llx]\n", i,
			 mem_rngs->ranges[i].start,
			 mem_rngs->ranges[i].end);
	पूर्ण
पूर्ण

/**
 * पुनः_स्मृति_mem_ranges - पुनः_स्मृतिate mem_ranges with size incremented
 *                      by MEM_RANGE_CHUNK_SZ. Frees up the old memory,
 *                      अगर memory allocation fails.
 * @mem_ranges:         Memory ranges to पुनः_स्मृतिate.
 *
 * Returns poपूर्णांकer to पुनः_स्मृतिated memory on success, शून्य otherwise.
 */
काष्ठा crash_mem *पुनः_स्मृति_mem_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	काष्ठा crash_mem *mem_rngs = *mem_ranges;
	अचिन्हित पूर्णांक nr_ranges;
	माप_प्रकार size;

	size = get_mem_rngs_size(mem_rngs);
	nr_ranges = mem_rngs ? mem_rngs->nr_ranges : 0;

	size += MEM_RANGE_CHUNK_SZ;
	mem_rngs = kपुनः_स्मृति(*mem_ranges, size, GFP_KERNEL);
	अगर (!mem_rngs) अणु
		kमुक्त(*mem_ranges);
		*mem_ranges = शून्य;
		वापस शून्य;
	पूर्ण

	mem_rngs->nr_ranges = nr_ranges;
	mem_rngs->max_nr_ranges = get_max_nr_ranges(size);
	*mem_ranges = mem_rngs;

	वापस mem_rngs;
पूर्ण

/**
 * add_mem_range - Updates existing memory range, अगर there is an overlap.
 *                 Else, adds a new memory range.
 * @mem_ranges:    Range list to add the memory range to.
 * @base:          Base address of the range to add.
 * @size:          Size of the memory range to add.
 *
 * (Re)allocates memory, अगर needed.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_mem_range(काष्ठा crash_mem **mem_ranges, u64 base, u64 size)
अणु
	काष्ठा crash_mem *mem_rngs = *mem_ranges;
	u64 mstart, mend, end;
	अचिन्हित पूर्णांक i;

	अगर (!size)
		वापस 0;

	end = base + size - 1;

	अगर (!mem_rngs || !(mem_rngs->nr_ranges))
		वापस __add_mem_range(mem_ranges, base, size);

	क्रम (i = 0; i < mem_rngs->nr_ranges; i++) अणु
		mstart = mem_rngs->ranges[i].start;
		mend = mem_rngs->ranges[i].end;
		अगर (base < mend && end > mstart) अणु
			अगर (base < mstart)
				mem_rngs->ranges[i].start = base;
			अगर (end > mend)
				mem_rngs->ranges[i].end = end;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस __add_mem_range(mem_ranges, base, size);
पूर्ण

/**
 * add_tce_mem_ranges - Adds tce-table range to the given memory ranges list.
 * @mem_ranges:         Range list to add the memory range(s) to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_tce_mem_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	काष्ठा device_node *dn = शून्य;
	पूर्णांक ret = 0;

	क्रम_each_node_by_type(dn, "pci") अणु
		u64 base;
		u32 size;

		ret = of_property_पढ़ो_u64(dn, "linux,tce-base", &base);
		ret |= of_property_पढ़ो_u32(dn, "linux,tce-size", &size);
		अगर (ret) अणु
			/*
			 * It is ok to have pci nodes without tce. So, ignore
			 * property करोes not exist error.
			 */
			अगर (ret == -EINVAL) अणु
				ret = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		ret = add_mem_range(mem_ranges, base, size);
		अगर (ret)
			अवरोध;
	पूर्ण

	of_node_put(dn);
	वापस ret;
पूर्ण

/**
 * add_initrd_mem_range - Adds initrd range to the given memory ranges list,
 *                        अगर the initrd was retained.
 * @mem_ranges:           Range list to add the memory range to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_initrd_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	u64 base, end;
	पूर्णांक ret;

	/* This range means something, only अगर initrd was retained */
	अगर (!म_माला(saved_command_line, "retain_initrd"))
		वापस 0;

	ret = of_property_पढ़ो_u64(of_chosen, "linux,initrd-start", &base);
	ret |= of_property_पढ़ो_u64(of_chosen, "linux,initrd-end", &end);
	अगर (!ret)
		ret = add_mem_range(mem_ranges, base, end - base + 1);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/**
 * add_htab_mem_range - Adds htab range to the given memory ranges list,
 *                      अगर it exists
 * @mem_ranges:         Range list to add the memory range to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_htab_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	अगर (!htab_address)
		वापस 0;

	वापस add_mem_range(mem_ranges, __pa(htab_address), htab_size_bytes);
पूर्ण
#पूर्ण_अगर

/**
 * add_kernel_mem_range - Adds kernel text region to the given
 *                        memory ranges list.
 * @mem_ranges:           Range list to add the memory range to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_kernel_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	वापस add_mem_range(mem_ranges, 0, __pa(_end));
पूर्ण

/**
 * add_rtas_mem_range - Adds RTAS region to the given memory ranges list.
 * @mem_ranges:         Range list to add the memory range to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_rtas_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	काष्ठा device_node *dn;
	u32 base, size;
	पूर्णांक ret = 0;

	dn = of_find_node_by_path("/rtas");
	अगर (!dn)
		वापस 0;

	ret = of_property_पढ़ो_u32(dn, "linux,rtas-base", &base);
	ret |= of_property_पढ़ो_u32(dn, "rtas-size", &size);
	अगर (!ret)
		ret = add_mem_range(mem_ranges, base, size);

	of_node_put(dn);
	वापस ret;
पूर्ण

/**
 * add_opal_mem_range - Adds OPAL region to the given memory ranges list.
 * @mem_ranges:         Range list to add the memory range to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_opal_mem_range(काष्ठा crash_mem **mem_ranges)
अणु
	काष्ठा device_node *dn;
	u64 base, size;
	पूर्णांक ret;

	dn = of_find_node_by_path("/ibm,opal");
	अगर (!dn)
		वापस 0;

	ret = of_property_पढ़ो_u64(dn, "opal-base-address", &base);
	ret |= of_property_पढ़ो_u64(dn, "opal-runtime-size", &size);
	अगर (!ret)
		ret = add_mem_range(mem_ranges, base, size);

	of_node_put(dn);
	वापस ret;
पूर्ण

/**
 * add_reserved_mem_ranges - Adds "/reserved-ranges" regions exported by f/w
 *                           to the given memory ranges list.
 * @mem_ranges:              Range list to add the memory ranges to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक add_reserved_mem_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	पूर्णांक n_mem_addr_cells, n_mem_size_cells, i, len, cells, ret = 0;
	स्थिर __be32 *prop;

	prop = of_get_property(of_root, "reserved-ranges", &len);
	अगर (!prop)
		वापस 0;

	n_mem_addr_cells = of_n_addr_cells(of_root);
	n_mem_size_cells = of_n_size_cells(of_root);
	cells = n_mem_addr_cells + n_mem_size_cells;

	/* Each reserved range is an (address,size) pair */
	क्रम (i = 0; i < (len / (माप(u32) * cells)); i++) अणु
		u64 base, size;

		base = of_पढ़ो_number(prop + (i * cells), n_mem_addr_cells);
		size = of_पढ़ो_number(prop + (i * cells) + n_mem_addr_cells,
				      n_mem_size_cells);

		ret = add_mem_range(mem_ranges, base, size);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
