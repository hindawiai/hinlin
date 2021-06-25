<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET		An implementation of the SOCKET network access protocol.
 *
 * Version:	@(#)socket.c	1.1.93	18/02/95
 *
 * Authors:	Orest Zborowski, <obz@Kodak.COM>
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 * Fixes:
 *		Anonymous	:	NOTSOCK/BADF cleanup. Error fix in
 *					shutकरोwn()
 *		Alan Cox	:	verअगरy_area() fixes
 *		Alan Cox	:	Removed DDI
 *		Jonathan Kamens	:	SOCK_DGRAM reconnect bug
 *		Alan Cox	:	Moved a load of checks to the very
 *					top level.
 *		Alan Cox	:	Move address काष्ठाures to/from user
 *					mode above the protocol layers.
 *		Rob Janssen	:	Allow 0 length sends.
 *		Alan Cox	:	Asynchronous I/O support (cribbed from the
 *					tty drivers).
 *		Niibe Yutaka	:	Asynchronous I/O क्रम ग_लिखोs (4.4BSD style)
 *		Jeff Uphoff	:	Made max number of sockets command-line
 *					configurable.
 *		Matti Aarnio	:	Made the number of sockets dynamic,
 *					to be allocated when needed, and mr.
 *					Uphoff's max is used as max to be
 *					allowed to allocate.
 *		Linus		:	Argh. हटाओd all the socket allocation
 *					altogether: it's in the inode now.
 *		Alan Cox	:	Made sock_alloc()/sock_release() खुला
 *					क्रम NetROM and future kernel nfsd type
 *					stuff.
 *		Alan Cox	:	sendmsg/recvmsg basics.
 *		Tom Dyas	:	Export net symbols.
 *		Marcin Dalecki	:	Fixed problems with CONFIG_NET="n".
 *		Alan Cox	:	Added thपढ़ो locking to sys_* calls
 *					क्रम sockets. May have errors at the
 *					moment.
 *		Kevin Buhr	:	Fixed the dumb errors in the above.
 *		Andi Kleen	:	Some small cleanups, optimizations,
 *					and fixed a copy_from_user() bug.
 *		Tigran Aivazian	:	sys_send(args) calls sys_sendto(args, शून्य, 0)
 *		Tigran Aivazian	:	Made listen(2) backlog sanity checks
 *					protocol-independent
 *
 *	This module is effectively the top level पूर्णांकerface to the BSD socket
 *	paradigm.
 *
 *	Based upon Swansea University Computer Society NET3.039
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/file.h>
#समावेश <linux/net.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/cache.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <linux/kmod.h>
#समावेश <linux/audit.h>
#समावेश <linux/wireless.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <linux/nospec.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

#समावेश <net/compat.h>
#समावेश <net/wext.h>
#समावेश <net/cls_cgroup.h>

#समावेश <net/sock.h>
#समावेश <linux/netfilter.h>

#समावेश <linux/अगर_tun.h>
#समावेश <linux/ipv6_route.h>
#समावेश <linux/route.h>
#समावेश <linux/termios.h>
#समावेश <linux/sockios.h>
#समावेश <net/busy_poll.h>
#समावेश <linux/errqueue.h>

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
अचिन्हित पूर्णांक sysctl_net_busy_पढ़ो __पढ़ो_mostly;
अचिन्हित पूर्णांक sysctl_net_busy_poll __पढ़ो_mostly;
#पूर्ण_अगर

अटल sमाप_प्रकार sock_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
अटल sमाप_प्रकार sock_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
अटल पूर्णांक sock_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);

अटल पूर्णांक sock_बंद(काष्ठा inode *inode, काष्ठा file *file);
अटल __poll_t sock_poll(काष्ठा file *file,
			      काष्ठा poll_table_काष्ठा *रुको);
अटल दीर्घ sock_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_sock_ioctl(काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर
अटल पूर्णांक sock_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on);
अटल sमाप_प्रकार sock_sendpage(काष्ठा file *file, काष्ठा page *page,
			     पूर्णांक offset, माप_प्रकार size, loff_t *ppos, पूर्णांक more);
अटल sमाप_प्रकार sock_splice_पढ़ो(काष्ठा file *file, loff_t *ppos,
				काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
				अचिन्हित पूर्णांक flags);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम sock_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा socket *sock = f->निजी_data;

	अगर (sock->ops->show_fdinfo)
		sock->ops->show_fdinfo(m, sock);
पूर्ण
#अन्यथा
#घोषणा sock_show_fdinfo शून्य
#पूर्ण_अगर

/*
 *	Socket files have a set of 'special' operations as well as the generic file ones. These don't appear
 *	in the operation काष्ठाures but are करोne directly via the socketcall() multiplexor.
 */

अटल स्थिर काष्ठा file_operations socket_file_ops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.पढ़ो_iter =	sock_पढ़ो_iter,
	.ग_लिखो_iter =	sock_ग_लिखो_iter,
	.poll =		sock_poll,
	.unlocked_ioctl = sock_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = compat_sock_ioctl,
#पूर्ण_अगर
	.mmap =		sock_mmap,
	.release =	sock_बंद,
	.fasync =	sock_fasync,
	.sendpage =	sock_sendpage,
	.splice_ग_लिखो = generic_splice_sendpage,
	.splice_पढ़ो =	sock_splice_पढ़ो,
	.show_fdinfo =	sock_show_fdinfo,
पूर्ण;

/*
 *	The protocol list. Each protocol is रेजिस्टरed in here.
 */

अटल DEFINE_SPINLOCK(net_family_lock);
अटल स्थिर काष्ठा net_proto_family __rcu *net_families[NPROTO] __पढ़ो_mostly;

/*
 * Support routines.
 * Move socket addresses back and क्रमth across the kernel/user
 * भागide and look after the messy bits.
 */

/**
 *	move_addr_to_kernel	-	copy a socket address पूर्णांकo kernel space
 *	@uaddr: Address in user space
 *	@kaddr: Address in kernel space
 *	@ulen: Length in user space
 *
 *	The address is copied पूर्णांकo kernel space. If the provided address is
 *	too दीर्घ an error code of -EINVAL is वापसed. If the copy gives
 *	invalid addresses -EFAULT is वापसed. On a success 0 is वापसed.
 */

पूर्णांक move_addr_to_kernel(व्योम __user *uaddr, पूर्णांक ulen, काष्ठा sockaddr_storage *kaddr)
अणु
	अगर (ulen < 0 || ulen > माप(काष्ठा sockaddr_storage))
		वापस -EINVAL;
	अगर (ulen == 0)
		वापस 0;
	अगर (copy_from_user(kaddr, uaddr, ulen))
		वापस -EFAULT;
	वापस audit_sockaddr(ulen, kaddr);
पूर्ण

/**
 *	move_addr_to_user	-	copy an address to user space
 *	@kaddr: kernel space address
 *	@klen: length of address in kernel
 *	@uaddr: user space address
 *	@ulen: poपूर्णांकer to user length field
 *
 *	The value poपूर्णांकed to by ulen on entry is the buffer length available.
 *	This is overwritten with the buffer space used. -EINVAL is वापसed
 *	अगर an overदीर्घ buffer is specअगरied or a negative buffer size. -EFAULT
 *	is वापसed अगर either the buffer or the length field are not
 *	accessible.
 *	After copying the data up to the limit the user specअगरies, the true
 *	length of the data is written over the length limit the user
 *	specअगरied. Zero is वापसed क्रम a success.
 */

अटल पूर्णांक move_addr_to_user(काष्ठा sockaddr_storage *kaddr, पूर्णांक klen,
			     व्योम __user *uaddr, पूर्णांक __user *ulen)
अणु
	पूर्णांक err;
	पूर्णांक len;

	BUG_ON(klen > माप(काष्ठा sockaddr_storage));
	err = get_user(len, ulen);
	अगर (err)
		वापस err;
	अगर (len > klen)
		len = klen;
	अगर (len < 0)
		वापस -EINVAL;
	अगर (len) अणु
		अगर (audit_sockaddr(klen, kaddr))
			वापस -ENOMEM;
		अगर (copy_to_user(uaddr, kaddr, len))
			वापस -EFAULT;
	पूर्ण
	/*
	 *      "fromlen shall refer to the value before truncation.."
	 *                      1003.1g
	 */
	वापस __put_user(klen, ulen);
पूर्ण

अटल काष्ठा kmem_cache *sock_inode_cachep __ro_after_init;

अटल काष्ठा inode *sock_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा socket_alloc *ei;

	ei = kmem_cache_alloc(sock_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	init_रुकोqueue_head(&ei->socket.wq.रुको);
	ei->socket.wq.fasync_list = शून्य;
	ei->socket.wq.flags = 0;

	ei->socket.state = SS_UNCONNECTED;
	ei->socket.flags = 0;
	ei->socket.ops = शून्य;
	ei->socket.sk = शून्य;
	ei->socket.file = शून्य;

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम sock_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा socket_alloc *ei;

	ei = container_of(inode, काष्ठा socket_alloc, vfs_inode);
	kmem_cache_मुक्त(sock_inode_cachep, ei);
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा socket_alloc *ei = (काष्ठा socket_alloc *)foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल व्योम init_inodecache(व्योम)
अणु
	sock_inode_cachep = kmem_cache_create("sock_inode_cache",
					      माप(काष्ठा socket_alloc),
					      0,
					      (SLAB_HWCACHE_ALIGN |
					       SLAB_RECLAIM_ACCOUNT |
					       SLAB_MEM_SPREAD | SLAB_ACCOUNT),
					      init_once);
	BUG_ON(sock_inode_cachep == शून्य);
पूर्ण

अटल स्थिर काष्ठा super_operations sockfs_ops = अणु
	.alloc_inode	= sock_alloc_inode,
	.मुक्त_inode	= sock_मुक्त_inode,
	.statfs		= simple_statfs,
पूर्ण;

/*
 * sockfs_dname() is called from d_path().
 */
अटल अक्षर *sockfs_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	वापस dynamic_dname(dentry, buffer, buflen, "socket:[%lu]",
				d_inode(dentry)->i_ino);
पूर्ण

अटल स्थिर काष्ठा dentry_operations sockfs_dentry_operations = अणु
	.d_dname  = sockfs_dname,
पूर्ण;

अटल पूर्णांक sockfs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			    काष्ठा dentry *dentry, काष्ठा inode *inode,
			    स्थिर अक्षर *suffix, व्योम *value, माप_प्रकार size)
अणु
	अगर (value) अणु
		अगर (dentry->d_name.len + 1 > size)
			वापस -दुस्फल;
		स_नकल(value, dentry->d_name.name, dentry->d_name.len + 1);
	पूर्ण
	वापस dentry->d_name.len + 1;
पूर्ण

#घोषणा XATTR_SOCKPROTONAME_SUFFIX "sockprotoname"
#घोषणा XATTR_NAME_SOCKPROTONAME (XATTR_SYSTEM_PREFIX XATTR_SOCKPROTONAME_SUFFIX)
#घोषणा XATTR_NAME_SOCKPROTONAME_LEN (माप(XATTR_NAME_SOCKPROTONAME)-1)

अटल स्थिर काष्ठा xattr_handler sockfs_xattr_handler = अणु
	.name = XATTR_NAME_SOCKPROTONAME,
	.get = sockfs_xattr_get,
पूर्ण;

अटल पूर्णांक sockfs_security_xattr_set(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा user_namespace *mnt_userns,
				     काष्ठा dentry *dentry, काष्ठा inode *inode,
				     स्थिर अक्षर *suffix, स्थिर व्योम *value,
				     माप_प्रकार size, पूर्णांक flags)
अणु
	/* Handled by LSM. */
	वापस -EAGAIN;
पूर्ण

अटल स्थिर काष्ठा xattr_handler sockfs_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.set = sockfs_security_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *sockfs_xattr_handlers[] = अणु
	&sockfs_xattr_handler,
	&sockfs_security_xattr_handler,
	शून्य
पूर्ण;

अटल पूर्णांक sockfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, SOCKFS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ops = &sockfs_ops;
	ctx->करोps = &sockfs_dentry_operations;
	ctx->xattr = sockfs_xattr_handlers;
	वापस 0;
पूर्ण

अटल काष्ठा vfsmount *sock_mnt __पढ़ो_mostly;

अटल काष्ठा file_प्रणाली_type sock_fs_type = अणु
	.name =		"sockfs",
	.init_fs_context = sockfs_init_fs_context,
	.समाप्त_sb =	समाप्त_anon_super,
पूर्ण;

/*
 *	Obtains the first available file descriptor and sets it up क्रम use.
 *
 *	These functions create file काष्ठाures and maps them to fd space
 *	of the current process. On success it वापसs file descriptor
 *	and file काष्ठा implicitly stored in sock->file.
 *	Note that another thपढ़ो may बंद file descriptor beक्रमe we वापस
 *	from this function. We use the fact that now we करो not refer
 *	to socket after mapping. If one day we will need it, this
 *	function will increment ref. count on file by 1.
 *
 *	In any हाल वापसed fd MAY BE not valid!
 *	This race condition is unaव्योमable
 *	with shared fd spaces, we cannot solve it inside kernel,
 *	but we take care of पूर्णांकernal coherence yet.
 */

/**
 *	sock_alloc_file - Bind a &socket to a &file
 *	@sock: socket
 *	@flags: file status flags
 *	@dname: protocol name
 *
 *	Returns the &file bound with @sock, implicitly storing it
 *	in sock->file. If dname is %शून्य, sets to "".
 *	On failure the वापस is a ERR poपूर्णांकer (see linux/err.h).
 *	This function uses GFP_KERNEL पूर्णांकernally.
 */

काष्ठा file *sock_alloc_file(काष्ठा socket *sock, पूर्णांक flags, स्थिर अक्षर *dname)
अणु
	काष्ठा file *file;

	अगर (!dname)
		dname = sock->sk ? sock->sk->sk_prot_creator->name : "";

	file = alloc_file_pseuकरो(SOCK_INODE(sock), sock_mnt, dname,
				O_RDWR | (flags & O_NONBLOCK),
				&socket_file_ops);
	अगर (IS_ERR(file)) अणु
		sock_release(sock);
		वापस file;
	पूर्ण

	sock->file = file;
	file->निजी_data = sock;
	stream_खोलो(SOCK_INODE(sock), file);
	वापस file;
पूर्ण
EXPORT_SYMBOL(sock_alloc_file);

अटल पूर्णांक sock_map_fd(काष्ठा socket *sock, पूर्णांक flags)
अणु
	काष्ठा file *newfile;
	पूर्णांक fd = get_unused_fd_flags(flags);
	अगर (unlikely(fd < 0)) अणु
		sock_release(sock);
		वापस fd;
	पूर्ण

	newfile = sock_alloc_file(sock, flags, शून्य);
	अगर (!IS_ERR(newfile)) अणु
		fd_install(fd, newfile);
		वापस fd;
	पूर्ण

	put_unused_fd(fd);
	वापस PTR_ERR(newfile);
पूर्ण

/**
 *	sock_from_file - Return the &socket bounded to @file.
 *	@file: file
 *
 *	On failure वापसs %शून्य.
 */

काष्ठा socket *sock_from_file(काष्ठा file *file)
अणु
	अगर (file->f_op == &socket_file_ops)
		वापस file->निजी_data;	/* set in sock_map_fd */

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sock_from_file);

/**
 *	sockfd_lookup - Go from a file number to its socket slot
 *	@fd: file handle
 *	@err: poपूर्णांकer to an error code वापस
 *
 *	The file handle passed in is locked and the socket it is bound
 *	to is वापसed. If an error occurs the err poपूर्णांकer is overwritten
 *	with a negative त्रुटि_सं code and शून्य is वापसed. The function checks
 *	क्रम both invalid handles and passing a handle which is not a socket.
 *
 *	On a success the socket object poपूर्णांकer is वापसed.
 */

काष्ठा socket *sockfd_lookup(पूर्णांक fd, पूर्णांक *err)
अणु
	काष्ठा file *file;
	काष्ठा socket *sock;

	file = fget(fd);
	अगर (!file) अणु
		*err = -EBADF;
		वापस शून्य;
	पूर्ण

	sock = sock_from_file(file);
	अगर (!sock) अणु
		*err = -ENOTSOCK;
		fput(file);
	पूर्ण
	वापस sock;
पूर्ण
EXPORT_SYMBOL(sockfd_lookup);

अटल काष्ठा socket *sockfd_lookup_light(पूर्णांक fd, पूर्णांक *err, पूर्णांक *fput_needed)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा socket *sock;

	*err = -EBADF;
	अगर (f.file) अणु
		sock = sock_from_file(f.file);
		अगर (likely(sock)) अणु
			*fput_needed = f.flags & FDPUT_FPUT;
			वापस sock;
		पूर्ण
		*err = -ENOTSOCK;
		fdput(f);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार sockfs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer,
				माप_प्रकार size)
अणु
	sमाप_प्रकार len;
	sमाप_प्रकार used = 0;

	len = security_inode_listsecurity(d_inode(dentry), buffer, size);
	अगर (len < 0)
		वापस len;
	used += len;
	अगर (buffer) अणु
		अगर (size < used)
			वापस -दुस्फल;
		buffer += len;
	पूर्ण

	len = (XATTR_NAME_SOCKPROTONAME_LEN + 1);
	used += len;
	अगर (buffer) अणु
		अगर (size < used)
			वापस -दुस्फल;
		स_नकल(buffer, XATTR_NAME_SOCKPROTONAME, len);
		buffer += len;
	पूर्ण

	वापस used;
पूर्ण

अटल पूर्णांक sockfs_setattr(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	पूर्णांक err = simple_setattr(&init_user_ns, dentry, iattr);

	अगर (!err && (iattr->ia_valid & ATTR_UID)) अणु
		काष्ठा socket *sock = SOCKET_I(d_inode(dentry));

		अगर (sock->sk)
			sock->sk->sk_uid = iattr->ia_uid;
		अन्यथा
			err = -ENOENT;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा inode_operations sockfs_inode_ops = अणु
	.listxattr = sockfs_listxattr,
	.setattr = sockfs_setattr,
पूर्ण;

/**
 *	sock_alloc - allocate a socket
 *
 *	Allocate a new inode and socket object. The two are bound together
 *	and initialised. The socket is then वापसed. If we are out of inodes
 *	शून्य is वापसed. This functions uses GFP_KERNEL पूर्णांकernally.
 */

काष्ठा socket *sock_alloc(व्योम)
अणु
	काष्ठा inode *inode;
	काष्ठा socket *sock;

	inode = new_inode_pseuकरो(sock_mnt->mnt_sb);
	अगर (!inode)
		वापस शून्य;

	sock = SOCKET_I(inode);

	inode->i_ino = get_next_ino();
	inode->i_mode = S_IFSOCK | S_IRWXUGO;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_op = &sockfs_inode_ops;

	वापस sock;
पूर्ण
EXPORT_SYMBOL(sock_alloc);

अटल व्योम __sock_release(काष्ठा socket *sock, काष्ठा inode *inode)
अणु
	अगर (sock->ops) अणु
		काष्ठा module *owner = sock->ops->owner;

		अगर (inode)
			inode_lock(inode);
		sock->ops->release(sock);
		sock->sk = शून्य;
		अगर (inode)
			inode_unlock(inode);
		sock->ops = शून्य;
		module_put(owner);
	पूर्ण

	अगर (sock->wq.fasync_list)
		pr_err("%s: fasync list not empty!\n", __func__);

	अगर (!sock->file) अणु
		iput(SOCK_INODE(sock));
		वापस;
	पूर्ण
	sock->file = शून्य;
पूर्ण

/**
 *	sock_release - बंद a socket
 *	@sock: socket to बंद
 *
 *	The socket is released from the protocol stack अगर it has a release
 *	callback, and the inode is then released अगर the socket is bound to
 *	an inode not a file.
 */
व्योम sock_release(काष्ठा socket *sock)
अणु
	__sock_release(sock, शून्य);
पूर्ण
EXPORT_SYMBOL(sock_release);

व्योम __sock_tx_बारtamp(__u16 tsflags, __u8 *tx_flags)
अणु
	u8 flags = *tx_flags;

	अगर (tsflags & SOF_TIMESTAMPING_TX_HARDWARE)
		flags |= SKBTX_HW_TSTAMP;

	अगर (tsflags & SOF_TIMESTAMPING_TX_SOFTWARE)
		flags |= SKBTX_SW_TSTAMP;

	अगर (tsflags & SOF_TIMESTAMPING_TX_SCHED)
		flags |= SKBTX_SCHED_TSTAMP;

	*tx_flags = flags;
पूर्ण
EXPORT_SYMBOL(__sock_tx_बारtamp);

INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet_sendmsg(काष्ठा socket *, काष्ठा msghdr *,
					   माप_प्रकार));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet6_sendmsg(काष्ठा socket *, काष्ठा msghdr *,
					    माप_प्रकार));
अटल अंतरभूत पूर्णांक sock_sendmsg_nosec(काष्ठा socket *sock, काष्ठा msghdr *msg)
अणु
	पूर्णांक ret = INसूचीECT_CALL_INET(sock->ops->sendmsg, inet6_sendmsg,
				     inet_sendmsg, sock, msg,
				     msg_data_left(msg));
	BUG_ON(ret == -EIOCBQUEUED);
	वापस ret;
पूर्ण

/**
 *	sock_sendmsg - send a message through @sock
 *	@sock: socket
 *	@msg: message to send
 *
 *	Sends @msg through @sock, passing through LSM.
 *	Returns the number of bytes sent, or an error code.
 */
पूर्णांक sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg)
अणु
	पूर्णांक err = security_socket_sendmsg(sock, msg,
					  msg_data_left(msg));

	वापस err ?: sock_sendmsg_nosec(sock, msg);
पूर्ण
EXPORT_SYMBOL(sock_sendmsg);

/**
 *	kernel_sendmsg - send a message through @sock (kernel-space)
 *	@sock: socket
 *	@msg: message header
 *	@vec: kernel vec
 *	@num: vec array length
 *	@size: total message data size
 *
 *	Builds the message data with @vec and sends it through @sock.
 *	Returns the number of bytes sent, or an error code.
 */

पूर्णांक kernel_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
		   काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार size)
अणु
	iov_iter_kvec(&msg->msg_iter, WRITE, vec, num, size);
	वापस sock_sendmsg(sock, msg);
पूर्ण
EXPORT_SYMBOL(kernel_sendmsg);

/**
 *	kernel_sendmsg_locked - send a message through @sock (kernel-space)
 *	@sk: sock
 *	@msg: message header
 *	@vec: output s/g array
 *	@num: output s/g array length
 *	@size: total message data size
 *
 *	Builds the message data with @vec and sends it through @sock.
 *	Returns the number of bytes sent, or an error code.
 *	Caller must hold @sk.
 */

पूर्णांक kernel_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg,
			  काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार size)
अणु
	काष्ठा socket *sock = sk->sk_socket;

	अगर (!sock->ops->sendmsg_locked)
		वापस sock_no_sendmsg_locked(sk, msg, size);

	iov_iter_kvec(&msg->msg_iter, WRITE, vec, num, size);

	वापस sock->ops->sendmsg_locked(sk, msg, msg_data_left(msg));
पूर्ण
EXPORT_SYMBOL(kernel_sendmsg_locked);

अटल bool skb_is_err_queue(स्थिर काष्ठा sk_buff *skb)
अणु
	/* pkt_type of skbs enqueued on the error queue are set to
	 * PACKET_OUTGOING in skb_set_err_queue(). This is only safe to करो
	 * in recvmsg, since skbs received on a local socket will never
	 * have a pkt_type of PACKET_OUTGOING.
	 */
	वापस skb->pkt_type == PACKET_OUTGOING;
पूर्ण

/* On transmit, software and hardware बारtamps are वापसed independently.
 * As the two skb clones share the hardware बारtamp, which may be updated
 * beक्रमe the software बारtamp is received, a hardware TX बारtamp may be
 * वापसed only अगर there is no software TX बारtamp. Ignore false software
 * बारtamps, which may be made in the __sock_recv_बारtamp() call when the
 * option SO_TIMESTAMP_OLD(NS) is enabled on the socket, even when the skb has a
 * hardware बारtamp.
 */
अटल bool skb_is_swtx_tstamp(स्थिर काष्ठा sk_buff *skb, पूर्णांक false_tstamp)
अणु
	वापस skb->tstamp && !false_tstamp && skb_is_err_queue(skb);
पूर्ण

अटल व्योम put_ts_pktinfo(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा scm_ts_pktinfo ts_pktinfo;
	काष्ठा net_device *orig_dev;

	अगर (!skb_mac_header_was_set(skb))
		वापस;

	स_रखो(&ts_pktinfo, 0, माप(ts_pktinfo));

	rcu_पढ़ो_lock();
	orig_dev = dev_get_by_napi_id(skb_napi_id(skb));
	अगर (orig_dev)
		ts_pktinfo.अगर_index = orig_dev->अगरindex;
	rcu_पढ़ो_unlock();

	ts_pktinfo.pkt_length = skb->len - skb_mac_offset(skb);
	put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPING_PKTINFO,
		 माप(ts_pktinfo), &ts_pktinfo);
पूर्ण

/*
 * called from sock_recv_बारtamp() अगर sock_flag(sk, SOCK_RCVTSTAMP)
 */
व्योम __sock_recv_बारtamp(काष्ठा msghdr *msg, काष्ठा sock *sk,
	काष्ठा sk_buff *skb)
अणु
	पूर्णांक need_software_tstamp = sock_flag(sk, SOCK_RCVTSTAMP);
	पूर्णांक new_tstamp = sock_flag(sk, SOCK_TSTAMP_NEW);
	काष्ठा scm_बारtamping_पूर्णांकernal tss;

	पूर्णांक empty = 1, false_tstamp = 0;
	काष्ठा skb_shared_hwtstamps *shhwtstamps =
		skb_hwtstamps(skb);

	/* Race occurred between बारtamp enabling and packet
	   receiving.  Fill in the current समय क्रम now. */
	अगर (need_software_tstamp && skb->tstamp == 0) अणु
		__net_बारtamp(skb);
		false_tstamp = 1;
	पूर्ण

	अगर (need_software_tstamp) अणु
		अगर (!sock_flag(sk, SOCK_RCVTSTAMPNS)) अणु
			अगर (new_tstamp) अणु
				काष्ठा __kernel_sock_समयval tv;

				skb_get_new_बारtamp(skb, &tv);
				put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_NEW,
					 माप(tv), &tv);
			पूर्ण अन्यथा अणु
				काष्ठा __kernel_old_समयval tv;

				skb_get_बारtamp(skb, &tv);
				put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_OLD,
					 माप(tv), &tv);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (new_tstamp) अणु
				काष्ठा __kernel_बारpec ts;

				skb_get_new_बारtampns(skb, &ts);
				put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPNS_NEW,
					 माप(ts), &ts);
			पूर्ण अन्यथा अणु
				काष्ठा __kernel_old_बारpec ts;

				skb_get_बारtampns(skb, &ts);
				put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPNS_OLD,
					 माप(ts), &ts);
			पूर्ण
		पूर्ण
	पूर्ण

	स_रखो(&tss, 0, माप(tss));
	अगर ((sk->sk_tsflags & SOF_TIMESTAMPING_SOFTWARE) &&
	    kसमय_प्रकारo_बारpec64_cond(skb->tstamp, tss.ts + 0))
		empty = 0;
	अगर (shhwtstamps &&
	    (sk->sk_tsflags & SOF_TIMESTAMPING_RAW_HARDWARE) &&
	    !skb_is_swtx_tstamp(skb, false_tstamp) &&
	    kसमय_प्रकारo_बारpec64_cond(shhwtstamps->hwtstamp, tss.ts + 2)) अणु
		empty = 0;
		अगर ((sk->sk_tsflags & SOF_TIMESTAMPING_OPT_PKTINFO) &&
		    !skb_is_err_queue(skb))
			put_ts_pktinfo(msg, skb);
	पूर्ण
	अगर (!empty) अणु
		अगर (sock_flag(sk, SOCK_TSTAMP_NEW))
			put_cmsg_scm_बारtamping64(msg, &tss);
		अन्यथा
			put_cmsg_scm_बारtamping(msg, &tss);

		अगर (skb_is_err_queue(skb) && skb->len &&
		    SKB_EXT_ERR(skb)->opt_stats)
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPING_OPT_STATS,
				 skb->len, skb->data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__sock_recv_बारtamp);

व्योम __sock_recv_wअगरi_status(काष्ठा msghdr *msg, काष्ठा sock *sk,
	काष्ठा sk_buff *skb)
अणु
	पूर्णांक ack;

	अगर (!sock_flag(sk, SOCK_WIFI_STATUS))
		वापस;
	अगर (!skb->wअगरi_acked_valid)
		वापस;

	ack = skb->wअगरi_acked;

	put_cmsg(msg, SOL_SOCKET, SCM_WIFI_STATUS, माप(ack), &ack);
पूर्ण
EXPORT_SYMBOL_GPL(__sock_recv_wअगरi_status);

अटल अंतरभूत व्योम sock_recv_drops(काष्ठा msghdr *msg, काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	अगर (sock_flag(sk, SOCK_RXQ_OVFL) && skb && SOCK_SKB_CB(skb)->dropcount)
		put_cmsg(msg, SOL_SOCKET, SO_RXQ_OVFL,
			माप(__u32), &SOCK_SKB_CB(skb)->dropcount);
पूर्ण

व्योम __sock_recv_ts_and_drops(काष्ठा msghdr *msg, काष्ठा sock *sk,
	काष्ठा sk_buff *skb)
अणु
	sock_recv_बारtamp(msg, sk, skb);
	sock_recv_drops(msg, sk, skb);
पूर्ण
EXPORT_SYMBOL_GPL(__sock_recv_ts_and_drops);

INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet_recvmsg(काष्ठा socket *, काष्ठा msghdr *,
					   माप_प्रकार, पूर्णांक));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet6_recvmsg(काष्ठा socket *, काष्ठा msghdr *,
					    माप_प्रकार, पूर्णांक));
अटल अंतरभूत पूर्णांक sock_recvmsg_nosec(काष्ठा socket *sock, काष्ठा msghdr *msg,
				     पूर्णांक flags)
अणु
	वापस INसूचीECT_CALL_INET(sock->ops->recvmsg, inet6_recvmsg,
				  inet_recvmsg, sock, msg, msg_data_left(msg),
				  flags);
पूर्ण

/**
 *	sock_recvmsg - receive a message from @sock
 *	@sock: socket
 *	@msg: message to receive
 *	@flags: message flags
 *
 *	Receives @msg from @sock, passing through LSM. Returns the total number
 *	of bytes received, or an error.
 */
पूर्णांक sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags)
अणु
	पूर्णांक err = security_socket_recvmsg(sock, msg, msg_data_left(msg), flags);

	वापस err ?: sock_recvmsg_nosec(sock, msg, flags);
पूर्ण
EXPORT_SYMBOL(sock_recvmsg);

/**
 *	kernel_recvmsg - Receive a message from a socket (kernel space)
 *	@sock: The socket to receive the message from
 *	@msg: Received message
 *	@vec: Input s/g array क्रम message data
 *	@num: Size of input s/g array
 *	@size: Number of bytes to पढ़ो
 *	@flags: Message flags (MSG_DONTWAIT, etc...)
 *
 *	On वापस the msg काष्ठाure contains the scatter/gather array passed in the
 *	vec argument. The array is modअगरied so that it consists of the unfilled
 *	portion of the original array.
 *
 *	The वापसed value is the total number of bytes received, or an error.
 */

पूर्णांक kernel_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
		   काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार size, पूर्णांक flags)
अणु
	msg->msg_control_is_user = false;
	iov_iter_kvec(&msg->msg_iter, READ, vec, num, size);
	वापस sock_recvmsg(sock, msg, flags);
पूर्ण
EXPORT_SYMBOL(kernel_recvmsg);

अटल sमाप_प्रकार sock_sendpage(काष्ठा file *file, काष्ठा page *page,
			     पूर्णांक offset, माप_प्रकार size, loff_t *ppos, पूर्णांक more)
अणु
	काष्ठा socket *sock;
	पूर्णांक flags;

	sock = file->निजी_data;

	flags = (file->f_flags & O_NONBLOCK) ? MSG_DONTWAIT : 0;
	/* more is a combination of MSG_MORE and MSG_SENDPAGE_NOTLAST */
	flags |= more;

	वापस kernel_sendpage(sock, page, offset, size, flags);
पूर्ण

अटल sमाप_प्रकार sock_splice_पढ़ो(काष्ठा file *file, loff_t *ppos,
				काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
				अचिन्हित पूर्णांक flags)
अणु
	काष्ठा socket *sock = file->निजी_data;

	अगर (unlikely(!sock->ops->splice_पढ़ो))
		वापस generic_file_splice_पढ़ो(file, ppos, pipe, len, flags);

	वापस sock->ops->splice_पढ़ो(sock, ppos, pipe, len, flags);
पूर्ण

अटल sमाप_प्रकार sock_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा socket *sock = file->निजी_data;
	काष्ठा msghdr msg = अणु.msg_iter = *to,
			     .msg_iocb = iocbपूर्ण;
	sमाप_प्रकार res;

	अगर (file->f_flags & O_NONBLOCK || (iocb->ki_flags & IOCB_NOWAIT))
		msg.msg_flags = MSG_DONTWAIT;

	अगर (iocb->ki_pos != 0)
		वापस -ESPIPE;

	अगर (!iov_iter_count(to))	/* Match SYS5 behaviour */
		वापस 0;

	res = sock_recvmsg(sock, &msg, msg.msg_flags);
	*to = msg.msg_iter;
	वापस res;
पूर्ण

अटल sमाप_प्रकार sock_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा socket *sock = file->निजी_data;
	काष्ठा msghdr msg = अणु.msg_iter = *from,
			     .msg_iocb = iocbपूर्ण;
	sमाप_प्रकार res;

	अगर (iocb->ki_pos != 0)
		वापस -ESPIPE;

	अगर (file->f_flags & O_NONBLOCK || (iocb->ki_flags & IOCB_NOWAIT))
		msg.msg_flags = MSG_DONTWAIT;

	अगर (sock->type == SOCK_SEQPACKET)
		msg.msg_flags |= MSG_EOR;

	res = sock_sendmsg(sock, &msg);
	*from = msg.msg_iter;
	वापस res;
पूर्ण

/*
 * Atomic setting of ioctl hooks to aव्योम race
 * with module unload.
 */

अटल DEFINE_MUTEX(br_ioctl_mutex);
अटल पूर्णांक (*br_ioctl_hook) (काष्ठा net *, अचिन्हित पूर्णांक cmd, व्योम __user *arg);

व्योम brioctl_set(पूर्णांक (*hook) (काष्ठा net *, अचिन्हित पूर्णांक, व्योम __user *))
अणु
	mutex_lock(&br_ioctl_mutex);
	br_ioctl_hook = hook;
	mutex_unlock(&br_ioctl_mutex);
पूर्ण
EXPORT_SYMBOL(brioctl_set);

अटल DEFINE_MUTEX(vlan_ioctl_mutex);
अटल पूर्णांक (*vlan_ioctl_hook) (काष्ठा net *, व्योम __user *arg);

व्योम vlan_ioctl_set(पूर्णांक (*hook) (काष्ठा net *, व्योम __user *))
अणु
	mutex_lock(&vlan_ioctl_mutex);
	vlan_ioctl_hook = hook;
	mutex_unlock(&vlan_ioctl_mutex);
पूर्ण
EXPORT_SYMBOL(vlan_ioctl_set);

अटल दीर्घ sock_करो_ioctl(काष्ठा net *net, काष्ठा socket *sock,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;
	व्योम __user *argp = (व्योम __user *)arg;

	err = sock->ops->ioctl(sock, cmd, arg);

	/*
	 * If this ioctl is unknown try to hand it करोwn
	 * to the NIC driver.
	 */
	अगर (err != -ENOIOCTLCMD)
		वापस err;

	अगर (cmd == SIOCGIFCONF) अणु
		काष्ठा अगरconf अगरc;
		अगर (copy_from_user(&अगरc, argp, माप(काष्ठा अगरconf)))
			वापस -EFAULT;
		rtnl_lock();
		err = dev_अगरconf(net, &अगरc, माप(काष्ठा अगरreq));
		rtnl_unlock();
		अगर (!err && copy_to_user(argp, &अगरc, माप(काष्ठा अगरconf)))
			err = -EFAULT;
	पूर्ण अन्यथा अणु
		काष्ठा अगरreq अगरr;
		bool need_copyout;
		अगर (copy_from_user(&अगरr, argp, माप(काष्ठा अगरreq)))
			वापस -EFAULT;
		err = dev_ioctl(net, cmd, &अगरr, &need_copyout);
		अगर (!err && need_copyout)
			अगर (copy_to_user(argp, &अगरr, माप(काष्ठा अगरreq)))
				वापस -EFAULT;
	पूर्ण
	वापस err;
पूर्ण

/*
 *	With an ioctl, arg may well be a user mode poपूर्णांकer, but we करोn't know
 *	what to करो with it - that's up to the protocol still.
 */

अटल दीर्घ sock_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक pid, err;
	काष्ठा net *net;

	sock = file->निजी_data;
	sk = sock->sk;
	net = sock_net(sk);
	अगर (unlikely(cmd >= SIOCDEVPRIVATE && cmd <= (SIOCDEVPRIVATE + 15))) अणु
		काष्ठा अगरreq अगरr;
		bool need_copyout;
		अगर (copy_from_user(&अगरr, argp, माप(काष्ठा अगरreq)))
			वापस -EFAULT;
		err = dev_ioctl(net, cmd, &अगरr, &need_copyout);
		अगर (!err && need_copyout)
			अगर (copy_to_user(argp, &अगरr, माप(काष्ठा अगरreq)))
				वापस -EFAULT;
	पूर्ण अन्यथा
#अगर_घोषित CONFIG_WEXT_CORE
	अगर (cmd >= SIOCIWFIRST && cmd <= SIOCIWLAST) अणु
		err = wext_handle_ioctl(net, cmd, argp);
	पूर्ण अन्यथा
#पूर्ण_अगर
		चयन (cmd) अणु
		हाल FIOSETOWN:
		हाल SIOCSPGRP:
			err = -EFAULT;
			अगर (get_user(pid, (पूर्णांक __user *)argp))
				अवरोध;
			err = f_setown(sock->file, pid, 1);
			अवरोध;
		हाल FIOGETOWN:
		हाल SIOCGPGRP:
			err = put_user(f_getown(sock->file),
				       (पूर्णांक __user *)argp);
			अवरोध;
		हाल SIOCGIFBR:
		हाल SIOCSIFBR:
		हाल SIOCBRADDBR:
		हाल SIOCBRDELBR:
			err = -ENOPKG;
			अगर (!br_ioctl_hook)
				request_module("bridge");

			mutex_lock(&br_ioctl_mutex);
			अगर (br_ioctl_hook)
				err = br_ioctl_hook(net, cmd, argp);
			mutex_unlock(&br_ioctl_mutex);
			अवरोध;
		हाल SIOCGIFVLAN:
		हाल SIOCSIFVLAN:
			err = -ENOPKG;
			अगर (!vlan_ioctl_hook)
				request_module("8021q");

			mutex_lock(&vlan_ioctl_mutex);
			अगर (vlan_ioctl_hook)
				err = vlan_ioctl_hook(net, argp);
			mutex_unlock(&vlan_ioctl_mutex);
			अवरोध;
		हाल SIOCGSKNS:
			err = -EPERM;
			अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
				अवरोध;

			err = खोलो_related_ns(&net->ns, get_net_ns);
			अवरोध;
		हाल SIOCGSTAMP_OLD:
		हाल SIOCGSTAMPNS_OLD:
			अगर (!sock->ops->gettstamp) अणु
				err = -ENOIOCTLCMD;
				अवरोध;
			पूर्ण
			err = sock->ops->gettstamp(sock, argp,
						   cmd == SIOCGSTAMP_OLD,
						   !IS_ENABLED(CONFIG_64BIT));
			अवरोध;
		हाल SIOCGSTAMP_NEW:
		हाल SIOCGSTAMPNS_NEW:
			अगर (!sock->ops->gettstamp) अणु
				err = -ENOIOCTLCMD;
				अवरोध;
			पूर्ण
			err = sock->ops->gettstamp(sock, argp,
						   cmd == SIOCGSTAMP_NEW,
						   false);
			अवरोध;
		शेष:
			err = sock_करो_ioctl(net, sock, cmd, arg);
			अवरोध;
		पूर्ण
	वापस err;
पूर्ण

/**
 *	sock_create_lite - creates a socket
 *	@family: protocol family (AF_INET, ...)
 *	@type: communication type (SOCK_STREAM, ...)
 *	@protocol: protocol (0, ...)
 *	@res: new socket
 *
 *	Creates a new socket and assigns it to @res, passing through LSM.
 *	The new socket initialization is not complete, see kernel_accept().
 *	Returns 0 or an error. On failure @res is set to %शून्य.
 *	This function पूर्णांकernally uses GFP_KERNEL.
 */

पूर्णांक sock_create_lite(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, काष्ठा socket **res)
अणु
	पूर्णांक err;
	काष्ठा socket *sock = शून्य;

	err = security_socket_create(family, type, protocol, 1);
	अगर (err)
		जाओ out;

	sock = sock_alloc();
	अगर (!sock) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	sock->type = type;
	err = security_socket_post_create(sock, family, type, protocol, 1);
	अगर (err)
		जाओ out_release;

out:
	*res = sock;
	वापस err;
out_release:
	sock_release(sock);
	sock = शून्य;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(sock_create_lite);

/* No kernel lock held - perfect */
अटल __poll_t sock_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा socket *sock = file->निजी_data;
	__poll_t events = poll_requested_events(रुको), flag = 0;

	अगर (!sock->ops->poll)
		वापस 0;

	अगर (sk_can_busy_loop(sock->sk)) अणु
		/* poll once अगर requested by the syscall */
		अगर (events & POLL_BUSY_LOOP)
			sk_busy_loop(sock->sk, 1);

		/* अगर this socket can poll_ll, tell the प्रणाली call */
		flag = POLL_BUSY_LOOP;
	पूर्ण

	वापस sock->ops->poll(file, sock, रुको) | flag;
पूर्ण

अटल पूर्णांक sock_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा socket *sock = file->निजी_data;

	वापस sock->ops->mmap(file, sock, vma);
पूर्ण

अटल पूर्णांक sock_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	__sock_release(SOCKET_I(inode), inode);
	वापस 0;
पूर्ण

/*
 *	Update the socket async list
 *
 *	Fasync_list locking strategy.
 *
 *	1. fasync_list is modअगरied only under process context socket lock
 *	   i.e. under semaphore.
 *	2. fasync_list is used under पढ़ो_lock(&sk->sk_callback_lock)
 *	   or under socket lock
 */

अटल पूर्णांक sock_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा socket *sock = filp->निजी_data;
	काष्ठा sock *sk = sock->sk;
	काष्ठा socket_wq *wq = &sock->wq;

	अगर (sk == शून्य)
		वापस -EINVAL;

	lock_sock(sk);
	fasync_helper(fd, filp, on, &wq->fasync_list);

	अगर (!wq->fasync_list)
		sock_reset_flag(sk, SOCK_FASYNC);
	अन्यथा
		sock_set_flag(sk, SOCK_FASYNC);

	release_sock(sk);
	वापस 0;
पूर्ण

/* This function may be called only under rcu_lock */

पूर्णांक sock_wake_async(काष्ठा socket_wq *wq, पूर्णांक how, पूर्णांक band)
अणु
	अगर (!wq || !wq->fasync_list)
		वापस -1;

	चयन (how) अणु
	हाल SOCK_WAKE_WAITD:
		अगर (test_bit(SOCKWQ_ASYNC_WAITDATA, &wq->flags))
			अवरोध;
		जाओ call_समाप्त;
	हाल SOCK_WAKE_SPACE:
		अगर (!test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &wq->flags))
			अवरोध;
		fallthrough;
	हाल SOCK_WAKE_IO:
call_समाप्त:
		समाप्त_fasync(&wq->fasync_list, SIGIO, band);
		अवरोध;
	हाल SOCK_WAKE_URG:
		समाप्त_fasync(&wq->fasync_list, SIGURG, band);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sock_wake_async);

/**
 *	__sock_create - creates a socket
 *	@net: net namespace
 *	@family: protocol family (AF_INET, ...)
 *	@type: communication type (SOCK_STREAM, ...)
 *	@protocol: protocol (0, ...)
 *	@res: new socket
 *	@kern: boolean क्रम kernel space sockets
 *
 *	Creates a new socket and assigns it to @res, passing through LSM.
 *	Returns 0 or an error. On failure @res is set to %शून्य. @kern must
 *	be set to true अगर the socket resides in kernel space.
 *	This function पूर्णांकernally uses GFP_KERNEL.
 */

पूर्णांक __sock_create(काष्ठा net *net, पूर्णांक family, पूर्णांक type, पूर्णांक protocol,
			 काष्ठा socket **res, पूर्णांक kern)
अणु
	पूर्णांक err;
	काष्ठा socket *sock;
	स्थिर काष्ठा net_proto_family *pf;

	/*
	 *      Check protocol is in range
	 */
	अगर (family < 0 || family >= NPROTO)
		वापस -EAFNOSUPPORT;
	अगर (type < 0 || type >= SOCK_MAX)
		वापस -EINVAL;

	/* Compatibility.

	   This uglymoron is moved from INET layer to here to aव्योम
	   deadlock in module load.
	 */
	अगर (family == PF_INET && type == SOCK_PACKET) अणु
		pr_info_once("%s uses obsolete (PF_INET,SOCK_PACKET)\n",
			     current->comm);
		family = PF_PACKET;
	पूर्ण

	err = security_socket_create(family, type, protocol, kern);
	अगर (err)
		वापस err;

	/*
	 *	Allocate the socket and allow the family to set things up. अगर
	 *	the protocol is 0, the family is inकाष्ठाed to select an appropriate
	 *	शेष.
	 */
	sock = sock_alloc();
	अगर (!sock) अणु
		net_warn_ratelimited("socket: no more sockets\n");
		वापस -ENखाता;	/* Not exactly a match, but its the
				   बंदst posix thing */
	पूर्ण

	sock->type = type;

#अगर_घोषित CONFIG_MODULES
	/* Attempt to load a protocol module अगर the find failed.
	 *
	 * 12/09/1996 Marcin: But! this makes REALLY only sense, अगर the user
	 * requested real, full-featured networking support upon configuration.
	 * Otherwise module support will अवरोध!
	 */
	अगर (rcu_access_poपूर्णांकer(net_families[family]) == शून्य)
		request_module("net-pf-%d", family);
#पूर्ण_अगर

	rcu_पढ़ो_lock();
	pf = rcu_dereference(net_families[family]);
	err = -EAFNOSUPPORT;
	अगर (!pf)
		जाओ out_release;

	/*
	 * We will call the ->create function, that possibly is in a loadable
	 * module, so we have to bump that loadable module refcnt first.
	 */
	अगर (!try_module_get(pf->owner))
		जाओ out_release;

	/* Now रक्षित by module ref count */
	rcu_पढ़ो_unlock();

	err = pf->create(net, sock, protocol, kern);
	अगर (err < 0)
		जाओ out_module_put;

	/*
	 * Now to bump the refcnt of the [loadable] module that owns this
	 * socket at sock_release समय we decrement its refcnt.
	 */
	अगर (!try_module_get(sock->ops->owner))
		जाओ out_module_busy;

	/*
	 * Now that we're करोne with the ->create function, the [loadable]
	 * module can have its refcnt decremented
	 */
	module_put(pf->owner);
	err = security_socket_post_create(sock, family, type, protocol, kern);
	अगर (err)
		जाओ out_sock_release;
	*res = sock;

	वापस 0;

out_module_busy:
	err = -EAFNOSUPPORT;
out_module_put:
	sock->ops = शून्य;
	module_put(pf->owner);
out_sock_release:
	sock_release(sock);
	वापस err;

out_release:
	rcu_पढ़ो_unlock();
	जाओ out_sock_release;
पूर्ण
EXPORT_SYMBOL(__sock_create);

/**
 *	sock_create - creates a socket
 *	@family: protocol family (AF_INET, ...)
 *	@type: communication type (SOCK_STREAM, ...)
 *	@protocol: protocol (0, ...)
 *	@res: new socket
 *
 *	A wrapper around __sock_create().
 *	Returns 0 or an error. This function पूर्णांकernally uses GFP_KERNEL.
 */

पूर्णांक sock_create(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, काष्ठा socket **res)
अणु
	वापस __sock_create(current->nsproxy->net_ns, family, type, protocol, res, 0);
पूर्ण
EXPORT_SYMBOL(sock_create);

/**
 *	sock_create_kern - creates a socket (kernel space)
 *	@net: net namespace
 *	@family: protocol family (AF_INET, ...)
 *	@type: communication type (SOCK_STREAM, ...)
 *	@protocol: protocol (0, ...)
 *	@res: new socket
 *
 *	A wrapper around __sock_create().
 *	Returns 0 or an error. This function पूर्णांकernally uses GFP_KERNEL.
 */

पूर्णांक sock_create_kern(काष्ठा net *net, पूर्णांक family, पूर्णांक type, पूर्णांक protocol, काष्ठा socket **res)
अणु
	वापस __sock_create(net, family, type, protocol, res, 1);
पूर्ण
EXPORT_SYMBOL(sock_create_kern);

पूर्णांक __sys_socket(पूर्णांक family, पूर्णांक type, पूर्णांक protocol)
अणु
	पूर्णांक retval;
	काष्ठा socket *sock;
	पूर्णांक flags;

	/* Check the SOCK_* स्थिरants क्रम consistency.  */
	BUILD_BUG_ON(SOCK_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON((SOCK_MAX | SOCK_TYPE_MASK) != SOCK_TYPE_MASK);
	BUILD_BUG_ON(SOCK_CLOEXEC & SOCK_TYPE_MASK);
	BUILD_BUG_ON(SOCK_NONBLOCK & SOCK_TYPE_MASK);

	flags = type & ~SOCK_TYPE_MASK;
	अगर (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK))
		वापस -EINVAL;
	type &= SOCK_TYPE_MASK;

	अगर (SOCK_NONBLOCK != O_NONBLOCK && (flags & SOCK_NONBLOCK))
		flags = (flags & ~SOCK_NONBLOCK) | O_NONBLOCK;

	retval = sock_create(family, type, protocol, &sock);
	अगर (retval < 0)
		वापस retval;

	वापस sock_map_fd(sock, flags & (O_CLOEXEC | O_NONBLOCK));
पूर्ण

SYSCALL_DEFINE3(socket, पूर्णांक, family, पूर्णांक, type, पूर्णांक, protocol)
अणु
	वापस __sys_socket(family, type, protocol);
पूर्ण

/*
 *	Create a pair of connected sockets.
 */

पूर्णांक __sys_socketpair(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, पूर्णांक __user *usockvec)
अणु
	काष्ठा socket *sock1, *sock2;
	पूर्णांक fd1, fd2, err;
	काष्ठा file *newfile1, *newfile2;
	पूर्णांक flags;

	flags = type & ~SOCK_TYPE_MASK;
	अगर (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK))
		वापस -EINVAL;
	type &= SOCK_TYPE_MASK;

	अगर (SOCK_NONBLOCK != O_NONBLOCK && (flags & SOCK_NONBLOCK))
		flags = (flags & ~SOCK_NONBLOCK) | O_NONBLOCK;

	/*
	 * reserve descriptors and make sure we won't fail
	 * to वापस them to userland.
	 */
	fd1 = get_unused_fd_flags(flags);
	अगर (unlikely(fd1 < 0))
		वापस fd1;

	fd2 = get_unused_fd_flags(flags);
	अगर (unlikely(fd2 < 0)) अणु
		put_unused_fd(fd1);
		वापस fd2;
	पूर्ण

	err = put_user(fd1, &usockvec[0]);
	अगर (err)
		जाओ out;

	err = put_user(fd2, &usockvec[1]);
	अगर (err)
		जाओ out;

	/*
	 * Obtain the first socket and check अगर the underlying protocol
	 * supports the socketpair call.
	 */

	err = sock_create(family, type, protocol, &sock1);
	अगर (unlikely(err < 0))
		जाओ out;

	err = sock_create(family, type, protocol, &sock2);
	अगर (unlikely(err < 0)) अणु
		sock_release(sock1);
		जाओ out;
	पूर्ण

	err = security_socket_socketpair(sock1, sock2);
	अगर (unlikely(err)) अणु
		sock_release(sock2);
		sock_release(sock1);
		जाओ out;
	पूर्ण

	err = sock1->ops->socketpair(sock1, sock2);
	अगर (unlikely(err < 0)) अणु
		sock_release(sock2);
		sock_release(sock1);
		जाओ out;
	पूर्ण

	newfile1 = sock_alloc_file(sock1, flags, शून्य);
	अगर (IS_ERR(newfile1)) अणु
		err = PTR_ERR(newfile1);
		sock_release(sock2);
		जाओ out;
	पूर्ण

	newfile2 = sock_alloc_file(sock2, flags, शून्य);
	अगर (IS_ERR(newfile2)) अणु
		err = PTR_ERR(newfile2);
		fput(newfile1);
		जाओ out;
	पूर्ण

	audit_fd_pair(fd1, fd2);

	fd_install(fd1, newfile1);
	fd_install(fd2, newfile2);
	वापस 0;

out:
	put_unused_fd(fd2);
	put_unused_fd(fd1);
	वापस err;
पूर्ण

SYSCALL_DEFINE4(socketpair, पूर्णांक, family, पूर्णांक, type, पूर्णांक, protocol,
		पूर्णांक __user *, usockvec)
अणु
	वापस __sys_socketpair(family, type, protocol, usockvec);
पूर्ण

/*
 *	Bind a name to a socket. Nothing much to करो here since it's
 *	the protocol's responsibility to handle the local address.
 *
 *	We move the socket address to kernel space beक्रमe we call
 *	the protocol layer (having also checked the address is ok).
 */

पूर्णांक __sys_bind(पूर्णांक fd, काष्ठा sockaddr __user *umyaddr, पूर्णांक addrlen)
अणु
	काष्ठा socket *sock;
	काष्ठा sockaddr_storage address;
	पूर्णांक err, fput_needed;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (sock) अणु
		err = move_addr_to_kernel(umyaddr, addrlen, &address);
		अगर (!err) अणु
			err = security_socket_bind(sock,
						   (काष्ठा sockaddr *)&address,
						   addrlen);
			अगर (!err)
				err = sock->ops->bind(sock,
						      (काष्ठा sockaddr *)
						      &address, addrlen);
		पूर्ण
		fput_light(sock->file, fput_needed);
	पूर्ण
	वापस err;
पूर्ण

SYSCALL_DEFINE3(bind, पूर्णांक, fd, काष्ठा sockaddr __user *, umyaddr, पूर्णांक, addrlen)
अणु
	वापस __sys_bind(fd, umyaddr, addrlen);
पूर्ण

/*
 *	Perक्रमm a listen. Basically, we allow the protocol to करो anything
 *	necessary क्रम a listen, and अगर that works, we mark the socket as
 *	पढ़ोy क्रम listening.
 */

पूर्णांक __sys_listen(पूर्णांक fd, पूर्णांक backlog)
अणु
	काष्ठा socket *sock;
	पूर्णांक err, fput_needed;
	पूर्णांक somaxconn;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (sock) अणु
		somaxconn = sock_net(sock->sk)->core.sysctl_somaxconn;
		अगर ((अचिन्हित पूर्णांक)backlog > somaxconn)
			backlog = somaxconn;

		err = security_socket_listen(sock, backlog);
		अगर (!err)
			err = sock->ops->listen(sock, backlog);

		fput_light(sock->file, fput_needed);
	पूर्ण
	वापस err;
पूर्ण

SYSCALL_DEFINE2(listen, पूर्णांक, fd, पूर्णांक, backlog)
अणु
	वापस __sys_listen(fd, backlog);
पूर्ण

पूर्णांक __sys_accept4_file(काष्ठा file *file, अचिन्हित file_flags,
		       काष्ठा sockaddr __user *upeer_sockaddr,
		       पूर्णांक __user *upeer_addrlen, पूर्णांक flags,
		       अचिन्हित दीर्घ nofile)
अणु
	काष्ठा socket *sock, *newsock;
	काष्ठा file *newfile;
	पूर्णांक err, len, newfd;
	काष्ठा sockaddr_storage address;

	अगर (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK))
		वापस -EINVAL;

	अगर (SOCK_NONBLOCK != O_NONBLOCK && (flags & SOCK_NONBLOCK))
		flags = (flags & ~SOCK_NONBLOCK) | O_NONBLOCK;

	sock = sock_from_file(file);
	अगर (!sock) अणु
		err = -ENOTSOCK;
		जाओ out;
	पूर्ण

	err = -ENखाता;
	newsock = sock_alloc();
	अगर (!newsock)
		जाओ out;

	newsock->type = sock->type;
	newsock->ops = sock->ops;

	/*
	 * We करोn't need try_module_get here, as the listening socket (sock)
	 * has the protocol module (sock->ops->owner) held.
	 */
	__module_get(newsock->ops->owner);

	newfd = __get_unused_fd_flags(flags, nofile);
	अगर (unlikely(newfd < 0)) अणु
		err = newfd;
		sock_release(newsock);
		जाओ out;
	पूर्ण
	newfile = sock_alloc_file(newsock, flags, sock->sk->sk_prot_creator->name);
	अगर (IS_ERR(newfile)) अणु
		err = PTR_ERR(newfile);
		put_unused_fd(newfd);
		जाओ out;
	पूर्ण

	err = security_socket_accept(sock, newsock);
	अगर (err)
		जाओ out_fd;

	err = sock->ops->accept(sock, newsock, sock->file->f_flags | file_flags,
					false);
	अगर (err < 0)
		जाओ out_fd;

	अगर (upeer_sockaddr) अणु
		len = newsock->ops->getname(newsock,
					(काष्ठा sockaddr *)&address, 2);
		अगर (len < 0) अणु
			err = -ECONNABORTED;
			जाओ out_fd;
		पूर्ण
		err = move_addr_to_user(&address,
					len, upeer_sockaddr, upeer_addrlen);
		अगर (err < 0)
			जाओ out_fd;
	पूर्ण

	/* File flags are not inherited via accept() unlike another OSes. */

	fd_install(newfd, newfile);
	err = newfd;
out:
	वापस err;
out_fd:
	fput(newfile);
	put_unused_fd(newfd);
	जाओ out;

पूर्ण

/*
 *	For accept, we attempt to create a new socket, set up the link
 *	with the client, wake up the client, then वापस the new
 *	connected fd. We collect the address of the connector in kernel
 *	space and move it to user at the very end. This is unclean because
 *	we खोलो the socket then वापस an error.
 *
 *	1003.1g adds the ability to recvmsg() to query connection pending
 *	status to recvmsg. We need to add that support in a way thats
 *	clean when we reकाष्ठाure accept also.
 */

पूर्णांक __sys_accept4(पूर्णांक fd, काष्ठा sockaddr __user *upeer_sockaddr,
		  पूर्णांक __user *upeer_addrlen, पूर्णांक flags)
अणु
	पूर्णांक ret = -EBADF;
	काष्ठा fd f;

	f = fdget(fd);
	अगर (f.file) अणु
		ret = __sys_accept4_file(f.file, 0, upeer_sockaddr,
						upeer_addrlen, flags,
						rlimit(RLIMIT_NOखाता));
		fdput(f);
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE4(accept4, पूर्णांक, fd, काष्ठा sockaddr __user *, upeer_sockaddr,
		पूर्णांक __user *, upeer_addrlen, पूर्णांक, flags)
अणु
	वापस __sys_accept4(fd, upeer_sockaddr, upeer_addrlen, flags);
पूर्ण

SYSCALL_DEFINE3(accept, पूर्णांक, fd, काष्ठा sockaddr __user *, upeer_sockaddr,
		पूर्णांक __user *, upeer_addrlen)
अणु
	वापस __sys_accept4(fd, upeer_sockaddr, upeer_addrlen, 0);
पूर्ण

/*
 *	Attempt to connect to a socket with the server address.  The address
 *	is in user space so we verअगरy it is OK and move it to kernel space.
 *
 *	For 1003.1g we need to add clean support क्रम a bind to AF_UNSPEC to
 *	अवरोध bindings
 *
 *	NOTE: 1003.1g draft 6.3 is broken with respect to AX.25/NetROM and
 *	other SEQPACKET protocols that take समय to connect() as it करोesn't
 *	include the -EINPROGRESS status क्रम such sockets.
 */

पूर्णांक __sys_connect_file(काष्ठा file *file, काष्ठा sockaddr_storage *address,
		       पूर्णांक addrlen, पूर्णांक file_flags)
अणु
	काष्ठा socket *sock;
	पूर्णांक err;

	sock = sock_from_file(file);
	अगर (!sock) अणु
		err = -ENOTSOCK;
		जाओ out;
	पूर्ण

	err =
	    security_socket_connect(sock, (काष्ठा sockaddr *)address, addrlen);
	अगर (err)
		जाओ out;

	err = sock->ops->connect(sock, (काष्ठा sockaddr *)address, addrlen,
				 sock->file->f_flags | file_flags);
out:
	वापस err;
पूर्ण

पूर्णांक __sys_connect(पूर्णांक fd, काष्ठा sockaddr __user *uservaddr, पूर्णांक addrlen)
अणु
	पूर्णांक ret = -EBADF;
	काष्ठा fd f;

	f = fdget(fd);
	अगर (f.file) अणु
		काष्ठा sockaddr_storage address;

		ret = move_addr_to_kernel(uservaddr, addrlen, &address);
		अगर (!ret)
			ret = __sys_connect_file(f.file, &address, addrlen, 0);
		fdput(f);
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE3(connect, पूर्णांक, fd, काष्ठा sockaddr __user *, uservaddr,
		पूर्णांक, addrlen)
अणु
	वापस __sys_connect(fd, uservaddr, addrlen);
पूर्ण

/*
 *	Get the local address ('name') of a socket object. Move the obtained
 *	name to user space.
 */

पूर्णांक __sys_माला_लोockname(पूर्णांक fd, काष्ठा sockaddr __user *usockaddr,
		      पूर्णांक __user *usockaddr_len)
अणु
	काष्ठा socket *sock;
	काष्ठा sockaddr_storage address;
	पूर्णांक err, fput_needed;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		जाओ out;

	err = security_socket_माला_लोockname(sock);
	अगर (err)
		जाओ out_put;

	err = sock->ops->getname(sock, (काष्ठा sockaddr *)&address, 0);
	अगर (err < 0)
		जाओ out_put;
        /* "err" is actually length in this हाल */
	err = move_addr_to_user(&address, err, usockaddr, usockaddr_len);

out_put:
	fput_light(sock->file, fput_needed);
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE3(माला_लोockname, पूर्णांक, fd, काष्ठा sockaddr __user *, usockaddr,
		पूर्णांक __user *, usockaddr_len)
अणु
	वापस __sys_माला_लोockname(fd, usockaddr, usockaddr_len);
पूर्ण

/*
 *	Get the remote address ('name') of a socket object. Move the obtained
 *	name to user space.
 */

पूर्णांक __sys_getpeername(पूर्णांक fd, काष्ठा sockaddr __user *usockaddr,
		      पूर्णांक __user *usockaddr_len)
अणु
	काष्ठा socket *sock;
	काष्ठा sockaddr_storage address;
	पूर्णांक err, fput_needed;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (sock != शून्य) अणु
		err = security_socket_getpeername(sock);
		अगर (err) अणु
			fput_light(sock->file, fput_needed);
			वापस err;
		पूर्ण

		err = sock->ops->getname(sock, (काष्ठा sockaddr *)&address, 1);
		अगर (err >= 0)
			/* "err" is actually length in this हाल */
			err = move_addr_to_user(&address, err, usockaddr,
						usockaddr_len);
		fput_light(sock->file, fput_needed);
	पूर्ण
	वापस err;
पूर्ण

SYSCALL_DEFINE3(getpeername, पूर्णांक, fd, काष्ठा sockaddr __user *, usockaddr,
		पूर्णांक __user *, usockaddr_len)
अणु
	वापस __sys_getpeername(fd, usockaddr, usockaddr_len);
पूर्ण

/*
 *	Send a datagram to a given address. We move the address पूर्णांकo kernel
 *	space and check the user space data area is पढ़ोable beक्रमe invoking
 *	the protocol.
 */
पूर्णांक __sys_sendto(पूर्णांक fd, व्योम __user *buff, माप_प्रकार len, अचिन्हित पूर्णांक flags,
		 काष्ठा sockaddr __user *addr,  पूर्णांक addr_len)
अणु
	काष्ठा socket *sock;
	काष्ठा sockaddr_storage address;
	पूर्णांक err;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	पूर्णांक fput_needed;

	err = import_single_range(WRITE, buff, len, &iov, &msg.msg_iter);
	अगर (unlikely(err))
		वापस err;
	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		जाओ out;

	msg.msg_name = शून्य;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_namelen = 0;
	अगर (addr) अणु
		err = move_addr_to_kernel(addr, addr_len, &address);
		अगर (err < 0)
			जाओ out_put;
		msg.msg_name = (काष्ठा sockaddr *)&address;
		msg.msg_namelen = addr_len;
	पूर्ण
	अगर (sock->file->f_flags & O_NONBLOCK)
		flags |= MSG_DONTWAIT;
	msg.msg_flags = flags;
	err = sock_sendmsg(sock, &msg);

out_put:
	fput_light(sock->file, fput_needed);
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE6(sendto, पूर्णांक, fd, व्योम __user *, buff, माप_प्रकार, len,
		अचिन्हित पूर्णांक, flags, काष्ठा sockaddr __user *, addr,
		पूर्णांक, addr_len)
अणु
	वापस __sys_sendto(fd, buff, len, flags, addr, addr_len);
पूर्ण

/*
 *	Send a datagram करोwn a socket.
 */

SYSCALL_DEFINE4(send, पूर्णांक, fd, व्योम __user *, buff, माप_प्रकार, len,
		अचिन्हित पूर्णांक, flags)
अणु
	वापस __sys_sendto(fd, buff, len, flags, शून्य, 0);
पूर्ण

/*
 *	Receive a frame from the socket and optionally record the address of the
 *	sender. We verअगरy the buffers are writable and अगर needed move the
 *	sender address from kernel to user space.
 */
पूर्णांक __sys_recvfrom(पूर्णांक fd, व्योम __user *ubuf, माप_प्रकार size, अचिन्हित पूर्णांक flags,
		   काष्ठा sockaddr __user *addr, पूर्णांक __user *addr_len)
अणु
	काष्ठा socket *sock;
	काष्ठा iovec iov;
	काष्ठा msghdr msg;
	काष्ठा sockaddr_storage address;
	पूर्णांक err, err2;
	पूर्णांक fput_needed;

	err = import_single_range(READ, ubuf, size, &iov, &msg.msg_iter);
	अगर (unlikely(err))
		वापस err;
	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		जाओ out;

	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	/* Save some cycles and करोn't copy the address अगर not needed */
	msg.msg_name = addr ? (काष्ठा sockaddr *)&address : शून्य;
	/* We assume all kernel code knows the size of sockaddr_storage */
	msg.msg_namelen = 0;
	msg.msg_iocb = शून्य;
	msg.msg_flags = 0;
	अगर (sock->file->f_flags & O_NONBLOCK)
		flags |= MSG_DONTWAIT;
	err = sock_recvmsg(sock, &msg, flags);

	अगर (err >= 0 && addr != शून्य) अणु
		err2 = move_addr_to_user(&address,
					 msg.msg_namelen, addr, addr_len);
		अगर (err2 < 0)
			err = err2;
	पूर्ण

	fput_light(sock->file, fput_needed);
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE6(recvfrom, पूर्णांक, fd, व्योम __user *, ubuf, माप_प्रकार, size,
		अचिन्हित पूर्णांक, flags, काष्ठा sockaddr __user *, addr,
		पूर्णांक __user *, addr_len)
अणु
	वापस __sys_recvfrom(fd, ubuf, size, flags, addr, addr_len);
पूर्ण

/*
 *	Receive a datagram from a socket.
 */

SYSCALL_DEFINE4(recv, पूर्णांक, fd, व्योम __user *, ubuf, माप_प्रकार, size,
		अचिन्हित पूर्णांक, flags)
अणु
	वापस __sys_recvfrom(fd, ubuf, size, flags, शून्य, शून्य);
पूर्ण

अटल bool sock_use_custom_sol_socket(स्थिर काष्ठा socket *sock)
अणु
	स्थिर काष्ठा sock *sk = sock->sk;

	/* Use sock->ops->setsockopt() क्रम MPTCP */
	वापस IS_ENABLED(CONFIG_MPTCP) &&
	       sk->sk_protocol == IPPROTO_MPTCP &&
	       sk->sk_type == SOCK_STREAM &&
	       (sk->sk_family == AF_INET || sk->sk_family == AF_INET6);
पूर्ण

/*
 *	Set a socket option. Because we करोn't know the option lengths we have
 *	to pass the user mode parameter क्रम the protocols to sort out.
 */
पूर्णांक __sys_setsockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname, अक्षर __user *user_optval,
		पूर्णांक optlen)
अणु
	sockptr_t optval = USER_SOCKPTR(user_optval);
	अक्षर *kernel_optval = शून्य;
	पूर्णांक err, fput_needed;
	काष्ठा socket *sock;

	अगर (optlen < 0)
		वापस -EINVAL;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		वापस err;

	err = security_socket_setsockopt(sock, level, optname);
	अगर (err)
		जाओ out_put;

	अगर (!in_compat_syscall())
		err = BPF_CGROUP_RUN_PROG_SETSOCKOPT(sock->sk, &level, &optname,
						     user_optval, &optlen,
						     &kernel_optval);
	अगर (err < 0)
		जाओ out_put;
	अगर (err > 0) अणु
		err = 0;
		जाओ out_put;
	पूर्ण

	अगर (kernel_optval)
		optval = KERNEL_SOCKPTR(kernel_optval);
	अगर (level == SOL_SOCKET && !sock_use_custom_sol_socket(sock))
		err = sock_setsockopt(sock, level, optname, optval, optlen);
	अन्यथा अगर (unlikely(!sock->ops->setsockopt))
		err = -EOPNOTSUPP;
	अन्यथा
		err = sock->ops->setsockopt(sock, level, optname, optval,
					    optlen);
	kमुक्त(kernel_optval);
out_put:
	fput_light(sock->file, fput_needed);
	वापस err;
पूर्ण

SYSCALL_DEFINE5(setsockopt, पूर्णांक, fd, पूर्णांक, level, पूर्णांक, optname,
		अक्षर __user *, optval, पूर्णांक, optlen)
अणु
	वापस __sys_setsockopt(fd, level, optname, optval, optlen);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(bool tcp_bpf_bypass_माला_लोockopt(पूर्णांक level,
							 पूर्णांक optname));

/*
 *	Get a socket option. Because we करोn't know the option lengths we have
 *	to pass a user mode parameter क्रम the protocols to sort out.
 */
पूर्णांक __sys_माला_लोockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval,
		पूर्णांक __user *optlen)
अणु
	पूर्णांक err, fput_needed;
	काष्ठा socket *sock;
	पूर्णांक max_optlen;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		वापस err;

	err = security_socket_माला_लोockopt(sock, level, optname);
	अगर (err)
		जाओ out_put;

	अगर (!in_compat_syscall())
		max_optlen = BPF_CGROUP_GETSOCKOPT_MAX_OPTLEN(optlen);

	अगर (level == SOL_SOCKET)
		err = sock_माला_लोockopt(sock, level, optname, optval, optlen);
	अन्यथा अगर (unlikely(!sock->ops->माला_लोockopt))
		err = -EOPNOTSUPP;
	अन्यथा
		err = sock->ops->माला_लोockopt(sock, level, optname, optval,
					    optlen);

	अगर (!in_compat_syscall())
		err = BPF_CGROUP_RUN_PROG_GETSOCKOPT(sock->sk, level, optname,
						     optval, optlen, max_optlen,
						     err);
out_put:
	fput_light(sock->file, fput_needed);
	वापस err;
पूर्ण

SYSCALL_DEFINE5(माला_लोockopt, पूर्णांक, fd, पूर्णांक, level, पूर्णांक, optname,
		अक्षर __user *, optval, पूर्णांक __user *, optlen)
अणु
	वापस __sys_माला_लोockopt(fd, level, optname, optval, optlen);
पूर्ण

/*
 *	Shutकरोwn a socket.
 */

पूर्णांक __sys_shutकरोwn_sock(काष्ठा socket *sock, पूर्णांक how)
अणु
	पूर्णांक err;

	err = security_socket_shutकरोwn(sock, how);
	अगर (!err)
		err = sock->ops->shutकरोwn(sock, how);

	वापस err;
पूर्ण

पूर्णांक __sys_shutकरोwn(पूर्णांक fd, पूर्णांक how)
अणु
	पूर्णांक err, fput_needed;
	काष्ठा socket *sock;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (sock != शून्य) अणु
		err = __sys_shutकरोwn_sock(sock, how);
		fput_light(sock->file, fput_needed);
	पूर्ण
	वापस err;
पूर्ण

SYSCALL_DEFINE2(shutकरोwn, पूर्णांक, fd, पूर्णांक, how)
अणु
	वापस __sys_shutकरोwn(fd, how);
पूर्ण

/* A couple of helpful macros क्रम getting the address of the 32/64 bit
 * fields which are the same type (पूर्णांक / अचिन्हित) on our platक्रमms.
 */
#घोषणा COMPAT_MSG(msg, member)	((MSG_CMSG_COMPAT & flags) ? &msg##_compat->member : &msg->member)
#घोषणा COMPAT_NAMELEN(msg)	COMPAT_MSG(msg, msg_namelen)
#घोषणा COMPAT_FLAGS(msg)	COMPAT_MSG(msg, msg_flags)

काष्ठा used_address अणु
	काष्ठा sockaddr_storage name;
	अचिन्हित पूर्णांक name_len;
पूर्ण;

पूर्णांक __copy_msghdr_from_user(काष्ठा msghdr *kmsg,
			    काष्ठा user_msghdr __user *umsg,
			    काष्ठा sockaddr __user **save_addr,
			    काष्ठा iovec __user **uiov, माप_प्रकार *nsegs)
अणु
	काष्ठा user_msghdr msg;
	sमाप_प्रकार err;

	अगर (copy_from_user(&msg, umsg, माप(*umsg)))
		वापस -EFAULT;

	kmsg->msg_control_is_user = true;
	kmsg->msg_control_user = msg.msg_control;
	kmsg->msg_controllen = msg.msg_controllen;
	kmsg->msg_flags = msg.msg_flags;

	kmsg->msg_namelen = msg.msg_namelen;
	अगर (!msg.msg_name)
		kmsg->msg_namelen = 0;

	अगर (kmsg->msg_namelen < 0)
		वापस -EINVAL;

	अगर (kmsg->msg_namelen > माप(काष्ठा sockaddr_storage))
		kmsg->msg_namelen = माप(काष्ठा sockaddr_storage);

	अगर (save_addr)
		*save_addr = msg.msg_name;

	अगर (msg.msg_name && kmsg->msg_namelen) अणु
		अगर (!save_addr) अणु
			err = move_addr_to_kernel(msg.msg_name,
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
	*uiov = msg.msg_iov;
	*nsegs = msg.msg_iovlen;
	वापस 0;
पूर्ण

अटल पूर्णांक copy_msghdr_from_user(काष्ठा msghdr *kmsg,
				 काष्ठा user_msghdr __user *umsg,
				 काष्ठा sockaddr __user **save_addr,
				 काष्ठा iovec **iov)
अणु
	काष्ठा user_msghdr msg;
	sमाप_प्रकार err;

	err = __copy_msghdr_from_user(kmsg, umsg, save_addr, &msg.msg_iov,
					&msg.msg_iovlen);
	अगर (err)
		वापस err;

	err = import_iovec(save_addr ? READ : WRITE,
			    msg.msg_iov, msg.msg_iovlen,
			    UIO_FASTIOV, iov, &kmsg->msg_iter);
	वापस err < 0 ? err : 0;
पूर्ण

अटल पूर्णांक ____sys_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg_sys,
			   अचिन्हित पूर्णांक flags, काष्ठा used_address *used_address,
			   अचिन्हित पूर्णांक allowed_msghdr_flags)
अणु
	अचिन्हित अक्षर ctl[माप(काष्ठा cmsghdr) + 20]
				__aligned(माप(__kernel_माप_प्रकार));
	/* 20 is size of ipv6_pktinfo */
	अचिन्हित अक्षर *ctl_buf = ctl;
	पूर्णांक ctl_len;
	sमाप_प्रकार err;

	err = -ENOBUFS;

	अगर (msg_sys->msg_controllen > पूर्णांक_उच्च)
		जाओ out;
	flags |= (msg_sys->msg_flags & allowed_msghdr_flags);
	ctl_len = msg_sys->msg_controllen;
	अगर ((MSG_CMSG_COMPAT & flags) && ctl_len) अणु
		err =
		    cmsghdr_from_user_compat_to_kern(msg_sys, sock->sk, ctl,
						     माप(ctl));
		अगर (err)
			जाओ out;
		ctl_buf = msg_sys->msg_control;
		ctl_len = msg_sys->msg_controllen;
	पूर्ण अन्यथा अगर (ctl_len) अणु
		BUILD_BUG_ON(माप(काष्ठा cmsghdr) !=
			     CMSG_ALIGN(माप(काष्ठा cmsghdr)));
		अगर (ctl_len > माप(ctl)) अणु
			ctl_buf = sock_kदो_स्मृति(sock->sk, ctl_len, GFP_KERNEL);
			अगर (ctl_buf == शून्य)
				जाओ out;
		पूर्ण
		err = -EFAULT;
		अगर (copy_from_user(ctl_buf, msg_sys->msg_control_user, ctl_len))
			जाओ out_मुक्तctl;
		msg_sys->msg_control = ctl_buf;
		msg_sys->msg_control_is_user = false;
	पूर्ण
	msg_sys->msg_flags = flags;

	अगर (sock->file->f_flags & O_NONBLOCK)
		msg_sys->msg_flags |= MSG_DONTWAIT;
	/*
	 * If this is sendmmsg() and current destination address is same as
	 * previously succeeded address, omit asking LSM's decision.
	 * used_address->name_len is initialized to अच_पूर्णांक_उच्च so that the first
	 * destination address never matches.
	 */
	अगर (used_address && msg_sys->msg_name &&
	    used_address->name_len == msg_sys->msg_namelen &&
	    !स_भेद(&used_address->name, msg_sys->msg_name,
		    used_address->name_len)) अणु
		err = sock_sendmsg_nosec(sock, msg_sys);
		जाओ out_मुक्तctl;
	पूर्ण
	err = sock_sendmsg(sock, msg_sys);
	/*
	 * If this is sendmmsg() and sending to current destination address was
	 * successful, remember it.
	 */
	अगर (used_address && err >= 0) अणु
		used_address->name_len = msg_sys->msg_namelen;
		अगर (msg_sys->msg_name)
			स_नकल(&used_address->name, msg_sys->msg_name,
			       used_address->name_len);
	पूर्ण

out_मुक्तctl:
	अगर (ctl_buf != ctl)
		sock_kमुक्त_s(sock->sk, ctl_buf, ctl_len);
out:
	वापस err;
पूर्ण

पूर्णांक sendmsg_copy_msghdr(काष्ठा msghdr *msg,
			काष्ठा user_msghdr __user *umsg, अचिन्हित flags,
			काष्ठा iovec **iov)
अणु
	पूर्णांक err;

	अगर (flags & MSG_CMSG_COMPAT) अणु
		काष्ठा compat_msghdr __user *msg_compat;

		msg_compat = (काष्ठा compat_msghdr __user *) umsg;
		err = get_compat_msghdr(msg, msg_compat, शून्य, iov);
	पूर्ण अन्यथा अणु
		err = copy_msghdr_from_user(msg, umsg, शून्य, iov);
	पूर्ण
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ___sys_sendmsg(काष्ठा socket *sock, काष्ठा user_msghdr __user *msg,
			 काष्ठा msghdr *msg_sys, अचिन्हित पूर्णांक flags,
			 काष्ठा used_address *used_address,
			 अचिन्हित पूर्णांक allowed_msghdr_flags)
अणु
	काष्ठा sockaddr_storage address;
	काष्ठा iovec iovstack[UIO_FASTIOV], *iov = iovstack;
	sमाप_प्रकार err;

	msg_sys->msg_name = &address;

	err = sendmsg_copy_msghdr(msg_sys, msg, flags, &iov);
	अगर (err < 0)
		वापस err;

	err = ____sys_sendmsg(sock, msg_sys, flags, used_address,
				allowed_msghdr_flags);
	kमुक्त(iov);
	वापस err;
पूर्ण

/*
 *	BSD sendmsg पूर्णांकerface
 */
दीर्घ __sys_sendmsg_sock(काष्ठा socket *sock, काष्ठा msghdr *msg,
			अचिन्हित पूर्णांक flags)
अणु
	वापस ____sys_sendmsg(sock, msg, flags, शून्य, 0);
पूर्ण

दीर्घ __sys_sendmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg, अचिन्हित पूर्णांक flags,
		   bool क्रमbid_cmsg_compat)
अणु
	पूर्णांक fput_needed, err;
	काष्ठा msghdr msg_sys;
	काष्ठा socket *sock;

	अगर (क्रमbid_cmsg_compat && (flags & MSG_CMSG_COMPAT))
		वापस -EINVAL;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		जाओ out;

	err = ___sys_sendmsg(sock, msg, &msg_sys, flags, शून्य, 0);

	fput_light(sock->file, fput_needed);
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE3(sendmsg, पूर्णांक, fd, काष्ठा user_msghdr __user *, msg, अचिन्हित पूर्णांक, flags)
अणु
	वापस __sys_sendmsg(fd, msg, flags, true);
पूर्ण

/*
 *	Linux sendmmsg पूर्णांकerface
 */

पूर्णांक __sys_sendmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *mmsg, अचिन्हित पूर्णांक vlen,
		   अचिन्हित पूर्णांक flags, bool क्रमbid_cmsg_compat)
अणु
	पूर्णांक fput_needed, err, datagrams;
	काष्ठा socket *sock;
	काष्ठा mmsghdr __user *entry;
	काष्ठा compat_mmsghdr __user *compat_entry;
	काष्ठा msghdr msg_sys;
	काष्ठा used_address used_address;
	अचिन्हित पूर्णांक oflags = flags;

	अगर (क्रमbid_cmsg_compat && (flags & MSG_CMSG_COMPAT))
		वापस -EINVAL;

	अगर (vlen > UIO_MAXIOV)
		vlen = UIO_MAXIOV;

	datagrams = 0;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		वापस err;

	used_address.name_len = अच_पूर्णांक_उच्च;
	entry = mmsg;
	compat_entry = (काष्ठा compat_mmsghdr __user *)mmsg;
	err = 0;
	flags |= MSG_BATCH;

	जबतक (datagrams < vlen) अणु
		अगर (datagrams == vlen - 1)
			flags = oflags;

		अगर (MSG_CMSG_COMPAT & flags) अणु
			err = ___sys_sendmsg(sock, (काष्ठा user_msghdr __user *)compat_entry,
					     &msg_sys, flags, &used_address, MSG_EOR);
			अगर (err < 0)
				अवरोध;
			err = __put_user(err, &compat_entry->msg_len);
			++compat_entry;
		पूर्ण अन्यथा अणु
			err = ___sys_sendmsg(sock,
					     (काष्ठा user_msghdr __user *)entry,
					     &msg_sys, flags, &used_address, MSG_EOR);
			अगर (err < 0)
				अवरोध;
			err = put_user(err, &entry->msg_len);
			++entry;
		पूर्ण

		अगर (err)
			अवरोध;
		++datagrams;
		अगर (msg_data_left(&msg_sys))
			अवरोध;
		cond_resched();
	पूर्ण

	fput_light(sock->file, fput_needed);

	/* We only वापस an error अगर no datagrams were able to be sent */
	अगर (datagrams != 0)
		वापस datagrams;

	वापस err;
पूर्ण

SYSCALL_DEFINE4(sendmmsg, पूर्णांक, fd, काष्ठा mmsghdr __user *, mmsg,
		अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags)
अणु
	वापस __sys_sendmmsg(fd, mmsg, vlen, flags, true);
पूर्ण

पूर्णांक recvmsg_copy_msghdr(काष्ठा msghdr *msg,
			काष्ठा user_msghdr __user *umsg, अचिन्हित flags,
			काष्ठा sockaddr __user **uaddr,
			काष्ठा iovec **iov)
अणु
	sमाप_प्रकार err;

	अगर (MSG_CMSG_COMPAT & flags) अणु
		काष्ठा compat_msghdr __user *msg_compat;

		msg_compat = (काष्ठा compat_msghdr __user *) umsg;
		err = get_compat_msghdr(msg, msg_compat, uaddr, iov);
	पूर्ण अन्यथा अणु
		err = copy_msghdr_from_user(msg, umsg, uaddr, iov);
	पूर्ण
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ____sys_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg_sys,
			   काष्ठा user_msghdr __user *msg,
			   काष्ठा sockaddr __user *uaddr,
			   अचिन्हित पूर्णांक flags, पूर्णांक nosec)
अणु
	काष्ठा compat_msghdr __user *msg_compat =
					(काष्ठा compat_msghdr __user *) msg;
	पूर्णांक __user *uaddr_len = COMPAT_NAMELEN(msg);
	काष्ठा sockaddr_storage addr;
	अचिन्हित दीर्घ cmsg_ptr;
	पूर्णांक len;
	sमाप_प्रकार err;

	msg_sys->msg_name = &addr;
	cmsg_ptr = (अचिन्हित दीर्घ)msg_sys->msg_control;
	msg_sys->msg_flags = flags & (MSG_CMSG_CLOEXEC|MSG_CMSG_COMPAT);

	/* We assume all kernel code knows the size of sockaddr_storage */
	msg_sys->msg_namelen = 0;

	अगर (sock->file->f_flags & O_NONBLOCK)
		flags |= MSG_DONTWAIT;

	अगर (unlikely(nosec))
		err = sock_recvmsg_nosec(sock, msg_sys, flags);
	अन्यथा
		err = sock_recvmsg(sock, msg_sys, flags);

	अगर (err < 0)
		जाओ out;
	len = err;

	अगर (uaddr != शून्य) अणु
		err = move_addr_to_user(&addr,
					msg_sys->msg_namelen, uaddr,
					uaddr_len);
		अगर (err < 0)
			जाओ out;
	पूर्ण
	err = __put_user((msg_sys->msg_flags & ~MSG_CMSG_COMPAT),
			 COMPAT_FLAGS(msg));
	अगर (err)
		जाओ out;
	अगर (MSG_CMSG_COMPAT & flags)
		err = __put_user((अचिन्हित दीर्घ)msg_sys->msg_control - cmsg_ptr,
				 &msg_compat->msg_controllen);
	अन्यथा
		err = __put_user((अचिन्हित दीर्घ)msg_sys->msg_control - cmsg_ptr,
				 &msg->msg_controllen);
	अगर (err)
		जाओ out;
	err = len;
out:
	वापस err;
पूर्ण

अटल पूर्णांक ___sys_recvmsg(काष्ठा socket *sock, काष्ठा user_msghdr __user *msg,
			 काष्ठा msghdr *msg_sys, अचिन्हित पूर्णांक flags, पूर्णांक nosec)
अणु
	काष्ठा iovec iovstack[UIO_FASTIOV], *iov = iovstack;
	/* user mode address poपूर्णांकers */
	काष्ठा sockaddr __user *uaddr;
	sमाप_प्रकार err;

	err = recvmsg_copy_msghdr(msg_sys, msg, flags, &uaddr, &iov);
	अगर (err < 0)
		वापस err;

	err = ____sys_recvmsg(sock, msg_sys, msg, uaddr, flags, nosec);
	kमुक्त(iov);
	वापस err;
पूर्ण

/*
 *	BSD recvmsg पूर्णांकerface
 */

दीर्घ __sys_recvmsg_sock(काष्ठा socket *sock, काष्ठा msghdr *msg,
			काष्ठा user_msghdr __user *umsg,
			काष्ठा sockaddr __user *uaddr, अचिन्हित पूर्णांक flags)
अणु
	वापस ____sys_recvmsg(sock, msg, umsg, uaddr, flags, 0);
पूर्ण

दीर्घ __sys_recvmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg, अचिन्हित पूर्णांक flags,
		   bool क्रमbid_cmsg_compat)
अणु
	पूर्णांक fput_needed, err;
	काष्ठा msghdr msg_sys;
	काष्ठा socket *sock;

	अगर (क्रमbid_cmsg_compat && (flags & MSG_CMSG_COMPAT))
		वापस -EINVAL;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		जाओ out;

	err = ___sys_recvmsg(sock, msg, &msg_sys, flags, 0);

	fput_light(sock->file, fput_needed);
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE3(recvmsg, पूर्णांक, fd, काष्ठा user_msghdr __user *, msg,
		अचिन्हित पूर्णांक, flags)
अणु
	वापस __sys_recvmsg(fd, msg, flags, true);
पूर्ण

/*
 *     Linux recvmmsg पूर्णांकerface
 */

अटल पूर्णांक करो_recvmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *mmsg,
			  अचिन्हित पूर्णांक vlen, अचिन्हित पूर्णांक flags,
			  काष्ठा बारpec64 *समयout)
अणु
	पूर्णांक fput_needed, err, datagrams;
	काष्ठा socket *sock;
	काष्ठा mmsghdr __user *entry;
	काष्ठा compat_mmsghdr __user *compat_entry;
	काष्ठा msghdr msg_sys;
	काष्ठा बारpec64 end_समय;
	काष्ठा बारpec64 समयout64;

	अगर (समयout &&
	    poll_select_set_समयout(&end_समय, समयout->tv_sec,
				    समयout->tv_nsec))
		वापस -EINVAL;

	datagrams = 0;

	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	अगर (!sock)
		वापस err;

	अगर (likely(!(flags & MSG_ERRQUEUE))) अणु
		err = sock_error(sock->sk);
		अगर (err) अणु
			datagrams = err;
			जाओ out_put;
		पूर्ण
	पूर्ण

	entry = mmsg;
	compat_entry = (काष्ठा compat_mmsghdr __user *)mmsg;

	जबतक (datagrams < vlen) अणु
		/*
		 * No need to ask LSM क्रम more than the first datagram.
		 */
		अगर (MSG_CMSG_COMPAT & flags) अणु
			err = ___sys_recvmsg(sock, (काष्ठा user_msghdr __user *)compat_entry,
					     &msg_sys, flags & ~MSG_WAITFORONE,
					     datagrams);
			अगर (err < 0)
				अवरोध;
			err = __put_user(err, &compat_entry->msg_len);
			++compat_entry;
		पूर्ण अन्यथा अणु
			err = ___sys_recvmsg(sock,
					     (काष्ठा user_msghdr __user *)entry,
					     &msg_sys, flags & ~MSG_WAITFORONE,
					     datagrams);
			अगर (err < 0)
				अवरोध;
			err = put_user(err, &entry->msg_len);
			++entry;
		पूर्ण

		अगर (err)
			अवरोध;
		++datagrams;

		/* MSG_WAITFORONE turns on MSG_DONTWAIT after one packet */
		अगर (flags & MSG_WAITFORONE)
			flags |= MSG_DONTWAIT;

		अगर (समयout) अणु
			kसमय_get_ts64(&समयout64);
			*समयout = बारpec64_sub(end_समय, समयout64);
			अगर (समयout->tv_sec < 0) अणु
				समयout->tv_sec = समयout->tv_nsec = 0;
				अवरोध;
			पूर्ण

			/* Timeout, वापस less than vlen datagrams */
			अगर (समयout->tv_nsec == 0 && समयout->tv_sec == 0)
				अवरोध;
		पूर्ण

		/* Out of band data, वापस right away */
		अगर (msg_sys.msg_flags & MSG_OOB)
			अवरोध;
		cond_resched();
	पूर्ण

	अगर (err == 0)
		जाओ out_put;

	अगर (datagrams == 0) अणु
		datagrams = err;
		जाओ out_put;
	पूर्ण

	/*
	 * We may वापस less entries than requested (vlen) अगर the
	 * sock is non block and there aren't enough datagrams...
	 */
	अगर (err != -EAGAIN) अणु
		/*
		 * ... or  अगर recvmsg वापसs an error after we
		 * received some datagrams, where we record the
		 * error to वापस on the next call or अगर the
		 * app asks about it using माला_लोockopt(SO_ERROR).
		 */
		sock->sk->sk_err = -err;
	पूर्ण
out_put:
	fput_light(sock->file, fput_needed);

	वापस datagrams;
पूर्ण

पूर्णांक __sys_recvmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *mmsg,
		   अचिन्हित पूर्णांक vlen, अचिन्हित पूर्णांक flags,
		   काष्ठा __kernel_बारpec __user *समयout,
		   काष्ठा old_बारpec32 __user *समयout32)
अणु
	पूर्णांक datagrams;
	काष्ठा बारpec64 समयout_sys;

	अगर (समयout && get_बारpec64(&समयout_sys, समयout))
		वापस -EFAULT;

	अगर (समयout32 && get_old_बारpec32(&समयout_sys, समयout32))
		वापस -EFAULT;

	अगर (!समयout && !समयout32)
		वापस करो_recvmmsg(fd, mmsg, vlen, flags, शून्य);

	datagrams = करो_recvmmsg(fd, mmsg, vlen, flags, &समयout_sys);

	अगर (datagrams <= 0)
		वापस datagrams;

	अगर (समयout && put_बारpec64(&समयout_sys, समयout))
		datagrams = -EFAULT;

	अगर (समयout32 && put_old_बारpec32(&समयout_sys, समयout32))
		datagrams = -EFAULT;

	वापस datagrams;
पूर्ण

SYSCALL_DEFINE5(recvmmsg, पूर्णांक, fd, काष्ठा mmsghdr __user *, mmsg,
		अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags,
		काष्ठा __kernel_बारpec __user *, समयout)
अणु
	अगर (flags & MSG_CMSG_COMPAT)
		वापस -EINVAL;

	वापस __sys_recvmmsg(fd, mmsg, vlen, flags, समयout, शून्य);
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE5(recvmmsg_समय32, पूर्णांक, fd, काष्ठा mmsghdr __user *, mmsg,
		अचिन्हित पूर्णांक, vlen, अचिन्हित पूर्णांक, flags,
		काष्ठा old_बारpec32 __user *, समयout)
अणु
	अगर (flags & MSG_CMSG_COMPAT)
		वापस -EINVAL;

	वापस __sys_recvmmsg(fd, mmsg, vlen, flags, शून्य, समयout);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_SOCKETCALL
/* Argument list sizes क्रम sys_socketcall */
#घोषणा AL(x) ((x) * माप(अचिन्हित दीर्घ))
अटल स्थिर अचिन्हित अक्षर nargs[21] = अणु
	AL(0), AL(3), AL(3), AL(3), AL(2), AL(3),
	AL(3), AL(3), AL(4), AL(4), AL(4), AL(6),
	AL(6), AL(2), AL(5), AL(5), AL(3), AL(3),
	AL(4), AL(5), AL(4)
पूर्ण;

#अघोषित AL

/*
 *	System call vectors.
 *
 *	Argument checking cleaned up. Saved 20% in size.
 *  This function करोesn't need to set the kernel lock because
 *  it is set by the callees.
 */

SYSCALL_DEFINE2(socketcall, पूर्णांक, call, अचिन्हित दीर्घ __user *, args)
अणु
	अचिन्हित दीर्घ a[AUDITSC_ARGS];
	अचिन्हित दीर्घ a0, a1;
	पूर्णांक err;
	अचिन्हित पूर्णांक len;

	अगर (call < 1 || call > SYS_SENDMMSG)
		वापस -EINVAL;
	call = array_index_nospec(call, SYS_SENDMMSG + 1);

	len = nargs[call];
	अगर (len > माप(a))
		वापस -EINVAL;

	/* copy_from_user should be SMP safe. */
	अगर (copy_from_user(a, args, len))
		वापस -EFAULT;

	err = audit_socketcall(nargs[call] / माप(अचिन्हित दीर्घ), a);
	अगर (err)
		वापस err;

	a0 = a[0];
	a1 = a[1];

	चयन (call) अणु
	हाल SYS_SOCKET:
		err = __sys_socket(a0, a1, a[2]);
		अवरोध;
	हाल SYS_BIND:
		err = __sys_bind(a0, (काष्ठा sockaddr __user *)a1, a[2]);
		अवरोध;
	हाल SYS_CONNECT:
		err = __sys_connect(a0, (काष्ठा sockaddr __user *)a1, a[2]);
		अवरोध;
	हाल SYS_LISTEN:
		err = __sys_listen(a0, a1);
		अवरोध;
	हाल SYS_ACCEPT:
		err = __sys_accept4(a0, (काष्ठा sockaddr __user *)a1,
				    (पूर्णांक __user *)a[2], 0);
		अवरोध;
	हाल SYS_GETSOCKNAME:
		err =
		    __sys_माला_लोockname(a0, (काष्ठा sockaddr __user *)a1,
				      (पूर्णांक __user *)a[2]);
		अवरोध;
	हाल SYS_GETPEERNAME:
		err =
		    __sys_getpeername(a0, (काष्ठा sockaddr __user *)a1,
				      (पूर्णांक __user *)a[2]);
		अवरोध;
	हाल SYS_SOCKETPAIR:
		err = __sys_socketpair(a0, a1, a[2], (पूर्णांक __user *)a[3]);
		अवरोध;
	हाल SYS_SEND:
		err = __sys_sendto(a0, (व्योम __user *)a1, a[2], a[3],
				   शून्य, 0);
		अवरोध;
	हाल SYS_SENDTO:
		err = __sys_sendto(a0, (व्योम __user *)a1, a[2], a[3],
				   (काष्ठा sockaddr __user *)a[4], a[5]);
		अवरोध;
	हाल SYS_RECV:
		err = __sys_recvfrom(a0, (व्योम __user *)a1, a[2], a[3],
				     शून्य, शून्य);
		अवरोध;
	हाल SYS_RECVFROM:
		err = __sys_recvfrom(a0, (व्योम __user *)a1, a[2], a[3],
				     (काष्ठा sockaddr __user *)a[4],
				     (पूर्णांक __user *)a[5]);
		अवरोध;
	हाल SYS_SHUTDOWN:
		err = __sys_shutकरोwn(a0, a1);
		अवरोध;
	हाल SYS_SETSOCKOPT:
		err = __sys_setsockopt(a0, a1, a[2], (अक्षर __user *)a[3],
				       a[4]);
		अवरोध;
	हाल SYS_GETSOCKOPT:
		err =
		    __sys_माला_लोockopt(a0, a1, a[2], (अक्षर __user *)a[3],
				     (पूर्णांक __user *)a[4]);
		अवरोध;
	हाल SYS_SENDMSG:
		err = __sys_sendmsg(a0, (काष्ठा user_msghdr __user *)a1,
				    a[2], true);
		अवरोध;
	हाल SYS_SENDMMSG:
		err = __sys_sendmmsg(a0, (काष्ठा mmsghdr __user *)a1, a[2],
				     a[3], true);
		अवरोध;
	हाल SYS_RECVMSG:
		err = __sys_recvmsg(a0, (काष्ठा user_msghdr __user *)a1,
				    a[2], true);
		अवरोध;
	हाल SYS_RECVMMSG:
		अगर (IS_ENABLED(CONFIG_64BIT))
			err = __sys_recvmmsg(a0, (काष्ठा mmsghdr __user *)a1,
					     a[2], a[3],
					     (काष्ठा __kernel_बारpec __user *)a[4],
					     शून्य);
		अन्यथा
			err = __sys_recvmmsg(a0, (काष्ठा mmsghdr __user *)a1,
					     a[2], a[3], शून्य,
					     (काष्ठा old_बारpec32 __user *)a[4]);
		अवरोध;
	हाल SYS_ACCEPT4:
		err = __sys_accept4(a0, (काष्ठा sockaddr __user *)a1,
				    (पूर्णांक __user *)a[2], a[3]);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

#पूर्ण_अगर				/* __ARCH_WANT_SYS_SOCKETCALL */

/**
 *	sock_रेजिस्टर - add a socket protocol handler
 *	@ops: description of protocol
 *
 *	This function is called by a protocol handler that wants to
 *	advertise its address family, and have it linked पूर्णांकo the
 *	socket पूर्णांकerface. The value ops->family corresponds to the
 *	socket प्रणाली call protocol family.
 */
पूर्णांक sock_रेजिस्टर(स्थिर काष्ठा net_proto_family *ops)
अणु
	पूर्णांक err;

	अगर (ops->family >= NPROTO) अणु
		pr_crit("protocol %d >= NPROTO(%d)\n", ops->family, NPROTO);
		वापस -ENOBUFS;
	पूर्ण

	spin_lock(&net_family_lock);
	अगर (rcu_dereference_रक्षित(net_families[ops->family],
				      lockdep_is_held(&net_family_lock)))
		err = -EEXIST;
	अन्यथा अणु
		rcu_assign_poपूर्णांकer(net_families[ops->family], ops);
		err = 0;
	पूर्ण
	spin_unlock(&net_family_lock);

	pr_info("NET: Registered protocol family %d\n", ops->family);
	वापस err;
पूर्ण
EXPORT_SYMBOL(sock_रेजिस्टर);

/**
 *	sock_unरेजिस्टर - हटाओ a protocol handler
 *	@family: protocol family to हटाओ
 *
 *	This function is called by a protocol handler that wants to
 *	हटाओ its address family, and have it unlinked from the
 *	new socket creation.
 *
 *	If protocol handler is a module, then it can use module reference
 *	counts to protect against new references. If protocol handler is not
 *	a module then it needs to provide its own protection in
 *	the ops->create routine.
 */
व्योम sock_unरेजिस्टर(पूर्णांक family)
अणु
	BUG_ON(family < 0 || family >= NPROTO);

	spin_lock(&net_family_lock);
	RCU_INIT_POINTER(net_families[family], शून्य);
	spin_unlock(&net_family_lock);

	synchronize_rcu();

	pr_info("NET: Unregistered protocol family %d\n", family);
पूर्ण
EXPORT_SYMBOL(sock_unरेजिस्टर);

bool sock_is_रेजिस्टरed(पूर्णांक family)
अणु
	वापस family < NPROTO && rcu_access_poपूर्णांकer(net_families[family]);
पूर्ण

अटल पूर्णांक __init sock_init(व्योम)
अणु
	पूर्णांक err;
	/*
	 *      Initialize the network sysctl infraकाष्ठाure.
	 */
	err = net_sysctl_init();
	अगर (err)
		जाओ out;

	/*
	 *      Initialize skbuff SLAB cache
	 */
	skb_init();

	/*
	 *      Initialize the protocols module.
	 */

	init_inodecache();

	err = रेजिस्टर_fileप्रणाली(&sock_fs_type);
	अगर (err)
		जाओ out;
	sock_mnt = kern_mount(&sock_fs_type);
	अगर (IS_ERR(sock_mnt)) अणु
		err = PTR_ERR(sock_mnt);
		जाओ out_mount;
	पूर्ण

	/* The real protocol initialization is perक्रमmed in later initcalls.
	 */

#अगर_घोषित CONFIG_NETFILTER
	err = netfilter_init();
	अगर (err)
		जाओ out;
#पूर्ण_अगर

	ptp_classअगरier_init();

out:
	वापस err;

out_mount:
	unरेजिस्टर_fileप्रणाली(&sock_fs_type);
	जाओ out;
पूर्ण

core_initcall(sock_init);	/* early initcall */

#अगर_घोषित CONFIG_PROC_FS
व्योम socket_seq_show(काष्ठा seq_file *seq)
अणु
	seq_म_लिखो(seq, "sockets: used %d\n",
		   sock_inuse_get(seq->निजी));
पूर्ण
#पूर्ण_अगर				/* CONFIG_PROC_FS */

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_dev_अगरconf(काष्ठा net *net, काष्ठा compat_अगरconf __user *uअगरc32)
अणु
	काष्ठा compat_अगरconf अगरc32;
	काष्ठा अगरconf अगरc;
	पूर्णांक err;

	अगर (copy_from_user(&अगरc32, uअगरc32, माप(काष्ठा compat_अगरconf)))
		वापस -EFAULT;

	अगरc.अगरc_len = अगरc32.अगरc_len;
	अगरc.अगरc_req = compat_ptr(अगरc32.अगरcbuf);

	rtnl_lock();
	err = dev_अगरconf(net, &अगरc, माप(काष्ठा compat_अगरreq));
	rtnl_unlock();
	अगर (err)
		वापस err;

	अगरc32.अगरc_len = अगरc.अगरc_len;
	अगर (copy_to_user(uअगरc32, &अगरc32, माप(काष्ठा compat_अगरconf)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_ioctl(काष्ठा net *net, काष्ठा compat_अगरreq __user *अगरr32)
अणु
	काष्ठा compat_ethtool_rxnfc __user *compat_rxnfc;
	bool convert_in = false, convert_out = false;
	माप_प्रकार buf_size = 0;
	काष्ठा ethtool_rxnfc __user *rxnfc = शून्य;
	काष्ठा अगरreq अगरr;
	u32 rule_cnt = 0, actual_rule_cnt;
	u32 ethcmd;
	u32 data;
	पूर्णांक ret;

	अगर (get_user(data, &अगरr32->अगरr_अगरru.अगरru_data))
		वापस -EFAULT;

	compat_rxnfc = compat_ptr(data);

	अगर (get_user(ethcmd, &compat_rxnfc->cmd))
		वापस -EFAULT;

	/* Most ethtool काष्ठाures are defined without padding.
	 * Unक्रमtunately काष्ठा ethtool_rxnfc is an exception.
	 */
	चयन (ethcmd) अणु
	शेष:
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		/* Buffer size is variable */
		अगर (get_user(rule_cnt, &compat_rxnfc->rule_cnt))
			वापस -EFAULT;
		अगर (rule_cnt > KMALLOC_MAX_SIZE / माप(u32))
			वापस -ENOMEM;
		buf_size += rule_cnt * माप(u32);
		fallthrough;
	हाल ETHTOOL_GRXRINGS:
	हाल ETHTOOL_GRXCLSRLCNT:
	हाल ETHTOOL_GRXCLSRULE:
	हाल ETHTOOL_SRXCLSRLINS:
		convert_out = true;
		fallthrough;
	हाल ETHTOOL_SRXCLSRLDEL:
		buf_size += माप(काष्ठा ethtool_rxnfc);
		convert_in = true;
		rxnfc = compat_alloc_user_space(buf_size);
		अवरोध;
	पूर्ण

	अगर (copy_from_user(&अगरr.अगरr_name, &अगरr32->अगरr_name, IFNAMSIZ))
		वापस -EFAULT;

	अगरr.अगरr_data = convert_in ? rxnfc : (व्योम __user *)compat_rxnfc;

	अगर (convert_in) अणु
		/* We expect there to be holes between fs.m_ext and
		 * fs.ring_cookie and at the end of fs, but nowhere अन्यथा.
		 */
		BUILD_BUG_ON(दुरत्व(काष्ठा compat_ethtool_rxnfc, fs.m_ext) +
			     माप(compat_rxnfc->fs.m_ext) !=
			     दुरत्व(काष्ठा ethtool_rxnfc, fs.m_ext) +
			     माप(rxnfc->fs.m_ext));
		BUILD_BUG_ON(
			दुरत्व(काष्ठा compat_ethtool_rxnfc, fs.location) -
			दुरत्व(काष्ठा compat_ethtool_rxnfc, fs.ring_cookie) !=
			दुरत्व(काष्ठा ethtool_rxnfc, fs.location) -
			दुरत्व(काष्ठा ethtool_rxnfc, fs.ring_cookie));

		अगर (copy_in_user(rxnfc, compat_rxnfc,
				 (व्योम __user *)(&rxnfc->fs.m_ext + 1) -
				 (व्योम __user *)rxnfc) ||
		    copy_in_user(&rxnfc->fs.ring_cookie,
				 &compat_rxnfc->fs.ring_cookie,
				 (व्योम __user *)(&rxnfc->fs.location + 1) -
				 (व्योम __user *)&rxnfc->fs.ring_cookie))
			वापस -EFAULT;
		अगर (ethcmd == ETHTOOL_GRXCLSRLALL) अणु
			अगर (put_user(rule_cnt, &rxnfc->rule_cnt))
				वापस -EFAULT;
		पूर्ण अन्यथा अगर (copy_in_user(&rxnfc->rule_cnt,
					&compat_rxnfc->rule_cnt,
					माप(rxnfc->rule_cnt)))
			वापस -EFAULT;
	पूर्ण

	ret = dev_ioctl(net, SIOCETHTOOL, &अगरr, शून्य);
	अगर (ret)
		वापस ret;

	अगर (convert_out) अणु
		अगर (copy_in_user(compat_rxnfc, rxnfc,
				 (स्थिर व्योम __user *)(&rxnfc->fs.m_ext + 1) -
				 (स्थिर व्योम __user *)rxnfc) ||
		    copy_in_user(&compat_rxnfc->fs.ring_cookie,
				 &rxnfc->fs.ring_cookie,
				 (स्थिर व्योम __user *)(&rxnfc->fs.location + 1) -
				 (स्थिर व्योम __user *)&rxnfc->fs.ring_cookie) ||
		    copy_in_user(&compat_rxnfc->rule_cnt, &rxnfc->rule_cnt,
				 माप(rxnfc->rule_cnt)))
			वापस -EFAULT;

		अगर (ethcmd == ETHTOOL_GRXCLSRLALL) अणु
			/* As an optimisation, we only copy the actual
			 * number of rules that the underlying
			 * function वापसed.  Since Mallory might
			 * change the rule count in user memory, we
			 * check that it is less than the rule count
			 * originally given (as the user buffer size),
			 * which has been range-checked.
			 */
			अगर (get_user(actual_rule_cnt, &rxnfc->rule_cnt))
				वापस -EFAULT;
			अगर (actual_rule_cnt < rule_cnt)
				rule_cnt = actual_rule_cnt;
			अगर (copy_in_user(&compat_rxnfc->rule_locs[0],
					 &rxnfc->rule_locs[0],
					 rule_cnt * माप(u32)))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक compat_siocwandev(काष्ठा net *net, काष्ठा compat_अगरreq __user *uअगरr32)
अणु
	compat_uptr_t uptr32;
	काष्ठा अगरreq अगरr;
	व्योम __user *saved;
	पूर्णांक err;

	अगर (copy_from_user(&अगरr, uअगरr32, माप(काष्ठा compat_अगरreq)))
		वापस -EFAULT;

	अगर (get_user(uptr32, &uअगरr32->अगरr_settings.अगरs_अगरsu))
		वापस -EFAULT;

	saved = अगरr.अगरr_settings.अगरs_अगरsu.raw_hdlc;
	अगरr.अगरr_settings.अगरs_अगरsu.raw_hdlc = compat_ptr(uptr32);

	err = dev_ioctl(net, SIOCWANDEV, &अगरr, शून्य);
	अगर (!err) अणु
		अगरr.अगरr_settings.अगरs_अगरsu.raw_hdlc = saved;
		अगर (copy_to_user(uअगरr32, &अगरr, माप(काष्ठा compat_अगरreq)))
			err = -EFAULT;
	पूर्ण
	वापस err;
पूर्ण

/* Handle ioctls that use अगरreq::अगरr_data and just need काष्ठा अगरreq converted */
अटल पूर्णांक compat_अगरr_data_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
				 काष्ठा compat_अगरreq __user *u_अगरreq32)
अणु
	काष्ठा अगरreq अगरreq;
	u32 data32;

	अगर (copy_from_user(अगरreq.अगरr_name, u_अगरreq32->अगरr_name, IFNAMSIZ))
		वापस -EFAULT;
	अगर (get_user(data32, &u_अगरreq32->अगरr_data))
		वापस -EFAULT;
	अगरreq.अगरr_data = compat_ptr(data32);

	वापस dev_ioctl(net, cmd, &अगरreq, शून्य);
पूर्ण

अटल पूर्णांक compat_अगरreq_ioctl(काष्ठा net *net, काष्ठा socket *sock,
			      अचिन्हित पूर्णांक cmd,
			      काष्ठा compat_अगरreq __user *uअगरr32)
अणु
	काष्ठा अगरreq __user *uअगरr;
	पूर्णांक err;

	/* Handle the fact that जबतक काष्ठा अगरreq has the same *layout* on
	 * 32/64 क्रम everything but अगरreq::अगरru_अगरmap and अगरreq::अगरru_data,
	 * which are handled अन्यथाwhere, it still has dअगरferent *size* due to
	 * अगरreq::अगरru_अगरmap (which is 16 bytes on 32 bit, 24 bytes on 64-bit,
	 * resulting in काष्ठा अगरreq being 32 and 40 bytes respectively).
	 * As a result, अगर the काष्ठा happens to be at the end of a page and
	 * the next page isn't पढ़ोable/writable, we get a fault. To prevent
	 * that, copy back and क्रमth to the full size.
	 */

	uअगरr = compat_alloc_user_space(माप(*uअगरr));
	अगर (copy_in_user(uअगरr, uअगरr32, माप(*uअगरr32)))
		वापस -EFAULT;

	err = sock_करो_ioctl(net, sock, cmd, (अचिन्हित दीर्घ)uअगरr);

	अगर (!err) अणु
		चयन (cmd) अणु
		हाल SIOCGIFFLAGS:
		हाल SIOCGIFMETRIC:
		हाल SIOCGIFMTU:
		हाल SIOCGIFMEM:
		हाल SIOCGIFHWADDR:
		हाल SIOCGIFINDEX:
		हाल SIOCGIFADDR:
		हाल SIOCGIFBRDADDR:
		हाल SIOCGIFDSTADDR:
		हाल SIOCGIFNETMASK:
		हाल SIOCGIFPFLAGS:
		हाल SIOCGIFTXQLEN:
		हाल SIOCGMIIPHY:
		हाल SIOCGMIIREG:
		हाल SIOCGIFNAME:
			अगर (copy_in_user(uअगरr32, uअगरr, माप(*uअगरr32)))
				err = -EFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक compat_sioc_अगरmap(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
			काष्ठा compat_अगरreq __user *uअगरr32)
अणु
	काष्ठा अगरreq अगरr;
	काष्ठा compat_अगरmap __user *uअगरmap32;
	पूर्णांक err;

	uअगरmap32 = &uअगरr32->अगरr_अगरru.अगरru_map;
	err = copy_from_user(&अगरr, uअगरr32, माप(अगरr.अगरr_name));
	err |= get_user(अगरr.अगरr_map.mem_start, &uअगरmap32->mem_start);
	err |= get_user(अगरr.अगरr_map.mem_end, &uअगरmap32->mem_end);
	err |= get_user(अगरr.अगरr_map.base_addr, &uअगरmap32->base_addr);
	err |= get_user(अगरr.अगरr_map.irq, &uअगरmap32->irq);
	err |= get_user(अगरr.अगरr_map.dma, &uअगरmap32->dma);
	err |= get_user(अगरr.अगरr_map.port, &uअगरmap32->port);
	अगर (err)
		वापस -EFAULT;

	err = dev_ioctl(net, cmd, &अगरr, शून्य);

	अगर (cmd == SIOCGIFMAP && !err) अणु
		err = copy_to_user(uअगरr32, &अगरr, माप(अगरr.अगरr_name));
		err |= put_user(अगरr.अगरr_map.mem_start, &uअगरmap32->mem_start);
		err |= put_user(अगरr.अगरr_map.mem_end, &uअगरmap32->mem_end);
		err |= put_user(अगरr.अगरr_map.base_addr, &uअगरmap32->base_addr);
		err |= put_user(अगरr.अगरr_map.irq, &uअगरmap32->irq);
		err |= put_user(अगरr.अगरr_map.dma, &uअगरmap32->dma);
		err |= put_user(अगरr.अगरr_map.port, &uअगरmap32->port);
		अगर (err)
			err = -EFAULT;
	पूर्ण
	वापस err;
पूर्ण

/* Since old style bridge ioctl's endup using SIOCDEVPRIVATE
 * क्रम some operations; this क्रमces use of the newer bridge-utils that
 * use compatible ioctls
 */
अटल पूर्णांक old_bridge_ioctl(compat_uदीर्घ_t __user *argp)
अणु
	compat_uदीर्घ_t पंचांगp;

	अगर (get_user(पंचांगp, argp))
		वापस -EFAULT;
	अगर (पंचांगp == BRCTL_GET_VERSION)
		वापस BRCTL_VERSION + 1;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक compat_sock_ioctl_trans(काष्ठा file *file, काष्ठा socket *sock,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);

	अगर (cmd >= SIOCDEVPRIVATE && cmd <= (SIOCDEVPRIVATE + 15))
		वापस compat_अगरr_data_ioctl(net, cmd, argp);

	चयन (cmd) अणु
	हाल SIOCSIFBR:
	हाल SIOCGIFBR:
		वापस old_bridge_ioctl(argp);
	हाल SIOCGIFCONF:
		वापस compat_dev_अगरconf(net, argp);
	हाल SIOCETHTOOL:
		वापस ethtool_ioctl(net, argp);
	हाल SIOCWANDEV:
		वापस compat_siocwandev(net, argp);
	हाल SIOCGIFMAP:
	हाल SIOCSIFMAP:
		वापस compat_sioc_अगरmap(net, cmd, argp);
	हाल SIOCGSTAMP_OLD:
	हाल SIOCGSTAMPNS_OLD:
		अगर (!sock->ops->gettstamp)
			वापस -ENOIOCTLCMD;
		वापस sock->ops->gettstamp(sock, argp, cmd == SIOCGSTAMP_OLD,
					    !COMPAT_USE_64BIT_TIME);

	हाल SIOCBONDSLAVEINFOQUERY:
	हाल SIOCBONDINFOQUERY:
	हाल SIOCSHWTSTAMP:
	हाल SIOCGHWTSTAMP:
		वापस compat_अगरr_data_ioctl(net, cmd, argp);

	हाल FIOSETOWN:
	हाल SIOCSPGRP:
	हाल FIOGETOWN:
	हाल SIOCGPGRP:
	हाल SIOCBRADDBR:
	हाल SIOCBRDELBR:
	हाल SIOCGIFVLAN:
	हाल SIOCSIFVLAN:
	हाल SIOCGSKNS:
	हाल SIOCGSTAMP_NEW:
	हाल SIOCGSTAMPNS_NEW:
		वापस sock_ioctl(file, cmd, arg);

	हाल SIOCGIFFLAGS:
	हाल SIOCSIFFLAGS:
	हाल SIOCGIFMETRIC:
	हाल SIOCSIFMETRIC:
	हाल SIOCGIFMTU:
	हाल SIOCSIFMTU:
	हाल SIOCGIFMEM:
	हाल SIOCSIFMEM:
	हाल SIOCGIFHWADDR:
	हाल SIOCSIFHWADDR:
	हाल SIOCADDMULTI:
	हाल SIOCDELMULTI:
	हाल SIOCGIFINDEX:
	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
	हाल SIOCSIFHWBROADCAST:
	हाल SIOCDIFADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCGIFDSTADDR:
	हाल SIOCSIFDSTADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCSIFNETMASK:
	हाल SIOCSIFPFLAGS:
	हाल SIOCGIFPFLAGS:
	हाल SIOCGIFTXQLEN:
	हाल SIOCSIFTXQLEN:
	हाल SIOCBRADDIF:
	हाल SIOCBRDELIF:
	हाल SIOCGIFNAME:
	हाल SIOCSIFNAME:
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
	हाल SIOCBONDENSLAVE:
	हाल SIOCBONDRELEASE:
	हाल SIOCBONDSETHWADDR:
	हाल SIOCBONDCHANGEACTIVE:
		वापस compat_अगरreq_ioctl(net, sock, cmd, argp);

	हाल SIOCSARP:
	हाल SIOCGARP:
	हाल SIOCDARP:
	हाल SIOCOUTQ:
	हाल SIOCOUTQNSD:
	हाल SIOCATMARK:
		वापस sock_करो_ioctl(net, sock, cmd, arg);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल दीर्घ compat_sock_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	काष्ठा socket *sock = file->निजी_data;
	पूर्णांक ret = -ENOIOCTLCMD;
	काष्ठा sock *sk;
	काष्ठा net *net;

	sk = sock->sk;
	net = sock_net(sk);

	अगर (sock->ops->compat_ioctl)
		ret = sock->ops->compat_ioctl(sock, cmd, arg);

	अगर (ret == -ENOIOCTLCMD &&
	    (cmd >= SIOCIWFIRST && cmd <= SIOCIWLAST))
		ret = compat_wext_handle_ioctl(net, cmd, arg);

	अगर (ret == -ENOIOCTLCMD)
		ret = compat_sock_ioctl_trans(file, sock, cmd, arg);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 *	kernel_bind - bind an address to a socket (kernel space)
 *	@sock: socket
 *	@addr: address
 *	@addrlen: length of address
 *
 *	Returns 0 or an error.
 */

पूर्णांक kernel_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addrlen)
अणु
	वापस sock->ops->bind(sock, addr, addrlen);
पूर्ण
EXPORT_SYMBOL(kernel_bind);

/**
 *	kernel_listen - move socket to listening state (kernel space)
 *	@sock: socket
 *	@backlog: pending connections queue size
 *
 *	Returns 0 or an error.
 */

पूर्णांक kernel_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस sock->ops->listen(sock, backlog);
पूर्ण
EXPORT_SYMBOL(kernel_listen);

/**
 *	kernel_accept - accept a connection (kernel space)
 *	@sock: listening socket
 *	@newsock: new connected socket
 *	@flags: flags
 *
 *	@flags must be SOCK_CLOEXEC, SOCK_NONBLOCK or 0.
 *	If it fails, @newsock is guaranteed to be %शून्य.
 *	Returns 0 or an error.
 */

पूर्णांक kernel_accept(काष्ठा socket *sock, काष्ठा socket **newsock, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	err = sock_create_lite(sk->sk_family, sk->sk_type, sk->sk_protocol,
			       newsock);
	अगर (err < 0)
		जाओ करोne;

	err = sock->ops->accept(sock, *newsock, flags, true);
	अगर (err < 0) अणु
		sock_release(*newsock);
		*newsock = शून्य;
		जाओ करोne;
	पूर्ण

	(*newsock)->ops = sock->ops;
	__module_get((*newsock)->ops->owner);

करोne:
	वापस err;
पूर्ण
EXPORT_SYMBOL(kernel_accept);

/**
 *	kernel_connect - connect a socket (kernel space)
 *	@sock: socket
 *	@addr: address
 *	@addrlen: address length
 *	@flags: flags (O_NONBLOCK, ...)
 *
 *	For datagram sockets, @addr is the address to which datagrams are sent
 *	by शेष, and the only address from which datagrams are received.
 *	For stream sockets, attempts to connect to @addr.
 *	Returns 0 or an error code.
 */

पूर्णांक kernel_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addrlen,
		   पूर्णांक flags)
अणु
	वापस sock->ops->connect(sock, addr, addrlen, flags);
पूर्ण
EXPORT_SYMBOL(kernel_connect);

/**
 *	kernel_माला_लोockname - get the address which the socket is bound (kernel space)
 *	@sock: socket
 *	@addr: address holder
 *
 * 	Fills the @addr poपूर्णांकer with the address which the socket is bound.
 *	Returns 0 or an error code.
 */

पूर्णांक kernel_माला_लोockname(काष्ठा socket *sock, काष्ठा sockaddr *addr)
अणु
	वापस sock->ops->getname(sock, addr, 0);
पूर्ण
EXPORT_SYMBOL(kernel_माला_लोockname);

/**
 *	kernel_getpeername - get the address which the socket is connected (kernel space)
 *	@sock: socket
 *	@addr: address holder
 *
 * 	Fills the @addr poपूर्णांकer with the address which the socket is connected.
 *	Returns 0 or an error code.
 */

पूर्णांक kernel_getpeername(काष्ठा socket *sock, काष्ठा sockaddr *addr)
अणु
	वापस sock->ops->getname(sock, addr, 1);
पूर्ण
EXPORT_SYMBOL(kernel_getpeername);

/**
 *	kernel_sendpage - send a &page through a socket (kernel space)
 *	@sock: socket
 *	@page: page
 *	@offset: page offset
 *	@size: total size in bytes
 *	@flags: flags (MSG_DONTWAIT, ...)
 *
 *	Returns the total amount sent in bytes or an error.
 */

पूर्णांक kernel_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset,
		    माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (sock->ops->sendpage) अणु
		/* Warn in हाल the improper page to zero-copy send */
		WARN_ONCE(!sendpage_ok(page), "improper page for zero-copy send");
		वापस sock->ops->sendpage(sock, page, offset, size, flags);
	पूर्ण
	वापस sock_no_sendpage(sock, page, offset, size, flags);
पूर्ण
EXPORT_SYMBOL(kernel_sendpage);

/**
 *	kernel_sendpage_locked - send a &page through the locked sock (kernel space)
 *	@sk: sock
 *	@page: page
 *	@offset: page offset
 *	@size: total size in bytes
 *	@flags: flags (MSG_DONTWAIT, ...)
 *
 *	Returns the total amount sent in bytes or an error.
 *	Caller must hold @sk.
 */

पूर्णांक kernel_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			   माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा socket *sock = sk->sk_socket;

	अगर (sock->ops->sendpage_locked)
		वापस sock->ops->sendpage_locked(sk, page, offset, size,
						  flags);

	वापस sock_no_sendpage_locked(sk, page, offset, size, flags);
पूर्ण
EXPORT_SYMBOL(kernel_sendpage_locked);

/**
 *	kernel_sock_shutकरोwn - shut करोwn part of a full-duplex connection (kernel space)
 *	@sock: socket
 *	@how: connection part
 *
 *	Returns 0 or an error.
 */

पूर्णांक kernel_sock_shutकरोwn(काष्ठा socket *sock, क्रमागत sock_shutकरोwn_cmd how)
अणु
	वापस sock->ops->shutकरोwn(sock, how);
पूर्ण
EXPORT_SYMBOL(kernel_sock_shutकरोwn);

/**
 *	kernel_sock_ip_overhead - वापसs the IP overhead imposed by a socket
 *	@sk: socket
 *
 *	This routine वापसs the IP overhead imposed by a socket i.e.
 *	the length of the underlying IP header, depending on whether
 *	this is an IPv4 or IPv6 socket and the length from IP options turned
 *	on at the socket. Assumes that the caller has a lock on the socket.
 */

u32 kernel_sock_ip_overhead(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet;
	काष्ठा ip_options_rcu *opt;
	u32 overhead = 0;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6_pinfo *np;
	काष्ठा ipv6_txoptions *optv6 = शून्य;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

	अगर (!sk)
		वापस overhead;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		inet = inet_sk(sk);
		overhead += माप(काष्ठा iphdr);
		opt = rcu_dereference_रक्षित(inet->inet_opt,
						sock_owned_by_user(sk));
		अगर (opt)
			overhead += opt->opt.optlen;
		वापस overhead;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		np = inet6_sk(sk);
		overhead += माप(काष्ठा ipv6hdr);
		अगर (np)
			optv6 = rcu_dereference_रक्षित(np->opt,
							  sock_owned_by_user(sk));
		अगर (optv6)
			overhead += (optv6->opt_flen + optv6->opt_nflen);
		वापस overhead;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */
	शेष: /* Returns 0 overhead अगर the socket is not ipv4 or ipv6 */
		वापस overhead;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kernel_sock_ip_overhead);
