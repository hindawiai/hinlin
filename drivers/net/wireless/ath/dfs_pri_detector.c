<शैली गुरु>
/*
 * Copyright (c) 2012 Neratec Solutions AG
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "ath.h"
#समावेश "dfs_pattern_detector.h"
#समावेश "dfs_pri_detector.h"

काष्ठा ath_dfs_pool_stats global_dfs_pool_stats = अणुपूर्ण;

#घोषणा DFS_POOL_STAT_INC(c) (global_dfs_pool_stats.c++)
#घोषणा DFS_POOL_STAT_DEC(c) (global_dfs_pool_stats.c--)
#घोषणा GET_PRI_TO_USE(MIN, MAX, RUNTIME) \
	(MIN + PRI_TOLERANCE == MAX - PRI_TOLERANCE ? \
	MIN + PRI_TOLERANCE : RUNTIME)

/*
 * काष्ठा pulse_elem - elements in pulse queue
 */
काष्ठा pulse_elem अणु
	काष्ठा list_head head;
	u64 ts;
पूर्ण;

/*
 * pde_get_multiple() - get number of multiples considering a given tolerance
 * Return value: factor अगर असल(val - factor*fraction) <= tolerance, 0 otherwise
 */
अटल u32 pde_get_multiple(u32 val, u32 fraction, u32 tolerance)
अणु
	u32 reमुख्यder;
	u32 factor;
	u32 delta;

	अगर (fraction == 0)
		वापस 0;

	delta = (val < fraction) ? (fraction - val) : (val - fraction);

	अगर (delta <= tolerance)
		/* val and fraction are within tolerance */
		वापस 1;

	factor = val / fraction;
	reमुख्यder = val % fraction;
	अगर (reमुख्यder > tolerance) अणु
		/* no exact match */
		अगर ((fraction - reमुख्यder) <= tolerance)
			/* reमुख्यder is within tolerance */
			factor++;
		अन्यथा
			factor = 0;
	पूर्ण
	वापस factor;
पूर्ण

/*
 * DOC: Singleton Pulse and Sequence Pools
 *
 * Instances of pri_sequence and pulse_elem are kept in singleton pools to
 * reduce the number of dynamic allocations. They are shared between all
 * instances and grow up to the peak number of simultaneously used objects.
 *
 * Memory is मुक्तd after all references to the pools are released.
 */
अटल u32 singleton_pool_references;
अटल LIST_HEAD(pulse_pool);
अटल LIST_HEAD(pseq_pool);
अटल DEFINE_SPINLOCK(pool_lock);

अटल व्योम pool_रेजिस्टर_ref(व्योम)
अणु
	spin_lock_bh(&pool_lock);
	singleton_pool_references++;
	DFS_POOL_STAT_INC(pool_reference);
	spin_unlock_bh(&pool_lock);
पूर्ण

अटल व्योम pool_deरेजिस्टर_ref(व्योम)
अणु
	spin_lock_bh(&pool_lock);
	singleton_pool_references--;
	DFS_POOL_STAT_DEC(pool_reference);
	अगर (singleton_pool_references == 0) अणु
		/* मुक्त singleton pools with no references left */
		काष्ठा pri_sequence *ps, *ps0;
		काष्ठा pulse_elem *p, *p0;

		list_क्रम_each_entry_safe(p, p0, &pulse_pool, head) अणु
			list_del(&p->head);
			DFS_POOL_STAT_DEC(pulse_allocated);
			kमुक्त(p);
		पूर्ण
		list_क्रम_each_entry_safe(ps, ps0, &pseq_pool, head) अणु
			list_del(&ps->head);
			DFS_POOL_STAT_DEC(pseq_allocated);
			kमुक्त(ps);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pool_lock);
पूर्ण

अटल व्योम pool_put_pulse_elem(काष्ठा pulse_elem *pe)
अणु
	spin_lock_bh(&pool_lock);
	list_add(&pe->head, &pulse_pool);
	DFS_POOL_STAT_DEC(pulse_used);
	spin_unlock_bh(&pool_lock);
पूर्ण

अटल व्योम pool_put_pseq_elem(काष्ठा pri_sequence *pse)
अणु
	spin_lock_bh(&pool_lock);
	list_add(&pse->head, &pseq_pool);
	DFS_POOL_STAT_DEC(pseq_used);
	spin_unlock_bh(&pool_lock);
पूर्ण

अटल काष्ठा pri_sequence *pool_get_pseq_elem(व्योम)
अणु
	काष्ठा pri_sequence *pse = शून्य;
	spin_lock_bh(&pool_lock);
	अगर (!list_empty(&pseq_pool)) अणु
		pse = list_first_entry(&pseq_pool, काष्ठा pri_sequence, head);
		list_del(&pse->head);
		DFS_POOL_STAT_INC(pseq_used);
	पूर्ण
	spin_unlock_bh(&pool_lock);
	वापस pse;
पूर्ण

अटल काष्ठा pulse_elem *pool_get_pulse_elem(व्योम)
अणु
	काष्ठा pulse_elem *pe = शून्य;
	spin_lock_bh(&pool_lock);
	अगर (!list_empty(&pulse_pool)) अणु
		pe = list_first_entry(&pulse_pool, काष्ठा pulse_elem, head);
		list_del(&pe->head);
		DFS_POOL_STAT_INC(pulse_used);
	पूर्ण
	spin_unlock_bh(&pool_lock);
	वापस pe;
पूर्ण

अटल काष्ठा pulse_elem *pulse_queue_get_tail(काष्ठा pri_detector *pde)
अणु
	काष्ठा list_head *l = &pde->pulses;
	अगर (list_empty(l))
		वापस शून्य;
	वापस list_entry(l->prev, काष्ठा pulse_elem, head);
पूर्ण

अटल bool pulse_queue_dequeue(काष्ठा pri_detector *pde)
अणु
	काष्ठा pulse_elem *p = pulse_queue_get_tail(pde);
	अगर (p != शून्य) अणु
		list_del_init(&p->head);
		pde->count--;
		/* give it back to pool */
		pool_put_pulse_elem(p);
	पूर्ण
	वापस (pde->count > 0);
पूर्ण

/* हटाओ pulses older than winकरोw */
अटल व्योम pulse_queue_check_winकरोw(काष्ठा pri_detector *pde)
अणु
	u64 min_valid_ts;
	काष्ठा pulse_elem *p;

	/* there is no delta समय with less than 2 pulses */
	अगर (pde->count < 2)
		वापस;

	अगर (pde->last_ts <= pde->winकरोw_size)
		वापस;

	min_valid_ts = pde->last_ts - pde->winकरोw_size;
	जबतक ((p = pulse_queue_get_tail(pde)) != शून्य) अणु
		अगर (p->ts >= min_valid_ts)
			वापस;
		pulse_queue_dequeue(pde);
	पूर्ण
पूर्ण

अटल bool pulse_queue_enqueue(काष्ठा pri_detector *pde, u64 ts)
अणु
	काष्ठा pulse_elem *p = pool_get_pulse_elem();
	अगर (p == शून्य) अणु
		p = kदो_स्मृति(माप(*p), GFP_ATOMIC);
		अगर (p == शून्य) अणु
			DFS_POOL_STAT_INC(pulse_alloc_error);
			वापस false;
		पूर्ण
		DFS_POOL_STAT_INC(pulse_allocated);
		DFS_POOL_STAT_INC(pulse_used);
	पूर्ण
	INIT_LIST_HEAD(&p->head);
	p->ts = ts;
	list_add(&p->head, &pde->pulses);
	pde->count++;
	pde->last_ts = ts;
	pulse_queue_check_winकरोw(pde);
	अगर (pde->count >= pde->max_count)
		pulse_queue_dequeue(pde);
	वापस true;
पूर्ण

अटल bool pseq_handler_create_sequences(काष्ठा pri_detector *pde,
					  u64 ts, u32 min_count)
अणु
	काष्ठा pulse_elem *p;
	list_क्रम_each_entry(p, &pde->pulses, head) अणु
		काष्ठा pri_sequence ps, *new_ps;
		काष्ठा pulse_elem *p2;
		u32 पंचांगp_false_count;
		u64 min_valid_ts;
		u32 delta_ts = ts - p->ts;

		अगर (delta_ts < pde->rs->pri_min)
			/* ignore too small pri */
			जारी;

		अगर (delta_ts > pde->rs->pri_max)
			/* stop on too large pri (sorted list) */
			अवरोध;

		/* build a new sequence with new potential pri */
		ps.count = 2;
		ps.count_falses = 0;
		ps.first_ts = p->ts;
		ps.last_ts = ts;
		ps.pri = GET_PRI_TO_USE(pde->rs->pri_min,
			pde->rs->pri_max, ts - p->ts);
		ps.dur = ps.pri * (pde->rs->ppb - 1)
				+ 2 * pde->rs->max_pri_tolerance;

		p2 = p;
		पंचांगp_false_count = 0;
		min_valid_ts = ts - ps.dur;
		/* check which past pulses are candidates क्रम new sequence */
		list_क्रम_each_entry_जारी(p2, &pde->pulses, head) अणु
			u32 factor;
			अगर (p2->ts < min_valid_ts)
				/* stop on crossing winकरोw border */
				अवरोध;
			/* check अगर pulse match (multi)PRI */
			factor = pde_get_multiple(ps.last_ts - p2->ts, ps.pri,
						  pde->rs->max_pri_tolerance);
			अगर (factor > 0) अणु
				ps.count++;
				ps.first_ts = p2->ts;
				/*
				 * on match, add the पूर्णांकermediate falses
				 * and reset counter
				 */
				ps.count_falses += पंचांगp_false_count;
				पंचांगp_false_count = 0;
			पूर्ण अन्यथा अणु
				/* this is a potential false one */
				पंचांगp_false_count++;
			पूर्ण
		पूर्ण
		अगर (ps.count <= min_count)
			/* did not reach minimum count, drop sequence */
			जारी;

		/* this is a valid one, add it */
		ps.deadline_ts = ps.first_ts + ps.dur;
		new_ps = pool_get_pseq_elem();
		अगर (new_ps == शून्य) अणु
			new_ps = kदो_स्मृति(माप(*new_ps), GFP_ATOMIC);
			अगर (new_ps == शून्य) अणु
				DFS_POOL_STAT_INC(pseq_alloc_error);
				वापस false;
			पूर्ण
			DFS_POOL_STAT_INC(pseq_allocated);
			DFS_POOL_STAT_INC(pseq_used);
		पूर्ण
		स_नकल(new_ps, &ps, माप(ps));
		INIT_LIST_HEAD(&new_ps->head);
		list_add(&new_ps->head, &pde->sequences);
	पूर्ण
	वापस true;
पूर्ण

/* check new ts and add to all matching existing sequences */
अटल u32
pseq_handler_add_to_existing_seqs(काष्ठा pri_detector *pde, u64 ts)
अणु
	u32 max_count = 0;
	काष्ठा pri_sequence *ps, *ps2;
	list_क्रम_each_entry_safe(ps, ps2, &pde->sequences, head) अणु
		u32 delta_ts;
		u32 factor;

		/* first ensure that sequence is within winकरोw */
		अगर (ts > ps->deadline_ts) अणु
			list_del_init(&ps->head);
			pool_put_pseq_elem(ps);
			जारी;
		पूर्ण

		delta_ts = ts - ps->last_ts;
		factor = pde_get_multiple(delta_ts, ps->pri,
					  pde->rs->max_pri_tolerance);
		अगर (factor > 0) अणु
			ps->last_ts = ts;
			ps->count++;

			अगर (max_count < ps->count)
				max_count = ps->count;
		पूर्ण अन्यथा अणु
			ps->count_falses++;
		पूर्ण
	पूर्ण
	वापस max_count;
पूर्ण

अटल काष्ठा pri_sequence *
pseq_handler_check_detection(काष्ठा pri_detector *pde)
अणु
	काष्ठा pri_sequence *ps;

	अगर (list_empty(&pde->sequences))
		वापस शून्य;

	list_क्रम_each_entry(ps, &pde->sequences, head) अणु
		/*
		 * we assume to have enough matching confidence अगर we
		 * 1) have enough pulses
		 * 2) have more matching than false pulses
		 */
		अगर ((ps->count >= pde->rs->ppb_thresh) &&
		    (ps->count * pde->rs->num_pri >= ps->count_falses))
			वापस ps;
	पूर्ण
	वापस शून्य;
पूर्ण


/* मुक्त pulse queue and sequences list and give objects back to pools */
अटल व्योम pri_detector_reset(काष्ठा pri_detector *pde, u64 ts)
अणु
	काष्ठा pri_sequence *ps, *ps0;
	काष्ठा pulse_elem *p, *p0;
	list_क्रम_each_entry_safe(ps, ps0, &pde->sequences, head) अणु
		list_del_init(&ps->head);
		pool_put_pseq_elem(ps);
	पूर्ण
	list_क्रम_each_entry_safe(p, p0, &pde->pulses, head) अणु
		list_del_init(&p->head);
		pool_put_pulse_elem(p);
	पूर्ण
	pde->count = 0;
	pde->last_ts = ts;
पूर्ण

अटल व्योम pri_detector_निकास(काष्ठा pri_detector *de)
अणु
	pri_detector_reset(de, 0);
	pool_deरेजिस्टर_ref();
	kमुक्त(de);
पूर्ण

अटल काष्ठा pri_sequence *pri_detector_add_pulse(काष्ठा pri_detector *de,
						   काष्ठा pulse_event *event)
अणु
	u32 max_updated_seq;
	काष्ठा pri_sequence *ps;
	u64 ts = event->ts;
	स्थिर काष्ठा radar_detector_specs *rs = de->rs;

	/* ignore pulses not within width range */
	अगर ((rs->width_min > event->width) || (rs->width_max < event->width))
		वापस शून्य;

	अगर ((ts - de->last_ts) < rs->max_pri_tolerance)
		/* अगर delta to last pulse is too लघु, करोn't use this pulse */
		वापस शून्य;
	/* radar detector spec needs chirp, but not detected */
	अगर (rs->chirp && rs->chirp != event->chirp)
		वापस शून्य;

	de->last_ts = ts;

	max_updated_seq = pseq_handler_add_to_existing_seqs(de, ts);

	अगर (!pseq_handler_create_sequences(de, ts, max_updated_seq)) अणु
		pri_detector_reset(de, ts);
		वापस शून्य;
	पूर्ण

	ps = pseq_handler_check_detection(de);

	अगर (ps == शून्य)
		pulse_queue_enqueue(de, ts);

	वापस ps;
पूर्ण

काष्ठा pri_detector *pri_detector_init(स्थिर काष्ठा radar_detector_specs *rs)
अणु
	काष्ठा pri_detector *de;

	de = kzalloc(माप(*de), GFP_ATOMIC);
	अगर (de == शून्य)
		वापस शून्य;
	de->निकास = pri_detector_निकास;
	de->add_pulse = pri_detector_add_pulse;
	de->reset = pri_detector_reset;

	INIT_LIST_HEAD(&de->sequences);
	INIT_LIST_HEAD(&de->pulses);
	de->winकरोw_size = rs->pri_max * rs->ppb * rs->num_pri;
	de->max_count = rs->ppb * 2;
	de->rs = rs;

	pool_रेजिस्टर_ref();
	वापस de;
पूर्ण
