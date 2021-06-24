<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * localalloc.c
 *
 * Node local data allocation
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/bitops.h>

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
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

#घोषणा OCFS2_LOCAL_ALLOC(dinode)	(&((dinode)->id2.i_lab))

अटल u32 ocfs2_local_alloc_count_bits(काष्ठा ocfs2_dinode *alloc);

अटल पूर्णांक ocfs2_local_alloc_find_clear_bits(काष्ठा ocfs2_super *osb,
					     काष्ठा ocfs2_dinode *alloc,
					     u32 *numbits,
					     काष्ठा ocfs2_alloc_reservation *resv);

अटल व्योम ocfs2_clear_local_alloc(काष्ठा ocfs2_dinode *alloc);

अटल पूर्णांक ocfs2_sync_local_to_मुख्य(काष्ठा ocfs2_super *osb,
				    handle_t *handle,
				    काष्ठा ocfs2_dinode *alloc,
				    काष्ठा inode *मुख्य_bm_inode,
				    काष्ठा buffer_head *मुख्य_bm_bh);

अटल पूर्णांक ocfs2_local_alloc_reserve_क्रम_winकरोw(काष्ठा ocfs2_super *osb,
						काष्ठा ocfs2_alloc_context **ac,
						काष्ठा inode **biपंचांगap_inode,
						काष्ठा buffer_head **biपंचांगap_bh);

अटल पूर्णांक ocfs2_local_alloc_new_winकरोw(काष्ठा ocfs2_super *osb,
					handle_t *handle,
					काष्ठा ocfs2_alloc_context *ac);

अटल पूर्णांक ocfs2_local_alloc_slide_winकरोw(काष्ठा ocfs2_super *osb,
					  काष्ठा inode *local_alloc_inode);

/*
 * ocfs2_la_शेष_mb() - determine a शेष size, in megabytes of
 * the local alloc.
 *
 * Generally, we'd like to pick as large a local alloc as
 * possible. Perक्रमmance on large workloads tends to scale
 * proportionally to la size. In addition to that, the reservations
 * code functions more efficiently as it can reserve more winकरोws क्रम
 * ग_लिखो.
 *
 * Some things work against us when trying to choose a large local alloc:
 *
 * - We need to ensure our sizing is picked to leave enough space in
 *   group descriptors क्रम other allocations (such as block groups,
 *   etc). Picking शेष sizes which are a multiple of 4 could help
 *   - block groups are allocated in 2mb and 4mb chunks.
 *
 * - Likewise, we करोn't want to starve other nodes of bits on small
 *   file प्रणालीs. This can easily be taken care of by limiting our
 *   शेष to a reasonable size (256M) on larger cluster sizes.
 *
 * - Some file प्रणालीs can't support very large sizes - 4k and 8k in
 *   particular are limited to less than 128 and 256 megabytes respectively.
 *
 * The following reference table shows group descriptor and local
 * alloc maximums at various cluster sizes (4k blocksize)
 *
 * csize: 4K	group: 126M	la: 121M
 * csize: 8K	group: 252M	la: 243M
 * csize: 16K	group: 504M	la: 486M
 * csize: 32K	group: 1008M	la: 972M
 * csize: 64K	group: 2016M	la: 1944M
 * csize: 128K	group: 4032M	la: 3888M
 * csize: 256K	group: 8064M	la: 7776M
 * csize: 512K	group: 16128M	la: 15552M
 * csize: 1024K	group: 32256M	la: 31104M
 */
#घोषणा	OCFS2_LA_MAX_DEFAULT_MB	256
#घोषणा	OCFS2_LA_OLD_DEFAULT	8
अचिन्हित पूर्णांक ocfs2_la_शेष_mb(काष्ठा ocfs2_super *osb)
अणु
	अचिन्हित पूर्णांक la_mb;
	अचिन्हित पूर्णांक gd_mb;
	अचिन्हित पूर्णांक la_max_mb;
	अचिन्हित पूर्णांक megs_per_slot;
	काष्ठा super_block *sb = osb->sb;

	gd_mb = ocfs2_clusters_to_megabytes(osb->sb,
		8 * ocfs2_group_biपंचांगap_size(sb, 0, osb->s_feature_incompat));

	/*
	 * This takes care of files प्रणालीs with very small group
	 * descriptors - 512 byte blocksize at cluster sizes lower
	 * than 16K and also 1k blocksize with 4k cluster size.
	 */
	अगर ((sb->s_blocksize == 512 && osb->s_clustersize <= 8192)
	    || (sb->s_blocksize == 1024 && osb->s_clustersize == 4096))
		वापस OCFS2_LA_OLD_DEFAULT;

	/*
	 * Leave enough room क्रम some block groups and make the final
	 * value we work from a multiple of 4.
	 */
	gd_mb -= 16;
	gd_mb &= 0xFFFFFFFB;

	la_mb = gd_mb;

	/*
	 * Keep winकरोw sizes करोwn to a reasonable शेष
	 */
	अगर (la_mb > OCFS2_LA_MAX_DEFAULT_MB) अणु
		/*
		 * Some clustersize / blocksize combinations will have
		 * given us a larger than OCFS2_LA_MAX_DEFAULT_MB
		 * शेष size, but get poor distribution when
		 * limited to exactly 256 megabytes.
		 *
		 * As an example, 16K clustersize at 4K blocksize
		 * gives us a cluster group size of 504M. Paring the
		 * local alloc size करोwn to 256 however, would give us
		 * only one winकरोw and around 200MB left in the
		 * cluster group. Instead, find the first size below
		 * 256 which would give us an even distribution.
		 *
		 * Larger cluster group sizes actually work out pretty
		 * well when pared to 256, so we करोn't have to करो this
		 * क्रम any group that fits more than two
		 * OCFS2_LA_MAX_DEFAULT_MB winकरोws.
		 */
		अगर (gd_mb > (2 * OCFS2_LA_MAX_DEFAULT_MB))
			la_mb = 256;
		अन्यथा अणु
			अचिन्हित पूर्णांक gd_mult = gd_mb;

			जबतक (gd_mult > 256)
				gd_mult = gd_mult >> 1;

			la_mb = gd_mult;
		पूर्ण
	पूर्ण

	megs_per_slot = osb->osb_clusters_at_boot / osb->max_slots;
	megs_per_slot = ocfs2_clusters_to_megabytes(osb->sb, megs_per_slot);
	/* Too many nodes, too few disk clusters. */
	अगर (megs_per_slot < la_mb)
		la_mb = megs_per_slot;

	/* We can't store more bits than we can in a block. */
	la_max_mb = ocfs2_clusters_to_megabytes(osb->sb,
						ocfs2_local_alloc_size(sb) * 8);
	अगर (la_mb > la_max_mb)
		la_mb = la_max_mb;

	वापस la_mb;
पूर्ण

व्योम ocfs2_la_set_sizes(काष्ठा ocfs2_super *osb, पूर्णांक requested_mb)
अणु
	काष्ठा super_block *sb = osb->sb;
	अचिन्हित पूर्णांक la_शेष_mb = ocfs2_la_शेष_mb(osb);
	अचिन्हित पूर्णांक la_max_mb;

	la_max_mb = ocfs2_clusters_to_megabytes(sb,
						ocfs2_local_alloc_size(sb) * 8);

	trace_ocfs2_la_set_sizes(requested_mb, la_max_mb, la_शेष_mb);

	अगर (requested_mb == -1) अणु
		/* No user request - use शेषs */
		osb->local_alloc_शेष_bits =
			ocfs2_megabytes_to_clusters(sb, la_शेष_mb);
	पूर्ण अन्यथा अगर (requested_mb > la_max_mb) अणु
		/* Request is too big, we give the maximum available */
		osb->local_alloc_शेष_bits =
			ocfs2_megabytes_to_clusters(sb, la_max_mb);
	पूर्ण अन्यथा अणु
		osb->local_alloc_शेष_bits =
			ocfs2_megabytes_to_clusters(sb, requested_mb);
	पूर्ण

	osb->local_alloc_bits = osb->local_alloc_शेष_bits;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_la_state_enabled(काष्ठा ocfs2_super *osb)
अणु
	वापस (osb->local_alloc_state == OCFS2_LA_THROTTLED ||
		osb->local_alloc_state == OCFS2_LA_ENABLED);
पूर्ण

व्योम ocfs2_local_alloc_seen_मुक्त_bits(काष्ठा ocfs2_super *osb,
				      अचिन्हित पूर्णांक num_clusters)
अणु
	spin_lock(&osb->osb_lock);
	अगर (osb->local_alloc_state == OCFS2_LA_DISABLED ||
	    osb->local_alloc_state == OCFS2_LA_THROTTLED)
		अगर (num_clusters >= osb->local_alloc_शेष_bits) अणु
			cancel_delayed_work(&osb->la_enable_wq);
			osb->local_alloc_state = OCFS2_LA_ENABLED;
		पूर्ण
	spin_unlock(&osb->osb_lock);
पूर्ण

व्योम ocfs2_la_enable_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocfs2_super *osb =
		container_of(work, काष्ठा ocfs2_super,
			     la_enable_wq.work);
	spin_lock(&osb->osb_lock);
	osb->local_alloc_state = OCFS2_LA_ENABLED;
	spin_unlock(&osb->osb_lock);
पूर्ण

/*
 * Tell us whether a given allocation should use the local alloc
 * file. Otherwise, it has to go to the मुख्य biपंचांगap.
 *
 * This function करोes semi-dirty पढ़ोs of local alloc size and state!
 * This is ok however, as the values are re-checked once under mutex.
 */
पूर्णांक ocfs2_alloc_should_use_local(काष्ठा ocfs2_super *osb, u64 bits)
अणु
	पूर्णांक ret = 0;
	पूर्णांक la_bits;

	spin_lock(&osb->osb_lock);
	la_bits = osb->local_alloc_bits;

	अगर (!ocfs2_la_state_enabled(osb))
		जाओ bail;

	/* la_bits should be at least twice the size (in clusters) of
	 * a new block group. We want to be sure block group
	 * allocations go through the local alloc, so allow an
	 * allocation to take up to half the biपंचांगap. */
	अगर (bits > (la_bits / 2))
		जाओ bail;

	ret = 1;
bail:
	trace_ocfs2_alloc_should_use_local(
	     (अचिन्हित दीर्घ दीर्घ)bits, osb->local_alloc_state, la_bits, ret);
	spin_unlock(&osb->osb_lock);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_load_local_alloc(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_dinode *alloc = शून्य;
	काष्ठा buffer_head *alloc_bh = शून्य;
	u32 num_used;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_local_alloc *la;

	अगर (osb->local_alloc_bits == 0)
		जाओ bail;

	अगर (osb->local_alloc_bits >= osb->biपंचांगap_cpg) अणु
		mlog(ML_NOTICE, "Requested local alloc window %d is larger "
		     "than max possible %u. Using defaults.\n",
		     osb->local_alloc_bits, (osb->biपंचांगap_cpg - 1));
		osb->local_alloc_bits =
			ocfs2_megabytes_to_clusters(osb->sb,
						    ocfs2_la_शेष_mb(osb));
	पूर्ण

	/* पढ़ो the alloc off disk */
	inode = ocfs2_get_प्रणाली_file_inode(osb, LOCAL_ALLOC_SYSTEM_INODE,
					    osb->slot_num);
	अगर (!inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_पढ़ो_inode_block_full(inode, &alloc_bh,
					     OCFS2_BH_IGNORE_CACHE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	alloc = (काष्ठा ocfs2_dinode *) alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	अगर (!(le32_to_cpu(alloc->i_flags) &
	    (OCFS2_LOCAL_ALLOC_FL|OCFS2_BITMAP_FL))) अणु
		mlog(ML_ERROR, "Invalid local alloc inode, %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर ((la->la_size == 0) ||
	    (le16_to_cpu(la->la_size) > ocfs2_local_alloc_size(inode->i_sb))) अणु
		mlog(ML_ERROR, "Local alloc size is invalid (la_size = %u)\n",
		     le16_to_cpu(la->la_size));
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	/* करो a little verअगरication. */
	num_used = ocfs2_local_alloc_count_bits(alloc);

	/* hopefully the local alloc has always been recovered beक्रमe
	 * we load it. */
	अगर (num_used
	    || alloc->id1.biपंचांगap1.i_used
	    || alloc->id1.biपंचांगap1.i_total
	    || la->la_bm_off) अणु
		mlog(ML_ERROR, "inconsistent detected, clean journal with"
		     " unrecovered local alloc, please run fsck.ocfs2!\n"
		     "found = %u, set = %u, taken = %u, off = %u\n",
		     num_used, le32_to_cpu(alloc->id1.biपंचांगap1.i_used),
		     le32_to_cpu(alloc->id1.biपंचांगap1.i_total),
		     OCFS2_LOCAL_ALLOC(alloc)->la_bm_off);

		status = -EINVAL;
		जाओ bail;
	पूर्ण

	osb->local_alloc_bh = alloc_bh;
	osb->local_alloc_state = OCFS2_LA_ENABLED;

bail:
	अगर (status < 0)
		brअन्यथा(alloc_bh);
	iput(inode);

	trace_ocfs2_load_local_alloc(osb->local_alloc_bits);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * वापस any unused bits to the biपंचांगap and ग_लिखो out a clean
 * local_alloc.
 *
 * local_alloc_bh is optional. If not passed, we will simply use the
 * one off osb. If you करो pass it however, be warned that it *will* be
 * वापसed brअन्यथा'd and NULL'd out.*/
व्योम ocfs2_shutकरोwn_local_alloc(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	handle_t *handle;
	काष्ठा inode *local_alloc_inode = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode = शून्य;
	काष्ठा ocfs2_dinode *alloc_copy = शून्य;
	काष्ठा ocfs2_dinode *alloc = शून्य;

	cancel_delayed_work(&osb->la_enable_wq);
	अगर (osb->ocfs2_wq)
		flush_workqueue(osb->ocfs2_wq);

	अगर (osb->local_alloc_state == OCFS2_LA_UNUSED)
		जाओ out;

	local_alloc_inode =
		ocfs2_get_प्रणाली_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    osb->slot_num);
	अगर (!local_alloc_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	osb->local_alloc_state = OCFS2_LA_DISABLED;

	ocfs2_resmap_uninit(&osb->osb_la_resmap);

	मुख्य_bm_inode = ocfs2_get_प्रणाली_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	अगर (!मुख्य_bm_inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	inode_lock(मुख्य_bm_inode);

	status = ocfs2_inode_lock(मुख्य_bm_inode, &मुख्य_bm_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_mutex;
	पूर्ण

	/* WINDOW_MOVE_CREDITS is a bit heavy... */
	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		mlog_त्रुटि_सं(PTR_ERR(handle));
		handle = शून्य;
		जाओ out_unlock;
	पूर्ण

	bh = osb->local_alloc_bh;
	alloc = (काष्ठा ocfs2_dinode *) bh->b_data;

	alloc_copy = kmemdup(alloc, bh->b_size, GFP_NOFS);
	अगर (!alloc_copy) अणु
		status = -ENOMEM;
		जाओ out_commit;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(local_alloc_inode),
					 bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	ocfs2_clear_local_alloc(alloc);
	ocfs2_journal_dirty(handle, bh);

	brअन्यथा(bh);
	osb->local_alloc_bh = शून्य;
	osb->local_alloc_state = OCFS2_LA_UNUSED;

	status = ocfs2_sync_local_to_मुख्य(osb, handle, alloc_copy,
					  मुख्य_bm_inode, मुख्य_bm_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_unlock:
	brअन्यथा(मुख्य_bm_bh);

	ocfs2_inode_unlock(मुख्य_bm_inode, 1);

out_mutex:
	inode_unlock(मुख्य_bm_inode);
	iput(मुख्य_bm_inode);

out:
	iput(local_alloc_inode);

	kमुक्त(alloc_copy);
पूर्ण

/*
 * We want to मुक्त the biपंचांगap bits outside of any recovery context as
 * we'll need a cluster lock to करो so, but we must clear the local
 * alloc beक्रमe giving up the recovered nodes journal. To solve this,
 * we kदो_स्मृति a copy of the local alloc beक्रमe it's change क्रम the
 * caller to process with ocfs2_complete_local_alloc_recovery
 */
पूर्णांक ocfs2_begin_local_alloc_recovery(काष्ठा ocfs2_super *osb,
				     पूर्णांक slot_num,
				     काष्ठा ocfs2_dinode **alloc_copy)
अणु
	पूर्णांक status = 0;
	काष्ठा buffer_head *alloc_bh = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_dinode *alloc;

	trace_ocfs2_begin_local_alloc_recovery(slot_num);

	*alloc_copy = शून्य;

	inode = ocfs2_get_प्रणाली_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    slot_num);
	अगर (!inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	inode_lock(inode);

	status = ocfs2_पढ़ो_inode_block_full(inode, &alloc_bh,
					     OCFS2_BH_IGNORE_CACHE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	*alloc_copy = kदो_स्मृति(alloc_bh->b_size, GFP_KERNEL);
	अगर (!(*alloc_copy)) अणु
		status = -ENOMEM;
		जाओ bail;
	पूर्ण
	स_नकल((*alloc_copy), alloc_bh->b_data, alloc_bh->b_size);

	alloc = (काष्ठा ocfs2_dinode *) alloc_bh->b_data;
	ocfs2_clear_local_alloc(alloc);

	ocfs2_compute_meta_ecc(osb->sb, alloc_bh->b_data, &alloc->i_check);
	status = ocfs2_ग_लिखो_block(osb, alloc_bh, INODE_CACHE(inode));
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

bail:
	अगर (status < 0) अणु
		kमुक्त(*alloc_copy);
		*alloc_copy = शून्य;
	पूर्ण

	brअन्यथा(alloc_bh);

	अगर (inode) अणु
		inode_unlock(inode);
		iput(inode);
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * Step 2: By now, we've completed the journal recovery, we've stamped
 * a clean local alloc on disk and dropped the node out of the
 * recovery map. Dlm locks will no दीर्घer stall, so lets clear out the
 * मुख्य biपंचांगap.
 */
पूर्णांक ocfs2_complete_local_alloc_recovery(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_dinode *alloc)
अणु
	पूर्णांक status;
	handle_t *handle;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode;

	मुख्य_bm_inode = ocfs2_get_प्रणाली_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	अगर (!मुख्य_bm_inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	inode_lock(मुख्य_bm_inode);

	status = ocfs2_inode_lock(मुख्य_bm_inode, &मुख्य_bm_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_mutex;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ out_unlock;
	पूर्ण

	/* we want the biपंचांगap change to be recorded on disk asap */
	handle->h_sync = 1;

	status = ocfs2_sync_local_to_मुख्य(osb, handle, alloc,
					  मुख्य_bm_inode, मुख्य_bm_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	ocfs2_commit_trans(osb, handle);

out_unlock:
	ocfs2_inode_unlock(मुख्य_bm_inode, 1);

out_mutex:
	inode_unlock(मुख्य_bm_inode);

	brअन्यथा(मुख्य_bm_bh);

	iput(मुख्य_bm_inode);

out:
	अगर (!status)
		ocfs2_init_steal_slots(osb);
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * make sure we've got at least bits_wanted contiguous bits in the
 * local alloc. You lose them when you drop i_mutex.
 *
 * We will add ourselves to the transaction passed in, but may start
 * our own in order to shअगरt winकरोws.
 */
पूर्णांक ocfs2_reserve_local_alloc_bits(काष्ठा ocfs2_super *osb,
				   u32 bits_wanted,
				   काष्ठा ocfs2_alloc_context *ac)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_dinode *alloc;
	काष्ठा inode *local_alloc_inode;
	अचिन्हित पूर्णांक मुक्त_bits;

	BUG_ON(!ac);

	local_alloc_inode =
		ocfs2_get_प्रणाली_file_inode(osb,
					    LOCAL_ALLOC_SYSTEM_INODE,
					    osb->slot_num);
	अगर (!local_alloc_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	inode_lock(local_alloc_inode);

	/*
	 * We must द्विगुन check state and allocator bits because
	 * another process may have changed them जबतक holding i_mutex.
	 */
	spin_lock(&osb->osb_lock);
	अगर (!ocfs2_la_state_enabled(osb) ||
	    (bits_wanted > osb->local_alloc_bits)) अणु
		spin_unlock(&osb->osb_lock);
		status = -ENOSPC;
		जाओ bail;
	पूर्ण
	spin_unlock(&osb->osb_lock);

	alloc = (काष्ठा ocfs2_dinode *) osb->local_alloc_bh->b_data;

#अगर_घोषित CONFIG_OCFS2_DEBUG_FS
	अगर (le32_to_cpu(alloc->id1.biपंचांगap1.i_used) !=
	    ocfs2_local_alloc_count_bits(alloc)) अणु
		status = ocfs2_error(osb->sb, "local alloc inode %llu says it has %u used bits, but a count shows %u\n",
				(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(alloc->i_blkno),
				le32_to_cpu(alloc->id1.biपंचांगap1.i_used),
				ocfs2_local_alloc_count_bits(alloc));
		जाओ bail;
	पूर्ण
#पूर्ण_अगर

	मुक्त_bits = le32_to_cpu(alloc->id1.biपंचांगap1.i_total) -
		le32_to_cpu(alloc->id1.biपंचांगap1.i_used);
	अगर (bits_wanted > मुक्त_bits) अणु
		/* uhoh, winकरोw change समय. */
		status =
			ocfs2_local_alloc_slide_winकरोw(osb, local_alloc_inode);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/*
		 * Under certain conditions, the winकरोw slide code
		 * might have reduced the number of bits available or
		 * disabled the local alloc entirely. Re-check
		 * here and वापस -ENOSPC अगर necessary.
		 */
		status = -ENOSPC;
		अगर (!ocfs2_la_state_enabled(osb))
			जाओ bail;

		मुक्त_bits = le32_to_cpu(alloc->id1.biपंचांगap1.i_total) -
			le32_to_cpu(alloc->id1.biपंचांगap1.i_used);
		अगर (bits_wanted > मुक्त_bits)
			जाओ bail;
	पूर्ण

	ac->ac_inode = local_alloc_inode;
	/* We should never use localalloc from another slot */
	ac->ac_alloc_slot = osb->slot_num;
	ac->ac_which = OCFS2_AC_USE_LOCAL;
	get_bh(osb->local_alloc_bh);
	ac->ac_bh = osb->local_alloc_bh;
	status = 0;
bail:
	अगर (status < 0 && local_alloc_inode) अणु
		inode_unlock(local_alloc_inode);
		iput(local_alloc_inode);
	पूर्ण

	trace_ocfs2_reserve_local_alloc_bits(
		(अचिन्हित दीर्घ दीर्घ)ac->ac_max_block,
		bits_wanted, osb->slot_num, status);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_claim_local_alloc_bits(काष्ठा ocfs2_super *osb,
				 handle_t *handle,
				 काष्ठा ocfs2_alloc_context *ac,
				 u32 bits_wanted,
				 u32 *bit_off,
				 u32 *num_bits)
अणु
	पूर्णांक status, start;
	काष्ठा inode *local_alloc_inode;
	व्योम *biपंचांगap;
	काष्ठा ocfs2_dinode *alloc;
	काष्ठा ocfs2_local_alloc *la;

	BUG_ON(ac->ac_which != OCFS2_AC_USE_LOCAL);

	local_alloc_inode = ac->ac_inode;
	alloc = (काष्ठा ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	start = ocfs2_local_alloc_find_clear_bits(osb, alloc, &bits_wanted,
						  ac->ac_resv);
	अगर (start == -1) अणु
		/* TODO: Shouldn't we just BUG here? */
		status = -ENOSPC;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	biपंचांगap = la->la_biपंचांगap;
	*bit_off = le32_to_cpu(la->la_bm_off) + start;
	*num_bits = bits_wanted;

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(local_alloc_inode),
					 osb->local_alloc_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_resmap_claimed_bits(&osb->osb_la_resmap, ac->ac_resv, start,
				  bits_wanted);

	जबतक(bits_wanted--)
		ocfs2_set_bit(start++, biपंचांगap);

	le32_add_cpu(&alloc->id1.biपंचांगap1.i_used, *num_bits);
	ocfs2_journal_dirty(handle, osb->local_alloc_bh);

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

पूर्णांक ocfs2_मुक्त_local_alloc_bits(काष्ठा ocfs2_super *osb,
				handle_t *handle,
				काष्ठा ocfs2_alloc_context *ac,
				u32 bit_off,
				u32 num_bits)
अणु
	पूर्णांक status, start;
	u32 clear_bits;
	काष्ठा inode *local_alloc_inode;
	व्योम *biपंचांगap;
	काष्ठा ocfs2_dinode *alloc;
	काष्ठा ocfs2_local_alloc *la;

	BUG_ON(ac->ac_which != OCFS2_AC_USE_LOCAL);

	local_alloc_inode = ac->ac_inode;
	alloc = (काष्ठा ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	biपंचांगap = la->la_biपंचांगap;
	start = bit_off - le32_to_cpu(la->la_bm_off);
	clear_bits = num_bits;

	status = ocfs2_journal_access_di(handle,
			INODE_CACHE(local_alloc_inode),
			osb->local_alloc_bh,
			OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	जबतक (clear_bits--)
		ocfs2_clear_bit(start++, biपंचांगap);

	le32_add_cpu(&alloc->id1.biपंचांगap1.i_used, -num_bits);
	ocfs2_journal_dirty(handle, osb->local_alloc_bh);

bail:
	वापस status;
पूर्ण

अटल u32 ocfs2_local_alloc_count_bits(काष्ठा ocfs2_dinode *alloc)
अणु
	u32 count;
	काष्ठा ocfs2_local_alloc *la = OCFS2_LOCAL_ALLOC(alloc);

	count = memweight(la->la_biपंचांगap, le16_to_cpu(la->la_size));

	trace_ocfs2_local_alloc_count_bits(count);
	वापस count;
पूर्ण

अटल पूर्णांक ocfs2_local_alloc_find_clear_bits(काष्ठा ocfs2_super *osb,
				     काष्ठा ocfs2_dinode *alloc,
				     u32 *numbits,
				     काष्ठा ocfs2_alloc_reservation *resv)
अणु
	पूर्णांक numfound = 0, bitoff, left, startoff;
	पूर्णांक local_resv = 0;
	काष्ठा ocfs2_alloc_reservation r;
	व्योम *biपंचांगap = शून्य;
	काष्ठा ocfs2_reservation_map *resmap = &osb->osb_la_resmap;

	अगर (!alloc->id1.biपंचांगap1.i_total) अणु
		bitoff = -1;
		जाओ bail;
	पूर्ण

	अगर (!resv) अणु
		local_resv = 1;
		ocfs2_resv_init_once(&r);
		ocfs2_resv_set_type(&r, OCFS2_RESV_FLAG_TMP);
		resv = &r;
	पूर्ण

	numfound = *numbits;
	अगर (ocfs2_resmap_resv_bits(resmap, resv, &bitoff, &numfound) == 0) अणु
		अगर (numfound < *numbits)
			*numbits = numfound;
		जाओ bail;
	पूर्ण

	/*
	 * Code error. While reservations are enabled, local
	 * allocation should _always_ go through them.
	 */
	BUG_ON(osb->osb_resv_level != 0);

	/*
	 * Reservations are disabled. Handle this the old way.
	 */

	biपंचांगap = OCFS2_LOCAL_ALLOC(alloc)->la_biपंचांगap;

	numfound = bitoff = startoff = 0;
	left = le32_to_cpu(alloc->id1.biपंचांगap1.i_total);
	जबतक ((bitoff = ocfs2_find_next_zero_bit(biपंचांगap, left, startoff)) != -1) अणु
		अगर (bitoff == left) अणु
			/* mlog(0, "bitoff (%d) == left", bitoff); */
			अवरोध;
		पूर्ण
		/* mlog(0, "Found a zero: bitoff = %d, startoff = %d, "
		   "numfound = %d\n", bitoff, startoff, numfound);*/

		/* Ok, we found a zero bit... is it contig. or करो we
		 * start over?*/
		अगर (bitoff == startoff) अणु
			/* we found a zero */
			numfound++;
			startoff++;
		पूर्ण अन्यथा अणु
			/* got a zero after some ones */
			numfound = 1;
			startoff = bitoff+1;
		पूर्ण
		/* we got everything we needed */
		अगर (numfound == *numbits) अणु
			/* mlog(0, "Found it all!\n"); */
			अवरोध;
		पूर्ण
	पूर्ण

	trace_ocfs2_local_alloc_find_clear_bits_search_biपंचांगap(bitoff, numfound);

	अगर (numfound == *numbits)
		bitoff = startoff - numfound;
	अन्यथा
		bitoff = -1;

bail:
	अगर (local_resv)
		ocfs2_resv_discard(resmap, resv);

	trace_ocfs2_local_alloc_find_clear_bits(*numbits,
		le32_to_cpu(alloc->id1.biपंचांगap1.i_total),
		bitoff, numfound);

	वापस bitoff;
पूर्ण

अटल व्योम ocfs2_clear_local_alloc(काष्ठा ocfs2_dinode *alloc)
अणु
	काष्ठा ocfs2_local_alloc *la = OCFS2_LOCAL_ALLOC(alloc);
	पूर्णांक i;

	alloc->id1.biपंचांगap1.i_total = 0;
	alloc->id1.biपंचांगap1.i_used = 0;
	la->la_bm_off = 0;
	क्रम(i = 0; i < le16_to_cpu(la->la_size); i++)
		la->la_biपंचांगap[i] = 0;
पूर्ण

#अगर 0
/* turn this on and uncomment below to aid debugging winकरोw shअगरts. */
अटल व्योम ocfs2_verअगरy_zero_bits(अचिन्हित दीर्घ *biपंचांगap,
				   अचिन्हित पूर्णांक start,
				   अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक पंचांगp = count;
	जबतक(पंचांगp--) अणु
		अगर (ocfs2_test_bit(start + पंचांगp, biपंचांगap)) अणु
			prपूर्णांकk("ocfs2_verify_zero_bits: start = %u, count = "
			       "%u\n", start, count);
			prपूर्णांकk("ocfs2_verify_zero_bits: bit %u is set!",
			       start + पंचांगp);
			BUG();
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * sync the local alloc to मुख्य biपंचांगap.
 *
 * assumes you've alपढ़ोy locked the मुख्य biपंचांगap -- the biपंचांगap inode
 * passed is used क्रम caching.
 */
अटल पूर्णांक ocfs2_sync_local_to_मुख्य(काष्ठा ocfs2_super *osb,
				    handle_t *handle,
				    काष्ठा ocfs2_dinode *alloc,
				    काष्ठा inode *मुख्य_bm_inode,
				    काष्ठा buffer_head *मुख्य_bm_bh)
अणु
	पूर्णांक status = 0;
	पूर्णांक bit_off, left, count, start;
	u64 la_start_blk;
	u64 blkno;
	व्योम *biपंचांगap;
	काष्ठा ocfs2_local_alloc *la = OCFS2_LOCAL_ALLOC(alloc);

	trace_ocfs2_sync_local_to_मुख्य(
	     le32_to_cpu(alloc->id1.biपंचांगap1.i_total),
	     le32_to_cpu(alloc->id1.biपंचांगap1.i_used));

	अगर (!alloc->id1.biपंचांगap1.i_total) अणु
		जाओ bail;
	पूर्ण

	अगर (le32_to_cpu(alloc->id1.biपंचांगap1.i_used) ==
	    le32_to_cpu(alloc->id1.biपंचांगap1.i_total)) अणु
		जाओ bail;
	पूर्ण

	la_start_blk = ocfs2_clusters_to_blocks(osb->sb,
						le32_to_cpu(la->la_bm_off));
	biपंचांगap = la->la_biपंचांगap;
	start = count = bit_off = 0;
	left = le32_to_cpu(alloc->id1.biपंचांगap1.i_total);

	जबतक ((bit_off = ocfs2_find_next_zero_bit(biपंचांगap, left, start))
	       != -1) अणु
		अगर ((bit_off < left) && (bit_off == start)) अणु
			count++;
			start++;
			जारी;
		पूर्ण
		अगर (count) अणु
			blkno = la_start_blk +
				ocfs2_clusters_to_blocks(osb->sb,
							 start - count);

			trace_ocfs2_sync_local_to_मुख्य_मुक्त(
			     count, start - count,
			     (अचिन्हित दीर्घ दीर्घ)la_start_blk,
			     (अचिन्हित दीर्घ दीर्घ)blkno);

			status = ocfs2_release_clusters(handle,
							मुख्य_bm_inode,
							मुख्य_bm_bh, blkno,
							count);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
		पूर्ण
		अगर (bit_off >= left)
			अवरोध;
		count = 1;
		start = bit_off + 1;
	पूर्ण

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

क्रमागत ocfs2_la_event अणु
	OCFS2_LA_EVENT_SLIDE,		/* Normal winकरोw slide. */
	OCFS2_LA_EVENT_FRAGMENTED,	/* The global biपंचांगap has
					 * enough bits theoretically
					 * मुक्त, but a contiguous
					 * allocation could not be
					 * found. */
	OCFS2_LA_EVENT_ENOSPC,		/* Global biपंचांगap करोesn't have
					 * enough bits मुक्त to satisfy
					 * our request. */
पूर्ण;
#घोषणा OCFS2_LA_ENABLE_INTERVAL (30 * HZ)
/*
 * Given an event, calculate the size of our next local alloc winकरोw.
 *
 * This should always be called under i_mutex of the local alloc inode
 * so that local alloc disabling करोesn't race with processes trying to
 * use the allocator.
 *
 * Returns the state which the local alloc was left in. This value can
 * be ignored by some paths.
 */
अटल पूर्णांक ocfs2_recalc_la_winकरोw(काष्ठा ocfs2_super *osb,
				  क्रमागत ocfs2_la_event event)
अणु
	अचिन्हित पूर्णांक bits;
	पूर्णांक state;

	spin_lock(&osb->osb_lock);
	अगर (osb->local_alloc_state == OCFS2_LA_DISABLED) अणु
		WARN_ON_ONCE(osb->local_alloc_state == OCFS2_LA_DISABLED);
		जाओ out_unlock;
	पूर्ण

	/*
	 * ENOSPC and fragmentation are treated similarly क्रम now.
	 */
	अगर (event == OCFS2_LA_EVENT_ENOSPC ||
	    event == OCFS2_LA_EVENT_FRAGMENTED) अणु
		/*
		 * We ran out of contiguous space in the primary
		 * biपंचांगap. Drastically reduce the number of bits used
		 * by local alloc until we have to disable it.
		 */
		bits = osb->local_alloc_bits >> 1;
		अगर (bits > ocfs2_megabytes_to_clusters(osb->sb, 1)) अणु
			/*
			 * By setting state to THROTTLED, we'll keep
			 * the number of local alloc bits used करोwn
			 * until an event occurs which would give us
			 * reason to assume the biपंचांगap situation might
			 * have changed.
			 */
			osb->local_alloc_state = OCFS2_LA_THROTTLED;
			osb->local_alloc_bits = bits;
		पूर्ण अन्यथा अणु
			osb->local_alloc_state = OCFS2_LA_DISABLED;
		पूर्ण
		queue_delayed_work(osb->ocfs2_wq, &osb->la_enable_wq,
				   OCFS2_LA_ENABLE_INTERVAL);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Don't increase the size of the local alloc winकरोw until we
	 * know we might be able to fulfill the request. Otherwise, we
	 * risk bouncing around the global biपंचांगap during periods of
	 * low space.
	 */
	अगर (osb->local_alloc_state != OCFS2_LA_THROTTLED)
		osb->local_alloc_bits = osb->local_alloc_शेष_bits;

out_unlock:
	state = osb->local_alloc_state;
	spin_unlock(&osb->osb_lock);

	वापस state;
पूर्ण

अटल पूर्णांक ocfs2_local_alloc_reserve_क्रम_winकरोw(काष्ठा ocfs2_super *osb,
						काष्ठा ocfs2_alloc_context **ac,
						काष्ठा inode **biपंचांगap_inode,
						काष्ठा buffer_head **biपंचांगap_bh)
अणु
	पूर्णांक status;

	*ac = kzalloc(माप(काष्ठा ocfs2_alloc_context), GFP_KERNEL);
	अगर (!(*ac)) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

retry_enospc:
	(*ac)->ac_bits_wanted = osb->local_alloc_bits;
	status = ocfs2_reserve_cluster_biपंचांगap_bits(osb, *ac);
	अगर (status == -ENOSPC) अणु
		अगर (ocfs2_recalc_la_winकरोw(osb, OCFS2_LA_EVENT_ENOSPC) ==
		    OCFS2_LA_DISABLED)
			जाओ bail;

		ocfs2_मुक्त_ac_resource(*ac);
		स_रखो(*ac, 0, माप(काष्ठा ocfs2_alloc_context));
		जाओ retry_enospc;
	पूर्ण
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	*biपंचांगap_inode = (*ac)->ac_inode;
	igrab(*biपंचांगap_inode);
	*biपंचांगap_bh = (*ac)->ac_bh;
	get_bh(*biपंचांगap_bh);
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

/*
 * pass it the biपंचांगap lock in lock_bh अगर you have it.
 */
अटल पूर्णांक ocfs2_local_alloc_new_winकरोw(काष्ठा ocfs2_super *osb,
					handle_t *handle,
					काष्ठा ocfs2_alloc_context *ac)
अणु
	पूर्णांक status = 0;
	u32 cluster_off, cluster_count;
	काष्ठा ocfs2_dinode *alloc = शून्य;
	काष्ठा ocfs2_local_alloc *la;

	alloc = (काष्ठा ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	trace_ocfs2_local_alloc_new_winकरोw(
		le32_to_cpu(alloc->id1.biपंचांगap1.i_total),
		osb->local_alloc_bits);

	/* Inकाष्ठा the allocation code to try the most recently used
	 * cluster group. We'll re-record the group used this pass
	 * below. */
	ac->ac_last_group = osb->la_last_gd;

	/* we used the generic suballoc reserve function, but we set
	 * everything up nicely, so there's no reason why we can't use
	 * the more specअगरic cluster api to claim bits. */
	status = ocfs2_claim_clusters(handle, ac, osb->local_alloc_bits,
				      &cluster_off, &cluster_count);
	अगर (status == -ENOSPC) अणु
retry_enospc:
		/*
		 * Note: We could also try syncing the journal here to
		 * allow use of any मुक्त bits which the current
		 * transaction can't give us access to. --Mark
		 */
		अगर (ocfs2_recalc_la_winकरोw(osb, OCFS2_LA_EVENT_FRAGMENTED) ==
		    OCFS2_LA_DISABLED)
			जाओ bail;

		ac->ac_bits_wanted = osb->local_alloc_bits;
		status = ocfs2_claim_clusters(handle, ac,
					      osb->local_alloc_bits,
					      &cluster_off,
					      &cluster_count);
		अगर (status == -ENOSPC)
			जाओ retry_enospc;
		/*
		 * We only shrunk the *minimum* number of in our
		 * request - it's entirely possible that the allocator
		 * might give us more than we asked क्रम.
		 */
		अगर (status == 0) अणु
			spin_lock(&osb->osb_lock);
			osb->local_alloc_bits = cluster_count;
			spin_unlock(&osb->osb_lock);
		पूर्ण
	पूर्ण
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb->la_last_gd = ac->ac_last_group;

	la->la_bm_off = cpu_to_le32(cluster_off);
	alloc->id1.biपंचांगap1.i_total = cpu_to_le32(cluster_count);
	/* just in हाल... In the future when we find space ourselves,
	 * we करोn't have to get all contiguous -- but we'll have to
	 * set all previously used bits in biपंचांगap and update
	 * la_bits_set beक्रमe setting the bits in the मुख्य biपंचांगap. */
	alloc->id1.biपंचांगap1.i_used = 0;
	स_रखो(OCFS2_LOCAL_ALLOC(alloc)->la_biपंचांगap, 0,
	       le16_to_cpu(la->la_size));

	ocfs2_resmap_restart(&osb->osb_la_resmap, cluster_count,
			     OCFS2_LOCAL_ALLOC(alloc)->la_biपंचांगap);

	trace_ocfs2_local_alloc_new_winकरोw_result(
		OCFS2_LOCAL_ALLOC(alloc)->la_bm_off,
		le32_to_cpu(alloc->id1.biपंचांगap1.i_total));

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* Note that we करो *NOT* lock the local alloc inode here as
 * it's been locked alपढ़ोy क्रम us. */
अटल पूर्णांक ocfs2_local_alloc_slide_winकरोw(काष्ठा ocfs2_super *osb,
					  काष्ठा inode *local_alloc_inode)
अणु
	पूर्णांक status = 0;
	काष्ठा buffer_head *मुख्य_bm_bh = शून्य;
	काष्ठा inode *मुख्य_bm_inode = शून्य;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dinode *alloc;
	काष्ठा ocfs2_dinode *alloc_copy = शून्य;
	काष्ठा ocfs2_alloc_context *ac = शून्य;

	ocfs2_recalc_la_winकरोw(osb, OCFS2_LA_EVENT_SLIDE);

	/* This will lock the मुख्य biपंचांगap क्रम us. */
	status = ocfs2_local_alloc_reserve_क्रम_winकरोw(osb,
						      &ac,
						      &मुख्य_bm_inode,
						      &मुख्य_bm_bh);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	alloc = (काष्ठा ocfs2_dinode *) osb->local_alloc_bh->b_data;

	/* We want to clear the local alloc beक्रमe करोing anything
	 * अन्यथा, so that अगर we error later during this operation,
	 * local alloc shutकरोwn won't try to द्विगुन मुक्त मुख्य biपंचांगap
	 * bits. Make a copy so the sync function knows which bits to
	 * मुक्त. */
	alloc_copy = kmemdup(alloc, osb->local_alloc_bh->b_size, GFP_NOFS);
	अगर (!alloc_copy) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(local_alloc_inode),
					 osb->local_alloc_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_clear_local_alloc(alloc);
	ocfs2_journal_dirty(handle, osb->local_alloc_bh);

	status = ocfs2_sync_local_to_मुख्य(osb, handle, alloc_copy,
					  मुख्य_bm_inode, मुख्य_bm_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_local_alloc_new_winकरोw(osb, handle, ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	atomic_inc(&osb->alloc_stats.moves);

bail:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	brअन्यथा(मुख्य_bm_bh);

	iput(मुख्य_bm_inode);
	kमुक्त(alloc_copy);

	अगर (ac)
		ocfs2_मुक्त_alloc_context(ac);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

