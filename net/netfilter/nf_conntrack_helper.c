<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Helper handling क्रम netfilter. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2003,2004 USAGI/WIDE Project <http://www.linux-ipv6.org>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_log.h>

अटल DEFINE_MUTEX(nf_ct_helper_mutex);
काष्ठा hlist_head *nf_ct_helper_hash __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_helper_hash);
अचिन्हित पूर्णांक nf_ct_helper_hsize __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_helper_hsize);
अटल अचिन्हित पूर्णांक nf_ct_helper_count __पढ़ो_mostly;

अटल bool nf_ct_स्वतः_assign_helper __पढ़ो_mostly = false;
module_param_named(nf_conntrack_helper, nf_ct_स्वतः_assign_helper, bool, 0644);
MODULE_PARM_DESC(nf_conntrack_helper,
		 "Enable automatic conntrack helper assignment (default 0)");

अटल DEFINE_MUTEX(nf_ct_nat_helpers_mutex);
अटल काष्ठा list_head nf_ct_nat_helpers __पढ़ो_mostly;

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

/* Stupid hash, but collision मुक्त क्रम the शेष registrations of the
 * helpers currently in the kernel. */
अटल अचिन्हित पूर्णांक helper_hash(स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	वापस (((tuple->src.l3num << 8) | tuple->dst.protonum) ^
		(__क्रमce __u16)tuple->src.u.all) % nf_ct_helper_hsize;
पूर्ण

अटल काष्ठा nf_conntrack_helper *
__nf_ct_helper_find(स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conntrack_tuple_mask mask = अणु .src.u.all = htons(0xFFFF) पूर्ण;
	अचिन्हित पूर्णांक h;

	अगर (!nf_ct_helper_count)
		वापस शून्य;

	h = helper_hash(tuple);
	hlist_क्रम_each_entry_rcu(helper, &nf_ct_helper_hash[h], hnode) अणु
		अगर (nf_ct_tuple_src_mask_cmp(tuple, &helper->tuple, &mask))
			वापस helper;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nf_conntrack_helper *
__nf_conntrack_helper_find(स्थिर अक्षर *name, u16 l3num, u8 protonum)
अणु
	काष्ठा nf_conntrack_helper *h;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nf_ct_helper_hsize; i++) अणु
		hlist_क्रम_each_entry_rcu(h, &nf_ct_helper_hash[i], hnode) अणु
			अगर (म_भेद(h->name, name))
				जारी;

			अगर (h->tuple.src.l3num != NFPROTO_UNSPEC &&
			    h->tuple.src.l3num != l3num)
				जारी;

			अगर (h->tuple.dst.protonum == protonum)
				वापस h;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__nf_conntrack_helper_find);

काष्ठा nf_conntrack_helper *
nf_conntrack_helper_try_module_get(स्थिर अक्षर *name, u16 l3num, u8 protonum)
अणु
	काष्ठा nf_conntrack_helper *h;

	rcu_पढ़ो_lock();

	h = __nf_conntrack_helper_find(name, l3num, protonum);
#अगर_घोषित CONFIG_MODULES
	अगर (h == शून्य) अणु
		rcu_पढ़ो_unlock();
		अगर (request_module("nfct-helper-%s", name) == 0) अणु
			rcu_पढ़ो_lock();
			h = __nf_conntrack_helper_find(name, l3num, protonum);
		पूर्ण अन्यथा अणु
			वापस h;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (h != शून्य && !try_module_get(h->me))
		h = शून्य;
	अगर (h != शून्य && !refcount_inc_not_zero(&h->refcnt)) अणु
		module_put(h->me);
		h = शून्य;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस h;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helper_try_module_get);

व्योम nf_conntrack_helper_put(काष्ठा nf_conntrack_helper *helper)
अणु
	refcount_dec(&helper->refcnt);
	module_put(helper->me);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helper_put);

अटल काष्ठा nf_conntrack_nat_helper *
nf_conntrack_nat_helper_find(स्थिर अक्षर *mod_name)
अणु
	काष्ठा nf_conntrack_nat_helper *cur;
	bool found = false;

	list_क्रम_each_entry_rcu(cur, &nf_ct_nat_helpers, list) अणु
		अगर (!म_भेद(cur->mod_name, mod_name)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found ? cur : शून्य;
पूर्ण

पूर्णांक
nf_nat_helper_try_module_get(स्थिर अक्षर *name, u16 l3num, u8 protonum)
अणु
	काष्ठा nf_conntrack_helper *h;
	काष्ठा nf_conntrack_nat_helper *nat;
	अक्षर mod_name[NF_CT_HELPER_NAME_LEN];
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	h = __nf_conntrack_helper_find(name, l3num, protonum);
	अगर (!h) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	nat = nf_conntrack_nat_helper_find(h->nat_mod_name);
	अगर (!nat) अणु
		snम_लिखो(mod_name, माप(mod_name), "%s", h->nat_mod_name);
		rcu_पढ़ो_unlock();
		request_module(mod_name);

		rcu_पढ़ो_lock();
		nat = nf_conntrack_nat_helper_find(mod_name);
		अगर (!nat) अणु
			rcu_पढ़ो_unlock();
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (!try_module_get(nat->module))
		ret = -ENOENT;

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_helper_try_module_get);

व्योम nf_nat_helper_put(काष्ठा nf_conntrack_helper *helper)
अणु
	काष्ठा nf_conntrack_nat_helper *nat;

	nat = nf_conntrack_nat_helper_find(helper->nat_mod_name);
	अगर (WARN_ON_ONCE(!nat))
		वापस;

	module_put(nat->module);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_helper_put);

काष्ठा nf_conn_help *
nf_ct_helper_ext_add(काष्ठा nf_conn *ct, gfp_t gfp)
अणु
	काष्ठा nf_conn_help *help;

	help = nf_ct_ext_add(ct, NF_CT_EXT_HELPER, gfp);
	अगर (help)
		INIT_HLIST_HEAD(&help->expectations);
	अन्यथा
		pr_debug("failed to add helper extension area");
	वापस help;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_ext_add);

अटल काष्ठा nf_conntrack_helper *
nf_ct_lookup_helper(काष्ठा nf_conn *ct, काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	अगर (!cnet->sysctl_स्वतः_assign_helper) अणु
		अगर (cnet->स्वतः_assign_helper_warned)
			वापस शून्य;
		अगर (!__nf_ct_helper_find(&ct->tuplehash[IP_CT_सूची_REPLY].tuple))
			वापस शून्य;
		pr_info("nf_conntrack: default automatic helper assignment "
			"has been turned off for security reasons and CT-based "
			"firewall rule not found. Use the iptables CT target "
			"to attach helpers instead.\n");
		cnet->स्वतः_assign_helper_warned = true;
		वापस शून्य;
	पूर्ण

	वापस __nf_ct_helper_find(&ct->tuplehash[IP_CT_सूची_REPLY].tuple);
पूर्ण

पूर्णांक __nf_ct_try_assign_helper(काष्ठा nf_conn *ct, काष्ठा nf_conn *पंचांगpl,
			      gfp_t flags)
अणु
	काष्ठा nf_conntrack_helper *helper = शून्य;
	काष्ठा nf_conn_help *help;
	काष्ठा net *net = nf_ct_net(ct);

	/* We alपढ़ोy got a helper explicitly attached. The function
	 * nf_conntrack_alter_reply - in हाल NAT is in use - asks क्रम looking
	 * the helper up again. Since now the user is in full control of
	 * making consistent helper configurations, skip this स्वतःmatic
	 * re-lookup, otherwise we'll lose the helper.
	 */
	अगर (test_bit(IPS_HELPER_BIT, &ct->status))
		वापस 0;

	अगर (पंचांगpl != शून्य) अणु
		help = nfct_help(पंचांगpl);
		अगर (help != शून्य) अणु
			helper = help->helper;
			set_bit(IPS_HELPER_BIT, &ct->status);
		पूर्ण
	पूर्ण

	help = nfct_help(ct);

	अगर (helper == शून्य) अणु
		helper = nf_ct_lookup_helper(ct, net);
		अगर (helper == शून्य) अणु
			अगर (help)
				RCU_INIT_POINTER(help->helper, शून्य);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (help == शून्य) अणु
		help = nf_ct_helper_ext_add(ct, flags);
		अगर (help == शून्य)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* We only allow helper re-assignment of the same sort since
		 * we cannot पुनः_स्मृतिate the helper extension area.
		 */
		काष्ठा nf_conntrack_helper *पंचांगp = rcu_dereference(help->helper);

		अगर (पंचांगp && पंचांगp->help != helper->help) अणु
			RCU_INIT_POINTER(help->helper, शून्य);
			वापस 0;
		पूर्ण
	पूर्ण

	rcu_assign_poपूर्णांकer(help->helper, helper);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__nf_ct_try_assign_helper);

/* appropriate ct lock protecting must be taken by caller */
अटल पूर्णांक unhelp(काष्ठा nf_conn *ct, व्योम *me)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);

	अगर (help && rcu_dereference_raw(help->helper) == me) अणु
		nf_conntrack_event(IPCT_HELPER, ct);
		RCU_INIT_POINTER(help->helper, शून्य);
	पूर्ण

	/* We are not पूर्णांकended to delete this conntrack. */
	वापस 0;
पूर्ण

व्योम nf_ct_helper_destroy(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);
	काष्ठा nf_conntrack_helper *helper;

	अगर (help) अणु
		rcu_पढ़ो_lock();
		helper = rcu_dereference(help->helper);
		अगर (helper && helper->destroy)
			helper->destroy(ct);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल LIST_HEAD(nf_ct_helper_expectfn_list);

व्योम nf_ct_helper_expectfn_रेजिस्टर(काष्ठा nf_ct_helper_expectfn *n)
अणु
	spin_lock_bh(&nf_conntrack_expect_lock);
	list_add_rcu(&n->head, &nf_ct_helper_expectfn_list);
	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_expectfn_रेजिस्टर);

व्योम nf_ct_helper_expectfn_unरेजिस्टर(काष्ठा nf_ct_helper_expectfn *n)
अणु
	spin_lock_bh(&nf_conntrack_expect_lock);
	list_del_rcu(&n->head);
	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_expectfn_unरेजिस्टर);

/* Caller should hold the rcu lock */
काष्ठा nf_ct_helper_expectfn *
nf_ct_helper_expectfn_find_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा nf_ct_helper_expectfn *cur;
	bool found = false;

	list_क्रम_each_entry_rcu(cur, &nf_ct_helper_expectfn_list, head) अणु
		अगर (!म_भेद(cur->name, name)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found ? cur : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_expectfn_find_by_name);

/* Caller should hold the rcu lock */
काष्ठा nf_ct_helper_expectfn *
nf_ct_helper_expectfn_find_by_symbol(स्थिर व्योम *symbol)
अणु
	काष्ठा nf_ct_helper_expectfn *cur;
	bool found = false;

	list_क्रम_each_entry_rcu(cur, &nf_ct_helper_expectfn_list, head) अणु
		अगर (cur->expectfn == symbol) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found ? cur : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_expectfn_find_by_symbol);

__म_लिखो(3, 4)
व्योम nf_ct_helper_log(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct,
		      स्थिर अक्षर *fmt, ...)
अणु
	स्थिर काष्ठा nf_conn_help *help;
	स्थिर काष्ठा nf_conntrack_helper *helper;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	/* Called from the helper function, this call never fails */
	help = nfct_help(ct);

	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	helper = rcu_dereference(help->helper);

	nf_log_packet(nf_ct_net(ct), nf_ct_l3num(ct), 0, skb, शून्य, शून्य, शून्य,
		      "nf_ct_%s: dropping packet: %pV ", helper->name, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_log);

पूर्णांक nf_conntrack_helper_रेजिस्टर(काष्ठा nf_conntrack_helper *me)
अणु
	काष्ठा nf_conntrack_tuple_mask mask = अणु .src.u.all = htons(0xFFFF) पूर्ण;
	अचिन्हित पूर्णांक h = helper_hash(&me->tuple);
	काष्ठा nf_conntrack_helper *cur;
	पूर्णांक ret = 0, i;

	BUG_ON(me->expect_policy == शून्य);
	BUG_ON(me->expect_class_max >= NF_CT_MAX_EXPECT_CLASSES);
	BUG_ON(म_माप(me->name) > NF_CT_HELPER_NAME_LEN - 1);

	अगर (me->expect_policy->max_expected > NF_CT_EXPECT_MAX_CNT)
		वापस -EINVAL;

	mutex_lock(&nf_ct_helper_mutex);
	क्रम (i = 0; i < nf_ct_helper_hsize; i++) अणु
		hlist_क्रम_each_entry(cur, &nf_ct_helper_hash[i], hnode) अणु
			अगर (!म_भेद(cur->name, me->name) &&
			    (cur->tuple.src.l3num == NFPROTO_UNSPEC ||
			     cur->tuple.src.l3num == me->tuple.src.l3num) &&
			    cur->tuple.dst.protonum == me->tuple.dst.protonum) अणु
				ret = -EEXIST;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* aव्योम unpredictable behaviour क्रम स्वतः_assign_helper */
	अगर (!(me->flags & NF_CT_HELPER_F_USERSPACE)) अणु
		hlist_क्रम_each_entry(cur, &nf_ct_helper_hash[h], hnode) अणु
			अगर (nf_ct_tuple_src_mask_cmp(&cur->tuple, &me->tuple,
						     &mask)) अणु
				ret = -EEXIST;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	refcount_set(&me->refcnt, 1);
	hlist_add_head_rcu(&me->hnode, &nf_ct_helper_hash[h]);
	nf_ct_helper_count++;
out:
	mutex_unlock(&nf_ct_helper_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helper_रेजिस्टर);

अटल bool expect_iter_me(काष्ठा nf_conntrack_expect *exp, व्योम *data)
अणु
	काष्ठा nf_conn_help *help = nfct_help(exp->master);
	स्थिर काष्ठा nf_conntrack_helper *me = data;
	स्थिर काष्ठा nf_conntrack_helper *this;

	अगर (exp->helper == me)
		वापस true;

	this = rcu_dereference_रक्षित(help->helper,
					 lockdep_is_held(&nf_conntrack_expect_lock));
	वापस this == me;
पूर्ण

व्योम nf_conntrack_helper_unरेजिस्टर(काष्ठा nf_conntrack_helper *me)
अणु
	mutex_lock(&nf_ct_helper_mutex);
	hlist_del_rcu(&me->hnode);
	nf_ct_helper_count--;
	mutex_unlock(&nf_ct_helper_mutex);

	/* Make sure every nothing is still using the helper unless its a
	 * connection in the hash.
	 */
	synchronize_rcu();

	nf_ct_expect_iterate_destroy(expect_iter_me, शून्य);
	nf_ct_iterate_destroy(unhelp, me);

	/* Maybe someone has gotten the helper alपढ़ोy when unhelp above.
	 * So need to रुको it.
	 */
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helper_unरेजिस्टर);

व्योम nf_ct_helper_init(काष्ठा nf_conntrack_helper *helper,
		       u16 l3num, u16 protonum, स्थिर अक्षर *name,
		       u16 शेष_port, u16 spec_port, u32 id,
		       स्थिर काष्ठा nf_conntrack_expect_policy *exp_pol,
		       u32 expect_class_max,
		       पूर्णांक (*help)(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   काष्ठा nf_conn *ct,
				   क्रमागत ip_conntrack_info ctinfo),
		       पूर्णांक (*from_nlattr)(काष्ठा nlattr *attr,
					  काष्ठा nf_conn *ct),
		       काष्ठा module *module)
अणु
	helper->tuple.src.l3num = l3num;
	helper->tuple.dst.protonum = protonum;
	helper->tuple.src.u.all = htons(spec_port);
	helper->expect_policy = exp_pol;
	helper->expect_class_max = expect_class_max;
	helper->help = help;
	helper->from_nlattr = from_nlattr;
	helper->me = module;
	snम_लिखो(helper->nat_mod_name, माप(helper->nat_mod_name),
		 NF_NAT_HELPER_PREFIX "%s", name);

	अगर (spec_port == शेष_port)
		snम_लिखो(helper->name, माप(helper->name), "%s", name);
	अन्यथा
		snम_लिखो(helper->name, माप(helper->name), "%s-%u", name, id);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_helper_init);

पूर्णांक nf_conntrack_helpers_रेजिस्टर(काष्ठा nf_conntrack_helper *helper,
				  अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < n; i++) अणु
		err = nf_conntrack_helper_रेजिस्टर(&helper[i]);
		अगर (err < 0)
			जाओ err;
	पूर्ण

	वापस err;
err:
	अगर (i > 0)
		nf_conntrack_helpers_unरेजिस्टर(helper, i);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helpers_रेजिस्टर);

व्योम nf_conntrack_helpers_unरेजिस्टर(काष्ठा nf_conntrack_helper *helper,
				अचिन्हित पूर्णांक n)
अणु
	जबतक (n-- > 0)
		nf_conntrack_helper_unरेजिस्टर(&helper[n]);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_helpers_unरेजिस्टर);

व्योम nf_nat_helper_रेजिस्टर(काष्ठा nf_conntrack_nat_helper *nat)
अणु
	mutex_lock(&nf_ct_nat_helpers_mutex);
	list_add_rcu(&nat->list, &nf_ct_nat_helpers);
	mutex_unlock(&nf_ct_nat_helpers_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_helper_रेजिस्टर);

व्योम nf_nat_helper_unरेजिस्टर(काष्ठा nf_conntrack_nat_helper *nat)
अणु
	mutex_lock(&nf_ct_nat_helpers_mutex);
	list_del_rcu(&nat->list);
	mutex_unlock(&nf_ct_nat_helpers_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_helper_unरेजिस्टर);

अटल स्थिर काष्ठा nf_ct_ext_type helper_extend = अणु
	.len	= माप(काष्ठा nf_conn_help),
	.align	= __alignof__(काष्ठा nf_conn_help),
	.id	= NF_CT_EXT_HELPER,
पूर्ण;

व्योम nf_conntrack_helper_pernet_init(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	cnet->sysctl_स्वतः_assign_helper = nf_ct_स्वतः_assign_helper;
पूर्ण

पूर्णांक nf_conntrack_helper_init(व्योम)
अणु
	पूर्णांक ret;
	nf_ct_helper_hsize = 1; /* माला_लो rounded up to use one page */
	nf_ct_helper_hash =
		nf_ct_alloc_hashtable(&nf_ct_helper_hsize, 0);
	अगर (!nf_ct_helper_hash)
		वापस -ENOMEM;

	ret = nf_ct_extend_रेजिस्टर(&helper_extend);
	अगर (ret < 0) अणु
		pr_err("nf_ct_helper: Unable to register helper extension.\n");
		जाओ out_extend;
	पूर्ण

	INIT_LIST_HEAD(&nf_ct_nat_helpers);
	वापस 0;
out_extend:
	kvमुक्त(nf_ct_helper_hash);
	वापस ret;
पूर्ण

व्योम nf_conntrack_helper_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&helper_extend);
	kvमुक्त(nf_ct_helper_hash);
पूर्ण
