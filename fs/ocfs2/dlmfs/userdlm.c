<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * userdlm.c
 *
 * Code which implements the kernel side of a minimal userspace
 * पूर्णांकerface to our DLM.
 *
 * Many of the functions here are pared करोwn versions of dlmglue.c
 * functions.
 *
 * Copyright (C) 2003, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/crc32.h>

#समावेश "../ocfs2_lockingver.h"
#समावेश "../stackglue.h"
#समावेश "userdlm.h"

#घोषणा MLOG_MASK_PREFIX ML_DLMFS
#समावेश "../cluster/masklog.h"


अटल अंतरभूत काष्ठा user_lock_res *user_lksb_to_lock_res(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस container_of(lksb, काष्ठा user_lock_res, l_lksb);
पूर्ण

अटल अंतरभूत पूर्णांक user_check_रुको_flag(काष्ठा user_lock_res *lockres,
				       पूर्णांक flag)
अणु
	पूर्णांक ret;

	spin_lock(&lockres->l_lock);
	ret = lockres->l_flags & flag;
	spin_unlock(&lockres->l_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम user_रुको_on_busy_lock(काष्ठा user_lock_res *lockres)

अणु
	रुको_event(lockres->l_event,
		   !user_check_रुको_flag(lockres, USER_LOCK_BUSY));
पूर्ण

अटल अंतरभूत व्योम user_रुको_on_blocked_lock(काष्ठा user_lock_res *lockres)

अणु
	रुको_event(lockres->l_event,
		   !user_check_रुको_flag(lockres, USER_LOCK_BLOCKED));
पूर्ण

/* I heart container_of... */
अटल अंतरभूत काष्ठा ocfs2_cluster_connection *
cluster_connection_from_user_lockres(काष्ठा user_lock_res *lockres)
अणु
	काष्ठा dlmfs_inode_निजी *ip;

	ip = container_of(lockres,
			  काष्ठा dlmfs_inode_निजी,
			  ip_lockres);
	वापस ip->ip_conn;
पूर्ण

अटल काष्ठा inode *
user_dlm_inode_from_user_lockres(काष्ठा user_lock_res *lockres)
अणु
	काष्ठा dlmfs_inode_निजी *ip;

	ip = container_of(lockres,
			  काष्ठा dlmfs_inode_निजी,
			  ip_lockres);
	वापस &ip->ip_vfs_inode;
पूर्ण

अटल अंतरभूत व्योम user_recover_from_dlm_error(काष्ठा user_lock_res *lockres)
अणु
	spin_lock(&lockres->l_lock);
	lockres->l_flags &= ~USER_LOCK_BUSY;
	spin_unlock(&lockres->l_lock);
पूर्ण

#घोषणा user_log_dlm_error(_func, _stat, _lockres) करो अणु			\
	mlog(ML_ERROR, "Dlm error %d while calling %s on "		\
		"resource %.*s\n", _stat, _func,			\
		_lockres->l_namelen, _lockres->l_name); 		\
पूर्ण जबतक (0)

/* WARNING: This function lives in a world where the only three lock
 * levels are EX, PR, and NL. It *will* have to be adjusted when more
 * lock types are added. */
अटल अंतरभूत पूर्णांक user_highest_compat_lock_level(पूर्णांक level)
अणु
	पूर्णांक new_level = DLM_LOCK_EX;

	अगर (level == DLM_LOCK_EX)
		new_level = DLM_LOCK_NL;
	अन्यथा अगर (level == DLM_LOCK_PR)
		new_level = DLM_LOCK_PR;
	वापस new_level;
पूर्ण

अटल व्योम user_ast(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	काष्ठा user_lock_res *lockres = user_lksb_to_lock_res(lksb);
	पूर्णांक status;

	mlog(ML_BASTS, "AST fired for lockres %.*s, level %d => %d\n",
	     lockres->l_namelen, lockres->l_name, lockres->l_level,
	     lockres->l_requested);

	spin_lock(&lockres->l_lock);

	status = ocfs2_dlm_lock_status(&lockres->l_lksb);
	अगर (status) अणु
		mlog(ML_ERROR, "lksb status value of %u on lockres %.*s\n",
		     status, lockres->l_namelen, lockres->l_name);
		spin_unlock(&lockres->l_lock);
		वापस;
	पूर्ण

	mlog_bug_on_msg(lockres->l_requested == DLM_LOCK_IV,
			"Lockres %.*s, requested ivmode. flags 0x%x\n",
			lockres->l_namelen, lockres->l_name, lockres->l_flags);

	/* we're करोwnconverting. */
	अगर (lockres->l_requested < lockres->l_level) अणु
		अगर (lockres->l_requested <=
		    user_highest_compat_lock_level(lockres->l_blocking)) अणु
			lockres->l_blocking = DLM_LOCK_NL;
			lockres->l_flags &= ~USER_LOCK_BLOCKED;
		पूर्ण
	पूर्ण

	lockres->l_level = lockres->l_requested;
	lockres->l_requested = DLM_LOCK_IV;
	lockres->l_flags |= USER_LOCK_ATTACHED;
	lockres->l_flags &= ~USER_LOCK_BUSY;

	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
पूर्ण

अटल अंतरभूत व्योम user_dlm_grab_inode_ref(काष्ठा user_lock_res *lockres)
अणु
	काष्ठा inode *inode;
	inode = user_dlm_inode_from_user_lockres(lockres);
	अगर (!igrab(inode))
		BUG();
पूर्ण

अटल व्योम user_dlm_unblock_lock(काष्ठा work_काष्ठा *work);

अटल व्योम __user_dlm_queue_lockres(काष्ठा user_lock_res *lockres)
अणु
	अगर (!(lockres->l_flags & USER_LOCK_QUEUED)) अणु
		user_dlm_grab_inode_ref(lockres);

		INIT_WORK(&lockres->l_work, user_dlm_unblock_lock);

		queue_work(user_dlm_worker, &lockres->l_work);
		lockres->l_flags |= USER_LOCK_QUEUED;
	पूर्ण
पूर्ण

अटल व्योम __user_dlm_cond_queue_lockres(काष्ठा user_lock_res *lockres)
अणु
	पूर्णांक queue = 0;

	अगर (!(lockres->l_flags & USER_LOCK_BLOCKED))
		वापस;

	चयन (lockres->l_blocking) अणु
	हाल DLM_LOCK_EX:
		अगर (!lockres->l_ex_holders && !lockres->l_ro_holders)
			queue = 1;
		अवरोध;
	हाल DLM_LOCK_PR:
		अगर (!lockres->l_ex_holders)
			queue = 1;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (queue)
		__user_dlm_queue_lockres(lockres);
पूर्ण

अटल व्योम user_bast(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक level)
अणु
	काष्ठा user_lock_res *lockres = user_lksb_to_lock_res(lksb);

	mlog(ML_BASTS, "BAST fired for lockres %.*s, blocking %d, level %d\n",
	     lockres->l_namelen, lockres->l_name, level, lockres->l_level);

	spin_lock(&lockres->l_lock);
	lockres->l_flags |= USER_LOCK_BLOCKED;
	अगर (level > lockres->l_blocking)
		lockres->l_blocking = level;

	__user_dlm_queue_lockres(lockres);
	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
पूर्ण

अटल व्योम user_unlock_ast(काष्ठा ocfs2_dlm_lksb *lksb, पूर्णांक status)
अणु
	काष्ठा user_lock_res *lockres = user_lksb_to_lock_res(lksb);

	mlog(ML_BASTS, "UNLOCK AST fired for lockres %.*s, flags 0x%x\n",
	     lockres->l_namelen, lockres->l_name, lockres->l_flags);

	अगर (status)
		mlog(ML_ERROR, "dlm returns status %d\n", status);

	spin_lock(&lockres->l_lock);
	/* The tearकरोwn flag माला_लो set early during the unlock process,
	 * so test the cancel flag to make sure that this ast isn't
	 * क्रम a concurrent cancel. */
	अगर (lockres->l_flags & USER_LOCK_IN_TEARDOWN
	    && !(lockres->l_flags & USER_LOCK_IN_CANCEL)) अणु
		lockres->l_level = DLM_LOCK_IV;
	पूर्ण अन्यथा अगर (status == DLM_CANCELGRANT) अणु
		/* We tried to cancel a convert request, but it was
		 * alपढ़ोy granted. Don't clear the busy flag - the
		 * ast should've करोne this alपढ़ोy. */
		BUG_ON(!(lockres->l_flags & USER_LOCK_IN_CANCEL));
		lockres->l_flags &= ~USER_LOCK_IN_CANCEL;
		जाओ out_noclear;
	पूर्ण अन्यथा अणु
		BUG_ON(!(lockres->l_flags & USER_LOCK_IN_CANCEL));
		/* Cancel succeeded, we want to re-queue */
		lockres->l_requested = DLM_LOCK_IV; /* cancel an
						    * upconvert
						    * request. */
		lockres->l_flags &= ~USER_LOCK_IN_CANCEL;
		/* we want the unblock thपढ़ो to look at it again
		 * now. */
		अगर (lockres->l_flags & USER_LOCK_BLOCKED)
			__user_dlm_queue_lockres(lockres);
	पूर्ण

	lockres->l_flags &= ~USER_LOCK_BUSY;
out_noclear:
	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
पूर्ण

/*
 * This is the userdlmfs locking protocol version.
 *
 * See fs/ocfs2/dlmglue.c क्रम more details on locking versions.
 */
अटल काष्ठा ocfs2_locking_protocol user_dlm_lproto = अणु
	.lp_max_version = अणु
		.pv_major = OCFS2_LOCKING_PROTOCOL_MAJOR,
		.pv_minor = OCFS2_LOCKING_PROTOCOL_MINOR,
	पूर्ण,
	.lp_lock_ast		= user_ast,
	.lp_blocking_ast	= user_bast,
	.lp_unlock_ast		= user_unlock_ast,
पूर्ण;

अटल अंतरभूत व्योम user_dlm_drop_inode_ref(काष्ठा user_lock_res *lockres)
अणु
	काष्ठा inode *inode;
	inode = user_dlm_inode_from_user_lockres(lockres);
	iput(inode);
पूर्ण

अटल व्योम user_dlm_unblock_lock(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक new_level, status;
	काष्ठा user_lock_res *lockres =
		container_of(work, काष्ठा user_lock_res, l_work);
	काष्ठा ocfs2_cluster_connection *conn =
		cluster_connection_from_user_lockres(lockres);

	mlog(0, "lockres %.*s\n", lockres->l_namelen, lockres->l_name);

	spin_lock(&lockres->l_lock);

	mlog_bug_on_msg(!(lockres->l_flags & USER_LOCK_QUEUED),
			"Lockres %.*s, flags 0x%x\n",
			lockres->l_namelen, lockres->l_name, lockres->l_flags);

	/* notice that we करोn't clear USER_LOCK_BLOCKED here. If it's
	 * set, we want user_ast clear it. */
	lockres->l_flags &= ~USER_LOCK_QUEUED;

	/* It's valid to get here and no दीर्घer be blocked - अगर we get
	 * several basts in a row, we might be queued by the first
	 * one, the unblock thपढ़ो might run and clear the queued
	 * flag, and finally we might get another bast which re-queues
	 * us beक्रमe our ast क्रम the करोwnconvert is called. */
	अगर (!(lockres->l_flags & USER_LOCK_BLOCKED)) अणु
		mlog(ML_BASTS, "lockres %.*s USER_LOCK_BLOCKED\n",
		     lockres->l_namelen, lockres->l_name);
		spin_unlock(&lockres->l_lock);
		जाओ drop_ref;
	पूर्ण

	अगर (lockres->l_flags & USER_LOCK_IN_TEARDOWN) अणु
		mlog(ML_BASTS, "lockres %.*s USER_LOCK_IN_TEARDOWN\n",
		     lockres->l_namelen, lockres->l_name);
		spin_unlock(&lockres->l_lock);
		जाओ drop_ref;
	पूर्ण

	अगर (lockres->l_flags & USER_LOCK_BUSY) अणु
		अगर (lockres->l_flags & USER_LOCK_IN_CANCEL) अणु
			mlog(ML_BASTS, "lockres %.*s USER_LOCK_IN_CANCEL\n",
			     lockres->l_namelen, lockres->l_name);
			spin_unlock(&lockres->l_lock);
			जाओ drop_ref;
		पूर्ण

		lockres->l_flags |= USER_LOCK_IN_CANCEL;
		spin_unlock(&lockres->l_lock);

		status = ocfs2_dlm_unlock(conn, &lockres->l_lksb,
					  DLM_LKF_CANCEL);
		अगर (status)
			user_log_dlm_error("ocfs2_dlm_unlock", status, lockres);
		जाओ drop_ref;
	पूर्ण

	/* If there are still incompat holders, we can निकास safely
	 * without worrying about re-queueing this lock as that will
	 * happen on the last call to user_cluster_unlock. */
	अगर ((lockres->l_blocking == DLM_LOCK_EX)
	    && (lockres->l_ex_holders || lockres->l_ro_holders)) अणु
		spin_unlock(&lockres->l_lock);
		mlog(ML_BASTS, "lockres %.*s, EX/PR Holders %u,%u\n",
		     lockres->l_namelen, lockres->l_name,
		     lockres->l_ex_holders, lockres->l_ro_holders);
		जाओ drop_ref;
	पूर्ण

	अगर ((lockres->l_blocking == DLM_LOCK_PR)
	    && lockres->l_ex_holders) अणु
		spin_unlock(&lockres->l_lock);
		mlog(ML_BASTS, "lockres %.*s, EX Holders %u\n",
		     lockres->l_namelen, lockres->l_name,
		     lockres->l_ex_holders);
		जाओ drop_ref;
	पूर्ण

	/* yay, we can करोwnconvert now. */
	new_level = user_highest_compat_lock_level(lockres->l_blocking);
	lockres->l_requested = new_level;
	lockres->l_flags |= USER_LOCK_BUSY;
	mlog(ML_BASTS, "lockres %.*s, downconvert %d => %d\n",
	     lockres->l_namelen, lockres->l_name, lockres->l_level, new_level);
	spin_unlock(&lockres->l_lock);

	/* need lock करोwnconvert request now... */
	status = ocfs2_dlm_lock(conn, new_level, &lockres->l_lksb,
				DLM_LKF_CONVERT|DLM_LKF_VALBLK,
				lockres->l_name,
				lockres->l_namelen);
	अगर (status) अणु
		user_log_dlm_error("ocfs2_dlm_lock", status, lockres);
		user_recover_from_dlm_error(lockres);
	पूर्ण

drop_ref:
	user_dlm_drop_inode_ref(lockres);
पूर्ण

अटल अंतरभूत व्योम user_dlm_inc_holders(काष्ठा user_lock_res *lockres,
					पूर्णांक level)
अणु
	चयन(level) अणु
	हाल DLM_LOCK_EX:
		lockres->l_ex_holders++;
		अवरोध;
	हाल DLM_LOCK_PR:
		lockres->l_ro_holders++;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/* predict what lock level we'll be dropping करोwn to on behalf
 * of another node, and वापस true अगर the currently wanted
 * level will be compatible with it. */
अटल अंतरभूत पूर्णांक
user_may_जारी_on_blocked_lock(काष्ठा user_lock_res *lockres,
				  पूर्णांक wanted)
अणु
	BUG_ON(!(lockres->l_flags & USER_LOCK_BLOCKED));

	वापस wanted <= user_highest_compat_lock_level(lockres->l_blocking);
पूर्ण

पूर्णांक user_dlm_cluster_lock(काष्ठा user_lock_res *lockres,
			  पूर्णांक level,
			  पूर्णांक lkm_flags)
अणु
	पूर्णांक status, local_flags;
	काष्ठा ocfs2_cluster_connection *conn =
		cluster_connection_from_user_lockres(lockres);

	अगर (level != DLM_LOCK_EX &&
	    level != DLM_LOCK_PR) अणु
		mlog(ML_ERROR, "lockres %.*s: invalid request!\n",
		     lockres->l_namelen, lockres->l_name);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	mlog(ML_BASTS, "lockres %.*s, level %d, flags = 0x%x\n",
	     lockres->l_namelen, lockres->l_name, level, lkm_flags);

again:
	अगर (संकेत_pending(current)) अणु
		status = -ERESTARTSYS;
		जाओ bail;
	पूर्ण

	spin_lock(&lockres->l_lock);

	/* We only compare against the currently granted level
	 * here. If the lock is blocked रुकोing on a करोwnconvert,
	 * we'll get caught below. */
	अगर ((lockres->l_flags & USER_LOCK_BUSY) &&
	    (level > lockres->l_level)) अणु
		/* is someone sitting in dlm_lock? If so, रुको on
		 * them. */
		spin_unlock(&lockres->l_lock);

		user_रुको_on_busy_lock(lockres);
		जाओ again;
	पूर्ण

	अगर ((lockres->l_flags & USER_LOCK_BLOCKED) &&
	    (!user_may_जारी_on_blocked_lock(lockres, level))) अणु
		/* is the lock is currently blocked on behalf of
		 * another node */
		spin_unlock(&lockres->l_lock);

		user_रुको_on_blocked_lock(lockres);
		जाओ again;
	पूर्ण

	अगर (level > lockres->l_level) अणु
		local_flags = lkm_flags | DLM_LKF_VALBLK;
		अगर (lockres->l_level != DLM_LOCK_IV)
			local_flags |= DLM_LKF_CONVERT;

		lockres->l_requested = level;
		lockres->l_flags |= USER_LOCK_BUSY;
		spin_unlock(&lockres->l_lock);

		BUG_ON(level == DLM_LOCK_IV);
		BUG_ON(level == DLM_LOCK_NL);

		/* call dlm_lock to upgrade lock now */
		status = ocfs2_dlm_lock(conn, level, &lockres->l_lksb,
					local_flags, lockres->l_name,
					lockres->l_namelen);
		अगर (status) अणु
			अगर ((lkm_flags & DLM_LKF_NOQUEUE) &&
			    (status != -EAGAIN))
				user_log_dlm_error("ocfs2_dlm_lock",
						   status, lockres);
			user_recover_from_dlm_error(lockres);
			जाओ bail;
		पूर्ण

		user_रुको_on_busy_lock(lockres);
		जाओ again;
	पूर्ण

	user_dlm_inc_holders(lockres, level);
	spin_unlock(&lockres->l_lock);

	status = 0;
bail:
	वापस status;
पूर्ण

अटल अंतरभूत व्योम user_dlm_dec_holders(काष्ठा user_lock_res *lockres,
					पूर्णांक level)
अणु
	चयन(level) अणु
	हाल DLM_LOCK_EX:
		BUG_ON(!lockres->l_ex_holders);
		lockres->l_ex_holders--;
		अवरोध;
	हाल DLM_LOCK_PR:
		BUG_ON(!lockres->l_ro_holders);
		lockres->l_ro_holders--;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम user_dlm_cluster_unlock(काष्ठा user_lock_res *lockres,
			     पूर्णांक level)
अणु
	अगर (level != DLM_LOCK_EX &&
	    level != DLM_LOCK_PR) अणु
		mlog(ML_ERROR, "lockres %.*s: invalid request!\n",
		     lockres->l_namelen, lockres->l_name);
		वापस;
	पूर्ण

	spin_lock(&lockres->l_lock);
	user_dlm_dec_holders(lockres, level);
	__user_dlm_cond_queue_lockres(lockres);
	spin_unlock(&lockres->l_lock);
पूर्ण

व्योम user_dlm_ग_लिखो_lvb(काष्ठा inode *inode,
			स्थिर अक्षर *val,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा user_lock_res *lockres = &DLMFS_I(inode)->ip_lockres;
	अक्षर *lvb;

	BUG_ON(len > DLM_LVB_LEN);

	spin_lock(&lockres->l_lock);

	BUG_ON(lockres->l_level < DLM_LOCK_EX);
	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	स_नकल(lvb, val, len);

	spin_unlock(&lockres->l_lock);
पूर्ण

bool user_dlm_पढ़ो_lvb(काष्ठा inode *inode, अक्षर *val)
अणु
	काष्ठा user_lock_res *lockres = &DLMFS_I(inode)->ip_lockres;
	अक्षर *lvb;
	bool ret = true;

	spin_lock(&lockres->l_lock);

	BUG_ON(lockres->l_level < DLM_LOCK_PR);
	अगर (ocfs2_dlm_lvb_valid(&lockres->l_lksb)) अणु
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		स_नकल(val, lvb, DLM_LVB_LEN);
	पूर्ण अन्यथा
		ret = false;

	spin_unlock(&lockres->l_lock);
	वापस ret;
पूर्ण

व्योम user_dlm_lock_res_init(काष्ठा user_lock_res *lockres,
			    काष्ठा dentry *dentry)
अणु
	स_रखो(lockres, 0, माप(*lockres));

	spin_lock_init(&lockres->l_lock);
	init_रुकोqueue_head(&lockres->l_event);
	lockres->l_level = DLM_LOCK_IV;
	lockres->l_requested = DLM_LOCK_IV;
	lockres->l_blocking = DLM_LOCK_IV;

	/* should have been checked beक्रमe getting here. */
	BUG_ON(dentry->d_name.len >= USER_DLM_LOCK_ID_MAX_LEN);

	स_नकल(lockres->l_name,
	       dentry->d_name.name,
	       dentry->d_name.len);
	lockres->l_namelen = dentry->d_name.len;
पूर्ण

पूर्णांक user_dlm_destroy_lock(काष्ठा user_lock_res *lockres)
अणु
	पूर्णांक status = -EBUSY;
	काष्ठा ocfs2_cluster_connection *conn =
		cluster_connection_from_user_lockres(lockres);

	mlog(ML_BASTS, "lockres %.*s\n", lockres->l_namelen, lockres->l_name);

	spin_lock(&lockres->l_lock);
	अगर (lockres->l_flags & USER_LOCK_IN_TEARDOWN) अणु
		spin_unlock(&lockres->l_lock);
		वापस 0;
	पूर्ण

	lockres->l_flags |= USER_LOCK_IN_TEARDOWN;

	जबतक (lockres->l_flags & USER_LOCK_BUSY) अणु
		spin_unlock(&lockres->l_lock);

		user_रुको_on_busy_lock(lockres);

		spin_lock(&lockres->l_lock);
	पूर्ण

	अगर (lockres->l_ro_holders || lockres->l_ex_holders) अणु
		spin_unlock(&lockres->l_lock);
		जाओ bail;
	पूर्ण

	status = 0;
	अगर (!(lockres->l_flags & USER_LOCK_ATTACHED)) अणु
		spin_unlock(&lockres->l_lock);
		जाओ bail;
	पूर्ण

	lockres->l_flags &= ~USER_LOCK_ATTACHED;
	lockres->l_flags |= USER_LOCK_BUSY;
	spin_unlock(&lockres->l_lock);

	status = ocfs2_dlm_unlock(conn, &lockres->l_lksb, DLM_LKF_VALBLK);
	अगर (status) अणु
		user_log_dlm_error("ocfs2_dlm_unlock", status, lockres);
		जाओ bail;
	पूर्ण

	user_रुको_on_busy_lock(lockres);

	status = 0;
bail:
	वापस status;
पूर्ण

अटल व्योम user_dlm_recovery_handler_noop(पूर्णांक node_num,
					   व्योम *recovery_data)
अणु
	/* We ignore recovery events */
	वापस;
पूर्ण

व्योम user_dlm_set_locking_protocol(व्योम)
अणु
	ocfs2_stack_glue_set_max_proto_version(&user_dlm_lproto.lp_max_version);
पूर्ण

काष्ठा ocfs2_cluster_connection *user_dlm_रेजिस्टर(स्थिर काष्ठा qstr *name)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_cluster_connection *conn;

	rc = ocfs2_cluster_connect_agnostic(name->name, name->len,
					    &user_dlm_lproto,
					    user_dlm_recovery_handler_noop,
					    शून्य, &conn);
	अगर (rc)
		mlog_त्रुटि_सं(rc);

	वापस rc ? ERR_PTR(rc) : conn;
पूर्ण

व्योम user_dlm_unरेजिस्टर(काष्ठा ocfs2_cluster_connection *conn)
अणु
	ocfs2_cluster_disconnect(conn, 0);
पूर्ण
