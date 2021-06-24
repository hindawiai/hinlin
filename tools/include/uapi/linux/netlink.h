<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_NETLINK_H
#घोषणा _UAPI__LINUX_NETLINK_H

#समावेश <linux/kernel.h>
#समावेश <linux/socket.h> /* क्रम __kernel_sa_family_t */
#समावेश <linux/types.h>

#घोषणा NETLINK_ROUTE		0	/* Routing/device hook				*/
#घोषणा NETLINK_UNUSED		1	/* Unused number				*/
#घोषणा NETLINK_USERSOCK	2	/* Reserved क्रम user mode socket protocols 	*/
#घोषणा NETLINK_FIREWALL	3	/* Unused number, क्रमmerly ip_queue		*/
#घोषणा NETLINK_SOCK_DIAG	4	/* socket monitoring				*/
#घोषणा NETLINK_NFLOG		5	/* netfilter/iptables ULOG */
#घोषणा NETLINK_XFRM		6	/* ipsec */
#घोषणा NETLINK_SELINUX		7	/* SELinux event notअगरications */
#घोषणा NETLINK_ISCSI		8	/* Open-iSCSI */
#घोषणा NETLINK_AUDIT		9	/* auditing */
#घोषणा NETLINK_FIB_LOOKUP	10	
#घोषणा NETLINK_CONNECTOR	11
#घोषणा NETLINK_NETFILTER	12	/* netfilter subप्रणाली */
#घोषणा NETLINK_IP6_FW		13
#घोषणा NETLINK_DNRTMSG		14	/* DECnet routing messages */
#घोषणा NETLINK_KOBJECT_UEVENT	15	/* Kernel messages to userspace */
#घोषणा NETLINK_GENERIC		16
/* leave room क्रम NETLINK_DM (DM Events) */
#घोषणा NETLINK_SCSITRANSPORT	18	/* SCSI Transports */
#घोषणा NETLINK_ECRYPTFS	19
#घोषणा NETLINK_RDMA		20
#घोषणा NETLINK_CRYPTO		21	/* Crypto layer */
#घोषणा NETLINK_SMC		22	/* SMC monitoring */

#घोषणा NETLINK_INET_DIAG	NETLINK_SOCK_DIAG

#घोषणा MAX_LINKS 32		

काष्ठा sockaddr_nl अणु
	__kernel_sa_family_t	nl_family;	/* AF_NETLINK	*/
	अचिन्हित लघु	nl_pad;		/* zero		*/
	__u32		nl_pid;		/* port ID	*/
       	__u32		nl_groups;	/* multicast groups mask */
पूर्ण;

काष्ठा nlmsghdr अणु
	__u32		nlmsg_len;	/* Length of message including header */
	__u16		nlmsg_type;	/* Message content */
	__u16		nlmsg_flags;	/* Additional flags */
	__u32		nlmsg_seq;	/* Sequence number */
	__u32		nlmsg_pid;	/* Sending process port ID */
पूर्ण;

/* Flags values */

#घोषणा NLM_F_REQUEST		0x01	/* It is request message. 	*/
#घोषणा NLM_F_MULTI		0x02	/* Multipart message, terminated by NLMSG_DONE */
#घोषणा NLM_F_ACK		0x04	/* Reply with ack, with zero or error code */
#घोषणा NLM_F_ECHO		0x08	/* Echo this request 		*/
#घोषणा NLM_F_DUMP_INTR		0x10	/* Dump was inconsistent due to sequence change */
#घोषणा NLM_F_DUMP_FILTERED	0x20	/* Dump was filtered as requested */

/* Modअगरiers to GET request */
#घोषणा NLM_F_ROOT	0x100	/* specअगरy tree	root	*/
#घोषणा NLM_F_MATCH	0x200	/* वापस all matching	*/
#घोषणा NLM_F_ATOMIC	0x400	/* atomic GET		*/
#घोषणा NLM_F_DUMP	(NLM_F_ROOT|NLM_F_MATCH)

/* Modअगरiers to NEW request */
#घोषणा NLM_F_REPLACE	0x100	/* Override existing		*/
#घोषणा NLM_F_EXCL	0x200	/* Do not touch, अगर it exists	*/
#घोषणा NLM_F_CREATE	0x400	/* Create, अगर it करोes not exist	*/
#घोषणा NLM_F_APPEND	0x800	/* Add to end of list		*/

/* Modअगरiers to DELETE request */
#घोषणा NLM_F_NONREC	0x100	/* Do not delete recursively	*/

/* Flags क्रम ACK message */
#घोषणा NLM_F_CAPPED	0x100	/* request was capped */
#घोषणा NLM_F_ACK_TLVS	0x200	/* extended ACK TVLs were included */

/*
   4.4BSD ADD		NLM_F_CREATE|NLM_F_EXCL
   4.4BSD CHANGE	NLM_F_REPLACE

   True CHANGE		NLM_F_CREATE|NLM_F_REPLACE
   Append		NLM_F_CREATE
   Check		NLM_F_EXCL
 */

#घोषणा NLMSG_ALIGNTO	4U
#घोषणा NLMSG_ALIGN(len) ( ((len)+NLMSG_ALIGNTO-1) & ~(NLMSG_ALIGNTO-1) )
#घोषणा NLMSG_HDRLEN	 ((पूर्णांक) NLMSG_ALIGN(माप(काष्ठा nlmsghdr)))
#घोषणा NLMSG_LENGTH(len) ((len) + NLMSG_HDRLEN)
#घोषणा NLMSG_SPACE(len) NLMSG_ALIGN(NLMSG_LENGTH(len))
#घोषणा NLMSG_DATA(nlh)  ((व्योम*)(((अक्षर*)nlh) + NLMSG_LENGTH(0)))
#घोषणा NLMSG_NEXT(nlh,len)	 ((len) -= NLMSG_ALIGN((nlh)->nlmsg_len), \
				  (काष्ठा nlmsghdr*)(((अक्षर*)(nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len)))
#घोषणा NLMSG_OK(nlh,len) ((len) >= (पूर्णांक)माप(काष्ठा nlmsghdr) && \
			   (nlh)->nlmsg_len >= माप(काष्ठा nlmsghdr) && \
			   (nlh)->nlmsg_len <= (len))
#घोषणा NLMSG_PAYLOAD(nlh,len) ((nlh)->nlmsg_len - NLMSG_SPACE((len)))

#घोषणा NLMSG_NOOP		0x1	/* Nothing.		*/
#घोषणा NLMSG_ERROR		0x2	/* Error		*/
#घोषणा NLMSG_DONE		0x3	/* End of a dump	*/
#घोषणा NLMSG_OVERRUN		0x4	/* Data lost		*/

#घोषणा NLMSG_MIN_TYPE		0x10	/* < 0x10: reserved control messages */

काष्ठा nlmsgerr अणु
	पूर्णांक		error;
	काष्ठा nlmsghdr msg;
	/*
	 * followed by the message contents unless NETLINK_CAP_ACK was set
	 * or the ACK indicates success (error == 0)
	 * message length is aligned with NLMSG_ALIGN()
	 */
	/*
	 * followed by TLVs defined in क्रमागत nlmsgerr_attrs
	 * अगर NETLINK_EXT_ACK was set
	 */
पूर्ण;

/**
 * क्रमागत nlmsgerr_attrs - nlmsgerr attributes
 * @NLMSGERR_ATTR_UNUSED: unused
 * @NLMSGERR_ATTR_MSG: error message string (string)
 * @NLMSGERR_ATTR_OFFS: offset of the invalid attribute in the original
 *	 message, counting from the beginning of the header (u32)
 * @NLMSGERR_ATTR_COOKIE: arbitrary subप्रणाली specअगरic cookie to
 *	be used - in the success हाल - to identअगरy a created
 *	object or operation or similar (binary)
 * @__NLMSGERR_ATTR_MAX: number of attributes
 * @NLMSGERR_ATTR_MAX: highest attribute number
 */
क्रमागत nlmsgerr_attrs अणु
	NLMSGERR_ATTR_UNUSED,
	NLMSGERR_ATTR_MSG,
	NLMSGERR_ATTR_OFFS,
	NLMSGERR_ATTR_COOKIE,

	__NLMSGERR_ATTR_MAX,
	NLMSGERR_ATTR_MAX = __NLMSGERR_ATTR_MAX - 1
पूर्ण;

#घोषणा NETLINK_ADD_MEMBERSHIP		1
#घोषणा NETLINK_DROP_MEMBERSHIP		2
#घोषणा NETLINK_PKTINFO			3
#घोषणा NETLINK_BROADCAST_ERROR		4
#घोषणा NETLINK_NO_ENOBUFS		5
#अगर_अघोषित __KERNEL__
#घोषणा NETLINK_RX_RING			6
#घोषणा NETLINK_TX_RING			7
#पूर्ण_अगर
#घोषणा NETLINK_LISTEN_ALL_NSID		8
#घोषणा NETLINK_LIST_MEMBERSHIPS	9
#घोषणा NETLINK_CAP_ACK			10
#घोषणा NETLINK_EXT_ACK			11
#घोषणा NETLINK_GET_STRICT_CHK		12

काष्ठा nl_pktinfo अणु
	__u32	group;
पूर्ण;

काष्ठा nl_mmap_req अणु
	अचिन्हित पूर्णांक	nm_block_size;
	अचिन्हित पूर्णांक	nm_block_nr;
	अचिन्हित पूर्णांक	nm_frame_size;
	अचिन्हित पूर्णांक	nm_frame_nr;
पूर्ण;

काष्ठा nl_mmap_hdr अणु
	अचिन्हित पूर्णांक	nm_status;
	अचिन्हित पूर्णांक	nm_len;
	__u32		nm_group;
	/* credentials */
	__u32		nm_pid;
	__u32		nm_uid;
	__u32		nm_gid;
पूर्ण;

#अगर_अघोषित __KERNEL__
क्रमागत nl_mmap_status अणु
	NL_MMAP_STATUS_UNUSED,
	NL_MMAP_STATUS_RESERVED,
	NL_MMAP_STATUS_VALID,
	NL_MMAP_STATUS_COPY,
	NL_MMAP_STATUS_SKIP,
पूर्ण;

#घोषणा NL_MMAP_MSG_ALIGNMENT		NLMSG_ALIGNTO
#घोषणा NL_MMAP_MSG_ALIGN(sz)		__ALIGN_KERNEL(sz, NL_MMAP_MSG_ALIGNMENT)
#घोषणा NL_MMAP_HDRLEN			NL_MMAP_MSG_ALIGN(माप(काष्ठा nl_mmap_hdr))
#पूर्ण_अगर

#घोषणा NET_MAJOR 36		/* Major 36 is reserved क्रम networking 						*/

क्रमागत अणु
	NETLINK_UNCONNECTED = 0,
	NETLINK_CONNECTED,
पूर्ण;

/*
 *  <------- NLA_HDRLEN ------> <-- NLA_ALIGN(payload)-->
 * +---------------------+- - -+- - - - - - - - - -+- - -+
 * |        Header       | Pad |     Payload       | Pad |
 * |   (काष्ठा nlattr)   | ing |                   | ing |
 * +---------------------+- - -+- - - - - - - - - -+- - -+
 *  <-------------- nlattr->nla_len -------------->
 */

काष्ठा nlattr अणु
	__u16           nla_len;
	__u16           nla_type;
पूर्ण;

/*
 * nla_type (16 bits)
 * +---+---+-------------------------------+
 * | N | O | Attribute Type                |
 * +---+---+-------------------------------+
 * N := Carries nested attributes
 * O := Payload stored in network byte order
 *
 * Note: The N and O flag are mutually exclusive.
 */
#घोषणा NLA_F_NESTED		(1 << 15)
#घोषणा NLA_F_NET_BYTEORDER	(1 << 14)
#घोषणा NLA_TYPE_MASK		~(NLA_F_NESTED | NLA_F_NET_BYTEORDER)

#घोषणा NLA_ALIGNTO		4
#घोषणा NLA_ALIGN(len)		(((len) + NLA_ALIGNTO - 1) & ~(NLA_ALIGNTO - 1))
#घोषणा NLA_HDRLEN		((पूर्णांक) NLA_ALIGN(माप(काष्ठा nlattr)))

/* Generic 32 bitflags attribute content sent to the kernel.
 *
 * The value is a biपंचांगap that defines the values being set
 * The selector is a biपंचांगask that defines which value is legit
 *
 * Examples:
 *  value = 0x0, and selector = 0x1
 *  implies we are selecting bit 1 and we want to set its value to 0.
 *
 *  value = 0x2, and selector = 0x2
 *  implies we are selecting bit 2 and we want to set its value to 1.
 *
 */
काष्ठा nla_bitfield32 अणु
	__u32 value;
	__u32 selector;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_NETLINK_H */
