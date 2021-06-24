<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the Interfaces handler.
 *
 * Version:	@(#)dev.h	1.0.10	08/12/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Corey Minyard <wf-rch!minyard@relay.EU.net>
 *		Donald J. Becker, <becker@cesdis.gsfc.nasa.gov>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Bjorn Ekwall. <bj0rn@blox.se>
 *              Pekka Riikonen <priikone@poseiकरोn.pspt.fi>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 *		Moved to /usr/include/linux क्रम NET3
 */
#अगर_अघोषित _UAPI_LINUX_NETDEVICE_H
#घोषणा _UAPI_LINUX_NETDEVICE_H

#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_link.h>


#घोषणा MAX_ADDR_LEN	32		/* Largest hardware address length */

/* Initial net device group. All devices beदीर्घ to group 0 by शेष. */
#घोषणा INIT_NETDEV_GROUP	0


/* पूर्णांकerface name assignment types (sysfs name_assign_type attribute) */
#घोषणा NET_NAME_UNKNOWN	0	/* unknown origin (not exposed to userspace) */
#घोषणा NET_NAME_ENUM		1	/* क्रमागतerated by kernel */
#घोषणा NET_NAME_PREDICTABLE	2	/* predictably named by the kernel */
#घोषणा NET_NAME_USER		3	/* provided by user-space */
#घोषणा NET_NAME_RENAMED	4	/* नामd by user-space */

/* Media selection options. */
क्रमागत अणु
        IF_PORT_UNKNOWN = 0,
        IF_PORT_10BASE2,
        IF_PORT_10BASET,
        IF_PORT_AUI,
        IF_PORT_100BASET,
        IF_PORT_100BASETX,
        IF_PORT_100BASEFX
पूर्ण;

/* hardware address assignment types */
#घोषणा NET_ADDR_PERM		0	/* address is permanent (शेष) */
#घोषणा NET_ADDR_RANDOM		1	/* address is generated अक्रमomly */
#घोषणा NET_ADDR_STOLEN		2	/* address is stolen from other device */
#घोषणा NET_ADDR_SET		3	/* address is set using
					 * dev_set_mac_address() */

#पूर्ण_अगर /* _UAPI_LINUX_NETDEVICE_H */
