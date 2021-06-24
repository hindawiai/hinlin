<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/fat/inode.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *  VFAT extensions by Gorकरोn Chaffee, merged with msकरोs fs by Henrik Storner
 *  Rewritten क्रम the स्थिरant inumbers support by Al Viro
 *
 *  Fixes:
 *
 *	Max Cohan: Fixed invalid FSINFO offset when info_sector is 0
 */

#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mpage.h>
#समावेश <linux/vfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/parser.h>
#समावेश <linux/uपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/iversion.h>
#समावेश "fat.h"

#अगर_अघोषित CONFIG_FAT_DEFAULT_IOCHARSET
/* अगर user करोn't select VFAT, this is undefined. */
#घोषणा CONFIG_FAT_DEFAULT_IOCHARSET	""
#पूर्ण_अगर

#घोषणा KB_IN_SECTORS 2

/* DOS dates from 1980/1/1 through 2107/12/31 */
#घोषणा FAT_DATE_MIN (0<<9 | 1<<5 | 1)
#घोषणा FAT_DATE_MAX (127<<9 | 12<<5 | 31)
#घोषणा FAT_TIME_MAX (23<<11 | 59<<5 | 29)

/*
 * A deserialized copy of the on-disk काष्ठाure laid out in काष्ठा
 * fat_boot_sector.
 */
काष्ठा fat_bios_param_block अणु
	u16	fat_sector_size;
	u8	fat_sec_per_clus;
	u16	fat_reserved;
	u8	fat_fats;
	u16	fat_dir_entries;
	u16	fat_sectors;
	u16	fat_fat_length;
	u32	fat_total_sect;

	u8	fat16_state;
	u32	fat16_vol_id;

	u32	fat32_length;
	u32	fat32_root_cluster;
	u16	fat32_info_sector;
	u8	fat32_state;
	u32	fat32_vol_id;
पूर्ण;

अटल पूर्णांक fat_शेष_codepage = CONFIG_FAT_DEFAULT_CODEPAGE;
अटल अक्षर fat_शेष_ioअक्षरset[] = CONFIG_FAT_DEFAULT_IOCHARSET;

अटल काष्ठा fat_floppy_शेषs अणु
	अचिन्हित nr_sectors;
	अचिन्हित sec_per_clus;
	अचिन्हित dir_entries;
	अचिन्हित media;
	अचिन्हित fat_length;
पूर्ण floppy_शेषs[] = अणु
अणु
	.nr_sectors = 160 * KB_IN_SECTORS,
	.sec_per_clus = 1,
	.dir_entries = 64,
	.media = 0xFE,
	.fat_length = 1,
पूर्ण,
अणु
	.nr_sectors = 180 * KB_IN_SECTORS,
	.sec_per_clus = 1,
	.dir_entries = 64,
	.media = 0xFC,
	.fat_length = 2,
पूर्ण,
अणु
	.nr_sectors = 320 * KB_IN_SECTORS,
	.sec_per_clus = 2,
	.dir_entries = 112,
	.media = 0xFF,
	.fat_length = 1,
पूर्ण,
अणु
	.nr_sectors = 360 * KB_IN_SECTORS,
	.sec_per_clus = 2,
	.dir_entries = 112,
	.media = 0xFD,
	.fat_length = 2,
पूर्ण,
पूर्ण;

पूर्णांक fat_add_cluster(काष्ठा inode *inode)
अणु
	पूर्णांक err, cluster;

	err = fat_alloc_clusters(inode, &cluster, 1);
	अगर (err)
		वापस err;
	/* FIXME: this cluster should be added after data of this
	 * cluster is ग_लिखोd */
	err = fat_chain_add(inode, cluster, 1);
	अगर (err)
		fat_मुक्त_clusters(inode, cluster);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक __fat_get_block(काष्ठा inode *inode, sector_t iblock,
				  अचिन्हित दीर्घ *max_blocks,
				  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	अचिन्हित दीर्घ mapped_blocks;
	sector_t phys, last_block;
	पूर्णांक err, offset;

	err = fat_bmap(inode, iblock, &phys, &mapped_blocks, create, false);
	अगर (err)
		वापस err;
	अगर (phys) अणु
		map_bh(bh_result, sb, phys);
		*max_blocks = min(mapped_blocks, *max_blocks);
		वापस 0;
	पूर्ण
	अगर (!create)
		वापस 0;

	अगर (iblock != MSDOS_I(inode)->mmu_निजी >> sb->s_blocksize_bits) अणु
		fat_fs_error(sb, "corrupted file size (i_pos %lld, %lld)",
			MSDOS_I(inode)->i_pos, MSDOS_I(inode)->mmu_निजी);
		वापस -EIO;
	पूर्ण

	last_block = inode->i_blocks >> (sb->s_blocksize_bits - 9);
	offset = (अचिन्हित दीर्घ)iblock & (sbi->sec_per_clus - 1);
	/*
	 * allocate a cluster according to the following.
	 * 1) no more available blocks
	 * 2) not part of fallocate region
	 */
	अगर (!offset && !(iblock < last_block)) अणु
		/* TODO: multiple cluster allocation would be desirable. */
		err = fat_add_cluster(inode);
		अगर (err)
			वापस err;
	पूर्ण
	/* available blocks on this cluster */
	mapped_blocks = sbi->sec_per_clus - offset;

	*max_blocks = min(mapped_blocks, *max_blocks);
	MSDOS_I(inode)->mmu_निजी += *max_blocks << sb->s_blocksize_bits;

	err = fat_bmap(inode, iblock, &phys, &mapped_blocks, create, false);
	अगर (err)
		वापस err;
	अगर (!phys) अणु
		fat_fs_error(sb,
			     "invalid FAT chain (i_pos %lld, last_block %llu)",
			     MSDOS_I(inode)->i_pos,
			     (अचिन्हित दीर्घ दीर्घ)last_block);
		वापस -EIO;
	पूर्ण

	BUG_ON(*max_blocks != mapped_blocks);
	set_buffer_new(bh_result);
	map_bh(bh_result, sb, phys);

	वापस 0;
पूर्ण

अटल पूर्णांक fat_get_block(काष्ठा inode *inode, sector_t iblock,
			 काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ max_blocks = bh_result->b_size >> inode->i_blkbits;
	पूर्णांक err;

	err = __fat_get_block(inode, iblock, &max_blocks, bh_result, create);
	अगर (err)
		वापस err;
	bh_result->b_size = max_blocks << sb->s_blocksize_bits;
	वापस 0;
पूर्ण

अटल पूर्णांक fat_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, fat_get_block, wbc);
पूर्ण

अटल पूर्णांक fat_ग_लिखोpages(काष्ठा address_space *mapping,
			  काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, fat_get_block);
पूर्ण

अटल पूर्णांक fat_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, fat_get_block);
पूर्ण

अटल व्योम fat_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, fat_get_block);
पूर्ण

अटल व्योम fat_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		fat_truncate_blocks(inode, inode->i_size);
	पूर्ण
पूर्ण

अटल पूर्णांक fat_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक err;

	*pagep = शून्य;
	err = cont_ग_लिखो_begin(file, mapping, pos, len, flags,
				pagep, fsdata, fat_get_block,
				&MSDOS_I(mapping->host)->mmu_निजी);
	अगर (err < 0)
		fat_ग_लिखो_failed(mapping, pos + len);
	वापस err;
पूर्ण

अटल पूर्णांक fat_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *pagep, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक err;
	err = generic_ग_लिखो_end(file, mapping, pos, len, copied, pagep, fsdata);
	अगर (err < len)
		fat_ग_लिखो_failed(mapping, pos + len);
	अगर (!(err < 0) && !(MSDOS_I(inode)->i_attrs & ATTR_ARCH)) अणु
		fat_truncate_समय(inode, शून्य, S_CTIME|S_MTIME);
		MSDOS_I(inode)->i_attrs |= ATTR_ARCH;
		mark_inode_dirty(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल sमाप_प्रकार fat_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	sमाप_प्रकार ret;

	अगर (iov_iter_rw(iter) == WRITE) अणु
		/*
		 * FIXME: blockdev_direct_IO() करोesn't use ->ग_लिखो_begin(),
		 * so we need to update the ->mmu_निजी to block boundary.
		 *
		 * But we must fill the reमुख्यing area or hole by nul क्रम
		 * updating ->mmu_निजी.
		 *
		 * Return 0, and fallback to normal buffered ग_लिखो.
		 */
		loff_t size = offset + count;
		अगर (MSDOS_I(inode)->mmu_निजी < size)
			वापस 0;
	पूर्ण

	/*
	 * FAT need to use the DIO_LOCKING क्रम aव्योमing the race
	 * condition of fat_get_block() and ->truncate().
	 */
	ret = blockdev_direct_IO(iocb, inode, iter, fat_get_block);
	अगर (ret < 0 && iov_iter_rw(iter) == WRITE)
		fat_ग_लिखो_failed(mapping, offset + count);

	वापस ret;
पूर्ण

अटल पूर्णांक fat_get_block_bmap(काष्ठा inode *inode, sector_t iblock,
		काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ max_blocks = bh_result->b_size >> inode->i_blkbits;
	पूर्णांक err;
	sector_t bmap;
	अचिन्हित दीर्घ mapped_blocks;

	BUG_ON(create != 0);

	err = fat_bmap(inode, iblock, &bmap, &mapped_blocks, create, true);
	अगर (err)
		वापस err;

	अगर (bmap) अणु
		map_bh(bh_result, sb, bmap);
		max_blocks = min(mapped_blocks, max_blocks);
	पूर्ण

	bh_result->b_size = max_blocks << sb->s_blocksize_bits;

	वापस 0;
पूर्ण

अटल sector_t _fat_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	sector_t blocknr;

	/* fat_get_cluster() assumes the requested blocknr isn't truncated. */
	करोwn_पढ़ो(&MSDOS_I(mapping->host)->truncate_lock);
	blocknr = generic_block_bmap(mapping, block, fat_get_block_bmap);
	up_पढ़ो(&MSDOS_I(mapping->host)->truncate_lock);

	वापस blocknr;
पूर्ण

/*
 * fat_block_truncate_page() zeroes out a mapping from file offset `from'
 * up to the end of the block which corresponds to `from'.
 * This is required during truncate to physically zeroout the tail end
 * of that block so it करोesn't yield old data अगर the file is later grown.
 * Also, aव्योम causing failure from fsx क्रम हालs of "data past EOF"
 */
पूर्णांक fat_block_truncate_page(काष्ठा inode *inode, loff_t from)
अणु
	वापस block_truncate_page(inode->i_mapping, from, fat_get_block);
पूर्ण

अटल स्थिर काष्ठा address_space_operations fat_aops = अणु
	.पढ़ोpage	= fat_पढ़ोpage,
	.पढ़ोahead	= fat_पढ़ोahead,
	.ग_लिखोpage	= fat_ग_लिखोpage,
	.ग_लिखोpages	= fat_ग_लिखोpages,
	.ग_लिखो_begin	= fat_ग_लिखो_begin,
	.ग_लिखो_end	= fat_ग_लिखो_end,
	.direct_IO	= fat_direct_IO,
	.bmap		= _fat_bmap
पूर्ण;

/*
 * New FAT inode stuff. We करो the following:
 *	a) i_ino is स्थिरant and has nothing with on-disk location.
 *	b) FAT manages its own cache of directory entries.
 *	c) *This* cache is indexed by on-disk location.
 *	d) inode has an associated directory entry, all right, but
 *		it may be unhashed.
 *	e) currently entries are stored within काष्ठा inode. That should
 *		change.
 *	f) we deal with races in the following way:
 *		1. सूची_पढ़ो() and lookup() करो FAT-dir-cache lookup.
 *		2. नाम() unhashes the F-d-c entry and rehashes it in
 *			a new place.
 *		3. unlink() and सूची_हटाओ() unhash F-d-c entry.
 *		4. fat_ग_लिखो_inode() checks whether the thing is unhashed.
 *			If it is we silently वापस. If it isn't we करो bपढ़ो(),
 *			check अगर the location is still valid and retry अगर it
 *			isn't. Otherwise we करो changes.
 *		5. Spinlock is used to protect hash/unhash/location check/lookup
 *		6. fat_evict_inode() unhashes the F-d-c entry.
 *		7. lookup() and सूची_पढ़ो() करो igrab() अगर they find a F-d-c entry
 *			and consider negative result as cache miss.
 */

अटल व्योम fat_hash_init(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक i;

	spin_lock_init(&sbi->inode_hash_lock);
	क्रम (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&sbi->inode_hashtable[i]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fat_hash(loff_t i_pos)
अणु
	वापस hash_32(i_pos, FAT_HASH_BITS);
पूर्ण

अटल व्योम dir_hash_init(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक i;

	spin_lock_init(&sbi->dir_hash_lock);
	क्रम (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&sbi->dir_hashtable[i]);
पूर्ण

व्योम fat_attach(काष्ठा inode *inode, loff_t i_pos)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);

	अगर (inode->i_ino != MSDOS_ROOT_INO) अणु
		काष्ठा hlist_head *head =   sbi->inode_hashtable
					  + fat_hash(i_pos);

		spin_lock(&sbi->inode_hash_lock);
		MSDOS_I(inode)->i_pos = i_pos;
		hlist_add_head(&MSDOS_I(inode)->i_fat_hash, head);
		spin_unlock(&sbi->inode_hash_lock);
	पूर्ण

	/* If NFS support is enabled, cache the mapping of start cluster
	 * to directory inode. This is used during reconnection of
	 * dentries to the fileप्रणाली root.
	 */
	अगर (S_ISसूची(inode->i_mode) && sbi->options.nfs) अणु
		काष्ठा hlist_head *d_head = sbi->dir_hashtable;
		d_head += fat_dir_hash(MSDOS_I(inode)->i_logstart);

		spin_lock(&sbi->dir_hash_lock);
		hlist_add_head(&MSDOS_I(inode)->i_dir_hash, d_head);
		spin_unlock(&sbi->dir_hash_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fat_attach);

व्योम fat_detach(काष्ठा inode *inode)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	spin_lock(&sbi->inode_hash_lock);
	MSDOS_I(inode)->i_pos = 0;
	hlist_del_init(&MSDOS_I(inode)->i_fat_hash);
	spin_unlock(&sbi->inode_hash_lock);

	अगर (S_ISसूची(inode->i_mode) && sbi->options.nfs) अणु
		spin_lock(&sbi->dir_hash_lock);
		hlist_del_init(&MSDOS_I(inode)->i_dir_hash);
		spin_unlock(&sbi->dir_hash_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fat_detach);

काष्ठा inode *fat_iget(काष्ठा super_block *sb, loff_t i_pos)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा hlist_head *head = sbi->inode_hashtable + fat_hash(i_pos);
	काष्ठा msकरोs_inode_info *i;
	काष्ठा inode *inode = शून्य;

	spin_lock(&sbi->inode_hash_lock);
	hlist_क्रम_each_entry(i, head, i_fat_hash) अणु
		BUG_ON(i->vfs_inode.i_sb != sb);
		अगर (i->i_pos != i_pos)
			जारी;
		inode = igrab(&i->vfs_inode);
		अगर (inode)
			अवरोध;
	पूर्ण
	spin_unlock(&sbi->inode_hash_lock);
	वापस inode;
पूर्ण

अटल पूर्णांक is_exec(अचिन्हित अक्षर *extension)
अणु
	अचिन्हित अक्षर exe_extensions[] = "EXECOMBAT", *walk;

	क्रम (walk = exe_extensions; *walk; walk += 3)
		अगर (!म_भेदन(extension, walk, 3))
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक fat_calc_dir_size(काष्ठा inode *inode)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	पूर्णांक ret, fclus, dclus;

	inode->i_size = 0;
	अगर (MSDOS_I(inode)->i_start == 0)
		वापस 0;

	ret = fat_get_cluster(inode, FAT_ENT_खातापूर्ण, &fclus, &dclus);
	अगर (ret < 0)
		वापस ret;
	inode->i_size = (fclus + 1) << sbi->cluster_bits;

	वापस 0;
पूर्ण

अटल पूर्णांक fat_validate_dir(काष्ठा inode *dir)
अणु
	काष्ठा super_block *sb = dir->i_sb;

	अगर (dir->i_nlink < 2) अणु
		/* Directory should have "."/".." entries at least. */
		fat_fs_error(sb, "corrupted directory (invalid entries)");
		वापस -EIO;
	पूर्ण
	अगर (MSDOS_I(dir)->i_start == 0 ||
	    MSDOS_I(dir)->i_start == MSDOS_SB(sb)->root_cluster) अणु
		/* Directory should poपूर्णांक valid cluster. */
		fat_fs_error(sb, "corrupted directory (invalid i_start)");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* करोesn't deal with root inode */
पूर्णांक fat_fill_inode(काष्ठा inode *inode, काष्ठा msकरोs_dir_entry *de)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	पूर्णांक error;

	MSDOS_I(inode)->i_pos = 0;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_iversion(inode);
	inode->i_generation = pअक्रमom_u32();

	अगर ((de->attr & ATTR_सूची) && !IS_FREE(de->name)) अणु
		inode->i_generation &= ~1;
		inode->i_mode = fat_make_mode(sbi, de->attr, S_IRWXUGO);
		inode->i_op = sbi->dir_ops;
		inode->i_fop = &fat_dir_operations;

		MSDOS_I(inode)->i_start = fat_get_start(sbi, de);
		MSDOS_I(inode)->i_logstart = MSDOS_I(inode)->i_start;
		error = fat_calc_dir_size(inode);
		अगर (error < 0)
			वापस error;
		MSDOS_I(inode)->mmu_निजी = inode->i_size;

		set_nlink(inode, fat_subdirs(inode));

		error = fat_validate_dir(inode);
		अगर (error < 0)
			वापस error;
	पूर्ण अन्यथा अणु /* not a directory */
		inode->i_generation |= 1;
		inode->i_mode = fat_make_mode(sbi, de->attr,
			((sbi->options.showexec && !is_exec(de->name + 8))
			 ? S_IRUGO|S_IWUGO : S_IRWXUGO));
		MSDOS_I(inode)->i_start = fat_get_start(sbi, de);

		MSDOS_I(inode)->i_logstart = MSDOS_I(inode)->i_start;
		inode->i_size = le32_to_cpu(de->size);
		inode->i_op = &fat_file_inode_operations;
		inode->i_fop = &fat_file_operations;
		inode->i_mapping->a_ops = &fat_aops;
		MSDOS_I(inode)->mmu_निजी = inode->i_size;
	पूर्ण
	अगर (de->attr & ATTR_SYS) अणु
		अगर (sbi->options.sys_immutable)
			inode->i_flags |= S_IMMUTABLE;
	पूर्ण
	fat_save_attrs(inode, de->attr);

	inode->i_blocks = ((inode->i_size + (sbi->cluster_size - 1))
			   & ~((loff_t)sbi->cluster_size - 1)) >> 9;

	fat_समय_fat2unix(sbi, &inode->i_mसमय, de->समय, de->date, 0);
	अगर (sbi->options.isvfat) अणु
		fat_समय_fat2unix(sbi, &inode->i_स_समय, de->स_समय,
				  de->cdate, de->स_समय_cs);
		fat_समय_fat2unix(sbi, &inode->i_aसमय, 0, de->adate, 0);
	पूर्ण अन्यथा
		fat_truncate_समय(inode, &inode->i_mसमय, S_ATIME|S_CTIME);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fat_lock_build_inode(काष्ठा msकरोs_sb_info *sbi)
अणु
	अगर (sbi->options.nfs == FAT_NFS_NOSTALE_RO)
		mutex_lock(&sbi->nfs_build_inode_lock);
पूर्ण

अटल अंतरभूत व्योम fat_unlock_build_inode(काष्ठा msकरोs_sb_info *sbi)
अणु
	अगर (sbi->options.nfs == FAT_NFS_NOSTALE_RO)
		mutex_unlock(&sbi->nfs_build_inode_lock);
पूर्ण

काष्ठा inode *fat_build_inode(काष्ठा super_block *sb,
			काष्ठा msकरोs_dir_entry *de, loff_t i_pos)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	fat_lock_build_inode(MSDOS_SB(sb));
	inode = fat_iget(sb, i_pos);
	अगर (inode)
		जाओ out;
	inode = new_inode(sb);
	अगर (!inode) अणु
		inode = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	inode->i_ino = iunique(sb, MSDOS_ROOT_INO);
	inode_set_iversion(inode, 1);
	err = fat_fill_inode(inode, de);
	अगर (err) अणु
		iput(inode);
		inode = ERR_PTR(err);
		जाओ out;
	पूर्ण
	fat_attach(inode, i_pos);
	insert_inode_hash(inode);
out:
	fat_unlock_build_inode(MSDOS_SB(sb));
	वापस inode;
पूर्ण

EXPORT_SYMBOL_GPL(fat_build_inode);

अटल पूर्णांक __fat_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक रुको);

अटल व्योम fat_मुक्त_eofblocks(काष्ठा inode *inode)
अणु
	/* Release unwritten fallocated blocks on inode eviction. */
	अगर ((inode->i_blocks << 9) >
			round_up(MSDOS_I(inode)->mmu_निजी,
				MSDOS_SB(inode->i_sb)->cluster_size)) अणु
		पूर्णांक err;

		fat_truncate_blocks(inode, MSDOS_I(inode)->mmu_निजी);
		/* Fallocate results in updating the i_start/iogstart
		 * क्रम the zero byte file. So, make it वापस to
		 * original state during evict and commit it to aव्योम
		 * any corruption on the next access to the cluster
		 * chain क्रम the file.
		 */
		err = __fat_ग_लिखो_inode(inode, inode_needs_sync(inode));
		अगर (err) अणु
			fat_msg(inode->i_sb, KERN_WARNING, "Failed to "
					"update on disk inode for unused "
					"fallocated blocks, inode could be "
					"corrupted. Please run fsck");
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम fat_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	अगर (!inode->i_nlink) अणु
		inode->i_size = 0;
		fat_truncate_blocks(inode, 0);
	पूर्ण अन्यथा
		fat_मुक्त_eofblocks(inode);

	invalidate_inode_buffers(inode);
	clear_inode(inode);
	fat_cache_inval_inode(inode);
	fat_detach(inode);
पूर्ण

अटल व्योम fat_set_state(काष्ठा super_block *sb,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक क्रमce)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा fat_boot_sector *b;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	/* करो not change any thing अगर mounted पढ़ो only */
	अगर (sb_rकरोnly(sb) && !क्रमce)
		वापस;

	/* करो not change state अगर fs was dirty */
	अगर (sbi->dirty) अणु
		/* warn only on set (mount). */
		अगर (set)
			fat_msg(sb, KERN_WARNING, "Volume was not properly "
				"unmounted. Some data may be corrupt. "
				"Please run fsck.");
		वापस;
	पूर्ण

	bh = sb_bपढ़ो(sb, 0);
	अगर (bh == शून्य) अणु
		fat_msg(sb, KERN_ERR, "unable to read boot sector "
			"to mark fs as dirty");
		वापस;
	पूर्ण

	b = (काष्ठा fat_boot_sector *) bh->b_data;

	अगर (is_fat32(sbi)) अणु
		अगर (set)
			b->fat32.state |= FAT_STATE_सूचीTY;
		अन्यथा
			b->fat32.state &= ~FAT_STATE_सूचीTY;
	पूर्ण अन्यथा /* fat 16 and 12 */ अणु
		अगर (set)
			b->fat16.state |= FAT_STATE_सूचीTY;
		अन्यथा
			b->fat16.state &= ~FAT_STATE_सूचीTY;
	पूर्ण

	mark_buffer_dirty(bh);
	sync_dirty_buffer(bh);
	brअन्यथा(bh);
पूर्ण

अटल व्योम fat_reset_ioअक्षरset(काष्ठा fat_mount_options *opts)
अणु
	अगर (opts->ioअक्षरset != fat_शेष_ioअक्षरset) अणु
		/* Note: opts->ioअक्षरset can be शून्य here */
		kमुक्त(opts->ioअक्षरset);
		opts->ioअक्षरset = fat_शेष_ioअक्षरset;
	पूर्ण
पूर्ण

अटल व्योम delayed_मुक्त(काष्ठा rcu_head *p)
अणु
	काष्ठा msकरोs_sb_info *sbi = container_of(p, काष्ठा msकरोs_sb_info, rcu);
	unload_nls(sbi->nls_disk);
	unload_nls(sbi->nls_io);
	fat_reset_ioअक्षरset(&sbi->options);
	kमुक्त(sbi);
पूर्ण

अटल व्योम fat_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	fat_set_state(sb, 0, 0);

	iput(sbi->fsinfo_inode);
	iput(sbi->fat_inode);

	call_rcu(&sbi->rcu, delayed_मुक्त);
पूर्ण

अटल काष्ठा kmem_cache *fat_inode_cachep;

अटल काष्ठा inode *fat_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_inode_info *ei;
	ei = kmem_cache_alloc(fat_inode_cachep, GFP_NOFS);
	अगर (!ei)
		वापस शून्य;

	init_rwsem(&ei->truncate_lock);
	/* Zeroing to allow iput() even अगर partial initialized inode. */
	ei->mmu_निजी = 0;
	ei->i_start = 0;
	ei->i_logstart = 0;
	ei->i_attrs = 0;
	ei->i_pos = 0;

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम fat_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(fat_inode_cachep, MSDOS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा msकरोs_inode_info *ei = (काष्ठा msकरोs_inode_info *)foo;

	spin_lock_init(&ei->cache_lru_lock);
	ei->nr_caches = 0;
	ei->cache_valid_id = FAT_CACHE_VALID + 1;
	INIT_LIST_HEAD(&ei->cache_lru);
	INIT_HLIST_NODE(&ei->i_fat_hash);
	INIT_HLIST_NODE(&ei->i_dir_hash);
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init fat_init_inodecache(व्योम)
अणु
	fat_inode_cachep = kmem_cache_create("fat_inode_cache",
					     माप(काष्ठा msकरोs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (fat_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __निकास fat_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(fat_inode_cachep);
पूर्ण

अटल पूर्णांक fat_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	bool new_rकरोnly;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	*flags |= SB_NOसूचीATIME | (sbi->options.isvfat ? 0 : SB_NOATIME);

	sync_fileप्रणाली(sb);

	/* make sure we update state on remount. */
	new_rकरोnly = *flags & SB_RDONLY;
	अगर (new_rकरोnly != sb_rकरोnly(sb)) अणु
		अगर (new_rकरोnly)
			fat_set_state(sb, 0, 0);
		अन्यथा
			fat_set_state(sb, 1, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fat_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	/* If the count of मुक्त cluster is still unknown, counts it here. */
	अगर (sbi->मुक्त_clusters == -1 || !sbi->मुक्त_clus_valid) अणु
		पूर्णांक err = fat_count_मुक्त_clusters(dentry->d_sb);
		अगर (err)
			वापस err;
	पूर्ण

	buf->f_type = dentry->d_sb->s_magic;
	buf->f_bsize = sbi->cluster_size;
	buf->f_blocks = sbi->max_cluster - FAT_START_ENT;
	buf->f_bमुक्त = sbi->मुक्त_clusters;
	buf->f_bavail = sbi->मुक्त_clusters;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen =
		(sbi->options.isvfat ? FAT_LFN_LEN : 12) * NLS_MAX_CHARSET_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक __fat_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक रुको)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh;
	काष्ठा msकरोs_dir_entry *raw_entry;
	loff_t i_pos;
	sector_t blocknr;
	पूर्णांक err, offset;

	अगर (inode->i_ino == MSDOS_ROOT_INO)
		वापस 0;

retry:
	i_pos = fat_i_pos_पढ़ो(sbi, inode);
	अगर (!i_pos)
		वापस 0;

	fat_get_blknr_offset(sbi, i_pos, &blocknr, &offset);
	bh = sb_bपढ़ो(sb, blocknr);
	अगर (!bh) अणु
		fat_msg(sb, KERN_ERR, "unable to read inode block "
		       "for updating (i_pos %lld)", i_pos);
		वापस -EIO;
	पूर्ण
	spin_lock(&sbi->inode_hash_lock);
	अगर (i_pos != MSDOS_I(inode)->i_pos) अणु
		spin_unlock(&sbi->inode_hash_lock);
		brअन्यथा(bh);
		जाओ retry;
	पूर्ण

	raw_entry = &((काष्ठा msकरोs_dir_entry *) (bh->b_data))[offset];
	अगर (S_ISसूची(inode->i_mode))
		raw_entry->size = 0;
	अन्यथा
		raw_entry->size = cpu_to_le32(inode->i_size);
	raw_entry->attr = fat_make_attrs(inode);
	fat_set_start(raw_entry, MSDOS_I(inode)->i_logstart);
	fat_समय_unix2fat(sbi, &inode->i_mसमय, &raw_entry->समय,
			  &raw_entry->date, शून्य);
	अगर (sbi->options.isvfat) अणु
		__le16 aसमय;
		fat_समय_unix2fat(sbi, &inode->i_स_समय, &raw_entry->स_समय,
				  &raw_entry->cdate, &raw_entry->स_समय_cs);
		fat_समय_unix2fat(sbi, &inode->i_aसमय, &aसमय,
				  &raw_entry->adate, शून्य);
	पूर्ण
	spin_unlock(&sbi->inode_hash_lock);
	mark_buffer_dirty(bh);
	err = 0;
	अगर (रुको)
		err = sync_dirty_buffer(bh);
	brअन्यथा(bh);
	वापस err;
पूर्ण

अटल पूर्णांक fat_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err;

	अगर (inode->i_ino == MSDOS_FSINFO_INO) अणु
		काष्ठा super_block *sb = inode->i_sb;

		mutex_lock(&MSDOS_SB(sb)->s_lock);
		err = fat_clusters_flush(sb);
		mutex_unlock(&MSDOS_SB(sb)->s_lock);
	पूर्ण अन्यथा
		err = __fat_ग_लिखो_inode(inode, wbc->sync_mode == WB_SYNC_ALL);

	वापस err;
पूर्ण

पूर्णांक fat_sync_inode(काष्ठा inode *inode)
अणु
	वापस __fat_ग_लिखो_inode(inode, 1);
पूर्ण

EXPORT_SYMBOL_GPL(fat_sync_inode);

अटल पूर्णांक fat_show_options(काष्ठा seq_file *m, काष्ठा dentry *root);
अटल स्थिर काष्ठा super_operations fat_sops = अणु
	.alloc_inode	= fat_alloc_inode,
	.मुक्त_inode	= fat_मुक्त_inode,
	.ग_लिखो_inode	= fat_ग_लिखो_inode,
	.evict_inode	= fat_evict_inode,
	.put_super	= fat_put_super,
	.statfs		= fat_statfs,
	.remount_fs	= fat_remount,

	.show_options	= fat_show_options,
पूर्ण;

अटल पूर्णांक fat_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(root->d_sb);
	काष्ठा fat_mount_options *opts = &sbi->options;
	पूर्णांक isvfat = opts->isvfat;

	अगर (!uid_eq(opts->fs_uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
				from_kuid_munged(&init_user_ns, opts->fs_uid));
	अगर (!gid_eq(opts->fs_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
				from_kgid_munged(&init_user_ns, opts->fs_gid));
	seq_म_लिखो(m, ",fmask=%04o", opts->fs_fmask);
	seq_म_लिखो(m, ",dmask=%04o", opts->fs_dmask);
	अगर (opts->allow_uसमय)
		seq_म_लिखो(m, ",allow_utime=%04o", opts->allow_uसमय);
	अगर (sbi->nls_disk)
		/* strip "cp" prefix from displayed option */
		seq_म_लिखो(m, ",codepage=%s", &sbi->nls_disk->अक्षरset[2]);
	अगर (isvfat) अणु
		अगर (sbi->nls_io)
			seq_म_लिखो(m, ",iocharset=%s", sbi->nls_io->अक्षरset);

		चयन (opts->लघुname) अणु
		हाल VFAT_SFN_DISPLAY_WIN95 | VFAT_SFN_CREATE_WIN95:
			seq_माला_दो(m, ",shortname=win95");
			अवरोध;
		हाल VFAT_SFN_DISPLAY_WINNT | VFAT_SFN_CREATE_WINNT:
			seq_माला_दो(m, ",shortname=winnt");
			अवरोध;
		हाल VFAT_SFN_DISPLAY_WINNT | VFAT_SFN_CREATE_WIN95:
			seq_माला_दो(m, ",shortname=mixed");
			अवरोध;
		हाल VFAT_SFN_DISPLAY_LOWER | VFAT_SFN_CREATE_WIN95:
			seq_माला_दो(m, ",shortname=lower");
			अवरोध;
		शेष:
			seq_माला_दो(m, ",shortname=unknown");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (opts->name_check != 'n')
		seq_म_लिखो(m, ",check=%c", opts->name_check);
	अगर (opts->useमुक्त)
		seq_माला_दो(m, ",usefree");
	अगर (opts->quiet)
		seq_माला_दो(m, ",quiet");
	अगर (opts->showexec)
		seq_माला_दो(m, ",showexec");
	अगर (opts->sys_immutable)
		seq_माला_दो(m, ",sys_immutable");
	अगर (!isvfat) अणु
		अगर (opts->करोtsOK)
			seq_माला_दो(m, ",dotsOK=yes");
		अगर (opts->noहाल)
			seq_माला_दो(m, ",nocase");
	पूर्ण अन्यथा अणु
		अगर (opts->utf8)
			seq_माला_दो(m, ",utf8");
		अगर (opts->unicode_xlate)
			seq_माला_दो(m, ",uni_xlate");
		अगर (!opts->numtail)
			seq_माला_दो(m, ",nonumtail");
		अगर (opts->rodir)
			seq_माला_दो(m, ",rodir");
	पूर्ण
	अगर (opts->flush)
		seq_माला_दो(m, ",flush");
	अगर (opts->tz_set) अणु
		अगर (opts->समय_offset)
			seq_म_लिखो(m, ",time_offset=%d", opts->समय_offset);
		अन्यथा
			seq_माला_दो(m, ",tz=UTC");
	पूर्ण
	अगर (opts->errors == FAT_ERRORS_CONT)
		seq_माला_दो(m, ",errors=continue");
	अन्यथा अगर (opts->errors == FAT_ERRORS_PANIC)
		seq_माला_दो(m, ",errors=panic");
	अन्यथा
		seq_माला_दो(m, ",errors=remount-ro");
	अगर (opts->nfs == FAT_NFS_NOSTALE_RO)
		seq_माला_दो(m, ",nfs=nostale_ro");
	अन्यथा अगर (opts->nfs)
		seq_माला_दो(m, ",nfs=stale_rw");
	अगर (opts->discard)
		seq_माला_दो(m, ",discard");
	अगर (opts->करोs1xfloppy)
		seq_माला_दो(m, ",dos1xfloppy");

	वापस 0;
पूर्ण

क्रमागत अणु
	Opt_check_n, Opt_check_r, Opt_check_s, Opt_uid, Opt_gid,
	Opt_umask, Opt_dmask, Opt_fmask, Opt_allow_uसमय, Opt_codepage,
	Opt_useमुक्त, Opt_noहाल, Opt_quiet, Opt_showexec, Opt_debug,
	Opt_immutable, Opt_करोts, Opt_noकरोts,
	Opt_अक्षरset, Opt_लघुname_lower, Opt_लघुname_win95,
	Opt_लघुname_winnt, Opt_लघुname_mixed, Opt_utf8_no, Opt_utf8_yes,
	Opt_uni_xl_no, Opt_uni_xl_yes, Opt_nonumtail_no, Opt_nonumtail_yes,
	Opt_obsolete, Opt_flush, Opt_tz_utc, Opt_rodir, Opt_err_cont,
	Opt_err_panic, Opt_err_ro, Opt_discard, Opt_nfs, Opt_समय_offset,
	Opt_nfs_stale_rw, Opt_nfs_nostale_ro, Opt_err, Opt_करोs1xfloppy,
पूर्ण;

अटल स्थिर match_table_t fat_tokens = अणु
	अणुOpt_check_r, "check=relaxed"पूर्ण,
	अणुOpt_check_s, "check=strict"पूर्ण,
	अणुOpt_check_n, "check=normal"पूर्ण,
	अणुOpt_check_r, "check=r"पूर्ण,
	अणुOpt_check_s, "check=s"पूर्ण,
	अणुOpt_check_n, "check=n"पूर्ण,
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_umask, "umask=%o"पूर्ण,
	अणुOpt_dmask, "dmask=%o"पूर्ण,
	अणुOpt_fmask, "fmask=%o"पूर्ण,
	अणुOpt_allow_uसमय, "allow_utime=%o"पूर्ण,
	अणुOpt_codepage, "codepage=%u"पूर्ण,
	अणुOpt_useमुक्त, "usefree"पूर्ण,
	अणुOpt_noहाल, "nocase"पूर्ण,
	अणुOpt_quiet, "quiet"पूर्ण,
	अणुOpt_showexec, "showexec"पूर्ण,
	अणुOpt_debug, "debug"पूर्ण,
	अणुOpt_immutable, "sys_immutable"पूर्ण,
	अणुOpt_flush, "flush"पूर्ण,
	अणुOpt_tz_utc, "tz=UTC"पूर्ण,
	अणुOpt_समय_offset, "time_offset=%d"पूर्ण,
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_nfs_stale_rw, "nfs"पूर्ण,
	अणुOpt_nfs_stale_rw, "nfs=stale_rw"पूर्ण,
	अणुOpt_nfs_nostale_ro, "nfs=nostale_ro"पूर्ण,
	अणुOpt_करोs1xfloppy, "dos1xfloppy"पूर्ण,
	अणुOpt_obsolete, "conv=binary"पूर्ण,
	अणुOpt_obsolete, "conv=text"पूर्ण,
	अणुOpt_obsolete, "conv=auto"पूर्ण,
	अणुOpt_obsolete, "conv=b"पूर्ण,
	अणुOpt_obsolete, "conv=t"पूर्ण,
	अणुOpt_obsolete, "conv=a"पूर्ण,
	अणुOpt_obsolete, "fat=%u"पूर्ण,
	अणुOpt_obsolete, "blocksize=%u"पूर्ण,
	अणुOpt_obsolete, "cvf_format=%20s"पूर्ण,
	अणुOpt_obsolete, "cvf_options=%100s"पूर्ण,
	अणुOpt_obsolete, "posix"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;
अटल स्थिर match_table_t msकरोs_tokens = अणु
	अणुOpt_noकरोts, "nodots"पूर्ण,
	अणुOpt_noकरोts, "dotsOK=no"पूर्ण,
	अणुOpt_करोts, "dots"पूर्ण,
	अणुOpt_करोts, "dotsOK=yes"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;
अटल स्थिर match_table_t vfat_tokens = अणु
	अणुOpt_अक्षरset, "iocharset=%s"पूर्ण,
	अणुOpt_लघुname_lower, "shortname=lower"पूर्ण,
	अणुOpt_लघुname_win95, "shortname=win95"पूर्ण,
	अणुOpt_लघुname_winnt, "shortname=winnt"पूर्ण,
	अणुOpt_लघुname_mixed, "shortname=mixed"पूर्ण,
	अणुOpt_utf8_no, "utf8=0"पूर्ण,		/* 0 or no or false */
	अणुOpt_utf8_no, "utf8=no"पूर्ण,
	अणुOpt_utf8_no, "utf8=false"पूर्ण,
	अणुOpt_utf8_yes, "utf8=1"पूर्ण,		/* empty or 1 or yes or true */
	अणुOpt_utf8_yes, "utf8=yes"पूर्ण,
	अणुOpt_utf8_yes, "utf8=true"पूर्ण,
	अणुOpt_utf8_yes, "utf8"पूर्ण,
	अणुOpt_uni_xl_no, "uni_xlate=0"पूर्ण,		/* 0 or no or false */
	अणुOpt_uni_xl_no, "uni_xlate=no"पूर्ण,
	अणुOpt_uni_xl_no, "uni_xlate=false"पूर्ण,
	अणुOpt_uni_xl_yes, "uni_xlate=1"पूर्ण,	/* empty or 1 or yes or true */
	अणुOpt_uni_xl_yes, "uni_xlate=yes"पूर्ण,
	अणुOpt_uni_xl_yes, "uni_xlate=true"पूर्ण,
	अणुOpt_uni_xl_yes, "uni_xlate"पूर्ण,
	अणुOpt_nonumtail_no, "nonumtail=0"पूर्ण,	/* 0 or no or false */
	अणुOpt_nonumtail_no, "nonumtail=no"पूर्ण,
	अणुOpt_nonumtail_no, "nonumtail=false"पूर्ण,
	अणुOpt_nonumtail_yes, "nonumtail=1"पूर्ण,	/* empty or 1 or yes or true */
	अणुOpt_nonumtail_yes, "nonumtail=yes"पूर्ण,
	अणुOpt_nonumtail_yes, "nonumtail=true"पूर्ण,
	अणुOpt_nonumtail_yes, "nonumtail"पूर्ण,
	अणुOpt_rodir, "rodir"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(काष्ठा super_block *sb, अक्षर *options, पूर्णांक is_vfat,
			 पूर्णांक silent, पूर्णांक *debug, काष्ठा fat_mount_options *opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	अक्षर *ioअक्षरset;

	opts->isvfat = is_vfat;

	opts->fs_uid = current_uid();
	opts->fs_gid = current_gid();
	opts->fs_fmask = opts->fs_dmask = current_umask();
	opts->allow_uसमय = -1;
	opts->codepage = fat_शेष_codepage;
	fat_reset_ioअक्षरset(opts);
	अगर (is_vfat) अणु
		opts->लघुname = VFAT_SFN_DISPLAY_WINNT|VFAT_SFN_CREATE_WIN95;
		opts->rodir = 0;
	पूर्ण अन्यथा अणु
		opts->लघुname = 0;
		opts->rodir = 1;
	पूर्ण
	opts->name_check = 'n';
	opts->quiet = opts->showexec = opts->sys_immutable = opts->करोtsOK =  0;
	opts->unicode_xlate = 0;
	opts->numtail = 1;
	opts->useमुक्त = opts->noहाल = 0;
	opts->tz_set = 0;
	opts->nfs = 0;
	opts->errors = FAT_ERRORS_RO;
	*debug = 0;

	opts->utf8 = IS_ENABLED(CONFIG_FAT_DEFAULT_UTF8) && is_vfat;

	अगर (!options)
		जाओ out;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, fat_tokens, args);
		अगर (token == Opt_err) अणु
			अगर (is_vfat)
				token = match_token(p, vfat_tokens, args);
			अन्यथा
				token = match_token(p, msकरोs_tokens, args);
		पूर्ण
		चयन (token) अणु
		हाल Opt_check_s:
			opts->name_check = 's';
			अवरोध;
		हाल Opt_check_r:
			opts->name_check = 'r';
			अवरोध;
		हाल Opt_check_n:
			opts->name_check = 'n';
			अवरोध;
		हाल Opt_useमुक्त:
			opts->useमुक्त = 1;
			अवरोध;
		हाल Opt_noहाल:
			अगर (!is_vfat)
				opts->noहाल = 1;
			अन्यथा अणु
				/* क्रम backward compatibility */
				opts->लघुname = VFAT_SFN_DISPLAY_WIN95
					| VFAT_SFN_CREATE_WIN95;
			पूर्ण
			अवरोध;
		हाल Opt_quiet:
			opts->quiet = 1;
			अवरोध;
		हाल Opt_showexec:
			opts->showexec = 1;
			अवरोध;
		हाल Opt_debug:
			*debug = 1;
			अवरोध;
		हाल Opt_immutable:
			opts->sys_immutable = 1;
			अवरोध;
		हाल Opt_uid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			opts->fs_uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(opts->fs_uid))
				वापस -EINVAL;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			opts->fs_gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(opts->fs_gid))
				वापस -EINVAL;
			अवरोध;
		हाल Opt_umask:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->fs_fmask = opts->fs_dmask = option;
			अवरोध;
		हाल Opt_dmask:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->fs_dmask = option;
			अवरोध;
		हाल Opt_fmask:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->fs_fmask = option;
			अवरोध;
		हाल Opt_allow_uसमय:
			अगर (match_octal(&args[0], &option))
				वापस -EINVAL;
			opts->allow_uसमय = option & (S_IWGRP | S_IWOTH);
			अवरोध;
		हाल Opt_codepage:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			opts->codepage = option;
			अवरोध;
		हाल Opt_flush:
			opts->flush = 1;
			अवरोध;
		हाल Opt_समय_offset:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस -EINVAL;
			/*
			 * GMT+-12 zones may have DST corrections so at least
			 * 13 hours dअगरference is needed. Make the limit 24
			 * just in हाल someone invents something unusual.
			 */
			अगर (option < -24 * 60 || option > 24 * 60)
				वापस -EINVAL;
			opts->tz_set = 1;
			opts->समय_offset = option;
			अवरोध;
		हाल Opt_tz_utc:
			opts->tz_set = 1;
			opts->समय_offset = 0;
			अवरोध;
		हाल Opt_err_cont:
			opts->errors = FAT_ERRORS_CONT;
			अवरोध;
		हाल Opt_err_panic:
			opts->errors = FAT_ERRORS_PANIC;
			अवरोध;
		हाल Opt_err_ro:
			opts->errors = FAT_ERRORS_RO;
			अवरोध;
		हाल Opt_nfs_stale_rw:
			opts->nfs = FAT_NFS_STALE_RW;
			अवरोध;
		हाल Opt_nfs_nostale_ro:
			opts->nfs = FAT_NFS_NOSTALE_RO;
			अवरोध;
		हाल Opt_करोs1xfloppy:
			opts->करोs1xfloppy = 1;
			अवरोध;

		/* msकरोs specअगरic */
		हाल Opt_करोts:
			opts->करोtsOK = 1;
			अवरोध;
		हाल Opt_noकरोts:
			opts->करोtsOK = 0;
			अवरोध;

		/* vfat specअगरic */
		हाल Opt_अक्षरset:
			fat_reset_ioअक्षरset(opts);
			ioअक्षरset = match_strdup(&args[0]);
			अगर (!ioअक्षरset)
				वापस -ENOMEM;
			opts->ioअक्षरset = ioअक्षरset;
			अवरोध;
		हाल Opt_लघुname_lower:
			opts->लघुname = VFAT_SFN_DISPLAY_LOWER
					| VFAT_SFN_CREATE_WIN95;
			अवरोध;
		हाल Opt_लघुname_win95:
			opts->लघुname = VFAT_SFN_DISPLAY_WIN95
					| VFAT_SFN_CREATE_WIN95;
			अवरोध;
		हाल Opt_लघुname_winnt:
			opts->लघुname = VFAT_SFN_DISPLAY_WINNT
					| VFAT_SFN_CREATE_WINNT;
			अवरोध;
		हाल Opt_लघुname_mixed:
			opts->लघुname = VFAT_SFN_DISPLAY_WINNT
					| VFAT_SFN_CREATE_WIN95;
			अवरोध;
		हाल Opt_utf8_no:		/* 0 or no or false */
			opts->utf8 = 0;
			अवरोध;
		हाल Opt_utf8_yes:		/* empty or 1 or yes or true */
			opts->utf8 = 1;
			अवरोध;
		हाल Opt_uni_xl_no:		/* 0 or no or false */
			opts->unicode_xlate = 0;
			अवरोध;
		हाल Opt_uni_xl_yes:		/* empty or 1 or yes or true */
			opts->unicode_xlate = 1;
			अवरोध;
		हाल Opt_nonumtail_no:		/* 0 or no or false */
			opts->numtail = 1;	/* negated option */
			अवरोध;
		हाल Opt_nonumtail_yes:		/* empty or 1 or yes or true */
			opts->numtail = 0;	/* negated option */
			अवरोध;
		हाल Opt_rodir:
			opts->rodir = 1;
			अवरोध;
		हाल Opt_discard:
			opts->discard = 1;
			अवरोध;

		/* obsolete mount options */
		हाल Opt_obsolete:
			fat_msg(sb, KERN_INFO, "\"%s\" option is obsolete, "
			       "not supported now", p);
			अवरोध;
		/* unknown option */
		शेष:
			अगर (!silent) अणु
				fat_msg(sb, KERN_ERR,
				       "Unrecognized mount option \"%s\" "
				       "or missing value", p);
			पूर्ण
			वापस -EINVAL;
		पूर्ण
	पूर्ण

out:
	/* UTF-8 करोesn't provide FAT semantics */
	अगर (!म_भेद(opts->ioअक्षरset, "utf8")) अणु
		fat_msg(sb, KERN_WARNING, "utf8 is not a recommended IO charset"
		       " for FAT filesystems, filesystem will be "
		       "case sensitive!");
	पूर्ण

	/* If user करोesn't specify allow_utime, it's initialized from dmask. */
	अगर (opts->allow_uसमय == (अचिन्हित लघु)-1)
		opts->allow_uसमय = ~opts->fs_dmask & (S_IWGRP | S_IWOTH);
	अगर (opts->unicode_xlate)
		opts->utf8 = 0;
	अगर (opts->nfs == FAT_NFS_NOSTALE_RO) अणु
		sb->s_flags |= SB_RDONLY;
		sb->s_export_op = &fat_export_ops_nostale;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fat_पढ़ो_root(काष्ठा inode *inode)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	पूर्णांक error;

	MSDOS_I(inode)->i_pos = MSDOS_ROOT_INO;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_iversion(inode);
	inode->i_generation = 0;
	inode->i_mode = fat_make_mode(sbi, ATTR_सूची, S_IRWXUGO);
	inode->i_op = sbi->dir_ops;
	inode->i_fop = &fat_dir_operations;
	अगर (is_fat32(sbi)) अणु
		MSDOS_I(inode)->i_start = sbi->root_cluster;
		error = fat_calc_dir_size(inode);
		अगर (error < 0)
			वापस error;
	पूर्ण अन्यथा अणु
		MSDOS_I(inode)->i_start = 0;
		inode->i_size = sbi->dir_entries * माप(काष्ठा msकरोs_dir_entry);
	पूर्ण
	inode->i_blocks = ((inode->i_size + (sbi->cluster_size - 1))
			   & ~((loff_t)sbi->cluster_size - 1)) >> 9;
	MSDOS_I(inode)->i_logstart = 0;
	MSDOS_I(inode)->mmu_निजी = inode->i_size;

	fat_save_attrs(inode, ATTR_सूची);
	inode->i_mसमय.tv_sec = inode->i_aसमय.tv_sec = inode->i_स_समय.tv_sec = 0;
	inode->i_mसमय.tv_nsec = inode->i_aसमय.tv_nsec = inode->i_स_समय.tv_nsec = 0;
	set_nlink(inode, fat_subdirs(inode)+2);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ calc_fat_clusters(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	/* Divide first to aव्योम overflow */
	अगर (!is_fat12(sbi)) अणु
		अचिन्हित दीर्घ ent_per_sec = sb->s_blocksize * 8 / sbi->fat_bits;
		वापस ent_per_sec * sbi->fat_length;
	पूर्ण

	वापस sbi->fat_length * sb->s_blocksize * 8 / sbi->fat_bits;
पूर्ण

अटल bool fat_bpb_is_zero(काष्ठा fat_boot_sector *b)
अणु
	अगर (get_unaligned_le16(&b->sector_size))
		वापस false;
	अगर (b->sec_per_clus)
		वापस false;
	अगर (b->reserved)
		वापस false;
	अगर (b->fats)
		वापस false;
	अगर (get_unaligned_le16(&b->dir_entries))
		वापस false;
	अगर (get_unaligned_le16(&b->sectors))
		वापस false;
	अगर (b->media)
		वापस false;
	अगर (b->fat_length)
		वापस false;
	अगर (b->secs_track)
		वापस false;
	अगर (b->heads)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक fat_पढ़ो_bpb(काष्ठा super_block *sb, काष्ठा fat_boot_sector *b,
	पूर्णांक silent, काष्ठा fat_bios_param_block *bpb)
अणु
	पूर्णांक error = -EINVAL;

	/* Read in BPB ... */
	स_रखो(bpb, 0, माप(*bpb));
	bpb->fat_sector_size = get_unaligned_le16(&b->sector_size);
	bpb->fat_sec_per_clus = b->sec_per_clus;
	bpb->fat_reserved = le16_to_cpu(b->reserved);
	bpb->fat_fats = b->fats;
	bpb->fat_dir_entries = get_unaligned_le16(&b->dir_entries);
	bpb->fat_sectors = get_unaligned_le16(&b->sectors);
	bpb->fat_fat_length = le16_to_cpu(b->fat_length);
	bpb->fat_total_sect = le32_to_cpu(b->total_sect);

	bpb->fat16_state = b->fat16.state;
	bpb->fat16_vol_id = get_unaligned_le32(b->fat16.vol_id);

	bpb->fat32_length = le32_to_cpu(b->fat32.length);
	bpb->fat32_root_cluster = le32_to_cpu(b->fat32.root_cluster);
	bpb->fat32_info_sector = le16_to_cpu(b->fat32.info_sector);
	bpb->fat32_state = b->fat32.state;
	bpb->fat32_vol_id = get_unaligned_le32(b->fat32.vol_id);

	/* Validate this looks like a FAT fileप्रणाली BPB */
	अगर (!bpb->fat_reserved) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR,
				"bogus number of reserved sectors");
		जाओ out;
	पूर्ण
	अगर (!bpb->fat_fats) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "bogus number of FAT structure");
		जाओ out;
	पूर्ण

	/*
	 * Earlier we checked here that b->secs_track and b->head are nonzero,
	 * but it turns out valid FAT fileप्रणालीs can have zero there.
	 */

	अगर (!fat_valid_media(b->media)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "invalid media value (0x%02x)",
				(अचिन्हित)b->media);
		जाओ out;
	पूर्ण

	अगर (!is_घातer_of_2(bpb->fat_sector_size)
	    || (bpb->fat_sector_size < 512)
	    || (bpb->fat_sector_size > 4096)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "bogus logical sector size %u",
			       (अचिन्हित)bpb->fat_sector_size);
		जाओ out;
	पूर्ण

	अगर (!is_घातer_of_2(bpb->fat_sec_per_clus)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "bogus sectors per cluster %u",
				(अचिन्हित)bpb->fat_sec_per_clus);
		जाओ out;
	पूर्ण

	अगर (bpb->fat_fat_length == 0 && bpb->fat32_length == 0) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "bogus number of FAT sectors");
		जाओ out;
	पूर्ण

	error = 0;

out:
	वापस error;
पूर्ण

अटल पूर्णांक fat_पढ़ो_अटल_bpb(काष्ठा super_block *sb,
	काष्ठा fat_boot_sector *b, पूर्णांक silent,
	काष्ठा fat_bios_param_block *bpb)
अणु
	अटल स्थिर अक्षर *notकरोs1x = "This doesn't look like a DOS 1.x volume";

	काष्ठा fat_floppy_शेषs *fशेषs = शून्य;
	पूर्णांक error = -EINVAL;
	sector_t bd_sects;
	अचिन्हित i;

	bd_sects = i_size_पढ़ो(sb->s_bdev->bd_inode) / SECTOR_SIZE;

	/* 16-bit DOS 1.x reliably wrote bootstrap लघु-jmp code */
	अगर (b->ignored[0] != 0xeb || b->ignored[2] != 0x90) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR,
				"%s; no bootstrapping code", notकरोs1x);
		जाओ out;
	पूर्ण

	/*
	 * If any value in this region is non-zero, it isn't archaic
	 * DOS.
	 */
	अगर (!fat_bpb_is_zero(b)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR,
				"%s; DOS 2.x BPB is non-zero", notकरोs1x);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(floppy_शेषs); i++) अणु
		अगर (floppy_शेषs[i].nr_sectors == bd_sects) अणु
			fशेषs = &floppy_शेषs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fशेषs == शून्य) अणु
		अगर (!silent)
			fat_msg(sb, KERN_WARNING,
				"This looks like a DOS 1.x volume, but isn't a recognized floppy size (%llu sectors)",
				(u64)bd_sects);
		जाओ out;
	पूर्ण

	अगर (!silent)
		fat_msg(sb, KERN_INFO,
			"This looks like a DOS 1.x volume; assuming default BPB values");

	स_रखो(bpb, 0, माप(*bpb));
	bpb->fat_sector_size = SECTOR_SIZE;
	bpb->fat_sec_per_clus = fशेषs->sec_per_clus;
	bpb->fat_reserved = 1;
	bpb->fat_fats = 2;
	bpb->fat_dir_entries = fशेषs->dir_entries;
	bpb->fat_sectors = fशेषs->nr_sectors;
	bpb->fat_fat_length = fशेषs->fat_length;

	error = 0;

out:
	वापस error;
पूर्ण

/*
 * Read the super block of an MS-DOS FS.
 */
पूर्णांक fat_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent, पूर्णांक isvfat,
		   व्योम (*setup)(काष्ठा super_block *))
अणु
	काष्ठा inode *root_inode = शून्य, *fat_inode = शून्य;
	काष्ठा inode *fsinfo_inode = शून्य;
	काष्ठा buffer_head *bh;
	काष्ठा fat_bios_param_block bpb;
	काष्ठा msकरोs_sb_info *sbi;
	u16 logical_sector_size;
	u32 total_sectors, total_clusters, fat_clusters, rootdir_sectors;
	पूर्णांक debug;
	दीर्घ error;
	अक्षर buf[50];
	काष्ठा बारpec64 ts;

	/*
	 * GFP_KERNEL is ok here, because जबतक we करो hold the
	 * superblock lock, memory pressure can't call back पूर्णांकo
	 * the fileप्रणाली, since we're only just about to mount
	 * it and have no inodes etc active!
	 */
	sbi = kzalloc(माप(काष्ठा msकरोs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	sb->s_fs_info = sbi;

	sb->s_flags |= SB_NOसूचीATIME;
	sb->s_magic = MSDOS_SUPER_MAGIC;
	sb->s_op = &fat_sops;
	sb->s_export_op = &fat_export_ops;
	/*
	 * fat बारtamps are complex and truncated by fat itself, so
	 * we set 1 here to be fast
	 */
	sb->s_समय_gran = 1;
	mutex_init(&sbi->nfs_build_inode_lock);
	ratelimit_state_init(&sbi->ratelimit, DEFAULT_RATELIMIT_INTERVAL,
			     DEFAULT_RATELIMIT_BURST);

	error = parse_options(sb, data, isvfat, silent, &debug, &sbi->options);
	अगर (error)
		जाओ out_fail;

	setup(sb); /* flavour-specअगरic stuff that needs options */

	error = -EIO;
	sb_min_blocksize(sb, 512);
	bh = sb_bपढ़ो(sb, 0);
	अगर (bh == शून्य) अणु
		fat_msg(sb, KERN_ERR, "unable to read boot sector");
		जाओ out_fail;
	पूर्ण

	error = fat_पढ़ो_bpb(sb, (काष्ठा fat_boot_sector *)bh->b_data, silent,
		&bpb);
	अगर (error == -EINVAL && sbi->options.करोs1xfloppy)
		error = fat_पढ़ो_अटल_bpb(sb,
			(काष्ठा fat_boot_sector *)bh->b_data, silent, &bpb);
	brअन्यथा(bh);

	अगर (error == -EINVAL)
		जाओ out_invalid;
	अन्यथा अगर (error)
		जाओ out_fail;

	logical_sector_size = bpb.fat_sector_size;
	sbi->sec_per_clus = bpb.fat_sec_per_clus;

	error = -EIO;
	अगर (logical_sector_size < sb->s_blocksize) अणु
		fat_msg(sb, KERN_ERR, "logical sector size too small for device"
		       " (logical sector size = %u)", logical_sector_size);
		जाओ out_fail;
	पूर्ण

	अगर (logical_sector_size > sb->s_blocksize) अणु
		काष्ठा buffer_head *bh_resize;

		अगर (!sb_set_blocksize(sb, logical_sector_size)) अणु
			fat_msg(sb, KERN_ERR, "unable to set blocksize %u",
			       logical_sector_size);
			जाओ out_fail;
		पूर्ण

		/* Verअगरy that the larger boot sector is fully पढ़ोable */
		bh_resize = sb_bपढ़ो(sb, 0);
		अगर (bh_resize == शून्य) अणु
			fat_msg(sb, KERN_ERR, "unable to read boot sector"
			       " (logical sector size = %lu)",
			       sb->s_blocksize);
			जाओ out_fail;
		पूर्ण
		brअन्यथा(bh_resize);
	पूर्ण

	mutex_init(&sbi->s_lock);
	sbi->cluster_size = sb->s_blocksize * sbi->sec_per_clus;
	sbi->cluster_bits = ffs(sbi->cluster_size) - 1;
	sbi->fats = bpb.fat_fats;
	sbi->fat_bits = 0;		/* Don't know yet */
	sbi->fat_start = bpb.fat_reserved;
	sbi->fat_length = bpb.fat_fat_length;
	sbi->root_cluster = 0;
	sbi->मुक्त_clusters = -1;	/* Don't know yet */
	sbi->मुक्त_clus_valid = 0;
	sbi->prev_मुक्त = FAT_START_ENT;
	sb->s_maxbytes = 0xffffffff;
	fat_समय_fat2unix(sbi, &ts, 0, cpu_to_le16(FAT_DATE_MIN), 0);
	sb->s_समय_min = ts.tv_sec;

	fat_समय_fat2unix(sbi, &ts, cpu_to_le16(FAT_TIME_MAX),
			  cpu_to_le16(FAT_DATE_MAX), 0);
	sb->s_समय_max = ts.tv_sec;

	अगर (!sbi->fat_length && bpb.fat32_length) अणु
		काष्ठा fat_boot_fsinfo *fsinfo;
		काष्ठा buffer_head *fsinfo_bh;

		/* Must be FAT32 */
		sbi->fat_bits = 32;
		sbi->fat_length = bpb.fat32_length;
		sbi->root_cluster = bpb.fat32_root_cluster;

		/* MC - अगर info_sector is 0, करोn't multiply by 0 */
		sbi->fsinfo_sector = bpb.fat32_info_sector;
		अगर (sbi->fsinfo_sector == 0)
			sbi->fsinfo_sector = 1;

		fsinfo_bh = sb_bपढ़ो(sb, sbi->fsinfo_sector);
		अगर (fsinfo_bh == शून्य) अणु
			fat_msg(sb, KERN_ERR, "bread failed, FSINFO block"
			       " (sector = %lu)", sbi->fsinfo_sector);
			जाओ out_fail;
		पूर्ण

		fsinfo = (काष्ठा fat_boot_fsinfo *)fsinfo_bh->b_data;
		अगर (!IS_FSINFO(fsinfo)) अणु
			fat_msg(sb, KERN_WARNING, "Invalid FSINFO signature: "
			       "0x%08x, 0x%08x (sector = %lu)",
			       le32_to_cpu(fsinfo->signature1),
			       le32_to_cpu(fsinfo->signature2),
			       sbi->fsinfo_sector);
		पूर्ण अन्यथा अणु
			अगर (sbi->options.useमुक्त)
				sbi->मुक्त_clus_valid = 1;
			sbi->मुक्त_clusters = le32_to_cpu(fsinfo->मुक्त_clusters);
			sbi->prev_मुक्त = le32_to_cpu(fsinfo->next_cluster);
		पूर्ण

		brअन्यथा(fsinfo_bh);
	पूर्ण

	/* पूर्णांकerpret volume ID as a little endian 32 bit पूर्णांकeger */
	अगर (is_fat32(sbi))
		sbi->vol_id = bpb.fat32_vol_id;
	अन्यथा /* fat 16 or 12 */
		sbi->vol_id = bpb.fat16_vol_id;

	sbi->dir_per_block = sb->s_blocksize / माप(काष्ठा msकरोs_dir_entry);
	sbi->dir_per_block_bits = ffs(sbi->dir_per_block) - 1;

	sbi->dir_start = sbi->fat_start + sbi->fats * sbi->fat_length;
	sbi->dir_entries = bpb.fat_dir_entries;
	अगर (sbi->dir_entries & (sbi->dir_per_block - 1)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "bogus number of directory entries"
			       " (%u)", sbi->dir_entries);
		जाओ out_invalid;
	पूर्ण

	rootdir_sectors = sbi->dir_entries
		* माप(काष्ठा msकरोs_dir_entry) / sb->s_blocksize;
	sbi->data_start = sbi->dir_start + rootdir_sectors;
	total_sectors = bpb.fat_sectors;
	अगर (total_sectors == 0)
		total_sectors = bpb.fat_total_sect;

	total_clusters = (total_sectors - sbi->data_start) / sbi->sec_per_clus;

	अगर (!is_fat32(sbi))
		sbi->fat_bits = (total_clusters > MAX_FAT12) ? 16 : 12;

	/* some OSes set FAT_STATE_सूचीTY and clean it on unmount. */
	अगर (is_fat32(sbi))
		sbi->dirty = bpb.fat32_state & FAT_STATE_सूचीTY;
	अन्यथा /* fat 16 or 12 */
		sbi->dirty = bpb.fat16_state & FAT_STATE_सूचीTY;

	/* check that FAT table करोes not overflow */
	fat_clusters = calc_fat_clusters(sb);
	total_clusters = min(total_clusters, fat_clusters - FAT_START_ENT);
	अगर (total_clusters > max_fat(sb)) अणु
		अगर (!silent)
			fat_msg(sb, KERN_ERR, "count of clusters too big (%u)",
			       total_clusters);
		जाओ out_invalid;
	पूर्ण

	sbi->max_cluster = total_clusters + FAT_START_ENT;
	/* check the मुक्त_clusters, it's not necessarily correct */
	अगर (sbi->मुक्त_clusters != -1 && sbi->मुक्त_clusters > total_clusters)
		sbi->मुक्त_clusters = -1;
	/* check the prev_मुक्त, it's not necessarily correct */
	sbi->prev_मुक्त %= sbi->max_cluster;
	अगर (sbi->prev_मुक्त < FAT_START_ENT)
		sbi->prev_मुक्त = FAT_START_ENT;

	/* set up enough so that it can पढ़ो an inode */
	fat_hash_init(sb);
	dir_hash_init(sb);
	fat_ent_access_init(sb);

	/*
	 * The low byte of the first FAT entry must have the same value as
	 * the media field of the boot sector. But in real world, too many
	 * devices are writing wrong values. So, हटाओd that validity check.
	 *
	 * The हटाओd check compared the first FAT entry to a value dependent
	 * on the media field like this:
	 * == (0x0F00 | media), क्रम FAT12
	 * == (0XFF00 | media), क्रम FAT16
	 * == (0x0FFFFF | media), क्रम FAT32
	 */

	error = -EINVAL;
	प्र_लिखो(buf, "cp%d", sbi->options.codepage);
	sbi->nls_disk = load_nls(buf);
	अगर (!sbi->nls_disk) अणु
		fat_msg(sb, KERN_ERR, "codepage %s not found", buf);
		जाओ out_fail;
	पूर्ण

	/* FIXME: utf8 is using ioअक्षरset क्रम upper/lower conversion */
	अगर (sbi->options.isvfat) अणु
		sbi->nls_io = load_nls(sbi->options.ioअक्षरset);
		अगर (!sbi->nls_io) अणु
			fat_msg(sb, KERN_ERR, "IO charset %s not found",
			       sbi->options.ioअक्षरset);
			जाओ out_fail;
		पूर्ण
	पूर्ण

	error = -ENOMEM;
	fat_inode = new_inode(sb);
	अगर (!fat_inode)
		जाओ out_fail;
	sbi->fat_inode = fat_inode;

	fsinfo_inode = new_inode(sb);
	अगर (!fsinfo_inode)
		जाओ out_fail;
	fsinfo_inode->i_ino = MSDOS_FSINFO_INO;
	sbi->fsinfo_inode = fsinfo_inode;
	insert_inode_hash(fsinfo_inode);

	root_inode = new_inode(sb);
	अगर (!root_inode)
		जाओ out_fail;
	root_inode->i_ino = MSDOS_ROOT_INO;
	inode_set_iversion(root_inode, 1);
	error = fat_पढ़ो_root(root_inode);
	अगर (error < 0) अणु
		iput(root_inode);
		जाओ out_fail;
	पूर्ण
	error = -ENOMEM;
	insert_inode_hash(root_inode);
	fat_attach(root_inode, 0);
	sb->s_root = d_make_root(root_inode);
	अगर (!sb->s_root) अणु
		fat_msg(sb, KERN_ERR, "get root inode failed");
		जाओ out_fail;
	पूर्ण

	अगर (sbi->options.discard) अणु
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
		अगर (!blk_queue_discard(q))
			fat_msg(sb, KERN_WARNING,
					"mounting with \"discard\" option, but "
					"the device does not support discard");
	पूर्ण

	fat_set_state(sb, 1, 0);
	वापस 0;

out_invalid:
	error = -EINVAL;
	अगर (!silent)
		fat_msg(sb, KERN_INFO, "Can't find a valid FAT filesystem");

out_fail:
	अगर (fsinfo_inode)
		iput(fsinfo_inode);
	अगर (fat_inode)
		iput(fat_inode);
	unload_nls(sbi->nls_io);
	unload_nls(sbi->nls_disk);
	fat_reset_ioअक्षरset(&sbi->options);
	sb->s_fs_info = शून्य;
	kमुक्त(sbi);
	वापस error;
पूर्ण

EXPORT_SYMBOL_GPL(fat_fill_super);

/*
 * helper function क्रम fat_flush_inodes.  This ग_लिखोs both the inode
 * and the file data blocks, रुकोing क्रम in flight data blocks beक्रमe
 * the start of the call.  It करोes not रुको क्रम any io started
 * during the call
 */
अटल पूर्णांक ग_लिखोback_inode(काष्ठा inode *inode)
अणु

	पूर्णांक ret;

	/* अगर we used रुको=1, sync_inode_metadata रुकोs क्रम the io क्रम the
	* inode to finish.  So रुको=0 is sent करोwn to sync_inode_metadata
	* and filemap_fdataग_लिखो is used क्रम the data blocks
	*/
	ret = sync_inode_metadata(inode, 0);
	अगर (!ret)
		ret = filemap_fdataग_लिखो(inode->i_mapping);
	वापस ret;
पूर्ण

/*
 * ग_लिखो data and metadata corresponding to i1 and i2.  The io is
 * started but we करो not रुको क्रम any of it to finish.
 *
 * filemap_flush is used क्रम the block device, so अगर there is a dirty
 * page क्रम a block alपढ़ोy in flight, we will not रुको and start the
 * io over again
 */
पूर्णांक fat_flush_inodes(काष्ठा super_block *sb, काष्ठा inode *i1, काष्ठा inode *i2)
अणु
	पूर्णांक ret = 0;
	अगर (!MSDOS_SB(sb)->options.flush)
		वापस 0;
	अगर (i1)
		ret = ग_लिखोback_inode(i1);
	अगर (!ret && i2)
		ret = ग_लिखोback_inode(i2);
	अगर (!ret) अणु
		काष्ठा address_space *mapping = sb->s_bdev->bd_inode->i_mapping;
		ret = filemap_flush(mapping);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fat_flush_inodes);

अटल पूर्णांक __init init_fat_fs(व्योम)
अणु
	पूर्णांक err;

	err = fat_cache_init();
	अगर (err)
		वापस err;

	err = fat_init_inodecache();
	अगर (err)
		जाओ failed;

	वापस 0;

failed:
	fat_cache_destroy();
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_fat_fs(व्योम)
अणु
	fat_cache_destroy();
	fat_destroy_inodecache();
पूर्ण

module_init(init_fat_fs)
module_निकास(निकास_fat_fs)

MODULE_LICENSE("GPL");
