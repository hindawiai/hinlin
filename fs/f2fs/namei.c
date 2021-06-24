<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/namei.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/quotaops.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश <trace/events/f2fs.h>

अटल काष्ठा inode *f2fs_new_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	nid_t ino;
	काष्ठा inode *inode;
	bool nid_मुक्त = false;
	bool encrypt = false;
	पूर्णांक xattr_size = 0;
	पूर्णांक err;

	inode = new_inode(dir->i_sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	f2fs_lock_op(sbi);
	अगर (!f2fs_alloc_nid(sbi, &ino)) अणु
		f2fs_unlock_op(sbi);
		err = -ENOSPC;
		जाओ fail;
	पूर्ण
	f2fs_unlock_op(sbi);

	nid_मुक्त = true;

	inode_init_owner(&init_user_ns, inode, dir, mode);

	inode->i_ino = ino;
	inode->i_blocks = 0;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	F2FS_I(inode)->i_crसमय = inode->i_mसमय;
	inode->i_generation = pअक्रमom_u32();

	अगर (S_ISसूची(inode->i_mode))
		F2FS_I(inode)->i_current_depth = 1;

	err = insert_inode_locked(inode);
	अगर (err) अणु
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (f2fs_sb_has_project_quota(sbi) &&
		(F2FS_I(dir)->i_flags & F2FS_PROJINHERIT_FL))
		F2FS_I(inode)->i_projid = F2FS_I(dir)->i_projid;
	अन्यथा
		F2FS_I(inode)->i_projid = make_kprojid(&init_user_ns,
							F2FS_DEF_PROJID);

	err = fscrypt_prepare_new_inode(dir, inode, &encrypt);
	अगर (err)
		जाओ fail_drop;

	err = dquot_initialize(inode);
	अगर (err)
		जाओ fail_drop;

	set_inode_flag(inode, FI_NEW_INODE);

	अगर (encrypt)
		f2fs_set_encrypted_inode(inode);

	अगर (f2fs_sb_has_extra_attr(sbi)) अणु
		set_inode_flag(inode, FI_EXTRA_ATTR);
		F2FS_I(inode)->i_extra_isize = F2FS_TOTAL_EXTRA_ATTR_SIZE;
	पूर्ण

	अगर (test_opt(sbi, INLINE_XATTR))
		set_inode_flag(inode, FI_INLINE_XATTR);

	अगर (test_opt(sbi, INLINE_DATA) && f2fs_may_अंतरभूत_data(inode))
		set_inode_flag(inode, FI_INLINE_DATA);
	अगर (f2fs_may_अंतरभूत_dentry(inode))
		set_inode_flag(inode, FI_INLINE_DENTRY);

	अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(sbi)) अणु
		f2fs_bug_on(sbi, !f2fs_has_extra_attr(inode));
		अगर (f2fs_has_अंतरभूत_xattr(inode))
			xattr_size = F2FS_OPTION(sbi).अंतरभूत_xattr_size;
		/* Otherwise, will be 0 */
	पूर्ण अन्यथा अगर (f2fs_has_अंतरभूत_xattr(inode) ||
				f2fs_has_अंतरभूत_dentry(inode)) अणु
		xattr_size = DEFAULT_INLINE_XATTR_ADDRS;
	पूर्ण
	F2FS_I(inode)->i_अंतरभूत_xattr_size = xattr_size;

	f2fs_init_extent_tree(inode, शून्य);

	stat_inc_अंतरभूत_xattr(inode);
	stat_inc_अंतरभूत_inode(inode);
	stat_inc_अंतरभूत_dir(inode);

	F2FS_I(inode)->i_flags =
		f2fs_mask_flags(mode, F2FS_I(dir)->i_flags & F2FS_FL_INHERITED);

	अगर (S_ISसूची(inode->i_mode))
		F2FS_I(inode)->i_flags |= F2FS_INDEX_FL;

	अगर (F2FS_I(inode)->i_flags & F2FS_PROJINHERIT_FL)
		set_inode_flag(inode, FI_PROJ_INHERIT);

	अगर (f2fs_sb_has_compression(sbi)) अणु
		/* Inherit the compression flag in directory */
		अगर ((F2FS_I(dir)->i_flags & F2FS_COMPR_FL) &&
					f2fs_may_compress(inode))
			set_compress_context(inode);
	पूर्ण

	f2fs_set_inode_flags(inode);

	trace_f2fs_new_inode(inode, 0);
	वापस inode;

fail:
	trace_f2fs_new_inode(inode, err);
	make_bad_inode(inode);
	अगर (nid_मुक्त)
		set_inode_flag(inode, FI_FREE_NID);
	iput(inode);
	वापस ERR_PTR(err);
fail_drop:
	trace_f2fs_new_inode(inode, err);
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	अगर (nid_मुक्त)
		set_inode_flag(inode, FI_FREE_NID);
	clear_nlink(inode);
	unlock_new_inode(inode);
	iput(inode);
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत पूर्णांक is_extension_exist(स्थिर अचिन्हित अक्षर *s, स्थिर अक्षर *sub)
अणु
	माप_प्रकार slen = म_माप(s);
	माप_प्रकार sublen = म_माप(sub);
	पूर्णांक i;

	अगर (sublen == 1 && *sub == '*')
		वापस 1;

	/*
	 * filename क्रमmat of mulसमयdia file should be defined as:
	 * "filename + '.' + extension + (optional: '.' + temp extension)".
	 */
	अगर (slen < sublen + 2)
		वापस 0;

	क्रम (i = 1; i < slen - sublen; i++) अणु
		अगर (s[i] != '.')
			जारी;
		अगर (!strnहालcmp(s + i + 1, sub, sublen))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set file's temperature क्रम hot/cold data separation
 */
अटल अंतरभूत व्योम set_file_temperature(काष्ठा f2fs_sb_info *sbi, काष्ठा inode *inode,
		स्थिर अचिन्हित अक्षर *name)
अणु
	__u8 (*extlist)[F2FS_EXTENSION_LEN] = sbi->raw_super->extension_list;
	पूर्णांक i, cold_count, hot_count;

	करोwn_पढ़ो(&sbi->sb_lock);

	cold_count = le32_to_cpu(sbi->raw_super->extension_count);
	hot_count = sbi->raw_super->hot_ext_count;

	क्रम (i = 0; i < cold_count + hot_count; i++) अणु
		अगर (is_extension_exist(name, extlist[i]))
			अवरोध;
	पूर्ण

	up_पढ़ो(&sbi->sb_lock);

	अगर (i == cold_count + hot_count)
		वापस;

	अगर (i < cold_count)
		file_set_cold(inode);
	अन्यथा
		file_set_hot(inode);
पूर्ण

पूर्णांक f2fs_update_extension_list(काष्ठा f2fs_sb_info *sbi, स्थिर अक्षर *name,
							bool hot, bool set)
अणु
	__u8 (*extlist)[F2FS_EXTENSION_LEN] = sbi->raw_super->extension_list;
	पूर्णांक cold_count = le32_to_cpu(sbi->raw_super->extension_count);
	पूर्णांक hot_count = sbi->raw_super->hot_ext_count;
	पूर्णांक total_count = cold_count + hot_count;
	पूर्णांक start, count;
	पूर्णांक i;

	अगर (set) अणु
		अगर (total_count == F2FS_MAX_EXTENSION)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!hot && !cold_count)
			वापस -EINVAL;
		अगर (hot && !hot_count)
			वापस -EINVAL;
	पूर्ण

	अगर (hot) अणु
		start = cold_count;
		count = total_count;
	पूर्ण अन्यथा अणु
		start = 0;
		count = cold_count;
	पूर्ण

	क्रम (i = start; i < count; i++) अणु
		अगर (म_भेद(name, extlist[i]))
			जारी;

		अगर (set)
			वापस -EINVAL;

		स_नकल(extlist[i], extlist[i + 1],
				F2FS_EXTENSION_LEN * (total_count - i - 1));
		स_रखो(extlist[total_count - 1], 0, F2FS_EXTENSION_LEN);
		अगर (hot)
			sbi->raw_super->hot_ext_count = hot_count - 1;
		अन्यथा
			sbi->raw_super->extension_count =
						cpu_to_le32(cold_count - 1);
		वापस 0;
	पूर्ण

	अगर (!set)
		वापस -EINVAL;

	अगर (hot) अणु
		स_नकल(extlist[count], name, म_माप(name));
		sbi->raw_super->hot_ext_count = hot_count + 1;
	पूर्ण अन्यथा अणु
		अक्षर buf[F2FS_MAX_EXTENSION][F2FS_EXTENSION_LEN];

		स_नकल(buf, &extlist[cold_count],
				F2FS_EXTENSION_LEN * hot_count);
		स_रखो(extlist[cold_count], 0, F2FS_EXTENSION_LEN);
		स_नकल(extlist[cold_count], name, म_माप(name));
		स_नकल(&extlist[cold_count + 1], buf,
				F2FS_EXTENSION_LEN * hot_count);
		sbi->raw_super->extension_count = cpu_to_le32(cold_count + 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम set_compress_inode(काष्ठा f2fs_sb_info *sbi, काष्ठा inode *inode,
						स्थिर अचिन्हित अक्षर *name)
अणु
	__u8 (*extlist)[F2FS_EXTENSION_LEN] = sbi->raw_super->extension_list;
	अचिन्हित अक्षर (*ext)[F2FS_EXTENSION_LEN];
	अचिन्हित पूर्णांक ext_cnt = F2FS_OPTION(sbi).compress_ext_cnt;
	पूर्णांक i, cold_count, hot_count;

	अगर (!f2fs_sb_has_compression(sbi) ||
			is_inode_flag_set(inode, FI_COMPRESSED_खाता) ||
			F2FS_I(inode)->i_flags & F2FS_NOCOMP_FL ||
			!f2fs_may_compress(inode))
		वापस;

	करोwn_पढ़ो(&sbi->sb_lock);

	cold_count = le32_to_cpu(sbi->raw_super->extension_count);
	hot_count = sbi->raw_super->hot_ext_count;

	क्रम (i = cold_count; i < cold_count + hot_count; i++) अणु
		अगर (is_extension_exist(name, extlist[i])) अणु
			up_पढ़ो(&sbi->sb_lock);
			वापस;
		पूर्ण
	पूर्ण

	up_पढ़ो(&sbi->sb_lock);

	ext = F2FS_OPTION(sbi).extensions;

	क्रम (i = 0; i < ext_cnt; i++) अणु
		अगर (!is_extension_exist(name, ext[i]))
			जारी;

		set_compress_context(inode);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक f2fs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode;
	nid_t ino = 0;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = f2fs_new_inode(dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (!test_opt(sbi, DISABLE_EXT_IDENTIFY))
		set_file_temperature(sbi, inode, dentry->d_name.name);

	set_compress_inode(sbi, inode, dentry->d_name.name);

	inode->i_op = &f2fs_file_inode_operations;
	inode->i_fop = &f2fs_file_operations;
	inode->i_mapping->a_ops = &f2fs_dblock_aops;
	ino = inode->i_ino;

	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	अगर (err)
		जाओ out;
	f2fs_unlock_op(sbi);

	f2fs_alloc_nid_करोne(sbi, ino);

	d_instantiate_new(dentry, inode);

	अगर (IS_सूचीSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_balance_fs(sbi, true);
	वापस 0;
out:
	f2fs_handle_failed_inode(inode);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	err = fscrypt_prepare_link(old_dentry, dir, dentry);
	अगर (err)
		वापस err;

	अगर (is_inode_flag_set(dir, FI_PROJ_INHERIT) &&
			(!projid_eq(F2FS_I(dir)->i_projid,
			F2FS_I(old_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	f2fs_balance_fs(sbi, true);

	inode->i_स_समय = current_समय(inode);
	ihold(inode);

	set_inode_flag(inode, FI_INC_LINK);
	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	अगर (err)
		जाओ out;
	f2fs_unlock_op(sbi);

	d_instantiate(dentry, inode);

	अगर (IS_सूचीSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);
	वापस 0;
out:
	clear_inode_flag(inode, FI_INC_LINK);
	iput(inode);
	f2fs_unlock_op(sbi);
	वापस err;
पूर्ण

काष्ठा dentry *f2fs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ ino = f2fs_inode_by_name(d_inode(child), &करोtकरोt_name, &page);

	अगर (!ino) अणु
		अगर (IS_ERR(page))
			वापस ERR_CAST(page);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	वापस d_obtain_alias(f2fs_iget(child->d_sb, ino));
पूर्ण

अटल पूर्णांक __recover_करोt_dentries(काष्ठा inode *dir, nid_t pino)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा qstr करोt = QSTR_INIT(".", 1);
	काष्ठा qstr करोtकरोt = QSTR_INIT("..", 2);
	काष्ठा f2fs_dir_entry *de;
	काष्ठा page *page;
	पूर्णांक err = 0;

	अगर (f2fs_पढ़ोonly(sbi->sb)) अणु
		f2fs_info(sbi, "skip recovering inline_dots inode (ino:%lu, pino:%u) in readonly mountpoint",
			  dir->i_ino, pino);
		वापस 0;
	पूर्ण

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);

	de = f2fs_find_entry(dir, &करोt, &page);
	अगर (de) अणु
		f2fs_put_page(page, 0);
	पूर्ण अन्यथा अगर (IS_ERR(page)) अणु
		err = PTR_ERR(page);
		जाओ out;
	पूर्ण अन्यथा अणु
		err = f2fs_करो_add_link(dir, &करोt, शून्य, dir->i_ino, S_IFसूची);
		अगर (err)
			जाओ out;
	पूर्ण

	de = f2fs_find_entry(dir, &करोtकरोt, &page);
	अगर (de)
		f2fs_put_page(page, 0);
	अन्यथा अगर (IS_ERR(page))
		err = PTR_ERR(page);
	अन्यथा
		err = f2fs_करो_add_link(dir, &करोtकरोt, शून्य, pino, S_IFसूची);
out:
	अगर (!err)
		clear_inode_flag(dir, FI_INLINE_DOTS);

	f2fs_unlock_op(sbi);
	वापस err;
पूर्ण

अटल काष्ठा dentry *f2fs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा f2fs_dir_entry *de;
	काष्ठा page *page;
	काष्ठा dentry *new;
	nid_t ino = -1;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक root_ino = F2FS_ROOT_INO(F2FS_I_SB(dir));
	काष्ठा f2fs_filename fname;

	trace_f2fs_lookup_start(dir, dentry, flags);

	अगर (dentry->d_name.len > F2FS_NAME_LEN) अणु
		err = -ENAMETOOLONG;
		जाओ out;
	पूर्ण

	err = f2fs_prepare_lookup(dir, dentry, &fname);
	generic_set_encrypted_ci_d_ops(dentry);
	अगर (err == -ENOENT)
		जाओ out_splice;
	अगर (err)
		जाओ out;
	de = __f2fs_find_entry(dir, &fname, &page);
	f2fs_मुक्त_filename(&fname);

	अगर (!de) अणु
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ out;
		पूर्ण
		err = -ENOENT;
		जाओ out_splice;
	पूर्ण

	ino = le32_to_cpu(de->ino);
	f2fs_put_page(page, 0);

	inode = f2fs_iget(dir->i_sb, ino);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	अगर ((dir->i_ino == root_ino) && f2fs_has_अंतरभूत_करोts(dir)) अणु
		err = __recover_करोt_dentries(dir, root_ino);
		अगर (err)
			जाओ out_iput;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_करोts(inode)) अणु
		err = __recover_करोt_dentries(inode, dir->i_ino);
		अगर (err)
			जाओ out_iput;
	पूर्ण
	अगर (IS_ENCRYPTED(dir) &&
	    (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
	    !fscrypt_has_permitted_context(dir, inode)) अणु
		f2fs_warn(F2FS_I_SB(inode), "Inconsistent encryption contexts: %lu/%lu",
			  dir->i_ino, inode->i_ino);
		err = -EPERM;
		जाओ out_iput;
	पूर्ण
out_splice:
#अगर_घोषित CONFIG_UNICODE
	अगर (!inode && IS_CASEFOLDED(dir)) अणु
		/* Eventually we want to call d_add_ci(dentry, शून्य)
		 * क्रम negative dentries in the encoding हाल as
		 * well.  For now, prevent the negative dentry
		 * from being cached.
		 */
		trace_f2fs_lookup_end(dir, dentry, ino, err);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर
	new = d_splice_alias(inode, dentry);
	err = PTR_ERR_OR_ZERO(new);
	trace_f2fs_lookup_end(dir, dentry, ino, !new ? -ENOENT : err);
	वापस new;
out_iput:
	iput(inode);
out:
	trace_f2fs_lookup_end(dir, dentry, ino, err);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक f2fs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा f2fs_dir_entry *de;
	काष्ठा page *page;
	पूर्णांक err;

	trace_f2fs_unlink_enter(dir, dentry);

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		err = -EIO;
		जाओ fail;
	पूर्ण

	err = dquot_initialize(dir);
	अगर (err)
		जाओ fail;
	err = dquot_initialize(inode);
	अगर (err)
		जाओ fail;

	de = f2fs_find_entry(dir, &dentry->d_name, &page);
	अगर (!de) अणु
		अगर (IS_ERR(page))
			err = PTR_ERR(page);
		जाओ fail;
	पूर्ण

	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);
	err = f2fs_acquire_orphan_inode(sbi);
	अगर (err) अणु
		f2fs_unlock_op(sbi);
		f2fs_put_page(page, 0);
		जाओ fail;
	पूर्ण
	f2fs_delete_entry(de, page, dir, inode);
#अगर_घोषित CONFIG_UNICODE
	/* VFS negative dentries are incompatible with Encoding and
	 * Case-insensitiveness. Eventually we'll want aव्योम
	 * invalidating the dentries here, aदीर्घside with वापसing the
	 * negative dentries at f2fs_lookup(), when it is better
	 * supported by the VFS क्रम the CI हाल.
	 */
	अगर (IS_CASEFOLDED(dir))
		d_invalidate(dentry);
#पूर्ण_अगर
	f2fs_unlock_op(sbi);

	अगर (IS_सूचीSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);
fail:
	trace_f2fs_unlink_निकास(inode, err);
	वापस err;
पूर्ण

अटल स्थिर अक्षर *f2fs_get_link(काष्ठा dentry *dentry,
				 काष्ठा inode *inode,
				 काष्ठा delayed_call *करोne)
अणु
	स्थिर अक्षर *link = page_get_link(dentry, inode, करोne);

	अगर (!IS_ERR(link) && !*link) अणु
		/* this is broken symlink हाल */
		करो_delayed_call(करोne);
		clear_delayed_call(करोne);
		link = ERR_PTR(-ENOENT);
	पूर्ण
	वापस link;
पूर्ण

अटल पूर्णांक f2fs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode;
	माप_प्रकार len = म_माप(symname);
	काष्ठा fscrypt_str disk_link;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	err = fscrypt_prepare_symlink(dir, symname, len, dir->i_sb->s_blocksize,
				      &disk_link);
	अगर (err)
		वापस err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = f2fs_new_inode(dir, S_IFLNK | S_IRWXUGO);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (IS_ENCRYPTED(inode))
		inode->i_op = &f2fs_encrypted_symlink_inode_operations;
	अन्यथा
		inode->i_op = &f2fs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &f2fs_dblock_aops;

	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	अगर (err)
		जाओ out_f2fs_handle_failed_inode;
	f2fs_unlock_op(sbi);
	f2fs_alloc_nid_करोne(sbi, inode->i_ino);

	err = fscrypt_encrypt_symlink(inode, symname, len, &disk_link);
	अगर (err)
		जाओ err_out;

	err = page_symlink(inode, disk_link.name, disk_link.len);

err_out:
	d_instantiate_new(dentry, inode);

	/*
	 * Let's flush symlink data in order to aव्योम broken symlink as much as
	 * possible. Nevertheless, fsyncing is the best way, but there is no
	 * way to get a file descriptor in order to flush that.
	 *
	 * Note that, it needs to करो dir->fsync to make this recoverable.
	 * If the symlink path is stored पूर्णांकo अंतरभूत_data, there is no
	 * perक्रमmance regression.
	 */
	अगर (!err) अणु
		filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0,
							disk_link.len - 1);

		अगर (IS_सूचीSYNC(dir))
			f2fs_sync_fs(sbi->sb, 1);
	पूर्ण अन्यथा अणु
		f2fs_unlink(dir, dentry);
	पूर्ण

	f2fs_balance_fs(sbi, true);
	जाओ out_मुक्त_encrypted_link;

out_f2fs_handle_failed_inode:
	f2fs_handle_failed_inode(inode);
out_मुक्त_encrypted_link:
	अगर (disk_link.name != (अचिन्हित अक्षर *)symname)
		kमुक्त(disk_link.name);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = f2fs_new_inode(dir, S_IFसूची | mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	inode->i_op = &f2fs_dir_inode_operations;
	inode->i_fop = &f2fs_dir_operations;
	inode->i_mapping->a_ops = &f2fs_dblock_aops;
	inode_nohighmem(inode);

	set_inode_flag(inode, FI_INC_LINK);
	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	अगर (err)
		जाओ out_fail;
	f2fs_unlock_op(sbi);

	f2fs_alloc_nid_करोne(sbi, inode->i_ino);

	d_instantiate_new(dentry, inode);

	अगर (IS_सूचीSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_balance_fs(sbi, true);
	वापस 0;

out_fail:
	clear_inode_flag(inode, FI_INC_LINK);
	f2fs_handle_failed_inode(inode);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (f2fs_empty_dir(inode))
		वापस f2fs_unlink(dir, dentry);
	वापस -ENOTEMPTY;
पूर्ण

अटल पूर्णांक f2fs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode;
	पूर्णांक err = 0;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = f2fs_new_inode(dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	init_special_inode(inode, inode->i_mode, rdev);
	inode->i_op = &f2fs_special_inode_operations;

	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	अगर (err)
		जाओ out;
	f2fs_unlock_op(sbi);

	f2fs_alloc_nid_करोne(sbi, inode->i_ino);

	d_instantiate_new(dentry, inode);

	अगर (IS_सूचीSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_balance_fs(sbi, true);
	वापस 0;
out:
	f2fs_handle_failed_inode(inode);
	वापस err;
पूर्ण

अटल पूर्णांक __f2fs_क्षणिक_ख(काष्ठा inode *dir, काष्ठा dentry *dentry,
					umode_t mode, काष्ठा inode **whiteout)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);
	काष्ठा inode *inode;
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = f2fs_new_inode(dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (whiteout) अणु
		init_special_inode(inode, inode->i_mode, WHITEOUT_DEV);
		inode->i_op = &f2fs_special_inode_operations;
	पूर्ण अन्यथा अणु
		inode->i_op = &f2fs_file_inode_operations;
		inode->i_fop = &f2fs_file_operations;
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
	पूर्ण

	f2fs_lock_op(sbi);
	err = f2fs_acquire_orphan_inode(sbi);
	अगर (err)
		जाओ out;

	err = f2fs_करो_क्षणिक_ख(inode, dir);
	अगर (err)
		जाओ release_out;

	/*
	 * add this non-linked क्षणिक_ख to orphan list, in this way we could
	 * हटाओ all unused data of क्षणिक_ख after abnormal घातer-off.
	 */
	f2fs_add_orphan_inode(inode);
	f2fs_alloc_nid_करोne(sbi, inode->i_ino);

	अगर (whiteout) अणु
		f2fs_i_links_ग_लिखो(inode, false);

		spin_lock(&inode->i_lock);
		inode->i_state |= I_LINKABLE;
		spin_unlock(&inode->i_lock);

		*whiteout = inode;
	पूर्ण अन्यथा अणु
		d_क्षणिक_ख(dentry, inode);
	पूर्ण
	/* link_count was changed by d_क्षणिक_ख as well. */
	f2fs_unlock_op(sbi);
	unlock_new_inode(inode);

	f2fs_balance_fs(sbi, true);
	वापस 0;

release_out:
	f2fs_release_orphan_inode(sbi);
out:
	f2fs_handle_failed_inode(inode);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	वापस __f2fs_क्षणिक_ख(dir, dentry, mode, शून्य);
पूर्ण

अटल पूर्णांक f2fs_create_whiteout(काष्ठा inode *dir, काष्ठा inode **whiteout)
अणु
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(dir))))
		वापस -EIO;

	वापस __f2fs_क्षणिक_ख(dir, शून्य, S_IFCHR | WHITEOUT_MODE, whiteout);
पूर्ण

अटल पूर्णांक f2fs_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(old_dir);
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा inode *whiteout = शून्य;
	काष्ठा page *old_dir_page = शून्य;
	काष्ठा page *old_page, *new_page = शून्य;
	काष्ठा f2fs_dir_entry *old_dir_entry = शून्य;
	काष्ठा f2fs_dir_entry *old_entry;
	काष्ठा f2fs_dir_entry *new_entry;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	अगर (is_inode_flag_set(new_dir, FI_PROJ_INHERIT) &&
			(!projid_eq(F2FS_I(new_dir)->i_projid,
			F2FS_I(old_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	/*
	 * If new_inode is null, the below renaming flow will
	 * add a link in old_dir which can conver अंतरभूत_dir.
	 * After then, अगर we failed to get the entry due to other
	 * reasons like ENOMEM, we had to हटाओ the new entry.
	 * Instead of adding such the error handling routine, let's
	 * simply convert first here.
	 */
	अगर (old_dir == new_dir && !new_inode) अणु
		err = f2fs_try_convert_अंतरभूत_dir(old_dir, new_dentry);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (flags & RENAME_WHITEOUT) अणु
		err = f2fs_create_whiteout(old_dir, &whiteout);
		अगर (err)
			वापस err;
	पूर्ण

	err = dquot_initialize(old_dir);
	अगर (err)
		जाओ out;

	err = dquot_initialize(new_dir);
	अगर (err)
		जाओ out;

	अगर (new_inode) अणु
		err = dquot_initialize(new_inode);
		अगर (err)
			जाओ out;
	पूर्ण

	err = -ENOENT;
	old_entry = f2fs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	अगर (!old_entry) अणु
		अगर (IS_ERR(old_page))
			err = PTR_ERR(old_page);
		जाओ out;
	पूर्ण

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		old_dir_entry = f2fs_parent_dir(old_inode, &old_dir_page);
		अगर (!old_dir_entry) अणु
			अगर (IS_ERR(old_dir_page))
				err = PTR_ERR(old_dir_page);
			जाओ out_old;
		पूर्ण
	पूर्ण

	अगर (new_inode) अणु

		err = -ENOTEMPTY;
		अगर (old_dir_entry && !f2fs_empty_dir(new_inode))
			जाओ out_dir;

		err = -ENOENT;
		new_entry = f2fs_find_entry(new_dir, &new_dentry->d_name,
						&new_page);
		अगर (!new_entry) अणु
			अगर (IS_ERR(new_page))
				err = PTR_ERR(new_page);
			जाओ out_dir;
		पूर्ण

		f2fs_balance_fs(sbi, true);

		f2fs_lock_op(sbi);

		err = f2fs_acquire_orphan_inode(sbi);
		अगर (err)
			जाओ put_out_dir;

		f2fs_set_link(new_dir, new_entry, new_page, old_inode);
		new_page = शून्य;

		new_inode->i_स_समय = current_समय(new_inode);
		करोwn_ग_लिखो(&F2FS_I(new_inode)->i_sem);
		अगर (old_dir_entry)
			f2fs_i_links_ग_लिखो(new_inode, false);
		f2fs_i_links_ग_लिखो(new_inode, false);
		up_ग_लिखो(&F2FS_I(new_inode)->i_sem);

		अगर (!new_inode->i_nlink)
			f2fs_add_orphan_inode(new_inode);
		अन्यथा
			f2fs_release_orphan_inode(sbi);
	पूर्ण अन्यथा अणु
		f2fs_balance_fs(sbi, true);

		f2fs_lock_op(sbi);

		err = f2fs_add_link(new_dentry, old_inode);
		अगर (err) अणु
			f2fs_unlock_op(sbi);
			जाओ out_dir;
		पूर्ण

		अगर (old_dir_entry)
			f2fs_i_links_ग_लिखो(new_dir, true);
	पूर्ण

	करोwn_ग_लिखो(&F2FS_I(old_inode)->i_sem);
	अगर (!old_dir_entry || whiteout)
		file_lost_pino(old_inode);
	अन्यथा
		/* adjust dir's i_pino to pass fsck check */
		f2fs_i_pino_ग_लिखो(old_inode, new_dir->i_ino);
	up_ग_लिखो(&F2FS_I(old_inode)->i_sem);

	old_inode->i_स_समय = current_समय(old_inode);
	f2fs_mark_inode_dirty_sync(old_inode, false);

	f2fs_delete_entry(old_entry, old_page, old_dir, शून्य);
	old_page = शून्य;

	अगर (whiteout) अणु
		set_inode_flag(whiteout, FI_INC_LINK);
		err = f2fs_add_link(old_dentry, whiteout);
		अगर (err)
			जाओ put_out_dir;

		spin_lock(&whiteout->i_lock);
		whiteout->i_state &= ~I_LINKABLE;
		spin_unlock(&whiteout->i_lock);

		iput(whiteout);
	पूर्ण

	अगर (old_dir_entry) अणु
		अगर (old_dir != new_dir && !whiteout)
			f2fs_set_link(old_inode, old_dir_entry,
						old_dir_page, new_dir);
		अन्यथा
			f2fs_put_page(old_dir_page, 0);
		f2fs_i_links_ग_लिखो(old_dir, false);
	पूर्ण
	अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT) अणु
		f2fs_add_ino_entry(sbi, new_dir->i_ino, TRANS_सूची_INO);
		अगर (S_ISसूची(old_inode->i_mode))
			f2fs_add_ino_entry(sbi, old_inode->i_ino,
							TRANS_सूची_INO);
	पूर्ण

	f2fs_unlock_op(sbi);

	अगर (IS_सूचीSYNC(old_dir) || IS_सूचीSYNC(new_dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_update_समय(sbi, REQ_TIME);
	वापस 0;

put_out_dir:
	f2fs_unlock_op(sbi);
	f2fs_put_page(new_page, 0);
out_dir:
	अगर (old_dir_entry)
		f2fs_put_page(old_dir_page, 0);
out_old:
	f2fs_put_page(old_page, 0);
out:
	अगर (whiteout)
		iput(whiteout);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_cross_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(old_dir);
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा page *old_dir_page, *new_dir_page;
	काष्ठा page *old_page, *new_page;
	काष्ठा f2fs_dir_entry *old_dir_entry = शून्य, *new_dir_entry = शून्य;
	काष्ठा f2fs_dir_entry *old_entry, *new_entry;
	पूर्णांक old_nlink = 0, new_nlink = 0;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(sbi)))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	अगर ((is_inode_flag_set(new_dir, FI_PROJ_INHERIT) &&
			!projid_eq(F2FS_I(new_dir)->i_projid,
			F2FS_I(old_dentry->d_inode)->i_projid)) ||
	    (is_inode_flag_set(new_dir, FI_PROJ_INHERIT) &&
			!projid_eq(F2FS_I(old_dir)->i_projid,
			F2FS_I(new_dentry->d_inode)->i_projid)))
		वापस -EXDEV;

	err = dquot_initialize(old_dir);
	अगर (err)
		जाओ out;

	err = dquot_initialize(new_dir);
	अगर (err)
		जाओ out;

	err = -ENOENT;
	old_entry = f2fs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	अगर (!old_entry) अणु
		अगर (IS_ERR(old_page))
			err = PTR_ERR(old_page);
		जाओ out;
	पूर्ण

	new_entry = f2fs_find_entry(new_dir, &new_dentry->d_name, &new_page);
	अगर (!new_entry) अणु
		अगर (IS_ERR(new_page))
			err = PTR_ERR(new_page);
		जाओ out_old;
	पूर्ण

	/* prepare क्रम updating ".." directory entry info later */
	अगर (old_dir != new_dir) अणु
		अगर (S_ISसूची(old_inode->i_mode)) अणु
			old_dir_entry = f2fs_parent_dir(old_inode,
							&old_dir_page);
			अगर (!old_dir_entry) अणु
				अगर (IS_ERR(old_dir_page))
					err = PTR_ERR(old_dir_page);
				जाओ out_new;
			पूर्ण
		पूर्ण

		अगर (S_ISसूची(new_inode->i_mode)) अणु
			new_dir_entry = f2fs_parent_dir(new_inode,
							&new_dir_page);
			अगर (!new_dir_entry) अणु
				अगर (IS_ERR(new_dir_page))
					err = PTR_ERR(new_dir_page);
				जाओ out_old_dir;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If cross नाम between file and directory those are not
	 * in the same directory, we will inc nlink of file's parent
	 * later, so we should check upper boundary of its nlink.
	 */
	अगर ((!old_dir_entry || !new_dir_entry) &&
				old_dir_entry != new_dir_entry) अणु
		old_nlink = old_dir_entry ? -1 : 1;
		new_nlink = -old_nlink;
		err = -EMLINK;
		अगर ((old_nlink > 0 && old_dir->i_nlink >= F2FS_LINK_MAX) ||
			(new_nlink > 0 && new_dir->i_nlink >= F2FS_LINK_MAX))
			जाओ out_new_dir;
	पूर्ण

	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);

	/* update ".." directory entry info of old dentry */
	अगर (old_dir_entry)
		f2fs_set_link(old_inode, old_dir_entry, old_dir_page, new_dir);

	/* update ".." directory entry info of new dentry */
	अगर (new_dir_entry)
		f2fs_set_link(new_inode, new_dir_entry, new_dir_page, old_dir);

	/* update directory entry info of old dir inode */
	f2fs_set_link(old_dir, old_entry, old_page, new_inode);

	करोwn_ग_लिखो(&F2FS_I(old_inode)->i_sem);
	अगर (!old_dir_entry)
		file_lost_pino(old_inode);
	अन्यथा
		/* adjust dir's i_pino to pass fsck check */
		f2fs_i_pino_ग_लिखो(old_inode, new_dir->i_ino);
	up_ग_लिखो(&F2FS_I(old_inode)->i_sem);

	old_dir->i_स_समय = current_समय(old_dir);
	अगर (old_nlink) अणु
		करोwn_ग_लिखो(&F2FS_I(old_dir)->i_sem);
		f2fs_i_links_ग_लिखो(old_dir, old_nlink > 0);
		up_ग_लिखो(&F2FS_I(old_dir)->i_sem);
	पूर्ण
	f2fs_mark_inode_dirty_sync(old_dir, false);

	/* update directory entry info of new dir inode */
	f2fs_set_link(new_dir, new_entry, new_page, old_inode);

	करोwn_ग_लिखो(&F2FS_I(new_inode)->i_sem);
	अगर (!new_dir_entry)
		file_lost_pino(new_inode);
	अन्यथा
		/* adjust dir's i_pino to pass fsck check */
		f2fs_i_pino_ग_लिखो(new_inode, old_dir->i_ino);
	up_ग_लिखो(&F2FS_I(new_inode)->i_sem);

	new_dir->i_स_समय = current_समय(new_dir);
	अगर (new_nlink) अणु
		करोwn_ग_लिखो(&F2FS_I(new_dir)->i_sem);
		f2fs_i_links_ग_लिखो(new_dir, new_nlink > 0);
		up_ग_लिखो(&F2FS_I(new_dir)->i_sem);
	पूर्ण
	f2fs_mark_inode_dirty_sync(new_dir, false);

	अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT) अणु
		f2fs_add_ino_entry(sbi, old_dir->i_ino, TRANS_सूची_INO);
		f2fs_add_ino_entry(sbi, new_dir->i_ino, TRANS_सूची_INO);
	पूर्ण

	f2fs_unlock_op(sbi);

	अगर (IS_सूचीSYNC(old_dir) || IS_सूचीSYNC(new_dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_update_समय(sbi, REQ_TIME);
	वापस 0;
out_new_dir:
	अगर (new_dir_entry) अणु
		f2fs_put_page(new_dir_page, 0);
	पूर्ण
out_old_dir:
	अगर (old_dir_entry) अणु
		f2fs_put_page(old_dir_page, 0);
	पूर्ण
out_new:
	f2fs_put_page(new_page, 0);
out_old:
	f2fs_put_page(old_page, 0);
out:
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_नाम2(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	err = fscrypt_prepare_नाम(old_dir, old_dentry, new_dir, new_dentry,
				     flags);
	अगर (err)
		वापस err;

	अगर (flags & RENAME_EXCHANGE) अणु
		वापस f2fs_cross_नाम(old_dir, old_dentry,
					 new_dir, new_dentry);
	पूर्ण
	/*
	 * VFS has alपढ़ोy handled the new dentry existence हाल,
	 * here, we just deal with "RENAME_NOREPLACE" as regular नाम.
	 */
	वापस f2fs_नाम(old_dir, old_dentry, new_dir, new_dentry, flags);
पूर्ण

अटल स्थिर अक्षर *f2fs_encrypted_get_link(काष्ठा dentry *dentry,
					   काष्ठा inode *inode,
					   काष्ठा delayed_call *करोne)
अणु
	काष्ठा page *page;
	स्थिर अक्षर *target;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	page = पढ़ो_mapping_page(inode->i_mapping, 0, शून्य);
	अगर (IS_ERR(page))
		वापस ERR_CAST(page);

	target = fscrypt_get_symlink(inode, page_address(page),
				     inode->i_sb->s_blocksize, करोne);
	put_page(page);
	वापस target;
पूर्ण

स्थिर काष्ठा inode_operations f2fs_encrypted_symlink_inode_operations = अणु
	.get_link	= f2fs_encrypted_get_link,
	.getattr	= f2fs_getattr,
	.setattr	= f2fs_setattr,
	.listxattr	= f2fs_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations f2fs_dir_inode_operations = अणु
	.create		= f2fs_create,
	.lookup		= f2fs_lookup,
	.link		= f2fs_link,
	.unlink		= f2fs_unlink,
	.symlink	= f2fs_symlink,
	.सूची_गढ़ो		= f2fs_सूची_गढ़ो,
	.सूची_हटाओ		= f2fs_सूची_हटाओ,
	.mknod		= f2fs_mknod,
	.नाम		= f2fs_नाम2,
	.क्षणिक_ख	= f2fs_क्षणिक_ख,
	.getattr	= f2fs_getattr,
	.setattr	= f2fs_setattr,
	.get_acl	= f2fs_get_acl,
	.set_acl	= f2fs_set_acl,
	.listxattr	= f2fs_listxattr,
	.fiemap		= f2fs_fiemap,
	.fileattr_get	= f2fs_fileattr_get,
	.fileattr_set	= f2fs_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations f2fs_symlink_inode_operations = अणु
	.get_link	= f2fs_get_link,
	.getattr	= f2fs_getattr,
	.setattr	= f2fs_setattr,
	.listxattr	= f2fs_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations f2fs_special_inode_operations = अणु
	.getattr	= f2fs_getattr,
	.setattr	= f2fs_setattr,
	.get_acl	= f2fs_get_acl,
	.set_acl	= f2fs_set_acl,
	.listxattr	= f2fs_listxattr,
पूर्ण;
