<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * suballoc.c
 *
 * metadata alloc and मुक्त
 * Inspired by ext3 block groups.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "blockcheck.h"
#समावेश "dlmglue.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "localalloc.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

#घोषणा NOT_ALLOC_NEW_GROUP		0
#घोषणा ALLOC_NEW_GROUP			0x1
#घोषणा ALLOC_GROUPS_FROM_GLOBAL	0x2

#घोषणा OCFS2_MAX_TO_STEAL		1024

काष्ठा ocfs2_suballoc_result अणु
	u64		sr_bg_blkno;	/* The bg we allocated from.  Set
					   to 0 when a block group is
					   contiguous. */
	u64		sr_bg_stable_blkno; /*
					     * Doesn't change, always
					     * set to target block
					     * group descriptor
					     * block.
					     */
	u64		sr_blkno;	/* The first allocated block */
	अचिन्हित पूर्णांक	sr_bit_offset;	/* The bit in the bg */
	अचिन्हित पूर्णांक	sr_bits;	/* How many bits we claimed */
पूर्ण;

अटल u64 ocfs2_group_from_res(काष्ठा ocfs2_suballoc_result *res)
अणु
	अगर (res->sr_blkno == 0)
		वापस 0;

	अगर (res->sr_bg_blkno)
		वापस res->sr_bg_blkno;

	वापस ocfs2_which_suballoc_group(res->sr_blkno, res->sr_bit_offset);
पूर्ण

अटल अंतरभूत u16 ocfs2_find_victim_chain(काष्ठा ocfs2_chain_list *cl);
अटल पूर्णांक ocfs2_block_group_fill(handle_t *handle,
				  काष्ठा inode *alloc_inode,
				  काष्ठा buffer_head *bg_bh,
				  u64 group_blkno,
				  अचिन्हित पूर्णांक group_clusters,
				  u16 my_chain,
				  काष्ठा ocfs2_chain_list *cl);
अटल पूर्णांक ocfs2_block_group_alloc(काष्ठा ocfs2_super *osb,
				   काष्ठा inode *alloc_inode,
				   काष्ठा buffer_head *bh,
				   u64 max_block,
				   u64 *last_alloc_group,
				   पूर्णांक flags);

अटल पूर्णांक ocfs2_cluster_group_search(काष्ठा inode *inode,
				      काष्ठा buffer_head *group_bh,
				      u32 bits_wanted, u32 min_bits,
				      u64 max_block,
				      काष्ठा ocfs2_suballoc_result *res);
अटल पूर्णांक ocfs2_block_group_search(काष्ठा inode *inode,
				    काष्ठा buffer_head *group_bh,
				    u32 bits_wanted, u32 min_bits,
				    u64 max_block,
				    काष्ठा ocfs2_suballoc_result *res);
अटल पूर्णांक ocfs2_claim_suballoc_bits(काष्ठा ocfs2_alloc_context *ac,
				     handle_t *handle,
				     u32 bits_wanted,
				     u32 min_bits,
				     काष्ठा ocfs2_suballoc_result *res);
अटल पूर्णांक ocfs2_test_bg_bit_allocatable(काष्ठा buffer_head *bg_bh,
					 पूर्णांक nr);
अटल पूर्णांक ocfs2_relink_block_group(handle_t *handle,
				    काष्ठा inode *alloc_inode,
				    काष्ठा buffer_head *fe_bh,
				    काष्ठा buffer_head *bg_bh,
				    काष्ठा buffer_head *prev_bg_bh,
				    u16 chain);
अटल अंतरभूत पूर्णांक ocfs2_block_group_reasonably_empty(काष्ठा ocfs2_group_desc *bg,
						     u32 wanted);
अटल अंतरभूत u32 ocfs2_desc_biपंचांगap_to_cluster_off(काष्ठा inode *inode,
						   u64 bg_blkno,
						   u16 bg_bit_off);
अटल अंतरभूत व्योम ocfs2_block_to_cluster_group(काष्ठा inode *inode,
						u64 data_blkno,
						u64 *bg_blkno,
						u16 *bg_bit_off);
अटल पूर्णांक ocfs2_reserve_clusters_with_limit(काष्ठा ocfs2_super *osb,
					     u32 bits_wanted, u64 max_block,
					     पूर्णांक flags,
					     काष्ठा ocfs2_alloc_context **ac);

व्योम ocfs2_मुक्त_ac_resource(काष्ठा ocfs2_alloc_context *ac)
अणु
	काष्ठा inode *inode = ac->ac_inode;

	अगर (inode) अणु
		अगर (ac->ac_which != OCFS2_AC_USE_LOCAL)
			ocfs2_inode_unlock(inode, 1);

		inode_unlock(inode);

		iput(inode);
		ac->ac_inode = शून्य;
	पूर्ण
	brअन्यथा(ac->ac_bh);
	ac->ac_bh = शून्य;
	ac->ac_resv = शून्य;
	kमुक्त(ac->ac_find_loc_priv);
	ac->ac_find_loc_priv = शून्य;
पूर्ण

व्योम ocfs2_मुक्त_alloc_context(काष्ठा ocfs2_alloc_context *ac)
अणु
	ocfs2_मुक्त_ac_resource(ac);
	kमुक्त(ac);
पूर्ण

अटल u32 ocfs2_bits_per_group(काष्ठा ocfs2_chain_list *cl)
अणु
	वापस (u32)le16_to_cpu(cl->cl_cpg) * (u32)le16_to_cpu(cl->cl_bpc);
पूर्ण

#घोषणा करो_error(fmt, ...)						\
करो अणु									\
	अगर (resize)							\
		mlog(ML_ERROR, fmt, ##__VA_ARGS__);			\
	अन्यथा								\
		वापस ocfs2_error(sb, fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

अटल पूर्णांक ocfs2_validate_gd_self(काष्ठा super_block *sb,
				  काष्ठा buffer_head *bh,
				  पूर्णांक resize)
अणु
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *)bh->b_data;

	अगर (!OCFS2_IS_VALID_GROUP_DESC(gd)) अणु
		करो_error("Group descriptor #%llu has bad signature %.*s\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
			 gd->bg_signature);
	पूर्ण

	अगर (le64_to_cpu(gd->bg_blkno) != bh->b_blocknr) अणु
		करो_error("Group descriptor #%llu has an invalid bg_blkno of %llu\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno));
	पूर्ण

	अगर (le32_to_cpu(gd->bg_generation) != OCFS2_SB(sb)->fs_generation) अणु
		करो_error("Group descriptor #%llu has an invalid fs_generation of #%u\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 le32_to_cpu(gd->bg_generation));
	पूर्ण

	अगर (le16_to_cpu(gd->bg_मुक्त_bits_count) > le16_to_cpu(gd->bg_bits)) अणु
		करो_error("Group descriptor #%llu has bit count %u but claims that %u are free\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 le16_to_cpu(gd->bg_bits),
			 le16_to_cpu(gd->bg_मुक्त_bits_count));
	पूर्ण

	अगर (le16_to_cpu(gd->bg_bits) > (8 * le16_to_cpu(gd->bg_size))) अणु
		करो_error("Group descriptor #%llu has bit count %u but max bitmap bits of %u\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 le16_to_cpu(gd->bg_bits),
			 8 * le16_to_cpu(gd->bg_size));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_validate_gd_parent(काष्ठा super_block *sb,
				    काष्ठा ocfs2_dinode *di,
				    काष्ठा buffer_head *bh,
				    पूर्णांक resize)
अणु
	अचिन्हित पूर्णांक max_bits;
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *)bh->b_data;

	अगर (di->i_blkno != gd->bg_parent_dinode) अणु
		करो_error("Group descriptor #%llu has bad parent pointer (%llu, expected %llu)\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_parent_dinode),
			 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno));
	पूर्ण

	max_bits = le16_to_cpu(di->id2.i_chain.cl_cpg) * le16_to_cpu(di->id2.i_chain.cl_bpc);
	अगर (le16_to_cpu(gd->bg_bits) > max_bits) अणु
		करो_error("Group descriptor #%llu has bit count of %u\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 le16_to_cpu(gd->bg_bits));
	पूर्ण

	/* In resize, we may meet the हाल bg_chain == cl_next_मुक्त_rec. */
	अगर ((le16_to_cpu(gd->bg_chain) >
	     le16_to_cpu(di->id2.i_chain.cl_next_मुक्त_rec)) ||
	    ((le16_to_cpu(gd->bg_chain) ==
	     le16_to_cpu(di->id2.i_chain.cl_next_मुक्त_rec)) && !resize)) अणु
		करो_error("Group descriptor #%llu has bad chain %u\n",
			 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			 le16_to_cpu(gd->bg_chain));
	पूर्ण

	वापस 0;
पूर्ण

#अघोषित करो_error

/*
 * This version only prपूर्णांकs errors.  It करोes not fail the fileप्रणाली, and
 * exists only क्रम resize.
 */
पूर्णांक ocfs2_check_group_descriptor(काष्ठा super_block *sb,
				 काष्ठा ocfs2_dinode *di,
				 काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *)bh->b_data;

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &gd->bg_check);
	अगर (rc) अणु
		mlog(ML_ERROR,
		     "Checksum failed for group descriptor %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
	पूर्ण अन्यथा
		rc = ocfs2_validate_gd_self(sb, bh, 1);
	अगर (!rc)
		rc = ocfs2_validate_gd_parent(sb, di, bh, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_validate_group_descriptor(काष्ठा super_block *sb,
					   काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *)bh->b_data;

	trace_ocfs2_validate_group_descriptor(
					(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &gd->bg_check);
	अगर (rc)
		वापस rc;

	/*
	 * Errors after here are fatal.
	 */

	वापस ocfs2_validate_gd_self(sb, bh, 0);
पूर्ण

पूर्णांक ocfs2_पढ़ो_group_descriptor(काष्ठा inode *inode, काष्ठा ocfs2_dinode *di,
				u64 gd_blkno, काष्ठा buffer_head **bh)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_block(INODE_CACHE(inode), gd_blkno, &पंचांगp,
			      ocfs2_validate_group_descriptor);
	अगर (rc)
		जाओ out;

	rc = ocfs2_validate_gd_parent(inode->i_sb, di, पंचांगp, 0);
	अगर (rc) अणु
		brअन्यथा(पंचांगp);
		जाओ out;
	पूर्ण

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!*bh)
		*bh = पंचांगp;

out:
	वापस rc;
पूर्ण

अटल व्योम ocfs2_bg_discontig_add_extent(काष्ठा ocfs2_super *osb,
					  काष्ठा ocfs2_group_desc *bg,
					  काष्ठा ocfs2_chain_list *cl,
					  u64 p_blkno, अचिन्हित पूर्णांक clusters)
अणु
	काष्ठा ocfs2_extent_list *el = &bg->bg_list;
	काष्ठा ocfs2_extent_rec *rec;

	BUG_ON(!ocfs2_supports_discontig_bg(osb));
	अगर (!el->l_next_मुक्त_rec)
		el->l_count = cpu_to_le16(ocfs2_extent_recs_per_gd(osb->sb));
	rec = &el->l_recs[le16_to_cpu(el->l_next_मुक्त_rec)];
	rec->e_blkno = cpu_to_le64(p_blkno);
	rec->e_cpos = cpu_to_le32(le16_to_cpu(bg->bg_bits) /
				  le16_to_cpu(cl->cl_bpc));
	rec->e_leaf_clusters = cpu_to_le16(clusters);
	le16_add_cpu(&bg->bg_bits, clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&bg->bg_मुक्त_bits_count,
		     clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&el->l_next_मुक्त_rec, 1);
पूर्ण

अटल पूर्णांक ocfs2_block_group_fill(handle_t *handle,
				  काष्ठा inode *alloc_inode,
				  काष्ठा buffer_head *bg_bh,
				  u64 group_blkno,
				  अचिन्हित पूर्णांक group_clusters,
				  u16 my_chain,
				  काष्ठा ocfs2_chain_list *cl)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);
	काष्ठा ocfs2_group_desc *bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;
	काष्ठा super_block * sb = alloc_inode->i_sb;

	अगर (((अचिन्हित दीर्घ दीर्घ) bg_bh->b_blocknr) != group_blkno) अणु
		status = ocfs2_error(alloc_inode->i_sb,
				     "group block (%llu) != b_blocknr (%llu)\n",
				     (अचिन्हित दीर्घ दीर्घ)group_blkno,
				     (अचिन्हित दीर्घ दीर्घ) bg_bh->b_blocknr);
		जाओ bail;
	पूर्ण

	status = ocfs2_journal_access_gd(handle,
					 INODE_CACHE(alloc_inode),
					 bg_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	स_रखो(bg, 0, sb->s_blocksize);
	म_नकल(bg->bg_signature, OCFS2_GROUP_DESC_SIGNATURE);
	bg->bg_generation = cpu_to_le32(osb->fs_generation);
	bg->bg_size = cpu_to_le16(ocfs2_group_biपंचांगap_size(sb, 1,
						osb->s_feature_incompat));
	bg->bg_chain = cpu_to_le16(my_chain);
	bg->bg_next_group = cl->cl_recs[my_chain].c_blkno;
	bg->bg_parent_dinode = cpu_to_le64(OCFS2_I(alloc_inode)->ip_blkno);
	bg->bg_blkno = cpu_to_le64(group_blkno);
	अगर (group_clusters == le16_to_cpu(cl->cl_cpg))
		bg->bg_bits = cpu_to_le16(ocfs2_bits_per_group(cl));
	अन्यथा
		ocfs2_bg_discontig_add_extent(osb, bg, cl, group_blkno,
					      group_clusters);

	/* set the 1st bit in the biपंचांगap to account क्रम the descriptor block */
	ocfs2_set_bit(0, (अचिन्हित दीर्घ *)bg->bg_biपंचांगap);
	bg->bg_मुक्त_bits_count = cpu_to_le16(le16_to_cpu(bg->bg_bits) - 1);

	ocfs2_journal_dirty(handle, bg_bh);

	/* There is no need to zero out or otherwise initialize the
	 * other blocks in a group - All valid FS metadata in a block
	 * group stores the superblock fs_generation value at
	 * allocation समय. */

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल अंतरभूत u16 ocfs2_find_smallest_chain(काष्ठा ocfs2_chain_list *cl)
अणु
	u16 curr, best;

	best = curr = 0;
	जबतक (curr < le16_to_cpu(cl->cl_count)) अणु
		अगर (le32_to_cpu(cl->cl_recs[best].c_total) >
		    le32_to_cpu(cl->cl_recs[curr].c_total))
			best = curr;
		curr++;
	पूर्ण
	वापस best;
पूर्ण

अटल काष्ठा buffer_head *
ocfs2_block_group_alloc_contig(काष्ठा ocfs2_super *osb, handle_t *handle,
			       काष्ठा inode *alloc_inode,
			       काष्ठा ocfs2_alloc_context *ac,
			       काष्ठा ocfs2_chain_list *cl)
अणु
	पूर्णांक status;
	u32 bit_off, num_bits;
	u64 bg_blkno;
	काष्ठा buffer_head *bg_bh;
	अचिन्हित पूर्णांक alloc_rec = ocfs2_find_smallest_chain(cl);

	status = ocfs2_claim_clusters(handle, ac,
				      le16_to_cpu(cl->cl_cpg), &bit_off,
				      &num_bits);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* setup the group */
	bg_blkno = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_block_group_alloc_contig(
	     (अचिन्हित दीर्घ दीर्घ)bg_blkno, alloc_rec);

	bg_bh = sb_getblk(osb->sb, bg_blkno);
	अगर (!bg_bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(alloc_inode), bg_bh);

	status = ocfs2_block_group_fill(handle, alloc_inode, bg_bh,
					bg_blkno, num_bits, alloc_rec, cl);
	अगर (status < 0) अणु
		brअन्यथा(bg_bh);
		mlog_त्रुटि_सं(status);
	पूर्ण

bail:
	वापस status ? ERR_PTR(status) : bg_bh;
पूर्ण

अटल पूर्णांक ocfs2_block_group_claim_bits(काष्ठा ocfs2_super *osb,
					handle_t *handle,
					काष्ठा ocfs2_alloc_context *ac,
					अचिन्हित पूर्णांक min_bits,
					u32 *bit_off, u32 *num_bits)
अणु
	पूर्णांक status = 0;

	जबतक (min_bits) अणु
		status = ocfs2_claim_clusters(handle, ac, min_bits,
					      bit_off, num_bits);
		अगर (status != -ENOSPC)
			अवरोध;

		min_bits >>= 1;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_block_group_grow_discontig(handle_t *handle,
					    काष्ठा inode *alloc_inode,
					    काष्ठा buffer_head *bg_bh,
					    काष्ठा ocfs2_alloc_context *ac,
					    काष्ठा ocfs2_chain_list *cl,
					    अचिन्हित पूर्णांक min_bits)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);
	काष्ठा ocfs2_group_desc *bg =
		(काष्ठा ocfs2_group_desc *)bg_bh->b_data;
	अचिन्हित पूर्णांक needed = le16_to_cpu(cl->cl_cpg) -
			 le16_to_cpu(bg->bg_bits) / le16_to_cpu(cl->cl_bpc);
	u32 p_cpos, clusters;
	u64 p_blkno;
	काष्ठा ocfs2_extent_list *el = &bg->bg_list;

	status = ocfs2_journal_access_gd(handle,
					 INODE_CACHE(alloc_inode),
					 bg_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	जबतक ((needed > 0) && (le16_to_cpu(el->l_next_मुक्त_rec) <
				le16_to_cpu(el->l_count))) अणु
		अगर (min_bits > needed)
			min_bits = needed;
		status = ocfs2_block_group_claim_bits(osb, handle, ac,
						      min_bits, &p_cpos,
						      &clusters);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		p_blkno = ocfs2_clusters_to_blocks(osb->sb, p_cpos);
		ocfs2_bg_discontig_add_extent(osb, bg, cl, p_blkno,
					      clusters);

		min_bits = clusters;
		needed = le16_to_cpu(cl->cl_cpg) -
			 le16_to_cpu(bg->bg_bits) / le16_to_cpu(cl->cl_bpc);
	पूर्ण

	अगर (needed > 0) अणु
		/*
		 * We have used up all the extent rec but can't fill up
		 * the cpg. So bail out.
		 */
		status = -ENOSPC;
		जाओ bail;
	पूर्ण

	ocfs2_journal_dirty(handle, bg_bh);

bail:
	वापस status;
पूर्ण

अटल व्योम ocfs2_bg_alloc_cleanup(handle_t *handle,
				   काष्ठा ocfs2_alloc_context *cluster_ac,
				   काष्ठा inode *alloc_inode,
				   काष्ठा buffer_head *bg_bh)
अणु
	पूर्णांक i, ret;
	काष्ठा ocfs2_group_desc *bg;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec;

	अगर (!bg_bh)
		वापस;

	bg = (काष्ठा ocfs2_group_desc *)bg_bh->b_data;
	el = &bg->bg_list;
	क्रम (i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++) अणु
		rec = &el->l_recs[i];
		ret = ocfs2_मुक्त_clusters(handle, cluster_ac->ac_inode,
					  cluster_ac->ac_bh,
					  le64_to_cpu(rec->e_blkno),
					  le16_to_cpu(rec->e_leaf_clusters));
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		/* Try all the clusters to मुक्त */
	पूर्ण

	ocfs2_हटाओ_from_cache(INODE_CACHE(alloc_inode), bg_bh);
	brअन्यथा(bg_bh);
पूर्ण

अटल काष्ठा buffer_head *
ocfs2_block_group_alloc_discontig(handle_t *handle,
				  काष्ठा inode *alloc_inode,
				  काष्ठा ocfs2_alloc_context *ac,
				  काष्ठा ocfs2_chain_list *cl)
अणु
	पूर्णांक status;
	u32 bit_off, num_bits;
	u64 bg_blkno;
	अचिन्हित पूर्णांक min_bits = le16_to_cpu(cl->cl_cpg) >> 1;
	काष्ठा buffer_head *bg_bh = शून्य;
	अचिन्हित पूर्णांक alloc_rec = ocfs2_find_smallest_chain(cl);
	काष्ठा ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);

	अगर (!ocfs2_supports_discontig_bg(osb)) अणु
		status = -ENOSPC;
		जाओ bail;
	पूर्ण

	status = ocfs2_extend_trans(handle,
				    ocfs2_calc_bg_discontig_credits(osb->sb));
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/*
	 * We're going to be grabbing from multiple cluster groups.
	 * We करोn't have enough credits to relink them all, and the
	 * cluster groups will be staying in cache क्रम the duration of
	 * this operation.
	 */
	ac->ac_disable_chain_relink = 1;

	/* Claim the first region */
	status = ocfs2_block_group_claim_bits(osb, handle, ac, min_bits,
					      &bit_off, &num_bits);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	min_bits = num_bits;

	/* setup the group */
	bg_blkno = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_block_group_alloc_discontig(
				(अचिन्हित दीर्घ दीर्घ)bg_blkno, alloc_rec);

	bg_bh = sb_getblk(osb->sb, bg_blkno);
	अगर (!bg_bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(alloc_inode), bg_bh);

	status = ocfs2_block_group_fill(handle, alloc_inode, bg_bh,
					bg_blkno, num_bits, alloc_rec, cl);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_block_group_grow_discontig(handle, alloc_inode,
						  bg_bh, ac, cl, min_bits);
	अगर (status)
		mlog_त्रुटि_सं(status);

bail:
	अगर (status)
		ocfs2_bg_alloc_cleanup(handle, ac, alloc_inode, bg_bh);
	वापस status ? ERR_PTR(status) : bg_bh;
पूर्ण

/*
 * We expect the block group allocator to alपढ़ोy be locked.
 */
अटल पूर्णांक ocfs2_block_group_alloc(काष्ठा ocfs2_super *osb,
				   काष्ठा inode *alloc_inode,
				   काष्ठा buffer_head *bh,
				   u64 max_block,
				   u64 *last_alloc_group,
				   पूर्णांक flags)
अणु
	पूर्णांक status, credits;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) bh->b_data;
	काष्ठा ocfs2_chain_list *cl;
	काष्ठा ocfs2_alloc_context *ac = शून्य;
	handle_t *handle = शून्य;
	u16 alloc_rec;
	काष्ठा buffer_head *bg_bh = शून्य;
	काष्ठा ocfs2_group_desc *bg;

	BUG_ON(ocfs2_is_cluster_biपंचांगap(alloc_inode));

	cl = &fe->id2.i_chain;
	status = ocfs2_reserve_clusters_with_limit(osb,
						   le16_to_cpu(cl->cl_cpg),
						   max_block, flags, &ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	credits = ocfs2_calc_group_alloc_credits(osb->sb,
						 le16_to_cpu(cl->cl_cpg));
	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (last_alloc_group && *last_alloc_group != 0) अणु
		trace_ocfs2_block_group_alloc(
				(अचिन्हित दीर्घ दीर्घ)*last_alloc_group);
		ac->ac_last_group = *last_alloc_group;
	पूर्ण

	bg_bh = ocfs2_block_group_alloc_contig(osb, handle, alloc_inode,
					       ac, cl);
	अगर (PTR_ERR(bg_bh) == -ENOSPC)
		bg_bh = ocfs2_block_group_alloc_discontig(handle,
							  alloc_inode,
							  ac, cl);
	अगर (IS_ERR(bg_bh)) अणु
		status = PTR_ERR(bg_bh);
		bg_bh = शून्य;
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	alloc_rec = le16_to_cpu(bg->bg_chain);
	le32_add_cpu(&cl->cl_recs[alloc_rec].c_मुक्त,
		     le16_to_cpu(bg->bg_मुक्त_bits_count));
	le32_add_cpu(&cl->cl_recs[alloc_rec].c_total,
		     le16_to_cpu(bg->bg_bits));
	cl->cl_recs[alloc_rec].c_blkno = bg->bg_blkno;
	अगर (le16_to_cpu(cl->cl_next_मुक्त_rec) < le16_to_cpu(cl->cl_count))
		le16_add_cpu(&cl->cl_next_मुक्त_rec, 1);

	le32_add_cpu(&fe->id1.biपंचांगap1.i_used, le16_to_cpu(bg->bg_bits) -
					le16_to_cpu(bg->bg_मुक्त_bits_count));
	le32_add_cpu(&fe->id1.biपंचांगap1.i_total, le16_to_cpu(bg->bg_bits));
	le32_add_cpu(&fe->i_clusters, le16_to_cpu(cl->cl_cpg));

	ocfs2_journal_dirty(handle, bh);

	spin_lock(&OCFS2_I(alloc_inode)->ip_lock);
	OCFS2_I(alloc_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	fe->i_size = cpu_to_le64(ocfs2_clusters_to_bytes(alloc_inode->i_sb,
					     le32_to_cpu(fe->i_clusters)));
	spin_unlock(&OCFS2_I(alloc_inode)->ip_lock);
	i_size_ग_लिखो(alloc_inode, le64_to_cpu(fe->i_size));
	alloc_inode->i_blocks = ocfs2_inode_sector_count(alloc_inode);
	ocfs2_update_inode_fsync_trans(handle, alloc_inode, 0);

	status = 0;

	/* save the new last alloc group so that the caller can cache it. */
	अगर (last_alloc_group)
		*last_alloc_group = ac->ac_last_group;

bail:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	अगर (ac)
		ocfs2_मुक्त_alloc_context(ac);

	brअन्यथा(bg_bh);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_reserve_suballoc_bits(काष्ठा ocfs2_super *osb,
				       काष्ठा ocfs2_alloc_context *ac,
				       पूर्णांक type,
				       u32 slot,
				       u64 *last_alloc_group,
				       पूर्णांक flags)
अणु
	पूर्णांक status;
	u32 bits_wanted = ac->ac_bits_wanted;
	काष्ठा inode *alloc_inode;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_dinode *fe;
	u32 मुक्त_bits;

	alloc_inode = ocfs2_get_प्रणाली_file_inode(osb, type, slot);
	अगर (!alloc_inode) अणु
		mlog_त्रुटि_सं(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	inode_lock(alloc_inode);

	status = ocfs2_inode_lock(alloc_inode, &bh, 1);
	अगर (status < 0) अणु
		inode_unlock(alloc_inode);
		iput(alloc_inode);

		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	ac->ac_inode = alloc_inode;
	ac->ac_alloc_slot = slot;

	fe = (काष्ठा ocfs2_dinode *) bh->b_data;

	/* The bh was validated by the inode पढ़ो inside
	 * ocfs2_inode_lock().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	अगर (!(fe->i_flags & cpu_to_le32(OCFS2_CHAIN_FL))) अणु
		status = ocfs2_error(alloc_inode->i_sb,
				     "Invalid chain allocator %llu\n",
				     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_blkno));
		जाओ bail;
	पूर्ण

	मुक्त_bits = le32_to_cpu(fe->id1.biपंचांगap1.i_total) -
		le32_to_cpu(fe->id1.biपंचांगap1.i_used);

	अगर (bits_wanted > मुक्त_bits) अणु
		/* cluster biपंचांगap never grows */
		अगर (ocfs2_is_cluster_biपंचांगap(alloc_inode)) अणु
			trace_ocfs2_reserve_suballoc_bits_nospc(bits_wanted,
								मुक्त_bits);
			status = -ENOSPC;
			जाओ bail;
		पूर्ण

		अगर (!(flags & ALLOC_NEW_GROUP)) अणु
			trace_ocfs2_reserve_suballoc_bits_no_new_group(
						slot, bits_wanted, मुक्त_bits);
			status = -ENOSPC;
			जाओ bail;
		पूर्ण

		status = ocfs2_block_group_alloc(osb, alloc_inode, bh,
						 ac->ac_max_block,
						 last_alloc_group, flags);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		atomic_inc(&osb->alloc_stats.bg_extends);

		/* You should never ask क्रम this much metadata */
		BUG_ON(bits_wanted >
		       (le32_to_cpu(fe->id1.biपंचांगap1.i_total)
			- le32_to_cpu(fe->id1.biपंचांगap1.i_used)));
	पूर्ण

	get_bh(bh);
	ac->ac_bh = bh;
bail:
	brअन्यथा(bh);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम ocfs2_init_inode_steal_slot(काष्ठा ocfs2_super *osb)
अणु
	spin_lock(&osb->osb_lock);
	osb->s_inode_steal_slot = OCFS2_INVALID_SLOT;
	spin_unlock(&osb->osb_lock);
	atomic_set(&osb->s_num_inodes_stolen, 0);
पूर्ण

अटल व्योम ocfs2_init_meta_steal_slot(काष्ठा ocfs2_super *osb)
अणु
	spin_lock(&osb->osb_lock);
	osb->s_meta_steal_slot = OCFS2_INVALID_SLOT;
	spin_unlock(&osb->osb_lock);
	atomic_set(&osb->s_num_meta_stolen, 0);
पूर्ण

व्योम ocfs2_init_steal_slots(काष्ठा ocfs2_super *osb)
अणु
	ocfs2_init_inode_steal_slot(osb);
	ocfs2_init_meta_steal_slot(osb);
पूर्ण

अटल व्योम __ocfs2_set_steal_slot(काष्ठा ocfs2_super *osb, पूर्णांक slot, पूर्णांक type)
अणु
	spin_lock(&osb->osb_lock);
	अगर (type == INODE_ALLOC_SYSTEM_INODE)
		osb->s_inode_steal_slot = (u16)slot;
	अन्यथा अगर (type == EXTENT_ALLOC_SYSTEM_INODE)
		osb->s_meta_steal_slot = (u16)slot;
	spin_unlock(&osb->osb_lock);
पूर्ण

अटल पूर्णांक __ocfs2_get_steal_slot(काष्ठा ocfs2_super *osb, पूर्णांक type)
अणु
	पूर्णांक slot = OCFS2_INVALID_SLOT;

	spin_lock(&osb->osb_lock);
	अगर (type == INODE_ALLOC_SYSTEM_INODE)
		slot = osb->s_inode_steal_slot;
	अन्यथा अगर (type == EXTENT_ALLOC_SYSTEM_INODE)
		slot = osb->s_meta_steal_slot;
	spin_unlock(&osb->osb_lock);

	वापस slot;
पूर्ण

अटल पूर्णांक ocfs2_get_inode_steal_slot(काष्ठा ocfs2_super *osb)
अणु
	वापस __ocfs2_get_steal_slot(osb, INODE_ALLOC_SYSTEM_INODE);
पूर्ण

अटल पूर्णांक ocfs2_get_meta_steal_slot(काष्ठा ocfs2_super *osb)
अणु
	वापस __ocfs2_get_steal_slot(osb, EXTENT_ALLOC_SYSTEM_INODE);
पूर्ण

अटल पूर्णांक ocfs2_steal_resource(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_alloc_context *ac,
				पूर्णांक type)
अणु
	पूर्णांक i, status = -ENOSPC;
	पूर्णांक slot = __ocfs2_get_steal_slot(osb, type);

	/* Start to steal resource from the first slot after ours. */
	अगर (slot == OCFS2_INVALID_SLOT)
		slot = osb->slot_num + 1;

	क्रम (i = 0; i < osb->max_slots; i++, slot++) अणु
		अगर (slot == osb->max_slots)
			slot = 0;

		अगर (slot == osb->slot_num)
			जारी;

		status = ocfs2_reserve_suballoc_bits(osb, ac,
						     type,
						     (u32)slot, शून्य,
						     NOT_ALLOC_NEW_GROUP);
		अगर (status >= 0) अणु
			__ocfs2_set_steal_slot(osb, slot, type);
			अवरोध;
		पूर्ण

		ocfs2_मुक्त_ac_resource(ac);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_steal_inode(काष्ठा ocfs2_super *osb,
			     काष्ठा ocfs2_alloc_context *ac)
अणु
	वापस ocfs2_steal_resource(osb, ac, INODE_ALLOC_SYSTEM_INODE);
पूर्ण

अटल पूर्णांक ocfs2_steal_meta(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_alloc_context *ac)
अणु
	वापस ocfs2_steal_resource(osb, ac, EXTENT_ALLOC_SYSTEM_INODE);
पूर्ण

पूर्णांक ocfs2_reserve_new_metadata_blocks(काष्ठा ocfs2_super *osb,
				      पूर्णांक blocks,
				      काष्ठा ocfs2_alloc_context **ac)
अणु
	पूर्णांक status;
	पूर्णांक slot = ocfs2_get_meta_steal_slot(osb);

	*ac = kzalloc(माप(काष्ठा ocfs2_alloc_context), GFP_KERNEL);
	अगर (!(*ac)) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	(*ac)->ac_bits_wanted = blocks;
	(*ac)->ac_which = OCFS2_AC_USE_META;
	(*ac)->ac_group_search = ocfs2_block_group_search;

	अगर (slot != OCFS2_INVALID_SLOT &&
		atomic_पढ़ो(&osb->s_num_meta_stolen) < OCFS2_MAX_TO_STEAL)
		जाओ extent_steal;

	atomic_set(&osb->s_num_meta_stolen, 0);
	status = ocfs2_reserve_suballoc_bits(osb, (*ac),
					     EXTENT_ALLOC_SYSTEM_INODE,
					     (u32)osb->slot_num, शून्य,
					     ALLOC_GROUPS_FROM_GLOBAL|ALLOC_NEW_GROUP);


	अगर (status >= 0) अणु
		status = 0;
		अगर (slot != OCFS2_INVALID_SLOT)
			ocfs2_init_meta_steal_slot(osb);
		जाओ bail;
	पूर्ण अन्यथा अगर (status < 0 && status != -ENOSPC) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_मुक्त_ac_resource(*ac);

extent_steal:
	status = ocfs2_steal_meta(osb, *ac);
	atomic_inc(&osb->s_num_meta_stolen);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = 0;
bail:
	अगर ((status < 0) && *ac) अणु
		ocfs2_मुक्त_alloc_context(*ac);
		*ac = शून्य;
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_reserve_new_metadata(काष्ठा ocfs2_super *osb,
			       काष्ठा ocfs2_extent_list *root_el,
			       काष्ठा ocfs2_alloc_context **ac)
अणु
	वापस ocfs2_reserve_new_metadata_blocks(osb,
					ocfs2_extend_meta_needed(root_el),
					ac);
पूर्ण

पूर्णांक ocfs2_reserve_new_inode(काष्ठा ocfs2_super *osb,
			    काष्ठा ocfs2_alloc_context **ac)
अणु
	पूर्णांक status;
	पूर्णांक slot = ocfs2_get_inode_steal_slot(osb);
	u64 alloc_group;

	*ac = kzalloc(माप(काष्ठा ocfs2_alloc_context), GFP_KERNEL);
	अगर (!(*ac)) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	(*ac)->ac_bits_wanted = 1;
	(*ac)->ac_which = OCFS2_AC_USE_INODE;

	(*ac)->ac_group_search = ocfs2_block_group_search;

	/*
	 * stat(2) can't handle i_ino > 32bits, so we tell the
	 * lower levels not to allocate us a block group past that
	 * limit.  The 'inode64' mount option aव्योमs this behavior.
	 */
	अगर (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64))
		(*ac)->ac_max_block = (u32)~0U;

	/*
	 * slot is set when we successfully steal inode from other nodes.
	 * It is reset in 3 places:
	 * 1. when we flush the truncate log
	 * 2. when we complete local alloc recovery.
	 * 3. when we successfully allocate from our own slot.
	 * After it is set, we will go on stealing inodes until we find the
	 * need to check our slots to see whether there is some space क्रम us.
	 */
	अगर (slot != OCFS2_INVALID_SLOT &&
	    atomic_पढ़ो(&osb->s_num_inodes_stolen) < OCFS2_MAX_TO_STEAL)
		जाओ inode_steal;

	atomic_set(&osb->s_num_inodes_stolen, 0);
	alloc_group = osb->osb_inode_alloc_group;
	status = ocfs2_reserve_suballoc_bits(osb, *ac,
					     INODE_ALLOC_SYSTEM_INODE,
					     (u32)osb->slot_num,
					     &alloc_group,
					     ALLOC_NEW_GROUP |
					     ALLOC_GROUPS_FROM_GLOBAL);
	अगर (status >= 0) अणु
		status = 0;

		spin_lock(&osb->osb_lock);
		osb->osb_inode_alloc_group = alloc_group;
		spin_unlock(&osb->osb_lock);
		trace_ocfs2_reserve_new_inode_new_group(
			(अचिन्हित दीर्घ दीर्घ)alloc_group);

		/*
		 * Some inodes must be मुक्तd by us, so try to allocate
		 * from our own next समय.
		 */
		अगर (slot != OCFS2_INVALID_SLOT)
			ocfs2_init_inode_steal_slot(osb);
		जाओ bail;
	पूर्ण अन्यथा अगर (status < 0 && status != -ENOSPC) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_मुक्त_ac_resource(*ac);

inode_steal:
	status = ocfs2_steal_inode(osb, *ac);
	atomic_inc(&osb->s_num_inodes_stolen);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = 0;
bail:
	अगर ((status < 0) && *ac) अणु
		ocfs2_मुक्त_alloc_context(*ac);
		*ac = शून्य;
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* local alloc code has to करो the same thing, so rather than करो this
 * twice.. */
पूर्णांक ocfs2_reserve_cluster_biपंचांगap_bits(काष्ठा ocfs2_super *osb,
				      काष्ठा ocfs2_alloc_context *ac)
अणु
	पूर्णांक status;

	ac->ac_which = OCFS2_AC_USE_MAIN;
	ac->ac_group_search = ocfs2_cluster_group_search;

	status = ocfs2_reserve_suballoc_bits(osb, ac,
					     GLOBAL_BITMAP_SYSTEM_INODE,
					     OCFS2_INVALID_SLOT, शून्य,
					     ALLOC_NEW_GROUP);
	अगर (status < 0 && status != -ENOSPC)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

/* Callers करोn't need to care which biपंचांगap (local alloc or मुख्य) to
 * use so we figure it out क्रम them, but unक्रमtunately this clutters
 * things a bit. */
अटल पूर्णांक ocfs2_reserve_clusters_with_limit(काष्ठा ocfs2_super *osb,
					     u32 bits_wanted, u64 max_block,
					     पूर्णांक flags,
					     काष्ठा ocfs2_alloc_context **ac)
अणु
	पूर्णांक status, ret = 0;
	पूर्णांक retried = 0;

	*ac = kzalloc(माप(काष्ठा ocfs2_alloc_context), GFP_KERNEL);
	अगर (!(*ac)) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	(*ac)->ac_bits_wanted = bits_wanted;
	(*ac)->ac_max_block = max_block;

	status = -ENOSPC;
	अगर (!(flags & ALLOC_GROUPS_FROM_GLOBAL) &&
	    ocfs2_alloc_should_use_local(osb, bits_wanted)) अणु
		status = ocfs2_reserve_local_alloc_bits(osb,
							bits_wanted,
							*ac);
		अगर ((status < 0) && (status != -ENOSPC)) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	अगर (status == -ENOSPC) अणु
retry:
		status = ocfs2_reserve_cluster_biपंचांगap_bits(osb, *ac);
		/* Retry अगर there is sufficient space cached in truncate log */
		अगर (status == -ENOSPC && !retried) अणु
			retried = 1;
			ocfs2_inode_unlock((*ac)->ac_inode, 1);
			inode_unlock((*ac)->ac_inode);

			ret = ocfs2_try_to_मुक्त_truncate_log(osb, bits_wanted);
			अगर (ret == 1) अणु
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = शून्य;
				जाओ retry;
			पूर्ण

			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);

			inode_lock((*ac)->ac_inode);
			ret = ocfs2_inode_lock((*ac)->ac_inode, शून्य, 1);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				inode_unlock((*ac)->ac_inode);
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = शून्य;
				जाओ bail;
			पूर्ण
		पूर्ण
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	status = 0;
bail:
	अगर ((status < 0) && *ac) अणु
		ocfs2_मुक्त_alloc_context(*ac);
		*ac = शून्य;
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_reserve_clusters(काष्ठा ocfs2_super *osb,
			   u32 bits_wanted,
			   काष्ठा ocfs2_alloc_context **ac)
अणु
	वापस ocfs2_reserve_clusters_with_limit(osb, bits_wanted, 0,
						 ALLOC_NEW_GROUP, ac);
पूर्ण

/*
 * More or less lअगरted from ext3. I'll leave their description below:
 *
 * "For ext3 allocations, we must not reuse any blocks which are
 * allocated in the biपंचांगap buffer's "last committed data" copy.  This
 * prevents deletes from मुक्तing up the page क्रम reuse until we have
 * committed the delete transaction.
 *
 * If we didn't करो this, then deleting something and पुनः_स्मृतिating it as
 * data would allow the old block to be overwritten beक्रमe the
 * transaction committed (because we क्रमce data to disk beक्रमe commit).
 * This would lead to corruption अगर we crashed between overwriting the
 * data and committing the delete.
 *
 * @@@ We may want to make this allocation behaviour conditional on
 * data-ग_लिखोs at some poपूर्णांक, and disable it क्रम metadata allocations or
 * sync-data inodes."
 *
 * Note: OCFS2 alपढ़ोy करोes this dअगरferently क्रम metadata vs data
 * allocations, as those biपंचांगaps are separate and unकरो access is never
 * called on a metadata group descriptor.
 */
अटल पूर्णांक ocfs2_test_bg_bit_allocatable(काष्ठा buffer_head *bg_bh,
					 पूर्णांक nr)
अणु
	काष्ठा ocfs2_group_desc *bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;
	काष्ठा journal_head *jh;
	पूर्णांक ret;

	अगर (ocfs2_test_bit(nr, (अचिन्हित दीर्घ *)bg->bg_biपंचांगap))
		वापस 0;

	अगर (!buffer_jbd(bg_bh))
		वापस 1;

	jh = bh2jh(bg_bh);
	spin_lock(&jh->b_state_lock);
	bg = (काष्ठा ocfs2_group_desc *) jh->b_committed_data;
	अगर (bg)
		ret = !ocfs2_test_bit(nr, (अचिन्हित दीर्घ *)bg->bg_biपंचांगap);
	अन्यथा
		ret = 1;
	spin_unlock(&jh->b_state_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_block_group_find_clear_bits(काष्ठा ocfs2_super *osb,
					     काष्ठा buffer_head *bg_bh,
					     अचिन्हित पूर्णांक bits_wanted,
					     अचिन्हित पूर्णांक total_bits,
					     काष्ठा ocfs2_suballoc_result *res)
अणु
	व्योम *biपंचांगap;
	u16 best_offset, best_size;
	पूर्णांक offset, start, found, status = 0;
	काष्ठा ocfs2_group_desc *bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;

	/* Callers got this descriptor from
	 * ocfs2_पढ़ो_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));

	found = start = best_offset = best_size = 0;
	biपंचांगap = bg->bg_biपंचांगap;

	जबतक((offset = ocfs2_find_next_zero_bit(biपंचांगap, total_bits, start)) != -1) अणु
		अगर (offset == total_bits)
			अवरोध;

		अगर (!ocfs2_test_bg_bit_allocatable(bg_bh, offset)) अणु
			/* We found a zero, but we can't use it as it
			 * hasn't been put to disk yet! */
			found = 0;
			start = offset + 1;
		पूर्ण अन्यथा अगर (offset == start) अणु
			/* we found a zero */
			found++;
			/* move start to the next bit to test */
			start++;
		पूर्ण अन्यथा अणु
			/* got a zero after some ones */
			found = 1;
			start = offset + 1;
		पूर्ण
		अगर (found > best_size) अणु
			best_size = found;
			best_offset = start - found;
		पूर्ण
		/* we got everything we needed */
		अगर (found == bits_wanted) अणु
			/* mlog(0, "Found it all!\n"); */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (best_size) अणु
		res->sr_bit_offset = best_offset;
		res->sr_bits = best_size;
	पूर्ण अन्यथा अणु
		status = -ENOSPC;
		/* No error log here -- see the comment above
		 * ocfs2_test_bg_bit_allocatable */
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ocfs2_block_group_set_bits(handle_t *handle,
					     काष्ठा inode *alloc_inode,
					     काष्ठा ocfs2_group_desc *bg,
					     काष्ठा buffer_head *group_bh,
					     अचिन्हित पूर्णांक bit_off,
					     अचिन्हित पूर्णांक num_bits)
अणु
	पूर्णांक status;
	व्योम *biपंचांगap = bg->bg_biपंचांगap;
	पूर्णांक journal_type = OCFS2_JOURNAL_ACCESS_WRITE;

	/* All callers get the descriptor via
	 * ocfs2_पढ़ो_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));
	BUG_ON(le16_to_cpu(bg->bg_मुक्त_bits_count) < num_bits);

	trace_ocfs2_block_group_set_bits(bit_off, num_bits);

	अगर (ocfs2_is_cluster_biपंचांगap(alloc_inode))
		journal_type = OCFS2_JOURNAL_ACCESS_UNDO;

	status = ocfs2_journal_access_gd(handle,
					 INODE_CACHE(alloc_inode),
					 group_bh,
					 journal_type);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	le16_add_cpu(&bg->bg_मुक्त_bits_count, -num_bits);
	अगर (le16_to_cpu(bg->bg_मुक्त_bits_count) > le16_to_cpu(bg->bg_bits)) अणु
		वापस ocfs2_error(alloc_inode->i_sb, "Group descriptor # %llu has bit count %u but claims %u are freed. num_bits %d\n",
				   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(bg->bg_blkno),
				   le16_to_cpu(bg->bg_bits),
				   le16_to_cpu(bg->bg_मुक्त_bits_count),
				   num_bits);
	पूर्ण
	जबतक(num_bits--)
		ocfs2_set_bit(bit_off++, biपंचांगap);

	ocfs2_journal_dirty(handle, group_bh);

bail:
	वापस status;
पूर्ण

/* find the one with the most empty bits */
अटल अंतरभूत u16 ocfs2_find_victim_chain(काष्ठा ocfs2_chain_list *cl)
अणु
	u16 curr, best;

	BUG_ON(!cl->cl_next_मुक्त_rec);

	best = curr = 0;
	जबतक (curr < le16_to_cpu(cl->cl_next_मुक्त_rec)) अणु
		अगर (le32_to_cpu(cl->cl_recs[curr].c_मुक्त) >
		    le32_to_cpu(cl->cl_recs[best].c_मुक्त))
			best = curr;
		curr++;
	पूर्ण

	BUG_ON(best >= le16_to_cpu(cl->cl_next_मुक्त_rec));
	वापस best;
पूर्ण

अटल पूर्णांक ocfs2_relink_block_group(handle_t *handle,
				    काष्ठा inode *alloc_inode,
				    काष्ठा buffer_head *fe_bh,
				    काष्ठा buffer_head *bg_bh,
				    काष्ठा buffer_head *prev_bg_bh,
				    u16 chain)
अणु
	पूर्णांक status;
	/* there is a really tiny chance the journal calls could fail,
	 * but we wouldn't want inconsistent blocks in *any* हाल. */
	u64 bg_ptr, prev_bg_ptr;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) fe_bh->b_data;
	काष्ठा ocfs2_group_desc *bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;
	काष्ठा ocfs2_group_desc *prev_bg = (काष्ठा ocfs2_group_desc *) prev_bg_bh->b_data;

	/* The caller got these descriptors from
	 * ocfs2_पढ़ो_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(prev_bg));

	trace_ocfs2_relink_block_group(
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_blkno), chain,
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(bg->bg_blkno),
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(prev_bg->bg_blkno));

	bg_ptr = le64_to_cpu(bg->bg_next_group);
	prev_bg_ptr = le64_to_cpu(prev_bg->bg_next_group);

	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 prev_bg_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0)
		जाओ out;

	prev_bg->bg_next_group = bg->bg_next_group;
	ocfs2_journal_dirty(handle, prev_bg_bh);

	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 bg_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0)
		जाओ out_rollback_prev_bg;

	bg->bg_next_group = fe->id2.i_chain.cl_recs[chain].c_blkno;
	ocfs2_journal_dirty(handle, bg_bh);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 fe_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0)
		जाओ out_rollback_bg;

	fe->id2.i_chain.cl_recs[chain].c_blkno = bg->bg_blkno;
	ocfs2_journal_dirty(handle, fe_bh);

out:
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	वापस status;

out_rollback_bg:
	bg->bg_next_group = cpu_to_le64(bg_ptr);
out_rollback_prev_bg:
	prev_bg->bg_next_group = cpu_to_le64(prev_bg_ptr);
	जाओ out;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_block_group_reasonably_empty(काष्ठा ocfs2_group_desc *bg,
						     u32 wanted)
अणु
	वापस le16_to_cpu(bg->bg_मुक्त_bits_count) > wanted;
पूर्ण

/* वापस 0 on success, -ENOSPC to keep searching and any other < 0
 * value on error. */
अटल पूर्णांक ocfs2_cluster_group_search(काष्ठा inode *inode,
				      काष्ठा buffer_head *group_bh,
				      u32 bits_wanted, u32 min_bits,
				      u64 max_block,
				      काष्ठा ocfs2_suballoc_result *res)
अणु
	पूर्णांक search = -ENOSPC;
	पूर्णांक ret;
	u64 blkoff;
	काष्ठा ocfs2_group_desc *gd = (काष्ठा ocfs2_group_desc *) group_bh->b_data;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	अचिन्हित पूर्णांक max_bits, gd_cluster_off;

	BUG_ON(!ocfs2_is_cluster_biपंचांगap(inode));

	अगर (gd->bg_मुक्त_bits_count) अणु
		max_bits = le16_to_cpu(gd->bg_bits);

		/* Tail groups in cluster biपंचांगaps which aren't cpg
		 * aligned are prone to partial extension by a failed
		 * fs resize. If the file प्रणाली resize never got to
		 * update the dinode cluster count, then we करोn't want
		 * to trust any clusters past it, regardless of what
		 * the group descriptor says. */
		gd_cluster_off = ocfs2_blocks_to_clusters(inode->i_sb,
							  le64_to_cpu(gd->bg_blkno));
		अगर ((gd_cluster_off + max_bits) >
		    OCFS2_I(inode)->ip_clusters) अणु
			max_bits = OCFS2_I(inode)->ip_clusters - gd_cluster_off;
			trace_ocfs2_cluster_group_search_wrong_max_bits(
				(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno),
				le16_to_cpu(gd->bg_bits),
				OCFS2_I(inode)->ip_clusters, max_bits);
		पूर्ण

		ret = ocfs2_block_group_find_clear_bits(osb,
							group_bh, bits_wanted,
							max_bits, res);
		अगर (ret)
			वापस ret;

		अगर (max_block) अणु
			blkoff = ocfs2_clusters_to_blocks(inode->i_sb,
							  gd_cluster_off +
							  res->sr_bit_offset +
							  res->sr_bits);
			trace_ocfs2_cluster_group_search_max_block(
				(अचिन्हित दीर्घ दीर्घ)blkoff,
				(अचिन्हित दीर्घ दीर्घ)max_block);
			अगर (blkoff > max_block)
				वापस -ENOSPC;
		पूर्ण

		/* ocfs2_block_group_find_clear_bits() might
		 * वापस success, but we still want to वापस
		 * -ENOSPC unless it found the minimum number
		 * of bits. */
		अगर (min_bits <= res->sr_bits)
			search = 0; /* success */
		अन्यथा अगर (res->sr_bits) अणु
			/*
			 * Don't show bits which we'll be वापसing
			 * क्रम allocation to the local alloc biपंचांगap.
			 */
			ocfs2_local_alloc_seen_मुक्त_bits(osb, res->sr_bits);
		पूर्ण
	पूर्ण

	वापस search;
पूर्ण

अटल पूर्णांक ocfs2_block_group_search(काष्ठा inode *inode,
				    काष्ठा buffer_head *group_bh,
				    u32 bits_wanted, u32 min_bits,
				    u64 max_block,
				    काष्ठा ocfs2_suballoc_result *res)
अणु
	पूर्णांक ret = -ENOSPC;
	u64 blkoff;
	काष्ठा ocfs2_group_desc *bg = (काष्ठा ocfs2_group_desc *) group_bh->b_data;

	BUG_ON(min_bits != 1);
	BUG_ON(ocfs2_is_cluster_biपंचांगap(inode));

	अगर (bg->bg_मुक्त_bits_count) अणु
		ret = ocfs2_block_group_find_clear_bits(OCFS2_SB(inode->i_sb),
							group_bh, bits_wanted,
							le16_to_cpu(bg->bg_bits),
							res);
		अगर (!ret && max_block) अणु
			blkoff = le64_to_cpu(bg->bg_blkno) +
				res->sr_bit_offset + res->sr_bits;
			trace_ocfs2_block_group_search_max_block(
				(अचिन्हित दीर्घ दीर्घ)blkoff,
				(अचिन्हित दीर्घ दीर्घ)max_block);
			अगर (blkoff > max_block)
				ret = -ENOSPC;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_alloc_dinode_update_counts(काष्ठा inode *inode,
				       handle_t *handle,
				       काष्ठा buffer_head *di_bh,
				       u32 num_bits,
				       u16 chain)
अणु
	पूर्णांक ret;
	u32 पंचांगp_used;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	काष्ठा ocfs2_chain_list *cl = (काष्ठा ocfs2_chain_list *) &di->id2.i_chain;

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	पंचांगp_used = le32_to_cpu(di->id1.biपंचांगap1.i_used);
	di->id1.biपंचांगap1.i_used = cpu_to_le32(num_bits + पंचांगp_used);
	le32_add_cpu(&cl->cl_recs[chain].c_मुक्त, -num_bits);
	ocfs2_journal_dirty(handle, di_bh);

out:
	वापस ret;
पूर्ण

व्योम ocfs2_rollback_alloc_dinode_counts(काष्ठा inode *inode,
				       काष्ठा buffer_head *di_bh,
				       u32 num_bits,
				       u16 chain)
अणु
	u32 पंचांगp_used;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	काष्ठा ocfs2_chain_list *cl;

	cl = (काष्ठा ocfs2_chain_list *)&di->id2.i_chain;
	पंचांगp_used = le32_to_cpu(di->id1.biपंचांगap1.i_used);
	di->id1.biपंचांगap1.i_used = cpu_to_le32(पंचांगp_used - num_bits);
	le32_add_cpu(&cl->cl_recs[chain].c_मुक्त, num_bits);
पूर्ण

अटल पूर्णांक ocfs2_bg_discontig_fix_by_rec(काष्ठा ocfs2_suballoc_result *res,
					 काष्ठा ocfs2_extent_rec *rec,
					 काष्ठा ocfs2_chain_list *cl)
अणु
	अचिन्हित पूर्णांक bpc = le16_to_cpu(cl->cl_bpc);
	अचिन्हित पूर्णांक bitoff = le32_to_cpu(rec->e_cpos) * bpc;
	अचिन्हित पूर्णांक bitcount = le16_to_cpu(rec->e_leaf_clusters) * bpc;

	अगर (res->sr_bit_offset < bitoff)
		वापस 0;
	अगर (res->sr_bit_offset >= (bitoff + bitcount))
		वापस 0;
	res->sr_blkno = le64_to_cpu(rec->e_blkno) +
		(res->sr_bit_offset - bitoff);
	अगर ((res->sr_bit_offset + res->sr_bits) > (bitoff + bitcount))
		res->sr_bits = (bitoff + bitcount) - res->sr_bit_offset;
	वापस 1;
पूर्ण

अटल व्योम ocfs2_bg_discontig_fix_result(काष्ठा ocfs2_alloc_context *ac,
					  काष्ठा ocfs2_group_desc *bg,
					  काष्ठा ocfs2_suballoc_result *res)
अणु
	पूर्णांक i;
	u64 bg_blkno = res->sr_bg_blkno;  /* Save off */
	काष्ठा ocfs2_extent_rec *rec;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)ac->ac_bh->b_data;
	काष्ठा ocfs2_chain_list *cl = &di->id2.i_chain;

	अगर (ocfs2_is_cluster_biपंचांगap(ac->ac_inode)) अणु
		res->sr_blkno = 0;
		वापस;
	पूर्ण

	res->sr_blkno = res->sr_bg_blkno + res->sr_bit_offset;
	res->sr_bg_blkno = 0;  /* Clear it क्रम contig block groups */
	अगर (!ocfs2_supports_discontig_bg(OCFS2_SB(ac->ac_inode->i_sb)) ||
	    !bg->bg_list.l_next_मुक्त_rec)
		वापस;

	क्रम (i = 0; i < le16_to_cpu(bg->bg_list.l_next_मुक्त_rec); i++) अणु
		rec = &bg->bg_list.l_recs[i];
		अगर (ocfs2_bg_discontig_fix_by_rec(res, rec, cl)) अणु
			res->sr_bg_blkno = bg_blkno;  /* Restore */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_search_one_group(काष्ठा ocfs2_alloc_context *ac,
				  handle_t *handle,
				  u32 bits_wanted,
				  u32 min_bits,
				  काष्ठा ocfs2_suballoc_result *res,
				  u16 *bits_left)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *group_bh = शून्य;
	काष्ठा ocfs2_group_desc *gd;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)ac->ac_bh->b_data;
	काष्ठा inode *alloc_inode = ac->ac_inode;

	ret = ocfs2_पढ़ो_group_descriptor(alloc_inode, di,
					  res->sr_bg_blkno, &group_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	gd = (काष्ठा ocfs2_group_desc *) group_bh->b_data;
	ret = ac->ac_group_search(alloc_inode, group_bh, bits_wanted, min_bits,
				  ac->ac_max_block, res);
	अगर (ret < 0) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!ret)
		ocfs2_bg_discontig_fix_result(ac, gd, res);

	/*
	 * sr_bg_blkno might have been changed by
	 * ocfs2_bg_discontig_fix_result
	 */
	res->sr_bg_stable_blkno = group_bh->b_blocknr;

	अगर (ac->ac_find_loc_only)
		जाओ out_loc_only;

	ret = ocfs2_alloc_dinode_update_counts(alloc_inode, handle, ac->ac_bh,
					       res->sr_bits,
					       le16_to_cpu(gd->bg_chain));
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_block_group_set_bits(handle, alloc_inode, gd, group_bh,
					 res->sr_bit_offset, res->sr_bits);
	अगर (ret < 0) अणु
		ocfs2_rollback_alloc_dinode_counts(alloc_inode, ac->ac_bh,
					       res->sr_bits,
					       le16_to_cpu(gd->bg_chain));
		mlog_त्रुटि_सं(ret);
	पूर्ण

out_loc_only:
	*bits_left = le16_to_cpu(gd->bg_मुक्त_bits_count);

out:
	brअन्यथा(group_bh);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_search_chain(काष्ठा ocfs2_alloc_context *ac,
			      handle_t *handle,
			      u32 bits_wanted,
			      u32 min_bits,
			      काष्ठा ocfs2_suballoc_result *res,
			      u16 *bits_left)
अणु
	पूर्णांक status;
	u16 chain;
	u64 next_group;
	काष्ठा inode *alloc_inode = ac->ac_inode;
	काष्ठा buffer_head *group_bh = शून्य;
	काष्ठा buffer_head *prev_group_bh = शून्य;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) ac->ac_bh->b_data;
	काष्ठा ocfs2_chain_list *cl = (काष्ठा ocfs2_chain_list *) &fe->id2.i_chain;
	काष्ठा ocfs2_group_desc *bg;

	chain = ac->ac_chain;
	trace_ocfs2_search_chain_begin(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(alloc_inode)->ip_blkno,
		bits_wanted, chain);

	status = ocfs2_पढ़ो_group_descriptor(alloc_inode, fe,
					     le64_to_cpu(cl->cl_recs[chain].c_blkno),
					     &group_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	bg = (काष्ठा ocfs2_group_desc *) group_bh->b_data;

	status = -ENOSPC;
	/* क्रम now, the chain search is a bit simplistic. We just use
	 * the 1st group with any empty bits. */
	जबतक ((status = ac->ac_group_search(alloc_inode, group_bh,
					     bits_wanted, min_bits,
					     ac->ac_max_block,
					     res)) == -ENOSPC) अणु
		अगर (!bg->bg_next_group)
			अवरोध;

		brअन्यथा(prev_group_bh);
		prev_group_bh = शून्य;

		next_group = le64_to_cpu(bg->bg_next_group);
		prev_group_bh = group_bh;
		group_bh = शून्य;
		status = ocfs2_पढ़ो_group_descriptor(alloc_inode, fe,
						     next_group, &group_bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		bg = (काष्ठा ocfs2_group_desc *) group_bh->b_data;
	पूर्ण
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_search_chain_succ(
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(bg->bg_blkno), res->sr_bits);

	res->sr_bg_blkno = le64_to_cpu(bg->bg_blkno);

	BUG_ON(res->sr_bits == 0);
	अगर (!status)
		ocfs2_bg_discontig_fix_result(ac, bg, res);

	/*
	 * sr_bg_blkno might have been changed by
	 * ocfs2_bg_discontig_fix_result
	 */
	res->sr_bg_stable_blkno = group_bh->b_blocknr;

	/*
	 * Keep track of previous block descriptor पढ़ो. When
	 * we find a target, अगर we have पढ़ो more than X
	 * number of descriptors, and the target is reasonably
	 * empty, relink him to top of his chain.
	 *
	 * We've पढ़ो 0 extra blocks and only send one more to
	 * the transaction, yet the next guy to search has a
	 * much easier समय.
	 *
	 * Do this *after* figuring out how many bits we're taking out
	 * of our target group.
	 */
	अगर (!ac->ac_disable_chain_relink &&
	    (prev_group_bh) &&
	    (ocfs2_block_group_reasonably_empty(bg, res->sr_bits))) अणु
		status = ocfs2_relink_block_group(handle, alloc_inode,
						  ac->ac_bh, group_bh,
						  prev_group_bh, chain);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	अगर (ac->ac_find_loc_only)
		जाओ out_loc_only;

	status = ocfs2_alloc_dinode_update_counts(alloc_inode, handle,
						  ac->ac_bh, res->sr_bits,
						  chain);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_block_group_set_bits(handle,
					    alloc_inode,
					    bg,
					    group_bh,
					    res->sr_bit_offset,
					    res->sr_bits);
	अगर (status < 0) अणु
		ocfs2_rollback_alloc_dinode_counts(alloc_inode,
					ac->ac_bh, res->sr_bits, chain);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_search_chain_end(
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_blkno),
			res->sr_bits);

out_loc_only:
	*bits_left = le16_to_cpu(bg->bg_मुक्त_bits_count);
bail:
	brअन्यथा(group_bh);
	brअन्यथा(prev_group_bh);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* will give out up to bits_wanted contiguous bits. */
अटल पूर्णांक ocfs2_claim_suballoc_bits(काष्ठा ocfs2_alloc_context *ac,
				     handle_t *handle,
				     u32 bits_wanted,
				     u32 min_bits,
				     काष्ठा ocfs2_suballoc_result *res)
अणु
	पूर्णांक status;
	u16 victim, i;
	u16 bits_left = 0;
	u64 hपूर्णांक = ac->ac_last_group;
	काष्ठा ocfs2_chain_list *cl;
	काष्ठा ocfs2_dinode *fe;

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);
	BUG_ON(bits_wanted > (ac->ac_bits_wanted - ac->ac_bits_given));
	BUG_ON(!ac->ac_bh);

	fe = (काष्ठा ocfs2_dinode *) ac->ac_bh->b_data;

	/* The bh was validated by the inode पढ़ो during
	 * ocfs2_reserve_suballoc_bits().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	अगर (le32_to_cpu(fe->id1.biपंचांगap1.i_used) >=
	    le32_to_cpu(fe->id1.biपंचांगap1.i_total)) अणु
		status = ocfs2_error(ac->ac_inode->i_sb,
				     "Chain allocator dinode %llu has %u used bits but only %u total\n",
				     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_blkno),
				     le32_to_cpu(fe->id1.biपंचांगap1.i_used),
				     le32_to_cpu(fe->id1.biपंचांगap1.i_total));
		जाओ bail;
	पूर्ण

	res->sr_bg_blkno = hपूर्णांक;
	अगर (res->sr_bg_blkno) अणु
		/* Attempt to लघु-circuit the usual search mechanism
		 * by jumping straight to the most recently used
		 * allocation group. This helps us मुख्यtain some
		 * contiguousness across allocations. */
		status = ocfs2_search_one_group(ac, handle, bits_wanted,
						min_bits, res, &bits_left);
		अगर (!status)
			जाओ set_hपूर्णांक;
		अगर (status < 0 && status != -ENOSPC) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	cl = (काष्ठा ocfs2_chain_list *) &fe->id2.i_chain;

	victim = ocfs2_find_victim_chain(cl);
	ac->ac_chain = victim;

	status = ocfs2_search_chain(ac, handle, bits_wanted, min_bits,
				    res, &bits_left);
	अगर (!status) अणु
		अगर (ocfs2_is_cluster_biपंचांगap(ac->ac_inode))
			hपूर्णांक = res->sr_bg_blkno;
		अन्यथा
			hपूर्णांक = ocfs2_group_from_res(res);
		जाओ set_hपूर्णांक;
	पूर्ण
	अगर (status < 0 && status != -ENOSPC) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_claim_suballoc_bits(victim);

	/* If we didn't pick a good victim, then just शेष to
	 * searching each chain in order. Don't allow chain relinking
	 * because we only calculate enough journal credits क्रम one
	 * relink per alloc. */
	ac->ac_disable_chain_relink = 1;
	क्रम (i = 0; i < le16_to_cpu(cl->cl_next_मुक्त_rec); i ++) अणु
		अगर (i == victim)
			जारी;
		अगर (!cl->cl_recs[i].c_मुक्त)
			जारी;

		ac->ac_chain = i;
		status = ocfs2_search_chain(ac, handle, bits_wanted, min_bits,
					    res, &bits_left);
		अगर (!status) अणु
			hपूर्णांक = ocfs2_group_from_res(res);
			अवरोध;
		पूर्ण
		अगर (status < 0 && status != -ENOSPC) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

set_hपूर्णांक:
	अगर (status != -ENOSPC) अणु
		/* If the next search of this group is not likely to
		 * yield a suitable extent, then we reset the last
		 * group hपूर्णांक so as to not waste a disk पढ़ो */
		अगर (bits_left < min_bits)
			ac->ac_last_group = 0;
		अन्यथा
			ac->ac_last_group = hपूर्णांक;
	पूर्ण

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_claim_metadata(handle_t *handle,
			 काष्ठा ocfs2_alloc_context *ac,
			 u32 bits_wanted,
			 u64 *suballoc_loc,
			 u16 *suballoc_bit_start,
			 अचिन्हित पूर्णांक *num_bits,
			 u64 *blkno_start)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_suballoc_result res = अणु .sr_blkno = 0, पूर्ण;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_wanted < (ac->ac_bits_given + bits_wanted));
	BUG_ON(ac->ac_which != OCFS2_AC_USE_META);

	status = ocfs2_claim_suballoc_bits(ac,
					   handle,
					   bits_wanted,
					   1,
					   &res);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	*suballoc_loc = res.sr_bg_blkno;
	*suballoc_bit_start = res.sr_bit_offset;
	*blkno_start = res.sr_blkno;
	ac->ac_bits_given += res.sr_bits;
	*num_bits = res.sr_bits;
	status = 0;
bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम ocfs2_init_inode_ac_group(काष्ठा inode *dir,
				      काष्ठा buffer_head *parent_di_bh,
				      काष्ठा ocfs2_alloc_context *ac)
अणु
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)parent_di_bh->b_data;
	/*
	 * Try to allocate inodes from some specअगरic group.
	 *
	 * If the parent dir has recorded the last group used in allocation,
	 * cool, use it. Otherwise अगर we try to allocate new inode from the
	 * same slot the parent dir beदीर्घs to, use the same chunk.
	 *
	 * We are very careful here to aव्योम the mistake of setting
	 * ac_last_group to a group descriptor from a dअगरferent (unlocked) slot.
	 */
	अगर (OCFS2_I(dir)->ip_last_used_group &&
	    OCFS2_I(dir)->ip_last_used_slot == ac->ac_alloc_slot)
		ac->ac_last_group = OCFS2_I(dir)->ip_last_used_group;
	अन्यथा अगर (le16_to_cpu(di->i_suballoc_slot) == ac->ac_alloc_slot) अणु
		अगर (di->i_suballoc_loc)
			ac->ac_last_group = le64_to_cpu(di->i_suballoc_loc);
		अन्यथा
			ac->ac_last_group = ocfs2_which_suballoc_group(
					le64_to_cpu(di->i_blkno),
					le16_to_cpu(di->i_suballoc_bit));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ocfs2_save_inode_ac_group(काष्ठा inode *dir,
					     काष्ठा ocfs2_alloc_context *ac)
अणु
	OCFS2_I(dir)->ip_last_used_group = ac->ac_last_group;
	OCFS2_I(dir)->ip_last_used_slot = ac->ac_alloc_slot;
पूर्ण

पूर्णांक ocfs2_find_new_inode_loc(काष्ठा inode *dir,
			     काष्ठा buffer_head *parent_fe_bh,
			     काष्ठा ocfs2_alloc_context *ac,
			     u64 *fe_blkno)
अणु
	पूर्णांक ret;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_suballoc_result *res;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	res = kzalloc(माप(*res), GFP_NOFS);
	अगर (res == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_init_inode_ac_group(dir, parent_fe_bh, ac);

	/*
	 * The handle started here is क्रम chain relink. Alternatively,
	 * we could just disable relink क्रम these calls.
	 */
	handle = ocfs2_start_trans(OCFS2_SB(dir->i_sb), OCFS2_SUBALLOC_ALLOC);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * This will inकाष्ठा ocfs2_claim_suballoc_bits and
	 * ocfs2_search_one_group to search but save actual allocation
	 * क्रम later.
	 */
	ac->ac_find_loc_only = 1;

	ret = ocfs2_claim_suballoc_bits(ac, handle, 1, 1, res);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ac->ac_find_loc_priv = res;
	*fe_blkno = res->sr_blkno;
	ocfs2_update_inode_fsync_trans(handle, dir, 0);
out:
	अगर (handle)
		ocfs2_commit_trans(OCFS2_SB(dir->i_sb), handle);

	अगर (ret)
		kमुक्त(res);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_claim_new_inode_at_loc(handle_t *handle,
				 काष्ठा inode *dir,
				 काष्ठा ocfs2_alloc_context *ac,
				 u64 *suballoc_loc,
				 u16 *suballoc_bit,
				 u64 di_blkno)
अणु
	पूर्णांक ret;
	u16 chain;
	काष्ठा ocfs2_suballoc_result *res = ac->ac_find_loc_priv;
	काष्ठा buffer_head *bg_bh = शून्य;
	काष्ठा ocfs2_group_desc *bg;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) ac->ac_bh->b_data;

	/*
	 * Since di_blkno is being passed back in, we check क्रम any
	 * inconsistencies which may have happened between
	 * calls. These are code bugs as di_blkno is not expected to
	 * change once वापसed from ocfs2_find_new_inode_loc()
	 */
	BUG_ON(res->sr_blkno != di_blkno);

	ret = ocfs2_पढ़ो_group_descriptor(ac->ac_inode, di,
					  res->sr_bg_stable_blkno, &bg_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	bg = (काष्ठा ocfs2_group_desc *) bg_bh->b_data;
	chain = le16_to_cpu(bg->bg_chain);

	ret = ocfs2_alloc_dinode_update_counts(ac->ac_inode, handle,
					       ac->ac_bh, res->sr_bits,
					       chain);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_block_group_set_bits(handle,
					 ac->ac_inode,
					 bg,
					 bg_bh,
					 res->sr_bit_offset,
					 res->sr_bits);
	अगर (ret < 0) अणु
		ocfs2_rollback_alloc_dinode_counts(ac->ac_inode,
					       ac->ac_bh, res->sr_bits, chain);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_claim_new_inode_at_loc((अचिन्हित दीर्घ दीर्घ)di_blkno,
					   res->sr_bits);

	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	BUG_ON(res->sr_bits != 1);

	*suballoc_loc = res->sr_bg_blkno;
	*suballoc_bit = res->sr_bit_offset;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_group(dir, ac);

out:
	brअन्यथा(bg_bh);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_claim_new_inode(handle_t *handle,
			  काष्ठा inode *dir,
			  काष्ठा buffer_head *parent_fe_bh,
			  काष्ठा ocfs2_alloc_context *ac,
			  u64 *suballoc_loc,
			  u16 *suballoc_bit,
			  u64 *fe_blkno)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_suballoc_result res;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	ocfs2_init_inode_ac_group(dir, parent_fe_bh, ac);

	status = ocfs2_claim_suballoc_bits(ac,
					   handle,
					   1,
					   1,
					   &res);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	BUG_ON(res.sr_bits != 1);

	*suballoc_loc = res.sr_bg_blkno;
	*suballoc_bit = res.sr_bit_offset;
	*fe_blkno = res.sr_blkno;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_group(dir, ac);
	status = 0;
bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* translate a group desc. blkno and it's biपंचांगap offset पूर्णांकo
 * disk cluster offset. */
अटल अंतरभूत u32 ocfs2_desc_biपंचांगap_to_cluster_off(काष्ठा inode *inode,
						   u64 bg_blkno,
						   u16 bg_bit_off)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u32 cluster = 0;

	BUG_ON(!ocfs2_is_cluster_biपंचांगap(inode));

	अगर (bg_blkno != osb->first_cluster_group_blkno)
		cluster = ocfs2_blocks_to_clusters(inode->i_sb, bg_blkno);
	cluster += (u32) bg_bit_off;
	वापस cluster;
पूर्ण

/* given a cluster offset, calculate which block group it beदीर्घs to
 * and वापस that block offset. */
u64 ocfs2_which_cluster_group(काष्ठा inode *inode, u32 cluster)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u32 group_no;

	BUG_ON(!ocfs2_is_cluster_biपंचांगap(inode));

	group_no = cluster / osb->biपंचांगap_cpg;
	अगर (!group_no)
		वापस osb->first_cluster_group_blkno;
	वापस ocfs2_clusters_to_blocks(inode->i_sb,
					group_no * osb->biपंचांगap_cpg);
पूर्ण

/* given the block number of a cluster start, calculate which cluster
 * group and descriptor biपंचांगap offset that corresponds to. */
अटल अंतरभूत व्योम ocfs2_block_to_cluster_group(काष्ठा inode *inode,
						u64 data_blkno,
						u64 *bg_blkno,
						u16 *bg_bit_off)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u32 data_cluster = ocfs2_blocks_to_clusters(osb->sb, data_blkno);

	BUG_ON(!ocfs2_is_cluster_biपंचांगap(inode));

	*bg_blkno = ocfs2_which_cluster_group(inode,
					      data_cluster);

	अगर (*bg_blkno == osb->first_cluster_group_blkno)
		*bg_bit_off = (u16) data_cluster;
	अन्यथा
		*bg_bit_off = (u16) ocfs2_blocks_to_clusters(osb->sb,
							     data_blkno - *bg_blkno);
पूर्ण

/*
 * min_bits - minimum contiguous chunk from this total allocation we
 * can handle. set to what we asked क्रम originally क्रम a full
 * contig. allocation, set to '1' to indicate we can deal with extents
 * of any size.
 */
पूर्णांक __ocfs2_claim_clusters(handle_t *handle,
			   काष्ठा ocfs2_alloc_context *ac,
			   u32 min_clusters,
			   u32 max_clusters,
			   u32 *cluster_start,
			   u32 *num_clusters)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक bits_wanted = max_clusters;
	काष्ठा ocfs2_suballoc_result res = अणु .sr_blkno = 0, पूर्ण;
	काष्ठा ocfs2_super *osb = OCFS2_SB(ac->ac_inode->i_sb);

	BUG_ON(ac->ac_bits_given >= ac->ac_bits_wanted);

	BUG_ON(ac->ac_which != OCFS2_AC_USE_LOCAL
	       && ac->ac_which != OCFS2_AC_USE_MAIN);

	अगर (ac->ac_which == OCFS2_AC_USE_LOCAL) अणु
		WARN_ON(min_clusters > 1);

		status = ocfs2_claim_local_alloc_bits(osb,
						      handle,
						      ac,
						      bits_wanted,
						      cluster_start,
						      num_clusters);
		अगर (!status)
			atomic_inc(&osb->alloc_stats.local_data);
	पूर्ण अन्यथा अणु
		अगर (min_clusters > (osb->biपंचांगap_cpg - 1)) अणु
			/* The only paths asking क्रम contiguousness
			 * should know about this alपढ़ोy. */
			mlog(ML_ERROR, "minimum allocation requested %u exceeds "
			     "group bitmap size %u!\n", min_clusters,
			     osb->biपंचांगap_cpg);
			status = -ENOSPC;
			जाओ bail;
		पूर्ण
		/* clamp the current request करोwn to a realistic size. */
		अगर (bits_wanted > (osb->biपंचांगap_cpg - 1))
			bits_wanted = osb->biपंचांगap_cpg - 1;

		status = ocfs2_claim_suballoc_bits(ac,
						   handle,
						   bits_wanted,
						   min_clusters,
						   &res);
		अगर (!status) अणु
			BUG_ON(res.sr_blkno); /* cluster alloc can't set */
			*cluster_start =
				ocfs2_desc_biपंचांगap_to_cluster_off(ac->ac_inode,
								 res.sr_bg_blkno,
								 res.sr_bit_offset);
			atomic_inc(&osb->alloc_stats.biपंचांगap_data);
			*num_clusters = res.sr_bits;
		पूर्ण
	पूर्ण
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ac->ac_bits_given += *num_clusters;

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_claim_clusters(handle_t *handle,
			 काष्ठा ocfs2_alloc_context *ac,
			 u32 min_clusters,
			 u32 *cluster_start,
			 u32 *num_clusters)
अणु
	अचिन्हित पूर्णांक bits_wanted = ac->ac_bits_wanted - ac->ac_bits_given;

	वापस __ocfs2_claim_clusters(handle, ac, min_clusters,
				      bits_wanted, cluster_start, num_clusters);
पूर्ण

अटल पूर्णांक ocfs2_block_group_clear_bits(handle_t *handle,
					काष्ठा inode *alloc_inode,
					काष्ठा ocfs2_group_desc *bg,
					काष्ठा buffer_head *group_bh,
					अचिन्हित पूर्णांक bit_off,
					अचिन्हित पूर्णांक num_bits,
					व्योम (*unकरो_fn)(अचिन्हित पूर्णांक bit,
							अचिन्हित दीर्घ *bmap))
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा ocfs2_group_desc *unकरो_bg = शून्य;
	काष्ठा journal_head *jh;

	/* The caller got this descriptor from
	 * ocfs2_पढ़ो_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));

	trace_ocfs2_block_group_clear_bits(bit_off, num_bits);

	BUG_ON(unकरो_fn && !ocfs2_is_cluster_biपंचांगap(alloc_inode));
	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 group_bh,
					 unकरो_fn ?
					 OCFS2_JOURNAL_ACCESS_UNDO :
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	jh = bh2jh(group_bh);
	अगर (unकरो_fn) अणु
		spin_lock(&jh->b_state_lock);
		unकरो_bg = (काष्ठा ocfs2_group_desc *) jh->b_committed_data;
		BUG_ON(!unकरो_bg);
	पूर्ण

	पंचांगp = num_bits;
	जबतक(पंचांगp--) अणु
		ocfs2_clear_bit((bit_off + पंचांगp),
				(अचिन्हित दीर्घ *) bg->bg_biपंचांगap);
		अगर (unकरो_fn)
			unकरो_fn(bit_off + पंचांगp,
				(अचिन्हित दीर्घ *) unकरो_bg->bg_biपंचांगap);
	पूर्ण
	le16_add_cpu(&bg->bg_मुक्त_bits_count, num_bits);
	अगर (le16_to_cpu(bg->bg_मुक्त_bits_count) > le16_to_cpu(bg->bg_bits)) अणु
		अगर (unकरो_fn)
			spin_unlock(&jh->b_state_lock);
		वापस ocfs2_error(alloc_inode->i_sb, "Group descriptor # %llu has bit count %u but claims %u are freed. num_bits %d\n",
				   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(bg->bg_blkno),
				   le16_to_cpu(bg->bg_bits),
				   le16_to_cpu(bg->bg_मुक्त_bits_count),
				   num_bits);
	पूर्ण

	अगर (unकरो_fn)
		spin_unlock(&jh->b_state_lock);

	ocfs2_journal_dirty(handle, group_bh);
bail:
	वापस status;
पूर्ण

/*
 * expects the suballoc inode to alपढ़ोy be locked.
 */
अटल पूर्णांक _ocfs2_मुक्त_suballoc_bits(handle_t *handle,
				     काष्ठा inode *alloc_inode,
				     काष्ठा buffer_head *alloc_bh,
				     अचिन्हित पूर्णांक start_bit,
				     u64 bg_blkno,
				     अचिन्हित पूर्णांक count,
				     व्योम (*unकरो_fn)(अचिन्हित पूर्णांक bit,
						     अचिन्हित दीर्घ *biपंचांगap))
अणु
	पूर्णांक status = 0;
	u32 पंचांगp_used;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) alloc_bh->b_data;
	काष्ठा ocfs2_chain_list *cl = &fe->id2.i_chain;
	काष्ठा buffer_head *group_bh = शून्य;
	काष्ठा ocfs2_group_desc *group;

	/* The alloc_bh comes from ocfs2_मुक्त_dinode() or
	 * ocfs2_मुक्त_clusters().  The callers have all locked the
	 * allocator and gotten alloc_bh from the lock call.  This
	 * validates the dinode buffer.  Any corruption that has happened
	 * is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));
	BUG_ON((count + start_bit) > ocfs2_bits_per_group(cl));

	trace_ocfs2_मुक्त_suballoc_bits(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(alloc_inode)->ip_blkno,
		(अचिन्हित दीर्घ दीर्घ)bg_blkno,
		start_bit, count);

	status = ocfs2_पढ़ो_group_descriptor(alloc_inode, fe, bg_blkno,
					     &group_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	group = (काष्ठा ocfs2_group_desc *) group_bh->b_data;

	BUG_ON((count + start_bit) > le16_to_cpu(group->bg_bits));

	status = ocfs2_block_group_clear_bits(handle, alloc_inode,
					      group, group_bh,
					      start_bit, count, unकरो_fn);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 alloc_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		ocfs2_block_group_set_bits(handle, alloc_inode, group, group_bh,
				start_bit, count);
		जाओ bail;
	पूर्ण

	le32_add_cpu(&cl->cl_recs[le16_to_cpu(group->bg_chain)].c_मुक्त,
		     count);
	पंचांगp_used = le32_to_cpu(fe->id1.biपंचांगap1.i_used);
	fe->id1.biपंचांगap1.i_used = cpu_to_le32(पंचांगp_used - count);
	ocfs2_journal_dirty(handle, alloc_bh);

bail:
	brअन्यथा(group_bh);
	वापस status;
पूर्ण

पूर्णांक ocfs2_मुक्त_suballoc_bits(handle_t *handle,
			     काष्ठा inode *alloc_inode,
			     काष्ठा buffer_head *alloc_bh,
			     अचिन्हित पूर्णांक start_bit,
			     u64 bg_blkno,
			     अचिन्हित पूर्णांक count)
अणु
	वापस _ocfs2_मुक्त_suballoc_bits(handle, alloc_inode, alloc_bh,
					 start_bit, bg_blkno, count, शून्य);
पूर्ण

पूर्णांक ocfs2_मुक्त_dinode(handle_t *handle,
		      काष्ठा inode *inode_alloc_inode,
		      काष्ठा buffer_head *inode_alloc_bh,
		      काष्ठा ocfs2_dinode *di)
अणु
	u64 blk = le64_to_cpu(di->i_blkno);
	u16 bit = le16_to_cpu(di->i_suballoc_bit);
	u64 bg_blkno = ocfs2_which_suballoc_group(blk, bit);

	अगर (di->i_suballoc_loc)
		bg_blkno = le64_to_cpu(di->i_suballoc_loc);
	वापस ocfs2_मुक्त_suballoc_bits(handle, inode_alloc_inode,
					inode_alloc_bh, bit, bg_blkno, 1);
पूर्ण

अटल पूर्णांक _ocfs2_मुक्त_clusters(handle_t *handle,
				काष्ठा inode *biपंचांगap_inode,
				काष्ठा buffer_head *biपंचांगap_bh,
				u64 start_blk,
				अचिन्हित पूर्णांक num_clusters,
				व्योम (*unकरो_fn)(अचिन्हित पूर्णांक bit,
						अचिन्हित दीर्घ *biपंचांगap))
अणु
	पूर्णांक status;
	u16 bg_start_bit;
	u64 bg_blkno;

	/* You can't ever have a contiguous set of clusters
	 * bigger than a block group biपंचांगap so we never have to worry
	 * about looping on them.
	 * This is expensive. We can safely हटाओ once this stuff has
	 * gotten tested really well. */
	BUG_ON(start_blk != ocfs2_clusters_to_blocks(biपंचांगap_inode->i_sb,
				ocfs2_blocks_to_clusters(biपंचांगap_inode->i_sb,
							 start_blk)));


	ocfs2_block_to_cluster_group(biपंचांगap_inode, start_blk, &bg_blkno,
				     &bg_start_bit);

	trace_ocfs2_मुक्त_clusters((अचिन्हित दीर्घ दीर्घ)bg_blkno,
			(अचिन्हित दीर्घ दीर्घ)start_blk,
			bg_start_bit, num_clusters);

	status = _ocfs2_मुक्त_suballoc_bits(handle, biपंचांगap_inode, biपंचांगap_bh,
					   bg_start_bit, bg_blkno,
					   num_clusters, unकरो_fn);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	ocfs2_local_alloc_seen_मुक्त_bits(OCFS2_SB(biपंचांगap_inode->i_sb),
					 num_clusters);

out:
	वापस status;
पूर्ण

पूर्णांक ocfs2_मुक्त_clusters(handle_t *handle,
			काष्ठा inode *biपंचांगap_inode,
			काष्ठा buffer_head *biपंचांगap_bh,
			u64 start_blk,
			अचिन्हित पूर्णांक num_clusters)
अणु
	वापस _ocfs2_मुक्त_clusters(handle, biपंचांगap_inode, biपंचांगap_bh,
				    start_blk, num_clusters,
				    _ocfs2_set_bit);
पूर्ण

/*
 * Give never-used clusters back to the global biपंचांगap.  We करोn't need
 * to protect these bits in the unकरो buffer.
 */
पूर्णांक ocfs2_release_clusters(handle_t *handle,
			   काष्ठा inode *biपंचांगap_inode,
			   काष्ठा buffer_head *biपंचांगap_bh,
			   u64 start_blk,
			   अचिन्हित पूर्णांक num_clusters)
अणु
	वापस _ocfs2_मुक्त_clusters(handle, biपंचांगap_inode, biपंचांगap_bh,
				    start_blk, num_clusters,
				    _ocfs2_clear_bit);
पूर्ण

/*
 * For a given allocation, determine which allocators will need to be
 * accessed, and lock them, reserving the appropriate number of bits.
 *
 * Sparse file प्रणालीs call this from ocfs2_ग_लिखो_begin_nolock()
 * and ocfs2_allocate_unwritten_extents().
 *
 * File प्रणालीs which करोn't support holes call this from
 * ocfs2_extend_allocation().
 */
पूर्णांक ocfs2_lock_allocators(काष्ठा inode *inode,
			  काष्ठा ocfs2_extent_tree *et,
			  u32 clusters_to_add, u32 extents_to_split,
			  काष्ठा ocfs2_alloc_context **data_ac,
			  काष्ठा ocfs2_alloc_context **meta_ac)
अणु
	पूर्णांक ret = 0, num_मुक्त_extents;
	अचिन्हित पूर्णांक max_recs_needed = clusters_to_add + 2 * extents_to_split;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	*meta_ac = शून्य;
	अगर (data_ac)
		*data_ac = शून्य;

	BUG_ON(clusters_to_add != 0 && data_ac == शून्य);

	num_मुक्त_extents = ocfs2_num_मुक्त_extents(et);
	अगर (num_मुक्त_extents < 0) अणु
		ret = num_मुक्त_extents;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Sparse allocation file प्रणालीs need to be more conservative
	 * with reserving room क्रम expansion - the actual allocation
	 * happens जबतक we've got a journal handle खोलो so re-taking
	 * a cluster lock (because we ran out of room क्रम another
	 * extent) will violate ordering rules.
	 *
	 * Most of the समय we'll only be seeing this 1 cluster at a समय
	 * anyway.
	 *
	 * Always lock क्रम any unwritten extents - we might want to
	 * add blocks during a split.
	 */
	अगर (!num_मुक्त_extents ||
	    (ocfs2_sparse_alloc(osb) && num_मुक्त_extents < max_recs_needed)) अणु
		ret = ocfs2_reserve_new_metadata(osb, et->et_root_el, meta_ac);
		अगर (ret < 0) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (clusters_to_add == 0)
		जाओ out;

	ret = ocfs2_reserve_clusters(osb, clusters_to_add, data_ac);
	अगर (ret < 0) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

out:
	अगर (ret) अणु
		अगर (*meta_ac) अणु
			ocfs2_मुक्त_alloc_context(*meta_ac);
			*meta_ac = शून्य;
		पूर्ण

		/*
		 * We cannot have an error and a non null *data_ac.
		 */
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Read the inode specअगरied by blkno to get suballoc_slot and
 * suballoc_bit.
 */
अटल पूर्णांक ocfs2_get_suballoc_slot_bit(काष्ठा ocfs2_super *osb, u64 blkno,
				       u16 *suballoc_slot, u64 *group_blkno,
				       u16 *suballoc_bit)
अणु
	पूर्णांक status;
	काष्ठा buffer_head *inode_bh = शून्य;
	काष्ठा ocfs2_dinode *inode_fe;

	trace_ocfs2_get_suballoc_slot_bit((अचिन्हित दीर्घ दीर्घ)blkno);

	/* dirty पढ़ो disk */
	status = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &inode_bh);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "read block %llu failed %d\n",
		     (अचिन्हित दीर्घ दीर्घ)blkno, status);
		जाओ bail;
	पूर्ण

	inode_fe = (काष्ठा ocfs2_dinode *) inode_bh->b_data;
	अगर (!OCFS2_IS_VALID_DINODE(inode_fe)) अणु
		mlog(ML_ERROR, "invalid inode %llu requested\n",
		     (अचिन्हित दीर्घ दीर्घ)blkno);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (le16_to_cpu(inode_fe->i_suballoc_slot) != (u16)OCFS2_INVALID_SLOT &&
	    (u32)le16_to_cpu(inode_fe->i_suballoc_slot) > osb->max_slots - 1) अणु
		mlog(ML_ERROR, "inode %llu has invalid suballoc slot %u\n",
		     (अचिन्हित दीर्घ दीर्घ)blkno,
		     (u32)le16_to_cpu(inode_fe->i_suballoc_slot));
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (suballoc_slot)
		*suballoc_slot = le16_to_cpu(inode_fe->i_suballoc_slot);
	अगर (suballoc_bit)
		*suballoc_bit = le16_to_cpu(inode_fe->i_suballoc_bit);
	अगर (group_blkno)
		*group_blkno = le64_to_cpu(inode_fe->i_suballoc_loc);

bail:
	brअन्यथा(inode_bh);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * test whether bit is SET in allocator biपंचांगap or not.  on success, 0
 * is वापसed and *res is 1 क्रम SET; 0 otherwise.  when fails, त्रुटि_सं
 * is वापसed and *res is meaningless.  Call this after you have
 * cluster locked against suballoc, or you may get a result based on
 * non-up2date contents
 */
अटल पूर्णांक ocfs2_test_suballoc_bit(काष्ठा ocfs2_super *osb,
				   काष्ठा inode *suballoc,
				   काष्ठा buffer_head *alloc_bh,
				   u64 group_blkno, u64 blkno,
				   u16 bit, पूर्णांक *res)
अणु
	काष्ठा ocfs2_dinode *alloc_di;
	काष्ठा ocfs2_group_desc *group;
	काष्ठा buffer_head *group_bh = शून्य;
	u64 bg_blkno;
	पूर्णांक status;

	trace_ocfs2_test_suballoc_bit((अचिन्हित दीर्घ दीर्घ)blkno,
				      (अचिन्हित पूर्णांक)bit);

	alloc_di = (काष्ठा ocfs2_dinode *)alloc_bh->b_data;
	अगर ((bit + 1) > ocfs2_bits_per_group(&alloc_di->id2.i_chain)) अणु
		mlog(ML_ERROR, "suballoc bit %u out of range of %u\n",
		     (अचिन्हित पूर्णांक)bit,
		     ocfs2_bits_per_group(&alloc_di->id2.i_chain));
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	bg_blkno = group_blkno ? group_blkno :
		   ocfs2_which_suballoc_group(blkno, bit);
	status = ocfs2_पढ़ो_group_descriptor(suballoc, alloc_di, bg_blkno,
					     &group_bh);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "read group %llu failed %d\n",
		     (अचिन्हित दीर्घ दीर्घ)bg_blkno, status);
		जाओ bail;
	पूर्ण

	group = (काष्ठा ocfs2_group_desc *) group_bh->b_data;
	*res = ocfs2_test_bit(bit, (अचिन्हित दीर्घ *)group->bg_biपंचांगap);

bail:
	brअन्यथा(group_bh);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * Test अगर the bit representing this inode (blkno) is set in the
 * suballocator.
 *
 * On success, 0 is वापसed and *res is 1 क्रम SET; 0 otherwise.
 *
 * In the event of failure, a negative value is वापसed and *res is
 * meaningless.
 *
 * Callers must make sure to hold nfs_sync_lock to prevent
 * ocfs2_delete_inode() on another node from accessing the same
 * suballocator concurrently.
 */
पूर्णांक ocfs2_test_inode_bit(काष्ठा ocfs2_super *osb, u64 blkno, पूर्णांक *res)
अणु
	पूर्णांक status;
	u64 group_blkno = 0;
	u16 suballoc_bit = 0, suballoc_slot = 0;
	काष्ठा inode *inode_alloc_inode;
	काष्ठा buffer_head *alloc_bh = शून्य;

	trace_ocfs2_test_inode_bit((अचिन्हित दीर्घ दीर्घ)blkno);

	status = ocfs2_get_suballoc_slot_bit(osb, blkno, &suballoc_slot,
					     &group_blkno, &suballoc_bit);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "get alloc slot and bit failed %d\n", status);
		जाओ bail;
	पूर्ण

	अगर (suballoc_slot == (u16)OCFS2_INVALID_SLOT)
		inode_alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
			GLOBAL_INODE_ALLOC_SYSTEM_INODE, suballoc_slot);
	अन्यथा
		inode_alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
			INODE_ALLOC_SYSTEM_INODE, suballoc_slot);
	अगर (!inode_alloc_inode) अणु
		/* the error code could be inaccurate, but we are not able to
		 * get the correct one. */
		status = -EINVAL;
		mlog(ML_ERROR, "unable to get alloc inode in slot %u\n",
		     (u32)suballoc_slot);
		जाओ bail;
	पूर्ण

	inode_lock(inode_alloc_inode);
	status = ocfs2_inode_lock(inode_alloc_inode, &alloc_bh, 0);
	अगर (status < 0) अणु
		inode_unlock(inode_alloc_inode);
		iput(inode_alloc_inode);
		mlog(ML_ERROR, "lock on alloc inode on slot %u failed %d\n",
		     (u32)suballoc_slot, status);
		जाओ bail;
	पूर्ण

	status = ocfs2_test_suballoc_bit(osb, inode_alloc_inode, alloc_bh,
					 group_blkno, blkno, suballoc_bit, res);
	अगर (status < 0)
		mlog(ML_ERROR, "test suballoc bit failed %d\n", status);

	ocfs2_inode_unlock(inode_alloc_inode, 0);
	inode_unlock(inode_alloc_inode);

	iput(inode_alloc_inode);
	brअन्यथा(alloc_bh);
bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण
