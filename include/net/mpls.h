<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 Nicira, Inc.
 */

#अगर_अघोषित _NET_MPLS_H
#घोषणा _NET_MPLS_H 1

#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mpls.h>

#घोषणा MPLS_HLEN 4

काष्ठा mpls_shim_hdr अणु
	__be32 label_stack_entry;
पूर्ण;

अटल अंतरभूत bool eth_p_mpls(__be16 eth_type)
अणु
	वापस eth_type == htons(ETH_P_MPLS_UC) ||
		eth_type == htons(ETH_P_MPLS_MC);
पूर्ण

अटल अंतरभूत काष्ठा mpls_shim_hdr *mpls_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा mpls_shim_hdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा mpls_shim_hdr mpls_entry_encode(u32 label,
						     अचिन्हित पूर्णांक ttl,
						     अचिन्हित पूर्णांक tc,
						     bool bos)
अणु
	काष्ठा mpls_shim_hdr result;

	result.label_stack_entry =
		cpu_to_be32((label << MPLS_LS_LABEL_SHIFT) |
			    (tc << MPLS_LS_TC_SHIFT) |
			    (bos ? (1 << MPLS_LS_S_SHIFT) : 0) |
			    (ttl << MPLS_LS_TTL_SHIFT));
	वापस result;
पूर्ण

#पूर्ण_अगर
