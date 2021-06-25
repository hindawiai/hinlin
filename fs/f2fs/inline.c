<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/अंतरभूत.c
 * Copyright (c) 2013, Intel Corporation
 * Authors: Huajun Li <huajun.li@पूर्णांकel.com>
 *          Haicheng Li <haicheng.li@पूर्णांकel.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/fiemap.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश <trace/events/f2fs.h>

bool f2fs_may_अंतरभूत_data(काष्ठा inode *inode)
अणु
	अगर (f2fs_is_atomic_file(inode))
		वापस false;

	अगर (!S_ISREG(inode->i_mode) && !S_ISLNK(inode->i_mode))
		वापस false;

	अगर (i_size_पढ़ो(inode) > MAX_INLINE_DATA(inode))
		वापस false;

	अगर (f2fs_post_पढ़ो_required(inode))
		वापस false;

	वापस true;
पूर्ण

bool f2fs_may_अंतरभूत_dentry(काष्ठा inode *inode)
अणु
	अगर (!test_opt(F2FS_I_SB(inode), INLINE_DENTRY))
		वापस false;

	अगर (!S_ISसूची(inode->i_mode))
		वापस false;

	वापस true;
पूर्ण

व्योम f2fs_करो_पढ़ो_अंतरभूत_data(काष्ठा page *page, काष्ठा page *ipage)
अणु
	काष्ठा inode *inode = page->mapping->host;
	व्योम *src_addr, *dst_addr;

	अगर (PageUptodate(page))
		वापस;

	f2fs_bug_on(F2FS_P_SB(page), page->index);

	zero_user_segment(page, MAX_INLINE_DATA(inode), PAGE_SIZE);

	/* Copy the whole अंतरभूत data block */
	src_addr = अंतरभूत_data_addr(inode, ipage);
	dst_addr = kmap_atomic(page);
	स_नकल(dst_addr, src_addr, MAX_INLINE_DATA(inode));
	flush_dcache_page(page);
	kunmap_atomic(dst_addr);
	अगर (!PageUptodate(page))
		SetPageUptodate(page);
पूर्ण

व्योम f2fs_truncate_अंतरभूत_inode(काष्ठा inode *inode,
					काष्ठा page *ipage, u64 from)
अणु
	व्योम *addr;

	अगर (from >= MAX_INLINE_DATA(inode))
		वापस;

	addr = अंतरभूत_data_addr(inode, ipage);

	f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);
	स_रखो(addr + from, 0, MAX_INLINE_DATA(inode) - from);
	set_page_dirty(ipage);

	अगर (from == 0)
		clear_inode_flag(inode, FI_DATA_EXIST);
पूर्ण

पूर्णांक f2fs_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा page *ipage;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	अगर (IS_ERR(ipage)) अणु
		unlock_page(page);
		वापस PTR_ERR(ipage);
	पूर्ण

	अगर (!f2fs_has_अंतरभूत_data(inode)) अणु
		f2fs_put_page(ipage, 1);
		वापस -EAGAIN;
	पूर्ण

	अगर (page->index)
		zero_user_segment(page, 0, PAGE_SIZE);
	अन्यथा
		f2fs_करो_पढ़ो_अंतरभूत_data(page, ipage);

	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	f2fs_put_page(ipage, 1);
	unlock_page(page);
	वापस 0;
पूर्ण

पूर्णांक f2fs_convert_अंतरभूत_page(काष्ठा dnode_of_data *dn, काष्ठा page *page)
अणु
	काष्ठा f2fs_io_info fio = अणु
		.sbi = F2FS_I_SB(dn->inode),
		.ino = dn->inode->i_ino,
		.type = DATA,
		.op = REQ_OP_WRITE,
		.op_flags = REQ_SYNC | REQ_PRIO,
		.page = page,
		.encrypted_page = शून्य,
		.io_type = FS_DATA_IO,
	पूर्ण;
	काष्ठा node_info ni;
	पूर्णांक dirty, err;

	अगर (!f2fs_exist_data(dn->inode))
		जाओ clear_out;

	err = f2fs_reserve_block(dn, 0);
	अगर (err)
		वापस err;

	err = f2fs_get_node_info(fio.sbi, dn->nid, &ni);
	अगर (err) अणु
		f2fs_truncate_data_blocks_range(dn, 1);
		f2fs_put_dnode(dn);
		वापस err;
	पूर्ण

	fio.version = ni.version;

	अगर (unlikely(dn->data_blkaddr != NEW_ADDR)) अणु
		f2fs_put_dnode(dn);
		set_sbi_flag(fio.sbi, SBI_NEED_FSCK);
		f2fs_warn(fio.sbi, "%s: corrupted inline inode ino=%lx, i_addr[0]:0x%x, run fsck to fix.",
			  __func__, dn->inode->i_ino, dn->data_blkaddr);
		वापस -EFSCORRUPTED;
	पूर्ण

	f2fs_bug_on(F2FS_P_SB(page), PageWriteback(page));

	f2fs_करो_पढ़ो_अंतरभूत_data(page, dn->inode_page);
	set_page_dirty(page);

	/* clear dirty state */
	dirty = clear_page_dirty_क्रम_io(page);

	/* ग_लिखो data page to try to make data consistent */
	set_page_ग_लिखोback(page);
	ClearPageError(page);
	fio.old_blkaddr = dn->data_blkaddr;
	set_inode_flag(dn->inode, FI_HOT_DATA);
	f2fs_outplace_ग_लिखो_data(dn, &fio);
	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);
	अगर (dirty) अणु
		inode_dec_dirty_pages(dn->inode);
		f2fs_हटाओ_dirty_inode(dn->inode);
	पूर्ण

	/* this converted अंतरभूत_data should be recovered. */
	set_inode_flag(dn->inode, FI_APPEND_WRITE);

	/* clear अंतरभूत data and flag after data ग_लिखोback */
	f2fs_truncate_अंतरभूत_inode(dn->inode, dn->inode_page, 0);
	clear_अंतरभूत_node(dn->inode_page);
clear_out:
	stat_dec_अंतरभूत_inode(dn->inode);
	clear_inode_flag(dn->inode, FI_INLINE_DATA);
	f2fs_put_dnode(dn);
	वापस 0;
पूर्ण

पूर्णांक f2fs_convert_अंतरभूत_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा dnode_of_data dn;
	काष्ठा page *ipage, *page;
	पूर्णांक err = 0;

	अगर (!f2fs_has_अंतरभूत_data(inode) ||
			f2fs_hw_is_पढ़ोonly(sbi) || f2fs_पढ़ोonly(sbi->sb))
		वापस 0;

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	page = f2fs_grab_cache_page(inode->i_mapping, 0, false);
	अगर (!page)
		वापस -ENOMEM;

	f2fs_lock_op(sbi);

	ipage = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(ipage)) अणु
		err = PTR_ERR(ipage);
		जाओ out;
	पूर्ण

	set_new_dnode(&dn, inode, ipage, ipage, 0);

	अगर (f2fs_has_अंतरभूत_data(inode))
		err = f2fs_convert_अंतरभूत_page(&dn, page);

	f2fs_put_dnode(&dn);
out:
	f2fs_unlock_op(sbi);

	f2fs_put_page(page, 1);

	अगर (!err)
		f2fs_balance_fs(sbi, dn.node_changed);

	वापस err;
पूर्ण

पूर्णांक f2fs_ग_लिखो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page)
अणु
	व्योम *src_addr, *dst_addr;
	काष्ठा dnode_of_data dn;
	पूर्णांक err;

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, 0, LOOKUP_NODE);
	अगर (err)
		वापस err;

	अगर (!f2fs_has_अंतरभूत_data(inode)) अणु
		f2fs_put_dnode(&dn);
		वापस -EAGAIN;
	पूर्ण

	f2fs_bug_on(F2FS_I_SB(inode), page->index);

	f2fs_रुको_on_page_ग_लिखोback(dn.inode_page, NODE, true, true);
	src_addr = kmap_atomic(page);
	dst_addr = अंतरभूत_data_addr(inode, dn.inode_page);
	स_नकल(dst_addr, src_addr, MAX_INLINE_DATA(inode));
	kunmap_atomic(src_addr);
	set_page_dirty(dn.inode_page);

	f2fs_clear_page_cache_dirty_tag(page);

	set_inode_flag(inode, FI_APPEND_WRITE);
	set_inode_flag(inode, FI_DATA_EXIST);

	clear_अंतरभूत_node(dn.inode_page);
	f2fs_put_dnode(&dn);
	वापस 0;
पूर्ण

पूर्णांक f2fs_recover_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *npage)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode *ri = शून्य;
	व्योम *src_addr, *dst_addr;
	काष्ठा page *ipage;

	/*
	 * The अंतरभूत_data recovery policy is as follows.
	 * [prev.] [next] of अंतरभूत_data flag
	 *    o       o  -> recover अंतरभूत_data
	 *    o       x  -> हटाओ अंतरभूत_data, and then recover data blocks
	 *    x       o  -> हटाओ data blocks, and then recover अंतरभूत_data
	 *    x       x  -> recover data blocks
	 */
	अगर (IS_INODE(npage))
		ri = F2FS_INODE(npage);

	अगर (f2fs_has_अंतरभूत_data(inode) &&
			ri && (ri->i_अंतरभूत & F2FS_INLINE_DATA)) अणु
process_अंतरभूत:
		ipage = f2fs_get_node_page(sbi, inode->i_ino);
		अगर (IS_ERR(ipage))
			वापस PTR_ERR(ipage);

		f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);

		src_addr = अंतरभूत_data_addr(inode, npage);
		dst_addr = अंतरभूत_data_addr(inode, ipage);
		स_नकल(dst_addr, src_addr, MAX_INLINE_DATA(inode));

		set_inode_flag(inode, FI_INLINE_DATA);
		set_inode_flag(inode, FI_DATA_EXIST);

		set_page_dirty(ipage);
		f2fs_put_page(ipage, 1);
		वापस 1;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_data(inode)) अणु
		ipage = f2fs_get_node_page(sbi, inode->i_ino);
		अगर (IS_ERR(ipage))
			वापस PTR_ERR(ipage);
		f2fs_truncate_अंतरभूत_inode(inode, ipage, 0);
		stat_dec_अंतरभूत_inode(inode);
		clear_inode_flag(inode, FI_INLINE_DATA);
		f2fs_put_page(ipage, 1);
	पूर्ण अन्यथा अगर (ri && (ri->i_अंतरभूत & F2FS_INLINE_DATA)) अणु
		पूर्णांक ret;

		ret = f2fs_truncate_blocks(inode, 0, false);
		अगर (ret)
			वापस ret;
		stat_inc_अंतरभूत_inode(inode);
		जाओ process_अंतरभूत;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा f2fs_dir_entry *f2fs_find_in_अंतरभूत_dir(काष्ठा inode *dir,
					स्थिर काष्ठा f2fs_filename *fname,
					काष्ठा page **res_page)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(dir->i_sb);
	काष्ठा f2fs_dir_entry *de;
	काष्ठा f2fs_dentry_ptr d;
	काष्ठा page *ipage;
	व्योम *अंतरभूत_dentry;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	अगर (IS_ERR(ipage)) अणु
		*res_page = ipage;
		वापस शून्य;
	पूर्ण

	अंतरभूत_dentry = अंतरभूत_data_addr(dir, ipage);

	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_dentry);
	de = f2fs_find_target_dentry(&d, fname, शून्य);
	unlock_page(ipage);
	अगर (IS_ERR(de)) अणु
		*res_page = ERR_CAST(de);
		de = शून्य;
	पूर्ण
	अगर (de)
		*res_page = ipage;
	अन्यथा
		f2fs_put_page(ipage, 0);

	वापस de;
पूर्ण

पूर्णांक f2fs_make_empty_अंतरभूत_dir(काष्ठा inode *inode, काष्ठा inode *parent,
							काष्ठा page *ipage)
अणु
	काष्ठा f2fs_dentry_ptr d;
	व्योम *अंतरभूत_dentry;

	अंतरभूत_dentry = अंतरभूत_data_addr(inode, ipage);

	make_dentry_ptr_अंतरभूत(inode, &d, अंतरभूत_dentry);
	f2fs_करो_make_empty_dir(inode, parent, &d);

	set_page_dirty(ipage);

	/* update i_size to MAX_INLINE_DATA */
	अगर (i_size_पढ़ो(inode) < MAX_INLINE_DATA(inode))
		f2fs_i_size_ग_लिखो(inode, MAX_INLINE_DATA(inode));
	वापस 0;
पूर्ण

/*
 * NOTE: ipage is grabbed by caller, but अगर any error occurs, we should
 * release ipage in this function.
 */
अटल पूर्णांक f2fs_move_अंतरभूत_dirents(काष्ठा inode *dir, काष्ठा page *ipage,
							व्योम *अंतरभूत_dentry)
अणु
	काष्ठा page *page;
	काष्ठा dnode_of_data dn;
	काष्ठा f2fs_dentry_block *dentry_blk;
	काष्ठा f2fs_dentry_ptr src, dst;
	पूर्णांक err;

	page = f2fs_grab_cache_page(dir->i_mapping, 0, true);
	अगर (!page) अणु
		f2fs_put_page(ipage, 1);
		वापस -ENOMEM;
	पूर्ण

	set_new_dnode(&dn, dir, ipage, शून्य, 0);
	err = f2fs_reserve_block(&dn, 0);
	अगर (err)
		जाओ out;

	अगर (unlikely(dn.data_blkaddr != NEW_ADDR)) अणु
		f2fs_put_dnode(&dn);
		set_sbi_flag(F2FS_P_SB(page), SBI_NEED_FSCK);
		f2fs_warn(F2FS_P_SB(page), "%s: corrupted inline inode ino=%lx, i_addr[0]:0x%x, run fsck to fix.",
			  __func__, dir->i_ino, dn.data_blkaddr);
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

	dentry_blk = page_address(page);

	make_dentry_ptr_अंतरभूत(dir, &src, अंतरभूत_dentry);
	make_dentry_ptr_block(dir, &dst, dentry_blk);

	/* copy data from अंतरभूत dentry block to new dentry block */
	स_नकल(dst.biपंचांगap, src.biपंचांगap, src.nr_biपंचांगap);
	स_रखो(dst.biपंचांगap + src.nr_biपंचांगap, 0, dst.nr_biपंचांगap - src.nr_biपंचांगap);
	/*
	 * we करो not need to zero out reमुख्यder part of dentry and filename
	 * field, since we have used biपंचांगap क्रम marking the usage status of
	 * them, besides, we can also ignore copying/zeroing reserved space
	 * of dentry block, because them haven't been used so far.
	 */
	स_नकल(dst.dentry, src.dentry, SIZE_OF_सूची_ENTRY * src.max);
	स_नकल(dst.filename, src.filename, src.max * F2FS_SLOT_LEN);

	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	set_page_dirty(page);

	/* clear अंतरभूत dir and flag after data ग_लिखोback */
	f2fs_truncate_अंतरभूत_inode(dir, ipage, 0);

	stat_dec_अंतरभूत_dir(dir);
	clear_inode_flag(dir, FI_INLINE_DENTRY);

	/*
	 * should retrieve reserved space which was used to keep
	 * अंतरभूत_dentry's काष्ठाure क्रम backward compatibility.
	 */
	अगर (!f2fs_sb_has_flexible_अंतरभूत_xattr(F2FS_I_SB(dir)) &&
			!f2fs_has_अंतरभूत_xattr(dir))
		F2FS_I(dir)->i_अंतरभूत_xattr_size = 0;

	f2fs_i_depth_ग_लिखो(dir, 1);
	अगर (i_size_पढ़ो(dir) < PAGE_SIZE)
		f2fs_i_size_ग_लिखो(dir, PAGE_SIZE);
out:
	f2fs_put_page(page, 1);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_add_अंतरभूत_entries(काष्ठा inode *dir, व्योम *अंतरभूत_dentry)
अणु
	काष्ठा f2fs_dentry_ptr d;
	अचिन्हित दीर्घ bit_pos = 0;
	पूर्णांक err = 0;

	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_dentry);

	जबतक (bit_pos < d.max) अणु
		काष्ठा f2fs_dir_entry *de;
		काष्ठा f2fs_filename fname;
		nid_t ino;
		umode_t fake_mode;

		अगर (!test_bit_le(bit_pos, d.biपंचांगap)) अणु
			bit_pos++;
			जारी;
		पूर्ण

		de = &d.dentry[bit_pos];

		अगर (unlikely(!de->name_len)) अणु
			bit_pos++;
			जारी;
		पूर्ण

		/*
		 * We only need the disk_name and hash to move the dentry.
		 * We करोn't need the original or हालfolded filenames.
		 */
		स_रखो(&fname, 0, माप(fname));
		fname.disk_name.name = d.filename[bit_pos];
		fname.disk_name.len = le16_to_cpu(de->name_len);
		fname.hash = de->hash_code;

		ino = le32_to_cpu(de->ino);
		fake_mode = f2fs_get_de_type(de) << S_SHIFT;

		err = f2fs_add_regular_entry(dir, &fname, शून्य, ino, fake_mode);
		अगर (err)
			जाओ punch_dentry_pages;

		bit_pos += GET_DENTRY_SLOTS(le16_to_cpu(de->name_len));
	पूर्ण
	वापस 0;
punch_dentry_pages:
	truncate_inode_pages(&dir->i_data, 0);
	f2fs_truncate_blocks(dir, 0, false);
	f2fs_हटाओ_dirty_inode(dir);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_move_rehashed_dirents(काष्ठा inode *dir, काष्ठा page *ipage,
							व्योम *अंतरभूत_dentry)
अणु
	व्योम *backup_dentry;
	पूर्णांक err;

	backup_dentry = f2fs_kदो_स्मृति(F2FS_I_SB(dir),
				MAX_INLINE_DATA(dir), GFP_F2FS_ZERO);
	अगर (!backup_dentry) अणु
		f2fs_put_page(ipage, 1);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(backup_dentry, अंतरभूत_dentry, MAX_INLINE_DATA(dir));
	f2fs_truncate_अंतरभूत_inode(dir, ipage, 0);

	unlock_page(ipage);

	err = f2fs_add_अंतरभूत_entries(dir, backup_dentry);
	अगर (err)
		जाओ recover;

	lock_page(ipage);

	stat_dec_अंतरभूत_dir(dir);
	clear_inode_flag(dir, FI_INLINE_DENTRY);

	/*
	 * should retrieve reserved space which was used to keep
	 * अंतरभूत_dentry's काष्ठाure क्रम backward compatibility.
	 */
	अगर (!f2fs_sb_has_flexible_अंतरभूत_xattr(F2FS_I_SB(dir)) &&
			!f2fs_has_अंतरभूत_xattr(dir))
		F2FS_I(dir)->i_अंतरभूत_xattr_size = 0;

	kमुक्त(backup_dentry);
	वापस 0;
recover:
	lock_page(ipage);
	f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);
	स_नकल(अंतरभूत_dentry, backup_dentry, MAX_INLINE_DATA(dir));
	f2fs_i_depth_ग_लिखो(dir, 0);
	f2fs_i_size_ग_लिखो(dir, MAX_INLINE_DATA(dir));
	set_page_dirty(ipage);
	f2fs_put_page(ipage, 1);

	kमुक्त(backup_dentry);
	वापस err;
पूर्ण

अटल पूर्णांक करो_convert_अंतरभूत_dir(काष्ठा inode *dir, काष्ठा page *ipage,
							व्योम *अंतरभूत_dentry)
अणु
	अगर (!F2FS_I(dir)->i_dir_level)
		वापस f2fs_move_अंतरभूत_dirents(dir, ipage, अंतरभूत_dentry);
	अन्यथा
		वापस f2fs_move_rehashed_dirents(dir, ipage, अंतरभूत_dentry);
पूर्ण

पूर्णांक f2fs_try_convert_अंतरभूत_dir(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा page *ipage;
	काष्ठा f2fs_filename fname;
	व्योम *अंतरभूत_dentry = शून्य;
	पूर्णांक err = 0;

	अगर (!f2fs_has_अंतरभूत_dentry(dir))
		वापस 0;

	f2fs_lock_op(sbi);

	err = f2fs_setup_filename(dir, &dentry->d_name, 0, &fname);
	अगर (err)
		जाओ out;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	अगर (IS_ERR(ipage)) अणु
		err = PTR_ERR(ipage);
		जाओ out_fname;
	पूर्ण

	अगर (f2fs_has_enough_room(dir, ipage, &fname)) अणु
		f2fs_put_page(ipage, 1);
		जाओ out_fname;
	पूर्ण

	अंतरभूत_dentry = अंतरभूत_data_addr(dir, ipage);

	err = करो_convert_अंतरभूत_dir(dir, ipage, अंतरभूत_dentry);
	अगर (!err)
		f2fs_put_page(ipage, 1);
out_fname:
	f2fs_मुक्त_filename(&fname);
out:
	f2fs_unlock_op(sbi);
	वापस err;
पूर्ण

पूर्णांक f2fs_add_अंतरभूत_entry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
			  काष्ठा inode *inode, nid_t ino, umode_t mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा page *ipage;
	अचिन्हित पूर्णांक bit_pos;
	व्योम *अंतरभूत_dentry = शून्य;
	काष्ठा f2fs_dentry_ptr d;
	पूर्णांक slots = GET_DENTRY_SLOTS(fname->disk_name.len);
	काष्ठा page *page = शून्य;
	पूर्णांक err = 0;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	अगर (IS_ERR(ipage))
		वापस PTR_ERR(ipage);

	अंतरभूत_dentry = अंतरभूत_data_addr(dir, ipage);
	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_dentry);

	bit_pos = f2fs_room_क्रम_filename(d.biपंचांगap, slots, d.max);
	अगर (bit_pos >= d.max) अणु
		err = करो_convert_अंतरभूत_dir(dir, ipage, अंतरभूत_dentry);
		अगर (err)
			वापस err;
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (inode) अणु
		करोwn_ग_लिखो(&F2FS_I(inode)->i_sem);
		page = f2fs_init_inode_metadata(inode, dir, fname, ipage);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ fail;
		पूर्ण
	पूर्ण

	f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);

	f2fs_update_dentry(ino, mode, &d, &fname->disk_name, fname->hash,
			   bit_pos);

	set_page_dirty(ipage);

	/* we करोn't need to mark_inode_dirty now */
	अगर (inode) अणु
		f2fs_i_pino_ग_लिखो(inode, dir->i_ino);

		/* synchronize inode page's data from inode cache */
		अगर (is_inode_flag_set(inode, FI_NEW_INODE))
			f2fs_update_inode(inode, page);

		f2fs_put_page(page, 1);
	पूर्ण

	f2fs_update_parent_metadata(dir, inode, 0);
fail:
	अगर (inode)
		up_ग_लिखो(&F2FS_I(inode)->i_sem);
out:
	f2fs_put_page(ipage, 1);
	वापस err;
पूर्ण

व्योम f2fs_delete_अंतरभूत_entry(काष्ठा f2fs_dir_entry *dentry, काष्ठा page *page,
					काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	काष्ठा f2fs_dentry_ptr d;
	व्योम *अंतरभूत_dentry;
	पूर्णांक slots = GET_DENTRY_SLOTS(le16_to_cpu(dentry->name_len));
	अचिन्हित पूर्णांक bit_pos;
	पूर्णांक i;

	lock_page(page);
	f2fs_रुको_on_page_ग_लिखोback(page, NODE, true, true);

	अंतरभूत_dentry = अंतरभूत_data_addr(dir, page);
	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_dentry);

	bit_pos = dentry - d.dentry;
	क्रम (i = 0; i < slots; i++)
		__clear_bit_le(bit_pos + i, d.biपंचांगap);

	set_page_dirty(page);
	f2fs_put_page(page, 1);

	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	f2fs_mark_inode_dirty_sync(dir, false);

	अगर (inode)
		f2fs_drop_nlink(dir, inode);
पूर्ण

bool f2fs_empty_अंतरभूत_dir(काष्ठा inode *dir)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा page *ipage;
	अचिन्हित पूर्णांक bit_pos = 2;
	व्योम *अंतरभूत_dentry;
	काष्ठा f2fs_dentry_ptr d;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	अगर (IS_ERR(ipage))
		वापस false;

	अंतरभूत_dentry = अंतरभूत_data_addr(dir, ipage);
	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_dentry);

	bit_pos = find_next_bit_le(d.biपंचांगap, d.max, bit_pos);

	f2fs_put_page(ipage, 1);

	अगर (bit_pos < d.max)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक f2fs_पढ़ो_अंतरभूत_dir(काष्ठा file *file, काष्ठा dir_context *ctx,
				काष्ठा fscrypt_str *fstr)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा page *ipage = शून्य;
	काष्ठा f2fs_dentry_ptr d;
	व्योम *अंतरभूत_dentry = शून्य;
	पूर्णांक err;

	make_dentry_ptr_अंतरभूत(inode, &d, अंतरभूत_dentry);

	अगर (ctx->pos == d.max)
		वापस 0;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	अगर (IS_ERR(ipage))
		वापस PTR_ERR(ipage);

	/*
	 * f2fs_सूची_पढ़ो was रक्षित by inode.i_rwsem, it is safe to access
	 * ipage without page's lock held.
	 */
	unlock_page(ipage);

	अंतरभूत_dentry = अंतरभूत_data_addr(inode, ipage);

	make_dentry_ptr_अंतरभूत(inode, &d, अंतरभूत_dentry);

	err = f2fs_fill_dentries(ctx, &d, 0, fstr);
	अगर (!err)
		ctx->pos = d.max;

	f2fs_put_page(ipage, 0);
	वापस err < 0 ? err : 0;
पूर्ण

पूर्णांक f2fs_अंतरभूत_data_fiemap(काष्ठा inode *inode,
		काष्ठा fiemap_extent_info *fieinfo, __u64 start, __u64 len)
अणु
	__u64 byteaddr, ilen;
	__u32 flags = FIEMAP_EXTENT_DATA_INLINE | FIEMAP_EXTENT_NOT_ALIGNED |
		FIEMAP_EXTENT_LAST;
	काष्ठा node_info ni;
	काष्ठा page *ipage;
	पूर्णांक err = 0;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	अगर (IS_ERR(ipage))
		वापस PTR_ERR(ipage);

	अगर ((S_ISREG(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
				!f2fs_has_अंतरभूत_data(inode)) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (S_ISसूची(inode->i_mode) && !f2fs_has_अंतरभूत_dentry(inode)) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	ilen = min_t(माप_प्रकार, MAX_INLINE_DATA(inode), i_size_पढ़ो(inode));
	अगर (start >= ilen)
		जाओ out;
	अगर (start + len < ilen)
		ilen = start + len;
	ilen -= start;

	err = f2fs_get_node_info(F2FS_I_SB(inode), inode->i_ino, &ni);
	अगर (err)
		जाओ out;

	byteaddr = (__u64)ni.blk_addr << inode->i_sb->s_blocksize_bits;
	byteaddr += (अक्षर *)अंतरभूत_data_addr(inode, ipage) -
					(अक्षर *)F2FS_INODE(ipage);
	err = fiemap_fill_next_extent(fieinfo, start, byteaddr, ilen, flags);
	trace_f2fs_fiemap(inode, start, byteaddr, ilen, flags, err);
out:
	f2fs_put_page(ipage, 1);
	वापस err;
पूर्ण
