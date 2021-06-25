<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Implementation of operations over local quota file
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/quota.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/module.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2_fs.h"
#समावेश "ocfs2.h"
#समावेश "inode.h"
#समावेश "alloc.h"
#समावेश "file.h"
#समावेश "buffer_head_io.h"
#समावेश "journal.h"
#समावेश "sysfile.h"
#समावेश "dlmglue.h"
#समावेश "quota.h"
#समावेश "uptodate.h"
#समावेश "super.h"
#समावेश "ocfs2_trace.h"

/* Number of local quota काष्ठाures per block */
अटल अंतरभूत अचिन्हित पूर्णांक ol_quota_entries_per_block(काष्ठा super_block *sb)
अणु
	वापस ((sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE) /
		माप(काष्ठा ocfs2_local_disk_dqblk));
पूर्ण

/* Number of blocks with entries in one chunk */
अटल अंतरभूत अचिन्हित पूर्णांक ol_chunk_blocks(काष्ठा super_block *sb)
अणु
	वापस ((sb->s_blocksize - माप(काष्ठा ocfs2_local_disk_chunk) -
		 OCFS2_QBLK_RESERVED_SPACE) << 3) /
	       ol_quota_entries_per_block(sb);
पूर्ण

/* Number of entries in a chunk biपंचांगap */
अटल अचिन्हित पूर्णांक ol_chunk_entries(काष्ठा super_block *sb)
अणु
	वापस ol_chunk_blocks(sb) * ol_quota_entries_per_block(sb);
पूर्ण

/* Offset of the chunk in quota file */
अटल अचिन्हित पूर्णांक ol_quota_chunk_block(काष्ठा super_block *sb, पूर्णांक c)
अणु
	/* 1 block क्रम local quota file info, 1 block per chunk क्रम chunk info */
	वापस 1 + (ol_chunk_blocks(sb) + 1) * c;
पूर्ण

अटल अचिन्हित पूर्णांक ol_dqblk_block(काष्ठा super_block *sb, पूर्णांक c, पूर्णांक off)
अणु
	पूर्णांक epb = ol_quota_entries_per_block(sb);

	वापस ol_quota_chunk_block(sb, c) + 1 + off / epb;
पूर्ण

अटल अचिन्हित पूर्णांक ol_dqblk_block_off(काष्ठा super_block *sb, पूर्णांक c, पूर्णांक off)
अणु
	पूर्णांक epb = ol_quota_entries_per_block(sb);

	वापस (off % epb) * माप(काष्ठा ocfs2_local_disk_dqblk);
पूर्ण

/* Offset of the dquot काष्ठाure in the quota file */
अटल loff_t ol_dqblk_off(काष्ठा super_block *sb, पूर्णांक c, पूर्णांक off)
अणु
	वापस (ol_dqblk_block(sb, c, off) << sb->s_blocksize_bits) +
	       ol_dqblk_block_off(sb, c, off);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ol_dqblk_block_offset(काष्ठा super_block *sb, loff_t off)
अणु
	वापस off & ((1 << sb->s_blocksize_bits) - 1);
पूर्ण

/* Compute offset in the chunk of a काष्ठाure with the given offset */
अटल पूर्णांक ol_dqblk_chunk_off(काष्ठा super_block *sb, पूर्णांक c, loff_t off)
अणु
	पूर्णांक epb = ol_quota_entries_per_block(sb);

	वापस ((off >> sb->s_blocksize_bits) -
			ol_quota_chunk_block(sb, c) - 1) * epb
	       + ((अचिन्हित पूर्णांक)(off & ((1 << sb->s_blocksize_bits) - 1))) /
		 माप(काष्ठा ocfs2_local_disk_dqblk);
पूर्ण

/* Write bufferhead पूर्णांकo the fs */
अटल पूर्णांक ocfs2_modअगरy_bh(काष्ठा inode *inode, काष्ठा buffer_head *bh,
		व्योम (*modअगरy)(काष्ठा buffer_head *, व्योम *), व्योम *निजी)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	handle_t *handle;
	पूर्णांक status;

	handle = ocfs2_start_trans(OCFS2_SB(sb),
				   OCFS2_QUOTA_BLOCK_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		ocfs2_commit_trans(OCFS2_SB(sb), handle);
		वापस status;
	पूर्ण
	lock_buffer(bh);
	modअगरy(bh, निजी);
	unlock_buffer(bh);
	ocfs2_journal_dirty(handle, bh);

	status = ocfs2_commit_trans(OCFS2_SB(sb), handle);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read quota block from a given logical offset.
 *
 * This function acquires ip_alloc_sem and thus it must not be called with a
 * transaction started.
 */
अटल पूर्णांक ocfs2_पढ़ो_quota_block(काष्ठा inode *inode, u64 v_block,
				  काष्ठा buffer_head **bh)
अणु
	पूर्णांक rc = 0;
	काष्ठा buffer_head *पंचांगp = *bh;

	अगर (i_size_पढ़ो(inode) >> inode->i_sb->s_blocksize_bits <= v_block)
		वापस ocfs2_error(inode->i_sb,
				"Quota file %llu is probably corrupted! Requested to read block %Lu but file has size only %Lu\n",
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)v_block,
				(अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode));

	rc = ocfs2_पढ़ो_virt_blocks(inode, v_block, 1, &पंचांगp, 0,
				    ocfs2_validate_quota_block);
	अगर (rc)
		mlog_त्रुटि_सं(rc);

	/* If ocfs2_पढ़ो_virt_blocks() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण

/* Check whether we understand क्रमmat of quota files */
अटल पूर्णांक ocfs2_local_check_quota_file(काष्ठा super_block *sb, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक lmagics[OCFS2_MAXQUOTAS] = OCFS2_LOCAL_QMAGICS;
	अचिन्हित पूर्णांक lversions[OCFS2_MAXQUOTAS] = OCFS2_LOCAL_QVERSIONS;
	अचिन्हित पूर्णांक gmagics[OCFS2_MAXQUOTAS] = OCFS2_GLOBAL_QMAGICS;
	अचिन्हित पूर्णांक gversions[OCFS2_MAXQUOTAS] = OCFS2_GLOBAL_QVERSIONS;
	अचिन्हित पूर्णांक ino[OCFS2_MAXQUOTAS] = अणु USER_QUOTA_SYSTEM_INODE,
					      GROUP_QUOTA_SYSTEM_INODE पूर्ण;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा inode *linode = sb_dqopt(sb)->files[type];
	काष्ठा inode *ginode = शून्य;
	काष्ठा ocfs2_disk_dqheader *dqhead;
	पूर्णांक status, ret = 0;

	/* First check whether we understand local quota file */
	status = ocfs2_पढ़ो_quota_block(linode, 0, &bh);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		mlog(ML_ERROR, "failed to read quota file header (type=%d)\n",
			type);
		जाओ out_err;
	पूर्ण
	dqhead = (काष्ठा ocfs2_disk_dqheader *)(bh->b_data);
	अगर (le32_to_cpu(dqhead->dqh_magic) != lmagics[type]) अणु
		mlog(ML_ERROR, "quota file magic does not match (%u != %u),"
			" type=%d\n", le32_to_cpu(dqhead->dqh_magic),
			lmagics[type], type);
		जाओ out_err;
	पूर्ण
	अगर (le32_to_cpu(dqhead->dqh_version) != lversions[type]) अणु
		mlog(ML_ERROR, "quota file version does not match (%u != %u),"
			" type=%d\n", le32_to_cpu(dqhead->dqh_version),
			lversions[type], type);
		जाओ out_err;
	पूर्ण
	brअन्यथा(bh);
	bh = शून्य;

	/* Next check whether we understand global quota file */
	ginode = ocfs2_get_प्रणाली_file_inode(OCFS2_SB(sb), ino[type],
						OCFS2_INVALID_SLOT);
	अगर (!ginode) अणु
		mlog(ML_ERROR, "cannot get global quota file inode "
				"(type=%d)\n", type);
		जाओ out_err;
	पूर्ण
	/* Since the header is पढ़ो only, we करोn't care about locking */
	status = ocfs2_पढ़ो_quota_block(ginode, 0, &bh);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		mlog(ML_ERROR, "failed to read global quota file header "
				"(type=%d)\n", type);
		जाओ out_err;
	पूर्ण
	dqhead = (काष्ठा ocfs2_disk_dqheader *)(bh->b_data);
	अगर (le32_to_cpu(dqhead->dqh_magic) != gmagics[type]) अणु
		mlog(ML_ERROR, "global quota file magic does not match "
			"(%u != %u), type=%d\n",
			le32_to_cpu(dqhead->dqh_magic), gmagics[type], type);
		जाओ out_err;
	पूर्ण
	अगर (le32_to_cpu(dqhead->dqh_version) != gversions[type]) अणु
		mlog(ML_ERROR, "global quota file version does not match "
			"(%u != %u), type=%d\n",
			le32_to_cpu(dqhead->dqh_version), gversions[type],
			type);
		जाओ out_err;
	पूर्ण

	ret = 1;
out_err:
	brअन्यथा(bh);
	iput(ginode);
	वापस ret;
पूर्ण

/* Release given list of quota file chunks */
अटल व्योम ocfs2_release_local_quota_biपंचांगaps(काष्ठा list_head *head)
अणु
	काष्ठा ocfs2_quota_chunk *pos, *next;

	list_क्रम_each_entry_safe(pos, next, head, qc_chunk) अणु
		list_del(&pos->qc_chunk);
		brअन्यथा(pos->qc_headerbh);
		kmem_cache_मुक्त(ocfs2_qf_chunk_cachep, pos);
	पूर्ण
पूर्ण

/* Load quota biपंचांगaps पूर्णांकo memory */
अटल पूर्णांक ocfs2_load_local_quota_biपंचांगaps(काष्ठा inode *inode,
			काष्ठा ocfs2_local_disk_dqinfo *ldinfo,
			काष्ठा list_head *head)
अणु
	काष्ठा ocfs2_quota_chunk *newchunk;
	पूर्णांक i, status;

	INIT_LIST_HEAD(head);
	क्रम (i = 0; i < le32_to_cpu(ldinfo->dqi_chunks); i++) अणु
		newchunk = kmem_cache_alloc(ocfs2_qf_chunk_cachep, GFP_NOFS);
		अगर (!newchunk) अणु
			ocfs2_release_local_quota_biपंचांगaps(head);
			वापस -ENOMEM;
		पूर्ण
		newchunk->qc_num = i;
		newchunk->qc_headerbh = शून्य;
		status = ocfs2_पढ़ो_quota_block(inode,
				ol_quota_chunk_block(inode->i_sb, i),
				&newchunk->qc_headerbh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			kmem_cache_मुक्त(ocfs2_qf_chunk_cachep, newchunk);
			ocfs2_release_local_quota_biपंचांगaps(head);
			वापस status;
		पूर्ण
		list_add_tail(&newchunk->qc_chunk, head);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम olq_update_info(काष्ठा buffer_head *bh, व्योम *निजी)
अणु
	काष्ठा mem_dqinfo *info = निजी;
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा ocfs2_local_disk_dqinfo *ldinfo;

	ldinfo = (काष्ठा ocfs2_local_disk_dqinfo *)(bh->b_data +
						OCFS2_LOCAL_INFO_OFF);
	spin_lock(&dq_data_lock);
	ldinfo->dqi_flags = cpu_to_le32(oinfo->dqi_flags);
	ldinfo->dqi_chunks = cpu_to_le32(oinfo->dqi_chunks);
	ldinfo->dqi_blocks = cpu_to_le32(oinfo->dqi_blocks);
	spin_unlock(&dq_data_lock);
पूर्ण

अटल पूर्णांक ocfs2_add_recovery_chunk(काष्ठा super_block *sb,
				    काष्ठा ocfs2_local_disk_chunk *dchunk,
				    पूर्णांक chunk,
				    काष्ठा list_head *head)
अणु
	काष्ठा ocfs2_recovery_chunk *rc;

	rc = kदो_स्मृति(माप(काष्ठा ocfs2_recovery_chunk), GFP_NOFS);
	अगर (!rc)
		वापस -ENOMEM;
	rc->rc_chunk = chunk;
	rc->rc_biपंचांगap = kदो_स्मृति(sb->s_blocksize, GFP_NOFS);
	अगर (!rc->rc_biपंचांगap) अणु
		kमुक्त(rc);
		वापस -ENOMEM;
	पूर्ण
	स_नकल(rc->rc_biपंचांगap, dchunk->dqc_biपंचांगap,
	       (ol_chunk_entries(sb) + 7) >> 3);
	list_add_tail(&rc->rc_list, head);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_recovery_list(काष्ठा list_head *head)
अणु
	काष्ठा ocfs2_recovery_chunk *next;
	काष्ठा ocfs2_recovery_chunk *rchunk;

	list_क्रम_each_entry_safe(rchunk, next, head, rc_list) अणु
		list_del(&rchunk->rc_list);
		kमुक्त(rchunk->rc_biपंचांगap);
		kमुक्त(rchunk);
	पूर्ण
पूर्ण

व्योम ocfs2_मुक्त_quota_recovery(काष्ठा ocfs2_quota_recovery *rec)
अणु
	पूर्णांक type;

	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++)
		मुक्त_recovery_list(&(rec->r_list[type]));
	kमुक्त(rec);
पूर्ण

/* Load entries in our quota file we have to recover*/
अटल पूर्णांक ocfs2_recovery_load_quota(काष्ठा inode *lqinode,
				     काष्ठा ocfs2_local_disk_dqinfo *ldinfo,
				     पूर्णांक type,
				     काष्ठा list_head *head)
अणु
	काष्ठा super_block *sb = lqinode->i_sb;
	काष्ठा buffer_head *hbh;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक i, chunks = le32_to_cpu(ldinfo->dqi_chunks);
	पूर्णांक status = 0;

	क्रम (i = 0; i < chunks; i++) अणु
		hbh = शून्य;
		status = ocfs2_पढ़ो_quota_block(lqinode,
						ol_quota_chunk_block(sb, i),
						&hbh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			अवरोध;
		पूर्ण
		dchunk = (काष्ठा ocfs2_local_disk_chunk *)hbh->b_data;
		अगर (le32_to_cpu(dchunk->dqc_मुक्त) < ol_chunk_entries(sb))
			status = ocfs2_add_recovery_chunk(sb, dchunk, i, head);
		brअन्यथा(hbh);
		अगर (status < 0)
			अवरोध;
	पूर्ण
	अगर (status < 0)
		मुक्त_recovery_list(head);
	वापस status;
पूर्ण

अटल काष्ठा ocfs2_quota_recovery *ocfs2_alloc_quota_recovery(व्योम)
अणु
	पूर्णांक type;
	काष्ठा ocfs2_quota_recovery *rec;

	rec = kदो_स्मृति(माप(काष्ठा ocfs2_quota_recovery), GFP_NOFS);
	अगर (!rec)
		वापस शून्य;
	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++)
		INIT_LIST_HEAD(&(rec->r_list[type]));
	वापस rec;
पूर्ण

/* Load inक्रमmation we need क्रम quota recovery पूर्णांकo memory */
काष्ठा ocfs2_quota_recovery *ocfs2_begin_quota_recovery(
						काष्ठा ocfs2_super *osb,
						पूर्णांक slot_num)
अणु
	अचिन्हित पूर्णांक feature[OCFS2_MAXQUOTAS] = अणु
					OCFS2_FEATURE_RO_COMPAT_USRQUOTA,
					OCFS2_FEATURE_RO_COMPAT_GRPQUOTAपूर्ण;
	अचिन्हित पूर्णांक ino[OCFS2_MAXQUOTAS] = अणु LOCAL_USER_QUOTA_SYSTEM_INODE,
					      LOCAL_GROUP_QUOTA_SYSTEM_INODE पूर्ण;
	काष्ठा super_block *sb = osb->sb;
	काष्ठा ocfs2_local_disk_dqinfo *ldinfo;
	काष्ठा inode *lqinode;
	काष्ठा buffer_head *bh;
	पूर्णांक type;
	पूर्णांक status = 0;
	काष्ठा ocfs2_quota_recovery *rec;

	prपूर्णांकk(KERN_NOTICE "ocfs2: Beginning quota recovery on device (%s) for "
	       "slot %u\n", osb->dev_str, slot_num);

	rec = ocfs2_alloc_quota_recovery();
	अगर (!rec)
		वापस ERR_PTR(-ENOMEM);
	/* First init... */

	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++) अणु
		अगर (!OCFS2_HAS_RO_COMPAT_FEATURE(sb, feature[type]))
			जारी;
		/* At this poपूर्णांक, journal of the slot is alपढ़ोy replayed so
		 * we can trust metadata and data of the quota file */
		lqinode = ocfs2_get_प्रणाली_file_inode(osb, ino[type], slot_num);
		अगर (!lqinode) अणु
			status = -ENOENT;
			जाओ out;
		पूर्ण
		status = ocfs2_inode_lock_full(lqinode, शून्य, 1,
					       OCFS2_META_LOCK_RECOVERY);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out_put;
		पूर्ण
		/* Now पढ़ो local header */
		bh = शून्य;
		status = ocfs2_पढ़ो_quota_block(lqinode, 0, &bh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			mlog(ML_ERROR, "failed to read quota file info header "
				"(slot=%d type=%d)\n", slot_num, type);
			जाओ out_lock;
		पूर्ण
		ldinfo = (काष्ठा ocfs2_local_disk_dqinfo *)(bh->b_data +
							OCFS2_LOCAL_INFO_OFF);
		status = ocfs2_recovery_load_quota(lqinode, ldinfo, type,
						   &rec->r_list[type]);
		brअन्यथा(bh);
out_lock:
		ocfs2_inode_unlock(lqinode, 1);
out_put:
		iput(lqinode);
		अगर (status < 0)
			अवरोध;
	पूर्ण
out:
	अगर (status < 0) अणु
		ocfs2_मुक्त_quota_recovery(rec);
		rec = ERR_PTR(status);
	पूर्ण
	वापस rec;
पूर्ण

/* Sync changes in local quota file पूर्णांकo global quota file and
 * reinitialize local quota file.
 * The function expects local quota file to be alपढ़ोy locked and
 * s_umount locked in shared mode. */
अटल पूर्णांक ocfs2_recover_local_quota_file(काष्ठा inode *lqinode,
					  पूर्णांक type,
					  काष्ठा ocfs2_quota_recovery *rec)
अणु
	काष्ठा super_block *sb = lqinode->i_sb;
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	काष्ठा ocfs2_local_disk_dqblk *dqblk;
	काष्ठा dquot *dquot;
	handle_t *handle;
	काष्ठा buffer_head *hbh = शून्य, *qbh = शून्य;
	पूर्णांक status = 0;
	पूर्णांक bit, chunk;
	काष्ठा ocfs2_recovery_chunk *rchunk, *next;
	qमाप_प्रकार spacechange, inodechange;

	trace_ocfs2_recover_local_quota_file((अचिन्हित दीर्घ)lqinode->i_ino, type);

	list_क्रम_each_entry_safe(rchunk, next, &(rec->r_list[type]), rc_list) अणु
		chunk = rchunk->rc_chunk;
		hbh = शून्य;
		status = ocfs2_पढ़ो_quota_block(lqinode,
						ol_quota_chunk_block(sb, chunk),
						&hbh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			अवरोध;
		पूर्ण
		dchunk = (काष्ठा ocfs2_local_disk_chunk *)hbh->b_data;
		क्रम_each_set_bit(bit, rchunk->rc_biपंचांगap, ol_chunk_entries(sb)) अणु
			qbh = शून्य;
			status = ocfs2_पढ़ो_quota_block(lqinode,
						ol_dqblk_block(sb, chunk, bit),
						&qbh);
			अगर (status) अणु
				mlog_त्रुटि_सं(status);
				अवरोध;
			पूर्ण
			dqblk = (काष्ठा ocfs2_local_disk_dqblk *)(qbh->b_data +
				ol_dqblk_block_off(sb, chunk, bit));
			dquot = dqget(sb,
				      make_kqid(&init_user_ns, type,
						le64_to_cpu(dqblk->dqb_id)));
			अगर (IS_ERR(dquot)) अणु
				status = PTR_ERR(dquot);
				mlog(ML_ERROR, "Failed to get quota structure "
				     "for id %u, type %d. Cannot finish quota "
				     "file recovery.\n",
				     (अचिन्हित)le64_to_cpu(dqblk->dqb_id),
				     type);
				जाओ out_put_bh;
			पूर्ण
			status = ocfs2_lock_global_qf(oinfo, 1);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ out_put_dquot;
			पूर्ण

			handle = ocfs2_start_trans(OCFS2_SB(sb),
						   OCFS2_QSYNC_CREDITS);
			अगर (IS_ERR(handle)) अणु
				status = PTR_ERR(handle);
				mlog_त्रुटि_सं(status);
				जाओ out_drop_lock;
			पूर्ण
			करोwn_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
			spin_lock(&dquot->dq_dqb_lock);
			/* Add usage from quota entry पूर्णांकo quota changes
			 * of our node. Auxiliary variables are important
			 * due to चिन्हितness */
			spacechange = le64_to_cpu(dqblk->dqb_spacemod);
			inodechange = le64_to_cpu(dqblk->dqb_inodemod);
			dquot->dq_dqb.dqb_curspace += spacechange;
			dquot->dq_dqb.dqb_curinodes += inodechange;
			spin_unlock(&dquot->dq_dqb_lock);
			/* We want to drop reference held by the crashed
			 * node. Since we have our own reference we know
			 * global काष्ठाure actually won't be मुक्तd. */
			status = ocfs2_global_release_dquot(dquot);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ out_commit;
			पूर्ण
			/* Release local quota file entry */
			status = ocfs2_journal_access_dq(handle,
					INODE_CACHE(lqinode),
					qbh, OCFS2_JOURNAL_ACCESS_WRITE);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ out_commit;
			पूर्ण
			lock_buffer(qbh);
			WARN_ON(!ocfs2_test_bit_unaligned(bit, dchunk->dqc_biपंचांगap));
			ocfs2_clear_bit_unaligned(bit, dchunk->dqc_biपंचांगap);
			le32_add_cpu(&dchunk->dqc_मुक्त, 1);
			unlock_buffer(qbh);
			ocfs2_journal_dirty(handle, qbh);
out_commit:
			up_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
			ocfs2_commit_trans(OCFS2_SB(sb), handle);
out_drop_lock:
			ocfs2_unlock_global_qf(oinfo, 1);
out_put_dquot:
			dqput(dquot);
out_put_bh:
			brअन्यथा(qbh);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		brअन्यथा(hbh);
		list_del(&rchunk->rc_list);
		kमुक्त(rchunk->rc_biपंचांगap);
		kमुक्त(rchunk);
		अगर (status < 0)
			अवरोध;
	पूर्ण
	अगर (status < 0)
		मुक्त_recovery_list(&(rec->r_list[type]));
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* Recover local quota files क्रम given node dअगरferent from us */
पूर्णांक ocfs2_finish_quota_recovery(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_quota_recovery *rec,
				पूर्णांक slot_num)
अणु
	अचिन्हित पूर्णांक ino[OCFS2_MAXQUOTAS] = अणु LOCAL_USER_QUOTA_SYSTEM_INODE,
					      LOCAL_GROUP_QUOTA_SYSTEM_INODE पूर्ण;
	काष्ठा super_block *sb = osb->sb;
	काष्ठा ocfs2_local_disk_dqinfo *ldinfo;
	काष्ठा buffer_head *bh;
	handle_t *handle;
	पूर्णांक type;
	पूर्णांक status = 0;
	काष्ठा inode *lqinode;
	अचिन्हित पूर्णांक flags;

	prपूर्णांकk(KERN_NOTICE "ocfs2: Finishing quota recovery on device (%s) for "
	       "slot %u\n", osb->dev_str, slot_num);

	करोwn_पढ़ो(&sb->s_umount);
	क्रम (type = 0; type < OCFS2_MAXQUOTAS; type++) अणु
		अगर (list_empty(&(rec->r_list[type])))
			जारी;
		trace_ocfs2_finish_quota_recovery(slot_num);
		lqinode = ocfs2_get_प्रणाली_file_inode(osb, ino[type], slot_num);
		अगर (!lqinode) अणु
			status = -ENOENT;
			जाओ out;
		पूर्ण
		status = ocfs2_inode_lock_full(lqinode, शून्य, 1,
						       OCFS2_META_LOCK_NOQUEUE);
		/* Someone अन्यथा is holding the lock? Then he must be
		 * करोing the recovery. Just skip the file... */
		अगर (status == -EAGAIN) अणु
			prपूर्णांकk(KERN_NOTICE "ocfs2: Skipping quota recovery on "
			       "device (%s) for slot %d because quota file is "
			       "locked.\n", osb->dev_str, slot_num);
			status = 0;
			जाओ out_put;
		पूर्ण अन्यथा अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out_put;
		पूर्ण
		/* Now पढ़ो local header */
		bh = शून्य;
		status = ocfs2_पढ़ो_quota_block(lqinode, 0, &bh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			mlog(ML_ERROR, "failed to read quota file info header "
				"(slot=%d type=%d)\n", slot_num, type);
			जाओ out_lock;
		पूर्ण
		ldinfo = (काष्ठा ocfs2_local_disk_dqinfo *)(bh->b_data +
							OCFS2_LOCAL_INFO_OFF);
		/* Is recovery still needed? */
		flags = le32_to_cpu(ldinfo->dqi_flags);
		अगर (!(flags & OLQF_CLEAN))
			status = ocfs2_recover_local_quota_file(lqinode,
								type,
								rec);
		/* We करोn't want to mark file as clean when it is actually
		 * active */
		अगर (slot_num == osb->slot_num)
			जाओ out_bh;
		/* Mark quota file as clean अगर we are recovering quota file of
		 * some other node. */
		handle = ocfs2_start_trans(osb,
					   OCFS2_LOCAL_QINFO_WRITE_CREDITS);
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			mlog_त्रुटि_सं(status);
			जाओ out_bh;
		पूर्ण
		status = ocfs2_journal_access_dq(handle, INODE_CACHE(lqinode),
						 bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out_trans;
		पूर्ण
		lock_buffer(bh);
		ldinfo->dqi_flags = cpu_to_le32(flags | OLQF_CLEAN);
		unlock_buffer(bh);
		ocfs2_journal_dirty(handle, bh);
out_trans:
		ocfs2_commit_trans(osb, handle);
out_bh:
		brअन्यथा(bh);
out_lock:
		ocfs2_inode_unlock(lqinode, 1);
out_put:
		iput(lqinode);
		अगर (status < 0)
			अवरोध;
	पूर्ण
out:
	up_पढ़ो(&sb->s_umount);
	kमुक्त(rec);
	वापस status;
पूर्ण

/* Read inक्रमmation header from quota file */
अटल पूर्णांक ocfs2_local_पढ़ो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा ocfs2_local_disk_dqinfo *ldinfo;
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo;
	काष्ठा inode *lqinode = sb_dqopt(sb)->files[type];
	पूर्णांक status;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_quota_recovery *rec;
	पूर्णांक locked = 0;

	info->dqi_max_spc_limit = 0x7fffffffffffffffLL;
	info->dqi_max_ino_limit = 0x7fffffffffffffffLL;
	oinfo = kदो_स्मृति(माप(काष्ठा ocfs2_mem_dqinfo), GFP_NOFS);
	अगर (!oinfo) अणु
		mlog(ML_ERROR, "failed to allocate memory for ocfs2 quota"
			       " info.");
		जाओ out_err;
	पूर्ण
	info->dqi_priv = oinfo;
	oinfo->dqi_type = type;
	INIT_LIST_HEAD(&oinfo->dqi_chunk);
	oinfo->dqi_rec = शून्य;
	oinfo->dqi_lqi_bh = शून्य;
	oinfo->dqi_libh = शून्य;

	status = ocfs2_global_पढ़ो_info(sb, type);
	अगर (status < 0)
		जाओ out_err;

	status = ocfs2_inode_lock(lqinode, &oinfo->dqi_lqi_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण
	locked = 1;

	/* Now पढ़ो local header */
	status = ocfs2_पढ़ो_quota_block(lqinode, 0, &bh);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		mlog(ML_ERROR, "failed to read quota file info header "
			"(type=%d)\n", type);
		जाओ out_err;
	पूर्ण
	ldinfo = (काष्ठा ocfs2_local_disk_dqinfo *)(bh->b_data +
						OCFS2_LOCAL_INFO_OFF);
	oinfo->dqi_flags = le32_to_cpu(ldinfo->dqi_flags);
	oinfo->dqi_chunks = le32_to_cpu(ldinfo->dqi_chunks);
	oinfo->dqi_blocks = le32_to_cpu(ldinfo->dqi_blocks);
	oinfo->dqi_libh = bh;

	/* We crashed when using local quota file? */
	अगर (!(oinfo->dqi_flags & OLQF_CLEAN)) अणु
		rec = OCFS2_SB(sb)->quota_rec;
		अगर (!rec) अणु
			rec = ocfs2_alloc_quota_recovery();
			अगर (!rec) अणु
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				जाओ out_err;
			पूर्ण
			OCFS2_SB(sb)->quota_rec = rec;
		पूर्ण

		status = ocfs2_recovery_load_quota(lqinode, ldinfo, type,
                                                   &rec->r_list[type]);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out_err;
		पूर्ण
	पूर्ण

	status = ocfs2_load_local_quota_biपंचांगaps(lqinode,
						ldinfo,
						&oinfo->dqi_chunk);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	/* Now mark quota file as used */
	oinfo->dqi_flags &= ~OLQF_CLEAN;
	status = ocfs2_modअगरy_bh(lqinode, bh, olq_update_info, info);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	वापस 0;
out_err:
	अगर (oinfo) अणु
		iput(oinfo->dqi_gqinode);
		ocfs2_simple_drop_lockres(OCFS2_SB(sb), &oinfo->dqi_gqlock);
		ocfs2_lock_res_मुक्त(&oinfo->dqi_gqlock);
		brअन्यथा(oinfo->dqi_lqi_bh);
		अगर (locked)
			ocfs2_inode_unlock(lqinode, 1);
		ocfs2_release_local_quota_biपंचांगaps(&oinfo->dqi_chunk);
		kमुक्त(oinfo);
	पूर्ण
	brअन्यथा(bh);
	वापस -1;
पूर्ण

/* Write local info to quota file */
अटल पूर्णांक ocfs2_local_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा buffer_head *bh = ((काष्ठा ocfs2_mem_dqinfo *)info->dqi_priv)
						->dqi_libh;
	पूर्णांक status;

	status = ocfs2_modअगरy_bh(sb_dqopt(sb)->files[type], bh, olq_update_info,
				 info);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* Release info from memory */
अटल पूर्णांक ocfs2_local_मुक्त_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा ocfs2_quota_chunk *chunk;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक mark_clean = 1, len;
	पूर्णांक status;

	iput(oinfo->dqi_gqinode);
	ocfs2_simple_drop_lockres(OCFS2_SB(sb), &oinfo->dqi_gqlock);
	ocfs2_lock_res_मुक्त(&oinfo->dqi_gqlock);
	list_क्रम_each_entry(chunk, &oinfo->dqi_chunk, qc_chunk) अणु
		dchunk = (काष्ठा ocfs2_local_disk_chunk *)
					(chunk->qc_headerbh->b_data);
		अगर (chunk->qc_num < oinfo->dqi_chunks - 1) अणु
			len = ol_chunk_entries(sb);
		पूर्ण अन्यथा अणु
			len = (oinfo->dqi_blocks -
			       ol_quota_chunk_block(sb, chunk->qc_num) - 1)
			      * ol_quota_entries_per_block(sb);
		पूर्ण
		/* Not all entries मुक्त? Bug! */
		अगर (le32_to_cpu(dchunk->dqc_मुक्त) != len) अणु
			mlog(ML_ERROR, "releasing quota file with used "
					"entries (type=%d)\n", type);
			mark_clean = 0;
		पूर्ण
	पूर्ण
	ocfs2_release_local_quota_biपंचांगaps(&oinfo->dqi_chunk);

	/*
	 * s_umount held in exclusive mode protects us against racing with
	 * recovery thपढ़ो...
	 */
	अगर (oinfo->dqi_rec) अणु
		ocfs2_मुक्त_quota_recovery(oinfo->dqi_rec);
		mark_clean = 0;
	पूर्ण

	अगर (!mark_clean)
		जाओ out;

	/* Mark local file as clean */
	oinfo->dqi_flags |= OLQF_CLEAN;
	status = ocfs2_modअगरy_bh(sb_dqopt(sb)->files[type],
				 oinfo->dqi_libh,
				 olq_update_info,
				 info);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

out:
	ocfs2_inode_unlock(sb_dqopt(sb)->files[type], 1);
	brअन्यथा(oinfo->dqi_libh);
	brअन्यथा(oinfo->dqi_lqi_bh);
	kमुक्त(oinfo);
	वापस 0;
पूर्ण

अटल व्योम olq_set_dquot(काष्ठा buffer_head *bh, व्योम *निजी)
अणु
	काष्ठा ocfs2_dquot *od = निजी;
	काष्ठा ocfs2_local_disk_dqblk *dqblk;
	काष्ठा super_block *sb = od->dq_dquot.dq_sb;

	dqblk = (काष्ठा ocfs2_local_disk_dqblk *)(bh->b_data
		+ ol_dqblk_block_offset(sb, od->dq_local_off));

	dqblk->dqb_id = cpu_to_le64(from_kqid(&init_user_ns,
					      od->dq_dquot.dq_id));
	spin_lock(&od->dq_dquot.dq_dqb_lock);
	dqblk->dqb_spacemod = cpu_to_le64(od->dq_dquot.dq_dqb.dqb_curspace -
					  od->dq_origspace);
	dqblk->dqb_inodemod = cpu_to_le64(od->dq_dquot.dq_dqb.dqb_curinodes -
					  od->dq_originodes);
	spin_unlock(&od->dq_dquot.dq_dqb_lock);
	trace_olq_set_dquot(
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(dqblk->dqb_spacemod),
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(dqblk->dqb_inodemod),
		from_kqid(&init_user_ns, od->dq_dquot.dq_id));
पूर्ण

/* Write dquot to local quota file */
पूर्णांक ocfs2_local_ग_लिखो_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा super_block *sb = dquot->dq_sb;
	काष्ठा ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	काष्ठा buffer_head *bh;
	काष्ठा inode *lqinode = sb_dqopt(sb)->files[dquot->dq_id.type];
	पूर्णांक status;

	status = ocfs2_पढ़ो_quota_phys_block(lqinode, od->dq_local_phys_blk,
					     &bh);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	status = ocfs2_modअगरy_bh(lqinode, bh, olq_set_dquot, od);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
out:
	brअन्यथा(bh);
	वापस status;
पूर्ण

/* Find मुक्त entry in local quota file */
अटल काष्ठा ocfs2_quota_chunk *ocfs2_find_मुक्त_entry(काष्ठा super_block *sb,
						       पूर्णांक type,
						       पूर्णांक *offset)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा ocfs2_quota_chunk *chunk;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक found = 0, len;

	list_क्रम_each_entry(chunk, &oinfo->dqi_chunk, qc_chunk) अणु
		dchunk = (काष्ठा ocfs2_local_disk_chunk *)
						chunk->qc_headerbh->b_data;
		अगर (le32_to_cpu(dchunk->dqc_मुक्त) > 0) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस शून्य;

	अगर (chunk->qc_num < oinfo->dqi_chunks - 1) अणु
		len = ol_chunk_entries(sb);
	पूर्ण अन्यथा अणु
		len = (oinfo->dqi_blocks -
		       ol_quota_chunk_block(sb, chunk->qc_num) - 1)
		      * ol_quota_entries_per_block(sb);
	पूर्ण

	found = ocfs2_find_next_zero_bit_unaligned(dchunk->dqc_biपंचांगap, len, 0);
	/* We failed? */
	अगर (found == len) अणु
		mlog(ML_ERROR, "Did not find empty entry in chunk %d with %u"
		     " entries free (type=%d)\n", chunk->qc_num,
		     le32_to_cpu(dchunk->dqc_मुक्त), type);
		वापस ERR_PTR(-EIO);
	पूर्ण
	*offset = found;
	वापस chunk;
पूर्ण

/* Add new chunk to the local quota file */
अटल काष्ठा ocfs2_quota_chunk *ocfs2_local_quota_add_chunk(
							काष्ठा super_block *sb,
							पूर्णांक type,
							पूर्णांक *offset)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा inode *lqinode = sb_dqopt(sb)->files[type];
	काष्ठा ocfs2_quota_chunk *chunk = शून्य;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक status;
	handle_t *handle;
	काष्ठा buffer_head *bh = शून्य, *dbh = शून्य;
	u64 p_blkno;

	/* We are रक्षित by dqio_sem so no locking needed */
	status = ocfs2_extend_no_holes(lqinode, शून्य,
				       i_size_पढ़ो(lqinode) + 2 * sb->s_blocksize,
				       i_size_पढ़ो(lqinode));
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	status = ocfs2_simple_size_update(lqinode, oinfo->dqi_lqi_bh,
					  i_size_पढ़ो(lqinode) + 2 * sb->s_blocksize);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	chunk = kmem_cache_alloc(ocfs2_qf_chunk_cachep, GFP_NOFS);
	अगर (!chunk) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	/* Local quota info and two new blocks we initialize */
	handle = ocfs2_start_trans(OCFS2_SB(sb),
			OCFS2_LOCAL_QINFO_WRITE_CREDITS +
			2 * OCFS2_QUOTA_BLOCK_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	/* Initialize chunk header */
	status = ocfs2_extent_map_get_blocks(lqinode, oinfo->dqi_blocks,
					     &p_blkno, शून्य, शून्य);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	bh = sb_getblk(sb, p_blkno);
	अगर (!bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	dchunk = (काष्ठा ocfs2_local_disk_chunk *)bh->b_data;
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(lqinode), bh);
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(lqinode), bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	lock_buffer(bh);
	dchunk->dqc_मुक्त = cpu_to_le32(ol_quota_entries_per_block(sb));
	स_रखो(dchunk->dqc_biपंचांगap, 0,
	       sb->s_blocksize - माप(काष्ठा ocfs2_local_disk_chunk) -
	       OCFS2_QBLK_RESERVED_SPACE);
	unlock_buffer(bh);
	ocfs2_journal_dirty(handle, bh);

	/* Initialize new block with काष्ठाures */
	status = ocfs2_extent_map_get_blocks(lqinode, oinfo->dqi_blocks + 1,
					     &p_blkno, शून्य, शून्य);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	dbh = sb_getblk(sb, p_blkno);
	अगर (!dbh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(lqinode), dbh);
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(lqinode), dbh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	lock_buffer(dbh);
	स_रखो(dbh->b_data, 0, sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE);
	unlock_buffer(dbh);
	ocfs2_journal_dirty(handle, dbh);

	/* Update local quotafile info */
	oinfo->dqi_blocks += 2;
	oinfo->dqi_chunks++;
	status = ocfs2_local_ग_लिखो_info(sb, type);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	status = ocfs2_commit_trans(OCFS2_SB(sb), handle);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	list_add_tail(&chunk->qc_chunk, &oinfo->dqi_chunk);
	chunk->qc_num = list_entry(chunk->qc_chunk.prev,
				   काष्ठा ocfs2_quota_chunk,
				   qc_chunk)->qc_num + 1;
	chunk->qc_headerbh = bh;
	*offset = 0;
	वापस chunk;
out_trans:
	ocfs2_commit_trans(OCFS2_SB(sb), handle);
out:
	brअन्यथा(bh);
	brअन्यथा(dbh);
	kmem_cache_मुक्त(ocfs2_qf_chunk_cachep, chunk);
	वापस ERR_PTR(status);
पूर्ण

/* Find मुक्त entry in local quota file */
अटल काष्ठा ocfs2_quota_chunk *ocfs2_extend_local_quota_file(
						       काष्ठा super_block *sb,
						       पूर्णांक type,
						       पूर्णांक *offset)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा ocfs2_quota_chunk *chunk;
	काष्ठा inode *lqinode = sb_dqopt(sb)->files[type];
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक epb = ol_quota_entries_per_block(sb);
	अचिन्हित पूर्णांक chunk_blocks;
	काष्ठा buffer_head *bh;
	u64 p_blkno;
	पूर्णांक status;
	handle_t *handle;

	अगर (list_empty(&oinfo->dqi_chunk))
		वापस ocfs2_local_quota_add_chunk(sb, type, offset);
	/* Is the last chunk full? */
	chunk = list_entry(oinfo->dqi_chunk.prev,
			काष्ठा ocfs2_quota_chunk, qc_chunk);
	chunk_blocks = oinfo->dqi_blocks -
			ol_quota_chunk_block(sb, chunk->qc_num) - 1;
	अगर (ol_chunk_blocks(sb) == chunk_blocks)
		वापस ocfs2_local_quota_add_chunk(sb, type, offset);

	/* We are रक्षित by dqio_sem so no locking needed */
	status = ocfs2_extend_no_holes(lqinode, शून्य,
				       i_size_पढ़ो(lqinode) + sb->s_blocksize,
				       i_size_पढ़ो(lqinode));
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	status = ocfs2_simple_size_update(lqinode, oinfo->dqi_lqi_bh,
					  i_size_पढ़ो(lqinode) + sb->s_blocksize);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	/* Get buffer from the just added block */
	status = ocfs2_extent_map_get_blocks(lqinode, oinfo->dqi_blocks,
					     &p_blkno, शून्य, शून्य);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	bh = sb_getblk(sb, p_blkno);
	अगर (!bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(lqinode), bh);

	/* Local quota info, chunk header and the new block we initialize */
	handle = ocfs2_start_trans(OCFS2_SB(sb),
			OCFS2_LOCAL_QINFO_WRITE_CREDITS +
			2 * OCFS2_QUOTA_BLOCK_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	/* Zero created block */
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(lqinode), bh,
				 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	lock_buffer(bh);
	स_रखो(bh->b_data, 0, sb->s_blocksize);
	unlock_buffer(bh);
	ocfs2_journal_dirty(handle, bh);

	/* Update chunk header */
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(lqinode),
					 chunk->qc_headerbh,
				 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण

	dchunk = (काष्ठा ocfs2_local_disk_chunk *)chunk->qc_headerbh->b_data;
	lock_buffer(chunk->qc_headerbh);
	le32_add_cpu(&dchunk->dqc_मुक्त, ol_quota_entries_per_block(sb));
	unlock_buffer(chunk->qc_headerbh);
	ocfs2_journal_dirty(handle, chunk->qc_headerbh);

	/* Update file header */
	oinfo->dqi_blocks++;
	status = ocfs2_local_ग_लिखो_info(sb, type);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण

	status = ocfs2_commit_trans(OCFS2_SB(sb), handle);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	*offset = chunk_blocks * epb;
	वापस chunk;
out_trans:
	ocfs2_commit_trans(OCFS2_SB(sb), handle);
out:
	वापस ERR_PTR(status);
पूर्ण

अटल व्योम olq_alloc_dquot(काष्ठा buffer_head *bh, व्योम *निजी)
अणु
	पूर्णांक *offset = निजी;
	काष्ठा ocfs2_local_disk_chunk *dchunk;

	dchunk = (काष्ठा ocfs2_local_disk_chunk *)bh->b_data;
	ocfs2_set_bit_unaligned(*offset, dchunk->dqc_biपंचांगap);
	le32_add_cpu(&dchunk->dqc_मुक्त, -1);
पूर्ण

/* Create dquot in the local file क्रम given id */
पूर्णांक ocfs2_create_local_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा super_block *sb = dquot->dq_sb;
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा inode *lqinode = sb_dqopt(sb)->files[type];
	काष्ठा ocfs2_quota_chunk *chunk;
	काष्ठा ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	पूर्णांक offset;
	पूर्णांक status;
	u64 pcount;

	करोwn_ग_लिखो(&OCFS2_I(lqinode)->ip_alloc_sem);
	chunk = ocfs2_find_मुक्त_entry(sb, type, &offset);
	अगर (!chunk) अणु
		chunk = ocfs2_extend_local_quota_file(sb, type, &offset);
		अगर (IS_ERR(chunk)) अणु
			status = PTR_ERR(chunk);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ERR(chunk)) अणु
		status = PTR_ERR(chunk);
		जाओ out;
	पूर्ण
	od->dq_local_off = ol_dqblk_off(sb, chunk->qc_num, offset);
	od->dq_chunk = chunk;
	status = ocfs2_extent_map_get_blocks(lqinode,
				     ol_dqblk_block(sb, chunk->qc_num, offset),
				     &od->dq_local_phys_blk,
				     &pcount,
				     शून्य);

	/* Initialize dquot काष्ठाure on disk */
	status = ocfs2_local_ग_लिखो_dquot(dquot);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	/* Mark काष्ठाure as allocated */
	status = ocfs2_modअगरy_bh(lqinode, chunk->qc_headerbh, olq_alloc_dquot,
				 &offset);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
out:
	up_ग_लिखो(&OCFS2_I(lqinode)->ip_alloc_sem);
	वापस status;
पूर्ण

/*
 * Release dquot काष्ठाure from local quota file. ocfs2_release_dquot() has
 * alपढ़ोy started a transaction and written all changes to global quota file
 */
पूर्णांक ocfs2_local_release_dquot(handle_t *handle, काष्ठा dquot *dquot)
अणु
	पूर्णांक status;
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा ocfs2_dquot *od = OCFS2_DQUOT(dquot);
	काष्ठा super_block *sb = dquot->dq_sb;
	काष्ठा ocfs2_local_disk_chunk *dchunk;
	पूर्णांक offset;

	status = ocfs2_journal_access_dq(handle,
			INODE_CACHE(sb_dqopt(sb)->files[type]),
			od->dq_chunk->qc_headerbh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	offset = ol_dqblk_chunk_off(sb, od->dq_chunk->qc_num,
					     od->dq_local_off);
	dchunk = (काष्ठा ocfs2_local_disk_chunk *)
			(od->dq_chunk->qc_headerbh->b_data);
	/* Mark काष्ठाure as मुक्तd */
	lock_buffer(od->dq_chunk->qc_headerbh);
	ocfs2_clear_bit_unaligned(offset, dchunk->dqc_biपंचांगap);
	le32_add_cpu(&dchunk->dqc_मुक्त, 1);
	unlock_buffer(od->dq_chunk->qc_headerbh);
	ocfs2_journal_dirty(handle, od->dq_chunk->qc_headerbh);

out:
	वापस status;
पूर्ण

अटल स्थिर काष्ठा quota_क्रमmat_ops ocfs2_क्रमmat_ops = अणु
	.check_quota_file	= ocfs2_local_check_quota_file,
	.पढ़ो_file_info		= ocfs2_local_पढ़ो_info,
	.ग_लिखो_file_info	= ocfs2_global_ग_लिखो_info,
	.मुक्त_file_info		= ocfs2_local_मुक्त_info,
पूर्ण;

काष्ठा quota_क्रमmat_type ocfs2_quota_क्रमmat = अणु
	.qf_fmt_id = QFMT_OCFS2,
	.qf_ops = &ocfs2_क्रमmat_ops,
	.qf_owner = THIS_MODULE
पूर्ण;
