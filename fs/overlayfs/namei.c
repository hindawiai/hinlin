<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Novell Inc.
 * Copyright (C) 2016 Red Hat, Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/cred.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/namei.h>
#समावेश <linux/xattr.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/mount.h>
#समावेश <linux/exportfs.h>
#समावेश "overlayfs.h"

काष्ठा ovl_lookup_data अणु
	काष्ठा super_block *sb;
	काष्ठा qstr name;
	bool is_dir;
	bool opaque;
	bool stop;
	bool last;
	अक्षर *redirect;
	bool metacopy;
पूर्ण;

अटल पूर्णांक ovl_check_redirect(काष्ठा dentry *dentry, काष्ठा ovl_lookup_data *d,
			      माप_प्रकार prelen, स्थिर अक्षर *post)
अणु
	पूर्णांक res;
	अक्षर *buf;
	काष्ठा ovl_fs *ofs = OVL_FS(d->sb);

	buf = ovl_get_redirect_xattr(ofs, dentry, prelen + म_माप(post));
	अगर (IS_ERR_OR_शून्य(buf))
		वापस PTR_ERR(buf);

	अगर (buf[0] == '/') अणु
		/*
		 * One of the ancestor path elements in an असलolute path
		 * lookup in ovl_lookup_layer() could have been opaque and
		 * that will stop further lookup in lower layers (d->stop=true)
		 * But we have found an असलolute redirect in decendant path
		 * element and that should क्रमce जारी lookup in lower
		 * layers (reset d->stop).
		 */
		d->stop = false;
	पूर्ण अन्यथा अणु
		res = म_माप(buf) + 1;
		स_हटाओ(buf + prelen, buf, res);
		स_नकल(buf, d->name.name, prelen);
	पूर्ण

	म_जोड़ो(buf, post);
	kमुक्त(d->redirect);
	d->redirect = buf;
	d->name.name = d->redirect;
	d->name.len = म_माप(d->redirect);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_acceptable(व्योम *ctx, काष्ठा dentry *dentry)
अणु
	/*
	 * A non-dir origin may be disconnected, which is fine, because
	 * we only need it क्रम its unique inode number.
	 */
	अगर (!d_is_dir(dentry))
		वापस 1;

	/* Don't decode a deleted empty directory */
	अगर (d_unhashed(dentry))
		वापस 0;

	/* Check अगर directory beदीर्घs to the layer we are decoding from */
	वापस is_subdir(dentry, ((काष्ठा vfsmount *)ctx)->mnt_root);
पूर्ण

/*
 * Check validity of an overlay file handle buffer.
 *
 * Return 0 क्रम a valid file handle.
 * Return -ENODATA क्रम "origin unknown".
 * Return <0 क्रम an invalid file handle.
 */
पूर्णांक ovl_check_fb_len(काष्ठा ovl_fb *fb, पूर्णांक fb_len)
अणु
	अगर (fb_len < माप(काष्ठा ovl_fb) || fb_len < fb->len)
		वापस -EINVAL;

	अगर (fb->magic != OVL_FH_MAGIC)
		वापस -EINVAL;

	/* Treat larger version and unknown flags as "origin unknown" */
	अगर (fb->version > OVL_FH_VERSION || fb->flags & ~OVL_FH_FLAG_ALL)
		वापस -ENODATA;

	/* Treat endianness mismatch as "origin unknown" */
	अगर (!(fb->flags & OVL_FH_FLAG_ANY_ENDIAN) &&
	    (fb->flags & OVL_FH_FLAG_BIG_ENDIAN) != OVL_FH_FLAG_CPU_ENDIAN)
		वापस -ENODATA;

	वापस 0;
पूर्ण

अटल काष्ठा ovl_fh *ovl_get_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
				 क्रमागत ovl_xattr ox)
अणु
	पूर्णांक res, err;
	काष्ठा ovl_fh *fh = शून्य;

	res = ovl_करो_getxattr(ofs, dentry, ox, शून्य, 0);
	अगर (res < 0) अणु
		अगर (res == -ENODATA || res == -EOPNOTSUPP)
			वापस शून्य;
		जाओ fail;
	पूर्ण
	/* Zero size value means "copied up but origin unknown" */
	अगर (res == 0)
		वापस शून्य;

	fh = kzalloc(res + OVL_FH_WIRE_OFFSET, GFP_KERNEL);
	अगर (!fh)
		वापस ERR_PTR(-ENOMEM);

	res = ovl_करो_getxattr(ofs, dentry, ox, fh->buf, res);
	अगर (res < 0)
		जाओ fail;

	err = ovl_check_fb_len(&fh->fb, res);
	अगर (err < 0) अणु
		अगर (err == -ENODATA)
			जाओ out;
		जाओ invalid;
	पूर्ण

	वापस fh;

out:
	kमुक्त(fh);
	वापस शून्य;

fail:
	pr_warn_ratelimited("failed to get origin (%i)\n", res);
	जाओ out;
invalid:
	pr_warn_ratelimited("invalid origin (%*phN)\n", res, fh);
	जाओ out;
पूर्ण

काष्ठा dentry *ovl_decode_real_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh,
				  काष्ठा vfsmount *mnt, bool connected)
अणु
	काष्ठा dentry *real;
	पूर्णांक bytes;

	अगर (!capable(CAP_DAC_READ_SEARCH))
		वापस शून्य;

	/*
	 * Make sure that the stored uuid matches the uuid of the lower
	 * layer where file handle will be decoded.
	 * In हाल of uuid=off option just make sure that stored uuid is null.
	 */
	अगर (ofs->config.uuid ? !uuid_equal(&fh->fb.uuid, &mnt->mnt_sb->s_uuid) :
			      !uuid_is_null(&fh->fb.uuid))
		वापस शून्य;

	bytes = (fh->fb.len - दुरत्व(काष्ठा ovl_fb, fid));
	real = exportfs_decode_fh(mnt, (काष्ठा fid *)fh->fb.fid,
				  bytes >> 2, (पूर्णांक)fh->fb.type,
				  connected ? ovl_acceptable : शून्य, mnt);
	अगर (IS_ERR(real)) अणु
		/*
		 * Treat stale file handle to lower file as "origin unknown".
		 * upper file handle could become stale when upper file is
		 * unlinked and this inक्रमmation is needed to handle stale
		 * index entries correctly.
		 */
		अगर (real == ERR_PTR(-ESTALE) &&
		    !(fh->fb.flags & OVL_FH_FLAG_PATH_UPPER))
			real = शून्य;
		वापस real;
	पूर्ण

	अगर (ovl_dentry_weird(real)) अणु
		dput(real);
		वापस शून्य;
	पूर्ण

	वापस real;
पूर्ण

अटल bool ovl_is_opaquedir(काष्ठा super_block *sb, काष्ठा dentry *dentry)
अणु
	वापस ovl_check_dir_xattr(sb, dentry, OVL_XATTR_OPAQUE);
पूर्ण

अटल काष्ठा dentry *ovl_lookup_positive_unlocked(स्थिर अक्षर *name,
						   काष्ठा dentry *base, पूर्णांक len,
						   bool drop_negative)
अणु
	काष्ठा dentry *ret = lookup_one_len_unlocked(name, base, len);

	अगर (!IS_ERR(ret) && d_flags_negative(smp_load_acquire(&ret->d_flags))) अणु
		अगर (drop_negative && ret->d_lockref.count == 1) अणु
			spin_lock(&ret->d_lock);
			/* Recheck condition under lock */
			अगर (d_is_negative(ret) && ret->d_lockref.count == 1)
				__d_drop(ret);
			spin_unlock(&ret->d_lock);
		पूर्ण
		dput(ret);
		ret = ERR_PTR(-ENOENT);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ovl_lookup_single(काष्ठा dentry *base, काष्ठा ovl_lookup_data *d,
			     स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen,
			     माप_प्रकार prelen, स्थिर अक्षर *post,
			     काष्ठा dentry **ret, bool drop_negative)
अणु
	काष्ठा dentry *this;
	पूर्णांक err;
	bool last_element = !post[0];

	this = ovl_lookup_positive_unlocked(name, base, namelen, drop_negative);
	अगर (IS_ERR(this)) अणु
		err = PTR_ERR(this);
		this = शून्य;
		अगर (err == -ENOENT || err == -ENAMETOOLONG)
			जाओ out;
		जाओ out_err;
	पूर्ण

	अगर (ovl_dentry_weird(this)) अणु
		/* Don't support traversing स्वतःmounts and other weirdness */
		err = -EREMOTE;
		जाओ out_err;
	पूर्ण
	अगर (ovl_is_whiteout(this)) अणु
		d->stop = d->opaque = true;
		जाओ put_and_out;
	पूर्ण
	/*
	 * This dentry should be a regular file अगर previous layer lookup
	 * found a metacopy dentry.
	 */
	अगर (last_element && d->metacopy && !d_is_reg(this)) अणु
		d->stop = true;
		जाओ put_and_out;
	पूर्ण
	अगर (!d_can_lookup(this)) अणु
		अगर (d->is_dir || !last_element) अणु
			d->stop = true;
			जाओ put_and_out;
		पूर्ण
		err = ovl_check_metacopy_xattr(OVL_FS(d->sb), this);
		अगर (err < 0)
			जाओ out_err;

		d->metacopy = err;
		d->stop = !d->metacopy;
		अगर (!d->metacopy || d->last)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (ovl_lookup_trap_inode(d->sb, this)) अणु
			/* Caught in a trap of overlapping layers */
			err = -ELOOP;
			जाओ out_err;
		पूर्ण

		अगर (last_element)
			d->is_dir = true;
		अगर (d->last)
			जाओ out;

		अगर (ovl_is_opaquedir(d->sb, this)) अणु
			d->stop = true;
			अगर (last_element)
				d->opaque = true;
			जाओ out;
		पूर्ण
	पूर्ण
	err = ovl_check_redirect(this, d, prelen, post);
	अगर (err)
		जाओ out_err;
out:
	*ret = this;
	वापस 0;

put_and_out:
	dput(this);
	this = शून्य;
	जाओ out;

out_err:
	dput(this);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_lookup_layer(काष्ठा dentry *base, काष्ठा ovl_lookup_data *d,
			    काष्ठा dentry **ret, bool drop_negative)
अणु
	/* Counting करोwn from the end, since the prefix can change */
	माप_प्रकार rem = d->name.len - 1;
	काष्ठा dentry *dentry = शून्य;
	पूर्णांक err;

	अगर (d->name.name[0] != '/')
		वापस ovl_lookup_single(base, d, d->name.name, d->name.len,
					 0, "", ret, drop_negative);

	जबतक (!IS_ERR_OR_शून्य(base) && d_can_lookup(base)) अणु
		स्थिर अक्षर *s = d->name.name + d->name.len - rem;
		स्थिर अक्षर *next = म_अक्षरnul(s, '/');
		माप_प्रकार thislen = next - s;
		bool end = !next[0];

		/* Verअगरy we did not go off the rails */
		अगर (WARN_ON(s[-1] != '/'))
			वापस -EIO;

		err = ovl_lookup_single(base, d, s, thislen,
					d->name.len - rem, next, &base,
					drop_negative);
		dput(dentry);
		अगर (err)
			वापस err;
		dentry = base;
		अगर (end)
			अवरोध;

		rem -= thislen + 1;

		अगर (WARN_ON(rem >= d->name.len))
			वापस -EIO;
	पूर्ण
	*ret = dentry;
	वापस 0;
पूर्ण


पूर्णांक ovl_check_origin_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh, bool connected,
			काष्ठा dentry *upperdentry, काष्ठा ovl_path **stackp)
अणु
	काष्ठा dentry *origin = शून्य;
	पूर्णांक i;

	क्रम (i = 1; i < ofs->numlayer; i++) अणु
		/*
		 * If lower fs uuid is not unique among lower fs we cannot match
		 * fh->uuid to layer.
		 */
		अगर (ofs->layers[i].fsid &&
		    ofs->layers[i].fs->bad_uuid)
			जारी;

		origin = ovl_decode_real_fh(ofs, fh, ofs->layers[i].mnt,
					    connected);
		अगर (origin)
			अवरोध;
	पूर्ण

	अगर (!origin)
		वापस -ESTALE;
	अन्यथा अगर (IS_ERR(origin))
		वापस PTR_ERR(origin);

	अगर (upperdentry && !ovl_is_whiteout(upperdentry) &&
	    inode_wrong_type(d_inode(upperdentry), d_inode(origin)->i_mode))
		जाओ invalid;

	अगर (!*stackp)
		*stackp = kदो_स्मृति(माप(काष्ठा ovl_path), GFP_KERNEL);
	अगर (!*stackp) अणु
		dput(origin);
		वापस -ENOMEM;
	पूर्ण
	**stackp = (काष्ठा ovl_path)अणु
		.dentry = origin,
		.layer = &ofs->layers[i]
	पूर्ण;

	वापस 0;

invalid:
	pr_warn_ratelimited("invalid origin (%pd2, ftype=%x, origin ftype=%x).\n",
			    upperdentry, d_inode(upperdentry)->i_mode & S_IFMT,
			    d_inode(origin)->i_mode & S_IFMT);
	dput(origin);
	वापस -EIO;
पूर्ण

अटल पूर्णांक ovl_check_origin(काष्ठा ovl_fs *ofs, काष्ठा dentry *upperdentry,
			    काष्ठा ovl_path **stackp)
अणु
	काष्ठा ovl_fh *fh = ovl_get_fh(ofs, upperdentry, OVL_XATTR_ORIGIN);
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(fh))
		वापस PTR_ERR(fh);

	err = ovl_check_origin_fh(ofs, fh, false, upperdentry, stackp);
	kमुक्त(fh);

	अगर (err) अणु
		अगर (err == -ESTALE)
			वापस 0;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Verअगरy that @fh matches the file handle stored in xattr @name.
 * Return 0 on match, -ESTALE on mismatch, < 0 on error.
 */
अटल पूर्णांक ovl_verअगरy_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
			 क्रमागत ovl_xattr ox, स्थिर काष्ठा ovl_fh *fh)
अणु
	काष्ठा ovl_fh *ofh = ovl_get_fh(ofs, dentry, ox);
	पूर्णांक err = 0;

	अगर (!ofh)
		वापस -ENODATA;

	अगर (IS_ERR(ofh))
		वापस PTR_ERR(ofh);

	अगर (fh->fb.len != ofh->fb.len || स_भेद(&fh->fb, &ofh->fb, fh->fb.len))
		err = -ESTALE;

	kमुक्त(ofh);
	वापस err;
पूर्ण

/*
 * Verअगरy that @real dentry matches the file handle stored in xattr @name.
 *
 * If @set is true and there is no stored file handle, encode @real and store
 * file handle in xattr @name.
 *
 * Return 0 on match, -ESTALE on mismatch, -ENODATA on no xattr, < 0 on error.
 */
पूर्णांक ovl_verअगरy_set_fh(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
		      क्रमागत ovl_xattr ox, काष्ठा dentry *real, bool is_upper,
		      bool set)
अणु
	काष्ठा inode *inode;
	काष्ठा ovl_fh *fh;
	पूर्णांक err;

	fh = ovl_encode_real_fh(ofs, real, is_upper);
	err = PTR_ERR(fh);
	अगर (IS_ERR(fh)) अणु
		fh = शून्य;
		जाओ fail;
	पूर्ण

	err = ovl_verअगरy_fh(ofs, dentry, ox, fh);
	अगर (set && err == -ENODATA)
		err = ovl_करो_setxattr(ofs, dentry, ox, fh->buf, fh->fb.len);
	अगर (err)
		जाओ fail;

out:
	kमुक्त(fh);
	वापस err;

fail:
	inode = d_inode(real);
	pr_warn_ratelimited("failed to verify %s (%pd2, ino=%lu, err=%i)\n",
			    is_upper ? "upper" : "origin", real,
			    inode ? inode->i_ino : 0, err);
	जाओ out;
पूर्ण

/* Get upper dentry from index */
काष्ठा dentry *ovl_index_upper(काष्ठा ovl_fs *ofs, काष्ठा dentry *index)
अणु
	काष्ठा ovl_fh *fh;
	काष्ठा dentry *upper;

	अगर (!d_is_dir(index))
		वापस dget(index);

	fh = ovl_get_fh(ofs, index, OVL_XATTR_UPPER);
	अगर (IS_ERR_OR_शून्य(fh))
		वापस ERR_CAST(fh);

	upper = ovl_decode_real_fh(ofs, fh, ovl_upper_mnt(ofs), true);
	kमुक्त(fh);

	अगर (IS_ERR_OR_शून्य(upper))
		वापस upper ?: ERR_PTR(-ESTALE);

	अगर (!d_is_dir(upper)) अणु
		pr_warn_ratelimited("invalid index upper (%pd2, upper=%pd2).\n",
				    index, upper);
		dput(upper);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस upper;
पूर्ण

/*
 * Verअगरy that an index entry name matches the origin file handle stored in
 * OVL_XATTR_ORIGIN and that origin file handle can be decoded to lower path.
 * Return 0 on match, -ESTALE on mismatch or stale origin, < 0 on error.
 */
पूर्णांक ovl_verअगरy_index(काष्ठा ovl_fs *ofs, काष्ठा dentry *index)
अणु
	काष्ठा ovl_fh *fh = शून्य;
	माप_प्रकार len;
	काष्ठा ovl_path origin = अणु पूर्ण;
	काष्ठा ovl_path *stack = &origin;
	काष्ठा dentry *upper = शून्य;
	पूर्णांक err;

	अगर (!d_inode(index))
		वापस 0;

	err = -EINVAL;
	अगर (index->d_name.len < माप(काष्ठा ovl_fb)*2)
		जाओ fail;

	err = -ENOMEM;
	len = index->d_name.len / 2;
	fh = kzalloc(len + OVL_FH_WIRE_OFFSET, GFP_KERNEL);
	अगर (!fh)
		जाओ fail;

	err = -EINVAL;
	अगर (hex2bin(fh->buf, index->d_name.name, len))
		जाओ fail;

	err = ovl_check_fb_len(&fh->fb, len);
	अगर (err)
		जाओ fail;

	/*
	 * Whiteout index entries are used as an indication that an exported
	 * overlay file handle should be treated as stale (i.e. after unlink
	 * of the overlay inode). These entries contain no origin xattr.
	 */
	अगर (ovl_is_whiteout(index))
		जाओ out;

	/*
	 * Verअगरying directory index entries are not stale is expensive, so
	 * only verअगरy stale dir index अगर NFS export is enabled.
	 */
	अगर (d_is_dir(index) && !ofs->config.nfs_export)
		जाओ out;

	/*
	 * Directory index entries should have 'upper' xattr poपूर्णांकing to the
	 * real upper dir. Non-dir index entries are hardlinks to the upper
	 * real inode. For non-dir index, we can पढ़ो the copy up origin xattr
	 * directly from the index dentry, but क्रम dir index we first need to
	 * decode the upper directory.
	 */
	upper = ovl_index_upper(ofs, index);
	अगर (IS_ERR_OR_शून्य(upper)) अणु
		err = PTR_ERR(upper);
		/*
		 * Directory index entries with no 'upper' xattr need to be
		 * हटाओd. When dir index entry has a stale 'upper' xattr,
		 * we assume that upper dir was हटाओd and we treat the dir
		 * index as orphan entry that needs to be whited out.
		 */
		अगर (err == -ESTALE)
			जाओ orphan;
		अन्यथा अगर (!err)
			err = -ESTALE;
		जाओ fail;
	पूर्ण

	err = ovl_verअगरy_fh(ofs, upper, OVL_XATTR_ORIGIN, fh);
	dput(upper);
	अगर (err)
		जाओ fail;

	/* Check अगर non-dir index is orphan and करोn't warn beक्रमe cleaning it */
	अगर (!d_is_dir(index) && d_inode(index)->i_nlink == 1) अणु
		err = ovl_check_origin_fh(ofs, fh, false, index, &stack);
		अगर (err)
			जाओ fail;

		अगर (ovl_get_nlink(ofs, origin.dentry, index, 0) == 0)
			जाओ orphan;
	पूर्ण

out:
	dput(origin.dentry);
	kमुक्त(fh);
	वापस err;

fail:
	pr_warn_ratelimited("failed to verify index (%pd2, ftype=%x, err=%i)\n",
			    index, d_inode(index)->i_mode & S_IFMT, err);
	जाओ out;

orphan:
	pr_warn_ratelimited("orphan index entry (%pd2, ftype=%x, nlink=%u)\n",
			    index, d_inode(index)->i_mode & S_IFMT,
			    d_inode(index)->i_nlink);
	err = -ENOENT;
	जाओ out;
पूर्ण

अटल पूर्णांक ovl_get_index_name_fh(काष्ठा ovl_fh *fh, काष्ठा qstr *name)
अणु
	अक्षर *n, *s;

	n = kसुस्मृति(fh->fb.len, 2, GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	s  = bin2hex(n, fh->buf, fh->fb.len);
	*name = (काष्ठा qstr) QSTR_INIT(n, s - n);

	वापस 0;

पूर्ण

/*
 * Lookup in indexdir क्रम the index entry of a lower real inode or a copy up
 * origin inode. The index entry name is the hex representation of the lower
 * inode file handle.
 *
 * If the index dentry in negative, then either no lower aliases have been
 * copied up yet, or aliases have been copied up in older kernels and are
 * not indexed.
 *
 * If the index dentry क्रम a copy up origin inode is positive, but poपूर्णांकs
 * to an inode dअगरferent than the upper inode, then either the upper inode
 * has been copied up and not indexed or it was indexed, but since then
 * index dir was cleared. Either way, that index cannot be used to indentअगरy
 * the overlay inode.
 */
पूर्णांक ovl_get_index_name(काष्ठा ovl_fs *ofs, काष्ठा dentry *origin,
		       काष्ठा qstr *name)
अणु
	काष्ठा ovl_fh *fh;
	पूर्णांक err;

	fh = ovl_encode_real_fh(ofs, origin, false);
	अगर (IS_ERR(fh))
		वापस PTR_ERR(fh);

	err = ovl_get_index_name_fh(fh, name);

	kमुक्त(fh);
	वापस err;
पूर्ण

/* Lookup index by file handle क्रम NFS export */
काष्ठा dentry *ovl_get_index_fh(काष्ठा ovl_fs *ofs, काष्ठा ovl_fh *fh)
अणु
	काष्ठा dentry *index;
	काष्ठा qstr name;
	पूर्णांक err;

	err = ovl_get_index_name_fh(fh, &name);
	अगर (err)
		वापस ERR_PTR(err);

	index = lookup_positive_unlocked(name.name, ofs->indexdir, name.len);
	kमुक्त(name.name);
	अगर (IS_ERR(index)) अणु
		अगर (PTR_ERR(index) == -ENOENT)
			index = शून्य;
		वापस index;
	पूर्ण

	अगर (ovl_is_whiteout(index))
		err = -ESTALE;
	अन्यथा अगर (ovl_dentry_weird(index))
		err = -EIO;
	अन्यथा
		वापस index;

	dput(index);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा dentry *ovl_lookup_index(काष्ठा ovl_fs *ofs, काष्ठा dentry *upper,
				काष्ठा dentry *origin, bool verअगरy)
अणु
	काष्ठा dentry *index;
	काष्ठा inode *inode;
	काष्ठा qstr name;
	bool is_dir = d_is_dir(origin);
	पूर्णांक err;

	err = ovl_get_index_name(ofs, origin, &name);
	अगर (err)
		वापस ERR_PTR(err);

	index = lookup_positive_unlocked(name.name, ofs->indexdir, name.len);
	अगर (IS_ERR(index)) अणु
		err = PTR_ERR(index);
		अगर (err == -ENOENT) अणु
			index = शून्य;
			जाओ out;
		पूर्ण
		pr_warn_ratelimited("failed inode index lookup (ino=%lu, key=%.*s, err=%i);\n"
				    "overlayfs: mount with '-o index=off' to disable inodes index.\n",
				    d_inode(origin)->i_ino, name.len, name.name,
				    err);
		जाओ out;
	पूर्ण

	inode = d_inode(index);
	अगर (ovl_is_whiteout(index) && !verअगरy) अणु
		/*
		 * When index lookup is called with !verअगरy क्रम decoding an
		 * overlay file handle, a whiteout index implies that decode
		 * should treat file handle as stale and no need to prपूर्णांक a
		 * warning about it.
		 */
		dput(index);
		index = ERR_PTR(-ESTALE);
		जाओ out;
	पूर्ण अन्यथा अगर (ovl_dentry_weird(index) || ovl_is_whiteout(index) ||
		   inode_wrong_type(inode, d_inode(origin)->i_mode)) अणु
		/*
		 * Index should always be of the same file type as origin
		 * except क्रम the हाल of a whiteout index. A whiteout
		 * index should only exist अगर all lower aliases have been
		 * unlinked, which means that finding a lower origin on lookup
		 * whose index is a whiteout should be treated as an error.
		 */
		pr_warn_ratelimited("bad index found (index=%pd2, ftype=%x, origin ftype=%x).\n",
				    index, d_inode(index)->i_mode & S_IFMT,
				    d_inode(origin)->i_mode & S_IFMT);
		जाओ fail;
	पूर्ण अन्यथा अगर (is_dir && verअगरy) अणु
		अगर (!upper) अणु
			pr_warn_ratelimited("suspected uncovered redirected dir found (origin=%pd2, index=%pd2).\n",
					    origin, index);
			जाओ fail;
		पूर्ण

		/* Verअगरy that dir index 'upper' xattr poपूर्णांकs to upper dir */
		err = ovl_verअगरy_upper(ofs, index, upper, false);
		अगर (err) अणु
			अगर (err == -ESTALE) अणु
				pr_warn_ratelimited("suspected multiply redirected dir found (upper=%pd2, origin=%pd2, index=%pd2).\n",
						    upper, origin, index);
			पूर्ण
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अगर (upper && d_inode(upper) != inode) अणु
		जाओ out_dput;
	पूर्ण
out:
	kमुक्त(name.name);
	वापस index;

out_dput:
	dput(index);
	index = शून्य;
	जाओ out;

fail:
	dput(index);
	index = ERR_PTR(-EIO);
	जाओ out;
पूर्ण

/*
 * Returns next layer in stack starting from top.
 * Returns -1 अगर this is the last layer.
 */
पूर्णांक ovl_path_next(पूर्णांक idx, काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	BUG_ON(idx < 0);
	अगर (idx == 0) अणु
		ovl_path_upper(dentry, path);
		अगर (path->dentry)
			वापस oe->numlower ? 1 : -1;
		idx++;
	पूर्ण
	BUG_ON(idx > oe->numlower);
	path->dentry = oe->lowerstack[idx - 1].dentry;
	path->mnt = oe->lowerstack[idx - 1].layer->mnt;

	वापस (idx < oe->numlower) ? idx + 1 : -1;
पूर्ण

/* Fix missing 'origin' xattr */
अटल पूर्णांक ovl_fix_origin(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
			  काष्ठा dentry *lower, काष्ठा dentry *upper)
अणु
	पूर्णांक err;

	अगर (ovl_check_origin_xattr(ofs, upper))
		वापस 0;

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		वापस err;

	err = ovl_set_origin(ofs, dentry, lower, upper);
	अगर (!err)
		err = ovl_set_impure(dentry->d_parent, upper->d_parent);

	ovl_drop_ग_लिखो(dentry);
	वापस err;
पूर्ण

काष्ठा dentry *ovl_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ovl_entry *oe;
	स्थिर काष्ठा cred *old_cred;
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;
	काष्ठा ovl_entry *poe = dentry->d_parent->d_fsdata;
	काष्ठा ovl_entry *roe = dentry->d_sb->s_root->d_fsdata;
	काष्ठा ovl_path *stack = शून्य, *origin_path = शून्य;
	काष्ठा dentry *upperdir, *upperdentry = शून्य;
	काष्ठा dentry *origin = शून्य;
	काष्ठा dentry *index = शून्य;
	अचिन्हित पूर्णांक ctr = 0;
	काष्ठा inode *inode = शून्य;
	bool upperopaque = false;
	अक्षर *upperredirect = शून्य;
	काष्ठा dentry *this;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	bool uppermetacopy = false;
	काष्ठा ovl_lookup_data d = अणु
		.sb = dentry->d_sb,
		.name = dentry->d_name,
		.is_dir = false,
		.opaque = false,
		.stop = false,
		.last = ofs->config.redirect_follow ? false : !poe->numlower,
		.redirect = शून्य,
		.metacopy = false,
	पूर्ण;

	अगर (dentry->d_name.len > ofs->namelen)
		वापस ERR_PTR(-ENAMETOOLONG);

	old_cred = ovl_override_creds(dentry->d_sb);
	upperdir = ovl_dentry_upper(dentry->d_parent);
	अगर (upperdir) अणु
		err = ovl_lookup_layer(upperdir, &d, &upperdentry, true);
		अगर (err)
			जाओ out;

		अगर (upperdentry && upperdentry->d_flags & DCACHE_OP_REAL) अणु
			dput(upperdentry);
			err = -EREMOTE;
			जाओ out;
		पूर्ण
		अगर (upperdentry && !d.is_dir) अणु
			/*
			 * Lookup copy up origin by decoding origin file handle.
			 * We may get a disconnected dentry, which is fine,
			 * because we only need to hold the origin inode in
			 * cache and use its inode number.  We may even get a
			 * connected dentry, that is not under any of the lower
			 * layers root.  That is also fine क्रम using it's inode
			 * number - it's the same as अगर we held a reference
			 * to a dentry in lower layer that was moved under us.
			 */
			err = ovl_check_origin(ofs, upperdentry, &origin_path);
			अगर (err)
				जाओ out_put_upper;

			अगर (d.metacopy)
				uppermetacopy = true;
		पूर्ण

		अगर (d.redirect) अणु
			err = -ENOMEM;
			upperredirect = kstrdup(d.redirect, GFP_KERNEL);
			अगर (!upperredirect)
				जाओ out_put_upper;
			अगर (d.redirect[0] == '/')
				poe = roe;
		पूर्ण
		upperopaque = d.opaque;
	पूर्ण

	अगर (!d.stop && poe->numlower) अणु
		err = -ENOMEM;
		stack = kसुस्मृति(ofs->numlayer - 1, माप(काष्ठा ovl_path),
				GFP_KERNEL);
		अगर (!stack)
			जाओ out_put_upper;
	पूर्ण

	क्रम (i = 0; !d.stop && i < poe->numlower; i++) अणु
		काष्ठा ovl_path lower = poe->lowerstack[i];

		अगर (!ofs->config.redirect_follow)
			d.last = i == poe->numlower - 1;
		अन्यथा
			d.last = lower.layer->idx == roe->numlower;

		err = ovl_lookup_layer(lower.dentry, &d, &this, false);
		अगर (err)
			जाओ out_put;

		अगर (!this)
			जारी;

		अगर ((uppermetacopy || d.metacopy) && !ofs->config.metacopy) अणु
			dput(this);
			err = -EPERM;
			pr_warn_ratelimited("refusing to follow metacopy origin for (%pd2)\n", dentry);
			जाओ out_put;
		पूर्ण

		/*
		 * If no origin fh is stored in upper of a merge dir, store fh
		 * of lower dir and set upper parent "impure".
		 */
		अगर (upperdentry && !ctr && !ofs->noxattr && d.is_dir) अणु
			err = ovl_fix_origin(ofs, dentry, this, upperdentry);
			अगर (err) अणु
				dput(this);
				जाओ out_put;
			पूर्ण
		पूर्ण

		/*
		 * When "verify_lower" feature is enabled, करो not merge with a
		 * lower dir that करोes not match a stored origin xattr. In any
		 * हाल, only verअगरied origin is used क्रम index lookup.
		 *
		 * For non-dir dentry, अगर index=on, then ensure origin
		 * matches the dentry found using path based lookup,
		 * otherwise error out.
		 */
		अगर (upperdentry && !ctr &&
		    ((d.is_dir && ovl_verअगरy_lower(dentry->d_sb)) ||
		     (!d.is_dir && ofs->config.index && origin_path))) अणु
			err = ovl_verअगरy_origin(ofs, upperdentry, this, false);
			अगर (err) अणु
				dput(this);
				अगर (d.is_dir)
					अवरोध;
				जाओ out_put;
			पूर्ण
			origin = this;
		पूर्ण

		अगर (d.metacopy && ctr) अणु
			/*
			 * Do not store पूर्णांकermediate metacopy dentries in
			 * lower chain, except top most lower metacopy dentry.
			 * Continue the loop so that अगर there is an असलolute
			 * redirect on this dentry, poe can be reset to roe.
			 */
			dput(this);
			this = शून्य;
		पूर्ण अन्यथा अणु
			stack[ctr].dentry = this;
			stack[ctr].layer = lower.layer;
			ctr++;
		पूर्ण

		/*
		 * Following redirects can have security consequences: it's like
		 * a symlink पूर्णांकo the lower layer without the permission checks.
		 * This is only a problem अगर the upper layer is untrusted (e.g
		 * comes from an USB drive).  This can allow a non-पढ़ोable file
		 * or directory to become पढ़ोable.
		 *
		 * Only following redirects when redirects are enabled disables
		 * this attack vector when not necessary.
		 */
		err = -EPERM;
		अगर (d.redirect && !ofs->config.redirect_follow) अणु
			pr_warn_ratelimited("refusing to follow redirect for (%pd2)\n",
					    dentry);
			जाओ out_put;
		पूर्ण

		अगर (d.stop)
			अवरोध;

		अगर (d.redirect && d.redirect[0] == '/' && poe != roe) अणु
			poe = roe;
			/* Find the current layer on the root dentry */
			i = lower.layer->idx - 1;
		पूर्ण
	पूर्ण

	/*
	 * For regular non-metacopy upper dentries, there is no lower
	 * path based lookup, hence ctr will be zero. If a dentry is found
	 * using ORIGIN xattr on upper, install it in stack.
	 *
	 * For metacopy dentry, path based lookup will find lower dentries.
	 * Just make sure a corresponding data dentry has been found.
	 */
	अगर (d.metacopy || (uppermetacopy && !ctr)) अणु
		pr_warn_ratelimited("metacopy with no lower data found - abort lookup (%pd2)\n",
				    dentry);
		err = -EIO;
		जाओ out_put;
	पूर्ण अन्यथा अगर (!d.is_dir && upperdentry && !ctr && origin_path) अणु
		अगर (WARN_ON(stack != शून्य)) अणु
			err = -EIO;
			जाओ out_put;
		पूर्ण
		stack = origin_path;
		ctr = 1;
		origin = origin_path->dentry;
		origin_path = शून्य;
	पूर्ण

	/*
	 * Always lookup index अगर there is no-upperdentry.
	 *
	 * For the हाल of upperdentry, we have set origin by now अगर it
	 * needed to be set. There are basically three हालs.
	 *
	 * For directories, lookup index by lower inode and verअगरy it matches
	 * upper inode. We only trust dir index अगर we verअगरied that lower dir
	 * matches origin, otherwise dir index entries may be inconsistent
	 * and we ignore them.
	 *
	 * For regular upper, we alपढ़ोy set origin अगर upper had ORIGIN
	 * xattr. There is no verअगरication though as there is no path
	 * based dentry lookup in lower in this हाल.
	 *
	 * For metacopy upper, we set a verअगरied origin alपढ़ोy अगर index
	 * is enabled and अगर upper had an ORIGIN xattr.
	 *
	 */
	अगर (!upperdentry && ctr)
		origin = stack[0].dentry;

	अगर (origin && ovl_indexdir(dentry->d_sb) &&
	    (!d.is_dir || ovl_index_all(dentry->d_sb))) अणु
		index = ovl_lookup_index(ofs, upperdentry, origin, true);
		अगर (IS_ERR(index)) अणु
			err = PTR_ERR(index);
			index = शून्य;
			जाओ out_put;
		पूर्ण
	पूर्ण

	oe = ovl_alloc_entry(ctr);
	err = -ENOMEM;
	अगर (!oe)
		जाओ out_put;

	स_नकल(oe->lowerstack, stack, माप(काष्ठा ovl_path) * ctr);
	dentry->d_fsdata = oe;

	अगर (upperopaque)
		ovl_dentry_set_opaque(dentry);

	अगर (upperdentry)
		ovl_dentry_set_upper_alias(dentry);
	अन्यथा अगर (index) अणु
		upperdentry = dget(index);
		upperredirect = ovl_get_redirect_xattr(ofs, upperdentry, 0);
		अगर (IS_ERR(upperredirect)) अणु
			err = PTR_ERR(upperredirect);
			upperredirect = शून्य;
			जाओ out_मुक्त_oe;
		पूर्ण
		err = ovl_check_metacopy_xattr(ofs, upperdentry);
		अगर (err < 0)
			जाओ out_मुक्त_oe;
		uppermetacopy = err;
	पूर्ण

	अगर (upperdentry || ctr) अणु
		काष्ठा ovl_inode_params oip = अणु
			.upperdentry = upperdentry,
			.lowerpath = stack,
			.index = index,
			.numlower = ctr,
			.redirect = upperredirect,
			.lowerdata = (ctr > 1 && !d.is_dir) ?
				      stack[ctr - 1].dentry : शून्य,
		पूर्ण;

		inode = ovl_get_inode(dentry->d_sb, &oip);
		err = PTR_ERR(inode);
		अगर (IS_ERR(inode))
			जाओ out_मुक्त_oe;
		अगर (upperdentry && !uppermetacopy)
			ovl_set_flag(OVL_UPPERDATA, inode);
	पूर्ण

	ovl_dentry_update_reval(dentry, upperdentry,
			DCACHE_OP_REVALIDATE | DCACHE_OP_WEAK_REVALIDATE);

	revert_creds(old_cred);
	अगर (origin_path) अणु
		dput(origin_path->dentry);
		kमुक्त(origin_path);
	पूर्ण
	dput(index);
	kमुक्त(stack);
	kमुक्त(d.redirect);
	वापस d_splice_alias(inode, dentry);

out_मुक्त_oe:
	dentry->d_fsdata = शून्य;
	kमुक्त(oe);
out_put:
	dput(index);
	क्रम (i = 0; i < ctr; i++)
		dput(stack[i].dentry);
	kमुक्त(stack);
out_put_upper:
	अगर (origin_path) अणु
		dput(origin_path->dentry);
		kमुक्त(origin_path);
	पूर्ण
	dput(upperdentry);
	kमुक्त(upperredirect);
out:
	kमुक्त(d.redirect);
	revert_creds(old_cred);
	वापस ERR_PTR(err);
पूर्ण

bool ovl_lower_positive(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *poe = dentry->d_parent->d_fsdata;
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	स्थिर काष्ठा cred *old_cred;
	अचिन्हित पूर्णांक i;
	bool positive = false;
	bool करोne = false;

	/*
	 * If dentry is negative, then lower is positive अगरf this is a
	 * whiteout.
	 */
	अगर (!dentry->d_inode)
		वापस ovl_dentry_is_opaque(dentry);

	/* Negative upper -> positive lower */
	अगर (!ovl_dentry_upper(dentry))
		वापस true;

	old_cred = ovl_override_creds(dentry->d_sb);
	/* Positive upper -> have to look up lower to see whether it exists */
	क्रम (i = 0; !करोne && !positive && i < poe->numlower; i++) अणु
		काष्ठा dentry *this;
		काष्ठा dentry *lowerdir = poe->lowerstack[i].dentry;

		this = lookup_positive_unlocked(name->name, lowerdir,
					       name->len);
		अगर (IS_ERR(this)) अणु
			चयन (PTR_ERR(this)) अणु
			हाल -ENOENT:
			हाल -ENAMETOOLONG:
				अवरोध;

			शेष:
				/*
				 * Assume something is there, we just couldn't
				 * access it.
				 */
				positive = true;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			positive = !ovl_is_whiteout(this);
			करोne = true;
			dput(this);
		पूर्ण
	पूर्ण
	revert_creds(old_cred);

	वापस positive;
पूर्ण
