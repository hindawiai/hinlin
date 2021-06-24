<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BR_NETFILTER_H_
#घोषणा _BR_NETFILTER_H_

#समावेश <linux/netfilter.h>

#समावेश "../../../net/bridge/br_private.h"

अटल अंतरभूत काष्ठा nf_bridge_info *nf_bridge_alloc(काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	काष्ठा nf_bridge_info *b = skb_ext_add(skb, SKB_EXT_BRIDGE_NF);

	अगर (b)
		स_रखो(b, 0, माप(*b));

	वापस b;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

व्योम nf_bridge_update_protocol(काष्ठा sk_buff *skb);

पूर्णांक br_nf_hook_thresh(अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
		      काष्ठा sk_buff *skb, काष्ठा net_device *indev,
		      काष्ठा net_device *outdev,
		      पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *,
				  काष्ठा sk_buff *));

अचिन्हित पूर्णांक nf_bridge_encap_header_len(स्थिर काष्ठा sk_buff *skb);

अटल अंतरभूत व्योम nf_bridge_push_encap_header(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = nf_bridge_encap_header_len(skb);

	skb_push(skb, len);
	skb->network_header -= len;
पूर्ण

पूर्णांक br_nf_pre_routing_finish_bridge(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल अंतरभूत काष्ठा rtable *bridge_parent_rtable(स्थिर काष्ठा net_device *dev)
अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	काष्ठा net_bridge_port *port;

	port = br_port_get_rcu(dev);
	वापस port ? &port->br->fake_rtable : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

काष्ठा net_device *setup_pre_routing(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा net *net);

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक br_validate_ipv6(काष्ठा net *net, काष्ठा sk_buff *skb);
अचिन्हित पूर्णांक br_nf_pre_routing_ipv6(व्योम *priv,
				    काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nf_hook_state *state);
#अन्यथा
अटल अंतरभूत पूर्णांक br_validate_ipv6(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
br_nf_pre_routing_ipv6(व्योम *priv, काष्ठा sk_buff *skb,
		       स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस NF_ACCEPT;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _BR_NETFILTER_H_ */
