<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/समय.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/uपन.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/iversion.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल पूर्णांक __exfat_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक sync)
अणु
	अचिन्हित दीर्घ दीर्घ on_disk_size;
	काष्ठा exfat_dentry *ep, *ep2;
	काष्ठा exfat_entry_set_cache *es = शून्य;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	bool is_dir = (ei->type == TYPE_सूची) ? true : false;

	अगर (inode->i_ino == EXFAT_ROOT_INO)
		वापस 0;

	/*
	 * If the inकरोde is alपढ़ोy unlinked, there is no need क्रम updating it.
	 */
	अगर (ei->dir.dir == सूची_DELETED)
		वापस 0;

	अगर (is_dir && ei->dir.dir == sbi->root_dir && ei->entry == -1)
		वापस 0;

	exfat_set_volume_dirty(sb);

	/* get the directory entry of given file or directory */
	es = exfat_get_dentry_set(sb, &(ei->dir), ei->entry, ES_ALL_ENTRIES);
	अगर (!es)
		वापस -EIO;
	ep = exfat_get_dentry_cached(es, 0);
	ep2 = exfat_get_dentry_cached(es, 1);

	ep->dentry.file.attr = cpu_to_le16(exfat_make_attr(inode));

	/* set खाता_INFO काष्ठाure using the acquired काष्ठा exfat_dentry */
	exfat_set_entry_समय(sbi, &ei->i_crसमय,
			&ep->dentry.file.create_tz,
			&ep->dentry.file.create_समय,
			&ep->dentry.file.create_date,
			&ep->dentry.file.create_समय_cs);
	exfat_set_entry_समय(sbi, &inode->i_mसमय,
			&ep->dentry.file.modअगरy_tz,
			&ep->dentry.file.modअगरy_समय,
			&ep->dentry.file.modअगरy_date,
			&ep->dentry.file.modअगरy_समय_cs);
	exfat_set_entry_समय(sbi, &inode->i_aसमय,
			&ep->dentry.file.access_tz,
			&ep->dentry.file.access_समय,
			&ep->dentry.file.access_date,
			शून्य);

	/* File size should be zero अगर there is no cluster allocated */
	on_disk_size = i_size_पढ़ो(inode);

	अगर (ei->start_clu == EXFAT_खातापूर्ण_CLUSTER)
		on_disk_size = 0;

	ep2->dentry.stream.valid_size = cpu_to_le64(on_disk_size);
	ep2->dentry.stream.size = ep2->dentry.stream.valid_size;

	exfat_update_dir_chksum_with_entry_set(es);
	वापस exfat_मुक्त_dentry_set(es, sync);
पूर्ण

पूर्णांक exfat_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;

	mutex_lock(&EXFAT_SB(inode->i_sb)->s_lock);
	ret = __exfat_ग_लिखो_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
	mutex_unlock(&EXFAT_SB(inode->i_sb)->s_lock);

	वापस ret;
पूर्ण

व्योम exfat_sync_inode(काष्ठा inode *inode)
अणु
	lockdep_निश्चित_held(&EXFAT_SB(inode->i_sb)->s_lock);
	__exfat_ग_लिखो_inode(inode, 1);
पूर्ण

/*
 * Input: inode, (logical) clu_offset, target allocation area
 * Output: errcode, cluster number
 * *clu = (~0), अगर it's unable to allocate a new cluster
 */
अटल पूर्णांक exfat_map_cluster(काष्ठा inode *inode, अचिन्हित पूर्णांक clu_offset,
		अचिन्हित पूर्णांक *clu, पूर्णांक create)
अणु
	पूर्णांक ret, modअगरied = false;
	अचिन्हित पूर्णांक last_clu;
	काष्ठा exfat_chain new_clu;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	अचिन्हित पूर्णांक local_clu_offset = clu_offset;
	अचिन्हित पूर्णांक num_to_be_allocated = 0, num_clusters = 0;

	अगर (EXFAT_I(inode)->i_size_ondisk > 0)
		num_clusters =
			EXFAT_B_TO_CLU_ROUND_UP(EXFAT_I(inode)->i_size_ondisk,
			sbi);

	अगर (clu_offset >= num_clusters)
		num_to_be_allocated = clu_offset - num_clusters + 1;

	अगर (!create && (num_to_be_allocated > 0)) अणु
		*clu = EXFAT_खातापूर्ण_CLUSTER;
		वापस 0;
	पूर्ण

	*clu = last_clu = ei->start_clu;

	अगर (ei->flags == ALLOC_NO_FAT_CHAIN) अणु
		अगर (clu_offset > 0 && *clu != EXFAT_खातापूर्ण_CLUSTER) अणु
			last_clu += clu_offset - 1;

			अगर (clu_offset == num_clusters)
				*clu = EXFAT_खातापूर्ण_CLUSTER;
			अन्यथा
				*clu += clu_offset;
		पूर्ण
	पूर्ण अन्यथा अगर (ei->type == TYPE_खाता) अणु
		अचिन्हित पूर्णांक fclus = 0;
		पूर्णांक err = exfat_get_cluster(inode, clu_offset,
				&fclus, clu, &last_clu, 1);
		अगर (err)
			वापस -EIO;

		clu_offset -= fclus;
	पूर्ण अन्यथा अणु
		/* hपूर्णांक inक्रमmation */
		अगर (clu_offset > 0 && ei->hपूर्णांक_bmap.off != EXFAT_खातापूर्ण_CLUSTER &&
		    ei->hपूर्णांक_bmap.off > 0 && clu_offset >= ei->hपूर्णांक_bmap.off) अणु
			clu_offset -= ei->hपूर्णांक_bmap.off;
			/* hपूर्णांक_bmap.clu should be valid */
			WARN_ON(ei->hपूर्णांक_bmap.clu < 2);
			*clu = ei->hपूर्णांक_bmap.clu;
		पूर्ण

		जबतक (clu_offset > 0 && *clu != EXFAT_खातापूर्ण_CLUSTER) अणु
			last_clu = *clu;
			अगर (exfat_get_next_cluster(sb, clu))
				वापस -EIO;
			clu_offset--;
		पूर्ण
	पूर्ण

	अगर (*clu == EXFAT_खातापूर्ण_CLUSTER) अणु
		exfat_set_volume_dirty(sb);

		new_clu.dir = (last_clu == EXFAT_खातापूर्ण_CLUSTER) ?
				EXFAT_खातापूर्ण_CLUSTER : last_clu + 1;
		new_clu.size = 0;
		new_clu.flags = ei->flags;

		/* allocate a cluster */
		अगर (num_to_be_allocated < 1) अणु
			/* Broken FAT (i_sze > allocated FAT) */
			exfat_fs_error(sb, "broken FAT chain.");
			वापस -EIO;
		पूर्ण

		ret = exfat_alloc_cluster(inode, num_to_be_allocated, &new_clu,
				inode_needs_sync(inode));
		अगर (ret)
			वापस ret;

		अगर (new_clu.dir == EXFAT_खातापूर्ण_CLUSTER ||
		    new_clu.dir == EXFAT_FREE_CLUSTER) अणु
			exfat_fs_error(sb,
				"bogus cluster new allocated (last_clu : %u, new_clu : %u)",
				last_clu, new_clu.dir);
			वापस -EIO;
		पूर्ण

		/* append to the FAT chain */
		अगर (last_clu == EXFAT_खातापूर्ण_CLUSTER) अणु
			अगर (new_clu.flags == ALLOC_FAT_CHAIN)
				ei->flags = ALLOC_FAT_CHAIN;
			ei->start_clu = new_clu.dir;
			modअगरied = true;
		पूर्ण अन्यथा अणु
			अगर (new_clu.flags != ei->flags) अणु
				/* no-fat-chain bit is disabled,
				 * so fat-chain should be synced with
				 * alloc-biपंचांगap
				 */
				exfat_chain_cont_cluster(sb, ei->start_clu,
					num_clusters);
				ei->flags = ALLOC_FAT_CHAIN;
				modअगरied = true;
			पूर्ण
			अगर (new_clu.flags == ALLOC_FAT_CHAIN)
				अगर (exfat_ent_set(sb, last_clu, new_clu.dir))
					वापस -EIO;
		पूर्ण

		num_clusters += num_to_be_allocated;
		*clu = new_clu.dir;

		अगर (ei->dir.dir != सूची_DELETED && modअगरied) अणु
			काष्ठा exfat_dentry *ep;
			काष्ठा exfat_entry_set_cache *es;
			पूर्णांक err;

			es = exfat_get_dentry_set(sb, &(ei->dir), ei->entry,
				ES_ALL_ENTRIES);
			अगर (!es)
				वापस -EIO;
			/* get stream entry */
			ep = exfat_get_dentry_cached(es, 1);

			/* update directory entry */
			ep->dentry.stream.flags = ei->flags;
			ep->dentry.stream.start_clu =
				cpu_to_le32(ei->start_clu);
			ep->dentry.stream.valid_size =
				cpu_to_le64(i_size_पढ़ो(inode));
			ep->dentry.stream.size =
				ep->dentry.stream.valid_size;

			exfat_update_dir_chksum_with_entry_set(es);
			err = exfat_मुक्त_dentry_set(es, inode_needs_sync(inode));
			अगर (err)
				वापस err;
		पूर्ण /* end of अगर != सूची_DELETED */

		inode->i_blocks +=
			num_to_be_allocated << sbi->sect_per_clus_bits;

		/*
		 * Move *clu poपूर्णांकer aदीर्घ FAT chains (hole care) because the
		 * caller of this function expect *clu to be the last cluster.
		 * This only works when num_to_be_allocated >= 2,
		 * *clu = (the first cluster of the allocated chain) =>
		 * (the last cluster of ...)
		 */
		अगर (ei->flags == ALLOC_NO_FAT_CHAIN) अणु
			*clu += num_to_be_allocated - 1;
		पूर्ण अन्यथा अणु
			जबतक (num_to_be_allocated > 1) अणु
				अगर (exfat_get_next_cluster(sb, clu))
					वापस -EIO;
				num_to_be_allocated--;
			पूर्ण
		पूर्ण

	पूर्ण

	/* hपूर्णांक inक्रमmation */
	ei->hपूर्णांक_bmap.off = local_clu_offset;
	ei->hपूर्णांक_bmap.clu = *clu;

	वापस 0;
पूर्ण

अटल पूर्णांक exfat_map_new_buffer(काष्ठा exfat_inode_info *ei,
		काष्ठा buffer_head *bh, loff_t pos)
अणु
	अगर (buffer_delay(bh) && pos > ei->i_size_aligned)
		वापस -EIO;
	set_buffer_new(bh);

	/*
	 * Adjust i_size_aligned अगर i_size_ondisk is bigger than it.
	 */
	अगर (ei->i_size_ondisk > ei->i_size_aligned)
		ei->i_size_aligned = ei->i_size_ondisk;
	वापस 0;
पूर्ण

अटल पूर्णांक exfat_get_block(काष्ठा inode *inode, sector_t iblock,
		काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित दीर्घ max_blocks = bh_result->b_size >> inode->i_blkbits;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ mapped_blocks = 0;
	अचिन्हित पूर्णांक cluster, sec_offset;
	sector_t last_block;
	sector_t phys = 0;
	loff_t pos;

	mutex_lock(&sbi->s_lock);
	last_block = EXFAT_B_TO_BLK_ROUND_UP(i_size_पढ़ो(inode), sb);
	अगर (iblock >= last_block && !create)
		जाओ करोne;

	/* Is this block alपढ़ोy allocated? */
	err = exfat_map_cluster(inode, iblock >> sbi->sect_per_clus_bits,
			&cluster, create);
	अगर (err) अणु
		अगर (err != -ENOSPC)
			exfat_fs_error_ratelimit(sb,
				"failed to bmap (inode : %p iblock : %llu, err : %d)",
				inode, (अचिन्हित दीर्घ दीर्घ)iblock, err);
		जाओ unlock_ret;
	पूर्ण

	अगर (cluster == EXFAT_खातापूर्ण_CLUSTER)
		जाओ करोne;

	/* sector offset in cluster */
	sec_offset = iblock & (sbi->sect_per_clus - 1);

	phys = exfat_cluster_to_sector(sbi, cluster) + sec_offset;
	mapped_blocks = sbi->sect_per_clus - sec_offset;
	max_blocks = min(mapped_blocks, max_blocks);

	/* Treat newly added block / cluster */
	अगर (iblock < last_block)
		create = 0;

	अगर (create || buffer_delay(bh_result)) अणु
		pos = EXFAT_BLK_TO_B((iblock + 1), sb);
		अगर (ei->i_size_ondisk < pos)
			ei->i_size_ondisk = pos;
	पूर्ण

	अगर (create) अणु
		err = exfat_map_new_buffer(ei, bh_result, pos);
		अगर (err) अणु
			exfat_fs_error(sb,
					"requested for bmap out of range(pos : (%llu) > i_size_aligned(%llu)\n",
					pos, ei->i_size_aligned);
			जाओ unlock_ret;
		पूर्ण
	पूर्ण

	अगर (buffer_delay(bh_result))
		clear_buffer_delay(bh_result);
	map_bh(bh_result, sb, phys);
करोne:
	bh_result->b_size = EXFAT_BLK_TO_B(max_blocks, sb);
unlock_ret:
	mutex_unlock(&sbi->s_lock);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, exfat_get_block);
पूर्ण

अटल व्योम exfat_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, exfat_get_block);
पूर्ण

अटल पूर्णांक exfat_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, exfat_get_block, wbc);
पूर्ण

अटल पूर्णांक exfat_ग_लिखोpages(काष्ठा address_space *mapping,
		काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, exfat_get_block);
पूर्ण

अटल व्योम exfat_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > i_size_पढ़ो(inode)) अणु
		truncate_pagecache(inode, i_size_पढ़ो(inode));
		exfat_truncate(inode, EXFAT_I(inode)->i_size_aligned);
	पूर्ण
पूर्ण

अटल पूर्णांक exfat_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक flags,
		काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
			       exfat_get_block,
			       &EXFAT_I(mapping->host)->i_size_ondisk);

	अगर (ret < 0)
		exfat_ग_लिखो_failed(mapping, pos+len);

	वापस ret;
पूर्ण

अटल पूर्णांक exfat_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक copied,
		काष्ठा page *pagep, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	पूर्णांक err;

	err = generic_ग_लिखो_end(file, mapping, pos, len, copied, pagep, fsdata);

	अगर (EXFAT_I(inode)->i_size_aligned < i_size_पढ़ो(inode)) अणु
		exfat_fs_error(inode->i_sb,
			"invalid size(size(%llu) > aligned(%llu)\n",
			i_size_पढ़ो(inode), EXFAT_I(inode)->i_size_aligned);
		वापस -EIO;
	पूर्ण

	अगर (err < len)
		exfat_ग_लिखो_failed(mapping, pos+len);

	अगर (!(err < 0) && !(ei->attr & ATTR_ARCHIVE)) अणु
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		ei->attr |= ATTR_ARCHIVE;
		mark_inode_dirty(inode);
	पूर्ण

	वापस err;
पूर्ण

अटल sमाप_प्रकार exfat_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा address_space *mapping = iocb->ki_filp->f_mapping;
	काष्ठा inode *inode = mapping->host;
	loff_t size = iocb->ki_pos + iov_iter_count(iter);
	पूर्णांक rw = iov_iter_rw(iter);
	sमाप_प्रकार ret;

	अगर (rw == WRITE) अणु
		/*
		 * FIXME: blockdev_direct_IO() करोesn't use ->ग_लिखो_begin(),
		 * so we need to update the ->i_size_aligned to block boundary.
		 *
		 * But we must fill the reमुख्यing area or hole by nul क्रम
		 * updating ->i_size_aligned
		 *
		 * Return 0, and fallback to normal buffered ग_लिखो.
		 */
		अगर (EXFAT_I(inode)->i_size_aligned < size)
			वापस 0;
	पूर्ण

	/*
	 * Need to use the DIO_LOCKING क्रम aव्योमing the race
	 * condition of exfat_get_block() and ->truncate().
	 */
	ret = blockdev_direct_IO(iocb, inode, iter, exfat_get_block);
	अगर (ret < 0 && (rw & WRITE))
		exfat_ग_लिखो_failed(mapping, size);
	वापस ret;
पूर्ण

अटल sector_t exfat_aop_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	sector_t blocknr;

	/* exfat_get_cluster() assumes the requested blocknr isn't truncated. */
	करोwn_पढ़ो(&EXFAT_I(mapping->host)->truncate_lock);
	blocknr = generic_block_bmap(mapping, block, exfat_get_block);
	up_पढ़ो(&EXFAT_I(mapping->host)->truncate_lock);
	वापस blocknr;
पूर्ण

/*
 * exfat_block_truncate_page() zeroes out a mapping from file offset `from'
 * up to the end of the block which corresponds to `from'.
 * This is required during truncate to physically zeroout the tail end
 * of that block so it करोesn't yield old data अगर the file is later grown.
 * Also, aव्योम causing failure from fsx क्रम हालs of "data past EOF"
 */
पूर्णांक exfat_block_truncate_page(काष्ठा inode *inode, loff_t from)
अणु
	वापस block_truncate_page(inode->i_mapping, from, exfat_get_block);
पूर्ण

अटल स्थिर काष्ठा address_space_operations exfat_aops = अणु
	.पढ़ोpage	= exfat_पढ़ोpage,
	.पढ़ोahead	= exfat_पढ़ोahead,
	.ग_लिखोpage	= exfat_ग_लिखोpage,
	.ग_लिखोpages	= exfat_ग_लिखोpages,
	.ग_लिखो_begin	= exfat_ग_लिखो_begin,
	.ग_लिखो_end	= exfat_ग_लिखो_end,
	.direct_IO	= exfat_direct_IO,
	.bmap		= exfat_aop_bmap
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ exfat_hash(loff_t i_pos)
अणु
	वापस hash_32(i_pos, EXFAT_HASH_BITS);
पूर्ण

व्योम exfat_hash_inode(काष्ठा inode *inode, loff_t i_pos)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);
	काष्ठा hlist_head *head = sbi->inode_hashtable + exfat_hash(i_pos);

	spin_lock(&sbi->inode_hash_lock);
	EXFAT_I(inode)->i_pos = i_pos;
	hlist_add_head(&EXFAT_I(inode)->i_hash_fat, head);
	spin_unlock(&sbi->inode_hash_lock);
पूर्ण

व्योम exfat_unhash_inode(काष्ठा inode *inode)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);

	spin_lock(&sbi->inode_hash_lock);
	hlist_del_init(&EXFAT_I(inode)->i_hash_fat);
	EXFAT_I(inode)->i_pos = 0;
	spin_unlock(&sbi->inode_hash_lock);
पूर्ण

काष्ठा inode *exfat_iget(काष्ठा super_block *sb, loff_t i_pos)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *info;
	काष्ठा hlist_head *head = sbi->inode_hashtable + exfat_hash(i_pos);
	काष्ठा inode *inode = शून्य;

	spin_lock(&sbi->inode_hash_lock);
	hlist_क्रम_each_entry(info, head, i_hash_fat) अणु
		WARN_ON(info->vfs_inode.i_sb != sb);

		अगर (i_pos != info->i_pos)
			जारी;
		inode = igrab(&info->vfs_inode);
		अगर (inode)
			अवरोध;
	पूर्ण
	spin_unlock(&sbi->inode_hash_lock);
	वापस inode;
पूर्ण

/* करोesn't deal with root inode */
अटल पूर्णांक exfat_fill_inode(काष्ठा inode *inode, काष्ठा exfat_dir_entry *info)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	loff_t size = info->size;

	ei->dir = info->dir;
	ei->entry = info->entry;
	ei->attr = info->attr;
	ei->start_clu = info->start_clu;
	ei->flags = info->flags;
	ei->type = info->type;

	ei->version = 0;
	ei->hपूर्णांक_stat.eidx = 0;
	ei->hपूर्णांक_stat.clu = info->start_clu;
	ei->hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;
	ei->hपूर्णांक_bmap.off = EXFAT_खातापूर्ण_CLUSTER;
	ei->i_pos = 0;

	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	inode_inc_iversion(inode);
	inode->i_generation = pअक्रमom_u32();

	अगर (info->attr & ATTR_SUBसूची) अणु /* directory */
		inode->i_generation &= ~1;
		inode->i_mode = exfat_make_mode(sbi, info->attr, 0777);
		inode->i_op = &exfat_dir_inode_operations;
		inode->i_fop = &exfat_dir_operations;
		set_nlink(inode, info->num_subdirs);
	पूर्ण अन्यथा अणु /* regular file */
		inode->i_generation |= 1;
		inode->i_mode = exfat_make_mode(sbi, info->attr, 0777);
		inode->i_op = &exfat_file_inode_operations;
		inode->i_fop = &exfat_file_operations;
		inode->i_mapping->a_ops = &exfat_aops;
		inode->i_mapping->nrpages = 0;
	पूर्ण

	i_size_ग_लिखो(inode, size);

	/* ondisk and aligned size should be aligned with block size */
	अगर (size & (inode->i_sb->s_blocksize - 1)) अणु
		size |= (inode->i_sb->s_blocksize - 1);
		size++;
	पूर्ण

	ei->i_size_aligned = size;
	ei->i_size_ondisk = size;

	exfat_save_attr(inode, info->attr);

	inode->i_blocks = ((i_size_पढ़ो(inode) + (sbi->cluster_size - 1)) &
		~(sbi->cluster_size - 1)) >> inode->i_blkbits;
	inode->i_mसमय = info->mसमय;
	inode->i_स_समय = info->mसमय;
	ei->i_crसमय = info->crसमय;
	inode->i_aसमय = info->aसमय;

	वापस 0;
पूर्ण

काष्ठा inode *exfat_build_inode(काष्ठा super_block *sb,
		काष्ठा exfat_dir_entry *info, loff_t i_pos)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	inode = exfat_iget(sb, i_pos);
	अगर (inode)
		जाओ out;
	inode = new_inode(sb);
	अगर (!inode) अणु
		inode = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	inode->i_ino = iunique(sb, EXFAT_ROOT_INO);
	inode_set_iversion(inode, 1);
	err = exfat_fill_inode(inode, info);
	अगर (err) अणु
		iput(inode);
		inode = ERR_PTR(err);
		जाओ out;
	पूर्ण
	exfat_hash_inode(inode, i_pos);
	insert_inode_hash(inode);
out:
	वापस inode;
पूर्ण

व्योम exfat_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages(&inode->i_data, 0);

	अगर (!inode->i_nlink) अणु
		i_size_ग_लिखो(inode, 0);
		mutex_lock(&EXFAT_SB(inode->i_sb)->s_lock);
		__exfat_truncate(inode, 0);
		mutex_unlock(&EXFAT_SB(inode->i_sb)->s_lock);
	पूर्ण

	invalidate_inode_buffers(inode);
	clear_inode(inode);
	exfat_cache_inval_inode(inode);
	exfat_unhash_inode(inode);
पूर्ण
