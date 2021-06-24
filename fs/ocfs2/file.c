<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * file.c
 *
 * File खोलो, बंद, extend, truncate
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/splice.h>
#समावेश <linux/mount.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "aops.h"
#समावेश "dir.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "sysfile.h"
#समावेश "inode.h"
#समावेश "ioctl.h"
#समावेश "journal.h"
#समावेश "locks.h"
#समावेश "mmap.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "quota.h"
#समावेश "refcounttree.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

अटल पूर्णांक ocfs2_init_file_निजी(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_file_निजी *fp;

	fp = kzalloc(माप(काष्ठा ocfs2_file_निजी), GFP_KERNEL);
	अगर (!fp)
		वापस -ENOMEM;

	fp->fp_file = file;
	mutex_init(&fp->fp_mutex);
	ocfs2_file_lock_res_init(&fp->fp_flock, fp);
	file->निजी_data = fp;

	वापस 0;
पूर्ण

अटल व्योम ocfs2_मुक्त_file_निजी(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_file_निजी *fp = file->निजी_data;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (fp) अणु
		ocfs2_simple_drop_lockres(osb, &fp->fp_flock);
		ocfs2_lock_res_मुक्त(&fp->fp_flock);
		kमुक्त(fp);
		file->निजी_data = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक status;
	पूर्णांक mode = file->f_flags;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	trace_ocfs2_file_खोलो(inode, file, file->f_path.dentry,
			      (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
			      file->f_path.dentry->d_name.len,
			      file->f_path.dentry->d_name.name, mode);

	अगर (file->f_mode & FMODE_WRITE) अणु
		status = dquot_initialize(inode);
		अगर (status)
			जाओ leave;
	पूर्ण

	spin_lock(&oi->ip_lock);

	/* Check that the inode hasn't been wiped from disk by another
	 * node. If it hasn't then we're safe as दीर्घ as we hold the
	 * spin lock until our increment of खोलो count. */
	अगर (oi->ip_flags & OCFS2_INODE_DELETED) अणु
		spin_unlock(&oi->ip_lock);

		status = -ENOENT;
		जाओ leave;
	पूर्ण

	अगर (mode & O_सूचीECT)
		oi->ip_flags |= OCFS2_INODE_OPEN_सूचीECT;

	oi->ip_खोलो_count++;
	spin_unlock(&oi->ip_lock);

	status = ocfs2_init_file_निजी(inode, file);
	अगर (status) अणु
		/*
		 * We want to set खोलो count back अगर we're failing the
		 * खोलो.
		 */
		spin_lock(&oi->ip_lock);
		oi->ip_खोलो_count--;
		spin_unlock(&oi->ip_lock);
	पूर्ण

	file->f_mode |= FMODE_NOWAIT;

leave:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	spin_lock(&oi->ip_lock);
	अगर (!--oi->ip_खोलो_count)
		oi->ip_flags &= ~OCFS2_INODE_OPEN_सूचीECT;

	trace_ocfs2_file_release(inode, file, file->f_path.dentry,
				 oi->ip_blkno,
				 file->f_path.dentry->d_name.len,
				 file->f_path.dentry->d_name.name,
				 oi->ip_खोलो_count);
	spin_unlock(&oi->ip_lock);

	ocfs2_मुक्त_file_निजी(inode, file);

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस ocfs2_init_file_निजी(inode, file);
पूर्ण

अटल पूर्णांक ocfs2_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	ocfs2_मुक्त_file_निजी(inode, file);
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_sync_file(काष्ठा file *file, loff_t start, loff_t end,
			   पूर्णांक datasync)
अणु
	पूर्णांक err = 0;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	journal_t *journal = osb->journal->j_journal;
	पूर्णांक ret;
	tid_t commit_tid;
	bool needs_barrier = false;

	trace_ocfs2_sync_file(inode, file, file->f_path.dentry,
			      oi->ip_blkno,
			      file->f_path.dentry->d_name.len,
			      file->f_path.dentry->d_name.name,
			      (अचिन्हित दीर्घ दीर्घ)datasync);

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	err = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (err)
		वापस err;

	commit_tid = datasync ? oi->i_datasync_tid : oi->i_sync_tid;
	अगर (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_trans_will_send_data_barrier(journal, commit_tid))
		needs_barrier = true;
	err = jbd2_complete_transaction(journal, commit_tid);
	अगर (needs_barrier) अणु
		ret = blkdev_issue_flush(inode->i_sb->s_bdev);
		अगर (!err)
			err = ret;
	पूर्ण

	अगर (err)
		mlog_त्रुटि_सं(err);

	वापस (err < 0) ? -EIO : 0;
पूर्ण

पूर्णांक ocfs2_should_update_aसमय(काष्ठा inode *inode,
			      काष्ठा vfsmount *vfsmnt)
अणु
	काष्ठा बारpec64 now;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस 0;

	अगर ((inode->i_flags & S_NOATIME) ||
	    ((inode->i_sb->s_flags & SB_NOसूचीATIME) && S_ISसूची(inode->i_mode)))
		वापस 0;

	/*
	 * We can be called with no vfsmnt काष्ठाure - NFSD will
	 * someबार करो this.
	 *
	 * Note that our action here is dअगरferent than touch_aसमय() -
	 * अगर we can't tell whether this is a noaसमय mount, then we
	 * करोn't know whether to trust the value of s_aसमय_quantum.
	 */
	अगर (vfsmnt == शून्य)
		वापस 0;

	अगर ((vfsmnt->mnt_flags & MNT_NOATIME) ||
	    ((vfsmnt->mnt_flags & MNT_NOसूचीATIME) && S_ISसूची(inode->i_mode)))
		वापस 0;

	अगर (vfsmnt->mnt_flags & MNT_RELATIME) अणु
		अगर ((बारpec64_compare(&inode->i_aसमय, &inode->i_mसमय) <= 0) ||
		    (बारpec64_compare(&inode->i_aसमय, &inode->i_स_समय) <= 0))
			वापस 1;

		वापस 0;
	पूर्ण

	now = current_समय(inode);
	अगर ((now.tv_sec - inode->i_aसमय.tv_sec <= osb->s_aसमय_quantum))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

पूर्णांक ocfs2_update_inode_aसमय(काष्ठा inode *inode,
			     काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) bh->b_data;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * Don't use ocfs2_mark_inode_dirty() here as we don't always
	 * have i_mutex to guard against concurrent changes to other
	 * inode fields.
	 */
	inode->i_aसमय = current_समय(inode);
	di->i_aसमय = cpu_to_le64(inode->i_aसमय.tv_sec);
	di->i_aसमय_nsec = cpu_to_le32(inode->i_aसमय.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);
	ocfs2_journal_dirty(handle, bh);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_set_inode_size(handle_t *handle,
				काष्ठा inode *inode,
				काष्ठा buffer_head *fe_bh,
				u64 new_i_size)
अणु
	पूर्णांक status;

	i_size_ग_लिखो(inode, new_i_size);
	inode->i_blocks = ocfs2_inode_sector_count(inode);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);

	status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

bail:
	वापस status;
पूर्ण

पूर्णांक ocfs2_simple_size_update(काष्ठा inode *inode,
			     काष्ठा buffer_head *di_bh,
			     u64 new_i_size)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle = शून्य;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_set_inode_size(handle, inode, di_bh,
				   new_i_size);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	ocfs2_update_inode_fsync_trans(handle, inode, 0);
	ocfs2_commit_trans(osb, handle);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_cow_file_pos(काष्ठा inode *inode,
			      काष्ठा buffer_head *fe_bh,
			      u64 offset)
अणु
	पूर्णांक status;
	u32 phys, cpos = offset >> OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	अचिन्हित पूर्णांक num_clusters = 0;
	अचिन्हित पूर्णांक ext_flags = 0;

	/*
	 * If the new offset is aligned to the range of the cluster, there is
	 * no space क्रम ocfs2_zero_range_क्रम_truncate to fill, so no need to
	 * CoW either.
	 */
	अगर ((offset & (OCFS2_SB(inode->i_sb)->s_clustersize - 1)) == 0)
		वापस 0;

	status = ocfs2_get_clusters(inode, cpos, &phys,
				    &num_clusters, &ext_flags);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	अगर (!(ext_flags & OCFS2_EXT_REFCOUNTED))
		जाओ out;

	वापस ocfs2_refcount_cow(inode, fe_bh, cpos, 1, cpos+1);

out:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_orphan_क्रम_truncate(काष्ठा ocfs2_super *osb,
				     काष्ठा inode *inode,
				     काष्ठा buffer_head *fe_bh,
				     u64 new_i_size)
अणु
	पूर्णांक status;
	handle_t *handle;
	काष्ठा ocfs2_dinode *di;
	u64 cluster_bytes;

	/*
	 * We need to CoW the cluster contains the offset अगर it is reflinked
	 * since we will call ocfs2_zero_range_क्रम_truncate later which will
	 * ग_लिखो "0" from offset to the end of the cluster.
	 */
	status = ocfs2_cow_file_pos(inode, fe_bh, new_i_size);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	/* TODO: This needs to actually orphan the inode in this
	 * transaction. */

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	/*
	 * Do this beक्रमe setting i_size.
	 */
	cluster_bytes = ocfs2_align_bytes_to_clusters(inode->i_sb, new_i_size);
	status = ocfs2_zero_range_क्रम_truncate(inode, handle, new_i_size,
					       cluster_bytes);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	i_size_ग_लिखो(inode, new_i_size);
	inode->i_स_समय = inode->i_mसमय = current_समय(inode);

	di = (काष्ठा ocfs2_dinode *) fe_bh->b_data;
	di->i_size = cpu_to_le64(new_i_size);
	di->i_स_समय = di->i_mसमय = cpu_to_le64(inode->i_स_समय.tv_sec);
	di->i_स_समय_nsec = di->i_mसमय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, fe_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	वापस status;
पूर्ण

पूर्णांक ocfs2_truncate_file(काष्ठा inode *inode,
			       काष्ठा buffer_head *di_bh,
			       u64 new_i_size)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	/* We trust di_bh because it comes from ocfs2_inode_lock(), which
	 * alपढ़ोy validated it */
	fe = (काष्ठा ocfs2_dinode *) di_bh->b_data;

	trace_ocfs2_truncate_file((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_size),
				  (अचिन्हित दीर्घ दीर्घ)new_i_size);

	mlog_bug_on_msg(le64_to_cpu(fe->i_size) != i_size_पढ़ो(inode),
			"Inode %llu, inode i_size = %lld != di "
			"i_size = %llu, i_flags = 0x%x\n",
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			i_size_पढ़ो(inode),
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_size),
			le32_to_cpu(fe->i_flags));

	अगर (new_i_size > le64_to_cpu(fe->i_size)) अणु
		trace_ocfs2_truncate_file_error(
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_size),
			(अचिन्हित दीर्घ दीर्घ)new_i_size);
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	ocfs2_resv_discard(&osb->osb_la_resmap,
			   &OCFS2_I(inode)->ip_la_data_resv);

	/*
	 * The inode lock क्रमced other nodes to sync and drop their
	 * pages, which (correctly) happens even अगर we have a truncate
	 * without allocation change - ocfs2 cluster sizes can be much
	 * greater than page size, so we have to truncate them
	 * anyway.
	 */
	unmap_mapping_range(inode->i_mapping, new_i_size + PAGE_SIZE - 1, 0, 1);
	truncate_inode_pages(inode->i_mapping, new_i_size);

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		status = ocfs2_truncate_अंतरभूत(inode, di_bh, new_i_size,
					       i_size_पढ़ो(inode), 1);
		अगर (status)
			mlog_त्रुटि_सं(status);

		जाओ bail_unlock_sem;
	पूर्ण

	/* alright, we're going to need to करो a full blown alloc size
	 * change. Orphan the inode so that recovery can complete the
	 * truncate अगर necessary. This करोes the task of marking
	 * i_size. */
	status = ocfs2_orphan_क्रम_truncate(osb, inode, di_bh, new_i_size);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_sem;
	पूर्ण

	status = ocfs2_commit_truncate(osb, inode, di_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_sem;
	पूर्ण

	/* TODO: orphan dir cleanup here. */
bail_unlock_sem:
	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

bail:
	अगर (!status && OCFS2_I(inode)->ip_clusters == 0)
		status = ocfs2_try_हटाओ_refcount_tree(inode, di_bh);

	वापस status;
पूर्ण

/*
 * extend file allocation only here.
 * we'll update all the disk stuff, and oip->alloc_size
 *
 * expect stuff to be locked, a transaction started and enough data /
 * metadata reservations in the contexts.
 *
 * Will वापस -EAGAIN, and a reason अगर a restart is needed.
 * If passed in, *reason will always be set, even in error.
 */
पूर्णांक ocfs2_add_inode_data(काष्ठा ocfs2_super *osb,
			 काष्ठा inode *inode,
			 u32 *logical_offset,
			 u32 clusters_to_add,
			 पूर्णांक mark_unwritten,
			 काष्ठा buffer_head *fe_bh,
			 handle_t *handle,
			 काष्ठा ocfs2_alloc_context *data_ac,
			 काष्ठा ocfs2_alloc_context *meta_ac,
			 क्रमागत ocfs2_alloc_restarted *reason_ret)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_extent_tree et;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), fe_bh);
	ret = ocfs2_add_clusters_in_btree(handle, &et, logical_offset,
					  clusters_to_add, mark_unwritten,
					  data_ac, meta_ac, reason_ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_extend_allocation(काष्ठा inode *inode, u32 logical_start,
				   u32 clusters_to_add, पूर्णांक mark_unwritten)
अणु
	पूर्णांक status = 0;
	पूर्णांक restart_func = 0;
	पूर्णांक credits;
	u32 prev_clusters;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_dinode *fe = शून्य;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	क्रमागत ocfs2_alloc_restarted why = RESTART_NONE;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_extent_tree et;
	पूर्णांक did_quota = 0;

	/*
	 * Unwritten extent only exists क्रम file प्रणालीs which
	 * support holes.
	 */
	BUG_ON(mark_unwritten && !ocfs2_sparse_alloc(osb));

	status = ocfs2_पढ़ो_inode_block(inode, &bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण
	fe = (काष्ठा ocfs2_dinode *) bh->b_data;

restart_all:
	BUG_ON(le32_to_cpu(fe->i_clusters) != OCFS2_I(inode)->ip_clusters);

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), bh);
	status = ocfs2_lock_allocators(inode, &et, clusters_to_add, 0,
				       &data_ac, &meta_ac);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	credits = ocfs2_calc_extend_credits(osb->sb, &fe->id2.i_list);
	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

restarted_transaction:
	trace_ocfs2_extend_allocation(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		(अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode),
		le32_to_cpu(fe->i_clusters), clusters_to_add,
		why, restart_func);

	status = dquot_alloc_space_nodirty(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	अगर (status)
		जाओ leave;
	did_quota = 1;

	/* reserve a ग_लिखो to the file entry early on - that we अगर we
	 * run out of credits in the allocation path, we can still
	 * update i_size. */
	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	prev_clusters = OCFS2_I(inode)->ip_clusters;

	status = ocfs2_add_inode_data(osb,
				      inode,
				      &logical_start,
				      clusters_to_add,
				      mark_unwritten,
				      bh,
				      handle,
				      data_ac,
				      meta_ac,
				      &why);
	अगर ((status < 0) && (status != -EAGAIN)) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण
	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_journal_dirty(handle, bh);

	spin_lock(&OCFS2_I(inode)->ip_lock);
	clusters_to_add -= (OCFS2_I(inode)->ip_clusters - prev_clusters);
	spin_unlock(&OCFS2_I(inode)->ip_lock);
	/* Release unused quota reservation */
	dquot_मुक्त_space(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	did_quota = 0;

	अगर (why != RESTART_NONE && clusters_to_add) अणु
		अगर (why == RESTART_META) अणु
			restart_func = 1;
			status = 0;
		पूर्ण अन्यथा अणु
			BUG_ON(why != RESTART_TRANS);

			status = ocfs2_allocate_extend_trans(handle, 1);
			अगर (status < 0) अणु
				/* handle still has to be committed at
				 * this poपूर्णांक. */
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				जाओ leave;
			पूर्ण
			जाओ restarted_transaction;
		पूर्ण
	पूर्ण

	trace_ocfs2_extend_allocation_end(OCFS2_I(inode)->ip_blkno,
	     le32_to_cpu(fe->i_clusters),
	     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_size),
	     OCFS2_I(inode)->ip_clusters,
	     (अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode));

leave:
	अगर (status < 0 && did_quota)
		dquot_मुक्त_space(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	अगर (handle) अणु
		ocfs2_commit_trans(osb, handle);
		handle = शून्य;
	पूर्ण
	अगर (data_ac) अणु
		ocfs2_मुक्त_alloc_context(data_ac);
		data_ac = शून्य;
	पूर्ण
	अगर (meta_ac) अणु
		ocfs2_मुक्त_alloc_context(meta_ac);
		meta_ac = शून्य;
	पूर्ण
	अगर ((!status) && restart_func) अणु
		restart_func = 0;
		जाओ restart_all;
	पूर्ण
	brअन्यथा(bh);
	bh = शून्य;

	वापस status;
पूर्ण

/*
 * While a ग_लिखो will alपढ़ोy be ordering the data, a truncate will not.
 * Thus, we need to explicitly order the zeroed pages.
 */
अटल handle_t *ocfs2_zero_start_ordered_transaction(काष्ठा inode *inode,
						      काष्ठा buffer_head *di_bh,
						      loff_t start_byte,
						      loff_t length)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle = शून्य;
	पूर्णांक ret = 0;

	अगर (!ocfs2_should_order_data(inode))
		जाओ out;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_jbd2_inode_add_ग_लिखो(handle, inode, start_byte, length);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	ocfs2_update_inode_fsync_trans(handle, inode, 1);

out:
	अगर (ret) अणु
		अगर (!IS_ERR(handle))
			ocfs2_commit_trans(osb, handle);
		handle = ERR_PTR(ret);
	पूर्ण
	वापस handle;
पूर्ण

/* Some parts of this taken from generic_cont_expand, which turned out
 * to be too fragile to करो exactly what we need without us having to
 * worry about recursive locking in ->ग_लिखो_begin() and ->ग_लिखो_end(). */
अटल पूर्णांक ocfs2_ग_लिखो_zero_page(काष्ठा inode *inode, u64 असल_from,
				 u64 असल_to, काष्ठा buffer_head *di_bh)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	अचिन्हित दीर्घ index = असल_from >> PAGE_SHIFT;
	handle_t *handle;
	पूर्णांक ret = 0;
	अचिन्हित zero_from, zero_to, block_start, block_end;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	BUG_ON(असल_from >= असल_to);
	BUG_ON(असल_to > (((u64)index + 1) << PAGE_SHIFT));
	BUG_ON(असल_from & (inode->i_blkbits - 1));

	handle = ocfs2_zero_start_ordered_transaction(inode, di_bh,
						      असल_from,
						      असल_to - असल_from);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out;
	पूर्ण

	page = find_or_create_page(mapping, index, GFP_NOFS);
	अगर (!page) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out_commit_trans;
	पूर्ण

	/* Get the offsets within the page that we want to zero */
	zero_from = असल_from & (PAGE_SIZE - 1);
	zero_to = असल_to & (PAGE_SIZE - 1);
	अगर (!zero_to)
		zero_to = PAGE_SIZE;

	trace_ocfs2_ग_लिखो_zero_page(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)असल_from,
			(अचिन्हित दीर्घ दीर्घ)असल_to,
			index, zero_from, zero_to);

	/* We know that zero_from is block aligned */
	क्रम (block_start = zero_from; block_start < zero_to;
	     block_start = block_end) अणु
		block_end = block_start + i_blocksize(inode);

		/*
		 * block_start is block-aligned.  Bump it by one to क्रमce
		 * __block_ग_लिखो_begin and block_commit_ग_लिखो to zero the
		 * whole block.
		 */
		ret = __block_ग_लिखो_begin(page, block_start + 1, 0,
					  ocfs2_get_block);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण


		/* must not update i_size! */
		ret = block_commit_ग_लिखो(page, block_start + 1,
					 block_start + 1);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
		अन्यथा
			ret = 0;
	पूर्ण

	/*
	 * fs-ग_लिखोback will release the dirty pages without page lock
	 * whose offset are over inode size, the release happens at
	 * block_ग_लिखो_full_page().
	 */
	i_size_ग_लिखो(inode, असल_to);
	inode->i_blocks = ocfs2_inode_sector_count(inode);
	di->i_size = cpu_to_le64((u64)i_size_पढ़ो(inode));
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	di->i_mसमय = di->i_स_समय = cpu_to_le64(inode->i_mसमय.tv_sec);
	di->i_स_समय_nsec = cpu_to_le32(inode->i_mसमय.tv_nsec);
	di->i_mसमय_nsec = di->i_स_समय_nsec;
	अगर (handle) अणु
		ocfs2_journal_dirty(handle, di_bh);
		ocfs2_update_inode_fsync_trans(handle, inode, 1);
	पूर्ण

out_unlock:
	unlock_page(page);
	put_page(page);
out_commit_trans:
	अगर (handle)
		ocfs2_commit_trans(OCFS2_SB(inode->i_sb), handle);
out:
	वापस ret;
पूर्ण

/*
 * Find the next range to zero.  We करो this in terms of bytes because
 * that's what ocfs2_zero_extend() wants, and it is dealing with the
 * pagecache.  We may वापस multiple extents.
 *
 * zero_start and zero_end are ocfs2_zero_extend()s current idea of what
 * needs to be zeroed.  range_start and range_end वापस the next zeroing
 * range.  A subsequent call should pass the previous range_end as its
 * zero_start.  If range_end is 0, there's nothing to करो.
 *
 * Unwritten extents are skipped over.  Refcounted extents are CoWd.
 */
अटल पूर्णांक ocfs2_zero_extend_get_range(काष्ठा inode *inode,
				       काष्ठा buffer_head *di_bh,
				       u64 zero_start, u64 zero_end,
				       u64 *range_start, u64 *range_end)
अणु
	पूर्णांक rc = 0, needs_cow = 0;
	u32 p_cpos, zero_clusters = 0;
	u32 zero_cpos =
		zero_start >> OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	u32 last_cpos = ocfs2_clusters_क्रम_bytes(inode->i_sb, zero_end);
	अचिन्हित पूर्णांक num_clusters = 0;
	अचिन्हित पूर्णांक ext_flags = 0;

	जबतक (zero_cpos < last_cpos) अणु
		rc = ocfs2_get_clusters(inode, zero_cpos, &p_cpos,
					&num_clusters, &ext_flags);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			जाओ out;
		पूर्ण

		अगर (p_cpos && !(ext_flags & OCFS2_EXT_UNWRITTEN)) अणु
			zero_clusters = num_clusters;
			अगर (ext_flags & OCFS2_EXT_REFCOUNTED)
				needs_cow = 1;
			अवरोध;
		पूर्ण

		zero_cpos += num_clusters;
	पूर्ण
	अगर (!zero_clusters) अणु
		*range_end = 0;
		जाओ out;
	पूर्ण

	जबतक ((zero_cpos + zero_clusters) < last_cpos) अणु
		rc = ocfs2_get_clusters(inode, zero_cpos + zero_clusters,
					&p_cpos, &num_clusters,
					&ext_flags);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			जाओ out;
		पूर्ण

		अगर (!p_cpos || (ext_flags & OCFS2_EXT_UNWRITTEN))
			अवरोध;
		अगर (ext_flags & OCFS2_EXT_REFCOUNTED)
			needs_cow = 1;
		zero_clusters += num_clusters;
	पूर्ण
	अगर ((zero_cpos + zero_clusters) > last_cpos)
		zero_clusters = last_cpos - zero_cpos;

	अगर (needs_cow) अणु
		rc = ocfs2_refcount_cow(inode, di_bh, zero_cpos,
					zero_clusters, अच_पूर्णांक_उच्च);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			जाओ out;
		पूर्ण
	पूर्ण

	*range_start = ocfs2_clusters_to_bytes(inode->i_sb, zero_cpos);
	*range_end = ocfs2_clusters_to_bytes(inode->i_sb,
					     zero_cpos + zero_clusters);

out:
	वापस rc;
पूर्ण

/*
 * Zero one range वापसed from ocfs2_zero_extend_get_range().  The caller
 * has made sure that the entire range needs zeroing.
 */
अटल पूर्णांक ocfs2_zero_extend_range(काष्ठा inode *inode, u64 range_start,
				   u64 range_end, काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक rc = 0;
	u64 next_pos;
	u64 zero_pos = range_start;

	trace_ocfs2_zero_extend_range(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)range_start,
			(अचिन्हित दीर्घ दीर्घ)range_end);
	BUG_ON(range_start >= range_end);

	जबतक (zero_pos < range_end) अणु
		next_pos = (zero_pos & PAGE_MASK) + PAGE_SIZE;
		अगर (next_pos > range_end)
			next_pos = range_end;
		rc = ocfs2_ग_लिखो_zero_page(inode, zero_pos, next_pos, di_bh);
		अगर (rc < 0) अणु
			mlog_त्रुटि_सं(rc);
			अवरोध;
		पूर्ण
		zero_pos = next_pos;

		/*
		 * Very large extends have the potential to lock up
		 * the cpu क्रम extended periods of समय.
		 */
		cond_resched();
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक ocfs2_zero_extend(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		      loff_t zero_to_size)
अणु
	पूर्णांक ret = 0;
	u64 zero_start, range_start = 0, range_end = 0;
	काष्ठा super_block *sb = inode->i_sb;

	zero_start = ocfs2_align_bytes_to_blocks(sb, i_size_पढ़ो(inode));
	trace_ocfs2_zero_extend((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)zero_start,
				(अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode));
	जबतक (zero_start < zero_to_size) अणु
		ret = ocfs2_zero_extend_get_range(inode, di_bh, zero_start,
						  zero_to_size,
						  &range_start,
						  &range_end);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
		अगर (!range_end)
			अवरोध;
		/* Trim the ends */
		अगर (range_start < zero_start)
			range_start = zero_start;
		अगर (range_end > zero_to_size)
			range_end = zero_to_size;

		ret = ocfs2_zero_extend_range(inode, range_start,
					      range_end, di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
		zero_start = range_end;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_extend_no_holes(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			  u64 new_i_size, u64 zero_to)
अणु
	पूर्णांक ret;
	u32 clusters_to_add;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	/*
	 * Only quota files call this without a bh, and they can't be
	 * refcounted.
	 */
	BUG_ON(!di_bh && ocfs2_is_refcount_inode(inode));
	BUG_ON(!di_bh && !(oi->ip_flags & OCFS2_INODE_SYSTEM_खाता));

	clusters_to_add = ocfs2_clusters_क्रम_bytes(inode->i_sb, new_i_size);
	अगर (clusters_to_add < oi->ip_clusters)
		clusters_to_add = 0;
	अन्यथा
		clusters_to_add -= oi->ip_clusters;

	अगर (clusters_to_add) अणु
		ret = ocfs2_extend_allocation(inode, oi->ip_clusters,
					      clusters_to_add, 0);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Call this even अगर we करोn't add any clusters to the tree. We
	 * still need to zero the area between the old i_size and the
	 * new i_size.
	 */
	ret = ocfs2_zero_extend(inode, di_bh, zero_to);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_extend_file(काष्ठा inode *inode,
			     काष्ठा buffer_head *di_bh,
			     u64 new_i_size)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	BUG_ON(!di_bh);

	/* setattr someबार calls us like this. */
	अगर (new_i_size == 0)
		जाओ out;

	अगर (i_size_पढ़ो(inode) == new_i_size)
		जाओ out;
	BUG_ON(new_i_size < i_size_पढ़ो(inode));

	/*
	 * The alloc sem blocks people in पढ़ो/ग_लिखो from पढ़ोing our
	 * allocation until we're करोne changing it. We depend on
	 * i_mutex to block other extend/truncate calls जबतक we're
	 * here.  We even have to hold it क्रम sparse files because there
	 * might be some tail zeroing.
	 */
	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		/*
		 * We can optimize small extends by keeping the inodes
		 * अंतरभूत data.
		 */
		अगर (ocfs2_size_fits_अंतरभूत_data(di_bh, new_i_size)) अणु
			up_ग_लिखो(&oi->ip_alloc_sem);
			जाओ out_update_size;
		पूर्ण

		ret = ocfs2_convert_अंतरभूत_data_to_extents(inode, di_bh);
		अगर (ret) अणु
			up_ग_लिखो(&oi->ip_alloc_sem);
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)))
		ret = ocfs2_zero_extend(inode, di_bh, new_i_size);
	अन्यथा
		ret = ocfs2_extend_no_holes(inode, di_bh, new_i_size,
					    new_i_size);

	up_ग_लिखो(&oi->ip_alloc_sem);

	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

out_update_size:
	ret = ocfs2_simple_size_update(inode, di_bh, new_i_size);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *attr)
अणु
	पूर्णांक status = 0, size_change;
	पूर्णांक inode_locked = 0;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	काष्ठा buffer_head *bh = शून्य;
	handle_t *handle = शून्य;
	काष्ठा dquot *transfer_to[MAXQUOTAS] = अणु पूर्ण;
	पूर्णांक qtype;
	पूर्णांक had_lock;
	काष्ठा ocfs2_lock_holder oh;

	trace_ocfs2_setattr(inode, dentry,
			    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			    dentry->d_name.len, dentry->d_name.name,
			    attr->ia_valid, attr->ia_mode,
			    from_kuid(&init_user_ns, attr->ia_uid),
			    from_kgid(&init_user_ns, attr->ia_gid));

	/* ensuring we करोn't even attempt to truncate a symlink */
	अगर (S_ISLNK(inode->i_mode))
		attr->ia_valid &= ~ATTR_SIZE;

#घोषणा OCFS2_VALID_ATTRS (ATTR_ATIME | ATTR_MTIME | ATTR_CTIME | ATTR_SIZE \
			   | ATTR_GID | ATTR_UID | ATTR_MODE)
	अगर (!(attr->ia_valid & OCFS2_VALID_ATTRS))
		वापस 0;

	status = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (status)
		वापस status;

	अगर (is_quota_modअगरication(inode, attr)) अणु
		status = dquot_initialize(inode);
		अगर (status)
			वापस status;
	पूर्ण
	size_change = S_ISREG(inode->i_mode) && attr->ia_valid & ATTR_SIZE;
	अगर (size_change) अणु
		/*
		 * Here we should रुको dio to finish beक्रमe inode lock
		 * to aव्योम a deadlock between ocfs2_setattr() and
		 * ocfs2_dio_end_io_ग_लिखो()
		 */
		inode_dio_रुको(inode);

		status = ocfs2_rw_lock(inode, 1);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	had_lock = ocfs2_inode_lock_tracker(inode, &bh, 1, &oh);
	अगर (had_lock < 0) अणु
		status = had_lock;
		जाओ bail_unlock_rw;
	पूर्ण अन्यथा अगर (had_lock) अणु
		/*
		 * As far as we know, ocfs2_setattr() could only be the first
		 * VFS entry poपूर्णांक in the call chain of recursive cluster
		 * locking issue.
		 *
		 * For instance:
		 * chmod_common()
		 *  notअगरy_change()
		 *   ocfs2_setattr()
		 *    posix_acl_chmod()
		 *     ocfs2_iop_get_acl()
		 *
		 * But, we're not 100% sure if it's always true, because the
		 * ordering of the VFS entry poपूर्णांकs in the call chain is out
		 * of our control. So, we'd better dump the stack here to
		 * catch the other हालs of recursive locking.
		 */
		mlog(ML_ERROR, "Another case of recursive locking:\n");
		dump_stack();
	पूर्ण
	inode_locked = 1;

	अगर (size_change) अणु
		status = inode_newsize_ok(inode, attr->ia_size);
		अगर (status)
			जाओ bail_unlock;

		अगर (i_size_पढ़ो(inode) >= attr->ia_size) अणु
			अगर (ocfs2_should_order_data(inode)) अणु
				status = ocfs2_begin_ordered_truncate(inode,
								      attr->ia_size);
				अगर (status)
					जाओ bail_unlock;
			पूर्ण
			status = ocfs2_truncate_file(inode, bh, attr->ia_size);
		पूर्ण अन्यथा
			status = ocfs2_extend_file(inode, bh, attr->ia_size);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			status = -ENOSPC;
			जाओ bail_unlock;
		पूर्ण
	पूर्ण

	अगर ((attr->ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, inode->i_uid)) ||
	    (attr->ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, inode->i_gid))) अणु
		/*
		 * Gather poपूर्णांकers to quota काष्ठाures so that allocation /
		 * मुक्तing of quota काष्ठाures happens here and not inside
		 * dquot_transfer() where we have problems with lock ordering
		 */
		अगर (attr->ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, inode->i_uid)
		    && OCFS2_HAS_RO_COMPAT_FEATURE(sb,
		    OCFS2_FEATURE_RO_COMPAT_USRQUOTA)) अणु
			transfer_to[USRQUOTA] = dqget(sb, make_kqid_uid(attr->ia_uid));
			अगर (IS_ERR(transfer_to[USRQUOTA])) अणु
				status = PTR_ERR(transfer_to[USRQUOTA]);
				transfer_to[USRQUOTA] = शून्य;
				जाओ bail_unlock;
			पूर्ण
		पूर्ण
		अगर (attr->ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, inode->i_gid)
		    && OCFS2_HAS_RO_COMPAT_FEATURE(sb,
		    OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)) अणु
			transfer_to[GRPQUOTA] = dqget(sb, make_kqid_gid(attr->ia_gid));
			अगर (IS_ERR(transfer_to[GRPQUOTA])) अणु
				status = PTR_ERR(transfer_to[GRPQUOTA]);
				transfer_to[GRPQUOTA] = शून्य;
				जाओ bail_unlock;
			पूर्ण
		पूर्ण
		करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
		handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS +
					   2 * ocfs2_quota_trans_credits(sb));
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			mlog_त्रुटि_सं(status);
			जाओ bail_unlock_alloc;
		पूर्ण
		status = __dquot_transfer(inode, transfer_to);
		अगर (status < 0)
			जाओ bail_commit;
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
		handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			mlog_त्रुटि_सं(status);
			जाओ bail_unlock_alloc;
		पूर्ण
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);

	status = ocfs2_mark_inode_dirty(handle, inode, bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

bail_commit:
	ocfs2_commit_trans(osb, handle);
bail_unlock_alloc:
	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
bail_unlock:
	अगर (status && inode_locked) अणु
		ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);
		inode_locked = 0;
	पूर्ण
bail_unlock_rw:
	अगर (size_change)
		ocfs2_rw_unlock(inode, 1);
bail:

	/* Release quota poपूर्णांकers in हाल we acquired them */
	क्रम (qtype = 0; qtype < OCFS2_MAXQUOTAS; qtype++)
		dqput(transfer_to[qtype]);

	अगर (!status && attr->ia_valid & ATTR_MODE) अणु
		status = ocfs2_acl_chmod(inode, bh);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण
	अगर (inode_locked)
		ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);

	brअन्यथा(bh);
	वापस status;
पूर्ण

पूर्णांक ocfs2_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा super_block *sb = path->dentry->d_sb;
	काष्ठा ocfs2_super *osb = sb->s_fs_info;
	पूर्णांक err;

	err = ocfs2_inode_revalidate(path->dentry);
	अगर (err) अणु
		अगर (err != -ENOENT)
			mlog_त्रुटि_सं(err);
		जाओ bail;
	पूर्ण

	generic_fillattr(&init_user_ns, inode, stat);
	/*
	 * If there is अंतरभूत data in the inode, the inode will normally not
	 * have data blocks allocated (it may have an बाह्यal xattr block).
	 * Report at least one sector क्रम such files, so tools like tar, rsync,
	 * others करोn't incorrectly think the file is completely sparse.
	 */
	अगर (unlikely(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		stat->blocks += (stat->size + 511)>>9;

	/* We set the blksize from the cluster size क्रम perक्रमmance */
	stat->blksize = osb->s_clustersize;

bail:
	वापस err;
पूर्ण

पूर्णांक ocfs2_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     पूर्णांक mask)
अणु
	पूर्णांक ret, had_lock;
	काष्ठा ocfs2_lock_holder oh;

	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	had_lock = ocfs2_inode_lock_tracker(inode, शून्य, 0, &oh);
	अगर (had_lock < 0) अणु
		ret = had_lock;
		जाओ out;
	पूर्ण अन्यथा अगर (had_lock) अणु
		/* See comments in ocfs2_setattr() क्रम details.
		 * The call chain of this हाल could be:
		 * करो_sys_खोलो()
		 *  may_खोलो()
		 *   inode_permission()
		 *    ocfs2_permission()
		 *     ocfs2_iop_get_acl()
		 */
		mlog(ML_ERROR, "Another case of recursive locking:\n");
		dump_stack();
	पूर्ण

	ret = generic_permission(&init_user_ns, inode, mask);

	ocfs2_inode_unlock_tracker(inode, 0, &oh, had_lock);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_ग_लिखो_हटाओ_suid(काष्ठा inode *inode,
				     काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di;

	trace_ocfs2_ग_लिखो_हटाओ_suid(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			inode->i_mode);

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_trans;
	पूर्ण

	inode->i_mode &= ~S_ISUID;
	अगर ((inode->i_mode & S_ISGID) && (inode->i_mode & S_IXGRP))
		inode->i_mode &= ~S_ISGID;

	di = (काष्ठा ocfs2_dinode *) bh->b_data;
	di->i_mode = cpu_to_le16(inode->i_mode);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, bh);

out_trans:
	ocfs2_commit_trans(osb, handle);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_ग_लिखो_हटाओ_suid(काष्ठा inode *inode)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *bh = शून्य;

	ret = ocfs2_पढ़ो_inode_block(inode, &bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret =  __ocfs2_ग_लिखो_हटाओ_suid(inode, bh);
out:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

/*
 * Allocate enough extents to cover the region starting at byte offset
 * start क्रम len bytes. Existing extents are skipped, any extents
 * added are marked as "unwritten".
 */
अटल पूर्णांक ocfs2_allocate_unwritten_extents(काष्ठा inode *inode,
					    u64 start, u64 len)
अणु
	पूर्णांक ret;
	u32 cpos, phys_cpos, clusters, alloc_size;
	u64 end = start + len;
	काष्ठा buffer_head *di_bh = शून्य;

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * Nothing to करो अगर the requested reservation range
		 * fits within the inode.
		 */
		अगर (ocfs2_size_fits_अंतरभूत_data(di_bh, end))
			जाओ out;

		ret = ocfs2_convert_अंतरभूत_data_to_extents(inode, di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We consider both start and len to be inclusive.
	 */
	cpos = start >> OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	clusters = ocfs2_clusters_क्रम_bytes(inode->i_sb, start + len);
	clusters -= cpos;

	जबतक (clusters) अणु
		ret = ocfs2_get_clusters(inode, cpos, &phys_cpos,
					 &alloc_size, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * Hole or existing extent len can be arbitrary, so
		 * cap it to our own allocation request.
		 */
		अगर (alloc_size > clusters)
			alloc_size = clusters;

		अगर (phys_cpos) अणु
			/*
			 * We alपढ़ोy have an allocation at this
			 * region so we can safely skip it.
			 */
			जाओ next;
		पूर्ण

		ret = ocfs2_extend_allocation(inode, cpos, alloc_size, 1);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

next:
		cpos += alloc_size;
		clusters -= alloc_size;
	पूर्ण

	ret = 0;
out:

	brअन्यथा(di_bh);
	वापस ret;
पूर्ण

/*
 * Truncate a byte range, aव्योमing pages within partial clusters. This
 * preserves those pages क्रम the zeroing code to ग_लिखो to.
 */
अटल व्योम ocfs2_truncate_cluster_pages(काष्ठा inode *inode, u64 byte_start,
					 u64 byte_len)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	loff_t start, end;
	काष्ठा address_space *mapping = inode->i_mapping;

	start = (loff_t)ocfs2_align_bytes_to_clusters(inode->i_sb, byte_start);
	end = byte_start + byte_len;
	end = end & ~(osb->s_clustersize - 1);

	अगर (start < end) अणु
		unmap_mapping_range(mapping, start, end - start, 0);
		truncate_inode_pages_range(mapping, start, end - 1);
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_zero_partial_clusters(काष्ठा inode *inode,
				       u64 start, u64 len)
अणु
	पूर्णांक ret = 0;
	u64 पंचांगpend = 0;
	u64 end = start + len;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	अचिन्हित पूर्णांक csize = osb->s_clustersize;
	handle_t *handle;

	/*
	 * The "start" and "end" values are NOT necessarily part of
	 * the range whose allocation is being deleted. Rather, this
	 * is what the user passed in with the request. We must zero
	 * partial clusters here. There's no need to worry about
	 * physical allocation - the zeroing code knows to skip holes.
	 */
	trace_ocfs2_zero_partial_clusters(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		(अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end);

	/*
	 * If both edges are on a cluster boundary then there's no
	 * zeroing required as the region is part of the allocation to
	 * be truncated.
	 */
	अगर ((start & (csize - 1)) == 0 && (end & (csize - 1)) == 0)
		जाओ out;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * If start is on a cluster boundary and end is somewhere in another
	 * cluster, we have not COWed the cluster starting at start, unless
	 * end is also within the same cluster. So, in this हाल, we skip this
	 * first call to ocfs2_zero_range_क्रम_truncate() truncate and move on
	 * to the next one.
	 */
	अगर ((start & (csize - 1)) != 0) अणु
		/*
		 * We want to get the byte offset of the end of the 1st
		 * cluster.
		 */
		पंचांगpend = (u64)osb->s_clustersize +
			(start & ~(osb->s_clustersize - 1));
		अगर (पंचांगpend > end)
			पंचांगpend = end;

		trace_ocfs2_zero_partial_clusters_range1(
			(अचिन्हित दीर्घ दीर्घ)start,
			(अचिन्हित दीर्घ दीर्घ)पंचांगpend);

		ret = ocfs2_zero_range_क्रम_truncate(inode, handle, start,
						    पंचांगpend);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

	अगर (पंचांगpend < end) अणु
		/*
		 * This may make start and end equal, but the zeroing
		 * code will skip any work in that हाल so there's no
		 * need to catch it up here.
		 */
		start = end & ~(osb->s_clustersize - 1);

		trace_ocfs2_zero_partial_clusters_range2(
			(अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end);

		ret = ocfs2_zero_range_क्रम_truncate(inode, handle, start, end);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
	ocfs2_update_inode_fsync_trans(handle, inode, 1);

	ocfs2_commit_trans(osb, handle);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_find_rec(काष्ठा ocfs2_extent_list *el, u32 pos)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_extent_rec *rec = शून्य;

	क्रम (i = le16_to_cpu(el->l_next_मुक्त_rec) - 1; i >= 0; i--) अणु

		rec = &el->l_recs[i];

		अगर (le32_to_cpu(rec->e_cpos) < pos)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

/*
 * Helper to calculate the punching pos and length in one run, we handle the
 * following three हालs in order:
 *
 * - हटाओ the entire record
 * - हटाओ a partial record
 * - no record needs to be हटाओd (hole-punching completed)
*/
अटल व्योम ocfs2_calc_trunc_pos(काष्ठा inode *inode,
				 काष्ठा ocfs2_extent_list *el,
				 काष्ठा ocfs2_extent_rec *rec,
				 u32 trunc_start, u32 *trunc_cpos,
				 u32 *trunc_len, u32 *trunc_end,
				 u64 *blkno, पूर्णांक *करोne)
अणु
	पूर्णांक ret = 0;
	u32 coff, range;

	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);

	अगर (le32_to_cpu(rec->e_cpos) >= trunc_start) अणु
		/*
		 * हटाओ an entire extent record.
		 */
		*trunc_cpos = le32_to_cpu(rec->e_cpos);
		/*
		 * Skip holes अगर any.
		 */
		अगर (range < *trunc_end)
			*trunc_end = range;
		*trunc_len = *trunc_end - le32_to_cpu(rec->e_cpos);
		*blkno = le64_to_cpu(rec->e_blkno);
		*trunc_end = le32_to_cpu(rec->e_cpos);
	पूर्ण अन्यथा अगर (range > trunc_start) अणु
		/*
		 * हटाओ a partial extent record, which means we're
		 * removing the last extent record.
		 */
		*trunc_cpos = trunc_start;
		/*
		 * skip hole अगर any.
		 */
		अगर (range < *trunc_end)
			*trunc_end = range;
		*trunc_len = *trunc_end - trunc_start;
		coff = trunc_start - le32_to_cpu(rec->e_cpos);
		*blkno = le64_to_cpu(rec->e_blkno) +
				ocfs2_clusters_to_blocks(inode->i_sb, coff);
		*trunc_end = trunc_start;
	पूर्ण अन्यथा अणु
		/*
		 * It may have two following possibilities:
		 *
		 * - last record has been हटाओd
		 * - trunc_start was within a hole
		 *
		 * both two हालs mean the completion of hole punching.
		 */
		ret = 1;
	पूर्ण

	*करोne = ret;
पूर्ण

पूर्णांक ocfs2_हटाओ_inode_range(काष्ठा inode *inode,
			     काष्ठा buffer_head *di_bh, u64 byte_start,
			     u64 byte_len)
अणु
	पूर्णांक ret = 0, flags = 0, करोne = 0, i;
	u32 trunc_start, trunc_len, trunc_end, trunc_cpos, phys_cpos;
	u32 cluster_in_el;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_extent_list *el = शून्य;
	काष्ठा ocfs2_extent_rec *rec = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	u64 blkno, refcount_loc = le64_to_cpu(di->i_refcount_loc);

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&dealloc);

	trace_ocfs2_हटाओ_inode_range(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)byte_start,
			(अचिन्हित दीर्घ दीर्घ)byte_len);

	अगर (byte_len == 0)
		वापस 0;

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = ocfs2_truncate_अंतरभूत(inode, di_bh, byte_start,
					    byte_start + byte_len, 0);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		/*
		 * There's no need to get fancy with the page cache
		 * truncate of an अंतरभूत-data inode. We're talking
		 * about less than a page here, which will be cached
		 * in the dinode buffer anyway.
		 */
		unmap_mapping_range(mapping, 0, 0, 0);
		truncate_inode_pages(mapping, 0);
		जाओ out;
	पूर्ण

	/*
	 * For reflinks, we may need to CoW 2 clusters which might be
	 * partially zero'd later, if hole's start and end offset were
	 * within one cluster(means is not exactly aligned to clustersize).
	 */

	अगर (ocfs2_is_refcount_inode(inode)) अणु
		ret = ocfs2_cow_file_pos(inode, di_bh, byte_start);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_cow_file_pos(inode, di_bh, byte_start + byte_len);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	trunc_start = ocfs2_clusters_क्रम_bytes(osb->sb, byte_start);
	trunc_end = (byte_start + byte_len) >> osb->s_clustersize_bits;
	cluster_in_el = trunc_end;

	ret = ocfs2_zero_partial_clusters(inode, byte_start, byte_len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	path = ocfs2_new_path_from_et(&et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	जबतक (trunc_end > trunc_start) अणु

		ret = ocfs2_find_path(INODE_CACHE(inode), path,
				      cluster_in_el);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		el = path_leaf_el(path);

		i = ocfs2_find_rec(el, trunc_end);
		/*
		 * Need to go to previous extent block.
		 */
		अगर (i < 0) अणु
			अगर (path->p_tree_depth == 0)
				अवरोध;

			ret = ocfs2_find_cpos_क्रम_left_leaf(inode->i_sb,
							    path,
							    &cluster_in_el);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			/*
			 * We've reached the lefपंचांगost extent block,
			 * it's safe to leave.
			 */
			अगर (cluster_in_el == 0)
				अवरोध;

			/*
			 * The 'pos' searched क्रम previous extent block is
			 * always one cluster less than actual trunc_end.
			 */
			trunc_end = cluster_in_el + 1;

			ocfs2_reinit_path(path, 1);

			जारी;

		पूर्ण अन्यथा
			rec = &el->l_recs[i];

		ocfs2_calc_trunc_pos(inode, el, rec, trunc_start, &trunc_cpos,
				     &trunc_len, &trunc_end, &blkno, &करोne);
		अगर (करोne)
			अवरोध;

		flags = rec->e_flags;
		phys_cpos = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

		ret = ocfs2_हटाओ_btree_range(inode, &et, trunc_cpos,
					       phys_cpos, trunc_len, flags,
					       &dealloc, refcount_loc, false);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		cluster_in_el = trunc_end;

		ocfs2_reinit_path(path, 1);
	पूर्ण

	ocfs2_truncate_cluster_pages(inode, byte_start, byte_len);

out:
	ocfs2_मुक्त_path(path);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &dealloc);

	वापस ret;
पूर्ण

/*
 * zero out partial blocks of one cluster.
 *
 * start: file offset where zero starts, will be made upper block aligned.
 * len: it will be trimmed to the end of current cluster अगर "start + len"
 *      is bigger than it.
 */
अटल पूर्णांक ocfs2_zeroout_partial_cluster(काष्ठा inode *inode,
					u64 start, u64 len)
अणु
	पूर्णांक ret;
	u64 start_block, end_block, nr_blocks;
	u64 p_block, offset;
	u32 cluster, p_cluster, nr_clusters;
	काष्ठा super_block *sb = inode->i_sb;
	u64 end = ocfs2_align_bytes_to_clusters(sb, start);

	अगर (start + len < end)
		end = start + len;

	start_block = ocfs2_blocks_क्रम_bytes(sb, start);
	end_block = ocfs2_blocks_क्रम_bytes(sb, end);
	nr_blocks = end_block - start_block;
	अगर (!nr_blocks)
		वापस 0;

	cluster = ocfs2_bytes_to_clusters(sb, start);
	ret = ocfs2_get_clusters(inode, cluster, &p_cluster,
				&nr_clusters, शून्य);
	अगर (ret)
		वापस ret;
	अगर (!p_cluster)
		वापस 0;

	offset = start_block - ocfs2_clusters_to_blocks(sb, cluster);
	p_block = ocfs2_clusters_to_blocks(sb, p_cluster) + offset;
	वापस sb_issue_zeroout(sb, p_block, nr_blocks, GFP_NOFS);
पूर्ण

/*
 * Parts of this function taken from xfs_change_file_space()
 */
अटल पूर्णांक __ocfs2_change_file_space(काष्ठा file *file, काष्ठा inode *inode,
				     loff_t f_pos, अचिन्हित पूर्णांक cmd,
				     काष्ठा ocfs2_space_resv *sr,
				     पूर्णांक change_size)
अणु
	पूर्णांक ret;
	s64 llen;
	loff_t size, orig_isize;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *di_bh = शून्य;
	handle_t *handle;
	अचिन्हित दीर्घ दीर्घ max_off = inode->i_sb->s_maxbytes;

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	inode_lock(inode);

	/*
	 * This prevents concurrent ग_लिखोs on other nodes
	 */
	ret = ocfs2_rw_lock(inode, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_rw_unlock;
	पूर्ण

	अगर (inode->i_flags & (S_IMMUTABLE|S_APPEND)) अणु
		ret = -EPERM;
		जाओ out_inode_unlock;
	पूर्ण

	orig_isize = i_size_पढ़ो(inode);
	चयन (sr->l_whence) अणु
	हाल 0: /*शुरू_से*/
		अवरोध;
	हाल 1: /*प्रस्तुत_से*/
		sr->l_start += f_pos;
		अवरोध;
	हाल 2: /*अंत_से*/
		sr->l_start += orig_isize;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_inode_unlock;
	पूर्ण
	sr->l_whence = 0;

	llen = sr->l_len > 0 ? sr->l_len - 1 : sr->l_len;

	अगर (sr->l_start < 0
	    || sr->l_start > max_off
	    || (sr->l_start + llen) < 0
	    || (sr->l_start + llen) > max_off) अणु
		ret = -EINVAL;
		जाओ out_inode_unlock;
	पूर्ण
	size = sr->l_start + sr->l_len;

	अगर (cmd == OCFS2_IOC_RESVSP || cmd == OCFS2_IOC_RESVSP64 ||
	    cmd == OCFS2_IOC_UNRESVSP || cmd == OCFS2_IOC_UNRESVSP64) अणु
		अगर (sr->l_len <= 0) अणु
			ret = -EINVAL;
			जाओ out_inode_unlock;
		पूर्ण
	पूर्ण

	अगर (file && should_हटाओ_suid(file->f_path.dentry)) अणु
		ret = __ocfs2_ग_लिखो_हटाओ_suid(inode, di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_inode_unlock;
		पूर्ण
	पूर्ण

	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	चयन (cmd) अणु
	हाल OCFS2_IOC_RESVSP:
	हाल OCFS2_IOC_RESVSP64:
		/*
		 * This takes अचिन्हित offsets, but the चिन्हित ones we
		 * pass have been checked against overflow above.
		 */
		ret = ocfs2_allocate_unwritten_extents(inode, sr->l_start,
						       sr->l_len);
		अवरोध;
	हाल OCFS2_IOC_UNRESVSP:
	हाल OCFS2_IOC_UNRESVSP64:
		ret = ocfs2_हटाओ_inode_range(inode, di_bh, sr->l_start,
					       sr->l_len);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	/* zeroout eof blocks in the cluster. */
	अगर (!ret && change_size && orig_isize < size) अणु
		ret = ocfs2_zeroout_partial_cluster(inode, orig_isize,
					size - orig_isize);
		अगर (!ret)
			i_size_ग_लिखो(inode, size);
	पूर्ण
	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_inode_unlock;
	पूर्ण

	/*
	 * We update c/mसमय क्रम these changes
	 */
	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_inode_unlock;
	पूर्ण

	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	ret = ocfs2_mark_inode_dirty(handle, inode, di_bh);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	अगर (file && (file->f_flags & O_SYNC))
		handle->h_sync = 1;

	ocfs2_commit_trans(osb, handle);

out_inode_unlock:
	brअन्यथा(di_bh);
	ocfs2_inode_unlock(inode, 1);
out_rw_unlock:
	ocfs2_rw_unlock(inode, 1);

out:
	inode_unlock(inode);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_change_file_space(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    काष्ठा ocfs2_space_resv *sr)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	पूर्णांक ret;

	अगर ((cmd == OCFS2_IOC_RESVSP || cmd == OCFS2_IOC_RESVSP64) &&
	    !ocfs2_ग_लिखोs_unwritten_extents(osb))
		वापस -ENOTTY;
	अन्यथा अगर ((cmd == OCFS2_IOC_UNRESVSP || cmd == OCFS2_IOC_UNRESVSP64) &&
		 !ocfs2_sparse_alloc(osb))
		वापस -ENOTTY;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;

	ret = mnt_want_ग_लिखो_file(file);
	अगर (ret)
		वापस ret;
	ret = __ocfs2_change_file_space(file, inode, file->f_pos, cmd, sr, 0);
	mnt_drop_ग_लिखो_file(file);
	वापस ret;
पूर्ण

अटल दीर्घ ocfs2_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
			    loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_space_resv sr;
	पूर्णांक change_size = 1;
	पूर्णांक cmd = OCFS2_IOC_RESVSP64;

	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		वापस -EOPNOTSUPP;
	अगर (!ocfs2_ग_लिखोs_unwritten_extents(osb))
		वापस -EOPNOTSUPP;

	अगर (mode & FALLOC_FL_KEEP_SIZE)
		change_size = 0;

	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		cmd = OCFS2_IOC_UNRESVSP64;

	sr.l_whence = 0;
	sr.l_start = (s64)offset;
	sr.l_len = (s64)len;

	वापस __ocfs2_change_file_space(शून्य, inode, offset, cmd, &sr,
					 change_size);
पूर्ण

पूर्णांक ocfs2_check_range_क्रम_refcount(काष्ठा inode *inode, loff_t pos,
				   माप_प्रकार count)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक extent_flags;
	u32 cpos, clusters, extent_len, phys_cpos;
	काष्ठा super_block *sb = inode->i_sb;

	अगर (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)) ||
	    !ocfs2_is_refcount_inode(inode) ||
	    OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस 0;

	cpos = pos >> OCFS2_SB(sb)->s_clustersize_bits;
	clusters = ocfs2_clusters_क्रम_bytes(sb, pos + count) - cpos;

	जबतक (clusters) अणु
		ret = ocfs2_get_clusters(inode, cpos, &phys_cpos, &extent_len,
					 &extent_flags);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (phys_cpos && (extent_flags & OCFS2_EXT_REFCOUNTED)) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		अगर (extent_len > clusters)
			extent_len = clusters;

		clusters -= extent_len;
		cpos += extent_len;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_is_io_unaligned(काष्ठा inode *inode, माप_प्रकार count, loff_t pos)
अणु
	पूर्णांक blockmask = inode->i_sb->s_blocksize - 1;
	loff_t final_size = pos + count;

	अगर ((pos & blockmask) || (final_size & blockmask))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_inode_lock_क्रम_extent_tree(काष्ठा inode *inode,
					    काष्ठा buffer_head **di_bh,
					    पूर्णांक meta_level,
					    पूर्णांक ग_लिखो_sem,
					    पूर्णांक रुको)
अणु
	पूर्णांक ret = 0;

	अगर (रुको)
		ret = ocfs2_inode_lock(inode, di_bh, meta_level);
	अन्यथा
		ret = ocfs2_try_inode_lock(inode, di_bh, meta_level);
	अगर (ret < 0)
		जाओ out;

	अगर (रुको) अणु
		अगर (ग_लिखो_sem)
			करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
		अन्यथा
			करोwn_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);
	पूर्ण अन्यथा अणु
		अगर (ग_लिखो_sem)
			ret = करोwn_ग_लिखो_trylock(&OCFS2_I(inode)->ip_alloc_sem);
		अन्यथा
			ret = करोwn_पढ़ो_trylock(&OCFS2_I(inode)->ip_alloc_sem);

		अगर (!ret) अणु
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	वापस ret;

out_unlock:
	brअन्यथा(*di_bh);
	*di_bh = शून्य;
	ocfs2_inode_unlock(inode, meta_level);
out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_inode_unlock_क्रम_extent_tree(काष्ठा inode *inode,
					       काष्ठा buffer_head **di_bh,
					       पूर्णांक meta_level,
					       पूर्णांक ग_लिखो_sem)
अणु
	अगर (ग_लिखो_sem)
		up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	अन्यथा
		up_पढ़ो(&OCFS2_I(inode)->ip_alloc_sem);

	brअन्यथा(*di_bh);
	*di_bh = शून्य;

	अगर (meta_level >= 0)
		ocfs2_inode_unlock(inode, meta_level);
पूर्ण

अटल पूर्णांक ocfs2_prepare_inode_क्रम_ग_लिखो(काष्ठा file *file,
					 loff_t pos, माप_प्रकार count, पूर्णांक रुको)
अणु
	पूर्णांक ret = 0, meta_level = 0, overग_लिखो_io = 0;
	पूर्णांक ग_लिखो_sem = 0;
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा buffer_head *di_bh = शून्य;
	u32 cpos;
	u32 clusters;

	/*
	 * We start with a पढ़ो level meta lock and only jump to an ex
	 * अगर we need to make modअगरications here.
	 */
	क्रम(;;) अणु
		ret = ocfs2_inode_lock_क्रम_extent_tree(inode,
						       &di_bh,
						       meta_level,
						       ग_लिखो_sem,
						       रुको);
		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * Check अगर IO will overग_लिखो allocated blocks in हाल
		 * IOCB_NOWAIT flag is set.
		 */
		अगर (!रुको && !overग_लिखो_io) अणु
			overग_लिखो_io = 1;

			ret = ocfs2_overग_लिखो_io(inode, di_bh, pos, count);
			अगर (ret < 0) अणु
				अगर (ret != -EAGAIN)
					mlog_त्रुटि_सं(ret);
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		/* Clear suid / sgid अगर necessary. We करो this here
		 * instead of later in the ग_लिखो path because
		 * हटाओ_suid() calls ->setattr without any hपूर्णांक that
		 * we may have alपढ़ोy करोne our cluster locking. Since
		 * ocfs2_setattr() *must* take cluster locks to
		 * proceed, this will lead us to recursively lock the
		 * inode. There's also the dinode i_size state which
		 * can be lost via setattr during extending ग_लिखोs (we
		 * set inode->i_size at the end of a ग_लिखो. */
		अगर (should_हटाओ_suid(dentry)) अणु
			अगर (meta_level == 0) अणु
				ocfs2_inode_unlock_क्रम_extent_tree(inode,
								   &di_bh,
								   meta_level,
								   ग_लिखो_sem);
				meta_level = 1;
				जारी;
			पूर्ण

			ret = ocfs2_ग_लिखो_हटाओ_suid(inode);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		ret = ocfs2_check_range_क्रम_refcount(inode, pos, count);
		अगर (ret == 1) अणु
			ocfs2_inode_unlock_क्रम_extent_tree(inode,
							   &di_bh,
							   meta_level,
							   ग_लिखो_sem);
			meta_level = 1;
			ग_लिखो_sem = 1;
			ret = ocfs2_inode_lock_क्रम_extent_tree(inode,
							       &di_bh,
							       meta_level,
							       ग_लिखो_sem,
							       रुको);
			अगर (ret < 0) अणु
				अगर (ret != -EAGAIN)
					mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			cpos = pos >> OCFS2_SB(inode->i_sb)->s_clustersize_bits;
			clusters =
				ocfs2_clusters_क्रम_bytes(inode->i_sb, pos + count) - cpos;
			ret = ocfs2_refcount_cow(inode, di_bh, cpos, clusters, अच_पूर्णांक_उच्च);
		पूर्ण

		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण

		अवरोध;
	पूर्ण

out_unlock:
	trace_ocfs2_prepare_inode_क्रम_ग_लिखो(OCFS2_I(inode)->ip_blkno,
					    pos, count, रुको);

	ocfs2_inode_unlock_क्रम_extent_tree(inode,
					   &di_bh,
					   meta_level,
					   ग_लिखो_sem);

out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ocfs2_file_ग_लिखो_iter(काष्ठा kiocb *iocb,
				    काष्ठा iov_iter *from)
अणु
	पूर्णांक rw_level;
	sमाप_प्रकार written = 0;
	sमाप_प्रकार ret;
	माप_प्रकार count = iov_iter_count(from);
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	पूर्णांक full_coherency = !(osb->s_mount_opt &
			       OCFS2_MOUNT_COHERENCY_BUFFERED);
	व्योम *saved_ki_complete = शून्य;
	पूर्णांक append_ग_लिखो = ((iocb->ki_pos + count) >=
			i_size_पढ़ो(inode) ? 1 : 0);
	पूर्णांक direct_io = iocb->ki_flags & IOCB_सूचीECT ? 1 : 0;
	पूर्णांक noरुको = iocb->ki_flags & IOCB_NOWAIT ? 1 : 0;

	trace_ocfs2_file_ग_लिखो_iter(inode, file, file->f_path.dentry,
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		file->f_path.dentry->d_name.len,
		file->f_path.dentry->d_name.name,
		(अचिन्हित पूर्णांक)from->nr_segs);	/* GRRRRR */

	अगर (!direct_io && noरुको)
		वापस -EOPNOTSUPP;

	अगर (count == 0)
		वापस 0;

	अगर (noरुको) अणु
		अगर (!inode_trylock(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा
		inode_lock(inode);

	/*
	 * Concurrent O_सूचीECT ग_लिखोs are allowed with
	 * mount_option "coherency=buffered".
	 * For append ग_लिखो, we must take rw EX.
	 */
	rw_level = (!direct_io || full_coherency || append_ग_लिखो);

	अगर (noरुको)
		ret = ocfs2_try_rw_lock(inode, rw_level);
	अन्यथा
		ret = ocfs2_rw_lock(inode, rw_level);
	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN)
			mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	/*
	 * O_सूचीECT ग_लिखोs with "coherency=full" need to take EX cluster
	 * inode_lock to guarantee coherency.
	 */
	अगर (direct_io && full_coherency) अणु
		/*
		 * We need to take and drop the inode lock to क्रमce
		 * other nodes to drop their caches.  Buffered I/O
		 * alपढ़ोy करोes this in ग_लिखो_begin().
		 */
		अगर (noरुको)
			ret = ocfs2_try_inode_lock(inode, शून्य, 1);
		अन्यथा
			ret = ocfs2_inode_lock(inode, शून्य, 1);
		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ocfs2_inode_unlock(inode, 1);
	पूर्ण

	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0) अणु
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	count = ret;

	ret = ocfs2_prepare_inode_क्रम_ग_लिखो(file, iocb->ki_pos, count, !noरुको);
	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (direct_io && !is_sync_kiocb(iocb) &&
	    ocfs2_is_io_unaligned(inode, count, iocb->ki_pos)) अणु
		/*
		 * Make it a sync io अगर it's an unaligned aio.
		 */
		saved_ki_complete = xchg(&iocb->ki_complete, शून्य);
	पूर्ण

	/* communicate with ocfs2_dio_end_io */
	ocfs2_iocb_set_rw_locked(iocb, rw_level);

	written = __generic_file_ग_लिखो_iter(iocb, from);
	/* buffered aio wouldn't have proper lock coverage today */
	BUG_ON(written == -EIOCBQUEUED && !direct_io);

	/*
	 * deep in g_f_a_w_n()->ocfs2_direct_IO we pass in a ocfs2_dio_end_io
	 * function poपूर्णांकer which is called when o_direct io completes so that
	 * it can unlock our rw lock.
	 * Unक्रमtunately there are error हालs which call end_io and others
	 * that करोn't.  so we don't have to unlock the rw_lock अगर either an
	 * async dio is going to करो it in the future or an end_io after an
	 * error has alपढ़ोy करोne it.
	 */
	अगर ((written == -EIOCBQUEUED) || (!ocfs2_iocb_is_rw_locked(iocb))) अणु
		rw_level = -1;
	पूर्ण

	अगर (unlikely(written <= 0))
		जाओ out;

	अगर (((file->f_flags & O_DSYNC) && !direct_io) ||
	    IS_SYNC(inode)) अणु
		ret = filemap_fdataग_लिखो_range(file->f_mapping,
					       iocb->ki_pos - written,
					       iocb->ki_pos - 1);
		अगर (ret < 0)
			written = ret;

		अगर (!ret) अणु
			ret = jbd2_journal_क्रमce_commit(osb->journal->j_journal);
			अगर (ret < 0)
				written = ret;
		पूर्ण

		अगर (!ret)
			ret = filemap_fdataरुको_range(file->f_mapping,
						      iocb->ki_pos - written,
						      iocb->ki_pos - 1);
	पूर्ण

out:
	अगर (saved_ki_complete)
		xchg(&iocb->ki_complete, saved_ki_complete);

	अगर (rw_level != -1)
		ocfs2_rw_unlock(inode, rw_level);

out_mutex:
	inode_unlock(inode);

	अगर (written)
		ret = written;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ocfs2_file_पढ़ो_iter(काष्ठा kiocb *iocb,
				   काष्ठा iov_iter *to)
अणु
	पूर्णांक ret = 0, rw_level = -1, lock_level = 0;
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक direct_io = iocb->ki_flags & IOCB_सूचीECT ? 1 : 0;
	पूर्णांक noरुको = iocb->ki_flags & IOCB_NOWAIT ? 1 : 0;

	trace_ocfs2_file_पढ़ो_iter(inode, filp, filp->f_path.dentry,
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			filp->f_path.dentry->d_name.len,
			filp->f_path.dentry->d_name.name,
			to->nr_segs);	/* GRRRRR */


	अगर (!inode) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	अगर (!direct_io && noरुको)
		वापस -EOPNOTSUPP;

	/*
	 * buffered पढ़ोs protect themselves in ->पढ़ोpage().  O_सूचीECT पढ़ोs
	 * need locks to protect pending पढ़ोs from racing with truncate.
	 */
	अगर (direct_io) अणु
		अगर (noरुको)
			ret = ocfs2_try_rw_lock(inode, 0);
		अन्यथा
			ret = ocfs2_rw_lock(inode, 0);

		अगर (ret < 0) अणु
			अगर (ret != -EAGAIN)
				mlog_त्रुटि_सं(ret);
			जाओ bail;
		पूर्ण
		rw_level = 0;
		/* communicate with ocfs2_dio_end_io */
		ocfs2_iocb_set_rw_locked(iocb, rw_level);
	पूर्ण

	/*
	 * We're fine letting folks race truncates and extending
	 * ग_लिखोs with पढ़ो across the cluster, just like they can
	 * locally. Hence no rw_lock during पढ़ो.
	 *
	 * Take and drop the meta data lock to update inode fields
	 * like i_size. This allows the checks करोwn below
	 * generic_file_पढ़ो_iter() a chance of actually working.
	 */
	ret = ocfs2_inode_lock_aसमय(inode, filp->f_path.mnt, &lock_level,
				     !noरुको);
	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN)
			mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण
	ocfs2_inode_unlock(inode, lock_level);

	ret = generic_file_पढ़ो_iter(iocb, to);
	trace_generic_file_पढ़ो_iter_ret(ret);

	/* buffered aio wouldn't have proper lock coverage today */
	BUG_ON(ret == -EIOCBQUEUED && !direct_io);

	/* see ocfs2_file_ग_लिखो_iter */
	अगर (ret == -EIOCBQUEUED || !ocfs2_iocb_is_rw_locked(iocb)) अणु
		rw_level = -1;
	पूर्ण

bail:
	अगर (rw_level != -1)
		ocfs2_rw_unlock(inode, rw_level);

	वापस ret;
पूर्ण

/* Refer generic_file_llseek_unlocked() */
अटल loff_t ocfs2_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक ret = 0;

	inode_lock(inode);

	चयन (whence) अणु
	हाल शुरू_से:
		अवरोध;
	हाल अंत_से:
		/* अंत_से requires the OCFS2 inode lock क्रम the file
		 * because it references the file's size.
		 */
		ret = ocfs2_inode_lock(inode, शून्य, 0);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		offset += i_size_पढ़ो(inode);
		ocfs2_inode_unlock(inode, 0);
		अवरोध;
	हाल प्रस्तुत_से:
		अगर (offset == 0) अणु
			offset = file->f_pos;
			जाओ out;
		पूर्ण
		offset += file->f_pos;
		अवरोध;
	हाल SEEK_DATA:
	हाल SEEK_HOLE:
		ret = ocfs2_seek_data_hole_offset(file, &offset, whence);
		अगर (ret)
			जाओ out;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	offset = vfs_setpos(file, offset, inode->i_sb->s_maxbytes);

out:
	inode_unlock(inode);
	अगर (ret)
		वापस ret;
	वापस offset;
पूर्ण

अटल loff_t ocfs2_remap_file_range(काष्ठा file *file_in, loff_t pos_in,
				     काष्ठा file *file_out, loff_t pos_out,
				     loff_t len, अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode_in->i_sb);
	काष्ठा buffer_head *in_bh = शून्य, *out_bh = शून्य;
	bool same_inode = (inode_in == inode_out);
	loff_t remapped = 0;
	sमाप_प्रकार ret;

	अगर (remap_flags & ~(REMAP_खाता_DEDUP | REMAP_खाता_ADVISORY))
		वापस -EINVAL;
	अगर (!ocfs2_refcount_tree(osb))
		वापस -EOPNOTSUPP;
	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb))
		वापस -EROFS;

	/* Lock both files against IO */
	ret = ocfs2_reflink_inodes_lock(inode_in, &in_bh, inode_out, &out_bh);
	अगर (ret)
		वापस ret;

	/* Check file eligibility and prepare क्रम block sharing. */
	ret = -EINVAL;
	अगर ((OCFS2_I(inode_in)->ip_flags & OCFS2_INODE_SYSTEM_खाता) ||
	    (OCFS2_I(inode_out)->ip_flags & OCFS2_INODE_SYSTEM_खाता))
		जाओ out_unlock;

	ret = generic_remap_file_range_prep(file_in, pos_in, file_out, pos_out,
			&len, remap_flags);
	अगर (ret < 0 || len == 0)
		जाओ out_unlock;

	/* Lock out changes to the allocation maps and remap. */
	करोwn_ग_लिखो(&OCFS2_I(inode_in)->ip_alloc_sem);
	अगर (!same_inode)
		करोwn_ग_लिखो_nested(&OCFS2_I(inode_out)->ip_alloc_sem,
				  SINGLE_DEPTH_NESTING);

	/* Zap any page cache क्रम the destination file's range. */
	truncate_inode_pages_range(&inode_out->i_data,
				   round_करोwn(pos_out, PAGE_SIZE),
				   round_up(pos_out + len, PAGE_SIZE) - 1);

	remapped = ocfs2_reflink_remap_blocks(inode_in, in_bh, pos_in,
			inode_out, out_bh, pos_out, len);
	up_ग_लिखो(&OCFS2_I(inode_in)->ip_alloc_sem);
	अगर (!same_inode)
		up_ग_लिखो(&OCFS2_I(inode_out)->ip_alloc_sem);
	अगर (remapped < 0) अणु
		ret = remapped;
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Empty the extent map so that we may get the right extent
	 * record from the disk.
	 */
	ocfs2_extent_map_trunc(inode_in, 0);
	ocfs2_extent_map_trunc(inode_out, 0);

	ret = ocfs2_reflink_update_dest(inode_out, out_bh, pos_out + len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

out_unlock:
	ocfs2_reflink_inodes_unlock(inode_in, in_bh, inode_out, out_bh);
	वापस remapped > 0 ? remapped : ret;
पूर्ण

स्थिर काष्ठा inode_operations ocfs2_file_iops = अणु
	.setattr	= ocfs2_setattr,
	.getattr	= ocfs2_getattr,
	.permission	= ocfs2_permission,
	.listxattr	= ocfs2_listxattr,
	.fiemap		= ocfs2_fiemap,
	.get_acl	= ocfs2_iop_get_acl,
	.set_acl	= ocfs2_iop_set_acl,
	.fileattr_get	= ocfs2_fileattr_get,
	.fileattr_set	= ocfs2_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations ocfs2_special_file_iops = अणु
	.setattr	= ocfs2_setattr,
	.getattr	= ocfs2_getattr,
	.permission	= ocfs2_permission,
	.get_acl	= ocfs2_iop_get_acl,
	.set_acl	= ocfs2_iop_set_acl,
पूर्ण;

/*
 * Other than ->lock, keep ocfs2_fops and ocfs2_करोps in sync with
 * ocfs2_fops_no_plocks and ocfs2_करोps_no_plocks!
 */
स्थिर काष्ठा file_operations ocfs2_fops = अणु
	.llseek		= ocfs2_file_llseek,
	.mmap		= ocfs2_mmap,
	.fsync		= ocfs2_sync_file,
	.release	= ocfs2_file_release,
	.खोलो		= ocfs2_file_खोलो,
	.पढ़ो_iter	= ocfs2_file_पढ़ो_iter,
	.ग_लिखो_iter	= ocfs2_file_ग_लिखो_iter,
	.unlocked_ioctl	= ocfs2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = ocfs2_compat_ioctl,
#पूर्ण_अगर
	.lock		= ocfs2_lock,
	.flock		= ocfs2_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= ocfs2_fallocate,
	.remap_file_range = ocfs2_remap_file_range,
पूर्ण;

स्थिर काष्ठा file_operations ocfs2_करोps = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate	= ocfs2_सूची_पढ़ो,
	.fsync		= ocfs2_sync_file,
	.release	= ocfs2_dir_release,
	.खोलो		= ocfs2_dir_खोलो,
	.unlocked_ioctl	= ocfs2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = ocfs2_compat_ioctl,
#पूर्ण_अगर
	.lock		= ocfs2_lock,
	.flock		= ocfs2_flock,
पूर्ण;

/*
 * POSIX-lockless variants of our file_operations.
 *
 * These will be used अगर the underlying cluster stack करोes not support
 * posix file locking, अगर the user passes the "localflocks" mount
 * option, or अगर we have a local-only fs.
 *
 * ocfs2_flock is in here because all stacks handle UNIX file locks,
 * so we still want it in the हाल of no stack support क्रम
 * plocks. Internally, it will करो the right thing when asked to ignore
 * the cluster.
 */
स्थिर काष्ठा file_operations ocfs2_fops_no_plocks = अणु
	.llseek		= ocfs2_file_llseek,
	.mmap		= ocfs2_mmap,
	.fsync		= ocfs2_sync_file,
	.release	= ocfs2_file_release,
	.खोलो		= ocfs2_file_खोलो,
	.पढ़ो_iter	= ocfs2_file_पढ़ो_iter,
	.ग_लिखो_iter	= ocfs2_file_ग_लिखो_iter,
	.unlocked_ioctl	= ocfs2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = ocfs2_compat_ioctl,
#पूर्ण_अगर
	.flock		= ocfs2_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= ocfs2_fallocate,
	.remap_file_range = ocfs2_remap_file_range,
पूर्ण;

स्थिर काष्ठा file_operations ocfs2_करोps_no_plocks = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate	= ocfs2_सूची_पढ़ो,
	.fsync		= ocfs2_sync_file,
	.release	= ocfs2_dir_release,
	.खोलो		= ocfs2_dir_खोलो,
	.unlocked_ioctl	= ocfs2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = ocfs2_compat_ioctl,
#पूर्ण_अगर
	.flock		= ocfs2_flock,
पूर्ण;
