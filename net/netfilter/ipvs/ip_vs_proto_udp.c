<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_proto_udp.c:	UDP load balancing support क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * Changes:     Hans Schillstrom <hans.schillstrom@ericsson.com>
 *              Network name space (netns) aware.
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/udp.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/ip_vs.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_checksum.h>

अटल पूर्णांक
udp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp);

अटल पूर्णांक
udp_conn_schedule(काष्ठा netns_ipvs *ipvs, पूर्णांक af, काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_proto_data *pd,
		  पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_service *svc;
	काष्ठा udphdr _udph, *uh;
	__be16 _ports[2], *ports = शून्य;

	अगर (likely(!ip_vs_iph_icmp(iph))) अणु
		/* IPv6 fragments, only first fragment will hit this */
		uh = skb_header_poपूर्णांकer(skb, iph->len, माप(_udph), &_udph);
		अगर (uh)
			ports = &uh->source;
	पूर्ण अन्यथा अणु
		ports = skb_header_poपूर्णांकer(
			skb, iph->len, माप(_ports), &_ports);
	पूर्ण

	अगर (!ports) अणु
		*verdict = NF_DROP;
		वापस 0;
	पूर्ण

	अगर (likely(!ip_vs_iph_inverse(iph)))
		svc = ip_vs_service_find(ipvs, af, skb->mark, iph->protocol,
					 &iph->daddr, ports[1]);
	अन्यथा
		svc = ip_vs_service_find(ipvs, af, skb->mark, iph->protocol,
					 &iph->saddr, ports[0]);

	अगर (svc) अणु
		पूर्णांक ignored;

		अगर (ip_vs_todrop(ipvs)) अणु
			/*
			 * It seems that we are very loaded.
			 * We have to drop this packet :(
			 */
			*verdict = NF_DROP;
			वापस 0;
		पूर्ण

		/*
		 * Let the भव server select a real server क्रम the
		 * incoming connection, and create a connection entry.
		 */
		*cpp = ip_vs_schedule(svc, skb, pd, &ignored, iph);
		अगर (!*cpp && ignored <= 0) अणु
			अगर (!ignored)
				*verdict = ip_vs_leave(svc, skb, pd, iph);
			अन्यथा
				*verdict = NF_DROP;
			वापस 0;
		पूर्ण
	पूर्ण
	/* NF_ACCEPT */
	वापस 1;
पूर्ण


अटल अंतरभूत व्योम
udp_fast_csum_update(पूर्णांक af, काष्ठा udphdr *uhdr,
		     स्थिर जोड़ nf_inet_addr *oldip,
		     स्थिर जोड़ nf_inet_addr *newip,
		     __be16 oldport, __be16 newport)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		uhdr->check =
			csum_fold(ip_vs_check_dअगरf16(oldip->ip6, newip->ip6,
					 ip_vs_check_dअगरf2(oldport, newport,
						~csum_unfold(uhdr->check))));
	अन्यथा
#पूर्ण_अगर
		uhdr->check =
			csum_fold(ip_vs_check_dअगरf4(oldip->ip, newip->ip,
					 ip_vs_check_dअगरf2(oldport, newport,
						~csum_unfold(uhdr->check))));
	अगर (!uhdr->check)
		uhdr->check = CSUM_MANGLED_0;
पूर्ण

अटल अंतरभूत व्योम
udp_partial_csum_update(पूर्णांक af, काष्ठा udphdr *uhdr,
		     स्थिर जोड़ nf_inet_addr *oldip,
		     स्थिर जोड़ nf_inet_addr *newip,
		     __be16 oldlen, __be16 newlen)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		uhdr->check =
			~csum_fold(ip_vs_check_dअगरf16(oldip->ip6, newip->ip6,
					 ip_vs_check_dअगरf2(oldlen, newlen,
						csum_unfold(uhdr->check))));
	अन्यथा
#पूर्ण_अगर
	uhdr->check =
		~csum_fold(ip_vs_check_dअगरf4(oldip->ip, newip->ip,
				ip_vs_check_dअगरf2(oldlen, newlen,
						csum_unfold(uhdr->check))));
पूर्ण


INसूचीECT_CALLABLE_SCOPE पूर्णांक
udp_snat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा udphdr *udph;
	अचिन्हित पूर्णांक udphoff = iph->len;
	bool payload_csum = false;
	पूर्णांक oldlen;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर
	oldlen = skb->len - udphoff;

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, udphoff + माप(*udph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!udp_csum_check(cp->af, skb, pp))
			वापस 0;

		/*
		 *	Call application helper अगर needed
		 */
		अगर (!(ret = ip_vs_app_pkt_out(cp, skb, iph)))
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 1)
			oldlen = skb->len - udphoff;
		अन्यथा
			payload_csum = true;
	पूर्ण

	udph = (व्योम *)skb_network_header(skb) + udphoff;
	udph->source = cp->vport;

	/*
	 *	Adjust UDP checksums
	 */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		udp_partial_csum_update(cp->af, udph, &cp->daddr, &cp->vaddr,
					htons(oldlen),
					htons(skb->len - udphoff));
	पूर्ण अन्यथा अगर (!payload_csum && (udph->check != 0)) अणु
		/* Only port and addr are changed, करो fast csum update */
		udp_fast_csum_update(cp->af, udph, &cp->daddr, &cp->vaddr,
				     cp->dport, cp->vport);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSARY : CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		/* full checksum calculation */
		udph->check = 0;
		skb->csum = skb_checksum(skb, udphoff, skb->len - udphoff, 0);
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->vaddr.in6,
						      &cp->caddr.in6,
						      skb->len - udphoff,
						      cp->protocol, skb->csum);
		अन्यथा
#पूर्ण_अगर
			udph->check = csum_tcpudp_magic(cp->vaddr.ip,
							cp->caddr.ip,
							skb->len - udphoff,
							cp->protocol,
							skb->csum);
		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		IP_VS_DBG(11, "O-pkt: %s O-csum=%d (+%zd)\n",
			  pp->name, udph->check,
			  (अक्षर*)&(udph->check) - (अक्षर*)udph);
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक
udp_dnat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा udphdr *udph;
	अचिन्हित पूर्णांक udphoff = iph->len;
	bool payload_csum = false;
	पूर्णांक oldlen;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर
	oldlen = skb->len - udphoff;

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, udphoff + माप(*udph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!udp_csum_check(cp->af, skb, pp))
			वापस 0;

		/*
		 *	Attempt ip_vs_app call.
		 *	It will fix ip_vs_conn
		 */
		अगर (!(ret = ip_vs_app_pkt_in(cp, skb, iph)))
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 1)
			oldlen = skb->len - udphoff;
		अन्यथा
			payload_csum = true;
	पूर्ण

	udph = (व्योम *)skb_network_header(skb) + udphoff;
	udph->dest = cp->dport;

	/*
	 *	Adjust UDP checksums
	 */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		udp_partial_csum_update(cp->af, udph, &cp->vaddr, &cp->daddr,
					htons(oldlen),
					htons(skb->len - udphoff));
	पूर्ण अन्यथा अगर (!payload_csum && (udph->check != 0)) अणु
		/* Only port and addr are changed, करो fast csum update */
		udp_fast_csum_update(cp->af, udph, &cp->vaddr, &cp->daddr,
				     cp->vport, cp->dport);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSARY : CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		/* full checksum calculation */
		udph->check = 0;
		skb->csum = skb_checksum(skb, udphoff, skb->len - udphoff, 0);
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->caddr.in6,
						      &cp->daddr.in6,
						      skb->len - udphoff,
						      cp->protocol, skb->csum);
		अन्यथा
#पूर्ण_अगर
			udph->check = csum_tcpudp_magic(cp->caddr.ip,
							cp->daddr.ip,
							skb->len - udphoff,
							cp->protocol,
							skb->csum);
		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक
udp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp)
अणु
	काष्ठा udphdr _udph, *uh;
	अचिन्हित पूर्णांक udphoff;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		udphoff = माप(काष्ठा ipv6hdr);
	अन्यथा
#पूर्ण_अगर
		udphoff = ip_hdrlen(skb);

	uh = skb_header_poपूर्णांकer(skb, udphoff, माप(_udph), &_udph);
	अगर (uh == शून्य)
		वापस 0;

	अगर (uh->check != 0) अणु
		चयन (skb->ip_summed) अणु
		हाल CHECKSUM_NONE:
			skb->csum = skb_checksum(skb, udphoff,
						 skb->len - udphoff, 0);
			fallthrough;
		हाल CHECKSUM_COMPLETE:
#अगर_घोषित CONFIG_IP_VS_IPV6
			अगर (af == AF_INET6) अणु
				अगर (csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						    &ipv6_hdr(skb)->daddr,
						    skb->len - udphoff,
						    ipv6_hdr(skb)->nexthdr,
						    skb->csum)) अणु
					IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
							 "Failed checksum for");
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा
#पूर्ण_अगर
				अगर (csum_tcpudp_magic(ip_hdr(skb)->saddr,
						      ip_hdr(skb)->daddr,
						      skb->len - udphoff,
						      ip_hdr(skb)->protocol,
						      skb->csum)) अणु
					IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
							 "Failed checksum for");
					वापस 0;
				पूर्ण
			अवरोध;
		शेष:
			/* No need to checksum. */
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत __u16 udp_app_hashkey(__be16 port)
अणु
	वापस (((__क्रमce u16)port >> UDP_APP_TAB_BITS) ^ (__क्रमce u16)port)
		& UDP_APP_TAB_MASK;
पूर्ण


अटल पूर्णांक udp_रेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_app *i;
	__u16 hash;
	__be16 port = inc->port;
	पूर्णांक ret = 0;
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);

	hash = udp_app_hashkey(port);

	list_क्रम_each_entry(i, &ipvs->udp_apps[hash], p_list) अणु
		अगर (i->port == port) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_rcu(&inc->p_list, &ipvs->udp_apps[hash]);
	atomic_inc(&pd->appcnt);

  out:
	वापस ret;
पूर्ण


अटल व्योम
udp_unरेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_UDP);

	atomic_dec(&pd->appcnt);
	list_del_rcu(&inc->p_list);
पूर्ण


अटल पूर्णांक udp_app_conn_bind(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा netns_ipvs *ipvs = cp->ipvs;
	पूर्णांक hash;
	काष्ठा ip_vs_app *inc;
	पूर्णांक result = 0;

	/* Default binding: bind app only क्रम NAT */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		वापस 0;

	/* Lookup application incarnations and bind the right one */
	hash = udp_app_hashkey(cp->vport);

	list_क्रम_each_entry_rcu(inc, &ipvs->udp_apps[hash], p_list) अणु
		अगर (inc->port == cp->vport) अणु
			अगर (unlikely(!ip_vs_app_inc_get(inc)))
				अवरोध;

			IP_VS_DBG_BUF(9, "%s(): Binding conn %s:%u->"
				      "%s:%u to app %s on port %u\n",
				      __func__,
				      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
				      ntohs(cp->cport),
				      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
				      ntohs(cp->vport),
				      inc->name, ntohs(inc->port));

			cp->app = inc;
			अगर (inc->init_conn)
				result = inc->init_conn(inc, cp);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण


अटल स्थिर पूर्णांक udp_समयouts[IP_VS_UDP_S_LAST+1] = अणु
	[IP_VS_UDP_S_NORMAL]		=	5*60*HZ,
	[IP_VS_UDP_S_LAST]		=	2*HZ,
पूर्ण;

अटल स्थिर अक्षर *स्थिर udp_state_name_table[IP_VS_UDP_S_LAST+1] = अणु
	[IP_VS_UDP_S_NORMAL]		=	"UDP",
	[IP_VS_UDP_S_LAST]		=	"BUG!",
पूर्ण;

अटल स्थिर अक्षर * udp_state_name(पूर्णांक state)
अणु
	अगर (state >= IP_VS_UDP_S_LAST)
		वापस "ERR!";
	वापस udp_state_name_table[state] ? udp_state_name_table[state] : "?";
पूर्ण

अटल व्योम
udp_state_transition(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
		     स्थिर काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_proto_data *pd)
अणु
	अगर (unlikely(!pd)) अणु
		pr_err("UDP no ns data\n");
		वापस;
	पूर्ण

	cp->समयout = pd->समयout_table[IP_VS_UDP_S_NORMAL];
	अगर (direction == IP_VS_सूची_OUTPUT)
		ip_vs_control_assure_ct(cp);
पूर्ण

अटल पूर्णांक __udp_init(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	ip_vs_init_hash_table(ipvs->udp_apps, UDP_APP_TAB_SIZE);
	pd->समयout_table = ip_vs_create_समयout_table((पूर्णांक *)udp_समयouts,
							माप(udp_समयouts));
	अगर (!pd->समयout_table)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __udp_निकास(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	kमुक्त(pd->समयout_table);
पूर्ण


काष्ठा ip_vs_protocol ip_vs_protocol_udp = अणु
	.name =			"UDP",
	.protocol =		IPPROTO_UDP,
	.num_states =		IP_VS_UDP_S_LAST,
	.करोnt_defrag =		0,
	.init =			शून्य,
	.निकास =			शून्य,
	.init_netns =		__udp_init,
	.निकास_netns =		__udp_निकास,
	.conn_schedule =	udp_conn_schedule,
	.conn_in_get =		ip_vs_conn_in_get_proto,
	.conn_out_get =		ip_vs_conn_out_get_proto,
	.snat_handler =		udp_snat_handler,
	.dnat_handler =		udp_dnat_handler,
	.state_transition =	udp_state_transition,
	.state_name =		udp_state_name,
	.रेजिस्टर_app =		udp_रेजिस्टर_app,
	.unरेजिस्टर_app =	udp_unरेजिस्टर_app,
	.app_conn_bind =	udp_app_conn_bind,
	.debug_packet =		ip_vs_tcpudp_debug_packet,
	.समयout_change =	शून्य,
पूर्ण;
