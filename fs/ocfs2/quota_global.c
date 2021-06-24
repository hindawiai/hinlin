<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Implementation of operations over global quota file
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/quota.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/dqblk_qtree.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/llist.h>
#समावेश <linux/iversion.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2_fs.h"
#समावेश "ocfs2.h"
#समावेश "alloc.h"
#समावेश "blockcheck.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "file.h"
#समावेश "sysfile.h"
#समावेश "dlmglue.h"
#समावेश "uptodate.h"
#समावेश "super.h"
#समावेश "buffer_head_io.h"
#समावेश "quota.h"
#समावेश "ocfs2_trace.h"

/*
 * Locking of quotas with OCFS2 is rather complex. Here are rules that
 * should be obeyed by all the functions:
 * - any ग_लिखो of quota काष्ठाure (either to local or global file) is रक्षित
 *   by dqio_sem or dquot->dq_lock.
 * - any modअगरication of global quota file holds inode cluster lock, i_mutex,
 *   and ip_alloc_sem of the global quota file (achieved by
 *   ocfs2_lock_global_qf). It also has to hold qinfo_lock.
 * - an allocation of new blocks क्रम local quota file is रक्षित by
 *   its ip_alloc_sem
 *
 * A rough sketch of locking dependencies (lf = local file, gf = global file):
 * Normal fileप्रणाली operation:
 *   start_trans -> dqio_sem -> ग_लिखो to lf
 * Syncing of local and global file:
 *   ocfs2_lock_global_qf -> start_trans -> dqio_sem -> qinfo_lock ->
 *     ग_लिखो to gf
 *						       -> ग_लिखो to lf
 * Acquire dquot क्रम the first समय:
 *   dq_lock -> ocfs2_lock_global_qf -> qinfo_lock -> पढ़ो from gf
 *				     -> alloc space क्रम gf
 *				     -> start_trans -> qinfo_lock -> ग_लिखो to gf
 *	     -> ip_alloc_sem of lf -> alloc space क्रम lf
 *	     -> ग_लिखो to lf
 * Release last reference to dquot:
 *   dq_lock -> ocfs2_lock_global_qf -> start_trans -> qinfo_lock -> ग_लिखो to gf
 *	     -> ग_लिखो to lf
 * Note that all the above operations also hold the inode cluster lock of lf.
 * Recovery:
 *   inode cluster lock of recovered lf
 *     -> पढ़ो biपंचांगaps -> ip_alloc_sem of lf
 *     -> ocfs2_lock_global_qf -> start_trans -> dqio_sem -> qinfo_lock ->
 *        ग_लिखो to gf
 */

अटल व्योम qsync_work_fn(काष्ठा work_काष्ठा *work);

अटल व्योम ocfs2_global_disk2memdqb(काष्ठा dquot *dquot, व्योम *dp)
अणु
	काष्ठा ocfs2_global_disk_dqblk *d = dp;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;

	/* Update from disk only entries not set by the admin */
	अगर (!test_bit(DQ_LASTSET_B + QIF_ILIMITS_B, &dquot->dq_flags)) अणु
		m->dqb_ihardlimit = le64_to_cpu(d->dqb_ihardlimit);
		m->dqb_isoftlimit = le64_to_cpu(d->dqb_isoftlimit);
	पूर्ण
	अगर (!test_bit(DQ_LASTSET_B + QIF_INODES_B, &dquot->dq_flags))
		m->dqb_curinodes = le64_to_cpu(d->dqb_curinodes);
	अगर (!test_bit(DQ_LASTSET_B + QIF_BLIMITS_B, &dquot->dq_flags)) अणु
		m->dqb_bhardlimit = le64_to_cpu(d->dqb_bhardlimit);
		m->dqb_bsoftlimit = le64_to_cpu(d->dqb_bsoftlimit);
	पूर्ण
	अगर (!test_bit(DQ_LASTSET_B + QIF_SPACE_B, &dquot->dq_flags))
		m->dqb_curspace = le64_to_cpu(d->dqb_curspace);
	अगर (!test_bit(DQ_LASTSET_B + QIF_BTIME_B, &dquot->dq_flags))
		m->dqb_bसमय = le64_to_cpu(d->dqb_bसमय);
	अगर (!test_bit(DQ_LASTSET_B + QIF_ITIME_B, &dquot->dq_flags))
		m->dqb_iसमय = le64_to_cpu(d->dqb_iसमय);
	OCFS2_DQUOT(dquot)->dq_use_count = le32_to_cpu(d->dqb_use_count);
पूर्ण

अटल व्योम ocfs2_global_mem2diskdqb(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा ocfs2_global_disk_dqblk *d = dp;
	काष्ठा mem_dqblk *m = &dquot->dq_dqb;

	d->dqb_id = cpu_to_le32(from_kqid(&init_user_ns, dquot->dq_id));
	d->dqb_use_count = cpu_to_le32(OCFS2_DQUOT(dquot)->dq_use_count);
	d->dqb_ihardlimit = cpu_to_le64(m->dqb_ihardlimit);
	d->dqb_isoftlimit = cpu_to_le64(m->dqb_isoftlimit);
	d->dqb_curinodes = cpu_to_le64(m->dqb_curinodes);
	d->dqb_bhardlimit = cpu_to_le64(m->dqb_bhardlimit);
	d->dqb_bsoftlimit = cpu_to_le64(m->dqb_bsoftlimit);
	d->dqb_curspace = cpu_to_le64(m->dqb_curspace);
	d->dqb_bसमय = cpu_to_le64(m->dqb_bसमय);
	d->dqb_iसमय = cpu_to_le64(m->dqb_iसमय);
	d->dqb_pad1 = d->dqb_pad2 = 0;
पूर्ण

अटल पूर्णांक ocfs2_global_is_id(व्योम *dp, काष्ठा dquot *dquot)
अणु
	काष्ठा ocfs2_global_disk_dqblk *d = dp;
	काष्ठा ocfs2_mem_dqinfo *oinfo =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;

	अगर (qtree_entry_unused(&oinfo->dqi_gi, dp))
		वापस 0;

	वापस qid_eq(make_kqid(&init_user_ns, dquot->dq_id.type,
				le32_to_cpu(d->dqb_id)),
		      dquot->dq_id);
पूर्ण

स्थिर काष्ठा qtree_fmt_operations ocfs2_global_ops = अणु
	.mem2disk_dqblk = ocfs2_global_mem2diskdqb,
	.disk2mem_dqblk = ocfs2_global_disk2memdqb,
	.is_id = ocfs2_global_is_id,
पूर्ण;

पूर्णांक ocfs2_validate_quota_block(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	काष्ठा ocfs2_disk_dqtrailer *dqt =
		ocfs2_block_dqtrailer(sb->s_blocksize, bh->b_data);

	trace_ocfs2_validate_quota_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	वापस ocfs2_validate_meta_ecc(sb, bh->b_data, &dqt->dq_check);
पूर्ण

पूर्णांक ocfs2_पढ़ो_quota_phys_block(काष्ठा inode *inode, u64 p_block,
				काष्ठा buffer_head **bhp)
अणु
	पूर्णांक rc;

	*bhp = शून्य;
	rc = ocfs2_पढ़ो_blocks(INODE_CACHE(inode), p_block, 1, bhp, 0,
			       ocfs2_validate_quota_block);
	अगर (rc)
		mlog_त्रुटि_सं(rc);
	वापस rc;
पूर्ण

/* Read data from global quotafile - aव्योम pagecache and such because we cannot
 * afक्रमd acquiring the locks... We use quota cluster lock to serialize
 * operations. Caller is responsible क्रम acquiring it. */
sमाप_प्रकार ocfs2_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			 माप_प्रकार len, loff_t off)
अणु
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	काष्ठा inode *gqinode = oinfo->dqi_gqinode;
	loff_t i_size = i_size_पढ़ो(gqinode);
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	sector_t blk = off >> sb->s_blocksize_bits;
	पूर्णांक err = 0;
	काष्ठा buffer_head *bh;
	माप_प्रकार toपढ़ो, tocopy;
	u64 pblock = 0, pcount = 0;

	अगर (off > i_size)
		वापस 0;
	अगर (off + len > i_size)
		len = i_size - off;
	toपढ़ो = len;
	जबतक (toपढ़ो > 0) अणु
		tocopy = min_t(माप_प्रकार, (sb->s_blocksize - offset), toपढ़ो);
		अगर (!pcount) अणु
			err = ocfs2_extent_map_get_blocks(gqinode, blk, &pblock,
							  &pcount, शून्य);
			अगर (err) अणु
				mlog_त्रुटि_सं(err);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			pcount--;
			pblock++;
		पूर्ण
		bh = शून्य;
		err = ocfs2_पढ़ो_quota_phys_block(gqinode, pblock, &bh);
		अगर (err) अणु
			mlog_त्रुटि_सं(err);
			वापस err;
		पूर्ण
		स_नकल(data, bh->b_data + offset, tocopy);
		brअन्यथा(bh);
		offset = 0;
		toपढ़ो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
	वापस len;
पूर्ण

/* Write to quotafile (we know the transaction is alपढ़ोy started and has
 * enough credits) */
sमाप_प्रकार ocfs2_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
			  स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा inode *gqinode = oinfo->dqi_gqinode;
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	sector_t blk = off >> sb->s_blocksize_bits;
	पूर्णांक err = 0, new = 0, ja_type;
	काष्ठा buffer_head *bh = शून्य;
	handle_t *handle = journal_current_handle();
	u64 pblock, pcount;

	अगर (!handle) अणु
		mlog(ML_ERROR, "Quota write (off=%llu, len=%llu) cancelled "
		     "because transaction was not started.\n",
		     (अचिन्हित दीर्घ दीर्घ)off, (अचिन्हित दीर्घ दीर्घ)len);
		वापस -EIO;
	पूर्ण
	अगर (len > sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE - offset) अणु
		WARN_ON(1);
		len = sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE - offset;
	पूर्ण

	अगर (i_size_पढ़ो(gqinode) < off + len) अणु
		loff_t rounded_end =
				ocfs2_align_bytes_to_blocks(sb, off + len);

		/* Space is alपढ़ोy allocated in ocfs2_acquire_dquot() */
		err = ocfs2_simple_size_update(gqinode,
					       oinfo->dqi_gqi_bh,
					       rounded_end);
		अगर (err < 0)
			जाओ out;
		new = 1;
	पूर्ण
	err = ocfs2_extent_map_get_blocks(gqinode, blk, &pblock, &pcount, शून्य);
	अगर (err) अणु
		mlog_त्रुटि_सं(err);
		जाओ out;
	पूर्ण
	/* Not rewriting whole block? */
	अगर ((offset || len < sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE) &&
	    !new) अणु
		err = ocfs2_पढ़ो_quota_phys_block(gqinode, pblock, &bh);
		ja_type = OCFS2_JOURNAL_ACCESS_WRITE;
	पूर्ण अन्यथा अणु
		bh = sb_getblk(sb, pblock);
		अगर (!bh)
			err = -ENOMEM;
		ja_type = OCFS2_JOURNAL_ACCESS_CREATE;
	पूर्ण
	अगर (err) अणु
		mlog_त्रुटि_सं(err);
		जाओ out;
	पूर्ण
	lock_buffer(bh);
	अगर (new)
		स_रखो(bh->b_data, 0, sb->s_blocksize);
	स_नकल(bh->b_data + offset, data, len);
	flush_dcache_page(bh->b_page);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);
	ocfs2_set_buffer_uptodate(INODE_CACHE(gqinode), bh);
	err = ocfs2_journal_access_dq(handle, INODE_CACHE(gqinode), bh,
				      ja_type);
	अगर (err < 0) अणु
		brअन्यथा(bh);
		जाओ out;
	पूर्ण
	ocfs2_journal_dirty(handle, bh);
	brअन्यथा(bh);
out:
	अगर (err) अणु
		mlog_त्रुटि_सं(err);
		वापस err;
	पूर्ण
	inode_inc_iversion(gqinode);
	ocfs2_mark_inode_dirty(handle, gqinode, oinfo->dqi_gqi_bh);
	वापस len;
पूर्ण

पूर्णांक ocfs2_lock_global_qf(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex)
अणु
	पूर्णांक status;
	काष्ठा buffer_head *bh = शून्य;

	status = ocfs2_inode_lock(oinfo->dqi_gqinode, &bh, ex);
	अगर (status < 0)
		वापस status;
	spin_lock(&dq_data_lock);
	अगर (!oinfo->dqi_gqi_count++)
		oinfo->dqi_gqi_bh = bh;
	अन्यथा
		WARN_ON(bh != oinfo->dqi_gqi_bh);
	spin_unlock(&dq_data_lock);
	अगर (ex) अणु
		inode_lock(oinfo->dqi_gqinode);
		करोwn_ग_लिखो(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ocfs2_unlock_global_qf(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex)
अणु
	अगर (ex) अणु
		up_ग_लिखो(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
		inode_unlock(oinfo->dqi_gqinode);
	पूर्ण अन्यथा अणु
		up_पढ़ो(&OCFS2_I(oinfo->dqi_gqinode)->ip_alloc_sem);
	पूर्ण
	ocfs2_inode_unlock(oinfo->dqi_gqinode, ex);
	brअन्यथा(oinfo->dqi_gqi_bh);
	spin_lock(&dq_data_lock);
	अगर (!--oinfo->dqi_gqi_count)
		oinfo->dqi_gqi_bh = शून्य;
	spin_unlock(&dq_data_lock);
पूर्ण

/* Read inक्रमmation header from global quota file */
पूर्णांक ocfs2_global_पढ़ो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *gqinode = शून्य;
	अचिन्हित पूर्णांक ino[OCFS2_MAXQUOTAS] = अणु USER_QUOTA_SYSTEM_INODE,
					      GROUP_QUOTA_SYSTEM_INODE पूर्ण;
	काष्ठा ocfs2_global_disk_dqinfo dinfo;
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	u64 pcount;
	पूर्णांक status;

	/* Read global header */
	gqinode = ocfs2_get_प्रणाली_file_inode(OCFS2_SB(sb), ino[type],
			OCFS2_INVALID_SLOT);
	अगर (!gqinode) अणु
		mlog(ML_ERROR, "failed to get global quota inode (type=%d)\n",
			type);
		status = -EINVAL;
		जाओ out_err;
	पूर्ण
	oinfo->dqi_gi.dqi_sb = sb;
	oinfo->dqi_gi.dqi_type = type;
	ocfs2_qinfo_lock_res_init(&oinfo->dqi_gqlock, oinfo);
	oinfo->dqi_gi.dqi_entry_size = माप(काष्ठा ocfs2_global_disk_dqblk);
	oinfo->dqi_gi.dqi_ops = &ocfs2_global_ops;
	oinfo->dqi_gqi_bh = शून्य;
	oinfo->dqi_gqi_count = 0;
	oinfo->dqi_gqinode = gqinode;
	status = ocfs2_lock_global_qf(oinfo, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	status = ocfs2_extent_map_get_blocks(gqinode, 0, &oinfo->dqi_giblk,
					     &pcount, शून्य);
	अगर (status < 0)
		जाओ out_unlock;

	status = ocfs2_qinfo_lock(oinfo, 0);
	अगर (status < 0)
		जाओ out_unlock;
	status = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dinfo,
				      माप(काष्ठा ocfs2_global_disk_dqinfo),
				      OCFS2_GLOBAL_INFO_OFF);
	ocfs2_qinfo_unlock(oinfo, 0);
	ocfs2_unlock_global_qf(oinfo, 0);
	अगर (status != माप(काष्ठा ocfs2_global_disk_dqinfo)) अणु
		mlog(ML_ERROR, "Cannot read global quota info (%d).\n",
		     status);
		अगर (status >= 0)
			status = -EIO;
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण
	info->dqi_bgrace = le32_to_cpu(dinfo.dqi_bgrace);
	info->dqi_igrace = le32_to_cpu(dinfo.dqi_igrace);
	oinfo->dqi_syncms = le32_to_cpu(dinfo.dqi_syncms);
	oinfo->dqi_gi.dqi_blocks = le32_to_cpu(dinfo.dqi_blocks);
	oinfo->dqi_gi.dqi_मुक्त_blk = le32_to_cpu(dinfo.dqi_मुक्त_blk);
	oinfo->dqi_gi.dqi_मुक्त_entry = le32_to_cpu(dinfo.dqi_मुक्त_entry);
	oinfo->dqi_gi.dqi_blocksize_bits = sb->s_blocksize_bits;
	oinfo->dqi_gi.dqi_usable_bs = sb->s_blocksize -
						OCFS2_QBLK_RESERVED_SPACE;
	oinfo->dqi_gi.dqi_qtree_depth = qtree_depth(&oinfo->dqi_gi);
	INIT_DELAYED_WORK(&oinfo->dqi_sync_work, qsync_work_fn);
	schedule_delayed_work(&oinfo->dqi_sync_work,
			      msecs_to_jअगरfies(oinfo->dqi_syncms));

out_err:
	वापस status;
out_unlock:
	ocfs2_unlock_global_qf(oinfo, 0);
	mlog_त्रुटि_सं(status);
	जाओ out_err;
पूर्ण

/* Write inक्रमmation to global quota file. Expects exlusive lock on quota
 * file inode and quota info */
अटल पूर्णांक __ocfs2_global_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा mem_dqinfo *info = sb_dqinfo(sb, type);
	काष्ठा ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	काष्ठा ocfs2_global_disk_dqinfo dinfo;
	sमाप_प्रकार size;

	spin_lock(&dq_data_lock);
	info->dqi_flags &= ~DQF_INFO_सूचीTY;
	dinfo.dqi_bgrace = cpu_to_le32(info->dqi_bgrace);
	dinfo.dqi_igrace = cpu_to_le32(info->dqi_igrace);
	spin_unlock(&dq_data_lock);
	dinfo.dqi_syncms = cpu_to_le32(oinfo->dqi_syncms);
	dinfo.dqi_blocks = cpu_to_le32(oinfo->dqi_gi.dqi_blocks);
	dinfo.dqi_मुक्त_blk = cpu_to_le32(oinfo->dqi_gi.dqi_मुक्त_blk);
	dinfo.dqi_मुक्त_entry = cpu_to_le32(oinfo->dqi_gi.dqi_मुक्त_entry);
	size = sb->s_op->quota_ग_लिखो(sb, type, (अक्षर *)&dinfo,
				     माप(काष्ठा ocfs2_global_disk_dqinfo),
				     OCFS2_GLOBAL_INFO_OFF);
	अगर (size != माप(काष्ठा ocfs2_global_disk_dqinfo)) अणु
		mlog(ML_ERROR, "Cannot write global quota info structure\n");
		अगर (size >= 0)
			size = -EIO;
		वापस size;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ocfs2_global_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	पूर्णांक err;
	काष्ठा quota_info *dqopt = sb_dqopt(sb);
	काष्ठा ocfs2_mem_dqinfo *info = dqopt->info[type].dqi_priv;

	करोwn_ग_लिखो(&dqopt->dqio_sem);
	err = ocfs2_qinfo_lock(info, 1);
	अगर (err < 0)
		जाओ out_sem;
	err = __ocfs2_global_ग_लिखो_info(sb, type);
	ocfs2_qinfo_unlock(info, 1);
out_sem:
	up_ग_लिखो(&dqopt->dqio_sem);
	वापस err;
पूर्ण

अटल पूर्णांक ocfs2_global_qinit_alloc(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;

	/*
	 * We may need to allocate tree blocks and a leaf block but not the
	 * root block
	 */
	वापस oinfo->dqi_gi.dqi_qtree_depth;
पूर्ण

अटल पूर्णांक ocfs2_calc_global_qinit_credits(काष्ठा super_block *sb, पूर्णांक type)
अणु
	/* We modअगरy all the allocated blocks, tree root, info block and
	 * the inode */
	वापस (ocfs2_global_qinit_alloc(sb, type) + 2) *
			OCFS2_QUOTA_BLOCK_UPDATE_CREDITS + 1;
पूर्ण

/* Sync local inक्रमmation about quota modअगरications with global quota file.
 * Caller must have started the transaction and obtained exclusive lock क्रम
 * global quota file inode */
पूर्णांक __ocfs2_sync_dquot(काष्ठा dquot *dquot, पूर्णांक मुक्तing)
अणु
	पूर्णांक err, err2;
	काष्ठा super_block *sb = dquot->dq_sb;
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;
	काष्ठा ocfs2_global_disk_dqblk dqblk;
	s64 spacechange, inodechange;
	समय64_t oldiसमय, oldbसमय;

	err = sb->s_op->quota_पढ़ो(sb, type, (अक्षर *)&dqblk,
				   माप(काष्ठा ocfs2_global_disk_dqblk),
				   dquot->dq_off);
	अगर (err != माप(काष्ठा ocfs2_global_disk_dqblk)) अणु
		अगर (err >= 0) अणु
			mlog(ML_ERROR, "Short read from global quota file "
				       "(%u read)\n", err);
			err = -EIO;
		पूर्ण
		जाओ out;
	पूर्ण

	/* Update space and inode usage. Get also other inक्रमmation from
	 * global quota file so that we करोn't overग_लिखो any changes there.
	 * We are */
	spin_lock(&dquot->dq_dqb_lock);
	spacechange = dquot->dq_dqb.dqb_curspace -
					OCFS2_DQUOT(dquot)->dq_origspace;
	inodechange = dquot->dq_dqb.dqb_curinodes -
					OCFS2_DQUOT(dquot)->dq_originodes;
	oldiसमय = dquot->dq_dqb.dqb_iसमय;
	oldbसमय = dquot->dq_dqb.dqb_bसमय;
	ocfs2_global_disk2memdqb(dquot, &dqblk);
	trace_ocfs2_sync_dquot(from_kqid(&init_user_ns, dquot->dq_id),
			       dquot->dq_dqb.dqb_curspace,
			       (दीर्घ दीर्घ)spacechange,
			       dquot->dq_dqb.dqb_curinodes,
			       (दीर्घ दीर्घ)inodechange);
	अगर (!test_bit(DQ_LASTSET_B + QIF_SPACE_B, &dquot->dq_flags))
		dquot->dq_dqb.dqb_curspace += spacechange;
	अगर (!test_bit(DQ_LASTSET_B + QIF_INODES_B, &dquot->dq_flags))
		dquot->dq_dqb.dqb_curinodes += inodechange;
	/* Set properly space grace समय... */
	अगर (dquot->dq_dqb.dqb_bsoftlimit &&
	    dquot->dq_dqb.dqb_curspace > dquot->dq_dqb.dqb_bsoftlimit) अणु
		अगर (!test_bit(DQ_LASTSET_B + QIF_BTIME_B, &dquot->dq_flags) &&
		    oldbसमय > 0) अणु
			अगर (dquot->dq_dqb.dqb_bसमय > 0)
				dquot->dq_dqb.dqb_bसमय =
					min(dquot->dq_dqb.dqb_bसमय, oldbसमय);
			अन्यथा
				dquot->dq_dqb.dqb_bसमय = oldbसमय;
		पूर्ण
	पूर्ण अन्यथा अणु
		dquot->dq_dqb.dqb_bसमय = 0;
		clear_bit(DQ_BLKS_B, &dquot->dq_flags);
	पूर्ण
	/* Set properly inode grace समय... */
	अगर (dquot->dq_dqb.dqb_isoftlimit &&
	    dquot->dq_dqb.dqb_curinodes > dquot->dq_dqb.dqb_isoftlimit) अणु
		अगर (!test_bit(DQ_LASTSET_B + QIF_ITIME_B, &dquot->dq_flags) &&
		    oldiसमय > 0) अणु
			अगर (dquot->dq_dqb.dqb_iसमय > 0)
				dquot->dq_dqb.dqb_iसमय =
					min(dquot->dq_dqb.dqb_iसमय, oldiसमय);
			अन्यथा
				dquot->dq_dqb.dqb_iसमय = oldiसमय;
		पूर्ण
	पूर्ण अन्यथा अणु
		dquot->dq_dqb.dqb_iसमय = 0;
		clear_bit(DQ_INODES_B, &dquot->dq_flags);
	पूर्ण
	/* All inक्रमmation is properly updated, clear the flags */
	__clear_bit(DQ_LASTSET_B + QIF_SPACE_B, &dquot->dq_flags);
	__clear_bit(DQ_LASTSET_B + QIF_INODES_B, &dquot->dq_flags);
	__clear_bit(DQ_LASTSET_B + QIF_BLIMITS_B, &dquot->dq_flags);
	__clear_bit(DQ_LASTSET_B + QIF_ILIMITS_B, &dquot->dq_flags);
	__clear_bit(DQ_LASTSET_B + QIF_BTIME_B, &dquot->dq_flags);
	__clear_bit(DQ_LASTSET_B + QIF_ITIME_B, &dquot->dq_flags);
	OCFS2_DQUOT(dquot)->dq_origspace = dquot->dq_dqb.dqb_curspace;
	OCFS2_DQUOT(dquot)->dq_originodes = dquot->dq_dqb.dqb_curinodes;
	spin_unlock(&dquot->dq_dqb_lock);
	err = ocfs2_qinfo_lock(info, मुक्तing);
	अगर (err < 0) अणु
		mlog(ML_ERROR, "Failed to lock quota info, losing quota write"
			       " (type=%d, id=%u)\n", dquot->dq_id.type,
			       (अचिन्हित)from_kqid(&init_user_ns, dquot->dq_id));
		जाओ out;
	पूर्ण
	अगर (मुक्तing)
		OCFS2_DQUOT(dquot)->dq_use_count--;
	err = qtree_ग_लिखो_dquot(&info->dqi_gi, dquot);
	अगर (err < 0)
		जाओ out_qlock;
	अगर (मुक्तing && !OCFS2_DQUOT(dquot)->dq_use_count) अणु
		err = qtree_release_dquot(&info->dqi_gi, dquot);
		अगर (info_dirty(sb_dqinfo(sb, type))) अणु
			err2 = __ocfs2_global_ग_लिखो_info(sb, type);
			अगर (!err)
				err = err2;
		पूर्ण
	पूर्ण
out_qlock:
	ocfs2_qinfo_unlock(info, मुक्तing);
out:
	अगर (err < 0)
		mlog_त्रुटि_सं(err);
	वापस err;
पूर्ण

/*
 *  Functions क्रम periodic syncing of dquots with global file
 */
अटल पूर्णांक ocfs2_sync_dquot_helper(काष्ठा dquot *dquot, अचिन्हित दीर्घ type)
अणु
	handle_t *handle;
	काष्ठा super_block *sb = dquot->dq_sb;
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	पूर्णांक status = 0;

	trace_ocfs2_sync_dquot_helper(from_kqid(&init_user_ns, dquot->dq_id),
				      dquot->dq_id.type,
				      type, sb->s_id);
	अगर (type != dquot->dq_id.type)
		जाओ out;
	status = ocfs2_lock_global_qf(oinfo, 1);
	अगर (status < 0)
		जाओ out;

	handle = ocfs2_start_trans(osb, OCFS2_QSYNC_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out_ilock;
	पूर्ण
	करोwn_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
	status = ocfs2_sync_dquot(dquot);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	/* We have to ग_लिखो local काष्ठाure as well... */
	status = ocfs2_local_ग_लिखो_dquot(dquot);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	up_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	वापस status;
पूर्ण

अटल व्योम qsync_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocfs2_mem_dqinfo *oinfo = container_of(work,
						      काष्ठा ocfs2_mem_dqinfo,
						      dqi_sync_work.work);
	काष्ठा super_block *sb = oinfo->dqi_gqinode->i_sb;

	/*
	 * We have to be careful here not to deadlock on s_umount as umount
	 * disabling quotas may be in progress and it रुकोs क्रम this work to
	 * complete. If trylock fails, we'll करो the sync next समय...
	 */
	अगर (करोwn_पढ़ो_trylock(&sb->s_umount)) अणु
		dquot_scan_active(sb, ocfs2_sync_dquot_helper, oinfo->dqi_type);
		up_पढ़ो(&sb->s_umount);
	पूर्ण
	schedule_delayed_work(&oinfo->dqi_sync_work,
			      msecs_to_jअगरfies(oinfo->dqi_syncms));
पूर्ण

/*
 *  Wrappers क्रम generic quota functions
 */

अटल पूर्णांक ocfs2_ग_लिखो_dquot(काष्ठा dquot *dquot)
अणु
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dquot->dq_sb);
	पूर्णांक status = 0;

	trace_ocfs2_ग_लिखो_dquot(from_kqid(&init_user_ns, dquot->dq_id),
				dquot->dq_id.type);

	handle = ocfs2_start_trans(osb, OCFS2_QWRITE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण
	करोwn_ग_लिखो(&sb_dqopt(dquot->dq_sb)->dqio_sem);
	status = ocfs2_local_ग_लिखो_dquot(dquot);
	up_ग_लिखो(&sb_dqopt(dquot->dq_sb)->dqio_sem);
	ocfs2_commit_trans(osb, handle);
out:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_calc_qdel_credits(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	/*
	 * We modअगरy tree, leaf block, global info, local chunk header,
	 * global and local inode; OCFS2_QINFO_WRITE_CREDITS alपढ़ोy
	 * accounts क्रम inode update
	 */
	वापस (oinfo->dqi_gi.dqi_qtree_depth + 2) *
	       OCFS2_QUOTA_BLOCK_UPDATE_CREDITS +
	       OCFS2_QINFO_WRITE_CREDITS +
	       OCFS2_INODE_UPDATE_CREDITS;
पूर्ण

व्योम ocfs2_drop_dquot_refs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocfs2_super *osb = container_of(work, काष्ठा ocfs2_super,
					       dquot_drop_work);
	काष्ठा llist_node *list;
	काष्ठा ocfs2_dquot *odquot, *next_odquot;

	list = llist_del_all(&osb->dquot_drop_list);
	llist_क्रम_each_entry_safe(odquot, next_odquot, list, list) अणु
		/* Drop the reference we acquired in ocfs2_dquot_release() */
		dqput(&odquot->dq_dquot);
	पूर्ण
पूर्ण

/*
 * Called when the last reference to dquot is dropped. If we are called from
 * करोwnconvert thपढ़ो, we cannot करो all the handling here because grabbing
 * quota lock could deadlock (the node holding the quota lock could need some
 * other cluster lock to proceed but with blocked करोwnconvert thपढ़ो we cannot
 * release any lock).
 */
अटल पूर्णांक ocfs2_release_dquot(काष्ठा dquot *dquot)
अणु
	handle_t *handle;
	काष्ठा ocfs2_mem_dqinfo *oinfo =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dquot->dq_sb);
	पूर्णांक status = 0;

	trace_ocfs2_release_dquot(from_kqid(&init_user_ns, dquot->dq_id),
				  dquot->dq_id.type);

	mutex_lock(&dquot->dq_lock);
	/* Check whether we are not racing with some other dqget() */
	अगर (dquot_is_busy(dquot))
		जाओ out;
	/* Running from करोwnconvert thपढ़ो? Postpone quota processing to wq */
	अगर (current == osb->dc_task) अणु
		/*
		 * Grab our own reference to dquot and queue it क्रम delayed
		 * dropping.  Quota code rechecks after calling
		 * ->release_dquot() and won't मुक्त dquot काष्ठाure.
		 */
		dqgrab(dquot);
		/* First entry on list -> queue work */
		अगर (llist_add(&OCFS2_DQUOT(dquot)->list, &osb->dquot_drop_list))
			queue_work(osb->ocfs2_wq, &osb->dquot_drop_work);
		जाओ out;
	पूर्ण
	status = ocfs2_lock_global_qf(oinfo, 1);
	अगर (status < 0)
		जाओ out;
	handle = ocfs2_start_trans(osb,
		ocfs2_calc_qdel_credits(dquot->dq_sb, dquot->dq_id.type));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out_ilock;
	पूर्ण

	status = ocfs2_global_release_dquot(dquot);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_trans;
	पूर्ण
	status = ocfs2_local_release_dquot(handle, dquot);
	/*
	 * If we fail here, we cannot करो much as global काष्ठाure is
	 * alपढ़ोy released. So just complain...
	 */
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	/*
	 * Clear dq_off so that we search क्रम the काष्ठाure in quota file next
	 * समय we acquire it. The काष्ठाure might be deleted and पुनः_स्मृतिated
	 * अन्यथाwhere by another node जबतक our dquot काष्ठाure is on मुक्तlist.
	 */
	dquot->dq_off = 0;
	clear_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out_trans:
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mutex_unlock(&dquot->dq_lock);
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/*
 * Read global dquot काष्ठाure from disk or create it अगर it करोes
 * not exist. Also update use count of the global काष्ठाure and
 * create काष्ठाure in node-local quota file.
 */
अटल पूर्णांक ocfs2_acquire_dquot(काष्ठा dquot *dquot)
अणु
	पूर्णांक status = 0, err;
	पूर्णांक ex = 0;
	काष्ठा super_block *sb = dquot->dq_sb;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;
	काष्ठा inode *gqinode = info->dqi_gqinode;
	पूर्णांक need_alloc = ocfs2_global_qinit_alloc(sb, type);
	handle_t *handle;

	trace_ocfs2_acquire_dquot(from_kqid(&init_user_ns, dquot->dq_id),
				  type);
	mutex_lock(&dquot->dq_lock);
	/*
	 * We need an exclusive lock, because we're going to update use count
	 * and instantiate possibly new dquot काष्ठाure
	 */
	status = ocfs2_lock_global_qf(info, 1);
	अगर (status < 0)
		जाओ out;
	status = ocfs2_qinfo_lock(info, 0);
	अगर (status < 0)
		जाओ out_dq;
	/*
	 * We always want to पढ़ो dquot काष्ठाure from disk because we करोn't
	 * know what happened with it जबतक it was on मुक्तlist.
	 */
	status = qtree_पढ़ो_dquot(&info->dqi_gi, dquot);
	ocfs2_qinfo_unlock(info, 0);
	अगर (status < 0)
		जाओ out_dq;

	OCFS2_DQUOT(dquot)->dq_use_count++;
	OCFS2_DQUOT(dquot)->dq_origspace = dquot->dq_dqb.dqb_curspace;
	OCFS2_DQUOT(dquot)->dq_originodes = dquot->dq_dqb.dqb_curinodes;
	अगर (!dquot->dq_off) अणु	/* No real quota entry? */
		ex = 1;
		/*
		 * Add blocks to quota file beक्रमe we start a transaction since
		 * locking allocators ranks above a transaction start
		 */
		WARN_ON(journal_current_handle());
		status = ocfs2_extend_no_holes(gqinode, शून्य,
			i_size_पढ़ो(gqinode) + (need_alloc << sb->s_blocksize_bits),
			i_size_पढ़ो(gqinode));
		अगर (status < 0)
			जाओ out_dq;
	पूर्ण

	handle = ocfs2_start_trans(osb,
				   ocfs2_calc_global_qinit_credits(sb, type));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		जाओ out_dq;
	पूर्ण
	status = ocfs2_qinfo_lock(info, ex);
	अगर (status < 0)
		जाओ out_trans;
	status = qtree_ग_लिखो_dquot(&info->dqi_gi, dquot);
	अगर (ex && info_dirty(sb_dqinfo(sb, type))) अणु
		err = __ocfs2_global_ग_लिखो_info(sb, type);
		अगर (!status)
			status = err;
	पूर्ण
	ocfs2_qinfo_unlock(info, ex);
out_trans:
	ocfs2_commit_trans(osb, handle);
out_dq:
	ocfs2_unlock_global_qf(info, 1);
	अगर (status < 0)
		जाओ out;

	status = ocfs2_create_local_dquot(dquot);
	अगर (status < 0)
		जाओ out;
	set_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out:
	mutex_unlock(&dquot->dq_lock);
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_get_next_id(काष्ठा super_block *sb, काष्ठा kqid *qid)
अणु
	पूर्णांक type = qid->type;
	काष्ठा ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;
	पूर्णांक status = 0;

	trace_ocfs2_get_next_id(from_kqid(&init_user_ns, *qid), type);
	अगर (!sb_has_quota_loaded(sb, type)) अणु
		status = -ESRCH;
		जाओ out;
	पूर्ण
	status = ocfs2_lock_global_qf(info, 0);
	अगर (status < 0)
		जाओ out;
	status = ocfs2_qinfo_lock(info, 0);
	अगर (status < 0)
		जाओ out_global;
	status = qtree_get_next_id(&info->dqi_gi, qid);
	ocfs2_qinfo_unlock(info, 0);
out_global:
	ocfs2_unlock_global_qf(info, 0);
out:
	/*
	 * Aव्योम logging ENOENT since it just means there isn't next ID and
	 * ESRCH which means quota isn't enabled क्रम the fileप्रणाली.
	 */
	अगर (status && status != -ENOENT && status != -ESRCH)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	अचिन्हित दीर्घ mask = (1 << (DQ_LASTSET_B + QIF_ILIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BLIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_INODES_B)) |
			     (1 << (DQ_LASTSET_B + QIF_SPACE_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BTIME_B)) |
			     (1 << (DQ_LASTSET_B + QIF_ITIME_B));
	पूर्णांक sync = 0;
	पूर्णांक status;
	काष्ठा super_block *sb = dquot->dq_sb;
	पूर्णांक type = dquot->dq_id.type;
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	trace_ocfs2_mark_dquot_dirty(from_kqid(&init_user_ns, dquot->dq_id),
				     type);

	/* In हाल user set some limits, sync dquot immediately to global
	 * quota file so that inक्रमmation propagates quicker */
	spin_lock(&dquot->dq_dqb_lock);
	अगर (dquot->dq_flags & mask)
		sync = 1;
	spin_unlock(&dquot->dq_dqb_lock);
	/* This is a slight hack but we can't afक्रमd getting global quota
	 * lock अगर we alपढ़ोy have a transaction started. */
	अगर (!sync || journal_current_handle()) अणु
		status = ocfs2_ग_लिखो_dquot(dquot);
		जाओ out;
	पूर्ण
	status = ocfs2_lock_global_qf(oinfo, 1);
	अगर (status < 0)
		जाओ out;
	handle = ocfs2_start_trans(osb, OCFS2_QSYNC_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out_ilock;
	पूर्ण
	करोwn_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
	status = ocfs2_sync_dquot(dquot);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_dlock;
	पूर्ण
	/* Now ग_लिखो updated local dquot काष्ठाure */
	status = ocfs2_local_ग_लिखो_dquot(dquot);
out_dlock:
	up_ग_लिखो(&sb_dqopt(sb)->dqio_sem);
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/* This should happen only after set_dqinfo(). */
अटल पूर्णांक ocfs2_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	handle_t *handle;
	पूर्णांक status = 0;
	काष्ठा ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;

	status = ocfs2_lock_global_qf(oinfo, 1);
	अगर (status < 0)
		जाओ out;
	handle = ocfs2_start_trans(OCFS2_SB(sb), OCFS2_QINFO_WRITE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ out_ilock;
	पूर्ण
	status = dquot_commit_info(sb, type);
	ocfs2_commit_trans(OCFS2_SB(sb), handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल काष्ठा dquot *ocfs2_alloc_dquot(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा ocfs2_dquot *dquot =
				kmem_cache_zalloc(ocfs2_dquot_cachep, GFP_NOFS);

	अगर (!dquot)
		वापस शून्य;
	वापस &dquot->dq_dquot;
पूर्ण

अटल व्योम ocfs2_destroy_dquot(काष्ठा dquot *dquot)
अणु
	kmem_cache_मुक्त(ocfs2_dquot_cachep, dquot);
पूर्ण

स्थिर काष्ठा dquot_operations ocfs2_quota_operations = अणु
	/* We never make dquot dirty so .ग_लिखो_dquot is never called */
	.acquire_dquot	= ocfs2_acquire_dquot,
	.release_dquot	= ocfs2_release_dquot,
	.mark_dirty	= ocfs2_mark_dquot_dirty,
	.ग_लिखो_info	= ocfs2_ग_लिखो_info,
	.alloc_dquot	= ocfs2_alloc_dquot,
	.destroy_dquot	= ocfs2_destroy_dquot,
	.get_next_id	= ocfs2_get_next_id,
पूर्ण;
