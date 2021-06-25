<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#समावेश "fuse_i.h"

#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/swap.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/uपन.स>
#समावेश <linux/fs.h>

अटल पूर्णांक fuse_send_खोलो(काष्ठा fuse_mount *fm, u64 nodeid,
			  अचिन्हित पूर्णांक खोलो_flags, पूर्णांक opcode,
			  काष्ठा fuse_खोलो_out *outargp)
अणु
	काष्ठा fuse_खोलो_in inarg;
	FUSE_ARGS(args);

	स_रखो(&inarg, 0, माप(inarg));
	inarg.flags = खोलो_flags & ~(O_CREAT | O_EXCL | O_NOCTTY);
	अगर (!fm->fc->atomic_o_trunc)
		inarg.flags &= ~O_TRUNC;

	अगर (fm->fc->handle_समाप्तpriv_v2 &&
	    (inarg.flags & O_TRUNC) && !capable(CAP_FSETID)) अणु
		inarg.खोलो_flags |= FUSE_OPEN_KILL_SUIDGID;
	पूर्ण

	args.opcode = opcode;
	args.nodeid = nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(*outargp);
	args.out_args[0].value = outargp;

	वापस fuse_simple_request(fm, &args);
पूर्ण

काष्ठा fuse_release_args अणु
	काष्ठा fuse_args args;
	काष्ठा fuse_release_in inarg;
	काष्ठा inode *inode;
पूर्ण;

काष्ठा fuse_file *fuse_file_alloc(काष्ठा fuse_mount *fm)
अणु
	काष्ठा fuse_file *ff;

	ff = kzalloc(माप(काष्ठा fuse_file), GFP_KERNEL_ACCOUNT);
	अगर (unlikely(!ff))
		वापस शून्य;

	ff->fm = fm;
	ff->release_args = kzalloc(माप(*ff->release_args),
				   GFP_KERNEL_ACCOUNT);
	अगर (!ff->release_args) अणु
		kमुक्त(ff);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&ff->ग_लिखो_entry);
	mutex_init(&ff->सूची_पढ़ो.lock);
	refcount_set(&ff->count, 1);
	RB_CLEAR_NODE(&ff->polled_node);
	init_रुकोqueue_head(&ff->poll_रुको);

	ff->kh = atomic64_inc_वापस(&fm->fc->khctr);

	वापस ff;
पूर्ण

व्योम fuse_file_मुक्त(काष्ठा fuse_file *ff)
अणु
	kमुक्त(ff->release_args);
	mutex_destroy(&ff->सूची_पढ़ो.lock);
	kमुक्त(ff);
पूर्ण

अटल काष्ठा fuse_file *fuse_file_get(काष्ठा fuse_file *ff)
अणु
	refcount_inc(&ff->count);
	वापस ff;
पूर्ण

अटल व्योम fuse_release_end(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			     पूर्णांक error)
अणु
	काष्ठा fuse_release_args *ra = container_of(args, typeof(*ra), args);

	iput(ra->inode);
	kमुक्त(ra);
पूर्ण

अटल व्योम fuse_file_put(काष्ठा fuse_file *ff, bool sync, bool isdir)
अणु
	अगर (refcount_dec_and_test(&ff->count)) अणु
		काष्ठा fuse_args *args = &ff->release_args->args;

		अगर (isdir ? ff->fm->fc->no_सूची_खोलो : ff->fm->fc->no_खोलो) अणु
			/* Do nothing when client करोes not implement 'open' */
			fuse_release_end(ff->fm, args, 0);
		पूर्ण अन्यथा अगर (sync) अणु
			fuse_simple_request(ff->fm, args);
			fuse_release_end(ff->fm, args, 0);
		पूर्ण अन्यथा अणु
			args->end = fuse_release_end;
			अगर (fuse_simple_background(ff->fm, args,
						   GFP_KERNEL | __GFP_NOFAIL))
				fuse_release_end(ff->fm, args, -ENOTCONN);
		पूर्ण
		kमुक्त(ff);
	पूर्ण
पूर्ण

काष्ठा fuse_file *fuse_file_खोलो(काष्ठा fuse_mount *fm, u64 nodeid,
				 अचिन्हित पूर्णांक खोलो_flags, bool isdir)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_file *ff;
	पूर्णांक opcode = isdir ? FUSE_OPENसूची : FUSE_OPEN;

	ff = fuse_file_alloc(fm);
	अगर (!ff)
		वापस ERR_PTR(-ENOMEM);

	ff->fh = 0;
	/* Default क्रम no-खोलो */
	ff->खोलो_flags = FOPEN_KEEP_CACHE | (isdir ? FOPEN_CACHE_सूची : 0);
	अगर (isdir ? !fc->no_सूची_खोलो : !fc->no_खोलो) अणु
		काष्ठा fuse_खोलो_out outarg;
		पूर्णांक err;

		err = fuse_send_खोलो(fm, nodeid, खोलो_flags, opcode, &outarg);
		अगर (!err) अणु
			ff->fh = outarg.fh;
			ff->खोलो_flags = outarg.खोलो_flags;

		पूर्ण अन्यथा अगर (err != -ENOSYS) अणु
			fuse_file_मुक्त(ff);
			वापस ERR_PTR(err);
		पूर्ण अन्यथा अणु
			अगर (isdir)
				fc->no_सूची_खोलो = 1;
			अन्यथा
				fc->no_खोलो = 1;
		पूर्ण
	पूर्ण

	अगर (isdir)
		ff->खोलो_flags &= ~FOPEN_सूचीECT_IO;

	ff->nodeid = nodeid;

	वापस ff;
पूर्ण

पूर्णांक fuse_करो_खोलो(काष्ठा fuse_mount *fm, u64 nodeid, काष्ठा file *file,
		 bool isdir)
अणु
	काष्ठा fuse_file *ff = fuse_file_खोलो(fm, nodeid, file->f_flags, isdir);

	अगर (!IS_ERR(ff))
		file->निजी_data = ff;

	वापस PTR_ERR_OR_ZERO(ff);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_करो_खोलो);

अटल व्योम fuse_link_ग_लिखो_file(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_file *ff = file->निजी_data;
	/*
	 * file may be written through mmap, so chain it onto the
	 * inodes's ग_लिखो_file list
	 */
	spin_lock(&fi->lock);
	अगर (list_empty(&ff->ग_लिखो_entry))
		list_add(&ff->ग_लिखो_entry, &fi->ग_लिखो_files);
	spin_unlock(&fi->lock);
पूर्ण

व्योम fuse_finish_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	अगर (!(ff->खोलो_flags & FOPEN_KEEP_CACHE))
		invalidate_inode_pages2(inode->i_mapping);
	अगर (ff->खोलो_flags & FOPEN_STREAM)
		stream_खोलो(inode, file);
	अन्यथा अगर (ff->खोलो_flags & FOPEN_NONSEEKABLE)
		nonseekable_खोलो(inode, file);
	अगर (fc->atomic_o_trunc && (file->f_flags & O_TRUNC)) अणु
		काष्ठा fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fi->lock);
		fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
		i_size_ग_लिखो(inode, 0);
		spin_unlock(&fi->lock);
		fuse_invalidate_attr(inode);
		अगर (fc->ग_लिखोback_cache)
			file_update_समय(file);
	पूर्ण
	अगर ((file->f_mode & FMODE_WRITE) && fc->ग_लिखोback_cache)
		fuse_link_ग_लिखो_file(file);
पूर्ण

पूर्णांक fuse_खोलो_common(काष्ठा inode *inode, काष्ठा file *file, bool isdir)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_conn *fc = fm->fc;
	पूर्णांक err;
	bool is_wb_truncate = (file->f_flags & O_TRUNC) &&
			  fc->atomic_o_trunc &&
			  fc->ग_लिखोback_cache;
	bool dax_truncate = (file->f_flags & O_TRUNC) &&
			  fc->atomic_o_trunc && FUSE_IS_DAX(inode);

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	err = generic_file_खोलो(inode, file);
	अगर (err)
		वापस err;

	अगर (is_wb_truncate || dax_truncate) अणु
		inode_lock(inode);
		fuse_set_noग_लिखो(inode);
	पूर्ण

	अगर (dax_truncate) अणु
		करोwn_ग_लिखो(&get_fuse_inode(inode)->i_mmap_sem);
		err = fuse_dax_अवरोध_layouts(inode, 0, 0);
		अगर (err)
			जाओ out;
	पूर्ण

	err = fuse_करो_खोलो(fm, get_node_id(inode), file, isdir);
	अगर (!err)
		fuse_finish_खोलो(inode, file);

out:
	अगर (dax_truncate)
		up_ग_लिखो(&get_fuse_inode(inode)->i_mmap_sem);

	अगर (is_wb_truncate | dax_truncate) अणु
		fuse_release_noग_लिखो(inode);
		inode_unlock(inode);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम fuse_prepare_release(काष्ठा fuse_inode *fi, काष्ठा fuse_file *ff,
				 अचिन्हित पूर्णांक flags, पूर्णांक opcode)
अणु
	काष्ठा fuse_conn *fc = ff->fm->fc;
	काष्ठा fuse_release_args *ra = ff->release_args;

	/* Inode is शून्य on error path of fuse_create_खोलो() */
	अगर (likely(fi)) अणु
		spin_lock(&fi->lock);
		list_del(&ff->ग_लिखो_entry);
		spin_unlock(&fi->lock);
	पूर्ण
	spin_lock(&fc->lock);
	अगर (!RB_EMPTY_NODE(&ff->polled_node))
		rb_erase(&ff->polled_node, &fc->polled_files);
	spin_unlock(&fc->lock);

	wake_up_पूर्णांकerruptible_all(&ff->poll_रुको);

	ra->inarg.fh = ff->fh;
	ra->inarg.flags = flags;
	ra->args.in_numargs = 1;
	ra->args.in_args[0].size = माप(काष्ठा fuse_release_in);
	ra->args.in_args[0].value = &ra->inarg;
	ra->args.opcode = opcode;
	ra->args.nodeid = ff->nodeid;
	ra->args.क्रमce = true;
	ra->args.nocreds = true;
पूर्ण

व्योम fuse_file_release(काष्ठा inode *inode, काष्ठा fuse_file *ff,
		       अचिन्हित पूर्णांक खोलो_flags, fl_owner_t id, bool isdir)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_release_args *ra = ff->release_args;
	पूर्णांक opcode = isdir ? FUSE_RELEASEसूची : FUSE_RELEASE;

	fuse_prepare_release(fi, ff, खोलो_flags, opcode);

	अगर (ff->flock) अणु
		ra->inarg.release_flags |= FUSE_RELEASE_FLOCK_UNLOCK;
		ra->inarg.lock_owner = fuse_lock_owner_id(ff->fm->fc, id);
	पूर्ण
	/* Hold inode until release is finished */
	ra->inode = igrab(inode);

	/*
	 * Normally this will send the RELEASE request, however अगर
	 * some asynchronous READ or WRITE requests are outstanding,
	 * the sending will be delayed.
	 *
	 * Make the release synchronous अगर this is a fuseblk mount,
	 * synchronous RELEASE is allowed (and desirable) in this हाल
	 * because the server can be trusted not to screw up.
	 */
	fuse_file_put(ff, ff->fm->fc->destroy, isdir);
पूर्ण

व्योम fuse_release_common(काष्ठा file *file, bool isdir)
अणु
	fuse_file_release(file_inode(file), file->निजी_data, file->f_flags,
			  (fl_owner_t) file, isdir);
पूर्ण

अटल पूर्णांक fuse_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस fuse_खोलो_common(inode, file, false);
पूर्ण

अटल पूर्णांक fuse_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	/* see fuse_vma_बंद() क्रम !ग_लिखोback_cache हाल */
	अगर (fc->ग_लिखोback_cache)
		ग_लिखो_inode_now(inode, 1);

	fuse_release_common(file, false);

	/* वापस value is ignored by VFS */
	वापस 0;
पूर्ण

व्योम fuse_sync_release(काष्ठा fuse_inode *fi, काष्ठा fuse_file *ff,
		       अचिन्हित पूर्णांक flags)
अणु
	WARN_ON(refcount_पढ़ो(&ff->count) > 1);
	fuse_prepare_release(fi, ff, flags, FUSE_RELEASE);
	/*
	 * iput(शून्य) is a no-op and since the refcount is 1 and everything's
	 * synchronous, we are fine with not करोing igrab() here"
	 */
	fuse_file_put(ff, true, false);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_sync_release);

/*
 * Scramble the ID space with XTEA, so that the value of the files_काष्ठा
 * poपूर्णांकer is not exposed to userspace.
 */
u64 fuse_lock_owner_id(काष्ठा fuse_conn *fc, fl_owner_t id)
अणु
	u32 *k = fc->scramble_key;
	u64 v = (अचिन्हित दीर्घ) id;
	u32 v0 = v;
	u32 v1 = v >> 32;
	u32 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		v0 += ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
		sum += 0x9E3779B9;
		v1 += ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
	पूर्ण

	वापस (u64) v0 + ((u64) v1 << 32);
पूर्ण

काष्ठा fuse_ग_लिखोpage_args अणु
	काष्ठा fuse_io_args ia;
	काष्ठा rb_node ग_लिखोpages_entry;
	काष्ठा list_head queue_entry;
	काष्ठा fuse_ग_लिखोpage_args *next;
	काष्ठा inode *inode;
पूर्ण;

अटल काष्ठा fuse_ग_लिखोpage_args *fuse_find_ग_लिखोback(काष्ठा fuse_inode *fi,
					    pgoff_t idx_from, pgoff_t idx_to)
अणु
	काष्ठा rb_node *n;

	n = fi->ग_लिखोpages.rb_node;

	जबतक (n) अणु
		काष्ठा fuse_ग_लिखोpage_args *wpa;
		pgoff_t curr_index;

		wpa = rb_entry(n, काष्ठा fuse_ग_लिखोpage_args, ग_लिखोpages_entry);
		WARN_ON(get_fuse_inode(wpa->inode) != fi);
		curr_index = wpa->ia.ग_लिखो.in.offset >> PAGE_SHIFT;
		अगर (idx_from >= curr_index + wpa->ia.ap.num_pages)
			n = n->rb_right;
		अन्यथा अगर (idx_to < curr_index)
			n = n->rb_left;
		अन्यथा
			वापस wpa;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Check अगर any page in a range is under ग_लिखोback
 *
 * This is currently करोne by walking the list of ग_लिखोpage requests
 * क्रम the inode, which can be pretty inefficient.
 */
अटल bool fuse_range_is_ग_लिखोback(काष्ठा inode *inode, pgoff_t idx_from,
				   pgoff_t idx_to)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	bool found;

	spin_lock(&fi->lock);
	found = fuse_find_ग_लिखोback(fi, idx_from, idx_to);
	spin_unlock(&fi->lock);

	वापस found;
पूर्ण

अटल अंतरभूत bool fuse_page_is_ग_लिखोback(काष्ठा inode *inode, pgoff_t index)
अणु
	वापस fuse_range_is_ग_लिखोback(inode, index, index);
पूर्ण

/*
 * Wait क्रम page ग_लिखोback to be completed.
 *
 * Since fuse करोesn't rely on the VM ग_लिखोback tracking, this has to
 * use some other means.
 */
अटल व्योम fuse_रुको_on_page_ग_लिखोback(काष्ठा inode *inode, pgoff_t index)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	रुको_event(fi->page_रुकोq, !fuse_page_is_ग_लिखोback(inode, index));
पूर्ण

/*
 * Wait क्रम all pending ग_लिखोpages on the inode to finish.
 *
 * This is currently करोne by blocking further ग_लिखोs with FUSE_NOWRITE
 * and रुकोing क्रम all sent ग_लिखोs to complete.
 *
 * This must be called under i_mutex, otherwise the FUSE_NOWRITE usage
 * could conflict with truncation.
 */
अटल व्योम fuse_sync_ग_लिखोs(काष्ठा inode *inode)
अणु
	fuse_set_noग_लिखो(inode);
	fuse_release_noग_लिखो(inode);
पूर्ण

अटल पूर्णांक fuse_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_flush_in inarg;
	FUSE_ARGS(args);
	पूर्णांक err;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	err = ग_लिखो_inode_now(inode, 1);
	अगर (err)
		वापस err;

	inode_lock(inode);
	fuse_sync_ग_लिखोs(inode);
	inode_unlock(inode);

	err = filemap_check_errors(file->f_mapping);
	अगर (err)
		वापस err;

	err = 0;
	अगर (fm->fc->no_flush)
		जाओ inval_attr_out;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.fh = ff->fh;
	inarg.lock_owner = fuse_lock_owner_id(fm->fc, id);
	args.opcode = FUSE_FLUSH;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.क्रमce = true;

	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_flush = 1;
		err = 0;
	पूर्ण

inval_attr_out:
	/*
	 * In memory i_blocks is not मुख्यtained by fuse, अगर ग_लिखोback cache is
	 * enabled, i_blocks from cached attr may not be accurate.
	 */
	अगर (!err && fm->fc->ग_लिखोback_cache)
		fuse_invalidate_attr(inode);
	वापस err;
पूर्ण

पूर्णांक fuse_fsync_common(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync, पूर्णांक opcode)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_file *ff = file->निजी_data;
	FUSE_ARGS(args);
	काष्ठा fuse_fsync_in inarg;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.fh = ff->fh;
	inarg.fsync_flags = datasync ? FUSE_FSYNC_FDATASYNC : 0;
	args.opcode = opcode;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	वापस fuse_simple_request(fm, &args);
पूर्ण

अटल पूर्णांक fuse_fsync(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	पूर्णांक err;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	inode_lock(inode);

	/*
	 * Start ग_लिखोback against all dirty pages of the inode, then
	 * रुको क्रम all outstanding ग_लिखोs, beक्रमe sending the FSYNC
	 * request.
	 */
	err = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (err)
		जाओ out;

	fuse_sync_ग_लिखोs(inode);

	/*
	 * Due to implementation of fuse ग_लिखोback
	 * file_ग_लिखो_and_रुको_range() करोes not catch errors.
	 * We have to करो this directly after fuse_sync_ग_लिखोs()
	 */
	err = file_check_and_advance_wb_err(file);
	अगर (err)
		जाओ out;

	err = sync_inode_metadata(inode, 1);
	अगर (err)
		जाओ out;

	अगर (fc->no_fsync)
		जाओ out;

	err = fuse_fsync_common(file, start, end, datasync, FUSE_FSYNC);
	अगर (err == -ENOSYS) अणु
		fc->no_fsync = 1;
		err = 0;
	पूर्ण
out:
	inode_unlock(inode);

	वापस err;
पूर्ण

व्योम fuse_पढ़ो_args_fill(काष्ठा fuse_io_args *ia, काष्ठा file *file, loff_t pos,
			 माप_प्रकार count, पूर्णांक opcode)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_args *args = &ia->ap.args;

	ia->पढ़ो.in.fh = ff->fh;
	ia->पढ़ो.in.offset = pos;
	ia->पढ़ो.in.size = count;
	ia->पढ़ो.in.flags = file->f_flags;
	args->opcode = opcode;
	args->nodeid = ff->nodeid;
	args->in_numargs = 1;
	args->in_args[0].size = माप(ia->पढ़ो.in);
	args->in_args[0].value = &ia->पढ़ो.in;
	args->out_argvar = true;
	args->out_numargs = 1;
	args->out_args[0].size = count;
पूर्ण

अटल व्योम fuse_release_user_pages(काष्ठा fuse_args_pages *ap,
				    bool should_dirty)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ap->num_pages; i++) अणु
		अगर (should_dirty)
			set_page_dirty_lock(ap->pages[i]);
		put_page(ap->pages[i]);
	पूर्ण
पूर्ण

अटल व्योम fuse_io_release(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा fuse_io_priv, refcnt));
पूर्ण

अटल sमाप_प्रकार fuse_get_res_by_io(काष्ठा fuse_io_priv *io)
अणु
	अगर (io->err)
		वापस io->err;

	अगर (io->bytes >= 0 && io->ग_लिखो)
		वापस -EIO;

	वापस io->bytes < 0 ? io->size : io->bytes;
पूर्ण

/**
 * In हाल of लघु पढ़ो, the caller sets 'pos' to the position of
 * actual end of fuse request in IO request. Otherwise, अगर bytes_requested
 * == bytes_transferred or rw == WRITE, the caller sets 'pos' to -1.
 *
 * An example:
 * User requested DIO पढ़ो of 64K. It was splitted पूर्णांकo two 32K fuse requests,
 * both submitted asynchronously. The first of them was ACKed by userspace as
 * fully completed (req->out.args[0].size == 32K) resulting in pos == -1. The
 * second request was ACKed as लघु, e.g. only 1K was पढ़ो, resulting in
 * pos == 33K.
 *
 * Thus, when all fuse requests are completed, the minimal non-negative 'pos'
 * will be equal to the length of the दीर्घest contiguous fragment of
 * transferred data starting from the beginning of IO request.
 */
अटल व्योम fuse_aio_complete(काष्ठा fuse_io_priv *io, पूर्णांक err, sमाप_प्रकार pos)
अणु
	पूर्णांक left;

	spin_lock(&io->lock);
	अगर (err)
		io->err = io->err ? : err;
	अन्यथा अगर (pos >= 0 && (io->bytes < 0 || pos < io->bytes))
		io->bytes = pos;

	left = --io->reqs;
	अगर (!left && io->blocking)
		complete(io->करोne);
	spin_unlock(&io->lock);

	अगर (!left && !io->blocking) अणु
		sमाप_प्रकार res = fuse_get_res_by_io(io);

		अगर (res >= 0) अणु
			काष्ठा inode *inode = file_inode(io->iocb->ki_filp);
			काष्ठा fuse_conn *fc = get_fuse_conn(inode);
			काष्ठा fuse_inode *fi = get_fuse_inode(inode);

			spin_lock(&fi->lock);
			fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
			spin_unlock(&fi->lock);
		पूर्ण

		io->iocb->ki_complete(io->iocb, res, 0);
	पूर्ण

	kref_put(&io->refcnt, fuse_io_release);
पूर्ण

अटल काष्ठा fuse_io_args *fuse_io_alloc(काष्ठा fuse_io_priv *io,
					  अचिन्हित पूर्णांक npages)
अणु
	काष्ठा fuse_io_args *ia;

	ia = kzalloc(माप(*ia), GFP_KERNEL);
	अगर (ia) अणु
		ia->io = io;
		ia->ap.pages = fuse_pages_alloc(npages, GFP_KERNEL,
						&ia->ap.descs);
		अगर (!ia->ap.pages) अणु
			kमुक्त(ia);
			ia = शून्य;
		पूर्ण
	पूर्ण
	वापस ia;
पूर्ण

अटल व्योम fuse_io_मुक्त(काष्ठा fuse_io_args *ia)
अणु
	kमुक्त(ia->ap.pages);
	kमुक्त(ia);
पूर्ण

अटल व्योम fuse_aio_complete_req(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
				  पूर्णांक err)
अणु
	काष्ठा fuse_io_args *ia = container_of(args, typeof(*ia), ap.args);
	काष्ठा fuse_io_priv *io = ia->io;
	sमाप_प्रकार pos = -1;

	fuse_release_user_pages(&ia->ap, io->should_dirty);

	अगर (err) अणु
		/* Nothing */
	पूर्ण अन्यथा अगर (io->ग_लिखो) अणु
		अगर (ia->ग_लिखो.out.size > ia->ग_लिखो.in.size) अणु
			err = -EIO;
		पूर्ण अन्यथा अगर (ia->ग_लिखो.in.size != ia->ग_लिखो.out.size) अणु
			pos = ia->ग_लिखो.in.offset - io->offset +
				ia->ग_लिखो.out.size;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 outsize = args->out_args[0].size;

		अगर (ia->पढ़ो.in.size != outsize)
			pos = ia->पढ़ो.in.offset - io->offset + outsize;
	पूर्ण

	fuse_aio_complete(io, err, pos);
	fuse_io_मुक्त(ia);
पूर्ण

अटल sमाप_प्रकार fuse_async_req_send(काष्ठा fuse_mount *fm,
				   काष्ठा fuse_io_args *ia, माप_प्रकार num_bytes)
अणु
	sमाप_प्रकार err;
	काष्ठा fuse_io_priv *io = ia->io;

	spin_lock(&io->lock);
	kref_get(&io->refcnt);
	io->size += num_bytes;
	io->reqs++;
	spin_unlock(&io->lock);

	ia->ap.args.end = fuse_aio_complete_req;
	ia->ap.args.may_block = io->should_dirty;
	err = fuse_simple_background(fm, &ia->ap.args, GFP_KERNEL);
	अगर (err)
		fuse_aio_complete_req(fm, &ia->ap.args, err);

	वापस num_bytes;
पूर्ण

अटल sमाप_प्रकार fuse_send_पढ़ो(काष्ठा fuse_io_args *ia, loff_t pos, माप_प्रकार count,
			      fl_owner_t owner)
अणु
	काष्ठा file *file = ia->io->iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;

	fuse_पढ़ो_args_fill(ia, file, pos, count, FUSE_READ);
	अगर (owner != शून्य) अणु
		ia->पढ़ो.in.पढ़ो_flags |= FUSE_READ_LOCKOWNER;
		ia->पढ़ो.in.lock_owner = fuse_lock_owner_id(fm->fc, owner);
	पूर्ण

	अगर (ia->io->async)
		वापस fuse_async_req_send(fm, ia, count);

	वापस fuse_simple_request(fm, &ia->ap.args);
पूर्ण

अटल व्योम fuse_पढ़ो_update_size(काष्ठा inode *inode, loff_t size,
				  u64 attr_ver)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	spin_lock(&fi->lock);
	अगर (attr_ver == fi->attr_version && size < inode->i_size &&
	    !test_bit(FUSE_I_SIZE_UNSTABLE, &fi->state)) अणु
		fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
		i_size_ग_लिखो(inode, size);
	पूर्ण
	spin_unlock(&fi->lock);
पूर्ण

अटल व्योम fuse_लघु_पढ़ो(काष्ठा inode *inode, u64 attr_ver, माप_प्रकार num_पढ़ो,
			    काष्ठा fuse_args_pages *ap)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * If ग_लिखोback_cache is enabled, a लघु पढ़ो means there's a hole in
	 * the file.  Some data after the hole is in page cache, but has not
	 * reached the client fs yet.  So the hole is not present there.
	 */
	अगर (!fc->ग_लिखोback_cache) अणु
		loff_t pos = page_offset(ap->pages[0]) + num_पढ़ो;
		fuse_पढ़ो_update_size(inode, pos, attr_ver);
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_करो_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	loff_t pos = page_offset(page);
	काष्ठा fuse_page_desc desc = अणु .length = PAGE_SIZE पूर्ण;
	काष्ठा fuse_io_args ia = अणु
		.ap.args.page_zeroing = true,
		.ap.args.out_pages = true,
		.ap.num_pages = 1,
		.ap.pages = &page,
		.ap.descs = &desc,
	पूर्ण;
	sमाप_प्रकार res;
	u64 attr_ver;

	/*
	 * Page ग_लिखोback can extend beyond the lअगरeसमय of the
	 * page-cache page, so make sure we पढ़ो a properly synced
	 * page.
	 */
	fuse_रुको_on_page_ग_लिखोback(inode, page->index);

	attr_ver = fuse_get_attr_version(fm->fc);

	/* Don't overflow end offset */
	अगर (pos + (desc.length - 1) == Lदीर्घ_उच्च)
		desc.length--;

	fuse_पढ़ो_args_fill(&ia, file, pos, desc.length, FUSE_READ);
	res = fuse_simple_request(fm, &ia.ap.args);
	अगर (res < 0)
		वापस res;
	/*
	 * Short पढ़ो means खातापूर्ण.  If file size is larger, truncate it
	 */
	अगर (res < desc.length)
		fuse_लघु_पढ़ो(inode, attr_ver, res, &ia.ap);

	SetPageUptodate(page);

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक err;

	err = -EIO;
	अगर (fuse_is_bad(inode))
		जाओ out;

	err = fuse_करो_पढ़ोpage(file, page);
	fuse_invalidate_aसमय(inode);
 out:
	unlock_page(page);
	वापस err;
पूर्ण

अटल व्योम fuse_पढ़ोpages_end(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			       पूर्णांक err)
अणु
	पूर्णांक i;
	काष्ठा fuse_io_args *ia = container_of(args, typeof(*ia), ap.args);
	काष्ठा fuse_args_pages *ap = &ia->ap;
	माप_प्रकार count = ia->पढ़ो.in.size;
	माप_प्रकार num_पढ़ो = args->out_args[0].size;
	काष्ठा address_space *mapping = शून्य;

	क्रम (i = 0; mapping == शून्य && i < ap->num_pages; i++)
		mapping = ap->pages[i]->mapping;

	अगर (mapping) अणु
		काष्ठा inode *inode = mapping->host;

		/*
		 * Short पढ़ो means खातापूर्ण. If file size is larger, truncate it
		 */
		अगर (!err && num_पढ़ो < count)
			fuse_लघु_पढ़ो(inode, ia->पढ़ो.attr_ver, num_पढ़ो, ap);

		fuse_invalidate_aसमय(inode);
	पूर्ण

	क्रम (i = 0; i < ap->num_pages; i++) अणु
		काष्ठा page *page = ap->pages[i];

		अगर (!err)
			SetPageUptodate(page);
		अन्यथा
			SetPageError(page);
		unlock_page(page);
		put_page(page);
	पूर्ण
	अगर (ia->ff)
		fuse_file_put(ia->ff, false, false);

	fuse_io_मुक्त(ia);
पूर्ण

अटल व्योम fuse_send_पढ़ोpages(काष्ठा fuse_io_args *ia, काष्ठा file *file)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;
	काष्ठा fuse_args_pages *ap = &ia->ap;
	loff_t pos = page_offset(ap->pages[0]);
	माप_प्रकार count = ap->num_pages << PAGE_SHIFT;
	sमाप_प्रकार res;
	पूर्णांक err;

	ap->args.out_pages = true;
	ap->args.page_zeroing = true;
	ap->args.page_replace = true;

	/* Don't overflow end offset */
	अगर (pos + (count - 1) == Lदीर्घ_उच्च) अणु
		count--;
		ap->descs[ap->num_pages - 1].length--;
	पूर्ण
	WARN_ON((loff_t) (pos + count) < 0);

	fuse_पढ़ो_args_fill(ia, file, pos, count, FUSE_READ);
	ia->पढ़ो.attr_ver = fuse_get_attr_version(fm->fc);
	अगर (fm->fc->async_पढ़ो) अणु
		ia->ff = fuse_file_get(ff);
		ap->args.end = fuse_पढ़ोpages_end;
		err = fuse_simple_background(fm, &ap->args, GFP_KERNEL);
		अगर (!err)
			वापस;
	पूर्ण अन्यथा अणु
		res = fuse_simple_request(fm, &ap->args);
		err = res < 0 ? res : 0;
	पूर्ण
	fuse_पढ़ोpages_end(fm, &ap->args, err);
पूर्ण

अटल व्योम fuse_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा inode *inode = rac->mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	अचिन्हित पूर्णांक i, max_pages, nr_pages = 0;

	अगर (fuse_is_bad(inode))
		वापस;

	max_pages = min_t(अचिन्हित पूर्णांक, fc->max_pages,
			fc->max_पढ़ो / PAGE_SIZE);

	क्रम (;;) अणु
		काष्ठा fuse_io_args *ia;
		काष्ठा fuse_args_pages *ap;

		nr_pages = पढ़ोahead_count(rac) - nr_pages;
		अगर (nr_pages > max_pages)
			nr_pages = max_pages;
		अगर (nr_pages == 0)
			अवरोध;
		ia = fuse_io_alloc(शून्य, nr_pages);
		अगर (!ia)
			वापस;
		ap = &ia->ap;
		nr_pages = __पढ़ोahead_batch(rac, ap->pages, nr_pages);
		क्रम (i = 0; i < nr_pages; i++) अणु
			fuse_रुको_on_page_ग_लिखोback(inode,
						    पढ़ोahead_index(rac) + i);
			ap->descs[i].length = PAGE_SIZE;
		पूर्ण
		ap->num_pages = nr_pages;
		fuse_send_पढ़ोpages(ia, rac->file);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार fuse_cache_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = iocb->ki_filp->f_mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * In स्वतः invalidate mode, always update attributes on पढ़ो.
	 * Otherwise, only update अगर we attempt to पढ़ो past खातापूर्ण (to ensure
	 * i_size is up to date).
	 */
	अगर (fc->स्वतः_inval_data ||
	    (iocb->ki_pos + iov_iter_count(to) > i_size_पढ़ो(inode))) अणु
		पूर्णांक err;
		err = fuse_update_attributes(inode, iocb->ki_filp);
		अगर (err)
			वापस err;
	पूर्ण

	वापस generic_file_पढ़ो_iter(iocb, to);
पूर्ण

अटल व्योम fuse_ग_लिखो_args_fill(काष्ठा fuse_io_args *ia, काष्ठा fuse_file *ff,
				 loff_t pos, माप_प्रकार count)
अणु
	काष्ठा fuse_args *args = &ia->ap.args;

	ia->ग_लिखो.in.fh = ff->fh;
	ia->ग_लिखो.in.offset = pos;
	ia->ग_लिखो.in.size = count;
	args->opcode = FUSE_WRITE;
	args->nodeid = ff->nodeid;
	args->in_numargs = 2;
	अगर (ff->fm->fc->minor < 9)
		args->in_args[0].size = FUSE_COMPAT_WRITE_IN_SIZE;
	अन्यथा
		args->in_args[0].size = माप(ia->ग_लिखो.in);
	args->in_args[0].value = &ia->ग_लिखो.in;
	args->in_args[1].size = count;
	args->out_numargs = 1;
	args->out_args[0].size = माप(ia->ग_लिखो.out);
	args->out_args[0].value = &ia->ग_लिखो.out;
पूर्ण

अटल अचिन्हित पूर्णांक fuse_ग_लिखो_flags(काष्ठा kiocb *iocb)
अणु
	अचिन्हित पूर्णांक flags = iocb->ki_filp->f_flags;

	अगर (iocb->ki_flags & IOCB_DSYNC)
		flags |= O_DSYNC;
	अगर (iocb->ki_flags & IOCB_SYNC)
		flags |= O_SYNC;

	वापस flags;
पूर्ण

अटल sमाप_प्रकार fuse_send_ग_लिखो(काष्ठा fuse_io_args *ia, loff_t pos,
			       माप_प्रकार count, fl_owner_t owner)
अणु
	काष्ठा kiocb *iocb = ia->io->iocb;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;
	काष्ठा fuse_ग_लिखो_in *inarg = &ia->ग_लिखो.in;
	sमाप_प्रकार err;

	fuse_ग_लिखो_args_fill(ia, ff, pos, count);
	inarg->flags = fuse_ग_लिखो_flags(iocb);
	अगर (owner != शून्य) अणु
		inarg->ग_लिखो_flags |= FUSE_WRITE_LOCKOWNER;
		inarg->lock_owner = fuse_lock_owner_id(fm->fc, owner);
	पूर्ण

	अगर (ia->io->async)
		वापस fuse_async_req_send(fm, ia, count);

	err = fuse_simple_request(fm, &ia->ap.args);
	अगर (!err && ia->ग_लिखो.out.size > count)
		err = -EIO;

	वापस err ?: ia->ग_लिखो.out.size;
पूर्ण

bool fuse_ग_लिखो_update_size(काष्ठा inode *inode, loff_t pos)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	bool ret = false;

	spin_lock(&fi->lock);
	fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
	अगर (pos > inode->i_size) अणु
		i_size_ग_लिखो(inode, pos);
		ret = true;
	पूर्ण
	spin_unlock(&fi->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार fuse_send_ग_लिखो_pages(काष्ठा fuse_io_args *ia,
				     काष्ठा kiocb *iocb, काष्ठा inode *inode,
				     loff_t pos, माप_प्रकार count)
अणु
	काष्ठा fuse_args_pages *ap = &ia->ap;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;
	अचिन्हित पूर्णांक offset, i;
	bool लघु_ग_लिखो;
	पूर्णांक err;

	क्रम (i = 0; i < ap->num_pages; i++)
		fuse_रुको_on_page_ग_लिखोback(inode, ap->pages[i]->index);

	fuse_ग_लिखो_args_fill(ia, ff, pos, count);
	ia->ग_लिखो.in.flags = fuse_ग_लिखो_flags(iocb);
	अगर (fm->fc->handle_समाप्तpriv_v2 && !capable(CAP_FSETID))
		ia->ग_लिखो.in.ग_लिखो_flags |= FUSE_WRITE_KILL_SUIDGID;

	err = fuse_simple_request(fm, &ap->args);
	अगर (!err && ia->ग_लिखो.out.size > count)
		err = -EIO;

	लघु_ग_लिखो = ia->ग_लिखो.out.size < count;
	offset = ap->descs[0].offset;
	count = ia->ग_लिखो.out.size;
	क्रम (i = 0; i < ap->num_pages; i++) अणु
		काष्ठा page *page = ap->pages[i];

		अगर (err) अणु
			ClearPageUptodate(page);
		पूर्ण अन्यथा अणु
			अगर (count >= PAGE_SIZE - offset)
				count -= PAGE_SIZE - offset;
			अन्यथा अणु
				अगर (लघु_ग_लिखो)
					ClearPageUptodate(page);
				count = 0;
			पूर्ण
			offset = 0;
		पूर्ण
		अगर (ia->ग_लिखो.page_locked && (i == ap->num_pages - 1))
			unlock_page(page);
		put_page(page);
	पूर्ण

	वापस err;
पूर्ण

अटल sमाप_प्रकार fuse_fill_ग_लिखो_pages(काष्ठा fuse_io_args *ia,
				     काष्ठा address_space *mapping,
				     काष्ठा iov_iter *ii, loff_t pos,
				     अचिन्हित पूर्णांक max_pages)
अणु
	काष्ठा fuse_args_pages *ap = &ia->ap;
	काष्ठा fuse_conn *fc = get_fuse_conn(mapping->host);
	अचिन्हित offset = pos & (PAGE_SIZE - 1);
	माप_प्रकार count = 0;
	पूर्णांक err;

	ap->args.in_pages = true;
	ap->descs[0].offset = offset;

	करो अणु
		माप_प्रकार पंचांगp;
		काष्ठा page *page;
		pgoff_t index = pos >> PAGE_SHIFT;
		माप_प्रकार bytes = min_t(माप_प्रकार, PAGE_SIZE - offset,
				     iov_iter_count(ii));

		bytes = min_t(माप_प्रकार, bytes, fc->max_ग_लिखो - count);

 again:
		err = -EFAULT;
		अगर (iov_iter_fault_in_पढ़ोable(ii, bytes))
			अवरोध;

		err = -ENOMEM;
		page = grab_cache_page_ग_लिखो_begin(mapping, index, 0);
		अगर (!page)
			अवरोध;

		अगर (mapping_writably_mapped(mapping))
			flush_dcache_page(page);

		पंचांगp = iov_iter_copy_from_user_atomic(page, ii, offset, bytes);
		flush_dcache_page(page);

		iov_iter_advance(ii, पंचांगp);
		अगर (!पंचांगp) अणु
			unlock_page(page);
			put_page(page);
			bytes = min(bytes, iov_iter_single_seg_count(ii));
			जाओ again;
		पूर्ण

		err = 0;
		ap->pages[ap->num_pages] = page;
		ap->descs[ap->num_pages].length = पंचांगp;
		ap->num_pages++;

		count += पंचांगp;
		pos += पंचांगp;
		offset += पंचांगp;
		अगर (offset == PAGE_SIZE)
			offset = 0;

		/* If we copied full page, mark it uptodate */
		अगर (पंचांगp == PAGE_SIZE)
			SetPageUptodate(page);

		अगर (PageUptodate(page)) अणु
			unlock_page(page);
		पूर्ण अन्यथा अणु
			ia->ग_लिखो.page_locked = true;
			अवरोध;
		पूर्ण
		अगर (!fc->big_ग_लिखोs)
			अवरोध;
	पूर्ण जबतक (iov_iter_count(ii) && count < fc->max_ग_लिखो &&
		 ap->num_pages < max_pages && offset == 0);

	वापस count > 0 ? count : err;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fuse_wr_pages(loff_t pos, माप_प्रकार len,
				     अचिन्हित पूर्णांक max_pages)
अणु
	वापस min_t(अचिन्हित पूर्णांक,
		     ((pos + len - 1) >> PAGE_SHIFT) -
		     (pos >> PAGE_SHIFT) + 1,
		     max_pages);
पूर्ण

अटल sमाप_प्रकार fuse_perक्रमm_ग_लिखो(काष्ठा kiocb *iocb,
				  काष्ठा address_space *mapping,
				  काष्ठा iov_iter *ii, loff_t pos)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	पूर्णांक err = 0;
	sमाप_प्रकार res = 0;

	अगर (inode->i_size < pos + iov_iter_count(ii))
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	करो अणु
		sमाप_प्रकार count;
		काष्ठा fuse_io_args ia = अणुपूर्ण;
		काष्ठा fuse_args_pages *ap = &ia.ap;
		अचिन्हित पूर्णांक nr_pages = fuse_wr_pages(pos, iov_iter_count(ii),
						      fc->max_pages);

		ap->pages = fuse_pages_alloc(nr_pages, GFP_KERNEL, &ap->descs);
		अगर (!ap->pages) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		count = fuse_fill_ग_लिखो_pages(&ia, mapping, ii, pos, nr_pages);
		अगर (count <= 0) अणु
			err = count;
		पूर्ण अन्यथा अणु
			err = fuse_send_ग_लिखो_pages(&ia, iocb, inode,
						    pos, count);
			अगर (!err) अणु
				माप_प्रकार num_written = ia.ग_लिखो.out.size;

				res += num_written;
				pos += num_written;

				/* अवरोध out of the loop on लघु ग_लिखो */
				अगर (num_written != count)
					err = -EIO;
			पूर्ण
		पूर्ण
		kमुक्त(ap->pages);
	पूर्ण जबतक (!err && iov_iter_count(ii));

	अगर (res > 0)
		fuse_ग_लिखो_update_size(inode, pos);

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
	fuse_invalidate_attr(inode);

	वापस res > 0 ? res : err;
पूर्ण

अटल sमाप_प्रकार fuse_cache_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	sमाप_प्रकार written = 0;
	sमाप_प्रकार written_buffered = 0;
	काष्ठा inode *inode = mapping->host;
	sमाप_प्रकार err;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	loff_t endbyte = 0;

	अगर (fc->ग_लिखोback_cache) अणु
		/* Update size (खातापूर्ण optimization) and mode (SUID clearing) */
		err = fuse_update_attributes(mapping->host, file);
		अगर (err)
			वापस err;

		अगर (fc->handle_समाप्तpriv_v2 &&
		    should_हटाओ_suid(file_dentry(file))) अणु
			जाओ ग_लिखोthrough;
		पूर्ण

		वापस generic_file_ग_लिखो_iter(iocb, from);
	पूर्ण

ग_लिखोthrough:
	inode_lock(inode);

	/* We can ग_लिखो back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);

	err = generic_ग_लिखो_checks(iocb, from);
	अगर (err <= 0)
		जाओ out;

	err = file_हटाओ_privs(file);
	अगर (err)
		जाओ out;

	err = file_update_समय(file);
	अगर (err)
		जाओ out;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		loff_t pos = iocb->ki_pos;
		written = generic_file_direct_ग_लिखो(iocb, from);
		अगर (written < 0 || !iov_iter_count(from))
			जाओ out;

		pos += written;

		written_buffered = fuse_perक्रमm_ग_लिखो(iocb, mapping, from, pos);
		अगर (written_buffered < 0) अणु
			err = written_buffered;
			जाओ out;
		पूर्ण
		endbyte = pos + written_buffered - 1;

		err = filemap_ग_लिखो_and_रुको_range(file->f_mapping, pos,
						   endbyte);
		अगर (err)
			जाओ out;

		invalidate_mapping_pages(file->f_mapping,
					 pos >> PAGE_SHIFT,
					 endbyte >> PAGE_SHIFT);

		written += written_buffered;
		iocb->ki_pos = pos + written_buffered;
	पूर्ण अन्यथा अणु
		written = fuse_perक्रमm_ग_लिखो(iocb, mapping, from, iocb->ki_pos);
		अगर (written >= 0)
			iocb->ki_pos += written;
	पूर्ण
out:
	current->backing_dev_info = शून्य;
	inode_unlock(inode);
	अगर (written > 0)
		written = generic_ग_लिखो_sync(iocb, written);

	वापस written ? written : err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fuse_get_user_addr(स्थिर काष्ठा iov_iter *ii)
अणु
	वापस (अचिन्हित दीर्घ)ii->iov->iov_base + ii->iov_offset;
पूर्ण

अटल अंतरभूत माप_प्रकार fuse_get_frag_size(स्थिर काष्ठा iov_iter *ii,
					माप_प्रकार max_size)
अणु
	वापस min(iov_iter_single_seg_count(ii), max_size);
पूर्ण

अटल पूर्णांक fuse_get_user_pages(काष्ठा fuse_args_pages *ap, काष्ठा iov_iter *ii,
			       माप_प्रकार *nbytesp, पूर्णांक ग_लिखो,
			       अचिन्हित पूर्णांक max_pages)
अणु
	माप_प्रकार nbytes = 0;  /* # bytes alपढ़ोy packed in req */
	sमाप_प्रकार ret = 0;

	/* Special हाल क्रम kernel I/O: can copy directly पूर्णांकo the buffer */
	अगर (iov_iter_is_kvec(ii)) अणु
		अचिन्हित दीर्घ user_addr = fuse_get_user_addr(ii);
		माप_प्रकार frag_size = fuse_get_frag_size(ii, *nbytesp);

		अगर (ग_लिखो)
			ap->args.in_args[1].value = (व्योम *) user_addr;
		अन्यथा
			ap->args.out_args[0].value = (व्योम *) user_addr;

		iov_iter_advance(ii, frag_size);
		*nbytesp = frag_size;
		वापस 0;
	पूर्ण

	जबतक (nbytes < *nbytesp && ap->num_pages < max_pages) अणु
		अचिन्हित npages;
		माप_प्रकार start;
		ret = iov_iter_get_pages(ii, &ap->pages[ap->num_pages],
					*nbytesp - nbytes,
					max_pages - ap->num_pages,
					&start);
		अगर (ret < 0)
			अवरोध;

		iov_iter_advance(ii, ret);
		nbytes += ret;

		ret += start;
		npages = (ret + PAGE_SIZE - 1) / PAGE_SIZE;

		ap->descs[ap->num_pages].offset = start;
		fuse_page_descs_length_init(ap->descs, ap->num_pages, npages);

		ap->num_pages += npages;
		ap->descs[ap->num_pages - 1].length -=
			(PAGE_SIZE - ret) & (PAGE_SIZE - 1);
	पूर्ण

	अगर (ग_लिखो)
		ap->args.in_pages = true;
	अन्यथा
		ap->args.out_pages = true;

	*nbytesp = nbytes;

	वापस ret < 0 ? ret : 0;
पूर्ण

sमाप_प्रकार fuse_direct_io(काष्ठा fuse_io_priv *io, काष्ठा iov_iter *iter,
		       loff_t *ppos, पूर्णांक flags)
अणु
	पूर्णांक ग_लिखो = flags & FUSE_DIO_WRITE;
	पूर्णांक cuse = flags & FUSE_DIO_CUSE;
	काष्ठा file *file = io->iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_conn *fc = ff->fm->fc;
	माप_प्रकार nmax = ग_लिखो ? fc->max_ग_लिखो : fc->max_पढ़ो;
	loff_t pos = *ppos;
	माप_प्रकार count = iov_iter_count(iter);
	pgoff_t idx_from = pos >> PAGE_SHIFT;
	pgoff_t idx_to = (pos + count - 1) >> PAGE_SHIFT;
	sमाप_प्रकार res = 0;
	पूर्णांक err = 0;
	काष्ठा fuse_io_args *ia;
	अचिन्हित पूर्णांक max_pages;

	max_pages = iov_iter_npages(iter, fc->max_pages);
	ia = fuse_io_alloc(io, max_pages);
	अगर (!ia)
		वापस -ENOMEM;

	ia->io = io;
	अगर (!cuse && fuse_range_is_ग_लिखोback(inode, idx_from, idx_to)) अणु
		अगर (!ग_लिखो)
			inode_lock(inode);
		fuse_sync_ग_लिखोs(inode);
		अगर (!ग_लिखो)
			inode_unlock(inode);
	पूर्ण

	io->should_dirty = !ग_लिखो && iter_is_iovec(iter);
	जबतक (count) अणु
		sमाप_प्रकार nres;
		fl_owner_t owner = current->files;
		माप_प्रकार nbytes = min(count, nmax);

		err = fuse_get_user_pages(&ia->ap, iter, &nbytes, ग_लिखो,
					  max_pages);
		अगर (err && !nbytes)
			अवरोध;

		अगर (ग_लिखो) अणु
			अगर (!capable(CAP_FSETID))
				ia->ग_लिखो.in.ग_लिखो_flags |= FUSE_WRITE_KILL_SUIDGID;

			nres = fuse_send_ग_लिखो(ia, pos, nbytes, owner);
		पूर्ण अन्यथा अणु
			nres = fuse_send_पढ़ो(ia, pos, nbytes, owner);
		पूर्ण

		अगर (!io->async || nres < 0) अणु
			fuse_release_user_pages(&ia->ap, io->should_dirty);
			fuse_io_मुक्त(ia);
		पूर्ण
		ia = शून्य;
		अगर (nres < 0) अणु
			iov_iter_revert(iter, nbytes);
			err = nres;
			अवरोध;
		पूर्ण
		WARN_ON(nres > nbytes);

		count -= nres;
		res += nres;
		pos += nres;
		अगर (nres != nbytes) अणु
			iov_iter_revert(iter, nbytes - nres);
			अवरोध;
		पूर्ण
		अगर (count) अणु
			max_pages = iov_iter_npages(iter, fc->max_pages);
			ia = fuse_io_alloc(io, max_pages);
			अगर (!ia)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (ia)
		fuse_io_मुक्त(ia);
	अगर (res > 0)
		*ppos = pos;

	वापस res > 0 ? res : err;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_direct_io);

अटल sमाप_प्रकार __fuse_direct_पढ़ो(काष्ठा fuse_io_priv *io,
				  काष्ठा iov_iter *iter,
				  loff_t *ppos)
अणु
	sमाप_प्रकार res;
	काष्ठा inode *inode = file_inode(io->iocb->ki_filp);

	res = fuse_direct_io(io, iter, ppos, 0);

	fuse_invalidate_aसमय(inode);

	वापस res;
पूर्ण

अटल sमाप_प्रकार fuse_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter);

अटल sमाप_प्रकार fuse_direct_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	sमाप_प्रकार res;

	अगर (!is_sync_kiocb(iocb) && iocb->ki_flags & IOCB_सूचीECT) अणु
		res = fuse_direct_IO(iocb, to);
	पूर्ण अन्यथा अणु
		काष्ठा fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);

		res = __fuse_direct_पढ़ो(&io, to, &iocb->ki_pos);
	पूर्ण

	वापस res;
पूर्ण

अटल sमाप_प्रकार fuse_direct_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);
	sमाप_प्रकार res;

	/* Don't allow parallel ग_लिखोs to the same file */
	inode_lock(inode);
	res = generic_ग_लिखो_checks(iocb, from);
	अगर (res > 0) अणु
		अगर (!is_sync_kiocb(iocb) && iocb->ki_flags & IOCB_सूचीECT) अणु
			res = fuse_direct_IO(iocb, from);
		पूर्ण अन्यथा अणु
			res = fuse_direct_io(&io, from, &iocb->ki_pos,
					     FUSE_DIO_WRITE);
		पूर्ण
	पूर्ण
	fuse_invalidate_attr(inode);
	अगर (res > 0)
		fuse_ग_लिखो_update_size(inode, iocb->ki_pos);
	inode_unlock(inode);

	वापस res;
पूर्ण

अटल sमाप_प्रकार fuse_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (FUSE_IS_DAX(inode))
		वापस fuse_dax_पढ़ो_iter(iocb, to);

	अगर (!(ff->खोलो_flags & FOPEN_सूचीECT_IO))
		वापस fuse_cache_पढ़ो_iter(iocb, to);
	अन्यथा
		वापस fuse_direct_पढ़ो_iter(iocb, to);
पूर्ण

अटल sमाप_प्रकार fuse_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (FUSE_IS_DAX(inode))
		वापस fuse_dax_ग_लिखो_iter(iocb, from);

	अगर (!(ff->खोलो_flags & FOPEN_सूचीECT_IO))
		वापस fuse_cache_ग_लिखो_iter(iocb, from);
	अन्यथा
		वापस fuse_direct_ग_लिखो_iter(iocb, from);
पूर्ण

अटल व्योम fuse_ग_लिखोpage_मुक्त(काष्ठा fuse_ग_लिखोpage_args *wpa)
अणु
	काष्ठा fuse_args_pages *ap = &wpa->ia.ap;
	पूर्णांक i;

	क्रम (i = 0; i < ap->num_pages; i++)
		__मुक्त_page(ap->pages[i]);

	अगर (wpa->ia.ff)
		fuse_file_put(wpa->ia.ff, false, false);

	kमुक्त(ap->pages);
	kमुक्त(wpa);
पूर्ण

अटल व्योम fuse_ग_लिखोpage_finish(काष्ठा fuse_mount *fm,
				  काष्ठा fuse_ग_लिखोpage_args *wpa)
अणु
	काष्ठा fuse_args_pages *ap = &wpa->ia.ap;
	काष्ठा inode *inode = wpa->inode;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
	पूर्णांक i;

	क्रम (i = 0; i < ap->num_pages; i++) अणु
		dec_wb_stat(&bdi->wb, WB_WRITEBACK);
		dec_node_page_state(ap->pages[i], NR_WRITEBACK_TEMP);
		wb_ग_लिखोout_inc(&bdi->wb);
	पूर्ण
	wake_up(&fi->page_रुकोq);
पूर्ण

/* Called under fi->lock, may release and reacquire it */
अटल व्योम fuse_send_ग_लिखोpage(काष्ठा fuse_mount *fm,
				काष्ठा fuse_ग_लिखोpage_args *wpa, loff_t size)
__releases(fi->lock)
__acquires(fi->lock)
अणु
	काष्ठा fuse_ग_लिखोpage_args *aux, *next;
	काष्ठा fuse_inode *fi = get_fuse_inode(wpa->inode);
	काष्ठा fuse_ग_लिखो_in *inarg = &wpa->ia.ग_लिखो.in;
	काष्ठा fuse_args *args = &wpa->ia.ap.args;
	__u64 data_size = wpa->ia.ap.num_pages * PAGE_SIZE;
	पूर्णांक err;

	fi->ग_लिखोctr++;
	अगर (inarg->offset + data_size <= size) अणु
		inarg->size = data_size;
	पूर्ण अन्यथा अगर (inarg->offset < size) अणु
		inarg->size = size - inarg->offset;
	पूर्ण अन्यथा अणु
		/* Got truncated off completely */
		जाओ out_मुक्त;
	पूर्ण

	args->in_args[1].size = inarg->size;
	args->क्रमce = true;
	args->nocreds = true;

	err = fuse_simple_background(fm, args, GFP_ATOMIC);
	अगर (err == -ENOMEM) अणु
		spin_unlock(&fi->lock);
		err = fuse_simple_background(fm, args, GFP_NOFS | __GFP_NOFAIL);
		spin_lock(&fi->lock);
	पूर्ण

	/* Fails on broken connection only */
	अगर (unlikely(err))
		जाओ out_मुक्त;

	वापस;

 out_मुक्त:
	fi->ग_लिखोctr--;
	rb_erase(&wpa->ग_लिखोpages_entry, &fi->ग_लिखोpages);
	fuse_ग_लिखोpage_finish(fm, wpa);
	spin_unlock(&fi->lock);

	/* After fuse_ग_लिखोpage_finish() aux request list is निजी */
	क्रम (aux = wpa->next; aux; aux = next) अणु
		next = aux->next;
		aux->next = शून्य;
		fuse_ग_लिखोpage_मुक्त(aux);
	पूर्ण

	fuse_ग_लिखोpage_मुक्त(wpa);
	spin_lock(&fi->lock);
पूर्ण

/*
 * If fi->ग_लिखोctr is positive (no truncate or fsync going on) send
 * all queued ग_लिखोpage requests.
 *
 * Called with fi->lock
 */
व्योम fuse_flush_ग_लिखोpages(काष्ठा inode *inode)
__releases(fi->lock)
__acquires(fi->lock)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	loff_t crop = i_size_पढ़ो(inode);
	काष्ठा fuse_ग_लिखोpage_args *wpa;

	जबतक (fi->ग_लिखोctr >= 0 && !list_empty(&fi->queued_ग_लिखोs)) अणु
		wpa = list_entry(fi->queued_ग_लिखोs.next,
				 काष्ठा fuse_ग_लिखोpage_args, queue_entry);
		list_del_init(&wpa->queue_entry);
		fuse_send_ग_लिखोpage(fm, wpa, crop);
	पूर्ण
पूर्ण

अटल काष्ठा fuse_ग_लिखोpage_args *fuse_insert_ग_लिखोback(काष्ठा rb_root *root,
						काष्ठा fuse_ग_लिखोpage_args *wpa)
अणु
	pgoff_t idx_from = wpa->ia.ग_लिखो.in.offset >> PAGE_SHIFT;
	pgoff_t idx_to = idx_from + wpa->ia.ap.num_pages - 1;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node  *parent = शून्य;

	WARN_ON(!wpa->ia.ap.num_pages);
	जबतक (*p) अणु
		काष्ठा fuse_ग_लिखोpage_args *curr;
		pgoff_t curr_index;

		parent = *p;
		curr = rb_entry(parent, काष्ठा fuse_ग_लिखोpage_args,
				ग_लिखोpages_entry);
		WARN_ON(curr->inode != wpa->inode);
		curr_index = curr->ia.ग_लिखो.in.offset >> PAGE_SHIFT;

		अगर (idx_from >= curr_index + curr->ia.ap.num_pages)
			p = &(*p)->rb_right;
		अन्यथा अगर (idx_to < curr_index)
			p = &(*p)->rb_left;
		अन्यथा
			वापस curr;
	पूर्ण

	rb_link_node(&wpa->ग_लिखोpages_entry, parent, p);
	rb_insert_color(&wpa->ग_लिखोpages_entry, root);
	वापस शून्य;
पूर्ण

अटल व्योम tree_insert(काष्ठा rb_root *root, काष्ठा fuse_ग_लिखोpage_args *wpa)
अणु
	WARN_ON(fuse_insert_ग_लिखोback(root, wpa));
पूर्ण

अटल व्योम fuse_ग_लिखोpage_end(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			       पूर्णांक error)
अणु
	काष्ठा fuse_ग_लिखोpage_args *wpa =
		container_of(args, typeof(*wpa), ia.ap.args);
	काष्ठा inode *inode = wpa->inode;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	mapping_set_error(inode->i_mapping, error);
	/*
	 * A ग_लिखोback finished and this might have updated mसमय/स_समय on
	 * server making local mसमय/स_समय stale.  Hence invalidate attrs.
	 * Do this only अगर ग_लिखोback_cache is not enabled.  If ग_लिखोback_cache
	 * is enabled, we trust local स_समय/mसमय.
	 */
	अगर (!fc->ग_लिखोback_cache)
		fuse_invalidate_attr(inode);
	spin_lock(&fi->lock);
	rb_erase(&wpa->ग_लिखोpages_entry, &fi->ग_लिखोpages);
	जबतक (wpa->next) अणु
		काष्ठा fuse_mount *fm = get_fuse_mount(inode);
		काष्ठा fuse_ग_लिखो_in *inarg = &wpa->ia.ग_लिखो.in;
		काष्ठा fuse_ग_लिखोpage_args *next = wpa->next;

		wpa->next = next->next;
		next->next = शून्य;
		next->ia.ff = fuse_file_get(wpa->ia.ff);
		tree_insert(&fi->ग_लिखोpages, next);

		/*
		 * Skip fuse_flush_ग_लिखोpages() to make it easy to crop requests
		 * based on primary request size.
		 *
		 * 1st हाल (trivial): there are no concurrent activities using
		 * fuse_set/release_noग_लिखो.  Then we're on safe side because
		 * fuse_flush_ग_लिखोpages() would call fuse_send_ग_लिखोpage()
		 * anyway.
		 *
		 * 2nd हाल: someone called fuse_set_noग_लिखो and it is रुकोing
		 * now क्रम completion of all in-flight requests.  This happens
		 * rarely and no more than once per page, so this should be
		 * okay.
		 *
		 * 3rd हाल: someone (e.g. fuse_करो_setattr()) is in the middle
		 * of fuse_set_noग_लिखो..fuse_release_noग_लिखो section.  The fact
		 * that fuse_set_noग_लिखो वापसed implies that all in-flight
		 * requests were completed aदीर्घ with all of their secondary
		 * requests.  Further primary requests are blocked by negative
		 * ग_लिखोctr.  Hence there cannot be any in-flight requests and
		 * no invocations of fuse_ग_लिखोpage_end() जबतक we're in
		 * fuse_set_noग_लिखो..fuse_release_noग_लिखो section.
		 */
		fuse_send_ग_लिखोpage(fm, next, inarg->offset + inarg->size);
	पूर्ण
	fi->ग_लिखोctr--;
	fuse_ग_लिखोpage_finish(fm, wpa);
	spin_unlock(&fi->lock);
	fuse_ग_लिखोpage_मुक्त(wpa);
पूर्ण

अटल काष्ठा fuse_file *__fuse_ग_लिखो_file_get(काष्ठा fuse_conn *fc,
					       काष्ठा fuse_inode *fi)
अणु
	काष्ठा fuse_file *ff = शून्य;

	spin_lock(&fi->lock);
	अगर (!list_empty(&fi->ग_लिखो_files)) अणु
		ff = list_entry(fi->ग_लिखो_files.next, काष्ठा fuse_file,
				ग_लिखो_entry);
		fuse_file_get(ff);
	पूर्ण
	spin_unlock(&fi->lock);

	वापस ff;
पूर्ण

अटल काष्ठा fuse_file *fuse_ग_लिखो_file_get(काष्ठा fuse_conn *fc,
					     काष्ठा fuse_inode *fi)
अणु
	काष्ठा fuse_file *ff = __fuse_ग_लिखो_file_get(fc, fi);
	WARN_ON(!ff);
	वापस ff;
पूर्ण

पूर्णांक fuse_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_file *ff;
	पूर्णांक err;

	ff = __fuse_ग_लिखो_file_get(fc, fi);
	err = fuse_flush_बार(inode, ff);
	अगर (ff)
		fuse_file_put(ff, false, false);

	वापस err;
पूर्ण

अटल काष्ठा fuse_ग_लिखोpage_args *fuse_ग_लिखोpage_args_alloc(व्योम)
अणु
	काष्ठा fuse_ग_लिखोpage_args *wpa;
	काष्ठा fuse_args_pages *ap;

	wpa = kzalloc(माप(*wpa), GFP_NOFS);
	अगर (wpa) अणु
		ap = &wpa->ia.ap;
		ap->num_pages = 0;
		ap->pages = fuse_pages_alloc(1, GFP_NOFS, &ap->descs);
		अगर (!ap->pages) अणु
			kमुक्त(wpa);
			wpa = शून्य;
		पूर्ण
	पूर्ण
	वापस wpa;

पूर्ण

अटल पूर्णांक fuse_ग_लिखोpage_locked(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_ग_लिखोpage_args *wpa;
	काष्ठा fuse_args_pages *ap;
	काष्ठा page *पंचांगp_page;
	पूर्णांक error = -ENOMEM;

	set_page_ग_लिखोback(page);

	wpa = fuse_ग_लिखोpage_args_alloc();
	अगर (!wpa)
		जाओ err;
	ap = &wpa->ia.ap;

	पंचांगp_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (!पंचांगp_page)
		जाओ err_मुक्त;

	error = -EIO;
	wpa->ia.ff = fuse_ग_लिखो_file_get(fc, fi);
	अगर (!wpa->ia.ff)
		जाओ err_nofile;

	fuse_ग_लिखो_args_fill(&wpa->ia, wpa->ia.ff, page_offset(page), 0);

	copy_highpage(पंचांगp_page, page);
	wpa->ia.ग_लिखो.in.ग_लिखो_flags |= FUSE_WRITE_CACHE;
	wpa->next = शून्य;
	ap->args.in_pages = true;
	ap->num_pages = 1;
	ap->pages[0] = पंचांगp_page;
	ap->descs[0].offset = 0;
	ap->descs[0].length = PAGE_SIZE;
	ap->args.end = fuse_ग_लिखोpage_end;
	wpa->inode = inode;

	inc_wb_stat(&inode_to_bdi(inode)->wb, WB_WRITEBACK);
	inc_node_page_state(पंचांगp_page, NR_WRITEBACK_TEMP);

	spin_lock(&fi->lock);
	tree_insert(&fi->ग_लिखोpages, wpa);
	list_add_tail(&wpa->queue_entry, &fi->queued_ग_लिखोs);
	fuse_flush_ग_लिखोpages(inode);
	spin_unlock(&fi->lock);

	end_page_ग_लिखोback(page);

	वापस 0;

err_nofile:
	__मुक्त_page(पंचांगp_page);
err_मुक्त:
	kमुक्त(wpa);
err:
	mapping_set_error(page->mapping, error);
	end_page_ग_लिखोback(page);
	वापस error;
पूर्ण

अटल पूर्णांक fuse_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err;

	अगर (fuse_page_is_ग_लिखोback(page->mapping->host, page->index)) अणु
		/*
		 * ->ग_लिखोpages() should be called क्रम sync() and मित्रs.  We
		 * should only get here on direct reclaim and then we are
		 * allowed to skip a page which is alपढ़ोy in flight
		 */
		WARN_ON(wbc->sync_mode == WB_SYNC_ALL);

		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	err = fuse_ग_लिखोpage_locked(page);
	unlock_page(page);

	वापस err;
पूर्ण

काष्ठा fuse_fill_wb_data अणु
	काष्ठा fuse_ग_लिखोpage_args *wpa;
	काष्ठा fuse_file *ff;
	काष्ठा inode *inode;
	काष्ठा page **orig_pages;
	अचिन्हित पूर्णांक max_pages;
पूर्ण;

अटल bool fuse_pages_पुनः_स्मृति(काष्ठा fuse_fill_wb_data *data)
अणु
	काष्ठा fuse_args_pages *ap = &data->wpa->ia.ap;
	काष्ठा fuse_conn *fc = get_fuse_conn(data->inode);
	काष्ठा page **pages;
	काष्ठा fuse_page_desc *descs;
	अचिन्हित पूर्णांक npages = min_t(अचिन्हित पूर्णांक,
				    max_t(अचिन्हित पूर्णांक, data->max_pages * 2,
					  FUSE_DEFAULT_MAX_PAGES_PER_REQ),
				    fc->max_pages);
	WARN_ON(npages <= data->max_pages);

	pages = fuse_pages_alloc(npages, GFP_NOFS, &descs);
	अगर (!pages)
		वापस false;

	स_नकल(pages, ap->pages, माप(काष्ठा page *) * ap->num_pages);
	स_नकल(descs, ap->descs, माप(काष्ठा fuse_page_desc) * ap->num_pages);
	kमुक्त(ap->pages);
	ap->pages = pages;
	ap->descs = descs;
	data->max_pages = npages;

	वापस true;
पूर्ण

अटल व्योम fuse_ग_लिखोpages_send(काष्ठा fuse_fill_wb_data *data)
अणु
	काष्ठा fuse_ग_लिखोpage_args *wpa = data->wpa;
	काष्ठा inode *inode = data->inode;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	पूर्णांक num_pages = wpa->ia.ap.num_pages;
	पूर्णांक i;

	wpa->ia.ff = fuse_file_get(data->ff);
	spin_lock(&fi->lock);
	list_add_tail(&wpa->queue_entry, &fi->queued_ग_लिखोs);
	fuse_flush_ग_लिखोpages(inode);
	spin_unlock(&fi->lock);

	क्रम (i = 0; i < num_pages; i++)
		end_page_ग_लिखोback(data->orig_pages[i]);
पूर्ण

/*
 * Check under fi->lock अगर the page is under ग_लिखोback, and insert it onto the
 * rb_tree अगर not. Otherwise iterate auxiliary ग_लिखो requests, to see अगर there's
 * one alपढ़ोy added क्रम a page at this offset.  If there's none, then insert
 * this new request onto the auxiliary list, otherwise reuse the existing one by
 * swapping the new temp page with the old one.
 */
अटल bool fuse_ग_लिखोpage_add(काष्ठा fuse_ग_लिखोpage_args *new_wpa,
			       काष्ठा page *page)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(new_wpa->inode);
	काष्ठा fuse_ग_लिखोpage_args *पंचांगp;
	काष्ठा fuse_ग_लिखोpage_args *old_wpa;
	काष्ठा fuse_args_pages *new_ap = &new_wpa->ia.ap;

	WARN_ON(new_ap->num_pages != 0);
	new_ap->num_pages = 1;

	spin_lock(&fi->lock);
	old_wpa = fuse_insert_ग_लिखोback(&fi->ग_लिखोpages, new_wpa);
	अगर (!old_wpa) अणु
		spin_unlock(&fi->lock);
		वापस true;
	पूर्ण

	क्रम (पंचांगp = old_wpa->next; पंचांगp; पंचांगp = पंचांगp->next) अणु
		pgoff_t curr_index;

		WARN_ON(पंचांगp->inode != new_wpa->inode);
		curr_index = पंचांगp->ia.ग_लिखो.in.offset >> PAGE_SHIFT;
		अगर (curr_index == page->index) अणु
			WARN_ON(पंचांगp->ia.ap.num_pages != 1);
			swap(पंचांगp->ia.ap.pages[0], new_ap->pages[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!पंचांगp) अणु
		new_wpa->next = old_wpa->next;
		old_wpa->next = new_wpa;
	पूर्ण

	spin_unlock(&fi->lock);

	अगर (पंचांगp) अणु
		काष्ठा backing_dev_info *bdi = inode_to_bdi(new_wpa->inode);

		dec_wb_stat(&bdi->wb, WB_WRITEBACK);
		dec_node_page_state(new_ap->pages[0], NR_WRITEBACK_TEMP);
		wb_ग_लिखोout_inc(&bdi->wb);
		fuse_ग_लिखोpage_मुक्त(new_wpa);
	पूर्ण

	वापस false;
पूर्ण

अटल bool fuse_ग_लिखोpage_need_send(काष्ठा fuse_conn *fc, काष्ठा page *page,
				     काष्ठा fuse_args_pages *ap,
				     काष्ठा fuse_fill_wb_data *data)
अणु
	WARN_ON(!ap->num_pages);

	/*
	 * Being under ग_लिखोback is unlikely but possible.  For example direct
	 * पढ़ो to an mmaped fuse file will set the page dirty twice; once when
	 * the pages are faulted with get_user_pages(), and then after the पढ़ो
	 * completed.
	 */
	अगर (fuse_page_is_ग_लिखोback(data->inode, page->index))
		वापस true;

	/* Reached max pages */
	अगर (ap->num_pages == fc->max_pages)
		वापस true;

	/* Reached max ग_लिखो bytes */
	अगर ((ap->num_pages + 1) * PAGE_SIZE > fc->max_ग_लिखो)
		वापस true;

	/* Discontinuity */
	अगर (data->orig_pages[ap->num_pages - 1]->index + 1 != page->index)
		वापस true;

	/* Need to grow the pages array?  If so, did the expansion fail? */
	अगर (ap->num_pages == data->max_pages && !fuse_pages_पुनः_स्मृति(data))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक fuse_ग_लिखोpages_fill(काष्ठा page *page,
		काष्ठा ग_लिखोback_control *wbc, व्योम *_data)
अणु
	काष्ठा fuse_fill_wb_data *data = _data;
	काष्ठा fuse_ग_लिखोpage_args *wpa = data->wpa;
	काष्ठा fuse_args_pages *ap = &wpa->ia.ap;
	काष्ठा inode *inode = data->inode;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा page *पंचांगp_page;
	पूर्णांक err;

	अगर (!data->ff) अणु
		err = -EIO;
		data->ff = fuse_ग_लिखो_file_get(fc, fi);
		अगर (!data->ff)
			जाओ out_unlock;
	पूर्ण

	अगर (wpa && fuse_ग_लिखोpage_need_send(fc, page, ap, data)) अणु
		fuse_ग_लिखोpages_send(data);
		data->wpa = शून्य;
	पूर्ण

	err = -ENOMEM;
	पंचांगp_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (!पंचांगp_page)
		जाओ out_unlock;

	/*
	 * The page must not be redirtied until the ग_लिखोout is completed
	 * (i.e. userspace has sent a reply to the ग_लिखो request).  Otherwise
	 * there could be more than one temporary page instance क्रम each real
	 * page.
	 *
	 * This is ensured by holding the page lock in page_mkग_लिखो() जबतक
	 * checking fuse_page_is_ग_लिखोback().  We alपढ़ोy hold the page lock
	 * since clear_page_dirty_क्रम_io() and keep it held until we add the
	 * request to the fi->ग_लिखोpages list and increment ap->num_pages.
	 * After this fuse_page_is_ग_लिखोback() will indicate that the page is
	 * under ग_लिखोback, so we can release the page lock.
	 */
	अगर (data->wpa == शून्य) अणु
		err = -ENOMEM;
		wpa = fuse_ग_लिखोpage_args_alloc();
		अगर (!wpa) अणु
			__मुक्त_page(पंचांगp_page);
			जाओ out_unlock;
		पूर्ण
		data->max_pages = 1;

		ap = &wpa->ia.ap;
		fuse_ग_लिखो_args_fill(&wpa->ia, data->ff, page_offset(page), 0);
		wpa->ia.ग_लिखो.in.ग_लिखो_flags |= FUSE_WRITE_CACHE;
		wpa->next = शून्य;
		ap->args.in_pages = true;
		ap->args.end = fuse_ग_लिखोpage_end;
		ap->num_pages = 0;
		wpa->inode = inode;
	पूर्ण
	set_page_ग_लिखोback(page);

	copy_highpage(पंचांगp_page, page);
	ap->pages[ap->num_pages] = पंचांगp_page;
	ap->descs[ap->num_pages].offset = 0;
	ap->descs[ap->num_pages].length = PAGE_SIZE;
	data->orig_pages[ap->num_pages] = page;

	inc_wb_stat(&inode_to_bdi(inode)->wb, WB_WRITEBACK);
	inc_node_page_state(पंचांगp_page, NR_WRITEBACK_TEMP);

	err = 0;
	अगर (data->wpa) अणु
		/*
		 * Protected by fi->lock against concurrent access by
		 * fuse_page_is_ग_लिखोback().
		 */
		spin_lock(&fi->lock);
		ap->num_pages++;
		spin_unlock(&fi->lock);
	पूर्ण अन्यथा अगर (fuse_ग_लिखोpage_add(wpa, page)) अणु
		data->wpa = wpa;
	पूर्ण अन्यथा अणु
		end_page_ग_लिखोback(page);
	पूर्ण
out_unlock:
	unlock_page(page);

	वापस err;
पूर्ण

अटल पूर्णांक fuse_ग_लिखोpages(काष्ठा address_space *mapping,
			   काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_fill_wb_data data;
	पूर्णांक err;

	err = -EIO;
	अगर (fuse_is_bad(inode))
		जाओ out;

	data.inode = inode;
	data.wpa = शून्य;
	data.ff = शून्य;

	err = -ENOMEM;
	data.orig_pages = kसुस्मृति(fc->max_pages,
				  माप(काष्ठा page *),
				  GFP_NOFS);
	अगर (!data.orig_pages)
		जाओ out;

	err = ग_लिखो_cache_pages(mapping, wbc, fuse_ग_लिखोpages_fill, &data);
	अगर (data.wpa) अणु
		WARN_ON(!data.wpa->ia.ap.num_pages);
		fuse_ग_लिखोpages_send(&data);
	पूर्ण
	अगर (data.ff)
		fuse_file_put(data.ff, false, false);

	kमुक्त(data.orig_pages);
out:
	वापस err;
पूर्ण

/*
 * It's worthy to make sure that space is reserved on disk क्रम the ग_लिखो,
 * but how to implement it without समाप्तing perक्रमmance need more thinking.
 */
अटल पूर्णांक fuse_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित len, अचिन्हित flags,
		काष्ठा page **pagep, व्योम **fsdata)
अणु
	pgoff_t index = pos >> PAGE_SHIFT;
	काष्ठा fuse_conn *fc = get_fuse_conn(file_inode(file));
	काष्ठा page *page;
	loff_t fsize;
	पूर्णांक err = -ENOMEM;

	WARN_ON(!fc->ग_लिखोback_cache);

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		जाओ error;

	fuse_रुको_on_page_ग_लिखोback(mapping->host, page->index);

	अगर (PageUptodate(page) || len == PAGE_SIZE)
		जाओ success;
	/*
	 * Check अगर the start this page comes after the end of file, in which
	 * हाल the पढ़ोpage can be optimized away.
	 */
	fsize = i_size_पढ़ो(mapping->host);
	अगर (fsize <= (pos & PAGE_MASK)) अणु
		माप_प्रकार off = pos & ~PAGE_MASK;
		अगर (off)
			zero_user_segment(page, 0, off);
		जाओ success;
	पूर्ण
	err = fuse_करो_पढ़ोpage(file, page);
	अगर (err)
		जाओ cleanup;
success:
	*pagep = page;
	वापस 0;

cleanup:
	unlock_page(page);
	put_page(page);
error:
	वापस err;
पूर्ण

अटल पूर्णांक fuse_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित len, अचिन्हित copied,
		काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;

	/* Haven't copied anything?  Skip zeroing, size extending, dirtying. */
	अगर (!copied)
		जाओ unlock;

	अगर (!PageUptodate(page)) अणु
		/* Zero any unwritten bytes at the end of the page */
		माप_प्रकार enकरोff = (pos + copied) & ~PAGE_MASK;
		अगर (enकरोff)
			zero_user_segment(page, enकरोff, PAGE_SIZE);
		SetPageUptodate(page);
	पूर्ण

	fuse_ग_लिखो_update_size(inode, pos + copied);
	set_page_dirty(page);

unlock:
	unlock_page(page);
	put_page(page);

	वापस copied;
पूर्ण

अटल पूर्णांक fuse_launder_page(काष्ठा page *page)
अणु
	पूर्णांक err = 0;
	अगर (clear_page_dirty_क्रम_io(page)) अणु
		काष्ठा inode *inode = page->mapping->host;

		/* Serialize with pending ग_लिखोback क्रम the same page */
		fuse_रुको_on_page_ग_लिखोback(inode, page->index);
		err = fuse_ग_लिखोpage_locked(page);
		अगर (!err)
			fuse_रुको_on_page_ग_लिखोback(inode, page->index);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Write back dirty pages now, because there may not be any suitable
 * खोलो files later
 */
अटल व्योम fuse_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	filemap_ग_लिखो_and_रुको(vma->vm_file->f_mapping);
पूर्ण

/*
 * Wait क्रम ग_लिखोback against this page to complete beक्रमe allowing it
 * to be marked dirty again, and hence written back again, possibly
 * beक्रमe the previous ग_लिखोpage completed.
 *
 * Block here, instead of in ->ग_लिखोpage(), so that the userspace fs
 * can only block processes actually operating on the fileप्रणाली.
 *
 * Otherwise unprivileged userspace fs would be able to block
 * unrelated:
 *
 * - page migration
 * - sync(2)
 * - try_to_मुक्त_pages() with order > PAGE_ALLOC_COSTLY_ORDER
 */
अटल vm_fault_t fuse_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);

	file_update_समय(vmf->vma->vm_file);
	lock_page(page);
	अगर (page->mapping != inode->i_mapping) अणु
		unlock_page(page);
		वापस VM_FAULT_NOPAGE;
	पूर्ण

	fuse_रुको_on_page_ग_लिखोback(inode, page->index);
	वापस VM_FAULT_LOCKED;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा fuse_file_vm_ops = अणु
	.बंद		= fuse_vma_बंद,
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= fuse_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक fuse_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;

	/* DAX mmap is superior to direct_io mmap */
	अगर (FUSE_IS_DAX(file_inode(file)))
		वापस fuse_dax_mmap(file, vma);

	अगर (ff->खोलो_flags & FOPEN_सूचीECT_IO) अणु
		/* Can't provide the coherency needed क्रम MAP_SHARED */
		अगर (vma->vm_flags & VM_MAYSHARE)
			वापस -ENODEV;

		invalidate_inode_pages2(file->f_mapping);

		वापस generic_file_mmap(file, vma);
	पूर्ण

	अगर ((vma->vm_flags & VM_SHARED) && (vma->vm_flags & VM_MAYWRITE))
		fuse_link_ग_लिखो_file(file);

	file_accessed(file);
	vma->vm_ops = &fuse_file_vm_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक convert_fuse_file_lock(काष्ठा fuse_conn *fc,
				  स्थिर काष्ठा fuse_file_lock *ffl,
				  काष्ठा file_lock *fl)
अणु
	चयन (ffl->type) अणु
	हाल F_UNLCK:
		अवरोध;

	हाल F_RDLCK:
	हाल F_WRLCK:
		अगर (ffl->start > OFFSET_MAX || ffl->end > OFFSET_MAX ||
		    ffl->end < ffl->start)
			वापस -EIO;

		fl->fl_start = ffl->start;
		fl->fl_end = ffl->end;

		/*
		 * Convert pid पूर्णांकo init's pid namespace.  The locks API will
		 * translate it पूर्णांकo the caller's pid namespace.
		 */
		rcu_पढ़ो_lock();
		fl->fl_pid = pid_nr_ns(find_pid_ns(ffl->pid, fc->pid_ns), &init_pid_ns);
		rcu_पढ़ो_unlock();
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण
	fl->fl_type = ffl->type;
	वापस 0;
पूर्ण

अटल व्योम fuse_lk_fill(काष्ठा fuse_args *args, काष्ठा file *file,
			 स्थिर काष्ठा file_lock *fl, पूर्णांक opcode, pid_t pid,
			 पूर्णांक flock, काष्ठा fuse_lk_in *inarg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_file *ff = file->निजी_data;

	स_रखो(inarg, 0, माप(*inarg));
	inarg->fh = ff->fh;
	inarg->owner = fuse_lock_owner_id(fc, fl->fl_owner);
	inarg->lk.start = fl->fl_start;
	inarg->lk.end = fl->fl_end;
	inarg->lk.type = fl->fl_type;
	inarg->lk.pid = pid;
	अगर (flock)
		inarg->lk_flags |= FUSE_LK_FLOCK;
	args->opcode = opcode;
	args->nodeid = get_node_id(inode);
	args->in_numargs = 1;
	args->in_args[0].size = माप(*inarg);
	args->in_args[0].value = inarg;
पूर्ण

अटल पूर्णांक fuse_getlk(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_lk_in inarg;
	काष्ठा fuse_lk_out outarg;
	पूर्णांक err;

	fuse_lk_fill(&args, file, fl, FUSE_GETLK, 0, 0, &inarg);
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (!err)
		err = convert_fuse_file_lock(fm->fc, &outarg.lk, fl);

	वापस err;
पूर्ण

अटल पूर्णांक fuse_setlk(काष्ठा file *file, काष्ठा file_lock *fl, पूर्णांक flock)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_lk_in inarg;
	पूर्णांक opcode = (fl->fl_flags & FL_SLEEP) ? FUSE_SETLKW : FUSE_SETLK;
	काष्ठा pid *pid = fl->fl_type != F_UNLCK ? task_tgid(current) : शून्य;
	pid_t pid_nr = pid_nr_ns(pid, fm->fc->pid_ns);
	पूर्णांक err;

	अगर (fl->fl_lmops && fl->fl_lmops->lm_grant) अणु
		/* NLM needs asynchronous locks, which we करोn't support yet */
		वापस -ENOLCK;
	पूर्ण

	/* Unlock on बंद is handled by the flush method */
	अगर ((fl->fl_flags & FL_CLOSE_POSIX) == FL_CLOSE_POSIX)
		वापस 0;

	fuse_lk_fill(&args, file, fl, opcode, pid_nr, flock, &inarg);
	err = fuse_simple_request(fm, &args);

	/* locking is restartable */
	अगर (err == -EINTR)
		err = -ERESTARTSYS;

	वापस err;
पूर्ण

अटल पूर्णांक fuse_file_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	पूर्णांक err;

	अगर (cmd == F_CANCELLK) अणु
		err = 0;
	पूर्ण अन्यथा अगर (cmd == F_GETLK) अणु
		अगर (fc->no_lock) अणु
			posix_test_lock(file, fl);
			err = 0;
		पूर्ण अन्यथा
			err = fuse_getlk(file, fl);
	पूर्ण अन्यथा अणु
		अगर (fc->no_lock)
			err = posix_lock_file(file, fl, शून्य);
		अन्यथा
			err = fuse_setlk(file, fl, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fuse_file_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	पूर्णांक err;

	अगर (fc->no_flock) अणु
		err = locks_lock_file_रुको(file, fl);
	पूर्ण अन्यथा अणु
		काष्ठा fuse_file *ff = file->निजी_data;

		/* emulate flock with POSIX locks */
		ff->flock = true;
		err = fuse_setlk(file, fl, 1);
	पूर्ण

	वापस err;
पूर्ण

अटल sector_t fuse_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_bmap_in inarg;
	काष्ठा fuse_bmap_out outarg;
	पूर्णांक err;

	अगर (!inode->i_sb->s_bdev || fm->fc->no_bmap)
		वापस 0;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.block = block;
	inarg.blocksize = inode->i_sb->s_blocksize;
	args.opcode = FUSE_BMAP;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS)
		fm->fc->no_bmap = 1;

	वापस err ? 0 : outarg.block;
पूर्ण

अटल loff_t fuse_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_file *ff = file->निजी_data;
	FUSE_ARGS(args);
	काष्ठा fuse_lseek_in inarg = अणु
		.fh = ff->fh,
		.offset = offset,
		.whence = whence
	पूर्ण;
	काष्ठा fuse_lseek_out outarg;
	पूर्णांक err;

	अगर (fm->fc->no_lseek)
		जाओ fallback;

	args.opcode = FUSE_LSEEK;
	args.nodeid = ff->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (err) अणु
		अगर (err == -ENOSYS) अणु
			fm->fc->no_lseek = 1;
			जाओ fallback;
		पूर्ण
		वापस err;
	पूर्ण

	वापस vfs_setpos(file, outarg.offset, inode->i_sb->s_maxbytes);

fallback:
	err = fuse_update_attributes(inode, file);
	अगर (!err)
		वापस generic_file_llseek(file, offset, whence);
	अन्यथा
		वापस err;
पूर्ण

अटल loff_t fuse_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	loff_t retval;
	काष्ठा inode *inode = file_inode(file);

	चयन (whence) अणु
	हाल शुरू_से:
	हाल प्रस्तुत_से:
		 /* No i_mutex protection necessary क्रम प्रस्तुत_से and शुरू_से */
		retval = generic_file_llseek(file, offset, whence);
		अवरोध;
	हाल अंत_से:
		inode_lock(inode);
		retval = fuse_update_attributes(inode, file);
		अगर (!retval)
			retval = generic_file_llseek(file, offset, whence);
		inode_unlock(inode);
		अवरोध;
	हाल SEEK_HOLE:
	हाल SEEK_DATA:
		inode_lock(inode);
		retval = fuse_lseek(file, offset, whence);
		inode_unlock(inode);
		अवरोध;
	शेष:
		retval = -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण

/*
 * All files which have been polled are linked to RB tree
 * fuse_conn->polled_files which is indexed by kh.  Walk the tree and
 * find the matching one.
 */
अटल काष्ठा rb_node **fuse_find_polled_node(काष्ठा fuse_conn *fc, u64 kh,
					      काष्ठा rb_node **parent_out)
अणु
	काष्ठा rb_node **link = &fc->polled_files.rb_node;
	काष्ठा rb_node *last = शून्य;

	जबतक (*link) अणु
		काष्ठा fuse_file *ff;

		last = *link;
		ff = rb_entry(last, काष्ठा fuse_file, polled_node);

		अगर (kh < ff->kh)
			link = &last->rb_left;
		अन्यथा अगर (kh > ff->kh)
			link = &last->rb_right;
		अन्यथा
			वापस link;
	पूर्ण

	अगर (parent_out)
		*parent_out = last;
	वापस link;
पूर्ण

/*
 * The file is about to be polled.  Make sure it's on the polled_files
 * RB tree.  Note that files once added to the polled_files tree are
 * not हटाओd beक्रमe the file is released.  This is because a file
 * polled once is likely to be polled again.
 */
अटल व्योम fuse_रेजिस्टर_polled_file(काष्ठा fuse_conn *fc,
				      काष्ठा fuse_file *ff)
अणु
	spin_lock(&fc->lock);
	अगर (RB_EMPTY_NODE(&ff->polled_node)) अणु
		काष्ठा rb_node **link, *parent;

		link = fuse_find_polled_node(fc, ff->kh, &parent);
		BUG_ON(*link);
		rb_link_node(&ff->polled_node, parent, link);
		rb_insert_color(&ff->polled_node, &fc->polled_files);
	पूर्ण
	spin_unlock(&fc->lock);
पूर्ण

__poll_t fuse_file_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;
	काष्ठा fuse_poll_in inarg = अणु .fh = ff->fh, .kh = ff->kh पूर्ण;
	काष्ठा fuse_poll_out outarg;
	FUSE_ARGS(args);
	पूर्णांक err;

	अगर (fm->fc->no_poll)
		वापस DEFAULT_POLLMASK;

	poll_रुको(file, &ff->poll_रुको, रुको);
	inarg.events = mangle_poll(poll_requested_events(रुको));

	/*
	 * Ask क्रम notअगरication अगरf there's someone रुकोing क्रम it.
	 * The client may ignore the flag and always notअगरy.
	 */
	अगर (रुकोqueue_active(&ff->poll_रुको)) अणु
		inarg.flags |= FUSE_POLL_SCHEDULE_NOTIFY;
		fuse_रेजिस्टर_polled_file(fm->fc, ff);
	पूर्ण

	args.opcode = FUSE_POLL;
	args.nodeid = ff->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);

	अगर (!err)
		वापस demangle_poll(outarg.revents);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_poll = 1;
		वापस DEFAULT_POLLMASK;
	पूर्ण
	वापस EPOLLERR;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_file_poll);

/*
 * This is called from fuse_handle_notअगरy() on FUSE_NOTIFY_POLL and
 * wakes up the poll रुकोers.
 */
पूर्णांक fuse_notअगरy_poll_wakeup(काष्ठा fuse_conn *fc,
			    काष्ठा fuse_notअगरy_poll_wakeup_out *outarg)
अणु
	u64 kh = outarg->kh;
	काष्ठा rb_node **link;

	spin_lock(&fc->lock);

	link = fuse_find_polled_node(fc, kh, शून्य);
	अगर (*link) अणु
		काष्ठा fuse_file *ff;

		ff = rb_entry(*link, काष्ठा fuse_file, polled_node);
		wake_up_पूर्णांकerruptible_sync(&ff->poll_रुको);
	पूर्ण

	spin_unlock(&fc->lock);
	वापस 0;
पूर्ण

अटल व्योम fuse_करो_truncate(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा iattr attr;

	attr.ia_valid = ATTR_SIZE;
	attr.ia_size = i_size_पढ़ो(inode);

	attr.ia_file = file;
	attr.ia_valid |= ATTR_खाता;

	fuse_करो_setattr(file_dentry(file), &attr, file);
पूर्ण

अटल अंतरभूत loff_t fuse_round_up(काष्ठा fuse_conn *fc, loff_t off)
अणु
	वापस round_up(off, fc->max_pages << PAGE_SHIFT);
पूर्ण

अटल sमाप_प्रकार
fuse_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);
	sमाप_प्रकार ret = 0;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fuse_file *ff = file->निजी_data;
	loff_t pos = 0;
	काष्ठा inode *inode;
	loff_t i_size;
	माप_प्रकार count = iov_iter_count(iter), लघुened = 0;
	loff_t offset = iocb->ki_pos;
	काष्ठा fuse_io_priv *io;

	pos = offset;
	inode = file->f_mapping->host;
	i_size = i_size_पढ़ो(inode);

	अगर ((iov_iter_rw(iter) == READ) && (offset >= i_size))
		वापस 0;

	io = kदो_स्मृति(माप(काष्ठा fuse_io_priv), GFP_KERNEL);
	अगर (!io)
		वापस -ENOMEM;
	spin_lock_init(&io->lock);
	kref_init(&io->refcnt);
	io->reqs = 1;
	io->bytes = -1;
	io->size = 0;
	io->offset = offset;
	io->ग_लिखो = (iov_iter_rw(iter) == WRITE);
	io->err = 0;
	/*
	 * By शेष, we want to optimize all I/Os with async request
	 * submission to the client fileप्रणाली अगर supported.
	 */
	io->async = ff->fm->fc->async_dio;
	io->iocb = iocb;
	io->blocking = is_sync_kiocb(iocb);

	/* optimization क्रम लघु पढ़ो */
	अगर (io->async && !io->ग_लिखो && offset + count > i_size) अणु
		iov_iter_truncate(iter, fuse_round_up(ff->fm->fc, i_size - offset));
		लघुened = count - iov_iter_count(iter);
		count -= लघुened;
	पूर्ण

	/*
	 * We cannot asynchronously extend the size of a file.
	 * In such हाल the aio will behave exactly like sync io.
	 */
	अगर ((offset + count > i_size) && io->ग_लिखो)
		io->blocking = true;

	अगर (io->async && io->blocking) अणु
		/*
		 * Additional reference to keep io around after
		 * calling fuse_aio_complete()
		 */
		kref_get(&io->refcnt);
		io->करोne = &रुको;
	पूर्ण

	अगर (iov_iter_rw(iter) == WRITE) अणु
		ret = fuse_direct_io(io, iter, &pos, FUSE_DIO_WRITE);
		fuse_invalidate_attr(inode);
	पूर्ण अन्यथा अणु
		ret = __fuse_direct_पढ़ो(io, iter, &pos);
	पूर्ण
	iov_iter_reexpand(iter, iov_iter_count(iter) + लघुened);

	अगर (io->async) अणु
		bool blocking = io->blocking;

		fuse_aio_complete(io, ret < 0 ? ret : 0, -1);

		/* we have a non-extending, async request, so वापस */
		अगर (!blocking)
			वापस -EIOCBQUEUED;

		रुको_क्रम_completion(&रुको);
		ret = fuse_get_res_by_io(io);
	पूर्ण

	kref_put(&io->refcnt, fuse_io_release);

	अगर (iov_iter_rw(iter) == WRITE) अणु
		अगर (ret > 0)
			fuse_ग_लिखो_update_size(inode, pos);
		अन्यथा अगर (ret < 0 && offset + count > i_size)
			fuse_करो_truncate(file);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fuse_ग_लिखोback_range(काष्ठा inode *inode, loff_t start, loff_t end)
अणु
	पूर्णांक err = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, start, end);

	अगर (!err)
		fuse_sync_ग_लिखोs(inode);

	वापस err;
पूर्ण

अटल दीर्घ fuse_file_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
				loff_t length)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	काष्ठा fuse_mount *fm = ff->fm;
	FUSE_ARGS(args);
	काष्ठा fuse_fallocate_in inarg = अणु
		.fh = ff->fh,
		.offset = offset,
		.length = length,
		.mode = mode
	पूर्ण;
	पूर्णांक err;
	bool lock_inode = !(mode & FALLOC_FL_KEEP_SIZE) ||
			   (mode & FALLOC_FL_PUNCH_HOLE);

	bool block_faults = FUSE_IS_DAX(inode) && lock_inode;

	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		वापस -EOPNOTSUPP;

	अगर (fm->fc->no_fallocate)
		वापस -EOPNOTSUPP;

	अगर (lock_inode) अणु
		inode_lock(inode);
		अगर (block_faults) अणु
			करोwn_ग_लिखो(&fi->i_mmap_sem);
			err = fuse_dax_अवरोध_layouts(inode, 0, 0);
			अगर (err)
				जाओ out;
		पूर्ण

		अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
			loff_t endbyte = offset + length - 1;

			err = fuse_ग_लिखोback_range(inode, offset, endbyte);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    offset + length > i_size_पढ़ो(inode)) अणु
		err = inode_newsize_ok(inode, offset + length);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE))
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	args.opcode = FUSE_FALLOCATE;
	args.nodeid = ff->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_fallocate = 1;
		err = -EOPNOTSUPP;
	पूर्ण
	अगर (err)
		जाओ out;

	/* we could have extended the file */
	अगर (!(mode & FALLOC_FL_KEEP_SIZE)) अणु
		bool changed = fuse_ग_लिखो_update_size(inode, offset + length);

		अगर (changed && fm->fc->ग_लिखोback_cache)
			file_update_समय(file);
	पूर्ण

	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		truncate_pagecache_range(inode, offset, offset + length - 1);

	fuse_invalidate_attr(inode);

out:
	अगर (!(mode & FALLOC_FL_KEEP_SIZE))
		clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	अगर (block_faults)
		up_ग_लिखो(&fi->i_mmap_sem);

	अगर (lock_inode)
		inode_unlock(inode);

	वापस err;
पूर्ण

अटल sमाप_प्रकार __fuse_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				      काष्ठा file *file_out, loff_t pos_out,
				      माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fuse_file *ff_in = file_in->निजी_data;
	काष्ठा fuse_file *ff_out = file_out->निजी_data;
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);
	काष्ठा fuse_inode *fi_out = get_fuse_inode(inode_out);
	काष्ठा fuse_mount *fm = ff_in->fm;
	काष्ठा fuse_conn *fc = fm->fc;
	FUSE_ARGS(args);
	काष्ठा fuse_copy_file_range_in inarg = अणु
		.fh_in = ff_in->fh,
		.off_in = pos_in,
		.nodeid_out = ff_out->nodeid,
		.fh_out = ff_out->fh,
		.off_out = pos_out,
		.len = len,
		.flags = flags
	पूर्ण;
	काष्ठा fuse_ग_लिखो_out outarg;
	sमाप_प्रकार err;
	/* mark unstable when ग_लिखो-back is not used, and file_out माला_लो
	 * extended */
	bool is_unstable = (!fc->ग_लिखोback_cache) &&
			   ((pos_out + len) > inode_out->i_size);

	अगर (fc->no_copy_file_range)
		वापस -EOPNOTSUPP;

	अगर (file_inode(file_in)->i_sb != file_inode(file_out)->i_sb)
		वापस -EXDEV;

	inode_lock(inode_in);
	err = fuse_ग_लिखोback_range(inode_in, pos_in, pos_in + len - 1);
	inode_unlock(inode_in);
	अगर (err)
		वापस err;

	inode_lock(inode_out);

	err = file_modअगरied(file_out);
	अगर (err)
		जाओ out;

	/*
	 * Write out dirty pages in the destination file beक्रमe sending the COPY
	 * request to userspace.  After the request is completed, truncate off
	 * pages (including partial ones) from the cache that have been copied,
	 * since these contain stale data at that poपूर्णांक.
	 *
	 * This should be mostly correct, but अगर the COPY ग_लिखोs to partial
	 * pages (at the start or end) and the parts not covered by the COPY are
	 * written through a memory map after calling fuse_ग_लिखोback_range(),
	 * then these partial page modअगरications will be lost on truncation.
	 *
	 * It is unlikely that someone would rely on such mixed style
	 * modअगरications.  Yet this करोes give less guarantees than अगर the
	 * copying was perक्रमmed with ग_लिखो(2).
	 *
	 * To fix this a i_mmap_sem style lock could be used to prevent new
	 * faults जबतक the copy is ongoing.
	 */
	err = fuse_ग_लिखोback_range(inode_out, pos_out, pos_out + len - 1);
	अगर (err)
		जाओ out;

	अगर (is_unstable)
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi_out->state);

	args.opcode = FUSE_COPY_खाता_RANGE;
	args.nodeid = ff_in->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fc->no_copy_file_range = 1;
		err = -EOPNOTSUPP;
	पूर्ण
	अगर (err)
		जाओ out;

	truncate_inode_pages_range(inode_out->i_mapping,
				   ALIGN_DOWN(pos_out, PAGE_SIZE),
				   ALIGN(pos_out + outarg.size, PAGE_SIZE) - 1);

	अगर (fc->ग_लिखोback_cache) अणु
		fuse_ग_लिखो_update_size(inode_out, pos_out + outarg.size);
		file_update_समय(file_out);
	पूर्ण

	fuse_invalidate_attr(inode_out);

	err = outarg.size;
out:
	अगर (is_unstable)
		clear_bit(FUSE_I_SIZE_UNSTABLE, &fi_out->state);

	inode_unlock(inode_out);
	file_accessed(file_in);

	वापस err;
पूर्ण

अटल sमाप_प्रकार fuse_copy_file_range(काष्ठा file *src_file, loff_t src_off,
				    काष्ठा file *dst_file, loff_t dst_off,
				    माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार ret;

	ret = __fuse_copy_file_range(src_file, src_off, dst_file, dst_off,
				     len, flags);

	अगर (ret == -EOPNOTSUPP || ret == -EXDEV)
		ret = generic_copy_file_range(src_file, src_off, dst_file,
					      dst_off, len, flags);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fuse_file_operations = अणु
	.llseek		= fuse_file_llseek,
	.पढ़ो_iter	= fuse_file_पढ़ो_iter,
	.ग_लिखो_iter	= fuse_file_ग_लिखो_iter,
	.mmap		= fuse_file_mmap,
	.खोलो		= fuse_खोलो,
	.flush		= fuse_flush,
	.release	= fuse_release,
	.fsync		= fuse_fsync,
	.lock		= fuse_file_lock,
	.get_unmapped_area = thp_get_unmapped_area,
	.flock		= fuse_file_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.unlocked_ioctl	= fuse_file_ioctl,
	.compat_ioctl	= fuse_file_compat_ioctl,
	.poll		= fuse_file_poll,
	.fallocate	= fuse_file_fallocate,
	.copy_file_range = fuse_copy_file_range,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations fuse_file_aops  = अणु
	.पढ़ोpage	= fuse_पढ़ोpage,
	.पढ़ोahead	= fuse_पढ़ोahead,
	.ग_लिखोpage	= fuse_ग_लिखोpage,
	.ग_लिखोpages	= fuse_ग_लिखोpages,
	.launder_page	= fuse_launder_page,
	.set_page_dirty	= __set_page_dirty_nobuffers,
	.bmap		= fuse_bmap,
	.direct_IO	= fuse_direct_IO,
	.ग_लिखो_begin	= fuse_ग_लिखो_begin,
	.ग_लिखो_end	= fuse_ग_लिखो_end,
पूर्ण;

व्योम fuse_init_file_inode(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	inode->i_fop = &fuse_file_operations;
	inode->i_data.a_ops = &fuse_file_aops;

	INIT_LIST_HEAD(&fi->ग_लिखो_files);
	INIT_LIST_HEAD(&fi->queued_ग_लिखोs);
	fi->ग_लिखोctr = 0;
	init_रुकोqueue_head(&fi->page_रुकोq);
	fi->ग_लिखोpages = RB_ROOT;

	अगर (IS_ENABLED(CONFIG_FUSE_DAX))
		fuse_dax_inode_init(inode);
पूर्ण
