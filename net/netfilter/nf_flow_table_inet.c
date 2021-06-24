<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_tables.h>

अटल अचिन्हित पूर्णांक
nf_flow_offload_inet_hook(व्योम *priv, काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_hook_state *state)
अणु
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		वापस nf_flow_offload_ip_hook(priv, skb, state);
	हाल htons(ETH_P_IPV6):
		वापस nf_flow_offload_ipv6_hook(priv, skb, state);
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक nf_flow_rule_route_inet(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	स्थिर काष्ठा flow_offload_tuple *flow_tuple = &flow->tuplehash[dir].tuple;
	पूर्णांक err;

	चयन (flow_tuple->l3proto) अणु
	हाल NFPROTO_IPV4:
		err = nf_flow_rule_route_ipv4(net, flow, dir, flow_rule);
		अवरोध;
	हाल NFPROTO_IPV6:
		err = nf_flow_rule_route_ipv6(net, flow, dir, flow_rule);
		अवरोध;
	शेष:
		err = -1;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा nf_flowtable_type flowtable_inet = अणु
	.family		= NFPROTO_INET,
	.init		= nf_flow_table_init,
	.setup		= nf_flow_table_offload_setup,
	.action		= nf_flow_rule_route_inet,
	.मुक्त		= nf_flow_table_मुक्त,
	.hook		= nf_flow_offload_inet_hook,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nf_flow_inet_module_init(व्योम)
अणु
	nft_रेजिस्टर_flowtable_type(&flowtable_inet);

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_flow_inet_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_flowtable_type(&flowtable_inet);
पूर्ण

module_init(nf_flow_inet_module_init);
module_निकास(nf_flow_inet_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NF_FLOWTABLE(1); /* NFPROTO_INET */
MODULE_DESCRIPTION("Netfilter flow table mixed IPv4/IPv6 module");
