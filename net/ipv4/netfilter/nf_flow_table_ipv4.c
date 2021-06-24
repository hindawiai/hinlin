<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_tables.h>

अटल काष्ठा nf_flowtable_type flowtable_ipv4 = अणु
	.family		= NFPROTO_IPV4,
	.init		= nf_flow_table_init,
	.setup		= nf_flow_table_offload_setup,
	.action		= nf_flow_rule_route_ipv4,
	.मुक्त		= nf_flow_table_मुक्त,
	.hook		= nf_flow_offload_ip_hook,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nf_flow_ipv4_module_init(व्योम)
अणु
	nft_रेजिस्टर_flowtable_type(&flowtable_ipv4);

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_flow_ipv4_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_flowtable_type(&flowtable_ipv4);
पूर्ण

module_init(nf_flow_ipv4_module_init);
module_निकास(nf_flow_ipv4_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NF_FLOWTABLE(AF_INET);
MODULE_DESCRIPTION("Netfilter flow table support");
