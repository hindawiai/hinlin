<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_BRIDGE_NETFILTER_H
#घोषणा _UAPI__LINUX_BRIDGE_NETFILTER_H

/* bridge-specअगरic defines क्रम netfilter. 
 */

#समावेश <linux/in.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_pppox.h>

#अगर_अघोषित __KERNEL__
#समावेश <सीमा.स> /* क्रम पूर्णांक_न्यून, पूर्णांक_उच्च */
#पूर्ण_अगर

/* Bridge Hooks */
/* After promisc drops, checksum checks. */
#घोषणा NF_BR_PRE_ROUTING	0
/* If the packet is destined क्रम this box. */
#घोषणा NF_BR_LOCAL_IN		1
/* If the packet is destined क्रम another पूर्णांकerface. */
#घोषणा NF_BR_FORWARD		2
/* Packets coming from a local process. */
#घोषणा NF_BR_LOCAL_OUT		3
/* Packets about to hit the wire. */
#घोषणा NF_BR_POST_ROUTING	4
/* Not really a hook, but used क्रम the ebtables broute table */
#घोषणा NF_BR_BROUTING		5
#घोषणा NF_BR_NUMHOOKS		6

क्रमागत nf_br_hook_priorities अणु
	NF_BR_PRI_FIRST = पूर्णांक_न्यून,
	NF_BR_PRI_NAT_DST_BRIDGED = -300,
	NF_BR_PRI_FILTER_BRIDGED = -200,
	NF_BR_PRI_BRNF = 0,
	NF_BR_PRI_NAT_DST_OTHER = 100,
	NF_BR_PRI_FILTER_OTHER = 200,
	NF_BR_PRI_NAT_SRC = 300,
	NF_BR_PRI_LAST = पूर्णांक_उच्च,
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_BRIDGE_NETFILTER_H */
