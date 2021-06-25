<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines  Corp., 2000-2004
*/

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/blkdev.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_txnmgr.h"
#समावेश "jfs_debug.h"

#घोषणा BITSPERPAGE	(PSIZE << 3)
#घोषणा L2MEGABYTE	20
#घोषणा MEGABYTE	(1 << L2MEGABYTE)
#घोषणा MEGABYTE32	(MEGABYTE << 5)

/* convert block number to bmap file page number */
#घोषणा BLKTODMAPN(b)\
	(((b) >> 13) + ((b) >> 23) + ((b) >> 33) + 3 + 1)

/*
 *	jfs_extendfs()
 *
 * function: extend file प्रणाली;
 *
 *   |-------------------------------|----------|----------|
 *   file प्रणाली space               fsck       अंतरभूत log
 *                                   workspace  space
 *
 * input:
 *	new LVSize: in LV blocks (required)
 *	new LogSize: in LV blocks (optional)
 *	new FSSize: in LV blocks (optional)
 *
 * new configuration:
 * 1. set new LogSize as specअगरied or शेष from new LVSize;
 * 2. compute new FSCKSize from new LVSize;
 * 3. set new FSSize as MIN(FSSize, LVSize-(LogSize+FSCKSize)) where
 *    निश्चित(new FSSize >= old FSSize),
 *    i.e., file प्रणाली must not be shrunk;
 */
पूर्णांक jfs_extendfs(काष्ठा super_block *sb, s64 newLVSize, पूर्णांक newLogSize)
अणु
	पूर्णांक rc = 0;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा inode *ipbmap = sbi->ipbmap;
	काष्ठा inode *ipbmap2;
	काष्ठा inode *ipimap = sbi->ipimap;
	काष्ठा jfs_log *log = sbi->log;
	काष्ठा bmap *bmp = sbi->bmap;
	s64 newLogAddress, newFSCKAddress;
	पूर्णांक newFSCKSize;
	s64 newMapSize = 0, mapSize;
	s64 XAddress, XSize, nblocks, xoff, xaddr, t64;
	s64 oldLVSize;
	s64 newFSSize;
	s64 VolumeSize;
	पूर्णांक newNpages = 0, nPages, newPage, xlen, t32;
	पूर्णांक tid;
	पूर्णांक log_क्रमmatted = 0;
	काष्ठा inode *iplist[1];
	काष्ठा jfs_superblock *j_sb, *j_sb2;
	s64 old_agsize;
	पूर्णांक agsizechanged = 0;
	काष्ठा buffer_head *bh, *bh2;

	/* If the volume hasn't grown, get out now */

	अगर (sbi->mntflag & JFS_INLINELOG)
		oldLVSize = addressPXD(&sbi->logpxd) + lengthPXD(&sbi->logpxd);
	अन्यथा
		oldLVSize = addressPXD(&sbi->fsckpxd) +
		    lengthPXD(&sbi->fsckpxd);

	अगर (oldLVSize >= newLVSize) अणु
		prपूर्णांकk(KERN_WARNING
		       "jfs_extendfs: volume hasn't grown, returning\n");
		जाओ out;
	पूर्ण

	VolumeSize = i_size_पढ़ो(sb->s_bdev->bd_inode) >> sb->s_blocksize_bits;

	अगर (VolumeSize) अणु
		अगर (newLVSize > VolumeSize) अणु
			prपूर्णांकk(KERN_WARNING "jfs_extendfs: invalid size\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check the device */
		bh = sb_bपढ़ो(sb, newLVSize - 1);
		अगर (!bh) अणु
			prपूर्णांकk(KERN_WARNING "jfs_extendfs: invalid size\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		bक्रमget(bh);
	पूर्ण

	/* Can't extend ग_लिखो-रक्षित drive */

	अगर (isReadOnly(ipbmap)) अणु
		prपूर्णांकk(KERN_WARNING "jfs_extendfs: read-only file system\n");
		rc = -EROFS;
		जाओ out;
	पूर्ण

	/*
	 *	reconfigure LV spaces
	 *	---------------------
	 *
	 * validate new size, or, अगर not specअगरied, determine new size
	 */

	/*
	 * reconfigure अंतरभूत log space:
	 */
	अगर ((sbi->mntflag & JFS_INLINELOG)) अणु
		अगर (newLogSize == 0) अणु
			/*
			 * no size specअगरied: शेष to 1/256 of aggregate
			 * size; rounded up to a megabyte boundary;
			 */
			newLogSize = newLVSize >> 8;
			t32 = (1 << (20 - sbi->l2bsize)) - 1;
			newLogSize = (newLogSize + t32) & ~t32;
			newLogSize =
			    min(newLogSize, MEGABYTE32 >> sbi->l2bsize);
		पूर्ण अन्यथा अणु
			/*
			 * convert the newLogSize to fs blocks.
			 *
			 * Since this is given in megabytes, it will always be
			 * an even number of pages.
			 */
			newLogSize = (newLogSize * MEGABYTE) >> sbi->l2bsize;
		पूर्ण

	पूर्ण अन्यथा
		newLogSize = 0;

	newLogAddress = newLVSize - newLogSize;

	/*
	 * reconfigure fsck work space:
	 *
	 * configure it to the end of the logical volume regardless of
	 * whether file प्रणाली extends to the end of the aggregate;
	 * Need enough 4k pages to cover:
	 *  - 1 bit per block in aggregate rounded up to BPERDMAP boundary
	 *  - 1 extra page to handle control page and पूर्णांकermediate level pages
	 *  - 50 extra pages क्रम the chkdsk service log
	 */
	t64 = ((newLVSize - newLogSize + BPERDMAP - 1) >> L2BPERDMAP)
	    << L2BPERDMAP;
	t32 = DIV_ROUND_UP(t64, BITSPERPAGE) + 1 + 50;
	newFSCKSize = t32 << sbi->l2nbperpage;
	newFSCKAddress = newLogAddress - newFSCKSize;

	/*
	 * compute new file प्रणाली space;
	 */
	newFSSize = newLVSize - newLogSize - newFSCKSize;

	/* file प्रणाली cannot be shrunk */
	अगर (newFSSize < bmp->db_mapsize) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * If we're expanding enough that the अंतरभूत log करोes not overlap
	 * the old one, we can क्रमmat the new log beक्रमe we quiesce the
	 * fileप्रणाली.
	 */
	अगर ((sbi->mntflag & JFS_INLINELOG) && (newLogAddress > oldLVSize)) अणु
		अगर ((rc = lmLogFormat(log, newLogAddress, newLogSize)))
			जाओ out;
		log_क्रमmatted = 1;
	पूर्ण
	/*
	 *	quiesce file प्रणाली
	 *
	 * (prepare to move the अंतरभूत log and to prevent map update)
	 *
	 * block any new transactions and रुको क्रम completion of
	 * all wip transactions and flush modअगरied pages s.t.
	 * on-disk file प्रणाली is in consistent state and
	 * log is not required क्रम recovery.
	 */
	txQuiesce(sb);

	/* Reset size of direct inode */
	sbi->direct_inode->i_size =  i_size_पढ़ो(sb->s_bdev->bd_inode);

	अगर (sbi->mntflag & JFS_INLINELOG) अणु
		/*
		 * deactivate old अंतरभूत log
		 */
		lmLogShutकरोwn(log);

		/*
		 * mark on-disk super block क्रम fs in transition;
		 *
		 * update on-disk superblock क्रम the new space configuration
		 * of अंतरभूत log space and fsck work space descriptors:
		 * N.B. FS descriptor is NOT updated;
		 *
		 * crash recovery:
		 * logreकरो(): अगर FM_EXTENDFS, वापस to fsck() क्रम cleanup;
		 * fsck(): अगर FM_EXTENDFS, reक्रमmat अंतरभूत log and fsck
		 * workspace from superblock अंतरभूत log descriptor and fsck
		 * workspace descriptor;
		 */

		/* पढ़ो in superblock */
		अगर ((rc = पढ़ोSuper(sb, &bh)))
			जाओ error_out;
		j_sb = (काष्ठा jfs_superblock *)bh->b_data;

		/* mark extendfs() in progress */
		j_sb->s_state |= cpu_to_le32(FM_EXTENDFS);
		j_sb->s_xsize = cpu_to_le64(newFSSize);
		PXDaddress(&j_sb->s_xfsckpxd, newFSCKAddress);
		PXDlength(&j_sb->s_xfsckpxd, newFSCKSize);
		PXDaddress(&j_sb->s_xlogpxd, newLogAddress);
		PXDlength(&j_sb->s_xlogpxd, newLogSize);

		/* synchronously update superblock */
		mark_buffer_dirty(bh);
		sync_dirty_buffer(bh);
		brअन्यथा(bh);

		/*
		 * क्रमmat new अंतरभूत log synchronously;
		 *
		 * crash recovery: अगर log move in progress,
		 * reक्रमmat log and निकास success;
		 */
		अगर (!log_क्रमmatted)
			अगर ((rc = lmLogFormat(log, newLogAddress, newLogSize)))
				जाओ error_out;

		/*
		 * activate new log
		 */
		log->base = newLogAddress;
		log->size = newLogSize >> (L2LOGPSIZE - sb->s_blocksize_bits);
		अगर ((rc = lmLogInit(log)))
			जाओ error_out;
	पूर्ण

	/*
	 *	extend block allocation map
	 *	---------------------------
	 *
	 * extendfs() क्रम new extension, retry after crash recovery;
	 *
	 * note: both logreकरो() and fsck() rebuild map from
	 * the biपंचांगap and configuration parameter from superblock
	 * (disregarding all other control inक्रमmation in the map);
	 *
	 * superblock:
	 *  s_size: aggregate size in physical blocks;
	 */
	/*
	 *	compute the new block allocation map configuration
	 *
	 * map dinode:
	 *  di_size: map file size in byte;
	 *  di_nblocks: number of blocks allocated क्रम map file;
	 *  di_mapsize: number of blocks in aggregate (covered by map);
	 * map control page:
	 *  db_mapsize: number of blocks in aggregate (covered by map);
	 */
	newMapSize = newFSSize;
	/* number of data pages of new bmap file:
	 * roundup new size to full dmap page boundary and
	 * add 1 extra dmap page क्रम next extendfs()
	 */
	t64 = (newMapSize - 1) + BPERDMAP;
	newNpages = BLKTODMAPN(t64) + 1;

	/*
	 *	extend map from current map (WITHOUT growing mapfile)
	 *
	 * map new extension with unmapped part of the last partial
	 * dmap page, अगर applicable, and extra page(s) allocated
	 * at end of bmap by mkfs() or previous extendfs();
	 */
      extendBmap:
	/* compute number of blocks requested to extend */
	mapSize = bmp->db_mapsize;
	XAddress = mapSize;	/* eXtension Address */
	XSize = newMapSize - mapSize;	/* eXtension Size */
	old_agsize = bmp->db_agsize;	/* We need to know अगर this changes */

	/* compute number of blocks that can be extended by current mapfile */
	t64 = dbMapFileSizeToMapSize(ipbmap);
	अगर (mapSize > t64) अणु
		prपूर्णांकk(KERN_ERR "jfs_extendfs: mapSize (0x%Lx) > t64 (0x%Lx)\n",
		       (दीर्घ दीर्घ) mapSize, (दीर्घ दीर्घ) t64);
		rc = -EIO;
		जाओ error_out;
	पूर्ण
	nblocks = min(t64 - mapSize, XSize);

	/*
	 * update map pages क्रम new extension:
	 *
	 * update/init dmap and bubble up the control hierarchy
	 * incrementally fold up dmaps पूर्णांकo upper levels;
	 * update bmap control page;
	 */
	अगर ((rc = dbExtendFS(ipbmap, XAddress, nblocks)))
		जाओ error_out;

	agsizechanged |= (bmp->db_agsize != old_agsize);

	/*
	 * the map now has extended to cover additional nblocks:
	 * dn_mapsize = oldMapsize + nblocks;
	 */
	/* ipbmap->i_mapsize += nblocks; */
	XSize -= nblocks;

	/*
	 *	grow map file to cover reमुख्यing extension
	 *	and/or one extra dmap page क्रम next extendfs();
	 *
	 * allocate new map pages and its backing blocks, and
	 * update map file xtree
	 */
	/* compute number of data pages of current bmap file */
	nPages = ipbmap->i_size >> L2PSIZE;

	/* need to grow map file ? */
	अगर (nPages == newNpages)
		जाओ finalizeBmap;

	/*
	 * grow bmap file क्रम the new map pages required:
	 *
	 * allocate growth at the start of newly extended region;
	 * bmap file only grows sequentially, i.e., both data pages
	 * and possibly xtree index pages may grow in append mode,
	 * s.t. logreकरो() can reस्थिरruct pre-extension state
	 * by washing away bmap file of pages outside s_size boundary;
	 */
	/*
	 * journal map file growth as अगर a regular file growth:
	 * (note: bmap is created with di_mode = IFJOURNAL|IFREG);
	 *
	 * journaling of bmap file growth is not required since
	 * logreकरो() करो/can not use log records of bmap file growth
	 * but it provides careful ग_लिखो semantics, pmap update, etc.;
	 */
	/* synchronous ग_लिखो of data pages: bmap data pages are
	 * cached in meta-data cache, and not written out
	 * by txCommit();
	 */
	rc = filemap_fdataरुको(ipbmap->i_mapping);
	अगर (rc)
		जाओ error_out;

	rc = filemap_ग_लिखो_and_रुको(ipbmap->i_mapping);
	अगर (rc)
		जाओ error_out;

	diWriteSpecial(ipbmap, 0);

	newPage = nPages;	/* first new page number */
	xoff = newPage << sbi->l2nbperpage;
	xlen = (newNpages - nPages) << sbi->l2nbperpage;
	xlen = min(xlen, (पूर्णांक) nblocks) & ~(sbi->nbperpage - 1);
	xaddr = XAddress;

	tid = txBegin(sb, COMMIT_FORCE);

	अगर ((rc = xtAppend(tid, ipbmap, 0, xoff, nblocks, &xlen, &xaddr, 0))) अणु
		txEnd(tid);
		जाओ error_out;
	पूर्ण
	/* update bmap file size */
	ipbmap->i_size += xlen << sbi->l2bsize;
	inode_add_bytes(ipbmap, xlen << sbi->l2bsize);

	iplist[0] = ipbmap;
	rc = txCommit(tid, 1, &iplist[0], COMMIT_FORCE);

	txEnd(tid);

	अगर (rc)
		जाओ error_out;

	/*
	 * map file has been grown now to cover extension to further out;
	 * di_size = new map file size;
	 *
	 * अगर huge extension, the previous extension based on previous
	 * map file size may not have been sufficient to cover whole extension
	 * (it could have been used up क्रम new map pages),
	 * but the newly grown map file now covers lot bigger new मुक्त space
	 * available क्रम further extension of map;
	 */
	/* any more blocks to extend ? */
	अगर (XSize)
		जाओ extendBmap;

      finalizeBmap:
	/* finalize bmap */
	dbFinalizeBmap(ipbmap);

	/*
	 *	update inode allocation map
	 *	---------------------------
	 *
	 * move iag lists from old to new iag;
	 * agstart field is not updated क्रम logreकरो() to reस्थिरruct
	 * iag lists अगर प्रणाली crash occurs.
	 * (computation of ag number from agstart based on agsize
	 * will correctly identअगरy the new ag);
	 */
	/* अगर new AG size the same as old AG size, करोne! */
	अगर (agsizechanged) अणु
		अगर ((rc = diExtendFS(ipimap, ipbmap)))
			जाओ error_out;

		/* finalize imap */
		अगर ((rc = diSync(ipimap)))
			जाओ error_out;
	पूर्ण

	/*
	 *	finalize
	 *	--------
	 *
	 * extension is committed when on-disk super block is
	 * updated with new descriptors: logreकरो will recover
	 * crash beक्रमe it to pre-extension state;
	 */

	/* sync log to skip log replay of bmap file growth transaction; */
	/* lmLogSync(log, 1); */

	/*
	 * synchronous ग_लिखो bmap global control page;
	 * क्रम crash beक्रमe completion of ग_लिखो
	 * logreकरो() will recover to pre-extendfs state;
	 * क्रम crash after completion of ग_लिखो,
	 * logreकरो() will recover post-extendfs state;
	 */
	अगर ((rc = dbSync(ipbmap)))
		जाओ error_out;

	/*
	 * copy primary bmap inode to secondary bmap inode
	 */

	ipbmap2 = diReadSpecial(sb, BMAP_I, 1);
	अगर (ipbmap2 == शून्य) अणु
		prपूर्णांकk(KERN_ERR "jfs_extendfs: diReadSpecial(bmap) failed\n");
		जाओ error_out;
	पूर्ण
	स_नकल(&JFS_IP(ipbmap2)->i_xtroot, &JFS_IP(ipbmap)->i_xtroot, 288);
	ipbmap2->i_size = ipbmap->i_size;
	ipbmap2->i_blocks = ipbmap->i_blocks;

	diWriteSpecial(ipbmap2, 1);
	diFreeSpecial(ipbmap2);

	/*
	 *	update superblock
	 */
	अगर ((rc = पढ़ोSuper(sb, &bh)))
		जाओ error_out;
	j_sb = (काष्ठा jfs_superblock *)bh->b_data;

	/* mark extendfs() completion */
	j_sb->s_state &= cpu_to_le32(~FM_EXTENDFS);
	j_sb->s_size = cpu_to_le64(bmp->db_mapsize <<
				   le16_to_cpu(j_sb->s_l2bfactor));
	j_sb->s_agsize = cpu_to_le32(bmp->db_agsize);

	/* update अंतरभूत log space descriptor */
	अगर (sbi->mntflag & JFS_INLINELOG) अणु
		PXDaddress(&(j_sb->s_logpxd), newLogAddress);
		PXDlength(&(j_sb->s_logpxd), newLogSize);
	पूर्ण

	/* record log's mount serial number */
	j_sb->s_logserial = cpu_to_le32(log->serial);

	/* update fsck work space descriptor */
	PXDaddress(&(j_sb->s_fsckpxd), newFSCKAddress);
	PXDlength(&(j_sb->s_fsckpxd), newFSCKSize);
	j_sb->s_fscklog = 1;
	/* sb->s_fsckloglen reमुख्यs the same */

	/* Update secondary superblock */
	bh2 = sb_bपढ़ो(sb, SUPER2_OFF >> sb->s_blocksize_bits);
	अगर (bh2) अणु
		j_sb2 = (काष्ठा jfs_superblock *)bh2->b_data;
		स_नकल(j_sb2, j_sb, माप (काष्ठा jfs_superblock));

		mark_buffer_dirty(bh);
		sync_dirty_buffer(bh2);
		brअन्यथा(bh2);
	पूर्ण

	/* ग_लिखो primary superblock */
	mark_buffer_dirty(bh);
	sync_dirty_buffer(bh);
	brअन्यथा(bh);

	जाओ resume;

      error_out:
	jfs_error(sb, "\n");

      resume:
	/*
	 *	resume file प्रणाली transactions
	 */
	txResume(sb);

      out:
	वापस rc;
पूर्ण
