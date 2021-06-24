<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/ipc/msg.c
 * Copyright (C) 1992 Krishna Balasubramanian
 *
 * Removed all the reमुख्यing kerneld mess
 * Catch the -EFAULT stuff properly
 * Use GFP_KERNEL क्रम messages as in 1.2
 * Fixed up the unchecked user space derefs
 * Copyright (C) 1998 Alan Cox & Andi Kleen
 *
 * /proc/sysvipc/msg support (c) 1999 Dragos Acostachioaie <dragos@iname.com>
 *
 * mostly rewritten, thपढ़ोed and wake-one semantics added
 * MSGMAX limit हटाओd, sysctl's added
 * (c) 1999 Manfred Spraul <manfred@colorfullअगरe.com>
 *
 * support क्रम audit of ipc object properties and permission changes
 * Dustin Kirkland <dustin.kirkland@us.ibm.com>
 *
 * namespaces support
 * OpenVZ, SWsoft Inc.
 * Pavel Emelianov <xemul@खोलोvz.org>
 */

#समावेश <linux/capability.h>
#समावेश <linux/msg.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/list.h>
#समावेश <linux/security.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/audit.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/rhashtable.h>

#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>
#समावेश "util.h"

/* one msq_queue काष्ठाure क्रम each present queue on the प्रणाली */
काष्ठा msg_queue अणु
	काष्ठा kern_ipc_perm q_perm;
	समय64_t q_sसमय;		/* last msgsnd समय */
	समय64_t q_rसमय;		/* last msgrcv समय */
	समय64_t q_स_समय;		/* last change समय */
	अचिन्हित दीर्घ q_cbytes;		/* current number of bytes on queue */
	अचिन्हित दीर्घ q_qnum;		/* number of messages in queue */
	अचिन्हित दीर्घ q_qbytes;		/* max number of bytes on queue */
	काष्ठा pid *q_lspid;		/* pid of last msgsnd */
	काष्ठा pid *q_lrpid;		/* last receive pid */

	काष्ठा list_head q_messages;
	काष्ठा list_head q_receivers;
	काष्ठा list_head q_senders;
पूर्ण __अक्रमomize_layout;

/*
 * MSG_BARRIER Locking:
 *
 * Similar to the optimization used in ipc/mqueue.c, one syscall वापस path
 * करोes not acquire any locks when it sees that a message exists in
 * msg_receiver.r_msg. Thereक्रमe r_msg is set using smp_store_release()
 * and accessed using READ_ONCE()+smp_acquire__after_ctrl_dep(). In addition,
 * wake_q_add_safe() is used. See ipc/mqueue.c क्रम more details
 */

/* one msg_receiver काष्ठाure क्रम each sleeping receiver */
काष्ठा msg_receiver अणु
	काष्ठा list_head	r_list;
	काष्ठा task_काष्ठा	*r_tsk;

	पूर्णांक			r_mode;
	दीर्घ			r_msgtype;
	दीर्घ			r_maxsize;

	काष्ठा msg_msg		*r_msg;
पूर्ण;

/* one msg_sender क्रम each sleeping sender */
काष्ठा msg_sender अणु
	काष्ठा list_head	list;
	काष्ठा task_काष्ठा	*tsk;
	माप_प्रकार                  msgsz;
पूर्ण;

#घोषणा SEARCH_ANY		1
#घोषणा SEARCH_EQUAL		2
#घोषणा SEARCH_NOTEQUAL		3
#घोषणा SEARCH_LESSEQUAL	4
#घोषणा SEARCH_NUMBER		5

#घोषणा msg_ids(ns)	((ns)->ids[IPC_MSG_IDS])

अटल अंतरभूत काष्ठा msg_queue *msq_obtain_object(काष्ठा ipc_namespace *ns, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_idr(&msg_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा msg_queue, q_perm);
पूर्ण

अटल अंतरभूत काष्ठा msg_queue *msq_obtain_object_check(काष्ठा ipc_namespace *ns,
							पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_check(&msg_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा msg_queue, q_perm);
पूर्ण

अटल अंतरभूत व्योम msg_rmid(काष्ठा ipc_namespace *ns, काष्ठा msg_queue *s)
अणु
	ipc_rmid(&msg_ids(ns), &s->q_perm);
पूर्ण

अटल व्योम msg_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा kern_ipc_perm *p = container_of(head, काष्ठा kern_ipc_perm, rcu);
	काष्ठा msg_queue *msq = container_of(p, काष्ठा msg_queue, q_perm);

	security_msg_queue_मुक्त(&msq->q_perm);
	kvमुक्त(msq);
पूर्ण

/**
 * newque - Create a new msg queue
 * @ns: namespace
 * @params: ptr to the काष्ठाure that contains the key and msgflg
 *
 * Called with msg_ids.rwsem held (ग_लिखोr)
 */
अटल पूर्णांक newque(काष्ठा ipc_namespace *ns, काष्ठा ipc_params *params)
अणु
	काष्ठा msg_queue *msq;
	पूर्णांक retval;
	key_t key = params->key;
	पूर्णांक msgflg = params->flg;

	msq = kvदो_स्मृति(माप(*msq), GFP_KERNEL);
	अगर (unlikely(!msq))
		वापस -ENOMEM;

	msq->q_perm.mode = msgflg & S_IRWXUGO;
	msq->q_perm.key = key;

	msq->q_perm.security = शून्य;
	retval = security_msg_queue_alloc(&msq->q_perm);
	अगर (retval) अणु
		kvमुक्त(msq);
		वापस retval;
	पूर्ण

	msq->q_sसमय = msq->q_rसमय = 0;
	msq->q_स_समय = kसमय_get_real_seconds();
	msq->q_cbytes = msq->q_qnum = 0;
	msq->q_qbytes = ns->msg_ctlmnb;
	msq->q_lspid = msq->q_lrpid = शून्य;
	INIT_LIST_HEAD(&msq->q_messages);
	INIT_LIST_HEAD(&msq->q_receivers);
	INIT_LIST_HEAD(&msq->q_senders);

	/* ipc_addid() locks msq upon success. */
	retval = ipc_addid(&msg_ids(ns), &msq->q_perm, ns->msg_ctlmni);
	अगर (retval < 0) अणु
		ipc_rcu_putref(&msq->q_perm, msg_rcu_मुक्त);
		वापस retval;
	पूर्ण

	ipc_unlock_object(&msq->q_perm);
	rcu_पढ़ो_unlock();

	वापस msq->q_perm.id;
पूर्ण

अटल अंतरभूत bool msg_fits_inqueue(काष्ठा msg_queue *msq, माप_प्रकार msgsz)
अणु
	वापस msgsz + msq->q_cbytes <= msq->q_qbytes &&
		1 + msq->q_qnum <= msq->q_qbytes;
पूर्ण

अटल अंतरभूत व्योम ss_add(काष्ठा msg_queue *msq,
			  काष्ठा msg_sender *mss, माप_प्रकार msgsz)
अणु
	mss->tsk = current;
	mss->msgsz = msgsz;
	/*
	 * No memory barrier required: we did ipc_lock_object(),
	 * and the waker obtains that lock beक्रमe calling wake_q_add().
	 */
	__set_current_state(TASK_INTERRUPTIBLE);
	list_add_tail(&mss->list, &msq->q_senders);
पूर्ण

अटल अंतरभूत व्योम ss_del(काष्ठा msg_sender *mss)
अणु
	अगर (mss->list.next)
		list_del(&mss->list);
पूर्ण

अटल व्योम ss_wakeup(काष्ठा msg_queue *msq,
		      काष्ठा wake_q_head *wake_q, bool समाप्त)
अणु
	काष्ठा msg_sender *mss, *t;
	काष्ठा task_काष्ठा *stop_tsk = शून्य;
	काष्ठा list_head *h = &msq->q_senders;

	list_क्रम_each_entry_safe(mss, t, h, list) अणु
		अगर (समाप्त)
			mss->list.next = शून्य;

		/*
		 * Stop at the first task we करोn't wakeup,
		 * we've alपढ़ोy iterated the original
		 * sender queue.
		 */
		अन्यथा अगर (stop_tsk == mss->tsk)
			अवरोध;
		/*
		 * We are not in an EIDRM scenario here, thereक्रमe
		 * verअगरy that we really need to wakeup the task.
		 * To मुख्यtain current semantics and wakeup order,
		 * move the sender to the tail on behalf of the
		 * blocked task.
		 */
		अन्यथा अगर (!msg_fits_inqueue(msq, mss->msgsz)) अणु
			अगर (!stop_tsk)
				stop_tsk = mss->tsk;

			list_move_tail(&mss->list, &msq->q_senders);
			जारी;
		पूर्ण

		wake_q_add(wake_q, mss->tsk);
	पूर्ण
पूर्ण

अटल व्योम expunge_all(काष्ठा msg_queue *msq, पूर्णांक res,
			काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा msg_receiver *msr, *t;

	list_क्रम_each_entry_safe(msr, t, &msq->q_receivers, r_list) अणु
		काष्ठा task_काष्ठा *r_tsk;

		r_tsk = get_task_काष्ठा(msr->r_tsk);

		/* see MSG_BARRIER क्रम purpose/pairing */
		smp_store_release(&msr->r_msg, ERR_PTR(res));
		wake_q_add_safe(wake_q, r_tsk);
	पूर्ण
पूर्ण

/*
 * मुक्तque() wakes up रुकोers on the sender and receiver रुकोing queue,
 * हटाओs the message queue from message queue ID IDR, and cleans up all the
 * messages associated with this queue.
 *
 * msg_ids.rwsem (ग_लिखोr) and the spinlock क्रम this message queue are held
 * beक्रमe मुक्तque() is called. msg_ids.rwsem reमुख्यs locked on निकास.
 */
अटल व्योम मुक्तque(काष्ठा ipc_namespace *ns, काष्ठा kern_ipc_perm *ipcp)
	__releases(RCU)
	__releases(&msq->q_perm)
अणु
	काष्ठा msg_msg *msg, *t;
	काष्ठा msg_queue *msq = container_of(ipcp, काष्ठा msg_queue, q_perm);
	DEFINE_WAKE_Q(wake_q);

	expunge_all(msq, -EIDRM, &wake_q);
	ss_wakeup(msq, &wake_q, true);
	msg_rmid(ns, msq);
	ipc_unlock_object(&msq->q_perm);
	wake_up_q(&wake_q);
	rcu_पढ़ो_unlock();

	list_क्रम_each_entry_safe(msg, t, &msq->q_messages, m_list) अणु
		atomic_dec(&ns->msg_hdrs);
		मुक्त_msg(msg);
	पूर्ण
	atomic_sub(msq->q_cbytes, &ns->msg_bytes);
	ipc_update_pid(&msq->q_lspid, शून्य);
	ipc_update_pid(&msq->q_lrpid, शून्य);
	ipc_rcu_putref(&msq->q_perm, msg_rcu_मुक्त);
पूर्ण

दीर्घ ksys_msgget(key_t key, पूर्णांक msgflg)
अणु
	काष्ठा ipc_namespace *ns;
	अटल स्थिर काष्ठा ipc_ops msg_ops = अणु
		.getnew = newque,
		.associate = security_msg_queue_associate,
	पूर्ण;
	काष्ठा ipc_params msg_params;

	ns = current->nsproxy->ipc_ns;

	msg_params.key = key;
	msg_params.flg = msgflg;

	वापस ipcget(ns, &msg_ids(ns), &msg_ops, &msg_params);
पूर्ण

SYSCALL_DEFINE2(msgget, key_t, key, पूर्णांक, msgflg)
अणु
	वापस ksys_msgget(key, msgflg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_msqid_to_user(व्योम __user *buf, काष्ठा msqid64_ds *in, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		वापस copy_to_user(buf, in, माप(*in));
	हाल IPC_OLD:
	अणु
		काष्ठा msqid_ds out;

		स_रखो(&out, 0, माप(out));

		ipc64_perm_to_ipc_perm(&in->msg_perm, &out.msg_perm);

		out.msg_sसमय		= in->msg_sसमय;
		out.msg_rसमय		= in->msg_rसमय;
		out.msg_स_समय		= in->msg_स_समय;

		अगर (in->msg_cbytes > अच_लघु_उच्च)
			out.msg_cbytes	= अच_लघु_उच्च;
		अन्यथा
			out.msg_cbytes	= in->msg_cbytes;
		out.msg_lcbytes		= in->msg_cbytes;

		अगर (in->msg_qnum > अच_लघु_उच्च)
			out.msg_qnum	= अच_लघु_उच्च;
		अन्यथा
			out.msg_qnum	= in->msg_qnum;

		अगर (in->msg_qbytes > अच_लघु_उच्च)
			out.msg_qbytes	= अच_लघु_उच्च;
		अन्यथा
			out.msg_qbytes	= in->msg_qbytes;
		out.msg_lqbytes		= in->msg_qbytes;

		out.msg_lspid		= in->msg_lspid;
		out.msg_lrpid		= in->msg_lrpid;

		वापस copy_to_user(buf, &out, माप(out));
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_msqid_from_user(काष्ठा msqid64_ds *out, व्योम __user *buf, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		अगर (copy_from_user(out, buf, माप(*out)))
			वापस -EFAULT;
		वापस 0;
	हाल IPC_OLD:
	अणु
		काष्ठा msqid_ds tbuf_old;

		अगर (copy_from_user(&tbuf_old, buf, माप(tbuf_old)))
			वापस -EFAULT;

		out->msg_perm.uid	= tbuf_old.msg_perm.uid;
		out->msg_perm.gid	= tbuf_old.msg_perm.gid;
		out->msg_perm.mode	= tbuf_old.msg_perm.mode;

		अगर (tbuf_old.msg_qbytes == 0)
			out->msg_qbytes	= tbuf_old.msg_lqbytes;
		अन्यथा
			out->msg_qbytes	= tbuf_old.msg_qbytes;

		वापस 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * This function handles some msgctl commands which require the rwsem
 * to be held in ग_लिखो mode.
 * NOTE: no locks must be held, the rwsem is taken inside this function.
 */
अटल पूर्णांक msgctl_करोwn(काष्ठा ipc_namespace *ns, पूर्णांक msqid, पूर्णांक cmd,
			काष्ठा ipc64_perm *perm, पूर्णांक msg_qbytes)
अणु
	काष्ठा kern_ipc_perm *ipcp;
	काष्ठा msg_queue *msq;
	पूर्णांक err;

	करोwn_ग_लिखो(&msg_ids(ns).rwsem);
	rcu_पढ़ो_lock();

	ipcp = ipcctl_obtain_check(ns, &msg_ids(ns), msqid, cmd,
				      perm, msg_qbytes);
	अगर (IS_ERR(ipcp)) अणु
		err = PTR_ERR(ipcp);
		जाओ out_unlock1;
	पूर्ण

	msq = container_of(ipcp, काष्ठा msg_queue, q_perm);

	err = security_msg_queue_msgctl(&msq->q_perm, cmd);
	अगर (err)
		जाओ out_unlock1;

	चयन (cmd) अणु
	हाल IPC_RMID:
		ipc_lock_object(&msq->q_perm);
		/* मुक्तque unlocks the ipc object and rcu */
		मुक्तque(ns, ipcp);
		जाओ out_up;
	हाल IPC_SET:
	अणु
		DEFINE_WAKE_Q(wake_q);

		अगर (msg_qbytes > ns->msg_ctlmnb &&
		    !capable(CAP_SYS_RESOURCE)) अणु
			err = -EPERM;
			जाओ out_unlock1;
		पूर्ण

		ipc_lock_object(&msq->q_perm);
		err = ipc_update_perm(perm, ipcp);
		अगर (err)
			जाओ out_unlock0;

		msq->q_qbytes = msg_qbytes;

		msq->q_स_समय = kसमय_get_real_seconds();
		/*
		 * Sleeping receivers might be excluded by
		 * stricter permissions.
		 */
		expunge_all(msq, -EAGAIN, &wake_q);
		/*
		 * Sleeping senders might be able to send
		 * due to a larger queue size.
		 */
		ss_wakeup(msq, &wake_q, false);
		ipc_unlock_object(&msq->q_perm);
		wake_up_q(&wake_q);

		जाओ out_unlock1;
	पूर्ण
	शेष:
		err = -EINVAL;
		जाओ out_unlock1;
	पूर्ण

out_unlock0:
	ipc_unlock_object(&msq->q_perm);
out_unlock1:
	rcu_पढ़ो_unlock();
out_up:
	up_ग_लिखो(&msg_ids(ns).rwsem);
	वापस err;
पूर्ण

अटल पूर्णांक msgctl_info(काष्ठा ipc_namespace *ns, पूर्णांक msqid,
			 पूर्णांक cmd, काष्ठा msginfo *msginfo)
अणु
	पूर्णांक err;
	पूर्णांक max_idx;

	/*
	 * We must not वापस kernel stack data.
	 * due to padding, it's not enough
	 * to set all member fields.
	 */
	err = security_msg_queue_msgctl(शून्य, cmd);
	अगर (err)
		वापस err;

	स_रखो(msginfo, 0, माप(*msginfo));
	msginfo->msgmni = ns->msg_ctlmni;
	msginfo->msgmax = ns->msg_ctlmax;
	msginfo->msgmnb = ns->msg_ctlmnb;
	msginfo->msgssz = MSGSSZ;
	msginfo->msgseg = MSGSEG;
	करोwn_पढ़ो(&msg_ids(ns).rwsem);
	अगर (cmd == MSG_INFO) अणु
		msginfo->msgpool = msg_ids(ns).in_use;
		msginfo->msgmap = atomic_पढ़ो(&ns->msg_hdrs);
		msginfo->msgtql = atomic_पढ़ो(&ns->msg_bytes);
	पूर्ण अन्यथा अणु
		msginfo->msgmap = MSGMAP;
		msginfo->msgpool = MSGPOOL;
		msginfo->msgtql = MSGTQL;
	पूर्ण
	max_idx = ipc_get_maxidx(&msg_ids(ns));
	up_पढ़ो(&msg_ids(ns).rwsem);
	वापस (max_idx < 0) ? 0 : max_idx;
पूर्ण

अटल पूर्णांक msgctl_stat(काष्ठा ipc_namespace *ns, पूर्णांक msqid,
			 पूर्णांक cmd, काष्ठा msqid64_ds *p)
अणु
	काष्ठा msg_queue *msq;
	पूर्णांक err;

	स_रखो(p, 0, माप(*p));

	rcu_पढ़ो_lock();
	अगर (cmd == MSG_STAT || cmd == MSG_STAT_ANY) अणु
		msq = msq_obtain_object(ns, msqid);
		अगर (IS_ERR(msq)) अणु
			err = PTR_ERR(msq);
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु /* IPC_STAT */
		msq = msq_obtain_object_check(ns, msqid);
		अगर (IS_ERR(msq)) अणु
			err = PTR_ERR(msq);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* see comment क्रम SHM_STAT_ANY */
	अगर (cmd == MSG_STAT_ANY)
		audit_ipc_obj(&msq->q_perm);
	अन्यथा अणु
		err = -EACCES;
		अगर (ipcperms(ns, &msq->q_perm, S_IRUGO))
			जाओ out_unlock;
	पूर्ण

	err = security_msg_queue_msgctl(&msq->q_perm, cmd);
	अगर (err)
		जाओ out_unlock;

	ipc_lock_object(&msq->q_perm);

	अगर (!ipc_valid_object(&msq->q_perm)) अणु
		ipc_unlock_object(&msq->q_perm);
		err = -EIDRM;
		जाओ out_unlock;
	पूर्ण

	kernel_to_ipc64_perm(&msq->q_perm, &p->msg_perm);
	p->msg_sसमय  = msq->q_sसमय;
	p->msg_rसमय  = msq->q_rसमय;
	p->msg_स_समय  = msq->q_स_समय;
#अगर_अघोषित CONFIG_64BIT
	p->msg_sसमय_high = msq->q_sसमय >> 32;
	p->msg_rसमय_high = msq->q_rसमय >> 32;
	p->msg_स_समय_high = msq->q_स_समय >> 32;
#पूर्ण_अगर
	p->msg_cbytes = msq->q_cbytes;
	p->msg_qnum   = msq->q_qnum;
	p->msg_qbytes = msq->q_qbytes;
	p->msg_lspid  = pid_vnr(msq->q_lspid);
	p->msg_lrpid  = pid_vnr(msq->q_lrpid);

	अगर (cmd == IPC_STAT) अणु
		/*
		 * As defined in SUS:
		 * Return 0 on success
		 */
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * MSG_STAT and MSG_STAT_ANY (both Linux specअगरic)
		 * Return the full id, including the sequence number
		 */
		err = msq->q_perm.id;
	पूर्ण

	ipc_unlock_object(&msq->q_perm);
out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल दीर्घ ksys_msgctl(पूर्णांक msqid, पूर्णांक cmd, काष्ठा msqid_ds __user *buf, पूर्णांक version)
अणु
	काष्ठा ipc_namespace *ns;
	काष्ठा msqid64_ds msqid64;
	पूर्णांक err;

	अगर (msqid < 0 || cmd < 0)
		वापस -EINVAL;

	ns = current->nsproxy->ipc_ns;

	चयन (cmd) अणु
	हाल IPC_INFO:
	हाल MSG_INFO: अणु
		काष्ठा msginfo msginfo;
		err = msgctl_info(ns, msqid, cmd, &msginfo);
		अगर (err < 0)
			वापस err;
		अगर (copy_to_user(buf, &msginfo, माप(काष्ठा msginfo)))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल MSG_STAT:	/* msqid is an index rather than a msg queue id */
	हाल MSG_STAT_ANY:
	हाल IPC_STAT:
		err = msgctl_stat(ns, msqid, cmd, &msqid64);
		अगर (err < 0)
			वापस err;
		अगर (copy_msqid_to_user(buf, &msqid64, version))
			err = -EFAULT;
		वापस err;
	हाल IPC_SET:
		अगर (copy_msqid_from_user(&msqid64, buf, version))
			वापस -EFAULT;
		वापस msgctl_करोwn(ns, msqid, cmd, &msqid64.msg_perm,
				   msqid64.msg_qbytes);
	हाल IPC_RMID:
		वापस msgctl_करोwn(ns, msqid, cmd, शून्य, 0);
	शेष:
		वापस  -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE3(msgctl, पूर्णांक, msqid, पूर्णांक, cmd, काष्ठा msqid_ds __user *, buf)
अणु
	वापस ksys_msgctl(msqid, cmd, buf, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_IPC_PARSE_VERSION
दीर्घ ksys_old_msgctl(पूर्णांक msqid, पूर्णांक cmd, काष्ठा msqid_ds __user *buf)
अणु
	पूर्णांक version = ipc_parse_version(&cmd);

	वापस ksys_msgctl(msqid, cmd, buf, version);
पूर्ण

SYSCALL_DEFINE3(old_msgctl, पूर्णांक, msqid, पूर्णांक, cmd, काष्ठा msqid_ds __user *, buf)
अणु
	वापस ksys_old_msgctl(msqid, cmd, buf);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_msqid_ds अणु
	काष्ठा compat_ipc_perm msg_perm;
	compat_uptr_t msg_first;
	compat_uptr_t msg_last;
	old_समय32_t msg_sसमय;
	old_समय32_t msg_rसमय;
	old_समय32_t msg_स_समय;
	compat_uदीर्घ_t msg_lcbytes;
	compat_uदीर्घ_t msg_lqbytes;
	अचिन्हित लघु msg_cbytes;
	अचिन्हित लघु msg_qnum;
	अचिन्हित लघु msg_qbytes;
	compat_ipc_pid_t msg_lspid;
	compat_ipc_pid_t msg_lrpid;
पूर्ण;

अटल पूर्णांक copy_compat_msqid_from_user(काष्ठा msqid64_ds *out, व्योम __user *buf,
					पूर्णांक version)
अणु
	स_रखो(out, 0, माप(*out));
	अगर (version == IPC_64) अणु
		काष्ठा compat_msqid64_ds __user *p = buf;
		अगर (get_compat_ipc64_perm(&out->msg_perm, &p->msg_perm))
			वापस -EFAULT;
		अगर (get_user(out->msg_qbytes, &p->msg_qbytes))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		काष्ठा compat_msqid_ds __user *p = buf;
		अगर (get_compat_ipc_perm(&out->msg_perm, &p->msg_perm))
			वापस -EFAULT;
		अगर (get_user(out->msg_qbytes, &p->msg_qbytes))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक copy_compat_msqid_to_user(व्योम __user *buf, काष्ठा msqid64_ds *in,
					पूर्णांक version)
अणु
	अगर (version == IPC_64) अणु
		काष्ठा compat_msqid64_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc64_perm(&v.msg_perm, &in->msg_perm);
		v.msg_sसमय	 = lower_32_bits(in->msg_sसमय);
		v.msg_sसमय_high = upper_32_bits(in->msg_sसमय);
		v.msg_rसमय	 = lower_32_bits(in->msg_rसमय);
		v.msg_rसमय_high = upper_32_bits(in->msg_rसमय);
		v.msg_स_समय	 = lower_32_bits(in->msg_स_समय);
		v.msg_स_समय_high = upper_32_bits(in->msg_स_समय);
		v.msg_cbytes = in->msg_cbytes;
		v.msg_qnum = in->msg_qnum;
		v.msg_qbytes = in->msg_qbytes;
		v.msg_lspid = in->msg_lspid;
		v.msg_lrpid = in->msg_lrpid;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण अन्यथा अणु
		काष्ठा compat_msqid_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc_perm(&v.msg_perm, &in->msg_perm);
		v.msg_sसमय = in->msg_sसमय;
		v.msg_rसमय = in->msg_rसमय;
		v.msg_स_समय = in->msg_स_समय;
		v.msg_cbytes = in->msg_cbytes;
		v.msg_qnum = in->msg_qnum;
		v.msg_qbytes = in->msg_qbytes;
		v.msg_lspid = in->msg_lspid;
		v.msg_lrpid = in->msg_lrpid;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण
पूर्ण

अटल दीर्घ compat_ksys_msgctl(पूर्णांक msqid, पूर्णांक cmd, व्योम __user *uptr, पूर्णांक version)
अणु
	काष्ठा ipc_namespace *ns;
	पूर्णांक err;
	काष्ठा msqid64_ds msqid64;

	ns = current->nsproxy->ipc_ns;

	अगर (msqid < 0 || cmd < 0)
		वापस -EINVAL;

	चयन (cmd & (~IPC_64)) अणु
	हाल IPC_INFO:
	हाल MSG_INFO: अणु
		काष्ठा msginfo msginfo;
		err = msgctl_info(ns, msqid, cmd, &msginfo);
		अगर (err < 0)
			वापस err;
		अगर (copy_to_user(uptr, &msginfo, माप(काष्ठा msginfo)))
			err = -EFAULT;
		वापस err;
	पूर्ण
	हाल IPC_STAT:
	हाल MSG_STAT:
	हाल MSG_STAT_ANY:
		err = msgctl_stat(ns, msqid, cmd, &msqid64);
		अगर (err < 0)
			वापस err;
		अगर (copy_compat_msqid_to_user(uptr, &msqid64, version))
			err = -EFAULT;
		वापस err;
	हाल IPC_SET:
		अगर (copy_compat_msqid_from_user(&msqid64, uptr, version))
			वापस -EFAULT;
		वापस msgctl_करोwn(ns, msqid, cmd, &msqid64.msg_perm, msqid64.msg_qbytes);
	हाल IPC_RMID:
		वापस msgctl_करोwn(ns, msqid, cmd, शून्य, 0);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

COMPAT_SYSCALL_DEFINE3(msgctl, पूर्णांक, msqid, पूर्णांक, cmd, व्योम __user *, uptr)
अणु
	वापस compat_ksys_msgctl(msqid, cmd, uptr, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_COMPAT_IPC_PARSE_VERSION
दीर्घ compat_ksys_old_msgctl(पूर्णांक msqid, पूर्णांक cmd, व्योम __user *uptr)
अणु
	पूर्णांक version = compat_ipc_parse_version(&cmd);

	वापस compat_ksys_msgctl(msqid, cmd, uptr, version);
पूर्ण

COMPAT_SYSCALL_DEFINE3(old_msgctl, पूर्णांक, msqid, पूर्णांक, cmd, व्योम __user *, uptr)
अणु
	वापस compat_ksys_old_msgctl(msqid, cmd, uptr);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक tesपंचांगsg(काष्ठा msg_msg *msg, दीर्घ type, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल SEARCH_ANY:
	हाल SEARCH_NUMBER:
		वापस 1;
	हाल SEARCH_LESSEQUAL:
		अगर (msg->m_type <= type)
			वापस 1;
		अवरोध;
	हाल SEARCH_EQUAL:
		अगर (msg->m_type == type)
			वापस 1;
		अवरोध;
	हाल SEARCH_NOTEQUAL:
		अगर (msg->m_type != type)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pipelined_send(काष्ठा msg_queue *msq, काष्ठा msg_msg *msg,
				 काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा msg_receiver *msr, *t;

	list_क्रम_each_entry_safe(msr, t, &msq->q_receivers, r_list) अणु
		अगर (tesपंचांगsg(msg, msr->r_msgtype, msr->r_mode) &&
		    !security_msg_queue_msgrcv(&msq->q_perm, msg, msr->r_tsk,
					       msr->r_msgtype, msr->r_mode)) अणु

			list_del(&msr->r_list);
			अगर (msr->r_maxsize < msg->m_ts) अणु
				wake_q_add(wake_q, msr->r_tsk);

				/* See expunge_all regarding memory barrier */
				smp_store_release(&msr->r_msg, ERR_PTR(-E2BIG));
			पूर्ण अन्यथा अणु
				ipc_update_pid(&msq->q_lrpid, task_pid(msr->r_tsk));
				msq->q_rसमय = kसमय_get_real_seconds();

				wake_q_add(wake_q, msr->r_tsk);

				/* See expunge_all regarding memory barrier */
				smp_store_release(&msr->r_msg, msg);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ करो_msgsnd(पूर्णांक msqid, दीर्घ mtype, व्योम __user *mtext,
		माप_प्रकार msgsz, पूर्णांक msgflg)
अणु
	काष्ठा msg_queue *msq;
	काष्ठा msg_msg *msg;
	पूर्णांक err;
	काष्ठा ipc_namespace *ns;
	DEFINE_WAKE_Q(wake_q);

	ns = current->nsproxy->ipc_ns;

	अगर (msgsz > ns->msg_ctlmax || (दीर्घ) msgsz < 0 || msqid < 0)
		वापस -EINVAL;
	अगर (mtype < 1)
		वापस -EINVAL;

	msg = load_msg(mtext, msgsz);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	msg->m_type = mtype;
	msg->m_ts = msgsz;

	rcu_पढ़ो_lock();
	msq = msq_obtain_object_check(ns, msqid);
	अगर (IS_ERR(msq)) अणु
		err = PTR_ERR(msq);
		जाओ out_unlock1;
	पूर्ण

	ipc_lock_object(&msq->q_perm);

	क्रम (;;) अणु
		काष्ठा msg_sender s;

		err = -EACCES;
		अगर (ipcperms(ns, &msq->q_perm, S_IWUGO))
			जाओ out_unlock0;

		/* raced with RMID? */
		अगर (!ipc_valid_object(&msq->q_perm)) अणु
			err = -EIDRM;
			जाओ out_unlock0;
		पूर्ण

		err = security_msg_queue_msgsnd(&msq->q_perm, msg, msgflg);
		अगर (err)
			जाओ out_unlock0;

		अगर (msg_fits_inqueue(msq, msgsz))
			अवरोध;

		/* queue full, रुको: */
		अगर (msgflg & IPC_NOWAIT) अणु
			err = -EAGAIN;
			जाओ out_unlock0;
		पूर्ण

		/* enqueue the sender and prepare to block */
		ss_add(msq, &s, msgsz);

		अगर (!ipc_rcu_getref(&msq->q_perm)) अणु
			err = -EIDRM;
			जाओ out_unlock0;
		पूर्ण

		ipc_unlock_object(&msq->q_perm);
		rcu_पढ़ो_unlock();
		schedule();

		rcu_पढ़ो_lock();
		ipc_lock_object(&msq->q_perm);

		ipc_rcu_putref(&msq->q_perm, msg_rcu_मुक्त);
		/* raced with RMID? */
		अगर (!ipc_valid_object(&msq->q_perm)) अणु
			err = -EIDRM;
			जाओ out_unlock0;
		पूर्ण
		ss_del(&s);

		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTNOHAND;
			जाओ out_unlock0;
		पूर्ण

	पूर्ण

	ipc_update_pid(&msq->q_lspid, task_tgid(current));
	msq->q_sसमय = kसमय_get_real_seconds();

	अगर (!pipelined_send(msq, msg, &wake_q)) अणु
		/* no one is रुकोing क्रम this message, enqueue it */
		list_add_tail(&msg->m_list, &msq->q_messages);
		msq->q_cbytes += msgsz;
		msq->q_qnum++;
		atomic_add(msgsz, &ns->msg_bytes);
		atomic_inc(&ns->msg_hdrs);
	पूर्ण

	err = 0;
	msg = शून्य;

out_unlock0:
	ipc_unlock_object(&msq->q_perm);
	wake_up_q(&wake_q);
out_unlock1:
	rcu_पढ़ो_unlock();
	अगर (msg != शून्य)
		मुक्त_msg(msg);
	वापस err;
पूर्ण

दीर्घ ksys_msgsnd(पूर्णांक msqid, काष्ठा msgbuf __user *msgp, माप_प्रकार msgsz,
		 पूर्णांक msgflg)
अणु
	दीर्घ mtype;

	अगर (get_user(mtype, &msgp->mtype))
		वापस -EFAULT;
	वापस करो_msgsnd(msqid, mtype, msgp->mtext, msgsz, msgflg);
पूर्ण

SYSCALL_DEFINE4(msgsnd, पूर्णांक, msqid, काष्ठा msgbuf __user *, msgp, माप_प्रकार, msgsz,
		पूर्णांक, msgflg)
अणु
	वापस ksys_msgsnd(msqid, msgp, msgsz, msgflg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_msgbuf अणु
	compat_दीर्घ_t mtype;
	अक्षर mtext[1];
पूर्ण;

दीर्घ compat_ksys_msgsnd(पूर्णांक msqid, compat_uptr_t msgp,
		       compat_sमाप_प्रकार msgsz, पूर्णांक msgflg)
अणु
	काष्ठा compat_msgbuf __user *up = compat_ptr(msgp);
	compat_दीर्घ_t mtype;

	अगर (get_user(mtype, &up->mtype))
		वापस -EFAULT;
	वापस करो_msgsnd(msqid, mtype, up->mtext, (sमाप_प्रकार)msgsz, msgflg);
पूर्ण

COMPAT_SYSCALL_DEFINE4(msgsnd, पूर्णांक, msqid, compat_uptr_t, msgp,
		       compat_sमाप_प्रकार, msgsz, पूर्णांक, msgflg)
अणु
	वापस compat_ksys_msgsnd(msqid, msgp, msgsz, msgflg);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक convert_mode(दीर्घ *msgtyp, पूर्णांक msgflg)
अणु
	अगर (msgflg & MSG_COPY)
		वापस SEARCH_NUMBER;
	/*
	 *  find message of correct type.
	 *  msgtyp = 0 => get first.
	 *  msgtyp > 0 => get first message of matching type.
	 *  msgtyp < 0 => get message with least type must be < असल(msgtype).
	 */
	अगर (*msgtyp == 0)
		वापस SEARCH_ANY;
	अगर (*msgtyp < 0) अणु
		अगर (*msgtyp == दीर्घ_न्यून) /* -दीर्घ_न्यून is undefined */
			*msgtyp = दीर्घ_उच्च;
		अन्यथा
			*msgtyp = -*msgtyp;
		वापस SEARCH_LESSEQUAL;
	पूर्ण
	अगर (msgflg & MSG_EXCEPT)
		वापस SEARCH_NOTEQUAL;
	वापस SEARCH_EQUAL;
पूर्ण

अटल दीर्घ करो_msg_fill(व्योम __user *dest, काष्ठा msg_msg *msg, माप_प्रकार bufsz)
अणु
	काष्ठा msgbuf __user *msgp = dest;
	माप_प्रकार msgsz;

	अगर (put_user(msg->m_type, &msgp->mtype))
		वापस -EFAULT;

	msgsz = (bufsz > msg->m_ts) ? msg->m_ts : bufsz;
	अगर (store_msg(msgp->mtext, msg, msgsz))
		वापस -EFAULT;
	वापस msgsz;
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
/*
 * This function creates new kernel message काष्ठाure, large enough to store
 * bufsz message bytes.
 */
अटल अंतरभूत काष्ठा msg_msg *prepare_copy(व्योम __user *buf, माप_प्रकार bufsz)
अणु
	काष्ठा msg_msg *copy;

	/*
	 * Create dummy message to copy real message to.
	 */
	copy = load_msg(buf, bufsz);
	अगर (!IS_ERR(copy))
		copy->m_ts = bufsz;
	वापस copy;
पूर्ण

अटल अंतरभूत व्योम मुक्त_copy(काष्ठा msg_msg *copy)
अणु
	अगर (copy)
		मुक्त_msg(copy);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा msg_msg *prepare_copy(व्योम __user *buf, माप_प्रकार bufsz)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम मुक्त_copy(काष्ठा msg_msg *copy)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा msg_msg *find_msg(काष्ठा msg_queue *msq, दीर्घ *msgtyp, पूर्णांक mode)
अणु
	काष्ठा msg_msg *msg, *found = शून्य;
	दीर्घ count = 0;

	list_क्रम_each_entry(msg, &msq->q_messages, m_list) अणु
		अगर (tesपंचांगsg(msg, *msgtyp, mode) &&
		    !security_msg_queue_msgrcv(&msq->q_perm, msg, current,
					       *msgtyp, mode)) अणु
			अगर (mode == SEARCH_LESSEQUAL && msg->m_type != 1) अणु
				*msgtyp = msg->m_type - 1;
				found = msg;
			पूर्ण अन्यथा अगर (mode == SEARCH_NUMBER) अणु
				अगर (*msgtyp == count)
					वापस msg;
			पूर्ण अन्यथा
				वापस msg;
			count++;
		पूर्ण
	पूर्ण

	वापस found ?: ERR_PTR(-EAGAIN);
पूर्ण

अटल दीर्घ करो_msgrcv(पूर्णांक msqid, व्योम __user *buf, माप_प्रकार bufsz, दीर्घ msgtyp, पूर्णांक msgflg,
	       दीर्घ (*msg_handler)(व्योम __user *, काष्ठा msg_msg *, माप_प्रकार))
अणु
	पूर्णांक mode;
	काष्ठा msg_queue *msq;
	काष्ठा ipc_namespace *ns;
	काष्ठा msg_msg *msg, *copy = शून्य;
	DEFINE_WAKE_Q(wake_q);

	ns = current->nsproxy->ipc_ns;

	अगर (msqid < 0 || (दीर्घ) bufsz < 0)
		वापस -EINVAL;

	अगर (msgflg & MSG_COPY) अणु
		अगर ((msgflg & MSG_EXCEPT) || !(msgflg & IPC_NOWAIT))
			वापस -EINVAL;
		copy = prepare_copy(buf, min_t(माप_प्रकार, bufsz, ns->msg_ctlmax));
		अगर (IS_ERR(copy))
			वापस PTR_ERR(copy);
	पूर्ण
	mode = convert_mode(&msgtyp, msgflg);

	rcu_पढ़ो_lock();
	msq = msq_obtain_object_check(ns, msqid);
	अगर (IS_ERR(msq)) अणु
		rcu_पढ़ो_unlock();
		मुक्त_copy(copy);
		वापस PTR_ERR(msq);
	पूर्ण

	क्रम (;;) अणु
		काष्ठा msg_receiver msr_d;

		msg = ERR_PTR(-EACCES);
		अगर (ipcperms(ns, &msq->q_perm, S_IRUGO))
			जाओ out_unlock1;

		ipc_lock_object(&msq->q_perm);

		/* raced with RMID? */
		अगर (!ipc_valid_object(&msq->q_perm)) अणु
			msg = ERR_PTR(-EIDRM);
			जाओ out_unlock0;
		पूर्ण

		msg = find_msg(msq, &msgtyp, mode);
		अगर (!IS_ERR(msg)) अणु
			/*
			 * Found a suitable message.
			 * Unlink it from the queue.
			 */
			अगर ((bufsz < msg->m_ts) && !(msgflg & MSG_NOERROR)) अणु
				msg = ERR_PTR(-E2BIG);
				जाओ out_unlock0;
			पूर्ण
			/*
			 * If we are copying, then करो not unlink message and करो
			 * not update queue parameters.
			 */
			अगर (msgflg & MSG_COPY) अणु
				msg = copy_msg(msg, copy);
				जाओ out_unlock0;
			पूर्ण

			list_del(&msg->m_list);
			msq->q_qnum--;
			msq->q_rसमय = kसमय_get_real_seconds();
			ipc_update_pid(&msq->q_lrpid, task_tgid(current));
			msq->q_cbytes -= msg->m_ts;
			atomic_sub(msg->m_ts, &ns->msg_bytes);
			atomic_dec(&ns->msg_hdrs);
			ss_wakeup(msq, &wake_q, false);

			जाओ out_unlock0;
		पूर्ण

		/* No message रुकोing. Wait क्रम a message */
		अगर (msgflg & IPC_NOWAIT) अणु
			msg = ERR_PTR(-ENOMSG);
			जाओ out_unlock0;
		पूर्ण

		list_add_tail(&msr_d.r_list, &msq->q_receivers);
		msr_d.r_tsk = current;
		msr_d.r_msgtype = msgtyp;
		msr_d.r_mode = mode;
		अगर (msgflg & MSG_NOERROR)
			msr_d.r_maxsize = पूर्णांक_उच्च;
		अन्यथा
			msr_d.r_maxsize = bufsz;

		/* memory barrier not require due to ipc_lock_object() */
		WRITE_ONCE(msr_d.r_msg, ERR_PTR(-EAGAIN));

		/* memory barrier not required, we own ipc_lock_object() */
		__set_current_state(TASK_INTERRUPTIBLE);

		ipc_unlock_object(&msq->q_perm);
		rcu_पढ़ो_unlock();
		schedule();

		/*
		 * Lockless receive, part 1:
		 * We करोn't hold a reference to the queue and getting a
		 * reference would defeat the idea of a lockless operation,
		 * thus the code relies on rcu to guarantee the existence of
		 * msq:
		 * Prior to deकाष्ठाion, expunge_all(-EIRDM) changes r_msg.
		 * Thus अगर r_msg is -EAGAIN, then the queue not yet destroyed.
		 */
		rcu_पढ़ो_lock();

		/*
		 * Lockless receive, part 2:
		 * The work in pipelined_send() and expunge_all():
		 * - Set poपूर्णांकer to message
		 * - Queue the receiver task क्रम later wakeup
		 * - Wake up the process after the lock is dropped.
		 *
		 * Should the process wake up beक्रमe this wakeup (due to a
		 * संकेत) it will either see the message and जारी ...
		 */
		msg = READ_ONCE(msr_d.r_msg);
		अगर (msg != ERR_PTR(-EAGAIN)) अणु
			/* see MSG_BARRIER क्रम purpose/pairing */
			smp_acquire__after_ctrl_dep();

			जाओ out_unlock1;
		पूर्ण

		 /*
		  * ... or see -EAGAIN, acquire the lock to check the message
		  * again.
		  */
		ipc_lock_object(&msq->q_perm);

		msg = READ_ONCE(msr_d.r_msg);
		अगर (msg != ERR_PTR(-EAGAIN))
			जाओ out_unlock0;

		list_del(&msr_d.r_list);
		अगर (संकेत_pending(current)) अणु
			msg = ERR_PTR(-ERESTARTNOHAND);
			जाओ out_unlock0;
		पूर्ण

		ipc_unlock_object(&msq->q_perm);
	पूर्ण

out_unlock0:
	ipc_unlock_object(&msq->q_perm);
	wake_up_q(&wake_q);
out_unlock1:
	rcu_पढ़ो_unlock();
	अगर (IS_ERR(msg)) अणु
		मुक्त_copy(copy);
		वापस PTR_ERR(msg);
	पूर्ण

	bufsz = msg_handler(buf, msg, bufsz);
	मुक्त_msg(msg);

	वापस bufsz;
पूर्ण

दीर्घ ksys_msgrcv(पूर्णांक msqid, काष्ठा msgbuf __user *msgp, माप_प्रकार msgsz,
		 दीर्घ msgtyp, पूर्णांक msgflg)
अणु
	वापस करो_msgrcv(msqid, msgp, msgsz, msgtyp, msgflg, करो_msg_fill);
पूर्ण

SYSCALL_DEFINE5(msgrcv, पूर्णांक, msqid, काष्ठा msgbuf __user *, msgp, माप_प्रकार, msgsz,
		दीर्घ, msgtyp, पूर्णांक, msgflg)
अणु
	वापस ksys_msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_करो_msg_fill(व्योम __user *dest, काष्ठा msg_msg *msg, माप_प्रकार bufsz)
अणु
	काष्ठा compat_msgbuf __user *msgp = dest;
	माप_प्रकार msgsz;

	अगर (put_user(msg->m_type, &msgp->mtype))
		वापस -EFAULT;

	msgsz = (bufsz > msg->m_ts) ? msg->m_ts : bufsz;
	अगर (store_msg(msgp->mtext, msg, msgsz))
		वापस -EFAULT;
	वापस msgsz;
पूर्ण

दीर्घ compat_ksys_msgrcv(पूर्णांक msqid, compat_uptr_t msgp, compat_sमाप_प्रकार msgsz,
			compat_दीर्घ_t msgtyp, पूर्णांक msgflg)
अणु
	वापस करो_msgrcv(msqid, compat_ptr(msgp), (sमाप_प्रकार)msgsz, (दीर्घ)msgtyp,
			 msgflg, compat_करो_msg_fill);
पूर्ण

COMPAT_SYSCALL_DEFINE5(msgrcv, पूर्णांक, msqid, compat_uptr_t, msgp,
		       compat_sमाप_प्रकार, msgsz, compat_दीर्घ_t, msgtyp,
		       पूर्णांक, msgflg)
अणु
	वापस compat_ksys_msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
पूर्ण
#पूर्ण_अगर

व्योम msg_init_ns(काष्ठा ipc_namespace *ns)
अणु
	ns->msg_ctlmax = MSGMAX;
	ns->msg_ctlmnb = MSGMNB;
	ns->msg_ctlmni = MSGMNI;

	atomic_set(&ns->msg_bytes, 0);
	atomic_set(&ns->msg_hdrs, 0);
	ipc_init_ids(&ns->ids[IPC_MSG_IDS]);
पूर्ण

#अगर_घोषित CONFIG_IPC_NS
व्योम msg_निकास_ns(काष्ठा ipc_namespace *ns)
अणु
	मुक्त_ipcs(ns, &msg_ids(ns), मुक्तque);
	idr_destroy(&ns->ids[IPC_MSG_IDS].ipcs_idr);
	rhashtable_destroy(&ns->ids[IPC_MSG_IDS].key_ht);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sysvipc_msg_proc_show(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा pid_namespace *pid_ns = ipc_seq_pid_ns(s);
	काष्ठा user_namespace *user_ns = seq_user_ns(s);
	काष्ठा kern_ipc_perm *ipcp = it;
	काष्ठा msg_queue *msq = container_of(ipcp, काष्ठा msg_queue, q_perm);

	seq_म_लिखो(s,
		   "%10d %10d  %4o  %10lu %10lu %5u %5u %5u %5u %5u %5u %10llu %10llu %10llu\n",
		   msq->q_perm.key,
		   msq->q_perm.id,
		   msq->q_perm.mode,
		   msq->q_cbytes,
		   msq->q_qnum,
		   pid_nr_ns(msq->q_lspid, pid_ns),
		   pid_nr_ns(msq->q_lrpid, pid_ns),
		   from_kuid_munged(user_ns, msq->q_perm.uid),
		   from_kgid_munged(user_ns, msq->q_perm.gid),
		   from_kuid_munged(user_ns, msq->q_perm.cuid),
		   from_kgid_munged(user_ns, msq->q_perm.cgid),
		   msq->q_sसमय,
		   msq->q_rसमय,
		   msq->q_स_समय);

	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init msg_init(व्योम)
अणु
	msg_init_ns(&init_ipc_ns);

	ipc_init_proc_पूर्णांकerface("sysvipc/msg",
				"       key      msqid perms      cbytes       qnum lspid lrpid   uid   gid  cuid  cgid      stime      rtime      ctime\n",
				IPC_MSG_IDS, sysvipc_msg_proc_show);
पूर्ण
