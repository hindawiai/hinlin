<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  SR-IPv6 implementation
 *
 *  Authors:
 *  David Lebrun <david.lebrun@uclouvain.be>
 *  eBPF support: Mathieu Xhonneux <m.xhonneux@gmail.com>
 */

#अगर_अघोषित _NET_SEG6_LOCAL_H
#घोषणा _NET_SEG6_LOCAL_H

#समावेश <linux/percpu.h>
#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>

बाह्य पूर्णांक seg6_lookup_nexthop(काष्ठा sk_buff *skb, काष्ठा in6_addr *nhaddr,
			       u32 tbl_id);
बाह्य bool seg6_bpf_has_valid_srh(काष्ठा sk_buff *skb);

काष्ठा seg6_bpf_srh_state अणु
	काष्ठा ipv6_sr_hdr *srh;
	u16 hdrlen;
	bool valid;
पूर्ण;

DECLARE_PER_CPU(काष्ठा seg6_bpf_srh_state, seg6_bpf_srh_states);

#पूर्ण_अगर
