<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * resize.c
 *
 * volume resize.
 * Inspired by ext3/resize.c.
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dlmglue.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"
#समावेश "suballoc.h"
#समावेश "resize.h"

/*
 * Check whether there are new backup superblocks exist
 * in the last group. If there are some, mark them or clear
 * them in the biपंचांगap.
 *
 * Return how many backups we find in the last group.
 */
अटल u16 ocfs2_calc_new_backup_super(काष्ठा inode *inode,
				       काष्ठा ocfs2_group_desc *gd,
				       u16 cl_cpg,
				       u16 old_bg_clusters,
				       पूर्णांक set)
अणु
	पूर्णांक i;
	u16 backups = 0;
	u32 cluster, lgd_cluster;
	u64 blkno, gd_blkno, lgd_blkno = le64_to_cpu(gd->bg_blkno);

	क्रम (i = 0; i < OCFS2_MAX_BACKUP_SUPERBLOCKS; i++) अणु
		blkno = ocfs2_backup_super_blkno(inode->i_sb, i);
		cluster = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

		gd_blkno = ocfs2_which_cluster_group(inode, cluster);
		अगर (gd_blkno < lgd_blkno)
			जारी;
		अन्यथा अगर (gd_blkno > lgd_blkno)
			अवरोध;

		/* check अगर alपढ़ोy करोne backup super */
		lgd_cluster = ocfs2_blocks_to_clusters(inode->i_sb, lgd_blkno);
		lgd_cluster += old_bg_clusters;
		अगर (lgd_cluster >= cluster)
			जारी;

		अगर (set)
			ocfs2_set_bit(cluster % cl_cpg,
				      (अचिन्हित दीर्घ *)gd->bg_biपंचांगap);
		अन्यथा
			ocfs2_clear_bit(cluster % cl_cpg,
					(अचिन्हित दीर्घ *)gd->bg_biपंचांगap);
		backups++;
	पूर्ण

	वापस backups;
पूर्ण

अटल पूर्णांक ocfs2_update_last_group_and_inode(handle_t *handle,
					     काष्ठा inode *bm_inode,
					     काष्ठा buffer_head *bm_bh,
					     काष्ठा buffer_head *group_bh,
					     u32 first_new_cluster,
					     पूर्णांक new_clusters)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(bm_inode->i_sb);
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) bm_bh->b_data;
	काष्ठा ocfs2_chain_list *cl = &fe->id2.i_chain;
	काष्ठा ocfs2_chain_rec *cr;
	काष्ठा ocfs2_group_desc *group;
	u16 chain, num_bits, backups = 0;
	u16 cl_bpc = le16_to_cpu(cl->cl_bpc);
	u16 cl_cpg = le16_to_cpu(cl->cl_cpg);
	u16 old_bg_clusters;

	trace_ocfs2_update_last_group_and_inode(new_clusters,
						first_new_cluster);

	ret = ocfs2_journal_access_gd(handle, INODE_CACHE(bm_inode),
				      group_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	group = (काष्ठा ocfs2_group_desc *)group_bh->b_data;

	old_bg_clusters = le16_to_cpu(group->bg_bits) / cl_bpc;
	/* update the group first. */
	num_bits = new_clusters * cl_bpc;
	le16_add_cpu(&group->bg_bits, num_bits);
	le16_add_cpu(&group->bg_मुक्त_bits_count, num_bits);

	/*
	 * check whether there are some new backup superblocks exist in
	 * this group and update the group biपंचांगap accordingly.
	 */
	अगर (OCFS2_HAS_COMPAT_FEATURE(osb->sb,
				     OCFS2_FEATURE_COMPAT_BACKUP_SB)) अणु
		backups = ocfs2_calc_new_backup_super(bm_inode,
						     group,
						     cl_cpg, old_bg_clusters, 1);
		le16_add_cpu(&group->bg_मुक्त_bits_count, -1 * backups);
	पूर्ण

	ocfs2_journal_dirty(handle, group_bh);

	/* update the inode accordingly. */
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(bm_inode), bm_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_rollback;
	पूर्ण

	chain = le16_to_cpu(group->bg_chain);
	cr = (&cl->cl_recs[chain]);
	le32_add_cpu(&cr->c_total, num_bits);
	le32_add_cpu(&cr->c_मुक्त, num_bits);
	le32_add_cpu(&fe->id1.biपंचांगap1.i_total, num_bits);
	le32_add_cpu(&fe->i_clusters, new_clusters);

	अगर (backups) अणु
		le32_add_cpu(&cr->c_मुक्त, -1 * backups);
		le32_add_cpu(&fe->id1.biपंचांगap1.i_used, backups);
	पूर्ण

	spin_lock(&OCFS2_I(bm_inode)->ip_lock);
	OCFS2_I(bm_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	le64_add_cpu(&fe->i_size, (u64)new_clusters << osb->s_clustersize_bits);
	spin_unlock(&OCFS2_I(bm_inode)->ip_lock);
	i_size_ग_लिखो(bm_inode, le64_to_cpu(fe->i_size));

	ocfs2_journal_dirty(handle, bm_bh);

out_rollback:
	अगर (ret < 0) अणु
		ocfs2_calc_new_backup_super(bm_inode,
					    group,
					    cl_cpg, old_bg_clusters, 0);
		le16_add_cpu(&group->bg_मुक्त_bits_count, backups);
		le16_add_cpu(&group->bg_bits, -1 * num_bits);
		le16_add_cpu(&group->bg_मुक्त_bits_count, -1 * num_bits);
	पूर्ण
out:
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक update_backups(काष्ठा inode * inode, u32 clusters, अक्षर *data)
अणु
	पूर्णांक i, ret = 0;
	u32 cluster;
	u64 blkno;
	काष्ठा buffer_head *backup = शून्य;
	काष्ठा ocfs2_dinode *backup_di = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	/* calculate the real backups we need to update. */
	क्रम (i = 0; i < OCFS2_MAX_BACKUP_SUPERBLOCKS; i++) अणु
		blkno = ocfs2_backup_super_blkno(inode->i_sb, i);
		cluster = ocfs2_blocks_to_clusters(inode->i_sb, blkno);
		अगर (cluster >= clusters)
			अवरोध;

		ret = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &backup);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		स_नकल(backup->b_data, data, inode->i_sb->s_blocksize);

		backup_di = (काष्ठा ocfs2_dinode *)backup->b_data;
		backup_di->i_blkno = cpu_to_le64(blkno);

		ret = ocfs2_ग_लिखो_super_or_backup(osb, backup);
		brअन्यथा(backup);
		backup = शून्य;
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ocfs2_update_super_and_backups(काष्ठा inode *inode,
					   पूर्णांक new_clusters)
अणु
	पूर्णांक ret;
	u32 clusters = 0;
	काष्ठा buffer_head *super_bh = शून्य;
	काष्ठा ocfs2_dinode *super_di = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	/*
	 * update the superblock last.
	 * It करोesn't matter अगर the ग_लिखो failed.
	 */
	ret = ocfs2_पढ़ो_blocks_sync(osb, OCFS2_SUPER_BLOCK_BLKNO, 1,
				     &super_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	super_di = (काष्ठा ocfs2_dinode *)super_bh->b_data;
	le32_add_cpu(&super_di->i_clusters, new_clusters);
	clusters = le32_to_cpu(super_di->i_clusters);

	ret = ocfs2_ग_लिखो_super_or_backup(osb, super_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (OCFS2_HAS_COMPAT_FEATURE(osb->sb, OCFS2_FEATURE_COMPAT_BACKUP_SB))
		ret = update_backups(inode, clusters, super_bh->b_data);

out:
	brअन्यथा(super_bh);
	अगर (ret)
		prपूर्णांकk(KERN_WARNING "ocfs2: Failed to update super blocks on %s"
			" during fs resize. This condition is not fatal,"
			" but fsck.ocfs2 should be run to fix it\n",
			osb->dev_str);
	वापस;
पूर्ण

/*
 * Extend the fileप्रणाली to the new number of clusters specअगरied.  This entry
 * poपूर्णांक is only used to extend the current fileप्रणाली to the end of the last
 * existing group.
 */
पूर्णांक ocfs2_group_extend(काष्ठा inode * inode, पूर्णांक new_clusters)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा buffer_head *group_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode = शून्य;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_group_desc *group = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u16 cl_bpc;
	u32 first_new_cluster;
	u64 lgd_blkno;

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	अगर (new_clusters < 0)
		वापस -EINVAL;
	अन्यथा अगर (new_clusters == 0)
		वापस 0;

	मुख्य_bm_inode = ocfs2_get_प्रणाली_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	अगर (!मुख्य_bm_inode) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	inode_lock(मुख्य_bm_inode);

	ret = ocfs2_inode_lock(मुख्य_bm_inode, &मुख्य_bm_bh, 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *)मुख्य_bm_bh->b_data;

	/* मुख्य_bm_bh is validated by inode पढ़ो inside ocfs2_inode_lock(),
	 * so any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	अगर (le16_to_cpu(fe->id2.i_chain.cl_cpg) !=
		ocfs2_group_biपंचांगap_size(osb->sb, 0,
					osb->s_feature_incompat) * 8) अणु
		mlog(ML_ERROR, "The disk is too old and small. "
		     "Force to do offline resize.");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	first_new_cluster = le32_to_cpu(fe->i_clusters);
	lgd_blkno = ocfs2_which_cluster_group(मुख्य_bm_inode,
					      first_new_cluster - 1);

	ret = ocfs2_पढ़ो_group_descriptor(मुख्य_bm_inode, fe, lgd_blkno,
					  &group_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण
	group = (काष्ठा ocfs2_group_desc *)group_bh->b_data;

	cl_bpc = le16_to_cpu(fe->id2.i_chain.cl_bpc);
	अगर (le16_to_cpu(group->bg_bits) / cl_bpc + new_clusters >
		le16_to_cpu(fe->id2.i_chain.cl_cpg)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण


	trace_ocfs2_group_extend(
	     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(group->bg_blkno), new_clusters);

	handle = ocfs2_start_trans(osb, OCFS2_GROUP_EXTEND_CREDITS);
	अगर (IS_ERR(handle)) अणु
		mlog_त्रुटि_सं(PTR_ERR(handle));
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* update the last group descriptor and inode. */
	ret = ocfs2_update_last_group_and_inode(handle, मुख्य_bm_inode,
						मुख्य_bm_bh, group_bh,
						first_new_cluster,
						new_clusters);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ocfs2_update_super_and_backups(मुख्य_bm_inode, new_clusters);

out_commit:
	ocfs2_commit_trans(osb, handle);
out_unlock:
	brअन्यथा(group_bh);
	brअन्यथा(मुख्य_bm_bh);

	ocfs2_inode_unlock(मुख्य_bm_inode, 1);

out_mutex:
	inode_unlock(मुख्य_bm_inode);
	iput(मुख्य_bm_inode);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_check_new_group(काष्ठा inode *inode,
				 काष्ठा ocfs2_dinode *di,
				 काष्ठा ocfs2_new_group_input *input,
				 काष्ठा buffer_head *group_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_group_desc *gd =
		(काष्ठा ocfs2_group_desc *)group_bh->b_data;
	u16 cl_bpc = le16_to_cpu(di->id2.i_chain.cl_bpc);

	ret = ocfs2_check_group_descriptor(inode->i_sb, di, group_bh);
	अगर (ret)
		जाओ out;

	ret = -EINVAL;
	अगर (le16_to_cpu(gd->bg_chain) != input->chain)
		mlog(ML_ERROR, "Group descriptor # %llu has bad chain %u "
		     "while input has %u set.\n",
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_chain), input->chain);
	अन्यथा अगर (le16_to_cpu(gd->bg_bits) != input->clusters * cl_bpc)
		mlog(ML_ERROR, "Group descriptor # %llu has bit count %u but "
		     "input has %u clusters set\n",
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_bits), input->clusters);
	अन्यथा अगर (le16_to_cpu(gd->bg_मुक्त_bits_count) != input->मुक्तs * cl_bpc)
		mlog(ML_ERROR, "Group descriptor # %llu has free bit count %u "
		     "but it should have %u set\n",
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_bits),
		     input->मुक्तs * cl_bpc);
	अन्यथा
		ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_verअगरy_group_and_input(काष्ठा inode *inode,
					काष्ठा ocfs2_dinode *di,
					काष्ठा ocfs2_new_group_input *input,
					काष्ठा buffer_head *group_bh)
अणु
	u16 cl_count = le16_to_cpu(di->id2.i_chain.cl_count);
	u16 cl_cpg = le16_to_cpu(di->id2.i_chain.cl_cpg);
	u16 next_मुक्त = le16_to_cpu(di->id2.i_chain.cl_next_मुक्त_rec);
	u32 cluster = ocfs2_blocks_to_clusters(inode->i_sb, input->group);
	u32 total_clusters = le32_to_cpu(di->i_clusters);
	पूर्णांक ret = -EINVAL;

	अगर (cluster < total_clusters)
		mlog(ML_ERROR, "add a group which is in the current volume.\n");
	अन्यथा अगर (input->chain >= cl_count)
		mlog(ML_ERROR, "input chain exceeds the limit.\n");
	अन्यथा अगर (next_मुक्त != cl_count && next_मुक्त != input->chain)
		mlog(ML_ERROR,
		     "the add group should be in chain %u\n", next_मुक्त);
	अन्यथा अगर (total_clusters + input->clusters < total_clusters)
		mlog(ML_ERROR, "add group's clusters overflow.\n");
	अन्यथा अगर (input->clusters > cl_cpg)
		mlog(ML_ERROR, "the cluster exceeds the maximum of a group\n");
	अन्यथा अगर (input->मुक्तs > input->clusters)
		mlog(ML_ERROR, "the free cluster exceeds the total clusters\n");
	अन्यथा अगर (total_clusters % cl_cpg != 0)
		mlog(ML_ERROR,
		     "the last group isn't full. Use group extend first.\n");
	अन्यथा अगर (input->group != ocfs2_which_cluster_group(inode, cluster))
		mlog(ML_ERROR, "group blkno is invalid\n");
	अन्यथा अगर ((ret = ocfs2_check_new_group(inode, di, input, group_bh)))
		mlog(ML_ERROR, "group descriptor check failed.\n");
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

/* Add a new group descriptor to global_biपंचांगap. */
पूर्णांक ocfs2_group_add(काष्ठा inode *inode, काष्ठा ocfs2_new_group_input *input)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode = शून्य;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *group_bh = शून्य;
	काष्ठा ocfs2_group_desc *group = शून्य;
	काष्ठा ocfs2_chain_list *cl;
	काष्ठा ocfs2_chain_rec *cr;
	u16 cl_bpc;
	u64 bg_ptr;

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	मुख्य_bm_inode = ocfs2_get_प्रणाली_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	अगर (!मुख्य_bm_inode) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	inode_lock(मुख्य_bm_inode);

	ret = ocfs2_inode_lock(मुख्य_bm_inode, &मुख्य_bm_bh, 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *)मुख्य_bm_bh->b_data;

	अगर (le16_to_cpu(fe->id2.i_chain.cl_cpg) !=
		ocfs2_group_biपंचांगap_size(osb->sb, 0,
					osb->s_feature_incompat) * 8) अणु
		mlog(ML_ERROR, "The disk is too old and small."
		     " Force to do offline resize.");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_पढ़ो_blocks_sync(osb, input->group, 1, &group_bh);
	अगर (ret < 0) अणु
		mlog(ML_ERROR, "Can't read the group descriptor # %llu "
		     "from the device.", (अचिन्हित दीर्घ दीर्घ)input->group);
		जाओ out_unlock;
	पूर्ण

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), group_bh);

	ret = ocfs2_verअगरy_group_and_input(मुख्य_bm_inode, fe, input, group_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_मुक्त_group_bh;
	पूर्ण

	trace_ocfs2_group_add((अचिन्हित दीर्घ दीर्घ)input->group,
			       input->chain, input->clusters, input->मुक्तs);

	handle = ocfs2_start_trans(osb, OCFS2_GROUP_ADD_CREDITS);
	अगर (IS_ERR(handle)) अणु
		mlog_त्रुटि_सं(PTR_ERR(handle));
		ret = -EINVAL;
		जाओ out_मुक्त_group_bh;
	पूर्ण

	cl_bpc = le16_to_cpu(fe->id2.i_chain.cl_bpc);
	cl = &fe->id2.i_chain;
	cr = &cl->cl_recs[input->chain];

	ret = ocfs2_journal_access_gd(handle, INODE_CACHE(मुख्य_bm_inode),
				      group_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	group = (काष्ठा ocfs2_group_desc *)group_bh->b_data;
	bg_ptr = le64_to_cpu(group->bg_next_group);
	group->bg_next_group = cr->c_blkno;
	ocfs2_journal_dirty(handle, group_bh);

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(मुख्य_bm_inode),
				      मुख्य_bm_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		group->bg_next_group = cpu_to_le64(bg_ptr);
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	अगर (input->chain == le16_to_cpu(cl->cl_next_मुक्त_rec)) अणु
		le16_add_cpu(&cl->cl_next_मुक्त_rec, 1);
		स_रखो(cr, 0, माप(काष्ठा ocfs2_chain_rec));
	पूर्ण

	cr->c_blkno = cpu_to_le64(input->group);
	le32_add_cpu(&cr->c_total, input->clusters * cl_bpc);
	le32_add_cpu(&cr->c_मुक्त, input->मुक्तs * cl_bpc);

	le32_add_cpu(&fe->id1.biपंचांगap1.i_total, input->clusters *cl_bpc);
	le32_add_cpu(&fe->id1.biपंचांगap1.i_used,
		     (input->clusters - input->मुक्तs) * cl_bpc);
	le32_add_cpu(&fe->i_clusters, input->clusters);

	ocfs2_journal_dirty(handle, मुख्य_bm_bh);

	spin_lock(&OCFS2_I(मुख्य_bm_inode)->ip_lock);
	OCFS2_I(मुख्य_bm_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	le64_add_cpu(&fe->i_size, (u64)input->clusters << osb->s_clustersize_bits);
	spin_unlock(&OCFS2_I(मुख्य_bm_inode)->ip_lock);
	i_size_ग_लिखो(मुख्य_bm_inode, le64_to_cpu(fe->i_size));

	ocfs2_update_super_and_backups(मुख्य_bm_inode, input->clusters);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_मुक्त_group_bh:
	brअन्यथा(group_bh);

out_unlock:
	brअन्यथा(मुख्य_bm_bh);

	ocfs2_inode_unlock(मुख्य_bm_inode, 1);

out_mutex:
	inode_unlock(मुख्य_bm_inode);
	iput(मुख्य_bm_inode);

out:
	वापस ret;
पूर्ण
