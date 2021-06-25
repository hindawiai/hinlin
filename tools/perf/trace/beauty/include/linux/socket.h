<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SOCKET_H
#घोषणा _LINUX_SOCKET_H


#समावेश <यंत्र/socket.h>			/* arch-dependent defines	*/
#समावेश <linux/sockios.h>		/* the SIOCxxx I/O controls	*/
#समावेश <linux/uपन.स>			/* iovec support		*/
#समावेश <linux/types.h>		/* pid_t			*/
#समावेश <linux/compiler.h>		/* __user			*/
#समावेश <uapi/linux/socket.h>

काष्ठा file;
काष्ठा pid;
काष्ठा cred;
काष्ठा socket;

#घोषणा __sockaddr_check_size(size)	\
	BUILD_BUG_ON(((size) > माप(काष्ठा __kernel_sockaddr_storage)))

#अगर_घोषित CONFIG_PROC_FS
काष्ठा seq_file;
बाह्य व्योम socket_seq_show(काष्ठा seq_file *seq);
#पूर्ण_अगर

प्रकार __kernel_sa_family_t	sa_family_t;

/*
 *	1003.1g requires sa_family_t and that sa_data is अक्षर.
 */

काष्ठा sockaddr अणु
	sa_family_t	sa_family;	/* address family, AF_xxx	*/
	अक्षर		sa_data[14];	/* 14 bytes of protocol address	*/
पूर्ण;

काष्ठा linger अणु
	पूर्णांक		l_onoff;	/* Linger active		*/
	पूर्णांक		l_linger;	/* How दीर्घ to linger क्रम	*/
पूर्ण;

#घोषणा sockaddr_storage __kernel_sockaddr_storage

/*
 *	As we करो 4.4BSD message passing we use a 4.4BSD message passing
 *	प्रणाली, not 4.3. Thus msg_accrights(len) are now missing. They
 *	beदीर्घ in an obscure libc emulation or the bin.
 */

काष्ठा msghdr अणु
	व्योम		*msg_name;	/* ptr to socket address काष्ठाure */
	पूर्णांक		msg_namelen;	/* size of socket address काष्ठाure */
	काष्ठा iov_iter	msg_iter;	/* data */

	/*
	 * Ancillary data. msg_control_user is the user buffer used क्रम the
	 * recv* side when msg_control_is_user is set, msg_control is the kernel
	 * buffer used क्रम all other हालs.
	 */
	जोड़ अणु
		व्योम		*msg_control;
		व्योम __user	*msg_control_user;
	पूर्ण;
	bool		msg_control_is_user : 1;
	__kernel_माप_प्रकार	msg_controllen;	/* ancillary data buffer length */
	अचिन्हित पूर्णांक	msg_flags;	/* flags on received message */
	काष्ठा kiocb	*msg_iocb;	/* ptr to iocb क्रम async requests */
पूर्ण;

काष्ठा user_msghdr अणु
	व्योम		__user *msg_name;	/* ptr to socket address काष्ठाure */
	पूर्णांक		msg_namelen;		/* size of socket address काष्ठाure */
	काष्ठा iovec	__user *msg_iov;	/* scatter/gather array */
	__kernel_माप_प्रकार	msg_iovlen;		/* # elements in msg_iov */
	व्योम		__user *msg_control;	/* ancillary data */
	__kernel_माप_प्रकार	msg_controllen;		/* ancillary data buffer length */
	अचिन्हित पूर्णांक	msg_flags;		/* flags on received message */
पूर्ण;

/* For recvmmsg/sendmmsg */
काष्ठा mmsghdr अणु
	काष्ठा user_msghdr  msg_hdr;
	अचिन्हित पूर्णांक        msg_len;
पूर्ण;

/*
 *	POSIX 1003.1g - ancillary data object inक्रमmation
 *	Ancillary data consists of a sequence of pairs of
 *	(cmsghdr, cmsg_data[])
 */

काष्ठा cmsghdr अणु
	__kernel_माप_प्रकार	cmsg_len;	/* data byte count, including hdr */
        पूर्णांक		cmsg_level;	/* originating protocol */
        पूर्णांक		cmsg_type;	/* protocol-specअगरic type */
पूर्ण;

/*
 *	Ancillary data object inक्रमmation MACROS
 *	Table 5-14 of POSIX 1003.1g
 */

#घोषणा __CMSG_NXTHDR(ctl, len, cmsg) __cmsg_nxthdr((ctl),(len),(cmsg))
#घोषणा CMSG_NXTHDR(mhdr, cmsg) cmsg_nxthdr((mhdr), (cmsg))

#घोषणा CMSG_ALIGN(len) ( ((len)+माप(दीर्घ)-1) & ~(माप(दीर्घ)-1) )

#घोषणा CMSG_DATA(cmsg) \
	((व्योम *)(cmsg) + माप(काष्ठा cmsghdr))
#घोषणा CMSG_USER_DATA(cmsg) \
	((व्योम __user *)(cmsg) + माप(काष्ठा cmsghdr))
#घोषणा CMSG_SPACE(len) (माप(काष्ठा cmsghdr) + CMSG_ALIGN(len))
#घोषणा CMSG_LEN(len) (माप(काष्ठा cmsghdr) + (len))

#घोषणा __CMSG_FIRSTHDR(ctl,len) ((len) >= माप(काष्ठा cmsghdr) ? \
				  (काष्ठा cmsghdr *)(ctl) : \
				  (काष्ठा cmsghdr *)शून्य)
#घोषणा CMSG_FIRSTHDR(msg)	__CMSG_FIRSTHDR((msg)->msg_control, (msg)->msg_controllen)
#घोषणा CMSG_OK(mhdr, cmsg) ((cmsg)->cmsg_len >= माप(काष्ठा cmsghdr) && \
			     (cmsg)->cmsg_len <= (अचिन्हित दीर्घ) \
			     ((mhdr)->msg_controllen - \
			      ((अक्षर *)(cmsg) - (अक्षर *)(mhdr)->msg_control)))
#घोषणा क्रम_each_cmsghdr(cmsg, msg) \
	क्रम (cmsg = CMSG_FIRSTHDR(msg); \
	     cmsg; \
	     cmsg = CMSG_NXTHDR(msg, cmsg))

/*
 *	Get the next cmsg header
 *
 *	PLEASE, करो not touch this function. If you think, that it is
 *	incorrect, grep kernel sources and think about consequences
 *	beक्रमe trying to improve it.
 *
 *	Now it always वापसs valid, not truncated ancillary object
 *	HEADER. But caller still MUST check, that cmsg->cmsg_len is
 *	inside range, given by msg->msg_controllen beक्रमe using
 *	ancillary object DATA.				--ANK (980731)
 */

अटल अंतरभूत काष्ठा cmsghdr * __cmsg_nxthdr(व्योम *__ctl, __kernel_माप_प्रकार __size,
					       काष्ठा cmsghdr *__cmsg)
अणु
	काष्ठा cmsghdr * __ptr;

	__ptr = (काष्ठा cmsghdr*)(((अचिन्हित अक्षर *) __cmsg) +  CMSG_ALIGN(__cmsg->cmsg_len));
	अगर ((अचिन्हित दीर्घ)((अक्षर*)(__ptr+1) - (अक्षर *) __ctl) > __size)
		वापस (काष्ठा cmsghdr *)0;

	वापस __ptr;
पूर्ण

अटल अंतरभूत काष्ठा cmsghdr * cmsg_nxthdr (काष्ठा msghdr *__msg, काष्ठा cmsghdr *__cmsg)
अणु
	वापस __cmsg_nxthdr(__msg->msg_control, __msg->msg_controllen, __cmsg);
पूर्ण

अटल अंतरभूत माप_प्रकार msg_data_left(काष्ठा msghdr *msg)
अणु
	वापस iov_iter_count(&msg->msg_iter);
पूर्ण

/* "Socket"-level control message types: */

#घोषणा	SCM_RIGHTS	0x01		/* rw: access rights (array of पूर्णांक) */
#घोषणा SCM_CREDENTIALS 0x02		/* rw: काष्ठा ucred		*/
#घोषणा SCM_SECURITY	0x03		/* rw: security label		*/

काष्ठा ucred अणु
	__u32	pid;
	__u32	uid;
	__u32	gid;
पूर्ण;

/* Supported address families. */
#घोषणा AF_UNSPEC	0
#घोषणा AF_UNIX		1	/* Unix करोमुख्य sockets 		*/
#घोषणा AF_LOCAL	1	/* POSIX name क्रम AF_UNIX	*/
#घोषणा AF_INET		2	/* Internet IP Protocol 	*/
#घोषणा AF_AX25		3	/* Amateur Radio AX.25 		*/
#घोषणा AF_IPX		4	/* Novell IPX 			*/
#घोषणा AF_APPLETALK	5	/* AppleTalk DDP 		*/
#घोषणा AF_NETROM	6	/* Amateur Radio NET/ROM 	*/
#घोषणा AF_BRIDGE	7	/* Multiprotocol bridge 	*/
#घोषणा AF_ATMPVC	8	/* ATM PVCs			*/
#घोषणा AF_X25		9	/* Reserved क्रम X.25 project 	*/
#घोषणा AF_INET6	10	/* IP version 6			*/
#घोषणा AF_ROSE		11	/* Amateur Radio X.25 PLP	*/
#घोषणा AF_DECnet	12	/* Reserved क्रम DECnet project	*/
#घोषणा AF_NETBEUI	13	/* Reserved क्रम 802.2LLC project*/
#घोषणा AF_SECURITY	14	/* Security callback pseuकरो AF */
#घोषणा AF_KEY		15      /* PF_KEY key management API */
#घोषणा AF_NETLINK	16
#घोषणा AF_ROUTE	AF_NETLINK /* Alias to emulate 4.4BSD */
#घोषणा AF_PACKET	17	/* Packet family		*/
#घोषणा AF_ASH		18	/* Ash				*/
#घोषणा AF_ECONET	19	/* Acorn Econet			*/
#घोषणा AF_ATMSVC	20	/* ATM SVCs			*/
#घोषणा AF_RDS		21	/* RDS sockets 			*/
#घोषणा AF_SNA		22	/* Linux SNA Project (nutters!) */
#घोषणा AF_IRDA		23	/* IRDA sockets			*/
#घोषणा AF_PPPOX	24	/* PPPoX sockets		*/
#घोषणा AF_WANPIPE	25	/* Wanpipe API Sockets */
#घोषणा AF_LLC		26	/* Linux LLC			*/
#घोषणा AF_IB		27	/* Native InfiniBand address	*/
#घोषणा AF_MPLS		28	/* MPLS */
#घोषणा AF_CAN		29	/* Controller Area Network      */
#घोषणा AF_TIPC		30	/* TIPC sockets			*/
#घोषणा AF_BLUETOOTH	31	/* Bluetooth sockets 		*/
#घोषणा AF_IUCV		32	/* IUCV sockets			*/
#घोषणा AF_RXRPC	33	/* RxRPC sockets 		*/
#घोषणा AF_ISDN		34	/* mISDN sockets 		*/
#घोषणा AF_PHONET	35	/* Phonet sockets		*/
#घोषणा AF_IEEE802154	36	/* IEEE802154 sockets		*/
#घोषणा AF_CAIF		37	/* CAIF sockets			*/
#घोषणा AF_ALG		38	/* Algorithm sockets		*/
#घोषणा AF_NFC		39	/* NFC sockets			*/
#घोषणा AF_VSOCK	40	/* vSockets			*/
#घोषणा AF_KCM		41	/* Kernel Connection Multiplexor*/
#घोषणा AF_QIPCRTR	42	/* Qualcomm IPC Router          */
#घोषणा AF_SMC		43	/* smc sockets: reserve number क्रम
				 * PF_SMC protocol family that
				 * reuses AF_INET address family
				 */
#घोषणा AF_XDP		44	/* XDP sockets			*/

#घोषणा AF_MAX		45	/* For now.. */

/* Protocol families, same as address families. */
#घोषणा PF_UNSPEC	AF_UNSPEC
#घोषणा PF_UNIX		AF_UNIX
#घोषणा PF_LOCAL	AF_LOCAL
#घोषणा PF_INET		AF_INET
#घोषणा PF_AX25		AF_AX25
#घोषणा PF_IPX		AF_IPX
#घोषणा PF_APPLETALK	AF_APPLETALK
#घोषणा	PF_NETROM	AF_NETROM
#घोषणा PF_BRIDGE	AF_BRIDGE
#घोषणा PF_ATMPVC	AF_ATMPVC
#घोषणा PF_X25		AF_X25
#घोषणा PF_INET6	AF_INET6
#घोषणा PF_ROSE		AF_ROSE
#घोषणा PF_DECnet	AF_DECnet
#घोषणा PF_NETBEUI	AF_NETBEUI
#घोषणा PF_SECURITY	AF_SECURITY
#घोषणा PF_KEY		AF_KEY
#घोषणा PF_NETLINK	AF_NETLINK
#घोषणा PF_ROUTE	AF_ROUTE
#घोषणा PF_PACKET	AF_PACKET
#घोषणा PF_ASH		AF_ASH
#घोषणा PF_ECONET	AF_ECONET
#घोषणा PF_ATMSVC	AF_ATMSVC
#घोषणा PF_RDS		AF_RDS
#घोषणा PF_SNA		AF_SNA
#घोषणा PF_IRDA		AF_IRDA
#घोषणा PF_PPPOX	AF_PPPOX
#घोषणा PF_WANPIPE	AF_WANPIPE
#घोषणा PF_LLC		AF_LLC
#घोषणा PF_IB		AF_IB
#घोषणा PF_MPLS		AF_MPLS
#घोषणा PF_CAN		AF_CAN
#घोषणा PF_TIPC		AF_TIPC
#घोषणा PF_BLUETOOTH	AF_BLUETOOTH
#घोषणा PF_IUCV		AF_IUCV
#घोषणा PF_RXRPC	AF_RXRPC
#घोषणा PF_ISDN		AF_ISDN
#घोषणा PF_PHONET	AF_PHONET
#घोषणा PF_IEEE802154	AF_IEEE802154
#घोषणा PF_CAIF		AF_CAIF
#घोषणा PF_ALG		AF_ALG
#घोषणा PF_NFC		AF_NFC
#घोषणा PF_VSOCK	AF_VSOCK
#घोषणा PF_KCM		AF_KCM
#घोषणा PF_QIPCRTR	AF_QIPCRTR
#घोषणा PF_SMC		AF_SMC
#घोषणा PF_XDP		AF_XDP
#घोषणा PF_MAX		AF_MAX

/* Maximum queue length specअगरiable by listen.  */
#घोषणा SOMAXCONN	4096

/* Flags we can use with send/ and recv.
   Added those क्रम 1003.1g not all are supported yet
 */

#घोषणा MSG_OOB		1
#घोषणा MSG_PEEK	2
#घोषणा MSG_DONTROUTE	4
#घोषणा MSG_TRYHARD     4       /* Synonym क्रम MSG_DONTROUTE क्रम DECnet */
#घोषणा MSG_CTRUNC	8
#घोषणा MSG_PROBE	0x10	/* Do not send. Only probe path f.e. क्रम MTU */
#घोषणा MSG_TRUNC	0x20
#घोषणा MSG_DONTWAIT	0x40	/* Nonblocking io		 */
#घोषणा MSG_EOR         0x80	/* End of record */
#घोषणा MSG_WAITALL	0x100	/* Wait क्रम a full request */
#घोषणा MSG_FIN         0x200
#घोषणा MSG_SYN		0x400
#घोषणा MSG_CONFIRM	0x800	/* Confirm path validity */
#घोषणा MSG_RST		0x1000
#घोषणा MSG_ERRQUEUE	0x2000	/* Fetch message from error queue */
#घोषणा MSG_NOSIGNAL	0x4000	/* Do not generate SIGPIPE */
#घोषणा MSG_MORE	0x8000	/* Sender will send more */
#घोषणा MSG_WAITFORONE	0x10000	/* recvmmsg(): block until 1+ packets avail */
#घोषणा MSG_SENDPAGE_NOPOLICY 0x10000 /* sendpage() पूर्णांकernal : करो no apply policy */
#घोषणा MSG_SENDPAGE_NOTLAST 0x20000 /* sendpage() पूर्णांकernal : not the last page */
#घोषणा MSG_BATCH	0x40000 /* sendmmsg(): more messages coming */
#घोषणा MSG_खातापूर्ण         MSG_FIN
#घोषणा MSG_NO_SHARED_FRAGS 0x80000 /* sendpage() पूर्णांकernal : page frags are not shared */
#घोषणा MSG_SENDPAGE_DECRYPTED	0x100000 /* sendpage() पूर्णांकernal : page may carry
					  * plain text and require encryption
					  */

#घोषणा MSG_ZEROCOPY	0x4000000	/* Use user data in kernel path */
#घोषणा MSG_FASTOPEN	0x20000000	/* Send data in TCP SYN */
#घोषणा MSG_CMSG_CLOEXEC 0x40000000	/* Set बंद_on_exec क्रम file
					   descriptor received through
					   SCM_RIGHTS */
#अगर defined(CONFIG_COMPAT)
#घोषणा MSG_CMSG_COMPAT	0x80000000	/* This message needs 32 bit fixups */
#अन्यथा
#घोषणा MSG_CMSG_COMPAT	0		/* We never have 32 bit fixups */
#पूर्ण_अगर


/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
#घोषणा SOL_IP		0
/* #घोषणा SOL_ICMP	1	No-no-no! Due to Linux :-) we cannot use SOL_ICMP=1 */
#घोषणा SOL_TCP		6
#घोषणा SOL_UDP		17
#घोषणा SOL_IPV6	41
#घोषणा SOL_ICMPV6	58
#घोषणा SOL_SCTP	132
#घोषणा SOL_UDPLITE	136     /* UDP-Lite (RFC 3828) */
#घोषणा SOL_RAW		255
#घोषणा SOL_IPX		256
#घोषणा SOL_AX25	257
#घोषणा SOL_ATALK	258
#घोषणा SOL_NETROM	259
#घोषणा SOL_ROSE	260
#घोषणा SOL_DECNET	261
#घोषणा	SOL_X25		262
#घोषणा SOL_PACKET	263
#घोषणा SOL_ATM		264	/* ATM layer (cell level) */
#घोषणा SOL_AAL		265	/* ATM Adaption Layer (packet level) */
#घोषणा SOL_IRDA        266
#घोषणा SOL_NETBEUI	267
#घोषणा SOL_LLC		268
#घोषणा SOL_DCCP	269
#घोषणा SOL_NETLINK	270
#घोषणा SOL_TIPC	271
#घोषणा SOL_RXRPC	272
#घोषणा SOL_PPPOL2TP	273
#घोषणा SOL_BLUETOOTH	274
#घोषणा SOL_PNPIPE	275
#घोषणा SOL_RDS		276
#घोषणा SOL_IUCV	277
#घोषणा SOL_CAIF	278
#घोषणा SOL_ALG		279
#घोषणा SOL_NFC		280
#घोषणा SOL_KCM		281
#घोषणा SOL_TLS		282
#घोषणा SOL_XDP		283

/* IPX options */
#घोषणा IPX_TYPE	1

बाह्य पूर्णांक move_addr_to_kernel(व्योम __user *uaddr, पूर्णांक ulen, काष्ठा sockaddr_storage *kaddr);
बाह्य पूर्णांक put_cmsg(काष्ठा msghdr*, पूर्णांक level, पूर्णांक type, पूर्णांक len, व्योम *data);

काष्ठा बारpec64;
काष्ठा __kernel_बारpec;
काष्ठा old_बारpec32;

काष्ठा scm_बारtamping_पूर्णांकernal अणु
	काष्ठा बारpec64 ts[3];
पूर्ण;

बाह्य व्योम put_cmsg_scm_बारtamping64(काष्ठा msghdr *msg, काष्ठा scm_बारtamping_पूर्णांकernal *tss);
बाह्य व्योम put_cmsg_scm_बारtamping(काष्ठा msghdr *msg, काष्ठा scm_बारtamping_पूर्णांकernal *tss);

/* The __sys_...msg variants allow MSG_CMSG_COMPAT अगरf
 * क्रमbid_cmsg_compat==false
 */
बाह्य दीर्घ __sys_recvmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg,
			  अचिन्हित पूर्णांक flags, bool क्रमbid_cmsg_compat);
बाह्य दीर्घ __sys_sendmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg,
			  अचिन्हित पूर्णांक flags, bool क्रमbid_cmsg_compat);
बाह्य पूर्णांक __sys_recvmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *mmsg,
			  अचिन्हित पूर्णांक vlen, अचिन्हित पूर्णांक flags,
			  काष्ठा __kernel_बारpec __user *समयout,
			  काष्ठा old_बारpec32 __user *समयout32);
बाह्य पूर्णांक __sys_sendmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *mmsg,
			  अचिन्हित पूर्णांक vlen, अचिन्हित पूर्णांक flags,
			  bool क्रमbid_cmsg_compat);
बाह्य दीर्घ __sys_sendmsg_sock(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       अचिन्हित पूर्णांक flags);
बाह्य दीर्घ __sys_recvmsg_sock(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       काष्ठा user_msghdr __user *umsg,
			       काष्ठा sockaddr __user *uaddr,
			       अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक sendmsg_copy_msghdr(काष्ठा msghdr *msg,
			       काष्ठा user_msghdr __user *umsg, अचिन्हित flags,
			       काष्ठा iovec **iov);
बाह्य पूर्णांक recvmsg_copy_msghdr(काष्ठा msghdr *msg,
			       काष्ठा user_msghdr __user *umsg, अचिन्हित flags,
			       काष्ठा sockaddr __user **uaddr,
			       काष्ठा iovec **iov);
बाह्य पूर्णांक __copy_msghdr_from_user(काष्ठा msghdr *kmsg,
				   काष्ठा user_msghdr __user *umsg,
				   काष्ठा sockaddr __user **save_addr,
				   काष्ठा iovec __user **uiov, माप_प्रकार *nsegs);

/* helpers which करो the actual work क्रम syscalls */
बाह्य पूर्णांक __sys_recvfrom(पूर्णांक fd, व्योम __user *ubuf, माप_प्रकार size,
			  अचिन्हित पूर्णांक flags, काष्ठा sockaddr __user *addr,
			  पूर्णांक __user *addr_len);
बाह्य पूर्णांक __sys_sendto(पूर्णांक fd, व्योम __user *buff, माप_प्रकार len,
			अचिन्हित पूर्णांक flags, काष्ठा sockaddr __user *addr,
			पूर्णांक addr_len);
बाह्य पूर्णांक __sys_accept4_file(काष्ठा file *file, अचिन्हित file_flags,
			काष्ठा sockaddr __user *upeer_sockaddr,
			 पूर्णांक __user *upeer_addrlen, पूर्णांक flags,
			 अचिन्हित दीर्घ nofile);
बाह्य पूर्णांक __sys_accept4(पूर्णांक fd, काष्ठा sockaddr __user *upeer_sockaddr,
			 पूर्णांक __user *upeer_addrlen, पूर्णांक flags);
बाह्य पूर्णांक __sys_socket(पूर्णांक family, पूर्णांक type, पूर्णांक protocol);
बाह्य पूर्णांक __sys_bind(पूर्णांक fd, काष्ठा sockaddr __user *umyaddr, पूर्णांक addrlen);
बाह्य पूर्णांक __sys_connect_file(काष्ठा file *file, काष्ठा sockaddr_storage *addr,
			      पूर्णांक addrlen, पूर्णांक file_flags);
बाह्य पूर्णांक __sys_connect(पूर्णांक fd, काष्ठा sockaddr __user *uservaddr,
			 पूर्णांक addrlen);
बाह्य पूर्णांक __sys_listen(पूर्णांक fd, पूर्णांक backlog);
बाह्य पूर्णांक __sys_माला_लोockname(पूर्णांक fd, काष्ठा sockaddr __user *usockaddr,
			     पूर्णांक __user *usockaddr_len);
बाह्य पूर्णांक __sys_getpeername(पूर्णांक fd, काष्ठा sockaddr __user *usockaddr,
			     पूर्णांक __user *usockaddr_len);
बाह्य पूर्णांक __sys_socketpair(पूर्णांक family, पूर्णांक type, पूर्णांक protocol,
			    पूर्णांक __user *usockvec);
बाह्य पूर्णांक __sys_shutकरोwn_sock(काष्ठा socket *sock, पूर्णांक how);
बाह्य पूर्णांक __sys_shutकरोwn(पूर्णांक fd, पूर्णांक how);
#पूर्ण_अगर /* _LINUX_SOCKET_H */
