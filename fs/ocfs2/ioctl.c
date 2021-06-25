<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ocfs2/ioctl.c
 *
 * Copyright (C) 2006 Herbert Poetzl
 * adapted from Remy Card's ext2/ioctl.c
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/fileattr.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "alloc.h"
#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"

#समावेश "ocfs2_fs.h"
#समावेश "ioctl.h"
#समावेश "resize.h"
#समावेश "refcounttree.h"
#समावेश "sysfile.h"
#समावेश "dir.h"
#समावेश "buffer_head_io.h"
#समावेश "suballoc.h"
#समावेश "move_extents.h"

#घोषणा o2info_from_user(a, b)	\
		copy_from_user(&(a), (b), माप(a))
#घोषणा o2info_to_user(a, b)	\
		copy_to_user((typeof(a) __user *)b, &(a), माप(a))

/*
 * This is just a best-efक्रमt to tell userspace that this request
 * caused the error.
 */
अटल अंतरभूत व्योम o2info_set_request_error(काष्ठा ocfs2_info_request *kreq,
					काष्ठा ocfs2_info_request __user *req)
अणु
	kreq->ir_flags |= OCFS2_INFO_FL_ERROR;
	(व्योम)put_user(kreq->ir_flags, (__u32 __user *)&(req->ir_flags));
पूर्ण

अटल अंतरभूत व्योम o2info_set_request_filled(काष्ठा ocfs2_info_request *req)
अणु
	req->ir_flags |= OCFS2_INFO_FL_FILLED;
पूर्ण

अटल अंतरभूत व्योम o2info_clear_request_filled(काष्ठा ocfs2_info_request *req)
अणु
	req->ir_flags &= ~OCFS2_INFO_FL_FILLED;
पूर्ण

अटल अंतरभूत पूर्णांक o2info_coherent(काष्ठा ocfs2_info_request *req)
अणु
	वापस (!(req->ir_flags & OCFS2_INFO_FL_NON_COHERENT));
पूर्ण

पूर्णांक ocfs2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक flags;
	पूर्णांक status;

	status = ocfs2_inode_lock(inode, शून्य, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण
	ocfs2_get_inode_flags(OCFS2_I(inode));
	flags = OCFS2_I(inode)->ip_attr;
	ocfs2_inode_unlock(inode, 0);

	fileattr_fill_flags(fa, flags & OCFS2_FL_VISIBLE);

	वापस status;
पूर्ण

पूर्णांक ocfs2_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक flags = fa->flags;
	काष्ठा ocfs2_inode_info *ocfs2_inode = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित oldflags;
	पूर्णांक status;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	status = ocfs2_inode_lock(inode, &bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (!S_ISसूची(inode->i_mode))
		flags &= ~OCFS2_सूचीSYNC_FL;

	oldflags = ocfs2_inode->ip_attr;
	flags = flags & OCFS2_FL_MODIFIABLE;
	flags |= oldflags & ~OCFS2_FL_MODIFIABLE;

	/* Check alपढ़ोy करोne by VFS, but repeat with ocfs lock */
	status = -EPERM;
	अगर ((flags ^ oldflags) & (FS_APPEND_FL | FS_IMMUTABLE_FL) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		जाओ bail_unlock;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock;
	पूर्ण

	ocfs2_inode->ip_attr = flags;
	ocfs2_set_inode_flags(inode);

	status = ocfs2_mark_inode_dirty(handle, inode, bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	ocfs2_commit_trans(osb, handle);

bail_unlock:
	ocfs2_inode_unlock(inode, 1);
bail:
	brअन्यथा(bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_blocksize(काष्ठा inode *inode,
				       काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_blocksize oib;

	अगर (o2info_from_user(oib, req))
		वापस -EFAULT;

	oib.ib_blocksize = inode->i_sb->s_blocksize;

	o2info_set_request_filled(&oib.ib_req);

	अगर (o2info_to_user(oib, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_clustersize(काष्ठा inode *inode,
					 काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_clustersize oic;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oic, req))
		वापस -EFAULT;

	oic.ic_clustersize = osb->s_clustersize;

	o2info_set_request_filled(&oic.ic_req);

	अगर (o2info_to_user(oic, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_maxslots(काष्ठा inode *inode,
				      काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_maxslots oim;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oim, req))
		वापस -EFAULT;

	oim.im_max_slots = osb->max_slots;

	o2info_set_request_filled(&oim.im_req);

	अगर (o2info_to_user(oim, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_label(काष्ठा inode *inode,
				   काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_label oil;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oil, req))
		वापस -EFAULT;

	स_नकल(oil.il_label, osb->vol_label, OCFS2_MAX_VOL_LABEL_LEN);

	o2info_set_request_filled(&oil.il_req);

	अगर (o2info_to_user(oil, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_uuid(काष्ठा inode *inode,
				  काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_uuid oiu;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oiu, req))
		वापस -EFAULT;

	स_नकल(oiu.iu_uuid_str, osb->uuid_str, OCFS2_TEXT_UUID_LEN + 1);

	o2info_set_request_filled(&oiu.iu_req);

	अगर (o2info_to_user(oiu, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_fs_features(काष्ठा inode *inode,
					 काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_fs_features oअगर;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oअगर, req))
		वापस -EFAULT;

	oअगर.अगर_compat_features = osb->s_feature_compat;
	oअगर.अगर_incompat_features = osb->s_feature_incompat;
	oअगर.अगर_ro_compat_features = osb->s_feature_ro_compat;

	o2info_set_request_filled(&oअगर.अगर_req);

	अगर (o2info_to_user(oअगर, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_journal_size(काष्ठा inode *inode,
					  काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_journal_size oij;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (o2info_from_user(oij, req))
		वापस -EFAULT;

	oij.ij_journal_size = i_size_पढ़ो(osb->journal->j_inode);

	o2info_set_request_filled(&oij.ij_req);

	अगर (o2info_to_user(oij, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_info_scan_inode_alloc(काष्ठा ocfs2_super *osb,
				       काष्ठा inode *inode_alloc, u64 blkno,
				       काष्ठा ocfs2_info_मुक्तinode *fi,
				       u32 slot)
अणु
	पूर्णांक status = 0, unlock = 0;

	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_dinode *dinode_alloc = शून्य;

	अगर (inode_alloc)
		inode_lock(inode_alloc);

	अगर (inode_alloc && o2info_coherent(&fi->अगरi_req)) अणु
		status = ocfs2_inode_lock(inode_alloc, &bh, 0);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		unlock = 1;
	पूर्ण अन्यथा अणु
		status = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	dinode_alloc = (काष्ठा ocfs2_dinode *)bh->b_data;

	fi->अगरi_stat[slot].lfi_total =
		le32_to_cpu(dinode_alloc->id1.biपंचांगap1.i_total);
	fi->अगरi_stat[slot].lfi_मुक्त =
		le32_to_cpu(dinode_alloc->id1.biपंचांगap1.i_total) -
		le32_to_cpu(dinode_alloc->id1.biपंचांगap1.i_used);

bail:
	अगर (unlock)
		ocfs2_inode_unlock(inode_alloc, 0);

	अगर (inode_alloc)
		inode_unlock(inode_alloc);

	brअन्यथा(bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_मुक्तinode(काष्ठा inode *inode,
				       काष्ठा ocfs2_info_request __user *req)
अणु
	u32 i;
	u64 blkno = -1;
	अक्षर namebuf[40];
	पूर्णांक status, type = INODE_ALLOC_SYSTEM_INODE;
	काष्ठा ocfs2_info_मुक्तinode *oअगरi = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *inode_alloc = शून्य;

	oअगरi = kzalloc(माप(काष्ठा ocfs2_info_मुक्तinode), GFP_KERNEL);
	अगर (!oअगरi) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	अगर (o2info_from_user(*oअगरi, req)) अणु
		status = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	oअगरi->अगरi_slotnum = osb->max_slots;

	क्रम (i = 0; i < oअगरi->अगरi_slotnum; i++) अणु
		अगर (o2info_coherent(&oअगरi->अगरi_req)) अणु
			inode_alloc = ocfs2_get_प्रणाली_file_inode(osb, type, i);
			अगर (!inode_alloc) अणु
				mlog(ML_ERROR, "unable to get alloc inode in "
				    "slot %u\n", i);
				status = -EIO;
				जाओ bail;
			पूर्ण
		पूर्ण अन्यथा अणु
			ocfs2_प्र_लिखो_प्रणाली_inode_name(namebuf,
							माप(namebuf),
							type, i);
			status = ocfs2_lookup_ino_from_name(osb->sys_root_inode,
							    namebuf,
							    म_माप(namebuf),
							    &blkno);
			अगर (status < 0) अणु
				status = -ENOENT;
				जाओ bail;
			पूर्ण
		पूर्ण

		status = ocfs2_info_scan_inode_alloc(osb, inode_alloc, blkno, oअगरi, i);

		iput(inode_alloc);
		inode_alloc = शून्य;

		अगर (status < 0)
			जाओ bail;
	पूर्ण

	o2info_set_request_filled(&oअगरi->अगरi_req);

	अगर (o2info_to_user(*oअगरi, req)) अणु
		status = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	status = 0;
bail:
	अगर (status)
		o2info_set_request_error(&oअगरi->अगरi_req, req);
out_मुक्त:
	kमुक्त(oअगरi);
out_err:
	वापस status;
पूर्ण

अटल व्योम o2ffg_update_histogram(काष्ठा ocfs2_info_मुक्त_chunk_list *hist,
				   अचिन्हित पूर्णांक chunksize)
अणु
	u32 index;

	index = __ilog2_u32(chunksize);
	अगर (index >= OCFS2_INFO_MAX_HIST)
		index = OCFS2_INFO_MAX_HIST - 1;

	hist->fc_chunks[index]++;
	hist->fc_clusters[index] += chunksize;
पूर्ण

अटल व्योम o2ffg_update_stats(काष्ठा ocfs2_info_मुक्तfrag_stats *stats,
			       अचिन्हित पूर्णांक chunksize)
अणु
	अगर (chunksize > stats->ffs_max)
		stats->ffs_max = chunksize;

	अगर (chunksize < stats->ffs_min)
		stats->ffs_min = chunksize;

	stats->ffs_avg += chunksize;
	stats->ffs_मुक्त_chunks_real++;
पूर्ण

अटल व्योम ocfs2_info_update_ffg(काष्ठा ocfs2_info_मुक्तfrag *ffg,
				  अचिन्हित पूर्णांक chunksize)
अणु
	o2ffg_update_histogram(&(ffg->अगरf_ffs.ffs_fc_hist), chunksize);
	o2ffg_update_stats(&(ffg->अगरf_ffs), chunksize);
पूर्ण

अटल पूर्णांक ocfs2_info_मुक्तfrag_scan_chain(काष्ठा ocfs2_super *osb,
					  काष्ठा inode *gb_inode,
					  काष्ठा ocfs2_dinode *gb_dinode,
					  काष्ठा ocfs2_chain_rec *rec,
					  काष्ठा ocfs2_info_मुक्तfrag *ffg,
					  u32 chunks_in_group)
अणु
	पूर्णांक status = 0, used;
	u64 blkno;

	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_group_desc *bg = शून्य;

	अचिन्हित पूर्णांक max_bits, num_clusters;
	अचिन्हित पूर्णांक offset = 0, cluster, chunk;
	अचिन्हित पूर्णांक chunk_मुक्त, last_chunksize = 0;

	अगर (!le32_to_cpu(rec->c_मुक्त))
		जाओ bail;

	करो अणु
		अगर (!bg)
			blkno = le64_to_cpu(rec->c_blkno);
		अन्यथा
			blkno = le64_to_cpu(bg->bg_next_group);

		अगर (bh) अणु
			brअन्यथा(bh);
			bh = शून्य;
		पूर्ण

		अगर (o2info_coherent(&ffg->अगरf_req))
			status = ocfs2_पढ़ो_group_descriptor(gb_inode,
							     gb_dinode,
							     blkno, &bh);
		अन्यथा
			status = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &bh);

		अगर (status < 0) अणु
			mlog(ML_ERROR, "Can't read the group descriptor # "
			     "%llu from device.", (अचिन्हित दीर्घ दीर्घ)blkno);
			status = -EIO;
			जाओ bail;
		पूर्ण

		bg = (काष्ठा ocfs2_group_desc *)bh->b_data;

		अगर (!le16_to_cpu(bg->bg_मुक्त_bits_count))
			जारी;

		max_bits = le16_to_cpu(bg->bg_bits);
		offset = 0;

		क्रम (chunk = 0; chunk < chunks_in_group; chunk++) अणु
			/*
			 * last chunk may be not an entire one.
			 */
			अगर ((offset + ffg->अगरf_chunksize) > max_bits)
				num_clusters = max_bits - offset;
			अन्यथा
				num_clusters = ffg->अगरf_chunksize;

			chunk_मुक्त = 0;
			क्रम (cluster = 0; cluster < num_clusters; cluster++) अणु
				used = ocfs2_test_bit(offset,
						(अचिन्हित दीर्घ *)bg->bg_biपंचांगap);
				/*
				 * - chunk_मुक्त counts मुक्त clusters in #N chunk.
				 * - last_chunksize records the size(in) clusters
				 *   क्रम the last real मुक्त chunk being counted.
				 */
				अगर (!used) अणु
					last_chunksize++;
					chunk_मुक्त++;
				पूर्ण

				अगर (used && last_chunksize) अणु
					ocfs2_info_update_ffg(ffg,
							      last_chunksize);
					last_chunksize = 0;
				पूर्ण

				offset++;
			पूर्ण

			अगर (chunk_मुक्त == ffg->अगरf_chunksize)
				ffg->अगरf_ffs.ffs_मुक्त_chunks++;
		पूर्ण

		/*
		 * need to update the info क्रम last मुक्त chunk.
		 */
		अगर (last_chunksize)
			ocfs2_info_update_ffg(ffg, last_chunksize);

	पूर्ण जबतक (le64_to_cpu(bg->bg_next_group));

bail:
	brअन्यथा(bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_info_मुक्तfrag_scan_biपंचांगap(काष्ठा ocfs2_super *osb,
					   काष्ठा inode *gb_inode, u64 blkno,
					   काष्ठा ocfs2_info_मुक्तfrag *ffg)
अणु
	u32 chunks_in_group;
	पूर्णांक status = 0, unlock = 0, i;

	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_chain_list *cl = शून्य;
	काष्ठा ocfs2_chain_rec *rec = शून्य;
	काष्ठा ocfs2_dinode *gb_dinode = शून्य;

	अगर (gb_inode)
		inode_lock(gb_inode);

	अगर (o2info_coherent(&ffg->अगरf_req)) अणु
		status = ocfs2_inode_lock(gb_inode, &bh, 0);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		unlock = 1;
	पूर्ण अन्यथा अणु
		status = ocfs2_पढ़ो_blocks_sync(osb, blkno, 1, &bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	gb_dinode = (काष्ठा ocfs2_dinode *)bh->b_data;
	cl = &(gb_dinode->id2.i_chain);

	/*
	 * Chunksize(in) clusters from userspace should be
	 * less than clusters in a group.
	 */
	अगर (ffg->अगरf_chunksize > le16_to_cpu(cl->cl_cpg)) अणु
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	स_रखो(&ffg->अगरf_ffs, 0, माप(काष्ठा ocfs2_info_मुक्तfrag_stats));

	ffg->अगरf_ffs.ffs_min = ~0U;
	ffg->अगरf_ffs.ffs_clusters =
			le32_to_cpu(gb_dinode->id1.biपंचांगap1.i_total);
	ffg->अगरf_ffs.ffs_मुक्त_clusters = ffg->अगरf_ffs.ffs_clusters -
			le32_to_cpu(gb_dinode->id1.biपंचांगap1.i_used);

	chunks_in_group = le16_to_cpu(cl->cl_cpg) / ffg->अगरf_chunksize + 1;

	क्रम (i = 0; i < le16_to_cpu(cl->cl_next_मुक्त_rec); i++) अणु
		rec = &(cl->cl_recs[i]);
		status = ocfs2_info_मुक्तfrag_scan_chain(osb, gb_inode,
							gb_dinode,
							rec, ffg,
							chunks_in_group);
		अगर (status)
			जाओ bail;
	पूर्ण

	अगर (ffg->अगरf_ffs.ffs_मुक्त_chunks_real)
		ffg->अगरf_ffs.ffs_avg = (ffg->अगरf_ffs.ffs_avg /
					ffg->अगरf_ffs.ffs_मुक्त_chunks_real);
bail:
	अगर (unlock)
		ocfs2_inode_unlock(gb_inode, 0);

	अगर (gb_inode)
		inode_unlock(gb_inode);

	iput(gb_inode);
	brअन्यथा(bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_मुक्तfrag(काष्ठा inode *inode,
				      काष्ठा ocfs2_info_request __user *req)
अणु
	u64 blkno = -1;
	अक्षर namebuf[40];
	पूर्णांक status, type = GLOBAL_BITMAP_SYSTEM_INODE;

	काष्ठा ocfs2_info_मुक्तfrag *oअगरf;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *gb_inode = शून्य;

	oअगरf = kzalloc(माप(काष्ठा ocfs2_info_मुक्तfrag), GFP_KERNEL);
	अगर (!oअगरf) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ out_err;
	पूर्ण

	अगर (o2info_from_user(*oअगरf, req)) अणु
		status = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	/*
	 * chunksize from userspace should be घातer of 2.
	 */
	अगर ((oअगरf->अगरf_chunksize & (oअगरf->अगरf_chunksize - 1)) ||
	    (!oअगरf->अगरf_chunksize)) अणु
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (o2info_coherent(&oअगरf->अगरf_req)) अणु
		gb_inode = ocfs2_get_प्रणाली_file_inode(osb, type,
						       OCFS2_INVALID_SLOT);
		अगर (!gb_inode) अणु
			mlog(ML_ERROR, "unable to get global_bitmap inode\n");
			status = -EIO;
			जाओ bail;
		पूर्ण
	पूर्ण अन्यथा अणु
		ocfs2_प्र_लिखो_प्रणाली_inode_name(namebuf, माप(namebuf), type,
						OCFS2_INVALID_SLOT);
		status = ocfs2_lookup_ino_from_name(osb->sys_root_inode,
						    namebuf,
						    म_माप(namebuf),
						    &blkno);
		अगर (status < 0) अणु
			status = -ENOENT;
			जाओ bail;
		पूर्ण
	पूर्ण

	status = ocfs2_info_मुक्तfrag_scan_biपंचांगap(osb, gb_inode, blkno, oअगरf);
	अगर (status < 0)
		जाओ bail;

	o2info_set_request_filled(&oअगरf->अगरf_req);

	अगर (o2info_to_user(*oअगरf, req)) अणु
		status = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	status = 0;
bail:
	अगर (status)
		o2info_set_request_error(&oअगरf->अगरf_req, req);
out_मुक्त:
	kमुक्त(oअगरf);
out_err:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_info_handle_unknown(काष्ठा inode *inode,
				     काष्ठा ocfs2_info_request __user *req)
अणु
	काष्ठा ocfs2_info_request oir;

	अगर (o2info_from_user(oir, req))
		वापस -EFAULT;

	o2info_clear_request_filled(&oir);

	अगर (o2info_to_user(oir, req))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Validate and distinguish OCFS2_IOC_INFO requests.
 *
 * - validate the magic number.
 * - distinguish dअगरferent requests.
 * - validate size of dअगरferent requests.
 */
अटल पूर्णांक ocfs2_info_handle_request(काष्ठा inode *inode,
				     काष्ठा ocfs2_info_request __user *req)
अणु
	पूर्णांक status = -EFAULT;
	काष्ठा ocfs2_info_request oir;

	अगर (o2info_from_user(oir, req))
		जाओ bail;

	status = -EINVAL;
	अगर (oir.ir_magic != OCFS2_INFO_MAGIC)
		जाओ bail;

	चयन (oir.ir_code) अणु
	हाल OCFS2_INFO_BLOCKSIZE:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_blocksize))
			status = ocfs2_info_handle_blocksize(inode, req);
		अवरोध;
	हाल OCFS2_INFO_CLUSTERSIZE:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_clustersize))
			status = ocfs2_info_handle_clustersize(inode, req);
		अवरोध;
	हाल OCFS2_INFO_MAXSLOTS:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_maxslots))
			status = ocfs2_info_handle_maxslots(inode, req);
		अवरोध;
	हाल OCFS2_INFO_LABEL:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_label))
			status = ocfs2_info_handle_label(inode, req);
		अवरोध;
	हाल OCFS2_INFO_UUID:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_uuid))
			status = ocfs2_info_handle_uuid(inode, req);
		अवरोध;
	हाल OCFS2_INFO_FS_FEATURES:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_fs_features))
			status = ocfs2_info_handle_fs_features(inode, req);
		अवरोध;
	हाल OCFS2_INFO_JOURNAL_SIZE:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_journal_size))
			status = ocfs2_info_handle_journal_size(inode, req);
		अवरोध;
	हाल OCFS2_INFO_FREEINODE:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_मुक्तinode))
			status = ocfs2_info_handle_मुक्तinode(inode, req);
		अवरोध;
	हाल OCFS2_INFO_FREEFRAG:
		अगर (oir.ir_size == माप(काष्ठा ocfs2_info_मुक्तfrag))
			status = ocfs2_info_handle_मुक्तfrag(inode, req);
		अवरोध;
	शेष:
		status = ocfs2_info_handle_unknown(inode, req);
		अवरोध;
	पूर्ण

bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_get_request_ptr(काष्ठा ocfs2_info *info, पूर्णांक idx,
				 u64 *req_addr, पूर्णांक compat_flag)
अणु
	पूर्णांक status = -EFAULT;
	u64 __user *bp = शून्य;

	अगर (compat_flag) अणु
#अगर_घोषित CONFIG_COMPAT
		/*
		 * poपूर्णांकer bp stores the base address of a poपूर्णांकers array,
		 * which collects all addresses of separate request.
		 */
		bp = (u64 __user *)(अचिन्हित दीर्घ)compat_ptr(info->oi_requests);
#अन्यथा
		BUG();
#पूर्ण_अगर
	पूर्ण अन्यथा
		bp = (u64 __user *)(अचिन्हित दीर्घ)(info->oi_requests);

	अगर (o2info_from_user(*req_addr, bp + idx))
		जाओ bail;

	status = 0;
bail:
	वापस status;
पूर्ण

/*
 * OCFS2_IOC_INFO handles an array of requests passed from userspace.
 *
 * ocfs2_info_handle() recevies a large info aggregation, grab and
 * validate the request count from header, then अवरोध it पूर्णांकo small
 * pieces, later specअगरic handlers can handle them one by one.
 *
 * Idea here is to make each separate request small enough to ensure
 * a better backward&क्रमward compatibility, since a small piece of
 * request will be less likely to be broken अगर disk layout get changed.
 */
अटल पूर्णांक ocfs2_info_handle(काष्ठा inode *inode, काष्ठा ocfs2_info *info,
			     पूर्णांक compat_flag)
अणु
	पूर्णांक i, status = 0;
	u64 req_addr;
	काष्ठा ocfs2_info_request __user *reqp;

	अगर ((info->oi_count > OCFS2_INFO_MAX_REQUEST) ||
	    (!info->oi_requests)) अणु
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	क्रम (i = 0; i < info->oi_count; i++) अणु

		status = ocfs2_get_request_ptr(info, i, &req_addr, compat_flag);
		अगर (status)
			अवरोध;

		reqp = (काष्ठा ocfs2_info_request __user *)(अचिन्हित दीर्घ)req_addr;
		अगर (!reqp) अणु
			status = -EINVAL;
			जाओ bail;
		पूर्ण

		status = ocfs2_info_handle_request(inode, reqp);
		अगर (status)
			अवरोध;
	पूर्ण

bail:
	वापस status;
पूर्ण

दीर्घ ocfs2_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक new_clusters;
	पूर्णांक status;
	काष्ठा ocfs2_space_resv sr;
	काष्ठा ocfs2_new_group_input input;
	काष्ठा reflink_arguments args;
	स्थिर अक्षर __user *old_path;
	स्थिर अक्षर __user *new_path;
	bool preserve;
	काष्ठा ocfs2_info info;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल OCFS2_IOC_RESVSP:
	हाल OCFS2_IOC_RESVSP64:
	हाल OCFS2_IOC_UNRESVSP:
	हाल OCFS2_IOC_UNRESVSP64:
		अगर (copy_from_user(&sr, (पूर्णांक __user *) arg, माप(sr)))
			वापस -EFAULT;

		वापस ocfs2_change_file_space(filp, cmd, &sr);
	हाल OCFS2_IOC_GROUP_EXTEND:
		अगर (!capable(CAP_SYS_RESOURCE))
			वापस -EPERM;

		अगर (get_user(new_clusters, (पूर्णांक __user *)arg))
			वापस -EFAULT;

		status = mnt_want_ग_लिखो_file(filp);
		अगर (status)
			वापस status;
		status = ocfs2_group_extend(inode, new_clusters);
		mnt_drop_ग_लिखो_file(filp);
		वापस status;
	हाल OCFS2_IOC_GROUP_ADD:
	हाल OCFS2_IOC_GROUP_ADD64:
		अगर (!capable(CAP_SYS_RESOURCE))
			वापस -EPERM;

		अगर (copy_from_user(&input, (पूर्णांक __user *) arg, माप(input)))
			वापस -EFAULT;

		status = mnt_want_ग_लिखो_file(filp);
		अगर (status)
			वापस status;
		status = ocfs2_group_add(inode, &input);
		mnt_drop_ग_लिखो_file(filp);
		वापस status;
	हाल OCFS2_IOC_REFLINK:
		अगर (copy_from_user(&args, argp, माप(args)))
			वापस -EFAULT;
		old_path = (स्थिर अक्षर __user *)(अचिन्हित दीर्घ)args.old_path;
		new_path = (स्थिर अक्षर __user *)(अचिन्हित दीर्घ)args.new_path;
		preserve = (args.preserve != 0);

		वापस ocfs2_reflink_ioctl(inode, old_path, new_path, preserve);
	हाल OCFS2_IOC_INFO:
		अगर (copy_from_user(&info, argp, माप(काष्ठा ocfs2_info)))
			वापस -EFAULT;

		वापस ocfs2_info_handle(inode, &info, 0);
	हाल FITRIM:
	अणु
		काष्ठा super_block *sb = inode->i_sb;
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
		काष्ठा fstrim_range range;
		पूर्णांक ret = 0;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (!blk_queue_discard(q))
			वापस -EOPNOTSUPP;

		अगर (copy_from_user(&range, argp, माप(range)))
			वापस -EFAULT;

		range.minlen = max_t(u64, q->limits.discard_granularity,
				     range.minlen);
		ret = ocfs2_trim_fs(sb, &range);
		अगर (ret < 0)
			वापस ret;

		अगर (copy_to_user(argp, &range, माप(range)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल OCFS2_IOC_MOVE_EXT:
		वापस ocfs2_ioctl_move_extents(filp, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ ocfs2_compat_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	bool preserve;
	काष्ठा reflink_arguments args;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ocfs2_info info;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल OCFS2_IOC_RESVSP:
	हाल OCFS2_IOC_RESVSP64:
	हाल OCFS2_IOC_UNRESVSP:
	हाल OCFS2_IOC_UNRESVSP64:
	हाल OCFS2_IOC_GROUP_EXTEND:
	हाल OCFS2_IOC_GROUP_ADD:
	हाल OCFS2_IOC_GROUP_ADD64:
		अवरोध;
	हाल OCFS2_IOC_REFLINK:
		अगर (copy_from_user(&args, argp, माप(args)))
			वापस -EFAULT;
		preserve = (args.preserve != 0);

		वापस ocfs2_reflink_ioctl(inode, compat_ptr(args.old_path),
					   compat_ptr(args.new_path), preserve);
	हाल OCFS2_IOC_INFO:
		अगर (copy_from_user(&info, argp, माप(काष्ठा ocfs2_info)))
			वापस -EFAULT;

		वापस ocfs2_info_handle(inode, &info, 1);
	हाल FITRIM:
	हाल OCFS2_IOC_MOVE_EXT:
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस ocfs2_ioctl(file, cmd, arg);
पूर्ण
#पूर्ण_अगर
