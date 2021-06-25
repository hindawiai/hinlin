<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BMAP_H__
#घोषणा	__XFS_BMAP_H__

काष्ठा getbmap;
काष्ठा xfs_bmbt_irec;
काष्ठा xfs_अगरork;
काष्ठा xfs_inode;
काष्ठा xfs_mount;
काष्ठा xfs_trans;

बाह्य kmem_zone_t	*xfs_bmap_मुक्त_item_zone;

/*
 * Argument काष्ठाure क्रम xfs_bmap_alloc.
 */
काष्ठा xfs_bदो_स्मृतिa अणु
	काष्ठा xfs_trans	*tp;	/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip;	/* incore inode poपूर्णांकer */
	काष्ठा xfs_bmbt_irec	prev;	/* extent beक्रमe the new one */
	काष्ठा xfs_bmbt_irec	got;	/* extent after, or delayed */

	xfs_fileoff_t		offset;	/* offset in file filling in */
	xfs_extlen_t		length;	/* i/o length asked/allocated */
	xfs_fsblock_t		blkno;	/* starting block of new extent */

	काष्ठा xfs_btree_cur	*cur;	/* btree cursor */
	काष्ठा xfs_iext_cursor	icur;	/* incore extent cursor */
	पूर्णांक			nallocs;/* number of extents alloc'd */
	पूर्णांक			logflags;/* flags क्रम transaction logging */

	xfs_extlen_t		total;	/* total blocks needed क्रम xaction */
	xfs_extlen_t		minlen;	/* minimum allocation size (blocks) */
	xfs_extlen_t		minleft; /* amount must be left after alloc */
	bool			eof;	/* set अगर allocating past last extent */
	bool			wasdel;	/* replacing a delayed allocation */
	bool			aeof;	/* allocated space at eof */
	bool			conv;	/* overwriting unwritten extents */
	पूर्णांक			datatype;/* data type being allocated */
	पूर्णांक			flags;
पूर्ण;

/*
 * List of extents to be मुक्त "later".
 * The list is kept sorted on xbf_startblock.
 */
काष्ठा xfs_extent_मुक्त_item
अणु
	xfs_fsblock_t		xefi_startblock;/* starting fs block number */
	xfs_extlen_t		xefi_blockcount;/* number of blocks in extent */
	bool			xefi_skip_discard;
	काष्ठा list_head	xefi_list;
	काष्ठा xfs_owner_info	xefi_oinfo;	/* extent owner */
पूर्ण;

#घोषणा	XFS_BMAP_MAX_NMAP	4

/*
 * Flags क्रम xfs_bmapi_*
 */
#घोषणा XFS_BMAPI_ENTIRE	0x001	/* वापस entire extent, not trimmed */
#घोषणा XFS_BMAPI_METADATA	0x002	/* mapping metadata not user data */
#घोषणा XFS_BMAPI_ATTRFORK	0x004	/* use attribute विभाजन not data */
#घोषणा XFS_BMAPI_PREALLOC	0x008	/* pपुनः_स्मृतिation op: unwritten space */
#घोषणा XFS_BMAPI_CONTIG	0x020	/* must allocate only one extent */
/*
 * unwritten extent conversion - this needs ग_लिखो cache flushing and no additional
 * allocation alignments. When specअगरied with XFS_BMAPI_PREALLOC it converts
 * from written to unwritten, otherwise convert from unwritten to written.
 */
#घोषणा XFS_BMAPI_CONVERT	0x040

/*
 * allocate zeroed extents - this requires all newly allocated user data extents
 * to be initialised to zero. It will be ignored अगर XFS_BMAPI_METADATA is set.
 * Use in conjunction with XFS_BMAPI_CONVERT to convert unwritten extents found
 * during the allocation range to zeroed written extents.
 */
#घोषणा XFS_BMAPI_ZERO		0x080

/*
 * Map the inode offset to the block given in ap->firstblock.  Primarily
 * used क्रम reflink.  The range must be in a hole, and this flag cannot be
 * turned on with PREALLOC or CONVERT, and cannot be used on the attr विभाजन.
 *
 * For bunmapi, this flag unmaps the range without adjusting quota, reducing
 * refcount, or मुक्तing the blocks.
 */
#घोषणा XFS_BMAPI_REMAP		0x100

/* Map something in the CoW विभाजन. */
#घोषणा XFS_BMAPI_COWFORK	0x200

/* Skip online discard of मुक्तd extents */
#घोषणा XFS_BMAPI_NODISCARD	0x1000

/* Do not update the rmap btree.  Used क्रम reस्थिरructing bmbt from rmapbt. */
#घोषणा XFS_BMAPI_NORMAP	0x2000

#घोषणा XFS_BMAPI_FLAGS \
	अणु XFS_BMAPI_ENTIRE,	"ENTIRE" पूर्ण, \
	अणु XFS_BMAPI_METADATA,	"METADATA" पूर्ण, \
	अणु XFS_BMAPI_ATTRFORK,	"ATTRFORK" पूर्ण, \
	अणु XFS_BMAPI_PREALLOC,	"PREALLOC" पूर्ण, \
	अणु XFS_BMAPI_CONTIG,	"CONTIG" पूर्ण, \
	अणु XFS_BMAPI_CONVERT,	"CONVERT" पूर्ण, \
	अणु XFS_BMAPI_ZERO,	"ZERO" पूर्ण, \
	अणु XFS_BMAPI_REMAP,	"REMAP" पूर्ण, \
	अणु XFS_BMAPI_COWFORK,	"COWFORK" पूर्ण, \
	अणु XFS_BMAPI_NODISCARD,	"NODISCARD" पूर्ण, \
	अणु XFS_BMAPI_NORMAP,	"NORMAP" पूर्ण


अटल अंतरभूत पूर्णांक xfs_bmapi_aflag(पूर्णांक w)
अणु
	वापस (w == XFS_ATTR_FORK ? XFS_BMAPI_ATTRFORK :
	       (w == XFS_COW_FORK ? XFS_BMAPI_COWFORK : 0));
पूर्ण

अटल अंतरभूत पूर्णांक xfs_bmapi_whichविभाजन(पूर्णांक bmapi_flags)
अणु
	अगर (bmapi_flags & XFS_BMAPI_COWFORK)
		वापस XFS_COW_FORK;
	अन्यथा अगर (bmapi_flags & XFS_BMAPI_ATTRFORK)
		वापस XFS_ATTR_FORK;
	वापस XFS_DATA_FORK;
पूर्ण

/*
 * Special values क्रम xfs_bmbt_irec_t br_startblock field.
 */
#घोषणा	DELAYSTARTBLOCK		((xfs_fsblock_t)-1LL)
#घोषणा	HOLESTARTBLOCK		((xfs_fsblock_t)-2LL)

/*
 * Flags क्रम xfs_bmap_add_extent*.
 */
#घोषणा BMAP_LEFT_CONTIG	(1 << 0)
#घोषणा BMAP_RIGHT_CONTIG	(1 << 1)
#घोषणा BMAP_LEFT_FILLING	(1 << 2)
#घोषणा BMAP_RIGHT_FILLING	(1 << 3)
#घोषणा BMAP_LEFT_DELAY		(1 << 4)
#घोषणा BMAP_RIGHT_DELAY	(1 << 5)
#घोषणा BMAP_LEFT_VALID		(1 << 6)
#घोषणा BMAP_RIGHT_VALID	(1 << 7)
#घोषणा BMAP_ATTRFORK		(1 << 8)
#घोषणा BMAP_COWFORK		(1 << 9)

#घोषणा XFS_BMAP_EXT_FLAGS \
	अणु BMAP_LEFT_CONTIG,	"LC" पूर्ण, \
	अणु BMAP_RIGHT_CONTIG,	"RC" पूर्ण, \
	अणु BMAP_LEFT_FILLING,	"LF" पूर्ण, \
	अणु BMAP_RIGHT_FILLING,	"RF" पूर्ण, \
	अणु BMAP_ATTRFORK,	"ATTR" पूर्ण, \
	अणु BMAP_COWFORK,		"COW" पूर्ण

/* Return true अगर the extent is an allocated extent, written or not. */
अटल अंतरभूत bool xfs_bmap_is_real_extent(काष्ठा xfs_bmbt_irec *irec)
अणु
	वापस irec->br_startblock != HOLESTARTBLOCK &&
		irec->br_startblock != DELAYSTARTBLOCK &&
		!isnullstartblock(irec->br_startblock);
पूर्ण

/*
 * Return true अगर the extent is a real, allocated extent, or false अगर it is  a
 * delayed allocation, and unwritten extent or a hole.
 */
अटल अंतरभूत bool xfs_bmap_is_written_extent(काष्ठा xfs_bmbt_irec *irec)
अणु
	वापस xfs_bmap_is_real_extent(irec) &&
	       irec->br_state != XFS_EXT_UNWRITTEN;
पूर्ण

/*
 * Check the mapping क्रम obviously garbage allocations that could trash the
 * fileप्रणाली immediately.
 */
#घोषणा xfs_valid_startblock(ip, startblock) \
	((startblock) != 0 || XFS_IS_REALTIME_INODE(ip))

व्योम	xfs_trim_extent(काष्ठा xfs_bmbt_irec *irec, xfs_fileoff_t bno,
		xfs_filblks_t len);
अचिन्हित पूर्णांक xfs_bmap_compute_attr_offset(काष्ठा xfs_mount *mp);
पूर्णांक	xfs_bmap_add_attrविभाजन(काष्ठा xfs_inode *ip, पूर्णांक size, पूर्णांक rsvd);
पूर्णांक	xfs_bmap_set_attrविभाजनoff(काष्ठा xfs_inode *ip, पूर्णांक size, पूर्णांक *version);
व्योम	xfs_bmap_local_to_extents_empty(काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन);
व्योम	__xfs_bmap_add_मुक्त(काष्ठा xfs_trans *tp, xfs_fsblock_t bno,
		xfs_filblks_t len, स्थिर काष्ठा xfs_owner_info *oinfo,
		bool skip_discard);
व्योम	xfs_bmap_compute_maxlevels(काष्ठा xfs_mount *mp, पूर्णांक whichविभाजन);
पूर्णांक	xfs_bmap_first_unused(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_extlen_t len, xfs_fileoff_t *unused, पूर्णांक whichविभाजन);
पूर्णांक	xfs_bmap_last_beक्रमe(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t *last_block, पूर्णांक whichविभाजन);
पूर्णांक	xfs_bmap_last_offset(काष्ठा xfs_inode *ip, xfs_fileoff_t *unused,
		पूर्णांक whichविभाजन);
पूर्णांक	xfs_bmapi_पढ़ो(काष्ठा xfs_inode *ip, xfs_fileoff_t bno,
		xfs_filblks_t len, काष्ठा xfs_bmbt_irec *mval,
		पूर्णांक *nmap, पूर्णांक flags);
पूर्णांक	xfs_bmapi_ग_लिखो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t bno, xfs_filblks_t len, पूर्णांक flags,
		xfs_extlen_t total, काष्ठा xfs_bmbt_irec *mval, पूर्णांक *nmap);
पूर्णांक	__xfs_bunmapi(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t bno, xfs_filblks_t *rlen, पूर्णांक flags,
		xfs_extnum_t nexts);
पूर्णांक	xfs_bunmapi(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t bno, xfs_filblks_t len, पूर्णांक flags,
		xfs_extnum_t nexts, पूर्णांक *करोne);
पूर्णांक	xfs_bmap_del_extent_delay(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *got,
		काष्ठा xfs_bmbt_irec *del);
व्योम	xfs_bmap_del_extent_cow(काष्ठा xfs_inode *ip,
		काष्ठा xfs_iext_cursor *cur, काष्ठा xfs_bmbt_irec *got,
		काष्ठा xfs_bmbt_irec *del);
uपूर्णांक	xfs_शेष_attroffset(काष्ठा xfs_inode *ip);
पूर्णांक	xfs_bmap_collapse_extents(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t *next_fsb, xfs_fileoff_t offset_shअगरt_fsb,
		bool *करोne);
पूर्णांक	xfs_bmap_can_insert_extents(काष्ठा xfs_inode *ip, xfs_fileoff_t off,
		xfs_fileoff_t shअगरt);
पूर्णांक	xfs_bmap_insert_extents(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t *next_fsb, xfs_fileoff_t offset_shअगरt_fsb,
		bool *करोne, xfs_fileoff_t stop_fsb);
पूर्णांक	xfs_bmap_split_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t split_offset);
पूर्णांक	xfs_bmapi_reserve_delalloc(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		xfs_fileoff_t off, xfs_filblks_t len, xfs_filblks_t pपुनः_स्मृति,
		काष्ठा xfs_bmbt_irec *got, काष्ठा xfs_iext_cursor *cur,
		पूर्णांक eof);
पूर्णांक	xfs_bmapi_convert_delalloc(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		xfs_off_t offset, काष्ठा iomap *iomap, अचिन्हित पूर्णांक *seq);
पूर्णांक	xfs_bmap_add_extent_unwritten_real(काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		काष्ठा xfs_iext_cursor *icur, काष्ठा xfs_btree_cur **curp,
		काष्ठा xfs_bmbt_irec *new, पूर्णांक *logflagsp);

अटल अंतरभूत व्योम
xfs_bmap_add_मुक्त(
	काष्ठा xfs_trans		*tp,
	xfs_fsblock_t			bno,
	xfs_filblks_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	__xfs_bmap_add_मुक्त(tp, bno, len, oinfo, false);
पूर्ण

क्रमागत xfs_bmap_पूर्णांकent_type अणु
	XFS_BMAP_MAP = 1,
	XFS_BMAP_UNMAP,
पूर्ण;

काष्ठा xfs_bmap_पूर्णांकent अणु
	काष्ठा list_head			bi_list;
	क्रमागत xfs_bmap_पूर्णांकent_type		bi_type;
	काष्ठा xfs_inode			*bi_owner;
	पूर्णांक					bi_whichविभाजन;
	काष्ठा xfs_bmbt_irec			bi_bmap;
पूर्ण;

पूर्णांक	xfs_bmap_finish_one(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		क्रमागत xfs_bmap_पूर्णांकent_type type, पूर्णांक whichविभाजन,
		xfs_fileoff_t startoff, xfs_fsblock_t startblock,
		xfs_filblks_t *blockcount, xfs_exntst_t state);
व्योम	xfs_bmap_map_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		काष्ठा xfs_bmbt_irec *imap);
व्योम	xfs_bmap_unmap_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		काष्ठा xfs_bmbt_irec *imap);

अटल अंतरभूत पूर्णांक xfs_bmap_विभाजन_to_state(पूर्णांक whichविभाजन)
अणु
	चयन (whichविभाजन) अणु
	हाल XFS_ATTR_FORK:
		वापस BMAP_ATTRFORK;
	हाल XFS_COW_FORK:
		वापस BMAP_COWFORK;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

xfs_failaddr_t xfs_bmap_validate_extent(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		काष्ठा xfs_bmbt_irec *irec);

पूर्णांक	xfs_bmapi_remap(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		xfs_fileoff_t bno, xfs_filblks_t len, xfs_fsblock_t startblock,
		पूर्णांक flags);

#पूर्ण_अगर	/* __XFS_BMAP_H__ */
