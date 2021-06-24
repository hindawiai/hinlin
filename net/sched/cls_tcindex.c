<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/cls_tcindex.c	Packet classअगरier क्रम skb->tc_index
 *
 * Written 1998,1999 by Werner Almesberger, EPFL ICA
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>
#समावेश <net/act_api.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sch_generic.h>

/*
 * Passing parameters to the root seems to be करोne more awkwardly than really
 * necessary. At least, u32 करोesn't seem to use such dirty hacks. To be
 * verअगरied. FIXME.
 */

#घोषणा PERFECT_HASH_THRESHOLD	64	/* use perfect hash अगर not bigger */
#घोषणा DEFAULT_HASH_SIZE	64	/* optimized क्रम dअगरfserv */


काष्ठा tcindex_data;

काष्ठा tcindex_filter_result अणु
	काष्ठा tcf_exts		exts;
	काष्ठा tcf_result	res;
	काष्ठा tcindex_data	*p;
	काष्ठा rcu_work		rwork;
पूर्ण;

काष्ठा tcindex_filter अणु
	u16 key;
	काष्ठा tcindex_filter_result result;
	काष्ठा tcindex_filter __rcu *next;
	काष्ठा rcu_work rwork;
पूर्ण;


काष्ठा tcindex_data अणु
	काष्ठा tcindex_filter_result *perfect; /* perfect hash; शून्य अगर none */
	काष्ठा tcindex_filter __rcu **h; /* imperfect hash; */
	काष्ठा tcf_proto *tp;
	u16 mask;		/* AND key with mask */
	u32 shअगरt;		/* shअगरt ANDed key to the right */
	u32 hash;		/* hash table size; 0 अगर undefined */
	u32 alloc_hash;		/* allocated size */
	u32 fall_through;	/* 0: only classअगरy अगर explicit match */
	refcount_t refcnt;	/* a temporary refcnt क्रम perfect hash */
	काष्ठा rcu_work rwork;
पूर्ण;

अटल अंतरभूत पूर्णांक tcindex_filter_is_set(काष्ठा tcindex_filter_result *r)
अणु
	वापस tcf_exts_has_actions(&r->exts) || r->res.classid;
पूर्ण

अटल व्योम tcindex_data_get(काष्ठा tcindex_data *p)
अणु
	refcount_inc(&p->refcnt);
पूर्ण

अटल व्योम tcindex_data_put(काष्ठा tcindex_data *p)
अणु
	अगर (refcount_dec_and_test(&p->refcnt)) अणु
		kमुक्त(p->perfect);
		kमुक्त(p->h);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल काष्ठा tcindex_filter_result *tcindex_lookup(काष्ठा tcindex_data *p,
						    u16 key)
अणु
	अगर (p->perfect) अणु
		काष्ठा tcindex_filter_result *f = p->perfect + key;

		वापस tcindex_filter_is_set(f) ? f : शून्य;
	पूर्ण अन्यथा अगर (p->h) अणु
		काष्ठा tcindex_filter __rcu **fp;
		काष्ठा tcindex_filter *f;

		fp = &p->h[key % p->hash];
		क्रम (f = rcu_dereference_bh_rtnl(*fp);
		     f;
		     fp = &f->next, f = rcu_dereference_bh_rtnl(*fp))
			अगर (f->key == key)
				वापस &f->result;
	पूर्ण

	वापस शून्य;
पूर्ण


अटल पूर्णांक tcindex_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			    काष्ठा tcf_result *res)
अणु
	काष्ठा tcindex_data *p = rcu_dereference_bh(tp->root);
	काष्ठा tcindex_filter_result *f;
	पूर्णांक key = (skb->tc_index & p->mask) >> p->shअगरt;

	pr_debug("tcindex_classify(skb %p,tp %p,res %p),p %p\n",
		 skb, tp, res, p);

	f = tcindex_lookup(p, key);
	अगर (!f) अणु
		काष्ठा Qdisc *q = tcf_block_q(tp->chain->block);

		अगर (!p->fall_through)
			वापस -1;
		res->classid = TC_H_MAKE(TC_H_MAJ(q->handle), key);
		res->class = 0;
		pr_debug("alg 0x%x\n", res->classid);
		वापस 0;
	पूर्ण
	*res = f->res;
	pr_debug("map 0x%x\n", res->classid);

	वापस tcf_exts_exec(skb, &f->exts, res);
पूर्ण


अटल व्योम *tcindex_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	काष्ठा tcindex_filter_result *r;

	pr_debug("tcindex_get(tp %p,handle 0x%08x)\n", tp, handle);
	अगर (p->perfect && handle >= p->alloc_hash)
		वापस शून्य;
	r = tcindex_lookup(p, handle);
	वापस r && tcindex_filter_is_set(r) ? r : शून्य;
पूर्ण

अटल पूर्णांक tcindex_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcindex_data *p;

	pr_debug("tcindex_init(tp %p)\n", tp);
	p = kzalloc(माप(काष्ठा tcindex_data), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->mask = 0xffff;
	p->hash = DEFAULT_HASH_SIZE;
	p->fall_through = 1;
	refcount_set(&p->refcnt, 1); /* Paired with tcindex_destroy_work() */

	rcu_assign_poपूर्णांकer(tp->root, p);
	वापस 0;
पूर्ण

अटल व्योम __tcindex_destroy_rexts(काष्ठा tcindex_filter_result *r)
अणु
	tcf_exts_destroy(&r->exts);
	tcf_exts_put_net(&r->exts);
	tcindex_data_put(r->p);
पूर्ण

अटल व्योम tcindex_destroy_rexts_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tcindex_filter_result *r;

	r = container_of(to_rcu_work(work),
			 काष्ठा tcindex_filter_result,
			 rwork);
	rtnl_lock();
	__tcindex_destroy_rexts(r);
	rtnl_unlock();
पूर्ण

अटल व्योम __tcindex_destroy_fexts(काष्ठा tcindex_filter *f)
अणु
	tcf_exts_destroy(&f->result.exts);
	tcf_exts_put_net(&f->result.exts);
	kमुक्त(f);
पूर्ण

अटल व्योम tcindex_destroy_fexts_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tcindex_filter *f = container_of(to_rcu_work(work),
						काष्ठा tcindex_filter,
						rwork);

	rtnl_lock();
	__tcindex_destroy_fexts(f);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक tcindex_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
			  bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	काष्ठा tcindex_filter_result *r = arg;
	काष्ठा tcindex_filter __rcu **walk;
	काष्ठा tcindex_filter *f = शून्य;

	pr_debug("tcindex_delete(tp %p,arg %p),p %p\n", tp, arg, p);
	अगर (p->perfect) अणु
		अगर (!r->res.class)
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < p->hash; i++) अणु
			walk = p->h + i;
			क्रम (f = rtnl_dereference(*walk); f;
			     walk = &f->next, f = rtnl_dereference(*walk)) अणु
				अगर (&f->result == r)
					जाओ found;
			पूर्ण
		पूर्ण
		वापस -ENOENT;

found:
		rcu_assign_poपूर्णांकer(*walk, rtnl_dereference(f->next));
	पूर्ण
	tcf_unbind_filter(tp, &r->res);
	/* all classअगरiers are required to call tcf_exts_destroy() after rcu
	 * grace period, since converted-to-rcu actions are relying on that
	 * in cleanup() callback
	 */
	अगर (f) अणु
		अगर (tcf_exts_get_net(&f->result.exts))
			tcf_queue_work(&f->rwork, tcindex_destroy_fexts_work);
		अन्यथा
			__tcindex_destroy_fexts(f);
	पूर्ण अन्यथा अणु
		tcindex_data_get(p);

		अगर (tcf_exts_get_net(&r->exts))
			tcf_queue_work(&r->rwork, tcindex_destroy_rexts_work);
		अन्यथा
			__tcindex_destroy_rexts(r);
	पूर्ण

	*last = false;
	वापस 0;
पूर्ण

अटल व्योम tcindex_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tcindex_data *p = container_of(to_rcu_work(work),
					      काष्ठा tcindex_data,
					      rwork);

	tcindex_data_put(p);
पूर्ण

अटल अंतरभूत पूर्णांक
valid_perfect_hash(काष्ठा tcindex_data *p)
अणु
	वापस  p->hash > (p->mask >> p->shअगरt);
पूर्ण

अटल स्थिर काष्ठा nla_policy tcindex_policy[TCA_TCINDEX_MAX + 1] = अणु
	[TCA_TCINDEX_HASH]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_TCINDEX_MASK]		= अणु .type = NLA_U16 पूर्ण,
	[TCA_TCINDEX_SHIFT]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_TCINDEX_FALL_THROUGH]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_TCINDEX_CLASSID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक tcindex_filter_result_init(काष्ठा tcindex_filter_result *r,
				      काष्ठा tcindex_data *p,
				      काष्ठा net *net)
अणु
	स_रखो(r, 0, माप(*r));
	r->p = p;
	वापस tcf_exts_init(&r->exts, net, TCA_TCINDEX_ACT,
			     TCA_TCINDEX_POLICE);
पूर्ण

अटल व्योम tcindex_partial_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tcindex_data *p = container_of(to_rcu_work(work),
					      काष्ठा tcindex_data,
					      rwork);

	rtnl_lock();
	kमुक्त(p->perfect);
	kमुक्त(p);
	rtnl_unlock();
पूर्ण

अटल व्योम tcindex_मुक्त_perfect_hash(काष्ठा tcindex_data *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cp->hash; i++)
		tcf_exts_destroy(&cp->perfect[i].exts);
	kमुक्त(cp->perfect);
पूर्ण

अटल पूर्णांक tcindex_alloc_perfect_hash(काष्ठा net *net, काष्ठा tcindex_data *cp)
अणु
	पूर्णांक i, err = 0;

	cp->perfect = kसुस्मृति(cp->hash, माप(काष्ठा tcindex_filter_result),
			      GFP_KERNEL);
	अगर (!cp->perfect)
		वापस -ENOMEM;

	क्रम (i = 0; i < cp->hash; i++) अणु
		err = tcf_exts_init(&cp->perfect[i].exts, net,
				    TCA_TCINDEX_ACT, TCA_TCINDEX_POLICE);
		अगर (err < 0)
			जाओ errout;
		cp->perfect[i].p = cp;
	पूर्ण

	वापस 0;

errout:
	tcindex_मुक्त_perfect_hash(cp);
	वापस err;
पूर्ण

अटल पूर्णांक
tcindex_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		  u32 handle, काष्ठा tcindex_data *p,
		  काष्ठा tcindex_filter_result *r, काष्ठा nlattr **tb,
		  काष्ठा nlattr *est, bool ovr, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcindex_filter_result new_filter_result, *old_r = r;
	काष्ठा tcindex_data *cp = शून्य, *oldp;
	काष्ठा tcindex_filter *f = शून्य; /* make gcc behave */
	काष्ठा tcf_result cr = अणुपूर्ण;
	पूर्णांक err, balloc = 0;
	काष्ठा tcf_exts e;

	err = tcf_exts_init(&e, net, TCA_TCINDEX_ACT, TCA_TCINDEX_POLICE);
	अगर (err < 0)
		वापस err;
	err = tcf_exts_validate(net, tp, tb, est, &e, ovr, true, extack);
	अगर (err < 0)
		जाओ errout;

	err = -ENOMEM;
	/* tcindex_data attributes must look atomic to classअगरier/lookup so
	 * allocate new tcindex data and RCU assign it onto root. Keeping
	 * perfect hash and hash poपूर्णांकers from old data.
	 */
	cp = kzalloc(माप(*cp), GFP_KERNEL);
	अगर (!cp)
		जाओ errout;

	cp->mask = p->mask;
	cp->shअगरt = p->shअगरt;
	cp->hash = p->hash;
	cp->alloc_hash = p->alloc_hash;
	cp->fall_through = p->fall_through;
	cp->tp = tp;
	refcount_set(&cp->refcnt, 1); /* Paired with tcindex_destroy_work() */

	अगर (tb[TCA_TCINDEX_HASH])
		cp->hash = nla_get_u32(tb[TCA_TCINDEX_HASH]);

	अगर (tb[TCA_TCINDEX_MASK])
		cp->mask = nla_get_u16(tb[TCA_TCINDEX_MASK]);

	अगर (tb[TCA_TCINDEX_SHIFT]) अणु
		cp->shअगरt = nla_get_u32(tb[TCA_TCINDEX_SHIFT]);
		अगर (cp->shअगरt > 16) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण
	पूर्ण
	अगर (!cp->hash) अणु
		/* Hash not specअगरied, use perfect hash अगर the upper limit
		 * of the hashing index is below the threshold.
		 */
		अगर ((cp->mask >> cp->shअगरt) < PERFECT_HASH_THRESHOLD)
			cp->hash = (cp->mask >> cp->shअगरt) + 1;
		अन्यथा
			cp->hash = DEFAULT_HASH_SIZE;
	पूर्ण

	अगर (p->perfect) अणु
		पूर्णांक i;

		अगर (tcindex_alloc_perfect_hash(net, cp) < 0)
			जाओ errout;
		cp->alloc_hash = cp->hash;
		क्रम (i = 0; i < min(cp->hash, p->hash); i++)
			cp->perfect[i].res = p->perfect[i].res;
		balloc = 1;
	पूर्ण
	cp->h = p->h;

	err = tcindex_filter_result_init(&new_filter_result, cp, net);
	अगर (err < 0)
		जाओ errout_alloc;
	अगर (old_r)
		cr = r->res;

	err = -EBUSY;

	/* Hash alपढ़ोy allocated, make sure that we still meet the
	 * requirements क्रम the allocated hash.
	 */
	अगर (cp->perfect) अणु
		अगर (!valid_perfect_hash(cp) ||
		    cp->hash > cp->alloc_hash)
			जाओ errout_alloc;
	पूर्ण अन्यथा अगर (cp->h && cp->hash != cp->alloc_hash) अणु
		जाओ errout_alloc;
	पूर्ण

	err = -EINVAL;
	अगर (tb[TCA_TCINDEX_FALL_THROUGH])
		cp->fall_through = nla_get_u32(tb[TCA_TCINDEX_FALL_THROUGH]);

	अगर (!cp->perfect && !cp->h)
		cp->alloc_hash = cp->hash;

	/* Note: this could be as restrictive as अगर (handle & ~(mask >> shअगरt))
	 * but then, we'd fail handles that may become valid after some future
	 * mask change. While this is extremely unlikely to ever matter,
	 * the check below is safer (and also more backwards-compatible).
	 */
	अगर (cp->perfect || valid_perfect_hash(cp))
		अगर (handle >= cp->alloc_hash)
			जाओ errout_alloc;


	err = -ENOMEM;
	अगर (!cp->perfect && !cp->h) अणु
		अगर (valid_perfect_hash(cp)) अणु
			अगर (tcindex_alloc_perfect_hash(net, cp) < 0)
				जाओ errout_alloc;
			balloc = 1;
		पूर्ण अन्यथा अणु
			काष्ठा tcindex_filter __rcu **hash;

			hash = kसुस्मृति(cp->hash,
				       माप(काष्ठा tcindex_filter *),
				       GFP_KERNEL);

			अगर (!hash)
				जाओ errout_alloc;

			cp->h = hash;
			balloc = 2;
		पूर्ण
	पूर्ण

	अगर (cp->perfect)
		r = cp->perfect + handle;
	अन्यथा
		r = tcindex_lookup(cp, handle) ? : &new_filter_result;

	अगर (r == &new_filter_result) अणु
		f = kzalloc(माप(*f), GFP_KERNEL);
		अगर (!f)
			जाओ errout_alloc;
		f->key = handle;
		f->next = शून्य;
		err = tcindex_filter_result_init(&f->result, cp, net);
		अगर (err < 0) अणु
			kमुक्त(f);
			जाओ errout_alloc;
		पूर्ण
	पूर्ण

	अगर (tb[TCA_TCINDEX_CLASSID]) अणु
		cr.classid = nla_get_u32(tb[TCA_TCINDEX_CLASSID]);
		tcf_bind_filter(tp, &cr, base);
	पूर्ण

	अगर (old_r && old_r != r) अणु
		err = tcindex_filter_result_init(old_r, cp, net);
		अगर (err < 0) अणु
			kमुक्त(f);
			जाओ errout_alloc;
		पूर्ण
	पूर्ण

	oldp = p;
	r->res = cr;
	tcf_exts_change(&r->exts, &e);

	rcu_assign_poपूर्णांकer(tp->root, cp);

	अगर (r == &new_filter_result) अणु
		काष्ठा tcindex_filter *nfp;
		काष्ठा tcindex_filter __rcu **fp;

		f->result.res = r->res;
		tcf_exts_change(&f->result.exts, &r->exts);

		fp = cp->h + (handle % cp->hash);
		क्रम (nfp = rtnl_dereference(*fp);
		     nfp;
		     fp = &nfp->next, nfp = rtnl_dereference(*fp))
				; /* nothing */

		rcu_assign_poपूर्णांकer(*fp, f);
	पूर्ण अन्यथा अणु
		tcf_exts_destroy(&new_filter_result.exts);
	पूर्ण

	अगर (oldp)
		tcf_queue_work(&oldp->rwork, tcindex_partial_destroy_work);
	वापस 0;

errout_alloc:
	अगर (balloc == 1)
		tcindex_मुक्त_perfect_hash(cp);
	अन्यथा अगर (balloc == 2)
		kमुक्त(cp->h);
	tcf_exts_destroy(&new_filter_result.exts);
errout:
	kमुक्त(cp);
	tcf_exts_destroy(&e);
	वापस err;
पूर्ण

अटल पूर्णांक
tcindex_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
	       काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base, u32 handle,
	       काष्ठा nlattr **tca, व्योम **arg, bool ovr,
	       bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_TCINDEX_MAX + 1];
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	काष्ठा tcindex_filter_result *r = *arg;
	पूर्णांक err;

	pr_debug("tcindex_change(tp %p,handle 0x%08x,tca %p,arg %p),opt %p,"
	    "p %p,r %p,*arg %p\n",
	    tp, handle, tca, arg, opt, p, r, *arg);

	अगर (!opt)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, TCA_TCINDEX_MAX, opt,
					  tcindex_policy, शून्य);
	अगर (err < 0)
		वापस err;

	वापस tcindex_set_parms(net, tp, base, handle, p, r, tb,
				 tca[TCA_RATE], ovr, extack);
पूर्ण

अटल व्योम tcindex_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *walker,
			 bool rtnl_held)
अणु
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	काष्ठा tcindex_filter *f, *next;
	पूर्णांक i;

	pr_debug("tcindex_walk(tp %p,walker %p),p %p\n", tp, walker, p);
	अगर (p->perfect) अणु
		क्रम (i = 0; i < p->hash; i++) अणु
			अगर (!p->perfect[i].res.class)
				जारी;
			अगर (walker->count >= walker->skip) अणु
				अगर (walker->fn(tp, p->perfect + i, walker) < 0) अणु
					walker->stop = 1;
					वापस;
				पूर्ण
			पूर्ण
			walker->count++;
		पूर्ण
	पूर्ण
	अगर (!p->h)
		वापस;
	क्रम (i = 0; i < p->hash; i++) अणु
		क्रम (f = rtnl_dereference(p->h[i]); f; f = next) अणु
			next = rtnl_dereference(f->next);
			अगर (walker->count >= walker->skip) अणु
				अगर (walker->fn(tp, &f->result, walker) < 0) अणु
					walker->stop = 1;
					वापस;
				पूर्ण
			पूर्ण
			walker->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tcindex_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	पूर्णांक i;

	pr_debug("tcindex_destroy(tp %p),p %p\n", tp, p);

	अगर (p->perfect) अणु
		क्रम (i = 0; i < p->hash; i++) अणु
			काष्ठा tcindex_filter_result *r = p->perfect + i;

			/* tcf_queue_work() करोes not guarantee the ordering we
			 * want, so we have to take this refcnt temporarily to
			 * ensure 'p' is मुक्तd after all tcindex_filter_result
			 * here. Imperfect hash करोes not need this, because it
			 * uses linked lists rather than an array.
			 */
			tcindex_data_get(p);

			tcf_unbind_filter(tp, &r->res);
			अगर (tcf_exts_get_net(&r->exts))
				tcf_queue_work(&r->rwork,
					       tcindex_destroy_rexts_work);
			अन्यथा
				__tcindex_destroy_rexts(r);
		पूर्ण
	पूर्ण

	क्रम (i = 0; p->h && i < p->hash; i++) अणु
		काष्ठा tcindex_filter *f, *next;
		bool last;

		क्रम (f = rtnl_dereference(p->h[i]); f; f = next) अणु
			next = rtnl_dereference(f->next);
			tcindex_delete(tp, &f->result, &last, rtnl_held, शून्य);
		पूर्ण
	पूर्ण

	tcf_queue_work(&p->rwork, tcindex_destroy_work);
पूर्ण


अटल पूर्णांक tcindex_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
			काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा tcindex_data *p = rtnl_dereference(tp->root);
	काष्ठा tcindex_filter_result *r = fh;
	काष्ठा nlattr *nest;

	pr_debug("tcindex_dump(tp %p,fh %p,skb %p,t %p),p %p,r %p\n",
		 tp, fh, skb, t, p, r);
	pr_debug("p->perfect %p p->h %p\n", p->perfect, p->h);

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (!fh) अणु
		t->tcm_handle = ~0; /* whatever ... */
		अगर (nla_put_u32(skb, TCA_TCINDEX_HASH, p->hash) ||
		    nla_put_u16(skb, TCA_TCINDEX_MASK, p->mask) ||
		    nla_put_u32(skb, TCA_TCINDEX_SHIFT, p->shअगरt) ||
		    nla_put_u32(skb, TCA_TCINDEX_FALL_THROUGH, p->fall_through))
			जाओ nla_put_failure;
		nla_nest_end(skb, nest);
	पूर्ण अन्यथा अणु
		अगर (p->perfect) अणु
			t->tcm_handle = r - p->perfect;
		पूर्ण अन्यथा अणु
			काष्ठा tcindex_filter *f;
			काष्ठा tcindex_filter __rcu **fp;
			पूर्णांक i;

			t->tcm_handle = 0;
			क्रम (i = 0; !t->tcm_handle && i < p->hash; i++) अणु
				fp = &p->h[i];
				क्रम (f = rtnl_dereference(*fp);
				     !t->tcm_handle && f;
				     fp = &f->next, f = rtnl_dereference(*fp)) अणु
					अगर (&f->result == r)
						t->tcm_handle = f->key;
				पूर्ण
			पूर्ण
		पूर्ण
		pr_debug("handle = %d\n", t->tcm_handle);
		अगर (r->res.class &&
		    nla_put_u32(skb, TCA_TCINDEX_CLASSID, r->res.classid))
			जाओ nla_put_failure;

		अगर (tcf_exts_dump(skb, &r->exts) < 0)
			जाओ nla_put_failure;
		nla_nest_end(skb, nest);

		अगर (tcf_exts_dump_stats(skb, &r->exts) < 0)
			जाओ nla_put_failure;
	पूर्ण

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम tcindex_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl,
			       व्योम *q, अचिन्हित दीर्घ base)
अणु
	काष्ठा tcindex_filter_result *r = fh;

	अगर (r && r->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &r->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &r->res);
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops cls_tcindex_ops __पढ़ो_mostly = अणु
	.kind		=	"tcindex",
	.classअगरy	=	tcindex_classअगरy,
	.init		=	tcindex_init,
	.destroy	=	tcindex_destroy,
	.get		=	tcindex_get,
	.change		=	tcindex_change,
	.delete		=	tcindex_delete,
	.walk		=	tcindex_walk,
	.dump		=	tcindex_dump,
	.bind_class	=	tcindex_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_tcindex(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_tcindex_ops);
पूर्ण

अटल व्योम __निकास निकास_tcindex(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_tcindex_ops);
पूर्ण

module_init(init_tcindex)
module_निकास(निकास_tcindex)
MODULE_LICENSE("GPL");
