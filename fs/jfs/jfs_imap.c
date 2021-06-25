<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

/*
 *	jfs_imap.c: inode allocation map manager
 *
 * Serialization:
 *   Each AG has a simple lock which is used to control the serialization of
 *	the AG level lists.  This lock should be taken first whenever an AG
 *	level list will be modअगरied or accessed.
 *
 *   Each IAG is locked by obtaining the buffer क्रम the IAG page.
 *
 *   There is also a inode lock क्रम the inode map inode.  A पढ़ो lock needs to
 *	be taken whenever an IAG is पढ़ो from the map or the global level
 *	inक्रमmation is पढ़ो.  A ग_लिखो lock needs to be taken whenever the global
 *	level inक्रमmation is modअगरied or an atomic operation needs to be used.
 *
 *	If more than one IAG is पढ़ो at one समय, the पढ़ो lock may not
 *	be given up until all of the IAG's are पढ़ो.  Otherwise, a deadlock
 *	may occur when trying to obtain the पढ़ो lock जबतक another thपढ़ो
 *	holding the पढ़ो lock is रुकोing on the IAG alपढ़ोy being held.
 *
 *   The control page of the inode map is पढ़ो पूर्णांकo memory by diMount().
 *	Thereafter it should only be modअगरied in memory and then it will be
 *	written out when the fileप्रणाली is unmounted by diUnmount().
 */

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/slab.h>

#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_debug.h"

/*
 * imap locks
 */
/* iag मुक्त list lock */
#घोषणा IAGFREE_LOCK_INIT(imap)		mutex_init(&imap->im_मुक्तlock)
#घोषणा IAGFREE_LOCK(imap)		mutex_lock(&imap->im_मुक्तlock)
#घोषणा IAGFREE_UNLOCK(imap)		mutex_unlock(&imap->im_मुक्तlock)

/* per ag iag list locks */
#घोषणा AG_LOCK_INIT(imap,index)	mutex_init(&(imap->im_aglock[index]))
#घोषणा AG_LOCK(imap,agno)		mutex_lock(&imap->im_aglock[agno])
#घोषणा AG_UNLOCK(imap,agno)		mutex_unlock(&imap->im_aglock[agno])

/*
 * क्रमward references
 */
अटल पूर्णांक diAllocAG(काष्ठा inomap *, पूर्णांक, bool, काष्ठा inode *);
अटल पूर्णांक diAllocAny(काष्ठा inomap *, पूर्णांक, bool, काष्ठा inode *);
अटल पूर्णांक diAllocBit(काष्ठा inomap *, काष्ठा iag *, पूर्णांक);
अटल पूर्णांक diAllocExt(काष्ठा inomap *, पूर्णांक, काष्ठा inode *);
अटल पूर्णांक diAllocIno(काष्ठा inomap *, पूर्णांक, काष्ठा inode *);
अटल पूर्णांक diFindFree(u32, पूर्णांक);
अटल पूर्णांक diNewExt(काष्ठा inomap *, काष्ठा iag *, पूर्णांक);
अटल पूर्णांक diNewIAG(काष्ठा inomap *, पूर्णांक *, पूर्णांक, काष्ठा metapage **);
अटल व्योम duplicateIXtree(काष्ठा super_block *, s64, पूर्णांक, s64 *);

अटल पूर्णांक diIAGRead(काष्ठा inomap * imap, पूर्णांक, काष्ठा metapage **);
अटल पूर्णांक copy_from_dinode(काष्ठा dinode *, काष्ठा inode *);
अटल व्योम copy_to_dinode(काष्ठा dinode *, काष्ठा inode *);

/*
 * NAME:	diMount()
 *
 * FUNCTION:	initialize the incore inode map control काष्ठाures क्रम
 *		a fileset or aggregate init समय.
 *
 *		the inode map's control काष्ठाure (dinomap) is
 *		brought in from disk and placed in भव memory.
 *
 * PARAMETERS:
 *	ipimap	- poपूर्णांकer to inode map inode क्रम the aggregate or fileset.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOMEM	- insufficient मुक्त भव memory.
 *	-EIO	- i/o error.
 */
पूर्णांक diMount(काष्ठा inode *ipimap)
अणु
	काष्ठा inomap *imap;
	काष्ठा metapage *mp;
	पूर्णांक index;
	काष्ठा dinomap_disk *dinom_le;

	/*
	 * allocate/initialize the in-memory inode map control काष्ठाure
	 */
	/* allocate the in-memory inode map control काष्ठाure. */
	imap = kदो_स्मृति(माप(काष्ठा inomap), GFP_KERNEL);
	अगर (imap == शून्य) अणु
		jfs_err("diMount: kmalloc returned NULL!");
		वापस -ENOMEM;
	पूर्ण

	/* पढ़ो the on-disk inode map control काष्ठाure. */

	mp = पढ़ो_metapage(ipimap,
			   IMAPBLKNO << JFS_SBI(ipimap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	अगर (mp == शून्य) अणु
		kमुक्त(imap);
		वापस -EIO;
	पूर्ण

	/* copy the on-disk version to the in-memory version. */
	dinom_le = (काष्ठा dinomap_disk *) mp->data;
	imap->im_मुक्तiag = le32_to_cpu(dinom_le->in_मुक्तiag);
	imap->im_nextiag = le32_to_cpu(dinom_le->in_nextiag);
	atomic_set(&imap->im_numinos, le32_to_cpu(dinom_le->in_numinos));
	atomic_set(&imap->im_numमुक्त, le32_to_cpu(dinom_le->in_numमुक्त));
	imap->im_nbperiext = le32_to_cpu(dinom_le->in_nbperiext);
	imap->im_l2nbperiext = le32_to_cpu(dinom_le->in_l2nbperiext);
	क्रम (index = 0; index < MAXAG; index++) अणु
		imap->im_agctl[index].inoमुक्त =
		    le32_to_cpu(dinom_le->in_agctl[index].inoमुक्त);
		imap->im_agctl[index].extमुक्त =
		    le32_to_cpu(dinom_le->in_agctl[index].extमुक्त);
		imap->im_agctl[index].numinos =
		    le32_to_cpu(dinom_le->in_agctl[index].numinos);
		imap->im_agctl[index].numमुक्त =
		    le32_to_cpu(dinom_le->in_agctl[index].numमुक्त);
	पूर्ण

	/* release the buffer. */
	release_metapage(mp);

	/*
	 * allocate/initialize inode allocation map locks
	 */
	/* allocate and init iag मुक्त list lock */
	IAGFREE_LOCK_INIT(imap);

	/* allocate and init ag list locks */
	क्रम (index = 0; index < MAXAG; index++) अणु
		AG_LOCK_INIT(imap, index);
	पूर्ण

	/* bind the inode map inode and inode map control काष्ठाure
	 * to each other.
	 */
	imap->im_ipimap = ipimap;
	JFS_IP(ipimap)->i_imap = imap;

	वापस (0);
पूर्ण


/*
 * NAME:	diUnmount()
 *
 * FUNCTION:	ग_लिखो to disk the incore inode map control काष्ठाures क्रम
 *		a fileset or aggregate at unmount समय.
 *
 * PARAMETERS:
 *	ipimap	- poपूर्णांकer to inode map inode क्रम the aggregate or fileset.
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOMEM	- insufficient मुक्त भव memory.
 *	-EIO	- i/o error.
 */
पूर्णांक diUnmount(काष्ठा inode *ipimap, पूर्णांक mounterror)
अणु
	काष्ठा inomap *imap = JFS_IP(ipimap)->i_imap;

	/*
	 * update the on-disk inode map control काष्ठाure
	 */

	अगर (!(mounterror || isReadOnly(ipimap)))
		diSync(ipimap);

	/*
	 * Invalidate the page cache buffers
	 */
	truncate_inode_pages(ipimap->i_mapping, 0);

	/*
	 * मुक्त in-memory control काष्ठाure
	 */
	kमुक्त(imap);

	वापस (0);
पूर्ण


/*
 *	diSync()
 */
पूर्णांक diSync(काष्ठा inode *ipimap)
अणु
	काष्ठा dinomap_disk *dinom_le;
	काष्ठा inomap *imp = JFS_IP(ipimap)->i_imap;
	काष्ठा metapage *mp;
	पूर्णांक index;

	/*
	 * ग_लिखो imap global conrol page
	 */
	/* पढ़ो the on-disk inode map control काष्ठाure */
	mp = get_metapage(ipimap,
			  IMAPBLKNO << JFS_SBI(ipimap->i_sb)->l2nbperpage,
			  PSIZE, 0);
	अगर (mp == शून्य) अणु
		jfs_err("diSync: get_metapage failed!");
		वापस -EIO;
	पूर्ण

	/* copy the in-memory version to the on-disk version */
	dinom_le = (काष्ठा dinomap_disk *) mp->data;
	dinom_le->in_मुक्तiag = cpu_to_le32(imp->im_मुक्तiag);
	dinom_le->in_nextiag = cpu_to_le32(imp->im_nextiag);
	dinom_le->in_numinos = cpu_to_le32(atomic_पढ़ो(&imp->im_numinos));
	dinom_le->in_numमुक्त = cpu_to_le32(atomic_पढ़ो(&imp->im_numमुक्त));
	dinom_le->in_nbperiext = cpu_to_le32(imp->im_nbperiext);
	dinom_le->in_l2nbperiext = cpu_to_le32(imp->im_l2nbperiext);
	क्रम (index = 0; index < MAXAG; index++) अणु
		dinom_le->in_agctl[index].inoमुक्त =
		    cpu_to_le32(imp->im_agctl[index].inoमुक्त);
		dinom_le->in_agctl[index].extमुक्त =
		    cpu_to_le32(imp->im_agctl[index].extमुक्त);
		dinom_le->in_agctl[index].numinos =
		    cpu_to_le32(imp->im_agctl[index].numinos);
		dinom_le->in_agctl[index].numमुक्त =
		    cpu_to_le32(imp->im_agctl[index].numमुक्त);
	पूर्ण

	/* ग_लिखो out the control काष्ठाure */
	ग_लिखो_metapage(mp);

	/*
	 * ग_लिखो out dirty pages of imap
	 */
	filemap_ग_लिखो_and_रुको(ipimap->i_mapping);

	diWriteSpecial(ipimap, 0);

	वापस (0);
पूर्ण


/*
 * NAME:	diRead()
 *
 * FUNCTION:	initialize an incore inode from disk.
 *
 *		on entry, the specअगरed incore inode should itself
 *		specअगरy the disk inode number corresponding to the
 *		incore inode (i.e. i_number should be initialized).
 *
 *		this routine handles incore inode initialization क्रम
 *		both "special" and "regular" inodes.  special inodes
 *		are those required early in the mount process and
 *		require special handling since much of the file प्रणाली
 *		is not yet initialized.  these "special" inodes are
 *		identअगरied by a शून्य inode map inode poपूर्णांकer and are
 *		actually initialized by a call to diReadSpecial().
 *
 *		क्रम regular inodes, the iag describing the disk inode
 *		is पढ़ो from disk to determine the inode extent address
 *		क्रम the disk inode.  with the inode extent address in
 *		hand, the page of the extent that contains the disk
 *		inode is पढ़ो and the disk inode is copied to the
 *		incore inode.
 *
 * PARAMETERS:
 *	ip	-  poपूर्णांकer to incore inode to be initialized from disk.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 *	-ENOMEM	- insufficient memory
 *
 */
पूर्णांक diRead(काष्ठा inode *ip)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	पूर्णांक iagno, ino, extno, rc;
	काष्ठा inode *ipimap;
	काष्ठा dinode *dp;
	काष्ठा iag *iagp;
	काष्ठा metapage *mp;
	s64 blkno, agstart;
	काष्ठा inomap *imap;
	पूर्णांक block_offset;
	पूर्णांक inodes_left;
	अचिन्हित दीर्घ pageno;
	पूर्णांक rel_inode;

	jfs_info("diRead: ino = %ld", ip->i_ino);

	ipimap = sbi->ipimap;
	JFS_IP(ip)->ipimap = ipimap;

	/* determine the iag number क्रम this inode (number) */
	iagno = INOTOIAG(ip->i_ino);

	/* पढ़ो the iag */
	imap = JFS_IP(ipimap)->i_imap;
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);
	rc = diIAGRead(imap, iagno, &mp);
	IREAD_UNLOCK(ipimap);
	अगर (rc) अणु
		jfs_err("diRead: diIAGRead returned %d", rc);
		वापस (rc);
	पूर्ण

	iagp = (काष्ठा iag *) mp->data;

	/* determine inode extent that holds the disk inode */
	ino = ip->i_ino & (INOSPERIAG - 1);
	extno = ino >> L2INOSPEREXT;

	अगर ((lengthPXD(&iagp->inoext[extno]) != imap->im_nbperiext) ||
	    (addressPXD(&iagp->inoext[extno]) == 0)) अणु
		release_metapage(mp);
		वापस -ESTALE;
	पूर्ण

	/* get disk block number of the page within the inode extent
	 * that holds the disk inode.
	 */
	blkno = INOPBLK(&iagp->inoext[extno], ino, sbi->l2nbperpage);

	/* get the ag क्रम the iag */
	agstart = le64_to_cpu(iagp->agstart);

	release_metapage(mp);

	rel_inode = (ino & (INOSPERPAGE - 1));
	pageno = blkno >> sbi->l2nbperpage;

	अगर ((block_offset = ((u32) blkno & (sbi->nbperpage - 1)))) अणु
		/*
		 * OS/2 didn't always align inode extents on page boundaries
		 */
		inodes_left =
		     (sbi->nbperpage - block_offset) << sbi->l2niperblk;

		अगर (rel_inode < inodes_left)
			rel_inode += block_offset << sbi->l2niperblk;
		अन्यथा अणु
			pageno += 1;
			rel_inode -= inodes_left;
		पूर्ण
	पूर्ण

	/* पढ़ो the page of disk inode */
	mp = पढ़ो_metapage(ipimap, pageno << sbi->l2nbperpage, PSIZE, 1);
	अगर (!mp) अणु
		jfs_err("diRead: read_metapage failed");
		वापस -EIO;
	पूर्ण

	/* locate the disk inode requested */
	dp = (काष्ठा dinode *) mp->data;
	dp += rel_inode;

	अगर (ip->i_ino != le32_to_cpu(dp->di_number)) अणु
		jfs_error(ip->i_sb, "i_ino != di_number\n");
		rc = -EIO;
	पूर्ण अन्यथा अगर (le32_to_cpu(dp->di_nlink) == 0)
		rc = -ESTALE;
	अन्यथा
		/* copy the disk inode to the in-memory inode */
		rc = copy_from_dinode(dp, ip);

	release_metapage(mp);

	/* set the ag क्रम the inode */
	JFS_IP(ip)->agstart = agstart;
	JFS_IP(ip)->active_ag = -1;

	वापस (rc);
पूर्ण


/*
 * NAME:	diReadSpecial()
 *
 * FUNCTION:	initialize a 'special' inode from disk.
 *
 *		this routines handles aggregate level inodes.  The
 *		inode cache cannot dअगरferentiate between the
 *		aggregate inodes and the fileप्रणाली inodes, so we
 *		handle these here.  We करोn't actually use the aggregate
 *		inode map, since these inodes are at a fixed location
 *		and in some हालs the aggregate inode map isn't initialized
 *		yet.
 *
 * PARAMETERS:
 *	sb - fileप्रणाली superblock
 *	inum - aggregate inode number
 *	secondary - 1 अगर secondary aggregate inode table
 *
 * RETURN VALUES:
 *	new inode	- success
 *	शून्य		- i/o error.
 */
काष्ठा inode *diReadSpecial(काष्ठा super_block *sb, ino_t inum, पूर्णांक secondary)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	uपूर्णांक address;
	काष्ठा dinode *dp;
	काष्ठा inode *ip;
	काष्ठा metapage *mp;

	ip = new_inode(sb);
	अगर (ip == शून्य) अणु
		jfs_err("diReadSpecial: new_inode returned NULL!");
		वापस ip;
	पूर्ण

	अगर (secondary) अणु
		address = addressPXD(&sbi->ait2) >> sbi->l2nbperpage;
		JFS_IP(ip)->ipimap = sbi->ipaimap2;
	पूर्ण अन्यथा अणु
		address = AITBL_OFF >> L2PSIZE;
		JFS_IP(ip)->ipimap = sbi->ipaimap;
	पूर्ण

	ASSERT(inum < INOSPEREXT);

	ip->i_ino = inum;

	address += inum >> 3;	/* 8 inodes per 4K page */

	/* पढ़ो the page of fixed disk inode (AIT) in raw mode */
	mp = पढ़ो_metapage(ip, address << sbi->l2nbperpage, PSIZE, 1);
	अगर (mp == शून्य) अणु
		set_nlink(ip, 1);	/* Don't want iput() deleting it */
		iput(ip);
		वापस (शून्य);
	पूर्ण

	/* get the poपूर्णांकer to the disk inode of पूर्णांकerest */
	dp = (काष्ठा dinode *) (mp->data);
	dp += inum % 8;		/* 8 inodes per 4K page */

	/* copy on-disk inode to in-memory inode */
	अगर ((copy_from_dinode(dp, ip)) != 0) अणु
		/* handle bad वापस by वापसing शून्य क्रम ip */
		set_nlink(ip, 1);	/* Don't want iput() deleting it */
		iput(ip);
		/* release the page */
		release_metapage(mp);
		वापस (शून्य);

	पूर्ण

	ip->i_mapping->a_ops = &jfs_metapage_aops;
	mapping_set_gfp_mask(ip->i_mapping, GFP_NOFS);

	/* Allocations to metadata inodes should not affect quotas */
	ip->i_flags |= S_NOQUOTA;

	अगर ((inum == खाताSYSTEM_I) && (JFS_IP(ip)->ipimap == sbi->ipaimap)) अणु
		sbi->gengen = le32_to_cpu(dp->di_gengen);
		sbi->inostamp = le32_to_cpu(dp->di_inostamp);
	पूर्ण

	/* release the page */
	release_metapage(mp);

	inode_fake_hash(ip);

	वापस (ip);
पूर्ण

/*
 * NAME:	diWriteSpecial()
 *
 * FUNCTION:	Write the special inode to disk
 *
 * PARAMETERS:
 *	ip - special inode
 *	secondary - 1 अगर secondary aggregate inode table
 *
 * RETURN VALUES: none
 */

व्योम diWriteSpecial(काष्ठा inode *ip, पूर्णांक secondary)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	uपूर्णांक address;
	काष्ठा dinode *dp;
	ino_t inum = ip->i_ino;
	काष्ठा metapage *mp;

	अगर (secondary)
		address = addressPXD(&sbi->ait2) >> sbi->l2nbperpage;
	अन्यथा
		address = AITBL_OFF >> L2PSIZE;

	ASSERT(inum < INOSPEREXT);

	address += inum >> 3;	/* 8 inodes per 4K page */

	/* पढ़ो the page of fixed disk inode (AIT) in raw mode */
	mp = पढ़ो_metapage(ip, address << sbi->l2nbperpage, PSIZE, 1);
	अगर (mp == शून्य) अणु
		jfs_err("diWriteSpecial: failed to read aggregate inode extent!");
		वापस;
	पूर्ण

	/* get the poपूर्णांकer to the disk inode of पूर्णांकerest */
	dp = (काष्ठा dinode *) (mp->data);
	dp += inum % 8;		/* 8 inodes per 4K page */

	/* copy on-disk inode to in-memory inode */
	copy_to_dinode(dp, ip);
	स_नकल(&dp->di_xtroot, &JFS_IP(ip)->i_xtroot, 288);

	अगर (inum == खाताSYSTEM_I)
		dp->di_gengen = cpu_to_le32(sbi->gengen);

	/* ग_लिखो the page */
	ग_लिखो_metapage(mp);
पूर्ण

/*
 * NAME:	diFreeSpecial()
 *
 * FUNCTION:	Free allocated space क्रम special inode
 */
व्योम diFreeSpecial(काष्ठा inode *ip)
अणु
	अगर (ip == शून्य) अणु
		jfs_err("diFreeSpecial called with NULL ip!");
		वापस;
	पूर्ण
	filemap_ग_लिखो_and_रुको(ip->i_mapping);
	truncate_inode_pages(ip->i_mapping, 0);
	iput(ip);
पूर्ण



/*
 * NAME:	diWrite()
 *
 * FUNCTION:	ग_लिखो the on-disk inode portion of the in-memory inode
 *		to its corresponding on-disk inode.
 *
 *		on entry, the specअगरed incore inode should itself
 *		specअगरy the disk inode number corresponding to the
 *		incore inode (i.e. i_number should be initialized).
 *
 *		the inode contains the inode extent address क्रम the disk
 *		inode.  with the inode extent address in hand, the
 *		page of the extent that contains the disk inode is
 *		पढ़ो and the disk inode portion of the incore inode
 *		is copied to the disk inode.
 *
 * PARAMETERS:
 *	tid -  transacation id
 *	ip  -  poपूर्णांकer to incore inode to be written to the inode extent.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 */
पूर्णांक diWrite(tid_t tid, काष्ठा inode *ip)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	पूर्णांक rc = 0;
	s32 ino;
	काष्ठा dinode *dp;
	s64 blkno;
	पूर्णांक block_offset;
	पूर्णांक inodes_left;
	काष्ठा metapage *mp;
	अचिन्हित दीर्घ pageno;
	पूर्णांक rel_inode;
	पूर्णांक dioffset;
	काष्ठा inode *ipimap;
	uपूर्णांक type;
	lid_t lid;
	काष्ठा tlock *ditlck, *tlck;
	काष्ठा linelock *dilinelock, *ilinelock;
	काष्ठा lv *lv;
	पूर्णांक n;

	ipimap = jfs_ip->ipimap;

	ino = ip->i_ino & (INOSPERIAG - 1);

	अगर (!addressPXD(&(jfs_ip->ixpxd)) ||
	    (lengthPXD(&(jfs_ip->ixpxd)) !=
	     JFS_IP(ipimap)->i_imap->im_nbperiext)) अणु
		jfs_error(ip->i_sb, "ixpxd invalid\n");
		वापस -EIO;
	पूर्ण

	/*
	 * पढ़ो the page of disk inode containing the specअगरied inode:
	 */
	/* compute the block address of the page */
	blkno = INOPBLK(&(jfs_ip->ixpxd), ino, sbi->l2nbperpage);

	rel_inode = (ino & (INOSPERPAGE - 1));
	pageno = blkno >> sbi->l2nbperpage;

	अगर ((block_offset = ((u32) blkno & (sbi->nbperpage - 1)))) अणु
		/*
		 * OS/2 didn't always align inode extents on page boundaries
		 */
		inodes_left =
		    (sbi->nbperpage - block_offset) << sbi->l2niperblk;

		अगर (rel_inode < inodes_left)
			rel_inode += block_offset << sbi->l2niperblk;
		अन्यथा अणु
			pageno += 1;
			rel_inode -= inodes_left;
		पूर्ण
	पूर्ण
	/* पढ़ो the page of disk inode */
      retry:
	mp = पढ़ो_metapage(ipimap, pageno << sbi->l2nbperpage, PSIZE, 1);
	अगर (!mp)
		वापस -EIO;

	/* get the poपूर्णांकer to the disk inode */
	dp = (काष्ठा dinode *) mp->data;
	dp += rel_inode;

	dioffset = (ino & (INOSPERPAGE - 1)) << L2DISIZE;

	/*
	 * acquire transaction lock on the on-disk inode;
	 * N.B. tlock is acquired on ipimap not ip;
	 */
	अगर ((ditlck =
	     txLock(tid, ipimap, mp, tlckINODE | tlckENTRY)) == शून्य)
		जाओ retry;
	dilinelock = (काष्ठा linelock *) & ditlck->lock;

	/*
	 * copy btree root from in-memory inode to on-disk inode
	 *
	 * (tlock is taken from अंतरभूत B+-tree root in in-memory
	 * inode when the B+-tree root is updated, which is poपूर्णांकed
	 * by jfs_ip->blid as well as being on tx tlock list)
	 *
	 * further processing of btree root is based on the copy
	 * in in-memory inode, where txLog() will log from, and,
	 * क्रम xtree root, txUpdateMap() will update map and reset
	 * XAD_NEW bit;
	 */

	अगर (S_ISसूची(ip->i_mode) && (lid = jfs_ip->xtlid)) अणु
		/*
		 * This is the special xtree inside the directory क्रम storing
		 * the directory table
		 */
		xtpage_t *p, *xp;
		xad_t *xad;

		jfs_ip->xtlid = 0;
		tlck = lid_to_tlock(lid);
		निश्चित(tlck->type & tlckXTREE);
		tlck->type |= tlckBTROOT;
		tlck->mp = mp;
		ilinelock = (काष्ठा linelock *) & tlck->lock;

		/*
		 * copy xtree root from inode to dinode:
		 */
		p = &jfs_ip->i_xtroot;
		xp = (xtpage_t *) &dp->di_dirtable;
		lv = ilinelock->lv;
		क्रम (n = 0; n < ilinelock->index; n++, lv++) अणु
			स_नकल(&xp->xad[lv->offset], &p->xad[lv->offset],
			       lv->length << L2XTSLOTSIZE);
		पूर्ण

		/* reset on-disk (metadata page) xtree XAD_NEW bit */
		xad = &xp->xad[XTENTRYSTART];
		क्रम (n = XTENTRYSTART;
		     n < le16_to_cpu(xp->header.nextindex); n++, xad++)
			अगर (xad->flag & (XAD_NEW | XAD_EXTENDED))
				xad->flag &= ~(XAD_NEW | XAD_EXTENDED);
	पूर्ण

	अगर ((lid = jfs_ip->blid) == 0)
		जाओ अंतरभूतData;
	jfs_ip->blid = 0;

	tlck = lid_to_tlock(lid);
	type = tlck->type;
	tlck->type |= tlckBTROOT;
	tlck->mp = mp;
	ilinelock = (काष्ठा linelock *) & tlck->lock;

	/*
	 *	regular file: 16 byte (XAD slot) granularity
	 */
	अगर (type & tlckXTREE) अणु
		xtpage_t *p, *xp;
		xad_t *xad;

		/*
		 * copy xtree root from inode to dinode:
		 */
		p = &jfs_ip->i_xtroot;
		xp = &dp->di_xtroot;
		lv = ilinelock->lv;
		क्रम (n = 0; n < ilinelock->index; n++, lv++) अणु
			स_नकल(&xp->xad[lv->offset], &p->xad[lv->offset],
			       lv->length << L2XTSLOTSIZE);
		पूर्ण

		/* reset on-disk (metadata page) xtree XAD_NEW bit */
		xad = &xp->xad[XTENTRYSTART];
		क्रम (n = XTENTRYSTART;
		     n < le16_to_cpu(xp->header.nextindex); n++, xad++)
			अगर (xad->flag & (XAD_NEW | XAD_EXTENDED))
				xad->flag &= ~(XAD_NEW | XAD_EXTENDED);
	पूर्ण
	/*
	 *	directory: 32 byte (directory entry slot) granularity
	 */
	अन्यथा अगर (type & tlckDTREE) अणु
		dtpage_t *p, *xp;

		/*
		 * copy dtree root from inode to dinode:
		 */
		p = (dtpage_t *) &jfs_ip->i_dtroot;
		xp = (dtpage_t *) & dp->di_dtroot;
		lv = ilinelock->lv;
		क्रम (n = 0; n < ilinelock->index; n++, lv++) अणु
			स_नकल(&xp->slot[lv->offset], &p->slot[lv->offset],
			       lv->length << L2DTSLOTSIZE);
		पूर्ण
	पूर्ण अन्यथा अणु
		jfs_err("diWrite: UFO tlock");
	पूर्ण

      अंतरभूतData:
	/*
	 * copy अंतरभूत symlink from in-memory inode to on-disk inode
	 */
	अगर (S_ISLNK(ip->i_mode) && ip->i_size < IDATASIZE) अणु
		lv = & dilinelock->lv[dilinelock->index];
		lv->offset = (dioffset + 2 * 128) >> L2INODESLOTSIZE;
		lv->length = 2;
		स_नकल(&dp->di_fastsymlink, jfs_ip->i_अंतरभूत, IDATASIZE);
		dilinelock->index++;
	पूर्ण
	/*
	 * copy अंतरभूत data from in-memory inode to on-disk inode:
	 * 128 byte slot granularity
	 */
	अगर (test_cflag(COMMIT_Inlineea, ip)) अणु
		lv = & dilinelock->lv[dilinelock->index];
		lv->offset = (dioffset + 3 * 128) >> L2INODESLOTSIZE;
		lv->length = 1;
		स_नकल(&dp->di_अंतरभूतea, jfs_ip->i_अंतरभूत_ea, INODESLOTSIZE);
		dilinelock->index++;

		clear_cflag(COMMIT_Inlineea, ip);
	पूर्ण

	/*
	 *	lock/copy inode base: 128 byte slot granularity
	 */
	lv = & dilinelock->lv[dilinelock->index];
	lv->offset = dioffset >> L2INODESLOTSIZE;
	copy_to_dinode(dp, ip);
	अगर (test_and_clear_cflag(COMMIT_Dirtable, ip)) अणु
		lv->length = 2;
		स_नकल(&dp->di_dirtable, &jfs_ip->i_dirtable, 96);
	पूर्ण अन्यथा
		lv->length = 1;
	dilinelock->index++;

	/* release the buffer holding the updated on-disk inode.
	 * the buffer will be later written by commit processing.
	 */
	ग_लिखो_metapage(mp);

	वापस (rc);
पूर्ण


/*
 * NAME:	diFree(ip)
 *
 * FUNCTION:	मुक्त a specअगरied inode from the inode working map
 *		क्रम a fileset or aggregate.
 *
 *		अगर the inode to be मुक्तd represents the first (only)
 *		मुक्त inode within the iag, the iag will be placed on
 *		the ag मुक्त inode list.
 *
 *		मुक्तing the inode will cause the inode extent to be
 *		मुक्तd अगर the inode is the only allocated inode within
 *		the extent.  in this हाल all the disk resource backing
 *		up the inode extent will be मुक्तd. in addition, the iag
 *		will be placed on the ag extent मुक्त list अगर the extent
 *		is the first मुक्त extent in the iag.  अगर मुक्तing the
 *		extent also means that no मुक्त inodes will exist क्रम
 *		the iag, the iag will also be हटाओd from the ag मुक्त
 *		inode list.
 *
 *		the iag describing the inode will be मुक्तd अगर the extent
 *		is to be मुक्तd and it is the only backed extent within
 *		the iag.  in this हाल, the iag will be हटाओd from the
 *		ag मुक्त extent list and ag मुक्त inode list and placed on
 *		the inode map's मुक्त iag list.
 *
 *		a careful update approach is used to provide consistency
 *		in the face of updates to multiple buffers.  under this
 *		approach, all required buffers are obtained beक्रमe making
 *		any updates and are held until all updates are complete.
 *
 * PARAMETERS:
 *	ip	- inode to be मुक्तd.
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error.
 */
पूर्णांक diFree(काष्ठा inode *ip)
अणु
	पूर्णांक rc;
	ino_t inum = ip->i_ino;
	काष्ठा iag *iagp, *aiagp, *biagp, *ciagp, *diagp;
	काष्ठा metapage *mp, *amp, *bmp, *cmp, *dmp;
	पूर्णांक iagno, ino, extno, bitno, sword, agno;
	पूर्णांक back, fwd;
	u32 biपंचांगap, mask;
	काष्ठा inode *ipimap = JFS_SBI(ip->i_sb)->ipimap;
	काष्ठा inomap *imap = JFS_IP(ipimap)->i_imap;
	pxd_t मुक्तpxd;
	tid_t tid;
	काष्ठा inode *iplist[3];
	काष्ठा tlock *tlck;
	काष्ठा pxd_lock *pxdlock;

	/*
	 * This is just to suppress compiler warnings.  The same logic that
	 * references these variables is used to initialize them.
	 */
	aiagp = biagp = ciagp = diagp = शून्य;

	/* get the iag number containing the inode.
	 */
	iagno = INOTOIAG(inum);

	/* make sure that the iag is contained within
	 * the map.
	 */
	अगर (iagno >= imap->im_nextiag) अणु
		prपूर्णांक_hex_dump(KERN_ERR, "imap: ", DUMP_PREFIX_ADDRESS, 16, 4,
			       imap, 32, 0);
		jfs_error(ip->i_sb, "inum = %d, iagno = %d, nextiag = %d\n",
			  (uपूर्णांक) inum, iagno, imap->im_nextiag);
		वापस -EIO;
	पूर्ण

	/* get the allocation group क्रम this ino.
	 */
	agno = BLKTOAG(JFS_IP(ip)->agstart, JFS_SBI(ip->i_sb));

	/* Lock the AG specअगरic inode map inक्रमmation
	 */
	AG_LOCK(imap, agno);

	/* Obtain पढ़ो lock in imap inode.  Don't release it until we have
	 * पढ़ो all of the IAG's that we are going to.
	 */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);

	/* पढ़ो the iag.
	 */
	अगर ((rc = diIAGRead(imap, iagno, &mp))) अणु
		IREAD_UNLOCK(ipimap);
		AG_UNLOCK(imap, agno);
		वापस (rc);
	पूर्ण
	iagp = (काष्ठा iag *) mp->data;

	/* get the inode number and extent number of the inode within
	 * the iag and the inode number within the extent.
	 */
	ino = inum & (INOSPERIAG - 1);
	extno = ino >> L2INOSPEREXT;
	bitno = ino & (INOSPEREXT - 1);
	mask = HIGHORDER >> bitno;

	अगर (!(le32_to_cpu(iagp->wmap[extno]) & mask)) अणु
		jfs_error(ip->i_sb, "wmap shows inode already free\n");
	पूर्ण

	अगर (!addressPXD(&iagp->inoext[extno])) अणु
		release_metapage(mp);
		IREAD_UNLOCK(ipimap);
		AG_UNLOCK(imap, agno);
		jfs_error(ip->i_sb, "invalid inoext\n");
		वापस -EIO;
	पूर्ण

	/* compute the biपंचांगap क्रम the extent reflecting the मुक्तd inode.
	 */
	biपंचांगap = le32_to_cpu(iagp->wmap[extno]) & ~mask;

	अगर (imap->im_agctl[agno].numमुक्त > imap->im_agctl[agno].numinos) अणु
		release_metapage(mp);
		IREAD_UNLOCK(ipimap);
		AG_UNLOCK(imap, agno);
		jfs_error(ip->i_sb, "numfree > numinos\n");
		वापस -EIO;
	पूर्ण
	/*
	 *	inode extent still has some inodes or below low water mark:
	 *	keep the inode extent;
	 */
	अगर (biपंचांगap ||
	    imap->im_agctl[agno].numमुक्त < 96 ||
	    (imap->im_agctl[agno].numमुक्त < 288 &&
	     (((imap->im_agctl[agno].numमुक्त * 100) /
	       imap->im_agctl[agno].numinos) <= 25))) अणु
		/* अगर the iag currently has no मुक्त inodes (i.e.,
		 * the inode being मुक्तd is the first मुक्त inode of iag),
		 * insert the iag at head of the inode मुक्त list क्रम the ag.
		 */
		अगर (iagp->nमुक्तinos == 0) अणु
			/* check अगर there are any iags on the ag inode
			 * मुक्त list.  अगर so, पढ़ो the first one so that
			 * we can link the current iag onto the list at
			 * the head.
			 */
			अगर ((fwd = imap->im_agctl[agno].inoमुक्त) >= 0) अणु
				/* पढ़ो the iag that currently is the head
				 * of the list.
				 */
				अगर ((rc = diIAGRead(imap, fwd, &amp))) अणु
					IREAD_UNLOCK(ipimap);
					AG_UNLOCK(imap, agno);
					release_metapage(mp);
					वापस (rc);
				पूर्ण
				aiagp = (काष्ठा iag *) amp->data;

				/* make current head poपूर्णांक back to the iag.
				 */
				aiagp->inoमुक्तback = cpu_to_le32(iagno);

				ग_लिखो_metapage(amp);
			पूर्ण

			/* iag poपूर्णांकs क्रमward to current head and iag
			 * becomes the new head of the list.
			 */
			iagp->inoमुक्तfwd =
			    cpu_to_le32(imap->im_agctl[agno].inoमुक्त);
			iagp->inoमुक्तback = cpu_to_le32(-1);
			imap->im_agctl[agno].inoमुक्त = iagno;
		पूर्ण
		IREAD_UNLOCK(ipimap);

		/* update the मुक्त inode summary map क्रम the extent अगर
		 * मुक्तing the inode means the extent will now have मुक्त
		 * inodes (i.e., the inode being मुक्तd is the first मुक्त
		 * inode of extent),
		 */
		अगर (iagp->wmap[extno] == cpu_to_le32(ONES)) अणु
			sword = extno >> L2EXTSPERSUM;
			bitno = extno & (EXTSPERSUM - 1);
			iagp->inosmap[sword] &=
			    cpu_to_le32(~(HIGHORDER >> bitno));
		पूर्ण

		/* update the biपंचांगap.
		 */
		iagp->wmap[extno] = cpu_to_le32(biपंचांगap);

		/* update the मुक्त inode counts at the iag, ag and
		 * map level.
		 */
		le32_add_cpu(&iagp->nमुक्तinos, 1);
		imap->im_agctl[agno].numमुक्त += 1;
		atomic_inc(&imap->im_numमुक्त);

		/* release the AG inode map lock
		 */
		AG_UNLOCK(imap, agno);

		/* ग_लिखो the iag */
		ग_लिखो_metapage(mp);

		वापस (0);
	पूर्ण


	/*
	 *	inode extent has become मुक्त and above low water mark:
	 *	मुक्त the inode extent;
	 */

	/*
	 *	prepare to update iag list(s) (careful update step 1)
	 */
	amp = bmp = cmp = dmp = शून्य;
	fwd = back = -1;

	/* check अगर the iag currently has no मुक्त extents.  अगर so,
	 * it will be placed on the head of the ag extent मुक्त list.
	 */
	अगर (iagp->nमुक्तexts == 0) अणु
		/* check अगर the ag extent मुक्त list has any iags.
		 * अगर so, पढ़ो the iag at the head of the list now.
		 * this (head) iag will be updated later to reflect
		 * the addition of the current iag at the head of
		 * the list.
		 */
		अगर ((fwd = imap->im_agctl[agno].extमुक्त) >= 0) अणु
			अगर ((rc = diIAGRead(imap, fwd, &amp)))
				जाओ error_out;
			aiagp = (काष्ठा iag *) amp->data;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* iag has मुक्त extents. check अगर the addition of a मुक्त
		 * extent will cause all extents to be मुक्त within this
		 * iag.  अगर so, the iag will be हटाओd from the ag extent
		 * मुक्त list and placed on the inode map's मुक्त iag list.
		 */
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG - 1)) अणु
			/* in preparation क्रम removing the iag from the
			 * ag extent मुक्त list, पढ़ो the iags preceding
			 * and following the iag on the ag extent मुक्त
			 * list.
			 */
			अगर ((fwd = le32_to_cpu(iagp->extमुक्तfwd)) >= 0) अणु
				अगर ((rc = diIAGRead(imap, fwd, &amp)))
					जाओ error_out;
				aiagp = (काष्ठा iag *) amp->data;
			पूर्ण

			अगर ((back = le32_to_cpu(iagp->extमुक्तback)) >= 0) अणु
				अगर ((rc = diIAGRead(imap, back, &bmp)))
					जाओ error_out;
				biagp = (काष्ठा iag *) bmp->data;
			पूर्ण
		पूर्ण
	पूर्ण

	/* हटाओ the iag from the ag inode मुक्त list अगर मुक्तing
	 * this extent cause the iag to have no मुक्त inodes.
	 */
	अगर (iagp->nमुक्तinos == cpu_to_le32(INOSPEREXT - 1)) अणु
		पूर्णांक inoमुक्तback = le32_to_cpu(iagp->inoमुक्तback);
		पूर्णांक inoमुक्तfwd = le32_to_cpu(iagp->inoमुक्तfwd);

		/* in preparation क्रम removing the iag from the
		 * ag inode मुक्त list, पढ़ो the iags preceding
		 * and following the iag on the ag inode मुक्त
		 * list.  beक्रमe पढ़ोing these iags, we must make
		 * sure that we alपढ़ोy करोn't have them in hand
		 * from up above, since re-पढ़ोing an iag (buffer)
		 * we are currently holding would cause a deadlock.
		 */
		अगर (inoमुक्तfwd >= 0) अणु

			अगर (inoमुक्तfwd == fwd)
				ciagp = (काष्ठा iag *) amp->data;
			अन्यथा अगर (inoमुक्तfwd == back)
				ciagp = (काष्ठा iag *) bmp->data;
			अन्यथा अणु
				अगर ((rc =
				     diIAGRead(imap, inoमुक्तfwd, &cmp)))
					जाओ error_out;
				ciagp = (काष्ठा iag *) cmp->data;
			पूर्ण
			निश्चित(ciagp != शून्य);
		पूर्ण

		अगर (inoमुक्तback >= 0) अणु
			अगर (inoमुक्तback == fwd)
				diagp = (काष्ठा iag *) amp->data;
			अन्यथा अगर (inoमुक्तback == back)
				diagp = (काष्ठा iag *) bmp->data;
			अन्यथा अणु
				अगर ((rc =
				     diIAGRead(imap, inoमुक्तback, &dmp)))
					जाओ error_out;
				diagp = (काष्ठा iag *) dmp->data;
			पूर्ण
			निश्चित(diagp != शून्य);
		पूर्ण
	पूर्ण

	IREAD_UNLOCK(ipimap);

	/*
	 * invalidate any page of the inode extent मुक्तd from buffer cache;
	 */
	मुक्तpxd = iagp->inoext[extno];
	invalidate_pxd_metapages(ip, मुक्तpxd);

	/*
	 *	update iag list(s) (careful update step 2)
	 */
	/* add the iag to the ag extent मुक्त list अगर this is the
	 * first मुक्त extent क्रम the iag.
	 */
	अगर (iagp->nमुक्तexts == 0) अणु
		अगर (fwd >= 0)
			aiagp->extमुक्तback = cpu_to_le32(iagno);

		iagp->extमुक्तfwd =
		    cpu_to_le32(imap->im_agctl[agno].extमुक्त);
		iagp->extमुक्तback = cpu_to_le32(-1);
		imap->im_agctl[agno].extमुक्त = iagno;
	पूर्ण अन्यथा अणु
		/* हटाओ the iag from the ag extent list अगर all extents
		 * are now मुक्त and place it on the inode map iag मुक्त list.
		 */
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG - 1)) अणु
			अगर (fwd >= 0)
				aiagp->extमुक्तback = iagp->extमुक्तback;

			अगर (back >= 0)
				biagp->extमुक्तfwd = iagp->extमुक्तfwd;
			अन्यथा
				imap->im_agctl[agno].extमुक्त =
				    le32_to_cpu(iagp->extमुक्तfwd);

			iagp->extमुक्तfwd = iagp->extमुक्तback = cpu_to_le32(-1);

			IAGFREE_LOCK(imap);
			iagp->iagमुक्त = cpu_to_le32(imap->im_मुक्तiag);
			imap->im_मुक्तiag = iagno;
			IAGFREE_UNLOCK(imap);
		पूर्ण
	पूर्ण

	/* हटाओ the iag from the ag inode मुक्त list अगर मुक्तing
	 * this extent causes the iag to have no मुक्त inodes.
	 */
	अगर (iagp->nमुक्तinos == cpu_to_le32(INOSPEREXT - 1)) अणु
		अगर ((पूर्णांक) le32_to_cpu(iagp->inoमुक्तfwd) >= 0)
			ciagp->inoमुक्तback = iagp->inoमुक्तback;

		अगर ((पूर्णांक) le32_to_cpu(iagp->inoमुक्तback) >= 0)
			diagp->inoमुक्तfwd = iagp->inoमुक्तfwd;
		अन्यथा
			imap->im_agctl[agno].inoमुक्त =
			    le32_to_cpu(iagp->inoमुक्तfwd);

		iagp->inoमुक्तfwd = iagp->inoमुक्तback = cpu_to_le32(-1);
	पूर्ण

	/* update the inode extent address and working map
	 * to reflect the मुक्त extent.
	 * the permanent map should have been updated alपढ़ोy
	 * क्रम the inode being मुक्तd.
	 */
	अगर (iagp->pmap[extno] != 0) अणु
		jfs_error(ip->i_sb, "the pmap does not show inode free\n");
	पूर्ण
	iagp->wmap[extno] = 0;
	PXDlength(&iagp->inoext[extno], 0);
	PXDaddress(&iagp->inoext[extno], 0);

	/* update the मुक्त extent and मुक्त inode summary maps
	 * to reflect the मुक्तd extent.
	 * the inode summary map is marked to indicate no inodes
	 * available क्रम the मुक्तd extent.
	 */
	sword = extno >> L2EXTSPERSUM;
	bitno = extno & (EXTSPERSUM - 1);
	mask = HIGHORDER >> bitno;
	iagp->inosmap[sword] |= cpu_to_le32(mask);
	iagp->extsmap[sword] &= cpu_to_le32(~mask);

	/* update the number of मुक्त inodes and number of मुक्त extents
	 * क्रम the iag.
	 */
	le32_add_cpu(&iagp->nमुक्तinos, -(INOSPEREXT - 1));
	le32_add_cpu(&iagp->nमुक्तexts, 1);

	/* update the number of मुक्त inodes and backed inodes
	 * at the ag and inode map level.
	 */
	imap->im_agctl[agno].numमुक्त -= (INOSPEREXT - 1);
	imap->im_agctl[agno].numinos -= INOSPEREXT;
	atomic_sub(INOSPEREXT - 1, &imap->im_numमुक्त);
	atomic_sub(INOSPEREXT, &imap->im_numinos);

	अगर (amp)
		ग_लिखो_metapage(amp);
	अगर (bmp)
		ग_लिखो_metapage(bmp);
	अगर (cmp)
		ग_लिखो_metapage(cmp);
	अगर (dmp)
		ग_लिखो_metapage(dmp);

	/*
	 * start transaction to update block allocation map
	 * क्रम the inode extent मुक्तd;
	 *
	 * N.B. AG_LOCK is released and iag will be released below, and
	 * other thपढ़ो may allocate inode from/reusing the ixad मुक्तd
	 * BUT with new/dअगरferent backing inode extent from the extent
	 * to be मुक्तd by the transaction;
	 */
	tid = txBegin(ipimap->i_sb, COMMIT_FORCE);
	mutex_lock(&JFS_IP(ipimap)->commit_mutex);

	/* acquire tlock of the iag page of the मुक्तd ixad
	 * to क्रमce the page NOHOMEOK (even though no data is
	 * logged from the iag page) until NOREDOPAGE|FREEXTENT log
	 * क्रम the मुक्त of the extent is committed;
	 * ग_लिखो FREEXTENT|NOREDOPAGE log record
	 * N.B. linelock is overlaid as मुक्तd extent descriptor;
	 */
	tlck = txLock(tid, ipimap, mp, tlckINODE | tlckFREE);
	pxdlock = (काष्ठा pxd_lock *) & tlck->lock;
	pxdlock->flag = mlckFREEPXD;
	pxdlock->pxd = मुक्तpxd;
	pxdlock->index = 1;

	ग_लिखो_metapage(mp);

	iplist[0] = ipimap;

	/*
	 * logreकरो needs the IAG number and IAG extent index in order
	 * to ensure that the IMap is consistent.  The least disruptive
	 * way to pass these values through  to the transaction manager
	 * is in the iplist array.
	 *
	 * It's not pretty, but it works.
	 */
	iplist[1] = (काष्ठा inode *) (माप_प्रकार)iagno;
	iplist[2] = (काष्ठा inode *) (माप_प्रकार)extno;

	rc = txCommit(tid, 1, &iplist[0], COMMIT_FORCE);

	txEnd(tid);
	mutex_unlock(&JFS_IP(ipimap)->commit_mutex);

	/* unlock the AG inode map inक्रमmation */
	AG_UNLOCK(imap, agno);

	वापस (0);

      error_out:
	IREAD_UNLOCK(ipimap);

	अगर (amp)
		release_metapage(amp);
	अगर (bmp)
		release_metapage(bmp);
	अगर (cmp)
		release_metapage(cmp);
	अगर (dmp)
		release_metapage(dmp);

	AG_UNLOCK(imap, agno);

	release_metapage(mp);

	वापस (rc);
पूर्ण

/*
 * There are several places in the diAlloc* routines where we initialize
 * the inode.
 */
अटल अंतरभूत व्योम
diInitInode(काष्ठा inode *ip, पूर्णांक iagno, पूर्णांक ino, पूर्णांक extno, काष्ठा iag * iagp)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);

	ip->i_ino = (iagno << L2INOSPERIAG) + ino;
	jfs_ip->ixpxd = iagp->inoext[extno];
	jfs_ip->agstart = le64_to_cpu(iagp->agstart);
	jfs_ip->active_ag = -1;
पूर्ण


/*
 * NAME:	diAlloc(pip,dir,ip)
 *
 * FUNCTION:	allocate a disk inode from the inode working map
 *		क्रम a fileset or aggregate.
 *
 * PARAMETERS:
 *	pip	- poपूर्णांकer to incore inode क्रम the parent inode.
 *	dir	- 'true' अगर the new disk inode is क्रम a directory.
 *	ip	- poपूर्णांकer to a new inode
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
पूर्णांक diAlloc(काष्ठा inode *pip, bool dir, काष्ठा inode *ip)
अणु
	पूर्णांक rc, ino, iagno, addext, extno, bitno, sword;
	पूर्णांक nwords, rem, i, agno;
	u32 mask, inosmap, extsmap;
	काष्ठा inode *ipimap;
	काष्ठा metapage *mp;
	ino_t inum;
	काष्ठा iag *iagp;
	काष्ठा inomap *imap;

	/* get the poपूर्णांकers to the inode map inode and the
	 * corresponding imap control काष्ठाure.
	 */
	ipimap = JFS_SBI(pip->i_sb)->ipimap;
	imap = JFS_IP(ipimap)->i_imap;
	JFS_IP(ip)->ipimap = ipimap;
	JFS_IP(ip)->fileset = खाताSYSTEM_I;

	/* क्रम a directory, the allocation policy is to start
	 * at the ag level using the preferred ag.
	 */
	अगर (dir) अणु
		agno = dbNextAG(JFS_SBI(pip->i_sb)->ipbmap);
		AG_LOCK(imap, agno);
		जाओ tryag;
	पूर्ण

	/* क्रम files, the policy starts off by trying to allocate from
	 * the same iag containing the parent disk inode:
	 * try to allocate the new disk inode बंद to the parent disk
	 * inode, using parent disk inode number + 1 as the allocation
	 * hपूर्णांक.  (we use a left-to-right policy to attempt to aव्योम
	 * moving backward on the disk.)  compute the hपूर्णांक within the
	 * file प्रणाली and the iag.
	 */

	/* get the ag number of this iag */
	agno = BLKTOAG(JFS_IP(pip)->agstart, JFS_SBI(pip->i_sb));

	अगर (atomic_पढ़ो(&JFS_SBI(pip->i_sb)->bmap->db_active[agno])) अणु
		/*
		 * There is an खोलो file actively growing.  We want to
		 * allocate new inodes from a dअगरferent ag to aव्योम
		 * fragmentation problems.
		 */
		agno = dbNextAG(JFS_SBI(pip->i_sb)->ipbmap);
		AG_LOCK(imap, agno);
		जाओ tryag;
	पूर्ण

	inum = pip->i_ino + 1;
	ino = inum & (INOSPERIAG - 1);

	/* back off the hपूर्णांक अगर it is outside of the iag */
	अगर (ino == 0)
		inum = pip->i_ino;

	/* lock the AG inode map inक्रमmation */
	AG_LOCK(imap, agno);

	/* Get पढ़ो lock on imap inode */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);

	/* get the iag number and पढ़ो the iag */
	iagno = INOTOIAG(inum);
	अगर ((rc = diIAGRead(imap, iagno, &mp))) अणु
		IREAD_UNLOCK(ipimap);
		AG_UNLOCK(imap, agno);
		वापस (rc);
	पूर्ण
	iagp = (काष्ठा iag *) mp->data;

	/* determine अगर new inode extent is allowed to be added to the iag.
	 * new inode extent can be added to the iag अगर the ag
	 * has less than 32 मुक्त disk inodes and the iag has मुक्त extents.
	 */
	addext = (imap->im_agctl[agno].numमुक्त < 32 && iagp->nमुक्तexts);

	/*
	 *	try to allocate from the IAG
	 */
	/* check अगर the inode may be allocated from the iag
	 * (i.e. the inode has मुक्त inodes or new extent can be added).
	 */
	अगर (iagp->nमुक्तinos || addext) अणु
		/* determine the extent number of the hपूर्णांक.
		 */
		extno = ino >> L2INOSPEREXT;

		/* check अगर the extent containing the hपूर्णांक has backed
		 * inodes.  अगर so, try to allocate within this extent.
		 */
		अगर (addressPXD(&iagp->inoext[extno])) अणु
			bitno = ino & (INOSPEREXT - 1);
			अगर ((bitno =
			     diFindFree(le32_to_cpu(iagp->wmap[extno]),
					bitno))
			    < INOSPEREXT) अणु
				ino = (extno << L2INOSPEREXT) + bitno;

				/* a मुक्त inode (bit) was found within this
				 * extent, so allocate it.
				 */
				rc = diAllocBit(imap, iagp, ino);
				IREAD_UNLOCK(ipimap);
				अगर (rc) अणु
					निश्चित(rc == -EIO);
				पूर्ण अन्यथा अणु
					/* set the results of the allocation
					 * and ग_लिखो the iag.
					 */
					diInitInode(ip, iagno, ino, extno,
						    iagp);
					mark_metapage_dirty(mp);
				पूर्ण
				release_metapage(mp);

				/* मुक्त the AG lock and वापस.
				 */
				AG_UNLOCK(imap, agno);
				वापस (rc);
			पूर्ण

			अगर (!addext)
				extno =
				    (extno ==
				     EXTSPERIAG - 1) ? 0 : extno + 1;
		पूर्ण

		/*
		 * no मुक्त inodes within the extent containing the hपूर्णांक.
		 *
		 * try to allocate from the backed extents following
		 * hपूर्णांक or, अगर appropriate (i.e. addext is true), allocate
		 * an extent of मुक्त inodes at or following the extent
		 * containing the hपूर्णांक.
		 *
		 * the मुक्त inode and मुक्त extent summary maps are used
		 * here, so determine the starting summary map position
		 * and the number of words we'll have to examine.  again,
		 * the approach is to allocate following the hपूर्णांक, so we
		 * might have to initially ignore prior bits of the summary
		 * map that represent extents prior to the extent containing
		 * the hपूर्णांक and later revisit these bits.
		 */
		bitno = extno & (EXTSPERSUM - 1);
		nwords = (bitno == 0) ? SMAPSZ : SMAPSZ + 1;
		sword = extno >> L2EXTSPERSUM;

		/* mask any prior bits क्रम the starting words of the
		 * summary map.
		 */
		mask = (bitno == 0) ? 0 : (ONES << (EXTSPERSUM - bitno));
		inosmap = le32_to_cpu(iagp->inosmap[sword]) | mask;
		extsmap = le32_to_cpu(iagp->extsmap[sword]) | mask;

		/* scan the मुक्त inode and मुक्त extent summary maps क्रम
		 * मुक्त resources.
		 */
		क्रम (i = 0; i < nwords; i++) अणु
			/* check अगर this word of the मुक्त inode summary
			 * map describes an extent with मुक्त inodes.
			 */
			अगर (~inosmap) अणु
				/* an extent with मुक्त inodes has been
				 * found. determine the extent number
				 * and the inode number within the extent.
				 */
				rem = diFindFree(inosmap, 0);
				extno = (sword << L2EXTSPERSUM) + rem;
				rem = diFindFree(le32_to_cpu(iagp->wmap[extno]),
						 0);
				अगर (rem >= INOSPEREXT) अणु
					IREAD_UNLOCK(ipimap);
					release_metapage(mp);
					AG_UNLOCK(imap, agno);
					jfs_error(ip->i_sb,
						  "can't find free bit in wmap\n");
					वापस -EIO;
				पूर्ण

				/* determine the inode number within the
				 * iag and allocate the inode from the
				 * map.
				 */
				ino = (extno << L2INOSPEREXT) + rem;
				rc = diAllocBit(imap, iagp, ino);
				IREAD_UNLOCK(ipimap);
				अगर (rc)
					निश्चित(rc == -EIO);
				अन्यथा अणु
					/* set the results of the allocation
					 * and ग_लिखो the iag.
					 */
					diInitInode(ip, iagno, ino, extno,
						    iagp);
					mark_metapage_dirty(mp);
				पूर्ण
				release_metapage(mp);

				/* मुक्त the AG lock and वापस.
				 */
				AG_UNLOCK(imap, agno);
				वापस (rc);

			पूर्ण

			/* check अगर we may allocate an extent of मुक्त
			 * inodes and whether this word of the मुक्त
			 * extents summary map describes a मुक्त extent.
			 */
			अगर (addext && ~extsmap) अणु
				/* a मुक्त extent has been found.  determine
				 * the extent number.
				 */
				rem = diFindFree(extsmap, 0);
				extno = (sword << L2EXTSPERSUM) + rem;

				/* allocate an extent of मुक्त inodes.
				 */
				अगर ((rc = diNewExt(imap, iagp, extno))) अणु
					/* अगर there is no disk space क्रम a
					 * new extent, try to allocate the
					 * disk inode from somewhere अन्यथा.
					 */
					अगर (rc == -ENOSPC)
						अवरोध;

					निश्चित(rc == -EIO);
				पूर्ण अन्यथा अणु
					/* set the results of the allocation
					 * and ग_लिखो the iag.
					 */
					diInitInode(ip, iagno,
						    extno << L2INOSPEREXT,
						    extno, iagp);
					mark_metapage_dirty(mp);
				पूर्ण
				release_metapage(mp);
				/* मुक्त the imap inode & the AG lock & वापस.
				 */
				IREAD_UNLOCK(ipimap);
				AG_UNLOCK(imap, agno);
				वापस (rc);
			पूर्ण

			/* move on to the next set of summary map words.
			 */
			sword = (sword == SMAPSZ - 1) ? 0 : sword + 1;
			inosmap = le32_to_cpu(iagp->inosmap[sword]);
			extsmap = le32_to_cpu(iagp->extsmap[sword]);
		पूर्ण
	पूर्ण
	/* unlock imap inode */
	IREAD_UNLOCK(ipimap);

	/* nothing करोing in this iag, so release it. */
	release_metapage(mp);

      tryag:
	/*
	 * try to allocate anywhere within the same AG as the parent inode.
	 */
	rc = diAllocAG(imap, agno, dir, ip);

	AG_UNLOCK(imap, agno);

	अगर (rc != -ENOSPC)
		वापस (rc);

	/*
	 * try to allocate in any AG.
	 */
	वापस (diAllocAny(imap, agno, dir, ip));
पूर्ण


/*
 * NAME:	diAllocAG(imap,agno,dir,ip)
 *
 * FUNCTION:	allocate a disk inode from the allocation group.
 *
 *		this routine first determines अगर a new extent of मुक्त
 *		inodes should be added क्रम the allocation group, with
 *		the current request satisfied from this extent. अगर this
 *		is the हाल, an attempt will be made to करो just that.  अगर
 *		this attempt fails or it has been determined that a new
 *		extent should not be added, an attempt is made to satisfy
 *		the request by allocating an existing (backed) मुक्त inode
 *		from the allocation group.
 *
 * PRE CONDITION: Alपढ़ोy have the AG lock क्रम this AG.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	agno	- allocation group to allocate from.
 *	dir	- 'true' अगर the new disk inode is क्रम a directory.
 *	ip	- poपूर्णांकer to the new inode to be filled in on successful वापस
 *		  with the disk inode number allocated, its extent address
 *		  and the start of the ag.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक
diAllocAG(काष्ठा inomap * imap, पूर्णांक agno, bool dir, काष्ठा inode *ip)
अणु
	पूर्णांक rc, addext, numमुक्त, numinos;

	/* get the number of मुक्त and the number of backed disk
	 * inodes currently within the ag.
	 */
	numमुक्त = imap->im_agctl[agno].numमुक्त;
	numinos = imap->im_agctl[agno].numinos;

	अगर (numमुक्त > numinos) अणु
		jfs_error(ip->i_sb, "numfree > numinos\n");
		वापस -EIO;
	पूर्ण

	/* determine अगर we should allocate a new extent of मुक्त inodes
	 * within the ag: क्रम directory inodes, add a new extent
	 * अगर there are a small number of मुक्त inodes or number of मुक्त
	 * inodes is a small percentage of the number of backed inodes.
	 */
	अगर (dir)
		addext = (numमुक्त < 64 ||
			  (numमुक्त < 256
			   && ((numमुक्त * 100) / numinos) <= 20));
	अन्यथा
		addext = (numमुक्त == 0);

	/*
	 * try to allocate a new extent of मुक्त inodes.
	 */
	अगर (addext) अणु
		/* अगर मुक्त space is not available क्रम this new extent, try
		 * below to allocate a मुक्त and existing (alपढ़ोy backed)
		 * inode from the ag.
		 */
		अगर ((rc = diAllocExt(imap, agno, ip)) != -ENOSPC)
			वापस (rc);
	पूर्ण

	/*
	 * try to allocate an existing मुक्त inode from the ag.
	 */
	वापस (diAllocIno(imap, agno, ip));
पूर्ण


/*
 * NAME:	diAllocAny(imap,agno,dir,iap)
 *
 * FUNCTION:	allocate a disk inode from any other allocation group.
 *
 *		this routine is called when an allocation attempt within
 *		the primary allocation group has failed. अगर attempts to
 *		allocate an inode from any allocation group other than the
 *		specअगरied primary group.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	agno	- primary allocation group (to aव्योम).
 *	dir	- 'true' अगर the new disk inode is क्रम a directory.
 *	ip	- poपूर्णांकer to a new inode to be filled in on successful वापस
 *		  with the disk inode number allocated, its extent address
 *		  and the start of the ag.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक
diAllocAny(काष्ठा inomap * imap, पूर्णांक agno, bool dir, काष्ठा inode *ip)
अणु
	पूर्णांक ag, rc;
	पूर्णांक maxag = JFS_SBI(imap->im_ipimap->i_sb)->bmap->db_maxag;


	/* try to allocate from the ags following agno up to
	 * the maximum ag number.
	 */
	क्रम (ag = agno + 1; ag <= maxag; ag++) अणु
		AG_LOCK(imap, ag);

		rc = diAllocAG(imap, ag, dir, ip);

		AG_UNLOCK(imap, ag);

		अगर (rc != -ENOSPC)
			वापस (rc);
	पूर्ण

	/* try to allocate from the ags in front of agno.
	 */
	क्रम (ag = 0; ag < agno; ag++) अणु
		AG_LOCK(imap, ag);

		rc = diAllocAG(imap, ag, dir, ip);

		AG_UNLOCK(imap, ag);

		अगर (rc != -ENOSPC)
			वापस (rc);
	पूर्ण

	/* no मुक्त disk inodes.
	 */
	वापस -ENOSPC;
पूर्ण


/*
 * NAME:	diAllocIno(imap,agno,ip)
 *
 * FUNCTION:	allocate a disk inode from the allocation group's मुक्त
 *		inode list, वापसing an error अगर this मुक्त list is
 *		empty (i.e. no iags on the list).
 *
 *		allocation occurs from the first iag on the list using
 *		the iag's मुक्त inode summary map to find the lefपंचांगost
 *		मुक्त inode in the iag.
 *
 * PRE CONDITION: Alपढ़ोy have AG lock क्रम this AG.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	agno	- allocation group.
 *	ip	- poपूर्णांकer to new inode to be filled in on successful वापस
 *		  with the disk inode number allocated, its extent address
 *		  and the start of the ag.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक diAllocIno(काष्ठा inomap * imap, पूर्णांक agno, काष्ठा inode *ip)
अणु
	पूर्णांक iagno, ino, rc, rem, extno, sword;
	काष्ठा metapage *mp;
	काष्ठा iag *iagp;

	/* check अगर there are iags on the ag's मुक्त inode list.
	 */
	अगर ((iagno = imap->im_agctl[agno].inoमुक्त) < 0)
		वापस -ENOSPC;

	/* obtain पढ़ो lock on imap inode */
	IREAD_LOCK(imap->im_ipimap, RDWRLOCK_IMAP);

	/* पढ़ो the iag at the head of the list.
	 */
	अगर ((rc = diIAGRead(imap, iagno, &mp))) अणु
		IREAD_UNLOCK(imap->im_ipimap);
		वापस (rc);
	पूर्ण
	iagp = (काष्ठा iag *) mp->data;

	/* better be मुक्त inodes in this iag अगर it is on the
	 * list.
	 */
	अगर (!iagp->nमुक्तinos) अणु
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb, "nfreeinos = 0, but iag on freelist\n");
		वापस -EIO;
	पूर्ण

	/* scan the मुक्त inode summary map to find an extent
	 * with मुक्त inodes.
	 */
	क्रम (sword = 0;; sword++) अणु
		अगर (sword >= SMAPSZ) अणु
			IREAD_UNLOCK(imap->im_ipimap);
			release_metapage(mp);
			jfs_error(ip->i_sb,
				  "free inode not found in summary map\n");
			वापस -EIO;
		पूर्ण

		अगर (~iagp->inosmap[sword])
			अवरोध;
	पूर्ण

	/* found a extent with मुक्त inodes. determine
	 * the extent number.
	 */
	rem = diFindFree(le32_to_cpu(iagp->inosmap[sword]), 0);
	अगर (rem >= EXTSPERSUM) अणु
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb, "no free extent found\n");
		वापस -EIO;
	पूर्ण
	extno = (sword << L2EXTSPERSUM) + rem;

	/* find the first मुक्त inode in the extent.
	 */
	rem = diFindFree(le32_to_cpu(iagp->wmap[extno]), 0);
	अगर (rem >= INOSPEREXT) अणु
		IREAD_UNLOCK(imap->im_ipimap);
		release_metapage(mp);
		jfs_error(ip->i_sb, "free inode not found\n");
		वापस -EIO;
	पूर्ण

	/* compute the inode number within the iag.
	 */
	ino = (extno << L2INOSPEREXT) + rem;

	/* allocate the inode.
	 */
	rc = diAllocBit(imap, iagp, ino);
	IREAD_UNLOCK(imap->im_ipimap);
	अगर (rc) अणु
		release_metapage(mp);
		वापस (rc);
	पूर्ण

	/* set the results of the allocation and ग_लिखो the iag.
	 */
	diInitInode(ip, iagno, ino, extno, iagp);
	ग_लिखो_metapage(mp);

	वापस (0);
पूर्ण


/*
 * NAME:	diAllocExt(imap,agno,ip)
 *
 * FUNCTION:	add a new extent of मुक्त inodes to an iag, allocating
 *		an inode from this extent to satisfy the current allocation
 *		request.
 *
 *		this routine first tries to find an existing iag with मुक्त
 *		extents through the ag मुक्त extent list.  अगर list is not
 *		empty, the head of the list will be selected as the home
 *		of the new extent of मुक्त inodes.  otherwise (the list is
 *		empty), a new iag will be allocated क्रम the ag to contain
 *		the extent.
 *
 *		once an iag has been selected, the मुक्त extent summary map
 *		is used to locate a मुक्त extent within the iag and diNewExt()
 *		is called to initialize the extent, with initialization
 *		including the allocation of the first inode of the extent
 *		क्रम the purpose of satisfying this request.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	agno	- allocation group number.
 *	ip	- poपूर्णांकer to new inode to be filled in on successful वापस
 *		  with the disk inode number allocated, its extent address
 *		  and the start of the ag.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक diAllocExt(काष्ठा inomap * imap, पूर्णांक agno, काष्ठा inode *ip)
अणु
	पूर्णांक rem, iagno, sword, extno, rc;
	काष्ठा metapage *mp;
	काष्ठा iag *iagp;

	/* check अगर the ag has any iags with मुक्त extents.  अगर not,
	 * allocate a new iag क्रम the ag.
	 */
	अगर ((iagno = imap->im_agctl[agno].extमुक्त) < 0) अणु
		/* If successful, diNewIAG will obtain the पढ़ो lock on the
		 * imap inode.
		 */
		अगर ((rc = diNewIAG(imap, &iagno, agno, &mp))) अणु
			वापस (rc);
		पूर्ण
		iagp = (काष्ठा iag *) mp->data;

		/* set the ag number अगर this a bअक्रम new iag
		 */
		iagp->agstart =
		    cpu_to_le64(AGTOBLK(agno, imap->im_ipimap));
	पूर्ण अन्यथा अणु
		/* पढ़ो the iag.
		 */
		IREAD_LOCK(imap->im_ipimap, RDWRLOCK_IMAP);
		अगर ((rc = diIAGRead(imap, iagno, &mp))) अणु
			IREAD_UNLOCK(imap->im_ipimap);
			jfs_error(ip->i_sb, "error reading iag\n");
			वापस rc;
		पूर्ण
		iagp = (काष्ठा iag *) mp->data;
	पूर्ण

	/* using the मुक्त extent summary map, find a मुक्त extent.
	 */
	क्रम (sword = 0;; sword++) अणु
		अगर (sword >= SMAPSZ) अणु
			release_metapage(mp);
			IREAD_UNLOCK(imap->im_ipimap);
			jfs_error(ip->i_sb, "free ext summary map not found\n");
			वापस -EIO;
		पूर्ण
		अगर (~iagp->extsmap[sword])
			अवरोध;
	पूर्ण

	/* determine the extent number of the मुक्त extent.
	 */
	rem = diFindFree(le32_to_cpu(iagp->extsmap[sword]), 0);
	अगर (rem >= EXTSPERSUM) अणु
		release_metapage(mp);
		IREAD_UNLOCK(imap->im_ipimap);
		jfs_error(ip->i_sb, "free extent not found\n");
		वापस -EIO;
	पूर्ण
	extno = (sword << L2EXTSPERSUM) + rem;

	/* initialize the new extent.
	 */
	rc = diNewExt(imap, iagp, extno);
	IREAD_UNLOCK(imap->im_ipimap);
	अगर (rc) अणु
		/* something bad happened.  अगर a new iag was allocated,
		 * place it back on the inode map's iag मुक्त list, and
		 * clear the ag number inक्रमmation.
		 */
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG)) अणु
			IAGFREE_LOCK(imap);
			iagp->iagमुक्त = cpu_to_le32(imap->im_मुक्तiag);
			imap->im_मुक्तiag = iagno;
			IAGFREE_UNLOCK(imap);
		पूर्ण
		ग_लिखो_metapage(mp);
		वापस (rc);
	पूर्ण

	/* set the results of the allocation and ग_लिखो the iag.
	 */
	diInitInode(ip, iagno, extno << L2INOSPEREXT, extno, iagp);

	ग_लिखो_metapage(mp);

	वापस (0);
पूर्ण


/*
 * NAME:	diAllocBit(imap,iagp,ino)
 *
 * FUNCTION:	allocate a backed inode from an iag.
 *
 *		this routine perक्रमms the mechanics of allocating a
 *		specअगरied inode from a backed extent.
 *
 *		अगर the inode to be allocated represents the last मुक्त
 *		inode within the iag, the iag will be हटाओd from the
 *		ag मुक्त inode list.
 *
 *		a careful update approach is used to provide consistency
 *		in the face of updates to multiple buffers.  under this
 *		approach, all required buffers are obtained beक्रमe making
 *		any updates and are held all are updates are complete.
 *
 * PRE CONDITION: Alपढ़ोy have buffer lock on iagp.  Alपढ़ोy have AG lock on
 *	this AG.  Must have पढ़ो lock on imap inode.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	iagp	- poपूर्णांकer to iag.
 *	ino	- inode number to be allocated within the iag.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक diAllocBit(काष्ठा inomap * imap, काष्ठा iag * iagp, पूर्णांक ino)
अणु
	पूर्णांक extno, bitno, agno, sword, rc;
	काष्ठा metapage *amp = शून्य, *bmp = शून्य;
	काष्ठा iag *aiagp = शून्य, *biagp = शून्य;
	u32 mask;

	/* check अगर this is the last मुक्त inode within the iag.
	 * अगर so, it will have to be हटाओd from the ag मुक्त
	 * inode list, so get the iags preceding and following
	 * it on the list.
	 */
	अगर (iagp->nमुक्तinos == cpu_to_le32(1)) अणु
		अगर ((पूर्णांक) le32_to_cpu(iagp->inoमुक्तfwd) >= 0) अणु
			अगर ((rc =
			     diIAGRead(imap, le32_to_cpu(iagp->inoमुक्तfwd),
				       &amp)))
				वापस (rc);
			aiagp = (काष्ठा iag *) amp->data;
		पूर्ण

		अगर ((पूर्णांक) le32_to_cpu(iagp->inoमुक्तback) >= 0) अणु
			अगर ((rc =
			     diIAGRead(imap,
				       le32_to_cpu(iagp->inoमुक्तback),
				       &bmp))) अणु
				अगर (amp)
					release_metapage(amp);
				वापस (rc);
			पूर्ण
			biagp = (काष्ठा iag *) bmp->data;
		पूर्ण
	पूर्ण

	/* get the ag number, extent number, inode number within
	 * the extent.
	 */
	agno = BLKTOAG(le64_to_cpu(iagp->agstart), JFS_SBI(imap->im_ipimap->i_sb));
	extno = ino >> L2INOSPEREXT;
	bitno = ino & (INOSPEREXT - 1);

	/* compute the mask क्रम setting the map.
	 */
	mask = HIGHORDER >> bitno;

	/* the inode should be मुक्त and backed.
	 */
	अगर (((le32_to_cpu(iagp->pmap[extno]) & mask) != 0) ||
	    ((le32_to_cpu(iagp->wmap[extno]) & mask) != 0) ||
	    (addressPXD(&iagp->inoext[extno]) == 0)) अणु
		अगर (amp)
			release_metapage(amp);
		अगर (bmp)
			release_metapage(bmp);

		jfs_error(imap->im_ipimap->i_sb, "iag inconsistent\n");
		वापस -EIO;
	पूर्ण

	/* mark the inode as allocated in the working map.
	 */
	iagp->wmap[extno] |= cpu_to_le32(mask);

	/* check अगर all inodes within the extent are now
	 * allocated.  अगर so, update the मुक्त inode summary
	 * map to reflect this.
	 */
	अगर (iagp->wmap[extno] == cpu_to_le32(ONES)) अणु
		sword = extno >> L2EXTSPERSUM;
		bitno = extno & (EXTSPERSUM - 1);
		iagp->inosmap[sword] |= cpu_to_le32(HIGHORDER >> bitno);
	पूर्ण

	/* अगर this was the last मुक्त inode in the iag, हटाओ the
	 * iag from the ag मुक्त inode list.
	 */
	अगर (iagp->nमुक्तinos == cpu_to_le32(1)) अणु
		अगर (amp) अणु
			aiagp->inoमुक्तback = iagp->inoमुक्तback;
			ग_लिखो_metapage(amp);
		पूर्ण

		अगर (bmp) अणु
			biagp->inoमुक्तfwd = iagp->inoमुक्तfwd;
			ग_लिखो_metapage(bmp);
		पूर्ण अन्यथा अणु
			imap->im_agctl[agno].inoमुक्त =
			    le32_to_cpu(iagp->inoमुक्तfwd);
		पूर्ण
		iagp->inoमुक्तfwd = iagp->inoमुक्तback = cpu_to_le32(-1);
	पूर्ण

	/* update the मुक्त inode count at the iag, ag, inode
	 * map levels.
	 */
	le32_add_cpu(&iagp->nमुक्तinos, -1);
	imap->im_agctl[agno].numमुक्त -= 1;
	atomic_dec(&imap->im_numमुक्त);

	वापस (0);
पूर्ण


/*
 * NAME:	diNewExt(imap,iagp,extno)
 *
 * FUNCTION:	initialize a new extent of inodes क्रम an iag, allocating
 *		the first inode of the extent क्रम use क्रम the current
 *		allocation request.
 *
 *		disk resources are allocated क्रम the new extent of inodes
 *		and the inodes themselves are initialized to reflect their
 *		existence within the extent (i.e. their inode numbers and
 *		inode extent addresses are set) and their initial state
 *		(mode and link count are set to zero).
 *
 *		अगर the iag is new, it is not yet on an ag extent मुक्त list
 *		but will now be placed on this list.
 *
 *		अगर the allocation of the new extent causes the iag to
 *		have no मुक्त extent, the iag will be हटाओd from the
 *		ag extent मुक्त list.
 *
 *		अगर the iag has no मुक्त backed inodes, it will be placed
 *		on the ag मुक्त inode list, since the addition of the new
 *		extent will now cause it to have मुक्त inodes.
 *
 *		a careful update approach is used to provide consistency
 *		(i.e. list consistency) in the face of updates to multiple
 *		buffers.  under this approach, all required buffers are
 *		obtained beक्रमe making any updates and are held until all
 *		updates are complete.
 *
 * PRE CONDITION: Alपढ़ोy have buffer lock on iagp.  Alपढ़ोy have AG lock on
 *	this AG.  Must have पढ़ो lock on imap inode.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	iagp	- poपूर्णांकer to iag.
 *	extno	- extent number.
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक diNewExt(काष्ठा inomap * imap, काष्ठा iag * iagp, पूर्णांक extno)
अणु
	पूर्णांक agno, iagno, fwd, back, मुक्तi = 0, sword, rc;
	काष्ठा iag *aiagp = शून्य, *biagp = शून्य, *ciagp = शून्य;
	काष्ठा metapage *amp, *bmp, *cmp, *dmp;
	काष्ठा inode *ipimap;
	s64 blkno, hपूर्णांक;
	पूर्णांक i, j;
	u32 mask;
	ino_t ino;
	काष्ठा dinode *dp;
	काष्ठा jfs_sb_info *sbi;

	/* better have मुक्त extents.
	 */
	अगर (!iagp->nमुक्तexts) अणु
		jfs_error(imap->im_ipimap->i_sb, "no free extents\n");
		वापस -EIO;
	पूर्ण

	/* get the inode map inode.
	 */
	ipimap = imap->im_ipimap;
	sbi = JFS_SBI(ipimap->i_sb);

	amp = bmp = cmp = शून्य;

	/* get the ag and iag numbers क्रम this iag.
	 */
	agno = BLKTOAG(le64_to_cpu(iagp->agstart), sbi);
	iagno = le32_to_cpu(iagp->iagnum);

	/* check अगर this is the last मुक्त extent within the
	 * iag.  अगर so, the iag must be हटाओd from the ag
	 * मुक्त extent list, so get the iags preceding and
	 * following the iag on this list.
	 */
	अगर (iagp->nमुक्तexts == cpu_to_le32(1)) अणु
		अगर ((fwd = le32_to_cpu(iagp->extमुक्तfwd)) >= 0) अणु
			अगर ((rc = diIAGRead(imap, fwd, &amp)))
				वापस (rc);
			aiagp = (काष्ठा iag *) amp->data;
		पूर्ण

		अगर ((back = le32_to_cpu(iagp->extमुक्तback)) >= 0) अणु
			अगर ((rc = diIAGRead(imap, back, &bmp)))
				जाओ error_out;
			biagp = (काष्ठा iag *) bmp->data;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* the iag has मुक्त extents.  अगर all extents are मुक्त
		 * (as is the हाल क्रम a newly allocated iag), the iag
		 * must be added to the ag मुक्त extent list, so get
		 * the iag at the head of the list in preparation क्रम
		 * adding this iag to this list.
		 */
		fwd = back = -1;
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG)) अणु
			अगर ((fwd = imap->im_agctl[agno].extमुक्त) >= 0) अणु
				अगर ((rc = diIAGRead(imap, fwd, &amp)))
					जाओ error_out;
				aiagp = (काष्ठा iag *) amp->data;
			पूर्ण
		पूर्ण
	पूर्ण

	/* check अगर the iag has no मुक्त inodes.  अगर so, the iag
	 * will have to be added to the ag मुक्त inode list, so get
	 * the iag at the head of the list in preparation क्रम
	 * adding this iag to this list.  in करोing this, we must
	 * check अगर we alपढ़ोy have the iag at the head of
	 * the list in hand.
	 */
	अगर (iagp->nमुक्तinos == 0) अणु
		मुक्तi = imap->im_agctl[agno].inoमुक्त;

		अगर (मुक्तi >= 0) अणु
			अगर (मुक्तi == fwd) अणु
				ciagp = aiagp;
			पूर्ण अन्यथा अगर (मुक्तi == back) अणु
				ciagp = biagp;
			पूर्ण अन्यथा अणु
				अगर ((rc = diIAGRead(imap, मुक्तi, &cmp)))
					जाओ error_out;
				ciagp = (काष्ठा iag *) cmp->data;
			पूर्ण
			अगर (ciagp == शून्य) अणु
				jfs_error(imap->im_ipimap->i_sb,
					  "ciagp == NULL\n");
				rc = -EIO;
				जाओ error_out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* allocate disk space क्रम the inode extent.
	 */
	अगर ((extno == 0) || (addressPXD(&iagp->inoext[extno - 1]) == 0))
		hपूर्णांक = ((s64) agno << sbi->bmap->db_agl2size) - 1;
	अन्यथा
		hपूर्णांक = addressPXD(&iagp->inoext[extno - 1]) +
		    lengthPXD(&iagp->inoext[extno - 1]) - 1;

	अगर ((rc = dbAlloc(ipimap, hपूर्णांक, (s64) imap->im_nbperiext, &blkno)))
		जाओ error_out;

	/* compute the inode number of the first inode within the
	 * extent.
	 */
	ino = (iagno << L2INOSPERIAG) + (extno << L2INOSPEREXT);

	/* initialize the inodes within the newly allocated extent a
	 * page at a समय.
	 */
	क्रम (i = 0; i < imap->im_nbperiext; i += sbi->nbperpage) अणु
		/* get a buffer क्रम this page of disk inodes.
		 */
		dmp = get_metapage(ipimap, blkno + i, PSIZE, 1);
		अगर (dmp == शून्य) अणु
			rc = -EIO;
			जाओ error_out;
		पूर्ण
		dp = (काष्ठा dinode *) dmp->data;

		/* initialize the inode number, mode, link count and
		 * inode extent address.
		 */
		क्रम (j = 0; j < INOSPERPAGE; j++, dp++, ino++) अणु
			dp->di_inostamp = cpu_to_le32(sbi->inostamp);
			dp->di_number = cpu_to_le32(ino);
			dp->di_fileset = cpu_to_le32(खाताSYSTEM_I);
			dp->di_mode = 0;
			dp->di_nlink = 0;
			PXDaddress(&(dp->di_ixpxd), blkno);
			PXDlength(&(dp->di_ixpxd), imap->im_nbperiext);
		पूर्ण
		ग_लिखो_metapage(dmp);
	पूर्ण

	/* अगर this is the last मुक्त extent within the iag, हटाओ the
	 * iag from the ag मुक्त extent list.
	 */
	अगर (iagp->nमुक्तexts == cpu_to_le32(1)) अणु
		अगर (fwd >= 0)
			aiagp->extमुक्तback = iagp->extमुक्तback;

		अगर (back >= 0)
			biagp->extमुक्तfwd = iagp->extमुक्तfwd;
		अन्यथा
			imap->im_agctl[agno].extमुक्त =
			    le32_to_cpu(iagp->extमुक्तfwd);

		iagp->extमुक्तfwd = iagp->extमुक्तback = cpu_to_le32(-1);
	पूर्ण अन्यथा अणु
		/* अगर the iag has all मुक्त extents (newly allocated iag),
		 * add the iag to the ag मुक्त extent list.
		 */
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG)) अणु
			अगर (fwd >= 0)
				aiagp->extमुक्तback = cpu_to_le32(iagno);

			iagp->extमुक्तfwd = cpu_to_le32(fwd);
			iagp->extमुक्तback = cpu_to_le32(-1);
			imap->im_agctl[agno].extमुक्त = iagno;
		पूर्ण
	पूर्ण

	/* अगर the iag has no मुक्त inodes, add the iag to the
	 * ag मुक्त inode list.
	 */
	अगर (iagp->nमुक्तinos == 0) अणु
		अगर (मुक्तi >= 0)
			ciagp->inoमुक्तback = cpu_to_le32(iagno);

		iagp->inoमुक्तfwd =
		    cpu_to_le32(imap->im_agctl[agno].inoमुक्त);
		iagp->inoमुक्तback = cpu_to_le32(-1);
		imap->im_agctl[agno].inoमुक्त = iagno;
	पूर्ण

	/* initialize the extent descriptor of the extent. */
	PXDlength(&iagp->inoext[extno], imap->im_nbperiext);
	PXDaddress(&iagp->inoext[extno], blkno);

	/* initialize the working and persistent map of the extent.
	 * the working map will be initialized such that
	 * it indicates the first inode of the extent is allocated.
	 */
	iagp->wmap[extno] = cpu_to_le32(HIGHORDER);
	iagp->pmap[extno] = 0;

	/* update the मुक्त inode and मुक्त extent summary maps
	 * क्रम the extent to indicate the extent has मुक्त inodes
	 * and no दीर्घer represents a मुक्त extent.
	 */
	sword = extno >> L2EXTSPERSUM;
	mask = HIGHORDER >> (extno & (EXTSPERSUM - 1));
	iagp->extsmap[sword] |= cpu_to_le32(mask);
	iagp->inosmap[sword] &= cpu_to_le32(~mask);

	/* update the मुक्त inode and मुक्त extent counts क्रम the
	 * iag.
	 */
	le32_add_cpu(&iagp->nमुक्तinos, (INOSPEREXT - 1));
	le32_add_cpu(&iagp->nमुक्तexts, -1);

	/* update the मुक्त and backed inode counts क्रम the ag.
	 */
	imap->im_agctl[agno].numमुक्त += (INOSPEREXT - 1);
	imap->im_agctl[agno].numinos += INOSPEREXT;

	/* update the मुक्त and backed inode counts क्रम the inode map.
	 */
	atomic_add(INOSPEREXT - 1, &imap->im_numमुक्त);
	atomic_add(INOSPEREXT, &imap->im_numinos);

	/* ग_लिखो the iags.
	 */
	अगर (amp)
		ग_लिखो_metapage(amp);
	अगर (bmp)
		ग_लिखो_metapage(bmp);
	अगर (cmp)
		ग_लिखो_metapage(cmp);

	वापस (0);

      error_out:

	/* release the iags.
	 */
	अगर (amp)
		release_metapage(amp);
	अगर (bmp)
		release_metapage(bmp);
	अगर (cmp)
		release_metapage(cmp);

	वापस (rc);
पूर्ण


/*
 * NAME:	diNewIAG(imap,iagnop,agno)
 *
 * FUNCTION:	allocate a new iag क्रम an allocation group.
 *
 *		first tries to allocate the iag from the inode map
 *		iagमुक्त list:
 *		अगर the list has मुक्त iags, the head of the list is हटाओd
 *		and वापसed to satisfy the request.
 *		अगर the inode map's iag मुक्त list is empty, the inode map
 *		is extended to hold a new iag. this new iag is initialized
 *		and वापसed to satisfy the request.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	iagnop	- poपूर्णांकer to an iag number set with the number of the
 *		  newly allocated iag upon successful वापस.
 *	agno	- allocation group number.
 *	bpp	- Buffer poपूर्णांकer to be filled in with new IAG's buffer
 *
 * RETURN VALUES:
 *	0	- success.
 *	-ENOSPC	- insufficient disk resources.
 *	-EIO	- i/o error.
 *
 * serialization:
 *	AG lock held on entry/निकास;
 *	ग_लिखो lock on the map is held inside;
 *	पढ़ो lock on the map is held on successful completion;
 *
 * note: new iag transaction:
 * . synchronously ग_लिखो iag;
 * . ग_लिखो log of xtree and inode of imap;
 * . commit;
 * . synchronous ग_लिखो of xtree (right to left, bottom to top);
 * . at start of logreकरो(): init in-memory imap with one additional iag page;
 * . at end of logreकरो(): re-पढ़ो imap inode to determine
 *   new imap size;
 */
अटल पूर्णांक
diNewIAG(काष्ठा inomap * imap, पूर्णांक *iagnop, पूर्णांक agno, काष्ठा metapage ** mpp)
अणु
	पूर्णांक rc;
	पूर्णांक iagno, i, xlen;
	काष्ठा inode *ipimap;
	काष्ठा super_block *sb;
	काष्ठा jfs_sb_info *sbi;
	काष्ठा metapage *mp;
	काष्ठा iag *iagp;
	s64 xaddr = 0;
	s64 blkno;
	tid_t tid;
	काष्ठा inode *iplist[1];

	/* pick up poपूर्णांकers to the inode map and mount inodes */
	ipimap = imap->im_ipimap;
	sb = ipimap->i_sb;
	sbi = JFS_SBI(sb);

	/* acquire the मुक्त iag lock */
	IAGFREE_LOCK(imap);

	/* अगर there are any iags on the inode map मुक्त iag list,
	 * allocate the iag from the head of the list.
	 */
	अगर (imap->im_मुक्तiag >= 0) अणु
		/* pick up the iag number at the head of the list */
		iagno = imap->im_मुक्तiag;

		/* determine the logical block number of the iag */
		blkno = IAGTOLBLK(iagno, sbi->l2nbperpage);
	पूर्ण अन्यथा अणु
		/* no मुक्त iags. the inode map will have to be extented
		 * to include a new iag.
		 */

		/* acquire inode map lock */
		IWRITE_LOCK(ipimap, RDWRLOCK_IMAP);

		अगर (ipimap->i_size >> L2PSIZE != imap->im_nextiag + 1) अणु
			IWRITE_UNLOCK(ipimap);
			IAGFREE_UNLOCK(imap);
			jfs_error(imap->im_ipimap->i_sb,
				  "ipimap->i_size is wrong\n");
			वापस -EIO;
		पूर्ण


		/* get the next available iag number */
		iagno = imap->im_nextiag;

		/* make sure that we have not exceeded the maximum inode
		 * number limit.
		 */
		अगर (iagno > (MAXIAGS - 1)) अणु
			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			rc = -ENOSPC;
			जाओ out;
		पूर्ण

		/*
		 * synchronously append new iag page.
		 */
		/* determine the logical address of iag page to append */
		blkno = IAGTOLBLK(iagno, sbi->l2nbperpage);

		/* Allocate extent क्रम new iag page */
		xlen = sbi->nbperpage;
		अगर ((rc = dbAlloc(ipimap, 0, (s64) xlen, &xaddr))) अणु
			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			जाओ out;
		पूर्ण

		/*
		 * start transaction of update of the inode map
		 * addressing काष्ठाure poपूर्णांकing to the new iag page;
		 */
		tid = txBegin(sb, COMMIT_FORCE);
		mutex_lock(&JFS_IP(ipimap)->commit_mutex);

		/* update the inode map addressing काष्ठाure to poपूर्णांक to it */
		अगर ((rc =
		     xtInsert(tid, ipimap, 0, blkno, xlen, &xaddr, 0))) अणु
			txEnd(tid);
			mutex_unlock(&JFS_IP(ipimap)->commit_mutex);
			/* Free the blocks allocated क्रम the iag since it was
			 * not successfully added to the inode map
			 */
			dbFree(ipimap, xaddr, (s64) xlen);

			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			जाओ out;
		पूर्ण

		/* update the inode map's inode to reflect the extension */
		ipimap->i_size += PSIZE;
		inode_add_bytes(ipimap, PSIZE);

		/* assign a buffer क्रम the page */
		mp = get_metapage(ipimap, blkno, PSIZE, 0);
		अगर (!mp) अणु
			/*
			 * This is very unlikely since we just created the
			 * extent, but let's try to handle it correctly
			 */
			xtTruncate(tid, ipimap, ipimap->i_size - PSIZE,
				   COMMIT_PWMAP);

			txAbort(tid, 0);
			txEnd(tid);
			mutex_unlock(&JFS_IP(ipimap)->commit_mutex);

			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			rc = -EIO;
			जाओ out;
		पूर्ण
		iagp = (काष्ठा iag *) mp->data;

		/* init the iag */
		स_रखो(iagp, 0, माप(काष्ठा iag));
		iagp->iagnum = cpu_to_le32(iagno);
		iagp->inoमुक्तfwd = iagp->inoमुक्तback = cpu_to_le32(-1);
		iagp->extमुक्तfwd = iagp->extमुक्तback = cpu_to_le32(-1);
		iagp->iagमुक्त = cpu_to_le32(-1);
		iagp->nमुक्तinos = 0;
		iagp->nमुक्तexts = cpu_to_le32(EXTSPERIAG);

		/* initialize the मुक्त inode summary map (मुक्त extent
		 * summary map initialization handled by bzero).
		 */
		क्रम (i = 0; i < SMAPSZ; i++)
			iagp->inosmap[i] = cpu_to_le32(ONES);

		/*
		 * Write and sync the metapage
		 */
		flush_metapage(mp);

		/*
		 * txCommit(COMMIT_FORCE) will synchronously ग_लिखो address
		 * index pages and inode after commit in careful update order
		 * of address index pages (right to left, bottom up);
		 */
		iplist[0] = ipimap;
		rc = txCommit(tid, 1, &iplist[0], COMMIT_FORCE);

		txEnd(tid);
		mutex_unlock(&JFS_IP(ipimap)->commit_mutex);

		duplicateIXtree(sb, blkno, xlen, &xaddr);

		/* update the next available iag number */
		imap->im_nextiag += 1;

		/* Add the iag to the iag मुक्त list so we करोn't lose the iag
		 * अगर a failure happens now.
		 */
		imap->im_मुक्तiag = iagno;

		/* Until we have logreकरो working, we want the imap inode &
		 * control page to be up to date.
		 */
		diSync(ipimap);

		/* release the inode map lock */
		IWRITE_UNLOCK(ipimap);
	पूर्ण

	/* obtain पढ़ो lock on map */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);

	/* पढ़ो the iag */
	अगर ((rc = diIAGRead(imap, iagno, &mp))) अणु
		IREAD_UNLOCK(ipimap);
		rc = -EIO;
		जाओ out;
	पूर्ण
	iagp = (काष्ठा iag *) mp->data;

	/* हटाओ the iag from the iag मुक्त list */
	imap->im_मुक्तiag = le32_to_cpu(iagp->iagमुक्त);
	iagp->iagमुक्त = cpu_to_le32(-1);

	/* set the वापस iag number and buffer poपूर्णांकer */
	*iagnop = iagno;
	*mpp = mp;

      out:
	/* release the iag मुक्त lock */
	IAGFREE_UNLOCK(imap);

	वापस (rc);
पूर्ण

/*
 * NAME:	diIAGRead()
 *
 * FUNCTION:	get the buffer क्रम the specअगरied iag within a fileset
 *		or aggregate inode map.
 *
 * PARAMETERS:
 *	imap	- poपूर्णांकer to inode map control काष्ठाure.
 *	iagno	- iag number.
 *	bpp	- poपूर्णांक to buffer poपूर्णांकer to be filled in on successful
 *		  निकास.
 *
 * SERIALIZATION:
 *	must have पढ़ो lock on imap inode
 *	(When called by diExtendFS, the fileप्रणाली is quiesced, thereक्रमe
 *	 the पढ़ो lock is unnecessary.)
 *
 * RETURN VALUES:
 *	0	- success.
 *	-EIO	- i/o error.
 */
अटल पूर्णांक diIAGRead(काष्ठा inomap * imap, पूर्णांक iagno, काष्ठा metapage ** mpp)
अणु
	काष्ठा inode *ipimap = imap->im_ipimap;
	s64 blkno;

	/* compute the logical block number of the iag. */
	blkno = IAGTOLBLK(iagno, JFS_SBI(ipimap->i_sb)->l2nbperpage);

	/* पढ़ो the iag. */
	*mpp = पढ़ो_metapage(ipimap, blkno, PSIZE, 0);
	अगर (*mpp == शून्य) अणु
		वापस -EIO;
	पूर्ण

	वापस (0);
पूर्ण

/*
 * NAME:	diFindFree()
 *
 * FUNCTION:	find the first मुक्त bit in a word starting at
 *		the specअगरied bit position.
 *
 * PARAMETERS:
 *	word	- word to be examined.
 *	start	- starting bit position.
 *
 * RETURN VALUES:
 *	bit position of first मुक्त bit in the word or 32 अगर
 *	no मुक्त bits were found.
 */
अटल पूर्णांक diFindFree(u32 word, पूर्णांक start)
अणु
	पूर्णांक bitno;
	निश्चित(start < 32);
	/* scan the word क्रम the first मुक्त bit. */
	क्रम (word <<= start, bitno = start; bitno < 32;
	     bitno++, word <<= 1) अणु
		अगर ((word & HIGHORDER) == 0)
			अवरोध;
	पूर्ण
	वापस (bitno);
पूर्ण

/*
 * NAME:	diUpdatePMap()
 *
 * FUNCTION: Update the persistent map in an IAG क्रम the allocation or
 *	मुक्तing of the specअगरied inode.
 *
 * PRE CONDITIONS: Working map has alपढ़ोy been updated क्रम allocate.
 *
 * PARAMETERS:
 *	ipimap	- Incore inode map inode
 *	inum	- Number of inode to mark in permanent map
 *	is_मुक्त	- If 'true' indicates inode should be marked मुक्तd, otherwise
 *		  indicates inode should be marked allocated.
 *
 * RETURN VALUES:
 *		0 क्रम success
 */
पूर्णांक
diUpdatePMap(काष्ठा inode *ipimap,
	     अचिन्हित दीर्घ inum, bool is_मुक्त, काष्ठा tblock * tblk)
अणु
	पूर्णांक rc;
	काष्ठा iag *iagp;
	काष्ठा metapage *mp;
	पूर्णांक iagno, ino, extno, bitno;
	काष्ठा inomap *imap;
	u32 mask;
	काष्ठा jfs_log *log;
	पूर्णांक lsn, dअगरft, dअगरfp;
	अचिन्हित दीर्घ flags;

	imap = JFS_IP(ipimap)->i_imap;
	/* get the iag number containing the inode */
	iagno = INOTOIAG(inum);
	/* make sure that the iag is contained within the map */
	अगर (iagno >= imap->im_nextiag) अणु
		jfs_error(ipimap->i_sb, "the iag is outside the map\n");
		वापस -EIO;
	पूर्ण
	/* पढ़ो the iag */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);
	rc = diIAGRead(imap, iagno, &mp);
	IREAD_UNLOCK(ipimap);
	अगर (rc)
		वापस (rc);
	metapage_रुको_क्रम_io(mp);
	iagp = (काष्ठा iag *) mp->data;
	/* get the inode number and extent number of the inode within
	 * the iag and the inode number within the extent.
	 */
	ino = inum & (INOSPERIAG - 1);
	extno = ino >> L2INOSPEREXT;
	bitno = ino & (INOSPEREXT - 1);
	mask = HIGHORDER >> bitno;
	/*
	 * mark the inode मुक्त in persistent map:
	 */
	अगर (is_मुक्त) अणु
		/* The inode should have been allocated both in working
		 * map and in persistent map;
		 * the inode will be मुक्तd from working map at the release
		 * of last reference release;
		 */
		अगर (!(le32_to_cpu(iagp->wmap[extno]) & mask)) अणु
			jfs_error(ipimap->i_sb,
				  "inode %ld not marked as allocated in wmap!\n",
				  inum);
		पूर्ण
		अगर (!(le32_to_cpu(iagp->pmap[extno]) & mask)) अणु
			jfs_error(ipimap->i_sb,
				  "inode %ld not marked as allocated in pmap!\n",
				  inum);
		पूर्ण
		/* update the biपंचांगap क्रम the extent of the मुक्तd inode */
		iagp->pmap[extno] &= cpu_to_le32(~mask);
	पूर्ण
	/*
	 * mark the inode allocated in persistent map:
	 */
	अन्यथा अणु
		/* The inode should be alपढ़ोy allocated in the working map
		 * and should be मुक्त in persistent map;
		 */
		अगर (!(le32_to_cpu(iagp->wmap[extno]) & mask)) अणु
			release_metapage(mp);
			jfs_error(ipimap->i_sb,
				  "the inode is not allocated in the working map\n");
			वापस -EIO;
		पूर्ण
		अगर ((le32_to_cpu(iagp->pmap[extno]) & mask) != 0) अणु
			release_metapage(mp);
			jfs_error(ipimap->i_sb,
				  "the inode is not free in the persistent map\n");
			वापस -EIO;
		पूर्ण
		/* update the biपंचांगap क्रम the extent of the allocated inode */
		iagp->pmap[extno] |= cpu_to_le32(mask);
	पूर्ण
	/*
	 * update iag lsn
	 */
	lsn = tblk->lsn;
	log = JFS_SBI(tblk->sb)->log;
	LOGSYNC_LOCK(log, flags);
	अगर (mp->lsn != 0) अणु
		/* inherit older/smaller lsn */
		logdअगरf(dअगरft, lsn, log);
		logdअगरf(dअगरfp, mp->lsn, log);
		अगर (dअगरft < dअगरfp) अणु
			mp->lsn = lsn;
			/* move mp after tblock in logsync list */
			list_move(&mp->synclist, &tblk->synclist);
		पूर्ण
		/* inherit younger/larger clsn */
		निश्चित(mp->clsn);
		logdअगरf(dअगरft, tblk->clsn, log);
		logdअगरf(dअगरfp, mp->clsn, log);
		अगर (dअगरft > dअगरfp)
			mp->clsn = tblk->clsn;
	पूर्ण अन्यथा अणु
		mp->log = log;
		mp->lsn = lsn;
		/* insert mp after tblock in logsync list */
		log->count++;
		list_add(&mp->synclist, &tblk->synclist);
		mp->clsn = tblk->clsn;
	पूर्ण
	LOGSYNC_UNLOCK(log, flags);
	ग_लिखो_metapage(mp);
	वापस (0);
पूर्ण

/*
 *	diExtendFS()
 *
 * function: update imap क्रम extendfs();
 *
 * note: AG size has been increased s.t. each k old contiguous AGs are
 * coalesced पूर्णांकo a new AG;
 */
पूर्णांक diExtendFS(काष्ठा inode *ipimap, काष्ठा inode *ipbmap)
अणु
	पूर्णांक rc, rcx = 0;
	काष्ठा inomap *imap = JFS_IP(ipimap)->i_imap;
	काष्ठा iag *iagp = शून्य, *hiagp = शून्य;
	काष्ठा bmap *mp = JFS_SBI(ipbmap->i_sb)->bmap;
	काष्ठा metapage *bp, *hbp;
	पूर्णांक i, n, head;
	पूर्णांक numinos, xnuminos = 0, xnumमुक्त = 0;
	s64 agstart;

	jfs_info("diExtendFS: nextiag:%d numinos:%d numfree:%d",
		   imap->im_nextiag, atomic_पढ़ो(&imap->im_numinos),
		   atomic_पढ़ो(&imap->im_numमुक्त));

	/*
	 *	reस्थिरruct imap
	 *
	 * coalesce contiguous k (newAGSize/oldAGSize) AGs;
	 * i.e., (AGi, ..., AGj) where i = k*n and j = k*(n+1) - 1 to AGn;
	 * note: new AG size = old AG size * (2**x).
	 */

	/* init per AG control inक्रमmation im_agctl[] */
	क्रम (i = 0; i < MAXAG; i++) अणु
		imap->im_agctl[i].inoमुक्त = -1;
		imap->im_agctl[i].extमुक्त = -1;
		imap->im_agctl[i].numinos = 0;	/* number of backed inodes */
		imap->im_agctl[i].numमुक्त = 0;	/* number of मुक्त backed inodes */
	पूर्ण

	/*
	 *	process each iag page of the map.
	 *
	 * rebuild AG Free Inode List, AG Free Inode Extent List;
	 */
	क्रम (i = 0; i < imap->im_nextiag; i++) अणु
		अगर ((rc = diIAGRead(imap, i, &bp))) अणु
			rcx = rc;
			जारी;
		पूर्ण
		iagp = (काष्ठा iag *) bp->data;
		अगर (le32_to_cpu(iagp->iagnum) != i) अणु
			release_metapage(bp);
			jfs_error(ipimap->i_sb, "unexpected value of iagnum\n");
			वापस -EIO;
		पूर्ण

		/* leave मुक्त iag in the मुक्त iag list */
		अगर (iagp->nमुक्तexts == cpu_to_le32(EXTSPERIAG)) अणु
			release_metapage(bp);
			जारी;
		पूर्ण

		agstart = le64_to_cpu(iagp->agstart);
		n = agstart >> mp->db_agl2size;
		iagp->agstart = cpu_to_le64((s64)n << mp->db_agl2size);

		/* compute backed inodes */
		numinos = (EXTSPERIAG - le32_to_cpu(iagp->nमुक्तexts))
		    << L2INOSPEREXT;
		अगर (numinos > 0) अणु
			/* merge AG backed inodes */
			imap->im_agctl[n].numinos += numinos;
			xnuminos += numinos;
		पूर्ण

		/* अगर any backed मुक्त inodes, insert at AG मुक्त inode list */
		अगर ((पूर्णांक) le32_to_cpu(iagp->nमुक्तinos) > 0) अणु
			अगर ((head = imap->im_agctl[n].inoमुक्त) == -1) अणु
				iagp->inoमुक्तfwd = cpu_to_le32(-1);
				iagp->inoमुक्तback = cpu_to_le32(-1);
			पूर्ण अन्यथा अणु
				अगर ((rc = diIAGRead(imap, head, &hbp))) अणु
					rcx = rc;
					जाओ nextiag;
				पूर्ण
				hiagp = (काष्ठा iag *) hbp->data;
				hiagp->inoमुक्तback = iagp->iagnum;
				iagp->inoमुक्तfwd = cpu_to_le32(head);
				iagp->inoमुक्तback = cpu_to_le32(-1);
				ग_लिखो_metapage(hbp);
			पूर्ण

			imap->im_agctl[n].inoमुक्त =
			    le32_to_cpu(iagp->iagnum);

			/* merge AG backed मुक्त inodes */
			imap->im_agctl[n].numमुक्त +=
			    le32_to_cpu(iagp->nमुक्तinos);
			xnumमुक्त += le32_to_cpu(iagp->nमुक्तinos);
		पूर्ण

		/* अगर any मुक्त extents, insert at AG मुक्त extent list */
		अगर (le32_to_cpu(iagp->nमुक्तexts) > 0) अणु
			अगर ((head = imap->im_agctl[n].extमुक्त) == -1) अणु
				iagp->extमुक्तfwd = cpu_to_le32(-1);
				iagp->extमुक्तback = cpu_to_le32(-1);
			पूर्ण अन्यथा अणु
				अगर ((rc = diIAGRead(imap, head, &hbp))) अणु
					rcx = rc;
					जाओ nextiag;
				पूर्ण
				hiagp = (काष्ठा iag *) hbp->data;
				hiagp->extमुक्तback = iagp->iagnum;
				iagp->extमुक्तfwd = cpu_to_le32(head);
				iagp->extमुक्तback = cpu_to_le32(-1);
				ग_लिखो_metapage(hbp);
			पूर्ण

			imap->im_agctl[n].extमुक्त =
			    le32_to_cpu(iagp->iagnum);
		पूर्ण

	      nextiag:
		ग_लिखो_metapage(bp);
	पूर्ण

	अगर (xnuminos != atomic_पढ़ो(&imap->im_numinos) ||
	    xnumमुक्त != atomic_पढ़ो(&imap->im_numमुक्त)) अणु
		jfs_error(ipimap->i_sb, "numinos or numfree incorrect\n");
		वापस -EIO;
	पूर्ण

	वापस rcx;
पूर्ण


/*
 *	duplicateIXtree()
 *
 * serialization: IWRITE_LOCK held on entry/निकास
 *
 * note: shaकरोw page with regular inode (rel.2);
 */
अटल व्योम duplicateIXtree(काष्ठा super_block *sb, s64 blkno,
			    पूर्णांक xlen, s64 *xaddr)
अणु
	काष्ठा jfs_superblock *j_sb;
	काष्ठा buffer_head *bh;
	काष्ठा inode *ip;
	tid_t tid;

	/* अगर AIT2 ipmap2 is bad, करो not try to update it */
	अगर (JFS_SBI(sb)->mntflag & JFS_BAD_SAIT)	/* s_flag */
		वापस;
	ip = diReadSpecial(sb, खाताSYSTEM_I, 1);
	अगर (ip == शून्य) अणु
		JFS_SBI(sb)->mntflag |= JFS_BAD_SAIT;
		अगर (पढ़ोSuper(sb, &bh))
			वापस;
		j_sb = (काष्ठा jfs_superblock *)bh->b_data;
		j_sb->s_flag |= cpu_to_le32(JFS_BAD_SAIT);

		mark_buffer_dirty(bh);
		sync_dirty_buffer(bh);
		brअन्यथा(bh);
		वापस;
	पूर्ण

	/* start transaction */
	tid = txBegin(sb, COMMIT_FORCE);
	/* update the inode map addressing काष्ठाure to poपूर्णांक to it */
	अगर (xtInsert(tid, ip, 0, blkno, xlen, xaddr, 0)) अणु
		JFS_SBI(sb)->mntflag |= JFS_BAD_SAIT;
		txAbort(tid, 1);
		जाओ cleanup;

	पूर्ण
	/* update the inode map's inode to reflect the extension */
	ip->i_size += PSIZE;
	inode_add_bytes(ip, PSIZE);
	txCommit(tid, 1, &ip, COMMIT_FORCE);
      cleanup:
	txEnd(tid);
	diFreeSpecial(ip);
पूर्ण

/*
 * NAME:	copy_from_dinode()
 *
 * FUNCTION:	Copies inode info from disk inode to in-memory inode
 *
 * RETURN VALUES:
 *	0	- success
 *	-ENOMEM	- insufficient memory
 */
अटल पूर्णांक copy_from_dinode(काष्ठा dinode * dip, काष्ठा inode *ip)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);

	jfs_ip->fileset = le32_to_cpu(dip->di_fileset);
	jfs_ip->mode2 = le32_to_cpu(dip->di_mode);
	jfs_set_inode_flags(ip);

	ip->i_mode = le32_to_cpu(dip->di_mode) & 0xffff;
	अगर (sbi->umask != -1) अणु
		ip->i_mode = (ip->i_mode & ~0777) | (0777 & ~sbi->umask);
		/* For directories, add x permission अगर r is allowed by umask */
		अगर (S_ISसूची(ip->i_mode)) अणु
			अगर (ip->i_mode & 0400)
				ip->i_mode |= 0100;
			अगर (ip->i_mode & 0040)
				ip->i_mode |= 0010;
			अगर (ip->i_mode & 0004)
				ip->i_mode |= 0001;
		पूर्ण
	पूर्ण
	set_nlink(ip, le32_to_cpu(dip->di_nlink));

	jfs_ip->saved_uid = make_kuid(&init_user_ns, le32_to_cpu(dip->di_uid));
	अगर (!uid_valid(sbi->uid))
		ip->i_uid = jfs_ip->saved_uid;
	अन्यथा अणु
		ip->i_uid = sbi->uid;
	पूर्ण

	jfs_ip->saved_gid = make_kgid(&init_user_ns, le32_to_cpu(dip->di_gid));
	अगर (!gid_valid(sbi->gid))
		ip->i_gid = jfs_ip->saved_gid;
	अन्यथा अणु
		ip->i_gid = sbi->gid;
	पूर्ण

	ip->i_size = le64_to_cpu(dip->di_size);
	ip->i_aसमय.tv_sec = le32_to_cpu(dip->di_aसमय.tv_sec);
	ip->i_aसमय.tv_nsec = le32_to_cpu(dip->di_aसमय.tv_nsec);
	ip->i_mसमय.tv_sec = le32_to_cpu(dip->di_mसमय.tv_sec);
	ip->i_mसमय.tv_nsec = le32_to_cpu(dip->di_mसमय.tv_nsec);
	ip->i_स_समय.tv_sec = le32_to_cpu(dip->di_स_समय.tv_sec);
	ip->i_स_समय.tv_nsec = le32_to_cpu(dip->di_स_समय.tv_nsec);
	ip->i_blocks = LBLK2PBLK(ip->i_sb, le64_to_cpu(dip->di_nblocks));
	ip->i_generation = le32_to_cpu(dip->di_gen);

	jfs_ip->ixpxd = dip->di_ixpxd;	/* in-memory pxd's are little-endian */
	jfs_ip->acl = dip->di_acl;	/* as are dxd's */
	jfs_ip->ea = dip->di_ea;
	jfs_ip->next_index = le32_to_cpu(dip->di_next_index);
	jfs_ip->oसमय = le32_to_cpu(dip->di_oसमय.tv_sec);
	jfs_ip->acltype = le32_to_cpu(dip->di_acltype);

	अगर (S_ISCHR(ip->i_mode) || S_ISBLK(ip->i_mode)) अणु
		jfs_ip->dev = le32_to_cpu(dip->di_rdev);
		ip->i_rdev = new_decode_dev(jfs_ip->dev);
	पूर्ण

	अगर (S_ISसूची(ip->i_mode)) अणु
		स_नकल(&jfs_ip->i_dirtable, &dip->di_dirtable, 384);
	पूर्ण अन्यथा अगर (S_ISREG(ip->i_mode) || S_ISLNK(ip->i_mode)) अणु
		स_नकल(&jfs_ip->i_xtroot, &dip->di_xtroot, 288);
	पूर्ण अन्यथा
		स_नकल(&jfs_ip->i_अंतरभूत_ea, &dip->di_अंतरभूतea, 128);

	/* Zero the in-memory-only stuff */
	jfs_ip->cflag = 0;
	jfs_ip->btindex = 0;
	jfs_ip->btorder = 0;
	jfs_ip->bxflag = 0;
	jfs_ip->blid = 0;
	jfs_ip->atlhead = 0;
	jfs_ip->atltail = 0;
	jfs_ip->xtlid = 0;
	वापस (0);
पूर्ण

/*
 * NAME:	copy_to_dinode()
 *
 * FUNCTION:	Copies inode info from in-memory inode to disk inode
 */
अटल व्योम copy_to_dinode(काष्ठा dinode * dip, काष्ठा inode *ip)
अणु
	काष्ठा jfs_inode_info *jfs_ip = JFS_IP(ip);
	काष्ठा jfs_sb_info *sbi = JFS_SBI(ip->i_sb);

	dip->di_fileset = cpu_to_le32(jfs_ip->fileset);
	dip->di_inostamp = cpu_to_le32(sbi->inostamp);
	dip->di_number = cpu_to_le32(ip->i_ino);
	dip->di_gen = cpu_to_le32(ip->i_generation);
	dip->di_size = cpu_to_le64(ip->i_size);
	dip->di_nblocks = cpu_to_le64(PBLK2LBLK(ip->i_sb, ip->i_blocks));
	dip->di_nlink = cpu_to_le32(ip->i_nlink);
	अगर (!uid_valid(sbi->uid))
		dip->di_uid = cpu_to_le32(i_uid_पढ़ो(ip));
	अन्यथा
		dip->di_uid =cpu_to_le32(from_kuid(&init_user_ns,
						   jfs_ip->saved_uid));
	अगर (!gid_valid(sbi->gid))
		dip->di_gid = cpu_to_le32(i_gid_पढ़ो(ip));
	अन्यथा
		dip->di_gid = cpu_to_le32(from_kgid(&init_user_ns,
						    jfs_ip->saved_gid));
	/*
	 * mode2 is only needed क्रम storing the higher order bits.
	 * Trust i_mode क्रम the lower order ones
	 */
	अगर (sbi->umask == -1)
		dip->di_mode = cpu_to_le32((jfs_ip->mode2 & 0xffff0000) |
					   ip->i_mode);
	अन्यथा /* Leave the original permissions alone */
		dip->di_mode = cpu_to_le32(jfs_ip->mode2);

	dip->di_aसमय.tv_sec = cpu_to_le32(ip->i_aसमय.tv_sec);
	dip->di_aसमय.tv_nsec = cpu_to_le32(ip->i_aसमय.tv_nsec);
	dip->di_स_समय.tv_sec = cpu_to_le32(ip->i_स_समय.tv_sec);
	dip->di_स_समय.tv_nsec = cpu_to_le32(ip->i_स_समय.tv_nsec);
	dip->di_mसमय.tv_sec = cpu_to_le32(ip->i_mसमय.tv_sec);
	dip->di_mसमय.tv_nsec = cpu_to_le32(ip->i_mसमय.tv_nsec);
	dip->di_ixpxd = jfs_ip->ixpxd;	/* in-memory pxd's are little-endian */
	dip->di_acl = jfs_ip->acl;	/* as are dxd's */
	dip->di_ea = jfs_ip->ea;
	dip->di_next_index = cpu_to_le32(jfs_ip->next_index);
	dip->di_oसमय.tv_sec = cpu_to_le32(jfs_ip->oसमय);
	dip->di_oसमय.tv_nsec = 0;
	dip->di_acltype = cpu_to_le32(jfs_ip->acltype);
	अगर (S_ISCHR(ip->i_mode) || S_ISBLK(ip->i_mode))
		dip->di_rdev = cpu_to_le32(jfs_ip->dev);
पूर्ण
