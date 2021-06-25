<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM compaction

#अगर !defined(_TRACE_COMPACTION_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_COMPACTION_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/mmflags.h>


DECLARE_EVENT_CLASS(mm_compaction_isolate_ढाँचा,

	TP_PROTO(
		अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ end_pfn,
		अचिन्हित दीर्घ nr_scanned,
		अचिन्हित दीर्घ nr_taken),

	TP_ARGS(start_pfn, end_pfn, nr_scanned, nr_taken),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, start_pfn)
		__field(अचिन्हित दीर्घ, end_pfn)
		__field(अचिन्हित दीर्घ, nr_scanned)
		__field(अचिन्हित दीर्घ, nr_taken)
	),

	TP_fast_assign(
		__entry->start_pfn = start_pfn;
		__entry->end_pfn = end_pfn;
		__entry->nr_scanned = nr_scanned;
		__entry->nr_taken = nr_taken;
	),

	TP_prपूर्णांकk("range=(0x%lx ~ 0x%lx) nr_scanned=%lu nr_taken=%lu",
		__entry->start_pfn,
		__entry->end_pfn,
		__entry->nr_scanned,
		__entry->nr_taken)
);

DEFINE_EVENT(mm_compaction_isolate_ढाँचा, mm_compaction_isolate_migratepages,

	TP_PROTO(
		अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ end_pfn,
		अचिन्हित दीर्घ nr_scanned,
		अचिन्हित दीर्घ nr_taken),

	TP_ARGS(start_pfn, end_pfn, nr_scanned, nr_taken)
);

DEFINE_EVENT(mm_compaction_isolate_ढाँचा, mm_compaction_isolate_मुक्तpages,

	TP_PROTO(
		अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ end_pfn,
		अचिन्हित दीर्घ nr_scanned,
		अचिन्हित दीर्घ nr_taken),

	TP_ARGS(start_pfn, end_pfn, nr_scanned, nr_taken)
);

#अगर_घोषित CONFIG_COMPACTION
TRACE_EVENT(mm_compaction_migratepages,

	TP_PROTO(अचिन्हित दीर्घ nr_all,
		पूर्णांक migrate_rc,
		काष्ठा list_head *migratepages),

	TP_ARGS(nr_all, migrate_rc, migratepages),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, nr_migrated)
		__field(अचिन्हित दीर्घ, nr_failed)
	),

	TP_fast_assign(
		अचिन्हित दीर्घ nr_failed = 0;
		काष्ठा list_head *page_lru;

		/*
		 * migrate_pages() वापसs either a non-negative number
		 * with the number of pages that failed migration, or an
		 * error code, in which हाल we need to count the reमुख्यing
		 * pages manually
		 */
		अगर (migrate_rc >= 0)
			nr_failed = migrate_rc;
		अन्यथा
			list_क्रम_each(page_lru, migratepages)
				nr_failed++;

		__entry->nr_migrated = nr_all - nr_failed;
		__entry->nr_failed = nr_failed;
	),

	TP_prपूर्णांकk("nr_migrated=%lu nr_failed=%lu",
		__entry->nr_migrated,
		__entry->nr_failed)
);

TRACE_EVENT(mm_compaction_begin,
	TP_PROTO(अचिन्हित दीर्घ zone_start, अचिन्हित दीर्घ migrate_pfn,
		अचिन्हित दीर्घ मुक्त_pfn, अचिन्हित दीर्घ zone_end, bool sync),

	TP_ARGS(zone_start, migrate_pfn, मुक्त_pfn, zone_end, sync),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, zone_start)
		__field(अचिन्हित दीर्घ, migrate_pfn)
		__field(अचिन्हित दीर्घ, मुक्त_pfn)
		__field(अचिन्हित दीर्घ, zone_end)
		__field(bool, sync)
	),

	TP_fast_assign(
		__entry->zone_start = zone_start;
		__entry->migrate_pfn = migrate_pfn;
		__entry->मुक्त_pfn = मुक्त_pfn;
		__entry->zone_end = zone_end;
		__entry->sync = sync;
	),

	TP_prपूर्णांकk("zone_start=0x%lx migrate_pfn=0x%lx free_pfn=0x%lx zone_end=0x%lx, mode=%s",
		__entry->zone_start,
		__entry->migrate_pfn,
		__entry->मुक्त_pfn,
		__entry->zone_end,
		__entry->sync ? "sync" : "async")
);

TRACE_EVENT(mm_compaction_end,
	TP_PROTO(अचिन्हित दीर्घ zone_start, अचिन्हित दीर्घ migrate_pfn,
		अचिन्हित दीर्घ मुक्त_pfn, अचिन्हित दीर्घ zone_end, bool sync,
		पूर्णांक status),

	TP_ARGS(zone_start, migrate_pfn, मुक्त_pfn, zone_end, sync, status),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, zone_start)
		__field(अचिन्हित दीर्घ, migrate_pfn)
		__field(अचिन्हित दीर्घ, मुक्त_pfn)
		__field(अचिन्हित दीर्घ, zone_end)
		__field(bool, sync)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->zone_start = zone_start;
		__entry->migrate_pfn = migrate_pfn;
		__entry->मुक्त_pfn = मुक्त_pfn;
		__entry->zone_end = zone_end;
		__entry->sync = sync;
		__entry->status = status;
	),

	TP_prपूर्णांकk("zone_start=0x%lx migrate_pfn=0x%lx free_pfn=0x%lx zone_end=0x%lx, mode=%s status=%s",
		__entry->zone_start,
		__entry->migrate_pfn,
		__entry->मुक्त_pfn,
		__entry->zone_end,
		__entry->sync ? "sync" : "async",
		__prपूर्णांक_symbolic(__entry->status, COMPACTION_STATUS))
);

TRACE_EVENT(mm_compaction_try_to_compact_pages,

	TP_PROTO(
		पूर्णांक order,
		gfp_t gfp_mask,
		पूर्णांक prio),

	TP_ARGS(order, gfp_mask, prio),

	TP_STRUCT__entry(
		__field(पूर्णांक, order)
		__field(gfp_t, gfp_mask)
		__field(पूर्णांक, prio)
	),

	TP_fast_assign(
		__entry->order = order;
		__entry->gfp_mask = gfp_mask;
		__entry->prio = prio;
	),

	TP_prपूर्णांकk("order=%d gfp_mask=%s priority=%d",
		__entry->order,
		show_gfp_flags(__entry->gfp_mask),
		__entry->prio)
);

DECLARE_EVENT_CLASS(mm_compaction_suitable_ढाँचा,

	TP_PROTO(काष्ठा zone *zone,
		पूर्णांक order,
		पूर्णांक ret),

	TP_ARGS(zone, order, ret),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(क्रमागत zone_type, idx)
		__field(पूर्णांक, order)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->nid = zone_to_nid(zone);
		__entry->idx = zone_idx(zone);
		__entry->order = order;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("node=%d zone=%-8s order=%d ret=%s",
		__entry->nid,
		__prपूर्णांक_symbolic(__entry->idx, ZONE_TYPE),
		__entry->order,
		__prपूर्णांक_symbolic(__entry->ret, COMPACTION_STATUS))
);

DEFINE_EVENT(mm_compaction_suitable_ढाँचा, mm_compaction_finished,

	TP_PROTO(काष्ठा zone *zone,
		पूर्णांक order,
		पूर्णांक ret),

	TP_ARGS(zone, order, ret)
);

DEFINE_EVENT(mm_compaction_suitable_ढाँचा, mm_compaction_suitable,

	TP_PROTO(काष्ठा zone *zone,
		पूर्णांक order,
		पूर्णांक ret),

	TP_ARGS(zone, order, ret)
);

DECLARE_EVENT_CLASS(mm_compaction_defer_ढाँचा,

	TP_PROTO(काष्ठा zone *zone, पूर्णांक order),

	TP_ARGS(zone, order),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(क्रमागत zone_type, idx)
		__field(पूर्णांक, order)
		__field(अचिन्हित पूर्णांक, considered)
		__field(अचिन्हित पूर्णांक, defer_shअगरt)
		__field(पूर्णांक, order_failed)
	),

	TP_fast_assign(
		__entry->nid = zone_to_nid(zone);
		__entry->idx = zone_idx(zone);
		__entry->order = order;
		__entry->considered = zone->compact_considered;
		__entry->defer_shअगरt = zone->compact_defer_shअगरt;
		__entry->order_failed = zone->compact_order_failed;
	),

	TP_prपूर्णांकk("node=%d zone=%-8s order=%d order_failed=%d consider=%u limit=%lu",
		__entry->nid,
		__prपूर्णांक_symbolic(__entry->idx, ZONE_TYPE),
		__entry->order,
		__entry->order_failed,
		__entry->considered,
		1UL << __entry->defer_shअगरt)
);

DEFINE_EVENT(mm_compaction_defer_ढाँचा, mm_compaction_deferred,

	TP_PROTO(काष्ठा zone *zone, पूर्णांक order),

	TP_ARGS(zone, order)
);

DEFINE_EVENT(mm_compaction_defer_ढाँचा, mm_compaction_defer_compaction,

	TP_PROTO(काष्ठा zone *zone, पूर्णांक order),

	TP_ARGS(zone, order)
);

DEFINE_EVENT(mm_compaction_defer_ढाँचा, mm_compaction_defer_reset,

	TP_PROTO(काष्ठा zone *zone, पूर्णांक order),

	TP_ARGS(zone, order)
);

TRACE_EVENT(mm_compaction_kcompactd_sleep,

	TP_PROTO(पूर्णांक nid),

	TP_ARGS(nid),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
	),

	TP_fast_assign(
		__entry->nid = nid;
	),

	TP_prपूर्णांकk("nid=%d", __entry->nid)
);

DECLARE_EVENT_CLASS(kcompactd_wake_ढाँचा,

	TP_PROTO(पूर्णांक nid, पूर्णांक order, क्रमागत zone_type highest_zoneidx),

	TP_ARGS(nid, order, highest_zoneidx),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(पूर्णांक, order)
		__field(क्रमागत zone_type, highest_zoneidx)
	),

	TP_fast_assign(
		__entry->nid = nid;
		__entry->order = order;
		__entry->highest_zoneidx = highest_zoneidx;
	),

	/*
	 * classzone_idx is previous name of the highest_zoneidx.
	 * Reason not to change it is the ABI requirement of the tracepoपूर्णांक.
	 */
	TP_prपूर्णांकk("nid=%d order=%d classzone_idx=%-8s",
		__entry->nid,
		__entry->order,
		__prपूर्णांक_symbolic(__entry->highest_zoneidx, ZONE_TYPE))
);

DEFINE_EVENT(kcompactd_wake_ढाँचा, mm_compaction_wakeup_kcompactd,

	TP_PROTO(पूर्णांक nid, पूर्णांक order, क्रमागत zone_type highest_zoneidx),

	TP_ARGS(nid, order, highest_zoneidx)
);

DEFINE_EVENT(kcompactd_wake_ढाँचा, mm_compaction_kcompactd_wake,

	TP_PROTO(पूर्णांक nid, पूर्णांक order, क्रमागत zone_type highest_zoneidx),

	TP_ARGS(nid, order, highest_zoneidx)
);
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_COMPACTION_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
