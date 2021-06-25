<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IEEE 802.15.4 पूर्णांकerface क्रम userspace
 *
 * Copyright 2007, 2008 Siemens AG
 *
 * Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 */

#अगर_अघोषित _AF_IEEE802154_H
#घोषणा _AF_IEEE802154_H

#समावेश <linux/socket.h> /* क्रम sa_family_t */

क्रमागत अणु
	IEEE802154_ADDR_NONE = 0x0,
	/* RESERVED = 0x01, */
	IEEE802154_ADDR_SHORT = 0x2, /* 16-bit address + PANid */
	IEEE802154_ADDR_LONG = 0x3, /* 64-bit address + PANid */
पूर्ण;

/* address length, octets */
#घोषणा IEEE802154_ADDR_LEN	8

काष्ठा ieee802154_addr_sa अणु
	पूर्णांक addr_type;
	u16 pan_id;
	जोड़ अणु
		u8 hwaddr[IEEE802154_ADDR_LEN];
		u16 लघु_addr;
	पूर्ण;
पूर्ण;

#घोषणा IEEE802154_PANID_BROADCAST	0xffff
#घोषणा IEEE802154_ADDR_BROADCAST	0xffff
#घोषणा IEEE802154_ADDR_UNDEF		0xfffe

काष्ठा sockaddr_ieee802154 अणु
	sa_family_t family; /* AF_IEEE802154 */
	काष्ठा ieee802154_addr_sa addr;
पूर्ण;

/* get/setsockopt */
#घोषणा SOL_IEEE802154	0

#घोषणा WPAN_WANTACK		0
#घोषणा WPAN_SECURITY		1
#घोषणा WPAN_SECURITY_LEVEL	2
#घोषणा WPAN_WANTLQI		3

#घोषणा WPAN_SECURITY_DEFAULT	0
#घोषणा WPAN_SECURITY_OFF	1
#घोषणा WPAN_SECURITY_ON	2

#घोषणा WPAN_SECURITY_LEVEL_DEFAULT	(-1)

#पूर्ण_अगर
