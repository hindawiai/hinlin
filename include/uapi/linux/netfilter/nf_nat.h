<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NETFILTER_NF_NAT_H
#घोषणा _NETFILTER_NF_NAT_H

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>

#घोषणा NF_NAT_RANGE_MAP_IPS			(1 << 0)
#घोषणा NF_NAT_RANGE_PROTO_SPECIFIED		(1 << 1)
#घोषणा NF_NAT_RANGE_PROTO_RANDOM		(1 << 2)
#घोषणा NF_NAT_RANGE_PERSISTENT			(1 << 3)
#घोषणा NF_NAT_RANGE_PROTO_RANDOM_FULLY		(1 << 4)
#घोषणा NF_NAT_RANGE_PROTO_OFFSET		(1 << 5)
#घोषणा NF_NAT_RANGE_NETMAP			(1 << 6)

#घोषणा NF_NAT_RANGE_PROTO_RANDOM_ALL		\
	(NF_NAT_RANGE_PROTO_RANDOM | NF_NAT_RANGE_PROTO_RANDOM_FULLY)

#घोषणा NF_NAT_RANGE_MASK					\
	(NF_NAT_RANGE_MAP_IPS | NF_NAT_RANGE_PROTO_SPECIFIED |	\
	 NF_NAT_RANGE_PROTO_RANDOM | NF_NAT_RANGE_PERSISTENT |	\
	 NF_NAT_RANGE_PROTO_RANDOM_FULLY | NF_NAT_RANGE_PROTO_OFFSET | \
	 NF_NAT_RANGE_NETMAP)

काष्ठा nf_nat_ipv4_range अणु
	अचिन्हित पूर्णांक			flags;
	__be32				min_ip;
	__be32				max_ip;
	जोड़ nf_conntrack_man_proto	min;
	जोड़ nf_conntrack_man_proto	max;
पूर्ण;

काष्ठा nf_nat_ipv4_multi_range_compat अणु
	अचिन्हित पूर्णांक			rangesize;
	काष्ठा nf_nat_ipv4_range	range[1];
पूर्ण;

काष्ठा nf_nat_range अणु
	अचिन्हित पूर्णांक			flags;
	जोड़ nf_inet_addr		min_addr;
	जोड़ nf_inet_addr		max_addr;
	जोड़ nf_conntrack_man_proto	min_proto;
	जोड़ nf_conntrack_man_proto	max_proto;
पूर्ण;

काष्ठा nf_nat_range2 अणु
	अचिन्हित पूर्णांक			flags;
	जोड़ nf_inet_addr		min_addr;
	जोड़ nf_inet_addr		max_addr;
	जोड़ nf_conntrack_man_proto	min_proto;
	जोड़ nf_conntrack_man_proto	max_proto;
	जोड़ nf_conntrack_man_proto	base_proto;
पूर्ण;

#पूर्ण_अगर /* _NETFILTER_NF_NAT_H */
