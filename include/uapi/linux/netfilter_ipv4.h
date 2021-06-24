<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* IPv4-specअगरic defines क्रम netfilter. 
 * (C)1998 Rusty Russell -- This code is GPL.
 */
#अगर_अघोषित _UAPI__LINUX_IP_NETFILTER_H
#घोषणा _UAPI__LINUX_IP_NETFILTER_H


#समावेश <linux/netfilter.h>

/* only क्रम userspace compatibility */
#अगर_अघोषित __KERNEL__

#समावेश <सीमा.स> /* क्रम पूर्णांक_न्यून, पूर्णांक_उच्च */

/* IP Hooks */
/* After promisc drops, checksum checks. */
#घोषणा NF_IP_PRE_ROUTING	0
/* If the packet is destined क्रम this box. */
#घोषणा NF_IP_LOCAL_IN		1
/* If the packet is destined क्रम another पूर्णांकerface. */
#घोषणा NF_IP_FORWARD		2
/* Packets coming from a local process. */
#घोषणा NF_IP_LOCAL_OUT		3
/* Packets about to hit the wire. */
#घोषणा NF_IP_POST_ROUTING	4
#घोषणा NF_IP_NUMHOOKS		5
#पूर्ण_अगर /* ! __KERNEL__ */

क्रमागत nf_ip_hook_priorities अणु
	NF_IP_PRI_FIRST = पूर्णांक_न्यून,
	NF_IP_PRI_RAW_BEFORE_DEFRAG = -450,
	NF_IP_PRI_CONNTRACK_DEFRAG = -400,
	NF_IP_PRI_RAW = -300,
	NF_IP_PRI_SELINUX_FIRST = -225,
	NF_IP_PRI_CONNTRACK = -200,
	NF_IP_PRI_MANGLE = -150,
	NF_IP_PRI_NAT_DST = -100,
	NF_IP_PRI_FILTER = 0,
	NF_IP_PRI_SECURITY = 50,
	NF_IP_PRI_NAT_SRC = 100,
	NF_IP_PRI_SELINUX_LAST = 225,
	NF_IP_PRI_CONNTRACK_HELPER = 300,
	NF_IP_PRI_CONNTRACK_CONFIRM = पूर्णांक_उच्च,
	NF_IP_PRI_LAST = पूर्णांक_उच्च,
पूर्ण;

/* Arguments क्रम setsockopt SOL_IP: */
/* 2.0 firewalling went from 64 through 71 (and +256, +512, etc). */
/* 2.2 firewalling (+ masq) went from 64 through 76 */
/* 2.4 firewalling went 64 through 67. */
#घोषणा SO_ORIGINAL_DST 80


#पूर्ण_अगर /* _UAPI__LINUX_IP_NETFILTER_H */
