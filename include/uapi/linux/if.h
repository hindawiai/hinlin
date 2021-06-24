<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the INET पूर्णांकerface module.
 *
 * Version:	@(#)अगर.h	1.0.2	04/18/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1982-1988
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _LINUX_IF_H
#घोषणा _LINUX_IF_H

#समावेश <linux/libc-compat.h>          /* क्रम compatibility with glibc */
#समावेश <linux/types.h>		/* क्रम "__kernel_caddr_t" et al	*/
#समावेश <linux/socket.h>		/* क्रम "struct sockaddr" et al	*/
#समावेश <linux/compiler.h>		/* क्रम "__user" et al           */

#अगर_अघोषित __KERNEL__
#समावेश <sys/socket.h>			/* क्रम काष्ठा sockaddr.		*/
#पूर्ण_अगर

#अगर __UAPI_DEF_IF_IFNAMSIZ
#घोषणा	IFNAMSIZ	16
#पूर्ण_अगर /* __UAPI_DEF_IF_IFNAMSIZ */
#घोषणा	IFALIASZ	256
#घोषणा	ALTIFNAMSIZ	128
#समावेश <linux/hdlc/ioctl.h>

/* For glibc compatibility. An empty क्रमागत करोes not compile. */
#अगर __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO != 0 || \
    __UAPI_DEF_IF_NET_DEVICE_FLAGS != 0
/**
 * क्रमागत net_device_flags - &काष्ठा net_device flags
 *
 * These are the &काष्ठा net_device flags, they can be set by drivers, the
 * kernel and some can be triggered by userspace. Userspace can query and
 * set these flags using userspace utilities but there is also a sysfs
 * entry available क्रम all dev flags which can be queried and set. These flags
 * are shared क्रम all types of net_devices. The sysfs entries are available
 * via /sys/class/net/<dev>/flags. Flags which can be toggled through sysfs
 * are annotated below, note that only a few flags can be toggled and some
 * other flags are always preserved from the original net_device flags
 * even अगर you try to set them via sysfs. Flags which are always preserved
 * are kept under the flag grouping @IFF_VOLATILE. Flags which are अस्थिर
 * are annotated below as such.
 *
 * You should have a pretty good reason to be extending these flags.
 *
 * @IFF_UP: पूर्णांकerface is up. Can be toggled through sysfs.
 * @IFF_BROADCAST: broadcast address valid. Volatile.
 * @IFF_DEBUG: turn on debugging. Can be toggled through sysfs.
 * @IFF_LOOPBACK: is a loopback net. Volatile.
 * @IFF_POINTOPOINT: पूर्णांकerface is has p-p link. Volatile.
 * @IFF_NOTRAILERS: aव्योम use of trailers. Can be toggled through sysfs.
 *	Volatile.
 * @IFF_RUNNING: पूर्णांकerface RFC2863 OPER_UP. Volatile.
 * @IFF_NOARP: no ARP protocol. Can be toggled through sysfs. Volatile.
 * @IFF_PROMISC: receive all packets. Can be toggled through sysfs.
 * @IFF_ALLMULTI: receive all multicast packets. Can be toggled through
 *	sysfs.
 * @IFF_MASTER: master of a load balancer. Volatile.
 * @IFF_SLAVE: slave of a load balancer. Volatile.
 * @IFF_MULTICAST: Supports multicast. Can be toggled through sysfs.
 * @IFF_PORTSEL: can set media type. Can be toggled through sysfs.
 * @IFF_AUTOMEDIA: स्वतः media select active. Can be toggled through sysfs.
 * @IFF_DYNAMIC: dialup device with changing addresses. Can be toggled
 *	through sysfs.
 * @IFF_LOWER_UP: driver संकेतs L1 up. Volatile.
 * @IFF_DORMANT: driver संकेतs करोrmant. Volatile.
 * @IFF_ECHO: echo sent packets. Volatile.
 */
क्रमागत net_device_flags अणु
/* क्रम compatibility with glibc net/अगर.h */
#अगर __UAPI_DEF_IF_NET_DEVICE_FLAGS
	IFF_UP				= 1<<0,  /* sysfs */
	IFF_BROADCAST			= 1<<1,  /* अस्थिर */
	IFF_DEBUG			= 1<<2,  /* sysfs */
	IFF_LOOPBACK			= 1<<3,  /* अस्थिर */
	IFF_POINTOPOINT			= 1<<4,  /* अस्थिर */
	IFF_NOTRAILERS			= 1<<5,  /* sysfs */
	IFF_RUNNING			= 1<<6,  /* अस्थिर */
	IFF_NOARP			= 1<<7,  /* sysfs */
	IFF_PROMISC			= 1<<8,  /* sysfs */
	IFF_ALLMULTI			= 1<<9,  /* sysfs */
	IFF_MASTER			= 1<<10, /* अस्थिर */
	IFF_SLAVE			= 1<<11, /* अस्थिर */
	IFF_MULTICAST			= 1<<12, /* sysfs */
	IFF_PORTSEL			= 1<<13, /* sysfs */
	IFF_AUTOMEDIA			= 1<<14, /* sysfs */
	IFF_DYNAMIC			= 1<<15, /* sysfs */
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS */
#अगर __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
	IFF_LOWER_UP			= 1<<16, /* अस्थिर */
	IFF_DORMANT			= 1<<17, /* अस्थिर */
	IFF_ECHO			= 1<<18, /* अस्थिर */
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO */
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO != 0 || __UAPI_DEF_IF_NET_DEVICE_FLAGS != 0 */

/* क्रम compatibility with glibc net/अगर.h */
#अगर __UAPI_DEF_IF_NET_DEVICE_FLAGS
#घोषणा IFF_UP				IFF_UP
#घोषणा IFF_BROADCAST			IFF_BROADCAST
#घोषणा IFF_DEBUG			IFF_DEBUG
#घोषणा IFF_LOOPBACK			IFF_LOOPBACK
#घोषणा IFF_POINTOPOINT			IFF_POINTOPOINT
#घोषणा IFF_NOTRAILERS			IFF_NOTRAILERS
#घोषणा IFF_RUNNING			IFF_RUNNING
#घोषणा IFF_NOARP			IFF_NOARP
#घोषणा IFF_PROMISC			IFF_PROMISC
#घोषणा IFF_ALLMULTI			IFF_ALLMULTI
#घोषणा IFF_MASTER			IFF_MASTER
#घोषणा IFF_SLAVE			IFF_SLAVE
#घोषणा IFF_MULTICAST			IFF_MULTICAST
#घोषणा IFF_PORTSEL			IFF_PORTSEL
#घोषणा IFF_AUTOMEDIA			IFF_AUTOMEDIA
#घोषणा IFF_DYNAMIC			IFF_DYNAMIC
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS */

#अगर __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
#घोषणा IFF_LOWER_UP			IFF_LOWER_UP
#घोषणा IFF_DORMANT			IFF_DORMANT
#घोषणा IFF_ECHO			IFF_ECHO
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO */

#घोषणा IFF_VOLATILE	(IFF_LOOPBACK|IFF_POINTOPOINT|IFF_BROADCAST|IFF_ECHO|\
		IFF_MASTER|IFF_SLAVE|IFF_RUNNING|IFF_LOWER_UP|IFF_DORMANT)

#घोषणा IF_GET_IFACE	0x0001		/* क्रम querying only */
#घोषणा IF_GET_PROTO	0x0002

/* For definitions see hdlc.h */
#घोषणा IF_IFACE_V35	0x1000		/* V.35 serial पूर्णांकerface	*/
#घोषणा IF_IFACE_V24	0x1001		/* V.24 serial पूर्णांकerface	*/
#घोषणा IF_IFACE_X21	0x1002		/* X.21 serial पूर्णांकerface	*/
#घोषणा IF_IFACE_T1	0x1003		/* T1 telco serial पूर्णांकerface	*/
#घोषणा IF_IFACE_E1	0x1004		/* E1 telco serial पूर्णांकerface	*/
#घोषणा IF_IFACE_SYNC_SERIAL 0x1005	/* can't be set by software	*/
#घोषणा IF_IFACE_X21D   0x1006          /* X.21 Dual Clocking (FarSite) */

/* For definitions see hdlc.h */
#घोषणा IF_PROTO_HDLC	0x2000		/* raw HDLC protocol		*/
#घोषणा IF_PROTO_PPP	0x2001		/* PPP protocol			*/
#घोषणा IF_PROTO_CISCO	0x2002		/* Cisco HDLC protocol		*/
#घोषणा IF_PROTO_FR	0x2003		/* Frame Relay protocol		*/
#घोषणा IF_PROTO_FR_ADD_PVC 0x2004	/*    Create FR PVC		*/
#घोषणा IF_PROTO_FR_DEL_PVC 0x2005	/*    Delete FR PVC		*/
#घोषणा IF_PROTO_X25	0x2006		/* X.25				*/
#घोषणा IF_PROTO_HDLC_ETH 0x2007	/* raw HDLC, Ethernet emulation	*/
#घोषणा IF_PROTO_FR_ADD_ETH_PVC 0x2008	/*  Create FR Ethernet-bridged PVC */
#घोषणा IF_PROTO_FR_DEL_ETH_PVC 0x2009	/*  Delete FR Ethernet-bridged PVC */
#घोषणा IF_PROTO_FR_PVC	0x200A		/* क्रम पढ़ोing PVC status	*/
#घोषणा IF_PROTO_FR_ETH_PVC 0x200B
#घोषणा IF_PROTO_RAW    0x200C          /* RAW Socket                   */

/* RFC 2863 operational status */
क्रमागत अणु
	IF_OPER_UNKNOWN,
	IF_OPER_NOTPRESENT,
	IF_OPER_DOWN,
	IF_OPER_LOWERLAYERDOWN,
	IF_OPER_TESTING,
	IF_OPER_DORMANT,
	IF_OPER_UP,
पूर्ण;

/* link modes */
क्रमागत अणु
	IF_LINK_MODE_DEFAULT,
	IF_LINK_MODE_DORMANT,	/* limit upward transition to करोrmant */
	IF_LINK_MODE_TESTING,	/* limit upward transition to testing */
पूर्ण;

/*
 *	Device mapping काष्ठाure. I'd just gone off and deचिन्हित a 
 *	beautअगरul scheme using only loadable modules with arguments
 *	क्रम driver options and aदीर्घ come the PCMCIA people 8)
 *
 *	Ah well. The get() side of this is good क्रम WDSETUP, and it'll
 *	be handy क्रम debugging things. The set side is fine क्रम now and
 *	being very small might be worth keeping क्रम clean configuration.
 */

/* क्रम compatibility with glibc net/अगर.h */
#अगर __UAPI_DEF_IF_IFMAP
काष्ठा अगरmap अणु
	अचिन्हित दीर्घ mem_start;
	अचिन्हित दीर्घ mem_end;
	अचिन्हित लघु base_addr; 
	अचिन्हित अक्षर irq;
	अचिन्हित अक्षर dma;
	अचिन्हित अक्षर port;
	/* 3 bytes spare */
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IF_IFMAP */

काष्ठा अगर_settings अणु
	अचिन्हित पूर्णांक type;	/* Type of physical device or protocol */
	अचिन्हित पूर्णांक size;	/* Size of the data allocated by the caller */
	जोड़ अणु
		/* अणुaपंचांग/eth/dslपूर्ण_settings anyone ? */
		raw_hdlc_proto		__user *raw_hdlc;
		cisco_proto		__user *cisco;
		fr_proto		__user *fr;
		fr_proto_pvc		__user *fr_pvc;
		fr_proto_pvc_info	__user *fr_pvc_info;
		x25_hdlc_proto		__user *x25;

		/* पूर्णांकerface settings */
		sync_serial_settings	__user *sync;
		te1_settings		__user *te1;
	पूर्ण अगरs_अगरsu;
पूर्ण;

/*
 * Interface request काष्ठाure used क्रम socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with अगरr_name.  The
 * reमुख्यder may be पूर्णांकerface specअगरic.
 */

/* क्रम compatibility with glibc net/अगर.h */
#अगर __UAPI_DEF_IF_IFREQ
काष्ठा अगरreq अणु
#घोषणा IFHWADDRLEN	6
	जोड़
	अणु
		अक्षर	अगरrn_name[IFNAMSIZ];		/* अगर name, e.g. "en0" */
	पूर्ण अगरr_अगरrn;
	
	जोड़ अणु
		काष्ठा	sockaddr अगरru_addr;
		काष्ठा	sockaddr अगरru_dstaddr;
		काष्ठा	sockaddr अगरru_broadaddr;
		काष्ठा	sockaddr अगरru_neपंचांगask;
		काष्ठा  sockaddr अगरru_hwaddr;
		लघु	अगरru_flags;
		पूर्णांक	अगरru_ivalue;
		पूर्णांक	अगरru_mtu;
		काष्ठा  अगरmap अगरru_map;
		अक्षर	अगरru_slave[IFNAMSIZ];	/* Just fits the size */
		अक्षर	अगरru_newname[IFNAMSIZ];
		व्योम __user *	अगरru_data;
		काष्ठा	अगर_settings अगरru_settings;
	पूर्ण अगरr_अगरru;
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IF_IFREQ */

#घोषणा अगरr_name	अगरr_अगरrn.अगरrn_name	/* पूर्णांकerface name 	*/
#घोषणा अगरr_hwaddr	अगरr_अगरru.अगरru_hwaddr	/* MAC address 		*/
#घोषणा	अगरr_addr	अगरr_अगरru.अगरru_addr	/* address		*/
#घोषणा	अगरr_dstaddr	अगरr_अगरru.अगरru_dstaddr	/* other end of p-p lnk	*/
#घोषणा	अगरr_broadaddr	अगरr_अगरru.अगरru_broadaddr	/* broadcast address	*/
#घोषणा	अगरr_neपंचांगask	अगरr_अगरru.अगरru_neपंचांगask	/* पूर्णांकerface net mask	*/
#घोषणा	अगरr_flags	अगरr_अगरru.अगरru_flags	/* flags		*/
#घोषणा	अगरr_metric	अगरr_अगरru.अगरru_ivalue	/* metric		*/
#घोषणा	अगरr_mtu		अगरr_अगरru.अगरru_mtu	/* mtu			*/
#घोषणा अगरr_map		अगरr_अगरru.अगरru_map	/* device map		*/
#घोषणा अगरr_slave	अगरr_अगरru.अगरru_slave	/* slave device		*/
#घोषणा	अगरr_data	अगरr_अगरru.अगरru_data	/* क्रम use by पूर्णांकerface	*/
#घोषणा अगरr_अगरindex	अगरr_अगरru.अगरru_ivalue	/* पूर्णांकerface index	*/
#घोषणा अगरr_bandwidth	अगरr_अगरru.अगरru_ivalue    /* link bandwidth	*/
#घोषणा अगरr_qlen	अगरr_अगरru.अगरru_ivalue	/* Queue length 	*/
#घोषणा अगरr_newname	अगरr_अगरru.अगरru_newname	/* New name		*/
#घोषणा अगरr_settings	अगरr_अगरru.अगरru_settings	/* Device/proto settings*/

/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve पूर्णांकerface configuration
 * क्रम machine (useful क्रम programs which
 * must know all networks accessible).
 */

/* क्रम compatibility with glibc net/अगर.h */
#अगर __UAPI_DEF_IF_IFCONF
काष्ठा अगरconf  अणु
	पूर्णांक	अगरc_len;			/* size of buffer	*/
	जोड़ अणु
		अक्षर __user *अगरcu_buf;
		काष्ठा अगरreq __user *अगरcu_req;
	पूर्ण अगरc_अगरcu;
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IF_IFCONF */

#घोषणा	अगरc_buf	अगरc_अगरcu.अगरcu_buf		/* buffer address	*/
#घोषणा	अगरc_req	अगरc_अगरcu.अगरcu_req		/* array of काष्ठाures	*/

#पूर्ण_अगर /* _LINUX_IF_H */
