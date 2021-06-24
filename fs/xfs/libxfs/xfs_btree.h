<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BTREE_H__
#घोषणा	__XFS_BTREE_H__

काष्ठा xfs_buf;
काष्ठा xfs_inode;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_अगरork;

बाह्य kmem_zone_t	*xfs_btree_cur_zone;

/*
 * Generic key, ptr and record wrapper काष्ठाures.
 *
 * These are disk क्रमmat काष्ठाures, and are converted where necessary
 * by the btree specअगरic code that needs to पूर्णांकerpret them.
 */
जोड़ xfs_btree_ptr अणु
	__be32			s;	/* लघु क्रमm ptr */
	__be64			l;	/* दीर्घ क्रमm ptr */
पूर्ण;

/*
 * The in-core btree key.  Overlapping btrees actually store two keys
 * per poपूर्णांकer, so we reserve enough memory to hold both.  The __*bigkey
 * items should never be accessed directly.
 */
जोड़ xfs_btree_key अणु
	काष्ठा xfs_bmbt_key		bmbt;
	xfs_bmdr_key_t			bmbr;	/* bmbt root block */
	xfs_alloc_key_t			alloc;
	काष्ठा xfs_inobt_key		inobt;
	काष्ठा xfs_rmap_key		rmap;
	काष्ठा xfs_rmap_key		__rmap_bigkey[2];
	काष्ठा xfs_refcount_key		refc;
पूर्ण;

जोड़ xfs_btree_rec अणु
	काष्ठा xfs_bmbt_rec		bmbt;
	xfs_bmdr_rec_t			bmbr;	/* bmbt root block */
	काष्ठा xfs_alloc_rec		alloc;
	काष्ठा xfs_inobt_rec		inobt;
	काष्ठा xfs_rmap_rec		rmap;
	काष्ठा xfs_refcount_rec		refc;
पूर्ण;

/*
 * This nonsense is to make -wlपूर्णांक happy.
 */
#घोषणा	XFS_LOOKUP_EQ	((xfs_lookup_t)XFS_LOOKUP_EQi)
#घोषणा	XFS_LOOKUP_LE	((xfs_lookup_t)XFS_LOOKUP_LEi)
#घोषणा	XFS_LOOKUP_GE	((xfs_lookup_t)XFS_LOOKUP_GEi)

#घोषणा	XFS_BTNUM_BNO	((xfs_btnum_t)XFS_BTNUM_BNOi)
#घोषणा	XFS_BTNUM_CNT	((xfs_btnum_t)XFS_BTNUM_CNTi)
#घोषणा	XFS_BTNUM_BMAP	((xfs_btnum_t)XFS_BTNUM_BMAPi)
#घोषणा	XFS_BTNUM_INO	((xfs_btnum_t)XFS_BTNUM_INOi)
#घोषणा	XFS_BTNUM_FINO	((xfs_btnum_t)XFS_BTNUM_FINOi)
#घोषणा	XFS_BTNUM_RMAP	((xfs_btnum_t)XFS_BTNUM_RMAPi)
#घोषणा	XFS_BTNUM_REFC	((xfs_btnum_t)XFS_BTNUM_REFCi)

uपूर्णांक32_t xfs_btree_magic(पूर्णांक crc, xfs_btnum_t btnum);

/*
 * For logging record fields.
 */
#घोषणा	XFS_BB_MAGIC		(1 << 0)
#घोषणा	XFS_BB_LEVEL		(1 << 1)
#घोषणा	XFS_BB_NUMRECS		(1 << 2)
#घोषणा	XFS_BB_LEFTSIB		(1 << 3)
#घोषणा	XFS_BB_RIGHTSIB		(1 << 4)
#घोषणा	XFS_BB_BLKNO		(1 << 5)
#घोषणा	XFS_BB_LSN		(1 << 6)
#घोषणा	XFS_BB_UUID		(1 << 7)
#घोषणा	XFS_BB_OWNER		(1 << 8)
#घोषणा	XFS_BB_NUM_BITS		5
#घोषणा	XFS_BB_ALL_BITS		((1 << XFS_BB_NUM_BITS) - 1)
#घोषणा	XFS_BB_NUM_BITS_CRC	9
#घोषणा	XFS_BB_ALL_BITS_CRC	((1 << XFS_BB_NUM_BITS_CRC) - 1)

/*
 * Generic stats पूर्णांकerface
 */
#घोषणा XFS_BTREE_STATS_INC(cur, stat)	\
	XFS_STATS_INC_OFF((cur)->bc_mp, (cur)->bc_stम_से_भf + __XBTS_ ## stat)
#घोषणा XFS_BTREE_STATS_ADD(cur, stat, val)	\
	XFS_STATS_ADD_OFF((cur)->bc_mp, (cur)->bc_stम_से_भf + __XBTS_ ## stat, val)

#घोषणा	XFS_BTREE_MAXLEVELS	9	/* max of all btrees */

काष्ठा xfs_btree_ops अणु
	/* size of the key and record काष्ठाures */
	माप_प्रकार	key_len;
	माप_प्रकार	rec_len;

	/* cursor operations */
	काष्ठा xfs_btree_cur *(*dup_cursor)(काष्ठा xfs_btree_cur *);
	व्योम	(*update_cursor)(काष्ठा xfs_btree_cur *src,
				 काष्ठा xfs_btree_cur *dst);

	/* update btree root poपूर्णांकer */
	व्योम	(*set_root)(काष्ठा xfs_btree_cur *cur,
			    जोड़ xfs_btree_ptr *nptr, पूर्णांक level_change);

	/* block allocation / मुक्तing */
	पूर्णांक	(*alloc_block)(काष्ठा xfs_btree_cur *cur,
			       जोड़ xfs_btree_ptr *start_bno,
			       जोड़ xfs_btree_ptr *new_bno,
			       पूर्णांक *stat);
	पूर्णांक	(*मुक्त_block)(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_buf *bp);

	/* update last record inक्रमmation */
	व्योम	(*update_lastrec)(काष्ठा xfs_btree_cur *cur,
				  काष्ठा xfs_btree_block *block,
				  जोड़ xfs_btree_rec *rec,
				  पूर्णांक ptr, पूर्णांक reason);

	/* records in block/level */
	पूर्णांक	(*get_minrecs)(काष्ठा xfs_btree_cur *cur, पूर्णांक level);
	पूर्णांक	(*get_maxrecs)(काष्ठा xfs_btree_cur *cur, पूर्णांक level);

	/* records on disk.  Matter क्रम the root in inode हाल. */
	पूर्णांक	(*get_dmaxrecs)(काष्ठा xfs_btree_cur *cur, पूर्णांक level);

	/* init values of btree काष्ठाures */
	व्योम	(*init_key_from_rec)(जोड़ xfs_btree_key *key,
				     जोड़ xfs_btree_rec *rec);
	व्योम	(*init_rec_from_cur)(काष्ठा xfs_btree_cur *cur,
				     जोड़ xfs_btree_rec *rec);
	व्योम	(*init_ptr_from_cur)(काष्ठा xfs_btree_cur *cur,
				     जोड़ xfs_btree_ptr *ptr);
	व्योम	(*init_high_key_from_rec)(जोड़ xfs_btree_key *key,
					  जोड़ xfs_btree_rec *rec);

	/* dअगरference between key value and cursor value */
	पूर्णांक64_t (*key_dअगरf)(काष्ठा xfs_btree_cur *cur,
			      जोड़ xfs_btree_key *key);

	/*
	 * Dअगरference between key2 and key1 -- positive अगर key1 > key2,
	 * negative अगर key1 < key2, and zero अगर equal.
	 */
	पूर्णांक64_t (*dअगरf_two_keys)(काष्ठा xfs_btree_cur *cur,
				   जोड़ xfs_btree_key *key1,
				   जोड़ xfs_btree_key *key2);

	स्थिर काष्ठा xfs_buf_ops	*buf_ops;

	/* check that k1 is lower than k2 */
	पूर्णांक	(*keys_inorder)(काष्ठा xfs_btree_cur *cur,
				जोड़ xfs_btree_key *k1,
				जोड़ xfs_btree_key *k2);

	/* check that r1 is lower than r2 */
	पूर्णांक	(*recs_inorder)(काष्ठा xfs_btree_cur *cur,
				जोड़ xfs_btree_rec *r1,
				जोड़ xfs_btree_rec *r2);
पूर्ण;

/*
 * Reasons क्रम the update_lastrec method to be called.
 */
#घोषणा LASTREC_UPDATE	0
#घोषणा LASTREC_INSREC	1
#घोषणा LASTREC_DELREC	2


जोड़ xfs_btree_irec अणु
	काष्ठा xfs_alloc_rec_incore	a;
	काष्ठा xfs_bmbt_irec		b;
	काष्ठा xfs_inobt_rec_incore	i;
	काष्ठा xfs_rmap_irec		r;
	काष्ठा xfs_refcount_irec	rc;
पूर्ण;

/* Per-AG btree inक्रमmation. */
काष्ठा xfs_btree_cur_ag अणु
	जोड़ अणु
		काष्ठा xfs_buf		*agbp;
		काष्ठा xbtree_afakeroot	*afake;	/* क्रम staging cursor */
	पूर्ण;
	xfs_agnumber_t		agno;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ nr_ops;	/* # record updates */
			पूर्णांक	shape_changes;	/* # of extent splits */
		पूर्ण refc;
		काष्ठा अणु
			bool	active;		/* allocation cursor state */
		पूर्ण abt;
	पूर्ण;
पूर्ण;

/* Btree-in-inode cursor inक्रमmation */
काष्ठा xfs_btree_cur_ino अणु
	काष्ठा xfs_inode		*ip;
	काष्ठा xbtree_अगरakeroot		*अगरake;	/* क्रम staging cursor */
	पूर्णांक				allocated;
	लघु				विभाजनsize;
	अक्षर				whichविभाजन;
	अक्षर				flags;
/* We are converting a delalloc reservation */
#घोषणा	XFS_BTCUR_BMBT_WASDEL		(1 << 0)

/* For extent swap, ignore owner check in verअगरier */
#घोषणा	XFS_BTCUR_BMBT_INVALID_OWNER	(1 << 1)
पूर्ण;

/*
 * Btree cursor काष्ठाure.
 * This collects all inक्रमmation needed by the btree code in one place.
 */
प्रकार काष्ठा xfs_btree_cur
अणु
	काष्ठा xfs_trans	*bc_tp;	/* transaction we're in, अगर any */
	काष्ठा xfs_mount	*bc_mp;	/* file प्रणाली mount काष्ठा */
	स्थिर काष्ठा xfs_btree_ops *bc_ops;
	uपूर्णांक			bc_flags; /* btree features - below */
	जोड़ xfs_btree_irec	bc_rec;	/* current insert/search record value */
	काष्ठा xfs_buf	*bc_bufs[XFS_BTREE_MAXLEVELS];	/* buf ptr per level */
	पूर्णांक		bc_ptrs[XFS_BTREE_MAXLEVELS];	/* key/record # */
	uपूर्णांक8_t		bc_ra[XFS_BTREE_MAXLEVELS];	/* पढ़ोahead bits */
#घोषणा	XFS_BTCUR_LEFTRA	1	/* left sibling has been पढ़ो-ahead */
#घोषणा	XFS_BTCUR_RIGHTRA	2	/* right sibling has been पढ़ो-ahead */
	uपूर्णांक8_t		bc_nlevels;	/* number of levels in the tree */
	uपूर्णांक8_t		bc_blocklog;	/* log2(blocksize) of btree blocks */
	xfs_btnum_t	bc_btnum;	/* identअगरies which btree type */
	पूर्णांक		bc_stम_से_भf;	/* offset of btre stats array */
	जोड़ अणु
		काष्ठा xfs_btree_cur_ag	bc_ag;
		काष्ठा xfs_btree_cur_ino bc_ino;
	पूर्ण;
पूर्ण xfs_btree_cur_t;

/* cursor flags */
#घोषणा XFS_BTREE_LONG_PTRS		(1<<0)	/* poपूर्णांकers are 64bits दीर्घ */
#घोषणा XFS_BTREE_ROOT_IN_INODE		(1<<1)	/* root may be variable size */
#घोषणा XFS_BTREE_LASTREC_UPDATE	(1<<2)	/* track last rec बाह्यally */
#घोषणा XFS_BTREE_CRC_BLOCKS		(1<<3)	/* uses extended btree blocks */
#घोषणा XFS_BTREE_OVERLAPPING		(1<<4)	/* overlapping पूर्णांकervals */
/*
 * The root of this btree is a fakeroot काष्ठाure so that we can stage a btree
 * rebuild without leaving it accessible via primary metadata.  The ops काष्ठा
 * is dynamically allocated and must be मुक्तd when the cursor is deleted.
 */
#घोषणा XFS_BTREE_STAGING		(1<<5)


#घोषणा	XFS_BTREE_NOERROR	0
#घोषणा	XFS_BTREE_ERROR		1

/*
 * Convert from buffer to btree block header.
 */
#घोषणा	XFS_BUF_TO_BLOCK(bp)	((काष्ठा xfs_btree_block *)((bp)->b_addr))

/*
 * Internal दीर्घ and लघु btree block checks.  They वापस शून्य अगर the
 * block is ok or the address of the failed check otherwise.
 */
xfs_failaddr_t __xfs_btree_check_lblock(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_btree_block *block, पूर्णांक level, काष्ठा xfs_buf *bp);
xfs_failaddr_t __xfs_btree_check_sblock(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_btree_block *block, पूर्णांक level, काष्ठा xfs_buf *bp);

/*
 * Check that block header is ok.
 */
पूर्णांक
xfs_btree_check_block(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	काष्ठा xfs_btree_block	*block,	/* generic btree block poपूर्णांकer */
	पूर्णांक			level,	/* level of the btree block */
	काष्ठा xfs_buf		*bp);	/* buffer containing block, अगर any */

/*
 * Check that (दीर्घ) poपूर्णांकer is ok.
 */
bool					/* error (0 or EFSCORRUPTED) */
xfs_btree_check_lptr(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_fsblock_t		fsbno,	/* btree block disk address */
	पूर्णांक			level);	/* btree block level */

/*
 * Check that (लघु) poपूर्णांकer is ok.
 */
bool					/* error (0 or EFSCORRUPTED) */
xfs_btree_check_sptr(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		agbno,	/* btree block disk address */
	पूर्णांक			level);	/* btree block level */

/*
 * Delete the btree cursor.
 */
व्योम
xfs_btree_del_cursor(
	xfs_btree_cur_t		*cur,	/* btree cursor */
	पूर्णांक			error);	/* del because of error */

/*
 * Duplicate the btree cursor.
 * Allocate a new one, copy the record, re-get the buffers.
 */
पूर्णांक					/* error */
xfs_btree_dup_cursor(
	xfs_btree_cur_t		*cur,	/* input cursor */
	xfs_btree_cur_t		**ncur);/* output cursor */

/*
 * Compute first and last byte offsets क्रम the fields given.
 * Interprets the offsets table, which contains काष्ठा field offsets.
 */
व्योम
xfs_btree_offsets(
	पूर्णांक64_t			fields,	/* biपंचांगask of fields */
	स्थिर लघु		*offsets,/* table of field offsets */
	पूर्णांक			nbits,	/* number of bits to inspect */
	पूर्णांक			*first,	/* output: first byte offset */
	पूर्णांक			*last);	/* output: last byte offset */

/*
 * Get a buffer क्रम the block, वापस it पढ़ो in.
 * Long-क्रमm addressing.
 */
पूर्णांक					/* error */
xfs_btree_पढ़ो_bufl(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_fsblock_t		fsbno,	/* file प्रणाली block number */
	काष्ठा xfs_buf		**bpp,	/* buffer क्रम fsbno */
	पूर्णांक			refval,	/* ref count value क्रम buffer */
	स्थिर काष्ठा xfs_buf_ops *ops);

/*
 * Read-ahead the block, करोn't wait for it, don't वापस a buffer.
 * Long-क्रमm addressing.
 */
व्योम					/* error */
xfs_btree_पढ़ोa_bufl(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount poपूर्णांक */
	xfs_fsblock_t		fsbno,	/* file प्रणाली block number */
	xfs_extlen_t		count,	/* count of fileप्रणाली blocks */
	स्थिर काष्ठा xfs_buf_ops *ops);

/*
 * Read-ahead the block, करोn't wait for it, don't वापस a buffer.
 * Short-क्रमm addressing.
 */
व्योम					/* error */
xfs_btree_पढ़ोa_bufs(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount poपूर्णांक */
	xfs_agnumber_t		agno,	/* allocation group number */
	xfs_agblock_t		agbno,	/* allocation group block number */
	xfs_extlen_t		count,	/* count of fileप्रणाली blocks */
	स्थिर काष्ठा xfs_buf_ops *ops);

/*
 * Initialise a new btree block header
 */
व्योम
xfs_btree_init_block(
	काष्ठा xfs_mount *mp,
	काष्ठा xfs_buf	*bp,
	xfs_btnum_t	btnum,
	__u16		level,
	__u16		numrecs,
	__u64		owner);

व्योम
xfs_btree_init_block_पूर्णांक(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_btree_block	*buf,
	xfs_daddr_t		blkno,
	xfs_btnum_t		btnum,
	__u16			level,
	__u16			numrecs,
	__u64			owner,
	अचिन्हित पूर्णांक		flags);

/*
 * Common btree core entry poपूर्णांकs.
 */
पूर्णांक xfs_btree_increment(काष्ठा xfs_btree_cur *, पूर्णांक, पूर्णांक *);
पूर्णांक xfs_btree_decrement(काष्ठा xfs_btree_cur *, पूर्णांक, पूर्णांक *);
पूर्णांक xfs_btree_lookup(काष्ठा xfs_btree_cur *, xfs_lookup_t, पूर्णांक *);
पूर्णांक xfs_btree_update(काष्ठा xfs_btree_cur *, जोड़ xfs_btree_rec *);
पूर्णांक xfs_btree_new_iroot(काष्ठा xfs_btree_cur *, पूर्णांक *, पूर्णांक *);
पूर्णांक xfs_btree_insert(काष्ठा xfs_btree_cur *, पूर्णांक *);
पूर्णांक xfs_btree_delete(काष्ठा xfs_btree_cur *, पूर्णांक *);
पूर्णांक xfs_btree_get_rec(काष्ठा xfs_btree_cur *, जोड़ xfs_btree_rec **, पूर्णांक *);
पूर्णांक xfs_btree_change_owner(काष्ठा xfs_btree_cur *cur, uपूर्णांक64_t new_owner,
			   काष्ठा list_head *buffer_list);

/*
 * btree block CRC helpers
 */
व्योम xfs_btree_lblock_calc_crc(काष्ठा xfs_buf *);
bool xfs_btree_lblock_verअगरy_crc(काष्ठा xfs_buf *);
व्योम xfs_btree_sblock_calc_crc(काष्ठा xfs_buf *);
bool xfs_btree_sblock_verअगरy_crc(काष्ठा xfs_buf *);

/*
 * Internal btree helpers also used by xfs_bmap.c.
 */
व्योम xfs_btree_log_block(काष्ठा xfs_btree_cur *, काष्ठा xfs_buf *, पूर्णांक);
व्योम xfs_btree_log_recs(काष्ठा xfs_btree_cur *, काष्ठा xfs_buf *, पूर्णांक, पूर्णांक);

/*
 * Helpers.
 */
अटल अंतरभूत पूर्णांक xfs_btree_get_numrecs(काष्ठा xfs_btree_block *block)
अणु
	वापस be16_to_cpu(block->bb_numrecs);
पूर्ण

अटल अंतरभूत व्योम xfs_btree_set_numrecs(काष्ठा xfs_btree_block *block,
		uपूर्णांक16_t numrecs)
अणु
	block->bb_numrecs = cpu_to_be16(numrecs);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_btree_get_level(काष्ठा xfs_btree_block *block)
अणु
	वापस be16_to_cpu(block->bb_level);
पूर्ण


/*
 * Min and max functions क्रम extlen, agblock, fileoff, and filblks types.
 */
#घोषणा	XFS_EXTLEN_MIN(a,b)	min_t(xfs_extlen_t, (a), (b))
#घोषणा	XFS_EXTLEN_MAX(a,b)	max_t(xfs_extlen_t, (a), (b))
#घोषणा	XFS_AGBLOCK_MIN(a,b)	min_t(xfs_agblock_t, (a), (b))
#घोषणा	XFS_AGBLOCK_MAX(a,b)	max_t(xfs_agblock_t, (a), (b))
#घोषणा	XFS_खाताOFF_MIN(a,b)	min_t(xfs_fileoff_t, (a), (b))
#घोषणा	XFS_खाताOFF_MAX(a,b)	max_t(xfs_fileoff_t, (a), (b))
#घोषणा	XFS_FILBLKS_MIN(a,b)	min_t(xfs_filblks_t, (a), (b))
#घोषणा	XFS_FILBLKS_MAX(a,b)	max_t(xfs_filblks_t, (a), (b))

xfs_failaddr_t xfs_btree_sblock_v5hdr_verअगरy(काष्ठा xfs_buf *bp);
xfs_failaddr_t xfs_btree_sblock_verअगरy(काष्ठा xfs_buf *bp,
		अचिन्हित पूर्णांक max_recs);
xfs_failaddr_t xfs_btree_lblock_v5hdr_verअगरy(काष्ठा xfs_buf *bp,
		uपूर्णांक64_t owner);
xfs_failaddr_t xfs_btree_lblock_verअगरy(काष्ठा xfs_buf *bp,
		अचिन्हित पूर्णांक max_recs);

uपूर्णांक xfs_btree_compute_maxlevels(uपूर्णांक *limits, अचिन्हित दीर्घ len);
अचिन्हित दीर्घ दीर्घ xfs_btree_calc_size(uपूर्णांक *limits, अचिन्हित दीर्घ दीर्घ len);

/*
 * Return codes क्रम the query range iterator function are 0 to जारी
 * iterating, and non-zero to stop iterating.  Any non-zero value will be
 * passed up to the _query_range caller.  The special value -ECANCELED can be
 * used to stop iteration, because _query_range never generates that error
 * code on its own.
 */
प्रकार पूर्णांक (*xfs_btree_query_range_fn)(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_rec *rec, व्योम *priv);

पूर्णांक xfs_btree_query_range(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_irec *low_rec, जोड़ xfs_btree_irec *high_rec,
		xfs_btree_query_range_fn fn, व्योम *priv);
पूर्णांक xfs_btree_query_all(काष्ठा xfs_btree_cur *cur, xfs_btree_query_range_fn fn,
		व्योम *priv);

प्रकार पूर्णांक (*xfs_btree_visit_blocks_fn)(काष्ठा xfs_btree_cur *cur, पूर्णांक level,
		व्योम *data);
/* Visit record blocks. */
#घोषणा XFS_BTREE_VISIT_RECORDS		(1 << 0)
/* Visit leaf blocks. */
#घोषणा XFS_BTREE_VISIT_LEAVES		(1 << 1)
/* Visit all blocks. */
#घोषणा XFS_BTREE_VISIT_ALL		(XFS_BTREE_VISIT_RECORDS | \
					 XFS_BTREE_VISIT_LEAVES)
पूर्णांक xfs_btree_visit_blocks(काष्ठा xfs_btree_cur *cur,
		xfs_btree_visit_blocks_fn fn, अचिन्हित पूर्णांक flags, व्योम *data);

पूर्णांक xfs_btree_count_blocks(काष्ठा xfs_btree_cur *cur, xfs_extlen_t *blocks);

जोड़ xfs_btree_rec *xfs_btree_rec_addr(काष्ठा xfs_btree_cur *cur, पूर्णांक n,
		काष्ठा xfs_btree_block *block);
जोड़ xfs_btree_key *xfs_btree_key_addr(काष्ठा xfs_btree_cur *cur, पूर्णांक n,
		काष्ठा xfs_btree_block *block);
जोड़ xfs_btree_key *xfs_btree_high_key_addr(काष्ठा xfs_btree_cur *cur, पूर्णांक n,
		काष्ठा xfs_btree_block *block);
जोड़ xfs_btree_ptr *xfs_btree_ptr_addr(काष्ठा xfs_btree_cur *cur, पूर्णांक n,
		काष्ठा xfs_btree_block *block);
पूर्णांक xfs_btree_lookup_get_block(काष्ठा xfs_btree_cur *cur, पूर्णांक level,
		जोड़ xfs_btree_ptr *pp, काष्ठा xfs_btree_block **blkp);
काष्ठा xfs_btree_block *xfs_btree_get_block(काष्ठा xfs_btree_cur *cur,
		पूर्णांक level, काष्ठा xfs_buf **bpp);
bool xfs_btree_ptr_is_null(काष्ठा xfs_btree_cur *cur, जोड़ xfs_btree_ptr *ptr);
पूर्णांक64_t xfs_btree_dअगरf_two_ptrs(काष्ठा xfs_btree_cur *cur,
				स्थिर जोड़ xfs_btree_ptr *a,
				स्थिर जोड़ xfs_btree_ptr *b);
व्योम xfs_btree_get_sibling(काष्ठा xfs_btree_cur *cur,
			   काष्ठा xfs_btree_block *block,
			   जोड़ xfs_btree_ptr *ptr, पूर्णांक lr);
व्योम xfs_btree_get_keys(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_btree_block *block, जोड़ xfs_btree_key *key);
जोड़ xfs_btree_key *xfs_btree_high_key_from_key(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_key *key);
पूर्णांक xfs_btree_has_record(काष्ठा xfs_btree_cur *cur, जोड़ xfs_btree_irec *low,
		जोड़ xfs_btree_irec *high, bool *exists);
bool xfs_btree_has_more_records(काष्ठा xfs_btree_cur *cur);
काष्ठा xfs_अगरork *xfs_btree_अगरork_ptr(काष्ठा xfs_btree_cur *cur);

/* Does this cursor poपूर्णांक to the last block in the given level? */
अटल अंतरभूत bool
xfs_btree_islastblock(
	xfs_btree_cur_t		*cur,
	पूर्णांक			level)
अणु
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;

	block = xfs_btree_get_block(cur, level, &bp);
	ASSERT(block && xfs_btree_check_block(cur, block, level, bp) == 0);

	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस block->bb_u.l.bb_rightsib == cpu_to_be64(शून्यFSBLOCK);
	वापस block->bb_u.s.bb_rightsib == cpu_to_be32(शून्यAGBLOCK);
पूर्ण

व्योम xfs_btree_set_ptr_null(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_ptr *ptr);
पूर्णांक xfs_btree_get_buf_block(काष्ठा xfs_btree_cur *cur, जोड़ xfs_btree_ptr *ptr,
		काष्ठा xfs_btree_block **block, काष्ठा xfs_buf **bpp);
व्योम xfs_btree_set_sibling(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_btree_block *block, जोड़ xfs_btree_ptr *ptr,
		पूर्णांक lr);
व्योम xfs_btree_init_block_cur(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_buf *bp, पूर्णांक level, पूर्णांक numrecs);
व्योम xfs_btree_copy_ptrs(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_ptr *dst_ptr,
		स्थिर जोड़ xfs_btree_ptr *src_ptr, पूर्णांक numptrs);
व्योम xfs_btree_copy_keys(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_key *dst_key, जोड़ xfs_btree_key *src_key,
		पूर्णांक numkeys);

#पूर्ण_अगर	/* __XFS_BTREE_H__ */
