<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/hfsplus/super.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfs.h>
#समावेश <linux/nls.h>

अटल काष्ठा inode *hfsplus_alloc_inode(काष्ठा super_block *sb);
अटल व्योम hfsplus_मुक्त_inode(काष्ठा inode *inode);

#समावेश "hfsplus_fs.h"
#समावेश "xattr.h"

अटल पूर्णांक hfsplus_प्रणाली_पढ़ो_inode(काष्ठा inode *inode)
अणु
	काष्ठा hfsplus_vh *vhdr = HFSPLUS_SB(inode->i_sb)->s_vhdr;

	चयन (inode->i_ino) अणु
	हाल HFSPLUS_EXT_CNID:
		hfsplus_inode_पढ़ो_विभाजन(inode, &vhdr->ext_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		अवरोध;
	हाल HFSPLUS_CAT_CNID:
		hfsplus_inode_पढ़ो_विभाजन(inode, &vhdr->cat_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		अवरोध;
	हाल HFSPLUS_ALLOC_CNID:
		hfsplus_inode_पढ़ो_विभाजन(inode, &vhdr->alloc_file);
		inode->i_mapping->a_ops = &hfsplus_aops;
		अवरोध;
	हाल HFSPLUS_START_CNID:
		hfsplus_inode_पढ़ो_विभाजन(inode, &vhdr->start_file);
		अवरोध;
	हाल HFSPLUS_ATTR_CNID:
		hfsplus_inode_पढ़ो_विभाजन(inode, &vhdr->attr_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा inode *hfsplus_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा hfs_find_data fd;
	काष्ठा inode *inode;
	पूर्णांक err;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	INIT_LIST_HEAD(&HFSPLUS_I(inode)->खोलो_dir_list);
	spin_lock_init(&HFSPLUS_I(inode)->खोलो_dir_lock);
	mutex_init(&HFSPLUS_I(inode)->extents_lock);
	HFSPLUS_I(inode)->flags = 0;
	HFSPLUS_I(inode)->extent_state = 0;
	HFSPLUS_I(inode)->rsrc_inode = शून्य;
	atomic_set(&HFSPLUS_I(inode)->खोलोcnt, 0);

	अगर (inode->i_ino >= HFSPLUS_FIRSTUSER_CNID ||
	    inode->i_ino == HFSPLUS_ROOT_CNID) अणु
		err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &fd);
		अगर (!err) अणु
			err = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
			अगर (!err)
				err = hfsplus_cat_पढ़ो_inode(inode, &fd);
			hfs_find_निकास(&fd);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = hfsplus_प्रणाली_पढ़ो_inode(inode);
	पूर्ण

	अगर (err) अणु
		iget_failed(inode);
		वापस ERR_PTR(err);
	पूर्ण

	unlock_new_inode(inode);
	वापस inode;
पूर्ण

अटल पूर्णांक hfsplus_प्रणाली_ग_लिखो_inode(काष्ठा inode *inode)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);
	काष्ठा hfsplus_vh *vhdr = sbi->s_vhdr;
	काष्ठा hfsplus_विभाजन_raw *विभाजन;
	काष्ठा hfs_btree *tree = शून्य;

	चयन (inode->i_ino) अणु
	हाल HFSPLUS_EXT_CNID:
		विभाजन = &vhdr->ext_file;
		tree = sbi->ext_tree;
		अवरोध;
	हाल HFSPLUS_CAT_CNID:
		विभाजन = &vhdr->cat_file;
		tree = sbi->cat_tree;
		अवरोध;
	हाल HFSPLUS_ALLOC_CNID:
		विभाजन = &vhdr->alloc_file;
		अवरोध;
	हाल HFSPLUS_START_CNID:
		विभाजन = &vhdr->start_file;
		अवरोध;
	हाल HFSPLUS_ATTR_CNID:
		विभाजन = &vhdr->attr_file;
		tree = sbi->attr_tree;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	अगर (विभाजन->total_size != cpu_to_be64(inode->i_size)) अणु
		set_bit(HFSPLUS_SB_WRITEBACKUP, &sbi->flags);
		hfsplus_mark_mdb_dirty(inode->i_sb);
	पूर्ण
	hfsplus_inode_ग_लिखो_विभाजन(inode, विभाजन);
	अगर (tree) अणु
		पूर्णांक err = hfs_btree_ग_लिखो(tree);

		अगर (err) अणु
			pr_err("b-tree write err: %d, ino %lu\n",
			       err, inode->i_ino);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_ग_लिखो_inode(काष्ठा inode *inode,
		काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err;

	hfs_dbg(INODE, "hfsplus_write_inode: %lu\n", inode->i_ino);

	err = hfsplus_ext_ग_लिखो_extent(inode);
	अगर (err)
		वापस err;

	अगर (inode->i_ino >= HFSPLUS_FIRSTUSER_CNID ||
	    inode->i_ino == HFSPLUS_ROOT_CNID)
		वापस hfsplus_cat_ग_लिखो_inode(inode);
	अन्यथा
		वापस hfsplus_प्रणाली_ग_लिखो_inode(inode);
पूर्ण

अटल व्योम hfsplus_evict_inode(काष्ठा inode *inode)
अणु
	hfs_dbg(INODE, "hfsplus_evict_inode: %lu\n", inode->i_ino);
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	अगर (HFSPLUS_IS_RSRC(inode)) अणु
		HFSPLUS_I(HFSPLUS_I(inode)->rsrc_inode)->rsrc_inode = शून्य;
		iput(HFSPLUS_I(inode)->rsrc_inode);
	पूर्ण
पूर्ण

अटल पूर्णांक hfsplus_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा hfsplus_vh *vhdr = sbi->s_vhdr;
	पूर्णांक ग_लिखो_backup = 0;
	पूर्णांक error, error2;

	अगर (!रुको)
		वापस 0;

	hfs_dbg(SUPER, "hfsplus_sync_fs\n");

	/*
	 * Explicitly ग_लिखो out the special metadata inodes.
	 *
	 * While these special inodes are marked as hashed and written
	 * out periकरोcically by the flusher thपढ़ोs we redirty them
	 * during ग_लिखोout of normal inodes, and thus the lअगरe lock
	 * prevents us from getting the latest state to disk.
	 */
	error = filemap_ग_लिखो_and_रुको(sbi->cat_tree->inode->i_mapping);
	error2 = filemap_ग_लिखो_and_रुको(sbi->ext_tree->inode->i_mapping);
	अगर (!error)
		error = error2;
	अगर (sbi->attr_tree) अणु
		error2 =
		    filemap_ग_लिखो_and_रुको(sbi->attr_tree->inode->i_mapping);
		अगर (!error)
			error = error2;
	पूर्ण
	error2 = filemap_ग_लिखो_and_रुको(sbi->alloc_file->i_mapping);
	अगर (!error)
		error = error2;

	mutex_lock(&sbi->vh_mutex);
	mutex_lock(&sbi->alloc_mutex);
	vhdr->मुक्त_blocks = cpu_to_be32(sbi->मुक्त_blocks);
	vhdr->next_cnid = cpu_to_be32(sbi->next_cnid);
	vhdr->folder_count = cpu_to_be32(sbi->folder_count);
	vhdr->file_count = cpu_to_be32(sbi->file_count);

	अगर (test_and_clear_bit(HFSPLUS_SB_WRITEBACKUP, &sbi->flags)) अणु
		स_नकल(sbi->s_backup_vhdr, sbi->s_vhdr, माप(*sbi->s_vhdr));
		ग_लिखो_backup = 1;
	पूर्ण

	error2 = hfsplus_submit_bio(sb,
				   sbi->part_start + HFSPLUS_VOLHEAD_SECTOR,
				   sbi->s_vhdr_buf, शून्य, REQ_OP_WRITE,
				   REQ_SYNC);
	अगर (!error)
		error = error2;
	अगर (!ग_लिखो_backup)
		जाओ out;

	error2 = hfsplus_submit_bio(sb,
				  sbi->part_start + sbi->sect_count - 2,
				  sbi->s_backup_vhdr_buf, शून्य, REQ_OP_WRITE,
				  REQ_SYNC);
	अगर (!error)
		error2 = error;
out:
	mutex_unlock(&sbi->alloc_mutex);
	mutex_unlock(&sbi->vh_mutex);

	अगर (!test_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags))
		blkdev_issue_flush(sb->s_bdev);

	वापस error;
पूर्ण

अटल व्योम delayed_sync_fs(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;
	काष्ठा hfsplus_sb_info *sbi;

	sbi = container_of(work, काष्ठा hfsplus_sb_info, sync_work.work);

	spin_lock(&sbi->work_lock);
	sbi->work_queued = 0;
	spin_unlock(&sbi->work_lock);

	err = hfsplus_sync_fs(sbi->alloc_file->i_sb, 1);
	अगर (err)
		pr_err("delayed sync fs err %d\n", err);
पूर्ण

व्योम hfsplus_mark_mdb_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	अचिन्हित दीर्घ delay;

	अगर (sb_rकरोnly(sb))
		वापस;

	spin_lock(&sbi->work_lock);
	अगर (!sbi->work_queued) अणु
		delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
		queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->sync_work, delay);
		sbi->work_queued = 1;
	पूर्ण
	spin_unlock(&sbi->work_lock);
पूर्ण

अटल व्योम hfsplus_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);

	hfs_dbg(SUPER, "hfsplus_put_super\n");

	cancel_delayed_work_sync(&sbi->sync_work);

	अगर (!sb_rकरोnly(sb) && sbi->s_vhdr) अणु
		काष्ठा hfsplus_vh *vhdr = sbi->s_vhdr;

		vhdr->modअगरy_date = hfsp_now2mt();
		vhdr->attributes |= cpu_to_be32(HFSPLUS_VOL_UNMNT);
		vhdr->attributes &= cpu_to_be32(~HFSPLUS_VOL_INCNSTNT);

		hfsplus_sync_fs(sb, 1);
	पूर्ण

	hfs_btree_बंद(sbi->attr_tree);
	hfs_btree_बंद(sbi->cat_tree);
	hfs_btree_बंद(sbi->ext_tree);
	iput(sbi->alloc_file);
	iput(sbi->hidden_dir);
	kमुक्त(sbi->s_vhdr_buf);
	kमुक्त(sbi->s_backup_vhdr_buf);
	unload_nls(sbi->nls);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
पूर्ण

अटल पूर्णांक hfsplus_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = HFSPLUS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->total_blocks << sbi->fs_shअगरt;
	buf->f_bमुक्त = sbi->मुक्त_blocks << sbi->fs_shअगरt;
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_files = 0xFFFFFFFF;
	buf->f_fमुक्त = 0xFFFFFFFF - sbi->next_cnid;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = HFSPLUS_MAX_STRLEN;

	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		वापस 0;
	अगर (!(*flags & SB_RDONLY)) अणु
		काष्ठा hfsplus_vh *vhdr = HFSPLUS_SB(sb)->s_vhdr;
		पूर्णांक क्रमce = 0;

		अगर (!hfsplus_parse_options_remount(data, &क्रमce))
			वापस -EINVAL;

		अगर (!(vhdr->attributes & cpu_to_be32(HFSPLUS_VOL_UNMNT))) अणु
			pr_warn("filesystem was not cleanly unmounted, running fsck.hfsplus is recommended.  leaving read-only.\n");
			sb->s_flags |= SB_RDONLY;
			*flags |= SB_RDONLY;
		पूर्ण अन्यथा अगर (क्रमce) अणु
			/* nothing */
		पूर्ण अन्यथा अगर (vhdr->attributes &
				cpu_to_be32(HFSPLUS_VOL_SOFTLOCK)) अणु
			pr_warn("filesystem is marked locked, leaving read-only.\n");
			sb->s_flags |= SB_RDONLY;
			*flags |= SB_RDONLY;
		पूर्ण अन्यथा अगर (vhdr->attributes &
				cpu_to_be32(HFSPLUS_VOL_JOURNALED)) अणु
			pr_warn("filesystem is marked journaled, leaving read-only.\n");
			sb->s_flags |= SB_RDONLY;
			*flags |= SB_RDONLY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations hfsplus_sops = अणु
	.alloc_inode	= hfsplus_alloc_inode,
	.मुक्त_inode	= hfsplus_मुक्त_inode,
	.ग_लिखो_inode	= hfsplus_ग_लिखो_inode,
	.evict_inode	= hfsplus_evict_inode,
	.put_super	= hfsplus_put_super,
	.sync_fs	= hfsplus_sync_fs,
	.statfs		= hfsplus_statfs,
	.remount_fs	= hfsplus_remount,
	.show_options	= hfsplus_show_options,
पूर्ण;

अटल पूर्णांक hfsplus_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा hfsplus_vh *vhdr;
	काष्ठा hfsplus_sb_info *sbi;
	hfsplus_cat_entry entry;
	काष्ठा hfs_find_data fd;
	काष्ठा inode *root, *inode;
	काष्ठा qstr str;
	काष्ठा nls_table *nls = शून्य;
	u64 last_fs_block, last_fs_page;
	पूर्णांक err;

	err = -ENOMEM;
	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		जाओ out;

	sb->s_fs_info = sbi;
	mutex_init(&sbi->alloc_mutex);
	mutex_init(&sbi->vh_mutex);
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->sync_work, delayed_sync_fs);
	hfsplus_fill_शेषs(sbi);

	err = -EINVAL;
	अगर (!hfsplus_parse_options(data, sbi)) अणु
		pr_err("unable to parse mount options\n");
		जाओ out_unload_nls;
	पूर्ण

	/* temporarily use utf8 to correctly find the hidden dir below */
	nls = sbi->nls;
	sbi->nls = load_nls("utf8");
	अगर (!sbi->nls) अणु
		pr_err("unable to load nls for utf8\n");
		जाओ out_unload_nls;
	पूर्ण

	/* Grab the volume header */
	अगर (hfsplus_पढ़ो_wrapper(sb)) अणु
		अगर (!silent)
			pr_warn("unable to find HFS+ superblock\n");
		जाओ out_unload_nls;
	पूर्ण
	vhdr = sbi->s_vhdr;

	/* Copy parts of the volume header पूर्णांकo the superblock */
	sb->s_magic = HFSPLUS_VOLHEAD_SIG;
	अगर (be16_to_cpu(vhdr->version) < HFSPLUS_MIN_VERSION ||
	    be16_to_cpu(vhdr->version) > HFSPLUS_CURRENT_VERSION) अणु
		pr_err("wrong filesystem version\n");
		जाओ out_मुक्त_vhdr;
	पूर्ण
	sbi->total_blocks = be32_to_cpu(vhdr->total_blocks);
	sbi->मुक्त_blocks = be32_to_cpu(vhdr->मुक्त_blocks);
	sbi->next_cnid = be32_to_cpu(vhdr->next_cnid);
	sbi->file_count = be32_to_cpu(vhdr->file_count);
	sbi->folder_count = be32_to_cpu(vhdr->folder_count);
	sbi->data_clump_blocks =
		be32_to_cpu(vhdr->data_clump_sz) >> sbi->alloc_blksz_shअगरt;
	अगर (!sbi->data_clump_blocks)
		sbi->data_clump_blocks = 1;
	sbi->rsrc_clump_blocks =
		be32_to_cpu(vhdr->rsrc_clump_sz) >> sbi->alloc_blksz_shअगरt;
	अगर (!sbi->rsrc_clump_blocks)
		sbi->rsrc_clump_blocks = 1;

	err = -EFBIG;
	last_fs_block = sbi->total_blocks - 1;
	last_fs_page = (last_fs_block << sbi->alloc_blksz_shअगरt) >>
			PAGE_SHIFT;

	अगर ((last_fs_block > (sector_t)(~0ULL) >> (sbi->alloc_blksz_shअगरt - 9)) ||
	    (last_fs_page > (pgoff_t)(~0ULL))) अणु
		pr_err("filesystem size too large\n");
		जाओ out_मुक्त_vhdr;
	पूर्ण

	/* Set up operations so we can load metadata */
	sb->s_op = &hfsplus_sops;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;

	अगर (!(vhdr->attributes & cpu_to_be32(HFSPLUS_VOL_UNMNT))) अणु
		pr_warn("Filesystem was not cleanly unmounted, running fsck.hfsplus is recommended.  mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण अन्यथा अगर (test_and_clear_bit(HFSPLUS_SB_FORCE, &sbi->flags)) अणु
		/* nothing */
	पूर्ण अन्यथा अगर (vhdr->attributes & cpu_to_be32(HFSPLUS_VOL_SOFTLOCK)) अणु
		pr_warn("Filesystem is marked locked, mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण अन्यथा अगर ((vhdr->attributes & cpu_to_be32(HFSPLUS_VOL_JOURNALED)) &&
			!sb_rकरोnly(sb)) अणु
		pr_warn("write access to a journaled filesystem is not supported, use the force option at your own risk, mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	पूर्ण

	err = -EINVAL;

	/* Load metadata objects (B*Trees) */
	sbi->ext_tree = hfs_btree_खोलो(sb, HFSPLUS_EXT_CNID);
	अगर (!sbi->ext_tree) अणु
		pr_err("failed to load extents file\n");
		जाओ out_मुक्त_vhdr;
	पूर्ण
	sbi->cat_tree = hfs_btree_खोलो(sb, HFSPLUS_CAT_CNID);
	अगर (!sbi->cat_tree) अणु
		pr_err("failed to load catalog file\n");
		जाओ out_बंद_ext_tree;
	पूर्ण
	atomic_set(&sbi->attr_tree_state, HFSPLUS_EMPTY_ATTR_TREE);
	अगर (vhdr->attr_file.total_blocks != 0) अणु
		sbi->attr_tree = hfs_btree_खोलो(sb, HFSPLUS_ATTR_CNID);
		अगर (!sbi->attr_tree) अणु
			pr_err("failed to load attributes file\n");
			जाओ out_बंद_cat_tree;
		पूर्ण
		atomic_set(&sbi->attr_tree_state, HFSPLUS_VALID_ATTR_TREE);
	पूर्ण
	sb->s_xattr = hfsplus_xattr_handlers;

	inode = hfsplus_iget(sb, HFSPLUS_ALLOC_CNID);
	अगर (IS_ERR(inode)) अणु
		pr_err("failed to load allocation file\n");
		err = PTR_ERR(inode);
		जाओ out_बंद_attr_tree;
	पूर्ण
	sbi->alloc_file = inode;

	/* Load the root directory */
	root = hfsplus_iget(sb, HFSPLUS_ROOT_CNID);
	अगर (IS_ERR(root)) अणु
		pr_err("failed to load root directory\n");
		err = PTR_ERR(root);
		जाओ out_put_alloc_file;
	पूर्ण

	sb->s_d_op = &hfsplus_dentry_operations;
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		err = -ENOMEM;
		जाओ out_put_alloc_file;
	पूर्ण

	str.len = माप(HFSP_HIDDENसूची_NAME) - 1;
	str.name = HFSP_HIDDENसूची_NAME;
	err = hfs_find_init(sbi->cat_tree, &fd);
	अगर (err)
		जाओ out_put_root;
	err = hfsplus_cat_build_key(sb, fd.search_key, HFSPLUS_ROOT_CNID, &str);
	अगर (unlikely(err < 0))
		जाओ out_put_root;
	अगर (!hfs_brec_पढ़ो(&fd, &entry, माप(entry))) अणु
		hfs_find_निकास(&fd);
		अगर (entry.type != cpu_to_be16(HFSPLUS_FOLDER)) अणु
			err = -EINVAL;
			जाओ out_put_root;
		पूर्ण
		inode = hfsplus_iget(sb, be32_to_cpu(entry.folder.id));
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			जाओ out_put_root;
		पूर्ण
		sbi->hidden_dir = inode;
	पूर्ण अन्यथा
		hfs_find_निकास(&fd);

	अगर (!sb_rकरोnly(sb)) अणु
		/*
		 * H+LX == hfsplusutils, H+Lx == this driver, H+lx is unused
		 * all three are रेजिस्टरed with Apple क्रम our use
		 */
		vhdr->last_mount_vers = cpu_to_be32(HFSP_MOUNT_VERSION);
		vhdr->modअगरy_date = hfsp_now2mt();
		be32_add_cpu(&vhdr->ग_लिखो_count, 1);
		vhdr->attributes &= cpu_to_be32(~HFSPLUS_VOL_UNMNT);
		vhdr->attributes |= cpu_to_be32(HFSPLUS_VOL_INCNSTNT);
		hfsplus_sync_fs(sb, 1);

		अगर (!sbi->hidden_dir) अणु
			mutex_lock(&sbi->vh_mutex);
			sbi->hidden_dir = hfsplus_new_inode(sb, root, S_IFसूची);
			अगर (!sbi->hidden_dir) अणु
				mutex_unlock(&sbi->vh_mutex);
				err = -ENOMEM;
				जाओ out_put_root;
			पूर्ण
			err = hfsplus_create_cat(sbi->hidden_dir->i_ino, root,
						 &str, sbi->hidden_dir);
			अगर (err) अणु
				mutex_unlock(&sbi->vh_mutex);
				जाओ out_put_hidden_dir;
			पूर्ण

			err = hfsplus_init_security(sbi->hidden_dir,
							root, &str);
			अगर (err == -EOPNOTSUPP)
				err = 0; /* Operation is not supported. */
			अन्यथा अगर (err) अणु
				/*
				 * Try to delete anyway without
				 * error analysis.
				 */
				hfsplus_delete_cat(sbi->hidden_dir->i_ino,
							root, &str);
				mutex_unlock(&sbi->vh_mutex);
				जाओ out_put_hidden_dir;
			पूर्ण

			mutex_unlock(&sbi->vh_mutex);
			hfsplus_mark_inode_dirty(sbi->hidden_dir,
						 HFSPLUS_I_CAT_सूचीTY);
		पूर्ण
	पूर्ण

	unload_nls(sbi->nls);
	sbi->nls = nls;
	वापस 0;

out_put_hidden_dir:
	cancel_delayed_work_sync(&sbi->sync_work);
	iput(sbi->hidden_dir);
out_put_root:
	dput(sb->s_root);
	sb->s_root = शून्य;
out_put_alloc_file:
	iput(sbi->alloc_file);
out_बंद_attr_tree:
	hfs_btree_बंद(sbi->attr_tree);
out_बंद_cat_tree:
	hfs_btree_बंद(sbi->cat_tree);
out_बंद_ext_tree:
	hfs_btree_बंद(sbi->ext_tree);
out_मुक्त_vhdr:
	kमुक्त(sbi->s_vhdr_buf);
	kमुक्त(sbi->s_backup_vhdr_buf);
out_unload_nls:
	unload_nls(sbi->nls);
	unload_nls(nls);
	kमुक्त(sbi);
out:
	वापस err;
पूर्ण

MODULE_AUTHOR("Brad Boyer");
MODULE_DESCRIPTION("Extended Macintosh Filesystem");
MODULE_LICENSE("GPL");

अटल काष्ठा kmem_cache *hfsplus_inode_cachep;

अटल काष्ठा inode *hfsplus_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा hfsplus_inode_info *i;

	i = kmem_cache_alloc(hfsplus_inode_cachep, GFP_KERNEL);
	वापस i ? &i->vfs_inode : शून्य;
पूर्ण

अटल व्योम hfsplus_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(hfsplus_inode_cachep, HFSPLUS_I(inode));
पूर्ण

#घोषणा HFSPLUS_INODE_SIZE	माप(काष्ठा hfsplus_inode_info)

अटल काष्ठा dentry *hfsplus_mount(काष्ठा file_प्रणाली_type *fs_type,
			  पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, hfsplus_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type hfsplus_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "hfsplus",
	.mount		= hfsplus_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("hfsplus");

अटल व्योम hfsplus_init_once(व्योम *p)
अणु
	काष्ठा hfsplus_inode_info *i = p;

	inode_init_once(&i->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_hfsplus_fs(व्योम)
अणु
	पूर्णांक err;

	hfsplus_inode_cachep = kmem_cache_create("hfsplus_icache",
		HFSPLUS_INODE_SIZE, 0, SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT,
		hfsplus_init_once);
	अगर (!hfsplus_inode_cachep)
		वापस -ENOMEM;
	err = hfsplus_create_attr_tree_cache();
	अगर (err)
		जाओ destroy_inode_cache;
	err = रेजिस्टर_fileप्रणाली(&hfsplus_fs_type);
	अगर (err)
		जाओ destroy_attr_tree_cache;
	वापस 0;

destroy_attr_tree_cache:
	hfsplus_destroy_attr_tree_cache();

destroy_inode_cache:
	kmem_cache_destroy(hfsplus_inode_cachep);

	वापस err;
पूर्ण

अटल व्योम __निकास निकास_hfsplus_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&hfsplus_fs_type);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	hfsplus_destroy_attr_tree_cache();
	kmem_cache_destroy(hfsplus_inode_cachep);
पूर्ण

module_init(init_hfsplus_fs)
module_निकास(निकास_hfsplus_fs)
