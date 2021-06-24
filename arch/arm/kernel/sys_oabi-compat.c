<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/kernel/sys_oabi-compat.c
 *
 *  Compatibility wrappers क्रम syscalls that are used from
 *  old ABI user space binaries with an EABI kernel.
 *
 *  Author:	Nicolas Pitre
 *  Created:	Oct 7, 2005
 *  Copyright:	MontaVista Software, Inc.
 */

/*
 * The legacy ABI and the new ARM EABI have dअगरferent rules making some
 * syscalls incompatible especially with काष्ठाure arguments.
 * Most notably, Eabi says 64-bit members should be 64-bit aligned instead of
 * simply word aligned.  EABI also pads काष्ठाures to the size of the largest
 * member it contains instead of the invariant 32-bit.
 *
 * The following syscalls are affected:
 *
 * sys_stat64:
 * sys_lstat64:
 * sys_ख_स्थिति64:
 * sys_ख_स्थितिat64:
 *
 *   काष्ठा stat64 has dअगरferent sizes and some members are shअगरted
 *   Compatibility wrappers are needed क्रम them and provided below.
 *
 * sys_fcntl64:
 *
 *   काष्ठा flock64 has dअगरferent sizes and some members are shअगरted
 *   A compatibility wrapper is needed and provided below.
 *
 * sys_statfs64:
 * sys_ख_स्थितिfs64:
 *
 *   काष्ठा statfs64 has extra padding with EABI growing its size from
 *   84 to 88.  This काष्ठा is now __attribute__((packed,aligned(4)))
 *   with a small assembly wrapper to क्रमce the sz argument to 84 अगर it is 88
 *   to aव्योम copying the extra padding over user space unexpecting it.
 *
 * sys_newuname:
 *
 *   काष्ठा new_utsname has no padding with EABI.  No problem there.
 *
 * sys_epoll_ctl:
 * sys_epoll_रुको:
 *
 *   काष्ठा epoll_event has its second member shअगरted also affecting the
 *   काष्ठाure size. Compatibility wrappers are needed and provided below.
 *
 * sys_ipc:
 * sys_semop:
 * sys_semसमयकरोp:
 *
 *   काष्ठा sembuf loses its padding with EABI.  Since arrays of them are
 *   used they have to be copyed to हटाओ the padding. Compatibility wrappers
 *   provided below.
 *
 * sys_bind:
 * sys_connect:
 * sys_sendmsg:
 * sys_sendto:
 * sys_socketcall:
 *
 *   काष्ठा sockaddr_un loses its padding with EABI.  Since the size of the
 *   काष्ठाure is used as a validation test in unix_mkname(), we need to
 *   change the length argument to 110 whenever it is 112.  Compatibility
 *   wrappers provided below.
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/cred.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/eventpoll.h>
#समावेश <linux/sem.h>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/ipc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

काष्ठा oldabi_stat64 अणु
	अचिन्हित दीर्घ दीर्घ st_dev;
	अचिन्हित पूर्णांक	__pad1;
	अचिन्हित दीर्घ	__st_ino;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;

	अचिन्हित दीर्घ	st_uid;
	अचिन्हित दीर्घ	st_gid;

	अचिन्हित दीर्घ दीर्घ st_rdev;
	अचिन्हित पूर्णांक	__pad2;

	दीर्घ दीर्घ	st_size;
	अचिन्हित दीर्घ	st_blksize;
	अचिन्हित दीर्घ दीर्घ st_blocks;

	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;

	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;

	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;

	अचिन्हित दीर्घ दीर्घ st_ino;
पूर्ण __attribute__ ((packed,aligned(4)));

अटल दीर्घ cp_oldabi_stat64(काष्ठा kstat *stat,
			     काष्ठा oldabi_stat64 __user *statbuf)
अणु
	काष्ठा oldabi_stat64 पंचांगp;

	पंचांगp.st_dev = huge_encode_dev(stat->dev);
	पंचांगp.__pad1 = 0;
	पंचांगp.__st_ino = stat->ino;
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = stat->nlink;
	पंचांगp.st_uid = from_kuid_munged(current_user_ns(), stat->uid);
	पंचांगp.st_gid = from_kgid_munged(current_user_ns(), stat->gid);
	पंचांगp.st_rdev = huge_encode_dev(stat->rdev);
	पंचांगp.st_size = stat->size;
	पंचांगp.st_blocks = stat->blocks;
	पंचांगp.__pad2 = 0;
	पंचांगp.st_blksize = stat->blksize;
	पंचांगp.st_aसमय = stat->aसमय.tv_sec;
	पंचांगp.st_aसमय_nsec = stat->aसमय.tv_nsec;
	पंचांगp.st_mसमय = stat->mसमय.tv_sec;
	पंचांगp.st_mसमय_nsec = stat->mसमय.tv_nsec;
	पंचांगp.st_स_समय = stat->स_समय.tv_sec;
	पंचांगp.st_स_समय_nsec = stat->स_समय.tv_nsec;
	पंचांगp.st_ino = stat->ino;
	वापस copy_to_user(statbuf,&पंचांगp,माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_stat64(स्थिर अक्षर __user * filename,
				काष्ठा oldabi_stat64 __user * statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_stat(filename, &stat);
	अगर (!error)
		error = cp_oldabi_stat64(&stat, statbuf);
	वापस error;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_lstat64(स्थिर अक्षर __user * filename,
				 काष्ठा oldabi_stat64 __user * statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_lstat(filename, &stat);
	अगर (!error)
		error = cp_oldabi_stat64(&stat, statbuf);
	वापस error;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_ख_स्थिति64(अचिन्हित दीर्घ fd,
				 काष्ठा oldabi_stat64 __user * statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);
	अगर (!error)
		error = cp_oldabi_stat64(&stat, statbuf);
	वापस error;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_ख_स्थितिat64(पूर्णांक dfd,
				   स्थिर अक्षर __user *filename,
				   काष्ठा oldabi_stat64  __user *statbuf,
				   पूर्णांक flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_oldabi_stat64(&stat, statbuf);
पूर्ण

काष्ठा oabi_flock64 अणु
	लघु	l_type;
	लघु	l_whence;
	loff_t	l_start;
	loff_t	l_len;
	pid_t	l_pid;
पूर्ण __attribute__ ((packed,aligned(4)));

अटल दीर्घ करो_locks(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा flock64 kernel;
	काष्ठा oabi_flock64 user;
	mm_segment_t fs;
	दीर्घ ret;

	अगर (copy_from_user(&user, (काष्ठा oabi_flock64 __user *)arg,
			   माप(user)))
		वापस -EFAULT;
	kernel.l_type	= user.l_type;
	kernel.l_whence	= user.l_whence;
	kernel.l_start	= user.l_start;
	kernel.l_len	= user.l_len;
	kernel.l_pid	= user.l_pid;

	fs = get_fs();
	set_fs(KERNEL_DS);
	ret = sys_fcntl64(fd, cmd, (अचिन्हित दीर्घ)&kernel);
	set_fs(fs);

	अगर (!ret && (cmd == F_GETLK64 || cmd == F_OFD_GETLK)) अणु
		user.l_type	= kernel.l_type;
		user.l_whence	= kernel.l_whence;
		user.l_start	= kernel.l_start;
		user.l_len	= kernel.l_len;
		user.l_pid	= kernel.l_pid;
		अगर (copy_to_user((काष्ठा oabi_flock64 __user *)arg,
				 &user, माप(user)))
			ret = -EFAULT;
	पूर्ण
	वापस ret;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_fcntl64(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल F_OFD_GETLK:
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
	हाल F_GETLK64:
	हाल F_SETLK64:
	हाल F_SETLKW64:
		वापस करो_locks(fd, cmd, arg);

	शेष:
		वापस sys_fcntl64(fd, cmd, arg);
	पूर्ण
पूर्ण

काष्ठा oabi_epoll_event अणु
	__u32 events;
	__u64 data;
पूर्ण __attribute__ ((packed,aligned(4)));

#अगर_घोषित CONFIG_EPOLL
यंत्रlinkage दीर्घ sys_oabi_epoll_ctl(पूर्णांक epfd, पूर्णांक op, पूर्णांक fd,
				   काष्ठा oabi_epoll_event __user *event)
अणु
	काष्ठा oabi_epoll_event user;
	काष्ठा epoll_event kernel;

	अगर (ep_op_has_event(op) &&
	    copy_from_user(&user, event, माप(user)))
		वापस -EFAULT;

	kernel.events = user.events;
	kernel.data   = user.data;

	वापस करो_epoll_ctl(epfd, op, fd, &kernel, false);
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_epoll_रुको(पूर्णांक epfd,
				    काष्ठा oabi_epoll_event __user *events,
				    पूर्णांक maxevents, पूर्णांक समयout)
अणु
	काष्ठा epoll_event *kbuf;
	काष्ठा oabi_epoll_event e;
	mm_segment_t fs;
	दीर्घ ret, err, i;

	अगर (maxevents <= 0 ||
			maxevents > (पूर्णांक_उच्च/माप(*kbuf)) ||
			maxevents > (पूर्णांक_उच्च/माप(*events)))
		वापस -EINVAL;
	अगर (!access_ok(events, माप(*events) * maxevents))
		वापस -EFAULT;
	kbuf = kदो_स्मृति_array(maxevents, माप(*kbuf), GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;
	fs = get_fs();
	set_fs(KERNEL_DS);
	ret = sys_epoll_रुको(epfd, kbuf, maxevents, समयout);
	set_fs(fs);
	err = 0;
	क्रम (i = 0; i < ret; i++) अणु
		e.events = kbuf[i].events;
		e.data = kbuf[i].data;
		err = __copy_to_user(events, &e, माप(e));
		अगर (err)
			अवरोध;
		events++;
	पूर्ण
	kमुक्त(kbuf);
	वापस err ? -EFAULT : ret;
पूर्ण
#अन्यथा
यंत्रlinkage दीर्घ sys_oabi_epoll_ctl(पूर्णांक epfd, पूर्णांक op, पूर्णांक fd,
				   काष्ठा oabi_epoll_event __user *event)
अणु
	वापस -EINVAL;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_epoll_रुको(पूर्णांक epfd,
				    काष्ठा oabi_epoll_event __user *events,
				    पूर्णांक maxevents, पूर्णांक समयout)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

काष्ठा oabi_sembuf अणु
	अचिन्हित लघु	sem_num;
	लघु		sem_op;
	लघु		sem_flg;
	अचिन्हित लघु	__pad;
पूर्ण;

यंत्रlinkage दीर्घ sys_oabi_semसमयकरोp(पूर्णांक semid,
				    काष्ठा oabi_sembuf __user *tsops,
				    अचिन्हित nsops,
				    स्थिर काष्ठा old_बारpec32 __user *समयout)
अणु
	काष्ठा sembuf *sops;
	काष्ठा old_बारpec32 local_समयout;
	दीर्घ err;
	पूर्णांक i;

	अगर (nsops < 1 || nsops > SEMOPM)
		वापस -EINVAL;
	अगर (!access_ok(tsops, माप(*tsops) * nsops))
		वापस -EFAULT;
	sops = kदो_स्मृति_array(nsops, माप(*sops), GFP_KERNEL);
	अगर (!sops)
		वापस -ENOMEM;
	err = 0;
	क्रम (i = 0; i < nsops; i++) अणु
		काष्ठा oabi_sembuf osb;
		err |= __copy_from_user(&osb, tsops, माप(osb));
		sops[i].sem_num = osb.sem_num;
		sops[i].sem_op = osb.sem_op;
		sops[i].sem_flg = osb.sem_flg;
		tsops++;
	पूर्ण
	अगर (समयout) अणु
		/* copy this as well beक्रमe changing करोमुख्य protection */
		err |= copy_from_user(&local_समयout, समयout, माप(*समयout));
		समयout = &local_समयout;
	पूर्ण
	अगर (err) अणु
		err = -EFAULT;
	पूर्ण अन्यथा अणु
		mm_segment_t fs = get_fs();
		set_fs(KERNEL_DS);
		err = sys_semसमयकरोp_समय32(semid, sops, nsops, समयout);
		set_fs(fs);
	पूर्ण
	kमुक्त(sops);
	वापस err;
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_semop(पूर्णांक semid, काष्ठा oabi_sembuf __user *tsops,
			       अचिन्हित nsops)
अणु
	वापस sys_oabi_semसमयकरोp(semid, tsops, nsops, शून्य);
पूर्ण

यंत्रlinkage पूर्णांक sys_oabi_ipc(uपूर्णांक call, पूर्णांक first, पूर्णांक second, पूर्णांक third,
			    व्योम __user *ptr, दीर्घ fअगरth)
अणु
	चयन (call & 0xffff) अणु
	हाल SEMOP:
		वापस  sys_oabi_semसमयकरोp(first,
					    (काष्ठा oabi_sembuf __user *)ptr,
					    second, शून्य);
	हाल SEMTIMEDOP:
		वापस  sys_oabi_semसमयकरोp(first,
					    (काष्ठा oabi_sembuf __user *)ptr,
					    second,
					    (स्थिर काष्ठा old_बारpec32 __user *)fअगरth);
	शेष:
		वापस sys_ipc(call, first, second, third, ptr, fअगरth);
	पूर्ण
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_bind(पूर्णांक fd, काष्ठा sockaddr __user *addr, पूर्णांक addrlen)
अणु
	sa_family_t sa_family;
	अगर (addrlen == 112 &&
	    get_user(sa_family, &addr->sa_family) == 0 &&
	    sa_family == AF_UNIX)
			addrlen = 110;
	वापस sys_bind(fd, addr, addrlen);
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_connect(पूर्णांक fd, काष्ठा sockaddr __user *addr, पूर्णांक addrlen)
अणु
	sa_family_t sa_family;
	अगर (addrlen == 112 &&
	    get_user(sa_family, &addr->sa_family) == 0 &&
	    sa_family == AF_UNIX)
			addrlen = 110;
	वापस sys_connect(fd, addr, addrlen);
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_sendto(पूर्णांक fd, व्योम __user *buff,
				माप_प्रकार len, अचिन्हित flags,
				काष्ठा sockaddr __user *addr,
				पूर्णांक addrlen)
अणु
	sa_family_t sa_family;
	अगर (addrlen == 112 &&
	    get_user(sa_family, &addr->sa_family) == 0 &&
	    sa_family == AF_UNIX)
			addrlen = 110;
	वापस sys_sendto(fd, buff, len, flags, addr, addrlen);
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_sendmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg, अचिन्हित flags)
अणु
	काष्ठा sockaddr __user *addr;
	पूर्णांक msg_namelen;
	sa_family_t sa_family;
	अगर (msg &&
	    get_user(msg_namelen, &msg->msg_namelen) == 0 &&
	    msg_namelen == 112 &&
	    get_user(addr, &msg->msg_name) == 0 &&
	    get_user(sa_family, &addr->sa_family) == 0 &&
	    sa_family == AF_UNIX)
	अणु
		/*
		 * HACK ALERT: there is a limit to how much backward bending
		 * we should करो क्रम what is actually a transitional
		 * compatibility layer.  This alपढ़ोy has known flaws with
		 * a few ioctls that we करोn't पूर्णांकend to fix.  Thereक्रमe
		 * consider this blatent hack as another one... and take care
		 * to run क्रम cover.  In most हालs it will "just work fine".
		 * If it करोesn't, well, tough.
		 */
		put_user(110, &msg->msg_namelen);
	पूर्ण
	वापस sys_sendmsg(fd, msg, flags);
पूर्ण

यंत्रlinkage दीर्घ sys_oabi_socketcall(पूर्णांक call, अचिन्हित दीर्घ __user *args)
अणु
	अचिन्हित दीर्घ r = -EFAULT, a[6];

	चयन (call) अणु
	हाल SYS_BIND:
		अगर (copy_from_user(a, args, 3 * माप(दीर्घ)) == 0)
			r = sys_oabi_bind(a[0], (काष्ठा sockaddr __user *)a[1], a[2]);
		अवरोध;
	हाल SYS_CONNECT:
		अगर (copy_from_user(a, args, 3 * माप(दीर्घ)) == 0)
			r = sys_oabi_connect(a[0], (काष्ठा sockaddr __user *)a[1], a[2]);
		अवरोध;
	हाल SYS_SENDTO:
		अगर (copy_from_user(a, args, 6 * माप(दीर्घ)) == 0)
			r = sys_oabi_sendto(a[0], (व्योम __user *)a[1], a[2], a[3],
					    (काष्ठा sockaddr __user *)a[4], a[5]);
		अवरोध;
	हाल SYS_SENDMSG:
		अगर (copy_from_user(a, args, 3 * माप(दीर्घ)) == 0)
			r = sys_oabi_sendmsg(a[0], (काष्ठा user_msghdr __user *)a[1], a[2]);
		अवरोध;
	शेष:
		r = sys_socketcall(call, args);
	पूर्ण

	वापस r;
पूर्ण
