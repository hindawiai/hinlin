<शैली गुरु>
/*
 * Compressed rom fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 1999 Linus Torvalds.
 *
 * This file is released under the GPL.
 */

/*
 * These are the VFS पूर्णांकerfaces to the compressed rom fileप्रणाली.
 * The actual compression is based on zlib, see the other files.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/super.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfs.h>
#समावेश <linux/mutex.h>
#समावेश <uapi/linux/cramfs_fs.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"

/*
 * cramfs super-block data in memory
 */
काष्ठा cramfs_sb_info अणु
	अचिन्हित दीर्घ magic;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ blocks;
	अचिन्हित दीर्घ files;
	अचिन्हित दीर्घ flags;
	व्योम *linear_virt_addr;
	resource_माप_प्रकार linear_phys_addr;
	माप_प्रकार mtd_poपूर्णांक_size;
पूर्ण;

अटल अंतरभूत काष्ठा cramfs_sb_info *CRAMFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल स्थिर काष्ठा super_operations cramfs_ops;
अटल स्थिर काष्ठा inode_operations cramfs_dir_inode_operations;
अटल स्थिर काष्ठा file_operations cramfs_directory_operations;
अटल स्थिर काष्ठा file_operations cramfs_physmem_fops;
अटल स्थिर काष्ठा address_space_operations cramfs_aops;

अटल DEFINE_MUTEX(पढ़ो_mutex);


/* These macros may change in future, to provide better st_ino semantics. */
#घोषणा OFFSET(x)	((x)->i_ino)

अटल अचिन्हित दीर्घ cramino(स्थिर काष्ठा cramfs_inode *cino, अचिन्हित पूर्णांक offset)
अणु
	अगर (!cino->offset)
		वापस offset + 1;
	अगर (!cino->size)
		वापस offset + 1;

	/*
	 * The file mode test fixes buggy mkcramfs implementations where
	 * cramfs_inode->offset is set to a non zero value क्रम entries
	 * which did not contain data, like devices node and fअगरos.
	 */
	चयन (cino->mode & S_IFMT) अणु
	हाल S_IFREG:
	हाल S_IFसूची:
	हाल S_IFLNK:
		वापस cino->offset << 2;
	शेष:
		अवरोध;
	पूर्ण
	वापस offset + 1;
पूर्ण

अटल काष्ठा inode *get_cramfs_inode(काष्ठा super_block *sb,
	स्थिर काष्ठा cramfs_inode *cramfs_inode, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा inode *inode;
	अटल काष्ठा बारpec64 zeroसमय;

	inode = iget_locked(sb, cramino(cramfs_inode, offset));
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	चयन (cramfs_inode->mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_fop = &generic_ro_fops;
		inode->i_data.a_ops = &cramfs_aops;
		अगर (IS_ENABLED(CONFIG_CRAMFS_MTD) &&
		    CRAMFS_SB(sb)->flags & CRAMFS_FLAG_EXT_BLOCK_POINTERS &&
		    CRAMFS_SB(sb)->linear_phys_addr)
			inode->i_fop = &cramfs_physmem_fops;
		अवरोध;
	हाल S_IFसूची:
		inode->i_op = &cramfs_dir_inode_operations;
		inode->i_fop = &cramfs_directory_operations;
		अवरोध;
	हाल S_IFLNK:
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &cramfs_aops;
		अवरोध;
	शेष:
		init_special_inode(inode, cramfs_inode->mode,
				old_decode_dev(cramfs_inode->size));
	पूर्ण

	inode->i_mode = cramfs_inode->mode;
	i_uid_ग_लिखो(inode, cramfs_inode->uid);
	i_gid_ग_लिखो(inode, cramfs_inode->gid);

	/* अगर the lower 2 bits are zero, the inode contains data */
	अगर (!(inode->i_ino & 3)) अणु
		inode->i_size = cramfs_inode->size;
		inode->i_blocks = (cramfs_inode->size - 1) / 512 + 1;
	पूर्ण

	/* Struct copy पूर्णांकentional */
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = zeroसमय;
	/* inode->i_nlink is left 1 - arguably wrong क्रम directories,
	   but it's the best we can करो without पढ़ोing the directory
	   contents.  1 yields the right result in GNU find, even
	   without -noleaf option. */

	unlock_new_inode(inode);

	वापस inode;
पूर्ण

/*
 * We have our own block cache: करोn't fill up the buffer cache
 * with the rom-image, because the way the fileप्रणाली is set
 * up the accesses should be fairly regular and cached in the
 * page cache and dentry tree anyway..
 *
 * This also acts as a way to guarantee contiguous areas of up to
 * BLKS_PER_BUF*PAGE_SIZE, so that the caller करोesn't need to
 * worry about end-of-buffer issues even when decompressing a full
 * page cache.
 *
 * Note: This is all optimized away at compile समय when
 *       CONFIG_CRAMFS_BLOCKDEV=n.
 */
#घोषणा READ_BUFFERS (2)
/* NEXT_BUFFER(): Loop over [0..(READ_BUFFERS-1)]. */
#घोषणा NEXT_BUFFER(_ix) ((_ix) ^ 1)

/*
 * BLKS_PER_BUF_SHIFT should be at least 2 to allow क्रम "compressed"
 * data that takes up more space than the original and with unlucky
 * alignment.
 */
#घोषणा BLKS_PER_BUF_SHIFT	(2)
#घोषणा BLKS_PER_BUF		(1 << BLKS_PER_BUF_SHIFT)
#घोषणा BUFFER_SIZE		(BLKS_PER_BUF*PAGE_SIZE)

अटल अचिन्हित अक्षर पढ़ो_buffers[READ_BUFFERS][BUFFER_SIZE];
अटल अचिन्हित buffer_blocknr[READ_BUFFERS];
अटल काष्ठा super_block *buffer_dev[READ_BUFFERS];
अटल पूर्णांक next_buffer;

/*
 * Populate our block cache and वापस a poपूर्णांकer to it.
 */
अटल व्योम *cramfs_blkdev_पढ़ो(काष्ठा super_block *sb, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा address_space *mapping = sb->s_bdev->bd_inode->i_mapping;
	काष्ठा page *pages[BLKS_PER_BUF];
	अचिन्हित i, blocknr, buffer;
	अचिन्हित दीर्घ devsize;
	अक्षर *data;

	अगर (!len)
		वापस शून्य;
	blocknr = offset >> PAGE_SHIFT;
	offset &= PAGE_SIZE - 1;

	/* Check अगर an existing buffer alपढ़ोy has the data.. */
	क्रम (i = 0; i < READ_BUFFERS; i++) अणु
		अचिन्हित पूर्णांक blk_offset;

		अगर (buffer_dev[i] != sb)
			जारी;
		अगर (blocknr < buffer_blocknr[i])
			जारी;
		blk_offset = (blocknr - buffer_blocknr[i]) << PAGE_SHIFT;
		blk_offset += offset;
		अगर (blk_offset > BUFFER_SIZE ||
		    blk_offset + len > BUFFER_SIZE)
			जारी;
		वापस पढ़ो_buffers[i] + blk_offset;
	पूर्ण

	devsize = mapping->host->i_size >> PAGE_SHIFT;

	/* Ok, पढ़ो in BLKS_PER_BUF pages completely first. */
	क्रम (i = 0; i < BLKS_PER_BUF; i++) अणु
		काष्ठा page *page = शून्य;

		अगर (blocknr + i < devsize) अणु
			page = पढ़ो_mapping_page(mapping, blocknr + i, शून्य);
			/* synchronous error? */
			अगर (IS_ERR(page))
				page = शून्य;
		पूर्ण
		pages[i] = page;
	पूर्ण

	क्रम (i = 0; i < BLKS_PER_BUF; i++) अणु
		काष्ठा page *page = pages[i];

		अगर (page) अणु
			रुको_on_page_locked(page);
			अगर (!PageUptodate(page)) अणु
				/* asynchronous error */
				put_page(page);
				pages[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	buffer = next_buffer;
	next_buffer = NEXT_BUFFER(buffer);
	buffer_blocknr[buffer] = blocknr;
	buffer_dev[buffer] = sb;

	data = पढ़ो_buffers[buffer];
	क्रम (i = 0; i < BLKS_PER_BUF; i++) अणु
		काष्ठा page *page = pages[i];

		अगर (page) अणु
			स_नकल(data, kmap(page), PAGE_SIZE);
			kunmap(page);
			put_page(page);
		पूर्ण अन्यथा
			स_रखो(data, 0, PAGE_SIZE);
		data += PAGE_SIZE;
	पूर्ण
	वापस पढ़ो_buffers[buffer] + offset;
पूर्ण

/*
 * Return a poपूर्णांकer to the linearly addressed cramfs image in memory.
 */
अटल व्योम *cramfs_direct_पढ़ो(काष्ठा super_block *sb, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(sb);

	अगर (!len)
		वापस शून्य;
	अगर (len > sbi->size || offset > sbi->size - len)
		वापस page_address(ZERO_PAGE(0));
	वापस sbi->linear_virt_addr + offset;
पूर्ण

/*
 * Returns a poपूर्णांकer to a buffer containing at least LEN bytes of
 * fileप्रणाली starting at byte offset OFFSET पूर्णांकo the fileप्रणाली.
 */
अटल व्योम *cramfs_पढ़ो(काष्ठा super_block *sb, अचिन्हित पूर्णांक offset,
			 अचिन्हित पूर्णांक len)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(sb);

	अगर (IS_ENABLED(CONFIG_CRAMFS_MTD) && sbi->linear_virt_addr)
		वापस cramfs_direct_पढ़ो(sb, offset, len);
	अन्यथा अगर (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV))
		वापस cramfs_blkdev_पढ़ो(sb, offset, len);
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * For a mapping to be possible, we need a range of uncompressed and
 * contiguous blocks. Return the offset क्रम the first block and number of
 * valid blocks क्रम which that is true, or zero otherwise.
 */
अटल u32 cramfs_get_block_range(काष्ठा inode *inode, u32 pgoff, u32 *pages)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(inode->i_sb);
	पूर्णांक i;
	u32 *blockptrs, first_block_addr;

	/*
	 * We can dereference memory directly here as this code may be
	 * reached only when there is a direct fileप्रणाली image mapping
	 * available in memory.
	 */
	blockptrs = (u32 *)(sbi->linear_virt_addr + OFFSET(inode) + pgoff * 4);
	first_block_addr = blockptrs[0] & ~CRAMFS_BLK_FLAGS;
	i = 0;
	करो अणु
		u32 block_off = i * (PAGE_SIZE >> CRAMFS_BLK_सूचीECT_PTR_SHIFT);
		u32 expect = (first_block_addr + block_off) |
			     CRAMFS_BLK_FLAG_सूचीECT_PTR |
			     CRAMFS_BLK_FLAG_UNCOMPRESSED;
		अगर (blockptrs[i] != expect) अणु
			pr_debug("range: block %d/%d got %#x expects %#x\n",
				 pgoff+i, pgoff + *pages - 1,
				 blockptrs[i], expect);
			अगर (i == 0)
				वापस 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (++i < *pages);

	*pages = i;
	वापस first_block_addr << CRAMFS_BLK_सूचीECT_PTR_SHIFT;
पूर्ण

#अगर_घोषित CONFIG_MMU

/*
 * Return true अगर the last page of a file in the fileप्रणाली image contains
 * some other data that करोesn't beदीर्घ to that file. It is assumed that the
 * last block is CRAMFS_BLK_FLAG_सूचीECT_PTR | CRAMFS_BLK_FLAG_UNCOMPRESSED
 * (verअगरied by cramfs_get_block_range() and directly accessible in memory.
 */
अटल bool cramfs_last_page_is_shared(काष्ठा inode *inode)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(inode->i_sb);
	u32 partial, last_page, blockaddr, *blockptrs;
	अक्षर *tail_data;

	partial = offset_in_page(inode->i_size);
	अगर (!partial)
		वापस false;
	last_page = inode->i_size >> PAGE_SHIFT;
	blockptrs = (u32 *)(sbi->linear_virt_addr + OFFSET(inode));
	blockaddr = blockptrs[last_page] & ~CRAMFS_BLK_FLAGS;
	blockaddr <<= CRAMFS_BLK_सूचीECT_PTR_SHIFT;
	tail_data = sbi->linear_virt_addr + blockaddr + partial;
	वापस स_प्रथम_inv(tail_data, 0, PAGE_SIZE - partial) ? true : false;
पूर्ण

अटल पूर्णांक cramfs_physmem_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(inode->i_sb);
	अचिन्हित पूर्णांक pages, max_pages, offset;
	अचिन्हित दीर्घ address, pgoff = vma->vm_pgoff;
	अक्षर *bailout_reason;
	पूर्णांक ret;

	ret = generic_file_पढ़ोonly_mmap(file, vma);
	अगर (ret)
		वापस ret;

	/*
	 * Now try to pre-populate ptes क्रम this vma with a direct
	 * mapping aव्योमing memory allocation when possible.
	 */

	/* Could COW work here? */
	bailout_reason = "vma is writable";
	अगर (vma->vm_flags & VM_WRITE)
		जाओ bailout;

	max_pages = (inode->i_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	bailout_reason = "beyond file limit";
	अगर (pgoff >= max_pages)
		जाओ bailout;
	pages = min(vma_pages(vma), max_pages - pgoff);

	offset = cramfs_get_block_range(inode, pgoff, &pages);
	bailout_reason = "unsuitable block layout";
	अगर (!offset)
		जाओ bailout;
	address = sbi->linear_phys_addr + offset;
	bailout_reason = "data is not page aligned";
	अगर (!PAGE_ALIGNED(address))
		जाओ bailout;

	/* Don't map the last page अगर it contains some other data */
	अगर (pgoff + pages == max_pages && cramfs_last_page_is_shared(inode)) अणु
		pr_debug("mmap: %pD: last page is shared\n", file);
		pages--;
	पूर्ण

	अगर (!pages) अणु
		bailout_reason = "no suitable block remaining";
		जाओ bailout;
	पूर्ण

	अगर (pages == vma_pages(vma)) अणु
		/*
		 * The entire vma is mappable. remap_pfn_range() will
		 * make it distinguishable from a non-direct mapping
		 * in /proc/<pid>/maps by substituting the file offset
		 * with the actual physical address.
		 */
		ret = remap_pfn_range(vma, vma->vm_start, address >> PAGE_SHIFT,
				      pages * PAGE_SIZE, vma->vm_page_prot);
	पूर्ण अन्यथा अणु
		/*
		 * Let's create a mixed map if we can't map it all.
		 * The normal paging machinery will take care of the
		 * unpopulated ptes via cramfs_पढ़ोpage().
		 */
		पूर्णांक i;
		vma->vm_flags |= VM_MIXEDMAP;
		क्रम (i = 0; i < pages && !ret; i++) अणु
			vm_fault_t vmf;
			अचिन्हित दीर्घ off = i * PAGE_SIZE;
			pfn_t pfn = phys_to_pfn_t(address + off, PFN_DEV);
			vmf = vmf_insert_mixed(vma, vma->vm_start + off, pfn);
			अगर (vmf & VM_FAULT_ERROR)
				ret = vm_fault_to_त्रुटि_सं(vmf, 0);
		पूर्ण
	पूर्ण

	अगर (!ret)
		pr_debug("mapped %pD[%lu] at 0x%08lx (%u/%lu pages) "
			 "to vma 0x%08lx, page_prot 0x%llx\n", file,
			 pgoff, address, pages, vma_pages(vma), vma->vm_start,
			 (अचिन्हित दीर्घ दीर्घ)pgprot_val(vma->vm_page_prot));
	वापस ret;

bailout:
	pr_debug("%pD[%lu]: direct mmap impossible: %s\n",
		 file, pgoff, bailout_reason);
	/* Didn't manage any direct map, but normal paging is still possible */
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_MMU */

अटल पूर्णांक cramfs_physmem_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & (VM_SHARED | VM_MAYSHARE) ? 0 : -ENOSYS;
पूर्ण

अटल अचिन्हित दीर्घ cramfs_physmem_get_unmapped_area(काष्ठा file *file,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(sb);
	अचिन्हित पूर्णांक pages, block_pages, max_pages, offset;

	pages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	max_pages = (inode->i_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अगर (pgoff >= max_pages || pages > max_pages - pgoff)
		वापस -EINVAL;
	block_pages = pages;
	offset = cramfs_get_block_range(inode, pgoff, &block_pages);
	अगर (!offset || block_pages != pages)
		वापस -ENOSYS;
	addr = sbi->linear_phys_addr + offset;
	pr_debug("get_unmapped for %pD ofs %#lx siz %lu at 0x%08lx\n",
		 file, pgoff*PAGE_SIZE, len, addr);
	वापस addr;
पूर्ण

अटल अचिन्हित पूर्णांक cramfs_physmem_mmap_capabilities(काष्ठा file *file)
अणु
	वापस NOMMU_MAP_COPY | NOMMU_MAP_सूचीECT |
	       NOMMU_MAP_READ | NOMMU_MAP_EXEC;
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

अटल स्थिर काष्ठा file_operations cramfs_physmem_fops = अणु
	.llseek			= generic_file_llseek,
	.पढ़ो_iter		= generic_file_पढ़ो_iter,
	.splice_पढ़ो		= generic_file_splice_पढ़ो,
	.mmap			= cramfs_physmem_mmap,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area	= cramfs_physmem_get_unmapped_area,
	.mmap_capabilities	= cramfs_physmem_mmap_capabilities,
#पूर्ण_अगर
पूर्ण;

अटल व्योम cramfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(sb);

	अगर (IS_ENABLED(CONFIG_CRAMFS_MTD) && sb->s_mtd) अणु
		अगर (sbi && sbi->mtd_poपूर्णांक_size)
			mtd_unpoपूर्णांक(sb->s_mtd, 0, sbi->mtd_poपूर्णांक_size);
		समाप्त_mtd_super(sb);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV) && sb->s_bdev) अणु
		समाप्त_block_super(sb);
	पूर्ण
	kमुक्त(sbi);
पूर्ण

अटल पूर्णांक cramfs_reconfigure(काष्ठा fs_context *fc)
अणु
	sync_fileप्रणाली(fc->root->d_sb);
	fc->sb_flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल पूर्णांक cramfs_पढ़ो_super(काष्ठा super_block *sb, काष्ठा fs_context *fc,
			     काष्ठा cramfs_super *super)
अणु
	काष्ठा cramfs_sb_info *sbi = CRAMFS_SB(sb);
	अचिन्हित दीर्घ root_offset;
	bool silent = fc->sb_flags & SB_SILENT;

	/* We करोn't know the real size yet */
	sbi->size = PAGE_SIZE;

	/* Read the first block and get the superblock from it */
	mutex_lock(&पढ़ो_mutex);
	स_नकल(super, cramfs_पढ़ो(sb, 0, माप(*super)), माप(*super));
	mutex_unlock(&पढ़ो_mutex);

	/* Do sanity checks on the superblock */
	अगर (super->magic != CRAMFS_MAGIC) अणु
		/* check क्रम wrong endianness */
		अगर (super->magic == CRAMFS_MAGIC_WEND) अणु
			अगर (!silent)
				errorfc(fc, "wrong endianness");
			वापस -EINVAL;
		पूर्ण

		/* check at 512 byte offset */
		mutex_lock(&पढ़ो_mutex);
		स_नकल(super,
		       cramfs_पढ़ो(sb, 512, माप(*super)),
		       माप(*super));
		mutex_unlock(&पढ़ो_mutex);
		अगर (super->magic != CRAMFS_MAGIC) अणु
			अगर (super->magic == CRAMFS_MAGIC_WEND && !silent)
				errorfc(fc, "wrong endianness");
			अन्यथा अगर (!silent)
				errorfc(fc, "wrong magic");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* get feature flags first */
	अगर (super->flags & ~CRAMFS_SUPPORTED_FLAGS) अणु
		errorfc(fc, "unsupported filesystem features");
		वापस -EINVAL;
	पूर्ण

	/* Check that the root inode is in a sane state */
	अगर (!S_ISसूची(super->root.mode)) अणु
		errorfc(fc, "root is not a directory");
		वापस -EINVAL;
	पूर्ण
	/* correct strange, hard-coded permissions of mkcramfs */
	super->root.mode |= 0555;

	root_offset = super->root.offset << 2;
	अगर (super->flags & CRAMFS_FLAG_FSID_VERSION_2) अणु
		sbi->size = super->size;
		sbi->blocks = super->fsid.blocks;
		sbi->files = super->fsid.files;
	पूर्ण अन्यथा अणु
		sbi->size = 1<<28;
		sbi->blocks = 0;
		sbi->files = 0;
	पूर्ण
	sbi->magic = super->magic;
	sbi->flags = super->flags;
	अगर (root_offset == 0)
		infofc(fc, "empty filesystem");
	अन्यथा अगर (!(super->flags & CRAMFS_FLAG_SHIFTED_ROOT_OFFSET) &&
		 ((root_offset != माप(काष्ठा cramfs_super)) &&
		  (root_offset != 512 + माप(काष्ठा cramfs_super))))
	अणु
		errorfc(fc, "bad root offset %lu", root_offset);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cramfs_finalize_super(काष्ठा super_block *sb,
				 काष्ठा cramfs_inode *cramfs_root)
अणु
	काष्ठा inode *root;

	/* Set it all up.. */
	sb->s_flags |= SB_RDONLY;
	sb->s_समय_min = 0;
	sb->s_समय_max = 0;
	sb->s_op = &cramfs_ops;
	root = get_cramfs_inode(sb, cramfs_root, 0);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक cramfs_blkdev_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा cramfs_sb_info *sbi;
	काष्ठा cramfs_super super;
	पूर्णांक i, err;

	sbi = kzalloc(माप(काष्ठा cramfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	sb->s_fs_info = sbi;

	/* Invalidate the पढ़ो buffers on mount: think disk change.. */
	क्रम (i = 0; i < READ_BUFFERS; i++)
		buffer_blocknr[i] = -1;

	err = cramfs_पढ़ो_super(sb, fc, &super);
	अगर (err)
		वापस err;
	वापस cramfs_finalize_super(sb, &super.root);
पूर्ण

अटल पूर्णांक cramfs_mtd_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा cramfs_sb_info *sbi;
	काष्ठा cramfs_super super;
	पूर्णांक err;

	sbi = kzalloc(माप(काष्ठा cramfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	sb->s_fs_info = sbi;

	/* Map only one page क्रम now.  Will remap it when fs size is known. */
	err = mtd_poपूर्णांक(sb->s_mtd, 0, PAGE_SIZE, &sbi->mtd_poपूर्णांक_size,
			&sbi->linear_virt_addr, &sbi->linear_phys_addr);
	अगर (err || sbi->mtd_poपूर्णांक_size != PAGE_SIZE) अणु
		pr_err("unable to get direct memory access to mtd:%s\n",
		       sb->s_mtd->name);
		वापस err ? : -ENODATA;
	पूर्ण

	pr_info("checking physical address %pap for linear cramfs image\n",
		&sbi->linear_phys_addr);
	err = cramfs_पढ़ो_super(sb, fc, &super);
	अगर (err)
		वापस err;

	/* Remap the whole fileप्रणाली now */
	pr_info("linear cramfs image on mtd:%s appears to be %lu KB in size\n",
		sb->s_mtd->name, sbi->size/1024);
	mtd_unpoपूर्णांक(sb->s_mtd, 0, PAGE_SIZE);
	err = mtd_poपूर्णांक(sb->s_mtd, 0, sbi->size, &sbi->mtd_poपूर्णांक_size,
			&sbi->linear_virt_addr, &sbi->linear_phys_addr);
	अगर (err || sbi->mtd_poपूर्णांक_size != sbi->size) अणु
		pr_err("unable to get direct memory access to mtd:%s\n",
		       sb->s_mtd->name);
		वापस err ? : -ENODATA;
	पूर्ण

	वापस cramfs_finalize_super(sb, &super.root);
पूर्ण

अटल पूर्णांक cramfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = 0;

	अगर (sb->s_bdev)
		id = huge_encode_dev(sb->s_bdev->bd_dev);
	अन्यथा अगर (sb->s_dev)
		id = huge_encode_dev(sb->s_dev);

	buf->f_type = CRAMFS_MAGIC;
	buf->f_bsize = PAGE_SIZE;
	buf->f_blocks = CRAMFS_SB(sb)->blocks;
	buf->f_bमुक्त = 0;
	buf->f_bavail = 0;
	buf->f_files = CRAMFS_SB(sb)->files;
	buf->f_fमुक्त = 0;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = CRAMFS_MAXPATHLEN;
	वापस 0;
पूर्ण

/*
 * Read a cramfs directory entry.
 */
अटल पूर्णांक cramfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	अक्षर *buf;
	अचिन्हित पूर्णांक offset;

	/* Offset within the thing. */
	अगर (ctx->pos >= inode->i_size)
		वापस 0;
	offset = ctx->pos;
	/* Directory entries are always 4-byte aligned */
	अगर (offset & 3)
		वापस -EINVAL;

	buf = kदो_स्मृति(CRAMFS_MAXPATHLEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (offset < inode->i_size) अणु
		काष्ठा cramfs_inode *de;
		अचिन्हित दीर्घ nextoffset;
		अक्षर *name;
		ino_t ino;
		umode_t mode;
		पूर्णांक namelen;

		mutex_lock(&पढ़ो_mutex);
		de = cramfs_पढ़ो(sb, OFFSET(inode) + offset, माप(*de)+CRAMFS_MAXPATHLEN);
		name = (अक्षर *)(de+1);

		/*
		 * Namelengths on disk are shअगरted by two
		 * and the name padded out to 4-byte boundaries
		 * with zeroes.
		 */
		namelen = de->namelen << 2;
		स_नकल(buf, name, namelen);
		ino = cramino(de, OFFSET(inode) + offset);
		mode = de->mode;
		mutex_unlock(&पढ़ो_mutex);
		nextoffset = offset + माप(*de) + namelen;
		क्रम (;;) अणु
			अगर (!namelen) अणु
				kमुक्त(buf);
				वापस -EIO;
			पूर्ण
			अगर (buf[namelen-1])
				अवरोध;
			namelen--;
		पूर्ण
		अगर (!dir_emit(ctx, buf, namelen, ino, mode >> 12))
			अवरोध;

		ctx->pos = offset = nextoffset;
	पूर्ण
	kमुक्त(buf);
	वापस 0;
पूर्ण

/*
 * Lookup and fill in the inode data..
 */
अटल काष्ठा dentry *cramfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा inode *inode = शून्य;
	पूर्णांक sorted;

	mutex_lock(&पढ़ो_mutex);
	sorted = CRAMFS_SB(dir->i_sb)->flags & CRAMFS_FLAG_SORTED_सूचीS;
	जबतक (offset < dir->i_size) अणु
		काष्ठा cramfs_inode *de;
		अक्षर *name;
		पूर्णांक namelen, retval;
		पूर्णांक dir_off = OFFSET(dir) + offset;

		de = cramfs_पढ़ो(dir->i_sb, dir_off, माप(*de)+CRAMFS_MAXPATHLEN);
		name = (अक्षर *)(de+1);

		/* Try to take advantage of sorted directories */
		अगर (sorted && (dentry->d_name.name[0] < name[0]))
			अवरोध;

		namelen = de->namelen << 2;
		offset += माप(*de) + namelen;

		/* Quick check that the name is roughly the right length */
		अगर (((dentry->d_name.len + 3) & ~3) != namelen)
			जारी;

		क्रम (;;) अणु
			अगर (!namelen) अणु
				inode = ERR_PTR(-EIO);
				जाओ out;
			पूर्ण
			अगर (name[namelen-1])
				अवरोध;
			namelen--;
		पूर्ण
		अगर (namelen != dentry->d_name.len)
			जारी;
		retval = स_भेद(dentry->d_name.name, name, namelen);
		अगर (retval > 0)
			जारी;
		अगर (!retval) अणु
			inode = get_cramfs_inode(dir->i_sb, de, dir_off);
			अवरोध;
		पूर्ण
		/* अन्यथा (retval < 0) */
		अगर (sorted)
			अवरोध;
	पूर्ण
out:
	mutex_unlock(&पढ़ो_mutex);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक cramfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	u32 maxblock;
	पूर्णांक bytes_filled;
	व्योम *pgdata;

	maxblock = (inode->i_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	bytes_filled = 0;
	pgdata = kmap(page);

	अगर (page->index < maxblock) अणु
		काष्ठा super_block *sb = inode->i_sb;
		u32 blkptr_offset = OFFSET(inode) + page->index * 4;
		u32 block_ptr, block_start, block_len;
		bool uncompressed, direct;

		mutex_lock(&पढ़ो_mutex);
		block_ptr = *(u32 *) cramfs_पढ़ो(sb, blkptr_offset, 4);
		uncompressed = (block_ptr & CRAMFS_BLK_FLAG_UNCOMPRESSED);
		direct = (block_ptr & CRAMFS_BLK_FLAG_सूचीECT_PTR);
		block_ptr &= ~CRAMFS_BLK_FLAGS;

		अगर (direct) अणु
			/*
			 * The block poपूर्णांकer is an असलolute start poपूर्णांकer,
			 * shअगरted by 2 bits. The size is included in the
			 * first 2 bytes of the data block when compressed,
			 * or PAGE_SIZE otherwise.
			 */
			block_start = block_ptr << CRAMFS_BLK_सूचीECT_PTR_SHIFT;
			अगर (uncompressed) अणु
				block_len = PAGE_SIZE;
				/* अगर last block: cap to file length */
				अगर (page->index == maxblock - 1)
					block_len =
						offset_in_page(inode->i_size);
			पूर्ण अन्यथा अणु
				block_len = *(u16 *)
					cramfs_पढ़ो(sb, block_start, 2);
				block_start += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * The block poपूर्णांकer indicates one past the end of
			 * the current block (start of next block). If this
			 * is the first block then it starts where the block
			 * poपूर्णांकer table ends, otherwise its start comes
			 * from the previous block's poपूर्णांकer.
			 */
			block_start = OFFSET(inode) + maxblock * 4;
			अगर (page->index)
				block_start = *(u32 *)
					cramfs_पढ़ो(sb, blkptr_offset - 4, 4);
			/* Beware... previous ptr might be a direct ptr */
			अगर (unlikely(block_start & CRAMFS_BLK_FLAG_सूचीECT_PTR)) अणु
				/* See comments on earlier code. */
				u32 prev_start = block_start;
				block_start = prev_start & ~CRAMFS_BLK_FLAGS;
				block_start <<= CRAMFS_BLK_सूचीECT_PTR_SHIFT;
				अगर (prev_start & CRAMFS_BLK_FLAG_UNCOMPRESSED) अणु
					block_start += PAGE_SIZE;
				पूर्ण अन्यथा अणु
					block_len = *(u16 *)
						cramfs_पढ़ो(sb, block_start, 2);
					block_start += 2 + block_len;
				पूर्ण
			पूर्ण
			block_start &= ~CRAMFS_BLK_FLAGS;
			block_len = block_ptr - block_start;
		पूर्ण

		अगर (block_len == 0)
			; /* hole */
		अन्यथा अगर (unlikely(block_len > 2*PAGE_SIZE ||
				  (uncompressed && block_len > PAGE_SIZE))) अणु
			mutex_unlock(&पढ़ो_mutex);
			pr_err("bad data blocksize %u\n", block_len);
			जाओ err;
		पूर्ण अन्यथा अगर (uncompressed) अणु
			स_नकल(pgdata,
			       cramfs_पढ़ो(sb, block_start, block_len),
			       block_len);
			bytes_filled = block_len;
		पूर्ण अन्यथा अणु
			bytes_filled = cramfs_uncompress_block(pgdata,
				 PAGE_SIZE,
				 cramfs_पढ़ो(sb, block_start, block_len),
				 block_len);
		पूर्ण
		mutex_unlock(&पढ़ो_mutex);
		अगर (unlikely(bytes_filled < 0))
			जाओ err;
	पूर्ण

	स_रखो(pgdata + bytes_filled, 0, PAGE_SIZE - bytes_filled);
	flush_dcache_page(page);
	kunmap(page);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

err:
	kunmap(page);
	ClearPageUptodate(page);
	SetPageError(page);
	unlock_page(page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा address_space_operations cramfs_aops = अणु
	.पढ़ोpage = cramfs_पढ़ोpage
पूर्ण;

/*
 * Our operations:
 */

/*
 * A directory can only सूची_पढ़ो
 */
अटल स्थिर काष्ठा file_operations cramfs_directory_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= cramfs_सूची_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा inode_operations cramfs_dir_inode_operations = अणु
	.lookup		= cramfs_lookup,
पूर्ण;

अटल स्थिर काष्ठा super_operations cramfs_ops = अणु
	.statfs		= cramfs_statfs,
पूर्ण;

अटल पूर्णांक cramfs_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक ret = -ENOPROTOOPT;

	अगर (IS_ENABLED(CONFIG_CRAMFS_MTD)) अणु
		ret = get_tree_mtd(fc, cramfs_mtd_fill_super);
		अगर (!ret)
			वापस 0;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV))
		ret = get_tree_bdev(fc, cramfs_blkdev_fill_super);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fs_context_operations cramfs_context_ops = अणु
	.get_tree	= cramfs_get_tree,
	.reconfigure	= cramfs_reconfigure,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक cramfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &cramfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type cramfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "cramfs",
	.init_fs_context = cramfs_init_fs_context,
	.समाप्त_sb	= cramfs_समाप्त_sb,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("cramfs");

अटल पूर्णांक __init init_cramfs_fs(व्योम)
अणु
	पूर्णांक rv;

	rv = cramfs_uncompress_init();
	अगर (rv < 0)
		वापस rv;
	rv = रेजिस्टर_fileप्रणाली(&cramfs_fs_type);
	अगर (rv < 0)
		cramfs_uncompress_निकास();
	वापस rv;
पूर्ण

अटल व्योम __निकास निकास_cramfs_fs(व्योम)
अणु
	cramfs_uncompress_निकास();
	unरेजिस्टर_fileप्रणाली(&cramfs_fs_type);
पूर्ण

module_init(init_cramfs_fs)
module_निकास(निकास_cramfs_fs)
MODULE_LICENSE("GPL");
