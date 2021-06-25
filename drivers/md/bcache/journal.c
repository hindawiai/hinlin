<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bcache journalling code, क्रम btree insertions
 *
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "extents.h"

#समावेश <trace/events/bcache.h>

/*
 * Journal replay/recovery:
 *
 * This code is all driven from run_cache_set(); we first पढ़ो the journal
 * entries, करो some other stuff, then we mark all the keys in the journal
 * entries (same as garbage collection would), then we replay them - reinserting
 * them पूर्णांकo the cache in precisely the same order as they appear in the
 * journal.
 *
 * We only journal keys that go in leaf nodes, which simplअगरies things quite a
 * bit.
 */

अटल व्योम journal_पढ़ो_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;

	closure_put(cl);
पूर्ण

अटल पूर्णांक journal_पढ़ो_bucket(काष्ठा cache *ca, काष्ठा list_head *list,
			       अचिन्हित पूर्णांक bucket_index)
अणु
	काष्ठा journal_device *ja = &ca->journal;
	काष्ठा bio *bio = &ja->bio;

	काष्ठा journal_replay *i;
	काष्ठा jset *j, *data = ca->set->journal.w[0].data;
	काष्ठा closure cl;
	अचिन्हित पूर्णांक len, left, offset = 0;
	पूर्णांक ret = 0;
	sector_t bucket = bucket_to_sector(ca->set, ca->sb.d[bucket_index]);

	closure_init_stack(&cl);

	pr_debug("reading %u\n", bucket_index);

	जबतक (offset < ca->sb.bucket_size) अणु
reपढ़ो:		left = ca->sb.bucket_size - offset;
		len = min_t(अचिन्हित पूर्णांक, left, PAGE_SECTORS << JSET_BITS);

		bio_reset(bio);
		bio->bi_iter.bi_sector	= bucket + offset;
		bio_set_dev(bio, ca->bdev);
		bio->bi_iter.bi_size	= len << 9;

		bio->bi_end_io	= journal_पढ़ो_endio;
		bio->bi_निजी = &cl;
		bio_set_op_attrs(bio, REQ_OP_READ, 0);
		bch_bio_map(bio, data);

		closure_bio_submit(ca->set, bio, &cl);
		closure_sync(&cl);

		/* This function could be simpler now since we no दीर्घer ग_लिखो
		 * journal entries that overlap bucket boundaries; this means
		 * the start of a bucket will always have a valid journal entry
		 * अगर it has any journal entries at all.
		 */

		j = data;
		जबतक (len) अणु
			काष्ठा list_head *where;
			माप_प्रकार blocks, bytes = set_bytes(j);

			अगर (j->magic != jset_magic(&ca->sb)) अणु
				pr_debug("%u: bad magic\n", bucket_index);
				वापस ret;
			पूर्ण

			अगर (bytes > left << 9 ||
			    bytes > PAGE_SIZE << JSET_BITS) अणु
				pr_info("%u: too big, %zu bytes, offset %u\n",
					bucket_index, bytes, offset);
				वापस ret;
			पूर्ण

			अगर (bytes > len << 9)
				जाओ reपढ़ो;

			अगर (j->csum != csum_set(j)) अणु
				pr_info("%u: bad csum, %zu bytes, offset %u\n",
					bucket_index, bytes, offset);
				वापस ret;
			पूर्ण

			blocks = set_blocks(j, block_bytes(ca));

			/*
			 * Nodes in 'list' are in linear increasing order of
			 * i->j.seq, the node on head has the smallest (oldest)
			 * journal seq, the node on tail has the biggest
			 * (latest) journal seq.
			 */

			/*
			 * Check from the oldest jset क्रम last_seq. If
			 * i->j.seq < j->last_seq, it means the oldest jset
			 * in list is expired and useless, हटाओ it from
			 * this list. Otherwise, j is a candidate jset क्रम
			 * further following checks.
			 */
			जबतक (!list_empty(list)) अणु
				i = list_first_entry(list,
					काष्ठा journal_replay, list);
				अगर (i->j.seq >= j->last_seq)
					अवरोध;
				list_del(&i->list);
				kमुक्त(i);
			पूर्ण

			/* iterate list in reverse order (from latest jset) */
			list_क्रम_each_entry_reverse(i, list, list) अणु
				अगर (j->seq == i->j.seq)
					जाओ next_set;

				/*
				 * अगर j->seq is less than any i->j.last_seq
				 * in list, j is an expired and useless jset.
				 */
				अगर (j->seq < i->j.last_seq)
					जाओ next_set;

				/*
				 * 'where' poपूर्णांकs to first jset in list which
				 * is elder then j.
				 */
				अगर (j->seq > i->j.seq) अणु
					where = &i->list;
					जाओ add;
				पूर्ण
			पूर्ण

			where = list;
add:
			i = kदो_स्मृति(दुरत्व(काष्ठा journal_replay, j) +
				    bytes, GFP_KERNEL);
			अगर (!i)
				वापस -ENOMEM;
			स_नकल(&i->j, j, bytes);
			/* Add to the location after 'where' poपूर्णांकs to */
			list_add(&i->list, where);
			ret = 1;

			अगर (j->seq > ja->seq[bucket_index])
				ja->seq[bucket_index] = j->seq;
next_set:
			offset	+= blocks * ca->sb.block_size;
			len	-= blocks * ca->sb.block_size;
			j = ((व्योम *) j) + blocks * block_bytes(ca);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक bch_journal_पढ़ो(काष्ठा cache_set *c, काष्ठा list_head *list)
अणु
#घोषणा पढ़ो_bucket(b)							\
	(अणु								\
		ret = journal_पढ़ो_bucket(ca, list, b);			\
		__set_bit(b, biपंचांगap);					\
		अगर (ret < 0)						\
			वापस ret;					\
		ret;							\
	पूर्ण)

	काष्ठा cache *ca = c->cache;
	पूर्णांक ret = 0;
	काष्ठा journal_device *ja = &ca->journal;
	DECLARE_BITMAP(biपंचांगap, SB_JOURNAL_BUCKETS);
	अचिन्हित पूर्णांक i, l, r, m;
	uपूर्णांक64_t seq;

	biपंचांगap_zero(biपंचांगap, SB_JOURNAL_BUCKETS);
	pr_debug("%u journal buckets\n", ca->sb.njournal_buckets);

	/*
	 * Read journal buckets ordered by golden ratio hash to quickly
	 * find a sequence of buckets with valid journal entries
	 */
	क्रम (i = 0; i < ca->sb.njournal_buckets; i++) अणु
		/*
		 * We must try the index l with ZERO first क्रम
		 * correctness due to the scenario that the journal
		 * bucket is circular buffer which might have wrapped
		 */
		l = (i * 2654435769U) % ca->sb.njournal_buckets;

		अगर (test_bit(l, biपंचांगap))
			अवरोध;

		अगर (पढ़ो_bucket(l))
			जाओ द्वा_खोज;
	पूर्ण

	/*
	 * If that fails, check all the buckets we haven't checked
	 * alपढ़ोy
	 */
	pr_debug("falling back to linear search\n");

	क्रम_each_clear_bit(l, biपंचांगap, ca->sb.njournal_buckets)
		अगर (पढ़ो_bucket(l))
			जाओ द्वा_खोज;

	/* no journal entries on this device? */
	अगर (l == ca->sb.njournal_buckets)
		जाओ out;
द्वा_खोज:
	BUG_ON(list_empty(list));

	/* Binary search */
	m = l;
	r = find_next_bit(biपंचांगap, ca->sb.njournal_buckets, l + 1);
	pr_debug("starting binary search, l %u r %u\n", l, r);

	जबतक (l + 1 < r) अणु
		seq = list_entry(list->prev, काष्ठा journal_replay,
				 list)->j.seq;

		m = (l + r) >> 1;
		पढ़ो_bucket(m);

		अगर (seq != list_entry(list->prev, काष्ठा journal_replay,
				      list)->j.seq)
			l = m;
		अन्यथा
			r = m;
	पूर्ण

	/*
	 * Read buckets in reverse order until we stop finding more
	 * journal entries
	 */
	pr_debug("finishing up: m %u njournal_buckets %u\n",
		 m, ca->sb.njournal_buckets);
	l = m;

	जबतक (1) अणु
		अगर (!l--)
			l = ca->sb.njournal_buckets - 1;

		अगर (l == m)
			अवरोध;

		अगर (test_bit(l, biपंचांगap))
			जारी;

		अगर (!पढ़ो_bucket(l))
			अवरोध;
	पूर्ण

	seq = 0;

	क्रम (i = 0; i < ca->sb.njournal_buckets; i++)
		अगर (ja->seq[i] > seq) अणु
			seq = ja->seq[i];
			/*
			 * When journal_reclaim() goes to allocate क्रम
			 * the first समय, it'll use the bucket after
			 * ja->cur_idx
			 */
			ja->cur_idx = i;
			ja->last_idx = ja->discard_idx = (i + 1) %
				ca->sb.njournal_buckets;

		पूर्ण

out:
	अगर (!list_empty(list))
		c->journal.seq = list_entry(list->prev,
					    काष्ठा journal_replay,
					    list)->j.seq;

	वापस 0;
#अघोषित पढ़ो_bucket
पूर्ण

व्योम bch_journal_mark(काष्ठा cache_set *c, काष्ठा list_head *list)
अणु
	atomic_t p = अणु 0 पूर्ण;
	काष्ठा bkey *k;
	काष्ठा journal_replay *i;
	काष्ठा journal *j = &c->journal;
	uपूर्णांक64_t last = j->seq;

	/*
	 * journal.pin should never fill up - we never ग_लिखो a journal
	 * entry when it would fill up. But अगर क्रम some reason it करोes, we
	 * iterate over the list in reverse order so that we can just skip that
	 * refcount instead of bugging.
	 */

	list_क्रम_each_entry_reverse(i, list, list) अणु
		BUG_ON(last < i->j.seq);
		i->pin = शून्य;

		जबतक (last-- != i->j.seq)
			अगर (fअगरo_मुक्त(&j->pin) > 1) अणु
				fअगरo_push_front(&j->pin, p);
				atomic_set(&fअगरo_front(&j->pin), 0);
			पूर्ण

		अगर (fअगरo_मुक्त(&j->pin) > 1) अणु
			fअगरo_push_front(&j->pin, p);
			i->pin = &fअगरo_front(&j->pin);
			atomic_set(i->pin, 1);
		पूर्ण

		क्रम (k = i->j.start;
		     k < bset_bkey_last(&i->j);
		     k = bkey_next(k))
			अगर (!__bch_extent_invalid(c, k)) अणु
				अचिन्हित पूर्णांक j;

				क्रम (j = 0; j < KEY_PTRS(k); j++)
					अगर (ptr_available(c, k, j))
						atomic_inc(&PTR_BUCKET(c, k, j)->pin);

				bch_initial_mark_key(c, 0, k);
			पूर्ण
	पूर्ण
पूर्ण

अटल bool is_discard_enabled(काष्ठा cache_set *s)
अणु
	काष्ठा cache *ca = s->cache;

	अगर (ca->discard)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक bch_journal_replay(काष्ठा cache_set *s, काष्ठा list_head *list)
अणु
	पूर्णांक ret = 0, keys = 0, entries = 0;
	काष्ठा bkey *k;
	काष्ठा journal_replay *i =
		list_entry(list->prev, काष्ठा journal_replay, list);

	uपूर्णांक64_t start = i->j.last_seq, end = i->j.seq, n = start;
	काष्ठा keylist keylist;

	list_क्रम_each_entry(i, list, list) अणु
		BUG_ON(i->pin && atomic_पढ़ो(i->pin) != 1);

		अगर (n != i->j.seq) अणु
			अगर (n == start && is_discard_enabled(s))
				pr_info("journal entries %llu-%llu may be discarded! (replaying %llu-%llu)\n",
					n, i->j.seq - 1, start, end);
			अन्यथा अणु
				pr_err("journal entries %llu-%llu missing! (replaying %llu-%llu)\n",
					n, i->j.seq - 1, start, end);
				ret = -EIO;
				जाओ err;
			पूर्ण
		पूर्ण

		क्रम (k = i->j.start;
		     k < bset_bkey_last(&i->j);
		     k = bkey_next(k)) अणु
			trace_bcache_journal_replay_key(k);

			bch_keylist_init_single(&keylist, k);

			ret = bch_btree_insert(s, &keylist, i->pin, शून्य);
			अगर (ret)
				जाओ err;

			BUG_ON(!bch_keylist_empty(&keylist));
			keys++;

			cond_resched();
		पूर्ण

		अगर (i->pin)
			atomic_dec(i->pin);
		n = i->j.seq + 1;
		entries++;
	पूर्ण

	pr_info("journal replay done, %i keys in %i entries, seq %llu\n",
		keys, entries, end);
err:
	जबतक (!list_empty(list)) अणु
		i = list_first_entry(list, काष्ठा journal_replay, list);
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण

	वापस ret;
पूर्ण

/* Journalling */

अटल व्योम btree_flush_ग_लिखो(काष्ठा cache_set *c)
अणु
	काष्ठा btree *b, *t, *btree_nodes[BTREE_FLUSH_NR];
	अचिन्हित पूर्णांक i, nr;
	पूर्णांक ref_nr;
	atomic_t *fअगरo_front_p, *now_fअगरo_front_p;
	माप_प्रकार mask;

	अगर (c->journal.btree_flushing)
		वापस;

	spin_lock(&c->journal.flush_ग_लिखो_lock);
	अगर (c->journal.btree_flushing) अणु
		spin_unlock(&c->journal.flush_ग_लिखो_lock);
		वापस;
	पूर्ण
	c->journal.btree_flushing = true;
	spin_unlock(&c->journal.flush_ग_लिखो_lock);

	/* get the oldest journal entry and check its refcount */
	spin_lock(&c->journal.lock);
	fअगरo_front_p = &fअगरo_front(&c->journal.pin);
	ref_nr = atomic_पढ़ो(fअगरo_front_p);
	अगर (ref_nr <= 0) अणु
		/*
		 * करो nothing अगर no btree node references
		 * the oldest journal entry
		 */
		spin_unlock(&c->journal.lock);
		जाओ out;
	पूर्ण
	spin_unlock(&c->journal.lock);

	mask = c->journal.pin.mask;
	nr = 0;
	atomic_दीर्घ_inc(&c->flush_ग_लिखो);
	स_रखो(btree_nodes, 0, माप(btree_nodes));

	mutex_lock(&c->bucket_lock);
	list_क्रम_each_entry_safe_reverse(b, t, &c->btree_cache, list) अणु
		/*
		 * It is safe to get now_fअगरo_front_p without holding
		 * c->journal.lock here, because we करोn't need to know
		 * the exactly accurate value, just check whether the
		 * front poपूर्णांकer of c->journal.pin is changed.
		 */
		now_fअगरo_front_p = &fअगरo_front(&c->journal.pin);
		/*
		 * If the oldest journal entry is reclaimed and front
		 * poपूर्णांकer of c->journal.pin changes, it is unnecessary
		 * to scan c->btree_cache anymore, just quit the loop and
		 * flush out what we have alपढ़ोy.
		 */
		अगर (now_fअगरo_front_p != fअगरo_front_p)
			अवरोध;
		/*
		 * quit this loop अगर all matching btree nodes are
		 * scanned and record in btree_nodes[] alपढ़ोy.
		 */
		ref_nr = atomic_पढ़ो(fअगरo_front_p);
		अगर (nr >= ref_nr)
			अवरोध;

		अगर (btree_node_journal_flush(b))
			pr_err("BUG: flush_write bit should not be set here!\n");

		mutex_lock(&b->ग_लिखो_lock);

		अगर (!btree_node_dirty(b)) अणु
			mutex_unlock(&b->ग_लिखो_lock);
			जारी;
		पूर्ण

		अगर (!btree_current_ग_लिखो(b)->journal) अणु
			mutex_unlock(&b->ग_लिखो_lock);
			जारी;
		पूर्ण

		/*
		 * Only select the btree node which exactly references
		 * the oldest journal entry.
		 *
		 * If the journal entry poपूर्णांकed by fअगरo_front_p is
		 * reclaimed in parallel, करोn't worry:
		 * - the list_क्रम_each_xxx loop will quit when checking
		 *   next now_fअगरo_front_p.
		 * - If there are matched nodes recorded in btree_nodes[],
		 *   they are clean now (this is why and how the oldest
		 *   journal entry can be reclaimed). These selected nodes
		 *   will be ignored and skipped in the following क्रम-loop.
		 */
		अगर (((btree_current_ग_लिखो(b)->journal - fअगरo_front_p) &
		     mask) != 0) अणु
			mutex_unlock(&b->ग_लिखो_lock);
			जारी;
		पूर्ण

		set_btree_node_journal_flush(b);

		mutex_unlock(&b->ग_लिखो_lock);

		btree_nodes[nr++] = b;
		/*
		 * To aव्योम holding c->bucket_lock too दीर्घ समय,
		 * only scan क्रम BTREE_FLUSH_NR matched btree nodes
		 * at most. If there are more btree nodes reference
		 * the oldest journal entry, try to flush them next
		 * समय when btree_flush_ग_लिखो() is called.
		 */
		अगर (nr == BTREE_FLUSH_NR)
			अवरोध;
	पूर्ण
	mutex_unlock(&c->bucket_lock);

	क्रम (i = 0; i < nr; i++) अणु
		b = btree_nodes[i];
		अगर (!b) अणु
			pr_err("BUG: btree_nodes[%d] is NULL\n", i);
			जारी;
		पूर्ण

		/* safe to check without holding b->ग_लिखो_lock */
		अगर (!btree_node_journal_flush(b)) अणु
			pr_err("BUG: bnode %p: journal_flush bit cleaned\n", b);
			जारी;
		पूर्ण

		mutex_lock(&b->ग_लिखो_lock);
		अगर (!btree_current_ग_लिखो(b)->journal) अणु
			clear_bit(BTREE_NODE_journal_flush, &b->flags);
			mutex_unlock(&b->ग_लिखो_lock);
			pr_debug("bnode %p: written by others\n", b);
			जारी;
		पूर्ण

		अगर (!btree_node_dirty(b)) अणु
			clear_bit(BTREE_NODE_journal_flush, &b->flags);
			mutex_unlock(&b->ग_लिखो_lock);
			pr_debug("bnode %p: dirty bit cleaned by others\n", b);
			जारी;
		पूर्ण

		__bch_btree_node_ग_लिखो(b, शून्य);
		clear_bit(BTREE_NODE_journal_flush, &b->flags);
		mutex_unlock(&b->ग_लिखो_lock);
	पूर्ण

out:
	spin_lock(&c->journal.flush_ग_लिखो_lock);
	c->journal.btree_flushing = false;
	spin_unlock(&c->journal.flush_ग_लिखो_lock);
पूर्ण

#घोषणा last_seq(j)	((j)->seq - fअगरo_used(&(j)->pin) + 1)

अटल व्योम journal_discard_endio(काष्ठा bio *bio)
अणु
	काष्ठा journal_device *ja =
		container_of(bio, काष्ठा journal_device, discard_bio);
	काष्ठा cache *ca = container_of(ja, काष्ठा cache, journal);

	atomic_set(&ja->discard_in_flight, DISCARD_DONE);

	closure_wake_up(&ca->set->journal.रुको);
	closure_put(&ca->set->cl);
पूर्ण

अटल व्योम journal_discard_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा journal_device *ja =
		container_of(work, काष्ठा journal_device, discard_work);

	submit_bio(&ja->discard_bio);
पूर्ण

अटल व्योम करो_journal_discard(काष्ठा cache *ca)
अणु
	काष्ठा journal_device *ja = &ca->journal;
	काष्ठा bio *bio = &ja->discard_bio;

	अगर (!ca->discard) अणु
		ja->discard_idx = ja->last_idx;
		वापस;
	पूर्ण

	चयन (atomic_पढ़ो(&ja->discard_in_flight)) अणु
	हाल DISCARD_IN_FLIGHT:
		वापस;

	हाल DISCARD_DONE:
		ja->discard_idx = (ja->discard_idx + 1) %
			ca->sb.njournal_buckets;

		atomic_set(&ja->discard_in_flight, DISCARD_READY);
		fallthrough;

	हाल DISCARD_READY:
		अगर (ja->discard_idx == ja->last_idx)
			वापस;

		atomic_set(&ja->discard_in_flight, DISCARD_IN_FLIGHT);

		bio_init(bio, bio->bi_अंतरभूत_vecs, 1);
		bio_set_op_attrs(bio, REQ_OP_DISCARD, 0);
		bio->bi_iter.bi_sector	= bucket_to_sector(ca->set,
						ca->sb.d[ja->discard_idx]);
		bio_set_dev(bio, ca->bdev);
		bio->bi_iter.bi_size	= bucket_bytes(ca);
		bio->bi_end_io		= journal_discard_endio;

		closure_get(&ca->set->cl);
		INIT_WORK(&ja->discard_work, journal_discard_work);
		queue_work(bch_journal_wq, &ja->discard_work);
	पूर्ण
पूर्ण

अटल व्योम journal_reclaim(काष्ठा cache_set *c)
अणु
	काष्ठा bkey *k = &c->journal.key;
	काष्ठा cache *ca = c->cache;
	uपूर्णांक64_t last_seq;
	अचिन्हित पूर्णांक next;
	काष्ठा journal_device *ja = &ca->journal;
	atomic_t p __maybe_unused;

	atomic_दीर्घ_inc(&c->reclaim);

	जबतक (!atomic_पढ़ो(&fअगरo_front(&c->journal.pin)))
		fअगरo_pop(&c->journal.pin, p);

	last_seq = last_seq(&c->journal);

	/* Update last_idx */

	जबतक (ja->last_idx != ja->cur_idx &&
	       ja->seq[ja->last_idx] < last_seq)
		ja->last_idx = (ja->last_idx + 1) %
			ca->sb.njournal_buckets;

	करो_journal_discard(ca);

	अगर (c->journal.blocks_मुक्त)
		जाओ out;

	next = (ja->cur_idx + 1) % ca->sb.njournal_buckets;
	/* No space available on this device */
	अगर (next == ja->discard_idx)
		जाओ out;

	ja->cur_idx = next;
	k->ptr[0] = MAKE_PTR(0,
			     bucket_to_sector(c, ca->sb.d[ja->cur_idx]),
			     ca->sb.nr_this_dev);
	atomic_दीर्घ_inc(&c->reclaimed_journal_buckets);

	bkey_init(k);
	SET_KEY_PTRS(k, 1);
	c->journal.blocks_मुक्त = ca->sb.bucket_size >> c->block_bits;

out:
	अगर (!journal_full(&c->journal))
		__closure_wake_up(&c->journal.रुको);
पूर्ण

व्योम bch_journal_next(काष्ठा journal *j)
अणु
	atomic_t p = अणु 1 पूर्ण;

	j->cur = (j->cur == j->w)
		? &j->w[1]
		: &j->w[0];

	/*
	 * The fअगरo_push() needs to happen at the same समय as j->seq is
	 * incremented क्रम last_seq() to be calculated correctly
	 */
	BUG_ON(!fअगरo_push(&j->pin, p));
	atomic_set(&fअगरo_back(&j->pin), 1);

	j->cur->data->seq	= ++j->seq;
	j->cur->dirty		= false;
	j->cur->need_ग_लिखो	= false;
	j->cur->data->keys	= 0;

	अगर (fअगरo_full(&j->pin))
		pr_debug("journal_pin full (%zu)\n", fअगरo_used(&j->pin));
पूर्ण

अटल व्योम journal_ग_लिखो_endio(काष्ठा bio *bio)
अणु
	काष्ठा journal_ग_लिखो *w = bio->bi_निजी;

	cache_set_err_on(bio->bi_status, w->c, "journal io error");
	closure_put(&w->c->journal.io);
पूर्ण

अटल व्योम journal_ग_लिखो(काष्ठा closure *cl);

अटल व्योम journal_ग_लिखो_करोne(काष्ठा closure *cl)
अणु
	काष्ठा journal *j = container_of(cl, काष्ठा journal, io);
	काष्ठा journal_ग_लिखो *w = (j->cur == j->w)
		? &j->w[1]
		: &j->w[0];

	__closure_wake_up(&w->रुको);
	जारी_at_nobarrier(cl, journal_ग_लिखो, bch_journal_wq);
पूर्ण

अटल व्योम journal_ग_लिखो_unlock(काष्ठा closure *cl)
	__releases(&c->journal.lock)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, journal.io);

	c->journal.io_in_flight = 0;
	spin_unlock(&c->journal.lock);
पूर्ण

अटल व्योम journal_ग_लिखो_unlocked(काष्ठा closure *cl)
	__releases(c->journal.lock)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, journal.io);
	काष्ठा cache *ca = c->cache;
	काष्ठा journal_ग_लिखो *w = c->journal.cur;
	काष्ठा bkey *k = &c->journal.key;
	अचिन्हित पूर्णांक i, sectors = set_blocks(w->data, block_bytes(ca)) *
		ca->sb.block_size;

	काष्ठा bio *bio;
	काष्ठा bio_list list;

	bio_list_init(&list);

	अगर (!w->need_ग_लिखो) अणु
		closure_वापस_with_deकाष्ठाor(cl, journal_ग_लिखो_unlock);
		वापस;
	पूर्ण अन्यथा अगर (journal_full(&c->journal)) अणु
		journal_reclaim(c);
		spin_unlock(&c->journal.lock);

		btree_flush_ग_लिखो(c);
		जारी_at(cl, journal_ग_लिखो, bch_journal_wq);
		वापस;
	पूर्ण

	c->journal.blocks_मुक्त -= set_blocks(w->data, block_bytes(ca));

	w->data->btree_level = c->root->level;

	bkey_copy(&w->data->btree_root, &c->root->key);
	bkey_copy(&w->data->uuid_bucket, &c->uuid_bucket);

	w->data->prio_bucket[ca->sb.nr_this_dev] = ca->prio_buckets[0];
	w->data->magic		= jset_magic(&ca->sb);
	w->data->version	= BCACHE_JSET_VERSION;
	w->data->last_seq	= last_seq(&c->journal);
	w->data->csum		= csum_set(w->data);

	क्रम (i = 0; i < KEY_PTRS(k); i++) अणु
		ca = c->cache;
		bio = &ca->journal.bio;

		atomic_दीर्घ_add(sectors, &ca->meta_sectors_written);

		bio_reset(bio);
		bio->bi_iter.bi_sector	= PTR_OFFSET(k, i);
		bio_set_dev(bio, ca->bdev);
		bio->bi_iter.bi_size = sectors << 9;

		bio->bi_end_io	= journal_ग_लिखो_endio;
		bio->bi_निजी = w;
		bio_set_op_attrs(bio, REQ_OP_WRITE,
				 REQ_SYNC|REQ_META|REQ_PREFLUSH|REQ_FUA);
		bch_bio_map(bio, w->data);

		trace_bcache_journal_ग_लिखो(bio, w->data->keys);
		bio_list_add(&list, bio);

		SET_PTR_OFFSET(k, i, PTR_OFFSET(k, i) + sectors);

		ca->journal.seq[ca->journal.cur_idx] = w->data->seq;
	पूर्ण

	/* If KEY_PTRS(k) == 0, this jset माला_लो lost in air */
	BUG_ON(i == 0);

	atomic_dec_bug(&fअगरo_back(&c->journal.pin));
	bch_journal_next(&c->journal);
	journal_reclaim(c);

	spin_unlock(&c->journal.lock);

	जबतक ((bio = bio_list_pop(&list)))
		closure_bio_submit(c, bio, cl);

	जारी_at(cl, journal_ग_लिखो_करोne, शून्य);
पूर्ण

अटल व्योम journal_ग_लिखो(काष्ठा closure *cl)
अणु
	काष्ठा cache_set *c = container_of(cl, काष्ठा cache_set, journal.io);

	spin_lock(&c->journal.lock);
	journal_ग_लिखो_unlocked(cl);
पूर्ण

अटल व्योम journal_try_ग_लिखो(काष्ठा cache_set *c)
	__releases(c->journal.lock)
अणु
	काष्ठा closure *cl = &c->journal.io;
	काष्ठा journal_ग_लिखो *w = c->journal.cur;

	w->need_ग_लिखो = true;

	अगर (!c->journal.io_in_flight) अणु
		c->journal.io_in_flight = 1;
		closure_call(cl, journal_ग_लिखो_unlocked, शून्य, &c->cl);
	पूर्ण अन्यथा अणु
		spin_unlock(&c->journal.lock);
	पूर्ण
पूर्ण

अटल काष्ठा journal_ग_लिखो *journal_रुको_क्रम_ग_लिखो(काष्ठा cache_set *c,
						    अचिन्हित पूर्णांक nkeys)
	__acquires(&c->journal.lock)
अणु
	माप_प्रकार sectors;
	काष्ठा closure cl;
	bool रुको = false;
	काष्ठा cache *ca = c->cache;

	closure_init_stack(&cl);

	spin_lock(&c->journal.lock);

	जबतक (1) अणु
		काष्ठा journal_ग_लिखो *w = c->journal.cur;

		sectors = __set_blocks(w->data, w->data->keys + nkeys,
				       block_bytes(ca)) * ca->sb.block_size;

		अगर (sectors <= min_t(माप_प्रकार,
				     c->journal.blocks_मुक्त * ca->sb.block_size,
				     PAGE_SECTORS << JSET_BITS))
			वापस w;

		अगर (रुको)
			closure_रुको(&c->journal.रुको, &cl);

		अगर (!journal_full(&c->journal)) अणु
			अगर (रुको)
				trace_bcache_journal_entry_full(c);

			/*
			 * XXX: If we were inserting so many keys that they
			 * won't fit in an _empty_ journal write, we'll
			 * deadlock. For now, handle this in
			 * bch_keylist_पुनः_स्मृति() - but something to think about.
			 */
			BUG_ON(!w->data->keys);

			journal_try_ग_लिखो(c); /* unlocks */
		पूर्ण अन्यथा अणु
			अगर (रुको)
				trace_bcache_journal_full(c);

			journal_reclaim(c);
			spin_unlock(&c->journal.lock);

			btree_flush_ग_लिखो(c);
		पूर्ण

		closure_sync(&cl);
		spin_lock(&c->journal.lock);
		रुको = true;
	पूर्ण
पूर्ण

अटल व्योम journal_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cache_set *c = container_of(to_delayed_work(work),
					   काष्ठा cache_set,
					   journal.work);
	spin_lock(&c->journal.lock);
	अगर (c->journal.cur->dirty)
		journal_try_ग_लिखो(c);
	अन्यथा
		spin_unlock(&c->journal.lock);
पूर्ण

/*
 * Entry poपूर्णांक to the journalling code - bio_insert() and btree_invalidate()
 * pass bch_journal() a list of keys to be journalled, and then
 * bch_journal() hands those same keys off to btree_insert_async()
 */

atomic_t *bch_journal(काष्ठा cache_set *c,
		      काष्ठा keylist *keys,
		      काष्ठा closure *parent)
अणु
	काष्ठा journal_ग_लिखो *w;
	atomic_t *ret;

	/* No journaling अगर CACHE_SET_IO_DISABLE set alपढ़ोy */
	अगर (unlikely(test_bit(CACHE_SET_IO_DISABLE, &c->flags)))
		वापस शून्य;

	अगर (!CACHE_SYNC(&c->cache->sb))
		वापस शून्य;

	w = journal_रुको_क्रम_ग_लिखो(c, bch_keylist_nkeys(keys));

	स_नकल(bset_bkey_last(w->data), keys->keys, bch_keylist_bytes(keys));
	w->data->keys += bch_keylist_nkeys(keys);

	ret = &fअगरo_back(&c->journal.pin);
	atomic_inc(ret);

	अगर (parent) अणु
		closure_रुको(&w->रुको, parent);
		journal_try_ग_लिखो(c);
	पूर्ण अन्यथा अगर (!w->dirty) अणु
		w->dirty = true;
		queue_delayed_work(bch_flush_wq, &c->journal.work,
				   msecs_to_jअगरfies(c->journal_delay_ms));
		spin_unlock(&c->journal.lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&c->journal.lock);
	पूर्ण


	वापस ret;
पूर्ण

व्योम bch_journal_meta(काष्ठा cache_set *c, काष्ठा closure *cl)
अणु
	काष्ठा keylist keys;
	atomic_t *ref;

	bch_keylist_init(&keys);

	ref = bch_journal(c, &keys, cl);
	अगर (ref)
		atomic_dec_bug(ref);
पूर्ण

व्योम bch_journal_मुक्त(काष्ठा cache_set *c)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) c->journal.w[1].data, JSET_BITS);
	मुक्त_pages((अचिन्हित दीर्घ) c->journal.w[0].data, JSET_BITS);
	मुक्त_fअगरo(&c->journal.pin);
पूर्ण

पूर्णांक bch_journal_alloc(काष्ठा cache_set *c)
अणु
	काष्ठा journal *j = &c->journal;

	spin_lock_init(&j->lock);
	spin_lock_init(&j->flush_ग_लिखो_lock);
	INIT_DELAYED_WORK(&j->work, journal_ग_लिखो_work);

	c->journal_delay_ms = 100;

	j->w[0].c = c;
	j->w[1].c = c;

	अगर (!(init_fअगरo(&j->pin, JOURNAL_PIN, GFP_KERNEL)) ||
	    !(j->w[0].data = (व्योम *) __get_मुक्त_pages(GFP_KERNEL|__GFP_COMP, JSET_BITS)) ||
	    !(j->w[1].data = (व्योम *) __get_मुक्त_pages(GFP_KERNEL|__GFP_COMP, JSET_BITS)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
