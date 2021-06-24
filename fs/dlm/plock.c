<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2008 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/dlm.h>
#समावेश <linux/dlm_plock.h>
#समावेश <linux/slab.h>

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"

अटल spinlock_t ops_lock;
अटल काष्ठा list_head send_list;
अटल काष्ठा list_head recv_list;
अटल रुको_queue_head_t send_wq;
अटल रुको_queue_head_t recv_wq;

काष्ठा plock_op अणु
	काष्ठा list_head list;
	पूर्णांक करोne;
	काष्ठा dlm_plock_info info;
पूर्ण;

काष्ठा plock_xop अणु
	काष्ठा plock_op xop;
	पूर्णांक (*callback)(काष्ठा file_lock *fl, पूर्णांक result);
	व्योम *fl;
	व्योम *file;
	काष्ठा file_lock flc;
पूर्ण;


अटल अंतरभूत व्योम set_version(काष्ठा dlm_plock_info *info)
अणु
	info->version[0] = DLM_PLOCK_VERSION_MAJOR;
	info->version[1] = DLM_PLOCK_VERSION_MINOR;
	info->version[2] = DLM_PLOCK_VERSION_PATCH;
पूर्ण

अटल पूर्णांक check_version(काष्ठा dlm_plock_info *info)
अणु
	अगर ((DLM_PLOCK_VERSION_MAJOR != info->version[0]) ||
	    (DLM_PLOCK_VERSION_MINOR < info->version[1])) अणु
		log_prपूर्णांक("plock device version mismatch: "
			  "kernel (%u.%u.%u), user (%u.%u.%u)",
			  DLM_PLOCK_VERSION_MAJOR,
			  DLM_PLOCK_VERSION_MINOR,
			  DLM_PLOCK_VERSION_PATCH,
			  info->version[0],
			  info->version[1],
			  info->version[2]);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम send_op(काष्ठा plock_op *op)
अणु
	set_version(&op->info);
	INIT_LIST_HEAD(&op->list);
	spin_lock(&ops_lock);
	list_add_tail(&op->list, &send_list);
	spin_unlock(&ops_lock);
	wake_up(&send_wq);
पूर्ण

/* If a process was समाप्तed जबतक रुकोing क्रम the only plock on a file,
   locks_हटाओ_posix will not see any lock on the file so it won't
   send an unlock-बंद to us to pass on to userspace to clean up the
   abanकरोned रुकोer.  So, we have to insert the unlock-बंद when the
   lock call is पूर्णांकerrupted. */

अटल व्योम करो_unlock_बंद(काष्ठा dlm_ls *ls, u64 number,
			    काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा plock_op *op;

	op = kzalloc(माप(*op), GFP_NOFS);
	अगर (!op)
		वापस;

	op->info.optype		= DLM_PLOCK_OP_UNLOCK;
	op->info.pid		= fl->fl_pid;
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= 0;
	op->info.end		= OFFSET_MAX;
	अगर (fl->fl_lmops && fl->fl_lmops->lm_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	अन्यथा
		op->info.owner	= (__u64)(दीर्घ) fl->fl_owner;

	op->info.flags |= DLM_PLOCK_FL_CLOSE;
	send_op(op);
पूर्ण

पूर्णांक dlm_posix_lock(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		   पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा plock_op *op;
	काष्ठा plock_xop *xop;
	पूर्णांक rv;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;

	xop = kzalloc(माप(*xop), GFP_NOFS);
	अगर (!xop) अणु
		rv = -ENOMEM;
		जाओ out;
	पूर्ण

	op = &xop->xop;
	op->info.optype		= DLM_PLOCK_OP_LOCK;
	op->info.pid		= fl->fl_pid;
	op->info.ex		= (fl->fl_type == F_WRLCK);
	op->info.रुको		= IS_SETLKW(cmd);
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	अगर (fl->fl_lmops && fl->fl_lmops->lm_grant) अणु
		/* fl_owner is lockd which करोesn't distinguish
		   processes on the nfs client */
		op->info.owner	= (__u64) fl->fl_pid;
		xop->callback	= fl->fl_lmops->lm_grant;
		locks_init_lock(&xop->flc);
		locks_copy_lock(&xop->flc, fl);
		xop->fl		= fl;
		xop->file	= file;
	पूर्ण अन्यथा अणु
		op->info.owner	= (__u64)(दीर्घ) fl->fl_owner;
		xop->callback	= शून्य;
	पूर्ण

	send_op(op);

	अगर (xop->callback == शून्य) अणु
		rv = रुको_event_पूर्णांकerruptible(recv_wq, (op->करोne != 0));
		अगर (rv == -ERESTARTSYS) अणु
			log_debug(ls, "dlm_posix_lock: wait killed %llx",
				  (अचिन्हित दीर्घ दीर्घ)number);
			spin_lock(&ops_lock);
			list_del(&op->list);
			spin_unlock(&ops_lock);
			kमुक्त(xop);
			करो_unlock_बंद(ls, number, file, fl);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		rv = खाता_LOCK_DEFERRED;
		जाओ out;
	पूर्ण

	spin_lock(&ops_lock);
	अगर (!list_empty(&op->list)) अणु
		log_error(ls, "dlm_posix_lock: op on list %llx",
			  (अचिन्हित दीर्घ दीर्घ)number);
		list_del(&op->list);
	पूर्ण
	spin_unlock(&ops_lock);

	rv = op->info.rv;

	अगर (!rv) अणु
		अगर (locks_lock_file_रुको(file, fl) < 0)
			log_error(ls, "dlm_posix_lock: vfs lock error %llx",
				  (अचिन्हित दीर्घ दीर्घ)number);
	पूर्ण

	kमुक्त(xop);
out:
	dlm_put_lockspace(ls);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(dlm_posix_lock);

/* Returns failure अगरf a successful lock operation should be canceled */
अटल पूर्णांक dlm_plock_callback(काष्ठा plock_op *op)
अणु
	काष्ठा file *file;
	काष्ठा file_lock *fl;
	काष्ठा file_lock *flc;
	पूर्णांक (*notअगरy)(काष्ठा file_lock *fl, पूर्णांक result) = शून्य;
	काष्ठा plock_xop *xop = (काष्ठा plock_xop *)op;
	पूर्णांक rv = 0;

	spin_lock(&ops_lock);
	अगर (!list_empty(&op->list)) अणु
		log_prपूर्णांक("dlm_plock_callback: op on list %llx",
			  (अचिन्हित दीर्घ दीर्घ)op->info.number);
		list_del(&op->list);
	पूर्ण
	spin_unlock(&ops_lock);

	/* check अगर the following 2 are still valid or make a copy */
	file = xop->file;
	flc = &xop->flc;
	fl = xop->fl;
	notअगरy = xop->callback;

	अगर (op->info.rv) अणु
		notअगरy(fl, op->info.rv);
		जाओ out;
	पूर्ण

	/* got fs lock; bookkeep locally as well: */
	flc->fl_flags &= ~FL_SLEEP;
	अगर (posix_lock_file(file, flc, शून्य)) अणु
		/*
		 * This can only happen in the हाल of kदो_स्मृति() failure.
		 * The fileप्रणाली's own lock is the authoritative lock,
		 * so a failure to get the lock locally is not a disaster.
		 * As दीर्घ as the fs cannot reliably cancel locks (especially
		 * in a low-memory situation), we're better off ignoring
		 * this failure than trying to recover.
		 */
		log_prपूर्णांक("dlm_plock_callback: vfs lock error %llx file %p fl %p",
			  (अचिन्हित दीर्घ दीर्घ)op->info.number, file, fl);
	पूर्ण

	rv = notअगरy(fl, 0);
	अगर (rv) अणु
		/* XXX: We need to cancel the fs lock here: */
		log_prपूर्णांक("dlm_plock_callback: lock granted after lock request "
			  "failed; dangling lock!\n");
		जाओ out;
	पूर्ण

out:
	kमुक्त(xop);
	वापस rv;
पूर्ण

पूर्णांक dlm_posix_unlock(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		     काष्ठा file_lock *fl)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा plock_op *op;
	पूर्णांक rv;
	अचिन्हित अक्षर fl_flags = fl->fl_flags;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;

	op = kzalloc(माप(*op), GFP_NOFS);
	अगर (!op) अणु
		rv = -ENOMEM;
		जाओ out;
	पूर्ण

	/* cause the vfs unlock to वापस ENOENT अगर lock is not found */
	fl->fl_flags |= FL_EXISTS;

	rv = locks_lock_file_रुको(file, fl);
	अगर (rv == -ENOENT) अणु
		rv = 0;
		जाओ out_मुक्त;
	पूर्ण
	अगर (rv < 0) अणु
		log_error(ls, "dlm_posix_unlock: vfs unlock error %d %llx",
			  rv, (अचिन्हित दीर्घ दीर्घ)number);
	पूर्ण

	op->info.optype		= DLM_PLOCK_OP_UNLOCK;
	op->info.pid		= fl->fl_pid;
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	अगर (fl->fl_lmops && fl->fl_lmops->lm_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	अन्यथा
		op->info.owner	= (__u64)(दीर्घ) fl->fl_owner;

	अगर (fl->fl_flags & FL_CLOSE) अणु
		op->info.flags |= DLM_PLOCK_FL_CLOSE;
		send_op(op);
		rv = 0;
		जाओ out;
	पूर्ण

	send_op(op);
	रुको_event(recv_wq, (op->करोne != 0));

	spin_lock(&ops_lock);
	अगर (!list_empty(&op->list)) अणु
		log_error(ls, "dlm_posix_unlock: op on list %llx",
			  (अचिन्हित दीर्घ दीर्घ)number);
		list_del(&op->list);
	पूर्ण
	spin_unlock(&ops_lock);

	rv = op->info.rv;

	अगर (rv == -ENOENT)
		rv = 0;

out_मुक्त:
	kमुक्त(op);
out:
	dlm_put_lockspace(ls);
	fl->fl_flags = fl_flags;
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(dlm_posix_unlock);

पूर्णांक dlm_posix_get(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		  काष्ठा file_lock *fl)
अणु
	काष्ठा dlm_ls *ls;
	काष्ठा plock_op *op;
	पूर्णांक rv;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;

	op = kzalloc(माप(*op), GFP_NOFS);
	अगर (!op) अणु
		rv = -ENOMEM;
		जाओ out;
	पूर्ण

	op->info.optype		= DLM_PLOCK_OP_GET;
	op->info.pid		= fl->fl_pid;
	op->info.ex		= (fl->fl_type == F_WRLCK);
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	अगर (fl->fl_lmops && fl->fl_lmops->lm_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	अन्यथा
		op->info.owner	= (__u64)(दीर्घ) fl->fl_owner;

	send_op(op);
	रुको_event(recv_wq, (op->करोne != 0));

	spin_lock(&ops_lock);
	अगर (!list_empty(&op->list)) अणु
		log_error(ls, "dlm_posix_get: op on list %llx",
			  (अचिन्हित दीर्घ दीर्घ)number);
		list_del(&op->list);
	पूर्ण
	spin_unlock(&ops_lock);

	/* info.rv from userspace is 1 क्रम conflict, 0 क्रम no-conflict,
	   -ENOENT अगर there are no locks on the file */

	rv = op->info.rv;

	fl->fl_type = F_UNLCK;
	अगर (rv == -ENOENT)
		rv = 0;
	अन्यथा अगर (rv > 0) अणु
		locks_init_lock(fl);
		fl->fl_type = (op->info.ex) ? F_WRLCK : F_RDLCK;
		fl->fl_flags = FL_POSIX;
		fl->fl_pid = -op->info.pid;
		fl->fl_start = op->info.start;
		fl->fl_end = op->info.end;
		rv = 0;
	पूर्ण

	kमुक्त(op);
out:
	dlm_put_lockspace(ls);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(dlm_posix_get);

/* a पढ़ो copies out one plock request from the send list */
अटल sमाप_प्रकार dev_पढ़ो(काष्ठा file *file, अक्षर __user *u, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा dlm_plock_info info;
	काष्ठा plock_op *op = शून्य;

	अगर (count < माप(info))
		वापस -EINVAL;

	spin_lock(&ops_lock);
	अगर (!list_empty(&send_list)) अणु
		op = list_entry(send_list.next, काष्ठा plock_op, list);
		अगर (op->info.flags & DLM_PLOCK_FL_CLOSE)
			list_del(&op->list);
		अन्यथा
			list_move(&op->list, &recv_list);
		स_नकल(&info, &op->info, माप(info));
	पूर्ण
	spin_unlock(&ops_lock);

	अगर (!op)
		वापस -EAGAIN;

	/* there is no need to get a reply from userspace क्रम unlocks
	   that were generated by the vfs cleaning up क्रम a बंद
	   (the process did not make an unlock call). */

	अगर (op->info.flags & DLM_PLOCK_FL_CLOSE)
		kमुक्त(op);

	अगर (copy_to_user(u, &info, माप(info)))
		वापस -EFAULT;
	वापस माप(info);
पूर्ण

/* a ग_लिखो copies in one plock result that should match a plock_op
   on the recv list */
अटल sमाप_प्रकार dev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *u, माप_प्रकार count,
			 loff_t *ppos)
अणु
	काष्ठा dlm_plock_info info;
	काष्ठा plock_op *op;
	पूर्णांक found = 0, करो_callback = 0;

	अगर (count != माप(info))
		वापस -EINVAL;

	अगर (copy_from_user(&info, u, माप(info)))
		वापस -EFAULT;

	अगर (check_version(&info))
		वापस -EINVAL;

	spin_lock(&ops_lock);
	list_क्रम_each_entry(op, &recv_list, list) अणु
		अगर (op->info.fsid == info.fsid &&
		    op->info.number == info.number &&
		    op->info.owner == info.owner) अणु
			काष्ठा plock_xop *xop = (काष्ठा plock_xop *)op;
			list_del_init(&op->list);
			स_नकल(&op->info, &info, माप(info));
			अगर (xop->callback)
				करो_callback = 1;
			अन्यथा
				op->करोne = 1;
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&ops_lock);

	अगर (found) अणु
		अगर (करो_callback)
			dlm_plock_callback(op);
		अन्यथा
			wake_up(&recv_wq);
	पूर्ण अन्यथा
		log_prपूर्णांक("dev_write no op %x %llx", info.fsid,
			  (अचिन्हित दीर्घ दीर्घ)info.number);
	वापस count;
पूर्ण

अटल __poll_t dev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;

	poll_रुको(file, &send_wq, रुको);

	spin_lock(&ops_lock);
	अगर (!list_empty(&send_list))
		mask = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&ops_lock);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations dev_fops = अणु
	.पढ़ो    = dev_पढ़ो,
	.ग_लिखो   = dev_ग_लिखो,
	.poll    = dev_poll,
	.owner   = THIS_MODULE,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice plock_dev_misc = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = DLM_PLOCK_MISC_NAME,
	.fops = &dev_fops
पूर्ण;

पूर्णांक dlm_plock_init(व्योम)
अणु
	पूर्णांक rv;

	spin_lock_init(&ops_lock);
	INIT_LIST_HEAD(&send_list);
	INIT_LIST_HEAD(&recv_list);
	init_रुकोqueue_head(&send_wq);
	init_रुकोqueue_head(&recv_wq);

	rv = misc_रेजिस्टर(&plock_dev_misc);
	अगर (rv)
		log_prपूर्णांक("dlm_plock_init: misc_register failed %d", rv);
	वापस rv;
पूर्ण

व्योम dlm_plock_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&plock_dev_misc);
पूर्ण

