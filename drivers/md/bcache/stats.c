<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bcache stats code
 *
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "stats.h"
#समावेश "btree.h"
#समावेश "sysfs.h"

/*
 * We keep असलolute totals of various statistics, and addionally a set of three
 * rolling averages.
 *
 * Every so often, a समयr goes off and rescales the rolling averages.
 * accounting_rescale[] is how many बार the समयr has to go off beक्रमe we
 * rescale each set of numbers; that माला_लो us half lives of 5 minutes, one hour,
 * and one day.
 *
 * accounting_delay is how often the समयr goes off - 22 बार in 5 minutes,
 * and accounting_weight is what we use to rescale:
 *
 * घात(31 / 32, 22) ~= 1/2
 *
 * So that we करोn't have to increment each set of numbers every समय we (say)
 * get a cache hit, we increment a single atomic_t in acc->collector, and when
 * the rescale function runs it resets the atomic counter to 0 and adds its
 * old value to each of the exported numbers.
 *
 * To reduce rounding error, the numbers in काष्ठा cache_stats are all
 * stored left shअगरted by 16, and scaled back in the sysfs show() function.
 */

अटल स्थिर अचिन्हित पूर्णांक DAY_RESCALE		= 288;
अटल स्थिर अचिन्हित पूर्णांक HOUR_RESCALE		= 12;
अटल स्थिर अचिन्हित पूर्णांक FIVE_MINUTE_RESCALE	= 1;
अटल स्थिर अचिन्हित पूर्णांक accounting_delay	= (HZ * 300) / 22;
अटल स्थिर अचिन्हित पूर्णांक accounting_weight	= 32;

/* sysfs पढ़ोing/writing */

पढ़ो_attribute(cache_hits);
पढ़ो_attribute(cache_misses);
पढ़ो_attribute(cache_bypass_hits);
पढ़ो_attribute(cache_bypass_misses);
पढ़ो_attribute(cache_hit_ratio);
पढ़ो_attribute(cache_miss_collisions);
पढ़ो_attribute(bypassed);

SHOW(bch_stats)
अणु
	काष्ठा cache_stats *s =
		container_of(kobj, काष्ठा cache_stats, kobj);
#घोषणा var(stat)		(s->stat >> 16)
	var_prपूर्णांक(cache_hits);
	var_prपूर्णांक(cache_misses);
	var_prपूर्णांक(cache_bypass_hits);
	var_prपूर्णांक(cache_bypass_misses);

	sysfs_prपूर्णांक(cache_hit_ratio,
		    DIV_SAFE(var(cache_hits) * 100,
			     var(cache_hits) + var(cache_misses)));

	var_prपूर्णांक(cache_miss_collisions);
	sysfs_hprपूर्णांक(bypassed,	var(sectors_bypassed) << 9);
#अघोषित var
	वापस 0;
पूर्ण

STORE(bch_stats)
अणु
	वापस size;
पूर्ण

अटल व्योम bch_stats_release(काष्ठा kobject *k)
अणु
पूर्ण

अटल काष्ठा attribute *bch_stats_files[] = अणु
	&sysfs_cache_hits,
	&sysfs_cache_misses,
	&sysfs_cache_bypass_hits,
	&sysfs_cache_bypass_misses,
	&sysfs_cache_hit_ratio,
	&sysfs_cache_miss_collisions,
	&sysfs_bypassed,
	शून्य
पूर्ण;
अटल KTYPE(bch_stats);

पूर्णांक bch_cache_accounting_add_kobjs(काष्ठा cache_accounting *acc,
				   काष्ठा kobject *parent)
अणु
	पूर्णांक ret = kobject_add(&acc->total.kobj, parent,
			      "stats_total");
	ret = ret ?: kobject_add(&acc->five_minute.kobj, parent,
				 "stats_five_minute");
	ret = ret ?: kobject_add(&acc->hour.kobj, parent,
				 "stats_hour");
	ret = ret ?: kobject_add(&acc->day.kobj, parent,
				 "stats_day");
	वापस ret;
पूर्ण

व्योम bch_cache_accounting_clear(काष्ठा cache_accounting *acc)
अणु
	acc->total.cache_hits = 0;
	acc->total.cache_misses = 0;
	acc->total.cache_bypass_hits = 0;
	acc->total.cache_bypass_misses = 0;
	acc->total.cache_miss_collisions = 0;
	acc->total.sectors_bypassed = 0;
पूर्ण

व्योम bch_cache_accounting_destroy(काष्ठा cache_accounting *acc)
अणु
	kobject_put(&acc->total.kobj);
	kobject_put(&acc->five_minute.kobj);
	kobject_put(&acc->hour.kobj);
	kobject_put(&acc->day.kobj);

	atomic_set(&acc->closing, 1);
	अगर (del_समयr_sync(&acc->समयr))
		closure_वापस(&acc->cl);
पूर्ण

/* EWMA scaling */

अटल व्योम scale_stat(अचिन्हित दीर्घ *stat)
अणु
	*stat =  ewma_add(*stat, 0, accounting_weight, 0);
पूर्ण

अटल व्योम scale_stats(काष्ठा cache_stats *stats, अचिन्हित दीर्घ rescale_at)
अणु
	अगर (++stats->rescale == rescale_at) अणु
		stats->rescale = 0;
		scale_stat(&stats->cache_hits);
		scale_stat(&stats->cache_misses);
		scale_stat(&stats->cache_bypass_hits);
		scale_stat(&stats->cache_bypass_misses);
		scale_stat(&stats->cache_miss_collisions);
		scale_stat(&stats->sectors_bypassed);
	पूर्ण
पूर्ण

अटल व्योम scale_accounting(काष्ठा समयr_list *t)
अणु
	काष्ठा cache_accounting *acc = from_समयr(acc, t, समयr);

#घोषणा move_stat(name) करो अणु						\
	अचिन्हित पूर्णांक t = atomic_xchg(&acc->collector.name, 0);		\
	t <<= 16;							\
	acc->five_minute.name += t;					\
	acc->hour.name += t;						\
	acc->day.name += t;						\
	acc->total.name += t;						\
पूर्ण जबतक (0)

	move_stat(cache_hits);
	move_stat(cache_misses);
	move_stat(cache_bypass_hits);
	move_stat(cache_bypass_misses);
	move_stat(cache_miss_collisions);
	move_stat(sectors_bypassed);

	scale_stats(&acc->total, 0);
	scale_stats(&acc->day, DAY_RESCALE);
	scale_stats(&acc->hour, HOUR_RESCALE);
	scale_stats(&acc->five_minute, FIVE_MINUTE_RESCALE);

	acc->समयr.expires += accounting_delay;

	अगर (!atomic_पढ़ो(&acc->closing))
		add_समयr(&acc->समयr);
	अन्यथा
		closure_वापस(&acc->cl);
पूर्ण

अटल व्योम mark_cache_stats(काष्ठा cache_stat_collector *stats,
			     bool hit, bool bypass)
अणु
	अगर (!bypass)
		अगर (hit)
			atomic_inc(&stats->cache_hits);
		अन्यथा
			atomic_inc(&stats->cache_misses);
	अन्यथा
		अगर (hit)
			atomic_inc(&stats->cache_bypass_hits);
		अन्यथा
			atomic_inc(&stats->cache_bypass_misses);
पूर्ण

व्योम bch_mark_cache_accounting(काष्ठा cache_set *c, काष्ठा bcache_device *d,
			       bool hit, bool bypass)
अणु
	काष्ठा cached_dev *dc = container_of(d, काष्ठा cached_dev, disk);

	mark_cache_stats(&dc->accounting.collector, hit, bypass);
	mark_cache_stats(&c->accounting.collector, hit, bypass);
पूर्ण

व्योम bch_mark_cache_miss_collision(काष्ठा cache_set *c, काष्ठा bcache_device *d)
अणु
	काष्ठा cached_dev *dc = container_of(d, काष्ठा cached_dev, disk);

	atomic_inc(&dc->accounting.collector.cache_miss_collisions);
	atomic_inc(&c->accounting.collector.cache_miss_collisions);
पूर्ण

व्योम bch_mark_sectors_bypassed(काष्ठा cache_set *c, काष्ठा cached_dev *dc,
			       पूर्णांक sectors)
अणु
	atomic_add(sectors, &dc->accounting.collector.sectors_bypassed);
	atomic_add(sectors, &c->accounting.collector.sectors_bypassed);
पूर्ण

व्योम bch_cache_accounting_init(काष्ठा cache_accounting *acc,
			       काष्ठा closure *parent)
अणु
	kobject_init(&acc->total.kobj,		&bch_stats_ktype);
	kobject_init(&acc->five_minute.kobj,	&bch_stats_ktype);
	kobject_init(&acc->hour.kobj,		&bch_stats_ktype);
	kobject_init(&acc->day.kobj,		&bch_stats_ktype);

	closure_init(&acc->cl, parent);
	समयr_setup(&acc->समयr, scale_accounting, 0);
	acc->समयr.expires	= jअगरfies + accounting_delay;
	add_समयr(&acc->समयr);
पूर्ण
