<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2007 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/gen_stats.h>
#समावेश <linux/jhash.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <net/gen_stats.h>
#समावेश <net/netlink.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_RATEEST.h>
#समावेश <net/netfilter/xt_rateest.h>

#घोषणा RATEEST_HSIZE	16

काष्ठा xt_rateest_net अणु
	काष्ठा mutex hash_lock;
	काष्ठा hlist_head hash[RATEEST_HSIZE];
पूर्ण;

अटल अचिन्हित पूर्णांक xt_rateest_id;

अटल अचिन्हित पूर्णांक jhash_rnd __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक xt_rateest_hash(स्थिर अक्षर *name)
अणु
	वापस jhash(name, माप_field(काष्ठा xt_rateest, name), jhash_rnd) &
	       (RATEEST_HSIZE - 1);
पूर्ण

अटल व्योम xt_rateest_hash_insert(काष्ठा xt_rateest_net *xn,
				   काष्ठा xt_rateest *est)
अणु
	अचिन्हित पूर्णांक h;

	h = xt_rateest_hash(est->name);
	hlist_add_head(&est->list, &xn->hash[h]);
पूर्ण

अटल काष्ठा xt_rateest *__xt_rateest_lookup(काष्ठा xt_rateest_net *xn,
					      स्थिर अक्षर *name)
अणु
	काष्ठा xt_rateest *est;
	अचिन्हित पूर्णांक h;

	h = xt_rateest_hash(name);
	hlist_क्रम_each_entry(est, &xn->hash[h], list) अणु
		अगर (म_भेद(est->name, name) == 0) अणु
			est->refcnt++;
			वापस est;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा xt_rateest *xt_rateest_lookup(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_rateest_net *xn = net_generic(net, xt_rateest_id);
	काष्ठा xt_rateest *est;

	mutex_lock(&xn->hash_lock);
	est = __xt_rateest_lookup(xn, name);
	mutex_unlock(&xn->hash_lock);
	वापस est;
पूर्ण
EXPORT_SYMBOL_GPL(xt_rateest_lookup);

व्योम xt_rateest_put(काष्ठा net *net, काष्ठा xt_rateest *est)
अणु
	काष्ठा xt_rateest_net *xn = net_generic(net, xt_rateest_id);

	mutex_lock(&xn->hash_lock);
	अगर (--est->refcnt == 0) अणु
		hlist_del(&est->list);
		gen_समाप्त_estimator(&est->rate_est);
		/*
		 * gen_estimator est_समयr() might access est->lock or bstats,
		 * रुको a RCU grace period beक्रमe मुक्तing 'est'
		 */
		kमुक्त_rcu(est, rcu);
	पूर्ण
	mutex_unlock(&xn->hash_lock);
पूर्ण
EXPORT_SYMBOL_GPL(xt_rateest_put);

अटल अचिन्हित पूर्णांक
xt_rateest_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_rateest_target_info *info = par->targinfo;
	काष्ठा gnet_stats_basic_packed *stats = &info->est->bstats;

	spin_lock_bh(&info->est->lock);
	stats->bytes += skb->len;
	stats->packets++;
	spin_unlock_bh(&info->est->lock);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक xt_rateest_tg_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_rateest_net *xn = net_generic(par->net, xt_rateest_id);
	काष्ठा xt_rateest_target_info *info = par->targinfo;
	काष्ठा xt_rateest *est;
	काष्ठा अणु
		काष्ठा nlattr		opt;
		काष्ठा gnet_estimator	est;
	पूर्ण cfg;
	पूर्णांक ret;

	अगर (strnlen(info->name, माप(est->name)) >= माप(est->name))
		वापस -ENAMETOOLONG;

	net_get_अक्रमom_once(&jhash_rnd, माप(jhash_rnd));

	mutex_lock(&xn->hash_lock);
	est = __xt_rateest_lookup(xn, info->name);
	अगर (est) अणु
		mutex_unlock(&xn->hash_lock);
		/*
		 * If estimator parameters are specअगरied, they must match the
		 * existing estimator.
		 */
		अगर ((!info->पूर्णांकerval && !info->ewma_log) ||
		    (info->पूर्णांकerval != est->params.पूर्णांकerval ||
		     info->ewma_log != est->params.ewma_log)) अणु
			xt_rateest_put(par->net, est);
			वापस -EINVAL;
		पूर्ण
		info->est = est;
		वापस 0;
	पूर्ण

	ret = -ENOMEM;
	est = kzalloc(माप(*est), GFP_KERNEL);
	अगर (!est)
		जाओ err1;

	strlcpy(est->name, info->name, माप(est->name));
	spin_lock_init(&est->lock);
	est->refcnt		= 1;
	est->params.पूर्णांकerval	= info->पूर्णांकerval;
	est->params.ewma_log	= info->ewma_log;

	cfg.opt.nla_len		= nla_attr_size(माप(cfg.est));
	cfg.opt.nla_type	= TCA_STATS_RATE_EST;
	cfg.est.पूर्णांकerval	= info->पूर्णांकerval;
	cfg.est.ewma_log	= info->ewma_log;

	ret = gen_new_estimator(&est->bstats, शून्य, &est->rate_est,
				&est->lock, शून्य, &cfg.opt);
	अगर (ret < 0)
		जाओ err2;

	info->est = est;
	xt_rateest_hash_insert(xn, est);
	mutex_unlock(&xn->hash_lock);
	वापस 0;

err2:
	kमुक्त(est);
err1:
	mutex_unlock(&xn->hash_lock);
	वापस ret;
पूर्ण

अटल व्योम xt_rateest_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	काष्ठा xt_rateest_target_info *info = par->targinfo;

	xt_rateest_put(par->net, info->est);
पूर्ण

अटल काष्ठा xt_target xt_rateest_tg_reg __पढ़ो_mostly = अणु
	.name       = "RATEEST",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.target     = xt_rateest_tg,
	.checkentry = xt_rateest_tg_checkentry,
	.destroy    = xt_rateest_tg_destroy,
	.tarमाला_लोize = माप(काष्ठा xt_rateest_target_info),
	.usersize   = दुरत्व(काष्ठा xt_rateest_target_info, est),
	.me         = THIS_MODULE,
पूर्ण;

अटल __net_init पूर्णांक xt_rateest_net_init(काष्ठा net *net)
अणु
	काष्ठा xt_rateest_net *xn = net_generic(net, xt_rateest_id);
	पूर्णांक i;

	mutex_init(&xn->hash_lock);
	क्रम (i = 0; i < ARRAY_SIZE(xn->hash); i++)
		INIT_HLIST_HEAD(&xn->hash[i]);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations xt_rateest_net_ops = अणु
	.init = xt_rateest_net_init,
	.id   = &xt_rateest_id,
	.size = माप(काष्ठा xt_rateest_net),
पूर्ण;

अटल पूर्णांक __init xt_rateest_tg_init(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_pernet_subsys(&xt_rateest_net_ops);

	अगर (err)
		वापस err;
	वापस xt_रेजिस्टर_target(&xt_rateest_tg_reg);
पूर्ण

अटल व्योम __निकास xt_rateest_tg_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&xt_rateest_tg_reg);
	unरेजिस्टर_pernet_subsys(&xt_rateest_net_ops);
पूर्ण


MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: packet rate estimator");
MODULE_ALIAS("ipt_RATEEST");
MODULE_ALIAS("ip6t_RATEEST");
module_init(xt_rateest_tg_init);
module_निकास(xt_rateest_tg_fini);
