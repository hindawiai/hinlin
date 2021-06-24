<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_SYNPROXY_SHARED_H
#घोषणा _NF_SYNPROXY_SHARED_H

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/ip6_route.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>

काष्ठा synproxy_stats अणु
	अचिन्हित पूर्णांक			syn_received;
	अचिन्हित पूर्णांक			cookie_invalid;
	अचिन्हित पूर्णांक			cookie_valid;
	अचिन्हित पूर्णांक			cookie_retrans;
	अचिन्हित पूर्णांक			conn_reखोलोed;
पूर्ण;

काष्ठा synproxy_net अणु
	काष्ठा nf_conn			*पंचांगpl;
	काष्ठा synproxy_stats __percpu	*stats;
	अचिन्हित पूर्णांक			hook_ref4;
	अचिन्हित पूर्णांक			hook_ref6;
पूर्ण;

बाह्य अचिन्हित पूर्णांक synproxy_net_id;
अटल अंतरभूत काष्ठा synproxy_net *synproxy_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, synproxy_net_id);
पूर्ण

काष्ठा synproxy_options अणु
	u8				options;
	u8				wscale;
	u16				mss_option;
	u16				mss_encode;
	u32				tsval;
	u32				tsecr;
पूर्ण;

काष्ठा nf_synproxy_info;
bool synproxy_parse_options(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक करोff,
			    स्थिर काष्ठा tcphdr *th,
			    काष्ठा synproxy_options *opts);

व्योम synproxy_init_बारtamp_cookie(स्थिर काष्ठा nf_synproxy_info *info,
				    काष्ठा synproxy_options *opts);

व्योम synproxy_send_client_synack(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
				 स्थिर काष्ठा tcphdr *th,
				 स्थिर काष्ठा synproxy_options *opts);

bool synproxy_recv_client_ack(काष्ठा net *net,
			      स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा tcphdr *th,
			      काष्ठा synproxy_options *opts, u32 recv_seq);

काष्ठा nf_hook_state;

अचिन्हित पूर्णांक ipv4_synproxy_hook(व्योम *priv, काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_hook_state *nhs);
पूर्णांक nf_synproxy_ipv4_init(काष्ठा synproxy_net *snet, काष्ठा net *net);
व्योम nf_synproxy_ipv4_fini(काष्ठा synproxy_net *snet, काष्ठा net *net);

#अगर IS_ENABLED(CONFIG_IPV6)
व्योम synproxy_send_client_synack_ipv6(काष्ठा net *net,
				      स्थिर काष्ठा sk_buff *skb,
				      स्थिर काष्ठा tcphdr *th,
				      स्थिर काष्ठा synproxy_options *opts);

bool synproxy_recv_client_ack_ipv6(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा tcphdr *th,
				   काष्ठा synproxy_options *opts, u32 recv_seq);

अचिन्हित पूर्णांक ipv6_synproxy_hook(व्योम *priv, काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_hook_state *nhs);
पूर्णांक nf_synproxy_ipv6_init(काष्ठा synproxy_net *snet, काष्ठा net *net);
व्योम nf_synproxy_ipv6_fini(काष्ठा synproxy_net *snet, काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक
nf_synproxy_ipv6_init(काष्ठा synproxy_net *snet, काष्ठा net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
nf_synproxy_ipv6_fini(काष्ठा synproxy_net *snet, काष्ठा net *net) अणुपूर्ण;
#पूर्ण_अगर /* CONFIG_IPV6 */

#पूर्ण_अगर /* _NF_SYNPROXY_SHARED_H */
