<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_DECNET_NETFILTER_H
#घोषणा __LINUX_DECNET_NETFILTER_H

/* DECnet-specअगरic defines क्रम netfilter. 
 * This file (C) Steve Whitehouse 1999 derived from the
 * ipv4 netfilter header file which is
 * (C)1998 Rusty Russell -- This code is GPL.
 */

#समावेश <linux/netfilter.h>

/* only क्रम userspace compatibility */
#अगर_अघोषित __KERNEL__

#समावेश <सीमा.स> /* क्रम पूर्णांक_न्यून, पूर्णांक_उच्च */

/* kernel define is in netfilter_defs.h */
#घोषणा NF_DN_NUMHOOKS		7
#पूर्ण_अगर /* ! __KERNEL__ */

/* DECnet Hooks */
/* After promisc drops, checksum checks. */
#घोषणा NF_DN_PRE_ROUTING	0
/* If the packet is destined क्रम this box. */
#घोषणा NF_DN_LOCAL_IN		1
/* If the packet is destined क्रम another पूर्णांकerface. */
#घोषणा NF_DN_FORWARD		2
/* Packets coming from a local process. */
#घोषणा NF_DN_LOCAL_OUT		3
/* Packets about to hit the wire. */
#घोषणा NF_DN_POST_ROUTING	4
/* Input Hello Packets */
#घोषणा NF_DN_HELLO		5
/* Input Routing Packets */
#घोषणा NF_DN_ROUTE		6

क्रमागत nf_dn_hook_priorities अणु
	NF_DN_PRI_FIRST = पूर्णांक_न्यून,
	NF_DN_PRI_CONNTRACK = -200,
	NF_DN_PRI_MANGLE = -150,
	NF_DN_PRI_NAT_DST = -100,
	NF_DN_PRI_FILTER = 0,
	NF_DN_PRI_NAT_SRC = 100,
	NF_DN_PRI_DNRTMSG = 200,
	NF_DN_PRI_LAST = पूर्णांक_उच्च,
पूर्ण;

काष्ठा nf_dn_rपंचांगsg अणु
	पूर्णांक nfdn_अगरindex;
पूर्ण;

#घोषणा NFDN_RTMSG(r) ((अचिन्हित अक्षर *)(r) + NLMSG_ALIGN(माप(काष्ठा nf_dn_rपंचांगsg)))

#अगर_अघोषित __KERNEL__
/* backwards compatibility क्रम userspace */
#घोषणा DNRMG_L1_GROUP 0x01
#घोषणा DNRMG_L2_GROUP 0x02
#पूर्ण_अगर

क्रमागत अणु
	DNRNG_NLGRP_NONE,
#घोषणा DNRNG_NLGRP_NONE	DNRNG_NLGRP_NONE
	DNRNG_NLGRP_L1,
#घोषणा DNRNG_NLGRP_L1		DNRNG_NLGRP_L1
	DNRNG_NLGRP_L2,
#घोषणा DNRNG_NLGRP_L2		DNRNG_NLGRP_L2
	__DNRNG_NLGRP_MAX
पूर्ण;
#घोषणा DNRNG_NLGRP_MAX	(__DNRNG_NLGRP_MAX - 1)

#पूर्ण_अगर /*__LINUX_DECNET_NETFILTER_H*/
