<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_NETFILTER_H
#घोषणा _UAPI__LINUX_NETFILTER_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

/* Responses from hook functions. */
#घोषणा NF_DROP 0
#घोषणा NF_ACCEPT 1
#घोषणा NF_STOLEN 2
#घोषणा NF_QUEUE 3
#घोषणा NF_REPEAT 4
#घोषणा NF_STOP 5	/* Deprecated, क्रम userspace nf_queue compatibility. */
#घोषणा NF_MAX_VERDICT NF_STOP

/* we overload the higher bits क्रम encoding auxiliary data such as the queue
 * number or त्रुटि_सं values. Not nice, but better than additional function
 * arguments. */
#घोषणा NF_VERDICT_MASK 0x000000ff

/* extra verdict flags have mask 0x0000ff00 */
#घोषणा NF_VERDICT_FLAG_QUEUE_BYPASS	0x00008000

/* queue number (NF_QUEUE) or त्रुटि_सं (NF_DROP) */
#घोषणा NF_VERDICT_QMASK 0xffff0000
#घोषणा NF_VERDICT_QBITS 16

#घोषणा NF_QUEUE_NR(x) ((((x) << 16) & NF_VERDICT_QMASK) | NF_QUEUE)

#घोषणा NF_DROP_ERR(x) (((-x) << 16) | NF_DROP)

/* only क्रम userspace compatibility */
#अगर_अघोषित __KERNEL__

/* NF_VERDICT_BITS should be 8 now, but userspace might अवरोध अगर this changes */
#घोषणा NF_VERDICT_BITS 16
#पूर्ण_अगर

क्रमागत nf_inet_hooks अणु
	NF_INET_PRE_ROUTING,
	NF_INET_LOCAL_IN,
	NF_INET_FORWARD,
	NF_INET_LOCAL_OUT,
	NF_INET_POST_ROUTING,
	NF_INET_NUMHOOKS,
	NF_INET_INGRESS = NF_INET_NUMHOOKS,
पूर्ण;

क्रमागत nf_dev_hooks अणु
	NF_NETDEV_INGRESS,
	NF_NETDEV_NUMHOOKS
पूर्ण;

क्रमागत अणु
	NFPROTO_UNSPEC =  0,
	NFPROTO_INET   =  1,
	NFPROTO_IPV4   =  2,
	NFPROTO_ARP    =  3,
	NFPROTO_NETDEV =  5,
	NFPROTO_BRIDGE =  7,
	NFPROTO_IPV6   = 10,
	NFPROTO_DECNET = 12,
	NFPROTO_NUMPROTO,
पूर्ण;

जोड़ nf_inet_addr अणु
	__u32		all[4];
	__be32		ip;
	__be32		ip6[4];
	काष्ठा in_addr	in;
	काष्ठा in6_addr	in6;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_NETFILTER_H */
