<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_NAT_H
#घोषणा _NF_NAT_H

#समावेश <linux/list.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter/nf_conntrack_pptp.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <uapi/linux/netfilter/nf_nat.h>

क्रमागत nf_nat_manip_type अणु
	NF_NAT_MANIP_SRC,
	NF_NAT_MANIP_DST
पूर्ण;

/* SRC manip occurs POST_ROUTING or LOCAL_IN */
#घोषणा HOOK2MANIP(hooknum) ((hooknum) != NF_INET_POST_ROUTING && \
			     (hooknum) != NF_INET_LOCAL_IN)

/* per conntrack: nat application helper निजी data */
जोड़ nf_conntrack_nat_help अणु
	/* insert nat helper निजी data here */
#अगर IS_ENABLED(CONFIG_NF_NAT_PPTP)
	काष्ठा nf_nat_pptp nat_pptp_info;
#पूर्ण_अगर
पूर्ण;

/* The काष्ठाure embedded in the conntrack काष्ठाure. */
काष्ठा nf_conn_nat अणु
	जोड़ nf_conntrack_nat_help help;
#अगर IS_ENABLED(CONFIG_NF_NAT_MASQUERADE)
	पूर्णांक masq_index;
#पूर्ण_अगर
पूर्ण;

/* Set up the info काष्ठाure to map पूर्णांकo this range. */
अचिन्हित पूर्णांक nf_nat_setup_info(काष्ठा nf_conn *ct,
			       स्थिर काष्ठा nf_nat_range2 *range,
			       क्रमागत nf_nat_manip_type maniptype);

बाह्य अचिन्हित पूर्णांक nf_nat_alloc_null_binding(काष्ठा nf_conn *ct,
					      अचिन्हित पूर्णांक hooknum);

काष्ठा nf_conn_nat *nf_ct_nat_ext_add(काष्ठा nf_conn *ct);

अटल अंतरभूत काष्ठा nf_conn_nat *nfct_nat(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
	वापस nf_ct_ext_find(ct, NF_CT_EXT_NAT);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool nf_nat_oअगर_changed(अचिन्हित पूर्णांक hooknum,
				      क्रमागत ip_conntrack_info ctinfo,
				      काष्ठा nf_conn_nat *nat,
				      स्थिर काष्ठा net_device *out)
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT_MASQUERADE)
	वापस nat && nat->masq_index && hooknum == NF_INET_POST_ROUTING &&
	       CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL &&
	       nat->masq_index != out->अगरindex;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

पूर्णांक nf_nat_रेजिस्टर_fn(काष्ठा net *net, u8 pf, स्थिर काष्ठा nf_hook_ops *ops,
		       स्थिर काष्ठा nf_hook_ops *nat_ops, अचिन्हित पूर्णांक ops_count);
व्योम nf_nat_unरेजिस्टर_fn(काष्ठा net *net, u8 pf, स्थिर काष्ठा nf_hook_ops *ops,
			  अचिन्हित पूर्णांक ops_count);

अचिन्हित पूर्णांक nf_nat_packet(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			   अचिन्हित पूर्णांक hooknum, काष्ठा sk_buff *skb);

अचिन्हित पूर्णांक nf_nat_manip_pkt(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			      क्रमागत nf_nat_manip_type mtype,
			      क्रमागत ip_conntrack_dir dir);
व्योम nf_nat_csum_recalc(काष्ठा sk_buff *skb,
			u8 nfproto, u8 proto, व्योम *data, __sum16 *check,
			पूर्णांक datalen, पूर्णांक oldlen);

पूर्णांक nf_nat_icmp_reply_translation(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				  क्रमागत ip_conntrack_info ctinfo,
				  अचिन्हित पूर्णांक hooknum);

पूर्णांक nf_nat_icmpv6_reply_translation(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				    क्रमागत ip_conntrack_info ctinfo,
				    अचिन्हित पूर्णांक hooknum, अचिन्हित पूर्णांक hdrlen);

पूर्णांक nf_nat_ipv4_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
व्योम nf_nat_ipv4_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);

पूर्णांक nf_nat_ipv6_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
व्योम nf_nat_ipv6_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);

पूर्णांक nf_nat_inet_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
व्योम nf_nat_inet_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);

अचिन्हित पूर्णांक
nf_nat_inet_fn(व्योम *priv, काष्ठा sk_buff *skb,
	       स्थिर काष्ठा nf_hook_state *state);

अटल अंतरभूत पूर्णांक nf_nat_initialized(काष्ठा nf_conn *ct,
				     क्रमागत nf_nat_manip_type manip)
अणु
	अगर (manip == NF_NAT_MANIP_SRC)
		वापस ct->status & IPS_SRC_NAT_DONE;
	अन्यथा
		वापस ct->status & IPS_DST_NAT_DONE;
पूर्ण
#पूर्ण_अगर
