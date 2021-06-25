<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  SR-IPv6 implementation
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 */

#अगर_अघोषित _NET_SEG6_H
#घोषणा _NET_SEG6_H

#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/seg6.h>
#समावेश <linux/rhashtable-types.h>

अटल अंतरभूत व्योम update_csum_dअगरf4(काष्ठा sk_buff *skb, __be32 from,
				     __be32 to)
अणु
	__be32 dअगरf[] = अणु ~from, to पूर्ण;

	skb->csum = ~csum_partial((अक्षर *)dअगरf, माप(dअगरf), ~skb->csum);
पूर्ण

अटल अंतरभूत व्योम update_csum_dअगरf16(काष्ठा sk_buff *skb, __be32 *from,
				      __be32 *to)
अणु
	__be32 dअगरf[] = अणु
		~from[0], ~from[1], ~from[2], ~from[3],
		to[0], to[1], to[2], to[3],
	पूर्ण;

	skb->csum = ~csum_partial((अक्षर *)dअगरf, माप(dअगरf), ~skb->csum);
पूर्ण

काष्ठा seg6_pernet_data अणु
	काष्ठा mutex lock;
	काष्ठा in6_addr __rcu *tun_src;
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	काष्ठा rhashtable hmac_infos;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा seg6_pernet_data *seg6_pernet(काष्ठा net *net)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	वापस net->ipv6.seg6_data;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

बाह्य पूर्णांक seg6_init(व्योम);
बाह्य व्योम seg6_निकास(व्योम);
बाह्य पूर्णांक seg6_iptunnel_init(व्योम);
बाह्य व्योम seg6_iptunnel_निकास(व्योम);
बाह्य पूर्णांक seg6_local_init(व्योम);
बाह्य व्योम seg6_local_निकास(व्योम);

बाह्य bool seg6_validate_srh(काष्ठा ipv6_sr_hdr *srh, पूर्णांक len, bool reduced);
बाह्य पूर्णांक seg6_करो_srh_encap(काष्ठा sk_buff *skb, काष्ठा ipv6_sr_hdr *osrh,
			     पूर्णांक proto);
बाह्य पूर्णांक seg6_करो_srh_अंतरभूत(काष्ठा sk_buff *skb, काष्ठा ipv6_sr_hdr *osrh);
बाह्य पूर्णांक seg6_lookup_nexthop(काष्ठा sk_buff *skb, काष्ठा in6_addr *nhaddr,
			       u32 tbl_id);
#पूर्ण_अगर
