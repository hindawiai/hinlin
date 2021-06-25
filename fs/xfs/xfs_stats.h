<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_STATS_H__
#घोषणा __XFS_STATS_H__


#समावेश <linux/percpu.h>

/*
 * The btree stats arrays have fixed offsets क्रम the dअगरferent stats. We
 * store the base index in the btree cursor via XFS_STATS_CALC_INDEX() and
 * that allows us to use fixed offsets पूर्णांकo the stats array क्रम each btree
 * stat. These index offsets are defined in the order they will be emitted
 * in the stats files, so it is possible to add new btree stat types by
 * appending to the क्रमागत list below.
 */
क्रमागत अणु
	__XBTS_lookup = 0,
	__XBTS_compare = 1,
	__XBTS_insrec = 2,
	__XBTS_delrec = 3,
	__XBTS_newroot = 4,
	__XBTS_समाप्तroot = 5,
	__XBTS_increment = 6,
	__XBTS_decrement = 7,
	__XBTS_lshअगरt = 8,
	__XBTS_rshअगरt = 9,
	__XBTS_split = 10,
	__XBTS_join = 11,
	__XBTS_alloc = 12,
	__XBTS_मुक्त = 13,
	__XBTS_moves = 14,

	__XBTS_MAX = 15,
पूर्ण;

/*
 * XFS global statistics
 */
काष्ठा __xfsstats अणु
	uपूर्णांक32_t		xs_allocx;
	uपूर्णांक32_t		xs_allocb;
	uपूर्णांक32_t		xs_मुक्तx;
	uपूर्णांक32_t		xs_मुक्तb;
	uपूर्णांक32_t		xs_abt_lookup;
	uपूर्णांक32_t		xs_abt_compare;
	uपूर्णांक32_t		xs_abt_insrec;
	uपूर्णांक32_t		xs_abt_delrec;
	uपूर्णांक32_t		xs_blk_mapr;
	uपूर्णांक32_t		xs_blk_mapw;
	uपूर्णांक32_t		xs_blk_unmap;
	uपूर्णांक32_t		xs_add_exlist;
	uपूर्णांक32_t		xs_del_exlist;
	uपूर्णांक32_t		xs_look_exlist;
	uपूर्णांक32_t		xs_cmp_exlist;
	uपूर्णांक32_t		xs_bmbt_lookup;
	uपूर्णांक32_t		xs_bmbt_compare;
	uपूर्णांक32_t		xs_bmbt_insrec;
	uपूर्णांक32_t		xs_bmbt_delrec;
	uपूर्णांक32_t		xs_dir_lookup;
	uपूर्णांक32_t		xs_dir_create;
	uपूर्णांक32_t		xs_dir_हटाओ;
	uपूर्णांक32_t		xs_dir_getdents;
	uपूर्णांक32_t		xs_trans_sync;
	uपूर्णांक32_t		xs_trans_async;
	uपूर्णांक32_t		xs_trans_empty;
	uपूर्णांक32_t		xs_ig_attempts;
	uपूर्णांक32_t		xs_ig_found;
	uपूर्णांक32_t		xs_ig_frecycle;
	uपूर्णांक32_t		xs_ig_missed;
	uपूर्णांक32_t		xs_ig_dup;
	uपूर्णांक32_t		xs_ig_reclaims;
	uपूर्णांक32_t		xs_ig_attrchg;
	uपूर्णांक32_t		xs_log_ग_लिखोs;
	uपूर्णांक32_t		xs_log_blocks;
	uपूर्णांक32_t		xs_log_noiclogs;
	uपूर्णांक32_t		xs_log_क्रमce;
	uपूर्णांक32_t		xs_log_क्रमce_sleep;
	uपूर्णांक32_t		xs_try_logspace;
	uपूर्णांक32_t		xs_sleep_logspace;
	uपूर्णांक32_t		xs_push_ail;
	uपूर्णांक32_t		xs_push_ail_success;
	uपूर्णांक32_t		xs_push_ail_pushbuf;
	uपूर्णांक32_t		xs_push_ail_pinned;
	uपूर्णांक32_t		xs_push_ail_locked;
	uपूर्णांक32_t		xs_push_ail_flushing;
	uपूर्णांक32_t		xs_push_ail_restarts;
	uपूर्णांक32_t		xs_push_ail_flush;
	uपूर्णांक32_t		xs_xstrat_quick;
	uपूर्णांक32_t		xs_xstrat_split;
	uपूर्णांक32_t		xs_ग_लिखो_calls;
	uपूर्णांक32_t		xs_पढ़ो_calls;
	uपूर्णांक32_t		xs_attr_get;
	uपूर्णांक32_t		xs_attr_set;
	uपूर्णांक32_t		xs_attr_हटाओ;
	uपूर्णांक32_t		xs_attr_list;
	uपूर्णांक32_t		xs_अगरlush_count;
	uपूर्णांक32_t		xs_icluster_flushcnt;
	uपूर्णांक32_t		xs_icluster_flushinode;
	uपूर्णांक32_t		vn_active;	/* # vnodes not on मुक्त lists */
	uपूर्णांक32_t		vn_alloc;	/* # बार vn_alloc called */
	uपूर्णांक32_t		vn_get;		/* # बार vn_get called */
	uपूर्णांक32_t		vn_hold;	/* # बार vn_hold called */
	uपूर्णांक32_t		vn_rele;	/* # बार vn_rele called */
	uपूर्णांक32_t		vn_reclaim;	/* # बार vn_reclaim called */
	uपूर्णांक32_t		vn_हटाओ;	/* # बार vn_हटाओ called */
	uपूर्णांक32_t		vn_मुक्त;	/* # बार vn_मुक्त called */
	uपूर्णांक32_t		xb_get;
	uपूर्णांक32_t		xb_create;
	uपूर्णांक32_t		xb_get_locked;
	uपूर्णांक32_t		xb_get_locked_रुकोed;
	uपूर्णांक32_t		xb_busy_locked;
	uपूर्णांक32_t		xb_miss_locked;
	uपूर्णांक32_t		xb_page_retries;
	uपूर्णांक32_t		xb_page_found;
	uपूर्णांक32_t		xb_get_पढ़ो;
/* Version 2 btree counters */
	uपूर्णांक32_t		xs_abtb_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_abtc_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_bmbt_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_ibt_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_fibt_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_rmap_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_refcbt_2[__XBTS_MAX];
	uपूर्णांक32_t		xs_qm_dqreclaims;
	uपूर्णांक32_t		xs_qm_dqreclaim_misses;
	uपूर्णांक32_t		xs_qm_dquot_dups;
	uपूर्णांक32_t		xs_qm_dqcachemisses;
	uपूर्णांक32_t		xs_qm_dqcachehits;
	uपूर्णांक32_t		xs_qm_dqwants;
	uपूर्णांक32_t		xs_qm_dquot;
	uपूर्णांक32_t		xs_qm_dquot_unused;
/* Extra precision counters */
	uपूर्णांक64_t		xs_xstrat_bytes;
	uपूर्णांक64_t		xs_ग_लिखो_bytes;
	uपूर्णांक64_t		xs_पढ़ो_bytes;
	uपूर्णांक64_t		defer_relog;
पूर्ण;

#घोषणा	xfsstats_offset(f)	(दुरत्व(काष्ठा __xfsstats, f)/माप(uपूर्णांक32_t))

काष्ठा xfsstats अणु
	जोड़ अणु
		काष्ठा __xfsstats	s;
		uपूर्णांक32_t		a[xfsstats_offset(xs_qm_dquot)];
	पूर्ण;
पूर्ण;

/*
 * simple wrapper क्रम getting the array index of s काष्ठा member offset
 */
#घोषणा XFS_STATS_CALC_INDEX(member)	\
	(दुरत्व(काष्ठा __xfsstats, member) / (पूर्णांक)माप(uपूर्णांक32_t))


पूर्णांक xfs_stats_क्रमmat(काष्ठा xfsstats __percpu *stats, अक्षर *buf);
व्योम xfs_stats_clearall(काष्ठा xfsstats __percpu *stats);
बाह्य काष्ठा xstats xfsstats;

#घोषणा XFS_STATS_INC(mp, v)					\
करो अणु								\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->s.v++;	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->s.v++;	\
पूर्ण जबतक (0)

#घोषणा XFS_STATS_DEC(mp, v)					\
करो अणु								\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->s.v--;	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->s.v--;	\
पूर्ण जबतक (0)

#घोषणा XFS_STATS_ADD(mp, v, inc)					\
करो अणु									\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->s.v += (inc);	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->s.v += (inc);	\
पूर्ण जबतक (0)

#घोषणा XFS_STATS_INC_OFF(mp, off)				\
करो अणु								\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->a[off]++;	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->a[off]++;	\
पूर्ण जबतक (0)

#घोषणा XFS_STATS_DEC_OFF(mp, off)					\
करो अणु								\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->a[off];	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->a[off];	\
पूर्ण जबतक (0)

#घोषणा XFS_STATS_ADD_OFF(mp, off, inc)					\
करो अणु									\
	per_cpu_ptr(xfsstats.xs_stats, current_cpu())->a[off] += (inc);	\
	per_cpu_ptr(mp->m_stats.xs_stats, current_cpu())->a[off] += (inc);	\
पूर्ण जबतक (0)

#अगर defined(CONFIG_PROC_FS)

बाह्य पूर्णांक xfs_init_procfs(व्योम);
बाह्य व्योम xfs_cleanup_procfs(व्योम);


#अन्यथा	/* !CONFIG_PROC_FS */

अटल अंतरभूत पूर्णांक xfs_init_procfs(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xfs_cleanup_procfs(व्योम)
अणु
पूर्ण

#पूर्ण_अगर	/* !CONFIG_PROC_FS */

#पूर्ण_अगर /* __XFS_STATS_H__ */
