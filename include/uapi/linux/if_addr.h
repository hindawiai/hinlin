<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_IF_ADDR_H
#घोषणा __LINUX_IF_ADDR_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>

काष्ठा अगरaddrmsg अणु
	__u8		अगरa_family;
	__u8		अगरa_prefixlen;	/* The prefix length		*/
	__u8		अगरa_flags;	/* Flags			*/
	__u8		अगरa_scope;	/* Address scope		*/
	__u32		अगरa_index;	/* Link index			*/
पूर्ण;

/*
 * Important comment:
 * IFA_ADDRESS is prefix address, rather than local पूर्णांकerface address.
 * It makes no dअगरference क्रम normally configured broadcast पूर्णांकerfaces,
 * but क्रम poपूर्णांक-to-poपूर्णांक IFA_ADDRESS is DESTINATION address,
 * local address is supplied in IFA_LOCAL attribute.
 *
 * IFA_FLAGS is a u32 attribute that extends the u8 field अगरa_flags.
 * If present, the value from काष्ठा अगरaddrmsg will be ignored.
 */
क्रमागत अणु
	IFA_UNSPEC,
	IFA_ADDRESS,
	IFA_LOCAL,
	IFA_LABEL,
	IFA_BROADCAST,
	IFA_ANYCAST,
	IFA_CACHEINFO,
	IFA_MULTICAST,
	IFA_FLAGS,
	IFA_RT_PRIORITY,  /* u32, priority/metric क्रम prefix route */
	IFA_TARGET_NETNSID,
	__IFA_MAX,
पूर्ण;

#घोषणा IFA_MAX (__IFA_MAX - 1)

/* अगरa_flags */
#घोषणा IFA_F_SECONDARY		0x01
#घोषणा IFA_F_TEMPORARY		IFA_F_SECONDARY

#घोषणा	IFA_F_NODAD		0x02
#घोषणा IFA_F_OPTIMISTIC	0x04
#घोषणा IFA_F_DADFAILED		0x08
#घोषणा	IFA_F_HOMEADDRESS	0x10
#घोषणा IFA_F_DEPRECATED	0x20
#घोषणा IFA_F_TENTATIVE		0x40
#घोषणा IFA_F_PERMANENT		0x80
#घोषणा IFA_F_MANAGETEMPADDR	0x100
#घोषणा IFA_F_NOPREFIXROUTE	0x200
#घोषणा IFA_F_MCAUTOJOIN	0x400
#घोषणा IFA_F_STABLE_PRIVACY	0x800

काष्ठा अगरa_cacheinfo अणु
	__u32	अगरa_prefered;
	__u32	अगरa_valid;
	__u32	cstamp; /* created बारtamp, hundredths of seconds */
	__u32	tstamp; /* updated बारtamp, hundredths of seconds */
पूर्ण;

/* backwards compatibility क्रम userspace */
#अगर_अघोषित __KERNEL__
#घोषणा IFA_RTA(r)  ((काष्ठा rtattr*)(((अक्षर*)(r)) + NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg))))
#घोषणा IFA_PAYLOAD(n) NLMSG_PAYLOAD(n,माप(काष्ठा अगरaddrmsg))
#पूर्ण_अगर

#पूर्ण_अगर
