<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NETFILTER_CORE_H_
#घोषणा __LINUX_NETFILTER_CORE_H_

#समावेश <uapi/linux/netfilter.h>

/* in/out/क्रमward only */
#घोषणा NF_ARP_NUMHOOKS 3

/* max hook is NF_DN_ROUTE (6), also see uapi/linux/netfilter_decnet.h */
#घोषणा NF_DN_NUMHOOKS 7

#अगर IS_ENABLED(CONFIG_DECNET)
/* Largest hook number + 1, see uapi/linux/netfilter_decnet.h */
#घोषणा NF_MAX_HOOKS	NF_DN_NUMHOOKS
#अन्यथा
#घोषणा NF_MAX_HOOKS	NF_INET_NUMHOOKS
#पूर्ण_अगर

#पूर्ण_अगर
