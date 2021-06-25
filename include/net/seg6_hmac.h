<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  SR-IPv6 implementation
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 */

#अगर_अघोषित _NET_SEG6_HMAC_H
#घोषणा _NET_SEG6_HMAC_H

#समावेश <net/flow.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/sock.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/route.h>
#समावेश <net/seg6.h>
#समावेश <linux/seg6_hmac.h>
#समावेश <linux/rhashtable-types.h>

#घोषणा SEG6_HMAC_MAX_DIGESTSIZE	160
#घोषणा SEG6_HMAC_RING_SIZE		256

काष्ठा seg6_hmac_info अणु
	काष्ठा rhash_head node;
	काष्ठा rcu_head rcu;

	u32 hmackeyid;
	अक्षर secret[SEG6_HMAC_SECRET_LEN];
	u8 slen;
	u8 alg_id;
पूर्ण;

काष्ठा seg6_hmac_algo अणु
	u8 alg_id;
	अक्षर name[64];
	काष्ठा crypto_shash * __percpu *tfms;
	काष्ठा shash_desc * __percpu *shashs;
पूर्ण;

बाह्य पूर्णांक seg6_hmac_compute(काष्ठा seg6_hmac_info *hinfo,
			     काष्ठा ipv6_sr_hdr *hdr, काष्ठा in6_addr *saddr,
			     u8 *output);
बाह्य काष्ठा seg6_hmac_info *seg6_hmac_info_lookup(काष्ठा net *net, u32 key);
बाह्य पूर्णांक seg6_hmac_info_add(काष्ठा net *net, u32 key,
			      काष्ठा seg6_hmac_info *hinfo);
बाह्य पूर्णांक seg6_hmac_info_del(काष्ठा net *net, u32 key);
बाह्य पूर्णांक seg6_push_hmac(काष्ठा net *net, काष्ठा in6_addr *saddr,
			  काष्ठा ipv6_sr_hdr *srh);
बाह्य bool seg6_hmac_validate_skb(काष्ठा sk_buff *skb);
बाह्य पूर्णांक seg6_hmac_init(व्योम);
बाह्य व्योम seg6_hmac_निकास(व्योम);
बाह्य पूर्णांक seg6_hmac_net_init(काष्ठा net *net);
बाह्य व्योम seg6_hmac_net_निकास(काष्ठा net *net);

#पूर्ण_अगर
