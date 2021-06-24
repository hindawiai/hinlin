<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * भाग.स
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_ALLOC_H
#घोषणा OCFS2_ALLOC_H


/*
 * For xattr tree leaf, we limit the leaf byte size to be 64K.
 */
#घोषणा OCFS2_MAX_XATTR_TREE_LEAF_SIZE 65536

/*
 * ocfs2_extent_tree and ocfs2_extent_tree_operations are used to असलtract
 * the b-tree operations in ocfs2. Now all the b-tree operations are not
 * limited to ocfs2_dinode only. Any data which need to allocate clusters
 * to store can use b-tree. And it only needs to implement its ocfs2_extent_tree
 * and operation.
 *
 * ocfs2_extent_tree becomes the first-class object क्रम extent tree
 * manipulation.  Callers of the alloc.c code need to fill it via one of
 * the ocfs2_init_*_extent_tree() operations below.
 *
 * ocfs2_extent_tree contains info क्रम the root of the b-tree, it must have a
 * root ocfs2_extent_list and a root_bh so that they can be used in the b-tree
 * functions.  It needs the ocfs2_caching_info काष्ठाure associated with
 * I/O on the tree.  With metadata ecc, we now call dअगरferent journal_access
 * functions क्रम each type of metadata, so it must have the
 * root_journal_access function.
 * ocfs2_extent_tree_operations असलtract the normal operations we करो क्रम
 * the root of extent b-tree.
 */
काष्ठा ocfs2_extent_tree_operations;
काष्ठा ocfs2_extent_tree अणु
	स्थिर काष्ठा ocfs2_extent_tree_operations *et_ops;
	काष्ठा buffer_head			*et_root_bh;
	काष्ठा ocfs2_extent_list		*et_root_el;
	काष्ठा ocfs2_caching_info		*et_ci;
	ocfs2_journal_access_func		et_root_journal_access;
	व्योम					*et_object;
	अचिन्हित पूर्णांक				et_max_leaf_clusters;
	काष्ठा ocfs2_cached_dealloc_ctxt	*et_dealloc;
पूर्ण;

/*
 * ocfs2_init_*_extent_tree() will fill an ocfs2_extent_tree from the
 * specअगरied object buffer.
 */
व्योम ocfs2_init_dinode_extent_tree(काष्ठा ocfs2_extent_tree *et,
				   काष्ठा ocfs2_caching_info *ci,
				   काष्ठा buffer_head *bh);
व्योम ocfs2_init_xattr_tree_extent_tree(काष्ठा ocfs2_extent_tree *et,
				       काष्ठा ocfs2_caching_info *ci,
				       काष्ठा buffer_head *bh);
काष्ठा ocfs2_xattr_value_buf;
व्योम ocfs2_init_xattr_value_extent_tree(काष्ठा ocfs2_extent_tree *et,
					काष्ठा ocfs2_caching_info *ci,
					काष्ठा ocfs2_xattr_value_buf *vb);
व्योम ocfs2_init_dx_root_extent_tree(काष्ठा ocfs2_extent_tree *et,
				    काष्ठा ocfs2_caching_info *ci,
				    काष्ठा buffer_head *bh);
व्योम ocfs2_init_refcount_extent_tree(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *bh);

/*
 * Read an extent block पूर्णांकo *bh.  If *bh is शून्य, a bh will be
 * allocated.  This is a cached पढ़ो.  The extent block will be validated
 * with ocfs2_validate_extent_block().
 */
पूर्णांक ocfs2_पढ़ो_extent_block(काष्ठा ocfs2_caching_info *ci, u64 eb_blkno,
			    काष्ठा buffer_head **bh);

काष्ठा ocfs2_alloc_context;
पूर्णांक ocfs2_insert_extent(handle_t *handle,
			काष्ठा ocfs2_extent_tree *et,
			u32 cpos,
			u64 start_blk,
			u32 new_clusters,
			u8 flags,
			काष्ठा ocfs2_alloc_context *meta_ac);

क्रमागत ocfs2_alloc_restarted अणु
	RESTART_NONE = 0,
	RESTART_TRANS,
	RESTART_META
पूर्ण;
पूर्णांक ocfs2_add_clusters_in_btree(handle_t *handle,
				काष्ठा ocfs2_extent_tree *et,
				u32 *logical_offset,
				u32 clusters_to_add,
				पूर्णांक mark_unwritten,
				काष्ठा ocfs2_alloc_context *data_ac,
				काष्ठा ocfs2_alloc_context *meta_ac,
				क्रमागत ocfs2_alloc_restarted *reason_ret);
काष्ठा ocfs2_cached_dealloc_ctxt;
काष्ठा ocfs2_path;
पूर्णांक ocfs2_split_extent(handle_t *handle,
		       काष्ठा ocfs2_extent_tree *et,
		       काष्ठा ocfs2_path *path,
		       पूर्णांक split_index,
		       काष्ठा ocfs2_extent_rec *split_rec,
		       काष्ठा ocfs2_alloc_context *meta_ac,
		       काष्ठा ocfs2_cached_dealloc_ctxt *dealloc);
पूर्णांक ocfs2_mark_extent_written(काष्ठा inode *inode,
			      काष्ठा ocfs2_extent_tree *et,
			      handle_t *handle, u32 cpos, u32 len, u32 phys,
			      काष्ठा ocfs2_alloc_context *meta_ac,
			      काष्ठा ocfs2_cached_dealloc_ctxt *dealloc);
पूर्णांक ocfs2_change_extent_flag(handle_t *handle,
			     काष्ठा ocfs2_extent_tree *et,
			     u32 cpos, u32 len, u32 phys,
			     काष्ठा ocfs2_alloc_context *meta_ac,
			     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			     पूर्णांक new_flags, पूर्णांक clear_flags);
पूर्णांक ocfs2_हटाओ_extent(handle_t *handle, काष्ठा ocfs2_extent_tree *et,
			u32 cpos, u32 len,
			काष्ठा ocfs2_alloc_context *meta_ac,
			काष्ठा ocfs2_cached_dealloc_ctxt *dealloc);
पूर्णांक ocfs2_हटाओ_btree_range(काष्ठा inode *inode,
			     काष्ठा ocfs2_extent_tree *et,
			     u32 cpos, u32 phys_cpos, u32 len, पूर्णांक flags,
			     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			     u64 refcount_loc, bool refcount_tree_locked);

पूर्णांक ocfs2_num_मुक्त_extents(काष्ठा ocfs2_extent_tree *et);

/*
 * how many new metadata chunks would an allocation need at maximum?
 *
 * Please note that the caller must make sure that root_el is the root
 * of extent tree. So क्रम an inode, it should be &fe->id2.i_list. Otherwise
 * the result may be wrong.
 */
अटल अंतरभूत पूर्णांक ocfs2_extend_meta_needed(काष्ठा ocfs2_extent_list *root_el)
अणु
	/*
	 * Rather than करो all the work of determining how much we need
	 * (involves a ton of पढ़ोs and locks), just ask क्रम the
	 * maximal limit.  That's a tree depth shअगरt.  So, one block क्रम
	 * level of the tree (current l_tree_depth), one block क्रम the
	 * new tree_depth==0 extent_block, and one block at the new
	 * top-of-the tree.
	 */
	वापस le16_to_cpu(root_el->l_tree_depth) + 2;
पूर्ण

व्योम ocfs2_dinode_new_extent_list(काष्ठा inode *inode, काष्ठा ocfs2_dinode *di);
व्योम ocfs2_set_inode_data_अंतरभूत(काष्ठा inode *inode, काष्ठा ocfs2_dinode *di);
पूर्णांक ocfs2_convert_अंतरभूत_data_to_extents(काष्ठा inode *inode,
					 काष्ठा buffer_head *di_bh);

पूर्णांक ocfs2_truncate_log_init(काष्ठा ocfs2_super *osb);
व्योम ocfs2_truncate_log_shutकरोwn(काष्ठा ocfs2_super *osb);
व्योम ocfs2_schedule_truncate_log_flush(काष्ठा ocfs2_super *osb,
				       पूर्णांक cancel);
पूर्णांक ocfs2_flush_truncate_log(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_begin_truncate_log_recovery(काष्ठा ocfs2_super *osb,
				      पूर्णांक slot_num,
				      काष्ठा ocfs2_dinode **tl_copy);
पूर्णांक ocfs2_complete_truncate_log_recovery(काष्ठा ocfs2_super *osb,
					 काष्ठा ocfs2_dinode *tl_copy);
पूर्णांक ocfs2_truncate_log_needs_flush(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_truncate_log_append(काष्ठा ocfs2_super *osb,
			      handle_t *handle,
			      u64 start_blk,
			      अचिन्हित पूर्णांक num_clusters);
पूर्णांक __ocfs2_flush_truncate_log(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_try_to_मुक्त_truncate_log(काष्ठा ocfs2_super *osb,
				   अचिन्हित पूर्णांक needed);

/*
 * Process local काष्ठाure which describes the block unlinks करोne
 * during an operation. This is populated via
 * ocfs2_cache_block_dealloc().
 *
 * ocfs2_run_deallocs() should be called after the potentially
 * de-allocating routines. No journal handles should be खोलो, and most
 * locks should have been dropped.
 */
काष्ठा ocfs2_cached_dealloc_ctxt अणु
	काष्ठा ocfs2_per_slot_मुक्त_list		*c_first_suballocator;
	काष्ठा ocfs2_cached_block_मुक्त 		*c_global_allocator;
पूर्ण;
अटल अंतरभूत व्योम ocfs2_init_dealloc_ctxt(काष्ठा ocfs2_cached_dealloc_ctxt *c)
अणु
	c->c_first_suballocator = शून्य;
	c->c_global_allocator = शून्य;
पूर्ण
पूर्णांक ocfs2_cache_cluster_dealloc(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
				u64 blkno, अचिन्हित पूर्णांक bit);
पूर्णांक ocfs2_cache_block_dealloc(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
			      पूर्णांक type, पूर्णांक slot, u64 suballoc, u64 blkno,
			      अचिन्हित पूर्णांक bit);
अटल अंतरभूत पूर्णांक ocfs2_dealloc_has_cluster(काष्ठा ocfs2_cached_dealloc_ctxt *c)
अणु
	वापस c->c_global_allocator != शून्य;
पूर्ण
पूर्णांक ocfs2_run_deallocs(काष्ठा ocfs2_super *osb,
		       काष्ठा ocfs2_cached_dealloc_ctxt *ctxt);

काष्ठा ocfs2_truncate_context अणु
	काष्ठा ocfs2_cached_dealloc_ctxt tc_dealloc;
	पूर्णांक tc_ext_alloc_locked; /* is it cluster locked? */
	/* these get destroyed once it's passed to ocfs2_commit_truncate. */
	काष्ठा buffer_head *tc_last_eb_bh;
पूर्ण;

पूर्णांक ocfs2_zero_range_क्रम_truncate(काष्ठा inode *inode, handle_t *handle,
				  u64 range_start, u64 range_end);
पूर्णांक ocfs2_commit_truncate(काष्ठा ocfs2_super *osb,
			  काष्ठा inode *inode,
			  काष्ठा buffer_head *di_bh);
पूर्णांक ocfs2_truncate_अंतरभूत(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			  अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end, पूर्णांक trunc);

पूर्णांक ocfs2_find_leaf(काष्ठा ocfs2_caching_info *ci,
		    काष्ठा ocfs2_extent_list *root_el, u32 cpos,
		    काष्ठा buffer_head **leaf_bh);
पूर्णांक ocfs2_search_extent_list(काष्ठा ocfs2_extent_list *el, u32 v_cluster);

पूर्णांक ocfs2_trim_fs(काष्ठा super_block *sb, काष्ठा fstrim_range *range);
/*
 * Helper function to look at the # of clusters in an extent record.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_rec_clusters(काष्ठा ocfs2_extent_list *el,
					      काष्ठा ocfs2_extent_rec *rec)
अणु
	/*
	 * Cluster count in extent records is slightly dअगरferent
	 * between पूर्णांकerior nodes and leaf nodes. This is to support
	 * unwritten extents which need a flags field in leaf node
	 * records, thus shrinking the available space क्रम a clusters
	 * field.
	 */
	अगर (el->l_tree_depth)
		वापस le32_to_cpu(rec->e_पूर्णांक_clusters);
	अन्यथा
		वापस le16_to_cpu(rec->e_leaf_clusters);
पूर्ण

/*
 * This is only valid क्रम leaf nodes, which are the only ones that can
 * have empty extents anyway.
 */
अटल अंतरभूत पूर्णांक ocfs2_is_empty_extent(काष्ठा ocfs2_extent_rec *rec)
अणु
	वापस !rec->e_leaf_clusters;
पूर्ण

पूर्णांक ocfs2_grab_pages(काष्ठा inode *inode, loff_t start, loff_t end,
		     काष्ठा page **pages, पूर्णांक *num);
व्योम ocfs2_map_and_dirty_page(काष्ठा inode *inode, handle_t *handle,
			      अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to,
			      काष्ठा page *page, पूर्णांक zero, u64 *phys);
/*
 * Structures which describe a path through a btree, and functions to
 * manipulate them.
 *
 * The idea here is to be as generic as possible with the tree
 * manipulation code.
 */
काष्ठा ocfs2_path_item अणु
	काष्ठा buffer_head		*bh;
	काष्ठा ocfs2_extent_list	*el;
पूर्ण;

#घोषणा OCFS2_MAX_PATH_DEPTH	5

काष्ठा ocfs2_path अणु
	पूर्णांक				p_tree_depth;
	ocfs2_journal_access_func	p_root_access;
	काष्ठा ocfs2_path_item		p_node[OCFS2_MAX_PATH_DEPTH];
पूर्ण;

#घोषणा path_root_bh(_path) ((_path)->p_node[0].bh)
#घोषणा path_root_el(_path) ((_path)->p_node[0].el)
#घोषणा path_root_access(_path)((_path)->p_root_access)
#घोषणा path_leaf_bh(_path) ((_path)->p_node[(_path)->p_tree_depth].bh)
#घोषणा path_leaf_el(_path) ((_path)->p_node[(_path)->p_tree_depth].el)
#घोषणा path_num_items(_path) ((_path)->p_tree_depth + 1)

व्योम ocfs2_reinit_path(काष्ठा ocfs2_path *path, पूर्णांक keep_root);
व्योम ocfs2_मुक्त_path(काष्ठा ocfs2_path *path);
पूर्णांक ocfs2_find_path(काष्ठा ocfs2_caching_info *ci,
		    काष्ठा ocfs2_path *path,
		    u32 cpos);
काष्ठा ocfs2_path *ocfs2_new_path_from_path(काष्ठा ocfs2_path *path);
काष्ठा ocfs2_path *ocfs2_new_path_from_et(काष्ठा ocfs2_extent_tree *et);
पूर्णांक ocfs2_path_bh_journal_access(handle_t *handle,
				 काष्ठा ocfs2_caching_info *ci,
				 काष्ठा ocfs2_path *path,
				 पूर्णांक idx);
पूर्णांक ocfs2_journal_access_path(काष्ठा ocfs2_caching_info *ci,
			      handle_t *handle,
			      काष्ठा ocfs2_path *path);
पूर्णांक ocfs2_find_cpos_क्रम_right_leaf(काष्ठा super_block *sb,
				   काष्ठा ocfs2_path *path, u32 *cpos);
पूर्णांक ocfs2_find_cpos_क्रम_left_leaf(काष्ठा super_block *sb,
				  काष्ठा ocfs2_path *path, u32 *cpos);
पूर्णांक ocfs2_find_subtree_root(काष्ठा ocfs2_extent_tree *et,
			    काष्ठा ocfs2_path *left,
			    काष्ठा ocfs2_path *right);
#पूर्ण_अगर /* OCFS2_ALLOC_H */
