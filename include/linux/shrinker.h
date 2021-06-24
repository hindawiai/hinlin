<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SHRINKER_H
#घोषणा _LINUX_SHRINKER_H

/*
 * This काष्ठा is used to pass inक्रमmation from page reclaim to the shrinkers.
 * We consolidate the values क्रम easier extention later.
 *
 * The 'gfpmask' refers to the allocation we are currently trying to
 * fulfil.
 */
काष्ठा shrink_control अणु
	gfp_t gfp_mask;

	/* current node being shrunk (क्रम NUMA aware shrinkers) */
	पूर्णांक nid;

	/*
	 * How many objects scan_objects should scan and try to reclaim.
	 * This is reset beक्रमe every call, so it is safe क्रम callees
	 * to modअगरy.
	 */
	अचिन्हित दीर्घ nr_to_scan;

	/*
	 * How many objects did scan_objects process?
	 * This शेषs to nr_to_scan beक्रमe every call, but the callee
	 * should track its actual progress.
	 */
	अचिन्हित दीर्घ nr_scanned;

	/* current memcg being shrunk (क्रम memcg aware shrinkers) */
	काष्ठा mem_cgroup *memcg;
पूर्ण;

#घोषणा SHRINK_STOP (~0UL)
#घोषणा SHRINK_EMPTY (~0UL - 1)
/*
 * A callback you can रेजिस्टर to apply pressure to ageable caches.
 *
 * @count_objects should वापस the number of मुक्तable items in the cache. If
 * there are no objects to मुक्त, it should वापस SHRINK_EMPTY, जबतक 0 is
 * वापसed in हालs of the number of मुक्तable items cannot be determined
 * or shrinker should skip this cache क्रम this समय (e.g., their number
 * is below shrinkable limit). No deadlock checks should be करोne during the
 * count callback - the shrinker relies on aggregating scan counts that couldn't
 * be executed due to potential deadlocks to be run at a later call when the
 * deadlock condition is no दीर्घer pending.
 *
 * @scan_objects will only be called अगर @count_objects वापसed a non-zero
 * value क्रम the number of मुक्तable objects. The callout should scan the cache
 * and attempt to मुक्त items from the cache. It should then वापस the number
 * of objects मुक्तd during the scan, or SHRINK_STOP अगर progress cannot be made
 * due to potential deadlocks. If SHRINK_STOP is वापसed, then no further
 * attempts to call the @scan_objects will be made from the current reclaim
 * context.
 *
 * @flags determine the shrinker abilities, like numa awareness
 */
काष्ठा shrinker अणु
	अचिन्हित दीर्घ (*count_objects)(काष्ठा shrinker *,
				       काष्ठा shrink_control *sc);
	अचिन्हित दीर्घ (*scan_objects)(काष्ठा shrinker *,
				      काष्ठा shrink_control *sc);

	दीर्घ batch;	/* reclaim batch size, 0 = शेष */
	पूर्णांक seeks;	/* seeks to recreate an obj */
	अचिन्हित flags;

	/* These are क्रम पूर्णांकernal use */
	काष्ठा list_head list;
#अगर_घोषित CONFIG_MEMCG
	/* ID in shrinker_idr */
	पूर्णांक id;
#पूर्ण_अगर
	/* objs pending delete, per node */
	atomic_दीर्घ_t *nr_deferred;
पूर्ण;
#घोषणा DEFAULT_SEEKS 2 /* A good number अगर you करोn't know better. */

/* Flags */
#घोषणा SHRINKER_REGISTERED	(1 << 0)
#घोषणा SHRINKER_NUMA_AWARE	(1 << 1)
#घोषणा SHRINKER_MEMCG_AWARE	(1 << 2)
/*
 * It just makes sense when the shrinker is also MEMCG_AWARE क्रम now,
 * non-MEMCG_AWARE shrinker should not have this flag set.
 */
#घोषणा SHRINKER_NONSLAB	(1 << 3)

बाह्य पूर्णांक pपुनः_स्मृति_shrinker(काष्ठा shrinker *shrinker);
बाह्य व्योम रेजिस्टर_shrinker_prepared(काष्ठा shrinker *shrinker);
बाह्य पूर्णांक रेजिस्टर_shrinker(काष्ठा shrinker *shrinker);
बाह्य व्योम unरेजिस्टर_shrinker(काष्ठा shrinker *shrinker);
बाह्य व्योम मुक्त_pपुनः_स्मृतिed_shrinker(काष्ठा shrinker *shrinker);
#पूर्ण_अगर
