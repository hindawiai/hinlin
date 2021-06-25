<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * extent_map.c
 *
 * Block/Cluster mapping functions
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/fiemap.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "inode.h"
#समावेश "super.h"
#समावेश "symlink.h"
#समावेश "aops.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

/*
 * The extent caching implementation is पूर्णांकentionally trivial.
 *
 * We only cache a small number of extents stored directly on the
 * inode, so linear order operations are acceptable. If we ever want
 * to increase the size of the extent map, then these algorithms must
 * get smarter.
 */

व्योम ocfs2_extent_map_init(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	oi->ip_extent_map.em_num_items = 0;
	INIT_LIST_HEAD(&oi->ip_extent_map.em_list);
पूर्ण

अटल व्योम __ocfs2_extent_map_lookup(काष्ठा ocfs2_extent_map *em,
				      अचिन्हित पूर्णांक cpos,
				      काष्ठा ocfs2_extent_map_item **ret_emi)
अणु
	अचिन्हित पूर्णांक range;
	काष्ठा ocfs2_extent_map_item *emi;

	*ret_emi = शून्य;

	list_क्रम_each_entry(emi, &em->em_list, ei_list) अणु
		range = emi->ei_cpos + emi->ei_clusters;

		अगर (cpos >= emi->ei_cpos && cpos < range) अणु
			list_move(&emi->ei_list, &em->em_list);

			*ret_emi = emi;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_extent_map_lookup(काष्ठा inode *inode, अचिन्हित पूर्णांक cpos,
				   अचिन्हित पूर्णांक *phys, अचिन्हित पूर्णांक *len,
				   अचिन्हित पूर्णांक *flags)
अणु
	अचिन्हित पूर्णांक coff;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_extent_map_item *emi;

	spin_lock(&oi->ip_lock);

	__ocfs2_extent_map_lookup(&oi->ip_extent_map, cpos, &emi);
	अगर (emi) अणु
		coff = cpos - emi->ei_cpos;
		*phys = emi->ei_phys + coff;
		अगर (len)
			*len = emi->ei_clusters - coff;
		अगर (flags)
			*flags = emi->ei_flags;
	पूर्ण

	spin_unlock(&oi->ip_lock);

	अगर (emi == शून्य)
		वापस -ENOENT;

	वापस 0;
पूर्ण

/*
 * Forget about all clusters equal to or greater than cpos.
 */
व्योम ocfs2_extent_map_trunc(काष्ठा inode *inode, अचिन्हित पूर्णांक cpos)
अणु
	काष्ठा ocfs2_extent_map_item *emi, *n;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_extent_map *em = &oi->ip_extent_map;
	LIST_HEAD(पंचांगp_list);
	अचिन्हित पूर्णांक range;

	spin_lock(&oi->ip_lock);
	list_क्रम_each_entry_safe(emi, n, &em->em_list, ei_list) अणु
		अगर (emi->ei_cpos >= cpos) अणु
			/* Full truncate of this record. */
			list_move(&emi->ei_list, &पंचांगp_list);
			BUG_ON(em->em_num_items == 0);
			em->em_num_items--;
			जारी;
		पूर्ण

		range = emi->ei_cpos + emi->ei_clusters;
		अगर (range > cpos) अणु
			/* Partial truncate */
			emi->ei_clusters = cpos - emi->ei_cpos;
		पूर्ण
	पूर्ण
	spin_unlock(&oi->ip_lock);

	list_क्रम_each_entry_safe(emi, n, &पंचांगp_list, ei_list) अणु
		list_del(&emi->ei_list);
		kमुक्त(emi);
	पूर्ण
पूर्ण

/*
 * Is any part of emi2 contained within emi1
 */
अटल पूर्णांक ocfs2_ei_is_contained(काष्ठा ocfs2_extent_map_item *emi1,
				 काष्ठा ocfs2_extent_map_item *emi2)
अणु
	अचिन्हित पूर्णांक range1, range2;

	/*
	 * Check अगर logical start of emi2 is inside emi1
	 */
	range1 = emi1->ei_cpos + emi1->ei_clusters;
	अगर (emi2->ei_cpos >= emi1->ei_cpos && emi2->ei_cpos < range1)
		वापस 1;

	/*
	 * Check अगर logical end of emi2 is inside emi1
	 */
	range2 = emi2->ei_cpos + emi2->ei_clusters;
	अगर (range2 > emi1->ei_cpos && range2 <= range1)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ocfs2_copy_emi_fields(काष्ठा ocfs2_extent_map_item *dest,
				  काष्ठा ocfs2_extent_map_item *src)
अणु
	dest->ei_cpos = src->ei_cpos;
	dest->ei_phys = src->ei_phys;
	dest->ei_clusters = src->ei_clusters;
	dest->ei_flags = src->ei_flags;
पूर्ण

/*
 * Try to merge emi with ins. Returns 1 अगर merge succeeds, zero
 * otherwise.
 */
अटल पूर्णांक ocfs2_try_to_merge_extent_map(काष्ठा ocfs2_extent_map_item *emi,
					 काष्ठा ocfs2_extent_map_item *ins)
अणु
	/*
	 * Handle contiguousness
	 */
	अगर (ins->ei_phys == (emi->ei_phys + emi->ei_clusters) &&
	    ins->ei_cpos == (emi->ei_cpos + emi->ei_clusters) &&
	    ins->ei_flags == emi->ei_flags) अणु
		emi->ei_clusters += ins->ei_clusters;
		वापस 1;
	पूर्ण अन्यथा अगर ((ins->ei_phys + ins->ei_clusters) == emi->ei_phys &&
		   (ins->ei_cpos + ins->ei_clusters) == emi->ei_cpos &&
		   ins->ei_flags == emi->ei_flags) अणु
		emi->ei_phys = ins->ei_phys;
		emi->ei_cpos = ins->ei_cpos;
		emi->ei_clusters += ins->ei_clusters;
		वापस 1;
	पूर्ण

	/*
	 * Overlapping extents - this shouldn't happen unless we've
	 * split an extent to change it's flags. That is exceedingly
	 * rare, so there's no sense in trying to optimize it yet.
	 */
	अगर (ocfs2_ei_is_contained(emi, ins) ||
	    ocfs2_ei_is_contained(ins, emi)) अणु
		ocfs2_copy_emi_fields(emi, ins);
		वापस 1;
	पूर्ण

	/* No merge was possible. */
	वापस 0;
पूर्ण

/*
 * In order to reduce complनिकासy on the caller, this insert function
 * is पूर्णांकentionally liberal in what it will accept.
 *
 * The only rule is that the truncate call *must* be used whenever
 * records have been deleted. This aव्योमs inserting overlapping
 * records with dअगरferent physical mappings.
 */
व्योम ocfs2_extent_map_insert_rec(काष्ठा inode *inode,
				 काष्ठा ocfs2_extent_rec *rec)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_extent_map *em = &oi->ip_extent_map;
	काष्ठा ocfs2_extent_map_item *emi, *new_emi = शून्य;
	काष्ठा ocfs2_extent_map_item ins;

	ins.ei_cpos = le32_to_cpu(rec->e_cpos);
	ins.ei_phys = ocfs2_blocks_to_clusters(inode->i_sb,
					       le64_to_cpu(rec->e_blkno));
	ins.ei_clusters = le16_to_cpu(rec->e_leaf_clusters);
	ins.ei_flags = rec->e_flags;

search:
	spin_lock(&oi->ip_lock);

	list_क्रम_each_entry(emi, &em->em_list, ei_list) अणु
		अगर (ocfs2_try_to_merge_extent_map(emi, &ins)) अणु
			list_move(&emi->ei_list, &em->em_list);
			spin_unlock(&oi->ip_lock);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * No item could be merged.
	 *
	 * Either allocate and add a new item, or overग_लिखो the last recently
	 * inserted.
	 */

	अगर (em->em_num_items < OCFS2_MAX_EXTENT_MAP_ITEMS) अणु
		अगर (new_emi == शून्य) अणु
			spin_unlock(&oi->ip_lock);

			new_emi = kदो_स्मृति(माप(*new_emi), GFP_NOFS);
			अगर (new_emi == शून्य)
				जाओ out;

			जाओ search;
		पूर्ण

		ocfs2_copy_emi_fields(new_emi, &ins);
		list_add(&new_emi->ei_list, &em->em_list);
		em->em_num_items++;
		new_emi = शून्य;
	पूर्ण अन्यथा अणु
		BUG_ON(list_empty(&em->em_list) || em->em_num_items == 0);
		emi = list_entry(em->em_list.prev,
				 काष्ठा ocfs2_extent_map_item, ei_list);
		list_move(&emi->ei_list, &em->em_list);
		ocfs2_copy_emi_fields(emi, &ins);
	पूर्ण

	spin_unlock(&oi->ip_lock);

out:
	kमुक्त(new_emi);
पूर्ण

अटल पूर्णांक ocfs2_last_eb_is_empty(काष्ठा inode *inode,
				  काष्ठा ocfs2_dinode *di)
अणु
	पूर्णांक ret, next_मुक्त;
	u64 last_eb_blk = le64_to_cpu(di->i_last_eb_blk);
	काष्ठा buffer_head *eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;

	ret = ocfs2_पढ़ो_extent_block(INODE_CACHE(inode), last_eb_blk, &eb_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
	el = &eb->h_list;

	अगर (el->l_tree_depth) अणु
		ocfs2_error(inode->i_sb,
			    "Inode %lu has non zero tree depth in leaf block %llu\n",
			    inode->i_ino,
			    (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
		ret = -EROFS;
		जाओ out;
	पूर्ण

	next_मुक्त = le16_to_cpu(el->l_next_मुक्त_rec);

	अगर (next_मुक्त == 0 ||
	    (next_मुक्त == 1 && ocfs2_is_empty_extent(&el->l_recs[0])))
		ret = 1;

out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

/*
 * Return the 1st index within el which contains an extent start
 * larger than v_cluster.
 */
अटल पूर्णांक ocfs2_search_क्रम_hole_index(काष्ठा ocfs2_extent_list *el,
				       u32 v_cluster)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_extent_rec *rec;

	क्रम(i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++) अणु
		rec = &el->l_recs[i];

		अगर (v_cluster < le32_to_cpu(rec->e_cpos))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

/*
 * Figure out the size of a hole which starts at v_cluster within the given
 * extent list.
 *
 * If there is no more allocation past v_cluster, we वापस the maximum
 * cluster size minus v_cluster.
 *
 * If we have in-inode extents, then el poपूर्णांकs to the dinode list and
 * eb_bh is शून्य. Otherwise, eb_bh should poपूर्णांक to the extent block
 * containing el.
 */
पूर्णांक ocfs2_figure_hole_clusters(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा ocfs2_extent_list *el,
			       काष्ठा buffer_head *eb_bh,
			       u32 v_cluster,
			       u32 *num_clusters)
अणु
	पूर्णांक ret, i;
	काष्ठा buffer_head *next_eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb, *next_eb;

	i = ocfs2_search_क्रम_hole_index(el, v_cluster);

	अगर (i == le16_to_cpu(el->l_next_मुक्त_rec) && eb_bh) अणु
		eb = (काष्ठा ocfs2_extent_block *)eb_bh->b_data;

		/*
		 * Check the next leaf क्रम any extents.
		 */

		अगर (le64_to_cpu(eb->h_next_leaf_blk) == 0ULL)
			जाओ no_more_extents;

		ret = ocfs2_पढ़ो_extent_block(ci,
					      le64_to_cpu(eb->h_next_leaf_blk),
					      &next_eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		next_eb = (काष्ठा ocfs2_extent_block *)next_eb_bh->b_data;
		el = &next_eb->h_list;
		i = ocfs2_search_क्रम_hole_index(el, v_cluster);
	पूर्ण

no_more_extents:
	अगर (i == le16_to_cpu(el->l_next_मुक्त_rec)) अणु
		/*
		 * We're at the end of our existing allocation. Just
		 * वापस the maximum number of clusters we could
		 * possibly allocate.
		 */
		*num_clusters = अच_पूर्णांक_उच्च - v_cluster;
	पूर्ण अन्यथा अणु
		*num_clusters = le32_to_cpu(el->l_recs[i].e_cpos) - v_cluster;
	पूर्ण

	ret = 0;
out:
	brअन्यथा(next_eb_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_get_clusters_nocache(काष्ठा inode *inode,
				      काष्ठा buffer_head *di_bh,
				      u32 v_cluster, अचिन्हित पूर्णांक *hole_len,
				      काष्ठा ocfs2_extent_rec *ret_rec,
				      अचिन्हित पूर्णांक *is_last)
अणु
	पूर्णांक i, ret, tree_height, len;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा buffer_head *eb_bh = शून्य;

	स_रखो(ret_rec, 0, माप(*ret_rec));
	अगर (is_last)
		*is_last = 0;

	di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	el = &di->id2.i_list;
	tree_height = le16_to_cpu(el->l_tree_depth);

	अगर (tree_height > 0) अणु
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, v_cluster,
				      &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ocfs2_error(inode->i_sb,
				    "Inode %lu has non zero tree depth in leaf block %llu\n",
				    inode->i_ino,
				    (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			ret = -EROFS;
			जाओ out;
		पूर्ण
	पूर्ण

	i = ocfs2_search_extent_list(el, v_cluster);
	अगर (i == -1) अणु
		/*
		 * Holes can be larger than the maximum size of an
		 * extent, so we वापस their lengths in a separate
		 * field.
		 */
		अगर (hole_len) अणु
			ret = ocfs2_figure_hole_clusters(INODE_CACHE(inode),
							 el, eb_bh,
							 v_cluster, &len);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			*hole_len = len;
		पूर्ण
		जाओ out_hole;
	पूर्ण

	rec = &el->l_recs[i];

	BUG_ON(v_cluster < le32_to_cpu(rec->e_cpos));

	अगर (!rec->e_blkno) अणु
		ocfs2_error(inode->i_sb,
			    "Inode %lu has bad extent record (%u, %u, 0)\n",
			    inode->i_ino,
			    le32_to_cpu(rec->e_cpos),
			    ocfs2_rec_clusters(el, rec));
		ret = -EROFS;
		जाओ out;
	पूर्ण

	*ret_rec = *rec;

	/*
	 * Checking क्रम last extent is potentially expensive - we
	 * might have to look at the next leaf over to see अगर it's
	 * empty.
	 *
	 * The first two checks are to see whether the caller even
	 * cares क्रम this inक्रमmation, and अगर the extent is at least
	 * the last in it's list.
	 *
	 * If those hold true, then the extent is last अगर any of the
	 * additional conditions hold true:
	 *  - Extent list is in-inode
	 *  - Extent list is right-most
	 *  - Extent list is 2nd to righपंचांगost, with empty right-most
	 */
	अगर (is_last) अणु
		अगर (i == (le16_to_cpu(el->l_next_मुक्त_rec) - 1)) अणु
			अगर (tree_height == 0)
				*is_last = 1;
			अन्यथा अगर (eb->h_blkno == di->i_last_eb_blk)
				*is_last = 1;
			अन्यथा अगर (eb->h_next_leaf_blk == di->i_last_eb_blk) अणु
				ret = ocfs2_last_eb_is_empty(inode, di);
				अगर (ret < 0) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण
				अगर (ret == 1)
					*is_last = 1;
			पूर्ण
		पूर्ण
	पूर्ण

out_hole:
	ret = 0;
out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

अटल व्योम ocfs2_relative_extent_offsets(काष्ठा super_block *sb,
					  u32 v_cluster,
					  काष्ठा ocfs2_extent_rec *rec,
					  u32 *p_cluster, u32 *num_clusters)

अणु
	u32 coff = v_cluster - le32_to_cpu(rec->e_cpos);

	*p_cluster = ocfs2_blocks_to_clusters(sb, le64_to_cpu(rec->e_blkno));
	*p_cluster = *p_cluster + coff;

	अगर (num_clusters)
		*num_clusters = le16_to_cpu(rec->e_leaf_clusters) - coff;
पूर्ण

पूर्णांक ocfs2_xattr_get_clusters(काष्ठा inode *inode, u32 v_cluster,
			     u32 *p_cluster, u32 *num_clusters,
			     काष्ठा ocfs2_extent_list *el,
			     अचिन्हित पूर्णांक *extent_flags)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा buffer_head *eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_rec *rec;
	u32 coff;

	अगर (el->l_tree_depth) अणु
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, v_cluster,
				      &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ocfs2_error(inode->i_sb,
				    "Inode %lu has non zero tree depth in xattr leaf block %llu\n",
				    inode->i_ino,
				    (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			ret = -EROFS;
			जाओ out;
		पूर्ण
	पूर्ण

	i = ocfs2_search_extent_list(el, v_cluster);
	अगर (i == -1) अणु
		ret = -EROFS;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण अन्यथा अणु
		rec = &el->l_recs[i];
		BUG_ON(v_cluster < le32_to_cpu(rec->e_cpos));

		अगर (!rec->e_blkno) अणु
			ocfs2_error(inode->i_sb,
				    "Inode %lu has bad extent record (%u, %u, 0) in xattr\n",
				    inode->i_ino,
				    le32_to_cpu(rec->e_cpos),
				    ocfs2_rec_clusters(el, rec));
			ret = -EROFS;
			जाओ out;
		पूर्ण
		coff = v_cluster - le32_to_cpu(rec->e_cpos);
		*p_cluster = ocfs2_blocks_to_clusters(inode->i_sb,
						    le64_to_cpu(rec->e_blkno));
		*p_cluster = *p_cluster + coff;
		अगर (num_clusters)
			*num_clusters = ocfs2_rec_clusters(el, rec) - coff;

		अगर (extent_flags)
			*extent_flags = rec->e_flags;
	पूर्ण
out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_get_clusters(काष्ठा inode *inode, u32 v_cluster,
		       u32 *p_cluster, u32 *num_clusters,
		       अचिन्हित पूर्णांक *extent_flags)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक hole_len, flags = 0;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_extent_rec rec;

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = -दुस्फल;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_extent_map_lookup(inode, v_cluster, p_cluster,
				      num_clusters, extent_flags);
	अगर (ret == 0)
		जाओ out;

	ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_get_clusters_nocache(inode, di_bh, v_cluster, &hole_len,
					 &rec, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (rec.e_blkno == 0ULL) अणु
		/*
		 * A hole was found. Return some canned values that
		 * callers can key on. If asked क्रम, num_clusters will
		 * be populated with the size of the hole.
		 */
		*p_cluster = 0;
		अगर (num_clusters) अणु
			*num_clusters = hole_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		ocfs2_relative_extent_offsets(inode->i_sb, v_cluster, &rec,
					      p_cluster, num_clusters);
		flags = rec.e_flags;

		ocfs2_extent_map_insert_rec(inode, &rec);
	पूर्ण

	अगर (extent_flags)
		*extent_flags = flags;

out:
	brअन्यथा(di_bh);
	वापस ret;
पूर्ण

/*
 * This expects alloc_sem to be held. The allocation cannot change at
 * all जबतक the map is in the process of being updated.
 */
पूर्णांक ocfs2_extent_map_get_blocks(काष्ठा inode *inode, u64 v_blkno, u64 *p_blkno,
				u64 *ret_count, अचिन्हित पूर्णांक *extent_flags)
अणु
	पूर्णांक ret;
	पूर्णांक bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	u32 cpos, num_clusters, p_cluster;
	u64 boff = 0;

	cpos = ocfs2_blocks_to_clusters(inode->i_sb, v_blkno);

	ret = ocfs2_get_clusters(inode, cpos, &p_cluster, &num_clusters,
				 extent_flags);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * p_cluster == 0 indicates a hole.
	 */
	अगर (p_cluster) अणु
		boff = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);
		boff += (v_blkno & (u64)(bpc - 1));
	पूर्ण

	*p_blkno = boff;

	अगर (ret_count) अणु
		*ret_count = ocfs2_clusters_to_blocks(inode->i_sb, num_clusters);
		*ret_count -= v_blkno & (u64)(bpc - 1);
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * The ocfs2_fiemap_अंतरभूत() may be a little bit misleading, since
 * it not only handles the fiemap क्रम अंतरभूतd files, but also deals
 * with the fast symlink, cause they have no dअगरference क्रम extent
 * mapping per se.
 */
अटल पूर्णांक ocfs2_fiemap_अंतरभूत(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			       काष्ठा fiemap_extent_info *fieinfo,
			       u64 map_start)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक id_count;
	काष्ठा ocfs2_dinode *di;
	u64 phys;
	u32 flags = FIEMAP_EXTENT_DATA_INLINE|FIEMAP_EXTENT_LAST;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	अगर (ocfs2_inode_is_fast_symlink(inode))
		id_count = ocfs2_fast_symlink_अक्षरs(inode->i_sb);
	अन्यथा
		id_count = le16_to_cpu(di->id2.i_data.id_count);

	अगर (map_start < id_count) अणु
		phys = oi->ip_blkno << inode->i_sb->s_blocksize_bits;
		अगर (ocfs2_inode_is_fast_symlink(inode))
			phys += दुरत्व(काष्ठा ocfs2_dinode, id2.i_symlink);
		अन्यथा
			phys += दुरत्व(काष्ठा ocfs2_dinode,
					 id2.i_data.id_data);

		ret = fiemap_fill_next_extent(fieinfo, 0, phys, id_count,
					      flags);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ocfs2_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		 u64 map_start, u64 map_len)
अणु
	पूर्णांक ret, is_last;
	u32 mapping_end, cpos;
	अचिन्हित पूर्णांक hole_size;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u64 len_bytes, phys_bytes, virt_bytes;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_extent_rec rec;

	ret = fiemap_prep(inode, fieinfo, map_start, &map_len, 0);
	अगर (ret)
		वापस ret;

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);

	/*
	 * Handle अंतरभूत-data and fast symlink separately.
	 */
	अगर ((OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) ||
	    ocfs2_inode_is_fast_symlink(inode)) अणु
		ret = ocfs2_fiemap_अंतरभूत(inode, di_bh, fieinfo, map_start);
		जाओ out_unlock;
	पूर्ण

	cpos = map_start >> osb->s_clustersize_bits;
	mapping_end = ocfs2_clusters_क्रम_bytes(inode->i_sb,
					       map_start + map_len);
	is_last = 0;
	जबतक (cpos < mapping_end && !is_last) अणु
		u32 fe_flags;

		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos,
						 &hole_size, &rec, &is_last);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण

		अगर (rec.e_blkno == 0ULL) अणु
			cpos += hole_size;
			जारी;
		पूर्ण

		fe_flags = 0;
		अगर (rec.e_flags & OCFS2_EXT_UNWRITTEN)
			fe_flags |= FIEMAP_EXTENT_UNWRITTEN;
		अगर (rec.e_flags & OCFS2_EXT_REFCOUNTED)
			fe_flags |= FIEMAP_EXTENT_SHARED;
		अगर (is_last)
			fe_flags |= FIEMAP_EXTENT_LAST;
		len_bytes = (u64)le16_to_cpu(rec.e_leaf_clusters) << osb->s_clustersize_bits;
		phys_bytes = le64_to_cpu(rec.e_blkno) << osb->sb->s_blocksize_bits;
		virt_bytes = (u64)le32_to_cpu(rec.e_cpos) << osb->s_clustersize_bits;

		ret = fiemap_fill_next_extent(fieinfo, virt_bytes, phys_bytes,
					      len_bytes, fe_flags);
		अगर (ret)
			अवरोध;

		cpos = le32_to_cpu(rec.e_cpos)+ le16_to_cpu(rec.e_leaf_clusters);
	पूर्ण

	अगर (ret > 0)
		ret = 0;

out_unlock:
	brअन्यथा(di_bh);

	up_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);

	ocfs2_inode_unlock(inode, 0);
out:

	वापस ret;
पूर्ण

/* Is IO overwriting allocated blocks? */
पूर्णांक ocfs2_overग_लिखो_io(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		       u64 map_start, u64 map_len)
अणु
	पूर्णांक ret = 0, is_last;
	u32 mapping_end, cpos;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_extent_rec rec;

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		अगर (ocfs2_size_fits_अंतरभूत_data(di_bh, map_start + map_len))
			वापस ret;
		अन्यथा
			वापस -EAGAIN;
	पूर्ण

	cpos = map_start >> osb->s_clustersize_bits;
	mapping_end = ocfs2_clusters_क्रम_bytes(inode->i_sb,
					       map_start + map_len);
	is_last = 0;
	जबतक (cpos < mapping_end && !is_last) अणु
		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos,
						 शून्य, &rec, &is_last);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (rec.e_blkno == 0ULL)
			अवरोध;

		अगर (rec.e_flags & OCFS2_EXT_REFCOUNTED)
			अवरोध;

		cpos = le32_to_cpu(rec.e_cpos) +
			le16_to_cpu(rec.e_leaf_clusters);
	पूर्ण

	अगर (cpos < mapping_end)
		ret = -EAGAIN;
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_seek_data_hole_offset(काष्ठा file *file, loff_t *offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक ret;
	अचिन्हित पूर्णांक is_last = 0, is_data = 0;
	u16 cs_bits = OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	u32 cpos, cend, clen, hole_size;
	u64 extoff, extlen;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_extent_rec rec;

	BUG_ON(whence != SEEK_DATA && whence != SEEK_HOLE);

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);

	अगर (*offset >= i_size_पढ़ो(inode)) अणु
		ret = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		अगर (whence == SEEK_HOLE)
			*offset = i_size_पढ़ो(inode);
		जाओ out_unlock;
	पूर्ण

	clen = 0;
	cpos = *offset >> cs_bits;
	cend = ocfs2_clusters_क्रम_bytes(inode->i_sb, i_size_पढ़ो(inode));

	जबतक (cpos < cend && !is_last) अणु
		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos, &hole_size,
						 &rec, &is_last);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण

		extoff = cpos;
		extoff <<= cs_bits;

		अगर (rec.e_blkno == 0ULL) अणु
			clen = hole_size;
			is_data = 0;
		पूर्ण अन्यथा अणु
			clen = le16_to_cpu(rec.e_leaf_clusters) -
				(cpos - le32_to_cpu(rec.e_cpos));
			is_data = (rec.e_flags & OCFS2_EXT_UNWRITTEN) ?  0 : 1;
		पूर्ण

		अगर ((!is_data && whence == SEEK_HOLE) ||
		    (is_data && whence == SEEK_DATA)) अणु
			अगर (extoff > *offset)
				*offset = extoff;
			जाओ out_unlock;
		पूर्ण

		अगर (!is_last)
			cpos += clen;
	पूर्ण

	अगर (whence == SEEK_HOLE) अणु
		extoff = cpos;
		extoff <<= cs_bits;
		extlen = clen;
		extlen <<=  cs_bits;

		अगर ((extoff + extlen) > i_size_पढ़ो(inode))
			extlen = i_size_पढ़ो(inode) - extoff;
		extoff += extlen;
		अगर (extoff > *offset)
			*offset = extoff;
		जाओ out_unlock;
	पूर्ण

	ret = -ENXIO;

out_unlock:

	brअन्यथा(di_bh);

	up_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);

	ocfs2_inode_unlock(inode, 0);
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_पढ़ो_virt_blocks(काष्ठा inode *inode, u64 v_block, पूर्णांक nr,
			   काष्ठा buffer_head *bhs[], पूर्णांक flags,
			   पूर्णांक (*validate)(काष्ठा super_block *sb,
					   काष्ठा buffer_head *bh))
अणु
	पूर्णांक rc = 0;
	u64 p_block, p_count;
	पूर्णांक i, count, करोne = 0;

	trace_ocfs2_पढ़ो_virt_blocks(
	     inode, (अचिन्हित दीर्घ दीर्घ)v_block, nr, bhs, flags,
	     validate);

	अगर (((v_block + nr - 1) << inode->i_sb->s_blocksize_bits) >=
	    i_size_पढ़ो(inode)) अणु
		BUG_ON(!(flags & OCFS2_BH_READAHEAD));
		जाओ out;
	पूर्ण

	जबतक (करोne < nr) अणु
		करोwn_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);
		rc = ocfs2_extent_map_get_blocks(inode, v_block + करोne,
						 &p_block, &p_count, शून्य);
		up_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			अवरोध;
		पूर्ण

		अगर (!p_block) अणु
			rc = -EIO;
			mlog(ML_ERROR,
			     "Inode #%llu contains a hole at offset %llu\n",
			     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			     (अचिन्हित दीर्घ दीर्घ)(v_block + करोne) <<
			     inode->i_sb->s_blocksize_bits);
			अवरोध;
		पूर्ण

		count = nr - करोne;
		अगर (p_count < count)
			count = p_count;

		/*
		 * If the caller passed us bhs, they should have come
		 * from a previous पढ़ोahead call to this function.  Thus,
		 * they should have the right b_blocknr.
		 */
		क्रम (i = 0; i < count; i++) अणु
			अगर (!bhs[करोne + i])
				जारी;
			BUG_ON(bhs[करोne + i]->b_blocknr != (p_block + i));
		पूर्ण

		rc = ocfs2_पढ़ो_blocks(INODE_CACHE(inode), p_block, count,
				       bhs + करोne, flags, validate);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			अवरोध;
		पूर्ण
		करोne += count;
	पूर्ण

out:
	वापस rc;
पूर्ण


