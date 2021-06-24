<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NETFILTER_INGRESS_H_
#घोषणा _NETFILTER_INGRESS_H_

#समावेश <linux/netfilter.h>
#समावेश <linux/netdevice.h>

#अगर_घोषित CONFIG_NETFILTER_INGRESS
अटल अंतरभूत bool nf_hook_ingress_active(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_JUMP_LABEL
	अगर (!अटल_key_false(&nf_hooks_needed[NFPROTO_NETDEV][NF_NETDEV_INGRESS]))
		वापस false;
#पूर्ण_अगर
	वापस rcu_access_poपूर्णांकer(skb->dev->nf_hooks_ingress);
पूर्ण

/* caller must hold rcu_पढ़ो_lock */
अटल अंतरभूत पूर्णांक nf_hook_ingress(काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_hook_entries *e = rcu_dereference(skb->dev->nf_hooks_ingress);
	काष्ठा nf_hook_state state;
	पूर्णांक ret;

	/* Must recheck the ingress hook head, in the event it became शून्य
	 * after the check in nf_hook_ingress_active evaluated to true.
	 */
	अगर (unlikely(!e))
		वापस 0;

	nf_hook_state_init(&state, NF_NETDEV_INGRESS,
			   NFPROTO_NETDEV, skb->dev, शून्य, शून्य,
			   dev_net(skb->dev), शून्य);
	ret = nf_hook_slow(skb, &state, e, 0);
	अगर (ret == 0)
		वापस -1;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम nf_hook_ingress_init(काष्ठा net_device *dev)
अणु
	RCU_INIT_POINTER(dev->nf_hooks_ingress, शून्य);
पूर्ण
#अन्यथा /* CONFIG_NETFILTER_INGRESS */
अटल अंतरभूत पूर्णांक nf_hook_ingress_active(काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nf_hook_ingress(काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nf_hook_ingress_init(काष्ठा net_device *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_NETFILTER_INGRESS */
#पूर्ण_अगर /* _NETFILTER_INGRESS_H_ */
