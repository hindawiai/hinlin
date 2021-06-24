<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BRIDGE_NETFILTER_H
#घोषणा __LINUX_BRIDGE_NETFILTER_H

#समावेश <uapi/linux/netfilter_bridge.h>
#समावेश <linux/skbuff.h>

काष्ठा nf_bridge_frag_data अणु
	अक्षर    mac[ETH_HLEN];
	bool    vlan_present;
	u16     vlan_tci;
	__be16  vlan_proto;
पूर्ण;

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)

पूर्णांक br_handle_frame_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल अंतरभूत व्योम br_drop_fake_rtable(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (dst && (dst->flags & DST_FAKE_RTABLE))
		skb_dst_drop(skb);
पूर्ण

अटल अंतरभूत काष्ठा nf_bridge_info *
nf_bridge_info_get(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_ext_find(skb, SKB_EXT_BRIDGE_NF);
पूर्ण

अटल अंतरभूत bool nf_bridge_info_exists(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_ext_exist(skb, SKB_EXT_BRIDGE_NF);
पूर्ण

अटल अंतरभूत पूर्णांक nf_bridge_get_physinअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (!nf_bridge)
		वापस 0;

	वापस nf_bridge->physindev ? nf_bridge->physindev->अगरindex : 0;
पूर्ण

अटल अंतरभूत पूर्णांक nf_bridge_get_physoutअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (!nf_bridge)
		वापस 0;

	वापस nf_bridge->physoutdev ? nf_bridge->physoutdev->अगरindex : 0;
पूर्ण

अटल अंतरभूत काष्ठा net_device *
nf_bridge_get_physindev(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	वापस nf_bridge ? nf_bridge->physindev : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_device *
nf_bridge_get_physoutdev(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	वापस nf_bridge ? nf_bridge->physoutdev : शून्य;
पूर्ण

अटल अंतरभूत bool nf_bridge_in_prerouting(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	वापस nf_bridge && nf_bridge->in_prerouting;
पूर्ण
#अन्यथा
#घोषणा br_drop_fake_rtable(skb)	        करो अणु पूर्ण जबतक (0)
अटल अंतरभूत bool nf_bridge_in_prerouting(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_BRIDGE_NETFILTER */

#पूर्ण_अगर
