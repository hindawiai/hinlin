<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_STATS_H_
#घोषणा _BCACHE_STATS_H_

काष्ठा cache_stat_collector अणु
	atomic_t cache_hits;
	atomic_t cache_misses;
	atomic_t cache_bypass_hits;
	atomic_t cache_bypass_misses;
	atomic_t cache_miss_collisions;
	atomic_t sectors_bypassed;
पूर्ण;

काष्ठा cache_stats अणु
	काष्ठा kobject		kobj;

	अचिन्हित दीर्घ cache_hits;
	अचिन्हित दीर्घ cache_misses;
	अचिन्हित दीर्घ cache_bypass_hits;
	अचिन्हित दीर्घ cache_bypass_misses;
	अचिन्हित दीर्घ cache_पढ़ोaheads;
	अचिन्हित दीर्घ cache_miss_collisions;
	अचिन्हित दीर्घ sectors_bypassed;

	अचिन्हित पूर्णांक		rescale;
पूर्ण;

काष्ठा cache_accounting अणु
	काष्ठा closure		cl;
	काष्ठा समयr_list	समयr;
	atomic_t		closing;

	काष्ठा cache_stat_collector collector;

	काष्ठा cache_stats total;
	काष्ठा cache_stats five_minute;
	काष्ठा cache_stats hour;
	काष्ठा cache_stats day;
पूर्ण;

काष्ठा cache_set;
काष्ठा cached_dev;
काष्ठा bcache_device;

व्योम bch_cache_accounting_init(काष्ठा cache_accounting *acc,
			       काष्ठा closure *parent);

पूर्णांक bch_cache_accounting_add_kobjs(काष्ठा cache_accounting *acc,
				   काष्ठा kobject *parent);

व्योम bch_cache_accounting_clear(काष्ठा cache_accounting *acc);

व्योम bch_cache_accounting_destroy(काष्ठा cache_accounting *acc);

व्योम bch_mark_cache_accounting(काष्ठा cache_set *c, काष्ठा bcache_device *d,
			       bool hit, bool bypass);
व्योम bch_mark_cache_पढ़ोahead(काष्ठा cache_set *c, काष्ठा bcache_device *d);
व्योम bch_mark_cache_miss_collision(काष्ठा cache_set *c,
				   काष्ठा bcache_device *d);
व्योम bch_mark_sectors_bypassed(काष्ठा cache_set *c,
			       काष्ठा cached_dev *dc,
			       पूर्णांक sectors);

#पूर्ण_अगर /* _BCACHE_STATS_H_ */
