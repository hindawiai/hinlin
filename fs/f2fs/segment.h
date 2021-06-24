<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/segment.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>

/* स्थिरant macro */
#घोषणा शून्य_SEGNO			((अचिन्हित पूर्णांक)(~0))
#घोषणा शून्य_SECNO			((अचिन्हित पूर्णांक)(~0))

#घोषणा DEF_RECLAIM_PREFREE_SEGMENTS	5	/* 5% over total segments */
#घोषणा DEF_MAX_RECLAIM_PREFREE_SEGMENTS	4096	/* 8GB in maximum */

#घोषणा F2FS_MIN_SEGMENTS	9 /* SB + 2 (CP + SIT + NAT) + SSA + MAIN */
#घोषणा F2FS_MIN_META_SEGMENTS	8 /* SB + 2 (CP + SIT + NAT) + SSA */

/* L: Logical segment # in volume, R: Relative segment # in मुख्य area */
#घोषणा GET_L2R_SEGNO(मुक्त_i, segno)	((segno) - (मुक्त_i)->start_segno)
#घोषणा GET_R2L_SEGNO(मुक्त_i, segno)	((segno) + (मुक्त_i)->start_segno)

#घोषणा IS_DATASEG(t)	((t) <= CURSEG_COLD_DATA)
#घोषणा IS_NODESEG(t)	((t) >= CURSEG_HOT_NODE && (t) <= CURSEG_COLD_NODE)

अटल अंतरभूत व्योम sanity_check_seg_type(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित लघु seg_type)
अणु
	f2fs_bug_on(sbi, seg_type >= NR_PERSISTENT_LOG);
पूर्ण

#घोषणा IS_HOT(t)	((t) == CURSEG_HOT_NODE || (t) == CURSEG_HOT_DATA)
#घोषणा IS_WARM(t)	((t) == CURSEG_WARM_NODE || (t) == CURSEG_WARM_DATA)
#घोषणा IS_COLD(t)	((t) == CURSEG_COLD_NODE || (t) == CURSEG_COLD_DATA)

#घोषणा IS_CURSEG(sbi, seg)						\
	(((seg) == CURSEG_I(sbi, CURSEG_HOT_DATA)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_WARM_DATA)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_COLD_DATA)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_HOT_NODE)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_WARM_NODE)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_COLD_NODE)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_COLD_DATA_PINNED)->segno) ||	\
	 ((seg) == CURSEG_I(sbi, CURSEG_ALL_DATA_ATGC)->segno))

#घोषणा IS_CURSEC(sbi, secno)						\
	(((secno) == CURSEG_I(sbi, CURSEG_HOT_DATA)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_WARM_DATA)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_COLD_DATA)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_HOT_NODE)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_WARM_NODE)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_COLD_NODE)->segno /		\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_COLD_DATA_PINNED)->segno /	\
	  (sbi)->segs_per_sec) ||	\
	 ((secno) == CURSEG_I(sbi, CURSEG_ALL_DATA_ATGC)->segno /	\
	  (sbi)->segs_per_sec))

#घोषणा MAIN_BLKADDR(sbi)						\
	(SM_I(sbi) ? SM_I(sbi)->मुख्य_blkaddr : 				\
		le32_to_cpu(F2FS_RAW_SUPER(sbi)->मुख्य_blkaddr))
#घोषणा SEG0_BLKADDR(sbi)						\
	(SM_I(sbi) ? SM_I(sbi)->seg0_blkaddr : 				\
		le32_to_cpu(F2FS_RAW_SUPER(sbi)->segment0_blkaddr))

#घोषणा MAIN_SEGS(sbi)	(SM_I(sbi)->मुख्य_segments)
#घोषणा MAIN_SECS(sbi)	((sbi)->total_sections)

#घोषणा TOTAL_SEGS(sbi)							\
	(SM_I(sbi) ? SM_I(sbi)->segment_count : 				\
		le32_to_cpu(F2FS_RAW_SUPER(sbi)->segment_count))
#घोषणा TOTAL_BLKS(sbi)	(TOTAL_SEGS(sbi) << (sbi)->log_blocks_per_seg)

#घोषणा MAX_BLKADDR(sbi)	(SEG0_BLKADDR(sbi) + TOTAL_BLKS(sbi))
#घोषणा SEGMENT_SIZE(sbi)	(1ULL << ((sbi)->log_blocksize +	\
					(sbi)->log_blocks_per_seg))

#घोषणा START_BLOCK(sbi, segno)	(SEG0_BLKADDR(sbi) +			\
	 (GET_R2L_SEGNO(FREE_I(sbi), segno) << (sbi)->log_blocks_per_seg))

#घोषणा NEXT_FREE_BLKADDR(sbi, curseg)					\
	(START_BLOCK(sbi, (curseg)->segno) + (curseg)->next_blkoff)

#घोषणा GET_SEGOFF_FROM_SEG0(sbi, blk_addr)	((blk_addr) - SEG0_BLKADDR(sbi))
#घोषणा GET_SEGNO_FROM_SEG0(sbi, blk_addr)				\
	(GET_SEGOFF_FROM_SEG0(sbi, blk_addr) >> (sbi)->log_blocks_per_seg)
#घोषणा GET_BLKOFF_FROM_SEG0(sbi, blk_addr)				\
	(GET_SEGOFF_FROM_SEG0(sbi, blk_addr) & ((sbi)->blocks_per_seg - 1))

#घोषणा GET_SEGNO(sbi, blk_addr)					\
	((!__is_valid_data_blkaddr(blk_addr)) ?			\
	शून्य_SEGNO : GET_L2R_SEGNO(FREE_I(sbi),			\
		GET_SEGNO_FROM_SEG0(sbi, blk_addr)))
#घोषणा BLKS_PER_SEC(sbi)					\
	((sbi)->segs_per_sec * (sbi)->blocks_per_seg)
#घोषणा GET_SEC_FROM_SEG(sbi, segno)				\
	(((segno) == -1) ? -1: (segno) / (sbi)->segs_per_sec)
#घोषणा GET_SEG_FROM_SEC(sbi, secno)				\
	((secno) * (sbi)->segs_per_sec)
#घोषणा GET_ZONE_FROM_SEC(sbi, secno)				\
	(((secno) == -1) ? -1: (secno) / (sbi)->secs_per_zone)
#घोषणा GET_ZONE_FROM_SEG(sbi, segno)				\
	GET_ZONE_FROM_SEC(sbi, GET_SEC_FROM_SEG(sbi, segno))

#घोषणा GET_SUM_BLOCK(sbi, segno)				\
	((sbi)->sm_info->ssa_blkaddr + (segno))

#घोषणा GET_SUM_TYPE(footer) ((footer)->entry_type)
#घोषणा SET_SUM_TYPE(footer, type) ((footer)->entry_type = (type))

#घोषणा SIT_ENTRY_OFFSET(sit_i, segno)					\
	((segno) % (sit_i)->sents_per_block)
#घोषणा SIT_BLOCK_OFFSET(segno)					\
	((segno) / SIT_ENTRY_PER_BLOCK)
#घोषणा	START_SEGNO(segno)		\
	(SIT_BLOCK_OFFSET(segno) * SIT_ENTRY_PER_BLOCK)
#घोषणा SIT_BLK_CNT(sbi)			\
	DIV_ROUND_UP(MAIN_SEGS(sbi), SIT_ENTRY_PER_BLOCK)
#घोषणा f2fs_biपंचांगap_size(nr)			\
	(BITS_TO_LONGS(nr) * माप(अचिन्हित दीर्घ))

#घोषणा SECTOR_FROM_BLOCK(blk_addr)					\
	(((sector_t)blk_addr) << F2FS_LOG_SECTORS_PER_BLOCK)
#घोषणा SECTOR_TO_BLOCK(sectors)					\
	((sectors) >> F2FS_LOG_SECTORS_PER_BLOCK)

/*
 * indicate a block allocation direction: RIGHT and LEFT.
 * RIGHT means allocating new sections towards the end of volume.
 * LEFT means the opposite direction.
 */
क्रमागत अणु
	ALLOC_RIGHT = 0,
	ALLOC_LEFT
पूर्ण;

/*
 * In the victim_sel_policy->alloc_mode, there are two block allocation modes.
 * LFS ग_लिखोs data sequentially with cleaning operations.
 * SSR (Slack Space Recycle) reuses obsolete space without cleaning operations.
 * AT_SSR (Age Threshold based Slack Space Recycle) merges fragments पूर्णांकo
 * fragmented segment which has similar aging degree.
 */
क्रमागत अणु
	LFS = 0,
	SSR,
	AT_SSR,
पूर्ण;

/*
 * In the victim_sel_policy->gc_mode, there are two gc, aka cleaning, modes.
 * GC_CB is based on cost-benefit algorithm.
 * GC_GREEDY is based on greedy algorithm.
 * GC_AT is based on age-threshold algorithm.
 */
क्रमागत अणु
	GC_CB = 0,
	GC_GREEDY,
	GC_AT,
	ALLOC_NEXT,
	FLUSH_DEVICE,
	MAX_GC_POLICY,
पूर्ण;

/*
 * BG_GC means the background cleaning job.
 * FG_GC means the on-demand cleaning job.
 */
क्रमागत अणु
	BG_GC = 0,
	FG_GC,
पूर्ण;

/* क्रम a function parameter to select a victim segment */
काष्ठा victim_sel_policy अणु
	पूर्णांक alloc_mode;			/* LFS or SSR */
	पूर्णांक gc_mode;			/* GC_CB or GC_GREEDY */
	अचिन्हित दीर्घ *dirty_biपंचांगap;	/* dirty segment/section biपंचांगap */
	अचिन्हित पूर्णांक max_search;	/*
					 * maximum # of segments/sections
					 * to search
					 */
	अचिन्हित पूर्णांक offset;		/* last scanned biपंचांगap offset */
	अचिन्हित पूर्णांक ofs_unit;		/* biपंचांगap search unit */
	अचिन्हित पूर्णांक min_cost;		/* minimum cost */
	अचिन्हित दीर्घ दीर्घ oldest_age;	/* oldest age of segments having the same min cost */
	अचिन्हित पूर्णांक min_segno;		/* segment # having min. cost */
	अचिन्हित दीर्घ दीर्घ age;		/* mसमय of GCed section*/
	अचिन्हित दीर्घ दीर्घ age_threshold;/* age threshold */
पूर्ण;

काष्ठा seg_entry अणु
	अचिन्हित पूर्णांक type:6;		/* segment type like CURSEG_XXX_TYPE */
	अचिन्हित पूर्णांक valid_blocks:10;	/* # of valid blocks */
	अचिन्हित पूर्णांक ckpt_valid_blocks:10;	/* # of valid blocks last cp */
	अचिन्हित पूर्णांक padding:6;		/* padding */
	अचिन्हित अक्षर *cur_valid_map;	/* validity biपंचांगap of blocks */
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अचिन्हित अक्षर *cur_valid_map_mir;	/* mirror of current valid biपंचांगap */
#पूर्ण_अगर
	/*
	 * # of valid blocks and the validity biपंचांगap stored in the last
	 * checkpoपूर्णांक pack. This inक्रमmation is used by the SSR mode.
	 */
	अचिन्हित अक्षर *ckpt_valid_map;	/* validity biपंचांगap of blocks last cp */
	अचिन्हित अक्षर *discard_map;
	अचिन्हित दीर्घ दीर्घ mसमय;	/* modअगरication समय of the segment */
पूर्ण;

काष्ठा sec_entry अणु
	अचिन्हित पूर्णांक valid_blocks;	/* # of valid blocks in a section */
पूर्ण;

काष्ठा segment_allocation अणु
	व्योम (*allocate_segment)(काष्ठा f2fs_sb_info *, पूर्णांक, bool);
पूर्ण;

#घोषणा MAX_SKIP_GC_COUNT			16

काष्ठा inmem_pages अणु
	काष्ठा list_head list;
	काष्ठा page *page;
	block_t old_addr;		/* क्रम revoking when fail to commit */
पूर्ण;

काष्ठा sit_info अणु
	स्थिर काष्ठा segment_allocation *s_ops;

	block_t sit_base_addr;		/* start block address of SIT area */
	block_t sit_blocks;		/* # of blocks used by SIT area */
	block_t written_valid_blocks;	/* # of valid blocks in मुख्य area */
	अक्षर *biपंचांगap;			/* all biपंचांगaps poपूर्णांकer */
	अक्षर *sit_biपंचांगap;		/* SIT biपंचांगap poपूर्णांकer */
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अक्षर *sit_biपंचांगap_mir;		/* SIT biपंचांगap mirror */

	/* biपंचांगap of segments to be ignored by GC in हाल of errors */
	अचिन्हित दीर्घ *invalid_segmap;
#पूर्ण_अगर
	अचिन्हित पूर्णांक biपंचांगap_size;	/* SIT biपंचांगap size */

	अचिन्हित दीर्घ *पंचांगp_map;			/* biपंचांगap क्रम temporal use */
	अचिन्हित दीर्घ *dirty_sentries_biपंचांगap;	/* biपंचांगap क्रम dirty sentries */
	अचिन्हित पूर्णांक dirty_sentries;		/* # of dirty sentries */
	अचिन्हित पूर्णांक sents_per_block;		/* # of SIT entries per block */
	काष्ठा rw_semaphore sentry_lock;	/* to protect SIT cache */
	काष्ठा seg_entry *sentries;		/* SIT segment-level cache */
	काष्ठा sec_entry *sec_entries;		/* SIT section-level cache */

	/* क्रम cost-benefit algorithm in cleaning procedure */
	अचिन्हित दीर्घ दीर्घ elapsed_समय;	/* elapsed समय after mount */
	अचिन्हित दीर्घ दीर्घ mounted_समय;	/* mount समय */
	अचिन्हित दीर्घ दीर्घ min_mसमय;		/* min. modअगरication समय */
	अचिन्हित दीर्घ दीर्घ max_mसमय;		/* max. modअगरication समय */
	अचिन्हित दीर्घ दीर्घ dirty_min_mसमय;	/* rerange candidates in GC_AT */
	अचिन्हित दीर्घ दीर्घ dirty_max_mसमय;	/* rerange candidates in GC_AT */

	अचिन्हित पूर्णांक last_victim[MAX_GC_POLICY]; /* last victim segment # */
पूर्ण;

काष्ठा मुक्त_segmap_info अणु
	अचिन्हित पूर्णांक start_segno;	/* start segment number logically */
	अचिन्हित पूर्णांक मुक्त_segments;	/* # of मुक्त segments */
	अचिन्हित पूर्णांक मुक्त_sections;	/* # of मुक्त sections */
	spinlock_t segmap_lock;		/* मुक्त segmap lock */
	अचिन्हित दीर्घ *मुक्त_segmap;	/* मुक्त segment biपंचांगap */
	अचिन्हित दीर्घ *मुक्त_secmap;	/* मुक्त section biपंचांगap */
पूर्ण;

/* Notice: The order of dirty type is same with CURSEG_XXX in f2fs.h */
क्रमागत dirty_type अणु
	सूचीTY_HOT_DATA,		/* dirty segments asचिन्हित as hot data logs */
	सूचीTY_WARM_DATA,	/* dirty segments asचिन्हित as warm data logs */
	सूचीTY_COLD_DATA,	/* dirty segments asचिन्हित as cold data logs */
	सूचीTY_HOT_NODE,		/* dirty segments asचिन्हित as hot node logs */
	सूचीTY_WARM_NODE,	/* dirty segments asचिन्हित as warm node logs */
	सूचीTY_COLD_NODE,	/* dirty segments asचिन्हित as cold node logs */
	सूचीTY,			/* to count # of dirty segments */
	PRE,			/* to count # of entirely obsolete segments */
	NR_सूचीTY_TYPE
पूर्ण;

काष्ठा dirty_seglist_info अणु
	स्थिर काष्ठा victim_selection *v_ops;	/* victim selction operation */
	अचिन्हित दीर्घ *dirty_segmap[NR_सूचीTY_TYPE];
	अचिन्हित दीर्घ *dirty_secmap;
	काष्ठा mutex seglist_lock;		/* lock क्रम segment biपंचांगaps */
	पूर्णांक nr_dirty[NR_सूचीTY_TYPE];		/* # of dirty segments */
	अचिन्हित दीर्घ *victim_secmap;		/* background GC victims */
पूर्ण;

/* victim selection function क्रम cleaning and SSR */
काष्ठा victim_selection अणु
	पूर्णांक (*get_victim)(काष्ठा f2fs_sb_info *, अचिन्हित पूर्णांक *,
					पूर्णांक, पूर्णांक, अक्षर, अचिन्हित दीर्घ दीर्घ);
पूर्ण;

/* क्रम active log inक्रमmation */
काष्ठा curseg_info अणु
	काष्ठा mutex curseg_mutex;		/* lock क्रम consistency */
	काष्ठा f2fs_summary_block *sum_blk;	/* cached summary block */
	काष्ठा rw_semaphore journal_rwsem;	/* protect journal area */
	काष्ठा f2fs_journal *journal;		/* cached journal info */
	अचिन्हित अक्षर alloc_type;		/* current allocation type */
	अचिन्हित लघु seg_type;		/* segment type like CURSEG_XXX_TYPE */
	अचिन्हित पूर्णांक segno;			/* current segment number */
	अचिन्हित लघु next_blkoff;		/* next block offset to ग_लिखो */
	अचिन्हित पूर्णांक zone;			/* current zone number */
	अचिन्हित पूर्णांक next_segno;		/* pपुनः_स्मृतिated segment */
	bool inited;				/* indicate inmem log is inited */
पूर्ण;

काष्ठा sit_entry_set अणु
	काष्ठा list_head set_list;	/* link with all sit sets */
	अचिन्हित पूर्णांक start_segno;	/* start segno of sits in set */
	अचिन्हित पूर्णांक entry_cnt;		/* the # of sit entries in set */
पूर्ण;

/*
 * अंतरभूत functions
 */
अटल अंतरभूत काष्ठा curseg_info *CURSEG_I(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	वापस (काष्ठा curseg_info *)(SM_I(sbi)->curseg_array + type);
पूर्ण

अटल अंतरभूत काष्ठा seg_entry *get_seg_entry(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित पूर्णांक segno)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	वापस &sit_i->sentries[segno];
पूर्ण

अटल अंतरभूत काष्ठा sec_entry *get_sec_entry(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित पूर्णांक segno)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	वापस &sit_i->sec_entries[GET_SEC_FROM_SEG(sbi, segno)];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_valid_blocks(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित पूर्णांक segno, bool use_section)
अणु
	/*
	 * In order to get # of valid blocks in a section instantly from many
	 * segments, f2fs manages two counting काष्ठाures separately.
	 */
	अगर (use_section && __is_large_section(sbi))
		वापस get_sec_entry(sbi, segno)->valid_blocks;
	अन्यथा
		वापस get_seg_entry(sbi, segno)->valid_blocks;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_ckpt_valid_blocks(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित पूर्णांक segno, bool use_section)
अणु
	अगर (use_section && __is_large_section(sbi)) अणु
		अचिन्हित पूर्णांक start_segno = START_SEGNO(segno);
		अचिन्हित पूर्णांक blocks = 0;
		पूर्णांक i;

		क्रम (i = 0; i < sbi->segs_per_sec; i++, start_segno++) अणु
			काष्ठा seg_entry *se = get_seg_entry(sbi, start_segno);

			blocks += se->ckpt_valid_blocks;
		पूर्ण
		वापस blocks;
	पूर्ण
	वापस get_seg_entry(sbi, segno)->ckpt_valid_blocks;
पूर्ण

अटल अंतरभूत व्योम seg_info_from_raw_sit(काष्ठा seg_entry *se,
					काष्ठा f2fs_sit_entry *rs)
अणु
	se->valid_blocks = GET_SIT_VBLOCKS(rs);
	se->ckpt_valid_blocks = GET_SIT_VBLOCKS(rs);
	स_नकल(se->cur_valid_map, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
	स_नकल(se->ckpt_valid_map, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	स_नकल(se->cur_valid_map_mir, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
#पूर्ण_अगर
	se->type = GET_SIT_TYPE(rs);
	se->mसमय = le64_to_cpu(rs->mसमय);
पूर्ण

अटल अंतरभूत व्योम __seg_info_to_raw_sit(काष्ठा seg_entry *se,
					काष्ठा f2fs_sit_entry *rs)
अणु
	अचिन्हित लघु raw_vblocks = (se->type << SIT_VBLOCKS_SHIFT) |
					se->valid_blocks;
	rs->vblocks = cpu_to_le16(raw_vblocks);
	स_नकल(rs->valid_map, se->cur_valid_map, SIT_VBLOCK_MAP_SIZE);
	rs->mसमय = cpu_to_le64(se->mसमय);
पूर्ण

अटल अंतरभूत व्योम seg_info_to_sit_page(काष्ठा f2fs_sb_info *sbi,
				काष्ठा page *page, अचिन्हित पूर्णांक start)
अणु
	काष्ठा f2fs_sit_block *raw_sit;
	काष्ठा seg_entry *se;
	काष्ठा f2fs_sit_entry *rs;
	अचिन्हित पूर्णांक end = min(start + SIT_ENTRY_PER_BLOCK,
					(अचिन्हित दीर्घ)MAIN_SEGS(sbi));
	पूर्णांक i;

	raw_sit = (काष्ठा f2fs_sit_block *)page_address(page);
	स_रखो(raw_sit, 0, PAGE_SIZE);
	क्रम (i = 0; i < end - start; i++) अणु
		rs = &raw_sit->entries[i];
		se = get_seg_entry(sbi, start + i);
		__seg_info_to_raw_sit(se, rs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम seg_info_to_raw_sit(काष्ठा seg_entry *se,
					काष्ठा f2fs_sit_entry *rs)
अणु
	__seg_info_to_raw_sit(se, rs);

	स_नकल(se->ckpt_valid_map, rs->valid_map, SIT_VBLOCK_MAP_SIZE);
	se->ckpt_valid_blocks = se->valid_blocks;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक find_next_inuse(काष्ठा मुक्त_segmap_info *मुक्त_i,
		अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक segno)
अणु
	अचिन्हित पूर्णांक ret;
	spin_lock(&मुक्त_i->segmap_lock);
	ret = find_next_bit(मुक्त_i->मुक्त_segmap, max, segno);
	spin_unlock(&मुक्त_i->segmap_lock);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __set_मुक्त(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);
	अचिन्हित पूर्णांक start_segno = GET_SEG_FROM_SEC(sbi, secno);
	अचिन्हित पूर्णांक next;
	अचिन्हित पूर्णांक usable_segs = f2fs_usable_segs_in_sec(sbi, segno);

	spin_lock(&मुक्त_i->segmap_lock);
	clear_bit(segno, मुक्त_i->मुक्त_segmap);
	मुक्त_i->मुक्त_segments++;

	next = find_next_bit(मुक्त_i->मुक्त_segmap,
			start_segno + sbi->segs_per_sec, start_segno);
	अगर (next >= start_segno + usable_segs) अणु
		clear_bit(secno, मुक्त_i->मुक्त_secmap);
		मुक्त_i->मुक्त_sections++;
	पूर्ण
	spin_unlock(&मुक्त_i->segmap_lock);
पूर्ण

अटल अंतरभूत व्योम __set_inuse(काष्ठा f2fs_sb_info *sbi,
		अचिन्हित पूर्णांक segno)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);

	set_bit(segno, मुक्त_i->मुक्त_segmap);
	मुक्त_i->मुक्त_segments--;
	अगर (!test_and_set_bit(secno, मुक्त_i->मुक्त_secmap))
		मुक्त_i->मुक्त_sections--;
पूर्ण

अटल अंतरभूत व्योम __set_test_and_मुक्त(काष्ठा f2fs_sb_info *sbi,
		अचिन्हित पूर्णांक segno, bool inmem)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);
	अचिन्हित पूर्णांक start_segno = GET_SEG_FROM_SEC(sbi, secno);
	अचिन्हित पूर्णांक next;
	अचिन्हित पूर्णांक usable_segs = f2fs_usable_segs_in_sec(sbi, segno);

	spin_lock(&मुक्त_i->segmap_lock);
	अगर (test_and_clear_bit(segno, मुक्त_i->मुक्त_segmap)) अणु
		मुक्त_i->मुक्त_segments++;

		अगर (!inmem && IS_CURSEC(sbi, secno))
			जाओ skip_मुक्त;
		next = find_next_bit(मुक्त_i->मुक्त_segmap,
				start_segno + sbi->segs_per_sec, start_segno);
		अगर (next >= start_segno + usable_segs) अणु
			अगर (test_and_clear_bit(secno, मुक्त_i->मुक्त_secmap))
				मुक्त_i->मुक्त_sections++;
		पूर्ण
	पूर्ण
skip_मुक्त:
	spin_unlock(&मुक्त_i->segmap_lock);
पूर्ण

अटल अंतरभूत व्योम __set_test_and_inuse(काष्ठा f2fs_sb_info *sbi,
		अचिन्हित पूर्णांक segno)
अणु
	काष्ठा मुक्त_segmap_info *मुक्त_i = FREE_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);

	spin_lock(&मुक्त_i->segmap_lock);
	अगर (!test_and_set_bit(segno, मुक्त_i->मुक्त_segmap)) अणु
		मुक्त_i->मुक्त_segments--;
		अगर (!test_and_set_bit(secno, मुक्त_i->मुक्त_secmap))
			मुक्त_i->मुक्त_sections--;
	पूर्ण
	spin_unlock(&मुक्त_i->segmap_lock);
पूर्ण

अटल अंतरभूत व्योम get_sit_biपंचांगap(काष्ठा f2fs_sb_info *sbi,
		व्योम *dst_addr)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अगर (स_भेद(sit_i->sit_biपंचांगap, sit_i->sit_biपंचांगap_mir,
						sit_i->biपंचांगap_size))
		f2fs_bug_on(sbi, 1);
#पूर्ण_अगर
	स_नकल(dst_addr, sit_i->sit_biपंचांगap, sit_i->biपंचांगap_size);
पूर्ण

अटल अंतरभूत block_t written_block_count(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस SIT_I(sbi)->written_valid_blocks;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक मुक्त_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस FREE_I(sbi)->मुक्त_segments;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक reserved_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस SM_I(sbi)->reserved_segments;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक मुक्त_sections(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस FREE_I(sbi)->मुक्त_sections;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक preमुक्त_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस सूचीTY_I(sbi)->nr_dirty[PRE];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dirty_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस सूचीTY_I(sbi)->nr_dirty[सूचीTY_HOT_DATA] +
		सूचीTY_I(sbi)->nr_dirty[सूचीTY_WARM_DATA] +
		सूचीTY_I(sbi)->nr_dirty[सूचीTY_COLD_DATA] +
		सूचीTY_I(sbi)->nr_dirty[सूचीTY_HOT_NODE] +
		सूचीTY_I(sbi)->nr_dirty[सूचीTY_WARM_NODE] +
		सूचीTY_I(sbi)->nr_dirty[सूचीTY_COLD_NODE];
पूर्ण

अटल अंतरभूत पूर्णांक overprovision_segments(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस SM_I(sbi)->ovp_segments;
पूर्ण

अटल अंतरभूत पूर्णांक reserved_sections(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस GET_SEC_FROM_SEG(sbi, reserved_segments(sbi));
पूर्ण

अटल अंतरभूत bool has_curseg_enough_space(काष्ठा f2fs_sb_info *sbi)
अणु
	अचिन्हित पूर्णांक node_blocks = get_pages(sbi, F2FS_सूचीTY_NODES) +
					get_pages(sbi, F2FS_सूचीTY_DENTS);
	अचिन्हित पूर्णांक dent_blocks = get_pages(sbi, F2FS_सूचीTY_DENTS);
	अचिन्हित पूर्णांक segno, left_blocks;
	पूर्णांक i;

	/* check current node segment */
	क्रम (i = CURSEG_HOT_NODE; i <= CURSEG_COLD_NODE; i++) अणु
		segno = CURSEG_I(sbi, i)->segno;
		left_blocks = f2fs_usable_blks_in_seg(sbi, segno) -
				get_seg_entry(sbi, segno)->ckpt_valid_blocks;

		अगर (node_blocks > left_blocks)
			वापस false;
	पूर्ण

	/* check current data segment */
	segno = CURSEG_I(sbi, CURSEG_HOT_DATA)->segno;
	left_blocks = f2fs_usable_blks_in_seg(sbi, segno) -
			get_seg_entry(sbi, segno)->ckpt_valid_blocks;
	अगर (dent_blocks > left_blocks)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool has_not_enough_मुक्त_secs(काष्ठा f2fs_sb_info *sbi,
					पूर्णांक मुक्तd, पूर्णांक needed)
अणु
	पूर्णांक node_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_NODES);
	पूर्णांक dent_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_DENTS);
	पूर्णांक imeta_secs = get_blocktype_secs(sbi, F2FS_सूचीTY_IMETA);

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		वापस false;

	अगर (मुक्त_sections(sbi) + मुक्तd == reserved_sections(sbi) + needed &&
			has_curseg_enough_space(sbi))
		वापस false;
	वापस (मुक्त_sections(sbi) + मुक्तd) <=
		(node_secs + 2 * dent_secs + imeta_secs +
		reserved_sections(sbi) + needed);
पूर्ण

अटल अंतरभूत bool f2fs_is_checkpoपूर्णांक_पढ़ोy(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (likely(!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस true;
	अगर (likely(!has_not_enough_मुक्त_secs(sbi, 0, 0)))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool excess_preमुक्त_segs(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस preमुक्त_segments(sbi) > SM_I(sbi)->rec_preमुक्त_segments;
पूर्ण

अटल अंतरभूत पूर्णांक utilization(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस भाग_u64((u64)valid_user_blocks(sbi) * 100,
					sbi->user_block_count);
पूर्ण

/*
 * Someबार f2fs may be better to drop out-of-place update policy.
 * And, users can control the policy through sysfs entries.
 * There are five policies with triggering conditions as follows.
 * F2FS_IPU_FORCE - all the समय,
 * F2FS_IPU_SSR - अगर SSR mode is activated,
 * F2FS_IPU_UTIL - अगर FS utilization is over threashold,
 * F2FS_IPU_SSR_UTIL - अगर SSR mode is activated and FS utilization is over
 *                     threashold,
 * F2FS_IPU_FSYNC - activated in fsync path only क्रम high perक्रमmance flash
 *                     storages. IPU will be triggered only अगर the # of dirty
 *                     pages over min_fsync_blocks. (=शेष option)
 * F2FS_IPU_ASYNC - करो IPU given by asynchronous ग_लिखो requests.
 * F2FS_IPU_NOCACHE - disable IPU bio cache.
 * F2FS_IPUT_DISABLE - disable IPU. (=शेष option in LFS mode)
 */
#घोषणा DEF_MIN_IPU_UTIL	70
#घोषणा DEF_MIN_FSYNC_BLOCKS	8
#घोषणा DEF_MIN_HOT_BLOCKS	16

#घोषणा SMALL_VOLUME_SEGMENTS	(16 * 512)	/* 16GB */

क्रमागत अणु
	F2FS_IPU_FORCE,
	F2FS_IPU_SSR,
	F2FS_IPU_UTIL,
	F2FS_IPU_SSR_UTIL,
	F2FS_IPU_FSYNC,
	F2FS_IPU_ASYNC,
	F2FS_IPU_NOCACHE,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक curseg_segno(काष्ठा f2fs_sb_info *sbi,
		पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	वापस curseg->segno;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर curseg_alloc_type(काष्ठा f2fs_sb_info *sbi,
		पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	वापस curseg->alloc_type;
पूर्ण

अटल अंतरभूत अचिन्हित लघु curseg_blkoff(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	काष्ठा curseg_info *curseg = CURSEG_I(sbi, type);
	वापस curseg->next_blkoff;
पूर्ण

अटल अंतरभूत व्योम check_seg_range(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	f2fs_bug_on(sbi, segno > TOTAL_SEGS(sbi) - 1);
पूर्ण

अटल अंतरभूत व्योम verअगरy_fio_blkaddr(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;

	अगर (__is_valid_data_blkaddr(fio->old_blkaddr))
		verअगरy_blkaddr(sbi, fio->old_blkaddr, __is_meta_io(fio) ?
					META_GENERIC : DATA_GENERIC);
	verअगरy_blkaddr(sbi, fio->new_blkaddr, __is_meta_io(fio) ?
					META_GENERIC : DATA_GENERIC_ENHANCE);
पूर्ण

/*
 * Summary block is always treated as an invalid block
 */
अटल अंतरभूत पूर्णांक check_block_count(काष्ठा f2fs_sb_info *sbi,
		पूर्णांक segno, काष्ठा f2fs_sit_entry *raw_sit)
अणु
	bool is_valid  = test_bit_le(0, raw_sit->valid_map) ? true : false;
	पूर्णांक valid_blocks = 0;
	पूर्णांक cur_pos = 0, next_pos;
	अचिन्हित पूर्णांक usable_blks_per_seg = f2fs_usable_blks_in_seg(sbi, segno);

	/* check biपंचांगap with valid block count */
	करो अणु
		अगर (is_valid) अणु
			next_pos = find_next_zero_bit_le(&raw_sit->valid_map,
					usable_blks_per_seg,
					cur_pos);
			valid_blocks += next_pos - cur_pos;
		पूर्ण अन्यथा
			next_pos = find_next_bit_le(&raw_sit->valid_map,
					usable_blks_per_seg,
					cur_pos);
		cur_pos = next_pos;
		is_valid = !is_valid;
	पूर्ण जबतक (cur_pos < usable_blks_per_seg);

	अगर (unlikely(GET_SIT_VBLOCKS(raw_sit) != valid_blocks)) अणु
		f2fs_err(sbi, "Mismatch valid blocks %d vs. %d",
			 GET_SIT_VBLOCKS(raw_sit), valid_blocks);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (usable_blks_per_seg < sbi->blocks_per_seg)
		f2fs_bug_on(sbi, find_next_bit_le(&raw_sit->valid_map,
				sbi->blocks_per_seg,
				usable_blks_per_seg) != sbi->blocks_per_seg);

	/* check segment usage, and check boundary of a given segment number */
	अगर (unlikely(GET_SIT_VBLOCKS(raw_sit) > usable_blks_per_seg
					|| segno > TOTAL_SEGS(sbi) - 1)) अणु
		f2fs_err(sbi, "Wrong valid blocks %d or segno %u",
			 GET_SIT_VBLOCKS(raw_sit), segno);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत pgoff_t current_sit_addr(काष्ठा f2fs_sb_info *sbi,
						अचिन्हित पूर्णांक start)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित पूर्णांक offset = SIT_BLOCK_OFFSET(start);
	block_t blk_addr = sit_i->sit_base_addr + offset;

	check_seg_range(sbi, start);

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अगर (f2fs_test_bit(offset, sit_i->sit_biपंचांगap) !=
			f2fs_test_bit(offset, sit_i->sit_biपंचांगap_mir))
		f2fs_bug_on(sbi, 1);
#पूर्ण_अगर

	/* calculate sit block address */
	अगर (f2fs_test_bit(offset, sit_i->sit_biपंचांगap))
		blk_addr += sit_i->sit_blocks;

	वापस blk_addr;
पूर्ण

अटल अंतरभूत pgoff_t next_sit_addr(काष्ठा f2fs_sb_info *sbi,
						pgoff_t block_addr)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	block_addr -= sit_i->sit_base_addr;
	अगर (block_addr < sit_i->sit_blocks)
		block_addr += sit_i->sit_blocks;
	अन्यथा
		block_addr -= sit_i->sit_blocks;

	वापस block_addr + sit_i->sit_base_addr;
पूर्ण

अटल अंतरभूत व्योम set_to_next_sit(काष्ठा sit_info *sit_i, अचिन्हित पूर्णांक start)
अणु
	अचिन्हित पूर्णांक block_off = SIT_BLOCK_OFFSET(start);

	f2fs_change_bit(block_off, sit_i->sit_biपंचांगap);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	f2fs_change_bit(block_off, sit_i->sit_biपंचांगap_mir);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ get_mसमय(काष्ठा f2fs_sb_info *sbi,
						bool base_समय)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	समय64_t dअगरf, now = kसमय_get_bootसमय_seconds();

	अगर (now >= sit_i->mounted_समय)
		वापस sit_i->elapsed_समय + now - sit_i->mounted_समय;

	/* प्रणाली समय is set to the past */
	अगर (!base_समय) अणु
		dअगरf = sit_i->mounted_समय - now;
		अगर (sit_i->elapsed_समय >= dअगरf)
			वापस sit_i->elapsed_समय - dअगरf;
		वापस 0;
	पूर्ण
	वापस sit_i->elapsed_समय;
पूर्ण

अटल अंतरभूत व्योम set_summary(काष्ठा f2fs_summary *sum, nid_t nid,
			अचिन्हित पूर्णांक ofs_in_node, अचिन्हित अक्षर version)
अणु
	sum->nid = cpu_to_le32(nid);
	sum->ofs_in_node = cpu_to_le16(ofs_in_node);
	sum->version = version;
पूर्ण

अटल अंतरभूत block_t start_sum_block(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस __start_cp_addr(sbi) +
		le32_to_cpu(F2FS_CKPT(sbi)->cp_pack_start_sum);
पूर्ण

अटल अंतरभूत block_t sum_blk_addr(काष्ठा f2fs_sb_info *sbi, पूर्णांक base, पूर्णांक type)
अणु
	वापस __start_cp_addr(sbi) +
		le32_to_cpu(F2FS_CKPT(sbi)->cp_pack_total_block_count)
				- (base + 1) + type;
पूर्ण

अटल अंतरभूत bool sec_usage_check(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक secno)
अणु
	अगर (IS_CURSEC(sbi, secno) || (sbi->cur_victim_sec == secno))
		वापस true;
	वापस false;
पूर्ण

/*
 * It is very important to gather dirty pages and ग_लिखो at once, so that we can
 * submit a big bio without पूर्णांकerfering other data ग_लिखोs.
 * By शेष, 512 pages क्रम directory data,
 * 512 pages (2MB) * 8 क्रम nodes, and
 * 256 pages * 8 क्रम meta are set.
 */
अटल अंतरभूत पूर्णांक nr_pages_to_skip(काष्ठा f2fs_sb_info *sbi, पूर्णांक type)
अणु
	अगर (sbi->sb->s_bdi->wb.dirty_exceeded)
		वापस 0;

	अगर (type == DATA)
		वापस sbi->blocks_per_seg;
	अन्यथा अगर (type == NODE)
		वापस 8 * sbi->blocks_per_seg;
	अन्यथा अगर (type == META)
		वापस 8 * BIO_MAX_VECS;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * When writing pages, it'd better align nr_to_ग_लिखो क्रम segment size.
 */
अटल अंतरभूत दीर्घ nr_pages_to_ग_लिखो(काष्ठा f2fs_sb_info *sbi, पूर्णांक type,
					काष्ठा ग_लिखोback_control *wbc)
अणु
	दीर्घ nr_to_ग_लिखो, desired;

	अगर (wbc->sync_mode != WB_SYNC_NONE)
		वापस 0;

	nr_to_ग_लिखो = wbc->nr_to_ग_लिखो;
	desired = BIO_MAX_VECS;
	अगर (type == NODE)
		desired <<= 1;

	wbc->nr_to_ग_लिखो = desired;
	वापस desired - nr_to_ग_लिखो;
पूर्ण

अटल अंतरभूत व्योम wake_up_discard_thपढ़ो(काष्ठा f2fs_sb_info *sbi, bool क्रमce)
अणु
	काष्ठा discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	bool wakeup = false;
	पूर्णांक i;

	अगर (क्रमce)
		जाओ wake_up;

	mutex_lock(&dcc->cmd_lock);
	क्रम (i = MAX_PLIST_NUM - 1; i >= 0; i--) अणु
		अगर (i + 1 < dcc->discard_granularity)
			अवरोध;
		अगर (!list_empty(&dcc->pend_list[i])) अणु
			wakeup = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&dcc->cmd_lock);
	अगर (!wakeup || !is_idle(sbi, DISCARD_TIME))
		वापस;
wake_up:
	dcc->discard_wake = 1;
	wake_up_पूर्णांकerruptible_all(&dcc->discard_रुको_queue);
पूर्ण
