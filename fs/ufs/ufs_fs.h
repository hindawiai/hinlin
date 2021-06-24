<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/ufs_fs.h
 *
 * Copyright (C) 1996
 * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)
 * Laboratory क्रम Computer Science Research Computing Facility
 * Rutgers, The State University of New Jersey
 *
 * Clean swab support by Fare <fare@tunes.org>
 * just hope no one is using NNUUXXI on __?64 काष्ठाure elements
 * 64-bit clean thanks to Maciej W. Rozycki <macro@ds2.pg.gda.pl>
 *
 * 4.4BSD (FreeBSD) support added on February 1st 1998 by
 * Niels Kristian Bech Jensen <nkbj@image.dk> partially based
 * on code by Martin von Loewis <martin@mira.isdn.cs.tu-berlin.de>.
 *
 * NeXTstep support added on February 5th 1998 by
 * Niels Kristian Bech Jensen <nkbj@image.dk>.
 *
 * Write support by Daniel Pirkl <daniel.pirkl@email.cz>
 *
 * HP/UX hfs fileप्रणाली support added by
 * Martin K. Petersen <mkp@mkp.net>, August 1999
 *
 * UFS2 (of FreeBSD 5.x) support added by
 * Niraj Kumar <niraj17@iitbombay.org>  , Jan 2004
 *
 */

#अगर_अघोषित __LINUX_UFS_FS_H
#घोषणा __LINUX_UFS_FS_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fs.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/भाग64.h>
प्रकार __u64 __bitwise __fs64;
प्रकार __u32 __bitwise __fs32;
प्रकार __u16 __bitwise __fs16;

#घोषणा UFS_BBLOCK 0
#घोषणा UFS_BBSIZE 8192
#घोषणा UFS_SBLOCK 8192
#घोषणा UFS_SBSIZE 8192

#घोषणा UFS_SECTOR_SIZE 512
#घोषणा UFS_SECTOR_BITS 9
#घोषणा UFS_MAGIC  0x00011954
#घोषणा UFS_MAGIC_BW 0x0f242697
#घोषणा UFS2_MAGIC 0x19540119
#घोषणा UFS_CIGAM  0x54190100 /* byteswapped MAGIC */

/* Copied from FreeBSD */
/*
 * Each disk drive contains some number of fileप्रणालीs.
 * A fileप्रणाली consists of a number of cylinder groups.
 * Each cylinder group has inodes and data.
 *
 * A fileप्रणाली is described by its super-block, which in turn
 * describes the cylinder groups.  The super-block is critical
 * data and is replicated in each cylinder group to protect against
 * catastrophic loss.  This is करोne at `newfs' समय and the critical
 * super-block data करोes not change, so the copies need not be
 * referenced further unless disaster strikes.
 *
 * For fileप्रणाली fs, the offsets of the various blocks of पूर्णांकerest
 * are given in the super block as:
 *      [fs->fs_sblkno]         Super-block
 *      [fs->fs_cblkno]         Cylinder group block
 *      [fs->fs_iblkno]         Inode blocks
 *      [fs->fs_dblkno]         Data blocks
 * The beginning of cylinder group cg in fs, is given by
 * the ``cgbase(fs, cg)'' macro.
 *
 * Depending on the architecture and the media, the superblock may
 * reside in any one of four places. For tiny media where every block
 * counts, it is placed at the very front of the partition. Historically,
 * UFS1 placed it 8K from the front to leave room क्रम the disk label and
 * a small bootstrap. For UFS2 it got moved to 64K from the front to leave
 * room क्रम the disk label and a bigger bootstrap, and क्रम really piggy
 * प्रणालीs we check at 256K from the front अगर the first three fail. In
 * all हालs the size of the superblock will be SBLOCKSIZE. All values are
 * given in byte-offset क्रमm, so they करो not imply a sector size. The
 * SBLOCKSEARCH specअगरies the order in which the locations should be searched.
 */
#घोषणा SBLOCK_FLOPPY        0
#घोषणा SBLOCK_UFS1       8192
#घोषणा SBLOCK_UFS2      65536
#घोषणा SBLOCK_PIGGY    262144
#घोषणा SBLOCKSIZE        8192
#घोषणा SBLOCKSEARCH \
        अणु SBLOCK_UFS2, SBLOCK_UFS1, SBLOCK_FLOPPY, SBLOCK_PIGGY, -1 पूर्ण


/* HP specअगरic MAGIC values */

#घोषणा UFS_MAGIC_LFN   0x00095014 /* fs supports filenames > 14 अक्षरs */
#घोषणा UFS_CIGAM_LFN   0x14500900 /* srahc 41 < semanelअगर stroppus sf */

#घोषणा UFS_MAGIC_SEC   0x00612195 /* B1 security fs */
#घोषणा UFS_CIGAM_SEC   0x95216100

#घोषणा UFS_MAGIC_FEA   0x00195612 /* fs_featurebits supported */
#घोषणा UFS_CIGAM_FEA   0x12561900

#घोषणा UFS_MAGIC_4GB   0x05231994 /* fs > 4 GB && fs_featurebits */
#घोषणा UFS_CIGAM_4GB   0x94192305

/* Seems somebody at HP goofed here. B1 and lfs are both 0x2 !?! */
#घोषणा UFS_FSF_LFN     0x00000001 /* दीर्घ file names */
#घोषणा UFS_FSF_B1      0x00000002 /* B1 security */
#घोषणा UFS_FSF_LFS     0x00000002 /* large files */
#घोषणा UFS_FSF_LUID    0x00000004 /* large UIDs */

/* End of HP stuff */


#घोषणा UFS_BSIZE	8192
#घोषणा UFS_MINBSIZE	4096
#घोषणा UFS_FSIZE	1024
#घोषणा UFS_MAXFRAG	(UFS_BSIZE / UFS_FSIZE)

#घोषणा UFS_NDADDR 12
#घोषणा UFS_NINसूची 3

#घोषणा UFS_IND_BLOCK	(UFS_NDADDR + 0)
#घोषणा UFS_DIND_BLOCK	(UFS_NDADDR + 1)
#घोषणा UFS_TIND_BLOCK	(UFS_NDADDR + 2)

#घोषणा UFS_Nसूची_FRAGMENT (UFS_NDADDR << uspi->s_fpbshअगरt)
#घोषणा UFS_IND_FRAGMENT (UFS_IND_BLOCK << uspi->s_fpbshअगरt)
#घोषणा UFS_DIND_FRAGMENT (UFS_DIND_BLOCK << uspi->s_fpbshअगरt)
#घोषणा UFS_TIND_FRAGMENT (UFS_TIND_BLOCK << uspi->s_fpbshअगरt)

#घोषणा UFS_ROOTINO 2
#घोषणा UFS_FIRST_INO (UFS_ROOTINO + 1)

#घोषणा UFS_USEEFT  ((__u16)65535)

/* fs_clean values */
#घोषणा UFS_FSOK      0x7c269d38
#घोषणा UFS_FSACTIVE  ((__s8)0x00)
#घोषणा UFS_FSCLEAN   ((__s8)0x01)
#घोषणा UFS_FSSTABLE  ((__s8)0x02)
#घोषणा UFS_FSOSF1    ((__s8)0x03)	/* is this correct क्रम DEC OSF/1? */
#घोषणा UFS_FSBAD     ((__s8)0xff)

/* Solaris-specअगरic fs_clean values */
#घोषणा UFS_FSSUSPEND ((__s8)0xfe)	/* temporarily suspended */
#घोषणा UFS_FSLOG     ((__s8)0xfd)	/* logging fs */
#घोषणा UFS_FSFIX     ((__s8)0xfc)	/* being repaired जबतक mounted */

/* From here to next blank line, s_flags क्रम ufs_sb_info */
/* directory entry encoding */
#घोषणा UFS_DE_MASK		0x00000010	/* mask क्रम the following */
#घोषणा UFS_DE_OLD		0x00000000
#घोषणा UFS_DE_44BSD		0x00000010
/* uid encoding */
#घोषणा UFS_UID_MASK		0x00000060	/* mask क्रम the following */
#घोषणा UFS_UID_OLD		0x00000000
#घोषणा UFS_UID_44BSD		0x00000020
#घोषणा UFS_UID_EFT		0x00000040
/* superblock state encoding */
#घोषणा UFS_ST_MASK		0x00000700	/* mask क्रम the following */
#घोषणा UFS_ST_OLD		0x00000000
#घोषणा UFS_ST_44BSD		0x00000100
#घोषणा UFS_ST_SUN		0x00000200 /* Solaris */
#घोषणा UFS_ST_SUNOS		0x00000300
#घोषणा UFS_ST_SUNx86		0x00000400 /* Solaris x86 */
/*cylinder group encoding */
#घोषणा UFS_CG_MASK		0x00003000	/* mask क्रम the following */
#घोषणा UFS_CG_OLD		0x00000000
#घोषणा UFS_CG_44BSD		0x00002000
#घोषणा UFS_CG_SUN		0x00001000
/* fileप्रणाली type encoding */
#घोषणा UFS_TYPE_MASK		0x00010000	/* mask क्रम the following */
#घोषणा UFS_TYPE_UFS1		0x00000000
#घोषणा UFS_TYPE_UFS2		0x00010000


/* fs_inodefmt options */
#घोषणा UFS_42INODEFMT	-1
#घोषणा UFS_44INODEFMT	2

/*
 * MINFREE gives the minimum acceptable percentage of file प्रणाली
 * blocks which may be मुक्त. If the मुक्तlist drops below this level
 * only the superuser may जारी to allocate blocks. This may
 * be set to 0 अगर no reserve of मुक्त blocks is deemed necessary,
 * however throughput drops by fअगरty percent अगर the file प्रणाली
 * is run at between 95% and 100% full; thus the minimum शेष
 * value of fs_minमुक्त is 5%. However, to get good clustering
 * perक्रमmance, 10% is a better choice. hence we use 10% as our
 * शेष value. With 10% मुक्त space, fragmentation is not a
 * problem, so we choose to optimize क्रम समय.
 */
#घोषणा UFS_MINFREE         5
#घोषणा UFS_DEFAULTOPT      UFS_OPTTIME

/*
 * Turn file प्रणाली block numbers पूर्णांकo disk block addresses.
 * This maps file प्रणाली blocks to device size blocks.
 */
#घोषणा ufs_fsbtodb(uspi, b)	((b) << (uspi)->s_fsbtodb)
#घोषणा	ufs_dbtofsb(uspi, b)	((b) >> (uspi)->s_fsbtodb)

/*
 * Cylinder group macros to locate things in cylinder groups.
 * They calc file प्रणाली addresses of cylinder group data काष्ठाures.
 */
#घोषणा	ufs_cgbase(c)	(uspi->s_fpg * (c))
#घोषणा ufs_cgstart(c)	((uspi)->fs_magic == UFS2_MAGIC ?  ufs_cgbase(c) : \
	(ufs_cgbase(c)  + uspi->s_cgoffset * ((c) & ~uspi->s_cgmask)))
#घोषणा	ufs_cgsblock(c)	(ufs_cgstart(c) + uspi->s_sblkno)	/* super blk */
#घोषणा	ufs_cgcmin(c)	(ufs_cgstart(c) + uspi->s_cblkno)	/* cg block */
#घोषणा	ufs_cgimin(c)	(ufs_cgstart(c) + uspi->s_iblkno)	/* inode blk */
#घोषणा	ufs_cgdmin(c)	(ufs_cgstart(c) + uspi->s_dblkno)	/* 1st data */

/*
 * Macros क्रम handling inode numbers:
 *     inode number to file प्रणाली block offset.
 *     inode number to cylinder group number.
 *     inode number to file प्रणाली block address.
 */
#घोषणा	ufs_inotocg(x)		((x) / uspi->s_ipg)
#घोषणा	ufs_inotocgoff(x)	((x) % uspi->s_ipg)
#घोषणा	ufs_inotofsba(x)	(((u64)ufs_cgimin(ufs_inotocg(x))) + ufs_inotocgoff(x) / uspi->s_inopf)
#घोषणा	ufs_inotofsbo(x)	((x) % uspi->s_inopf)

/*
 * Compute the cylinder and rotational position of a cyl block addr.
 */
#घोषणा ufs_cbtocylno(bno) \
	((bno) * uspi->s_nspf / uspi->s_spc)
#घोषणा ufs_cbtorpos(bno)				      \
	((UFS_SB(sb)->s_flags & UFS_CG_SUN) ?		      \
	 (((((bno) * uspi->s_nspf % uspi->s_spc) %	      \
	    uspi->s_nsect) *				      \
	   uspi->s_nrpos) / uspi->s_nsect)		      \
	 :						      \
	((((bno) * uspi->s_nspf % uspi->s_spc / uspi->s_nsect \
	* uspi->s_trackskew + (bno) * uspi->s_nspf % uspi->s_spc \
	% uspi->s_nsect * uspi->s_पूर्णांकerleave) % uspi->s_nsect \
	  * uspi->s_nrpos) / uspi->s_npsect))

/*
 * The following macros optimize certain frequently calculated
 * quantities by using shअगरts and masks in place of भागisions
 * modulos and multiplications.
 */
#घोषणा ufs_blkoff(loc)		((loc) & uspi->s_qbmask)
#घोषणा ufs_fragoff(loc)	((loc) & uspi->s_qfmask)
#घोषणा ufs_lblktosize(blk)	((blk) << uspi->s_bshअगरt)
#घोषणा ufs_lblkno(loc)		((loc) >> uspi->s_bshअगरt)
#घोषणा ufs_numfrags(loc)	((loc) >> uspi->s_fshअगरt)
#घोषणा ufs_blkroundup(size)	(((size) + uspi->s_qbmask) & uspi->s_bmask)
#घोषणा ufs_fragroundup(size)	(((size) + uspi->s_qfmask) & uspi->s_fmask)
#घोषणा ufs_fragstoblks(frags)	((frags) >> uspi->s_fpbshअगरt)
#घोषणा ufs_blkstofrags(blks)	((blks) << uspi->s_fpbshअगरt)
#घोषणा ufs_fragnum(fsb)	((fsb) & uspi->s_fpbmask)
#घोषणा ufs_blknum(fsb)		((fsb) & ~uspi->s_fpbmask)

#घोषणा	UFS_MAXNAMLEN 255
#घोषणा UFS_MAXMNTLEN 512
#घोषणा UFS2_MAXMNTLEN 468
#घोषणा UFS2_MAXVOLLEN 32
#घोषणा UFS_MAXCSBUFS 31
#घोषणा UFS_LINK_MAX 32000
/*
#घोषणा	UFS2_NOCSPTRS	((128 / माप(व्योम *)) - 4)
*/
#घोषणा	UFS2_NOCSPTRS	28

/*
 * UFS_सूची_PAD defines the directory entries boundaries
 * (must be a multiple of 4)
 */
#घोषणा UFS_सूची_PAD			4
#घोषणा UFS_सूची_ROUND			(UFS_सूची_PAD - 1)
#घोषणा UFS_सूची_REC_LEN(name_len)	(((name_len) + 1 + 8 + UFS_सूची_ROUND) & ~UFS_सूची_ROUND)

काष्ठा ufs_समयval अणु
	__fs32	tv_sec;
	__fs32	tv_usec;
पूर्ण;

काष्ठा ufs_dir_entry अणु
	__fs32  d_ino;			/* inode number of this entry */
	__fs16  d_reclen;		/* length of this entry */
	जोड़ अणु
		__fs16	d_namlen;		/* actual length of d_name */
		काष्ठा अणु
			__u8	d_type;		/* file type */
			__u8	d_namlen;	/* length of string in d_name */
		पूर्ण d_44;
	पूर्ण d_u;
	__u8	d_name[UFS_MAXNAMLEN + 1];	/* file name */
पूर्ण;

काष्ठा ufs_csum अणु
	__fs32	cs_ndir;	/* number of directories */
	__fs32	cs_nbमुक्त;	/* number of मुक्त blocks */
	__fs32	cs_nअगरree;	/* number of मुक्त inodes */
	__fs32	cs_nfमुक्त;	/* number of मुक्त frags */
पूर्ण;
काष्ठा ufs2_csum_total अणु
	__fs64	cs_ndir;	/* number of directories */
	__fs64	cs_nbमुक्त;	/* number of मुक्त blocks */
	__fs64	cs_nअगरree;	/* number of मुक्त inodes */
	__fs64	cs_nfमुक्त;	/* number of मुक्त frags */
	__fs64   cs_numclusters;	/* number of मुक्त clusters */
	__fs64   cs_spare[3];	/* future expansion */
पूर्ण;

काष्ठा ufs_csum_core अणु
	__u64	cs_ndir;	/* number of directories */
	__u64	cs_nbमुक्त;	/* number of मुक्त blocks */
	__u64	cs_nअगरree;	/* number of मुक्त inodes */
	__u64	cs_nfमुक्त;	/* number of मुक्त frags */
	__u64   cs_numclusters;	/* number of मुक्त clusters */
पूर्ण;

/*
 * File प्रणाली flags
 */
#घोषणा UFS_UNCLEAN      0x01    /* file प्रणाली not clean at mount (unused) */
#घोषणा UFS_DOSOFTDEP    0x02    /* file प्रणाली using soft dependencies */
#घोषणा UFS_NEEDSFSCK    0x04    /* needs sync fsck (FreeBSD compat, unused) */
#घोषणा UFS_INDEXसूचीS    0x08    /* kernel supports indexed directories */
#घोषणा UFS_ACLS         0x10    /* file प्रणाली has ACLs enabled */
#घोषणा UFS_MULTILABEL   0x20    /* file प्रणाली is MAC multi-label */
#घोषणा UFS_FLAGS_UPDATED 0x80   /* flags have been moved to new location */

#अगर 0
/*
 * This is the actual superblock, as it is laid out on the disk.
 * Do NOT use this काष्ठाure, because of माप(ufs_super_block) > 512 and
 * it may occupy several blocks, use
 * काष्ठा ufs_super_block_(first,second,third) instead.
 */
काष्ठा ufs_super_block अणु
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_link;	/* UNUSED */
		पूर्ण fs_42;
		काष्ठा अणु
			__fs32	fs_state;	/* file प्रणाली state flag */
		पूर्ण fs_sun;
	पूर्ण fs_u0;
	__fs32	fs_rlink;	/* UNUSED */
	__fs32	fs_sblkno;	/* addr of super-block in filesys */
	__fs32	fs_cblkno;	/* offset of cyl-block in filesys */
	__fs32	fs_iblkno;	/* offset of inode-blocks in filesys */
	__fs32	fs_dblkno;	/* offset of first data after cg */
	__fs32	fs_cgoffset;	/* cylinder group offset in cylinder */
	__fs32	fs_cgmask;	/* used to calc mod fs_ntrak */
	__fs32	fs_समय;	/* last समय written -- समय_प्रकार */
	__fs32	fs_size;	/* number of blocks in fs */
	__fs32	fs_dsize;	/* number of data blocks in fs */
	__fs32	fs_ncg;		/* number of cylinder groups */
	__fs32	fs_bsize;	/* size of basic blocks in fs */
	__fs32	fs_fsize;	/* size of frag blocks in fs */
	__fs32	fs_frag;	/* number of frags in a block in fs */
/* these are configuration parameters */
	__fs32	fs_minमुक्त;	/* minimum percentage of मुक्त blocks */
	__fs32	fs_rotdelay;	/* num of ms क्रम optimal next block */
	__fs32	fs_rps;		/* disk revolutions per second */
/* these fields can be computed from the others */
	__fs32	fs_bmask;	/* ``blkoff'' calc of blk offsets */
	__fs32	fs_fmask;	/* ``fragoff'' calc of frag offsets */
	__fs32	fs_bshअगरt;	/* ``lblkno'' calc of logical blkno */
	__fs32	fs_fshअगरt;	/* ``numfrags'' calc number of frags */
/* these are configuration parameters */
	__fs32	fs_maxcontig;	/* max number of contiguous blks */
	__fs32	fs_maxbpg;	/* max number of blks per cyl group */
/* these fields can be computed from the others */
	__fs32	fs_fragshअगरt;	/* block to frag shअगरt */
	__fs32	fs_fsbtodb;	/* fsbtodb and dbtofsb shअगरt स्थिरant */
	__fs32	fs_sbsize;	/* actual size of super block */
	__fs32	fs_csmask;	/* csum block offset */
	__fs32	fs_csshअगरt;	/* csum block number */
	__fs32	fs_nindir;	/* value of NINसूची */
	__fs32	fs_inopb;	/* value of INOPB */
	__fs32	fs_nspf;	/* value of NSPF */
/* yet another configuration parameter */
	__fs32	fs_optim;	/* optimization preference, see below */
/* these fields are derived from the hardware */
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_npsect;	/* # sectors/track including spares */
		पूर्ण fs_sun;
		काष्ठा अणु
			__fs32	fs_state;	/* file प्रणाली state समय stamp */
		पूर्ण fs_sunx86;
	पूर्ण fs_u1;
	__fs32	fs_पूर्णांकerleave;	/* hardware sector पूर्णांकerleave */
	__fs32	fs_trackskew;	/* sector 0 skew, per track */
/* a unique id क्रम this fileप्रणाली (currently unused and unमुख्यtained) */
/* In 4.3 Tahoe this space is used by fs_headचयन and fs_trkseek */
/* Neither of those fields is used in the Tahoe code right now but */
/* there could be problems अगर they are.                            */
	__fs32	fs_id[2];	/* file प्रणाली id */
/* sizes determined by number of cylinder groups and their sizes */
	__fs32	fs_csaddr;	/* blk addr of cyl grp summary area */
	__fs32	fs_cssize;	/* size of cyl grp summary area */
	__fs32	fs_cgsize;	/* cylinder group size */
/* these fields are derived from the hardware */
	__fs32	fs_ntrak;	/* tracks per cylinder */
	__fs32	fs_nsect;	/* sectors per track */
	__fs32	fs_spc;		/* sectors per cylinder */
/* this comes from the disk driver partitioning */
	__fs32	fs_ncyl;	/* cylinders in file प्रणाली */
/* these fields can be computed from the others */
	__fs32	fs_cpg;		/* cylinders per group */
	__fs32	fs_ipg;		/* inodes per cylinder group */
	__fs32	fs_fpg;		/* blocks per group * fs_frag */
/* this data must be re-computed after crashes */
	काष्ठा ufs_csum fs_cstotal;	/* cylinder summary inक्रमmation */
/* these fields are cleared at mount समय */
	__s8	fs_भ_शेष;	/* super block modअगरied flag */
	__s8	fs_clean;	/* file प्रणाली is clean flag */
	__s8	fs_ronly;	/* mounted पढ़ो-only flag */
	__s8	fs_flags;
	जोड़ अणु
		काष्ठा अणु
			__s8	fs_fsmnt[UFS_MAXMNTLEN];/* name mounted on */
			__fs32	fs_cgrotor;	/* last cg searched */
			__fs32	fs_csp[UFS_MAXCSBUFS];/*list of fs_cs info buffers */
			__fs32	fs_maxcluster;
			__fs32	fs_cpc;		/* cyl per cycle in postbl */
			__fs16	fs_opostbl[16][8]; /* old rotation block list head */
		पूर्ण fs_u1;
		काष्ठा अणु
			__s8  fs_fsmnt[UFS2_MAXMNTLEN];	/* name mounted on */
			__u8   fs_volname[UFS2_MAXVOLLEN]; /* volume name */
			__fs64  fs_swuid;		/* प्रणाली-wide uid */
			__fs32  fs_pad;	/* due to alignment of fs_swuid */
			__fs32   fs_cgrotor;     /* last cg searched */
			__fs32   fs_ocsp[UFS2_NOCSPTRS]; /*list of fs_cs info buffers */
			__fs32   fs_contigdirs;/*# of contiguously allocated dirs */
			__fs32   fs_csp;	/* cg summary info buffer क्रम fs_cs */
			__fs32   fs_maxcluster;
			__fs32   fs_active;/* used by snapshots to track fs */
			__fs32   fs_old_cpc;	/* cyl per cycle in postbl */
			__fs32   fs_maxbsize;/*maximum blocking factor permitted */
			__fs64   fs_sparecon64[17];/*old rotation block list head */
			__fs64   fs_sblockloc; /* byte offset of standard superblock */
			काष्ठा  ufs2_csum_total fs_cstotal;/*cylinder summary inक्रमmation*/
			काष्ठा  ufs_समयval    fs_समय;		/* last समय written */
			__fs64    fs_size;		/* number of blocks in fs */
			__fs64    fs_dsize;	/* number of data blocks in fs */
			__fs64   fs_csaddr;	/* blk addr of cyl grp summary area */
			__fs64    fs_pendingblocks;/* blocks in process of being मुक्तd */
			__fs32    fs_pendinginodes;/*inodes in process of being मुक्तd */
		पूर्ण fs_u2;
	पूर्ण  fs_u11;
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_sparecon[53];/* reserved क्रम future स्थिरants */
			__fs32	fs_reclaim;
			__fs32	fs_sparecon2[1];
			__fs32	fs_state;	/* file प्रणाली state समय stamp */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		पूर्ण fs_sun;
		काष्ठा अणु
			__fs32	fs_sparecon[53];/* reserved क्रम future स्थिरants */
			__fs32	fs_reclaim;
			__fs32	fs_sparecon2[1];
			__fs32	fs_npsect;	/* # sectors/track including spares */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		पूर्ण fs_sunx86;
		काष्ठा अणु
			__fs32	fs_sparecon[50];/* reserved क्रम future स्थिरants */
			__fs32	fs_contigsumsize;/* size of cluster summary array */
			__fs32	fs_maxsymlinklen;/* max length of an पूर्णांकernal symlink */
			__fs32	fs_inodefmt;	/* क्रमmat of on-disk inodes */
			__fs32	fs_maxfilesize[2];	/* max representable file size */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
			__fs32	fs_state;	/* file प्रणाली state समय stamp */
		पूर्ण fs_44;
	पूर्ण fs_u2;
	__fs32	fs_postblक्रमmat;	/* क्रमmat of positional layout tables */
	__fs32	fs_nrpos;		/* number of rotational positions */
	__fs32	fs_postbloff;		/* (__s16) rotation block list head */
	__fs32	fs_rotbloff;		/* (__u8) blocks क्रम each rotation */
	__fs32	fs_magic;		/* magic number */
	__u8	fs_space[1];		/* list of blocks क्रम each rotation */
पूर्ण;
#पूर्ण_अगर/*काष्ठा ufs_super_block*/

/*
 * Preference क्रम optimization.
 */
#घोषणा UFS_OPTTIME	0	/* minimize allocation समय */
#घोषणा UFS_OPTSPACE	1	/* minimize disk fragmentation */

/*
 * Rotational layout table क्रमmat types
 */
#घोषणा UFS_42POSTBLFMT		-1	/* 4.2BSD rotational table क्रमmat */
#घोषणा UFS_DYNAMICPOSTBLFMT	1	/* dynamic rotational table क्रमmat */

/*
 * Convert cylinder group to base address of its global summary info.
 */
#घोषणा fs_cs(indx) s_csp[(indx)]

/*
 * Cylinder group block क्रम a file प्रणाली.
 *
 * Writable fields in the cylinder group are रक्षित by the associated
 * super block lock fs->fs_lock.
 */
#घोषणा	CG_MAGIC	0x090255
#घोषणा ufs_cg_chkmagic(sb, ucg) \
	(fs32_to_cpu((sb), (ucg)->cg_magic) == CG_MAGIC)
/*
 * Macros क्रम access to old cylinder group array काष्ठाures
 */
#घोषणा ufs_ocg_blktot(sb, ucg)      fs32_to_cpu((sb), ((काष्ठा ufs_old_cylinder_group *)(ucg))->cg_btot)
#घोषणा ufs_ocg_blks(sb, ucg, cylno) fs32_to_cpu((sb), ((काष्ठा ufs_old_cylinder_group *)(ucg))->cg_b[cylno])
#घोषणा ufs_ocg_inosused(sb, ucg)    fs32_to_cpu((sb), ((काष्ठा ufs_old_cylinder_group *)(ucg))->cg_iused)
#घोषणा ufs_ocg_blksमुक्त(sb, ucg)    fs32_to_cpu((sb), ((काष्ठा ufs_old_cylinder_group *)(ucg))->cg_मुक्त)
#घोषणा ufs_ocg_chkmagic(sb, ucg) \
	(fs32_to_cpu((sb), ((काष्ठा ufs_old_cylinder_group *)(ucg))->cg_magic) == CG_MAGIC)

/*
 * size of this काष्ठाure is 172 B
 */
काष्ठा	ufs_cylinder_group अणु
	__fs32	cg_link;		/* linked list of cyl groups */
	__fs32	cg_magic;		/* magic number */
	__fs32	cg_समय;		/* समय last written */
	__fs32	cg_cgx;			/* we are the cgx'th cylinder group */
	__fs16	cg_ncyl;		/* number of cyl's this cg */
	__fs16	cg_niblk;		/* number of inode blocks this cg */
	__fs32	cg_ndblk;		/* number of data blocks this cg */
	काष्ठा	ufs_csum cg_cs;		/* cylinder summary inक्रमmation */
	__fs32	cg_rotor;		/* position of last used block */
	__fs32	cg_frotor;		/* position of last used frag */
	__fs32	cg_irotor;		/* position of last used inode */
	__fs32	cg_frsum[UFS_MAXFRAG];	/* counts of available frags */
	__fs32	cg_btotoff;		/* (__u32) block totals per cylinder */
	__fs32	cg_boff;		/* (लघु) मुक्त block positions */
	__fs32	cg_iuseकरोff;		/* (अक्षर) used inode map */
	__fs32	cg_मुक्तoff;		/* (u_अक्षर) मुक्त block map */
	__fs32	cg_nextमुक्तoff;		/* (u_अक्षर) next available space */
	जोड़ अणु
		काष्ठा अणु
			__fs32	cg_clustersumoff;	/* (u_पूर्णांक32) counts of avail clusters */
			__fs32	cg_clusteroff;		/* (u_पूर्णांक8) मुक्त cluster map */
			__fs32	cg_nclusterblks;	/* number of clusters this cg */
			__fs32	cg_sparecon[13];	/* reserved क्रम future use */
		पूर्ण cg_44;
		काष्ठा अणु
			__fs32	cg_clustersumoff;/* (u_पूर्णांक32) counts of avail clusters */
			__fs32	cg_clusteroff;	/* (u_पूर्णांक8) मुक्त cluster map */
			__fs32	cg_nclusterblks;/* number of clusters this cg */
			__fs32   cg_niblk; /* number of inode blocks this cg */
			__fs32   cg_initediblk;	/* last initialized inode */
			__fs32   cg_sparecon32[3];/* reserved क्रम future use */
			__fs64   cg_समय;	/* समय last written */
			__fs64	cg_sparecon[3];	/* reserved क्रम future use */
		पूर्ण cg_u2;
		__fs32	cg_sparecon[16];	/* reserved क्रम future use */
	पूर्ण cg_u;
	__u8	cg_space[1];		/* space क्रम cylinder group maps */
/* actually दीर्घer */
पूर्ण;

/* Historic Cylinder group info */
काष्ठा ufs_old_cylinder_group अणु
	__fs32	cg_link;		/* linked list of cyl groups */
	__fs32	cg_rlink;		/* क्रम incore cyl groups     */
	__fs32	cg_समय;		/* समय last written */
	__fs32	cg_cgx;			/* we are the cgx'th cylinder group */
	__fs16	cg_ncyl;		/* number of cyl's this cg */
	__fs16	cg_niblk;		/* number of inode blocks this cg */
	__fs32	cg_ndblk;		/* number of data blocks this cg */
	काष्ठा	ufs_csum cg_cs;		/* cylinder summary inक्रमmation */
	__fs32	cg_rotor;		/* position of last used block */
	__fs32	cg_frotor;		/* position of last used frag */
	__fs32	cg_irotor;		/* position of last used inode */
	__fs32	cg_frsum[8];		/* counts of available frags */
	__fs32	cg_btot[32];		/* block totals per cylinder */
	__fs16	cg_b[32][8];		/* positions of मुक्त blocks */
	__u8	cg_iused[256];		/* used inode map */
	__fs32	cg_magic;		/* magic number */
	__u8	cg_मुक्त[1];		/* मुक्त block map */
/* actually दीर्घer */
पूर्ण;

/*
 * काष्ठाure of an on-disk inode
 */
काष्ठा ufs_inode अणु
	__fs16	ui_mode;		/*  0x0 */
	__fs16	ui_nlink;		/*  0x2 */
	जोड़ अणु
		काष्ठा अणु
			__fs16	ui_suid;	/*  0x4 */
			__fs16	ui_sgid;	/*  0x6 */
		पूर्ण oldids;
		__fs32	ui_inumber;		/*  0x4 lsf: inode number */
		__fs32	ui_author;		/*  0x4 GNU HURD: author */
	पूर्ण ui_u1;
	__fs64	ui_size;		/*  0x8 */
	काष्ठा ufs_समयval ui_aसमय;	/* 0x10 access */
	काष्ठा ufs_समयval ui_mसमय;	/* 0x18 modअगरication */
	काष्ठा ufs_समयval ui_स_समय;	/* 0x20 creation */
	जोड़ अणु
		काष्ठा अणु
			__fs32	ui_db[UFS_NDADDR];/* 0x28 data blocks */
			__fs32	ui_ib[UFS_NINसूची];/* 0x58 indirect blocks */
		पूर्ण ui_addr;
		__u8	ui_symlink[4*(UFS_NDADDR+UFS_NINसूची)];/* 0x28 fast symlink */
	पूर्ण ui_u2;
	__fs32	ui_flags;		/* 0x64 immutable, append-only... */
	__fs32	ui_blocks;		/* 0x68 blocks in use */
	__fs32	ui_gen;			/* 0x6c like ext2 i_version, क्रम NFS support */
	जोड़ अणु
		काष्ठा अणु
			__fs32	ui_shaकरोw;	/* 0x70 shaकरोw inode with security data */
			__fs32	ui_uid;		/* 0x74 दीर्घ EFT version of uid */
			__fs32	ui_gid;		/* 0x78 दीर्घ EFT version of gid */
			__fs32	ui_oeftflag;	/* 0x7c reserved */
		पूर्ण ui_sun;
		काष्ठा अणु
			__fs32	ui_uid;		/* 0x70 File owner */
			__fs32	ui_gid;		/* 0x74 File group */
			__fs32	ui_spare[2];	/* 0x78 reserved */
		पूर्ण ui_44;
		काष्ठा अणु
			__fs32	ui_uid;		/* 0x70 */
			__fs32	ui_gid;		/* 0x74 */
			__fs16	ui_modeh;	/* 0x78 mode high bits */
			__fs16	ui_spare;	/* 0x7A unused */
			__fs32	ui_trans;	/* 0x7c fileप्रणाली translator */
		पूर्ण ui_hurd;
	पूर्ण ui_u3;
पूर्ण;

#घोषणा UFS_NXADDR  2            /* External addresses in inode. */
काष्ठा ufs2_inode अणु
	__fs16     ui_mode;        /*   0: IFMT, permissions; see below. */
	__fs16     ui_nlink;       /*   2: File link count. */
	__fs32     ui_uid;         /*   4: File owner. */
	__fs32     ui_gid;         /*   8: File group. */
	__fs32     ui_blksize;     /*  12: Inode blocksize. */
	__fs64     ui_size;        /*  16: File byte count. */
	__fs64     ui_blocks;      /*  24: Bytes actually held. */
	__fs64   ui_aसमय;       /*  32: Last access समय. */
	__fs64   ui_mसमय;       /*  40: Last modअगरied समय. */
	__fs64   ui_स_समय;       /*  48: Last inode change समय. */
	__fs64   ui_birthसमय;   /*  56: Inode creation समय. */
	__fs32     ui_mसमयnsec;   /*  64: Last modअगरied समय. */
	__fs32     ui_aसमयnsec;   /*  68: Last access समय. */
	__fs32     ui_स_समयnsec;   /*  72: Last inode change समय. */
	__fs32     ui_birthnsec;   /*  76: Inode creation समय. */
	__fs32     ui_gen;         /*  80: Generation number. */
	__fs32     ui_kernflags;   /*  84: Kernel flags. */
	__fs32     ui_flags;       /*  88: Status flags (chflags). */
	__fs32     ui_extsize;     /*  92: External attributes block. */
	__fs64     ui_extb[UFS_NXADDR];/*  96: External attributes block. */
	जोड़ अणु
		काष्ठा अणु
			__fs64     ui_db[UFS_NDADDR]; /* 112: Direct disk blocks. */
			__fs64     ui_ib[UFS_NINसूची];/* 208: Indirect disk blocks.*/
		पूर्ण ui_addr;
	__u8	ui_symlink[2*4*(UFS_NDADDR+UFS_NINसूची)];/* 0x28 fast symlink */
	पूर्ण ui_u2;
	__fs64     ui_spare[3];    /* 232: Reserved; currently unused */
पूर्ण;


/* FreeBSD has these in sys/स्थिति.स */
/* ui_flags that can be set by a file owner */
#घोषणा UFS_UF_SETTABLE   0x0000ffff
#घोषणा UFS_UF_NODUMP     0x00000001  /* करो not dump */
#घोषणा UFS_UF_IMMUTABLE  0x00000002  /* immutable (can't "change") */
#घोषणा UFS_UF_APPEND     0x00000004  /* append-only */
#घोषणा UFS_UF_OPAQUE     0x00000008  /* directory is opaque (जोड़fs) */
#घोषणा UFS_UF_NOUNLINK   0x00000010  /* can't be हटाओd or नामd */
/* ui_flags that only root can set */
#घोषणा UFS_SF_SETTABLE   0xffff0000
#घोषणा UFS_SF_ARCHIVED   0x00010000  /* archived */
#घोषणा UFS_SF_IMMUTABLE  0x00020000  /* immutable (can't "change") */
#घोषणा UFS_SF_APPEND     0x00040000  /* append-only */
#घोषणा UFS_SF_NOUNLINK   0x00100000  /* can't be हटाओd or नामd */

/*
 * This काष्ठाure is used क्रम पढ़ोing disk काष्ठाures larger
 * than the size of fragment.
 */
काष्ठा ufs_buffer_head अणु
	__u64 fragment;			/* first fragment */
	__u64 count;				/* number of fragments */
	काष्ठा buffer_head * bh[UFS_MAXFRAG];	/* buffers */
पूर्ण;

काष्ठा ufs_cg_निजी_info अणु
	काष्ठा ufs_buffer_head c_ubh;
	__u32	c_cgx;		/* number of cylidner group */
	__u16	c_ncyl;		/* number of cyl's this cg */
	__u16	c_niblk;	/* number of inode blocks this cg */
	__u32	c_ndblk;	/* number of data blocks this cg */
	__u32	c_rotor;	/* position of last used block */
	__u32	c_frotor;	/* position of last used frag */
	__u32	c_irotor;	/* position of last used inode */
	__u32	c_btotoff;	/* (__u32) block totals per cylinder */
	__u32	c_boff;		/* (लघु) मुक्त block positions */
	__u32	c_iuseकरोff;	/* (अक्षर) used inode map */
	__u32	c_मुक्तoff;	/* (u_अक्षर) मुक्त block map */
	__u32	c_nextमुक्तoff;	/* (u_अक्षर) next available space */
	__u32	c_clustersumoff;/* (u_पूर्णांक32) counts of avail clusters */
	__u32	c_clusteroff;	/* (u_पूर्णांक8) मुक्त cluster map */
	__u32	c_nclusterblks;	/* number of clusters this cg */
पूर्ण;


काष्ठा ufs_sb_निजी_info अणु
	काष्ठा ufs_buffer_head s_ubh; /* buffer containing super block */
	काष्ठा ufs_csum_core cs_total;
	__u32	s_sblkno;	/* offset of super-blocks in filesys */
	__u32	s_cblkno;	/* offset of cg-block in filesys */
	__u32	s_iblkno;	/* offset of inode-blocks in filesys */
	__u32	s_dblkno;	/* offset of first data after cg */
	__u32	s_cgoffset;	/* cylinder group offset in cylinder */
	__u32	s_cgmask;	/* used to calc mod fs_ntrak */
	__u64	s_size;		/* number of blocks (fragments) in fs */
	__u64	s_dsize;	/* number of data blocks in fs */
	__u32	s_ncg;		/* number of cylinder groups */
	__u32	s_bsize;	/* size of basic blocks */
	__u32	s_fsize;	/* size of fragments */
	__u32	s_fpb;		/* fragments per block */
	__u32	s_minमुक्त;	/* minimum percentage of मुक्त blocks */
	__u32	s_bmask;	/* `blkoff'' calc of blk offsets */
	__u32	s_fmask;	/* s_fsize mask */
	__u32	s_bshअगरt;	/* `lblkno'' calc of logical blkno */
	__u32   s_fshअगरt;	/* s_fsize shअगरt */
	__u32	s_fpbshअगरt;	/* fragments per block shअगरt */
	__u32	s_fsbtodb;	/* fsbtodb and dbtofsb shअगरt स्थिरant */
	__u32	s_sbsize;	/* actual size of super block */
	__u32   s_csmask;	/* csum block offset */
	__u32	s_csshअगरt;	/* csum block number */
	__u32	s_nindir;	/* value of NINसूची */
	__u32	s_inopb;	/* value of INOPB */
	__u32	s_nspf;		/* value of NSPF */
	__u32	s_npsect;	/* # sectors/track including spares */
	__u32	s_पूर्णांकerleave;	/* hardware sector पूर्णांकerleave */
	__u32	s_trackskew;	/* sector 0 skew, per track */
	__u64	s_csaddr;	/* blk addr of cyl grp summary area */
	__u32	s_cssize;	/* size of cyl grp summary area */
	__u32	s_cgsize;	/* cylinder group size */
	__u32	s_ntrak;	/* tracks per cylinder */
	__u32	s_nsect;	/* sectors per track */
	__u32	s_spc;		/* sectors per cylinder */
	__u32	s_ipg;		/* inodes per cylinder group */
	__u32	s_fpg;		/* fragments per group */
	__u32	s_cpc;		/* cyl per cycle in postbl */
	__s32	s_contigsumsize;/* size of cluster summary array, 44bsd */
	__s64	s_qbmask;	/* ~usb_bmask */
	__s64	s_qfmask;	/* ~usb_fmask */
	__s32	s_postblक्रमmat;	/* क्रमmat of positional layout tables */
	__s32	s_nrpos;	/* number of rotational positions */
        __s32	s_postbloff;	/* (__s16) rotation block list head */
	__s32	s_rotbloff;	/* (__u8) blocks क्रम each rotation */

	__u32	s_fpbmask;	/* fragments per block mask */
	__u32	s_apb;		/* address per block */
	__u32	s_2apb;		/* address per block^2 */
	__u32	s_3apb;		/* address per block^3 */
	__u32	s_apbmask;	/* address per block mask */
	__u32	s_apbshअगरt;	/* address per block shअगरt */
	__u32	s_2apbshअगरt;	/* address per block shअगरt * 2 */
	__u32	s_3apbshअगरt;	/* address per block shअगरt * 3 */
	__u32	s_nspfshअगरt;	/* number of sector per fragment shअगरt */
	__u32	s_nspb;		/* number of sector per block */
	__u32	s_inopf;	/* inodes per fragment */
	__u32	s_sbbase;	/* offset of NeXTstep superblock */
	__u32	s_bpf;		/* bits per fragment */
	__u32	s_bpfshअगरt;	/* bits per fragment shअगरt*/
	__u32	s_bpfmask;	/* bits per fragment mask */

	__u32	s_maxsymlinklen;/* upper limit on fast symlinks' size */
	__s32	fs_magic;       /* fileप्रणाली magic */
	अचिन्हित पूर्णांक s_dirblksize;
	__u64   s_root_blocks;
	__u64	s_समय_प्रकारo_space;
	__u64	s_space_to_समय;
पूर्ण;

/*
 * Sizes of this काष्ठाures are:
 *	ufs_super_block_first	512
 *	ufs_super_block_second	512
 *	ufs_super_block_third	356
 */
काष्ठा ufs_super_block_first अणु
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_link;	/* UNUSED */
		पूर्ण fs_42;
		काष्ठा अणु
			__fs32	fs_state;	/* file प्रणाली state flag */
		पूर्ण fs_sun;
	पूर्ण fs_u0;
	__fs32	fs_rlink;
	__fs32	fs_sblkno;
	__fs32	fs_cblkno;
	__fs32	fs_iblkno;
	__fs32	fs_dblkno;
	__fs32	fs_cgoffset;
	__fs32	fs_cgmask;
	__fs32	fs_समय;
	__fs32	fs_size;
	__fs32	fs_dsize;
	__fs32	fs_ncg;
	__fs32	fs_bsize;
	__fs32	fs_fsize;
	__fs32	fs_frag;
	__fs32	fs_minमुक्त;
	__fs32	fs_rotdelay;
	__fs32	fs_rps;
	__fs32	fs_bmask;
	__fs32	fs_fmask;
	__fs32	fs_bshअगरt;
	__fs32	fs_fshअगरt;
	__fs32	fs_maxcontig;
	__fs32	fs_maxbpg;
	__fs32	fs_fragshअगरt;
	__fs32	fs_fsbtodb;
	__fs32	fs_sbsize;
	__fs32	fs_csmask;
	__fs32	fs_csshअगरt;
	__fs32	fs_nindir;
	__fs32	fs_inopb;
	__fs32	fs_nspf;
	__fs32	fs_optim;
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_npsect;
		पूर्ण fs_sun;
		काष्ठा अणु
			__fs32	fs_state;
		पूर्ण fs_sunx86;
	पूर्ण fs_u1;
	__fs32	fs_पूर्णांकerleave;
	__fs32	fs_trackskew;
	__fs32	fs_id[2];
	__fs32	fs_csaddr;
	__fs32	fs_cssize;
	__fs32	fs_cgsize;
	__fs32	fs_ntrak;
	__fs32	fs_nsect;
	__fs32	fs_spc;
	__fs32	fs_ncyl;
	__fs32	fs_cpg;
	__fs32	fs_ipg;
	__fs32	fs_fpg;
	काष्ठा ufs_csum fs_cstotal;
	__s8	fs_भ_शेष;
	__s8	fs_clean;
	__s8	fs_ronly;
	__s8	fs_flags;
	__s8	fs_fsmnt[UFS_MAXMNTLEN - 212];

पूर्ण;

काष्ठा ufs_super_block_second अणु
	जोड़ अणु
		काष्ठा अणु
			__s8	fs_fsmnt[212];
			__fs32	fs_cgrotor;
			__fs32	fs_csp[UFS_MAXCSBUFS];
			__fs32	fs_maxcluster;
			__fs32	fs_cpc;
			__fs16	fs_opostbl[82];
		पूर्ण fs_u1;
		काष्ठा अणु
			__s8  fs_fsmnt[UFS2_MAXMNTLEN - UFS_MAXMNTLEN + 212];
			__u8   fs_volname[UFS2_MAXVOLLEN];
			__fs64  fs_swuid;
			__fs32  fs_pad;
			__fs32   fs_cgrotor;
			__fs32   fs_ocsp[UFS2_NOCSPTRS];
			__fs32   fs_contigdirs;
			__fs32   fs_csp;
			__fs32   fs_maxcluster;
			__fs32   fs_active;
			__fs32   fs_old_cpc;
			__fs32   fs_maxbsize;
			__fs64   fs_sparecon64[17];
			__fs64   fs_sblockloc;
			__fs64	cs_ndir;
			__fs64	cs_nbमुक्त;
		पूर्ण fs_u2;
	पूर्ण fs_un;
पूर्ण;

काष्ठा ufs_super_block_third अणु
	जोड़ अणु
		काष्ठा अणु
			__fs16	fs_opostbl[46];
		पूर्ण fs_u1;
		काष्ठा अणु
			__fs64	cs_nअगरree;	/* number of मुक्त inodes */
			__fs64	cs_nfमुक्त;	/* number of मुक्त frags */
			__fs64   cs_numclusters;	/* number of मुक्त clusters */
			__fs64   cs_spare[3];	/* future expansion */
			काष्ठा  ufs_समयval    fs_समय;		/* last समय written */
			__fs64    fs_size;		/* number of blocks in fs */
			__fs64    fs_dsize;	/* number of data blocks in fs */
			__fs64   fs_csaddr;	/* blk addr of cyl grp summary area */
			__fs64    fs_pendingblocks;/* blocks in process of being मुक्तd */
			__fs32    fs_pendinginodes;/*inodes in process of being मुक्तd */
		पूर्ण __attribute__ ((packed)) fs_u2;
	पूर्ण fs_un1;
	जोड़ अणु
		काष्ठा अणु
			__fs32	fs_sparecon[53];/* reserved क्रम future स्थिरants */
			__fs32	fs_reclaim;
			__fs32	fs_sparecon2[1];
			__fs32	fs_state;	/* file प्रणाली state समय stamp */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		पूर्ण fs_sun;
		काष्ठा अणु
			__fs32	fs_sparecon[53];/* reserved क्रम future स्थिरants */
			__fs32	fs_reclaim;
			__fs32	fs_sparecon2[1];
			__fs32	fs_npsect;	/* # sectors/track including spares */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
		पूर्ण fs_sunx86;
		काष्ठा अणु
			__fs32	fs_sparecon[50];/* reserved क्रम future स्थिरants */
			__fs32	fs_contigsumsize;/* size of cluster summary array */
			__fs32	fs_maxsymlinklen;/* max length of an पूर्णांकernal symlink */
			__fs32	fs_inodefmt;	/* क्रमmat of on-disk inodes */
			__fs32	fs_maxfilesize[2];	/* max representable file size */
			__fs32	fs_qbmask[2];	/* ~usb_bmask */
			__fs32	fs_qfmask[2];	/* ~usb_fmask */
			__fs32	fs_state;	/* file प्रणाली state समय stamp */
		पूर्ण fs_44;
	पूर्ण fs_un2;
	__fs32	fs_postblक्रमmat;
	__fs32	fs_nrpos;
	__fs32	fs_postbloff;
	__fs32	fs_rotbloff;
	__fs32	fs_magic;
	__u8	fs_space[1];
पूर्ण;

#पूर्ण_अगर /* __LINUX_UFS_FS_H */
