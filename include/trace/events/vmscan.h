<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vmscan

#अगर !defined(_TRACE_VMSCAN_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_VMSCAN_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/mm.h>
#समावेश <linux/memcontrol.h>
#समावेश <trace/events/mmflags.h>

#घोषणा RECLAIM_WB_ANON		0x0001u
#घोषणा RECLAIM_WB_खाता		0x0002u
#घोषणा RECLAIM_WB_MIXED	0x0010u
#घोषणा RECLAIM_WB_SYNC		0x0004u /* Unused, all reclaim async */
#घोषणा RECLAIM_WB_ASYNC	0x0008u
#घोषणा RECLAIM_WB_LRU		(RECLAIM_WB_ANON|RECLAIM_WB_खाता)

#घोषणा show_reclaim_flags(flags)				\
	(flags) ? __prपूर्णांक_flags(flags, "|",			\
		अणुRECLAIM_WB_ANON,	"RECLAIM_WB_ANON"पूर्ण,	\
		अणुRECLAIM_WB_खाता,	"RECLAIM_WB_FILE"पूर्ण,	\
		अणुRECLAIM_WB_MIXED,	"RECLAIM_WB_MIXED"पूर्ण,	\
		अणुRECLAIM_WB_SYNC,	"RECLAIM_WB_SYNC"पूर्ण,	\
		अणुRECLAIM_WB_ASYNC,	"RECLAIM_WB_ASYNC"पूर्ण	\
		) : "RECLAIM_WB_NONE"

#घोषणा trace_reclaim_flags(file) ( \
	(file ? RECLAIM_WB_खाता : RECLAIM_WB_ANON) | \
	(RECLAIM_WB_ASYNC) \
	)

TRACE_EVENT(mm_vmscan_kswapd_sleep,

	TP_PROTO(पूर्णांक nid),

	TP_ARGS(nid),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	nid	)
	),

	TP_fast_assign(
		__entry->nid	= nid;
	),

	TP_prपूर्णांकk("nid=%d", __entry->nid)
);

TRACE_EVENT(mm_vmscan_kswapd_wake,

	TP_PROTO(पूर्णांक nid, पूर्णांक zid, पूर्णांक order),

	TP_ARGS(nid, zid, order),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	nid	)
		__field(	पूर्णांक,	zid	)
		__field(	पूर्णांक,	order	)
	),

	TP_fast_assign(
		__entry->nid	= nid;
		__entry->zid    = zid;
		__entry->order	= order;
	),

	TP_prपूर्णांकk("nid=%d order=%d",
		__entry->nid,
		__entry->order)
);

TRACE_EVENT(mm_vmscan_wakeup_kswapd,

	TP_PROTO(पूर्णांक nid, पूर्णांक zid, पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(nid, zid, order, gfp_flags),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	nid		)
		__field(	पूर्णांक,	zid		)
		__field(	पूर्णांक,	order		)
		__field(	gfp_t,	gfp_flags	)
	),

	TP_fast_assign(
		__entry->nid		= nid;
		__entry->zid		= zid;
		__entry->order		= order;
		__entry->gfp_flags	= gfp_flags;
	),

	TP_prपूर्णांकk("nid=%d order=%d gfp_flags=%s",
		__entry->nid,
		__entry->order,
		show_gfp_flags(__entry->gfp_flags))
);

DECLARE_EVENT_CLASS(mm_vmscan_direct_reclaim_begin_ढाँचा,

	TP_PROTO(पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(order, gfp_flags),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	order		)
		__field(	gfp_t,	gfp_flags	)
	),

	TP_fast_assign(
		__entry->order		= order;
		__entry->gfp_flags	= gfp_flags;
	),

	TP_prपूर्णांकk("order=%d gfp_flags=%s",
		__entry->order,
		show_gfp_flags(__entry->gfp_flags))
);

DEFINE_EVENT(mm_vmscan_direct_reclaim_begin_ढाँचा, mm_vmscan_direct_reclaim_begin,

	TP_PROTO(पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(order, gfp_flags)
);

#अगर_घोषित CONFIG_MEMCG
DEFINE_EVENT(mm_vmscan_direct_reclaim_begin_ढाँचा, mm_vmscan_memcg_reclaim_begin,

	TP_PROTO(पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(order, gfp_flags)
);

DEFINE_EVENT(mm_vmscan_direct_reclaim_begin_ढाँचा, mm_vmscan_memcg_softlimit_reclaim_begin,

	TP_PROTO(पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(order, gfp_flags)
);
#पूर्ण_अगर /* CONFIG_MEMCG */

DECLARE_EVENT_CLASS(mm_vmscan_direct_reclaim_end_ढाँचा,

	TP_PROTO(अचिन्हित दीर्घ nr_reclaimed),

	TP_ARGS(nr_reclaimed),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	nr_reclaimed	)
	),

	TP_fast_assign(
		__entry->nr_reclaimed	= nr_reclaimed;
	),

	TP_prपूर्णांकk("nr_reclaimed=%lu", __entry->nr_reclaimed)
);

DEFINE_EVENT(mm_vmscan_direct_reclaim_end_ढाँचा, mm_vmscan_direct_reclaim_end,

	TP_PROTO(अचिन्हित दीर्घ nr_reclaimed),

	TP_ARGS(nr_reclaimed)
);

#अगर_घोषित CONFIG_MEMCG
DEFINE_EVENT(mm_vmscan_direct_reclaim_end_ढाँचा, mm_vmscan_memcg_reclaim_end,

	TP_PROTO(अचिन्हित दीर्घ nr_reclaimed),

	TP_ARGS(nr_reclaimed)
);

DEFINE_EVENT(mm_vmscan_direct_reclaim_end_ढाँचा, mm_vmscan_memcg_softlimit_reclaim_end,

	TP_PROTO(अचिन्हित दीर्घ nr_reclaimed),

	TP_ARGS(nr_reclaimed)
);
#पूर्ण_अगर /* CONFIG_MEMCG */

TRACE_EVENT(mm_shrink_slab_start,
	TP_PROTO(काष्ठा shrinker *shr, काष्ठा shrink_control *sc,
		दीर्घ nr_objects_to_shrink, अचिन्हित दीर्घ cache_items,
		अचिन्हित दीर्घ दीर्घ delta, अचिन्हित दीर्घ total_scan,
		पूर्णांक priority),

	TP_ARGS(shr, sc, nr_objects_to_shrink, cache_items, delta, total_scan,
		priority),

	TP_STRUCT__entry(
		__field(काष्ठा shrinker *, shr)
		__field(व्योम *, shrink)
		__field(पूर्णांक, nid)
		__field(दीर्घ, nr_objects_to_shrink)
		__field(gfp_t, gfp_flags)
		__field(अचिन्हित दीर्घ, cache_items)
		__field(अचिन्हित दीर्घ दीर्घ, delta)
		__field(अचिन्हित दीर्घ, total_scan)
		__field(पूर्णांक, priority)
	),

	TP_fast_assign(
		__entry->shr = shr;
		__entry->shrink = shr->scan_objects;
		__entry->nid = sc->nid;
		__entry->nr_objects_to_shrink = nr_objects_to_shrink;
		__entry->gfp_flags = sc->gfp_mask;
		__entry->cache_items = cache_items;
		__entry->delta = delta;
		__entry->total_scan = total_scan;
		__entry->priority = priority;
	),

	TP_prपूर्णांकk("%pS %p: nid: %d objects to shrink %ld gfp_flags %s cache items %ld delta %lld total_scan %ld priority %d",
		__entry->shrink,
		__entry->shr,
		__entry->nid,
		__entry->nr_objects_to_shrink,
		show_gfp_flags(__entry->gfp_flags),
		__entry->cache_items,
		__entry->delta,
		__entry->total_scan,
		__entry->priority)
);

TRACE_EVENT(mm_shrink_slab_end,
	TP_PROTO(काष्ठा shrinker *shr, पूर्णांक nid, पूर्णांक shrinker_retval,
		दीर्घ unused_scan_cnt, दीर्घ new_scan_cnt, दीर्घ total_scan),

	TP_ARGS(shr, nid, shrinker_retval, unused_scan_cnt, new_scan_cnt,
		total_scan),

	TP_STRUCT__entry(
		__field(काष्ठा shrinker *, shr)
		__field(पूर्णांक, nid)
		__field(व्योम *, shrink)
		__field(दीर्घ, unused_scan)
		__field(दीर्घ, new_scan)
		__field(पूर्णांक, retval)
		__field(दीर्घ, total_scan)
	),

	TP_fast_assign(
		__entry->shr = shr;
		__entry->nid = nid;
		__entry->shrink = shr->scan_objects;
		__entry->unused_scan = unused_scan_cnt;
		__entry->new_scan = new_scan_cnt;
		__entry->retval = shrinker_retval;
		__entry->total_scan = total_scan;
	),

	TP_prपूर्णांकk("%pS %p: nid: %d unused scan count %ld new scan count %ld total_scan %ld last shrinker return val %d",
		__entry->shrink,
		__entry->shr,
		__entry->nid,
		__entry->unused_scan,
		__entry->new_scan,
		__entry->total_scan,
		__entry->retval)
);

TRACE_EVENT(mm_vmscan_lru_isolate,
	TP_PROTO(पूर्णांक highest_zoneidx,
		पूर्णांक order,
		अचिन्हित दीर्घ nr_requested,
		अचिन्हित दीर्घ nr_scanned,
		अचिन्हित दीर्घ nr_skipped,
		अचिन्हित दीर्घ nr_taken,
		isolate_mode_t isolate_mode,
		पूर्णांक lru),

	TP_ARGS(highest_zoneidx, order, nr_requested, nr_scanned, nr_skipped, nr_taken, isolate_mode, lru),

	TP_STRUCT__entry(
		__field(पूर्णांक, highest_zoneidx)
		__field(पूर्णांक, order)
		__field(अचिन्हित दीर्घ, nr_requested)
		__field(अचिन्हित दीर्घ, nr_scanned)
		__field(अचिन्हित दीर्घ, nr_skipped)
		__field(अचिन्हित दीर्घ, nr_taken)
		__field(isolate_mode_t, isolate_mode)
		__field(पूर्णांक, lru)
	),

	TP_fast_assign(
		__entry->highest_zoneidx = highest_zoneidx;
		__entry->order = order;
		__entry->nr_requested = nr_requested;
		__entry->nr_scanned = nr_scanned;
		__entry->nr_skipped = nr_skipped;
		__entry->nr_taken = nr_taken;
		__entry->isolate_mode = isolate_mode;
		__entry->lru = lru;
	),

	/*
	 * classzone is previous name of the highest_zoneidx.
	 * Reason not to change it is the ABI requirement of the tracepoपूर्णांक.
	 */
	TP_prपूर्णांकk("isolate_mode=%d classzone=%d order=%d nr_requested=%lu nr_scanned=%lu nr_skipped=%lu nr_taken=%lu lru=%s",
		__entry->isolate_mode,
		__entry->highest_zoneidx,
		__entry->order,
		__entry->nr_requested,
		__entry->nr_scanned,
		__entry->nr_skipped,
		__entry->nr_taken,
		__prपूर्णांक_symbolic(__entry->lru, LRU_NAMES))
);

TRACE_EVENT(mm_vmscan_ग_लिखोpage,

	TP_PROTO(काष्ठा page *page),

	TP_ARGS(page),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pfn)
		__field(पूर्णांक, reclaim_flags)
	),

	TP_fast_assign(
		__entry->pfn = page_to_pfn(page);
		__entry->reclaim_flags = trace_reclaim_flags(
						page_is_file_lru(page));
	),

	TP_prपूर्णांकk("page=%p pfn=%lu flags=%s",
		pfn_to_page(__entry->pfn),
		__entry->pfn,
		show_reclaim_flags(__entry->reclaim_flags))
);

TRACE_EVENT(mm_vmscan_lru_shrink_inactive,

	TP_PROTO(पूर्णांक nid,
		अचिन्हित दीर्घ nr_scanned, अचिन्हित दीर्घ nr_reclaimed,
		काष्ठा reclaim_stat *stat, पूर्णांक priority, पूर्णांक file),

	TP_ARGS(nid, nr_scanned, nr_reclaimed, stat, priority, file),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(अचिन्हित दीर्घ, nr_scanned)
		__field(अचिन्हित दीर्घ, nr_reclaimed)
		__field(अचिन्हित दीर्घ, nr_dirty)
		__field(अचिन्हित दीर्घ, nr_ग_लिखोback)
		__field(अचिन्हित दीर्घ, nr_congested)
		__field(अचिन्हित दीर्घ, nr_immediate)
		__field(अचिन्हित पूर्णांक, nr_activate0)
		__field(अचिन्हित पूर्णांक, nr_activate1)
		__field(अचिन्हित दीर्घ, nr_ref_keep)
		__field(अचिन्हित दीर्घ, nr_unmap_fail)
		__field(पूर्णांक, priority)
		__field(पूर्णांक, reclaim_flags)
	),

	TP_fast_assign(
		__entry->nid = nid;
		__entry->nr_scanned = nr_scanned;
		__entry->nr_reclaimed = nr_reclaimed;
		__entry->nr_dirty = stat->nr_dirty;
		__entry->nr_ग_लिखोback = stat->nr_ग_लिखोback;
		__entry->nr_congested = stat->nr_congested;
		__entry->nr_immediate = stat->nr_immediate;
		__entry->nr_activate0 = stat->nr_activate[0];
		__entry->nr_activate1 = stat->nr_activate[1];
		__entry->nr_ref_keep = stat->nr_ref_keep;
		__entry->nr_unmap_fail = stat->nr_unmap_fail;
		__entry->priority = priority;
		__entry->reclaim_flags = trace_reclaim_flags(file);
	),

	TP_prपूर्णांकk("nid=%d nr_scanned=%ld nr_reclaimed=%ld nr_dirty=%ld nr_writeback=%ld nr_congested=%ld nr_immediate=%ld nr_activate_anon=%d nr_activate_file=%d nr_ref_keep=%ld nr_unmap_fail=%ld priority=%d flags=%s",
		__entry->nid,
		__entry->nr_scanned, __entry->nr_reclaimed,
		__entry->nr_dirty, __entry->nr_ग_लिखोback,
		__entry->nr_congested, __entry->nr_immediate,
		__entry->nr_activate0, __entry->nr_activate1,
		__entry->nr_ref_keep, __entry->nr_unmap_fail,
		__entry->priority,
		show_reclaim_flags(__entry->reclaim_flags))
);

TRACE_EVENT(mm_vmscan_lru_shrink_active,

	TP_PROTO(पूर्णांक nid, अचिन्हित दीर्घ nr_taken,
		अचिन्हित दीर्घ nr_active, अचिन्हित दीर्घ nr_deactivated,
		अचिन्हित दीर्घ nr_referenced, पूर्णांक priority, पूर्णांक file),

	TP_ARGS(nid, nr_taken, nr_active, nr_deactivated, nr_referenced, priority, file),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(अचिन्हित दीर्घ, nr_taken)
		__field(अचिन्हित दीर्घ, nr_active)
		__field(अचिन्हित दीर्घ, nr_deactivated)
		__field(अचिन्हित दीर्घ, nr_referenced)
		__field(पूर्णांक, priority)
		__field(पूर्णांक, reclaim_flags)
	),

	TP_fast_assign(
		__entry->nid = nid;
		__entry->nr_taken = nr_taken;
		__entry->nr_active = nr_active;
		__entry->nr_deactivated = nr_deactivated;
		__entry->nr_referenced = nr_referenced;
		__entry->priority = priority;
		__entry->reclaim_flags = trace_reclaim_flags(file);
	),

	TP_prपूर्णांकk("nid=%d nr_taken=%ld nr_active=%ld nr_deactivated=%ld nr_referenced=%ld priority=%d flags=%s",
		__entry->nid,
		__entry->nr_taken,
		__entry->nr_active, __entry->nr_deactivated, __entry->nr_referenced,
		__entry->priority,
		show_reclaim_flags(__entry->reclaim_flags))
);

TRACE_EVENT(mm_vmscan_inactive_list_is_low,

	TP_PROTO(पूर्णांक nid, पूर्णांक reclaim_idx,
		अचिन्हित दीर्घ total_inactive, अचिन्हित दीर्घ inactive,
		अचिन्हित दीर्घ total_active, अचिन्हित दीर्घ active,
		अचिन्हित दीर्घ ratio, पूर्णांक file),

	TP_ARGS(nid, reclaim_idx, total_inactive, inactive, total_active, active, ratio, file),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(पूर्णांक, reclaim_idx)
		__field(अचिन्हित दीर्घ, total_inactive)
		__field(अचिन्हित दीर्घ, inactive)
		__field(अचिन्हित दीर्घ, total_active)
		__field(अचिन्हित दीर्घ, active)
		__field(अचिन्हित दीर्घ, ratio)
		__field(पूर्णांक, reclaim_flags)
	),

	TP_fast_assign(
		__entry->nid = nid;
		__entry->reclaim_idx = reclaim_idx;
		__entry->total_inactive = total_inactive;
		__entry->inactive = inactive;
		__entry->total_active = total_active;
		__entry->active = active;
		__entry->ratio = ratio;
		__entry->reclaim_flags = trace_reclaim_flags(file) &
					 RECLAIM_WB_LRU;
	),

	TP_prपूर्णांकk("nid=%d reclaim_idx=%d total_inactive=%ld inactive=%ld total_active=%ld active=%ld ratio=%ld flags=%s",
		__entry->nid,
		__entry->reclaim_idx,
		__entry->total_inactive, __entry->inactive,
		__entry->total_active, __entry->active,
		__entry->ratio,
		show_reclaim_flags(__entry->reclaim_flags))
);

TRACE_EVENT(mm_vmscan_node_reclaim_begin,

	TP_PROTO(पूर्णांक nid, पूर्णांक order, gfp_t gfp_flags),

	TP_ARGS(nid, order, gfp_flags),

	TP_STRUCT__entry(
		__field(पूर्णांक, nid)
		__field(पूर्णांक, order)
		__field(gfp_t, gfp_flags)
	),

	TP_fast_assign(
		__entry->nid = nid;
		__entry->order = order;
		__entry->gfp_flags = gfp_flags;
	),

	TP_prपूर्णांकk("nid=%d order=%d gfp_flags=%s",
		__entry->nid,
		__entry->order,
		show_gfp_flags(__entry->gfp_flags))
);

DEFINE_EVENT(mm_vmscan_direct_reclaim_end_ढाँचा, mm_vmscan_node_reclaim_end,

	TP_PROTO(अचिन्हित दीर्घ nr_reclaimed),

	TP_ARGS(nr_reclaimed)
);

#पूर्ण_अगर /* _TRACE_VMSCAN_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
