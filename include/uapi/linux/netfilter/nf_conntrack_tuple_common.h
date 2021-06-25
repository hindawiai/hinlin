<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NF_CONNTRACK_TUPLE_COMMON_H
#घोषणा _NF_CONNTRACK_TUPLE_COMMON_H

#समावेश <linux/types.h>
#अगर_अघोषित __KERNEL__
#समावेश <linux/netfilter.h>
#पूर्ण_अगर
#समावेश <linux/netfilter/nf_conntrack_common.h> /* IP_CT_IS_REPLY */

क्रमागत ip_conntrack_dir अणु
	IP_CT_सूची_ORIGINAL,
	IP_CT_सूची_REPLY,
	IP_CT_सूची_MAX
पूर्ण;

/* The protocol-specअगरic manipulable parts of the tuple: always in
 * network order
 */
जोड़ nf_conntrack_man_proto अणु
	/* Add other protocols here. */
	__be16 all;

	काष्ठा अणु
		__be16 port;
	पूर्ण tcp;
	काष्ठा अणु
		__be16 port;
	पूर्ण udp;
	काष्ठा अणु
		__be16 id;
	पूर्ण icmp;
	काष्ठा अणु
		__be16 port;
	पूर्ण dccp;
	काष्ठा अणु
		__be16 port;
	पूर्ण sctp;
	काष्ठा अणु
		__be16 key;	/* GRE key is 32bit, PPtP only uses 16bit */
	पूर्ण gre;
पूर्ण;

#घोषणा CTINFO2सूची(ctinfo) ((ctinfo) >= IP_CT_IS_REPLY ? IP_CT_सूची_REPLY : IP_CT_सूची_ORIGINAL)

#पूर्ण_अगर /* _NF_CONNTRACK_TUPLE_COMMON_H */
