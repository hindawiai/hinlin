<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2010 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/dlm.h>
#समावेश <linux/dlm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "lock.h"
#समावेश "lvb_table.h"
#समावेश "user.h"
#समावेश "ast.h"
#समावेश "config.h"

अटल स्थिर अक्षर name_prefix[] = "dlm";
अटल स्थिर काष्ठा file_operations device_fops;
अटल atomic_t dlm_monitor_खोलोed;
अटल पूर्णांक dlm_monitor_unused = 1;

#अगर_घोषित CONFIG_COMPAT

काष्ठा dlm_lock_params32 अणु
	__u8 mode;
	__u8 namelen;
	__u16 unused;
	__u32 flags;
	__u32 lkid;
	__u32 parent;
	__u64 xid;
	__u64 समयout;
	__u32 castparam;
	__u32 castaddr;
	__u32 bastparam;
	__u32 bastaddr;
	__u32 lksb;
	अक्षर lvb[DLM_USER_LVB_LEN];
	अक्षर name[];
पूर्ण;

काष्ठा dlm_ग_लिखो_request32 अणु
	__u32 version[3];
	__u8 cmd;
	__u8 is64bit;
	__u8 unused[2];

	जोड़  अणु
		काष्ठा dlm_lock_params32 lock;
		काष्ठा dlm_lspace_params lspace;
		काष्ठा dlm_purge_params purge;
	पूर्ण i;
पूर्ण;

काष्ठा dlm_lksb32 अणु
	__u32 sb_status;
	__u32 sb_lkid;
	__u8 sb_flags;
	__u32 sb_lvbptr;
पूर्ण;

काष्ठा dlm_lock_result32 अणु
	__u32 version[3];
	__u32 length;
	__u32 user_astaddr;
	__u32 user_astparam;
	__u32 user_lksb;
	काष्ठा dlm_lksb32 lksb;
	__u8 bast_mode;
	__u8 unused[3];
	/* Offsets may be zero अगर no data is present */
	__u32 lvb_offset;
पूर्ण;

अटल व्योम compat_input(काष्ठा dlm_ग_लिखो_request *kb,
			 काष्ठा dlm_ग_लिखो_request32 *kb32,
			 पूर्णांक namelen)
अणु
	kb->version[0] = kb32->version[0];
	kb->version[1] = kb32->version[1];
	kb->version[2] = kb32->version[2];

	kb->cmd = kb32->cmd;
	kb->is64bit = kb32->is64bit;
	अगर (kb->cmd == DLM_USER_CREATE_LOCKSPACE ||
	    kb->cmd == DLM_USER_REMOVE_LOCKSPACE) अणु
		kb->i.lspace.flags = kb32->i.lspace.flags;
		kb->i.lspace.minor = kb32->i.lspace.minor;
		स_नकल(kb->i.lspace.name, kb32->i.lspace.name, namelen);
	पूर्ण अन्यथा अगर (kb->cmd == DLM_USER_PURGE) अणु
		kb->i.purge.nodeid = kb32->i.purge.nodeid;
		kb->i.purge.pid = kb32->i.purge.pid;
	पूर्ण अन्यथा अणु
		kb->i.lock.mode = kb32->i.lock.mode;
		kb->i.lock.namelen = kb32->i.lock.namelen;
		kb->i.lock.flags = kb32->i.lock.flags;
		kb->i.lock.lkid = kb32->i.lock.lkid;
		kb->i.lock.parent = kb32->i.lock.parent;
		kb->i.lock.xid = kb32->i.lock.xid;
		kb->i.lock.समयout = kb32->i.lock.समयout;
		kb->i.lock.castparam = (व्योम *)(दीर्घ)kb32->i.lock.castparam;
		kb->i.lock.castaddr = (व्योम *)(दीर्घ)kb32->i.lock.castaddr;
		kb->i.lock.bastparam = (व्योम *)(दीर्घ)kb32->i.lock.bastparam;
		kb->i.lock.bastaddr = (व्योम *)(दीर्घ)kb32->i.lock.bastaddr;
		kb->i.lock.lksb = (व्योम *)(दीर्घ)kb32->i.lock.lksb;
		स_नकल(kb->i.lock.lvb, kb32->i.lock.lvb, DLM_USER_LVB_LEN);
		स_नकल(kb->i.lock.name, kb32->i.lock.name, namelen);
	पूर्ण
पूर्ण

अटल व्योम compat_output(काष्ठा dlm_lock_result *res,
			  काष्ठा dlm_lock_result32 *res32)
अणु
	स_रखो(res32, 0, माप(*res32));

	res32->version[0] = res->version[0];
	res32->version[1] = res->version[1];
	res32->version[2] = res->version[2];

	res32->user_astaddr = (__u32)(दीर्घ)res->user_astaddr;
	res32->user_astparam = (__u32)(दीर्घ)res->user_astparam;
	res32->user_lksb = (__u32)(दीर्घ)res->user_lksb;
	res32->bast_mode = res->bast_mode;

	res32->lvb_offset = res->lvb_offset;
	res32->length = res->length;

	res32->lksb.sb_status = res->lksb.sb_status;
	res32->lksb.sb_flags = res->lksb.sb_flags;
	res32->lksb.sb_lkid = res->lksb.sb_lkid;
	res32->lksb.sb_lvbptr = (__u32)(दीर्घ)res->lksb.sb_lvbptr;
पूर्ण
#पूर्ण_अगर

/* Figure out अगर this lock is at the end of its lअगरe and no दीर्घer
   available क्रम the application to use.  The lkb still exists until
   the final ast is पढ़ो.  A lock becomes EOL in three situations:
     1. a noqueue request fails with EAGAIN
     2. an unlock completes with EUNLOCK
     3. a cancel of a रुकोing request completes with ECANCEL/EDEADLK
   An EOL lock needs to be हटाओd from the process's list of locks.
   And we can't allow any new operation on an EOL lock.  This is
   not related to the lअगरeसमय of the lkb काष्ठा which is managed
   entirely by refcount. */

अटल पूर्णांक lkb_is_enकरोflअगरe(पूर्णांक mode, पूर्णांक status)
अणु
	चयन (status) अणु
	हाल -DLM_EUNLOCK:
		वापस 1;
	हाल -DLM_ECANCEL:
	हाल -ETIMEDOUT:
	हाल -EDEADLK:
	हाल -EAGAIN:
		अगर (mode == DLM_LOCK_IV)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* we could possibly check अगर the cancel of an orphan has resulted in the lkb
   being हटाओd and then हटाओ that lkb from the orphans list and मुक्त it */

व्योम dlm_user_add_ast(काष्ठा dlm_lkb *lkb, uपूर्णांक32_t flags, पूर्णांक mode,
		      पूर्णांक status, uपूर्णांक32_t sbflags, uपूर्णांक64_t seq)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा dlm_user_args *ua;
	काष्ठा dlm_user_proc *proc;
	पूर्णांक rv;

	अगर (lkb->lkb_flags & (DLM_IFL_ORPHAN | DLM_IFL_DEAD))
		वापस;

	ls = lkb->lkb_resource->res_ls;
	mutex_lock(&ls->ls_clear_proc_locks);

	/* If ORPHAN/DEAD flag is set, it means the process is dead so an ast
	   can't be delivered.  For ORPHAN's, dlm_clear_proc_locks() मुक्तd
	   lkb->ua so we can't try to use it.  This second check is necessary
	   क्रम हालs where a completion ast is received क्रम an operation that
	   began beक्रमe clear_proc_locks did its cancel/unlock. */

	अगर (lkb->lkb_flags & (DLM_IFL_ORPHAN | DLM_IFL_DEAD))
		जाओ out;

	DLM_ASSERT(lkb->lkb_ua, dlm_prपूर्णांक_lkb(lkb););
	ua = lkb->lkb_ua;
	proc = ua->proc;

	अगर ((flags & DLM_CB_BAST) && ua->bastaddr == शून्य)
		जाओ out;

	अगर ((flags & DLM_CB_CAST) && lkb_is_enकरोflअगरe(mode, status))
		lkb->lkb_flags |= DLM_IFL_ENDOFLIFE;

	spin_lock(&proc->asts_spin);

	rv = dlm_add_lkb_callback(lkb, flags, mode, status, sbflags, seq);
	अगर (rv < 0) अणु
		spin_unlock(&proc->asts_spin);
		जाओ out;
	पूर्ण

	अगर (list_empty(&lkb->lkb_cb_list)) अणु
		kref_get(&lkb->lkb_ref);
		list_add_tail(&lkb->lkb_cb_list, &proc->asts);
		wake_up_पूर्णांकerruptible(&proc->रुको);
	पूर्ण
	spin_unlock(&proc->asts_spin);

	अगर (lkb->lkb_flags & DLM_IFL_ENDOFLIFE) अणु
		/* N.B. spin_lock locks_spin, not asts_spin */
		spin_lock(&proc->locks_spin);
		अगर (!list_empty(&lkb->lkb_ownqueue)) अणु
			list_del_init(&lkb->lkb_ownqueue);
			dlm_put_lkb(lkb);
		पूर्ण
		spin_unlock(&proc->locks_spin);
	पूर्ण
 out:
	mutex_unlock(&ls->ls_clear_proc_locks);
पूर्ण

अटल पूर्णांक device_user_lock(काष्ठा dlm_user_proc *proc,
			    काष्ठा dlm_lock_params *params)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा dlm_user_args *ua;
	uपूर्णांक32_t lkid;
	पूर्णांक error = -ENOMEM;

	ls = dlm_find_lockspace_local(proc->lockspace);
	अगर (!ls)
		वापस -ENOENT;

	अगर (!params->castaddr || !params->lksb) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	ua = kzalloc(माप(काष्ठा dlm_user_args), GFP_NOFS);
	अगर (!ua)
		जाओ out;
	ua->proc = proc;
	ua->user_lksb = params->lksb;
	ua->castparam = params->castparam;
	ua->castaddr = params->castaddr;
	ua->bastparam = params->bastparam;
	ua->bastaddr = params->bastaddr;
	ua->xid = params->xid;

	अगर (params->flags & DLM_LKF_CONVERT) अणु
		error = dlm_user_convert(ls, ua,
				         params->mode, params->flags,
				         params->lkid, params->lvb,
					 (अचिन्हित दीर्घ) params->समयout);
	पूर्ण अन्यथा अगर (params->flags & DLM_LKF_ORPHAN) अणु
		error = dlm_user_aकरोpt_orphan(ls, ua,
					 params->mode, params->flags,
					 params->name, params->namelen,
					 (अचिन्हित दीर्घ) params->समयout,
					 &lkid);
		अगर (!error)
			error = lkid;
	पूर्ण अन्यथा अणु
		error = dlm_user_request(ls, ua,
					 params->mode, params->flags,
					 params->name, params->namelen,
					 (अचिन्हित दीर्घ) params->समयout);
		अगर (!error)
			error = ua->lksb.sb_lkid;
	पूर्ण
 out:
	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

अटल पूर्णांक device_user_unlock(काष्ठा dlm_user_proc *proc,
			      काष्ठा dlm_lock_params *params)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा dlm_user_args *ua;
	पूर्णांक error = -ENOMEM;

	ls = dlm_find_lockspace_local(proc->lockspace);
	अगर (!ls)
		वापस -ENOENT;

	ua = kzalloc(माप(काष्ठा dlm_user_args), GFP_NOFS);
	अगर (!ua)
		जाओ out;
	ua->proc = proc;
	ua->user_lksb = params->lksb;
	ua->castparam = params->castparam;
	ua->castaddr = params->castaddr;

	अगर (params->flags & DLM_LKF_CANCEL)
		error = dlm_user_cancel(ls, ua, params->flags, params->lkid);
	अन्यथा
		error = dlm_user_unlock(ls, ua, params->flags, params->lkid,
					params->lvb);
 out:
	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

अटल पूर्णांक device_user_deadlock(काष्ठा dlm_user_proc *proc,
				काष्ठा dlm_lock_params *params)
अणु
	काष्ठा dlm_ls *ls;
	पूर्णांक error;

	ls = dlm_find_lockspace_local(proc->lockspace);
	अगर (!ls)
		वापस -ENOENT;

	error = dlm_user_deadlock(ls, params->flags, params->lkid);

	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

अटल पूर्णांक dlm_device_रेजिस्टर(काष्ठा dlm_ls *ls, अक्षर *name)
अणु
	पूर्णांक error, len;

	/* The device is alपढ़ोy रेजिस्टरed.  This happens when the
	   lockspace is created multiple बार from userspace. */
	अगर (ls->ls_device.name)
		वापस 0;

	error = -ENOMEM;
	len = म_माप(name) + म_माप(name_prefix) + 2;
	ls->ls_device.name = kzalloc(len, GFP_NOFS);
	अगर (!ls->ls_device.name)
		जाओ fail;

	snम_लिखो((अक्षर *)ls->ls_device.name, len, "%s_%s", name_prefix,
		 name);
	ls->ls_device.fops = &device_fops;
	ls->ls_device.minor = MISC_DYNAMIC_MINOR;

	error = misc_रेजिस्टर(&ls->ls_device);
	अगर (error) अणु
		kमुक्त(ls->ls_device.name);
		/* this has to be set to शून्य
		 * to aव्योम a द्विगुन-मुक्त in dlm_device_deरेजिस्टर
		 */
		ls->ls_device.name = शून्य;
	पूर्ण
fail:
	वापस error;
पूर्ण

पूर्णांक dlm_device_deरेजिस्टर(काष्ठा dlm_ls *ls)
अणु
	/* The device is not रेजिस्टरed.  This happens when the lockspace
	   was never used from userspace, or when device_create_lockspace()
	   calls dlm_release_lockspace() after the रेजिस्टर fails. */
	अगर (!ls->ls_device.name)
		वापस 0;

	misc_deरेजिस्टर(&ls->ls_device);
	kमुक्त(ls->ls_device.name);
	वापस 0;
पूर्ण

अटल पूर्णांक device_user_purge(काष्ठा dlm_user_proc *proc,
			     काष्ठा dlm_purge_params *params)
अणु
	काष्ठा dlm_ls *ls;
	पूर्णांक error;

	ls = dlm_find_lockspace_local(proc->lockspace);
	अगर (!ls)
		वापस -ENOENT;

	error = dlm_user_purge(ls, proc, params->nodeid, params->pid);

	dlm_put_lockspace(ls);
	वापस error;
पूर्ण

अटल पूर्णांक device_create_lockspace(काष्ठा dlm_lspace_params *params)
अणु
	dlm_lockspace_t *lockspace;
	काष्ठा dlm_ls *ls;
	पूर्णांक error;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	error = dlm_new_lockspace(params->name, dlm_config.ci_cluster_name, params->flags,
				  DLM_USER_LVB_LEN, शून्य, शून्य, शून्य,
				  &lockspace);
	अगर (error)
		वापस error;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -ENOENT;

	error = dlm_device_रेजिस्टर(ls, params->name);
	dlm_put_lockspace(ls);

	अगर (error)
		dlm_release_lockspace(lockspace, 0);
	अन्यथा
		error = ls->ls_device.minor;

	वापस error;
पूर्ण

अटल पूर्णांक device_हटाओ_lockspace(काष्ठा dlm_lspace_params *params)
अणु
	dlm_lockspace_t *lockspace;
	काष्ठा dlm_ls *ls;
	पूर्णांक error, क्रमce = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ls = dlm_find_lockspace_device(params->minor);
	अगर (!ls)
		वापस -ENOENT;

	अगर (params->flags & DLM_USER_LSFLG_FORCEFREE)
		क्रमce = 2;

	lockspace = ls->ls_local_handle;
	dlm_put_lockspace(ls);

	/* The final dlm_release_lockspace रुकोs क्रम references to go to
	   zero, so all processes will need to बंद their device क्रम the
	   ls beक्रमe the release will proceed.  release also calls the
	   device_deरेजिस्टर above.  Converting a positive वापस value
	   from release to zero means that userspace won't know when its
	   release was the final one, but it shouldn't need to know. */

	error = dlm_release_lockspace(lockspace, क्रमce);
	अगर (error > 0)
		error = 0;
	वापस error;
पूर्ण

/* Check the user's version matches ours */
अटल पूर्णांक check_version(काष्ठा dlm_ग_लिखो_request *req)
अणु
	अगर (req->version[0] != DLM_DEVICE_VERSION_MAJOR ||
	    (req->version[0] == DLM_DEVICE_VERSION_MAJOR &&
	     req->version[1] > DLM_DEVICE_VERSION_MINOR)) अणु

		prपूर्णांकk(KERN_DEBUG "dlm: process %s (%d) version mismatch "
		       "user (%d.%d.%d) kernel (%d.%d.%d)\n",
		       current->comm,
		       task_pid_nr(current),
		       req->version[0],
		       req->version[1],
		       req->version[2],
		       DLM_DEVICE_VERSION_MAJOR,
		       DLM_DEVICE_VERSION_MINOR,
		       DLM_DEVICE_VERSION_PATCH);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * device_ग_लिखो
 *
 *   device_user_lock
 *     dlm_user_request -> request_lock
 *     dlm_user_convert -> convert_lock
 *
 *   device_user_unlock
 *     dlm_user_unlock -> unlock_lock
 *     dlm_user_cancel -> cancel_lock
 *
 *   device_create_lockspace
 *     dlm_new_lockspace
 *
 *   device_हटाओ_lockspace
 *     dlm_release_lockspace
 */

/* a ग_लिखो to a lockspace device is a lock or unlock request, a ग_लिखो
   to the control device is to create/हटाओ a lockspace */

अटल sमाप_प्रकार device_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dlm_user_proc *proc = file->निजी_data;
	काष्ठा dlm_ग_लिखो_request *kbuf;
	पूर्णांक error;

#अगर_घोषित CONFIG_COMPAT
	अगर (count < माप(काष्ठा dlm_ग_लिखो_request32))
#अन्यथा
	अगर (count < माप(काष्ठा dlm_ग_लिखो_request))
#पूर्ण_अगर
		वापस -EINVAL;

	/*
	 * can't compare against COMPAT/dlm_ग_लिखो_request32 because
	 * we करोn't yet know अगर is64bit is zero
	 */
	अगर (count > माप(काष्ठा dlm_ग_लिखो_request) + DLM_RESNAME_MAXLEN)
		वापस -EINVAL;

	kbuf = memdup_user_nul(buf, count);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	अगर (check_version(kbuf)) अणु
		error = -EBADE;
		जाओ out_मुक्त;
	पूर्ण

#अगर_घोषित CONFIG_COMPAT
	अगर (!kbuf->is64bit) अणु
		काष्ठा dlm_ग_लिखो_request32 *k32buf;
		पूर्णांक namelen = 0;

		अगर (count > माप(काष्ठा dlm_ग_लिखो_request32))
			namelen = count - माप(काष्ठा dlm_ग_लिखो_request32);

		k32buf = (काष्ठा dlm_ग_लिखो_request32 *)kbuf;

		/* add 1 after namelen so that the name string is terminated */
		kbuf = kzalloc(माप(काष्ठा dlm_ग_लिखो_request) + namelen + 1,
			       GFP_NOFS);
		अगर (!kbuf) अणु
			kमुक्त(k32buf);
			वापस -ENOMEM;
		पूर्ण

		अगर (proc)
			set_bit(DLM_PROC_FLAGS_COMPAT, &proc->flags);

		compat_input(kbuf, k32buf, namelen);
		kमुक्त(k32buf);
	पूर्ण
#पूर्ण_अगर

	/* करो we really need this? can a ग_लिखो happen after a बंद? */
	अगर ((kbuf->cmd == DLM_USER_LOCK || kbuf->cmd == DLM_USER_UNLOCK) &&
	    (proc && test_bit(DLM_PROC_FLAGS_CLOSING, &proc->flags))) अणु
		error = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	error = -EINVAL;

	चयन (kbuf->cmd)
	अणु
	हाल DLM_USER_LOCK:
		अगर (!proc) अणु
			log_prपूर्णांक("no locking on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_user_lock(proc, &kbuf->i.lock);
		अवरोध;

	हाल DLM_USER_UNLOCK:
		अगर (!proc) अणु
			log_prपूर्णांक("no locking on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_user_unlock(proc, &kbuf->i.lock);
		अवरोध;

	हाल DLM_USER_DEADLOCK:
		अगर (!proc) अणु
			log_prपूर्णांक("no locking on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_user_deadlock(proc, &kbuf->i.lock);
		अवरोध;

	हाल DLM_USER_CREATE_LOCKSPACE:
		अगर (proc) अणु
			log_prपूर्णांक("create/remove only on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_create_lockspace(&kbuf->i.lspace);
		अवरोध;

	हाल DLM_USER_REMOVE_LOCKSPACE:
		अगर (proc) अणु
			log_prपूर्णांक("create/remove only on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_हटाओ_lockspace(&kbuf->i.lspace);
		अवरोध;

	हाल DLM_USER_PURGE:
		अगर (!proc) अणु
			log_prपूर्णांक("no locking on control device");
			जाओ out_मुक्त;
		पूर्ण
		error = device_user_purge(proc, &kbuf->i.purge);
		अवरोध;

	शेष:
		log_prपूर्णांक("Unknown command passed to DLM device : %d\n",
			  kbuf->cmd);
	पूर्ण

 out_मुक्त:
	kमुक्त(kbuf);
	वापस error;
पूर्ण

/* Every process that खोलोs the lockspace device has its own "proc" काष्ठाure
   hanging off the खोलो file that's used to keep track of locks owned by the
   process and asts that need to be delivered to the process. */

अटल पूर्णांक device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_user_proc *proc;
	काष्ठा dlm_ls *ls;

	ls = dlm_find_lockspace_device(iminor(inode));
	अगर (!ls)
		वापस -ENOENT;

	proc = kzalloc(माप(काष्ठा dlm_user_proc), GFP_NOFS);
	अगर (!proc) अणु
		dlm_put_lockspace(ls);
		वापस -ENOMEM;
	पूर्ण

	proc->lockspace = ls->ls_local_handle;
	INIT_LIST_HEAD(&proc->asts);
	INIT_LIST_HEAD(&proc->locks);
	INIT_LIST_HEAD(&proc->unlocking);
	spin_lock_init(&proc->asts_spin);
	spin_lock_init(&proc->locks_spin);
	init_रुकोqueue_head(&proc->रुको);
	file->निजी_data = proc;

	वापस 0;
पूर्ण

अटल पूर्णांक device_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dlm_user_proc *proc = file->निजी_data;
	काष्ठा dlm_ls *ls;

	ls = dlm_find_lockspace_local(proc->lockspace);
	अगर (!ls)
		वापस -ENOENT;

	set_bit(DLM_PROC_FLAGS_CLOSING, &proc->flags);

	dlm_clear_proc_locks(ls, proc);

	/* at this poपूर्णांक no more lkb's should exist क्रम this lockspace,
	   so there's no chance of dlm_user_add_ast() being called and
	   looking क्रम lkb->ua->proc */

	kमुक्त(proc);
	file->निजी_data = शून्य;

	dlm_put_lockspace(ls);
	dlm_put_lockspace(ls);  /* क्रम the find in device_खोलो() */

	/* FIXME: AUTOFREE: अगर this ls is no दीर्घer used करो
	   device_हटाओ_lockspace() */

	वापस 0;
पूर्ण

अटल पूर्णांक copy_result_to_user(काष्ठा dlm_user_args *ua, पूर्णांक compat,
			       uपूर्णांक32_t flags, पूर्णांक mode, पूर्णांक copy_lvb,
			       अक्षर __user *buf, माप_प्रकार count)
अणु
#अगर_घोषित CONFIG_COMPAT
	काष्ठा dlm_lock_result32 result32;
#पूर्ण_अगर
	काष्ठा dlm_lock_result result;
	व्योम *resultptr;
	पूर्णांक error=0;
	पूर्णांक len;
	पूर्णांक काष्ठा_len;

	स_रखो(&result, 0, माप(काष्ठा dlm_lock_result));
	result.version[0] = DLM_DEVICE_VERSION_MAJOR;
	result.version[1] = DLM_DEVICE_VERSION_MINOR;
	result.version[2] = DLM_DEVICE_VERSION_PATCH;
	स_नकल(&result.lksb, &ua->lksb, दुरत्व(काष्ठा dlm_lksb, sb_lvbptr));
	result.user_lksb = ua->user_lksb;

	/* FIXME: dlm1 provides क्रम the user's bastparam/addr to not be updated
	   in a conversion unless the conversion is successful.  See code
	   in dlm_user_convert() क्रम updating ua from ua_पंचांगp.  OpenVMS, though,
	   notes that a new blocking AST address and parameter are set even अगर
	   the conversion fails, so maybe we should just करो that. */

	अगर (flags & DLM_CB_BAST) अणु
		result.user_astaddr = ua->bastaddr;
		result.user_astparam = ua->bastparam;
		result.bast_mode = mode;
	पूर्ण अन्यथा अणु
		result.user_astaddr = ua->castaddr;
		result.user_astparam = ua->castparam;
	पूर्ण

#अगर_घोषित CONFIG_COMPAT
	अगर (compat)
		len = माप(काष्ठा dlm_lock_result32);
	अन्यथा
#पूर्ण_अगर
		len = माप(काष्ठा dlm_lock_result);
	काष्ठा_len = len;

	/* copy lvb to userspace अगर there is one, it's been updated, and
	   the user buffer has space क्रम it */

	अगर (copy_lvb && ua->lksb.sb_lvbptr && count >= len + DLM_USER_LVB_LEN) अणु
		अगर (copy_to_user(buf+len, ua->lksb.sb_lvbptr,
				 DLM_USER_LVB_LEN)) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण

		result.lvb_offset = len;
		len += DLM_USER_LVB_LEN;
	पूर्ण

	result.length = len;
	resultptr = &result;
#अगर_घोषित CONFIG_COMPAT
	अगर (compat) अणु
		compat_output(&result, &result32);
		resultptr = &result32;
	पूर्ण
#पूर्ण_अगर

	अगर (copy_to_user(buf, resultptr, काष्ठा_len))
		error = -EFAULT;
	अन्यथा
		error = len;
 out:
	वापस error;
पूर्ण

अटल पूर्णांक copy_version_to_user(अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा dlm_device_version ver;

	स_रखो(&ver, 0, माप(काष्ठा dlm_device_version));
	ver.version[0] = DLM_DEVICE_VERSION_MAJOR;
	ver.version[1] = DLM_DEVICE_VERSION_MINOR;
	ver.version[2] = DLM_DEVICE_VERSION_PATCH;

	अगर (copy_to_user(buf, &ver, माप(काष्ठा dlm_device_version)))
		वापस -EFAULT;
	वापस माप(काष्ठा dlm_device_version);
पूर्ण

/* a पढ़ो वापसs a single ast described in a काष्ठा dlm_lock_result */

अटल sमाप_प्रकार device_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			   loff_t *ppos)
अणु
	काष्ठा dlm_user_proc *proc = file->निजी_data;
	काष्ठा dlm_lkb *lkb;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा dlm_callback cb;
	पूर्णांक rv, resid, copy_lvb = 0;
	पूर्णांक old_mode, new_mode;

	अगर (count == माप(काष्ठा dlm_device_version)) अणु
		rv = copy_version_to_user(buf, count);
		वापस rv;
	पूर्ण

	अगर (!proc) अणु
		log_prपूर्णांक("non-version read from control device %zu", count);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_COMPAT
	अगर (count < माप(काष्ठा dlm_lock_result32))
#अन्यथा
	अगर (count < माप(काष्ठा dlm_lock_result))
#पूर्ण_अगर
		वापस -EINVAL;

 try_another:

	/* करो we really need this? can a पढ़ो happen after a बंद? */
	अगर (test_bit(DLM_PROC_FLAGS_CLOSING, &proc->flags))
		वापस -EINVAL;

	spin_lock(&proc->asts_spin);
	अगर (list_empty(&proc->asts)) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			spin_unlock(&proc->asts_spin);
			वापस -EAGAIN;
		पूर्ण

		add_रुको_queue(&proc->रुको, &रुको);

	repeat:
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (list_empty(&proc->asts) && !संकेत_pending(current)) अणु
			spin_unlock(&proc->asts_spin);
			schedule();
			spin_lock(&proc->asts_spin);
			जाओ repeat;
		पूर्ण
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&proc->रुको, &रुको);

		अगर (संकेत_pending(current)) अणु
			spin_unlock(&proc->asts_spin);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण

	/* अगर we empty lkb_callbacks, we करोn't want to unlock the spinlock
	   without removing lkb_cb_list; so empty lkb_cb_list is always
	   consistent with empty lkb_callbacks */

	lkb = list_entry(proc->asts.next, काष्ठा dlm_lkb, lkb_cb_list);

	/* rem_lkb_callback sets a new lkb_last_cast */
	old_mode = lkb->lkb_last_cast.mode;

	rv = dlm_rem_lkb_callback(lkb->lkb_resource->res_ls, lkb, &cb, &resid);
	अगर (rv < 0) अणु
		/* this shouldn't happen; lkb should have been हटाओd from
		   list when resid was zero */
		log_prपूर्णांक("dlm_rem_lkb_callback empty %x", lkb->lkb_id);
		list_del_init(&lkb->lkb_cb_list);
		spin_unlock(&proc->asts_spin);
		/* हटाओs ref क्रम proc->asts, may cause lkb to be मुक्तd */
		dlm_put_lkb(lkb);
		जाओ try_another;
	पूर्ण
	अगर (!resid)
		list_del_init(&lkb->lkb_cb_list);
	spin_unlock(&proc->asts_spin);

	अगर (cb.flags & DLM_CB_SKIP) अणु
		/* हटाओs ref क्रम proc->asts, may cause lkb to be मुक्तd */
		अगर (!resid)
			dlm_put_lkb(lkb);
		जाओ try_another;
	पूर्ण

	अगर (cb.flags & DLM_CB_CAST) अणु
		new_mode = cb.mode;

		अगर (!cb.sb_status && lkb->lkb_lksb->sb_lvbptr &&
		    dlm_lvb_operations[old_mode + 1][new_mode + 1])
			copy_lvb = 1;

		lkb->lkb_lksb->sb_status = cb.sb_status;
		lkb->lkb_lksb->sb_flags = cb.sb_flags;
	पूर्ण

	rv = copy_result_to_user(lkb->lkb_ua,
				 test_bit(DLM_PROC_FLAGS_COMPAT, &proc->flags),
				 cb.flags, cb.mode, copy_lvb, buf, count);

	/* हटाओs ref क्रम proc->asts, may cause lkb to be मुक्तd */
	अगर (!resid)
		dlm_put_lkb(lkb);

	वापस rv;
पूर्ण

अटल __poll_t device_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dlm_user_proc *proc = file->निजी_data;

	poll_रुको(file, &proc->रुको, रुको);

	spin_lock(&proc->asts_spin);
	अगर (!list_empty(&proc->asts)) अणु
		spin_unlock(&proc->asts_spin);
		वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण
	spin_unlock(&proc->asts_spin);
	वापस 0;
पूर्ण

पूर्णांक dlm_user_daemon_available(व्योम)
अणु
	/* dlm_controld hasn't started (or, has started, but not
	   properly populated configfs) */

	अगर (!dlm_our_nodeid())
		वापस 0;

	/* This is to deal with versions of dlm_controld that करोn't
	   know about the monitor device.  We assume that अगर the
	   dlm_controld was started (above), but the monitor device
	   was never खोलोed, that it's an old version.  dlm_controld
	   should खोलो the monitor device beक्रमe populating configfs. */

	अगर (dlm_monitor_unused)
		वापस 1;

	वापस atomic_पढ़ो(&dlm_monitor_खोलोed) ? 1 : 0;
पूर्ण

अटल पूर्णांक ctl_device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक ctl_device_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक monitor_device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_inc(&dlm_monitor_खोलोed);
	dlm_monitor_unused = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक monitor_device_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (atomic_dec_and_test(&dlm_monitor_खोलोed))
		dlm_stop_lockspaces();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations device_fops = अणु
	.खोलो    = device_खोलो,
	.release = device_बंद,
	.पढ़ो    = device_पढ़ो,
	.ग_लिखो   = device_ग_लिखो,
	.poll    = device_poll,
	.owner   = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations ctl_device_fops = अणु
	.खोलो    = ctl_device_खोलो,
	.release = ctl_device_बंद,
	.पढ़ो    = device_पढ़ो,
	.ग_लिखो   = device_ग_लिखो,
	.owner   = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice ctl_device = अणु
	.name  = "dlm-control",
	.fops  = &ctl_device_fops,
	.minor = MISC_DYNAMIC_MINOR,
पूर्ण;

अटल स्थिर काष्ठा file_operations monitor_device_fops = अणु
	.खोलो    = monitor_device_खोलो,
	.release = monitor_device_बंद,
	.owner   = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice monitor_device = अणु
	.name  = "dlm-monitor",
	.fops  = &monitor_device_fops,
	.minor = MISC_DYNAMIC_MINOR,
पूर्ण;

पूर्णांक __init dlm_user_init(व्योम)
अणु
	पूर्णांक error;

	atomic_set(&dlm_monitor_खोलोed, 0);

	error = misc_रेजिस्टर(&ctl_device);
	अगर (error) अणु
		log_prपूर्णांक("misc_register failed for control device");
		जाओ out;
	पूर्ण

	error = misc_रेजिस्टर(&monitor_device);
	अगर (error) अणु
		log_prपूर्णांक("misc_register failed for monitor device");
		misc_deरेजिस्टर(&ctl_device);
	पूर्ण
 out:
	वापस error;
पूर्ण

व्योम dlm_user_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&ctl_device);
	misc_deरेजिस्टर(&monitor_device);
पूर्ण

