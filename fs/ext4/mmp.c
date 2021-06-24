<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/utsname.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "ext4.h"

/* Checksumming functions */
अटल __le32 ext4_mmp_csum(काष्ठा super_block *sb, काष्ठा mmp_काष्ठा *mmp)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक offset = दुरत्व(काष्ठा mmp_काष्ठा, mmp_checksum);
	__u32 csum;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (अक्षर *)mmp, offset);

	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक ext4_mmp_csum_verअगरy(काष्ठा super_block *sb, काष्ठा mmp_काष्ठा *mmp)
अणु
	अगर (!ext4_has_metadata_csum(sb))
		वापस 1;

	वापस mmp->mmp_checksum == ext4_mmp_csum(sb, mmp);
पूर्ण

अटल व्योम ext4_mmp_csum_set(काष्ठा super_block *sb, काष्ठा mmp_काष्ठा *mmp)
अणु
	अगर (!ext4_has_metadata_csum(sb))
		वापस;

	mmp->mmp_checksum = ext4_mmp_csum(sb, mmp);
पूर्ण

/*
 * Write the MMP block using REQ_SYNC to try to get the block on-disk
 * faster.
 */
अटल पूर्णांक ग_लिखो_mmp_block(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	काष्ठा mmp_काष्ठा *mmp = (काष्ठा mmp_काष्ठा *)(bh->b_data);

	/*
	 * We protect against मुक्तzing so that we करोn't create dirty buffers
	 * on frozen fileप्रणाली.
	 */
	sb_start_ग_लिखो(sb);
	ext4_mmp_csum_set(sb, mmp);
	lock_buffer(bh);
	bh->b_end_io = end_buffer_ग_लिखो_sync;
	get_bh(bh);
	submit_bh(REQ_OP_WRITE, REQ_SYNC | REQ_META | REQ_PRIO, bh);
	रुको_on_buffer(bh);
	sb_end_ग_लिखो(sb);
	अगर (unlikely(!buffer_uptodate(bh)))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Read the MMP block. It _must_ be पढ़ो from disk and hence we clear the
 * uptodate flag on the buffer.
 */
अटल पूर्णांक पढ़ो_mmp_block(काष्ठा super_block *sb, काष्ठा buffer_head **bh,
			  ext4_fsblk_t mmp_block)
अणु
	काष्ठा mmp_काष्ठा *mmp;
	पूर्णांक ret;

	अगर (*bh)
		clear_buffer_uptodate(*bh);

	/* This would be sb_bपढ़ो(sb, mmp_block), except we need to be sure
	 * that the MD RAID device cache has been bypassed, and that the पढ़ो
	 * is not blocked in the elevator. */
	अगर (!*bh) अणु
		*bh = sb_getblk(sb, mmp_block);
		अगर (!*bh) अणु
			ret = -ENOMEM;
			जाओ warn_निकास;
		पूर्ण
	पूर्ण

	lock_buffer(*bh);
	ret = ext4_पढ़ो_bh(*bh, REQ_META | REQ_PRIO, शून्य);
	अगर (ret)
		जाओ warn_निकास;

	mmp = (काष्ठा mmp_काष्ठा *)((*bh)->b_data);
	अगर (le32_to_cpu(mmp->mmp_magic) != EXT4_MMP_MAGIC) अणु
		ret = -EFSCORRUPTED;
		जाओ warn_निकास;
	पूर्ण
	अगर (!ext4_mmp_csum_verअगरy(sb, mmp)) अणु
		ret = -EFSBADCRC;
		जाओ warn_निकास;
	पूर्ण
	वापस 0;
warn_निकास:
	brअन्यथा(*bh);
	*bh = शून्य;
	ext4_warning(sb, "Error %d while reading MMP block %llu",
		     ret, mmp_block);
	वापस ret;
पूर्ण

/*
 * Dump as much inक्रमmation as possible to help the admin.
 */
व्योम __dump_mmp_msg(काष्ठा super_block *sb, काष्ठा mmp_काष्ठा *mmp,
		    स्थिर अक्षर *function, अचिन्हित पूर्णांक line, स्थिर अक्षर *msg)
अणु
	__ext4_warning(sb, function, line, "%s", msg);
	__ext4_warning(sb, function, line,
		       "MMP failure info: last update time: %llu, last update node: %.*s, last update device: %.*s",
		       (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(mmp->mmp_समय),
		       (पूर्णांक)माप(mmp->mmp_nodename), mmp->mmp_nodename,
		       (पूर्णांक)माप(mmp->mmp_bdevname), mmp->mmp_bdevname);
पूर्ण

/*
 * kmmpd will update the MMP sequence every s_mmp_update_पूर्णांकerval seconds
 */
अटल पूर्णांक kmmpd(व्योम *data)
अणु
	काष्ठा super_block *sb = ((काष्ठा mmpd_data *) data)->sb;
	काष्ठा buffer_head *bh = ((काष्ठा mmpd_data *) data)->bh;
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;
	काष्ठा mmp_काष्ठा *mmp;
	ext4_fsblk_t mmp_block;
	u32 seq = 0;
	अचिन्हित दीर्घ failed_ग_लिखोs = 0;
	पूर्णांक mmp_update_पूर्णांकerval = le16_to_cpu(es->s_mmp_update_पूर्णांकerval);
	अचिन्हित mmp_check_पूर्णांकerval;
	अचिन्हित दीर्घ last_update_समय;
	अचिन्हित दीर्घ dअगरf;
	पूर्णांक retval;

	mmp_block = le64_to_cpu(es->s_mmp_block);
	mmp = (काष्ठा mmp_काष्ठा *)(bh->b_data);
	mmp->mmp_समय = cpu_to_le64(kसमय_get_real_seconds());
	/*
	 * Start with the higher mmp_check_पूर्णांकerval and reduce it अगर
	 * the MMP block is being updated on समय.
	 */
	mmp_check_पूर्णांकerval = max(EXT4_MMP_CHECK_MULT * mmp_update_पूर्णांकerval,
				 EXT4_MMP_MIN_CHECK_INTERVAL);
	mmp->mmp_check_पूर्णांकerval = cpu_to_le16(mmp_check_पूर्णांकerval);
	BUILD_BUG_ON(माप(mmp->mmp_bdevname) < BDEVNAME_SIZE);
	bdevname(bh->b_bdev, mmp->mmp_bdevname);

	स_नकल(mmp->mmp_nodename, init_utsname()->nodename,
	       माप(mmp->mmp_nodename));

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (++seq > EXT4_MMP_SEQ_MAX)
			seq = 1;

		mmp->mmp_seq = cpu_to_le32(seq);
		mmp->mmp_समय = cpu_to_le64(kसमय_get_real_seconds());
		last_update_समय = jअगरfies;

		retval = ग_लिखो_mmp_block(sb, bh);
		/*
		 * Don't spew too many error messages. Prपूर्णांक one every
		 * (s_mmp_update_पूर्णांकerval * 60) seconds.
		 */
		अगर (retval) अणु
			अगर ((failed_ग_लिखोs % 60) == 0) अणु
				ext4_error_err(sb, -retval,
					       "Error writing to MMP block");
			पूर्ण
			failed_ग_लिखोs++;
		पूर्ण

		अगर (!(le32_to_cpu(es->s_feature_incompat) &
		    EXT4_FEATURE_INCOMPAT_MMP)) अणु
			ext4_warning(sb, "kmmpd being stopped since MMP feature"
				     " has been disabled.");
			जाओ निकास_thपढ़ो;
		पूर्ण

		अगर (sb_rकरोnly(sb))
			अवरोध;

		dअगरf = jअगरfies - last_update_समय;
		अगर (dअगरf < mmp_update_पूर्णांकerval * HZ)
			schedule_समयout_पूर्णांकerruptible(mmp_update_पूर्णांकerval *
						       HZ - dअगरf);

		/*
		 * We need to make sure that more than mmp_check_पूर्णांकerval
		 * seconds have not passed since writing. If that has happened
		 * we need to check अगर the MMP block is as we left it.
		 */
		dअगरf = jअगरfies - last_update_समय;
		अगर (dअगरf > mmp_check_पूर्णांकerval * HZ) अणु
			काष्ठा buffer_head *bh_check = शून्य;
			काष्ठा mmp_काष्ठा *mmp_check;

			retval = पढ़ो_mmp_block(sb, &bh_check, mmp_block);
			अगर (retval) अणु
				ext4_error_err(sb, -retval,
					       "error reading MMP data: %d",
					       retval);
				जाओ निकास_thपढ़ो;
			पूर्ण

			mmp_check = (काष्ठा mmp_काष्ठा *)(bh_check->b_data);
			अगर (mmp->mmp_seq != mmp_check->mmp_seq ||
			    स_भेद(mmp->mmp_nodename, mmp_check->mmp_nodename,
				   माप(mmp->mmp_nodename))) अणु
				dump_mmp_msg(sb, mmp_check,
					     "Error while updating MMP info. "
					     "The filesystem seems to have been"
					     " multiply mounted.");
				ext4_error_err(sb, EBUSY, "abort");
				put_bh(bh_check);
				retval = -EBUSY;
				जाओ निकास_thपढ़ो;
			पूर्ण
			put_bh(bh_check);
		पूर्ण

		 /*
		 * Adjust the mmp_check_पूर्णांकerval depending on how much समय
		 * it took क्रम the MMP block to be written.
		 */
		mmp_check_पूर्णांकerval = max(min(EXT4_MMP_CHECK_MULT * dअगरf / HZ,
					     EXT4_MMP_MAX_CHECK_INTERVAL),
					 EXT4_MMP_MIN_CHECK_INTERVAL);
		mmp->mmp_check_पूर्णांकerval = cpu_to_le16(mmp_check_पूर्णांकerval);
	पूर्ण

	/*
	 * Unmount seems to be clean.
	 */
	mmp->mmp_seq = cpu_to_le32(EXT4_MMP_SEQ_CLEAN);
	mmp->mmp_समय = cpu_to_le64(kसमय_get_real_seconds());

	retval = ग_लिखो_mmp_block(sb, bh);

निकास_thपढ़ो:
	EXT4_SB(sb)->s_mmp_tsk = शून्य;
	kमुक्त(data);
	brअन्यथा(bh);
	वापस retval;
पूर्ण

/*
 * Get a अक्रमom new sequence number but make sure it is not greater than
 * EXT4_MMP_SEQ_MAX.
 */
अटल अचिन्हित पूर्णांक mmp_new_seq(व्योम)
अणु
	u32 new_seq;

	करो अणु
		new_seq = pअक्रमom_u32();
	पूर्ण जबतक (new_seq > EXT4_MMP_SEQ_MAX);

	वापस new_seq;
पूर्ण

/*
 * Protect the fileप्रणाली from being mounted more than once.
 */
पूर्णांक ext4_multi_mount_protect(काष्ठा super_block *sb,
				    ext4_fsblk_t mmp_block)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा mmp_काष्ठा *mmp = शून्य;
	काष्ठा mmpd_data *mmpd_data;
	u32 seq;
	अचिन्हित पूर्णांक mmp_check_पूर्णांकerval = le16_to_cpu(es->s_mmp_update_पूर्णांकerval);
	अचिन्हित पूर्णांक रुको_समय = 0;
	पूर्णांक retval;

	अगर (mmp_block < le32_to_cpu(es->s_first_data_block) ||
	    mmp_block >= ext4_blocks_count(es)) अणु
		ext4_warning(sb, "Invalid MMP block in superblock");
		जाओ failed;
	पूर्ण

	retval = पढ़ो_mmp_block(sb, &bh, mmp_block);
	अगर (retval)
		जाओ failed;

	mmp = (काष्ठा mmp_काष्ठा *)(bh->b_data);

	अगर (mmp_check_पूर्णांकerval < EXT4_MMP_MIN_CHECK_INTERVAL)
		mmp_check_पूर्णांकerval = EXT4_MMP_MIN_CHECK_INTERVAL;

	/*
	 * If check_पूर्णांकerval in MMP block is larger, use that instead of
	 * update_पूर्णांकerval from the superblock.
	 */
	अगर (le16_to_cpu(mmp->mmp_check_पूर्णांकerval) > mmp_check_पूर्णांकerval)
		mmp_check_पूर्णांकerval = le16_to_cpu(mmp->mmp_check_पूर्णांकerval);

	seq = le32_to_cpu(mmp->mmp_seq);
	अगर (seq == EXT4_MMP_SEQ_CLEAN)
		जाओ skip;

	अगर (seq == EXT4_MMP_SEQ_FSCK) अणु
		dump_mmp_msg(sb, mmp, "fsck is running on the filesystem");
		जाओ failed;
	पूर्ण

	रुको_समय = min(mmp_check_पूर्णांकerval * 2 + 1,
			mmp_check_पूर्णांकerval + 60);

	/* Prपूर्णांक MMP पूर्णांकerval अगर more than 20 secs. */
	अगर (रुको_समय > EXT4_MMP_MIN_CHECK_INTERVAL * 4)
		ext4_warning(sb, "MMP interval %u higher than expected, please"
			     " wait.\n", रुको_समय * 2);

	अगर (schedule_समयout_पूर्णांकerruptible(HZ * रुको_समय) != 0) अणु
		ext4_warning(sb, "MMP startup interrupted, failing mount\n");
		जाओ failed;
	पूर्ण

	retval = पढ़ो_mmp_block(sb, &bh, mmp_block);
	अगर (retval)
		जाओ failed;
	mmp = (काष्ठा mmp_काष्ठा *)(bh->b_data);
	अगर (seq != le32_to_cpu(mmp->mmp_seq)) अणु
		dump_mmp_msg(sb, mmp,
			     "Device is already active on another node.");
		जाओ failed;
	पूर्ण

skip:
	/*
	 * ग_लिखो a new अक्रमom sequence number.
	 */
	seq = mmp_new_seq();
	mmp->mmp_seq = cpu_to_le32(seq);

	retval = ग_लिखो_mmp_block(sb, bh);
	अगर (retval)
		जाओ failed;

	/*
	 * रुको क्रम MMP पूर्णांकerval and check mmp_seq.
	 */
	अगर (schedule_समयout_पूर्णांकerruptible(HZ * रुको_समय) != 0) अणु
		ext4_warning(sb, "MMP startup interrupted, failing mount");
		जाओ failed;
	पूर्ण

	retval = पढ़ो_mmp_block(sb, &bh, mmp_block);
	अगर (retval)
		जाओ failed;
	mmp = (काष्ठा mmp_काष्ठा *)(bh->b_data);
	अगर (seq != le32_to_cpu(mmp->mmp_seq)) अणु
		dump_mmp_msg(sb, mmp,
			     "Device is already active on another node.");
		जाओ failed;
	पूर्ण

	mmpd_data = kदो_स्मृति(माप(*mmpd_data), GFP_KERNEL);
	अगर (!mmpd_data) अणु
		ext4_warning(sb, "not enough memory for mmpd_data");
		जाओ failed;
	पूर्ण
	mmpd_data->sb = sb;
	mmpd_data->bh = bh;

	/*
	 * Start a kernel thपढ़ो to update the MMP block periodically.
	 */
	EXT4_SB(sb)->s_mmp_tsk = kthपढ़ो_run(kmmpd, mmpd_data, "kmmpd-%.*s",
					     (पूर्णांक)माप(mmp->mmp_bdevname),
					     bdevname(bh->b_bdev,
						      mmp->mmp_bdevname));
	अगर (IS_ERR(EXT4_SB(sb)->s_mmp_tsk)) अणु
		EXT4_SB(sb)->s_mmp_tsk = शून्य;
		kमुक्त(mmpd_data);
		ext4_warning(sb, "Unable to create kmmpd thread for %s.",
			     sb->s_id);
		जाओ failed;
	पूर्ण

	वापस 0;

failed:
	brअन्यथा(bh);
	वापस 1;
पूर्ण


