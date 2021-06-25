<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Universal TUN/TAP device driver.
 *  Copyright (C) 1999-2000 Maxim Krasnyansky <max_mk@yahoo.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License क्रम more details.
 */

#अगर_अघोषित _UAPI__IF_TUN_H
#घोषणा _UAPI__IF_TUN_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/filter.h>

/* Read queue size */
#घोषणा TUN_READQ_SIZE	500
/* TUN device type flags: deprecated. Use IFF_TUN/IFF_TAP instead. */
#घोषणा TUN_TUN_DEV 	IFF_TUN
#घोषणा TUN_TAP_DEV	IFF_TAP
#घोषणा TUN_TYPE_MASK   0x000f

/* Ioctl defines */
#घोषणा TUNSETNOCSUM  _IOW('T', 200, पूर्णांक) 
#घोषणा TUNSETDEBUG   _IOW('T', 201, पूर्णांक) 
#घोषणा TUNSETIFF     _IOW('T', 202, पूर्णांक) 
#घोषणा TUNSETPERSIST _IOW('T', 203, पूर्णांक) 
#घोषणा TUNSETOWNER   _IOW('T', 204, पूर्णांक)
#घोषणा TUNSETLINK    _IOW('T', 205, पूर्णांक)
#घोषणा TUNSETGROUP   _IOW('T', 206, पूर्णांक)
#घोषणा TUNGETFEATURES _IOR('T', 207, अचिन्हित पूर्णांक)
#घोषणा TUNSETOFFLOAD  _IOW('T', 208, अचिन्हित पूर्णांक)
#घोषणा TUNSETTXFILTER _IOW('T', 209, अचिन्हित पूर्णांक)
#घोषणा TUNGETIFF      _IOR('T', 210, अचिन्हित पूर्णांक)
#घोषणा TUNGETSNDBUF   _IOR('T', 211, पूर्णांक)
#घोषणा TUNSETSNDBUF   _IOW('T', 212, पूर्णांक)
#घोषणा TUNATTACHFILTER _IOW('T', 213, काष्ठा sock_fprog)
#घोषणा TUNDETACHFILTER _IOW('T', 214, काष्ठा sock_fprog)
#घोषणा TUNGETVNETHDRSZ _IOR('T', 215, पूर्णांक)
#घोषणा TUNSETVNETHDRSZ _IOW('T', 216, पूर्णांक)
#घोषणा TUNSETQUEUE  _IOW('T', 217, पूर्णांक)
#घोषणा TUNSETIFINDEX	_IOW('T', 218, अचिन्हित पूर्णांक)
#घोषणा TUNGETFILTER _IOR('T', 219, काष्ठा sock_fprog)
#घोषणा TUNSETVNETLE _IOW('T', 220, पूर्णांक)
#घोषणा TUNGETVNETLE _IOR('T', 221, पूर्णांक)
/* The TUNSETVNETBE and TUNGETVNETBE ioctls are क्रम cross-endian support on
 * little-endian hosts. Not all kernel configurations support them, but all
 * configurations that support SET also support GET.
 */
#घोषणा TUNSETVNETBE _IOW('T', 222, पूर्णांक)
#घोषणा TUNGETVNETBE _IOR('T', 223, पूर्णांक)
#घोषणा TUNSETSTEERINGEBPF _IOR('T', 224, पूर्णांक)
#घोषणा TUNSETFILTEREBPF _IOR('T', 225, पूर्णांक)
#घोषणा TUNSETCARRIER _IOW('T', 226, पूर्णांक)
#घोषणा TUNGETDEVNETNS _IO('T', 227)

/* TUNSETIFF अगरr flags */
#घोषणा IFF_TUN		0x0001
#घोषणा IFF_TAP		0x0002
#घोषणा IFF_NAPI	0x0010
#घोषणा IFF_NAPI_FRAGS	0x0020
#घोषणा IFF_NO_PI	0x1000
/* This flag has no real effect */
#घोषणा IFF_ONE_QUEUE	0x2000
#घोषणा IFF_VNET_HDR	0x4000
#घोषणा IFF_TUN_EXCL	0x8000
#घोषणा IFF_MULTI_QUEUE 0x0100
#घोषणा IFF_ATTACH_QUEUE 0x0200
#घोषणा IFF_DETACH_QUEUE 0x0400
/* पढ़ो-only flag */
#घोषणा IFF_PERSIST	0x0800
#घोषणा IFF_NOFILTER	0x1000

/* Socket options */
#घोषणा TUN_TX_TIMESTAMP 1

/* Features क्रम GSO (TUNSETOFFLOAD). */
#घोषणा TUN_F_CSUM	0x01	/* You can hand me unchecksummed packets. */
#घोषणा TUN_F_TSO4	0x02	/* I can handle TSO क्रम IPv4 packets */
#घोषणा TUN_F_TSO6	0x04	/* I can handle TSO क्रम IPv6 packets */
#घोषणा TUN_F_TSO_ECN	0x08	/* I can handle TSO with ECN bits. */
#घोषणा TUN_F_UFO	0x10	/* I can handle UFO packets */

/* Protocol info prepended to the packets (when IFF_NO_PI is not set) */
#घोषणा TUN_PKT_STRIP	0x0001
काष्ठा tun_pi अणु
	__u16  flags;
	__be16 proto;
पूर्ण;

/*
 * Filter spec (used क्रम SETXXFILTER ioctls)
 * This stuff is applicable only to the TAP (Ethernet) devices.
 * If the count is zero the filter is disabled and the driver accepts
 * all packets (promisc mode).
 * If the filter is enabled in order to accept broadcast packets
 * broadcast addr must be explicitly included in the addr list.
 */
#घोषणा TUN_FLT_ALLMULTI 0x0001 /* Accept all multicast packets */
काष्ठा tun_filter अणु
	__u16  flags; /* TUN_FLT_ flags see above */
	__u16  count; /* Number of addresses */
	__u8   addr[0][ETH_ALEN];
पूर्ण;

#पूर्ण_अगर /* _UAPI__IF_TUN_H */
