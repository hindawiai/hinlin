<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2004-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IOCTL32_H__
#घोषणा __XFS_IOCTL32_H__

#समावेश <linux/compat.h>

/*
 * on 32-bit arches, ioctl argument काष्ठाures may have dअगरferent sizes
 * and/or alignment.  We define compat काष्ठाures which match the
 * 32-bit sizes/alignments here, and their associated ioctl numbers.
 *
 * xfs_ioctl32.c contains routines to copy these काष्ठाures in and out.
 */

/* stock kernel-level ioctls we support */
#घोषणा XFS_IOC_GETVERSION_32	FS_IOC32_GETVERSION

/*
 * On पूर्णांकel, even अगर sizes match, alignment and/or padding may dअगरfer.
 */
#अगर defined(CONFIG_IA64) || defined(CONFIG_X86_64)
#घोषणा BROKEN_X86_ALIGNMENT
#घोषणा __compat_packed __attribute__((packed))
#अन्यथा
#घोषणा __compat_packed
#पूर्ण_अगर

प्रकार काष्ठा compat_xfs_bsसमय अणु
	old_समय32_t	tv_sec;		/* seconds		*/
	__s32		tv_nsec;	/* and nanoseconds	*/
पूर्ण compat_xfs_bsसमय_प्रकार;

काष्ठा compat_xfs_bstat अणु
	__u64		bs_ino;		/* inode number			*/
	__u16		bs_mode;	/* type and mode		*/
	__u16		bs_nlink;	/* number of links		*/
	__u32		bs_uid;		/* user id			*/
	__u32		bs_gid;		/* group id			*/
	__u32		bs_rdev;	/* device value			*/
	__s32		bs_blksize;	/* block size			*/
	__s64		bs_size;	/* file size			*/
	compat_xfs_bsसमय_प्रकार bs_aसमय;	/* access समय			*/
	compat_xfs_bsसमय_प्रकार bs_mसमय;	/* modअगरy समय			*/
	compat_xfs_bsसमय_प्रकार bs_स_समय;	/* inode change समय		*/
	पूर्णांक64_t		bs_blocks;	/* number of blocks		*/
	__u32		bs_xflags;	/* extended flags		*/
	__s32		bs_extsize;	/* extent size			*/
	__s32		bs_extents;	/* number of extents		*/
	__u32		bs_gen;		/* generation count		*/
	__u16		bs_projid_lo;	/* lower part of project id	*/
#घोषणा	bs_projid	bs_projid_lo	/* (previously just bs_projid)	*/
	__u16		bs_विभाजनoff;	/* inode विभाजन offset in bytes	*/
	__u16		bs_projid_hi;	/* high part of project id	*/
	अचिन्हित अक्षर	bs_pad[10];	/* pad space, unused		*/
	__u32		bs_dmevmask;	/* DMIG event mask		*/
	__u16		bs_dmstate;	/* DMIG state info		*/
	__u16		bs_aextents;	/* attribute number of extents	*/
पूर्ण __compat_packed;

काष्ठा compat_xfs_fsop_bulkreq अणु
	compat_uptr_t	lastip;		/* last inode # poपूर्णांकer		*/
	__s32		icount;		/* count of entries in buffer	*/
	compat_uptr_t	ubuffer;	/* user buffer क्रम inode desc.	*/
	compat_uptr_t	ocount;		/* output count poपूर्णांकer		*/
पूर्ण;

#घोषणा XFS_IOC_FSBULKSTAT_32 \
	_IOWR('X', 101, काष्ठा compat_xfs_fsop_bulkreq)
#घोषणा XFS_IOC_FSBULKSTAT_SINGLE_32 \
	_IOWR('X', 102, काष्ठा compat_xfs_fsop_bulkreq)
#घोषणा XFS_IOC_FSINUMBERS_32 \
	_IOWR('X', 103, काष्ठा compat_xfs_fsop_bulkreq)

प्रकार काष्ठा compat_xfs_fsop_handlereq अणु
	__u32		fd;		/* fd क्रम FD_TO_HANDLE		*/
	compat_uptr_t	path;		/* user pathname		*/
	__u32		oflags;		/* खोलो flags			*/
	compat_uptr_t	ihandle;	/* user supplied handle		*/
	__u32		ihandlen;	/* user supplied length		*/
	compat_uptr_t	ohandle;	/* user buffer क्रम handle	*/
	compat_uptr_t	ohandlen;	/* user buffer length		*/
पूर्ण compat_xfs_fsop_handlereq_t;

#घोषणा XFS_IOC_PATH_TO_FSHANDLE_32 \
	_IOWR('X', 104, काष्ठा compat_xfs_fsop_handlereq)
#घोषणा XFS_IOC_PATH_TO_HANDLE_32 \
	_IOWR('X', 105, काष्ठा compat_xfs_fsop_handlereq)
#घोषणा XFS_IOC_FD_TO_HANDLE_32 \
	_IOWR('X', 106, काष्ठा compat_xfs_fsop_handlereq)
#घोषणा XFS_IOC_OPEN_BY_HANDLE_32 \
	_IOWR('X', 107, काष्ठा compat_xfs_fsop_handlereq)
#घोषणा XFS_IOC_READLINK_BY_HANDLE_32 \
	_IOWR('X', 108, काष्ठा compat_xfs_fsop_handlereq)

/* The bstat field in the swapext काष्ठा needs translation */
काष्ठा compat_xfs_swapext अणु
	पूर्णांक64_t			sx_version;	/* version */
	पूर्णांक64_t			sx_fdtarget;	/* fd of target file */
	पूर्णांक64_t			sx_fdपंचांगp;	/* fd of पंचांगp file */
	xfs_off_t		sx_offset;	/* offset पूर्णांकo file */
	xfs_off_t		sx_length;	/* leng from offset */
	अक्षर			sx_pad[16];	/* pad space, unused */
	काष्ठा compat_xfs_bstat	sx_stat;	/* stat of target b4 copy */
पूर्ण __compat_packed;

#घोषणा XFS_IOC_SWAPEXT_32	_IOWR('X', 109, काष्ठा compat_xfs_swapext)

प्रकार काष्ठा compat_xfs_fsop_attrlist_handlereq अणु
	काष्ठा compat_xfs_fsop_handlereq hreq; /* handle पूर्णांकerface काष्ठाure */
	काष्ठा xfs_attrlist_cursor	pos; /* opaque cookie, list offset */
	__u32				flags;	/* which namespace to use */
	__u32				buflen;	/* length of buffer supplied */
	compat_uptr_t			buffer;	/* वापसed names */
पूर्ण __compat_packed compat_xfs_fsop_attrlist_handlereq_t;

/* Note: actually this is पढ़ो/ग_लिखो */
#घोषणा XFS_IOC_ATTRLIST_BY_HANDLE_32 \
	_IOW('X', 122, काष्ठा compat_xfs_fsop_attrlist_handlereq)

/* am_opcodes defined in xfs_fs.h */
प्रकार काष्ठा compat_xfs_attr_multiop अणु
	__u32		am_opcode;
	__s32		am_error;
	compat_uptr_t	am_attrname;
	compat_uptr_t	am_attrvalue;
	__u32		am_length;
	__u32		am_flags;
पूर्ण compat_xfs_attr_multiop_t;

प्रकार काष्ठा compat_xfs_fsop_attrmulti_handlereq अणु
	काष्ठा compat_xfs_fsop_handlereq hreq; /* handle पूर्णांकerface काष्ठाure */
	__u32				opcount;/* count of following multiop */
	/* ptr to compat_xfs_attr_multiop */
	compat_uptr_t			ops; /* attr_multi data */
पूर्ण compat_xfs_fsop_attrmulti_handlereq_t;

#घोषणा XFS_IOC_ATTRMULTI_BY_HANDLE_32 \
	_IOW('X', 123, काष्ठा compat_xfs_fsop_attrmulti_handlereq)

#अगर_घोषित BROKEN_X86_ALIGNMENT
/* on ia32 l_start is on a 32-bit boundary */
प्रकार काष्ठा compat_xfs_flock64 अणु
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start	__attribute__((packed));
			/* len == 0 means until end of file */
	__s64		l_len __attribute__((packed));
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserve area */
पूर्ण compat_xfs_flock64_t;

#घोषणा XFS_IOC_ALLOCSP_32	_IOW('X', 10, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_FREESP_32	_IOW('X', 11, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_ALLOCSP64_32	_IOW('X', 36, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_FREESP64_32	_IOW('X', 37, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_RESVSP_32	_IOW('X', 40, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_UNRESVSP_32	_IOW('X', 41, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_RESVSP64_32	_IOW('X', 42, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_UNRESVSP64_32	_IOW('X', 43, काष्ठा compat_xfs_flock64)
#घोषणा XFS_IOC_ZERO_RANGE_32	_IOW('X', 57, काष्ठा compat_xfs_flock64)

प्रकार काष्ठा compat_xfs_fsop_geom_v1 अणु
	__u32		blocksize;	/* fileप्रणाली (data) block size */
	__u32		rtextsize;	/* realसमय extent size		*/
	__u32		agblocks;	/* fsblocks in an AG		*/
	__u32		agcount;	/* number of allocation groups	*/
	__u32		logblocks;	/* fsblocks in the log		*/
	__u32		sectsize;	/* (data) sector size, bytes	*/
	__u32		inodesize;	/* inode size in bytes		*/
	__u32		imaxpct;	/* max allowed inode space(%)	*/
	__u64		datablocks;	/* fsblocks in data subvolume	*/
	__u64		rtblocks;	/* fsblocks in realसमय subvol	*/
	__u64		rtextents;	/* rt extents in realसमय subvol*/
	__u64		logstart;	/* starting fsblock of the log	*/
	अचिन्हित अक्षर	uuid[16];	/* unique id of the fileप्रणाली	*/
	__u32		sunit;		/* stripe unit, fsblocks	*/
	__u32		swidth;		/* stripe width, fsblocks	*/
	__s32		version;	/* काष्ठाure version		*/
	__u32		flags;		/* superblock version flags	*/
	__u32		logsectsize;	/* log sector size, bytes	*/
	__u32		rtsectsize;	/* realसमय sector size, bytes	*/
	__u32		dirblocksize;	/* directory block size, bytes	*/
पूर्ण __attribute__((packed)) compat_xfs_fsop_geom_v1_t;

#घोषणा XFS_IOC_FSGEOMETRY_V1_32  \
	_IOR('X', 100, काष्ठा compat_xfs_fsop_geom_v1)

काष्ठा compat_xfs_inogrp अणु
	__u64		xi_startino;	/* starting inode number	*/
	__s32		xi_alloccount;	/* # bits set in allocmask	*/
	__u64		xi_allocmask;	/* mask of allocated inodes	*/
पूर्ण __attribute__((packed));

/* These growfs input काष्ठाures have padding on the end, so must translate */
प्रकार काष्ठा compat_xfs_growfs_data अणु
	__u64		newblocks;	/* new data subvol size, fsblocks */
	__u32		imaxpct;	/* new inode space percentage limit */
पूर्ण __attribute__((packed)) compat_xfs_growfs_data_t;

प्रकार काष्ठा compat_xfs_growfs_rt अणु
	__u64		newblocks;	/* new realसमय size, fsblocks */
	__u32		extsize;	/* new realसमय extent size, fsblocks */
पूर्ण __attribute__((packed)) compat_xfs_growfs_rt_t;

#घोषणा XFS_IOC_FSGROWFSDATA_32 _IOW('X', 110, काष्ठा compat_xfs_growfs_data)
#घोषणा XFS_IOC_FSGROWFSRT_32   _IOW('X', 112, काष्ठा compat_xfs_growfs_rt)

#पूर्ण_अगर /* BROKEN_X86_ALIGNMENT */

#पूर्ण_अगर /* __XFS_IOCTL32_H__ */
