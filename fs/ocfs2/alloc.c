<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * alloc.c
 *
 * Extent allocs and मुक्तs
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "aops.h"
#समावेश "blockcheck.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "localalloc.h"
#समावेश "suballoc.h"
#समावेश "sysfile.h"
#समावेश "file.h"
#समावेश "super.h"
#समावेश "uptodate.h"
#समावेश "xattr.h"
#समावेश "refcounttree.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

क्रमागत ocfs2_contig_type अणु
	CONTIG_NONE = 0,
	CONTIG_LEFT,
	CONTIG_RIGHT,
	CONTIG_LEFTRIGHT,
पूर्ण;

अटल क्रमागत ocfs2_contig_type
	ocfs2_extent_rec_contig(काष्ठा super_block *sb,
				काष्ठा ocfs2_extent_rec *ext,
				काष्ठा ocfs2_extent_rec *insert_rec);
/*
 * Operations क्रम a specअगरic extent tree type.
 *
 * To implement an on-disk btree (extent tree) type in ocfs2, add
 * an ocfs2_extent_tree_operations काष्ठाure and the matching
 * ocfs2_init_<thingy>_extent_tree() function.  That's pretty much it
 * क्रम the allocation portion of the extent tree.
 */
काष्ठा ocfs2_extent_tree_operations अणु
	/*
	 * last_eb_blk is the block number of the right most leaf extent
	 * block.  Most on-disk काष्ठाures containing an extent tree store
	 * this value क्रम fast access.  The ->eo_set_last_eb_blk() and
	 * ->eo_get_last_eb_blk() operations access this value.  They are
	 *  both required.
	 */
	व्योम (*eo_set_last_eb_blk)(काष्ठा ocfs2_extent_tree *et,
				   u64 blkno);
	u64 (*eo_get_last_eb_blk)(काष्ठा ocfs2_extent_tree *et);

	/*
	 * The on-disk काष्ठाure usually keeps track of how many total
	 * clusters are stored in this extent tree.  This function updates
	 * that value.  new_clusters is the delta, and must be
	 * added to the total.  Required.
	 */
	व्योम (*eo_update_clusters)(काष्ठा ocfs2_extent_tree *et,
				   u32 new_clusters);

	/*
	 * If this extent tree is supported by an extent map, insert
	 * a record पूर्णांकo the map.
	 */
	व्योम (*eo_extent_map_insert)(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_extent_rec *rec);

	/*
	 * If this extent tree is supported by an extent map, truncate the
	 * map to clusters,
	 */
	व्योम (*eo_extent_map_truncate)(काष्ठा ocfs2_extent_tree *et,
				       u32 clusters);

	/*
	 * If ->eo_insert_check() exists, it is called beक्रमe rec is
	 * inserted पूर्णांकo the extent tree.  It is optional.
	 */
	पूर्णांक (*eo_insert_check)(काष्ठा ocfs2_extent_tree *et,
			       काष्ठा ocfs2_extent_rec *rec);
	पूर्णांक (*eo_sanity_check)(काष्ठा ocfs2_extent_tree *et);

	/*
	 * --------------------------------------------------------------
	 * The reमुख्यing are पूर्णांकernal to ocfs2_extent_tree and करोn't have
	 * accessor functions
	 */

	/*
	 * ->eo_fill_root_el() takes et->et_object and sets et->et_root_el.
	 * It is required.
	 */
	व्योम (*eo_fill_root_el)(काष्ठा ocfs2_extent_tree *et);

	/*
	 * ->eo_fill_max_leaf_clusters sets et->et_max_leaf_clusters अगर
	 * it exists.  If it करोes not, et->et_max_leaf_clusters is set
	 * to 0 (unlimited).  Optional.
	 */
	व्योम (*eo_fill_max_leaf_clusters)(काष्ठा ocfs2_extent_tree *et);

	/*
	 * ->eo_extent_contig test whether the 2 ocfs2_extent_rec
	 * are contiguous or not. Optional. Don't need to set it अगर use
	 * ocfs2_extent_rec as the tree leaf.
	 */
	क्रमागत ocfs2_contig_type
		(*eo_extent_contig)(काष्ठा ocfs2_extent_tree *et,
				    काष्ठा ocfs2_extent_rec *ext,
				    काष्ठा ocfs2_extent_rec *insert_rec);
पूर्ण;


/*
 * Pre-declare ocfs2_dinode_et_ops so we can use it as a sanity check
 * in the methods.
 */
अटल u64 ocfs2_dinode_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et);
अटल व्योम ocfs2_dinode_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					 u64 blkno);
अटल व्योम ocfs2_dinode_update_clusters(काष्ठा ocfs2_extent_tree *et,
					 u32 clusters);
अटल व्योम ocfs2_dinode_extent_map_insert(काष्ठा ocfs2_extent_tree *et,
					   काष्ठा ocfs2_extent_rec *rec);
अटल व्योम ocfs2_dinode_extent_map_truncate(काष्ठा ocfs2_extent_tree *et,
					     u32 clusters);
अटल पूर्णांक ocfs2_dinode_insert_check(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_extent_rec *rec);
अटल पूर्णांक ocfs2_dinode_sanity_check(काष्ठा ocfs2_extent_tree *et);
अटल व्योम ocfs2_dinode_fill_root_el(काष्ठा ocfs2_extent_tree *et);

अटल पूर्णांक ocfs2_reuse_blk_from_dealloc(handle_t *handle,
					काष्ठा ocfs2_extent_tree *et,
					काष्ठा buffer_head **new_eb_bh,
					पूर्णांक blk_wanted, पूर्णांक *blk_given);
अटल पूर्णांक ocfs2_is_dealloc_empty(काष्ठा ocfs2_extent_tree *et);

अटल स्थिर काष्ठा ocfs2_extent_tree_operations ocfs2_dinode_et_ops = अणु
	.eo_set_last_eb_blk	= ocfs2_dinode_set_last_eb_blk,
	.eo_get_last_eb_blk	= ocfs2_dinode_get_last_eb_blk,
	.eo_update_clusters	= ocfs2_dinode_update_clusters,
	.eo_extent_map_insert	= ocfs2_dinode_extent_map_insert,
	.eo_extent_map_truncate	= ocfs2_dinode_extent_map_truncate,
	.eo_insert_check	= ocfs2_dinode_insert_check,
	.eo_sanity_check	= ocfs2_dinode_sanity_check,
	.eo_fill_root_el	= ocfs2_dinode_fill_root_el,
पूर्ण;

अटल व्योम ocfs2_dinode_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					 u64 blkno)
अणु
	काष्ठा ocfs2_dinode *di = et->et_object;

	BUG_ON(et->et_ops != &ocfs2_dinode_et_ops);
	di->i_last_eb_blk = cpu_to_le64(blkno);
पूर्ण

अटल u64 ocfs2_dinode_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dinode *di = et->et_object;

	BUG_ON(et->et_ops != &ocfs2_dinode_et_ops);
	वापस le64_to_cpu(di->i_last_eb_blk);
पूर्ण

अटल व्योम ocfs2_dinode_update_clusters(काष्ठा ocfs2_extent_tree *et,
					 u32 clusters)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(et->et_ci);
	काष्ठा ocfs2_dinode *di = et->et_object;

	le32_add_cpu(&di->i_clusters, clusters);
	spin_lock(&oi->ip_lock);
	oi->ip_clusters = le32_to_cpu(di->i_clusters);
	spin_unlock(&oi->ip_lock);
पूर्ण

अटल व्योम ocfs2_dinode_extent_map_insert(काष्ठा ocfs2_extent_tree *et,
					   काष्ठा ocfs2_extent_rec *rec)
अणु
	काष्ठा inode *inode = &cache_info_to_inode(et->et_ci)->vfs_inode;

	ocfs2_extent_map_insert_rec(inode, rec);
पूर्ण

अटल व्योम ocfs2_dinode_extent_map_truncate(काष्ठा ocfs2_extent_tree *et,
					     u32 clusters)
अणु
	काष्ठा inode *inode = &cache_info_to_inode(et->et_ci)->vfs_inode;

	ocfs2_extent_map_trunc(inode, clusters);
पूर्ण

अटल पूर्णांक ocfs2_dinode_insert_check(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_extent_rec *rec)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(et->et_ci);
	काष्ठा ocfs2_super *osb = OCFS2_SB(oi->vfs_inode.i_sb);

	BUG_ON(oi->ip_dyn_features & OCFS2_INLINE_DATA_FL);
	mlog_bug_on_msg(!ocfs2_sparse_alloc(osb) &&
			(oi->ip_clusters != le32_to_cpu(rec->e_cpos)),
			"Device %s, asking for sparse allocation: inode %llu, "
			"cpos %u, clusters %u\n",
			osb->dev_str,
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
			rec->e_cpos, oi->ip_clusters);

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_dinode_sanity_check(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dinode *di = et->et_object;

	BUG_ON(et->et_ops != &ocfs2_dinode_et_ops);
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	वापस 0;
पूर्ण

अटल व्योम ocfs2_dinode_fill_root_el(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dinode *di = et->et_object;

	et->et_root_el = &di->id2.i_list;
पूर्ण


अटल व्योम ocfs2_xattr_value_fill_root_el(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_xattr_value_buf *vb = et->et_object;

	et->et_root_el = &vb->vb_xv->xr_list;
पूर्ण

अटल व्योम ocfs2_xattr_value_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					      u64 blkno)
अणु
	काष्ठा ocfs2_xattr_value_buf *vb = et->et_object;

	vb->vb_xv->xr_last_eb_blk = cpu_to_le64(blkno);
पूर्ण

अटल u64 ocfs2_xattr_value_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_xattr_value_buf *vb = et->et_object;

	वापस le64_to_cpu(vb->vb_xv->xr_last_eb_blk);
पूर्ण

अटल व्योम ocfs2_xattr_value_update_clusters(काष्ठा ocfs2_extent_tree *et,
					      u32 clusters)
अणु
	काष्ठा ocfs2_xattr_value_buf *vb = et->et_object;

	le32_add_cpu(&vb->vb_xv->xr_clusters, clusters);
पूर्ण

अटल स्थिर काष्ठा ocfs2_extent_tree_operations ocfs2_xattr_value_et_ops = अणु
	.eo_set_last_eb_blk	= ocfs2_xattr_value_set_last_eb_blk,
	.eo_get_last_eb_blk	= ocfs2_xattr_value_get_last_eb_blk,
	.eo_update_clusters	= ocfs2_xattr_value_update_clusters,
	.eo_fill_root_el	= ocfs2_xattr_value_fill_root_el,
पूर्ण;

अटल व्योम ocfs2_xattr_tree_fill_root_el(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_xattr_block *xb = et->et_object;

	et->et_root_el = &xb->xb_attrs.xb_root.xt_list;
पूर्ण

अटल व्योम ocfs2_xattr_tree_fill_max_leaf_clusters(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	et->et_max_leaf_clusters =
		ocfs2_clusters_क्रम_bytes(sb, OCFS2_MAX_XATTR_TREE_LEAF_SIZE);
पूर्ण

अटल व्योम ocfs2_xattr_tree_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					     u64 blkno)
अणु
	काष्ठा ocfs2_xattr_block *xb = et->et_object;
	काष्ठा ocfs2_xattr_tree_root *xt = &xb->xb_attrs.xb_root;

	xt->xt_last_eb_blk = cpu_to_le64(blkno);
पूर्ण

अटल u64 ocfs2_xattr_tree_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_xattr_block *xb = et->et_object;
	काष्ठा ocfs2_xattr_tree_root *xt = &xb->xb_attrs.xb_root;

	वापस le64_to_cpu(xt->xt_last_eb_blk);
पूर्ण

अटल व्योम ocfs2_xattr_tree_update_clusters(काष्ठा ocfs2_extent_tree *et,
					     u32 clusters)
अणु
	काष्ठा ocfs2_xattr_block *xb = et->et_object;

	le32_add_cpu(&xb->xb_attrs.xb_root.xt_clusters, clusters);
पूर्ण

अटल स्थिर काष्ठा ocfs2_extent_tree_operations ocfs2_xattr_tree_et_ops = अणु
	.eo_set_last_eb_blk	= ocfs2_xattr_tree_set_last_eb_blk,
	.eo_get_last_eb_blk	= ocfs2_xattr_tree_get_last_eb_blk,
	.eo_update_clusters	= ocfs2_xattr_tree_update_clusters,
	.eo_fill_root_el	= ocfs2_xattr_tree_fill_root_el,
	.eo_fill_max_leaf_clusters = ocfs2_xattr_tree_fill_max_leaf_clusters,
पूर्ण;

अटल व्योम ocfs2_dx_root_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					  u64 blkno)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root = et->et_object;

	dx_root->dr_last_eb_blk = cpu_to_le64(blkno);
पूर्ण

अटल u64 ocfs2_dx_root_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root = et->et_object;

	वापस le64_to_cpu(dx_root->dr_last_eb_blk);
पूर्ण

अटल व्योम ocfs2_dx_root_update_clusters(काष्ठा ocfs2_extent_tree *et,
					  u32 clusters)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root = et->et_object;

	le32_add_cpu(&dx_root->dr_clusters, clusters);
पूर्ण

अटल पूर्णांक ocfs2_dx_root_sanity_check(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root = et->et_object;

	BUG_ON(!OCFS2_IS_VALID_DX_ROOT(dx_root));

	वापस 0;
पूर्ण

अटल व्योम ocfs2_dx_root_fill_root_el(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root = et->et_object;

	et->et_root_el = &dx_root->dr_list;
पूर्ण

अटल स्थिर काष्ठा ocfs2_extent_tree_operations ocfs2_dx_root_et_ops = अणु
	.eo_set_last_eb_blk	= ocfs2_dx_root_set_last_eb_blk,
	.eo_get_last_eb_blk	= ocfs2_dx_root_get_last_eb_blk,
	.eo_update_clusters	= ocfs2_dx_root_update_clusters,
	.eo_sanity_check	= ocfs2_dx_root_sanity_check,
	.eo_fill_root_el	= ocfs2_dx_root_fill_root_el,
पूर्ण;

अटल व्योम ocfs2_refcount_tree_fill_root_el(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_refcount_block *rb = et->et_object;

	et->et_root_el = &rb->rf_list;
पूर्ण

अटल व्योम ocfs2_refcount_tree_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
						u64 blkno)
अणु
	काष्ठा ocfs2_refcount_block *rb = et->et_object;

	rb->rf_last_eb_blk = cpu_to_le64(blkno);
पूर्ण

अटल u64 ocfs2_refcount_tree_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_refcount_block *rb = et->et_object;

	वापस le64_to_cpu(rb->rf_last_eb_blk);
पूर्ण

अटल व्योम ocfs2_refcount_tree_update_clusters(काष्ठा ocfs2_extent_tree *et,
						u32 clusters)
अणु
	काष्ठा ocfs2_refcount_block *rb = et->et_object;

	le32_add_cpu(&rb->rf_clusters, clusters);
पूर्ण

अटल क्रमागत ocfs2_contig_type
ocfs2_refcount_tree_extent_contig(काष्ठा ocfs2_extent_tree *et,
				  काष्ठा ocfs2_extent_rec *ext,
				  काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	वापस CONTIG_NONE;
पूर्ण

अटल स्थिर काष्ठा ocfs2_extent_tree_operations ocfs2_refcount_tree_et_ops = अणु
	.eo_set_last_eb_blk	= ocfs2_refcount_tree_set_last_eb_blk,
	.eo_get_last_eb_blk	= ocfs2_refcount_tree_get_last_eb_blk,
	.eo_update_clusters	= ocfs2_refcount_tree_update_clusters,
	.eo_fill_root_el	= ocfs2_refcount_tree_fill_root_el,
	.eo_extent_contig	= ocfs2_refcount_tree_extent_contig,
पूर्ण;

अटल व्योम __ocfs2_init_extent_tree(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *bh,
				     ocfs2_journal_access_func access,
				     व्योम *obj,
				     स्थिर काष्ठा ocfs2_extent_tree_operations *ops)
अणु
	et->et_ops = ops;
	et->et_root_bh = bh;
	et->et_ci = ci;
	et->et_root_journal_access = access;
	अगर (!obj)
		obj = (व्योम *)bh->b_data;
	et->et_object = obj;
	et->et_dealloc = शून्य;

	et->et_ops->eo_fill_root_el(et);
	अगर (!et->et_ops->eo_fill_max_leaf_clusters)
		et->et_max_leaf_clusters = 0;
	अन्यथा
		et->et_ops->eo_fill_max_leaf_clusters(et);
पूर्ण

व्योम ocfs2_init_dinode_extent_tree(काष्ठा ocfs2_extent_tree *et,
				   काष्ठा ocfs2_caching_info *ci,
				   काष्ठा buffer_head *bh)
अणु
	__ocfs2_init_extent_tree(et, ci, bh, ocfs2_journal_access_di,
				 शून्य, &ocfs2_dinode_et_ops);
पूर्ण

व्योम ocfs2_init_xattr_tree_extent_tree(काष्ठा ocfs2_extent_tree *et,
				       काष्ठा ocfs2_caching_info *ci,
				       काष्ठा buffer_head *bh)
अणु
	__ocfs2_init_extent_tree(et, ci, bh, ocfs2_journal_access_xb,
				 शून्य, &ocfs2_xattr_tree_et_ops);
पूर्ण

व्योम ocfs2_init_xattr_value_extent_tree(काष्ठा ocfs2_extent_tree *et,
					काष्ठा ocfs2_caching_info *ci,
					काष्ठा ocfs2_xattr_value_buf *vb)
अणु
	__ocfs2_init_extent_tree(et, ci, vb->vb_bh, vb->vb_access, vb,
				 &ocfs2_xattr_value_et_ops);
पूर्ण

व्योम ocfs2_init_dx_root_extent_tree(काष्ठा ocfs2_extent_tree *et,
				    काष्ठा ocfs2_caching_info *ci,
				    काष्ठा buffer_head *bh)
अणु
	__ocfs2_init_extent_tree(et, ci, bh, ocfs2_journal_access_dr,
				 शून्य, &ocfs2_dx_root_et_ops);
पूर्ण

व्योम ocfs2_init_refcount_extent_tree(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *bh)
अणु
	__ocfs2_init_extent_tree(et, ci, bh, ocfs2_journal_access_rb,
				 शून्य, &ocfs2_refcount_tree_et_ops);
पूर्ण

अटल अंतरभूत व्योम ocfs2_et_set_last_eb_blk(काष्ठा ocfs2_extent_tree *et,
					    u64 new_last_eb_blk)
अणु
	et->et_ops->eo_set_last_eb_blk(et, new_last_eb_blk);
पूर्ण

अटल अंतरभूत u64 ocfs2_et_get_last_eb_blk(काष्ठा ocfs2_extent_tree *et)
अणु
	वापस et->et_ops->eo_get_last_eb_blk(et);
पूर्ण

अटल अंतरभूत व्योम ocfs2_et_update_clusters(काष्ठा ocfs2_extent_tree *et,
					    u32 clusters)
अणु
	et->et_ops->eo_update_clusters(et, clusters);
पूर्ण

अटल अंतरभूत व्योम ocfs2_et_extent_map_insert(काष्ठा ocfs2_extent_tree *et,
					      काष्ठा ocfs2_extent_rec *rec)
अणु
	अगर (et->et_ops->eo_extent_map_insert)
		et->et_ops->eo_extent_map_insert(et, rec);
पूर्ण

अटल अंतरभूत व्योम ocfs2_et_extent_map_truncate(काष्ठा ocfs2_extent_tree *et,
						u32 clusters)
अणु
	अगर (et->et_ops->eo_extent_map_truncate)
		et->et_ops->eo_extent_map_truncate(et, clusters);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_et_root_journal_access(handle_t *handle,
					       काष्ठा ocfs2_extent_tree *et,
					       पूर्णांक type)
अणु
	वापस et->et_root_journal_access(handle, et->et_ci, et->et_root_bh,
					  type);
पूर्ण

अटल अंतरभूत क्रमागत ocfs2_contig_type
	ocfs2_et_extent_contig(काष्ठा ocfs2_extent_tree *et,
			       काष्ठा ocfs2_extent_rec *rec,
			       काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	अगर (et->et_ops->eo_extent_contig)
		वापस et->et_ops->eo_extent_contig(et, rec, insert_rec);

	वापस ocfs2_extent_rec_contig(
				ocfs2_metadata_cache_get_super(et->et_ci),
				rec, insert_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_et_insert_check(काष्ठा ocfs2_extent_tree *et,
					काष्ठा ocfs2_extent_rec *rec)
अणु
	पूर्णांक ret = 0;

	अगर (et->et_ops->eo_insert_check)
		ret = et->et_ops->eo_insert_check(et, rec);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_et_sanity_check(काष्ठा ocfs2_extent_tree *et)
अणु
	पूर्णांक ret = 0;

	अगर (et->et_ops->eo_sanity_check)
		ret = et->et_ops->eo_sanity_check(et);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_cache_extent_block_मुक्त(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
					 काष्ठा ocfs2_extent_block *eb);
अटल व्योम ocfs2_adjust_righपंचांगost_records(handle_t *handle,
					   काष्ठा ocfs2_extent_tree *et,
					   काष्ठा ocfs2_path *path,
					   काष्ठा ocfs2_extent_rec *insert_rec);
/*
 * Reset the actual path elements so that we can re-use the काष्ठाure
 * to build another path. Generally, this involves मुक्तing the buffer
 * heads.
 */
व्योम ocfs2_reinit_path(काष्ठा ocfs2_path *path, पूर्णांक keep_root)
अणु
	पूर्णांक i, start = 0, depth = 0;
	काष्ठा ocfs2_path_item *node;

	अगर (keep_root)
		start = 1;

	क्रम(i = start; i < path_num_items(path); i++) अणु
		node = &path->p_node[i];

		brअन्यथा(node->bh);
		node->bh = शून्य;
		node->el = शून्य;
	पूर्ण

	/*
	 * Tree depth may change during truncate, or insert. If we're
	 * keeping the root extent list, then make sure that our path
	 * काष्ठाure reflects the proper depth.
	 */
	अगर (keep_root)
		depth = le16_to_cpu(path_root_el(path)->l_tree_depth);
	अन्यथा
		path_root_access(path) = शून्य;

	path->p_tree_depth = depth;
पूर्ण

व्योम ocfs2_मुक्त_path(काष्ठा ocfs2_path *path)
अणु
	अगर (path) अणु
		ocfs2_reinit_path(path, 0);
		kमुक्त(path);
	पूर्ण
पूर्ण

/*
 * All the elements of src पूर्णांकo dest. After this call, src could be मुक्तd
 * without affecting dest.
 *
 * Both paths should have the same root. Any non-root elements of dest
 * will be मुक्तd.
 */
अटल व्योम ocfs2_cp_path(काष्ठा ocfs2_path *dest, काष्ठा ocfs2_path *src)
अणु
	पूर्णांक i;

	BUG_ON(path_root_bh(dest) != path_root_bh(src));
	BUG_ON(path_root_el(dest) != path_root_el(src));
	BUG_ON(path_root_access(dest) != path_root_access(src));

	ocfs2_reinit_path(dest, 1);

	क्रम(i = 1; i < OCFS2_MAX_PATH_DEPTH; i++) अणु
		dest->p_node[i].bh = src->p_node[i].bh;
		dest->p_node[i].el = src->p_node[i].el;

		अगर (dest->p_node[i].bh)
			get_bh(dest->p_node[i].bh);
	पूर्ण
पूर्ण

/*
 * Make the *dest path the same as src and re-initialize src path to
 * have a root only.
 */
अटल व्योम ocfs2_mv_path(काष्ठा ocfs2_path *dest, काष्ठा ocfs2_path *src)
अणु
	पूर्णांक i;

	BUG_ON(path_root_bh(dest) != path_root_bh(src));
	BUG_ON(path_root_access(dest) != path_root_access(src));

	क्रम(i = 1; i < OCFS2_MAX_PATH_DEPTH; i++) अणु
		brअन्यथा(dest->p_node[i].bh);

		dest->p_node[i].bh = src->p_node[i].bh;
		dest->p_node[i].el = src->p_node[i].el;

		src->p_node[i].bh = शून्य;
		src->p_node[i].el = शून्य;
	पूर्ण
पूर्ण

/*
 * Insert an extent block at given index.
 *
 * This will not take an additional reference on eb_bh.
 */
अटल अंतरभूत व्योम ocfs2_path_insert_eb(काष्ठा ocfs2_path *path, पूर्णांक index,
					काष्ठा buffer_head *eb_bh)
अणु
	काष्ठा ocfs2_extent_block *eb = (काष्ठा ocfs2_extent_block *)eb_bh->b_data;

	/*
	 * Right now, no root bh is an extent block, so this helps
	 * catch code errors with dinode trees. The निश्चितion can be
	 * safely हटाओd अगर we ever need to insert extent block
	 * काष्ठाures at the root.
	 */
	BUG_ON(index == 0);

	path->p_node[index].bh = eb_bh;
	path->p_node[index].el = &eb->h_list;
पूर्ण

अटल काष्ठा ocfs2_path *ocfs2_new_path(काष्ठा buffer_head *root_bh,
					 काष्ठा ocfs2_extent_list *root_el,
					 ocfs2_journal_access_func access)
अणु
	काष्ठा ocfs2_path *path;

	BUG_ON(le16_to_cpu(root_el->l_tree_depth) >= OCFS2_MAX_PATH_DEPTH);

	path = kzalloc(माप(*path), GFP_NOFS);
	अगर (path) अणु
		path->p_tree_depth = le16_to_cpu(root_el->l_tree_depth);
		get_bh(root_bh);
		path_root_bh(path) = root_bh;
		path_root_el(path) = root_el;
		path_root_access(path) = access;
	पूर्ण

	वापस path;
पूर्ण

काष्ठा ocfs2_path *ocfs2_new_path_from_path(काष्ठा ocfs2_path *path)
अणु
	वापस ocfs2_new_path(path_root_bh(path), path_root_el(path),
			      path_root_access(path));
पूर्ण

काष्ठा ocfs2_path *ocfs2_new_path_from_et(काष्ठा ocfs2_extent_tree *et)
अणु
	वापस ocfs2_new_path(et->et_root_bh, et->et_root_el,
			      et->et_root_journal_access);
पूर्ण

/*
 * Journal the buffer at depth idx.  All idx>0 are extent_blocks,
 * otherwise it's the root_access function.
 *
 * I करोn't like the way this function's name looks next to
 * ocfs2_journal_access_path(), but I करोn't have a better one.
 */
पूर्णांक ocfs2_path_bh_journal_access(handle_t *handle,
				 काष्ठा ocfs2_caching_info *ci,
				 काष्ठा ocfs2_path *path,
				 पूर्णांक idx)
अणु
	ocfs2_journal_access_func access = path_root_access(path);

	अगर (!access)
		access = ocfs2_journal_access;

	अगर (idx)
		access = ocfs2_journal_access_eb;

	वापस access(handle, ci, path->p_node[idx].bh,
		      OCFS2_JOURNAL_ACCESS_WRITE);
पूर्ण

/*
 * Convenience function to journal all components in a path.
 */
पूर्णांक ocfs2_journal_access_path(काष्ठा ocfs2_caching_info *ci,
			      handle_t *handle,
			      काष्ठा ocfs2_path *path)
अणु
	पूर्णांक i, ret = 0;

	अगर (!path)
		जाओ out;

	क्रम(i = 0; i < path_num_items(path); i++) अणु
		ret = ocfs2_path_bh_journal_access(handle, ci, path, i);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Return the index of the extent record which contains cluster #v_cluster.
 * -1 is वापसed अगर it was not found.
 *
 * Should work fine on पूर्णांकerior and exterior nodes.
 */
पूर्णांक ocfs2_search_extent_list(काष्ठा ocfs2_extent_list *el, u32 v_cluster)
अणु
	पूर्णांक ret = -1;
	पूर्णांक i;
	काष्ठा ocfs2_extent_rec *rec;
	u32 rec_end, rec_start, clusters;

	क्रम(i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++) अणु
		rec = &el->l_recs[i];

		rec_start = le32_to_cpu(rec->e_cpos);
		clusters = ocfs2_rec_clusters(el, rec);

		rec_end = rec_start + clusters;

		अगर (v_cluster >= rec_start && v_cluster < rec_end) अणु
			ret = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * NOTE: ocfs2_block_extent_contig(), ocfs2_extents_adjacent() and
 * ocfs2_extent_rec_contig only work properly against leaf nodes!
 */
अटल पूर्णांक ocfs2_block_extent_contig(काष्ठा super_block *sb,
				     काष्ठा ocfs2_extent_rec *ext,
				     u64 blkno)
अणु
	u64 blk_end = le64_to_cpu(ext->e_blkno);

	blk_end += ocfs2_clusters_to_blocks(sb,
				    le16_to_cpu(ext->e_leaf_clusters));

	वापस blkno == blk_end;
पूर्ण

अटल पूर्णांक ocfs2_extents_adjacent(काष्ठा ocfs2_extent_rec *left,
				  काष्ठा ocfs2_extent_rec *right)
अणु
	u32 left_range;

	left_range = le32_to_cpu(left->e_cpos) +
		le16_to_cpu(left->e_leaf_clusters);

	वापस (left_range == le32_to_cpu(right->e_cpos));
पूर्ण

अटल क्रमागत ocfs2_contig_type
	ocfs2_extent_rec_contig(काष्ठा super_block *sb,
				काष्ठा ocfs2_extent_rec *ext,
				काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	u64 blkno = le64_to_cpu(insert_rec->e_blkno);

	/*
	 * Refuse to coalesce extent records with dअगरferent flag
	 * fields - we करोn't want to mix unwritten extents with user
	 * data.
	 */
	अगर (ext->e_flags != insert_rec->e_flags)
		वापस CONTIG_NONE;

	अगर (ocfs2_extents_adjacent(ext, insert_rec) &&
	    ocfs2_block_extent_contig(sb, ext, blkno))
			वापस CONTIG_RIGHT;

	blkno = le64_to_cpu(ext->e_blkno);
	अगर (ocfs2_extents_adjacent(insert_rec, ext) &&
	    ocfs2_block_extent_contig(sb, insert_rec, blkno))
		वापस CONTIG_LEFT;

	वापस CONTIG_NONE;
पूर्ण

/*
 * NOTE: We can have pretty much any combination of contiguousness and
 * appending.
 *
 * The usefulness of APPEND_TAIL is more in that it lets us know that
 * we'll have to update the path to that leaf.
 */
क्रमागत ocfs2_append_type अणु
	APPEND_NONE = 0,
	APPEND_TAIL,
पूर्ण;

क्रमागत ocfs2_split_type अणु
	SPLIT_NONE = 0,
	SPLIT_LEFT,
	SPLIT_RIGHT,
पूर्ण;

काष्ठा ocfs2_insert_type अणु
	क्रमागत ocfs2_split_type	ins_split;
	क्रमागत ocfs2_append_type	ins_appending;
	क्रमागत ocfs2_contig_type	ins_contig;
	पूर्णांक			ins_contig_index;
	पूर्णांक			ins_tree_depth;
पूर्ण;

काष्ठा ocfs2_merge_ctxt अणु
	क्रमागत ocfs2_contig_type	c_contig_type;
	पूर्णांक			c_has_empty_extent;
	पूर्णांक			c_split_covers_rec;
पूर्ण;

अटल पूर्णांक ocfs2_validate_extent_block(काष्ठा super_block *sb,
				       काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_extent_block *eb =
		(काष्ठा ocfs2_extent_block *)bh->b_data;

	trace_ocfs2_validate_extent_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &eb->h_check);
	अगर (rc) अणु
		mlog(ML_ERROR, "Checksum failed for extent block %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस rc;
	पूर्ण

	/*
	 * Errors after here are fatal.
	 */

	अगर (!OCFS2_IS_VALID_EXTENT_BLOCK(eb)) अणु
		rc = ocfs2_error(sb,
				 "Extent block #%llu has bad signature %.*s\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
				 eb->h_signature);
		जाओ bail;
	पूर्ण

	अगर (le64_to_cpu(eb->h_blkno) != bh->b_blocknr) अणु
		rc = ocfs2_error(sb,
				 "Extent block #%llu has an invalid h_blkno of %llu\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(eb->h_blkno));
		जाओ bail;
	पूर्ण

	अगर (le32_to_cpu(eb->h_fs_generation) != OCFS2_SB(sb)->fs_generation)
		rc = ocfs2_error(sb,
				 "Extent block #%llu has an invalid h_fs_generation of #%u\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 le32_to_cpu(eb->h_fs_generation));
bail:
	वापस rc;
पूर्ण

पूर्णांक ocfs2_पढ़ो_extent_block(काष्ठा ocfs2_caching_info *ci, u64 eb_blkno,
			    काष्ठा buffer_head **bh)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_block(ci, eb_blkno, &पंचांगp,
			      ocfs2_validate_extent_block);

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण


/*
 * How many मुक्त extents have we got beक्रमe we need more meta data?
 */
पूर्णांक ocfs2_num_मुक्त_extents(काष्ठा ocfs2_extent_tree *et)
अणु
	पूर्णांक retval;
	काष्ठा ocfs2_extent_list *el = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा buffer_head *eb_bh = शून्य;
	u64 last_eb_blk = 0;

	el = et->et_root_el;
	last_eb_blk = ocfs2_et_get_last_eb_blk(et);

	अगर (last_eb_blk) अणु
		retval = ocfs2_पढ़ो_extent_block(et->et_ci, last_eb_blk,
						 &eb_bh);
		अगर (retval < 0) अणु
			mlog_त्रुटि_सं(retval);
			जाओ bail;
		पूर्ण
		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;
	पूर्ण

	BUG_ON(el->l_tree_depth != 0);

	retval = le16_to_cpu(el->l_count) - le16_to_cpu(el->l_next_मुक्त_rec);
bail:
	brअन्यथा(eb_bh);

	trace_ocfs2_num_मुक्त_extents(retval);
	वापस retval;
पूर्ण

/* expects array to alपढ़ोy be allocated
 *
 * sets h_signature, h_blkno, h_suballoc_bit, h_suballoc_slot, and
 * l_count क्रम you
 */
अटल पूर्णांक ocfs2_create_new_meta_bhs(handle_t *handle,
				     काष्ठा ocfs2_extent_tree *et,
				     पूर्णांक wanted,
				     काष्ठा ocfs2_alloc_context *meta_ac,
				     काष्ठा buffer_head *bhs[])
अणु
	पूर्णांक count, status, i;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, first_blkno;
	काष्ठा ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(et->et_ci));
	काष्ठा ocfs2_extent_block *eb;

	count = 0;
	जबतक (count < wanted) अणु
		status = ocfs2_claim_metadata(handle,
					      meta_ac,
					      wanted - count,
					      &suballoc_loc,
					      &suballoc_bit_start,
					      &num_got,
					      &first_blkno);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		क्रम(i = count;  i < (num_got + count); i++) अणु
			bhs[i] = sb_getblk(osb->sb, first_blkno);
			अगर (bhs[i] == शून्य) अणु
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
			ocfs2_set_new_buffer_uptodate(et->et_ci, bhs[i]);

			status = ocfs2_journal_access_eb(handle, et->et_ci,
							 bhs[i],
							 OCFS2_JOURNAL_ACCESS_CREATE);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण

			स_रखो(bhs[i]->b_data, 0, osb->sb->s_blocksize);
			eb = (काष्ठा ocfs2_extent_block *) bhs[i]->b_data;
			/* Ok, setup the minimal stuff here. */
			म_नकल(eb->h_signature, OCFS2_EXTENT_BLOCK_SIGNATURE);
			eb->h_blkno = cpu_to_le64(first_blkno);
			eb->h_fs_generation = cpu_to_le32(osb->fs_generation);
			eb->h_suballoc_slot =
				cpu_to_le16(meta_ac->ac_alloc_slot);
			eb->h_suballoc_loc = cpu_to_le64(suballoc_loc);
			eb->h_suballoc_bit = cpu_to_le16(suballoc_bit_start);
			eb->h_list.l_count =
				cpu_to_le16(ocfs2_extent_recs_per_eb(osb->sb));

			suballoc_bit_start++;
			first_blkno++;

			/* We'll also be dirtied by the caller, so
			 * this isn't असलolutely necessary. */
			ocfs2_journal_dirty(handle, bhs[i]);
		पूर्ण

		count += num_got;
	पूर्ण

	status = 0;
bail:
	अगर (status < 0) अणु
		क्रम(i = 0; i < wanted; i++) अणु
			brअन्यथा(bhs[i]);
			bhs[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/*
 * Helper function क्रम ocfs2_add_branch() and ocfs2_shअगरt_tree_depth().
 *
 * Returns the sum of the righपंचांगost extent rec logical offset and
 * cluster count.
 *
 * ocfs2_add_branch() uses this to determine what logical cluster
 * value should be populated पूर्णांकo the lefपंचांगost new branch records.
 *
 * ocfs2_shअगरt_tree_depth() uses this to determine the # clusters
 * value क्रम the new topmost tree record.
 */
अटल अंतरभूत u32 ocfs2_sum_righपंचांगost_rec(काष्ठा ocfs2_extent_list  *el)
अणु
	पूर्णांक i;

	i = le16_to_cpu(el->l_next_मुक्त_rec) - 1;

	वापस le32_to_cpu(el->l_recs[i].e_cpos) +
		ocfs2_rec_clusters(el, &el->l_recs[i]);
पूर्ण

/*
 * Change range of the branches in the right most path according to the leaf
 * extent block's righपंचांगost record.
 */
अटल पूर्णांक ocfs2_adjust_righपंचांगost_branch(handle_t *handle,
					 काष्ठा ocfs2_extent_tree *et)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;

	path = ocfs2_new_path_from_et(et);
	अगर (!path) अणु
		status = -ENOMEM;
		वापस status;
	पूर्ण

	status = ocfs2_find_path(et->et_ci, path, अच_पूर्णांक_उच्च);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	status = ocfs2_extend_trans(handle, path_num_items(path));
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	status = ocfs2_journal_access_path(et->et_ci, handle, path);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	el = path_leaf_el(path);
	rec = &el->l_recs[le16_to_cpu(el->l_next_मुक्त_rec) - 1];

	ocfs2_adjust_righपंचांगost_records(handle, et, path, rec);

out:
	ocfs2_मुक्त_path(path);
	वापस status;
पूर्ण

/*
 * Add an entire tree branch to our inode. eb_bh is the extent block
 * to start at, अगर we करोn't want to start the branch at the root
 * काष्ठाure.
 *
 * last_eb_bh is required as we have to update it's next_leaf poपूर्णांकer
 * क्रम the new last extent block.
 *
 * the new branch will be 'empty' in the sense that every block will
 * contain a single record with cluster count == 0.
 */
अटल पूर्णांक ocfs2_add_branch(handle_t *handle,
			    काष्ठा ocfs2_extent_tree *et,
			    काष्ठा buffer_head *eb_bh,
			    काष्ठा buffer_head **last_eb_bh,
			    काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक status, new_blocks, i, block_given = 0;
	u64 next_blkno, new_last_eb_blk;
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head **new_eb_bhs = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list  *eb_el;
	काष्ठा ocfs2_extent_list  *el;
	u32 new_cpos, root_end;

	BUG_ON(!last_eb_bh || !*last_eb_bh);

	अगर (eb_bh) अणु
		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;
	पूर्ण अन्यथा
		el = et->et_root_el;

	/* we never add a branch to a leaf. */
	BUG_ON(!el->l_tree_depth);

	new_blocks = le16_to_cpu(el->l_tree_depth);

	eb = (काष्ठा ocfs2_extent_block *)(*last_eb_bh)->b_data;
	new_cpos = ocfs2_sum_righपंचांगost_rec(&eb->h_list);
	root_end = ocfs2_sum_righपंचांगost_rec(et->et_root_el);

	/*
	 * If there is a gap beक्रमe the root end and the real end
	 * of the righmost leaf block, we need to हटाओ the gap
	 * between new_cpos and root_end first so that the tree
	 * is consistent after we add a new branch(it will start
	 * from new_cpos).
	 */
	अगर (root_end > new_cpos) अणु
		trace_ocfs2_adjust_righपंचांगost_branch(
			(अचिन्हित दीर्घ दीर्घ)
			ocfs2_metadata_cache_owner(et->et_ci),
			root_end, new_cpos);

		status = ocfs2_adjust_righपंचांगost_branch(handle, et);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* allocate the number of new eb blocks we need */
	new_eb_bhs = kसुस्मृति(new_blocks, माप(काष्ठा buffer_head *),
			     GFP_KERNEL);
	अगर (!new_eb_bhs) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* Firstyly, try to reuse dealloc since we have alपढ़ोy estimated how
	 * many extent blocks we may use.
	 */
	अगर (!ocfs2_is_dealloc_empty(et)) अणु
		status = ocfs2_reuse_blk_from_dealloc(handle, et,
						      new_eb_bhs, new_blocks,
						      &block_given);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	BUG_ON(block_given > new_blocks);

	अगर (block_given < new_blocks) अणु
		BUG_ON(!meta_ac);
		status = ocfs2_create_new_meta_bhs(handle, et,
						   new_blocks - block_given,
						   meta_ac,
						   &new_eb_bhs[block_given]);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Note: new_eb_bhs[new_blocks - 1] is the guy which will be
	 * linked with the rest of the tree.
	 * conversly, new_eb_bhs[0] is the new bottommost leaf.
	 *
	 * when we leave the loop, new_last_eb_blk will poपूर्णांक to the
	 * newest leaf, and next_blkno will poपूर्णांक to the topmost extent
	 * block. */
	next_blkno = new_last_eb_blk = 0;
	क्रम(i = 0; i < new_blocks; i++) अणु
		bh = new_eb_bhs[i];
		eb = (काष्ठा ocfs2_extent_block *) bh->b_data;
		/* ocfs2_create_new_meta_bhs() should create it right! */
		BUG_ON(!OCFS2_IS_VALID_EXTENT_BLOCK(eb));
		eb_el = &eb->h_list;

		status = ocfs2_journal_access_eb(handle, et->et_ci, bh,
						 OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		eb->h_next_leaf_blk = 0;
		eb_el->l_tree_depth = cpu_to_le16(i);
		eb_el->l_next_मुक्त_rec = cpu_to_le16(1);
		/*
		 * This actually counts as an empty extent as
		 * c_clusters == 0
		 */
		eb_el->l_recs[0].e_cpos = cpu_to_le32(new_cpos);
		eb_el->l_recs[0].e_blkno = cpu_to_le64(next_blkno);
		/*
		 * eb_el isn't always an पूर्णांकerior node, but even leaf
		 * nodes want a zero'd flags and reserved field so
		 * this माला_लो the whole 32 bits regardless of use.
		 */
		eb_el->l_recs[0].e_पूर्णांक_clusters = cpu_to_le32(0);
		अगर (!eb_el->l_tree_depth)
			new_last_eb_blk = le64_to_cpu(eb->h_blkno);

		ocfs2_journal_dirty(handle, bh);
		next_blkno = le64_to_cpu(eb->h_blkno);
	पूर्ण

	/* This is a bit hairy. We want to update up to three blocks
	 * here without leaving any of them in an inconsistent state
	 * in हाल of error. We करोn't have to worry about
	 * journal_dirty erroring as it won't unless we've पातed the
	 * handle (in which हाल we would never be here) so reserving
	 * the ग_लिखो with journal_access is all we need to करो. */
	status = ocfs2_journal_access_eb(handle, et->et_ci, *last_eb_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	अगर (eb_bh) अणु
		status = ocfs2_journal_access_eb(handle, et->et_ci, eb_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Link the new branch पूर्णांकo the rest of the tree (el will
	 * either be on the root_bh, or the extent block passed in. */
	i = le16_to_cpu(el->l_next_मुक्त_rec);
	el->l_recs[i].e_blkno = cpu_to_le64(next_blkno);
	el->l_recs[i].e_cpos = cpu_to_le32(new_cpos);
	el->l_recs[i].e_पूर्णांक_clusters = 0;
	le16_add_cpu(&el->l_next_मुक्त_rec, 1);

	/* fe needs a new last extent block poपूर्णांकer, as करोes the
	 * next_leaf on the previously last-extent-block. */
	ocfs2_et_set_last_eb_blk(et, new_last_eb_blk);

	eb = (काष्ठा ocfs2_extent_block *) (*last_eb_bh)->b_data;
	eb->h_next_leaf_blk = cpu_to_le64(new_last_eb_blk);

	ocfs2_journal_dirty(handle, *last_eb_bh);
	ocfs2_journal_dirty(handle, et->et_root_bh);
	अगर (eb_bh)
		ocfs2_journal_dirty(handle, eb_bh);

	/*
	 * Some callers want to track the righपंचांगost leaf so pass it
	 * back here.
	 */
	brअन्यथा(*last_eb_bh);
	get_bh(new_eb_bhs[0]);
	*last_eb_bh = new_eb_bhs[0];

	status = 0;
bail:
	अगर (new_eb_bhs) अणु
		क्रम (i = 0; i < new_blocks; i++)
			brअन्यथा(new_eb_bhs[i]);
		kमुक्त(new_eb_bhs);
	पूर्ण

	वापस status;
पूर्ण

/*
 * adds another level to the allocation tree.
 * वापसs back the new extent block so you can add a branch to it
 * after this call.
 */
अटल पूर्णांक ocfs2_shअगरt_tree_depth(handle_t *handle,
				  काष्ठा ocfs2_extent_tree *et,
				  काष्ठा ocfs2_alloc_context *meta_ac,
				  काष्ठा buffer_head **ret_new_eb_bh)
अणु
	पूर्णांक status, i, block_given = 0;
	u32 new_clusters;
	काष्ठा buffer_head *new_eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list  *root_el;
	काष्ठा ocfs2_extent_list  *eb_el;

	अगर (!ocfs2_is_dealloc_empty(et)) अणु
		status = ocfs2_reuse_blk_from_dealloc(handle, et,
						      &new_eb_bh, 1,
						      &block_given);
	पूर्ण अन्यथा अगर (meta_ac) अणु
		status = ocfs2_create_new_meta_bhs(handle, et, 1, meta_ac,
						   &new_eb_bh);

	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	eb = (काष्ठा ocfs2_extent_block *) new_eb_bh->b_data;
	/* ocfs2_create_new_meta_bhs() should create it right! */
	BUG_ON(!OCFS2_IS_VALID_EXTENT_BLOCK(eb));

	eb_el = &eb->h_list;
	root_el = et->et_root_el;

	status = ocfs2_journal_access_eb(handle, et->et_ci, new_eb_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* copy the root extent list data पूर्णांकo the new extent block */
	eb_el->l_tree_depth = root_el->l_tree_depth;
	eb_el->l_next_मुक्त_rec = root_el->l_next_मुक्त_rec;
	क्रम (i = 0; i < le16_to_cpu(root_el->l_next_मुक्त_rec); i++)
		eb_el->l_recs[i] = root_el->l_recs[i];

	ocfs2_journal_dirty(handle, new_eb_bh);

	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	new_clusters = ocfs2_sum_righपंचांगost_rec(eb_el);

	/* update root_bh now */
	le16_add_cpu(&root_el->l_tree_depth, 1);
	root_el->l_recs[0].e_cpos = 0;
	root_el->l_recs[0].e_blkno = eb->h_blkno;
	root_el->l_recs[0].e_पूर्णांक_clusters = cpu_to_le32(new_clusters);
	क्रम (i = 1; i < le16_to_cpu(root_el->l_next_मुक्त_rec); i++)
		स_रखो(&root_el->l_recs[i], 0, माप(काष्ठा ocfs2_extent_rec));
	root_el->l_next_मुक्त_rec = cpu_to_le16(1);

	/* If this is our 1st tree depth shअगरt, then last_eb_blk
	 * becomes the allocated extent block */
	अगर (root_el->l_tree_depth == cpu_to_le16(1))
		ocfs2_et_set_last_eb_blk(et, le64_to_cpu(eb->h_blkno));

	ocfs2_journal_dirty(handle, et->et_root_bh);

	*ret_new_eb_bh = new_eb_bh;
	new_eb_bh = शून्य;
	status = 0;
bail:
	brअन्यथा(new_eb_bh);

	वापस status;
पूर्ण

/*
 * Should only be called when there is no space left in any of the
 * leaf nodes. What we want to करो is find the lowest tree depth
 * non-leaf extent block with room क्रम new records. There are three
 * valid results of this search:
 *
 * 1) a lowest extent block is found, then we pass it back in
 *    *lowest_eb_bh and वापस '0'
 *
 * 2) the search fails to find anything, but the root_el has room. We
 *    pass शून्य back in *lowest_eb_bh, but still वापस '0'
 *
 * 3) the search fails to find anything AND the root_el is full, in
 *    which हाल we वापस > 0
 *
 * वापस status < 0 indicates an error.
 */
अटल पूर्णांक ocfs2_find_branch_target(काष्ठा ocfs2_extent_tree *et,
				    काष्ठा buffer_head **target_bh)
अणु
	पूर्णांक status = 0, i;
	u64 blkno;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list  *el;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा buffer_head *lowest_bh = शून्य;

	*target_bh = शून्य;

	el = et->et_root_el;

	जबतक(le16_to_cpu(el->l_tree_depth) > 1) अणु
		अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0) अणु
			status = ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
					"Owner %llu has empty extent list (next_free_rec == 0)\n",
					(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci));
			जाओ bail;
		पूर्ण
		i = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
		blkno = le64_to_cpu(el->l_recs[i].e_blkno);
		अगर (!blkno) अणु
			status = ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
					"Owner %llu has extent list where extent # %d has no physical block start\n",
					(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci), i);
			जाओ bail;
		पूर्ण

		brअन्यथा(bh);
		bh = शून्य;

		status = ocfs2_पढ़ो_extent_block(et->et_ci, blkno, &bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;

		अगर (le16_to_cpu(el->l_next_मुक्त_rec) <
		    le16_to_cpu(el->l_count)) अणु
			brअन्यथा(lowest_bh);
			lowest_bh = bh;
			get_bh(lowest_bh);
		पूर्ण
	पूर्ण

	/* If we didn't find one and the fe doesn't have any room,
	 * then वापस '1' */
	el = et->et_root_el;
	अगर (!lowest_bh && (el->l_next_मुक्त_rec == el->l_count))
		status = 1;

	*target_bh = lowest_bh;
bail:
	brअन्यथा(bh);

	वापस status;
पूर्ण

/*
 * Grow a b-tree so that it has more records.
 *
 * We might shअगरt the tree depth in which हाल existing paths should
 * be considered invalid.
 *
 * Tree depth after the grow is वापसed via *final_depth.
 *
 * *last_eb_bh will be updated by ocfs2_add_branch().
 */
अटल पूर्णांक ocfs2_grow_tree(handle_t *handle, काष्ठा ocfs2_extent_tree *et,
			   पूर्णांक *final_depth, काष्ठा buffer_head **last_eb_bh,
			   काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret, shअगरt;
	काष्ठा ocfs2_extent_list *el = et->et_root_el;
	पूर्णांक depth = le16_to_cpu(el->l_tree_depth);
	काष्ठा buffer_head *bh = शून्य;

	BUG_ON(meta_ac == शून्य && ocfs2_is_dealloc_empty(et));

	shअगरt = ocfs2_find_branch_target(et, &bh);
	अगर (shअगरt < 0) अणु
		ret = shअगरt;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* We traveled all the way to the bottom of the allocation tree
	 * and didn't find room क्रम any more extents - we need to add
	 * another tree level */
	अगर (shअगरt) अणु
		BUG_ON(bh);
		trace_ocfs2_grow_tree(
			(अचिन्हित दीर्घ दीर्घ)
			ocfs2_metadata_cache_owner(et->et_ci),
			depth);

		/* ocfs2_shअगरt_tree_depth will वापस us a buffer with
		 * the new extent block (so we can pass that to
		 * ocfs2_add_branch). */
		ret = ocfs2_shअगरt_tree_depth(handle, et, meta_ac, &bh);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		depth++;
		अगर (depth == 1) अणु
			/*
			 * Special हाल: we have room now अगर we shअगरted from
			 * tree_depth 0, so no more work needs to be करोne.
			 *
			 * We won't be calling add_branch, so pass
			 * back *last_eb_bh as the new leaf. At depth
			 * zero, it should always be null so there's
			 * no reason to brअन्यथा.
			 */
			BUG_ON(*last_eb_bh);
			get_bh(bh);
			*last_eb_bh = bh;
			जाओ out;
		पूर्ण
	पूर्ण

	/* call ocfs2_add_branch to add the final part of the tree with
	 * the new data. */
	ret = ocfs2_add_branch(handle, et, bh, last_eb_bh,
			       meta_ac);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

out:
	अगर (final_depth)
		*final_depth = depth;
	brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * This function will discard the righपंचांगost extent record.
 */
अटल व्योम ocfs2_shअगरt_records_right(काष्ठा ocfs2_extent_list *el)
अणु
	पूर्णांक next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
	पूर्णांक count = le16_to_cpu(el->l_count);
	अचिन्हित पूर्णांक num_bytes;

	BUG_ON(!next_मुक्त);
	/* This will cause us to go off the end of our extent list. */
	BUG_ON(next_मुक्त >= count);

	num_bytes = माप(काष्ठा ocfs2_extent_rec) * next_मुक्त;

	स_हटाओ(&el->l_recs[1], &el->l_recs[0], num_bytes);
पूर्ण

अटल व्योम ocfs2_rotate_leaf(काष्ठा ocfs2_extent_list *el,
			      काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	पूर्णांक i, insert_index, next_मुक्त, has_empty, num_bytes;
	u32 insert_cpos = le32_to_cpu(insert_rec->e_cpos);
	काष्ठा ocfs2_extent_rec *rec;

	next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
	has_empty = ocfs2_is_empty_extent(&el->l_recs[0]);

	BUG_ON(!next_मुक्त);

	/* The tree code beक्रमe us didn't allow enough room in the leaf. */
	BUG_ON(el->l_next_मुक्त_rec == el->l_count && !has_empty);

	/*
	 * The easiest way to approach this is to just हटाओ the
	 * empty extent and temporarily decrement next_मुक्त.
	 */
	अगर (has_empty) अणु
		/*
		 * If next_मुक्त was 1 (only an empty extent), this
		 * loop won't execute, which is fine. We still want
		 * the decrement above to happen.
		 */
		क्रम(i = 0; i < (next_मुक्त - 1); i++)
			el->l_recs[i] = el->l_recs[i+1];

		next_मुक्त--;
	पूर्ण

	/*
	 * Figure out what the new record index should be.
	 */
	क्रम(i = 0; i < next_मुक्त; i++) अणु
		rec = &el->l_recs[i];

		अगर (insert_cpos < le32_to_cpu(rec->e_cpos))
			अवरोध;
	पूर्ण
	insert_index = i;

	trace_ocfs2_rotate_leaf(insert_cpos, insert_index,
				has_empty, next_मुक्त,
				le16_to_cpu(el->l_count));

	BUG_ON(insert_index < 0);
	BUG_ON(insert_index >= le16_to_cpu(el->l_count));
	BUG_ON(insert_index > next_मुक्त);

	/*
	 * No need to स_हटाओ अगर we're just adding to the tail.
	 */
	अगर (insert_index != next_मुक्त) अणु
		BUG_ON(next_मुक्त >= le16_to_cpu(el->l_count));

		num_bytes = next_मुक्त - insert_index;
		num_bytes *= माप(काष्ठा ocfs2_extent_rec);
		स_हटाओ(&el->l_recs[insert_index + 1],
			&el->l_recs[insert_index],
			num_bytes);
	पूर्ण

	/*
	 * Either we had an empty extent, and need to re-increment or
	 * there was no empty extent on a non full righपंचांगost leaf node,
	 * in which हाल we still need to increment.
	 */
	next_मुक्त++;
	el->l_next_मुक्त_rec = cpu_to_le16(next_मुक्त);
	/*
	 * Make sure none of the math above just messed up our tree.
	 */
	BUG_ON(le16_to_cpu(el->l_next_मुक्त_rec) > le16_to_cpu(el->l_count));

	el->l_recs[insert_index] = *insert_rec;

पूर्ण

अटल व्योम ocfs2_हटाओ_empty_extent(काष्ठा ocfs2_extent_list *el)
अणु
	पूर्णांक size, num_recs = le16_to_cpu(el->l_next_मुक्त_rec);

	BUG_ON(num_recs == 0);

	अगर (ocfs2_is_empty_extent(&el->l_recs[0])) अणु
		num_recs--;
		size = num_recs * माप(काष्ठा ocfs2_extent_rec);
		स_हटाओ(&el->l_recs[0], &el->l_recs[1], size);
		स_रखो(&el->l_recs[num_recs], 0,
		       माप(काष्ठा ocfs2_extent_rec));
		el->l_next_मुक्त_rec = cpu_to_le16(num_recs);
	पूर्ण
पूर्ण

/*
 * Create an empty extent record .
 *
 * l_next_मुक्त_rec may be updated.
 *
 * If an empty extent alपढ़ोy exists करो nothing.
 */
अटल व्योम ocfs2_create_empty_extent(काष्ठा ocfs2_extent_list *el)
अणु
	पूर्णांक next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	अगर (next_मुक्त == 0)
		जाओ set_and_inc;

	अगर (ocfs2_is_empty_extent(&el->l_recs[0]))
		वापस;

	mlog_bug_on_msg(el->l_count == el->l_next_मुक्त_rec,
			"Asked to create an empty extent in a full list:\n"
			"count = %u, tree depth = %u",
			le16_to_cpu(el->l_count),
			le16_to_cpu(el->l_tree_depth));

	ocfs2_shअगरt_records_right(el);

set_and_inc:
	le16_add_cpu(&el->l_next_मुक्त_rec, 1);
	स_रखो(&el->l_recs[0], 0, माप(काष्ठा ocfs2_extent_rec));
पूर्ण

/*
 * For a rotation which involves two leaf nodes, the "root node" is
 * the lowest level tree node which contains a path to both leafs. This
 * resulting set of inक्रमmation can be used to क्रमm a complete "subtree"
 *
 * This function is passed two full paths from the dinode करोwn to a
 * pair of adjacent leaves. It's task is to figure out which path
 * index contains the subtree root - this can be the root index itself
 * in a worst-हाल rotation.
 *
 * The array index of the subtree root is passed back.
 */
पूर्णांक ocfs2_find_subtree_root(काष्ठा ocfs2_extent_tree *et,
			    काष्ठा ocfs2_path *left,
			    काष्ठा ocfs2_path *right)
अणु
	पूर्णांक i = 0;

	/*
	 * Check that the caller passed in two paths from the same tree.
	 */
	BUG_ON(path_root_bh(left) != path_root_bh(right));

	करो अणु
		i++;

		/*
		 * The caller didn't pass two adjacent paths.
		 */
		mlog_bug_on_msg(i > left->p_tree_depth,
				"Owner %llu, left depth %u, right depth %u\n"
				"left leaf blk %llu, right leaf blk %llu\n",
				(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
				left->p_tree_depth, right->p_tree_depth,
				(अचिन्हित दीर्घ दीर्घ)path_leaf_bh(left)->b_blocknr,
				(अचिन्हित दीर्घ दीर्घ)path_leaf_bh(right)->b_blocknr);
	पूर्ण जबतक (left->p_node[i].bh->b_blocknr ==
		 right->p_node[i].bh->b_blocknr);

	वापस i - 1;
पूर्ण

प्रकार व्योम (path_insert_t)(व्योम *, काष्ठा buffer_head *);

/*
 * Traverse a btree path in search of cpos, starting at root_el.
 *
 * This code can be called with a cpos larger than the tree, in which
 * हाल it will वापस the righपंचांगost path.
 */
अटल पूर्णांक __ocfs2_find_path(काष्ठा ocfs2_caching_info *ci,
			     काष्ठा ocfs2_extent_list *root_el, u32 cpos,
			     path_insert_t *func, व्योम *data)
अणु
	पूर्णांक i, ret = 0;
	u32 range;
	u64 blkno;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;

	el = root_el;
	जबतक (el->l_tree_depth) अणु
		अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has empty extent list at depth %u\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
				    le16_to_cpu(el->l_tree_depth));
			ret = -EROFS;
			जाओ out;

		पूर्ण

		क्रम(i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec) - 1; i++) अणु
			rec = &el->l_recs[i];

			/*
			 * In the हाल that cpos is off the allocation
			 * tree, this should just wind up वापसing the
			 * righपंचांगost record.
			 */
			range = le32_to_cpu(rec->e_cpos) +
				ocfs2_rec_clusters(el, rec);
			अगर (cpos >= le32_to_cpu(rec->e_cpos) && cpos < range)
			    अवरोध;
		पूर्ण

		blkno = le64_to_cpu(el->l_recs[i].e_blkno);
		अगर (blkno == 0) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has bad blkno in extent list at depth %u (index %d)\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
				    le16_to_cpu(el->l_tree_depth), i);
			ret = -EROFS;
			जाओ out;
		पूर्ण

		brअन्यथा(bh);
		bh = शून्य;
		ret = ocfs2_पढ़ो_extent_block(ci, blkno, &bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;

		अगर (le16_to_cpu(el->l_next_मुक्त_rec) >
		    le16_to_cpu(el->l_count)) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has bad count in extent list at block %llu (next free=%u, count=%u)\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
				    (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				    le16_to_cpu(el->l_next_मुक्त_rec),
				    le16_to_cpu(el->l_count));
			ret = -EROFS;
			जाओ out;
		पूर्ण

		अगर (func)
			func(data, bh);
	पूर्ण

out:
	/*
	 * Catch any trailing bh that the loop didn't handle.
	 */
	brअन्यथा(bh);

	वापस ret;
पूर्ण

/*
 * Given an initialized path (that is, it has a valid root extent
 * list), this function will traverse the btree in search of the path
 * which would contain cpos.
 *
 * The path traveled is recorded in the path काष्ठाure.
 *
 * Note that this will not करो any comparisons on leaf node extent
 * records, so it will work fine in the हाल that we just added a tree
 * branch.
 */
काष्ठा find_path_data अणु
	पूर्णांक index;
	काष्ठा ocfs2_path *path;
पूर्ण;
अटल व्योम find_path_ins(व्योम *data, काष्ठा buffer_head *bh)
अणु
	काष्ठा find_path_data *fp = data;

	get_bh(bh);
	ocfs2_path_insert_eb(fp->path, fp->index, bh);
	fp->index++;
पूर्ण
पूर्णांक ocfs2_find_path(काष्ठा ocfs2_caching_info *ci,
		    काष्ठा ocfs2_path *path, u32 cpos)
अणु
	काष्ठा find_path_data data;

	data.index = 1;
	data.path = path;
	वापस __ocfs2_find_path(ci, path_root_el(path), cpos,
				 find_path_ins, &data);
पूर्ण

अटल व्योम find_leaf_ins(व्योम *data, काष्ठा buffer_head *bh)
अणु
	काष्ठा ocfs2_extent_block *eb =(काष्ठा ocfs2_extent_block *)bh->b_data;
	काष्ठा ocfs2_extent_list *el = &eb->h_list;
	काष्ठा buffer_head **ret = data;

	/* We want to retain only the leaf block. */
	अगर (le16_to_cpu(el->l_tree_depth) == 0) अणु
		get_bh(bh);
		*ret = bh;
	पूर्ण
पूर्ण
/*
 * Find the leaf block in the tree which would contain cpos. No
 * checking of the actual leaf is करोne.
 *
 * Some paths want to call this instead of allocating a path काष्ठाure
 * and calling ocfs2_find_path().
 *
 * This function करोesn't handle non btree extent lists.
 */
पूर्णांक ocfs2_find_leaf(काष्ठा ocfs2_caching_info *ci,
		    काष्ठा ocfs2_extent_list *root_el, u32 cpos,
		    काष्ठा buffer_head **leaf_bh)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *bh = शून्य;

	ret = __ocfs2_find_path(ci, root_el, cpos, find_leaf_ins, &bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*leaf_bh = bh;
out:
	वापस ret;
पूर्ण

/*
 * Adjust the adjacent records (left_rec, right_rec) involved in a rotation.
 *
 * Basically, we've moved stuff around at the bottom of the tree and
 * we need to fix up the extent records above the changes to reflect
 * the new changes.
 *
 * left_rec: the record on the left.
 * right_rec: the record to the right of left_rec
 * right_child_el: is the child list poपूर्णांकed to by right_rec
 *
 * By definition, this only works on पूर्णांकerior nodes.
 */
अटल व्योम ocfs2_adjust_adjacent_records(काष्ठा ocfs2_extent_rec *left_rec,
				  काष्ठा ocfs2_extent_rec *right_rec,
				  काष्ठा ocfs2_extent_list *right_child_el)
अणु
	u32 left_clusters, right_end;

	/*
	 * Interior nodes never have holes. Their cpos is the cpos of
	 * the lefपंचांगost record in their child list. Their cluster
	 * count covers the full theoretical range of their child list
	 * - the range between their cpos and the cpos of the record
	 * immediately to their right.
	 */
	left_clusters = le32_to_cpu(right_child_el->l_recs[0].e_cpos);
	अगर (!ocfs2_rec_clusters(right_child_el, &right_child_el->l_recs[0])) अणु
		BUG_ON(right_child_el->l_tree_depth);
		BUG_ON(le16_to_cpu(right_child_el->l_next_मुक्त_rec) <= 1);
		left_clusters = le32_to_cpu(right_child_el->l_recs[1].e_cpos);
	पूर्ण
	left_clusters -= le32_to_cpu(left_rec->e_cpos);
	left_rec->e_पूर्णांक_clusters = cpu_to_le32(left_clusters);

	/*
	 * Calculate the righपंचांगost cluster count boundary beक्रमe
	 * moving cpos - we will need to adjust clusters after
	 * updating e_cpos to keep the same highest cluster count.
	 */
	right_end = le32_to_cpu(right_rec->e_cpos);
	right_end += le32_to_cpu(right_rec->e_पूर्णांक_clusters);

	right_rec->e_cpos = left_rec->e_cpos;
	le32_add_cpu(&right_rec->e_cpos, left_clusters);

	right_end -= le32_to_cpu(right_rec->e_cpos);
	right_rec->e_पूर्णांक_clusters = cpu_to_le32(right_end);
पूर्ण

/*
 * Adjust the adjacent root node records involved in a
 * rotation. left_el_blkno is passed in as a key so that we can easily
 * find it's index in the root list.
 */
अटल व्योम ocfs2_adjust_root_records(काष्ठा ocfs2_extent_list *root_el,
				      काष्ठा ocfs2_extent_list *left_el,
				      काष्ठा ocfs2_extent_list *right_el,
				      u64 left_el_blkno)
अणु
	पूर्णांक i;

	BUG_ON(le16_to_cpu(root_el->l_tree_depth) <=
	       le16_to_cpu(left_el->l_tree_depth));

	क्रम(i = 0; i < le16_to_cpu(root_el->l_next_मुक्त_rec) - 1; i++) अणु
		अगर (le64_to_cpu(root_el->l_recs[i].e_blkno) == left_el_blkno)
			अवरोध;
	पूर्ण

	/*
	 * The path walking code should have never वापसed a root and
	 * two paths which are not adjacent.
	 */
	BUG_ON(i >= (le16_to_cpu(root_el->l_next_मुक्त_rec) - 1));

	ocfs2_adjust_adjacent_records(&root_el->l_recs[i],
				      &root_el->l_recs[i + 1], right_el);
पूर्ण

/*
 * We've changed a leaf block (in right_path) and need to reflect that
 * change back up the subtree.
 *
 * This happens in multiple places:
 *   - When we've moved an extent record from the left path leaf to the right
 *     path leaf to make room क्रम an empty extent in the left path leaf.
 *   - When our insert पूर्णांकo the right path leaf is at the lefपंचांगost edge
 *     and requires an update of the path immediately to it's left. This
 *     can occur at the end of some types of rotation and appending inserts.
 *   - When we've adjusted the last extent record in the left path leaf and the
 *     1st extent record in the right path leaf during cross extent block merge.
 */
अटल व्योम ocfs2_complete_edge_insert(handle_t *handle,
				       काष्ठा ocfs2_path *left_path,
				       काष्ठा ocfs2_path *right_path,
				       पूर्णांक subtree_index)
अणु
	पूर्णांक i, idx;
	काष्ठा ocfs2_extent_list *el, *left_el, *right_el;
	काष्ठा ocfs2_extent_rec *left_rec, *right_rec;
	काष्ठा buffer_head *root_bh = left_path->p_node[subtree_index].bh;

	/*
	 * Update the counts and position values within all the
	 * पूर्णांकerior nodes to reflect the leaf rotation we just did.
	 *
	 * The root node is handled below the loop.
	 *
	 * We begin the loop with right_el and left_el poपूर्णांकing to the
	 * leaf lists and work our way up.
	 *
	 * NOTE: within this loop, left_el and right_el always refer
	 * to the *child* lists.
	 */
	left_el = path_leaf_el(left_path);
	right_el = path_leaf_el(right_path);
	क्रम(i = left_path->p_tree_depth - 1; i > subtree_index; i--) अणु
		trace_ocfs2_complete_edge_insert(i);

		/*
		 * One nice property of knowing that all of these
		 * nodes are below the root is that we only deal with
		 * the lefपंचांगost right node record and the righपंचांगost
		 * left node record.
		 */
		el = left_path->p_node[i].el;
		idx = le16_to_cpu(left_el->l_next_मुक्त_rec) - 1;
		left_rec = &el->l_recs[idx];

		el = right_path->p_node[i].el;
		right_rec = &el->l_recs[0];

		ocfs2_adjust_adjacent_records(left_rec, right_rec, right_el);

		ocfs2_journal_dirty(handle, left_path->p_node[i].bh);
		ocfs2_journal_dirty(handle, right_path->p_node[i].bh);

		/*
		 * Setup our list poपूर्णांकers now so that the current
		 * parents become children in the next iteration.
		 */
		left_el = left_path->p_node[i].el;
		right_el = right_path->p_node[i].el;
	पूर्ण

	/*
	 * At the root node, adjust the two adjacent records which
	 * begin our path to the leaves.
	 */

	el = left_path->p_node[subtree_index].el;
	left_el = left_path->p_node[subtree_index + 1].el;
	right_el = right_path->p_node[subtree_index + 1].el;

	ocfs2_adjust_root_records(el, left_el, right_el,
				  left_path->p_node[subtree_index + 1].bh->b_blocknr);

	root_bh = left_path->p_node[subtree_index].bh;

	ocfs2_journal_dirty(handle, root_bh);
पूर्ण

अटल पूर्णांक ocfs2_rotate_subtree_right(handle_t *handle,
				      काष्ठा ocfs2_extent_tree *et,
				      काष्ठा ocfs2_path *left_path,
				      काष्ठा ocfs2_path *right_path,
				      पूर्णांक subtree_index)
अणु
	पूर्णांक ret, i;
	काष्ठा buffer_head *right_leaf_bh;
	काष्ठा buffer_head *left_leaf_bh = शून्य;
	काष्ठा buffer_head *root_bh;
	काष्ठा ocfs2_extent_list *right_el, *left_el;
	काष्ठा ocfs2_extent_rec move_rec;

	left_leaf_bh = path_leaf_bh(left_path);
	left_el = path_leaf_el(left_path);

	अगर (left_el->l_next_मुक्त_rec != left_el->l_count) अणु
		ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
			    "Inode %llu has non-full interior leaf node %llu (next free = %u)\n",
			    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
			    (अचिन्हित दीर्घ दीर्घ)left_leaf_bh->b_blocknr,
			    le16_to_cpu(left_el->l_next_मुक्त_rec));
		वापस -EROFS;
	पूर्ण

	/*
	 * This extent block may alपढ़ोy have an empty record, so we
	 * वापस early अगर so.
	 */
	अगर (ocfs2_is_empty_extent(&left_el->l_recs[0]))
		वापस 0;

	root_bh = left_path->p_node[subtree_index].bh;
	BUG_ON(root_bh != right_path->p_node[subtree_index].bh);

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, right_path,
					   subtree_index);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	क्रम(i = subtree_index + 1; i < path_num_items(right_path); i++) अणु
		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   right_path, i);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   left_path, i);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	right_leaf_bh = path_leaf_bh(right_path);
	right_el = path_leaf_el(right_path);

	/* This is a code error, not a disk corruption. */
	mlog_bug_on_msg(!right_el->l_next_मुक्त_rec, "Inode %llu: Rotate fails "
			"because rightmost leaf block %llu is empty\n",
			(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
			(अचिन्हित दीर्घ दीर्घ)right_leaf_bh->b_blocknr);

	ocfs2_create_empty_extent(right_el);

	ocfs2_journal_dirty(handle, right_leaf_bh);

	/* Do the copy now. */
	i = le16_to_cpu(left_el->l_next_मुक्त_rec) - 1;
	move_rec = left_el->l_recs[i];
	right_el->l_recs[0] = move_rec;

	/*
	 * Clear out the record we just copied and shअगरt everything
	 * over, leaving an empty extent in the left leaf.
	 *
	 * We temporarily subtract from next_मुक्त_rec so that the
	 * shअगरt will lose the tail record (which is now defunct).
	 */
	le16_add_cpu(&left_el->l_next_मुक्त_rec, -1);
	ocfs2_shअगरt_records_right(left_el);
	स_रखो(&left_el->l_recs[0], 0, माप(काष्ठा ocfs2_extent_rec));
	le16_add_cpu(&left_el->l_next_मुक्त_rec, 1);

	ocfs2_journal_dirty(handle, left_leaf_bh);

	ocfs2_complete_edge_insert(handle, left_path, right_path,
				   subtree_index);

out:
	वापस ret;
पूर्ण

/*
 * Given a full path, determine what cpos value would वापस us a path
 * containing the leaf immediately to the left of the current one.
 *
 * Will वापस zero अगर the path passed in is alपढ़ोy the lefपंचांगost path.
 */
पूर्णांक ocfs2_find_cpos_क्रम_left_leaf(काष्ठा super_block *sb,
				  काष्ठा ocfs2_path *path, u32 *cpos)
अणु
	पूर्णांक i, j, ret = 0;
	u64 blkno;
	काष्ठा ocfs2_extent_list *el;

	BUG_ON(path->p_tree_depth == 0);

	*cpos = 0;

	blkno = path_leaf_bh(path)->b_blocknr;

	/* Start at the tree node just above the leaf and work our way up. */
	i = path->p_tree_depth - 1;
	जबतक (i >= 0) अणु
		el = path->p_node[i].el;

		/*
		 * Find the extent record just beक्रमe the one in our
		 * path.
		 */
		क्रम(j = 0; j < le16_to_cpu(el->l_next_मुक्त_rec); j++) अणु
			अगर (le64_to_cpu(el->l_recs[j].e_blkno) == blkno) अणु
				अगर (j == 0) अणु
					अगर (i == 0) अणु
						/*
						 * We've determined that the
						 * path specअगरied is alपढ़ोy
						 * the lefपंचांगost one - वापस a
						 * cpos of zero.
						 */
						जाओ out;
					पूर्ण
					/*
					 * The lefपंचांगost record poपूर्णांकs to our
					 * leaf - we need to travel up the
					 * tree one level.
					 */
					जाओ next_node;
				पूर्ण

				*cpos = le32_to_cpu(el->l_recs[j - 1].e_cpos);
				*cpos = *cpos + ocfs2_rec_clusters(el,
							   &el->l_recs[j - 1]);
				*cpos = *cpos - 1;
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * If we got here, we never found a valid node where
		 * the tree indicated one should be.
		 */
		ocfs2_error(sb, "Invalid extent tree at extent block %llu\n",
			    (अचिन्हित दीर्घ दीर्घ)blkno);
		ret = -EROFS;
		जाओ out;

next_node:
		blkno = path->p_node[i].bh->b_blocknr;
		i--;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Extend the transaction by enough credits to complete the rotation,
 * and still leave at least the original number of credits allocated
 * to this transaction.
 */
अटल पूर्णांक ocfs2_extend_rotate_transaction(handle_t *handle, पूर्णांक subtree_depth,
					   पूर्णांक op_credits,
					   काष्ठा ocfs2_path *path)
अणु
	पूर्णांक ret = 0;
	पूर्णांक credits = (path->p_tree_depth - subtree_depth) * 2 + 1 + op_credits;

	अगर (jbd2_handle_buffer_credits(handle) < credits)
		ret = ocfs2_extend_trans(handle,
				credits - jbd2_handle_buffer_credits(handle));

	वापस ret;
पूर्ण

/*
 * Trap the हाल where we're inserting पूर्णांकo the theoretical range past
 * the _actual_ left leaf range. Otherwise, we'll rotate a record
 * whose cpos is less than ours पूर्णांकo the right leaf.
 *
 * It's only necessary to look at the righपंचांगost record of the left
 * leaf because the logic that calls us should ensure that the
 * theoretical ranges in the path components above the leaves are
 * correct.
 */
अटल पूर्णांक ocfs2_rotate_requires_path_adjusपंचांगent(काष्ठा ocfs2_path *left_path,
						 u32 insert_cpos)
अणु
	काष्ठा ocfs2_extent_list *left_el;
	काष्ठा ocfs2_extent_rec *rec;
	पूर्णांक next_मुक्त;

	left_el = path_leaf_el(left_path);
	next_मुक्त = le16_to_cpu(left_el->l_next_मुक्त_rec);
	rec = &left_el->l_recs[next_मुक्त - 1];

	अगर (insert_cpos > le32_to_cpu(rec->e_cpos))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_lefपंचांगost_rec_contains(काष्ठा ocfs2_extent_list *el, u32 cpos)
अणु
	पूर्णांक next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
	अचिन्हित पूर्णांक range;
	काष्ठा ocfs2_extent_rec *rec;

	अगर (next_मुक्त == 0)
		वापस 0;

	rec = &el->l_recs[0];
	अगर (ocfs2_is_empty_extent(rec)) अणु
		/* Empty list. */
		अगर (next_मुक्त == 1)
			वापस 0;
		rec = &el->l_recs[1];
	पूर्ण

	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	अगर (cpos >= le32_to_cpu(rec->e_cpos) && cpos < range)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Rotate all the records in a btree right one record, starting at insert_cpos.
 *
 * The path to the righपंचांगost leaf should be passed in.
 *
 * The array is assumed to be large enough to hold an entire path (tree depth).
 *
 * Upon successful वापस from this function:
 *
 * - The 'right_path' array will contain a path to the leaf block
 *   whose range contains e_cpos.
 * - That leaf block will have a single empty extent in list index 0.
 * - In the हाल that the rotation requires a post-insert update,
 *   *ret_left_path will contain a valid path which can be passed to
 *   ocfs2_insert_path().
 */
अटल पूर्णांक ocfs2_rotate_tree_right(handle_t *handle,
				   काष्ठा ocfs2_extent_tree *et,
				   क्रमागत ocfs2_split_type split,
				   u32 insert_cpos,
				   काष्ठा ocfs2_path *right_path,
				   काष्ठा ocfs2_path **ret_left_path)
अणु
	पूर्णांक ret, start, orig_credits = jbd2_handle_buffer_credits(handle);
	u32 cpos;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);

	*ret_left_path = शून्य;

	left_path = ocfs2_new_path_from_path(right_path);
	अगर (!left_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_cpos_क्रम_left_leaf(sb, right_path, &cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_rotate_tree_right(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		insert_cpos, cpos);

	/*
	 * What we want to करो here is:
	 *
	 * 1) Start with the righपंचांगost path.
	 *
	 * 2) Determine a path to the leaf block directly to the left
	 *    of that leaf.
	 *
	 * 3) Determine the 'subtree root' - the lowest level tree node
	 *    which contains a path to both leaves.
	 *
	 * 4) Rotate the subtree.
	 *
	 * 5) Find the next subtree by considering the left path to be
	 *    the new right path.
	 *
	 * The check at the top of this जबतक loop also accepts
	 * insert_cpos == cpos because cpos is only a _theoretical_
	 * value to get us the left path - insert_cpos might very well
	 * be filling that hole.
	 *
	 * Stop at a cpos of '0' because we either started at the
	 * lefपंचांगost branch (i.e., a tree with one branch and a
	 * rotation inside of it), or we've gone as far as we can in
	 * rotating subtrees.
	 */
	जबतक (cpos && insert_cpos <= cpos) अणु
		trace_ocfs2_rotate_tree_right(
			(अचिन्हित दीर्घ दीर्घ)
			ocfs2_metadata_cache_owner(et->et_ci),
			insert_cpos, cpos);

		ret = ocfs2_find_path(et->et_ci, left_path, cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		mlog_bug_on_msg(path_leaf_bh(left_path) ==
				path_leaf_bh(right_path),
				"Owner %llu: error during insert of %u "
				"(left path cpos %u) results in two identical "
				"paths ending at %llu\n",
				(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
				insert_cpos, cpos,
				(अचिन्हित दीर्घ दीर्घ)
				path_leaf_bh(left_path)->b_blocknr);

		अगर (split == SPLIT_NONE &&
		    ocfs2_rotate_requires_path_adjusपंचांगent(left_path,
							  insert_cpos)) अणु

			/*
			 * We've rotated the tree as much as we
			 * should. The rest is up to
			 * ocfs2_insert_path() to complete, after the
			 * record insertion. We indicate this
			 * situation by वापसing the left path.
			 *
			 * The reason we करोn't adjust the records here
			 * beक्रमe the record insert is that an error
			 * later might अवरोध the rule where a parent
			 * record e_cpos will reflect the actual
			 * e_cpos of the 1st nonempty record of the
			 * child list.
			 */
			*ret_left_path = left_path;
			जाओ out_ret_path;
		पूर्ण

		start = ocfs2_find_subtree_root(et, left_path, right_path);

		trace_ocfs2_rotate_subtree(start,
			(अचिन्हित दीर्घ दीर्घ)
			right_path->p_node[start].bh->b_blocknr,
			right_path->p_tree_depth);

		ret = ocfs2_extend_rotate_transaction(handle, start,
						      orig_credits, right_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_rotate_subtree_right(handle, et, left_path,
						 right_path, start);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (split != SPLIT_NONE &&
		    ocfs2_lefपंचांगost_rec_contains(path_leaf_el(right_path),
						insert_cpos)) अणु
			/*
			 * A rotate moves the righपंचांगost left leaf
			 * record over to the lefपंचांगost right leaf
			 * slot. If we're करोing an extent split
			 * instead of a real insert, then we have to
			 * check that the extent to be split wasn't
			 * just moved over. If it was, then we can
			 * निकास here, passing left_path back -
			 * ocfs2_split_extent() is smart enough to
			 * search both leaves.
			 */
			*ret_left_path = left_path;
			जाओ out_ret_path;
		पूर्ण

		/*
		 * There is no need to re-पढ़ो the next right path
		 * as we know that it'll be our current left
		 * path. Optimize by copying values instead.
		 */
		ocfs2_mv_path(right_path, left_path);

		ret = ocfs2_find_cpos_क्रम_left_leaf(sb, right_path, &cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	ocfs2_मुक्त_path(left_path);

out_ret_path:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_update_edge_lengths(handle_t *handle,
				     काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_path *path)
अणु
	पूर्णांक i, idx, ret;
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_block *eb;
	u32 range;

	ret = ocfs2_journal_access_path(et->et_ci, handle, path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Path should always be righपंचांगost. */
	eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(path)->b_data;
	BUG_ON(eb->h_next_leaf_blk != 0ULL);

	el = &eb->h_list;
	BUG_ON(le16_to_cpu(el->l_next_मुक्त_rec) == 0);
	idx = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
	rec = &el->l_recs[idx];
	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);

	क्रम (i = 0; i < path->p_tree_depth; i++) अणु
		el = path->p_node[i].el;
		idx = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
		rec = &el->l_recs[idx];

		rec->e_पूर्णांक_clusters = cpu_to_le32(range);
		le32_add_cpu(&rec->e_पूर्णांक_clusters, -le32_to_cpu(rec->e_cpos));

		ocfs2_journal_dirty(handle, path->p_node[i].bh);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_unlink_path(handle_t *handle,
			      काष्ठा ocfs2_extent_tree *et,
			      काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			      काष्ठा ocfs2_path *path, पूर्णांक unlink_start)
अणु
	पूर्णांक ret, i;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा buffer_head *bh;

	क्रम(i = unlink_start; i < path_num_items(path); i++) अणु
		bh = path->p_node[i].bh;

		eb = (काष्ठा ocfs2_extent_block *)bh->b_data;
		/*
		 * Not all nodes might have had their final count
		 * decremented by the caller - handle this here.
		 */
		el = &eb->h_list;
		अगर (le16_to_cpu(el->l_next_मुक्त_rec) > 1) अणु
			mlog(ML_ERROR,
			     "Inode %llu, attempted to remove extent block "
			     "%llu with %u records\n",
			     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
			     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(eb->h_blkno),
			     le16_to_cpu(el->l_next_मुक्त_rec));

			ocfs2_journal_dirty(handle, bh);
			ocfs2_हटाओ_from_cache(et->et_ci, bh);
			जारी;
		पूर्ण

		el->l_next_मुक्त_rec = 0;
		स_रखो(&el->l_recs[0], 0, माप(काष्ठा ocfs2_extent_rec));

		ocfs2_journal_dirty(handle, bh);

		ret = ocfs2_cache_extent_block_मुक्त(dealloc, eb);
		अगर (ret)
			mlog_त्रुटि_सं(ret);

		ocfs2_हटाओ_from_cache(et->et_ci, bh);
	पूर्ण
पूर्ण

अटल व्योम ocfs2_unlink_subtree(handle_t *handle,
				 काष्ठा ocfs2_extent_tree *et,
				 काष्ठा ocfs2_path *left_path,
				 काष्ठा ocfs2_path *right_path,
				 पूर्णांक subtree_index,
				 काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक i;
	काष्ठा buffer_head *root_bh = left_path->p_node[subtree_index].bh;
	काष्ठा ocfs2_extent_list *root_el = left_path->p_node[subtree_index].el;
	काष्ठा ocfs2_extent_block *eb;

	eb = (काष्ठा ocfs2_extent_block *)right_path->p_node[subtree_index + 1].bh->b_data;

	क्रम(i = 1; i < le16_to_cpu(root_el->l_next_मुक्त_rec); i++)
		अगर (root_el->l_recs[i].e_blkno == eb->h_blkno)
			अवरोध;

	BUG_ON(i >= le16_to_cpu(root_el->l_next_मुक्त_rec));

	स_रखो(&root_el->l_recs[i], 0, माप(काष्ठा ocfs2_extent_rec));
	le16_add_cpu(&root_el->l_next_मुक्त_rec, -1);

	eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(left_path)->b_data;
	eb->h_next_leaf_blk = 0;

	ocfs2_journal_dirty(handle, root_bh);
	ocfs2_journal_dirty(handle, path_leaf_bh(left_path));

	ocfs2_unlink_path(handle, et, dealloc, right_path,
			  subtree_index + 1);
पूर्ण

अटल पूर्णांक ocfs2_rotate_subtree_left(handle_t *handle,
				     काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_path *left_path,
				     काष्ठा ocfs2_path *right_path,
				     पूर्णांक subtree_index,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				     पूर्णांक *deleted)
अणु
	पूर्णांक ret, i, del_right_subtree = 0, right_has_empty = 0;
	काष्ठा buffer_head *root_bh, *et_root_bh = path_root_bh(right_path);
	काष्ठा ocfs2_extent_list *right_leaf_el, *left_leaf_el;
	काष्ठा ocfs2_extent_block *eb;

	*deleted = 0;

	right_leaf_el = path_leaf_el(right_path);
	left_leaf_el = path_leaf_el(left_path);
	root_bh = left_path->p_node[subtree_index].bh;
	BUG_ON(root_bh != right_path->p_node[subtree_index].bh);

	अगर (!ocfs2_is_empty_extent(&left_leaf_el->l_recs[0]))
		वापस 0;

	eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(right_path)->b_data;
	अगर (ocfs2_is_empty_extent(&right_leaf_el->l_recs[0])) अणु
		/*
		 * It's legal क्रम us to proceed अगर the right leaf is
		 * the righपंचांगost one and it has an empty extent. There
		 * are two हालs to handle - whether the leaf will be
		 * empty after removal or not. If the leaf isn't empty
		 * then just हटाओ the empty extent up front. The
		 * next block will handle empty leaves by flagging
		 * them क्रम unlink.
		 *
		 * Non righपंचांगost leaves will throw -EAGAIN and the
		 * caller can manually move the subtree and retry.
		 */

		अगर (eb->h_next_leaf_blk != 0ULL)
			वापस -EAGAIN;

		अगर (le16_to_cpu(right_leaf_el->l_next_मुक्त_rec) > 1) अणु
			ret = ocfs2_journal_access_eb(handle, et->et_ci,
						      path_leaf_bh(right_path),
						      OCFS2_JOURNAL_ACCESS_WRITE);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ocfs2_हटाओ_empty_extent(right_leaf_el);
		पूर्ण अन्यथा
			right_has_empty = 1;
	पूर्ण

	अगर (eb->h_next_leaf_blk == 0ULL &&
	    le16_to_cpu(right_leaf_el->l_next_मुक्त_rec) == 1) अणु
		/*
		 * We have to update i_last_eb_blk during the meta
		 * data delete.
		 */
		ret = ocfs2_et_root_journal_access(handle, et,
						   OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		del_right_subtree = 1;
	पूर्ण

	/*
	 * Getting here with an empty extent in the right path implies
	 * that it's the righपंचांगost path and will be deleted.
	 */
	BUG_ON(right_has_empty && !del_right_subtree);

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, right_path,
					   subtree_index);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	क्रम(i = subtree_index + 1; i < path_num_items(right_path); i++) अणु
		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   right_path, i);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   left_path, i);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!right_has_empty) अणु
		/*
		 * Only करो this अगर we're moving a real
		 * record. Otherwise, the action is delayed until
		 * after removal of the right path in which हाल we
		 * can करो a simple shअगरt to हटाओ the empty extent.
		 */
		ocfs2_rotate_leaf(left_leaf_el, &right_leaf_el->l_recs[0]);
		स_रखो(&right_leaf_el->l_recs[0], 0,
		       माप(काष्ठा ocfs2_extent_rec));
	पूर्ण
	अगर (eb->h_next_leaf_blk == 0ULL) अणु
		/*
		 * Move recs over to get rid of empty extent, decrease
		 * next_मुक्त. This is allowed to हटाओ the last
		 * extent in our leaf (setting l_next_मुक्त_rec to
		 * zero) - the delete code below won't care.
		 */
		ocfs2_हटाओ_empty_extent(right_leaf_el);
	पूर्ण

	ocfs2_journal_dirty(handle, path_leaf_bh(left_path));
	ocfs2_journal_dirty(handle, path_leaf_bh(right_path));

	अगर (del_right_subtree) अणु
		ocfs2_unlink_subtree(handle, et, left_path, right_path,
				     subtree_index, dealloc);
		ret = ocfs2_update_edge_lengths(handle, et, left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(left_path)->b_data;
		ocfs2_et_set_last_eb_blk(et, le64_to_cpu(eb->h_blkno));

		/*
		 * Removal of the extent in the left leaf was skipped
		 * above so we could delete the right path
		 * 1st.
		 */
		अगर (right_has_empty)
			ocfs2_हटाओ_empty_extent(left_leaf_el);

		ocfs2_journal_dirty(handle, et_root_bh);

		*deleted = 1;
	पूर्ण अन्यथा
		ocfs2_complete_edge_insert(handle, left_path, right_path,
					   subtree_index);

out:
	वापस ret;
पूर्ण

/*
 * Given a full path, determine what cpos value would वापस us a path
 * containing the leaf immediately to the right of the current one.
 *
 * Will वापस zero अगर the path passed in is alपढ़ोy the righपंचांगost path.
 *
 * This looks similar, but is subtly dअगरferent to
 * ocfs2_find_cpos_क्रम_left_leaf().
 */
पूर्णांक ocfs2_find_cpos_क्रम_right_leaf(काष्ठा super_block *sb,
				   काष्ठा ocfs2_path *path, u32 *cpos)
अणु
	पूर्णांक i, j, ret = 0;
	u64 blkno;
	काष्ठा ocfs2_extent_list *el;

	*cpos = 0;

	अगर (path->p_tree_depth == 0)
		वापस 0;

	blkno = path_leaf_bh(path)->b_blocknr;

	/* Start at the tree node just above the leaf and work our way up. */
	i = path->p_tree_depth - 1;
	जबतक (i >= 0) अणु
		पूर्णांक next_मुक्त;

		el = path->p_node[i].el;

		/*
		 * Find the extent record just after the one in our
		 * path.
		 */
		next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
		क्रम(j = 0; j < le16_to_cpu(el->l_next_मुक्त_rec); j++) अणु
			अगर (le64_to_cpu(el->l_recs[j].e_blkno) == blkno) अणु
				अगर (j == (next_मुक्त - 1)) अणु
					अगर (i == 0) अणु
						/*
						 * We've determined that the
						 * path specअगरied is alपढ़ोy
						 * the righपंचांगost one - वापस a
						 * cpos of zero.
						 */
						जाओ out;
					पूर्ण
					/*
					 * The righपंचांगost record poपूर्णांकs to our
					 * leaf - we need to travel up the
					 * tree one level.
					 */
					जाओ next_node;
				पूर्ण

				*cpos = le32_to_cpu(el->l_recs[j + 1].e_cpos);
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * If we got here, we never found a valid node where
		 * the tree indicated one should be.
		 */
		ocfs2_error(sb, "Invalid extent tree at extent block %llu\n",
			    (अचिन्हित दीर्घ दीर्घ)blkno);
		ret = -EROFS;
		जाओ out;

next_node:
		blkno = path->p_node[i].bh->b_blocknr;
		i--;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_rotate_righपंचांगost_leaf_left(handle_t *handle,
					    काष्ठा ocfs2_extent_tree *et,
					    काष्ठा ocfs2_path *path)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *bh = path_leaf_bh(path);
	काष्ठा ocfs2_extent_list *el = path_leaf_el(path);

	अगर (!ocfs2_is_empty_extent(&el->l_recs[0]))
		वापस 0;

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, path,
					   path_num_items(path) - 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_हटाओ_empty_extent(el);
	ocfs2_journal_dirty(handle, bh);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_rotate_tree_left(handle_t *handle,
				    काष्ठा ocfs2_extent_tree *et,
				    पूर्णांक orig_credits,
				    काष्ठा ocfs2_path *path,
				    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				    काष्ठा ocfs2_path **empty_extent_path)
अणु
	पूर्णांक ret, subtree_root, deleted;
	u32 right_cpos;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_path *right_path = शून्य;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);

	अगर (!ocfs2_is_empty_extent(&(path_leaf_el(path)->l_recs[0])))
		वापस 0;

	*empty_extent_path = शून्य;

	ret = ocfs2_find_cpos_क्रम_right_leaf(sb, path, &right_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	left_path = ocfs2_new_path_from_path(path);
	अगर (!left_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_cp_path(left_path, path);

	right_path = ocfs2_new_path_from_path(path);
	अगर (!right_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	जबतक (right_cpos) अणु
		ret = ocfs2_find_path(et->et_ci, right_path, right_cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		subtree_root = ocfs2_find_subtree_root(et, left_path,
						       right_path);

		trace_ocfs2_rotate_subtree(subtree_root,
		     (अचिन्हित दीर्घ दीर्घ)
		     right_path->p_node[subtree_root].bh->b_blocknr,
		     right_path->p_tree_depth);

		ret = ocfs2_extend_rotate_transaction(handle, 0,
						      orig_credits, left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * Caller might still want to make changes to the
		 * tree root, so re-add it to the journal here.
		 */
		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   left_path, 0);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_rotate_subtree_left(handle, et, left_path,
						right_path, subtree_root,
						dealloc, &deleted);
		अगर (ret == -EAGAIN) अणु
			/*
			 * The rotation has to temporarily stop due to
			 * the right subtree having an empty
			 * extent. Pass it back to the caller क्रम a
			 * fixup.
			 */
			*empty_extent_path = right_path;
			right_path = शून्य;
			जाओ out;
		पूर्ण
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * The subtree rotate might have हटाओd records on
		 * the righपंचांगost edge. If so, then rotation is
		 * complete.
		 */
		अगर (deleted)
			अवरोध;

		ocfs2_mv_path(left_path, right_path);

		ret = ocfs2_find_cpos_क्रम_right_leaf(sb, left_path,
						     &right_cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	ocfs2_मुक्त_path(right_path);
	ocfs2_मुक्त_path(left_path);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_हटाओ_righपंचांगost_path(handle_t *handle,
				काष्ठा ocfs2_extent_tree *et,
				काष्ठा ocfs2_path *path,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret, subtree_index;
	u32 cpos;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;

	ret = ocfs2_et_sanity_check(et);
	अगर (ret)
		जाओ out;

	ret = ocfs2_journal_access_path(et->et_ci, handle, path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_cpos_क्रम_left_leaf(ocfs2_metadata_cache_get_super(et->et_ci),
					    path, &cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (cpos) अणु
		/*
		 * We have a path to the left of this one - it needs
		 * an update too.
		 */
		left_path = ocfs2_new_path_from_path(path);
		अगर (!left_path) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_find_path(et->et_ci, left_path, cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		subtree_index = ocfs2_find_subtree_root(et, left_path, path);

		ocfs2_unlink_subtree(handle, et, left_path, path,
				     subtree_index, dealloc);
		ret = ocfs2_update_edge_lengths(handle, et, left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(left_path)->b_data;
		ocfs2_et_set_last_eb_blk(et, le64_to_cpu(eb->h_blkno));
	पूर्ण अन्यथा अणु
		/*
		 * 'path' is also the lefपंचांगost path which
		 * means it must be the only one. This माला_लो
		 * handled dअगरferently because we want to
		 * revert the root back to having extents
		 * in-line.
		 */
		ocfs2_unlink_path(handle, et, dealloc, path, 1);

		el = et->et_root_el;
		el->l_tree_depth = 0;
		el->l_next_मुक्त_rec = 0;
		स_रखो(&el->l_recs[0], 0, माप(काष्ठा ocfs2_extent_rec));

		ocfs2_et_set_last_eb_blk(et, 0);
	पूर्ण

	ocfs2_journal_dirty(handle, path_root_bh(path));

out:
	ocfs2_मुक्त_path(left_path);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_हटाओ_righपंचांगost_empty_extent(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_extent_tree *et,
				काष्ठा ocfs2_path *path,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	handle_t *handle;
	पूर्णांक ret;
	पूर्णांक credits = path->p_tree_depth * 2 + 1;

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ret = ocfs2_हटाओ_righपंचांगost_path(handle, et, path, dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	ocfs2_commit_trans(osb, handle);
	वापस ret;
पूर्ण

/*
 * Left rotation of btree records.
 *
 * In many ways, this is (unsurprisingly) the opposite of right
 * rotation. We start at some non-righपंचांगost path containing an empty
 * extent in the leaf block. The code works its way to the righपंचांगost
 * path by rotating records to the left in every subtree.
 *
 * This is used by any code which reduces the number of extent records
 * in a leaf. After removal, an empty record should be placed in the
 * lefपंचांगost list position.
 *
 * This won't handle a length update of the righपंचांगost path records अगर
 * the righपंचांगost tree leaf record is हटाओd so the caller is
 * responsible क्रम detecting and correcting that.
 */
अटल पूर्णांक ocfs2_rotate_tree_left(handle_t *handle,
				  काष्ठा ocfs2_extent_tree *et,
				  काष्ठा ocfs2_path *path,
				  काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret, orig_credits = jbd2_handle_buffer_credits(handle);
	काष्ठा ocfs2_path *पंचांगp_path = शून्य, *restart_path = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;

	el = path_leaf_el(path);
	अगर (!ocfs2_is_empty_extent(&el->l_recs[0]))
		वापस 0;

	अगर (path->p_tree_depth == 0) अणु
righपंचांगost_no_delete:
		/*
		 * Inline extents. This is trivially handled, so करो
		 * it up front.
		 */
		ret = ocfs2_rotate_righपंचांगost_leaf_left(handle, et, path);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Handle righपंचांगost branch now. There's several हालs:
	 *  1) simple rotation leaving records in there. That's trivial.
	 *  2) rotation requiring a branch delete - there's no more
	 *     records left. Two हालs of this:
	 *     a) There are branches to the left.
	 *     b) This is also the lefपंचांगost (the only) branch.
	 *
	 *  1) is handled via ocfs2_rotate_righपंचांगost_leaf_left()
	 *  2a) we need the left branch so that we can update it with the unlink
	 *  2b) we need to bring the root back to अंतरभूत extents.
	 */

	eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(path)->b_data;
	el = &eb->h_list;
	अगर (eb->h_next_leaf_blk == 0) अणु
		/*
		 * This माला_लो a bit tricky अगर we're going to delete the
		 * righपंचांगost path. Get the other हालs out of the way
		 * 1st.
		 */
		अगर (le16_to_cpu(el->l_next_मुक्त_rec) > 1)
			जाओ righपंचांगost_no_delete;

		अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0) अणु
			ret = ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
					"Owner %llu has empty extent block at %llu\n",
					(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(eb->h_blkno));
			जाओ out;
		पूर्ण

		/*
		 * XXX: The caller can not trust "path" any more after
		 * this as it will have been deleted. What करो we करो?
		 *
		 * In theory the rotate-क्रम-merge code will never get
		 * here because it'll always ask क्रम a rotate in a
		 * nonempty list.
		 */

		ret = ocfs2_हटाओ_righपंचांगost_path(handle, et, path,
						  dealloc);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Now we can loop, remembering the path we get from -EAGAIN
	 * and restarting from there.
	 */
try_rotate:
	ret = __ocfs2_rotate_tree_left(handle, et, orig_credits, path,
				       dealloc, &restart_path);
	अगर (ret && ret != -EAGAIN) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	जबतक (ret == -EAGAIN) अणु
		पंचांगp_path = restart_path;
		restart_path = शून्य;

		ret = __ocfs2_rotate_tree_left(handle, et, orig_credits,
					       पंचांगp_path, dealloc,
					       &restart_path);
		अगर (ret && ret != -EAGAIN) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ocfs2_मुक्त_path(पंचांगp_path);
		पंचांगp_path = शून्य;

		अगर (ret == 0)
			जाओ try_rotate;
	पूर्ण

out:
	ocfs2_मुक्त_path(पंचांगp_path);
	ocfs2_मुक्त_path(restart_path);
	वापस ret;
पूर्ण

अटल व्योम ocfs2_cleanup_merge(काष्ठा ocfs2_extent_list *el,
				पूर्णांक index)
अणु
	काष्ठा ocfs2_extent_rec *rec = &el->l_recs[index];
	अचिन्हित पूर्णांक size;

	अगर (rec->e_leaf_clusters == 0) अणु
		/*
		 * We consumed all of the merged-from record. An empty
		 * extent cannot exist anywhere but the 1st array
		 * position, so move things over अगर the merged-from
		 * record करोesn't occupy that position.
		 *
		 * This creates a new empty extent so the caller
		 * should be smart enough to have हटाओd any existing
		 * ones.
		 */
		अगर (index > 0) अणु
			BUG_ON(ocfs2_is_empty_extent(&el->l_recs[0]));
			size = index * माप(काष्ठा ocfs2_extent_rec);
			स_हटाओ(&el->l_recs[1], &el->l_recs[0], size);
		पूर्ण

		/*
		 * Always स_रखो - the caller करोesn't check whether it
		 * created an empty extent, so there could be junk in
		 * the other fields.
		 */
		स_रखो(&el->l_recs[0], 0, माप(काष्ठा ocfs2_extent_rec));
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_get_right_path(काष्ठा ocfs2_extent_tree *et,
				काष्ठा ocfs2_path *left_path,
				काष्ठा ocfs2_path **ret_right_path)
अणु
	पूर्णांक ret;
	u32 right_cpos;
	काष्ठा ocfs2_path *right_path = शून्य;
	काष्ठा ocfs2_extent_list *left_el;

	*ret_right_path = शून्य;

	/* This function shouldn't be called क्रम non-trees. */
	BUG_ON(left_path->p_tree_depth == 0);

	left_el = path_leaf_el(left_path);
	BUG_ON(left_el->l_next_मुक्त_rec != left_el->l_count);

	ret = ocfs2_find_cpos_क्रम_right_leaf(ocfs2_metadata_cache_get_super(et->et_ci),
					     left_path, &right_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* This function shouldn't be called क्रम the righपंचांगost leaf. */
	BUG_ON(right_cpos == 0);

	right_path = ocfs2_new_path_from_path(left_path);
	अगर (!right_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, right_path, right_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*ret_right_path = right_path;
out:
	अगर (ret)
		ocfs2_मुक्त_path(right_path);
	वापस ret;
पूर्ण

/*
 * Remove split_rec clusters from the record at index and merge them
 * onto the beginning of the record "next" to it.
 * For index < l_count - 1, the next means the extent rec at index + 1.
 * For index == l_count - 1, the "next" means the 1st extent rec of the
 * next extent block.
 */
अटल पूर्णांक ocfs2_merge_rec_right(काष्ठा ocfs2_path *left_path,
				 handle_t *handle,
				 काष्ठा ocfs2_extent_tree *et,
				 काष्ठा ocfs2_extent_rec *split_rec,
				 पूर्णांक index)
अणु
	पूर्णांक ret, next_मुक्त, i;
	अचिन्हित पूर्णांक split_clusters = le16_to_cpu(split_rec->e_leaf_clusters);
	काष्ठा ocfs2_extent_rec *left_rec;
	काष्ठा ocfs2_extent_rec *right_rec;
	काष्ठा ocfs2_extent_list *right_el;
	काष्ठा ocfs2_path *right_path = शून्य;
	पूर्णांक subtree_index = 0;
	काष्ठा ocfs2_extent_list *el = path_leaf_el(left_path);
	काष्ठा buffer_head *bh = path_leaf_bh(left_path);
	काष्ठा buffer_head *root_bh = शून्य;

	BUG_ON(index >= le16_to_cpu(el->l_next_मुक्त_rec));
	left_rec = &el->l_recs[index];

	अगर (index == le16_to_cpu(el->l_next_मुक्त_rec) - 1 &&
	    le16_to_cpu(el->l_next_मुक्त_rec) == le16_to_cpu(el->l_count)) अणु
		/* we meet with a cross extent block merge. */
		ret = ocfs2_get_right_path(et, left_path, &right_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		right_el = path_leaf_el(right_path);
		next_मुक्त = le16_to_cpu(right_el->l_next_मुक्त_rec);
		BUG_ON(next_मुक्त <= 0);
		right_rec = &right_el->l_recs[0];
		अगर (ocfs2_is_empty_extent(right_rec)) अणु
			BUG_ON(next_मुक्त <= 1);
			right_rec = &right_el->l_recs[1];
		पूर्ण

		BUG_ON(le32_to_cpu(left_rec->e_cpos) +
		       le16_to_cpu(left_rec->e_leaf_clusters) !=
		       le32_to_cpu(right_rec->e_cpos));

		subtree_index = ocfs2_find_subtree_root(et, left_path,
							right_path);

		ret = ocfs2_extend_rotate_transaction(handle, subtree_index,
					jbd2_handle_buffer_credits(handle),
					right_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		root_bh = left_path->p_node[subtree_index].bh;
		BUG_ON(root_bh != right_path->p_node[subtree_index].bh);

		ret = ocfs2_path_bh_journal_access(handle, et->et_ci, right_path,
						   subtree_index);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		क्रम (i = subtree_index + 1;
		     i < path_num_items(right_path); i++) अणु
			ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
							   right_path, i);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
							   left_path, i);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		BUG_ON(index == le16_to_cpu(el->l_next_मुक्त_rec) - 1);
		right_rec = &el->l_recs[index + 1];
	पूर्ण

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, left_path,
					   path_num_items(left_path) - 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	le16_add_cpu(&left_rec->e_leaf_clusters, -split_clusters);

	le32_add_cpu(&right_rec->e_cpos, -split_clusters);
	le64_add_cpu(&right_rec->e_blkno,
		     -ocfs2_clusters_to_blocks(ocfs2_metadata_cache_get_super(et->et_ci),
					       split_clusters));
	le16_add_cpu(&right_rec->e_leaf_clusters, split_clusters);

	ocfs2_cleanup_merge(el, index);

	ocfs2_journal_dirty(handle, bh);
	अगर (right_path) अणु
		ocfs2_journal_dirty(handle, path_leaf_bh(right_path));
		ocfs2_complete_edge_insert(handle, left_path, right_path,
					   subtree_index);
	पूर्ण
out:
	ocfs2_मुक्त_path(right_path);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_get_left_path(काष्ठा ocfs2_extent_tree *et,
			       काष्ठा ocfs2_path *right_path,
			       काष्ठा ocfs2_path **ret_left_path)
अणु
	पूर्णांक ret;
	u32 left_cpos;
	काष्ठा ocfs2_path *left_path = शून्य;

	*ret_left_path = शून्य;

	/* This function shouldn't be called क्रम non-trees. */
	BUG_ON(right_path->p_tree_depth == 0);

	ret = ocfs2_find_cpos_क्रम_left_leaf(ocfs2_metadata_cache_get_super(et->et_ci),
					    right_path, &left_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* This function shouldn't be called क्रम the lefपंचांगost leaf. */
	BUG_ON(left_cpos == 0);

	left_path = ocfs2_new_path_from_path(right_path);
	अगर (!left_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, left_path, left_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*ret_left_path = left_path;
out:
	अगर (ret)
		ocfs2_मुक्त_path(left_path);
	वापस ret;
पूर्ण

/*
 * Remove split_rec clusters from the record at index and merge them
 * onto the tail of the record "before" it.
 * For index > 0, the "before" means the extent rec at index - 1.
 *
 * For index == 0, the "before" means the last record of the previous
 * extent block. And there is also a situation that we may need to
 * हटाओ the righपंचांगost leaf extent block in the right_path and change
 * the right path to indicate the new righपंचांगost path.
 */
अटल पूर्णांक ocfs2_merge_rec_left(काष्ठा ocfs2_path *right_path,
				handle_t *handle,
				काष्ठा ocfs2_extent_tree *et,
				काष्ठा ocfs2_extent_rec *split_rec,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				पूर्णांक index)
अणु
	पूर्णांक ret, i, subtree_index = 0, has_empty_extent = 0;
	अचिन्हित पूर्णांक split_clusters = le16_to_cpu(split_rec->e_leaf_clusters);
	काष्ठा ocfs2_extent_rec *left_rec;
	काष्ठा ocfs2_extent_rec *right_rec;
	काष्ठा ocfs2_extent_list *el = path_leaf_el(right_path);
	काष्ठा buffer_head *bh = path_leaf_bh(right_path);
	काष्ठा buffer_head *root_bh = शून्य;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_extent_list *left_el;

	BUG_ON(index < 0);

	right_rec = &el->l_recs[index];
	अगर (index == 0) अणु
		/* we meet with a cross extent block merge. */
		ret = ocfs2_get_left_path(et, right_path, &left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		left_el = path_leaf_el(left_path);
		BUG_ON(le16_to_cpu(left_el->l_next_मुक्त_rec) !=
		       le16_to_cpu(left_el->l_count));

		left_rec = &left_el->l_recs[
				le16_to_cpu(left_el->l_next_मुक्त_rec) - 1];
		BUG_ON(le32_to_cpu(left_rec->e_cpos) +
		       le16_to_cpu(left_rec->e_leaf_clusters) !=
		       le32_to_cpu(split_rec->e_cpos));

		subtree_index = ocfs2_find_subtree_root(et, left_path,
							right_path);

		ret = ocfs2_extend_rotate_transaction(handle, subtree_index,
					jbd2_handle_buffer_credits(handle),
					left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		root_bh = left_path->p_node[subtree_index].bh;
		BUG_ON(root_bh != right_path->p_node[subtree_index].bh);

		ret = ocfs2_path_bh_journal_access(handle, et->et_ci, right_path,
						   subtree_index);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		क्रम (i = subtree_index + 1;
		     i < path_num_items(right_path); i++) अणु
			ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
							   right_path, i);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
							   left_path, i);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		left_rec = &el->l_recs[index - 1];
		अगर (ocfs2_is_empty_extent(&el->l_recs[0]))
			has_empty_extent = 1;
	पूर्ण

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, right_path,
					   path_num_items(right_path) - 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (has_empty_extent && index == 1) अणु
		/*
		 * The easy हाल - we can just plop the record right in.
		 */
		*left_rec = *split_rec;
	पूर्ण अन्यथा
		le16_add_cpu(&left_rec->e_leaf_clusters, split_clusters);

	le32_add_cpu(&right_rec->e_cpos, split_clusters);
	le64_add_cpu(&right_rec->e_blkno,
		     ocfs2_clusters_to_blocks(ocfs2_metadata_cache_get_super(et->et_ci),
					      split_clusters));
	le16_add_cpu(&right_rec->e_leaf_clusters, -split_clusters);

	ocfs2_cleanup_merge(el, index);

	ocfs2_journal_dirty(handle, bh);
	अगर (left_path) अणु
		ocfs2_journal_dirty(handle, path_leaf_bh(left_path));

		/*
		 * In the situation that the right_rec is empty and the extent
		 * block is empty also,  ocfs2_complete_edge_insert can't handle
		 * it and we need to delete the right extent block.
		 */
		अगर (le16_to_cpu(right_rec->e_leaf_clusters) == 0 &&
		    le16_to_cpu(el->l_next_मुक्त_rec) == 1) अणु
			/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
			ret = ocfs2_extend_rotate_transaction(handle, 0,
					jbd2_handle_buffer_credits(handle),
					right_path);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_हटाओ_righपंचांगost_path(handle, et,
							  right_path,
							  dealloc);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			/* Now the righपंचांगost extent block has been deleted.
			 * So we use the new righपंचांगost path.
			 */
			ocfs2_mv_path(right_path, left_path);
			left_path = शून्य;
		पूर्ण अन्यथा
			ocfs2_complete_edge_insert(handle, left_path,
						   right_path, subtree_index);
	पूर्ण
out:
	ocfs2_मुक्त_path(left_path);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_try_to_merge_extent(handle_t *handle,
				     काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_path *path,
				     पूर्णांक split_index,
				     काष्ठा ocfs2_extent_rec *split_rec,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				     काष्ठा ocfs2_merge_ctxt *ctxt)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_extent_list *el = path_leaf_el(path);
	काष्ठा ocfs2_extent_rec *rec = &el->l_recs[split_index];

	BUG_ON(ctxt->c_contig_type == CONTIG_NONE);

	अगर (ctxt->c_split_covers_rec && ctxt->c_has_empty_extent) अणु
		/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
		ret = ocfs2_extend_rotate_transaction(handle, 0,
				jbd2_handle_buffer_credits(handle),
				path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		/*
		 * The merge code will need to create an empty
		 * extent to take the place of the newly
		 * emptied slot. Remove any pre-existing empty
		 * extents - having more than one in a leaf is
		 * illegal.
		 */
		ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		split_index--;
		rec = &el->l_recs[split_index];
	पूर्ण

	अगर (ctxt->c_contig_type == CONTIG_LEFTRIGHT) अणु
		/*
		 * Left-right contig implies this.
		 */
		BUG_ON(!ctxt->c_split_covers_rec);

		/*
		 * Since the leftright insert always covers the entire
		 * extent, this call will delete the insert record
		 * entirely, resulting in an empty extent record added to
		 * the extent block.
		 *
		 * Since the adding of an empty extent shअगरts
		 * everything back to the right, there's no need to
		 * update split_index here.
		 *
		 * When the split_index is zero, we need to merge it to the
		 * prevoius extent block. It is more efficient and easier
		 * अगर we करो merge_right first and merge_left later.
		 */
		ret = ocfs2_merge_rec_right(path, handle, et, split_rec,
					    split_index);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * We can only get this from logic error above.
		 */
		BUG_ON(!ocfs2_is_empty_extent(&el->l_recs[0]));

		/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
		ret = ocfs2_extend_rotate_transaction(handle, 0,
					jbd2_handle_buffer_credits(handle),
					path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/* The merge left us with an empty extent, हटाओ it. */
		ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		rec = &el->l_recs[split_index];

		/*
		 * Note that we करोn't pass split_rec here on purpose -
		 * we've merged it पूर्णांकo the rec alपढ़ोy.
		 */
		ret = ocfs2_merge_rec_left(path, handle, et, rec,
					   dealloc, split_index);

		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
		ret = ocfs2_extend_rotate_transaction(handle, 0,
				jbd2_handle_buffer_credits(handle),
				path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
		/*
		 * Error from this last rotate is not critical, so
		 * prपूर्णांक but करोn't bubble it up.
		 */
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Merge a record to the left or right.
		 *
		 * 'contig_type' is relative to the existing record,
		 * so क्रम example, अगर we're "right contig", it's to
		 * the record on the left (hence the left merge).
		 */
		अगर (ctxt->c_contig_type == CONTIG_RIGHT) अणु
			ret = ocfs2_merge_rec_left(path, handle, et,
						   split_rec, dealloc,
						   split_index);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = ocfs2_merge_rec_right(path, handle,
						    et, split_rec,
						    split_index);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (ctxt->c_split_covers_rec) अणु
			/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
			ret = ocfs2_extend_rotate_transaction(handle, 0,
					jbd2_handle_buffer_credits(handle),
					path);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				ret = 0;
				जाओ out;
			पूर्ण

			/*
			 * The merge may have left an empty extent in
			 * our leaf. Try to rotate it away.
			 */
			ret = ocfs2_rotate_tree_left(handle, et, path,
						     dealloc);
			अगर (ret)
				mlog_त्रुटि_सं(ret);
			ret = 0;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_subtract_from_rec(काष्ठा super_block *sb,
				    क्रमागत ocfs2_split_type split,
				    काष्ठा ocfs2_extent_rec *rec,
				    काष्ठा ocfs2_extent_rec *split_rec)
अणु
	u64 len_blocks;

	len_blocks = ocfs2_clusters_to_blocks(sb,
				le16_to_cpu(split_rec->e_leaf_clusters));

	अगर (split == SPLIT_LEFT) अणु
		/*
		 * Region is on the left edge of the existing
		 * record.
		 */
		le32_add_cpu(&rec->e_cpos,
			     le16_to_cpu(split_rec->e_leaf_clusters));
		le64_add_cpu(&rec->e_blkno, len_blocks);
		le16_add_cpu(&rec->e_leaf_clusters,
			     -le16_to_cpu(split_rec->e_leaf_clusters));
	पूर्ण अन्यथा अणु
		/*
		 * Region is on the right edge of the existing
		 * record.
		 */
		le16_add_cpu(&rec->e_leaf_clusters,
			     -le16_to_cpu(split_rec->e_leaf_clusters));
	पूर्ण
पूर्ण

/*
 * Do the final bits of extent record insertion at the target leaf
 * list. If this leaf is part of an allocation tree, it is assumed
 * that the tree above has been prepared.
 */
अटल व्योम ocfs2_insert_at_leaf(काष्ठा ocfs2_extent_tree *et,
				 काष्ठा ocfs2_extent_rec *insert_rec,
				 काष्ठा ocfs2_extent_list *el,
				 काष्ठा ocfs2_insert_type *insert)
अणु
	पूर्णांक i = insert->ins_contig_index;
	अचिन्हित पूर्णांक range;
	काष्ठा ocfs2_extent_rec *rec;

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	अगर (insert->ins_split != SPLIT_NONE) अणु
		i = ocfs2_search_extent_list(el, le32_to_cpu(insert_rec->e_cpos));
		BUG_ON(i == -1);
		rec = &el->l_recs[i];
		ocfs2_subtract_from_rec(ocfs2_metadata_cache_get_super(et->et_ci),
					insert->ins_split, rec,
					insert_rec);
		जाओ rotate;
	पूर्ण

	/*
	 * Contiguous insert - either left or right.
	 */
	अगर (insert->ins_contig != CONTIG_NONE) अणु
		rec = &el->l_recs[i];
		अगर (insert->ins_contig == CONTIG_LEFT) अणु
			rec->e_blkno = insert_rec->e_blkno;
			rec->e_cpos = insert_rec->e_cpos;
		पूर्ण
		le16_add_cpu(&rec->e_leaf_clusters,
			     le16_to_cpu(insert_rec->e_leaf_clusters));
		वापस;
	पूर्ण

	/*
	 * Handle insert पूर्णांकo an empty leaf.
	 */
	अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0 ||
	    ((le16_to_cpu(el->l_next_मुक्त_rec) == 1) &&
	     ocfs2_is_empty_extent(&el->l_recs[0]))) अणु
		el->l_recs[0] = *insert_rec;
		el->l_next_मुक्त_rec = cpu_to_le16(1);
		वापस;
	पूर्ण

	/*
	 * Appending insert.
	 */
	अगर (insert->ins_appending == APPEND_TAIL) अणु
		i = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
		rec = &el->l_recs[i];
		range = le32_to_cpu(rec->e_cpos)
			+ le16_to_cpu(rec->e_leaf_clusters);
		BUG_ON(le32_to_cpu(insert_rec->e_cpos) < range);

		mlog_bug_on_msg(le16_to_cpu(el->l_next_मुक्त_rec) >=
				le16_to_cpu(el->l_count),
				"owner %llu, depth %u, count %u, next free %u, "
				"rec.cpos %u, rec.clusters %u, "
				"insert.cpos %u, insert.clusters %u\n",
				ocfs2_metadata_cache_owner(et->et_ci),
				le16_to_cpu(el->l_tree_depth),
				le16_to_cpu(el->l_count),
				le16_to_cpu(el->l_next_मुक्त_rec),
				le32_to_cpu(el->l_recs[i].e_cpos),
				le16_to_cpu(el->l_recs[i].e_leaf_clusters),
				le32_to_cpu(insert_rec->e_cpos),
				le16_to_cpu(insert_rec->e_leaf_clusters));
		i++;
		el->l_recs[i] = *insert_rec;
		le16_add_cpu(&el->l_next_मुक्त_rec, 1);
		वापस;
	पूर्ण

rotate:
	/*
	 * Ok, we have to rotate.
	 *
	 * At this poपूर्णांक, it is safe to assume that inserting पूर्णांकo an
	 * empty leaf and appending to a leaf have both been handled
	 * above.
	 *
	 * This leaf needs to have space, either by the empty 1st
	 * extent record, or by virtue of an l_next_मुक्त_rec < l_count.
	 */
	ocfs2_rotate_leaf(el, insert_rec);
पूर्ण

अटल व्योम ocfs2_adjust_righपंचांगost_records(handle_t *handle,
					   काष्ठा ocfs2_extent_tree *et,
					   काष्ठा ocfs2_path *path,
					   काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	पूर्णांक i, next_मुक्त;
	काष्ठा buffer_head *bh;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;

	/*
	 * Update everything except the leaf block.
	 */
	क्रम (i = 0; i < path->p_tree_depth; i++) अणु
		bh = path->p_node[i].bh;
		el = path->p_node[i].el;

		next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
		अगर (next_मुक्त == 0) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu has a bad extent list\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci));
			वापस;
		पूर्ण

		rec = &el->l_recs[next_मुक्त - 1];

		rec->e_पूर्णांक_clusters = insert_rec->e_cpos;
		le32_add_cpu(&rec->e_पूर्णांक_clusters,
			     le16_to_cpu(insert_rec->e_leaf_clusters));
		le32_add_cpu(&rec->e_पूर्णांक_clusters,
			     -le32_to_cpu(rec->e_cpos));

		ocfs2_journal_dirty(handle, bh);
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_append_rec_to_path(handle_t *handle,
				    काष्ठा ocfs2_extent_tree *et,
				    काष्ठा ocfs2_extent_rec *insert_rec,
				    काष्ठा ocfs2_path *right_path,
				    काष्ठा ocfs2_path **ret_left_path)
अणु
	पूर्णांक ret, next_मुक्त;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_path *left_path = शून्य;

	*ret_left_path = शून्य;

	/*
	 * This shouldn't happen क्रम non-trees. The extent rec cluster
	 * count manipulation below only works क्रम पूर्णांकerior nodes.
	 */
	BUG_ON(right_path->p_tree_depth == 0);

	/*
	 * If our appending insert is at the lefपंचांगost edge of a leaf,
	 * then we might need to update the righपंचांगost records of the
	 * neighboring path.
	 */
	el = path_leaf_el(right_path);
	next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
	अगर (next_मुक्त == 0 ||
	    (next_मुक्त == 1 && ocfs2_is_empty_extent(&el->l_recs[0]))) अणु
		u32 left_cpos;

		ret = ocfs2_find_cpos_क्रम_left_leaf(ocfs2_metadata_cache_get_super(et->et_ci),
						    right_path, &left_cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		trace_ocfs2_append_rec_to_path(
			(अचिन्हित दीर्घ दीर्घ)
			ocfs2_metadata_cache_owner(et->et_ci),
			le32_to_cpu(insert_rec->e_cpos),
			left_cpos);

		/*
		 * No need to worry अगर the append is alपढ़ोy in the
		 * lefपंचांगost leaf.
		 */
		अगर (left_cpos) अणु
			left_path = ocfs2_new_path_from_path(right_path);
			अगर (!left_path) अणु
				ret = -ENOMEM;
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_find_path(et->et_ci, left_path,
					      left_cpos);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			/*
			 * ocfs2_insert_path() will pass the left_path to the
			 * journal क्रम us.
			 */
		पूर्ण
	पूर्ण

	ret = ocfs2_journal_access_path(et->et_ci, handle, right_path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_adjust_righपंचांगost_records(handle, et, right_path, insert_rec);

	*ret_left_path = left_path;
	ret = 0;
out:
	अगर (ret != 0)
		ocfs2_मुक्त_path(left_path);

	वापस ret;
पूर्ण

अटल व्योम ocfs2_split_record(काष्ठा ocfs2_extent_tree *et,
			       काष्ठा ocfs2_path *left_path,
			       काष्ठा ocfs2_path *right_path,
			       काष्ठा ocfs2_extent_rec *split_rec,
			       क्रमागत ocfs2_split_type split)
अणु
	पूर्णांक index;
	u32 cpos = le32_to_cpu(split_rec->e_cpos);
	काष्ठा ocfs2_extent_list *left_el = शून्य, *right_el, *insert_el, *el;
	काष्ठा ocfs2_extent_rec *rec, *पंचांगprec;

	right_el = path_leaf_el(right_path);
	अगर (left_path)
		left_el = path_leaf_el(left_path);

	el = right_el;
	insert_el = right_el;
	index = ocfs2_search_extent_list(el, cpos);
	अगर (index != -1) अणु
		अगर (index == 0 && left_path) अणु
			BUG_ON(ocfs2_is_empty_extent(&el->l_recs[0]));

			/*
			 * This typically means that the record
			 * started in the left path but moved to the
			 * right as a result of rotation. We either
			 * move the existing record to the left, or we
			 * करो the later insert there.
			 *
			 * In this हाल, the left path should always
			 * exist as the rotate code will have passed
			 * it back क्रम a post-insert update.
			 */

			अगर (split == SPLIT_LEFT) अणु
				/*
				 * It's a left split. Since we know
				 * that the rotate code gave us an
				 * empty extent in the left path, we
				 * can just करो the insert there.
				 */
				insert_el = left_el;
			पूर्ण अन्यथा अणु
				/*
				 * Right split - we have to move the
				 * existing record over to the left
				 * leaf. The insert will be पूर्णांकo the
				 * newly created empty extent in the
				 * right leaf.
				 */
				पंचांगprec = &right_el->l_recs[index];
				ocfs2_rotate_leaf(left_el, पंचांगprec);
				el = left_el;

				स_रखो(पंचांगprec, 0, माप(*पंचांगprec));
				index = ocfs2_search_extent_list(left_el, cpos);
				BUG_ON(index == -1);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(!left_path);
		BUG_ON(!ocfs2_is_empty_extent(&left_el->l_recs[0]));
		/*
		 * Left path is easy - we can just allow the insert to
		 * happen.
		 */
		el = left_el;
		insert_el = left_el;
		index = ocfs2_search_extent_list(el, cpos);
		BUG_ON(index == -1);
	पूर्ण

	rec = &el->l_recs[index];
	ocfs2_subtract_from_rec(ocfs2_metadata_cache_get_super(et->et_ci),
				split, rec, split_rec);
	ocfs2_rotate_leaf(insert_el, split_rec);
पूर्ण

/*
 * This function only करोes inserts on an allocation b-tree. For tree
 * depth = 0, ocfs2_insert_at_leaf() is called directly.
 *
 * right_path is the path we want to करो the actual insert
 * in. left_path should only be passed in अगर we need to update that
 * portion of the tree after an edge insert.
 */
अटल पूर्णांक ocfs2_insert_path(handle_t *handle,
			     काष्ठा ocfs2_extent_tree *et,
			     काष्ठा ocfs2_path *left_path,
			     काष्ठा ocfs2_path *right_path,
			     काष्ठा ocfs2_extent_rec *insert_rec,
			     काष्ठा ocfs2_insert_type *insert)
अणु
	पूर्णांक ret, subtree_index;
	काष्ठा buffer_head *leaf_bh = path_leaf_bh(right_path);

	अगर (left_path) अणु
		/*
		 * There's a chance that left_path got passed back to
		 * us without being accounted क्रम in the
		 * journal. Extend our transaction here to be sure we
		 * can change those blocks.
		 */
		ret = ocfs2_extend_trans(handle, left_path->p_tree_depth);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Pass both paths to the journal. The majority of inserts
	 * will be touching all components anyway.
	 */
	ret = ocfs2_journal_access_path(et->et_ci, handle, right_path);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (insert->ins_split != SPLIT_NONE) अणु
		/*
		 * We could call ocfs2_insert_at_leaf() क्रम some types
		 * of splits, but it's easier to just let one separate
		 * function sort it all out.
		 */
		ocfs2_split_record(et, left_path, right_path,
				   insert_rec, insert->ins_split);

		/*
		 * Split might have modअगरied either leaf and we करोn't
		 * have a guarantee that the later edge insert will
		 * dirty this क्रम us.
		 */
		अगर (left_path)
			ocfs2_journal_dirty(handle,
					    path_leaf_bh(left_path));
	पूर्ण अन्यथा
		ocfs2_insert_at_leaf(et, insert_rec, path_leaf_el(right_path),
				     insert);

	ocfs2_journal_dirty(handle, leaf_bh);

	अगर (left_path) अणु
		/*
		 * The rotate code has indicated that we need to fix
		 * up portions of the tree after the insert.
		 *
		 * XXX: Should we extend the transaction here?
		 */
		subtree_index = ocfs2_find_subtree_root(et, left_path,
							right_path);
		ocfs2_complete_edge_insert(handle, left_path, right_path,
					   subtree_index);
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_करो_insert_extent(handle_t *handle,
				  काष्ठा ocfs2_extent_tree *et,
				  काष्ठा ocfs2_extent_rec *insert_rec,
				  काष्ठा ocfs2_insert_type *type)
अणु
	पूर्णांक ret, rotate = 0;
	u32 cpos;
	काष्ठा ocfs2_path *right_path = शून्य;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_extent_list *el;

	el = et->et_root_el;

	ret = ocfs2_et_root_journal_access(handle, et,
					   OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(el->l_tree_depth) == 0) अणु
		ocfs2_insert_at_leaf(et, insert_rec, el, type);
		जाओ out_update_clusters;
	पूर्ण

	right_path = ocfs2_new_path_from_et(et);
	अगर (!right_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Determine the path to start with. Rotations need the
	 * righपंचांगost path, everything अन्यथा can go directly to the
	 * target leaf.
	 */
	cpos = le32_to_cpu(insert_rec->e_cpos);
	अगर (type->ins_appending == APPEND_NONE &&
	    type->ins_contig == CONTIG_NONE) अणु
		rotate = 1;
		cpos = अच_पूर्णांक_उच्च;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, right_path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Rotations and appends need special treaपंचांगent - they modअगरy
	 * parts of the tree's above them.
	 *
	 * Both might pass back a path immediate to the left of the
	 * one being inserted to. This will be cause
	 * ocfs2_insert_path() to modअगरy the righपंचांगost records of
	 * left_path to account क्रम an edge insert.
	 *
	 * XXX: When modअगरying this code, keep in mind that an insert
	 * can wind up skipping both of these two special हालs...
	 */
	अगर (rotate) अणु
		ret = ocfs2_rotate_tree_right(handle, et, type->ins_split,
					      le32_to_cpu(insert_rec->e_cpos),
					      right_path, &left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * ocfs2_rotate_tree_right() might have extended the
		 * transaction without re-journaling our tree root.
		 */
		ret = ocfs2_et_root_journal_access(handle, et,
						   OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (type->ins_appending == APPEND_TAIL
		   && type->ins_contig != CONTIG_LEFT) अणु
		ret = ocfs2_append_rec_to_path(handle, et, insert_rec,
					       right_path, &left_path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_insert_path(handle, et, left_path, right_path,
				insert_rec, type);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

out_update_clusters:
	अगर (type->ins_split == SPLIT_NONE)
		ocfs2_et_update_clusters(et,
					 le16_to_cpu(insert_rec->e_leaf_clusters));

	ocfs2_journal_dirty(handle, et->et_root_bh);

out:
	ocfs2_मुक्त_path(left_path);
	ocfs2_मुक्त_path(right_path);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_figure_merge_contig_type(काष्ठा ocfs2_extent_tree *et,
			       काष्ठा ocfs2_path *path,
			       काष्ठा ocfs2_extent_list *el, पूर्णांक index,
			       काष्ठा ocfs2_extent_rec *split_rec,
			       काष्ठा ocfs2_merge_ctxt *ctxt)
अणु
	पूर्णांक status = 0;
	क्रमागत ocfs2_contig_type ret = CONTIG_NONE;
	u32 left_cpos, right_cpos;
	काष्ठा ocfs2_extent_rec *rec = शून्य;
	काष्ठा ocfs2_extent_list *new_el;
	काष्ठा ocfs2_path *left_path = शून्य, *right_path = शून्य;
	काष्ठा buffer_head *bh;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);

	अगर (index > 0) अणु
		rec = &el->l_recs[index - 1];
	पूर्ण अन्यथा अगर (path->p_tree_depth > 0) अणु
		status = ocfs2_find_cpos_क्रम_left_leaf(sb, path, &left_cpos);
		अगर (status)
			जाओ निकास;

		अगर (left_cpos != 0) अणु
			left_path = ocfs2_new_path_from_path(path);
			अगर (!left_path) अणु
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				जाओ निकास;
			पूर्ण

			status = ocfs2_find_path(et->et_ci, left_path,
						 left_cpos);
			अगर (status)
				जाओ मुक्त_left_path;

			new_el = path_leaf_el(left_path);

			अगर (le16_to_cpu(new_el->l_next_मुक्त_rec) !=
			    le16_to_cpu(new_el->l_count)) अणु
				bh = path_leaf_bh(left_path);
				eb = (काष्ठा ocfs2_extent_block *)bh->b_data;
				status = ocfs2_error(sb,
						"Extent block #%llu has an invalid l_next_free_rec of %d.  It should have matched the l_count of %d\n",
						(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(eb->h_blkno),
						le16_to_cpu(new_el->l_next_मुक्त_rec),
						le16_to_cpu(new_el->l_count));
				जाओ मुक्त_left_path;
			पूर्ण
			rec = &new_el->l_recs[
				le16_to_cpu(new_el->l_next_मुक्त_rec) - 1];
		पूर्ण
	पूर्ण

	/*
	 * We're careful to check क्रम an empty extent record here -
	 * the merge code will know what to करो अगर it sees one.
	 */
	अगर (rec) अणु
		अगर (index == 1 && ocfs2_is_empty_extent(rec)) अणु
			अगर (split_rec->e_cpos == el->l_recs[index].e_cpos)
				ret = CONTIG_RIGHT;
		पूर्ण अन्यथा अणु
			ret = ocfs2_et_extent_contig(et, rec, split_rec);
		पूर्ण
	पूर्ण

	rec = शून्य;
	अगर (index < (le16_to_cpu(el->l_next_मुक्त_rec) - 1))
		rec = &el->l_recs[index + 1];
	अन्यथा अगर (le16_to_cpu(el->l_next_मुक्त_rec) == le16_to_cpu(el->l_count) &&
		 path->p_tree_depth > 0) अणु
		status = ocfs2_find_cpos_क्रम_right_leaf(sb, path, &right_cpos);
		अगर (status)
			जाओ मुक्त_left_path;

		अगर (right_cpos == 0)
			जाओ मुक्त_left_path;

		right_path = ocfs2_new_path_from_path(path);
		अगर (!right_path) अणु
			status = -ENOMEM;
			mlog_त्रुटि_सं(status);
			जाओ मुक्त_left_path;
		पूर्ण

		status = ocfs2_find_path(et->et_ci, right_path, right_cpos);
		अगर (status)
			जाओ मुक्त_right_path;

		new_el = path_leaf_el(right_path);
		rec = &new_el->l_recs[0];
		अगर (ocfs2_is_empty_extent(rec)) अणु
			अगर (le16_to_cpu(new_el->l_next_मुक्त_rec) <= 1) अणु
				bh = path_leaf_bh(right_path);
				eb = (काष्ठा ocfs2_extent_block *)bh->b_data;
				status = ocfs2_error(sb,
						"Extent block #%llu has an invalid l_next_free_rec of %d\n",
						(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(eb->h_blkno),
						le16_to_cpu(new_el->l_next_मुक्त_rec));
				जाओ मुक्त_right_path;
			पूर्ण
			rec = &new_el->l_recs[1];
		पूर्ण
	पूर्ण

	अगर (rec) अणु
		क्रमागत ocfs2_contig_type contig_type;

		contig_type = ocfs2_et_extent_contig(et, rec, split_rec);

		अगर (contig_type == CONTIG_LEFT && ret == CONTIG_RIGHT)
			ret = CONTIG_LEFTRIGHT;
		अन्यथा अगर (ret == CONTIG_NONE)
			ret = contig_type;
	पूर्ण

मुक्त_right_path:
	ocfs2_मुक्त_path(right_path);
मुक्त_left_path:
	ocfs2_मुक्त_path(left_path);
निकास:
	अगर (status == 0)
		ctxt->c_contig_type = ret;

	वापस status;
पूर्ण

अटल व्योम ocfs2_figure_contig_type(काष्ठा ocfs2_extent_tree *et,
				     काष्ठा ocfs2_insert_type *insert,
				     काष्ठा ocfs2_extent_list *el,
				     काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	पूर्णांक i;
	क्रमागत ocfs2_contig_type contig_type = CONTIG_NONE;

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	क्रम(i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++) अणु
		contig_type = ocfs2_et_extent_contig(et, &el->l_recs[i],
						     insert_rec);
		अगर (contig_type != CONTIG_NONE) अणु
			insert->ins_contig_index = i;
			अवरोध;
		पूर्ण
	पूर्ण
	insert->ins_contig = contig_type;

	अगर (insert->ins_contig != CONTIG_NONE) अणु
		काष्ठा ocfs2_extent_rec *rec =
				&el->l_recs[insert->ins_contig_index];
		अचिन्हित पूर्णांक len = le16_to_cpu(rec->e_leaf_clusters) +
				   le16_to_cpu(insert_rec->e_leaf_clusters);

		/*
		 * Caller might want us to limit the size of extents, करोn't
		 * calculate contiguousness अगर we might exceed that limit.
		 */
		अगर (et->et_max_leaf_clusters &&
		    (len > et->et_max_leaf_clusters))
			insert->ins_contig = CONTIG_NONE;
	पूर्ण
पूर्ण

/*
 * This should only be called against the righmost leaf extent list.
 *
 * ocfs2_figure_appending_type() will figure out whether we'll have to
 * insert at the tail of the righपंचांगost leaf.
 *
 * This should also work against the root extent list क्रम tree's with 0
 * depth. If we consider the root extent list to be the righपंचांगost leaf node
 * then the logic here makes sense.
 */
अटल व्योम ocfs2_figure_appending_type(काष्ठा ocfs2_insert_type *insert,
					काष्ठा ocfs2_extent_list *el,
					काष्ठा ocfs2_extent_rec *insert_rec)
अणु
	पूर्णांक i;
	u32 cpos = le32_to_cpu(insert_rec->e_cpos);
	काष्ठा ocfs2_extent_rec *rec;

	insert->ins_appending = APPEND_NONE;

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	अगर (!el->l_next_मुक्त_rec)
		जाओ set_tail_append;

	अगर (ocfs2_is_empty_extent(&el->l_recs[0])) अणु
		/* Were all records empty? */
		अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 1)
			जाओ set_tail_append;
	पूर्ण

	i = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
	rec = &el->l_recs[i];

	अगर (cpos >=
	    (le32_to_cpu(rec->e_cpos) + le16_to_cpu(rec->e_leaf_clusters)))
		जाओ set_tail_append;

	वापस;

set_tail_append:
	insert->ins_appending = APPEND_TAIL;
पूर्ण

/*
 * Helper function called at the beginning of an insert.
 *
 * This computes a few things that are commonly used in the process of
 * inserting पूर्णांकo the btree:
 *   - Whether the new extent is contiguous with an existing one.
 *   - The current tree depth.
 *   - Whether the insert is an appending one.
 *   - The total # of मुक्त records in the tree.
 *
 * All of the inक्रमmation is stored on the ocfs2_insert_type
 * काष्ठाure.
 */
अटल पूर्णांक ocfs2_figure_insert_type(काष्ठा ocfs2_extent_tree *et,
				    काष्ठा buffer_head **last_eb_bh,
				    काष्ठा ocfs2_extent_rec *insert_rec,
				    पूर्णांक *मुक्त_records,
				    काष्ठा ocfs2_insert_type *insert)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा buffer_head *bh = शून्य;

	insert->ins_split = SPLIT_NONE;

	el = et->et_root_el;
	insert->ins_tree_depth = le16_to_cpu(el->l_tree_depth);

	अगर (el->l_tree_depth) अणु
		/*
		 * If we have tree depth, we पढ़ो in the
		 * righपंचांगost extent block ahead of समय as
		 * ocfs2_figure_insert_type() and ocfs2_add_branch()
		 * may want it later.
		 */
		ret = ocfs2_पढ़ो_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		eb = (काष्ठा ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;
	पूर्ण

	/*
	 * Unless we have a contiguous insert, we'll need to know अगर
	 * there is room left in our allocation tree क्रम another
	 * extent record.
	 *
	 * XXX: This test is simplistic, we can search क्रम empty
	 * extent records too.
	 */
	*मुक्त_records = le16_to_cpu(el->l_count) -
		le16_to_cpu(el->l_next_मुक्त_rec);

	अगर (!insert->ins_tree_depth) अणु
		ocfs2_figure_contig_type(et, insert, el, insert_rec);
		ocfs2_figure_appending_type(insert, el, insert_rec);
		वापस 0;
	पूर्ण

	path = ocfs2_new_path_from_et(et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * In the हाल that we're inserting past what the tree
	 * currently accounts क्रम, ocfs2_find_path() will वापस क्रम
	 * us the righपंचांगost tree path. This is accounted क्रम below in
	 * the appending code.
	 */
	ret = ocfs2_find_path(et->et_ci, path, le32_to_cpu(insert_rec->e_cpos));
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	el = path_leaf_el(path);

	/*
	 * Now that we have the path, there's two things we want to determine:
	 * 1) Contiguousness (also set contig_index अगर this is so)
	 *
	 * 2) Are we करोing an append? We can trivially अवरोध this up
         *     पूर्णांकo two types of appends: simple record append, or a
         *     rotate inside the tail leaf.
	 */
	ocfs2_figure_contig_type(et, insert, el, insert_rec);

	/*
	 * The insert code isn't quite पढ़ोy to deal with all हालs of
	 * left contiguousness. Specअगरically, अगर it's an insert पूर्णांकo
	 * the 1st record in a leaf, it will require the adjusपंचांगent of
	 * cluster count on the last record of the path directly to it's
	 * left. For now, just catch that हाल and fool the layers
	 * above us. This works just fine क्रम tree_depth == 0, which
	 * is why we allow that above.
	 */
	अगर (insert->ins_contig == CONTIG_LEFT &&
	    insert->ins_contig_index == 0)
		insert->ins_contig = CONTIG_NONE;

	/*
	 * Ok, so we can simply compare against last_eb to figure out
	 * whether the path करोesn't exist. This will only happen in
	 * the हाल that we're करोing a tail append, so maybe we can
	 * take advantage of that inक्रमmation somehow.
	 */
	अगर (ocfs2_et_get_last_eb_blk(et) ==
	    path_leaf_bh(path)->b_blocknr) अणु
		/*
		 * Ok, ocfs2_find_path() वापसed us the righपंचांगost
		 * tree path. This might be an appending insert. There are
		 * two हालs:
		 *    1) We're करोing a true append at the tail:
		 *	-This might even be off the end of the leaf
		 *    2) We're "appending" by rotating in the tail
		 */
		ocfs2_figure_appending_type(insert, el, insert_rec);
	पूर्ण

out:
	ocfs2_मुक्त_path(path);

	अगर (ret == 0)
		*last_eb_bh = bh;
	अन्यथा
		brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * Insert an extent पूर्णांकo a btree.
 *
 * The caller needs to update the owning btree's cluster count.
 */
पूर्णांक ocfs2_insert_extent(handle_t *handle,
			काष्ठा ocfs2_extent_tree *et,
			u32 cpos,
			u64 start_blk,
			u32 new_clusters,
			u8 flags,
			काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक status;
	पूर्णांक मुक्त_records;
	काष्ठा buffer_head *last_eb_bh = शून्य;
	काष्ठा ocfs2_insert_type insert = अणु0, पूर्ण;
	काष्ठा ocfs2_extent_rec rec;

	trace_ocfs2_insert_extent_start(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		cpos, new_clusters);

	स_रखो(&rec, 0, माप(rec));
	rec.e_cpos = cpu_to_le32(cpos);
	rec.e_blkno = cpu_to_le64(start_blk);
	rec.e_leaf_clusters = cpu_to_le16(new_clusters);
	rec.e_flags = flags;
	status = ocfs2_et_insert_check(et, &rec);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_figure_insert_type(et, &last_eb_bh, &rec,
					  &मुक्त_records, &insert);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_insert_extent(insert.ins_appending, insert.ins_contig,
				  insert.ins_contig_index, मुक्त_records,
				  insert.ins_tree_depth);

	अगर (insert.ins_contig == CONTIG_NONE && मुक्त_records == 0) अणु
		status = ocfs2_grow_tree(handle, et,
					 &insert.ins_tree_depth, &last_eb_bh,
					 meta_ac);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Finally, we can add clusters. This might rotate the tree क्रम us. */
	status = ocfs2_करो_insert_extent(handle, et, &rec, &insert);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	अन्यथा
		ocfs2_et_extent_map_insert(et, &rec);

bail:
	brअन्यथा(last_eb_bh);

	वापस status;
पूर्ण

/*
 * Allcate and add clusters पूर्णांकo the extent b-tree.
 * The new clusters(clusters_to_add) will be inserted at logical_offset.
 * The extent b-tree's root is specअगरied by et, and
 * it is not limited to the file storage. Any extent tree can use this
 * function अगर it implements the proper ocfs2_extent_tree.
 */
पूर्णांक ocfs2_add_clusters_in_btree(handle_t *handle,
				काष्ठा ocfs2_extent_tree *et,
				u32 *logical_offset,
				u32 clusters_to_add,
				पूर्णांक mark_unwritten,
				काष्ठा ocfs2_alloc_context *data_ac,
				काष्ठा ocfs2_alloc_context *meta_ac,
				क्रमागत ocfs2_alloc_restarted *reason_ret)
अणु
	पूर्णांक status = 0, err = 0;
	पूर्णांक need_मुक्त = 0;
	पूर्णांक मुक्त_extents;
	क्रमागत ocfs2_alloc_restarted reason = RESTART_NONE;
	u32 bit_off, num_bits;
	u64 block;
	u8 flags = 0;
	काष्ठा ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(et->et_ci));

	BUG_ON(!clusters_to_add);

	अगर (mark_unwritten)
		flags = OCFS2_EXT_UNWRITTEN;

	मुक्त_extents = ocfs2_num_मुक्त_extents(et);
	अगर (मुक्त_extents < 0) अणु
		status = मुक्त_extents;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* there are two हालs which could cause us to EAGAIN in the
	 * we-need-more-metadata हाल:
	 * 1) we haven't reserved *any*
	 * 2) we are so fragmented, we've needed to add metadata too
	 *    many बार. */
	अगर (!मुक्त_extents && !meta_ac) अणु
		err = -1;
		status = -EAGAIN;
		reason = RESTART_META;
		जाओ leave;
	पूर्ण अन्यथा अगर ((!मुक्त_extents)
		   && (ocfs2_alloc_context_bits_left(meta_ac)
		       < ocfs2_extend_meta_needed(et->et_root_el))) अणु
		err = -2;
		status = -EAGAIN;
		reason = RESTART_META;
		जाओ leave;
	पूर्ण

	status = __ocfs2_claim_clusters(handle, data_ac, 1,
					clusters_to_add, &bit_off, &num_bits);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	BUG_ON(num_bits > clusters_to_add);

	/* reserve our ग_लिखो early -- insert_extent may update the tree root */
	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		need_मुक्त = 1;
		जाओ bail;
	पूर्ण

	block = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_add_clusters_in_btree(
	     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
	     bit_off, num_bits);
	status = ocfs2_insert_extent(handle, et, *logical_offset, block,
				     num_bits, flags, meta_ac);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		need_मुक्त = 1;
		जाओ bail;
	पूर्ण

	ocfs2_journal_dirty(handle, et->et_root_bh);

	clusters_to_add -= num_bits;
	*logical_offset += num_bits;

	अगर (clusters_to_add) अणु
		err = clusters_to_add;
		status = -EAGAIN;
		reason = RESTART_TRANS;
	पूर्ण

bail:
	अगर (need_मुक्त) अणु
		अगर (data_ac->ac_which == OCFS2_AC_USE_LOCAL)
			ocfs2_मुक्त_local_alloc_bits(osb, handle, data_ac,
					bit_off, num_bits);
		अन्यथा
			ocfs2_मुक्त_clusters(handle,
					data_ac->ac_inode,
					data_ac->ac_bh,
					ocfs2_clusters_to_blocks(osb->sb, bit_off),
					num_bits);
	पूर्ण

leave:
	अगर (reason_ret)
		*reason_ret = reason;
	trace_ocfs2_add_clusters_in_btree_ret(status, reason, err);
	वापस status;
पूर्ण

अटल व्योम ocfs2_make_right_split_rec(काष्ठा super_block *sb,
				       काष्ठा ocfs2_extent_rec *split_rec,
				       u32 cpos,
				       काष्ठा ocfs2_extent_rec *rec)
अणु
	u32 rec_cpos = le32_to_cpu(rec->e_cpos);
	u32 rec_range = rec_cpos + le16_to_cpu(rec->e_leaf_clusters);

	स_रखो(split_rec, 0, माप(काष्ठा ocfs2_extent_rec));

	split_rec->e_cpos = cpu_to_le32(cpos);
	split_rec->e_leaf_clusters = cpu_to_le16(rec_range - cpos);

	split_rec->e_blkno = rec->e_blkno;
	le64_add_cpu(&split_rec->e_blkno,
		     ocfs2_clusters_to_blocks(sb, cpos - rec_cpos));

	split_rec->e_flags = rec->e_flags;
पूर्ण

अटल पूर्णांक ocfs2_split_and_insert(handle_t *handle,
				  काष्ठा ocfs2_extent_tree *et,
				  काष्ठा ocfs2_path *path,
				  काष्ठा buffer_head **last_eb_bh,
				  पूर्णांक split_index,
				  काष्ठा ocfs2_extent_rec *orig_split_rec,
				  काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret = 0, depth;
	अचिन्हित पूर्णांक insert_range, rec_range, करो_leftright = 0;
	काष्ठा ocfs2_extent_rec पंचांगprec;
	काष्ठा ocfs2_extent_list *righपंचांगost_el;
	काष्ठा ocfs2_extent_rec rec;
	काष्ठा ocfs2_extent_rec split_rec = *orig_split_rec;
	काष्ठा ocfs2_insert_type insert;
	काष्ठा ocfs2_extent_block *eb;

leftright:
	/*
	 * Store a copy of the record on the stack - it might move
	 * around as the tree is manipulated below.
	 */
	rec = path_leaf_el(path)->l_recs[split_index];

	righपंचांगost_el = et->et_root_el;

	depth = le16_to_cpu(righपंचांगost_el->l_tree_depth);
	अगर (depth) अणु
		BUG_ON(!(*last_eb_bh));
		eb = (काष्ठा ocfs2_extent_block *) (*last_eb_bh)->b_data;
		righपंचांगost_el = &eb->h_list;
	पूर्ण

	अगर (le16_to_cpu(righपंचांगost_el->l_next_मुक्त_rec) ==
	    le16_to_cpu(righपंचांगost_el->l_count)) अणु
		ret = ocfs2_grow_tree(handle, et,
				      &depth, last_eb_bh, meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	स_रखो(&insert, 0, माप(काष्ठा ocfs2_insert_type));
	insert.ins_appending = APPEND_NONE;
	insert.ins_contig = CONTIG_NONE;
	insert.ins_tree_depth = depth;

	insert_range = le32_to_cpu(split_rec.e_cpos) +
		le16_to_cpu(split_rec.e_leaf_clusters);
	rec_range = le32_to_cpu(rec.e_cpos) +
		le16_to_cpu(rec.e_leaf_clusters);

	अगर (split_rec.e_cpos == rec.e_cpos) अणु
		insert.ins_split = SPLIT_LEFT;
	पूर्ण अन्यथा अगर (insert_range == rec_range) अणु
		insert.ins_split = SPLIT_RIGHT;
	पूर्ण अन्यथा अणु
		/*
		 * Left/right split. We fake this as a right split
		 * first and then make a second pass as a left split.
		 */
		insert.ins_split = SPLIT_RIGHT;

		ocfs2_make_right_split_rec(ocfs2_metadata_cache_get_super(et->et_ci),
					   &पंचांगprec, insert_range, &rec);

		split_rec = पंचांगprec;

		BUG_ON(करो_leftright);
		करो_leftright = 1;
	पूर्ण

	ret = ocfs2_करो_insert_extent(handle, et, &split_rec, &insert);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (करो_leftright == 1) अणु
		u32 cpos;
		काष्ठा ocfs2_extent_list *el;

		करो_leftright++;
		split_rec = *orig_split_rec;

		ocfs2_reinit_path(path, 1);

		cpos = le32_to_cpu(split_rec.e_cpos);
		ret = ocfs2_find_path(et->et_ci, path, cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		el = path_leaf_el(path);
		split_index = ocfs2_search_extent_list(el, cpos);
		अगर (split_index == -1) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu has an extent at cpos %u which can no longer be found\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
				    cpos);
			ret = -EROFS;
			जाओ out;
		पूर्ण
		जाओ leftright;
	पूर्ण
out:

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_replace_extent_rec(handle_t *handle,
				    काष्ठा ocfs2_extent_tree *et,
				    काष्ठा ocfs2_path *path,
				    काष्ठा ocfs2_extent_list *el,
				    पूर्णांक split_index,
				    काष्ठा ocfs2_extent_rec *split_rec)
अणु
	पूर्णांक ret;

	ret = ocfs2_path_bh_journal_access(handle, et->et_ci, path,
					   path_num_items(path) - 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	el->l_recs[split_index] = *split_rec;

	ocfs2_journal_dirty(handle, path_leaf_bh(path));
out:
	वापस ret;
पूर्ण

/*
 * Split part or all of the extent record at split_index in the leaf
 * poपूर्णांकed to by path. Merge with the contiguous extent record अगर needed.
 *
 * Care is taken to handle contiguousness so as to not grow the tree.
 *
 * meta_ac is not strictly necessary - we only truly need it अगर growth
 * of the tree is required. All other हालs will degrade पूर्णांकo a less
 * optimal tree layout.
 *
 * last_eb_bh should be the righपंचांगost leaf block क्रम any extent
 * btree. Since a split may grow the tree or a merge might shrink it,
 * the caller cannot trust the contents of that buffer after this call.
 *
 * This code is optimized क्रम पढ़ोability - several passes might be
 * made over certain portions of the tree. All of those blocks will
 * have been brought पूर्णांकo cache (and pinned via the journal), so the
 * extra overhead is not expressed in terms of disk पढ़ोs.
 */
पूर्णांक ocfs2_split_extent(handle_t *handle,
		       काष्ठा ocfs2_extent_tree *et,
		       काष्ठा ocfs2_path *path,
		       पूर्णांक split_index,
		       काष्ठा ocfs2_extent_rec *split_rec,
		       काष्ठा ocfs2_alloc_context *meta_ac,
		       काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_extent_list *el = path_leaf_el(path);
	काष्ठा buffer_head *last_eb_bh = शून्य;
	काष्ठा ocfs2_extent_rec *rec = &el->l_recs[split_index];
	काष्ठा ocfs2_merge_ctxt ctxt;

	अगर (le32_to_cpu(rec->e_cpos) > le32_to_cpu(split_rec->e_cpos) ||
	    ((le32_to_cpu(rec->e_cpos) + le16_to_cpu(rec->e_leaf_clusters)) <
	     (le32_to_cpu(split_rec->e_cpos) + le16_to_cpu(split_rec->e_leaf_clusters)))) अणु
		ret = -EIO;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_figure_merge_contig_type(et, path, el,
					     split_index,
					     split_rec,
					     &ctxt);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * The core merge / split code wants to know how much room is
	 * left in this allocation tree, so we pass the
	 * righपंचांगost extent list.
	 */
	अगर (path->p_tree_depth) अणु
		ret = ocfs2_पढ़ो_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &last_eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rec->e_cpos == split_rec->e_cpos &&
	    rec->e_leaf_clusters == split_rec->e_leaf_clusters)
		ctxt.c_split_covers_rec = 1;
	अन्यथा
		ctxt.c_split_covers_rec = 0;

	ctxt.c_has_empty_extent = ocfs2_is_empty_extent(&el->l_recs[0]);

	trace_ocfs2_split_extent(split_index, ctxt.c_contig_type,
				 ctxt.c_has_empty_extent,
				 ctxt.c_split_covers_rec);

	अगर (ctxt.c_contig_type == CONTIG_NONE) अणु
		अगर (ctxt.c_split_covers_rec)
			ret = ocfs2_replace_extent_rec(handle, et, path, el,
						       split_index, split_rec);
		अन्यथा
			ret = ocfs2_split_and_insert(handle, et, path,
						     &last_eb_bh, split_index,
						     split_rec, meta_ac);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण अन्यथा अणु
		ret = ocfs2_try_to_merge_extent(handle, et, path,
						split_index, split_rec,
						dealloc, &ctxt);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out:
	brअन्यथा(last_eb_bh);
	वापस ret;
पूर्ण

/*
 * Change the flags of the alपढ़ोy-existing extent at cpos क्रम len clusters.
 *
 * new_flags: the flags we want to set.
 * clear_flags: the flags we want to clear.
 * phys: the new physical offset we want this new extent starts from.
 *
 * If the existing extent is larger than the request, initiate a
 * split. An attempt will be made at merging with adjacent extents.
 *
 * The caller is responsible क्रम passing करोwn meta_ac अगर we'll need it.
 */
पूर्णांक ocfs2_change_extent_flag(handle_t *handle,
			     काष्ठा ocfs2_extent_tree *et,
			     u32 cpos, u32 len, u32 phys,
			     काष्ठा ocfs2_alloc_context *meta_ac,
			     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			     पूर्णांक new_flags, पूर्णांक clear_flags)
अणु
	पूर्णांक ret, index;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	u64 start_blkno = ocfs2_clusters_to_blocks(sb, phys);
	काष्ठा ocfs2_extent_rec split_rec;
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;

	left_path = ocfs2_new_path_from_et(et);
	अगर (!left_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, left_path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	el = path_leaf_el(left_path);

	index = ocfs2_search_extent_list(el, cpos);
	अगर (index == -1) अणु
		ocfs2_error(sb,
			    "Owner %llu has an extent at cpos %u which can no longer be found\n",
			    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
			    cpos);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	ret = -EIO;
	rec = &el->l_recs[index];
	अगर (new_flags && (rec->e_flags & new_flags)) अणु
		mlog(ML_ERROR, "Owner %llu tried to set %d flags on an "
		     "extent that already had them\n",
		     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		     new_flags);
		जाओ out;
	पूर्ण

	अगर (clear_flags && !(rec->e_flags & clear_flags)) अणु
		mlog(ML_ERROR, "Owner %llu tried to clear %d flags on an "
		     "extent that didn't have them\n",
		     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		     clear_flags);
		जाओ out;
	पूर्ण

	स_रखो(&split_rec, 0, माप(काष्ठा ocfs2_extent_rec));
	split_rec.e_cpos = cpu_to_le32(cpos);
	split_rec.e_leaf_clusters = cpu_to_le16(len);
	split_rec.e_blkno = cpu_to_le64(start_blkno);
	split_rec.e_flags = rec->e_flags;
	अगर (new_flags)
		split_rec.e_flags |= new_flags;
	अगर (clear_flags)
		split_rec.e_flags &= ~clear_flags;

	ret = ocfs2_split_extent(handle, et, left_path,
				 index, &split_rec, meta_ac,
				 dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	ocfs2_मुक्त_path(left_path);
	वापस ret;

पूर्ण

/*
 * Mark the alपढ़ोy-existing extent at cpos as written क्रम len clusters.
 * This हटाओs the unwritten extent flag.
 *
 * If the existing extent is larger than the request, initiate a
 * split. An attempt will be made at merging with adjacent extents.
 *
 * The caller is responsible क्रम passing करोwn meta_ac अगर we'll need it.
 */
पूर्णांक ocfs2_mark_extent_written(काष्ठा inode *inode,
			      काष्ठा ocfs2_extent_tree *et,
			      handle_t *handle, u32 cpos, u32 len, u32 phys,
			      काष्ठा ocfs2_alloc_context *meta_ac,
			      काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret;

	trace_ocfs2_mark_extent_written(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		cpos, len, phys);

	अगर (!ocfs2_ग_लिखोs_unwritten_extents(OCFS2_SB(inode->i_sb))) अणु
		ocfs2_error(inode->i_sb, "Inode %llu has unwritten extents that are being written to, but the feature bit is not set in the super block\n",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	/*
	 * XXX: This should be fixed up so that we just re-insert the
	 * next extent records.
	 */
	ocfs2_et_extent_map_truncate(et, 0);

	ret = ocfs2_change_extent_flag(handle, et, cpos,
				       len, phys, meta_ac, dealloc,
				       0, OCFS2_EXT_UNWRITTEN);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_split_tree(handle_t *handle, काष्ठा ocfs2_extent_tree *et,
			    काष्ठा ocfs2_path *path,
			    पूर्णांक index, u32 new_range,
			    काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret, depth, credits;
	काष्ठा buffer_head *last_eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *righपंचांगost_el, *el;
	काष्ठा ocfs2_extent_rec split_rec;
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_insert_type insert;

	/*
	 * Setup the record to split beक्रमe we grow the tree.
	 */
	el = path_leaf_el(path);
	rec = &el->l_recs[index];
	ocfs2_make_right_split_rec(ocfs2_metadata_cache_get_super(et->et_ci),
				   &split_rec, new_range, rec);

	depth = path->p_tree_depth;
	अगर (depth > 0) अणु
		ret = ocfs2_पढ़ो_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &last_eb_bh);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) last_eb_bh->b_data;
		righपंचांगost_el = &eb->h_list;
	पूर्ण अन्यथा
		righपंचांगost_el = path_leaf_el(path);

	credits = path->p_tree_depth +
		  ocfs2_extend_meta_needed(et->et_root_el);
	ret = ocfs2_extend_trans(handle, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(righपंचांगost_el->l_next_मुक्त_rec) ==
	    le16_to_cpu(righपंचांगost_el->l_count)) अणु
		ret = ocfs2_grow_tree(handle, et, &depth, &last_eb_bh,
				      meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	स_रखो(&insert, 0, माप(काष्ठा ocfs2_insert_type));
	insert.ins_appending = APPEND_NONE;
	insert.ins_contig = CONTIG_NONE;
	insert.ins_split = SPLIT_RIGHT;
	insert.ins_tree_depth = depth;

	ret = ocfs2_करो_insert_extent(handle, et, &split_rec, &insert);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	brअन्यथा(last_eb_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_truncate_rec(handle_t *handle,
			      काष्ठा ocfs2_extent_tree *et,
			      काष्ठा ocfs2_path *path, पूर्णांक index,
			      काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			      u32 cpos, u32 len)
अणु
	पूर्णांक ret;
	u32 left_cpos, rec_range, trunc_range;
	पूर्णांक is_righपंचांगost_tree_rec = 0;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	काष्ठा ocfs2_path *left_path = शून्य;
	काष्ठा ocfs2_extent_list *el = path_leaf_el(path);
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_extent_block *eb;

	अगर (ocfs2_is_empty_extent(&el->l_recs[0]) && index > 0) अणु
		/* extend credit क्रम ocfs2_हटाओ_righपंचांगost_path */
		ret = ocfs2_extend_rotate_transaction(handle, 0,
				jbd2_handle_buffer_credits(handle),
				path);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		index--;
	पूर्ण

	अगर (index == (le16_to_cpu(el->l_next_मुक्त_rec) - 1) &&
	    path->p_tree_depth) अणु
		/*
		 * Check whether this is the righपंचांगost tree record. If
		 * we हटाओ all of this record or part of its right
		 * edge then an update of the record lengths above it
		 * will be required.
		 */
		eb = (काष्ठा ocfs2_extent_block *)path_leaf_bh(path)->b_data;
		अगर (eb->h_next_leaf_blk == 0)
			is_righपंचांगost_tree_rec = 1;
	पूर्ण

	rec = &el->l_recs[index];
	अगर (index == 0 && path->p_tree_depth &&
	    le32_to_cpu(rec->e_cpos) == cpos) अणु
		/*
		 * Changing the lefपंचांगost offset (via partial or whole
		 * record truncate) of an पूर्णांकerior (or righपंचांगost) path
		 * means we have to update the subtree that is क्रमmed
		 * by this leaf and the one to it's left.
		 *
		 * There are two हालs we can skip:
		 *   1) Path is the lefपंचांगost one in our btree.
		 *   2) The leaf is righपंचांगost and will be empty after
		 *      we हटाओ the extent record - the rotate code
		 *      knows how to update the newly क्रमmed edge.
		 */

		ret = ocfs2_find_cpos_क्रम_left_leaf(sb, path, &left_cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (left_cpos && le16_to_cpu(el->l_next_मुक्त_rec) > 1) अणु
			left_path = ocfs2_new_path_from_path(path);
			अगर (!left_path) अणु
				ret = -ENOMEM;
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_find_path(et->et_ci, left_path,
					      left_cpos);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = ocfs2_extend_rotate_transaction(handle, 0,
					jbd2_handle_buffer_credits(handle),
					path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_path(et->et_ci, handle, path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	rec_range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	trunc_range = cpos + len;

	अगर (le32_to_cpu(rec->e_cpos) == cpos && rec_range == trunc_range) अणु
		पूर्णांक next_मुक्त;

		स_रखो(rec, 0, माप(*rec));
		ocfs2_cleanup_merge(el, index);

		next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);
		अगर (is_righपंचांगost_tree_rec && next_मुक्त > 1) अणु
			/*
			 * We skip the edge update अगर this path will
			 * be deleted by the rotate code.
			 */
			rec = &el->l_recs[next_मुक्त - 1];
			ocfs2_adjust_righपंचांगost_records(handle, et, path,
						       rec);
		पूर्ण
	पूर्ण अन्यथा अगर (le32_to_cpu(rec->e_cpos) == cpos) अणु
		/* Remove lefपंचांगost portion of the record. */
		le32_add_cpu(&rec->e_cpos, len);
		le64_add_cpu(&rec->e_blkno, ocfs2_clusters_to_blocks(sb, len));
		le16_add_cpu(&rec->e_leaf_clusters, -len);
	पूर्ण अन्यथा अगर (rec_range == trunc_range) अणु
		/* Remove righपंचांगost portion of the record */
		le16_add_cpu(&rec->e_leaf_clusters, -len);
		अगर (is_righपंचांगost_tree_rec)
			ocfs2_adjust_righपंचांगost_records(handle, et, path, rec);
	पूर्ण अन्यथा अणु
		/* Caller should have trapped this. */
		mlog(ML_ERROR, "Owner %llu: Invalid record truncate: (%u, %u) "
		     "(%u, %u)\n",
		     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		     le32_to_cpu(rec->e_cpos),
		     le16_to_cpu(rec->e_leaf_clusters), cpos, len);
		BUG();
	पूर्ण

	अगर (left_path) अणु
		पूर्णांक subtree_index;

		subtree_index = ocfs2_find_subtree_root(et, left_path, path);
		ocfs2_complete_edge_insert(handle, left_path, path,
					   subtree_index);
	पूर्ण

	ocfs2_journal_dirty(handle, path_leaf_bh(path));

	ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	ocfs2_मुक्त_path(left_path);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_हटाओ_extent(handle_t *handle,
			काष्ठा ocfs2_extent_tree *et,
			u32 cpos, u32 len,
			काष्ठा ocfs2_alloc_context *meta_ac,
			काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret, index;
	u32 rec_range, trunc_range;
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_path *path = शून्य;

	/*
	 * XXX: Why are we truncating to 0 instead of wherever this
	 * affects us?
	 */
	ocfs2_et_extent_map_truncate(et, 0);

	path = ocfs2_new_path_from_et(et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	el = path_leaf_el(path);
	index = ocfs2_search_extent_list(el, cpos);
	अगर (index == -1) अणु
		ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
			    "Owner %llu has an extent at cpos %u which can no longer be found\n",
			    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
			    cpos);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	/*
	 * We have 3 हालs of extent removal:
	 *   1) Range covers the entire extent rec
	 *   2) Range begins or ends on one edge of the extent rec
	 *   3) Range is in the middle of the extent rec (no shared edges)
	 *
	 * For हाल 1 we हटाओ the extent rec and left rotate to
	 * fill the hole.
	 *
	 * For हाल 2 we just shrink the existing extent rec, with a
	 * tree update अगर the shrinking edge is also the edge of an
	 * extent block.
	 *
	 * For हाल 3 we करो a right split to turn the extent rec पूर्णांकo
	 * something हाल 2 can handle.
	 */
	rec = &el->l_recs[index];
	rec_range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	trunc_range = cpos + len;

	BUG_ON(cpos < le32_to_cpu(rec->e_cpos) || trunc_range > rec_range);

	trace_ocfs2_हटाओ_extent(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
		cpos, len, index, le32_to_cpu(rec->e_cpos),
		ocfs2_rec_clusters(el, rec));

	अगर (le32_to_cpu(rec->e_cpos) == cpos || rec_range == trunc_range) अणु
		ret = ocfs2_truncate_rec(handle, et, path, index, dealloc,
					 cpos, len);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ocfs2_split_tree(handle, et, path, index,
				       trunc_range, meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * The split could have manipulated the tree enough to
		 * move the record location, so we have to look क्रम it again.
		 */
		ocfs2_reinit_path(path, 1);

		ret = ocfs2_find_path(et->et_ci, path, cpos);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		el = path_leaf_el(path);
		index = ocfs2_search_extent_list(el, cpos);
		अगर (index == -1) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu: split at cpos %u lost record\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
				    cpos);
			ret = -EROFS;
			जाओ out;
		पूर्ण

		/*
		 * Double check our values here. If anything is fishy,
		 * it's easier to catch it at the top level.
		 */
		rec = &el->l_recs[index];
		rec_range = le32_to_cpu(rec->e_cpos) +
			ocfs2_rec_clusters(el, rec);
		अगर (rec_range != trunc_range) अणु
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu: error after split at cpos %u trunc len %u, existing record is (%u,%u)\n",
				    (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(et->et_ci),
				    cpos, len, le32_to_cpu(rec->e_cpos),
				    ocfs2_rec_clusters(el, rec));
			ret = -EROFS;
			जाओ out;
		पूर्ण

		ret = ocfs2_truncate_rec(handle, et, path, index, dealloc,
					 cpos, len);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out:
	ocfs2_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * ocfs2_reserve_blocks_क्रम_rec_trunc() would look basically the
 * same as ocfs2_lock_alloctors(), except क्रम it accepts a blocks
 * number to reserve some extra blocks, and it only handles meta
 * data allocations.
 *
 * Currently, only ocfs2_हटाओ_btree_range() uses it क्रम truncating
 * and punching holes.
 */
अटल पूर्णांक ocfs2_reserve_blocks_क्रम_rec_trunc(काष्ठा inode *inode,
					      काष्ठा ocfs2_extent_tree *et,
					      u32 extents_to_split,
					      काष्ठा ocfs2_alloc_context **ac,
					      पूर्णांक extra_blocks)
अणु
	पूर्णांक ret = 0, num_मुक्त_extents;
	अचिन्हित पूर्णांक max_recs_needed = 2 * extents_to_split;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	*ac = शून्य;

	num_मुक्त_extents = ocfs2_num_मुक्त_extents(et);
	अगर (num_मुक्त_extents < 0) अणु
		ret = num_मुक्त_extents;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!num_मुक्त_extents ||
	    (ocfs2_sparse_alloc(osb) && num_मुक्त_extents < max_recs_needed))
		extra_blocks += ocfs2_extend_meta_needed(et->et_root_el);

	अगर (extra_blocks) अणु
		ret = ocfs2_reserve_new_metadata_blocks(osb, extra_blocks, ac);
		अगर (ret < 0) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
		पूर्ण
	पूर्ण

out:
	अगर (ret) अणु
		अगर (*ac) अणु
			ocfs2_मुक्त_alloc_context(*ac);
			*ac = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_हटाओ_btree_range(काष्ठा inode *inode,
			     काष्ठा ocfs2_extent_tree *et,
			     u32 cpos, u32 phys_cpos, u32 len, पूर्णांक flags,
			     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			     u64 refcount_loc, bool refcount_tree_locked)
अणु
	पूर्णांक ret, credits = 0, extra_blocks = 0;
	u64 phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;

	अगर ((flags & OCFS2_EXT_REFCOUNTED) && len) अणु
		BUG_ON(!ocfs2_is_refcount_inode(inode));

		अगर (!refcount_tree_locked) अणु
			ret = ocfs2_lock_refcount_tree(osb, refcount_loc, 1,
						       &ref_tree, शून्य);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ bail;
			पूर्ण
		पूर्ण

		ret = ocfs2_prepare_refcount_change_क्रम_del(inode,
							    refcount_loc,
							    phys_blkno,
							    len,
							    &credits,
							    &extra_blocks);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ bail;
		पूर्ण
	पूर्ण

	ret = ocfs2_reserve_blocks_क्रम_rec_trunc(inode, et, 1, &meta_ac,
						 extra_blocks);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	inode_lock(tl_inode);

	अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
		ret = __ocfs2_flush_truncate_log(osb);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	handle = ocfs2_start_trans(osb,
			ocfs2_हटाओ_extent_credits(osb->sb) + credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_et_root_journal_access(handle, et,
					   OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	dquot_मुक्त_space_nodirty(inode,
				  ocfs2_clusters_to_bytes(inode->i_sb, len));

	ret = ocfs2_हटाओ_extent(handle, et, cpos, len, meta_ac, dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ocfs2_et_update_clusters(et, -len);
	ocfs2_update_inode_fsync_trans(handle, inode, 1);

	ocfs2_journal_dirty(handle, et->et_root_bh);

	अगर (phys_blkno) अणु
		अगर (flags & OCFS2_EXT_REFCOUNTED)
			ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(osb->sb,
								 phys_blkno),
					len, meta_ac,
					dealloc, 1);
		अन्यथा
			ret = ocfs2_truncate_log_append(osb, handle,
							phys_blkno, len);
		अगर (ret)
			mlog_त्रुटि_सं(ret);

	पूर्ण

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	inode_unlock(tl_inode);
bail:
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_truncate_log_needs_flush(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा buffer_head *tl_bh = osb->osb_tl_bh;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_truncate_log *tl;

	di = (काष्ठा ocfs2_dinode *) tl_bh->b_data;
	tl = &di->id2.i_dealloc;

	mlog_bug_on_msg(le16_to_cpu(tl->tl_used) > le16_to_cpu(tl->tl_count),
			"slot %d, invalid truncate log parameters: used = "
			"%u, count = %u\n", osb->slot_num,
			le16_to_cpu(tl->tl_used), le16_to_cpu(tl->tl_count));
	वापस le16_to_cpu(tl->tl_used) == le16_to_cpu(tl->tl_count);
पूर्ण

अटल पूर्णांक ocfs2_truncate_log_can_coalesce(काष्ठा ocfs2_truncate_log *tl,
					   अचिन्हित पूर्णांक new_start)
अणु
	अचिन्हित पूर्णांक tail_index;
	अचिन्हित पूर्णांक current_tail;

	/* No records, nothing to coalesce */
	अगर (!le16_to_cpu(tl->tl_used))
		वापस 0;

	tail_index = le16_to_cpu(tl->tl_used) - 1;
	current_tail = le32_to_cpu(tl->tl_recs[tail_index].t_start);
	current_tail += le32_to_cpu(tl->tl_recs[tail_index].t_clusters);

	वापस current_tail == new_start;
पूर्ण

पूर्णांक ocfs2_truncate_log_append(काष्ठा ocfs2_super *osb,
			      handle_t *handle,
			      u64 start_blk,
			      अचिन्हित पूर्णांक num_clusters)
अणु
	पूर्णांक status, index;
	अचिन्हित पूर्णांक start_cluster, tl_count;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा buffer_head *tl_bh = osb->osb_tl_bh;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_truncate_log *tl;

	BUG_ON(inode_trylock(tl_inode));

	start_cluster = ocfs2_blocks_to_clusters(osb->sb, start_blk);

	di = (काष्ठा ocfs2_dinode *) tl_bh->b_data;

	/* tl_bh is loaded from ocfs2_truncate_log_init().  It's validated
	 * by the underlying call to ocfs2_पढ़ो_inode_block(), so any
	 * corruption is a code bug */
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	tl = &di->id2.i_dealloc;
	tl_count = le16_to_cpu(tl->tl_count);
	mlog_bug_on_msg(tl_count > ocfs2_truncate_recs_per_inode(osb->sb) ||
			tl_count == 0,
			"Truncate record count on #%llu invalid "
			"wanted %u, actual %u\n",
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(tl_inode)->ip_blkno,
			ocfs2_truncate_recs_per_inode(osb->sb),
			le16_to_cpu(tl->tl_count));

	/* Caller should have known to flush beक्रमe calling us. */
	index = le16_to_cpu(tl->tl_used);
	अगर (index >= tl_count) अणु
		status = -ENOSPC;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(tl_inode), tl_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_truncate_log_append(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(tl_inode)->ip_blkno, index,
		start_cluster, num_clusters);
	अगर (ocfs2_truncate_log_can_coalesce(tl, start_cluster)) अणु
		/*
		 * Move index back to the record we are coalescing with.
		 * ocfs2_truncate_log_can_coalesce() guarantees nonzero
		 */
		index--;

		num_clusters += le32_to_cpu(tl->tl_recs[index].t_clusters);
		trace_ocfs2_truncate_log_append(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(tl_inode)->ip_blkno,
			index, le32_to_cpu(tl->tl_recs[index].t_start),
			num_clusters);
	पूर्ण अन्यथा अणु
		tl->tl_recs[index].t_start = cpu_to_le32(start_cluster);
		tl->tl_used = cpu_to_le16(index + 1);
	पूर्ण
	tl->tl_recs[index].t_clusters = cpu_to_le32(num_clusters);

	ocfs2_journal_dirty(handle, tl_bh);

	osb->truncated_clusters += num_clusters;
bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_replay_truncate_records(काष्ठा ocfs2_super *osb,
					 काष्ठा inode *data_alloc_inode,
					 काष्ठा buffer_head *data_alloc_bh)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	अचिन्हित पूर्णांक num_clusters;
	u64 start_blk;
	काष्ठा ocfs2_truncate_rec rec;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_truncate_log *tl;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा buffer_head *tl_bh = osb->osb_tl_bh;
	handle_t *handle;

	di = (काष्ठा ocfs2_dinode *) tl_bh->b_data;
	tl = &di->id2.i_dealloc;
	i = le16_to_cpu(tl->tl_used) - 1;
	जबतक (i >= 0) अणु
		handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_FLUSH_ONE_REC);
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* Caller has given us at least enough credits to
		 * update the truncate log dinode */
		status = ocfs2_journal_access_di(handle, INODE_CACHE(tl_inode), tl_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		tl->tl_used = cpu_to_le16(i);

		ocfs2_journal_dirty(handle, tl_bh);

		rec = tl->tl_recs[i];
		start_blk = ocfs2_clusters_to_blocks(data_alloc_inode->i_sb,
						    le32_to_cpu(rec.t_start));
		num_clusters = le32_to_cpu(rec.t_clusters);

		/* अगर start_blk is not set, we ignore the record as
		 * invalid. */
		अगर (start_blk) अणु
			trace_ocfs2_replay_truncate_records(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(tl_inode)->ip_blkno,
				i, le32_to_cpu(rec.t_start), num_clusters);

			status = ocfs2_मुक्त_clusters(handle, data_alloc_inode,
						     data_alloc_bh, start_blk,
						     num_clusters);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
		पूर्ण

		ocfs2_commit_trans(osb, handle);
		i--;
	पूर्ण

	osb->truncated_clusters = 0;

bail:
	वापस status;
पूर्ण

/* Expects you to alपढ़ोy be holding tl_inode->i_mutex */
पूर्णांक __ocfs2_flush_truncate_log(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक num_to_flush;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा inode *data_alloc_inode = शून्य;
	काष्ठा buffer_head *tl_bh = osb->osb_tl_bh;
	काष्ठा buffer_head *data_alloc_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_truncate_log *tl;
	काष्ठा ocfs2_journal *journal = osb->journal;

	BUG_ON(inode_trylock(tl_inode));

	di = (काष्ठा ocfs2_dinode *) tl_bh->b_data;

	/* tl_bh is loaded from ocfs2_truncate_log_init().  It's validated
	 * by the underlying call to ocfs2_पढ़ो_inode_block(), so any
	 * corruption is a code bug */
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	tl = &di->id2.i_dealloc;
	num_to_flush = le16_to_cpu(tl->tl_used);
	trace_ocfs2_flush_truncate_log(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(tl_inode)->ip_blkno,
		num_to_flush);
	अगर (!num_to_flush) अणु
		status = 0;
		जाओ out;
	पूर्ण

	/* Appending truncate log(TA) and flushing truncate log(TF) are
	 * two separated transactions. They can be both committed but not
	 * checkpoपूर्णांकed. If crash occurs then, both two transaction will be
	 * replayed with several alपढ़ोy released to global biपंचांगap clusters.
	 * Then truncate log will be replayed resulting in cluster द्विगुन मुक्त.
	 */
	jbd2_journal_lock_updates(journal->j_journal);
	status = jbd2_journal_flush(journal->j_journal);
	jbd2_journal_unlock_updates(journal->j_journal);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	data_alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
						       GLOBAL_BITMAP_SYSTEM_INODE,
						       OCFS2_INVALID_SLOT);
	अगर (!data_alloc_inode) अणु
		status = -EINVAL;
		mlog(ML_ERROR, "Could not get bitmap inode!\n");
		जाओ out;
	पूर्ण

	inode_lock(data_alloc_inode);

	status = ocfs2_inode_lock(data_alloc_inode, &data_alloc_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_mutex;
	पूर्ण

	status = ocfs2_replay_truncate_records(osb, data_alloc_inode,
					       data_alloc_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	brअन्यथा(data_alloc_bh);
	ocfs2_inode_unlock(data_alloc_inode, 1);

out_mutex:
	inode_unlock(data_alloc_inode);
	iput(data_alloc_inode);

out:
	वापस status;
पूर्ण

पूर्णांक ocfs2_flush_truncate_log(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;

	inode_lock(tl_inode);
	status = __ocfs2_flush_truncate_log(osb);
	inode_unlock(tl_inode);

	वापस status;
पूर्ण

अटल व्योम ocfs2_truncate_log_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_super *osb =
		container_of(work, काष्ठा ocfs2_super,
			     osb_truncate_log_wq.work);

	status = ocfs2_flush_truncate_log(osb);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	अन्यथा
		ocfs2_init_steal_slots(osb);
पूर्ण

#घोषणा OCFS2_TRUNCATE_LOG_FLUSH_INTERVAL (2 * HZ)
व्योम ocfs2_schedule_truncate_log_flush(काष्ठा ocfs2_super *osb,
				       पूर्णांक cancel)
अणु
	अगर (osb->osb_tl_inode &&
			atomic_पढ़ो(&osb->osb_tl_disable) == 0) अणु
		/* We want to push off log flushes जबतक truncates are
		 * still running. */
		अगर (cancel)
			cancel_delayed_work(&osb->osb_truncate_log_wq);

		queue_delayed_work(osb->ocfs2_wq, &osb->osb_truncate_log_wq,
				   OCFS2_TRUNCATE_LOG_FLUSH_INTERVAL);
	पूर्ण
पूर्ण

/*
 * Try to flush truncate logs अगर we can मुक्त enough clusters from it.
 * As क्रम वापस value, "< 0" means error, "0" no space and "1" means
 * we have मुक्तd enough spaces and let the caller try to allocate again.
 */
पूर्णांक ocfs2_try_to_मुक्त_truncate_log(काष्ठा ocfs2_super *osb,
					अचिन्हित पूर्णांक needed)
अणु
	tid_t target;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक truncated_clusters;

	inode_lock(osb->osb_tl_inode);
	truncated_clusters = osb->truncated_clusters;
	inode_unlock(osb->osb_tl_inode);

	/*
	 * Check whether we can succeed in allocating अगर we मुक्त
	 * the truncate log.
	 */
	अगर (truncated_clusters < needed)
		जाओ out;

	ret = ocfs2_flush_truncate_log(osb);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (jbd2_journal_start_commit(osb->journal->j_journal, &target)) अणु
		jbd2_log_रुको_commit(osb->journal->j_journal, target);
		ret = 1;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_get_truncate_log_info(काष्ठा ocfs2_super *osb,
				       पूर्णांक slot_num,
				       काष्ठा inode **tl_inode,
				       काष्ठा buffer_head **tl_bh)
अणु
	पूर्णांक status;
	काष्ठा inode *inode = शून्य;
	काष्ठा buffer_head *bh = शून्य;

	inode = ocfs2_get_प्रणाली_file_inode(osb,
					   TRUNCATE_LOG_SYSTEM_INODE,
					   slot_num);
	अगर (!inode) अणु
		status = -EINVAL;
		mlog(ML_ERROR, "Could not get load truncate log inode!\n");
		जाओ bail;
	पूर्ण

	status = ocfs2_पढ़ो_inode_block(inode, &bh);
	अगर (status < 0) अणु
		iput(inode);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	*tl_inode = inode;
	*tl_bh    = bh;
bail:
	वापस status;
पूर्ण

/* called during the 1st stage of node recovery. we stamp a clean
 * truncate log and pass back a copy क्रम processing later. अगर the
 * truncate log करोes not require processing, a *tl_copy is set to
 * शून्य. */
पूर्णांक ocfs2_begin_truncate_log_recovery(काष्ठा ocfs2_super *osb,
				      पूर्णांक slot_num,
				      काष्ठा ocfs2_dinode **tl_copy)
अणु
	पूर्णांक status;
	काष्ठा inode *tl_inode = शून्य;
	काष्ठा buffer_head *tl_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_truncate_log *tl;

	*tl_copy = शून्य;

	trace_ocfs2_begin_truncate_log_recovery(slot_num);

	status = ocfs2_get_truncate_log_info(osb, slot_num, &tl_inode, &tl_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *) tl_bh->b_data;

	/* tl_bh is loaded from ocfs2_get_truncate_log_info().  It's
	 * validated by the underlying call to ocfs2_पढ़ो_inode_block(),
	 * so any corruption is a code bug */
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	tl = &di->id2.i_dealloc;
	अगर (le16_to_cpu(tl->tl_used)) अणु
		trace_ocfs2_truncate_log_recovery_num(le16_to_cpu(tl->tl_used));

		/*
		 * Assuming the ग_लिखो-out below goes well, this copy will be
		 * passed back to recovery क्रम processing.
		 */
		*tl_copy = kmemdup(tl_bh->b_data, tl_bh->b_size, GFP_KERNEL);
		अगर (!(*tl_copy)) अणु
			status = -ENOMEM;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* All we need to करो to clear the truncate log is set
		 * tl_used. */
		tl->tl_used = 0;

		ocfs2_compute_meta_ecc(osb->sb, tl_bh->b_data, &di->i_check);
		status = ocfs2_ग_लिखो_block(osb, tl_bh, INODE_CACHE(tl_inode));
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

bail:
	iput(tl_inode);
	brअन्यथा(tl_bh);

	अगर (status < 0) अणु
		kमुक्त(*tl_copy);
		*tl_copy = शून्य;
		mlog_त्रुटि_सं(status);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ocfs2_complete_truncate_log_recovery(काष्ठा ocfs2_super *osb,
					 काष्ठा ocfs2_dinode *tl_copy)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	अचिन्हित पूर्णांक clusters, num_recs, start_cluster;
	u64 start_blk;
	handle_t *handle;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा ocfs2_truncate_log *tl;

	अगर (OCFS2_I(tl_inode)->ip_blkno == le64_to_cpu(tl_copy->i_blkno)) अणु
		mlog(ML_ERROR, "Asked to recover my own truncate log!\n");
		वापस -EINVAL;
	पूर्ण

	tl = &tl_copy->id2.i_dealloc;
	num_recs = le16_to_cpu(tl->tl_used);
	trace_ocfs2_complete_truncate_log_recovery(
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(tl_copy->i_blkno),
		num_recs);

	inode_lock(tl_inode);
	क्रम(i = 0; i < num_recs; i++) अणु
		अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
			status = __ocfs2_flush_truncate_log(osb);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail_up;
			पूर्ण
		पूर्ण

		handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_UPDATE);
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			mlog_त्रुटि_सं(status);
			जाओ bail_up;
		पूर्ण

		clusters = le32_to_cpu(tl->tl_recs[i].t_clusters);
		start_cluster = le32_to_cpu(tl->tl_recs[i].t_start);
		start_blk = ocfs2_clusters_to_blocks(osb->sb, start_cluster);

		status = ocfs2_truncate_log_append(osb, handle,
						   start_blk, clusters);
		ocfs2_commit_trans(osb, handle);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail_up;
		पूर्ण
	पूर्ण

bail_up:
	inode_unlock(tl_inode);

	वापस status;
पूर्ण

व्योम ocfs2_truncate_log_shutकरोwn(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;

	atomic_set(&osb->osb_tl_disable, 1);

	अगर (tl_inode) अणु
		cancel_delayed_work(&osb->osb_truncate_log_wq);
		flush_workqueue(osb->ocfs2_wq);

		status = ocfs2_flush_truncate_log(osb);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);

		brअन्यथा(osb->osb_tl_bh);
		iput(osb->osb_tl_inode);
	पूर्ण
पूर्ण

पूर्णांक ocfs2_truncate_log_init(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	काष्ठा inode *tl_inode = शून्य;
	काष्ठा buffer_head *tl_bh = शून्य;

	status = ocfs2_get_truncate_log_info(osb,
					     osb->slot_num,
					     &tl_inode,
					     &tl_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* ocfs2_truncate_log_shutकरोwn keys on the existence of
	 * osb->osb_tl_inode so we करोn't set any of the osb variables
	 * until we're sure all is well. */
	INIT_DELAYED_WORK(&osb->osb_truncate_log_wq,
			  ocfs2_truncate_log_worker);
	atomic_set(&osb->osb_tl_disable, 0);
	osb->osb_tl_bh    = tl_bh;
	osb->osb_tl_inode = tl_inode;

	वापस status;
पूर्ण

/*
 * Delayed de-allocation of suballocator blocks.
 *
 * Some sets of block de-allocations might involve multiple suballocator inodes.
 *
 * The locking क्रम this can get extremely complicated, especially when
 * the suballocator inodes to delete from aren't known until deep
 * within an unrelated codepath.
 *
 * ocfs2_extent_block काष्ठाures are a good example of this - an inode
 * btree could have been grown by any number of nodes each allocating
 * out of their own suballoc inode.
 *
 * These काष्ठाures allow the delay of block de-allocation until a
 * later समय, when locking of multiple cluster inodes won't cause
 * deadlock.
 */

/*
 * Describe a single bit मुक्तd from a suballocator.  For the block
 * suballocators, it represents one block.  For the global cluster
 * allocator, it represents some clusters and मुक्त_bit indicates
 * clusters number.
 */
काष्ठा ocfs2_cached_block_मुक्त अणु
	काष्ठा ocfs2_cached_block_मुक्त		*मुक्त_next;
	u64					मुक्त_bg;
	u64					मुक्त_blk;
	अचिन्हित पूर्णांक				मुक्त_bit;
पूर्ण;

काष्ठा ocfs2_per_slot_मुक्त_list अणु
	काष्ठा ocfs2_per_slot_मुक्त_list		*f_next_suballocator;
	पूर्णांक					f_inode_type;
	पूर्णांक					f_slot;
	काष्ठा ocfs2_cached_block_मुक्त		*f_first;
पूर्ण;

अटल पूर्णांक ocfs2_मुक्त_cached_blocks(काष्ठा ocfs2_super *osb,
				    पूर्णांक sysfile_type,
				    पूर्णांक slot,
				    काष्ठा ocfs2_cached_block_मुक्त *head)
अणु
	पूर्णांक ret;
	u64 bg_blkno;
	handle_t *handle;
	काष्ठा inode *inode;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_cached_block_मुक्त *पंचांगp;

	inode = ocfs2_get_प्रणाली_file_inode(osb, sysfile_type, slot);
	अगर (!inode) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	inode_lock(inode);

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	जबतक (head) अणु
		अगर (head->मुक्त_bg)
			bg_blkno = head->मुक्त_bg;
		अन्यथा
			bg_blkno = ocfs2_which_suballoc_group(head->मुक्त_blk,
							      head->मुक्त_bit);
		handle = ocfs2_start_trans(osb, OCFS2_SUBALLOC_FREE);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण

		trace_ocfs2_मुक्त_cached_blocks(
		     (अचिन्हित दीर्घ दीर्घ)head->मुक्त_blk, head->मुक्त_bit);

		ret = ocfs2_मुक्त_suballoc_bits(handle, inode, di_bh,
					       head->मुक्त_bit, bg_blkno, 1);
		अगर (ret)
			mlog_त्रुटि_सं(ret);

		ocfs2_commit_trans(osb, handle);

		पंचांगp = head;
		head = head->मुक्त_next;
		kमुक्त(पंचांगp);
	पूर्ण

out_unlock:
	ocfs2_inode_unlock(inode, 1);
	brअन्यथा(di_bh);
out_mutex:
	inode_unlock(inode);
	iput(inode);
out:
	जबतक(head) अणु
		/* Premature निकास may have left some dangling items. */
		पंचांगp = head;
		head = head->मुक्त_next;
		kमुक्त(पंचांगp);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_cache_cluster_dealloc(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
				u64 blkno, अचिन्हित पूर्णांक bit)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_cached_block_मुक्त *item;

	item = kzalloc(माप(*item), GFP_NOFS);
	अगर (item == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	trace_ocfs2_cache_cluster_dealloc((अचिन्हित दीर्घ दीर्घ)blkno, bit);

	item->मुक्त_blk = blkno;
	item->मुक्त_bit = bit;
	item->मुक्त_next = ctxt->c_global_allocator;

	ctxt->c_global_allocator = item;
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_मुक्त_cached_clusters(काष्ठा ocfs2_super *osb,
				      काष्ठा ocfs2_cached_block_मुक्त *head)
अणु
	काष्ठा ocfs2_cached_block_मुक्त *पंचांगp;
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	पूर्णांक ret = 0;

	inode_lock(tl_inode);

	जबतक (head) अणु
		अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
			ret = __ocfs2_flush_truncate_log(osb);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				अवरोध;
			पूर्ण
		पूर्ण

		handle = ocfs2_start_trans(osb, OCFS2_TRUNCATE_LOG_UPDATE);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_truncate_log_append(osb, handle, head->मुक्त_blk,
						head->मुक्त_bit);

		ocfs2_commit_trans(osb, handle);
		पंचांगp = head;
		head = head->मुक्त_next;
		kमुक्त(पंचांगp);

		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	inode_unlock(tl_inode);

	जबतक (head) अणु
		/* Premature निकास may have left some dangling items. */
		पंचांगp = head;
		head = head->मुक्त_next;
		kमुक्त(पंचांगp);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_run_deallocs(काष्ठा ocfs2_super *osb,
		       काष्ठा ocfs2_cached_dealloc_ctxt *ctxt)
अणु
	पूर्णांक ret = 0, ret2;
	काष्ठा ocfs2_per_slot_मुक्त_list *fl;

	अगर (!ctxt)
		वापस 0;

	जबतक (ctxt->c_first_suballocator) अणु
		fl = ctxt->c_first_suballocator;

		अगर (fl->f_first) अणु
			trace_ocfs2_run_deallocs(fl->f_inode_type,
						 fl->f_slot);
			ret2 = ocfs2_मुक्त_cached_blocks(osb,
							fl->f_inode_type,
							fl->f_slot,
							fl->f_first);
			अगर (ret2)
				mlog_त्रुटि_सं(ret2);
			अगर (!ret)
				ret = ret2;
		पूर्ण

		ctxt->c_first_suballocator = fl->f_next_suballocator;
		kमुक्त(fl);
	पूर्ण

	अगर (ctxt->c_global_allocator) अणु
		ret2 = ocfs2_मुक्त_cached_clusters(osb,
						  ctxt->c_global_allocator);
		अगर (ret2)
			mlog_त्रुटि_सं(ret2);
		अगर (!ret)
			ret = ret2;

		ctxt->c_global_allocator = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा ocfs2_per_slot_मुक्त_list *
ocfs2_find_per_slot_मुक्त_list(पूर्णांक type,
			      पूर्णांक slot,
			      काष्ठा ocfs2_cached_dealloc_ctxt *ctxt)
अणु
	काष्ठा ocfs2_per_slot_मुक्त_list *fl = ctxt->c_first_suballocator;

	जबतक (fl) अणु
		अगर (fl->f_inode_type == type && fl->f_slot == slot)
			वापस fl;

		fl = fl->f_next_suballocator;
	पूर्ण

	fl = kदो_स्मृति(माप(*fl), GFP_NOFS);
	अगर (fl) अणु
		fl->f_inode_type = type;
		fl->f_slot = slot;
		fl->f_first = शून्य;
		fl->f_next_suballocator = ctxt->c_first_suballocator;

		ctxt->c_first_suballocator = fl;
	पूर्ण
	वापस fl;
पूर्ण

अटल काष्ठा ocfs2_per_slot_मुक्त_list *
ocfs2_find_preferred_मुक्त_list(पूर्णांक type,
			       पूर्णांक preferred_slot,
			       पूर्णांक *real_slot,
			       काष्ठा ocfs2_cached_dealloc_ctxt *ctxt)
अणु
	काष्ठा ocfs2_per_slot_मुक्त_list *fl = ctxt->c_first_suballocator;

	जबतक (fl) अणु
		अगर (fl->f_inode_type == type && fl->f_slot == preferred_slot) अणु
			*real_slot = fl->f_slot;
			वापस fl;
		पूर्ण

		fl = fl->f_next_suballocator;
	पूर्ण

	/* If we can't find any मुक्त list matching preferred slot, just use
	 * the first one.
	 */
	fl = ctxt->c_first_suballocator;
	*real_slot = fl->f_slot;

	वापस fl;
पूर्ण

/* Return Value 1 indicates empty */
अटल पूर्णांक ocfs2_is_dealloc_empty(काष्ठा ocfs2_extent_tree *et)
अणु
	काष्ठा ocfs2_per_slot_मुक्त_list *fl = शून्य;

	अगर (!et->et_dealloc)
		वापस 1;

	fl = et->et_dealloc->c_first_suballocator;
	अगर (!fl)
		वापस 1;

	अगर (!fl->f_first)
		वापस 1;

	वापस 0;
पूर्ण

/* If extent was deleted from tree due to extent rotation and merging, and
 * no metadata is reserved ahead of समय. Try to reuse some extents
 * just deleted. This is only used to reuse extent blocks.
 * It is supposed to find enough extent blocks in dealloc अगर our estimation
 * on metadata is accurate.
 */
अटल पूर्णांक ocfs2_reuse_blk_from_dealloc(handle_t *handle,
					काष्ठा ocfs2_extent_tree *et,
					काष्ठा buffer_head **new_eb_bh,
					पूर्णांक blk_wanted, पूर्णांक *blk_given)
अणु
	पूर्णांक i, status = 0, real_slot;
	काष्ठा ocfs2_cached_dealloc_ctxt *dealloc;
	काष्ठा ocfs2_per_slot_मुक्त_list *fl;
	काष्ठा ocfs2_cached_block_मुक्त *bf;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(et->et_ci));

	*blk_given = 0;

	/* If extent tree करोesn't have a dealloc, this is not faulty. Just
	 * tell upper caller dealloc can't provide any block and it should
	 * ask क्रम alloc to claim more space.
	 */
	dealloc = et->et_dealloc;
	अगर (!dealloc)
		जाओ bail;

	क्रम (i = 0; i < blk_wanted; i++) अणु
		/* Prefer to use local slot */
		fl = ocfs2_find_preferred_मुक्त_list(EXTENT_ALLOC_SYSTEM_INODE,
						    osb->slot_num, &real_slot,
						    dealloc);
		/* If no more block can be reused, we should claim more
		 * from alloc. Just वापस here normally.
		 */
		अगर (!fl) अणु
			status = 0;
			अवरोध;
		पूर्ण

		bf = fl->f_first;
		fl->f_first = bf->मुक्त_next;

		new_eb_bh[i] = sb_getblk(osb->sb, bf->मुक्त_blk);
		अगर (new_eb_bh[i] == शून्य) अणु
			status = -ENOMEM;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		mlog(0, "Reusing block(%llu) from "
		     "dealloc(local slot:%d, real slot:%d)\n",
		     bf->मुक्त_blk, osb->slot_num, real_slot);

		ocfs2_set_new_buffer_uptodate(et->et_ci, new_eb_bh[i]);

		status = ocfs2_journal_access_eb(handle, et->et_ci,
						 new_eb_bh[i],
						 OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		स_रखो(new_eb_bh[i]->b_data, 0, osb->sb->s_blocksize);
		eb = (काष्ठा ocfs2_extent_block *) new_eb_bh[i]->b_data;

		/* We can't guarantee that buffer head is still cached, so
		 * polutlate the extent block again.
		 */
		म_नकल(eb->h_signature, OCFS2_EXTENT_BLOCK_SIGNATURE);
		eb->h_blkno = cpu_to_le64(bf->मुक्त_blk);
		eb->h_fs_generation = cpu_to_le32(osb->fs_generation);
		eb->h_suballoc_slot = cpu_to_le16(real_slot);
		eb->h_suballoc_loc = cpu_to_le64(bf->मुक्त_bg);
		eb->h_suballoc_bit = cpu_to_le16(bf->मुक्त_bit);
		eb->h_list.l_count =
			cpu_to_le16(ocfs2_extent_recs_per_eb(osb->sb));

		/* We'll also be dirtied by the caller, so
		 * this isn't असलolutely necessary.
		 */
		ocfs2_journal_dirty(handle, new_eb_bh[i]);

		अगर (!fl->f_first) अणु
			dealloc->c_first_suballocator = fl->f_next_suballocator;
			kमुक्त(fl);
		पूर्ण
		kमुक्त(bf);
	पूर्ण

	*blk_given = i;

bail:
	अगर (unlikely(status < 0)) अणु
		क्रम (i = 0; i < blk_wanted; i++)
			brअन्यथा(new_eb_bh[i]);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ocfs2_cache_block_dealloc(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
			      पूर्णांक type, पूर्णांक slot, u64 suballoc,
			      u64 blkno, अचिन्हित पूर्णांक bit)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_per_slot_मुक्त_list *fl;
	काष्ठा ocfs2_cached_block_मुक्त *item;

	fl = ocfs2_find_per_slot_मुक्त_list(type, slot, ctxt);
	अगर (fl == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	item = kzalloc(माप(*item), GFP_NOFS);
	अगर (item == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_cache_block_dealloc(type, slot,
					(अचिन्हित दीर्घ दीर्घ)suballoc,
					(अचिन्हित दीर्घ दीर्घ)blkno, bit);

	item->मुक्त_bg = suballoc;
	item->मुक्त_blk = blkno;
	item->मुक्त_bit = bit;
	item->मुक्त_next = fl->f_first;

	fl->f_first = item;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_cache_extent_block_मुक्त(काष्ठा ocfs2_cached_dealloc_ctxt *ctxt,
					 काष्ठा ocfs2_extent_block *eb)
अणु
	वापस ocfs2_cache_block_dealloc(ctxt, EXTENT_ALLOC_SYSTEM_INODE,
					 le16_to_cpu(eb->h_suballoc_slot),
					 le64_to_cpu(eb->h_suballoc_loc),
					 le64_to_cpu(eb->h_blkno),
					 le16_to_cpu(eb->h_suballoc_bit));
पूर्ण

अटल पूर्णांक ocfs2_zero_func(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	set_buffer_uptodate(bh);
	mark_buffer_dirty(bh);
	वापस 0;
पूर्ण

व्योम ocfs2_map_and_dirty_page(काष्ठा inode *inode, handle_t *handle,
			      अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to,
			      काष्ठा page *page, पूर्णांक zero, u64 *phys)
अणु
	पूर्णांक ret, partial = 0;
	loff_t start_byte = ((loff_t)page->index << PAGE_SHIFT) + from;
	loff_t length = to - from;

	ret = ocfs2_map_page_blocks(page, phys, inode, from, to, 0);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	अगर (zero)
		zero_user_segment(page, from, to);

	/*
	 * Need to set the buffers we zero'd पूर्णांकo uptodate
	 * here अगर they aren't - ocfs2_map_page_blocks()
	 * might've skipped some
	 */
	ret = walk_page_buffers(handle, page_buffers(page),
				from, to, &partial,
				ocfs2_zero_func);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);
	अन्यथा अगर (ocfs2_should_order_data(inode)) अणु
		ret = ocfs2_jbd2_inode_add_ग_लिखो(handle, inode,
						 start_byte, length);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
	पूर्ण

	अगर (!partial)
		SetPageUptodate(page);

	flush_dcache_page(page);
पूर्ण

अटल व्योम ocfs2_zero_cluster_pages(काष्ठा inode *inode, loff_t start,
				     loff_t end, काष्ठा page **pages,
				     पूर्णांक numpages, u64 phys, handle_t *handle)
अणु
	पूर्णांक i;
	काष्ठा page *page;
	अचिन्हित पूर्णांक from, to = PAGE_SIZE;
	काष्ठा super_block *sb = inode->i_sb;

	BUG_ON(!ocfs2_sparse_alloc(OCFS2_SB(sb)));

	अगर (numpages == 0)
		जाओ out;

	to = PAGE_SIZE;
	क्रम(i = 0; i < numpages; i++) अणु
		page = pages[i];

		from = start & (PAGE_SIZE - 1);
		अगर ((end >> PAGE_SHIFT) == page->index)
			to = end & (PAGE_SIZE - 1);

		BUG_ON(from > PAGE_SIZE);
		BUG_ON(to > PAGE_SIZE);

		ocfs2_map_and_dirty_page(inode, handle, from, to, page, 1,
					 &phys);

		start = (page->index + 1) << PAGE_SHIFT;
	पूर्ण
out:
	अगर (pages)
		ocfs2_unlock_and_मुक्त_pages(pages, numpages);
पूर्ण

पूर्णांक ocfs2_grab_pages(काष्ठा inode *inode, loff_t start, loff_t end,
		     काष्ठा page **pages, पूर्णांक *num)
अणु
	पूर्णांक numpages, ret = 0;
	काष्ठा address_space *mapping = inode->i_mapping;
	अचिन्हित दीर्घ index;
	loff_t last_page_bytes;

	BUG_ON(start > end);

	numpages = 0;
	last_page_bytes = PAGE_ALIGN(end);
	index = start >> PAGE_SHIFT;
	करो अणु
		pages[numpages] = find_or_create_page(mapping, index, GFP_NOFS);
		अगर (!pages[numpages]) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		numpages++;
		index++;
	पूर्ण जबतक (index < (last_page_bytes >> PAGE_SHIFT));

out:
	अगर (ret != 0) अणु
		अगर (pages)
			ocfs2_unlock_and_मुक्त_pages(pages, numpages);
		numpages = 0;
	पूर्ण

	*num = numpages;

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_grab_eof_pages(काष्ठा inode *inode, loff_t start, loff_t end,
				काष्ठा page **pages, पूर्णांक *num)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	BUG_ON(start >> OCFS2_SB(sb)->s_clustersize_bits !=
	       (end - 1) >> OCFS2_SB(sb)->s_clustersize_bits);

	वापस ocfs2_grab_pages(inode, start, end, pages, num);
पूर्ण

/*
 * Zero the area past i_size but still within an allocated
 * cluster. This aव्योमs exposing nonzero data on subsequent file
 * extends.
 *
 * We need to call this beक्रमe i_size is updated on the inode because
 * otherwise block_ग_लिखो_full_page() will skip ग_लिखोout of pages past
 * i_size. The new_i_size parameter is passed क्रम this reason.
 */
पूर्णांक ocfs2_zero_range_क्रम_truncate(काष्ठा inode *inode, handle_t *handle,
				  u64 range_start, u64 range_end)
अणु
	पूर्णांक ret = 0, numpages;
	काष्ठा page **pages = शून्य;
	u64 phys;
	अचिन्हित पूर्णांक ext_flags;
	काष्ठा super_block *sb = inode->i_sb;

	/*
	 * File प्रणालीs which करोn't support sparse files zero on every
	 * extend.
	 */
	अगर (!ocfs2_sparse_alloc(OCFS2_SB(sb)))
		वापस 0;

	pages = kसुस्मृति(ocfs2_pages_per_cluster(sb),
			माप(काष्ठा page *), GFP_NOFS);
	अगर (pages == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (range_start == range_end)
		जाओ out;

	ret = ocfs2_extent_map_get_blocks(inode,
					  range_start >> sb->s_blocksize_bits,
					  &phys, शून्य, &ext_flags);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Tail is a hole, or is marked unwritten. In either हाल, we
	 * can count on पढ़ो and ग_लिखो to वापस/push zero's.
	 */
	अगर (phys == 0 || ext_flags & OCFS2_EXT_UNWRITTEN)
		जाओ out;

	ret = ocfs2_grab_eof_pages(inode, range_start, range_end, pages,
				   &numpages);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_zero_cluster_pages(inode, range_start, range_end, pages,
				 numpages, phys, handle);

	/*
	 * Initiate ग_लिखोout of the pages we zero'd here. We don't
	 * रुको on them - the truncate_inode_pages() call later will
	 * करो that क्रम us.
	 */
	ret = filemap_fdataग_लिखो_range(inode->i_mapping, range_start,
				       range_end - 1);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	kमुक्त(pages);

	वापस ret;
पूर्ण

अटल व्योम ocfs2_zero_dinode_id2_with_xattr(काष्ठा inode *inode,
					     काष्ठा ocfs2_dinode *di)
अणु
	अचिन्हित पूर्णांक blocksize = 1 << inode->i_sb->s_blocksize_bits;
	अचिन्हित पूर्णांक xattrsize = le16_to_cpu(di->i_xattr_अंतरभूत_size);

	अगर (le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_XATTR_FL)
		स_रखो(&di->id2, 0, blocksize -
				    दुरत्व(काष्ठा ocfs2_dinode, id2) -
				    xattrsize);
	अन्यथा
		स_रखो(&di->id2, 0, blocksize -
				    दुरत्व(काष्ठा ocfs2_dinode, id2));
पूर्ण

व्योम ocfs2_dinode_new_extent_list(काष्ठा inode *inode,
				  काष्ठा ocfs2_dinode *di)
अणु
	ocfs2_zero_dinode_id2_with_xattr(inode, di);
	di->id2.i_list.l_tree_depth = 0;
	di->id2.i_list.l_next_मुक्त_rec = 0;
	di->id2.i_list.l_count = cpu_to_le16(
		ocfs2_extent_recs_per_inode_with_xattr(inode->i_sb, di));
पूर्ण

व्योम ocfs2_set_inode_data_अंतरभूत(काष्ठा inode *inode, काष्ठा ocfs2_dinode *di)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_अंतरभूत_data *idata = &di->id2.i_data;

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_INLINE_DATA_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	/*
	 * We clear the entire i_data काष्ठाure here so that all
	 * fields can be properly initialized.
	 */
	ocfs2_zero_dinode_id2_with_xattr(inode, di);

	idata->id_count = cpu_to_le16(
			ocfs2_max_अंतरभूत_data_with_xattr(inode->i_sb, di));
पूर्ण

पूर्णांक ocfs2_convert_अंतरभूत_data_to_extents(काष्ठा inode *inode,
					 काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret, i, has_data, num_pages = 0;
	पूर्णांक need_मुक्त = 0;
	u32 bit_off, num;
	handle_t *handle;
	u64 block;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा page **pages = शून्य;
	loff_t end = osb->s_clustersize;
	काष्ठा ocfs2_extent_tree et;
	पूर्णांक did_quota = 0;

	has_data = i_size_पढ़ो(inode) ? 1 : 0;

	अगर (has_data) अणु
		pages = kसुस्मृति(ocfs2_pages_per_cluster(osb->sb),
				माप(काष्ठा page *), GFP_NOFS);
		अगर (pages == शून्य) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		ret = ocfs2_reserve_clusters(osb, 1, &data_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ मुक्त_pages;
		पूर्ण
	पूर्ण

	handle = ocfs2_start_trans(osb,
				   ocfs2_अंतरभूत_to_extents_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	अगर (has_data) अणु
		अचिन्हित पूर्णांक page_end;
		u64 phys;

		ret = dquot_alloc_space_nodirty(inode,
				       ocfs2_clusters_to_bytes(osb->sb, 1));
		अगर (ret)
			जाओ out_commit;
		did_quota = 1;

		data_ac->ac_resv = &oi->ip_la_data_resv;

		ret = ocfs2_claim_clusters(handle, data_ac, 1, &bit_off,
					   &num);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण

		/*
		 * Save two copies, one क्रम insert, and one that can
		 * be changed by ocfs2_map_and_dirty_page() below.
		 */
		block = phys = ocfs2_clusters_to_blocks(inode->i_sb, bit_off);

		/*
		 * Non sparse file प्रणालीs zero on extend, so no need
		 * to करो that now.
		 */
		अगर (!ocfs2_sparse_alloc(osb) &&
		    PAGE_SIZE < osb->s_clustersize)
			end = PAGE_SIZE;

		ret = ocfs2_grab_eof_pages(inode, 0, end, pages, &num_pages);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			need_मुक्त = 1;
			जाओ out_commit;
		पूर्ण

		/*
		 * This should populate the 1st page क्रम us and mark
		 * it up to date.
		 */
		ret = ocfs2_पढ़ो_अंतरभूत_data(inode, pages[0], di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			need_मुक्त = 1;
			जाओ out_unlock;
		पूर्ण

		page_end = PAGE_SIZE;
		अगर (PAGE_SIZE > osb->s_clustersize)
			page_end = osb->s_clustersize;

		क्रम (i = 0; i < num_pages; i++)
			ocfs2_map_and_dirty_page(inode, handle, 0, page_end,
						 pages[i], i > 0, &phys);
	पूर्ण

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~OCFS2_INLINE_DATA_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_dinode_new_extent_list(inode, di);

	ocfs2_journal_dirty(handle, di_bh);

	अगर (has_data) अणु
		/*
		 * An error at this poपूर्णांक should be extremely rare. If
		 * this proves to be false, we could always re-build
		 * the in-inode data from our pages.
		 */
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
		ret = ocfs2_insert_extent(handle, &et, 0, block, 1, 0, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			need_मुक्त = 1;
			जाओ out_unlock;
		पूर्ण

		inode->i_blocks = ocfs2_inode_sector_count(inode);
	पूर्ण

out_unlock:
	अगर (pages)
		ocfs2_unlock_and_मुक्त_pages(pages, num_pages);

out_commit:
	अगर (ret < 0 && did_quota)
		dquot_मुक्त_space_nodirty(inode,
					  ocfs2_clusters_to_bytes(osb->sb, 1));

	अगर (need_मुक्त) अणु
		अगर (data_ac->ac_which == OCFS2_AC_USE_LOCAL)
			ocfs2_मुक्त_local_alloc_bits(osb, handle, data_ac,
					bit_off, num);
		अन्यथा
			ocfs2_मुक्त_clusters(handle,
					data_ac->ac_inode,
					data_ac->ac_bh,
					ocfs2_clusters_to_blocks(osb->sb, bit_off),
					num);
	पूर्ण

	ocfs2_commit_trans(osb, handle);

out:
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
मुक्त_pages:
	kमुक्त(pages);
	वापस ret;
पूर्ण

/*
 * It is expected, that by the समय you call this function,
 * inode->i_size and fe->i_size have been adjusted.
 *
 * WARNING: This will kमुक्त the truncate context
 */
पूर्णांक ocfs2_commit_truncate(काष्ठा ocfs2_super *osb,
			  काष्ठा inode *inode,
			  काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक status = 0, i, flags = 0;
	u32 new_highest_cpos, range, trunc_cpos, trunc_len, phys_cpos, coff;
	u64 blkno = 0;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_extent_list *root_el = &(di->id2.i_list);
	u64 refcount_loc = le64_to_cpu(di->i_refcount_loc);
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&dealloc);

	new_highest_cpos = ocfs2_clusters_क्रम_bytes(osb->sb,
						     i_size_पढ़ो(inode));

	path = ocfs2_new_path(di_bh, &di->id2.i_list,
			      ocfs2_journal_access_di);
	अगर (!path) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_extent_map_trunc(inode, new_highest_cpos);

start:
	/*
	 * Check that we still have allocation to delete.
	 */
	अगर (OCFS2_I(inode)->ip_clusters == 0) अणु
		status = 0;
		जाओ bail;
	पूर्ण

	/*
	 * Truncate always works against the righपंचांगost tree branch.
	 */
	status = ocfs2_find_path(INODE_CACHE(inode), path, अच_पूर्णांक_उच्च);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_commit_truncate(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		new_highest_cpos,
		OCFS2_I(inode)->ip_clusters,
		path->p_tree_depth);

	/*
	 * By now, el will poपूर्णांक to the extent list on the bottom most
	 * portion of this tree. Only the tail record is considered in
	 * each pass.
	 *
	 * We handle the following हालs, in order:
	 * - empty extent: delete the reमुख्यing branch
	 * - हटाओ the entire record
	 * - हटाओ a partial record
	 * - no record needs to be हटाओd (truncate has completed)
	 */
	el = path_leaf_el(path);
	अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0) अणु
		ocfs2_error(inode->i_sb,
			    "Inode %llu has empty extent block at %llu\n",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			    (अचिन्हित दीर्घ दीर्घ)path_leaf_bh(path)->b_blocknr);
		status = -EROFS;
		जाओ bail;
	पूर्ण

	i = le16_to_cpu(el->l_next_मुक्त_rec) - 1;
	rec = &el->l_recs[i];
	flags = rec->e_flags;
	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);

	अगर (i == 0 && ocfs2_is_empty_extent(rec)) अणु
		/*
		 * Lower levels depend on this never happening, but it's best
		 * to check it up here beक्रमe changing the tree.
		*/
		अगर (root_el->l_tree_depth && rec->e_पूर्णांक_clusters == 0) अणु
			mlog(ML_ERROR, "Inode %lu has an empty "
				    "extent record, depth %u\n", inode->i_ino,
				    le16_to_cpu(root_el->l_tree_depth));
			status = ocfs2_हटाओ_righपंचांगost_empty_extent(osb,
					&et, path, &dealloc);
			अगर (status) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण

			ocfs2_reinit_path(path, 1);
			जाओ start;
		पूर्ण अन्यथा अणु
			trunc_cpos = le32_to_cpu(rec->e_cpos);
			trunc_len = 0;
			blkno = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (le32_to_cpu(rec->e_cpos) >= new_highest_cpos) अणु
		/*
		 * Truncate entire record.
		 */
		trunc_cpos = le32_to_cpu(rec->e_cpos);
		trunc_len = ocfs2_rec_clusters(el, rec);
		blkno = le64_to_cpu(rec->e_blkno);
	पूर्ण अन्यथा अगर (range > new_highest_cpos) अणु
		/*
		 * Partial truncate. it also should be
		 * the last truncate we're करोing.
		 */
		trunc_cpos = new_highest_cpos;
		trunc_len = range - new_highest_cpos;
		coff = new_highest_cpos - le32_to_cpu(rec->e_cpos);
		blkno = le64_to_cpu(rec->e_blkno) +
				ocfs2_clusters_to_blocks(inode->i_sb, coff);
	पूर्ण अन्यथा अणु
		/*
		 * Truncate completed, leave happily.
		 */
		status = 0;
		जाओ bail;
	पूर्ण

	phys_cpos = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

	अगर ((flags & OCFS2_EXT_REFCOUNTED) && trunc_len && !ref_tree) अणु
		status = ocfs2_lock_refcount_tree(osb, refcount_loc, 1,
				&ref_tree, शून्य);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	status = ocfs2_हटाओ_btree_range(inode, &et, trunc_cpos,
					  phys_cpos, trunc_len, flags, &dealloc,
					  refcount_loc, true);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_reinit_path(path, 1);

	/*
	 * The check above will catch the हाल where we've truncated
	 * away all allocation.
	 */
	जाओ start;

bail:
	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	ocfs2_schedule_truncate_log_flush(osb, 1);

	ocfs2_run_deallocs(osb, &dealloc);

	ocfs2_मुक्त_path(path);

	वापस status;
पूर्ण

/*
 * 'start' is inclusive, 'end' is not.
 */
पूर्णांक ocfs2_truncate_अंतरभूत(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			  अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end, पूर्णांक trunc)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक numbytes;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_अंतरभूत_data *idata = &di->id2.i_data;

	/* No need to punch hole beyond i_size. */
	अगर (start >= i_size_पढ़ो(inode))
		वापस 0;

	अगर (end > i_size_पढ़ो(inode))
		end = i_size_पढ़ो(inode);

	BUG_ON(start > end);

	अगर (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) ||
	    !(le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_DATA_FL) ||
	    !ocfs2_supports_अंतरभूत_data(osb)) अणु
		ocfs2_error(inode->i_sb,
			    "Inline data flags for inode %llu don't agree! Disk: 0x%x, Memory: 0x%x, Superblock: 0x%x\n",
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			    le16_to_cpu(di->i_dyn_features),
			    OCFS2_I(inode)->ip_dyn_features,
			    osb->s_feature_incompat);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	numbytes = end - start;
	स_रखो(idata->id_data + start, 0, numbytes);

	/*
	 * No need to worry about the data page here - it's been
	 * truncated alपढ़ोy and अंतरभूत data करोesn't need it क्रम
	 * pushing zero's to disk, so we'll let पढ़ोpage pick it up
	 * later.
	 */
	अगर (trunc) अणु
		i_size_ग_लिखो(inode, start);
		di->i_size = cpu_to_le64(start);
	पूर्ण

	inode->i_blocks = ocfs2_inode_sector_count(inode);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);

	di->i_स_समय = di->i_mसमय = cpu_to_le64(inode->i_स_समय.tv_sec);
	di->i_स_समय_nsec = di->i_mसमय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);

	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_trim_extent(काष्ठा super_block *sb,
			     काष्ठा ocfs2_group_desc *gd,
			     u64 group, u32 start, u32 count)
अणु
	u64 discard, bcount;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	bcount = ocfs2_clusters_to_blocks(sb, count);
	discard = ocfs2_clusters_to_blocks(sb, start);

	/*
	 * For the first cluster group, the gd->bg_blkno is not at the start
	 * of the group, but at an offset from the start. If we add it जबतक
	 * calculating discard क्रम first group, we will wrongly start fstrim a
	 * few blocks after the desried start block and the range can cross
	 * over पूर्णांकo the next cluster group. So, add it only अगर this is not
	 * the first cluster group.
	 */
	अगर (group != osb->first_cluster_group_blkno)
		discard += le64_to_cpu(gd->bg_blkno);

	trace_ocfs2_trim_extent(sb, (अचिन्हित दीर्घ दीर्घ)discard, bcount);

	वापस sb_issue_discard(sb, discard, bcount, GFP_NOFS, 0);
पूर्ण

अटल पूर्णांक ocfs2_trim_group(काष्ठा super_block *sb,
			    काष्ठा ocfs2_group_desc *gd, u64 group,
			    u32 start, u32 max, u32 minbits)
अणु
	पूर्णांक ret = 0, count = 0, next;
	व्योम *biपंचांगap = gd->bg_biपंचांगap;

	अगर (le16_to_cpu(gd->bg_मुक्त_bits_count) < minbits)
		वापस 0;

	trace_ocfs2_trim_group((अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno),
			       start, max, minbits);

	जबतक (start < max) अणु
		start = ocfs2_find_next_zero_bit(biपंचांगap, max, start);
		अगर (start >= max)
			अवरोध;
		next = ocfs2_find_next_bit(biपंचांगap, max, start);

		अगर ((next - start) >= minbits) अणु
			ret = ocfs2_trim_extent(sb, gd, group,
						start, next - start);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				अवरोध;
			पूर्ण
			count += next - start;
		पूर्ण
		start = next + 1;

		अगर (fatal_संकेत_pending(current)) अणु
			count = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर ((le16_to_cpu(gd->bg_मुक्त_bits_count) - count) < minbits)
			अवरोध;
	पूर्ण

	अगर (ret < 0)
		count = ret;

	वापस count;
पूर्ण

अटल
पूर्णांक ocfs2_trim_मुख्यbm(काष्ठा super_block *sb, काष्ठा fstrim_range *range)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	u64 start, len, trimmed = 0, first_group, last_group = 0, group = 0;
	पूर्णांक ret, cnt;
	u32 first_bit, last_bit, minlen;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode = शून्य;
	काष्ठा buffer_head *gd_bh = शून्य;
	काष्ठा ocfs2_dinode *मुख्य_bm;
	काष्ठा ocfs2_group_desc *gd = शून्य;

	start = range->start >> osb->s_clustersize_bits;
	len = range->len >> osb->s_clustersize_bits;
	minlen = range->minlen >> osb->s_clustersize_bits;

	अगर (minlen >= osb->biपंचांगap_cpg || range->len < sb->s_blocksize)
		वापस -EINVAL;

	trace_ocfs2_trim_मुख्यbm(start, len, minlen);

next_group:
	मुख्य_bm_inode = ocfs2_get_प्रणाली_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	अगर (!मुख्य_bm_inode) अणु
		ret = -EIO;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	inode_lock(मुख्य_bm_inode);

	ret = ocfs2_inode_lock(मुख्य_bm_inode, &मुख्य_bm_bh, 0);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण
	मुख्य_bm = (काष्ठा ocfs2_dinode *)मुख्य_bm_bh->b_data;

	/*
	 * Do some check beक्रमe trim the first group.
	 */
	अगर (!group) अणु
		अगर (start >= le32_to_cpu(मुख्य_bm->i_clusters)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		अगर (start + len > le32_to_cpu(मुख्य_bm->i_clusters))
			len = le32_to_cpu(मुख्य_bm->i_clusters) - start;

		/*
		 * Determine first and last group to examine based on
		 * start and len
		 */
		first_group = ocfs2_which_cluster_group(मुख्य_bm_inode, start);
		अगर (first_group == osb->first_cluster_group_blkno)
			first_bit = start;
		अन्यथा
			first_bit = start - ocfs2_blocks_to_clusters(sb,
								first_group);
		last_group = ocfs2_which_cluster_group(मुख्य_bm_inode,
						       start + len - 1);
		group = first_group;
	पूर्ण

	करो अणु
		अगर (first_bit + len >= osb->biपंचांगap_cpg)
			last_bit = osb->biपंचांगap_cpg;
		अन्यथा
			last_bit = first_bit + len;

		ret = ocfs2_पढ़ो_group_descriptor(मुख्य_bm_inode,
						  मुख्य_bm, group,
						  &gd_bh);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		gd = (काष्ठा ocfs2_group_desc *)gd_bh->b_data;
		cnt = ocfs2_trim_group(sb, gd, group,
				       first_bit, last_bit, minlen);
		brअन्यथा(gd_bh);
		gd_bh = शून्य;
		अगर (cnt < 0) अणु
			ret = cnt;
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		trimmed += cnt;
		len -= osb->biपंचांगap_cpg - first_bit;
		first_bit = 0;
		अगर (group == osb->first_cluster_group_blkno)
			group = ocfs2_clusters_to_blocks(sb, osb->biपंचांगap_cpg);
		अन्यथा
			group += ocfs2_clusters_to_blocks(sb, osb->biपंचांगap_cpg);
	पूर्ण जबतक (0);

out_unlock:
	ocfs2_inode_unlock(मुख्य_bm_inode, 0);
	brअन्यथा(मुख्य_bm_bh);
	मुख्य_bm_bh = शून्य;
out_mutex:
	inode_unlock(मुख्य_bm_inode);
	iput(मुख्य_bm_inode);

	/*
	 * If all the groups trim are not करोne or failed, but we should release
	 * मुख्य_bm related locks क्रम aव्योमing the current IO starve, then go to
	 * trim the next group
	 */
	अगर (ret >= 0 && group <= last_group) अणु
		cond_resched();
		जाओ next_group;
	पूर्ण
out:
	range->len = trimmed * sb->s_blocksize;
	वापस ret;
पूर्ण

पूर्णांक ocfs2_trim_fs(काष्ठा super_block *sb, काष्ठा fstrim_range *range)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	काष्ठा ocfs2_trim_fs_info info, *pinfo = शून्य;

	ocfs2_trim_fs_lock_res_init(osb);

	trace_ocfs2_trim_fs(range->start, range->len, range->minlen);

	ret = ocfs2_trim_fs_lock(osb, शून्य, 1);
	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN) अणु
			mlog_त्रुटि_सं(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			वापस ret;
		पूर्ण

		mlog(ML_NOTICE, "Wait for trim on device (%s) to "
		     "finish, which is running from another node.\n",
		     osb->dev_str);
		ret = ocfs2_trim_fs_lock(osb, &info, 0);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			वापस ret;
		पूर्ण

		अगर (info.tf_valid && info.tf_success &&
		    info.tf_start == range->start &&
		    info.tf_len == range->len &&
		    info.tf_minlen == range->minlen) अणु
			/* Aव्योम sending duplicated trim to a shared device */
			mlog(ML_NOTICE, "The same trim on device (%s) was "
			     "just done from node (%u), return.\n",
			     osb->dev_str, info.tf_nodक्रमागत);
			range->len = info.tf_trimlen;
			जाओ out;
		पूर्ण
	पूर्ण

	info.tf_nodक्रमागत = osb->node_num;
	info.tf_start = range->start;
	info.tf_len = range->len;
	info.tf_minlen = range->minlen;

	ret = ocfs2_trim_मुख्यbm(sb, range);

	info.tf_trimlen = range->len;
	info.tf_success = (ret < 0 ? 0 : 1);
	pinfo = &info;
out:
	ocfs2_trim_fs_unlock(osb, pinfo);
	ocfs2_trim_fs_lock_res_uninit(osb);
	वापस ret;
पूर्ण
