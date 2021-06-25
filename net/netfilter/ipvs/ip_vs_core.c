<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS         An implementation of the IP भव server support क्रम the
 *              LINUX operating प्रणाली.  IPVS is now implemented as a module
 *              over the Netfilter framework. IPVS can be used to build a
 *              high-perक्रमmance and highly available server based on a
 *              cluster of servers.
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * The IPVS code क्रम kernel 2.2 was करोne by Wensong Zhang and Peter Kese,
 * with changes/fixes from Julian Anastasov, Lars Marowsky-Bree, Horms
 * and others.
 *
 * Changes:
 *	Paul `Rusty' Russell		properly handle non-linear skbs
 *	Harald Welte			करोn't use nfcache
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/slab.h>

#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/icmp.h>                   /* क्रम icmp_send */
#समावेश <net/gue.h>
#समावेश <net/gre.h>
#समावेश <net/route.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/netns/generic.h>		/* net_generic() */

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>

#अगर_घोषित CONFIG_IP_VS_IPV6
#समावेश <net/ipv6.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/ip6_route.h>
#पूर्ण_अगर

#समावेश <net/ip_vs.h>
#समावेश <linux/indirect_call_wrapper.h>


EXPORT_SYMBOL(रेजिस्टर_ip_vs_scheduler);
EXPORT_SYMBOL(unरेजिस्टर_ip_vs_scheduler);
EXPORT_SYMBOL(ip_vs_proto_name);
EXPORT_SYMBOL(ip_vs_conn_new);
EXPORT_SYMBOL(ip_vs_conn_in_get);
EXPORT_SYMBOL(ip_vs_conn_out_get);
#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
EXPORT_SYMBOL(ip_vs_tcp_conn_listen);
#पूर्ण_अगर
EXPORT_SYMBOL(ip_vs_conn_put);
#अगर_घोषित CONFIG_IP_VS_DEBUG
EXPORT_SYMBOL(ip_vs_get_debug_level);
#पूर्ण_अगर
EXPORT_SYMBOL(ip_vs_new_conn_out);

#अगर defined(CONFIG_IP_VS_PROTO_TCP) && defined(CONFIG_IP_VS_PROTO_UDP)
#घोषणा SNAT_CALL(f, ...) \
	INसूचीECT_CALL_2(f, tcp_snat_handler, udp_snat_handler, __VA_ARGS__)
#या_अगर defined(CONFIG_IP_VS_PROTO_TCP)
#घोषणा SNAT_CALL(f, ...) INसूचीECT_CALL_1(f, tcp_snat_handler, __VA_ARGS__)
#या_अगर defined(CONFIG_IP_VS_PROTO_UDP)
#घोषणा SNAT_CALL(f, ...) INसूचीECT_CALL_1(f, udp_snat_handler, __VA_ARGS__)
#अन्यथा
#घोषणा SNAT_CALL(f, ...) f(__VA_ARGS__)
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक ip_vs_net_id __पढ़ो_mostly;
/* netns cnt used क्रम uniqueness */
अटल atomic_t ipvs_netns_cnt = ATOMIC_INIT(0);

/* ID used in ICMP lookups */
#घोषणा icmp_id(icmph)          (((icmph)->un).echo.id)
#घोषणा icmpv6_id(icmph)        (icmph->icmp6_dataun.u_echo.identअगरier)

स्थिर अक्षर *ip_vs_proto_name(अचिन्हित पूर्णांक proto)
अणु
	अटल अक्षर buf[20];

	चयन (proto) अणु
	हाल IPPROTO_IP:
		वापस "IP";
	हाल IPPROTO_UDP:
		वापस "UDP";
	हाल IPPROTO_TCP:
		वापस "TCP";
	हाल IPPROTO_SCTP:
		वापस "SCTP";
	हाल IPPROTO_ICMP:
		वापस "ICMP";
#अगर_घोषित CONFIG_IP_VS_IPV6
	हाल IPPROTO_ICMPV6:
		वापस "ICMPv6";
#पूर्ण_अगर
	शेष:
		प्र_लिखो(buf, "IP_%u", proto);
		वापस buf;
	पूर्ण
पूर्ण

व्योम ip_vs_init_hash_table(काष्ठा list_head *table, पूर्णांक rows)
अणु
	जबतक (--rows >= 0)
		INIT_LIST_HEAD(&table[rows]);
पूर्ण

अटल अंतरभूत व्योम
ip_vs_in_stats(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_vs_dest *dest = cp->dest;
	काष्ठा netns_ipvs *ipvs = cp->ipvs;

	अगर (dest && (dest->flags & IP_VS_DEST_F_AVAILABLE)) अणु
		काष्ठा ip_vs_cpu_stats *s;
		काष्ठा ip_vs_service *svc;

		local_bh_disable();

		s = this_cpu_ptr(dest->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.inpkts++;
		s->cnt.inbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		svc = rcu_dereference(dest->svc);
		s = this_cpu_ptr(svc->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.inpkts++;
		s->cnt.inbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		s = this_cpu_ptr(ipvs->tot_stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.inpkts++;
		s->cnt.inbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		local_bh_enable();
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम
ip_vs_out_stats(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_vs_dest *dest = cp->dest;
	काष्ठा netns_ipvs *ipvs = cp->ipvs;

	अगर (dest && (dest->flags & IP_VS_DEST_F_AVAILABLE)) अणु
		काष्ठा ip_vs_cpu_stats *s;
		काष्ठा ip_vs_service *svc;

		local_bh_disable();

		s = this_cpu_ptr(dest->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.outpkts++;
		s->cnt.outbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		svc = rcu_dereference(dest->svc);
		s = this_cpu_ptr(svc->stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.outpkts++;
		s->cnt.outbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		s = this_cpu_ptr(ipvs->tot_stats.cpustats);
		u64_stats_update_begin(&s->syncp);
		s->cnt.outpkts++;
		s->cnt.outbytes += skb->len;
		u64_stats_update_end(&s->syncp);

		local_bh_enable();
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम
ip_vs_conn_stats(काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_service *svc)
अणु
	काष्ठा netns_ipvs *ipvs = svc->ipvs;
	काष्ठा ip_vs_cpu_stats *s;

	local_bh_disable();

	s = this_cpu_ptr(cp->dest->stats.cpustats);
	u64_stats_update_begin(&s->syncp);
	s->cnt.conns++;
	u64_stats_update_end(&s->syncp);

	s = this_cpu_ptr(svc->stats.cpustats);
	u64_stats_update_begin(&s->syncp);
	s->cnt.conns++;
	u64_stats_update_end(&s->syncp);

	s = this_cpu_ptr(ipvs->tot_stats.cpustats);
	u64_stats_update_begin(&s->syncp);
	s->cnt.conns++;
	u64_stats_update_end(&s->syncp);

	local_bh_enable();
पूर्ण


अटल अंतरभूत व्योम
ip_vs_set_state(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
		स्थिर काष्ठा sk_buff *skb,
		काष्ठा ip_vs_proto_data *pd)
अणु
	अगर (likely(pd->pp->state_transition))
		pd->pp->state_transition(cp, direction, skb, pd);
पूर्ण

अटल अंतरभूत पूर्णांक
ip_vs_conn_fill_param_persist(स्थिर काष्ठा ip_vs_service *svc,
			      काष्ठा sk_buff *skb, पूर्णांक protocol,
			      स्थिर जोड़ nf_inet_addr *caddr, __be16 cport,
			      स्थिर जोड़ nf_inet_addr *vaddr, __be16 vport,
			      काष्ठा ip_vs_conn_param *p)
अणु
	ip_vs_conn_fill_param(svc->ipvs, svc->af, protocol, caddr, cport, vaddr,
			      vport, p);
	p->pe = rcu_dereference(svc->pe);
	अगर (p->pe && p->pe->fill_param)
		वापस p->pe->fill_param(p, skb);

	वापस 0;
पूर्ण

/*
 *  IPVS persistent scheduling function
 *  It creates a connection entry according to its ढाँचा अगर exists,
 *  or selects a server and creates a connection entry plus a ढाँचा.
 *  Locking: we are svc user (svc->refcnt), so we hold all dests too
 *  Protocols supported: TCP, UDP
 */
अटल काष्ठा ip_vs_conn *
ip_vs_sched_persist(काष्ठा ip_vs_service *svc,
		    काष्ठा sk_buff *skb, __be16 src_port, __be16 dst_port,
		    पूर्णांक *ignored, काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_conn *cp = शून्य;
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_conn *ct;
	__be16 dport = 0;		/* destination port to क्रमward */
	अचिन्हित पूर्णांक flags;
	काष्ठा ip_vs_conn_param param;
	स्थिर जोड़ nf_inet_addr fwmark = अणु .ip = htonl(svc->fwmark) पूर्ण;
	जोड़ nf_inet_addr snet;	/* source network of the client,
					   after masking */
	स्थिर जोड़ nf_inet_addr *src_addr, *dst_addr;

	अगर (likely(!ip_vs_iph_inverse(iph))) अणु
		src_addr = &iph->saddr;
		dst_addr = &iph->daddr;
	पूर्ण अन्यथा अणु
		src_addr = &iph->daddr;
		dst_addr = &iph->saddr;
	पूर्ण


	/* Mask saddr with the neपंचांगask to adjust ढाँचा granularity */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (svc->af == AF_INET6)
		ipv6_addr_prefix(&snet.in6, &src_addr->in6,
				 (__क्रमce __u32) svc->neपंचांगask);
	अन्यथा
#पूर्ण_अगर
		snet.ip = src_addr->ip & svc->neपंचांगask;

	IP_VS_DBG_BUF(6, "p-schedule: src %s:%u dest %s:%u "
		      "mnet %s\n",
		      IP_VS_DBG_ADDR(svc->af, src_addr), ntohs(src_port),
		      IP_VS_DBG_ADDR(svc->af, dst_addr), ntohs(dst_port),
		      IP_VS_DBG_ADDR(svc->af, &snet));

	/*
	 * As far as we know, FTP is a very complicated network protocol, and
	 * it uses control connection and data connections. For active FTP,
	 * FTP server initialize data connection to the client, its source port
	 * is often 20. For passive FTP, FTP server tells the clients the port
	 * that it passively listens to,  and the client issues the data
	 * connection. In the tunneling or direct routing mode, the load
	 * balancer is on the client-to-server half of connection, the port
	 * number is unknown to the load balancer. So, a conn ढाँचा like
	 * <caddr, 0, vaddr, 0, daddr, 0> is created क्रम persistent FTP
	 * service, and a ढाँचा like <caddr, 0, vaddr, vport, daddr, dport>
	 * is created क्रम other persistent services.
	 */
	अणु
		पूर्णांक protocol = iph->protocol;
		स्थिर जोड़ nf_inet_addr *vaddr = dst_addr;
		__be16 vport = 0;

		अगर (dst_port == svc->port) अणु
			/* non-FTP ढाँचा:
			 * <protocol, caddr, 0, vaddr, vport, daddr, dport>
			 * FTP ढाँचा:
			 * <protocol, caddr, 0, vaddr, 0, daddr, 0>
			 */
			अगर (svc->port != FTPPORT)
				vport = dst_port;
		पूर्ण अन्यथा अणु
			/* Note: persistent fwmark-based services and
			 * persistent port zero service are handled here.
			 * fwmark ढाँचा:
			 * <IPPROTO_IP,caddr,0,fwmark,0,daddr,0>
			 * port zero ढाँचा:
			 * <protocol,caddr,0,vaddr,0,daddr,0>
			 */
			अगर (svc->fwmark) अणु
				protocol = IPPROTO_IP;
				vaddr = &fwmark;
			पूर्ण
		पूर्ण
		/* वापस *ignored = -1 so NF_DROP can be used */
		अगर (ip_vs_conn_fill_param_persist(svc, skb, protocol, &snet, 0,
						  vaddr, vport, &param) < 0) अणु
			*ignored = -1;
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* Check अगर a ढाँचा alपढ़ोy exists */
	ct = ip_vs_ct_in_get(&param);
	अगर (!ct || !ip_vs_check_ढाँचा(ct, शून्य)) अणु
		काष्ठा ip_vs_scheduler *sched;

		/*
		 * No ढाँचा found or the dest of the connection
		 * ढाँचा is not available.
		 * वापस *ignored=0 i.e. ICMP and NF_DROP
		 */
		sched = rcu_dereference(svc->scheduler);
		अगर (sched) अणु
			/* पढ़ो svc->sched_data after svc->scheduler */
			smp_rmb();
			dest = sched->schedule(svc, skb, iph);
		पूर्ण अन्यथा अणु
			dest = शून्य;
		पूर्ण
		अगर (!dest) अणु
			IP_VS_DBG(1, "p-schedule: no dest found.\n");
			kमुक्त(param.pe_data);
			*ignored = 0;
			वापस शून्य;
		पूर्ण

		अगर (dst_port == svc->port && svc->port != FTPPORT)
			dport = dest->port;

		/* Create a ढाँचा
		 * This adds param.pe_data to the ढाँचा,
		 * and thus param.pe_data will be destroyed
		 * when the ढाँचा expires */
		ct = ip_vs_conn_new(&param, dest->af, &dest->addr, dport,
				    IP_VS_CONN_F_TEMPLATE, dest, skb->mark);
		अगर (ct == शून्य) अणु
			kमुक्त(param.pe_data);
			*ignored = -1;
			वापस शून्य;
		पूर्ण

		ct->समयout = svc->समयout;
	पूर्ण अन्यथा अणु
		/* set destination with the found ढाँचा */
		dest = ct->dest;
		kमुक्त(param.pe_data);
	पूर्ण

	dport = dst_port;
	अगर (dport == svc->port && dest->port)
		dport = dest->port;

	flags = (svc->flags & IP_VS_SVC_F_ONEPACKET
		 && iph->protocol == IPPROTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Create a new connection according to the ढाँचा
	 */
	ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol, src_addr,
			      src_port, dst_addr, dst_port, &param);

	cp = ip_vs_conn_new(&param, dest->af, &dest->addr, dport, flags, dest,
			    skb->mark);
	अगर (cp == शून्य) अणु
		ip_vs_conn_put(ct);
		*ignored = -1;
		वापस शून्य;
	पूर्ण

	/*
	 *    Add its control
	 */
	ip_vs_control_add(cp, ct);
	ip_vs_conn_put(ct);

	ip_vs_conn_stats(cp, svc);
	वापस cp;
पूर्ण


/*
 *  IPVS मुख्य scheduling function
 *  It selects a server according to the भव service, and
 *  creates a connection entry.
 *  Protocols supported: TCP, UDP
 *
 *  Usage of *ignored
 *
 * 1 :   protocol tried to schedule (eg. on SYN), found svc but the
 *       svc/scheduler decides that this packet should be accepted with
 *       NF_ACCEPT because it must not be scheduled.
 *
 * 0 :   scheduler can not find destination, so try bypass or
 *       वापस ICMP and then NF_DROP (ip_vs_leave).
 *
 * -1 :  scheduler tried to schedule but fatal error occurred, eg.
 *       ip_vs_conn_new failure (ENOMEM) or ip_vs_sip_fill_param
 *       failure such as missing Call-ID, ENOMEM on skb_linearize
 *       or pe_data. In this हाल we should वापस NF_DROP without
 *       any attempts to send ICMP with ip_vs_leave.
 */
काष्ठा ip_vs_conn *
ip_vs_schedule(काष्ठा ip_vs_service *svc, काष्ठा sk_buff *skb,
	       काष्ठा ip_vs_proto_data *pd, पूर्णांक *ignored,
	       काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_protocol *pp = pd->pp;
	काष्ठा ip_vs_conn *cp = शून्य;
	काष्ठा ip_vs_scheduler *sched;
	काष्ठा ip_vs_dest *dest;
	__be16 _ports[2], *pptr, cport, vport;
	स्थिर व्योम *caddr, *vaddr;
	अचिन्हित पूर्णांक flags;

	*ignored = 1;
	/*
	 * IPv6 frags, only the first hit here.
	 */
	pptr = frag_safe_skb_hp(skb, iph->len, माप(_ports), _ports);
	अगर (pptr == शून्य)
		वापस शून्य;

	अगर (likely(!ip_vs_iph_inverse(iph))) अणु
		cport = pptr[0];
		caddr = &iph->saddr;
		vport = pptr[1];
		vaddr = &iph->daddr;
	पूर्ण अन्यथा अणु
		cport = pptr[1];
		caddr = &iph->daddr;
		vport = pptr[0];
		vaddr = &iph->saddr;
	पूर्ण

	/*
	 * FTPDATA needs this check when using local real server.
	 * Never schedule Active FTPDATA connections from real server.
	 * For LVS-NAT they must be alपढ़ोy created. For other methods
	 * with persistence the connection is created on SYN+ACK.
	 */
	अगर (cport == FTPDATA) अणु
		IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
			      "Not scheduling FTPDATA");
		वापस शून्य;
	पूर्ण

	/*
	 *    Do not schedule replies from local real server.
	 */
	अगर ((!skb->dev || skb->dev->flags & IFF_LOOPBACK)) अणु
		iph->hdr_flags ^= IP_VS_HDR_INVERSE;
		cp = INसूचीECT_CALL_1(pp->conn_in_get,
				     ip_vs_conn_in_get_proto, svc->ipvs,
				     svc->af, skb, iph);
		iph->hdr_flags ^= IP_VS_HDR_INVERSE;

		अगर (cp) अणु
			IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
				      "Not scheduling reply for existing"
				      " connection");
			__ip_vs_conn_put(cp);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/*
	 *    Persistent service
	 */
	अगर (svc->flags & IP_VS_SVC_F_PERSISTENT)
		वापस ip_vs_sched_persist(svc, skb, cport, vport, ignored,
					   iph);

	*ignored = 0;

	/*
	 *    Non-persistent service
	 */
	अगर (!svc->fwmark && vport != svc->port) अणु
		अगर (!svc->port)
			pr_err("Schedule: port zero only supported "
			       "in persistent services, "
			       "check your ipvs configuration\n");
		वापस शून्य;
	पूर्ण

	sched = rcu_dereference(svc->scheduler);
	अगर (sched) अणु
		/* पढ़ो svc->sched_data after svc->scheduler */
		smp_rmb();
		dest = sched->schedule(svc, skb, iph);
	पूर्ण अन्यथा अणु
		dest = शून्य;
	पूर्ण
	अगर (dest == शून्य) अणु
		IP_VS_DBG(1, "Schedule: no dest found.\n");
		वापस शून्य;
	पूर्ण

	flags = (svc->flags & IP_VS_SVC_F_ONEPACKET
		 && iph->protocol == IPPROTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Create a connection entry.
	 */
	अणु
		काष्ठा ip_vs_conn_param p;

		ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol,
				      caddr, cport, vaddr, vport, &p);
		cp = ip_vs_conn_new(&p, dest->af, &dest->addr,
				    dest->port ? dest->port : vport,
				    flags, dest, skb->mark);
		अगर (!cp) अणु
			*ignored = -1;
			वापस शून्य;
		पूर्ण
	पूर्ण

	IP_VS_DBG_BUF(6, "Schedule fwd:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->flags:%X conn->refcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->daf, &cp->daddr), ntohs(cp->dport),
		      cp->flags, refcount_पढ़ो(&cp->refcnt));

	ip_vs_conn_stats(cp, svc);
	वापस cp;
पूर्ण

अटल अंतरभूत पूर्णांक ip_vs_addr_is_unicast(काष्ठा net *net, पूर्णांक af,
					जोड़ nf_inet_addr *addr)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		वापस ipv6_addr_type(&addr->in6) & IPV6_ADDR_UNICAST;
#पूर्ण_अगर
	वापस (inet_addr_type(net, addr->ip) == RTN_UNICAST);
पूर्ण

/*
 *  Pass or drop the packet.
 *  Called by ip_vs_in, when the भव service is available but
 *  no destination is available क्रम a new connection.
 */
पूर्णांक ip_vs_leave(काष्ठा ip_vs_service *svc, काष्ठा sk_buff *skb,
		काष्ठा ip_vs_proto_data *pd, काष्ठा ip_vs_iphdr *iph)
अणु
	__be16 _ports[2], *pptr, dport;
	काष्ठा netns_ipvs *ipvs = svc->ipvs;
	काष्ठा net *net = ipvs->net;

	pptr = frag_safe_skb_hp(skb, iph->len, माप(_ports), _ports);
	अगर (!pptr)
		वापस NF_DROP;
	dport = likely(!ip_vs_iph_inverse(iph)) ? pptr[1] : pptr[0];

	/* अगर it is fwmark-based service, the cache_bypass sysctl is up
	   and the destination is a non-local unicast, then create
	   a cache_bypass connection entry */
	अगर (sysctl_cache_bypass(ipvs) && svc->fwmark &&
	    !(iph->hdr_flags & (IP_VS_HDR_INVERSE | IP_VS_HDR_ICMP)) &&
	    ip_vs_addr_is_unicast(net, svc->af, &iph->daddr)) अणु
		पूर्णांक ret;
		काष्ठा ip_vs_conn *cp;
		अचिन्हित पूर्णांक flags = (svc->flags & IP_VS_SVC_F_ONEPACKET &&
				      iph->protocol == IPPROTO_UDP) ?
				      IP_VS_CONN_F_ONE_PACKET : 0;
		जोड़ nf_inet_addr daddr = अणु .all = अणु 0, 0, 0, 0 पूर्ण पूर्ण;

		/* create a new connection entry */
		IP_VS_DBG(6, "%s(): create a cache_bypass entry\n", __func__);
		अणु
			काष्ठा ip_vs_conn_param p;
			ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol,
					      &iph->saddr, pptr[0],
					      &iph->daddr, pptr[1], &p);
			cp = ip_vs_conn_new(&p, svc->af, &daddr, 0,
					    IP_VS_CONN_F_BYPASS | flags,
					    शून्य, skb->mark);
			अगर (!cp)
				वापस NF_DROP;
		पूर्ण

		/* statistics */
		ip_vs_in_stats(cp, skb);

		/* set state */
		ip_vs_set_state(cp, IP_VS_सूची_INPUT, skb, pd);

		/* transmit the first SYN packet */
		ret = cp->packet_xmit(skb, cp, pd->pp, iph);
		/* करो not touch skb anymore */

		अगर ((cp->flags & IP_VS_CONN_F_ONE_PACKET) && cp->control)
			atomic_inc(&cp->control->in_pkts);
		अन्यथा
			atomic_inc(&cp->in_pkts);
		ip_vs_conn_put(cp);
		वापस ret;
	पूर्ण

	/*
	 * When the भव ftp service is presented, packets destined
	 * क्रम other services on the VIP may get here (except services
	 * listed in the ipvs table), pass the packets, because it is
	 * not ipvs job to decide to drop the packets.
	 */
	अगर (svc->port == FTPPORT && dport != FTPPORT)
		वापस NF_ACCEPT;

	अगर (unlikely(ip_vs_iph_icmp(iph)))
		वापस NF_DROP;

	/*
	 * Notअगरy the client that the destination is unreachable, and
	 * release the socket buffer.
	 * Since it is in IP layer, the TCP socket is not actually
	 * created, the TCP RST packet cannot be sent, instead that
	 * ICMP_PORT_UNREACH is sent here no matter it is TCP/UDP. --WZ
	 */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (svc->af == AF_INET6) अणु
		अगर (!skb->dev)
			skb->dev = net->loopback_dev;
		icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);
	पूर्ण अन्यथा
#पूर्ण_अगर
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

	वापस NF_DROP;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल पूर्णांक sysctl_snat_reroute(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_snat_reroute;
पूर्ण

अटल पूर्णांक sysctl_nat_icmp_send(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_nat_icmp_send;
पूर्ण

#अन्यथा

अटल पूर्णांक sysctl_snat_reroute(काष्ठा netns_ipvs *ipvs) अणु वापस 0; पूर्ण
अटल पूर्णांक sysctl_nat_icmp_send(काष्ठा netns_ipvs *ipvs) अणु वापस 0; पूर्ण

#पूर्ण_अगर

__sum16 ip_vs_checksum_complete(काष्ठा sk_buff *skb, पूर्णांक offset)
अणु
	वापस csum_fold(skb_checksum(skb, offset, skb->len - offset, 0));
पूर्ण

अटल अंतरभूत क्रमागत ip_defrag_users ip_vs_defrag_user(अचिन्हित पूर्णांक hooknum)
अणु
	अगर (NF_INET_LOCAL_IN == hooknum)
		वापस IP_DEFRAG_VS_IN;
	अगर (NF_INET_FORWARD == hooknum)
		वापस IP_DEFRAG_VS_FWD;
	वापस IP_DEFRAG_VS_OUT;
पूर्ण

अटल अंतरभूत पूर्णांक ip_vs_gather_frags(काष्ठा netns_ipvs *ipvs,
				     काष्ठा sk_buff *skb, u_पूर्णांक32_t user)
अणु
	पूर्णांक err;

	local_bh_disable();
	err = ip_defrag(ipvs->net, skb, user);
	local_bh_enable();
	अगर (!err)
		ip_send_check(ip_hdr(skb));

	वापस err;
पूर्ण

अटल पूर्णांक ip_vs_route_me_harder(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
				 काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hooknum)
अणु
	अगर (!sysctl_snat_reroute(ipvs))
		वापस 0;
	/* Reroute replies only to remote clients (FORWARD and LOCAL_OUT) */
	अगर (NF_INET_LOCAL_IN == hooknum)
		वापस 0;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);

		अगर (dst->dev && !(dst->dev->flags & IFF_LOOPBACK) &&
		    ip6_route_me_harder(ipvs->net, skb->sk, skb) != 0)
			वापस 1;
	पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (!(skb_rtable(skb)->rt_flags & RTCF_LOCAL) &&
		    ip_route_me_harder(ipvs->net, skb->sk, skb, RTN_LOCAL) != 0)
			वापस 1;

	वापस 0;
पूर्ण

/*
 * Packet has been made sufficiently writable in caller
 * - inout: 1=in->out, 0=out->in
 */
व्योम ip_vs_nat_icmp(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		    काष्ठा ip_vs_conn *cp, पूर्णांक inout)
अणु
	काष्ठा iphdr *iph	 = ip_hdr(skb);
	अचिन्हित पूर्णांक icmp_offset = iph->ihl*4;
	काष्ठा icmphdr *icmph	 = (काष्ठा icmphdr *)(skb_network_header(skb) +
						      icmp_offset);
	काष्ठा iphdr *ciph	 = (काष्ठा iphdr *)(icmph + 1);

	अगर (inout) अणु
		iph->saddr = cp->vaddr.ip;
		ip_send_check(iph);
		ciph->daddr = cp->vaddr.ip;
		ip_send_check(ciph);
	पूर्ण अन्यथा अणु
		iph->daddr = cp->daddr.ip;
		ip_send_check(iph);
		ciph->saddr = cp->daddr.ip;
		ip_send_check(ciph);
	पूर्ण

	/* the TCP/UDP/SCTP port */
	अगर (IPPROTO_TCP == ciph->protocol || IPPROTO_UDP == ciph->protocol ||
	    IPPROTO_SCTP == ciph->protocol) अणु
		__be16 *ports = (व्योम *)ciph + ciph->ihl*4;

		अगर (inout)
			ports[1] = cp->vport;
		अन्यथा
			ports[0] = cp->dport;
	पूर्ण

	/* And finally the ICMP checksum */
	icmph->checksum = 0;
	icmph->checksum = ip_vs_checksum_complete(skb, icmp_offset);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (inout)
		IP_VS_DBG_PKT(11, AF_INET, pp, skb, (व्योम *)ciph - (व्योम *)iph,
			"Forwarding altered outgoing ICMP");
	अन्यथा
		IP_VS_DBG_PKT(11, AF_INET, pp, skb, (व्योम *)ciph - (व्योम *)iph,
			"Forwarding altered incoming ICMP");
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
व्योम ip_vs_nat_icmp_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		    काष्ठा ip_vs_conn *cp, पूर्णांक inout)
अणु
	काष्ठा ipv6hdr *iph	 = ipv6_hdr(skb);
	अचिन्हित पूर्णांक icmp_offset = 0;
	अचिन्हित पूर्णांक offs	 = 0; /* header offset*/
	पूर्णांक protocol;
	काष्ठा icmp6hdr *icmph;
	काष्ठा ipv6hdr *ciph;
	अचिन्हित लघु fragoffs;

	ipv6_find_hdr(skb, &icmp_offset, IPPROTO_ICMPV6, &fragoffs, शून्य);
	icmph = (काष्ठा icmp6hdr *)(skb_network_header(skb) + icmp_offset);
	offs = icmp_offset + माप(काष्ठा icmp6hdr);
	ciph = (काष्ठा ipv6hdr *)(skb_network_header(skb) + offs);

	protocol = ipv6_find_hdr(skb, &offs, -1, &fragoffs, शून्य);

	अगर (inout) अणु
		iph->saddr = cp->vaddr.in6;
		ciph->daddr = cp->vaddr.in6;
	पूर्ण अन्यथा अणु
		iph->daddr = cp->daddr.in6;
		ciph->saddr = cp->daddr.in6;
	पूर्ण

	/* the TCP/UDP/SCTP port */
	अगर (!fragoffs && (IPPROTO_TCP == protocol || IPPROTO_UDP == protocol ||
			  IPPROTO_SCTP == protocol)) अणु
		__be16 *ports = (व्योम *)(skb_network_header(skb) + offs);

		IP_VS_DBG(11, "%s() changed port %d to %d\n", __func__,
			      ntohs(inout ? ports[1] : ports[0]),
			      ntohs(inout ? cp->vport : cp->dport));
		अगर (inout)
			ports[1] = cp->vport;
		अन्यथा
			ports[0] = cp->dport;
	पूर्ण

	/* And finally the ICMP checksum */
	icmph->icmp6_cksum = ~csum_ipv6_magic(&iph->saddr, &iph->daddr,
					      skb->len - icmp_offset,
					      IPPROTO_ICMPV6, 0);
	skb->csum_start = skb_network_header(skb) - skb->head + icmp_offset;
	skb->csum_offset = दुरत्व(काष्ठा icmp6hdr, icmp6_cksum);
	skb->ip_summed = CHECKSUM_PARTIAL;

	अगर (inout)
		IP_VS_DBG_PKT(11, AF_INET6, pp, skb,
			      (व्योम *)ciph - (व्योम *)iph,
			      "Forwarding altered outgoing ICMPv6");
	अन्यथा
		IP_VS_DBG_PKT(11, AF_INET6, pp, skb,
			      (व्योम *)ciph - (व्योम *)iph,
			      "Forwarding altered incoming ICMPv6");
पूर्ण
#पूर्ण_अगर

/* Handle relevant response ICMP messages - क्रमward to the right
 * destination host.
 */
अटल पूर्णांक handle_response_icmp(पूर्णांक af, काष्ठा sk_buff *skb,
				जोड़ nf_inet_addr *snet,
				__u8 protocol, काष्ठा ip_vs_conn *cp,
				काष्ठा ip_vs_protocol *pp,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक ihl,
				अचिन्हित पूर्णांक hooknum)
अणु
	अचिन्हित पूर्णांक verdict = NF_DROP;

	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		जाओ after_nat;

	/* Ensure the checksum is correct */
	अगर (!skb_csum_unnecessary(skb) && ip_vs_checksum_complete(skb, ihl)) अणु
		/* Failed checksum! */
		IP_VS_DBG_BUF(1, "Forward ICMP: failed checksum from %s!\n",
			      IP_VS_DBG_ADDR(af, snet));
		जाओ out;
	पूर्ण

	अगर (IPPROTO_TCP == protocol || IPPROTO_UDP == protocol ||
	    IPPROTO_SCTP == protocol)
		offset += 2 * माप(__u16);
	अगर (skb_ensure_writable(skb, offset))
		जाओ out;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		ip_vs_nat_icmp_v6(skb, pp, cp, 1);
	अन्यथा
#पूर्ण_अगर
		ip_vs_nat_icmp(skb, pp, cp, 1);

	अगर (ip_vs_route_me_harder(cp->ipvs, af, skb, hooknum))
		जाओ out;

after_nat:
	/* करो the statistics and put it back */
	ip_vs_out_stats(cp, skb);

	skb->ipvs_property = 1;
	अगर (!(cp->flags & IP_VS_CONN_F_NFCT))
		ip_vs_notrack(skb);
	अन्यथा
		ip_vs_update_conntrack(skb, cp, 0);
	verdict = NF_ACCEPT;

out:
	__ip_vs_conn_put(cp);

	वापस verdict;
पूर्ण

/*
 *	Handle ICMP messages in the inside-to-outside direction (outgoing).
 *	Find any that might be relevant, check against existing connections.
 *	Currently handles error types - unreachable, quench, ttl exceeded.
 */
अटल पूर्णांक ip_vs_out_icmp(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb,
			  पूर्णांक *related, अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा iphdr *iph;
	काष्ठा icmphdr	_icmph, *ic;
	काष्ठा iphdr	_ciph, *cih;	/* The ip header contained within the ICMP */
	काष्ठा ip_vs_iphdr ciph;
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_protocol *pp;
	अचिन्हित पूर्णांक offset, ihl;
	जोड़ nf_inet_addr snet;

	*related = 1;

	/* reassemble IP fragments */
	अगर (ip_is_fragment(ip_hdr(skb))) अणु
		अगर (ip_vs_gather_frags(ipvs, skb, ip_vs_defrag_user(hooknum)))
			वापस NF_STOLEN;
	पूर्ण

	iph = ip_hdr(skb);
	offset = ihl = iph->ihl * 4;
	ic = skb_header_poपूर्णांकer(skb, offset, माप(_icmph), &_icmph);
	अगर (ic == शून्य)
		वापस NF_DROP;

	IP_VS_DBG(12, "Outgoing ICMP (%d,%d) %pI4->%pI4\n",
		  ic->type, ntohs(icmp_id(ic)),
		  &iph->saddr, &iph->daddr);

	/*
	 * Work through seeing अगर this is क्रम us.
	 * These checks are supposed to be in an order that means easy
	 * things are checked first to speed up processing.... however
	 * this means that some packets will manage to get a दीर्घ way
	 * करोwn this stack and then be rejected, but that's lअगरe.
	 */
	अगर ((ic->type != ICMP_DEST_UNREACH) &&
	    (ic->type != ICMP_SOURCE_QUENCH) &&
	    (ic->type != ICMP_TIME_EXCEEDED)) अणु
		*related = 0;
		वापस NF_ACCEPT;
	पूर्ण

	/* Now find the contained IP header */
	offset += माप(_icmph);
	cih = skb_header_poपूर्णांकer(skb, offset, माप(_ciph), &_ciph);
	अगर (cih == शून्य)
		वापस NF_ACCEPT; /* The packet looks wrong, ignore */

	pp = ip_vs_proto_get(cih->protocol);
	अगर (!pp)
		वापस NF_ACCEPT;

	/* Is the embedded protocol header present? */
	अगर (unlikely(cih->frag_off & htons(IP_OFFSET) &&
		     pp->करोnt_defrag))
		वापस NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET, pp, skb, offset,
		      "Checking outgoing ICMP for");

	ip_vs_fill_iph_skb_icmp(AF_INET, skb, offset, true, &ciph);

	/* The embedded headers contain source and dest in reverse order */
	cp = INसूचीECT_CALL_1(pp->conn_out_get, ip_vs_conn_out_get_proto,
			     ipvs, AF_INET, skb, &ciph);
	अगर (!cp)
		वापस NF_ACCEPT;

	snet.ip = iph->saddr;
	वापस handle_response_icmp(AF_INET, skb, &snet, cih->protocol, cp,
				    pp, ciph.len, ihl, hooknum);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल पूर्णांक ip_vs_out_icmp_v6(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb,
			     पूर्णांक *related,  अचिन्हित पूर्णांक hooknum,
			     काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा icmp6hdr	_icmph, *ic;
	काष्ठा ip_vs_iphdr ciph = अणु.flags = 0, .fragoffs = 0पूर्ण;/*Contained IP */
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_protocol *pp;
	जोड़ nf_inet_addr snet;
	अचिन्हित पूर्णांक offset;

	*related = 1;
	ic = frag_safe_skb_hp(skb, ipvsh->len, माप(_icmph), &_icmph);
	अगर (ic == शून्य)
		वापस NF_DROP;

	/*
	 * Work through seeing अगर this is क्रम us.
	 * These checks are supposed to be in an order that means easy
	 * things are checked first to speed up processing.... however
	 * this means that some packets will manage to get a दीर्घ way
	 * करोwn this stack and then be rejected, but that's lअगरe.
	 */
	अगर (ic->icmp6_type & ICMPV6_INFOMSG_MASK) अणु
		*related = 0;
		वापस NF_ACCEPT;
	पूर्ण
	/* Fragment header that is beक्रमe ICMP header tells us that:
	 * it's not an error message since they can't be fragmented.
	 */
	अगर (ipvsh->flags & IP6_FH_F_FRAG)
		वापस NF_DROP;

	IP_VS_DBG(8, "Outgoing ICMPv6 (%d,%d) %pI6c->%pI6c\n",
		  ic->icmp6_type, ntohs(icmpv6_id(ic)),
		  &ipvsh->saddr, &ipvsh->daddr);

	अगर (!ip_vs_fill_iph_skb_icmp(AF_INET6, skb, ipvsh->len + माप(_icmph),
				     true, &ciph))
		वापस NF_ACCEPT; /* The packet looks wrong, ignore */

	pp = ip_vs_proto_get(ciph.protocol);
	अगर (!pp)
		वापस NF_ACCEPT;

	/* The embedded headers contain source and dest in reverse order */
	cp = INसूचीECT_CALL_1(pp->conn_out_get, ip_vs_conn_out_get_proto,
			     ipvs, AF_INET6, skb, &ciph);
	अगर (!cp)
		वापस NF_ACCEPT;

	snet.in6 = ciph.saddr.in6;
	offset = ciph.len;
	वापस handle_response_icmp(AF_INET6, skb, &snet, ciph.protocol, cp,
				    pp, offset, माप(काष्ठा ipv6hdr),
				    hooknum);
पूर्ण
#पूर्ण_अगर

/*
 * Check अगर sctp chunc is ABORT chunk
 */
अटल अंतरभूत पूर्णांक is_sctp_पात(स्थिर काष्ठा sk_buff *skb, पूर्णांक nh_len)
अणु
	काष्ठा sctp_chunkhdr *sch, schunk;
	sch = skb_header_poपूर्णांकer(skb, nh_len + माप(काष्ठा sctphdr),
				 माप(schunk), &schunk);
	अगर (sch == शून्य)
		वापस 0;
	अगर (sch->type == SCTP_CID_ABORT)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_tcp_reset(स्थिर काष्ठा sk_buff *skb, पूर्णांक nh_len)
अणु
	काष्ठा tcphdr _tcph, *th;

	th = skb_header_poपूर्णांकer(skb, nh_len, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस 0;
	वापस th->rst;
पूर्ण

अटल अंतरभूत bool is_new_conn(स्थिर काष्ठा sk_buff *skb,
			       काष्ठा ip_vs_iphdr *iph)
अणु
	चयन (iph->protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _tcph, *th;

		th = skb_header_poपूर्णांकer(skb, iph->len, माप(_tcph), &_tcph);
		अगर (th == शून्य)
			वापस false;
		वापस th->syn;
	पूर्ण
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctp_chunkhdr *sch, schunk;

		sch = skb_header_poपूर्णांकer(skb, iph->len + माप(काष्ठा sctphdr),
					 माप(schunk), &schunk);
		अगर (sch == शून्य)
			वापस false;
		वापस sch->type == SCTP_CID_INIT;
	पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_new_conn_expected(स्थिर काष्ठा ip_vs_conn *cp,
					पूर्णांक conn_reuse_mode)
अणु
	/* Controlled (FTP DATA or persistence)? */
	अगर (cp->control)
		वापस false;

	चयन (cp->protocol) अणु
	हाल IPPROTO_TCP:
		वापस (cp->state == IP_VS_TCP_S_TIME_WAIT) ||
		       (cp->state == IP_VS_TCP_S_CLOSE) ||
			((conn_reuse_mode & 2) &&
			 (cp->state == IP_VS_TCP_S_FIN_WAIT) &&
			 (cp->flags & IP_VS_CONN_F_NOOUTPUT));
	हाल IPPROTO_SCTP:
		वापस cp->state == IP_VS_SCTP_S_CLOSED;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* Generic function to create new connections क्रम outgoing RS packets
 *
 * Pre-requisites क्रम successful connection creation:
 * 1) Virtual Service is NOT fwmark based:
 *    In fwmark-VS actual vaddr and vport are unknown to IPVS
 * 2) Real Server and Virtual Service were NOT configured without port:
 *    This is to allow match of dअगरferent VS to the same RS ip-addr
 */
काष्ठा ip_vs_conn *ip_vs_new_conn_out(काष्ठा ip_vs_service *svc,
				      काष्ठा ip_vs_dest *dest,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा ip_vs_iphdr *iph,
				      __be16 dport,
				      __be16 cport)
अणु
	काष्ठा ip_vs_conn_param param;
	काष्ठा ip_vs_conn *ct = शून्य, *cp = शून्य;
	स्थिर जोड़ nf_inet_addr *vaddr, *daddr, *caddr;
	जोड़ nf_inet_addr snet;
	__be16 vport;
	अचिन्हित पूर्णांक flags;

	EnterFunction(12);
	vaddr = &svc->addr;
	vport = svc->port;
	daddr = &iph->saddr;
	caddr = &iph->daddr;

	/* check pre-requisites are satisfied */
	अगर (svc->fwmark)
		वापस शून्य;
	अगर (!vport || !dport)
		वापस शून्य;

	/* क्रम persistent service first create connection ढाँचा */
	अगर (svc->flags & IP_VS_SVC_F_PERSISTENT) अणु
		/* apply neपंचांगask the same way ingress-side करोes */
#अगर_घोषित CONFIG_IP_VS_IPV6
		अगर (svc->af == AF_INET6)
			ipv6_addr_prefix(&snet.in6, &caddr->in6,
					 (__क्रमce __u32)svc->neपंचांगask);
		अन्यथा
#पूर्ण_अगर
			snet.ip = caddr->ip & svc->neपंचांगask;
		/* fill params and create ढाँचा अगर not existent */
		अगर (ip_vs_conn_fill_param_persist(svc, skb, iph->protocol,
						  &snet, 0, vaddr,
						  vport, &param) < 0)
			वापस शून्य;
		ct = ip_vs_ct_in_get(&param);
		/* check अगर ढाँचा exists and poपूर्णांकs to the same dest */
		अगर (!ct || !ip_vs_check_ढाँचा(ct, dest)) अणु
			ct = ip_vs_conn_new(&param, dest->af, daddr, dport,
					    IP_VS_CONN_F_TEMPLATE, dest, 0);
			अगर (!ct) अणु
				kमुक्त(param.pe_data);
				वापस शून्य;
			पूर्ण
			ct->समयout = svc->समयout;
		पूर्ण अन्यथा अणु
			kमुक्त(param.pe_data);
		पूर्ण
	पूर्ण

	/* connection flags */
	flags = ((svc->flags & IP_VS_SVC_F_ONEPACKET) &&
		 iph->protocol == IPPROTO_UDP) ? IP_VS_CONN_F_ONE_PACKET : 0;
	/* create connection */
	ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol,
			      caddr, cport, vaddr, vport, &param);
	cp = ip_vs_conn_new(&param, dest->af, daddr, dport, flags, dest, 0);
	अगर (!cp) अणु
		अगर (ct)
			ip_vs_conn_put(ct);
		वापस शून्य;
	पूर्ण
	अगर (ct) अणु
		ip_vs_control_add(cp, ct);
		ip_vs_conn_put(ct);
	पूर्ण
	ip_vs_conn_stats(cp, svc);

	/* वापस connection (will be used to handle outgoing packet) */
	IP_VS_DBG_BUF(6, "New connection RS-initiated:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->flags:%X conn->refcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->af, &cp->daddr), ntohs(cp->dport),
		      cp->flags, refcount_पढ़ो(&cp->refcnt));
	LeaveFunction(12);
	वापस cp;
पूर्ण

/* Handle outgoing packets which are considered requests initiated by
 * real servers, so that subsequent responses from बाह्यal client can be
 * routed to the right real server.
 * Used also क्रम outgoing responses in OPS mode.
 *
 * Connection management is handled by persistent-engine specअगरic callback.
 */
अटल काष्ठा ip_vs_conn *__ip_vs_rs_conn_out(अचिन्हित पूर्णांक hooknum,
					      काष्ठा netns_ipvs *ipvs,
					      पूर्णांक af, काष्ठा sk_buff *skb,
					      स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_conn *cp = शून्य;
	__be16 _ports[2], *pptr;

	अगर (hooknum == NF_INET_LOCAL_IN)
		वापस शून्य;

	pptr = frag_safe_skb_hp(skb, iph->len,
				माप(_ports), _ports);
	अगर (!pptr)
		वापस शून्य;

	dest = ip_vs_find_real_service(ipvs, af, iph->protocol,
				       &iph->saddr, pptr[0]);
	अगर (dest) अणु
		काष्ठा ip_vs_service *svc;
		काष्ठा ip_vs_pe *pe;

		svc = rcu_dereference(dest->svc);
		अगर (svc) अणु
			pe = rcu_dereference(svc->pe);
			अगर (pe && pe->conn_out)
				cp = pe->conn_out(svc, dest, skb, iph,
						  pptr[0], pptr[1]);
		पूर्ण
	पूर्ण

	वापस cp;
पूर्ण

/* Handle response packets: reग_लिखो addresses and send away...
 */
अटल अचिन्हित पूर्णांक
handle_response(पूर्णांक af, काष्ठा sk_buff *skb, काष्ठा ip_vs_proto_data *pd,
		काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph,
		अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा ip_vs_protocol *pp = pd->pp;

	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
		जाओ after_nat;

	IP_VS_DBG_PKT(11, af, pp, skb, iph->off, "Outgoing packet");

	अगर (skb_ensure_writable(skb, iph->len))
		जाओ drop;

	/* mangle the packet */
	अगर (pp->snat_handler &&
	    !SNAT_CALL(pp->snat_handler, skb, pp, cp, iph))
		जाओ drop;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		ipv6_hdr(skb)->saddr = cp->vaddr.in6;
	अन्यथा
#पूर्ण_अगर
	अणु
		ip_hdr(skb)->saddr = cp->vaddr.ip;
		ip_send_check(ip_hdr(skb));
	पूर्ण

	/*
	 * nf_iterate करोes not expect change in the skb->dst->dev.
	 * It looks like it is not fatal to enable this code क्रम hooks
	 * where our handlers are at the end of the chain list and
	 * when all next handlers use skb->dst->dev and not outdev.
	 * It will definitely route properly the inout NAT traffic
	 * when multiple paths are used.
	 */

	/* For policy routing, packets originating from this
	 * machine itself may be routed dअगरferently to packets
	 * passing through.  We want this packet to be routed as
	 * अगर it came from this machine itself.  So re-compute
	 * the routing inक्रमmation.
	 */
	अगर (ip_vs_route_me_harder(cp->ipvs, af, skb, hooknum))
		जाओ drop;

	IP_VS_DBG_PKT(10, af, pp, skb, iph->off, "After SNAT");

after_nat:
	ip_vs_out_stats(cp, skb);
	ip_vs_set_state(cp, IP_VS_सूची_OUTPUT, skb, pd);
	skb->ipvs_property = 1;
	अगर (!(cp->flags & IP_VS_CONN_F_NFCT))
		ip_vs_notrack(skb);
	अन्यथा
		ip_vs_update_conntrack(skb, cp, 0);
	ip_vs_conn_put(cp);

	LeaveFunction(11);
	वापस NF_ACCEPT;

drop:
	ip_vs_conn_put(cp);
	kमुक्त_skb(skb);
	LeaveFunction(11);
	वापस NF_STOLEN;
पूर्ण

/*
 *	Check अगर outgoing packet beदीर्घs to the established ip_vs_conn.
 */
अटल अचिन्हित पूर्णांक
ip_vs_out(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक hooknum, काष्ठा sk_buff *skb, पूर्णांक af)
अणु
	काष्ठा ip_vs_iphdr iph;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_proto_data *pd;
	काष्ठा ip_vs_conn *cp;
	काष्ठा sock *sk;

	EnterFunction(11);

	/* Alपढ़ोy marked as IPVS request or reply? */
	अगर (skb->ipvs_property)
		वापस NF_ACCEPT;

	sk = skb_to_full_sk(skb);
	/* Bad... Do not अवरोध raw sockets */
	अगर (unlikely(sk && hooknum == NF_INET_LOCAL_OUT &&
		     af == AF_INET)) अणु

		अगर (sk->sk_family == PF_INET && inet_sk(sk)->nodefrag)
			वापस NF_ACCEPT;
	पूर्ण

	अगर (unlikely(!skb_dst(skb)))
		वापस NF_ACCEPT;

	अगर (!ipvs->enable)
		वापस NF_ACCEPT;

	ip_vs_fill_iph_skb(af, skb, false, &iph);
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6) अणु
		अगर (unlikely(iph.protocol == IPPROTO_ICMPV6)) अणु
			पूर्णांक related;
			पूर्णांक verdict = ip_vs_out_icmp_v6(ipvs, skb, &related,
							hooknum, &iph);

			अगर (related)
				वापस verdict;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (unlikely(iph.protocol == IPPROTO_ICMP)) अणु
			पूर्णांक related;
			पूर्णांक verdict = ip_vs_out_icmp(ipvs, skb, &related, hooknum);

			अगर (related)
				वापस verdict;
		पूर्ण

	pd = ip_vs_proto_data_get(ipvs, iph.protocol);
	अगर (unlikely(!pd))
		वापस NF_ACCEPT;
	pp = pd->pp;

	/* reassemble IP fragments */
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET)
#पूर्ण_अगर
		अगर (unlikely(ip_is_fragment(ip_hdr(skb)) && !pp->करोnt_defrag)) अणु
			अगर (ip_vs_gather_frags(ipvs, skb,
					       ip_vs_defrag_user(hooknum)))
				वापस NF_STOLEN;

			ip_vs_fill_iph_skb(AF_INET, skb, false, &iph);
		पूर्ण

	/*
	 * Check अगर the packet beदीर्घs to an existing entry
	 */
	cp = INसूचीECT_CALL_1(pp->conn_out_get, ip_vs_conn_out_get_proto,
			     ipvs, af, skb, &iph);

	अगर (likely(cp))
		वापस handle_response(af, skb, pd, cp, &iph, hooknum);

	/* Check क्रम real-server-started requests */
	अगर (atomic_पढ़ो(&ipvs->conn_out_counter)) अणु
		/* Currently only क्रम UDP:
		 * connection oriented protocols typically use
		 * ephemeral ports क्रम outgoing connections, so
		 * related incoming responses would not match any VS
		 */
		अगर (pp->protocol == IPPROTO_UDP) अणु
			cp = __ip_vs_rs_conn_out(hooknum, ipvs, af, skb, &iph);
			अगर (likely(cp))
				वापस handle_response(af, skb, pd, cp, &iph,
						       hooknum);
		पूर्ण
	पूर्ण

	अगर (sysctl_nat_icmp_send(ipvs) &&
	    (pp->protocol == IPPROTO_TCP ||
	     pp->protocol == IPPROTO_UDP ||
	     pp->protocol == IPPROTO_SCTP)) अणु
		__be16 _ports[2], *pptr;

		pptr = frag_safe_skb_hp(skb, iph.len,
					 माप(_ports), _ports);
		अगर (pptr == शून्य)
			वापस NF_ACCEPT;	/* Not क्रम me */
		अगर (ip_vs_has_real_service(ipvs, af, iph.protocol, &iph.saddr,
					   pptr[0])) अणु
			/*
			 * Notअगरy the real server: there is no
			 * existing entry अगर it is not RST
			 * packet or not TCP packet.
			 */
			अगर ((iph.protocol != IPPROTO_TCP &&
			     iph.protocol != IPPROTO_SCTP)
			     || ((iph.protocol == IPPROTO_TCP
				  && !is_tcp_reset(skb, iph.len))
				 || (iph.protocol == IPPROTO_SCTP
					&& !is_sctp_पात(skb,
						iph.len)))) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
				अगर (af == AF_INET6) अणु
					अगर (!skb->dev)
						skb->dev = ipvs->net->loopback_dev;
					icmpv6_send(skb,
						    ICMPV6_DEST_UNREACH,
						    ICMPV6_PORT_UNREACH,
						    0);
				पूर्ण अन्यथा
#पूर्ण_अगर
					icmp_send(skb,
						  ICMP_DEST_UNREACH,
						  ICMP_PORT_UNREACH, 0);
				वापस NF_DROP;
			पूर्ण
		पूर्ण
	पूर्ण

	IP_VS_DBG_PKT(12, af, pp, skb, iph.off,
		      "ip_vs_out: packet continues traversal as normal");
	वापस NF_ACCEPT;
पूर्ण

/*
 *	It is hooked at the NF_INET_FORWARD and NF_INET_LOCAL_IN chain,
 *	used only क्रम VS/NAT.
 *	Check अगर packet is reply क्रम established ip_vs_conn.
 */
अटल अचिन्हित पूर्णांक
ip_vs_reply4(व्योम *priv, काष्ठा sk_buff *skb,
	     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_out(net_ipvs(state->net), state->hook, skb, AF_INET);
पूर्ण

/*
 *	It is hooked at the NF_INET_LOCAL_OUT chain, used only क्रम VS/NAT.
 *	Check अगर packet is reply क्रम established ip_vs_conn.
 */
अटल अचिन्हित पूर्णांक
ip_vs_local_reply4(व्योम *priv, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_out(net_ipvs(state->net), state->hook, skb, AF_INET);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6

/*
 *	It is hooked at the NF_INET_FORWARD and NF_INET_LOCAL_IN chain,
 *	used only क्रम VS/NAT.
 *	Check अगर packet is reply क्रम established ip_vs_conn.
 */
अटल अचिन्हित पूर्णांक
ip_vs_reply6(व्योम *priv, काष्ठा sk_buff *skb,
	     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_out(net_ipvs(state->net), state->hook, skb, AF_INET6);
पूर्ण

/*
 *	It is hooked at the NF_INET_LOCAL_OUT chain, used only क्रम VS/NAT.
 *	Check अगर packet is reply क्रम established ip_vs_conn.
 */
अटल अचिन्हित पूर्णांक
ip_vs_local_reply6(व्योम *priv, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_out(net_ipvs(state->net), state->hook, skb, AF_INET6);
पूर्ण

#पूर्ण_अगर

अटल अचिन्हित पूर्णांक
ip_vs_try_to_schedule(काष्ठा netns_ipvs *ipvs, पूर्णांक af, काष्ठा sk_buff *skb,
		      काष्ठा ip_vs_proto_data *pd,
		      पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
		      काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_protocol *pp = pd->pp;

	अगर (!iph->fragoffs) अणु
		/* No (second) fragments need to enter here, as nf_defrag_ipv6
		 * replayed fragment zero will alपढ़ोy have created the cp
		 */

		/* Schedule and create new connection entry पूर्णांकo cpp */
		अगर (!pp->conn_schedule(ipvs, af, skb, pd, verdict, cpp, iph))
			वापस 0;
	पूर्ण

	अगर (unlikely(!*cpp)) अणु
		/* sorry, all this trouble क्रम a no-hit :) */
		IP_VS_DBG_PKT(12, af, pp, skb, iph->off,
			      "ip_vs_in: packet continues traversal as normal");

		/* Fragment couldn't be mapped to a conn entry */
		अगर (iph->fragoffs)
			IP_VS_DBG_PKT(7, af, pp, skb, iph->off,
				      "unhandled fragment");

		*verdict = NF_ACCEPT;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Check the UDP tunnel and वापस its header length */
अटल पूर्णांक ipvs_udp_decap(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक offset, __u16 af,
			  स्थिर जोड़ nf_inet_addr *daddr, __u8 *proto)
अणु
	काष्ठा udphdr _udph, *udph;
	काष्ठा ip_vs_dest *dest;

	udph = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
	अगर (!udph)
		जाओ unk;
	offset += माप(काष्ठा udphdr);
	dest = ip_vs_find_tunnel(ipvs, af, daddr, udph->dest);
	अगर (!dest)
		जाओ unk;
	अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		काष्ठा guehdr _gueh, *gueh;

		gueh = skb_header_poपूर्णांकer(skb, offset, माप(_gueh), &_gueh);
		अगर (!gueh)
			जाओ unk;
		अगर (gueh->control != 0 || gueh->version != 0)
			जाओ unk;
		/* Later we can support also IPPROTO_IPV6 */
		अगर (gueh->proto_ctype != IPPROTO_IPIP)
			जाओ unk;
		*proto = gueh->proto_ctype;
		वापस माप(काष्ठा udphdr) + माप(काष्ठा guehdr) +
		       (gueh->hlen << 2);
	पूर्ण

unk:
	वापस 0;
पूर्ण

/* Check the GRE tunnel and वापस its header length */
अटल पूर्णांक ipvs_gre_decap(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक offset, __u16 af,
			  स्थिर जोड़ nf_inet_addr *daddr, __u8 *proto)
अणु
	काष्ठा gre_base_hdr _greh, *greh;
	काष्ठा ip_vs_dest *dest;

	greh = skb_header_poपूर्णांकer(skb, offset, माप(_greh), &_greh);
	अगर (!greh)
		जाओ unk;
	dest = ip_vs_find_tunnel(ipvs, af, daddr, 0);
	अगर (!dest)
		जाओ unk;
	अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
		__be16 type;

		/* Only support version 0 and C (csum) */
		अगर ((greh->flags & ~GRE_CSUM) != 0)
			जाओ unk;
		type = greh->protocol;
		/* Later we can support also IPPROTO_IPV6 */
		अगर (type != htons(ETH_P_IP))
			जाओ unk;
		*proto = IPPROTO_IPIP;
		वापस gre_calc_hlen(gre_flags_to_tnl_flags(greh->flags));
	पूर्ण

unk:
	वापस 0;
पूर्ण

/*
 *	Handle ICMP messages in the outside-to-inside direction (incoming).
 *	Find any that might be relevant, check against existing connections,
 *	क्रमward to the right destination host अगर relevant.
 *	Currently handles error types - unreachable, quench, ttl exceeded.
 */
अटल पूर्णांक
ip_vs_in_icmp(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb, पूर्णांक *related,
	      अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा iphdr *iph;
	काष्ठा icmphdr	_icmph, *ic;
	काष्ठा iphdr	_ciph, *cih;	/* The ip header contained within the ICMP */
	काष्ठा ip_vs_iphdr ciph;
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_proto_data *pd;
	अचिन्हित पूर्णांक offset, offset2, ihl, verdict;
	bool tunnel, new_cp = false;
	जोड़ nf_inet_addr *raddr;
	अक्षर *outer_proto = "IPIP";

	*related = 1;

	/* reassemble IP fragments */
	अगर (ip_is_fragment(ip_hdr(skb))) अणु
		अगर (ip_vs_gather_frags(ipvs, skb, ip_vs_defrag_user(hooknum)))
			वापस NF_STOLEN;
	पूर्ण

	iph = ip_hdr(skb);
	offset = ihl = iph->ihl * 4;
	ic = skb_header_poपूर्णांकer(skb, offset, माप(_icmph), &_icmph);
	अगर (ic == शून्य)
		वापस NF_DROP;

	IP_VS_DBG(12, "Incoming ICMP (%d,%d) %pI4->%pI4\n",
		  ic->type, ntohs(icmp_id(ic)),
		  &iph->saddr, &iph->daddr);

	/*
	 * Work through seeing अगर this is क्रम us.
	 * These checks are supposed to be in an order that means easy
	 * things are checked first to speed up processing.... however
	 * this means that some packets will manage to get a दीर्घ way
	 * करोwn this stack and then be rejected, but that's lअगरe.
	 */
	अगर ((ic->type != ICMP_DEST_UNREACH) &&
	    (ic->type != ICMP_SOURCE_QUENCH) &&
	    (ic->type != ICMP_TIME_EXCEEDED)) अणु
		*related = 0;
		वापस NF_ACCEPT;
	पूर्ण

	/* Now find the contained IP header */
	offset += माप(_icmph);
	cih = skb_header_poपूर्णांकer(skb, offset, माप(_ciph), &_ciph);
	अगर (cih == शून्य)
		वापस NF_ACCEPT; /* The packet looks wrong, ignore */
	raddr = (जोड़ nf_inet_addr *)&cih->daddr;

	/* Special हाल क्रम errors क्रम IPIP/UDP/GRE tunnel packets */
	tunnel = false;
	अगर (cih->protocol == IPPROTO_IPIP) अणु
		काष्ठा ip_vs_dest *dest;

		अगर (unlikely(cih->frag_off & htons(IP_OFFSET)))
			वापस NF_ACCEPT;
		/* Error क्रम our IPIP must arrive at LOCAL_IN */
		अगर (!(skb_rtable(skb)->rt_flags & RTCF_LOCAL))
			वापस NF_ACCEPT;
		dest = ip_vs_find_tunnel(ipvs, AF_INET, raddr, 0);
		/* Only क्रम known tunnel */
		अगर (!dest || dest->tun_type != IP_VS_CONN_F_TUNNEL_TYPE_IPIP)
			वापस NF_ACCEPT;
		offset += cih->ihl * 4;
		cih = skb_header_poपूर्णांकer(skb, offset, माप(_ciph), &_ciph);
		अगर (cih == शून्य)
			वापस NF_ACCEPT; /* The packet looks wrong, ignore */
		tunnel = true;
	पूर्ण अन्यथा अगर ((cih->protocol == IPPROTO_UDP ||	/* Can be UDP encap */
		    cih->protocol == IPPROTO_GRE) &&	/* Can be GRE encap */
		   /* Error क्रम our tunnel must arrive at LOCAL_IN */
		   (skb_rtable(skb)->rt_flags & RTCF_LOCAL)) अणु
		__u8 iproto;
		पूर्णांक ulen;

		/* Non-first fragment has no UDP/GRE header */
		अगर (unlikely(cih->frag_off & htons(IP_OFFSET)))
			वापस NF_ACCEPT;
		offset2 = offset + cih->ihl * 4;
		अगर (cih->protocol == IPPROTO_UDP) अणु
			ulen = ipvs_udp_decap(ipvs, skb, offset2, AF_INET,
					      raddr, &iproto);
			outer_proto = "UDP";
		पूर्ण अन्यथा अणु
			ulen = ipvs_gre_decap(ipvs, skb, offset2, AF_INET,
					      raddr, &iproto);
			outer_proto = "GRE";
		पूर्ण
		अगर (ulen > 0) अणु
			/* Skip IP and UDP/GRE tunnel headers */
			offset = offset2 + ulen;
			/* Now we should be at the original IP header */
			cih = skb_header_poपूर्णांकer(skb, offset, माप(_ciph),
						 &_ciph);
			अगर (cih && cih->version == 4 && cih->ihl >= 5 &&
			    iproto == IPPROTO_IPIP)
				tunnel = true;
			अन्यथा
				वापस NF_ACCEPT;
		पूर्ण
	पूर्ण

	pd = ip_vs_proto_data_get(ipvs, cih->protocol);
	अगर (!pd)
		वापस NF_ACCEPT;
	pp = pd->pp;

	/* Is the embedded protocol header present? */
	अगर (unlikely(cih->frag_off & htons(IP_OFFSET) &&
		     pp->करोnt_defrag))
		वापस NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET, pp, skb, offset,
		      "Checking incoming ICMP for");

	offset2 = offset;
	ip_vs_fill_iph_skb_icmp(AF_INET, skb, offset, !tunnel, &ciph);
	offset = ciph.len;

	/* The embedded headers contain source and dest in reverse order.
	 * For IPIP/UDP/GRE tunnel this is error क्रम request, not क्रम reply.
	 */
	cp = INसूचीECT_CALL_1(pp->conn_in_get, ip_vs_conn_in_get_proto,
			     ipvs, AF_INET, skb, &ciph);

	अगर (!cp) अणु
		पूर्णांक v;

		अगर (tunnel || !sysctl_schedule_icmp(ipvs))
			वापस NF_ACCEPT;

		अगर (!ip_vs_try_to_schedule(ipvs, AF_INET, skb, pd, &v, &cp, &ciph))
			वापस v;
		new_cp = true;
	पूर्ण

	verdict = NF_DROP;

	/* Ensure the checksum is correct */
	अगर (!skb_csum_unnecessary(skb) && ip_vs_checksum_complete(skb, ihl)) अणु
		/* Failed checksum! */
		IP_VS_DBG(1, "Incoming ICMP: failed checksum from %pI4!\n",
			  &iph->saddr);
		जाओ out;
	पूर्ण

	अगर (tunnel) अणु
		__be32 info = ic->un.gateway;
		__u8 type = ic->type;
		__u8 code = ic->code;

		/* Update the MTU */
		अगर (ic->type == ICMP_DEST_UNREACH &&
		    ic->code == ICMP_FRAG_NEEDED) अणु
			काष्ठा ip_vs_dest *dest = cp->dest;
			u32 mtu = ntohs(ic->un.frag.mtu);
			__be16 frag_off = cih->frag_off;

			/* Strip outer IP and ICMP, go to IPIP/UDP/GRE header */
			अगर (pskb_pull(skb, ihl + माप(_icmph)) == शून्य)
				जाओ ignore_tunnel;
			offset2 -= ihl + माप(_icmph);
			skb_reset_network_header(skb);
			IP_VS_DBG(12, "ICMP for %s %pI4->%pI4: mtu=%u\n",
				  outer_proto, &ip_hdr(skb)->saddr,
				  &ip_hdr(skb)->daddr, mtu);
			ipv4_update_pmtu(skb, ipvs->net, mtu, 0, 0);
			/* Client uses PMTUD? */
			अगर (!(frag_off & htons(IP_DF)))
				जाओ ignore_tunnel;
			/* Prefer the resulting PMTU */
			अगर (dest) अणु
				काष्ठा ip_vs_dest_dst *dest_dst;

				dest_dst = rcu_dereference(dest->dest_dst);
				अगर (dest_dst)
					mtu = dst_mtu(dest_dst->dst_cache);
			पूर्ण
			अगर (mtu > 68 + माप(काष्ठा iphdr))
				mtu -= माप(काष्ठा iphdr);
			info = htonl(mtu);
		पूर्ण
		/* Strip outer IP, ICMP and IPIP/UDP/GRE, go to IP header of
		 * original request.
		 */
		अगर (pskb_pull(skb, offset2) == शून्य)
			जाओ ignore_tunnel;
		skb_reset_network_header(skb);
		IP_VS_DBG(12, "Sending ICMP for %pI4->%pI4: t=%u, c=%u, i=%u\n",
			&ip_hdr(skb)->saddr, &ip_hdr(skb)->daddr,
			type, code, ntohl(info));
		icmp_send(skb, type, code, info);
		/* ICMP can be लघुer but anyways, account it */
		ip_vs_out_stats(cp, skb);

ignore_tunnel:
		consume_skb(skb);
		verdict = NF_STOLEN;
		जाओ out;
	पूर्ण

	/* करो the statistics and put it back */
	ip_vs_in_stats(cp, skb);
	अगर (IPPROTO_TCP == cih->protocol || IPPROTO_UDP == cih->protocol ||
	    IPPROTO_SCTP == cih->protocol)
		offset += 2 * माप(__u16);
	verdict = ip_vs_icmp_xmit(skb, cp, pp, offset, hooknum, &ciph);

out:
	अगर (likely(!new_cp))
		__ip_vs_conn_put(cp);
	अन्यथा
		ip_vs_conn_put(cp);

	वापस verdict;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल पूर्णांक ip_vs_in_icmp_v6(काष्ठा netns_ipvs *ipvs, काष्ठा sk_buff *skb,
			    पूर्णांक *related, अचिन्हित पूर्णांक hooknum,
			    काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा icmp6hdr	_icmph, *ic;
	काष्ठा ip_vs_iphdr ciph = अणु.flags = 0, .fragoffs = 0पूर्ण;/*Contained IP */
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_proto_data *pd;
	अचिन्हित पूर्णांक offset, verdict;
	bool new_cp = false;

	*related = 1;

	ic = frag_safe_skb_hp(skb, iph->len, माप(_icmph), &_icmph);
	अगर (ic == शून्य)
		वापस NF_DROP;

	/*
	 * Work through seeing अगर this is क्रम us.
	 * These checks are supposed to be in an order that means easy
	 * things are checked first to speed up processing.... however
	 * this means that some packets will manage to get a दीर्घ way
	 * करोwn this stack and then be rejected, but that's lअगरe.
	 */
	अगर (ic->icmp6_type & ICMPV6_INFOMSG_MASK) अणु
		*related = 0;
		वापस NF_ACCEPT;
	पूर्ण
	/* Fragment header that is beक्रमe ICMP header tells us that:
	 * it's not an error message since they can't be fragmented.
	 */
	अगर (iph->flags & IP6_FH_F_FRAG)
		वापस NF_DROP;

	IP_VS_DBG(8, "Incoming ICMPv6 (%d,%d) %pI6c->%pI6c\n",
		  ic->icmp6_type, ntohs(icmpv6_id(ic)),
		  &iph->saddr, &iph->daddr);

	offset = iph->len + माप(_icmph);
	अगर (!ip_vs_fill_iph_skb_icmp(AF_INET6, skb, offset, true, &ciph))
		वापस NF_ACCEPT;

	pd = ip_vs_proto_data_get(ipvs, ciph.protocol);
	अगर (!pd)
		वापस NF_ACCEPT;
	pp = pd->pp;

	/* Cannot handle fragmented embedded protocol */
	अगर (ciph.fragoffs)
		वापस NF_ACCEPT;

	IP_VS_DBG_PKT(11, AF_INET6, pp, skb, offset,
		      "Checking incoming ICMPv6 for");

	/* The embedded headers contain source and dest in reverse order
	 * अगर not from localhost
	 */
	cp = INसूचीECT_CALL_1(pp->conn_in_get, ip_vs_conn_in_get_proto,
			     ipvs, AF_INET6, skb, &ciph);

	अगर (!cp) अणु
		पूर्णांक v;

		अगर (!sysctl_schedule_icmp(ipvs))
			वापस NF_ACCEPT;

		अगर (!ip_vs_try_to_schedule(ipvs, AF_INET6, skb, pd, &v, &cp, &ciph))
			वापस v;

		new_cp = true;
	पूर्ण

	/* VS/TUN, VS/DR and LOCALNODE just let it go */
	अगर ((hooknum == NF_INET_LOCAL_OUT) &&
	    (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)) अणु
		verdict = NF_ACCEPT;
		जाओ out;
	पूर्ण

	/* करो the statistics and put it back */
	ip_vs_in_stats(cp, skb);

	/* Need to mangle contained IPv6 header in ICMPv6 packet */
	offset = ciph.len;
	अगर (IPPROTO_TCP == ciph.protocol || IPPROTO_UDP == ciph.protocol ||
	    IPPROTO_SCTP == ciph.protocol)
		offset += 2 * माप(__u16); /* Also mangle ports */

	verdict = ip_vs_icmp_xmit_v6(skb, cp, pp, offset, hooknum, &ciph);

out:
	अगर (likely(!new_cp))
		__ip_vs_conn_put(cp);
	अन्यथा
		ip_vs_conn_put(cp);

	वापस verdict;
पूर्ण
#पूर्ण_अगर


/*
 *	Check अगर it's क्रम भव services, look it up,
 *	and send it on its way...
 */
अटल अचिन्हित पूर्णांक
ip_vs_in(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक hooknum, काष्ठा sk_buff *skb, पूर्णांक af)
अणु
	काष्ठा ip_vs_iphdr iph;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_proto_data *pd;
	काष्ठा ip_vs_conn *cp;
	पूर्णांक ret, pkts;
	पूर्णांक conn_reuse_mode;
	काष्ठा sock *sk;

	/* Alपढ़ोy marked as IPVS request or reply? */
	अगर (skb->ipvs_property)
		वापस NF_ACCEPT;

	/*
	 *	Big tappo:
	 *	- remote client: only PACKET_HOST
	 *	- route: used क्रम काष्ठा net when skb->dev is unset
	 */
	अगर (unlikely((skb->pkt_type != PACKET_HOST &&
		      hooknum != NF_INET_LOCAL_OUT) ||
		     !skb_dst(skb))) अणु
		ip_vs_fill_iph_skb(af, skb, false, &iph);
		IP_VS_DBG_BUF(12, "packet type=%d proto=%d daddr=%s"
			      " ignored in hook %u\n",
			      skb->pkt_type, iph.protocol,
			      IP_VS_DBG_ADDR(af, &iph.daddr), hooknum);
		वापस NF_ACCEPT;
	पूर्ण
	/* ipvs enabled in this netns ? */
	अगर (unlikely(sysctl_backup_only(ipvs) || !ipvs->enable))
		वापस NF_ACCEPT;

	ip_vs_fill_iph_skb(af, skb, false, &iph);

	/* Bad... Do not अवरोध raw sockets */
	sk = skb_to_full_sk(skb);
	अगर (unlikely(sk && hooknum == NF_INET_LOCAL_OUT &&
		     af == AF_INET)) अणु

		अगर (sk->sk_family == PF_INET && inet_sk(sk)->nodefrag)
			वापस NF_ACCEPT;
	पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6) अणु
		अगर (unlikely(iph.protocol == IPPROTO_ICMPV6)) अणु
			पूर्णांक related;
			पूर्णांक verdict = ip_vs_in_icmp_v6(ipvs, skb, &related,
						       hooknum, &iph);

			अगर (related)
				वापस verdict;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (unlikely(iph.protocol == IPPROTO_ICMP)) अणु
			पूर्णांक related;
			पूर्णांक verdict = ip_vs_in_icmp(ipvs, skb, &related,
						    hooknum);

			अगर (related)
				वापस verdict;
		पूर्ण

	/* Protocol supported? */
	pd = ip_vs_proto_data_get(ipvs, iph.protocol);
	अगर (unlikely(!pd)) अणु
		/* The only way we'll see this packet again is if it's
		 * encapsulated, so mark it with ipvs_property=1 so we
		 * skip it अगर we're ignoring tunneled packets
		 */
		अगर (sysctl_ignore_tunneled(ipvs))
			skb->ipvs_property = 1;

		वापस NF_ACCEPT;
	पूर्ण
	pp = pd->pp;
	/*
	 * Check अगर the packet beदीर्घs to an existing connection entry
	 */
	cp = INसूचीECT_CALL_1(pp->conn_in_get, ip_vs_conn_in_get_proto,
			     ipvs, af, skb, &iph);

	conn_reuse_mode = sysctl_conn_reuse_mode(ipvs);
	अगर (conn_reuse_mode && !iph.fragoffs && is_new_conn(skb, &iph) && cp) अणु
		bool old_ct = false, resched = false;

		अगर (unlikely(sysctl_expire_nodest_conn(ipvs)) && cp->dest &&
		    unlikely(!atomic_पढ़ो(&cp->dest->weight))) अणु
			resched = true;
			old_ct = ip_vs_conn_uses_old_conntrack(cp, skb);
		पूर्ण अन्यथा अगर (is_new_conn_expected(cp, conn_reuse_mode)) अणु
			old_ct = ip_vs_conn_uses_old_conntrack(cp, skb);
			अगर (!atomic_पढ़ो(&cp->n_control)) अणु
				resched = true;
			पूर्ण अन्यथा अणु
				/* Do not reschedule controlling connection
				 * that uses conntrack जबतक it is still
				 * referenced by controlled connection(s).
				 */
				resched = !old_ct;
			पूर्ण
		पूर्ण

		अगर (resched) अणु
			अगर (!old_ct)
				cp->flags &= ~IP_VS_CONN_F_NFCT;
			अगर (!atomic_पढ़ो(&cp->n_control))
				ip_vs_conn_expire_now(cp);
			__ip_vs_conn_put(cp);
			अगर (old_ct)
				वापस NF_DROP;
			cp = शून्य;
		पूर्ण
	पूर्ण

	/* Check the server status */
	अगर (cp && cp->dest && !(cp->dest->flags & IP_VS_DEST_F_AVAILABLE)) अणु
		/* the destination server is not available */
		अगर (sysctl_expire_nodest_conn(ipvs)) अणु
			bool old_ct = ip_vs_conn_uses_old_conntrack(cp, skb);

			अगर (!old_ct)
				cp->flags &= ~IP_VS_CONN_F_NFCT;

			ip_vs_conn_expire_now(cp);
			__ip_vs_conn_put(cp);
			अगर (old_ct)
				वापस NF_DROP;
			cp = शून्य;
		पूर्ण अन्यथा अणु
			__ip_vs_conn_put(cp);
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	अगर (unlikely(!cp)) अणु
		पूर्णांक v;

		अगर (!ip_vs_try_to_schedule(ipvs, af, skb, pd, &v, &cp, &iph))
			वापस v;
	पूर्ण

	IP_VS_DBG_PKT(11, af, pp, skb, iph.off, "Incoming packet");

	ip_vs_in_stats(cp, skb);
	ip_vs_set_state(cp, IP_VS_सूची_INPUT, skb, pd);
	अगर (cp->packet_xmit)
		ret = cp->packet_xmit(skb, cp, pp, &iph);
		/* करो not touch skb anymore */
	अन्यथा अणु
		IP_VS_DBG_RL("warning: packet_xmit is null");
		ret = NF_ACCEPT;
	पूर्ण

	/* Increase its packet counter and check अगर it is needed
	 * to be synchronized
	 *
	 * Sync connection अगर it is about to बंद to
	 * encorage the standby servers to update the connections समयout
	 *
	 * For ONE_PKT let ip_vs_sync_conn() करो the filter work.
	 */

	अगर (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		pkts = sysctl_sync_threshold(ipvs);
	अन्यथा
		pkts = atomic_inc_वापस(&cp->in_pkts);

	अगर (ipvs->sync_state & IP_VS_STATE_MASTER)
		ip_vs_sync_conn(ipvs, cp, pkts);
	अन्यथा अगर ((cp->flags & IP_VS_CONN_F_ONE_PACKET) && cp->control)
		/* increment is करोne inside ip_vs_sync_conn too */
		atomic_inc(&cp->control->in_pkts);

	ip_vs_conn_put(cp);
	वापस ret;
पूर्ण

/*
 *	AF_INET handler in NF_INET_LOCAL_IN chain
 *	Schedule and क्रमward packets from remote clients
 */
अटल अचिन्हित पूर्णांक
ip_vs_remote_request4(व्योम *priv, काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_in(net_ipvs(state->net), state->hook, skb, AF_INET);
पूर्ण

/*
 *	AF_INET handler in NF_INET_LOCAL_OUT chain
 *	Schedule and क्रमward packets from local clients
 */
अटल अचिन्हित पूर्णांक
ip_vs_local_request4(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_in(net_ipvs(state->net), state->hook, skb, AF_INET);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6

/*
 *	AF_INET6 handler in NF_INET_LOCAL_IN chain
 *	Schedule and क्रमward packets from remote clients
 */
अटल अचिन्हित पूर्णांक
ip_vs_remote_request6(व्योम *priv, काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_in(net_ipvs(state->net), state->hook, skb, AF_INET6);
पूर्ण

/*
 *	AF_INET6 handler in NF_INET_LOCAL_OUT chain
 *	Schedule and क्रमward packets from local clients
 */
अटल अचिन्हित पूर्णांक
ip_vs_local_request6(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस ip_vs_in(net_ipvs(state->net), state->hook, skb, AF_INET6);
पूर्ण

#पूर्ण_अगर


/*
 *	It is hooked at the NF_INET_FORWARD chain, in order to catch ICMP
 *      related packets destined क्रम 0.0.0.0/0.
 *      When fwmark-based भव service is used, such as transparent
 *      cache cluster, TCP packets can be marked and routed to ip_vs_in,
 *      but ICMP destined क्रम 0.0.0.0/0 cannot not be easily marked and
 *      sent to ip_vs_in_icmp. So, catch them at the NF_INET_FORWARD chain
 *      and send them to ip_vs_in_icmp.
 */
अटल अचिन्हित पूर्णांक
ip_vs_क्रमward_icmp(व्योम *priv, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा nf_hook_state *state)
अणु
	पूर्णांक r;
	काष्ठा netns_ipvs *ipvs = net_ipvs(state->net);

	अगर (ip_hdr(skb)->protocol != IPPROTO_ICMP)
		वापस NF_ACCEPT;

	/* ipvs enabled in this netns ? */
	अगर (unlikely(sysctl_backup_only(ipvs) || !ipvs->enable))
		वापस NF_ACCEPT;

	वापस ip_vs_in_icmp(ipvs, skb, &r, state->hook);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल अचिन्हित पूर्णांक
ip_vs_क्रमward_icmp_v6(व्योम *priv, काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nf_hook_state *state)
अणु
	पूर्णांक r;
	काष्ठा netns_ipvs *ipvs = net_ipvs(state->net);
	काष्ठा ip_vs_iphdr iphdr;

	ip_vs_fill_iph_skb(AF_INET6, skb, false, &iphdr);
	अगर (iphdr.protocol != IPPROTO_ICMPV6)
		वापस NF_ACCEPT;

	/* ipvs enabled in this netns ? */
	अगर (unlikely(sysctl_backup_only(ipvs) || !ipvs->enable))
		वापस NF_ACCEPT;

	वापस ip_vs_in_icmp_v6(ipvs, skb, &r, state->hook, &iphdr);
पूर्ण
#पूर्ण_अगर


अटल स्थिर काष्ठा nf_hook_ops ip_vs_ops4[] = अणु
	/* After packet filtering, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_reply4,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_NAT_SRC - 2,
	पूर्ण,
	/* After packet filtering, क्रमward packet through VS/DR, VS/TUN,
	 * or VS/NAT(change destination), so that filtering rules can be
	 * applied to IPVS. */
	अणु
		.hook		= ip_vs_remote_request4,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_NAT_SRC - 1,
	पूर्ण,
	/* Beक्रमe ip_vs_in, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_local_reply4,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_NAT_DST + 1,
	पूर्ण,
	/* After mangle, schedule and क्रमward local requests */
	अणु
		.hook		= ip_vs_local_request4,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_NAT_DST + 2,
	पूर्ण,
	/* After packet filtering (but beक्रमe ip_vs_out_icmp), catch icmp
	 * destined क्रम 0.0.0.0/0, which is क्रम incoming IPVS connections */
	अणु
		.hook		= ip_vs_क्रमward_icmp,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_FORWARD,
		.priority	= 99,
	पूर्ण,
	/* After packet filtering, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_reply4,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_FORWARD,
		.priority	= 100,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल स्थिर काष्ठा nf_hook_ops ip_vs_ops6[] = अणु
	/* After packet filtering, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_reply6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_NAT_SRC - 2,
	पूर्ण,
	/* After packet filtering, क्रमward packet through VS/DR, VS/TUN,
	 * or VS/NAT(change destination), so that filtering rules can be
	 * applied to IPVS. */
	अणु
		.hook		= ip_vs_remote_request6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_NAT_SRC - 1,
	पूर्ण,
	/* Beक्रमe ip_vs_in, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_local_reply6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_NAT_DST + 1,
	पूर्ण,
	/* After mangle, schedule and क्रमward local requests */
	अणु
		.hook		= ip_vs_local_request6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_NAT_DST + 2,
	पूर्ण,
	/* After packet filtering (but beक्रमe ip_vs_out_icmp), catch icmp
	 * destined क्रम 0.0.0.0/0, which is क्रम incoming IPVS connections */
	अणु
		.hook		= ip_vs_क्रमward_icmp_v6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_FORWARD,
		.priority	= 99,
	पूर्ण,
	/* After packet filtering, change source only क्रम VS/NAT */
	अणु
		.hook		= ip_vs_reply6,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_FORWARD,
		.priority	= 100,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

पूर्णांक ip_vs_रेजिस्टर_hooks(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक af)
अणु
	स्थिर काष्ठा nf_hook_ops *ops;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक afmask;
	पूर्णांक ret = 0;

	अगर (af == AF_INET6) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
		ops = ip_vs_ops6;
		count = ARRAY_SIZE(ip_vs_ops6);
		afmask = 2;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		ops = ip_vs_ops4;
		count = ARRAY_SIZE(ip_vs_ops4);
		afmask = 1;
	पूर्ण

	अगर (!(ipvs->hooks_afmask & afmask)) अणु
		ret = nf_रेजिस्टर_net_hooks(ipvs->net, ops, count);
		अगर (ret >= 0)
			ipvs->hooks_afmask |= afmask;
	पूर्ण
	वापस ret;
पूर्ण

व्योम ip_vs_unरेजिस्टर_hooks(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक af)
अणु
	स्थिर काष्ठा nf_hook_ops *ops;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक afmask;

	अगर (af == AF_INET6) अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
		ops = ip_vs_ops6;
		count = ARRAY_SIZE(ip_vs_ops6);
		afmask = 2;
#अन्यथा
		वापस;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		ops = ip_vs_ops4;
		count = ARRAY_SIZE(ip_vs_ops4);
		afmask = 1;
	पूर्ण

	अगर (ipvs->hooks_afmask & afmask) अणु
		nf_unरेजिस्टर_net_hooks(ipvs->net, ops, count);
		ipvs->hooks_afmask &= ~afmask;
	पूर्ण
पूर्ण

/*
 *	Initialize IP Virtual Server netns mem.
 */
अटल पूर्णांक __net_init __ip_vs_init(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs;

	ipvs = net_generic(net, ip_vs_net_id);
	अगर (ipvs == शून्य)
		वापस -ENOMEM;

	/* Hold the beast until a service is रेजिस्टरed */
	ipvs->enable = 0;
	ipvs->net = net;
	/* Counters used क्रम creating unique names */
	ipvs->gen = atomic_पढ़ो(&ipvs_netns_cnt);
	atomic_inc(&ipvs_netns_cnt);
	net->ipvs = ipvs;

	अगर (ip_vs_estimator_net_init(ipvs) < 0)
		जाओ estimator_fail;

	अगर (ip_vs_control_net_init(ipvs) < 0)
		जाओ control_fail;

	अगर (ip_vs_protocol_net_init(ipvs) < 0)
		जाओ protocol_fail;

	अगर (ip_vs_app_net_init(ipvs) < 0)
		जाओ app_fail;

	अगर (ip_vs_conn_net_init(ipvs) < 0)
		जाओ conn_fail;

	अगर (ip_vs_sync_net_init(ipvs) < 0)
		जाओ sync_fail;

	वापस 0;
/*
 * Error handling
 */

sync_fail:
	ip_vs_conn_net_cleanup(ipvs);
conn_fail:
	ip_vs_app_net_cleanup(ipvs);
app_fail:
	ip_vs_protocol_net_cleanup(ipvs);
protocol_fail:
	ip_vs_control_net_cleanup(ipvs);
control_fail:
	ip_vs_estimator_net_cleanup(ipvs);
estimator_fail:
	net->ipvs = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास __ip_vs_cleanup_batch(काष्ठा list_head *net_list)
अणु
	काष्ठा netns_ipvs *ipvs;
	काष्ठा net *net;

	ip_vs_service_nets_cleanup(net_list);	/* ip_vs_flush() with locks */
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		ipvs = net_ipvs(net);
		ip_vs_conn_net_cleanup(ipvs);
		ip_vs_app_net_cleanup(ipvs);
		ip_vs_protocol_net_cleanup(ipvs);
		ip_vs_control_net_cleanup(ipvs);
		ip_vs_estimator_net_cleanup(ipvs);
		IP_VS_DBG(2, "ipvs netns %d released\n", ipvs->gen);
		net->ipvs = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __net_निकास __ip_vs_dev_cleanup_batch(काष्ठा list_head *net_list)
अणु
	काष्ठा netns_ipvs *ipvs;
	काष्ठा net *net;

	EnterFunction(2);
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		ipvs = net_ipvs(net);
		ip_vs_unरेजिस्टर_hooks(ipvs, AF_INET);
		ip_vs_unरेजिस्टर_hooks(ipvs, AF_INET6);
		ipvs->enable = 0;	/* Disable packet reception */
		smp_wmb();
		ip_vs_sync_net_cleanup(ipvs);
	पूर्ण
	LeaveFunction(2);
पूर्ण

अटल काष्ठा pernet_operations ipvs_core_ops = अणु
	.init = __ip_vs_init,
	.निकास_batch = __ip_vs_cleanup_batch,
	.id   = &ip_vs_net_id,
	.size = माप(काष्ठा netns_ipvs),
पूर्ण;

अटल काष्ठा pernet_operations ipvs_core_dev_ops = अणु
	.निकास_batch = __ip_vs_dev_cleanup_batch,
पूर्ण;

/*
 *	Initialize IP Virtual Server
 */
अटल पूर्णांक __init ip_vs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ip_vs_control_init();
	अगर (ret < 0) अणु
		pr_err("can't setup control.\n");
		जाओ निकास;
	पूर्ण

	ip_vs_protocol_init();

	ret = ip_vs_conn_init();
	अगर (ret < 0) अणु
		pr_err("can't setup connection table.\n");
		जाओ cleanup_protocol;
	पूर्ण

	ret = रेजिस्टर_pernet_subsys(&ipvs_core_ops);	/* Alloc ip_vs काष्ठा */
	अगर (ret < 0)
		जाओ cleanup_conn;

	ret = रेजिस्टर_pernet_device(&ipvs_core_dev_ops);
	अगर (ret < 0)
		जाओ cleanup_sub;

	ret = ip_vs_रेजिस्टर_nl_ioctl();
	अगर (ret < 0) अणु
		pr_err("can't register netlink/ioctl.\n");
		जाओ cleanup_dev;
	पूर्ण

	pr_info("ipvs loaded.\n");

	वापस ret;

cleanup_dev:
	unरेजिस्टर_pernet_device(&ipvs_core_dev_ops);
cleanup_sub:
	unरेजिस्टर_pernet_subsys(&ipvs_core_ops);
cleanup_conn:
	ip_vs_conn_cleanup();
cleanup_protocol:
	ip_vs_protocol_cleanup();
	ip_vs_control_cleanup();
निकास:
	वापस ret;
पूर्ण

अटल व्योम __निकास ip_vs_cleanup(व्योम)
अणु
	ip_vs_unरेजिस्टर_nl_ioctl();
	unरेजिस्टर_pernet_device(&ipvs_core_dev_ops);
	unरेजिस्टर_pernet_subsys(&ipvs_core_ops);	/* मुक्त ip_vs काष्ठा */
	ip_vs_conn_cleanup();
	ip_vs_protocol_cleanup();
	ip_vs_control_cleanup();
	pr_info("ipvs unloaded.\n");
पूर्ण

module_init(ip_vs_init);
module_निकास(ip_vs_cleanup);
MODULE_LICENSE("GPL");
