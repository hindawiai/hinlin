<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

/*
 * Module: jfs_mount.c
 *
 * note: file प्रणाली in transition to aggregate/fileset:
 *
 * file प्रणाली mount is पूर्णांकerpreted as the mount of aggregate,
 * अगर not alपढ़ोy mounted, and mount of the single/only fileset in
 * the aggregate;
 *
 * a file प्रणाली/aggregate is represented by an पूर्णांकernal inode
 * (aka mount inode) initialized with aggregate superblock;
 * each vfs represents a fileset, and poपूर्णांकs to its "fileset inode
 * allocation map inode" (aka fileset inode):
 * (an aggregate itself is काष्ठाured recursively as a filset:
 * an पूर्णांकernal vfs is स्थिरructed and poपूर्णांकs to its "fileset inode
 * allocation map inode" (aka aggregate inode) where each inode
 * represents a fileset inode) so that inode number is mapped to
 * on-disk inode in unअगरorm way at both aggregate and fileset level;
 *
 * each vnode/inode of a fileset is linked to its vfs (to facilitate
 * per fileset inode operations, e.g., unmount of a fileset, etc.);
 * each inode poपूर्णांकs to the mount inode (to facilitate access to
 * per aggregate inक्रमmation, e.g., block size, etc.) as well as
 * its file set inode.
 *
 *   aggregate
 *   ipmnt
 *   mntvfs -> fileset ipimap+ -> aggregate ipbmap -> aggregate ipaimap;
 *             fileset vfs     -> vp(1) <-> ... <-> vp(n) <->vproot;
 */

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/log2.h>

#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_debug.h"


/*
 * क्रमward references
 */
अटल पूर्णांक chkSuper(काष्ठा super_block *);
अटल पूर्णांक logMOUNT(काष्ठा super_block *sb);

/*
 * NAME:	jfs_mount(sb)
 *
 * FUNCTION:	vfs_mount()
 *
 * PARAMETER:	sb	- super block
 *
 * RETURN:	-EBUSY	- device alपढ़ोy mounted or खोलो क्रम ग_लिखो
 *		-EBUSY	- cvrdvp alपढ़ोy mounted;
 *		-EBUSY	- mount table full
 *		-ENOTसूची- cvrdvp not directory on a device mount
 *		-ENXIO	- device खोलो failure
 */
पूर्णांक jfs_mount(काष्ठा super_block *sb)
अणु
	पूर्णांक rc = 0;		/* Return code */
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा inode *ipaimap = शून्य;
	काष्ठा inode *ipaimap2 = शून्य;
	काष्ठा inode *ipimap = शून्य;
	काष्ठा inode *ipbmap = शून्य;

	/*
	 * पढ़ो/validate superblock
	 * (initialize mount inode from the superblock)
	 */
	अगर ((rc = chkSuper(sb))) अणु
		जाओ errout20;
	पूर्ण

	ipaimap = diReadSpecial(sb, AGGREGATE_I, 0);
	अगर (ipaimap == शून्य) अणु
		jfs_err("jfs_mount: Failed to read AGGREGATE_I");
		rc = -EIO;
		जाओ errout20;
	पूर्ण
	sbi->ipaimap = ipaimap;

	jfs_info("jfs_mount: ipaimap:0x%p", ipaimap);

	/*
	 * initialize aggregate inode allocation map
	 */
	अगर ((rc = diMount(ipaimap))) अणु
		jfs_err("jfs_mount: diMount(ipaimap) failed w/rc = %d", rc);
		जाओ errout21;
	पूर्ण

	/*
	 * खोलो aggregate block allocation map
	 */
	ipbmap = diReadSpecial(sb, BMAP_I, 0);
	अगर (ipbmap == शून्य) अणु
		rc = -EIO;
		जाओ errout22;
	पूर्ण

	jfs_info("jfs_mount: ipbmap:0x%p", ipbmap);

	sbi->ipbmap = ipbmap;

	/*
	 * initialize aggregate block allocation map
	 */
	अगर ((rc = dbMount(ipbmap))) अणु
		jfs_err("jfs_mount: dbMount failed w/rc = %d", rc);
		जाओ errout22;
	पूर्ण

	/*
	 * खोलो the secondary aggregate inode allocation map
	 *
	 * This is a duplicate of the aggregate inode allocation map.
	 *
	 * hand craft a vfs in the same fashion as we did to पढ़ो ipaimap.
	 * By adding INOSPEREXT (32) to the inode number, we are telling
	 * diReadSpecial that we are पढ़ोing from the secondary aggregate
	 * inode table.  This also creates a unique entry in the inode hash
	 * table.
	 */
	अगर ((sbi->mntflag & JFS_BAD_SAIT) == 0) अणु
		ipaimap2 = diReadSpecial(sb, AGGREGATE_I, 1);
		अगर (!ipaimap2) अणु
			jfs_err("jfs_mount: Failed to read AGGREGATE_I");
			rc = -EIO;
			जाओ errout35;
		पूर्ण
		sbi->ipaimap2 = ipaimap2;

		jfs_info("jfs_mount: ipaimap2:0x%p", ipaimap2);

		/*
		 * initialize secondary aggregate inode allocation map
		 */
		अगर ((rc = diMount(ipaimap2))) अणु
			jfs_err("jfs_mount: diMount(ipaimap2) failed, rc = %d",
				rc);
			जाओ errout35;
		पूर्ण
	पूर्ण अन्यथा
		/* Secondary aggregate inode table is not valid */
		sbi->ipaimap2 = शून्य;

	/*
	 *	mount (the only/single) fileset
	 */
	/*
	 * खोलो fileset inode allocation map (aka fileset inode)
	 */
	ipimap = diReadSpecial(sb, खाताSYSTEM_I, 0);
	अगर (ipimap == शून्य) अणु
		jfs_err("jfs_mount: Failed to read FILESYSTEM_I");
		/* खोलो fileset secondary inode allocation map */
		rc = -EIO;
		जाओ errout40;
	पूर्ण
	jfs_info("jfs_mount: ipimap:0x%p", ipimap);

	/* map further access of per fileset inodes by the fileset inode */
	sbi->ipimap = ipimap;

	/* initialize fileset inode allocation map */
	अगर ((rc = diMount(ipimap))) अणु
		jfs_err("jfs_mount: diMount failed w/rc = %d", rc);
		जाओ errout41;
	पूर्ण

	जाओ out;

	/*
	 *	unwind on error
	 */
      errout41:		/* बंद fileset inode allocation map inode */
	diFreeSpecial(ipimap);

      errout40:		/* fileset बंदd */

	/* बंद secondary aggregate inode allocation map */
	अगर (ipaimap2) अणु
		diUnmount(ipaimap2, 1);
		diFreeSpecial(ipaimap2);
	पूर्ण

      errout35:

	/* बंद aggregate block allocation map */
	dbUnmount(ipbmap, 1);
	diFreeSpecial(ipbmap);

      errout22:		/* बंद aggregate inode allocation map */

	diUnmount(ipaimap, 1);

      errout21:		/* बंद aggregate inodes */
	diFreeSpecial(ipaimap);
      errout20:		/* aggregate बंदd */

      out:

	अगर (rc)
		jfs_err("Mount JFS Failure: %d", rc);

	वापस rc;
पूर्ण

/*
 * NAME:	jfs_mount_rw(sb, remount)
 *
 * FUNCTION:	Completes पढ़ो-ग_लिखो mount, or remounts पढ़ो-only volume
 *		as पढ़ो-ग_लिखो
 */
पूर्णांक jfs_mount_rw(काष्ठा super_block *sb, पूर्णांक remount)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	पूर्णांक rc;

	/*
	 * If we are re-mounting a previously पढ़ो-only volume, we want to
	 * re-पढ़ो the inode and block maps, since fsck.jfs may have updated
	 * them.
	 */
	अगर (remount) अणु
		अगर (chkSuper(sb) || (sbi->state != FM_CLEAN))
			वापस -EINVAL;

		truncate_inode_pages(sbi->ipimap->i_mapping, 0);
		truncate_inode_pages(sbi->ipbmap->i_mapping, 0);
		diUnmount(sbi->ipimap, 1);
		अगर ((rc = diMount(sbi->ipimap))) अणु
			jfs_err("jfs_mount_rw: diMount failed!");
			वापस rc;
		पूर्ण

		dbUnmount(sbi->ipbmap, 1);
		अगर ((rc = dbMount(sbi->ipbmap))) अणु
			jfs_err("jfs_mount_rw: dbMount failed!");
			वापस rc;
		पूर्ण
	पूर्ण

	/*
	 * खोलो/initialize log
	 */
	अगर ((rc = lmLogOpen(sb)))
		वापस rc;

	/*
	 * update file प्रणाली superblock;
	 */
	अगर ((rc = updateSuper(sb, FM_MOUNT))) अणु
		jfs_err("jfs_mount: updateSuper failed w/rc = %d", rc);
		lmLogClose(sb);
		वापस rc;
	पूर्ण

	/*
	 * ग_लिखो MOUNT log record of the file प्रणाली
	 */
	logMOUNT(sb);

	वापस rc;
पूर्ण

/*
 *	chkSuper()
 *
 * validate the superblock of the file प्रणाली to be mounted and
 * get the file प्रणाली parameters.
 *
 * वापसs
 *	0 with fragsize set अगर check successful
 *	error code अगर not successful
 */
अटल पूर्णांक chkSuper(काष्ठा super_block *sb)
अणु
	पूर्णांक rc = 0;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_superblock *j_sb;
	काष्ठा buffer_head *bh;
	पूर्णांक AIM_bytesize, AIT_bytesize;
	पूर्णांक expected_AIM_bytesize, expected_AIT_bytesize;
	s64 AIM_byte_addr, AIT_byte_addr, fsckwsp_addr;
	s64 byte_addr_dअगरf0, byte_addr_dअगरf1;
	s32 bsize;

	अगर ((rc = पढ़ोSuper(sb, &bh)))
		वापस rc;
	j_sb = (काष्ठा jfs_superblock *)bh->b_data;

	/*
	 * validate superblock
	 */
	/* validate fs signature */
	अगर (म_भेदन(j_sb->s_magic, JFS_MAGIC, 4) ||
	    le32_to_cpu(j_sb->s_version) > JFS_VERSION) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	bsize = le32_to_cpu(j_sb->s_bsize);
#अगर_घोषित _JFS_4K
	अगर (bsize != PSIZE) अणु
		jfs_err("Currently only 4K block size supported!");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
#पूर्ण_अगर				/* _JFS_4K */

	jfs_info("superblock: flag:0x%08x state:0x%08x size:0x%Lx",
		 le32_to_cpu(j_sb->s_flag), le32_to_cpu(j_sb->s_state),
		 (अचिन्हित दीर्घ दीर्घ) le64_to_cpu(j_sb->s_size));

	/* validate the descriptors क्रम Secondary AIM and AIT */
	अगर ((j_sb->s_flag & cpu_to_le32(JFS_BAD_SAIT)) !=
	    cpu_to_le32(JFS_BAD_SAIT)) अणु
		expected_AIM_bytesize = 2 * PSIZE;
		AIM_bytesize = lengthPXD(&(j_sb->s_aim2)) * bsize;
		expected_AIT_bytesize = 4 * PSIZE;
		AIT_bytesize = lengthPXD(&(j_sb->s_ait2)) * bsize;
		AIM_byte_addr = addressPXD(&(j_sb->s_aim2)) * bsize;
		AIT_byte_addr = addressPXD(&(j_sb->s_ait2)) * bsize;
		byte_addr_dअगरf0 = AIT_byte_addr - AIM_byte_addr;
		fsckwsp_addr = addressPXD(&(j_sb->s_fsckpxd)) * bsize;
		byte_addr_dअगरf1 = fsckwsp_addr - AIT_byte_addr;
		अगर ((AIM_bytesize != expected_AIM_bytesize) ||
		    (AIT_bytesize != expected_AIT_bytesize) ||
		    (byte_addr_dअगरf0 != AIM_bytesize) ||
		    (byte_addr_dअगरf1 <= AIT_bytesize))
			j_sb->s_flag |= cpu_to_le32(JFS_BAD_SAIT);
	पूर्ण

	अगर ((j_sb->s_flag & cpu_to_le32(JFS_GROUPCOMMIT)) !=
	    cpu_to_le32(JFS_GROUPCOMMIT))
		j_sb->s_flag |= cpu_to_le32(JFS_GROUPCOMMIT);

	/* validate fs state */
	अगर (j_sb->s_state != cpu_to_le32(FM_CLEAN) &&
	    !sb_rकरोnly(sb)) अणु
		jfs_err("jfs_mount: Mount Failure: File System Dirty.");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	sbi->state = le32_to_cpu(j_sb->s_state);
	sbi->mntflag = le32_to_cpu(j_sb->s_flag);

	/*
	 * JFS always करोes I/O by 4K pages.  Don't tell the buffer cache
	 * that we use anything अन्यथा (leave s_blocksize alone).
	 */
	sbi->bsize = bsize;
	sbi->l2bsize = le16_to_cpu(j_sb->s_l2bsize);

	/* check some fields क्रम possible corruption */
	अगर (sbi->l2bsize != ilog2((u32)bsize) ||
	    j_sb->pad != 0 ||
	    le32_to_cpu(j_sb->s_state) > FM_STATE_MAX) अणु
		rc = -EINVAL;
		jfs_err("jfs_mount: Mount Failure: superblock is corrupt!");
		जाओ out;
	पूर्ण

	/*
	 * For now, ignore s_pbsize, l2bfactor.  All I/O going through buffer
	 * cache.
	 */
	sbi->nbperpage = PSIZE >> sbi->l2bsize;
	sbi->l2nbperpage = L2PSIZE - sbi->l2bsize;
	sbi->l2niperblk = sbi->l2bsize - L2DISIZE;
	अगर (sbi->mntflag & JFS_INLINELOG)
		sbi->logpxd = j_sb->s_logpxd;
	अन्यथा अणु
		sbi->logdev = new_decode_dev(le32_to_cpu(j_sb->s_logdev));
		uuid_copy(&sbi->uuid, &j_sb->s_uuid);
		uuid_copy(&sbi->loguuid, &j_sb->s_loguuid);
	पूर्ण
	sbi->fsckpxd = j_sb->s_fsckpxd;
	sbi->ait2 = j_sb->s_ait2;

      out:
	brअन्यथा(bh);
	वापस rc;
पूर्ण


/*
 *	updateSuper()
 *
 * update synchronously superblock अगर it is mounted पढ़ो-ग_लिखो.
 */
पूर्णांक updateSuper(काष्ठा super_block *sb, uपूर्णांक state)
अणु
	काष्ठा jfs_superblock *j_sb;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा buffer_head *bh;
	पूर्णांक rc;

	अगर (sbi->flag & JFS_NOINTEGRITY) अणु
		अगर (state == FM_सूचीTY) अणु
			sbi->p_state = state;
			वापस 0;
		पूर्ण अन्यथा अगर (state == FM_MOUNT) अणु
			sbi->p_state = sbi->state;
			state = FM_सूचीTY;
		पूर्ण अन्यथा अगर (state == FM_CLEAN) अणु
			state = sbi->p_state;
		पूर्ण अन्यथा
			jfs_err("updateSuper: bad state");
	पूर्ण अन्यथा अगर (sbi->state == FM_सूचीTY)
		वापस 0;

	अगर ((rc = पढ़ोSuper(sb, &bh)))
		वापस rc;

	j_sb = (काष्ठा jfs_superblock *)bh->b_data;

	j_sb->s_state = cpu_to_le32(state);
	sbi->state = state;

	अगर (state == FM_MOUNT) अणु
		/* record log's dev_t and mount serial number */
		j_sb->s_logdev = cpu_to_le32(new_encode_dev(sbi->log->bdev->bd_dev));
		j_sb->s_logserial = cpu_to_le32(sbi->log->serial);
	पूर्ण अन्यथा अगर (state == FM_CLEAN) अणु
		/*
		 * If this volume is shared with OS/2, OS/2 will need to
		 * recalculate DASD usage, since we करोn't deal with it.
		 */
		अगर (j_sb->s_flag & cpu_to_le32(JFS_DASD_ENABLED))
			j_sb->s_flag |= cpu_to_le32(JFS_DASD_PRIME);
	पूर्ण

	mark_buffer_dirty(bh);
	sync_dirty_buffer(bh);
	brअन्यथा(bh);

	वापस 0;
पूर्ण


/*
 *	पढ़ोSuper()
 *
 * पढ़ो superblock by raw sector address
 */
पूर्णांक पढ़ोSuper(काष्ठा super_block *sb, काष्ठा buffer_head **bpp)
अणु
	/* पढ़ो in primary superblock */
	*bpp = sb_bपढ़ो(sb, SUPER1_OFF >> sb->s_blocksize_bits);
	अगर (*bpp)
		वापस 0;

	/* पढ़ो in secondary/replicated superblock */
	*bpp = sb_bपढ़ो(sb, SUPER2_OFF >> sb->s_blocksize_bits);
	अगर (*bpp)
		वापस 0;

	वापस -EIO;
पूर्ण


/*
 *	logMOUNT()
 *
 * function: ग_लिखो a MOUNT log record क्रम file प्रणाली.
 *
 * MOUNT record keeps logreकरो() from processing log records
 * क्रम this file प्रणाली past this poपूर्णांक in log.
 * it is harmless अगर mount fails.
 *
 * note: MOUNT record is at aggregate level, not at fileset level,
 * since log records of previous mounts of a fileset
 * (e.g., AFTER record of extent allocation) have to be processed
 * to update block allocation map at aggregate level.
 */
अटल पूर्णांक logMOUNT(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_log *log = JFS_SBI(sb)->log;
	काष्ठा lrd lrd;

	lrd.logtid = 0;
	lrd.backchain = 0;
	lrd.type = cpu_to_le16(LOG_MOUNT);
	lrd.length = 0;
	lrd.aggregate = cpu_to_le32(new_encode_dev(sb->s_bdev->bd_dev));
	lmLog(log, शून्य, &lrd, शून्य);

	वापस 0;
पूर्ण
