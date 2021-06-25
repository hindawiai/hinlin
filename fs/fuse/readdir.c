<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2018  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/


#समावेश "fuse_i.h"
#समावेश <linux/iversion.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>

अटल bool fuse_use_सूची_पढ़ोplus(काष्ठा inode *dir, काष्ठा dir_context *ctx)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(dir);
	काष्ठा fuse_inode *fi = get_fuse_inode(dir);

	अगर (!fc->करो_सूची_पढ़ोplus)
		वापस false;
	अगर (!fc->सूची_पढ़ोplus_स्वतः)
		वापस true;
	अगर (test_and_clear_bit(FUSE_I_ADVISE_RDPLUS, &fi->state))
		वापस true;
	अगर (ctx->pos == 0)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम fuse_add_dirent_to_cache(काष्ठा file *file,
				     काष्ठा fuse_dirent *dirent, loff_t pos)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(file_inode(file));
	माप_प्रकार reclen = FUSE_सूचीENT_SIZE(dirent);
	pgoff_t index;
	काष्ठा page *page;
	loff_t size;
	u64 version;
	अचिन्हित पूर्णांक offset;
	व्योम *addr;

	spin_lock(&fi->rdc.lock);
	/*
	 * Is cache alपढ़ोy completed?  Or this entry करोes not go at the end of
	 * cache?
	 */
	अगर (fi->rdc.cached || pos != fi->rdc.pos) अणु
		spin_unlock(&fi->rdc.lock);
		वापस;
	पूर्ण
	version = fi->rdc.version;
	size = fi->rdc.size;
	offset = size & ~PAGE_MASK;
	index = size >> PAGE_SHIFT;
	/* Dirent करोesn't fit in current page?  Jump to next page. */
	अगर (offset + reclen > PAGE_SIZE) अणु
		index++;
		offset = 0;
	पूर्ण
	spin_unlock(&fi->rdc.lock);

	अगर (offset) अणु
		page = find_lock_page(file->f_mapping, index);
	पूर्ण अन्यथा अणु
		page = find_or_create_page(file->f_mapping, index,
					   mapping_gfp_mask(file->f_mapping));
	पूर्ण
	अगर (!page)
		वापस;

	spin_lock(&fi->rdc.lock);
	/* Raced with another सूची_पढ़ो */
	अगर (fi->rdc.version != version || fi->rdc.size != size ||
	    WARN_ON(fi->rdc.pos != pos))
		जाओ unlock;

	addr = kmap_atomic(page);
	अगर (!offset)
		clear_page(addr);
	स_नकल(addr + offset, dirent, reclen);
	kunmap_atomic(addr);
	fi->rdc.size = (index << PAGE_SHIFT) + offset + reclen;
	fi->rdc.pos = dirent->off;
unlock:
	spin_unlock(&fi->rdc.lock);
	unlock_page(page);
	put_page(page);
पूर्ण

अटल व्योम fuse_सूची_पढ़ो_cache_end(काष्ठा file *file, loff_t pos)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(file_inode(file));
	loff_t end;

	spin_lock(&fi->rdc.lock);
	/* करोes cache end position match current position? */
	अगर (fi->rdc.pos != pos) अणु
		spin_unlock(&fi->rdc.lock);
		वापस;
	पूर्ण

	fi->rdc.cached = true;
	end = ALIGN(fi->rdc.size, PAGE_SIZE);
	spin_unlock(&fi->rdc.lock);

	/* truncate unused tail of cache */
	truncate_inode_pages(file->f_mapping, end);
पूर्ण

अटल bool fuse_emit(काष्ठा file *file, काष्ठा dir_context *ctx,
		      काष्ठा fuse_dirent *dirent)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;

	अगर (ff->खोलो_flags & FOPEN_CACHE_सूची)
		fuse_add_dirent_to_cache(file, dirent, ctx->pos);

	वापस dir_emit(ctx, dirent->name, dirent->namelen, dirent->ino,
			dirent->type);
पूर्ण

अटल पूर्णांक parse_dirfile(अक्षर *buf, माप_प्रकार nbytes, काष्ठा file *file,
			 काष्ठा dir_context *ctx)
अणु
	जबतक (nbytes >= FUSE_NAME_OFFSET) अणु
		काष्ठा fuse_dirent *dirent = (काष्ठा fuse_dirent *) buf;
		माप_प्रकार reclen = FUSE_सूचीENT_SIZE(dirent);
		अगर (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			वापस -EIO;
		अगर (reclen > nbytes)
			अवरोध;
		अगर (स_प्रथम(dirent->name, '/', dirent->namelen) != शून्य)
			वापस -EIO;

		अगर (!fuse_emit(file, ctx, dirent))
			अवरोध;

		buf += reclen;
		nbytes -= reclen;
		ctx->pos = dirent->off;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_direntplus_link(काष्ठा file *file,
				काष्ठा fuse_direntplus *direntplus,
				u64 attr_version)
अणु
	काष्ठा fuse_entry_out *o = &direntplus->entry_out;
	काष्ठा fuse_dirent *dirent = &direntplus->dirent;
	काष्ठा dentry *parent = file->f_path.dentry;
	काष्ठा qstr name = QSTR_INIT(dirent->name, dirent->namelen);
	काष्ठा dentry *dentry;
	काष्ठा dentry *alias;
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा fuse_conn *fc;
	काष्ठा inode *inode;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	अगर (!o->nodeid) अणु
		/*
		 * Unlike in the हाल of fuse_lookup, zero nodeid करोes not mean
		 * ENOENT. Instead, it only means the userspace fileप्रणाली did
		 * not want to वापस attributes/handle क्रम this entry.
		 *
		 * So करो nothing.
		 */
		वापस 0;
	पूर्ण

	अगर (name.name[0] == '.') अणु
		/*
		 * We could potentially refresh the attributes of the directory
		 * and its parent?
		 */
		अगर (name.len == 1)
			वापस 0;
		अगर (name.name[1] == '.' && name.len == 2)
			वापस 0;
	पूर्ण

	अगर (invalid_nodeid(o->nodeid))
		वापस -EIO;
	अगर (fuse_invalid_attr(&o->attr))
		वापस -EIO;

	fc = get_fuse_conn(dir);

	name.hash = full_name_hash(parent, name.name, name.len);
	dentry = d_lookup(parent, &name);
	अगर (!dentry) अणु
retry:
		dentry = d_alloc_parallel(parent, &name, &wq);
		अगर (IS_ERR(dentry))
			वापस PTR_ERR(dentry);
	पूर्ण
	अगर (!d_in_lookup(dentry)) अणु
		काष्ठा fuse_inode *fi;
		inode = d_inode(dentry);
		अगर (!inode ||
		    get_node_id(inode) != o->nodeid ||
		    inode_wrong_type(inode, o->attr.mode)) अणु
			d_invalidate(dentry);
			dput(dentry);
			जाओ retry;
		पूर्ण
		अगर (fuse_is_bad(inode)) अणु
			dput(dentry);
			वापस -EIO;
		पूर्ण

		fi = get_fuse_inode(inode);
		spin_lock(&fi->lock);
		fi->nlookup++;
		spin_unlock(&fi->lock);

		क्रमget_all_cached_acls(inode);
		fuse_change_attributes(inode, &o->attr,
				       entry_attr_समयout(o),
				       attr_version);
		/*
		 * The other branch comes via fuse_iget()
		 * which bumps nlookup inside
		 */
	पूर्ण अन्यथा अणु
		inode = fuse_iget(dir->i_sb, o->nodeid, o->generation,
				  &o->attr, entry_attr_समयout(o),
				  attr_version);
		अगर (!inode)
			inode = ERR_PTR(-ENOMEM);

		alias = d_splice_alias(inode, dentry);
		d_lookup_करोne(dentry);
		अगर (alias) अणु
			dput(dentry);
			dentry = alias;
		पूर्ण
		अगर (IS_ERR(dentry))
			वापस PTR_ERR(dentry);
	पूर्ण
	अगर (fc->सूची_पढ़ोplus_स्वतः)
		set_bit(FUSE_I_INIT_RDPLUS, &get_fuse_inode(inode)->state);
	fuse_change_entry_समयout(dentry, o);

	dput(dentry);
	वापस 0;
पूर्ण

अटल व्योम fuse_क्रमce_क्रमget(काष्ठा file *file, u64 nodeid)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_क्रमget_in inarg;
	FUSE_ARGS(args);

	स_रखो(&inarg, 0, माप(inarg));
	inarg.nlookup = 1;
	args.opcode = FUSE_FORGET;
	args.nodeid = nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.क्रमce = true;
	args.noreply = true;

	fuse_simple_request(fm, &args);
	/* ignore errors */
पूर्ण

अटल पूर्णांक parse_dirplusfile(अक्षर *buf, माप_प्रकार nbytes, काष्ठा file *file,
			     काष्ठा dir_context *ctx, u64 attr_version)
अणु
	काष्ठा fuse_direntplus *direntplus;
	काष्ठा fuse_dirent *dirent;
	माप_प्रकार reclen;
	पूर्णांक over = 0;
	पूर्णांक ret;

	जबतक (nbytes >= FUSE_NAME_OFFSET_सूचीENTPLUS) अणु
		direntplus = (काष्ठा fuse_direntplus *) buf;
		dirent = &direntplus->dirent;
		reclen = FUSE_सूचीENTPLUS_SIZE(direntplus);

		अगर (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			वापस -EIO;
		अगर (reclen > nbytes)
			अवरोध;
		अगर (स_प्रथम(dirent->name, '/', dirent->namelen) != शून्य)
			वापस -EIO;

		अगर (!over) अणु
			/* We fill entries पूर्णांकo dstbuf only as much as
			   it can hold. But we still जारी iterating
			   over reमुख्यing entries to link them. If not,
			   we need to send a FORGET क्रम each of those
			   which we did not link.
			*/
			over = !fuse_emit(file, ctx, dirent);
			अगर (!over)
				ctx->pos = dirent->off;
		पूर्ण

		buf += reclen;
		nbytes -= reclen;

		ret = fuse_direntplus_link(file, direntplus, attr_version);
		अगर (ret)
			fuse_क्रमce_क्रमget(file, direntplus->entry_out.nodeid);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_सूची_पढ़ो_uncached(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक plus;
	sमाप_प्रकार res;
	काष्ठा page *page;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_io_args ia = अणुपूर्ण;
	काष्ठा fuse_args_pages *ap = &ia.ap;
	काष्ठा fuse_page_desc desc = अणु .length = PAGE_SIZE पूर्ण;
	u64 attr_version = 0;
	bool locked;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	plus = fuse_use_सूची_पढ़ोplus(inode, ctx);
	ap->args.out_pages = true;
	ap->num_pages = 1;
	ap->pages = &page;
	ap->descs = &desc;
	अगर (plus) अणु
		attr_version = fuse_get_attr_version(fm->fc);
		fuse_पढ़ो_args_fill(&ia, file, ctx->pos, PAGE_SIZE,
				    FUSE_READसूचीPLUS);
	पूर्ण अन्यथा अणु
		fuse_पढ़ो_args_fill(&ia, file, ctx->pos, PAGE_SIZE,
				    FUSE_READसूची);
	पूर्ण
	locked = fuse_lock_inode(inode);
	res = fuse_simple_request(fm, &ap->args);
	fuse_unlock_inode(inode, locked);
	अगर (res >= 0) अणु
		अगर (!res) अणु
			काष्ठा fuse_file *ff = file->निजी_data;

			अगर (ff->खोलो_flags & FOPEN_CACHE_सूची)
				fuse_सूची_पढ़ो_cache_end(file, ctx->pos);
		पूर्ण अन्यथा अगर (plus) अणु
			res = parse_dirplusfile(page_address(page), res,
						file, ctx, attr_version);
		पूर्ण अन्यथा अणु
			res = parse_dirfile(page_address(page), res, file,
					    ctx);
		पूर्ण
	पूर्ण

	__मुक्त_page(page);
	fuse_invalidate_aसमय(inode);
	वापस res;
पूर्ण

क्रमागत fuse_parse_result अणु
	FOUND_ERR = -1,
	FOUND_NONE = 0,
	FOUND_SOME,
	FOUND_ALL,
पूर्ण;

अटल क्रमागत fuse_parse_result fuse_parse_cache(काष्ठा fuse_file *ff,
					       व्योम *addr, अचिन्हित पूर्णांक size,
					       काष्ठा dir_context *ctx)
अणु
	अचिन्हित पूर्णांक offset = ff->सूची_पढ़ो.cache_off & ~PAGE_MASK;
	क्रमागत fuse_parse_result res = FOUND_NONE;

	WARN_ON(offset >= size);

	क्रम (;;) अणु
		काष्ठा fuse_dirent *dirent = addr + offset;
		अचिन्हित पूर्णांक nbytes = size - offset;
		माप_प्रकार reclen;

		अगर (nbytes < FUSE_NAME_OFFSET || !dirent->namelen)
			अवरोध;

		reclen = FUSE_सूचीENT_SIZE(dirent); /* derefs ->namelen */

		अगर (WARN_ON(dirent->namelen > FUSE_NAME_MAX))
			वापस FOUND_ERR;
		अगर (WARN_ON(reclen > nbytes))
			वापस FOUND_ERR;
		अगर (WARN_ON(स_प्रथम(dirent->name, '/', dirent->namelen) != शून्य))
			वापस FOUND_ERR;

		अगर (ff->सूची_पढ़ो.pos == ctx->pos) अणु
			res = FOUND_SOME;
			अगर (!dir_emit(ctx, dirent->name, dirent->namelen,
				      dirent->ino, dirent->type))
				वापस FOUND_ALL;
			ctx->pos = dirent->off;
		पूर्ण
		ff->सूची_पढ़ो.pos = dirent->off;
		ff->सूची_पढ़ो.cache_off += reclen;

		offset += reclen;
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम fuse_rdc_reset(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	fi->rdc.cached = false;
	fi->rdc.version++;
	fi->rdc.size = 0;
	fi->rdc.pos = 0;
पूर्ण

#घोषणा UNCACHED 1

अटल पूर्णांक fuse_सूची_पढ़ो_cached(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	क्रमागत fuse_parse_result res;
	pgoff_t index;
	अचिन्हित पूर्णांक size;
	काष्ठा page *page;
	व्योम *addr;

	/* Seeked?  If so, reset the cache stream */
	अगर (ff->सूची_पढ़ो.pos != ctx->pos) अणु
		ff->सूची_पढ़ो.pos = 0;
		ff->सूची_पढ़ो.cache_off = 0;
	पूर्ण

	/*
	 * We're just about to start पढ़ोing पूर्णांकo the cache or पढ़ोing the
	 * cache; both हालs require an up-to-date mसमय value.
	 */
	अगर (!ctx->pos && fc->स्वतः_inval_data) अणु
		पूर्णांक err = fuse_update_attributes(inode, file);

		अगर (err)
			वापस err;
	पूर्ण

retry:
	spin_lock(&fi->rdc.lock);
retry_locked:
	अगर (!fi->rdc.cached) अणु
		/* Starting cache? Set cache mसमय. */
		अगर (!ctx->pos && !fi->rdc.size) अणु
			fi->rdc.mसमय = inode->i_mसमय;
			fi->rdc.iversion = inode_query_iversion(inode);
		पूर्ण
		spin_unlock(&fi->rdc.lock);
		वापस UNCACHED;
	पूर्ण
	/*
	 * When at the beginning of the directory (i.e. just after सूची_खोलो(3) or
	 * सूची_शुरु(3)), then need to check whether directory contents have
	 * changed, and reset the cache अगर so.
	 */
	अगर (!ctx->pos) अणु
		अगर (inode_peek_iversion(inode) != fi->rdc.iversion ||
		    !बारpec64_equal(&fi->rdc.mसमय, &inode->i_mसमय)) अणु
			fuse_rdc_reset(inode);
			जाओ retry_locked;
		पूर्ण
	पूर्ण

	/*
	 * If cache version changed since the last getdents() call, then reset
	 * the cache stream.
	 */
	अगर (ff->सूची_पढ़ो.version != fi->rdc.version) अणु
		ff->सूची_पढ़ो.pos = 0;
		ff->सूची_पढ़ो.cache_off = 0;
	पूर्ण
	/*
	 * If at the beginning of the cache, than reset version to
	 * current.
	 */
	अगर (ff->सूची_पढ़ो.pos == 0)
		ff->सूची_पढ़ो.version = fi->rdc.version;

	WARN_ON(fi->rdc.size < ff->सूची_पढ़ो.cache_off);

	index = ff->सूची_पढ़ो.cache_off >> PAGE_SHIFT;

	अगर (index == (fi->rdc.size >> PAGE_SHIFT))
		size = fi->rdc.size & ~PAGE_MASK;
	अन्यथा
		size = PAGE_SIZE;
	spin_unlock(&fi->rdc.lock);

	/* खातापूर्ण? */
	अगर ((ff->सूची_पढ़ो.cache_off & ~PAGE_MASK) == size)
		वापस 0;

	page = find_get_page_flags(file->f_mapping, index,
				   FGP_ACCESSED | FGP_LOCK);
	spin_lock(&fi->rdc.lock);
	अगर (!page) अणु
		/*
		 * Uh-oh: page gone missing, cache is useless
		 */
		अगर (fi->rdc.version == ff->सूची_पढ़ो.version)
			fuse_rdc_reset(inode);
		जाओ retry_locked;
	पूर्ण

	/* Make sure it's still the same version after getting the page. */
	अगर (ff->सूची_पढ़ो.version != fi->rdc.version) अणु
		spin_unlock(&fi->rdc.lock);
		unlock_page(page);
		put_page(page);
		जाओ retry;
	पूर्ण
	spin_unlock(&fi->rdc.lock);

	/*
	 * Contents of the page are now रक्षित against changing by holding
	 * the page lock.
	 */
	addr = kmap(page);
	res = fuse_parse_cache(ff, addr, size, ctx);
	kunmap(page);
	unlock_page(page);
	put_page(page);

	अगर (res == FOUND_ERR)
		वापस -EIO;

	अगर (res == FOUND_ALL)
		वापस 0;

	अगर (size == PAGE_SIZE) अणु
		/* We hit end of page: skip to next page. */
		ff->सूची_पढ़ो.cache_off = ALIGN(ff->सूची_पढ़ो.cache_off, PAGE_SIZE);
		जाओ retry;
	पूर्ण

	/*
	 * End of cache reached.  If found position, then we are करोne, otherwise
	 * need to fall back to uncached, since the position we were looking क्रम
	 * wasn't in the cache.
	 */
	वापस res == FOUND_SOME ? 0 : UNCACHED;
पूर्ण

पूर्णांक fuse_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक err;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	mutex_lock(&ff->सूची_पढ़ो.lock);

	err = UNCACHED;
	अगर (ff->खोलो_flags & FOPEN_CACHE_सूची)
		err = fuse_सूची_पढ़ो_cached(file, ctx);
	अगर (err == UNCACHED)
		err = fuse_सूची_पढ़ो_uncached(file, ctx);

	mutex_unlock(&ff->सूची_पढ़ो.lock);

	वापस err;
पूर्ण
