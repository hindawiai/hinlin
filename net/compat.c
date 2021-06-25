<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 32bit Socket syscall emulation. Based on arch/sparc64/kernel/sys_sparc32.c.
 *
 * Copyright (C) 2000		VA Linux Co
 * Copyright (C) 2000		Don Dugger <n0ano@valinux.com>
 * Copyright (C) 1999 		Arun Sharma <arun.sharma@पूर्णांकel.com>
 * Copyright (C) 1997,1998 	Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 		David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2000		Hewlett-Packard Co.
 * Copyright (C) 2000		David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2000,2001	Andi Kleen, SuSE Lअसल
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/file.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/socket.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/filter.h>
#समावेश <linux/compat.h>
#समावेश <linux/security.h>
#समावेश <linux/audit.h>
#समावेश <linux/export.h>

#समावेश <net/scm.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/uaccess.h>
#समावेश <net/compat.h>

पूर्णांक __get_compat_msghdr(काष्ठा msghdr *kmsg,
			काष्ठा compat_msghdr __user *umsg,
			काष्ठा sockaddr __user **save_addr,
			compat_uptr_t *ptr, compat_माप_प्रकार *len)
अणु
	काष्ठा compat_msghdr msg;
	sमाप_प्रकार err;

	अगर (copy_from_user(&msg, umsg, माप(*umsg)))
		वापस -EFAULT;

	kmsg->msg_flags = msg.msg_flags;
	kmsg->msg_namelen = msg.msg_namelen;

	अगर (!msg.msg_name)
		kmsg->msg_namelen = 0;

	अगर (kmsg->msg_namelen < 0)
		वापस -EINVAL;

	अगर (kmsg->msg_namelen > माप(काष्ठा sockaddr_storage))
		kmsg->msg_namelen = माप(काष्ठा sockaddr_storage);

	kmsg->msg_control_is_user = true;
	kmsg->msg_control_user = compat_ptr(msg.msg_control);
	kmsg->msg_controllen = msg.msg_controllen;

	अगर (save_addr)
		*save_addr = compat_ptr(msg.msg_name);

	अगर (msg.msg_name && kmsg->msg_namelen) अणु
		अगर (!save_addr) अणु
			err = move_addr_to_kernel(compat_ptr(msg.msg_name),
						  kmsg->msg_namelen,
						  kmsg->msg_name);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		kmsg->msg_name = शून्य;
		kmsg->msg_namelen = 0;
	पूर्ण

	अगर (msg.msg_iovlen > UIO_MAXIOV)
		वापस -EMSGSIZE;

	kmsg->msg_iocb = शून्य;
	*ptr = msg.msg_iov;
	*len = msg.msg_iovlen;
	वापस 0;
पूर्ण

पूर्णांक get_compat_msghdr(काष्ठा msghdr *kmsg,
		      काष्ठा compat_msghdr __user *umsg,
		      काष्ठा sockaddr __user **save_addr,
		      काष्ठा iovec **iov)
अणु
	compat_uptr_t ptr;
	compat_माप_प्रकार len;
	sमाप_प्रकार err;

	err = __get_compat_msghdr(kmsg, umsg, save_addr, &ptr, &len);
	अगर (err)
		वापस err;

	err = import_iovec(save_addr ? READ : WRITE, compat_ptr(ptr), len,
			   UIO_FASTIOV, iov, &kmsg->msg_iter);
	वापस err < 0 ? err : 0;
पूर्ण

/* Bleech... */
#घोषणा CMSG_COMPAT_ALIGN(len)	ALIGN((len), माप(s32))

#घोषणा CMSG_COMPAT_DATA(cmsg)				\
	((व्योम __user *)((अक्षर __user *)(cmsg) + माप(काष्ठा compat_cmsghdr)))
#घोषणा CMSG_COMPAT_SPACE(len)				\
	(माप(काष्ठा compat_cmsghdr) + CMSG_COMPAT_ALIGN(len))
#घोषणा CMSG_COMPAT_LEN(len)				\
	(माप(काष्ठा compat_cmsghdr) + (len))

#घोषणा CMSG_COMPAT_FIRSTHDR(msg)			\
	(((msg)->msg_controllen) >= माप(काष्ठा compat_cmsghdr) ?	\
	 (काष्ठा compat_cmsghdr __user *)((msg)->msg_control) :		\
	 (काष्ठा compat_cmsghdr __user *)शून्य)

#घोषणा CMSG_COMPAT_OK(ucmlen, ucmsg, mhdr) \
	((ucmlen) >= माप(काष्ठा compat_cmsghdr) && \
	 (ucmlen) <= (अचिन्हित दीर्घ) \
	 ((mhdr)->msg_controllen - \
	  ((अक्षर __user *)(ucmsg) - (अक्षर __user *)(mhdr)->msg_control_user)))

अटल अंतरभूत काष्ठा compat_cmsghdr __user *cmsg_compat_nxthdr(काष्ठा msghdr *msg,
		काष्ठा compat_cmsghdr __user *cmsg, पूर्णांक cmsg_len)
अणु
	अक्षर __user *ptr = (अक्षर __user *)cmsg + CMSG_COMPAT_ALIGN(cmsg_len);
	अगर ((अचिन्हित दीर्घ)(ptr + 1 - (अक्षर __user *)msg->msg_control) >
			msg->msg_controllen)
		वापस शून्य;
	वापस (काष्ठा compat_cmsghdr __user *)ptr;
पूर्ण

/* There is a lot of hair here because the alignment rules (and
 * thus placement) of cmsg headers and length are dअगरferent क्रम
 * 32-bit apps.  -DaveM
 */
पूर्णांक cmsghdr_from_user_compat_to_kern(काष्ठा msghdr *kmsg, काष्ठा sock *sk,
			       अचिन्हित अक्षर *stackbuf, पूर्णांक stackbuf_size)
अणु
	काष्ठा compat_cmsghdr __user *ucmsg;
	काष्ठा cmsghdr *kcmsg, *kcmsg_base;
	compat_माप_प्रकार ucmlen;
	__kernel_माप_प्रकार kcmlen, पंचांगp;
	पूर्णांक err = -EFAULT;

	BUILD_BUG_ON(माप(काष्ठा compat_cmsghdr) !=
		     CMSG_COMPAT_ALIGN(माप(काष्ठा compat_cmsghdr)));

	kcmlen = 0;
	kcmsg_base = kcmsg = (काष्ठा cmsghdr *)stackbuf;
	ucmsg = CMSG_COMPAT_FIRSTHDR(kmsg);
	जबतक (ucmsg != शून्य) अणु
		अगर (get_user(ucmlen, &ucmsg->cmsg_len))
			वापस -EFAULT;

		/* Catch bogons. */
		अगर (!CMSG_COMPAT_OK(ucmlen, ucmsg, kmsg))
			वापस -EINVAL;

		पंचांगp = ((ucmlen - माप(*ucmsg)) + माप(काष्ठा cmsghdr));
		पंचांगp = CMSG_ALIGN(पंचांगp);
		kcmlen += पंचांगp;
		ucmsg = cmsg_compat_nxthdr(kmsg, ucmsg, ucmlen);
	पूर्ण
	अगर (kcmlen == 0)
		वापस -EINVAL;

	/* The kcmlen holds the 64-bit version of the control length.
	 * It may not be modअगरied as we करो not stick it पूर्णांकo the kmsg
	 * until we have successfully copied over all of the data
	 * from the user.
	 */
	अगर (kcmlen > stackbuf_size)
		kcmsg_base = kcmsg = sock_kदो_स्मृति(sk, kcmlen, GFP_KERNEL);
	अगर (kcmsg == शून्य)
		वापस -ENOMEM;

	/* Now copy them over neatly. */
	स_रखो(kcmsg, 0, kcmlen);
	ucmsg = CMSG_COMPAT_FIRSTHDR(kmsg);
	जबतक (ucmsg != शून्य) अणु
		काष्ठा compat_cmsghdr cmsg;
		अगर (copy_from_user(&cmsg, ucmsg, माप(cmsg)))
			जाओ Efault;
		अगर (!CMSG_COMPAT_OK(cmsg.cmsg_len, ucmsg, kmsg))
			जाओ Einval;
		पंचांगp = ((cmsg.cmsg_len - माप(*ucmsg)) + माप(काष्ठा cmsghdr));
		अगर ((अक्षर *)kcmsg_base + kcmlen - (अक्षर *)kcmsg < CMSG_ALIGN(पंचांगp))
			जाओ Einval;
		kcmsg->cmsg_len = पंचांगp;
		kcmsg->cmsg_level = cmsg.cmsg_level;
		kcmsg->cmsg_type = cmsg.cmsg_type;
		पंचांगp = CMSG_ALIGN(पंचांगp);
		अगर (copy_from_user(CMSG_DATA(kcmsg),
				   CMSG_COMPAT_DATA(ucmsg),
				   (cmsg.cmsg_len - माप(*ucmsg))))
			जाओ Efault;

		/* Advance. */
		kcmsg = (काष्ठा cmsghdr *)((अक्षर *)kcmsg + पंचांगp);
		ucmsg = cmsg_compat_nxthdr(kmsg, ucmsg, cmsg.cmsg_len);
	पूर्ण

	/*
	 * check the length of messages copied in is the same as the
	 * what we get from the first loop
	 */
	अगर ((अक्षर *)kcmsg - (अक्षर *)kcmsg_base != kcmlen)
		जाओ Einval;

	/* Ok, looks like we made it.  Hook it up and वापस success. */
	kmsg->msg_control = kcmsg_base;
	kmsg->msg_controllen = kcmlen;
	वापस 0;

Einval:
	err = -EINVAL;
Efault:
	अगर (kcmsg_base != (काष्ठा cmsghdr *)stackbuf)
		sock_kमुक्त_s(sk, kcmsg_base, kcmlen);
	वापस err;
पूर्ण

पूर्णांक put_cmsg_compat(काष्ठा msghdr *kmsg, पूर्णांक level, पूर्णांक type, पूर्णांक len, व्योम *data)
अणु
	काष्ठा compat_cmsghdr __user *cm = (काष्ठा compat_cmsghdr __user *) kmsg->msg_control;
	काष्ठा compat_cmsghdr cmhdr;
	काष्ठा old_समयval32 ctv;
	काष्ठा old_बारpec32 cts[3];
	पूर्णांक cmlen;

	अगर (cm == शून्य || kmsg->msg_controllen < माप(*cm)) अणु
		kmsg->msg_flags |= MSG_CTRUNC;
		वापस 0; /* XXX: वापस error? check spec. */
	पूर्ण

	अगर (!COMPAT_USE_64BIT_TIME) अणु
		अगर (level == SOL_SOCKET && type == SO_TIMESTAMP_OLD) अणु
			काष्ठा __kernel_old_समयval *tv = (काष्ठा __kernel_old_समयval *)data;
			ctv.tv_sec = tv->tv_sec;
			ctv.tv_usec = tv->tv_usec;
			data = &ctv;
			len = माप(ctv);
		पूर्ण
		अगर (level == SOL_SOCKET &&
		    (type == SO_TIMESTAMPNS_OLD || type == SO_TIMESTAMPING_OLD)) अणु
			पूर्णांक count = type == SO_TIMESTAMPNS_OLD ? 1 : 3;
			पूर्णांक i;
			काष्ठा __kernel_old_बारpec *ts = data;
			क्रम (i = 0; i < count; i++) अणु
				cts[i].tv_sec = ts[i].tv_sec;
				cts[i].tv_nsec = ts[i].tv_nsec;
			पूर्ण
			data = &cts;
			len = माप(cts[0]) * count;
		पूर्ण
	पूर्ण

	cmlen = CMSG_COMPAT_LEN(len);
	अगर (kmsg->msg_controllen < cmlen) अणु
		kmsg->msg_flags |= MSG_CTRUNC;
		cmlen = kmsg->msg_controllen;
	पूर्ण
	cmhdr.cmsg_level = level;
	cmhdr.cmsg_type = type;
	cmhdr.cmsg_len = cmlen;

	अगर (copy_to_user(cm, &cmhdr, माप cmhdr))
		वापस -EFAULT;
	अगर (copy_to_user(CMSG_COMPAT_DATA(cm), data, cmlen - माप(काष्ठा compat_cmsghdr)))
		वापस -EFAULT;
	cmlen = CMSG_COMPAT_SPACE(len);
	अगर (kmsg->msg_controllen < cmlen)
		cmlen = kmsg->msg_controllen;
	kmsg->msg_control += cmlen;
	kmsg->msg_controllen -= cmlen;
	वापस 0;
पूर्ण

अटल पूर्णांक scm_max_fds_compat(काष्ठा msghdr *msg)
अणु
	अगर (msg->msg_controllen <= माप(काष्ठा compat_cmsghdr))
		वापस 0;
	वापस (msg->msg_controllen - माप(काष्ठा compat_cmsghdr)) / माप(पूर्णांक);
पूर्ण

व्योम scm_detach_fds_compat(काष्ठा msghdr *msg, काष्ठा scm_cookie *scm)
अणु
	काष्ठा compat_cmsghdr __user *cm =
		(काष्ठा compat_cmsghdr __user *)msg->msg_control;
	अचिन्हित पूर्णांक o_flags = (msg->msg_flags & MSG_CMSG_CLOEXEC) ? O_CLOEXEC : 0;
	पूर्णांक fdmax = min_t(पूर्णांक, scm_max_fds_compat(msg), scm->fp->count);
	पूर्णांक __user *cmsg_data = CMSG_COMPAT_DATA(cm);
	पूर्णांक err = 0, i;

	क्रम (i = 0; i < fdmax; i++) अणु
		err = receive_fd_user(scm->fp->fp[i], cmsg_data + i, o_flags);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	अगर (i > 0) अणु
		पूर्णांक cmlen = CMSG_COMPAT_LEN(i * माप(पूर्णांक));

		err = put_user(SOL_SOCKET, &cm->cmsg_level);
		अगर (!err)
			err = put_user(SCM_RIGHTS, &cm->cmsg_type);
		अगर (!err)
			err = put_user(cmlen, &cm->cmsg_len);
		अगर (!err) अणु
			cmlen = CMSG_COMPAT_SPACE(i * माप(पूर्णांक));
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

/* Argument list sizes क्रम compat_sys_socketcall */
#घोषणा AL(x) ((x) * माप(u32))
अटल अचिन्हित अक्षर nas[21] = अणु
	AL(0), AL(3), AL(3), AL(3), AL(2), AL(3),
	AL(3), AL(3), AL(4), AL(4), AL(4), AL(6),
	AL(6), AL(2), AL(5), AL(5), AL(3), AL(3),
	AL(4), AL(5), AL(4)
पूर्ण;
#अघोषित AL

अटल अंतरभूत दीर्घ __compat_sys_sendmsg(पूर्णांक fd,
					काष्ठा compat_msghdr __user *msg,
					अचिन्हित पूर्णांक flags)
अणु
	वापस __sys_sendmsg(fd, (काष्ठा user_msghdr __user *)msg,
			     flags | MSG_CMSG_COMPAT, false);
पूर्ण

COMPAT_SYSCALL_DEFINE3(sendmsg, पूर्णांक, fd, काष्ठा compat_msghdr __user *, msg,
		       अचिन्हित पूर्णांक, flags)
अणु
	वापस __compat_sys_sendmsg(fd, msg, flags);
पूर्ण

अटल अंतरभूत दीर्घ __compat_sys_sendmmsg(पूर्णांक fd,
					 काष्ठा compat_mmsghdr __user *mmsg,
					 अचिन्हित पूर्णांक vlen, अचिन्हित पूर्णांक flags)
अणु
	वापस __sys_sendmmsg(fd, (काष्ठा mmsghdr __user *)mmsg, vlen,
			      flags | MSG_CMSG_COMPAT, false);
पूर्ण

COMPAT_SYSCALL_DEFINE4(sendmmsg, पूर्णांक, fd, काष्ठा compat_mmsghdr __user *, mmsg,
		       अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags)
अणु
	वापस __compat_sys_sendmmsg(fd, mmsg, vlen, flags);
पूर्ण

अटल अंतरभूत दीर्घ __compat_sys_recvmsg(पूर्णांक fd,
					काष्ठा compat_msghdr __user *msg,
					अचिन्हित पूर्णांक flags)
अणु
	वापस __sys_recvmsg(fd, (काष्ठा user_msghdr __user *)msg,
			     flags | MSG_CMSG_COMPAT, false);
पूर्ण

COMPAT_SYSCALL_DEFINE3(recvmsg, पूर्णांक, fd, काष्ठा compat_msghdr __user *, msg,
		       अचिन्हित पूर्णांक, flags)
अणु
	वापस __compat_sys_recvmsg(fd, msg, flags);
पूर्ण

अटल अंतरभूत दीर्घ __compat_sys_recvfrom(पूर्णांक fd, व्योम __user *buf,
					 compat_माप_प्रकार len, अचिन्हित पूर्णांक flags,
					 काष्ठा sockaddr __user *addr,
					 पूर्णांक __user *addrlen)
अणु
	वापस __sys_recvfrom(fd, buf, len, flags | MSG_CMSG_COMPAT, addr,
			      addrlen);
पूर्ण

COMPAT_SYSCALL_DEFINE4(recv, पूर्णांक, fd, व्योम __user *, buf, compat_माप_प्रकार, len, अचिन्हित पूर्णांक, flags)
अणु
	वापस __compat_sys_recvfrom(fd, buf, len, flags, शून्य, शून्य);
पूर्ण

COMPAT_SYSCALL_DEFINE6(recvfrom, पूर्णांक, fd, व्योम __user *, buf, compat_माप_प्रकार, len,
		       अचिन्हित पूर्णांक, flags, काष्ठा sockaddr __user *, addr,
		       पूर्णांक __user *, addrlen)
अणु
	वापस __compat_sys_recvfrom(fd, buf, len, flags, addr, addrlen);
पूर्ण

COMPAT_SYSCALL_DEFINE5(recvmmsg_समय64, पूर्णांक, fd, काष्ठा compat_mmsghdr __user *, mmsg,
		       अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags,
		       काष्ठा __kernel_बारpec __user *, समयout)
अणु
	वापस __sys_recvmmsg(fd, (काष्ठा mmsghdr __user *)mmsg, vlen,
			      flags | MSG_CMSG_COMPAT, समयout, शून्य);
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
COMPAT_SYSCALL_DEFINE5(recvmmsg_समय32, पूर्णांक, fd, काष्ठा compat_mmsghdr __user *, mmsg,
		       अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags,
		       काष्ठा old_बारpec32 __user *, समयout)
अणु
	वापस __sys_recvmmsg(fd, (काष्ठा mmsghdr __user *)mmsg, vlen,
			      flags | MSG_CMSG_COMPAT, शून्य, समयout);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE2(socketcall, पूर्णांक, call, u32 __user *, args)
अणु
	u32 a[AUDITSC_ARGS];
	अचिन्हित पूर्णांक len;
	u32 a0, a1;
	पूर्णांक ret;

	अगर (call < SYS_SOCKET || call > SYS_SENDMMSG)
		वापस -EINVAL;
	len = nas[call];
	अगर (len > माप(a))
		वापस -EINVAL;

	अगर (copy_from_user(a, args, len))
		वापस -EFAULT;

	ret = audit_socketcall_compat(len / माप(a[0]), a);
	अगर (ret)
		वापस ret;

	a0 = a[0];
	a1 = a[1];

	चयन (call) अणु
	हाल SYS_SOCKET:
		ret = __sys_socket(a0, a1, a[2]);
		अवरोध;
	हाल SYS_BIND:
		ret = __sys_bind(a0, compat_ptr(a1), a[2]);
		अवरोध;
	हाल SYS_CONNECT:
		ret = __sys_connect(a0, compat_ptr(a1), a[2]);
		अवरोध;
	हाल SYS_LISTEN:
		ret = __sys_listen(a0, a1);
		अवरोध;
	हाल SYS_ACCEPT:
		ret = __sys_accept4(a0, compat_ptr(a1), compat_ptr(a[2]), 0);
		अवरोध;
	हाल SYS_GETSOCKNAME:
		ret = __sys_माला_लोockname(a0, compat_ptr(a1), compat_ptr(a[2]));
		अवरोध;
	हाल SYS_GETPEERNAME:
		ret = __sys_getpeername(a0, compat_ptr(a1), compat_ptr(a[2]));
		अवरोध;
	हाल SYS_SOCKETPAIR:
		ret = __sys_socketpair(a0, a1, a[2], compat_ptr(a[3]));
		अवरोध;
	हाल SYS_SEND:
		ret = __sys_sendto(a0, compat_ptr(a1), a[2], a[3], शून्य, 0);
		अवरोध;
	हाल SYS_SENDTO:
		ret = __sys_sendto(a0, compat_ptr(a1), a[2], a[3],
				   compat_ptr(a[4]), a[5]);
		अवरोध;
	हाल SYS_RECV:
		ret = __compat_sys_recvfrom(a0, compat_ptr(a1), a[2], a[3],
					    शून्य, शून्य);
		अवरोध;
	हाल SYS_RECVFROM:
		ret = __compat_sys_recvfrom(a0, compat_ptr(a1), a[2], a[3],
					    compat_ptr(a[4]),
					    compat_ptr(a[5]));
		अवरोध;
	हाल SYS_SHUTDOWN:
		ret = __sys_shutकरोwn(a0, a1);
		अवरोध;
	हाल SYS_SETSOCKOPT:
		ret = __sys_setsockopt(a0, a1, a[2], compat_ptr(a[3]), a[4]);
		अवरोध;
	हाल SYS_GETSOCKOPT:
		ret = __sys_माला_लोockopt(a0, a1, a[2], compat_ptr(a[3]),
				       compat_ptr(a[4]));
		अवरोध;
	हाल SYS_SENDMSG:
		ret = __compat_sys_sendmsg(a0, compat_ptr(a1), a[2]);
		अवरोध;
	हाल SYS_SENDMMSG:
		ret = __compat_sys_sendmmsg(a0, compat_ptr(a1), a[2], a[3]);
		अवरोध;
	हाल SYS_RECVMSG:
		ret = __compat_sys_recvmsg(a0, compat_ptr(a1), a[2]);
		अवरोध;
	हाल SYS_RECVMMSG:
		ret = __sys_recvmmsg(a0, compat_ptr(a1), a[2],
				     a[3] | MSG_CMSG_COMPAT, शून्य,
				     compat_ptr(a[4]));
		अवरोध;
	हाल SYS_ACCEPT4:
		ret = __sys_accept4(a0, compat_ptr(a1), compat_ptr(a[2]), a[3]);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
