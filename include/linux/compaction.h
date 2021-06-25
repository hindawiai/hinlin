<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_COMPACTION_H
#घोषणा _LINUX_COMPACTION_H

/*
 * Determines how hard direct compaction should try to succeed.
 * Lower value means higher priority, analogically to reclaim priority.
 */
क्रमागत compact_priority अणु
	COMPACT_PRIO_SYNC_FULL,
	MIN_COMPACT_PRIORITY = COMPACT_PRIO_SYNC_FULL,
	COMPACT_PRIO_SYNC_LIGHT,
	MIN_COMPACT_COSTLY_PRIORITY = COMPACT_PRIO_SYNC_LIGHT,
	DEF_COMPACT_PRIORITY = COMPACT_PRIO_SYNC_LIGHT,
	COMPACT_PRIO_ASYNC,
	INIT_COMPACT_PRIORITY = COMPACT_PRIO_ASYNC
पूर्ण;

/* Return values क्रम compact_zone() and try_to_compact_pages() */
/* When adding new states, please adjust include/trace/events/compaction.h */
क्रमागत compact_result अणु
	/* For more detailed tracepoपूर्णांक output - पूर्णांकernal to compaction */
	COMPACT_NOT_SUITABLE_ZONE,
	/*
	 * compaction didn't start as it was not possible or direct reclaim
	 * was more suitable
	 */
	COMPACT_SKIPPED,
	/* compaction didn't start as it was deferred due to past failures */
	COMPACT_DEFERRED,

	/* For more detailed tracepoपूर्णांक output - पूर्णांकernal to compaction */
	COMPACT_NO_SUITABLE_PAGE,
	/* compaction should जारी to another pageblock */
	COMPACT_CONTINUE,

	/*
	 * The full zone was compacted scanned but wasn't successfull to compact
	 * suitable pages.
	 */
	COMPACT_COMPLETE,
	/*
	 * direct compaction has scanned part of the zone but wasn't successfull
	 * to compact suitable pages.
	 */
	COMPACT_PARTIAL_SKIPPED,

	/* compaction terminated prematurely due to lock contentions */
	COMPACT_CONTENDED,

	/*
	 * direct compaction terminated after concluding that the allocation
	 * should now succeed
	 */
	COMPACT_SUCCESS,
पूर्ण;

काष्ठा alloc_context; /* in mm/पूर्णांकernal.h */

/*
 * Number of मुक्त order-0 pages that should be available above given watermark
 * to make sure compaction has reasonable chance of not running out of मुक्त
 * pages that it needs to isolate as migration target during its work.
 */
अटल अंतरभूत अचिन्हित दीर्घ compact_gap(अचिन्हित पूर्णांक order)
अणु
	/*
	 * Although all the isolations क्रम migration are temporary, compaction
	 * मुक्त scanner may have up to 1 << order pages on its list and then
	 * try to split an (order - 1) मुक्त page. At that poपूर्णांक, a gap of
	 * 1 << order might not be enough, so it's safer to require twice that
	 * amount. Note that the number of pages on the list is also
	 * effectively limited by COMPACT_CLUSTER_MAX, as that's the maximum
	 * that the migrate scanner can have isolated on migrate list, and मुक्त
	 * scanner is only invoked when the number of isolated मुक्त pages is
	 * lower than that. But it's not worth to complicate the क्रमmula here
	 * as a bigger gap क्रम higher orders than strictly necessary can also
	 * improve chances of compaction success.
	 */
	वापस 2UL << order;
पूर्ण

#अगर_घोषित CONFIG_COMPACTION
बाह्य अचिन्हित पूर्णांक sysctl_compaction_proactiveness;
बाह्य पूर्णांक sysctl_compaction_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *length, loff_t *ppos);
बाह्य पूर्णांक sysctl_extfrag_threshold;
बाह्य पूर्णांक sysctl_compact_unevictable_allowed;

बाह्य अचिन्हित पूर्णांक extfrag_क्रम_order(काष्ठा zone *zone, अचिन्हित पूर्णांक order);
बाह्य पूर्णांक fragmentation_index(काष्ठा zone *zone, अचिन्हित पूर्णांक order);
बाह्य क्रमागत compact_result try_to_compact_pages(gfp_t gfp_mask,
		अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक alloc_flags,
		स्थिर काष्ठा alloc_context *ac, क्रमागत compact_priority prio,
		काष्ठा page **page);
बाह्य व्योम reset_isolation_suitable(pg_data_t *pgdat);
बाह्य क्रमागत compact_result compaction_suitable(काष्ठा zone *zone, पूर्णांक order,
		अचिन्हित पूर्णांक alloc_flags, पूर्णांक highest_zoneidx);

बाह्य व्योम compaction_defer_reset(काष्ठा zone *zone, पूर्णांक order,
				bool alloc_success);

/* Compaction has made some progress and retrying makes sense */
अटल अंतरभूत bool compaction_made_progress(क्रमागत compact_result result)
अणु
	/*
	 * Even though this might sound confusing this in fact tells us
	 * that the compaction successfully isolated and migrated some
	 * pageblocks.
	 */
	अगर (result == COMPACT_SUCCESS)
		वापस true;

	वापस false;
पूर्ण

/* Compaction has failed and it करोesn't make much sense to keep retrying. */
अटल अंतरभूत bool compaction_failed(क्रमागत compact_result result)
अणु
	/* All zones were scanned completely and still not result. */
	अगर (result == COMPACT_COMPLETE)
		वापस true;

	वापस false;
पूर्ण

/* Compaction needs reclaim to be perक्रमmed first, so it can जारी. */
अटल अंतरभूत bool compaction_needs_reclaim(क्रमागत compact_result result)
अणु
	/*
	 * Compaction backed off due to watermark checks क्रम order-0
	 * so the regular reclaim has to try harder and reclaim something.
	 */
	अगर (result == COMPACT_SKIPPED)
		वापस true;

	वापस false;
पूर्ण

/*
 * Compaction has backed off क्रम some reason after करोing some work or none
 * at all. It might be throttling or lock contention. Retrying might be still
 * worthजबतक, but with a higher priority अगर allowed.
 */
अटल अंतरभूत bool compaction_withdrawn(क्रमागत compact_result result)
अणु
	/*
	 * If compaction is deferred क्रम high-order allocations, it is
	 * because sync compaction recently failed. If this is the हाल
	 * and the caller requested a THP allocation, we करो not want
	 * to heavily disrupt the प्रणाली, so we fail the allocation
	 * instead of entering direct reclaim.
	 */
	अगर (result == COMPACT_DEFERRED)
		वापस true;

	/*
	 * If compaction in async mode encounters contention or blocks higher
	 * priority task we back off early rather than cause stalls.
	 */
	अगर (result == COMPACT_CONTENDED)
		वापस true;

	/*
	 * Page scanners have met but we haven't scanned full zones so this
	 * is a back off in fact.
	 */
	अगर (result == COMPACT_PARTIAL_SKIPPED)
		वापस true;

	वापस false;
पूर्ण


bool compaction_zonelist_suitable(काष्ठा alloc_context *ac, पूर्णांक order,
					पूर्णांक alloc_flags);

बाह्य पूर्णांक kcompactd_run(पूर्णांक nid);
बाह्य व्योम kcompactd_stop(पूर्णांक nid);
बाह्य व्योम wakeup_kcompactd(pg_data_t *pgdat, पूर्णांक order, पूर्णांक highest_zoneidx);

#अन्यथा
अटल अंतरभूत व्योम reset_isolation_suitable(pg_data_t *pgdat)
अणु
पूर्ण

अटल अंतरभूत क्रमागत compact_result compaction_suitable(काष्ठा zone *zone, पूर्णांक order,
					पूर्णांक alloc_flags, पूर्णांक highest_zoneidx)
अणु
	वापस COMPACT_SKIPPED;
पूर्ण

अटल अंतरभूत bool compaction_made_progress(क्रमागत compact_result result)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool compaction_failed(क्रमागत compact_result result)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool compaction_needs_reclaim(क्रमागत compact_result result)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool compaction_withdrawn(क्रमागत compact_result result)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक kcompactd_run(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kcompactd_stop(पूर्णांक nid)
अणु
पूर्ण

अटल अंतरभूत व्योम wakeup_kcompactd(pg_data_t *pgdat,
				पूर्णांक order, पूर्णांक highest_zoneidx)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPACTION */

काष्ठा node;
#अगर defined(CONFIG_COMPACTION) && defined(CONFIG_SYSFS) && defined(CONFIG_NUMA)
बाह्य पूर्णांक compaction_रेजिस्टर_node(काष्ठा node *node);
बाह्य व्योम compaction_unरेजिस्टर_node(काष्ठा node *node);

#अन्यथा

अटल अंतरभूत पूर्णांक compaction_रेजिस्टर_node(काष्ठा node *node)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम compaction_unरेजिस्टर_node(काष्ठा node *node)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPACTION && CONFIG_SYSFS && CONFIG_NUMA */

#पूर्ण_अगर /* _LINUX_COMPACTION_H */
