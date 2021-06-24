<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * subभाग.स
 *
 * Defines sub allocator api
 *
 * Copyright (C) 2003, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _CHAINALLOC_H_
#घोषणा _CHAINALLOC_H_

काष्ठा ocfs2_suballoc_result;
प्रकार पूर्णांक (group_search_t)(काष्ठा inode *,
			     काष्ठा buffer_head *,
			     u32,			/* bits_wanted */
			     u32,			/* min_bits */
			     u64,			/* max_block */
			     काष्ठा ocfs2_suballoc_result *);
							/* found bits */

काष्ठा ocfs2_alloc_context अणु
	काष्ठा inode *ac_inode;    /* which biपंचांगap are we allocating from? */
	काष्ठा buffer_head *ac_bh; /* file entry bh */
	u32    ac_alloc_slot;   /* which slot are we allocating from? */
	u32    ac_bits_wanted;
	u32    ac_bits_given;
#घोषणा OCFS2_AC_USE_LOCAL 1
#घोषणा OCFS2_AC_USE_MAIN  2
#घोषणा OCFS2_AC_USE_INODE 3
#घोषणा OCFS2_AC_USE_META  4
	u32    ac_which;

	/* these are used by the chain search */
	u16    ac_chain;
	पूर्णांक    ac_disable_chain_relink;
	group_search_t *ac_group_search;

	u64    ac_last_group;
	u64    ac_max_block;  /* Highest block number to allocate. 0 is
				 the same as ~0 - unlimited */

	पूर्णांक    ac_find_loc_only;  /* hack क्रम reflink operation ordering */
	काष्ठा ocfs2_suballoc_result *ac_find_loc_priv; /* */

	काष्ठा ocfs2_alloc_reservation	*ac_resv;
पूर्ण;

व्योम ocfs2_init_steal_slots(काष्ठा ocfs2_super *osb);
व्योम ocfs2_मुक्त_alloc_context(काष्ठा ocfs2_alloc_context *ac);
अटल अंतरभूत पूर्णांक ocfs2_alloc_context_bits_left(काष्ठा ocfs2_alloc_context *ac)
अणु
	वापस ac->ac_bits_wanted - ac->ac_bits_given;
पूर्ण

/*
 * Please note that the caller must make sure that root_el is the root
 * of extent tree. So क्रम an inode, it should be &fe->id2.i_list. Otherwise
 * the result may be wrong.
 */
पूर्णांक ocfs2_reserve_new_metadata(काष्ठा ocfs2_super *osb,
			       काष्ठा ocfs2_extent_list *root_el,
			       काष्ठा ocfs2_alloc_context **ac);
पूर्णांक ocfs2_reserve_new_metadata_blocks(काष्ठा ocfs2_super *osb,
				      पूर्णांक blocks,
				      काष्ठा ocfs2_alloc_context **ac);
पूर्णांक ocfs2_reserve_new_inode(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_alloc_context **ac);
पूर्णांक ocfs2_reserve_clusters(काष्ठा ocfs2_super *osb,
			   u32 bits_wanted,
			   काष्ठा ocfs2_alloc_context **ac);

पूर्णांक ocfs2_alloc_dinode_update_counts(काष्ठा inode *inode,
			 handle_t *handle,
			 काष्ठा buffer_head *di_bh,
			 u32 num_bits,
			 u16 chain);
व्योम ocfs2_rollback_alloc_dinode_counts(काष्ठा inode *inode,
			 काष्ठा buffer_head *di_bh,
			 u32 num_bits,
			 u16 chain);
पूर्णांक ocfs2_block_group_set_bits(handle_t *handle,
			 काष्ठा inode *alloc_inode,
			 काष्ठा ocfs2_group_desc *bg,
			 काष्ठा buffer_head *group_bh,
			 अचिन्हित पूर्णांक bit_off,
			 अचिन्हित पूर्णांक num_bits);

पूर्णांक ocfs2_claim_metadata(handle_t *handle,
			 काष्ठा ocfs2_alloc_context *ac,
			 u32 bits_wanted,
			 u64 *suballoc_loc,
			 u16 *suballoc_bit_start,
			 u32 *num_bits,
			 u64 *blkno_start);
पूर्णांक ocfs2_claim_new_inode(handle_t *handle,
			  काष्ठा inode *dir,
			  काष्ठा buffer_head *parent_fe_bh,
			  काष्ठा ocfs2_alloc_context *ac,
			  u64 *suballoc_loc,
			  u16 *suballoc_bit,
			  u64 *fe_blkno);
पूर्णांक ocfs2_claim_clusters(handle_t *handle,
			 काष्ठा ocfs2_alloc_context *ac,
			 u32 min_clusters,
			 u32 *cluster_start,
			 u32 *num_clusters);
/*
 * Use this variant of ocfs2_claim_clusters to specअगरy a maxiumum
 * number of clusters smaller than the allocation reserved.
 */
पूर्णांक __ocfs2_claim_clusters(handle_t *handle,
			   काष्ठा ocfs2_alloc_context *ac,
			   u32 min_clusters,
			   u32 max_clusters,
			   u32 *cluster_start,
			   u32 *num_clusters);

पूर्णांक ocfs2_मुक्त_suballoc_bits(handle_t *handle,
			     काष्ठा inode *alloc_inode,
			     काष्ठा buffer_head *alloc_bh,
			     अचिन्हित पूर्णांक start_bit,
			     u64 bg_blkno,
			     अचिन्हित पूर्णांक count);
पूर्णांक ocfs2_मुक्त_dinode(handle_t *handle,
		      काष्ठा inode *inode_alloc_inode,
		      काष्ठा buffer_head *inode_alloc_bh,
		      काष्ठा ocfs2_dinode *di);
पूर्णांक ocfs2_मुक्त_clusters(handle_t *handle,
			काष्ठा inode *biपंचांगap_inode,
			काष्ठा buffer_head *biपंचांगap_bh,
			u64 start_blk,
			अचिन्हित पूर्णांक num_clusters);
पूर्णांक ocfs2_release_clusters(handle_t *handle,
			   काष्ठा inode *biपंचांगap_inode,
			   काष्ठा buffer_head *biपंचांगap_bh,
			   u64 start_blk,
			   अचिन्हित पूर्णांक num_clusters);

अटल अंतरभूत u64 ocfs2_which_suballoc_group(u64 block, अचिन्हित पूर्णांक bit)
अणु
	u64 group = block - (u64) bit;

	वापस group;
पूर्ण

अटल अंतरभूत u32 ocfs2_cluster_from_desc(काष्ठा ocfs2_super *osb,
					  u64 bg_blkno)
अणु
	/* This should work क्रम all block group descriptors as only
	 * the 1st group descriptor of the cluster biपंचांगap is
	 * dअगरferent. */

	अगर (bg_blkno == osb->first_cluster_group_blkno)
		वापस 0;

	/* the rest of the block groups are located at the beginning
	 * of their 1st cluster, so a direct translation just
	 * works. */
	वापस ocfs2_blocks_to_clusters(osb->sb, bg_blkno);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_is_cluster_biपंचांगap(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	वापस osb->biपंचांगap_blkno == OCFS2_I(inode)->ip_blkno;
पूर्ण

/* This is क्रम local alloc ONLY. Others should use the task-specअगरic
 * apis above. */
पूर्णांक ocfs2_reserve_cluster_biपंचांगap_bits(काष्ठा ocfs2_super *osb,
				      काष्ठा ocfs2_alloc_context *ac);
व्योम ocfs2_मुक्त_ac_resource(काष्ठा ocfs2_alloc_context *ac);

/* given a cluster offset, calculate which block group it beदीर्घs to
 * and वापस that block offset. */
u64 ocfs2_which_cluster_group(काष्ठा inode *inode, u32 cluster);

/*
 * By शेष, ocfs2_पढ़ो_group_descriptor() calls ocfs2_error() when it
 * finds a problem.  A caller that wants to check a group descriptor
 * without going पढ़ोonly should पढ़ो the block with ocfs2_पढ़ो_block[s]()
 * and then checking it with this function.  This is only resize, really.
 * Everyone अन्यथा should be using ocfs2_पढ़ो_group_descriptor().
 */
पूर्णांक ocfs2_check_group_descriptor(काष्ठा super_block *sb,
				 काष्ठा ocfs2_dinode *di,
				 काष्ठा buffer_head *bh);
/*
 * Read a group descriptor block पूर्णांकo *bh.  If *bh is शून्य, a bh will be
 * allocated.  This is a cached पढ़ो.  The descriptor will be validated with
 * ocfs2_validate_group_descriptor().
 */
पूर्णांक ocfs2_पढ़ो_group_descriptor(काष्ठा inode *inode, काष्ठा ocfs2_dinode *di,
				u64 gd_blkno, काष्ठा buffer_head **bh);

पूर्णांक ocfs2_lock_allocators(काष्ठा inode *inode, काष्ठा ocfs2_extent_tree *et,
			  u32 clusters_to_add, u32 extents_to_split,
			  काष्ठा ocfs2_alloc_context **data_ac,
			  काष्ठा ocfs2_alloc_context **meta_ac);

पूर्णांक ocfs2_test_inode_bit(काष्ठा ocfs2_super *osb, u64 blkno, पूर्णांक *res);



/*
 * The following two पूर्णांकerfaces are क्रम ocfs2_create_inode_in_orphan().
 */
पूर्णांक ocfs2_find_new_inode_loc(काष्ठा inode *dir,
			     काष्ठा buffer_head *parent_fe_bh,
			     काष्ठा ocfs2_alloc_context *ac,
			     u64 *fe_blkno);

पूर्णांक ocfs2_claim_new_inode_at_loc(handle_t *handle,
				 काष्ठा inode *dir,
				 काष्ठा ocfs2_alloc_context *ac,
				 u64 *suballoc_loc,
				 u16 *suballoc_bit,
				 u64 di_blkno);

#पूर्ण_अगर /* _CHAINALLOC_H_ */
