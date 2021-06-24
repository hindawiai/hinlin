<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ip_vs_proto_ah_esp.c:	AH/ESP IPSec load balancing support क्रम IPVS
 *
 * Authors:	Julian Anastasov <ja@ssi.bg>, February 2002
 *		Wensong Zhang <wensong@linuxभवserver.org>
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>

#समावेश <net/ip_vs.h>


/* TODO:

काष्ठा isakmp_hdr अणु
	__u8		icookie[8];
	__u8		rcookie[8];
	__u8		np;
	__u8		version;
	__u8		xchgtype;
	__u8		flags;
	__u32		msgid;
	__u32		length;
पूर्ण;

*/

#घोषणा PORT_ISAKMP	500

अटल व्योम
ah_esp_conn_fill_param_proto(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
			     स्थिर काष्ठा ip_vs_iphdr *iph,
			     काष्ठा ip_vs_conn_param *p)
अणु
	अगर (likely(!ip_vs_iph_inverse(iph)))
		ip_vs_conn_fill_param(ipvs, af, IPPROTO_UDP,
				      &iph->saddr, htons(PORT_ISAKMP),
				      &iph->daddr, htons(PORT_ISAKMP), p);
	अन्यथा
		ip_vs_conn_fill_param(ipvs, af, IPPROTO_UDP,
				      &iph->daddr, htons(PORT_ISAKMP),
				      &iph->saddr, htons(PORT_ISAKMP), p);
पूर्ण

अटल काष्ठा ip_vs_conn *
ah_esp_conn_in_get(काष्ठा netns_ipvs *ipvs, पूर्णांक af, स्थिर काष्ठा sk_buff *skb,
		   स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_conn_param p;

	ah_esp_conn_fill_param_proto(ipvs, af, iph, &p);
	cp = ip_vs_conn_in_get(&p);
	अगर (!cp) अणु
		/*
		 * We are not sure अगर the packet is from our
		 * service, so our conn_schedule hook should वापस NF_ACCEPT
		 */
		IP_VS_DBG_BUF(12, "Unknown ISAKMP entry for outin packet "
			      "%s%s %s->%s\n",
			      ip_vs_iph_icmp(iph) ? "ICMP+" : "",
			      ip_vs_proto_get(iph->protocol)->name,
			      IP_VS_DBG_ADDR(af, &iph->saddr),
			      IP_VS_DBG_ADDR(af, &iph->daddr));
	पूर्ण

	वापस cp;
पूर्ण


अटल काष्ठा ip_vs_conn *
ah_esp_conn_out_get(काष्ठा netns_ipvs *ipvs, पूर्णांक af, स्थिर काष्ठा sk_buff *skb,
		    स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_conn *cp;
	काष्ठा ip_vs_conn_param p;

	ah_esp_conn_fill_param_proto(ipvs, af, iph, &p);
	cp = ip_vs_conn_out_get(&p);
	अगर (!cp) अणु
		IP_VS_DBG_BUF(12, "Unknown ISAKMP entry for inout packet "
			      "%s%s %s->%s\n",
			      ip_vs_iph_icmp(iph) ? "ICMP+" : "",
			      ip_vs_proto_get(iph->protocol)->name,
			      IP_VS_DBG_ADDR(af, &iph->saddr),
			      IP_VS_DBG_ADDR(af, &iph->daddr));
	पूर्ण

	वापस cp;
पूर्ण


अटल पूर्णांक
ah_esp_conn_schedule(काष्ठा netns_ipvs *ipvs, पूर्णांक af, काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_proto_data *pd,
		     पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
		     काष्ठा ip_vs_iphdr *iph)
अणु
	/*
	 * AH/ESP is only related traffic. Pass the packet to IP stack.
	 */
	*verdict = NF_ACCEPT;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_PROTO_AH
काष्ठा ip_vs_protocol ip_vs_protocol_ah = अणु
	.name =			"AH",
	.protocol =		IPPROTO_AH,
	.num_states =		1,
	.करोnt_defrag =		1,
	.init =			शून्य,
	.निकास =			शून्य,
	.conn_schedule =	ah_esp_conn_schedule,
	.conn_in_get =		ah_esp_conn_in_get,
	.conn_out_get =		ah_esp_conn_out_get,
	.snat_handler =		शून्य,
	.dnat_handler =		शून्य,
	.state_transition =	शून्य,
	.रेजिस्टर_app =		शून्य,
	.unरेजिस्टर_app =	शून्य,
	.app_conn_bind =	शून्य,
	.debug_packet =		ip_vs_tcpudp_debug_packet,
	.समयout_change =	शून्य,		/* ISAKMP */
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_VS_PROTO_ESP
काष्ठा ip_vs_protocol ip_vs_protocol_esp = अणु
	.name =			"ESP",
	.protocol =		IPPROTO_ESP,
	.num_states =		1,
	.करोnt_defrag =		1,
	.init =			शून्य,
	.निकास =			शून्य,
	.conn_schedule =	ah_esp_conn_schedule,
	.conn_in_get =		ah_esp_conn_in_get,
	.conn_out_get =		ah_esp_conn_out_get,
	.snat_handler =		शून्य,
	.dnat_handler =		शून्य,
	.state_transition =	शून्य,
	.रेजिस्टर_app =		शून्य,
	.unरेजिस्टर_app =	शून्य,
	.app_conn_bind =	शून्य,
	.debug_packet =		ip_vs_tcpudp_debug_packet,
	.समयout_change =	शून्य,		/* ISAKMP */
पूर्ण;
#पूर्ण_अगर
