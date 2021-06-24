<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ग_लिखोback

#अगर !defined(_TRACE_WRITEBACK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_WRITEBACK_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ग_लिखोback.h>

#घोषणा show_inode_state(state)					\
	__prपूर्णांक_flags(state, "|",				\
		अणुI_सूचीTY_SYNC,		"I_DIRTY_SYNC"पूर्ण,	\
		अणुI_सूचीTY_DATASYNC,	"I_DIRTY_DATASYNC"पूर्ण,	\
		अणुI_सूचीTY_PAGES,		"I_DIRTY_PAGES"पूर्ण,	\
		अणुI_NEW,			"I_NEW"पूर्ण,		\
		अणुI_WILL_FREE,		"I_WILL_FREE"पूर्ण,		\
		अणुI_FREEING,		"I_FREEING"पूर्ण,		\
		अणुI_CLEAR,		"I_CLEAR"पूर्ण,		\
		अणुI_SYNC,		"I_SYNC"पूर्ण,		\
		अणुI_सूचीTY_TIME,		"I_DIRTY_TIME"पूर्ण,	\
		अणुI_REFERENCED,		"I_REFERENCED"पूर्ण		\
	)

/* क्रमागतs need to be exported to user space */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a,b) 	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a,b)	TRACE_DEFINE_ENUM(a);

#घोषणा WB_WORK_REASON							\
	EM( WB_REASON_BACKGROUND,		"background")		\
	EM( WB_REASON_VMSCAN,			"vmscan")		\
	EM( WB_REASON_SYNC,			"sync")			\
	EM( WB_REASON_PERIODIC,			"periodic")		\
	EM( WB_REASON_LAPTOP_TIMER,		"laptop_timer")		\
	EM( WB_REASON_FS_FREE_SPACE,		"fs_free_space")	\
	EMe(WB_REASON_FORKER_THREAD,		"forker_thread")

WB_WORK_REASON

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a,b)		अणु a, b पूर्ण,
#घोषणा EMe(a,b)	अणु a, b पूर्ण

काष्ठा wb_ग_लिखोback_work;

DECLARE_EVENT_CLASS(ग_लिखोback_page_ढाँचा,

	TP_PROTO(काष्ठा page *page, काष्ठा address_space *mapping),

	TP_ARGS(page, mapping),

	TP_STRUCT__entry (
		__array(अक्षर, name, 32)
		__field(ino_t, ino)
		__field(pgoff_t, index)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name,
			    bdi_dev_name(mapping ? inode_to_bdi(mapping->host) :
					 शून्य), 32);
		__entry->ino = mapping ? mapping->host->i_ino : 0;
		__entry->index = page->index;
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu index=%lu",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->ino,
		__entry->index
	)
);

DEFINE_EVENT(ग_लिखोback_page_ढाँचा, ग_लिखोback_dirty_page,

	TP_PROTO(काष्ठा page *page, काष्ठा address_space *mapping),

	TP_ARGS(page, mapping)
);

DEFINE_EVENT(ग_लिखोback_page_ढाँचा, रुको_on_page_ग_लिखोback,

	TP_PROTO(काष्ठा page *page, काष्ठा address_space *mapping),

	TP_ARGS(page, mapping)
);

DECLARE_EVENT_CLASS(ग_लिखोback_dirty_inode_ढाँचा,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक flags),

	TP_ARGS(inode, flags),

	TP_STRUCT__entry (
		__array(अक्षर, name, 32)
		__field(ino_t, ino)
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, flags)
	),

	TP_fast_assign(
		काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);

		/* may be called क्रम files on pseuकरो FSes w/ unरेजिस्टरed bdi */
		strscpy_pad(__entry->name, bdi_dev_name(bdi), 32);
		__entry->ino		= inode->i_ino;
		__entry->state		= inode->i_state;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu state=%s flags=%s",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->ino,
		show_inode_state(__entry->state),
		show_inode_state(__entry->flags)
	)
);

DEFINE_EVENT(ग_लिखोback_dirty_inode_ढाँचा, ग_लिखोback_mark_inode_dirty,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक flags),

	TP_ARGS(inode, flags)
);

DEFINE_EVENT(ग_लिखोback_dirty_inode_ढाँचा, ग_लिखोback_dirty_inode_start,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक flags),

	TP_ARGS(inode, flags)
);

DEFINE_EVENT(ग_लिखोback_dirty_inode_ढाँचा, ग_लिखोback_dirty_inode,

	TP_PROTO(काष्ठा inode *inode, पूर्णांक flags),

	TP_ARGS(inode, flags)
);

#अगर_घोषित CREATE_TRACE_POINTS
#अगर_घोषित CONFIG_CGROUP_WRITEBACK

अटल अंतरभूत ino_t __trace_wb_assign_cgroup(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस cgroup_ino(wb->memcg_css->cgroup);
पूर्ण

अटल अंतरभूत ino_t __trace_wbc_assign_cgroup(काष्ठा ग_लिखोback_control *wbc)
अणु
	अगर (wbc->wb)
		वापस __trace_wb_assign_cgroup(wbc->wb);
	अन्यथा
		वापस 1;
पूर्ण
#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत ino_t __trace_wb_assign_cgroup(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत ino_t __trace_wbc_assign_cgroup(काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस 1;
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */
#पूर्ण_अगर	/* CREATE_TRACE_POINTS */

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
TRACE_EVENT(inode_क्रमeign_history,

	TP_PROTO(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc,
		 अचिन्हित पूर्णांक history),

	TP_ARGS(inode, wbc, history),

	TP_STRUCT__entry(
		__array(अक्षर,		name, 32)
		__field(ino_t,		ino)
		__field(ino_t,		cgroup_ino)
		__field(अचिन्हित पूर्णांक,	history)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(inode_to_bdi(inode)), 32);
		__entry->ino		= inode->i_ino;
		__entry->cgroup_ino	= __trace_wbc_assign_cgroup(wbc);
		__entry->history	= history;
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu cgroup_ino=%lu history=0x%x",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->ino,
		(अचिन्हित दीर्घ)__entry->cgroup_ino,
		__entry->history
	)
);

TRACE_EVENT(inode_चयन_wbs,

	TP_PROTO(काष्ठा inode *inode, काष्ठा bdi_ग_लिखोback *old_wb,
		 काष्ठा bdi_ग_लिखोback *new_wb),

	TP_ARGS(inode, old_wb, new_wb),

	TP_STRUCT__entry(
		__array(अक्षर,		name, 32)
		__field(ino_t,		ino)
		__field(ino_t,		old_cgroup_ino)
		__field(ino_t,		new_cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(old_wb->bdi), 32);
		__entry->ino		= inode->i_ino;
		__entry->old_cgroup_ino	= __trace_wb_assign_cgroup(old_wb);
		__entry->new_cgroup_ino	= __trace_wb_assign_cgroup(new_wb);
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu old_cgroup_ino=%lu new_cgroup_ino=%lu",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->ino,
		(अचिन्हित दीर्घ)__entry->old_cgroup_ino,
		(अचिन्हित दीर्घ)__entry->new_cgroup_ino
	)
);

TRACE_EVENT(track_क्रमeign_dirty,

	TP_PROTO(काष्ठा page *page, काष्ठा bdi_ग_लिखोback *wb),

	TP_ARGS(page, wb),

	TP_STRUCT__entry(
		__array(अक्षर,		name, 32)
		__field(u64,		bdi_id)
		__field(ino_t,		ino)
		__field(अचिन्हित पूर्णांक,	memcg_id)
		__field(ino_t,		cgroup_ino)
		__field(ino_t,		page_cgroup_ino)
	),

	TP_fast_assign(
		काष्ठा address_space *mapping = page_mapping(page);
		काष्ठा inode *inode = mapping ? mapping->host : शून्य;

		strscpy_pad(__entry->name, bdi_dev_name(wb->bdi), 32);
		__entry->bdi_id		= wb->bdi->id;
		__entry->ino		= inode ? inode->i_ino : 0;
		__entry->memcg_id	= wb->memcg_css->id;
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(wb);
		__entry->page_cgroup_ino = cgroup_ino(page_memcg(page)->css.cgroup);
	),

	TP_prपूर्णांकk("bdi %s[%llu]: ino=%lu memcg_id=%u cgroup_ino=%lu page_cgroup_ino=%lu",
		__entry->name,
		__entry->bdi_id,
		(अचिन्हित दीर्घ)__entry->ino,
		__entry->memcg_id,
		(अचिन्हित दीर्घ)__entry->cgroup_ino,
		(अचिन्हित दीर्घ)__entry->page_cgroup_ino
	)
);

TRACE_EVENT(flush_क्रमeign,

	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित पूर्णांक frn_bdi_id,
		 अचिन्हित पूर्णांक frn_memcg_id),

	TP_ARGS(wb, frn_bdi_id, frn_memcg_id),

	TP_STRUCT__entry(
		__array(अक्षर,		name, 32)
		__field(ino_t,		cgroup_ino)
		__field(अचिन्हित पूर्णांक,	frn_bdi_id)
		__field(अचिन्हित पूर्णांक,	frn_memcg_id)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(wb->bdi), 32);
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(wb);
		__entry->frn_bdi_id	= frn_bdi_id;
		__entry->frn_memcg_id	= frn_memcg_id;
	),

	TP_prपूर्णांकk("bdi %s: cgroup_ino=%lu frn_bdi_id=%u frn_memcg_id=%u",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->cgroup_ino,
		__entry->frn_bdi_id,
		__entry->frn_memcg_id
	)
);
#पूर्ण_अगर

DECLARE_EVENT_CLASS(ग_लिखोback_ग_लिखो_inode_ढाँचा,

	TP_PROTO(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc),

	TP_ARGS(inode, wbc),

	TP_STRUCT__entry (
		__array(अक्षर, name, 32)
		__field(ino_t, ino)
		__field(पूर्णांक, sync_mode)
		__field(ino_t, cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entry->ino		= inode->i_ino;
		__entry->sync_mode	= wbc->sync_mode;
		__entry->cgroup_ino	= __trace_wbc_assign_cgroup(wbc);
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu sync_mode=%d cgroup_ino=%lu",
		__entry->name,
		(अचिन्हित दीर्घ)__entry->ino,
		__entry->sync_mode,
		(अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);

DEFINE_EVENT(ग_लिखोback_ग_लिखो_inode_ढाँचा, ग_लिखोback_ग_लिखो_inode_start,

	TP_PROTO(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc),

	TP_ARGS(inode, wbc)
);

DEFINE_EVENT(ग_लिखोback_ग_लिखो_inode_ढाँचा, ग_लिखोback_ग_लिखो_inode,

	TP_PROTO(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc),

	TP_ARGS(inode, wbc)
);

DECLARE_EVENT_CLASS(ग_लिखोback_work_class,
	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb, काष्ठा wb_ग_लिखोback_work *work),
	TP_ARGS(wb, work),
	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(दीर्घ, nr_pages)
		__field(dev_t, sb_dev)
		__field(पूर्णांक, sync_mode)
		__field(पूर्णांक, क्रम_kupdate)
		__field(पूर्णांक, range_cyclic)
		__field(पूर्णांक, क्रम_background)
		__field(पूर्णांक, reason)
		__field(ino_t, cgroup_ino)
	),
	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(wb->bdi), 32);
		__entry->nr_pages = work->nr_pages;
		__entry->sb_dev = work->sb ? work->sb->s_dev : 0;
		__entry->sync_mode = work->sync_mode;
		__entry->क्रम_kupdate = work->क्रम_kupdate;
		__entry->range_cyclic = work->range_cyclic;
		__entry->क्रम_background	= work->क्रम_background;
		__entry->reason = work->reason;
		__entry->cgroup_ino = __trace_wb_assign_cgroup(wb);
	),
	TP_prपूर्णांकk("bdi %s: sb_dev %d:%d nr_pages=%ld sync_mode=%d "
		  "kupdate=%d range_cyclic=%d background=%d reason=%s cgroup_ino=%lu",
		  __entry->name,
		  MAJOR(__entry->sb_dev), MINOR(__entry->sb_dev),
		  __entry->nr_pages,
		  __entry->sync_mode,
		  __entry->क्रम_kupdate,
		  __entry->range_cyclic,
		  __entry->क्रम_background,
		  __prपूर्णांक_symbolic(__entry->reason, WB_WORK_REASON),
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);
#घोषणा DEFINE_WRITEBACK_WORK_EVENT(name) \
DEFINE_EVENT(ग_लिखोback_work_class, name, \
	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb, काष्ठा wb_ग_लिखोback_work *work), \
	TP_ARGS(wb, work))
DEFINE_WRITEBACK_WORK_EVENT(ग_लिखोback_queue);
DEFINE_WRITEBACK_WORK_EVENT(ग_लिखोback_exec);
DEFINE_WRITEBACK_WORK_EVENT(ग_लिखोback_start);
DEFINE_WRITEBACK_WORK_EVENT(ग_लिखोback_written);
DEFINE_WRITEBACK_WORK_EVENT(ग_लिखोback_रुको);

TRACE_EVENT(ग_लिखोback_pages_written,
	TP_PROTO(दीर्घ pages_written),
	TP_ARGS(pages_written),
	TP_STRUCT__entry(
		__field(दीर्घ,		pages)
	),
	TP_fast_assign(
		__entry->pages		= pages_written;
	),
	TP_prपूर्णांकk("%ld", __entry->pages)
);

DECLARE_EVENT_CLASS(ग_लिखोback_class,
	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb),
	TP_ARGS(wb),
	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(ino_t, cgroup_ino)
	),
	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(wb->bdi), 32);
		__entry->cgroup_ino = __trace_wb_assign_cgroup(wb);
	),
	TP_prपूर्णांकk("bdi %s: cgroup_ino=%lu",
		  __entry->name,
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);
#घोषणा DEFINE_WRITEBACK_EVENT(name) \
DEFINE_EVENT(ग_लिखोback_class, name, \
	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb), \
	TP_ARGS(wb))

DEFINE_WRITEBACK_EVENT(ग_लिखोback_wake_background);

TRACE_EVENT(ग_लिखोback_bdi_रेजिस्टर,
	TP_PROTO(काष्ठा backing_dev_info *bdi),
	TP_ARGS(bdi),
	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
	),
	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(bdi), 32);
	),
	TP_prपूर्णांकk("bdi %s",
		__entry->name
	)
);

DECLARE_EVENT_CLASS(wbc_class,
	TP_PROTO(काष्ठा ग_लिखोback_control *wbc, काष्ठा backing_dev_info *bdi),
	TP_ARGS(wbc, bdi),
	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(दीर्घ, nr_to_ग_लिखो)
		__field(दीर्घ, pages_skipped)
		__field(पूर्णांक, sync_mode)
		__field(पूर्णांक, क्रम_kupdate)
		__field(पूर्णांक, क्रम_background)
		__field(पूर्णांक, क्रम_reclaim)
		__field(पूर्णांक, range_cyclic)
		__field(दीर्घ, range_start)
		__field(दीर्घ, range_end)
		__field(ino_t, cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(bdi), 32);
		__entry->nr_to_ग_लिखो	= wbc->nr_to_ग_लिखो;
		__entry->pages_skipped	= wbc->pages_skipped;
		__entry->sync_mode	= wbc->sync_mode;
		__entry->क्रम_kupdate	= wbc->क्रम_kupdate;
		__entry->क्रम_background	= wbc->क्रम_background;
		__entry->क्रम_reclaim	= wbc->क्रम_reclaim;
		__entry->range_cyclic	= wbc->range_cyclic;
		__entry->range_start	= (दीर्घ)wbc->range_start;
		__entry->range_end	= (दीर्घ)wbc->range_end;
		__entry->cgroup_ino	= __trace_wbc_assign_cgroup(wbc);
	),

	TP_prपूर्णांकk("bdi %s: towrt=%ld skip=%ld mode=%d kupd=%d "
		"bgrd=%d reclm=%d cyclic=%d "
		"start=0x%lx end=0x%lx cgroup_ino=%lu",
		__entry->name,
		__entry->nr_to_ग_लिखो,
		__entry->pages_skipped,
		__entry->sync_mode,
		__entry->क्रम_kupdate,
		__entry->क्रम_background,
		__entry->क्रम_reclaim,
		__entry->range_cyclic,
		__entry->range_start,
		__entry->range_end,
		(अचिन्हित दीर्घ)__entry->cgroup_ino
	)
)

#घोषणा DEFINE_WBC_EVENT(name) \
DEFINE_EVENT(wbc_class, name, \
	TP_PROTO(काष्ठा ग_लिखोback_control *wbc, काष्ठा backing_dev_info *bdi), \
	TP_ARGS(wbc, bdi))
DEFINE_WBC_EVENT(wbc_ग_लिखोpage);

TRACE_EVENT(ग_लिखोback_queue_io,
	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb,
		 काष्ठा wb_ग_लिखोback_work *work,
		 अचिन्हित दीर्घ dirtied_beक्रमe,
		 पूर्णांक moved),
	TP_ARGS(wb, work, dirtied_beक्रमe, moved),
	TP_STRUCT__entry(
		__array(अक्षर,		name, 32)
		__field(अचिन्हित दीर्घ,	older)
		__field(दीर्घ,		age)
		__field(पूर्णांक,		moved)
		__field(पूर्णांक,		reason)
		__field(ino_t,		cgroup_ino)
	),
	TP_fast_assign(
		strscpy_pad(__entry->name, bdi_dev_name(wb->bdi), 32);
		__entry->older	= dirtied_beक्रमe;
		__entry->age	= (jअगरfies - dirtied_beक्रमe) * 1000 / HZ;
		__entry->moved	= moved;
		__entry->reason	= work->reason;
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(wb);
	),
	TP_prपूर्णांकk("bdi %s: older=%lu age=%ld enqueue=%d reason=%s cgroup_ino=%lu",
		__entry->name,
		__entry->older,	/* dirtied_beक्रमe in jअगरfies */
		__entry->age,	/* dirtied_beक्रमe in relative milliseconds */
		__entry->moved,
		__prपूर्णांक_symbolic(__entry->reason, WB_WORK_REASON),
		(अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);

TRACE_EVENT(global_dirty_state,

	TP_PROTO(अचिन्हित दीर्घ background_thresh,
		 अचिन्हित दीर्घ dirty_thresh
	),

	TP_ARGS(background_thresh,
		dirty_thresh
	),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ,	nr_dirty)
		__field(अचिन्हित दीर्घ,	nr_ग_लिखोback)
		__field(अचिन्हित दीर्घ,	background_thresh)
		__field(अचिन्हित दीर्घ,	dirty_thresh)
		__field(अचिन्हित दीर्घ,	dirty_limit)
		__field(अचिन्हित दीर्घ,	nr_dirtied)
		__field(अचिन्हित दीर्घ,	nr_written)
	),

	TP_fast_assign(
		__entry->nr_dirty	= global_node_page_state(NR_खाता_सूचीTY);
		__entry->nr_ग_लिखोback	= global_node_page_state(NR_WRITEBACK);
		__entry->nr_dirtied	= global_node_page_state(NR_सूचीTIED);
		__entry->nr_written	= global_node_page_state(NR_WRITTEN);
		__entry->background_thresh = background_thresh;
		__entry->dirty_thresh	= dirty_thresh;
		__entry->dirty_limit	= global_wb_करोमुख्य.dirty_limit;
	),

	TP_prपूर्णांकk("dirty=%lu writeback=%lu "
		  "bg_thresh=%lu thresh=%lu limit=%lu "
		  "dirtied=%lu written=%lu",
		  __entry->nr_dirty,
		  __entry->nr_ग_लिखोback,
		  __entry->background_thresh,
		  __entry->dirty_thresh,
		  __entry->dirty_limit,
		  __entry->nr_dirtied,
		  __entry->nr_written
	)
);

#घोषणा KBps(x)			((x) << (PAGE_SHIFT - 10))

TRACE_EVENT(bdi_dirty_ratelimit,

	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb,
		 अचिन्हित दीर्घ dirty_rate,
		 अचिन्हित दीर्घ task_ratelimit),

	TP_ARGS(wb, dirty_rate, task_ratelimit),

	TP_STRUCT__entry(
		__array(अक्षर,		bdi, 32)
		__field(अचिन्हित दीर्घ,	ग_लिखो_bw)
		__field(अचिन्हित दीर्घ,	avg_ग_लिखो_bw)
		__field(अचिन्हित दीर्घ,	dirty_rate)
		__field(अचिन्हित दीर्घ,	dirty_ratelimit)
		__field(अचिन्हित दीर्घ,	task_ratelimit)
		__field(अचिन्हित दीर्घ,	balanced_dirty_ratelimit)
		__field(ino_t,		cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->bdi, bdi_dev_name(wb->bdi), 32);
		__entry->ग_लिखो_bw	= KBps(wb->ग_लिखो_bandwidth);
		__entry->avg_ग_लिखो_bw	= KBps(wb->avg_ग_लिखो_bandwidth);
		__entry->dirty_rate	= KBps(dirty_rate);
		__entry->dirty_ratelimit = KBps(wb->dirty_ratelimit);
		__entry->task_ratelimit	= KBps(task_ratelimit);
		__entry->balanced_dirty_ratelimit =
					KBps(wb->balanced_dirty_ratelimit);
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(wb);
	),

	TP_prपूर्णांकk("bdi %s: "
		  "write_bw=%lu awrite_bw=%lu dirty_rate=%lu "
		  "dirty_ratelimit=%lu task_ratelimit=%lu "
		  "balanced_dirty_ratelimit=%lu cgroup_ino=%lu",
		  __entry->bdi,
		  __entry->ग_लिखो_bw,		/* ग_लिखो bandwidth */
		  __entry->avg_ग_लिखो_bw,	/* avg ग_लिखो bandwidth */
		  __entry->dirty_rate,		/* bdi dirty rate */
		  __entry->dirty_ratelimit,	/* base ratelimit */
		  __entry->task_ratelimit, /* ratelimit with position control */
		  __entry->balanced_dirty_ratelimit, /* the balanced ratelimit */
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);

TRACE_EVENT(balance_dirty_pages,

	TP_PROTO(काष्ठा bdi_ग_लिखोback *wb,
		 अचिन्हित दीर्घ thresh,
		 अचिन्हित दीर्घ bg_thresh,
		 अचिन्हित दीर्घ dirty,
		 अचिन्हित दीर्घ bdi_thresh,
		 अचिन्हित दीर्घ bdi_dirty,
		 अचिन्हित दीर्घ dirty_ratelimit,
		 अचिन्हित दीर्घ task_ratelimit,
		 अचिन्हित दीर्घ dirtied,
		 अचिन्हित दीर्घ period,
		 दीर्घ छोड़ो,
		 अचिन्हित दीर्घ start_समय),

	TP_ARGS(wb, thresh, bg_thresh, dirty, bdi_thresh, bdi_dirty,
		dirty_ratelimit, task_ratelimit,
		dirtied, period, छोड़ो, start_समय),

	TP_STRUCT__entry(
		__array(	 अक्षर,	bdi, 32)
		__field(अचिन्हित दीर्घ,	limit)
		__field(अचिन्हित दीर्घ,	setpoपूर्णांक)
		__field(अचिन्हित दीर्घ,	dirty)
		__field(अचिन्हित दीर्घ,	bdi_setpoपूर्णांक)
		__field(अचिन्हित दीर्घ,	bdi_dirty)
		__field(अचिन्हित दीर्घ,	dirty_ratelimit)
		__field(अचिन्हित दीर्घ,	task_ratelimit)
		__field(अचिन्हित पूर्णांक,	dirtied)
		__field(अचिन्हित पूर्णांक,	dirtied_छोड़ो)
		__field(अचिन्हित दीर्घ,	छोड़ोd)
		__field(	 दीर्घ,	छोड़ो)
		__field(अचिन्हित दीर्घ,	period)
		__field(	 दीर्घ,	think)
		__field(ino_t,		cgroup_ino)
	),

	TP_fast_assign(
		अचिन्हित दीर्घ मुक्तrun = (thresh + bg_thresh) / 2;
		strscpy_pad(__entry->bdi, bdi_dev_name(wb->bdi), 32);

		__entry->limit		= global_wb_करोमुख्य.dirty_limit;
		__entry->setpoपूर्णांक	= (global_wb_करोमुख्य.dirty_limit +
						मुक्तrun) / 2;
		__entry->dirty		= dirty;
		__entry->bdi_setpoपूर्णांक	= __entry->setpoपूर्णांक *
						bdi_thresh / (thresh + 1);
		__entry->bdi_dirty	= bdi_dirty;
		__entry->dirty_ratelimit = KBps(dirty_ratelimit);
		__entry->task_ratelimit	= KBps(task_ratelimit);
		__entry->dirtied	= dirtied;
		__entry->dirtied_छोड़ो	= current->nr_dirtied_छोड़ो;
		__entry->think		= current->dirty_छोड़ोd_when == 0 ? 0 :
			 (दीर्घ)(jअगरfies - current->dirty_छोड़ोd_when) * 1000/HZ;
		__entry->period		= period * 1000 / HZ;
		__entry->छोड़ो		= छोड़ो * 1000 / HZ;
		__entry->छोड़ोd		= (jअगरfies - start_समय) * 1000 / HZ;
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(wb);
	),


	TP_prपूर्णांकk("bdi %s: "
		  "limit=%lu setpoint=%lu dirty=%lu "
		  "bdi_setpoint=%lu bdi_dirty=%lu "
		  "dirty_ratelimit=%lu task_ratelimit=%lu "
		  "dirtied=%u dirtied_pause=%u "
		  "paused=%lu pause=%ld period=%lu think=%ld cgroup_ino=%lu",
		  __entry->bdi,
		  __entry->limit,
		  __entry->setpoपूर्णांक,
		  __entry->dirty,
		  __entry->bdi_setpoपूर्णांक,
		  __entry->bdi_dirty,
		  __entry->dirty_ratelimit,
		  __entry->task_ratelimit,
		  __entry->dirtied,
		  __entry->dirtied_छोड़ो,
		  __entry->छोड़ोd,	/* ms */
		  __entry->छोड़ो,	/* ms */
		  __entry->period,	/* ms */
		  __entry->think,	/* ms */
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	  )
);

TRACE_EVENT(ग_लिखोback_sb_inodes_requeue,

	TP_PROTO(काष्ठा inode *inode),
	TP_ARGS(inode),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(ino_t, ino)
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, dirtied_when)
		__field(ino_t, cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entry->ino		= inode->i_ino;
		__entry->state		= inode->i_state;
		__entry->dirtied_when	= inode->dirtied_when;
		__entry->cgroup_ino	= __trace_wb_assign_cgroup(inode_to_wb(inode));
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu state=%s dirtied_when=%lu age=%lu cgroup_ino=%lu",
		  __entry->name,
		  (अचिन्हित दीर्घ)__entry->ino,
		  show_inode_state(__entry->state),
		  __entry->dirtied_when,
		  (jअगरfies - __entry->dirtied_when) / HZ,
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);

DECLARE_EVENT_CLASS(ग_लिखोback_congest_रुकोed_ढाँचा,

	TP_PROTO(अचिन्हित पूर्णांक usec_समयout, अचिन्हित पूर्णांक usec_delayed),

	TP_ARGS(usec_समयout, usec_delayed),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	usec_समयout	)
		__field(	अचिन्हित पूर्णांक,	usec_delayed	)
	),

	TP_fast_assign(
		__entry->usec_समयout	= usec_समयout;
		__entry->usec_delayed	= usec_delayed;
	),

	TP_prपूर्णांकk("usec_timeout=%u usec_delayed=%u",
			__entry->usec_समयout,
			__entry->usec_delayed)
);

DEFINE_EVENT(ग_लिखोback_congest_रुकोed_ढाँचा, ग_लिखोback_congestion_रुको,

	TP_PROTO(अचिन्हित पूर्णांक usec_समयout, अचिन्हित पूर्णांक usec_delayed),

	TP_ARGS(usec_समयout, usec_delayed)
);

DEFINE_EVENT(ग_लिखोback_congest_रुकोed_ढाँचा, ग_लिखोback_रुको_अगरf_congested,

	TP_PROTO(अचिन्हित पूर्णांक usec_समयout, अचिन्हित पूर्णांक usec_delayed),

	TP_ARGS(usec_समयout, usec_delayed)
);

DECLARE_EVENT_CLASS(ग_लिखोback_single_inode_ढाँचा,

	TP_PROTO(काष्ठा inode *inode,
		 काष्ठा ग_लिखोback_control *wbc,
		 अचिन्हित दीर्घ nr_to_ग_लिखो
	),

	TP_ARGS(inode, wbc, nr_to_ग_लिखो),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(ino_t, ino)
		__field(अचिन्हित दीर्घ, state)
		__field(अचिन्हित दीर्घ, dirtied_when)
		__field(अचिन्हित दीर्घ, ग_लिखोback_index)
		__field(दीर्घ, nr_to_ग_लिखो)
		__field(अचिन्हित दीर्घ, wrote)
		__field(ino_t, cgroup_ino)
	),

	TP_fast_assign(
		strscpy_pad(__entry->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entry->ino		= inode->i_ino;
		__entry->state		= inode->i_state;
		__entry->dirtied_when	= inode->dirtied_when;
		__entry->ग_लिखोback_index = inode->i_mapping->ग_लिखोback_index;
		__entry->nr_to_ग_लिखो	= nr_to_ग_लिखो;
		__entry->wrote		= nr_to_ग_लिखो - wbc->nr_to_ग_लिखो;
		__entry->cgroup_ino	= __trace_wbc_assign_cgroup(wbc);
	),

	TP_prपूर्णांकk("bdi %s: ino=%lu state=%s dirtied_when=%lu age=%lu "
		  "index=%lu to_write=%ld wrote=%lu cgroup_ino=%lu",
		  __entry->name,
		  (अचिन्हित दीर्घ)__entry->ino,
		  show_inode_state(__entry->state),
		  __entry->dirtied_when,
		  (jअगरfies - __entry->dirtied_when) / HZ,
		  __entry->ग_लिखोback_index,
		  __entry->nr_to_ग_लिखो,
		  __entry->wrote,
		  (अचिन्हित दीर्घ)__entry->cgroup_ino
	)
);

DEFINE_EVENT(ग_लिखोback_single_inode_ढाँचा, ग_लिखोback_single_inode_start,
	TP_PROTO(काष्ठा inode *inode,
		 काष्ठा ग_लिखोback_control *wbc,
		 अचिन्हित दीर्घ nr_to_ग_लिखो),
	TP_ARGS(inode, wbc, nr_to_ग_लिखो)
);

DEFINE_EVENT(ग_लिखोback_single_inode_ढाँचा, ग_लिखोback_single_inode,
	TP_PROTO(काष्ठा inode *inode,
		 काष्ठा ग_लिखोback_control *wbc,
		 अचिन्हित दीर्घ nr_to_ग_लिखो),
	TP_ARGS(inode, wbc, nr_to_ग_लिखो)
);

DECLARE_EVENT_CLASS(ग_लिखोback_inode_ढाँचा,
	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	ino_t,	ino			)
		__field(अचिन्हित दीर्घ,	state			)
		__field(	__u16, mode			)
		__field(अचिन्हित दीर्घ, dirtied_when		)
	),

	TP_fast_assign(
		__entry->dev	= inode->i_sb->s_dev;
		__entry->ino	= inode->i_ino;
		__entry->state	= inode->i_state;
		__entry->mode	= inode->i_mode;
		__entry->dirtied_when = inode->dirtied_when;
	),

	TP_prपूर्णांकk("dev %d,%d ino %lu dirtied %lu state %s mode 0%o",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  (अचिन्हित दीर्घ)__entry->ino, __entry->dirtied_when,
		  show_inode_state(__entry->state), __entry->mode)
);

DEFINE_EVENT(ग_लिखोback_inode_ढाँचा, ग_लिखोback_lazyसमय,
	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(ग_लिखोback_inode_ढाँचा, ग_लिखोback_lazyसमय_iput,
	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

DEFINE_EVENT(ग_लिखोback_inode_ढाँचा, ग_लिखोback_dirty_inode_enqueue,

	TP_PROTO(काष्ठा inode *inode),

	TP_ARGS(inode)
);

/*
 * Inode ग_लिखोback list tracking.
 */

DEFINE_EVENT(ग_लिखोback_inode_ढाँचा, sb_mark_inode_ग_लिखोback,
	TP_PROTO(काष्ठा inode *inode),
	TP_ARGS(inode)
);

DEFINE_EVENT(ग_लिखोback_inode_ढाँचा, sb_clear_inode_ग_लिखोback,
	TP_PROTO(काष्ठा inode *inode),
	TP_ARGS(inode)
);

#पूर्ण_अगर /* _TRACE_WRITEBACK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
