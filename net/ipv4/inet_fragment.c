<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inet fragments management
 *
 * 		Authors:	Pavel Emelyanov <xemul@खोलोvz.org>
 *				Started as consolidation of ipv4/ip_fragment.c,
 *				ipv6/reassembly. and ipv6 nf conntrack reassembly
 */

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/rhashtable.h>

#समावेश <net/sock.h>
#समावेश <net/inet_frag.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

/* Use skb->cb to track consecutive/adjacent fragments coming at
 * the end of the queue. Nodes in the rb-tree queue will
 * contain "runs" of one or more adjacent fragments.
 *
 * Invariants:
 * - next_frag is शून्य at the tail of a "run";
 * - the head of a "run" has the sum of all fragment lengths in frag_run_len.
 */
काष्ठा ipfrag_skb_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm	h4;
		काष्ठा inet6_skb_parm	h6;
	पूर्ण;
	काष्ठा sk_buff		*next_frag;
	पूर्णांक			frag_run_len;
पूर्ण;

#घोषणा FRAG_CB(skb)		((काष्ठा ipfrag_skb_cb *)((skb)->cb))

अटल व्योम fragcb_clear(काष्ठा sk_buff *skb)
अणु
	RB_CLEAR_NODE(&skb->rbnode);
	FRAG_CB(skb)->next_frag = शून्य;
	FRAG_CB(skb)->frag_run_len = skb->len;
पूर्ण

/* Append skb to the last "run". */
अटल व्योम fragrun_append_to_last(काष्ठा inet_frag_queue *q,
				   काष्ठा sk_buff *skb)
अणु
	fragcb_clear(skb);

	FRAG_CB(q->last_run_head)->frag_run_len += skb->len;
	FRAG_CB(q->fragments_tail)->next_frag = skb;
	q->fragments_tail = skb;
पूर्ण

/* Create a new "run" with the skb. */
अटल व्योम fragrun_create(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ipfrag_skb_cb) > माप(skb->cb));
	fragcb_clear(skb);

	अगर (q->last_run_head)
		rb_link_node(&skb->rbnode, &q->last_run_head->rbnode,
			     &q->last_run_head->rbnode.rb_right);
	अन्यथा
		rb_link_node(&skb->rbnode, शून्य, &q->rb_fragments.rb_node);
	rb_insert_color(&skb->rbnode, &q->rb_fragments);

	q->fragments_tail = skb;
	q->last_run_head = skb;
पूर्ण

/* Given the OR values of all fragments, apply RFC 3168 5.3 requirements
 * Value : 0xff अगर frame should be dropped.
 *         0 or INET_ECN_CE value, to be ORed in to final iph->tos field
 */
स्थिर u8 ip_frag_ecn_table[16] = अणु
	/* at least one fragment had CE, and others ECT_0 or ECT_1 */
	[IPFRAG_ECN_CE | IPFRAG_ECN_ECT_0]			= INET_ECN_CE,
	[IPFRAG_ECN_CE | IPFRAG_ECN_ECT_1]			= INET_ECN_CE,
	[IPFRAG_ECN_CE | IPFRAG_ECN_ECT_0 | IPFRAG_ECN_ECT_1]	= INET_ECN_CE,

	/* invalid combinations : drop frame */
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_CE] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_ECT_0] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_ECT_1] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_ECT_0 | IPFRAG_ECN_ECT_1] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_CE | IPFRAG_ECN_ECT_0] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_CE | IPFRAG_ECN_ECT_1] = 0xff,
	[IPFRAG_ECN_NOT_ECT | IPFRAG_ECN_CE | IPFRAG_ECN_ECT_0 | IPFRAG_ECN_ECT_1] = 0xff,
पूर्ण;
EXPORT_SYMBOL(ip_frag_ecn_table);

पूर्णांक inet_frags_init(काष्ठा inet_frags *f)
अणु
	f->frags_cachep = kmem_cache_create(f->frags_cache_name, f->qsize, 0, 0,
					    शून्य);
	अगर (!f->frags_cachep)
		वापस -ENOMEM;

	refcount_set(&f->refcnt, 1);
	init_completion(&f->completion);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(inet_frags_init);

व्योम inet_frags_fini(काष्ठा inet_frags *f)
अणु
	अगर (refcount_dec_and_test(&f->refcnt))
		complete(&f->completion);

	रुको_क्रम_completion(&f->completion);

	kmem_cache_destroy(f->frags_cachep);
	f->frags_cachep = शून्य;
पूर्ण
EXPORT_SYMBOL(inet_frags_fini);

/* called from rhashtable_मुक्त_and_destroy() at netns_frags dismantle */
अटल व्योम inet_frags_मुक्त_cb(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा inet_frag_queue *fq = ptr;
	पूर्णांक count;

	count = del_समयr_sync(&fq->समयr) ? 1 : 0;

	spin_lock_bh(&fq->lock);
	अगर (!(fq->flags & INET_FRAG_COMPLETE)) अणु
		fq->flags |= INET_FRAG_COMPLETE;
		count++;
	पूर्ण अन्यथा अगर (fq->flags & INET_FRAG_HASH_DEAD) अणु
		count++;
	पूर्ण
	spin_unlock_bh(&fq->lock);

	अगर (refcount_sub_and_test(count, &fq->refcnt))
		inet_frag_destroy(fq);
पूर्ण

अटल LLIST_HEAD(fqdir_मुक्त_list);

अटल व्योम fqdir_मुक्त_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा llist_node *समाप्त_list;
	काष्ठा fqdir *fqdir, *पंचांगp;
	काष्ठा inet_frags *f;

	/* Atomically snapshot the list of fqdirs to मुक्त */
	समाप्त_list = llist_del_all(&fqdir_मुक्त_list);

	/* We need to make sure all ongoing call_rcu(..., inet_frag_destroy_rcu)
	 * have completed, since they need to dereference fqdir.
	 * Would it not be nice to have kमुक्त_rcu_barrier() ? :)
	 */
	rcu_barrier();

	llist_क्रम_each_entry_safe(fqdir, पंचांगp, समाप्त_list, मुक्त_list) अणु
		f = fqdir->f;
		अगर (refcount_dec_and_test(&f->refcnt))
			complete(&f->completion);

		kमुक्त(fqdir);
	पूर्ण
पूर्ण

अटल DECLARE_WORK(fqdir_मुक्त_work, fqdir_मुक्त_fn);

अटल व्योम fqdir_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fqdir *fqdir = container_of(work, काष्ठा fqdir, destroy_work);

	rhashtable_मुक्त_and_destroy(&fqdir->rhashtable, inet_frags_मुक्त_cb, शून्य);

	अगर (llist_add(&fqdir->मुक्त_list, &fqdir_मुक्त_list))
		queue_work(प्रणाली_wq, &fqdir_मुक्त_work);
पूर्ण

पूर्णांक fqdir_init(काष्ठा fqdir **fqdirp, काष्ठा inet_frags *f, काष्ठा net *net)
अणु
	काष्ठा fqdir *fqdir = kzalloc(माप(*fqdir), GFP_KERNEL);
	पूर्णांक res;

	अगर (!fqdir)
		वापस -ENOMEM;
	fqdir->f = f;
	fqdir->net = net;
	res = rhashtable_init(&fqdir->rhashtable, &fqdir->f->rhash_params);
	अगर (res < 0) अणु
		kमुक्त(fqdir);
		वापस res;
	पूर्ण
	refcount_inc(&f->refcnt);
	*fqdirp = fqdir;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fqdir_init);

अटल काष्ठा workqueue_काष्ठा *inet_frag_wq;

अटल पूर्णांक __init inet_frag_wq_init(व्योम)
अणु
	inet_frag_wq = create_workqueue("inet_frag_wq");
	अगर (!inet_frag_wq)
		panic("Could not create inet frag workq");
	वापस 0;
पूर्ण

pure_initcall(inet_frag_wq_init);

व्योम fqdir_निकास(काष्ठा fqdir *fqdir)
अणु
	INIT_WORK(&fqdir->destroy_work, fqdir_work_fn);
	queue_work(inet_frag_wq, &fqdir->destroy_work);
पूर्ण
EXPORT_SYMBOL(fqdir_निकास);

व्योम inet_frag_समाप्त(काष्ठा inet_frag_queue *fq)
अणु
	अगर (del_समयr(&fq->समयr))
		refcount_dec(&fq->refcnt);

	अगर (!(fq->flags & INET_FRAG_COMPLETE)) अणु
		काष्ठा fqdir *fqdir = fq->fqdir;

		fq->flags |= INET_FRAG_COMPLETE;
		rcu_पढ़ो_lock();
		/* The RCU पढ़ो lock provides a memory barrier
		 * guaranteeing that अगर fqdir->dead is false then
		 * the hash table deकाष्ठाion will not start until
		 * after we unlock.  Paired with inet_frags_निकास_net().
		 */
		अगर (!fqdir->dead) अणु
			rhashtable_हटाओ_fast(&fqdir->rhashtable, &fq->node,
					       fqdir->f->rhash_params);
			refcount_dec(&fq->refcnt);
		पूर्ण अन्यथा अणु
			fq->flags |= INET_FRAG_HASH_DEAD;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(inet_frag_समाप्त);

अटल व्योम inet_frag_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा inet_frag_queue *q = container_of(head, काष्ठा inet_frag_queue,
						 rcu);
	काष्ठा inet_frags *f = q->fqdir->f;

	अगर (f->deकाष्ठाor)
		f->deकाष्ठाor(q);
	kmem_cache_मुक्त(f->frags_cachep, q);
पूर्ण

अचिन्हित पूर्णांक inet_frag_rbtree_purge(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *p = rb_first(root);
	अचिन्हित पूर्णांक sum = 0;

	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_entry(p, काष्ठा sk_buff, rbnode);

		p = rb_next(p);
		rb_erase(&skb->rbnode, root);
		जबतक (skb) अणु
			काष्ठा sk_buff *next = FRAG_CB(skb)->next_frag;

			sum += skb->truesize;
			kमुक्त_skb(skb);
			skb = next;
		पूर्ण
	पूर्ण
	वापस sum;
पूर्ण
EXPORT_SYMBOL(inet_frag_rbtree_purge);

व्योम inet_frag_destroy(काष्ठा inet_frag_queue *q)
अणु
	काष्ठा fqdir *fqdir;
	अचिन्हित पूर्णांक sum, sum_truesize = 0;
	काष्ठा inet_frags *f;

	WARN_ON(!(q->flags & INET_FRAG_COMPLETE));
	WARN_ON(del_समयr(&q->समयr) != 0);

	/* Release all fragment data. */
	fqdir = q->fqdir;
	f = fqdir->f;
	sum_truesize = inet_frag_rbtree_purge(&q->rb_fragments);
	sum = sum_truesize + f->qsize;

	call_rcu(&q->rcu, inet_frag_destroy_rcu);

	sub_frag_mem_limit(fqdir, sum);
पूर्ण
EXPORT_SYMBOL(inet_frag_destroy);

अटल काष्ठा inet_frag_queue *inet_frag_alloc(काष्ठा fqdir *fqdir,
					       काष्ठा inet_frags *f,
					       व्योम *arg)
अणु
	काष्ठा inet_frag_queue *q;

	q = kmem_cache_zalloc(f->frags_cachep, GFP_ATOMIC);
	अगर (!q)
		वापस शून्य;

	q->fqdir = fqdir;
	f->स्थिरructor(q, arg);
	add_frag_mem_limit(fqdir, f->qsize);

	समयr_setup(&q->समयr, f->frag_expire, 0);
	spin_lock_init(&q->lock);
	refcount_set(&q->refcnt, 3);

	वापस q;
पूर्ण

अटल काष्ठा inet_frag_queue *inet_frag_create(काष्ठा fqdir *fqdir,
						व्योम *arg,
						काष्ठा inet_frag_queue **prev)
अणु
	काष्ठा inet_frags *f = fqdir->f;
	काष्ठा inet_frag_queue *q;

	q = inet_frag_alloc(fqdir, f, arg);
	अगर (!q) अणु
		*prev = ERR_PTR(-ENOMEM);
		वापस शून्य;
	पूर्ण
	mod_समयr(&q->समयr, jअगरfies + fqdir->समयout);

	*prev = rhashtable_lookup_get_insert_key(&fqdir->rhashtable, &q->key,
						 &q->node, f->rhash_params);
	अगर (*prev) अणु
		q->flags |= INET_FRAG_COMPLETE;
		inet_frag_समाप्त(q);
		inet_frag_destroy(q);
		वापस शून्य;
	पूर्ण
	वापस q;
पूर्ण

/* TODO : call from rcu_पढ़ो_lock() and no दीर्घer use refcount_inc_not_zero() */
काष्ठा inet_frag_queue *inet_frag_find(काष्ठा fqdir *fqdir, व्योम *key)
अणु
	काष्ठा inet_frag_queue *fq = शून्य, *prev;

	अगर (!fqdir->high_thresh || frag_mem_limit(fqdir) > fqdir->high_thresh)
		वापस शून्य;

	rcu_पढ़ो_lock();

	prev = rhashtable_lookup(&fqdir->rhashtable, key, fqdir->f->rhash_params);
	अगर (!prev)
		fq = inet_frag_create(fqdir, key, &prev);
	अगर (!IS_ERR_OR_शून्य(prev)) अणु
		fq = prev;
		अगर (!refcount_inc_not_zero(&fq->refcnt))
			fq = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस fq;
पूर्ण
EXPORT_SYMBOL(inet_frag_find);

पूर्णांक inet_frag_queue_insert(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *skb,
			   पूर्णांक offset, पूर्णांक end)
अणु
	काष्ठा sk_buff *last = q->fragments_tail;

	/* RFC5722, Section 4, amended by Errata ID : 3089
	 *                          When reassembling an IPv6 datagram, अगर
	 *   one or more its स्थिरituent fragments is determined to be an
	 *   overlapping fragment, the entire datagram (and any स्थिरituent
	 *   fragments) MUST be silently discarded.
	 *
	 * Duplicates, however, should be ignored (i.e. skb dropped, but the
	 * queue/fragments kept क्रम later reassembly).
	 */
	अगर (!last)
		fragrun_create(q, skb);  /* First fragment. */
	अन्यथा अगर (last->ip_defrag_offset + last->len < end) अणु
		/* This is the common हाल: skb goes to the end. */
		/* Detect and discard overlaps. */
		अगर (offset < last->ip_defrag_offset + last->len)
			वापस IPFRAG_OVERLAP;
		अगर (offset == last->ip_defrag_offset + last->len)
			fragrun_append_to_last(q, skb);
		अन्यथा
			fragrun_create(q, skb);
	पूर्ण अन्यथा अणु
		/* Binary search. Note that skb can become the first fragment,
		 * but not the last (covered above).
		 */
		काष्ठा rb_node **rbn, *parent;

		rbn = &q->rb_fragments.rb_node;
		करो अणु
			काष्ठा sk_buff *curr;
			पूर्णांक curr_run_end;

			parent = *rbn;
			curr = rb_to_skb(parent);
			curr_run_end = curr->ip_defrag_offset +
					FRAG_CB(curr)->frag_run_len;
			अगर (end <= curr->ip_defrag_offset)
				rbn = &parent->rb_left;
			अन्यथा अगर (offset >= curr_run_end)
				rbn = &parent->rb_right;
			अन्यथा अगर (offset >= curr->ip_defrag_offset &&
				 end <= curr_run_end)
				वापस IPFRAG_DUP;
			अन्यथा
				वापस IPFRAG_OVERLAP;
		पूर्ण जबतक (*rbn);
		/* Here we have parent properly set, and rbn poपूर्णांकing to
		 * one of its शून्य left/right children. Insert skb.
		 */
		fragcb_clear(skb);
		rb_link_node(&skb->rbnode, parent, rbn);
		rb_insert_color(&skb->rbnode, &q->rb_fragments);
	पूर्ण

	skb->ip_defrag_offset = offset;

	वापस IPFRAG_OK;
पूर्ण
EXPORT_SYMBOL(inet_frag_queue_insert);

व्योम *inet_frag_reयंत्र_prepare(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *skb,
			      काष्ठा sk_buff *parent)
अणु
	काष्ठा sk_buff *fp, *head = skb_rb_first(&q->rb_fragments);
	काष्ठा sk_buff **nextp;
	पूर्णांक delta;

	अगर (head != skb) अणु
		fp = skb_clone(skb, GFP_ATOMIC);
		अगर (!fp)
			वापस शून्य;
		FRAG_CB(fp)->next_frag = FRAG_CB(skb)->next_frag;
		अगर (RB_EMPTY_NODE(&skb->rbnode))
			FRAG_CB(parent)->next_frag = fp;
		अन्यथा
			rb_replace_node(&skb->rbnode, &fp->rbnode,
					&q->rb_fragments);
		अगर (q->fragments_tail == skb)
			q->fragments_tail = fp;
		skb_morph(skb, head);
		FRAG_CB(skb)->next_frag = FRAG_CB(head)->next_frag;
		rb_replace_node(&head->rbnode, &skb->rbnode,
				&q->rb_fragments);
		consume_skb(head);
		head = skb;
	पूर्ण
	WARN_ON(head->ip_defrag_offset != 0);

	delta = -head->truesize;

	/* Head of list must not be cloned. */
	अगर (skb_unclone(head, GFP_ATOMIC))
		वापस शून्य;

	delta += head->truesize;
	अगर (delta)
		add_frag_mem_limit(q->fqdir, delta);

	/* If the first fragment is fragmented itself, we split
	 * it to two chunks: the first with data and paged part
	 * and the second, holding only fragments.
	 */
	अगर (skb_has_frag_list(head)) अणु
		काष्ठा sk_buff *clone;
		पूर्णांक i, plen = 0;

		clone = alloc_skb(0, GFP_ATOMIC);
		अगर (!clone)
			वापस शून्य;
		skb_shinfo(clone)->frag_list = skb_shinfo(head)->frag_list;
		skb_frag_list_init(head);
		क्रम (i = 0; i < skb_shinfo(head)->nr_frags; i++)
			plen += skb_frag_size(&skb_shinfo(head)->frags[i]);
		clone->data_len = head->data_len - plen;
		clone->len = clone->data_len;
		head->truesize += clone->truesize;
		clone->csum = 0;
		clone->ip_summed = head->ip_summed;
		add_frag_mem_limit(q->fqdir, clone->truesize);
		skb_shinfo(head)->frag_list = clone;
		nextp = &clone->next;
	पूर्ण अन्यथा अणु
		nextp = &skb_shinfo(head)->frag_list;
	पूर्ण

	वापस nextp;
पूर्ण
EXPORT_SYMBOL(inet_frag_reयंत्र_prepare);

व्योम inet_frag_reयंत्र_finish(काष्ठा inet_frag_queue *q, काष्ठा sk_buff *head,
			    व्योम *reयंत्र_data, bool try_coalesce)
अणु
	काष्ठा sk_buff **nextp = (काष्ठा sk_buff **)reयंत्र_data;
	काष्ठा rb_node *rbn;
	काष्ठा sk_buff *fp;
	पूर्णांक sum_truesize;

	skb_push(head, head->data - skb_network_header(head));

	/* Traverse the tree in order, to build frag_list. */
	fp = FRAG_CB(head)->next_frag;
	rbn = rb_next(&head->rbnode);
	rb_erase(&head->rbnode, &q->rb_fragments);

	sum_truesize = head->truesize;
	जबतक (rbn || fp) अणु
		/* fp poपूर्णांकs to the next sk_buff in the current run;
		 * rbn poपूर्णांकs to the next run.
		 */
		/* Go through the current run. */
		जबतक (fp) अणु
			काष्ठा sk_buff *next_frag = FRAG_CB(fp)->next_frag;
			bool stolen;
			पूर्णांक delta;

			sum_truesize += fp->truesize;
			अगर (head->ip_summed != fp->ip_summed)
				head->ip_summed = CHECKSUM_NONE;
			अन्यथा अगर (head->ip_summed == CHECKSUM_COMPLETE)
				head->csum = csum_add(head->csum, fp->csum);

			अगर (try_coalesce && skb_try_coalesce(head, fp, &stolen,
							     &delta)) अणु
				kमुक्त_skb_partial(fp, stolen);
			पूर्ण अन्यथा अणु
				fp->prev = शून्य;
				स_रखो(&fp->rbnode, 0, माप(fp->rbnode));
				fp->sk = शून्य;

				head->data_len += fp->len;
				head->len += fp->len;
				head->truesize += fp->truesize;

				*nextp = fp;
				nextp = &fp->next;
			पूर्ण

			fp = next_frag;
		पूर्ण
		/* Move to the next run. */
		अगर (rbn) अणु
			काष्ठा rb_node *rbnext = rb_next(rbn);

			fp = rb_to_skb(rbn);
			rb_erase(rbn, &q->rb_fragments);
			rbn = rbnext;
		पूर्ण
	पूर्ण
	sub_frag_mem_limit(q->fqdir, sum_truesize);

	*nextp = शून्य;
	skb_mark_not_on_list(head);
	head->prev = शून्य;
	head->tstamp = q->stamp;
पूर्ण
EXPORT_SYMBOL(inet_frag_reयंत्र_finish);

काष्ठा sk_buff *inet_frag_pull_head(काष्ठा inet_frag_queue *q)
अणु
	काष्ठा sk_buff *head, *skb;

	head = skb_rb_first(&q->rb_fragments);
	अगर (!head)
		वापस शून्य;
	skb = FRAG_CB(head)->next_frag;
	अगर (skb)
		rb_replace_node(&head->rbnode, &skb->rbnode,
				&q->rb_fragments);
	अन्यथा
		rb_erase(&head->rbnode, &q->rb_fragments);
	स_रखो(&head->rbnode, 0, माप(head->rbnode));
	barrier();

	अगर (head == q->fragments_tail)
		q->fragments_tail = शून्य;

	sub_frag_mem_limit(q->fqdir, head->truesize);

	वापस head;
पूर्ण
EXPORT_SYMBOL(inet_frag_pull_head);
