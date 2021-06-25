<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_TYPES_H__
#घोषणा	__XFS_TYPES_H__

प्रकार uपूर्णांक32_t	prid_t;		/* project ID */

प्रकार uपूर्णांक32_t	xfs_agblock_t;	/* blockno in alloc. group */
प्रकार uपूर्णांक32_t	xfs_agino_t;	/* inode # within allocation grp */
प्रकार uपूर्णांक32_t	xfs_extlen_t;	/* extent length in blocks */
प्रकार uपूर्णांक32_t	xfs_agnumber_t;	/* allocation group number */
प्रकार पूर्णांक32_t		xfs_extnum_t;	/* # of extents in a file */
प्रकार पूर्णांक16_t		xfs_aextnum_t;	/* # extents in an attribute विभाजन */
प्रकार पूर्णांक64_t		xfs_fमाप_प्रकार;	/* bytes in a file */
प्रकार uपूर्णांक64_t	xfs_ufमाप_प्रकार;	/* अचिन्हित bytes in a file */

प्रकार पूर्णांक32_t		xfs_suminfo_t;	/* type of biपंचांगap summary info */
प्रकार uपूर्णांक32_t	xfs_rtword_t;	/* word type क्रम biपंचांगap manipulations */

प्रकार पूर्णांक64_t		xfs_lsn_t;	/* log sequence number */

प्रकार uपूर्णांक32_t	xfs_dablk_t;	/* dir/attr block number (in file) */
प्रकार uपूर्णांक32_t	xfs_dahash_t;	/* dir/attr hash value */

प्रकार uपूर्णांक64_t	xfs_fsblock_t;	/* blockno in fileप्रणाली (agno|agbno) */
प्रकार uपूर्णांक64_t	xfs_rfsblock_t;	/* blockno in fileप्रणाली (raw) */
प्रकार uपूर्णांक64_t	xfs_rtblock_t;	/* extent (block) in realसमय area */
प्रकार uपूर्णांक64_t	xfs_fileoff_t;	/* block number in a file */
प्रकार uपूर्णांक64_t	xfs_filblks_t;	/* number of blocks in a file */

प्रकार पूर्णांक64_t		xfs_srtblock_t;	/* चिन्हित version of xfs_rtblock_t */

/*
 * New verअगरiers will वापस the inकाष्ठाion address of the failing check.
 * शून्य means everything is ok.
 */
प्रकार व्योम *		xfs_failaddr_t;

/*
 * Null values क्रम the types.
 */
#घोषणा	शून्यFSBLOCK	((xfs_fsblock_t)-1)
#घोषणा	शून्यRFSBLOCK	((xfs_rfsblock_t)-1)
#घोषणा	शून्यRTBLOCK	((xfs_rtblock_t)-1)
#घोषणा	शून्यखाताOFF	((xfs_fileoff_t)-1)

#घोषणा	शून्यAGBLOCK	((xfs_agblock_t)-1)
#घोषणा	शून्यAGNUMBER	((xfs_agnumber_t)-1)

#घोषणा शून्यCOMMITLSN	((xfs_lsn_t)-1)

#घोषणा	शून्यFSINO	((xfs_ino_t)-1)
#घोषणा	शून्यAGINO	((xfs_agino_t)-1)

/*
 * Max values क्रम extlen, extnum, aextnum.
 */
#घोषणा	MAXEXTLEN	((xfs_extlen_t)0x001fffff)	/* 21 bits */
#घोषणा	MAXEXTNUM	((xfs_extnum_t)0x7fffffff)	/* चिन्हित पूर्णांक */
#घोषणा	MAXAEXTNUM	((xfs_aextnum_t)0x7fff)		/* चिन्हित लघु */

/*
 * Minimum and maximum blocksize and sectorsize.
 * The blocksize upper limit is pretty much arbitrary.
 * The sectorsize upper limit is due to माप(sb_sectsize).
 * CRC enable fileप्रणालीs use 512 byte inodes, meaning 512 byte block sizes
 * cannot be used.
 */
#घोषणा XFS_MIN_BLOCKSIZE_LOG	9	/* i.e. 512 bytes */
#घोषणा XFS_MAX_BLOCKSIZE_LOG	16	/* i.e. 65536 bytes */
#घोषणा XFS_MIN_BLOCKSIZE	(1 << XFS_MIN_BLOCKSIZE_LOG)
#घोषणा XFS_MAX_BLOCKSIZE	(1 << XFS_MAX_BLOCKSIZE_LOG)
#घोषणा XFS_MIN_CRC_BLOCKSIZE	(1 << (XFS_MIN_BLOCKSIZE_LOG + 1))
#घोषणा XFS_MIN_SECTORSIZE_LOG	9	/* i.e. 512 bytes */
#घोषणा XFS_MAX_SECTORSIZE_LOG	15	/* i.e. 32768 bytes */
#घोषणा XFS_MIN_SECTORSIZE	(1 << XFS_MIN_SECTORSIZE_LOG)
#घोषणा XFS_MAX_SECTORSIZE	(1 << XFS_MAX_SECTORSIZE_LOG)

/*
 * Inode विभाजन identअगरiers.
 */
#घोषणा	XFS_DATA_FORK	0
#घोषणा	XFS_ATTR_FORK	1
#घोषणा	XFS_COW_FORK	2

/*
 * Min numbers of data/attr विभाजन btree root poपूर्णांकers.
 */
#घोषणा MINDBTPTRS	3
#घोषणा MINABTPTRS	2

/*
 * MAXNAMELEN is the length (including the terminating null) of
 * the दीर्घest permissible file (component) name.
 */
#घोषणा MAXNAMELEN	256

/*
 * This क्रमागत is used in string mapping in xfs_trace.h; please keep the
 * TRACE_DEFINE_ENUMs क्रम it up to date.
 */
प्रकार क्रमागत अणु
	XFS_LOOKUP_EQi, XFS_LOOKUP_LEi, XFS_LOOKUP_GEi
पूर्ण xfs_lookup_t;

#घोषणा XFS_AG_BTREE_CMP_FORMAT_STR \
	अणु XFS_LOOKUP_EQi,	"eq" पूर्ण, \
	अणु XFS_LOOKUP_LEi,	"le" पूर्ण, \
	अणु XFS_LOOKUP_GEi,	"ge" पूर्ण

/*
 * This क्रमागत is used in string mapping in xfs_trace.h and scrub/trace.h;
 * please keep the TRACE_DEFINE_ENUMs क्रम it up to date.
 */
प्रकार क्रमागत अणु
	XFS_BTNUM_BNOi, XFS_BTNUM_CNTi, XFS_BTNUM_RMAPi, XFS_BTNUM_BMAPi,
	XFS_BTNUM_INOi, XFS_BTNUM_FINOi, XFS_BTNUM_REFCi, XFS_BTNUM_MAX
पूर्ण xfs_btnum_t;

#घोषणा XFS_BTNUM_STRINGS \
	अणु XFS_BTNUM_BNOi,	"bnobt" पूर्ण, \
	अणु XFS_BTNUM_CNTi,	"cntbt" पूर्ण, \
	अणु XFS_BTNUM_RMAPi,	"rmapbt" पूर्ण, \
	अणु XFS_BTNUM_BMAPi,	"bmbt" पूर्ण, \
	अणु XFS_BTNUM_INOi,	"inobt" पूर्ण, \
	अणु XFS_BTNUM_FINOi,	"finobt" पूर्ण, \
	अणु XFS_BTNUM_REFCi,	"refcbt" पूर्ण

काष्ठा xfs_name अणु
	स्थिर अचिन्हित अक्षर	*name;
	पूर्णांक			len;
	पूर्णांक			type;
पूर्ण;

/*
 * uid_t and gid_t are hard-coded to 32 bits in the inode.
 * Hence, an 'id' in a dquot is 32 bits..
 */
प्रकार uपूर्णांक32_t	xfs_dqid_t;

/*
 * Constants क्रम bit manipulations.
 */
#घोषणा	XFS_NBBYLOG	3		/* log2(NBBY) */
#घोषणा	XFS_WORDLOG	2		/* log2(माप(xfs_rtword_t)) */
#घोषणा	XFS_NBWORDLOG	(XFS_NBBYLOG + XFS_WORDLOG)
#घोषणा	XFS_NBWORD	(1 << XFS_NBWORDLOG)
#घोषणा	XFS_WORDMASK	((1 << XFS_WORDLOG) - 1)

काष्ठा xfs_iext_cursor अणु
	काष्ठा xfs_iext_leaf	*leaf;
	पूर्णांक			pos;
पूर्ण;

प्रकार क्रमागत अणु
	XFS_EXT_NORM, XFS_EXT_UNWRITTEN,
पूर्ण xfs_exntst_t;

प्रकार काष्ठा xfs_bmbt_irec
अणु
	xfs_fileoff_t	br_startoff;	/* starting file offset */
	xfs_fsblock_t	br_startblock;	/* starting block number */
	xfs_filblks_t	br_blockcount;	/* number of blocks */
	xfs_exntst_t	br_state;	/* extent state */
पूर्ण xfs_bmbt_irec_t;

/* per-AG block reservation types */
क्रमागत xfs_ag_resv_type अणु
	XFS_AG_RESV_NONE = 0,
	XFS_AG_RESV_AGFL,
	XFS_AG_RESV_METADATA,
	XFS_AG_RESV_RMAPBT,
पूर्ण;

/*
 * Type verअगरier functions
 */
काष्ठा xfs_mount;

xfs_agblock_t xfs_ag_block_count(काष्ठा xfs_mount *mp, xfs_agnumber_t agno);
bool xfs_verअगरy_agbno(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		xfs_agblock_t agbno);
bool xfs_verअगरy_fsbno(काष्ठा xfs_mount *mp, xfs_fsblock_t fsbno);
bool xfs_verअगरy_fsbext(काष्ठा xfs_mount *mp, xfs_fsblock_t fsbno,
		xfs_fsblock_t len);

व्योम xfs_agino_range(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		xfs_agino_t *first, xfs_agino_t *last);
bool xfs_verअगरy_agino(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		xfs_agino_t agino);
bool xfs_verअगरy_agino_or_null(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
		xfs_agino_t agino);
bool xfs_verअगरy_ino(काष्ठा xfs_mount *mp, xfs_ino_t ino);
bool xfs_पूर्णांकernal_inum(काष्ठा xfs_mount *mp, xfs_ino_t ino);
bool xfs_verअगरy_dir_ino(काष्ठा xfs_mount *mp, xfs_ino_t ino);
bool xfs_verअगरy_rtbno(काष्ठा xfs_mount *mp, xfs_rtblock_t rtbno);
bool xfs_verअगरy_rtext(काष्ठा xfs_mount *mp, xfs_rtblock_t rtbno,
		xfs_rtblock_t len);
bool xfs_verअगरy_icount(काष्ठा xfs_mount *mp, अचिन्हित दीर्घ दीर्घ icount);
bool xfs_verअगरy_dablk(काष्ठा xfs_mount *mp, xfs_fileoff_t off);
व्योम xfs_icount_range(काष्ठा xfs_mount *mp, अचिन्हित दीर्घ दीर्घ *min,
		अचिन्हित दीर्घ दीर्घ *max);
bool xfs_verअगरy_fileoff(काष्ठा xfs_mount *mp, xfs_fileoff_t off);
bool xfs_verअगरy_fileext(काष्ठा xfs_mount *mp, xfs_fileoff_t off,
		xfs_fileoff_t len);

#पूर्ण_अगर	/* __XFS_TYPES_H__ */
