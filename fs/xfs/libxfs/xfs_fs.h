<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */
/*
 * Copyright (c) 1995-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_FS_H__
#घोषणा __XFS_FS_H__

/*
 * SGI's XFS filesystem's major stuff (स्थिरants, काष्ठाures)
 */

/*
 * Direct I/O attribute record used with XFS_IOC_DIOINFO
 * d_miniosz is the min xfer size, xfer size multiple and file seek offset
 * alignment.
 */
#अगर_अघोषित HAVE_DIOATTR
काष्ठा dioattr अणु
	__u32		d_mem;		/* data buffer memory alignment */
	__u32		d_miniosz;	/* min xfer size		*/
	__u32		d_maxiosz;	/* max xfer size		*/
पूर्ण;
#पूर्ण_अगर

/*
 * Structure क्रम XFS_IOC_GETBMAP.
 * On input, fill in bmv_offset and bmv_length of the first काष्ठाure
 * to indicate the area of पूर्णांकerest in the file, and bmv_entries with
 * the number of array elements given back.  The first काष्ठाure is
 * updated on वापस to give the offset and length क्रम the next call.
 */
#अगर_अघोषित HAVE_GETBMAP
काष्ठा getbmap अणु
	__s64		bmv_offset;	/* file offset of segment in blocks */
	__s64		bmv_block;	/* starting block (64-bit daddr_t)  */
	__s64		bmv_length;	/* length of segment, blocks	    */
	__s32		bmv_count;	/* # of entries in array incl. 1st  */
	__s32		bmv_entries;	/* # of entries filled in (output)  */
पूर्ण;
#पूर्ण_अगर

/*
 *	Structure क्रम XFS_IOC_GETBMAPX.	 Fields bmv_offset through bmv_entries
 *	are used exactly as in the getbmap काष्ठाure.  The getbmapx काष्ठाure
 *	has additional bmv_अगरlags and bmv_oflags fields. The bmv_अगरlags field
 *	is only used क्रम the first काष्ठाure.  It contains input flags
 *	specअगरying XFS_IOC_GETBMAPX actions.  The bmv_oflags field is filled
 *	in by the XFS_IOC_GETBMAPX command क्रम each वापसed काष्ठाure after
 *	the first.
 */
#अगर_अघोषित HAVE_GETBMAPX
काष्ठा getbmapx अणु
	__s64		bmv_offset;	/* file offset of segment in blocks */
	__s64		bmv_block;	/* starting block (64-bit daddr_t)  */
	__s64		bmv_length;	/* length of segment, blocks	    */
	__s32		bmv_count;	/* # of entries in array incl. 1st  */
	__s32		bmv_entries;	/* # of entries filled in (output). */
	__s32		bmv_अगरlags;	/* input flags (1st काष्ठाure)	    */
	__s32		bmv_oflags;	/* output flags (after 1st काष्ठाure)*/
	__s32		bmv_unused1;	/* future use			    */
	__s32		bmv_unused2;	/* future use			    */
पूर्ण;
#पूर्ण_अगर

/*	bmv_अगरlags values - set by XFS_IOC_GETBMAPX caller.	*/
#घोषणा BMV_IF_ATTRFORK		0x1	/* वापस attr विभाजन rather than data */
#घोषणा BMV_IF_NO_DMAPI_READ	0x2	/* Deprecated */
#घोषणा BMV_IF_PREALLOC		0x4	/* rtn status BMV_OF_PREALLOC अगर req */
#घोषणा BMV_IF_DELALLOC		0x8	/* rtn status BMV_OF_DELALLOC अगर req */
#घोषणा BMV_IF_NO_HOLES		0x10	/* Do not वापस holes */
#घोषणा BMV_IF_COWFORK		0x20	/* वापस CoW विभाजन rather than data */
#घोषणा BMV_IF_VALID	\
	(BMV_IF_ATTRFORK|BMV_IF_NO_DMAPI_READ|BMV_IF_PREALLOC|	\
	 BMV_IF_DELALLOC|BMV_IF_NO_HOLES|BMV_IF_COWFORK)

/*	bmv_oflags values - वापसed क्रम each non-header segment */
#घोषणा BMV_OF_PREALLOC		0x1	/* segment = unwritten pre-allocation */
#घोषणा BMV_OF_DELALLOC		0x2	/* segment = delayed allocation */
#घोषणा BMV_OF_LAST		0x4	/* segment is the last in the file */
#घोषणा BMV_OF_SHARED		0x8	/* segment shared with another file */

/*	fmr_owner special values क्रम FS_IOC_GETFSMAP */
#घोषणा XFS_FMR_OWN_FREE	FMR_OWN_FREE      /* मुक्त space */
#घोषणा XFS_FMR_OWN_UNKNOWN	FMR_OWN_UNKNOWN   /* unknown owner */
#घोषणा XFS_FMR_OWN_FS		FMR_OWNER('X', 1) /* अटल fs metadata */
#घोषणा XFS_FMR_OWN_LOG		FMR_OWNER('X', 2) /* journalling log */
#घोषणा XFS_FMR_OWN_AG		FMR_OWNER('X', 3) /* per-AG metadata */
#घोषणा XFS_FMR_OWN_INOBT	FMR_OWNER('X', 4) /* inode btree blocks */
#घोषणा XFS_FMR_OWN_INODES	FMR_OWNER('X', 5) /* inodes */
#घोषणा XFS_FMR_OWN_REFC	FMR_OWNER('X', 6) /* refcount tree */
#घोषणा XFS_FMR_OWN_COW		FMR_OWNER('X', 7) /* cow staging */
#घोषणा XFS_FMR_OWN_DEFECTIVE	FMR_OWNER('X', 8) /* bad blocks */

/*
 * Structure क्रम XFS_IOC_FSSETDM.
 * For use by backup and restore programs to set the XFS on-disk inode
 * fields di_dmevmask and di_dmstate.  These must be set to exactly and
 * only values previously obtained via xfs_bulkstat!  (Specअगरically the
 * काष्ठा xfs_bstat fields bs_dmevmask and bs_dmstate.)
 */
#अगर_अघोषित HAVE_FSDMIDATA
काष्ठा fsdmidata अणु
	__u32		fsd_dmevmask;	/* corresponds to di_dmevmask */
	__u16		fsd_padding;
	__u16		fsd_dmstate;	/* corresponds to di_dmstate  */
पूर्ण;
#पूर्ण_अगर

/*
 * File segment locking set data type क्रम 64 bit access.
 * Also used क्रम all the RESV/FREE पूर्णांकerfaces.
 */
प्रकार काष्ठा xfs_flock64 अणु
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start;
	__s64		l_len;		/* len == 0 means until end of file */
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserve area			    */
पूर्ण xfs_flock64_t;

/*
 * Output क्रम XFS_IOC_FSGEOMETRY_V1
 */
काष्ठा xfs_fsop_geom_v1 अणु
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
पूर्ण;

/*
 * Output क्रम XFS_IOC_FSGEOMETRY_V4
 */
काष्ठा xfs_fsop_geom_v4 अणु
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
	__u32		logsunit;	/* log stripe unit, bytes	*/
पूर्ण;

/*
 * Output क्रम XFS_IOC_FSGEOMETRY
 */
काष्ठा xfs_fsop_geom अणु
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
	__u32		logsunit;	/* log stripe unit, bytes	*/
	uपूर्णांक32_t	sick;		/* o: unhealthy fs & rt metadata */
	uपूर्णांक32_t	checked;	/* o: checked fs & rt metadata	*/
	__u64		reserved[17];	/* reserved space		*/
पूर्ण;

#घोषणा XFS_FSOP_GEOM_SICK_COUNTERS	(1 << 0)  /* summary counters */
#घोषणा XFS_FSOP_GEOM_SICK_UQUOTA	(1 << 1)  /* user quota */
#घोषणा XFS_FSOP_GEOM_SICK_GQUOTA	(1 << 2)  /* group quota */
#घोषणा XFS_FSOP_GEOM_SICK_PQUOTA	(1 << 3)  /* project quota */
#घोषणा XFS_FSOP_GEOM_SICK_RT_BITMAP	(1 << 4)  /* realसमय biपंचांगap */
#घोषणा XFS_FSOP_GEOM_SICK_RT_SUMMARY	(1 << 5)  /* realसमय summary */

/* Output क्रम XFS_FS_COUNTS */
प्रकार काष्ठा xfs_fsop_counts अणु
	__u64	मुक्तdata;	/* मुक्त data section blocks */
	__u64	मुक्तrtx;	/* मुक्त rt extents */
	__u64	मुक्तino;	/* मुक्त inodes */
	__u64	allocino;	/* total allocated inodes */
पूर्ण xfs_fsop_counts_t;

/* Input/Output क्रम XFS_GET_RESBLKS and XFS_SET_RESBLKS */
प्रकार काष्ठा xfs_fsop_resblks अणु
	__u64  resblks;
	__u64  resblks_avail;
पूर्ण xfs_fsop_resblks_t;

#घोषणा XFS_FSOP_GEOM_VERSION		0
#घोषणा XFS_FSOP_GEOM_VERSION_V5	5

#घोषणा XFS_FSOP_GEOM_FLAGS_ATTR	(1 << 0)  /* attributes in use	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_NLINK	(1 << 1)  /* 32-bit nlink values   */
#घोषणा XFS_FSOP_GEOM_FLAGS_QUOTA	(1 << 2)  /* quotas enabled	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_IALIGN	(1 << 3)  /* inode alignment	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_DALIGN	(1 << 4)  /* large data alignment  */
#घोषणा XFS_FSOP_GEOM_FLAGS_SHARED	(1 << 5)  /* पढ़ो-only shared	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_EXTFLG	(1 << 6)  /* special extent flag   */
#घोषणा XFS_FSOP_GEOM_FLAGS_सूचीV2	(1 << 7)  /* directory version 2   */
#घोषणा XFS_FSOP_GEOM_FLAGS_LOGV2	(1 << 8)  /* log क्रमmat version 2  */
#घोषणा XFS_FSOP_GEOM_FLAGS_SECTOR	(1 << 9)  /* sector sizes >1BB	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_ATTR2	(1 << 10) /* अंतरभूत attributes rework */
#घोषणा XFS_FSOP_GEOM_FLAGS_PROJID32	(1 << 11) /* 32-bit project IDs	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_सूचीV2CI	(1 << 12) /* ASCII only CI names   */
	/*  -- Do not use --		(1 << 13)    SGI parent poपूर्णांकers   */
#घोषणा XFS_FSOP_GEOM_FLAGS_LAZYSB	(1 << 14) /* lazy superblock counters */
#घोषणा XFS_FSOP_GEOM_FLAGS_V5SB	(1 << 15) /* version 5 superblock  */
#घोषणा XFS_FSOP_GEOM_FLAGS_FTYPE	(1 << 16) /* inode directory types */
#घोषणा XFS_FSOP_GEOM_FLAGS_FINOBT	(1 << 17) /* मुक्त inode btree	   */
#घोषणा XFS_FSOP_GEOM_FLAGS_SPINODES	(1 << 18) /* sparse inode chunks   */
#घोषणा XFS_FSOP_GEOM_FLAGS_RMAPBT	(1 << 19) /* reverse mapping btree */
#घोषणा XFS_FSOP_GEOM_FLAGS_REFLINK	(1 << 20) /* files can share blocks */
#घोषणा XFS_FSOP_GEOM_FLAGS_BIGTIME	(1 << 21) /* 64-bit nsec बारtamps */
#घोषणा XFS_FSOP_GEOM_FLAGS_INOBTCNT	(1 << 22) /* inobt btree counter */

/*
 * Minimum and maximum sizes need क्रम growth checks.
 *
 * Block counts are in units of fileप्रणाली blocks, not basic blocks.
 */
#घोषणा XFS_MIN_AG_BLOCKS	64
#घोषणा XFS_MIN_LOG_BLOCKS	512ULL
#घोषणा XFS_MAX_LOG_BLOCKS	(1024 * 1024ULL)
#घोषणा XFS_MIN_LOG_BYTES	(10 * 1024 * 1024ULL)

/*
 * Limits on sb_agblocks/sb_agblklog -- mkfs won't क्रमmat AGs smaller than
 * 16MB or larger than 1TB.
 */
#घोषणा XFS_MIN_AG_BYTES	(1ULL << 24)	/* 16 MB */
#घोषणा XFS_MAX_AG_BYTES	(1ULL << 40)	/* 1 TB */

/* keep the maximum size under 2^31 by a small amount */
#घोषणा XFS_MAX_LOG_BYTES \
	((2 * 1024 * 1024 * 1024ULL) - XFS_MIN_LOG_BYTES)

/* Used क्रम sanity checks on superblock */
#घोषणा XFS_MAX_DBLOCKS(s) ((xfs_rfsblock_t)(s)->sb_agcount * (s)->sb_agblocks)
#घोषणा XFS_MIN_DBLOCKS(s) ((xfs_rfsblock_t)((s)->sb_agcount - 1) *	\
			 (s)->sb_agblocks + XFS_MIN_AG_BLOCKS)

/*
 * Output क्रम XFS_IOC_AG_GEOMETRY
 */
काष्ठा xfs_ag_geometry अणु
	uपूर्णांक32_t	ag_number;	/* i/o: AG number */
	uपूर्णांक32_t	ag_length;	/* o: length in blocks */
	uपूर्णांक32_t	ag_मुक्तblks;	/* o: मुक्त space */
	uपूर्णांक32_t	ag_icount;	/* o: inodes allocated */
	uपूर्णांक32_t	ag_अगरree;	/* o: inodes मुक्त */
	uपूर्णांक32_t	ag_sick;	/* o: sick things in ag */
	uपूर्णांक32_t	ag_checked;	/* o: checked metadata in ag */
	uपूर्णांक32_t	ag_flags;	/* i/o: flags क्रम this ag */
	uपूर्णांक64_t	ag_reserved[12];/* o: zero */
पूर्ण;
#घोषणा XFS_AG_GEOM_SICK_SB	(1 << 0)  /* superblock */
#घोषणा XFS_AG_GEOM_SICK_AGF	(1 << 1)  /* AGF header */
#घोषणा XFS_AG_GEOM_SICK_AGFL	(1 << 2)  /* AGFL header */
#घोषणा XFS_AG_GEOM_SICK_AGI	(1 << 3)  /* AGI header */
#घोषणा XFS_AG_GEOM_SICK_BNOBT	(1 << 4)  /* मुक्त space by block */
#घोषणा XFS_AG_GEOM_SICK_CNTBT	(1 << 5)  /* मुक्त space by length */
#घोषणा XFS_AG_GEOM_SICK_INOBT	(1 << 6)  /* inode index */
#घोषणा XFS_AG_GEOM_SICK_FINOBT	(1 << 7)  /* मुक्त inode index */
#घोषणा XFS_AG_GEOM_SICK_RMAPBT	(1 << 8)  /* reverse mappings */
#घोषणा XFS_AG_GEOM_SICK_REFCNTBT (1 << 9)  /* reference counts */

/*
 * Structures क्रम XFS_IOC_FSGROWFSDATA, XFS_IOC_FSGROWFSLOG & XFS_IOC_FSGROWFSRT
 */
प्रकार काष्ठा xfs_growfs_data अणु
	__u64		newblocks;	/* new data subvol size, fsblocks */
	__u32		imaxpct;	/* new inode space percentage limit */
पूर्ण xfs_growfs_data_t;

प्रकार काष्ठा xfs_growfs_log अणु
	__u32		newblocks;	/* new log size, fsblocks */
	__u32		isपूर्णांक;		/* 1 अगर new log is पूर्णांकernal */
पूर्ण xfs_growfs_log_t;

प्रकार काष्ठा xfs_growfs_rt अणु
	__u64		newblocks;	/* new realसमय size, fsblocks */
	__u32		extsize;	/* new realसमय extent size, fsblocks */
पूर्ण xfs_growfs_rt_t;


/*
 * Structures वापसed from ioctl XFS_IOC_FSBULKSTAT & XFS_IOC_FSBULKSTAT_SINGLE
 */
प्रकार काष्ठा xfs_bsसमय अणु
	__kernel_दीर्घ_t tv_sec;		/* seconds		*/
	__s32		tv_nsec;	/* and nanoseconds	*/
पूर्ण xfs_bsसमय_प्रकार;

काष्ठा xfs_bstat अणु
	__u64		bs_ino;		/* inode number			*/
	__u16		bs_mode;	/* type and mode		*/
	__u16		bs_nlink;	/* number of links		*/
	__u32		bs_uid;		/* user id			*/
	__u32		bs_gid;		/* group id			*/
	__u32		bs_rdev;	/* device value			*/
	__s32		bs_blksize;	/* block size			*/
	__s64		bs_size;	/* file size			*/
	xfs_bsसमय_प्रकार	bs_aसमय;	/* access समय			*/
	xfs_bsसमय_प्रकार	bs_mसमय;	/* modअगरy समय			*/
	xfs_bsसमय_प्रकार	bs_स_समय;	/* inode change समय		*/
	पूर्णांक64_t		bs_blocks;	/* number of blocks		*/
	__u32		bs_xflags;	/* extended flags		*/
	__s32		bs_extsize;	/* extent size			*/
	__s32		bs_extents;	/* number of extents		*/
	__u32		bs_gen;		/* generation count		*/
	__u16		bs_projid_lo;	/* lower part of project id	*/
#घोषणा	bs_projid	bs_projid_lo	/* (previously just bs_projid)	*/
	__u16		bs_विभाजनoff;	/* inode विभाजन offset in bytes	*/
	__u16		bs_projid_hi;	/* higher part of project id	*/
	uपूर्णांक16_t	bs_sick;	/* sick inode metadata		*/
	uपूर्णांक16_t	bs_checked;	/* checked inode metadata	*/
	अचिन्हित अक्षर	bs_pad[2];	/* pad space, unused		*/
	__u32		bs_cowextsize;	/* cow extent size		*/
	__u32		bs_dmevmask;	/* DMIG event mask		*/
	__u16		bs_dmstate;	/* DMIG state info		*/
	__u16		bs_aextents;	/* attribute number of extents	*/
पूर्ण;

/* New bulkstat काष्ठाure that reports v5 features and fixes padding issues */
काष्ठा xfs_bulkstat अणु
	uपूर्णांक64_t	bs_ino;		/* inode number			*/
	uपूर्णांक64_t	bs_size;	/* file size			*/

	uपूर्णांक64_t	bs_blocks;	/* number of blocks		*/
	uपूर्णांक64_t	bs_xflags;	/* extended flags		*/

	पूर्णांक64_t		bs_aसमय;	/* access समय, seconds		*/
	पूर्णांक64_t		bs_mसमय;	/* modअगरy समय, seconds		*/

	पूर्णांक64_t		bs_स_समय;	/* inode change समय, seconds	*/
	पूर्णांक64_t		bs_bसमय;	/* creation समय, seconds	*/

	uपूर्णांक32_t	bs_gen;		/* generation count		*/
	uपूर्णांक32_t	bs_uid;		/* user id			*/
	uपूर्णांक32_t	bs_gid;		/* group id			*/
	uपूर्णांक32_t	bs_projectid;	/* project id			*/

	uपूर्णांक32_t	bs_aसमय_nsec;	/* access समय, nanoseconds	*/
	uपूर्णांक32_t	bs_mसमय_nsec;	/* modअगरy समय, nanoseconds	*/
	uपूर्णांक32_t	bs_स_समय_nsec;	/* inode change समय, nanoseconds */
	uपूर्णांक32_t	bs_bसमय_nsec;	/* creation समय, nanoseconds	*/

	uपूर्णांक32_t	bs_blksize;	/* block size			*/
	uपूर्णांक32_t	bs_rdev;	/* device value			*/
	uपूर्णांक32_t	bs_cowextsize_blks; /* cow extent size hपूर्णांक, blocks */
	uपूर्णांक32_t	bs_extsize_blks; /* extent size hपूर्णांक, blocks	*/

	uपूर्णांक32_t	bs_nlink;	/* number of links		*/
	uपूर्णांक32_t	bs_extents;	/* number of extents		*/
	uपूर्णांक32_t	bs_aextents;	/* attribute number of extents	*/
	uपूर्णांक16_t	bs_version;	/* काष्ठाure version		*/
	uपूर्णांक16_t	bs_विभाजनoff;	/* inode विभाजन offset in bytes	*/

	uपूर्णांक16_t	bs_sick;	/* sick inode metadata		*/
	uपूर्णांक16_t	bs_checked;	/* checked inode metadata	*/
	uपूर्णांक16_t	bs_mode;	/* type and mode		*/
	uपूर्णांक16_t	bs_pad2;	/* zeroed			*/

	uपूर्णांक64_t	bs_pad[7];	/* zeroed			*/
पूर्ण;

#घोषणा XFS_BULKSTAT_VERSION_V1	(1)
#घोषणा XFS_BULKSTAT_VERSION_V5	(5)

/* bs_sick flags */
#घोषणा XFS_BS_SICK_INODE	(1 << 0)  /* inode core */
#घोषणा XFS_BS_SICK_BMBTD	(1 << 1)  /* data विभाजन */
#घोषणा XFS_BS_SICK_BMBTA	(1 << 2)  /* attr विभाजन */
#घोषणा XFS_BS_SICK_BMBTC	(1 << 3)  /* cow विभाजन */
#घोषणा XFS_BS_SICK_सूची		(1 << 4)  /* directory */
#घोषणा XFS_BS_SICK_XATTR	(1 << 5)  /* extended attributes */
#घोषणा XFS_BS_SICK_SYMLINK	(1 << 6)  /* symbolic link remote target */
#घोषणा XFS_BS_SICK_PARENT	(1 << 7)  /* parent poपूर्णांकers */

/*
 * Project quota id helpers (previously projid was 16bit only
 * and using two 16bit values to hold new 32bit projid was chosen
 * to retain compatibility with "old" fileप्रणालीs).
 */
अटल अंतरभूत uपूर्णांक32_t
bstat_get_projid(स्थिर काष्ठा xfs_bstat *bs)
अणु
	वापस (uपूर्णांक32_t)bs->bs_projid_hi << 16 | bs->bs_projid_lo;
पूर्ण

/*
 * The user-level BulkStat Request पूर्णांकerface काष्ठाure.
 */
काष्ठा xfs_fsop_bulkreq अणु
	__u64		__user *lastip;	/* last inode # poपूर्णांकer		*/
	__s32		icount;		/* count of entries in buffer	*/
	व्योम		__user *ubuffer;/* user buffer क्रम inode desc.	*/
	__s32		__user *ocount;	/* output count poपूर्णांकer		*/
पूर्ण;

/*
 * Structures वापसed from xfs_inumbers routine (XFS_IOC_FSINUMBERS).
 */
काष्ठा xfs_inogrp अणु
	__u64		xi_startino;	/* starting inode number	*/
	__s32		xi_alloccount;	/* # bits set in allocmask	*/
	__u64		xi_allocmask;	/* mask of allocated inodes	*/
पूर्ण;

/* New inumbers काष्ठाure that reports v5 features and fixes padding issues */
काष्ठा xfs_inumbers अणु
	uपूर्णांक64_t	xi_startino;	/* starting inode number	*/
	uपूर्णांक64_t	xi_allocmask;	/* mask of allocated inodes	*/
	uपूर्णांक8_t		xi_alloccount;	/* # bits set in allocmask	*/
	uपूर्णांक8_t		xi_version;	/* version			*/
	uपूर्णांक8_t		xi_padding[6];	/* zero				*/
पूर्ण;

#घोषणा XFS_INUMBERS_VERSION_V1	(1)
#घोषणा XFS_INUMBERS_VERSION_V5	(5)

/* Header क्रम bulk inode requests. */
काष्ठा xfs_bulk_ireq अणु
	uपूर्णांक64_t	ino;		/* I/O: start with this inode	*/
	uपूर्णांक32_t	flags;		/* I/O: operation flags		*/
	uपूर्णांक32_t	icount;		/* I: count of entries in buffer */
	uपूर्णांक32_t	ocount;		/* O: count of entries filled out */
	uपूर्णांक32_t	agno;		/* I: see comment क्रम IREQ_AGNO	*/
	uपूर्णांक64_t	reserved[5];	/* must be zero			*/
पूर्ण;

/*
 * Only वापस results from the specअगरied @agno.  If @ino is zero, start
 * with the first inode of @agno.
 */
#घोषणा XFS_BULK_IREQ_AGNO	(1 << 0)

/*
 * Return bulkstat inक्रमmation क्रम a single inode, where @ino value is a
 * special value, not a literal inode number.  See the XFS_BULK_IREQ_SPECIAL_*
 * values below.  Not compatible with XFS_BULK_IREQ_AGNO.
 */
#घोषणा XFS_BULK_IREQ_SPECIAL	(1 << 1)

#घोषणा XFS_BULK_IREQ_FLAGS_ALL	(XFS_BULK_IREQ_AGNO | \
				 XFS_BULK_IREQ_SPECIAL)

/* Operate on the root directory inode. */
#घोषणा XFS_BULK_IREQ_SPECIAL_ROOT	(1)

/*
 * ioctl काष्ठाures क्रम v5 bulkstat and inumbers requests
 */
काष्ठा xfs_bulkstat_req अणु
	काष्ठा xfs_bulk_ireq	hdr;
	काष्ठा xfs_bulkstat	bulkstat[];
पूर्ण;
#घोषणा XFS_BULKSTAT_REQ_SIZE(nr)	(माप(काष्ठा xfs_bulkstat_req) + \
					 (nr) * माप(काष्ठा xfs_bulkstat))

काष्ठा xfs_inumbers_req अणु
	काष्ठा xfs_bulk_ireq	hdr;
	काष्ठा xfs_inumbers	inumbers[];
पूर्ण;
#घोषणा XFS_INUMBERS_REQ_SIZE(nr)	(माप(काष्ठा xfs_inumbers_req) + \
					 (nr) * माप(काष्ठा xfs_inumbers))

/*
 * Error injection.
 */
प्रकार काष्ठा xfs_error_injection अणु
	__s32		fd;
	__s32		errtag;
पूर्ण xfs_error_injection_t;


/*
 * Speculative pपुनः_स्मृतिation trimming.
 */
#घोषणा XFS_खातापूर्णBLOCKS_VERSION		1
काष्ठा xfs_fs_eofblocks अणु
	__u32		eof_version;
	__u32		eof_flags;
	uid_t		eof_uid;
	gid_t		eof_gid;
	prid_t		eof_prid;
	__u32		pad32;
	__u64		eof_min_file_size;
	__u64		pad64[12];
पूर्ण;

/* eof_flags values */
#घोषणा XFS_खातापूर्ण_FLAGS_SYNC		(1 << 0) /* sync/रुको mode scan */
#घोषणा XFS_खातापूर्ण_FLAGS_UID		(1 << 1) /* filter by uid */
#घोषणा XFS_खातापूर्ण_FLAGS_GID		(1 << 2) /* filter by gid */
#घोषणा XFS_खातापूर्ण_FLAGS_PRID		(1 << 3) /* filter by project id */
#घोषणा XFS_खातापूर्ण_FLAGS_MINखाताSIZE	(1 << 4) /* filter by min file size */
#घोषणा XFS_खातापूर्ण_FLAGS_UNION		(1 << 5) /* जोड़ filter algorithm;
						  * kernel only, not included in
						  * valid mask */
#घोषणा XFS_खातापूर्ण_FLAGS_VALID	\
	(XFS_खातापूर्ण_FLAGS_SYNC |	\
	 XFS_खातापूर्ण_FLAGS_UID |	\
	 XFS_खातापूर्ण_FLAGS_GID |	\
	 XFS_खातापूर्ण_FLAGS_PRID |	\
	 XFS_खातापूर्ण_FLAGS_MINखाताSIZE)


/*
 * The user-level Handle Request पूर्णांकerface काष्ठाure.
 */
प्रकार काष्ठा xfs_fsop_handlereq अणु
	__u32		fd;		/* fd क्रम FD_TO_HANDLE		*/
	व्योम		__user *path;	/* user pathname		*/
	__u32		oflags;		/* खोलो flags			*/
	व्योम		__user *ihandle;/* user supplied handle		*/
	__u32		ihandlen;	/* user supplied length		*/
	व्योम		__user *ohandle;/* user buffer क्रम handle	*/
	__u32		__user *ohandlen;/* user buffer length		*/
पूर्ण xfs_fsop_handlereq_t;

/*
 * Compound काष्ठाures क्रम passing args through Handle Request पूर्णांकerfaces
 * xfs_fssetdm_by_handle, xfs_attrlist_by_handle, xfs_attrmulti_by_handle
 * - ioctls: XFS_IOC_FSSETDM_BY_HANDLE, XFS_IOC_ATTRLIST_BY_HANDLE, and
 *	     XFS_IOC_ATTRMULTI_BY_HANDLE
 */

प्रकार काष्ठा xfs_fsop_setdm_handlereq अणु
	काष्ठा xfs_fsop_handlereq	hreq;	/* handle inक्रमmation	*/
	काष्ठा fsdmidata		__user *data;	/* DMAPI data	*/
पूर्ण xfs_fsop_setdm_handlereq_t;

/*
 * Flags passed in xfs_attr_multiop.am_flags क्रम the attr ioctl पूर्णांकerface.
 *
 * NOTE: Must match the values declared in libattr without the XFS_IOC_ prefix.
 */
#घोषणा XFS_IOC_ATTR_ROOT	0x0002	/* use attrs in root namespace */
#घोषणा XFS_IOC_ATTR_SECURE	0x0008	/* use attrs in security namespace */
#घोषणा XFS_IOC_ATTR_CREATE	0x0010	/* fail अगर attr alपढ़ोy exists */
#घोषणा XFS_IOC_ATTR_REPLACE	0x0020	/* fail अगर attr करोes not exist */

प्रकार काष्ठा xfs_attrlist_cursor अणु
	__u32		opaque[4];
पूर्ण xfs_attrlist_cursor_t;

/*
 * Define how lists of attribute names are वापसed to userspace from the
 * XFS_IOC_ATTRLIST_BY_HANDLE ioctl.  काष्ठा xfs_attrlist is the header at the
 * beginning of the वापसed buffer, and a each entry in al_offset contains the
 * relative offset of an xfs_attrlist_ent containing the actual entry.
 *
 * NOTE: काष्ठा xfs_attrlist must match काष्ठा attrlist defined in libattr, and
 * काष्ठा xfs_attrlist_ent must match काष्ठा attrlist_ent defined in libattr.
 */
काष्ठा xfs_attrlist अणु
	__s32	al_count;	/* number of entries in attrlist */
	__s32	al_more;	/* T/F: more attrs (करो call again) */
	__s32	al_offset[1];	/* byte offsets of attrs [var-sized] */
पूर्ण;

काष्ठा xfs_attrlist_ent अणु	/* data from attr_list() */
	__u32	a_valuelen;	/* number bytes in value of attr */
	अक्षर	a_name[1];	/* attr name (शून्य terminated) */
पूर्ण;

प्रकार काष्ठा xfs_fsop_attrlist_handlereq अणु
	काष्ठा xfs_fsop_handlereq	hreq; /* handle पूर्णांकerface काष्ठाure */
	काष्ठा xfs_attrlist_cursor	pos; /* opaque cookie, list offset */
	__u32				flags;	/* which namespace to use */
	__u32				buflen;	/* length of buffer supplied */
	व्योम				__user *buffer;	/* वापसed names */
पूर्ण xfs_fsop_attrlist_handlereq_t;

प्रकार काष्ठा xfs_attr_multiop अणु
	__u32		am_opcode;
#घोषणा ATTR_OP_GET	1	/* वापस the indicated attr's value */
#घोषणा ATTR_OP_SET	2	/* set/create the indicated attr/value pair */
#घोषणा ATTR_OP_REMOVE	3	/* हटाओ the indicated attr */
	__s32		am_error;
	व्योम		__user *am_attrname;
	व्योम		__user *am_attrvalue;
	__u32		am_length;
	__u32		am_flags; /* XFS_IOC_ATTR_* */
पूर्ण xfs_attr_multiop_t;

प्रकार काष्ठा xfs_fsop_attrmulti_handlereq अणु
	काष्ठा xfs_fsop_handlereq	hreq; /* handle पूर्णांकerface काष्ठाure */
	__u32				opcount;/* count of following multiop */
	काष्ठा xfs_attr_multiop		__user *ops; /* attr_multi data */
पूर्ण xfs_fsop_attrmulti_handlereq_t;

/*
 * per machine unique fileप्रणाली identअगरier types.
 */
प्रकार काष्ठा अणु __u32 val[2]; पूर्ण xfs_fsid_t; /* file प्रणाली id type */

प्रकार काष्ठा xfs_fid अणु
	__u16	fid_len;		/* length of reमुख्यder	*/
	__u16	fid_pad;
	__u32	fid_gen;		/* generation number	*/
	__u64	fid_ino;		/* 64 bits inode number */
पूर्ण xfs_fid_t;

प्रकार काष्ठा xfs_handle अणु
	जोड़ अणु
		__s64	    align;	/* क्रमce alignment of ha_fid	 */
		xfs_fsid_t  _ha_fsid;	/* unique file प्रणाली identअगरier */
	पूर्ण ha_u;
	xfs_fid_t	ha_fid;		/* file प्रणाली specअगरic file ID	 */
पूर्ण xfs_handle_t;
#घोषणा ha_fsid ha_u._ha_fsid

/*
 * Structure passed to XFS_IOC_SWAPEXT
 */
प्रकार काष्ठा xfs_swapext
अणु
	पूर्णांक64_t		sx_version;	/* version */
#घोषणा XFS_SX_VERSION		0
	पूर्णांक64_t		sx_fdtarget;	/* fd of target file */
	पूर्णांक64_t		sx_fdपंचांगp;	/* fd of पंचांगp file */
	xfs_off_t	sx_offset;	/* offset पूर्णांकo file */
	xfs_off_t	sx_length;	/* leng from offset */
	अक्षर		sx_pad[16];	/* pad space, unused */
	काष्ठा xfs_bstat sx_stat;	/* stat of target b4 copy */
पूर्ण xfs_swapext_t;

/*
 * Flags क्रम going करोwn operation
 */
#घोषणा XFS_FSOP_GOING_FLAGS_DEFAULT		0x0	/* going करोwn */
#घोषणा XFS_FSOP_GOING_FLAGS_LOGFLUSH		0x1	/* flush log but not data */
#घोषणा XFS_FSOP_GOING_FLAGS_NOLOGFLUSH		0x2	/* करोn't flush log nor data */

/* metadata scrubbing */
काष्ठा xfs_scrub_metadata अणु
	__u32 sm_type;		/* What to check? */
	__u32 sm_flags;		/* flags; see below. */
	__u64 sm_ino;		/* inode number. */
	__u32 sm_gen;		/* inode generation. */
	__u32 sm_agno;		/* ag number. */
	__u64 sm_reserved[5];	/* pad to 64 bytes */
पूर्ण;

/*
 * Metadata types and flags क्रम scrub operation.
 */

/* Scrub subcommands. */
#घोषणा XFS_SCRUB_TYPE_PROBE	0	/* presence test ioctl */
#घोषणा XFS_SCRUB_TYPE_SB	1	/* superblock */
#घोषणा XFS_SCRUB_TYPE_AGF	2	/* AG मुक्त header */
#घोषणा XFS_SCRUB_TYPE_AGFL	3	/* AG मुक्त list */
#घोषणा XFS_SCRUB_TYPE_AGI	4	/* AG inode header */
#घोषणा XFS_SCRUB_TYPE_BNOBT	5	/* मुक्तsp by block btree */
#घोषणा XFS_SCRUB_TYPE_CNTBT	6	/* मुक्तsp by length btree */
#घोषणा XFS_SCRUB_TYPE_INOBT	7	/* inode btree */
#घोषणा XFS_SCRUB_TYPE_FINOBT	8	/* मुक्त inode btree */
#घोषणा XFS_SCRUB_TYPE_RMAPBT	9	/* reverse mapping btree */
#घोषणा XFS_SCRUB_TYPE_REFCNTBT	10	/* reference count btree */
#घोषणा XFS_SCRUB_TYPE_INODE	11	/* inode record */
#घोषणा XFS_SCRUB_TYPE_BMBTD	12	/* data विभाजन block mapping */
#घोषणा XFS_SCRUB_TYPE_BMBTA	13	/* attr विभाजन block mapping */
#घोषणा XFS_SCRUB_TYPE_BMBTC	14	/* CoW विभाजन block mapping */
#घोषणा XFS_SCRUB_TYPE_सूची	15	/* directory */
#घोषणा XFS_SCRUB_TYPE_XATTR	16	/* extended attribute */
#घोषणा XFS_SCRUB_TYPE_SYMLINK	17	/* symbolic link */
#घोषणा XFS_SCRUB_TYPE_PARENT	18	/* parent poपूर्णांकers */
#घोषणा XFS_SCRUB_TYPE_RTBITMAP	19	/* realसमय biपंचांगap */
#घोषणा XFS_SCRUB_TYPE_RTSUM	20	/* realसमय summary */
#घोषणा XFS_SCRUB_TYPE_UQUOTA	21	/* user quotas */
#घोषणा XFS_SCRUB_TYPE_GQUOTA	22	/* group quotas */
#घोषणा XFS_SCRUB_TYPE_PQUOTA	23	/* project quotas */
#घोषणा XFS_SCRUB_TYPE_FSCOUNTERS 24	/* fs summary counters */

/* Number of scrub subcommands. */
#घोषणा XFS_SCRUB_TYPE_NR	25

/* i: Repair this metadata. */
#घोषणा XFS_SCRUB_IFLAG_REPAIR		(1 << 0)

/* o: Metadata object needs repair. */
#घोषणा XFS_SCRUB_OFLAG_CORRUPT		(1 << 1)

/*
 * o: Metadata object could be optimized.  It's not corrupt, but
 *    we could improve on it somehow.
 */
#घोषणा XFS_SCRUB_OFLAG_PREEN		(1 << 2)

/* o: Cross-referencing failed. */
#घोषणा XFS_SCRUB_OFLAG_XFAIL		(1 << 3)

/* o: Metadata object disagrees with cross-referenced metadata. */
#घोषणा XFS_SCRUB_OFLAG_XCORRUPT	(1 << 4)

/* o: Scan was not complete. */
#घोषणा XFS_SCRUB_OFLAG_INCOMPLETE	(1 << 5)

/* o: Metadata object looked funny but isn't corrupt. */
#घोषणा XFS_SCRUB_OFLAG_WARNING		(1 << 6)

/*
 * o: IFLAG_REPAIR was set but metadata object did not need fixing or
 *    optimization and has thereक्रमe not been altered.
 */
#घोषणा XFS_SCRUB_OFLAG_NO_REPAIR_NEEDED (1 << 7)

#घोषणा XFS_SCRUB_FLAGS_IN	(XFS_SCRUB_IFLAG_REPAIR)
#घोषणा XFS_SCRUB_FLAGS_OUT	(XFS_SCRUB_OFLAG_CORRUPT | \
				 XFS_SCRUB_OFLAG_PREEN | \
				 XFS_SCRUB_OFLAG_XFAIL | \
				 XFS_SCRUB_OFLAG_XCORRUPT | \
				 XFS_SCRUB_OFLAG_INCOMPLETE | \
				 XFS_SCRUB_OFLAG_WARNING | \
				 XFS_SCRUB_OFLAG_NO_REPAIR_NEEDED)
#घोषणा XFS_SCRUB_FLAGS_ALL	(XFS_SCRUB_FLAGS_IN | XFS_SCRUB_FLAGS_OUT)

/*
 * ioctl limits
 */
#अगर_घोषित XATTR_LIST_MAX
#  define XFS_XATTR_LIST_MAX XATTR_LIST_MAX
#अन्यथा
#  define XFS_XATTR_LIST_MAX 65536
#पूर्ण_अगर


/*
 * ioctl commands that are used by Linux fileप्रणालीs
 */
#घोषणा XFS_IOC_GETXFLAGS	FS_IOC_GETFLAGS
#घोषणा XFS_IOC_SETXFLAGS	FS_IOC_SETFLAGS
#घोषणा XFS_IOC_GETVERSION	FS_IOC_GETVERSION

/*
 * ioctl commands that replace IRIX fcntl()'s
 * For 'documentation' purposed more than anything अन्यथा,
 * the "cmd #" field reflects the IRIX fcntl number.
 */
#घोषणा XFS_IOC_ALLOCSP		_IOW ('X', 10, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_FREESP		_IOW ('X', 11, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_DIOINFO		_IOR ('X', 30, काष्ठा dioattr)
#घोषणा XFS_IOC_FSGETXATTR	FS_IOC_FSGETXATTR
#घोषणा XFS_IOC_FSSETXATTR	FS_IOC_FSSETXATTR
#घोषणा XFS_IOC_ALLOCSP64	_IOW ('X', 36, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_FREESP64	_IOW ('X', 37, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_GETBMAP		_IOWR('X', 38, काष्ठा getbmap)
#घोषणा XFS_IOC_FSSETDM		_IOW ('X', 39, काष्ठा fsdmidata)
#घोषणा XFS_IOC_RESVSP		_IOW ('X', 40, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_UNRESVSP	_IOW ('X', 41, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_RESVSP64	_IOW ('X', 42, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_UNRESVSP64	_IOW ('X', 43, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_GETBMAPA	_IOWR('X', 44, काष्ठा getbmap)
#घोषणा XFS_IOC_FSGETXATTRA	_IOR ('X', 45, काष्ठा fsxattr)
/*	XFS_IOC_SETBIOSIZE ---- deprecated 46	   */
/*	XFS_IOC_GETBIOSIZE ---- deprecated 47	   */
#घोषणा XFS_IOC_GETBMAPX	_IOWR('X', 56, काष्ठा getbmap)
#घोषणा XFS_IOC_ZERO_RANGE	_IOW ('X', 57, काष्ठा xfs_flock64)
#घोषणा XFS_IOC_FREE_खातापूर्णBLOCKS	_IOR ('X', 58, काष्ठा xfs_fs_eofblocks)
/*	XFS_IOC_GETFSMAP ------ hoisted 59         */
#घोषणा XFS_IOC_SCRUB_METADATA	_IOWR('X', 60, काष्ठा xfs_scrub_metadata)
#घोषणा XFS_IOC_AG_GEOMETRY	_IOWR('X', 61, काष्ठा xfs_ag_geometry)

/*
 * ioctl commands that replace IRIX syssgi()'s
 */
#घोषणा XFS_IOC_FSGEOMETRY_V1	     _IOR ('X', 100, काष्ठा xfs_fsop_geom_v1)
#घोषणा XFS_IOC_FSBULKSTAT	     _IOWR('X', 101, काष्ठा xfs_fsop_bulkreq)
#घोषणा XFS_IOC_FSBULKSTAT_SINGLE    _IOWR('X', 102, काष्ठा xfs_fsop_bulkreq)
#घोषणा XFS_IOC_FSINUMBERS	     _IOWR('X', 103, काष्ठा xfs_fsop_bulkreq)
#घोषणा XFS_IOC_PATH_TO_FSHANDLE     _IOWR('X', 104, काष्ठा xfs_fsop_handlereq)
#घोषणा XFS_IOC_PATH_TO_HANDLE	     _IOWR('X', 105, काष्ठा xfs_fsop_handlereq)
#घोषणा XFS_IOC_FD_TO_HANDLE	     _IOWR('X', 106, काष्ठा xfs_fsop_handlereq)
#घोषणा XFS_IOC_OPEN_BY_HANDLE	     _IOWR('X', 107, काष्ठा xfs_fsop_handlereq)
#घोषणा XFS_IOC_READLINK_BY_HANDLE   _IOWR('X', 108, काष्ठा xfs_fsop_handlereq)
#घोषणा XFS_IOC_SWAPEXT		     _IOWR('X', 109, काष्ठा xfs_swapext)
#घोषणा XFS_IOC_FSGROWFSDATA	     _IOW ('X', 110, काष्ठा xfs_growfs_data)
#घोषणा XFS_IOC_FSGROWFSLOG	     _IOW ('X', 111, काष्ठा xfs_growfs_log)
#घोषणा XFS_IOC_FSGROWFSRT	     _IOW ('X', 112, काष्ठा xfs_growfs_rt)
#घोषणा XFS_IOC_FSCOUNTS	     _IOR ('X', 113, काष्ठा xfs_fsop_counts)
#घोषणा XFS_IOC_SET_RESBLKS	     _IOWR('X', 114, काष्ठा xfs_fsop_resblks)
#घोषणा XFS_IOC_GET_RESBLKS	     _IOR ('X', 115, काष्ठा xfs_fsop_resblks)
#घोषणा XFS_IOC_ERROR_INJECTION	     _IOW ('X', 116, काष्ठा xfs_error_injection)
#घोषणा XFS_IOC_ERROR_CLEARALL	     _IOW ('X', 117, काष्ठा xfs_error_injection)
/*	XFS_IOC_ATTRCTL_BY_HANDLE -- deprecated 118	 */

#घोषणा XFS_IOC_FREEZE		     _IOWR('X', 119, पूर्णांक)	/* aka FIFREEZE */
#घोषणा XFS_IOC_THAW		     _IOWR('X', 120, पूर्णांक)	/* aka FITHAW */

#घोषणा XFS_IOC_FSSETDM_BY_HANDLE    _IOW ('X', 121, काष्ठा xfs_fsop_setdm_handlereq)
#घोषणा XFS_IOC_ATTRLIST_BY_HANDLE   _IOW ('X', 122, काष्ठा xfs_fsop_attrlist_handlereq)
#घोषणा XFS_IOC_ATTRMULTI_BY_HANDLE  _IOW ('X', 123, काष्ठा xfs_fsop_attrmulti_handlereq)
#घोषणा XFS_IOC_FSGEOMETRY_V4	     _IOR ('X', 124, काष्ठा xfs_fsop_geom_v4)
#घोषणा XFS_IOC_GOINGDOWN	     _IOR ('X', 125, uपूर्णांक32_t)
#घोषणा XFS_IOC_FSGEOMETRY	     _IOR ('X', 126, काष्ठा xfs_fsop_geom)
#घोषणा XFS_IOC_BULKSTAT	     _IOR ('X', 127, काष्ठा xfs_bulkstat_req)
#घोषणा XFS_IOC_INUMBERS	     _IOR ('X', 128, काष्ठा xfs_inumbers_req)
/*	XFS_IOC_GETFSUUID ---------- deprecated 140	 */


#अगर_अघोषित HAVE_BBMACROS
/*
 * Block I/O parameterization.	A basic block (BB) is the lowest size of
 * fileप्रणाली allocation, and must equal 512.  Length units given to bio
 * routines are in BB's.
 */
#घोषणा BBSHIFT		9
#घोषणा BBSIZE		(1<<BBSHIFT)
#घोषणा BBMASK		(BBSIZE-1)
#घोषणा BTOBB(bytes)	(((__u64)(bytes) + BBSIZE - 1) >> BBSHIFT)
#घोषणा BTOBBT(bytes)	((__u64)(bytes) >> BBSHIFT)
#घोषणा BBTOB(bbs)	((bbs) << BBSHIFT)
#पूर्ण_अगर

#पूर्ण_अगर	/* __XFS_FS_H__ */
