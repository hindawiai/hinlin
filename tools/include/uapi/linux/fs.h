<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FS_H
#घोषणा _UAPI_LINUX_FS_H

/*
 * This file has definitions क्रम some important file table काष्ठाures
 * and स्थिरants and काष्ठाures used by various generic file प्रणाली
 * ioctl's.  Please करो not make any changes in this file beक्रमe
 * sending patches क्रम review to linux-fsdevel@vger.kernel.org and
 * linux-api@vger.kernel.org.
 */

#समावेश <linux/सीमा.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#अगर_अघोषित __KERNEL__
#समावेश <linux/fscrypt.h>
#पूर्ण_अगर

/* Use of MS_* flags within the kernel is restricted to core mount(2) code. */
#अगर !defined(__KERNEL__)
#समावेश <linux/mount.h>
#पूर्ण_अगर

/*
 * It's silly to have NR_OPEN bigger than NR_खाता, but you can change
 * the file limit at runसमय and only root can increase the per-process
 * nr_file rlimit, so it's safe to set up a ridiculously high असलolute
 * upper limit on files-per-process.
 *
 * Some programs (notably those using select()) may have to be 
 * recompiled to take full advantage of the new limits..  
 */

/* Fixed स्थिरants first: */
#अघोषित NR_OPEN
#घोषणा INR_OPEN_CUR 1024	/* Initial setting क्रम nfile rlimits */
#घोषणा INR_OPEN_MAX 4096	/* Hard limit क्रम nfile rlimits */

#घोषणा BLOCK_SIZE_BITS 10
#घोषणा BLOCK_SIZE (1<<BLOCK_SIZE_BITS)

#घोषणा शुरू_से	0	/* seek relative to beginning of file */
#घोषणा प्रस्तुत_से	1	/* seek relative to current file position */
#घोषणा अंत_से	2	/* seek relative to end of file */
#घोषणा SEEK_DATA	3	/* seek to the next data */
#घोषणा SEEK_HOLE	4	/* seek to the next hole */
#घोषणा SEEK_MAX	SEEK_HOLE

#घोषणा RENAME_NOREPLACE	(1 << 0)	/* Don't overग_लिखो target */
#घोषणा RENAME_EXCHANGE		(1 << 1)	/* Exchange source and dest */
#घोषणा RENAME_WHITEOUT		(1 << 2)	/* Whiteout source */

काष्ठा file_clone_range अणु
	__s64 src_fd;
	__u64 src_offset;
	__u64 src_length;
	__u64 dest_offset;
पूर्ण;

काष्ठा fstrim_range अणु
	__u64 start;
	__u64 len;
	__u64 minlen;
पूर्ण;

/* extent-same (dedupe) ioctls; these MUST match the btrfs ioctl definitions */
#घोषणा खाता_DEDUPE_RANGE_SAME		0
#घोषणा खाता_DEDUPE_RANGE_DIFFERS	1

/* from काष्ठा btrfs_ioctl_file_extent_same_info */
काष्ठा file_dedupe_range_info अणु
	__s64 dest_fd;		/* in - destination file */
	__u64 dest_offset;	/* in - start of extent in destination */
	__u64 bytes_deduped;	/* out - total # of bytes we were able
				 * to dedupe from this file. */
	/* status of this dedupe operation:
	 * < 0 क्रम error
	 * == खाता_DEDUPE_RANGE_SAME अगर dedupe succeeds
	 * == खाता_DEDUPE_RANGE_DIFFERS अगर data dअगरfers
	 */
	__s32 status;		/* out - see above description */
	__u32 reserved;		/* must be zero */
पूर्ण;

/* from काष्ठा btrfs_ioctl_file_extent_same_args */
काष्ठा file_dedupe_range अणु
	__u64 src_offset;	/* in - start of extent in source */
	__u64 src_length;	/* in - length of extent */
	__u16 dest_count;	/* in - total elements in info array */
	__u16 reserved1;	/* must be zero */
	__u32 reserved2;	/* must be zero */
	काष्ठा file_dedupe_range_info info[0];
पूर्ण;

/* And dynamically-tunable limits and शेषs: */
काष्ठा files_stat_काष्ठा अणु
	अचिन्हित दीर्घ nr_files;		/* पढ़ो only */
	अचिन्हित दीर्घ nr_मुक्त_files;	/* पढ़ो only */
	अचिन्हित दीर्घ max_files;		/* tunable */
पूर्ण;

काष्ठा inodes_stat_t अणु
	दीर्घ nr_inodes;
	दीर्घ nr_unused;
	दीर्घ dummy[5];		/* padding क्रम sysctl ABI compatibility */
पूर्ण;


#घोषणा NR_खाता  8192	/* this can well be larger on a larger प्रणाली */

/*
 * Structure क्रम FS_IOC_FSGETXATTR[A] and FS_IOC_FSSETXATTR.
 */
काष्ठा fsxattr अणु
	__u32		fsx_xflags;	/* xflags field value (get/set) */
	__u32		fsx_extsize;	/* extsize field value (get/set)*/
	__u32		fsx_nextents;	/* nextents field value (get)	*/
	__u32		fsx_projid;	/* project identअगरier (get/set) */
	__u32		fsx_cowextsize;	/* CoW extsize field value (get/set)*/
	अचिन्हित अक्षर	fsx_pad[8];
पूर्ण;

/*
 * Flags क्रम the fsx_xflags field
 */
#घोषणा FS_XFLAG_REALTIME	0x00000001	/* data in realसमय volume */
#घोषणा FS_XFLAG_PREALLOC	0x00000002	/* pपुनः_स्मृतिated file extents */
#घोषणा FS_XFLAG_IMMUTABLE	0x00000008	/* file cannot be modअगरied */
#घोषणा FS_XFLAG_APPEND		0x00000010	/* all ग_लिखोs append */
#घोषणा FS_XFLAG_SYNC		0x00000020	/* all ग_लिखोs synchronous */
#घोषणा FS_XFLAG_NOATIME	0x00000040	/* करो not update access समय */
#घोषणा FS_XFLAG_NODUMP		0x00000080	/* करो not include in backups */
#घोषणा FS_XFLAG_RTINHERIT	0x00000100	/* create with rt bit set */
#घोषणा FS_XFLAG_PROJINHERIT	0x00000200	/* create with parents projid */
#घोषणा FS_XFLAG_NOSYMLINKS	0x00000400	/* disallow symlink creation */
#घोषणा FS_XFLAG_EXTSIZE	0x00000800	/* extent size allocator hपूर्णांक */
#घोषणा FS_XFLAG_EXTSZINHERIT	0x00001000	/* inherit inode extent size */
#घोषणा FS_XFLAG_NODEFRAG	0x00002000	/* करो not defragment */
#घोषणा FS_XFLAG_खाताSTREAM	0x00004000	/* use filestream allocator */
#घोषणा FS_XFLAG_DAX		0x00008000	/* use DAX क्रम IO */
#घोषणा FS_XFLAG_COWEXTSIZE	0x00010000	/* CoW extent size allocator hपूर्णांक */
#घोषणा FS_XFLAG_HASATTR	0x80000000	/* no DIFLAG क्रम this	*/

/* the पढ़ो-only stuff करोesn't really beदीर्घ here, but any other place is
   probably as bad and I करोn't want to create yet another include file. */

#घोषणा BLKROSET   _IO(0x12,93)	/* set device पढ़ो-only (0 = पढ़ो-ग_लिखो) */
#घोषणा BLKROGET   _IO(0x12,94)	/* get पढ़ो-only status (0 = पढ़ो_ग_लिखो) */
#घोषणा BLKRRPART  _IO(0x12,95)	/* re-पढ़ो partition table */
#घोषणा BLKGETSIZE _IO(0x12,96)	/* वापस device size /512 (दीर्घ *arg) */
#घोषणा BLKFLSBUF  _IO(0x12,97)	/* flush buffer cache */
#घोषणा BLKRASET   _IO(0x12,98)	/* set पढ़ो ahead क्रम block device */
#घोषणा BLKRAGET   _IO(0x12,99)	/* get current पढ़ो ahead setting */
#घोषणा BLKFRASET  _IO(0x12,100)/* set fileप्रणाली (mm/filemap.c) पढ़ो-ahead */
#घोषणा BLKFRAGET  _IO(0x12,101)/* get fileप्रणाली (mm/filemap.c) पढ़ो-ahead */
#घोषणा BLKSECTSET _IO(0x12,102)/* set max sectors per request (ll_rw_blk.c) */
#घोषणा BLKSECTGET _IO(0x12,103)/* get max sectors per request (ll_rw_blk.c) */
#घोषणा BLKSSZGET  _IO(0x12,104)/* get block device sector size */
#अगर 0
#घोषणा BLKPG      _IO(0x12,105)/* See blkpg.h */

/* Some people are morons.  Do not use माप! */

#घोषणा BLKELVGET  _IOR(0x12,106,माप_प्रकार)/* elevator get */
#घोषणा BLKELVSET  _IOW(0x12,107,माप_प्रकार)/* elevator set */
/* This was here just to show that the number is taken -
   probably all these _IO(0x12,*) ioctls should be moved to blkpg.h. */
#पूर्ण_अगर
/* A jump here: 108-111 have been used क्रम various निजी purposes. */
#घोषणा BLKBSZGET  _IOR(0x12,112,माप_प्रकार)
#घोषणा BLKBSZSET  _IOW(0x12,113,माप_प्रकार)
#घोषणा BLKGETSIZE64 _IOR(0x12,114,माप_प्रकार)	/* वापस device size in bytes (u64 *arg) */
#घोषणा BLKTRACESETUP _IOWR(0x12,115,काष्ठा blk_user_trace_setup)
#घोषणा BLKTRACESTART _IO(0x12,116)
#घोषणा BLKTRACESTOP _IO(0x12,117)
#घोषणा BLKTRACETEARDOWN _IO(0x12,118)
#घोषणा BLKDISCARD _IO(0x12,119)
#घोषणा BLKIOMIN _IO(0x12,120)
#घोषणा BLKIOOPT _IO(0x12,121)
#घोषणा BLKALIGNOFF _IO(0x12,122)
#घोषणा BLKPBSZGET _IO(0x12,123)
#घोषणा BLKDISCARDZEROES _IO(0x12,124)
#घोषणा BLKSECDISCARD _IO(0x12,125)
#घोषणा BLKROTATIONAL _IO(0x12,126)
#घोषणा BLKZEROOUT _IO(0x12,127)
/*
 * A jump here: 130-136 are reserved क्रम zoned block devices
 * (see uapi/linux/blkzoned.h)
 */

#घोषणा BMAP_IOCTL 1		/* obsolete - kept क्रम compatibility */
#घोषणा FIBMAP	   _IO(0x00,1)	/* bmap access */
#घोषणा FIGETBSZ   _IO(0x00,2)	/* get the block size used क्रम bmap */
#घोषणा FIFREEZE	_IOWR('X', 119, पूर्णांक)	/* Freeze */
#घोषणा FITHAW		_IOWR('X', 120, पूर्णांक)	/* Thaw */
#घोषणा FITRIM		_IOWR('X', 121, काष्ठा fstrim_range)	/* Trim */
#घोषणा FICLONE		_IOW(0x94, 9, पूर्णांक)
#घोषणा FICLONदुस्फल	_IOW(0x94, 13, काष्ठा file_clone_range)
#घोषणा FIDEDUPदुस्फल	_IOWR(0x94, 54, काष्ठा file_dedupe_range)

#घोषणा FSLABEL_MAX 256	/* Max अक्षरs क्रम the पूर्णांकerface; each fs may dअगरfer */

#घोषणा	FS_IOC_GETFLAGS			_IOR('f', 1, दीर्घ)
#घोषणा	FS_IOC_SETFLAGS			_IOW('f', 2, दीर्घ)
#घोषणा	FS_IOC_GETVERSION		_IOR('v', 1, दीर्घ)
#घोषणा	FS_IOC_SETVERSION		_IOW('v', 2, दीर्घ)
#घोषणा FS_IOC_FIEMAP			_IOWR('f', 11, काष्ठा fiemap)
#घोषणा FS_IOC32_GETFLAGS		_IOR('f', 1, पूर्णांक)
#घोषणा FS_IOC32_SETFLAGS		_IOW('f', 2, पूर्णांक)
#घोषणा FS_IOC32_GETVERSION		_IOR('v', 1, पूर्णांक)
#घोषणा FS_IOC32_SETVERSION		_IOW('v', 2, पूर्णांक)
#घोषणा FS_IOC_FSGETXATTR		_IOR('X', 31, काष्ठा fsxattr)
#घोषणा FS_IOC_FSSETXATTR		_IOW('X', 32, काष्ठा fsxattr)
#घोषणा FS_IOC_GETFSLABEL		_IOR(0x94, 49, अक्षर[FSLABEL_MAX])
#घोषणा FS_IOC_SETFSLABEL		_IOW(0x94, 50, अक्षर[FSLABEL_MAX])

/*
 * Inode flags (FS_IOC_GETFLAGS / FS_IOC_SETFLAGS)
 *
 * Note: क्रम historical reasons, these flags were originally used and
 * defined क्रम use by ext2/ext3, and then other file प्रणालीs started
 * using these flags so they wouldn't need to ग_लिखो their own version
 * of chattr/lsattr (which was shipped as part of e2fsprogs).  You
 * should think twice beक्रमe trying to use these flags in new
 * contexts, or trying to assign these flags, since they are used both
 * as the UAPI and the on-disk encoding क्रम ext2/3/4.  Also, we are
 * almost out of 32-bit flags.  :-)
 *
 * We have recently hoisted FS_IOC_FSGETXATTR / FS_IOC_FSSETXATTR from
 * XFS to the generic FS level पूर्णांकerface.  This uses a काष्ठाure that
 * has padding and hence has more room to grow, so it may be more
 * appropriate क्रम many new use हालs.
 *
 * Please करो not change these flags or पूर्णांकerfaces beक्रमe checking with
 * linux-fsdevel@vger.kernel.org and linux-api@vger.kernel.org.
 */
#घोषणा	FS_SECRM_FL			0x00000001 /* Secure deletion */
#घोषणा	FS_UNRM_FL			0x00000002 /* Undelete */
#घोषणा	FS_COMPR_FL			0x00000004 /* Compress file */
#घोषणा FS_SYNC_FL			0x00000008 /* Synchronous updates */
#घोषणा FS_IMMUTABLE_FL			0x00000010 /* Immutable file */
#घोषणा FS_APPEND_FL			0x00000020 /* ग_लिखोs to file may only append */
#घोषणा FS_NODUMP_FL			0x00000040 /* करो not dump file */
#घोषणा FS_NOATIME_FL			0x00000080 /* करो not update aसमय */
/* Reserved क्रम compression usage... */
#घोषणा FS_सूचीTY_FL			0x00000100
#घोषणा FS_COMPRBLK_FL			0x00000200 /* One or more compressed clusters */
#घोषणा FS_NOCOMP_FL			0x00000400 /* Don't compress */
/* End compression flags --- maybe not all used */
#घोषणा FS_ENCRYPT_FL			0x00000800 /* Encrypted file */
#घोषणा FS_BTREE_FL			0x00001000 /* btree क्रमmat dir */
#घोषणा FS_INDEX_FL			0x00001000 /* hash-indexed directory */
#घोषणा FS_IMAGIC_FL			0x00002000 /* AFS directory */
#घोषणा FS_JOURNAL_DATA_FL		0x00004000 /* Reserved क्रम ext3 */
#घोषणा FS_NOTAIL_FL			0x00008000 /* file tail should not be merged */
#घोषणा FS_सूचीSYNC_FL			0x00010000 /* dirsync behaviour (directories only) */
#घोषणा FS_TOPसूची_FL			0x00020000 /* Top of directory hierarchies*/
#घोषणा FS_HUGE_खाता_FL			0x00040000 /* Reserved क्रम ext4 */
#घोषणा FS_EXTENT_FL			0x00080000 /* Extents */
#घोषणा FS_VERITY_FL			0x00100000 /* Verity रक्षित inode */
#घोषणा FS_EA_INODE_FL			0x00200000 /* Inode used क्रम large EA */
#घोषणा FS_खातापूर्णBLOCKS_FL			0x00400000 /* Reserved क्रम ext4 */
#घोषणा FS_NOCOW_FL			0x00800000 /* Do not cow file */
#घोषणा FS_DAX_FL			0x02000000 /* Inode is DAX */
#घोषणा FS_INLINE_DATA_FL		0x10000000 /* Reserved क्रम ext4 */
#घोषणा FS_PROJINHERIT_FL		0x20000000 /* Create with parents projid */
#घोषणा FS_CASEFOLD_FL			0x40000000 /* Folder is हाल insensitive */
#घोषणा FS_RESERVED_FL			0x80000000 /* reserved क्रम ext2 lib */

#घोषणा FS_FL_USER_VISIBLE		0x0003DFFF /* User visible flags */
#घोषणा FS_FL_USER_MODIFIABLE		0x000380FF /* User modअगरiable flags */


#घोषणा SYNC_खाता_RANGE_WAIT_BEFORE	1
#घोषणा SYNC_खाता_RANGE_WRITE		2
#घोषणा SYNC_खाता_RANGE_WAIT_AFTER	4
#घोषणा SYNC_खाता_RANGE_WRITE_AND_WAIT	(SYNC_खाता_RANGE_WRITE | \
					 SYNC_खाता_RANGE_WAIT_BEFORE | \
					 SYNC_खाता_RANGE_WAIT_AFTER)

/*
 * Flags क्रम pपढ़ोv2/pग_लिखोv2:
 */

प्रकार पूर्णांक __bitwise __kernel_rwf_t;

/* high priority request, poll अगर possible */
#घोषणा RWF_HIPRI	((__क्रमce __kernel_rwf_t)0x00000001)

/* per-IO O_DSYNC */
#घोषणा RWF_DSYNC	((__क्रमce __kernel_rwf_t)0x00000002)

/* per-IO O_SYNC */
#घोषणा RWF_SYNC	((__क्रमce __kernel_rwf_t)0x00000004)

/* per-IO, वापस -EAGAIN अगर operation would block */
#घोषणा RWF_NOWAIT	((__क्रमce __kernel_rwf_t)0x00000008)

/* per-IO O_APPEND */
#घोषणा RWF_APPEND	((__क्रमce __kernel_rwf_t)0x00000010)

/* mask of flags supported by the kernel */
#घोषणा RWF_SUPPORTED	(RWF_HIPRI | RWF_DSYNC | RWF_SYNC | RWF_NOWAIT |\
			 RWF_APPEND)

#पूर्ण_अगर /* _UAPI_LINUX_FS_H */
