<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/ip.h>
#समावेश <linux/sctp.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/sctp/checksum.h>
#समावेश <net/ip_vs.h>

अटल पूर्णांक
sctp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp);

अटल पूर्णांक
sctp_conn_schedule(काष्ठा netns_ipvs *ipvs, पूर्णांक af, काष्ठा sk_buff *skb,
		   काष्ठा ip_vs_proto_data *pd,
		   पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
		   काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_service *svc;
	काष्ठा sctp_chunkhdr _schunkh, *sch;
	काष्ठा sctphdr *sh, _sctph;
	__be16 _ports[2], *ports = शून्य;

	अगर (likely(!ip_vs_iph_icmp(iph))) अणु
		sh = skb_header_poपूर्णांकer(skb, iph->len, माप(_sctph), &_sctph);
		अगर (sh) अणु
			sch = skb_header_poपूर्णांकer(skb, iph->len + माप(_sctph),
						 माप(_schunkh), &_schunkh);
			अगर (sch) अणु
				अगर (sch->type == SCTP_CID_ABORT ||
				    !(sysctl_sloppy_sctp(ipvs) ||
				      sch->type == SCTP_CID_INIT))
					वापस 1;
				ports = &sh->source;
			पूर्ण
		पूर्ण
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

अटल व्योम sctp_nat_csum(काष्ठा sk_buff *skb, काष्ठा sctphdr *sctph,
			  अचिन्हित पूर्णांक sctphoff)
अणु
	sctph->checksum = sctp_compute_cksum(skb, sctphoff);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक
sctp_snat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		  काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा sctphdr *sctph;
	अचिन्हित पूर्णांक sctphoff = iph->len;
	bool payload_csum = false;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, sctphoff + माप(*sctph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!sctp_csum_check(cp->af, skb, pp))
			वापस 0;

		/* Call application helper अगर needed */
		ret = ip_vs_app_pkt_out(cp, skb, iph);
		अगर (ret == 0)
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 2)
			payload_csum = true;
	पूर्ण

	sctph = (व्योम *) skb_network_header(skb) + sctphoff;

	/* Only update csum अगर we really have to */
	अगर (sctph->source != cp->vport || payload_csum ||
	    skb->ip_summed == CHECKSUM_PARTIAL) अणु
		sctph->source = cp->vport;
		sctp_nat_csum(skb, sctph, sctphoff);
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक
sctp_dnat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		  काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा sctphdr *sctph;
	अचिन्हित पूर्णांक sctphoff = iph->len;
	bool payload_csum = false;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (cp->af == AF_INET6 && iph->fragoffs)
		वापस 1;
#पूर्ण_अगर

	/* csum_check requires unshared skb */
	अगर (skb_ensure_writable(skb, sctphoff + माप(*sctph)))
		वापस 0;

	अगर (unlikely(cp->app != शून्य)) अणु
		पूर्णांक ret;

		/* Some checks beक्रमe mangling */
		अगर (!sctp_csum_check(cp->af, skb, pp))
			वापस 0;

		/* Call application helper अगर needed */
		ret = ip_vs_app_pkt_in(cp, skb, iph);
		अगर (ret == 0)
			वापस 0;
		/* ret=2: csum update is needed after payload mangling */
		अगर (ret == 2)
			payload_csum = true;
	पूर्ण

	sctph = (व्योम *) skb_network_header(skb) + sctphoff;

	/* Only update csum अगर we really have to */
	अगर (sctph->dest != cp->dport || payload_csum ||
	    (skb->ip_summed == CHECKSUM_PARTIAL &&
	     !(skb_dst(skb)->dev->features & NETIF_F_SCTP_CRC))) अणु
		sctph->dest = cp->dport;
		sctp_nat_csum(skb, sctph, sctphoff);
	पूर्ण अन्यथा अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक
sctp_csum_check(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp)
अणु
	अचिन्हित पूर्णांक sctphoff;
	काष्ठा sctphdr *sh;
	__le32 cmp, val;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		sctphoff = माप(काष्ठा ipv6hdr);
	अन्यथा
#पूर्ण_अगर
		sctphoff = ip_hdrlen(skb);

	sh = (काष्ठा sctphdr *)(skb->data + sctphoff);
	cmp = sh->checksum;
	val = sctp_compute_cksum(skb, sctphoff);

	अगर (val != cmp) अणु
		/* CRC failure, dump it. */
		IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
				"Failed checksum for");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

क्रमागत ipvs_sctp_event_t अणु
	IP_VS_SCTP_DATA = 0,		/* DATA, SACK, HEARTBEATs */
	IP_VS_SCTP_INIT,
	IP_VS_SCTP_INIT_ACK,
	IP_VS_SCTP_COOKIE_ECHO,
	IP_VS_SCTP_COOKIE_ACK,
	IP_VS_SCTP_SHUTDOWN,
	IP_VS_SCTP_SHUTDOWN_ACK,
	IP_VS_SCTP_SHUTDOWN_COMPLETE,
	IP_VS_SCTP_ERROR,
	IP_VS_SCTP_ABORT,
	IP_VS_SCTP_EVENT_LAST
पूर्ण;

/* RFC 2960, 3.2 Chunk Field Descriptions */
अटल __u8 sctp_events[] = अणु
	[SCTP_CID_DATA]			= IP_VS_SCTP_DATA,
	[SCTP_CID_INIT]			= IP_VS_SCTP_INIT,
	[SCTP_CID_INIT_ACK]		= IP_VS_SCTP_INIT_ACK,
	[SCTP_CID_SACK]			= IP_VS_SCTP_DATA,
	[SCTP_CID_HEARTBEAT]		= IP_VS_SCTP_DATA,
	[SCTP_CID_HEARTBEAT_ACK]	= IP_VS_SCTP_DATA,
	[SCTP_CID_ABORT]		= IP_VS_SCTP_ABORT,
	[SCTP_CID_SHUTDOWN]		= IP_VS_SCTP_SHUTDOWN,
	[SCTP_CID_SHUTDOWN_ACK]		= IP_VS_SCTP_SHUTDOWN_ACK,
	[SCTP_CID_ERROR]		= IP_VS_SCTP_ERROR,
	[SCTP_CID_COOKIE_ECHO]		= IP_VS_SCTP_COOKIE_ECHO,
	[SCTP_CID_COOKIE_ACK]		= IP_VS_SCTP_COOKIE_ACK,
	[SCTP_CID_ECN_ECNE]		= IP_VS_SCTP_DATA,
	[SCTP_CID_ECN_CWR]		= IP_VS_SCTP_DATA,
	[SCTP_CID_SHUTDOWN_COMPLETE]	= IP_VS_SCTP_SHUTDOWN_COMPLETE,
पूर्ण;

/* SCTP States:
 * See RFC 2960, 4. SCTP Association State Diagram
 *
 * New states (not in diagram):
 * - INIT1 state: use लघुer समयout क्रम dropped INIT packets
 * - REJECTED state: use लघुer समयout अगर INIT is rejected with ABORT
 * - INIT, COOKIE_SENT, COOKIE_REPLIED, COOKIE states: क्रम better debugging
 *
 * The states are as seen in real server. In the diagram, INIT1, INIT,
 * COOKIE_SENT and COOKIE_REPLIED processing happens in CLOSED state.
 *
 * States as per packets from client (C) and server (S):
 *
 * Setup of client connection:
 * IP_VS_SCTP_S_INIT1: First C:INIT sent, रुको क्रम S:INIT-ACK
 * IP_VS_SCTP_S_INIT: Next C:INIT sent, रुको क्रम S:INIT-ACK
 * IP_VS_SCTP_S_COOKIE_SENT: S:INIT-ACK sent, रुको क्रम C:COOKIE-ECHO
 * IP_VS_SCTP_S_COOKIE_REPLIED: C:COOKIE-ECHO sent, रुको क्रम S:COOKIE-ACK
 *
 * Setup of server connection:
 * IP_VS_SCTP_S_COOKIE_WAIT: S:INIT sent, रुको क्रम C:INIT-ACK
 * IP_VS_SCTP_S_COOKIE: C:INIT-ACK sent, रुको क्रम S:COOKIE-ECHO
 * IP_VS_SCTP_S_COOKIE_ECHOED: S:COOKIE-ECHO sent, रुको क्रम C:COOKIE-ACK
 */

#घोषणा sNO IP_VS_SCTP_S_NONE
#घोषणा sI1 IP_VS_SCTP_S_INIT1
#घोषणा sIN IP_VS_SCTP_S_INIT
#घोषणा sCS IP_VS_SCTP_S_COOKIE_SENT
#घोषणा sCR IP_VS_SCTP_S_COOKIE_REPLIED
#घोषणा sCW IP_VS_SCTP_S_COOKIE_WAIT
#घोषणा sCO IP_VS_SCTP_S_COOKIE
#घोषणा sCE IP_VS_SCTP_S_COOKIE_ECHOED
#घोषणा sES IP_VS_SCTP_S_ESTABLISHED
#घोषणा sSS IP_VS_SCTP_S_SHUTDOWN_SENT
#घोषणा sSR IP_VS_SCTP_S_SHUTDOWN_RECEIVED
#घोषणा sSA IP_VS_SCTP_S_SHUTDOWN_ACK_SENT
#घोषणा sRJ IP_VS_SCTP_S_REJECTED
#घोषणा sCL IP_VS_SCTP_S_CLOSED

अटल स्थिर __u8 sctp_states
	[IP_VS_सूची_LAST][IP_VS_SCTP_EVENT_LAST][IP_VS_SCTP_S_LAST] = अणु
	अणु /* INPUT */
/*        sNO, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCL*/
/* d   */अणुsES, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* i   */अणुsI1, sIN, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sIN, sINपूर्ण,
/* i_a */अणुsCW, sCW, sCW, sCS, sCR, sCO, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_e */अणुsCR, sIN, sIN, sCR, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_a */अणुsES, sI1, sIN, sCS, sCR, sCW, sCO, sES, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s   */अणुsSR, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sSR, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s_a */अणुsCL, sIN, sIN, sCS, sCR, sCW, sCO, sCE, sES, sCL, sSR, sCL, sRJ, sCLपूर्ण,
/* s_c */अणुsCL, sCL, sCL, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sCL, sRJ, sCLपूर्ण,
/* err */अणुsCL, sI1, sIN, sCS, sCR, sCW, sCO, sCL, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* ab  */अणुsCL, sCL, sCL, sCL, sCL, sRJ, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCLपूर्ण,
	पूर्ण,
	अणु /* OUTPUT */
/*        sNO, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCL*/
/* d   */अणुsES, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* i   */अणुsCW, sCW, sCW, sCW, sCW, sCW, sCW, sCW, sES, sCW, sCW, sCW, sCW, sCWपूर्ण,
/* i_a */अणुsCS, sCS, sCS, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_e */अणुsCE, sCE, sCE, sCE, sCE, sCE, sCE, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_a */अणुsES, sES, sES, sES, sES, sES, sES, sES, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s   */अणुsSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s_a */अणुsSA, sSA, sSA, sSA, sSA, sCW, sCO, sCE, sES, sSA, sSA, sSA, sRJ, sCLपूर्ण,
/* s_c */अणुsCL, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* err */अणुsCL, sCL, sCL, sCL, sCL, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* ab  */अणुsCL, sRJ, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCLपूर्ण,
	पूर्ण,
	अणु /* INPUT-ONLY */
/*        sNO, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCL*/
/* d   */अणुsES, sI1, sIN, sCS, sCR, sES, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* i   */अणुsI1, sIN, sIN, sIN, sIN, sIN, sCO, sCE, sES, sSS, sSR, sSA, sIN, sINपूर्ण,
/* i_a */अणुsCE, sCE, sCE, sCE, sCE, sCE, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_e */अणुsES, sES, sES, sES, sES, sES, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* c_a */अणुsES, sI1, sIN, sES, sES, sCW, sES, sES, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s   */अणुsSR, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sSR, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* s_a */अणुsCL, sIN, sIN, sCS, sCR, sCW, sCO, sCE, sCL, sCL, sSR, sCL, sRJ, sCLपूर्ण,
/* s_c */अणुsCL, sCL, sCL, sCL, sCL, sCW, sCO, sCE, sES, sSS, sCL, sCL, sRJ, sCLपूर्ण,
/* err */अणुsCL, sI1, sIN, sCS, sCR, sCW, sCO, sCE, sES, sSS, sSR, sSA, sRJ, sCLपूर्ण,
/* ab  */अणुsCL, sCL, sCL, sCL, sCL, sRJ, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCLपूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा IP_VS_SCTP_MAX_RTO	((60 + 1) * HZ)

/* Timeout table[state] */
अटल स्थिर पूर्णांक sctp_समयouts[IP_VS_SCTP_S_LAST + 1] = अणु
	[IP_VS_SCTP_S_NONE]			= 2 * HZ,
	[IP_VS_SCTP_S_INIT1]			= (0 + 3 + 1) * HZ,
	[IP_VS_SCTP_S_INIT]			= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_COOKIE_SENT]		= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_COOKIE_REPLIED]		= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_COOKIE_WAIT]		= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_COOKIE]			= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_COOKIE_ECHOED]		= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_ESTABLISHED]		= 15 * 60 * HZ,
	[IP_VS_SCTP_S_SHUTDOWN_SENT]		= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_SHUTDOWN_RECEIVED]	= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_SHUTDOWN_ACK_SENT]	= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_REJECTED]			= (0 + 3 + 1) * HZ,
	[IP_VS_SCTP_S_CLOSED]			= IP_VS_SCTP_MAX_RTO,
	[IP_VS_SCTP_S_LAST]			= 2 * HZ,
पूर्ण;

अटल स्थिर अक्षर *sctp_state_name_table[IP_VS_SCTP_S_LAST + 1] = अणु
	[IP_VS_SCTP_S_NONE]			= "NONE",
	[IP_VS_SCTP_S_INIT1]			= "INIT1",
	[IP_VS_SCTP_S_INIT]			= "INIT",
	[IP_VS_SCTP_S_COOKIE_SENT]		= "C-SENT",
	[IP_VS_SCTP_S_COOKIE_REPLIED]		= "C-REPLIED",
	[IP_VS_SCTP_S_COOKIE_WAIT]		= "C-WAIT",
	[IP_VS_SCTP_S_COOKIE]			= "COOKIE",
	[IP_VS_SCTP_S_COOKIE_ECHOED]		= "C-ECHOED",
	[IP_VS_SCTP_S_ESTABLISHED]		= "ESTABLISHED",
	[IP_VS_SCTP_S_SHUTDOWN_SENT]		= "S-SENT",
	[IP_VS_SCTP_S_SHUTDOWN_RECEIVED]	= "S-RECEIVED",
	[IP_VS_SCTP_S_SHUTDOWN_ACK_SENT]	= "S-ACK-SENT",
	[IP_VS_SCTP_S_REJECTED]			= "REJECTED",
	[IP_VS_SCTP_S_CLOSED]			= "CLOSED",
	[IP_VS_SCTP_S_LAST]			= "BUG!",
पूर्ण;


अटल स्थिर अक्षर *sctp_state_name(पूर्णांक state)
अणु
	अगर (state >= IP_VS_SCTP_S_LAST)
		वापस "ERR!";
	अगर (sctp_state_name_table[state])
		वापस sctp_state_name_table[state];
	वापस "?";
पूर्ण

अटल अंतरभूत व्योम
set_sctp_state(काष्ठा ip_vs_proto_data *pd, काष्ठा ip_vs_conn *cp,
		पूर्णांक direction, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunkhdr _sctpch, *sch;
	अचिन्हित अक्षर chunk_type;
	पूर्णांक event, next_state;
	पूर्णांक ihl, cofs;

#अगर_घोषित CONFIG_IP_VS_IPV6
	ihl = cp->af == AF_INET ? ip_hdrlen(skb) : माप(काष्ठा ipv6hdr);
#अन्यथा
	ihl = ip_hdrlen(skb);
#पूर्ण_अगर

	cofs = ihl + माप(काष्ठा sctphdr);
	sch = skb_header_poपूर्णांकer(skb, cofs, माप(_sctpch), &_sctpch);
	अगर (sch == शून्य)
		वापस;

	chunk_type = sch->type;
	/*
	 * Section 3: Multiple chunks can be bundled पूर्णांकo one SCTP packet
	 * up to the MTU size, except क्रम the INIT, INIT ACK, and
	 * SHUTDOWN COMPLETE chunks. These chunks MUST NOT be bundled with
	 * any other chunk in a packet.
	 *
	 * Section 3.3.7: DATA chunks MUST NOT be bundled with ABORT. Control
	 * chunks (except क्रम INIT, INIT ACK, and SHUTDOWN COMPLETE) MAY be
	 * bundled with an ABORT, but they MUST be placed beक्रमe the ABORT
	 * in the SCTP packet or they will be ignored by the receiver.
	 */
	अगर ((sch->type == SCTP_CID_COOKIE_ECHO) ||
	    (sch->type == SCTP_CID_COOKIE_ACK)) अणु
		पूर्णांक clen = ntohs(sch->length);

		अगर (clen >= माप(_sctpch)) अणु
			sch = skb_header_poपूर्णांकer(skb, cofs + ALIGN(clen, 4),
						 माप(_sctpch), &_sctpch);
			अगर (sch && sch->type == SCTP_CID_ABORT)
				chunk_type = sch->type;
		पूर्ण
	पूर्ण

	event = (chunk_type < माप(sctp_events)) ?
		sctp_events[chunk_type] : IP_VS_SCTP_DATA;

	/* Update direction to INPUT_ONLY अगर necessary
	 * or delete NO_OUTPUT flag अगर output packet detected
	 */
	अगर (cp->flags & IP_VS_CONN_F_NOOUTPUT) अणु
		अगर (direction == IP_VS_सूची_OUTPUT)
			cp->flags &= ~IP_VS_CONN_F_NOOUTPUT;
		अन्यथा
			direction = IP_VS_सूची_INPUT_ONLY;
	पूर्ण

	next_state = sctp_states[direction][event][cp->state];

	अगर (next_state != cp->state) अणु
		काष्ठा ip_vs_dest *dest = cp->dest;

		IP_VS_DBG_BUF(8, "%s %s  %s:%d->"
				"%s:%d state: %s->%s conn->refcnt:%d\n",
				pd->pp->name,
				((direction == IP_VS_सूची_OUTPUT) ?
				 "output " : "input "),
				IP_VS_DBG_ADDR(cp->daf, &cp->daddr),
				ntohs(cp->dport),
				IP_VS_DBG_ADDR(cp->af, &cp->caddr),
				ntohs(cp->cport),
				sctp_state_name(cp->state),
				sctp_state_name(next_state),
				refcount_पढ़ो(&cp->refcnt));
		अगर (dest) अणु
			अगर (!(cp->flags & IP_VS_CONN_F_INACTIVE) &&
				(next_state != IP_VS_SCTP_S_ESTABLISHED)) अणु
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
				cp->flags |= IP_VS_CONN_F_INACTIVE;
			पूर्ण अन्यथा अगर ((cp->flags & IP_VS_CONN_F_INACTIVE) &&
				   (next_state == IP_VS_SCTP_S_ESTABLISHED)) अणु
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
				cp->flags &= ~IP_VS_CONN_F_INACTIVE;
			पूर्ण
		पूर्ण
		अगर (next_state == IP_VS_SCTP_S_ESTABLISHED)
			ip_vs_control_assure_ct(cp);
	पूर्ण
	अगर (likely(pd))
		cp->समयout = pd->समयout_table[cp->state = next_state];
	अन्यथा	/* What to करो ? */
		cp->समयout = sctp_समयouts[cp->state = next_state];
पूर्ण

अटल व्योम
sctp_state_transition(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
		स्थिर काष्ठा sk_buff *skb, काष्ठा ip_vs_proto_data *pd)
अणु
	spin_lock_bh(&cp->lock);
	set_sctp_state(pd, cp, direction, skb);
	spin_unlock_bh(&cp->lock);
पूर्ण

अटल अंतरभूत __u16 sctp_app_hashkey(__be16 port)
अणु
	वापस (((__क्रमce u16)port >> SCTP_APP_TAB_BITS) ^ (__क्रमce u16)port)
		& SCTP_APP_TAB_MASK;
पूर्ण

अटल पूर्णांक sctp_रेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_app *i;
	__u16 hash;
	__be16 port = inc->port;
	पूर्णांक ret = 0;
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_SCTP);

	hash = sctp_app_hashkey(port);

	list_क्रम_each_entry(i, &ipvs->sctp_apps[hash], p_list) अणु
		अगर (i->port == port) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_rcu(&inc->p_list, &ipvs->sctp_apps[hash]);
	atomic_inc(&pd->appcnt);
out:

	वापस ret;
पूर्ण

अटल व्योम sctp_unरेजिस्टर_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_proto_data *pd = ip_vs_proto_data_get(ipvs, IPPROTO_SCTP);

	atomic_dec(&pd->appcnt);
	list_del_rcu(&inc->p_list);
पूर्ण

अटल पूर्णांक sctp_app_conn_bind(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा netns_ipvs *ipvs = cp->ipvs;
	पूर्णांक hash;
	काष्ठा ip_vs_app *inc;
	पूर्णांक result = 0;

	/* Default binding: bind app only क्रम NAT */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		वापस 0;
	/* Lookup application incarnations and bind the right one */
	hash = sctp_app_hashkey(cp->vport);

	list_क्रम_each_entry_rcu(inc, &ipvs->sctp_apps[hash], p_list) अणु
		अगर (inc->port == cp->vport) अणु
			अगर (unlikely(!ip_vs_app_inc_get(inc)))
				अवरोध;

			IP_VS_DBG_BUF(9, "%s: Binding conn %s:%u->"
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

/* ---------------------------------------------
 *   समयouts is netns related now.
 * ---------------------------------------------
 */
अटल पूर्णांक __ip_vs_sctp_init(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	ip_vs_init_hash_table(ipvs->sctp_apps, SCTP_APP_TAB_SIZE);
	pd->समयout_table = ip_vs_create_समयout_table((पूर्णांक *)sctp_समयouts,
							माप(sctp_समयouts));
	अगर (!pd->समयout_table)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __ip_vs_sctp_निकास(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	kमुक्त(pd->समयout_table);
पूर्ण

काष्ठा ip_vs_protocol ip_vs_protocol_sctp = अणु
	.name		= "SCTP",
	.protocol	= IPPROTO_SCTP,
	.num_states	= IP_VS_SCTP_S_LAST,
	.करोnt_defrag	= 0,
	.init		= शून्य,
	.निकास		= शून्य,
	.init_netns	= __ip_vs_sctp_init,
	.निकास_netns	= __ip_vs_sctp_निकास,
	.रेजिस्टर_app	= sctp_रेजिस्टर_app,
	.unरेजिस्टर_app = sctp_unरेजिस्टर_app,
	.conn_schedule	= sctp_conn_schedule,
	.conn_in_get	= ip_vs_conn_in_get_proto,
	.conn_out_get	= ip_vs_conn_out_get_proto,
	.snat_handler	= sctp_snat_handler,
	.dnat_handler	= sctp_dnat_handler,
	.state_name	= sctp_state_name,
	.state_transition = sctp_state_transition,
	.app_conn_bind	= sctp_app_conn_bind,
	.debug_packet	= ip_vs_tcpudp_debug_packet,
	.समयout_change	= शून्य,
पूर्ण;
