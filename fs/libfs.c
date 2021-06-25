<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	fs/libfs.c
 *	Library क्रम fileप्रणालीs ग_लिखोrs.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/export.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/mount.h>
#समावेश <linux/vfs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/namei.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/buffer_head.h> /* sync_mapping_buffers */
#समावेश <linux/fs_context.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/unicode.h>
#समावेश <linux/fscrypt.h>

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

पूर्णांक simple_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		   काष्ठा kstat *stat, u32 request_mask,
		   अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	generic_fillattr(&init_user_ns, inode, stat);
	stat->blocks = inode->i_mapping->nrpages << (PAGE_SHIFT - 9);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_getattr);

पूर्णांक simple_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	buf->f_type = dentry->d_sb->s_magic;
	buf->f_bsize = PAGE_SIZE;
	buf->f_namelen = NAME_MAX;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_statfs);

/*
 * Retaining negative dentries क्रम an in-memory fileप्रणाली just wastes
 * memory and lookup समय: arrange क्रम them to be deleted immediately.
 */
पूर्णांक always_delete_dentry(स्थिर काष्ठा dentry *dentry)
अणु
	वापस 1;
पूर्ण
EXPORT_SYMBOL(always_delete_dentry);

स्थिर काष्ठा dentry_operations simple_dentry_operations = अणु
	.d_delete = always_delete_dentry,
पूर्ण;
EXPORT_SYMBOL(simple_dentry_operations);

/*
 * Lookup the data. This is trivial - अगर the dentry didn't alपढ़ोy
 * exist, we know it is negative.  Set d_op to delete negative dentries.
 */
काष्ठा dentry *simple_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (dentry->d_name.len > NAME_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);
	अगर (!dentry->d_sb->s_d_op)
		d_set_d_op(dentry, &simple_dentry_operations);
	d_add(dentry, शून्य);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(simple_lookup);

पूर्णांक dcache_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = d_alloc_cursor(file->f_path.dentry);

	वापस file->निजी_data ? 0 : -ENOMEM;
पूर्ण
EXPORT_SYMBOL(dcache_dir_खोलो);

पूर्णांक dcache_dir_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	dput(file->निजी_data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dcache_dir_बंद);

/* parent is locked at least shared */
/*
 * Returns an element of siblings' list.
 * We are looking क्रम <count>th positive after <p>; अगर
 * found, dentry is grabbed and वापसed to caller.
 * If no such element exists, शून्य is वापसed.
 */
अटल काष्ठा dentry *scan_positives(काष्ठा dentry *cursor,
					काष्ठा list_head *p,
					loff_t count,
					काष्ठा dentry *last)
अणु
	काष्ठा dentry *dentry = cursor->d_parent, *found = शून्य;

	spin_lock(&dentry->d_lock);
	जबतक ((p = p->next) != &dentry->d_subdirs) अणु
		काष्ठा dentry *d = list_entry(p, काष्ठा dentry, d_child);
		// we must at least skip cursors, to aव्योम livelocks
		अगर (d->d_flags & DCACHE_DENTRY_CURSOR)
			जारी;
		अगर (simple_positive(d) && !--count) अणु
			spin_lock_nested(&d->d_lock, DENTRY_D_LOCK_NESTED);
			अगर (simple_positive(d))
				found = dget_dlock(d);
			spin_unlock(&d->d_lock);
			अगर (likely(found))
				अवरोध;
			count = 1;
		पूर्ण
		अगर (need_resched()) अणु
			list_move(&cursor->d_child, p);
			p = &cursor->d_child;
			spin_unlock(&dentry->d_lock);
			cond_resched();
			spin_lock(&dentry->d_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&dentry->d_lock);
	dput(last);
	वापस found;
पूर्ण

loff_t dcache_dir_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	चयन (whence) अणु
		हाल 1:
			offset += file->f_pos;
			fallthrough;
		हाल 0:
			अगर (offset >= 0)
				अवरोध;
			fallthrough;
		शेष:
			वापस -EINVAL;
	पूर्ण
	अगर (offset != file->f_pos) अणु
		काष्ठा dentry *cursor = file->निजी_data;
		काष्ठा dentry *to = शून्य;

		inode_lock_shared(dentry->d_inode);

		अगर (offset > 2)
			to = scan_positives(cursor, &dentry->d_subdirs,
					    offset - 2, शून्य);
		spin_lock(&dentry->d_lock);
		अगर (to)
			list_move(&cursor->d_child, &to->d_child);
		अन्यथा
			list_del_init(&cursor->d_child);
		spin_unlock(&dentry->d_lock);
		dput(to);

		file->f_pos = offset;

		inode_unlock_shared(dentry->d_inode);
	पूर्ण
	वापस offset;
पूर्ण
EXPORT_SYMBOL(dcache_dir_lseek);

/* Relationship between i_mode and the DT_xxx types */
अटल अंतरभूत अचिन्हित अक्षर dt_type(काष्ठा inode *inode)
अणु
	वापस (inode->i_mode >> 12) & 15;
पूर्ण

/*
 * Directory is locked and all positive dentries in it are safe, since
 * क्रम ramfs-type trees they can't go away without unlink() or सूची_हटाओ(),
 * both impossible due to the lock on directory.
 */

पूर्णांक dcache_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा dentry *cursor = file->निजी_data;
	काष्ठा list_head *anchor = &dentry->d_subdirs;
	काष्ठा dentry *next = शून्य;
	काष्ठा list_head *p;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;

	अगर (ctx->pos == 2)
		p = anchor;
	अन्यथा अगर (!list_empty(&cursor->d_child))
		p = &cursor->d_child;
	अन्यथा
		वापस 0;

	जबतक ((next = scan_positives(cursor, p, 1, next)) != शून्य) अणु
		अगर (!dir_emit(ctx, next->d_name.name, next->d_name.len,
			      d_inode(next)->i_ino, dt_type(d_inode(next))))
			अवरोध;
		ctx->pos++;
		p = &next->d_child;
	पूर्ण
	spin_lock(&dentry->d_lock);
	अगर (next)
		list_move_tail(&cursor->d_child, &next->d_child);
	अन्यथा
		list_del_init(&cursor->d_child);
	spin_unlock(&dentry->d_lock);
	dput(next);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dcache_सूची_पढ़ो);

sमाप_प्रकार generic_पढ़ो_dir(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार siz, loff_t *ppos)
अणु
	वापस -EISसूची;
पूर्ण
EXPORT_SYMBOL(generic_पढ़ो_dir);

स्थिर काष्ठा file_operations simple_dir_operations = अणु
	.खोलो		= dcache_dir_खोलो,
	.release	= dcache_dir_बंद,
	.llseek		= dcache_dir_lseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= dcache_सूची_पढ़ो,
	.fsync		= noop_fsync,
पूर्ण;
EXPORT_SYMBOL(simple_dir_operations);

स्थिर काष्ठा inode_operations simple_dir_inode_operations = अणु
	.lookup		= simple_lookup,
पूर्ण;
EXPORT_SYMBOL(simple_dir_inode_operations);

अटल काष्ठा dentry *find_next_child(काष्ठा dentry *parent, काष्ठा dentry *prev)
अणु
	काष्ठा dentry *child = शून्य;
	काष्ठा list_head *p = prev ? &prev->d_child : &parent->d_subdirs;

	spin_lock(&parent->d_lock);
	जबतक ((p = p->next) != &parent->d_subdirs) अणु
		काष्ठा dentry *d = container_of(p, काष्ठा dentry, d_child);
		अगर (simple_positive(d)) अणु
			spin_lock_nested(&d->d_lock, DENTRY_D_LOCK_NESTED);
			अगर (simple_positive(d))
				child = dget_dlock(d);
			spin_unlock(&d->d_lock);
			अगर (likely(child))
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&parent->d_lock);
	dput(prev);
	वापस child;
पूर्ण

व्योम simple_recursive_removal(काष्ठा dentry *dentry,
                              व्योम (*callback)(काष्ठा dentry *))
अणु
	काष्ठा dentry *this = dget(dentry);
	जबतक (true) अणु
		काष्ठा dentry *victim = शून्य, *child;
		काष्ठा inode *inode = this->d_inode;

		inode_lock(inode);
		अगर (d_is_dir(this))
			inode->i_flags |= S_DEAD;
		जबतक ((child = find_next_child(this, victim)) == शून्य) अणु
			// समाप्त and ascend
			// update metadata जबतक it's still locked
			inode->i_स_समय = current_समय(inode);
			clear_nlink(inode);
			inode_unlock(inode);
			victim = this;
			this = this->d_parent;
			inode = this->d_inode;
			inode_lock(inode);
			अगर (simple_positive(victim)) अणु
				d_invalidate(victim);	// aव्योम lost mounts
				अगर (d_is_dir(victim))
					fsnotअगरy_सूची_हटाओ(inode, victim);
				अन्यथा
					fsnotअगरy_unlink(inode, victim);
				अगर (callback)
					callback(victim);
				dput(victim);		// unpin it
			पूर्ण
			अगर (victim == dentry) अणु
				inode->i_स_समय = inode->i_mसमय =
					current_समय(inode);
				अगर (d_is_dir(dentry))
					drop_nlink(inode);
				inode_unlock(inode);
				dput(dentry);
				वापस;
			पूर्ण
		पूर्ण
		inode_unlock(inode);
		this = child;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(simple_recursive_removal);

अटल स्थिर काष्ठा super_operations simple_super_operations = अणु
	.statfs		= simple_statfs,
पूर्ण;

अटल पूर्णांक pseuकरो_fs_fill_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = fc->fs_निजी;
	काष्ठा inode *root;

	s->s_maxbytes = MAX_LFS_खाताSIZE;
	s->s_blocksize = PAGE_SIZE;
	s->s_blocksize_bits = PAGE_SHIFT;
	s->s_magic = ctx->magic;
	s->s_op = ctx->ops ?: &simple_super_operations;
	s->s_xattr = ctx->xattr;
	s->s_समय_gran = 1;
	root = new_inode(s);
	अगर (!root)
		वापस -ENOMEM;

	/*
	 * since this is the first inode, make it number 1. New inodes created
	 * after this must take care not to collide with it (by passing
	 * max_reserved of 1 to iunique).
	 */
	root->i_ino = 1;
	root->i_mode = S_IFसूची | S_IRUSR | S_IWUSR;
	root->i_aसमय = root->i_mसमय = root->i_स_समय = current_समय(root);
	s->s_root = d_make_root(root);
	अगर (!s->s_root)
		वापस -ENOMEM;
	s->s_d_op = ctx->करोps;
	वापस 0;
पूर्ण

अटल पूर्णांक pseuकरो_fs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, pseuकरो_fs_fill_super);
पूर्ण

अटल व्योम pseuकरो_fs_मुक्त(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->fs_निजी);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations pseuकरो_fs_context_ops = अणु
	.मुक्त		= pseuकरो_fs_मुक्त,
	.get_tree	= pseuकरो_fs_get_tree,
पूर्ण;

/*
 * Common helper क्रम pseuकरो-fileप्रणालीs (sockfs, pipefs, bdev - stuff that
 * will never be mountable)
 */
काष्ठा pseuकरो_fs_context *init_pseuकरो(काष्ठा fs_context *fc,
					अचिन्हित दीर्घ magic)
अणु
	काष्ठा pseuकरो_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा pseuकरो_fs_context), GFP_KERNEL);
	अगर (likely(ctx)) अणु
		ctx->magic = magic;
		fc->fs_निजी = ctx;
		fc->ops = &pseuकरो_fs_context_ops;
		fc->sb_flags |= SB_NOUSER;
		fc->global = true;
	पूर्ण
	वापस ctx;
पूर्ण
EXPORT_SYMBOL(init_pseuकरो);

पूर्णांक simple_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (inode->i_निजी)
		file->निजी_data = inode->i_निजी;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_खोलो);

पूर्णांक simple_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);

	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(inode);
	inc_nlink(inode);
	ihold(inode);
	dget(dentry);
	d_instantiate(dentry, inode);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_link);

पूर्णांक simple_empty(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *child;
	पूर्णांक ret = 0;

	spin_lock(&dentry->d_lock);
	list_क्रम_each_entry(child, &dentry->d_subdirs, d_child) अणु
		spin_lock_nested(&child->d_lock, DENTRY_D_LOCK_NESTED);
		अगर (simple_positive(child)) अणु
			spin_unlock(&child->d_lock);
			जाओ out;
		पूर्ण
		spin_unlock(&child->d_lock);
	पूर्ण
	ret = 1;
out:
	spin_unlock(&dentry->d_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(simple_empty);

पूर्णांक simple_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय = current_समय(inode);
	drop_nlink(inode);
	dput(dentry);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_unlink);

पूर्णांक simple_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अगर (!simple_empty(dentry))
		वापस -ENOTEMPTY;

	drop_nlink(d_inode(dentry));
	simple_unlink(dir, dentry);
	drop_nlink(dir);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_सूची_हटाओ);

पूर्णांक simple_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		  काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		  काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक they_are_dirs = d_is_dir(old_dentry);

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	अगर (!simple_empty(new_dentry))
		वापस -ENOTEMPTY;

	अगर (d_really_is_positive(new_dentry)) अणु
		simple_unlink(new_dir, new_dentry);
		अगर (they_are_dirs) अणु
			drop_nlink(d_inode(new_dentry));
			drop_nlink(old_dir);
		पूर्ण
	पूर्ण अन्यथा अगर (they_are_dirs) अणु
		drop_nlink(old_dir);
		inc_nlink(new_dir);
	पूर्ण

	old_dir->i_स_समय = old_dir->i_mसमय = new_dir->i_स_समय =
		new_dir->i_mसमय = inode->i_स_समय = current_समय(old_dir);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_नाम);

/**
 * simple_setattr - setattr क्रम simple fileप्रणाली
 * @mnt_userns: user namespace of the target mount
 * @dentry: dentry
 * @iattr: iattr काष्ठाure
 *
 * Returns 0 on success, -error on failure.
 *
 * simple_setattr is a simple ->setattr implementation without a proper
 * implementation of size changes.
 *
 * It can either be used क्रम in-memory fileप्रणालीs or special files
 * on simple regular fileप्रणालीs.  Anything that needs to change on-disk
 * or wire state on size changes needs its own setattr method.
 */
पूर्णांक simple_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	error = setattr_prepare(mnt_userns, dentry, iattr);
	अगर (error)
		वापस error;

	अगर (iattr->ia_valid & ATTR_SIZE)
		truncate_setsize(inode, iattr->ia_size);
	setattr_copy(mnt_userns, inode, iattr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_setattr);

पूर्णांक simple_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	clear_highpage(page);
	flush_dcache_page(page);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_पढ़ोpage);

पूर्णांक simple_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा page *page;
	pgoff_t index;

	index = pos >> PAGE_SHIFT;

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;

	*pagep = page;

	अगर (!PageUptodate(page) && (len != PAGE_SIZE)) अणु
		अचिन्हित from = pos & (PAGE_SIZE - 1);

		zero_user_segments(page, 0, from, from + len, PAGE_SIZE);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_ग_लिखो_begin);

/**
 * simple_ग_लिखो_end - .ग_लिखो_end helper क्रम non-block-device FSes
 * @file: See .ग_लिखो_end of address_space_operations
 * @mapping: 		"
 * @pos: 		"
 * @len: 		"
 * @copied: 		"
 * @page: 		"
 * @fsdata: 		"
 *
 * simple_ग_लिखो_end करोes the minimum needed क्रम updating a page after writing is
 * करोne. It has the same API signature as the .ग_लिखो_end of
 * address_space_operations vector. So it can just be set onto .ग_लिखो_end क्रम
 * FSes that करोn't need any other processing. i_mutex is assumed to be held.
 * Block based fileप्रणालीs should use generic_ग_लिखो_end().
 * NOTE: Even though i_size might get updated by this function, mark_inode_dirty
 * is not called, so a fileप्रणाली that actually करोes store data in .ग_लिखो_inode
 * should extend on what's करोne here with a call to mark_inode_dirty() in the
 * हाल that i_size has changed.
 *
 * Use *ONLY* with simple_पढ़ोpage()
 */
पूर्णांक simple_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;
	loff_t last_pos = pos + copied;

	/* zero the stale part of the page अगर we did a लघु copy */
	अगर (!PageUptodate(page)) अणु
		अगर (copied < len) अणु
			अचिन्हित from = pos & (PAGE_SIZE - 1);

			zero_user(page, from + copied, len - copied);
		पूर्ण
		SetPageUptodate(page);
	पूर्ण
	/*
	 * No need to use i_size_पढ़ो() here, the i_size
	 * cannot change under us because we hold the i_mutex.
	 */
	अगर (last_pos > inode->i_size)
		i_size_ग_लिखो(inode, last_pos);

	set_page_dirty(page);
	unlock_page(page);
	put_page(page);

	वापस copied;
पूर्ण
EXPORT_SYMBOL(simple_ग_लिखो_end);

/*
 * the inodes created here are not hashed. If you use iunique to generate
 * unique inode values later क्रम this fileप्रणाली, then you must take care
 * to pass it an appropriate max_reserved value to aव्योम collisions.
 */
पूर्णांक simple_fill_super(काष्ठा super_block *s, अचिन्हित दीर्घ magic,
		      स्थिर काष्ठा tree_descr *files)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *root;
	काष्ठा dentry *dentry;
	पूर्णांक i;

	s->s_blocksize = PAGE_SIZE;
	s->s_blocksize_bits = PAGE_SHIFT;
	s->s_magic = magic;
	s->s_op = &simple_super_operations;
	s->s_समय_gran = 1;

	inode = new_inode(s);
	अगर (!inode)
		वापस -ENOMEM;
	/*
	 * because the root inode is 1, the files array must not contain an
	 * entry at index 1
	 */
	inode->i_ino = 1;
	inode->i_mode = S_IFसूची | 0755;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	set_nlink(inode, 2);
	root = d_make_root(inode);
	अगर (!root)
		वापस -ENOMEM;
	क्रम (i = 0; !files->name || files->name[0]; i++, files++) अणु
		अगर (!files->name)
			जारी;

		/* warn अगर it tries to conflict with the root inode */
		अगर (unlikely(i == 1))
			prपूर्णांकk(KERN_WARNING "%s: %s passed in a files array"
				"with an index of 1!\n", __func__,
				s->s_type->name);

		dentry = d_alloc_name(root, files->name);
		अगर (!dentry)
			जाओ out;
		inode = new_inode(s);
		अगर (!inode) अणु
			dput(dentry);
			जाओ out;
		पूर्ण
		inode->i_mode = S_IFREG | files->mode;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inode->i_fop = files->ops;
		inode->i_ino = i;
		d_add(dentry, inode);
	पूर्ण
	s->s_root = root;
	वापस 0;
out:
	d_genocide(root);
	shrink_dcache_parent(root);
	dput(root);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(simple_fill_super);

अटल DEFINE_SPINLOCK(pin_fs_lock);

पूर्णांक simple_pin_fs(काष्ठा file_प्रणाली_type *type, काष्ठा vfsmount **mount, पूर्णांक *count)
अणु
	काष्ठा vfsmount *mnt = शून्य;
	spin_lock(&pin_fs_lock);
	अगर (unlikely(!*mount)) अणु
		spin_unlock(&pin_fs_lock);
		mnt = vfs_kern_mount(type, SB_KERNMOUNT, type->name, शून्य);
		अगर (IS_ERR(mnt))
			वापस PTR_ERR(mnt);
		spin_lock(&pin_fs_lock);
		अगर (!*mount)
			*mount = mnt;
	पूर्ण
	mntget(*mount);
	++*count;
	spin_unlock(&pin_fs_lock);
	mntput(mnt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_pin_fs);

व्योम simple_release_fs(काष्ठा vfsmount **mount, पूर्णांक *count)
अणु
	काष्ठा vfsmount *mnt;
	spin_lock(&pin_fs_lock);
	mnt = *mount;
	अगर (!--*count)
		*mount = शून्य;
	spin_unlock(&pin_fs_lock);
	mntput(mnt);
पूर्ण
EXPORT_SYMBOL(simple_release_fs);

/**
 * simple_पढ़ो_from_buffer - copy data from the buffer to user space
 * @to: the user space buffer to पढ़ो to
 * @count: the maximum number of bytes to पढ़ो
 * @ppos: the current position in the buffer
 * @from: the buffer to पढ़ो from
 * @available: the size of the buffer
 *
 * The simple_पढ़ो_from_buffer() function पढ़ोs up to @count bytes from the
 * buffer @from at offset @ppos पूर्णांकo the user space address starting at @to.
 *
 * On success, the number of bytes पढ़ो is वापसed and the offset @ppos is
 * advanced by this number, or negative value is वापसed on error.
 **/
sमाप_प्रकार simple_पढ़ो_from_buffer(व्योम __user *to, माप_प्रकार count, loff_t *ppos,
				स्थिर व्योम *from, माप_प्रकार available)
अणु
	loff_t pos = *ppos;
	माप_प्रकार ret;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= available || !count)
		वापस 0;
	अगर (count > available - pos)
		count = available - pos;
	ret = copy_to_user(to, from + pos, count);
	अगर (ret == count)
		वापस -EFAULT;
	count -= ret;
	*ppos = pos + count;
	वापस count;
पूर्ण
EXPORT_SYMBOL(simple_पढ़ो_from_buffer);

/**
 * simple_ग_लिखो_to_buffer - copy data from user space to the buffer
 * @to: the buffer to ग_लिखो to
 * @available: the size of the buffer
 * @ppos: the current position in the buffer
 * @from: the user space buffer to पढ़ो from
 * @count: the maximum number of bytes to पढ़ो
 *
 * The simple_ग_लिखो_to_buffer() function पढ़ोs up to @count bytes from the user
 * space address starting at @from पूर्णांकo the buffer @to at offset @ppos.
 *
 * On success, the number of bytes written is वापसed and the offset @ppos is
 * advanced by this number, or negative value is वापसed on error.
 **/
sमाप_प्रकार simple_ग_लिखो_to_buffer(व्योम *to, माप_प्रकार available, loff_t *ppos,
		स्थिर व्योम __user *from, माप_प्रकार count)
अणु
	loff_t pos = *ppos;
	माप_प्रकार res;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= available || !count)
		वापस 0;
	अगर (count > available - pos)
		count = available - pos;
	res = copy_from_user(to + pos, from, count);
	अगर (res == count)
		वापस -EFAULT;
	count -= res;
	*ppos = pos + count;
	वापस count;
पूर्ण
EXPORT_SYMBOL(simple_ग_लिखो_to_buffer);

/**
 * memory_पढ़ो_from_buffer - copy data from the buffer
 * @to: the kernel space buffer to पढ़ो to
 * @count: the maximum number of bytes to पढ़ो
 * @ppos: the current position in the buffer
 * @from: the buffer to पढ़ो from
 * @available: the size of the buffer
 *
 * The memory_पढ़ो_from_buffer() function पढ़ोs up to @count bytes from the
 * buffer @from at offset @ppos पूर्णांकo the kernel space address starting at @to.
 *
 * On success, the number of bytes पढ़ो is वापसed and the offset @ppos is
 * advanced by this number, or negative value is वापसed on error.
 **/
sमाप_प्रकार memory_पढ़ो_from_buffer(व्योम *to, माप_प्रकार count, loff_t *ppos,
				स्थिर व्योम *from, माप_प्रकार available)
अणु
	loff_t pos = *ppos;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= available)
		वापस 0;
	अगर (count > available - pos)
		count = available - pos;
	स_नकल(to, from + pos, count);
	*ppos = pos + count;

	वापस count;
पूर्ण
EXPORT_SYMBOL(memory_पढ़ो_from_buffer);

/*
 * Transaction based IO.
 * The file expects a single ग_लिखो which triggers the transaction, and then
 * possibly a पढ़ो which collects the result - which is stored in a
 * file-local buffer.
 */

व्योम simple_transaction_set(काष्ठा file *file, माप_प्रकार n)
अणु
	काष्ठा simple_transaction_argresp *ar = file->निजी_data;

	BUG_ON(n > SIMPLE_TRANSACTION_LIMIT);

	/*
	 * The barrier ensures that ar->size will really reमुख्य zero until
	 * ar->data is पढ़ोy क्रम पढ़ोing.
	 */
	smp_mb();
	ar->size = n;
पूर्ण
EXPORT_SYMBOL(simple_transaction_set);

अक्षर *simple_transaction_get(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार size)
अणु
	काष्ठा simple_transaction_argresp *ar;
	अटल DEFINE_SPINLOCK(simple_transaction_lock);

	अगर (size > SIMPLE_TRANSACTION_LIMIT - 1)
		वापस ERR_PTR(-EFBIG);

	ar = (काष्ठा simple_transaction_argresp *)get_zeroed_page(GFP_KERNEL);
	अगर (!ar)
		वापस ERR_PTR(-ENOMEM);

	spin_lock(&simple_transaction_lock);

	/* only one ग_लिखो allowed per खोलो */
	अगर (file->निजी_data) अणु
		spin_unlock(&simple_transaction_lock);
		मुक्त_page((अचिन्हित दीर्घ)ar);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	file->निजी_data = ar;

	spin_unlock(&simple_transaction_lock);

	अगर (copy_from_user(ar->data, buf, size))
		वापस ERR_PTR(-EFAULT);

	वापस ar->data;
पूर्ण
EXPORT_SYMBOL(simple_transaction_get);

sमाप_प्रकार simple_transaction_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा simple_transaction_argresp *ar = file->निजी_data;

	अगर (!ar)
		वापस 0;
	वापस simple_पढ़ो_from_buffer(buf, size, pos, ar->data, ar->size);
पूर्ण
EXPORT_SYMBOL(simple_transaction_पढ़ो);

पूर्णांक simple_transaction_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	मुक्त_page((अचिन्हित दीर्घ)file->निजी_data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(simple_transaction_release);

/* Simple attribute files */

काष्ठा simple_attr अणु
	पूर्णांक (*get)(व्योम *, u64 *);
	पूर्णांक (*set)(व्योम *, u64);
	अक्षर get_buf[24];	/* enough to store a u64 and "\n\0" */
	अक्षर set_buf[24];
	व्योम *data;
	स्थिर अक्षर *fmt;	/* क्रमmat क्रम पढ़ो operation */
	काष्ठा mutex mutex;	/* protects access to these buffers */
पूर्ण;

/* simple_attr_खोलो is called by an actual attribute खोलो file operation
 * to set the attribute specअगरic access operations. */
पूर्णांक simple_attr_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		     पूर्णांक (*get)(व्योम *, u64 *), पूर्णांक (*set)(व्योम *, u64),
		     स्थिर अक्षर *fmt)
अणु
	काष्ठा simple_attr *attr;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	attr->get = get;
	attr->set = set;
	attr->data = inode->i_निजी;
	attr->fmt = fmt;
	mutex_init(&attr->mutex);

	file->निजी_data = attr;

	वापस nonseekable_खोलो(inode, file);
पूर्ण
EXPORT_SYMBOL_GPL(simple_attr_खोलो);

पूर्णांक simple_attr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(simple_attr_release);	/* GPL-only?  This?  Really? */

/* पढ़ो from the buffer that is filled with the get function */
sमाप_प्रकार simple_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा simple_attr *attr;
	माप_प्रकार size;
	sमाप_प्रकार ret;

	attr = file->निजी_data;

	अगर (!attr->get)
		वापस -EACCES;

	ret = mutex_lock_पूर्णांकerruptible(&attr->mutex);
	अगर (ret)
		वापस ret;

	अगर (*ppos && attr->get_buf[0]) अणु
		/* जारीd पढ़ो */
		size = म_माप(attr->get_buf);
	पूर्ण अन्यथा अणु
		/* first पढ़ो */
		u64 val;
		ret = attr->get(attr->data, &val);
		अगर (ret)
			जाओ out;

		size = scnम_लिखो(attr->get_buf, माप(attr->get_buf),
				 attr->fmt, (अचिन्हित दीर्घ दीर्घ)val);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(buf, len, ppos, attr->get_buf, size);
out:
	mutex_unlock(&attr->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(simple_attr_पढ़ो);

/* पूर्णांकerpret the buffer as a number to call the set function with */
sमाप_प्रकार simple_attr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा simple_attr *attr;
	अचिन्हित दीर्घ दीर्घ val;
	माप_प्रकार size;
	sमाप_प्रकार ret;

	attr = file->निजी_data;
	अगर (!attr->set)
		वापस -EACCES;

	ret = mutex_lock_पूर्णांकerruptible(&attr->mutex);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	size = min(माप(attr->set_buf) - 1, len);
	अगर (copy_from_user(attr->set_buf, buf, size))
		जाओ out;

	attr->set_buf[size] = '\0';
	ret = kम_से_अदीर्घl(attr->set_buf, 0, &val);
	अगर (ret)
		जाओ out;
	ret = attr->set(attr->data, val);
	अगर (ret == 0)
		ret = len; /* on success, claim we got the whole input */
out:
	mutex_unlock(&attr->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(simple_attr_ग_लिखो);

/**
 * generic_fh_to_dentry - generic helper क्रम the fh_to_dentry export operation
 * @sb:		fileप्रणाली to करो the file handle conversion on
 * @fid:	file handle to convert
 * @fh_len:	length of the file handle in bytes
 * @fh_type:	type of file handle
 * @get_inode:	fileप्रणाली callback to retrieve inode
 *
 * This function decodes @fid as दीर्घ as it has one of the well-known
 * Linux filehandle types and calls @get_inode on it to retrieve the
 * inode क्रम the object specअगरied in the file handle.
 */
काष्ठा dentry *generic_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type, काष्ठा inode *(*get_inode)
			(काष्ठा super_block *sb, u64 ino, u32 gen))
अणु
	काष्ठा inode *inode = शून्य;

	अगर (fh_len < 2)
		वापस शून्य;

	चयन (fh_type) अणु
	हाल खाताID_INO32_GEN:
	हाल खाताID_INO32_GEN_PARENT:
		inode = get_inode(sb, fid->i32.ino, fid->i32.gen);
		अवरोध;
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण
EXPORT_SYMBOL_GPL(generic_fh_to_dentry);

/**
 * generic_fh_to_parent - generic helper क्रम the fh_to_parent export operation
 * @sb:		fileप्रणाली to करो the file handle conversion on
 * @fid:	file handle to convert
 * @fh_len:	length of the file handle in bytes
 * @fh_type:	type of file handle
 * @get_inode:	fileप्रणाली callback to retrieve inode
 *
 * This function decodes @fid as दीर्घ as it has one of the well-known
 * Linux filehandle types and calls @get_inode on it to retrieve the
 * inode क्रम the _parent_ object specअगरied in the file handle अगर it
 * is specअगरied in the file handle, or शून्य otherwise.
 */
काष्ठा dentry *generic_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type, काष्ठा inode *(*get_inode)
			(काष्ठा super_block *sb, u64 ino, u32 gen))
अणु
	काष्ठा inode *inode = शून्य;

	अगर (fh_len <= 2)
		वापस शून्य;

	चयन (fh_type) अणु
	हाल खाताID_INO32_GEN_PARENT:
		inode = get_inode(sb, fid->i32.parent_ino,
				  (fh_len > 3 ? fid->i32.parent_gen : 0));
		अवरोध;
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण
EXPORT_SYMBOL_GPL(generic_fh_to_parent);

/**
 * __generic_file_fsync - generic fsync implementation क्रम simple fileप्रणालीs
 *
 * @file:	file to synchronize
 * @start:	start offset in bytes
 * @end:	end offset in bytes (inclusive)
 * @datasync:	only synchronize essential metadata अगर true
 *
 * This is a generic implementation of the fsync method क्रम simple
 * fileप्रणालीs which track all non-inode metadata in the buffers list
 * hanging off the address_space काष्ठाure.
 */
पूर्णांक __generic_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
				 पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक err;
	पूर्णांक ret;

	err = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (err)
		वापस err;

	inode_lock(inode);
	ret = sync_mapping_buffers(inode->i_mapping);
	अगर (!(inode->i_state & I_सूचीTY_ALL))
		जाओ out;
	अगर (datasync && !(inode->i_state & I_सूचीTY_DATASYNC))
		जाओ out;

	err = sync_inode_metadata(inode, 1);
	अगर (ret == 0)
		ret = err;

out:
	inode_unlock(inode);
	/* check and advance again to catch errors after syncing out buffers */
	err = file_check_and_advance_wb_err(file);
	अगर (ret == 0)
		ret = err;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__generic_file_fsync);

/**
 * generic_file_fsync - generic fsync implementation क्रम simple fileप्रणालीs
 *			with flush
 * @file:	file to synchronize
 * @start:	start offset in bytes
 * @end:	end offset in bytes (inclusive)
 * @datasync:	only synchronize essential metadata अगर true
 *
 */

पूर्णांक generic_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
		       पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक err;

	err = __generic_file_fsync(file, start, end, datasync);
	अगर (err)
		वापस err;
	वापस blkdev_issue_flush(inode->i_sb->s_bdev);
पूर्ण
EXPORT_SYMBOL(generic_file_fsync);

/**
 * generic_check_addressable - Check addressability of file प्रणाली
 * @blocksize_bits:	log of file प्रणाली block size
 * @num_blocks:		number of blocks in file प्रणाली
 *
 * Determine whether a file प्रणाली with @num_blocks blocks (and a
 * block size of 2**@blocksize_bits) is addressable by the sector_t
 * and page cache of the प्रणाली.  Return 0 अगर so and -EFBIG otherwise.
 */
पूर्णांक generic_check_addressable(अचिन्हित blocksize_bits, u64 num_blocks)
अणु
	u64 last_fs_block = num_blocks - 1;
	u64 last_fs_page =
		last_fs_block >> (PAGE_SHIFT - blocksize_bits);

	अगर (unlikely(num_blocks == 0))
		वापस 0;

	अगर ((blocksize_bits < 9) || (blocksize_bits > PAGE_SHIFT))
		वापस -EINVAL;

	अगर ((last_fs_block > (sector_t)(~0ULL) >> (blocksize_bits - 9)) ||
	    (last_fs_page > (pgoff_t)(~0ULL))) अणु
		वापस -EFBIG;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(generic_check_addressable);

/*
 * No-op implementation of ->fsync क्रम in-memory fileप्रणालीs.
 */
पूर्णांक noop_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(noop_fsync);

पूर्णांक noop_set_page_dirty(काष्ठा page *page)
अणु
	/*
	 * Unlike __set_page_dirty_no_ग_लिखोback that handles dirty page
	 * tracking in the page object, dax करोes all dirty tracking in
	 * the inode address_space in response to mkग_लिखो faults. In the
	 * dax हाल we only need to worry about potentially dirty CPU
	 * caches, not dirty page cache pages to ग_लिखो back.
	 *
	 * This callback is defined to prevent fallback to
	 * __set_page_dirty_buffers() in set_page_dirty().
	 */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(noop_set_page_dirty);

व्योम noop_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक length)
अणु
	/*
	 * There is no page cache to invalidate in the dax हाल, however
	 * we need this callback defined to prevent falling back to
	 * block_invalidatepage() in करो_invalidatepage().
	 */
पूर्ण
EXPORT_SYMBOL_GPL(noop_invalidatepage);

sमाप_प्रकार noop_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	/*
	 * iomap based fileप्रणालीs support direct I/O without need क्रम
	 * this callback. However, it still needs to be set in
	 * inode->a_ops so that खोलो/fcntl know that direct I/O is
	 * generally supported.
	 */
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(noop_direct_IO);

/* Because kमुक्त isn't assignment-compatible with व्योम(व्योम*) ;-/ */
व्योम kमुक्त_link(व्योम *p)
अणु
	kमुक्त(p);
पूर्ण
EXPORT_SYMBOL(kमुक्त_link);

/*
 * nop .set_page_dirty method so that people can use .page_mkग_लिखो on
 * anon inodes.
 */
अटल पूर्णांक anon_set_page_dirty(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण;

काष्ठा inode *alloc_anon_inode(काष्ठा super_block *s)
अणु
	अटल स्थिर काष्ठा address_space_operations anon_aops = अणु
		.set_page_dirty = anon_set_page_dirty,
	पूर्ण;
	काष्ठा inode *inode = new_inode_pseuकरो(s);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	inode->i_ino = get_next_ino();
	inode->i_mapping->a_ops = &anon_aops;

	/*
	 * Mark the inode dirty from the very beginning,
	 * that way it will never be moved to the dirty
	 * list because mark_inode_dirty() will think
	 * that it alपढ़ोy _is_ on the dirty list.
	 */
	inode->i_state = I_सूचीTY;
	inode->i_mode = S_IRUSR | S_IWUSR;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_flags |= S_PRIVATE;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	वापस inode;
पूर्ण
EXPORT_SYMBOL(alloc_anon_inode);

/**
 * simple_nosetlease - generic helper क्रम prohibiting leases
 * @filp: file poपूर्णांकer
 * @arg: type of lease to obtain
 * @flp: new lease supplied क्रम insertion
 * @priv: निजी data क्रम lm_setup operation
 *
 * Generic helper क्रम fileप्रणालीs that करो not wish to allow leases to be set.
 * All arguments are ignored and it just वापसs -EINVAL.
 */
पूर्णांक
simple_nosetlease(काष्ठा file *filp, दीर्घ arg, काष्ठा file_lock **flp,
		  व्योम **priv)
अणु
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(simple_nosetlease);

/**
 * simple_get_link - generic helper to get the target of "fast" symlinks
 * @dentry: not used here
 * @inode: the symlink inode
 * @करोne: not used here
 *
 * Generic helper क्रम fileप्रणालीs to use क्रम symlink inodes where a poपूर्णांकer to
 * the symlink target is stored in ->i_link.  NOTE: this isn't normally called,
 * since as an optimization the path lookup code uses any non-शून्य ->i_link
 * directly, without calling ->get_link().  But ->get_link() still must be set,
 * to mark the inode_operations as being क्रम a symlink.
 *
 * Return: the symlink target
 */
स्थिर अक्षर *simple_get_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
			    काष्ठा delayed_call *करोne)
अणु
	वापस inode->i_link;
पूर्ण
EXPORT_SYMBOL(simple_get_link);

स्थिर काष्ठा inode_operations simple_symlink_inode_operations = अणु
	.get_link = simple_get_link,
पूर्ण;
EXPORT_SYMBOL(simple_symlink_inode_operations);

/*
 * Operations क्रम a permanently empty directory.
 */
अटल काष्ठा dentry *empty_dir_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक empty_dir_getattr(काष्ठा user_namespace *mnt_userns,
			     स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			     u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

अटल पूर्णांक empty_dir_setattr(काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	वापस -EPERM;
पूर्ण

अटल sमाप_प्रकार empty_dir_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा inode_operations empty_dir_inode_operations = अणु
	.lookup		= empty_dir_lookup,
	.permission	= generic_permission,
	.setattr	= empty_dir_setattr,
	.getattr	= empty_dir_getattr,
	.listxattr	= empty_dir_listxattr,
पूर्ण;

अटल loff_t empty_dir_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	/* An empty directory has two entries . and .. at offsets 0 and 1 */
	वापस generic_file_llseek_size(file, offset, whence, 2, 2);
पूर्ण

अटल पूर्णांक empty_dir_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	dir_emit_करोts(file, ctx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations empty_dir_operations = अणु
	.llseek		= empty_dir_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= empty_dir_सूची_पढ़ो,
	.fsync		= noop_fsync,
पूर्ण;


व्योम make_empty_dir_inode(काष्ठा inode *inode)
अणु
	set_nlink(inode, 2);
	inode->i_mode = S_IFसूची | S_IRUGO | S_IXUGO;
	inode->i_uid = GLOBAL_ROOT_UID;
	inode->i_gid = GLOBAL_ROOT_GID;
	inode->i_rdev = 0;
	inode->i_size = 0;
	inode->i_blkbits = PAGE_SHIFT;
	inode->i_blocks = 0;

	inode->i_op = &empty_dir_inode_operations;
	inode->i_opflags &= ~IOP_XATTR;
	inode->i_fop = &empty_dir_operations;
पूर्ण

bool is_empty_dir_inode(काष्ठा inode *inode)
अणु
	वापस (inode->i_fop == &empty_dir_operations) &&
		(inode->i_op == &empty_dir_inode_operations);
पूर्ण

#अगर_घोषित CONFIG_UNICODE
/*
 * Determine अगर the name of a dentry should be हालfolded.
 *
 * Return: अगर names will need हालfolding
 */
अटल bool needs_हालfold(स्थिर काष्ठा inode *dir)
अणु
	वापस IS_CASEFOLDED(dir) && dir->i_sb->s_encoding;
पूर्ण

/**
 * generic_ci_d_compare - generic d_compare implementation क्रम हालfolding fileप्रणालीs
 * @dentry:	dentry whose name we are checking against
 * @len:	len of name of dentry
 * @str:	str poपूर्णांकer to name of dentry
 * @name:	Name to compare against
 *
 * Return: 0 अगर names match, 1 अगर mismatch, or -ERRNO
 */
अटल पूर्णांक generic_ci_d_compare(स्थिर काष्ठा dentry *dentry, अचिन्हित पूर्णांक len,
				स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	स्थिर काष्ठा dentry *parent = READ_ONCE(dentry->d_parent);
	स्थिर काष्ठा inode *dir = READ_ONCE(parent->d_inode);
	स्थिर काष्ठा super_block *sb = dentry->d_sb;
	स्थिर काष्ठा unicode_map *um = sb->s_encoding;
	काष्ठा qstr qstr = QSTR_INIT(str, len);
	अक्षर strbuf[DNAME_INLINE_LEN];
	पूर्णांक ret;

	अगर (!dir || !needs_हालfold(dir))
		जाओ fallback;
	/*
	 * If the dentry name is stored in-line, then it may be concurrently
	 * modअगरied by a नाम.  If this happens, the VFS will eventually retry
	 * the lookup, so it करोesn't matter what ->d_compare() वापसs.
	 * However, it's unsafe to call utf8_strnहालcmp() with an unstable
	 * string.  Thereक्रमe, we have to copy the name पूर्णांकo a temporary buffer.
	 */
	अगर (len <= DNAME_INLINE_LEN - 1) अणु
		स_नकल(strbuf, str, len);
		strbuf[len] = 0;
		qstr.name = strbuf;
		/* prevent compiler from optimizing out the temporary buffer */
		barrier();
	पूर्ण
	ret = utf8_strnहालcmp(um, name, &qstr);
	अगर (ret >= 0)
		वापस ret;

	अगर (sb_has_strict_encoding(sb))
		वापस -EINVAL;
fallback:
	अगर (len != name->len)
		वापस 1;
	वापस !!स_भेद(str, name->name, len);
पूर्ण

/**
 * generic_ci_d_hash - generic d_hash implementation क्रम हालfolding fileप्रणालीs
 * @dentry:	dentry of the parent directory
 * @str:	qstr of name whose hash we should fill in
 *
 * Return: 0 अगर hash was successful or unchanged, and -EINVAL on error
 */
अटल पूर्णांक generic_ci_d_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *str)
अणु
	स्थिर काष्ठा inode *dir = READ_ONCE(dentry->d_inode);
	काष्ठा super_block *sb = dentry->d_sb;
	स्थिर काष्ठा unicode_map *um = sb->s_encoding;
	पूर्णांक ret = 0;

	अगर (!dir || !needs_हालfold(dir))
		वापस 0;

	ret = utf8_हालfold_hash(um, dentry, str);
	अगर (ret < 0 && sb_has_strict_encoding(sb))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dentry_operations generic_ci_dentry_ops = अणु
	.d_hash = generic_ci_d_hash,
	.d_compare = generic_ci_d_compare,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल स्थिर काष्ठा dentry_operations generic_encrypted_dentry_ops = अणु
	.d_revalidate = fscrypt_d_revalidate,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_FS_ENCRYPTION) && defined(CONFIG_UNICODE)
अटल स्थिर काष्ठा dentry_operations generic_encrypted_ci_dentry_ops = अणु
	.d_hash = generic_ci_d_hash,
	.d_compare = generic_ci_d_compare,
	.d_revalidate = fscrypt_d_revalidate,
पूर्ण;
#पूर्ण_अगर

/**
 * generic_set_encrypted_ci_d_ops - helper क्रम setting d_ops क्रम given dentry
 * @dentry:	dentry to set ops on
 *
 * Casefolded directories need d_hash and d_compare set, so that the dentries
 * contained in them are handled हाल-insensitively.  Note that these operations
 * are needed on the parent directory rather than on the dentries in it, and
 * जबतक the हालfolding flag can be toggled on and off on an empty directory,
 * dentry_operations can't be changed later.  As a result, अगर the fileप्रणाली has
 * हालfolding support enabled at all, we have to give all dentries the
 * हालfolding operations even अगर their inode करोesn't have the हालfolding flag
 * currently (and thus the हालfolding ops would be no-ops क्रम now).
 *
 * Encryption works dअगरferently in that the only dentry operation it needs is
 * d_revalidate, which it only needs on dentries that have the no-key name flag.
 * The no-key flag can't be set "later", so we don't have to worry about that.
 *
 * Finally, to maximize compatibility with overlayfs (which isn't compatible
 * with certain dentry operations) and to aव्योम taking an unnecessary
 * perक्रमmance hit, we use custom dentry_operations क्रम each possible
 * combination rather than always installing all operations.
 */
व्योम generic_set_encrypted_ci_d_ops(काष्ठा dentry *dentry)
अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	bool needs_encrypt_ops = dentry->d_flags & DCACHE_NOKEY_NAME;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	bool needs_ci_ops = dentry->d_sb->s_encoding;
#पूर्ण_अगर
#अगर defined(CONFIG_FS_ENCRYPTION) && defined(CONFIG_UNICODE)
	अगर (needs_encrypt_ops && needs_ci_ops) अणु
		d_set_d_op(dentry, &generic_encrypted_ci_dentry_ops);
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_ENCRYPTION
	अगर (needs_encrypt_ops) अणु
		d_set_d_op(dentry, &generic_encrypted_dentry_ops);
		वापस;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	अगर (needs_ci_ops) अणु
		d_set_d_op(dentry, &generic_ci_dentry_ops);
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(generic_set_encrypted_ci_d_ops);
