<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xfrm_policy.c
 *
 * Changes:
 *	Mitsuru KANDA @USAGI
 * 	Kazunori MIYAZAWA @USAGI
 * 	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 * 		IPv6 support
 * 	Kazunori MIYAZAWA @USAGI
 * 	YOSHIFUJI Hideaki
 * 		Split up af-specअगरic portion
 *	Derek Atkins <derek@ihtfp.com>		Add the post_input processor
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/cpu.h>
#समावेश <linux/audit.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
#समावेश <net/mip6.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFRM_STATISTICS
#समावेश <net/snmp.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFRM_ESPINTCP
#समावेश <net/espपूर्णांकcp.h>
#पूर्ण_अगर

#समावेश "xfrm_hash.h"

#घोषणा XFRM_QUEUE_TMO_MIN ((अचिन्हित)(HZ/10))
#घोषणा XFRM_QUEUE_TMO_MAX ((अचिन्हित)(60*HZ))
#घोषणा XFRM_MAX_QUEUE_LEN	100

काष्ठा xfrm_flo अणु
	काष्ठा dst_entry *dst_orig;
	u8 flags;
पूर्ण;

/* prefixes smaller than this are stored in lists, not trees. */
#घोषणा INEXACT_PREFIXLEN_IPV4	16
#घोषणा INEXACT_PREFIXLEN_IPV6	48

काष्ठा xfrm_pol_inexact_node अणु
	काष्ठा rb_node node;
	जोड़ अणु
		xfrm_address_t addr;
		काष्ठा rcu_head rcu;
	पूर्ण;
	u8 prefixlen;

	काष्ठा rb_root root;

	/* the policies matching this node, can be empty list */
	काष्ठा hlist_head hhead;
पूर्ण;

/* xfrm inexact policy search tree:
 * xfrm_pol_inexact_bin = hash(dir,type,family,अगर_id);
 *  |
 * +---- root_d: sorted by daddr:prefix
 * |                 |
 * |        xfrm_pol_inexact_node
 * |                 |
 * |                 +- root: sorted by saddr/prefix
 * |                 |              |
 * |                 |         xfrm_pol_inexact_node
 * |                 |              |
 * |                 |              + root: unused
 * |                 |              |
 * |                 |              + hhead: saddr:daddr policies
 * |                 |
 * |                 +- coarse policies and all any:daddr policies
 * |
 * +---- root_s: sorted by saddr:prefix
 * |                 |
 * |        xfrm_pol_inexact_node
 * |                 |
 * |                 + root: unused
 * |                 |
 * |                 + hhead: saddr:any policies
 * |
 * +---- coarse policies and all any:any policies
 *
 * Lookups वापस four candidate lists:
 * 1. any:any list from top-level xfrm_pol_inexact_bin
 * 2. any:daddr list from daddr tree
 * 3. saddr:daddr list from 2nd level daddr tree
 * 4. saddr:any list from saddr tree
 *
 * This result set then needs to be searched क्रम the policy with
 * the lowest priority.  If two results have same prio, youngest one wins.
 */

काष्ठा xfrm_pol_inexact_key अणु
	possible_net_t net;
	u32 अगर_id;
	u16 family;
	u8 dir, type;
पूर्ण;

काष्ठा xfrm_pol_inexact_bin अणु
	काष्ठा xfrm_pol_inexact_key k;
	काष्ठा rhash_head head;
	/* list containing '*:*' policies */
	काष्ठा hlist_head hhead;

	seqcount_spinlock_t count;
	/* tree sorted by daddr/prefix */
	काष्ठा rb_root root_d;

	/* tree sorted by saddr/prefix */
	काष्ठा rb_root root_s;

	/* slow path below */
	काष्ठा list_head inexact_bins;
	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत xfrm_pol_inexact_candidate_type अणु
	XFRM_POL_CAND_BOTH,
	XFRM_POL_CAND_SADDR,
	XFRM_POL_CAND_DADDR,
	XFRM_POL_CAND_ANY,

	XFRM_POL_CAND_MAX,
पूर्ण;

काष्ठा xfrm_pol_inexact_candidates अणु
	काष्ठा hlist_head *res[XFRM_POL_CAND_MAX];
पूर्ण;

अटल DEFINE_SPINLOCK(xfrm_अगर_cb_lock);
अटल काष्ठा xfrm_अगर_cb स्थिर __rcu *xfrm_अगर_cb __पढ़ो_mostly;

अटल DEFINE_SPINLOCK(xfrm_policy_afinfo_lock);
अटल काष्ठा xfrm_policy_afinfo स्थिर __rcu *xfrm_policy_afinfo[AF_INET6 + 1]
						__पढ़ो_mostly;

अटल काष्ठा kmem_cache *xfrm_dst_cache __ro_after_init;
अटल __पढ़ो_mostly seqcount_mutex_t xfrm_policy_hash_generation;

अटल काष्ठा rhashtable xfrm_policy_inexact_table;
अटल स्थिर काष्ठा rhashtable_params xfrm_pol_inexact_params;

अटल व्योम xfrm_init_pmtu(काष्ठा xfrm_dst **bundle, पूर्णांक nr);
अटल पूर्णांक stale_bundle(काष्ठा dst_entry *dst);
अटल पूर्णांक xfrm_bundle_ok(काष्ठा xfrm_dst *xdst);
अटल व्योम xfrm_policy_queue_process(काष्ठा समयr_list *t);

अटल व्योम __xfrm_policy_link(काष्ठा xfrm_policy *pol, पूर्णांक dir);
अटल काष्ठा xfrm_policy *__xfrm_policy_unlink(काष्ठा xfrm_policy *pol,
						पूर्णांक dir);

अटल काष्ठा xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup(काष्ठा net *net, u8 type, u16 family, u8 dir,
			   u32 अगर_id);

अटल काष्ठा xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup_rcu(काष्ठा net *net,
			       u8 type, u16 family, u8 dir, u32 अगर_id);
अटल काष्ठा xfrm_policy *
xfrm_policy_insert_list(काष्ठा hlist_head *chain, काष्ठा xfrm_policy *policy,
			bool excl);
अटल व्योम xfrm_policy_insert_inexact_list(काष्ठा hlist_head *chain,
					    काष्ठा xfrm_policy *policy);

अटल bool
xfrm_policy_find_inexact_candidates(काष्ठा xfrm_pol_inexact_candidates *cand,
				    काष्ठा xfrm_pol_inexact_bin *b,
				    स्थिर xfrm_address_t *saddr,
				    स्थिर xfrm_address_t *daddr);

अटल अंतरभूत bool xfrm_pol_hold_rcu(काष्ठा xfrm_policy *policy)
अणु
	वापस refcount_inc_not_zero(&policy->refcnt);
पूर्ण

अटल अंतरभूत bool
__xfrm4_selector_match(स्थिर काष्ठा xfrm_selector *sel, स्थिर काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा flowi4 *fl4 = &fl->u.ip4;

	वापस  addr4_match(fl4->daddr, sel->daddr.a4, sel->prefixlen_d) &&
		addr4_match(fl4->saddr, sel->saddr.a4, sel->prefixlen_s) &&
		!((xfrm_flowi_dport(fl, &fl4->uli) ^ sel->dport) & sel->dport_mask) &&
		!((xfrm_flowi_sport(fl, &fl4->uli) ^ sel->sport) & sel->sport_mask) &&
		(fl4->flowi4_proto == sel->proto || !sel->proto) &&
		(fl4->flowi4_oअगर == sel->अगरindex || !sel->अगरindex);
पूर्ण

अटल अंतरभूत bool
__xfrm6_selector_match(स्थिर काष्ठा xfrm_selector *sel, स्थिर काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा flowi6 *fl6 = &fl->u.ip6;

	वापस  addr_match(&fl6->daddr, &sel->daddr, sel->prefixlen_d) &&
		addr_match(&fl6->saddr, &sel->saddr, sel->prefixlen_s) &&
		!((xfrm_flowi_dport(fl, &fl6->uli) ^ sel->dport) & sel->dport_mask) &&
		!((xfrm_flowi_sport(fl, &fl6->uli) ^ sel->sport) & sel->sport_mask) &&
		(fl6->flowi6_proto == sel->proto || !sel->proto) &&
		(fl6->flowi6_oअगर == sel->अगरindex || !sel->अगरindex);
पूर्ण

bool xfrm_selector_match(स्थिर काष्ठा xfrm_selector *sel, स्थिर काष्ठा flowi *fl,
			 अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस __xfrm4_selector_match(sel, fl);
	हाल AF_INET6:
		वापस __xfrm6_selector_match(sel, fl);
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा xfrm_policy_afinfo *xfrm_policy_get_afinfo(अचिन्हित लघु family)
अणु
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo;

	अगर (unlikely(family >= ARRAY_SIZE(xfrm_policy_afinfo)))
		वापस शून्य;
	rcu_पढ़ो_lock();
	afinfo = rcu_dereference(xfrm_policy_afinfo[family]);
	अगर (unlikely(!afinfo))
		rcu_पढ़ो_unlock();
	वापस afinfo;
पूर्ण

/* Called with rcu_पढ़ो_lock(). */
अटल स्थिर काष्ठा xfrm_अगर_cb *xfrm_अगर_get_cb(व्योम)
अणु
	वापस rcu_dereference(xfrm_अगर_cb);
पूर्ण

काष्ठा dst_entry *__xfrm_dst_lookup(काष्ठा net *net, पूर्णांक tos, पूर्णांक oअगर,
				    स्थिर xfrm_address_t *saddr,
				    स्थिर xfrm_address_t *daddr,
				    पूर्णांक family, u32 mark)
अणु
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo;
	काष्ठा dst_entry *dst;

	afinfo = xfrm_policy_get_afinfo(family);
	अगर (unlikely(afinfo == शून्य))
		वापस ERR_PTR(-EAFNOSUPPORT);

	dst = afinfo->dst_lookup(net, tos, oअगर, saddr, daddr, mark);

	rcu_पढ़ो_unlock();

	वापस dst;
पूर्ण
EXPORT_SYMBOL(__xfrm_dst_lookup);

अटल अंतरभूत काष्ठा dst_entry *xfrm_dst_lookup(काष्ठा xfrm_state *x,
						पूर्णांक tos, पूर्णांक oअगर,
						xfrm_address_t *prev_saddr,
						xfrm_address_t *prev_daddr,
						पूर्णांक family, u32 mark)
अणु
	काष्ठा net *net = xs_net(x);
	xfrm_address_t *saddr = &x->props.saddr;
	xfrm_address_t *daddr = &x->id.daddr;
	काष्ठा dst_entry *dst;

	अगर (x->type->flags & XFRM_TYPE_LOCAL_COADDR) अणु
		saddr = x->coaddr;
		daddr = prev_daddr;
	पूर्ण
	अगर (x->type->flags & XFRM_TYPE_REMOTE_COADDR) अणु
		saddr = prev_saddr;
		daddr = x->coaddr;
	पूर्ण

	dst = __xfrm_dst_lookup(net, tos, oअगर, saddr, daddr, family, mark);

	अगर (!IS_ERR(dst)) अणु
		अगर (prev_saddr != saddr)
			स_नकल(prev_saddr, saddr,  माप(*prev_saddr));
		अगर (prev_daddr != daddr)
			स_नकल(prev_daddr, daddr,  माप(*prev_daddr));
	पूर्ण

	वापस dst;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ make_jअगरfies(दीर्घ secs)
अणु
	अगर (secs >= (MAX_SCHEDULE_TIMEOUT-1)/HZ)
		वापस MAX_SCHEDULE_TIMEOUT-1;
	अन्यथा
		वापस secs*HZ;
पूर्ण

अटल व्योम xfrm_policy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा xfrm_policy *xp = from_समयr(xp, t, समयr);
	समय64_t now = kसमय_get_real_seconds();
	समय64_t next = TIME64_MAX;
	पूर्णांक warn = 0;
	पूर्णांक dir;

	पढ़ो_lock(&xp->lock);

	अगर (unlikely(xp->walk.dead))
		जाओ out;

	dir = xfrm_policy_id2dir(xp->index);

	अगर (xp->lft.hard_add_expires_seconds) अणु
		समय64_t पंचांगo = xp->lft.hard_add_expires_seconds +
			xp->curlft.add_समय - now;
		अगर (पंचांगo <= 0)
			जाओ expired;
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण
	अगर (xp->lft.hard_use_expires_seconds) अणु
		समय64_t पंचांगo = xp->lft.hard_use_expires_seconds +
			(xp->curlft.use_समय ? : xp->curlft.add_समय) - now;
		अगर (पंचांगo <= 0)
			जाओ expired;
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण
	अगर (xp->lft.soft_add_expires_seconds) अणु
		समय64_t पंचांगo = xp->lft.soft_add_expires_seconds +
			xp->curlft.add_समय - now;
		अगर (पंचांगo <= 0) अणु
			warn = 1;
			पंचांगo = XFRM_KM_TIMEOUT;
		पूर्ण
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण
	अगर (xp->lft.soft_use_expires_seconds) अणु
		समय64_t पंचांगo = xp->lft.soft_use_expires_seconds +
			(xp->curlft.use_समय ? : xp->curlft.add_समय) - now;
		अगर (पंचांगo <= 0) अणु
			warn = 1;
			पंचांगo = XFRM_KM_TIMEOUT;
		पूर्ण
		अगर (पंचांगo < next)
			next = पंचांगo;
	पूर्ण

	अगर (warn)
		km_policy_expired(xp, dir, 0, 0);
	अगर (next != TIME64_MAX &&
	    !mod_समयr(&xp->समयr, jअगरfies + make_jअगरfies(next)))
		xfrm_pol_hold(xp);

out:
	पढ़ो_unlock(&xp->lock);
	xfrm_pol_put(xp);
	वापस;

expired:
	पढ़ो_unlock(&xp->lock);
	अगर (!xfrm_policy_delete(xp, dir))
		km_policy_expired(xp, dir, 1, 0);
	xfrm_pol_put(xp);
पूर्ण

/* Allocate xfrm_policy. Not used here, it is supposed to be used by pfkeyv2
 * SPD calls.
 */

काष्ठा xfrm_policy *xfrm_policy_alloc(काष्ठा net *net, gfp_t gfp)
अणु
	काष्ठा xfrm_policy *policy;

	policy = kzalloc(माप(काष्ठा xfrm_policy), gfp);

	अगर (policy) अणु
		ग_लिखो_pnet(&policy->xp_net, net);
		INIT_LIST_HEAD(&policy->walk.all);
		INIT_HLIST_NODE(&policy->bydst_inexact_list);
		INIT_HLIST_NODE(&policy->bydst);
		INIT_HLIST_NODE(&policy->byidx);
		rwlock_init(&policy->lock);
		refcount_set(&policy->refcnt, 1);
		skb_queue_head_init(&policy->polq.hold_queue);
		समयr_setup(&policy->समयr, xfrm_policy_समयr, 0);
		समयr_setup(&policy->polq.hold_समयr,
			    xfrm_policy_queue_process, 0);
	पूर्ण
	वापस policy;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_alloc);

अटल व्योम xfrm_policy_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा xfrm_policy *policy = container_of(head, काष्ठा xfrm_policy, rcu);

	security_xfrm_policy_मुक्त(policy->security);
	kमुक्त(policy);
पूर्ण

/* Destroy xfrm_policy: descendant resources must be released to this moment. */

व्योम xfrm_policy_destroy(काष्ठा xfrm_policy *policy)
अणु
	BUG_ON(!policy->walk.dead);

	अगर (del_समयr(&policy->समयr) || del_समयr(&policy->polq.hold_समयr))
		BUG();

	call_rcu(&policy->rcu, xfrm_policy_destroy_rcu);
पूर्ण
EXPORT_SYMBOL(xfrm_policy_destroy);

/* Rule must be locked. Release descendant resources, announce
 * entry dead. The rule must be unlinked from lists to the moment.
 */

अटल व्योम xfrm_policy_समाप्त(काष्ठा xfrm_policy *policy)
अणु
	ग_लिखो_lock_bh(&policy->lock);
	policy->walk.dead = 1;
	ग_लिखो_unlock_bh(&policy->lock);

	atomic_inc(&policy->genid);

	अगर (del_समयr(&policy->polq.hold_समयr))
		xfrm_pol_put(policy);
	skb_queue_purge(&policy->polq.hold_queue);

	अगर (del_समयr(&policy->समयr))
		xfrm_pol_put(policy);

	xfrm_pol_put(policy);
पूर्ण

अटल अचिन्हित पूर्णांक xfrm_policy_hashmax __पढ़ो_mostly = 1 * 1024 * 1024;

अटल अंतरभूत अचिन्हित पूर्णांक idx_hash(काष्ठा net *net, u32 index)
अणु
	वापस __idx_hash(index, net->xfrm.policy_idx_hmask);
पूर्ण

/* calculate policy hash thresholds */
अटल व्योम __get_hash_thresh(काष्ठा net *net,
			      अचिन्हित लघु family, पूर्णांक dir,
			      u8 *dbits, u8 *sbits)
अणु
	चयन (family) अणु
	हाल AF_INET:
		*dbits = net->xfrm.policy_bydst[dir].dbits4;
		*sbits = net->xfrm.policy_bydst[dir].sbits4;
		अवरोध;

	हाल AF_INET6:
		*dbits = net->xfrm.policy_bydst[dir].dbits6;
		*sbits = net->xfrm.policy_bydst[dir].sbits6;
		अवरोध;

	शेष:
		*dbits = 0;
		*sbits = 0;
	पूर्ण
पूर्ण

अटल काष्ठा hlist_head *policy_hash_bysel(काष्ठा net *net,
					    स्थिर काष्ठा xfrm_selector *sel,
					    अचिन्हित लघु family, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_bydst[dir].hmask;
	अचिन्हित पूर्णांक hash;
	u8 dbits;
	u8 sbits;

	__get_hash_thresh(net, family, dir, &dbits, &sbits);
	hash = __sel_hash(sel, family, hmask, dbits, sbits);

	अगर (hash == hmask + 1)
		वापस शून्य;

	वापस rcu_dereference_check(net->xfrm.policy_bydst[dir].table,
		     lockdep_is_held(&net->xfrm.xfrm_policy_lock)) + hash;
पूर्ण

अटल काष्ठा hlist_head *policy_hash_direct(काष्ठा net *net,
					     स्थिर xfrm_address_t *daddr,
					     स्थिर xfrm_address_t *saddr,
					     अचिन्हित लघु family, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_bydst[dir].hmask;
	अचिन्हित पूर्णांक hash;
	u8 dbits;
	u8 sbits;

	__get_hash_thresh(net, family, dir, &dbits, &sbits);
	hash = __addr_hash(daddr, saddr, family, hmask, dbits, sbits);

	वापस rcu_dereference_check(net->xfrm.policy_bydst[dir].table,
		     lockdep_is_held(&net->xfrm.xfrm_policy_lock)) + hash;
पूर्ण

अटल व्योम xfrm_dst_hash_transfer(काष्ठा net *net,
				   काष्ठा hlist_head *list,
				   काष्ठा hlist_head *ndsttable,
				   अचिन्हित पूर्णांक nhashmask,
				   पूर्णांक dir)
अणु
	काष्ठा hlist_node *पंचांगp, *entry0 = शून्य;
	काष्ठा xfrm_policy *pol;
	अचिन्हित पूर्णांक h0 = 0;
	u8 dbits;
	u8 sbits;

reकरो:
	hlist_क्रम_each_entry_safe(pol, पंचांगp, list, bydst) अणु
		अचिन्हित पूर्णांक h;

		__get_hash_thresh(net, pol->family, dir, &dbits, &sbits);
		h = __addr_hash(&pol->selector.daddr, &pol->selector.saddr,
				pol->family, nhashmask, dbits, sbits);
		अगर (!entry0) अणु
			hlist_del_rcu(&pol->bydst);
			hlist_add_head_rcu(&pol->bydst, ndsttable + h);
			h0 = h;
		पूर्ण अन्यथा अणु
			अगर (h != h0)
				जारी;
			hlist_del_rcu(&pol->bydst);
			hlist_add_behind_rcu(&pol->bydst, entry0);
		पूर्ण
		entry0 = &pol->bydst;
	पूर्ण
	अगर (!hlist_empty(list)) अणु
		entry0 = शून्य;
		जाओ reकरो;
	पूर्ण
पूर्ण

अटल व्योम xfrm_idx_hash_transfer(काष्ठा hlist_head *list,
				   काष्ठा hlist_head *nidxtable,
				   अचिन्हित पूर्णांक nhashmask)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा xfrm_policy *pol;

	hlist_क्रम_each_entry_safe(pol, पंचांगp, list, byidx) अणु
		अचिन्हित पूर्णांक h;

		h = __idx_hash(pol->index, nhashmask);
		hlist_add_head(&pol->byidx, nidxtable+h);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ xfrm_new_hash_mask(अचिन्हित पूर्णांक old_hmask)
अणु
	वापस ((old_hmask + 1) << 1) - 1;
पूर्ण

अटल व्योम xfrm_bydst_resize(काष्ठा net *net, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_bydst[dir].hmask;
	अचिन्हित पूर्णांक nhashmask = xfrm_new_hash_mask(hmask);
	अचिन्हित पूर्णांक nsize = (nhashmask + 1) * माप(काष्ठा hlist_head);
	काष्ठा hlist_head *ndst = xfrm_hash_alloc(nsize);
	काष्ठा hlist_head *odst;
	पूर्णांक i;

	अगर (!ndst)
		वापस;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	ग_लिखो_seqcount_begin(&xfrm_policy_hash_generation);

	odst = rcu_dereference_रक्षित(net->xfrm.policy_bydst[dir].table,
				lockdep_is_held(&net->xfrm.xfrm_policy_lock));

	क्रम (i = hmask; i >= 0; i--)
		xfrm_dst_hash_transfer(net, odst + i, ndst, nhashmask, dir);

	rcu_assign_poपूर्णांकer(net->xfrm.policy_bydst[dir].table, ndst);
	net->xfrm.policy_bydst[dir].hmask = nhashmask;

	ग_लिखो_seqcount_end(&xfrm_policy_hash_generation);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	synchronize_rcu();

	xfrm_hash_मुक्त(odst, (hmask + 1) * माप(काष्ठा hlist_head));
पूर्ण

अटल व्योम xfrm_byidx_resize(काष्ठा net *net, पूर्णांक total)
अणु
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_idx_hmask;
	अचिन्हित पूर्णांक nhashmask = xfrm_new_hash_mask(hmask);
	अचिन्हित पूर्णांक nsize = (nhashmask + 1) * माप(काष्ठा hlist_head);
	काष्ठा hlist_head *oidx = net->xfrm.policy_byidx;
	काष्ठा hlist_head *nidx = xfrm_hash_alloc(nsize);
	पूर्णांक i;

	अगर (!nidx)
		वापस;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);

	क्रम (i = hmask; i >= 0; i--)
		xfrm_idx_hash_transfer(oidx + i, nidx, nhashmask);

	net->xfrm.policy_byidx = nidx;
	net->xfrm.policy_idx_hmask = nhashmask;

	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	xfrm_hash_मुक्त(oidx, (hmask + 1) * माप(काष्ठा hlist_head));
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_bydst_should_resize(काष्ठा net *net, पूर्णांक dir, पूर्णांक *total)
अणु
	अचिन्हित पूर्णांक cnt = net->xfrm.policy_count[dir];
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_bydst[dir].hmask;

	अगर (total)
		*total += cnt;

	अगर ((hmask + 1) < xfrm_policy_hashmax &&
	    cnt > hmask)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_byidx_should_resize(काष्ठा net *net, पूर्णांक total)
अणु
	अचिन्हित पूर्णांक hmask = net->xfrm.policy_idx_hmask;

	अगर ((hmask + 1) < xfrm_policy_hashmax &&
	    total > hmask)
		वापस 1;

	वापस 0;
पूर्ण

व्योम xfrm_spd_getinfo(काष्ठा net *net, काष्ठा xfrmk_spdinfo *si)
अणु
	si->incnt = net->xfrm.policy_count[XFRM_POLICY_IN];
	si->outcnt = net->xfrm.policy_count[XFRM_POLICY_OUT];
	si->fwdcnt = net->xfrm.policy_count[XFRM_POLICY_FWD];
	si->inscnt = net->xfrm.policy_count[XFRM_POLICY_IN+XFRM_POLICY_MAX];
	si->outscnt = net->xfrm.policy_count[XFRM_POLICY_OUT+XFRM_POLICY_MAX];
	si->fwdscnt = net->xfrm.policy_count[XFRM_POLICY_FWD+XFRM_POLICY_MAX];
	si->spdhcnt = net->xfrm.policy_idx_hmask;
	si->spdhmcnt = xfrm_policy_hashmax;
पूर्ण
EXPORT_SYMBOL(xfrm_spd_getinfo);

अटल DEFINE_MUTEX(hash_resize_mutex);
अटल व्योम xfrm_hash_resize(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net *net = container_of(work, काष्ठा net, xfrm.policy_hash_work);
	पूर्णांक dir, total;

	mutex_lock(&hash_resize_mutex);

	total = 0;
	क्रम (dir = 0; dir < XFRM_POLICY_MAX; dir++) अणु
		अगर (xfrm_bydst_should_resize(net, dir, &total))
			xfrm_bydst_resize(net, dir);
	पूर्ण
	अगर (xfrm_byidx_should_resize(net, total))
		xfrm_byidx_resize(net, total);

	mutex_unlock(&hash_resize_mutex);
पूर्ण

/* Make sure *pol can be inserted पूर्णांकo fastbin.
 * Useful to check that later insert requests will be successful
 * (provided xfrm_policy_lock is held throughout).
 */
अटल काष्ठा xfrm_pol_inexact_bin *
xfrm_policy_inexact_alloc_bin(स्थिर काष्ठा xfrm_policy *pol, u8 dir)
अणु
	काष्ठा xfrm_pol_inexact_bin *bin, *prev;
	काष्ठा xfrm_pol_inexact_key k = अणु
		.family = pol->family,
		.type = pol->type,
		.dir = dir,
		.अगर_id = pol->अगर_id,
	पूर्ण;
	काष्ठा net *net = xp_net(pol);

	lockdep_निश्चित_held(&net->xfrm.xfrm_policy_lock);

	ग_लिखो_pnet(&k.net, net);
	bin = rhashtable_lookup_fast(&xfrm_policy_inexact_table, &k,
				     xfrm_pol_inexact_params);
	अगर (bin)
		वापस bin;

	bin = kzalloc(माप(*bin), GFP_ATOMIC);
	अगर (!bin)
		वापस शून्य;

	bin->k = k;
	INIT_HLIST_HEAD(&bin->hhead);
	bin->root_d = RB_ROOT;
	bin->root_s = RB_ROOT;
	seqcount_spinlock_init(&bin->count, &net->xfrm.xfrm_policy_lock);

	prev = rhashtable_lookup_get_insert_key(&xfrm_policy_inexact_table,
						&bin->k, &bin->head,
						xfrm_pol_inexact_params);
	अगर (!prev) अणु
		list_add(&bin->inexact_bins, &net->xfrm.inexact_bins);
		वापस bin;
	पूर्ण

	kमुक्त(bin);

	वापस IS_ERR(prev) ? शून्य : prev;
पूर्ण

अटल bool xfrm_pol_inexact_addr_use_any_list(स्थिर xfrm_address_t *addr,
					       पूर्णांक family, u8 prefixlen)
अणु
	अगर (xfrm_addr_any(addr, family))
		वापस true;

	अगर (family == AF_INET6 && prefixlen < INEXACT_PREFIXLEN_IPV6)
		वापस true;

	अगर (family == AF_INET && prefixlen < INEXACT_PREFIXLEN_IPV4)
		वापस true;

	वापस false;
पूर्ण

अटल bool
xfrm_policy_inexact_insert_use_any_list(स्थिर काष्ठा xfrm_policy *policy)
अणु
	स्थिर xfrm_address_t *addr;
	bool saddr_any, daddr_any;
	u8 prefixlen;

	addr = &policy->selector.saddr;
	prefixlen = policy->selector.prefixlen_s;

	saddr_any = xfrm_pol_inexact_addr_use_any_list(addr,
						       policy->family,
						       prefixlen);
	addr = &policy->selector.daddr;
	prefixlen = policy->selector.prefixlen_d;
	daddr_any = xfrm_pol_inexact_addr_use_any_list(addr,
						       policy->family,
						       prefixlen);
	वापस saddr_any && daddr_any;
पूर्ण

अटल व्योम xfrm_pol_inexact_node_init(काष्ठा xfrm_pol_inexact_node *node,
				       स्थिर xfrm_address_t *addr, u8 prefixlen)
अणु
	node->addr = *addr;
	node->prefixlen = prefixlen;
पूर्ण

अटल काष्ठा xfrm_pol_inexact_node *
xfrm_pol_inexact_node_alloc(स्थिर xfrm_address_t *addr, u8 prefixlen)
अणु
	काष्ठा xfrm_pol_inexact_node *node;

	node = kzalloc(माप(*node), GFP_ATOMIC);
	अगर (node)
		xfrm_pol_inexact_node_init(node, addr, prefixlen);

	वापस node;
पूर्ण

अटल पूर्णांक xfrm_policy_addr_delta(स्थिर xfrm_address_t *a,
				  स्थिर xfrm_address_t *b,
				  u8 prefixlen, u16 family)
अणु
	u32 ma, mb, mask;
	अचिन्हित पूर्णांक pdw, pbi;
	पूर्णांक delta = 0;

	चयन (family) अणु
	हाल AF_INET:
		अगर (prefixlen == 0)
			वापस 0;
		mask = ~0U << (32 - prefixlen);
		ma = ntohl(a->a4) & mask;
		mb = ntohl(b->a4) & mask;
		अगर (ma < mb)
			delta = -1;
		अन्यथा अगर (ma > mb)
			delta = 1;
		अवरोध;
	हाल AF_INET6:
		pdw = prefixlen >> 5;
		pbi = prefixlen & 0x1f;

		अगर (pdw) अणु
			delta = स_भेद(a->a6, b->a6, pdw << 2);
			अगर (delta)
				वापस delta;
		पूर्ण
		अगर (pbi) अणु
			mask = ~0U << (32 - pbi);
			ma = ntohl(a->a6[pdw]) & mask;
			mb = ntohl(b->a6[pdw]) & mask;
			अगर (ma < mb)
				delta = -1;
			अन्यथा अगर (ma > mb)
				delta = 1;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस delta;
पूर्ण

अटल व्योम xfrm_policy_inexact_list_reinsert(काष्ठा net *net,
					      काष्ठा xfrm_pol_inexact_node *n,
					      u16 family)
अणु
	अचिन्हित पूर्णांक matched_s, matched_d;
	काष्ठा xfrm_policy *policy, *p;

	matched_s = 0;
	matched_d = 0;

	list_क्रम_each_entry_reverse(policy, &net->xfrm.policy_all, walk.all) अणु
		काष्ठा hlist_node *newpos = शून्य;
		bool matches_s, matches_d;

		अगर (!policy->bydst_reinsert)
			जारी;

		WARN_ON_ONCE(policy->family != family);

		policy->bydst_reinsert = false;
		hlist_क्रम_each_entry(p, &n->hhead, bydst) अणु
			अगर (policy->priority > p->priority)
				newpos = &p->bydst;
			अन्यथा अगर (policy->priority == p->priority &&
				 policy->pos > p->pos)
				newpos = &p->bydst;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (newpos)
			hlist_add_behind_rcu(&policy->bydst, newpos);
		अन्यथा
			hlist_add_head_rcu(&policy->bydst, &n->hhead);

		/* paranoia checks follow.
		 * Check that the reinserted policy matches at least
		 * saddr or daddr क्रम current node prefix.
		 *
		 * Matching both is fine, matching saddr in one policy
		 * (but not daddr) and then matching only daddr in another
		 * is a bug.
		 */
		matches_s = xfrm_policy_addr_delta(&policy->selector.saddr,
						   &n->addr,
						   n->prefixlen,
						   family) == 0;
		matches_d = xfrm_policy_addr_delta(&policy->selector.daddr,
						   &n->addr,
						   n->prefixlen,
						   family) == 0;
		अगर (matches_s && matches_d)
			जारी;

		WARN_ON_ONCE(!matches_s && !matches_d);
		अगर (matches_s)
			matched_s++;
		अगर (matches_d)
			matched_d++;
		WARN_ON_ONCE(matched_s && matched_d);
	पूर्ण
पूर्ण

अटल व्योम xfrm_policy_inexact_node_reinsert(काष्ठा net *net,
					      काष्ठा xfrm_pol_inexact_node *n,
					      काष्ठा rb_root *new,
					      u16 family)
अणु
	काष्ठा xfrm_pol_inexact_node *node;
	काष्ठा rb_node **p, *parent;

	/* we should not have another subtree here */
	WARN_ON_ONCE(!RB_EMPTY_ROOT(&n->root));
restart:
	parent = शून्य;
	p = &new->rb_node;
	जबतक (*p) अणु
		u8 prefixlen;
		पूर्णांक delta;

		parent = *p;
		node = rb_entry(*p, काष्ठा xfrm_pol_inexact_node, node);

		prefixlen = min(node->prefixlen, n->prefixlen);

		delta = xfrm_policy_addr_delta(&n->addr, &node->addr,
					       prefixlen, family);
		अगर (delta < 0) अणु
			p = &parent->rb_left;
		पूर्ण अन्यथा अगर (delta > 0) अणु
			p = &parent->rb_right;
		पूर्ण अन्यथा अणु
			bool same_prefixlen = node->prefixlen == n->prefixlen;
			काष्ठा xfrm_policy *पंचांगp;

			hlist_क्रम_each_entry(पंचांगp, &n->hhead, bydst) अणु
				पंचांगp->bydst_reinsert = true;
				hlist_del_rcu(&पंचांगp->bydst);
			पूर्ण

			node->prefixlen = prefixlen;

			xfrm_policy_inexact_list_reinsert(net, node, family);

			अगर (same_prefixlen) अणु
				kमुक्त_rcu(n, rcu);
				वापस;
			पूर्ण

			rb_erase(*p, new);
			kमुक्त_rcu(n, rcu);
			n = node;
			जाओ restart;
		पूर्ण
	पूर्ण

	rb_link_node_rcu(&n->node, parent, p);
	rb_insert_color(&n->node, new);
पूर्ण

/* merge nodes v and n */
अटल व्योम xfrm_policy_inexact_node_merge(काष्ठा net *net,
					   काष्ठा xfrm_pol_inexact_node *v,
					   काष्ठा xfrm_pol_inexact_node *n,
					   u16 family)
अणु
	काष्ठा xfrm_pol_inexact_node *node;
	काष्ठा xfrm_policy *पंचांगp;
	काष्ठा rb_node *rnode;

	/* To-be-merged node v has a subtree.
	 *
	 * Dismantle it and insert its nodes to n->root.
	 */
	जबतक ((rnode = rb_first(&v->root)) != शून्य) अणु
		node = rb_entry(rnode, काष्ठा xfrm_pol_inexact_node, node);
		rb_erase(&node->node, &v->root);
		xfrm_policy_inexact_node_reinsert(net, node, &n->root,
						  family);
	पूर्ण

	hlist_क्रम_each_entry(पंचांगp, &v->hhead, bydst) अणु
		पंचांगp->bydst_reinsert = true;
		hlist_del_rcu(&पंचांगp->bydst);
	पूर्ण

	xfrm_policy_inexact_list_reinsert(net, n, family);
पूर्ण

अटल काष्ठा xfrm_pol_inexact_node *
xfrm_policy_inexact_insert_node(काष्ठा net *net,
				काष्ठा rb_root *root,
				xfrm_address_t *addr,
				u16 family, u8 prefixlen, u8 dir)
अणु
	काष्ठा xfrm_pol_inexact_node *cached = शून्य;
	काष्ठा rb_node **p, *parent = शून्य;
	काष्ठा xfrm_pol_inexact_node *node;

	p = &root->rb_node;
	जबतक (*p) अणु
		पूर्णांक delta;

		parent = *p;
		node = rb_entry(*p, काष्ठा xfrm_pol_inexact_node, node);

		delta = xfrm_policy_addr_delta(addr, &node->addr,
					       node->prefixlen,
					       family);
		अगर (delta == 0 && prefixlen >= node->prefixlen) अणु
			WARN_ON_ONCE(cached); /* ipsec policies got lost */
			वापस node;
		पूर्ण

		अगर (delta < 0)
			p = &parent->rb_left;
		अन्यथा
			p = &parent->rb_right;

		अगर (prefixlen < node->prefixlen) अणु
			delta = xfrm_policy_addr_delta(addr, &node->addr,
						       prefixlen,
						       family);
			अगर (delta)
				जारी;

			/* This node is a subnet of the new prefix. It needs
			 * to be हटाओd and re-inserted with the smaller
			 * prefix and all nodes that are now also covered
			 * by the reduced prefixlen.
			 */
			rb_erase(&node->node, root);

			अगर (!cached) अणु
				xfrm_pol_inexact_node_init(node, addr,
							   prefixlen);
				cached = node;
			पूर्ण अन्यथा अणु
				/* This node also falls within the new
				 * prefixlen. Merge the to-be-reinserted
				 * node and this one.
				 */
				xfrm_policy_inexact_node_merge(net, node,
							       cached, family);
				kमुक्त_rcu(node, rcu);
			पूर्ण

			/* restart */
			p = &root->rb_node;
			parent = शून्य;
		पूर्ण
	पूर्ण

	node = cached;
	अगर (!node) अणु
		node = xfrm_pol_inexact_node_alloc(addr, prefixlen);
		अगर (!node)
			वापस शून्य;
	पूर्ण

	rb_link_node_rcu(&node->node, parent, p);
	rb_insert_color(&node->node, root);

	वापस node;
पूर्ण

अटल व्योम xfrm_policy_inexact_gc_tree(काष्ठा rb_root *r, bool rm)
अणु
	काष्ठा xfrm_pol_inexact_node *node;
	काष्ठा rb_node *rn = rb_first(r);

	जबतक (rn) अणु
		node = rb_entry(rn, काष्ठा xfrm_pol_inexact_node, node);

		xfrm_policy_inexact_gc_tree(&node->root, rm);
		rn = rb_next(rn);

		अगर (!hlist_empty(&node->hhead) || !RB_EMPTY_ROOT(&node->root)) अणु
			WARN_ON_ONCE(rm);
			जारी;
		पूर्ण

		rb_erase(&node->node, r);
		kमुक्त_rcu(node, rcu);
	पूर्ण
पूर्ण

अटल व्योम __xfrm_policy_inexact_prune_bin(काष्ठा xfrm_pol_inexact_bin *b, bool net_निकास)
अणु
	ग_लिखो_seqcount_begin(&b->count);
	xfrm_policy_inexact_gc_tree(&b->root_d, net_निकास);
	xfrm_policy_inexact_gc_tree(&b->root_s, net_निकास);
	ग_लिखो_seqcount_end(&b->count);

	अगर (!RB_EMPTY_ROOT(&b->root_d) || !RB_EMPTY_ROOT(&b->root_s) ||
	    !hlist_empty(&b->hhead)) अणु
		WARN_ON_ONCE(net_निकास);
		वापस;
	पूर्ण

	अगर (rhashtable_हटाओ_fast(&xfrm_policy_inexact_table, &b->head,
				   xfrm_pol_inexact_params) == 0) अणु
		list_del(&b->inexact_bins);
		kमुक्त_rcu(b, rcu);
	पूर्ण
पूर्ण

अटल व्योम xfrm_policy_inexact_prune_bin(काष्ठा xfrm_pol_inexact_bin *b)
अणु
	काष्ठा net *net = पढ़ो_pnet(&b->k.net);

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	__xfrm_policy_inexact_prune_bin(b, false);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
पूर्ण

अटल व्योम __xfrm_policy_inexact_flush(काष्ठा net *net)
अणु
	काष्ठा xfrm_pol_inexact_bin *bin, *t;

	lockdep_निश्चित_held(&net->xfrm.xfrm_policy_lock);

	list_क्रम_each_entry_safe(bin, t, &net->xfrm.inexact_bins, inexact_bins)
		__xfrm_policy_inexact_prune_bin(bin, false);
पूर्ण

अटल काष्ठा hlist_head *
xfrm_policy_inexact_alloc_chain(काष्ठा xfrm_pol_inexact_bin *bin,
				काष्ठा xfrm_policy *policy, u8 dir)
अणु
	काष्ठा xfrm_pol_inexact_node *n;
	काष्ठा net *net;

	net = xp_net(policy);
	lockdep_निश्चित_held(&net->xfrm.xfrm_policy_lock);

	अगर (xfrm_policy_inexact_insert_use_any_list(policy))
		वापस &bin->hhead;

	अगर (xfrm_pol_inexact_addr_use_any_list(&policy->selector.daddr,
					       policy->family,
					       policy->selector.prefixlen_d)) अणु
		ग_लिखो_seqcount_begin(&bin->count);
		n = xfrm_policy_inexact_insert_node(net,
						    &bin->root_s,
						    &policy->selector.saddr,
						    policy->family,
						    policy->selector.prefixlen_s,
						    dir);
		ग_लिखो_seqcount_end(&bin->count);
		अगर (!n)
			वापस शून्य;

		वापस &n->hhead;
	पूर्ण

	/* daddr is fixed */
	ग_लिखो_seqcount_begin(&bin->count);
	n = xfrm_policy_inexact_insert_node(net,
					    &bin->root_d,
					    &policy->selector.daddr,
					    policy->family,
					    policy->selector.prefixlen_d, dir);
	ग_लिखो_seqcount_end(&bin->count);
	अगर (!n)
		वापस शून्य;

	/* saddr is wildcard */
	अगर (xfrm_pol_inexact_addr_use_any_list(&policy->selector.saddr,
					       policy->family,
					       policy->selector.prefixlen_s))
		वापस &n->hhead;

	ग_लिखो_seqcount_begin(&bin->count);
	n = xfrm_policy_inexact_insert_node(net,
					    &n->root,
					    &policy->selector.saddr,
					    policy->family,
					    policy->selector.prefixlen_s, dir);
	ग_लिखो_seqcount_end(&bin->count);
	अगर (!n)
		वापस शून्य;

	वापस &n->hhead;
पूर्ण

अटल काष्ठा xfrm_policy *
xfrm_policy_inexact_insert(काष्ठा xfrm_policy *policy, u8 dir, पूर्णांक excl)
अणु
	काष्ठा xfrm_pol_inexact_bin *bin;
	काष्ठा xfrm_policy *delpol;
	काष्ठा hlist_head *chain;
	काष्ठा net *net;

	bin = xfrm_policy_inexact_alloc_bin(policy, dir);
	अगर (!bin)
		वापस ERR_PTR(-ENOMEM);

	net = xp_net(policy);
	lockdep_निश्चित_held(&net->xfrm.xfrm_policy_lock);

	chain = xfrm_policy_inexact_alloc_chain(bin, policy, dir);
	अगर (!chain) अणु
		__xfrm_policy_inexact_prune_bin(bin, false);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	delpol = xfrm_policy_insert_list(chain, policy, excl);
	अगर (delpol && excl) अणु
		__xfrm_policy_inexact_prune_bin(bin, false);
		वापस ERR_PTR(-EEXIST);
	पूर्ण

	chain = &net->xfrm.policy_inexact[dir];
	xfrm_policy_insert_inexact_list(chain, policy);

	अगर (delpol)
		__xfrm_policy_inexact_prune_bin(bin, false);

	वापस delpol;
पूर्ण

अटल व्योम xfrm_hash_rebuild(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net *net = container_of(work, काष्ठा net,
				       xfrm.policy_hthresh.work);
	अचिन्हित पूर्णांक hmask;
	काष्ठा xfrm_policy *pol;
	काष्ठा xfrm_policy *policy;
	काष्ठा hlist_head *chain;
	काष्ठा hlist_head *odst;
	काष्ठा hlist_node *newpos;
	पूर्णांक i;
	पूर्णांक dir;
	अचिन्हित seq;
	u8 lbits4, rbits4, lbits6, rbits6;

	mutex_lock(&hash_resize_mutex);

	/* पढ़ो selector prefixlen thresholds */
	करो अणु
		seq = पढ़ो_seqbegin(&net->xfrm.policy_hthresh.lock);

		lbits4 = net->xfrm.policy_hthresh.lbits4;
		rbits4 = net->xfrm.policy_hthresh.rbits4;
		lbits6 = net->xfrm.policy_hthresh.lbits6;
		rbits6 = net->xfrm.policy_hthresh.rbits6;
	पूर्ण जबतक (पढ़ो_seqretry(&net->xfrm.policy_hthresh.lock, seq));

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	ग_लिखो_seqcount_begin(&xfrm_policy_hash_generation);

	/* make sure that we can insert the indirect policies again beक्रमe
	 * we start with deकाष्ठाive action.
	 */
	list_क्रम_each_entry(policy, &net->xfrm.policy_all, walk.all) अणु
		काष्ठा xfrm_pol_inexact_bin *bin;
		u8 dbits, sbits;

		dir = xfrm_policy_id2dir(policy->index);
		अगर (policy->walk.dead || dir >= XFRM_POLICY_MAX)
			जारी;

		अगर ((dir & XFRM_POLICY_MASK) == XFRM_POLICY_OUT) अणु
			अगर (policy->family == AF_INET) अणु
				dbits = rbits4;
				sbits = lbits4;
			पूर्ण अन्यथा अणु
				dbits = rbits6;
				sbits = lbits6;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (policy->family == AF_INET) अणु
				dbits = lbits4;
				sbits = rbits4;
			पूर्ण अन्यथा अणु
				dbits = lbits6;
				sbits = rbits6;
			पूर्ण
		पूर्ण

		अगर (policy->selector.prefixlen_d < dbits ||
		    policy->selector.prefixlen_s < sbits)
			जारी;

		bin = xfrm_policy_inexact_alloc_bin(policy, dir);
		अगर (!bin)
			जाओ out_unlock;

		अगर (!xfrm_policy_inexact_alloc_chain(bin, policy, dir))
			जाओ out_unlock;
	पूर्ण

	/* reset the bydst and inexact table in all directions */
	क्रम (dir = 0; dir < XFRM_POLICY_MAX; dir++) अणु
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(policy, n,
					  &net->xfrm.policy_inexact[dir],
					  bydst_inexact_list) अणु
			hlist_del_rcu(&policy->bydst);
			hlist_del_init(&policy->bydst_inexact_list);
		पूर्ण

		hmask = net->xfrm.policy_bydst[dir].hmask;
		odst = net->xfrm.policy_bydst[dir].table;
		क्रम (i = hmask; i >= 0; i--) अणु
			hlist_क्रम_each_entry_safe(policy, n, odst + i, bydst)
				hlist_del_rcu(&policy->bydst);
		पूर्ण
		अगर ((dir & XFRM_POLICY_MASK) == XFRM_POLICY_OUT) अणु
			/* dir out => dst = remote, src = local */
			net->xfrm.policy_bydst[dir].dbits4 = rbits4;
			net->xfrm.policy_bydst[dir].sbits4 = lbits4;
			net->xfrm.policy_bydst[dir].dbits6 = rbits6;
			net->xfrm.policy_bydst[dir].sbits6 = lbits6;
		पूर्ण अन्यथा अणु
			/* dir in/fwd => dst = local, src = remote */
			net->xfrm.policy_bydst[dir].dbits4 = lbits4;
			net->xfrm.policy_bydst[dir].sbits4 = rbits4;
			net->xfrm.policy_bydst[dir].dbits6 = lbits6;
			net->xfrm.policy_bydst[dir].sbits6 = rbits6;
		पूर्ण
	पूर्ण

	/* re-insert all policies by order of creation */
	list_क्रम_each_entry_reverse(policy, &net->xfrm.policy_all, walk.all) अणु
		अगर (policy->walk.dead)
			जारी;
		dir = xfrm_policy_id2dir(policy->index);
		अगर (dir >= XFRM_POLICY_MAX) अणु
			/* skip socket policies */
			जारी;
		पूर्ण
		newpos = शून्य;
		chain = policy_hash_bysel(net, &policy->selector,
					  policy->family, dir);

		अगर (!chain) अणु
			व्योम *p = xfrm_policy_inexact_insert(policy, dir, 0);

			WARN_ONCE(IS_ERR(p), "reinsert: %ld\n", PTR_ERR(p));
			जारी;
		पूर्ण

		hlist_क्रम_each_entry(pol, chain, bydst) अणु
			अगर (policy->priority >= pol->priority)
				newpos = &pol->bydst;
			अन्यथा
				अवरोध;
		पूर्ण
		अगर (newpos)
			hlist_add_behind_rcu(&policy->bydst, newpos);
		अन्यथा
			hlist_add_head_rcu(&policy->bydst, chain);
	पूर्ण

out_unlock:
	__xfrm_policy_inexact_flush(net);
	ग_लिखो_seqcount_end(&xfrm_policy_hash_generation);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	mutex_unlock(&hash_resize_mutex);
पूर्ण

व्योम xfrm_policy_hash_rebuild(काष्ठा net *net)
अणु
	schedule_work(&net->xfrm.policy_hthresh.work);
पूर्ण
EXPORT_SYMBOL(xfrm_policy_hash_rebuild);

/* Generate new index... KAME seems to generate them ordered by cost
 * of an असलolute inpredictability of ordering of rules. This will not pass. */
अटल u32 xfrm_gen_index(काष्ठा net *net, पूर्णांक dir, u32 index)
अणु
	अटल u32 idx_generator;

	क्रम (;;) अणु
		काष्ठा hlist_head *list;
		काष्ठा xfrm_policy *p;
		u32 idx;
		पूर्णांक found;

		अगर (!index) अणु
			idx = (idx_generator | dir);
			idx_generator += 8;
		पूर्ण अन्यथा अणु
			idx = index;
			index = 0;
		पूर्ण

		अगर (idx == 0)
			idx = 8;
		list = net->xfrm.policy_byidx + idx_hash(net, idx);
		found = 0;
		hlist_क्रम_each_entry(p, list, byidx) अणु
			अगर (p->index == idx) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found)
			वापस idx;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक selector_cmp(काष्ठा xfrm_selector *s1, काष्ठा xfrm_selector *s2)
अणु
	u32 *p1 = (u32 *) s1;
	u32 *p2 = (u32 *) s2;
	पूर्णांक len = माप(काष्ठा xfrm_selector) / माप(u32);
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (p1[i] != p2[i])
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xfrm_policy_requeue(काष्ठा xfrm_policy *old,
				काष्ठा xfrm_policy *new)
अणु
	काष्ठा xfrm_policy_queue *pq = &old->polq;
	काष्ठा sk_buff_head list;

	अगर (skb_queue_empty(&pq->hold_queue))
		वापस;

	__skb_queue_head_init(&list);

	spin_lock_bh(&pq->hold_queue.lock);
	skb_queue_splice_init(&pq->hold_queue, &list);
	अगर (del_समयr(&pq->hold_समयr))
		xfrm_pol_put(old);
	spin_unlock_bh(&pq->hold_queue.lock);

	pq = &new->polq;

	spin_lock_bh(&pq->hold_queue.lock);
	skb_queue_splice(&list, &pq->hold_queue);
	pq->समयout = XFRM_QUEUE_TMO_MIN;
	अगर (!mod_समयr(&pq->hold_समयr, jअगरfies))
		xfrm_pol_hold(new);
	spin_unlock_bh(&pq->hold_queue.lock);
पूर्ण

अटल अंतरभूत bool xfrm_policy_mark_match(स्थिर काष्ठा xfrm_mark *mark,
					  काष्ठा xfrm_policy *pol)
अणु
	वापस mark->v == pol->mark.v && mark->m == pol->mark.m;
पूर्ण

अटल u32 xfrm_pol_bin_key(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा xfrm_pol_inexact_key *k = data;
	u32 a = k->type << 24 | k->dir << 16 | k->family;

	वापस jhash_3words(a, k->अगर_id, net_hash_mix(पढ़ो_pnet(&k->net)),
			    seed);
पूर्ण

अटल u32 xfrm_pol_bin_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा xfrm_pol_inexact_bin *b = data;

	वापस xfrm_pol_bin_key(&b->k, 0, seed);
पूर्ण

अटल पूर्णांक xfrm_pol_bin_cmp(काष्ठा rhashtable_compare_arg *arg,
			    स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा xfrm_pol_inexact_key *key = arg->key;
	स्थिर काष्ठा xfrm_pol_inexact_bin *b = ptr;
	पूर्णांक ret;

	अगर (!net_eq(पढ़ो_pnet(&b->k.net), पढ़ो_pnet(&key->net)))
		वापस -1;

	ret = b->k.dir ^ key->dir;
	अगर (ret)
		वापस ret;

	ret = b->k.type ^ key->type;
	अगर (ret)
		वापस ret;

	ret = b->k.family ^ key->family;
	अगर (ret)
		वापस ret;

	वापस b->k.अगर_id ^ key->अगर_id;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params xfrm_pol_inexact_params = अणु
	.head_offset		= दुरत्व(काष्ठा xfrm_pol_inexact_bin, head),
	.hashfn			= xfrm_pol_bin_key,
	.obj_hashfn		= xfrm_pol_bin_obj,
	.obj_cmpfn		= xfrm_pol_bin_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

अटल व्योम xfrm_policy_insert_inexact_list(काष्ठा hlist_head *chain,
					    काष्ठा xfrm_policy *policy)
अणु
	काष्ठा xfrm_policy *pol, *delpol = शून्य;
	काष्ठा hlist_node *newpos = शून्य;
	पूर्णांक i = 0;

	hlist_क्रम_each_entry(pol, chain, bydst_inexact_list) अणु
		अगर (pol->type == policy->type &&
		    pol->अगर_id == policy->अगर_id &&
		    !selector_cmp(&pol->selector, &policy->selector) &&
		    xfrm_policy_mark_match(&policy->mark, pol) &&
		    xfrm_sec_ctx_match(pol->security, policy->security) &&
		    !WARN_ON(delpol)) अणु
			delpol = pol;
			अगर (policy->priority > pol->priority)
				जारी;
		पूर्ण अन्यथा अगर (policy->priority >= pol->priority) अणु
			newpos = &pol->bydst_inexact_list;
			जारी;
		पूर्ण
		अगर (delpol)
			अवरोध;
	पूर्ण

	अगर (newpos)
		hlist_add_behind_rcu(&policy->bydst_inexact_list, newpos);
	अन्यथा
		hlist_add_head_rcu(&policy->bydst_inexact_list, chain);

	hlist_क्रम_each_entry(pol, chain, bydst_inexact_list) अणु
		pol->pos = i;
		i++;
	पूर्ण
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_policy_insert_list(काष्ठा hlist_head *chain,
						   काष्ठा xfrm_policy *policy,
						   bool excl)
अणु
	काष्ठा xfrm_policy *pol, *newpos = शून्य, *delpol = शून्य;

	hlist_क्रम_each_entry(pol, chain, bydst) अणु
		अगर (pol->type == policy->type &&
		    pol->अगर_id == policy->अगर_id &&
		    !selector_cmp(&pol->selector, &policy->selector) &&
		    xfrm_policy_mark_match(&policy->mark, pol) &&
		    xfrm_sec_ctx_match(pol->security, policy->security) &&
		    !WARN_ON(delpol)) अणु
			अगर (excl)
				वापस ERR_PTR(-EEXIST);
			delpol = pol;
			अगर (policy->priority > pol->priority)
				जारी;
		पूर्ण अन्यथा अगर (policy->priority >= pol->priority) अणु
			newpos = pol;
			जारी;
		पूर्ण
		अगर (delpol)
			अवरोध;
	पूर्ण

	अगर (newpos)
		hlist_add_behind_rcu(&policy->bydst, &newpos->bydst);
	अन्यथा
		hlist_add_head_rcu(&policy->bydst, chain);

	वापस delpol;
पूर्ण

पूर्णांक xfrm_policy_insert(पूर्णांक dir, काष्ठा xfrm_policy *policy, पूर्णांक excl)
अणु
	काष्ठा net *net = xp_net(policy);
	काष्ठा xfrm_policy *delpol;
	काष्ठा hlist_head *chain;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	chain = policy_hash_bysel(net, &policy->selector, policy->family, dir);
	अगर (chain)
		delpol = xfrm_policy_insert_list(chain, policy, excl);
	अन्यथा
		delpol = xfrm_policy_inexact_insert(policy, dir, excl);

	अगर (IS_ERR(delpol)) अणु
		spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
		वापस PTR_ERR(delpol);
	पूर्ण

	__xfrm_policy_link(policy, dir);

	/* After previous checking, family can either be AF_INET or AF_INET6 */
	अगर (policy->family == AF_INET)
		rt_genid_bump_ipv4(net);
	अन्यथा
		rt_genid_bump_ipv6(net);

	अगर (delpol) अणु
		xfrm_policy_requeue(delpol, policy);
		__xfrm_policy_unlink(delpol, dir);
	पूर्ण
	policy->index = delpol ? delpol->index : xfrm_gen_index(net, dir, policy->index);
	hlist_add_head(&policy->byidx, net->xfrm.policy_byidx+idx_hash(net, policy->index));
	policy->curlft.add_समय = kसमय_get_real_seconds();
	policy->curlft.use_समय = 0;
	अगर (!mod_समयr(&policy->समयr, jअगरfies + HZ))
		xfrm_pol_hold(policy);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	अगर (delpol)
		xfrm_policy_समाप्त(delpol);
	अन्यथा अगर (xfrm_bydst_should_resize(net, dir, शून्य))
		schedule_work(&net->xfrm.policy_hash_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_insert);

अटल काष्ठा xfrm_policy *
__xfrm_policy_bysel_ctx(काष्ठा hlist_head *chain, स्थिर काष्ठा xfrm_mark *mark,
			u32 अगर_id, u8 type, पूर्णांक dir, काष्ठा xfrm_selector *sel,
			काष्ठा xfrm_sec_ctx *ctx)
अणु
	काष्ठा xfrm_policy *pol;

	अगर (!chain)
		वापस शून्य;

	hlist_क्रम_each_entry(pol, chain, bydst) अणु
		अगर (pol->type == type &&
		    pol->अगर_id == अगर_id &&
		    xfrm_policy_mark_match(mark, pol) &&
		    !selector_cmp(sel, &pol->selector) &&
		    xfrm_sec_ctx_match(ctx, pol->security))
			वापस pol;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा xfrm_policy *
xfrm_policy_bysel_ctx(काष्ठा net *net, स्थिर काष्ठा xfrm_mark *mark, u32 अगर_id,
		      u8 type, पूर्णांक dir, काष्ठा xfrm_selector *sel,
		      काष्ठा xfrm_sec_ctx *ctx, पूर्णांक delete, पूर्णांक *err)
अणु
	काष्ठा xfrm_pol_inexact_bin *bin = शून्य;
	काष्ठा xfrm_policy *pol, *ret = शून्य;
	काष्ठा hlist_head *chain;

	*err = 0;
	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	chain = policy_hash_bysel(net, sel, sel->family, dir);
	अगर (!chain) अणु
		काष्ठा xfrm_pol_inexact_candidates cand;
		पूर्णांक i;

		bin = xfrm_policy_inexact_lookup(net, type,
						 sel->family, dir, अगर_id);
		अगर (!bin) अणु
			spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
			वापस शून्य;
		पूर्ण

		अगर (!xfrm_policy_find_inexact_candidates(&cand, bin,
							 &sel->saddr,
							 &sel->daddr)) अणु
			spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
			वापस शून्य;
		पूर्ण

		pol = शून्य;
		क्रम (i = 0; i < ARRAY_SIZE(cand.res); i++) अणु
			काष्ठा xfrm_policy *पंचांगp;

			पंचांगp = __xfrm_policy_bysel_ctx(cand.res[i], mark,
						      अगर_id, type, dir,
						      sel, ctx);
			अगर (!पंचांगp)
				जारी;

			अगर (!pol || पंचांगp->pos < pol->pos)
				pol = पंचांगp;
		पूर्ण
	पूर्ण अन्यथा अणु
		pol = __xfrm_policy_bysel_ctx(chain, mark, अगर_id, type, dir,
					      sel, ctx);
	पूर्ण

	अगर (pol) अणु
		xfrm_pol_hold(pol);
		अगर (delete) अणु
			*err = security_xfrm_policy_delete(pol->security);
			अगर (*err) अणु
				spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
				वापस pol;
			पूर्ण
			__xfrm_policy_unlink(pol, dir);
		पूर्ण
		ret = pol;
	पूर्ण
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	अगर (ret && delete)
		xfrm_policy_समाप्त(ret);
	अगर (bin && delete)
		xfrm_policy_inexact_prune_bin(bin);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_bysel_ctx);

काष्ठा xfrm_policy *
xfrm_policy_byid(काष्ठा net *net, स्थिर काष्ठा xfrm_mark *mark, u32 अगर_id,
		 u8 type, पूर्णांक dir, u32 id, पूर्णांक delete, पूर्णांक *err)
अणु
	काष्ठा xfrm_policy *pol, *ret;
	काष्ठा hlist_head *chain;

	*err = -ENOENT;
	अगर (xfrm_policy_id2dir(id) != dir)
		वापस शून्य;

	*err = 0;
	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	chain = net->xfrm.policy_byidx + idx_hash(net, id);
	ret = शून्य;
	hlist_क्रम_each_entry(pol, chain, byidx) अणु
		अगर (pol->type == type && pol->index == id &&
		    pol->अगर_id == अगर_id && xfrm_policy_mark_match(mark, pol)) अणु
			xfrm_pol_hold(pol);
			अगर (delete) अणु
				*err = security_xfrm_policy_delete(
								pol->security);
				अगर (*err) अणु
					spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
					वापस pol;
				पूर्ण
				__xfrm_policy_unlink(pol, dir);
			पूर्ण
			ret = pol;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	अगर (ret && delete)
		xfrm_policy_समाप्त(ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_byid);

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
अटल अंतरभूत पूर्णांक
xfrm_policy_flush_secctx_check(काष्ठा net *net, u8 type, bool task_valid)
अणु
	काष्ठा xfrm_policy *pol;
	पूर्णांक err = 0;

	list_क्रम_each_entry(pol, &net->xfrm.policy_all, walk.all) अणु
		अगर (pol->walk.dead ||
		    xfrm_policy_id2dir(pol->index) >= XFRM_POLICY_MAX ||
		    pol->type != type)
			जारी;

		err = security_xfrm_policy_delete(pol->security);
		अगर (err) अणु
			xfrm_audit_policy_delete(pol, 0, task_valid);
			वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
xfrm_policy_flush_secctx_check(काष्ठा net *net, u8 type, bool task_valid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक xfrm_policy_flush(काष्ठा net *net, u8 type, bool task_valid)
अणु
	पूर्णांक dir, err = 0, cnt = 0;
	काष्ठा xfrm_policy *pol;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);

	err = xfrm_policy_flush_secctx_check(net, type, task_valid);
	अगर (err)
		जाओ out;

again:
	list_क्रम_each_entry(pol, &net->xfrm.policy_all, walk.all) अणु
		dir = xfrm_policy_id2dir(pol->index);
		अगर (pol->walk.dead ||
		    dir >= XFRM_POLICY_MAX ||
		    pol->type != type)
			जारी;

		__xfrm_policy_unlink(pol, dir);
		spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
		cnt++;
		xfrm_audit_policy_delete(pol, 1, task_valid);
		xfrm_policy_समाप्त(pol);
		spin_lock_bh(&net->xfrm.xfrm_policy_lock);
		जाओ again;
	पूर्ण
	अगर (cnt)
		__xfrm_policy_inexact_flush(net);
	अन्यथा
		err = -ESRCH;
out:
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_flush);

पूर्णांक xfrm_policy_walk(काष्ठा net *net, काष्ठा xfrm_policy_walk *walk,
		     पूर्णांक (*func)(काष्ठा xfrm_policy *, पूर्णांक, पूर्णांक, व्योम*),
		     व्योम *data)
अणु
	काष्ठा xfrm_policy *pol;
	काष्ठा xfrm_policy_walk_entry *x;
	पूर्णांक error = 0;

	अगर (walk->type >= XFRM_POLICY_TYPE_MAX &&
	    walk->type != XFRM_POLICY_TYPE_ANY)
		वापस -EINVAL;

	अगर (list_empty(&walk->walk.all) && walk->seq != 0)
		वापस 0;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	अगर (list_empty(&walk->walk.all))
		x = list_first_entry(&net->xfrm.policy_all, काष्ठा xfrm_policy_walk_entry, all);
	अन्यथा
		x = list_first_entry(&walk->walk.all,
				     काष्ठा xfrm_policy_walk_entry, all);

	list_क्रम_each_entry_from(x, &net->xfrm.policy_all, all) अणु
		अगर (x->dead)
			जारी;
		pol = container_of(x, काष्ठा xfrm_policy, walk);
		अगर (walk->type != XFRM_POLICY_TYPE_ANY &&
		    walk->type != pol->type)
			जारी;
		error = func(pol, xfrm_policy_id2dir(pol->index),
			     walk->seq, data);
		अगर (error) अणु
			list_move_tail(&walk->walk.all, &x->all);
			जाओ out;
		पूर्ण
		walk->seq++;
	पूर्ण
	अगर (walk->seq == 0) अणु
		error = -ENOENT;
		जाओ out;
	पूर्ण
	list_del_init(&walk->walk.all);
out:
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
	वापस error;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_walk);

व्योम xfrm_policy_walk_init(काष्ठा xfrm_policy_walk *walk, u8 type)
अणु
	INIT_LIST_HEAD(&walk->walk.all);
	walk->walk.dead = 1;
	walk->type = type;
	walk->seq = 0;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_walk_init);

व्योम xfrm_policy_walk_करोne(काष्ठा xfrm_policy_walk *walk, काष्ठा net *net)
अणु
	अगर (list_empty(&walk->walk.all))
		वापस;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock); /*FIXME where is net? */
	list_del(&walk->walk.all);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
पूर्ण
EXPORT_SYMBOL(xfrm_policy_walk_करोne);

/*
 * Find policy to apply to this flow.
 *
 * Returns 0 अगर policy found, अन्यथा an -त्रुटि_सं.
 */
अटल पूर्णांक xfrm_policy_match(स्थिर काष्ठा xfrm_policy *pol,
			     स्थिर काष्ठा flowi *fl,
			     u8 type, u16 family, पूर्णांक dir, u32 अगर_id)
अणु
	स्थिर काष्ठा xfrm_selector *sel = &pol->selector;
	पूर्णांक ret = -ESRCH;
	bool match;

	अगर (pol->family != family ||
	    pol->अगर_id != अगर_id ||
	    (fl->flowi_mark & pol->mark.m) != pol->mark.v ||
	    pol->type != type)
		वापस ret;

	match = xfrm_selector_match(sel, fl, family);
	अगर (match)
		ret = security_xfrm_policy_lookup(pol->security, fl->flowi_secid,
						  dir);
	वापस ret;
पूर्ण

अटल काष्ठा xfrm_pol_inexact_node *
xfrm_policy_lookup_inexact_addr(स्थिर काष्ठा rb_root *r,
				seqcount_spinlock_t *count,
				स्थिर xfrm_address_t *addr, u16 family)
अणु
	स्थिर काष्ठा rb_node *parent;
	पूर्णांक seq;

again:
	seq = पढ़ो_seqcount_begin(count);

	parent = rcu_dereference_raw(r->rb_node);
	जबतक (parent) अणु
		काष्ठा xfrm_pol_inexact_node *node;
		पूर्णांक delta;

		node = rb_entry(parent, काष्ठा xfrm_pol_inexact_node, node);

		delta = xfrm_policy_addr_delta(addr, &node->addr,
					       node->prefixlen, family);
		अगर (delta < 0) अणु
			parent = rcu_dereference_raw(parent->rb_left);
			जारी;
		पूर्ण अन्यथा अगर (delta > 0) अणु
			parent = rcu_dereference_raw(parent->rb_right);
			जारी;
		पूर्ण

		वापस node;
	पूर्ण

	अगर (पढ़ो_seqcount_retry(count, seq))
		जाओ again;

	वापस शून्य;
पूर्ण

अटल bool
xfrm_policy_find_inexact_candidates(काष्ठा xfrm_pol_inexact_candidates *cand,
				    काष्ठा xfrm_pol_inexact_bin *b,
				    स्थिर xfrm_address_t *saddr,
				    स्थिर xfrm_address_t *daddr)
अणु
	काष्ठा xfrm_pol_inexact_node *n;
	u16 family;

	अगर (!b)
		वापस false;

	family = b->k.family;
	स_रखो(cand, 0, माप(*cand));
	cand->res[XFRM_POL_CAND_ANY] = &b->hhead;

	n = xfrm_policy_lookup_inexact_addr(&b->root_d, &b->count, daddr,
					    family);
	अगर (n) अणु
		cand->res[XFRM_POL_CAND_DADDR] = &n->hhead;
		n = xfrm_policy_lookup_inexact_addr(&n->root, &b->count, saddr,
						    family);
		अगर (n)
			cand->res[XFRM_POL_CAND_BOTH] = &n->hhead;
	पूर्ण

	n = xfrm_policy_lookup_inexact_addr(&b->root_s, &b->count, saddr,
					    family);
	अगर (n)
		cand->res[XFRM_POL_CAND_SADDR] = &n->hhead;

	वापस true;
पूर्ण

अटल काष्ठा xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup_rcu(काष्ठा net *net, u8 type, u16 family,
			       u8 dir, u32 अगर_id)
अणु
	काष्ठा xfrm_pol_inexact_key k = अणु
		.family = family,
		.type = type,
		.dir = dir,
		.अगर_id = अगर_id,
	पूर्ण;

	ग_लिखो_pnet(&k.net, net);

	वापस rhashtable_lookup(&xfrm_policy_inexact_table, &k,
				 xfrm_pol_inexact_params);
पूर्ण

अटल काष्ठा xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup(काष्ठा net *net, u8 type, u16 family,
			   u8 dir, u32 अगर_id)
अणु
	काष्ठा xfrm_pol_inexact_bin *bin;

	lockdep_निश्चित_held(&net->xfrm.xfrm_policy_lock);

	rcu_पढ़ो_lock();
	bin = xfrm_policy_inexact_lookup_rcu(net, type, family, dir, अगर_id);
	rcu_पढ़ो_unlock();

	वापस bin;
पूर्ण

अटल काष्ठा xfrm_policy *
__xfrm_policy_eval_candidates(काष्ठा hlist_head *chain,
			      काष्ठा xfrm_policy *prefer,
			      स्थिर काष्ठा flowi *fl,
			      u8 type, u16 family, पूर्णांक dir, u32 अगर_id)
अणु
	u32 priority = prefer ? prefer->priority : ~0u;
	काष्ठा xfrm_policy *pol;

	अगर (!chain)
		वापस शून्य;

	hlist_क्रम_each_entry_rcu(pol, chain, bydst) अणु
		पूर्णांक err;

		अगर (pol->priority > priority)
			अवरोध;

		err = xfrm_policy_match(pol, fl, type, family, dir, अगर_id);
		अगर (err) अणु
			अगर (err != -ESRCH)
				वापस ERR_PTR(err);

			जारी;
		पूर्ण

		अगर (prefer) अणु
			/* matches.  Is it older than *prefer? */
			अगर (pol->priority == priority &&
			    prefer->pos < pol->pos)
				वापस prefer;
		पूर्ण

		वापस pol;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा xfrm_policy *
xfrm_policy_eval_candidates(काष्ठा xfrm_pol_inexact_candidates *cand,
			    काष्ठा xfrm_policy *prefer,
			    स्थिर काष्ठा flowi *fl,
			    u8 type, u16 family, पूर्णांक dir, u32 अगर_id)
अणु
	काष्ठा xfrm_policy *पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cand->res); i++) अणु
		पंचांगp = __xfrm_policy_eval_candidates(cand->res[i],
						    prefer,
						    fl, type, family, dir,
						    अगर_id);
		अगर (!पंचांगp)
			जारी;

		अगर (IS_ERR(पंचांगp))
			वापस पंचांगp;
		prefer = पंचांगp;
	पूर्ण

	वापस prefer;
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_policy_lookup_bytype(काष्ठा net *net, u8 type,
						     स्थिर काष्ठा flowi *fl,
						     u16 family, u8 dir,
						     u32 अगर_id)
अणु
	काष्ठा xfrm_pol_inexact_candidates cand;
	स्थिर xfrm_address_t *daddr, *saddr;
	काष्ठा xfrm_pol_inexact_bin *bin;
	काष्ठा xfrm_policy *pol, *ret;
	काष्ठा hlist_head *chain;
	अचिन्हित पूर्णांक sequence;
	पूर्णांक err;

	daddr = xfrm_flowi_daddr(fl, family);
	saddr = xfrm_flowi_saddr(fl, family);
	अगर (unlikely(!daddr || !saddr))
		वापस शून्य;

	rcu_पढ़ो_lock();
 retry:
	करो अणु
		sequence = पढ़ो_seqcount_begin(&xfrm_policy_hash_generation);
		chain = policy_hash_direct(net, daddr, saddr, family, dir);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&xfrm_policy_hash_generation, sequence));

	ret = शून्य;
	hlist_क्रम_each_entry_rcu(pol, chain, bydst) अणु
		err = xfrm_policy_match(pol, fl, type, family, dir, अगर_id);
		अगर (err) अणु
			अगर (err == -ESRCH)
				जारी;
			अन्यथा अणु
				ret = ERR_PTR(err);
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = pol;
			अवरोध;
		पूर्ण
	पूर्ण
	bin = xfrm_policy_inexact_lookup_rcu(net, type, family, dir, अगर_id);
	अगर (!bin || !xfrm_policy_find_inexact_candidates(&cand, bin, saddr,
							 daddr))
		जाओ skip_inexact;

	pol = xfrm_policy_eval_candidates(&cand, ret, fl, type,
					  family, dir, अगर_id);
	अगर (pol) अणु
		ret = pol;
		अगर (IS_ERR(pol))
			जाओ fail;
	पूर्ण

skip_inexact:
	अगर (पढ़ो_seqcount_retry(&xfrm_policy_hash_generation, sequence))
		जाओ retry;

	अगर (ret && !xfrm_pol_hold_rcu(ret))
		जाओ retry;
fail:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_policy_lookup(काष्ठा net *net,
					      स्थिर काष्ठा flowi *fl,
					      u16 family, u8 dir, u32 अगर_id)
अणु
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	काष्ठा xfrm_policy *pol;

	pol = xfrm_policy_lookup_bytype(net, XFRM_POLICY_TYPE_SUB, fl, family,
					dir, अगर_id);
	अगर (pol != शून्य)
		वापस pol;
#पूर्ण_अगर
	वापस xfrm_policy_lookup_bytype(net, XFRM_POLICY_TYPE_MAIN, fl, family,
					 dir, अगर_id);
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_sk_policy_lookup(स्थिर काष्ठा sock *sk, पूर्णांक dir,
						 स्थिर काष्ठा flowi *fl,
						 u16 family, u32 अगर_id)
अणु
	काष्ठा xfrm_policy *pol;

	rcu_पढ़ो_lock();
 again:
	pol = rcu_dereference(sk->sk_policy[dir]);
	अगर (pol != शून्य) अणु
		bool match;
		पूर्णांक err = 0;

		अगर (pol->family != family) अणु
			pol = शून्य;
			जाओ out;
		पूर्ण

		match = xfrm_selector_match(&pol->selector, fl, family);
		अगर (match) अणु
			अगर ((sk->sk_mark & pol->mark.m) != pol->mark.v ||
			    pol->अगर_id != अगर_id) अणु
				pol = शून्य;
				जाओ out;
			पूर्ण
			err = security_xfrm_policy_lookup(pol->security,
						      fl->flowi_secid,
						      dir);
			अगर (!err) अणु
				अगर (!xfrm_pol_hold_rcu(pol))
					जाओ again;
			पूर्ण अन्यथा अगर (err == -ESRCH) अणु
				pol = शून्य;
			पूर्ण अन्यथा अणु
				pol = ERR_PTR(err);
			पूर्ण
		पूर्ण अन्यथा
			pol = शून्य;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस pol;
पूर्ण

अटल व्योम __xfrm_policy_link(काष्ठा xfrm_policy *pol, पूर्णांक dir)
अणु
	काष्ठा net *net = xp_net(pol);

	list_add(&pol->walk.all, &net->xfrm.policy_all);
	net->xfrm.policy_count[dir]++;
	xfrm_pol_hold(pol);
पूर्ण

अटल काष्ठा xfrm_policy *__xfrm_policy_unlink(काष्ठा xfrm_policy *pol,
						पूर्णांक dir)
अणु
	काष्ठा net *net = xp_net(pol);

	अगर (list_empty(&pol->walk.all))
		वापस शून्य;

	/* Socket policies are not hashed. */
	अगर (!hlist_unhashed(&pol->bydst)) अणु
		hlist_del_rcu(&pol->bydst);
		hlist_del_init(&pol->bydst_inexact_list);
		hlist_del(&pol->byidx);
	पूर्ण

	list_del_init(&pol->walk.all);
	net->xfrm.policy_count[dir]--;

	वापस pol;
पूर्ण

अटल व्योम xfrm_sk_policy_link(काष्ठा xfrm_policy *pol, पूर्णांक dir)
अणु
	__xfrm_policy_link(pol, XFRM_POLICY_MAX + dir);
पूर्ण

अटल व्योम xfrm_sk_policy_unlink(काष्ठा xfrm_policy *pol, पूर्णांक dir)
अणु
	__xfrm_policy_unlink(pol, XFRM_POLICY_MAX + dir);
पूर्ण

पूर्णांक xfrm_policy_delete(काष्ठा xfrm_policy *pol, पूर्णांक dir)
अणु
	काष्ठा net *net = xp_net(pol);

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	pol = __xfrm_policy_unlink(pol, dir);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
	अगर (pol) अणु
		xfrm_policy_समाप्त(pol);
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_delete);

पूर्णांक xfrm_sk_policy_insert(काष्ठा sock *sk, पूर्णांक dir, काष्ठा xfrm_policy *pol)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_policy *old_pol;

#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	अगर (pol && pol->type != XFRM_POLICY_TYPE_MAIN)
		वापस -EINVAL;
#पूर्ण_अगर

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	old_pol = rcu_dereference_रक्षित(sk->sk_policy[dir],
				lockdep_is_held(&net->xfrm.xfrm_policy_lock));
	अगर (pol) अणु
		pol->curlft.add_समय = kसमय_get_real_seconds();
		pol->index = xfrm_gen_index(net, XFRM_POLICY_MAX+dir, 0);
		xfrm_sk_policy_link(pol, dir);
	पूर्ण
	rcu_assign_poपूर्णांकer(sk->sk_policy[dir], pol);
	अगर (old_pol) अणु
		अगर (pol)
			xfrm_policy_requeue(old_pol, pol);

		/* Unlinking succeeds always. This is the only function
		 * allowed to delete or replace socket policy.
		 */
		xfrm_sk_policy_unlink(old_pol, dir);
	पूर्ण
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	अगर (old_pol) अणु
		xfrm_policy_समाप्त(old_pol);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xfrm_policy *clone_policy(स्थिर काष्ठा xfrm_policy *old, पूर्णांक dir)
अणु
	काष्ठा xfrm_policy *newp = xfrm_policy_alloc(xp_net(old), GFP_ATOMIC);
	काष्ठा net *net = xp_net(old);

	अगर (newp) अणु
		newp->selector = old->selector;
		अगर (security_xfrm_policy_clone(old->security,
					       &newp->security)) अणु
			kमुक्त(newp);
			वापस शून्य;  /* ENOMEM */
		पूर्ण
		newp->lft = old->lft;
		newp->curlft = old->curlft;
		newp->mark = old->mark;
		newp->अगर_id = old->अगर_id;
		newp->action = old->action;
		newp->flags = old->flags;
		newp->xfrm_nr = old->xfrm_nr;
		newp->index = old->index;
		newp->type = old->type;
		newp->family = old->family;
		स_नकल(newp->xfrm_vec, old->xfrm_vec,
		       newp->xfrm_nr*माप(काष्ठा xfrm_पंचांगpl));
		spin_lock_bh(&net->xfrm.xfrm_policy_lock);
		xfrm_sk_policy_link(newp, dir);
		spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
		xfrm_pol_put(newp);
	पूर्ण
	वापस newp;
पूर्ण

पूर्णांक __xfrm_sk_clone_policy(काष्ठा sock *sk, स्थिर काष्ठा sock *osk)
अणु
	स्थिर काष्ठा xfrm_policy *p;
	काष्ठा xfrm_policy *np;
	पूर्णांक i, ret = 0;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < 2; i++) अणु
		p = rcu_dereference(osk->sk_policy[i]);
		अगर (p) अणु
			np = clone_policy(p, i);
			अगर (unlikely(!np)) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			rcu_assign_poपूर्णांकer(sk->sk_policy[i], np);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक
xfrm_get_saddr(काष्ठा net *net, पूर्णांक oअगर, xfrm_address_t *local,
	       xfrm_address_t *remote, अचिन्हित लघु family, u32 mark)
अणु
	पूर्णांक err;
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);

	अगर (unlikely(afinfo == शून्य))
		वापस -EINVAL;
	err = afinfo->get_saddr(net, oअगर, local, remote, mark);
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* Resolve list of ढाँचाs क्रम the flow, given policy. */

अटल पूर्णांक
xfrm_पंचांगpl_resolve_one(काष्ठा xfrm_policy *policy, स्थिर काष्ठा flowi *fl,
		      काष्ठा xfrm_state **xfrm, अचिन्हित लघु family)
अणु
	काष्ठा net *net = xp_net(policy);
	पूर्णांक nx;
	पूर्णांक i, error;
	xfrm_address_t *daddr = xfrm_flowi_daddr(fl, family);
	xfrm_address_t *saddr = xfrm_flowi_saddr(fl, family);
	xfrm_address_t पंचांगp;

	क्रम (nx = 0, i = 0; i < policy->xfrm_nr; i++) अणु
		काष्ठा xfrm_state *x;
		xfrm_address_t *remote = daddr;
		xfrm_address_t *local  = saddr;
		काष्ठा xfrm_पंचांगpl *पंचांगpl = &policy->xfrm_vec[i];

		अगर (पंचांगpl->mode == XFRM_MODE_TUNNEL ||
		    पंचांगpl->mode == XFRM_MODE_BEET) अणु
			remote = &पंचांगpl->id.daddr;
			local = &पंचांगpl->saddr;
			अगर (xfrm_addr_any(local, पंचांगpl->encap_family)) अणु
				error = xfrm_get_saddr(net, fl->flowi_oअगर,
						       &पंचांगp, remote,
						       पंचांगpl->encap_family, 0);
				अगर (error)
					जाओ fail;
				local = &पंचांगp;
			पूर्ण
		पूर्ण

		x = xfrm_state_find(remote, local, fl, पंचांगpl, policy, &error,
				    family, policy->अगर_id);

		अगर (x && x->km.state == XFRM_STATE_VALID) अणु
			xfrm[nx++] = x;
			daddr = remote;
			saddr = local;
			जारी;
		पूर्ण
		अगर (x) अणु
			error = (x->km.state == XFRM_STATE_ERROR ?
				 -EINVAL : -EAGAIN);
			xfrm_state_put(x);
		पूर्ण अन्यथा अगर (error == -ESRCH) अणु
			error = -EAGAIN;
		पूर्ण

		अगर (!पंचांगpl->optional)
			जाओ fail;
	पूर्ण
	वापस nx;

fail:
	क्रम (nx--; nx >= 0; nx--)
		xfrm_state_put(xfrm[nx]);
	वापस error;
पूर्ण

अटल पूर्णांक
xfrm_पंचांगpl_resolve(काष्ठा xfrm_policy **pols, पूर्णांक npols, स्थिर काष्ठा flowi *fl,
		  काष्ठा xfrm_state **xfrm, अचिन्हित लघु family)
अणु
	काष्ठा xfrm_state *tp[XFRM_MAX_DEPTH];
	काष्ठा xfrm_state **tpp = (npols > 1) ? tp : xfrm;
	पूर्णांक cnx = 0;
	पूर्णांक error;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < npols; i++) अणु
		अगर (cnx + pols[i]->xfrm_nr >= XFRM_MAX_DEPTH) अणु
			error = -ENOBUFS;
			जाओ fail;
		पूर्ण

		ret = xfrm_पंचांगpl_resolve_one(pols[i], fl, &tpp[cnx], family);
		अगर (ret < 0) अणु
			error = ret;
			जाओ fail;
		पूर्ण अन्यथा
			cnx += ret;
	पूर्ण

	/* found states are sorted क्रम outbound processing */
	अगर (npols > 1)
		xfrm_state_sort(xfrm, tpp, cnx, family);

	वापस cnx;

 fail:
	क्रम (cnx--; cnx >= 0; cnx--)
		xfrm_state_put(tpp[cnx]);
	वापस error;

पूर्ण

अटल पूर्णांक xfrm_get_tos(स्थिर काष्ठा flowi *fl, पूर्णांक family)
अणु
	अगर (family == AF_INET)
		वापस IPTOS_RT_MASK & fl->u.ip4.flowi4_tos;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_dst *xfrm_alloc_dst(काष्ठा net *net, पूर्णांक family)
अणु
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);
	काष्ठा dst_ops *dst_ops;
	काष्ठा xfrm_dst *xdst;

	अगर (!afinfo)
		वापस ERR_PTR(-EINVAL);

	चयन (family) अणु
	हाल AF_INET:
		dst_ops = &net->xfrm.xfrm4_dst_ops;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		dst_ops = &net->xfrm.xfrm6_dst_ops;
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
	xdst = dst_alloc(dst_ops, शून्य, 1, DST_OBSOLETE_NONE, 0);

	अगर (likely(xdst)) अणु
		काष्ठा dst_entry *dst = &xdst->u.dst;

		स_रखो(dst + 1, 0, माप(*xdst) - माप(*dst));
	पूर्ण अन्यथा
		xdst = ERR_PTR(-ENOBUFS);

	rcu_पढ़ो_unlock();

	वापस xdst;
पूर्ण

अटल व्योम xfrm_init_path(काष्ठा xfrm_dst *path, काष्ठा dst_entry *dst,
			   पूर्णांक nfheader_len)
अणु
	अगर (dst->ops->family == AF_INET6) अणु
		काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;
		path->path_cookie = rt6_get_cookie(rt);
		path->u.rt6.rt6i_nfheader_len = nfheader_len;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_fill_dst(काष्ठा xfrm_dst *xdst, काष्ठा net_device *dev,
				स्थिर काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo =
		xfrm_policy_get_afinfo(xdst->u.dst.ops->family);
	पूर्णांक err;

	अगर (!afinfo)
		वापस -EINVAL;

	err = afinfo->fill_dst(xdst, dev, fl);

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण


/* Allocate chain of dst_entry's, attach known xfrm's, calculate
 * all the metrics... Shortly, bundle a bundle.
 */

अटल काष्ठा dst_entry *xfrm_bundle_create(काष्ठा xfrm_policy *policy,
					    काष्ठा xfrm_state **xfrm,
					    काष्ठा xfrm_dst **bundle,
					    पूर्णांक nx,
					    स्थिर काष्ठा flowi *fl,
					    काष्ठा dst_entry *dst)
अणु
	स्थिर काष्ठा xfrm_state_afinfo *afinfo;
	स्थिर काष्ठा xfrm_mode *inner_mode;
	काष्ठा net *net = xp_net(policy);
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा net_device *dev;
	काष्ठा xfrm_dst *xdst_prev = शून्य;
	काष्ठा xfrm_dst *xdst0 = शून्य;
	पूर्णांक i = 0;
	पूर्णांक err;
	पूर्णांक header_len = 0;
	पूर्णांक nfheader_len = 0;
	पूर्णांक trailer_len = 0;
	पूर्णांक tos;
	पूर्णांक family = policy->selector.family;
	xfrm_address_t saddr, daddr;

	xfrm_flowi_addr_get(fl, &saddr, &daddr, family);

	tos = xfrm_get_tos(fl, family);

	dst_hold(dst);

	क्रम (; i < nx; i++) अणु
		काष्ठा xfrm_dst *xdst = xfrm_alloc_dst(net, family);
		काष्ठा dst_entry *dst1 = &xdst->u.dst;

		err = PTR_ERR(xdst);
		अगर (IS_ERR(xdst)) अणु
			dst_release(dst);
			जाओ put_states;
		पूर्ण

		bundle[i] = xdst;
		अगर (!xdst_prev)
			xdst0 = xdst;
		अन्यथा
			/* Ref count is taken during xfrm_alloc_dst()
			 * No need to करो dst_clone() on dst1
			 */
			xfrm_dst_set_child(xdst_prev, &xdst->u.dst);

		अगर (xfrm[i]->sel.family == AF_UNSPEC) अणु
			inner_mode = xfrm_ip2inner_mode(xfrm[i],
							xfrm_af2proto(family));
			अगर (!inner_mode) अणु
				err = -EAFNOSUPPORT;
				dst_release(dst);
				जाओ put_states;
			पूर्ण
		पूर्ण अन्यथा
			inner_mode = &xfrm[i]->inner_mode;

		xdst->route = dst;
		dst_copy_metrics(dst1, dst);

		अगर (xfrm[i]->props.mode != XFRM_MODE_TRANSPORT) अणु
			__u32 mark = 0;

			अगर (xfrm[i]->props.smark.v || xfrm[i]->props.smark.m)
				mark = xfrm_smark_get(fl->flowi_mark, xfrm[i]);

			family = xfrm[i]->props.family;
			dst = xfrm_dst_lookup(xfrm[i], tos, fl->flowi_oअगर,
					      &saddr, &daddr, family, mark);
			err = PTR_ERR(dst);
			अगर (IS_ERR(dst))
				जाओ put_states;
		पूर्ण अन्यथा
			dst_hold(dst);

		dst1->xfrm = xfrm[i];
		xdst->xfrm_genid = xfrm[i]->genid;

		dst1->obsolete = DST_OBSOLETE_FORCE_CHK;
		dst1->lastuse = now;

		dst1->input = dst_discard;

		rcu_पढ़ो_lock();
		afinfo = xfrm_state_afinfo_get_rcu(inner_mode->family);
		अगर (likely(afinfo))
			dst1->output = afinfo->output;
		अन्यथा
			dst1->output = dst_discard_out;
		rcu_पढ़ो_unlock();

		xdst_prev = xdst;

		header_len += xfrm[i]->props.header_len;
		अगर (xfrm[i]->type->flags & XFRM_TYPE_NON_FRAGMENT)
			nfheader_len += xfrm[i]->props.header_len;
		trailer_len += xfrm[i]->props.trailer_len;
	पूर्ण

	xfrm_dst_set_child(xdst_prev, dst);
	xdst0->path = dst;

	err = -ENODEV;
	dev = dst->dev;
	अगर (!dev)
		जाओ मुक्त_dst;

	xfrm_init_path(xdst0, dst, nfheader_len);
	xfrm_init_pmtu(bundle, nx);

	क्रम (xdst_prev = xdst0; xdst_prev != (काष्ठा xfrm_dst *)dst;
	     xdst_prev = (काष्ठा xfrm_dst *) xfrm_dst_child(&xdst_prev->u.dst)) अणु
		err = xfrm_fill_dst(xdst_prev, dev, fl);
		अगर (err)
			जाओ मुक्त_dst;

		xdst_prev->u.dst.header_len = header_len;
		xdst_prev->u.dst.trailer_len = trailer_len;
		header_len -= xdst_prev->u.dst.xfrm->props.header_len;
		trailer_len -= xdst_prev->u.dst.xfrm->props.trailer_len;
	पूर्ण

	वापस &xdst0->u.dst;

put_states:
	क्रम (; i < nx; i++)
		xfrm_state_put(xfrm[i]);
मुक्त_dst:
	अगर (xdst0)
		dst_release_immediate(&xdst0->u.dst);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक xfrm_expand_policies(स्थिर काष्ठा flowi *fl, u16 family,
				काष्ठा xfrm_policy **pols,
				पूर्णांक *num_pols, पूर्णांक *num_xfrms)
अणु
	पूर्णांक i;

	अगर (*num_pols == 0 || !pols[0]) अणु
		*num_pols = 0;
		*num_xfrms = 0;
		वापस 0;
	पूर्ण
	अगर (IS_ERR(pols[0]))
		वापस PTR_ERR(pols[0]);

	*num_xfrms = pols[0]->xfrm_nr;

#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	अगर (pols[0] && pols[0]->action == XFRM_POLICY_ALLOW &&
	    pols[0]->type != XFRM_POLICY_TYPE_MAIN) अणु
		pols[1] = xfrm_policy_lookup_bytype(xp_net(pols[0]),
						    XFRM_POLICY_TYPE_MAIN,
						    fl, family,
						    XFRM_POLICY_OUT,
						    pols[0]->अगर_id);
		अगर (pols[1]) अणु
			अगर (IS_ERR(pols[1])) अणु
				xfrm_pols_put(pols, *num_pols);
				वापस PTR_ERR(pols[1]);
			पूर्ण
			(*num_pols)++;
			(*num_xfrms) += pols[1]->xfrm_nr;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	क्रम (i = 0; i < *num_pols; i++) अणु
		अगर (pols[i]->action != XFRM_POLICY_ALLOW) अणु
			*num_xfrms = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

अटल काष्ठा xfrm_dst *
xfrm_resolve_and_create_bundle(काष्ठा xfrm_policy **pols, पूर्णांक num_pols,
			       स्थिर काष्ठा flowi *fl, u16 family,
			       काष्ठा dst_entry *dst_orig)
अणु
	काष्ठा net *net = xp_net(pols[0]);
	काष्ठा xfrm_state *xfrm[XFRM_MAX_DEPTH];
	काष्ठा xfrm_dst *bundle[XFRM_MAX_DEPTH];
	काष्ठा xfrm_dst *xdst;
	काष्ठा dst_entry *dst;
	पूर्णांक err;

	/* Try to instantiate a bundle */
	err = xfrm_पंचांगpl_resolve(pols, num_pols, fl, xfrm, family);
	अगर (err <= 0) अणु
		अगर (err == 0)
			वापस शून्य;

		अगर (err != -EAGAIN)
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTPOLERROR);
		वापस ERR_PTR(err);
	पूर्ण

	dst = xfrm_bundle_create(pols[0], xfrm, bundle, err, fl, dst_orig);
	अगर (IS_ERR(dst)) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTBUNDLEGENERROR);
		वापस ERR_CAST(dst);
	पूर्ण

	xdst = (काष्ठा xfrm_dst *)dst;
	xdst->num_xfrms = err;
	xdst->num_pols = num_pols;
	स_नकल(xdst->pols, pols, माप(काष्ठा xfrm_policy *) * num_pols);
	xdst->policy_genid = atomic_पढ़ो(&pols[0]->genid);

	वापस xdst;
पूर्ण

अटल व्योम xfrm_policy_queue_process(काष्ठा समयr_list *t)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	काष्ठा dst_entry *dst;
	काष्ठा xfrm_policy *pol = from_समयr(pol, t, polq.hold_समयr);
	काष्ठा net *net = xp_net(pol);
	काष्ठा xfrm_policy_queue *pq = &pol->polq;
	काष्ठा flowi fl;
	काष्ठा sk_buff_head list;
	__u32 skb_mark;

	spin_lock(&pq->hold_queue.lock);
	skb = skb_peek(&pq->hold_queue);
	अगर (!skb) अणु
		spin_unlock(&pq->hold_queue.lock);
		जाओ out;
	पूर्ण
	dst = skb_dst(skb);
	sk = skb->sk;

	/* Fixup the mark to support VTI. */
	skb_mark = skb->mark;
	skb->mark = pol->mark.v;
	xfrm_decode_session(skb, &fl, dst->ops->family);
	skb->mark = skb_mark;
	spin_unlock(&pq->hold_queue.lock);

	dst_hold(xfrm_dst_path(dst));
	dst = xfrm_lookup(net, xfrm_dst_path(dst), &fl, sk, XFRM_LOOKUP_QUEUE);
	अगर (IS_ERR(dst))
		जाओ purge_queue;

	अगर (dst->flags & DST_XFRM_QUEUE) अणु
		dst_release(dst);

		अगर (pq->समयout >= XFRM_QUEUE_TMO_MAX)
			जाओ purge_queue;

		pq->समयout = pq->समयout << 1;
		अगर (!mod_समयr(&pq->hold_समयr, jअगरfies + pq->समयout))
			xfrm_pol_hold(pol);
		जाओ out;
	पूर्ण

	dst_release(dst);

	__skb_queue_head_init(&list);

	spin_lock(&pq->hold_queue.lock);
	pq->समयout = 0;
	skb_queue_splice_init(&pq->hold_queue, &list);
	spin_unlock(&pq->hold_queue.lock);

	जबतक (!skb_queue_empty(&list)) अणु
		skb = __skb_dequeue(&list);

		/* Fixup the mark to support VTI. */
		skb_mark = skb->mark;
		skb->mark = pol->mark.v;
		xfrm_decode_session(skb, &fl, skb_dst(skb)->ops->family);
		skb->mark = skb_mark;

		dst_hold(xfrm_dst_path(skb_dst(skb)));
		dst = xfrm_lookup(net, xfrm_dst_path(skb_dst(skb)), &fl, skb->sk, 0);
		अगर (IS_ERR(dst)) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		nf_reset_ct(skb);
		skb_dst_drop(skb);
		skb_dst_set(skb, dst);

		dst_output(net, skb->sk, skb);
	पूर्ण

out:
	xfrm_pol_put(pol);
	वापस;

purge_queue:
	pq->समयout = 0;
	skb_queue_purge(&pq->hold_queue);
	xfrm_pol_put(pol);
पूर्ण

अटल पूर्णांक xdst_queue_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ sched_next;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *) dst;
	काष्ठा xfrm_policy *pol = xdst->pols[0];
	काष्ठा xfrm_policy_queue *pq = &pol->polq;

	अगर (unlikely(skb_fclone_busy(sk, skb))) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (pq->hold_queue.qlen > XFRM_MAX_QUEUE_LEN) अणु
		kमुक्त_skb(skb);
		वापस -EAGAIN;
	पूर्ण

	skb_dst_क्रमce(skb);

	spin_lock_bh(&pq->hold_queue.lock);

	अगर (!pq->समयout)
		pq->समयout = XFRM_QUEUE_TMO_MIN;

	sched_next = jअगरfies + pq->समयout;

	अगर (del_समयr(&pq->hold_समयr)) अणु
		अगर (समय_beक्रमe(pq->hold_समयr.expires, sched_next))
			sched_next = pq->hold_समयr.expires;
		xfrm_pol_put(pol);
	पूर्ण

	__skb_queue_tail(&pq->hold_queue, skb);
	अगर (!mod_समयr(&pq->hold_समयr, sched_next))
		xfrm_pol_hold(pol);

	spin_unlock_bh(&pq->hold_queue.lock);

	वापस 0;
पूर्ण

अटल काष्ठा xfrm_dst *xfrm_create_dummy_bundle(काष्ठा net *net,
						 काष्ठा xfrm_flo *xflo,
						 स्थिर काष्ठा flowi *fl,
						 पूर्णांक num_xfrms,
						 u16 family)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev;
	काष्ठा dst_entry *dst;
	काष्ठा dst_entry *dst1;
	काष्ठा xfrm_dst *xdst;

	xdst = xfrm_alloc_dst(net, family);
	अगर (IS_ERR(xdst))
		वापस xdst;

	अगर (!(xflo->flags & XFRM_LOOKUP_QUEUE) ||
	    net->xfrm.sysctl_larval_drop ||
	    num_xfrms <= 0)
		वापस xdst;

	dst = xflo->dst_orig;
	dst1 = &xdst->u.dst;
	dst_hold(dst);
	xdst->route = dst;

	dst_copy_metrics(dst1, dst);

	dst1->obsolete = DST_OBSOLETE_FORCE_CHK;
	dst1->flags |= DST_XFRM_QUEUE;
	dst1->lastuse = jअगरfies;

	dst1->input = dst_discard;
	dst1->output = xdst_queue_output;

	dst_hold(dst);
	xfrm_dst_set_child(xdst, dst);
	xdst->path = dst;

	xfrm_init_path((काष्ठा xfrm_dst *)dst1, dst, 0);

	err = -ENODEV;
	dev = dst->dev;
	अगर (!dev)
		जाओ मुक्त_dst;

	err = xfrm_fill_dst(xdst, dev, fl);
	अगर (err)
		जाओ मुक्त_dst;

out:
	वापस xdst;

मुक्त_dst:
	dst_release(dst1);
	xdst = ERR_PTR(err);
	जाओ out;
पूर्ण

अटल काष्ठा xfrm_dst *xfrm_bundle_lookup(काष्ठा net *net,
					   स्थिर काष्ठा flowi *fl,
					   u16 family, u8 dir,
					   काष्ठा xfrm_flo *xflo, u32 अगर_id)
अणु
	काष्ठा xfrm_policy *pols[XFRM_POLICY_TYPE_MAX];
	पूर्णांक num_pols = 0, num_xfrms = 0, err;
	काष्ठा xfrm_dst *xdst;

	/* Resolve policies to use अगर we couldn't get them from
	 * previous cache entry */
	num_pols = 1;
	pols[0] = xfrm_policy_lookup(net, fl, family, dir, अगर_id);
	err = xfrm_expand_policies(fl, family, pols,
					   &num_pols, &num_xfrms);
	अगर (err < 0)
		जाओ inc_error;
	अगर (num_pols == 0)
		वापस शून्य;
	अगर (num_xfrms <= 0)
		जाओ make_dummy_bundle;

	xdst = xfrm_resolve_and_create_bundle(pols, num_pols, fl, family,
					      xflo->dst_orig);
	अगर (IS_ERR(xdst)) अणु
		err = PTR_ERR(xdst);
		अगर (err == -EREMOTE) अणु
			xfrm_pols_put(pols, num_pols);
			वापस शून्य;
		पूर्ण

		अगर (err != -EAGAIN)
			जाओ error;
		जाओ make_dummy_bundle;
	पूर्ण अन्यथा अगर (xdst == शून्य) अणु
		num_xfrms = 0;
		जाओ make_dummy_bundle;
	पूर्ण

	वापस xdst;

make_dummy_bundle:
	/* We found policies, but there's no bundles to instantiate:
	 * either because the policy blocks, has no transक्रमmations or
	 * we could not build ढाँचा (no xfrm_states).*/
	xdst = xfrm_create_dummy_bundle(net, xflo, fl, num_xfrms, family);
	अगर (IS_ERR(xdst)) अणु
		xfrm_pols_put(pols, num_pols);
		वापस ERR_CAST(xdst);
	पूर्ण
	xdst->num_pols = num_pols;
	xdst->num_xfrms = num_xfrms;
	स_नकल(xdst->pols, pols, माप(काष्ठा xfrm_policy *) * num_pols);

	वापस xdst;

inc_error:
	XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTPOLERROR);
error:
	xfrm_pols_put(pols, num_pols);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा dst_entry *make_blackhole(काष्ठा net *net, u16 family,
					काष्ठा dst_entry *dst_orig)
अणु
	स्थिर काष्ठा xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);
	काष्ठा dst_entry *ret;

	अगर (!afinfo) अणु
		dst_release(dst_orig);
		वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अणु
		ret = afinfo->blackhole_route(net, dst_orig);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Finds/creates a bundle क्रम given flow and अगर_id
 *
 * At the moment we eat a raw IP route. Mostly to speed up lookups
 * on पूर्णांकerfaces with disabled IPsec.
 *
 * xfrm_lookup uses an अगर_id of 0 by शेष, and is provided क्रम
 * compatibility
 */
काष्ठा dst_entry *xfrm_lookup_with_अगरid(काष्ठा net *net,
					काष्ठा dst_entry *dst_orig,
					स्थिर काष्ठा flowi *fl,
					स्थिर काष्ठा sock *sk,
					पूर्णांक flags, u32 अगर_id)
अणु
	काष्ठा xfrm_policy *pols[XFRM_POLICY_TYPE_MAX];
	काष्ठा xfrm_dst *xdst;
	काष्ठा dst_entry *dst, *route;
	u16 family = dst_orig->ops->family;
	u8 dir = XFRM_POLICY_OUT;
	पूर्णांक i, err, num_pols, num_xfrms = 0, drop_pols = 0;

	dst = शून्य;
	xdst = शून्य;
	route = शून्य;

	sk = sk_स्थिर_to_full_sk(sk);
	अगर (sk && sk->sk_policy[XFRM_POLICY_OUT]) अणु
		num_pols = 1;
		pols[0] = xfrm_sk_policy_lookup(sk, XFRM_POLICY_OUT, fl, family,
						अगर_id);
		err = xfrm_expand_policies(fl, family, pols,
					   &num_pols, &num_xfrms);
		अगर (err < 0)
			जाओ dropdst;

		अगर (num_pols) अणु
			अगर (num_xfrms <= 0) अणु
				drop_pols = num_pols;
				जाओ no_transक्रमm;
			पूर्ण

			xdst = xfrm_resolve_and_create_bundle(
					pols, num_pols, fl,
					family, dst_orig);

			अगर (IS_ERR(xdst)) अणु
				xfrm_pols_put(pols, num_pols);
				err = PTR_ERR(xdst);
				अगर (err == -EREMOTE)
					जाओ nopol;

				जाओ dropdst;
			पूर्ण अन्यथा अगर (xdst == शून्य) अणु
				num_xfrms = 0;
				drop_pols = num_pols;
				जाओ no_transक्रमm;
			पूर्ण

			route = xdst->route;
		पूर्ण
	पूर्ण

	अगर (xdst == शून्य) अणु
		काष्ठा xfrm_flo xflo;

		xflo.dst_orig = dst_orig;
		xflo.flags = flags;

		/* To accelerate a bit...  */
		अगर (!अगर_id && ((dst_orig->flags & DST_NOXFRM) ||
			       !net->xfrm.policy_count[XFRM_POLICY_OUT]))
			जाओ nopol;

		xdst = xfrm_bundle_lookup(net, fl, family, dir, &xflo, अगर_id);
		अगर (xdst == शून्य)
			जाओ nopol;
		अगर (IS_ERR(xdst)) अणु
			err = PTR_ERR(xdst);
			जाओ dropdst;
		पूर्ण

		num_pols = xdst->num_pols;
		num_xfrms = xdst->num_xfrms;
		स_नकल(pols, xdst->pols, माप(काष्ठा xfrm_policy *) * num_pols);
		route = xdst->route;
	पूर्ण

	dst = &xdst->u.dst;
	अगर (route == शून्य && num_xfrms > 0) अणु
		/* The only हाल when xfrm_bundle_lookup() वापसs a
		 * bundle with null route, is when the ढाँचा could
		 * not be resolved. It means policies are there, but
		 * bundle could not be created, since we करोn't yet
		 * have the xfrm_state's. We need to रुको क्रम KM to
		 * negotiate new SA's or bail out with error.*/
		अगर (net->xfrm.sysctl_larval_drop) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTNOSTATES);
			err = -EREMOTE;
			जाओ error;
		पूर्ण

		err = -EAGAIN;

		XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTNOSTATES);
		जाओ error;
	पूर्ण

no_transक्रमm:
	अगर (num_pols == 0)
		जाओ nopol;

	अगर ((flags & XFRM_LOOKUP_ICMP) &&
	    !(pols[0]->flags & XFRM_POLICY_ICMP)) अणु
		err = -ENOENT;
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < num_pols; i++)
		pols[i]->curlft.use_समय = kसमय_get_real_seconds();

	अगर (num_xfrms < 0) अणु
		/* Prohibit the flow */
		XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTPOLBLOCK);
		err = -EPERM;
		जाओ error;
	पूर्ण अन्यथा अगर (num_xfrms > 0) अणु
		/* Flow transक्रमmed */
		dst_release(dst_orig);
	पूर्ण अन्यथा अणु
		/* Flow passes untransक्रमmed */
		dst_release(dst);
		dst = dst_orig;
	पूर्ण
ok:
	xfrm_pols_put(pols, drop_pols);
	अगर (dst && dst->xfrm &&
	    dst->xfrm->props.mode == XFRM_MODE_TUNNEL)
		dst->flags |= DST_XFRM_TUNNEL;
	वापस dst;

nopol:
	अगर (!(flags & XFRM_LOOKUP_ICMP)) अणु
		dst = dst_orig;
		जाओ ok;
	पूर्ण
	err = -ENOENT;
error:
	dst_release(dst);
dropdst:
	अगर (!(flags & XFRM_LOOKUP_KEEP_DST_REF))
		dst_release(dst_orig);
	xfrm_pols_put(pols, drop_pols);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(xfrm_lookup_with_अगरid);

/* Main function: finds/creates a bundle क्रम given flow.
 *
 * At the moment we eat a raw IP route. Mostly to speed up lookups
 * on पूर्णांकerfaces with disabled IPsec.
 */
काष्ठा dst_entry *xfrm_lookup(काष्ठा net *net, काष्ठा dst_entry *dst_orig,
			      स्थिर काष्ठा flowi *fl, स्थिर काष्ठा sock *sk,
			      पूर्णांक flags)
अणु
	वापस xfrm_lookup_with_अगरid(net, dst_orig, fl, sk, flags, 0);
पूर्ण
EXPORT_SYMBOL(xfrm_lookup);

/* Callers of xfrm_lookup_route() must ensure a call to dst_output().
 * Otherwise we may send out blackholed packets.
 */
काष्ठा dst_entry *xfrm_lookup_route(काष्ठा net *net, काष्ठा dst_entry *dst_orig,
				    स्थिर काष्ठा flowi *fl,
				    स्थिर काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा dst_entry *dst = xfrm_lookup(net, dst_orig, fl, sk,
					    flags | XFRM_LOOKUP_QUEUE |
					    XFRM_LOOKUP_KEEP_DST_REF);

	अगर (PTR_ERR(dst) == -EREMOTE)
		वापस make_blackhole(net, dst_orig->ops->family, dst_orig);

	अगर (IS_ERR(dst))
		dst_release(dst_orig);

	वापस dst;
पूर्ण
EXPORT_SYMBOL(xfrm_lookup_route);

अटल अंतरभूत पूर्णांक
xfrm_secpath_reject(पूर्णांक idx, काष्ठा sk_buff *skb, स्थिर काष्ठा flowi *fl)
अणु
	काष्ठा sec_path *sp = skb_sec_path(skb);
	काष्ठा xfrm_state *x;

	अगर (!sp || idx < 0 || idx >= sp->len)
		वापस 0;
	x = sp->xvec[idx];
	अगर (!x->type->reject)
		वापस 0;
	वापस x->type->reject(x, skb, fl);
पूर्ण

/* When skb is transक्रमmed back to its "native" क्रमm, we have to
 * check policy restrictions. At the moment we make this in maximally
 * stupid way. Shame on me. :-) Of course, connected sockets must
 * have policy cached at them.
 */

अटल अंतरभूत पूर्णांक
xfrm_state_ok(स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl, स्थिर काष्ठा xfrm_state *x,
	      अचिन्हित लघु family)
अणु
	अगर (xfrm_state_kern(x))
		वापस पंचांगpl->optional && !xfrm_state_addr_cmp(पंचांगpl, x, पंचांगpl->encap_family);
	वापस	x->id.proto == पंचांगpl->id.proto &&
		(x->id.spi == पंचांगpl->id.spi || !पंचांगpl->id.spi) &&
		(x->props.reqid == पंचांगpl->reqid || !पंचांगpl->reqid) &&
		x->props.mode == पंचांगpl->mode &&
		(पंचांगpl->allalgs || (पंचांगpl->aalgos & (1<<x->props.aalgo)) ||
		 !(xfrm_id_proto_match(पंचांगpl->id.proto, IPSEC_PROTO_ANY))) &&
		!(x->props.mode != XFRM_MODE_TRANSPORT &&
		  xfrm_state_addr_cmp(पंचांगpl, x, family));
पूर्ण

/*
 * 0 or more than 0 is वापसed when validation is succeeded (either bypass
 * because of optional transport mode, or next index of the mathced secpath
 * state with the ढाँचा.
 * -1 is वापसed when no matching ढाँचा is found.
 * Otherwise "-2 - errored_index" is वापसed.
 */
अटल अंतरभूत पूर्णांक
xfrm_policy_ok(स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl, स्थिर काष्ठा sec_path *sp, पूर्णांक start,
	       अचिन्हित लघु family)
अणु
	पूर्णांक idx = start;

	अगर (पंचांगpl->optional) अणु
		अगर (पंचांगpl->mode == XFRM_MODE_TRANSPORT)
			वापस start;
	पूर्ण अन्यथा
		start = -1;
	क्रम (; idx < sp->len; idx++) अणु
		अगर (xfrm_state_ok(पंचांगpl, sp->xvec[idx], family))
			वापस ++idx;
		अगर (sp->xvec[idx]->props.mode != XFRM_MODE_TRANSPORT) अणु
			अगर (start == -1)
				start = -2-idx;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस start;
पूर्ण

अटल व्योम
decode_session4(काष्ठा sk_buff *skb, काष्ठा flowi *fl, bool reverse)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक ihl = iph->ihl;
	u8 *xprth = skb_network_header(skb) + ihl * 4;
	काष्ठा flowi4 *fl4 = &fl->u.ip4;
	पूर्णांक oअगर = 0;

	अगर (skb_dst(skb) && skb_dst(skb)->dev)
		oअगर = skb_dst(skb)->dev->अगरindex;

	स_रखो(fl4, 0, माप(काष्ठा flowi4));
	fl4->flowi4_mark = skb->mark;
	fl4->flowi4_oअगर = reverse ? skb->skb_iअगर : oअगर;

	fl4->flowi4_proto = iph->protocol;
	fl4->daddr = reverse ? iph->saddr : iph->daddr;
	fl4->saddr = reverse ? iph->daddr : iph->saddr;
	fl4->flowi4_tos = iph->tos;

	अगर (!ip_is_fragment(iph)) अणु
		चयन (iph->protocol) अणु
		हाल IPPROTO_UDP:
		हाल IPPROTO_UDPLITE:
		हाल IPPROTO_TCP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_DCCP:
			अगर (xprth + 4 < skb->data ||
			    pskb_may_pull(skb, xprth + 4 - skb->data)) अणु
				__be16 *ports;

				xprth = skb_network_header(skb) + ihl * 4;
				ports = (__be16 *)xprth;

				fl4->fl4_sport = ports[!!reverse];
				fl4->fl4_dport = ports[!reverse];
			पूर्ण
			अवरोध;
		हाल IPPROTO_ICMP:
			अगर (xprth + 2 < skb->data ||
			    pskb_may_pull(skb, xprth + 2 - skb->data)) अणु
				u8 *icmp;

				xprth = skb_network_header(skb) + ihl * 4;
				icmp = xprth;

				fl4->fl4_icmp_type = icmp[0];
				fl4->fl4_icmp_code = icmp[1];
			पूर्ण
			अवरोध;
		हाल IPPROTO_GRE:
			अगर (xprth + 12 < skb->data ||
			    pskb_may_pull(skb, xprth + 12 - skb->data)) अणु
				__be16 *greflags;
				__be32 *gre_hdr;

				xprth = skb_network_header(skb) + ihl * 4;
				greflags = (__be16 *)xprth;
				gre_hdr = (__be32 *)xprth;

				अगर (greflags[0] & GRE_KEY) अणु
					अगर (greflags[0] & GRE_CSUM)
						gre_hdr++;
					fl4->fl4_gre_key = gre_hdr[1];
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम
decode_session6(काष्ठा sk_buff *skb, काष्ठा flowi *fl, bool reverse)
अणु
	काष्ठा flowi6 *fl6 = &fl->u.ip6;
	पूर्णांक onlyproto = 0;
	स्थिर काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	u32 offset = माप(*hdr);
	काष्ठा ipv6_opt_hdr *exthdr;
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	u16 nhoff = IP6CB(skb)->nhoff;
	पूर्णांक oअगर = 0;
	u8 nexthdr;

	अगर (!nhoff)
		nhoff = दुरत्व(काष्ठा ipv6hdr, nexthdr);

	nexthdr = nh[nhoff];

	अगर (skb_dst(skb) && skb_dst(skb)->dev)
		oअगर = skb_dst(skb)->dev->अगरindex;

	स_रखो(fl6, 0, माप(काष्ठा flowi6));
	fl6->flowi6_mark = skb->mark;
	fl6->flowi6_oअगर = reverse ? skb->skb_iअगर : oअगर;

	fl6->daddr = reverse ? hdr->saddr : hdr->daddr;
	fl6->saddr = reverse ? hdr->daddr : hdr->saddr;

	जबतक (nh + offset + माप(*exthdr) < skb->data ||
	       pskb_may_pull(skb, nh + offset + माप(*exthdr) - skb->data)) अणु
		nh = skb_network_header(skb);
		exthdr = (काष्ठा ipv6_opt_hdr *)(nh + offset);

		चयन (nexthdr) अणु
		हाल NEXTHDR_FRAGMENT:
			onlyproto = 1;
			fallthrough;
		हाल NEXTHDR_ROUTING:
		हाल NEXTHDR_HOP:
		हाल NEXTHDR_DEST:
			offset += ipv6_optlen(exthdr);
			nexthdr = exthdr->nexthdr;
			exthdr = (काष्ठा ipv6_opt_hdr *)(nh + offset);
			अवरोध;
		हाल IPPROTO_UDP:
		हाल IPPROTO_UDPLITE:
		हाल IPPROTO_TCP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_DCCP:
			अगर (!onlyproto && (nh + offset + 4 < skb->data ||
			     pskb_may_pull(skb, nh + offset + 4 - skb->data))) अणु
				__be16 *ports;

				nh = skb_network_header(skb);
				ports = (__be16 *)(nh + offset);
				fl6->fl6_sport = ports[!!reverse];
				fl6->fl6_dport = ports[!reverse];
			पूर्ण
			fl6->flowi6_proto = nexthdr;
			वापस;
		हाल IPPROTO_ICMPV6:
			अगर (!onlyproto && (nh + offset + 2 < skb->data ||
			    pskb_may_pull(skb, nh + offset + 2 - skb->data))) अणु
				u8 *icmp;

				nh = skb_network_header(skb);
				icmp = (u8 *)(nh + offset);
				fl6->fl6_icmp_type = icmp[0];
				fl6->fl6_icmp_code = icmp[1];
			पूर्ण
			fl6->flowi6_proto = nexthdr;
			वापस;
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		हाल IPPROTO_MH:
			offset += ipv6_optlen(exthdr);
			अगर (!onlyproto && (nh + offset + 3 < skb->data ||
			    pskb_may_pull(skb, nh + offset + 3 - skb->data))) अणु
				काष्ठा ip6_mh *mh;

				nh = skb_network_header(skb);
				mh = (काष्ठा ip6_mh *)(nh + offset);
				fl6->fl6_mh_type = mh->ip6mh_type;
			पूर्ण
			fl6->flowi6_proto = nexthdr;
			वापस;
#पूर्ण_अगर
		शेष:
			fl6->flowi6_proto = nexthdr;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक __xfrm_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl,
			  अचिन्हित पूर्णांक family, पूर्णांक reverse)
अणु
	चयन (family) अणु
	हाल AF_INET:
		decode_session4(skb, fl, reverse);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		decode_session6(skb, fl, reverse);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण

	वापस security_xfrm_decode_session(skb, &fl->flowi_secid);
पूर्ण
EXPORT_SYMBOL(__xfrm_decode_session);

अटल अंतरभूत पूर्णांक secpath_has_nontransport(स्थिर काष्ठा sec_path *sp, पूर्णांक k, पूर्णांक *idxp)
अणु
	क्रम (; k < sp->len; k++) अणु
		अगर (sp->xvec[k]->props.mode != XFRM_MODE_TRANSPORT) अणु
			*idxp = k;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __xfrm_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb,
			अचिन्हित लघु family)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा xfrm_policy *pol;
	काष्ठा xfrm_policy *pols[XFRM_POLICY_TYPE_MAX];
	पूर्णांक npols = 0;
	पूर्णांक xfrm_nr;
	पूर्णांक pi;
	पूर्णांक reverse;
	काष्ठा flowi fl;
	पूर्णांक xerr_idx = -1;
	स्थिर काष्ठा xfrm_अगर_cb *अगरcb;
	काष्ठा sec_path *sp;
	काष्ठा xfrm_अगर *xi;
	u32 अगर_id = 0;

	rcu_पढ़ो_lock();
	अगरcb = xfrm_अगर_get_cb();

	अगर (अगरcb) अणु
		xi = अगरcb->decode_session(skb, family);
		अगर (xi) अणु
			अगर_id = xi->p.अगर_id;
			net = xi->net;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	reverse = dir & ~XFRM_POLICY_MASK;
	dir &= XFRM_POLICY_MASK;

	अगर (__xfrm_decode_session(skb, &fl, family, reverse) < 0) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
		वापस 0;
	पूर्ण

	nf_nat_decode_session(skb, &fl, family);

	/* First, check used SA against their selectors. */
	sp = skb_sec_path(skb);
	अगर (sp) अणु
		पूर्णांक i;

		क्रम (i = sp->len - 1; i >= 0; i--) अणु
			काष्ठा xfrm_state *x = sp->xvec[i];
			अगर (!xfrm_selector_match(&x->sel, &fl, family)) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINSTATEMISMATCH);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	pol = शून्य;
	sk = sk_to_full_sk(sk);
	अगर (sk && sk->sk_policy[dir]) अणु
		pol = xfrm_sk_policy_lookup(sk, dir, &fl, family, अगर_id);
		अगर (IS_ERR(pol)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINPOLERROR);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!pol)
		pol = xfrm_policy_lookup(net, &fl, family, dir, अगर_id);

	अगर (IS_ERR(pol)) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINPOLERROR);
		वापस 0;
	पूर्ण

	अगर (!pol) अणु
		अगर (sp && secpath_has_nontransport(sp, 0, &xerr_idx)) अणु
			xfrm_secpath_reject(xerr_idx, skb, &fl);
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINNOPOLS);
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	pol->curlft.use_समय = kसमय_get_real_seconds();

	pols[0] = pol;
	npols++;
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	अगर (pols[0]->type != XFRM_POLICY_TYPE_MAIN) अणु
		pols[1] = xfrm_policy_lookup_bytype(net, XFRM_POLICY_TYPE_MAIN,
						    &fl, family,
						    XFRM_POLICY_IN, अगर_id);
		अगर (pols[1]) अणु
			अगर (IS_ERR(pols[1])) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINPOLERROR);
				वापस 0;
			पूर्ण
			pols[1]->curlft.use_समय = kसमय_get_real_seconds();
			npols++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (pol->action == XFRM_POLICY_ALLOW) अणु
		अटल काष्ठा sec_path dummy;
		काष्ठा xfrm_पंचांगpl *tp[XFRM_MAX_DEPTH];
		काष्ठा xfrm_पंचांगpl *stp[XFRM_MAX_DEPTH];
		काष्ठा xfrm_पंचांगpl **tpp = tp;
		पूर्णांक ti = 0;
		पूर्णांक i, k;

		sp = skb_sec_path(skb);
		अगर (!sp)
			sp = &dummy;

		क्रम (pi = 0; pi < npols; pi++) अणु
			अगर (pols[pi] != pol &&
			    pols[pi]->action != XFRM_POLICY_ALLOW) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINPOLBLOCK);
				जाओ reject;
			पूर्ण
			अगर (ti + pols[pi]->xfrm_nr >= XFRM_MAX_DEPTH) अणु
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINBUFFERERROR);
				जाओ reject_error;
			पूर्ण
			क्रम (i = 0; i < pols[pi]->xfrm_nr; i++)
				tpp[ti++] = &pols[pi]->xfrm_vec[i];
		पूर्ण
		xfrm_nr = ti;
		अगर (npols > 1) अणु
			xfrm_पंचांगpl_sort(stp, tpp, xfrm_nr, family);
			tpp = stp;
		पूर्ण

		/* For each tunnel xfrm, find the first matching पंचांगpl.
		 * For each पंचांगpl beक्रमe that, find corresponding xfrm.
		 * Order is _important_. Later we will implement
		 * some barriers, but at the moment barriers
		 * are implied between each two transक्रमmations.
		 */
		क्रम (i = xfrm_nr-1, k = 0; i >= 0; i--) अणु
			k = xfrm_policy_ok(tpp[i], sp, k, family);
			अगर (k < 0) अणु
				अगर (k < -1)
					/* "-2 - errored_index" वापसed */
					xerr_idx = -(2+k);
				XFRM_INC_STATS(net, LINUX_MIB_XFRMINTMPLMISMATCH);
				जाओ reject;
			पूर्ण
		पूर्ण

		अगर (secpath_has_nontransport(sp, k, &xerr_idx)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMINTMPLMISMATCH);
			जाओ reject;
		पूर्ण

		xfrm_pols_put(pols, npols);
		वापस 1;
	पूर्ण
	XFRM_INC_STATS(net, LINUX_MIB_XFRMINPOLBLOCK);

reject:
	xfrm_secpath_reject(xerr_idx, skb, &fl);
reject_error:
	xfrm_pols_put(pols, npols);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__xfrm_policy_check);

पूर्णांक __xfrm_route_क्रमward(काष्ठा sk_buff *skb, अचिन्हित लघु family)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा flowi fl;
	काष्ठा dst_entry *dst;
	पूर्णांक res = 1;

	अगर (xfrm_decode_session(skb, &fl, family) < 0) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMFWDHDRERROR);
		वापस 0;
	पूर्ण

	skb_dst_क्रमce(skb);
	अगर (!skb_dst(skb)) अणु
		XFRM_INC_STATS(net, LINUX_MIB_XFRMFWDHDRERROR);
		वापस 0;
	पूर्ण

	dst = xfrm_lookup(net, skb_dst(skb), &fl, शून्य, XFRM_LOOKUP_QUEUE);
	अगर (IS_ERR(dst)) अणु
		res = 0;
		dst = शून्य;
	पूर्ण
	skb_dst_set(skb, dst);
	वापस res;
पूर्ण
EXPORT_SYMBOL(__xfrm_route_क्रमward);

/* Optimize later using cookies and generation ids. */

अटल काष्ठा dst_entry *xfrm_dst_check(काष्ठा dst_entry *dst, u32 cookie)
अणु
	/* Code (such as __xfrm4_bundle_create()) sets dst->obsolete
	 * to DST_OBSOLETE_FORCE_CHK to क्रमce all XFRM destinations to
	 * get validated by dst_ops->check on every use.  We करो this
	 * because when a normal route referenced by an XFRM dst is
	 * obsoleted we करो not go looking around क्रम all parent
	 * referencing XFRM dsts so that we can invalidate them.  It
	 * is just too much work.  Instead we make the checks here on
	 * every use.  For example:
	 *
	 *	XFRM dst A --> IPv4 dst X
	 *
	 * X is the "xdst->route" of A (X is also the "dst->path" of A
	 * in this example).  If X is marked obsolete, "A" will not
	 * notice.  That's what we are validating here via the
	 * stale_bundle() check.
	 *
	 * When a dst is हटाओd from the fib tree, DST_OBSOLETE_DEAD will
	 * be marked on it.
	 * This will क्रमce stale_bundle() to fail on any xdst bundle with
	 * this dst linked in it.
	 */
	अगर (dst->obsolete < 0 && !stale_bundle(dst))
		वापस dst;

	वापस शून्य;
पूर्ण

अटल पूर्णांक stale_bundle(काष्ठा dst_entry *dst)
अणु
	वापस !xfrm_bundle_ok((काष्ठा xfrm_dst *)dst);
पूर्ण

व्योम xfrm_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev)
अणु
	जबतक ((dst = xfrm_dst_child(dst)) && dst->xfrm && dst->dev == dev) अणु
		dst->dev = dev_net(dev)->loopback_dev;
		dev_hold(dst->dev);
		dev_put(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xfrm_dst_अगरकरोwn);

अटल व्योम xfrm_link_failure(काष्ठा sk_buff *skb)
अणु
	/* Impossible. Such dst must be popped beक्रमe reaches poपूर्णांक of failure. */
पूर्ण

अटल काष्ठा dst_entry *xfrm_negative_advice(काष्ठा dst_entry *dst)
अणु
	अगर (dst) अणु
		अगर (dst->obsolete) अणु
			dst_release(dst);
			dst = शून्य;
		पूर्ण
	पूर्ण
	वापस dst;
पूर्ण

अटल व्योम xfrm_init_pmtu(काष्ठा xfrm_dst **bundle, पूर्णांक nr)
अणु
	जबतक (nr--) अणु
		काष्ठा xfrm_dst *xdst = bundle[nr];
		u32 pmtu, route_mtu_cached;
		काष्ठा dst_entry *dst;

		dst = &xdst->u.dst;
		pmtu = dst_mtu(xfrm_dst_child(dst));
		xdst->child_mtu_cached = pmtu;

		pmtu = xfrm_state_mtu(dst->xfrm, pmtu);

		route_mtu_cached = dst_mtu(xdst->route);
		xdst->route_mtu_cached = route_mtu_cached;

		अगर (pmtu > route_mtu_cached)
			pmtu = route_mtu_cached;

		dst_metric_set(dst, RTAX_MTU, pmtu);
	पूर्ण
पूर्ण

/* Check that the bundle accepts the flow and its components are
 * still valid.
 */

अटल पूर्णांक xfrm_bundle_ok(काष्ठा xfrm_dst *first)
अणु
	काष्ठा xfrm_dst *bundle[XFRM_MAX_DEPTH];
	काष्ठा dst_entry *dst = &first->u.dst;
	काष्ठा xfrm_dst *xdst;
	पूर्णांक start_from, nr;
	u32 mtu;

	अगर (!dst_check(xfrm_dst_path(dst), ((काष्ठा xfrm_dst *)dst)->path_cookie) ||
	    (dst->dev && !netअगर_running(dst->dev)))
		वापस 0;

	अगर (dst->flags & DST_XFRM_QUEUE)
		वापस 1;

	start_from = nr = 0;
	करो अणु
		काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;

		अगर (dst->xfrm->km.state != XFRM_STATE_VALID)
			वापस 0;
		अगर (xdst->xfrm_genid != dst->xfrm->genid)
			वापस 0;
		अगर (xdst->num_pols > 0 &&
		    xdst->policy_genid != atomic_पढ़ो(&xdst->pols[0]->genid))
			वापस 0;

		bundle[nr++] = xdst;

		mtu = dst_mtu(xfrm_dst_child(dst));
		अगर (xdst->child_mtu_cached != mtu) अणु
			start_from = nr;
			xdst->child_mtu_cached = mtu;
		पूर्ण

		अगर (!dst_check(xdst->route, xdst->route_cookie))
			वापस 0;
		mtu = dst_mtu(xdst->route);
		अगर (xdst->route_mtu_cached != mtu) अणु
			start_from = nr;
			xdst->route_mtu_cached = mtu;
		पूर्ण

		dst = xfrm_dst_child(dst);
	पूर्ण जबतक (dst->xfrm);

	अगर (likely(!start_from))
		वापस 1;

	xdst = bundle[start_from - 1];
	mtu = xdst->child_mtu_cached;
	जबतक (start_from--) अणु
		dst = &xdst->u.dst;

		mtu = xfrm_state_mtu(dst->xfrm, mtu);
		अगर (mtu > xdst->route_mtu_cached)
			mtu = xdst->route_mtu_cached;
		dst_metric_set(dst, RTAX_MTU, mtu);
		अगर (!start_from)
			अवरोध;

		xdst = bundle[start_from - 1];
		xdst->child_mtu_cached = mtu;
	पूर्ण

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक xfrm_शेष_advmss(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst_metric_advmss(xfrm_dst_path(dst));
पूर्ण

अटल अचिन्हित पूर्णांक xfrm_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	अचिन्हित पूर्णांक mtu = dst_metric_raw(dst, RTAX_MTU);

	वापस mtu ? : dst_mtu(xfrm_dst_path(dst));
पूर्ण

अटल स्थिर व्योम *xfrm_get_dst_nexthop(स्थिर काष्ठा dst_entry *dst,
					स्थिर व्योम *daddr)
अणु
	जबतक (dst->xfrm) अणु
		स्थिर काष्ठा xfrm_state *xfrm = dst->xfrm;

		dst = xfrm_dst_child(dst);

		अगर (xfrm->props.mode == XFRM_MODE_TRANSPORT)
			जारी;
		अगर (xfrm->type->flags & XFRM_TYPE_REMOTE_COADDR)
			daddr = xfrm->coaddr;
		अन्यथा अगर (!(xfrm->type->flags & XFRM_TYPE_LOCAL_COADDR))
			daddr = &xfrm->id.daddr;
	पूर्ण
	वापस daddr;
पूर्ण

अटल काष्ठा neighbour *xfrm_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					   काष्ठा sk_buff *skb,
					   स्थिर व्योम *daddr)
अणु
	स्थिर काष्ठा dst_entry *path = xfrm_dst_path(dst);

	अगर (!skb)
		daddr = xfrm_get_dst_nexthop(dst, daddr);
	वापस path->ops->neigh_lookup(path, skb, daddr);
पूर्ण

अटल व्योम xfrm_confirm_neigh(स्थिर काष्ठा dst_entry *dst, स्थिर व्योम *daddr)
अणु
	स्थिर काष्ठा dst_entry *path = xfrm_dst_path(dst);

	daddr = xfrm_get_dst_nexthop(dst, daddr);
	path->ops->confirm_neigh(path, daddr);
पूर्ण

पूर्णांक xfrm_policy_रेजिस्टर_afinfo(स्थिर काष्ठा xfrm_policy_afinfo *afinfo, पूर्णांक family)
अणु
	पूर्णांक err = 0;

	अगर (WARN_ON(family >= ARRAY_SIZE(xfrm_policy_afinfo)))
		वापस -EAFNOSUPPORT;

	spin_lock(&xfrm_policy_afinfo_lock);
	अगर (unlikely(xfrm_policy_afinfo[family] != शून्य))
		err = -EEXIST;
	अन्यथा अणु
		काष्ठा dst_ops *dst_ops = afinfo->dst_ops;
		अगर (likely(dst_ops->kmem_cachep == शून्य))
			dst_ops->kmem_cachep = xfrm_dst_cache;
		अगर (likely(dst_ops->check == शून्य))
			dst_ops->check = xfrm_dst_check;
		अगर (likely(dst_ops->शेष_advmss == शून्य))
			dst_ops->शेष_advmss = xfrm_शेष_advmss;
		अगर (likely(dst_ops->mtu == शून्य))
			dst_ops->mtu = xfrm_mtu;
		अगर (likely(dst_ops->negative_advice == शून्य))
			dst_ops->negative_advice = xfrm_negative_advice;
		अगर (likely(dst_ops->link_failure == शून्य))
			dst_ops->link_failure = xfrm_link_failure;
		अगर (likely(dst_ops->neigh_lookup == शून्य))
			dst_ops->neigh_lookup = xfrm_neigh_lookup;
		अगर (likely(!dst_ops->confirm_neigh))
			dst_ops->confirm_neigh = xfrm_confirm_neigh;
		rcu_assign_poपूर्णांकer(xfrm_policy_afinfo[family], afinfo);
	पूर्ण
	spin_unlock(&xfrm_policy_afinfo_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_रेजिस्टर_afinfo);

व्योम xfrm_policy_unरेजिस्टर_afinfo(स्थिर काष्ठा xfrm_policy_afinfo *afinfo)
अणु
	काष्ठा dst_ops *dst_ops = afinfo->dst_ops;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xfrm_policy_afinfo); i++) अणु
		अगर (xfrm_policy_afinfo[i] != afinfo)
			जारी;
		RCU_INIT_POINTER(xfrm_policy_afinfo[i], शून्य);
		अवरोध;
	पूर्ण

	synchronize_rcu();

	dst_ops->kmem_cachep = शून्य;
	dst_ops->check = शून्य;
	dst_ops->negative_advice = शून्य;
	dst_ops->link_failure = शून्य;
पूर्ण
EXPORT_SYMBOL(xfrm_policy_unरेजिस्टर_afinfo);

व्योम xfrm_अगर_रेजिस्टर_cb(स्थिर काष्ठा xfrm_अगर_cb *अगरcb)
अणु
	spin_lock(&xfrm_अगर_cb_lock);
	rcu_assign_poपूर्णांकer(xfrm_अगर_cb, अगरcb);
	spin_unlock(&xfrm_अगर_cb_lock);
पूर्ण
EXPORT_SYMBOL(xfrm_अगर_रेजिस्टर_cb);

व्योम xfrm_अगर_unरेजिस्टर_cb(व्योम)
अणु
	RCU_INIT_POINTER(xfrm_अगर_cb, शून्य);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(xfrm_अगर_unरेजिस्टर_cb);

#अगर_घोषित CONFIG_XFRM_STATISTICS
अटल पूर्णांक __net_init xfrm_statistics_init(काष्ठा net *net)
अणु
	पूर्णांक rv;
	net->mib.xfrm_statistics = alloc_percpu(काष्ठा linux_xfrm_mib);
	अगर (!net->mib.xfrm_statistics)
		वापस -ENOMEM;
	rv = xfrm_proc_init(net);
	अगर (rv < 0)
		मुक्त_percpu(net->mib.xfrm_statistics);
	वापस rv;
पूर्ण

अटल व्योम xfrm_statistics_fini(काष्ठा net *net)
अणु
	xfrm_proc_fini(net);
	मुक्त_percpu(net->mib.xfrm_statistics);
पूर्ण
#अन्यथा
अटल पूर्णांक __net_init xfrm_statistics_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम xfrm_statistics_fini(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init xfrm_policy_init(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक hmask, sz;
	पूर्णांक dir, err;

	अगर (net_eq(net, &init_net)) अणु
		xfrm_dst_cache = kmem_cache_create("xfrm_dst_cache",
					   माप(काष्ठा xfrm_dst),
					   0, SLAB_HWCACHE_ALIGN|SLAB_PANIC,
					   शून्य);
		err = rhashtable_init(&xfrm_policy_inexact_table,
				      &xfrm_pol_inexact_params);
		BUG_ON(err);
	पूर्ण

	hmask = 8 - 1;
	sz = (hmask+1) * माप(काष्ठा hlist_head);

	net->xfrm.policy_byidx = xfrm_hash_alloc(sz);
	अगर (!net->xfrm.policy_byidx)
		जाओ out_byidx;
	net->xfrm.policy_idx_hmask = hmask;

	क्रम (dir = 0; dir < XFRM_POLICY_MAX; dir++) अणु
		काष्ठा xfrm_policy_hash *htab;

		net->xfrm.policy_count[dir] = 0;
		net->xfrm.policy_count[XFRM_POLICY_MAX + dir] = 0;
		INIT_HLIST_HEAD(&net->xfrm.policy_inexact[dir]);

		htab = &net->xfrm.policy_bydst[dir];
		htab->table = xfrm_hash_alloc(sz);
		अगर (!htab->table)
			जाओ out_bydst;
		htab->hmask = hmask;
		htab->dbits4 = 32;
		htab->sbits4 = 32;
		htab->dbits6 = 128;
		htab->sbits6 = 128;
	पूर्ण
	net->xfrm.policy_hthresh.lbits4 = 32;
	net->xfrm.policy_hthresh.rbits4 = 32;
	net->xfrm.policy_hthresh.lbits6 = 128;
	net->xfrm.policy_hthresh.rbits6 = 128;

	seqlock_init(&net->xfrm.policy_hthresh.lock);

	INIT_LIST_HEAD(&net->xfrm.policy_all);
	INIT_LIST_HEAD(&net->xfrm.inexact_bins);
	INIT_WORK(&net->xfrm.policy_hash_work, xfrm_hash_resize);
	INIT_WORK(&net->xfrm.policy_hthresh.work, xfrm_hash_rebuild);
	वापस 0;

out_bydst:
	क्रम (dir--; dir >= 0; dir--) अणु
		काष्ठा xfrm_policy_hash *htab;

		htab = &net->xfrm.policy_bydst[dir];
		xfrm_hash_मुक्त(htab->table, sz);
	पूर्ण
	xfrm_hash_मुक्त(net->xfrm.policy_byidx, sz);
out_byidx:
	वापस -ENOMEM;
पूर्ण

अटल व्योम xfrm_policy_fini(काष्ठा net *net)
अणु
	काष्ठा xfrm_pol_inexact_bin *b, *t;
	अचिन्हित पूर्णांक sz;
	पूर्णांक dir;

	flush_work(&net->xfrm.policy_hash_work);
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	xfrm_policy_flush(net, XFRM_POLICY_TYPE_SUB, false);
#पूर्ण_अगर
	xfrm_policy_flush(net, XFRM_POLICY_TYPE_MAIN, false);

	WARN_ON(!list_empty(&net->xfrm.policy_all));

	क्रम (dir = 0; dir < XFRM_POLICY_MAX; dir++) अणु
		काष्ठा xfrm_policy_hash *htab;

		WARN_ON(!hlist_empty(&net->xfrm.policy_inexact[dir]));

		htab = &net->xfrm.policy_bydst[dir];
		sz = (htab->hmask + 1) * माप(काष्ठा hlist_head);
		WARN_ON(!hlist_empty(htab->table));
		xfrm_hash_मुक्त(htab->table, sz);
	पूर्ण

	sz = (net->xfrm.policy_idx_hmask + 1) * माप(काष्ठा hlist_head);
	WARN_ON(!hlist_empty(net->xfrm.policy_byidx));
	xfrm_hash_मुक्त(net->xfrm.policy_byidx, sz);

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	list_क्रम_each_entry_safe(b, t, &net->xfrm.inexact_bins, inexact_bins)
		__xfrm_policy_inexact_prune_bin(b, true);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
पूर्ण

अटल पूर्णांक __net_init xfrm_net_init(काष्ठा net *net)
अणु
	पूर्णांक rv;

	/* Initialize the per-net locks here */
	spin_lock_init(&net->xfrm.xfrm_state_lock);
	spin_lock_init(&net->xfrm.xfrm_policy_lock);
	mutex_init(&net->xfrm.xfrm_cfg_mutex);

	rv = xfrm_statistics_init(net);
	अगर (rv < 0)
		जाओ out_statistics;
	rv = xfrm_state_init(net);
	अगर (rv < 0)
		जाओ out_state;
	rv = xfrm_policy_init(net);
	अगर (rv < 0)
		जाओ out_policy;
	rv = xfrm_sysctl_init(net);
	अगर (rv < 0)
		जाओ out_sysctl;

	वापस 0;

out_sysctl:
	xfrm_policy_fini(net);
out_policy:
	xfrm_state_fini(net);
out_state:
	xfrm_statistics_fini(net);
out_statistics:
	वापस rv;
पूर्ण

अटल व्योम __net_निकास xfrm_net_निकास(काष्ठा net *net)
अणु
	xfrm_sysctl_fini(net);
	xfrm_policy_fini(net);
	xfrm_state_fini(net);
	xfrm_statistics_fini(net);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata xfrm_net_ops = अणु
	.init = xfrm_net_init,
	.निकास = xfrm_net_निकास,
पूर्ण;

व्योम __init xfrm_init(व्योम)
अणु
	रेजिस्टर_pernet_subsys(&xfrm_net_ops);
	xfrm_dev_init();
	seqcount_mutex_init(&xfrm_policy_hash_generation, &hash_resize_mutex);
	xfrm_input_init();

#अगर_घोषित CONFIG_XFRM_ESPINTCP
	espपूर्णांकcp_init();
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_AUDITSYSCALL
अटल व्योम xfrm_audit_common_policyinfo(काष्ठा xfrm_policy *xp,
					 काष्ठा audit_buffer *audit_buf)
अणु
	काष्ठा xfrm_sec_ctx *ctx = xp->security;
	काष्ठा xfrm_selector *sel = &xp->selector;

	अगर (ctx)
		audit_log_क्रमmat(audit_buf, " sec_alg=%u sec_doi=%u sec_obj=%s",
				 ctx->ctx_alg, ctx->ctx_करोi, ctx->ctx_str);

	चयन (sel->family) अणु
	हाल AF_INET:
		audit_log_क्रमmat(audit_buf, " src=%pI4", &sel->saddr.a4);
		अगर (sel->prefixlen_s != 32)
			audit_log_क्रमmat(audit_buf, " src_prefixlen=%d",
					 sel->prefixlen_s);
		audit_log_क्रमmat(audit_buf, " dst=%pI4", &sel->daddr.a4);
		अगर (sel->prefixlen_d != 32)
			audit_log_क्रमmat(audit_buf, " dst_prefixlen=%d",
					 sel->prefixlen_d);
		अवरोध;
	हाल AF_INET6:
		audit_log_क्रमmat(audit_buf, " src=%pI6", sel->saddr.a6);
		अगर (sel->prefixlen_s != 128)
			audit_log_क्रमmat(audit_buf, " src_prefixlen=%d",
					 sel->prefixlen_s);
		audit_log_क्रमmat(audit_buf, " dst=%pI6", sel->daddr.a6);
		अगर (sel->prefixlen_d != 128)
			audit_log_क्रमmat(audit_buf, " dst_prefixlen=%d",
					 sel->prefixlen_d);
		अवरोध;
	पूर्ण
पूर्ण

व्योम xfrm_audit_policy_add(काष्ठा xfrm_policy *xp, पूर्णांक result, bool task_valid)
अणु
	काष्ठा audit_buffer *audit_buf;

	audit_buf = xfrm_audit_start("SPD-add");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_usrinfo(task_valid, audit_buf);
	audit_log_क्रमmat(audit_buf, " res=%u", result);
	xfrm_audit_common_policyinfo(xp, audit_buf);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_policy_add);

व्योम xfrm_audit_policy_delete(काष्ठा xfrm_policy *xp, पूर्णांक result,
			      bool task_valid)
अणु
	काष्ठा audit_buffer *audit_buf;

	audit_buf = xfrm_audit_start("SPD-delete");
	अगर (audit_buf == शून्य)
		वापस;
	xfrm_audit_helper_usrinfo(task_valid, audit_buf);
	audit_log_क्रमmat(audit_buf, " res=%u", result);
	xfrm_audit_common_policyinfo(xp, audit_buf);
	audit_log_end(audit_buf);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_audit_policy_delete);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM_MIGRATE
अटल bool xfrm_migrate_selector_match(स्थिर काष्ठा xfrm_selector *sel_cmp,
					स्थिर काष्ठा xfrm_selector *sel_tgt)
अणु
	अगर (sel_cmp->proto == IPSEC_ULPROTO_ANY) अणु
		अगर (sel_tgt->family == sel_cmp->family &&
		    xfrm_addr_equal(&sel_tgt->daddr, &sel_cmp->daddr,
				    sel_cmp->family) &&
		    xfrm_addr_equal(&sel_tgt->saddr, &sel_cmp->saddr,
				    sel_cmp->family) &&
		    sel_tgt->prefixlen_d == sel_cmp->prefixlen_d &&
		    sel_tgt->prefixlen_s == sel_cmp->prefixlen_s) अणु
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (स_भेद(sel_tgt, sel_cmp, माप(*sel_tgt)) == 0) अणु
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_migrate_policy_find(स्थिर काष्ठा xfrm_selector *sel,
						    u8 dir, u8 type, काष्ठा net *net)
अणु
	काष्ठा xfrm_policy *pol, *ret = शून्य;
	काष्ठा hlist_head *chain;
	u32 priority = ~0U;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	chain = policy_hash_direct(net, &sel->daddr, &sel->saddr, sel->family, dir);
	hlist_क्रम_each_entry(pol, chain, bydst) अणु
		अगर (xfrm_migrate_selector_match(sel, &pol->selector) &&
		    pol->type == type) अणु
			ret = pol;
			priority = ret->priority;
			अवरोध;
		पूर्ण
	पूर्ण
	chain = &net->xfrm.policy_inexact[dir];
	hlist_क्रम_each_entry(pol, chain, bydst_inexact_list) अणु
		अगर ((pol->priority >= priority) && ret)
			अवरोध;

		अगर (xfrm_migrate_selector_match(sel, &pol->selector) &&
		    pol->type == type) अणु
			ret = pol;
			अवरोध;
		पूर्ण
	पूर्ण

	xfrm_pol_hold(ret);

	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक migrate_पंचांगpl_match(स्थिर काष्ठा xfrm_migrate *m, स्थिर काष्ठा xfrm_पंचांगpl *t)
अणु
	पूर्णांक match = 0;

	अगर (t->mode == m->mode && t->id.proto == m->proto &&
	    (m->reqid == 0 || t->reqid == m->reqid)) अणु
		चयन (t->mode) अणु
		हाल XFRM_MODE_TUNNEL:
		हाल XFRM_MODE_BEET:
			अगर (xfrm_addr_equal(&t->id.daddr, &m->old_daddr,
					    m->old_family) &&
			    xfrm_addr_equal(&t->saddr, &m->old_saddr,
					    m->old_family)) अणु
				match = 1;
			पूर्ण
			अवरोध;
		हाल XFRM_MODE_TRANSPORT:
			/* in हाल of transport mode, ढाँचा करोes not store
			   any IP addresses, hence we just compare mode and
			   protocol */
			match = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस match;
पूर्ण

/* update endpoपूर्णांक address(es) of ढाँचा(s) */
अटल पूर्णांक xfrm_policy_migrate(काष्ठा xfrm_policy *pol,
			       काष्ठा xfrm_migrate *m, पूर्णांक num_migrate)
अणु
	काष्ठा xfrm_migrate *mp;
	पूर्णांक i, j, n = 0;

	ग_लिखो_lock_bh(&pol->lock);
	अगर (unlikely(pol->walk.dead)) अणु
		/* target policy has been deleted */
		ग_लिखो_unlock_bh(&pol->lock);
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < pol->xfrm_nr; i++) अणु
		क्रम (j = 0, mp = m; j < num_migrate; j++, mp++) अणु
			अगर (!migrate_पंचांगpl_match(mp, &pol->xfrm_vec[i]))
				जारी;
			n++;
			अगर (pol->xfrm_vec[i].mode != XFRM_MODE_TUNNEL &&
			    pol->xfrm_vec[i].mode != XFRM_MODE_BEET)
				जारी;
			/* update endpoपूर्णांकs */
			स_नकल(&pol->xfrm_vec[i].id.daddr, &mp->new_daddr,
			       माप(pol->xfrm_vec[i].id.daddr));
			स_नकल(&pol->xfrm_vec[i].saddr, &mp->new_saddr,
			       माप(pol->xfrm_vec[i].saddr));
			pol->xfrm_vec[i].encap_family = mp->new_family;
			/* flush bundles */
			atomic_inc(&pol->genid);
		पूर्ण
	पूर्ण

	ग_लिखो_unlock_bh(&pol->lock);

	अगर (!n)
		वापस -ENODATA;

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_migrate_check(स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_migrate)
अणु
	पूर्णांक i, j;

	अगर (num_migrate < 1 || num_migrate > XFRM_MAX_DEPTH)
		वापस -EINVAL;

	क्रम (i = 0; i < num_migrate; i++) अणु
		अगर (xfrm_addr_any(&m[i].new_daddr, m[i].new_family) ||
		    xfrm_addr_any(&m[i].new_saddr, m[i].new_family))
			वापस -EINVAL;

		/* check अगर there is any duplicated entry */
		क्रम (j = i + 1; j < num_migrate; j++) अणु
			अगर (!स_भेद(&m[i].old_daddr, &m[j].old_daddr,
				    माप(m[i].old_daddr)) &&
			    !स_भेद(&m[i].old_saddr, &m[j].old_saddr,
				    माप(m[i].old_saddr)) &&
			    m[i].proto == m[j].proto &&
			    m[i].mode == m[j].mode &&
			    m[i].reqid == m[j].reqid &&
			    m[i].old_family == m[j].old_family)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xfrm_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
		 काष्ठा xfrm_migrate *m, पूर्णांक num_migrate,
		 काष्ठा xfrm_kmaddress *k, काष्ठा net *net,
		 काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	पूर्णांक i, err, nx_cur = 0, nx_new = 0;
	काष्ठा xfrm_policy *pol = शून्य;
	काष्ठा xfrm_state *x, *xc;
	काष्ठा xfrm_state *x_cur[XFRM_MAX_DEPTH];
	काष्ठा xfrm_state *x_new[XFRM_MAX_DEPTH];
	काष्ठा xfrm_migrate *mp;

	/* Stage 0 - sanity checks */
	अगर ((err = xfrm_migrate_check(m, num_migrate)) < 0)
		जाओ out;

	अगर (dir >= XFRM_POLICY_MAX) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Stage 1 - find policy */
	अगर ((pol = xfrm_migrate_policy_find(sel, dir, type, net)) == शून्य) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	/* Stage 2 - find and update state(s) */
	क्रम (i = 0, mp = m; i < num_migrate; i++, mp++) अणु
		अगर ((x = xfrm_migrate_state_find(mp, net))) अणु
			x_cur[nx_cur] = x;
			nx_cur++;
			xc = xfrm_state_migrate(x, mp, encap);
			अगर (xc) अणु
				x_new[nx_new] = xc;
				nx_new++;
			पूर्ण अन्यथा अणु
				err = -ENODATA;
				जाओ restore_state;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Stage 3 - update policy */
	अगर ((err = xfrm_policy_migrate(pol, m, num_migrate)) < 0)
		जाओ restore_state;

	/* Stage 4 - delete old state(s) */
	अगर (nx_cur) अणु
		xfrm_states_put(x_cur, nx_cur);
		xfrm_states_delete(x_cur, nx_cur);
	पूर्ण

	/* Stage 5 - announce */
	km_migrate(sel, dir, type, m, num_migrate, k, encap);

	xfrm_pol_put(pol);

	वापस 0;
out:
	वापस err;

restore_state:
	अगर (pol)
		xfrm_pol_put(pol);
	अगर (nx_cur)
		xfrm_states_put(x_cur, nx_cur);
	अगर (nx_new)
		xfrm_states_delete(x_new, nx_new);

	वापस err;
पूर्ण
EXPORT_SYMBOL(xfrm_migrate);
#पूर्ण_अगर
