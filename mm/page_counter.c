<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lockless hierarchical page accounting & limiting
 *
 * Copyright (C) 2014 Red Hat, Inc., Johannes Weiner
 */

#समावेश <linux/page_counter.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/page.h>

अटल व्योम propagate_रक्षित_usage(काष्ठा page_counter *c,
				      अचिन्हित दीर्घ usage)
अणु
	अचिन्हित दीर्घ रक्षित, old_रक्षित;
	अचिन्हित दीर्घ low, min;
	दीर्घ delta;

	अगर (!c->parent)
		वापस;

	min = READ_ONCE(c->min);
	अगर (min || atomic_दीर्घ_पढ़ो(&c->min_usage)) अणु
		रक्षित = min(usage, min);
		old_रक्षित = atomic_दीर्घ_xchg(&c->min_usage, रक्षित);
		delta = रक्षित - old_रक्षित;
		अगर (delta)
			atomic_दीर्घ_add(delta, &c->parent->children_min_usage);
	पूर्ण

	low = READ_ONCE(c->low);
	अगर (low || atomic_दीर्घ_पढ़ो(&c->low_usage)) अणु
		रक्षित = min(usage, low);
		old_रक्षित = atomic_दीर्घ_xchg(&c->low_usage, रक्षित);
		delta = रक्षित - old_रक्षित;
		अगर (delta)
			atomic_दीर्घ_add(delta, &c->parent->children_low_usage);
	पूर्ण
पूर्ण

/**
 * page_counter_cancel - take pages out of the local counter
 * @counter: counter
 * @nr_pages: number of pages to cancel
 */
व्योम page_counter_cancel(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	दीर्घ new;

	new = atomic_दीर्घ_sub_वापस(nr_pages, &counter->usage);
	/* More unअक्षरges than अक्षरges? */
	अगर (WARN_ONCE(new < 0, "page_counter underflow: %ld nr_pages=%lu\n",
		      new, nr_pages)) अणु
		new = 0;
		atomic_दीर्घ_set(&counter->usage, new);
	पूर्ण
	propagate_रक्षित_usage(counter, new);
पूर्ण

/**
 * page_counter_अक्षरge - hierarchically अक्षरge pages
 * @counter: counter
 * @nr_pages: number of pages to अक्षरge
 *
 * NOTE: This करोes not consider any configured counter limits.
 */
व्योम page_counter_अक्षरge(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page_counter *c;

	क्रम (c = counter; c; c = c->parent) अणु
		दीर्घ new;

		new = atomic_दीर्घ_add_वापस(nr_pages, &c->usage);
		propagate_रक्षित_usage(c, new);
		/*
		 * This is indeed racy, but we can live with some
		 * inaccuracy in the watermark.
		 */
		अगर (new > READ_ONCE(c->watermark))
			WRITE_ONCE(c->watermark, new);
	पूर्ण
पूर्ण

/**
 * page_counter_try_अक्षरge - try to hierarchically अक्षरge pages
 * @counter: counter
 * @nr_pages: number of pages to अक्षरge
 * @fail: poपूर्णांकs first counter to hit its limit, अगर any
 *
 * Returns %true on success, or %false and @fail अगर the counter or one
 * of its ancestors has hit its configured limit.
 */
bool page_counter_try_अक्षरge(काष्ठा page_counter *counter,
			     अचिन्हित दीर्घ nr_pages,
			     काष्ठा page_counter **fail)
अणु
	काष्ठा page_counter *c;

	क्रम (c = counter; c; c = c->parent) अणु
		दीर्घ new;
		/*
		 * Charge speculatively to aव्योम an expensive CAS.  If
		 * a bigger अक्षरge fails, it might falsely lock out a
		 * racing smaller अक्षरge and send it पूर्णांकo reclaim
		 * early, but the error is limited to the dअगरference
		 * between the two sizes, which is less than 2M/4M in
		 * हाल of a THP locking out a regular page अक्षरge.
		 *
		 * The atomic_दीर्घ_add_वापस() implies a full memory
		 * barrier between incrementing the count and पढ़ोing
		 * the limit.  When racing with page_counter_set_max(),
		 * we either see the new limit or the setter sees the
		 * counter has changed and retries.
		 */
		new = atomic_दीर्घ_add_वापस(nr_pages, &c->usage);
		अगर (new > c->max) अणु
			atomic_दीर्घ_sub(nr_pages, &c->usage);
			propagate_रक्षित_usage(c, new);
			/*
			 * This is racy, but we can live with some
			 * inaccuracy in the failcnt which is only used
			 * to report stats.
			 */
			data_race(c->failcnt++);
			*fail = c;
			जाओ failed;
		पूर्ण
		propagate_रक्षित_usage(c, new);
		/*
		 * Just like with failcnt, we can live with some
		 * inaccuracy in the watermark.
		 */
		अगर (new > READ_ONCE(c->watermark))
			WRITE_ONCE(c->watermark, new);
	पूर्ण
	वापस true;

failed:
	क्रम (c = counter; c != *fail; c = c->parent)
		page_counter_cancel(c, nr_pages);

	वापस false;
पूर्ण

/**
 * page_counter_unअक्षरge - hierarchically unअक्षरge pages
 * @counter: counter
 * @nr_pages: number of pages to unअक्षरge
 */
व्योम page_counter_unअक्षरge(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page_counter *c;

	क्रम (c = counter; c; c = c->parent)
		page_counter_cancel(c, nr_pages);
पूर्ण

/**
 * page_counter_set_max - set the maximum number of pages allowed
 * @counter: counter
 * @nr_pages: limit to set
 *
 * Returns 0 on success, -EBUSY अगर the current number of pages on the
 * counter alपढ़ोy exceeds the specअगरied limit.
 *
 * The caller must serialize invocations on the same counter.
 */
पूर्णांक page_counter_set_max(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	क्रम (;;) अणु
		अचिन्हित दीर्घ old;
		दीर्घ usage;

		/*
		 * Update the limit जबतक making sure that it's not
		 * below the concurrently-changing counter value.
		 *
		 * The xchg implies two full memory barriers beक्रमe
		 * and after, so the पढ़ो-swap-पढ़ो is ordered and
		 * ensures coherency with page_counter_try_अक्षरge():
		 * that function modअगरies the count beक्रमe checking
		 * the limit, so अगर it sees the old limit, we see the
		 * modअगरied counter and retry.
		 */
		usage = page_counter_पढ़ो(counter);

		अगर (usage > nr_pages)
			वापस -EBUSY;

		old = xchg(&counter->max, nr_pages);

		अगर (page_counter_पढ़ो(counter) <= usage)
			वापस 0;

		counter->max = old;
		cond_resched();
	पूर्ण
पूर्ण

/**
 * page_counter_set_min - set the amount of रक्षित memory
 * @counter: counter
 * @nr_pages: value to set
 *
 * The caller must serialize invocations on the same counter.
 */
व्योम page_counter_set_min(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page_counter *c;

	WRITE_ONCE(counter->min, nr_pages);

	क्रम (c = counter; c; c = c->parent)
		propagate_रक्षित_usage(c, atomic_दीर्घ_पढ़ो(&c->usage));
पूर्ण

/**
 * page_counter_set_low - set the amount of रक्षित memory
 * @counter: counter
 * @nr_pages: value to set
 *
 * The caller must serialize invocations on the same counter.
 */
व्योम page_counter_set_low(काष्ठा page_counter *counter, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page_counter *c;

	WRITE_ONCE(counter->low, nr_pages);

	क्रम (c = counter; c; c = c->parent)
		propagate_रक्षित_usage(c, atomic_दीर्घ_पढ़ो(&c->usage));
पूर्ण

/**
 * page_counter_memparse - memparse() क्रम page counter limits
 * @buf: string to parse
 * @max: string meaning maximum possible value
 * @nr_pages: वापसs the result in number of pages
 *
 * Returns -EINVAL, or 0 and @nr_pages on success.  @nr_pages will be
 * limited to %PAGE_COUNTER_MAX.
 */
पूर्णांक page_counter_memparse(स्थिर अक्षर *buf, स्थिर अक्षर *max,
			  अचिन्हित दीर्घ *nr_pages)
अणु
	अक्षर *end;
	u64 bytes;

	अगर (!म_भेद(buf, max)) अणु
		*nr_pages = PAGE_COUNTER_MAX;
		वापस 0;
	पूर्ण

	bytes = memparse(buf, &end);
	अगर (*end != '\0')
		वापस -EINVAL;

	*nr_pages = min(bytes / PAGE_SIZE, (u64)PAGE_COUNTER_MAX);

	वापस 0;
पूर्ण
