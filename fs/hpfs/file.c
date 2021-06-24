<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/file.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  file VFS functions
 */

#समावेश "hpfs_fn.h"
#समावेश <linux/mpage.h>
#समावेश <linux/fiemap.h>

#घोषणा BLOCKS(size) (((size) + 511) >> 9)

अटल पूर्णांक hpfs_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	hpfs_lock(inode->i_sb);
	hpfs_ग_लिखो_अगर_changed(inode);
	hpfs_unlock(inode->i_sb);
	वापस 0;
पूर्ण

पूर्णांक hpfs_file_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक ret;

	ret = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (ret)
		वापस ret;
	वापस sync_blockdev(inode->i_sb->s_bdev);
पूर्ण

/*
 * generic_file_पढ़ो often calls bmap with non-existing sector,
 * so we must ignore such errors.
 */

अटल secno hpfs_bmap(काष्ठा inode *inode, अचिन्हित file_secno, अचिन्हित *n_secs)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	अचिन्हित n, disk_secno;
	काष्ठा fnode *fnode;
	काष्ठा buffer_head *bh;
	अगर (BLOCKS(hpfs_i(inode)->mmu_निजी) <= file_secno) वापस 0;
	n = file_secno - hpfs_inode->i_file_sec;
	अगर (n < hpfs_inode->i_n_secs) अणु
		*n_secs = hpfs_inode->i_n_secs - n;
		वापस hpfs_inode->i_disk_sec + n;
	पूर्ण
	अगर (!(fnode = hpfs_map_fnode(inode->i_sb, inode->i_ino, &bh))) वापस 0;
	disk_secno = hpfs_bplus_lookup(inode->i_sb, inode, &fnode->btree, file_secno, bh);
	अगर (disk_secno == -1) वापस 0;
	अगर (hpfs_chk_sectors(inode->i_sb, disk_secno, 1, "bmap")) वापस 0;
	n = file_secno - hpfs_inode->i_file_sec;
	अगर (n < hpfs_inode->i_n_secs) अणु
		*n_secs = hpfs_inode->i_n_secs - n;
		वापस hpfs_inode->i_disk_sec + n;
	पूर्ण
	*n_secs = 1;
	वापस disk_secno;
पूर्ण

व्योम hpfs_truncate(काष्ठा inode *i)
अणु
	अगर (IS_IMMUTABLE(i)) वापस /*-EPERM*/;
	hpfs_lock_निश्चित(i->i_sb);

	hpfs_i(i)->i_n_secs = 0;
	i->i_blocks = 1 + ((i->i_size + 511) >> 9);
	hpfs_i(i)->mmu_निजी = i->i_size;
	hpfs_truncate_btree(i->i_sb, i->i_ino, 1, ((i->i_size + 511) >> 9));
	hpfs_ग_लिखो_inode(i);
	hpfs_i(i)->i_n_secs = 0;
पूर्ण

अटल पूर्णांक hpfs_get_block(काष्ठा inode *inode, sector_t iblock, काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक r;
	secno s;
	अचिन्हित n_secs;
	hpfs_lock(inode->i_sb);
	s = hpfs_bmap(inode, iblock, &n_secs);
	अगर (s) अणु
		अगर (bh_result->b_size >> 9 < n_secs)
			n_secs = bh_result->b_size >> 9;
		n_secs = hpfs_search_hotfix_map_क्रम_range(inode->i_sb, s, n_secs);
		अगर (unlikely(!n_secs)) अणु
			s = hpfs_search_hotfix_map(inode->i_sb, s);
			n_secs = 1;
		पूर्ण
		map_bh(bh_result, inode->i_sb, s);
		bh_result->b_size = n_secs << 9;
		जाओ ret_0;
	पूर्ण
	अगर (!create) जाओ ret_0;
	अगर (iblock<<9 != hpfs_i(inode)->mmu_निजी) अणु
		BUG();
		r = -EIO;
		जाओ ret_r;
	पूर्ण
	अगर ((s = hpfs_add_sector_to_btree(inode->i_sb, inode->i_ino, 1, inode->i_blocks - 1)) == -1) अणु
		hpfs_truncate_btree(inode->i_sb, inode->i_ino, 1, inode->i_blocks - 1);
		r = -ENOSPC;
		जाओ ret_r;
	पूर्ण
	inode->i_blocks++;
	hpfs_i(inode)->mmu_निजी += 512;
	set_buffer_new(bh_result);
	map_bh(bh_result, inode->i_sb, hpfs_search_hotfix_map(inode->i_sb, s));
	ret_0:
	r = 0;
	ret_r:
	hpfs_unlock(inode->i_sb);
	वापस r;
पूर्ण

अटल पूर्णांक hpfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, hpfs_get_block);
पूर्ण

अटल पूर्णांक hpfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, hpfs_get_block, wbc);
पूर्ण

अटल व्योम hpfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, hpfs_get_block);
पूर्ण

अटल पूर्णांक hpfs_ग_लिखोpages(काष्ठा address_space *mapping,
			   काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, hpfs_get_block);
पूर्ण

अटल व्योम hpfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	hpfs_lock(inode->i_sb);

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		hpfs_truncate(inode);
	पूर्ण

	hpfs_unlock(inode->i_sb);
पूर्ण

अटल पूर्णांक hpfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
				hpfs_get_block,
				&hpfs_i(mapping->host)->mmu_निजी);
	अगर (unlikely(ret))
		hpfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल पूर्णांक hpfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *pagep, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक err;
	err = generic_ग_लिखो_end(file, mapping, pos, len, copied, pagep, fsdata);
	अगर (err < len)
		hpfs_ग_लिखो_failed(mapping, pos + len);
	अगर (!(err < 0)) अणु
		/* make sure we ग_लिखो it on बंद, अगर not earlier */
		hpfs_lock(inode->i_sb);
		hpfs_i(inode)->i_dirty = 1;
		hpfs_unlock(inode->i_sb);
	पूर्ण
	वापस err;
पूर्ण

अटल sector_t _hpfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, hpfs_get_block);
पूर्ण

अटल पूर्णांक hpfs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo, u64 start, u64 len)
अणु
	वापस generic_block_fiemap(inode, fieinfo, start, len, hpfs_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations hpfs_aops = अणु
	.पढ़ोpage = hpfs_पढ़ोpage,
	.ग_लिखोpage = hpfs_ग_लिखोpage,
	.पढ़ोahead = hpfs_पढ़ोahead,
	.ग_लिखोpages = hpfs_ग_लिखोpages,
	.ग_लिखो_begin = hpfs_ग_लिखो_begin,
	.ग_लिखो_end = hpfs_ग_लिखो_end,
	.bmap = _hpfs_bmap
पूर्ण;

स्थिर काष्ठा file_operations hpfs_file_ops =
अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.release	= hpfs_file_release,
	.fsync		= hpfs_file_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.unlocked_ioctl	= hpfs_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

स्थिर काष्ठा inode_operations hpfs_file_iops =
अणु
	.setattr	= hpfs_setattr,
	.fiemap		= hpfs_fiemap,
पूर्ण;
