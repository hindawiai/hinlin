<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* scm.c - Socket level control messages processing.
 *
 * Author:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *              Alignment and value checking mods by Craig Metz
 */

#समावेश <linux/module.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/socket.h>
#समावेश <linux/file.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/net.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/security.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/pid.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/errqueue.h>

#समावेश <linux/uaccess.h>

#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/compat.h>
#समावेश <net/scm.h>
#समावेश <net/cls_cgroup.h>


/*
 *	Only allow a user to send credentials, that they could set with
 *	setu(g)id.
 */

अटल __अंतरभूत__ पूर्णांक scm_check_creds(काष्ठा ucred *creds)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	kuid_t uid = make_kuid(cred->user_ns, creds->uid);
	kgid_t gid = make_kgid(cred->user_ns, creds->gid);

	अगर (!uid_valid(uid) || !gid_valid(gid))
		वापस -EINVAL;

	अगर ((creds->pid == task_tgid_vnr(current) ||
	     ns_capable(task_active_pid_ns(current)->user_ns, CAP_SYS_ADMIN)) &&
	    ((uid_eq(uid, cred->uid)   || uid_eq(uid, cred->euid) ||
	      uid_eq(uid, cred->suid)) || ns_capable(cred->user_ns, CAP_SETUID)) &&
	    ((gid_eq(gid, cred->gid)   || gid_eq(gid, cred->egid) ||
	      gid_eq(gid, cred->sgid)) || ns_capable(cred->user_ns, CAP_SETGID))) अणु
	       वापस 0;
	पूर्ण
	वापस -EPERM;
पूर्ण

अटल पूर्णांक scm_fp_copy(काष्ठा cmsghdr *cmsg, काष्ठा scm_fp_list **fplp)
अणु
	पूर्णांक *fdp = (पूर्णांक*)CMSG_DATA(cmsg);
	काष्ठा scm_fp_list *fpl = *fplp;
	काष्ठा file **fpp;
	पूर्णांक i, num;

	num = (cmsg->cmsg_len - माप(काष्ठा cmsghdr))/माप(पूर्णांक);

	अगर (num <= 0)
		वापस 0;

	अगर (num > SCM_MAX_FD)
		वापस -EINVAL;

	अगर (!fpl)
	अणु
		fpl = kदो_स्मृति(माप(काष्ठा scm_fp_list), GFP_KERNEL);
		अगर (!fpl)
			वापस -ENOMEM;
		*fplp = fpl;
		fpl->count = 0;
		fpl->max = SCM_MAX_FD;
		fpl->user = शून्य;
	पूर्ण
	fpp = &fpl->fp[fpl->count];

	अगर (fpl->count + num > fpl->max)
		वापस -EINVAL;

	/*
	 *	Verअगरy the descriptors and increment the usage count.
	 */

	क्रम (i=0; i< num; i++)
	अणु
		पूर्णांक fd = fdp[i];
		काष्ठा file *file;

		अगर (fd < 0 || !(file = fget_raw(fd)))
			वापस -EBADF;
		*fpp++ = file;
		fpl->count++;
	पूर्ण

	अगर (!fpl->user)
		fpl->user = get_uid(current_user());

	वापस num;
पूर्ण

व्योम __scm_destroy(काष्ठा scm_cookie *scm)
अणु
	काष्ठा scm_fp_list *fpl = scm->fp;
	पूर्णांक i;

	अगर (fpl) अणु
		scm->fp = शून्य;
		क्रम (i=fpl->count-1; i>=0; i--)
			fput(fpl->fp[i]);
		मुक्त_uid(fpl->user);
		kमुक्त(fpl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__scm_destroy);

पूर्णांक __scm_send(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा scm_cookie *p)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक err;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		err = -EINVAL;

		/* Verअगरy that cmsg_len is at least माप(काष्ठा cmsghdr) */
		/* The first check was omitted in <= 2.2.5. The reasoning was
		   that parser checks cmsg_len in any हाल, so that
		   additional check would be work duplication.
		   But अगर cmsg_level is not SOL_SOCKET, we करो not check
		   क्रम too लघु ancillary data object at all! Oops.
		   OK, let's add it...
		 */
		अगर (!CMSG_OK(msg, cmsg))
			जाओ error;

		अगर (cmsg->cmsg_level != SOL_SOCKET)
			जारी;

		चयन (cmsg->cmsg_type)
		अणु
		हाल SCM_RIGHTS:
			अगर (!sock->ops || sock->ops->family != PF_UNIX)
				जाओ error;
			err=scm_fp_copy(cmsg, &p->fp);
			अगर (err<0)
				जाओ error;
			अवरोध;
		हाल SCM_CREDENTIALS:
		अणु
			काष्ठा ucred creds;
			kuid_t uid;
			kgid_t gid;
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा ucred)))
				जाओ error;
			स_नकल(&creds, CMSG_DATA(cmsg), माप(काष्ठा ucred));
			err = scm_check_creds(&creds);
			अगर (err)
				जाओ error;

			p->creds.pid = creds.pid;
			अगर (!p->pid || pid_vnr(p->pid) != creds.pid) अणु
				काष्ठा pid *pid;
				err = -ESRCH;
				pid = find_get_pid(creds.pid);
				अगर (!pid)
					जाओ error;
				put_pid(p->pid);
				p->pid = pid;
			पूर्ण

			err = -EINVAL;
			uid = make_kuid(current_user_ns(), creds.uid);
			gid = make_kgid(current_user_ns(), creds.gid);
			अगर (!uid_valid(uid) || !gid_valid(gid))
				जाओ error;

			p->creds.uid = uid;
			p->creds.gid = gid;
			अवरोध;
		पूर्ण
		शेष:
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (p->fp && !p->fp->count)
	अणु
		kमुक्त(p->fp);
		p->fp = शून्य;
	पूर्ण
	वापस 0;

error:
	scm_destroy(p);
	वापस err;
पूर्ण
EXPORT_SYMBOL(__scm_send);

पूर्णांक put_cmsg(काष्ठा msghdr * msg, पूर्णांक level, पूर्णांक type, पूर्णांक len, व्योम *data)
अणु
	पूर्णांक cmlen = CMSG_LEN(len);

	अगर (msg->msg_flags & MSG_CMSG_COMPAT)
		वापस put_cmsg_compat(msg, level, type, len, data);

	अगर (!msg->msg_control || msg->msg_controllen < माप(काष्ठा cmsghdr)) अणु
		msg->msg_flags |= MSG_CTRUNC;
		वापस 0; /* XXX: वापस error? check spec. */
	पूर्ण
	अगर (msg->msg_controllen < cmlen) अणु
		msg->msg_flags |= MSG_CTRUNC;
		cmlen = msg->msg_controllen;
	पूर्ण

	अगर (msg->msg_control_is_user) अणु
		काष्ठा cmsghdr __user *cm = msg->msg_control_user;

		अगर (!user_ग_लिखो_access_begin(cm, cmlen))
			जाओ efault;

		unsafe_put_user(cmlen, &cm->cmsg_len, efault_end);
		unsafe_put_user(level, &cm->cmsg_level, efault_end);
		unsafe_put_user(type, &cm->cmsg_type, efault_end);
		unsafe_copy_to_user(CMSG_USER_DATA(cm), data,
				    cmlen - माप(*cm), efault_end);
		user_ग_लिखो_access_end();
	पूर्ण अन्यथा अणु
		काष्ठा cmsghdr *cm = msg->msg_control;

		cm->cmsg_level = level;
		cm->cmsg_type = type;
		cm->cmsg_len = cmlen;
		स_नकल(CMSG_DATA(cm), data, cmlen - माप(*cm));
	पूर्ण

	cmlen = min(CMSG_SPACE(len), msg->msg_controllen);
	msg->msg_control += cmlen;
	msg->msg_controllen -= cmlen;
	वापस 0;

efault_end:
	user_ग_लिखो_access_end();
efault:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(put_cmsg);

व्योम put_cmsg_scm_बारtamping64(काष्ठा msghdr *msg, काष्ठा scm_बारtamping_पूर्णांकernal *tss_पूर्णांकernal)
अणु
	काष्ठा scm_बारtamping64 tss;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tss.ts); i++) अणु
		tss.ts[i].tv_sec = tss_पूर्णांकernal->ts[i].tv_sec;
		tss.ts[i].tv_nsec = tss_पूर्णांकernal->ts[i].tv_nsec;
	पूर्ण

	put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPING_NEW, माप(tss), &tss);
पूर्ण
EXPORT_SYMBOL(put_cmsg_scm_बारtamping64);

व्योम put_cmsg_scm_बारtamping(काष्ठा msghdr *msg, काष्ठा scm_बारtamping_पूर्णांकernal *tss_पूर्णांकernal)
अणु
	काष्ठा scm_बारtamping tss;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tss.ts); i++) अणु
		tss.ts[i].tv_sec = tss_पूर्णांकernal->ts[i].tv_sec;
		tss.ts[i].tv_nsec = tss_पूर्णांकernal->ts[i].tv_nsec;
	पूर्ण

	put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPING_OLD, माप(tss), &tss);
पूर्ण
EXPORT_SYMBOL(put_cmsg_scm_बारtamping);

अटल पूर्णांक scm_max_fds(काष्ठा msghdr *msg)
अणु
	अगर (msg->msg_controllen <= माप(काष्ठा cmsghdr))
		वापस 0;
	वापस (msg->msg_controllen - माप(काष्ठा cmsghdr)) / माप(पूर्णांक);
पूर्ण

व्योम scm_detach_fds(काष्ठा msghdr *msg, काष्ठा scm_cookie *scm)
अणु
	काष्ठा cmsghdr __user *cm =
		(__क्रमce काष्ठा cmsghdr __user *)msg->msg_control;
	अचिन्हित पूर्णांक o_flags = (msg->msg_flags & MSG_CMSG_CLOEXEC) ? O_CLOEXEC : 0;
	पूर्णांक fdmax = min_t(पूर्णांक, scm_max_fds(msg), scm->fp->count);
	पूर्णांक __user *cmsg_data = CMSG_USER_DATA(cm);
	पूर्णांक err = 0, i;

	/* no use क्रम FD passing from kernel space callers */
	अगर (WARN_ON_ONCE(!msg->msg_control_is_user))
		वापस;

	अगर (msg->msg_flags & MSG_CMSG_COMPAT) अणु
		scm_detach_fds_compat(msg, scm);
		वापस;
	पूर्ण

	क्रम (i = 0; i < fdmax; i++) अणु
		err = receive_fd_user(scm->fp->fp[i], cmsg_data + i, o_flags);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	अगर (i > 0) अणु
		पूर्णांक cmlen = CMSG_LEN(i * माप(पूर्णांक));

		err = put_user(SOL_SOCKET, &cm->cmsg_level);
		अगर (!err)
			err = put_user(SCM_RIGHTS, &cm->cmsg_type);
		अगर (!err)
			err = put_user(cmlen, &cm->cmsg_len);
		अगर (!err) अणु
			cmlen = CMSG_SPACE(i * माप(पूर्णांक));
			अगर (msg->msg_controllen < cmlen)
				cmlen = msg->msg_controllen;
			msg->msg_control += cmlen;
			msg->msg_controllen -= cmlen;
		पूर्ण
	पूर्ण

	अगर (i < scm->fp->count || (scm->fp->count && fdmax <= 0))
		msg->msg_flags |= MSG_CTRUNC;

	/*
	 * All of the files that fit in the message have had their usage counts
	 * incremented, so we just मुक्त the list.
	 */
	__scm_destroy(scm);
पूर्ण
EXPORT_SYMBOL(scm_detach_fds);

काष्ठा scm_fp_list *scm_fp_dup(काष्ठा scm_fp_list *fpl)
अणु
	काष्ठा scm_fp_list *new_fpl;
	पूर्णांक i;

	अगर (!fpl)
		वापस शून्य;

	new_fpl = kmemdup(fpl, दुरत्व(काष्ठा scm_fp_list, fp[fpl->count]),
			  GFP_KERNEL);
	अगर (new_fpl) अणु
		क्रम (i = 0; i < fpl->count; i++)
			get_file(fpl->fp[i]);
		new_fpl->max = new_fpl->count;
		new_fpl->user = get_uid(fpl->user);
	पूर्ण
	वापस new_fpl;
पूर्ण
EXPORT_SYMBOL(scm_fp_dup);
