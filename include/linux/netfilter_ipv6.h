<शैली गुरु>
/* IPv6-specअगरic defines क्रम netfilter. 
 * (C)1998 Rusty Russell -- This code is GPL.
 * (C)1999 David Jeffery
 *   this header was blatantly ripped from netfilter_ipv4.h
 *   it's amazing what adding a bunch of 6s can करो =8^)
 */
#अगर_अघोषित __LINUX_IP6_NETFILTER_H
#घोषणा __LINUX_IP6_NETFILTER_H

#समावेश <uapi/linux/netfilter_ipv6.h>
#समावेश <net/tcp.h>

/* Check क्रम an extension */
अटल अंतरभूत पूर्णांक
nf_ip6_ext_hdr(u8 nexthdr)
अणु	वापस (nexthdr == IPPROTO_HOPOPTS) ||
	       (nexthdr == IPPROTO_ROUTING) ||
	       (nexthdr == IPPROTO_FRAGMENT) ||
	       (nexthdr == IPPROTO_ESP) ||
	       (nexthdr == IPPROTO_AH) ||
	       (nexthdr == IPPROTO_NONE) ||
	       (nexthdr == IPPROTO_DSTOPTS);
पूर्ण

/* Extra routing may needed on local out, as the QUEUE target never वापसs
 * control to the table.
 */
काष्ठा ip6_rt_info अणु
	काष्ठा in6_addr daddr;
	काष्ठा in6_addr saddr;
	u_पूर्णांक32_t mark;
पूर्ण;

काष्ठा nf_queue_entry;
काष्ठा nf_bridge_frag_data;

/*
 * Hook functions क्रम ipv6 to allow xt_* modules to be built-in even
 * अगर IPv6 is a module.
 */
काष्ठा nf_ipv6_ops अणु
#अगर IS_MODULE(CONFIG_IPV6)
	पूर्णांक (*chk_addr)(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			स्थिर काष्ठा net_device *dev, पूर्णांक strict);
	पूर्णांक (*route_me_harder)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक (*dev_get_saddr)(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा in6_addr *daddr, अचिन्हित पूर्णांक srcprefs,
		       काष्ठा in6_addr *saddr);
	पूर्णांक (*route)(काष्ठा net *net, काष्ठा dst_entry **dst, काष्ठा flowi *fl,
		     bool strict);
	u32 (*cookie_init_sequence)(स्थिर काष्ठा ipv6hdr *iph,
				    स्थिर काष्ठा tcphdr *th, u16 *mssp);
	पूर्णांक (*cookie_v6_check)(स्थिर काष्ठा ipv6hdr *iph,
			       स्थिर काष्ठा tcphdr *th, __u32 cookie);
#पूर्ण_अगर
	व्योम (*route_input)(काष्ठा sk_buff *skb);
	पूर्णांक (*fragment)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
			पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *));
	पूर्णांक (*reroute)(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_queue_entry *entry);
#अगर IS_MODULE(CONFIG_IPV6)
	पूर्णांक (*br_fragment)(काष्ठा net *net, काष्ठा sock *sk,
			   काष्ठा sk_buff *skb,
			   काष्ठा nf_bridge_frag_data *data,
			   पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
					 स्थिर काष्ठा nf_bridge_frag_data *data,
					 काष्ठा sk_buff *));
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_NETFILTER
#समावेश <net/addrconf.h>

बाह्य स्थिर काष्ठा nf_ipv6_ops __rcu *nf_ipv6_ops;
अटल अंतरभूत स्थिर काष्ठा nf_ipv6_ops *nf_get_ipv6_ops(व्योम)
अणु
	वापस rcu_dereference(nf_ipv6_ops);
पूर्ण

अटल अंतरभूत पूर्णांक nf_ipv6_chk_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
				   स्थिर काष्ठा net_device *dev, पूर्णांक strict)
अणु
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (!v6_ops)
		वापस 1;

	वापस v6_ops->chk_addr(net, addr, dev, strict);
#या_अगर IS_BUILTIN(CONFIG_IPV6)
	वापस ipv6_chk_addr(net, addr, dev, strict);
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

पूर्णांक __nf_ip6_route(काष्ठा net *net, काष्ठा dst_entry **dst,
			       काष्ठा flowi *fl, bool strict);

अटल अंतरभूत पूर्णांक nf_ip6_route(काष्ठा net *net, काष्ठा dst_entry **dst,
			       काष्ठा flowi *fl, bool strict)
अणु
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6ops = nf_get_ipv6_ops();

	अगर (v6ops)
		वापस v6ops->route(net, dst, fl, strict);

	वापस -EHOSTUNREACH;
#पूर्ण_अगर
#अगर IS_BUILTIN(CONFIG_IPV6)
	वापस __nf_ip6_route(net, dst, fl, strict);
#अन्यथा
	वापस -EHOSTUNREACH;
#पूर्ण_अगर
पूर्ण

#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>

पूर्णांक br_ip6_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		    काष्ठा nf_bridge_frag_data *data,
		    पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
				  स्थिर काष्ठा nf_bridge_frag_data *data,
				  काष्ठा sk_buff *));

अटल अंतरभूत पूर्णांक nf_br_ip6_fragment(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb,
				     काष्ठा nf_bridge_frag_data *data,
				     पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
						   स्थिर काष्ठा nf_bridge_frag_data *data,
						   काष्ठा sk_buff *))
अणु
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (!v6_ops)
		वापस 1;

	वापस v6_ops->br_fragment(net, sk, skb, data, output);
#या_अगर IS_BUILTIN(CONFIG_IPV6)
	वापस br_ip6_fragment(net, sk, skb, data, output);
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

पूर्णांक ip6_route_me_harder(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक nf_ip6_route_me_harder(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (!v6_ops)
		वापस -EHOSTUNREACH;

	वापस v6_ops->route_me_harder(net, sk, skb);
#या_अगर IS_BUILTIN(CONFIG_IPV6)
	वापस ip6_route_me_harder(net, sk, skb);
#अन्यथा
	वापस -EHOSTUNREACH;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 nf_ipv6_cookie_init_sequence(स्थिर काष्ठा ipv6hdr *iph,
					       स्थिर काष्ठा tcphdr *th,
					       u16 *mssp)
अणु
#अगर IS_ENABLED(CONFIG_SYN_COOKIES)
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (v6_ops)
		वापस v6_ops->cookie_init_sequence(iph, th, mssp);
#या_अगर IS_BUILTIN(CONFIG_IPV6)
	वापस __cookie_v6_init_sequence(iph, th, mssp);
#पूर्ण_अगर
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nf_cookie_v6_check(स्थिर काष्ठा ipv6hdr *iph,
				     स्थिर काष्ठा tcphdr *th, __u32 cookie)
अणु
#अगर IS_ENABLED(CONFIG_SYN_COOKIES)
#अगर IS_MODULE(CONFIG_IPV6)
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (v6_ops)
		वापस v6_ops->cookie_v6_check(iph, th, cookie);
#या_अगर IS_BUILTIN(CONFIG_IPV6)
	वापस __cookie_v6_check(iph, th, cookie);
#पूर्ण_अगर
#पूर्ण_अगर
	वापस 0;
पूर्ण

__sum16 nf_ip6_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
			अचिन्हित पूर्णांक dataoff, u_पूर्णांक8_t protocol);

पूर्णांक ipv6_netfilter_init(व्योम);
व्योम ipv6_netfilter_fini(व्योम);

#अन्यथा /* CONFIG_NETFILTER */
अटल अंतरभूत पूर्णांक ipv6_netfilter_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ipv6_netfilter_fini(व्योम) अणु वापस; पूर्ण
अटल अंतरभूत स्थिर काष्ठा nf_ipv6_ops *nf_get_ipv6_ops(व्योम) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर /* CONFIG_NETFILTER */

#पूर्ण_अगर /*__LINUX_IP6_NETFILTER_H*/
