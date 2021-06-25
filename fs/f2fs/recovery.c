<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/recovery.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"

/*
 * Roll क्रमward recovery scenarios.
 *
 * [Term] F: fsync_mark, D: dentry_mark
 *
 * 1. inode(x) | CP | inode(x) | dnode(F)
 * -> Update the latest inode(x).
 *
 * 2. inode(x) | CP | inode(F) | dnode(F)
 * -> No problem.
 *
 * 3. inode(x) | CP | dnode(F) | inode(x)
 * -> Recover to the latest dnode(F), and drop the last inode(x)
 *
 * 4. inode(x) | CP | dnode(F) | inode(F)
 * -> No problem.
 *
 * 5. CP | inode(x) | dnode(F)
 * -> The inode(DF) was missing. Should drop this dnode(F).
 *
 * 6. CP | inode(DF) | dnode(F)
 * -> No problem.
 *
 * 7. CP | dnode(F) | inode(DF)
 * -> If f2fs_iget fails, then जाओ next to find inode(DF).
 *
 * 8. CP | dnode(F) | inode(x)
 * -> If f2fs_iget fails, then जाओ next to find inode(DF).
 *    But it will fail due to no inode(DF).
 */

अटल काष्ठा kmem_cache *fsync_entry_slab;

bool f2fs_space_क्रम_roll_क्रमward(काष्ठा f2fs_sb_info *sbi)
अणु
	s64 nalloc = percpu_counter_sum_positive(&sbi->alloc_valid_block_count);

	अगर (sbi->last_valid_block_count + nalloc > sbi->user_block_count)
		वापस false;
	वापस true;
पूर्ण

अटल काष्ठा fsync_inode_entry *get_fsync_inode(काष्ठा list_head *head,
								nid_t ino)
अणु
	काष्ठा fsync_inode_entry *entry;

	list_क्रम_each_entry(entry, head, list)
		अगर (entry->inode->i_ino == ino)
			वापस entry;

	वापस शून्य;
पूर्ण

अटल काष्ठा fsync_inode_entry *add_fsync_inode(काष्ठा f2fs_sb_info *sbi,
			काष्ठा list_head *head, nid_t ino, bool quota_inode)
अणु
	काष्ठा inode *inode;
	काष्ठा fsync_inode_entry *entry;
	पूर्णांक err;

	inode = f2fs_iget_retry(sbi->sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	err = dquot_initialize(inode);
	अगर (err)
		जाओ err_out;

	अगर (quota_inode) अणु
		err = dquot_alloc_inode(inode);
		अगर (err)
			जाओ err_out;
	पूर्ण

	entry = f2fs_kmem_cache_alloc(fsync_entry_slab, GFP_F2FS_ZERO);
	entry->inode = inode;
	list_add_tail(&entry->list, head);

	वापस entry;
err_out:
	iput(inode);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम del_fsync_inode(काष्ठा fsync_inode_entry *entry, पूर्णांक drop)
अणु
	अगर (drop) अणु
		/* inode should not be recovered, drop it */
		f2fs_inode_synced(entry->inode);
	पूर्ण
	iput(entry->inode);
	list_del(&entry->list);
	kmem_cache_मुक्त(fsync_entry_slab, entry);
पूर्ण

अटल पूर्णांक init_recovered_filename(स्थिर काष्ठा inode *dir,
				   काष्ठा f2fs_inode *raw_inode,
				   काष्ठा f2fs_filename *fname,
				   काष्ठा qstr *usr_fname)
अणु
	पूर्णांक err;

	स_रखो(fname, 0, माप(*fname));
	fname->disk_name.len = le32_to_cpu(raw_inode->i_namelen);
	fname->disk_name.name = raw_inode->i_name;

	अगर (WARN_ON(fname->disk_name.len > F2FS_NAME_LEN))
		वापस -ENAMETOOLONG;

	अगर (!IS_ENCRYPTED(dir)) अणु
		usr_fname->name = fname->disk_name.name;
		usr_fname->len = fname->disk_name.len;
		fname->usr_fname = usr_fname;
	पूर्ण

	/* Compute the hash of the filename */
	अगर (IS_ENCRYPTED(dir) && IS_CASEFOLDED(dir)) अणु
		/*
		 * In this हाल the hash isn't computable without the key, so it
		 * was saved on-disk.
		 */
		अगर (fname->disk_name.len + माप(f2fs_hash_t) > F2FS_NAME_LEN)
			वापस -EINVAL;
		fname->hash = get_unaligned((f2fs_hash_t *)
				&raw_inode->i_name[fname->disk_name.len]);
	पूर्ण अन्यथा अगर (IS_CASEFOLDED(dir)) अणु
		err = f2fs_init_हालfolded_name(dir, fname);
		अगर (err)
			वापस err;
		f2fs_hash_filename(dir, fname);
#अगर_घोषित CONFIG_UNICODE
		/* Case-sensitive match is fine क्रम recovery */
		kमुक्त(fname->cf_name.name);
		fname->cf_name.name = शून्य;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		f2fs_hash_filename(dir, fname);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक recover_dentry(काष्ठा inode *inode, काष्ठा page *ipage,
						काष्ठा list_head *dir_list)
अणु
	काष्ठा f2fs_inode *raw_inode = F2FS_INODE(ipage);
	nid_t pino = le32_to_cpu(raw_inode->i_pino);
	काष्ठा f2fs_dir_entry *de;
	काष्ठा f2fs_filename fname;
	काष्ठा qstr usr_fname;
	काष्ठा page *page;
	काष्ठा inode *dir, *einode;
	काष्ठा fsync_inode_entry *entry;
	पूर्णांक err = 0;
	अक्षर *name;

	entry = get_fsync_inode(dir_list, pino);
	अगर (!entry) अणु
		entry = add_fsync_inode(F2FS_I_SB(inode), dir_list,
							pino, false);
		अगर (IS_ERR(entry)) अणु
			dir = ERR_CAST(entry);
			err = PTR_ERR(entry);
			जाओ out;
		पूर्ण
	पूर्ण

	dir = entry->inode;
	err = init_recovered_filename(dir, raw_inode, &fname, &usr_fname);
	अगर (err)
		जाओ out;
retry:
	de = __f2fs_find_entry(dir, &fname, &page);
	अगर (de && inode->i_ino == le32_to_cpu(de->ino))
		जाओ out_put;

	अगर (de) अणु
		einode = f2fs_iget_retry(inode->i_sb, le32_to_cpu(de->ino));
		अगर (IS_ERR(einode)) अणु
			WARN_ON(1);
			err = PTR_ERR(einode);
			अगर (err == -ENOENT)
				err = -EEXIST;
			जाओ out_put;
		पूर्ण

		err = dquot_initialize(einode);
		अगर (err) अणु
			iput(einode);
			जाओ out_put;
		पूर्ण

		err = f2fs_acquire_orphan_inode(F2FS_I_SB(inode));
		अगर (err) अणु
			iput(einode);
			जाओ out_put;
		पूर्ण
		f2fs_delete_entry(de, page, dir, einode);
		iput(einode);
		जाओ retry;
	पूर्ण अन्यथा अगर (IS_ERR(page)) अणु
		err = PTR_ERR(page);
	पूर्ण अन्यथा अणु
		err = f2fs_add_dentry(dir, &fname, inode,
					inode->i_ino, inode->i_mode);
	पूर्ण
	अगर (err == -ENOMEM)
		जाओ retry;
	जाओ out;

out_put:
	f2fs_put_page(page, 0);
out:
	अगर (file_enc_name(inode))
		name = "<encrypted>";
	अन्यथा
		name = raw_inode->i_name;
	f2fs_notice(F2FS_I_SB(inode), "%s: ino = %x, name = %s, dir = %lx, err = %d",
		    __func__, ino_of_node(ipage), name,
		    IS_ERR(dir) ? 0 : dir->i_ino, err);
	वापस err;
पूर्ण

अटल पूर्णांक recover_quota_data(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *raw = F2FS_INODE(page);
	काष्ठा iattr attr;
	uid_t i_uid = le32_to_cpu(raw->i_uid);
	gid_t i_gid = le32_to_cpu(raw->i_gid);
	पूर्णांक err;

	स_रखो(&attr, 0, माप(attr));

	attr.ia_uid = make_kuid(inode->i_sb->s_user_ns, i_uid);
	attr.ia_gid = make_kgid(inode->i_sb->s_user_ns, i_gid);

	अगर (!uid_eq(attr.ia_uid, inode->i_uid))
		attr.ia_valid |= ATTR_UID;
	अगर (!gid_eq(attr.ia_gid, inode->i_gid))
		attr.ia_valid |= ATTR_GID;

	अगर (!attr.ia_valid)
		वापस 0;

	err = dquot_transfer(inode, &attr);
	अगर (err)
		set_sbi_flag(F2FS_I_SB(inode), SBI_QUOTA_NEED_REPAIR);
	वापस err;
पूर्ण

अटल व्योम recover_अंतरभूत_flags(काष्ठा inode *inode, काष्ठा f2fs_inode *ri)
अणु
	अगर (ri->i_अंतरभूत & F2FS_PIN_खाता)
		set_inode_flag(inode, FI_PIN_खाता);
	अन्यथा
		clear_inode_flag(inode, FI_PIN_खाता);
	अगर (ri->i_अंतरभूत & F2FS_DATA_EXIST)
		set_inode_flag(inode, FI_DATA_EXIST);
	अन्यथा
		clear_inode_flag(inode, FI_DATA_EXIST);
पूर्ण

अटल पूर्णांक recover_inode(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *raw = F2FS_INODE(page);
	अक्षर *name;
	पूर्णांक err;

	inode->i_mode = le16_to_cpu(raw->i_mode);

	err = recover_quota_data(inode, page);
	अगर (err)
		वापस err;

	i_uid_ग_लिखो(inode, le32_to_cpu(raw->i_uid));
	i_gid_ग_लिखो(inode, le32_to_cpu(raw->i_gid));

	अगर (raw->i_अंतरभूत & F2FS_EXTRA_ATTR) अणु
		अगर (f2fs_sb_has_project_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(raw, le16_to_cpu(raw->i_extra_isize),
								i_projid)) अणु
			projid_t i_projid;
			kprojid_t kprojid;

			i_projid = (projid_t)le32_to_cpu(raw->i_projid);
			kprojid = make_kprojid(&init_user_ns, i_projid);

			अगर (!projid_eq(kprojid, F2FS_I(inode)->i_projid)) अणु
				err = f2fs_transfer_project_quota(inode,
								kprojid);
				अगर (err)
					वापस err;
				F2FS_I(inode)->i_projid = kprojid;
			पूर्ण
		पूर्ण
	पूर्ण

	f2fs_i_size_ग_लिखो(inode, le64_to_cpu(raw->i_size));
	inode->i_aसमय.tv_sec = le64_to_cpu(raw->i_aसमय);
	inode->i_स_समय.tv_sec = le64_to_cpu(raw->i_स_समय);
	inode->i_mसमय.tv_sec = le64_to_cpu(raw->i_mसमय);
	inode->i_aसमय.tv_nsec = le32_to_cpu(raw->i_aसमय_nsec);
	inode->i_स_समय.tv_nsec = le32_to_cpu(raw->i_स_समय_nsec);
	inode->i_mसमय.tv_nsec = le32_to_cpu(raw->i_mसमय_nsec);

	F2FS_I(inode)->i_advise = raw->i_advise;
	F2FS_I(inode)->i_flags = le32_to_cpu(raw->i_flags);
	f2fs_set_inode_flags(inode);
	F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN] =
				le16_to_cpu(raw->i_gc_failures);

	recover_अंतरभूत_flags(inode, raw);

	f2fs_mark_inode_dirty_sync(inode, true);

	अगर (file_enc_name(inode))
		name = "<encrypted>";
	अन्यथा
		name = F2FS_INODE(page)->i_name;

	f2fs_notice(F2FS_I_SB(inode), "recover_inode: ino = %x, name = %s, inline = %x",
		    ino_of_node(page), name, raw->i_अंतरभूत);
	वापस 0;
पूर्ण

अटल पूर्णांक find_fsync_dnodes(काष्ठा f2fs_sb_info *sbi, काष्ठा list_head *head,
				bool check_only)
अणु
	काष्ठा curseg_info *curseg;
	काष्ठा page *page = शून्य;
	block_t blkaddr;
	अचिन्हित पूर्णांक loop_cnt = 0;
	अचिन्हित पूर्णांक मुक्त_blocks = MAIN_SEGS(sbi) * sbi->blocks_per_seg -
						valid_user_blocks(sbi);
	पूर्णांक err = 0;

	/* get node pages in the current segment */
	curseg = CURSEG_I(sbi, CURSEG_WARM_NODE);
	blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	जबतक (1) अणु
		काष्ठा fsync_inode_entry *entry;

		अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr, META_POR))
			वापस 0;

		page = f2fs_get_पंचांगp_page(sbi, blkaddr);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			अवरोध;
		पूर्ण

		अगर (!is_recoverable_dnode(page)) अणु
			f2fs_put_page(page, 1);
			अवरोध;
		पूर्ण

		अगर (!is_fsync_dnode(page))
			जाओ next;

		entry = get_fsync_inode(head, ino_of_node(page));
		अगर (!entry) अणु
			bool quota_inode = false;

			अगर (!check_only &&
					IS_INODE(page) && is_dent_dnode(page)) अणु
				err = f2fs_recover_inode_page(sbi, page);
				अगर (err) अणु
					f2fs_put_page(page, 1);
					अवरोध;
				पूर्ण
				quota_inode = true;
			पूर्ण

			/*
			 * CP | dnode(F) | inode(DF)
			 * For this हाल, we should not give up now.
			 */
			entry = add_fsync_inode(sbi, head, ino_of_node(page),
								quota_inode);
			अगर (IS_ERR(entry)) अणु
				err = PTR_ERR(entry);
				अगर (err == -ENOENT) अणु
					err = 0;
					जाओ next;
				पूर्ण
				f2fs_put_page(page, 1);
				अवरोध;
			पूर्ण
		पूर्ण
		entry->blkaddr = blkaddr;

		अगर (IS_INODE(page) && is_dent_dnode(page))
			entry->last_dentry = blkaddr;
next:
		/* sanity check in order to detect looped node chain */
		अगर (++loop_cnt >= मुक्त_blocks ||
			blkaddr == next_blkaddr_of_node(page)) अणु
			f2fs_notice(sbi, "%s: detect looped node chain, blkaddr:%u, next:%u",
				    __func__, blkaddr,
				    next_blkaddr_of_node(page));
			f2fs_put_page(page, 1);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/* check next segment */
		blkaddr = next_blkaddr_of_node(page);
		f2fs_put_page(page, 1);

		f2fs_ra_meta_pages_cond(sbi, blkaddr);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम destroy_fsync_dnodes(काष्ठा list_head *head, पूर्णांक drop)
अणु
	काष्ठा fsync_inode_entry *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, head, list)
		del_fsync_inode(entry, drop);
पूर्ण

अटल पूर्णांक check_index_in_prev_nodes(काष्ठा f2fs_sb_info *sbi,
			block_t blkaddr, काष्ठा dnode_of_data *dn)
अणु
	काष्ठा seg_entry *sentry;
	अचिन्हित पूर्णांक segno = GET_SEGNO(sbi, blkaddr);
	अचिन्हित लघु blkoff = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);
	काष्ठा f2fs_summary_block *sum_node;
	काष्ठा f2fs_summary sum;
	काष्ठा page *sum_page, *node_page;
	काष्ठा dnode_of_data tdn = *dn;
	nid_t ino, nid;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक offset;
	block_t bidx;
	पूर्णांक i;

	sentry = get_seg_entry(sbi, segno);
	अगर (!f2fs_test_bit(blkoff, sentry->cur_valid_map))
		वापस 0;

	/* Get the previous summary */
	क्रम (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++) अणु
		काष्ठा curseg_info *curseg = CURSEG_I(sbi, i);

		अगर (curseg->segno == segno) अणु
			sum = curseg->sum_blk->entries[blkoff];
			जाओ got_it;
		पूर्ण
	पूर्ण

	sum_page = f2fs_get_sum_page(sbi, segno);
	अगर (IS_ERR(sum_page))
		वापस PTR_ERR(sum_page);
	sum_node = (काष्ठा f2fs_summary_block *)page_address(sum_page);
	sum = sum_node->entries[blkoff];
	f2fs_put_page(sum_page, 1);
got_it:
	/* Use the locked dnode page and inode */
	nid = le32_to_cpu(sum.nid);
	अगर (dn->inode->i_ino == nid) अणु
		tdn.nid = nid;
		अगर (!dn->inode_page_locked)
			lock_page(dn->inode_page);
		tdn.node_page = dn->inode_page;
		tdn.ofs_in_node = le16_to_cpu(sum.ofs_in_node);
		जाओ truncate_out;
	पूर्ण अन्यथा अगर (dn->nid == nid) अणु
		tdn.ofs_in_node = le16_to_cpu(sum.ofs_in_node);
		जाओ truncate_out;
	पूर्ण

	/* Get the node page */
	node_page = f2fs_get_node_page(sbi, nid);
	अगर (IS_ERR(node_page))
		वापस PTR_ERR(node_page);

	offset = ofs_of_node(node_page);
	ino = ino_of_node(node_page);
	f2fs_put_page(node_page, 1);

	अगर (ino != dn->inode->i_ino) अणु
		पूर्णांक ret;

		/* Deallocate previous index in the node page */
		inode = f2fs_iget_retry(sbi->sb, ino);
		अगर (IS_ERR(inode))
			वापस PTR_ERR(inode);

		ret = dquot_initialize(inode);
		अगर (ret) अणु
			iput(inode);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		inode = dn->inode;
	पूर्ण

	bidx = f2fs_start_bidx_of_node(offset, inode) +
				le16_to_cpu(sum.ofs_in_node);

	/*
	 * अगर inode page is locked, unlock temporarily, but its reference
	 * count keeps alive.
	 */
	अगर (ino == dn->inode->i_ino && dn->inode_page_locked)
		unlock_page(dn->inode_page);

	set_new_dnode(&tdn, inode, शून्य, शून्य, 0);
	अगर (f2fs_get_dnode_of_data(&tdn, bidx, LOOKUP_NODE))
		जाओ out;

	अगर (tdn.data_blkaddr == blkaddr)
		f2fs_truncate_data_blocks_range(&tdn, 1);

	f2fs_put_dnode(&tdn);
out:
	अगर (ino != dn->inode->i_ino)
		iput(inode);
	अन्यथा अगर (dn->inode_page_locked)
		lock_page(dn->inode_page);
	वापस 0;

truncate_out:
	अगर (f2fs_data_blkaddr(&tdn) == blkaddr)
		f2fs_truncate_data_blocks_range(&tdn, 1);
	अगर (dn->inode->i_ino == nid && !dn->inode_page_locked)
		unlock_page(dn->inode_page);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_recover_data(काष्ठा f2fs_sb_info *sbi, काष्ठा inode *inode,
					काष्ठा page *page)
अणु
	काष्ठा dnode_of_data dn;
	काष्ठा node_info ni;
	अचिन्हित पूर्णांक start, end;
	पूर्णांक err = 0, recovered = 0;

	/* step 1: recover xattr */
	अगर (IS_INODE(page)) अणु
		err = f2fs_recover_अंतरभूत_xattr(inode, page);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अगर (f2fs_has_xattr_block(ofs_of_node(page))) अणु
		err = f2fs_recover_xattr_data(inode, page);
		अगर (!err)
			recovered++;
		जाओ out;
	पूर्ण

	/* step 2: recover अंतरभूत data */
	err = f2fs_recover_अंतरभूत_data(inode, page);
	अगर (err) अणु
		अगर (err == 1)
			err = 0;
		जाओ out;
	पूर्ण

	/* step 3: recover data indices */
	start = f2fs_start_bidx_of_node(ofs_of_node(page), inode);
	end = start + ADDRS_PER_PAGE(page, inode);

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
retry_dn:
	err = f2fs_get_dnode_of_data(&dn, start, ALLOC_NODE);
	अगर (err) अणु
		अगर (err == -ENOMEM) अणु
			congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
			जाओ retry_dn;
		पूर्ण
		जाओ out;
	पूर्ण

	f2fs_रुको_on_page_ग_लिखोback(dn.node_page, NODE, true, true);

	err = f2fs_get_node_info(sbi, dn.nid, &ni);
	अगर (err)
		जाओ err;

	f2fs_bug_on(sbi, ni.ino != ino_of_node(page));

	अगर (ofs_of_node(dn.node_page) != ofs_of_node(page)) अणु
		f2fs_warn(sbi, "Inconsistent ofs_of_node, ino:%lu, ofs:%u, %u",
			  inode->i_ino, ofs_of_node(dn.node_page),
			  ofs_of_node(page));
		err = -EFSCORRUPTED;
		जाओ err;
	पूर्ण

	क्रम (; start < end; start++, dn.ofs_in_node++) अणु
		block_t src, dest;

		src = f2fs_data_blkaddr(&dn);
		dest = data_blkaddr(dn.inode, page, dn.ofs_in_node);

		अगर (__is_valid_data_blkaddr(src) &&
			!f2fs_is_valid_blkaddr(sbi, src, META_POR)) अणु
			err = -EFSCORRUPTED;
			जाओ err;
		पूर्ण

		अगर (__is_valid_data_blkaddr(dest) &&
			!f2fs_is_valid_blkaddr(sbi, dest, META_POR)) अणु
			err = -EFSCORRUPTED;
			जाओ err;
		पूर्ण

		/* skip recovering अगर dest is the same as src */
		अगर (src == dest)
			जारी;

		/* dest is invalid, just invalidate src block */
		अगर (dest == शून्य_ADDR) अणु
			f2fs_truncate_data_blocks_range(&dn, 1);
			जारी;
		पूर्ण

		अगर (!file_keep_isize(inode) &&
			(i_size_पढ़ो(inode) <= ((loff_t)start << PAGE_SHIFT)))
			f2fs_i_size_ग_लिखो(inode,
				(loff_t)(start + 1) << PAGE_SHIFT);

		/*
		 * dest is reserved block, invalidate src block
		 * and then reserve one new block in dnode page.
		 */
		अगर (dest == NEW_ADDR) अणु
			f2fs_truncate_data_blocks_range(&dn, 1);
			f2fs_reserve_new_block(&dn);
			जारी;
		पूर्ण

		/* dest is valid block, try to recover from src to dest */
		अगर (f2fs_is_valid_blkaddr(sbi, dest, META_POR)) अणु

			अगर (src == शून्य_ADDR) अणु
				err = f2fs_reserve_new_block(&dn);
				जबतक (err &&
				       IS_ENABLED(CONFIG_F2FS_FAULT_INJECTION))
					err = f2fs_reserve_new_block(&dn);
				/* We should not get -ENOSPC */
				f2fs_bug_on(sbi, err);
				अगर (err)
					जाओ err;
			पूर्ण
retry_prev:
			/* Check the previous node page having this index */
			err = check_index_in_prev_nodes(sbi, dest, &dn);
			अगर (err) अणु
				अगर (err == -ENOMEM) अणु
					congestion_रुको(BLK_RW_ASYNC,
							DEFAULT_IO_TIMEOUT);
					जाओ retry_prev;
				पूर्ण
				जाओ err;
			पूर्ण

			/* ग_लिखो dummy data page */
			f2fs_replace_block(sbi, &dn, src, dest,
						ni.version, false, false);
			recovered++;
		पूर्ण
	पूर्ण

	copy_node_footer(dn.node_page, page);
	fill_node_footer(dn.node_page, dn.nid, ni.ino,
					ofs_of_node(page), false);
	set_page_dirty(dn.node_page);
err:
	f2fs_put_dnode(&dn);
out:
	f2fs_notice(sbi, "recover_data: ino = %lx (i_size: %s) recovered = %d, err = %d",
		    inode->i_ino, file_keep_isize(inode) ? "keep" : "recover",
		    recovered, err);
	वापस err;
पूर्ण

अटल पूर्णांक recover_data(काष्ठा f2fs_sb_info *sbi, काष्ठा list_head *inode_list,
		काष्ठा list_head *पंचांगp_inode_list, काष्ठा list_head *dir_list)
अणु
	काष्ठा curseg_info *curseg;
	काष्ठा page *page = शून्य;
	पूर्णांक err = 0;
	block_t blkaddr;

	/* get node pages in the current segment */
	curseg = CURSEG_I(sbi, CURSEG_WARM_NODE);
	blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	जबतक (1) अणु
		काष्ठा fsync_inode_entry *entry;

		अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr, META_POR))
			अवरोध;

		f2fs_ra_meta_pages_cond(sbi, blkaddr);

		page = f2fs_get_पंचांगp_page(sbi, blkaddr);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			अवरोध;
		पूर्ण

		अगर (!is_recoverable_dnode(page)) अणु
			f2fs_put_page(page, 1);
			अवरोध;
		पूर्ण

		entry = get_fsync_inode(inode_list, ino_of_node(page));
		अगर (!entry)
			जाओ next;
		/*
		 * inode(x) | CP | inode(x) | dnode(F)
		 * In this हाल, we can lose the latest inode(x).
		 * So, call recover_inode क्रम the inode update.
		 */
		अगर (IS_INODE(page)) अणु
			err = recover_inode(entry->inode, page);
			अगर (err) अणु
				f2fs_put_page(page, 1);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (entry->last_dentry == blkaddr) अणु
			err = recover_dentry(entry->inode, page, dir_list);
			अगर (err) अणु
				f2fs_put_page(page, 1);
				अवरोध;
			पूर्ण
		पूर्ण
		err = करो_recover_data(sbi, entry->inode, page);
		अगर (err) अणु
			f2fs_put_page(page, 1);
			अवरोध;
		पूर्ण

		अगर (entry->blkaddr == blkaddr)
			list_move_tail(&entry->list, पंचांगp_inode_list);
next:
		/* check next segment */
		blkaddr = next_blkaddr_of_node(page);
		f2fs_put_page(page, 1);
	पूर्ण
	अगर (!err)
		f2fs_allocate_new_segments(sbi);
	वापस err;
पूर्ण

पूर्णांक f2fs_recover_fsync_data(काष्ठा f2fs_sb_info *sbi, bool check_only)
अणु
	काष्ठा list_head inode_list, पंचांगp_inode_list;
	काष्ठा list_head dir_list;
	पूर्णांक err;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ s_flags = sbi->sb->s_flags;
	bool need_ग_लिखोcp = false;
	bool fix_curseg_ग_लिखो_poपूर्णांकer = false;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक quota_enabled;
#पूर्ण_अगर

	अगर (s_flags & SB_RDONLY) अणु
		f2fs_info(sbi, "recover fsync data on readonly fs");
		sbi->sb->s_flags &= ~SB_RDONLY;
	पूर्ण

#अगर_घोषित CONFIG_QUOTA
	/* Needed क्रम iput() to work correctly and not trash data */
	sbi->sb->s_flags |= SB_ACTIVE;
	/* Turn on quotas so that they are updated correctly */
	quota_enabled = f2fs_enable_quota_files(sbi, s_flags & SB_RDONLY);
#पूर्ण_अगर

	fsync_entry_slab = f2fs_kmem_cache_create("f2fs_fsync_inode_entry",
			माप(काष्ठा fsync_inode_entry));
	अगर (!fsync_entry_slab) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&inode_list);
	INIT_LIST_HEAD(&पंचांगp_inode_list);
	INIT_LIST_HEAD(&dir_list);

	/* prevent checkpoपूर्णांक */
	करोwn_ग_लिखो(&sbi->cp_global_sem);

	/* step #1: find fsynced inode numbers */
	err = find_fsync_dnodes(sbi, &inode_list, check_only);
	अगर (err || list_empty(&inode_list))
		जाओ skip;

	अगर (check_only) अणु
		ret = 1;
		जाओ skip;
	पूर्ण

	need_ग_लिखोcp = true;

	/* step #2: recover data */
	err = recover_data(sbi, &inode_list, &पंचांगp_inode_list, &dir_list);
	अगर (!err)
		f2fs_bug_on(sbi, !list_empty(&inode_list));
	अन्यथा अणु
		/* restore s_flags to let iput() trash data */
		sbi->sb->s_flags = s_flags;
	पूर्ण
skip:
	fix_curseg_ग_लिखो_poपूर्णांकer = !check_only || list_empty(&inode_list);

	destroy_fsync_dnodes(&inode_list, err);
	destroy_fsync_dnodes(&पंचांगp_inode_list, err);

	/* truncate meta pages to be used by the recovery */
	truncate_inode_pages_range(META_MAPPING(sbi),
			(loff_t)MAIN_BLKADDR(sbi) << PAGE_SHIFT, -1);

	अगर (err) अणु
		truncate_inode_pages_final(NODE_MAPPING(sbi));
		truncate_inode_pages_final(META_MAPPING(sbi));
	पूर्ण

	/*
	 * If fsync data succeeds or there is no fsync data to recover,
	 * and the f2fs is not पढ़ो only, check and fix zoned block devices'
	 * ग_लिखो poपूर्णांकer consistency.
	 */
	अगर (!err && fix_curseg_ग_लिखो_poपूर्णांकer && !f2fs_पढ़ोonly(sbi->sb) &&
			f2fs_sb_has_blkzoned(sbi)) अणु
		err = f2fs_fix_curseg_ग_लिखो_poपूर्णांकer(sbi);
		ret = err;
	पूर्ण

	अगर (!err)
		clear_sbi_flag(sbi, SBI_POR_DOING);

	up_ग_लिखो(&sbi->cp_global_sem);

	/* let's drop all the directory inodes क्रम clean checkpoपूर्णांक */
	destroy_fsync_dnodes(&dir_list, err);

	अगर (need_ग_लिखोcp) अणु
		set_sbi_flag(sbi, SBI_IS_RECOVERED);

		अगर (!err) अणु
			काष्ठा cp_control cpc = अणु
				.reason = CP_RECOVERY,
			पूर्ण;
			err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
		पूर्ण
	पूर्ण

	kmem_cache_destroy(fsync_entry_slab);
out:
#अगर_घोषित CONFIG_QUOTA
	/* Turn quotas off */
	अगर (quota_enabled)
		f2fs_quota_off_umount(sbi->sb);
#पूर्ण_अगर
	sbi->sb->s_flags = s_flags; /* Restore SB_RDONLY status */

	वापस ret ? ret : err;
पूर्ण
