<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IF_LINK_H
#घोषणा _LINUX_IF_LINK_H

#समावेश <uapi/linux/अगर_link.h>


/* We करोn't want this काष्ठाure exposed to user space */
काष्ठा अगरla_vf_stats अणु
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 broadcast;
	__u64 multicast;
	__u64 rx_dropped;
	__u64 tx_dropped;
पूर्ण;

काष्ठा अगरla_vf_info अणु
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 spoofchk;
	__u32 linkstate;
	__u32 min_tx_rate;
	__u32 max_tx_rate;
	__u32 rss_query_en;
	__u32 trusted;
	__be16 vlan_proto;
पूर्ण;
#पूर्ण_अगर /* _LINUX_IF_LINK_H */
