<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/file.h>
#समावेश <linux/xattr.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/ratelimit.h>
#समावेश "overlayfs.h"

काष्ठा ovl_cache_entry अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक type;
	u64 real_ino;
	u64 ino;
	काष्ठा list_head l_node;
	काष्ठा rb_node node;
	काष्ठा ovl_cache_entry *next_maybe_whiteout;
	bool is_upper;
	bool is_whiteout;
	अक्षर name[];
पूर्ण;

काष्ठा ovl_dir_cache अणु
	दीर्घ refcount;
	u64 version;
	काष्ठा list_head entries;
	काष्ठा rb_root root;
पूर्ण;

काष्ठा ovl_सूची_पढ़ो_data अणु
	काष्ठा dir_context ctx;
	काष्ठा dentry *dentry;
	bool is_lowest;
	काष्ठा rb_root *root;
	काष्ठा list_head *list;
	काष्ठा list_head middle;
	काष्ठा ovl_cache_entry *first_maybe_whiteout;
	पूर्णांक count;
	पूर्णांक err;
	bool is_upper;
	bool d_type_supported;
पूर्ण;

काष्ठा ovl_dir_file अणु
	bool is_real;
	bool is_upper;
	काष्ठा ovl_dir_cache *cache;
	काष्ठा list_head *cursor;
	काष्ठा file *realfile;
	काष्ठा file *upperfile;
पूर्ण;

अटल काष्ठा ovl_cache_entry *ovl_cache_entry_from_node(काष्ठा rb_node *n)
अणु
	वापस rb_entry(n, काष्ठा ovl_cache_entry, node);
पूर्ण

अटल bool ovl_cache_entry_find_link(स्थिर अक्षर *name, पूर्णांक len,
				      काष्ठा rb_node ***link,
				      काष्ठा rb_node **parent)
अणु
	bool found = false;
	काष्ठा rb_node **newp = *link;

	जबतक (!found && *newp) अणु
		पूर्णांक cmp;
		काष्ठा ovl_cache_entry *पंचांगp;

		*parent = *newp;
		पंचांगp = ovl_cache_entry_from_node(*newp);
		cmp = म_भेदन(name, पंचांगp->name, len);
		अगर (cmp > 0)
			newp = &पंचांगp->node.rb_right;
		अन्यथा अगर (cmp < 0 || len < पंचांगp->len)
			newp = &पंचांगp->node.rb_left;
		अन्यथा
			found = true;
	पूर्ण
	*link = newp;

	वापस found;
पूर्ण

अटल काष्ठा ovl_cache_entry *ovl_cache_entry_find(काष्ठा rb_root *root,
						    स्थिर अक्षर *name, पूर्णांक len)
अणु
	काष्ठा rb_node *node = root->rb_node;
	पूर्णांक cmp;

	जबतक (node) अणु
		काष्ठा ovl_cache_entry *p = ovl_cache_entry_from_node(node);

		cmp = म_भेदन(name, p->name, len);
		अगर (cmp > 0)
			node = p->node.rb_right;
		अन्यथा अगर (cmp < 0 || len < p->len)
			node = p->node.rb_left;
		अन्यथा
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool ovl_calc_d_ino(काष्ठा ovl_सूची_पढ़ो_data *rdd,
			   काष्ठा ovl_cache_entry *p)
अणु
	/* Don't care अगर not करोing ovl_iter() */
	अगर (!rdd->dentry)
		वापस false;

	/* Always recalc d_ino when remapping lower inode numbers */
	अगर (ovl_xino_bits(rdd->dentry->d_sb))
		वापस true;

	/* Always recalc d_ino क्रम parent */
	अगर (म_भेद(p->name, "..") == 0)
		वापस true;

	/* If this is lower, then native d_ino will करो */
	अगर (!rdd->is_upper)
		वापस false;

	/*
	 * Recalc d_ino क्रम '.' and क्रम all entries अगर dir is impure (contains
	 * copied up entries)
	 */
	अगर ((p->name[0] == '.' && p->len == 1) ||
	    ovl_test_flag(OVL_IMPURE, d_inode(rdd->dentry)))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा ovl_cache_entry *ovl_cache_entry_new(काष्ठा ovl_सूची_पढ़ो_data *rdd,
						   स्थिर अक्षर *name, पूर्णांक len,
						   u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_cache_entry *p;
	माप_प्रकार size = दुरत्व(काष्ठा ovl_cache_entry, name[len + 1]);

	p = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	स_नकल(p->name, name, len);
	p->name[len] = '\0';
	p->len = len;
	p->type = d_type;
	p->real_ino = ino;
	p->ino = ino;
	/* Defer setting d_ino क्रम upper entry to ovl_iterate() */
	अगर (ovl_calc_d_ino(rdd, p))
		p->ino = 0;
	p->is_upper = rdd->is_upper;
	p->is_whiteout = false;

	अगर (d_type == DT_CHR) अणु
		p->next_maybe_whiteout = rdd->first_maybe_whiteout;
		rdd->first_maybe_whiteout = p;
	पूर्ण
	वापस p;
पूर्ण

अटल पूर्णांक ovl_cache_entry_add_rb(काष्ठा ovl_सूची_पढ़ो_data *rdd,
				  स्थिर अक्षर *name, पूर्णांक len, u64 ino,
				  अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा rb_node **newp = &rdd->root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ovl_cache_entry *p;

	अगर (ovl_cache_entry_find_link(name, len, &newp, &parent))
		वापस 0;

	p = ovl_cache_entry_new(rdd, name, len, ino, d_type);
	अगर (p == शून्य) अणु
		rdd->err = -ENOMEM;
		वापस -ENOMEM;
	पूर्ण

	list_add_tail(&p->l_node, rdd->list);
	rb_link_node(&p->node, parent, newp);
	rb_insert_color(&p->node, rdd->root);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_fill_lowest(काष्ठा ovl_सूची_पढ़ो_data *rdd,
			   स्थिर अक्षर *name, पूर्णांक namelen,
			   loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_cache_entry *p;

	p = ovl_cache_entry_find(rdd->root, name, namelen);
	अगर (p) अणु
		list_move_tail(&p->l_node, &rdd->middle);
	पूर्ण अन्यथा अणु
		p = ovl_cache_entry_new(rdd, name, namelen, ino, d_type);
		अगर (p == शून्य)
			rdd->err = -ENOMEM;
		अन्यथा
			list_add_tail(&p->l_node, &rdd->middle);
	पूर्ण

	वापस rdd->err;
पूर्ण

व्योम ovl_cache_मुक्त(काष्ठा list_head *list)
अणु
	काष्ठा ovl_cache_entry *p;
	काष्ठा ovl_cache_entry *n;

	list_क्रम_each_entry_safe(p, n, list, l_node)
		kमुक्त(p);

	INIT_LIST_HEAD(list);
पूर्ण

व्योम ovl_dir_cache_मुक्त(काष्ठा inode *inode)
अणु
	काष्ठा ovl_dir_cache *cache = ovl_dir_cache(inode);

	अगर (cache) अणु
		ovl_cache_मुक्त(&cache->entries);
		kमुक्त(cache);
	पूर्ण
पूर्ण

अटल व्योम ovl_cache_put(काष्ठा ovl_dir_file *od, काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_dir_cache *cache = od->cache;

	WARN_ON(cache->refcount <= 0);
	cache->refcount--;
	अगर (!cache->refcount) अणु
		अगर (ovl_dir_cache(d_inode(dentry)) == cache)
			ovl_set_dir_cache(d_inode(dentry), शून्य);

		ovl_cache_मुक्त(&cache->entries);
		kमुक्त(cache);
	पूर्ण
पूर्ण

अटल पूर्णांक ovl_fill_merge(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			  पूर्णांक namelen, loff_t offset, u64 ino,
			  अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_सूची_पढ़ो_data *rdd =
		container_of(ctx, काष्ठा ovl_सूची_पढ़ो_data, ctx);

	rdd->count++;
	अगर (!rdd->is_lowest)
		वापस ovl_cache_entry_add_rb(rdd, name, namelen, ino, d_type);
	अन्यथा
		वापस ovl_fill_lowest(rdd, name, namelen, offset, ino, d_type);
पूर्ण

अटल पूर्णांक ovl_check_whiteouts(काष्ठा dentry *dir, काष्ठा ovl_सूची_पढ़ो_data *rdd)
अणु
	पूर्णांक err;
	काष्ठा ovl_cache_entry *p;
	काष्ठा dentry *dentry;
	स्थिर काष्ठा cred *old_cred;

	old_cred = ovl_override_creds(rdd->dentry->d_sb);

	err = करोwn_ग_लिखो_समाप्तable(&dir->d_inode->i_rwsem);
	अगर (!err) अणु
		जबतक (rdd->first_maybe_whiteout) अणु
			p = rdd->first_maybe_whiteout;
			rdd->first_maybe_whiteout = p->next_maybe_whiteout;
			dentry = lookup_one_len(p->name, dir, p->len);
			अगर (!IS_ERR(dentry)) अणु
				p->is_whiteout = ovl_is_whiteout(dentry);
				dput(dentry);
			पूर्ण
		पूर्ण
		inode_unlock(dir->d_inode);
	पूर्ण
	revert_creds(old_cred);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ovl_dir_पढ़ो(काष्ठा path *realpath,
			       काष्ठा ovl_सूची_पढ़ो_data *rdd)
अणु
	काष्ठा file *realfile;
	पूर्णांक err;

	realfile = ovl_path_खोलो(realpath, O_RDONLY | O_LARGEखाता);
	अगर (IS_ERR(realfile))
		वापस PTR_ERR(realfile);

	rdd->first_maybe_whiteout = शून्य;
	rdd->ctx.pos = 0;
	करो अणु
		rdd->count = 0;
		rdd->err = 0;
		err = iterate_dir(realfile, &rdd->ctx);
		अगर (err >= 0)
			err = rdd->err;
	पूर्ण जबतक (!err && rdd->count);

	अगर (!err && rdd->first_maybe_whiteout && rdd->dentry)
		err = ovl_check_whiteouts(realpath->dentry, rdd);

	fput(realfile);

	वापस err;
पूर्ण

अटल व्योम ovl_dir_reset(काष्ठा file *file)
अणु
	काष्ठा ovl_dir_file *od = file->निजी_data;
	काष्ठा ovl_dir_cache *cache = od->cache;
	काष्ठा dentry *dentry = file->f_path.dentry;
	bool is_real;

	अगर (cache && ovl_dentry_version_get(dentry) != cache->version) अणु
		ovl_cache_put(od, dentry);
		od->cache = शून्य;
		od->cursor = शून्य;
	पूर्ण
	is_real = ovl_dir_is_real(dentry);
	अगर (od->is_real != is_real) अणु
		/* is_real can only become false when dir is copied up */
		अगर (WARN_ON(is_real))
			वापस;
		od->is_real = false;
	पूर्ण
पूर्ण

अटल पूर्णांक ovl_dir_पढ़ो_merged(काष्ठा dentry *dentry, काष्ठा list_head *list,
	काष्ठा rb_root *root)
अणु
	पूर्णांक err;
	काष्ठा path realpath;
	काष्ठा ovl_सूची_पढ़ो_data rdd = अणु
		.ctx.actor = ovl_fill_merge,
		.dentry = dentry,
		.list = list,
		.root = root,
		.is_lowest = false,
	पूर्ण;
	पूर्णांक idx, next;

	क्रम (idx = 0; idx != -1; idx = next) अणु
		next = ovl_path_next(idx, dentry, &realpath);
		rdd.is_upper = ovl_dentry_upper(dentry) == realpath.dentry;

		अगर (next != -1) अणु
			err = ovl_dir_पढ़ो(&realpath, &rdd);
			अगर (err)
				अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * Insert lowest layer entries beक्रमe upper ones, this
			 * allows offsets to be reasonably स्थिरant
			 */
			list_add(&rdd.middle, rdd.list);
			rdd.is_lowest = true;
			err = ovl_dir_पढ़ो(&realpath, &rdd);
			list_del(&rdd.middle);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ovl_seek_cursor(काष्ठा ovl_dir_file *od, loff_t pos)
अणु
	काष्ठा list_head *p;
	loff_t off = 0;

	list_क्रम_each(p, &od->cache->entries) अणु
		अगर (off >= pos)
			अवरोध;
		off++;
	पूर्ण
	/* Cursor is safe since the cache is stable */
	od->cursor = p;
पूर्ण

अटल काष्ठा ovl_dir_cache *ovl_cache_get(काष्ठा dentry *dentry)
अणु
	पूर्णांक res;
	काष्ठा ovl_dir_cache *cache;

	cache = ovl_dir_cache(d_inode(dentry));
	अगर (cache && ovl_dentry_version_get(dentry) == cache->version) अणु
		WARN_ON(!cache->refcount);
		cache->refcount++;
		वापस cache;
	पूर्ण
	ovl_set_dir_cache(d_inode(dentry), शून्य);

	cache = kzalloc(माप(काष्ठा ovl_dir_cache), GFP_KERNEL);
	अगर (!cache)
		वापस ERR_PTR(-ENOMEM);

	cache->refcount = 1;
	INIT_LIST_HEAD(&cache->entries);
	cache->root = RB_ROOT;

	res = ovl_dir_पढ़ो_merged(dentry, &cache->entries, &cache->root);
	अगर (res) अणु
		ovl_cache_मुक्त(&cache->entries);
		kमुक्त(cache);
		वापस ERR_PTR(res);
	पूर्ण

	cache->version = ovl_dentry_version_get(dentry);
	ovl_set_dir_cache(d_inode(dentry), cache);

	वापस cache;
पूर्ण

/* Map inode number to lower fs unique range */
अटल u64 ovl_remap_lower_ino(u64 ino, पूर्णांक xinobits, पूर्णांक fsid,
			       स्थिर अक्षर *name, पूर्णांक namelen, bool warn)
अणु
	अचिन्हित पूर्णांक xinoshअगरt = 64 - xinobits;

	अगर (unlikely(ino >> xinoshअगरt)) अणु
		अगर (warn) अणु
			pr_warn_ratelimited("d_ino too big (%.*s, ino=%llu, xinobits=%d)\n",
					    namelen, name, ino, xinobits);
		पूर्ण
		वापस ino;
	पूर्ण

	/*
	 * The lowest xinobit is reserved क्रम mapping the non-peresistent inode
	 * numbers range, but this range is only exposed via st_ino, not here.
	 */
	वापस ino | ((u64)fsid) << (xinoshअगरt + 1);
पूर्ण

/*
 * Set d_ino क्रम upper entries. Non-upper entries should always report
 * the uppermost real inode ino and should not call this function.
 *
 * When not all layer are on same fs, report real ino also क्रम upper.
 *
 * When all layers are on the same fs, and upper has a reference to
 * copy up origin, call vfs_getattr() on the overlay entry to make
 * sure that d_ino will be consistent with st_ino from stat(2).
 */
अटल पूर्णांक ovl_cache_update_ino(काष्ठा path *path, काष्ठा ovl_cache_entry *p)

अणु
	काष्ठा dentry *dir = path->dentry;
	काष्ठा dentry *this = शून्य;
	क्रमागत ovl_path_type type;
	u64 ino = p->real_ino;
	पूर्णांक xinobits = ovl_xino_bits(dir->d_sb);
	पूर्णांक err = 0;

	अगर (!ovl_same_dev(dir->d_sb))
		जाओ out;

	अगर (p->name[0] == '.') अणु
		अगर (p->len == 1) अणु
			this = dget(dir);
			जाओ get;
		पूर्ण
		अगर (p->len == 2 && p->name[1] == '.') अणु
			/* we shall not be moved */
			this = dget(dir->d_parent);
			जाओ get;
		पूर्ण
	पूर्ण
	this = lookup_one_len(p->name, dir, p->len);
	अगर (IS_ERR_OR_शून्य(this) || !this->d_inode) अणु
		अगर (IS_ERR(this)) अणु
			err = PTR_ERR(this);
			this = शून्य;
			जाओ fail;
		पूर्ण
		जाओ out;
	पूर्ण

get:
	type = ovl_path_type(this);
	अगर (OVL_TYPE_ORIGIN(type)) अणु
		काष्ठा kstat stat;
		काष्ठा path statpath = *path;

		statpath.dentry = this;
		err = vfs_getattr(&statpath, &stat, STATX_INO, 0);
		अगर (err)
			जाओ fail;

		/*
		 * Directory inode is always on overlay st_dev.
		 * Non-dir with ovl_same_dev() could be on pseuकरो st_dev in हाल
		 * of xino bits overflow.
		 */
		WARN_ON_ONCE(S_ISसूची(stat.mode) &&
			     dir->d_sb->s_dev != stat.dev);
		ino = stat.ino;
	पूर्ण अन्यथा अगर (xinobits && !OVL_TYPE_UPPER(type)) अणु
		ino = ovl_remap_lower_ino(ino, xinobits,
					  ovl_layer_lower(this)->fsid,
					  p->name, p->len,
					  ovl_xino_warn(dir->d_sb));
	पूर्ण

out:
	p->ino = ino;
	dput(this);
	वापस err;

fail:
	pr_warn_ratelimited("failed to look up (%s) for ino (%i)\n",
			    p->name, err);
	जाओ out;
पूर्ण

अटल पूर्णांक ovl_fill_plain(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			  पूर्णांक namelen, loff_t offset, u64 ino,
			  अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_cache_entry *p;
	काष्ठा ovl_सूची_पढ़ो_data *rdd =
		container_of(ctx, काष्ठा ovl_सूची_पढ़ो_data, ctx);

	rdd->count++;
	p = ovl_cache_entry_new(rdd, name, namelen, ino, d_type);
	अगर (p == शून्य) अणु
		rdd->err = -ENOMEM;
		वापस -ENOMEM;
	पूर्ण
	list_add_tail(&p->l_node, rdd->list);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_dir_पढ़ो_impure(काष्ठा path *path,  काष्ठा list_head *list,
			       काष्ठा rb_root *root)
अणु
	पूर्णांक err;
	काष्ठा path realpath;
	काष्ठा ovl_cache_entry *p, *n;
	काष्ठा ovl_सूची_पढ़ो_data rdd = अणु
		.ctx.actor = ovl_fill_plain,
		.list = list,
		.root = root,
	पूर्ण;

	INIT_LIST_HEAD(list);
	*root = RB_ROOT;
	ovl_path_upper(path->dentry, &realpath);

	err = ovl_dir_पढ़ो(&realpath, &rdd);
	अगर (err)
		वापस err;

	list_क्रम_each_entry_safe(p, n, list, l_node) अणु
		अगर (म_भेद(p->name, ".") != 0 &&
		    म_भेद(p->name, "..") != 0) अणु
			err = ovl_cache_update_ino(path, p);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (p->ino == p->real_ino) अणु
			list_del(&p->l_node);
			kमुक्त(p);
		पूर्ण अन्यथा अणु
			काष्ठा rb_node **newp = &root->rb_node;
			काष्ठा rb_node *parent = शून्य;

			अगर (WARN_ON(ovl_cache_entry_find_link(p->name, p->len,
							      &newp, &parent)))
				वापस -EIO;

			rb_link_node(&p->node, parent, newp);
			rb_insert_color(&p->node, root);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ovl_dir_cache *ovl_cache_get_impure(काष्ठा path *path)
अणु
	पूर्णांक res;
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा ovl_fs *ofs = OVL_FS(dentry->d_sb);
	काष्ठा ovl_dir_cache *cache;

	cache = ovl_dir_cache(d_inode(dentry));
	अगर (cache && ovl_dentry_version_get(dentry) == cache->version)
		वापस cache;

	/* Impure cache is not refcounted, मुक्त it here */
	ovl_dir_cache_मुक्त(d_inode(dentry));
	ovl_set_dir_cache(d_inode(dentry), शून्य);

	cache = kzalloc(माप(काष्ठा ovl_dir_cache), GFP_KERNEL);
	अगर (!cache)
		वापस ERR_PTR(-ENOMEM);

	res = ovl_dir_पढ़ो_impure(path, &cache->entries, &cache->root);
	अगर (res) अणु
		ovl_cache_मुक्त(&cache->entries);
		kमुक्त(cache);
		वापस ERR_PTR(res);
	पूर्ण
	अगर (list_empty(&cache->entries)) अणु
		/*
		 * A good opportunity to get rid of an unneeded "impure" flag.
		 * Removing the "impure" xattr is best efक्रमt.
		 */
		अगर (!ovl_want_ग_लिखो(dentry)) अणु
			ovl_करो_हटाओxattr(ofs, ovl_dentry_upper(dentry),
					   OVL_XATTR_IMPURE);
			ovl_drop_ग_लिखो(dentry);
		पूर्ण
		ovl_clear_flag(OVL_IMPURE, d_inode(dentry));
		kमुक्त(cache);
		वापस शून्य;
	पूर्ण

	cache->version = ovl_dentry_version_get(dentry);
	ovl_set_dir_cache(d_inode(dentry), cache);

	वापस cache;
पूर्ण

काष्ठा ovl_सूची_पढ़ो_translate अणु
	काष्ठा dir_context *orig_ctx;
	काष्ठा ovl_dir_cache *cache;
	काष्ठा dir_context ctx;
	u64 parent_ino;
	पूर्णांक fsid;
	पूर्णांक xinobits;
	bool xinowarn;
पूर्ण;

अटल पूर्णांक ovl_fill_real(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			   पूर्णांक namelen, loff_t offset, u64 ino,
			   अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_सूची_पढ़ो_translate *rdt =
		container_of(ctx, काष्ठा ovl_सूची_पढ़ो_translate, ctx);
	काष्ठा dir_context *orig_ctx = rdt->orig_ctx;

	अगर (rdt->parent_ino && म_भेद(name, "..") == 0) अणु
		ino = rdt->parent_ino;
	पूर्ण अन्यथा अगर (rdt->cache) अणु
		काष्ठा ovl_cache_entry *p;

		p = ovl_cache_entry_find(&rdt->cache->root, name, namelen);
		अगर (p)
			ino = p->ino;
	पूर्ण अन्यथा अगर (rdt->xinobits) अणु
		ino = ovl_remap_lower_ino(ino, rdt->xinobits, rdt->fsid,
					  name, namelen, rdt->xinowarn);
	पूर्ण

	वापस orig_ctx->actor(orig_ctx, name, namelen, offset, ino, d_type);
पूर्ण

अटल bool ovl_is_impure_dir(काष्ठा file *file)
अणु
	काष्ठा ovl_dir_file *od = file->निजी_data;
	काष्ठा inode *dir = d_inode(file->f_path.dentry);

	/*
	 * Only upper dir can be impure, but अगर we are in the middle of
	 * iterating a lower real dir, dir could be copied up and marked
	 * impure. We only want the impure cache अगर we started iterating
	 * a real upper dir to begin with.
	 */
	वापस od->is_upper && ovl_test_flag(OVL_IMPURE, dir);

पूर्ण

अटल पूर्णांक ovl_iterate_real(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक err;
	काष्ठा ovl_dir_file *od = file->निजी_data;
	काष्ठा dentry *dir = file->f_path.dentry;
	स्थिर काष्ठा ovl_layer *lower_layer = ovl_layer_lower(dir);
	काष्ठा ovl_सूची_पढ़ो_translate rdt = अणु
		.ctx.actor = ovl_fill_real,
		.orig_ctx = ctx,
		.xinobits = ovl_xino_bits(dir->d_sb),
		.xinowarn = ovl_xino_warn(dir->d_sb),
	पूर्ण;

	अगर (rdt.xinobits && lower_layer)
		rdt.fsid = lower_layer->fsid;

	अगर (OVL_TYPE_MERGE(ovl_path_type(dir->d_parent))) अणु
		काष्ठा kstat stat;
		काष्ठा path statpath = file->f_path;

		statpath.dentry = dir->d_parent;
		err = vfs_getattr(&statpath, &stat, STATX_INO, 0);
		अगर (err)
			वापस err;

		WARN_ON_ONCE(dir->d_sb->s_dev != stat.dev);
		rdt.parent_ino = stat.ino;
	पूर्ण

	अगर (ovl_is_impure_dir(file)) अणु
		rdt.cache = ovl_cache_get_impure(&file->f_path);
		अगर (IS_ERR(rdt.cache))
			वापस PTR_ERR(rdt.cache);
	पूर्ण

	err = iterate_dir(od->realfile, &rdt.ctx);
	ctx->pos = rdt.ctx.pos;

	वापस err;
पूर्ण


अटल पूर्णांक ovl_iterate(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा ovl_dir_file *od = file->निजी_data;
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा ovl_cache_entry *p;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	old_cred = ovl_override_creds(dentry->d_sb);
	अगर (!ctx->pos)
		ovl_dir_reset(file);

	अगर (od->is_real) अणु
		/*
		 * If parent is merge, then need to adjust d_ino क्रम '..', अगर
		 * dir is impure then need to adjust d_ino क्रम copied up
		 * entries.
		 */
		अगर (ovl_xino_bits(dentry->d_sb) ||
		    (ovl_same_fs(dentry->d_sb) &&
		     (ovl_is_impure_dir(file) ||
		      OVL_TYPE_MERGE(ovl_path_type(dentry->d_parent))))) अणु
			err = ovl_iterate_real(file, ctx);
		पूर्ण अन्यथा अणु
			err = iterate_dir(od->realfile, ctx);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!od->cache) अणु
		काष्ठा ovl_dir_cache *cache;

		cache = ovl_cache_get(dentry);
		err = PTR_ERR(cache);
		अगर (IS_ERR(cache))
			जाओ out;

		od->cache = cache;
		ovl_seek_cursor(od, ctx->pos);
	पूर्ण

	जबतक (od->cursor != &od->cache->entries) अणु
		p = list_entry(od->cursor, काष्ठा ovl_cache_entry, l_node);
		अगर (!p->is_whiteout) अणु
			अगर (!p->ino) अणु
				err = ovl_cache_update_ino(&file->f_path, p);
				अगर (err)
					जाओ out;
			पूर्ण
			अगर (!dir_emit(ctx, p->name, p->len, p->ino, p->type))
				अवरोध;
		पूर्ण
		od->cursor = p->l_node.next;
		ctx->pos++;
	पूर्ण
	err = 0;
out:
	revert_creds(old_cred);
	वापस err;
पूर्ण

अटल loff_t ovl_dir_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	loff_t res;
	काष्ठा ovl_dir_file *od = file->निजी_data;

	inode_lock(file_inode(file));
	अगर (!file->f_pos)
		ovl_dir_reset(file);

	अगर (od->is_real) अणु
		res = vfs_llseek(od->realfile, offset, origin);
		file->f_pos = od->realfile->f_pos;
	पूर्ण अन्यथा अणु
		res = -EINVAL;

		चयन (origin) अणु
		हाल प्रस्तुत_से:
			offset += file->f_pos;
			अवरोध;
		हाल शुरू_से:
			अवरोध;
		शेष:
			जाओ out_unlock;
		पूर्ण
		अगर (offset < 0)
			जाओ out_unlock;

		अगर (offset != file->f_pos) अणु
			file->f_pos = offset;
			अगर (od->cache)
				ovl_seek_cursor(od, offset);
		पूर्ण
		res = offset;
	पूर्ण
out_unlock:
	inode_unlock(file_inode(file));

	वापस res;
पूर्ण

अटल काष्ठा file *ovl_dir_खोलो_realfile(स्थिर काष्ठा file *file,
					  काष्ठा path *realpath)
अणु
	काष्ठा file *res;
	स्थिर काष्ठा cred *old_cred;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	res = ovl_path_खोलो(realpath, O_RDONLY | (file->f_flags & O_LARGEखाता));
	revert_creds(old_cred);

	वापस res;
पूर्ण

/*
 * Like ovl_real_fdget(), वापसs upperfile अगर dir was copied up since खोलो.
 * Unlike ovl_real_fdget(), this caches upperfile in file->निजी_data.
 *
 * TODO: use same असलtract type क्रम file->निजी_data of dir and file so
 * upperfile could also be cached क्रम files as well.
 */
काष्ठा file *ovl_dir_real_file(स्थिर काष्ठा file *file, bool want_upper)
अणु

	काष्ठा ovl_dir_file *od = file->निजी_data;
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा file *old, *realfile = od->realfile;

	अगर (!OVL_TYPE_UPPER(ovl_path_type(dentry)))
		वापस want_upper ? शून्य : realfile;

	/*
	 * Need to check अगर we started out being a lower dir, but got copied up
	 */
	अगर (!od->is_upper) अणु
		realfile = READ_ONCE(od->upperfile);
		अगर (!realfile) अणु
			काष्ठा path upperpath;

			ovl_path_upper(dentry, &upperpath);
			realfile = ovl_dir_खोलो_realfile(file, &upperpath);
			अगर (IS_ERR(realfile))
				वापस realfile;

			old = cmpxchg_release(&od->upperfile, शून्य, realfile);
			अगर (old) अणु
				fput(realfile);
				realfile = old;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस realfile;
पूर्ण

अटल पूर्णांक ovl_dir_fsync(काष्ठा file *file, loff_t start, loff_t end,
			 पूर्णांक datasync)
अणु
	काष्ठा file *realfile;
	पूर्णांक err;

	err = ovl_sync_status(OVL_FS(file->f_path.dentry->d_sb));
	अगर (err <= 0)
		वापस err;

	realfile = ovl_dir_real_file(file, true);
	err = PTR_ERR_OR_ZERO(realfile);

	/* Nothing to sync क्रम lower */
	अगर (!realfile || err)
		वापस err;

	वापस vfs_fsync_range(realfile, start, end, datasync);
पूर्ण

अटल पूर्णांक ovl_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ovl_dir_file *od = file->निजी_data;

	अगर (od->cache) अणु
		inode_lock(inode);
		ovl_cache_put(od, file->f_path.dentry);
		inode_unlock(inode);
	पूर्ण
	fput(od->realfile);
	अगर (od->upperfile)
		fput(od->upperfile);
	kमुक्त(od);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा path realpath;
	काष्ठा file *realfile;
	काष्ठा ovl_dir_file *od;
	क्रमागत ovl_path_type type;

	od = kzalloc(माप(काष्ठा ovl_dir_file), GFP_KERNEL);
	अगर (!od)
		वापस -ENOMEM;

	type = ovl_path_real(file->f_path.dentry, &realpath);
	realfile = ovl_dir_खोलो_realfile(file, &realpath);
	अगर (IS_ERR(realfile)) अणु
		kमुक्त(od);
		वापस PTR_ERR(realfile);
	पूर्ण
	od->realfile = realfile;
	od->is_real = ovl_dir_is_real(file->f_path.dentry);
	od->is_upper = OVL_TYPE_UPPER(type);
	file->निजी_data = od;

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations ovl_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.खोलो		= ovl_dir_खोलो,
	.iterate	= ovl_iterate,
	.llseek		= ovl_dir_llseek,
	.fsync		= ovl_dir_fsync,
	.release	= ovl_dir_release,
पूर्ण;

पूर्णांक ovl_check_empty_dir(काष्ठा dentry *dentry, काष्ठा list_head *list)
अणु
	पूर्णांक err;
	काष्ठा ovl_cache_entry *p, *n;
	काष्ठा rb_root root = RB_ROOT;
	स्थिर काष्ठा cred *old_cred;

	old_cred = ovl_override_creds(dentry->d_sb);
	err = ovl_dir_पढ़ो_merged(dentry, list, &root);
	revert_creds(old_cred);
	अगर (err)
		वापस err;

	err = 0;

	list_क्रम_each_entry_safe(p, n, list, l_node) अणु
		/*
		 * Select whiteouts in upperdir, they should
		 * be cleared when deleting this directory.
		 */
		अगर (p->is_whiteout) अणु
			अगर (p->is_upper)
				जारी;
			जाओ del_entry;
		पूर्ण

		अगर (p->name[0] == '.') अणु
			अगर (p->len == 1)
				जाओ del_entry;
			अगर (p->len == 2 && p->name[1] == '.')
				जाओ del_entry;
		पूर्ण
		err = -ENOTEMPTY;
		अवरोध;

del_entry:
		list_del(&p->l_node);
		kमुक्त(p);
	पूर्ण

	वापस err;
पूर्ण

व्योम ovl_cleanup_whiteouts(काष्ठा dentry *upper, काष्ठा list_head *list)
अणु
	काष्ठा ovl_cache_entry *p;

	inode_lock_nested(upper->d_inode, I_MUTEX_CHILD);
	list_क्रम_each_entry(p, list, l_node) अणु
		काष्ठा dentry *dentry;

		अगर (WARN_ON(!p->is_whiteout || !p->is_upper))
			जारी;

		dentry = lookup_one_len(p->name, upper, p->len);
		अगर (IS_ERR(dentry)) अणु
			pr_err("lookup '%s/%.*s' failed (%i)\n",
			       upper->d_name.name, p->len, p->name,
			       (पूर्णांक) PTR_ERR(dentry));
			जारी;
		पूर्ण
		अगर (dentry->d_inode)
			ovl_cleanup(upper->d_inode, dentry);
		dput(dentry);
	पूर्ण
	inode_unlock(upper->d_inode);
पूर्ण

अटल पूर्णांक ovl_check_d_type(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			  पूर्णांक namelen, loff_t offset, u64 ino,
			  अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ovl_सूची_पढ़ो_data *rdd =
		container_of(ctx, काष्ठा ovl_सूची_पढ़ो_data, ctx);

	/* Even अगर d_type is not supported, DT_सूची is वापसed क्रम . and .. */
	अगर (!म_भेदन(name, ".", namelen) || !म_भेदन(name, "..", namelen))
		वापस 0;

	अगर (d_type != DT_UNKNOWN)
		rdd->d_type_supported = true;

	वापस 0;
पूर्ण

/*
 * Returns 1 अगर d_type is supported, 0 not supported/unknown. Negative values
 * अगर error is encountered.
 */
पूर्णांक ovl_check_d_type_supported(काष्ठा path *realpath)
अणु
	पूर्णांक err;
	काष्ठा ovl_सूची_पढ़ो_data rdd = अणु
		.ctx.actor = ovl_check_d_type,
		.d_type_supported = false,
	पूर्ण;

	err = ovl_dir_पढ़ो(realpath, &rdd);
	अगर (err)
		वापस err;

	वापस rdd.d_type_supported;
पूर्ण

#घोषणा OVL_INCOMPATसूची_NAME "incompat"

अटल पूर्णांक ovl_workdir_cleanup_recurse(काष्ठा path *path, पूर्णांक level)
अणु
	पूर्णांक err;
	काष्ठा inode *dir = path->dentry->d_inode;
	LIST_HEAD(list);
	काष्ठा rb_root root = RB_ROOT;
	काष्ठा ovl_cache_entry *p;
	काष्ठा ovl_सूची_पढ़ो_data rdd = अणु
		.ctx.actor = ovl_fill_merge,
		.dentry = शून्य,
		.list = &list,
		.root = &root,
		.is_lowest = false,
	पूर्ण;
	bool incompat = false;

	/*
	 * The "work/incompat" directory is treated specially - अगर it is not
	 * empty, instead of prपूर्णांकing a generic error and mounting पढ़ो-only,
	 * we will error about incompat features and fail the mount.
	 *
	 * When called from ovl_indexdir_cleanup(), path->dentry->d_name.name
	 * starts with '#'.
	 */
	अगर (level == 2 &&
	    !म_भेद(path->dentry->d_name.name, OVL_INCOMPATसूची_NAME))
		incompat = true;

	err = ovl_dir_पढ़ो(path, &rdd);
	अगर (err)
		जाओ out;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	list_क्रम_each_entry(p, &list, l_node) अणु
		काष्ठा dentry *dentry;

		अगर (p->name[0] == '.') अणु
			अगर (p->len == 1)
				जारी;
			अगर (p->len == 2 && p->name[1] == '.')
				जारी;
		पूर्ण अन्यथा अगर (incompat) अणु
			pr_err("overlay with incompat feature '%s' cannot be mounted\n",
				p->name);
			err = -EINVAL;
			अवरोध;
		पूर्ण
		dentry = lookup_one_len(p->name, path->dentry, p->len);
		अगर (IS_ERR(dentry))
			जारी;
		अगर (dentry->d_inode)
			err = ovl_workdir_cleanup(dir, path->mnt, dentry, level);
		dput(dentry);
		अगर (err)
			अवरोध;
	पूर्ण
	inode_unlock(dir);
out:
	ovl_cache_मुक्त(&list);
	वापस err;
पूर्ण

पूर्णांक ovl_workdir_cleanup(काष्ठा inode *dir, काष्ठा vfsmount *mnt,
			 काष्ठा dentry *dentry, पूर्णांक level)
अणु
	पूर्णांक err;

	अगर (!d_is_dir(dentry) || level > 1) अणु
		वापस ovl_cleanup(dir, dentry);
	पूर्ण

	err = ovl_करो_सूची_हटाओ(dir, dentry);
	अगर (err) अणु
		काष्ठा path path = अणु .mnt = mnt, .dentry = dentry पूर्ण;

		inode_unlock(dir);
		err = ovl_workdir_cleanup_recurse(&path, level + 1);
		inode_lock_nested(dir, I_MUTEX_PARENT);
		अगर (!err)
			err = ovl_cleanup(dir, dentry);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ovl_indexdir_cleanup(काष्ठा ovl_fs *ofs)
अणु
	पूर्णांक err;
	काष्ठा dentry *indexdir = ofs->indexdir;
	काष्ठा dentry *index = शून्य;
	काष्ठा inode *dir = indexdir->d_inode;
	काष्ठा path path = अणु .mnt = ovl_upper_mnt(ofs), .dentry = indexdir पूर्ण;
	LIST_HEAD(list);
	काष्ठा rb_root root = RB_ROOT;
	काष्ठा ovl_cache_entry *p;
	काष्ठा ovl_सूची_पढ़ो_data rdd = अणु
		.ctx.actor = ovl_fill_merge,
		.dentry = शून्य,
		.list = &list,
		.root = &root,
		.is_lowest = false,
	पूर्ण;

	err = ovl_dir_पढ़ो(&path, &rdd);
	अगर (err)
		जाओ out;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	list_क्रम_each_entry(p, &list, l_node) अणु
		अगर (p->name[0] == '.') अणु
			अगर (p->len == 1)
				जारी;
			अगर (p->len == 2 && p->name[1] == '.')
				जारी;
		पूर्ण
		index = lookup_one_len(p->name, indexdir, p->len);
		अगर (IS_ERR(index)) अणु
			err = PTR_ERR(index);
			index = शून्य;
			अवरोध;
		पूर्ण
		/* Cleanup leftover from index create/cleanup attempt */
		अगर (index->d_name.name[0] == '#') अणु
			err = ovl_workdir_cleanup(dir, path.mnt, index, 1);
			अगर (err)
				अवरोध;
			जाओ next;
		पूर्ण
		err = ovl_verअगरy_index(ofs, index);
		अगर (!err) अणु
			जाओ next;
		पूर्ण अन्यथा अगर (err == -ESTALE) अणु
			/* Cleanup stale index entries */
			err = ovl_cleanup(dir, index);
		पूर्ण अन्यथा अगर (err != -ENOENT) अणु
			/*
			 * Abort mount to aव्योम corrupting the index अगर
			 * an incompatible index entry was found or on out
			 * of memory.
			 */
			अवरोध;
		पूर्ण अन्यथा अगर (ofs->config.nfs_export) अणु
			/*
			 * Whiteout orphan index to block future खोलो by
			 * handle after overlay nlink dropped to zero.
			 */
			err = ovl_cleanup_and_whiteout(ofs, dir, index);
		पूर्ण अन्यथा अणु
			/* Cleanup orphan index entries */
			err = ovl_cleanup(dir, index);
		पूर्ण

		अगर (err)
			अवरोध;

next:
		dput(index);
		index = शून्य;
	पूर्ण
	dput(index);
	inode_unlock(dir);
out:
	ovl_cache_मुक्त(&list);
	अगर (err)
		pr_err("failed index dir cleanup (%i)\n", err);
	वापस err;
पूर्ण
