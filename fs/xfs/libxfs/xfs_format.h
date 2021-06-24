<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_FORMAT_H__
#घोषणा __XFS_FORMAT_H__

/*
 * XFS On Disk Format Definitions
 *
 * This header file defines all the on-disk क्रमmat definitions क्रम 
 * general XFS objects. Directory and attribute related objects are defined in
 * xfs_da_क्रमmat.h, which log and log item क्रमmats are defined in
 * xfs_log_क्रमmat.h. Everything अन्यथा goes here.
 */

काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_inode;
काष्ठा xfs_buf;
काष्ठा xfs_अगरork;

/*
 * Super block
 * Fits पूर्णांकo a sector-sized buffer at address 0 of each allocation group.
 * Only the first of these is ever updated except during growfs.
 */
#घोषणा	XFS_SB_MAGIC		0x58465342	/* 'XFSB' */
#घोषणा	XFS_SB_VERSION_1	1		/* 5.3, 6.0.1, 6.1 */
#घोषणा	XFS_SB_VERSION_2	2		/* 6.2 - attributes */
#घोषणा	XFS_SB_VERSION_3	3		/* 6.2 - new inode version */
#घोषणा	XFS_SB_VERSION_4	4		/* 6.2+ - biपंचांगask version */
#घोषणा	XFS_SB_VERSION_5	5		/* CRC enabled fileप्रणाली */
#घोषणा	XFS_SB_VERSION_NUMBITS		0x000f
#घोषणा	XFS_SB_VERSION_ALLFBITS		0xfff0
#घोषणा	XFS_SB_VERSION_ATTRBIT		0x0010
#घोषणा	XFS_SB_VERSION_NLINKBIT		0x0020
#घोषणा	XFS_SB_VERSION_QUOTABIT		0x0040
#घोषणा	XFS_SB_VERSION_ALIGNBIT		0x0080
#घोषणा	XFS_SB_VERSION_DALIGNBIT	0x0100
#घोषणा	XFS_SB_VERSION_SHAREDBIT	0x0200
#घोषणा XFS_SB_VERSION_LOGV2BIT		0x0400
#घोषणा XFS_SB_VERSION_SECTORBIT	0x0800
#घोषणा	XFS_SB_VERSION_EXTFLGBIT	0x1000
#घोषणा	XFS_SB_VERSION_सूचीV2BIT		0x2000
#घोषणा	XFS_SB_VERSION_BORGBIT		0x4000	/* ASCII only हाल-insens. */
#घोषणा	XFS_SB_VERSION_MOREBITSBIT	0x8000

/*
 * The size of a single extended attribute on disk is limited by
 * the size of index values within the attribute entries themselves.
 * These are be16 fields, so we can only support attribute data
 * sizes up to 2^16 bytes in length.
 */
#घोषणा XFS_XATTR_SIZE_MAX (1 << 16)

/*
 * Supported feature bit list is just all bits in the versionnum field because
 * we've used them all up and understand them all. Except, of course, क्रम the
 * shared superblock bit, which nobody knows what it करोes and so is unsupported.
 */
#घोषणा	XFS_SB_VERSION_OKBITS		\
	((XFS_SB_VERSION_NUMBITS | XFS_SB_VERSION_ALLFBITS) & \
		~XFS_SB_VERSION_SHAREDBIT)

/*
 * There are two words to hold XFS "feature" bits: the original
 * word, sb_versionnum, and sb_features2.  Whenever a bit is set in
 * sb_features2, the feature bit XFS_SB_VERSION_MOREBITSBIT must be set.
 *
 * These defines represent bits in sb_features2.
 */
#घोषणा XFS_SB_VERSION2_RESERVED1BIT	0x00000001
#घोषणा XFS_SB_VERSION2_LAZYSBCOUNTBIT	0x00000002	/* Superblk counters */
#घोषणा XFS_SB_VERSION2_RESERVED4BIT	0x00000004
#घोषणा XFS_SB_VERSION2_ATTR2BIT	0x00000008	/* Inline attr rework */
#घोषणा XFS_SB_VERSION2_PARENTBIT	0x00000010	/* parent poपूर्णांकers */
#घोषणा XFS_SB_VERSION2_PROJID32BIT	0x00000080	/* 32 bit project id */
#घोषणा XFS_SB_VERSION2_CRCBIT		0x00000100	/* metadata CRCs */
#घोषणा XFS_SB_VERSION2_FTYPE		0x00000200	/* inode type in dir */

#घोषणा	XFS_SB_VERSION2_OKBITS		\
	(XFS_SB_VERSION2_LAZYSBCOUNTBIT	| \
	 XFS_SB_VERSION2_ATTR2BIT	| \
	 XFS_SB_VERSION2_PROJID32BIT	| \
	 XFS_SB_VERSION2_FTYPE)

/* Maximum size of the xfs fileप्रणाली label, no terminating शून्य */
#घोषणा XFSLABEL_MAX			12

/*
 * Superblock - in core version.  Must match the ondisk version below.
 * Must be padded to 64 bit alignment.
 */
प्रकार काष्ठा xfs_sb अणु
	uपूर्णांक32_t	sb_magicnum;	/* magic number == XFS_SB_MAGIC */
	uपूर्णांक32_t	sb_blocksize;	/* logical block size, bytes */
	xfs_rfsblock_t	sb_dblocks;	/* number of data blocks */
	xfs_rfsblock_t	sb_rblocks;	/* number of realसमय blocks */
	xfs_rtblock_t	sb_rextents;	/* number of realसमय extents */
	uuid_t		sb_uuid;	/* user-visible file प्रणाली unique id */
	xfs_fsblock_t	sb_logstart;	/* starting block of log अगर पूर्णांकernal */
	xfs_ino_t	sb_rootino;	/* root inode number */
	xfs_ino_t	sb_rbmino;	/* biपंचांगap inode क्रम realसमय extents */
	xfs_ino_t	sb_rsumino;	/* summary inode क्रम rt biपंचांगap */
	xfs_agblock_t	sb_rextsize;	/* realसमय extent size, blocks */
	xfs_agblock_t	sb_agblocks;	/* size of an allocation group */
	xfs_agnumber_t	sb_agcount;	/* number of allocation groups */
	xfs_extlen_t	sb_rbmblocks;	/* number of rt biपंचांगap blocks */
	xfs_extlen_t	sb_logblocks;	/* number of log blocks */
	uपूर्णांक16_t	sb_versionnum;	/* header version == XFS_SB_VERSION */
	uपूर्णांक16_t	sb_sectsize;	/* volume sector size, bytes */
	uपूर्णांक16_t	sb_inodesize;	/* inode size, bytes */
	uपूर्णांक16_t	sb_inopblock;	/* inodes per block */
	अक्षर		sb_fname[XFSLABEL_MAX]; /* file प्रणाली name */
	uपूर्णांक8_t		sb_blocklog;	/* log2 of sb_blocksize */
	uपूर्णांक8_t		sb_sectlog;	/* log2 of sb_sectsize */
	uपूर्णांक8_t		sb_inodelog;	/* log2 of sb_inodesize */
	uपूर्णांक8_t		sb_inopblog;	/* log2 of sb_inopblock */
	uपूर्णांक8_t		sb_agblklog;	/* log2 of sb_agblocks (rounded up) */
	uपूर्णांक8_t		sb_rextslog;	/* log2 of sb_rextents */
	uपूर्णांक8_t		sb_inprogress;	/* mkfs is in progress, करोn't mount */
	uपूर्णांक8_t		sb_imax_pct;	/* max % of fs क्रम inode space */
					/* statistics */
	/*
	 * These fields must reमुख्य contiguous.  If you really
	 * want to change their layout, make sure you fix the
	 * code in xfs_trans_apply_sb_deltas().
	 */
	uपूर्णांक64_t	sb_icount;	/* allocated inodes */
	uपूर्णांक64_t	sb_अगरree;	/* मुक्त inodes */
	uपूर्णांक64_t	sb_fdblocks;	/* मुक्त data blocks */
	uपूर्णांक64_t	sb_frextents;	/* मुक्त realसमय extents */
	/*
	 * End contiguous fields.
	 */
	xfs_ino_t	sb_uquotino;	/* user quota inode */
	xfs_ino_t	sb_gquotino;	/* group quota inode */
	uपूर्णांक16_t	sb_qflags;	/* quota flags */
	uपूर्णांक8_t		sb_flags;	/* misc. flags */
	uपूर्णांक8_t		sb_shared_vn;	/* shared version number */
	xfs_extlen_t	sb_inoalignmt;	/* inode chunk alignment, fsblocks */
	uपूर्णांक32_t	sb_unit;	/* stripe or raid unit */
	uपूर्णांक32_t	sb_width;	/* stripe or raid width */
	uपूर्णांक8_t		sb_dirblklog;	/* log2 of dir block size (fsbs) */
	uपूर्णांक8_t		sb_logsectlog;	/* log2 of the log sector size */
	uपूर्णांक16_t	sb_logsectsize;	/* sector size क्रम the log, bytes */
	uपूर्णांक32_t	sb_logsunit;	/* stripe unit size क्रम the log */
	uपूर्णांक32_t	sb_features2;	/* additional feature bits */

	/*
	 * bad features2 field as a result of failing to pad the sb काष्ठाure to
	 * 64 bits. Some machines will be using this field क्रम features2 bits.
	 * Easiest just to mark it bad and not use it क्रम anything अन्यथा.
	 *
	 * This is not kept up to date in memory; it is always overwritten by
	 * the value in sb_features2 when क्रमmatting the incore superblock to
	 * the disk buffer.
	 */
	uपूर्णांक32_t	sb_bad_features2;

	/* version 5 superblock fields start here */

	/* feature masks */
	uपूर्णांक32_t	sb_features_compat;
	uपूर्णांक32_t	sb_features_ro_compat;
	uपूर्णांक32_t	sb_features_incompat;
	uपूर्णांक32_t	sb_features_log_incompat;

	uपूर्णांक32_t	sb_crc;		/* superblock crc */
	xfs_extlen_t	sb_spino_align;	/* sparse inode chunk alignment */

	xfs_ino_t	sb_pquotino;	/* project quota inode */
	xfs_lsn_t	sb_lsn;		/* last ग_लिखो sequence */
	uuid_t		sb_meta_uuid;	/* metadata file प्रणाली unique id */

	/* must be padded to 64 bit alignment */
पूर्ण xfs_sb_t;

#घोषणा XFS_SB_CRC_OFF		दुरत्व(काष्ठा xfs_sb, sb_crc)

/*
 * Superblock - on disk version.  Must match the in core version above.
 * Must be padded to 64 bit alignment.
 */
प्रकार काष्ठा xfs_dsb अणु
	__be32		sb_magicnum;	/* magic number == XFS_SB_MAGIC */
	__be32		sb_blocksize;	/* logical block size, bytes */
	__be64		sb_dblocks;	/* number of data blocks */
	__be64		sb_rblocks;	/* number of realसमय blocks */
	__be64		sb_rextents;	/* number of realसमय extents */
	uuid_t		sb_uuid;	/* user-visible file प्रणाली unique id */
	__be64		sb_logstart;	/* starting block of log अगर पूर्णांकernal */
	__be64		sb_rootino;	/* root inode number */
	__be64		sb_rbmino;	/* biपंचांगap inode क्रम realसमय extents */
	__be64		sb_rsumino;	/* summary inode क्रम rt biपंचांगap */
	__be32		sb_rextsize;	/* realसमय extent size, blocks */
	__be32		sb_agblocks;	/* size of an allocation group */
	__be32		sb_agcount;	/* number of allocation groups */
	__be32		sb_rbmblocks;	/* number of rt biपंचांगap blocks */
	__be32		sb_logblocks;	/* number of log blocks */
	__be16		sb_versionnum;	/* header version == XFS_SB_VERSION */
	__be16		sb_sectsize;	/* volume sector size, bytes */
	__be16		sb_inodesize;	/* inode size, bytes */
	__be16		sb_inopblock;	/* inodes per block */
	अक्षर		sb_fname[XFSLABEL_MAX]; /* file प्रणाली name */
	__u8		sb_blocklog;	/* log2 of sb_blocksize */
	__u8		sb_sectlog;	/* log2 of sb_sectsize */
	__u8		sb_inodelog;	/* log2 of sb_inodesize */
	__u8		sb_inopblog;	/* log2 of sb_inopblock */
	__u8		sb_agblklog;	/* log2 of sb_agblocks (rounded up) */
	__u8		sb_rextslog;	/* log2 of sb_rextents */
	__u8		sb_inprogress;	/* mkfs is in progress, करोn't mount */
	__u8		sb_imax_pct;	/* max % of fs क्रम inode space */
					/* statistics */
	/*
	 * These fields must reमुख्य contiguous.  If you really
	 * want to change their layout, make sure you fix the
	 * code in xfs_trans_apply_sb_deltas().
	 */
	__be64		sb_icount;	/* allocated inodes */
	__be64		sb_अगरree;	/* मुक्त inodes */
	__be64		sb_fdblocks;	/* मुक्त data blocks */
	__be64		sb_frextents;	/* मुक्त realसमय extents */
	/*
	 * End contiguous fields.
	 */
	__be64		sb_uquotino;	/* user quota inode */
	__be64		sb_gquotino;	/* group quota inode */
	__be16		sb_qflags;	/* quota flags */
	__u8		sb_flags;	/* misc. flags */
	__u8		sb_shared_vn;	/* shared version number */
	__be32		sb_inoalignmt;	/* inode chunk alignment, fsblocks */
	__be32		sb_unit;	/* stripe or raid unit */
	__be32		sb_width;	/* stripe or raid width */
	__u8		sb_dirblklog;	/* log2 of dir block size (fsbs) */
	__u8		sb_logsectlog;	/* log2 of the log sector size */
	__be16		sb_logsectsize;	/* sector size क्रम the log, bytes */
	__be32		sb_logsunit;	/* stripe unit size क्रम the log */
	__be32		sb_features2;	/* additional feature bits */
	/*
	 * bad features2 field as a result of failing to pad the sb
	 * काष्ठाure to 64 bits. Some machines will be using this field
	 * क्रम features2 bits. Easiest just to mark it bad and not use
	 * it क्रम anything अन्यथा.
	 */
	__be32		sb_bad_features2;

	/* version 5 superblock fields start here */

	/* feature masks */
	__be32		sb_features_compat;
	__be32		sb_features_ro_compat;
	__be32		sb_features_incompat;
	__be32		sb_features_log_incompat;

	__le32		sb_crc;		/* superblock crc */
	__be32		sb_spino_align;	/* sparse inode chunk alignment */

	__be64		sb_pquotino;	/* project quota inode */
	__be64		sb_lsn;		/* last ग_लिखो sequence */
	uuid_t		sb_meta_uuid;	/* metadata file प्रणाली unique id */

	/* must be padded to 64 bit alignment */
पूर्ण xfs_dsb_t;


/*
 * Misc. Flags - warning - these will be cleared by xfs_repair unless
 * a feature bit is set when the flag is used.
 */
#घोषणा XFS_SBF_NOFLAGS		0x00	/* no flags set */
#घोषणा XFS_SBF_READONLY	0x01	/* only पढ़ो-only mounts allowed */

/*
 * define max. shared version we can पूर्णांकeroperate with
 */
#घोषणा XFS_SB_MAX_SHARED_VN	0

#घोषणा	XFS_SB_VERSION_NUM(sbp)	((sbp)->sb_versionnum & XFS_SB_VERSION_NUMBITS)

/*
 * The first XFS version we support is a v4 superblock with V2 directories.
 */
अटल अंतरभूत bool xfs_sb_good_v4_features(काष्ठा xfs_sb *sbp)
अणु
	अगर (!(sbp->sb_versionnum & XFS_SB_VERSION_सूचीV2BIT))
		वापस false;
	अगर (!(sbp->sb_versionnum & XFS_SB_VERSION_EXTFLGBIT))
		वापस false;

	/* check क्रम unknown features in the fs */
	अगर ((sbp->sb_versionnum & ~XFS_SB_VERSION_OKBITS) ||
	    ((sbp->sb_versionnum & XFS_SB_VERSION_MOREBITSBIT) &&
	     (sbp->sb_features2 & ~XFS_SB_VERSION2_OKBITS)))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool xfs_sb_good_version(काष्ठा xfs_sb *sbp)
अणु
	अगर (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5)
		वापस true;
	अगर (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4)
		वापस xfs_sb_good_v4_features(sbp);
	वापस false;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasrealसमय(काष्ठा xfs_sb *sbp)
अणु
	वापस sbp->sb_rblocks > 0;
पूर्ण

/*
 * Detect a mismatched features2 field.  Older kernels पढ़ो/wrote
 * this पूर्णांकo the wrong slot, so to be safe we keep them in sync.
 */
अटल अंतरभूत bool xfs_sb_has_mismatched_features2(काष्ठा xfs_sb *sbp)
अणु
	वापस sbp->sb_bad_features2 != sbp->sb_features2;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasattr(काष्ठा xfs_sb *sbp)
अणु
	वापस (sbp->sb_versionnum & XFS_SB_VERSION_ATTRBIT);
पूर्ण

अटल अंतरभूत व्योम xfs_sb_version_addattr(काष्ठा xfs_sb *sbp)
अणु
	sbp->sb_versionnum |= XFS_SB_VERSION_ATTRBIT;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasquota(काष्ठा xfs_sb *sbp)
अणु
	वापस (sbp->sb_versionnum & XFS_SB_VERSION_QUOTABIT);
पूर्ण

अटल अंतरभूत व्योम xfs_sb_version_addquota(काष्ठा xfs_sb *sbp)
अणु
	sbp->sb_versionnum |= XFS_SB_VERSION_QUOTABIT;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasalign(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 ||
		(sbp->sb_versionnum & XFS_SB_VERSION_ALIGNBIT));
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasdalign(काष्ठा xfs_sb *sbp)
अणु
	वापस (sbp->sb_versionnum & XFS_SB_VERSION_DALIGNBIT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_haslogv2(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 ||
	       (sbp->sb_versionnum & XFS_SB_VERSION_LOGV2BIT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hassector(काष्ठा xfs_sb *sbp)
अणु
	वापस (sbp->sb_versionnum & XFS_SB_VERSION_SECTORBIT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasasciici(काष्ठा xfs_sb *sbp)
अणु
	वापस (sbp->sb_versionnum & XFS_SB_VERSION_BORGBIT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hयंत्रorebits(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 ||
	       (sbp->sb_versionnum & XFS_SB_VERSION_MOREBITSBIT);
पूर्ण

/*
 * sb_features2 bit version macros.
 */
अटल अंतरभूत bool xfs_sb_version_haslazysbcount(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) ||
	       (xfs_sb_version_hयंत्रorebits(sbp) &&
		(sbp->sb_features2 & XFS_SB_VERSION2_LAZYSBCOUNTBIT));
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasattr2(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) ||
	       (xfs_sb_version_hयंत्रorebits(sbp) &&
		(sbp->sb_features2 & XFS_SB_VERSION2_ATTR2BIT));
पूर्ण

अटल अंतरभूत व्योम xfs_sb_version_addattr2(काष्ठा xfs_sb *sbp)
अणु
	sbp->sb_versionnum |= XFS_SB_VERSION_MOREBITSBIT;
	sbp->sb_features2 |= XFS_SB_VERSION2_ATTR2BIT;
पूर्ण

अटल अंतरभूत व्योम xfs_sb_version_हटाओattr2(काष्ठा xfs_sb *sbp)
अणु
	sbp->sb_features2 &= ~XFS_SB_VERSION2_ATTR2BIT;
	अगर (!sbp->sb_features2)
		sbp->sb_versionnum &= ~XFS_SB_VERSION_MOREBITSBIT;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasprojid32bit(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) ||
	       (xfs_sb_version_hयंत्रorebits(sbp) &&
		(sbp->sb_features2 & XFS_SB_VERSION2_PROJID32BIT));
पूर्ण

अटल अंतरभूत व्योम xfs_sb_version_addprojid32bit(काष्ठा xfs_sb *sbp)
अणु
	sbp->sb_versionnum |= XFS_SB_VERSION_MOREBITSBIT;
	sbp->sb_features2 |= XFS_SB_VERSION2_PROJID32BIT;
पूर्ण

/*
 * Extended v5 superblock feature masks. These are to be used क्रम new v5
 * superblock features only.
 *
 * Compat features are new features that old kernels will not notice or affect
 * and so can mount पढ़ो-ग_लिखो without issues.
 *
 * RO-Compat (पढ़ो only) are features that old kernels can पढ़ो but will अवरोध
 * अगर they ग_लिखो. Hence only पढ़ो-only mounts of such fileप्रणालीs are allowed on
 * kernels that करोn't support the feature bit.
 *
 * InCompat features are features which old kernels will not understand and so
 * must not mount.
 *
 * Log-InCompat features are क्रम changes to log क्रमmats or new transactions that
 * can't be replayed on older kernels. The fields are set when the fileप्रणाली is
 * mounted, and a clean unmount clears the fields.
 */
#घोषणा XFS_SB_FEAT_COMPAT_ALL 0
#घोषणा XFS_SB_FEAT_COMPAT_UNKNOWN	~XFS_SB_FEAT_COMPAT_ALL
अटल अंतरभूत bool
xfs_sb_has_compat_feature(
	काष्ठा xfs_sb	*sbp,
	uपूर्णांक32_t	feature)
अणु
	वापस (sbp->sb_features_compat & feature) != 0;
पूर्ण

#घोषणा XFS_SB_FEAT_RO_COMPAT_FINOBT   (1 << 0)		/* मुक्त inode btree */
#घोषणा XFS_SB_FEAT_RO_COMPAT_RMAPBT   (1 << 1)		/* reverse map btree */
#घोषणा XFS_SB_FEAT_RO_COMPAT_REFLINK  (1 << 2)		/* reflinked files */
#घोषणा XFS_SB_FEAT_RO_COMPAT_INOBTCNT (1 << 3)		/* inobt block counts */
#घोषणा XFS_SB_FEAT_RO_COMPAT_ALL \
		(XFS_SB_FEAT_RO_COMPAT_FINOBT | \
		 XFS_SB_FEAT_RO_COMPAT_RMAPBT | \
		 XFS_SB_FEAT_RO_COMPAT_REFLINK| \
		 XFS_SB_FEAT_RO_COMPAT_INOBTCNT)
#घोषणा XFS_SB_FEAT_RO_COMPAT_UNKNOWN	~XFS_SB_FEAT_RO_COMPAT_ALL
अटल अंतरभूत bool
xfs_sb_has_ro_compat_feature(
	काष्ठा xfs_sb	*sbp,
	uपूर्णांक32_t	feature)
अणु
	वापस (sbp->sb_features_ro_compat & feature) != 0;
पूर्ण

#घोषणा XFS_SB_FEAT_INCOMPAT_FTYPE	(1 << 0)	/* filetype in dirent */
#घोषणा XFS_SB_FEAT_INCOMPAT_SPINODES	(1 << 1)	/* sparse inode chunks */
#घोषणा XFS_SB_FEAT_INCOMPAT_META_UUID	(1 << 2)	/* metadata UUID */
#घोषणा XFS_SB_FEAT_INCOMPAT_BIGTIME	(1 << 3)	/* large बारtamps */
#घोषणा XFS_SB_FEAT_INCOMPAT_NEEDSREPAIR (1 << 4)	/* needs xfs_repair */
#घोषणा XFS_SB_FEAT_INCOMPAT_ALL \
		(XFS_SB_FEAT_INCOMPAT_FTYPE|	\
		 XFS_SB_FEAT_INCOMPAT_SPINODES|	\
		 XFS_SB_FEAT_INCOMPAT_META_UUID| \
		 XFS_SB_FEAT_INCOMPAT_BIGTIME| \
		 XFS_SB_FEAT_INCOMPAT_NEEDSREPAIR)

#घोषणा XFS_SB_FEAT_INCOMPAT_UNKNOWN	~XFS_SB_FEAT_INCOMPAT_ALL
अटल अंतरभूत bool
xfs_sb_has_incompat_feature(
	काष्ठा xfs_sb	*sbp,
	uपूर्णांक32_t	feature)
अणु
	वापस (sbp->sb_features_incompat & feature) != 0;
पूर्ण

#घोषणा XFS_SB_FEAT_INCOMPAT_LOG_ALL 0
#घोषणा XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN	~XFS_SB_FEAT_INCOMPAT_LOG_ALL
अटल अंतरभूत bool
xfs_sb_has_incompat_log_feature(
	काष्ठा xfs_sb	*sbp,
	uपूर्णांक32_t	feature)
अणु
	वापस (sbp->sb_features_log_incompat & feature) != 0;
पूर्ण

/*
 * V5 superblock specअगरic feature checks
 */
अटल अंतरभूत bool xfs_sb_version_hascrc(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5;
पूर्ण

/*
 * v5 file प्रणालीs support V3 inodes only, earlier file प्रणालीs support
 * v2 and v1 inodes.
 */
अटल अंतरभूत bool xfs_sb_version_has_v3inode(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5;
पूर्ण

अटल अंतरभूत bool xfs_dinode_good_version(काष्ठा xfs_sb *sbp,
		uपूर्णांक8_t version)
अणु
	अगर (xfs_sb_version_has_v3inode(sbp))
		वापस version == 3;
	वापस version == 1 || version == 2;
पूर्ण

अटल अंतरभूत bool xfs_sb_version_has_pquotino(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5;
पूर्ण

अटल अंतरभूत पूर्णांक xfs_sb_version_hasftype(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		xfs_sb_has_incompat_feature(sbp, XFS_SB_FEAT_INCOMPAT_FTYPE)) ||
	       (xfs_sb_version_hयंत्रorebits(sbp) &&
		 (sbp->sb_features2 & XFS_SB_VERSION2_FTYPE));
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasfinobt(xfs_sb_t *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) &&
		(sbp->sb_features_ro_compat & XFS_SB_FEAT_RO_COMPAT_FINOBT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hassparseinodes(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		xfs_sb_has_incompat_feature(sbp, XFS_SB_FEAT_INCOMPAT_SPINODES);
पूर्ण

/*
 * XFS_SB_FEAT_INCOMPAT_META_UUID indicates that the metadata UUID
 * is stored separately from the user-visible UUID; this allows the
 * user-visible UUID to be changed on V5 fileप्रणालीs which have a
 * fileप्रणाली UUID stamped पूर्णांकo every piece of metadata.
 */
अटल अंतरभूत bool xfs_sb_version_hयंत्रetauuid(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) &&
		(sbp->sb_features_incompat & XFS_SB_FEAT_INCOMPAT_META_UUID);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasrmapbt(काष्ठा xfs_sb *sbp)
अणु
	वापस (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5) &&
		(sbp->sb_features_ro_compat & XFS_SB_FEAT_RO_COMPAT_RMAPBT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasreflink(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		(sbp->sb_features_ro_compat & XFS_SB_FEAT_RO_COMPAT_REFLINK);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_hasbigसमय(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		(sbp->sb_features_incompat & XFS_SB_FEAT_INCOMPAT_BIGTIME);
पूर्ण

/*
 * Inode btree block counter.  We record the number of inobt and finobt blocks
 * in the AGI header so that we can skip the finobt walk at mount समय when
 * setting up per-AG reservations.
 */
अटल अंतरभूत bool xfs_sb_version_hasinobtcounts(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		(sbp->sb_features_ro_compat & XFS_SB_FEAT_RO_COMPAT_INOBTCNT);
पूर्ण

अटल अंतरभूत bool xfs_sb_version_needsrepair(काष्ठा xfs_sb *sbp)
अणु
	वापस XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		(sbp->sb_features_incompat & XFS_SB_FEAT_INCOMPAT_NEEDSREPAIR);
पूर्ण

/*
 * end of superblock version macros
 */

अटल अंतरभूत bool
xfs_is_quota_inode(काष्ठा xfs_sb *sbp, xfs_ino_t ino)
अणु
	वापस (ino == sbp->sb_uquotino ||
		ino == sbp->sb_gquotino ||
		ino == sbp->sb_pquotino);
पूर्ण

#घोषणा XFS_SB_DADDR		((xfs_daddr_t)0) /* daddr in fileप्रणाली/ag */
#घोषणा	XFS_SB_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_SB_DADDR)

#घोषणा	XFS_HDR_BLOCK(mp,d)	((xfs_agblock_t)XFS_BB_TO_FSBT(mp,d))
#घोषणा	XFS_DADDR_TO_FSB(mp,d)	XFS_AGB_TO_FSB(mp, \
			xfs_daddr_to_agno(mp,d), xfs_daddr_to_agbno(mp,d))
#घोषणा	XFS_FSB_TO_DADDR(mp,fsbno)	XFS_AGB_TO_DADDR(mp, \
			XFS_FSB_TO_AGNO(mp,fsbno), XFS_FSB_TO_AGBNO(mp,fsbno))

/*
 * File प्रणाली sector to basic block conversions.
 */
#घोषणा XFS_FSS_TO_BB(mp,sec)	((sec) << (mp)->m_sectbb_log)

/*
 * File प्रणाली block to basic block conversions.
 */
#घोषणा	XFS_FSB_TO_BB(mp,fsbno)	((fsbno) << (mp)->m_blkbb_log)
#घोषणा	XFS_BB_TO_FSB(mp,bb)	\
	(((bb) + (XFS_FSB_TO_BB(mp,1) - 1)) >> (mp)->m_blkbb_log)
#घोषणा	XFS_BB_TO_FSBT(mp,bb)	((bb) >> (mp)->m_blkbb_log)

/*
 * File प्रणाली block to byte conversions.
 */
#घोषणा XFS_FSB_TO_B(mp,fsbno)	((xfs_fमाप_प्रकार)(fsbno) << (mp)->m_sb.sb_blocklog)
#घोषणा XFS_B_TO_FSB(mp,b)	\
	((((uपूर्णांक64_t)(b)) + (mp)->m_blockmask) >> (mp)->m_sb.sb_blocklog)
#घोषणा XFS_B_TO_FSBT(mp,b)	(((uपूर्णांक64_t)(b)) >> (mp)->m_sb.sb_blocklog)

/*
 * Allocation group header
 *
 * This is भागided पूर्णांकo three काष्ठाures, placed in sequential 512-byte
 * buffers after a copy of the superblock (also in a 512-byte buffer).
 */
#घोषणा	XFS_AGF_MAGIC	0x58414746	/* 'XAGF' */
#घोषणा	XFS_AGI_MAGIC	0x58414749	/* 'XAGI' */
#घोषणा	XFS_AGFL_MAGIC	0x5841464c	/* 'XAFL' */
#घोषणा	XFS_AGF_VERSION	1
#घोषणा	XFS_AGI_VERSION	1

#घोषणा	XFS_AGF_GOOD_VERSION(v)	((v) == XFS_AGF_VERSION)
#घोषणा	XFS_AGI_GOOD_VERSION(v)	((v) == XFS_AGI_VERSION)

/*
 * Btree number 0 is bno, 1 is cnt, 2 is rmap. This value gives the size of the
 * arrays below.
 */
#घोषणा	XFS_BTNUM_AGF	((पूर्णांक)XFS_BTNUM_RMAPi + 1)

/*
 * The second word of agf_levels in the first a.g. overlaps the EFS
 * superblock's magic number.  Since the magic numbers valid क्रम EFS
 * are > 64k, our value cannot be confused क्रम an EFS superblock's.
 */

प्रकार काष्ठा xfs_agf अणु
	/*
	 * Common allocation group header inक्रमmation
	 */
	__be32		agf_magicnum;	/* magic number == XFS_AGF_MAGIC */
	__be32		agf_versionnum;	/* header version == XFS_AGF_VERSION */
	__be32		agf_seqno;	/* sequence # starting from 0 */
	__be32		agf_length;	/* size in blocks of a.g. */
	/*
	 * Freespace and rmap inक्रमmation
	 */
	__be32		agf_roots[XFS_BTNUM_AGF];	/* root blocks */
	__be32		agf_levels[XFS_BTNUM_AGF];	/* btree levels */

	__be32		agf_flfirst;	/* first मुक्तlist block's index */
	__be32		agf_fllast;	/* last मुक्तlist block's index */
	__be32		agf_flcount;	/* count of blocks in मुक्तlist */
	__be32		agf_मुक्तblks;	/* total मुक्त blocks */

	__be32		agf_दीर्घest;	/* दीर्घest मुक्त space */
	__be32		agf_btreeblks;	/* # of blocks held in AGF btrees */
	uuid_t		agf_uuid;	/* uuid of fileप्रणाली */

	__be32		agf_rmap_blocks;	/* rmapbt blocks used */
	__be32		agf_refcount_blocks;	/* refcountbt blocks used */

	__be32		agf_refcount_root;	/* refcount tree root block */
	__be32		agf_refcount_level;	/* refcount btree levels */

	/*
	 * reserve some contiguous space क्रम future logged fields beक्रमe we add
	 * the unlogged fields. This makes the range logging via flags and
	 * काष्ठाure offsets much simpler.
	 */
	__be64		agf_spare64[14];

	/* unlogged fields, written during buffer ग_लिखोback. */
	__be64		agf_lsn;	/* last ग_लिखो sequence */
	__be32		agf_crc;	/* crc of agf sector */
	__be32		agf_spare2;

	/* काष्ठाure must be padded to 64 bit alignment */
पूर्ण xfs_agf_t;

#घोषणा XFS_AGF_CRC_OFF		दुरत्व(काष्ठा xfs_agf, agf_crc)

#घोषणा	XFS_AGF_MAGICNUM	0x00000001
#घोषणा	XFS_AGF_VERSIONNUM	0x00000002
#घोषणा	XFS_AGF_SEQNO		0x00000004
#घोषणा	XFS_AGF_LENGTH		0x00000008
#घोषणा	XFS_AGF_ROOTS		0x00000010
#घोषणा	XFS_AGF_LEVELS		0x00000020
#घोषणा	XFS_AGF_FLFIRST		0x00000040
#घोषणा	XFS_AGF_FLLAST		0x00000080
#घोषणा	XFS_AGF_FLCOUNT		0x00000100
#घोषणा	XFS_AGF_FREEBLKS	0x00000200
#घोषणा	XFS_AGF_LONGEST		0x00000400
#घोषणा	XFS_AGF_BTREEBLKS	0x00000800
#घोषणा	XFS_AGF_UUID		0x00001000
#घोषणा	XFS_AGF_RMAP_BLOCKS	0x00002000
#घोषणा	XFS_AGF_REFCOUNT_BLOCKS	0x00004000
#घोषणा	XFS_AGF_REFCOUNT_ROOT	0x00008000
#घोषणा	XFS_AGF_REFCOUNT_LEVEL	0x00010000
#घोषणा	XFS_AGF_SPARE64		0x00020000
#घोषणा	XFS_AGF_NUM_BITS	18
#घोषणा	XFS_AGF_ALL_BITS	((1 << XFS_AGF_NUM_BITS) - 1)

#घोषणा XFS_AGF_FLAGS \
	अणु XFS_AGF_MAGICNUM,	"MAGICNUM" पूर्ण, \
	अणु XFS_AGF_VERSIONNUM,	"VERSIONNUM" पूर्ण, \
	अणु XFS_AGF_SEQNO,	"SEQNO" पूर्ण, \
	अणु XFS_AGF_LENGTH,	"LENGTH" पूर्ण, \
	अणु XFS_AGF_ROOTS,	"ROOTS" पूर्ण, \
	अणु XFS_AGF_LEVELS,	"LEVELS" पूर्ण, \
	अणु XFS_AGF_FLFIRST,	"FLFIRST" पूर्ण, \
	अणु XFS_AGF_FLLAST,	"FLLAST" पूर्ण, \
	अणु XFS_AGF_FLCOUNT,	"FLCOUNT" पूर्ण, \
	अणु XFS_AGF_FREEBLKS,	"FREEBLKS" पूर्ण, \
	अणु XFS_AGF_LONGEST,	"LONGEST" पूर्ण, \
	अणु XFS_AGF_BTREEBLKS,	"BTREEBLKS" पूर्ण, \
	अणु XFS_AGF_UUID,		"UUID" पूर्ण, \
	अणु XFS_AGF_RMAP_BLOCKS,	"RMAP_BLOCKS" पूर्ण, \
	अणु XFS_AGF_REFCOUNT_BLOCKS,	"REFCOUNT_BLOCKS" पूर्ण, \
	अणु XFS_AGF_REFCOUNT_ROOT,	"REFCOUNT_ROOT" पूर्ण, \
	अणु XFS_AGF_REFCOUNT_LEVEL,	"REFCOUNT_LEVEL" पूर्ण, \
	अणु XFS_AGF_SPARE64,	"SPARE64" पूर्ण

/* disk block (xfs_daddr_t) in the AG */
#घोषणा XFS_AGF_DADDR(mp)	((xfs_daddr_t)(1 << (mp)->m_sectbb_log))
#घोषणा	XFS_AGF_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGF_DADDR(mp))

/*
 * Size of the unlinked inode hash table in the agi.
 */
#घोषणा	XFS_AGI_UNLINKED_BUCKETS	64

प्रकार काष्ठा xfs_agi अणु
	/*
	 * Common allocation group header inक्रमmation
	 */
	__be32		agi_magicnum;	/* magic number == XFS_AGI_MAGIC */
	__be32		agi_versionnum;	/* header version == XFS_AGI_VERSION */
	__be32		agi_seqno;	/* sequence # starting from 0 */
	__be32		agi_length;	/* size in blocks of a.g. */
	/*
	 * Inode inक्रमmation
	 * Inodes are mapped by पूर्णांकerpreting the inode number, so no
	 * mapping data is needed here.
	 */
	__be32		agi_count;	/* count of allocated inodes */
	__be32		agi_root;	/* root of inode btree */
	__be32		agi_level;	/* levels in inode btree */
	__be32		agi_मुक्तcount;	/* number of मुक्त inodes */

	__be32		agi_newino;	/* new inode just allocated */
	__be32		agi_dirino;	/* last directory inode chunk */
	/*
	 * Hash table of inodes which have been unlinked but are
	 * still being referenced.
	 */
	__be32		agi_unlinked[XFS_AGI_UNLINKED_BUCKETS];
	/*
	 * This marks the end of logging region 1 and start of logging region 2.
	 */
	uuid_t		agi_uuid;	/* uuid of fileप्रणाली */
	__be32		agi_crc;	/* crc of agi sector */
	__be32		agi_pad32;
	__be64		agi_lsn;	/* last ग_लिखो sequence */

	__be32		agi_मुक्त_root; /* root of the मुक्त inode btree */
	__be32		agi_मुक्त_level;/* levels in मुक्त inode btree */

	__be32		agi_iblocks;	/* inobt blocks used */
	__be32		agi_fblocks;	/* finobt blocks used */

	/* काष्ठाure must be padded to 64 bit alignment */
पूर्ण xfs_agi_t;

#घोषणा XFS_AGI_CRC_OFF		दुरत्व(काष्ठा xfs_agi, agi_crc)

#घोषणा	XFS_AGI_MAGICNUM	(1 << 0)
#घोषणा	XFS_AGI_VERSIONNUM	(1 << 1)
#घोषणा	XFS_AGI_SEQNO		(1 << 2)
#घोषणा	XFS_AGI_LENGTH		(1 << 3)
#घोषणा	XFS_AGI_COUNT		(1 << 4)
#घोषणा	XFS_AGI_ROOT		(1 << 5)
#घोषणा	XFS_AGI_LEVEL		(1 << 6)
#घोषणा	XFS_AGI_FREECOUNT	(1 << 7)
#घोषणा	XFS_AGI_NEWINO		(1 << 8)
#घोषणा	XFS_AGI_सूचीINO		(1 << 9)
#घोषणा	XFS_AGI_UNLINKED	(1 << 10)
#घोषणा	XFS_AGI_NUM_BITS_R1	11	/* end of the 1st agi logging region */
#घोषणा	XFS_AGI_ALL_BITS_R1	((1 << XFS_AGI_NUM_BITS_R1) - 1)
#घोषणा	XFS_AGI_FREE_ROOT	(1 << 11)
#घोषणा	XFS_AGI_FREE_LEVEL	(1 << 12)
#घोषणा	XFS_AGI_IBLOCKS		(1 << 13) /* both inobt/finobt block counters */
#घोषणा	XFS_AGI_NUM_BITS_R2	14

/* disk block (xfs_daddr_t) in the AG */
#घोषणा XFS_AGI_DADDR(mp)	((xfs_daddr_t)(2 << (mp)->m_sectbb_log))
#घोषणा	XFS_AGI_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGI_DADDR(mp))

/*
 * The third a.g. block contains the a.g. मुक्तlist, an array
 * of block poपूर्णांकers to blocks owned by the allocation btree code.
 */
#घोषणा XFS_AGFL_DADDR(mp)	((xfs_daddr_t)(3 << (mp)->m_sectbb_log))
#घोषणा	XFS_AGFL_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGFL_DADDR(mp))
#घोषणा	XFS_BUF_TO_AGFL(bp)	((काष्ठा xfs_agfl *)((bp)->b_addr))

काष्ठा xfs_agfl अणु
	__be32		agfl_magicnum;
	__be32		agfl_seqno;
	uuid_t		agfl_uuid;
	__be64		agfl_lsn;
	__be32		agfl_crc;
पूर्ण __attribute__((packed));

#घोषणा XFS_AGFL_CRC_OFF	दुरत्व(काष्ठा xfs_agfl, agfl_crc)

#घोषणा XFS_AGB_TO_FSB(mp,agno,agbno)	\
	(((xfs_fsblock_t)(agno) << (mp)->m_sb.sb_agblklog) | (agbno))
#घोषणा	XFS_FSB_TO_AGNO(mp,fsbno)	\
	((xfs_agnumber_t)((fsbno) >> (mp)->m_sb.sb_agblklog))
#घोषणा	XFS_FSB_TO_AGBNO(mp,fsbno)	\
	((xfs_agblock_t)((fsbno) & xfs_mask32lo((mp)->m_sb.sb_agblklog)))
#घोषणा	XFS_AGB_TO_DADDR(mp,agno,agbno)	\
	((xfs_daddr_t)XFS_FSB_TO_BB(mp, \
		(xfs_fsblock_t)(agno) * (mp)->m_sb.sb_agblocks + (agbno)))
#घोषणा	XFS_AG_DADDR(mp,agno,d)		(XFS_AGB_TO_DADDR(mp, agno, 0) + (d))

/*
 * For checking क्रम bad ranges of xfs_daddr_t's, covering multiple
 * allocation groups or a single xfs_daddr_t that's a superblock copy.
 */
#घोषणा	XFS_AG_CHECK_DADDR(mp,d,len)	\
	((len) == 1 ? \
	    ASSERT((d) == XFS_SB_DADDR || \
		   xfs_daddr_to_agbno(mp, d) != XFS_SB_DADDR) : \
	    ASSERT(xfs_daddr_to_agno(mp, d) == \
		   xfs_daddr_to_agno(mp, (d) + (len) - 1)))

/*
 * XFS Timestamps
 * ==============
 *
 * Traditional ondisk inode बारtamps consist of चिन्हित 32-bit counters क्रम
 * seconds and nanoseconds; समय zero is the Unix epoch, Jan  1 00:00:00 UTC
 * 1970, which means that the बारtamp epoch is the same as the Unix epoch.
 * Thereक्रमe, the ondisk min and max defined here can be used directly to
 * स्थिरrain the incore बारtamps on a Unix प्रणाली.  Note that we actually
 * encode a __be64 value on disk.
 *
 * When the bigसमय feature is enabled, ondisk inode बारtamps become an
 * अचिन्हित 64-bit nanoseconds counter.  This means that the bigसमय inode
 * बारtamp epoch is the start of the classic बारtamp range, which is
 * Dec 31 20:45:52 UTC 1901.  Because the epochs are not the same, callers
 * /must/ use the bigसमय conversion functions when encoding and decoding raw
 * बारtamps.
 */
प्रकार __be64 xfs_बारtamp_t;

/* Legacy बारtamp encoding क्रमmat. */
काष्ठा xfs_legacy_बारtamp अणु
	__be32		t_sec;		/* बारtamp seconds */
	__be32		t_nsec;		/* बारtamp nanoseconds */
पूर्ण;

/*
 * Smallest possible ondisk seconds value with traditional बारtamps.  This
 * corresponds exactly with the incore बारtamp Dec 13 20:45:52 UTC 1901.
 */
#घोषणा XFS_LEGACY_TIME_MIN	((पूर्णांक64_t)S32_MIN)

/*
 * Largest possible ondisk seconds value with traditional बारtamps.  This
 * corresponds exactly with the incore बारtamp Jan 19 03:14:07 UTC 2038.
 */
#घोषणा XFS_LEGACY_TIME_MAX	((पूर्णांक64_t)S32_MAX)

/*
 * Smallest possible ondisk seconds value with bigसमय बारtamps.  This
 * corresponds (after conversion to a Unix बारtamp) with the traditional
 * minimum बारtamp of Dec 13 20:45:52 UTC 1901.
 */
#घोषणा XFS_BIGTIME_TIME_MIN	((पूर्णांक64_t)0)

/*
 * Largest supported ondisk seconds value with bigसमय बारtamps.  This
 * corresponds (after conversion to a Unix बारtamp) with an incore बारtamp
 * of Jul  2 20:20:24 UTC 2486.
 *
 * We round करोwn the ondisk limit so that the bigसमय quota and inode max
 * बारtamps will be the same.
 */
#घोषणा XFS_BIGTIME_TIME_MAX	((पूर्णांक64_t)((-1ULL / NSEC_PER_SEC) & ~0x3ULL))

/*
 * Bigसमय epoch is set exactly to the minimum समय value that a traditional
 * 32-bit बारtamp can represent when using the Unix epoch as a reference.
 * Hence the Unix epoch is at a fixed offset पूर्णांकo the supported bigसमय
 * बारtamp range.
 *
 * The bigसमय epoch also matches the minimum value an on-disk 32-bit XFS
 * बारtamp can represent so we will not lose any fidelity in converting
 * to/from unix and bigसमय बारtamps.
 *
 * The following conversion factor converts a seconds counter from the Unix
 * epoch to the bigसमय epoch.
 */
#घोषणा XFS_BIGTIME_EPOCH_OFFSET	(-(पूर्णांक64_t)S32_MIN)

/* Convert a बारtamp from the Unix epoch to the bigसमय epoch. */
अटल अंतरभूत uपूर्णांक64_t xfs_unix_to_bigसमय(समय64_t unix_seconds)
अणु
	वापस (uपूर्णांक64_t)unix_seconds + XFS_BIGTIME_EPOCH_OFFSET;
पूर्ण

/* Convert a बारtamp from the bigसमय epoch to the Unix epoch. */
अटल अंतरभूत समय64_t xfs_bigसमय_प्रकारo_unix(uपूर्णांक64_t ondisk_seconds)
अणु
	वापस (समय64_t)ondisk_seconds - XFS_BIGTIME_EPOCH_OFFSET;
पूर्ण

/*
 * On-disk inode काष्ठाure.
 *
 * This is just the header or "dinode core", the inode is expanded to fill a
 * variable size the leftover area split पूर्णांकo a data and an attribute विभाजन.
 * The क्रमmat of the data and attribute विभाजन depends on the क्रमmat of the
 * inode as indicated by di_क्रमmat and di_aक्रमmat.  To access the data and
 * attribute use the XFS_DFORK_DPTR, XFS_DFORK_APTR, and XFS_DFORK_PTR macros
 * below.
 *
 * There is a very similar काष्ठा xfs_log_dinode which matches the layout of
 * this काष्ठाure, but is kept in native क्रमmat instead of big endian.
 *
 * Note: di_flushiter is only used by v1/2 inodes - it's effectively a zeroed
 * padding field क्रम v3 inodes.
 */
#घोषणा	XFS_DINODE_MAGIC		0x494e	/* 'IN' */
प्रकार काष्ठा xfs_dinode अणु
	__be16		di_magic;	/* inode magic # = XFS_DINODE_MAGIC */
	__be16		di_mode;	/* mode and type of file */
	__u8		di_version;	/* inode version */
	__u8		di_क्रमmat;	/* क्रमmat of di_c data */
	__be16		di_onlink;	/* old number of links to file */
	__be32		di_uid;		/* owner's user id */
	__be32		di_gid;		/* owner's group id */
	__be32		di_nlink;	/* number of links to file */
	__be16		di_projid_lo;	/* lower part of owner's project id */
	__be16		di_projid_hi;	/* higher part owner's project id */
	__u8		di_pad[6];	/* unused, zeroed space */
	__be16		di_flushiter;	/* incremented on flush */
	xfs_बारtamp_t	di_aसमय;	/* समय last accessed */
	xfs_बारtamp_t	di_mसमय;	/* समय last modअगरied */
	xfs_बारtamp_t	di_स_समय;	/* समय created/inode modअगरied */
	__be64		di_size;	/* number of bytes in file */
	__be64		di_nblocks;	/* # of direct & btree blocks used */
	__be32		di_extsize;	/* basic/minimum extent size क्रम file */
	__be32		di_nextents;	/* number of extents in data विभाजन */
	__be16		di_anextents;	/* number of extents in attribute विभाजन*/
	__u8		di_विभाजनoff;	/* attr विभाजन offs, <<3 क्रम 64b align */
	__s8		di_aक्रमmat;	/* क्रमmat of attr विभाजन's data */
	__be32		di_dmevmask;	/* DMIG event mask */
	__be16		di_dmstate;	/* DMIG state info */
	__be16		di_flags;	/* अक्रमom flags, XFS_DIFLAG_... */
	__be32		di_gen;		/* generation number */

	/* di_next_unlinked is the only non-core field in the old dinode */
	__be32		di_next_unlinked;/* agi unlinked list ptr */

	/* start of the extended dinode, writable fields */
	__le32		di_crc;		/* CRC of the inode */
	__be64		di_changecount;	/* number of attribute changes */
	__be64		di_lsn;		/* flush sequence */
	__be64		di_flags2;	/* more अक्रमom flags */
	__be32		di_cowextsize;	/* basic cow extent size क्रम file */
	__u8		di_pad2[12];	/* more padding क्रम future expansion */

	/* fields only written to during inode creation */
	xfs_बारtamp_t	di_crसमय;	/* समय created */
	__be64		di_ino;		/* inode number */
	uuid_t		di_uuid;	/* UUID of the fileप्रणाली */

	/* काष्ठाure must be padded to 64 bit alignment */
पूर्ण xfs_dinode_t;

#घोषणा XFS_DINODE_CRC_OFF	दुरत्व(काष्ठा xfs_dinode, di_crc)

#घोषणा DI_MAX_FLUSH 0xffff

/*
 * Size of the core inode on disk.  Version 1 and 2 inodes have
 * the same size, but version 3 has grown a few additional fields.
 */
अटल अंतरभूत uपूर्णांक xfs_dinode_size(पूर्णांक version)
अणु
	अगर (version == 3)
		वापस माप(काष्ठा xfs_dinode);
	वापस दुरत्व(काष्ठा xfs_dinode, di_crc);
पूर्ण

/*
 * The 32 bit link count in the inode theoretically maxes out at अच_पूर्णांक_उच्च.
 * Since the pathconf पूर्णांकerface is चिन्हित, we use 2^31 - 1 instead.
 */
#घोषणा	XFS_MAXLINK		((1U << 31) - 1U)

/*
 * Values क्रम di_क्रमmat
 *
 * This क्रमागत is used in string mapping in xfs_trace.h; please keep the
 * TRACE_DEFINE_ENUMs क्रम it up to date.
 */
क्रमागत xfs_dinode_fmt अणु
	XFS_DINODE_FMT_DEV,		/* xfs_dev_t */
	XFS_DINODE_FMT_LOCAL,		/* bulk data */
	XFS_DINODE_FMT_EXTENTS,		/* काष्ठा xfs_bmbt_rec */
	XFS_DINODE_FMT_BTREE,		/* काष्ठा xfs_bmdr_block */
	XFS_DINODE_FMT_UUID		/* added दीर्घ ago, but never used */
पूर्ण;

#घोषणा XFS_INODE_FORMAT_STR \
	अणु XFS_DINODE_FMT_DEV,		"dev" पूर्ण, \
	अणु XFS_DINODE_FMT_LOCAL,		"local" पूर्ण, \
	अणु XFS_DINODE_FMT_EXTENTS,	"extent" पूर्ण, \
	अणु XFS_DINODE_FMT_BTREE,		"btree" पूर्ण, \
	अणु XFS_DINODE_FMT_UUID,		"uuid" पूर्ण

/*
 * Inode minimum and maximum sizes.
 */
#घोषणा	XFS_DINODE_MIN_LOG	8
#घोषणा	XFS_DINODE_MAX_LOG	11
#घोषणा	XFS_DINODE_MIN_SIZE	(1 << XFS_DINODE_MIN_LOG)
#घोषणा	XFS_DINODE_MAX_SIZE	(1 << XFS_DINODE_MAX_LOG)

/*
 * Inode size क्रम given fs.
 */
#घोषणा XFS_DINODE_SIZE(sbp) \
	(xfs_sb_version_has_v3inode(sbp) ? \
		माप(काष्ठा xfs_dinode) : \
		दुरत्व(काष्ठा xfs_dinode, di_crc))
#घोषणा XFS_LITINO(mp) \
	((mp)->m_sb.sb_inodesize - XFS_DINODE_SIZE(&(mp)->m_sb))

/*
 * Inode data & attribute विभाजन sizes, per inode.
 */
#घोषणा XFS_DFORK_BOFF(dip)		((पूर्णांक)((dip)->di_विभाजनoff << 3))

#घोषणा XFS_DFORK_DSIZE(dip,mp) \
	((dip)->di_विभाजनoff ? XFS_DFORK_BOFF(dip) : XFS_LITINO(mp))
#घोषणा XFS_DFORK_ASIZE(dip,mp) \
	((dip)->di_विभाजनoff ? XFS_LITINO(mp) - XFS_DFORK_BOFF(dip) : 0)
#घोषणा XFS_DFORK_SIZE(dip,mp,w) \
	((w) == XFS_DATA_FORK ? \
		XFS_DFORK_DSIZE(dip, mp) : \
		XFS_DFORK_ASIZE(dip, mp))

#घोषणा XFS_DFORK_MAXEXT(dip, mp, w) \
	(XFS_DFORK_SIZE(dip, mp, w) / माप(काष्ठा xfs_bmbt_rec))

/*
 * Return poपूर्णांकers to the data or attribute विभाजनs.
 */
#घोषणा XFS_DFORK_DPTR(dip) \
	((अक्षर *)dip + xfs_dinode_size(dip->di_version))
#घोषणा XFS_DFORK_APTR(dip)	\
	(XFS_DFORK_DPTR(dip) + XFS_DFORK_BOFF(dip))
#घोषणा XFS_DFORK_PTR(dip,w)	\
	((w) == XFS_DATA_FORK ? XFS_DFORK_DPTR(dip) : XFS_DFORK_APTR(dip))

#घोषणा XFS_DFORK_FORMAT(dip,w) \
	((w) == XFS_DATA_FORK ? \
		(dip)->di_क्रमmat : \
		(dip)->di_aक्रमmat)
#घोषणा XFS_DFORK_NEXTENTS(dip,w) \
	((w) == XFS_DATA_FORK ? \
		be32_to_cpu((dip)->di_nextents) : \
		be16_to_cpu((dip)->di_anextents))

/*
 * For block and अक्षरacter special files the 32bit dev_t is stored at the
 * beginning of the data विभाजन.
 */
अटल अंतरभूत xfs_dev_t xfs_dinode_get_rdev(काष्ठा xfs_dinode *dip)
अणु
	वापस be32_to_cpu(*(__be32 *)XFS_DFORK_DPTR(dip));
पूर्ण

अटल अंतरभूत व्योम xfs_dinode_put_rdev(काष्ठा xfs_dinode *dip, xfs_dev_t rdev)
अणु
	*(__be32 *)XFS_DFORK_DPTR(dip) = cpu_to_be32(rdev);
पूर्ण

/*
 * Values क्रम di_flags
 */
#घोषणा XFS_DIFLAG_REALTIME_BIT  0	/* file's blocks come from rt area */
#घोषणा XFS_DIFLAG_PREALLOC_BIT  1	/* file space has been pपुनः_स्मृतिated */
#घोषणा XFS_DIFLAG_NEWRTBM_BIT   2	/* क्रम rtbiपंचांगap inode, new क्रमmat */
#घोषणा XFS_DIFLAG_IMMUTABLE_BIT 3	/* inode is immutable */
#घोषणा XFS_DIFLAG_APPEND_BIT    4	/* inode is append-only */
#घोषणा XFS_DIFLAG_SYNC_BIT      5	/* inode is written synchronously */
#घोषणा XFS_DIFLAG_NOATIME_BIT   6	/* करो not update aसमय */
#घोषणा XFS_DIFLAG_NODUMP_BIT    7	/* करो not dump */
#घोषणा XFS_DIFLAG_RTINHERIT_BIT 8	/* create with realसमय bit set */
#घोषणा XFS_DIFLAG_PROJINHERIT_BIT   9	/* create with parents projid */
#घोषणा XFS_DIFLAG_NOSYMLINKS_BIT   10	/* disallow symlink creation */
#घोषणा XFS_DIFLAG_EXTSIZE_BIT      11	/* inode extent size allocator hपूर्णांक */
#घोषणा XFS_DIFLAG_EXTSZINHERIT_BIT 12	/* inherit inode extent size */
#घोषणा XFS_DIFLAG_NODEFRAG_BIT     13	/* करो not reorganize/defragment */
#घोषणा XFS_DIFLAG_खाताSTREAM_BIT   14  /* use filestream allocator */
/* Do not use bit 15, di_flags is legacy and unchanging now */

#घोषणा XFS_DIFLAG_REALTIME      (1 << XFS_DIFLAG_REALTIME_BIT)
#घोषणा XFS_DIFLAG_PREALLOC      (1 << XFS_DIFLAG_PREALLOC_BIT)
#घोषणा XFS_DIFLAG_NEWRTBM       (1 << XFS_DIFLAG_NEWRTBM_BIT)
#घोषणा XFS_DIFLAG_IMMUTABLE     (1 << XFS_DIFLAG_IMMUTABLE_BIT)
#घोषणा XFS_DIFLAG_APPEND        (1 << XFS_DIFLAG_APPEND_BIT)
#घोषणा XFS_DIFLAG_SYNC          (1 << XFS_DIFLAG_SYNC_BIT)
#घोषणा XFS_DIFLAG_NOATIME       (1 << XFS_DIFLAG_NOATIME_BIT)
#घोषणा XFS_DIFLAG_NODUMP        (1 << XFS_DIFLAG_NODUMP_BIT)
#घोषणा XFS_DIFLAG_RTINHERIT     (1 << XFS_DIFLAG_RTINHERIT_BIT)
#घोषणा XFS_DIFLAG_PROJINHERIT   (1 << XFS_DIFLAG_PROJINHERIT_BIT)
#घोषणा XFS_DIFLAG_NOSYMLINKS    (1 << XFS_DIFLAG_NOSYMLINKS_BIT)
#घोषणा XFS_DIFLAG_EXTSIZE       (1 << XFS_DIFLAG_EXTSIZE_BIT)
#घोषणा XFS_DIFLAG_EXTSZINHERIT  (1 << XFS_DIFLAG_EXTSZINHERIT_BIT)
#घोषणा XFS_DIFLAG_NODEFRAG      (1 << XFS_DIFLAG_NODEFRAG_BIT)
#घोषणा XFS_DIFLAG_खाताSTREAM    (1 << XFS_DIFLAG_खाताSTREAM_BIT)

#घोषणा XFS_DIFLAG_ANY \
	(XFS_DIFLAG_REALTIME | XFS_DIFLAG_PREALLOC | XFS_DIFLAG_NEWRTBM | \
	 XFS_DIFLAG_IMMUTABLE | XFS_DIFLAG_APPEND | XFS_DIFLAG_SYNC | \
	 XFS_DIFLAG_NOATIME | XFS_DIFLAG_NODUMP | XFS_DIFLAG_RTINHERIT | \
	 XFS_DIFLAG_PROJINHERIT | XFS_DIFLAG_NOSYMLINKS | XFS_DIFLAG_EXTSIZE | \
	 XFS_DIFLAG_EXTSZINHERIT | XFS_DIFLAG_NODEFRAG | XFS_DIFLAG_खाताSTREAM)

/*
 * Values क्रम di_flags2 These start by being exposed to userspace in the upper
 * 16 bits of the XFS_XFLAG_s range.
 */
#घोषणा XFS_DIFLAG2_DAX_BIT	0	/* use DAX क्रम this inode */
#घोषणा XFS_DIFLAG2_REFLINK_BIT	1	/* file's blocks may be shared */
#घोषणा XFS_DIFLAG2_COWEXTSIZE_BIT   2  /* copy on ग_लिखो extent size hपूर्णांक */
#घोषणा XFS_DIFLAG2_BIGTIME_BIT	3	/* big बारtamps */

#घोषणा XFS_DIFLAG2_DAX		(1 << XFS_DIFLAG2_DAX_BIT)
#घोषणा XFS_DIFLAG2_REFLINK     (1 << XFS_DIFLAG2_REFLINK_BIT)
#घोषणा XFS_DIFLAG2_COWEXTSIZE  (1 << XFS_DIFLAG2_COWEXTSIZE_BIT)
#घोषणा XFS_DIFLAG2_BIGTIME	(1 << XFS_DIFLAG2_BIGTIME_BIT)

#घोषणा XFS_DIFLAG2_ANY \
	(XFS_DIFLAG2_DAX | XFS_DIFLAG2_REFLINK | XFS_DIFLAG2_COWEXTSIZE | \
	 XFS_DIFLAG2_BIGTIME)

अटल अंतरभूत bool xfs_dinode_has_bigसमय(स्थिर काष्ठा xfs_dinode *dip)
अणु
	वापस dip->di_version >= 3 &&
	       (dip->di_flags2 & cpu_to_be64(XFS_DIFLAG2_BIGTIME));
पूर्ण

/*
 * Inode number क्रमmat:
 * low inopblog bits - offset in block
 * next agblklog bits - block number in ag
 * next agno_log bits - ag number
 * high agno_log-agblklog-inopblog bits - 0
 */
#घोषणा	XFS_INO_MASK(k)			(uपूर्णांक32_t)((1ULL << (k)) - 1)
#घोषणा	XFS_INO_OFFSET_BITS(mp)		(mp)->m_sb.sb_inopblog
#घोषणा	XFS_INO_AGBNO_BITS(mp)		(mp)->m_sb.sb_agblklog
#घोषणा	XFS_INO_AGINO_BITS(mp)		((mp)->m_ino_geo.agino_log)
#घोषणा	XFS_INO_AGNO_BITS(mp)		(mp)->m_agno_log
#घोषणा	XFS_INO_BITS(mp)		\
	XFS_INO_AGNO_BITS(mp) + XFS_INO_AGINO_BITS(mp)
#घोषणा	XFS_INO_TO_AGNO(mp,i)		\
	((xfs_agnumber_t)((i) >> XFS_INO_AGINO_BITS(mp)))
#घोषणा	XFS_INO_TO_AGINO(mp,i)		\
	((xfs_agino_t)(i) & XFS_INO_MASK(XFS_INO_AGINO_BITS(mp)))
#घोषणा	XFS_INO_TO_AGBNO(mp,i)		\
	(((xfs_agblock_t)(i) >> XFS_INO_OFFSET_BITS(mp)) & \
		XFS_INO_MASK(XFS_INO_AGBNO_BITS(mp)))
#घोषणा	XFS_INO_TO_OFFSET(mp,i)		\
	((पूर्णांक)(i) & XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
#घोषणा	XFS_INO_TO_FSB(mp,i)		\
	XFS_AGB_TO_FSB(mp, XFS_INO_TO_AGNO(mp,i), XFS_INO_TO_AGBNO(mp,i))
#घोषणा	XFS_AGINO_TO_INO(mp,a,i)	\
	(((xfs_ino_t)(a) << XFS_INO_AGINO_BITS(mp)) | (i))
#घोषणा	XFS_AGINO_TO_AGBNO(mp,i)	((i) >> XFS_INO_OFFSET_BITS(mp))
#घोषणा	XFS_AGINO_TO_OFFSET(mp,i)	\
	((i) & XFS_INO_MASK(XFS_INO_OFFSET_BITS(mp)))
#घोषणा	XFS_OFFBNO_TO_AGINO(mp,b,o)	\
	((xfs_agino_t)(((b) << XFS_INO_OFFSET_BITS(mp)) | (o)))
#घोषणा	XFS_FSB_TO_INO(mp, b)	((xfs_ino_t)((b) << XFS_INO_OFFSET_BITS(mp)))
#घोषणा	XFS_AGB_TO_AGINO(mp, b)	((xfs_agino_t)((b) << XFS_INO_OFFSET_BITS(mp)))

#घोषणा	XFS_MAXINUMBER		((xfs_ino_t)((1ULL << 56) - 1ULL))
#घोषणा	XFS_MAXINUMBER_32	((xfs_ino_t)((1ULL << 32) - 1ULL))

/*
 * RealTime Device क्रमmat definitions
 */

/* Min and max rt extent sizes, specअगरied in bytes */
#घोषणा	XFS_MAX_RTEXTSIZE	(1024 * 1024 * 1024)	/* 1GB */
#घोषणा	XFS_DFL_RTEXTSIZE	(64 * 1024)	        /* 64kB */
#घोषणा	XFS_MIN_RTEXTSIZE	(4 * 1024)		/* 4kB */

#घोषणा	XFS_BLOCKSIZE(mp)	((mp)->m_sb.sb_blocksize)
#घोषणा	XFS_BLOCKMASK(mp)	((mp)->m_blockmask)
#घोषणा	XFS_BLOCKWSIZE(mp)	((mp)->m_blockwsize)
#घोषणा	XFS_BLOCKWMASK(mp)	((mp)->m_blockwmask)

/*
 * RT Summary and bit manipulation macros.
 */
#घोषणा	XFS_SUMOFFS(mp,ls,bb)	((पूर्णांक)((ls) * (mp)->m_sb.sb_rbmblocks + (bb)))
#घोषणा	XFS_SUMOFFSTOBLOCK(mp,s)	\
	(((s) * (uपूर्णांक)माप(xfs_suminfo_t)) >> (mp)->m_sb.sb_blocklog)
#घोषणा	XFS_SUMPTR(mp,bp,so)	\
	((xfs_suminfo_t *)((bp)->b_addr + \
		(((so) * (uपूर्णांक)माप(xfs_suminfo_t)) & XFS_BLOCKMASK(mp))))

#घोषणा	XFS_BITTOBLOCK(mp,bi)	((bi) >> (mp)->m_blkbit_log)
#घोषणा	XFS_BLOCKTOBIT(mp,bb)	((bb) << (mp)->m_blkbit_log)
#घोषणा	XFS_BITTOWORD(mp,bi)	\
	((पूर्णांक)(((bi) >> XFS_NBWORDLOG) & XFS_BLOCKWMASK(mp)))

#घोषणा	XFS_RTMIN(a,b)	((a) < (b) ? (a) : (b))
#घोषणा	XFS_RTMAX(a,b)	((a) > (b) ? (a) : (b))

#घोषणा	XFS_RTLOBIT(w)	xfs_lowbit32(w)
#घोषणा	XFS_RTHIBIT(w)	xfs_highbit32(w)

#घोषणा	XFS_RTBLOCKLOG(b)	xfs_highbit64(b)

/*
 * Dquot and dquot block क्रमmat definitions
 */
#घोषणा XFS_DQUOT_MAGIC		0x4451		/* 'DQ' */
#घोषणा XFS_DQUOT_VERSION	(uपूर्णांक8_t)0x01	/* latest version number */

#घोषणा XFS_DQTYPE_USER		0x01		/* user dquot record */
#घोषणा XFS_DQTYPE_PROJ		0x02		/* project dquot record */
#घोषणा XFS_DQTYPE_GROUP	0x04		/* group dquot record */
#घोषणा XFS_DQTYPE_BIGTIME	0x80		/* large expiry बारtamps */

/* biपंचांगask to determine अगर this is a user/group/project dquot */
#घोषणा XFS_DQTYPE_REC_MASK	(XFS_DQTYPE_USER | \
				 XFS_DQTYPE_PROJ | \
				 XFS_DQTYPE_GROUP)

#घोषणा XFS_DQTYPE_ANY		(XFS_DQTYPE_REC_MASK | \
				 XFS_DQTYPE_BIGTIME)

/*
 * XFS Quota Timers
 * ================
 *
 * Traditional quota grace period expiration समयrs are an अचिन्हित 32-bit
 * seconds counter; समय zero is the Unix epoch, Jan  1 00:00:01 UTC 1970.
 * Note that an expiration value of zero means that the quota limit has not
 * been reached, and thereक्रमe no expiration has been set.  Thereक्रमe, the
 * ondisk min and max defined here can be used directly to स्थिरrain the incore
 * quota expiration बारtamps on a Unix प्रणाली.
 *
 * When bigसमय is enabled, we trade two bits of precision to expand the
 * expiration समयout range to match that of big inode बारtamps.  The min and
 * max recorded here are the on-disk limits, not a Unix बारtamp.
 *
 * The grace period क्रम each quota type is stored in the root dquot (id = 0)
 * and is applied to a non-root dquot when it exceeds the soft or hard limits.
 * The length of quota grace periods are अचिन्हित 32-bit quantities measured in
 * units of seconds.  A value of zero means to use the शेष period.
 */

/*
 * Smallest possible ondisk quota expiration value with traditional बारtamps.
 * This corresponds exactly with the incore expiration Jan  1 00:00:01 UTC 1970.
 */
#घोषणा XFS_DQ_LEGACY_EXPIRY_MIN	((पूर्णांक64_t)1)

/*
 * Largest possible ondisk quota expiration value with traditional बारtamps.
 * This corresponds exactly with the incore expiration Feb  7 06:28:15 UTC 2106.
 */
#घोषणा XFS_DQ_LEGACY_EXPIRY_MAX	((पूर्णांक64_t)U32_MAX)

/*
 * Smallest possible ondisk quota expiration value with bigसमय बारtamps.
 * This corresponds (after conversion to a Unix बारtamp) with the incore
 * expiration of Jan  1 00:00:04 UTC 1970.
 */
#घोषणा XFS_DQ_BIGTIME_EXPIRY_MIN	(XFS_DQ_LEGACY_EXPIRY_MIN)

/*
 * Largest supported ondisk quota expiration value with bigसमय बारtamps.
 * This corresponds (after conversion to a Unix बारtamp) with an incore
 * expiration of Jul  2 20:20:24 UTC 2486.
 *
 * The ondisk field supports values up to -1U, which corresponds to an incore
 * expiration in 2514.  This is beyond the maximum the bigसमय inode बारtamp,
 * so we cap the maximum bigसमय quota expiration to the max inode बारtamp.
 */
#घोषणा XFS_DQ_BIGTIME_EXPIRY_MAX	((पूर्णांक64_t)4074815106U)

/*
 * The following conversion factors assist in converting a quota expiration
 * बारtamp between the incore and ondisk क्रमmats.
 */
#घोषणा XFS_DQ_BIGTIME_SHIFT	(2)
#घोषणा XFS_DQ_BIGTIME_SLACK	((पूर्णांक64_t)(1ULL << XFS_DQ_BIGTIME_SHIFT) - 1)

/* Convert an incore quota expiration बारtamp to an ondisk bigसमय value. */
अटल अंतरभूत uपूर्णांक32_t xfs_dq_unix_to_bigसमय(समय64_t unix_seconds)
अणु
	/*
	 * Round the expiration बारtamp up to the nearest bigसमय बारtamp
	 * that we can store, to give users the most समय to fix problems.
	 */
	वापस ((uपूर्णांक64_t)unix_seconds + XFS_DQ_BIGTIME_SLACK) >>
			XFS_DQ_BIGTIME_SHIFT;
पूर्ण

/* Convert an ondisk bigसमय quota expiration value to an incore बारtamp. */
अटल अंतरभूत समय64_t xfs_dq_bigसमय_प्रकारo_unix(uपूर्णांक32_t ondisk_seconds)
अणु
	वापस (समय64_t)ondisk_seconds << XFS_DQ_BIGTIME_SHIFT;
पूर्ण

/*
 * Default quota grace periods, ranging from zero (use the compiled शेषs)
 * to ~136 years.  These are applied to a non-root dquot that has exceeded
 * either limit.
 */
#घोषणा XFS_DQ_GRACE_MIN		((पूर्णांक64_t)0)
#घोषणा XFS_DQ_GRACE_MAX		((पूर्णांक64_t)U32_MAX)

/*
 * This is the मुख्य portion of the on-disk representation of quota inक्रमmation
 * क्रम a user.  We pad this with some more expansion room to स्थिरruct the on
 * disk काष्ठाure.
 */
काष्ठा xfs_disk_dquot अणु
	__be16		d_magic;	/* dquot magic = XFS_DQUOT_MAGIC */
	__u8		d_version;	/* dquot version */
	__u8		d_type;		/* XFS_DQTYPE_USER/PROJ/GROUP */
	__be32		d_id;		/* user,project,group id */
	__be64		d_blk_hardlimit;/* असलolute limit on disk blks */
	__be64		d_blk_softlimit;/* preferred limit on disk blks */
	__be64		d_ino_hardlimit;/* maximum # allocated inodes */
	__be64		d_ino_softlimit;/* preferred inode limit */
	__be64		d_bcount;	/* disk blocks owned by the user */
	__be64		d_icount;	/* inodes owned by the user */
	__be32		d_iसमयr;	/* zero अगर within inode limits अगर not,
					   this is when we refuse service */
	__be32		d_bसमयr;	/* similar to above; क्रम disk blocks */
	__be16		d_iwarns;	/* warnings issued wrt num inodes */
	__be16		d_bwarns;	/* warnings issued wrt disk blocks */
	__be32		d_pad0;		/* 64 bit align */
	__be64		d_rtb_hardlimit;/* असलolute limit on realसमय blks */
	__be64		d_rtb_softlimit;/* preferred limit on RT disk blks */
	__be64		d_rtbcount;	/* realसमय blocks owned */
	__be32		d_rtbसमयr;	/* similar to above; क्रम RT disk blocks */
	__be16		d_rtbwarns;	/* warnings issued wrt RT disk blocks */
	__be16		d_pad;
पूर्ण;

/*
 * This is what goes on disk. This is separated from the xfs_disk_dquot because
 * carrying the unnecessary padding would be a waste of memory.
 */
प्रकार काष्ठा xfs_dqblk अणु
	काष्ठा xfs_disk_dquot	dd_diskdq; /* portion living incore as well */
	अक्षर			dd_fill[4];/* filling क्रम posterity */

	/*
	 * These two are only present on fileप्रणालीs with the CRC bits set.
	 */
	__be32		  dd_crc;	/* checksum */
	__be64		  dd_lsn;	/* last modअगरication in log */
	uuid_t		  dd_uuid;	/* location inक्रमmation */
पूर्ण xfs_dqblk_t;

#घोषणा XFS_DQUOT_CRC_OFF	दुरत्व(काष्ठा xfs_dqblk, dd_crc)

/*
 * This defines the unit of allocation of dquots.
 *
 * Currently, it is just one file प्रणाली block, and a 4K blk contains 30
 * (136 * 30 = 4080) dquots. It's probably not worth trying to make
 * this more dynamic.
 *
 * However, अगर this number is changed, we have to make sure that we करोn't
 * implicitly assume that we करो allocations in chunks of a single fileप्रणाली
 * block in the dquot/xqm code.
 *
 * This is part of the ondisk क्रमmat because the काष्ठाure size is not a घातer
 * of two, which leaves slack at the end of the disk block.
 */
#घोषणा XFS_DQUOT_CLUSTER_SIZE_FSB	(xfs_filblks_t)1

/*
 * Remote symlink क्रमmat and access functions.
 */
#घोषणा XFS_SYMLINK_MAGIC	0x58534c4d	/* XSLM */

काष्ठा xfs_dsymlink_hdr अणु
	__be32	sl_magic;
	__be32	sl_offset;
	__be32	sl_bytes;
	__be32	sl_crc;
	uuid_t	sl_uuid;
	__be64	sl_owner;
	__be64	sl_blkno;
	__be64	sl_lsn;
पूर्ण;

#घोषणा XFS_SYMLINK_CRC_OFF	दुरत्व(काष्ठा xfs_dsymlink_hdr, sl_crc)

#घोषणा XFS_SYMLINK_MAXLEN	1024
/*
 * The maximum pathlen is 1024 bytes. Since the minimum file प्रणाली
 * blocksize is 512 bytes, we can get a max of 3 extents back from
 * bmapi when crc headers are taken पूर्णांकo account.
 */
#घोषणा XFS_SYMLINK_MAPS 3

#घोषणा XFS_SYMLINK_BUF_SPACE(mp, bufsize)	\
	((bufsize) - (xfs_sb_version_hascrc(&(mp)->m_sb) ? \
			माप(काष्ठा xfs_dsymlink_hdr) : 0))


/*
 * Allocation Btree क्रमmat definitions
 *
 * There are two on-disk btrees, one sorted by blockno and one sorted
 * by blockcount and blockno.  All blocks look the same to make the code
 * simpler; अगर we have समय later, we'll make the optimizations.
 */
#घोषणा	XFS_ABTB_MAGIC		0x41425442	/* 'ABTB' क्रम bno tree */
#घोषणा	XFS_ABTB_CRC_MAGIC	0x41423342	/* 'AB3B' */
#घोषणा	XFS_ABTC_MAGIC		0x41425443	/* 'ABTC' क्रम cnt tree */
#घोषणा	XFS_ABTC_CRC_MAGIC	0x41423343	/* 'AB3C' */

/*
 * Data record/key काष्ठाure
 */
प्रकार काष्ठा xfs_alloc_rec अणु
	__be32		ar_startblock;	/* starting block number */
	__be32		ar_blockcount;	/* count of मुक्त blocks */
पूर्ण xfs_alloc_rec_t, xfs_alloc_key_t;

प्रकार काष्ठा xfs_alloc_rec_incore अणु
	xfs_agblock_t	ar_startblock;	/* starting block number */
	xfs_extlen_t	ar_blockcount;	/* count of मुक्त blocks */
पूर्ण xfs_alloc_rec_incore_t;

/* btree poपूर्णांकer type */
प्रकार __be32 xfs_alloc_ptr_t;

/*
 * Block numbers in the AG:
 * SB is sector 0, AGF is sector 1, AGI is sector 2, AGFL is sector 3.
 */
#घोषणा	XFS_BNO_BLOCK(mp)	((xfs_agblock_t)(XFS_AGFL_BLOCK(mp) + 1))
#घोषणा	XFS_CNT_BLOCK(mp)	((xfs_agblock_t)(XFS_BNO_BLOCK(mp) + 1))


/*
 * Inode Allocation Btree क्रमmat definitions
 *
 * There is a btree क्रम the inode map per allocation group.
 */
#घोषणा	XFS_IBT_MAGIC		0x49414254	/* 'IABT' */
#घोषणा	XFS_IBT_CRC_MAGIC	0x49414233	/* 'IAB3' */
#घोषणा	XFS_FIBT_MAGIC		0x46494254	/* 'FIBT' */
#घोषणा	XFS_FIBT_CRC_MAGIC	0x46494233	/* 'FIB3' */

प्रकार uपूर्णांक64_t	xfs_inoमुक्त_t;
#घोषणा	XFS_INODES_PER_CHUNK		(NBBY * माप(xfs_inoमुक्त_t))
#घोषणा	XFS_INODES_PER_CHUNK_LOG	(XFS_NBBYLOG + 3)
#घोषणा	XFS_INOBT_ALL_FREE		((xfs_inoमुक्त_t)-1)
#घोषणा	XFS_INOBT_MASK(i)		((xfs_inoमुक्त_t)1 << (i))

#घोषणा XFS_INOBT_HOLEMASK_FULL		0	/* holemask क्रम full chunk */
#घोषणा XFS_INOBT_HOLEMASK_BITS		(NBBY * माप(uपूर्णांक16_t))
#घोषणा XFS_INODES_PER_HOLEMASK_BIT	\
	(XFS_INODES_PER_CHUNK / (NBBY * माप(uपूर्णांक16_t)))

अटल अंतरभूत xfs_inoमुक्त_t xfs_inobt_maskn(पूर्णांक i, पूर्णांक n)
अणु
	वापस ((n >= XFS_INODES_PER_CHUNK ? 0 : XFS_INOBT_MASK(n)) - 1) << i;
पूर्ण

/*
 * The on-disk inode record काष्ठाure has two क्रमmats. The original "full"
 * क्रमmat uses a 4-byte मुक्तcount. The "sparse" क्रमmat uses a 1-byte मुक्तcount
 * and replaces the 3 high-order मुक्तcount bytes wth the holemask and inode
 * count.
 *
 * The holemask of the sparse record क्रमmat allows an inode chunk to have holes
 * that refer to blocks not owned by the inode record. This facilitates inode
 * allocation in the event of severe मुक्त space fragmentation.
 */
प्रकार काष्ठा xfs_inobt_rec अणु
	__be32		ir_startino;	/* starting inode number */
	जोड़ अणु
		काष्ठा अणु
			__be32	ir_मुक्तcount;	/* count of मुक्त inodes */
		पूर्ण f;
		काष्ठा अणु
			__be16	ir_holemask;/* hole mask क्रम sparse chunks */
			__u8	ir_count;	/* total inode count */
			__u8	ir_मुक्तcount;	/* count of मुक्त inodes */
		पूर्ण sp;
	पूर्ण ir_u;
	__be64		ir_मुक्त;	/* मुक्त inode mask */
पूर्ण xfs_inobt_rec_t;

प्रकार काष्ठा xfs_inobt_rec_incore अणु
	xfs_agino_t	ir_startino;	/* starting inode number */
	uपूर्णांक16_t	ir_holemask;	/* hole mask क्रम sparse chunks */
	uपूर्णांक8_t		ir_count;	/* total inode count */
	uपूर्णांक8_t		ir_मुक्तcount;	/* count of मुक्त inodes (set bits) */
	xfs_inoमुक्त_t	ir_मुक्त;	/* मुक्त inode mask */
पूर्ण xfs_inobt_rec_incore_t;

अटल अंतरभूत bool xfs_inobt_issparse(uपूर्णांक16_t holemask)
अणु
	/* non-zero holemask represents a sparse rec. */
	वापस holemask;
पूर्ण

/*
 * Key काष्ठाure
 */
प्रकार काष्ठा xfs_inobt_key अणु
	__be32		ir_startino;	/* starting inode number */
पूर्ण xfs_inobt_key_t;

/* btree poपूर्णांकer type */
प्रकार __be32 xfs_inobt_ptr_t;

/*
 * block numbers in the AG.
 */
#घोषणा	XFS_IBT_BLOCK(mp)		((xfs_agblock_t)(XFS_CNT_BLOCK(mp) + 1))
#घोषणा	XFS_FIBT_BLOCK(mp)		((xfs_agblock_t)(XFS_IBT_BLOCK(mp) + 1))

/*
 * Reverse mapping btree क्रमmat definitions
 *
 * There is a btree क्रम the reverse map per allocation group
 */
#घोषणा	XFS_RMAP_CRC_MAGIC	0x524d4233	/* 'RMB3' */

/*
 * Ownership info क्रम an extent.  This is used to create reverse-mapping
 * entries.
 */
#घोषणा XFS_OWNER_INFO_ATTR_FORK	(1 << 0)
#घोषणा XFS_OWNER_INFO_BMBT_BLOCK	(1 << 1)
काष्ठा xfs_owner_info अणु
	uपूर्णांक64_t		oi_owner;
	xfs_fileoff_t		oi_offset;
	अचिन्हित पूर्णांक		oi_flags;
पूर्ण;

/*
 * Special owner types.
 *
 * Seeing as we only support up to 8EB, we have the upper bit of the owner field
 * to tell us we have a special owner value. We use these क्रम अटल metadata
 * allocated at mkfs/growfs समय, as well as क्रम मुक्तspace management metadata.
 */
#घोषणा XFS_RMAP_OWN_शून्य	(-1ULL)	/* No owner, क्रम growfs */
#घोषणा XFS_RMAP_OWN_UNKNOWN	(-2ULL)	/* Unknown owner, क्रम EFI recovery */
#घोषणा XFS_RMAP_OWN_FS		(-3ULL)	/* अटल fs metadata */
#घोषणा XFS_RMAP_OWN_LOG	(-4ULL)	/* अटल fs metadata */
#घोषणा XFS_RMAP_OWN_AG		(-5ULL)	/* AG मुक्तspace btree blocks */
#घोषणा XFS_RMAP_OWN_INOBT	(-6ULL)	/* Inode btree blocks */
#घोषणा XFS_RMAP_OWN_INODES	(-7ULL)	/* Inode chunk */
#घोषणा XFS_RMAP_OWN_REFC	(-8ULL) /* refcount tree */
#घोषणा XFS_RMAP_OWN_COW	(-9ULL) /* cow allocations */
#घोषणा XFS_RMAP_OWN_MIN	(-10ULL) /* guard */

#घोषणा XFS_RMAP_NON_INODE_OWNER(owner)	(!!((owner) & (1ULL << 63)))

/*
 * Data record काष्ठाure
 */
काष्ठा xfs_rmap_rec अणु
	__be32		rm_startblock;	/* extent start block */
	__be32		rm_blockcount;	/* extent length */
	__be64		rm_owner;	/* extent owner */
	__be64		rm_offset;	/* offset within the owner */
पूर्ण;

/*
 * rmap btree record
 *  rm_offset:63 is the attribute विभाजन flag
 *  rm_offset:62 is the bmbt block flag
 *  rm_offset:61 is the unwritten extent flag (same as l0:63 in bmbt)
 *  rm_offset:54-60 aren't used and should be zero
 *  rm_offset:0-53 is the block offset within the inode
 */
#घोषणा XFS_RMAP_OFF_ATTR_FORK	((uपूर्णांक64_t)1ULL << 63)
#घोषणा XFS_RMAP_OFF_BMBT_BLOCK	((uपूर्णांक64_t)1ULL << 62)
#घोषणा XFS_RMAP_OFF_UNWRITTEN	((uपूर्णांक64_t)1ULL << 61)

#घोषणा XFS_RMAP_LEN_MAX	((uपूर्णांक32_t)~0U)
#घोषणा XFS_RMAP_OFF_FLAGS	(XFS_RMAP_OFF_ATTR_FORK | \
				 XFS_RMAP_OFF_BMBT_BLOCK | \
				 XFS_RMAP_OFF_UNWRITTEN)
#घोषणा XFS_RMAP_OFF_MASK	((uपूर्णांक64_t)0x3FFFFFFFFFFFFFULL)

#घोषणा XFS_RMAP_OFF(off)		((off) & XFS_RMAP_OFF_MASK)

#घोषणा XFS_RMAP_IS_BMBT_BLOCK(off)	(!!((off) & XFS_RMAP_OFF_BMBT_BLOCK))
#घोषणा XFS_RMAP_IS_ATTR_FORK(off)	(!!((off) & XFS_RMAP_OFF_ATTR_FORK))
#घोषणा XFS_RMAP_IS_UNWRITTEN(len)	(!!((off) & XFS_RMAP_OFF_UNWRITTEN))

#घोषणा RMAPBT_STARTBLOCK_BITLEN	32
#घोषणा RMAPBT_BLOCKCOUNT_BITLEN	32
#घोषणा RMAPBT_OWNER_BITLEN		64
#घोषणा RMAPBT_ATTRFLAG_BITLEN		1
#घोषणा RMAPBT_BMBTFLAG_BITLEN		1
#घोषणा RMAPBT_EXNTFLAG_BITLEN		1
#घोषणा RMAPBT_UNUSED_OFFSET_BITLEN	7
#घोषणा RMAPBT_OFFSET_BITLEN		54

#घोषणा XFS_RMAP_ATTR_FORK		(1 << 0)
#घोषणा XFS_RMAP_BMBT_BLOCK		(1 << 1)
#घोषणा XFS_RMAP_UNWRITTEN		(1 << 2)
#घोषणा XFS_RMAP_KEY_FLAGS		(XFS_RMAP_ATTR_FORK | \
					 XFS_RMAP_BMBT_BLOCK)
#घोषणा XFS_RMAP_REC_FLAGS		(XFS_RMAP_UNWRITTEN)
काष्ठा xfs_rmap_irec अणु
	xfs_agblock_t	rm_startblock;	/* extent start block */
	xfs_extlen_t	rm_blockcount;	/* extent length */
	uपूर्णांक64_t	rm_owner;	/* extent owner */
	uपूर्णांक64_t	rm_offset;	/* offset within the owner */
	अचिन्हित पूर्णांक	rm_flags;	/* state flags */
पूर्ण;

/*
 * Key काष्ठाure
 *
 * We करोn't use the length क्रम lookups
 */
काष्ठा xfs_rmap_key अणु
	__be32		rm_startblock;	/* extent start block */
	__be64		rm_owner;	/* extent owner */
	__be64		rm_offset;	/* offset within the owner */
पूर्ण __attribute__((packed));

/* btree poपूर्णांकer type */
प्रकार __be32 xfs_rmap_ptr_t;

#घोषणा	XFS_RMAP_BLOCK(mp) \
	(xfs_sb_version_hasfinobt(&((mp)->m_sb)) ? \
	 XFS_FIBT_BLOCK(mp) + 1 : \
	 XFS_IBT_BLOCK(mp) + 1)

/*
 * Reference Count Btree क्रमmat definitions
 *
 */
#घोषणा	XFS_REFC_CRC_MAGIC	0x52334643	/* 'R3FC' */

अचिन्हित पूर्णांक xfs_refc_block(काष्ठा xfs_mount *mp);

/*
 * Data record/key काष्ठाure
 *
 * Each record associates a range of physical blocks (starting at
 * rc_startblock and ending rc_blockcount blocks later) with a reference
 * count (rc_refcount).  Extents that are being used to stage a copy on
 * ग_लिखो (CoW) operation are recorded in the refcount btree with a
 * refcount of 1.  All other records must have a refcount > 1 and must
 * track an extent mapped only by file data विभाजनs.
 *
 * Extents with a single owner (attributes, metadata, non-shared file
 * data) are not tracked here.  Free space is also not tracked here.
 * This is consistent with pre-reflink XFS.
 */

/*
 * Extents that are being used to stage a copy on ग_लिखो are stored
 * in the refcount btree with a refcount of 1 and the upper bit set
 * on the startblock.  This speeds up mount समय deletion of stale
 * staging extents because they're all at the right side of the tree.
 */
#घोषणा XFS_REFC_COW_START		((xfs_agblock_t)(1U << 31))
#घोषणा REFCNTBT_COWFLAG_BITLEN		1
#घोषणा REFCNTBT_AGBLOCK_BITLEN		31

काष्ठा xfs_refcount_rec अणु
	__be32		rc_startblock;	/* starting block number */
	__be32		rc_blockcount;	/* count of blocks */
	__be32		rc_refcount;	/* number of inodes linked here */
पूर्ण;

काष्ठा xfs_refcount_key अणु
	__be32		rc_startblock;	/* starting block number */
पूर्ण;

काष्ठा xfs_refcount_irec अणु
	xfs_agblock_t	rc_startblock;	/* starting block number */
	xfs_extlen_t	rc_blockcount;	/* count of मुक्त blocks */
	xfs_nlink_t	rc_refcount;	/* number of inodes linked here */
पूर्ण;

#घोषणा MAXREFCOUNT	((xfs_nlink_t)~0U)
#घोषणा MAXREFCEXTLEN	((xfs_extlen_t)~0U)

/* btree poपूर्णांकer type */
प्रकार __be32 xfs_refcount_ptr_t;


/*
 * BMAP Btree क्रमmat definitions
 *
 * This includes both the root block definition that sits inside an inode विभाजन
 * and the record/poपूर्णांकer क्रमmats क्रम the leaf/node in the blocks.
 */
#घोषणा XFS_BMAP_MAGIC		0x424d4150	/* 'BMAP' */
#घोषणा XFS_BMAP_CRC_MAGIC	0x424d4133	/* 'BMA3' */

/*
 * Bmap root header, on-disk क्रमm only.
 */
प्रकार काष्ठा xfs_bmdr_block अणु
	__be16		bb_level;	/* 0 is a leaf */
	__be16		bb_numrecs;	/* current # of data records */
पूर्ण xfs_bmdr_block_t;

/*
 * Bmap btree record and extent descriptor.
 *  l0:63 is an extent flag (value 1 indicates non-normal).
 *  l0:9-62 are startoff.
 *  l0:0-8 and l1:21-63 are startblock.
 *  l1:0-20 are blockcount.
 */
#घोषणा BMBT_EXNTFLAG_BITLEN	1
#घोषणा BMBT_STARTOFF_BITLEN	54
#घोषणा BMBT_STARTBLOCK_BITLEN	52
#घोषणा BMBT_BLOCKCOUNT_BITLEN	21

#घोषणा BMBT_STARTOFF_MASK	((1ULL << BMBT_STARTOFF_BITLEN) - 1)
#घोषणा BMBT_BLOCKCOUNT_MASK	((1ULL << BMBT_BLOCKCOUNT_BITLEN) - 1)

/*
 * bmbt records have a file offset (block) field that is 54 bits wide, so this
 * is the largest xfs_fileoff_t that we ever expect to see.
 */
#घोषणा XFS_MAX_खाताOFF		(BMBT_STARTOFF_MASK + BMBT_BLOCKCOUNT_MASK)

प्रकार काष्ठा xfs_bmbt_rec अणु
	__be64			l0, l1;
पूर्ण xfs_bmbt_rec_t;

प्रकार uपूर्णांक64_t	xfs_bmbt_rec_base_t;	/* use this क्रम casts */
प्रकार xfs_bmbt_rec_t xfs_bmdr_rec_t;

/*
 * Values and macros क्रम delayed-allocation startblock fields.
 */
#घोषणा STARTBLOCKVALBITS	17
#घोषणा STARTBLOCKMASKBITS	(15 + 20)
#घोषणा STARTBLOCKMASK		\
	(((((xfs_fsblock_t)1) << STARTBLOCKMASKBITS) - 1) << STARTBLOCKVALBITS)

अटल अंतरभूत पूर्णांक isnullstartblock(xfs_fsblock_t x)
अणु
	वापस ((x) & STARTBLOCKMASK) == STARTBLOCKMASK;
पूर्ण

अटल अंतरभूत xfs_fsblock_t nullstartblock(पूर्णांक k)
अणु
	ASSERT(k < (1 << STARTBLOCKVALBITS));
	वापस STARTBLOCKMASK | (k);
पूर्ण

अटल अंतरभूत xfs_filblks_t startblockval(xfs_fsblock_t x)
अणु
	वापस (xfs_filblks_t)((x) & ~STARTBLOCKMASK);
पूर्ण

/*
 * Key काष्ठाure क्रम non-leaf levels of the tree.
 */
प्रकार काष्ठा xfs_bmbt_key अणु
	__be64		br_startoff;	/* starting file offset */
पूर्ण xfs_bmbt_key_t, xfs_bmdr_key_t;

/* btree poपूर्णांकer type */
प्रकार __be64 xfs_bmbt_ptr_t, xfs_bmdr_ptr_t;


/*
 * Generic Btree block क्रमmat definitions
 *
 * This is a combination of the actual क्रमmat used on disk क्रम लघु and दीर्घ
 * क्रमmat btrees.  The first three fields are shared by both क्रमmat, but the
 * poपूर्णांकers are dअगरferent and should be used with care.
 *
 * To get the size of the actual लघु or दीर्घ क्रमm headers please use the size
 * macros below.  Never use माप(xfs_btree_block).
 *
 * The blkno, crc, lsn, owner and uuid fields are only available in fileप्रणालीs
 * with the crc feature bit, and all accesses to them must be conditional on
 * that flag.
 */
/* लघु क्रमm block header */
काष्ठा xfs_btree_block_shdr अणु
	__be32		bb_leftsib;
	__be32		bb_rightsib;

	__be64		bb_blkno;
	__be64		bb_lsn;
	uuid_t		bb_uuid;
	__be32		bb_owner;
	__le32		bb_crc;
पूर्ण;

/* दीर्घ क्रमm block header */
काष्ठा xfs_btree_block_lhdr अणु
	__be64		bb_leftsib;
	__be64		bb_rightsib;

	__be64		bb_blkno;
	__be64		bb_lsn;
	uuid_t		bb_uuid;
	__be64		bb_owner;
	__le32		bb_crc;
	__be32		bb_pad; /* padding क्रम alignment */
पूर्ण;

काष्ठा xfs_btree_block अणु
	__be32		bb_magic;	/* magic number क्रम block type */
	__be16		bb_level;	/* 0 is a leaf */
	__be16		bb_numrecs;	/* current # of data records */
	जोड़ अणु
		काष्ठा xfs_btree_block_shdr s;
		काष्ठा xfs_btree_block_lhdr l;
	पूर्ण bb_u;				/* rest */
पूर्ण;

/* size of a लघु क्रमm block */
#घोषणा XFS_BTREE_SBLOCK_LEN \
	(दुरत्व(काष्ठा xfs_btree_block, bb_u) + \
	 दुरत्व(काष्ठा xfs_btree_block_shdr, bb_blkno))
/* size of a दीर्घ क्रमm block */
#घोषणा XFS_BTREE_LBLOCK_LEN \
	(दुरत्व(काष्ठा xfs_btree_block, bb_u) + \
	 दुरत्व(काष्ठा xfs_btree_block_lhdr, bb_blkno))

/* sizes of CRC enabled btree blocks */
#घोषणा XFS_BTREE_SBLOCK_CRC_LEN \
	(दुरत्व(काष्ठा xfs_btree_block, bb_u) + \
	 माप(काष्ठा xfs_btree_block_shdr))
#घोषणा XFS_BTREE_LBLOCK_CRC_LEN \
	(दुरत्व(काष्ठा xfs_btree_block, bb_u) + \
	 माप(काष्ठा xfs_btree_block_lhdr))

#घोषणा XFS_BTREE_SBLOCK_CRC_OFF \
	दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_crc)
#घोषणा XFS_BTREE_LBLOCK_CRC_OFF \
	दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_crc)

/*
 * On-disk XFS access control list काष्ठाure.
 */
काष्ठा xfs_acl_entry अणु
	__be32	ae_tag;
	__be32	ae_id;
	__be16	ae_perm;
	__be16	ae_pad;		/* fill the implicit hole in the काष्ठाure */
पूर्ण;

काष्ठा xfs_acl अणु
	__be32			acl_cnt;
	काष्ठा xfs_acl_entry	acl_entry[];
पूर्ण;

/*
 * The number of ACL entries allowed is defined by the on-disk क्रमmat.
 * For v4 superblocks, that is limited to 25 entries. For v5 superblocks, it is
 * limited only by the maximum size of the xattr that stores the inक्रमmation.
 */
#घोषणा XFS_ACL_MAX_ENTRIES(mp)	\
	(xfs_sb_version_hascrc(&mp->m_sb) \
		?  (XFS_XATTR_SIZE_MAX - माप(काष्ठा xfs_acl)) / \
						माप(काष्ठा xfs_acl_entry) \
		: 25)

#घोषणा XFS_ACL_SIZE(cnt) \
	(माप(काष्ठा xfs_acl) + \
		माप(काष्ठा xfs_acl_entry) * cnt)

#घोषणा XFS_ACL_MAX_SIZE(mp) \
	XFS_ACL_SIZE(XFS_ACL_MAX_ENTRIES((mp)))


/* On-disk XFS extended attribute names */
#घोषणा SGI_ACL_खाता		"SGI_ACL_FILE"
#घोषणा SGI_ACL_DEFAULT		"SGI_ACL_DEFAULT"
#घोषणा SGI_ACL_खाता_SIZE	(माप(SGI_ACL_खाता)-1)
#घोषणा SGI_ACL_DEFAULT_SIZE	(माप(SGI_ACL_DEFAULT)-1)

#पूर्ण_अगर /* __XFS_FORMAT_H__ */
