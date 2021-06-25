<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Floating proportions with flexible aging period
 *
 *   Copyright (C) 2011, SUSE, Jan Kara <jack@suse.cz>
 *
 * The goal of this code is: Given dअगरferent types of event, measure proportion
 * of each type of event over समय. The proportions are measured with
 * exponentially decaying history to give smooth transitions. A क्रमmula
 * expressing proportion of event of type 'j' is:
 *
 *   p_अणुjपूर्ण = (\Sum_अणुi>=0पूर्ण x_अणुi,jपूर्ण/2^अणुi+1पूर्ण)/(\Sum_अणुi>=0पूर्ण x_i/2^अणुi+1पूर्ण)
 *
 * Where x_अणुi,jपूर्ण is j's number of events in i-th last समय period and x_i is
 * total number of events in i-th last समय period.
 *
 * Note that p_अणुjपूर्ण's are normalised, i.e.
 *
 *   \Sum_अणुjपूर्ण p_अणुjपूर्ण = 1,
 *
 * This क्रमmula can be straightक्रमwardly computed by मुख्यtaining denominator
 * (let's call it 'd') and for each event type its numerator (let's call it
 * 'n_j'). When an event of type 'j' happens, we simply need to करो:
 *   n_j++; d++;
 *
 * When a new period is declared, we could करो:
 *   d /= 2
 *   क्रम each j
 *     n_j /= 2
 *
 * To aव्योम iteration over all event types, we instead shअगरt numerator of event
 * j lazily when someone asks क्रम a proportion of event j or when event j
 * occurs. This can bit trivially implemented by remembering last period in
 * which something happened with proportion of type j.
 */
#समावेश <linux/flex_proportions.h>

पूर्णांक fprop_global_init(काष्ठा fprop_global *p, gfp_t gfp)
अणु
	पूर्णांक err;

	p->period = 0;
	/* Use 1 to aव्योम dealing with periods with 0 events... */
	err = percpu_counter_init(&p->events, 1, gfp);
	अगर (err)
		वापस err;
	seqcount_init(&p->sequence);
	वापस 0;
पूर्ण

व्योम fprop_global_destroy(काष्ठा fprop_global *p)
अणु
	percpu_counter_destroy(&p->events);
पूर्ण

/*
 * Declare @periods new periods. It is upto the caller to make sure period
 * transitions cannot happen in parallel.
 *
 * The function वापसs true अगर the proportions are still defined and false
 * अगर aging zeroed out all events. This can be used to detect whether declaring
 * further periods has any effect.
 */
bool fprop_new_period(काष्ठा fprop_global *p, पूर्णांक periods)
अणु
	s64 events;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	events = percpu_counter_sum(&p->events);
	/*
	 * Don't करो anything अगर there are no events.
	 */
	अगर (events <= 1) अणु
		local_irq_restore(flags);
		वापस false;
	पूर्ण
	ग_लिखो_seqcount_begin(&p->sequence);
	अगर (periods < 64)
		events -= events >> periods;
	/* Use addition to aव्योम losing events happening between sum and set */
	percpu_counter_add(&p->events, -events);
	p->period += periods;
	ग_लिखो_seqcount_end(&p->sequence);
	local_irq_restore(flags);

	वापस true;
पूर्ण

/*
 * ---- SINGLE ----
 */

पूर्णांक fprop_local_init_single(काष्ठा fprop_local_single *pl)
अणु
	pl->events = 0;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	वापस 0;
पूर्ण

व्योम fprop_local_destroy_single(काष्ठा fprop_local_single *pl)
अणु
पूर्ण

अटल व्योम fprop_reflect_period_single(काष्ठा fprop_global *p,
					काष्ठा fprop_local_single *pl)
अणु
	अचिन्हित पूर्णांक period = p->period;
	अचिन्हित दीर्घ flags;

	/* Fast path - period didn't change */
	अगर (pl->period == period)
		वापस;
	raw_spin_lock_irqsave(&pl->lock, flags);
	/* Someone updated pl->period जबतक we were spinning? */
	अगर (pl->period >= period) अणु
		raw_spin_unlock_irqrestore(&pl->lock, flags);
		वापस;
	पूर्ण
	/* Aging zeroed our fraction? */
	अगर (period - pl->period < BITS_PER_LONG)
		pl->events >>= period - pl->period;
	अन्यथा
		pl->events = 0;
	pl->period = period;
	raw_spin_unlock_irqrestore(&pl->lock, flags);
पूर्ण

/* Event of type pl happened */
व्योम __fprop_inc_single(काष्ठा fprop_global *p, काष्ठा fprop_local_single *pl)
अणु
	fprop_reflect_period_single(p, pl);
	pl->events++;
	percpu_counter_add(&p->events, 1);
पूर्ण

/* Return fraction of events of type pl */
व्योम fprop_fraction_single(काष्ठा fprop_global *p,
			   काष्ठा fprop_local_single *pl,
			   अचिन्हित दीर्घ *numerator, अचिन्हित दीर्घ *denominator)
अणु
	अचिन्हित पूर्णांक seq;
	s64 num, den;

	करो अणु
		seq = पढ़ो_seqcount_begin(&p->sequence);
		fprop_reflect_period_single(p, pl);
		num = pl->events;
		den = percpu_counter_पढ़ो_positive(&p->events);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&p->sequence, seq));

	/*
	 * Make fraction <= 1 and denominator > 0 even in presence of percpu
	 * counter errors
	 */
	अगर (den <= num) अणु
		अगर (num)
			den = num;
		अन्यथा
			den = 1;
	पूर्ण
	*denominator = den;
	*numerator = num;
पूर्ण

/*
 * ---- PERCPU ----
 */
#घोषणा PROP_BATCH (8*(1+ilog2(nr_cpu_ids)))

पूर्णांक fprop_local_init_percpu(काष्ठा fprop_local_percpu *pl, gfp_t gfp)
अणु
	पूर्णांक err;

	err = percpu_counter_init(&pl->events, 0, gfp);
	अगर (err)
		वापस err;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	वापस 0;
पूर्ण

व्योम fprop_local_destroy_percpu(काष्ठा fprop_local_percpu *pl)
अणु
	percpu_counter_destroy(&pl->events);
पूर्ण

अटल व्योम fprop_reflect_period_percpu(काष्ठा fprop_global *p,
					काष्ठा fprop_local_percpu *pl)
अणु
	अचिन्हित पूर्णांक period = p->period;
	अचिन्हित दीर्घ flags;

	/* Fast path - period didn't change */
	अगर (pl->period == period)
		वापस;
	raw_spin_lock_irqsave(&pl->lock, flags);
	/* Someone updated pl->period जबतक we were spinning? */
	अगर (pl->period >= period) अणु
		raw_spin_unlock_irqrestore(&pl->lock, flags);
		वापस;
	पूर्ण
	/* Aging zeroed our fraction? */
	अगर (period - pl->period < BITS_PER_LONG) अणु
		s64 val = percpu_counter_पढ़ो(&pl->events);

		अगर (val < (nr_cpu_ids * PROP_BATCH))
			val = percpu_counter_sum(&pl->events);

		percpu_counter_add_batch(&pl->events,
			-val + (val >> (period-pl->period)), PROP_BATCH);
	पूर्ण अन्यथा
		percpu_counter_set(&pl->events, 0);
	pl->period = period;
	raw_spin_unlock_irqrestore(&pl->lock, flags);
पूर्ण

/* Event of type pl happened */
व्योम __fprop_inc_percpu(काष्ठा fprop_global *p, काष्ठा fprop_local_percpu *pl)
अणु
	fprop_reflect_period_percpu(p, pl);
	percpu_counter_add_batch(&pl->events, 1, PROP_BATCH);
	percpu_counter_add(&p->events, 1);
पूर्ण

व्योम fprop_fraction_percpu(काष्ठा fprop_global *p,
			   काष्ठा fprop_local_percpu *pl,
			   अचिन्हित दीर्घ *numerator, अचिन्हित दीर्घ *denominator)
अणु
	अचिन्हित पूर्णांक seq;
	s64 num, den;

	करो अणु
		seq = पढ़ो_seqcount_begin(&p->sequence);
		fprop_reflect_period_percpu(p, pl);
		num = percpu_counter_पढ़ो_positive(&pl->events);
		den = percpu_counter_पढ़ो_positive(&p->events);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&p->sequence, seq));

	/*
	 * Make fraction <= 1 and denominator > 0 even in presence of percpu
	 * counter errors
	 */
	अगर (den <= num) अणु
		अगर (num)
			den = num;
		अन्यथा
			den = 1;
	पूर्ण
	*denominator = den;
	*numerator = num;
पूर्ण

/*
 * Like __fprop_inc_percpu() except that event is counted only अगर the given
 * type has fraction smaller than @max_frac/FPROP_FRAC_BASE
 */
व्योम __fprop_inc_percpu_max(काष्ठा fprop_global *p,
			    काष्ठा fprop_local_percpu *pl, पूर्णांक max_frac)
अणु
	अगर (unlikely(max_frac < FPROP_FRAC_BASE)) अणु
		अचिन्हित दीर्घ numerator, denominator;

		fprop_fraction_percpu(p, pl, &numerator, &denominator);
		अगर (numerator >
		    (((u64)denominator) * max_frac) >> FPROP_FRAC_SHIFT)
			वापस;
	पूर्ण

	__fprop_inc_percpu(p, pl);
पूर्ण
