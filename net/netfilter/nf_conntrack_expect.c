<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Expectation handling क्रम nf_conntrack. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2003,2004 USAGI/WIDE Project <http://www.linux-ipv6.org>
 * (c) 2005-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jhash.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/hash.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

अचिन्हित पूर्णांक nf_ct_expect_hsize __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_expect_hsize);

काष्ठा hlist_head *nf_ct_expect_hash __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_expect_hash);

अचिन्हित पूर्णांक nf_ct_expect_max __पढ़ो_mostly;

अटल काष्ठा kmem_cache *nf_ct_expect_cachep __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक nf_ct_expect_hashrnd __पढ़ो_mostly;

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

/* nf_conntrack_expect helper functions */
व्योम nf_ct_unlink_expect_report(काष्ठा nf_conntrack_expect *exp,
				u32 portid, पूर्णांक report)
अणु
	काष्ठा nf_conn_help *master_help = nfct_help(exp->master);
	काष्ठा net *net = nf_ct_exp_net(exp);
	काष्ठा nf_conntrack_net *cnet;

	WARN_ON(!master_help);
	WARN_ON(समयr_pending(&exp->समयout));

	hlist_del_rcu(&exp->hnode);

	cnet = net_generic(net, nf_conntrack_net_id);
	cnet->expect_count--;

	hlist_del_rcu(&exp->lnode);
	master_help->expecting[exp->class]--;

	nf_ct_expect_event_report(IPEXP_DESTROY, exp, portid, report);
	nf_ct_expect_put(exp);

	NF_CT_STAT_INC(net, expect_delete);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_unlink_expect_report);

अटल व्योम nf_ct_expectation_समयd_out(काष्ठा समयr_list *t)
अणु
	काष्ठा nf_conntrack_expect *exp = from_समयr(exp, t, समयout);

	spin_lock_bh(&nf_conntrack_expect_lock);
	nf_ct_unlink_expect(exp);
	spin_unlock_bh(&nf_conntrack_expect_lock);
	nf_ct_expect_put(exp);
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_expect_dst_hash(स्थिर काष्ठा net *n, स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	अचिन्हित पूर्णांक hash, seed;

	get_अक्रमom_once(&nf_ct_expect_hashrnd, माप(nf_ct_expect_hashrnd));

	seed = nf_ct_expect_hashrnd ^ net_hash_mix(n);

	hash = jhash2(tuple->dst.u3.all, ARRAY_SIZE(tuple->dst.u3.all),
		      (((tuple->dst.protonum ^ tuple->src.l3num) << 16) |
		       (__क्रमce __u16)tuple->dst.u.all) ^ seed);

	वापस reciprocal_scale(hash, nf_ct_expect_hsize);
पूर्ण

अटल bool
nf_ct_exp_equal(स्थिर काष्ठा nf_conntrack_tuple *tuple,
		स्थिर काष्ठा nf_conntrack_expect *i,
		स्थिर काष्ठा nf_conntrack_zone *zone,
		स्थिर काष्ठा net *net)
अणु
	वापस nf_ct_tuple_mask_cmp(tuple, &i->tuple, &i->mask) &&
	       net_eq(net, nf_ct_net(i->master)) &&
	       nf_ct_zone_equal_any(i->master, zone);
पूर्ण

bool nf_ct_हटाओ_expect(काष्ठा nf_conntrack_expect *exp)
अणु
	अगर (del_समयr(&exp->समयout)) अणु
		nf_ct_unlink_expect(exp);
		nf_ct_expect_put(exp);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_हटाओ_expect);

काष्ठा nf_conntrack_expect *
__nf_ct_expect_find(काष्ठा net *net,
		    स्थिर काष्ठा nf_conntrack_zone *zone,
		    स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	काष्ठा nf_conntrack_expect *i;
	अचिन्हित पूर्णांक h;

	अगर (!cnet->expect_count)
		वापस शून्य;

	h = nf_ct_expect_dst_hash(net, tuple);
	hlist_क्रम_each_entry_rcu(i, &nf_ct_expect_hash[h], hnode) अणु
		अगर (nf_ct_exp_equal(tuple, i, zone, net))
			वापस i;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__nf_ct_expect_find);

/* Just find a expectation corresponding to a tuple. */
काष्ठा nf_conntrack_expect *
nf_ct_expect_find_get(काष्ठा net *net,
		      स्थिर काष्ठा nf_conntrack_zone *zone,
		      स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा nf_conntrack_expect *i;

	rcu_पढ़ो_lock();
	i = __nf_ct_expect_find(net, zone, tuple);
	अगर (i && !refcount_inc_not_zero(&i->use))
		i = शून्य;
	rcu_पढ़ो_unlock();

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_find_get);

/* If an expectation क्रम this connection is found, it माला_लो delete from
 * global list then वापसed. */
काष्ठा nf_conntrack_expect *
nf_ct_find_expectation(काष्ठा net *net,
		       स्थिर काष्ठा nf_conntrack_zone *zone,
		       स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	काष्ठा nf_conntrack_expect *i, *exp = शून्य;
	अचिन्हित पूर्णांक h;

	अगर (!cnet->expect_count)
		वापस शून्य;

	h = nf_ct_expect_dst_hash(net, tuple);
	hlist_क्रम_each_entry(i, &nf_ct_expect_hash[h], hnode) अणु
		अगर (!(i->flags & NF_CT_EXPECT_INACTIVE) &&
		    nf_ct_exp_equal(tuple, i, zone, net)) अणु
			exp = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!exp)
		वापस शून्य;

	/* If master is not in hash table yet (ie. packet hasn't left
	   this machine yet), how can other end know about expected?
	   Hence these are not the droids you are looking क्रम (अगर
	   master ct never got confirmed, we'd hold a reference to it
	   and weird things would happen to future packets). */
	अगर (!nf_ct_is_confirmed(exp->master))
		वापस शून्य;

	/* Aव्योम race with other CPUs, that क्रम exp->master ct, is
	 * about to invoke ->destroy(), or nf_ct_delete() via समयout
	 * or early_drop().
	 *
	 * The atomic_inc_not_zero() check tells:  If that fails, we
	 * know that the ct is being destroyed.  If it succeeds, we
	 * can be sure the ct cannot disappear underneath.
	 */
	अगर (unlikely(nf_ct_is_dying(exp->master) ||
		     !atomic_inc_not_zero(&exp->master->ct_general.use)))
		वापस शून्य;

	अगर (exp->flags & NF_CT_EXPECT_PERMANENT) अणु
		refcount_inc(&exp->use);
		वापस exp;
	पूर्ण अन्यथा अगर (del_समयr(&exp->समयout)) अणु
		nf_ct_unlink_expect(exp);
		वापस exp;
	पूर्ण
	/* Unकरो exp->master refcnt increase, अगर del_समयr() failed */
	nf_ct_put(exp->master);

	वापस शून्य;
पूर्ण

/* delete all expectations क्रम this conntrack */
व्योम nf_ct_हटाओ_expectations(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा hlist_node *next;

	/* Optimization: most connection never expect any others. */
	अगर (!help)
		वापस;

	spin_lock_bh(&nf_conntrack_expect_lock);
	hlist_क्रम_each_entry_safe(exp, next, &help->expectations, lnode) अणु
		nf_ct_हटाओ_expect(exp);
	पूर्ण
	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_हटाओ_expectations);

/* Would two expected things clash? */
अटल अंतरभूत पूर्णांक expect_clash(स्थिर काष्ठा nf_conntrack_expect *a,
			       स्थिर काष्ठा nf_conntrack_expect *b)
अणु
	/* Part covered by पूर्णांकersection of masks must be unequal,
	   otherwise they clash */
	काष्ठा nf_conntrack_tuple_mask पूर्णांकersect_mask;
	पूर्णांक count;

	पूर्णांकersect_mask.src.u.all = a->mask.src.u.all & b->mask.src.u.all;

	क्रम (count = 0; count < NF_CT_TUPLE_L3SIZE; count++)अणु
		पूर्णांकersect_mask.src.u3.all[count] =
			a->mask.src.u3.all[count] & b->mask.src.u3.all[count];
	पूर्ण

	वापस nf_ct_tuple_mask_cmp(&a->tuple, &b->tuple, &पूर्णांकersect_mask) &&
	       net_eq(nf_ct_net(a->master), nf_ct_net(b->master)) &&
	       nf_ct_zone_equal_any(a->master, nf_ct_zone(b->master));
पूर्ण

अटल अंतरभूत पूर्णांक expect_matches(स्थिर काष्ठा nf_conntrack_expect *a,
				 स्थिर काष्ठा nf_conntrack_expect *b)
अणु
	वापस nf_ct_tuple_equal(&a->tuple, &b->tuple) &&
	       nf_ct_tuple_mask_equal(&a->mask, &b->mask) &&
	       net_eq(nf_ct_net(a->master), nf_ct_net(b->master)) &&
	       nf_ct_zone_equal_any(a->master, nf_ct_zone(b->master));
पूर्ण

अटल bool master_matches(स्थिर काष्ठा nf_conntrack_expect *a,
			   स्थिर काष्ठा nf_conntrack_expect *b,
			   अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & NF_CT_EXP_F_SKIP_MASTER)
		वापस true;

	वापस a->master == b->master;
पूर्ण

/* Generally a bad idea to call this: could have matched alपढ़ोy. */
व्योम nf_ct_unexpect_related(काष्ठा nf_conntrack_expect *exp)
अणु
	spin_lock_bh(&nf_conntrack_expect_lock);
	nf_ct_हटाओ_expect(exp);
	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_unexpect_related);

/* We करोn't increase the master conntrack refcount क्रम non-fulfilled
 * conntracks. During the conntrack deकाष्ठाion, the expectations are
 * always समाप्तed beक्रमe the conntrack itself */
काष्ठा nf_conntrack_expect *nf_ct_expect_alloc(काष्ठा nf_conn *me)
अणु
	काष्ठा nf_conntrack_expect *new;

	new = kmem_cache_alloc(nf_ct_expect_cachep, GFP_ATOMIC);
	अगर (!new)
		वापस शून्य;

	new->master = me;
	refcount_set(&new->use, 1);
	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_alloc);

व्योम nf_ct_expect_init(काष्ठा nf_conntrack_expect *exp, अचिन्हित पूर्णांक class,
		       u_पूर्णांक8_t family,
		       स्थिर जोड़ nf_inet_addr *saddr,
		       स्थिर जोड़ nf_inet_addr *daddr,
		       u_पूर्णांक8_t proto, स्थिर __be16 *src, स्थिर __be16 *dst)
अणु
	पूर्णांक len;

	अगर (family == AF_INET)
		len = 4;
	अन्यथा
		len = 16;

	exp->flags = 0;
	exp->class = class;
	exp->expectfn = शून्य;
	exp->helper = शून्य;
	exp->tuple.src.l3num = family;
	exp->tuple.dst.protonum = proto;

	अगर (saddr) अणु
		स_नकल(&exp->tuple.src.u3, saddr, len);
		अगर (माप(exp->tuple.src.u3) > len)
			/* address needs to be cleared क्रम nf_ct_tuple_equal */
			स_रखो((व्योम *)&exp->tuple.src.u3 + len, 0x00,
			       माप(exp->tuple.src.u3) - len);
		स_रखो(&exp->mask.src.u3, 0xFF, len);
		अगर (माप(exp->mask.src.u3) > len)
			स_रखो((व्योम *)&exp->mask.src.u3 + len, 0x00,
			       माप(exp->mask.src.u3) - len);
	पूर्ण अन्यथा अणु
		स_रखो(&exp->tuple.src.u3, 0x00, माप(exp->tuple.src.u3));
		स_रखो(&exp->mask.src.u3, 0x00, माप(exp->mask.src.u3));
	पूर्ण

	अगर (src) अणु
		exp->tuple.src.u.all = *src;
		exp->mask.src.u.all = htons(0xFFFF);
	पूर्ण अन्यथा अणु
		exp->tuple.src.u.all = 0;
		exp->mask.src.u.all = 0;
	पूर्ण

	स_नकल(&exp->tuple.dst.u3, daddr, len);
	अगर (माप(exp->tuple.dst.u3) > len)
		/* address needs to be cleared क्रम nf_ct_tuple_equal */
		स_रखो((व्योम *)&exp->tuple.dst.u3 + len, 0x00,
		       माप(exp->tuple.dst.u3) - len);

	exp->tuple.dst.u.all = *dst;

#अगर IS_ENABLED(CONFIG_NF_NAT)
	स_रखो(&exp->saved_addr, 0, माप(exp->saved_addr));
	स_रखो(&exp->saved_proto, 0, माप(exp->saved_proto));
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_init);

अटल व्योम nf_ct_expect_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा nf_conntrack_expect *exp;

	exp = container_of(head, काष्ठा nf_conntrack_expect, rcu);
	kmem_cache_मुक्त(nf_ct_expect_cachep, exp);
पूर्ण

व्योम nf_ct_expect_put(काष्ठा nf_conntrack_expect *exp)
अणु
	अगर (refcount_dec_and_test(&exp->use))
		call_rcu(&exp->rcu, nf_ct_expect_मुक्त_rcu);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_put);

अटल व्योम nf_ct_expect_insert(काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_conntrack_net *cnet;
	काष्ठा nf_conn_help *master_help = nfct_help(exp->master);
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा net *net = nf_ct_exp_net(exp);
	अचिन्हित पूर्णांक h = nf_ct_expect_dst_hash(net, &exp->tuple);

	/* two references : one क्रम hash insert, one क्रम the समयr */
	refcount_add(2, &exp->use);

	समयr_setup(&exp->समयout, nf_ct_expectation_समयd_out, 0);
	helper = rcu_dereference_रक्षित(master_help->helper,
					   lockdep_is_held(&nf_conntrack_expect_lock));
	अगर (helper) अणु
		exp->समयout.expires = jअगरfies +
			helper->expect_policy[exp->class].समयout * HZ;
	पूर्ण
	add_समयr(&exp->समयout);

	hlist_add_head_rcu(&exp->lnode, &master_help->expectations);
	master_help->expecting[exp->class]++;

	hlist_add_head_rcu(&exp->hnode, &nf_ct_expect_hash[h]);
	cnet = net_generic(net, nf_conntrack_net_id);
	cnet->expect_count++;

	NF_CT_STAT_INC(net, expect_create);
पूर्ण

/* Race with expectations being used means we could have none to find; OK. */
अटल व्योम evict_oldest_expect(काष्ठा nf_conn *master,
				काष्ठा nf_conntrack_expect *new)
अणु
	काष्ठा nf_conn_help *master_help = nfct_help(master);
	काष्ठा nf_conntrack_expect *exp, *last = शून्य;

	hlist_क्रम_each_entry(exp, &master_help->expectations, lnode) अणु
		अगर (exp->class == new->class)
			last = exp;
	पूर्ण

	अगर (last)
		nf_ct_हटाओ_expect(last);
पूर्ण

अटल अंतरभूत पूर्णांक __nf_ct_expect_check(काष्ठा nf_conntrack_expect *expect,
				       अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा nf_conntrack_expect_policy *p;
	काष्ठा nf_conntrack_expect *i;
	काष्ठा nf_conntrack_net *cnet;
	काष्ठा nf_conn *master = expect->master;
	काष्ठा nf_conn_help *master_help = nfct_help(master);
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा net *net = nf_ct_exp_net(expect);
	काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक h;
	पूर्णांक ret = 0;

	अगर (!master_help) अणु
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण
	h = nf_ct_expect_dst_hash(net, &expect->tuple);
	hlist_क्रम_each_entry_safe(i, next, &nf_ct_expect_hash[h], hnode) अणु
		अगर (master_matches(i, expect, flags) &&
		    expect_matches(i, expect)) अणु
			अगर (i->class != expect->class ||
			    i->master != expect->master)
				वापस -EALREADY;

			अगर (nf_ct_हटाओ_expect(i))
				अवरोध;
		पूर्ण अन्यथा अगर (expect_clash(i, expect)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण
	/* Will be over limit? */
	helper = rcu_dereference_रक्षित(master_help->helper,
					   lockdep_is_held(&nf_conntrack_expect_lock));
	अगर (helper) अणु
		p = &helper->expect_policy[expect->class];
		अगर (p->max_expected &&
		    master_help->expecting[expect->class] >= p->max_expected) अणु
			evict_oldest_expect(master, expect);
			अगर (master_help->expecting[expect->class]
						>= p->max_expected) अणु
				ret = -EMखाता;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	cnet = net_generic(net, nf_conntrack_net_id);
	अगर (cnet->expect_count >= nf_ct_expect_max) अणु
		net_warn_ratelimited("nf_conntrack: expectation table full\n");
		ret = -EMखाता;
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक nf_ct_expect_related_report(काष्ठा nf_conntrack_expect *expect,
				u32 portid, पूर्णांक report, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;

	spin_lock_bh(&nf_conntrack_expect_lock);
	ret = __nf_ct_expect_check(expect, flags);
	अगर (ret < 0)
		जाओ out;

	nf_ct_expect_insert(expect);

	spin_unlock_bh(&nf_conntrack_expect_lock);
	nf_ct_expect_event_report(IPEXP_NEW, expect, portid, report);
	वापस 0;
out:
	spin_unlock_bh(&nf_conntrack_expect_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_related_report);

व्योम nf_ct_expect_iterate_destroy(bool (*iter)(काष्ठा nf_conntrack_expect *e, व्योम *data),
				  व्योम *data)
अणु
	काष्ठा nf_conntrack_expect *exp;
	स्थिर काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक i;

	spin_lock_bh(&nf_conntrack_expect_lock);

	क्रम (i = 0; i < nf_ct_expect_hsize; i++) अणु
		hlist_क्रम_each_entry_safe(exp, next,
					  &nf_ct_expect_hash[i],
					  hnode) अणु
			अगर (iter(exp, data) && del_समयr(&exp->समयout)) अणु
				nf_ct_unlink_expect(exp);
				nf_ct_expect_put(exp);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_iterate_destroy);

व्योम nf_ct_expect_iterate_net(काष्ठा net *net,
			      bool (*iter)(काष्ठा nf_conntrack_expect *e, व्योम *data),
			      व्योम *data,
			      u32 portid, पूर्णांक report)
अणु
	काष्ठा nf_conntrack_expect *exp;
	स्थिर काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक i;

	spin_lock_bh(&nf_conntrack_expect_lock);

	क्रम (i = 0; i < nf_ct_expect_hsize; i++) अणु
		hlist_क्रम_each_entry_safe(exp, next,
					  &nf_ct_expect_hash[i],
					  hnode) अणु

			अगर (!net_eq(nf_ct_exp_net(exp), net))
				जारी;

			अगर (iter(exp, data) && del_समयr(&exp->समयout)) अणु
				nf_ct_unlink_expect_report(exp, portid, report);
				nf_ct_expect_put(exp);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_iterate_net);

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
काष्ठा ct_expect_iter_state अणु
	काष्ठा seq_net_निजी p;
	अचिन्हित पूर्णांक bucket;
पूर्ण;

अटल काष्ठा hlist_node *ct_expect_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा ct_expect_iter_state *st = seq->निजी;
	काष्ठा hlist_node *n;

	क्रम (st->bucket = 0; st->bucket < nf_ct_expect_hsize; st->bucket++) अणु
		n = rcu_dereference(hlist_first_rcu(&nf_ct_expect_hash[st->bucket]));
		अगर (n)
			वापस n;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_node *ct_expect_get_next(काष्ठा seq_file *seq,
					     काष्ठा hlist_node *head)
अणु
	काष्ठा ct_expect_iter_state *st = seq->निजी;

	head = rcu_dereference(hlist_next_rcu(head));
	जबतक (head == शून्य) अणु
		अगर (++st->bucket >= nf_ct_expect_hsize)
			वापस शून्य;
		head = rcu_dereference(hlist_first_rcu(&nf_ct_expect_hash[st->bucket]));
	पूर्ण
	वापस head;
पूर्ण

अटल काष्ठा hlist_node *ct_expect_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा hlist_node *head = ct_expect_get_first(seq);

	अगर (head)
		जबतक (pos && (head = ct_expect_get_next(seq, head)))
			pos--;
	वापस pos ? शून्य : head;
पूर्ण

अटल व्योम *exp_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस ct_expect_get_idx(seq, *pos);
पूर्ण

अटल व्योम *exp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस ct_expect_get_next(seq, v);
पूर्ण

अटल व्योम exp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक exp_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nf_conntrack_expect *expect;
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा hlist_node *n = v;
	अक्षर *delim = "";

	expect = hlist_entry(n, काष्ठा nf_conntrack_expect, hnode);

	अगर (expect->समयout.function)
		seq_म_लिखो(s, "%ld ", समयr_pending(&expect->समयout)
			   ? (दीर्घ)(expect->समयout.expires - jअगरfies)/HZ : 0);
	अन्यथा
		seq_माला_दो(s, "- ");
	seq_म_लिखो(s, "l3proto = %u proto=%u ",
		   expect->tuple.src.l3num,
		   expect->tuple.dst.protonum);
	prपूर्णांक_tuple(s, &expect->tuple,
		    nf_ct_l4proto_find(expect->tuple.dst.protonum));

	अगर (expect->flags & NF_CT_EXPECT_PERMANENT) अणु
		seq_माला_दो(s, "PERMANENT");
		delim = ",";
	पूर्ण
	अगर (expect->flags & NF_CT_EXPECT_INACTIVE) अणु
		seq_म_लिखो(s, "%sINACTIVE", delim);
		delim = ",";
	पूर्ण
	अगर (expect->flags & NF_CT_EXPECT_USERSPACE)
		seq_म_लिखो(s, "%sUSERSPACE", delim);

	helper = rcu_dereference(nfct_help(expect->master)->helper);
	अगर (helper) अणु
		seq_म_लिखो(s, "%s%s", expect->flags ? " " : "", helper->name);
		अगर (helper->expect_policy[expect->class].name[0])
			seq_म_लिखो(s, "/%s",
				   helper->expect_policy[expect->class].name);
	पूर्ण

	seq_अ_दो(s, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations exp_seq_ops = अणु
	.start = exp_seq_start,
	.next = exp_seq_next,
	.stop = exp_seq_stop,
	.show = exp_seq_show
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_PROCFS */

अटल पूर्णांक exp_proc_init(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	काष्ठा proc_dir_entry *proc;
	kuid_t root_uid;
	kgid_t root_gid;

	proc = proc_create_net("nf_conntrack_expect", 0440, net->proc_net,
			&exp_seq_ops, माप(काष्ठा ct_expect_iter_state));
	अगर (!proc)
		वापस -ENOMEM;

	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_PROCFS */
	वापस 0;
पूर्ण

अटल व्योम exp_proc_हटाओ(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	हटाओ_proc_entry("nf_conntrack_expect", net->proc_net);
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_PROCFS */
पूर्ण

module_param_named(expect_hashsize, nf_ct_expect_hsize, uपूर्णांक, 0400);

पूर्णांक nf_conntrack_expect_pernet_init(काष्ठा net *net)
अणु
	वापस exp_proc_init(net);
पूर्ण

व्योम nf_conntrack_expect_pernet_fini(काष्ठा net *net)
अणु
	exp_proc_हटाओ(net);
पूर्ण

पूर्णांक nf_conntrack_expect_init(व्योम)
अणु
	अगर (!nf_ct_expect_hsize) अणु
		nf_ct_expect_hsize = nf_conntrack_htable_size / 256;
		अगर (!nf_ct_expect_hsize)
			nf_ct_expect_hsize = 1;
	पूर्ण
	nf_ct_expect_max = nf_ct_expect_hsize * 4;
	nf_ct_expect_cachep = kmem_cache_create("nf_conntrack_expect",
				माप(काष्ठा nf_conntrack_expect),
				0, 0, शून्य);
	अगर (!nf_ct_expect_cachep)
		वापस -ENOMEM;

	nf_ct_expect_hash = nf_ct_alloc_hashtable(&nf_ct_expect_hsize, 0);
	अगर (!nf_ct_expect_hash) अणु
		kmem_cache_destroy(nf_ct_expect_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nf_conntrack_expect_fini(व्योम)
अणु
	rcu_barrier(); /* Wait क्रम call_rcu() beक्रमe destroy */
	kmem_cache_destroy(nf_ct_expect_cachep);
	kvमुक्त(nf_ct_expect_hash);
पूर्ण
