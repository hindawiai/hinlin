<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Red Hat, Inc.
 */

#समावेश <linux/cred.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/xattr.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/splice.h>
#समावेश <linux/security.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश "overlayfs.h"

काष्ठा ovl_aio_req अणु
	काष्ठा kiocb iocb;
	काष्ठा kiocb *orig_iocb;
	काष्ठा fd fd;
पूर्ण;

अटल काष्ठा kmem_cache *ovl_aio_request_cachep;

अटल अक्षर ovl_whatisit(काष्ठा inode *inode, काष्ठा inode *realinode)
अणु
	अगर (realinode != ovl_inode_upper(inode))
		वापस 'l';
	अगर (ovl_has_upperdata(inode))
		वापस 'u';
	अन्यथा
		वापस 'm';
पूर्ण

/* No aसमय modअगरicaton nor notअगरy on underlying */
#घोषणा OVL_OPEN_FLAGS (O_NOATIME | FMODE_NONOTIFY)

अटल काष्ठा file *ovl_खोलो_realfile(स्थिर काष्ठा file *file,
				      काष्ठा inode *realinode)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा file *realfile;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक flags = file->f_flags | OVL_OPEN_FLAGS;
	पूर्णांक acc_mode = ACC_MODE(flags);
	पूर्णांक err;

	अगर (flags & O_APPEND)
		acc_mode |= MAY_APPEND;

	old_cred = ovl_override_creds(inode->i_sb);
	err = inode_permission(&init_user_ns, realinode, MAY_OPEN | acc_mode);
	अगर (err) अणु
		realfile = ERR_PTR(err);
	पूर्ण अन्यथा अणु
		अगर (!inode_owner_or_capable(&init_user_ns, realinode))
			flags &= ~O_NOATIME;

		realfile = खोलो_with_fake_path(&file->f_path, flags, realinode,
					       current_cred());
	पूर्ण
	revert_creds(old_cred);

	pr_debug("open(%p[%pD2/%c], 0%o) -> (%p, 0%o)\n",
		 file, file, ovl_whatisit(inode, realinode), file->f_flags,
		 realfile, IS_ERR(realfile) ? 0 : realfile->f_flags);

	वापस realfile;
पूर्ण

#घोषणा OVL_SETFL_MASK (O_APPEND | O_NONBLOCK | O_NDELAY | O_सूचीECT)

अटल पूर्णांक ovl_change_flags(काष्ठा file *file, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक err;

	flags &= OVL_SETFL_MASK;

	अगर (((flags ^ file->f_flags) & O_APPEND) && IS_APPEND(inode))
		वापस -EPERM;

	अगर (flags & O_सूचीECT) अणु
		अगर (!file->f_mapping->a_ops ||
		    !file->f_mapping->a_ops->direct_IO)
			वापस -EINVAL;
	पूर्ण

	अगर (file->f_op->check_flags) अणु
		err = file->f_op->check_flags(flags);
		अगर (err)
			वापस err;
	पूर्ण

	spin_lock(&file->f_lock);
	file->f_flags = (file->f_flags & ~OVL_SETFL_MASK) | flags;
	spin_unlock(&file->f_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_real_fdget_meta(स्थिर काष्ठा file *file, काष्ठा fd *real,
			       bool allow_meta)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा inode *realinode;

	real->flags = 0;
	real->file = file->निजी_data;

	अगर (allow_meta)
		realinode = ovl_inode_real(inode);
	अन्यथा
		realinode = ovl_inode_realdata(inode);

	/* Has it been copied up since we'd खोलोed it? */
	अगर (unlikely(file_inode(real->file) != realinode)) अणु
		real->flags = FDPUT_FPUT;
		real->file = ovl_खोलो_realfile(file, realinode);

		वापस PTR_ERR_OR_ZERO(real->file);
	पूर्ण

	/* Did the flags change since खोलो? */
	अगर (unlikely((file->f_flags ^ real->file->f_flags) & ~OVL_OPEN_FLAGS))
		वापस ovl_change_flags(real->file, file->f_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_real_fdget(स्थिर काष्ठा file *file, काष्ठा fd *real)
अणु
	अगर (d_is_dir(file_dentry(file))) अणु
		real->flags = 0;
		real->file = ovl_dir_real_file(file, false);

		वापस PTR_ERR_OR_ZERO(real->file);
	पूर्ण

	वापस ovl_real_fdget_meta(file, real, false);
पूर्ण

अटल पूर्णांक ovl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा file *realfile;
	पूर्णांक err;

	err = ovl_maybe_copy_up(file_dentry(file), file->f_flags);
	अगर (err)
		वापस err;

	/* No दीर्घer need these flags, so करोn't pass them on to underlying fs */
	file->f_flags &= ~(O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC);

	realfile = ovl_खोलो_realfile(file, ovl_inode_realdata(inode));
	अगर (IS_ERR(realfile))
		वापस PTR_ERR(realfile);

	file->निजी_data = realfile;

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	fput(file->निजी_data);

	वापस 0;
पूर्ण

अटल loff_t ovl_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	loff_t ret;

	/*
	 * The two special हालs below करो not need to involve real fs,
	 * so we can optimizing concurrent callers.
	 */
	अगर (offset == 0) अणु
		अगर (whence == प्रस्तुत_से)
			वापस file->f_pos;

		अगर (whence == शुरू_से)
			वापस vfs_setpos(file, 0, 0);
	पूर्ण

	ret = ovl_real_fdget(file, &real);
	अगर (ret)
		वापस ret;

	/*
	 * Overlay file f_pos is the master copy that is preserved
	 * through copy up and modअगरied on पढ़ो/ग_लिखो, but only real
	 * fs knows how to SEEK_HOLE/SEEK_DATA and real fs may impose
	 * limitations that are more strict than ->s_maxbytes क्रम specअगरic
	 * files, so we use the real file to perक्रमm seeks.
	 */
	ovl_inode_lock(inode);
	real.file->f_pos = file->f_pos;

	old_cred = ovl_override_creds(inode->i_sb);
	ret = vfs_llseek(real.file, offset, whence);
	revert_creds(old_cred);

	file->f_pos = real.file->f_pos;
	ovl_inode_unlock(inode);

	fdput(real);

	वापस ret;
पूर्ण

अटल व्योम ovl_file_accessed(काष्ठा file *file)
अणु
	काष्ठा inode *inode, *upperinode;

	अगर (file->f_flags & O_NOATIME)
		वापस;

	inode = file_inode(file);
	upperinode = ovl_inode_upper(inode);

	अगर (!upperinode)
		वापस;

	अगर ((!बारpec64_equal(&inode->i_mसमय, &upperinode->i_mसमय) ||
	     !बारpec64_equal(&inode->i_स_समय, &upperinode->i_स_समय))) अणु
		inode->i_mसमय = upperinode->i_mसमय;
		inode->i_स_समय = upperinode->i_स_समय;
	पूर्ण

	touch_aसमय(&file->f_path);
पूर्ण

अटल rwf_t ovl_iocb_to_rwf(पूर्णांक अगरl)
अणु
	rwf_t flags = 0;

	अगर (अगरl & IOCB_NOWAIT)
		flags |= RWF_NOWAIT;
	अगर (अगरl & IOCB_HIPRI)
		flags |= RWF_HIPRI;
	अगर (अगरl & IOCB_DSYNC)
		flags |= RWF_DSYNC;
	अगर (अगरl & IOCB_SYNC)
		flags |= RWF_SYNC;

	वापस flags;
पूर्ण

अटल व्योम ovl_aio_cleanup_handler(काष्ठा ovl_aio_req *aio_req)
अणु
	काष्ठा kiocb *iocb = &aio_req->iocb;
	काष्ठा kiocb *orig_iocb = aio_req->orig_iocb;

	अगर (iocb->ki_flags & IOCB_WRITE) अणु
		काष्ठा inode *inode = file_inode(orig_iocb->ki_filp);

		/* Actually acquired in ovl_ग_लिखो_iter() */
		__sb_ग_लिखोrs_acquired(file_inode(iocb->ki_filp)->i_sb,
				      SB_FREEZE_WRITE);
		file_end_ग_लिखो(iocb->ki_filp);
		ovl_copyattr(ovl_inode_real(inode), inode);
	पूर्ण

	orig_iocb->ki_pos = iocb->ki_pos;
	fdput(aio_req->fd);
	kmem_cache_मुक्त(ovl_aio_request_cachep, aio_req);
पूर्ण

अटल व्योम ovl_aio_rw_complete(काष्ठा kiocb *iocb, दीर्घ res, दीर्घ res2)
अणु
	काष्ठा ovl_aio_req *aio_req = container_of(iocb,
						   काष्ठा ovl_aio_req, iocb);
	काष्ठा kiocb *orig_iocb = aio_req->orig_iocb;

	ovl_aio_cleanup_handler(aio_req);
	orig_iocb->ki_complete(orig_iocb, res, res2);
पूर्ण

अटल sमाप_प्रकार ovl_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	sमाप_प्रकार ret;

	अगर (!iov_iter_count(iter))
		वापस 0;

	ret = ovl_real_fdget(file, &real);
	अगर (ret)
		वापस ret;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	अगर (is_sync_kiocb(iocb)) अणु
		ret = vfs_iter_पढ़ो(real.file, iter, &iocb->ki_pos,
				    ovl_iocb_to_rwf(iocb->ki_flags));
	पूर्ण अन्यथा अणु
		काष्ठा ovl_aio_req *aio_req;

		ret = -ENOMEM;
		aio_req = kmem_cache_zalloc(ovl_aio_request_cachep, GFP_KERNEL);
		अगर (!aio_req)
			जाओ out;

		aio_req->fd = real;
		real.flags = 0;
		aio_req->orig_iocb = iocb;
		kiocb_clone(&aio_req->iocb, iocb, real.file);
		aio_req->iocb.ki_complete = ovl_aio_rw_complete;
		ret = vfs_iocb_iter_पढ़ो(real.file, &aio_req->iocb, iter);
		अगर (ret != -EIOCBQUEUED)
			ovl_aio_cleanup_handler(aio_req);
	पूर्ण
out:
	revert_creds(old_cred);
	ovl_file_accessed(file);

	fdput(real);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ovl_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	sमाप_प्रकार ret;
	पूर्णांक अगरl = iocb->ki_flags;

	अगर (!iov_iter_count(iter))
		वापस 0;

	inode_lock(inode);
	/* Update mode */
	ovl_copyattr(ovl_inode_real(inode), inode);
	ret = file_हटाओ_privs(file);
	अगर (ret)
		जाओ out_unlock;

	ret = ovl_real_fdget(file, &real);
	अगर (ret)
		जाओ out_unlock;

	अगर (!ovl_should_sync(OVL_FS(inode->i_sb)))
		अगरl &= ~(IOCB_DSYNC | IOCB_SYNC);

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	अगर (is_sync_kiocb(iocb)) अणु
		file_start_ग_लिखो(real.file);
		ret = vfs_iter_ग_लिखो(real.file, iter, &iocb->ki_pos,
				     ovl_iocb_to_rwf(अगरl));
		file_end_ग_लिखो(real.file);
		/* Update size */
		ovl_copyattr(ovl_inode_real(inode), inode);
	पूर्ण अन्यथा अणु
		काष्ठा ovl_aio_req *aio_req;

		ret = -ENOMEM;
		aio_req = kmem_cache_zalloc(ovl_aio_request_cachep, GFP_KERNEL);
		अगर (!aio_req)
			जाओ out;

		file_start_ग_लिखो(real.file);
		/* Pacअगरy lockdep, same trick as करोne in aio_ग_लिखो() */
		__sb_ग_लिखोrs_release(file_inode(real.file)->i_sb,
				     SB_FREEZE_WRITE);
		aio_req->fd = real;
		real.flags = 0;
		aio_req->orig_iocb = iocb;
		kiocb_clone(&aio_req->iocb, iocb, real.file);
		aio_req->iocb.ki_flags = अगरl;
		aio_req->iocb.ki_complete = ovl_aio_rw_complete;
		ret = vfs_iocb_iter_ग_लिखो(real.file, &aio_req->iocb, iter);
		अगर (ret != -EIOCBQUEUED)
			ovl_aio_cleanup_handler(aio_req);
	पूर्ण
out:
	revert_creds(old_cred);
	fdput(real);

out_unlock:
	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल पूर्णांक ovl_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक ret;

	ret = ovl_sync_status(OVL_FS(file_inode(file)->i_sb));
	अगर (ret <= 0)
		वापस ret;

	ret = ovl_real_fdget_meta(file, &real, !datasync);
	अगर (ret)
		वापस ret;

	/* Don't sync lower file क्रम fear of receiving EROFS error */
	अगर (file_inode(real.file) == ovl_inode_upper(file_inode(file))) अणु
		old_cred = ovl_override_creds(file_inode(file)->i_sb);
		ret = vfs_fsync_range(real.file, start, end, datasync);
		revert_creds(old_cred);
	पूर्ण

	fdput(real);

	वापस ret;
पूर्ण

अटल पूर्णांक ovl_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *realfile = file->निजी_data;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक ret;

	अगर (!realfile->f_op->mmap)
		वापस -ENODEV;

	अगर (WARN_ON(file != vma->vm_file))
		वापस -EIO;

	vma_set_file(vma, realfile);

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	ret = call_mmap(vma->vm_file, vma);
	revert_creds(old_cred);
	ovl_file_accessed(file);

	वापस ret;
पूर्ण

अटल दीर्घ ovl_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक ret;

	ret = ovl_real_fdget(file, &real);
	अगर (ret)
		वापस ret;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	ret = vfs_fallocate(real.file, mode, offset, len);
	revert_creds(old_cred);

	/* Update size */
	ovl_copyattr(ovl_inode_real(inode), inode);

	fdput(real);

	वापस ret;
पूर्ण

अटल पूर्णांक ovl_fadvise(काष्ठा file *file, loff_t offset, loff_t len, पूर्णांक advice)
अणु
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक ret;

	ret = ovl_real_fdget(file, &real);
	अगर (ret)
		वापस ret;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	ret = vfs_fadvise(real.file, offset, len, advice);
	revert_creds(old_cred);

	fdput(real);

	वापस ret;
पूर्ण

क्रमागत ovl_copyop अणु
	OVL_COPY,
	OVL_CLONE,
	OVL_DEDUPE,
पूर्ण;

अटल loff_t ovl_copyfile(काष्ठा file *file_in, loff_t pos_in,
			    काष्ठा file *file_out, loff_t pos_out,
			    loff_t len, अचिन्हित पूर्णांक flags, क्रमागत ovl_copyop op)
अणु
	काष्ठा inode *inode_out = file_inode(file_out);
	काष्ठा fd real_in, real_out;
	स्थिर काष्ठा cred *old_cred;
	loff_t ret;

	ret = ovl_real_fdget(file_out, &real_out);
	अगर (ret)
		वापस ret;

	ret = ovl_real_fdget(file_in, &real_in);
	अगर (ret) अणु
		fdput(real_out);
		वापस ret;
	पूर्ण

	old_cred = ovl_override_creds(file_inode(file_out)->i_sb);
	चयन (op) अणु
	हाल OVL_COPY:
		ret = vfs_copy_file_range(real_in.file, pos_in,
					  real_out.file, pos_out, len, flags);
		अवरोध;

	हाल OVL_CLONE:
		ret = vfs_clone_file_range(real_in.file, pos_in,
					   real_out.file, pos_out, len, flags);
		अवरोध;

	हाल OVL_DEDUPE:
		ret = vfs_dedupe_file_range_one(real_in.file, pos_in,
						real_out.file, pos_out, len,
						flags);
		अवरोध;
	पूर्ण
	revert_creds(old_cred);

	/* Update size */
	ovl_copyattr(ovl_inode_real(inode_out), inode_out);

	fdput(real_in);
	fdput(real_out);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ovl_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				   काष्ठा file *file_out, loff_t pos_out,
				   माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	वापस ovl_copyfile(file_in, pos_in, file_out, pos_out, len, flags,
			    OVL_COPY);
पूर्ण

अटल loff_t ovl_remap_file_range(काष्ठा file *file_in, loff_t pos_in,
				   काष्ठा file *file_out, loff_t pos_out,
				   loff_t len, अचिन्हित पूर्णांक remap_flags)
अणु
	क्रमागत ovl_copyop op;

	अगर (remap_flags & ~(REMAP_खाता_DEDUP | REMAP_खाता_ADVISORY))
		वापस -EINVAL;

	अगर (remap_flags & REMAP_खाता_DEDUP)
		op = OVL_DEDUPE;
	अन्यथा
		op = OVL_CLONE;

	/*
	 * Don't copy up because of a dedupe request, this wouldn't make sense
	 * most of the समय (data would be duplicated instead of deduplicated).
	 */
	अगर (op == OVL_DEDUPE &&
	    (!ovl_inode_upper(file_inode(file_in)) ||
	     !ovl_inode_upper(file_inode(file_out))))
		वापस -EPERM;

	वापस ovl_copyfile(file_in, pos_in, file_out, pos_out, len,
			    remap_flags, op);
पूर्ण

अटल पूर्णांक ovl_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा fd real;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	err = ovl_real_fdget(file, &real);
	अगर (err)
		वापस err;

	अगर (real.file->f_op->flush) अणु
		old_cred = ovl_override_creds(file_inode(file)->i_sb);
		err = real.file->f_op->flush(real.file, id);
		revert_creds(old_cred);
	पूर्ण
	fdput(real);

	वापस err;
पूर्ण

स्थिर काष्ठा file_operations ovl_file_operations = अणु
	.खोलो		= ovl_खोलो,
	.release	= ovl_release,
	.llseek		= ovl_llseek,
	.पढ़ो_iter	= ovl_पढ़ो_iter,
	.ग_लिखो_iter	= ovl_ग_लिखो_iter,
	.fsync		= ovl_fsync,
	.mmap		= ovl_mmap,
	.fallocate	= ovl_fallocate,
	.fadvise	= ovl_fadvise,
	.flush		= ovl_flush,
	.splice_पढ़ो    = generic_file_splice_पढ़ो,
	.splice_ग_लिखो   = iter_file_splice_ग_लिखो,

	.copy_file_range	= ovl_copy_file_range,
	.remap_file_range	= ovl_remap_file_range,
पूर्ण;

पूर्णांक __init ovl_aio_request_cache_init(व्योम)
अणु
	ovl_aio_request_cachep = kmem_cache_create("ovl_aio_req",
						   माप(काष्ठा ovl_aio_req),
						   0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ovl_aio_request_cachep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ovl_aio_request_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(ovl_aio_request_cachep);
पूर्ण
