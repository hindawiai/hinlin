<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_NETCONF_H_
#घोषणा _UAPI_LINUX_NETCONF_H_

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>

काष्ठा netconfmsg अणु
	__u8	ncm_family;
पूर्ण;

क्रमागत अणु
	NETCONFA_UNSPEC,
	NETCONFA_IFINDEX,
	NETCONFA_FORWARDING,
	NETCONFA_RP_FILTER,
	NETCONFA_MC_FORWARDING,
	NETCONFA_PROXY_NEIGH,
	NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
	NETCONFA_INPUT,
	NETCONFA_BC_FORWARDING,
	__NETCONFA_MAX
पूर्ण;
#घोषणा NETCONFA_MAX	(__NETCONFA_MAX - 1)
#घोषणा NETCONFA_ALL	-1

#घोषणा NETCONFA_IFINDEX_ALL		-1
#घोषणा NETCONFA_IFINDEX_DEFAULT	-2

#पूर्ण_अगर /* _UAPI_LINUX_NETCONF_H_ */
