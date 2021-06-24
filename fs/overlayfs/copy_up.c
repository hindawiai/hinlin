<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/splice.h>
#समावेश <linux/xattr.h>
#समावेश <linux/security.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/cred.h>
#समावेश <linux/namei.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/exportfs.h>
#समावेश "overlayfs.h"

#घोषणा OVL_COPY_UP_CHUNK_SIZE (1 << 20)

अटल पूर्णांक ovl_ccup_set(स्थिर अक्षर *buf, स्थिर काष्ठा kernel_param *param)
अणु
	pr_warn("\"check_copy_up\" module option is obsolete\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ovl_ccup_get(अक्षर *buf, स्थिर काष्ठा kernel_param *param)
अणु
	वापस प्र_लिखो(buf, "N\n");
पूर्ण

module_param_call(check_copy_up, ovl_ccup_set, ovl_ccup_get, शून्य, 0644);
MODULE_PARM_DESC(check_copy_up, "Obsolete; does nothing");

अटल bool ovl_must_copy_xattr(स्थिर अक्षर *name)
अणु
	वापस !म_भेद(name, XATTR_POSIX_ACL_ACCESS) ||
	       !म_भेद(name, XATTR_POSIX_ACL_DEFAULT) ||
	       !म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN);
पूर्ण

पूर्णांक ovl_copy_xattr(काष्ठा super_block *sb, काष्ठा dentry *old,
		   काष्ठा dentry *new)
अणु
	sमाप_प्रकार list_size, size, value_size = 0;
	अक्षर *buf, *name, *value = शून्य;
	पूर्णांक error = 0;
	माप_प्रकार slen;

	अगर (!(old->d_inode->i_opflags & IOP_XATTR) ||
	    !(new->d_inode->i_opflags & IOP_XATTR))
		वापस 0;

	list_size = vfs_listxattr(old, शून्य, 0);
	अगर (list_size <= 0) अणु
		अगर (list_size == -EOPNOTSUPP)
			वापस 0;
		वापस list_size;
	पूर्ण

	buf = kzalloc(list_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	list_size = vfs_listxattr(old, buf, list_size);
	अगर (list_size <= 0) अणु
		error = list_size;
		जाओ out;
	पूर्ण

	क्रम (name = buf; list_size; name += slen) अणु
		slen = strnlen(name, list_size) + 1;

		/* underlying fs providing us with an broken xattr list? */
		अगर (WARN_ON(slen > list_size)) अणु
			error = -EIO;
			अवरोध;
		पूर्ण
		list_size -= slen;

		अगर (ovl_is_निजी_xattr(sb, name))
			जारी;

		error = security_inode_copy_up_xattr(name);
		अगर (error < 0 && error != -EOPNOTSUPP)
			अवरोध;
		अगर (error == 1) अणु
			error = 0;
			जारी; /* Discard */
		पूर्ण
retry:
		size = vfs_getxattr(&init_user_ns, old, name, value, value_size);
		अगर (size == -दुस्फल)
			size = vfs_getxattr(&init_user_ns, old, name, शून्य, 0);

		अगर (size < 0) अणु
			error = size;
			अवरोध;
		पूर्ण

		अगर (size > value_size) अणु
			व्योम *new;

			new = kपुनः_स्मृति(value, size, GFP_KERNEL);
			अगर (!new) अणु
				error = -ENOMEM;
				अवरोध;
			पूर्ण
			value = new;
			value_size = size;
			जाओ retry;
		पूर्ण

		error = vfs_setxattr(&init_user_ns, new, name, value, size, 0);
		अगर (error) अणु
			अगर (error != -EOPNOTSUPP || ovl_must_copy_xattr(name))
				अवरोध;

			/* Ignore failure to copy unknown xattrs */
			error = 0;
		पूर्ण
	पूर्ण
	kमुक्त(value);
out:
	kमुक्त(buf);
	वापस error;
पूर्ण

अटल पूर्णांक ovl_copy_up_data(काष्ठा ovl_fs *ofs, काष्ठा path *old,
			    काष्ठा path *new, loff_t len)
अणु
	काष्ठा file *old_file;
	काष्ठा file *new_file;
	loff_t old_pos = 0;
	loff_t new_pos = 0;
	loff_t cloned;
	loff_t data_pos = -1;
	loff_t hole_len;
	bool skip_hole = false;
	पूर्णांक error = 0;

	अगर (len == 0)
		वापस 0;

	old_file = ovl_path_खोलो(old, O_LARGEखाता | O_RDONLY);
	अगर (IS_ERR(old_file))
		वापस PTR_ERR(old_file);

	new_file = ovl_path_खोलो(new, O_LARGEखाता | O_WRONLY);
	अगर (IS_ERR(new_file)) अणु
		error = PTR_ERR(new_file);
		जाओ out_fput;
	पूर्ण

	/* Try to use clone_file_range to clone up within the same fs */
	cloned = करो_clone_file_range(old_file, 0, new_file, 0, len, 0);
	अगर (cloned == len)
		जाओ out;
	/* Couldn't clone, so now we try to copy the data */

	/* Check अगर lower fs supports seek operation */
	अगर (old_file->f_mode & FMODE_LSEEK &&
	    old_file->f_op->llseek)
		skip_hole = true;

	जबतक (len) अणु
		माप_प्रकार this_len = OVL_COPY_UP_CHUNK_SIZE;
		दीर्घ bytes;

		अगर (len < this_len)
			this_len = len;

		अगर (संकेत_pending_state(TASK_KILLABLE, current)) अणु
			error = -EINTR;
			अवरोध;
		पूर्ण

		/*
		 * Fill zero क्रम hole will cost unnecessary disk space
		 * and meanजबतक slow करोwn the copy-up speed, so we करो
		 * an optimization क्रम hole during copy-up, it relies
		 * on SEEK_DATA implementation in lower fs so अगर lower
		 * fs करोes not support it, copy-up will behave as beक्रमe.
		 *
		 * Detail logic of hole detection as below:
		 * When we detect next data position is larger than current
		 * position we will skip that hole, otherwise we copy
		 * data in the size of OVL_COPY_UP_CHUNK_SIZE. Actually,
		 * it may not recognize all kind of holes and someबार
		 * only skips partial of hole area. However, it will be
		 * enough क्रम most of the use हालs.
		 */

		अगर (skip_hole && data_pos < old_pos) अणु
			data_pos = vfs_llseek(old_file, old_pos, SEEK_DATA);
			अगर (data_pos > old_pos) अणु
				hole_len = data_pos - old_pos;
				len -= hole_len;
				old_pos = new_pos = data_pos;
				जारी;
			पूर्ण अन्यथा अगर (data_pos == -ENXIO) अणु
				अवरोध;
			पूर्ण अन्यथा अगर (data_pos < 0) अणु
				skip_hole = false;
			पूर्ण
		पूर्ण

		bytes = करो_splice_direct(old_file, &old_pos,
					 new_file, &new_pos,
					 this_len, SPLICE_F_MOVE);
		अगर (bytes <= 0) अणु
			error = bytes;
			अवरोध;
		पूर्ण
		WARN_ON(old_pos != new_pos);

		len -= bytes;
	पूर्ण
out:
	अगर (!error && ovl_should_sync(ofs))
		error = vfs_fsync(new_file, 0);
	fput(new_file);
out_fput:
	fput(old_file);
	वापस error;
पूर्ण

अटल पूर्णांक ovl_set_size(काष्ठा dentry *upperdentry, काष्ठा kstat *stat)
अणु
	काष्ठा iattr attr = अणु
		.ia_valid = ATTR_SIZE,
		.ia_size = stat->size,
	पूर्ण;

	वापस notअगरy_change(&init_user_ns, upperdentry, &attr, शून्य);
पूर्ण

अटल पूर्णांक ovl_set_बारtamps(काष्ठा dentry *upperdentry, काष्ठा kstat *stat)
अणु
	काष्ठा iattr attr = अणु
		.ia_valid =
		     ATTR_ATIME | ATTR_MTIME | ATTR_ATIME_SET | ATTR_MTIME_SET,
		.ia_aसमय = stat->aसमय,
		.ia_mसमय = stat->mसमय,
	पूर्ण;

	वापस notअगरy_change(&init_user_ns, upperdentry, &attr, शून्य);
पूर्ण

पूर्णांक ovl_set_attr(काष्ठा dentry *upperdentry, काष्ठा kstat *stat)
अणु
	पूर्णांक err = 0;

	अगर (!S_ISLNK(stat->mode)) अणु
		काष्ठा iattr attr = अणु
			.ia_valid = ATTR_MODE,
			.ia_mode = stat->mode,
		पूर्ण;
		err = notअगरy_change(&init_user_ns, upperdentry, &attr, शून्य);
	पूर्ण
	अगर (!err) अणु
		काष्ठा iattr attr = अणु
			.ia_valid = ATTR_UID | ATTR_GID,
			.ia_uid = stat->uid,
			.ia_gid = stat->gid,
		पूर्ण;
		err = notअगरy_change(&init_user_ns, upperdentry, &attr, शून्य);
	पूर्ण
	अगर (!err)
		ovl_set_बारtamps(upperdentry, stat);

	वापस err;
पूर्ण

काष्ठा ovl_fh *ovl_encode_real_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *real,
				  bool is_upper)
अणु
	काष्ठा ovl_fh *fh;
	पूर्णांक fh_type, dwords;
	पूर्णांक buflen = MAX_HANDLE_SZ;
	uuid_t *uuid = &real->d_sb->s_uuid;
	पूर्णांक err;

	/* Make sure the real fid stays 32bit aligned */
	BUILD_BUG_ON(OVL_FH_FID_OFFSET % 4);
	BUILD_BUG_ON(MAX_HANDLE_SZ + OVL_FH_FID_OFFSET > 255);

	fh = kzalloc(buflen + OVL_FH_FID_OFFSET, GFP_KERNEL);
	अगर (!fh)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * We encode a non-connectable file handle क्रम non-dir, because we
	 * only need to find the lower inode number and we करोn't want to pay
	 * the price or reconnecting the dentry.
	 */
	dwords = buflen >> 2;
	fh_type = exportfs_encode_fh(real, (व्योम *)fh->fb.fid, &dwords, 0);
	buflen = (dwords << 2);

	err = -EIO;
	अगर (WARN_ON(fh_type < 0) ||
	    WARN_ON(buflen > MAX_HANDLE_SZ) ||
	    WARN_ON(fh_type == खाताID_INVALID))
		जाओ out_err;

	fh->fb.version = OVL_FH_VERSION;
	fh->fb.magic = OVL_FH_MAGIC;
	fh->fb.type = fh_type;
	fh->fb.flags = OVL_FH_FLAG_CPU_ENDIAN;
	/*
	 * When we will want to decode an overlay dentry from this handle
	 * and all layers are on the same fs, अगर we get a disconncted real
	 * dentry when we decode fid, the only way to tell अगर we should assign
	 * it to upperdentry or to lowerstack is by checking this flag.
	 */
	अगर (is_upper)
		fh->fb.flags |= OVL_FH_FLAG_PATH_UPPER;
	fh->fb.len = माप(fh->fb) + buflen;
	अगर (ofs->config.uuid)
		fh->fb.uuid = *uuid;

	वापस fh;

out_err:
	kमुक्त(fh);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक ovl_set_origin(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
		   काष्ठा dentry *lower, काष्ठा dentry *upper)
अणु
	स्थिर काष्ठा ovl_fh *fh = शून्य;
	पूर्णांक err;

	/*
	 * When lower layer करोesn't support export operations store a 'null' fh,
	 * so we can use the overlay.origin xattr to distignuish between a copy
	 * up and a pure upper inode.
	 */
	अगर (ovl_can_decode_fh(lower->d_sb)) अणु
		fh = ovl_encode_real_fh(ofs, lower, false);
		अगर (IS_ERR(fh))
			वापस PTR_ERR(fh);
	पूर्ण

	/*
	 * Do not fail when upper करोesn't support xattrs.
	 */
	err = ovl_check_setxattr(dentry, upper, OVL_XATTR_ORIGIN, fh->buf,
				 fh ? fh->fb.len : 0, 0);
	kमुक्त(fh);

	/* Ignore -EPERM from setting "user.*" on symlink/special */
	वापस err == -EPERM ? 0 : err;
पूर्ण

/* Store file handle of @upper dir in @index dir entry */
अटल पूर्णांक ovl_set_upper_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *upper,
			    काष्ठा dentry *index)
अणु
	स्थिर काष्ठा ovl_fh *fh;
	पूर्णांक err;

	fh = ovl_encode_real_fh(ofs, upper, true);
	अगर (IS_ERR(fh))
		वापस PTR_ERR(fh);

	err = ovl_करो_setxattr(ofs, index, OVL_XATTR_UPPER, fh->buf, fh->fb.len);

	kमुक्त(fh);
	वापस err;
पूर्ण

/*
 * Create and install index entry.
 *
 * Caller must hold i_mutex on indexdir.
 */
अटल पूर्णांक ovl_create_index(काष्ठा dentry *dentry, काष्ठा dentry *origin,
			    काष्ठा dentry *upper)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(dentry->d_sb);
	काष्ठा dentry *indexdir = ovl_indexdir(dentry->d_sb);
	काष्ठा inode *dir = d_inode(indexdir);
	काष्ठा dentry *index = शून्य;
	काष्ठा dentry *temp = शून्य;
	काष्ठा qstr name = अणु पूर्ण;
	पूर्णांक err;

	/*
	 * For now this is only used क्रम creating index entry क्रम directories,
	 * because non-dir are copied up directly to index and then hardlinked
	 * to upper dir.
	 *
	 * TODO: implement create index क्रम non-dir, so we can call it when
	 * encoding file handle क्रम non-dir in हाल index करोes not exist.
	 */
	अगर (WARN_ON(!d_is_dir(dentry)))
		वापस -EIO;

	/* Directory not expected to be indexed beक्रमe copy up */
	अगर (WARN_ON(ovl_test_flag(OVL_INDEX, d_inode(dentry))))
		वापस -EIO;

	err = ovl_get_index_name(ofs, origin, &name);
	अगर (err)
		वापस err;

	temp = ovl_create_temp(indexdir, OVL_CATTR(S_IFसूची | 0));
	err = PTR_ERR(temp);
	अगर (IS_ERR(temp))
		जाओ मुक्त_name;

	err = ovl_set_upper_fh(ofs, upper, temp);
	अगर (err)
		जाओ out;

	index = lookup_one_len(name.name, indexdir, name.len);
	अगर (IS_ERR(index)) अणु
		err = PTR_ERR(index);
	पूर्ण अन्यथा अणु
		err = ovl_करो_नाम(dir, temp, dir, index, 0);
		dput(index);
	पूर्ण
out:
	अगर (err)
		ovl_cleanup(dir, temp);
	dput(temp);
मुक्त_name:
	kमुक्त(name.name);
	वापस err;
पूर्ण

काष्ठा ovl_copy_up_ctx अणु
	काष्ठा dentry *parent;
	काष्ठा dentry *dentry;
	काष्ठा path lowerpath;
	काष्ठा kstat stat;
	काष्ठा kstat pstat;
	स्थिर अक्षर *link;
	काष्ठा dentry *destdir;
	काष्ठा qstr destname;
	काष्ठा dentry *workdir;
	bool origin;
	bool indexed;
	bool metacopy;
पूर्ण;

अटल पूर्णांक ovl_link_up(काष्ठा ovl_copy_up_ctx *c)
अणु
	पूर्णांक err;
	काष्ठा dentry *upper;
	काष्ठा dentry *upperdir = ovl_dentry_upper(c->parent);
	काष्ठा inode *udir = d_inode(upperdir);

	/* Mark parent "impure" because it may now contain non-pure upper */
	err = ovl_set_impure(c->parent, upperdir);
	अगर (err)
		वापस err;

	err = ovl_set_nlink_lower(c->dentry);
	अगर (err)
		वापस err;

	inode_lock_nested(udir, I_MUTEX_PARENT);
	upper = lookup_one_len(c->dentry->d_name.name, upperdir,
			       c->dentry->d_name.len);
	err = PTR_ERR(upper);
	अगर (!IS_ERR(upper)) अणु
		err = ovl_करो_link(ovl_dentry_upper(c->dentry), udir, upper);
		dput(upper);

		अगर (!err) अणु
			/* Restore बारtamps on parent (best efक्रमt) */
			ovl_set_बारtamps(upperdir, &c->pstat);
			ovl_dentry_set_upper_alias(c->dentry);
		पूर्ण
	पूर्ण
	inode_unlock(udir);
	अगर (err)
		वापस err;

	err = ovl_set_nlink_upper(c->dentry);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_copy_up_inode(काष्ठा ovl_copy_up_ctx *c, काष्ठा dentry *temp)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(c->dentry->d_sb);
	पूर्णांक err;

	/*
	 * Copy up data first and then xattrs. Writing data after
	 * xattrs will हटाओ security.capability xattr स्वतःmatically.
	 */
	अगर (S_ISREG(c->stat.mode) && !c->metacopy) अणु
		काष्ठा path upperpath, datapath;

		ovl_path_upper(c->dentry, &upperpath);
		अगर (WARN_ON(upperpath.dentry != शून्य))
			वापस -EIO;
		upperpath.dentry = temp;

		ovl_path_lowerdata(c->dentry, &datapath);
		err = ovl_copy_up_data(ofs, &datapath, &upperpath,
				       c->stat.size);
		अगर (err)
			वापस err;
	पूर्ण

	err = ovl_copy_xattr(c->dentry->d_sb, c->lowerpath.dentry, temp);
	अगर (err)
		वापस err;

	/*
	 * Store identअगरier of lower inode in upper inode xattr to
	 * allow lookup of the copy up origin inode.
	 *
	 * Don't set origin when we are अवरोधing the association with a lower
	 * hard link.
	 */
	अगर (c->origin) अणु
		err = ovl_set_origin(ofs, c->dentry, c->lowerpath.dentry, temp);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (c->metacopy) अणु
		err = ovl_check_setxattr(c->dentry, temp, OVL_XATTR_METACOPY,
					 शून्य, 0, -EOPNOTSUPP);
		अगर (err)
			वापस err;
	पूर्ण

	inode_lock(temp->d_inode);
	अगर (S_ISREG(c->stat.mode))
		err = ovl_set_size(temp, &c->stat);
	अगर (!err)
		err = ovl_set_attr(temp, &c->stat);
	inode_unlock(temp->d_inode);

	वापस err;
पूर्ण

काष्ठा ovl_cu_creds अणु
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
पूर्ण;

अटल पूर्णांक ovl_prep_cu_creds(काष्ठा dentry *dentry, काष्ठा ovl_cu_creds *cc)
अणु
	पूर्णांक err;

	cc->old = cc->new = शून्य;
	err = security_inode_copy_up(dentry, &cc->new);
	अगर (err < 0)
		वापस err;

	अगर (cc->new)
		cc->old = override_creds(cc->new);

	वापस 0;
पूर्ण

अटल व्योम ovl_revert_cu_creds(काष्ठा ovl_cu_creds *cc)
अणु
	अगर (cc->new) अणु
		revert_creds(cc->old);
		put_cred(cc->new);
	पूर्ण
पूर्ण

/*
 * Copyup using workdir to prepare temp file.  Used when copying up directories,
 * special files or when upper fs करोesn't support O_TMPखाता.
 */
अटल पूर्णांक ovl_copy_up_workdir(काष्ठा ovl_copy_up_ctx *c)
अणु
	काष्ठा inode *inode;
	काष्ठा inode *udir = d_inode(c->destdir), *wdir = d_inode(c->workdir);
	काष्ठा dentry *temp, *upper;
	काष्ठा ovl_cu_creds cc;
	पूर्णांक err;
	काष्ठा ovl_cattr cattr = अणु
		/* Can't properly set mode on creation because of the umask */
		.mode = c->stat.mode & S_IFMT,
		.rdev = c->stat.rdev,
		.link = c->link
	पूर्ण;

	/* workdir and destdir could be the same when copying up to indexdir */
	err = -EIO;
	अगर (lock_नाम(c->workdir, c->destdir) != शून्य)
		जाओ unlock;

	err = ovl_prep_cu_creds(c->dentry, &cc);
	अगर (err)
		जाओ unlock;

	temp = ovl_create_temp(c->workdir, &cattr);
	ovl_revert_cu_creds(&cc);

	err = PTR_ERR(temp);
	अगर (IS_ERR(temp))
		जाओ unlock;

	err = ovl_copy_up_inode(c, temp);
	अगर (err)
		जाओ cleanup;

	अगर (S_ISसूची(c->stat.mode) && c->indexed) अणु
		err = ovl_create_index(c->dentry, c->lowerpath.dentry, temp);
		अगर (err)
			जाओ cleanup;
	पूर्ण

	upper = lookup_one_len(c->destname.name, c->destdir, c->destname.len);
	err = PTR_ERR(upper);
	अगर (IS_ERR(upper))
		जाओ cleanup;

	err = ovl_करो_नाम(wdir, temp, udir, upper, 0);
	dput(upper);
	अगर (err)
		जाओ cleanup;

	अगर (!c->metacopy)
		ovl_set_upperdata(d_inode(c->dentry));
	inode = d_inode(c->dentry);
	ovl_inode_update(inode, temp);
	अगर (S_ISसूची(inode->i_mode))
		ovl_set_flag(OVL_WHITEOUTS, inode);
unlock:
	unlock_नाम(c->workdir, c->destdir);

	वापस err;

cleanup:
	ovl_cleanup(wdir, temp);
	dput(temp);
	जाओ unlock;
पूर्ण

/* Copyup using O_TMPखाता which करोes not require cross dir locking */
अटल पूर्णांक ovl_copy_up_क्षणिक_ख(काष्ठा ovl_copy_up_ctx *c)
अणु
	काष्ठा inode *udir = d_inode(c->destdir);
	काष्ठा dentry *temp, *upper;
	काष्ठा ovl_cu_creds cc;
	पूर्णांक err;

	err = ovl_prep_cu_creds(c->dentry, &cc);
	अगर (err)
		वापस err;

	temp = ovl_करो_क्षणिक_ख(c->workdir, c->stat.mode);
	ovl_revert_cu_creds(&cc);

	अगर (IS_ERR(temp))
		वापस PTR_ERR(temp);

	err = ovl_copy_up_inode(c, temp);
	अगर (err)
		जाओ out_dput;

	inode_lock_nested(udir, I_MUTEX_PARENT);

	upper = lookup_one_len(c->destname.name, c->destdir, c->destname.len);
	err = PTR_ERR(upper);
	अगर (!IS_ERR(upper)) अणु
		err = ovl_करो_link(temp, udir, upper);
		dput(upper);
	पूर्ण
	inode_unlock(udir);

	अगर (err)
		जाओ out_dput;

	अगर (!c->metacopy)
		ovl_set_upperdata(d_inode(c->dentry));
	ovl_inode_update(d_inode(c->dentry), temp);

	वापस 0;

out_dput:
	dput(temp);
	वापस err;
पूर्ण

/*
 * Copy up a single dentry
 *
 * All नामs start with copy up of source अगर necessary.  The actual
 * नाम will only proceed once the copy up was successful.  Copy up uses
 * upper parent i_mutex क्रम exclusion.  Since नाम can change d_parent it
 * is possible that the copy up will lock the old parent.  At that poपूर्णांक
 * the file will have alपढ़ोy been copied up anyway.
 */
अटल पूर्णांक ovl_करो_copy_up(काष्ठा ovl_copy_up_ctx *c)
अणु
	पूर्णांक err;
	काष्ठा ovl_fs *ofs = OVL_FS(c->dentry->d_sb);
	bool to_index = false;

	/*
	 * Indexed non-dir is copied up directly to the index entry and then
	 * hardlinked to upper dir. Indexed dir is copied up to indexdir,
	 * then index entry is created and then copied up dir installed.
	 * Copying dir up to indexdir instead of workdir simplअगरies locking.
	 */
	अगर (ovl_need_index(c->dentry)) अणु
		c->indexed = true;
		अगर (S_ISसूची(c->stat.mode))
			c->workdir = ovl_indexdir(c->dentry->d_sb);
		अन्यथा
			to_index = true;
	पूर्ण

	अगर (S_ISसूची(c->stat.mode) || c->stat.nlink == 1 || to_index)
		c->origin = true;

	अगर (to_index) अणु
		c->destdir = ovl_indexdir(c->dentry->d_sb);
		err = ovl_get_index_name(ofs, c->lowerpath.dentry, &c->destname);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (WARN_ON(!c->parent)) अणु
		/* Disconnected dentry must be copied up to index dir */
		वापस -EIO;
	पूर्ण अन्यथा अणु
		/*
		 * Mark parent "impure" because it may now contain non-pure
		 * upper
		 */
		err = ovl_set_impure(c->parent, c->destdir);
		अगर (err)
			वापस err;
	पूर्ण

	/* Should we copyup with O_TMPखाता or with workdir? */
	अगर (S_ISREG(c->stat.mode) && ofs->क्षणिक_ख)
		err = ovl_copy_up_क्षणिक_ख(c);
	अन्यथा
		err = ovl_copy_up_workdir(c);
	अगर (err)
		जाओ out;

	अगर (c->indexed)
		ovl_set_flag(OVL_INDEX, d_inode(c->dentry));

	अगर (to_index) अणु
		/* Initialize nlink क्रम copy up of disconnected dentry */
		err = ovl_set_nlink_upper(c->dentry);
	पूर्ण अन्यथा अणु
		काष्ठा inode *udir = d_inode(c->destdir);

		/* Restore बारtamps on parent (best efक्रमt) */
		inode_lock(udir);
		ovl_set_बारtamps(c->destdir, &c->pstat);
		inode_unlock(udir);

		ovl_dentry_set_upper_alias(c->dentry);
	पूर्ण

out:
	अगर (to_index)
		kमुक्त(c->destname.name);
	वापस err;
पूर्ण

अटल bool ovl_need_meta_copy_up(काष्ठा dentry *dentry, umode_t mode,
				  पूर्णांक flags)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;

	अगर (!ofs->config.metacopy)
		वापस false;

	अगर (!S_ISREG(mode))
		वापस false;

	अगर (flags && ((OPEN_FMODE(flags) & FMODE_WRITE) || (flags & O_TRUNC)))
		वापस false;

	वापस true;
पूर्ण

अटल sमाप_प्रकार ovl_getxattr(काष्ठा dentry *dentry, अक्षर *name, अक्षर **value)
अणु
	sमाप_प्रकार res;
	अक्षर *buf;

	res = vfs_getxattr(&init_user_ns, dentry, name, शून्य, 0);
	अगर (res == -ENODATA || res == -EOPNOTSUPP)
		res = 0;

	अगर (res > 0) अणु
		buf = kzalloc(res, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		res = vfs_getxattr(&init_user_ns, dentry, name, buf, res);
		अगर (res < 0)
			kमुक्त(buf);
		अन्यथा
			*value = buf;
	पूर्ण
	वापस res;
पूर्ण

/* Copy up data of an inode which was copied up metadata only in the past. */
अटल पूर्णांक ovl_copy_up_meta_inode_data(काष्ठा ovl_copy_up_ctx *c)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(c->dentry->d_sb);
	काष्ठा path upperpath, datapath;
	पूर्णांक err;
	अक्षर *capability = शून्य;
	sमाप_प्रकार cap_size;

	ovl_path_upper(c->dentry, &upperpath);
	अगर (WARN_ON(upperpath.dentry == शून्य))
		वापस -EIO;

	ovl_path_lowerdata(c->dentry, &datapath);
	अगर (WARN_ON(datapath.dentry == शून्य))
		वापस -EIO;

	अगर (c->stat.size) अणु
		err = cap_size = ovl_getxattr(upperpath.dentry, XATTR_NAME_CAPS,
					      &capability);
		अगर (cap_size < 0)
			जाओ out;
	पूर्ण

	err = ovl_copy_up_data(ofs, &datapath, &upperpath, c->stat.size);
	अगर (err)
		जाओ out_मुक्त;

	/*
	 * Writing to upper file will clear security.capability xattr. We
	 * करोn't want that to happen क्रम normal copy-up operation.
	 */
	अगर (capability) अणु
		err = vfs_setxattr(&init_user_ns, upperpath.dentry,
				   XATTR_NAME_CAPS, capability, cap_size, 0);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण


	err = ovl_करो_हटाओxattr(ofs, upperpath.dentry, OVL_XATTR_METACOPY);
	अगर (err)
		जाओ out_मुक्त;

	ovl_set_upperdata(d_inode(c->dentry));
out_मुक्त:
	kमुक्त(capability);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ovl_copy_up_one(काष्ठा dentry *parent, काष्ठा dentry *dentry,
			   पूर्णांक flags)
अणु
	पूर्णांक err;
	DEFINE_DELAYED_CALL(करोne);
	काष्ठा path parentpath;
	काष्ठा ovl_copy_up_ctx ctx = अणु
		.parent = parent,
		.dentry = dentry,
		.workdir = ovl_workdir(dentry),
	पूर्ण;

	अगर (WARN_ON(!ctx.workdir))
		वापस -EROFS;

	ovl_path_lower(dentry, &ctx.lowerpath);
	err = vfs_getattr(&ctx.lowerpath, &ctx.stat,
			  STATX_BASIC_STATS, AT_STATX_SYNC_AS_STAT);
	अगर (err)
		वापस err;

	ctx.metacopy = ovl_need_meta_copy_up(dentry, ctx.stat.mode, flags);

	अगर (parent) अणु
		ovl_path_upper(parent, &parentpath);
		ctx.destdir = parentpath.dentry;
		ctx.destname = dentry->d_name;

		err = vfs_getattr(&parentpath, &ctx.pstat,
				  STATX_ATIME | STATX_MTIME,
				  AT_STATX_SYNC_AS_STAT);
		अगर (err)
			वापस err;
	पूर्ण

	/* maybe truncate regular file. this has no effect on dirs */
	अगर (flags & O_TRUNC)
		ctx.stat.size = 0;

	अगर (S_ISLNK(ctx.stat.mode)) अणु
		ctx.link = vfs_get_link(ctx.lowerpath.dentry, &करोne);
		अगर (IS_ERR(ctx.link))
			वापस PTR_ERR(ctx.link);
	पूर्ण

	err = ovl_copy_up_start(dentry, flags);
	/* err < 0: पूर्णांकerrupted, err > 0: raced with another copy-up */
	अगर (unlikely(err)) अणु
		अगर (err > 0)
			err = 0;
	पूर्ण अन्यथा अणु
		अगर (!ovl_dentry_upper(dentry))
			err = ovl_करो_copy_up(&ctx);
		अगर (!err && parent && !ovl_dentry_has_upper_alias(dentry))
			err = ovl_link_up(&ctx);
		अगर (!err && ovl_dentry_needs_data_copy_up_locked(dentry, flags))
			err = ovl_copy_up_meta_inode_data(&ctx);
		ovl_copy_up_end(dentry);
	पूर्ण
	करो_delayed_call(&करोne);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_copy_up_flags(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	स्थिर काष्ठा cred *old_cred;
	bool disconnected = (dentry->d_flags & DCACHE_DISCONNECTED);

	/*
	 * With NFS export, copy up can get called क्रम a disconnected non-dir.
	 * In this हाल, we will copy up lower inode to index dir without
	 * linking it to upper dir.
	 */
	अगर (WARN_ON(disconnected && d_is_dir(dentry)))
		वापस -EIO;

	old_cred = ovl_override_creds(dentry->d_sb);
	जबतक (!err) अणु
		काष्ठा dentry *next;
		काष्ठा dentry *parent = शून्य;

		अगर (ovl_alपढ़ोy_copied_up(dentry, flags))
			अवरोध;

		next = dget(dentry);
		/* find the topmost dentry not yet copied up */
		क्रम (; !disconnected;) अणु
			parent = dget_parent(next);

			अगर (ovl_dentry_upper(parent))
				अवरोध;

			dput(next);
			next = parent;
		पूर्ण

		err = ovl_copy_up_one(parent, next, flags);

		dput(parent);
		dput(next);
	पूर्ण
	revert_creds(old_cred);

	वापस err;
पूर्ण

अटल bool ovl_खोलो_need_copy_up(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	/* Copy up of disconnected dentry करोes not set upper alias */
	अगर (ovl_alपढ़ोy_copied_up(dentry, flags))
		वापस false;

	अगर (special_file(d_inode(dentry)->i_mode))
		वापस false;

	अगर (!ovl_खोलो_flags_need_copy_up(flags))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक ovl_maybe_copy_up(काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	पूर्णांक err = 0;

	अगर (ovl_खोलो_need_copy_up(dentry, flags)) अणु
		err = ovl_want_ग_लिखो(dentry);
		अगर (!err) अणु
			err = ovl_copy_up_flags(dentry, flags);
			ovl_drop_ग_लिखो(dentry);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ovl_copy_up_with_data(काष्ठा dentry *dentry)
अणु
	वापस ovl_copy_up_flags(dentry, O_WRONLY);
पूर्ण

पूर्णांक ovl_copy_up(काष्ठा dentry *dentry)
अणु
	वापस ovl_copy_up_flags(dentry, 0);
पूर्ण
