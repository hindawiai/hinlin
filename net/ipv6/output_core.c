<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv6 library code, needed by अटल components when full IPv6 support is
 * not configured or अटल.  These functions are needed by GSO/GRO implementation.
 */
#समावेश <linux/export.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/addrconf.h>
#समावेश <net/secure_seq.h>
#समावेश <linux/netfilter.h>

अटल u32 __ipv6_select_ident(काष्ठा net *net,
			       स्थिर काष्ठा in6_addr *dst,
			       स्थिर काष्ठा in6_addr *src)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr dst;
		काष्ठा in6_addr src;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.dst = *dst,
		.src = *src,
	पूर्ण;
	u32 hash, id;

	/* Note the following code is not safe, but this is okay. */
	अगर (unlikely(siphash_key_is_zero(&net->ipv4.ip_id_key)))
		get_अक्रमom_bytes(&net->ipv4.ip_id_key,
				 माप(net->ipv4.ip_id_key));

	hash = siphash(&combined, माप(combined), &net->ipv4.ip_id_key);

	/* Treat id of 0 as unset and अगर we get 0 back from ip_idents_reserve,
	 * set the hight order instead thus minimizing possible future
	 * collisions.
	 */
	id = ip_idents_reserve(hash, 1);
	अगर (unlikely(!id))
		id = 1 << 31;

	वापस id;
पूर्ण

/* This function exists only क्रम tap drivers that must support broken
 * clients requesting UFO without specअगरying an IPv6 fragment ID.
 *
 * This is similar to ipv6_select_ident() but we use an independent hash
 * seed to limit inक्रमmation leakage.
 *
 * The network header must be set beक्रमe calling this.
 */
__be32 ipv6_proxy_select_ident(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा in6_addr buf[2];
	काष्ठा in6_addr *addrs;
	u32 id;

	addrs = skb_header_poपूर्णांकer(skb,
				   skb_network_offset(skb) +
				   दुरत्व(काष्ठा ipv6hdr, saddr),
				   माप(buf), buf);
	अगर (!addrs)
		वापस 0;

	id = __ipv6_select_ident(net, &addrs[1], &addrs[0]);
	वापस htonl(id);
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_proxy_select_ident);

__be32 ipv6_select_ident(काष्ठा net *net,
			 स्थिर काष्ठा in6_addr *daddr,
			 स्थिर काष्ठा in6_addr *saddr)
अणु
	u32 id;

	id = __ipv6_select_ident(net, daddr, saddr);
	वापस htonl(id);
पूर्ण
EXPORT_SYMBOL(ipv6_select_ident);

पूर्णांक ip6_find_1stfragopt(काष्ठा sk_buff *skb, u8 **nexthdr)
अणु
	अचिन्हित पूर्णांक offset = माप(काष्ठा ipv6hdr);
	अचिन्हित पूर्णांक packet_len = skb_tail_poपूर्णांकer(skb) -
		skb_network_header(skb);
	पूर्णांक found_rhdr = 0;
	*nexthdr = &ipv6_hdr(skb)->nexthdr;

	जबतक (offset <= packet_len) अणु
		काष्ठा ipv6_opt_hdr *exthdr;

		चयन (**nexthdr) अणु

		हाल NEXTHDR_HOP:
			अवरोध;
		हाल NEXTHDR_ROUTING:
			found_rhdr = 1;
			अवरोध;
		हाल NEXTHDR_DEST:
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
			अगर (ipv6_find_tlv(skb, offset, IPV6_TLV_HAO) >= 0)
				अवरोध;
#पूर्ण_अगर
			अगर (found_rhdr)
				वापस offset;
			अवरोध;
		शेष:
			वापस offset;
		पूर्ण

		अगर (offset + माप(काष्ठा ipv6_opt_hdr) > packet_len)
			वापस -EINVAL;

		exthdr = (काष्ठा ipv6_opt_hdr *)(skb_network_header(skb) +
						 offset);
		offset += ipv6_optlen(exthdr);
		अगर (offset > IPV6_MAXPLEN)
			वापस -EINVAL;
		*nexthdr = &exthdr->nexthdr;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ip6_find_1stfragopt);

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक ip6_dst_hoplimit(काष्ठा dst_entry *dst)
अणु
	पूर्णांक hoplimit = dst_metric_raw(dst, RTAX_HOPLIMIT);
	अगर (hoplimit == 0) अणु
		काष्ठा net_device *dev = dst->dev;
		काष्ठा inet6_dev *idev;

		rcu_पढ़ो_lock();
		idev = __in6_dev_get(dev);
		अगर (idev)
			hoplimit = idev->cnf.hop_limit;
		अन्यथा
			hoplimit = dev_net(dev)->ipv6.devconf_all->hop_limit;
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस hoplimit;
पूर्ण
EXPORT_SYMBOL(ip6_dst_hoplimit);
#पूर्ण_अगर

पूर्णांक __ip6_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len;

	len = skb->len - माप(काष्ठा ipv6hdr);
	अगर (len > IPV6_MAXPLEN)
		len = 0;
	ipv6_hdr(skb)->payload_len = htons(len);
	IP6CB(skb)->nhoff = दुरत्व(काष्ठा ipv6hdr, nexthdr);

	/* अगर egress device is enslaved to an L3 master device pass the
	 * skb to its handler क्रम processing
	 */
	skb = l3mdev_ip6_out(sk, skb);
	अगर (unlikely(!skb))
		वापस 0;

	skb->protocol = htons(ETH_P_IPV6);

	वापस nf_hook(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
		       net, sk, skb, शून्य, skb_dst(skb)->dev,
		       dst_output);
पूर्ण
EXPORT_SYMBOL_GPL(__ip6_local_out);

पूर्णांक ip6_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = __ip6_local_out(net, sk, skb);
	अगर (likely(err == 1))
		err = dst_output(net, sk, skb);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_local_out);
