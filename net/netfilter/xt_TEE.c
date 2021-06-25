<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	"TEE" target extension क्रम Xtables
 *	Copyright तऊ Sebastian Claथen, 2007
 *	Jan Engelhardt, 2007-2010
 *
 *	based on ipt_ROUTE.c from Cथऊdric de Launois
 *	<delaunois@info.ucl.be>
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/route.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/route.h>
#समावेश <net/netfilter/ipv4/nf_dup_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_dup_ipv6.h>
#समावेश <linux/netfilter/xt_TEE.h>

काष्ठा xt_tee_priv अणु
	काष्ठा list_head	list;
	काष्ठा xt_tee_tginfo	*tginfo;
	पूर्णांक			oअगर;
पूर्ण;

अटल अचिन्हित पूर्णांक tee_net_id __पढ़ो_mostly;
अटल स्थिर जोड़ nf_inet_addr tee_zero_address;

काष्ठा tee_net अणु
	काष्ठा list_head priv_list;
	/* lock protects the priv_list */
	काष्ठा mutex lock;
पूर्ण;

अटल अचिन्हित पूर्णांक
tee_tg4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tee_tginfo *info = par->targinfo;
	पूर्णांक oअगर = info->priv ? info->priv->oअगर : 0;

	nf_dup_ipv4(xt_net(par), skb, xt_hooknum(par), &info->gw.in, oअगर);

	वापस XT_CONTINUE;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल अचिन्हित पूर्णांक
tee_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tee_tginfo *info = par->targinfo;
	पूर्णांक oअगर = info->priv ? info->priv->oअगर : 0;

	nf_dup_ipv6(xt_net(par), skb, xt_hooknum(par), &info->gw.in6, oअगर);

	वापस XT_CONTINUE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tee_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा tee_net *tn = net_generic(net, tee_net_id);
	काष्ठा xt_tee_priv *priv;

	mutex_lock(&tn->lock);
	list_क्रम_each_entry(priv, &tn->priv_list, list) अणु
		चयन (event) अणु
		हाल NETDEV_REGISTER:
			अगर (!म_भेद(dev->name, priv->tginfo->oअगर))
				priv->oअगर = dev->अगरindex;
			अवरोध;
		हाल NETDEV_UNREGISTER:
			अगर (dev->अगरindex == priv->oअगर)
				priv->oअगर = -1;
			अवरोध;
		हाल NETDEV_CHANGENAME:
			अगर (!म_भेद(dev->name, priv->tginfo->oअगर))
				priv->oअगर = dev->अगरindex;
			अन्यथा अगर (dev->अगरindex == priv->oअगर)
				priv->oअगर = -1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tn->lock);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक tee_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा tee_net *tn = net_generic(par->net, tee_net_id);
	काष्ठा xt_tee_tginfo *info = par->targinfo;
	काष्ठा xt_tee_priv *priv;

	/* 0.0.0.0 and :: not allowed */
	अगर (स_भेद(&info->gw, &tee_zero_address,
		   माप(tee_zero_address)) == 0)
		वापस -EINVAL;

	अगर (info->oअगर[0]) अणु
		काष्ठा net_device *dev;

		अगर (info->oअगर[माप(info->oअगर)-1] != '\0')
			वापस -EINVAL;

		priv = kzalloc(माप(*priv), GFP_KERNEL);
		अगर (priv == शून्य)
			वापस -ENOMEM;

		priv->tginfo  = info;
		priv->oअगर     = -1;
		info->priv    = priv;

		dev = dev_get_by_name(par->net, info->oअगर);
		अगर (dev) अणु
			priv->oअगर = dev->अगरindex;
			dev_put(dev);
		पूर्ण
		mutex_lock(&tn->lock);
		list_add(&priv->list, &tn->priv_list);
		mutex_unlock(&tn->lock);
	पूर्ण अन्यथा
		info->priv = शून्य;

	अटल_key_slow_inc(&xt_tee_enabled);
	वापस 0;
पूर्ण

अटल व्योम tee_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	काष्ठा tee_net *tn = net_generic(par->net, tee_net_id);
	काष्ठा xt_tee_tginfo *info = par->targinfo;

	अगर (info->priv) अणु
		mutex_lock(&tn->lock);
		list_del(&info->priv->list);
		mutex_unlock(&tn->lock);
		kमुक्त(info->priv);
	पूर्ण
	अटल_key_slow_dec(&xt_tee_enabled);
पूर्ण

अटल काष्ठा xt_target tee_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "TEE",
		.revision   = 1,
		.family     = NFPROTO_IPV4,
		.target     = tee_tg4,
		.tarमाला_लोize = माप(काष्ठा xt_tee_tginfo),
		.usersize   = दुरत्व(काष्ठा xt_tee_tginfo, priv),
		.checkentry = tee_tg_check,
		.destroy    = tee_tg_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name       = "TEE",
		.revision   = 1,
		.family     = NFPROTO_IPV6,
		.target     = tee_tg6,
		.tarमाला_लोize = माप(काष्ठा xt_tee_tginfo),
		.usersize   = दुरत्व(काष्ठा xt_tee_tginfo, priv),
		.checkentry = tee_tg_check,
		.destroy    = tee_tg_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __net_init tee_net_init(काष्ठा net *net)
अणु
	काष्ठा tee_net *tn = net_generic(net, tee_net_id);

	INIT_LIST_HEAD(&tn->priv_list);
	mutex_init(&tn->lock);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations tee_net_ops = अणु
	.init = tee_net_init,
	.id   = &tee_net_id,
	.size = माप(काष्ठा tee_net),
पूर्ण;

अटल काष्ठा notअगरier_block tee_netdev_notअगरier = अणु
	.notअगरier_call = tee_netdev_event,
पूर्ण;

अटल पूर्णांक __init tee_tg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&tee_net_ops);
	अगर (ret < 0)
		वापस ret;

	ret = xt_रेजिस्टर_tarमाला_लो(tee_tg_reg, ARRAY_SIZE(tee_tg_reg));
	अगर (ret < 0)
		जाओ cleanup_subsys;

	ret = रेजिस्टर_netdevice_notअगरier(&tee_netdev_notअगरier);
	अगर (ret < 0)
		जाओ unरेजिस्टर_tarमाला_लो;

	वापस 0;

unरेजिस्टर_tarमाला_लो:
	xt_unरेजिस्टर_tarमाला_लो(tee_tg_reg, ARRAY_SIZE(tee_tg_reg));
cleanup_subsys:
	unरेजिस्टर_pernet_subsys(&tee_net_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास tee_tg_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&tee_netdev_notअगरier);
	xt_unरेजिस्टर_tarमाला_लो(tee_tg_reg, ARRAY_SIZE(tee_tg_reg));
	unरेजिस्टर_pernet_subsys(&tee_net_ops);
पूर्ण

module_init(tee_tg_init);
module_निकास(tee_tg_निकास);
MODULE_AUTHOR("Sebastian Claथen <sebastian.classen@freenet.ag>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: Reroute packet copy");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_TEE");
MODULE_ALIAS("ip6t_TEE");
