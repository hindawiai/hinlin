<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NET		An implementation of the SOCKET network access protocol.
 *		This is the master header file क्रम the Linux NET layer,
 *		or, in plain English: the networking handling part of the
 *		kernel.
 *
 * Version:	@(#)net.h	1.0.3	05/25/93
 *
 * Authors:	Orest Zborowski, <obz@Kodak.COM>
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_NET_H
#घोषणा _LINUX_NET_H

#समावेश <linux/stringअगरy.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/रुको.h>
#समावेश <linux/fcntl.h>	/* For O_CLOEXEC and O_NONBLOCK */
#समावेश <linux/rcupdate.h>
#समावेश <linux/once.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sockptr.h>

#समावेश <uapi/linux/net.h>

काष्ठा poll_table_काष्ठा;
काष्ठा pipe_inode_info;
काष्ठा inode;
काष्ठा file;
काष्ठा net;

/* Historically, SOCKWQ_ASYNC_NOSPACE & SOCKWQ_ASYNC_WAITDATA were located
 * in sock->flags, but moved पूर्णांकo sk->sk_wq->flags to be RCU रक्षित.
 * Eventually all flags will be in sk->sk_wq->flags.
 */
#घोषणा SOCKWQ_ASYNC_NOSPACE	0
#घोषणा SOCKWQ_ASYNC_WAITDATA	1
#घोषणा SOCK_NOSPACE		2
#घोषणा SOCK_PASSCRED		3
#घोषणा SOCK_PASSSEC		4

#अगर_अघोषित ARCH_HAS_SOCKET_TYPES
/**
 * क्रमागत sock_type - Socket types
 * @SOCK_STREAM: stream (connection) socket
 * @SOCK_DGRAM: datagram (conn.less) socket
 * @SOCK_RAW: raw socket
 * @SOCK_RDM: reliably-delivered message
 * @SOCK_SEQPACKET: sequential packet socket
 * @SOCK_DCCP: Datagram Congestion Control Protocol socket
 * @SOCK_PACKET: linux specअगरic way of getting packets at the dev level.
 *		  For writing rarp and other similar things on the user level.
 *
 * When adding some new socket type please
 * grep ARCH_HAS_SOCKET_TYPE include/यंत्र-* /socket.h, at least MIPS
 * overrides this क्रमागत क्रम binary compat reasons.
 */
क्रमागत sock_type अणु
	SOCK_STREAM	= 1,
	SOCK_DGRAM	= 2,
	SOCK_RAW	= 3,
	SOCK_RDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
पूर्ण;

#घोषणा SOCK_MAX (SOCK_PACKET + 1)
/* Mask which covers at least up to SOCK_MASK-1.  The
 * reमुख्यing bits are used as flags. */
#घोषणा SOCK_TYPE_MASK 0xf

/* Flags क्रम socket, socketpair, accept4 */
#घोषणा SOCK_CLOEXEC	O_CLOEXEC
#अगर_अघोषित SOCK_NONBLOCK
#घोषणा SOCK_NONBLOCK	O_NONBLOCK
#पूर्ण_अगर

#पूर्ण_अगर /* ARCH_HAS_SOCKET_TYPES */

/**
 * क्रमागत sock_shutकरोwn_cmd - Shutकरोwn types
 * @SHUT_RD: shutकरोwn receptions
 * @SHUT_WR: shutकरोwn transmissions
 * @SHUT_RDWR: shutकरोwn receptions/transmissions
 */
क्रमागत sock_shutकरोwn_cmd अणु
	SHUT_RD,
	SHUT_WR,
	SHUT_RDWR,
पूर्ण;

काष्ठा socket_wq अणु
	/* Note: रुको MUST be first field of socket_wq */
	रुको_queue_head_t	रुको;
	काष्ठा fasync_काष्ठा	*fasync_list;
	अचिन्हित दीर्घ		flags; /* %SOCKWQ_ASYNC_NOSPACE, etc */
	काष्ठा rcu_head		rcu;
पूर्ण ____cacheline_aligned_in_smp;

/**
 *  काष्ठा socket - general BSD socket
 *  @state: socket state (%SS_CONNECTED, etc)
 *  @type: socket type (%SOCK_STREAM, etc)
 *  @flags: socket flags (%SOCK_NOSPACE, etc)
 *  @ops: protocol specअगरic socket operations
 *  @file: File back poपूर्णांकer क्रम gc
 *  @sk: पूर्णांकernal networking protocol agnostic socket representation
 *  @wq: रुको queue क्रम several uses
 */
काष्ठा socket अणु
	socket_state		state;

	लघु			type;

	अचिन्हित दीर्घ		flags;

	काष्ठा file		*file;
	काष्ठा sock		*sk;
	स्थिर काष्ठा proto_ops	*ops;

	काष्ठा socket_wq	wq;
पूर्ण;

काष्ठा vm_area_काष्ठा;
काष्ठा page;
काष्ठा sockaddr;
काष्ठा msghdr;
काष्ठा module;
काष्ठा sk_buff;
प्रकार पूर्णांक (*sk_पढ़ो_actor_t)(पढ़ो_descriptor_t *, काष्ठा sk_buff *,
			       अचिन्हित पूर्णांक, माप_प्रकार);

काष्ठा proto_ops अणु
	पूर्णांक		family;
	काष्ठा module	*owner;
	पूर्णांक		(*release)   (काष्ठा socket *sock);
	पूर्णांक		(*bind)	     (काष्ठा socket *sock,
				      काष्ठा sockaddr *myaddr,
				      पूर्णांक sockaddr_len);
	पूर्णांक		(*connect)   (काष्ठा socket *sock,
				      काष्ठा sockaddr *vaddr,
				      पूर्णांक sockaddr_len, पूर्णांक flags);
	पूर्णांक		(*socketpair)(काष्ठा socket *sock1,
				      काष्ठा socket *sock2);
	पूर्णांक		(*accept)    (काष्ठा socket *sock,
				      काष्ठा socket *newsock, पूर्णांक flags, bool kern);
	पूर्णांक		(*getname)   (काष्ठा socket *sock,
				      काष्ठा sockaddr *addr,
				      पूर्णांक peer);
	__poll_t	(*poll)	     (काष्ठा file *file, काष्ठा socket *sock,
				      काष्ठा poll_table_काष्ठा *रुको);
	पूर्णांक		(*ioctl)     (काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg);
#अगर_घोषित CONFIG_COMPAT
	पूर्णांक	 	(*compat_ioctl) (काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg);
#पूर्ण_अगर
	पूर्णांक		(*gettstamp) (काष्ठा socket *sock, व्योम __user *userstamp,
				      bool समयval, bool समय32);
	पूर्णांक		(*listen)    (काष्ठा socket *sock, पूर्णांक len);
	पूर्णांक		(*shutकरोwn)  (काष्ठा socket *sock, पूर्णांक flags);
	पूर्णांक		(*setsockopt)(काष्ठा socket *sock, पूर्णांक level,
				      पूर्णांक optname, sockptr_t optval,
				      अचिन्हित पूर्णांक optlen);
	पूर्णांक		(*माला_लोockopt)(काष्ठा socket *sock, पूर्णांक level,
				      पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen);
	व्योम		(*show_fdinfo)(काष्ठा seq_file *m, काष्ठा socket *sock);
	पूर्णांक		(*sendmsg)   (काष्ठा socket *sock, काष्ठा msghdr *m,
				      माप_प्रकार total_len);
	/* Notes क्रम implementing recvmsg:
	 * ===============================
	 * msg->msg_namelen should get updated by the recvmsg handlers
	 * अगरf msg_name != शून्य. It is by शेष 0 to prevent
	 * वापसing uninitialized memory to user space.  The recvfrom
	 * handlers can assume that msg.msg_name is either शून्य or has
	 * a minimum size of माप(काष्ठा sockaddr_storage).
	 */
	पूर्णांक		(*recvmsg)   (काष्ठा socket *sock, काष्ठा msghdr *m,
				      माप_प्रकार total_len, पूर्णांक flags);
	पूर्णांक		(*mmap)	     (काष्ठा file *file, काष्ठा socket *sock,
				      काष्ठा vm_area_काष्ठा * vma);
	sमाप_प्रकार		(*sendpage)  (काष्ठा socket *sock, काष्ठा page *page,
				      पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
	sमाप_प्रकार 	(*splice_पढ़ो)(काष्ठा socket *sock,  loff_t *ppos,
				       काष्ठा pipe_inode_info *pipe, माप_प्रकार len, अचिन्हित पूर्णांक flags);
	पूर्णांक		(*set_peek_off)(काष्ठा sock *sk, पूर्णांक val);
	पूर्णांक		(*peek_len)(काष्ठा socket *sock);

	/* The following functions are called पूर्णांकernally by kernel with
	 * sock lock alपढ़ोy held.
	 */
	पूर्णांक		(*पढ़ो_sock)(काष्ठा sock *sk, पढ़ो_descriptor_t *desc,
				     sk_पढ़ो_actor_t recv_actor);
	पूर्णांक		(*sendpage_locked)(काष्ठा sock *sk, काष्ठा page *page,
					   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
	पूर्णांक		(*sendmsg_locked)(काष्ठा sock *sk, काष्ठा msghdr *msg,
					  माप_प्रकार size);
	पूर्णांक		(*set_rcvlowat)(काष्ठा sock *sk, पूर्णांक val);
पूर्ण;

#घोषणा DECLARE_SOCKADDR(type, dst, src)	\
	type dst = (अणु __sockaddr_check_size(माप(*dst)); (type) src; पूर्ण)

काष्ठा net_proto_family अणु
	पूर्णांक		family;
	पूर्णांक		(*create)(काष्ठा net *net, काष्ठा socket *sock,
				  पूर्णांक protocol, पूर्णांक kern);
	काष्ठा module	*owner;
पूर्ण;

काष्ठा iovec;
काष्ठा kvec;

क्रमागत अणु
	SOCK_WAKE_IO,
	SOCK_WAKE_WAITD,
	SOCK_WAKE_SPACE,
	SOCK_WAKE_URG,
पूर्ण;

पूर्णांक sock_wake_async(काष्ठा socket_wq *sk_wq, पूर्णांक how, पूर्णांक band);
पूर्णांक sock_रेजिस्टर(स्थिर काष्ठा net_proto_family *fam);
व्योम sock_unरेजिस्टर(पूर्णांक family);
bool sock_is_रेजिस्टरed(पूर्णांक family);
पूर्णांक __sock_create(काष्ठा net *net, पूर्णांक family, पूर्णांक type, पूर्णांक proto,
		  काष्ठा socket **res, पूर्णांक kern);
पूर्णांक sock_create(पूर्णांक family, पूर्णांक type, पूर्णांक proto, काष्ठा socket **res);
पूर्णांक sock_create_kern(काष्ठा net *net, पूर्णांक family, पूर्णांक type, पूर्णांक proto, काष्ठा socket **res);
पूर्णांक sock_create_lite(पूर्णांक family, पूर्णांक type, पूर्णांक proto, काष्ठा socket **res);
काष्ठा socket *sock_alloc(व्योम);
व्योम sock_release(काष्ठा socket *sock);
पूर्णांक sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg);
पूर्णांक sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags);
काष्ठा file *sock_alloc_file(काष्ठा socket *sock, पूर्णांक flags, स्थिर अक्षर *dname);
काष्ठा socket *sockfd_lookup(पूर्णांक fd, पूर्णांक *err);
काष्ठा socket *sock_from_file(काष्ठा file *file);
#घोषणा		     sockfd_put(sock) fput(sock->file)
पूर्णांक net_ratelimit(व्योम);

#घोषणा net_ratelimited_function(function, ...)			\
करो अणु								\
	अगर (net_ratelimit())					\
		function(__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा net_emerg_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_emerg, fmt, ##__VA_ARGS__)
#घोषणा net_alert_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_alert, fmt, ##__VA_ARGS__)
#घोषणा net_crit_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_crit, fmt, ##__VA_ARGS__)
#घोषणा net_err_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_err, fmt, ##__VA_ARGS__)
#घोषणा net_notice_ratelimited(fmt, ...)			\
	net_ratelimited_function(pr_notice, fmt, ##__VA_ARGS__)
#घोषणा net_warn_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_warn, fmt, ##__VA_ARGS__)
#घोषणा net_info_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_info, fmt, ##__VA_ARGS__)
#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा net_dbg_ratelimited(fmt, ...)					\
करो अणु									\
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, fmt);			\
	अगर (DYNAMIC_DEBUG_BRANCH(descriptor) &&				\
	    net_ratelimit())						\
		__dynamic_pr_debug(&descriptor, pr_fmt(fmt),		\
		                   ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा net_dbg_ratelimited(fmt, ...)				\
	net_ratelimited_function(pr_debug, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा net_dbg_ratelimited(fmt, ...)				\
	करो अणु							\
		अगर (0)						\
			no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__); \
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा net_get_अक्रमom_once(buf, nbytes)			\
	get_अक्रमom_once((buf), (nbytes))
#घोषणा net_get_अक्रमom_once_रुको(buf, nbytes)			\
	get_अक्रमom_once_रुको((buf), (nbytes))

/*
 * E.g. XFS meta- & log-data is in slab pages, or bcache meta
 * data pages, or other high order pages allocated by
 * __get_मुक्त_pages() without __GFP_COMP, which have a page_count
 * of 0 and/or have PageSlab() set. We cannot use send_page क्रम
 * those, as that करोes get_page(); put_page(); and would cause
 * either a VM_BUG directly, or __page_cache_release a page that
 * would actually still be referenced by someone, leading to some
 * obscure delayed Oops somewhere अन्यथा.
 */
अटल अंतरभूत bool sendpage_ok(काष्ठा page *page)
अणु
	वापस !PageSlab(page) && page_count(page) >= 1;
पूर्ण

पूर्णांक kernel_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा kvec *vec,
		   माप_प्रकार num, माप_प्रकार len);
पूर्णांक kernel_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg,
			  काष्ठा kvec *vec, माप_प्रकार num, माप_प्रकार len);
पूर्णांक kernel_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, काष्ठा kvec *vec,
		   माप_प्रकार num, माप_प्रकार len, पूर्णांक flags);

पूर्णांक kernel_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addrlen);
पूर्णांक kernel_listen(काष्ठा socket *sock, पूर्णांक backlog);
पूर्णांक kernel_accept(काष्ठा socket *sock, काष्ठा socket **newsock, पूर्णांक flags);
पूर्णांक kernel_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addrlen,
		   पूर्णांक flags);
पूर्णांक kernel_माला_लोockname(काष्ठा socket *sock, काष्ठा sockaddr *addr);
पूर्णांक kernel_getpeername(काष्ठा socket *sock, काष्ठा sockaddr *addr);
पूर्णांक kernel_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset,
		    माप_प्रकार size, पूर्णांक flags);
पूर्णांक kernel_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			   माप_प्रकार size, पूर्णांक flags);
पूर्णांक kernel_sock_shutकरोwn(काष्ठा socket *sock, क्रमागत sock_shutकरोwn_cmd how);

/* Routine वापसs the IP overhead imposed by a (caller-रक्षित) socket. */
u32 kernel_sock_ip_overhead(काष्ठा sock *sk);

#घोषणा MODULE_ALIAS_NETPROTO(proto) \
	MODULE_ALIAS("net-pf-" __stringअगरy(proto))

#घोषणा MODULE_ALIAS_NET_PF_PROTO(pf, proto) \
	MODULE_ALIAS("net-pf-" __stringअगरy(pf) "-proto-" __stringअगरy(proto))

#घोषणा MODULE_ALIAS_NET_PF_PROTO_TYPE(pf, proto, type) \
	MODULE_ALIAS("net-pf-" __stringअगरy(pf) "-proto-" __stringअगरy(proto) \
		     "-type-" __stringअगरy(type))

#घोषणा MODULE_ALIAS_NET_PF_PROTO_NAME(pf, proto, name) \
	MODULE_ALIAS("net-pf-" __stringअगरy(pf) "-proto-" __stringअगरy(proto) \
		     name)
#पूर्ण_अगर	/* _LINUX_NET_H */
