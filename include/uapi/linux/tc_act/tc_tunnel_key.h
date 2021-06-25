<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (c) 2016, Amir Vadai <amir@vadai.me>
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित __LINUX_TC_TUNNEL_KEY_H
#घोषणा __LINUX_TC_TUNNEL_KEY_H

#समावेश <linux/pkt_cls.h>

#घोषणा TCA_TUNNEL_KEY_ACT_SET	    1
#घोषणा TCA_TUNNEL_KEY_ACT_RELEASE  2

काष्ठा tc_tunnel_key अणु
	tc_gen;
	पूर्णांक t_action;
पूर्ण;

क्रमागत अणु
	TCA_TUNNEL_KEY_UNSPEC,
	TCA_TUNNEL_KEY_TM,
	TCA_TUNNEL_KEY_PARMS,
	TCA_TUNNEL_KEY_ENC_IPV4_SRC,	/* be32 */
	TCA_TUNNEL_KEY_ENC_IPV4_DST,	/* be32 */
	TCA_TUNNEL_KEY_ENC_IPV6_SRC,	/* काष्ठा in6_addr */
	TCA_TUNNEL_KEY_ENC_IPV6_DST,	/* काष्ठा in6_addr */
	TCA_TUNNEL_KEY_ENC_KEY_ID,	/* be64 */
	TCA_TUNNEL_KEY_PAD,
	TCA_TUNNEL_KEY_ENC_DST_PORT,	/* be16 */
	TCA_TUNNEL_KEY_NO_CSUM,		/* u8 */
	TCA_TUNNEL_KEY_ENC_OPTS,	/* Nested TCA_TUNNEL_KEY_ENC_OPTS_
					 * attributes
					 */
	TCA_TUNNEL_KEY_ENC_TOS,		/* u8 */
	TCA_TUNNEL_KEY_ENC_TTL,		/* u8 */
	__TCA_TUNNEL_KEY_MAX,
पूर्ण;

#घोषणा TCA_TUNNEL_KEY_MAX (__TCA_TUNNEL_KEY_MAX - 1)

क्रमागत अणु
	TCA_TUNNEL_KEY_ENC_OPTS_UNSPEC,
	TCA_TUNNEL_KEY_ENC_OPTS_GENEVE,		/* Nested
						 * TCA_TUNNEL_KEY_ENC_OPTS_
						 * attributes
						 */
	TCA_TUNNEL_KEY_ENC_OPTS_VXLAN,		/* Nested
						 * TCA_TUNNEL_KEY_ENC_OPTS_
						 * attributes
						 */
	TCA_TUNNEL_KEY_ENC_OPTS_ERSPAN,		/* Nested
						 * TCA_TUNNEL_KEY_ENC_OPTS_
						 * attributes
						 */
	__TCA_TUNNEL_KEY_ENC_OPTS_MAX,
पूर्ण;

#घोषणा TCA_TUNNEL_KEY_ENC_OPTS_MAX (__TCA_TUNNEL_KEY_ENC_OPTS_MAX - 1)

क्रमागत अणु
	TCA_TUNNEL_KEY_ENC_OPT_GENEVE_UNSPEC,
	TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS,		/* be16 */
	TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE,		/* u8 */
	TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA,		/* 4 to 128 bytes */

	__TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX,
पूर्ण;

#घोषणा TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX \
	(__TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX - 1)

क्रमागत अणु
	TCA_TUNNEL_KEY_ENC_OPT_VXLAN_UNSPEC,
	TCA_TUNNEL_KEY_ENC_OPT_VXLAN_GBP,		/* u32 */
	__TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX,
पूर्ण;

#घोषणा TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX \
	(__TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX - 1)

क्रमागत अणु
	TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_UNSPEC,
	TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_VER,		/* u8 */
	TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_INDEX,		/* be32 */
	TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_सूची,		/* u8 */
	TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_HWID,		/* u8 */
	__TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX,
पूर्ण;

#घोषणा TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX \
	(__TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX - 1)

#पूर्ण_अगर
