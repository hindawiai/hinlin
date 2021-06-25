<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/inode.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Modअगरied क्रम Amiga FFS fileप्रणाली.
 *
 *  (C) 1992  Eric Youngdale Modअगरied क्रम ISO9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 */
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/gfp.h>
#समावेश "affs.h"

काष्ठा inode *affs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा affs_sb_info	*sbi = AFFS_SB(sb);
	काष्ठा buffer_head	*bh;
	काष्ठा affs_tail	*tail;
	काष्ठा inode		*inode;
	u32			 block;
	u32			 size;
	u32			 prot;
	u16			 id;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	pr_debug("affs_iget(%lu)\n", inode->i_ino);

	block = inode->i_ino;
	bh = affs_bपढ़ो(sb, block);
	अगर (!bh) अणु
		affs_warning(sb, "read_inode", "Cannot read block %d", block);
		जाओ bad_inode;
	पूर्ण
	अगर (affs_checksum_block(sb, bh) || be32_to_cpu(AFFS_HEAD(bh)->ptype) != T_SHORT) अणु
		affs_warning(sb,"read_inode",
			   "Checksum or type (ptype=%d) error on inode %d",
			   AFFS_HEAD(bh)->ptype, block);
		जाओ bad_inode;
	पूर्ण

	tail = AFFS_TAIL(sb, bh);
	prot = be32_to_cpu(tail->protect);

	inode->i_size = 0;
	set_nlink(inode, 1);
	inode->i_mode = 0;
	AFFS_I(inode)->i_extcnt = 1;
	AFFS_I(inode)->i_ext_last = ~1;
	AFFS_I(inode)->i_protect = prot;
	atomic_set(&AFFS_I(inode)->i_खोलोcnt, 0);
	AFFS_I(inode)->i_blkcnt = 0;
	AFFS_I(inode)->i_lc = शून्य;
	AFFS_I(inode)->i_lc_size = 0;
	AFFS_I(inode)->i_lc_shअगरt = 0;
	AFFS_I(inode)->i_lc_mask = 0;
	AFFS_I(inode)->i_ac = शून्य;
	AFFS_I(inode)->i_ext_bh = शून्य;
	AFFS_I(inode)->mmu_निजी = 0;
	AFFS_I(inode)->i_lastalloc = 0;
	AFFS_I(inode)->i_pa_cnt = 0;

	अगर (affs_test_opt(sbi->s_flags, SF_SETMODE))
		inode->i_mode = sbi->s_mode;
	अन्यथा
		inode->i_mode = affs_prot_to_mode(prot);

	id = be16_to_cpu(tail->uid);
	अगर (id == 0 || affs_test_opt(sbi->s_flags, SF_SETUID))
		inode->i_uid = sbi->s_uid;
	अन्यथा अगर (id == 0xFFFF && affs_test_opt(sbi->s_flags, SF_MUFS))
		i_uid_ग_लिखो(inode, 0);
	अन्यथा
		i_uid_ग_लिखो(inode, id);

	id = be16_to_cpu(tail->gid);
	अगर (id == 0 || affs_test_opt(sbi->s_flags, SF_SETGID))
		inode->i_gid = sbi->s_gid;
	अन्यथा अगर (id == 0xFFFF && affs_test_opt(sbi->s_flags, SF_MUFS))
		i_gid_ग_लिखो(inode, 0);
	अन्यथा
		i_gid_ग_लिखो(inode, id);

	चयन (be32_to_cpu(tail->stype)) अणु
	हाल ST_ROOT:
		inode->i_uid = sbi->s_uid;
		inode->i_gid = sbi->s_gid;
		fallthrough;
	हाल ST_USERसूची:
		अगर (be32_to_cpu(tail->stype) == ST_USERसूची ||
		    affs_test_opt(sbi->s_flags, SF_SETMODE)) अणु
			अगर (inode->i_mode & S_IRUSR)
				inode->i_mode |= S_IXUSR;
			अगर (inode->i_mode & S_IRGRP)
				inode->i_mode |= S_IXGRP;
			अगर (inode->i_mode & S_IROTH)
				inode->i_mode |= S_IXOTH;
			inode->i_mode |= S_IFसूची;
		पूर्ण अन्यथा
			inode->i_mode = S_IRUGO | S_IXUGO | S_IWUSR | S_IFसूची;
		/* Maybe it should be controlled by mount parameter? */
		//inode->i_mode |= S_ISVTX;
		inode->i_op = &affs_dir_inode_operations;
		inode->i_fop = &affs_dir_operations;
		अवरोध;
	हाल ST_LINKसूची:
#अगर 0
		affs_warning(sb, "read_inode", "inode is LINKDIR");
		जाओ bad_inode;
#अन्यथा
		inode->i_mode |= S_IFसूची;
		/* ... and leave ->i_op and ->i_fop poपूर्णांकing to empty */
		अवरोध;
#पूर्ण_अगर
	हाल ST_LINKखाता:
		affs_warning(sb, "read_inode", "inode is LINKFILE");
		जाओ bad_inode;
	हाल ST_खाता:
		size = be32_to_cpu(tail->size);
		inode->i_mode |= S_IFREG;
		AFFS_I(inode)->mmu_निजी = inode->i_size = size;
		अगर (inode->i_size) अणु
			AFFS_I(inode)->i_blkcnt = (size - 1) /
					       sbi->s_data_blksize + 1;
			AFFS_I(inode)->i_extcnt = (AFFS_I(inode)->i_blkcnt - 1) /
					       sbi->s_hashsize + 1;
		पूर्ण
		अगर (tail->link_chain)
			set_nlink(inode, 2);
		inode->i_mapping->a_ops = affs_test_opt(sbi->s_flags, SF_OFS) ?
					  &affs_aops_ofs : &affs_aops;
		inode->i_op = &affs_file_inode_operations;
		inode->i_fop = &affs_file_operations;
		अवरोध;
	हाल ST_SOFTLINK:
		inode->i_size = म_माप((अक्षर *)AFFS_HEAD(bh)->table);
		inode->i_mode |= S_IFLNK;
		inode_nohighmem(inode);
		inode->i_op = &affs_symlink_inode_operations;
		inode->i_data.a_ops = &affs_symlink_aops;
		अवरोध;
	पूर्ण

	inode->i_mसमय.tv_sec = inode->i_aसमय.tv_sec = inode->i_स_समय.tv_sec
		       = (be32_to_cpu(tail->change.days) * 86400LL +
		         be32_to_cpu(tail->change.mins) * 60 +
			 be32_to_cpu(tail->change.ticks) / 50 +
			 AFFS_EPOCH_DELTA) +
			 sys_tz.tz_minuteswest * 60;
	inode->i_mसमय.tv_nsec = inode->i_स_समय.tv_nsec = inode->i_aसमय.tv_nsec = 0;
	affs_brअन्यथा(bh);
	unlock_new_inode(inode);
	वापस inode;

bad_inode:
	affs_brअन्यथा(bh);
	iget_failed(inode);
	वापस ERR_PTR(-EIO);
पूर्ण

पूर्णांक
affs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा super_block	*sb = inode->i_sb;
	काष्ठा buffer_head	*bh;
	काष्ठा affs_tail	*tail;
	uid_t			 uid;
	gid_t			 gid;

	pr_debug("write_inode(%lu)\n", inode->i_ino);

	अगर (!inode->i_nlink)
		// possibly मुक्त block
		वापस 0;
	bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh) अणु
		affs_error(sb,"write_inode","Cannot read block %lu",inode->i_ino);
		वापस -EIO;
	पूर्ण
	tail = AFFS_TAIL(sb, bh);
	अगर (tail->stype == cpu_to_be32(ST_ROOT)) अणु
		affs_secs_to_datestamp(inode->i_mसमय.tv_sec,
				       &AFFS_ROOT_TAIL(sb, bh)->root_change);
	पूर्ण अन्यथा अणु
		tail->protect = cpu_to_be32(AFFS_I(inode)->i_protect);
		tail->size = cpu_to_be32(inode->i_size);
		affs_secs_to_datestamp(inode->i_mसमय.tv_sec, &tail->change);
		अगर (!(inode->i_ino == AFFS_SB(sb)->s_root_block)) अणु
			uid = i_uid_पढ़ो(inode);
			gid = i_gid_पढ़ो(inode);
			अगर (affs_test_opt(AFFS_SB(sb)->s_flags, SF_MUFS)) अणु
				अगर (uid == 0 || uid == 0xFFFF)
					uid = uid ^ ~0;
				अगर (gid == 0 || gid == 0xFFFF)
					gid = gid ^ ~0;
			पूर्ण
			अगर (!affs_test_opt(AFFS_SB(sb)->s_flags, SF_SETUID))
				tail->uid = cpu_to_be16(uid);
			अगर (!affs_test_opt(AFFS_SB(sb)->s_flags, SF_SETGID))
				tail->gid = cpu_to_be16(gid);
		पूर्ण
	पूर्ण
	affs_fix_checksum(sb, bh);
	mark_buffer_dirty_inode(bh, inode);
	affs_brअन्यथा(bh);
	affs_मुक्त_pपुनः_स्मृति(inode);
	वापस 0;
पूर्ण

पूर्णांक
affs_notअगरy_change(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	pr_debug("notify_change(%lu,0x%x)\n", inode->i_ino, attr->ia_valid);

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		जाओ out;

	अगर (((attr->ia_valid & ATTR_UID) &&
	      affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_SETUID)) ||
	    ((attr->ia_valid & ATTR_GID) &&
	      affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_SETGID)) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     (AFFS_SB(inode->i_sb)->s_flags &
	      (AFFS_MOUNT_SF_SETMODE | AFFS_MOUNT_SF_IMMUTABLE)))) अणु
		अगर (!affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_QUIET))
			error = -EPERM;
		जाओ out;
	पूर्ण

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;

		truncate_setsize(inode, attr->ia_size);
		affs_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);

	अगर (attr->ia_valid & ATTR_MODE)
		affs_mode_to_prot(inode);
out:
	वापस error;
पूर्ण

व्योम
affs_evict_inode(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ cache_page;
	pr_debug("evict_inode(ino=%lu, nlink=%u)\n",
		 inode->i_ino, inode->i_nlink);
	truncate_inode_pages_final(&inode->i_data);

	अगर (!inode->i_nlink) अणु
		inode->i_size = 0;
		affs_truncate(inode);
	पूर्ण

	invalidate_inode_buffers(inode);
	clear_inode(inode);
	affs_मुक्त_pपुनः_स्मृति(inode);
	cache_page = (अचिन्हित दीर्घ)AFFS_I(inode)->i_lc;
	अगर (cache_page) अणु
		pr_debug("freeing ext cache\n");
		AFFS_I(inode)->i_lc = शून्य;
		AFFS_I(inode)->i_ac = शून्य;
		मुक्त_page(cache_page);
	पूर्ण
	affs_brअन्यथा(AFFS_I(inode)->i_ext_bh);
	AFFS_I(inode)->i_ext_last = ~1;
	AFFS_I(inode)->i_ext_bh = शून्य;

	अगर (!inode->i_nlink)
		affs_मुक्त_block(inode->i_sb, inode->i_ino);
पूर्ण

काष्ठा inode *
affs_new_inode(काष्ठा inode *dir)
अणु
	काष्ठा super_block	*sb = dir->i_sb;
	काष्ठा inode		*inode;
	u32			 block;
	काष्ठा buffer_head	*bh;

	अगर (!(inode = new_inode(sb)))
		जाओ err_inode;

	अगर (!(block = affs_alloc_block(dir, dir->i_ino)))
		जाओ err_block;

	bh = affs_getzeroblk(sb, block);
	अगर (!bh)
		जाओ err_bh;
	mark_buffer_dirty_inode(bh, inode);
	affs_brअन्यथा(bh);

	inode->i_uid     = current_fsuid();
	inode->i_gid     = current_fsgid();
	inode->i_ino     = block;
	set_nlink(inode, 1);
	inode->i_mसमय   = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	atomic_set(&AFFS_I(inode)->i_खोलोcnt, 0);
	AFFS_I(inode)->i_blkcnt = 0;
	AFFS_I(inode)->i_lc = शून्य;
	AFFS_I(inode)->i_lc_size = 0;
	AFFS_I(inode)->i_lc_shअगरt = 0;
	AFFS_I(inode)->i_lc_mask = 0;
	AFFS_I(inode)->i_ac = शून्य;
	AFFS_I(inode)->i_ext_bh = शून्य;
	AFFS_I(inode)->mmu_निजी = 0;
	AFFS_I(inode)->i_protect = 0;
	AFFS_I(inode)->i_lastalloc = 0;
	AFFS_I(inode)->i_pa_cnt = 0;
	AFFS_I(inode)->i_extcnt = 1;
	AFFS_I(inode)->i_ext_last = ~1;

	insert_inode_hash(inode);

	वापस inode;

err_bh:
	affs_मुक्त_block(sb, block);
err_block:
	iput(inode);
err_inode:
	वापस शून्य;
पूर्ण

/*
 * Add an entry to a directory. Create the header block
 * and insert it पूर्णांकo the hash table.
 */

पूर्णांक
affs_add_entry(काष्ठा inode *dir, काष्ठा inode *inode, काष्ठा dentry *dentry, s32 type)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा buffer_head *inode_bh = शून्य;
	काष्ठा buffer_head *bh;
	u32 block = 0;
	पूर्णांक retval;

	pr_debug("%s(dir=%lu, inode=%lu, \"%pd\", type=%d)\n", __func__,
		 dir->i_ino, inode->i_ino, dentry, type);

	retval = -EIO;
	bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh)
		जाओ करोne;

	affs_lock_link(inode);
	चयन (type) अणु
	हाल ST_LINKखाता:
	हाल ST_LINKसूची:
		retval = -ENOSPC;
		block = affs_alloc_block(dir, dir->i_ino);
		अगर (!block)
			जाओ err;
		retval = -EIO;
		inode_bh = bh;
		bh = affs_getzeroblk(sb, block);
		अगर (!bh)
			जाओ err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	AFFS_HEAD(bh)->ptype = cpu_to_be32(T_SHORT);
	AFFS_HEAD(bh)->key = cpu_to_be32(bh->b_blocknr);
	affs_copy_name(AFFS_TAIL(sb, bh)->name, dentry);
	AFFS_TAIL(sb, bh)->stype = cpu_to_be32(type);
	AFFS_TAIL(sb, bh)->parent = cpu_to_be32(dir->i_ino);

	अगर (inode_bh) अणु
		__be32 chain;
	       	chain = AFFS_TAIL(sb, inode_bh)->link_chain;
		AFFS_TAIL(sb, bh)->original = cpu_to_be32(inode->i_ino);
		AFFS_TAIL(sb, bh)->link_chain = chain;
		AFFS_TAIL(sb, inode_bh)->link_chain = cpu_to_be32(block);
		affs_adjust_checksum(inode_bh, block - be32_to_cpu(chain));
		mark_buffer_dirty_inode(inode_bh, inode);
		set_nlink(inode, 2);
		ihold(inode);
	पूर्ण
	affs_fix_checksum(sb, bh);
	mark_buffer_dirty_inode(bh, inode);
	dentry->d_fsdata = (व्योम *)(दीर्घ)bh->b_blocknr;

	affs_lock_dir(dir);
	retval = affs_insert_hash(dir, bh);
	mark_buffer_dirty_inode(bh, inode);
	affs_unlock_dir(dir);
	affs_unlock_link(inode);

	d_instantiate(dentry, inode);
करोne:
	affs_brअन्यथा(inode_bh);
	affs_brअन्यथा(bh);
	वापस retval;
err:
	अगर (block)
		affs_मुक्त_block(sb, block);
	affs_unlock_link(inode);
	जाओ करोne;
पूर्ण
