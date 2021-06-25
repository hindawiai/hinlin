<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header क्रम use in defining a given L4 protocol क्रम connection tracking.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- generalized L3 protocol dependent part.
 *
 * Derived from include/linux/netfiter_ipv4/ip_conntrack_protcol.h
 */

#अगर_अघोषित _NF_CONNTRACK_L4PROTO_H
#घोषणा _NF_CONNTRACK_L4PROTO_H
#समावेश <linux/netlink.h>
#समावेश <net/netlink.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netns/generic.h>

काष्ठा seq_file;

काष्ठा nf_conntrack_l4proto अणु
	/* L4 Protocol number. */
	u_पूर्णांक8_t l4proto;

	/* Resolve clashes on insertion races. */
	bool allow_clash;

	/* protoinfo nlattr size, बंदs a hole */
	u16 nlattr_size;

	/* called by gc worker अगर table is full */
	bool (*can_early_drop)(स्थिर काष्ठा nf_conn *ct);

	/* convert protoinfo to nfnetink attributes */
	पूर्णांक (*to_nlattr)(काष्ठा sk_buff *skb, काष्ठा nlattr *nla,
			 काष्ठा nf_conn *ct, bool destroy);

	/* convert nfnetlink attributes to protoinfo */
	पूर्णांक (*from_nlattr)(काष्ठा nlattr *tb[], काष्ठा nf_conn *ct);

	पूर्णांक (*tuple_to_nlattr)(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conntrack_tuple *t);
	/* Calculate tuple nlattr size */
	अचिन्हित पूर्णांक (*nlattr_tuple_size)(व्योम);
	पूर्णांक (*nlattr_to_tuple)(काष्ठा nlattr *tb[],
			       काष्ठा nf_conntrack_tuple *t,
			       u_पूर्णांक32_t flags);
	स्थिर काष्ठा nla_policy *nla_policy;

	काष्ठा अणु
		पूर्णांक (*nlattr_to_obj)(काष्ठा nlattr *tb[],
				     काष्ठा net *net, व्योम *data);
		पूर्णांक (*obj_to_nlattr)(काष्ठा sk_buff *skb, स्थिर व्योम *data);

		u16 obj_size;
		u16 nlattr_max;
		स्थिर काष्ठा nla_policy *nla_policy;
	पूर्ण ctnl_समयout;
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	/* Prपूर्णांक out the निजी part of the conntrack. */
	व्योम (*prपूर्णांक_conntrack)(काष्ठा seq_file *s, काष्ठा nf_conn *);
#पूर्ण_अगर
पूर्ण;

bool icmp_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक dataoff,
		       काष्ठा net *net,
		       काष्ठा nf_conntrack_tuple *tuple);

bool icmpv6_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb,
			 अचिन्हित पूर्णांक dataoff,
			 काष्ठा net *net,
			 काष्ठा nf_conntrack_tuple *tuple);

bool nf_conntrack_invert_icmp_tuple(काष्ठा nf_conntrack_tuple *tuple,
				    स्थिर काष्ठा nf_conntrack_tuple *orig);
bool nf_conntrack_invert_icmpv6_tuple(काष्ठा nf_conntrack_tuple *tuple,
				      स्थिर काष्ठा nf_conntrack_tuple *orig);

पूर्णांक nf_conntrack_inet_error(काष्ठा nf_conn *पंचांगpl, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    स्थिर काष्ठा nf_hook_state *state,
			    u8 l4proto,
			    जोड़ nf_inet_addr *outer_daddr);

पूर्णांक nf_conntrack_icmpv4_error(काष्ठा nf_conn *पंचांगpl,
			      काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक dataoff,
			      स्थिर काष्ठा nf_hook_state *state);

पूर्णांक nf_conntrack_icmpv6_error(काष्ठा nf_conn *पंचांगpl,
			      काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक dataoff,
			      स्थिर काष्ठा nf_hook_state *state);

पूर्णांक nf_conntrack_icmp_packet(काष्ठा nf_conn *ct,
			     काष्ठा sk_buff *skb,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state);

पूर्णांक nf_conntrack_icmpv6_packet(काष्ठा nf_conn *ct,
			       काष्ठा sk_buff *skb,
			       क्रमागत ip_conntrack_info ctinfo,
			       स्थिर काष्ठा nf_hook_state *state);

पूर्णांक nf_conntrack_udp_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state);
पूर्णांक nf_conntrack_udplite_packet(काष्ठा nf_conn *ct,
				काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक dataoff,
				क्रमागत ip_conntrack_info ctinfo,
				स्थिर काष्ठा nf_hook_state *state);
पूर्णांक nf_conntrack_tcp_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state);
पूर्णांक nf_conntrack_dccp_packet(काष्ठा nf_conn *ct,
			     काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक dataoff,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state);
पूर्णांक nf_conntrack_sctp_packet(काष्ठा nf_conn *ct,
			     काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक dataoff,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state);
पूर्णांक nf_conntrack_gre_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state);

व्योम nf_conntrack_generic_init_net(काष्ठा net *net);
व्योम nf_conntrack_tcp_init_net(काष्ठा net *net);
व्योम nf_conntrack_udp_init_net(काष्ठा net *net);
व्योम nf_conntrack_gre_init_net(काष्ठा net *net);
व्योम nf_conntrack_dccp_init_net(काष्ठा net *net);
व्योम nf_conntrack_sctp_init_net(काष्ठा net *net);
व्योम nf_conntrack_icmp_init_net(काष्ठा net *net);
व्योम nf_conntrack_icmpv6_init_net(काष्ठा net *net);

/* Existing built-in generic protocol */
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_generic;

#घोषणा MAX_NF_CT_PROTO IPPROTO_UDPLITE

स्थिर काष्ठा nf_conntrack_l4proto *nf_ct_l4proto_find(u8 l4proto);

/* Generic netlink helpers */
पूर्णांक nf_ct_port_tuple_to_nlattr(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conntrack_tuple *tuple);
पूर्णांक nf_ct_port_nlattr_to_tuple(काष्ठा nlattr *tb[],
			       काष्ठा nf_conntrack_tuple *t,
			       u_पूर्णांक32_t flags);
अचिन्हित पूर्णांक nf_ct_port_nlattr_tuple_size(व्योम);
बाह्य स्थिर काष्ठा nla_policy nf_ct_port_nla_policy[];

#अगर_घोषित CONFIG_SYSCTL
__म_लिखो(3, 4) __cold
व्योम nf_ct_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conn *ct,
			       स्थिर अक्षर *fmt, ...);
__म_लिखो(5, 6) __cold
व्योम nf_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb,
			    काष्ठा net *net,
			    u16 pf, u8 protonum,
			    स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत __म_लिखो(5, 6) __cold
व्योम nf_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb, काष्ठा net *net,
			    u16 pf, u8 protonum, स्थिर अक्षर *fmt, ...) अणुपूर्ण
अटल अंतरभूत __म_लिखो(3, 4) __cold
व्योम nf_ct_l4proto_log_invalid(स्थिर काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_conn *ct,
			       स्थिर अक्षर *fmt, ...) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
अटल अंतरभूत काष्ठा nf_generic_net *nf_generic_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.generic;
पूर्ण

अटल अंतरभूत काष्ठा nf_tcp_net *nf_tcp_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.tcp;
पूर्ण

अटल अंतरभूत काष्ठा nf_udp_net *nf_udp_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.udp;
पूर्ण

अटल अंतरभूत काष्ठा nf_icmp_net *nf_icmp_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.icmp;
पूर्ण

अटल अंतरभूत काष्ठा nf_icmp_net *nf_icmpv6_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.icmpv6;
पूर्ण

/* Caller must check nf_ct_protonum(ct) is IPPROTO_TCP beक्रमe calling. */
अटल अंतरभूत व्योम nf_ct_set_tcp_be_liberal(काष्ठा nf_conn *ct)
अणु
	ct->proto.tcp.seen[0].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
	ct->proto.tcp.seen[1].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
पूर्ण

/* Caller must check nf_ct_protonum(ct) is IPPROTO_TCP beक्रमe calling. */
अटल अंतरभूत bool nf_conntrack_tcp_established(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस ct->proto.tcp.state == TCP_CONNTRACK_ESTABLISHED &&
	       test_bit(IPS_ASSURED_BIT, &ct->status);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
अटल अंतरभूत काष्ठा nf_dccp_net *nf_dccp_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.dccp;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
अटल अंतरभूत काष्ठा nf_sctp_net *nf_sctp_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.sctp;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
अटल अंतरभूत काष्ठा nf_gre_net *nf_gre_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.gre;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /*_NF_CONNTRACK_PROTOCOL_H*/
