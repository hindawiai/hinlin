<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* dir.c: AFS fileप्रणाली directory handling
 *
 * Copyright (C) 2002, 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sched.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश "internal.h"
#समावेश "afs_fs.h"
#समावेश "xdr_fs.h"

अटल काष्ठा dentry *afs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 अचिन्हित पूर्णांक flags);
अटल पूर्णांक afs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक afs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx);
अटल पूर्णांक afs_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags);
अटल पूर्णांक afs_d_delete(स्थिर काष्ठा dentry *dentry);
अटल व्योम afs_d_iput(काष्ठा dentry *dentry, काष्ठा inode *inode);
अटल पूर्णांक afs_lookup_one_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक nlen,
				  loff_t fpos, u64 ino, अचिन्हित dtype);
अटल पूर्णांक afs_lookup_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक nlen,
			      loff_t fpos, u64 ino, अचिन्हित dtype);
अटल पूर्णांक afs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl);
अटल पूर्णांक afs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode);
अटल पूर्णांक afs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry);
अटल पूर्णांक afs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry);
अटल पूर्णांक afs_link(काष्ठा dentry *from, काष्ठा inode *dir,
		    काष्ठा dentry *dentry);
अटल पूर्णांक afs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, स्थिर अक्षर *content);
अटल पूर्णांक afs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags);
अटल पूर्णांक afs_dir_releasepage(काष्ठा page *page, gfp_t gfp_flags);
अटल व्योम afs_dir_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक length);

अटल पूर्णांक afs_dir_set_page_dirty(काष्ठा page *page)
अणु
	BUG(); /* This should never happen. */
पूर्ण

स्थिर काष्ठा file_operations afs_dir_file_operations = अणु
	.खोलो		= afs_dir_खोलो,
	.release	= afs_release,
	.iterate_shared	= afs_सूची_पढ़ो,
	.lock		= afs_lock,
	.llseek		= generic_file_llseek,
पूर्ण;

स्थिर काष्ठा inode_operations afs_dir_inode_operations = अणु
	.create		= afs_create,
	.lookup		= afs_lookup,
	.link		= afs_link,
	.unlink		= afs_unlink,
	.symlink	= afs_symlink,
	.सूची_गढ़ो		= afs_सूची_गढ़ो,
	.सूची_हटाओ		= afs_सूची_हटाओ,
	.नाम		= afs_नाम,
	.permission	= afs_permission,
	.getattr	= afs_getattr,
	.setattr	= afs_setattr,
पूर्ण;

स्थिर काष्ठा address_space_operations afs_dir_aops = अणु
	.set_page_dirty	= afs_dir_set_page_dirty,
	.releasepage	= afs_dir_releasepage,
	.invalidatepage	= afs_dir_invalidatepage,
पूर्ण;

स्थिर काष्ठा dentry_operations afs_fs_dentry_operations = अणु
	.d_revalidate	= afs_d_revalidate,
	.d_delete	= afs_d_delete,
	.d_release	= afs_d_release,
	.d_स्वतःmount	= afs_d_स्वतःmount,
	.d_iput		= afs_d_iput,
पूर्ण;

काष्ठा afs_lookup_one_cookie अणु
	काष्ठा dir_context	ctx;
	काष्ठा qstr		name;
	bool			found;
	काष्ठा afs_fid		fid;
पूर्ण;

काष्ठा afs_lookup_cookie अणु
	काष्ठा dir_context	ctx;
	काष्ठा qstr		name;
	bool			found;
	bool			one_only;
	अचिन्हित लघु		nr_fids;
	काष्ठा afs_fid		fids[50];
पूर्ण;

/*
 * Drop the refs that we're holding on the pages we were reading into.  We've
 * got refs on the first nr_pages pages.
 */
अटल व्योम afs_dir_पढ़ो_cleanup(काष्ठा afs_पढ़ो *req)
अणु
	काष्ठा address_space *mapping = req->vnode->vfs_inode.i_mapping;
	काष्ठा page *page;
	pgoff_t last = req->nr_pages - 1;

	XA_STATE(xas, &mapping->i_pages, 0);

	अगर (unlikely(!req->nr_pages))
		वापस;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, last) अणु
		अगर (xas_retry(&xas, page))
			जारी;
		BUG_ON(xa_is_value(page));
		BUG_ON(PageCompound(page));
		ASSERTCMP(page->mapping, ==, mapping);

		put_page(page);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * check that a directory page is valid
 */
अटल bool afs_dir_check_page(काष्ठा afs_vnode *dvnode, काष्ठा page *page,
			       loff_t i_size)
अणु
	काष्ठा afs_xdr_dir_page *dbuf;
	loff_t latter, off;
	पूर्णांक पंचांगp, qty;

	/* Determine how many magic numbers there should be in this page, but
	 * we must take care because the directory may change size under us.
	 */
	off = page_offset(page);
	अगर (i_size <= off)
		जाओ checked;

	latter = i_size - off;
	अगर (latter >= PAGE_SIZE)
		qty = PAGE_SIZE;
	अन्यथा
		qty = latter;
	qty /= माप(जोड़ afs_xdr_dir_block);

	/* check them */
	dbuf = kmap_atomic(page);
	क्रम (पंचांगp = 0; पंचांगp < qty; पंचांगp++) अणु
		अगर (dbuf->blocks[पंचांगp].hdr.magic != AFS_सूची_MAGIC) अणु
			prपूर्णांकk("kAFS: %s(%lx): bad magic %d/%d is %04hx\n",
			       __func__, dvnode->vfs_inode.i_ino, पंचांगp, qty,
			       ntohs(dbuf->blocks[पंचांगp].hdr.magic));
			trace_afs_dir_check_failed(dvnode, off, i_size);
			kunmap(page);
			trace_afs_file_error(dvnode, -EIO, afs_file_error_dir_bad_magic);
			जाओ error;
		पूर्ण

		/* Make sure each block is NUL terminated so we can reasonably
		 * use string functions on it.  The filenames in the page
		 * *should* be NUL-terminated anyway.
		 */
		((u8 *)&dbuf->blocks[पंचांगp])[AFS_सूची_BLOCK_SIZE - 1] = 0;
	पूर्ण

	kunmap_atomic(dbuf);

checked:
	afs_stat_v(dvnode, n_पढ़ो_dir);
	वापस true;

error:
	वापस false;
पूर्ण

/*
 * Dump the contents of a directory.
 */
अटल व्योम afs_dir_dump(काष्ठा afs_vnode *dvnode, काष्ठा afs_पढ़ो *req)
अणु
	काष्ठा afs_xdr_dir_page *dbuf;
	काष्ठा address_space *mapping = dvnode->vfs_inode.i_mapping;
	काष्ठा page *page;
	अचिन्हित पूर्णांक i, qty = PAGE_SIZE / माप(जोड़ afs_xdr_dir_block);
	pgoff_t last = req->nr_pages - 1;

	XA_STATE(xas, &mapping->i_pages, 0);

	pr_warn("DIR %llx:%llx f=%llx l=%llx al=%llx\n",
		dvnode->fid.vid, dvnode->fid.vnode,
		req->file_size, req->len, req->actual_len);
	pr_warn("DIR %llx %x %zx %zx\n",
		req->pos, req->nr_pages,
		req->iter->iov_offset,  iov_iter_count(req->iter));

	xas_क्रम_each(&xas, page, last) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		BUG_ON(PageCompound(page));
		BUG_ON(page->mapping != mapping);

		dbuf = kmap_atomic(page);
		क्रम (i = 0; i < qty; i++) अणु
			जोड़ afs_xdr_dir_block *block = &dbuf->blocks[i];

			pr_warn("[%02lx] %32phN\n", page->index * qty + i, block);
		पूर्ण
		kunmap_atomic(dbuf);
	पूर्ण
पूर्ण

/*
 * Check all the pages in a directory.  All the pages are held pinned.
 */
अटल पूर्णांक afs_dir_check(काष्ठा afs_vnode *dvnode, काष्ठा afs_पढ़ो *req)
अणु
	काष्ठा address_space *mapping = dvnode->vfs_inode.i_mapping;
	काष्ठा page *page;
	pgoff_t last = req->nr_pages - 1;
	पूर्णांक ret = 0;

	XA_STATE(xas, &mapping->i_pages, 0);

	अगर (unlikely(!req->nr_pages))
		वापस 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, last) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		BUG_ON(PageCompound(page));
		BUG_ON(page->mapping != mapping);

		अगर (!afs_dir_check_page(dvnode, page, req->file_size)) अणु
			afs_dir_dump(dvnode, req);
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * खोलो an AFS directory file
 */
अटल पूर्णांक afs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	_enter("{%lu}", inode->i_ino);

	BUILD_BUG_ON(माप(जोड़ afs_xdr_dir_block) != 2048);
	BUILD_BUG_ON(माप(जोड़ afs_xdr_dirent) != 32);

	अगर (test_bit(AFS_VNODE_DELETED, &AFS_FS_I(inode)->flags))
		वापस -ENOENT;

	वापस afs_खोलो(inode, file);
पूर्ण

/*
 * Read the directory पूर्णांकo the pagecache in one go, scrubbing the previous
 * contents.  The list of pages is वापसed, pinning them so that they करोn't
 * get reclaimed during the iteration.
 */
अटल काष्ठा afs_पढ़ो *afs_पढ़ो_dir(काष्ठा afs_vnode *dvnode, काष्ठा key *key)
	__acquires(&dvnode->validate_lock)
अणु
	काष्ठा afs_पढ़ो *req;
	loff_t i_size;
	पूर्णांक nr_pages, i, n;
	पूर्णांक ret;

	_enter("");

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	refcount_set(&req->usage, 1);
	req->vnode = dvnode;
	req->key = key_get(key);
	req->cleanup = afs_dir_पढ़ो_cleanup;

expand:
	i_size = i_size_पढ़ो(&dvnode->vfs_inode);
	अगर (i_size < 2048) अणु
		ret = afs_bad(dvnode, afs_file_error_dir_small);
		जाओ error;
	पूर्ण
	अगर (i_size > 2048 * 1024) अणु
		trace_afs_file_error(dvnode, -EFBIG, afs_file_error_dir_big);
		ret = -EFBIG;
		जाओ error;
	पूर्ण

	_enter("%llu", i_size);

	nr_pages = (i_size + PAGE_SIZE - 1) / PAGE_SIZE;

	req->actual_len = i_size; /* May change */
	req->len = nr_pages * PAGE_SIZE; /* We can ask क्रम more than there is */
	req->data_version = dvnode->status.data_version; /* May change */
	iov_iter_xarray(&req->def_iter, READ, &dvnode->vfs_inode.i_mapping->i_pages,
			0, i_size);
	req->iter = &req->def_iter;

	/* Fill in any gaps that we might find where the memory reclaimer has
	 * been at work and pin all the pages.  If there are any gaps, we will
	 * need to reपढ़ो the entire directory contents.
	 */
	i = req->nr_pages;
	जबतक (i < nr_pages) अणु
		काष्ठा page *pages[8], *page;

		n = find_get_pages_contig(dvnode->vfs_inode.i_mapping, i,
					  min_t(अचिन्हित पूर्णांक, nr_pages - i,
						ARRAY_SIZE(pages)),
					  pages);
		_debug("find %u at %u/%u", n, i, nr_pages);

		अगर (n == 0) अणु
			gfp_t gfp = dvnode->vfs_inode.i_mapping->gfp_mask;

			अगर (test_and_clear_bit(AFS_VNODE_सूची_VALID, &dvnode->flags))
				afs_stat_v(dvnode, n_inval);

			ret = -ENOMEM;
			page = __page_cache_alloc(gfp);
			अगर (!page)
				जाओ error;
			ret = add_to_page_cache_lru(page,
						    dvnode->vfs_inode.i_mapping,
						    i, gfp);
			अगर (ret < 0)
				जाओ error;

			attach_page_निजी(page, (व्योम *)1);
			unlock_page(page);
			req->nr_pages++;
			i++;
		पूर्ण अन्यथा अणु
			req->nr_pages += n;
			i += n;
		पूर्ण
	पूर्ण

	/* If we're going to reload, we need to lock all the pages to prevent
	 * races.
	 */
	ret = -ERESTARTSYS;
	अगर (करोwn_पढ़ो_समाप्तable(&dvnode->validate_lock) < 0)
		जाओ error;

	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags))
		जाओ success;

	up_पढ़ो(&dvnode->validate_lock);
	अगर (करोwn_ग_लिखो_समाप्तable(&dvnode->validate_lock) < 0)
		जाओ error;

	अगर (!test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags)) अणु
		trace_afs_reload_dir(dvnode);
		ret = afs_fetch_data(dvnode, req);
		अगर (ret < 0)
			जाओ error_unlock;

		task_io_account_पढ़ो(PAGE_SIZE * req->nr_pages);

		अगर (req->len < req->file_size) अणु
			/* The content has grown, so we need to expand the
			 * buffer.
			 */
			up_ग_लिखो(&dvnode->validate_lock);
			जाओ expand;
		पूर्ण

		/* Validate the data we just पढ़ो. */
		ret = afs_dir_check(dvnode, req);
		अगर (ret < 0)
			जाओ error_unlock;

		// TODO: Trim excess pages

		set_bit(AFS_VNODE_सूची_VALID, &dvnode->flags);
	पूर्ण

	करोwngrade_ग_लिखो(&dvnode->validate_lock);
success:
	वापस req;

error_unlock:
	up_ग_लिखो(&dvnode->validate_lock);
error:
	afs_put_पढ़ो(req);
	_leave(" = %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * deal with one block in an AFS directory
 */
अटल पूर्णांक afs_dir_iterate_block(काष्ठा afs_vnode *dvnode,
				 काष्ठा dir_context *ctx,
				 जोड़ afs_xdr_dir_block *block,
				 अचिन्हित blkoff)
अणु
	जोड़ afs_xdr_dirent *dire;
	अचिन्हित offset, next, curr, nr_slots;
	माप_प्रकार nlen;
	पूर्णांक पंचांगp;

	_enter("%u,%x,%p,,",(अचिन्हित)ctx->pos,blkoff,block);

	curr = (ctx->pos - blkoff) / माप(जोड़ afs_xdr_dirent);

	/* walk through the block, an entry at a समय */
	क्रम (offset = (blkoff == 0 ? AFS_सूची_RESV_BLOCKS0 : AFS_सूची_RESV_BLOCKS);
	     offset < AFS_सूची_SLOTS_PER_BLOCK;
	     offset = next
	     ) अणु
		/* skip entries marked unused in the biपंचांगap */
		अगर (!(block->hdr.biपंचांगap[offset / 8] &
		      (1 << (offset % 8)))) अणु
			_debug("ENT[%zu.%u]: unused",
			       blkoff / माप(जोड़ afs_xdr_dir_block), offset);
			next = offset + 1;
			अगर (offset >= curr)
				ctx->pos = blkoff +
					next * माप(जोड़ afs_xdr_dirent);
			जारी;
		पूर्ण

		/* got a valid entry */
		dire = &block->dirents[offset];
		nlen = strnlen(dire->u.name,
			       माप(*block) -
			       offset * माप(जोड़ afs_xdr_dirent));
		अगर (nlen > AFSNAMEMAX - 1) अणु
			_debug("ENT[%zu]: name too long (len %u/%zu)",
			       blkoff / माप(जोड़ afs_xdr_dir_block),
			       offset, nlen);
			वापस afs_bad(dvnode, afs_file_error_dir_name_too_दीर्घ);
		पूर्ण

		_debug("ENT[%zu.%u]: %s %zu \"%s\"",
		       blkoff / माप(जोड़ afs_xdr_dir_block), offset,
		       (offset < curr ? "skip" : "fill"),
		       nlen, dire->u.name);

		nr_slots = afs_dir_calc_slots(nlen);
		next = offset + nr_slots;
		अगर (next > AFS_सूची_SLOTS_PER_BLOCK) अणु
			_debug("ENT[%zu.%u]:"
			       " %u extends beyond end dir block"
			       " (len %zu)",
			       blkoff / माप(जोड़ afs_xdr_dir_block),
			       offset, next, nlen);
			वापस afs_bad(dvnode, afs_file_error_dir_over_end);
		पूर्ण

		/* Check that the name-extension dirents are all allocated */
		क्रम (पंचांगp = 1; पंचांगp < nr_slots; पंचांगp++) अणु
			अचिन्हित पूर्णांक ix = offset + पंचांगp;
			अगर (!(block->hdr.biपंचांगap[ix / 8] & (1 << (ix % 8)))) अणु
				_debug("ENT[%zu.u]:"
				       " %u unmarked extension (%u/%u)",
				       blkoff / माप(जोड़ afs_xdr_dir_block),
				       offset, पंचांगp, nr_slots);
				वापस afs_bad(dvnode, afs_file_error_dir_unmarked_ext);
			पूर्ण
		पूर्ण

		/* skip अगर starts beक्रमe the current position */
		अगर (offset < curr)
			जारी;

		/* found the next entry */
		अगर (!dir_emit(ctx, dire->u.name, nlen,
			      ntohl(dire->u.vnode),
			      (ctx->actor == afs_lookup_filldir ||
			       ctx->actor == afs_lookup_one_filldir)?
			      ntohl(dire->u.unique) : DT_UNKNOWN)) अणु
			_leave(" = 0 [full]");
			वापस 0;
		पूर्ण

		ctx->pos = blkoff + next * माप(जोड़ afs_xdr_dirent);
	पूर्ण

	_leave(" = 1 [more]");
	वापस 1;
पूर्ण

/*
 * iterate through the data blob that lists the contents of an AFS directory
 */
अटल पूर्णांक afs_dir_iterate(काष्ठा inode *dir, काष्ठा dir_context *ctx,
			   काष्ठा key *key, afs_dataversion_t *_dir_version)
अणु
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	काष्ठा afs_xdr_dir_page *dbuf;
	जोड़ afs_xdr_dir_block *dblock;
	काष्ठा afs_पढ़ो *req;
	काष्ठा page *page;
	अचिन्हित blkoff, limit;
	व्योम __rcu **slot;
	पूर्णांक ret;

	_enter("{%lu},%u,,", dir->i_ino, (अचिन्हित)ctx->pos);

	अगर (test_bit(AFS_VNODE_DELETED, &AFS_FS_I(dir)->flags)) अणु
		_leave(" = -ESTALE");
		वापस -ESTALE;
	पूर्ण

	req = afs_पढ़ो_dir(dvnode, key);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	*_dir_version = req->data_version;

	/* round the file position up to the next entry boundary */
	ctx->pos += माप(जोड़ afs_xdr_dirent) - 1;
	ctx->pos &= ~(माप(जोड़ afs_xdr_dirent) - 1);

	/* walk through the blocks in sequence */
	ret = 0;
	जबतक (ctx->pos < req->actual_len) अणु
		blkoff = ctx->pos & ~(माप(जोड़ afs_xdr_dir_block) - 1);

		/* Fetch the appropriate page from the directory and re-add it
		 * to the LRU.  We have all the pages pinned with an extra ref.
		 */
		rcu_पढ़ो_lock();
		page = शून्य;
		slot = radix_tree_lookup_slot(&dvnode->vfs_inode.i_mapping->i_pages,
					      blkoff / PAGE_SIZE);
		अगर (slot)
			page = radix_tree_deref_slot(slot);
		rcu_पढ़ो_unlock();
		अगर (!page) अणु
			ret = afs_bad(dvnode, afs_file_error_dir_missing_page);
			अवरोध;
		पूर्ण
		mark_page_accessed(page);

		limit = blkoff & ~(PAGE_SIZE - 1);

		dbuf = kmap(page);

		/* deal with the inभागidual blocks stashed on this page */
		करो अणु
			dblock = &dbuf->blocks[(blkoff % PAGE_SIZE) /
					       माप(जोड़ afs_xdr_dir_block)];
			ret = afs_dir_iterate_block(dvnode, ctx, dblock, blkoff);
			अगर (ret != 1) अणु
				kunmap(page);
				जाओ out;
			पूर्ण

			blkoff += माप(जोड़ afs_xdr_dir_block);

		पूर्ण जबतक (ctx->pos < dir->i_size && blkoff < limit);

		kunmap(page);
		ret = 0;
	पूर्ण

out:
	up_पढ़ो(&dvnode->validate_lock);
	afs_put_पढ़ो(req);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * पढ़ो an AFS directory
 */
अटल पूर्णांक afs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	afs_dataversion_t dir_version;

	वापस afs_dir_iterate(file_inode(file), ctx, afs_file_key(file),
			       &dir_version);
पूर्ण

/*
 * Search the directory क्रम a single name
 * - अगर afs_dir_iterate_block() spots this function, it'll pass the FID
 *   uniquअगरier through dtype
 */
अटल पूर्णांक afs_lookup_one_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
				  पूर्णांक nlen, loff_t fpos, u64 ino, अचिन्हित dtype)
अणु
	काष्ठा afs_lookup_one_cookie *cookie =
		container_of(ctx, काष्ठा afs_lookup_one_cookie, ctx);

	_enter("{%s,%u},%s,%u,,%llu,%u",
	       cookie->name.name, cookie->name.len, name, nlen,
	       (अचिन्हित दीर्घ दीर्घ) ino, dtype);

	/* insanity checks first */
	BUILD_BUG_ON(माप(जोड़ afs_xdr_dir_block) != 2048);
	BUILD_BUG_ON(माप(जोड़ afs_xdr_dirent) != 32);

	अगर (cookie->name.len != nlen ||
	    स_भेद(cookie->name.name, name, nlen) != 0) अणु
		_leave(" = 0 [no]");
		वापस 0;
	पूर्ण

	cookie->fid.vnode = ino;
	cookie->fid.unique = dtype;
	cookie->found = 1;

	_leave(" = -1 [found]");
	वापस -1;
पूर्ण

/*
 * Do a lookup of a single name in a directory
 * - just वापसs the FID the dentry name maps to अगर found
 */
अटल पूर्णांक afs_करो_lookup_one(काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा afs_fid *fid, काष्ठा key *key,
			     afs_dataversion_t *_dir_version)
अणु
	काष्ठा afs_super_info *as = dir->i_sb->s_fs_info;
	काष्ठा afs_lookup_one_cookie cookie = अणु
		.ctx.actor = afs_lookup_one_filldir,
		.name = dentry->d_name,
		.fid.vid = as->volume->vid
	पूर्ण;
	पूर्णांक ret;

	_enter("{%lu},%p{%pd},", dir->i_ino, dentry, dentry);

	/* search the directory */
	ret = afs_dir_iterate(dir, &cookie.ctx, key, _dir_version);
	अगर (ret < 0) अणु
		_leave(" = %d [iter]", ret);
		वापस ret;
	पूर्ण

	ret = -ENOENT;
	अगर (!cookie.found) अणु
		_leave(" = -ENOENT [not found]");
		वापस -ENOENT;
	पूर्ण

	*fid = cookie.fid;
	_leave(" = 0 { vn=%llu u=%u }", fid->vnode, fid->unique);
	वापस 0;
पूर्ण

/*
 * search the directory क्रम a name
 * - अगर afs_dir_iterate_block() spots this function, it'll pass the FID
 *   uniquअगरier through dtype
 */
अटल पूर्णांक afs_lookup_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			      पूर्णांक nlen, loff_t fpos, u64 ino, अचिन्हित dtype)
अणु
	काष्ठा afs_lookup_cookie *cookie =
		container_of(ctx, काष्ठा afs_lookup_cookie, ctx);
	पूर्णांक ret;

	_enter("{%s,%u},%s,%u,,%llu,%u",
	       cookie->name.name, cookie->name.len, name, nlen,
	       (अचिन्हित दीर्घ दीर्घ) ino, dtype);

	/* insanity checks first */
	BUILD_BUG_ON(माप(जोड़ afs_xdr_dir_block) != 2048);
	BUILD_BUG_ON(माप(जोड़ afs_xdr_dirent) != 32);

	अगर (cookie->found) अणु
		अगर (cookie->nr_fids < 50) अणु
			cookie->fids[cookie->nr_fids].vnode	= ino;
			cookie->fids[cookie->nr_fids].unique	= dtype;
			cookie->nr_fids++;
		पूर्ण
	पूर्ण अन्यथा अगर (cookie->name.len == nlen &&
		   स_भेद(cookie->name.name, name, nlen) == 0) अणु
		cookie->fids[1].vnode	= ino;
		cookie->fids[1].unique	= dtype;
		cookie->found = 1;
		अगर (cookie->one_only)
			वापस -1;
	पूर्ण

	ret = cookie->nr_fids >= 50 ? -1 : 0;
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Deal with the result of a successful lookup operation.  Turn all the files
 * पूर्णांकo inodes and save the first one - which is the one we actually want.
 */
अटल व्योम afs_करो_lookup_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp;
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;
	u32 पात_code;
	पूर्णांक i;

	_enter("");

	क्रम (i = 0; i < op->nr_files; i++) अणु
		चयन (i) अणु
		हाल 0:
			vp = &op->file[0];
			पात_code = vp->scb.status.पात_code;
			अगर (पात_code != 0) अणु
				op->ac.पात_code = पात_code;
				op->error = afs_पात_to_error(पात_code);
			पूर्ण
			अवरोध;

		हाल 1:
			vp = &op->file[1];
			अवरोध;

		शेष:
			vp = &op->more_files[i - 2];
			अवरोध;
		पूर्ण

		अगर (!vp->scb.have_status && !vp->scb.have_error)
			जारी;

		_debug("do [%u]", i);
		अगर (vp->vnode) अणु
			अगर (!test_bit(AFS_VNODE_UNSET, &vp->vnode->flags))
				afs_vnode_commit_status(op, vp);
		पूर्ण अन्यथा अगर (vp->scb.status.पात_code == 0) अणु
			inode = afs_iget(op, vp);
			अगर (!IS_ERR(inode)) अणु
				vnode = AFS_FS_I(inode);
				afs_cache_permit(vnode, op->key,
						 0 /* Assume vnode->cb_अवरोध is 0 */ +
						 op->cb_v_अवरोध,
						 &vp->scb);
				vp->vnode = vnode;
				vp->put_vnode = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			_debug("- abort %d %llx:%llx.%x",
			       vp->scb.status.पात_code,
			       vp->fid.vid, vp->fid.vnode, vp->fid.unique);
		पूर्ण
	पूर्ण

	_leave("");
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_अंतरभूत_bulk_status_operation = अणु
	.issue_afs_rpc	= afs_fs_अंतरभूत_bulk_status,
	.issue_yfs_rpc	= yfs_fs_अंतरभूत_bulk_status,
	.success	= afs_करो_lookup_success,
पूर्ण;

अटल स्थिर काष्ठा afs_operation_ops afs_lookup_fetch_status_operation = अणु
	.issue_afs_rpc	= afs_fs_fetch_status,
	.issue_yfs_rpc	= yfs_fs_fetch_status,
	.success	= afs_करो_lookup_success,
	.पातed	= afs_check_क्रम_remote_deletion,
पूर्ण;

/*
 * See अगर we know that the server we expect to use करोesn't support
 * FS.InlineBulkStatus.
 */
अटल bool afs_server_supports_ibulk(काष्ठा afs_vnode *dvnode)
अणु
	काष्ठा afs_server_list *slist;
	काष्ठा afs_volume *volume = dvnode->volume;
	काष्ठा afs_server *server;
	bool ret = true;
	पूर्णांक i;

	अगर (!test_bit(AFS_VOLUME_MAYBE_NO_IBULK, &volume->flags))
		वापस true;

	rcu_पढ़ो_lock();
	slist = rcu_dereference(volume->servers);

	क्रम (i = 0; i < slist->nr_servers; i++) अणु
		server = slist->servers[i].server;
		अगर (server == dvnode->cb_server) अणु
			अगर (test_bit(AFS_SERVER_FL_NO_IBULK, &server->flags))
				ret = false;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * Do a lookup in a directory.  We make use of bulk lookup to query a slew of
 * files in one go and create inodes क्रम them.  The inode of the file we were
 * asked क्रम is वापसed.
 */
अटल काष्ठा inode *afs_करो_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   काष्ठा key *key)
अणु
	काष्ठा afs_lookup_cookie *cookie;
	काष्ठा afs_vnode_param *vp;
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir), *vnode;
	काष्ठा inode *inode = शून्य, *ti;
	afs_dataversion_t data_version = READ_ONCE(dvnode->status.data_version);
	दीर्घ ret;
	पूर्णांक i;

	_enter("{%lu},%p{%pd},", dir->i_ino, dentry, dentry);

	cookie = kzalloc(माप(काष्ठा afs_lookup_cookie), GFP_KERNEL);
	अगर (!cookie)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < ARRAY_SIZE(cookie->fids); i++)
		cookie->fids[i].vid = dvnode->fid.vid;
	cookie->ctx.actor = afs_lookup_filldir;
	cookie->name = dentry->d_name;
	cookie->nr_fids = 2; /* slot 0 is saved क्रम the fid we actually want
			      * and slot 1 क्रम the directory */

	अगर (!afs_server_supports_ibulk(dvnode))
		cookie->one_only = true;

	/* search the directory */
	ret = afs_dir_iterate(dir, &cookie->ctx, key, &data_version);
	अगर (ret < 0)
		जाओ out;

	dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)data_version;

	ret = -ENOENT;
	अगर (!cookie->found)
		जाओ out;

	/* Check to see अगर we alपढ़ोy have an inode क्रम the primary fid. */
	inode = ilookup5(dir->i_sb, cookie->fids[1].vnode,
			 afs_ilookup5_test_by_fid, &cookie->fids[1]);
	अगर (inode)
		जाओ out; /* We करो */

	/* Okay, we didn't find it.  We need to query the server - and whilst
	 * we're doing that, we're going to attempt to look up a bunch of other
	 * vnodes also.
	 */
	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ out;
	पूर्ण

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_fid(op, 1, &cookie->fids[1]);

	op->nr_files = cookie->nr_fids;
	_debug("nr_files %u", op->nr_files);

	/* Need space क्रम examining all the selected files */
	op->error = -ENOMEM;
	अगर (op->nr_files > 2) अणु
		op->more_files = kvसुस्मृति(op->nr_files - 2,
					  माप(काष्ठा afs_vnode_param),
					  GFP_KERNEL);
		अगर (!op->more_files)
			जाओ out_op;

		क्रम (i = 2; i < op->nr_files; i++) अणु
			vp = &op->more_files[i - 2];
			vp->fid = cookie->fids[i];

			/* Find any inodes that alपढ़ोy exist and get their
			 * callback counters.
			 */
			ti = ilookup5_noरुको(dir->i_sb, vp->fid.vnode,
					     afs_ilookup5_test_by_fid, &vp->fid);
			अगर (!IS_ERR_OR_शून्य(ti)) अणु
				vnode = AFS_FS_I(ti);
				vp->dv_beक्रमe = vnode->status.data_version;
				vp->cb_अवरोध_beक्रमe = afs_calc_vnode_cb_अवरोध(vnode);
				vp->vnode = vnode;
				vp->put_vnode = true;
				vp->speculative = true; /* vnode not locked */
			पूर्ण
		पूर्ण
	पूर्ण

	/* Try FS.InlineBulkStatus first.  Abort codes क्रम the inभागidual
	 * lookups contained therein are stored in the reply without पातing
	 * the whole operation.
	 */
	op->error = -ENOTSUPP;
	अगर (!cookie->one_only) अणु
		op->ops = &afs_अंतरभूत_bulk_status_operation;
		afs_begin_vnode_operation(op);
		afs_रुको_क्रम_operation(op);
	पूर्ण

	अगर (op->error == -ENOTSUPP) अणु
		/* We could try FS.BulkStatus next, but this पातs the entire
		 * op अगर any of the lookups fails - so, क्रम the moment, revert
		 * to FS.FetchStatus क्रम op->file[1].
		 */
		op->fetch_status.which = 1;
		op->ops = &afs_lookup_fetch_status_operation;
		afs_begin_vnode_operation(op);
		afs_रुको_क्रम_operation(op);
	पूर्ण
	inode = ERR_PTR(op->error);

out_op:
	अगर (op->error == 0) अणु
		inode = &op->file[1].vnode->vfs_inode;
		op->file[1].vnode = शून्य;
	पूर्ण

	अगर (op->file[0].scb.have_status)
		dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)op->file[0].scb.status.data_version;
	अन्यथा
		dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)op->file[0].dv_beक्रमe;
	ret = afs_put_operation(op);
out:
	kमुक्त(cookie);
	_leave("");
	वापस inode ?: ERR_PTR(ret);
पूर्ण

/*
 * Look up an entry in a directory with @sys substitution.
 */
अटल काष्ठा dentry *afs_lookup_atsys(काष्ठा inode *dir, काष्ठा dentry *dentry,
				       काष्ठा key *key)
अणु
	काष्ठा afs_sysnames *subs;
	काष्ठा afs_net *net = afs_i2net(dir);
	काष्ठा dentry *ret;
	अक्षर *buf, *p, *name;
	पूर्णांक len, i;

	_enter("");

	ret = ERR_PTR(-ENOMEM);
	p = buf = kदो_स्मृति(AFSNAMEMAX, GFP_KERNEL);
	अगर (!buf)
		जाओ out_p;
	अगर (dentry->d_name.len > 4) अणु
		स_नकल(p, dentry->d_name.name, dentry->d_name.len - 4);
		p += dentry->d_name.len - 4;
	पूर्ण

	/* There is an ordered list of substitutes that we have to try. */
	पढ़ो_lock(&net->sysnames_lock);
	subs = net->sysnames;
	refcount_inc(&subs->usage);
	पढ़ो_unlock(&net->sysnames_lock);

	क्रम (i = 0; i < subs->nr; i++) अणु
		name = subs->subs[i];
		len = dentry->d_name.len - 4 + म_माप(name);
		अगर (len >= AFSNAMEMAX) अणु
			ret = ERR_PTR(-ENAMETOOLONG);
			जाओ out_s;
		पूर्ण

		म_नकल(p, name);
		ret = lookup_one_len(buf, dentry->d_parent, len);
		अगर (IS_ERR(ret) || d_is_positive(ret))
			जाओ out_s;
		dput(ret);
	पूर्ण

	/* We करोn't want to d_add() the @sys dentry here as we don't want to
	 * the cached dentry to hide changes to the sysnames list.
	 */
	ret = शून्य;
out_s:
	afs_put_sysnames(subs);
	kमुक्त(buf);
out_p:
	key_put(key);
	वापस ret;
पूर्ण

/*
 * look up an entry in a directory
 */
अटल काष्ठा dentry *afs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	काष्ठा afs_fid fid = अणुपूर्ण;
	काष्ठा inode *inode;
	काष्ठा dentry *d;
	काष्ठा key *key;
	पूर्णांक ret;

	_enter("{%llx:%llu},%p{%pd},",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry, dentry);

	ASSERTCMP(d_inode(dentry), ==, शून्य);

	अगर (dentry->d_name.len >= AFSNAMEMAX) अणु
		_leave(" = -ENAMETOOLONG");
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण

	अगर (test_bit(AFS_VNODE_DELETED, &dvnode->flags)) अणु
		_leave(" = -ESTALE");
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	key = afs_request_key(dvnode->volume->cell);
	अगर (IS_ERR(key)) अणु
		_leave(" = %ld [key]", PTR_ERR(key));
		वापस ERR_CAST(key);
	पूर्ण

	ret = afs_validate(dvnode, key);
	अगर (ret < 0) अणु
		key_put(key);
		_leave(" = %d [val]", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (dentry->d_name.len >= 4 &&
	    dentry->d_name.name[dentry->d_name.len - 4] == '@' &&
	    dentry->d_name.name[dentry->d_name.len - 3] == 's' &&
	    dentry->d_name.name[dentry->d_name.len - 2] == 'y' &&
	    dentry->d_name.name[dentry->d_name.len - 1] == 's')
		वापस afs_lookup_atsys(dir, dentry, key);

	afs_stat_v(dvnode, n_lookup);
	inode = afs_करो_lookup(dir, dentry, key);
	key_put(key);
	अगर (inode == ERR_PTR(-ENOENT))
		inode = afs_try_स्वतः_mntpt(dentry, dir);

	अगर (!IS_ERR_OR_शून्य(inode))
		fid = AFS_FS_I(inode)->fid;

	_debug("splice %p", dentry->d_inode);
	d = d_splice_alias(inode, dentry);
	अगर (!IS_ERR_OR_शून्य(d)) अणु
		d->d_fsdata = dentry->d_fsdata;
		trace_afs_lookup(dvnode, &d->d_name, &fid);
	पूर्ण अन्यथा अणु
		trace_afs_lookup(dvnode, &dentry->d_name, &fid);
	पूर्ण
	_leave("");
	वापस d;
पूर्ण

/*
 * Check the validity of a dentry under RCU conditions.
 */
अटल पूर्णांक afs_d_revalidate_rcu(काष्ठा dentry *dentry)
अणु
	काष्ठा afs_vnode *dvnode, *vnode;
	काष्ठा dentry *parent;
	काष्ठा inode *dir, *inode;
	दीर्घ dir_version, de_version;

	_enter("%p", dentry);

	/* Check the parent directory is still valid first. */
	parent = READ_ONCE(dentry->d_parent);
	dir = d_inode_rcu(parent);
	अगर (!dir)
		वापस -ECHILD;
	dvnode = AFS_FS_I(dir);
	अगर (test_bit(AFS_VNODE_DELETED, &dvnode->flags))
		वापस -ECHILD;

	अगर (!afs_check_validity(dvnode))
		वापस -ECHILD;

	/* We only need to invalidate a dentry अगर the server's copy changed
	 * behind our back.  If we made the change, it's no problem.  Note that
	 * on a 32-bit प्रणाली, we only have 32 bits in the dentry to store the
	 * version.
	 */
	dir_version = (दीर्घ)READ_ONCE(dvnode->status.data_version);
	de_version = (दीर्घ)READ_ONCE(dentry->d_fsdata);
	अगर (de_version != dir_version) अणु
		dir_version = (दीर्घ)READ_ONCE(dvnode->invalid_beक्रमe);
		अगर (de_version - dir_version < 0)
			वापस -ECHILD;
	पूर्ण

	/* Check to see अगर the vnode referred to by the dentry still
	 * has a callback.
	 */
	अगर (d_really_is_positive(dentry)) अणु
		inode = d_inode_rcu(dentry);
		अगर (inode) अणु
			vnode = AFS_FS_I(inode);
			अगर (!afs_check_validity(vnode))
				वापस -ECHILD;
		पूर्ण
	पूर्ण

	वापस 1; /* Still valid */
पूर्ण

/*
 * check that a dentry lookup hit has found a valid entry
 * - NOTE! the hit can be a negative hit too, so we can't assume we have an
 *   inode
 */
अटल पूर्णांक afs_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा afs_vnode *vnode, *dir;
	काष्ठा afs_fid fid;
	काष्ठा dentry *parent;
	काष्ठा inode *inode;
	काष्ठा key *key;
	afs_dataversion_t dir_version, invalid_beक्रमe;
	दीर्घ de_version;
	पूर्णांक ret;

	अगर (flags & LOOKUP_RCU)
		वापस afs_d_revalidate_rcu(dentry);

	अगर (d_really_is_positive(dentry)) अणु
		vnode = AFS_FS_I(d_inode(dentry));
		_enter("{v={%llx:%llu} n=%pd fl=%lx},",
		       vnode->fid.vid, vnode->fid.vnode, dentry,
		       vnode->flags);
	पूर्ण अन्यथा अणु
		_enter("{neg n=%pd}", dentry);
	पूर्ण

	key = afs_request_key(AFS_FS_S(dentry->d_sb)->volume->cell);
	अगर (IS_ERR(key))
		key = शून्य;

	अगर (d_really_is_positive(dentry)) अणु
		inode = d_inode(dentry);
		अगर (inode) अणु
			vnode = AFS_FS_I(inode);
			afs_validate(vnode, key);
			अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags))
				जाओ out_bad;
		पूर्ण
	पूर्ण

	/* lock करोwn the parent dentry so we can peer at it */
	parent = dget_parent(dentry);
	dir = AFS_FS_I(d_inode(parent));

	/* validate the parent directory */
	afs_validate(dir, key);

	अगर (test_bit(AFS_VNODE_DELETED, &dir->flags)) अणु
		_debug("%pd: parent dir deleted", dentry);
		जाओ out_bad_parent;
	पूर्ण

	/* We only need to invalidate a dentry अगर the server's copy changed
	 * behind our back.  If we made the change, it's no problem.  Note that
	 * on a 32-bit प्रणाली, we only have 32 bits in the dentry to store the
	 * version.
	 */
	dir_version = dir->status.data_version;
	de_version = (दीर्घ)dentry->d_fsdata;
	अगर (de_version == (दीर्घ)dir_version)
		जाओ out_valid_noupdate;

	invalid_beक्रमe = dir->invalid_beक्रमe;
	अगर (de_version - (दीर्घ)invalid_beक्रमe >= 0)
		जाओ out_valid;

	_debug("dir modified");
	afs_stat_v(dir, n_reval);

	/* search the directory क्रम this vnode */
	ret = afs_करो_lookup_one(&dir->vfs_inode, dentry, &fid, key, &dir_version);
	चयन (ret) अणु
	हाल 0:
		/* the filename maps to something */
		अगर (d_really_is_negative(dentry))
			जाओ out_bad_parent;
		inode = d_inode(dentry);
		अगर (is_bad_inode(inode)) अणु
			prपूर्णांकk("kAFS: afs_d_revalidate: %pd2 has bad inode\n",
			       dentry);
			जाओ out_bad_parent;
		पूर्ण

		vnode = AFS_FS_I(inode);

		/* अगर the vnode ID has changed, then the dirent poपूर्णांकs to a
		 * dअगरferent file */
		अगर (fid.vnode != vnode->fid.vnode) अणु
			_debug("%pd: dirent changed [%llu != %llu]",
			       dentry, fid.vnode,
			       vnode->fid.vnode);
			जाओ not_found;
		पूर्ण

		/* अगर the vnode ID uniqअगरier has changed, then the file has
		 * been deleted and replaced, and the original vnode ID has
		 * been reused */
		अगर (fid.unique != vnode->fid.unique) अणु
			_debug("%pd: file deleted (uq %u -> %u I:%u)",
			       dentry, fid.unique,
			       vnode->fid.unique,
			       vnode->vfs_inode.i_generation);
			ग_लिखो_seqlock(&vnode->cb_lock);
			set_bit(AFS_VNODE_DELETED, &vnode->flags);
			ग_लिखो_sequnlock(&vnode->cb_lock);
			जाओ not_found;
		पूर्ण
		जाओ out_valid;

	हाल -ENOENT:
		/* the filename is unknown */
		_debug("%pd: dirent not found", dentry);
		अगर (d_really_is_positive(dentry))
			जाओ not_found;
		जाओ out_valid;

	शेष:
		_debug("failed to iterate dir %pd: %d",
		       parent, ret);
		जाओ out_bad_parent;
	पूर्ण

out_valid:
	dentry->d_fsdata = (व्योम *)(अचिन्हित दीर्घ)dir_version;
out_valid_noupdate:
	dput(parent);
	key_put(key);
	_leave(" = 1 [valid]");
	वापस 1;

	/* the dirent, अगर it exists, now poपूर्णांकs to a dअगरferent vnode */
not_found:
	spin_lock(&dentry->d_lock);
	dentry->d_flags |= DCACHE_NFSFS_RENAMED;
	spin_unlock(&dentry->d_lock);

out_bad_parent:
	_debug("dropping dentry %pd2", dentry);
	dput(parent);
out_bad:
	key_put(key);

	_leave(" = 0 [bad]");
	वापस 0;
पूर्ण

/*
 * allow the VFS to enquire as to whether a dentry should be unhashed (mustn't
 * sleep)
 * - called from dput() when d_count is going to 0.
 * - वापस 1 to request dentry be unhashed, 0 otherwise
 */
अटल पूर्णांक afs_d_delete(स्थिर काष्ठा dentry *dentry)
अणु
	_enter("%pd", dentry);

	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		जाओ zap;

	अगर (d_really_is_positive(dentry) &&
	    (test_bit(AFS_VNODE_DELETED,   &AFS_FS_I(d_inode(dentry))->flags) ||
	     test_bit(AFS_VNODE_PSEUDOसूची, &AFS_FS_I(d_inode(dentry))->flags)))
		जाओ zap;

	_leave(" = 0 [keep]");
	वापस 0;

zap:
	_leave(" = 1 [zap]");
	वापस 1;
पूर्ण

/*
 * Clean up sillyनाम files on dentry removal.
 */
अटल व्योम afs_d_iput(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		afs_silly_iput(dentry, inode);
	iput(inode);
पूर्ण

/*
 * handle dentry release
 */
व्योम afs_d_release(काष्ठा dentry *dentry)
अणु
	_enter("%pd", dentry);
पूर्ण

व्योम afs_check_क्रम_remote_deletion(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;

	चयन (op->ac.पात_code) अणु
	हाल VNOVNODE:
		set_bit(AFS_VNODE_DELETED, &vnode->flags);
		afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_deleted);
	पूर्ण
पूर्ण

/*
 * Create a new inode क्रम create/सूची_गढ़ो/symlink
 */
अटल व्योम afs_vnode_new_inode(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;

	_enter("");

	ASSERTCMP(op->error, ==, 0);

	inode = afs_iget(op, vp);
	अगर (IS_ERR(inode)) अणु
		/* ENOMEM or EINTR at a really inconvenient समय - just abanकरोn
		 * the new directory on the server.
		 */
		op->error = PTR_ERR(inode);
		वापस;
	पूर्ण

	vnode = AFS_FS_I(inode);
	set_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	अगर (!op->error)
		afs_cache_permit(vnode, op->key, vnode->cb_अवरोध, &vp->scb);
	d_instantiate(op->dentry, inode);
पूर्ण

अटल व्योम afs_create_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	op->स_समय = op->file[0].scb.status.mसमय_client;
	afs_vnode_commit_status(op, &op->file[0]);
	afs_update_dentry_version(op, &op->file[0], op->dentry);
	afs_vnode_new_inode(op);
पूर्ण

अटल व्योम afs_create_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_vnode *dvnode = dvp->vnode;

	_enter("op=%08x", op->debug_id);

	करोwn_ग_लिखो(&dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags) &&
	    dvnode->status.data_version == dvp->dv_beक्रमe + dvp->dv_delta)
		afs_edit_dir_add(dvnode, &op->dentry->d_name, &vp->fid,
				 op->create.reason);
	up_ग_लिखो(&dvnode->validate_lock);
पूर्ण

अटल व्योम afs_create_put(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);

	अगर (op->error)
		d_drop(op->dentry);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_सूची_गढ़ो_operation = अणु
	.issue_afs_rpc	= afs_fs_make_dir,
	.issue_yfs_rpc	= yfs_fs_make_dir,
	.success	= afs_create_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_create_edit_dir,
	.put		= afs_create_put,
पूर्ण;

/*
 * create a directory on an AFS fileप्रणाली
 */
अटल पूर्णांक afs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);

	_enter("{%llx:%llu},{%pd},%ho",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry, mode);

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op)) अणु
		d_drop(dentry);
		वापस PTR_ERR(op);
	पूर्ण

	afs_op_set_vnode(op, 0, dvnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;
	op->dentry	= dentry;
	op->create.mode	= S_IFसूची | mode;
	op->create.reason = afs_edit_dir_क्रम_सूची_गढ़ो;
	op->ops		= &afs_सूची_गढ़ो_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

/*
 * Remove a subdir from a directory.
 */
अटल व्योम afs_dir_हटाओ_subdir(काष्ठा dentry *dentry)
अणु
	अगर (d_really_is_positive(dentry)) अणु
		काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(dentry));

		clear_nlink(&vnode->vfs_inode);
		set_bit(AFS_VNODE_DELETED, &vnode->flags);
		clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
		clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags);
	पूर्ण
पूर्ण

अटल व्योम afs_सूची_हटाओ_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	op->स_समय = op->file[0].scb.status.mसमय_client;
	afs_vnode_commit_status(op, &op->file[0]);
	afs_update_dentry_version(op, &op->file[0], op->dentry);
पूर्ण

अटल व्योम afs_सूची_हटाओ_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode *dvnode = dvp->vnode;

	_enter("op=%08x", op->debug_id);
	afs_dir_हटाओ_subdir(op->dentry);

	करोwn_ग_लिखो(&dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags) &&
	    dvnode->status.data_version == dvp->dv_beक्रमe + dvp->dv_delta)
		afs_edit_dir_हटाओ(dvnode, &op->dentry->d_name,
				    afs_edit_dir_क्रम_सूची_हटाओ);
	up_ग_लिखो(&dvnode->validate_lock);
पूर्ण

अटल व्योम afs_सूची_हटाओ_put(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	अगर (op->file[1].vnode)
		up_ग_लिखो(&op->file[1].vnode->सूची_हटाओ_lock);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_सूची_हटाओ_operation = अणु
	.issue_afs_rpc	= afs_fs_हटाओ_dir,
	.issue_yfs_rpc	= yfs_fs_हटाओ_dir,
	.success	= afs_सूची_हटाओ_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_सूची_हटाओ_edit_dir,
	.put		= afs_सूची_हटाओ_put,
पूर्ण;

/*
 * हटाओ a directory from an AFS fileप्रणाली
 */
अटल पूर्णांक afs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir), *vnode = शून्य;
	पूर्णांक ret;

	_enter("{%llx:%llu},{%pd}",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry);

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, dvnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;

	op->dentry	= dentry;
	op->ops		= &afs_सूची_हटाओ_operation;

	/* Try to make sure we have a callback promise on the victim. */
	अगर (d_really_is_positive(dentry)) अणु
		vnode = AFS_FS_I(d_inode(dentry));
		ret = afs_validate(vnode, op->key);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	अगर (vnode) अणु
		ret = करोwn_ग_लिखो_समाप्तable(&vnode->सूची_हटाओ_lock);
		अगर (ret < 0)
			जाओ error;
		op->file[1].vnode = vnode;
	पूर्ण

	वापस afs_करो_sync_operation(op);

error:
	वापस afs_put_operation(op);
पूर्ण

/*
 * Remove a link to a file or symlink from a directory.
 *
 * If the file was not deleted due to excess hard links, the fileserver will
 * अवरोध the callback promise on the file - अगर it had one - beक्रमe it वापसs
 * to us, and अगर it was deleted, it won't
 *
 * However, अगर we didn't have a callback promise outstanding, or it was
 * outstanding on a dअगरferent server, then it won't अवरोध it either...
 */
अटल व्योम afs_dir_हटाओ_link(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *dvnode = op->file[0].vnode;
	काष्ठा afs_vnode *vnode = op->file[1].vnode;
	काष्ठा dentry *dentry = op->dentry;
	पूर्णांक ret;

	अगर (op->error != 0 ||
	    (op->file[1].scb.have_status && op->file[1].scb.have_error))
		वापस;
	अगर (d_really_is_positive(dentry))
		वापस;

	अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags)) अणु
		/* Alपढ़ोy करोne */
	पूर्ण अन्यथा अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags)) अणु
		ग_लिखो_seqlock(&vnode->cb_lock);
		drop_nlink(&vnode->vfs_inode);
		अगर (vnode->vfs_inode.i_nlink == 0) अणु
			set_bit(AFS_VNODE_DELETED, &vnode->flags);
			__afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_unlink);
		पूर्ण
		ग_लिखो_sequnlock(&vnode->cb_lock);
	पूर्ण अन्यथा अणु
		afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_unlink);

		अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags))
			_debug("AFS_VNODE_DELETED");

		ret = afs_validate(vnode, op->key);
		अगर (ret != -ESTALE)
			op->error = ret;
	पूर्ण

	_debug("nlink %d [val %d]", vnode->vfs_inode.i_nlink, op->error);
पूर्ण

अटल व्योम afs_unlink_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	op->स_समय = op->file[0].scb.status.mसमय_client;
	afs_check_dir_conflict(op, &op->file[0]);
	afs_vnode_commit_status(op, &op->file[0]);
	afs_vnode_commit_status(op, &op->file[1]);
	afs_update_dentry_version(op, &op->file[0], op->dentry);
	afs_dir_हटाओ_link(op);
पूर्ण

अटल व्योम afs_unlink_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode *dvnode = dvp->vnode;

	_enter("op=%08x", op->debug_id);
	करोwn_ग_लिखो(&dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags) &&
	    dvnode->status.data_version == dvp->dv_beक्रमe + dvp->dv_delta)
		afs_edit_dir_हटाओ(dvnode, &op->dentry->d_name,
				    afs_edit_dir_क्रम_unlink);
	up_ग_लिखो(&dvnode->validate_lock);
पूर्ण

अटल व्योम afs_unlink_put(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	अगर (op->unlink.need_rehash && op->error < 0 && op->error != -ENOENT)
		d_rehash(op->dentry);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_unlink_operation = अणु
	.issue_afs_rpc	= afs_fs_हटाओ_file,
	.issue_yfs_rpc	= yfs_fs_हटाओ_file,
	.success	= afs_unlink_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_unlink_edit_dir,
	.put		= afs_unlink_put,
पूर्ण;

/*
 * Remove a file or symlink from an AFS fileप्रणाली.
 */
अटल पूर्णांक afs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(dentry));
	पूर्णांक ret;

	_enter("{%llx:%llu},{%pd}",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry);

	अगर (dentry->d_name.len >= AFSNAMEMAX)
		वापस -ENAMETOOLONG;

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, dvnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;

	/* Try to make sure we have a callback promise on the victim. */
	ret = afs_validate(vnode, op->key);
	अगर (ret < 0) अणु
		op->error = ret;
		जाओ error;
	पूर्ण

	spin_lock(&dentry->d_lock);
	अगर (d_count(dentry) > 1) अणु
		spin_unlock(&dentry->d_lock);
		/* Start asynchronous ग_लिखोout of the inode */
		ग_लिखो_inode_now(d_inode(dentry), 0);
		op->error = afs_sillyनाम(dvnode, vnode, dentry, op->key);
		जाओ error;
	पूर्ण
	अगर (!d_unhashed(dentry)) अणु
		/* Prevent a race with RCU lookup. */
		__d_drop(dentry);
		op->unlink.need_rehash = true;
	पूर्ण
	spin_unlock(&dentry->d_lock);

	op->file[1].vnode = vnode;
	op->file[1].update_स_समय = true;
	op->file[1].op_unlinked = true;
	op->dentry	= dentry;
	op->ops		= &afs_unlink_operation;
	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);

	/* If there was a conflict with a third party, check the status of the
	 * unlinked vnode.
	 */
	अगर (op->error == 0 && (op->flags & AFS_OPERATION_सूची_CONFLICT)) अणु
		op->file[1].update_स_समय = false;
		op->fetch_status.which = 1;
		op->ops = &afs_fetch_status_operation;
		afs_begin_vnode_operation(op);
		afs_रुको_क्रम_operation(op);
	पूर्ण

	वापस afs_put_operation(op);

error:
	वापस afs_put_operation(op);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_create_operation = अणु
	.issue_afs_rpc	= afs_fs_create_file,
	.issue_yfs_rpc	= yfs_fs_create_file,
	.success	= afs_create_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_create_edit_dir,
	.put		= afs_create_put,
पूर्ण;

/*
 * create a regular file on an AFS fileप्रणाली
 */
अटल पूर्णांक afs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	पूर्णांक ret = -ENAMETOOLONG;

	_enter("{%llx:%llu},{%pd},%ho",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry, mode);

	अगर (dentry->d_name.len >= AFSNAMEMAX)
		जाओ error;

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ error;
	पूर्ण

	afs_op_set_vnode(op, 0, dvnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;

	op->dentry	= dentry;
	op->create.mode	= S_IFREG | mode;
	op->create.reason = afs_edit_dir_क्रम_create;
	op->ops		= &afs_create_operation;
	वापस afs_करो_sync_operation(op);

error:
	d_drop(dentry);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल व्योम afs_link_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];

	_enter("op=%08x", op->debug_id);
	op->स_समय = dvp->scb.status.mसमय_client;
	afs_vnode_commit_status(op, dvp);
	afs_vnode_commit_status(op, vp);
	afs_update_dentry_version(op, dvp, op->dentry);
	अगर (op->dentry_2->d_parent == op->dentry->d_parent)
		afs_update_dentry_version(op, dvp, op->dentry_2);
	ihold(&vp->vnode->vfs_inode);
	d_instantiate(op->dentry, &vp->vnode->vfs_inode);
पूर्ण

अटल व्योम afs_link_put(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	अगर (op->error)
		d_drop(op->dentry);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_link_operation = अणु
	.issue_afs_rpc	= afs_fs_link,
	.issue_yfs_rpc	= yfs_fs_link,
	.success	= afs_link_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_create_edit_dir,
	.put		= afs_link_put,
पूर्ण;

/*
 * create a hard link between files in an AFS fileप्रणाली
 */
अटल पूर्णांक afs_link(काष्ठा dentry *from, काष्ठा inode *dir,
		    काष्ठा dentry *dentry)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(from));
	पूर्णांक ret = -ENAMETOOLONG;

	_enter("{%llx:%llu},{%llx:%llu},{%pd}",
	       vnode->fid.vid, vnode->fid.vnode,
	       dvnode->fid.vid, dvnode->fid.vnode,
	       dentry);

	अगर (dentry->d_name.len >= AFSNAMEMAX)
		जाओ error;

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ error;
	पूर्ण

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, vnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;
	op->file[1].update_स_समय = true;

	op->dentry		= dentry;
	op->dentry_2		= from;
	op->ops			= &afs_link_operation;
	op->create.reason	= afs_edit_dir_क्रम_link;
	वापस afs_करो_sync_operation(op);

error:
	d_drop(dentry);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_symlink_operation = अणु
	.issue_afs_rpc	= afs_fs_symlink,
	.issue_yfs_rpc	= yfs_fs_symlink,
	.success	= afs_create_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_create_edit_dir,
	.put		= afs_create_put,
पूर्ण;

/*
 * create a symlink in an AFS fileप्रणाली
 */
अटल पूर्णांक afs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, स्थिर अक्षर *content)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *dvnode = AFS_FS_I(dir);
	पूर्णांक ret;

	_enter("{%llx:%llu},{%pd},%s",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry,
	       content);

	ret = -ENAMETOOLONG;
	अगर (dentry->d_name.len >= AFSNAMEMAX)
		जाओ error;

	ret = -EINVAL;
	अगर (म_माप(content) >= AFSPATHMAX)
		जाओ error;

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ error;
	पूर्ण

	afs_op_set_vnode(op, 0, dvnode);
	op->file[0].dv_delta = 1;

	op->dentry		= dentry;
	op->ops			= &afs_symlink_operation;
	op->create.reason	= afs_edit_dir_क्रम_symlink;
	op->create.symlink	= content;
	वापस afs_करो_sync_operation(op);

error:
	d_drop(dentry);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल व्योम afs_नाम_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);

	op->स_समय = op->file[0].scb.status.mसमय_client;
	afs_check_dir_conflict(op, &op->file[1]);
	afs_vnode_commit_status(op, &op->file[0]);
	अगर (op->file[1].vnode != op->file[0].vnode) अणु
		op->स_समय = op->file[1].scb.status.mसमय_client;
		afs_vnode_commit_status(op, &op->file[1]);
	पूर्ण
पूर्ण

अटल व्योम afs_नाम_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *orig_dvp = &op->file[0];
	काष्ठा afs_vnode_param *new_dvp = &op->file[1];
	काष्ठा afs_vnode *orig_dvnode = orig_dvp->vnode;
	काष्ठा afs_vnode *new_dvnode = new_dvp->vnode;
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(op->dentry));
	काष्ठा dentry *old_dentry = op->dentry;
	काष्ठा dentry *new_dentry = op->dentry_2;
	काष्ठा inode *new_inode;

	_enter("op=%08x", op->debug_id);

	अगर (op->नाम.rehash) अणु
		d_rehash(op->नाम.rehash);
		op->नाम.rehash = शून्य;
	पूर्ण

	करोwn_ग_लिखो(&orig_dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &orig_dvnode->flags) &&
	    orig_dvnode->status.data_version == orig_dvp->dv_beक्रमe + orig_dvp->dv_delta)
		afs_edit_dir_हटाओ(orig_dvnode, &old_dentry->d_name,
				    afs_edit_dir_क्रम_नाम_0);

	अगर (new_dvnode != orig_dvnode) अणु
		up_ग_लिखो(&orig_dvnode->validate_lock);
		करोwn_ग_लिखो(&new_dvnode->validate_lock);
	पूर्ण

	अगर (test_bit(AFS_VNODE_सूची_VALID, &new_dvnode->flags) &&
	    new_dvnode->status.data_version == new_dvp->dv_beक्रमe + new_dvp->dv_delta) अणु
		अगर (!op->नाम.new_negative)
			afs_edit_dir_हटाओ(new_dvnode, &new_dentry->d_name,
					    afs_edit_dir_क्रम_नाम_1);

		afs_edit_dir_add(new_dvnode, &new_dentry->d_name,
				 &vnode->fid, afs_edit_dir_क्रम_नाम_2);
	पूर्ण

	new_inode = d_inode(new_dentry);
	अगर (new_inode) अणु
		spin_lock(&new_inode->i_lock);
		अगर (S_ISसूची(new_inode->i_mode))
			clear_nlink(new_inode);
		अन्यथा अगर (new_inode->i_nlink > 0)
			drop_nlink(new_inode);
		spin_unlock(&new_inode->i_lock);
	पूर्ण

	/* Now we can update d_fsdata on the dentries to reflect their
	 * new parent's data_version.
	 *
	 * Note that अगर we ever implement RENAME_EXCHANGE, we'll have
	 * to update both dentries with opposing dir versions.
	 */
	afs_update_dentry_version(op, new_dvp, op->dentry);
	afs_update_dentry_version(op, new_dvp, op->dentry_2);

	d_move(old_dentry, new_dentry);

	up_ग_लिखो(&new_dvnode->validate_lock);
पूर्ण

अटल व्योम afs_नाम_put(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	अगर (op->नाम.rehash)
		d_rehash(op->नाम.rehash);
	dput(op->नाम.पंचांगp);
	अगर (op->error)
		d_rehash(op->dentry);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_नाम_operation = अणु
	.issue_afs_rpc	= afs_fs_नाम,
	.issue_yfs_rpc	= yfs_fs_नाम,
	.success	= afs_नाम_success,
	.edit_dir	= afs_नाम_edit_dir,
	.put		= afs_नाम_put,
पूर्ण;

/*
 * नाम a file in an AFS fileप्रणाली and/or move it between directories
 */
अटल पूर्णांक afs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *orig_dvnode, *new_dvnode, *vnode;
	पूर्णांक ret;

	अगर (flags)
		वापस -EINVAL;

	/* Don't allow silly-नाम files be moved around. */
	अगर (old_dentry->d_flags & DCACHE_NFSFS_RENAMED)
		वापस -EINVAL;

	vnode = AFS_FS_I(d_inode(old_dentry));
	orig_dvnode = AFS_FS_I(old_dir);
	new_dvnode = AFS_FS_I(new_dir);

	_enter("{%llx:%llu},{%llx:%llu},{%llx:%llu},{%pd}",
	       orig_dvnode->fid.vid, orig_dvnode->fid.vnode,
	       vnode->fid.vid, vnode->fid.vnode,
	       new_dvnode->fid.vid, new_dvnode->fid.vnode,
	       new_dentry);

	op = afs_alloc_operation(शून्य, orig_dvnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, orig_dvnode);
	afs_op_set_vnode(op, 1, new_dvnode); /* May be same as orig_dvnode */
	op->file[0].dv_delta = 1;
	op->file[1].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[1].modअगरication = true;
	op->file[0].update_स_समय = true;
	op->file[1].update_स_समय = true;

	op->dentry		= old_dentry;
	op->dentry_2		= new_dentry;
	op->नाम.new_negative	= d_is_negative(new_dentry);
	op->ops			= &afs_नाम_operation;

	/* For non-directories, check whether the target is busy and अगर so,
	 * make a copy of the dentry and then करो a silly-नाम.  If the
	 * silly-नाम succeeds, the copied dentry is hashed and becomes the
	 * new target.
	 */
	अगर (d_is_positive(new_dentry) && !d_is_dir(new_dentry)) अणु
		/* To prevent any new references to the target during the
		 * नाम, we unhash the dentry in advance.
		 */
		अगर (!d_unhashed(new_dentry)) अणु
			d_drop(new_dentry);
			op->नाम.rehash = new_dentry;
		पूर्ण

		अगर (d_count(new_dentry) > 2) अणु
			/* copy the target dentry's name */
			ret = -ENOMEM;
			op->नाम.पंचांगp = d_alloc(new_dentry->d_parent,
						 &new_dentry->d_name);
			अगर (!op->नाम.पंचांगp)
				जाओ error;

			ret = afs_sillyनाम(new_dvnode,
					      AFS_FS_I(d_inode(new_dentry)),
					      new_dentry, op->key);
			अगर (ret)
				जाओ error;

			op->dentry_2 = op->नाम.पंचांगp;
			op->नाम.rehash = शून्य;
			op->नाम.new_negative = true;
		पूर्ण
	पूर्ण

	/* This bit is potentially nasty as there's a potential race with
	 * afs_d_revalidateअणु,_rcuपूर्ण().  We have to change d_fsdata on the dentry
	 * to reflect it's new parent's new data_version after the op, but
	 * d_revalidate may see old_dentry between the op having taken place
	 * and the version being updated.
	 *
	 * So drop the old_dentry क्रम now to make other thपढ़ोs go through
	 * lookup instead - which we hold a lock against.
	 */
	d_drop(old_dentry);

	वापस afs_करो_sync_operation(op);

error:
	वापस afs_put_operation(op);
पूर्ण

/*
 * Release a directory page and clean up its निजी state अगर it's not busy
 * - वापस true अगर the page can now be released, false अगर not
 */
अटल पूर्णांक afs_dir_releasepage(काष्ठा page *page, gfp_t gfp_flags)
अणु
	काष्ठा afs_vnode *dvnode = AFS_FS_I(page->mapping->host);

	_enter("{{%llx:%llu}[%lu]}", dvnode->fid.vid, dvnode->fid.vnode, page->index);

	detach_page_निजी(page);

	/* The directory will need reloading. */
	अगर (test_and_clear_bit(AFS_VNODE_सूची_VALID, &dvnode->flags))
		afs_stat_v(dvnode, n_relpg);
	वापस 1;
पूर्ण

/*
 * invalidate part or all of a page
 * - release a page and clean up its निजी data अगर offset is 0 (indicating
 *   the entire page)
 */
अटल व्योम afs_dir_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक length)
अणु
	काष्ठा afs_vnode *dvnode = AFS_FS_I(page->mapping->host);

	_enter("{%lu},%u,%u", page->index, offset, length);

	BUG_ON(!PageLocked(page));

	/* The directory will need reloading. */
	अगर (test_and_clear_bit(AFS_VNODE_सूची_VALID, &dvnode->flags))
		afs_stat_v(dvnode, n_inval);

	/* we clean up only अगर the entire page is being invalidated */
	अगर (offset == 0 && length == thp_size(page))
		detach_page_निजी(page);
पूर्ण
