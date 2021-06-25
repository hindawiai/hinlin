<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_proto.c: transport protocol load balancing support क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * Changes:
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/gfp.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/proc_fs.h>

#समावेश <net/ip_vs.h>


/*
 * IPVS protocols can only be रेजिस्टरed/unरेजिस्टरed when the ipvs
 * module is loaded/unloaded, so no lock is needed in accessing the
 * ipvs protocol table.
 */

#घोषणा IP_VS_PROTO_TAB_SIZE		32	/* must be घातer of 2 */
#घोषणा IP_VS_PROTO_HASH(proto)		((proto) & (IP_VS_PROTO_TAB_SIZE-1))

अटल काष्ठा ip_vs_protocol *ip_vs_proto_table[IP_VS_PROTO_TAB_SIZE];

/* States क्रम conn ढाँचाs: NONE or words separated with ",", max 15 अक्षरs */
अटल स्थिर अक्षर *ip_vs_ctpl_state_name_table[IP_VS_CTPL_S_LAST] = अणु
	[IP_VS_CTPL_S_NONE]			= "NONE",
	[IP_VS_CTPL_S_ASSURED]			= "ASSURED",
पूर्ण;

/*
 *	रेजिस्टर an ipvs protocol
 */
अटल पूर्णांक __used __init रेजिस्टर_ip_vs_protocol(काष्ठा ip_vs_protocol *pp)
अणु
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(pp->protocol);

	pp->next = ip_vs_proto_table[hash];
	ip_vs_proto_table[hash] = pp;

	अगर (pp->init != शून्य)
		pp->init(pp);

	वापस 0;
पूर्ण

/*
 *	रेजिस्टर an ipvs protocols netns related data
 */
अटल पूर्णांक
रेजिस्टर_ip_vs_proto_netns(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_protocol *pp)
अणु
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(pp->protocol);
	काष्ठा ip_vs_proto_data *pd =
			kzalloc(माप(काष्ठा ip_vs_proto_data), GFP_KERNEL);

	अगर (!pd)
		वापस -ENOMEM;

	pd->pp = pp;	/* For speed issues */
	pd->next = ipvs->proto_data_table[hash];
	ipvs->proto_data_table[hash] = pd;
	atomic_set(&pd->appcnt, 0);	/* Init app counter */

	अगर (pp->init_netns != शून्य) अणु
		पूर्णांक ret = pp->init_netns(ipvs, pd);
		अगर (ret) अणु
			/* unlink an मुक्त proto data */
			ipvs->proto_data_table[hash] = pd->next;
			kमुक्त(pd);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	unरेजिस्टर an ipvs protocol
 */
अटल पूर्णांक unरेजिस्टर_ip_vs_protocol(काष्ठा ip_vs_protocol *pp)
अणु
	काष्ठा ip_vs_protocol **pp_p;
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(pp->protocol);

	pp_p = &ip_vs_proto_table[hash];
	क्रम (; *pp_p; pp_p = &(*pp_p)->next) अणु
		अगर (*pp_p == pp) अणु
			*pp_p = pp->next;
			अगर (pp->निकास != शून्य)
				pp->निकास(pp);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ESRCH;
पूर्ण

/*
 *	unरेजिस्टर an ipvs protocols netns data
 */
अटल पूर्णांक
unरेजिस्टर_ip_vs_proto_netns(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd)
अणु
	काष्ठा ip_vs_proto_data **pd_p;
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(pd->pp->protocol);

	pd_p = &ipvs->proto_data_table[hash];
	क्रम (; *pd_p; pd_p = &(*pd_p)->next) अणु
		अगर (*pd_p == pd) अणु
			*pd_p = pd->next;
			अगर (pd->pp->निकास_netns != शून्य)
				pd->pp->निकास_netns(ipvs, pd);
			kमुक्त(pd);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ESRCH;
पूर्ण

/*
 *	get ip_vs_protocol object by its proto.
 */
काष्ठा ip_vs_protocol * ip_vs_proto_get(अचिन्हित लघु proto)
अणु
	काष्ठा ip_vs_protocol *pp;
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(proto);

	क्रम (pp = ip_vs_proto_table[hash]; pp; pp = pp->next) अणु
		अगर (pp->protocol == proto)
			वापस pp;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ip_vs_proto_get);

/*
 *	get ip_vs_protocol object data by netns and proto
 */
काष्ठा ip_vs_proto_data *
ip_vs_proto_data_get(काष्ठा netns_ipvs *ipvs, अचिन्हित लघु proto)
अणु
	काष्ठा ip_vs_proto_data *pd;
	अचिन्हित पूर्णांक hash = IP_VS_PROTO_HASH(proto);

	क्रम (pd = ipvs->proto_data_table[hash]; pd; pd = pd->next) अणु
		अगर (pd->pp->protocol == proto)
			वापस pd;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ip_vs_proto_data_get);

/*
 *	Propagate event क्रम state change to all protocols
 */
व्योम ip_vs_protocol_समयout_change(काष्ठा netns_ipvs *ipvs, पूर्णांक flags)
अणु
	काष्ठा ip_vs_proto_data *pd;
	पूर्णांक i;

	क्रम (i = 0; i < IP_VS_PROTO_TAB_SIZE; i++) अणु
		क्रम (pd = ipvs->proto_data_table[i]; pd; pd = pd->next) अणु
			अगर (pd->pp->समयout_change)
				pd->pp->समयout_change(pd, flags);
		पूर्ण
	पूर्ण
पूर्ण


पूर्णांक *
ip_vs_create_समयout_table(पूर्णांक *table, पूर्णांक size)
अणु
	वापस kmemdup(table, size, GFP_KERNEL);
पूर्ण


स्थिर अक्षर *ip_vs_state_name(स्थिर काष्ठा ip_vs_conn *cp)
अणु
	अचिन्हित पूर्णांक state = cp->state;
	काष्ठा ip_vs_protocol *pp;

	अगर (cp->flags & IP_VS_CONN_F_TEMPLATE) अणु

		अगर (state >= IP_VS_CTPL_S_LAST)
			वापस "ERR!";
		वापस ip_vs_ctpl_state_name_table[state] ? : "?";
	पूर्ण
	pp = ip_vs_proto_get(cp->protocol);
	अगर (pp == शून्य || pp->state_name == शून्य)
		वापस (cp->protocol == IPPROTO_IP) ? "NONE" : "ERR!";
	वापस pp->state_name(state);
पूर्ण


अटल व्योम
ip_vs_tcpudp_debug_packet_v4(काष्ठा ip_vs_protocol *pp,
			     स्थिर काष्ठा sk_buff *skb,
			     पूर्णांक offset,
			     स्थिर अक्षर *msg)
अणु
	अक्षर buf[128];
	काष्ठा iphdr _iph, *ih;

	ih = skb_header_poपूर्णांकer(skb, offset, माप(_iph), &_iph);
	अगर (ih == शून्य)
		प्र_लिखो(buf, "TRUNCATED");
	अन्यथा अगर (ih->frag_off & htons(IP_OFFSET))
		प्र_लिखो(buf, "%pI4->%pI4 frag", &ih->saddr, &ih->daddr);
	अन्यथा अणु
		__be16 _ports[2], *pptr;

		pptr = skb_header_poपूर्णांकer(skb, offset + ih->ihl*4,
					  माप(_ports), _ports);
		अगर (pptr == शून्य)
			प्र_लिखो(buf, "TRUNCATED %pI4->%pI4",
				&ih->saddr, &ih->daddr);
		अन्यथा
			प्र_लिखो(buf, "%pI4:%u->%pI4:%u",
				&ih->saddr, ntohs(pptr[0]),
				&ih->daddr, ntohs(pptr[1]));
	पूर्ण

	pr_debug("%s: %s %s\n", msg, pp->name, buf);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल व्योम
ip_vs_tcpudp_debug_packet_v6(काष्ठा ip_vs_protocol *pp,
			     स्थिर काष्ठा sk_buff *skb,
			     पूर्णांक offset,
			     स्थिर अक्षर *msg)
अणु
	अक्षर buf[192];
	काष्ठा ipv6hdr _iph, *ih;

	ih = skb_header_poपूर्णांकer(skb, offset, माप(_iph), &_iph);
	अगर (ih == शून्य)
		प्र_लिखो(buf, "TRUNCATED");
	अन्यथा अगर (ih->nexthdr == IPPROTO_FRAGMENT)
		प्र_लिखो(buf, "%pI6c->%pI6c frag", &ih->saddr, &ih->daddr);
	अन्यथा अणु
		__be16 _ports[2], *pptr;

		pptr = skb_header_poपूर्णांकer(skb, offset + माप(काष्ठा ipv6hdr),
					  माप(_ports), _ports);
		अगर (pptr == शून्य)
			प्र_लिखो(buf, "TRUNCATED %pI6c->%pI6c",
				&ih->saddr, &ih->daddr);
		अन्यथा
			प्र_लिखो(buf, "%pI6c:%u->%pI6c:%u",
				&ih->saddr, ntohs(pptr[0]),
				&ih->daddr, ntohs(pptr[1]));
	पूर्ण

	pr_debug("%s: %s %s\n", msg, pp->name, buf);
पूर्ण
#पूर्ण_अगर


व्योम
ip_vs_tcpudp_debug_packet(पूर्णांक af, काष्ठा ip_vs_protocol *pp,
			  स्थिर काष्ठा sk_buff *skb,
			  पूर्णांक offset,
			  स्थिर अक्षर *msg)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		ip_vs_tcpudp_debug_packet_v6(pp, skb, offset, msg);
	अन्यथा
#पूर्ण_अगर
		ip_vs_tcpudp_debug_packet_v4(pp, skb, offset, msg);
पूर्ण

/*
 * per network name-space init
 */
पूर्णांक __net_init ip_vs_protocol_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	पूर्णांक i, ret;
	अटल काष्ठा ip_vs_protocol *protos[] = अणु
#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
        &ip_vs_protocol_tcp,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	&ip_vs_protocol_udp,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_SCTP
	&ip_vs_protocol_sctp,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_AH
	&ip_vs_protocol_ah,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_ESP
	&ip_vs_protocol_esp,
#पूर्ण_अगर
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(protos); i++) अणु
		ret = रेजिस्टर_ip_vs_proto_netns(ipvs, protos[i]);
		अगर (ret < 0)
			जाओ cleanup;
	पूर्ण
	वापस 0;

cleanup:
	ip_vs_protocol_net_cleanup(ipvs);
	वापस ret;
पूर्ण

व्योम __net_निकास ip_vs_protocol_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	काष्ठा ip_vs_proto_data *pd;
	पूर्णांक i;

	/* unरेजिस्टर all the ipvs proto data क्रम this netns */
	क्रम (i = 0; i < IP_VS_PROTO_TAB_SIZE; i++) अणु
		जबतक ((pd = ipvs->proto_data_table[i]) != शून्य)
			unरेजिस्टर_ip_vs_proto_netns(ipvs, pd);
	पूर्ण
पूर्ण

पूर्णांक __init ip_vs_protocol_init(व्योम)
अणु
	अक्षर protocols[64];
#घोषणा REGISTER_PROTOCOL(p)			\
	करो अणु					\
		रेजिस्टर_ip_vs_protocol(p);	\
		म_जोड़ो(protocols, ", ");	\
		म_जोड़ो(protocols, (p)->name);	\
	पूर्ण जबतक (0)

	protocols[0] = '\0';
	protocols[2] = '\0';
#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
	REGISTER_PROTOCOL(&ip_vs_protocol_tcp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	REGISTER_PROTOCOL(&ip_vs_protocol_udp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_SCTP
	REGISTER_PROTOCOL(&ip_vs_protocol_sctp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_AH
	REGISTER_PROTOCOL(&ip_vs_protocol_ah);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_VS_PROTO_ESP
	REGISTER_PROTOCOL(&ip_vs_protocol_esp);
#पूर्ण_अगर
	pr_info("Registered protocols (%s)\n", &protocols[2]);

	वापस 0;
पूर्ण


व्योम ip_vs_protocol_cleanup(व्योम)
अणु
	काष्ठा ip_vs_protocol *pp;
	पूर्णांक i;

	/* unरेजिस्टर all the ipvs protocols */
	क्रम (i = 0; i < IP_VS_PROTO_TAB_SIZE; i++) अणु
		जबतक ((pp = ip_vs_proto_table[i]) != शून्य)
			unरेजिस्टर_ip_vs_protocol(pp);
	पूर्ण
पूर्ण
