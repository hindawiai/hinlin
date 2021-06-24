<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-cache-background-tracker.h"
#समावेश "dm-cache-policy-internal.h"
#समावेश "dm-cache-policy.h"
#समावेश "dm.h"

#समावेश <linux/hash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/math64.h>

#घोषणा DM_MSG_PREFIX "cache-policy-smq"

/*----------------------------------------------------------------*/

/*
 * Safe भागision functions that वापस zero on भागide by zero.
 */
अटल अचिन्हित safe_भाग(अचिन्हित n, अचिन्हित d)
अणु
	वापस d ? n / d : 0u;
पूर्ण

अटल अचिन्हित safe_mod(अचिन्हित n, अचिन्हित d)
अणु
	वापस d ? n % d : 0u;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा entry अणु
	अचिन्हित hash_next:28;
	अचिन्हित prev:28;
	अचिन्हित next:28;
	अचिन्हित level:6;
	bool dirty:1;
	bool allocated:1;
	bool sentinel:1;
	bool pending_work:1;

	dm_oblock_t oblock;
पूर्ण;

/*----------------------------------------------------------------*/

#घोषणा INDEXER_शून्य ((1u << 28u) - 1u)

/*
 * An entry_space manages a set of entries that we use क्रम the queues.
 * The clean and dirty queues share entries, so this object is separate
 * from the queue itself.
 */
काष्ठा entry_space अणु
	काष्ठा entry *begin;
	काष्ठा entry *end;
पूर्ण;

अटल पूर्णांक space_init(काष्ठा entry_space *es, अचिन्हित nr_entries)
अणु
	अगर (!nr_entries) अणु
		es->begin = es->end = शून्य;
		वापस 0;
	पूर्ण

	es->begin = vzalloc(array_size(nr_entries, माप(काष्ठा entry)));
	अगर (!es->begin)
		वापस -ENOMEM;

	es->end = es->begin + nr_entries;
	वापस 0;
पूर्ण

अटल व्योम space_निकास(काष्ठा entry_space *es)
अणु
	vमुक्त(es->begin);
पूर्ण

अटल काष्ठा entry *__get_entry(काष्ठा entry_space *es, अचिन्हित block)
अणु
	काष्ठा entry *e;

	e = es->begin + block;
	BUG_ON(e >= es->end);

	वापस e;
पूर्ण

अटल अचिन्हित to_index(काष्ठा entry_space *es, काष्ठा entry *e)
अणु
	BUG_ON(e < es->begin || e >= es->end);
	वापस e - es->begin;
पूर्ण

अटल काष्ठा entry *to_entry(काष्ठा entry_space *es, अचिन्हित block)
अणु
	अगर (block == INDEXER_शून्य)
		वापस शून्य;

	वापस __get_entry(es, block);
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा ilist अणु
	अचिन्हित nr_elts;	/* excluding sentinel entries */
	अचिन्हित head, tail;
पूर्ण;

अटल व्योम l_init(काष्ठा ilist *l)
अणु
	l->nr_elts = 0;
	l->head = l->tail = INDEXER_शून्य;
पूर्ण

अटल काष्ठा entry *l_head(काष्ठा entry_space *es, काष्ठा ilist *l)
अणु
	वापस to_entry(es, l->head);
पूर्ण

अटल काष्ठा entry *l_tail(काष्ठा entry_space *es, काष्ठा ilist *l)
अणु
	वापस to_entry(es, l->tail);
पूर्ण

अटल काष्ठा entry *l_next(काष्ठा entry_space *es, काष्ठा entry *e)
अणु
	वापस to_entry(es, e->next);
पूर्ण

अटल काष्ठा entry *l_prev(काष्ठा entry_space *es, काष्ठा entry *e)
अणु
	वापस to_entry(es, e->prev);
पूर्ण

अटल bool l_empty(काष्ठा ilist *l)
अणु
	वापस l->head == INDEXER_शून्य;
पूर्ण

अटल व्योम l_add_head(काष्ठा entry_space *es, काष्ठा ilist *l, काष्ठा entry *e)
अणु
	काष्ठा entry *head = l_head(es, l);

	e->next = l->head;
	e->prev = INDEXER_शून्य;

	अगर (head)
		head->prev = l->head = to_index(es, e);
	अन्यथा
		l->head = l->tail = to_index(es, e);

	अगर (!e->sentinel)
		l->nr_elts++;
पूर्ण

अटल व्योम l_add_tail(काष्ठा entry_space *es, काष्ठा ilist *l, काष्ठा entry *e)
अणु
	काष्ठा entry *tail = l_tail(es, l);

	e->next = INDEXER_शून्य;
	e->prev = l->tail;

	अगर (tail)
		tail->next = l->tail = to_index(es, e);
	अन्यथा
		l->head = l->tail = to_index(es, e);

	अगर (!e->sentinel)
		l->nr_elts++;
पूर्ण

अटल व्योम l_add_beक्रमe(काष्ठा entry_space *es, काष्ठा ilist *l,
			 काष्ठा entry *old, काष्ठा entry *e)
अणु
	काष्ठा entry *prev = l_prev(es, old);

	अगर (!prev)
		l_add_head(es, l, e);

	अन्यथा अणु
		e->prev = old->prev;
		e->next = to_index(es, old);
		prev->next = old->prev = to_index(es, e);

		अगर (!e->sentinel)
			l->nr_elts++;
	पूर्ण
पूर्ण

अटल व्योम l_del(काष्ठा entry_space *es, काष्ठा ilist *l, काष्ठा entry *e)
अणु
	काष्ठा entry *prev = l_prev(es, e);
	काष्ठा entry *next = l_next(es, e);

	अगर (prev)
		prev->next = e->next;
	अन्यथा
		l->head = e->next;

	अगर (next)
		next->prev = e->prev;
	अन्यथा
		l->tail = e->prev;

	अगर (!e->sentinel)
		l->nr_elts--;
पूर्ण

अटल काष्ठा entry *l_pop_head(काष्ठा entry_space *es, काष्ठा ilist *l)
अणु
	काष्ठा entry *e;

	क्रम (e = l_head(es, l); e; e = l_next(es, e))
		अगर (!e->sentinel) अणु
			l_del(es, l, e);
			वापस e;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा entry *l_pop_tail(काष्ठा entry_space *es, काष्ठा ilist *l)
अणु
	काष्ठा entry *e;

	क्रम (e = l_tail(es, l); e; e = l_prev(es, e))
		अगर (!e->sentinel) अणु
			l_del(es, l, e);
			वापस e;
		पूर्ण

	वापस शून्य;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * The stochastic-multi-queue is a set of lru lists stacked पूर्णांकo levels.
 * Entries are moved up levels when they are used, which loosely orders the
 * most accessed entries in the top levels and least in the bottom.  This
 * काष्ठाure is *much* better than a single lru list.
 */
#घोषणा MAX_LEVELS 64u

काष्ठा queue अणु
	काष्ठा entry_space *es;

	अचिन्हित nr_elts;
	अचिन्हित nr_levels;
	काष्ठा ilist qs[MAX_LEVELS];

	/*
	 * We मुख्यtain a count of the number of entries we would like in each
	 * level.
	 */
	अचिन्हित last_target_nr_elts;
	अचिन्हित nr_top_levels;
	अचिन्हित nr_in_top_levels;
	अचिन्हित target_count[MAX_LEVELS];
पूर्ण;

अटल व्योम q_init(काष्ठा queue *q, काष्ठा entry_space *es, अचिन्हित nr_levels)
अणु
	अचिन्हित i;

	q->es = es;
	q->nr_elts = 0;
	q->nr_levels = nr_levels;

	क्रम (i = 0; i < q->nr_levels; i++) अणु
		l_init(q->qs + i);
		q->target_count[i] = 0u;
	पूर्ण

	q->last_target_nr_elts = 0u;
	q->nr_top_levels = 0u;
	q->nr_in_top_levels = 0u;
पूर्ण

अटल अचिन्हित q_size(काष्ठा queue *q)
अणु
	वापस q->nr_elts;
पूर्ण

/*
 * Insert an entry to the back of the given level.
 */
अटल व्योम q_push(काष्ठा queue *q, काष्ठा entry *e)
अणु
	BUG_ON(e->pending_work);

	अगर (!e->sentinel)
		q->nr_elts++;

	l_add_tail(q->es, q->qs + e->level, e);
पूर्ण

अटल व्योम q_push_front(काष्ठा queue *q, काष्ठा entry *e)
अणु
	BUG_ON(e->pending_work);

	अगर (!e->sentinel)
		q->nr_elts++;

	l_add_head(q->es, q->qs + e->level, e);
पूर्ण

अटल व्योम q_push_beक्रमe(काष्ठा queue *q, काष्ठा entry *old, काष्ठा entry *e)
अणु
	BUG_ON(e->pending_work);

	अगर (!e->sentinel)
		q->nr_elts++;

	l_add_beक्रमe(q->es, q->qs + e->level, old, e);
पूर्ण

अटल व्योम q_del(काष्ठा queue *q, काष्ठा entry *e)
अणु
	l_del(q->es, q->qs + e->level, e);
	अगर (!e->sentinel)
		q->nr_elts--;
पूर्ण

/*
 * Return the oldest entry of the lowest populated level.
 */
अटल काष्ठा entry *q_peek(काष्ठा queue *q, अचिन्हित max_level, bool can_cross_sentinel)
अणु
	अचिन्हित level;
	काष्ठा entry *e;

	max_level = min(max_level, q->nr_levels);

	क्रम (level = 0; level < max_level; level++)
		क्रम (e = l_head(q->es, q->qs + level); e; e = l_next(q->es, e)) अणु
			अगर (e->sentinel) अणु
				अगर (can_cross_sentinel)
					जारी;
				अन्यथा
					अवरोध;
			पूर्ण

			वापस e;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा entry *q_pop(काष्ठा queue *q)
अणु
	काष्ठा entry *e = q_peek(q, q->nr_levels, true);

	अगर (e)
		q_del(q, e);

	वापस e;
पूर्ण

/*
 * This function assumes there is a non-sentinel entry to pop.  It's only
 * used by redistribute, so we know this is true.  It also करोesn't adjust
 * the q->nr_elts count.
 */
अटल काष्ठा entry *__redist_pop_from(काष्ठा queue *q, अचिन्हित level)
अणु
	काष्ठा entry *e;

	क्रम (; level < q->nr_levels; level++)
		क्रम (e = l_head(q->es, q->qs + level); e; e = l_next(q->es, e))
			अगर (!e->sentinel) अणु
				l_del(q->es, q->qs + e->level, e);
				वापस e;
			पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम q_set_tarमाला_लो_subrange_(काष्ठा queue *q, अचिन्हित nr_elts, अचिन्हित lbegin, अचिन्हित lend)
अणु
	अचिन्हित level, nr_levels, entries_per_level, reमुख्यder;

	BUG_ON(lbegin > lend);
	BUG_ON(lend > q->nr_levels);
	nr_levels = lend - lbegin;
	entries_per_level = safe_भाग(nr_elts, nr_levels);
	reमुख्यder = safe_mod(nr_elts, nr_levels);

	क्रम (level = lbegin; level < lend; level++)
		q->target_count[level] =
			(level < (lbegin + reमुख्यder)) ? entries_per_level + 1u : entries_per_level;
पूर्ण

/*
 * Typically we have fewer elements in the top few levels which allows us
 * to adjust the promote threshold nicely.
 */
अटल व्योम q_set_tarमाला_लो(काष्ठा queue *q)
अणु
	अगर (q->last_target_nr_elts == q->nr_elts)
		वापस;

	q->last_target_nr_elts = q->nr_elts;

	अगर (q->nr_top_levels > q->nr_levels)
		q_set_tarमाला_लो_subrange_(q, q->nr_elts, 0, q->nr_levels);

	अन्यथा अणु
		q_set_tarमाला_लो_subrange_(q, q->nr_in_top_levels,
					q->nr_levels - q->nr_top_levels, q->nr_levels);

		अगर (q->nr_in_top_levels < q->nr_elts)
			q_set_tarमाला_लो_subrange_(q, q->nr_elts - q->nr_in_top_levels,
						0, q->nr_levels - q->nr_top_levels);
		अन्यथा
			q_set_tarमाला_लो_subrange_(q, 0, 0, q->nr_levels - q->nr_top_levels);
	पूर्ण
पूर्ण

अटल व्योम q_redistribute(काष्ठा queue *q)
अणु
	अचिन्हित target, level;
	काष्ठा ilist *l, *l_above;
	काष्ठा entry *e;

	q_set_tarमाला_लो(q);

	क्रम (level = 0u; level < q->nr_levels - 1u; level++) अणु
		l = q->qs + level;
		target = q->target_count[level];

		/*
		 * Pull करोwn some entries from the level above.
		 */
		जबतक (l->nr_elts < target) अणु
			e = __redist_pop_from(q, level + 1u);
			अगर (!e) अणु
				/* bug in nr_elts */
				अवरोध;
			पूर्ण

			e->level = level;
			l_add_tail(q->es, l, e);
		पूर्ण

		/*
		 * Push some entries up.
		 */
		l_above = q->qs + level + 1u;
		जबतक (l->nr_elts > target) अणु
			e = l_pop_tail(q->es, l);

			अगर (!e)
				/* bug in nr_elts */
				अवरोध;

			e->level = level + 1u;
			l_add_tail(q->es, l_above, e);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम q_requeue(काष्ठा queue *q, काष्ठा entry *e, अचिन्हित extra_levels,
		      काष्ठा entry *s1, काष्ठा entry *s2)
अणु
	काष्ठा entry *de;
	अचिन्हित sentinels_passed = 0;
	अचिन्हित new_level = min(q->nr_levels - 1u, e->level + extra_levels);

	/* try and find an entry to swap with */
	अगर (extra_levels && (e->level < q->nr_levels - 1u)) अणु
		क्रम (de = l_head(q->es, q->qs + new_level); de && de->sentinel; de = l_next(q->es, de))
			sentinels_passed++;

		अगर (de) अणु
			q_del(q, de);
			de->level = e->level;
			अगर (s1) अणु
				चयन (sentinels_passed) अणु
				हाल 0:
					q_push_beक्रमe(q, s1, de);
					अवरोध;

				हाल 1:
					q_push_beक्रमe(q, s2, de);
					अवरोध;

				शेष:
					q_push(q, de);
				पूर्ण
			पूर्ण अन्यथा
				q_push(q, de);
		पूर्ण
	पूर्ण

	q_del(q, e);
	e->level = new_level;
	q_push(q, e);
पूर्ण

/*----------------------------------------------------------------*/

#घोषणा FP_SHIFT 8
#घोषणा SIXTEENTH (1u << (FP_SHIFT - 4u))
#घोषणा EIGHTH (1u << (FP_SHIFT - 3u))

काष्ठा stats अणु
	अचिन्हित hit_threshold;
	अचिन्हित hits;
	अचिन्हित misses;
पूर्ण;

क्रमागत perक्रमmance अणु
	Q_POOR,
	Q_FAIR,
	Q_WELL
पूर्ण;

अटल व्योम stats_init(काष्ठा stats *s, अचिन्हित nr_levels)
अणु
	s->hit_threshold = (nr_levels * 3u) / 4u;
	s->hits = 0u;
	s->misses = 0u;
पूर्ण

अटल व्योम stats_reset(काष्ठा stats *s)
अणु
	s->hits = s->misses = 0u;
पूर्ण

अटल व्योम stats_level_accessed(काष्ठा stats *s, अचिन्हित level)
अणु
	अगर (level >= s->hit_threshold)
		s->hits++;
	अन्यथा
		s->misses++;
पूर्ण

अटल व्योम stats_miss(काष्ठा stats *s)
अणु
	s->misses++;
पूर्ण

/*
 * There are बार when we करोn't have any confidence in the hotspot queue.
 * Such as when a fresh cache is created and the blocks have been spपढ़ो
 * out across the levels, or अगर an io load changes.  We detect this by
 * seeing how often a lookup is in the top levels of the hotspot queue.
 */
अटल क्रमागत perक्रमmance stats_assess(काष्ठा stats *s)
अणु
	अचिन्हित confidence = safe_भाग(s->hits << FP_SHIFT, s->hits + s->misses);

	अगर (confidence < SIXTEENTH)
		वापस Q_POOR;

	अन्यथा अगर (confidence < EIGHTH)
		वापस Q_FAIR;

	अन्यथा
		वापस Q_WELL;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा smq_hash_table अणु
	काष्ठा entry_space *es;
	अचिन्हित दीर्घ दीर्घ hash_bits;
	अचिन्हित *buckets;
पूर्ण;

/*
 * All cache entries are stored in a chained hash table.  To save space we
 * use indexing again, and only store indexes to the next entry.
 */
अटल पूर्णांक h_init(काष्ठा smq_hash_table *ht, काष्ठा entry_space *es, अचिन्हित nr_entries)
अणु
	अचिन्हित i, nr_buckets;

	ht->es = es;
	nr_buckets = roundup_घात_of_two(max(nr_entries / 4u, 16u));
	ht->hash_bits = __ffs(nr_buckets);

	ht->buckets = vदो_स्मृति(array_size(nr_buckets, माप(*ht->buckets)));
	अगर (!ht->buckets)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_buckets; i++)
		ht->buckets[i] = INDEXER_शून्य;

	वापस 0;
पूर्ण

अटल व्योम h_निकास(काष्ठा smq_hash_table *ht)
अणु
	vमुक्त(ht->buckets);
पूर्ण

अटल काष्ठा entry *h_head(काष्ठा smq_hash_table *ht, अचिन्हित bucket)
अणु
	वापस to_entry(ht->es, ht->buckets[bucket]);
पूर्ण

अटल काष्ठा entry *h_next(काष्ठा smq_hash_table *ht, काष्ठा entry *e)
अणु
	वापस to_entry(ht->es, e->hash_next);
पूर्ण

अटल व्योम __h_insert(काष्ठा smq_hash_table *ht, अचिन्हित bucket, काष्ठा entry *e)
अणु
	e->hash_next = ht->buckets[bucket];
	ht->buckets[bucket] = to_index(ht->es, e);
पूर्ण

अटल व्योम h_insert(काष्ठा smq_hash_table *ht, काष्ठा entry *e)
अणु
	अचिन्हित h = hash_64(from_oblock(e->oblock), ht->hash_bits);
	__h_insert(ht, h, e);
पूर्ण

अटल काष्ठा entry *__h_lookup(काष्ठा smq_hash_table *ht, अचिन्हित h, dm_oblock_t oblock,
				काष्ठा entry **prev)
अणु
	काष्ठा entry *e;

	*prev = शून्य;
	क्रम (e = h_head(ht, h); e; e = h_next(ht, e)) अणु
		अगर (e->oblock == oblock)
			वापस e;

		*prev = e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __h_unlink(काष्ठा smq_hash_table *ht, अचिन्हित h,
		       काष्ठा entry *e, काष्ठा entry *prev)
अणु
	अगर (prev)
		prev->hash_next = e->hash_next;
	अन्यथा
		ht->buckets[h] = e->hash_next;
पूर्ण

/*
 * Also moves each entry to the front of the bucket.
 */
अटल काष्ठा entry *h_lookup(काष्ठा smq_hash_table *ht, dm_oblock_t oblock)
अणु
	काष्ठा entry *e, *prev;
	अचिन्हित h = hash_64(from_oblock(oblock), ht->hash_bits);

	e = __h_lookup(ht, h, oblock, &prev);
	अगर (e && prev) अणु
		/*
		 * Move to the front because this entry is likely
		 * to be hit again.
		 */
		__h_unlink(ht, h, e, prev);
		__h_insert(ht, h, e);
	पूर्ण

	वापस e;
पूर्ण

अटल व्योम h_हटाओ(काष्ठा smq_hash_table *ht, काष्ठा entry *e)
अणु
	अचिन्हित h = hash_64(from_oblock(e->oblock), ht->hash_bits);
	काष्ठा entry *prev;

	/*
	 * The करोwn side of using a singly linked list is we have to
	 * iterate the bucket to हटाओ an item.
	 */
	e = __h_lookup(ht, h, e->oblock, &prev);
	अगर (e)
		__h_unlink(ht, h, e, prev);
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा entry_alloc अणु
	काष्ठा entry_space *es;
	अचिन्हित begin;

	अचिन्हित nr_allocated;
	काष्ठा ilist मुक्त;
पूर्ण;

अटल व्योम init_allocator(काष्ठा entry_alloc *ea, काष्ठा entry_space *es,
			   अचिन्हित begin, अचिन्हित end)
अणु
	अचिन्हित i;

	ea->es = es;
	ea->nr_allocated = 0u;
	ea->begin = begin;

	l_init(&ea->मुक्त);
	क्रम (i = begin; i != end; i++)
		l_add_tail(ea->es, &ea->मुक्त, __get_entry(ea->es, i));
पूर्ण

अटल व्योम init_entry(काष्ठा entry *e)
अणु
	/*
	 * We can't स_रखो because that would clear the hotspot and
	 * sentinel bits which reमुख्य स्थिरant.
	 */
	e->hash_next = INDEXER_शून्य;
	e->next = INDEXER_शून्य;
	e->prev = INDEXER_शून्य;
	e->level = 0u;
	e->dirty = true;	/* FIXME: audit */
	e->allocated = true;
	e->sentinel = false;
	e->pending_work = false;
पूर्ण

अटल काष्ठा entry *alloc_entry(काष्ठा entry_alloc *ea)
अणु
	काष्ठा entry *e;

	अगर (l_empty(&ea->मुक्त))
		वापस शून्य;

	e = l_pop_head(ea->es, &ea->मुक्त);
	init_entry(e);
	ea->nr_allocated++;

	वापस e;
पूर्ण

/*
 * This assumes the cblock hasn't alपढ़ोy been allocated.
 */
अटल काष्ठा entry *alloc_particular_entry(काष्ठा entry_alloc *ea, अचिन्हित i)
अणु
	काष्ठा entry *e = __get_entry(ea->es, ea->begin + i);

	BUG_ON(e->allocated);

	l_del(ea->es, &ea->मुक्त, e);
	init_entry(e);
	ea->nr_allocated++;

	वापस e;
पूर्ण

अटल व्योम मुक्त_entry(काष्ठा entry_alloc *ea, काष्ठा entry *e)
अणु
	BUG_ON(!ea->nr_allocated);
	BUG_ON(!e->allocated);

	ea->nr_allocated--;
	e->allocated = false;
	l_add_tail(ea->es, &ea->मुक्त, e);
पूर्ण

अटल bool allocator_empty(काष्ठा entry_alloc *ea)
अणु
	वापस l_empty(&ea->मुक्त);
पूर्ण

अटल अचिन्हित get_index(काष्ठा entry_alloc *ea, काष्ठा entry *e)
अणु
	वापस to_index(ea->es, e) - ea->begin;
पूर्ण

अटल काष्ठा entry *get_entry(काष्ठा entry_alloc *ea, अचिन्हित index)
अणु
	वापस __get_entry(ea->es, ea->begin + index);
पूर्ण

/*----------------------------------------------------------------*/

#घोषणा NR_HOTSPOT_LEVELS 64u
#घोषणा NR_CACHE_LEVELS 64u

#घोषणा WRITEBACK_PERIOD (10ul * HZ)
#घोषणा DEMOTE_PERIOD (60ul * HZ)

#घोषणा HOTSPOT_UPDATE_PERIOD (HZ)
#घोषणा CACHE_UPDATE_PERIOD (60ul * HZ)

काष्ठा smq_policy अणु
	काष्ठा dm_cache_policy policy;

	/* protects everything */
	spinlock_t lock;
	dm_cblock_t cache_size;
	sector_t cache_block_size;

	sector_t hotspot_block_size;
	अचिन्हित nr_hotspot_blocks;
	अचिन्हित cache_blocks_per_hotspot_block;
	अचिन्हित hotspot_level_jump;

	काष्ठा entry_space es;
	काष्ठा entry_alloc ग_लिखोback_sentinel_alloc;
	काष्ठा entry_alloc demote_sentinel_alloc;
	काष्ठा entry_alloc hotspot_alloc;
	काष्ठा entry_alloc cache_alloc;

	अचिन्हित दीर्घ *hotspot_hit_bits;
	अचिन्हित दीर्घ *cache_hit_bits;

	/*
	 * We मुख्यtain three queues of entries.  The cache proper,
	 * consisting of a clean and dirty queue, containing the currently
	 * active mappings.  The hotspot queue uses a larger block size to
	 * track blocks that are being hit frequently and potential
	 * candidates क्रम promotion to the cache.
	 */
	काष्ठा queue hotspot;
	काष्ठा queue clean;
	काष्ठा queue dirty;

	काष्ठा stats hotspot_stats;
	काष्ठा stats cache_stats;

	/*
	 * Keeps track of समय, incremented by the core.  We use this to
	 * aव्योम attributing multiple hits within the same tick.
	 */
	अचिन्हित tick;

	/*
	 * The hash tables allows us to quickly find an entry by origin
	 * block.
	 */
	काष्ठा smq_hash_table table;
	काष्ठा smq_hash_table hotspot_table;

	bool current_ग_लिखोback_sentinels;
	अचिन्हित दीर्घ next_ग_लिखोback_period;

	bool current_demote_sentinels;
	अचिन्हित दीर्घ next_demote_period;

	अचिन्हित ग_लिखो_promote_level;
	अचिन्हित पढ़ो_promote_level;

	अचिन्हित दीर्घ next_hotspot_period;
	अचिन्हित दीर्घ next_cache_period;

	काष्ठा background_tracker *bg_work;

	bool migrations_allowed;
पूर्ण;

/*----------------------------------------------------------------*/

अटल काष्ठा entry *get_sentinel(काष्ठा entry_alloc *ea, अचिन्हित level, bool which)
अणु
	वापस get_entry(ea, which ? level : NR_CACHE_LEVELS + level);
पूर्ण

अटल काष्ठा entry *ग_लिखोback_sentinel(काष्ठा smq_policy *mq, अचिन्हित level)
अणु
	वापस get_sentinel(&mq->ग_लिखोback_sentinel_alloc, level, mq->current_ग_लिखोback_sentinels);
पूर्ण

अटल काष्ठा entry *demote_sentinel(काष्ठा smq_policy *mq, अचिन्हित level)
अणु
	वापस get_sentinel(&mq->demote_sentinel_alloc, level, mq->current_demote_sentinels);
पूर्ण

अटल व्योम __update_ग_लिखोback_sentinels(काष्ठा smq_policy *mq)
अणु
	अचिन्हित level;
	काष्ठा queue *q = &mq->dirty;
	काष्ठा entry *sentinel;

	क्रम (level = 0; level < q->nr_levels; level++) अणु
		sentinel = ग_लिखोback_sentinel(mq, level);
		q_del(q, sentinel);
		q_push(q, sentinel);
	पूर्ण
पूर्ण

अटल व्योम __update_demote_sentinels(काष्ठा smq_policy *mq)
अणु
	अचिन्हित level;
	काष्ठा queue *q = &mq->clean;
	काष्ठा entry *sentinel;

	क्रम (level = 0; level < q->nr_levels; level++) अणु
		sentinel = demote_sentinel(mq, level);
		q_del(q, sentinel);
		q_push(q, sentinel);
	पूर्ण
पूर्ण

अटल व्योम update_sentinels(काष्ठा smq_policy *mq)
अणु
	अगर (समय_after(jअगरfies, mq->next_ग_लिखोback_period)) अणु
		mq->next_ग_लिखोback_period = jअगरfies + WRITEBACK_PERIOD;
		mq->current_ग_लिखोback_sentinels = !mq->current_ग_लिखोback_sentinels;
		__update_ग_लिखोback_sentinels(mq);
	पूर्ण

	अगर (समय_after(jअगरfies, mq->next_demote_period)) अणु
		mq->next_demote_period = jअगरfies + DEMOTE_PERIOD;
		mq->current_demote_sentinels = !mq->current_demote_sentinels;
		__update_demote_sentinels(mq);
	पूर्ण
पूर्ण

अटल व्योम __sentinels_init(काष्ठा smq_policy *mq)
अणु
	अचिन्हित level;
	काष्ठा entry *sentinel;

	क्रम (level = 0; level < NR_CACHE_LEVELS; level++) अणु
		sentinel = ग_लिखोback_sentinel(mq, level);
		sentinel->level = level;
		q_push(&mq->dirty, sentinel);

		sentinel = demote_sentinel(mq, level);
		sentinel->level = level;
		q_push(&mq->clean, sentinel);
	पूर्ण
पूर्ण

अटल व्योम sentinels_init(काष्ठा smq_policy *mq)
अणु
	mq->next_ग_लिखोback_period = jअगरfies + WRITEBACK_PERIOD;
	mq->next_demote_period = jअगरfies + DEMOTE_PERIOD;

	mq->current_ग_लिखोback_sentinels = false;
	mq->current_demote_sentinels = false;
	__sentinels_init(mq);

	mq->current_ग_लिखोback_sentinels = !mq->current_ग_लिखोback_sentinels;
	mq->current_demote_sentinels = !mq->current_demote_sentinels;
	__sentinels_init(mq);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम del_queue(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	q_del(e->dirty ? &mq->dirty : &mq->clean, e);
पूर्ण

अटल व्योम push_queue(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	अगर (e->dirty)
		q_push(&mq->dirty, e);
	अन्यथा
		q_push(&mq->clean, e);
पूर्ण

// !h, !q, a -> h, q, a
अटल व्योम push(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	h_insert(&mq->table, e);
	अगर (!e->pending_work)
		push_queue(mq, e);
पूर्ण

अटल व्योम push_queue_front(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	अगर (e->dirty)
		q_push_front(&mq->dirty, e);
	अन्यथा
		q_push_front(&mq->clean, e);
पूर्ण

अटल व्योम push_front(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	h_insert(&mq->table, e);
	अगर (!e->pending_work)
		push_queue_front(mq, e);
पूर्ण

अटल dm_cblock_t infer_cblock(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	वापस to_cblock(get_index(&mq->cache_alloc, e));
पूर्ण

अटल व्योम requeue(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	/*
	 * Pending work has temporarily been taken out of the queues.
	 */
	अगर (e->pending_work)
		वापस;

	अगर (!test_and_set_bit(from_cblock(infer_cblock(mq, e)), mq->cache_hit_bits)) अणु
		अगर (!e->dirty) अणु
			q_requeue(&mq->clean, e, 1u, शून्य, शून्य);
			वापस;
		पूर्ण

		q_requeue(&mq->dirty, e, 1u,
			  get_sentinel(&mq->ग_लिखोback_sentinel_alloc, e->level, !mq->current_ग_लिखोback_sentinels),
			  get_sentinel(&mq->ग_लिखोback_sentinel_alloc, e->level, mq->current_ग_लिखोback_sentinels));
	पूर्ण
पूर्ण

अटल अचिन्हित शेष_promote_level(काष्ठा smq_policy *mq)
अणु
	/*
	 * The promote level depends on the current perक्रमmance of the
	 * cache.
	 *
	 * If the cache is perक्रमming badly, then we can't afक्रमd
	 * to promote much without causing perक्रमmance to drop below that
	 * of the origin device.
	 *
	 * If the cache is perक्रमming well, then we करोn't need to promote
	 * much.  If it isn't broken, don't fix it.
	 *
	 * If the cache is middling then we promote more.
	 *
	 * This scheme reminds me of a graph of entropy vs probability of a
	 * binary variable.
	 */
	अटल अचिन्हित table[] = अणु1, 1, 1, 2, 4, 6, 7, 8, 7, 6, 4, 4, 3, 3, 2, 2, 1पूर्ण;

	अचिन्हित hits = mq->cache_stats.hits;
	अचिन्हित misses = mq->cache_stats.misses;
	अचिन्हित index = safe_भाग(hits << 4u, hits + misses);
	वापस table[index];
पूर्ण

अटल व्योम update_promote_levels(काष्ठा smq_policy *mq)
अणु
	/*
	 * If there are unused cache entries then we want to be really
	 * eager to promote.
	 */
	अचिन्हित threshold_level = allocator_empty(&mq->cache_alloc) ?
		शेष_promote_level(mq) : (NR_HOTSPOT_LEVELS / 2u);

	threshold_level = max(threshold_level, NR_HOTSPOT_LEVELS);

	/*
	 * If the hotspot queue is perक्रमming badly then we have little
	 * confidence that we know which blocks to promote.  So we cut करोwn
	 * the amount of promotions.
	 */
	चयन (stats_assess(&mq->hotspot_stats)) अणु
	हाल Q_POOR:
		threshold_level /= 4u;
		अवरोध;

	हाल Q_FAIR:
		threshold_level /= 2u;
		अवरोध;

	हाल Q_WELL:
		अवरोध;
	पूर्ण

	mq->पढ़ो_promote_level = NR_HOTSPOT_LEVELS - threshold_level;
	mq->ग_लिखो_promote_level = (NR_HOTSPOT_LEVELS - threshold_level);
पूर्ण

/*
 * If the hotspot queue is perक्रमming badly, then we try and move entries
 * around more quickly.
 */
अटल व्योम update_level_jump(काष्ठा smq_policy *mq)
अणु
	चयन (stats_assess(&mq->hotspot_stats)) अणु
	हाल Q_POOR:
		mq->hotspot_level_jump = 4u;
		अवरोध;

	हाल Q_FAIR:
		mq->hotspot_level_jump = 2u;
		अवरोध;

	हाल Q_WELL:
		mq->hotspot_level_jump = 1u;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम end_hotspot_period(काष्ठा smq_policy *mq)
अणु
	clear_bitset(mq->hotspot_hit_bits, mq->nr_hotspot_blocks);
	update_promote_levels(mq);

	अगर (समय_after(jअगरfies, mq->next_hotspot_period)) अणु
		update_level_jump(mq);
		q_redistribute(&mq->hotspot);
		stats_reset(&mq->hotspot_stats);
		mq->next_hotspot_period = jअगरfies + HOTSPOT_UPDATE_PERIOD;
	पूर्ण
पूर्ण

अटल व्योम end_cache_period(काष्ठा smq_policy *mq)
अणु
	अगर (समय_after(jअगरfies, mq->next_cache_period)) अणु
		clear_bitset(mq->cache_hit_bits, from_cblock(mq->cache_size));

		q_redistribute(&mq->dirty);
		q_redistribute(&mq->clean);
		stats_reset(&mq->cache_stats);

		mq->next_cache_period = jअगरfies + CACHE_UPDATE_PERIOD;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Tarमाला_लो are given as a percentage.
 */
#घोषणा CLEAN_TARGET 25u
#घोषणा FREE_TARGET 25u

अटल अचिन्हित percent_to_target(काष्ठा smq_policy *mq, अचिन्हित p)
अणु
	वापस from_cblock(mq->cache_size) * p / 100u;
पूर्ण

अटल bool clean_target_met(काष्ठा smq_policy *mq, bool idle)
अणु
	/*
	 * Cache entries may not be populated.  So we cannot rely on the
	 * size of the clean queue.
	 */
	अगर (idle) अणु
		/*
		 * We'd like to clean everything.
		 */
		वापस q_size(&mq->dirty) == 0u;
	पूर्ण

	/*
	 * If we're busy we don't worry about cleaning at all.
	 */
	वापस true;
पूर्ण

अटल bool मुक्त_target_met(काष्ठा smq_policy *mq)
अणु
	अचिन्हित nr_मुक्त;

	nr_मुक्त = from_cblock(mq->cache_size) - mq->cache_alloc.nr_allocated;
	वापस (nr_मुक्त + btracker_nr_demotions_queued(mq->bg_work)) >=
		percent_to_target(mq, FREE_TARGET);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम mark_pending(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	BUG_ON(e->sentinel);
	BUG_ON(!e->allocated);
	BUG_ON(e->pending_work);
	e->pending_work = true;
पूर्ण

अटल व्योम clear_pending(काष्ठा smq_policy *mq, काष्ठा entry *e)
अणु
	BUG_ON(!e->pending_work);
	e->pending_work = false;
पूर्ण

अटल व्योम queue_ग_लिखोback(काष्ठा smq_policy *mq, bool idle)
अणु
	पूर्णांक r;
	काष्ठा policy_work work;
	काष्ठा entry *e;

	e = q_peek(&mq->dirty, mq->dirty.nr_levels, idle);
	अगर (e) अणु
		mark_pending(mq, e);
		q_del(&mq->dirty, e);

		work.op = POLICY_WRITEBACK;
		work.oblock = e->oblock;
		work.cblock = infer_cblock(mq, e);

		r = btracker_queue(mq->bg_work, &work, शून्य);
		अगर (r) अणु
			clear_pending(mq, e);
			q_push_front(&mq->dirty, e);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम queue_demotion(काष्ठा smq_policy *mq)
अणु
	पूर्णांक r;
	काष्ठा policy_work work;
	काष्ठा entry *e;

	अगर (WARN_ON_ONCE(!mq->migrations_allowed))
		वापस;

	e = q_peek(&mq->clean, mq->clean.nr_levels / 2, true);
	अगर (!e) अणु
		अगर (!clean_target_met(mq, true))
			queue_ग_लिखोback(mq, false);
		वापस;
	पूर्ण

	mark_pending(mq, e);
	q_del(&mq->clean, e);

	work.op = POLICY_DEMOTE;
	work.oblock = e->oblock;
	work.cblock = infer_cblock(mq, e);
	r = btracker_queue(mq->bg_work, &work, शून्य);
	अगर (r) अणु
		clear_pending(mq, e);
		q_push_front(&mq->clean, e);
	पूर्ण
पूर्ण

अटल व्योम queue_promotion(काष्ठा smq_policy *mq, dm_oblock_t oblock,
			    काष्ठा policy_work **workp)
अणु
	पूर्णांक r;
	काष्ठा entry *e;
	काष्ठा policy_work work;

	अगर (!mq->migrations_allowed)
		वापस;

	अगर (allocator_empty(&mq->cache_alloc)) अणु
		/*
		 * We always claim to be 'idle' to ensure some demotions happen
		 * with continuous loads.
		 */
		अगर (!मुक्त_target_met(mq))
			queue_demotion(mq);
		वापस;
	पूर्ण

	अगर (btracker_promotion_alपढ़ोy_present(mq->bg_work, oblock))
		वापस;

	/*
	 * We allocate the entry now to reserve the cblock.  If the
	 * background work is पातed we must remember to मुक्त it.
	 */
	e = alloc_entry(&mq->cache_alloc);
	BUG_ON(!e);
	e->pending_work = true;
	work.op = POLICY_PROMOTE;
	work.oblock = oblock;
	work.cblock = infer_cblock(mq, e);
	r = btracker_queue(mq->bg_work, &work, workp);
	अगर (r)
		मुक्त_entry(&mq->cache_alloc, e);
पूर्ण

/*----------------------------------------------------------------*/

क्रमागत promote_result अणु
	PROMOTE_NOT,
	PROMOTE_TEMPORARY,
	PROMOTE_PERMANENT
पूर्ण;

/*
 * Converts a boolean पूर्णांकo a promote result.
 */
अटल क्रमागत promote_result maybe_promote(bool promote)
अणु
	वापस promote ? PROMOTE_PERMANENT : PROMOTE_NOT;
पूर्ण

अटल क्रमागत promote_result should_promote(काष्ठा smq_policy *mq, काष्ठा entry *hs_e,
					  पूर्णांक data_dir, bool fast_promote)
अणु
	अगर (data_dir == WRITE) अणु
		अगर (!allocator_empty(&mq->cache_alloc) && fast_promote)
			वापस PROMOTE_TEMPORARY;

		वापस maybe_promote(hs_e->level >= mq->ग_लिखो_promote_level);
	पूर्ण अन्यथा
		वापस maybe_promote(hs_e->level >= mq->पढ़ो_promote_level);
पूर्ण

अटल dm_oblock_t to_hblock(काष्ठा smq_policy *mq, dm_oblock_t b)
अणु
	sector_t r = from_oblock(b);
	(व्योम) sector_भाग(r, mq->cache_blocks_per_hotspot_block);
	वापस to_oblock(r);
पूर्ण

अटल काष्ठा entry *update_hotspot_queue(काष्ठा smq_policy *mq, dm_oblock_t b)
अणु
	अचिन्हित hi;
	dm_oblock_t hb = to_hblock(mq, b);
	काष्ठा entry *e = h_lookup(&mq->hotspot_table, hb);

	अगर (e) अणु
		stats_level_accessed(&mq->hotspot_stats, e->level);

		hi = get_index(&mq->hotspot_alloc, e);
		q_requeue(&mq->hotspot, e,
			  test_and_set_bit(hi, mq->hotspot_hit_bits) ?
			  0u : mq->hotspot_level_jump,
			  शून्य, शून्य);

	पूर्ण अन्यथा अणु
		stats_miss(&mq->hotspot_stats);

		e = alloc_entry(&mq->hotspot_alloc);
		अगर (!e) अणु
			e = q_pop(&mq->hotspot);
			अगर (e) अणु
				h_हटाओ(&mq->hotspot_table, e);
				hi = get_index(&mq->hotspot_alloc, e);
				clear_bit(hi, mq->hotspot_hit_bits);
			पूर्ण

		पूर्ण

		अगर (e) अणु
			e->oblock = hb;
			q_push(&mq->hotspot, e);
			h_insert(&mq->hotspot_table, e);
		पूर्ण
	पूर्ण

	वापस e;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Public पूर्णांकerface, via the policy काष्ठा.  See dm-cache-policy.h क्रम a
 * description of these.
 */

अटल काष्ठा smq_policy *to_smq_policy(काष्ठा dm_cache_policy *p)
अणु
	वापस container_of(p, काष्ठा smq_policy, policy);
पूर्ण

अटल व्योम smq_destroy(काष्ठा dm_cache_policy *p)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);

	btracker_destroy(mq->bg_work);
	h_निकास(&mq->hotspot_table);
	h_निकास(&mq->table);
	मुक्त_bitset(mq->hotspot_hit_bits);
	मुक्त_bitset(mq->cache_hit_bits);
	space_निकास(&mq->es);
	kमुक्त(mq);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक __lookup(काष्ठा smq_policy *mq, dm_oblock_t oblock, dm_cblock_t *cblock,
		    पूर्णांक data_dir, bool fast_copy,
		    काष्ठा policy_work **work, bool *background_work)
अणु
	काष्ठा entry *e, *hs_e;
	क्रमागत promote_result pr;

	*background_work = false;

	e = h_lookup(&mq->table, oblock);
	अगर (e) अणु
		stats_level_accessed(&mq->cache_stats, e->level);

		requeue(mq, e);
		*cblock = infer_cblock(mq, e);
		वापस 0;

	पूर्ण अन्यथा अणु
		stats_miss(&mq->cache_stats);

		/*
		 * The hotspot queue only माला_लो updated with misses.
		 */
		hs_e = update_hotspot_queue(mq, oblock);

		pr = should_promote(mq, hs_e, data_dir, fast_copy);
		अगर (pr != PROMOTE_NOT) अणु
			queue_promotion(mq, oblock, work);
			*background_work = true;
		पूर्ण

		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल पूर्णांक smq_lookup(काष्ठा dm_cache_policy *p, dm_oblock_t oblock, dm_cblock_t *cblock,
		      पूर्णांक data_dir, bool fast_copy,
		      bool *background_work)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	r = __lookup(mq, oblock, cblock,
		     data_dir, fast_copy,
		     शून्य, background_work);
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक smq_lookup_with_work(काष्ठा dm_cache_policy *p,
				dm_oblock_t oblock, dm_cblock_t *cblock,
				पूर्णांक data_dir, bool fast_copy,
				काष्ठा policy_work **work)
अणु
	पूर्णांक r;
	bool background_queued;
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	r = __lookup(mq, oblock, cblock, data_dir, fast_copy, work, &background_queued);
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक smq_get_background_work(काष्ठा dm_cache_policy *p, bool idle,
				   काष्ठा policy_work **result)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	r = btracker_issue(mq->bg_work, result);
	अगर (r == -ENODATA) अणु
		अगर (!clean_target_met(mq, idle)) अणु
			queue_ग_लिखोback(mq, idle);
			r = btracker_issue(mq->bg_work, result);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस r;
पूर्ण

/*
 * We need to clear any pending work flags that have been set, and in the
 * हाल of promotion मुक्त the entry क्रम the destination cblock.
 */
अटल व्योम __complete_background_work(काष्ठा smq_policy *mq,
				       काष्ठा policy_work *work,
				       bool success)
अणु
	काष्ठा entry *e = get_entry(&mq->cache_alloc,
				    from_cblock(work->cblock));

	चयन (work->op) अणु
	हाल POLICY_PROMOTE:
		// !h, !q, a
		clear_pending(mq, e);
		अगर (success) अणु
			e->oblock = work->oblock;
			e->level = NR_CACHE_LEVELS - 1;
			push(mq, e);
			// h, q, a
		पूर्ण अन्यथा अणु
			मुक्त_entry(&mq->cache_alloc, e);
			// !h, !q, !a
		पूर्ण
		अवरोध;

	हाल POLICY_DEMOTE:
		// h, !q, a
		अगर (success) अणु
			h_हटाओ(&mq->table, e);
			मुक्त_entry(&mq->cache_alloc, e);
			// !h, !q, !a
		पूर्ण अन्यथा अणु
			clear_pending(mq, e);
			push_queue(mq, e);
			// h, q, a
		पूर्ण
		अवरोध;

	हाल POLICY_WRITEBACK:
		// h, !q, a
		clear_pending(mq, e);
		push_queue(mq, e);
		// h, q, a
		अवरोध;
	पूर्ण

	btracker_complete(mq->bg_work, work);
पूर्ण

अटल व्योम smq_complete_background_work(काष्ठा dm_cache_policy *p,
					 काष्ठा policy_work *work,
					 bool success)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	__complete_background_work(mq, work, success);
	spin_unlock_irqrestore(&mq->lock, flags);
पूर्ण

// in_hash(oblock) -> in_hash(oblock)
अटल व्योम __smq_set_clear_dirty(काष्ठा smq_policy *mq, dm_cblock_t cblock, bool set)
अणु
	काष्ठा entry *e = get_entry(&mq->cache_alloc, from_cblock(cblock));

	अगर (e->pending_work)
		e->dirty = set;
	अन्यथा अणु
		del_queue(mq, e);
		e->dirty = set;
		push_queue(mq, e);
	पूर्ण
पूर्ण

अटल व्योम smq_set_dirty(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	__smq_set_clear_dirty(mq, cblock, true);
	spin_unlock_irqrestore(&mq->lock, flags);
पूर्ण

अटल व्योम smq_clear_dirty(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mq->lock, flags);
	__smq_set_clear_dirty(mq, cblock, false);
	spin_unlock_irqrestore(&mq->lock, flags);
पूर्ण

अटल अचिन्हित अक्रमom_level(dm_cblock_t cblock)
अणु
	वापस hash_32(from_cblock(cblock), 9) & (NR_CACHE_LEVELS - 1);
पूर्ण

अटल पूर्णांक smq_load_mapping(काष्ठा dm_cache_policy *p,
			    dm_oblock_t oblock, dm_cblock_t cblock,
			    bool dirty, uपूर्णांक32_t hपूर्णांक, bool hपूर्णांक_valid)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	काष्ठा entry *e;

	e = alloc_particular_entry(&mq->cache_alloc, from_cblock(cblock));
	e->oblock = oblock;
	e->dirty = dirty;
	e->level = hपूर्णांक_valid ? min(hपूर्णांक, NR_CACHE_LEVELS - 1) : अक्रमom_level(cblock);
	e->pending_work = false;

	/*
	 * When we load mappings we push ahead of both sentinels in order to
	 * allow demotions and cleaning to occur immediately.
	 */
	push_front(mq, e);

	वापस 0;
पूर्ण

अटल पूर्णांक smq_invalidate_mapping(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	काष्ठा entry *e = get_entry(&mq->cache_alloc, from_cblock(cblock));

	अगर (!e->allocated)
		वापस -ENODATA;

	// FIXME: what अगर this block has pending background work?
	del_queue(mq, e);
	h_हटाओ(&mq->table, e);
	मुक्त_entry(&mq->cache_alloc, e);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t smq_get_hपूर्णांक(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	काष्ठा entry *e = get_entry(&mq->cache_alloc, from_cblock(cblock));

	अगर (!e->allocated)
		वापस 0;

	वापस e->level;
पूर्ण

अटल dm_cblock_t smq_residency(काष्ठा dm_cache_policy *p)
अणु
	dm_cblock_t r;
	अचिन्हित दीर्घ flags;
	काष्ठा smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	r = to_cblock(mq->cache_alloc.nr_allocated);
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस r;
पूर्ण

अटल व्योम smq_tick(काष्ठा dm_cache_policy *p, bool can_block)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mq->lock, flags);
	mq->tick++;
	update_sentinels(mq);
	end_hotspot_period(mq);
	end_cache_period(mq);
	spin_unlock_irqrestore(&mq->lock, flags);
पूर्ण

अटल व्योम smq_allow_migrations(काष्ठा dm_cache_policy *p, bool allow)
अणु
	काष्ठा smq_policy *mq = to_smq_policy(p);
	mq->migrations_allowed = allow;
पूर्ण

/*
 * smq has no config values, but the old mq policy did.  To aव्योम अवरोधing
 * software we जारी to accept these configurables क्रम the mq policy,
 * but they have no effect.
 */
अटल पूर्णांक mq_set_config_value(काष्ठा dm_cache_policy *p,
			       स्थिर अक्षर *key, स्थिर अक्षर *value)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (kम_से_अदीर्घ(value, 10, &पंचांगp))
		वापस -EINVAL;

	अगर (!strहालcmp(key, "random_threshold") ||
	    !strहालcmp(key, "sequential_threshold") ||
	    !strहालcmp(key, "discard_promote_adjustment") ||
	    !strहालcmp(key, "read_promote_adjustment") ||
	    !strहालcmp(key, "write_promote_adjustment")) अणु
		DMWARN("tunable '%s' no longer has any effect, mq policy is now an alias for smq", key);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mq_emit_config_values(काष्ठा dm_cache_policy *p, अक्षर *result,
				 अचिन्हित maxlen, sमाप_प्रकार *sz_ptr)
अणु
	sमाप_प्रकार sz = *sz_ptr;

	DMEMIT("10 random_threshold 0 "
	       "sequential_threshold 0 "
	       "discard_promote_adjustment 0 "
	       "read_promote_adjustment 0 "
	       "write_promote_adjustment 0 ");

	*sz_ptr = sz;
	वापस 0;
पूर्ण

/* Init the policy plugin पूर्णांकerface function poपूर्णांकers. */
अटल व्योम init_policy_functions(काष्ठा smq_policy *mq, bool mimic_mq)
अणु
	mq->policy.destroy = smq_destroy;
	mq->policy.lookup = smq_lookup;
	mq->policy.lookup_with_work = smq_lookup_with_work;
	mq->policy.get_background_work = smq_get_background_work;
	mq->policy.complete_background_work = smq_complete_background_work;
	mq->policy.set_dirty = smq_set_dirty;
	mq->policy.clear_dirty = smq_clear_dirty;
	mq->policy.load_mapping = smq_load_mapping;
	mq->policy.invalidate_mapping = smq_invalidate_mapping;
	mq->policy.get_hपूर्णांक = smq_get_hपूर्णांक;
	mq->policy.residency = smq_residency;
	mq->policy.tick = smq_tick;
	mq->policy.allow_migrations = smq_allow_migrations;

	अगर (mimic_mq) अणु
		mq->policy.set_config_value = mq_set_config_value;
		mq->policy.emit_config_values = mq_emit_config_values;
	पूर्ण
पूर्ण

अटल bool too_many_hotspot_blocks(sector_t origin_size,
				    sector_t hotspot_block_size,
				    अचिन्हित nr_hotspot_blocks)
अणु
	वापस (hotspot_block_size * nr_hotspot_blocks) > origin_size;
पूर्ण

अटल व्योम calc_hotspot_params(sector_t origin_size,
				sector_t cache_block_size,
				अचिन्हित nr_cache_blocks,
				sector_t *hotspot_block_size,
				अचिन्हित *nr_hotspot_blocks)
अणु
	*hotspot_block_size = cache_block_size * 16u;
	*nr_hotspot_blocks = max(nr_cache_blocks / 4u, 1024u);

	जबतक ((*hotspot_block_size > cache_block_size) &&
	       too_many_hotspot_blocks(origin_size, *hotspot_block_size, *nr_hotspot_blocks))
		*hotspot_block_size /= 2u;
पूर्ण

अटल काष्ठा dm_cache_policy *__smq_create(dm_cblock_t cache_size,
					    sector_t origin_size,
					    sector_t cache_block_size,
					    bool mimic_mq,
					    bool migrations_allowed)
अणु
	अचिन्हित i;
	अचिन्हित nr_sentinels_per_queue = 2u * NR_CACHE_LEVELS;
	अचिन्हित total_sentinels = 2u * nr_sentinels_per_queue;
	काष्ठा smq_policy *mq = kzalloc(माप(*mq), GFP_KERNEL);

	अगर (!mq)
		वापस शून्य;

	init_policy_functions(mq, mimic_mq);
	mq->cache_size = cache_size;
	mq->cache_block_size = cache_block_size;

	calc_hotspot_params(origin_size, cache_block_size, from_cblock(cache_size),
			    &mq->hotspot_block_size, &mq->nr_hotspot_blocks);

	mq->cache_blocks_per_hotspot_block = भाग64_u64(mq->hotspot_block_size, mq->cache_block_size);
	mq->hotspot_level_jump = 1u;
	अगर (space_init(&mq->es, total_sentinels + mq->nr_hotspot_blocks + from_cblock(cache_size))) अणु
		DMERR("couldn't initialize entry space");
		जाओ bad_pool_init;
	पूर्ण

	init_allocator(&mq->ग_लिखोback_sentinel_alloc, &mq->es, 0, nr_sentinels_per_queue);
	क्रम (i = 0; i < nr_sentinels_per_queue; i++)
		get_entry(&mq->ग_लिखोback_sentinel_alloc, i)->sentinel = true;

	init_allocator(&mq->demote_sentinel_alloc, &mq->es, nr_sentinels_per_queue, total_sentinels);
	क्रम (i = 0; i < nr_sentinels_per_queue; i++)
		get_entry(&mq->demote_sentinel_alloc, i)->sentinel = true;

	init_allocator(&mq->hotspot_alloc, &mq->es, total_sentinels,
		       total_sentinels + mq->nr_hotspot_blocks);

	init_allocator(&mq->cache_alloc, &mq->es,
		       total_sentinels + mq->nr_hotspot_blocks,
		       total_sentinels + mq->nr_hotspot_blocks + from_cblock(cache_size));

	mq->hotspot_hit_bits = alloc_bitset(mq->nr_hotspot_blocks);
	अगर (!mq->hotspot_hit_bits) अणु
		DMERR("couldn't allocate hotspot hit bitset");
		जाओ bad_hotspot_hit_bits;
	पूर्ण
	clear_bitset(mq->hotspot_hit_bits, mq->nr_hotspot_blocks);

	अगर (from_cblock(cache_size)) अणु
		mq->cache_hit_bits = alloc_bitset(from_cblock(cache_size));
		अगर (!mq->cache_hit_bits) अणु
			DMERR("couldn't allocate cache hit bitset");
			जाओ bad_cache_hit_bits;
		पूर्ण
		clear_bitset(mq->cache_hit_bits, from_cblock(mq->cache_size));
	पूर्ण अन्यथा
		mq->cache_hit_bits = शून्य;

	mq->tick = 0;
	spin_lock_init(&mq->lock);

	q_init(&mq->hotspot, &mq->es, NR_HOTSPOT_LEVELS);
	mq->hotspot.nr_top_levels = 8;
	mq->hotspot.nr_in_top_levels = min(mq->nr_hotspot_blocks / NR_HOTSPOT_LEVELS,
					   from_cblock(mq->cache_size) / mq->cache_blocks_per_hotspot_block);

	q_init(&mq->clean, &mq->es, NR_CACHE_LEVELS);
	q_init(&mq->dirty, &mq->es, NR_CACHE_LEVELS);

	stats_init(&mq->hotspot_stats, NR_HOTSPOT_LEVELS);
	stats_init(&mq->cache_stats, NR_CACHE_LEVELS);

	अगर (h_init(&mq->table, &mq->es, from_cblock(cache_size)))
		जाओ bad_alloc_table;

	अगर (h_init(&mq->hotspot_table, &mq->es, mq->nr_hotspot_blocks))
		जाओ bad_alloc_hotspot_table;

	sentinels_init(mq);
	mq->ग_लिखो_promote_level = mq->पढ़ो_promote_level = NR_HOTSPOT_LEVELS;

	mq->next_hotspot_period = jअगरfies;
	mq->next_cache_period = jअगरfies;

	mq->bg_work = btracker_create(4096); /* FIXME: hard coded value */
	अगर (!mq->bg_work)
		जाओ bad_btracker;

	mq->migrations_allowed = migrations_allowed;

	वापस &mq->policy;

bad_btracker:
	h_निकास(&mq->hotspot_table);
bad_alloc_hotspot_table:
	h_निकास(&mq->table);
bad_alloc_table:
	मुक्त_bitset(mq->cache_hit_bits);
bad_cache_hit_bits:
	मुक्त_bitset(mq->hotspot_hit_bits);
bad_hotspot_hit_bits:
	space_निकास(&mq->es);
bad_pool_init:
	kमुक्त(mq);

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_cache_policy *smq_create(dm_cblock_t cache_size,
					  sector_t origin_size,
					  sector_t cache_block_size)
अणु
	वापस __smq_create(cache_size, origin_size, cache_block_size, false, true);
पूर्ण

अटल काष्ठा dm_cache_policy *mq_create(dm_cblock_t cache_size,
					 sector_t origin_size,
					 sector_t cache_block_size)
अणु
	वापस __smq_create(cache_size, origin_size, cache_block_size, true, true);
पूर्ण

अटल काष्ठा dm_cache_policy *cleaner_create(dm_cblock_t cache_size,
					      sector_t origin_size,
					      sector_t cache_block_size)
अणु
	वापस __smq_create(cache_size, origin_size, cache_block_size, false, false);
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा dm_cache_policy_type smq_policy_type = अणु
	.name = "smq",
	.version = अणु2, 0, 0पूर्ण,
	.hपूर्णांक_size = 4,
	.owner = THIS_MODULE,
	.create = smq_create
पूर्ण;

अटल काष्ठा dm_cache_policy_type mq_policy_type = अणु
	.name = "mq",
	.version = अणु2, 0, 0पूर्ण,
	.hपूर्णांक_size = 4,
	.owner = THIS_MODULE,
	.create = mq_create,
पूर्ण;

अटल काष्ठा dm_cache_policy_type cleaner_policy_type = अणु
	.name = "cleaner",
	.version = अणु2, 0, 0पूर्ण,
	.hपूर्णांक_size = 4,
	.owner = THIS_MODULE,
	.create = cleaner_create,
पूर्ण;

अटल काष्ठा dm_cache_policy_type शेष_policy_type = अणु
	.name = "default",
	.version = अणु2, 0, 0पूर्ण,
	.hपूर्णांक_size = 4,
	.owner = THIS_MODULE,
	.create = smq_create,
	.real = &smq_policy_type
पूर्ण;

अटल पूर्णांक __init smq_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_cache_policy_रेजिस्टर(&smq_policy_type);
	अगर (r) अणु
		DMERR("register failed %d", r);
		वापस -ENOMEM;
	पूर्ण

	r = dm_cache_policy_रेजिस्टर(&mq_policy_type);
	अगर (r) अणु
		DMERR("register failed (as mq) %d", r);
		जाओ out_mq;
	पूर्ण

	r = dm_cache_policy_रेजिस्टर(&cleaner_policy_type);
	अगर (r) अणु
		DMERR("register failed (as cleaner) %d", r);
		जाओ out_cleaner;
	पूर्ण

	r = dm_cache_policy_रेजिस्टर(&शेष_policy_type);
	अगर (r) अणु
		DMERR("register failed (as default) %d", r);
		जाओ out_शेष;
	पूर्ण

	वापस 0;

out_शेष:
	dm_cache_policy_unरेजिस्टर(&cleaner_policy_type);
out_cleaner:
	dm_cache_policy_unरेजिस्टर(&mq_policy_type);
out_mq:
	dm_cache_policy_unरेजिस्टर(&smq_policy_type);

	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास smq_निकास(व्योम)
अणु
	dm_cache_policy_unरेजिस्टर(&cleaner_policy_type);
	dm_cache_policy_unरेजिस्टर(&smq_policy_type);
	dm_cache_policy_unरेजिस्टर(&mq_policy_type);
	dm_cache_policy_unरेजिस्टर(&शेष_policy_type);
पूर्ण

module_init(smq_init);
module_निकास(smq_निकास);

MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("smq cache policy");

MODULE_ALIAS("dm-cache-default");
MODULE_ALIAS("dm-cache-mq");
MODULE_ALIAS("dm-cache-cleaner");
