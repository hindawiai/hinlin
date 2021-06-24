<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ppc64 code to implement the kexec_file_load syscall
 *
 * Copyright (C) 2004  Adam Litke (agl@us.ibm.com)
 * Copyright (C) 2004  IBM Corp.
 * Copyright (C) 2004,2005  Milton D Miller II, IBM Corporation
 * Copyright (C) 2005  R Sharada (sharada@in.ibm.com)
 * Copyright (C) 2006  Mohan Kumar M (mohan@in.ibm.com)
 * Copyright (C) 2020  IBM Corporation
 *
 * Based on kexec-tools' kexec-ppc64.c, kexec-elf-rel-ppc64.c, fs2dt.c.
 * Heavily modअगरied क्रम the kernel by
 * Hari Bathini, IBM Corporation.
 */

#समावेश <linux/kexec.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/drस्मृति.स>
#समावेश <यंत्र/kexec_ranges.h>
#समावेश <यंत्र/crashdump-ppc64.h>

काष्ठा umem_info अणु
	u64 *buf;		/* data buffer क्रम usable-memory property */
	u32 size;		/* size allocated क्रम the data buffer */
	u32 max_entries;	/* maximum no. of entries */
	u32 idx;		/* index of current entry */

	/* usable memory ranges to look up */
	अचिन्हित पूर्णांक nr_ranges;
	स्थिर काष्ठा crash_mem_range *ranges;
पूर्ण;

स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[] = अणु
	&kexec_elf64_ops,
	शून्य
पूर्ण;

/**
 * get_exclude_memory_ranges - Get exclude memory ranges. This list includes
 *                             regions like opal/rtas, tce-table, initrd,
 *                             kernel, htab which should be aव्योमed जबतक
 *                             setting up kexec load segments.
 * @mem_ranges:                Range list to add the memory ranges to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक get_exclude_memory_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	पूर्णांक ret;

	ret = add_tce_mem_ranges(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_initrd_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_htab_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_kernel_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_rtas_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_opal_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_reserved_mem_ranges(mem_ranges);
	अगर (ret)
		जाओ out;

	/* exclude memory ranges should be sorted क्रम easy lookup */
	sort_memory_ranges(*mem_ranges, true);
out:
	अगर (ret)
		pr_err("Failed to setup exclude memory ranges\n");
	वापस ret;
पूर्ण

/**
 * get_usable_memory_ranges - Get usable memory ranges. This list includes
 *                            regions like crashkernel, opal/rtas & tce-table,
 *                            that kdump kernel could use.
 * @mem_ranges:               Range list to add the memory ranges to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक get_usable_memory_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	पूर्णांक ret;

	/*
	 * Early boot failure observed on guests when low memory (first memory
	 * block?) is not added to usable memory. So, add [0, crashk_res.end]
	 * instead of [crashk_res.start, crashk_res.end] to workaround it.
	 * Also, crashed kernel's memory must be added to reserve map to
	 * aव्योम kdump kernel from using it.
	 */
	ret = add_mem_range(mem_ranges, 0, crashk_res.end + 1);
	अगर (ret)
		जाओ out;

	ret = add_rtas_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_opal_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_tce_mem_ranges(mem_ranges);
out:
	अगर (ret)
		pr_err("Failed to setup usable memory ranges\n");
	वापस ret;
पूर्ण

/**
 * get_crash_memory_ranges - Get crash memory ranges. This list includes
 *                           first/crashing kernel's memory regions that
 *                           would be exported via an elfcore.
 * @mem_ranges:              Range list to add the memory ranges to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक get_crash_memory_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	phys_addr_t base, end;
	काष्ठा crash_mem *पंचांगem;
	u64 i;
	पूर्णांक ret;

	क्रम_each_mem_range(i, &base, &end) अणु
		u64 size = end - base;

		/* Skip backup memory region, which needs a separate entry */
		अगर (base == BACKUP_SRC_START) अणु
			अगर (size > BACKUP_SRC_SIZE) अणु
				base = BACKUP_SRC_END + 1;
				size -= BACKUP_SRC_SIZE;
			पूर्ण अन्यथा
				जारी;
		पूर्ण

		ret = add_mem_range(mem_ranges, base, size);
		अगर (ret)
			जाओ out;

		/* Try merging adjacent ranges beक्रमe पुनः_स्मृतिation attempt */
		अगर ((*mem_ranges)->nr_ranges == (*mem_ranges)->max_nr_ranges)
			sort_memory_ranges(*mem_ranges, true);
	पूर्ण

	/* Reallocate memory ranges अगर there is no space to split ranges */
	पंचांगem = *mem_ranges;
	अगर (पंचांगem && (पंचांगem->nr_ranges == पंचांगem->max_nr_ranges)) अणु
		पंचांगem = पुनः_स्मृति_mem_ranges(mem_ranges);
		अगर (!पंचांगem)
			जाओ out;
	पूर्ण

	/* Exclude crashkernel region */
	ret = crash_exclude_mem_range(पंचांगem, crashk_res.start, crashk_res.end);
	अगर (ret)
		जाओ out;

	/*
	 * FIXME: For now, stay in parity with kexec-tools but अगर RTAS/OPAL
	 *        regions are exported to save their context at the समय of
	 *        crash, they should actually be backed up just like the
	 *        first 64K bytes of memory.
	 */
	ret = add_rtas_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_opal_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	/* create a separate program header क्रम the backup region */
	ret = add_mem_range(mem_ranges, BACKUP_SRC_START, BACKUP_SRC_SIZE);
	अगर (ret)
		जाओ out;

	sort_memory_ranges(*mem_ranges, false);
out:
	अगर (ret)
		pr_err("Failed to setup crash memory ranges\n");
	वापस ret;
पूर्ण

/**
 * get_reserved_memory_ranges - Get reserve memory ranges. This list includes
 *                              memory regions that should be added to the
 *                              memory reserve map to ensure the region is
 *                              रक्षित from any mischief.
 * @mem_ranges:                 Range list to add the memory ranges to.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक get_reserved_memory_ranges(काष्ठा crash_mem **mem_ranges)
अणु
	पूर्णांक ret;

	ret = add_rtas_mem_range(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_tce_mem_ranges(mem_ranges);
	अगर (ret)
		जाओ out;

	ret = add_reserved_mem_ranges(mem_ranges);
out:
	अगर (ret)
		pr_err("Failed to setup reserved memory ranges\n");
	वापस ret;
पूर्ण

/**
 * __locate_mem_hole_top_करोwn - Looks top करोwn क्रम a large enough memory hole
 *                              in the memory regions between buf_min & buf_max
 *                              क्रम the buffer. If found, sets kbuf->mem.
 * @kbuf:                       Buffer contents and memory parameters.
 * @buf_min:                    Minimum address क्रम the buffer.
 * @buf_max:                    Maximum address क्रम the buffer.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक __locate_mem_hole_top_करोwn(काष्ठा kexec_buf *kbuf,
				      u64 buf_min, u64 buf_max)
अणु
	पूर्णांक ret = -EADDRNOTAVAIL;
	phys_addr_t start, end;
	u64 i;

	क्रम_each_mem_range_rev(i, &start, &end) अणु
		/*
		 * memblock uses [start, end) convention जबतक it is
		 * [start, end] here. Fix the off-by-one to have the
		 * same convention.
		 */
		end -= 1;

		अगर (start > buf_max)
			जारी;

		/* Memory hole not found */
		अगर (end < buf_min)
			अवरोध;

		/* Adjust memory region based on the given range */
		अगर (start < buf_min)
			start = buf_min;
		अगर (end > buf_max)
			end = buf_max;

		start = ALIGN(start, kbuf->buf_align);
		अगर (start < end && (end - start + 1) >= kbuf->memsz) अणु
			/* Suitable memory range found. Set kbuf->mem */
			kbuf->mem = ALIGN_DOWN(end - kbuf->memsz + 1,
					       kbuf->buf_align);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * locate_mem_hole_top_करोwn_ppc64 - Skip special memory regions to find a
 *                                  suitable buffer with top करोwn approach.
 * @kbuf:                           Buffer contents and memory parameters.
 * @buf_min:                        Minimum address क्रम the buffer.
 * @buf_max:                        Maximum address क्रम the buffer.
 * @emem:                           Exclude memory ranges.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक locate_mem_hole_top_करोwn_ppc64(काष्ठा kexec_buf *kbuf,
					  u64 buf_min, u64 buf_max,
					  स्थिर काष्ठा crash_mem *emem)
अणु
	पूर्णांक i, ret = 0, err = -EADDRNOTAVAIL;
	u64 start, end, पंचांगin, पंचांगax;

	पंचांगax = buf_max;
	क्रम (i = (emem->nr_ranges - 1); i >= 0; i--) अणु
		start = emem->ranges[i].start;
		end = emem->ranges[i].end;

		अगर (start > पंचांगax)
			जारी;

		अगर (end < पंचांगax) अणु
			पंचांगin = (end < buf_min ? buf_min : end + 1);
			ret = __locate_mem_hole_top_करोwn(kbuf, पंचांगin, पंचांगax);
			अगर (!ret)
				वापस 0;
		पूर्ण

		पंचांगax = start - 1;

		अगर (पंचांगax < buf_min) अणु
			ret = err;
			अवरोध;
		पूर्ण
		ret = 0;
	पूर्ण

	अगर (!ret) अणु
		पंचांगin = buf_min;
		ret = __locate_mem_hole_top_करोwn(kbuf, पंचांगin, पंचांगax);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * __locate_mem_hole_bottom_up - Looks bottom up क्रम a large enough memory hole
 *                               in the memory regions between buf_min & buf_max
 *                               क्रम the buffer. If found, sets kbuf->mem.
 * @kbuf:                        Buffer contents and memory parameters.
 * @buf_min:                     Minimum address क्रम the buffer.
 * @buf_max:                     Maximum address क्रम the buffer.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक __locate_mem_hole_bottom_up(काष्ठा kexec_buf *kbuf,
				       u64 buf_min, u64 buf_max)
अणु
	पूर्णांक ret = -EADDRNOTAVAIL;
	phys_addr_t start, end;
	u64 i;

	क्रम_each_mem_range(i, &start, &end) अणु
		/*
		 * memblock uses [start, end) convention जबतक it is
		 * [start, end] here. Fix the off-by-one to have the
		 * same convention.
		 */
		end -= 1;

		अगर (end < buf_min)
			जारी;

		/* Memory hole not found */
		अगर (start > buf_max)
			अवरोध;

		/* Adjust memory region based on the given range */
		अगर (start < buf_min)
			start = buf_min;
		अगर (end > buf_max)
			end = buf_max;

		start = ALIGN(start, kbuf->buf_align);
		अगर (start < end && (end - start + 1) >= kbuf->memsz) अणु
			/* Suitable memory range found. Set kbuf->mem */
			kbuf->mem = start;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * locate_mem_hole_bottom_up_ppc64 - Skip special memory regions to find a
 *                                   suitable buffer with bottom up approach.
 * @kbuf:                            Buffer contents and memory parameters.
 * @buf_min:                         Minimum address क्रम the buffer.
 * @buf_max:                         Maximum address क्रम the buffer.
 * @emem:                            Exclude memory ranges.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक locate_mem_hole_bottom_up_ppc64(काष्ठा kexec_buf *kbuf,
					   u64 buf_min, u64 buf_max,
					   स्थिर काष्ठा crash_mem *emem)
अणु
	पूर्णांक i, ret = 0, err = -EADDRNOTAVAIL;
	u64 start, end, पंचांगin, पंचांगax;

	पंचांगin = buf_min;
	क्रम (i = 0; i < emem->nr_ranges; i++) अणु
		start = emem->ranges[i].start;
		end = emem->ranges[i].end;

		अगर (end < पंचांगin)
			जारी;

		अगर (start > पंचांगin) अणु
			पंचांगax = (start > buf_max ? buf_max : start - 1);
			ret = __locate_mem_hole_bottom_up(kbuf, पंचांगin, पंचांगax);
			अगर (!ret)
				वापस 0;
		पूर्ण

		पंचांगin = end + 1;

		अगर (पंचांगin > buf_max) अणु
			ret = err;
			अवरोध;
		पूर्ण
		ret = 0;
	पूर्ण

	अगर (!ret) अणु
		पंचांगax = buf_max;
		ret = __locate_mem_hole_bottom_up(kbuf, पंचांगin, पंचांगax);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * check_पुनः_स्मृति_usable_mem - Reallocate buffer अगर it can't accommodate entries
 * @um_info:                  Usable memory buffer and ranges info.
 * @cnt:                      No. of entries to accommodate.
 *
 * Frees up the old buffer अगर memory पुनः_स्मृतिation fails.
 *
 * Returns buffer on success, शून्य on error.
 */
अटल u64 *check_पुनः_स्मृति_usable_mem(काष्ठा umem_info *um_info, पूर्णांक cnt)
अणु
	u32 new_size;
	u64 *tbuf;

	अगर ((um_info->idx + cnt) <= um_info->max_entries)
		वापस um_info->buf;

	new_size = um_info->size + MEM_RANGE_CHUNK_SZ;
	tbuf = kपुनः_स्मृति(um_info->buf, new_size, GFP_KERNEL);
	अगर (tbuf) अणु
		um_info->buf = tbuf;
		um_info->size = new_size;
		um_info->max_entries = (um_info->size / माप(u64));
	पूर्ण

	वापस tbuf;
पूर्ण

/**
 * add_usable_mem - Add the usable memory ranges within the given memory range
 *                  to the buffer
 * @um_info:        Usable memory buffer and ranges info.
 * @base:           Base address of memory range to look क्रम.
 * @end:            End address of memory range to look क्रम.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक add_usable_mem(काष्ठा umem_info *um_info, u64 base, u64 end)
अणु
	u64 loc_base, loc_end;
	bool add;
	पूर्णांक i;

	क्रम (i = 0; i < um_info->nr_ranges; i++) अणु
		add = false;
		loc_base = um_info->ranges[i].start;
		loc_end = um_info->ranges[i].end;
		अगर (loc_base >= base && loc_end <= end)
			add = true;
		अन्यथा अगर (base < loc_end && end > loc_base) अणु
			अगर (loc_base < base)
				loc_base = base;
			अगर (loc_end > end)
				loc_end = end;
			add = true;
		पूर्ण

		अगर (add) अणु
			अगर (!check_पुनः_स्मृति_usable_mem(um_info, 2))
				वापस -ENOMEM;

			um_info->buf[um_info->idx++] = cpu_to_be64(loc_base);
			um_info->buf[um_info->idx++] =
					cpu_to_be64(loc_end - loc_base + 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * kdump_setup_usable_lmb - This is a callback function that माला_लो called by
 *                          walk_drmem_lmbs क्रम every LMB to set its
 *                          usable memory ranges.
 * @lmb:                    LMB info.
 * @usm:                    linux,drconf-usable-memory property value.
 * @data:                   Poपूर्णांकer to usable memory buffer and ranges info.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक kdump_setup_usable_lmb(काष्ठा drmem_lmb *lmb, स्थिर __be32 **usm,
				  व्योम *data)
अणु
	काष्ठा umem_info *um_info;
	पूर्णांक पंचांगp_idx, ret;
	u64 base, end;

	/*
	 * kdump load isn't supported on kernels alपढ़ोy booted with
	 * linux,drconf-usable-memory property.
	 */
	अगर (*usm) अणु
		pr_err("linux,drconf-usable-memory property already exists!");
		वापस -EINVAL;
	पूर्ण

	um_info = data;
	पंचांगp_idx = um_info->idx;
	अगर (!check_पुनः_स्मृति_usable_mem(um_info, 1))
		वापस -ENOMEM;

	um_info->idx++;
	base = lmb->base_addr;
	end = base + drmem_lmb_size() - 1;
	ret = add_usable_mem(um_info, base, end);
	अगर (!ret) अणु
		/*
		 * Update the no. of ranges added. Two entries (base & size)
		 * क्रम every range added.
		 */
		um_info->buf[पंचांगp_idx] =
				cpu_to_be64((um_info->idx - पंचांगp_idx - 1) / 2);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा NODE_PATH_LEN		256
/**
 * add_usable_mem_property - Add usable memory property क्रम the given
 *                           memory node.
 * @fdt:                     Flattened device tree क्रम the kdump kernel.
 * @dn:                      Memory node.
 * @um_info:                 Usable memory buffer and ranges info.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक add_usable_mem_property(व्योम *fdt, काष्ठा device_node *dn,
				   काष्ठा umem_info *um_info)
अणु
	पूर्णांक n_mem_addr_cells, n_mem_size_cells, node;
	अक्षर path[NODE_PATH_LEN];
	पूर्णांक i, len, ranges, ret;
	स्थिर __be32 *prop;
	u64 base, end;

	of_node_get(dn);

	अगर (snम_लिखो(path, NODE_PATH_LEN, "%pOF", dn) > (NODE_PATH_LEN - 1)) अणु
		pr_err("Buffer (%d) too small for memory node: %pOF\n",
		       NODE_PATH_LEN, dn);
		वापस -EOVERFLOW;
	पूर्ण
	pr_debug("Memory node path: %s\n", path);

	/* Now that we know the path, find its offset in kdump kernel's fdt */
	node = fdt_path_offset(fdt, path);
	अगर (node < 0) अणु
		pr_err("Malformed device tree: error reading %s\n", path);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Get the address & size cells */
	n_mem_addr_cells = of_n_addr_cells(dn);
	n_mem_size_cells = of_n_size_cells(dn);
	pr_debug("address cells: %d, size cells: %d\n", n_mem_addr_cells,
		 n_mem_size_cells);

	um_info->idx  = 0;
	अगर (!check_पुनः_स्मृति_usable_mem(um_info, 2)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	prop = of_get_property(dn, "reg", &len);
	अगर (!prop || len <= 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * "reg" property represents sequence of (addr,size) tuples
	 * each representing a memory range.
	 */
	ranges = (len >> 2) / (n_mem_addr_cells + n_mem_size_cells);

	क्रम (i = 0; i < ranges; i++) अणु
		base = of_पढ़ो_number(prop, n_mem_addr_cells);
		prop += n_mem_addr_cells;
		end = base + of_पढ़ो_number(prop, n_mem_size_cells) - 1;
		prop += n_mem_size_cells;

		ret = add_usable_mem(um_info, base, end);
		अगर (ret)
			जाओ out;
	पूर्ण

	/*
	 * No kdump kernel usable memory found in this memory node.
	 * Write (0,0) tuple in linux,usable-memory property क्रम
	 * this region to be ignored.
	 */
	अगर (um_info->idx == 0) अणु
		um_info->buf[0] = 0;
		um_info->buf[1] = 0;
		um_info->idx = 2;
	पूर्ण

	ret = fdt_setprop(fdt, node, "linux,usable-memory", um_info->buf,
			  (um_info->idx * माप(u64)));

out:
	of_node_put(dn);
	वापस ret;
पूर्ण


/**
 * update_usable_mem_fdt - Updates kdump kernel's fdt with linux,usable-memory
 *                         and linux,drconf-usable-memory DT properties as
 *                         appropriate to restrict its memory usage.
 * @fdt:                   Flattened device tree क्रम the kdump kernel.
 * @usable_mem:            Usable memory ranges क्रम kdump kernel.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक update_usable_mem_fdt(व्योम *fdt, काष्ठा crash_mem *usable_mem)
अणु
	काष्ठा umem_info um_info;
	काष्ठा device_node *dn;
	पूर्णांक node, ret = 0;

	अगर (!usable_mem) अणु
		pr_err("Usable memory ranges for kdump kernel not found\n");
		वापस -ENOENT;
	पूर्ण

	node = fdt_path_offset(fdt, "/ibm,dynamic-reconfiguration-memory");
	अगर (node == -FDT_ERR_NOTFOUND)
		pr_debug("No dynamic reconfiguration memory found\n");
	अन्यथा अगर (node < 0) अणु
		pr_err("Malformed device tree: error reading /ibm,dynamic-reconfiguration-memory.\n");
		वापस -EINVAL;
	पूर्ण

	um_info.buf  = शून्य;
	um_info.size = 0;
	um_info.max_entries = 0;
	um_info.idx  = 0;
	/* Memory ranges to look up */
	um_info.ranges = &(usable_mem->ranges[0]);
	um_info.nr_ranges = usable_mem->nr_ranges;

	dn = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (dn) अणु
		ret = walk_drmem_lmbs(dn, &um_info, kdump_setup_usable_lmb);
		of_node_put(dn);

		अगर (ret) अणु
			pr_err("Could not setup linux,drconf-usable-memory property for kdump\n");
			जाओ out;
		पूर्ण

		ret = fdt_setprop(fdt, node, "linux,drconf-usable-memory",
				  um_info.buf, (um_info.idx * माप(u64)));
		अगर (ret) अणु
			pr_err("Failed to update fdt with linux,drconf-usable-memory property");
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Walk through each memory node and set linux,usable-memory property
	 * क्रम the corresponding node in kdump kernel's fdt.
	 */
	क्रम_each_node_by_type(dn, "memory") अणु
		ret = add_usable_mem_property(fdt, dn, &um_info);
		अगर (ret) अणु
			pr_err("Failed to set linux,usable-memory property for %s node",
			       dn->full_name);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(um_info.buf);
	वापस ret;
पूर्ण

/**
 * load_backup_segment - Locate a memory hole to place the backup region.
 * @image:               Kexec image.
 * @kbuf:                Buffer contents and memory parameters.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक load_backup_segment(काष्ठा kimage *image, काष्ठा kexec_buf *kbuf)
अणु
	व्योम *buf;
	पूर्णांक ret;

	/*
	 * Setup a source buffer क्रम backup segment.
	 *
	 * A source buffer has no meaning क्रम backup region as data will
	 * be copied from backup source, after crash, in the purgatory.
	 * But as load segment code करोesn't recognize such segments,
	 * setup a dummy source buffer to keep it happy क्रम now.
	 */
	buf = vzalloc(BACKUP_SRC_SIZE);
	अगर (!buf)
		वापस -ENOMEM;

	kbuf->buffer = buf;
	kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf->bufsz = kbuf->memsz = BACKUP_SRC_SIZE;
	kbuf->top_करोwn = false;

	ret = kexec_add_buffer(kbuf);
	अगर (ret) अणु
		vमुक्त(buf);
		वापस ret;
	पूर्ण

	image->arch.backup_buf = buf;
	image->arch.backup_start = kbuf->mem;
	वापस 0;
पूर्ण

/**
 * update_backup_region_phdr - Update backup region's offset क्रम the core to
 *                             export the region appropriately.
 * @image:                     Kexec image.
 * @ehdr:                      ELF core header.
 *
 * Assumes an exclusive program header is setup क्रम the backup region
 * in the ELF headers
 *
 * Returns nothing.
 */
अटल व्योम update_backup_region_phdr(काष्ठा kimage *image, Elf64_Ehdr *ehdr)
अणु
	Elf64_Phdr *phdr;
	अचिन्हित पूर्णांक i;

	phdr = (Elf64_Phdr *)(ehdr + 1);
	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		अगर (phdr->p_paddr == BACKUP_SRC_START) अणु
			phdr->p_offset = image->arch.backup_start;
			pr_debug("Backup region offset updated to 0x%lx\n",
				 image->arch.backup_start);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * load_elfcorehdr_segment - Setup crash memory ranges and initialize elfcorehdr
 *                           segment needed to load kdump kernel.
 * @image:                   Kexec image.
 * @kbuf:                    Buffer contents and memory parameters.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक load_elfcorehdr_segment(काष्ठा kimage *image, काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा crash_mem *cmem = शून्य;
	अचिन्हित दीर्घ headers_sz;
	व्योम *headers = शून्य;
	पूर्णांक ret;

	ret = get_crash_memory_ranges(&cmem);
	अगर (ret)
		जाओ out;

	/* Setup elfcorehdr segment */
	ret = crash_prepare_elf64_headers(cmem, false, &headers, &headers_sz);
	अगर (ret) अणु
		pr_err("Failed to prepare elf headers for the core\n");
		जाओ out;
	पूर्ण

	/* Fix the offset क्रम backup region in the ELF header */
	update_backup_region_phdr(image, headers);

	kbuf->buffer = headers;
	kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf->bufsz = kbuf->memsz = headers_sz;
	kbuf->top_करोwn = false;

	ret = kexec_add_buffer(kbuf);
	अगर (ret) अणु
		vमुक्त(headers);
		जाओ out;
	पूर्ण

	image->elf_load_addr = kbuf->mem;
	image->elf_headers_sz = headers_sz;
	image->elf_headers = headers;
out:
	kमुक्त(cmem);
	वापस ret;
पूर्ण

/**
 * load_crashdump_segments_ppc64 - Initialize the additional segements needed
 *                                 to load kdump kernel.
 * @image:                         Kexec image.
 * @kbuf:                          Buffer contents and memory parameters.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक load_crashdump_segments_ppc64(काष्ठा kimage *image,
				  काष्ठा kexec_buf *kbuf)
अणु
	पूर्णांक ret;

	/* Load backup segment - first 64K bytes of the crashing kernel */
	ret = load_backup_segment(image, kbuf);
	अगर (ret) अणु
		pr_err("Failed to load backup segment\n");
		वापस ret;
	पूर्ण
	pr_debug("Loaded the backup region at 0x%lx\n", kbuf->mem);

	/* Load elfcorehdr segment - to export crashing kernel's vmcore */
	ret = load_elfcorehdr_segment(image, kbuf);
	अगर (ret) अणु
		pr_err("Failed to load elfcorehdr segment\n");
		वापस ret;
	पूर्ण
	pr_debug("Loaded elf core header at 0x%lx, bufsz=0x%lx memsz=0x%lx\n",
		 image->elf_load_addr, kbuf->bufsz, kbuf->memsz);

	वापस 0;
पूर्ण

/**
 * setup_purgatory_ppc64 - initialize PPC64 specअगरic purgatory's global
 *                         variables and call setup_purgatory() to initialize
 *                         common global variable.
 * @image:                 kexec image.
 * @slave_code:            Slave code क्रम the purgatory.
 * @fdt:                   Flattened device tree क्रम the next kernel.
 * @kernel_load_addr:      Address where the kernel is loaded.
 * @fdt_load_addr:         Address where the flattened device tree is loaded.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक setup_purgatory_ppc64(काष्ठा kimage *image, स्थिर व्योम *slave_code,
			  स्थिर व्योम *fdt, अचिन्हित दीर्घ kernel_load_addr,
			  अचिन्हित दीर्घ fdt_load_addr)
अणु
	काष्ठा device_node *dn = शून्य;
	पूर्णांक ret;

	ret = setup_purgatory(image, slave_code, fdt, kernel_load_addr,
			      fdt_load_addr);
	अगर (ret)
		जाओ out;

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		u32 my_run_at_load = 1;

		/*
		 * Tell relocatable kernel to run at load address
		 * via the word meant क्रम that at 0x5c.
		 */
		ret = kexec_purgatory_get_set_symbol(image, "run_at_load",
						     &my_run_at_load,
						     माप(my_run_at_load),
						     false);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Tell purgatory where to look क्रम backup region */
	ret = kexec_purgatory_get_set_symbol(image, "backup_start",
					     &image->arch.backup_start,
					     माप(image->arch.backup_start),
					     false);
	अगर (ret)
		जाओ out;

	/* Setup OPAL base & entry values */
	dn = of_find_node_by_path("/ibm,opal");
	अगर (dn) अणु
		u64 val;

		of_property_पढ़ो_u64(dn, "opal-base-address", &val);
		ret = kexec_purgatory_get_set_symbol(image, "opal_base", &val,
						     माप(val), false);
		अगर (ret)
			जाओ out;

		of_property_पढ़ो_u64(dn, "opal-entry-address", &val);
		ret = kexec_purgatory_get_set_symbol(image, "opal_entry", &val,
						     माप(val), false);
	पूर्ण
out:
	अगर (ret)
		pr_err("Failed to setup purgatory symbols");
	of_node_put(dn);
	वापस ret;
पूर्ण

/**
 * kexec_extra_fdt_size_ppc64 - Return the estimated additional size needed to
 *                              setup FDT क्रम kexec/kdump kernel.
 * @image:                      kexec image being loaded.
 *
 * Returns the estimated extra size needed क्रम kexec/kdump kernel FDT.
 */
अचिन्हित पूर्णांक kexec_extra_fdt_size_ppc64(काष्ठा kimage *image)
अणु
	u64 usm_entries;

	अगर (image->type != KEXEC_TYPE_CRASH)
		वापस 0;

	/*
	 * For kdump kernel, account क्रम linux,usable-memory and
	 * linux,drconf-usable-memory properties. Get an approximate on the
	 * number of usable memory entries and use क्रम FDT size estimation.
	 */
	usm_entries = ((memblock_end_of_DRAM() / drmem_lmb_size()) +
		       (2 * (resource_size(&crashk_res) / drmem_lmb_size())));
	वापस (अचिन्हित पूर्णांक)(usm_entries * माप(u64));
पूर्ण

/**
 * add_node_props - Reads node properties from device node काष्ठाure and add
 *                  them to fdt.
 * @fdt:            Flattened device tree of the kernel
 * @node_offset:    offset of the node to add a property at
 * @dn:             device node poपूर्णांकer
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक add_node_props(व्योम *fdt, पूर्णांक node_offset, स्थिर काष्ठा device_node *dn)
अणु
	पूर्णांक ret = 0;
	काष्ठा property *pp;

	अगर (!dn)
		वापस -EINVAL;

	क्रम_each_property_of_node(dn, pp) अणु
		ret = fdt_setprop(fdt, node_offset, pp->name, pp->value, pp->length);
		अगर (ret < 0) अणु
			pr_err("Unable to add %s property: %s\n", pp->name, fdt_म_त्रुटि(ret));
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * update_cpus_node - Update cpus node of flattened device tree using of_root
 *                    device node.
 * @fdt:              Flattened device tree of the kernel.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक update_cpus_node(व्योम *fdt)
अणु
	काष्ठा device_node *cpus_node, *dn;
	पूर्णांक cpus_offset, cpus_subnode_offset, ret = 0;

	cpus_offset = fdt_path_offset(fdt, "/cpus");
	अगर (cpus_offset < 0 && cpus_offset != -FDT_ERR_NOTFOUND) अणु
		pr_err("Malformed device tree: error reading /cpus node: %s\n",
		       fdt_म_त्रुटि(cpus_offset));
		वापस cpus_offset;
	पूर्ण

	अगर (cpus_offset > 0) अणु
		ret = fdt_del_node(fdt, cpus_offset);
		अगर (ret < 0) अणु
			pr_err("Error deleting /cpus node: %s\n", fdt_म_त्रुटि(ret));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Add cpus node to fdt */
	cpus_offset = fdt_add_subnode(fdt, fdt_path_offset(fdt, "/"), "cpus");
	अगर (cpus_offset < 0) अणु
		pr_err("Error creating /cpus node: %s\n", fdt_म_त्रुटि(cpus_offset));
		वापस -EINVAL;
	पूर्ण

	/* Add cpus node properties */
	cpus_node = of_find_node_by_path("/cpus");
	ret = add_node_props(fdt, cpus_offset, cpus_node);
	of_node_put(cpus_node);
	अगर (ret < 0)
		वापस ret;

	/* Loop through all subnodes of cpus and add them to fdt */
	क्रम_each_node_by_type(dn, "cpu") अणु
		cpus_subnode_offset = fdt_add_subnode(fdt, cpus_offset, dn->full_name);
		अगर (cpus_subnode_offset < 0) अणु
			pr_err("Unable to add %s subnode: %s\n", dn->full_name,
			       fdt_म_त्रुटि(cpus_subnode_offset));
			ret = cpus_subnode_offset;
			जाओ out;
		पूर्ण

		ret = add_node_props(fdt, cpus_subnode_offset, dn);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	of_node_put(dn);
	वापस ret;
पूर्ण

/**
 * setup_new_fdt_ppc64 - Update the flattend device-tree of the kernel
 *                       being loaded.
 * @image:               kexec image being loaded.
 * @fdt:                 Flattened device tree क्रम the next kernel.
 * @initrd_load_addr:    Address where the next initrd will be loaded.
 * @initrd_len:          Size of the next initrd, or 0 अगर there will be none.
 * @cmdline:             Command line क्रम the next kernel, or शून्य अगर there will
 *                       be none.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक setup_new_fdt_ppc64(स्थिर काष्ठा kimage *image, व्योम *fdt,
			अचिन्हित दीर्घ initrd_load_addr,
			अचिन्हित दीर्घ initrd_len, स्थिर अक्षर *cmdline)
अणु
	काष्ठा crash_mem *umem = शून्य, *rmem = शून्य;
	पूर्णांक i, nr_ranges, ret;

	/*
	 * Restrict memory usage क्रम kdump kernel by setting up
	 * usable memory ranges and memory reserve map.
	 */
	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		ret = get_usable_memory_ranges(&umem);
		अगर (ret)
			जाओ out;

		ret = update_usable_mem_fdt(fdt, umem);
		अगर (ret) अणु
			pr_err("Error setting up usable-memory property for kdump kernel\n");
			जाओ out;
		पूर्ण

		/*
		 * Ensure we करोn't touch crashed kernel's memory except the
		 * first 64K of RAM, which will be backed up.
		 */
		ret = fdt_add_mem_rsv(fdt, BACKUP_SRC_END + 1,
				      crashk_res.start - BACKUP_SRC_SIZE);
		अगर (ret) अणु
			pr_err("Error reserving crash memory: %s\n",
			       fdt_म_त्रुटि(ret));
			जाओ out;
		पूर्ण

		/* Ensure backup region is not used by kdump/capture kernel */
		ret = fdt_add_mem_rsv(fdt, image->arch.backup_start,
				      BACKUP_SRC_SIZE);
		अगर (ret) अणु
			pr_err("Error reserving memory for backup: %s\n",
			       fdt_म_त्रुटि(ret));
			जाओ out;
		पूर्ण
	पूर्ण

	/* Update cpus nodes inक्रमmation to account hotplug CPUs. */
	ret =  update_cpus_node(fdt);
	अगर (ret < 0)
		जाओ out;

	/* Update memory reserve map */
	ret = get_reserved_memory_ranges(&rmem);
	अगर (ret)
		जाओ out;

	nr_ranges = rmem ? rmem->nr_ranges : 0;
	क्रम (i = 0; i < nr_ranges; i++) अणु
		u64 base, size;

		base = rmem->ranges[i].start;
		size = rmem->ranges[i].end - base + 1;
		ret = fdt_add_mem_rsv(fdt, base, size);
		अगर (ret) अणु
			pr_err("Error updating memory reserve map: %s\n",
			       fdt_म_त्रुटि(ret));
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(rmem);
	kमुक्त(umem);
	वापस ret;
पूर्ण

/**
 * arch_kexec_locate_mem_hole - Skip special memory regions like rtas, opal,
 *                              tce-table, reserved-ranges & such (exclude
 *                              memory ranges) as they can't be used क्रम kexec
 *                              segment buffer. Sets kbuf->mem when a suitable
 *                              memory hole is found.
 * @kbuf:                       Buffer contents and memory parameters.
 *
 * Assumes minimum of PAGE_SIZE alignment क्रम kbuf->memsz & kbuf->buf_align.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक arch_kexec_locate_mem_hole(काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा crash_mem **emem;
	u64 buf_min, buf_max;
	पूर्णांक ret;

	/* Look up the exclude ranges list जबतक locating the memory hole */
	emem = &(kbuf->image->arch.exclude_ranges);
	अगर (!(*emem) || ((*emem)->nr_ranges == 0)) अणु
		pr_warn("No exclude range list. Using the default locate mem hole method\n");
		वापस kexec_locate_mem_hole(kbuf);
	पूर्ण

	buf_min = kbuf->buf_min;
	buf_max = kbuf->buf_max;
	/* Segments क्रम kdump kernel should be within crashkernel region */
	अगर (kbuf->image->type == KEXEC_TYPE_CRASH) अणु
		buf_min = (buf_min < crashk_res.start ?
			   crashk_res.start : buf_min);
		buf_max = (buf_max > crashk_res.end ?
			   crashk_res.end : buf_max);
	पूर्ण

	अगर (buf_min > buf_max) अणु
		pr_err("Invalid buffer min and/or max values\n");
		वापस -EINVAL;
	पूर्ण

	अगर (kbuf->top_करोwn)
		ret = locate_mem_hole_top_करोwn_ppc64(kbuf, buf_min, buf_max,
						     *emem);
	अन्यथा
		ret = locate_mem_hole_bottom_up_ppc64(kbuf, buf_min, buf_max,
						      *emem);

	/* Add the buffer allocated to the exclude list क्रम the next lookup */
	अगर (!ret) अणु
		add_mem_range(emem, kbuf->mem, kbuf->memsz);
		sort_memory_ranges(*emem, true);
	पूर्ण अन्यथा अणु
		pr_err("Failed to locate memory buffer of size %lu\n",
		       kbuf->memsz);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * arch_kexec_kernel_image_probe - Does additional handling needed to setup
 *                                 kexec segments.
 * @image:                         kexec image being loaded.
 * @buf:                           Buffer poपूर्णांकing to elf data.
 * @buf_len:                       Length of the buffer.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक arch_kexec_kernel_image_probe(काष्ठा kimage *image, व्योम *buf,
				  अचिन्हित दीर्घ buf_len)
अणु
	पूर्णांक ret;

	/* Get exclude memory ranges needed क्रम setting up kexec segments */
	ret = get_exclude_memory_ranges(&(image->arch.exclude_ranges));
	अगर (ret) अणु
		pr_err("Failed to setup exclude memory ranges for buffer lookup\n");
		वापस ret;
	पूर्ण

	वापस kexec_image_probe_शेष(image, buf, buf_len);
पूर्ण

/**
 * arch_kimage_file_post_load_cleanup - Frees up all the allocations करोne
 *                                      जबतक loading the image.
 * @image:                              kexec image being loaded.
 *
 * Returns 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक arch_kimage_file_post_load_cleanup(काष्ठा kimage *image)
अणु
	kमुक्त(image->arch.exclude_ranges);
	image->arch.exclude_ranges = शून्य;

	vमुक्त(image->arch.backup_buf);
	image->arch.backup_buf = शून्य;

	vमुक्त(image->elf_headers);
	image->elf_headers = शून्य;
	image->elf_headers_sz = 0;

	kvमुक्त(image->arch.fdt);
	image->arch.fdt = शून्य;

	वापस kexec_image_post_load_cleanup_शेष(image);
पूर्ण
