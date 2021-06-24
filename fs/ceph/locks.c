<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/file.h>
#समावेश <linux/namei.h>
#समावेश <linux/अक्रमom.h>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश <linux/ceph/pagelist.h>

अटल u64 lock_secret;
अटल पूर्णांक ceph_lock_रुको_क्रम_completion(काष्ठा ceph_mds_client *mdsc,
                                         काष्ठा ceph_mds_request *req);

अटल अंतरभूत u64 secure_addr(व्योम *addr)
अणु
	u64 v = lock_secret ^ (u64)(अचिन्हित दीर्घ)addr;
	/*
	 * Set the most signअगरicant bit, so that MDS knows the 'owner'
	 * is sufficient to identअगरy the owner of lock. (old code uses
	 * both 'owner' and 'pid')
	 */
	v |= (1ULL << 63);
	वापस v;
पूर्ण

व्योम __init ceph_flock_init(व्योम)
अणु
	get_अक्रमom_bytes(&lock_secret, माप(lock_secret));
पूर्ण

अटल व्योम ceph_fl_copy_lock(काष्ठा file_lock *dst, काष्ठा file_lock *src)
अणु
	काष्ठा ceph_file_info *fi = dst->fl_file->निजी_data;
	काष्ठा inode *inode = file_inode(dst->fl_file);
	atomic_inc(&ceph_inode(inode)->i_filelock_ref);
	atomic_inc(&fi->num_locks);
पूर्ण

अटल व्योम ceph_fl_release_lock(काष्ठा file_lock *fl)
अणु
	काष्ठा ceph_file_info *fi = fl->fl_file->निजी_data;
	काष्ठा inode *inode = file_inode(fl->fl_file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	atomic_dec(&fi->num_locks);
	अगर (atomic_dec_and_test(&ci->i_filelock_ref)) अणु
		/* clear error when all locks are released */
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags &= ~CEPH_I_ERROR_खाताLOCK;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_lock_operations ceph_fl_lock_ops = अणु
	.fl_copy_lock = ceph_fl_copy_lock,
	.fl_release_निजी = ceph_fl_release_lock,
पूर्ण;

/*
 * Implement fcntl and flock locking functions.
 */
अटल पूर्णांक ceph_lock_message(u8 lock_type, u16 operation, काष्ठा inode *inode,
			     पूर्णांक cmd, u8 रुको, काष्ठा file_lock *fl)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_mds_request *req;
	पूर्णांक err;
	u64 length = 0;
	u64 owner;

	अगर (operation == CEPH_MDS_OP_SETखाताLOCK) अणु
		/*
		 * increasing i_filelock_ref बंदs race winकरोw between
		 * handling request reply and adding file_lock काष्ठा to
		 * inode. Otherwise, auth caps may get trimmed in the
		 * winकरोw. Caller function will decrease the counter.
		 */
		fl->fl_ops = &ceph_fl_lock_ops;
		fl->fl_ops->fl_copy_lock(fl, शून्य);
	पूर्ण

	अगर (operation != CEPH_MDS_OP_SETखाताLOCK || cmd == CEPH_LOCK_UNLOCK)
		रुको = 0;

	req = ceph_mdsc_create_request(mdsc, operation, USE_AUTH_MDS);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;

	/* mds requires start and length rather than start and end */
	अगर (Lदीर्घ_उच्च == fl->fl_end)
		length = 0;
	अन्यथा
		length = fl->fl_end - fl->fl_start + 1;

	owner = secure_addr(fl->fl_owner);

	करोut("ceph_lock_message: rule: %d, op: %d, owner: %llx, pid: %llu, "
	     "start: %llu, length: %llu, wait: %d, type: %d\n", (पूर्णांक)lock_type,
	     (पूर्णांक)operation, owner, (u64)fl->fl_pid, fl->fl_start, length,
	     रुको, fl->fl_type);

	req->r_args.filelock_change.rule = lock_type;
	req->r_args.filelock_change.type = cmd;
	req->r_args.filelock_change.owner = cpu_to_le64(owner);
	req->r_args.filelock_change.pid = cpu_to_le64((u64)fl->fl_pid);
	req->r_args.filelock_change.start = cpu_to_le64(fl->fl_start);
	req->r_args.filelock_change.length = cpu_to_le64(length);
	req->r_args.filelock_change.रुको = रुको;

	अगर (रुको)
		req->r_रुको_क्रम_completion = ceph_lock_रुको_क्रम_completion;

	err = ceph_mdsc_करो_request(mdsc, inode, req);
	अगर (!err && operation == CEPH_MDS_OP_GETखाताLOCK) अणु
		fl->fl_pid = -le64_to_cpu(req->r_reply_info.filelock_reply->pid);
		अगर (CEPH_LOCK_SHARED == req->r_reply_info.filelock_reply->type)
			fl->fl_type = F_RDLCK;
		अन्यथा अगर (CEPH_LOCK_EXCL == req->r_reply_info.filelock_reply->type)
			fl->fl_type = F_WRLCK;
		अन्यथा
			fl->fl_type = F_UNLCK;

		fl->fl_start = le64_to_cpu(req->r_reply_info.filelock_reply->start);
		length = le64_to_cpu(req->r_reply_info.filelock_reply->start) +
						 le64_to_cpu(req->r_reply_info.filelock_reply->length);
		अगर (length >= 1)
			fl->fl_end = length -1;
		अन्यथा
			fl->fl_end = 0;

	पूर्ण
	ceph_mdsc_put_request(req);
	करोut("ceph_lock_message: rule: %d, op: %d, pid: %llu, start: %llu, "
	     "length: %llu, wait: %d, type: %d, err code %d\n", (पूर्णांक)lock_type,
	     (पूर्णांक)operation, (u64)fl->fl_pid, fl->fl_start,
	     length, रुको, fl->fl_type, err);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_lock_रुको_क्रम_completion(काष्ठा ceph_mds_client *mdsc,
                                         काष्ठा ceph_mds_request *req)
अणु
	काष्ठा ceph_mds_request *पूर्णांकr_req;
	काष्ठा inode *inode = req->r_inode;
	पूर्णांक err, lock_type;

	BUG_ON(req->r_op != CEPH_MDS_OP_SETखाताLOCK);
	अगर (req->r_args.filelock_change.rule == CEPH_LOCK_FCNTL)
		lock_type = CEPH_LOCK_FCNTL_INTR;
	अन्यथा अगर (req->r_args.filelock_change.rule == CEPH_LOCK_FLOCK)
		lock_type = CEPH_LOCK_FLOCK_INTR;
	अन्यथा
		BUG_ON(1);
	BUG_ON(req->r_args.filelock_change.type == CEPH_LOCK_UNLOCK);

	err = रुको_क्रम_completion_पूर्णांकerruptible(&req->r_completion);
	अगर (!err)
		वापस 0;

	करोut("ceph_lock_wait_for_completion: request %llu was interrupted\n",
	     req->r_tid);

	mutex_lock(&mdsc->mutex);
	अगर (test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags)) अणु
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * ensure we aren't running concurrently with
		 * ceph_fill_trace or ceph_सूची_पढ़ो_prepopulate, which
		 * rely on locks (dir mutex) held by our caller.
		 */
		mutex_lock(&req->r_fill_mutex);
		req->r_err = err;
		set_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags);
		mutex_unlock(&req->r_fill_mutex);

		अगर (!req->r_session) अणु
			// haven't sent the request
			err = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&mdsc->mutex);
	अगर (!err)
		वापस 0;

	पूर्णांकr_req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETखाताLOCK,
					    USE_AUTH_MDS);
	अगर (IS_ERR(पूर्णांकr_req))
		वापस PTR_ERR(पूर्णांकr_req);

	पूर्णांकr_req->r_inode = inode;
	ihold(inode);
	पूर्णांकr_req->r_num_caps = 1;

	पूर्णांकr_req->r_args.filelock_change = req->r_args.filelock_change;
	पूर्णांकr_req->r_args.filelock_change.rule = lock_type;
	पूर्णांकr_req->r_args.filelock_change.type = CEPH_LOCK_UNLOCK;

	err = ceph_mdsc_करो_request(mdsc, inode, पूर्णांकr_req);
	ceph_mdsc_put_request(पूर्णांकr_req);

	अगर (err && err != -ERESTARTSYS)
		वापस err;

	रुको_क्रम_completion_समाप्तable(&req->r_safe_completion);
	वापस 0;
पूर्ण

अटल पूर्णांक try_unlock_file(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक orig_flags = fl->fl_flags;
	fl->fl_flags |= FL_EXISTS;
	err = locks_lock_file_रुको(file, fl);
	fl->fl_flags = orig_flags;
	अगर (err == -ENOENT) अणु
		अगर (!(orig_flags & FL_EXISTS))
			err = 0;
		वापस err;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Attempt to set an fcntl lock.
 * For now, this just goes away to the server. Later it may be more awesome.
 */
पूर्णांक ceph_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक err = 0;
	u16 op = CEPH_MDS_OP_SETखाताLOCK;
	u8 रुको = 0;
	u8 lock_cmd;

	अगर (!(fl->fl_flags & FL_POSIX))
		वापस -ENOLCK;
	/* No mandatory locks */
	अगर (__mandatory_lock(file->f_mapping->host) && fl->fl_type != F_UNLCK)
		वापस -ENOLCK;

	करोut("ceph_lock, fl_owner: %p\n", fl->fl_owner);

	/* set रुको bit as appropriate, then make command as Ceph expects it*/
	अगर (IS_GETLK(cmd))
		op = CEPH_MDS_OP_GETखाताLOCK;
	अन्यथा अगर (IS_SETLKW(cmd))
		रुको = 1;

	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_ceph_flags & CEPH_I_ERROR_खाताLOCK) अणु
		err = -EIO;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	अगर (err < 0) अणु
		अगर (op == CEPH_MDS_OP_SETखाताLOCK && F_UNLCK == fl->fl_type)
			posix_lock_file(file, fl, शून्य);
		वापस err;
	पूर्ण

	अगर (F_RDLCK == fl->fl_type)
		lock_cmd = CEPH_LOCK_SHARED;
	अन्यथा अगर (F_WRLCK == fl->fl_type)
		lock_cmd = CEPH_LOCK_EXCL;
	अन्यथा
		lock_cmd = CEPH_LOCK_UNLOCK;

	अगर (op == CEPH_MDS_OP_SETखाताLOCK && F_UNLCK == fl->fl_type) अणु
		err = try_unlock_file(file, fl);
		अगर (err <= 0)
			वापस err;
	पूर्ण

	err = ceph_lock_message(CEPH_LOCK_FCNTL, op, inode, lock_cmd, रुको, fl);
	अगर (!err) अणु
		अगर (op == CEPH_MDS_OP_SETखाताLOCK && F_UNLCK != fl->fl_type) अणु
			करोut("mds locked, locking locally\n");
			err = posix_lock_file(file, fl, शून्य);
			अगर (err) अणु
				/* unकरो! This should only happen अगर
				 * the kernel detects local
				 * deadlock. */
				ceph_lock_message(CEPH_LOCK_FCNTL, op, inode,
						  CEPH_LOCK_UNLOCK, 0, fl);
				करोut("got %d on posix_lock_file, undid lock\n",
				     err);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ceph_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक err = 0;
	u8 रुको = 0;
	u8 lock_cmd;

	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;
	/* No mandatory locks */
	अगर (fl->fl_type & LOCK_MAND)
		वापस -EOPNOTSUPP;

	करोut("ceph_flock, fl_file: %p\n", fl->fl_file);

	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_ceph_flags & CEPH_I_ERROR_खाताLOCK) अणु
		err = -EIO;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	अगर (err < 0) अणु
		अगर (F_UNLCK == fl->fl_type)
			locks_lock_file_रुको(file, fl);
		वापस err;
	पूर्ण

	अगर (IS_SETLKW(cmd))
		रुको = 1;

	अगर (F_RDLCK == fl->fl_type)
		lock_cmd = CEPH_LOCK_SHARED;
	अन्यथा अगर (F_WRLCK == fl->fl_type)
		lock_cmd = CEPH_LOCK_EXCL;
	अन्यथा
		lock_cmd = CEPH_LOCK_UNLOCK;

	अगर (F_UNLCK == fl->fl_type) अणु
		err = try_unlock_file(file, fl);
		अगर (err <= 0)
			वापस err;
	पूर्ण

	err = ceph_lock_message(CEPH_LOCK_FLOCK, CEPH_MDS_OP_SETखाताLOCK,
				inode, lock_cmd, रुको, fl);
	अगर (!err && F_UNLCK != fl->fl_type) अणु
		err = locks_lock_file_रुको(file, fl);
		अगर (err) अणु
			ceph_lock_message(CEPH_LOCK_FLOCK,
					  CEPH_MDS_OP_SETखाताLOCK,
					  inode, CEPH_LOCK_UNLOCK, 0, fl);
			करोut("got %d on locks_lock_file_wait, undid lock\n", err);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/*
 * Fills in the passed counter variables, so you can prepare pagelist metadata
 * beक्रमe calling ceph_encode_locks.
 */
व्योम ceph_count_locks(काष्ठा inode *inode, पूर्णांक *fcntl_count, पूर्णांक *flock_count)
अणु
	काष्ठा file_lock *lock;
	काष्ठा file_lock_context *ctx;

	*fcntl_count = 0;
	*flock_count = 0;

	ctx = inode->i_flctx;
	अगर (ctx) अणु
		spin_lock(&ctx->flc_lock);
		list_क्रम_each_entry(lock, &ctx->flc_posix, fl_list)
			++(*fcntl_count);
		list_क्रम_each_entry(lock, &ctx->flc_flock, fl_list)
			++(*flock_count);
		spin_unlock(&ctx->flc_lock);
	पूर्ण
	करोut("counted %d flock locks and %d fcntl locks\n",
	     *flock_count, *fcntl_count);
पूर्ण

/*
 * Given a poपूर्णांकer to a lock, convert it to a ceph filelock
 */
अटल पूर्णांक lock_to_ceph_filelock(काष्ठा file_lock *lock,
				 काष्ठा ceph_filelock *cephlock)
अणु
	पूर्णांक err = 0;
	cephlock->start = cpu_to_le64(lock->fl_start);
	cephlock->length = cpu_to_le64(lock->fl_end - lock->fl_start + 1);
	cephlock->client = cpu_to_le64(0);
	cephlock->pid = cpu_to_le64((u64)lock->fl_pid);
	cephlock->owner = cpu_to_le64(secure_addr(lock->fl_owner));

	चयन (lock->fl_type) अणु
	हाल F_RDLCK:
		cephlock->type = CEPH_LOCK_SHARED;
		अवरोध;
	हाल F_WRLCK:
		cephlock->type = CEPH_LOCK_EXCL;
		अवरोध;
	हाल F_UNLCK:
		cephlock->type = CEPH_LOCK_UNLOCK;
		अवरोध;
	शेष:
		करोut("Have unknown lock type %d\n", lock->fl_type);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

/*
 * Encode the flock and fcntl locks क्रम the given inode पूर्णांकo the ceph_filelock
 * array. Must be called with inode->i_lock alपढ़ोy held.
 * If we encounter more of a specअगरic lock type than expected, वापस -ENOSPC.
 */
पूर्णांक ceph_encode_locks_to_buffer(काष्ठा inode *inode,
				काष्ठा ceph_filelock *flocks,
				पूर्णांक num_fcntl_locks, पूर्णांक num_flock_locks)
अणु
	काष्ठा file_lock *lock;
	काष्ठा file_lock_context *ctx = inode->i_flctx;
	पूर्णांक err = 0;
	पूर्णांक seen_fcntl = 0;
	पूर्णांक seen_flock = 0;
	पूर्णांक l = 0;

	करोut("encoding %d flock and %d fcntl locks\n", num_flock_locks,
	     num_fcntl_locks);

	अगर (!ctx)
		वापस 0;

	spin_lock(&ctx->flc_lock);
	list_क्रम_each_entry(lock, &ctx->flc_posix, fl_list) अणु
		++seen_fcntl;
		अगर (seen_fcntl > num_fcntl_locks) अणु
			err = -ENOSPC;
			जाओ fail;
		पूर्ण
		err = lock_to_ceph_filelock(lock, &flocks[l]);
		अगर (err)
			जाओ fail;
		++l;
	पूर्ण
	list_क्रम_each_entry(lock, &ctx->flc_flock, fl_list) अणु
		++seen_flock;
		अगर (seen_flock > num_flock_locks) अणु
			err = -ENOSPC;
			जाओ fail;
		पूर्ण
		err = lock_to_ceph_filelock(lock, &flocks[l]);
		अगर (err)
			जाओ fail;
		++l;
	पूर्ण
fail:
	spin_unlock(&ctx->flc_lock);
	वापस err;
पूर्ण

/*
 * Copy the encoded flock and fcntl locks पूर्णांकo the pagelist.
 * Format is: #fcntl locks, sequential fcntl locks, #flock locks,
 * sequential flock locks.
 * Returns zero on success.
 */
पूर्णांक ceph_locks_to_pagelist(काष्ठा ceph_filelock *flocks,
			   काष्ठा ceph_pagelist *pagelist,
			   पूर्णांक num_fcntl_locks, पूर्णांक num_flock_locks)
अणु
	पूर्णांक err = 0;
	__le32 nlocks;

	nlocks = cpu_to_le32(num_fcntl_locks);
	err = ceph_pagelist_append(pagelist, &nlocks, माप(nlocks));
	अगर (err)
		जाओ out_fail;

	अगर (num_fcntl_locks > 0) अणु
		err = ceph_pagelist_append(pagelist, flocks,
					   num_fcntl_locks * माप(*flocks));
		अगर (err)
			जाओ out_fail;
	पूर्ण

	nlocks = cpu_to_le32(num_flock_locks);
	err = ceph_pagelist_append(pagelist, &nlocks, माप(nlocks));
	अगर (err)
		जाओ out_fail;

	अगर (num_flock_locks > 0) अणु
		err = ceph_pagelist_append(pagelist, &flocks[num_fcntl_locks],
					   num_flock_locks * माप(*flocks));
	पूर्ण
out_fail:
	वापस err;
पूर्ण
