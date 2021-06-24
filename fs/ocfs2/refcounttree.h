<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * refcounttree.h
 *
 * Copyright (C) 2009 Oracle.  All rights reserved.
 */
#अगर_अघोषित OCFS2_REFCOUNTTREE_H
#घोषणा OCFS2_REFCOUNTTREE_H

काष्ठा ocfs2_refcount_tree अणु
	काष्ठा rb_node rf_node;
	u64 rf_blkno;
	u32 rf_generation;
	काष्ठा kref rf_अ_लोnt;
	काष्ठा rw_semaphore rf_sem;
	काष्ठा ocfs2_lock_res rf_lockres;
	पूर्णांक rf_हटाओd;

	/* the following 4 fields are used by caching_info. */
	spinlock_t rf_lock;
	काष्ठा ocfs2_caching_info rf_ci;
	काष्ठा mutex rf_io_mutex;
	काष्ठा super_block *rf_sb;
पूर्ण;

व्योम ocfs2_purge_refcount_trees(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_lock_refcount_tree(काष्ठा ocfs2_super *osb, u64 ref_blkno, पूर्णांक rw,
			     काष्ठा ocfs2_refcount_tree **tree,
			     काष्ठा buffer_head **ref_bh);
व्योम ocfs2_unlock_refcount_tree(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_refcount_tree *tree,
				पूर्णांक rw);

पूर्णांक ocfs2_decrease_refcount(काष्ठा inode *inode,
			    handle_t *handle, u32 cpos, u32 len,
			    काष्ठा ocfs2_alloc_context *meta_ac,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			    पूर्णांक delete);
पूर्णांक ocfs2_prepare_refcount_change_क्रम_del(काष्ठा inode *inode,
					  u64 refcount_loc,
					  u64 phys_blkno,
					  u32 clusters,
					  पूर्णांक *credits,
					  पूर्णांक *ref_blocks);
पूर्णांक ocfs2_refcount_cow(काष्ठा inode *inode,
		       काष्ठा buffer_head *di_bh,
		       u32 cpos, u32 ग_लिखो_len, u32 max_cpos);

प्रकार पूर्णांक (ocfs2_post_refcount_func)(काष्ठा inode *inode,
				       handle_t *handle,
				       व्योम *para);
/*
 * Some refcount caller need to करो more work after we modअगरy the data b-tree
 * during refcount operation(including CoW and add refcount flag), and make the
 * transaction complete. So it must give us this काष्ठाure so that we can करो it
 * within our transaction.
 *
 */
काष्ठा ocfs2_post_refcount अणु
	पूर्णांक credits;			/* credits it need क्रम journal. */
	ocfs2_post_refcount_func *func;	/* real function. */
	व्योम *para;
पूर्ण;

पूर्णांक ocfs2_refcounted_xattr_delete_need(काष्ठा inode *inode,
				       काष्ठा ocfs2_caching_info *ref_ci,
				       काष्ठा buffer_head *ref_root_bh,
				       काष्ठा ocfs2_xattr_value_root *xv,
				       पूर्णांक *meta_add, पूर्णांक *credits);
पूर्णांक ocfs2_refcount_cow_xattr(काष्ठा inode *inode,
			     काष्ठा ocfs2_dinode *di,
			     काष्ठा ocfs2_xattr_value_buf *vb,
			     काष्ठा ocfs2_refcount_tree *ref_tree,
			     काष्ठा buffer_head *ref_root_bh,
			     u32 cpos, u32 ग_लिखो_len,
			     काष्ठा ocfs2_post_refcount *post);
पूर्णांक ocfs2_duplicate_clusters_by_page(handle_t *handle,
				     काष्ठा inode *inode,
				     u32 cpos, u32 old_cluster,
				     u32 new_cluster, u32 new_len);
पूर्णांक ocfs2_duplicate_clusters_by_jbd(handle_t *handle,
				    काष्ठा inode *inode,
				    u32 cpos, u32 old_cluster,
				    u32 new_cluster, u32 new_len);
पूर्णांक ocfs2_cow_sync_ग_लिखोback(काष्ठा super_block *sb,
			     काष्ठा inode *inode,
			     u32 cpos, u32 num_clusters);
पूर्णांक ocfs2_add_refcount_flag(काष्ठा inode *inode,
			    काष्ठा ocfs2_extent_tree *data_et,
			    काष्ठा ocfs2_caching_info *ref_ci,
			    काष्ठा buffer_head *ref_root_bh,
			    u32 cpos, u32 p_cluster, u32 num_clusters,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			    काष्ठा ocfs2_post_refcount *post);
पूर्णांक ocfs2_हटाओ_refcount_tree(काष्ठा inode *inode, काष्ठा buffer_head *di_bh);
पूर्णांक ocfs2_try_हटाओ_refcount_tree(काष्ठा inode *inode,
				   काष्ठा buffer_head *di_bh);
पूर्णांक ocfs2_increase_refcount(handle_t *handle,
			    काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *ref_root_bh,
			    u64 cpos, u32 len,
			    काष्ठा ocfs2_alloc_context *meta_ac,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc);
पूर्णांक ocfs2_reflink_ioctl(काष्ठा inode *inode,
			स्थिर अक्षर __user *oldname,
			स्थिर अक्षर __user *newname,
			bool preserve);
loff_t ocfs2_reflink_remap_blocks(काष्ठा inode *s_inode,
				  काष्ठा buffer_head *s_bh,
				  loff_t pos_in,
				  काष्ठा inode *t_inode,
				  काष्ठा buffer_head *t_bh,
				  loff_t pos_out,
				  loff_t len);
पूर्णांक ocfs2_reflink_inodes_lock(काष्ठा inode *s_inode,
			      काष्ठा buffer_head **bh1,
			      काष्ठा inode *t_inode,
			      काष्ठा buffer_head **bh2);
व्योम ocfs2_reflink_inodes_unlock(काष्ठा inode *s_inode,
				 काष्ठा buffer_head *s_bh,
				 काष्ठा inode *t_inode,
				 काष्ठा buffer_head *t_bh);
पूर्णांक ocfs2_reflink_update_dest(काष्ठा inode *dest,
			      काष्ठा buffer_head *d_bh,
			      loff_t newlen);

#पूर्ण_अगर /* OCFS2_REFCOUNTTREE_H */
