<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/gc.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#घोषणा GC_THREAD_MIN_WB_PAGES		1	/*
						 * a threshold to determine
						 * whether IO subप्रणाली is idle
						 * or not
						 */
#घोषणा DEF_GC_THREAD_URGENT_SLEEP_TIME	500	/* 500 ms */
#घोषणा DEF_GC_THREAD_MIN_SLEEP_TIME	30000	/* milliseconds */
#घोषणा DEF_GC_THREAD_MAX_SLEEP_TIME	60000
#घोषणा DEF_GC_THREAD_NOGC_SLEEP_TIME	300000	/* रुको 5 min */

/* choose candidates from sections which has age of more than 7 days */
#घोषणा DEF_GC_THREAD_AGE_THRESHOLD		(60 * 60 * 24 * 7)
#घोषणा DEF_GC_THREAD_CANDIDATE_RATIO		20	/* select 20% oldest sections as candidates */
#घोषणा DEF_GC_THREAD_MAX_CANDIDATE_COUNT	10	/* select at most 10 sections as candidates */
#घोषणा DEF_GC_THREAD_AGE_WEIGHT		60	/* age weight */
#घोषणा DEFAULT_ACCURACY_CLASS			10000	/* accuracy class */

#घोषणा LIMIT_INVALID_BLOCK	40 /* percentage over total user space */
#घोषणा LIMIT_FREE_BLOCK	40 /* percentage over invalid + मुक्त space */

#घोषणा DEF_GC_FAILED_PINNED_खाताS	2048

/* Search max. number of dirty segments to select a victim segment */
#घोषणा DEF_MAX_VICTIM_SEARCH 4096 /* covers 8GB */

काष्ठा f2fs_gc_kthपढ़ो अणु
	काष्ठा task_काष्ठा *f2fs_gc_task;
	रुको_queue_head_t gc_रुको_queue_head;

	/* क्रम gc sleep समय */
	अचिन्हित पूर्णांक urgent_sleep_समय;
	अचिन्हित पूर्णांक min_sleep_समय;
	अचिन्हित पूर्णांक max_sleep_समय;
	अचिन्हित पूर्णांक no_gc_sleep_समय;

	/* क्रम changing gc mode */
	अचिन्हित पूर्णांक gc_wake;

	/* क्रम GC_MERGE mount option */
	रुको_queue_head_t fggc_wq;		/*
						 * caller of f2fs_balance_fs()
						 * will रुको on this रुको queue.
						 */
पूर्ण;

काष्ठा gc_inode_list अणु
	काष्ठा list_head ilist;
	काष्ठा radix_tree_root iroot;
पूर्ण;

काष्ठा victim_info अणु
	अचिन्हित दीर्घ दीर्घ mसमय;	/* mसमय of section */
	अचिन्हित पूर्णांक segno;		/* section No. */
पूर्ण;

काष्ठा victim_entry अणु
	काष्ठा rb_node rb_node;		/* rb node located in rb-tree */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ दीर्घ mसमय;	/* mसमय of section */
			अचिन्हित पूर्णांक segno;		/* segment No. */
		पूर्ण;
		काष्ठा victim_info vi;	/* victim info */
	पूर्ण;
	काष्ठा list_head list;
पूर्ण;

/*
 * अंतरभूत functions
 */

/*
 * On a Zoned device zone-capacity can be less than zone-size and अगर
 * zone-capacity is not aligned to f2fs segment size(2MB), then the segment
 * starting just beक्रमe zone-capacity has some blocks spanning across the
 * zone-capacity, these blocks are not usable.
 * Such spanning segments can be in मुक्त list so calculate the sum of usable
 * blocks in currently मुक्त segments including normal and spanning segments.
 */
अटल अंतरभूत block_t मुक्त_segs_blk_count_zoned(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t मुक्त_seg_blks = 0;
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	पूर्णांक j;

	spin_lock(&मुक्त_i->segmap_lock);
	क्रम (j = 0; j < MAIN_SEGS(sbi); j++)
		अगर (!test_bit(j, मुक्त_i->मुक्त_segmap))
			मुक्त_seg_blks += f2fs_usable_blks_in_seg(sbi, j);
	spin_unlock(&मुक्त_i->segmap_lock);

	वापस मुक्त_seg_blks;
पूर्ण

अटल अंतरभूत block_t मुक्त_segs_blk_count(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (f2fs_sb_has_blkzoned(sbi))
		वापस मुक्त_segs_blk_count_zoned(sbi);

	वापस मुक्त_segments(sbi) << sbi->log_blocks_per_seg;
पूर्ण

अटल अंतरभूत block_t मुक्त_user_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t मुक्त_blks, ovp_blks;

	मुक्त_blks = मुक्त_segs_blk_count(sbi);
	ovp_blks = overprovision_segments(sbi) << sbi->log_blocks_per_seg;

	अगर (मुक्त_blks < ovp_blks)
		वापस 0;

	वापस मुक्त_blks - ovp_blks;
पूर्ण

अटल अंतरभूत block_t limit_invalid_user_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस (दीर्घ)(sbi->user_block_count * LIMIT_INVALID_BLOCK) / 100;
पूर्ण

अटल अंतरभूत block_t limit_मुक्त_user_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t reclaimable_user_blocks = sbi->user_block_count -
		written_block_count(sbi);
	वापस (दीर्घ)(reclaimable_user_blocks * LIMIT_FREE_BLOCK) / 100;
पूर्ण

अटल अंतरभूत व्योम increase_sleep_समय(काष्ठा f2fs_gc_kthपढ़ो *gc_th,
							अचिन्हित पूर्णांक *रुको)
अणु
	अचिन्हित पूर्णांक min_समय = gc_th->min_sleep_समय;
	अचिन्हित पूर्णांक max_समय = gc_th->max_sleep_समय;

	अगर (*रुको == gc_th->no_gc_sleep_समय)
		वापस;

	अगर ((दीर्घ दीर्घ)*रुको + (दीर्घ दीर्घ)min_समय > (दीर्घ दीर्घ)max_समय)
		*रुको = max_समय;
	अन्यथा
		*रुको += min_समय;
पूर्ण

अटल अंतरभूत व्योम decrease_sleep_समय(काष्ठा f2fs_gc_kthपढ़ो *gc_th,
							अचिन्हित पूर्णांक *रुको)
अणु
	अचिन्हित पूर्णांक min_समय = gc_th->min_sleep_समय;

	अगर (*रुको == gc_th->no_gc_sleep_समय)
		*रुको = gc_th->max_sleep_समय;

	अगर ((दीर्घ दीर्घ)*रुको - (दीर्घ दीर्घ)min_समय < (दीर्घ दीर्घ)min_समय)
		*रुको = min_समय;
	अन्यथा
		*रुको -= min_समय;
पूर्ण

अटल अंतरभूत bool has_enough_invalid_blocks(काष्ठा f2fs_sb_info *sbi)
अणु
	block_t invalid_user_blocks = sbi->user_block_count -
					written_block_count(sbi);
	/*
	 * Background GC is triggered with the following conditions.
	 * 1. There are a number of invalid blocks.
	 * 2. There is not enough मुक्त space.
	 */
	अगर (invalid_user_blocks > limit_invalid_user_blocks(sbi) &&
			मुक्त_user_blocks(sbi) < limit_मुक्त_user_blocks(sbi))
		वापस true;
	वापस false;
पूर्ण
