<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Overlayfs NFS export support.
 *
 * Amir Goldstein <amir73il@gmail.com>
 *
 * Copyright (C) 2017-2018 CTERA Networks. All Rights Reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/cred.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/xattr.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/ratelimit.h>
#समावेश "overlayfs.h"

अटल पूर्णांक ovl_encode_maybe_copy_up(काष्ठा dentry *dentry)
अणु
	पूर्णांक err;

	अगर (ovl_dentry_upper(dentry))
		वापस 0;

	err = ovl_want_ग_लिखो(dentry);
	अगर (!err) अणु
		err = ovl_copy_up(dentry);
		ovl_drop_ग_लिखो(dentry);
	पूर्ण

	अगर (err) अणु
		pr_warn_ratelimited("failed to copy up on encode (%pd2, err=%i)\n",
				    dentry, err);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Beक्रमe encoding a non-upper directory file handle from real layer N, we need
 * to check अगर it will be possible to reconnect an overlay dentry from the real
 * lower decoded dentry. This is करोne by following the overlay ancestry up to a
 * "layer N connected" ancestor and verअगरying that all parents aदीर्घ the way are
 * "layer N connectable". If an ancestor that is NOT "layer N connectable" is
 * found, we need to copy up an ancestor, which is "layer N connectable", thus
 * making that ancestor "layer N connected". For example:
 *
 * layer 1: /a
 * layer 2: /a/b/c
 *
 * The overlay dentry /a is NOT "layer 2 connectable", because अगर dir /a is
 * copied up and नामd, upper dir /a will be indexed by lower dir /a from
 * layer 1. The dir /a from layer 2 will never be indexed, so the algorithm (*)
 * in ovl_lookup_real_ancestor() will not be able to lookup a connected overlay
 * dentry from the connected lower dentry /a/b/c.
 *
 * To aव्योम this problem on decode समय, we need to copy up an ancestor of
 * /a/b/c, which is "layer 2 connectable", on encode समय. That ancestor is
 * /a/b. After copy up (and index) of /a/b, it will become "layer 2 connected"
 * and when the समय comes to decode the file handle from lower dentry /a/b/c,
 * ovl_lookup_real_ancestor() will find the indexed ancestor /a/b and decoding
 * a connected overlay dentry will be accomplished.
 *
 * (*) the algorithm in ovl_lookup_real_ancestor() can be improved to lookup an
 * entry /a in the lower layers above layer N and find the indexed dir /a from
 * layer 1. If that improvement is made, then the check क्रम "layer N connected"
 * will need to verअगरy there are no redirects in lower layers above N. In the
 * example above, /a will be "layer 2 connectable". However, अगर layer 2 dir /a
 * is a target of a layer 1 redirect, then /a will NOT be "layer 2 connectable":
 *
 * layer 1: /A (redirect = /a)
 * layer 2: /a/b/c
 */

/* Return the lowest layer क्रम encoding a connectable file handle */
अटल पूर्णांक ovl_connectable_layer(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = OVL_E(dentry);

	/* We can get overlay root from root of any layer */
	अगर (dentry == dentry->d_sb->s_root)
		वापस oe->numlower;

	/*
	 * If it's an unindexed merge dir, then it's not connectable with any
	 * lower layer
	 */
	अगर (ovl_dentry_upper(dentry) &&
	    !ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		वापस 0;

	/* We can get upper/overlay path from indexed/lower dentry */
	वापस oe->lowerstack[0].layer->idx;
पूर्ण

/*
 * @dentry is "connected" अगर all ancestors up to root or a "connected" ancestor
 * have the same uppermost lower layer as the origin's layer. We may need to
 * copy up a "connectable" ancestor to make it "connected". A "connected" dentry
 * cannot become non "connected", so cache positive result in dentry flags.
 *
 * Return the connected origin layer or < 0 on error.
 */
अटल पूर्णांक ovl_connect_layer(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *next, *parent = शून्य;
	पूर्णांक origin_layer;
	पूर्णांक err = 0;

	अगर (WARN_ON(dentry == dentry->d_sb->s_root) ||
	    WARN_ON(!ovl_dentry_lower(dentry)))
		वापस -EIO;

	origin_layer = OVL_E(dentry)->lowerstack[0].layer->idx;
	अगर (ovl_dentry_test_flag(OVL_E_CONNECTED, dentry))
		वापस origin_layer;

	/* Find the topmost origin layer connectable ancestor of @dentry */
	next = dget(dentry);
	क्रम (;;) अणु
		parent = dget_parent(next);
		अगर (WARN_ON(parent == next)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण

		/*
		 * If @parent is not origin layer connectable, then copy up
		 * @next which is origin layer connectable and we are करोne.
		 */
		अगर (ovl_connectable_layer(parent) < origin_layer) अणु
			err = ovl_encode_maybe_copy_up(next);
			अवरोध;
		पूर्ण

		/* If @parent is connected or indexed we are करोne */
		अगर (ovl_dentry_test_flag(OVL_E_CONNECTED, parent) ||
		    ovl_test_flag(OVL_INDEX, d_inode(parent)))
			अवरोध;

		dput(next);
		next = parent;
	पूर्ण

	dput(parent);
	dput(next);

	अगर (!err)
		ovl_dentry_set_flag(OVL_E_CONNECTED, dentry);

	वापस err ?: origin_layer;
पूर्ण

/*
 * We only need to encode origin अगर there is a chance that the same object was
 * encoded pre copy up and then we need to stay consistent with the same
 * encoding also after copy up. If non-pure upper is not indexed, then it was
 * copied up beक्रमe NFS export was enabled. In that हाल we करोn't need to worry
 * about staying consistent with pre copy up encoding and we encode an upper
 * file handle. Overlay root dentry is a निजी हाल of non-indexed upper.
 *
 * The following table summarizes the dअगरferent file handle encodings used क्रम
 * dअगरferent overlay object types:
 *
 *  Object type		| Encoding
 * --------------------------------
 *  Pure upper		| U
 *  Non-indexed upper	| U
 *  Indexed upper	| L (*)
 *  Non-upper		| L (*)
 *
 * U = upper file handle
 * L = lower file handle
 *
 * (*) Connecting an overlay dir from real lower dentry is not always
 * possible when there are redirects in lower layers and non-indexed merge dirs.
 * To mitigate those हाल, we may copy up the lower dir ancestor beक्रमe encode
 * a lower dir file handle.
 *
 * Return 0 क्रम upper file handle, > 0 क्रम lower file handle or < 0 on error.
 */
अटल पूर्णांक ovl_check_encode_origin(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;

	/* Upper file handle क्रम pure upper */
	अगर (!ovl_dentry_lower(dentry))
		वापस 0;

	/*
	 * Upper file handle क्रम non-indexed upper.
	 *
	 * Root is never indexed, so अगर there's an upper layer, encode upper क्रम
	 * root.
	 */
	अगर (ovl_dentry_upper(dentry) &&
	    !ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		वापस 0;

	/*
	 * Decoding a merge dir, whose origin's ancestor is under a redirected
	 * lower dir or under a non-indexed upper is not always possible.
	 * ovl_connect_layer() will try to make origin's layer "connected" by
	 * copying up a "connectable" ancestor.
	 */
	अगर (d_is_dir(dentry) && ovl_upper_mnt(ofs))
		वापस ovl_connect_layer(dentry);

	/* Lower file handle क्रम indexed and non-upper dir/non-dir */
	वापस 1;
पूर्ण

अटल पूर्णांक ovl_dentry_to_fid(काष्ठा ovl_fs *ofs, काष्ठा dentry *dentry,
			     u32 *fid, पूर्णांक buflen)
अणु
	काष्ठा ovl_fh *fh = शून्य;
	पूर्णांक err, enc_lower;
	पूर्णांक len;

	/*
	 * Check अगर we should encode a lower or upper file handle and maybe
	 * copy up an ancestor to make lower file handle connectable.
	 */
	err = enc_lower = ovl_check_encode_origin(dentry);
	अगर (enc_lower < 0)
		जाओ fail;

	/* Encode an upper or lower file handle */
	fh = ovl_encode_real_fh(ofs, enc_lower ? ovl_dentry_lower(dentry) :
				ovl_dentry_upper(dentry), !enc_lower);
	अगर (IS_ERR(fh))
		वापस PTR_ERR(fh);

	len = OVL_FH_LEN(fh);
	अगर (len <= buflen)
		स_नकल(fid, fh, len);
	err = len;

out:
	kमुक्त(fh);
	वापस err;

fail:
	pr_warn_ratelimited("failed to encode file handle (%pd2, err=%i)\n",
			    dentry, err);
	जाओ out;
पूर्ण

अटल पूर्णांक ovl_encode_fh(काष्ठा inode *inode, u32 *fid, पूर्णांक *max_len,
			 काष्ठा inode *parent)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(inode->i_sb);
	काष्ठा dentry *dentry;
	पूर्णांक bytes, buflen = *max_len << 2;

	/* TODO: encode connectable file handles */
	अगर (parent)
		वापस खाताID_INVALID;

	dentry = d_find_any_alias(inode);
	अगर (WARN_ON(!dentry))
		वापस खाताID_INVALID;

	bytes = ovl_dentry_to_fid(ofs, dentry, fid, buflen);
	dput(dentry);
	अगर (bytes <= 0)
		वापस खाताID_INVALID;

	*max_len = bytes >> 2;
	अगर (bytes > buflen)
		वापस खाताID_INVALID;

	वापस OVL_खाताID_V1;
पूर्ण

/*
 * Find or instantiate an overlay dentry from real dentries and index.
 */
अटल काष्ठा dentry *ovl_obtain_alias(काष्ठा super_block *sb,
				       काष्ठा dentry *upper_alias,
				       काष्ठा ovl_path *lowerpath,
				       काष्ठा dentry *index)
अणु
	काष्ठा dentry *lower = lowerpath ? lowerpath->dentry : शून्य;
	काष्ठा dentry *upper = upper_alias ?: index;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	काष्ठा ovl_entry *oe;
	काष्ठा ovl_inode_params oip = अणु
		.lowerpath = lowerpath,
		.index = index,
		.numlower = !!lower
	पूर्ण;

	/* We get overlay directory dentries with ovl_lookup_real() */
	अगर (d_is_dir(upper ?: lower))
		वापस ERR_PTR(-EIO);

	oip.upperdentry = dget(upper);
	inode = ovl_get_inode(sb, &oip);
	अगर (IS_ERR(inode)) अणु
		dput(upper);
		वापस ERR_CAST(inode);
	पूर्ण

	अगर (upper)
		ovl_set_flag(OVL_UPPERDATA, inode);

	dentry = d_find_any_alias(inode);
	अगर (dentry)
		जाओ out_iput;

	dentry = d_alloc_anon(inode->i_sb);
	अगर (unlikely(!dentry))
		जाओ nomem;
	oe = ovl_alloc_entry(lower ? 1 : 0);
	अगर (!oe)
		जाओ nomem;

	अगर (lower) अणु
		oe->lowerstack->dentry = dget(lower);
		oe->lowerstack->layer = lowerpath->layer;
	पूर्ण
	dentry->d_fsdata = oe;
	अगर (upper_alias)
		ovl_dentry_set_upper_alias(dentry);

	ovl_dentry_update_reval(dentry, upper,
			DCACHE_OP_REVALIDATE | DCACHE_OP_WEAK_REVALIDATE);

	वापस d_instantiate_anon(dentry, inode);

nomem:
	dput(dentry);
	dentry = ERR_PTR(-ENOMEM);
out_iput:
	iput(inode);
	वापस dentry;
पूर्ण

/* Get the upper or lower dentry in stach whose on layer @idx */
अटल काष्ठा dentry *ovl_dentry_real_at(काष्ठा dentry *dentry, पूर्णांक idx)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;
	पूर्णांक i;

	अगर (!idx)
		वापस ovl_dentry_upper(dentry);

	क्रम (i = 0; i < oe->numlower; i++) अणु
		अगर (oe->lowerstack[i].layer->idx == idx)
			वापस oe->lowerstack[i].dentry;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Lookup a child overlay dentry to get a connected overlay dentry whose real
 * dentry is @real. If @real is on upper layer, we lookup a child overlay
 * dentry with the same name as the real dentry. Otherwise, we need to consult
 * index क्रम lookup.
 */
अटल काष्ठा dentry *ovl_lookup_real_one(काष्ठा dentry *connected,
					  काष्ठा dentry *real,
					  स्थिर काष्ठा ovl_layer *layer)
अणु
	काष्ठा inode *dir = d_inode(connected);
	काष्ठा dentry *this, *parent = शून्य;
	काष्ठा name_snapshot name;
	पूर्णांक err;

	/*
	 * Lookup child overlay dentry by real name. The dir mutex protects us
	 * from racing with overlay नाम. If the overlay dentry that is above
	 * real has alपढ़ोy been moved to a parent that is not under the
	 * connected overlay dir, we वापस -ECHILD and restart the lookup of
	 * connected real path from the top.
	 */
	inode_lock_nested(dir, I_MUTEX_PARENT);
	err = -ECHILD;
	parent = dget_parent(real);
	अगर (ovl_dentry_real_at(connected, layer->idx) != parent)
		जाओ fail;

	/*
	 * We also need to take a snapshot of real dentry name to protect us
	 * from racing with underlying layer नाम. In this हाल, we करोn't
	 * care about वापसing ESTALE, only from dereferencing a मुक्त name
	 * poपूर्णांकer because we hold no lock on the real dentry.
	 */
	take_dentry_name_snapshot(&name, real);
	this = lookup_one_len(name.name.name, connected, name.name.len);
	err = PTR_ERR(this);
	अगर (IS_ERR(this)) अणु
		जाओ fail;
	पूर्ण अन्यथा अगर (!this || !this->d_inode) अणु
		dput(this);
		err = -ENOENT;
		जाओ fail;
	पूर्ण अन्यथा अगर (ovl_dentry_real_at(this, layer->idx) != real) अणु
		dput(this);
		err = -ESTALE;
		जाओ fail;
	पूर्ण

out:
	release_dentry_name_snapshot(&name);
	dput(parent);
	inode_unlock(dir);
	वापस this;

fail:
	pr_warn_ratelimited("failed to lookup one by real (%pd2, layer=%d, connected=%pd2, err=%i)\n",
			    real, layer->idx, connected, err);
	this = ERR_PTR(err);
	जाओ out;
पूर्ण

अटल काष्ठा dentry *ovl_lookup_real(काष्ठा super_block *sb,
				      काष्ठा dentry *real,
				      स्थिर काष्ठा ovl_layer *layer);

/*
 * Lookup an indexed or hashed overlay dentry by real inode.
 */
अटल काष्ठा dentry *ovl_lookup_real_inode(काष्ठा super_block *sb,
					    काष्ठा dentry *real,
					    स्थिर काष्ठा ovl_layer *layer)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	काष्ठा dentry *index = शून्य;
	काष्ठा dentry *this = शून्य;
	काष्ठा inode *inode;

	/*
	 * Decoding upper dir from index is expensive, so first try to lookup
	 * overlay dentry in inode/dcache.
	 */
	inode = ovl_lookup_inode(sb, real, !layer->idx);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (inode) अणु
		this = d_find_any_alias(inode);
		iput(inode);
	पूर्ण

	/*
	 * For decoded lower dir file handle, lookup index by origin to check
	 * अगर lower dir was copied up and and/or हटाओd.
	 */
	अगर (!this && layer->idx && ofs->indexdir && !WARN_ON(!d_is_dir(real))) अणु
		index = ovl_lookup_index(ofs, शून्य, real, false);
		अगर (IS_ERR(index))
			वापस index;
	पूर्ण

	/* Get connected upper overlay dir from index */
	अगर (index) अणु
		काष्ठा dentry *upper = ovl_index_upper(ofs, index);

		dput(index);
		अगर (IS_ERR_OR_शून्य(upper))
			वापस upper;

		/*
		 * ovl_lookup_real() in lower layer may call recursively once to
		 * ovl_lookup_real() in upper layer. The first level call walks
		 * back lower parents to the topmost indexed parent. The second
		 * recursive call walks back from indexed upper to the topmost
		 * connected/hashed upper parent (or up to root).
		 */
		this = ovl_lookup_real(sb, upper, &ofs->layers[0]);
		dput(upper);
	पूर्ण

	अगर (IS_ERR_OR_शून्य(this))
		वापस this;

	अगर (ovl_dentry_real_at(this, layer->idx) != real) अणु
		dput(this);
		this = ERR_PTR(-EIO);
	पूर्ण

	वापस this;
पूर्ण

/*
 * Lookup an indexed or hashed overlay dentry, whose real dentry is an
 * ancestor of @real.
 */
अटल काष्ठा dentry *ovl_lookup_real_ancestor(काष्ठा super_block *sb,
					       काष्ठा dentry *real,
					       स्थिर काष्ठा ovl_layer *layer)
अणु
	काष्ठा dentry *next, *parent = शून्य;
	काष्ठा dentry *ancestor = ERR_PTR(-EIO);

	अगर (real == layer->mnt->mnt_root)
		वापस dget(sb->s_root);

	/* Find the topmost indexed or hashed ancestor */
	next = dget(real);
	क्रम (;;) अणु
		parent = dget_parent(next);

		/*
		 * Lookup a matching overlay dentry in inode/dentry
		 * cache or in index by real inode.
		 */
		ancestor = ovl_lookup_real_inode(sb, next, layer);
		अगर (ancestor)
			अवरोध;

		अगर (parent == layer->mnt->mnt_root) अणु
			ancestor = dget(sb->s_root);
			अवरोध;
		पूर्ण

		/*
		 * If @real has been moved out of the layer root directory,
		 * we will eventully hit the real fs root. This cannot happen
		 * by legit overlay नाम, so we वापस error in that हाल.
		 */
		अगर (parent == next) अणु
			ancestor = ERR_PTR(-EXDEV);
			अवरोध;
		पूर्ण

		dput(next);
		next = parent;
	पूर्ण

	dput(parent);
	dput(next);

	वापस ancestor;
पूर्ण

/*
 * Lookup a connected overlay dentry whose real dentry is @real.
 * If @real is on upper layer, we lookup a child overlay dentry with the same
 * path the real dentry. Otherwise, we need to consult index क्रम lookup.
 */
अटल काष्ठा dentry *ovl_lookup_real(काष्ठा super_block *sb,
				      काष्ठा dentry *real,
				      स्थिर काष्ठा ovl_layer *layer)
अणु
	काष्ठा dentry *connected;
	पूर्णांक err = 0;

	connected = ovl_lookup_real_ancestor(sb, real, layer);
	अगर (IS_ERR(connected))
		वापस connected;

	जबतक (!err) अणु
		काष्ठा dentry *next, *this;
		काष्ठा dentry *parent = शून्य;
		काष्ठा dentry *real_connected = ovl_dentry_real_at(connected,
								   layer->idx);

		अगर (real_connected == real)
			अवरोध;

		/* Find the topmost dentry not yet connected */
		next = dget(real);
		क्रम (;;) अणु
			parent = dget_parent(next);

			अगर (parent == real_connected)
				अवरोध;

			/*
			 * If real has been moved out of 'real_connected',
			 * we will not find 'real_connected' and hit the layer
			 * root. In that हाल, we need to restart connecting.
			 * This game can go on क्रमever in the worst हाल. We
			 * may want to consider taking s_vfs_नाम_mutex अगर
			 * this happens more than once.
			 */
			अगर (parent == layer->mnt->mnt_root) अणु
				dput(connected);
				connected = dget(sb->s_root);
				अवरोध;
			पूर्ण

			/*
			 * If real file has been moved out of the layer root
			 * directory, we will eventully hit the real fs root.
			 * This cannot happen by legit overlay नाम, so we
			 * वापस error in that हाल.
			 */
			अगर (parent == next) अणु
				err = -EXDEV;
				अवरोध;
			पूर्ण

			dput(next);
			next = parent;
		पूर्ण

		अगर (!err) अणु
			this = ovl_lookup_real_one(connected, next, layer);
			अगर (IS_ERR(this))
				err = PTR_ERR(this);

			/*
			 * Lookup of child in overlay can fail when racing with
			 * overlay नाम of child away from 'connected' parent.
			 * In this हाल, we need to restart the lookup from the
			 * top, because we cannot trust that 'real_connected' is
			 * still an ancestor of 'real'. There is a good chance
			 * that the नामd overlay ancestor is now in cache, so
			 * ovl_lookup_real_ancestor() will find it and we can
			 * जारी to connect exactly from where lookup failed.
			 */
			अगर (err == -ECHILD) अणु
				this = ovl_lookup_real_ancestor(sb, real,
								layer);
				err = PTR_ERR_OR_ZERO(this);
			पूर्ण
			अगर (!err) अणु
				dput(connected);
				connected = this;
			पूर्ण
		पूर्ण

		dput(parent);
		dput(next);
	पूर्ण

	अगर (err)
		जाओ fail;

	वापस connected;

fail:
	pr_warn_ratelimited("failed to lookup by real (%pd2, layer=%d, connected=%pd2, err=%i)\n",
			    real, layer->idx, connected, err);
	dput(connected);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Get an overlay dentry from upper/lower real dentries and index.
 */
अटल काष्ठा dentry *ovl_get_dentry(काष्ठा super_block *sb,
				     काष्ठा dentry *upper,
				     काष्ठा ovl_path *lowerpath,
				     काष्ठा dentry *index)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	स्थिर काष्ठा ovl_layer *layer = upper ? &ofs->layers[0] : lowerpath->layer;
	काष्ठा dentry *real = upper ?: (index ?: lowerpath->dentry);

	/*
	 * Obtain a disconnected overlay dentry from a non-dir real dentry
	 * and index.
	 */
	अगर (!d_is_dir(real))
		वापस ovl_obtain_alias(sb, upper, lowerpath, index);

	/* Removed empty directory? */
	अगर ((real->d_flags & DCACHE_DISCONNECTED) || d_unhashed(real))
		वापस ERR_PTR(-ENOENT);

	/*
	 * If real dentry is connected and hashed, get a connected overlay
	 * dentry whose real dentry is @real.
	 */
	वापस ovl_lookup_real(sb, real, layer);
पूर्ण

अटल काष्ठा dentry *ovl_upper_fh_to_d(काष्ठा super_block *sb,
					काष्ठा ovl_fh *fh)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	काष्ठा dentry *dentry;
	काष्ठा dentry *upper;

	अगर (!ovl_upper_mnt(ofs))
		वापस ERR_PTR(-EACCES);

	upper = ovl_decode_real_fh(ofs, fh, ovl_upper_mnt(ofs), true);
	अगर (IS_ERR_OR_शून्य(upper))
		वापस upper;

	dentry = ovl_get_dentry(sb, upper, शून्य, शून्य);
	dput(upper);

	वापस dentry;
पूर्ण

अटल काष्ठा dentry *ovl_lower_fh_to_d(काष्ठा super_block *sb,
					काष्ठा ovl_fh *fh)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	काष्ठा ovl_path origin = अणु पूर्ण;
	काष्ठा ovl_path *stack = &origin;
	काष्ठा dentry *dentry = शून्य;
	काष्ठा dentry *index = शून्य;
	काष्ठा inode *inode;
	पूर्णांक err;

	/* First lookup overlay inode in inode cache by origin fh */
	err = ovl_check_origin_fh(ofs, fh, false, शून्य, &stack);
	अगर (err)
		वापस ERR_PTR(err);

	अगर (!d_is_dir(origin.dentry) ||
	    !(origin.dentry->d_flags & DCACHE_DISCONNECTED)) अणु
		inode = ovl_lookup_inode(sb, origin.dentry, false);
		err = PTR_ERR(inode);
		अगर (IS_ERR(inode))
			जाओ out_err;
		अगर (inode) अणु
			dentry = d_find_any_alias(inode);
			iput(inode);
			अगर (dentry)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Then lookup indexed upper/whiteout by origin fh */
	अगर (ofs->indexdir) अणु
		index = ovl_get_index_fh(ofs, fh);
		err = PTR_ERR(index);
		अगर (IS_ERR(index)) अणु
			index = शून्य;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* Then try to get a connected upper dir by index */
	अगर (index && d_is_dir(index)) अणु
		काष्ठा dentry *upper = ovl_index_upper(ofs, index);

		err = PTR_ERR(upper);
		अगर (IS_ERR_OR_शून्य(upper))
			जाओ out_err;

		dentry = ovl_get_dentry(sb, upper, शून्य, शून्य);
		dput(upper);
		जाओ out;
	पूर्ण

	/* Find origin.dentry again with ovl_acceptable() layer check */
	अगर (d_is_dir(origin.dentry)) अणु
		dput(origin.dentry);
		origin.dentry = शून्य;
		err = ovl_check_origin_fh(ofs, fh, true, शून्य, &stack);
		अगर (err)
			जाओ out_err;
	पूर्ण
	अगर (index) अणु
		err = ovl_verअगरy_origin(ofs, index, origin.dentry, false);
		अगर (err)
			जाओ out_err;
	पूर्ण

	/* Get a connected non-upper dir or disconnected non-dir */
	dentry = ovl_get_dentry(sb, शून्य, &origin, index);

out:
	dput(origin.dentry);
	dput(index);
	वापस dentry;

out_err:
	dentry = ERR_PTR(err);
	जाओ out;
पूर्ण

अटल काष्ठा ovl_fh *ovl_fid_to_fh(काष्ठा fid *fid, पूर्णांक buflen, पूर्णांक fh_type)
अणु
	काष्ठा ovl_fh *fh;

	/* If on-wire inner fid is aligned - nothing to करो */
	अगर (fh_type == OVL_खाताID_V1)
		वापस (काष्ठा ovl_fh *)fid;

	अगर (fh_type != OVL_खाताID_V0)
		वापस ERR_PTR(-EINVAL);

	अगर (buflen <= OVL_FH_WIRE_OFFSET)
		वापस ERR_PTR(-EINVAL);

	fh = kzalloc(buflen, GFP_KERNEL);
	अगर (!fh)
		वापस ERR_PTR(-ENOMEM);

	/* Copy unaligned inner fh पूर्णांकo aligned buffer */
	स_नकल(&fh->fb, fid, buflen - OVL_FH_WIRE_OFFSET);
	वापस fh;
पूर्ण

अटल काष्ठा dentry *ovl_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
				       पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा dentry *dentry = शून्य;
	काष्ठा ovl_fh *fh = शून्य;
	पूर्णांक len = fh_len << 2;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक err;

	fh = ovl_fid_to_fh(fid, len, fh_type);
	err = PTR_ERR(fh);
	अगर (IS_ERR(fh))
		जाओ out_err;

	err = ovl_check_fh_len(fh, len);
	अगर (err)
		जाओ out_err;

	flags = fh->fb.flags;
	dentry = (flags & OVL_FH_FLAG_PATH_UPPER) ?
		 ovl_upper_fh_to_d(sb, fh) :
		 ovl_lower_fh_to_d(sb, fh);
	err = PTR_ERR(dentry);
	अगर (IS_ERR(dentry) && err != -ESTALE)
		जाओ out_err;

out:
	/* We may have needed to re-align OVL_खाताID_V0 */
	अगर (!IS_ERR_OR_शून्य(fh) && fh != (व्योम *)fid)
		kमुक्त(fh);

	वापस dentry;

out_err:
	pr_warn_ratelimited("failed to decode file handle (len=%d, type=%d, flags=%x, err=%i)\n",
			    fh_len, fh_type, flags, err);
	dentry = ERR_PTR(err);
	जाओ out;
पूर्ण

अटल काष्ठा dentry *ovl_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
				       पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	pr_warn_ratelimited("connectable file handles not supported; use 'no_subtree_check' exportfs option.\n");
	वापस ERR_PTR(-EACCES);
पूर्ण

अटल पूर्णांक ovl_get_name(काष्ठा dentry *parent, अक्षर *name,
			काष्ठा dentry *child)
अणु
	/*
	 * ovl_fh_to_dentry() वापसs connected dir overlay dentries and
	 * ovl_fh_to_parent() is not implemented, so we should not get here.
	 */
	WARN_ON_ONCE(1);
	वापस -EIO;
पूर्ण

अटल काष्ठा dentry *ovl_get_parent(काष्ठा dentry *dentry)
अणु
	/*
	 * ovl_fh_to_dentry() वापसs connected dir overlay dentries, so we
	 * should not get here.
	 */
	WARN_ON_ONCE(1);
	वापस ERR_PTR(-EIO);
पूर्ण

स्थिर काष्ठा export_operations ovl_export_operations = अणु
	.encode_fh	= ovl_encode_fh,
	.fh_to_dentry	= ovl_fh_to_dentry,
	.fh_to_parent	= ovl_fh_to_parent,
	.get_name	= ovl_get_name,
	.get_parent	= ovl_get_parent,
पूर्ण;
