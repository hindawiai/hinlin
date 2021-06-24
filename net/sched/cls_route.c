<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_route.c	ROUTE4 classअगरier.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/dst.h>
#समावेश <net/route.h>
#समावेश <net/netlink.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>

/*
 * 1. For now we assume that route tags < 256.
 *    It allows to use direct table lookups, instead of hash tables.
 * 2. For now we assume that "from TAG" and "fromdev DEV" statements
 *    are mutually  exclusive.
 * 3. "to TAG from ANY" has higher priority, than "to ANY from XXX"
 */
काष्ठा route4_fasपंचांगap अणु
	काष्ठा route4_filter		*filter;
	u32				id;
	पूर्णांक				iअगर;
पूर्ण;

काष्ठा route4_head अणु
	काष्ठा route4_fasपंचांगap		fasपंचांगap[16];
	काष्ठा route4_bucket __rcu	*table[256 + 1];
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा route4_bucket अणु
	/* 16 FROM buckets + 16 IIF buckets + 1 wildcard bucket */
	काष्ठा route4_filter __rcu	*ht[16 + 16 + 1];
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा route4_filter अणु
	काष्ठा route4_filter __rcu	*next;
	u32			id;
	पूर्णांक			iअगर;

	काष्ठा tcf_result	res;
	काष्ठा tcf_exts		exts;
	u32			handle;
	काष्ठा route4_bucket	*bkt;
	काष्ठा tcf_proto	*tp;
	काष्ठा rcu_work		rwork;
पूर्ण;

#घोषणा ROUTE4_FAILURE ((काष्ठा route4_filter *)(-1L))

अटल अंतरभूत पूर्णांक route4_fasपंचांगap_hash(u32 id, पूर्णांक iअगर)
अणु
	वापस id & 0xF;
पूर्ण

अटल DEFINE_SPINLOCK(fasपंचांगap_lock);
अटल व्योम
route4_reset_fasपंचांगap(काष्ठा route4_head *head)
अणु
	spin_lock_bh(&fasपंचांगap_lock);
	स_रखो(head->fasपंचांगap, 0, माप(head->fasपंचांगap));
	spin_unlock_bh(&fasपंचांगap_lock);
पूर्ण

अटल व्योम
route4_set_fasपंचांगap(काष्ठा route4_head *head, u32 id, पूर्णांक iअगर,
		   काष्ठा route4_filter *f)
अणु
	पूर्णांक h = route4_fasपंचांगap_hash(id, iअगर);

	/* fasपंचांगap updates must look atomic to aling id, अगरf, filter */
	spin_lock_bh(&fasपंचांगap_lock);
	head->fasपंचांगap[h].id = id;
	head->fasपंचांगap[h].iअगर = iअगर;
	head->fasपंचांगap[h].filter = f;
	spin_unlock_bh(&fasपंचांगap_lock);
पूर्ण

अटल अंतरभूत पूर्णांक route4_hash_to(u32 id)
अणु
	वापस id & 0xFF;
पूर्ण

अटल अंतरभूत पूर्णांक route4_hash_from(u32 id)
अणु
	वापस (id >> 16) & 0xF;
पूर्ण

अटल अंतरभूत पूर्णांक route4_hash_iअगर(पूर्णांक iअगर)
अणु
	वापस 16 + ((iअगर >> 16) & 0xF);
पूर्ण

अटल अंतरभूत पूर्णांक route4_hash_wild(व्योम)
अणु
	वापस 32;
पूर्ण

#घोषणा ROUTE4_APPLY_RESULT()					\
अणु								\
	*res = f->res;						\
	अगर (tcf_exts_has_actions(&f->exts)) अणु			\
		पूर्णांक r = tcf_exts_exec(skb, &f->exts, res);	\
		अगर (r < 0) अणु					\
			करोnt_cache = 1;				\
			जारी;				\
		पूर्ण						\
		वापस r;					\
	पूर्ण अन्यथा अगर (!करोnt_cache)					\
		route4_set_fasपंचांगap(head, id, iअगर, f);		\
	वापस 0;						\
पूर्ण

अटल पूर्णांक route4_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			   काष्ठा tcf_result *res)
अणु
	काष्ठा route4_head *head = rcu_dereference_bh(tp->root);
	काष्ठा dst_entry *dst;
	काष्ठा route4_bucket *b;
	काष्ठा route4_filter *f;
	u32 id, h;
	पूर्णांक iअगर, करोnt_cache = 0;

	dst = skb_dst(skb);
	अगर (!dst)
		जाओ failure;

	id = dst->tclassid;

	iअगर = inet_iअगर(skb);

	h = route4_fasपंचांगap_hash(id, iअगर);

	spin_lock(&fasपंचांगap_lock);
	अगर (id == head->fasपंचांगap[h].id &&
	    iअगर == head->fasपंचांगap[h].iअगर &&
	    (f = head->fasपंचांगap[h].filter) != शून्य) अणु
		अगर (f == ROUTE4_FAILURE) अणु
			spin_unlock(&fasपंचांगap_lock);
			जाओ failure;
		पूर्ण

		*res = f->res;
		spin_unlock(&fasपंचांगap_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&fasपंचांगap_lock);

	h = route4_hash_to(id);

restart:
	b = rcu_dereference_bh(head->table[h]);
	अगर (b) अणु
		क्रम (f = rcu_dereference_bh(b->ht[route4_hash_from(id)]);
		     f;
		     f = rcu_dereference_bh(f->next))
			अगर (f->id == id)
				ROUTE4_APPLY_RESULT();

		क्रम (f = rcu_dereference_bh(b->ht[route4_hash_iअगर(iअगर)]);
		     f;
		     f = rcu_dereference_bh(f->next))
			अगर (f->iअगर == iअगर)
				ROUTE4_APPLY_RESULT();

		क्रम (f = rcu_dereference_bh(b->ht[route4_hash_wild()]);
		     f;
		     f = rcu_dereference_bh(f->next))
			ROUTE4_APPLY_RESULT();
	पूर्ण
	अगर (h < 256) अणु
		h = 256;
		id &= ~0xFFFF;
		जाओ restart;
	पूर्ण

	अगर (!करोnt_cache)
		route4_set_fasपंचांगap(head, id, iअगर, ROUTE4_FAILURE);
failure:
	वापस -1;
पूर्ण

अटल अंतरभूत u32 to_hash(u32 id)
अणु
	u32 h = id & 0xFF;

	अगर (id & 0x8000)
		h += 256;
	वापस h;
पूर्ण

अटल अंतरभूत u32 from_hash(u32 id)
अणु
	id &= 0xFFFF;
	अगर (id == 0xFFFF)
		वापस 32;
	अगर (!(id & 0x8000)) अणु
		अगर (id > 255)
			वापस 256;
		वापस id & 0xF;
	पूर्ण
	वापस 16 + (id & 0xF);
पूर्ण

अटल व्योम *route4_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा route4_head *head = rtnl_dereference(tp->root);
	काष्ठा route4_bucket *b;
	काष्ठा route4_filter *f;
	अचिन्हित पूर्णांक h1, h2;

	h1 = to_hash(handle);
	अगर (h1 > 256)
		वापस शून्य;

	h2 = from_hash(handle >> 16);
	अगर (h2 > 32)
		वापस शून्य;

	b = rtnl_dereference(head->table[h1]);
	अगर (b) अणु
		क्रम (f = rtnl_dereference(b->ht[h2]);
		     f;
		     f = rtnl_dereference(f->next))
			अगर (f->handle == handle)
				वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक route4_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा route4_head *head;

	head = kzalloc(माप(काष्ठा route4_head), GFP_KERNEL);
	अगर (head == शून्य)
		वापस -ENOBUFS;

	rcu_assign_poपूर्णांकer(tp->root, head);
	वापस 0;
पूर्ण

अटल व्योम __route4_delete_filter(काष्ठा route4_filter *f)
अणु
	tcf_exts_destroy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kमुक्त(f);
पूर्ण

अटल व्योम route4_delete_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा route4_filter *f = container_of(to_rcu_work(work),
					       काष्ठा route4_filter,
					       rwork);
	rtnl_lock();
	__route4_delete_filter(f);
	rtnl_unlock();
पूर्ण

अटल व्योम route4_queue_work(काष्ठा route4_filter *f)
अणु
	tcf_queue_work(&f->rwork, route4_delete_filter_work);
पूर्ण

अटल व्योम route4_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा route4_head *head = rtnl_dereference(tp->root);
	पूर्णांक h1, h2;

	अगर (head == शून्य)
		वापस;

	क्रम (h1 = 0; h1 <= 256; h1++) अणु
		काष्ठा route4_bucket *b;

		b = rtnl_dereference(head->table[h1]);
		अगर (b) अणु
			क्रम (h2 = 0; h2 <= 32; h2++) अणु
				काष्ठा route4_filter *f;

				जबतक ((f = rtnl_dereference(b->ht[h2])) != शून्य) अणु
					काष्ठा route4_filter *next;

					next = rtnl_dereference(f->next);
					RCU_INIT_POINTER(b->ht[h2], next);
					tcf_unbind_filter(tp, &f->res);
					अगर (tcf_exts_get_net(&f->exts))
						route4_queue_work(f);
					अन्यथा
						__route4_delete_filter(f);
				पूर्ण
			पूर्ण
			RCU_INIT_POINTER(head->table[h1], शून्य);
			kमुक्त_rcu(b, rcu);
		पूर्ण
	पूर्ण
	kमुक्त_rcu(head, rcu);
पूर्ण

अटल पूर्णांक route4_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
			 bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा route4_head *head = rtnl_dereference(tp->root);
	काष्ठा route4_filter *f = arg;
	काष्ठा route4_filter __rcu **fp;
	काष्ठा route4_filter *nf;
	काष्ठा route4_bucket *b;
	अचिन्हित पूर्णांक h = 0;
	पूर्णांक i, h1;

	अगर (!head || !f)
		वापस -EINVAL;

	h = f->handle;
	b = f->bkt;

	fp = &b->ht[from_hash(h >> 16)];
	क्रम (nf = rtnl_dereference(*fp); nf;
	     fp = &nf->next, nf = rtnl_dereference(*fp)) अणु
		अगर (nf == f) अणु
			/* unlink it */
			RCU_INIT_POINTER(*fp, rtnl_dereference(f->next));

			/* Remove any fasपंचांगap lookups that might ref filter
			 * notice we unlink'd the filter so we can't get it
			 * back in the fasपंचांगap.
			 */
			route4_reset_fasपंचांगap(head);

			/* Delete it */
			tcf_unbind_filter(tp, &f->res);
			tcf_exts_get_net(&f->exts);
			tcf_queue_work(&f->rwork, route4_delete_filter_work);

			/* Strip RTNL रक्षित tree */
			क्रम (i = 0; i <= 32; i++) अणु
				काष्ठा route4_filter *rt;

				rt = rtnl_dereference(b->ht[i]);
				अगर (rt)
					जाओ out;
			पूर्ण

			/* OK, session has no flows */
			RCU_INIT_POINTER(head->table[to_hash(h)], शून्य);
			kमुक्त_rcu(b, rcu);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	*last = true;
	क्रम (h1 = 0; h1 <= 256; h1++) अणु
		अगर (rcu_access_poपूर्णांकer(head->table[h1])) अणु
			*last = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy route4_policy[TCA_ROUTE4_MAX + 1] = अणु
	[TCA_ROUTE4_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_ROUTE4_TO]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_ROUTE4_FROM]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_ROUTE4_IIF]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक route4_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			    अचिन्हित दीर्घ base, काष्ठा route4_filter *f,
			    u32 handle, काष्ठा route4_head *head,
			    काष्ठा nlattr **tb, काष्ठा nlattr *est, पूर्णांक new,
			    bool ovr, काष्ठा netlink_ext_ack *extack)
अणु
	u32 id = 0, to = 0, nhandle = 0x8000;
	काष्ठा route4_filter *fp;
	अचिन्हित पूर्णांक h1;
	काष्ठा route4_bucket *b;
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, est, &f->exts, ovr, true, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_ROUTE4_TO]) अणु
		अगर (new && handle & 0x8000)
			वापस -EINVAL;
		to = nla_get_u32(tb[TCA_ROUTE4_TO]);
		अगर (to > 0xFF)
			वापस -EINVAL;
		nhandle = to;
	पूर्ण

	अगर (tb[TCA_ROUTE4_FROM]) अणु
		अगर (tb[TCA_ROUTE4_IIF])
			वापस -EINVAL;
		id = nla_get_u32(tb[TCA_ROUTE4_FROM]);
		अगर (id > 0xFF)
			वापस -EINVAL;
		nhandle |= id << 16;
	पूर्ण अन्यथा अगर (tb[TCA_ROUTE4_IIF]) अणु
		id = nla_get_u32(tb[TCA_ROUTE4_IIF]);
		अगर (id > 0x7FFF)
			वापस -EINVAL;
		nhandle |= (id | 0x8000) << 16;
	पूर्ण अन्यथा
		nhandle |= 0xFFFF << 16;

	अगर (handle && new) अणु
		nhandle |= handle & 0x7F00;
		अगर (nhandle != handle)
			वापस -EINVAL;
	पूर्ण

	h1 = to_hash(nhandle);
	b = rtnl_dereference(head->table[h1]);
	अगर (!b) अणु
		b = kzalloc(माप(काष्ठा route4_bucket), GFP_KERNEL);
		अगर (b == शून्य)
			वापस -ENOBUFS;

		rcu_assign_poपूर्णांकer(head->table[h1], b);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक h2 = from_hash(nhandle >> 16);

		क्रम (fp = rtnl_dereference(b->ht[h2]);
		     fp;
		     fp = rtnl_dereference(fp->next))
			अगर (fp->handle == f->handle)
				वापस -EEXIST;
	पूर्ण

	अगर (tb[TCA_ROUTE4_TO])
		f->id = to;

	अगर (tb[TCA_ROUTE4_FROM])
		f->id = to | id<<16;
	अन्यथा अगर (tb[TCA_ROUTE4_IIF])
		f->iअगर = id;

	f->handle = nhandle;
	f->bkt = b;
	f->tp = tp;

	अगर (tb[TCA_ROUTE4_CLASSID]) अणु
		f->res.classid = nla_get_u32(tb[TCA_ROUTE4_CLASSID]);
		tcf_bind_filter(tp, &f->res, base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक route4_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
			 काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base, u32 handle,
			 काष्ठा nlattr **tca, व्योम **arg, bool ovr,
			 bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा route4_head *head = rtnl_dereference(tp->root);
	काष्ठा route4_filter __rcu **fp;
	काष्ठा route4_filter *fold, *f1, *pfp, *f = शून्य;
	काष्ठा route4_bucket *b;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_ROUTE4_MAX + 1];
	अचिन्हित पूर्णांक h, th;
	पूर्णांक err;
	bool new = true;

	अगर (opt == शून्य)
		वापस handle ? -EINVAL : 0;

	err = nla_parse_nested_deprecated(tb, TCA_ROUTE4_MAX, opt,
					  route4_policy, शून्य);
	अगर (err < 0)
		वापस err;

	fold = *arg;
	अगर (fold && handle && fold->handle != handle)
			वापस -EINVAL;

	err = -ENOBUFS;
	f = kzalloc(माप(काष्ठा route4_filter), GFP_KERNEL);
	अगर (!f)
		जाओ errout;

	err = tcf_exts_init(&f->exts, net, TCA_ROUTE4_ACT, TCA_ROUTE4_POLICE);
	अगर (err < 0)
		जाओ errout;

	अगर (fold) अणु
		f->id = fold->id;
		f->iअगर = fold->iअगर;
		f->res = fold->res;
		f->handle = fold->handle;

		f->tp = fold->tp;
		f->bkt = fold->bkt;
		new = false;
	पूर्ण

	err = route4_set_parms(net, tp, base, f, handle, head, tb,
			       tca[TCA_RATE], new, ovr, extack);
	अगर (err < 0)
		जाओ errout;

	h = from_hash(f->handle >> 16);
	fp = &f->bkt->ht[h];
	क्रम (pfp = rtnl_dereference(*fp);
	     (f1 = rtnl_dereference(*fp)) != शून्य;
	     fp = &f1->next)
		अगर (f->handle < f1->handle)
			अवरोध;

	tcf_block_netअगर_keep_dst(tp->chain->block);
	rcu_assign_poपूर्णांकer(f->next, f1);
	rcu_assign_poपूर्णांकer(*fp, f);

	अगर (fold && fold->handle && f->handle != fold->handle) अणु
		th = to_hash(fold->handle);
		h = from_hash(fold->handle >> 16);
		b = rtnl_dereference(head->table[th]);
		अगर (b) अणु
			fp = &b->ht[h];
			क्रम (pfp = rtnl_dereference(*fp); pfp;
			     fp = &pfp->next, pfp = rtnl_dereference(*fp)) अणु
				अगर (pfp == fold) अणु
					rcu_assign_poपूर्णांकer(*fp, fold->next);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	route4_reset_fasपंचांगap(head);
	*arg = f;
	अगर (fold) अणु
		tcf_unbind_filter(tp, &fold->res);
		tcf_exts_get_net(&fold->exts);
		tcf_queue_work(&fold->rwork, route4_delete_filter_work);
	पूर्ण
	वापस 0;

errout:
	अगर (f)
		tcf_exts_destroy(&f->exts);
	kमुक्त(f);
	वापस err;
पूर्ण

अटल व्योम route4_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
			bool rtnl_held)
अणु
	काष्ठा route4_head *head = rtnl_dereference(tp->root);
	अचिन्हित पूर्णांक h, h1;

	अगर (head == शून्य || arg->stop)
		वापस;

	क्रम (h = 0; h <= 256; h++) अणु
		काष्ठा route4_bucket *b = rtnl_dereference(head->table[h]);

		अगर (b) अणु
			क्रम (h1 = 0; h1 <= 32; h1++) अणु
				काष्ठा route4_filter *f;

				क्रम (f = rtnl_dereference(b->ht[h1]);
				     f;
				     f = rtnl_dereference(f->next)) अणु
					अगर (arg->count < arg->skip) अणु
						arg->count++;
						जारी;
					पूर्ण
					अगर (arg->fn(tp, f, arg) < 0) अणु
						arg->stop = 1;
						वापस;
					पूर्ण
					arg->count++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक route4_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		       काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा route4_filter *f = fh;
	काष्ठा nlattr *nest;
	u32 id;

	अगर (f == शून्य)
		वापस skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (!(f->handle & 0x8000)) अणु
		id = f->id & 0xFF;
		अगर (nla_put_u32(skb, TCA_ROUTE4_TO, id))
			जाओ nla_put_failure;
	पूर्ण
	अगर (f->handle & 0x80000000) अणु
		अगर ((f->handle >> 16) != 0xFFFF &&
		    nla_put_u32(skb, TCA_ROUTE4_IIF, f->iअगर))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		id = f->id >> 16;
		अगर (nla_put_u32(skb, TCA_ROUTE4_FROM, id))
			जाओ nla_put_failure;
	पूर्ण
	अगर (f->res.classid &&
	    nla_put_u32(skb, TCA_ROUTE4_CLASSID, f->res.classid))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम route4_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			      अचिन्हित दीर्घ base)
अणु
	काष्ठा route4_filter *f = fh;

	अगर (f && f->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &f->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &f->res);
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops cls_route4_ops __पढ़ो_mostly = अणु
	.kind		=	"route",
	.classअगरy	=	route4_classअगरy,
	.init		=	route4_init,
	.destroy	=	route4_destroy,
	.get		=	route4_get,
	.change		=	route4_change,
	.delete		=	route4_delete,
	.walk		=	route4_walk,
	.dump		=	route4_dump,
	.bind_class	=	route4_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_route4(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_route4_ops);
पूर्ण

अटल व्योम __निकास निकास_route4(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_route4_ops);
पूर्ण

module_init(init_route4)
module_निकास(निकास_route4)
MODULE_LICENSE("GPL");
