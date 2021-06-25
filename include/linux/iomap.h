<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_IOMAP_H
#घोषणा LINUX_IOMAP_H 1

#समावेश <linux/atomic.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/blkdev.h>

काष्ठा address_space;
काष्ठा fiemap_extent_info;
काष्ठा inode;
काष्ठा iomap_dio;
काष्ठा iomap_ग_लिखोpage_ctx;
काष्ठा iov_iter;
काष्ठा kiocb;
काष्ठा page;
काष्ठा vm_area_काष्ठा;
काष्ठा vm_fault;

/*
 * Types of block ranges क्रम iomap mappings:
 */
#घोषणा IOMAP_HOLE	0	/* no blocks allocated, need allocation */
#घोषणा IOMAP_DELALLOC	1	/* delayed allocation blocks */
#घोषणा IOMAP_MAPPED	2	/* blocks allocated at @addr */
#घोषणा IOMAP_UNWRITTEN	3	/* blocks allocated at @addr in unwritten state */
#घोषणा IOMAP_INLINE	4	/* data अंतरभूत in the inode */

/*
 * Flags reported by the file प्रणाली from iomap_begin:
 *
 * IOMAP_F_NEW indicates that the blocks have been newly allocated and need
 * zeroing क्रम areas that no data is copied to.
 *
 * IOMAP_F_सूचीTY indicates the inode has uncommitted metadata needed to access
 * written data and requires fdatasync to commit them to persistent storage.
 * This needs to take पूर्णांकo account metadata changes that *may* be made at IO
 * completion, such as file size updates from direct IO.
 *
 * IOMAP_F_SHARED indicates that the blocks are shared, and will need to be
 * unshared as part a ग_लिखो.
 *
 * IOMAP_F_MERGED indicates that the iomap contains the merge of multiple block
 * mappings.
 *
 * IOMAP_F_BUFFER_HEAD indicates that the file प्रणाली requires the use of
 * buffer heads क्रम this mapping.
 */
#घोषणा IOMAP_F_NEW		0x01
#घोषणा IOMAP_F_सूचीTY		0x02
#घोषणा IOMAP_F_SHARED		0x04
#घोषणा IOMAP_F_MERGED		0x08
#घोषणा IOMAP_F_BUFFER_HEAD	0x10
#घोषणा IOMAP_F_ZONE_APPEND	0x20

/*
 * Flags set by the core iomap code during operations:
 *
 * IOMAP_F_SIZE_CHANGED indicates to the iomap_end method that the file size
 * has changed as the result of this ग_लिखो operation.
 */
#घोषणा IOMAP_F_SIZE_CHANGED	0x100

/*
 * Flags from 0x1000 up are क्रम file प्रणाली specअगरic usage:
 */
#घोषणा IOMAP_F_PRIVATE		0x1000


/*
 * Magic value क्रम addr:
 */
#घोषणा IOMAP_शून्य_ADDR -1ULL	/* addr is not valid */

काष्ठा iomap_page_ops;

काष्ठा iomap अणु
	u64			addr; /* disk offset of mapping, bytes */
	loff_t			offset;	/* file offset of mapping, bytes */
	u64			length;	/* length of mapping, bytes */
	u16			type;	/* type of mapping */
	u16			flags;	/* flags क्रम mapping */
	काष्ठा block_device	*bdev;	/* block device क्रम I/O */
	काष्ठा dax_device	*dax_dev; /* dax_dev क्रम dax operations */
	व्योम			*अंतरभूत_data;
	व्योम			*निजी; /* fileप्रणाली निजी */
	स्थिर काष्ठा iomap_page_ops *page_ops;
पूर्ण;

अटल अंतरभूत sector_t
iomap_sector(काष्ठा iomap *iomap, loff_t pos)
अणु
	वापस (iomap->addr + pos - iomap->offset) >> SECTOR_SHIFT;
पूर्ण

/*
 * When a fileप्रणाली sets page_ops in an iomap mapping it वापसs, page_prepare
 * and page_करोne will be called क्रम each page written to.  This only applies to
 * buffered ग_लिखोs as unbuffered ग_लिखोs will not typically have pages
 * associated with them.
 *
 * When page_prepare succeeds, page_करोne will always be called to करो any
 * cleanup work necessary.  In that page_करोne call, @page will be शून्य अगर the
 * associated page could not be obtained.
 */
काष्ठा iomap_page_ops अणु
	पूर्णांक (*page_prepare)(काष्ठा inode *inode, loff_t pos, अचिन्हित len,
			काष्ठा iomap *iomap);
	व्योम (*page_करोne)(काष्ठा inode *inode, loff_t pos, अचिन्हित copied,
			काष्ठा page *page, काष्ठा iomap *iomap);
पूर्ण;

/*
 * Flags क्रम iomap_begin / iomap_end.  No flag implies a पढ़ो.
 */
#घोषणा IOMAP_WRITE		(1 << 0) /* writing, must allocate blocks */
#घोषणा IOMAP_ZERO		(1 << 1) /* zeroing operation, may skip holes */
#घोषणा IOMAP_REPORT		(1 << 2) /* report extent status, e.g. FIEMAP */
#घोषणा IOMAP_FAULT		(1 << 3) /* mapping क्रम page fault */
#घोषणा IOMAP_सूचीECT		(1 << 4) /* direct I/O */
#घोषणा IOMAP_NOWAIT		(1 << 5) /* करो not block */
#घोषणा IOMAP_OVERWRITE_ONLY	(1 << 6) /* only pure overग_लिखोs allowed */

काष्ठा iomap_ops अणु
	/*
	 * Return the existing mapping at pos, or reserve space starting at
	 * pos क्रम up to length, as दीर्घ as we can करो it as a single mapping.
	 * The actual length is वापसed in iomap->length.
	 */
	पूर्णांक (*iomap_begin)(काष्ठा inode *inode, loff_t pos, loff_t length,
			अचिन्हित flags, काष्ठा iomap *iomap,
			काष्ठा iomap *srcmap);

	/*
	 * Commit and/or unreserve space previous allocated using iomap_begin.
	 * Written indicates the length of the successful ग_लिखो operation which
	 * needs to be commited, जबतक the rest needs to be unreserved.
	 * Written might be zero अगर no data was written.
	 */
	पूर्णांक (*iomap_end)(काष्ठा inode *inode, loff_t pos, loff_t length,
			sमाप_प्रकार written, अचिन्हित flags, काष्ठा iomap *iomap);
पूर्ण;

/*
 * Main iomap iterator function.
 */
प्रकार loff_t (*iomap_actor_t)(काष्ठा inode *inode, loff_t pos, loff_t len,
		व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap);

loff_t iomap_apply(काष्ठा inode *inode, loff_t pos, loff_t length,
		अचिन्हित flags, स्थिर काष्ठा iomap_ops *ops, व्योम *data,
		iomap_actor_t actor);

sमाप_प्रकार iomap_file_buffered_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from,
		स्थिर काष्ठा iomap_ops *ops);
पूर्णांक iomap_पढ़ोpage(काष्ठा page *page, स्थिर काष्ठा iomap_ops *ops);
व्योम iomap_पढ़ोahead(काष्ठा पढ़ोahead_control *, स्थिर काष्ठा iomap_ops *ops);
पूर्णांक iomap_set_page_dirty(काष्ठा page *page);
पूर्णांक iomap_is_partially_uptodate(काष्ठा page *page, अचिन्हित दीर्घ from,
		अचिन्हित दीर्घ count);
पूर्णांक iomap_releasepage(काष्ठा page *page, gfp_t gfp_mask);
व्योम iomap_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक len);
#अगर_घोषित CONFIG_MIGRATION
पूर्णांक iomap_migrate_page(काष्ठा address_space *mapping, काष्ठा page *newpage,
		काष्ठा page *page, क्रमागत migrate_mode mode);
#अन्यथा
#घोषणा iomap_migrate_page शून्य
#पूर्ण_अगर
पूर्णांक iomap_file_unshare(काष्ठा inode *inode, loff_t pos, loff_t len,
		स्थिर काष्ठा iomap_ops *ops);
पूर्णांक iomap_zero_range(काष्ठा inode *inode, loff_t pos, loff_t len,
		bool *did_zero, स्थिर काष्ठा iomap_ops *ops);
पूर्णांक iomap_truncate_page(काष्ठा inode *inode, loff_t pos, bool *did_zero,
		स्थिर काष्ठा iomap_ops *ops);
vm_fault_t iomap_page_mkग_लिखो(काष्ठा vm_fault *vmf,
			स्थिर काष्ठा iomap_ops *ops);
पूर्णांक iomap_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 len, स्थिर काष्ठा iomap_ops *ops);
loff_t iomap_seek_hole(काष्ठा inode *inode, loff_t offset,
		स्थिर काष्ठा iomap_ops *ops);
loff_t iomap_seek_data(काष्ठा inode *inode, loff_t offset,
		स्थिर काष्ठा iomap_ops *ops);
sector_t iomap_bmap(काष्ठा address_space *mapping, sector_t bno,
		स्थिर काष्ठा iomap_ops *ops);

/*
 * Structure क्रम ग_लिखोback I/O completions.
 */
काष्ठा iomap_ioend अणु
	काष्ठा list_head	io_list;	/* next ioend in chain */
	u16			io_type;
	u16			io_flags;	/* IOMAP_F_* */
	काष्ठा inode		*io_inode;	/* file being written to */
	माप_प्रकार			io_size;	/* size of the extent */
	loff_t			io_offset;	/* offset in the file */
	काष्ठा bio		*io_bio;	/* bio being built */
	काष्ठा bio		io_अंतरभूत_bio;	/* MUST BE LAST! */
पूर्ण;

काष्ठा iomap_ग_लिखोback_ops अणु
	/*
	 * Required, maps the blocks so that ग_लिखोback can be perक्रमmed on
	 * the range starting at offset.
	 */
	पूर्णांक (*map_blocks)(काष्ठा iomap_ग_लिखोpage_ctx *wpc, काष्ठा inode *inode,
				loff_t offset);

	/*
	 * Optional, allows the file प्रणालीs to perक्रमm actions just beक्रमe
	 * submitting the bio and/or override the bio end_io handler क्रम complex
	 * operations like copy on ग_लिखो extent manipulation or unwritten extent
	 * conversions.
	 */
	पूर्णांक (*prepare_ioend)(काष्ठा iomap_ioend *ioend, पूर्णांक status);

	/*
	 * Optional, allows the file प्रणाली to discard state on a page where
	 * we failed to submit any I/O.
	 */
	व्योम (*discard_page)(काष्ठा page *page, loff_t fileoff);
पूर्ण;

काष्ठा iomap_ग_लिखोpage_ctx अणु
	काष्ठा iomap		iomap;
	काष्ठा iomap_ioend	*ioend;
	स्थिर काष्ठा iomap_ग_लिखोback_ops *ops;
पूर्ण;

व्योम iomap_finish_ioends(काष्ठा iomap_ioend *ioend, पूर्णांक error);
व्योम iomap_ioend_try_merge(काष्ठा iomap_ioend *ioend,
		काष्ठा list_head *more_ioends);
व्योम iomap_sort_ioends(काष्ठा list_head *ioend_list);
पूर्णांक iomap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		स्थिर काष्ठा iomap_ग_लिखोback_ops *ops);
पूर्णांक iomap_ग_लिखोpages(काष्ठा address_space *mapping,
		काष्ठा ग_लिखोback_control *wbc, काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		स्थिर काष्ठा iomap_ग_लिखोback_ops *ops);

/*
 * Flags क्रम direct I/O ->end_io:
 */
#घोषणा IOMAP_DIO_UNWRITTEN	(1 << 0)	/* covers unwritten extent(s) */
#घोषणा IOMAP_DIO_COW		(1 << 1)	/* covers COW extent(s) */

काष्ठा iomap_dio_ops अणु
	पूर्णांक (*end_io)(काष्ठा kiocb *iocb, sमाप_प्रकार size, पूर्णांक error,
		      अचिन्हित flags);
	blk_qc_t (*submit_io)(काष्ठा inode *inode, काष्ठा iomap *iomap,
			काष्ठा bio *bio, loff_t file_offset);
पूर्ण;

/*
 * Wait क्रम the I/O to complete in iomap_dio_rw even अगर the kiocb is not
 * synchronous.
 */
#घोषणा IOMAP_DIO_FORCE_WAIT	(1 << 0)

/*
 * Do not allocate blocks or zero partial blocks, but instead fall back to
 * the caller by वापसing -EAGAIN.  Used to optimize direct I/O ग_लिखोs that
 * are not aligned to the file प्रणाली block size.
  */
#घोषणा IOMAP_DIO_OVERWRITE_ONLY	(1 << 1)

sमाप_प्रकार iomap_dio_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops, स्थिर काष्ठा iomap_dio_ops *करोps,
		अचिन्हित पूर्णांक dio_flags);
काष्ठा iomap_dio *__iomap_dio_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops, स्थिर काष्ठा iomap_dio_ops *करोps,
		अचिन्हित पूर्णांक dio_flags);
sमाप_प्रकार iomap_dio_complete(काष्ठा iomap_dio *dio);
पूर्णांक iomap_dio_iopoll(काष्ठा kiocb *kiocb, bool spin);

#अगर_घोषित CONFIG_SWAP
काष्ठा file;
काष्ठा swap_info_काष्ठा;

पूर्णांक iomap_swapfile_activate(काष्ठा swap_info_काष्ठा *sis,
		काष्ठा file *swap_file, sector_t *pagespan,
		स्थिर काष्ठा iomap_ops *ops);
#अन्यथा
# define iomap_swapfile_activate(sis, swapfile, pagespan, ops)	(-EIO)
#पूर्ण_अगर /* CONFIG_SWAP */

#पूर्ण_अगर /* LINUX_IOMAP_H */
