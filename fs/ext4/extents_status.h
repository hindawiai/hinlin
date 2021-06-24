<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/ext4/extents_status.h
 *
 * Written by Yongqiang Yang <xiaoqiangnk@gmail.com>
 * Modअगरied by
 *	Allison Henderson <achender@linux.vnet.ibm.com>
 *	Zheng Liu <wenqing.lz@taobao.com>
 *
 */

#अगर_अघोषित _EXT4_EXTENTS_STATUS_H
#घोषणा _EXT4_EXTENTS_STATUS_H

/*
 * Turn on ES_DEBUG__ to get lots of info about extent status operations.
 */
#अगर_घोषित ES_DEBUG__
#घोषणा es_debug(fmt, ...)	prपूर्णांकk(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा es_debug(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/*
 * With ES_AGGRESSIVE_TEST defined, the result of es caching will be
 * checked with old map_block's result.
 */
#घोषणा ES_AGGRESSIVE_TEST__

/*
 * These flags live in the high bits of extent_status.es_pblk
 */
क्रमागत अणु
	ES_WRITTEN_B,
	ES_UNWRITTEN_B,
	ES_DELAYED_B,
	ES_HOLE_B,
	ES_REFERENCED_B,
	ES_FLAGS
पूर्ण;

#घोषणा ES_SHIFT (माप(ext4_fsblk_t)*8 - ES_FLAGS)
#घोषणा ES_MASK (~((ext4_fsblk_t)0) << ES_SHIFT)

#घोषणा EXTENT_STATUS_WRITTEN	(1 << ES_WRITTEN_B)
#घोषणा EXTENT_STATUS_UNWRITTEN (1 << ES_UNWRITTEN_B)
#घोषणा EXTENT_STATUS_DELAYED	(1 << ES_DELAYED_B)
#घोषणा EXTENT_STATUS_HOLE	(1 << ES_HOLE_B)
#घोषणा EXTENT_STATUS_REFERENCED	(1 << ES_REFERENCED_B)

#घोषणा ES_TYPE_MASK	((ext4_fsblk_t)(EXTENT_STATUS_WRITTEN | \
			  EXTENT_STATUS_UNWRITTEN | \
			  EXTENT_STATUS_DELAYED | \
			  EXTENT_STATUS_HOLE) << ES_SHIFT)

काष्ठा ext4_sb_info;
काष्ठा ext4_extent;

काष्ठा extent_status अणु
	काष्ठा rb_node rb_node;
	ext4_lblk_t es_lblk;	/* first logical block extent covers */
	ext4_lblk_t es_len;	/* length of extent in block */
	ext4_fsblk_t es_pblk;	/* first physical block */
पूर्ण;

काष्ठा ext4_es_tree अणु
	काष्ठा rb_root root;
	काष्ठा extent_status *cache_es;	/* recently accessed extent */
पूर्ण;

काष्ठा ext4_es_stats अणु
	अचिन्हित दीर्घ es_stats_shrunk;
	काष्ठा percpu_counter es_stats_cache_hits;
	काष्ठा percpu_counter es_stats_cache_misses;
	u64 es_stats_scan_समय;
	u64 es_stats_max_scan_समय;
	काष्ठा percpu_counter es_stats_all_cnt;
	काष्ठा percpu_counter es_stats_shk_cnt;
पूर्ण;

/*
 * Pending cluster reservations क्रम bigalloc file प्रणालीs
 *
 * A cluster with a pending reservation is a logical cluster shared by at
 * least one extent in the extents status tree with delayed and unwritten
 * status and at least one other written or unwritten extent.  The
 * reservation is said to be pending because a cluster reservation would
 * have to be taken in the event all blocks in the cluster shared with
 * written or unwritten extents were deleted जबतक the delayed and
 * unwritten blocks reमुख्यed.
 *
 * The set of pending cluster reservations is an auxiliary data काष्ठाure
 * used with the extents status tree to implement reserved cluster/block
 * accounting क्रम bigalloc file प्रणालीs.  The set is kept in memory and
 * records all pending cluster reservations.
 *
 * Its primary function is to aव्योम the need to पढ़ो extents from the
 * disk when invalidating pages as a result of a truncate, punch hole, or
 * collapse range operation.  Page invalidation requires a decrease in the
 * reserved cluster count अगर it results in the removal of all delayed
 * and unwritten extents (blocks) from a cluster that is not shared with a
 * written or unwritten extent, and no decrease otherwise.  Determining
 * whether the cluster is shared can be करोne by searching क्रम a pending
 * reservation on it.
 *
 * Secondarily, it provides a potentially faster method क्रम determining
 * whether the reserved cluster count should be increased when a physical
 * cluster is deallocated as a result of a truncate, punch hole, or
 * collapse range operation.  The necessary inक्रमmation is also present
 * in the extents status tree, but might be more rapidly accessed in
 * the pending reservation set in many हालs due to smaller size.
 *
 * The pending cluster reservation set is implemented as a red-black tree
 * with the goal of minimizing per page search समय overhead.
 */

काष्ठा pending_reservation अणु
	काष्ठा rb_node rb_node;
	ext4_lblk_t lclu;
पूर्ण;

काष्ठा ext4_pending_tree अणु
	काष्ठा rb_root root;
पूर्ण;

बाह्य पूर्णांक __init ext4_init_es(व्योम);
बाह्य व्योम ext4_निकास_es(व्योम);
बाह्य व्योम ext4_es_init_tree(काष्ठा ext4_es_tree *tree);

बाह्य पूर्णांक ext4_es_insert_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
				 ext4_lblk_t len, ext4_fsblk_t pblk,
				 अचिन्हित पूर्णांक status);
बाह्य व्योम ext4_es_cache_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
				 ext4_lblk_t len, ext4_fsblk_t pblk,
				 अचिन्हित पूर्णांक status);
बाह्य पूर्णांक ext4_es_हटाओ_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
				 ext4_lblk_t len);
बाह्य व्योम ext4_es_find_extent_range(काष्ठा inode *inode,
				      पूर्णांक (*match_fn)(काष्ठा extent_status *es),
				      ext4_lblk_t lblk, ext4_lblk_t end,
				      काष्ठा extent_status *es);
बाह्य पूर्णांक ext4_es_lookup_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
				 ext4_lblk_t *next_lblk,
				 काष्ठा extent_status *es);
बाह्य bool ext4_es_scan_range(काष्ठा inode *inode,
			       पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			       ext4_lblk_t lblk, ext4_lblk_t end);
बाह्य bool ext4_es_scan_clu(काष्ठा inode *inode,
			     पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			     ext4_lblk_t lblk);

अटल अंतरभूत अचिन्हित पूर्णांक ext4_es_status(काष्ठा extent_status *es)
अणु
	वापस es->es_pblk >> ES_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ext4_es_type(काष्ठा extent_status *es)
अणु
	वापस (es->es_pblk & ES_TYPE_MASK) >> ES_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_written(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_type(es) & EXTENT_STATUS_WRITTEN) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_unwritten(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_type(es) & EXTENT_STATUS_UNWRITTEN) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_delayed(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_type(es) & EXTENT_STATUS_DELAYED) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_hole(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_type(es) & EXTENT_STATUS_HOLE) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_mapped(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_is_written(es) || ext4_es_is_unwritten(es));
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_delonly(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_is_delayed(es) && !ext4_es_is_unwritten(es));
पूर्ण

अटल अंतरभूत व्योम ext4_es_set_referenced(काष्ठा extent_status *es)
अणु
	es->es_pblk |= ((ext4_fsblk_t)EXTENT_STATUS_REFERENCED) << ES_SHIFT;
पूर्ण

अटल अंतरभूत व्योम ext4_es_clear_referenced(काष्ठा extent_status *es)
अणु
	es->es_pblk &= ~(((ext4_fsblk_t)EXTENT_STATUS_REFERENCED) << ES_SHIFT);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_es_is_referenced(काष्ठा extent_status *es)
अणु
	वापस (ext4_es_status(es) & EXTENT_STATUS_REFERENCED) != 0;
पूर्ण

अटल अंतरभूत ext4_fsblk_t ext4_es_pblock(काष्ठा extent_status *es)
अणु
	वापस es->es_pblk & ~ES_MASK;
पूर्ण

अटल अंतरभूत ext4_fsblk_t ext4_es_show_pblock(काष्ठा extent_status *es)
अणु
	ext4_fsblk_t pblock = ext4_es_pblock(es);
	वापस pblock == ~ES_MASK ? 0 : pblock;
पूर्ण

अटल अंतरभूत व्योम ext4_es_store_pblock(काष्ठा extent_status *es,
					ext4_fsblk_t pb)
अणु
	ext4_fsblk_t block;

	block = (pb & ~ES_MASK) | (es->es_pblk & ES_MASK);
	es->es_pblk = block;
पूर्ण

अटल अंतरभूत व्योम ext4_es_store_status(काष्ठा extent_status *es,
					अचिन्हित पूर्णांक status)
अणु
	es->es_pblk = (((ext4_fsblk_t)status << ES_SHIFT) & ES_MASK) |
		      (es->es_pblk & ~ES_MASK);
पूर्ण

अटल अंतरभूत व्योम ext4_es_store_pblock_status(काष्ठा extent_status *es,
					       ext4_fsblk_t pb,
					       अचिन्हित पूर्णांक status)
अणु
	es->es_pblk = (((ext4_fsblk_t)status << ES_SHIFT) & ES_MASK) |
		      (pb & ~ES_MASK);
पूर्ण

बाह्य पूर्णांक ext4_es_रेजिस्टर_shrinker(काष्ठा ext4_sb_info *sbi);
बाह्य व्योम ext4_es_unरेजिस्टर_shrinker(काष्ठा ext4_sb_info *sbi);

बाह्य पूर्णांक ext4_seq_es_shrinker_info_show(काष्ठा seq_file *seq, व्योम *v);

बाह्य पूर्णांक __init ext4_init_pending(व्योम);
बाह्य व्योम ext4_निकास_pending(व्योम);
बाह्य व्योम ext4_init_pending_tree(काष्ठा ext4_pending_tree *tree);
बाह्य व्योम ext4_हटाओ_pending(काष्ठा inode *inode, ext4_lblk_t lblk);
बाह्य bool ext4_is_pending(काष्ठा inode *inode, ext4_lblk_t lblk);
बाह्य पूर्णांक ext4_es_insert_delayed_block(काष्ठा inode *inode, ext4_lblk_t lblk,
					bool allocated);
बाह्य अचिन्हित पूर्णांक ext4_es_delayed_clu(काष्ठा inode *inode, ext4_lblk_t lblk,
					ext4_lblk_t len);
बाह्य व्योम ext4_clear_inode_es(काष्ठा inode *inode);

#पूर्ण_अगर /* _EXT4_EXTENTS_STATUS_H */
