<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <linux/fभाग.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mount.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/sysmacros.h>
#समावेश <sys/un.h>
#समावेश <sys/types.h>
#समावेश <sys/eventfd.h>
#समावेश <poll.h>
#समावेश <os.h>

अटल व्योम copy_stat(काष्ठा uml_stat *dst, स्थिर काष्ठा stat64 *src)
अणु
	*dst = ((काष्ठा uml_stat) अणु
		.ust_dev     = src->st_dev,     /* device */
		.ust_ino     = src->st_ino,     /* inode */
		.ust_mode    = src->st_mode,    /* protection */
		.ust_nlink   = src->st_nlink,   /* number of hard links */
		.ust_uid     = src->st_uid,     /* user ID of owner */
		.ust_gid     = src->st_gid,     /* group ID of owner */
		.ust_size    = src->st_size,    /* total size, in bytes */
		.ust_blksize = src->st_blksize, /* blocksize क्रम filesys I/O */
		.ust_blocks  = src->st_blocks,  /* number of blocks allocated */
		.ust_aसमय   = src->st_aसमय,   /* समय of last access */
		.ust_mसमय   = src->st_mसमय,   /* समय of last modअगरication */
		.ust_स_समय   = src->st_स_समय,   /* समय of last change */
	पूर्ण);
पूर्ण

पूर्णांक os_stat_fd(स्थिर पूर्णांक fd, काष्ठा uml_stat *ubuf)
अणु
	काष्ठा stat64 sbuf;
	पूर्णांक err;

	CATCH_EINTR(err = ख_स्थिति64(fd, &sbuf));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	अगर (ubuf != शून्य)
		copy_stat(ubuf, &sbuf);
	वापस err;
पूर्ण

पूर्णांक os_stat_file(स्थिर अक्षर *file_name, काष्ठा uml_stat *ubuf)
अणु
	काष्ठा stat64 sbuf;
	पूर्णांक err;

	CATCH_EINTR(err = stat64(file_name, &sbuf));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	अगर (ubuf != शून्य)
		copy_stat(ubuf, &sbuf);
	वापस err;
पूर्ण

पूर्णांक os_access(स्थिर अक्षर *file, पूर्णांक mode)
अणु
	पूर्णांक amode, err;

	amode = (mode & OS_ACC_R_OK ? R_OK : 0) |
		(mode & OS_ACC_W_OK ? W_OK : 0) |
		(mode & OS_ACC_X_OK ? X_OK : 0) |
		(mode & OS_ACC_F_OK ? F_OK : 0);

	err = access(file, amode);
	अगर (err < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

/* FIXME? required only by hostaudio (because it passes ioctls verbatim) */
पूर्णांक os_ioctl_generic(पूर्णांक fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;

	err = ioctl(fd, cmd, arg);
	अगर (err < 0)
		वापस -त्रुटि_सं;

	वापस err;
पूर्ण

/* FIXME: ensure namebuf in os_get_अगर_name is big enough */
पूर्णांक os_get_अगरname(पूर्णांक fd, अक्षर* namebuf)
अणु
	अगर (ioctl(fd, SIOCGIFNAME, namebuf) < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_set_slip(पूर्णांक fd)
अणु
	पूर्णांक disc, sencap;

	disc = N_SLIP;
	अगर (ioctl(fd, TIOCSETD, &disc) < 0)
		वापस -त्रुटि_सं;

	sencap = 0;
	अगर (ioctl(fd, SIOCSIFENCAP, &sencap) < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_mode_fd(पूर्णांक fd, पूर्णांक mode)
अणु
	पूर्णांक err;

	CATCH_EINTR(err = fchmod(fd, mode));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_file_type(अक्षर *file)
अणु
	काष्ठा uml_stat buf;
	पूर्णांक err;

	err = os_stat_file(file, &buf);
	अगर (err < 0)
		वापस err;

	अगर (S_ISसूची(buf.ust_mode))
		वापस OS_TYPE_सूची;
	अन्यथा अगर (S_ISLNK(buf.ust_mode))
		वापस OS_TYPE_SYMLINK;
	अन्यथा अगर (S_ISCHR(buf.ust_mode))
		वापस OS_TYPE_CHARDEV;
	अन्यथा अगर (S_ISBLK(buf.ust_mode))
		वापस OS_TYPE_BLOCKDEV;
	अन्यथा अगर (S_ISFIFO(buf.ust_mode))
		वापस OS_TYPE_FIFO;
	अन्यथा अगर (S_ISSOCK(buf.ust_mode))
		वापस OS_TYPE_SOCK;
	अन्यथा वापस OS_TYPE_खाता;
पूर्ण

पूर्णांक os_file_mode(स्थिर अक्षर *file, काष्ठा खोलोflags *mode_out)
अणु
	पूर्णांक err;

	*mode_out = OPENFLAGS();

	err = access(file, W_OK);
	अगर (err && (त्रुटि_सं != EACCES))
		वापस -त्रुटि_सं;
	अन्यथा अगर (!err)
		*mode_out = of_ग_लिखो(*mode_out);

	err = access(file, R_OK);
	अगर (err && (त्रुटि_सं != EACCES))
		वापस -त्रुटि_सं;
	अन्यथा अगर (!err)
		*mode_out = of_पढ़ो(*mode_out);

	वापस err;
पूर्ण

पूर्णांक os_खोलो_file(स्थिर अक्षर *file, काष्ठा खोलोflags flags, पूर्णांक mode)
अणु
	पूर्णांक fd, err, f = 0;

	अगर (flags.r && flags.w)
		f = O_RDWR;
	अन्यथा अगर (flags.r)
		f = O_RDONLY;
	अन्यथा अगर (flags.w)
		f = O_WRONLY;
	अन्यथा f = 0;

	अगर (flags.s)
		f |= O_SYNC;
	अगर (flags.c)
		f |= O_CREAT;
	अगर (flags.t)
		f |= O_TRUNC;
	अगर (flags.e)
		f |= O_EXCL;
	अगर (flags.a)
		f |= O_APPEND;

	fd = खोलो64(file, f, mode);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	अगर (flags.cl && fcntl(fd, F_SETFD, 1)) अणु
		err = -त्रुटि_सं;
		बंद(fd);
		वापस err;
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक os_connect_socket(स्थिर अक्षर *name)
अणु
	काष्ठा sockaddr_un sock;
	पूर्णांक fd, err;

	sock.sun_family = AF_UNIX;
	snम_लिखो(sock.sun_path, माप(sock.sun_path), "%s", name);

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	अगर (fd < 0) अणु
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	err = connect(fd, (काष्ठा sockaddr *) &sock, माप(sock));
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ out_बंद;
	पूर्ण

	वापस fd;

out_बंद:
	बंद(fd);
out:
	वापस err;
पूर्ण

व्योम os_बंद_file(पूर्णांक fd)
अणु
	बंद(fd);
पूर्ण
पूर्णांक os_fsync_file(पूर्णांक fd)
अणु
	अगर (fsync(fd) < 0)
	    वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक os_seek_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ offset)
अणु
	अचिन्हित दीर्घ दीर्घ actual;

	actual = lseek64(fd, offset, शुरू_से);
	अगर (actual != offset)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक os_पढ़ो_file(पूर्णांक fd, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n = पढ़ो(fd, buf, len);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण

पूर्णांक os_pपढ़ो_file(पूर्णांक fd, व्योम *buf, पूर्णांक len, अचिन्हित दीर्घ दीर्घ offset)
अणु
	पूर्णांक n = pपढ़ो(fd, buf, len, offset);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण

पूर्णांक os_ग_लिखो_file(पूर्णांक fd, स्थिर व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक n = ग_लिखो(fd, (व्योम *) buf, len);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण

पूर्णांक os_sync_file(पूर्णांक fd)
अणु
	पूर्णांक n = fdatasync(fd);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण

पूर्णांक os_pग_लिखो_file(पूर्णांक fd, स्थिर व्योम *buf, पूर्णांक len, अचिन्हित दीर्घ दीर्घ offset)
अणु
	पूर्णांक n = pग_लिखो(fd, (व्योम *) buf, len, offset);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण


पूर्णांक os_file_size(स्थिर अक्षर *file, अचिन्हित दीर्घ दीर्घ *size_out)
अणु
	काष्ठा uml_stat buf;
	पूर्णांक err;

	err = os_stat_file(file, &buf);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Couldn't stat \"%s\" : err = %d\n", file,
		       -err);
		वापस err;
	पूर्ण

	अगर (S_ISBLK(buf.ust_mode)) अणु
		पूर्णांक fd;
		दीर्घ blocks;

		fd = खोलो(file, O_RDONLY, 0);
		अगर (fd < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "Couldn't open \"%s\", "
			       "errno = %d\n", file, त्रुटि_सं);
			वापस err;
		पूर्ण
		अगर (ioctl(fd, BLKGETSIZE, &blocks) < 0) अणु
			err = -त्रुटि_सं;
			prपूर्णांकk(UM_KERN_ERR "Couldn't get the block size of "
			       "\"%s\", errno = %d\n", file, त्रुटि_सं);
			बंद(fd);
			वापस err;
		पूर्ण
		*size_out = ((दीर्घ दीर्घ) blocks) * 512;
		बंद(fd);
	पूर्ण
	अन्यथा *size_out = buf.ust_size;

	वापस 0;
पूर्ण

पूर्णांक os_file_modसमय(स्थिर अक्षर *file, दीर्घ दीर्घ *modसमय)
अणु
	काष्ठा uml_stat buf;
	पूर्णांक err;

	err = os_stat_file(file, &buf);
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Couldn't stat \"%s\" : err = %d\n", file,
		       -err);
		वापस err;
	पूर्ण

	*modसमय = buf.ust_mसमय;
	वापस 0;
पूर्ण

पूर्णांक os_set_exec_बंद(पूर्णांक fd)
अणु
	पूर्णांक err;

	CATCH_EINTR(err = fcntl(fd, F_SETFD, FD_CLOEXEC));

	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस err;
पूर्ण

पूर्णांक os_pipe(पूर्णांक *fds, पूर्णांक stream, पूर्णांक बंद_on_exec)
अणु
	पूर्णांक err, type = stream ? SOCK_STREAM : SOCK_DGRAM;

	err = socketpair(AF_UNIX, type, 0, fds);
	अगर (err < 0)
		वापस -त्रुटि_सं;

	अगर (!बंद_on_exec)
		वापस 0;

	err = os_set_exec_बंद(fds[0]);
	अगर (err < 0)
		जाओ error;

	err = os_set_exec_बंद(fds[1]);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	prपूर्णांकk(UM_KERN_ERR "os_pipe : Setting FD_CLOEXEC failed, err = %d\n",
	       -err);
	बंद(fds[1]);
	बंद(fds[0]);
	वापस err;
पूर्ण

पूर्णांक os_set_fd_async(पूर्णांक fd)
अणु
	पूर्णांक err, flags;

	flags = fcntl(fd, F_GETFL);
	अगर (flags < 0)
		वापस -त्रुटि_सं;

	flags |= O_ASYNC | O_NONBLOCK;
	अगर (fcntl(fd, F_SETFL, flags) < 0) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "os_set_fd_async : failed to set O_ASYNC "
		       "and O_NONBLOCK on fd # %d, errno = %d\n", fd, त्रुटि_सं);
		वापस err;
	पूर्ण

	अगर ((fcntl(fd, F_SETSIG, SIGIO) < 0) ||
	    (fcntl(fd, F_SETOWN, os_getpid()) < 0)) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "os_set_fd_async : Failed to fcntl F_SETOWN "
		       "(or F_SETSIG) fd %d, errno = %d\n", fd, त्रुटि_सं);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक os_clear_fd_async(पूर्णांक fd)
अणु
	पूर्णांक flags;

	flags = fcntl(fd, F_GETFL);
	अगर (flags < 0)
		वापस -त्रुटि_सं;

	flags &= ~(O_ASYNC | O_NONBLOCK);
	अगर (fcntl(fd, F_SETFL, flags) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक os_set_fd_block(पूर्णांक fd, पूर्णांक blocking)
अणु
	पूर्णांक flags;

	flags = fcntl(fd, F_GETFL);
	अगर (flags < 0)
		वापस -त्रुटि_सं;

	अगर (blocking)
		flags &= ~O_NONBLOCK;
	अन्यथा
		flags |= O_NONBLOCK;

	अगर (fcntl(fd, F_SETFL, flags) < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_accept_connection(पूर्णांक fd)
अणु
	पूर्णांक new;

	new = accept(fd, शून्य, 0);
	अगर (new < 0)
		वापस -त्रुटि_सं;
	वापस new;
पूर्ण

#अगर_अघोषित SHUT_RD
#घोषणा SHUT_RD 0
#पूर्ण_अगर

#अगर_अघोषित SHUT_WR
#घोषणा SHUT_WR 1
#पूर्ण_अगर

#अगर_अघोषित SHUT_RDWR
#घोषणा SHUT_RDWR 2
#पूर्ण_अगर

पूर्णांक os_shutकरोwn_socket(पूर्णांक fd, पूर्णांक r, पूर्णांक w)
अणु
	पूर्णांक what, err;

	अगर (r && w)
		what = SHUT_RDWR;
	अन्यथा अगर (r)
		what = SHUT_RD;
	अन्यथा अगर (w)
		what = SHUT_WR;
	अन्यथा
		वापस -EINVAL;

	err = shutकरोwn(fd, what);
	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक os_rcv_fd(पूर्णांक fd, पूर्णांक *helper_pid_out)
अणु
	पूर्णांक new, n;
	अक्षर buf[CMSG_SPACE(माप(new))];
	काष्ठा msghdr msg;
	काष्ठा cmsghdr *cmsg;
	काष्ठा iovec iov;

	msg.msg_name = शून्य;
	msg.msg_namelen = 0;
	iov = ((काष्ठा iovec) अणु .iov_base  = helper_pid_out,
				.iov_len   = माप(*helper_pid_out) पूर्ण);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = माप(buf);
	msg.msg_flags = 0;

	n = recvmsg(fd, &msg, 0);
	अगर (n < 0)
		वापस -त्रुटि_सं;
	अन्यथा अगर (n != iov.iov_len)
		*helper_pid_out = -1;

	cmsg = CMSG_FIRSTHDR(&msg);
	अगर (cmsg == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "rcv_fd didn't receive anything, "
		       "error = %d\n", त्रुटि_सं);
		वापस -1;
	पूर्ण
	अगर ((cmsg->cmsg_level != SOL_SOCKET) ||
	    (cmsg->cmsg_type != SCM_RIGHTS)) अणु
		prपूर्णांकk(UM_KERN_ERR "rcv_fd didn't receive a descriptor\n");
		वापस -1;
	पूर्ण

	new = ((पूर्णांक *) CMSG_DATA(cmsg))[0];
	वापस new;
पूर्ण

पूर्णांक os_create_unix_socket(स्थिर अक्षर *file, पूर्णांक len, पूर्णांक बंद_on_exec)
अणु
	काष्ठा sockaddr_un addr;
	पूर्णांक sock, err;

	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	अगर (sock < 0)
		वापस -त्रुटि_सं;

	अगर (बंद_on_exec) अणु
		err = os_set_exec_बंद(sock);
		अगर (err < 0)
			prपूर्णांकk(UM_KERN_ERR "create_unix_socket : "
			       "close_on_exec failed, err = %d", -err);
	पूर्ण

	addr.sun_family = AF_UNIX;

	snम_लिखो(addr.sun_path, len, "%s", file);

	err = bind(sock, (काष्ठा sockaddr *) &addr, माप(addr));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	वापस sock;
पूर्ण

व्योम os_flush_मानक_निकास(व्योम)
अणु
	ख_साफ(मानक_निकास);
पूर्ण

पूर्णांक os_lock_file(पूर्णांक fd, पूर्णांक excl)
अणु
	पूर्णांक type = excl ? F_WRLCK : F_RDLCK;
	काष्ठा flock lock = ((काष्ठा flock) अणु .l_type	= type,
					      .l_whence	= शुरू_से,
					      .l_start	= 0,
					      .l_len	= 0 पूर्ण );
	पूर्णांक err, save;

	err = fcntl(fd, F_SETLK, &lock);
	अगर (!err)
		जाओ out;

	save = -त्रुटि_सं;
	err = fcntl(fd, F_GETLK, &lock);
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	prपूर्णांकk(UM_KERN_ERR "F_SETLK failed, file already locked by pid %d\n",
	       lock.l_pid);
	err = save;
 out:
	वापस err;
पूर्ण

अचिन्हित os_major(अचिन्हित दीर्घ दीर्घ dev)
अणु
	वापस major(dev);
पूर्ण

अचिन्हित os_minor(अचिन्हित दीर्घ दीर्घ dev)
अणु
	वापस minor(dev);
पूर्ण

अचिन्हित दीर्घ दीर्घ os_makedev(अचिन्हित major, अचिन्हित minor)
अणु
	वापस makedev(major, minor);
पूर्ण

पूर्णांक os_falloc_punch(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ offset, पूर्णांक len)
अणु
	पूर्णांक n = fallocate(fd, FALLOC_FL_PUNCH_HOLE|FALLOC_FL_KEEP_SIZE, offset, len);

	अगर (n < 0)
		वापस -त्रुटि_सं;
	वापस n;
पूर्ण

पूर्णांक os_eventfd(अचिन्हित पूर्णांक initval, पूर्णांक flags)
अणु
	पूर्णांक fd = eventfd(initval, flags);

	अगर (fd < 0)
		वापस -त्रुटि_सं;
	वापस fd;
पूर्ण

पूर्णांक os_sendmsg_fds(पूर्णांक fd, स्थिर व्योम *buf, अचिन्हित पूर्णांक len, स्थिर पूर्णांक *fds,
		   अचिन्हित पूर्णांक fds_num)
अणु
	काष्ठा iovec iov = अणु
		.iov_base = (व्योम *) buf,
		.iov_len = len,
	पूर्ण;
	जोड़ अणु
		अक्षर control[CMSG_SPACE(माप(*fds) * OS_SENDMSG_MAX_FDS)];
		काष्ठा cmsghdr align;
	पूर्ण u;
	अचिन्हित पूर्णांक fds_size = माप(*fds) * fds_num;
	काष्ठा msghdr msg = अणु
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = u.control,
		.msg_controllen = CMSG_SPACE(fds_size),
	पूर्ण;
	काष्ठा cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
	पूर्णांक err;

	अगर (fds_num > OS_SENDMSG_MAX_FDS)
		वापस -EINVAL;
	स_रखो(u.control, 0, माप(u.control));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(fds_size);
	स_नकल(CMSG_DATA(cmsg), fds, fds_size);
	err = sendmsg(fd, &msg, 0);

	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस err;
पूर्ण

पूर्णांक os_poll(अचिन्हित पूर्णांक n, स्थिर पूर्णांक *fds)
अणु
	/* currently need 2 FDs at most so aव्योम dynamic allocation */
	काष्ठा pollfd pollfds[2] = अणुपूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (n > ARRAY_SIZE(pollfds))
		वापस -EINVAL;

	क्रम (i = 0; i < n; i++) अणु
		pollfds[i].fd = fds[i];
		pollfds[i].events = POLLIN;
	पूर्ण

	ret = poll(pollfds, n, -1);
	अगर (ret < 0)
		वापस -त्रुटि_सं;

	/* Return the index of the available FD */
	क्रम (i = 0; i < n; i++) अणु
		अगर (pollfds[i].revents)
			वापस i;
	पूर्ण

	वापस -EIO;
पूर्ण
