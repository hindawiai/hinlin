<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* IPv6-specअगरic defines क्रम netfilter. 
 * (C)1998 Rusty Russell -- This code is GPL.
 * (C)1999 David Jeffery
 *   this header was blatantly ripped from netfilter_ipv4.h 
 *   it's amazing what adding a bunch of 6s can करो =8^)
 */
#अगर_अघोषित _UAPI__LINUX_IP6_NETFILTER_H
#घोषणा _UAPI__LINUX_IP6_NETFILTER_H


#समावेश <linux/netfilter.h>

/* only क्रम userspace compatibility */
#अगर_अघोषित __KERNEL__

#समावेश <सीमा.स> /* क्रम पूर्णांक_न्यून, पूर्णांक_उच्च */

/* IP6 Hooks */
/* After promisc drops, checksum checks. */
#घोषणा NF_IP6_PRE_ROUTING	0
/* If the packet is destined क्रम this box. */
#घोषणा NF_IP6_LOCAL_IN		1
/* If the packet is destined क्रम another पूर्णांकerface. */
#घोषणा NF_IP6_FORWARD		2
/* Packets coming from a local process. */
#घोषणा NF_IP6_LOCAL_OUT		3
/* Packets about to hit the wire. */
#घोषणा NF_IP6_POST_ROUTING	4
#घोषणा NF_IP6_NUMHOOKS		5
#पूर्ण_अगर /* ! __KERNEL__ */


क्रमागत nf_ip6_hook_priorities अणु
	NF_IP6_PRI_FIRST = पूर्णांक_न्यून,
	NF_IP6_PRI_RAW_BEFORE_DEFRAG = -450,
	NF_IP6_PRI_CONNTRACK_DEFRAG = -400,
	NF_IP6_PRI_RAW = -300,
	NF_IP6_PRI_SELINUX_FIRST = -225,
	NF_IP6_PRI_CONNTRACK = -200,
	NF_IP6_PRI_MANGLE = -150,
	NF_IP6_PRI_NAT_DST = -100,
	NF_IP6_PRI_FILTER = 0,
	NF_IP6_PRI_SECURITY = 50,
	NF_IP6_PRI_NAT_SRC = 100,
	NF_IP6_PRI_SELINUX_LAST = 225,
	NF_IP6_PRI_CONNTRACK_HELPER = 300,
	NF_IP6_PRI_LAST = पूर्णांक_उच्च,
पूर्ण;


#पूर्ण_अगर /* _UAPI__LINUX_IP6_NETFILTER_H */
