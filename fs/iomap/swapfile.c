<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/swap.h>

/* Swapfile activation */

काष्ठा iomap_swapfile_info अणु
	काष्ठा iomap iomap;		/* accumulated iomap */
	काष्ठा swap_info_काष्ठा *sis;
	uपूर्णांक64_t lowest_ppage;		/* lowest physical addr seen (pages) */
	uपूर्णांक64_t highest_ppage;		/* highest physical addr seen (pages) */
	अचिन्हित दीर्घ nr_pages;		/* number of pages collected */
	पूर्णांक nr_extents;			/* extent count */
	काष्ठा file *file;
पूर्ण;

/*
 * Collect physical extents क्रम this swap file.  Physical extents reported to
 * the swap code must be trimmed to align to a page boundary.  The logical
 * offset within the file is irrelevant since the swapfile code maps logical
 * page numbers of the swap device to the physical page-aligned extents.
 */
अटल पूर्णांक iomap_swapfile_add_extent(काष्ठा iomap_swapfile_info *isi)
अणु
	काष्ठा iomap *iomap = &isi->iomap;
	अचिन्हित दीर्घ nr_pages;
	uपूर्णांक64_t first_ppage;
	uपूर्णांक64_t first_ppage_reported;
	uपूर्णांक64_t next_ppage;
	पूर्णांक error;

	/*
	 * Round the start up and the end करोwn so that the physical
	 * extent aligns to a page boundary.
	 */
	first_ppage = ALIGN(iomap->addr, PAGE_SIZE) >> PAGE_SHIFT;
	next_ppage = ALIGN_DOWN(iomap->addr + iomap->length, PAGE_SIZE) >>
			PAGE_SHIFT;

	/* Skip too-लघु physical extents. */
	अगर (first_ppage >= next_ppage)
		वापस 0;
	nr_pages = next_ppage - first_ppage;

	/*
	 * Calculate how much swap space we're adding; the first page contains
	 * the swap header and करोesn't count.  The mm still wants that first
	 * page fed to add_swap_extent, however.
	 */
	first_ppage_reported = first_ppage;
	अगर (iomap->offset == 0)
		first_ppage_reported++;
	अगर (isi->lowest_ppage > first_ppage_reported)
		isi->lowest_ppage = first_ppage_reported;
	अगर (isi->highest_ppage < (next_ppage - 1))
		isi->highest_ppage = next_ppage - 1;

	/* Add extent, set up क्रम the next call. */
	error = add_swap_extent(isi->sis, isi->nr_pages, nr_pages, first_ppage);
	अगर (error < 0)
		वापस error;
	isi->nr_extents += error;
	isi->nr_pages += nr_pages;
	वापस 0;
पूर्ण

अटल पूर्णांक iomap_swapfile_fail(काष्ठा iomap_swapfile_info *isi, स्थिर अक्षर *str)
अणु
	अक्षर *buf, *p = ERR_PTR(-ENOMEM);

	buf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (buf)
		p = file_path(isi->file, buf, PATH_MAX);
	pr_err("swapon: file %s %s\n", IS_ERR(p) ? "<unknown>" : p, str);
	kमुक्त(buf);
	वापस -EINVAL;
पूर्ण

/*
 * Accumulate iomaps क्रम this swap file.  We have to accumulate iomaps because
 * swap only cares about contiguous page-aligned physical extents and makes no
 * distinction between written and unwritten extents.
 */
अटल loff_t iomap_swapfile_activate_actor(काष्ठा inode *inode, loff_t pos,
		loff_t count, व्योम *data, काष्ठा iomap *iomap,
		काष्ठा iomap *srcmap)
अणु
	काष्ठा iomap_swapfile_info *isi = data;
	पूर्णांक error;

	चयन (iomap->type) अणु
	हाल IOMAP_MAPPED:
	हाल IOMAP_UNWRITTEN:
		/* Only real or unwritten extents. */
		अवरोध;
	हाल IOMAP_INLINE:
		/* No अंतरभूत data. */
		वापस iomap_swapfile_fail(isi, "is inline");
	शेष:
		वापस iomap_swapfile_fail(isi, "has unallocated extents");
	पूर्ण

	/* No uncommitted metadata or shared blocks. */
	अगर (iomap->flags & IOMAP_F_सूचीTY)
		वापस iomap_swapfile_fail(isi, "is not committed");
	अगर (iomap->flags & IOMAP_F_SHARED)
		वापस iomap_swapfile_fail(isi, "has shared extents");

	/* Only one bdev per swap file. */
	अगर (iomap->bdev != isi->sis->bdev)
		वापस iomap_swapfile_fail(isi, "outside the main device");

	अगर (isi->iomap.length == 0) अणु
		/* No accumulated extent, so just store it. */
		स_नकल(&isi->iomap, iomap, माप(isi->iomap));
	पूर्ण अन्यथा अगर (isi->iomap.addr + isi->iomap.length == iomap->addr) अणु
		/* Append this to the accumulated extent. */
		isi->iomap.length += iomap->length;
	पूर्ण अन्यथा अणु
		/* Otherwise, add the retained iomap and store this one. */
		error = iomap_swapfile_add_extent(isi);
		अगर (error)
			वापस error;
		स_नकल(&isi->iomap, iomap, माप(isi->iomap));
	पूर्ण
	वापस count;
पूर्ण

/*
 * Iterate a swap file's iomaps to स्थिरruct physical extents that can be
 * passed to the swapfile subप्रणाली.
 */
पूर्णांक iomap_swapfile_activate(काष्ठा swap_info_काष्ठा *sis,
		काष्ठा file *swap_file, sector_t *pagespan,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा iomap_swapfile_info isi = अणु
		.sis = sis,
		.lowest_ppage = (sector_t)-1ULL,
		.file = swap_file,
	पूर्ण;
	काष्ठा address_space *mapping = swap_file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	loff_t pos = 0;
	loff_t len = ALIGN_DOWN(i_size_पढ़ो(inode), PAGE_SIZE);
	loff_t ret;

	/*
	 * Persist all file mapping metadata so that we won't have any
	 * IOMAP_F_सूचीTY iomaps.
	 */
	ret = vfs_fsync(swap_file, 1);
	अगर (ret)
		वापस ret;

	जबतक (len > 0) अणु
		ret = iomap_apply(inode, pos, len, IOMAP_REPORT,
				ops, &isi, iomap_swapfile_activate_actor);
		अगर (ret <= 0)
			वापस ret;

		pos += ret;
		len -= ret;
	पूर्ण

	अगर (isi.iomap.length) अणु
		ret = iomap_swapfile_add_extent(&isi);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * If this swapfile करोesn't contain even a single page-aligned
	 * contiguous range of blocks, reject this useless swapfile to
	 * prevent confusion later on.
	 */
	अगर (isi.nr_pages == 0) अणु
		pr_warn("swapon: Cannot find a single usable page in file.\n");
		वापस -EINVAL;
	पूर्ण

	*pagespan = 1 + isi.highest_ppage - isi.lowest_ppage;
	sis->max = isi.nr_pages;
	sis->pages = isi.nr_pages - 1;
	sis->highest_bit = isi.nr_pages - 1;
	वापस isi.nr_extents;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_swapfile_activate);
