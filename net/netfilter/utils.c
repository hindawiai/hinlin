<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/netfilter/nf_queue.h>
#समावेश <net/ip6_checksum.h>

#अगर_घोषित CONFIG_INET
__sum16 nf_ip_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
		       अचिन्हित पूर्णांक dataoff, u8 protocol)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	__sum16 csum = 0;

	चयन (skb->ip_summed) अणु
	हाल CHECKSUM_COMPLETE:
		अगर (hook != NF_INET_PRE_ROUTING && hook != NF_INET_LOCAL_IN)
			अवरोध;
		अगर ((protocol != IPPROTO_TCP && protocol != IPPROTO_UDP &&
		    !csum_fold(skb->csum)) ||
		    !csum_tcpudp_magic(iph->saddr, iph->daddr,
				       skb->len - dataoff, protocol,
				       skb->csum)) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CHECKSUM_NONE:
		अगर (protocol != IPPROTO_TCP && protocol != IPPROTO_UDP)
			skb->csum = 0;
		अन्यथा
			skb->csum = csum_tcpudp_nofold(iph->saddr, iph->daddr,
						       skb->len - dataoff,
						       protocol, 0);
		csum = __skb_checksum_complete(skb);
	पूर्ण
	वापस csum;
पूर्ण
EXPORT_SYMBOL(nf_ip_checksum);
#पूर्ण_अगर

अटल __sum16 nf_ip_checksum_partial(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
				      अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक len,
				      u8 protocol)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	__sum16 csum = 0;

	चयन (skb->ip_summed) अणु
	हाल CHECKSUM_COMPLETE:
		अगर (len == skb->len - dataoff)
			वापस nf_ip_checksum(skb, hook, dataoff, protocol);
		fallthrough;
	हाल CHECKSUM_NONE:
		skb->csum = csum_tcpudp_nofold(iph->saddr, iph->daddr, protocol,
					       skb->len - dataoff, 0);
		skb->ip_summed = CHECKSUM_NONE;
		वापस __skb_checksum_complete_head(skb, dataoff + len);
	पूर्ण
	वापस csum;
पूर्ण

__sum16 nf_ip6_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
			अचिन्हित पूर्णांक dataoff, u8 protocol)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	__sum16 csum = 0;

	चयन (skb->ip_summed) अणु
	हाल CHECKSUM_COMPLETE:
		अगर (hook != NF_INET_PRE_ROUTING && hook != NF_INET_LOCAL_IN)
			अवरोध;
		अगर (!csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
				     skb->len - dataoff, protocol,
				     csum_sub(skb->csum,
					      skb_checksum(skb, 0,
							   dataoff, 0)))) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CHECKSUM_NONE:
		skb->csum = ~csum_unfold(
				csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr,
					     skb->len - dataoff,
					     protocol,
					     csum_sub(0,
						      skb_checksum(skb, 0,
								   dataoff, 0))));
		csum = __skb_checksum_complete(skb);
	पूर्ण
	वापस csum;
पूर्ण
EXPORT_SYMBOL(nf_ip6_checksum);

अटल __sum16 nf_ip6_checksum_partial(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
				       अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक len,
				       u8 protocol)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	__wsum hsum;
	__sum16 csum = 0;

	चयन (skb->ip_summed) अणु
	हाल CHECKSUM_COMPLETE:
		अगर (len == skb->len - dataoff)
			वापस nf_ip6_checksum(skb, hook, dataoff, protocol);
		fallthrough;
	हाल CHECKSUM_NONE:
		hsum = skb_checksum(skb, 0, dataoff, 0);
		skb->csum = ~csum_unfold(csum_ipv6_magic(&ip6h->saddr,
							 &ip6h->daddr,
							 skb->len - dataoff,
							 protocol,
							 csum_sub(0, hsum)));
		skb->ip_summed = CHECKSUM_NONE;
		वापस __skb_checksum_complete_head(skb, dataoff + len);
	पूर्ण
	वापस csum;
पूर्ण;

__sum16 nf_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
		    अचिन्हित पूर्णांक dataoff, u8 protocol,
		    अचिन्हित लघु family)
अणु
	__sum16 csum = 0;

	चयन (family) अणु
	हाल AF_INET:
		csum = nf_ip_checksum(skb, hook, dataoff, protocol);
		अवरोध;
	हाल AF_INET6:
		csum = nf_ip6_checksum(skb, hook, dataoff, protocol);
		अवरोध;
	पूर्ण

	वापस csum;
पूर्ण
EXPORT_SYMBOL_GPL(nf_checksum);

__sum16 nf_checksum_partial(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
			    अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक len,
			    u8 protocol, अचिन्हित लघु family)
अणु
	__sum16 csum = 0;

	चयन (family) अणु
	हाल AF_INET:
		csum = nf_ip_checksum_partial(skb, hook, dataoff, len,
					      protocol);
		अवरोध;
	हाल AF_INET6:
		csum = nf_ip6_checksum_partial(skb, hook, dataoff, len,
					       protocol);
		अवरोध;
	पूर्ण

	वापस csum;
पूर्ण
EXPORT_SYMBOL_GPL(nf_checksum_partial);

पूर्णांक nf_route(काष्ठा net *net, काष्ठा dst_entry **dst, काष्ठा flowi *fl,
	     bool strict, अचिन्हित लघु family)
अणु
	स्थिर काष्ठा nf_ipv6_ops *v6ops __maybe_unused;
	पूर्णांक ret = 0;

	चयन (family) अणु
	हाल AF_INET:
		ret = nf_ip_route(net, dst, fl, strict);
		अवरोध;
	हाल AF_INET6:
		ret = nf_ip6_route(net, dst, fl, strict);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_route);

अटल पूर्णांक nf_ip_reroute(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_queue_entry *entry)
अणु
#अगर_घोषित CONFIG_INET
	स्थिर काष्ठा ip_rt_info *rt_info = nf_queue_entry_reroute(entry);

	अगर (entry->state.hook == NF_INET_LOCAL_OUT) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		अगर (!(iph->tos == rt_info->tos &&
		      skb->mark == rt_info->mark &&
		      iph->daddr == rt_info->daddr &&
		      iph->saddr == rt_info->saddr))
			वापस ip_route_me_harder(entry->state.net, entry->state.sk,
						  skb, RTN_UNSPEC);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक nf_reroute(काष्ठा sk_buff *skb, काष्ठा nf_queue_entry *entry)
अणु
	स्थिर काष्ठा nf_ipv6_ops *v6ops;
	पूर्णांक ret = 0;

	चयन (entry->state.pf) अणु
	हाल AF_INET:
		ret = nf_ip_reroute(skb, entry);
		अवरोध;
	हाल AF_INET6:
		v6ops = rcu_dereference(nf_ipv6_ops);
		अगर (v6ops)
			ret = v6ops->reroute(skb, entry);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
