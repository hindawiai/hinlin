<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_IPSEC_H
#घोषणा _LINUX_IPSEC_H

/* The definitions, required to talk to KAME racoon IKE. */

#समावेश <linux/pfkeyv2.h>

#घोषणा IPSEC_PORT_ANY		0
#घोषणा IPSEC_ULPROTO_ANY	255
#घोषणा IPSEC_PROTO_ANY		255

क्रमागत अणु
	IPSEC_MODE_ANY		= 0,	/* We करो not support this क्रम SA */
	IPSEC_MODE_TRANSPORT	= 1,
	IPSEC_MODE_TUNNEL	= 2,
	IPSEC_MODE_BEET         = 3
पूर्ण;

क्रमागत अणु
	IPSEC_सूची_ANY		= 0,
	IPSEC_सूची_INBOUND	= 1,
	IPSEC_सूची_OUTBOUND	= 2,
	IPSEC_सूची_FWD		= 3,	/* It is our own */
	IPSEC_सूची_MAX		= 4,
	IPSEC_सूची_INVALID	= 5
पूर्ण;

क्रमागत अणु
	IPSEC_POLICY_DISCARD	= 0,
	IPSEC_POLICY_NONE	= 1,
	IPSEC_POLICY_IPSEC	= 2,
	IPSEC_POLICY_ENTRUST	= 3,
	IPSEC_POLICY_BYPASS	= 4
पूर्ण;

क्रमागत अणु
	IPSEC_LEVEL_DEFAULT	= 0,
	IPSEC_LEVEL_USE		= 1,
	IPSEC_LEVEL_REQUIRE	= 2,
	IPSEC_LEVEL_UNIQUE	= 3
पूर्ण;

#घोषणा IPSEC_MANUAL_REQID_MAX	0x3fff

#घोषणा IPSEC_REPLAYWSIZE  32

#पूर्ण_अगर	/* _LINUX_IPSEC_H */
