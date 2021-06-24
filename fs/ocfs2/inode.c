<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inode.c
 *
 * vfs' aops, fops, करोps and iops
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/iversion.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dir.h"
#समावेश "blockcheck.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "namei.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "symlink.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "xattr.h"
#समावेश "refcounttree.h"
#समावेश "ocfs2_trace.h"
#समावेश "filecheck.h"

#समावेश "buffer_head_io.h"

काष्ठा ocfs2_find_inode_args
अणु
	u64		fi_blkno;
	अचिन्हित दीर्घ	fi_ino;
	अचिन्हित पूर्णांक	fi_flags;
	अचिन्हित पूर्णांक	fi_sysfile_type;
पूर्ण;

अटल काष्ठा lock_class_key ocfs2_sysfile_lock_key[NUM_SYSTEM_INODES];

अटल पूर्णांक ocfs2_पढ़ो_locked_inode(काष्ठा inode *inode,
				   काष्ठा ocfs2_find_inode_args *args);
अटल पूर्णांक ocfs2_init_locked_inode(काष्ठा inode *inode, व्योम *opaque);
अटल पूर्णांक ocfs2_find_actor(काष्ठा inode *inode, व्योम *opaque);
अटल पूर्णांक ocfs2_truncate_क्रम_delete(काष्ठा ocfs2_super *osb,
				    काष्ठा inode *inode,
				    काष्ठा buffer_head *fe_bh);

अटल पूर्णांक ocfs2_filecheck_पढ़ो_inode_block_full(काष्ठा inode *inode,
						 काष्ठा buffer_head **bh,
						 पूर्णांक flags, पूर्णांक type);
अटल पूर्णांक ocfs2_filecheck_validate_inode_block(काष्ठा super_block *sb,
						काष्ठा buffer_head *bh);
अटल पूर्णांक ocfs2_filecheck_repair_inode_block(काष्ठा super_block *sb,
					      काष्ठा buffer_head *bh);

व्योम ocfs2_set_inode_flags(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक flags = OCFS2_I(inode)->ip_attr;

	inode->i_flags &= ~(S_IMMUTABLE |
		S_SYNC | S_APPEND | S_NOATIME | S_सूचीSYNC);

	अगर (flags & OCFS2_IMMUTABLE_FL)
		inode->i_flags |= S_IMMUTABLE;

	अगर (flags & OCFS2_SYNC_FL)
		inode->i_flags |= S_SYNC;
	अगर (flags & OCFS2_APPEND_FL)
		inode->i_flags |= S_APPEND;
	अगर (flags & OCFS2_NOATIME_FL)
		inode->i_flags |= S_NOATIME;
	अगर (flags & OCFS2_सूचीSYNC_FL)
		inode->i_flags |= S_सूचीSYNC;
पूर्ण

/* Propagate flags from i_flags to OCFS2_I(inode)->ip_attr */
व्योम ocfs2_get_inode_flags(काष्ठा ocfs2_inode_info *oi)
अणु
	अचिन्हित पूर्णांक flags = oi->vfs_inode.i_flags;

	oi->ip_attr &= ~(OCFS2_SYNC_FL|OCFS2_APPEND_FL|
			OCFS2_IMMUTABLE_FL|OCFS2_NOATIME_FL|OCFS2_सूचीSYNC_FL);
	अगर (flags & S_SYNC)
		oi->ip_attr |= OCFS2_SYNC_FL;
	अगर (flags & S_APPEND)
		oi->ip_attr |= OCFS2_APPEND_FL;
	अगर (flags & S_IMMUTABLE)
		oi->ip_attr |= OCFS2_IMMUTABLE_FL;
	अगर (flags & S_NOATIME)
		oi->ip_attr |= OCFS2_NOATIME_FL;
	अगर (flags & S_सूचीSYNC)
		oi->ip_attr |= OCFS2_सूचीSYNC_FL;
पूर्ण

काष्ठा inode *ocfs2_ilookup(काष्ठा super_block *sb, u64 blkno)
अणु
	काष्ठा ocfs2_find_inode_args args;

	args.fi_blkno = blkno;
	args.fi_flags = 0;
	args.fi_ino = ino_from_blkno(sb, blkno);
	args.fi_sysfile_type = 0;

	वापस ilookup5(sb, blkno, ocfs2_find_actor, &args);
पूर्ण
काष्ठा inode *ocfs2_iget(काष्ठा ocfs2_super *osb, u64 blkno, अचिन्हित flags,
			 पूर्णांक sysfile_type)
अणु
	पूर्णांक rc = -ESTALE;
	काष्ठा inode *inode = शून्य;
	काष्ठा super_block *sb = osb->sb;
	काष्ठा ocfs2_find_inode_args args;
	journal_t *journal = OCFS2_SB(sb)->journal->j_journal;

	trace_ocfs2_iget_begin((अचिन्हित दीर्घ दीर्घ)blkno, flags,
			       sysfile_type);

	/* Ok. By now we've either got the offsets passed to us by the
	 * caller, or we just pulled them off the bh. Lets करो some
	 * sanity checks to make sure they're OK. */
	अगर (blkno == 0) अणु
		inode = ERR_PTR(-EINVAL);
		mlog_त्रुटि_सं(PTR_ERR(inode));
		जाओ bail;
	पूर्ण

	args.fi_blkno = blkno;
	args.fi_flags = flags;
	args.fi_ino = ino_from_blkno(sb, blkno);
	args.fi_sysfile_type = sysfile_type;

	inode = iget5_locked(sb, args.fi_ino, ocfs2_find_actor,
			     ocfs2_init_locked_inode, &args);
	/* inode was *not* in the inode cache. 2.6.x requires
	 * us to करो our own पढ़ो_inode call and unlock it
	 * afterwards. */
	अगर (inode == शून्य) अणु
		inode = ERR_PTR(-ENOMEM);
		mlog_त्रुटि_सं(PTR_ERR(inode));
		जाओ bail;
	पूर्ण
	trace_ocfs2_iget5_locked(inode->i_state);
	अगर (inode->i_state & I_NEW) अणु
		rc = ocfs2_पढ़ो_locked_inode(inode, &args);
		unlock_new_inode(inode);
	पूर्ण
	अगर (is_bad_inode(inode)) अणु
		iput(inode);
		inode = ERR_PTR(rc);
		जाओ bail;
	पूर्ण

	/*
	 * Set transaction id's of transactions that have to be committed
	 * to finish f[data]sync. We set them to currently running transaction
	 * as we cannot be sure that the inode or some of its metadata isn't
	 * part of the transaction - the inode could have been reclaimed and
	 * now it is reपढ़ो from disk.
	 */
	अगर (journal) अणु
		transaction_t *transaction;
		tid_t tid;
		काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

		पढ़ो_lock(&journal->j_state_lock);
		अगर (journal->j_running_transaction)
			transaction = journal->j_running_transaction;
		अन्यथा
			transaction = journal->j_committing_transaction;
		अगर (transaction)
			tid = transaction->t_tid;
		अन्यथा
			tid = journal->j_commit_sequence;
		पढ़ो_unlock(&journal->j_state_lock);
		oi->i_sync_tid = tid;
		oi->i_datasync_tid = tid;
	पूर्ण

bail:
	अगर (!IS_ERR(inode)) अणु
		trace_ocfs2_iget_end(inode, 
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
	पूर्ण

	वापस inode;
पूर्ण


/*
 * here's how inodes get पढ़ो from disk:
 * iget5_locked -> find_actor -> OCFS2_FIND_ACTOR
 * found? : वापस the in-memory inode
 * not found? : get_new_inode -> OCFS2_INIT_LOCKED_INODE
 */

अटल पूर्णांक ocfs2_find_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा ocfs2_find_inode_args *args = शून्य;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	पूर्णांक ret = 0;

	args = opaque;

	mlog_bug_on_msg(!inode, "No inode in find actor!\n");

	trace_ocfs2_find_actor(inode, inode->i_ino, opaque, args->fi_blkno);

	अगर (oi->ip_blkno != args->fi_blkno)
		जाओ bail;

	ret = 1;
bail:
	वापस ret;
पूर्ण

/*
 * initialize the new inode, but करोn't करो anything that would cause
 * us to sleep.
 * वापस 0 on success, 1 on failure
 */
अटल पूर्णांक ocfs2_init_locked_inode(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा ocfs2_find_inode_args *args = opaque;
	अटल काष्ठा lock_class_key ocfs2_quota_ip_alloc_sem_key,
				     ocfs2_file_ip_alloc_sem_key;

	inode->i_ino = args->fi_ino;
	OCFS2_I(inode)->ip_blkno = args->fi_blkno;
	अगर (args->fi_sysfile_type != 0)
		lockdep_set_class(&inode->i_rwsem,
			&ocfs2_sysfile_lock_key[args->fi_sysfile_type]);
	अगर (args->fi_sysfile_type == USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == GROUP_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_GROUP_QUOTA_SYSTEM_INODE)
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_quota_ip_alloc_sem_key);
	अन्यथा
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_file_ip_alloc_sem_key);

	वापस 0;
पूर्ण

व्योम ocfs2_populate_inode(काष्ठा inode *inode, काष्ठा ocfs2_dinode *fe,
			  पूर्णांक create_ino)
अणु
	काष्ठा super_block *sb;
	काष्ठा ocfs2_super *osb;
	पूर्णांक use_plocks = 1;

	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	अगर ((osb->s_mount_opt & OCFS2_MOUNT_LOCALFLOCKS) ||
	    ocfs2_mount_local(osb) || !ocfs2_stack_supports_plocks())
		use_plocks = 0;

	/*
	 * These have all been checked by ocfs2_पढ़ो_inode_block() or set
	 * by ocfs2_mknod_locked(), so a failure is a code bug.
	 */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));  /* This means that पढ़ो_inode
						cannot create a superblock
						inode today.  change अगर
						that is needed. */
	BUG_ON(!(fe->i_flags & cpu_to_le32(OCFS2_VALID_FL)));
	BUG_ON(le32_to_cpu(fe->i_fs_generation) != osb->fs_generation);


	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	OCFS2_I(inode)->ip_attr = le32_to_cpu(fe->i_attr);
	OCFS2_I(inode)->ip_dyn_features = le16_to_cpu(fe->i_dyn_features);

	inode_set_iversion(inode, 1);
	inode->i_generation = le32_to_cpu(fe->i_generation);
	inode->i_rdev = huge_decode_dev(le64_to_cpu(fe->id1.dev1.i_rdev));
	inode->i_mode = le16_to_cpu(fe->i_mode);
	i_uid_ग_लिखो(inode, le32_to_cpu(fe->i_uid));
	i_gid_ग_लिखो(inode, le32_to_cpu(fe->i_gid));

	/* Fast symlinks will have i_size but no allocated clusters. */
	अगर (S_ISLNK(inode->i_mode) && !fe->i_clusters) अणु
		inode->i_blocks = 0;
		inode->i_mapping->a_ops = &ocfs2_fast_symlink_aops;
	पूर्ण अन्यथा अणु
		inode->i_blocks = ocfs2_inode_sector_count(inode);
		inode->i_mapping->a_ops = &ocfs2_aops;
	पूर्ण
	inode->i_aसमय.tv_sec = le64_to_cpu(fe->i_aसमय);
	inode->i_aसमय.tv_nsec = le32_to_cpu(fe->i_aसमय_nsec);
	inode->i_mसमय.tv_sec = le64_to_cpu(fe->i_mसमय);
	inode->i_mसमय.tv_nsec = le32_to_cpu(fe->i_mसमय_nsec);
	inode->i_स_समय.tv_sec = le64_to_cpu(fe->i_स_समय);
	inode->i_स_समय.tv_nsec = le32_to_cpu(fe->i_स_समय_nsec);

	अगर (OCFS2_I(inode)->ip_blkno != le64_to_cpu(fe->i_blkno))
		mlog(ML_ERROR,
		     "ip_blkno %llu != i_blkno %llu!\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(fe->i_blkno));

	set_nlink(inode, ocfs2_पढ़ो_links_count(fe));

	trace_ocfs2_populate_inode(OCFS2_I(inode)->ip_blkno,
				   le32_to_cpu(fe->i_flags));
	अगर (fe->i_flags & cpu_to_le32(OCFS2_SYSTEM_FL)) अणु
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_SYSTEM_खाता;
		inode->i_flags |= S_NOQUOTA;
	पूर्ण
  
	अगर (fe->i_flags & cpu_to_le32(OCFS2_LOCAL_ALLOC_FL)) अणु
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_BITMAP;
	पूर्ण अन्यथा अगर (fe->i_flags & cpu_to_le32(OCFS2_BITMAP_FL)) अणु
		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_BITMAP;
	पूर्ण अन्यथा अगर (fe->i_flags & cpu_to_le32(OCFS2_QUOTA_FL)) अणु
		inode->i_flags |= S_NOQUOTA;
	पूर्ण अन्यथा अगर (fe->i_flags & cpu_to_le32(OCFS2_SUPER_BLOCK_FL)) अणु
		/* we can't actually hit this as read_inode can't
		 * handle superblocks today ;-) */
		BUG();
	पूर्ण

	चयन (inode->i_mode & S_IFMT) अणु
	    हाल S_IFREG:
		    अगर (use_plocks)
			    inode->i_fop = &ocfs2_fops;
		    अन्यथा
			    inode->i_fop = &ocfs2_fops_no_plocks;
		    inode->i_op = &ocfs2_file_iops;
		    i_size_ग_लिखो(inode, le64_to_cpu(fe->i_size));
		    अवरोध;
	    हाल S_IFसूची:
		    inode->i_op = &ocfs2_dir_iops;
		    अगर (use_plocks)
			    inode->i_fop = &ocfs2_करोps;
		    अन्यथा
			    inode->i_fop = &ocfs2_करोps_no_plocks;
		    i_size_ग_लिखो(inode, le64_to_cpu(fe->i_size));
		    OCFS2_I(inode)->ip_dir_lock_gen = 1;
		    अवरोध;
	    हाल S_IFLNK:
		    inode->i_op = &ocfs2_symlink_inode_operations;
		    inode_nohighmem(inode);
		    i_size_ग_लिखो(inode, le64_to_cpu(fe->i_size));
		    अवरोध;
	    शेष:
		    inode->i_op = &ocfs2_special_file_iops;
		    init_special_inode(inode, inode->i_mode,
				       inode->i_rdev);
		    अवरोध;
	पूर्ण

	अगर (create_ino) अणु
		inode->i_ino = ino_from_blkno(inode->i_sb,
			       le64_to_cpu(fe->i_blkno));

		/*
		 * If we ever want to create प्रणाली files from kernel,
		 * the generation argument to
		 * ocfs2_inode_lock_res_init() will have to change.
		 */
		BUG_ON(le32_to_cpu(fe->i_flags) & OCFS2_SYSTEM_FL);

		ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_inode_lockres,
					  OCFS2_LOCK_TYPE_META, 0, inode);

		ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_खोलो_lockres,
					  OCFS2_LOCK_TYPE_OPEN, 0, inode);
	पूर्ण

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_rw_lockres,
				  OCFS2_LOCK_TYPE_RW, inode->i_generation,
				  inode);

	ocfs2_set_inode_flags(inode);

	OCFS2_I(inode)->ip_last_used_slot = 0;
	OCFS2_I(inode)->ip_last_used_group = 0;

	अगर (S_ISसूची(inode->i_mode))
		ocfs2_resv_set_type(&OCFS2_I(inode)->ip_la_data_resv,
				    OCFS2_RESV_FLAG_सूची);
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_locked_inode(काष्ठा inode *inode,
				   काष्ठा ocfs2_find_inode_args *args)
अणु
	काष्ठा super_block *sb;
	काष्ठा ocfs2_super *osb;
	काष्ठा ocfs2_dinode *fe;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक status, can_lock, lock_level = 0;
	u32 generation = 0;

	status = -EINVAL;
	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	/*
	 * To improve perक्रमmance of cold-cache inode stats, we take
	 * the cluster lock here अगर possible.
	 *
	 * Generally, OCFS2 never trusts the contents of an inode
	 * unless it's holding a cluster lock, so taking it here isn't
	 * a correctness issue as much as it is a perक्रमmance
	 * improvement.
	 *
	 * There are three बार when taking the lock is not a good idea:
	 *
	 * 1) During startup, beक्रमe we have initialized the DLM.
	 *
	 * 2) If we are पढ़ोing certain प्रणाली files which never get
	 *    cluster locks (local alloc, truncate log).
	 *
	 * 3) If the process करोing the iget() is responsible क्रम
	 *    orphan dir recovery. We're holding the orphan dir lock and
	 *    can get पूर्णांकo a deadlock with another process on another
	 *    node in ->delete_inode().
	 *
	 * #1 and #2 can be simply solved by never taking the lock
	 * here क्रम प्रणाली files (which are the only type we पढ़ो
	 * during mount). It's a heavier approach, but our मुख्य
	 * concern is user-accessible files anyway.
	 *
	 * #3 works itself out because we'll eventually take the
	 * cluster lock beक्रमe trusting anything anyway.
	 */
	can_lock = !(args->fi_flags & OCFS2_FI_FLAG_SYSखाता)
		&& !(args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY)
		&& !ocfs2_mount_local(osb);

	trace_ocfs2_पढ़ो_locked_inode(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno, can_lock);

	/*
	 * To मुख्यtain backwards compatibility with older versions of
	 * ocfs2-tools, we still store the generation value क्रम प्रणाली
	 * files. The only ones that actually matter to userspace are
	 * the journals, but it's easier and inexpensive to just flag
	 * all प्रणाली files similarly.
	 */
	अगर (args->fi_flags & OCFS2_FI_FLAG_SYSखाता)
		generation = osb->fs_generation;

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_inode_lockres,
				  OCFS2_LOCK_TYPE_META,
				  generation, inode);

	ocfs2_inode_lock_res_init(&OCFS2_I(inode)->ip_खोलो_lockres,
				  OCFS2_LOCK_TYPE_OPEN,
				  0, inode);

	अगर (can_lock) अणु
		status = ocfs2_खोलो_lock(inode);
		अगर (status) अणु
			make_bad_inode(inode);
			mlog_त्रुटि_सं(status);
			वापस status;
		पूर्ण
		status = ocfs2_inode_lock(inode, शून्य, lock_level);
		अगर (status) अणु
			make_bad_inode(inode);
			mlog_त्रुटि_सं(status);
			वापस status;
		पूर्ण
	पूर्ण

	अगर (args->fi_flags & OCFS2_FI_FLAG_ORPHAN_RECOVERY) अणु
		status = ocfs2_try_खोलो_lock(inode, 0);
		अगर (status) अणु
			make_bad_inode(inode);
			वापस status;
		पूर्ण
	पूर्ण

	अगर (can_lock) अणु
		अगर (args->fi_flags & OCFS2_FI_FLAG_खाताCHECK_CHK)
			status = ocfs2_filecheck_पढ़ो_inode_block_full(inode,
						&bh, OCFS2_BH_IGNORE_CACHE, 0);
		अन्यथा अगर (args->fi_flags & OCFS2_FI_FLAG_खाताCHECK_FIX)
			status = ocfs2_filecheck_पढ़ो_inode_block_full(inode,
						&bh, OCFS2_BH_IGNORE_CACHE, 1);
		अन्यथा
			status = ocfs2_पढ़ो_inode_block_full(inode,
						&bh, OCFS2_BH_IGNORE_CACHE);
	पूर्ण अन्यथा अणु
		status = ocfs2_पढ़ो_blocks_sync(osb, args->fi_blkno, 1, &bh);
		/*
		 * If buffer is in jbd, then its checksum may not have been
		 * computed as yet.
		 */
		अगर (!status && !buffer_jbd(bh)) अणु
			अगर (args->fi_flags & OCFS2_FI_FLAG_खाताCHECK_CHK)
				status = ocfs2_filecheck_validate_inode_block(
								osb->sb, bh);
			अन्यथा अगर (args->fi_flags & OCFS2_FI_FLAG_खाताCHECK_FIX)
				status = ocfs2_filecheck_repair_inode_block(
								osb->sb, bh);
			अन्यथा
				status = ocfs2_validate_inode_block(
								osb->sb, bh);
		पूर्ण
	पूर्ण
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = -EINVAL;
	fe = (काष्ठा ocfs2_dinode *) bh->b_data;

	/*
	 * This is a code bug. Right now the caller needs to
	 * understand whether it is asking क्रम a प्रणाली file inode or
	 * not so the proper lock names can be built.
	 */
	mlog_bug_on_msg(!!(fe->i_flags & cpu_to_le32(OCFS2_SYSTEM_FL)) !=
			!!(args->fi_flags & OCFS2_FI_FLAG_SYSखाता),
			"Inode %llu: system file state is ambiguous\n",
			(अचिन्हित दीर्घ दीर्घ)args->fi_blkno);

	अगर (S_ISCHR(le16_to_cpu(fe->i_mode)) ||
	    S_ISBLK(le16_to_cpu(fe->i_mode)))
		inode->i_rdev = huge_decode_dev(le64_to_cpu(fe->id1.dev1.i_rdev));

	ocfs2_populate_inode(inode, fe, 0);

	BUG_ON(args->fi_blkno != le64_to_cpu(fe->i_blkno));

	अगर (buffer_dirty(bh) && !buffer_jbd(bh)) अणु
		अगर (can_lock) अणु
			ocfs2_inode_unlock(inode, lock_level);
			lock_level = 1;
			ocfs2_inode_lock(inode, शून्य, lock_level);
		पूर्ण
		status = ocfs2_ग_लिखो_block(osb, bh, INODE_CACHE(inode));
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	status = 0;

bail:
	अगर (can_lock)
		ocfs2_inode_unlock(inode, lock_level);

	अगर (status < 0)
		make_bad_inode(inode);

	brअन्यथा(bh);

	वापस status;
पूर्ण

व्योम ocfs2_sync_blockdev(काष्ठा super_block *sb)
अणु
	sync_blockdev(sb->s_bdev);
पूर्ण

अटल पूर्णांक ocfs2_truncate_क्रम_delete(काष्ठा ocfs2_super *osb,
				     काष्ठा inode *inode,
				     काष्ठा buffer_head *fe_bh)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_dinode *fe;
	handle_t *handle = शून्य;

	fe = (काष्ठा ocfs2_dinode *) fe_bh->b_data;

	/*
	 * This check will also skip truncate of inodes with अंतरभूत
	 * data and fast symlinks.
	 */
	अगर (fe->i_clusters) अणु
		अगर (ocfs2_should_order_data(inode))
			ocfs2_begin_ordered_truncate(inode, 0);

		handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
		अगर (IS_ERR(handle)) अणु
			status = PTR_ERR(handle);
			handle = शून्य;
			mlog_त्रुटि_सं(status);
			जाओ out;
		पूर्ण

		status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
						 fe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out;
		पूर्ण

		i_size_ग_लिखो(inode, 0);

		status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ out;
		पूर्ण

		ocfs2_commit_trans(osb, handle);
		handle = शून्य;

		status = ocfs2_commit_truncate(osb, inode, fe_bh);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

out:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_हटाओ_inode(काष्ठा inode *inode,
			      काष्ठा buffer_head *di_bh,
			      काष्ठा inode *orphan_dir_inode,
			      काष्ठा buffer_head *orphan_dir_bh)
अणु
	पूर्णांक status;
	काष्ठा inode *inode_alloc_inode = शून्य;
	काष्ठा buffer_head *inode_alloc_bh = शून्य;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) di_bh->b_data;

	inode_alloc_inode =
		ocfs2_get_प्रणाली_file_inode(osb, INODE_ALLOC_SYSTEM_INODE,
					    le16_to_cpu(di->i_suballoc_slot));
	अगर (!inode_alloc_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	inode_lock(inode_alloc_inode);
	status = ocfs2_inode_lock(inode_alloc_inode, &inode_alloc_bh, 1);
	अगर (status < 0) अणु
		inode_unlock(inode_alloc_inode);

		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_DELETE_INODE_CREDITS +
				   ocfs2_quota_trans_credits(inode->i_sb));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock;
	पूर्ण

	अगर (!(OCFS2_I(inode)->ip_flags & OCFS2_INODE_SKIP_ORPHAN_सूची)) अणु
		status = ocfs2_orphan_del(osb, handle, orphan_dir_inode, inode,
					  orphan_dir_bh, false);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail_commit;
		पूर्ण
	पूर्ण

	/* set the inodes dसमय */
	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_commit;
	पूर्ण

	di->i_dसमय = cpu_to_le64(kसमय_get_real_seconds());
	di->i_flags &= cpu_to_le32(~(OCFS2_VALID_FL | OCFS2_ORPHANED_FL));
	ocfs2_journal_dirty(handle, di_bh);

	ocfs2_हटाओ_from_cache(INODE_CACHE(inode), di_bh);
	dquot_मुक्त_inode(inode);

	status = ocfs2_मुक्त_dinode(handle, inode_alloc_inode,
				   inode_alloc_bh, di);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

bail_commit:
	ocfs2_commit_trans(osb, handle);
bail_unlock:
	ocfs2_inode_unlock(inode_alloc_inode, 1);
	inode_unlock(inode_alloc_inode);
	brअन्यथा(inode_alloc_bh);
bail:
	iput(inode_alloc_inode);

	वापस status;
पूर्ण

/*
 * Serialize with orphan dir recovery. If the process करोing
 * recovery on this orphan dir करोes an iget() with the dir
 * i_mutex held, we'll deadlock here. Instead we detect this
 * and निकास early - recovery will wipe this inode क्रम us.
 */
अटल पूर्णांक ocfs2_check_orphan_recovery_state(काष्ठा ocfs2_super *osb,
					     पूर्णांक slot)
अणु
	पूर्णांक ret = 0;

	spin_lock(&osb->osb_lock);
	अगर (ocfs2_node_map_test_bit(osb, &osb->osb_recovering_orphan_dirs, slot)) अणु
		ret = -EDEADLK;
		जाओ out;
	पूर्ण
	/* This संकेतs to the orphan recovery process that it should
	 * रुको क्रम us to handle the wipe. */
	osb->osb_orphan_wipes[slot]++;
out:
	spin_unlock(&osb->osb_lock);
	trace_ocfs2_check_orphan_recovery_state(slot, ret);
	वापस ret;
पूर्ण

अटल व्योम ocfs2_संकेत_wipe_completion(काष्ठा ocfs2_super *osb,
					 पूर्णांक slot)
अणु
	spin_lock(&osb->osb_lock);
	osb->osb_orphan_wipes[slot]--;
	spin_unlock(&osb->osb_lock);

	wake_up(&osb->osb_wipe_event);
पूर्ण

अटल पूर्णांक ocfs2_wipe_inode(काष्ठा inode *inode,
			    काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक status, orphaned_slot = -1;
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) di_bh->b_data;

	अगर (!(OCFS2_I(inode)->ip_flags & OCFS2_INODE_SKIP_ORPHAN_सूची)) अणु
		orphaned_slot = le16_to_cpu(di->i_orphaned_slot);

		status = ocfs2_check_orphan_recovery_state(osb, orphaned_slot);
		अगर (status)
			वापस status;

		orphan_dir_inode = ocfs2_get_प्रणाली_file_inode(osb,
							       ORPHAN_सूची_SYSTEM_INODE,
							       orphaned_slot);
		अगर (!orphan_dir_inode) अणु
			status = -ENOENT;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* Lock the orphan dir. The lock will be held क्रम the entire
		 * delete_inode operation. We करो this now to aव्योम races with
		 * recovery completion on other nodes. */
		inode_lock(orphan_dir_inode);
		status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
		अगर (status < 0) अणु
			inode_unlock(orphan_dir_inode);

			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* we करो this जबतक holding the orphan dir lock because we
	 * करोn't want recovery being run from another node to try an
	 * inode delete underneath us -- this will result in two nodes
	 * truncating the same file! */
	status = ocfs2_truncate_क्रम_delete(osb, inode, di_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_dir;
	पूर्ण

	/* Remove any dir index tree */
	अगर (S_ISसूची(inode->i_mode)) अणु
		status = ocfs2_dx_dir_truncate(inode, di_bh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail_unlock_dir;
		पूर्ण
	पूर्ण

	/*Free extended attribute resources associated with this inode.*/
	status = ocfs2_xattr_हटाओ(inode, di_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_dir;
	पूर्ण

	status = ocfs2_हटाओ_refcount_tree(inode, di_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_dir;
	पूर्ण

	status = ocfs2_हटाओ_inode(inode, di_bh, orphan_dir_inode,
				    orphan_dir_bh);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

bail_unlock_dir:
	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SKIP_ORPHAN_सूची)
		वापस status;

	ocfs2_inode_unlock(orphan_dir_inode, 1);
	inode_unlock(orphan_dir_inode);
	brअन्यथा(orphan_dir_bh);
bail:
	iput(orphan_dir_inode);
	ocfs2_संकेत_wipe_completion(osb, orphaned_slot);

	वापस status;
पूर्ण

/* There is a series of simple checks that should be करोne beक्रमe a
 * trylock is even considered. Encapsulate those in this function. */
अटल पूर्णांक ocfs2_inode_is_valid_to_delete(काष्ठा inode *inode)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	trace_ocfs2_inode_is_valid_to_delete(current, osb->dc_task,
					     (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
					     oi->ip_flags);

	/* We shouldn't be getting here क्रम the root directory
	 * inode.. */
	अगर (inode == osb->root_inode) अणु
		mlog(ML_ERROR, "Skipping delete of root inode.\n");
		जाओ bail;
	पूर्ण

	/*
	 * If we're coming from downconvert_thread we can't go पूर्णांकo our own
	 * voting [hello, deadlock city!] so we cannot delete the inode. But
	 * since we dropped last inode ref when करोwnconverting dentry lock,
	 * we cannot have the file खोलो and thus the node करोing unlink will
	 * take care of deleting the inode.
	 */
	अगर (current == osb->dc_task)
		जाओ bail;

	spin_lock(&oi->ip_lock);
	/* OCFS2 *never* deletes प्रणाली files. This should technically
	 * never get here as प्रणाली file inodes should always have a
	 * positive link count. */
	अगर (oi->ip_flags & OCFS2_INODE_SYSTEM_खाता) अणु
		mlog(ML_ERROR, "Skipping delete of system file %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);
		जाओ bail_unlock;
	पूर्ण

	ret = 1;
bail_unlock:
	spin_unlock(&oi->ip_lock);
bail:
	वापस ret;
पूर्ण

/* Query the cluster to determine whether we should wipe an inode from
 * disk or not.
 *
 * Requires the inode to have the cluster lock. */
अटल पूर्णांक ocfs2_query_inode_wipe(काष्ठा inode *inode,
				  काष्ठा buffer_head *di_bh,
				  पूर्णांक *wipe)
अणु
	पूर्णांक status = 0, reason = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di;

	*wipe = 0;

	trace_ocfs2_query_inode_wipe_begin((अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
					   inode->i_nlink);

	/* While we were रुकोing क्रम the cluster lock in
	 * ocfs2_delete_inode, another node might have asked to delete
	 * the inode. Recheck our flags to catch this. */
	अगर (!ocfs2_inode_is_valid_to_delete(inode)) अणु
		reason = 1;
		जाओ bail;
	पूर्ण

	/* Now that we have an up to date inode, we can द्विगुन check
	 * the link count. */
	अगर (inode->i_nlink)
		जाओ bail;

	/* Do some basic inode verअगरication... */
	di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	अगर (!(di->i_flags & cpu_to_le32(OCFS2_ORPHANED_FL)) &&
	    !(oi->ip_flags & OCFS2_INODE_SKIP_ORPHAN_सूची)) अणु
		/*
		 * Inodes in the orphan dir must have ORPHANED_FL.  The only
		 * inodes that come back out of the orphan dir are reflink
		 * tarमाला_लो. A reflink target may be moved out of the orphan
		 * dir between the समय we scan the directory and the समय we
		 * process it. This would lead to HAS_REFCOUNT_FL being set but
		 * ORPHANED_FL not.
		 */
		अगर (di->i_dyn_features & cpu_to_le16(OCFS2_HAS_REFCOUNT_FL)) अणु
			reason = 2;
			जाओ bail;
		पूर्ण

		/* क्रम lack of a better error? */
		status = -EEXIST;
		mlog(ML_ERROR,
		     "Inode %llu (on-disk %llu) not orphaned! "
		     "Disk flags  0x%x, inode flags 0x%x\n",
		     (अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno),
		     le32_to_cpu(di->i_flags), oi->ip_flags);
		जाओ bail;
	पूर्ण

	/* has someone alपढ़ोy deleted us?! baaad... */
	अगर (di->i_dसमय) अणु
		status = -EEXIST;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/*
	 * This is how ocfs2 determines whether an inode is still live
	 * within the cluster. Every node takes a shared पढ़ो lock on
	 * the inode खोलो lock in ocfs2_पढ़ो_locked_inode(). When we
	 * get to ->delete_inode(), each node tries to convert it's
	 * lock to an exclusive. Trylocks are serialized by the inode
	 * meta data lock. If the upconvert succeeds, we know the inode
	 * is no दीर्घer live and can be deleted.
	 *
	 * Though we call this with the meta data lock held, the
	 * trylock keeps us from ABBA deadlock.
	 */
	status = ocfs2_try_खोलो_lock(inode, 1);
	अगर (status == -EAGAIN) अणु
		status = 0;
		reason = 3;
		जाओ bail;
	पूर्ण
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	*wipe = 1;
	trace_ocfs2_query_inode_wipe_succ(le16_to_cpu(di->i_orphaned_slot));

bail:
	trace_ocfs2_query_inode_wipe_end(status, reason);
	वापस status;
पूर्ण

/* Support function क्रम ocfs2_delete_inode. Will help us keep the
 * inode data in a consistent state क्रम clear_inode. Always truncates
 * pages, optionally sync's them first. */
अटल व्योम ocfs2_cleanup_delete_inode(काष्ठा inode *inode,
				       पूर्णांक sync_data)
अणु
	trace_ocfs2_cleanup_delete_inode(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno, sync_data);
	अगर (sync_data)
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
	truncate_inode_pages_final(&inode->i_data);
पूर्ण

अटल व्योम ocfs2_delete_inode(काष्ठा inode *inode)
अणु
	पूर्णांक wipe, status;
	sigset_t oldset;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di = शून्य;

	trace_ocfs2_delete_inode(inode->i_ino,
				 (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				 is_bad_inode(inode));

	/* When we fail in पढ़ो_inode() we mark inode as bad. The second test
	 * catches the हाल when inode allocation fails beक्रमe allocating
	 * a block क्रम inode. */
	अगर (is_bad_inode(inode) || !OCFS2_I(inode)->ip_blkno)
		जाओ bail;

	अगर (!ocfs2_inode_is_valid_to_delete(inode)) अणु
		/* It's probably not necessary to truncate_inode_pages
		 * here but we करो it क्रम safety anyway (it will most
		 * likely be a no-op anyway) */
		ocfs2_cleanup_delete_inode(inode, 0);
		जाओ bail;
	पूर्ण

	dquot_initialize(inode);

	/* We want to block संकेतs in delete_inode as the lock and
	 * messaging paths may वापस us -ERESTARTSYS. Which would
	 * cause us to निकास early, resulting in inodes being orphaned
	 * क्रमever. */
	ocfs2_block_संकेतs(&oldset);

	/*
	 * Synchronize us against ocfs2_get_dentry. We take this in
	 * shared mode so that all nodes can still concurrently
	 * process deletes.
	 */
	status = ocfs2_nfs_sync_lock(OCFS2_SB(inode->i_sb), 0);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "getting nfs sync lock(PR) failed %d\n", status);
		ocfs2_cleanup_delete_inode(inode, 0);
		जाओ bail_unblock;
	पूर्ण
	/* Lock करोwn the inode. This gives us an up to date view of
	 * it's metadata (क्रम verअगरication), and allows us to
	 * serialize delete_inode on multiple nodes.
	 *
	 * Even though we might be करोing a truncate, we करोn't take the
	 * allocation lock here as it won't be needed - nobody will
	 * have the file खोलो.
	 */
	status = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		ocfs2_cleanup_delete_inode(inode, 0);
		जाओ bail_unlock_nfs_sync;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	/* Skip inode deletion and रुको क्रम dio orphan entry recovered
	 * first */
	अगर (unlikely(di->i_flags & cpu_to_le32(OCFS2_DIO_ORPHANED_FL))) अणु
		ocfs2_cleanup_delete_inode(inode, 0);
		जाओ bail_unlock_inode;
	पूर्ण

	/* Query the cluster. This will be the final decision made
	 * beक्रमe we go ahead and wipe the inode. */
	status = ocfs2_query_inode_wipe(inode, di_bh, &wipe);
	अगर (!wipe || status < 0) अणु
		/* Error and remote inode busy both mean we won't be
		 * removing the inode, so they take almost the same
		 * path. */
		अगर (status < 0)
			mlog_त्रुटि_सं(status);

		/* Someone in the cluster has disallowed a wipe of
		 * this inode, or it was never completely
		 * orphaned. Write out the pages and निकास now. */
		ocfs2_cleanup_delete_inode(inode, 1);
		जाओ bail_unlock_inode;
	पूर्ण

	ocfs2_cleanup_delete_inode(inode, 0);

	status = ocfs2_wipe_inode(inode, di_bh);
	अगर (status < 0) अणु
		अगर (status != -EDEADLK)
			mlog_त्रुटि_सं(status);
		जाओ bail_unlock_inode;
	पूर्ण

	/*
	 * Mark the inode as successfully deleted.
	 *
	 * This is important क्रम ocfs2_clear_inode() as it will check
	 * this flag and skip any checkpoपूर्णांकing work
	 *
	 * ocfs2_stuff_meta_lvb() also uses this flag to invalidate
	 * the LVB क्रम other nodes.
	 */
	OCFS2_I(inode)->ip_flags |= OCFS2_INODE_DELETED;

bail_unlock_inode:
	ocfs2_inode_unlock(inode, 1);
	brअन्यथा(di_bh);

bail_unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(OCFS2_SB(inode->i_sb), 0);

bail_unblock:
	ocfs2_unblock_संकेतs(&oldset);
bail:
	वापस;
पूर्ण

अटल व्योम ocfs2_clear_inode(काष्ठा inode *inode)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	clear_inode(inode);
	trace_ocfs2_clear_inode((अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
				inode->i_nlink);

	mlog_bug_on_msg(osb == शून्य,
			"Inode=%lu\n", inode->i_ino);

	dquot_drop(inode);

	/* To preven remote deletes we hold खोलो lock beक्रमe, now it
	 * is समय to unlock PR and EX खोलो locks. */
	ocfs2_खोलो_unlock(inode);

	/* Do these beक्रमe all the other work so that we करोn't bounce
	 * the करोwnconvert thपढ़ो जबतक रुकोing to destroy the locks. */
	ocfs2_mark_lockres_मुक्तing(osb, &oi->ip_rw_lockres);
	ocfs2_mark_lockres_मुक्तing(osb, &oi->ip_inode_lockres);
	ocfs2_mark_lockres_मुक्तing(osb, &oi->ip_खोलो_lockres);

	ocfs2_resv_discard(&osb->osb_la_resmap,
			   &oi->ip_la_data_resv);
	ocfs2_resv_init_once(&oi->ip_la_data_resv);

	/* We very well may get a clear_inode beक्रमe all an inodes
	 * metadata has hit disk. Of course, we can't drop any cluster
	 * locks until the journal has finished with it. The only
	 * exception here are successfully wiped inodes - their
	 * metadata can now be considered to be part of the प्रणाली
	 * inodes from which it came. */
	अगर (!(oi->ip_flags & OCFS2_INODE_DELETED))
		ocfs2_checkpoपूर्णांक_inode(inode);

	mlog_bug_on_msg(!list_empty(&oi->ip_io_markers),
			"Clear inode of %llu, inode has io markers\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);
	mlog_bug_on_msg(!list_empty(&oi->ip_unwritten_list),
			"Clear inode of %llu, inode has unwritten extents\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);

	ocfs2_extent_map_trunc(inode, 0);

	status = ocfs2_drop_inode_locks(inode);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	ocfs2_lock_res_मुक्त(&oi->ip_rw_lockres);
	ocfs2_lock_res_मुक्त(&oi->ip_inode_lockres);
	ocfs2_lock_res_मुक्त(&oi->ip_खोलो_lockres);

	ocfs2_metadata_cache_निकास(INODE_CACHE(inode));

	mlog_bug_on_msg(INODE_CACHE(inode)->ci_num_cached,
			"Clear inode of %llu, inode has %u cache items\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
			INODE_CACHE(inode)->ci_num_cached);

	mlog_bug_on_msg(!(INODE_CACHE(inode)->ci_flags & OCFS2_CACHE_FL_INLINE),
			"Clear inode of %llu, inode has a bad flag\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);

	mlog_bug_on_msg(spin_is_locked(&oi->ip_lock),
			"Clear inode of %llu, inode is locked\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);

	mlog_bug_on_msg(!mutex_trylock(&oi->ip_io_mutex),
			"Clear inode of %llu, io_mutex is locked\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);
	mutex_unlock(&oi->ip_io_mutex);

	/*
	 * करोwn_trylock() वापसs 0, करोwn_ग_लिखो_trylock() वापसs 1
	 * kernel 1, world 0
	 */
	mlog_bug_on_msg(!करोwn_ग_लिखो_trylock(&oi->ip_alloc_sem),
			"Clear inode of %llu, alloc_sem is locked\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);
	up_ग_लिखो(&oi->ip_alloc_sem);

	mlog_bug_on_msg(oi->ip_खोलो_count,
			"Clear inode of %llu has open count %d\n",
			(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno, oi->ip_खोलो_count);

	/* Clear all other flags. */
	oi->ip_flags = 0;
	oi->ip_dir_start_lookup = 0;
	oi->ip_blkno = 0ULL;

	/*
	 * ip_jinode is used to track txns against this inode. We ensure that
	 * the journal is flushed beक्रमe journal shutकरोwn. Thus it is safe to
	 * have inodes get cleaned up after journal shutकरोwn.
	 */
	jbd2_journal_release_jbd_inode(osb->journal->j_journal,
				       &oi->ip_jinode);
पूर्ण

व्योम ocfs2_evict_inode(काष्ठा inode *inode)
अणु
	अगर (!inode->i_nlink ||
	    (OCFS2_I(inode)->ip_flags & OCFS2_INODE_MAYBE_ORPHANED)) अणु
		ocfs2_delete_inode(inode);
	पूर्ण अन्यथा अणु
		truncate_inode_pages_final(&inode->i_data);
	पूर्ण
	ocfs2_clear_inode(inode);
पूर्ण

/* Called under inode_lock, with no more references on the
 * काष्ठा inode, so it's safe here to check the flags field
 * and to manipulate i_nlink without any other locks. */
पूर्णांक ocfs2_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	trace_ocfs2_drop_inode((अचिन्हित दीर्घ दीर्घ)oi->ip_blkno,
				inode->i_nlink, oi->ip_flags);

	निश्चित_spin_locked(&inode->i_lock);
	inode->i_state |= I_WILL_FREE;
	spin_unlock(&inode->i_lock);
	ग_लिखो_inode_now(inode, 1);
	spin_lock(&inode->i_lock);
	WARN_ON(inode->i_state & I_NEW);
	inode->i_state &= ~I_WILL_FREE;

	वापस 1;
पूर्ण

/*
 * This is called from our getattr.
 */
पूर्णांक ocfs2_inode_revalidate(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक status = 0;

	trace_ocfs2_inode_revalidate(inode,
		inode ? (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno : 0ULL,
		inode ? (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_flags : 0);

	अगर (!inode) अणु
		status = -ENOENT;
		जाओ bail;
	पूर्ण

	spin_lock(&OCFS2_I(inode)->ip_lock);
	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_DELETED) अणु
		spin_unlock(&OCFS2_I(inode)->ip_lock);
		status = -ENOENT;
		जाओ bail;
	पूर्ण
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	/* Let ocfs2_inode_lock करो the work of updating our काष्ठा
	 * inode क्रम us. */
	status = ocfs2_inode_lock(inode, शून्य, 0);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	ocfs2_inode_unlock(inode, 0);
bail:
	वापस status;
पूर्ण

/*
 * Updates a disk inode from a
 * काष्ठा inode.
 * Only takes ip_lock.
 */
पूर्णांक ocfs2_mark_inode_dirty(handle_t *handle,
			   काष्ठा inode *inode,
			   काष्ठा buffer_head *bh)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) bh->b_data;

	trace_ocfs2_mark_inode_dirty((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	spin_lock(&OCFS2_I(inode)->ip_lock);
	fe->i_clusters = cpu_to_le32(OCFS2_I(inode)->ip_clusters);
	ocfs2_get_inode_flags(OCFS2_I(inode));
	fe->i_attr = cpu_to_le32(OCFS2_I(inode)->ip_attr);
	fe->i_dyn_features = cpu_to_le16(OCFS2_I(inode)->ip_dyn_features);
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	fe->i_size = cpu_to_le64(i_size_पढ़ो(inode));
	ocfs2_set_links_count(fe, inode->i_nlink);
	fe->i_uid = cpu_to_le32(i_uid_पढ़ो(inode));
	fe->i_gid = cpu_to_le32(i_gid_पढ़ो(inode));
	fe->i_mode = cpu_to_le16(inode->i_mode);
	fe->i_aसमय = cpu_to_le64(inode->i_aसमय.tv_sec);
	fe->i_aसमय_nsec = cpu_to_le32(inode->i_aसमय.tv_nsec);
	fe->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	fe->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	fe->i_mसमय = cpu_to_le64(inode->i_mसमय.tv_sec);
	fe->i_mसमय_nsec = cpu_to_le32(inode->i_mसमय.tv_nsec);

	ocfs2_journal_dirty(handle, bh);
	ocfs2_update_inode_fsync_trans(handle, inode, 1);
leave:
	वापस status;
पूर्ण

/*
 *
 * Updates a काष्ठा inode from a disk inode.
 * करोes no i/o, only takes ip_lock.
 */
व्योम ocfs2_refresh_inode(काष्ठा inode *inode,
			 काष्ठा ocfs2_dinode *fe)
अणु
	spin_lock(&OCFS2_I(inode)->ip_lock);

	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	OCFS2_I(inode)->ip_attr = le32_to_cpu(fe->i_attr);
	OCFS2_I(inode)->ip_dyn_features = le16_to_cpu(fe->i_dyn_features);
	ocfs2_set_inode_flags(inode);
	i_size_ग_लिखो(inode, le64_to_cpu(fe->i_size));
	set_nlink(inode, ocfs2_पढ़ो_links_count(fe));
	i_uid_ग_लिखो(inode, le32_to_cpu(fe->i_uid));
	i_gid_ग_लिखो(inode, le32_to_cpu(fe->i_gid));
	inode->i_mode = le16_to_cpu(fe->i_mode);
	अगर (S_ISLNK(inode->i_mode) && le32_to_cpu(fe->i_clusters) == 0)
		inode->i_blocks = 0;
	अन्यथा
		inode->i_blocks = ocfs2_inode_sector_count(inode);
	inode->i_aसमय.tv_sec = le64_to_cpu(fe->i_aसमय);
	inode->i_aसमय.tv_nsec = le32_to_cpu(fe->i_aसमय_nsec);
	inode->i_mसमय.tv_sec = le64_to_cpu(fe->i_mसमय);
	inode->i_mसमय.tv_nsec = le32_to_cpu(fe->i_mसमय_nsec);
	inode->i_स_समय.tv_sec = le64_to_cpu(fe->i_स_समय);
	inode->i_स_समय.tv_nsec = le32_to_cpu(fe->i_स_समय_nsec);

	spin_unlock(&OCFS2_I(inode)->ip_lock);
पूर्ण

पूर्णांक ocfs2_validate_inode_block(काष्ठा super_block *sb,
			       काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;

	trace_ocfs2_validate_inode_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &di->i_check);
	अगर (rc) अणु
		mlog(ML_ERROR, "Checksum failed for dinode %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		जाओ bail;
	पूर्ण

	/*
	 * Errors after here are fatal.
	 */

	rc = -EINVAL;

	अगर (!OCFS2_IS_VALID_DINODE(di)) अणु
		rc = ocfs2_error(sb, "Invalid dinode #%llu: signature = %.*s\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
				 di->i_signature);
		जाओ bail;
	पूर्ण

	अगर (le64_to_cpu(di->i_blkno) != bh->b_blocknr) अणु
		rc = ocfs2_error(sb, "Invalid dinode #%llu: i_blkno is %llu\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno));
		जाओ bail;
	पूर्ण

	अगर (!(di->i_flags & cpu_to_le32(OCFS2_VALID_FL))) अणु
		rc = ocfs2_error(sb,
				 "Invalid dinode #%llu: OCFS2_VALID_FL not set\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		जाओ bail;
	पूर्ण

	अगर (le32_to_cpu(di->i_fs_generation) !=
	    OCFS2_SB(sb)->fs_generation) अणु
		rc = ocfs2_error(sb,
				 "Invalid dinode #%llu: fs_generation is %u\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 le32_to_cpu(di->i_fs_generation));
		जाओ bail;
	पूर्ण

	rc = 0;

bail:
	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_filecheck_validate_inode_block(काष्ठा super_block *sb,
						काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;

	trace_ocfs2_filecheck_validate_inode_block(
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * Call ocfs2_validate_meta_ecc() first since it has ecc repair
	 * function, but we should not वापस error immediately when ecc
	 * validation fails, because the reason is quite likely the invalid
	 * inode number inputed.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &di->i_check);
	अगर (rc) अणु
		mlog(ML_ERROR,
		     "Filecheck: checksum failed for dinode %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		rc = -OCFS2_खाताCHECK_ERR_BLOCKECC;
	पूर्ण

	अगर (!OCFS2_IS_VALID_DINODE(di)) अणु
		mlog(ML_ERROR,
		     "Filecheck: invalid dinode #%llu: signature = %.*s\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7, di->i_signature);
		rc = -OCFS2_खाताCHECK_ERR_INVALIDINO;
		जाओ bail;
	पूर्ण अन्यथा अगर (rc)
		जाओ bail;

	अगर (le64_to_cpu(di->i_blkno) != bh->b_blocknr) अणु
		mlog(ML_ERROR,
		     "Filecheck: invalid dinode #%llu: i_blkno is %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno));
		rc = -OCFS2_खाताCHECK_ERR_BLOCKNO;
		जाओ bail;
	पूर्ण

	अगर (!(di->i_flags & cpu_to_le32(OCFS2_VALID_FL))) अणु
		mlog(ML_ERROR,
		     "Filecheck: invalid dinode #%llu: OCFS2_VALID_FL "
		     "not set\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		rc = -OCFS2_खाताCHECK_ERR_VALIDFLAG;
		जाओ bail;
	पूर्ण

	अगर (le32_to_cpu(di->i_fs_generation) !=
	    OCFS2_SB(sb)->fs_generation) अणु
		mlog(ML_ERROR,
		     "Filecheck: invalid dinode #%llu: fs_generation is %u\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
		     le32_to_cpu(di->i_fs_generation));
		rc = -OCFS2_खाताCHECK_ERR_GENERATION;
	पूर्ण

bail:
	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_filecheck_repair_inode_block(काष्ठा super_block *sb,
					      काष्ठा buffer_head *bh)
अणु
	पूर्णांक changed = 0;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;

	अगर (!ocfs2_filecheck_validate_inode_block(sb, bh))
		वापस 0;

	trace_ocfs2_filecheck_repair_inode_block(
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	अगर (ocfs2_is_hard_पढ़ोonly(OCFS2_SB(sb)) ||
	    ocfs2_is_soft_पढ़ोonly(OCFS2_SB(sb))) अणु
		mlog(ML_ERROR,
		     "Filecheck: cannot repair dinode #%llu "
		     "on readonly filesystem\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस -OCFS2_खाताCHECK_ERR_READONLY;
	पूर्ण

	अगर (buffer_jbd(bh)) अणु
		mlog(ML_ERROR,
		     "Filecheck: cannot repair dinode #%llu, "
		     "its buffer is in jbd\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस -OCFS2_खाताCHECK_ERR_INJBD;
	पूर्ण

	अगर (!OCFS2_IS_VALID_DINODE(di)) अणु
		/* Cannot fix invalid inode block */
		वापस -OCFS2_खाताCHECK_ERR_INVALIDINO;
	पूर्ण

	अगर (!(di->i_flags & cpu_to_le32(OCFS2_VALID_FL))) अणु
		/* Cannot just add VALID_FL flag back as a fix,
		 * need more things to check here.
		 */
		वापस -OCFS2_खाताCHECK_ERR_VALIDFLAG;
	पूर्ण

	अगर (le64_to_cpu(di->i_blkno) != bh->b_blocknr) अणु
		di->i_blkno = cpu_to_le64(bh->b_blocknr);
		changed = 1;
		mlog(ML_ERROR,
		     "Filecheck: reset dinode #%llu: i_blkno to %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
		     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(di->i_blkno));
	पूर्ण

	अगर (le32_to_cpu(di->i_fs_generation) !=
	    OCFS2_SB(sb)->fs_generation) अणु
		di->i_fs_generation = cpu_to_le32(OCFS2_SB(sb)->fs_generation);
		changed = 1;
		mlog(ML_ERROR,
		     "Filecheck: reset dinode #%llu: fs_generation to %u\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
		     le32_to_cpu(di->i_fs_generation));
	पूर्ण

	अगर (changed || ocfs2_validate_meta_ecc(sb, bh->b_data, &di->i_check)) अणु
		ocfs2_compute_meta_ecc(sb, bh->b_data, &di->i_check);
		mark_buffer_dirty(bh);
		mlog(ML_ERROR,
		     "Filecheck: reset dinode #%llu: compute meta ecc\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ocfs2_filecheck_पढ़ो_inode_block_full(काष्ठा inode *inode,
				      काष्ठा buffer_head **bh,
				      पूर्णांक flags, पूर्णांक type)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	अगर (!type) /* Check inode block */
		rc = ocfs2_पढ़ो_blocks(INODE_CACHE(inode),
				OCFS2_I(inode)->ip_blkno,
				1, &पंचांगp, flags,
				ocfs2_filecheck_validate_inode_block);
	अन्यथा /* Repair inode block */
		rc = ocfs2_पढ़ो_blocks(INODE_CACHE(inode),
				OCFS2_I(inode)->ip_blkno,
				1, &पंचांगp, flags,
				ocfs2_filecheck_repair_inode_block);

	/* If ocfs2_पढ़ो_blocks() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण

पूर्णांक ocfs2_पढ़ो_inode_block_full(काष्ठा inode *inode, काष्ठा buffer_head **bh,
				पूर्णांक flags)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_blocks(INODE_CACHE(inode), OCFS2_I(inode)->ip_blkno,
			       1, &पंचांगp, flags, ocfs2_validate_inode_block);

	/* If ocfs2_पढ़ो_blocks() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण

पूर्णांक ocfs2_पढ़ो_inode_block(काष्ठा inode *inode, काष्ठा buffer_head **bh)
अणु
	वापस ocfs2_पढ़ो_inode_block_full(inode, bh, 0);
पूर्ण


अटल u64 ocfs2_inode_cache_owner(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	वापस oi->ip_blkno;
पूर्ण

अटल काष्ठा super_block *ocfs2_inode_cache_get_super(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	वापस oi->vfs_inode.i_sb;
पूर्ण

अटल व्योम ocfs2_inode_cache_lock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	spin_lock(&oi->ip_lock);
पूर्ण

अटल व्योम ocfs2_inode_cache_unlock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	spin_unlock(&oi->ip_lock);
पूर्ण

अटल व्योम ocfs2_inode_cache_io_lock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	mutex_lock(&oi->ip_io_mutex);
पूर्ण

अटल व्योम ocfs2_inode_cache_io_unlock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_inode_info *oi = cache_info_to_inode(ci);

	mutex_unlock(&oi->ip_io_mutex);
पूर्ण

स्थिर काष्ठा ocfs2_caching_operations ocfs2_inode_caching_ops = अणु
	.co_owner		= ocfs2_inode_cache_owner,
	.co_get_super		= ocfs2_inode_cache_get_super,
	.co_cache_lock		= ocfs2_inode_cache_lock,
	.co_cache_unlock	= ocfs2_inode_cache_unlock,
	.co_io_lock		= ocfs2_inode_cache_io_lock,
	.co_io_unlock		= ocfs2_inode_cache_io_unlock,
पूर्ण;

