<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_proto_tcp.c:	TCP load balancing support क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * Changes:     Hans Schillstrom <hans.schillstrom@ericsson.com>
 *
 *              Network name space (netns) aware.
 *              Global data moved to netns i.e काष्ठा netns_ipvs
 *              tcp_समयouts table has copy per netns in a hash table per
 *              protocol ip_vs_proto_data and is handled by netns
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>                  /* क्रम tcphdr */
#समावेश <net/ip.h>
#समावेश <net/tcp.h>                    /* क्रम csum_tcpudp_magic */
#समावेश <net/ip6_checksum.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/ip_vs.h>

अटल पूर्णांक
tcp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp);

अटल पूर्णांक
tcp_conn_schedule(काष्ठा netns_ipvs *ipvs, पूर्णांक af, काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_proto_data *pd,
		  पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_service *svc;
	काष्ठा tcphdr _tcph, *th;
	__be16 _ports[2], *ports = शून्य;

	/* In the event of icmp, we're only guaranteed to have the first 8
	 * bytes of the transport header, so we only check the rest of the
	 * TCP packet क्रम non-ICMP packets
	 */
	अगर (likely(!ip_vs_iph_icmp(iph))) अणु
		th = skb_header_poपूर्णांकer(skb, iph->len, माप(_tcph), &_tcph);
		अगर (th) अणु
			अगर (th->rst || !(sysctl_sloppy_tcp(ipvs) || th->syn))
				वापस 1;
			ports = &th->source;
		पूर्ण
	पूर्ण अन्यथा अणु
		ports = skb_header_poपूर्णांकer(
			skb, iph->len, माप(_ports), &_ports);
	पूर्ण

	अगर (!ports) अणु
		*verdict = NF_DROP;
		वापस 0;
	पूर्ण

	/* No !th->ack check to allow scheduling on SYN+ACK क्रम Active FTP */

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
tcp_fast_csum_update(पूर्णांक af, काष्ठा tcphdr *tcph,
		     स्थिर जोड़ nf_inet_addr *oldip,
		     स्थिर जोड़ nf_inet_addr *newip,
		     __be16 oldport, __be16 newport)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		tcph->check =
			csum_fold(ip_vs_check_dअगरf16(oldip->ip6, newip->ip6,
					 ip_vs_check_dअगरf2(oldport, newport,
						~csum_unfold(tcph->check))));
	अन्यथा
#पूर्ण_अगर
	tcph->check =
		csum_fold(ip_vs_check_dअगरf4(oldip->ip, newip->ip,
				 ip_vs_check_dअगरf2(oldport, newport,
						~csum_unfold(tcph->check))));
पूर्ण


अटल अंतरभूत व्योम
tcp_partial_csum_update(पूर्णांक af, काष्ठा tcphdr *tcph,
		     स्थिर जोड़ nf_inet_addr *oldip,
		     स्थिर जोड़ nf_inet_addr *newip,
		     __be16 oldlen, __be16 newlen)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		tcph->check =
			~csum_fold(ip_vs_check_dअगरf16(oldip->ip6, newip->ip6,
					 ip_vs_check_dअगरf2(oldlen, newlen,
						csum_unfold(tcph->check))));
	अन्यथा
#पूर्ण_अगर
	tcph->check =
		~csum_fold(ip_vs_check_dअगरf4(oldip->ip, newip->ip,
				ip_vs_check_dअगरf2(oldlen, newlen,
						csum_unfold(tcph->check))));
पूर्ण


INसूचीECT_CALLABLE_SCOPE पूर्णांक
tcp_snat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा tcphdr *tcph;
	अचिन्हित पूर्णांक tcphoff = iph->len;
	bool payload_csum = false;
	पूर्णांक oldlen;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर
	oldlen = skb->len - tcphoff;

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, tcphoff + माप(*tcph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!tcp_csum_check(cp->af, skb, pp))
			वापस 0;

		/* Call application helper अगर needed */
		अगर (!(ret = ip_vs_app_pkt_out(cp, skb, iph)))
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 1)
			oldlen = skb->len - tcphoff;
		अन्यथा
			payload_csum = true;
	पूर्ण

	tcph = (व्योम *)skb_network_header(skb) + tcphoff;
	tcph->source = cp->vport;

	/* Adjust TCP checksums */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		tcp_partial_csum_update(cp->af, tcph, &cp->daddr, &cp->vaddr,
					htons(oldlen),
					htons(skb->len - tcphoff));
	पूर्ण अन्यथा अगर (!payload_csum) अणु
		/* Only port and addr are changed, करो fast csum update */
		tcp_fast_csum_update(cp->af, tcph, &cp->daddr, &cp->vaddr,
				     cp->dport, cp->vport);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSARY : CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		/* full checksum calculation */
		tcph->check = 0;
		skb->csum = skb_checksum(skb, tcphoff, skb->len - tcphoff, 0);
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			tcph->check = csum_ipv6_magic(&cp->vaddr.in6,
						      &cp->caddr.in6,
						      skb->len - tcphoff,
						      cp->protocol, skb->csum);
		अन्यथा
#पूर्ण_अगर
			tcph->check = csum_tcpudp_magic(cp->vaddr.ip,
							cp->caddr.ip,
							skb->len - tcphoff,
							cp->protocol,
							skb->csum);
		skb->ip_summed = CHECKSUM_UNNECESSARY;

		IP_VS_DBG(11, "O-pkt: %s O-csum=%d (+%zd)\n",
			  pp->name, tcph->check,
			  (अक्षर*)&(tcph->check) - (अक्षर*)tcph);
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक
tcp_dnat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा tcphdr *tcph;
	अचिन्हित पूर्णांक tcphoff = iph->len;
	bool payload_csum = false;
	पूर्णांक oldlen;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर
	oldlen = skb->len - tcphoff;

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, tcphoff + माप(*tcph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!tcp_csum_check(cp->af, skb, pp))
			वापस 0;

		/*
		 *	Attempt ip_vs_app call.
		 *	It will fix ip_vs_conn and iph ack_seq stuff
		 */
		अगर (!(ret = ip_vs_app_pkt_in(cp, skb, iph)))
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 1)
			oldlen = skb->len - tcphoff;
		अन्यथा
			payload_csum = true;
	पूर्ण

	tcph = (व्योम *)skb_network_header(skb) + tcphoff;
	tcph->dest = cp->dport;

	/*
	 *	Adjust TCP checksums
	 */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		tcp_partial_csum_update(cp->af, tcph, &cp->vaddr, &cp->daddr,
					htons(oldlen),
					htons(skb->len - tcphoff));
	पूर्ण अन्यथा अगर (!payload_csum) अणु
		/* Only port and addr are changed, करो fast csum update */
		tcp_fast_csum_update(cp->af, tcph, &cp->vaddr, &cp->daddr,
				     cp->vport, cp->dport);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = cp->app ?
					 CHECKSUM_UNNECESSARY : CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		/* full checksum calculation */
		tcph->check = 0;
		skb->csum = skb_checksum(skb, tcphoff, skb->len - tcphoff, 0);
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (cp->af == AF_INET6)
			tcph->check = csum_ipv6_magic(&cp->caddr.in6,
						      &cp->daddr.in6,
						      skb->len - tcphoff,
						      cp->protocol, skb->csum);
		अन्यथा
#पूर्ण_अगर
			tcph->check = csum_tcpudp_magic(cp->caddr.ip,
							cp->daddr.ip,
							skb->len - tcphoff,
							cp->protocol,
							skb->csum);
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक
tcp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp)
अणु
	अचिन्हित पूर्णांक tcphoff;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		tcphoff = माप(काष्ठा ipv6hdr);
	अन्यथा
#पूर्ण_अगर
		tcphoff = ip_hdrlen(skb);

	चयन (skb->ip_summed) अणु
	हाल CHECKSUM_NONE:
		skb->csum = skb_checksum(skb, tcphoff, skb->len - tcphoff, 0);
		fallthrough;
	हाल CHECKSUM_COMPLETE:
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (af == AF_INET6) अणु
			अगर (csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
					    &ipv6_hdr(skb)->daddr,
					    skb->len - tcphoff,
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
					      skb->len - tcphoff,
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

	वापस 1;
पूर्ण


#घोषणा TCP_सूची_INPUT		0
#घोषणा TCP_सूची_OUTPUT		4
#घोषणा TCP_सूची_INPUT_ONLY	8

अटल स्थिर पूर्णांक tcp_state_off[IP_VS_सूची_LAST] = अणु
	[IP_VS_सूची_INPUT]		=	TCP_सूची_INPUT,
	[IP_VS_सूची_OUTPUT]		=	TCP_सूची_OUTPUT,
	[IP_VS_सूची_INPUT_ONLY]		=	TCP_सूची_INPUT_ONLY,
पूर्ण;

/*
 *	Timeout table[state]
 */
अटल स्थिर पूर्णांक tcp_समयouts[IP_VS_TCP_S_LAST+1] = अणु
	[IP_VS_TCP_S_NONE]		=	2*HZ,
	[IP_VS_TCP_S_ESTABLISHED]	=	15*60*HZ,
	[IP_VS_TCP_S_SYN_SENT]		=	2*60*HZ,
	[IP_VS_TCP_S_SYN_RECV]		=	1*60*HZ,
	[IP_VS_TCP_S_FIN_WAIT]		=	2*60*HZ,
	[IP_VS_TCP_S_TIME_WAIT]		=	2*60*HZ,
	[IP_VS_TCP_S_CLOSE]		=	10*HZ,
	[IP_VS_TCP_S_CLOSE_WAIT]	=	60*HZ,
	[IP_VS_TCP_S_LAST_ACK]		=	30*HZ,
	[IP_VS_TCP_S_LISTEN]		=	2*60*HZ,
	[IP_VS_TCP_S_SYNACK]		=	120*HZ,
	[IP_VS_TCP_S_LAST]		=	2*HZ,
पूर्ण;

अटल स्थिर अक्षर *स्थिर tcp_state_name_table[IP_VS_TCP_S_LAST+1] = अणु
	[IP_VS_TCP_S_NONE]		=	"NONE",
	[IP_VS_TCP_S_ESTABLISHED]	=	"ESTABLISHED",
	[IP_VS_TCP_S_SYN_SENT]		=	"SYN_SENT",
	[IP_VS_TCP_S_SYN_RECV]		=	"SYN_RECV",
	[IP_VS_TCP_S_FIN_WAIT]		=	"FIN_WAIT",
	[IP_VS_TCP_S_TIME_WAIT]		=	"TIME_WAIT",
	[IP_VS_TCP_S_CLOSE]		=	"CLOSE",
	[IP_VS_TCP_S_CLOSE_WAIT]	=	"CLOSE_WAIT",
	[IP_VS_TCP_S_LAST_ACK]		=	"LAST_ACK",
	[IP_VS_TCP_S_LISTEN]		=	"LISTEN",
	[IP_VS_TCP_S_SYNACK]		=	"SYNACK",
	[IP_VS_TCP_S_LAST]		=	"BUG!",
पूर्ण;

अटल स्थिर bool tcp_state_active_table[IP_VS_TCP_S_LAST] = अणु
	[IP_VS_TCP_S_NONE]		=	false,
	[IP_VS_TCP_S_ESTABLISHED]	=	true,
	[IP_VS_TCP_S_SYN_SENT]		=	true,
	[IP_VS_TCP_S_SYN_RECV]		=	true,
	[IP_VS_TCP_S_FIN_WAIT]		=	false,
	[IP_VS_TCP_S_TIME_WAIT]		=	false,
	[IP_VS_TCP_S_CLOSE]		=	false,
	[IP_VS_TCP_S_CLOSE_WAIT]	=	false,
	[IP_VS_TCP_S_LAST_ACK]		=	false,
	[IP_VS_TCP_S_LISTEN]		=	false,
	[IP_VS_TCP_S_SYNACK]		=	true,
पूर्ण;

#घोषणा sNO IP_VS_TCP_S_NONE
#घोषणा sES IP_VS_TCP_S_ESTABLISHED
#घोषणा sSS IP_VS_TCP_S_SYN_SENT
#घोषणा sSR IP_VS_TCP_S_SYN_RECV
#घोषणा sFW IP_VS_TCP_S_FIN_WAIT
#घोषणा sTW IP_VS_TCP_S_TIME_WAIT
#घोषणा sCL IP_VS_TCP_S_CLOSE
#घोषणा sCW IP_VS_TCP_S_CLOSE_WAIT
#घोषणा sLA IP_VS_TCP_S_LAST_ACK
#घोषणा sLI IP_VS_TCP_S_LISTEN
#घोषणा sSA IP_VS_TCP_S_SYNACK

काष्ठा tcp_states_t अणु
	पूर्णांक next_state[IP_VS_TCP_S_LAST];
पूर्ण;

अटल स्थिर अक्षर * tcp_state_name(पूर्णांक state)
अणु
	अगर (state >= IP_VS_TCP_S_LAST)
		वापस "ERR!";
	वापस tcp_state_name_table[state] ? tcp_state_name_table[state] : "?";
पूर्ण

अटल bool tcp_state_active(पूर्णांक state)
अणु
	अगर (state >= IP_VS_TCP_S_LAST)
		वापस false;
	वापस tcp_state_active_table[state];
पूर्ण

अटल काष्ठा tcp_states_t tcp_states[] = अणु
/*	INPUT */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSR, sES, sES, sSR, sSR, sSR, sSR, sSR, sSR, sSR, sSR पूर्णपूर्ण,
/*fin*/ अणुअणुsCL, sCW, sSS, sTW, sTW, sTW, sCL, sCW, sLA, sLI, sTW पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sES, sFW, sTW, sCL, sCW, sCL, sLI, sES पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sCL, sSR, sCL, sCL, sCL, sCL, sLA, sLI, sSR पूर्णपूर्ण,

/*	OUTPUT */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSS, sES, sSS, sSR, sSS, sSS, sSS, sSS, sSS, sLI, sSR पूर्णपूर्ण,
/*fin*/ अणुअणुsTW, sFW, sSS, sTW, sFW, sTW, sCL, sTW, sLA, sLI, sTW पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sES, sFW, sTW, sCL, sCW, sLA, sES, sES पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sSS, sCL, sCL, sTW, sCL, sCL, sCL, sCL, sCL पूर्णपूर्ण,

/*	INPUT-ONLY */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSR, sES, sES, sSR, sSR, sSR, sSR, sSR, sSR, sSR, sSR पूर्णपूर्ण,
/*fin*/ अणुअणुsCL, sFW, sSS, sTW, sFW, sTW, sCL, sCW, sLA, sLI, sTW पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sES, sFW, sTW, sCL, sCW, sCL, sLI, sES पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sCL, sSR, sCL, sCL, sCL, sCL, sLA, sLI, sCL पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा tcp_states_t tcp_states_करोs[] = अणु
/*	INPUT */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSR, sES, sES, sSR, sSR, sSR, sSR, sSR, sSR, sSR, sSA पूर्णपूर्ण,
/*fin*/ अणुअणुsCL, sCW, sSS, sTW, sTW, sTW, sCL, sCW, sLA, sLI, sSA पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sSR, sFW, sTW, sCL, sCW, sCL, sLI, sSA पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sCL, sSR, sCL, sCL, sCL, sCL, sLA, sLI, sCL पूर्णपूर्ण,

/*	OUTPUT */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSS, sES, sSS, sSA, sSS, sSS, sSS, sSS, sSS, sLI, sSA पूर्णपूर्ण,
/*fin*/ अणुअणुsTW, sFW, sSS, sTW, sFW, sTW, sCL, sTW, sLA, sLI, sTW पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sES, sFW, sTW, sCL, sCW, sLA, sES, sES पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sSS, sCL, sCL, sTW, sCL, sCL, sCL, sCL, sCL पूर्णपूर्ण,

/*	INPUT-ONLY */
/*        sNO, sES, sSS, sSR, sFW, sTW, sCL, sCW, sLA, sLI, sSA	*/
/*syn*/ अणुअणुsSA, sES, sES, sSR, sSA, sSA, sSA, sSA, sSA, sSA, sSA पूर्णपूर्ण,
/*fin*/ अणुअणुsCL, sFW, sSS, sTW, sFW, sTW, sCL, sCW, sLA, sLI, sTW पूर्णपूर्ण,
/*ack*/ अणुअणुsES, sES, sSS, sES, sFW, sTW, sCL, sCW, sCL, sLI, sES पूर्णपूर्ण,
/*rst*/ अणुअणुsCL, sCL, sCL, sSR, sCL, sCL, sCL, sCL, sLA, sLI, sCL पूर्णपूर्ण,
पूर्ण;

अटल व्योम tcp_समयout_change(काष्ठा ip_vs_proto_data *pd, पूर्णांक flags)
अणु
	पूर्णांक on = (flags & 1);		/* secure_tcp */

	/*
	** FIXME: change secure_tcp to independent sysctl var
	** or make it per-service or per-app because it is valid
	** क्रम most अगर not क्रम all of the applications. Something
	** like "capabilities" (flags) क्रम each object.
	*/
	pd->tcp_state_table = (on ? tcp_states_करोs : tcp_states);
पूर्ण

अटल अंतरभूत पूर्णांक tcp_state_idx(काष्ठा tcphdr *th)
अणु
	अगर (th->rst)
		वापस 3;
	अगर (th->syn)
		वापस 0;
	अगर (th->fin)
		वापस 1;
	अगर (th->ack)
		वापस 2;
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम
set_tcp_state(काष्ठा ip_vs_proto_data *pd, काष्ठा ip_vs_conn *cp,
	      पूर्णांक direction, काष्ठा tcphdr *th)
अणु
	पूर्णांक state_idx;
	पूर्णांक new_state = IP_VS_TCP_S_CLOSE;
	पूर्णांक state_off = tcp_state_off[direction];

	/*
	 *    Update state offset to INPUT_ONLY अगर necessary
	 *    or delete NO_OUTPUT flag अगर output packet detected
	 */
	अगर (cp->flags & IP_VS_CONN_F_NOOUTPUT) अणु
		अगर (state_off == TCP_सूची_OUTPUT)
			cp->flags &= ~IP_VS_CONN_F_NOOUTPUT;
		अन्यथा
			state_off = TCP_सूची_INPUT_ONLY;
	पूर्ण

	अगर ((state_idx = tcp_state_idx(th)) < 0) अणु
		IP_VS_DBG(8, "tcp_state_idx=%d!!!\n", state_idx);
		जाओ tcp_state_out;
	पूर्ण

	new_state =
		pd->tcp_state_table[state_off+state_idx].next_state[cp->state];

  tcp_state_out:
	अगर (new_state != cp->state) अणु
		काष्ठा ip_vs_dest *dest = cp->dest;

		IP_VS_DBG_BUF(8, "%s %s [%c%c%c%c] c:%s:%d v:%s:%d "
			      "d:%s:%d state: %s->%s conn->refcnt:%d\n",
			      pd->pp->name,
			      ((state_off == TCP_सूची_OUTPUT) ?
			       "output " : "input "),
			      th->syn ? 'S' : '.',
			      th->fin ? 'F' : '.',
			      th->ack ? 'A' : '.',
			      th->rst ? 'R' : '.',
			      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
			      ntohs(cp->cport),
			      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
			      ntohs(cp->vport),
			      IP_VS_DBG_ADDR(cp->daf, &cp->daddr),
			      ntohs(cp->dport),
			      tcp_state_name(cp->state),
			      tcp_state_name(new_state),
			      refcount_पढ़ो(&cp->refcnt));

		अगर (dest) अणु
			अगर (!(cp->flags & IP_VS_CONN_F_INACTIVE) &&
			    !tcp_state_active(new_state)) अणु
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
				cp->flags |= IP_VS_CONN_F_INACTIVE;
			पूर्ण अन्यथा अगर ((cp->flags & IP_VS_CONN_F_INACTIVE) &&
				   tcp_state_active(new_state)) अणु
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
				cp->flags &= ~IP_VS_CONN_F_INACTIVE;
			पूर्ण
		पूर्ण
		अगर (new_state == IP_VS_TCP_S_ESTABLISHED)
			ip_vs_control_assure_ct(cp);
	पूर्ण

	अगर (likely(pd))
		cp->समयout = pd->समयout_table[cp->state = new_state];
	अन्यथा	/* What to करो ? */
		cp->समयout = tcp_समयouts[cp->state = new_state];
पूर्ण

/*
 *	Handle state transitions
 */
अटल व्योम
tcp_state_transition(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
		     स्थिर काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_proto_data *pd)
अणु
	काष्ठा tcphdr _tcph, *th;

#अगर_घोषित CONFIG_IP_VS_IPV6
	पूर्णांक ihl = cp->af == AF_INET ? ip_hdrlen(skb) : माप(काष्ठा ipv6hdr);
#अन्यथा
	पूर्णांक ihl = ip_hdrlen(skb);
#पूर्ण_अगर

	th = skb_header_poपूर्णांकer(skb, ihl, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस;

	spin_lock_bh(&cp->lock);
	set_tcp_state(pd, cp, direction, th);
	spin_unlock_bh(&cp->lock);
पूर्ण

अटल अंतरभूत __u16 tcp_app_hashkey(__be16 port)
अणु
	वापस (((__क्रमce u16)port >> TCP_APP_TAB_BITS) ^ (__क्रमce u16)port)
		& TCP_APP_TAB_MASK;
पूर्ण


अटल पूर्णांक tcp_रेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_app *i;
	__u16 hash;
	__be16 port = inc->port;
	पूर्णांक ret = 0;
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);

	hash = tcp_app_hashkey(port);

	list_क्रम_each_entry(i, &ipvs->tcp_apps[hash], p_list) अणु
		अगर (i->port == port) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_rcu(&inc->p_list, &ipvs->tcp_apps[hash]);
	atomic_inc(&pd->appcnt);

  out:
	वापस ret;
पूर्ण


अटल व्योम
tcp_unरेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_TCP);

	atomic_dec(&pd->appcnt);
	list_del_rcu(&inc->p_list);
पूर्ण


अटल पूर्णांक
tcp_app_conn_bind(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा netns_ipvs *ipvs = cp->ipvs;
	पूर्णांक hash;
	काष्ठा ip_vs_app *inc;
	पूर्णांक result = 0;

	/* Default binding: bind app only क्रम NAT */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		वापस 0;

	/* Lookup application incarnations and bind the right one */
	hash = tcp_app_hashkey(cp->vport);

	list_क्रम_each_entry_rcu(inc, &ipvs->tcp_apps[hash], p_list) अणु
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


/*
 *	Set LISTEN समयout. (ip_vs_conn_put will setup समयr)
 */
व्योम ip_vs_tcp_conn_listen(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(cp->ipvs, IPPROTO_TCP);

	spin_lock_bh(&cp->lock);
	cp->state = IP_VS_TCP_S_LISTEN;
	cp->समयout = (pd ? pd->समयout_table[IP_VS_TCP_S_LISTEN]
			   : tcp_समयouts[IP_VS_TCP_S_LISTEN]);
	spin_unlock_bh(&cp->lock);
पूर्ण

/* ---------------------------------------------
 *   समयouts is netns related now.
 * ---------------------------------------------
 */
अटल पूर्णांक __ip_vs_tcp_init(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	ip_vs_init_hash_table(ipvs->tcp_apps, TCP_APP_TAB_SIZE);
	pd->समयout_table = ip_vs_create_समयout_table((पूर्णांक *)tcp_समयouts,
							माप(tcp_समयouts));
	अगर (!pd->समयout_table)
		वापस -ENOMEM;
	pd->tcp_state_table = tcp_states;
	वापस 0;
पूर्ण

अटल व्योम __ip_vs_tcp_निकास(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	kमुक्त(pd->समयout_table);
पूर्ण


काष्ठा ip_vs_protocol ip_vs_protocol_tcp = अणु
	.name =			"TCP",
	.protocol =		IPPROTO_TCP,
	.num_states =		IP_VS_TCP_S_LAST,
	.करोnt_defrag =		0,
	.init =			शून्य,
	.निकास =			शून्य,
	.init_netns =		__ip_vs_tcp_init,
	.निकास_netns =		__ip_vs_tcp_निकास,
	.रेजिस्टर_app =		tcp_रेजिस्टर_app,
	.unरेजिस्टर_app =	tcp_unरेजिस्टर_app,
	.conn_schedule =	tcp_conn_schedule,
	.conn_in_get =		ip_vs_conn_in_get_proto,
	.conn_out_get =		ip_vs_conn_out_get_proto,
	.snat_handler =		tcp_snat_handler,
	.dnat_handler =		tcp_dnat_handler,
	.state_name =		tcp_state_name,
	.state_transition =	tcp_state_transition,
	.app_conn_bind =	tcp_app_conn_bind,
	.debug_packet =		ip_vs_tcpudp_debug_packet,
	.समयout_change =	tcp_समयout_change,
पूर्ण;
