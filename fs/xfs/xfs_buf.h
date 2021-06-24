<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BUF_H__
#घोषणा __XFS_BUF_H__

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/dax.h>
#समावेश <linux/uपन.स>
#समावेश <linux/list_lru.h>

/*
 *	Base types
 */
काष्ठा xfs_buf;

#घोषणा XFS_BUF_DADDR_शून्य	((xfs_daddr_t) (-1LL))

#घोषणा XBF_READ	 (1 << 0) /* buffer पूर्णांकended क्रम पढ़ोing from device */
#घोषणा XBF_WRITE	 (1 << 1) /* buffer पूर्णांकended क्रम writing to device */
#घोषणा XBF_READ_AHEAD	 (1 << 2) /* asynchronous पढ़ो-ahead */
#घोषणा XBF_NO_IOACCT	 (1 << 3) /* bypass I/O accounting (non-LRU bufs) */
#घोषणा XBF_ASYNC	 (1 << 4) /* initiator will not रुको क्रम completion */
#घोषणा XBF_DONE	 (1 << 5) /* all pages in the buffer uptodate */
#घोषणा XBF_STALE	 (1 << 6) /* buffer has been staled, करो not find it */
#घोषणा XBF_WRITE_FAIL	 (1 << 7) /* async ग_लिखोs have failed on this buffer */

/* buffer type flags क्रम ग_लिखो callbacks */
#घोषणा _XBF_INODES	 (1 << 16)/* inode buffer */
#घोषणा _XBF_DQUOTS	 (1 << 17)/* dquot buffer */
#घोषणा _XBF_LOGRECOVERY	 (1 << 18)/* log recovery buffer */

/* flags used only पूर्णांकernally */
#घोषणा _XBF_PAGES	 (1 << 20)/* backed by refcounted pages */
#घोषणा _XBF_KMEM	 (1 << 21)/* backed by heap memory */
#घोषणा _XBF_DELWRI_Q	 (1 << 22)/* buffer on a delwri queue */

/* flags used only as arguments to access routines */
#घोषणा XBF_TRYLOCK	 (1 << 30)/* lock requested, but करो not रुको */
#घोषणा XBF_UNMAPPED	 (1 << 31)/* करो not map the buffer */

प्रकार अचिन्हित पूर्णांक xfs_buf_flags_t;

#घोषणा XFS_BUF_FLAGS \
	अणु XBF_READ,		"READ" पूर्ण, \
	अणु XBF_WRITE,		"WRITE" पूर्ण, \
	अणु XBF_READ_AHEAD,	"READ_AHEAD" पूर्ण, \
	अणु XBF_NO_IOACCT,	"NO_IOACCT" पूर्ण, \
	अणु XBF_ASYNC,		"ASYNC" पूर्ण, \
	अणु XBF_DONE,		"DONE" पूर्ण, \
	अणु XBF_STALE,		"STALE" पूर्ण, \
	अणु XBF_WRITE_FAIL,	"WRITE_FAIL" पूर्ण, \
	अणु _XBF_INODES,		"INODES" पूर्ण, \
	अणु _XBF_DQUOTS,		"DQUOTS" पूर्ण, \
	अणु _XBF_LOGRECOVERY,		"LOG_RECOVERY" पूर्ण, \
	अणु _XBF_PAGES,		"PAGES" पूर्ण, \
	अणु _XBF_KMEM,		"KMEM" पूर्ण, \
	अणु _XBF_DELWRI_Q,	"DELWRI_Q" पूर्ण, \
	/* The following पूर्णांकerface flags should never be set */ \
	अणु XBF_TRYLOCK,		"TRYLOCK" पूर्ण, \
	अणु XBF_UNMAPPED,		"UNMAPPED" पूर्ण

/*
 * Internal state flags.
 */
#घोषणा XFS_BSTATE_DISPOSE	 (1 << 0)	/* buffer being discarded */
#घोषणा XFS_BSTATE_IN_FLIGHT	 (1 << 1)	/* I/O in flight */

/*
 * The xfs_buftarg contains 2 notions of "sector size" -
 *
 * 1) The metadata sector size, which is the minimum unit and
 *    alignment of IO which will be perक्रमmed by metadata operations.
 * 2) The device logical sector size
 *
 * The first is specअगरied at mkfs समय, and is stored on-disk in the
 * superblock's sb_sectsize.
 *
 * The latter is derived from the underlying device, and controls direct IO
 * alignment स्थिरraपूर्णांकs.
 */
प्रकार काष्ठा xfs_buftarg अणु
	dev_t			bt_dev;
	काष्ठा block_device	*bt_bdev;
	काष्ठा dax_device	*bt_daxdev;
	काष्ठा xfs_mount	*bt_mount;
	अचिन्हित पूर्णांक		bt_meta_sectorsize;
	माप_प्रकार			bt_meta_sectormask;
	माप_प्रकार			bt_logical_sectorsize;
	माप_प्रकार			bt_logical_sectormask;

	/* LRU control काष्ठाures */
	काष्ठा shrinker		bt_shrinker;
	काष्ठा list_lru		bt_lru;

	काष्ठा percpu_counter	bt_io_count;
	काष्ठा ratelimit_state	bt_ioerror_rl;
पूर्ण xfs_buftarg_t;

#घोषणा XB_PAGES	2

काष्ठा xfs_buf_map अणु
	xfs_daddr_t		bm_bn;	/* block number क्रम I/O */
	पूर्णांक			bm_len;	/* size of I/O */
पूर्ण;

#घोषणा DEFINE_SINGLE_BUF_MAP(map, blkno, numblk) \
	काष्ठा xfs_buf_map (map) = अणु .bm_bn = (blkno), .bm_len = (numblk) पूर्ण;

काष्ठा xfs_buf_ops अणु
	अक्षर *name;
	जोड़ अणु
		__be32 magic[2];	/* v4 and v5 on disk magic values */
		__be16 magic16[2];	/* v4 and v5 on disk magic values */
	पूर्ण;
	व्योम (*verअगरy_पढ़ो)(काष्ठा xfs_buf *);
	व्योम (*verअगरy_ग_लिखो)(काष्ठा xfs_buf *);
	xfs_failaddr_t (*verअगरy_काष्ठा)(काष्ठा xfs_buf *bp);
पूर्ण;

काष्ठा xfs_buf अणु
	/*
	 * first cacheline holds all the fields needed क्रम an uncontended cache
	 * hit to be fully processed. The semaphore straddles the cacheline
	 * boundary, but the counter and lock sits on the first cacheline,
	 * which is the only bit that is touched अगर we hit the semaphore
	 * fast-path on locking.
	 */
	काष्ठा rhash_head	b_rhash_head;	/* pag buffer hash node */
	xfs_daddr_t		b_bn;		/* block number of buffer */
	पूर्णांक			b_length;	/* size of buffer in BBs */
	atomic_t		b_hold;		/* reference count */
	atomic_t		b_lru_ref;	/* lru reclaim ref count */
	xfs_buf_flags_t		b_flags;	/* status flags */
	काष्ठा semaphore	b_sema;		/* semaphore क्रम lockables */

	/*
	 * concurrent access to b_lru and b_lru_flags are रक्षित by
	 * bt_lru_lock and not by b_sema
	 */
	काष्ठा list_head	b_lru;		/* lru list */
	spinlock_t		b_lock;		/* पूर्णांकernal state lock */
	अचिन्हित पूर्णांक		b_state;	/* पूर्णांकernal state flags */
	पूर्णांक			b_io_error;	/* पूर्णांकernal IO error state */
	रुको_queue_head_t	b_रुकोers;	/* unpin रुकोers */
	काष्ठा list_head	b_list;
	काष्ठा xfs_perag	*b_pag;		/* contains rbtree root */
	काष्ठा xfs_mount	*b_mount;
	काष्ठा xfs_buftarg	*b_target;	/* buffer target (device) */
	व्योम			*b_addr;	/* भव address of buffer */
	काष्ठा work_काष्ठा	b_ioend_work;
	काष्ठा completion	b_ioरुको;	/* queue क्रम I/O रुकोers */
	काष्ठा xfs_buf_log_item	*b_log_item;
	काष्ठा list_head	b_li_list;	/* Log items list head */
	काष्ठा xfs_trans	*b_transp;
	काष्ठा page		**b_pages;	/* array of page poपूर्णांकers */
	काष्ठा page		*b_page_array[XB_PAGES]; /* अंतरभूत pages */
	काष्ठा xfs_buf_map	*b_maps;	/* compound buffer map */
	काष्ठा xfs_buf_map	__b_map;	/* अंतरभूत compound buffer map */
	पूर्णांक			b_map_count;
	atomic_t		b_pin_count;	/* pin count */
	atomic_t		b_io_reमुख्यing;	/* #outstanding I/O requests */
	अचिन्हित पूर्णांक		b_page_count;	/* size of page array */
	अचिन्हित पूर्णांक		b_offset;	/* page offset in first page */
	पूर्णांक			b_error;	/* error code on I/O */

	/*
	 * async ग_लिखो failure retry count. Initialised to zero on the first
	 * failure, then when it exceeds the maximum configured without a
	 * success the ग_लिखो is considered to be failed permanently and the
	 * ioकरोne handler will take appropriate action.
	 *
	 * For retry समयouts, we record the jअगरfie of the first failure. This
	 * means that we can change the retry समयout क्रम buffers alपढ़ोy under
	 * I/O and thus aव्योम getting stuck in a retry loop with a दीर्घ समयout.
	 *
	 * last_error is used to ensure that we are getting repeated errors, not
	 * dअगरferent errors. e.g. a block device might change ENOSPC to EIO when
	 * a failure समयout occurs, so we want to re-initialise the error
	 * retry behaviour appropriately when that happens.
	 */
	पूर्णांक			b_retries;
	अचिन्हित दीर्घ		b_first_retry_समय; /* in jअगरfies */
	पूर्णांक			b_last_error;

	स्थिर काष्ठा xfs_buf_ops	*b_ops;
पूर्ण;

/* Finding and Reading Buffers */
काष्ठा xfs_buf *xfs_buf_incore(काष्ठा xfs_buftarg *target,
			   xfs_daddr_t blkno, माप_प्रकार numblks,
			   xfs_buf_flags_t flags);

पूर्णांक xfs_buf_get_map(काष्ठा xfs_buftarg *target, काष्ठा xfs_buf_map *map,
		पूर्णांक nmaps, xfs_buf_flags_t flags, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_buf_पढ़ो_map(काष्ठा xfs_buftarg *target, काष्ठा xfs_buf_map *map,
		पूर्णांक nmaps, xfs_buf_flags_t flags, काष्ठा xfs_buf **bpp,
		स्थिर काष्ठा xfs_buf_ops *ops, xfs_failaddr_t fa);
व्योम xfs_buf_पढ़ोahead_map(काष्ठा xfs_buftarg *target,
			       काष्ठा xfs_buf_map *map, पूर्णांक nmaps,
			       स्थिर काष्ठा xfs_buf_ops *ops);

अटल अंतरभूत पूर्णांक
xfs_buf_get(
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	माप_प्रकार			numblks,
	काष्ठा xfs_buf		**bpp)
अणु
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);

	वापस xfs_buf_get_map(target, &map, 1, 0, bpp);
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_buf_पढ़ो(
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	माप_प्रकार			numblks,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);

	वापस xfs_buf_पढ़ो_map(target, &map, 1, flags, bpp, ops,
			__builtin_वापस_address(0));
पूर्ण

अटल अंतरभूत व्योम
xfs_buf_पढ़ोahead(
	काष्ठा xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	माप_प्रकार			numblks,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);
	वापस xfs_buf_पढ़ोahead_map(target, &map, 1, ops);
पूर्ण

पूर्णांक xfs_buf_get_uncached(काष्ठा xfs_buftarg *target, माप_प्रकार numblks, पूर्णांक flags,
		काष्ठा xfs_buf **bpp);
पूर्णांक xfs_buf_पढ़ो_uncached(काष्ठा xfs_buftarg *target, xfs_daddr_t daddr,
			  माप_प्रकार numblks, पूर्णांक flags, काष्ठा xfs_buf **bpp,
			  स्थिर काष्ठा xfs_buf_ops *ops);
पूर्णांक _xfs_buf_पढ़ो(काष्ठा xfs_buf *bp, xfs_buf_flags_t flags);
व्योम xfs_buf_hold(काष्ठा xfs_buf *bp);

/* Releasing Buffers */
बाह्य व्योम xfs_buf_rele(काष्ठा xfs_buf *);

/* Locking and Unlocking Buffers */
बाह्य पूर्णांक xfs_buf_trylock(काष्ठा xfs_buf *);
बाह्य व्योम xfs_buf_lock(काष्ठा xfs_buf *);
बाह्य व्योम xfs_buf_unlock(काष्ठा xfs_buf *);
#घोषणा xfs_buf_islocked(bp) \
	((bp)->b_sema.count <= 0)

अटल अंतरभूत व्योम xfs_buf_rअन्यथा(काष्ठा xfs_buf *bp)
अणु
	xfs_buf_unlock(bp);
	xfs_buf_rele(bp);
पूर्ण

/* Buffer Read and Write Routines */
बाह्य पूर्णांक xfs_bग_लिखो(काष्ठा xfs_buf *bp);

बाह्य व्योम __xfs_buf_ioerror(काष्ठा xfs_buf *bp, पूर्णांक error,
		xfs_failaddr_t failaddr);
#घोषणा xfs_buf_ioerror(bp, err) __xfs_buf_ioerror((bp), (err), __this_address)
बाह्य व्योम xfs_buf_ioerror_alert(काष्ठा xfs_buf *bp, xfs_failaddr_t fa);
व्योम xfs_buf_ioend_fail(काष्ठा xfs_buf *);
व्योम xfs_buf_zero(काष्ठा xfs_buf *bp, माप_प्रकार boff, माप_प्रकार bsize);
व्योम __xfs_buf_mark_corrupt(काष्ठा xfs_buf *bp, xfs_failaddr_t fa);
#घोषणा xfs_buf_mark_corrupt(bp) __xfs_buf_mark_corrupt((bp), __this_address)

/* Buffer Utility Routines */
बाह्य व्योम *xfs_buf_offset(काष्ठा xfs_buf *, माप_प्रकार);
बाह्य व्योम xfs_buf_stale(काष्ठा xfs_buf *bp);

/* Delayed Write Buffer Routines */
बाह्य व्योम xfs_buf_delwri_cancel(काष्ठा list_head *);
बाह्य bool xfs_buf_delwri_queue(काष्ठा xfs_buf *, काष्ठा list_head *);
बाह्य पूर्णांक xfs_buf_delwri_submit(काष्ठा list_head *);
बाह्य पूर्णांक xfs_buf_delwri_submit_noरुको(काष्ठा list_head *);
बाह्य पूर्णांक xfs_buf_delwri_pushbuf(काष्ठा xfs_buf *, काष्ठा list_head *);

/* Buffer Daemon Setup Routines */
बाह्य पूर्णांक xfs_buf_init(व्योम);
बाह्य व्योम xfs_buf_terminate(व्योम);

/*
 * These macros use the IO block map rather than b_bn. b_bn is now really
 * just क्रम the buffer cache index क्रम cached buffers. As IO करोes not use b_bn
 * anymore, uncached buffers करो not use b_bn at all and hence must modअगरy the IO
 * map directly. Uncached buffers are not allowed to be discontiguous, so this
 * is safe to करो.
 *
 * In future, uncached buffers will pass the block number directly to the io
 * request function and hence these macros will go away at that poपूर्णांक.
 */
#घोषणा XFS_BUF_ADDR(bp)		((bp)->b_maps[0].bm_bn)
#घोषणा XFS_BUF_SET_ADDR(bp, bno)	((bp)->b_maps[0].bm_bn = (xfs_daddr_t)(bno))

व्योम xfs_buf_set_ref(काष्ठा xfs_buf *bp, पूर्णांक lru_ref);

/*
 * If the buffer is alपढ़ोy on the LRU, करो nothing. Otherwise set the buffer
 * up with a reference count of 0 so it will be tossed from the cache when
 * released.
 */
अटल अंतरभूत व्योम xfs_buf_oneshot(काष्ठा xfs_buf *bp)
अणु
	अगर (!list_empty(&bp->b_lru) || atomic_पढ़ो(&bp->b_lru_ref) > 1)
		वापस;
	atomic_set(&bp->b_lru_ref, 0);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_buf_ispinned(काष्ठा xfs_buf *bp)
अणु
	वापस atomic_पढ़ो(&bp->b_pin_count);
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_buf_verअगरy_cksum(काष्ठा xfs_buf *bp, अचिन्हित दीर्घ cksum_offset)
अणु
	वापस xfs_verअगरy_cksum(bp->b_addr, BBTOB(bp->b_length),
				cksum_offset);
पूर्ण

अटल अंतरभूत व्योम
xfs_buf_update_cksum(काष्ठा xfs_buf *bp, अचिन्हित दीर्घ cksum_offset)
अणु
	xfs_update_cksum(bp->b_addr, BBTOB(bp->b_length),
			 cksum_offset);
पूर्ण

/*
 *	Handling of buftargs.
 */
बाह्य काष्ठा xfs_buftarg *xfs_alloc_buftarg(काष्ठा xfs_mount *,
		काष्ठा block_device *, काष्ठा dax_device *);
बाह्य व्योम xfs_मुक्त_buftarg(काष्ठा xfs_buftarg *);
बाह्य व्योम xfs_buftarg_रुको(काष्ठा xfs_buftarg *);
बाह्य व्योम xfs_buftarg_drain(काष्ठा xfs_buftarg *);
बाह्य पूर्णांक xfs_setsize_buftarg(काष्ठा xfs_buftarg *, अचिन्हित पूर्णांक);

#घोषणा xfs_माला_लोize_buftarg(buftarg)	block_size((buftarg)->bt_bdev)
#घोषणा xfs_पढ़ोonly_buftarg(buftarg)	bdev_पढ़ो_only((buftarg)->bt_bdev)

अटल अंतरभूत पूर्णांक
xfs_buftarg_dma_alignment(काष्ठा xfs_buftarg *bt)
अणु
	वापस queue_dma_alignment(bt->bt_bdev->bd_disk->queue);
पूर्ण

पूर्णांक xfs_buf_reverअगरy(काष्ठा xfs_buf *bp, स्थिर काष्ठा xfs_buf_ops *ops);
bool xfs_verअगरy_magic(काष्ठा xfs_buf *bp, __be32 dmagic);
bool xfs_verअगरy_magic16(काष्ठा xfs_buf *bp, __be16 dmagic);

#पूर्ण_अगर	/* __XFS_BUF_H__ */
