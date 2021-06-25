<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Novell Inc.
 * Copyright (C) 2016 Red Hat, Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/xattr.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/uuid.h>
#समावेश <linux/namei.h>
#समावेश <linux/ratelimit.h>
#समावेश "overlayfs.h"

पूर्णांक ovl_want_ग_लिखो(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;
	वापस mnt_want_ग_लिखो(ovl_upper_mnt(ofs));
पूर्ण

व्योम ovl_drop_ग_लिखो(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;
	mnt_drop_ग_लिखो(ovl_upper_mnt(ofs));
पूर्ण

काष्ठा dentry *ovl_workdir(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;
	वापस ofs->workdir;
पूर्ण

स्थिर काष्ठा cred *ovl_override_creds(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	वापस override_creds(ofs->creator_cred);
पूर्ण

/*
 * Check अगर underlying fs supports file handles and try to determine encoding
 * type, in order to deduce maximum inode number used by fs.
 *
 * Return 0 अगर file handles are not supported.
 * Return 1 (खाताID_INO32_GEN) अगर fs uses the शेष 32bit inode encoding.
 * Return -1 अगर fs uses a non शेष encoding with unknown inode size.
 */
पूर्णांक ovl_can_decode_fh(काष्ठा super_block *sb)
अणु
	अगर (!capable(CAP_DAC_READ_SEARCH))
		वापस 0;

	अगर (!sb->s_export_op || !sb->s_export_op->fh_to_dentry)
		वापस 0;

	वापस sb->s_export_op->encode_fh ? -1 : खाताID_INO32_GEN;
पूर्ण

काष्ठा dentry *ovl_indexdir(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	वापस ofs->indexdir;
पूर्ण

/* Index all files on copy up. For now only enabled क्रम NFS export */
bool ovl_index_all(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	वापस ofs->config.nfs_export && ofs->config.index;
पूर्ण

/* Verअगरy lower origin on lookup. For now only enabled क्रम NFS export */
bool ovl_verअगरy_lower(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	वापस ofs->config.nfs_export && ofs->config.index;
पूर्ण

काष्ठा ovl_entry *ovl_alloc_entry(अचिन्हित पूर्णांक numlower)
अणु
	माप_प्रकार size = दुरत्व(काष्ठा ovl_entry, lowerstack[numlower]);
	काष्ठा ovl_entry *oe = kzalloc(size, GFP_KERNEL);

	अगर (oe)
		oe->numlower = numlower;

	वापस oe;
पूर्ण

bool ovl_dentry_remote(काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags &
		(DCACHE_OP_REVALIDATE | DCACHE_OP_WEAK_REVALIDATE);
पूर्ण

व्योम ovl_dentry_update_reval(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry,
			     अचिन्हित पूर्णांक mask)
अणु
	काष्ठा ovl_entry *oe = OVL_E(dentry);
	अचिन्हित पूर्णांक i, flags = 0;

	अगर (upperdentry)
		flags |= upperdentry->d_flags;
	क्रम (i = 0; i < oe->numlower; i++)
		flags |= oe->lowerstack[i].dentry->d_flags;

	spin_lock(&dentry->d_lock);
	dentry->d_flags &= ~mask;
	dentry->d_flags |= flags & mask;
	spin_unlock(&dentry->d_lock);
पूर्ण

bool ovl_dentry_weird(काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & (DCACHE_NEED_AUTOMOUNT |
				  DCACHE_MANAGE_TRANSIT |
				  DCACHE_OP_HASH |
				  DCACHE_OP_COMPARE);
पूर्ण

क्रमागत ovl_path_type ovl_path_type(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;
	क्रमागत ovl_path_type type = 0;

	अगर (ovl_dentry_upper(dentry)) अणु
		type = __OVL_PATH_UPPER;

		/*
		 * Non-dir dentry can hold lower dentry of its copy up origin.
		 */
		अगर (oe->numlower) अणु
			अगर (ovl_test_flag(OVL_CONST_INO, d_inode(dentry)))
				type |= __OVL_PATH_ORIGIN;
			अगर (d_is_dir(dentry) ||
			    !ovl_has_upperdata(d_inode(dentry)))
				type |= __OVL_PATH_MERGE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (oe->numlower > 1)
			type |= __OVL_PATH_MERGE;
	पूर्ण
	वापस type;
पूर्ण

व्योम ovl_path_upper(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;

	path->mnt = ovl_upper_mnt(ofs);
	path->dentry = ovl_dentry_upper(dentry);
पूर्ण

व्योम ovl_path_lower(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	अगर (oe->numlower) अणु
		path->mnt = oe->lowerstack[0].layer->mnt;
		path->dentry = oe->lowerstack[0].dentry;
	पूर्ण अन्यथा अणु
		*path = (काष्ठा path) अणु पूर्ण;
	पूर्ण
पूर्ण

व्योम ovl_path_lowerdata(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	अगर (oe->numlower) अणु
		path->mnt = oe->lowerstack[oe->numlower - 1].layer->mnt;
		path->dentry = oe->lowerstack[oe->numlower - 1].dentry;
	पूर्ण अन्यथा अणु
		*path = (काष्ठा path) अणु पूर्ण;
	पूर्ण
पूर्ण

क्रमागत ovl_path_type ovl_path_real(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	क्रमागत ovl_path_type type = ovl_path_type(dentry);

	अगर (!OVL_TYPE_UPPER(type))
		ovl_path_lower(dentry, path);
	अन्यथा
		ovl_path_upper(dentry, path);

	वापस type;
पूर्ण

काष्ठा dentry *ovl_dentry_upper(काष्ठा dentry *dentry)
अणु
	वापस ovl_upperdentry_dereference(OVL_I(d_inode(dentry)));
पूर्ण

काष्ठा dentry *ovl_dentry_lower(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	वापस oe->numlower ? oe->lowerstack[0].dentry : शून्य;
पूर्ण

स्थिर काष्ठा ovl_layer *ovl_layer_lower(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	वापस oe->numlower ? oe->lowerstack[0].layer : शून्य;
पूर्ण

/*
 * ovl_dentry_lower() could वापस either a data dentry or metacopy dentry
 * depending on what is stored in lowerstack[0]. At बार we need to find
 * lower dentry which has data (and not metacopy dentry). This helper
 * वापसs the lower data dentry.
 */
काष्ठा dentry *ovl_dentry_lowerdata(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	वापस oe->numlower ? oe->lowerstack[oe->numlower - 1].dentry : शून्य;
पूर्ण

काष्ठा dentry *ovl_dentry_real(काष्ठा dentry *dentry)
अणु
	वापस ovl_dentry_upper(dentry) ?: ovl_dentry_lower(dentry);
पूर्ण

काष्ठा dentry *ovl_i_dentry_upper(काष्ठा inode *inode)
अणु
	वापस ovl_upperdentry_dereference(OVL_I(inode));
पूर्ण

काष्ठा inode *ovl_inode_upper(काष्ठा inode *inode)
अणु
	काष्ठा dentry *upperdentry = ovl_i_dentry_upper(inode);

	वापस upperdentry ? d_inode(upperdentry) : शून्य;
पूर्ण

काष्ठा inode *ovl_inode_lower(काष्ठा inode *inode)
अणु
	वापस OVL_I(inode)->lower;
पूर्ण

काष्ठा inode *ovl_inode_real(काष्ठा inode *inode)
अणु
	वापस ovl_inode_upper(inode) ?: ovl_inode_lower(inode);
पूर्ण

/* Return inode which contains lower data. Do not वापस metacopy */
काष्ठा inode *ovl_inode_lowerdata(काष्ठा inode *inode)
अणु
	अगर (WARN_ON(!S_ISREG(inode->i_mode)))
		वापस शून्य;

	वापस OVL_I(inode)->lowerdata ?: ovl_inode_lower(inode);
पूर्ण

/* Return real inode which contains data. Does not वापस metacopy inode */
काष्ठा inode *ovl_inode_realdata(काष्ठा inode *inode)
अणु
	काष्ठा inode *upperinode;

	upperinode = ovl_inode_upper(inode);
	अगर (upperinode && ovl_has_upperdata(inode))
		वापस upperinode;

	वापस ovl_inode_lowerdata(inode);
पूर्ण

काष्ठा ovl_dir_cache *ovl_dir_cache(काष्ठा inode *inode)
अणु
	वापस OVL_I(inode)->cache;
पूर्ण

व्योम ovl_set_dir_cache(काष्ठा inode *inode, काष्ठा ovl_dir_cache *cache)
अणु
	OVL_I(inode)->cache = cache;
पूर्ण

व्योम ovl_dentry_set_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry)
अणु
	set_bit(flag, &OVL_E(dentry)->flags);
पूर्ण

व्योम ovl_dentry_clear_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry)
अणु
	clear_bit(flag, &OVL_E(dentry)->flags);
पूर्ण

bool ovl_dentry_test_flag(अचिन्हित दीर्घ flag, काष्ठा dentry *dentry)
अणु
	वापस test_bit(flag, &OVL_E(dentry)->flags);
पूर्ण

bool ovl_dentry_is_opaque(काष्ठा dentry *dentry)
अणु
	वापस ovl_dentry_test_flag(OVL_E_OPAQUE, dentry);
पूर्ण

bool ovl_dentry_is_whiteout(काष्ठा dentry *dentry)
अणु
	वापस !dentry->d_inode && ovl_dentry_is_opaque(dentry);
पूर्ण

व्योम ovl_dentry_set_opaque(काष्ठा dentry *dentry)
अणु
	ovl_dentry_set_flag(OVL_E_OPAQUE, dentry);
पूर्ण

/*
 * For hard links and decoded file handles, it's possible क्रम ovl_dentry_upper()
 * to वापस positive, जबतक there's no actual upper alias क्रम the inode.
 * Copy up code needs to know about the existence of the upper alias, so it
 * can't use ovl_dentry_upper().
 */
bool ovl_dentry_has_upper_alias(काष्ठा dentry *dentry)
अणु
	वापस ovl_dentry_test_flag(OVL_E_UPPER_ALIAS, dentry);
पूर्ण

व्योम ovl_dentry_set_upper_alias(काष्ठा dentry *dentry)
अणु
	ovl_dentry_set_flag(OVL_E_UPPER_ALIAS, dentry);
पूर्ण

अटल bool ovl_should_check_upperdata(काष्ठा inode *inode)
अणु
	अगर (!S_ISREG(inode->i_mode))
		वापस false;

	अगर (!ovl_inode_lower(inode))
		वापस false;

	वापस true;
पूर्ण

bool ovl_has_upperdata(काष्ठा inode *inode)
अणु
	अगर (!ovl_should_check_upperdata(inode))
		वापस true;

	अगर (!ovl_test_flag(OVL_UPPERDATA, inode))
		वापस false;
	/*
	 * Pairs with smp_wmb() in ovl_set_upperdata(). Main user of
	 * ovl_has_upperdata() is ovl_copy_up_meta_inode_data(). Make sure
	 * अगर setting of OVL_UPPERDATA is visible, then effects of ग_लिखोs
	 * beक्रमe that are visible too.
	 */
	smp_rmb();
	वापस true;
पूर्ण

व्योम ovl_set_upperdata(काष्ठा inode *inode)
अणु
	/*
	 * Pairs with smp_rmb() in ovl_has_upperdata(). Make sure
	 * अगर OVL_UPPERDATA flag is visible, then effects of ग_लिखो operations
	 * beक्रमe it are visible as well.
	 */
	smp_wmb();
	ovl_set_flag(OVL_UPPERDATA, inode);
पूर्ण

/* Caller should hold ovl_inode->lock */
bool ovl_dentry_needs_data_copy_up_locked(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	अगर (!ovl_खोलो_flags_need_copy_up(flags))
		वापस false;

	वापस !ovl_test_flag(OVL_UPPERDATA, d_inode(dentry));
पूर्ण

bool ovl_dentry_needs_data_copy_up(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	अगर (!ovl_खोलो_flags_need_copy_up(flags))
		वापस false;

	वापस !ovl_has_upperdata(d_inode(dentry));
पूर्ण

bool ovl_redirect_dir(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	वापस ofs->config.redirect_dir && !ofs->noxattr;
पूर्ण

स्थिर अक्षर *ovl_dentry_get_redirect(काष्ठा dentry *dentry)
अणु
	वापस OVL_I(d_inode(dentry))->redirect;
पूर्ण

व्योम ovl_dentry_set_redirect(काष्ठा dentry *dentry, स्थिर अक्षर *redirect)
अणु
	काष्ठा ovl_inode *oi = OVL_I(d_inode(dentry));

	kमुक्त(oi->redirect);
	oi->redirect = redirect;
पूर्ण

व्योम ovl_inode_update(काष्ठा inode *inode, काष्ठा dentry *upperdentry)
अणु
	काष्ठा inode *upperinode = d_inode(upperdentry);

	WARN_ON(OVL_I(inode)->__upperdentry);

	/*
	 * Make sure upperdentry is consistent beक्रमe making it visible
	 */
	smp_wmb();
	OVL_I(inode)->__upperdentry = upperdentry;
	अगर (inode_unhashed(inode)) अणु
		inode->i_निजी = upperinode;
		__insert_inode_hash(inode, (अचिन्हित दीर्घ) upperinode);
	पूर्ण
पूर्ण

अटल व्योम ovl_dir_version_inc(काष्ठा dentry *dentry, bool impurity)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	WARN_ON(!inode_is_locked(inode));
	WARN_ON(!d_is_dir(dentry));
	/*
	 * Version is used by सूची_पढ़ो code to keep cache consistent.
	 * For merge dirs (or dirs with origin) all changes need to be noted.
	 * For non-merge dirs, cache contains only impure entries (i.e. ones
	 * which have been copied up and have origins), so only need to note
	 * changes to impure entries.
	 */
	अगर (!ovl_dir_is_real(dentry) || impurity)
		OVL_I(inode)->version++;
पूर्ण

व्योम ovl_dir_modअगरied(काष्ठा dentry *dentry, bool impurity)
अणु
	/* Copy mसमय/स_समय */
	ovl_copyattr(d_inode(ovl_dentry_upper(dentry)), d_inode(dentry));

	ovl_dir_version_inc(dentry, impurity);
पूर्ण

u64 ovl_dentry_version_get(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	WARN_ON(!inode_is_locked(inode));
	वापस OVL_I(inode)->version;
पूर्ण

bool ovl_is_whiteout(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = dentry->d_inode;

	वापस inode && IS_WHITEOUT(inode);
पूर्ण

काष्ठा file *ovl_path_खोलो(काष्ठा path *path, पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	पूर्णांक err, acc_mode;

	अगर (flags & ~(O_ACCMODE | O_LARGEखाता))
		BUG();

	चयन (flags & O_ACCMODE) अणु
	हाल O_RDONLY:
		acc_mode = MAY_READ;
		अवरोध;
	हाल O_WRONLY:
		acc_mode = MAY_WRITE;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	err = inode_permission(&init_user_ns, inode, acc_mode | MAY_OPEN);
	अगर (err)
		वापस ERR_PTR(err);

	/* O_NOATIME is an optimization, करोn't fail अगर not permitted */
	अगर (inode_owner_or_capable(&init_user_ns, inode))
		flags |= O_NOATIME;

	वापस dentry_खोलो(path, flags, current_cred());
पूर्ण

/* Caller should hold ovl_inode->lock */
अटल bool ovl_alपढ़ोy_copied_up_locked(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	bool disconnected = dentry->d_flags & DCACHE_DISCONNECTED;

	अगर (ovl_dentry_upper(dentry) &&
	    (ovl_dentry_has_upper_alias(dentry) || disconnected) &&
	    !ovl_dentry_needs_data_copy_up_locked(dentry, flags))
		वापस true;

	वापस false;
पूर्ण

bool ovl_alपढ़ोy_copied_up(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	bool disconnected = dentry->d_flags & DCACHE_DISCONNECTED;

	/*
	 * Check अगर copy-up has happened as well as क्रम upper alias (in
	 * हाल of hard links) is there.
	 *
	 * Both checks are lockless:
	 *  - false negatives: will recheck under oi->lock
	 *  - false positives:
	 *    + ovl_dentry_upper() uses memory barriers to ensure the
	 *      upper dentry is up-to-date
	 *    + ovl_dentry_has_upper_alias() relies on locking of
	 *      upper parent i_rwsem to prevent reordering copy-up
	 *      with नाम.
	 */
	अगर (ovl_dentry_upper(dentry) &&
	    (ovl_dentry_has_upper_alias(dentry) || disconnected) &&
	    !ovl_dentry_needs_data_copy_up(dentry, flags))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक ovl_copy_up_start(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक err;

	err = ovl_inode_lock_पूर्णांकerruptible(inode);
	अगर (!err && ovl_alपढ़ोy_copied_up_locked(dentry, flags)) अणु
		err = 1; /* Alपढ़ोy copied up */
		ovl_inode_unlock(inode);
	पूर्ण

	वापस err;
पूर्ण

व्योम ovl_copy_up_end(काष्ठा dentry *dentry)
अणु
	ovl_inode_unlock(d_inode(dentry));
पूर्ण

bool ovl_check_origin_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry)
अणु
	पूर्णांक res;

	res = ovl_करो_getxattr(ofs, dentry, OVL_XATTR_ORIGIN, शून्य, 0);

	/* Zero size value means "copied up but origin unknown" */
	अगर (res >= 0)
		वापस true;

	वापस false;
पूर्ण

bool ovl_check_dir_xattr(काष्ठा super_block *sb, काष्ठा dentry *dentry,
			 क्रमागत ovl_xattr ox)
अणु
	पूर्णांक res;
	अक्षर val;

	अगर (!d_is_dir(dentry))
		वापस false;

	res = ovl_करो_getxattr(OVL_FS(sb), dentry, ox, &val, 1);
	अगर (res == 1 && val == 'y')
		वापस true;

	वापस false;
पूर्ण

#घोषणा OVL_XATTR_OPAQUE_POSTFIX	"opaque"
#घोषणा OVL_XATTR_REसूचीECT_POSTFIX	"redirect"
#घोषणा OVL_XATTR_ORIGIN_POSTFIX	"origin"
#घोषणा OVL_XATTR_IMPURE_POSTFIX	"impure"
#घोषणा OVL_XATTR_NLINK_POSTFIX		"nlink"
#घोषणा OVL_XATTR_UPPER_POSTFIX		"upper"
#घोषणा OVL_XATTR_METACOPY_POSTFIX	"metacopy"

#घोषणा OVL_XATTR_TAB_ENTRY(x) \
	[x] = अणु [false] = OVL_XATTR_TRUSTED_PREFIX x ## _POSTFIX, \
		[true] = OVL_XATTR_USER_PREFIX x ## _POSTFIX पूर्ण

स्थिर अक्षर *स्थिर ovl_xattr_table[][2] = अणु
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_OPAQUE),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_REसूचीECT),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_ORIGIN),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_IMPURE),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_NLINK),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_UPPER),
	OVL_XATTR_TAB_ENTRY(OVL_XATTR_METACOPY),
पूर्ण;

पूर्णांक ovl_check_setxattr(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry,
		       क्रमागत ovl_xattr ox, स्थिर व्योम *value, माप_प्रकार size,
		       पूर्णांक xerr)
अणु
	पूर्णांक err;
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;

	अगर (ofs->noxattr)
		वापस xerr;

	err = ovl_करो_setxattr(ofs, upperdentry, ox, value, size);

	अगर (err == -EOPNOTSUPP) अणु
		pr_warn("cannot set %s xattr on upper\n", ovl_xattr(ofs, ox));
		ofs->noxattr = true;
		वापस xerr;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ovl_set_impure(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry)
अणु
	पूर्णांक err;

	अगर (ovl_test_flag(OVL_IMPURE, d_inode(dentry)))
		वापस 0;

	/*
	 * Do not fail when upper करोesn't support xattrs.
	 * Upper inodes won't have origin nor redirect xattr anyway.
	 */
	err = ovl_check_setxattr(dentry, upperdentry, OVL_XATTR_IMPURE,
				 "y", 1, 0);
	अगर (!err)
		ovl_set_flag(OVL_IMPURE, d_inode(dentry));

	वापस err;
पूर्ण

/**
 * Caller must hold a reference to inode to prevent it from being मुक्तd जबतक
 * it is marked inuse.
 */
bool ovl_inuse_trylock(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	bool locked = false;

	spin_lock(&inode->i_lock);
	अगर (!(inode->i_state & I_OVL_INUSE)) अणु
		inode->i_state |= I_OVL_INUSE;
		locked = true;
	पूर्ण
	spin_unlock(&inode->i_lock);

	वापस locked;
पूर्ण

व्योम ovl_inuse_unlock(काष्ठा dentry *dentry)
अणु
	अगर (dentry) अणु
		काष्ठा inode *inode = d_inode(dentry);

		spin_lock(&inode->i_lock);
		WARN_ON(!(inode->i_state & I_OVL_INUSE));
		inode->i_state &= ~I_OVL_INUSE;
		spin_unlock(&inode->i_lock);
	पूर्ण
पूर्ण

bool ovl_is_inuse(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	bool inuse;

	spin_lock(&inode->i_lock);
	inuse = (inode->i_state & I_OVL_INUSE);
	spin_unlock(&inode->i_lock);

	वापस inuse;
पूर्ण

/*
 * Does this overlay dentry need to be indexed on copy up?
 */
bool ovl_need_index(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *lower = ovl_dentry_lower(dentry);

	अगर (!lower || !ovl_indexdir(dentry->d_sb))
		वापस false;

	/* Index all files क्रम NFS export and consistency verअगरication */
	अगर (ovl_index_all(dentry->d_sb))
		वापस true;

	/* Index only lower hardlinks on copy up */
	अगर (!d_is_dir(lower) && d_inode(lower)->i_nlink > 1)
		वापस true;

	वापस false;
पूर्ण

/* Caller must hold OVL_I(inode)->lock */
अटल व्योम ovl_cleanup_index(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(dentry->d_sb);
	काष्ठा dentry *indexdir = ovl_indexdir(dentry->d_sb);
	काष्ठा inode *dir = indexdir->d_inode;
	काष्ठा dentry *lowerdentry = ovl_dentry_lower(dentry);
	काष्ठा dentry *upperdentry = ovl_dentry_upper(dentry);
	काष्ठा dentry *index = शून्य;
	काष्ठा inode *inode;
	काष्ठा qstr name = अणु पूर्ण;
	पूर्णांक err;

	err = ovl_get_index_name(ofs, lowerdentry, &name);
	अगर (err)
		जाओ fail;

	inode = d_inode(upperdentry);
	अगर (!S_ISसूची(inode->i_mode) && inode->i_nlink != 1) अणु
		pr_warn_ratelimited("cleanup linked index (%pd2, ino=%lu, nlink=%u)\n",
				    upperdentry, inode->i_ino, inode->i_nlink);
		/*
		 * We either have a bug with persistent जोड़ nlink or a lower
		 * hardlink was added जबतक overlay is mounted. Adding a lower
		 * hardlink and then unlinking all overlay hardlinks would drop
		 * overlay nlink to zero beक्रमe all upper inodes are unlinked.
		 * As a safety measure, when that situation is detected, set
		 * the overlay nlink to the index inode nlink minus one क्रम the
		 * index entry itself.
		 */
		set_nlink(d_inode(dentry), inode->i_nlink - 1);
		ovl_set_nlink_upper(dentry);
		जाओ out;
	पूर्ण

	inode_lock_nested(dir, I_MUTEX_PARENT);
	index = lookup_one_len(name.name, indexdir, name.len);
	err = PTR_ERR(index);
	अगर (IS_ERR(index)) अणु
		index = शून्य;
	पूर्ण अन्यथा अगर (ovl_index_all(dentry->d_sb)) अणु
		/* Whiteout orphan index to block future खोलो by handle */
		err = ovl_cleanup_and_whiteout(OVL_FS(dentry->d_sb),
					       dir, index);
	पूर्ण अन्यथा अणु
		/* Cleanup orphan index entries */
		err = ovl_cleanup(dir, index);
	पूर्ण

	inode_unlock(dir);
	अगर (err)
		जाओ fail;

out:
	kमुक्त(name.name);
	dput(index);
	वापस;

fail:
	pr_err("cleanup index of '%pd2' failed (%i)\n", dentry, err);
	जाओ out;
पूर्ण

/*
 * Operations that change overlay inode and upper inode nlink need to be
 * synchronized with copy up क्रम persistent nlink accounting.
 */
पूर्णांक ovl_nlink_start(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	अगर (WARN_ON(!inode))
		वापस -ENOENT;

	/*
	 * With inodes index is enabled, we store the जोड़ overlay nlink
	 * in an xattr on the index inode. When whiting out an indexed lower,
	 * we need to decrement the overlay persistent nlink, but beक्रमe the
	 * first copy up, we have no upper index inode to store the xattr.
	 *
	 * As a workaround, beक्रमe whiteout/नाम over an indexed lower,
	 * copy up to create the upper index. Creating the upper index will
	 * initialize the overlay nlink, so it could be dropped अगर unlink
	 * or नाम succeeds.
	 *
	 * TODO: implement metadata only index copy up when called with
	 *       ovl_copy_up_flags(dentry, O_PATH).
	 */
	अगर (ovl_need_index(dentry) && !ovl_dentry_has_upper_alias(dentry)) अणु
		err = ovl_copy_up(dentry);
		अगर (err)
			वापस err;
	पूर्ण

	err = ovl_inode_lock_पूर्णांकerruptible(inode);
	अगर (err)
		वापस err;

	अगर (d_is_dir(dentry) || !ovl_test_flag(OVL_INDEX, inode))
		जाओ out;

	old_cred = ovl_override_creds(dentry->d_sb);
	/*
	 * The overlay inode nlink should be incremented/decremented IFF the
	 * upper operation succeeds, aदीर्घ with nlink change of upper inode.
	 * Thereक्रमe, beक्रमe link/unlink/नाम, we store the जोड़ nlink
	 * value relative to the upper inode nlink in an upper inode xattr.
	 */
	err = ovl_set_nlink_upper(dentry);
	revert_creds(old_cred);

out:
	अगर (err)
		ovl_inode_unlock(inode);

	वापस err;
पूर्ण

व्योम ovl_nlink_end(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (ovl_test_flag(OVL_INDEX, inode) && inode->i_nlink == 0) अणु
		स्थिर काष्ठा cred *old_cred;

		old_cred = ovl_override_creds(dentry->d_sb);
		ovl_cleanup_index(dentry);
		revert_creds(old_cred);
	पूर्ण

	ovl_inode_unlock(inode);
पूर्ण

पूर्णांक ovl_lock_नाम_workdir(काष्ठा dentry *workdir, काष्ठा dentry *upperdir)
अणु
	/* Workdir should not be the same as upperdir */
	अगर (workdir == upperdir)
		जाओ err;

	/* Workdir should not be subdir of upperdir and vice versa */
	अगर (lock_नाम(workdir, upperdir) != शून्य)
		जाओ err_unlock;

	वापस 0;

err_unlock:
	unlock_नाम(workdir, upperdir);
err:
	pr_err("failed to lock workdir+upperdir\n");
	वापस -EIO;
पूर्ण

/* err < 0, 0 अगर no metacopy xattr, 1 अगर metacopy xattr found */
पूर्णांक ovl_check_metacopy_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry)
अणु
	पूर्णांक res;

	/* Only regular files can have metacopy xattr */
	अगर (!S_ISREG(d_inode(dentry)->i_mode))
		वापस 0;

	res = ovl_करो_getxattr(ofs, dentry, OVL_XATTR_METACOPY, शून्य, 0);
	अगर (res < 0) अणु
		अगर (res == -ENODATA || res == -EOPNOTSUPP)
			वापस 0;
		/*
		 * getxattr on user.* may fail with EACCES in हाल there's no
		 * पढ़ो permission on the inode.  Not much we can करो, other than
		 * tell the caller that this is not a metacopy inode.
		 */
		अगर (ofs->config.userxattr && res == -EACCES)
			वापस 0;
		जाओ out;
	पूर्ण

	वापस 1;
out:
	pr_warn_ratelimited("failed to get metacopy (%i)\n", res);
	वापस res;
पूर्ण

bool ovl_is_metacopy_dentry(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	अगर (!d_is_reg(dentry))
		वापस false;

	अगर (ovl_dentry_upper(dentry)) अणु
		अगर (!ovl_has_upperdata(d_inode(dentry)))
			वापस true;
		वापस false;
	पूर्ण

	वापस (oe->numlower > 1);
पूर्ण

अक्षर *ovl_get_redirect_xattr(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
			     पूर्णांक padding)
अणु
	पूर्णांक res;
	अक्षर *s, *next, *buf = शून्य;

	res = ovl_करो_getxattr(ofs, dentry, OVL_XATTR_REसूचीECT, शून्य, 0);
	अगर (res == -ENODATA || res == -EOPNOTSUPP)
		वापस शून्य;
	अगर (res < 0)
		जाओ fail;
	अगर (res == 0)
		जाओ invalid;

	buf = kzalloc(res + padding + 1, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	res = ovl_करो_getxattr(ofs, dentry, OVL_XATTR_REसूचीECT, buf, res);
	अगर (res < 0)
		जाओ fail;
	अगर (res == 0)
		जाओ invalid;

	अगर (buf[0] == '/') अणु
		क्रम (s = buf; *s++ == '/'; s = next) अणु
			next = म_अक्षरnul(s, '/');
			अगर (s == next)
				जाओ invalid;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (म_अक्षर(buf, '/') != शून्य)
			जाओ invalid;
	पूर्ण

	वापस buf;
invalid:
	pr_warn_ratelimited("invalid redirect (%s)\n", buf);
	res = -EINVAL;
	जाओ err_मुक्त;
fail:
	pr_warn_ratelimited("failed to get redirect (%i)\n", res);
err_मुक्त:
	kमुक्त(buf);
	वापस ERR_PTR(res);
पूर्ण

/*
 * ovl_sync_status() - Check fs sync status क्रम अस्थिर mounts
 *
 * Returns 1 अगर this is not a अस्थिर mount and a real sync is required.
 *
 * Returns 0 अगर syncing can be skipped because mount is अस्थिर, and no errors
 * have occurred on the upperdir since the mount.
 *
 * Returns -त्रुटि_सं अगर it is a अस्थिर mount, and the error that occurred since
 * the last mount. If the error code changes, it'll वापस the latest error
 * code.
 */

पूर्णांक ovl_sync_status(काष्ठा ovl_fs *ofs)
अणु
	काष्ठा vfsmount *mnt;

	अगर (ovl_should_sync(ofs))
		वापस 1;

	mnt = ovl_upper_mnt(ofs);
	अगर (!mnt)
		वापस 0;

	वापस errseq_check(&mnt->mnt_sb->s_wb_err, ofs->errseq);
पूर्ण
