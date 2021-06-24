<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/namei.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Modअगरied क्रम Amiga FFS fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 */

#समावेश "affs.h"
#समावेश <linux/exportfs.h>

प्रकार पूर्णांक (*बड़े_t)(पूर्णांक);

/* Simple बड़े() क्रम DOS\1 */

अटल पूर्णांक
affs_बड़े(पूर्णांक ch)
अणु
	वापस ch >= 'a' && ch <= 'z' ? ch -= ('a' - 'A') : ch;
पूर्ण

/* International बड़े() क्रम DOS\3 ("international") */

अटल पूर्णांक
affs_पूर्णांकl_बड़े(पूर्णांक ch)
अणु
	वापस (ch >= 'a' && ch <= 'z') || (ch >= 0xE0
		&& ch <= 0xFE && ch != 0xF7) ?
		ch - ('a' - 'A') : ch;
पूर्ण

अटल अंतरभूत बड़े_t
affs_get_बड़े(काष्ठा super_block *sb)
अणु
	वापस affs_test_opt(AFFS_SB(sb)->s_flags, SF_INTL) ?
	       affs_पूर्णांकl_बड़े : affs_बड़े;
पूर्ण

/*
 * Note: the dentry argument is the parent dentry.
 */
अटल अंतरभूत पूर्णांक
__affs_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr, बड़े_t बड़े, bool notruncate)
अणु
	स्थिर u8 *name = qstr->name;
	अचिन्हित दीर्घ hash;
	पूर्णांक retval;
	u32 len;

	retval = affs_check_name(qstr->name, qstr->len, notruncate);
	अगर (retval)
		वापस retval;

	hash = init_name_hash(dentry);
	len = min(qstr->len, AFFSNAMEMAX);
	क्रम (; len > 0; name++, len--)
		hash = partial_name_hash(बड़े(*name), hash);
	qstr->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

अटल पूर्णांक
affs_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	वापस __affs_hash_dentry(dentry, qstr, affs_बड़े,
				  affs_nofilenametruncate(dentry));

पूर्ण

अटल पूर्णांक
affs_पूर्णांकl_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	वापस __affs_hash_dentry(dentry, qstr, affs_पूर्णांकl_बड़े,
				  affs_nofilenametruncate(dentry));

पूर्ण

अटल अंतरभूत पूर्णांक __affs_compare_dentry(अचिन्हित पूर्णांक len,
		स्थिर अक्षर *str, स्थिर काष्ठा qstr *name, बड़े_t बड़े,
		bool notruncate)
अणु
	स्थिर u8 *aname = str;
	स्थिर u8 *bname = name->name;

	/*
	 * 'str' is the name of an alपढ़ोy existing dentry, so the name
	 * must be valid. 'name' must be validated first.
	 */

	अगर (affs_check_name(name->name, name->len, notruncate))
		वापस 1;

	/*
	 * If the names are दीर्घer than the allowed 30 अक्षरs,
	 * the excess is ignored, so their length may dअगरfer.
	 */
	अगर (len >= AFFSNAMEMAX) अणु
		अगर (name->len < AFFSNAMEMAX)
			वापस 1;
		len = AFFSNAMEMAX;
	पूर्ण अन्यथा अगर (len != name->len)
		वापस 1;

	क्रम (; len > 0; len--)
		अगर (बड़े(*aname++) != बड़े(*bname++))
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
affs_compare_dentry(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु

	वापस __affs_compare_dentry(len, str, name, affs_बड़े,
				     affs_nofilenametruncate(dentry));
पूर्ण

अटल पूर्णांक
affs_पूर्णांकl_compare_dentry(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	वापस __affs_compare_dentry(len, str, name, affs_पूर्णांकl_बड़े,
				     affs_nofilenametruncate(dentry));

पूर्ण

/*
 * NOTE! unlike म_भेदन, affs_match वापसs 1 क्रम success, 0 क्रम failure.
 */

अटल अंतरभूत पूर्णांक
affs_match(काष्ठा dentry *dentry, स्थिर u8 *name2, बड़े_t बड़े)
अणु
	स्थिर u8 *name = dentry->d_name.name;
	पूर्णांक len = dentry->d_name.len;

	अगर (len >= AFFSNAMEMAX) अणु
		अगर (*name2 < AFFSNAMEMAX)
			वापस 0;
		len = AFFSNAMEMAX;
	पूर्ण अन्यथा अगर (len != *name2)
		वापस 0;

	क्रम (name2++; len > 0; len--)
		अगर (बड़े(*name++) != बड़े(*name2++))
			वापस 0;
	वापस 1;
पूर्ण

पूर्णांक
affs_hash_name(काष्ठा super_block *sb, स्थिर u8 *name, अचिन्हित पूर्णांक len)
अणु
	बड़े_t बड़े = affs_get_बड़े(sb);
	u32 hash;

	hash = len = min(len, AFFSNAMEMAX);
	क्रम (; len > 0; len--)
		hash = (hash * 13 + बड़े(*name++)) & 0x7ff;

	वापस hash % AFFS_SB(sb)->s_hashsize;
पूर्ण

अटल काष्ठा buffer_head *
affs_find_entry(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा buffer_head *bh;
	बड़े_t बड़े = affs_get_बड़े(sb);
	u32 key;

	pr_debug("%s(\"%pd\")\n", __func__, dentry);

	bh = affs_bपढ़ो(sb, dir->i_ino);
	अगर (!bh)
		वापस ERR_PTR(-EIO);

	key = be32_to_cpu(AFFS_HEAD(bh)->table[affs_hash_name(sb, dentry->d_name.name, dentry->d_name.len)]);

	क्रम (;;) अणु
		affs_brअन्यथा(bh);
		अगर (key == 0)
			वापस शून्य;
		bh = affs_bपढ़ो(sb, key);
		अगर (!bh)
			वापस ERR_PTR(-EIO);
		अगर (affs_match(dentry, AFFS_TAIL(sb, bh)->name, बड़े))
			वापस bh;
		key = be32_to_cpu(AFFS_TAIL(sb, bh)->hash_chain);
	पूर्ण
पूर्ण

काष्ठा dentry *
affs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा buffer_head *bh;
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *res;

	pr_debug("%s(\"%pd\")\n", __func__, dentry);

	affs_lock_dir(dir);
	bh = affs_find_entry(dir, dentry);
	अगर (IS_ERR(bh)) अणु
		affs_unlock_dir(dir);
		वापस ERR_CAST(bh);
	पूर्ण
	अगर (bh) अणु
		u32 ino = bh->b_blocknr;

		/* store the real header ino in d_fsdata क्रम faster lookups */
		dentry->d_fsdata = (व्योम *)(दीर्घ)ino;
		चयन (be32_to_cpu(AFFS_TAIL(sb, bh)->stype)) अणु
		//link to dirs disabled
		//हाल ST_LINKसूची:
		हाल ST_LINKखाता:
			ino = be32_to_cpu(AFFS_TAIL(sb, bh)->original);
		पूर्ण
		affs_brअन्यथा(bh);
		inode = affs_iget(sb, ino);
	पूर्ण
	res = d_splice_alias(inode, dentry);
	अगर (!IS_ERR_OR_शून्य(res))
		res->d_fsdata = dentry->d_fsdata;
	affs_unlock_dir(dir);
	वापस res;
पूर्ण

पूर्णांक
affs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	pr_debug("%s(dir=%lu, %lu \"%pd\")\n", __func__, dir->i_ino,
		 d_inode(dentry)->i_ino, dentry);

	वापस affs_हटाओ_header(dentry);
पूर्ण

पूर्णांक
affs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	    काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode	*inode;
	पूर्णांक		 error;

	pr_debug("%s(%lu,\"%pd\",0%ho)\n",
		 __func__, dir->i_ino, dentry, mode);

	inode = affs_new_inode(dir);
	अगर (!inode)
		वापस -ENOSPC;

	inode->i_mode = mode;
	affs_mode_to_prot(inode);
	mark_inode_dirty(inode);

	inode->i_op = &affs_file_inode_operations;
	inode->i_fop = &affs_file_operations;
	inode->i_mapping->a_ops = affs_test_opt(AFFS_SB(sb)->s_flags, SF_OFS) ?
				  &affs_aops_ofs : &affs_aops;
	error = affs_add_entry(dir, inode, dentry, ST_खाता);
	अगर (error) अणु
		clear_nlink(inode);
		iput(inode);
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
affs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	   काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode		*inode;
	पूर्णांक			 error;

	pr_debug("%s(%lu,\"%pd\",0%ho)\n",
		 __func__, dir->i_ino, dentry, mode);

	inode = affs_new_inode(dir);
	अगर (!inode)
		वापस -ENOSPC;

	inode->i_mode = S_IFसूची | mode;
	affs_mode_to_prot(inode);

	inode->i_op = &affs_dir_inode_operations;
	inode->i_fop = &affs_dir_operations;

	error = affs_add_entry(dir, inode, dentry, ST_USERसूची);
	अगर (error) अणु
		clear_nlink(inode);
		mark_inode_dirty(inode);
		iput(inode);
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
affs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	pr_debug("%s(dir=%lu, %lu \"%pd\")\n", __func__, dir->i_ino,
		 d_inode(dentry)->i_ino, dentry);

	वापस affs_हटाओ_header(dentry);
पूर्ण

पूर्णांक
affs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	     काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा super_block	*sb = dir->i_sb;
	काष्ठा buffer_head	*bh;
	काष्ठा inode		*inode;
	अक्षर			*p;
	पूर्णांक			 i, maxlen, error;
	अक्षर			 c, lc;

	pr_debug("%s(%lu,\"%pd\" -> \"%s\")\n",
		 __func__, dir->i_ino, dentry, symname);

	maxlen = AFFS_SB(sb)->s_hashsize * माप(u32) - 1;
	inode  = affs_new_inode(dir);
	अगर (!inode)
		वापस -ENOSPC;

	inode->i_op = &affs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_data.a_ops = &affs_symlink_aops;
	inode->i_mode = S_IFLNK | 0777;
	affs_mode_to_prot(inode);

	error = -EIO;
	bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh)
		जाओ err;
	i  = 0;
	p  = (अक्षर *)AFFS_HEAD(bh)->table;
	lc = '/';
	अगर (*symname == '/') अणु
		काष्ठा affs_sb_info *sbi = AFFS_SB(sb);
		जबतक (*symname == '/')
			symname++;
		spin_lock(&sbi->symlink_lock);
		जबतक (sbi->s_volume[i])	/* Cannot overflow */
			*p++ = sbi->s_volume[i++];
		spin_unlock(&sbi->symlink_lock);
	पूर्ण
	जबतक (i < maxlen && (c = *symname++)) अणु
		अगर (c == '.' && lc == '/' && *symname == '.' && symname[1] == '/') अणु
			*p++ = '/';
			i++;
			symname += 2;
			lc = '/';
		पूर्ण अन्यथा अगर (c == '.' && lc == '/' && *symname == '/') अणु
			symname++;
			lc = '/';
		पूर्ण अन्यथा अणु
			*p++ = c;
			lc   = c;
			i++;
		पूर्ण
		अगर (lc == '/')
			जबतक (*symname == '/')
				symname++;
	पूर्ण
	*p = 0;
	inode->i_size = i + 1;
	mark_buffer_dirty_inode(bh, inode);
	affs_brअन्यथा(bh);
	mark_inode_dirty(inode);

	error = affs_add_entry(dir, inode, dentry, ST_SOFTLINK);
	अगर (error)
		जाओ err;

	वापस 0;

err:
	clear_nlink(inode);
	mark_inode_dirty(inode);
	iput(inode);
	वापस error;
पूर्ण

पूर्णांक
affs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);

	pr_debug("%s(%lu, %lu, \"%pd\")\n", __func__, inode->i_ino, dir->i_ino,
		 dentry);

	वापस affs_add_entry(dir, inode, dentry, ST_LINKखाता);
पूर्ण

अटल पूर्णांक
affs_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
	    काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
अणु
	काष्ठा super_block *sb = old_dir->i_sb;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक retval;

	retval = affs_check_name(new_dentry->d_name.name,
				 new_dentry->d_name.len,
				 affs_nofilenametruncate(old_dentry));

	अगर (retval)
		वापस retval;

	/* Unlink destination अगर it alपढ़ोy exists */
	अगर (d_really_is_positive(new_dentry)) अणु
		retval = affs_हटाओ_header(new_dentry);
		अगर (retval)
			वापस retval;
	पूर्ण

	bh = affs_bपढ़ो(sb, d_inode(old_dentry)->i_ino);
	अगर (!bh)
		वापस -EIO;

	/* Remove header from its parent directory. */
	affs_lock_dir(old_dir);
	retval = affs_हटाओ_hash(old_dir, bh);
	affs_unlock_dir(old_dir);
	अगर (retval)
		जाओ करोne;

	/* And insert it पूर्णांकo the new directory with the new name. */
	affs_copy_name(AFFS_TAIL(sb, bh)->name, new_dentry);
	affs_fix_checksum(sb, bh);
	affs_lock_dir(new_dir);
	retval = affs_insert_hash(new_dir, bh);
	affs_unlock_dir(new_dir);
	/* TODO: move it back to old_dir, अगर error? */

करोne:
	mark_buffer_dirty_inode(bh, retval ? old_dir : new_dir);
	affs_brअन्यथा(bh);
	वापस retval;
पूर्ण

अटल पूर्णांक
affs_xनाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
	     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
अणु

	काष्ठा super_block *sb = old_dir->i_sb;
	काष्ठा buffer_head *bh_old = शून्य;
	काष्ठा buffer_head *bh_new = शून्य;
	पूर्णांक retval;

	bh_old = affs_bपढ़ो(sb, d_inode(old_dentry)->i_ino);
	अगर (!bh_old)
		वापस -EIO;

	bh_new = affs_bपढ़ो(sb, d_inode(new_dentry)->i_ino);
	अगर (!bh_new) अणु
		affs_brअन्यथा(bh_old);
		वापस -EIO;
	पूर्ण

	/* Remove old header from its parent directory. */
	affs_lock_dir(old_dir);
	retval = affs_हटाओ_hash(old_dir, bh_old);
	affs_unlock_dir(old_dir);
	अगर (retval)
		जाओ करोne;

	/* Remove new header from its parent directory. */
	affs_lock_dir(new_dir);
	retval = affs_हटाओ_hash(new_dir, bh_new);
	affs_unlock_dir(new_dir);
	अगर (retval)
		जाओ करोne;

	/* Insert old पूर्णांकo the new directory with the new name. */
	affs_copy_name(AFFS_TAIL(sb, bh_old)->name, new_dentry);
	affs_fix_checksum(sb, bh_old);
	affs_lock_dir(new_dir);
	retval = affs_insert_hash(new_dir, bh_old);
	affs_unlock_dir(new_dir);

	/* Insert new पूर्णांकo the old directory with the old name. */
	affs_copy_name(AFFS_TAIL(sb, bh_new)->name, old_dentry);
	affs_fix_checksum(sb, bh_new);
	affs_lock_dir(old_dir);
	retval = affs_insert_hash(old_dir, bh_new);
	affs_unlock_dir(old_dir);
करोne:
	mark_buffer_dirty_inode(bh_old, new_dir);
	mark_buffer_dirty_inode(bh_new, old_dir);
	affs_brअन्यथा(bh_old);
	affs_brअन्यथा(bh_new);
	वापस retval;
पूर्ण

पूर्णांक affs_नाम2(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		 काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		 काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE))
		वापस -EINVAL;

	pr_debug("%s(old=%lu,\"%pd\" to new=%lu,\"%pd\")\n", __func__,
		 old_dir->i_ino, old_dentry, new_dir->i_ino, new_dentry);

	अगर (flags & RENAME_EXCHANGE)
		वापस affs_xनाम(old_dir, old_dentry, new_dir, new_dentry);

	वापस affs_नाम(old_dir, old_dentry, new_dir, new_dentry);
पूर्ण

अटल काष्ठा dentry *affs_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *parent;
	काष्ठा buffer_head *bh;

	bh = affs_bपढ़ो(child->d_sb, d_inode(child)->i_ino);
	अगर (!bh)
		वापस ERR_PTR(-EIO);

	parent = affs_iget(child->d_sb,
			   be32_to_cpu(AFFS_TAIL(child->d_sb, bh)->parent));
	brअन्यथा(bh);
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	वापस d_obtain_alias(parent);
पूर्ण

अटल काष्ठा inode *affs_nfs_get_inode(काष्ठा super_block *sb, u64 ino,
					u32 generation)
अणु
	काष्ठा inode *inode;

	अगर (!affs_validblock(sb, ino))
		वापस ERR_PTR(-ESTALE);

	inode = affs_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	वापस inode;
पूर्ण

अटल काष्ठा dentry *affs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    affs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *affs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    affs_nfs_get_inode);
पूर्ण

स्थिर काष्ठा export_operations affs_export_ops = अणु
	.fh_to_dentry = affs_fh_to_dentry,
	.fh_to_parent = affs_fh_to_parent,
	.get_parent = affs_get_parent,
पूर्ण;

स्थिर काष्ठा dentry_operations affs_dentry_operations = अणु
	.d_hash		= affs_hash_dentry,
	.d_compare	= affs_compare_dentry,
पूर्ण;

स्थिर काष्ठा dentry_operations affs_पूर्णांकl_dentry_operations = अणु
	.d_hash		= affs_पूर्णांकl_hash_dentry,
	.d_compare	= affs_पूर्णांकl_compare_dentry,
पूर्ण;
