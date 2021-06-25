<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/file.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Modअगरied क्रम Amiga FFS fileप्रणाली.
 *
 *  (C) 1992  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 *
 *  affs regular file handling primitives
 */

#समावेश <linux/uपन.स>
#समावेश <linux/blkdev.h>
#समावेश "affs.h"

अटल काष्ठा buffer_head *affs_get_extblock_slow(काष्ठा inode *inode, u32 ext);

अटल पूर्णांक
affs_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	pr_debug("open(%lu,%d)\n",
		 inode->i_ino, atomic_पढ़ो(&AFFS_I(inode)->i_खोलोcnt));
	atomic_inc(&AFFS_I(inode)->i_खोलोcnt);
	वापस 0;
पूर्ण

अटल पूर्णांक
affs_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	pr_debug("release(%lu, %d)\n",
		 inode->i_ino, atomic_पढ़ो(&AFFS_I(inode)->i_खोलोcnt));

	अगर (atomic_dec_and_test(&AFFS_I(inode)->i_खोलोcnt)) अणु
		inode_lock(inode);
		अगर (inode->i_size != AFFS_I(inode)->mmu_निजी)
			affs_truncate(inode);
		affs_मुक्त_pपुनः_स्मृति(inode);
		inode_unlock(inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
affs_grow_extcache(काष्ठा inode *inode, u32 lc_idx)
अणु
	काष्ठा super_block	*sb = inode->i_sb;
	काष्ठा buffer_head	*bh;
	u32 lc_max;
	पूर्णांक i, j, key;

	अगर (!AFFS_I(inode)->i_lc) अणु
		अक्षर *ptr = (अक्षर *)get_zeroed_page(GFP_NOFS);
		अगर (!ptr)
			वापस -ENOMEM;
		AFFS_I(inode)->i_lc = (u32 *)ptr;
		AFFS_I(inode)->i_ac = (काष्ठा affs_ext_key *)(ptr + AFFS_CACHE_SIZE / 2);
	पूर्ण

	lc_max = AFFS_LC_SIZE << AFFS_I(inode)->i_lc_shअगरt;

	अगर (AFFS_I(inode)->i_extcnt > lc_max) अणु
		u32 lc_shअगरt, lc_mask, पंचांगp, off;

		/* need to recalculate linear cache, start from old size */
		lc_shअगरt = AFFS_I(inode)->i_lc_shअगरt;
		पंचांगp = (AFFS_I(inode)->i_extcnt / AFFS_LC_SIZE) >> lc_shअगरt;
		क्रम (; पंचांगp; पंचांगp >>= 1)
			lc_shअगरt++;
		lc_mask = (1 << lc_shअगरt) - 1;

		/* fix idx and old size to new shअगरt */
		lc_idx >>= (lc_shअगरt - AFFS_I(inode)->i_lc_shअगरt);
		AFFS_I(inode)->i_lc_size >>= (lc_shअगरt - AFFS_I(inode)->i_lc_shअगरt);

		/* first shrink old cache to make more space */
		off = 1 << (lc_shअगरt - AFFS_I(inode)->i_lc_shअगरt);
		क्रम (i = 1, j = off; j < AFFS_LC_SIZE; i++, j += off)
			AFFS_I(inode)->i_ac[i] = AFFS_I(inode)->i_ac[j];

		AFFS_I(inode)->i_lc_shअगरt = lc_shअगरt;
		AFFS_I(inode)->i_lc_mask = lc_mask;
	पूर्ण

	/* fill cache to the needed index */
	i = AFFS_I(inode)->i_lc_size;
	AFFS_I(inode)->i_lc_size = lc_idx + 1;
	क्रम (; i <= lc_idx; i++) अणु
		अगर (!i) अणु
			AFFS_I(inode)->i_lc[0] = inode->i_ino;
			जारी;
		पूर्ण
		key = AFFS_I(inode)->i_lc[i - 1];
		j = AFFS_I(inode)->i_lc_mask + 1;
		// unlock cache
		क्रम (; j > 0; j--) अणु
			bh = affs_bपढ़ो(sb, key);
			अगर (!bh)
				जाओ err;
			key = be32_to_cpu(AFFS_TAIL(sb, bh)->extension);
			affs_brअन्यथा(bh);
		पूर्ण
		// lock cache
		AFFS_I(inode)->i_lc[i] = key;
	पूर्ण

	वापस 0;

err:
	// lock cache
	वापस -EIO;
पूर्ण

अटल काष्ठा buffer_head *
affs_alloc_extblock(काष्ठा inode *inode, काष्ठा buffer_head *bh, u32 ext)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *new_bh;
	u32 blocknr, पंचांगp;

	blocknr = affs_alloc_block(inode, bh->b_blocknr);
	अगर (!blocknr)
		वापस ERR_PTR(-ENOSPC);

	new_bh = affs_getzeroblk(sb, blocknr);
	अगर (!new_bh) अणु
		affs_मुक्त_block(sb, blocknr);
		वापस ERR_PTR(-EIO);
	पूर्ण

	AFFS_HEAD(new_bh)->ptype = cpu_to_be32(T_LIST);
	AFFS_HEAD(new_bh)->key = cpu_to_be32(blocknr);
	AFFS_TAIL(sb, new_bh)->stype = cpu_to_be32(ST_खाता);
	AFFS_TAIL(sb, new_bh)->parent = cpu_to_be32(inode->i_ino);
	affs_fix_checksum(sb, new_bh);

	mark_buffer_dirty_inode(new_bh, inode);

	पंचांगp = be32_to_cpu(AFFS_TAIL(sb, bh)->extension);
	अगर (पंचांगp)
		affs_warning(sb, "alloc_ext", "previous extension set (%x)", पंचांगp);
	AFFS_TAIL(sb, bh)->extension = cpu_to_be32(blocknr);
	affs_adjust_checksum(bh, blocknr - पंचांगp);
	mark_buffer_dirty_inode(bh, inode);

	AFFS_I(inode)->i_extcnt++;
	mark_inode_dirty(inode);

	वापस new_bh;
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
affs_get_extblock(काष्ठा inode *inode, u32 ext)
अणु
	/* अंतरभूत the simplest हाल: same extended block as last समय */
	काष्ठा buffer_head *bh = AFFS_I(inode)->i_ext_bh;
	अगर (ext == AFFS_I(inode)->i_ext_last)
		get_bh(bh);
	अन्यथा
		/* we have to करो more (not अंतरभूतd) */
		bh = affs_get_extblock_slow(inode, ext);

	वापस bh;
पूर्ण

अटल काष्ठा buffer_head *
affs_get_extblock_slow(काष्ठा inode *inode, u32 ext)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh;
	u32 ext_key;
	u32 lc_idx, lc_off, ac_idx;
	u32 पंचांगp, idx;

	अगर (ext == AFFS_I(inode)->i_ext_last + 1) अणु
		/* पढ़ो the next extended block from the current one */
		bh = AFFS_I(inode)->i_ext_bh;
		ext_key = be32_to_cpu(AFFS_TAIL(sb, bh)->extension);
		अगर (ext < AFFS_I(inode)->i_extcnt)
			जाओ पढ़ो_ext;
		BUG_ON(ext > AFFS_I(inode)->i_extcnt);
		bh = affs_alloc_extblock(inode, bh, ext);
		अगर (IS_ERR(bh))
			वापस bh;
		जाओ store_ext;
	पूर्ण

	अगर (ext == 0) अणु
		/* we seek back to the file header block */
		ext_key = inode->i_ino;
		जाओ पढ़ो_ext;
	पूर्ण

	अगर (ext >= AFFS_I(inode)->i_extcnt) अणु
		काष्ठा buffer_head *prev_bh;

		/* allocate a new extended block */
		BUG_ON(ext > AFFS_I(inode)->i_extcnt);

		/* get previous extended block */
		prev_bh = affs_get_extblock(inode, ext - 1);
		अगर (IS_ERR(prev_bh))
			वापस prev_bh;
		bh = affs_alloc_extblock(inode, prev_bh, ext);
		affs_brअन्यथा(prev_bh);
		अगर (IS_ERR(bh))
			वापस bh;
		जाओ store_ext;
	पूर्ण

again:
	/* check अगर there is an extended cache and whether it's large enough */
	lc_idx = ext >> AFFS_I(inode)->i_lc_shअगरt;
	lc_off = ext & AFFS_I(inode)->i_lc_mask;

	अगर (lc_idx >= AFFS_I(inode)->i_lc_size) अणु
		पूर्णांक err;

		err = affs_grow_extcache(inode, lc_idx);
		अगर (err)
			वापस ERR_PTR(err);
		जाओ again;
	पूर्ण

	/* every n'th key we find in the linear cache */
	अगर (!lc_off) अणु
		ext_key = AFFS_I(inode)->i_lc[lc_idx];
		जाओ पढ़ो_ext;
	पूर्ण

	/* maybe it's still in the associative cache */
	ac_idx = (ext - lc_idx - 1) & AFFS_AC_MASK;
	अगर (AFFS_I(inode)->i_ac[ac_idx].ext == ext) अणु
		ext_key = AFFS_I(inode)->i_ac[ac_idx].key;
		जाओ पढ़ो_ext;
	पूर्ण

	/* try to find one of the previous extended blocks */
	पंचांगp = ext;
	idx = ac_idx;
	जबतक (--पंचांगp, --lc_off > 0) अणु
		idx = (idx - 1) & AFFS_AC_MASK;
		अगर (AFFS_I(inode)->i_ac[idx].ext == पंचांगp) अणु
			ext_key = AFFS_I(inode)->i_ac[idx].key;
			जाओ find_ext;
		पूर्ण
	पूर्ण

	/* fall back to the linear cache */
	ext_key = AFFS_I(inode)->i_lc[lc_idx];
find_ext:
	/* पढ़ो all extended blocks until we find the one we need */
	//unlock cache
	करो अणु
		bh = affs_bपढ़ो(sb, ext_key);
		अगर (!bh)
			जाओ err_bपढ़ो;
		ext_key = be32_to_cpu(AFFS_TAIL(sb, bh)->extension);
		affs_brअन्यथा(bh);
		पंचांगp++;
	पूर्ण जबतक (पंचांगp < ext);
	//lock cache

	/* store it in the associative cache */
	// recalculate ac_idx?
	AFFS_I(inode)->i_ac[ac_idx].ext = ext;
	AFFS_I(inode)->i_ac[ac_idx].key = ext_key;

पढ़ो_ext:
	/* finally पढ़ो the right extended block */
	//unlock cache
	bh = affs_bपढ़ो(sb, ext_key);
	अगर (!bh)
		जाओ err_bपढ़ो;
	//lock cache

store_ext:
	/* release old cached extended block and store the new one */
	affs_brअन्यथा(AFFS_I(inode)->i_ext_bh);
	AFFS_I(inode)->i_ext_last = ext;
	AFFS_I(inode)->i_ext_bh = bh;
	get_bh(bh);

	वापस bh;

err_bपढ़ो:
	affs_brअन्यथा(bh);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल पूर्णांक
affs_get_block(काष्ठा inode *inode, sector_t block, काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा super_block	*sb = inode->i_sb;
	काष्ठा buffer_head	*ext_bh;
	u32			 ext;

	pr_debug("%s(%lu, %llu)\n", __func__, inode->i_ino,
		 (अचिन्हित दीर्घ दीर्घ)block);

	BUG_ON(block > (sector_t)0x7fffffffUL);

	अगर (block >= AFFS_I(inode)->i_blkcnt) अणु
		अगर (block > AFFS_I(inode)->i_blkcnt || !create)
			जाओ err_big;
	पूर्ण अन्यथा
		create = 0;

	//lock cache
	affs_lock_ext(inode);

	ext = (u32)block / AFFS_SB(sb)->s_hashsize;
	block -= ext * AFFS_SB(sb)->s_hashsize;
	ext_bh = affs_get_extblock(inode, ext);
	अगर (IS_ERR(ext_bh))
		जाओ err_ext;
	map_bh(bh_result, sb, (sector_t)be32_to_cpu(AFFS_BLOCK(sb, ext_bh, block)));

	अगर (create) अणु
		u32 blocknr = affs_alloc_block(inode, ext_bh->b_blocknr);
		अगर (!blocknr)
			जाओ err_alloc;
		set_buffer_new(bh_result);
		AFFS_I(inode)->mmu_निजी += AFFS_SB(sb)->s_data_blksize;
		AFFS_I(inode)->i_blkcnt++;

		/* store new block */
		अगर (bh_result->b_blocknr)
			affs_warning(sb, "get_block",
				     "block already set (%llx)",
				     (अचिन्हित दीर्घ दीर्घ)bh_result->b_blocknr);
		AFFS_BLOCK(sb, ext_bh, block) = cpu_to_be32(blocknr);
		AFFS_HEAD(ext_bh)->block_count = cpu_to_be32(block + 1);
		affs_adjust_checksum(ext_bh, blocknr - bh_result->b_blocknr + 1);
		bh_result->b_blocknr = blocknr;

		अगर (!block) अणु
			/* insert first block पूर्णांकo header block */
			u32 पंचांगp = be32_to_cpu(AFFS_HEAD(ext_bh)->first_data);
			अगर (पंचांगp)
				affs_warning(sb, "get_block", "first block already set (%d)", पंचांगp);
			AFFS_HEAD(ext_bh)->first_data = cpu_to_be32(blocknr);
			affs_adjust_checksum(ext_bh, blocknr - पंचांगp);
		पूर्ण
	पूर्ण

	affs_brअन्यथा(ext_bh);
	//unlock cache
	affs_unlock_ext(inode);
	वापस 0;

err_big:
	affs_error(inode->i_sb, "get_block", "strange block request %llu",
		   (अचिन्हित दीर्घ दीर्घ)block);
	वापस -EIO;
err_ext:
	// unlock cache
	affs_unlock_ext(inode);
	वापस PTR_ERR(ext_bh);
err_alloc:
	brअन्यथा(ext_bh);
	clear_buffer_mapped(bh_result);
	bh_result->b_bdev = शून्य;
	// unlock cache
	affs_unlock_ext(inode);
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक affs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, affs_get_block, wbc);
पूर्ण

अटल पूर्णांक affs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, affs_get_block);
पूर्ण

अटल व्योम affs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		affs_truncate(inode);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
affs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	sमाप_प्रकार ret;

	अगर (iov_iter_rw(iter) == WRITE) अणु
		loff_t size = offset + count;

		अगर (AFFS_I(inode)->mmu_निजी < size)
			वापस 0;
	पूर्ण

	ret = blockdev_direct_IO(iocb, inode, iter, affs_get_block);
	अगर (ret < 0 && iov_iter_rw(iter) == WRITE)
		affs_ग_लिखो_failed(mapping, offset + count);
	वापस ret;
पूर्ण

अटल पूर्णांक affs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
				affs_get_block,
				&AFFS_I(mapping->host)->mmu_निजी);
	अगर (unlikely(ret))
		affs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल पूर्णांक affs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			  loff_t pos, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक copied,
			  काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret;

	ret = generic_ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);

	/* Clear Archived bit on file ग_लिखोs, as AmigaOS would करो */
	अगर (AFFS_I(inode)->i_protect & FIBF_ARCHIVED) अणु
		AFFS_I(inode)->i_protect &= ~FIBF_ARCHIVED;
		mark_inode_dirty(inode);
	पूर्ण

	वापस ret;
पूर्ण

अटल sector_t _affs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,affs_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations affs_aops = अणु
	.पढ़ोpage = affs_पढ़ोpage,
	.ग_लिखोpage = affs_ग_लिखोpage,
	.ग_लिखो_begin = affs_ग_लिखो_begin,
	.ग_लिखो_end = affs_ग_लिखो_end,
	.direct_IO = affs_direct_IO,
	.bmap = _affs_bmap
पूर्ण;

अटल अंतरभूत काष्ठा buffer_head *
affs_bपढ़ो_ino(काष्ठा inode *inode, पूर्णांक block, पूर्णांक create)
अणु
	काष्ठा buffer_head *bh, पंचांगp_bh;
	पूर्णांक err;

	पंचांगp_bh.b_state = 0;
	err = affs_get_block(inode, block, &पंचांगp_bh, create);
	अगर (!err) अणु
		bh = affs_bपढ़ो(inode->i_sb, पंचांगp_bh.b_blocknr);
		अगर (bh) अणु
			bh->b_state |= पंचांगp_bh.b_state;
			वापस bh;
		पूर्ण
		err = -EIO;
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
affs_getzeroblk_ino(काष्ठा inode *inode, पूर्णांक block)
अणु
	काष्ठा buffer_head *bh, पंचांगp_bh;
	पूर्णांक err;

	पंचांगp_bh.b_state = 0;
	err = affs_get_block(inode, block, &पंचांगp_bh, 1);
	अगर (!err) अणु
		bh = affs_getzeroblk(inode->i_sb, पंचांगp_bh.b_blocknr);
		अगर (bh) अणु
			bh->b_state |= पंचांगp_bh.b_state;
			वापस bh;
		पूर्ण
		err = -EIO;
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
affs_getemptyblk_ino(काष्ठा inode *inode, पूर्णांक block)
अणु
	काष्ठा buffer_head *bh, पंचांगp_bh;
	पूर्णांक err;

	पंचांगp_bh.b_state = 0;
	err = affs_get_block(inode, block, &पंचांगp_bh, 1);
	अगर (!err) अणु
		bh = affs_getemptyblk(inode->i_sb, पंचांगp_bh.b_blocknr);
		अगर (bh) अणु
			bh->b_state |= पंचांगp_bh.b_state;
			वापस bh;
		पूर्ण
		err = -EIO;
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
affs_करो_पढ़ोpage_ofs(काष्ठा page *page, अचिन्हित to, पूर्णांक create)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh;
	अक्षर *data;
	अचिन्हित pos = 0;
	u32 bidx, boff, bsize;
	u32 पंचांगp;

	pr_debug("%s(%lu, %ld, 0, %d)\n", __func__, inode->i_ino,
		 page->index, to);
	BUG_ON(to > PAGE_SIZE);
	bsize = AFFS_SB(sb)->s_data_blksize;
	पंचांगp = page->index << PAGE_SHIFT;
	bidx = पंचांगp / bsize;
	boff = पंचांगp % bsize;

	जबतक (pos < to) अणु
		bh = affs_bपढ़ो_ino(inode, bidx, create);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		पंचांगp = min(bsize - boff, to - pos);
		BUG_ON(pos + पंचांगp > to || पंचांगp > bsize);
		data = kmap_atomic(page);
		स_नकल(data + pos, AFFS_DATA(bh) + boff, पंचांगp);
		kunmap_atomic(data);
		affs_brअन्यथा(bh);
		bidx++;
		pos += पंचांगp;
		boff = 0;
	पूर्ण
	flush_dcache_page(page);
	वापस 0;
पूर्ण

अटल पूर्णांक
affs_extent_file_ofs(काष्ठा inode *inode, u32 newsize)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh, *prev_bh;
	u32 bidx, boff;
	u32 size, bsize;
	u32 पंचांगp;

	pr_debug("%s(%lu, %d)\n", __func__, inode->i_ino, newsize);
	bsize = AFFS_SB(sb)->s_data_blksize;
	bh = शून्य;
	size = AFFS_I(inode)->mmu_निजी;
	bidx = size / bsize;
	boff = size % bsize;
	अगर (boff) अणु
		bh = affs_bपढ़ो_ino(inode, bidx, 0);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
		पंचांगp = min(bsize - boff, newsize - size);
		BUG_ON(boff + पंचांगp > bsize || पंचांगp > bsize);
		स_रखो(AFFS_DATA(bh) + boff, 0, पंचांगp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, पंचांगp);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		size += पंचांगp;
		bidx++;
	पूर्ण अन्यथा अगर (bidx) अणु
		bh = affs_bपढ़ो_ino(inode, bidx - 1, 0);
		अगर (IS_ERR(bh))
			वापस PTR_ERR(bh);
	पूर्ण

	जबतक (size < newsize) अणु
		prev_bh = bh;
		bh = affs_getzeroblk_ino(inode, bidx);
		अगर (IS_ERR(bh))
			जाओ out;
		पंचांगp = min(bsize, newsize - size);
		BUG_ON(पंचांगp > bsize);
		AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
		AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
		AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
		AFFS_DATA_HEAD(bh)->size = cpu_to_be32(पंचांगp);
		affs_fix_checksum(sb, bh);
		bh->b_state &= ~(1UL << BH_New);
		mark_buffer_dirty_inode(bh, inode);
		अगर (prev_bh) अणु
			u32 पंचांगp_next = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);

			अगर (पंचांगp_next)
				affs_warning(sb, "extent_file_ofs",
					     "next block already set for %d (%d)",
					     bidx, पंचांगp_next);
			AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
			affs_adjust_checksum(prev_bh, bh->b_blocknr - पंचांगp_next);
			mark_buffer_dirty_inode(prev_bh, inode);
			affs_brअन्यथा(prev_bh);
		पूर्ण
		size += bsize;
		bidx++;
	पूर्ण
	affs_brअन्यथा(bh);
	inode->i_size = AFFS_I(inode)->mmu_निजी = newsize;
	वापस 0;

out:
	inode->i_size = AFFS_I(inode)->mmu_निजी = newsize;
	वापस PTR_ERR(bh);
पूर्ण

अटल पूर्णांक
affs_पढ़ोpage_ofs(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	u32 to;
	पूर्णांक err;

	pr_debug("%s(%lu, %ld)\n", __func__, inode->i_ino, page->index);
	to = PAGE_SIZE;
	अगर (((page->index + 1) << PAGE_SHIFT) > inode->i_size) अणु
		to = inode->i_size & ~PAGE_MASK;
		स_रखो(page_address(page) + to, 0, PAGE_SIZE - to);
	पूर्ण

	err = affs_करो_पढ़ोpage_ofs(page, to, 0);
	अगर (!err)
		SetPageUptodate(page);
	unlock_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक affs_ग_लिखो_begin_ofs(काष्ठा file *file, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा page *page;
	pgoff_t index;
	पूर्णांक err = 0;

	pr_debug("%s(%lu, %llu, %llu)\n", __func__, inode->i_ino, pos,
		 pos + len);
	अगर (pos > AFFS_I(inode)->mmu_निजी) अणु
		/* XXX: this probably leaves a too-big i_size in हाल of
		 * failure. Should really be updating i_size at ग_लिखो_end समय
		 */
		err = affs_extent_file_ofs(inode, pos);
		अगर (err)
			वापस err;
	पूर्ण

	index = pos >> PAGE_SHIFT;
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;

	अगर (PageUptodate(page))
		वापस 0;

	/* XXX: inefficient but safe in the face of लघु ग_लिखोs */
	err = affs_करो_पढ़ोpage_ofs(page, PAGE_SIZE, 1);
	अगर (err) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक affs_ग_लिखो_end_ofs(काष्ठा file *file, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित copied,
				काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *bh, *prev_bh;
	अक्षर *data;
	u32 bidx, boff, bsize;
	अचिन्हित from, to;
	u32 पंचांगp;
	पूर्णांक written;

	from = pos & (PAGE_SIZE - 1);
	to = from + len;
	/*
	 * XXX: not sure अगर this can handle लघु copies (len < copied), but
	 * we करोn't have to, because the page should always be uptodate here,
	 * due to ग_लिखो_begin.
	 */

	pr_debug("%s(%lu, %llu, %llu)\n", __func__, inode->i_ino, pos,
		 pos + len);
	bsize = AFFS_SB(sb)->s_data_blksize;
	data = page_address(page);

	bh = शून्य;
	written = 0;
	पंचांगp = (page->index << PAGE_SHIFT) + from;
	bidx = पंचांगp / bsize;
	boff = पंचांगp % bsize;
	अगर (boff) अणु
		bh = affs_bपढ़ो_ino(inode, bidx, 0);
		अगर (IS_ERR(bh)) अणु
			written = PTR_ERR(bh);
			जाओ err_first_bh;
		पूर्ण
		पंचांगp = min(bsize - boff, to - from);
		BUG_ON(boff + पंचांगp > bsize || पंचांगp > bsize);
		स_नकल(AFFS_DATA(bh) + boff, data + from, पंचांगp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, पंचांगp);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += पंचांगp;
		from += पंचांगp;
		bidx++;
	पूर्ण अन्यथा अगर (bidx) अणु
		bh = affs_bपढ़ो_ino(inode, bidx - 1, 0);
		अगर (IS_ERR(bh)) अणु
			written = PTR_ERR(bh);
			जाओ err_first_bh;
		पूर्ण
	पूर्ण
	जबतक (from + bsize <= to) अणु
		prev_bh = bh;
		bh = affs_getemptyblk_ino(inode, bidx);
		अगर (IS_ERR(bh))
			जाओ err_bh;
		स_नकल(AFFS_DATA(bh), data + from, bsize);
		अगर (buffer_new(bh)) अणु
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(bsize);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UL << BH_New);
			अगर (prev_bh) अणु
				u32 पंचांगp_next = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);

				अगर (पंचांगp_next)
					affs_warning(sb, "commit_write_ofs",
						     "next block already set for %d (%d)",
						     bidx, पंचांगp_next);
				AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
				affs_adjust_checksum(prev_bh, bh->b_blocknr - पंचांगp_next);
				mark_buffer_dirty_inode(prev_bh, inode);
			पूर्ण
		पूर्ण
		affs_brअन्यथा(prev_bh);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += bsize;
		from += bsize;
		bidx++;
	पूर्ण
	अगर (from < to) अणु
		prev_bh = bh;
		bh = affs_bपढ़ो_ino(inode, bidx, 1);
		अगर (IS_ERR(bh))
			जाओ err_bh;
		पंचांगp = min(bsize, to - from);
		BUG_ON(पंचांगp > bsize);
		स_नकल(AFFS_DATA(bh), data + from, पंचांगp);
		अगर (buffer_new(bh)) अणु
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(पंचांगp);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UL << BH_New);
			अगर (prev_bh) अणु
				u32 पंचांगp_next = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);

				अगर (पंचांगp_next)
					affs_warning(sb, "commit_write_ofs",
						     "next block already set for %d (%d)",
						     bidx, पंचांगp_next);
				AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
				affs_adjust_checksum(prev_bh, bh->b_blocknr - पंचांगp_next);
				mark_buffer_dirty_inode(prev_bh, inode);
			पूर्ण
		पूर्ण अन्यथा अगर (be32_to_cpu(AFFS_DATA_HEAD(bh)->size) < पंचांगp)
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(पंचांगp);
		affs_brअन्यथा(prev_bh);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += पंचांगp;
		from += पंचांगp;
		bidx++;
	पूर्ण
	SetPageUptodate(page);

करोne:
	affs_brअन्यथा(bh);
	पंचांगp = (page->index << PAGE_SHIFT) + from;
	अगर (पंचांगp > inode->i_size)
		inode->i_size = AFFS_I(inode)->mmu_निजी = पंचांगp;

	/* Clear Archived bit on file ग_लिखोs, as AmigaOS would करो */
	अगर (AFFS_I(inode)->i_protect & FIBF_ARCHIVED) अणु
		AFFS_I(inode)->i_protect &= ~FIBF_ARCHIVED;
		mark_inode_dirty(inode);
	पूर्ण

err_first_bh:
	unlock_page(page);
	put_page(page);

	वापस written;

err_bh:
	bh = prev_bh;
	अगर (!written)
		written = PTR_ERR(bh);
	जाओ करोne;
पूर्ण

स्थिर काष्ठा address_space_operations affs_aops_ofs = अणु
	.पढ़ोpage = affs_पढ़ोpage_ofs,
	//.ग_लिखोpage = affs_ग_लिखोpage_ofs,
	.ग_लिखो_begin = affs_ग_लिखो_begin_ofs,
	.ग_लिखो_end = affs_ग_लिखो_end_ofs
पूर्ण;

/* Free any pपुनः_स्मृतिated blocks. */

व्योम
affs_मुक्त_pपुनः_स्मृति(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	pr_debug("free_prealloc(ino=%lu)\n", inode->i_ino);

	जबतक (AFFS_I(inode)->i_pa_cnt) अणु
		AFFS_I(inode)->i_pa_cnt--;
		affs_मुक्त_block(sb, ++AFFS_I(inode)->i_lastalloc);
	पूर्ण
पूर्ण

/* Truncate (or enlarge) a file to the requested size. */

व्योम
affs_truncate(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	u32 ext, ext_key;
	u32 last_blk, blkcnt, blk;
	u32 size;
	काष्ठा buffer_head *ext_bh;
	पूर्णांक i;

	pr_debug("truncate(inode=%lu, oldsize=%llu, newsize=%llu)\n",
		 inode->i_ino, AFFS_I(inode)->mmu_निजी, inode->i_size);

	last_blk = 0;
	ext = 0;
	अगर (inode->i_size) अणु
		last_blk = ((u32)inode->i_size - 1) / AFFS_SB(sb)->s_data_blksize;
		ext = last_blk / AFFS_SB(sb)->s_hashsize;
	पूर्ण

	अगर (inode->i_size > AFFS_I(inode)->mmu_निजी) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा page *page;
		व्योम *fsdata;
		loff_t isize = inode->i_size;
		पूर्णांक res;

		res = mapping->a_ops->ग_लिखो_begin(शून्य, mapping, isize, 0, 0, &page, &fsdata);
		अगर (!res)
			res = mapping->a_ops->ग_लिखो_end(शून्य, mapping, isize, 0, 0, page, fsdata);
		अन्यथा
			inode->i_size = AFFS_I(inode)->mmu_निजी;
		mark_inode_dirty(inode);
		वापस;
	पूर्ण अन्यथा अगर (inode->i_size == AFFS_I(inode)->mmu_निजी)
		वापस;

	// lock cache
	ext_bh = affs_get_extblock(inode, ext);
	अगर (IS_ERR(ext_bh)) अणु
		affs_warning(sb, "truncate",
			     "unexpected read error for ext block %u (%ld)",
			     ext, PTR_ERR(ext_bh));
		वापस;
	पूर्ण
	अगर (AFFS_I(inode)->i_lc) अणु
		/* clear linear cache */
		i = (ext + 1) >> AFFS_I(inode)->i_lc_shअगरt;
		अगर (AFFS_I(inode)->i_lc_size > i) अणु
			AFFS_I(inode)->i_lc_size = i;
			क्रम (; i < AFFS_LC_SIZE; i++)
				AFFS_I(inode)->i_lc[i] = 0;
		पूर्ण
		/* clear associative cache */
		क्रम (i = 0; i < AFFS_AC_SIZE; i++)
			अगर (AFFS_I(inode)->i_ac[i].ext >= ext)
				AFFS_I(inode)->i_ac[i].ext = 0;
	पूर्ण
	ext_key = be32_to_cpu(AFFS_TAIL(sb, ext_bh)->extension);

	blkcnt = AFFS_I(inode)->i_blkcnt;
	i = 0;
	blk = last_blk;
	अगर (inode->i_size) अणु
		i = last_blk % AFFS_SB(sb)->s_hashsize + 1;
		blk++;
	पूर्ण अन्यथा
		AFFS_HEAD(ext_bh)->first_data = 0;
	AFFS_HEAD(ext_bh)->block_count = cpu_to_be32(i);
	size = AFFS_SB(sb)->s_hashsize;
	अगर (size > blkcnt - blk + i)
		size = blkcnt - blk + i;
	क्रम (; i < size; i++, blk++) अणु
		affs_मुक्त_block(sb, be32_to_cpu(AFFS_BLOCK(sb, ext_bh, i)));
		AFFS_BLOCK(sb, ext_bh, i) = 0;
	पूर्ण
	AFFS_TAIL(sb, ext_bh)->extension = 0;
	affs_fix_checksum(sb, ext_bh);
	mark_buffer_dirty_inode(ext_bh, inode);
	affs_brअन्यथा(ext_bh);

	अगर (inode->i_size) अणु
		AFFS_I(inode)->i_blkcnt = last_blk + 1;
		AFFS_I(inode)->i_extcnt = ext + 1;
		अगर (affs_test_opt(AFFS_SB(sb)->s_flags, SF_OFS)) अणु
			काष्ठा buffer_head *bh = affs_bपढ़ो_ino(inode, last_blk, 0);
			u32 पंचांगp;
			अगर (IS_ERR(bh)) अणु
				affs_warning(sb, "truncate",
					     "unexpected read error for last block %u (%ld)",
					     ext, PTR_ERR(bh));
				वापस;
			पूर्ण
			पंचांगp = be32_to_cpu(AFFS_DATA_HEAD(bh)->next);
			AFFS_DATA_HEAD(bh)->next = 0;
			affs_adjust_checksum(bh, -पंचांगp);
			affs_brअन्यथा(bh);
		पूर्ण
	पूर्ण अन्यथा अणु
		AFFS_I(inode)->i_blkcnt = 0;
		AFFS_I(inode)->i_extcnt = 1;
	पूर्ण
	AFFS_I(inode)->mmu_निजी = inode->i_size;
	// unlock cache

	जबतक (ext_key) अणु
		ext_bh = affs_bपढ़ो(sb, ext_key);
		size = AFFS_SB(sb)->s_hashsize;
		अगर (size > blkcnt - blk)
			size = blkcnt - blk;
		क्रम (i = 0; i < size; i++, blk++)
			affs_मुक्त_block(sb, be32_to_cpu(AFFS_BLOCK(sb, ext_bh, i)));
		affs_मुक्त_block(sb, ext_key);
		ext_key = be32_to_cpu(AFFS_TAIL(sb, ext_bh)->extension);
		affs_brअन्यथा(ext_bh);
	पूर्ण
	affs_मुक्त_pपुनः_स्मृति(inode);
पूर्ण

पूर्णांक affs_file_fsync(काष्ठा file *filp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक ret, err;

	err = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (err)
		वापस err;

	inode_lock(inode);
	ret = ग_लिखो_inode_now(inode, 0);
	err = sync_blockdev(inode->i_sb->s_bdev);
	अगर (!ret)
		ret = err;
	inode_unlock(inode);
	वापस ret;
पूर्ण
स्थिर काष्ठा file_operations affs_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.खोलो		= affs_file_खोलो,
	.release	= affs_file_release,
	.fsync		= affs_file_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

स्थिर काष्ठा inode_operations affs_file_inode_operations = अणु
	.setattr	= affs_notअगरy_change,
पूर्ण;
