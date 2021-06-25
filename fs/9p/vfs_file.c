<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_file.c
 *
 * This file contians vfs file ops क्रम 9P2000.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/inet.h>
#समावेश <linux/list.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/utsname.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/idr.h>
#समावेश <linux/uपन.स>
#समावेश <linux/slab.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"
#समावेश "cache.h"

अटल स्थिर काष्ठा vm_operations_काष्ठा v9fs_file_vm_ops;
अटल स्थिर काष्ठा vm_operations_काष्ठा v9fs_mmap_file_vm_ops;

/**
 * v9fs_file_खोलो - खोलो a file (or directory)
 * @inode: inode to be खोलोed
 * @file: file being खोलोed
 *
 */

पूर्णांक v9fs_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा v9fs_inode *v9inode;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid, *ग_लिखोback_fid;
	पूर्णांक omode;

	p9_debug(P9_DEBUG_VFS, "inode: %p file: %p\n", inode, file);
	v9inode = V9FS_I(inode);
	v9ses = v9fs_inode2v9ses(inode);
	अगर (v9fs_proto_करोtl(v9ses))
		omode = v9fs_खोलो_to_करोtl_flags(file->f_flags);
	अन्यथा
		omode = v9fs_uflags2omode(file->f_flags,
					v9fs_proto_करोtu(v9ses));
	fid = file->निजी_data;
	अगर (!fid) अणु
		fid = v9fs_fid_clone(file_dentry(file));
		अगर (IS_ERR(fid))
			वापस PTR_ERR(fid);

		err = p9_client_खोलो(fid, omode);
		अगर (err < 0) अणु
			p9_client_clunk(fid);
			वापस err;
		पूर्ण
		अगर ((file->f_flags & O_APPEND) &&
			(!v9fs_proto_करोtu(v9ses) && !v9fs_proto_करोtl(v9ses)))
			generic_file_llseek(file, 0, अंत_से);
	पूर्ण

	file->निजी_data = fid;
	mutex_lock(&v9inode->v_mutex);
	अगर ((v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) &&
	    !v9inode->ग_लिखोback_fid &&
	    ((file->f_flags & O_ACCMODE) != O_RDONLY)) अणु
		/*
		 * clone a fid and add it to ग_लिखोback_fid
		 * we करो it during खोलो समय instead of
		 * page dirty समय via ग_लिखो_begin/page_mkग_लिखो
		 * because we want ग_लिखो after unlink useहाल
		 * to work.
		 */
		ग_लिखोback_fid = v9fs_ग_लिखोback_fid(file_dentry(file));
		अगर (IS_ERR(ग_लिखोback_fid)) अणु
			err = PTR_ERR(ग_लिखोback_fid);
			mutex_unlock(&v9inode->v_mutex);
			जाओ out_error;
		पूर्ण
		v9inode->ग_लिखोback_fid = (व्योम *) ग_लिखोback_fid;
	पूर्ण
	mutex_unlock(&v9inode->v_mutex);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		v9fs_cache_inode_set_cookie(inode, file);
	v9fs_खोलो_fid_add(inode, fid);
	वापस 0;
out_error:
	p9_client_clunk(file->निजी_data);
	file->निजी_data = शून्य;
	वापस err;
पूर्ण

/**
 * v9fs_file_lock - lock a file (or directory)
 * @filp: file to be locked
 * @cmd: lock command
 * @fl: file lock काष्ठाure
 *
 * Bugs: this looks like a local only lock, we should extend पूर्णांकo 9P
 *       by using खोलो exclusive
 */

अटल पूर्णांक v9fs_file_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक res = 0;
	काष्ठा inode *inode = file_inode(filp);

	p9_debug(P9_DEBUG_VFS, "filp: %p lock: %p\n", filp, fl);

	/* No mandatory locks */
	अगर (__mandatory_lock(inode) && fl->fl_type != F_UNLCK)
		वापस -ENOLCK;

	अगर ((IS_SETLK(cmd) || IS_SETLKW(cmd)) && fl->fl_type != F_UNLCK) अणु
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
		invalidate_mapping_pages(&inode->i_data, 0, -1);
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक v9fs_file_करो_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा p9_flock flock;
	काष्ठा p9_fid *fid;
	uपूर्णांक8_t status = P9_LOCK_ERROR;
	पूर्णांक res = 0;
	अचिन्हित अक्षर fl_type;
	काष्ठा v9fs_session_info *v9ses;

	fid = filp->निजी_data;
	BUG_ON(fid == शून्य);

	अगर ((fl->fl_flags & FL_POSIX) != FL_POSIX)
		BUG();

	res = locks_lock_file_रुको(filp, fl);
	अगर (res < 0)
		जाओ out;

	/* convert posix lock to p9 tlock args */
	स_रखो(&flock, 0, माप(flock));
	/* map the lock type */
	चयन (fl->fl_type) अणु
	हाल F_RDLCK:
		flock.type = P9_LOCK_TYPE_RDLCK;
		अवरोध;
	हाल F_WRLCK:
		flock.type = P9_LOCK_TYPE_WRLCK;
		अवरोध;
	हाल F_UNLCK:
		flock.type = P9_LOCK_TYPE_UNLCK;
		अवरोध;
	पूर्ण
	flock.start = fl->fl_start;
	अगर (fl->fl_end == OFFSET_MAX)
		flock.length = 0;
	अन्यथा
		flock.length = fl->fl_end - fl->fl_start + 1;
	flock.proc_id = fl->fl_pid;
	flock.client_id = fid->clnt->name;
	अगर (IS_SETLKW(cmd))
		flock.flags = P9_LOCK_FLAGS_BLOCK;

	v9ses = v9fs_inode2v9ses(file_inode(filp));

	/*
	 * अगर its a blocked request and we get P9_LOCK_BLOCKED as the status
	 * क्रम lock request, keep on trying
	 */
	क्रम (;;) अणु
		res = p9_client_lock_करोtl(fid, &flock, &status);
		अगर (res < 0)
			जाओ out_unlock;

		अगर (status != P9_LOCK_BLOCKED)
			अवरोध;
		अगर (status == P9_LOCK_BLOCKED && !IS_SETLKW(cmd))
			अवरोध;
		अगर (schedule_समयout_पूर्णांकerruptible(v9ses->session_lock_समयout)
				!= 0)
			अवरोध;
		/*
		 * p9_client_lock_करोtl overग_लिखोs flock.client_id with the
		 * server message, मुक्त and reuse the client name
		 */
		अगर (flock.client_id != fid->clnt->name) अणु
			kमुक्त(flock.client_id);
			flock.client_id = fid->clnt->name;
		पूर्ण
	पूर्ण

	/* map 9p status to VFS status */
	चयन (status) अणु
	हाल P9_LOCK_SUCCESS:
		res = 0;
		अवरोध;
	हाल P9_LOCK_BLOCKED:
		res = -EAGAIN;
		अवरोध;
	शेष:
		WARN_ONCE(1, "unknown lock status code: %d\n", status);
		fallthrough;
	हाल P9_LOCK_ERROR:
	हाल P9_LOCK_GRACE:
		res = -ENOLCK;
		अवरोध;
	पूर्ण

out_unlock:
	/*
	 * inहाल server वापसed error क्रम lock request, revert
	 * it locally
	 */
	अगर (res < 0 && fl->fl_type != F_UNLCK) अणु
		fl_type = fl->fl_type;
		fl->fl_type = F_UNLCK;
		/* Even अगर this fails we want to वापस the remote error */
		locks_lock_file_रुको(filp, fl);
		fl->fl_type = fl_type;
	पूर्ण
	अगर (flock.client_id != fid->clnt->name)
		kमुक्त(flock.client_id);
out:
	वापस res;
पूर्ण

अटल पूर्णांक v9fs_file_getlock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	काष्ठा p9_getlock glock;
	काष्ठा p9_fid *fid;
	पूर्णांक res = 0;

	fid = filp->निजी_data;
	BUG_ON(fid == शून्य);

	posix_test_lock(filp, fl);
	/*
	 * अगर we have a conflicting lock locally, no need to validate
	 * with server
	 */
	अगर (fl->fl_type != F_UNLCK)
		वापस res;

	/* convert posix lock to p9 tgetlock args */
	स_रखो(&glock, 0, माप(glock));
	glock.type  = P9_LOCK_TYPE_UNLCK;
	glock.start = fl->fl_start;
	अगर (fl->fl_end == OFFSET_MAX)
		glock.length = 0;
	अन्यथा
		glock.length = fl->fl_end - fl->fl_start + 1;
	glock.proc_id = fl->fl_pid;
	glock.client_id = fid->clnt->name;

	res = p9_client_getlock_करोtl(fid, &glock);
	अगर (res < 0)
		जाओ out;
	/* map 9p lock type to os lock type */
	चयन (glock.type) अणु
	हाल P9_LOCK_TYPE_RDLCK:
		fl->fl_type = F_RDLCK;
		अवरोध;
	हाल P9_LOCK_TYPE_WRLCK:
		fl->fl_type = F_WRLCK;
		अवरोध;
	हाल P9_LOCK_TYPE_UNLCK:
		fl->fl_type = F_UNLCK;
		अवरोध;
	पूर्ण
	अगर (glock.type != P9_LOCK_TYPE_UNLCK) अणु
		fl->fl_start = glock.start;
		अगर (glock.length == 0)
			fl->fl_end = OFFSET_MAX;
		अन्यथा
			fl->fl_end = glock.start + glock.length - 1;
		fl->fl_pid = -glock.proc_id;
	पूर्ण
out:
	अगर (glock.client_id != fid->clnt->name)
		kमुक्त(glock.client_id);
	वापस res;
पूर्ण

/**
 * v9fs_file_lock_करोtl - lock a file (or directory)
 * @filp: file to be locked
 * @cmd: lock command
 * @fl: file lock काष्ठाure
 *
 */

अटल पूर्णांक v9fs_file_lock_करोtl(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret = -ENOLCK;

	p9_debug(P9_DEBUG_VFS, "filp: %p cmd:%d lock: %p name: %pD\n",
		 filp, cmd, fl, filp);

	/* No mandatory locks */
	अगर (__mandatory_lock(inode) && fl->fl_type != F_UNLCK)
		जाओ out_err;

	अगर ((IS_SETLK(cmd) || IS_SETLKW(cmd)) && fl->fl_type != F_UNLCK) अणु
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
		invalidate_mapping_pages(&inode->i_data, 0, -1);
	पूर्ण

	अगर (IS_SETLK(cmd) || IS_SETLKW(cmd))
		ret = v9fs_file_करो_lock(filp, cmd, fl);
	अन्यथा अगर (IS_GETLK(cmd))
		ret = v9fs_file_getlock(filp, fl);
	अन्यथा
		ret = -EINVAL;
out_err:
	वापस ret;
पूर्ण

/**
 * v9fs_file_flock_करोtl - lock a file
 * @filp: file to be locked
 * @cmd: lock command
 * @fl: file lock काष्ठाure
 *
 */

अटल पूर्णांक v9fs_file_flock_करोtl(काष्ठा file *filp, पूर्णांक cmd,
	काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret = -ENOLCK;

	p9_debug(P9_DEBUG_VFS, "filp: %p cmd:%d lock: %p name: %pD\n",
		 filp, cmd, fl, filp);

	/* No mandatory locks */
	अगर (__mandatory_lock(inode) && fl->fl_type != F_UNLCK)
		जाओ out_err;

	अगर (!(fl->fl_flags & FL_FLOCK))
		जाओ out_err;

	अगर ((IS_SETLK(cmd) || IS_SETLKW(cmd)) && fl->fl_type != F_UNLCK) अणु
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
		invalidate_mapping_pages(&inode->i_data, 0, -1);
	पूर्ण
	/* Convert flock to posix lock */
	fl->fl_flags |= FL_POSIX;
	fl->fl_flags ^= FL_FLOCK;

	अगर (IS_SETLK(cmd) | IS_SETLKW(cmd))
		ret = v9fs_file_करो_lock(filp, cmd, fl);
	अन्यथा
		ret = -EINVAL;
out_err:
	वापस ret;
पूर्ण

/**
 * v9fs_file_पढ़ो - पढ़ो from a file
 * @filp: file poपूर्णांकer to पढ़ो
 * @udata: user data buffer to पढ़ो data पूर्णांकo
 * @count: size of buffer
 * @offset: offset at which to पढ़ो data
 *
 */

अटल sमाप_प्रकार
v9fs_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा p9_fid *fid = iocb->ki_filp->निजी_data;
	पूर्णांक ret, err = 0;

	p9_debug(P9_DEBUG_VFS, "count %zu offset %lld\n",
		 iov_iter_count(to), iocb->ki_pos);

	अगर (iocb->ki_filp->f_flags & O_NONBLOCK)
		ret = p9_client_पढ़ो_once(fid, iocb->ki_pos, to, &err);
	अन्यथा
		ret = p9_client_पढ़ो(fid, iocb->ki_pos, to, &err);
	अगर (!ret)
		वापस err;

	iocb->ki_pos += ret;
	वापस ret;
पूर्ण

/**
 * v9fs_file_ग_लिखो - ग_लिखो to a file
 * @filp: file poपूर्णांकer to ग_लिखो
 * @data: data buffer to ग_लिखो data from
 * @count: size of buffer
 * @offset: offset at which to ग_लिखो data
 *
 */
अटल sमाप_प्रकार
v9fs_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	sमाप_प्रकार retval;
	loff_t origin;
	पूर्णांक err = 0;

	retval = generic_ग_लिखो_checks(iocb, from);
	अगर (retval <= 0)
		वापस retval;

	origin = iocb->ki_pos;
	retval = p9_client_ग_लिखो(file->निजी_data, iocb->ki_pos, from, &err);
	अगर (retval > 0) अणु
		काष्ठा inode *inode = file_inode(file);
		loff_t i_size;
		अचिन्हित दीर्घ pg_start, pg_end;
		pg_start = origin >> PAGE_SHIFT;
		pg_end = (origin + retval - 1) >> PAGE_SHIFT;
		अगर (inode->i_mapping && inode->i_mapping->nrpages)
			invalidate_inode_pages2_range(inode->i_mapping,
						      pg_start, pg_end);
		iocb->ki_pos += retval;
		i_size = i_size_पढ़ो(inode);
		अगर (iocb->ki_pos > i_size) अणु
			inode_add_bytes(inode, iocb->ki_pos - i_size);
			/*
			 * Need to serialize against i_size_ग_लिखो() in
			 * v9fs_stat2inode()
			 */
			v9fs_i_size_ग_लिखो(inode, iocb->ki_pos);
		पूर्ण
		वापस retval;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक v9fs_file_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			   पूर्णांक datasync)
अणु
	काष्ठा p9_fid *fid;
	काष्ठा inode *inode = filp->f_mapping->host;
	काष्ठा p9_wstat wstat;
	पूर्णांक retval;

	retval = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (retval)
		वापस retval;

	inode_lock(inode);
	p9_debug(P9_DEBUG_VFS, "filp %p datasync %x\n", filp, datasync);

	fid = filp->निजी_data;
	v9fs_blank_wstat(&wstat);

	retval = p9_client_wstat(fid, &wstat);
	inode_unlock(inode);

	वापस retval;
पूर्ण

पूर्णांक v9fs_file_fsync_करोtl(काष्ठा file *filp, loff_t start, loff_t end,
			 पूर्णांक datasync)
अणु
	काष्ठा p9_fid *fid;
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक retval;

	retval = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (retval)
		वापस retval;

	inode_lock(inode);
	p9_debug(P9_DEBUG_VFS, "filp %p datasync %x\n", filp, datasync);

	fid = filp->निजी_data;

	retval = p9_client_fsync(fid, datasync);
	inode_unlock(inode);

	वापस retval;
पूर्ण

अटल पूर्णांक
v9fs_file_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक retval;


	retval = generic_file_mmap(filp, vma);
	अगर (!retval)
		vma->vm_ops = &v9fs_file_vm_ops;

	वापस retval;
पूर्ण

अटल पूर्णांक
v9fs_mmap_file_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	काष्ठा v9fs_inode *v9inode;
	काष्ठा p9_fid *fid;

	inode = file_inode(filp);
	v9inode = V9FS_I(inode);
	mutex_lock(&v9inode->v_mutex);
	अगर (!v9inode->ग_लिखोback_fid &&
	    (vma->vm_flags & VM_SHARED) &&
	    (vma->vm_flags & VM_WRITE)) अणु
		/*
		 * clone a fid and add it to ग_लिखोback_fid
		 * we करो it during mmap instead of
		 * page dirty समय via ग_लिखो_begin/page_mkग_लिखो
		 * because we want ग_लिखो after unlink useहाल
		 * to work.
		 */
		fid = v9fs_ग_लिखोback_fid(file_dentry(filp));
		अगर (IS_ERR(fid)) अणु
			retval = PTR_ERR(fid);
			mutex_unlock(&v9inode->v_mutex);
			वापस retval;
		पूर्ण
		v9inode->ग_लिखोback_fid = (व्योम *) fid;
	पूर्ण
	mutex_unlock(&v9inode->v_mutex);

	retval = generic_file_mmap(filp, vma);
	अगर (!retval)
		vma->vm_ops = &v9fs_mmap_file_vm_ops;

	वापस retval;
पूर्ण

अटल vm_fault_t
v9fs_vm_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा v9fs_inode *v9inode;
	काष्ठा page *page = vmf->page;
	काष्ठा file *filp = vmf->vma->vm_file;
	काष्ठा inode *inode = file_inode(filp);


	p9_debug(P9_DEBUG_VFS, "page %p fid %lx\n",
		 page, (अचिन्हित दीर्घ)filp->निजी_data);

	/* Update file बार beक्रमe taking page lock */
	file_update_समय(filp);

	v9inode = V9FS_I(inode);
	/* make sure the cache has finished storing the page */
	v9fs_fscache_रुको_on_page_ग_लिखो(inode, page);
	BUG_ON(!v9inode->ग_लिखोback_fid);
	lock_page(page);
	अगर (page->mapping != inode->i_mapping)
		जाओ out_unlock;
	रुको_क्रम_stable_page(page);

	वापस VM_FAULT_LOCKED;
out_unlock:
	unlock_page(page);
	वापस VM_FAULT_NOPAGE;
पूर्ण

/**
 * v9fs_mmap_file_पढ़ो - पढ़ो from a file
 * @filp: file poपूर्णांकer to पढ़ो
 * @data: user data buffer to पढ़ो data पूर्णांकo
 * @count: size of buffer
 * @offset: offset at which to पढ़ो data
 *
 */
अटल sमाप_प्रकार
v9fs_mmap_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	/* TODO: Check अगर there are dirty pages */
	वापस v9fs_file_पढ़ो_iter(iocb, to);
पूर्ण

/**
 * v9fs_mmap_file_ग_लिखो - ग_लिखो to a file
 * @filp: file poपूर्णांकer to ग_लिखो
 * @data: data buffer to ग_लिखो data from
 * @count: size of buffer
 * @offset: offset at which to ग_लिखो data
 *
 */
अटल sमाप_प्रकार
v9fs_mmap_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	/*
	 * TODO: invalidate mmaps on filp's inode between
	 * offset and offset+count
	 */
	वापस v9fs_file_ग_लिखो_iter(iocb, from);
पूर्ण

अटल व्योम v9fs_mmap_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode;

	काष्ठा ग_लिखोback_control wbc = अणु
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.sync_mode = WB_SYNC_ALL,
		.range_start = (loff_t)vma->vm_pgoff * PAGE_SIZE,
		 /* असलolute end, byte at end included */
		.range_end = (loff_t)vma->vm_pgoff * PAGE_SIZE +
			(vma->vm_end - vma->vm_start - 1),
	पूर्ण;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस;

	p9_debug(P9_DEBUG_VFS, "9p VMA close, %p, flushing", vma);

	inode = file_inode(vma->vm_file);

	अगर (!mapping_can_ग_लिखोback(inode->i_mapping))
		wbc.nr_to_ग_लिखो = 0;

	might_sleep();
	sync_inode(inode, &wbc);
पूर्ण


अटल स्थिर काष्ठा vm_operations_काष्ठा v9fs_file_vm_ops = अणु
	.fault = filemap_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = v9fs_vm_page_mkग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा v9fs_mmap_file_vm_ops = अणु
	.बंद = v9fs_mmap_vm_बंद,
	.fault = filemap_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = v9fs_vm_page_mkग_लिखो,
पूर्ण;


स्थिर काष्ठा file_operations v9fs_cached_file_operations = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = generic_file_पढ़ो_iter,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock,
	.mmap = v9fs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_cached_file_operations_करोtl = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = generic_file_पढ़ो_iter,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock_करोtl,
	.flock = v9fs_file_flock_करोtl,
	.mmap = v9fs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync_करोtl,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_file_operations = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = v9fs_file_पढ़ो_iter,
	.ग_लिखो_iter = v9fs_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock,
	.mmap = generic_file_पढ़ोonly_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_file_operations_करोtl = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = v9fs_file_पढ़ो_iter,
	.ग_लिखो_iter = v9fs_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock_करोtl,
	.flock = v9fs_file_flock_करोtl,
	.mmap = generic_file_पढ़ोonly_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync_करोtl,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_mmap_file_operations = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = v9fs_mmap_file_पढ़ो_iter,
	.ग_लिखो_iter = v9fs_mmap_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock,
	.mmap = v9fs_mmap_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync,
पूर्ण;

स्थिर काष्ठा file_operations v9fs_mmap_file_operations_करोtl = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = v9fs_mmap_file_पढ़ो_iter,
	.ग_लिखो_iter = v9fs_mmap_file_ग_लिखो_iter,
	.खोलो = v9fs_file_खोलो,
	.release = v9fs_dir_release,
	.lock = v9fs_file_lock_करोtl,
	.flock = v9fs_file_flock_करोtl,
	.mmap = v9fs_mmap_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.fsync = v9fs_file_fsync_करोtl,
पूर्ण;
