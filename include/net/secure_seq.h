<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_SECURE_SEQ
#घोषणा _NET_SECURE_SEQ

#समावेश <linux/types.h>

u32 secure_ipv4_port_ephemeral(__be32 saddr, __be32 daddr, __be16 dport);
u32 secure_ipv6_port_ephemeral(स्थिर __be32 *saddr, स्थिर __be32 *daddr,
			       __be16 dport);
u32 secure_tcp_seq(__be32 saddr, __be32 daddr,
		   __be16 sport, __be16 dport);
u32 secure_tcp_ts_off(स्थिर काष्ठा net *net, __be32 saddr, __be32 daddr);
u32 secure_tcpv6_seq(स्थिर __be32 *saddr, स्थिर __be32 *daddr,
		     __be16 sport, __be16 dport);
u32 secure_tcpv6_ts_off(स्थिर काष्ठा net *net,
			स्थिर __be32 *saddr, स्थिर __be32 *daddr);
u64 secure_dccp_sequence_number(__be32 saddr, __be32 daddr,
				__be16 sport, __be16 dport);
u64 secure_dccpv6_sequence_number(__be32 *saddr, __be32 *daddr,
				  __be16 sport, __be16 dport);

#पूर्ण_अगर /* _NET_SECURE_SEQ */
