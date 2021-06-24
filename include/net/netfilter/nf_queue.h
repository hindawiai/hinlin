<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_QUEUE_H
#घोषणा _NF_QUEUE_H

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/jhash.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>

/* Each queued (to userspace) skbuff has one of these. */
काष्ठा nf_queue_entry अणु
	काष्ठा list_head	list;
	काष्ठा sk_buff		*skb;
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		hook_index;	/* index in hook_entries->hook[] */
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	काष्ठा net_device	*physin;
	काष्ठा net_device	*physout;
#पूर्ण_अगर
	काष्ठा nf_hook_state	state;
	u16			size; /* माप(entry) + saved route keys */

	/* extra space to store route keys */
पूर्ण;

#घोषणा nf_queue_entry_reroute(x) ((व्योम *)x + माप(काष्ठा nf_queue_entry))

/* Packet queuing */
काष्ठा nf_queue_handler अणु
	पूर्णांक		(*outfn)(काष्ठा nf_queue_entry *entry,
				 अचिन्हित पूर्णांक queuक्रमागत);
	व्योम		(*nf_hook_drop)(काष्ठा net *net);
पूर्ण;

व्योम nf_रेजिस्टर_queue_handler(काष्ठा net *net, स्थिर काष्ठा nf_queue_handler *qh);
व्योम nf_unरेजिस्टर_queue_handler(काष्ठा net *net);
व्योम nf_reinject(काष्ठा nf_queue_entry *entry, अचिन्हित पूर्णांक verdict);

व्योम nf_queue_entry_get_refs(काष्ठा nf_queue_entry *entry);
व्योम nf_queue_entry_मुक्त(काष्ठा nf_queue_entry *entry);

अटल अंतरभूत व्योम init_hashअक्रमom(u32 *jhash_initval)
अणु
	जबतक (*jhash_initval == 0)
		*jhash_initval = pअक्रमom_u32();
पूर्ण

अटल अंतरभूत u32 hash_v4(स्थिर काष्ठा iphdr *iph, u32 initval)
अणु
	/* packets in either direction go पूर्णांकo same queue */
	अगर ((__क्रमce u32)iph->saddr < (__क्रमce u32)iph->daddr)
		वापस jhash_3words((__क्रमce u32)iph->saddr,
			(__क्रमce u32)iph->daddr, iph->protocol, initval);

	वापस jhash_3words((__क्रमce u32)iph->daddr,
			(__क्रमce u32)iph->saddr, iph->protocol, initval);
पूर्ण

अटल अंतरभूत u32 hash_v6(स्थिर काष्ठा ipv6hdr *ip6h, u32 initval)
अणु
	u32 a, b, c;

	अगर ((__क्रमce u32)ip6h->saddr.s6_addr32[3] <
	    (__क्रमce u32)ip6h->daddr.s6_addr32[3]) अणु
		a = (__क्रमce u32) ip6h->saddr.s6_addr32[3];
		b = (__क्रमce u32) ip6h->daddr.s6_addr32[3];
	पूर्ण अन्यथा अणु
		b = (__क्रमce u32) ip6h->saddr.s6_addr32[3];
		a = (__क्रमce u32) ip6h->daddr.s6_addr32[3];
	पूर्ण

	अगर ((__क्रमce u32)ip6h->saddr.s6_addr32[1] <
	    (__क्रमce u32)ip6h->daddr.s6_addr32[1])
		c = (__क्रमce u32) ip6h->saddr.s6_addr32[1];
	अन्यथा
		c = (__क्रमce u32) ip6h->daddr.s6_addr32[1];

	वापस jhash_3words(a, b, c, initval);
पूर्ण

अटल अंतरभूत u32 hash_bridge(स्थिर काष्ठा sk_buff *skb, u32 initval)
अणु
	काष्ठा ipv6hdr *ip6h, _ip6h;
	काष्ठा iphdr *iph, _iph;

	चयन (eth_hdr(skb)->h_proto) अणु
	हाल htons(ETH_P_IP):
		iph = skb_header_poपूर्णांकer(skb, skb_network_offset(skb),
					 माप(*iph), &_iph);
		अगर (iph)
			वापस hash_v4(iph, initval);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ip6h = skb_header_poपूर्णांकer(skb, skb_network_offset(skb),
					  माप(*ip6h), &_ip6h);
		अगर (ip6h)
			वापस hash_v6(ip6h, initval);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32
nfqueue_hash(स्थिर काष्ठा sk_buff *skb, u16 queue, u16 queues_total, u8 family,
	     u32 initval)
अणु
	चयन (family) अणु
	हाल NFPROTO_IPV4:
		queue += reciprocal_scale(hash_v4(ip_hdr(skb), initval),
					  queues_total);
		अवरोध;
	हाल NFPROTO_IPV6:
		queue += reciprocal_scale(hash_v6(ipv6_hdr(skb), initval),
					  queues_total);
		अवरोध;
	हाल NFPROTO_BRIDGE:
		queue += reciprocal_scale(hash_bridge(skb, initval),
					  queues_total);
		अवरोध;
	पूर्ण

	वापस queue;
पूर्ण

पूर्णांक nf_queue(काष्ठा sk_buff *skb, काष्ठा nf_hook_state *state,
	     अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक verdict);

#पूर्ण_अगर /* _NF_QUEUE_H */
