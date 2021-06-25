<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * move_extents.c
 *
 * Copyright (C) 2011 Oracle.  All rights reserved.
 */
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/mount.h>
#समावेश <linux/swap.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "ocfs2_ioctl.h"

#समावेश "alloc.h"
#समावेश "localalloc.h"
#समावेश "aops.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "suballoc.h"
#समावेश "uptodate.h"
#समावेश "super.h"
#समावेश "dir.h"
#समावेश "buffer_head_io.h"
#समावेश "sysfile.h"
#समावेश "refcounttree.h"
#समावेश "move_extents.h"

काष्ठा ocfs2_move_extents_context अणु
	काष्ठा inode *inode;
	काष्ठा file *file;
	पूर्णांक स्वतः_defrag;
	पूर्णांक partial;
	पूर्णांक credits;
	u32 new_phys_cpos;
	u32 clusters_moved;
	u64 refcount_loc;
	काष्ठा ocfs2_move_extents *range;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_alloc_context *meta_ac;
	काष्ठा ocfs2_alloc_context *data_ac;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
पूर्ण;

अटल पूर्णांक __ocfs2_move_extent(handle_t *handle,
			       काष्ठा ocfs2_move_extents_context *context,
			       u32 cpos, u32 len, u32 p_cpos, u32 new_p_cpos,
			       पूर्णांक ext_flags)
अणु
	पूर्णांक ret = 0, index;
	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_extent_rec *rec, replace_rec;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_extent_list *el;
	u64 ino = ocfs2_metadata_cache_owner(context->et.et_ci);
	u64 old_blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cpos);

	ret = ocfs2_duplicate_clusters_by_page(handle, inode, cpos,
					       p_cpos, new_p_cpos, len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	स_रखो(&replace_rec, 0, माप(replace_rec));
	replace_rec.e_cpos = cpu_to_le32(cpos);
	replace_rec.e_leaf_clusters = cpu_to_le16(len);
	replace_rec.e_blkno = cpu_to_le64(ocfs2_clusters_to_blocks(inode->i_sb,
								   new_p_cpos));

	path = ocfs2_new_path_from_et(&context->et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(INODE_CACHE(inode), path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	el = path_leaf_el(path);

	index = ocfs2_search_extent_list(el, cpos);
	अगर (index == -1) अणु
		ret = ocfs2_error(inode->i_sb,
				  "Inode %llu has an extent at cpos %u which can no longer be found\n",
				  (अचिन्हित दीर्घ दीर्घ)ino, cpos);
		जाओ out;
	पूर्ण

	rec = &el->l_recs[index];

	BUG_ON(ext_flags != rec->e_flags);
	/*
	 * after moving/defraging to new location, the extent is not going
	 * to be refcounted anymore.
	 */
	replace_rec.e_flags = ext_flags & ~OCFS2_EXT_REFCOUNTED;

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
				      context->et.et_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_split_extent(handle, &context->et, path, index,
				 &replace_rec, context->meta_ac,
				 &context->dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_journal_dirty(handle, context->et.et_root_bh);

	context->new_phys_cpos = new_p_cpos;

	/*
	 * need I to append truncate log क्रम old clusters?
	 */
	अगर (old_blkno) अणु
		अगर (ext_flags & OCFS2_EXT_REFCOUNTED)
			ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(osb->sb,
								 old_blkno),
					len, context->meta_ac,
					&context->dealloc, 1);
		अन्यथा
			ret = ocfs2_truncate_log_append(osb, handle,
							old_blkno, len);
	पूर्ण

	ocfs2_update_inode_fsync_trans(handle, inode, 0);
out:
	ocfs2_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * lock allocator, and reserve appropriate number of bits क्रम
 * meta blocks.
 */
अटल पूर्णांक ocfs2_lock_meta_allocator_move_extents(काष्ठा inode *inode,
					काष्ठा ocfs2_extent_tree *et,
					u32 clusters_to_move,
					u32 extents_to_split,
					काष्ठा ocfs2_alloc_context **meta_ac,
					पूर्णांक extra_blocks,
					पूर्णांक *credits)
अणु
	पूर्णांक ret, num_मुक्त_extents;
	अचिन्हित पूर्णांक max_recs_needed = 2 * extents_to_split + clusters_to_move;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	num_मुक्त_extents = ocfs2_num_मुक्त_extents(et);
	अगर (num_मुक्त_extents < 0) अणु
		ret = num_मुक्त_extents;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!num_मुक्त_extents ||
	    (ocfs2_sparse_alloc(osb) && num_मुक्त_extents < max_recs_needed))
		extra_blocks += ocfs2_extend_meta_needed(et->et_root_el);

	ret = ocfs2_reserve_new_metadata_blocks(osb, extra_blocks, meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण


	*credits += ocfs2_calc_extend_credits(osb->sb, et->et_root_el);

	mlog(0, "reserve metadata_blocks: %d, data_clusters: %u, credits: %d\n",
	     extra_blocks, clusters_to_move, *credits);
out:
	अगर (ret) अणु
		अगर (*meta_ac) अणु
			ocfs2_मुक्त_alloc_context(*meta_ac);
			*meta_ac = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Using one journal handle to guarantee the data consistency in हाल
 * crash happens anywhere.
 *
 *  XXX: defrag can end up with finishing partial extent as requested,
 * due to not enough contiguous clusters can be found in allocator.
 */
अटल पूर्णांक ocfs2_defrag_extent(काष्ठा ocfs2_move_extents_context *context,
			       u32 cpos, u32 phys_cpos, u32 *len, पूर्णांक ext_flags)
अणु
	पूर्णांक ret, credits = 0, extra_blocks = 0, partial = context->partial;
	handle_t *handle;
	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;
	u32 new_phys_cpos, new_len;
	u64 phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
	पूर्णांक need_मुक्त = 0;

	अगर ((ext_flags & OCFS2_EXT_REFCOUNTED) && *len) अणु
		BUG_ON(!ocfs2_is_refcount_inode(inode));
		BUG_ON(!context->refcount_loc);

		ret = ocfs2_lock_refcount_tree(osb, context->refcount_loc, 1,
					       &ref_tree, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		ret = ocfs2_prepare_refcount_change_क्रम_del(inode,
							context->refcount_loc,
							phys_blkno,
							*len,
							&credits,
							&extra_blocks);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_lock_meta_allocator_move_extents(inode, &context->et,
						*len, 1,
						&context->meta_ac,
						extra_blocks, &credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * should be using allocation reservation strategy there?
	 *
	 * अगर (context->data_ac)
	 *	context->data_ac->ac_resv = &OCFS2_I(inode)->ip_la_data_resv;
	 */

	inode_lock(tl_inode);

	अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
		ret = __ocfs2_flush_truncate_log(osb);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock_mutex;
		पूर्ण
	पूर्ण

	/*
	 * Make sure ocfs2_reserve_cluster is called after
	 * __ocfs2_flush_truncate_log, otherwise, dead lock may happen.
	 *
	 * If ocfs2_reserve_cluster is called
	 * beक्रमe __ocfs2_flush_truncate_log, dead lock on global biपंचांगap
	 * may happen.
	 *
	 */
	ret = ocfs2_reserve_clusters(osb, *len, &context->data_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock_mutex;
	पूर्ण

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock_mutex;
	पूर्ण

	ret = __ocfs2_claim_clusters(handle, context->data_ac, 1, *len,
				     &new_phys_cpos, &new_len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * allowing partial extent moving is kind of 'pros and cons', it makes
	 * whole defragmentation less likely to fail, on the contrary, the bad
	 * thing is it may make the fs even more fragmented after moving, let
	 * userspace make a good decision here.
	 */
	अगर (new_len != *len) अणु
		mlog(0, "len_claimed: %u, len: %u\n", new_len, *len);
		अगर (!partial) अणु
			context->range->me_flags &= ~OCFS2_MOVE_EXT_FL_COMPLETE;
			ret = -ENOSPC;
			need_मुक्त = 1;
			जाओ out_commit;
		पूर्ण
	पूर्ण

	mlog(0, "cpos: %u, phys_cpos: %u, new_phys_cpos: %u\n", cpos,
	     phys_cpos, new_phys_cpos);

	ret = __ocfs2_move_extent(handle, context, cpos, new_len, phys_cpos,
				  new_phys_cpos, ext_flags);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	अगर (partial && (new_len != *len))
		*len = new_len;

	/*
	 * Here we should ग_लिखो the new page out first अगर we are
	 * in ग_लिखो-back mode.
	 */
	ret = ocfs2_cow_sync_ग_लिखोback(inode->i_sb, context->inode, cpos, *len);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_commit:
	अगर (need_मुक्त && context->data_ac) अणु
		काष्ठा ocfs2_alloc_context *data_ac = context->data_ac;

		अगर (context->data_ac->ac_which == OCFS2_AC_USE_LOCAL)
			ocfs2_मुक्त_local_alloc_bits(osb, handle, data_ac,
					new_phys_cpos, new_len);
		अन्यथा
			ocfs2_मुक्त_clusters(handle,
					data_ac->ac_inode,
					data_ac->ac_bh,
					ocfs2_clusters_to_blocks(osb->sb, new_phys_cpos),
					new_len);
	पूर्ण

	ocfs2_commit_trans(osb, handle);

out_unlock_mutex:
	inode_unlock(tl_inode);

	अगर (context->data_ac) अणु
		ocfs2_मुक्त_alloc_context(context->data_ac);
		context->data_ac = शून्य;
	पूर्ण

	अगर (context->meta_ac) अणु
		ocfs2_मुक्त_alloc_context(context->meta_ac);
		context->meta_ac = शून्य;
	पूर्ण

out:
	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	वापस ret;
पूर्ण

/*
 * find the victim alloc group, where #blkno fits.
 */
अटल पूर्णांक ocfs2_find_victim_alloc_group(काष्ठा inode *inode,
					 u64 vict_blkno,
					 पूर्णांक type, पूर्णांक slot,
					 पूर्णांक *vict_bit,
					 काष्ठा buffer_head **ret_bh)
अणु
	पूर्णांक ret, i, bits_per_unit = 0;
	u64 blkno;
	अक्षर namebuf[40];

	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *ac_bh = शून्य, *gd_bh = शून्य;
	काष्ठा ocfs2_chain_list *cl;
	काष्ठा ocfs2_chain_rec *rec;
	काष्ठा ocfs2_dinode *ac_dinode;
	काष्ठा ocfs2_group_desc *bg;

	ocfs2_प्र_लिखो_प्रणाली_inode_name(namebuf, माप(namebuf), type, slot);
	ret = ocfs2_lookup_ino_from_name(osb->sys_root_inode, namebuf,
					 म_माप(namebuf), &blkno);
	अगर (ret) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &ac_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ac_dinode = (काष्ठा ocfs2_dinode *)ac_bh->b_data;
	cl = &(ac_dinode->id2.i_chain);
	rec = &(cl->cl_recs[0]);

	अगर (type == GLOBAL_BITMAP_SYSTEM_INODE)
		bits_per_unit = osb->s_clustersize_bits -
					inode->i_sb->s_blocksize_bits;
	/*
	 * 'vict_blkno' was out of the valid range.
	 */
	अगर ((vict_blkno < le64_to_cpu(rec->c_blkno)) ||
	    (vict_blkno >= ((u64)le32_to_cpu(ac_dinode->id1.biपंचांगap1.i_total) <<
				bits_per_unit))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < le16_to_cpu(cl->cl_next_मुक्त_rec); i++) अणु

		rec = &(cl->cl_recs[i]);
		अगर (!rec)
			जारी;

		bg = शून्य;

		करो अणु
			अगर (!bg)
				blkno = le64_to_cpu(rec->c_blkno);
			अन्यथा
				blkno = le64_to_cpu(bg->bg_next_group);

			अगर (gd_bh) अणु
				brअन्यथा(gd_bh);
				gd_bh = शून्य;
			पूर्ण

			ret = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &gd_bh);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			bg = (काष्ठा ocfs2_group_desc *)gd_bh->b_data;

			अगर (vict_blkno < (le64_to_cpu(bg->bg_blkno) +
						le16_to_cpu(bg->bg_bits))) अणु

				*ret_bh = gd_bh;
				*vict_bit = (vict_blkno - blkno) >>
							bits_per_unit;
				mlog(0, "find the victim group: #%llu, "
				     "total_bits: %u, vict_bit: %u\n",
				     blkno, le16_to_cpu(bg->bg_bits),
				     *vict_bit);
				जाओ out;
			पूर्ण

		पूर्ण जबतक (le64_to_cpu(bg->bg_next_group));
	पूर्ण

	ret = -EINVAL;
out:
	brअन्यथा(ac_bh);

	/*
	 * caller has to release the gd_bh properly.
	 */
	वापस ret;
पूर्ण

/*
 * XXX: helper to validate and adjust moving goal.
 */
अटल पूर्णांक ocfs2_validate_and_adjust_move_goal(काष्ठा inode *inode,
					       काष्ठा ocfs2_move_extents *range)
अणु
	पूर्णांक ret, goal_bit = 0;

	काष्ठा buffer_head *gd_bh = शून्य;
	काष्ठा ocfs2_group_desc *bg;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	पूर्णांक c_to_b = 1 << (osb->s_clustersize_bits -
					inode->i_sb->s_blocksize_bits);

	/*
	 * make goal become cluster aligned.
	 */
	range->me_goal = ocfs2_block_to_cluster_start(inode->i_sb,
						      range->me_goal);
	/*
	 * validate goal sits within global_biपंचांगap, and वापस the victim
	 * group desc
	 */
	ret = ocfs2_find_victim_alloc_group(inode, range->me_goal,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT,
					    &goal_bit, &gd_bh);
	अगर (ret)
		जाओ out;

	bg = (काष्ठा ocfs2_group_desc *)gd_bh->b_data;

	/*
	 * moving goal is not allowd to start with a group desc blok(#0 blk)
	 * let's compromise to the latter cluster.
	 */
	अगर (range->me_goal == le64_to_cpu(bg->bg_blkno))
		range->me_goal += c_to_b;

	/*
	 * movement is not gonna cross two groups.
	 */
	अगर ((le16_to_cpu(bg->bg_bits) - goal_bit) * osb->s_clustersize <
								range->me_len) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/*
	 * more exact validations/adjusपंचांगents will be perक्रमmed later during
	 * moving operation क्रम each extent range.
	 */
	mlog(0, "extents get ready to be moved to #%llu block\n",
	     range->me_goal);

out:
	brअन्यथा(gd_bh);

	वापस ret;
पूर्ण

अटल व्योम ocfs2_probe_alloc_group(काष्ठा inode *inode, काष्ठा buffer_head *bh,
				    पूर्णांक *goal_bit, u32 move_len, u32 max_hop,
				    u32 *phys_cpos)
अणु
	पूर्णांक i, used, last_मुक्त_bits = 0, base_bit = *goal_bit;
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *)bh->b_data;
	u32 base_cpos = ocfs2_blocks_to_clusters(inode->i_sb,
						 le64_to_cpu(gd->bg_blkno));

	क्रम (i = base_bit; i < le16_to_cpu(gd->bg_bits); i++) अणु

		used = ocfs2_test_bit(i, (अचिन्हित दीर्घ *)gd->bg_biपंचांगap);
		अगर (used) अणु
			/*
			 * we even tried searching the मुक्त chunk by jumping
			 * a 'max_hop' distance, but still failed.
			 */
			अगर ((i - base_bit) > max_hop) अणु
				*phys_cpos = 0;
				अवरोध;
			पूर्ण

			अगर (last_मुक्त_bits)
				last_मुक्त_bits = 0;

			जारी;
		पूर्ण अन्यथा
			last_मुक्त_bits++;

		अगर (last_मुक्त_bits == move_len) अणु
			*goal_bit = i;
			*phys_cpos = base_cpos + i;
			अवरोध;
		पूर्ण
	पूर्ण

	mlog(0, "found phys_cpos: %u to fit the wanted moving.\n", *phys_cpos);
पूर्ण

अटल पूर्णांक ocfs2_move_extent(काष्ठा ocfs2_move_extents_context *context,
			     u32 cpos, u32 phys_cpos, u32 *new_phys_cpos,
			     u32 len, पूर्णांक ext_flags)
अणु
	पूर्णांक ret, credits = 0, extra_blocks = 0, goal_bit = 0;
	handle_t *handle;
	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा inode *gb_inode = शून्य;
	काष्ठा buffer_head *gb_bh = शून्य;
	काष्ठा buffer_head *gd_bh = शून्य;
	काष्ठा ocfs2_group_desc *gd;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;
	u32 move_max_hop = ocfs2_blocks_to_clusters(inode->i_sb,
						    context->range->me_threshold);
	u64 phys_blkno, new_phys_blkno;

	phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);

	अगर ((ext_flags & OCFS2_EXT_REFCOUNTED) && len) अणु
		BUG_ON(!ocfs2_is_refcount_inode(inode));
		BUG_ON(!context->refcount_loc);

		ret = ocfs2_lock_refcount_tree(osb, context->refcount_loc, 1,
					       &ref_tree, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		ret = ocfs2_prepare_refcount_change_क्रम_del(inode,
							context->refcount_loc,
							phys_blkno,
							len,
							&credits,
							&extra_blocks);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_lock_meta_allocator_move_extents(inode, &context->et,
						len, 1,
						&context->meta_ac,
						extra_blocks, &credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * need to count 2 extra credits क्रम global_biपंचांगap inode and
	 * group descriptor.
	 */
	credits += OCFS2_INODE_UPDATE_CREDITS + 1;

	/*
	 * ocfs2_move_extent() didn't reserve any clusters in lock_allocators()
	 * logic, जबतक we still need to lock the global_biपंचांगap.
	 */
	gb_inode = ocfs2_get_प्रणाली_file_inode(osb, GLOBAL_BITMAP_SYSTEM_INODE,
					       OCFS2_INVALID_SLOT);
	अगर (!gb_inode) अणु
		mlog(ML_ERROR, "unable to get global_bitmap inode\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	inode_lock(gb_inode);

	ret = ocfs2_inode_lock(gb_inode, &gb_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock_gb_mutex;
	पूर्ण

	inode_lock(tl_inode);

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock_tl_inode;
	पूर्ण

	new_phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, *new_phys_cpos);
	ret = ocfs2_find_victim_alloc_group(inode, new_phys_blkno,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT,
					    &goal_bit, &gd_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * probe the victim cluster group to find a proper
	 * region to fit wanted movement, it even will perfrom
	 * a best-efक्रमt attempt by compromising to a threshold
	 * around the goal.
	 */
	ocfs2_probe_alloc_group(inode, gd_bh, &goal_bit, len, move_max_hop,
				new_phys_cpos);
	अगर (!*new_phys_cpos) अणु
		ret = -ENOSPC;
		जाओ out_commit;
	पूर्ण

	ret = __ocfs2_move_extent(handle, context, cpos, len, phys_cpos,
				  *new_phys_cpos, ext_flags);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	gd = (काष्ठा ocfs2_group_desc *)gd_bh->b_data;
	ret = ocfs2_alloc_dinode_update_counts(gb_inode, handle, gb_bh, len,
					       le16_to_cpu(gd->bg_chain));
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = ocfs2_block_group_set_bits(handle, gb_inode, gd, gd_bh,
					 goal_bit, len);
	अगर (ret) अणु
		ocfs2_rollback_alloc_dinode_counts(gb_inode, gb_bh, len,
					       le16_to_cpu(gd->bg_chain));
		mlog_त्रुटि_सं(ret);
	पूर्ण

	/*
	 * Here we should ग_लिखो the new page out first अगर we are
	 * in ग_लिखो-back mode.
	 */
	ret = ocfs2_cow_sync_ग_लिखोback(inode->i_sb, context->inode, cpos, len);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);
	brअन्यथा(gd_bh);

out_unlock_tl_inode:
	inode_unlock(tl_inode);

	ocfs2_inode_unlock(gb_inode, 1);
out_unlock_gb_mutex:
	inode_unlock(gb_inode);
	brअन्यथा(gb_bh);
	iput(gb_inode);

out:
	अगर (context->meta_ac) अणु
		ocfs2_मुक्त_alloc_context(context->meta_ac);
		context->meta_ac = शून्य;
	पूर्ण

	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	वापस ret;
पूर्ण

/*
 * Helper to calculate the defraging length in one run according to threshold.
 */
अटल व्योम ocfs2_calc_extent_defrag_len(u32 *alloc_size, u32 *len_defraged,
					 u32 threshold, पूर्णांक *skip)
अणु
	अगर ((*alloc_size + *len_defraged) < threshold) अणु
		/*
		 * proceed defragmentation until we meet the thresh
		 */
		*len_defraged += *alloc_size;
	पूर्ण अन्यथा अगर (*len_defraged == 0) अणु
		/*
		 * XXX: skip a large extent.
		 */
		*skip = 1;
	पूर्ण अन्यथा अणु
		/*
		 * split this extent to coalesce with क्रमmer pieces as
		 * to reach the threshold.
		 *
		 * we're करोne here with one cycle of defragmentation
		 * in a size of 'thresh', resetting 'len_defraged'
		 * क्रमces a new defragmentation.
		 */
		*alloc_size = threshold - *len_defraged;
		*len_defraged = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __ocfs2_move_extents_range(काष्ठा buffer_head *di_bh,
				काष्ठा ocfs2_move_extents_context *context)
अणु
	पूर्णांक ret = 0, flags, करो_defrag, skip = 0;
	u32 cpos, phys_cpos, move_start, len_to_move, alloc_size;
	u32 len_defraged = 0, defrag_thresh = 0, new_phys_cpos = 0;

	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_move_extents *range = context->range;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर ((i_size_पढ़ो(inode) == 0) || (range->me_len == 0))
		वापस 0;

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस 0;

	context->refcount_loc = le64_to_cpu(di->i_refcount_loc);

	ocfs2_init_dinode_extent_tree(&context->et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&context->dealloc);

	/*
	 * TO-DO XXX:
	 *
	 * - xattr extents.
	 */

	करो_defrag = context->स्वतः_defrag;

	/*
	 * extents moving happens in unit of clusters, क्रम the sake
	 * of simplicity, we may ignore two clusters where 'byte_start'
	 * and 'byte_start + len' were within.
	 */
	move_start = ocfs2_clusters_क्रम_bytes(osb->sb, range->me_start);
	len_to_move = (range->me_start + range->me_len) >>
						osb->s_clustersize_bits;
	अगर (len_to_move >= move_start)
		len_to_move -= move_start;
	अन्यथा
		len_to_move = 0;

	अगर (करो_defrag) अणु
		defrag_thresh = range->me_threshold >> osb->s_clustersize_bits;
		अगर (defrag_thresh <= 1)
			जाओ करोne;
	पूर्ण अन्यथा
		new_phys_cpos = ocfs2_blocks_to_clusters(inode->i_sb,
							 range->me_goal);

	mlog(0, "Inode: %llu, start: %llu, len: %llu, cstart: %u, clen: %u, "
	     "thresh: %u\n",
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
	     (अचिन्हित दीर्घ दीर्घ)range->me_start,
	     (अचिन्हित दीर्घ दीर्घ)range->me_len,
	     move_start, len_to_move, defrag_thresh);

	cpos = move_start;
	जबतक (len_to_move) अणु
		ret = ocfs2_get_clusters(inode, cpos, &phys_cpos, &alloc_size,
					 &flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (alloc_size > len_to_move)
			alloc_size = len_to_move;

		/*
		 * XXX: how to deal with a hole:
		 *
		 * - skip the hole of course
		 * - क्रमce a new defragmentation
		 */
		अगर (!phys_cpos) अणु
			अगर (करो_defrag)
				len_defraged = 0;

			जाओ next;
		पूर्ण

		अगर (करो_defrag) अणु
			ocfs2_calc_extent_defrag_len(&alloc_size, &len_defraged,
						     defrag_thresh, &skip);
			/*
			 * skip large extents
			 */
			अगर (skip) अणु
				skip = 0;
				जाओ next;
			पूर्ण

			mlog(0, "#Defrag: cpos: %u, phys_cpos: %u, "
			     "alloc_size: %u, len_defraged: %u\n",
			     cpos, phys_cpos, alloc_size, len_defraged);

			ret = ocfs2_defrag_extent(context, cpos, phys_cpos,
						  &alloc_size, flags);
		पूर्ण अन्यथा अणु
			ret = ocfs2_move_extent(context, cpos, phys_cpos,
						&new_phys_cpos, alloc_size,
						flags);

			new_phys_cpos += alloc_size;
		पूर्ण

		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		context->clusters_moved += alloc_size;
next:
		cpos += alloc_size;
		len_to_move -= alloc_size;
	पूर्ण

करोne:
	range->me_flags |= OCFS2_MOVE_EXT_FL_COMPLETE;

out:
	range->me_moved_len = ocfs2_clusters_to_bytes(osb->sb,
						      context->clusters_moved);
	range->me_new_offset = ocfs2_clusters_to_bytes(osb->sb,
						       context->new_phys_cpos);

	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &context->dealloc);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_move_extents(काष्ठा ocfs2_move_extents_context *context)
अणु
	पूर्णांक status;
	handle_t *handle;
	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_dinode *di;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	inode_lock(inode);

	/*
	 * This prevents concurrent ग_लिखोs from other nodes
	 */
	status = ocfs2_rw_lock(inode, 1);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	status = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_rw_unlock;
	पूर्ण

	/*
	 * rememer ip_xattr_sem also needs to be held अगर necessary
	 */
	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	status = __ocfs2_move_extents_range(di_bh, context);

	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_inode_unlock;
	पूर्ण

	/*
	 * We update स_समय क्रम these changes
	 */
	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out_inode_unlock;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	inode->i_स_समय = current_समय(inode);
	di->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	di->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_inode_unlock:
	brअन्यथा(di_bh);
	ocfs2_inode_unlock(inode, 1);
out_rw_unlock:
	ocfs2_rw_unlock(inode, 1);
out:
	inode_unlock(inode);

	वापस status;
पूर्ण

पूर्णांक ocfs2_ioctl_move_extents(काष्ठा file *filp, व्योम __user *argp)
अणु
	पूर्णांक status;

	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ocfs2_move_extents range;
	काष्ठा ocfs2_move_extents_context *context;

	अगर (!argp)
		वापस -EINVAL;

	status = mnt_want_ग_लिखो_file(filp);
	अगर (status)
		वापस status;

	अगर ((!S_ISREG(inode->i_mode)) || !(filp->f_mode & FMODE_WRITE)) अणु
		status = -EPERM;
		जाओ out_drop;
	पूर्ण

	अगर (inode->i_flags & (S_IMMUTABLE|S_APPEND)) अणु
		status = -EPERM;
		जाओ out_drop;
	पूर्ण

	context = kzalloc(माप(काष्ठा ocfs2_move_extents_context), GFP_NOFS);
	अगर (!context) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out_drop;
	पूर्ण

	context->inode = inode;
	context->file = filp;

	अगर (copy_from_user(&range, argp, माप(range))) अणु
		status = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	अगर (range.me_start > i_size_पढ़ो(inode)) अणु
		status = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (range.me_start + range.me_len > i_size_पढ़ो(inode))
			range.me_len = i_size_पढ़ो(inode) - range.me_start;

	context->range = &range;

	अगर (range.me_flags & OCFS2_MOVE_EXT_FL_AUTO_DEFRAG) अणु
		context->स्वतः_defrag = 1;
		/*
		 * ok, the शेष theshold क्रम the defragmentation
		 * is 1M, since our maximum clustersize was 1M also.
		 * any thought?
		 */
		अगर (!range.me_threshold)
			range.me_threshold = 1024 * 1024;

		अगर (range.me_threshold > i_size_पढ़ो(inode))
			range.me_threshold = i_size_पढ़ो(inode);

		अगर (range.me_flags & OCFS2_MOVE_EXT_FL_PART_DEFRAG)
			context->partial = 1;
	पूर्ण अन्यथा अणु
		/*
		 * first best-efक्रमt attempt to validate and adjust the goal
		 * (physical address in block), जबतक it can't guarantee later
		 * operation can succeed all the समय since global_biपंचांगap may
		 * change a bit over समय.
		 */

		status = ocfs2_validate_and_adjust_move_goal(inode, &range);
		अगर (status)
			जाओ out_copy;
	पूर्ण

	status = ocfs2_move_extents(context);
	अगर (status)
		mlog_त्रुटि_सं(status);
out_copy:
	/*
	 * movement/defragmentation may end up being partially completed,
	 * that's the reason why we need to वापस userspace the finished
	 * length and new_offset even अगर failure happens somewhere.
	 */
	अगर (copy_to_user(argp, &range, माप(range)))
		status = -EFAULT;

out_मुक्त:
	kमुक्त(context);
out_drop:
	mnt_drop_ग_लिखो_file(filp);

	वापस status;
पूर्ण
