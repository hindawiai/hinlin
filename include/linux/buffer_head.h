<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/buffer_head.h
 *
 * Everything to करो with buffer_heads.
 */

#अगर_अघोषित _LINUX_BUFFER_HEAD_H
#घोषणा _LINUX_BUFFER_HEAD_H

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/linkage.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>

#अगर_घोषित CONFIG_BLOCK

क्रमागत bh_state_bits अणु
	BH_Uptodate,	/* Contains valid data */
	BH_Dirty,	/* Is dirty */
	BH_Lock,	/* Is locked */
	BH_Req,		/* Has been submitted क्रम I/O */

	BH_Mapped,	/* Has a disk mapping */
	BH_New,		/* Disk mapping was newly created by get_block */
	BH_Async_Read,	/* Is under end_buffer_async_पढ़ो I/O */
	BH_Async_Write,	/* Is under end_buffer_async_ग_लिखो I/O */
	BH_Delay,	/* Buffer is not yet allocated on disk */
	BH_Boundary,	/* Block is followed by a discontiguity */
	BH_Write_EIO,	/* I/O error on ग_लिखो */
	BH_Unwritten,	/* Buffer is allocated on disk but not written */
	BH_Quiet,	/* Buffer Error Prinks to be quiet */
	BH_Meta,	/* Buffer contains metadata */
	BH_Prio,	/* Buffer should be submitted with REQ_PRIO */
	BH_Defer_Completion, /* Defer AIO completion to workqueue */

	BH_PrivateStart,/* not a state bit, but the first bit available
			 * क्रम निजी allocation by other entities
			 */
पूर्ण;

#घोषणा MAX_BUF_PER_PAGE (PAGE_SIZE / 512)

काष्ठा page;
काष्ठा buffer_head;
काष्ठा address_space;
प्रकार व्योम (bh_end_io_t)(काष्ठा buffer_head *bh, पूर्णांक uptodate);

/*
 * Historically, a buffer_head was used to map a single block
 * within a page, and of course as the unit of I/O through the
 * fileप्रणाली and block layers.  Nowadays the basic I/O unit
 * is the bio, and buffer_heads are used क्रम extracting block
 * mappings (via a get_block_t call), क्रम tracking state within
 * a page (via a page_mapping) and क्रम wrapping bio submission
 * क्रम backward compatibility reasons (e.g. submit_bh).
 */
काष्ठा buffer_head अणु
	अचिन्हित दीर्घ b_state;		/* buffer state biपंचांगap (see above) */
	काष्ठा buffer_head *b_this_page;/* circular list of page's buffers */
	काष्ठा page *b_page;		/* the page this bh is mapped to */

	sector_t b_blocknr;		/* start block number */
	माप_प्रकार b_size;			/* size of mapping */
	अक्षर *b_data;			/* poपूर्णांकer to data within the page */

	काष्ठा block_device *b_bdev;
	bh_end_io_t *b_end_io;		/* I/O completion */
 	व्योम *b_निजी;		/* reserved क्रम b_end_io */
	काष्ठा list_head b_assoc_buffers; /* associated with another mapping */
	काष्ठा address_space *b_assoc_map;	/* mapping this buffer is
						   associated with */
	atomic_t b_count;		/* users using this buffer_head */
	spinlock_t b_uptodate_lock;	/* Used by the first bh in a page, to
					 * serialise IO completion of other
					 * buffers in the page */
पूर्ण;

/*
 * macro tricks to expand the set_buffer_foo(), clear_buffer_foo()
 * and buffer_foo() functions.
 * To aव्योम reset buffer flags that are alपढ़ोy set, because that causes
 * a costly cache line transition, check the flag first.
 */
#घोषणा BUFFER_FNS(bit, name)						\
अटल __always_अंतरभूत व्योम set_buffer_##name(काष्ठा buffer_head *bh)	\
अणु									\
	अगर (!test_bit(BH_##bit, &(bh)->b_state))			\
		set_bit(BH_##bit, &(bh)->b_state);			\
पूर्ण									\
अटल __always_अंतरभूत व्योम clear_buffer_##name(काष्ठा buffer_head *bh)	\
अणु									\
	clear_bit(BH_##bit, &(bh)->b_state);				\
पूर्ण									\
अटल __always_अंतरभूत पूर्णांक buffer_##name(स्थिर काष्ठा buffer_head *bh)	\
अणु									\
	वापस test_bit(BH_##bit, &(bh)->b_state);			\
पूर्ण

/*
 * test_set_buffer_foo() and test_clear_buffer_foo()
 */
#घोषणा TAS_BUFFER_FNS(bit, name)					\
अटल __always_अंतरभूत पूर्णांक test_set_buffer_##name(काष्ठा buffer_head *bh) \
अणु									\
	वापस test_and_set_bit(BH_##bit, &(bh)->b_state);		\
पूर्ण									\
अटल __always_अंतरभूत पूर्णांक test_clear_buffer_##name(काष्ठा buffer_head *bh) \
अणु									\
	वापस test_and_clear_bit(BH_##bit, &(bh)->b_state);		\
पूर्ण									\

/*
 * Emit the buffer bitops functions.   Note that there are also functions
 * of the क्रमm "mark_buffer_foo()".  These are higher-level functions which
 * करो something in addition to setting a b_state bit.
 */
BUFFER_FNS(Uptodate, uptodate)
BUFFER_FNS(Dirty, dirty)
TAS_BUFFER_FNS(Dirty, dirty)
BUFFER_FNS(Lock, locked)
BUFFER_FNS(Req, req)
TAS_BUFFER_FNS(Req, req)
BUFFER_FNS(Mapped, mapped)
BUFFER_FNS(New, new)
BUFFER_FNS(Async_Read, async_पढ़ो)
BUFFER_FNS(Async_Write, async_ग_लिखो)
BUFFER_FNS(Delay, delay)
BUFFER_FNS(Boundary, boundary)
BUFFER_FNS(Write_EIO, ग_लिखो_io_error)
BUFFER_FNS(Unwritten, unwritten)
BUFFER_FNS(Meta, meta)
BUFFER_FNS(Prio, prio)
BUFFER_FNS(Defer_Completion, defer_completion)

#घोषणा bh_offset(bh)		((अचिन्हित दीर्घ)(bh)->b_data & ~PAGE_MASK)

/* If we *know* page->निजी refers to buffer_heads */
#घोषणा page_buffers(page)					\
	(अणु							\
		BUG_ON(!PagePrivate(page));			\
		((काष्ठा buffer_head *)page_निजी(page));	\
	पूर्ण)
#घोषणा page_has_buffers(page)	PagePrivate(page)

व्योम buffer_check_dirty_ग_लिखोback(काष्ठा page *page,
				     bool *dirty, bool *ग_लिखोback);

/*
 * Declarations
 */

व्योम mark_buffer_dirty(काष्ठा buffer_head *bh);
व्योम mark_buffer_ग_लिखो_io_error(काष्ठा buffer_head *bh);
व्योम touch_buffer(काष्ठा buffer_head *bh);
व्योम set_bh_page(काष्ठा buffer_head *bh,
		काष्ठा page *page, अचिन्हित दीर्घ offset);
पूर्णांक try_to_मुक्त_buffers(काष्ठा page *);
काष्ठा buffer_head *alloc_page_buffers(काष्ठा page *page, अचिन्हित दीर्घ size,
		bool retry);
व्योम create_empty_buffers(काष्ठा page *, अचिन्हित दीर्घ,
			अचिन्हित दीर्घ b_state);
व्योम end_buffer_पढ़ो_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate);
व्योम end_buffer_ग_लिखो_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate);
व्योम end_buffer_async_ग_लिखो(काष्ठा buffer_head *bh, पूर्णांक uptodate);

/* Things to करो with buffers at mapping->निजी_list */
व्योम mark_buffer_dirty_inode(काष्ठा buffer_head *bh, काष्ठा inode *inode);
पूर्णांक inode_has_buffers(काष्ठा inode *);
व्योम invalidate_inode_buffers(काष्ठा inode *);
पूर्णांक हटाओ_inode_buffers(काष्ठा inode *inode);
पूर्णांक sync_mapping_buffers(काष्ठा address_space *mapping);
व्योम clean_bdev_aliases(काष्ठा block_device *bdev, sector_t block,
			sector_t len);
अटल अंतरभूत व्योम clean_bdev_bh_alias(काष्ठा buffer_head *bh)
अणु
	clean_bdev_aliases(bh->b_bdev, bh->b_blocknr, 1);
पूर्ण

व्योम mark_buffer_async_ग_लिखो(काष्ठा buffer_head *bh);
व्योम __रुको_on_buffer(काष्ठा buffer_head *);
रुको_queue_head_t *bh_रुकोq_head(काष्ठा buffer_head *bh);
काष्ठा buffer_head *__find_get_block(काष्ठा block_device *bdev, sector_t block,
			अचिन्हित size);
काष्ठा buffer_head *__getblk_gfp(काष्ठा block_device *bdev, sector_t block,
				  अचिन्हित size, gfp_t gfp);
व्योम __brअन्यथा(काष्ठा buffer_head *);
व्योम __bक्रमget(काष्ठा buffer_head *);
व्योम __bपढ़ोahead(काष्ठा block_device *, sector_t block, अचिन्हित पूर्णांक size);
व्योम __bपढ़ोahead_gfp(काष्ठा block_device *, sector_t block, अचिन्हित पूर्णांक size,
		  gfp_t gfp);
काष्ठा buffer_head *__bपढ़ो_gfp(काष्ठा block_device *,
				sector_t block, अचिन्हित size, gfp_t gfp);
व्योम invalidate_bh_lrus(व्योम);
व्योम invalidate_bh_lrus_cpu(पूर्णांक cpu);
bool has_bh_in_lru(पूर्णांक cpu, व्योम *dummy);
काष्ठा buffer_head *alloc_buffer_head(gfp_t gfp_flags);
व्योम मुक्त_buffer_head(काष्ठा buffer_head * bh);
व्योम unlock_buffer(काष्ठा buffer_head *bh);
व्योम __lock_buffer(काष्ठा buffer_head *bh);
व्योम ll_rw_block(पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा buffer_head * bh[]);
पूर्णांक sync_dirty_buffer(काष्ठा buffer_head *bh);
पूर्णांक __sync_dirty_buffer(काष्ठा buffer_head *bh, पूर्णांक op_flags);
व्योम ग_लिखो_dirty_buffer(काष्ठा buffer_head *bh, पूर्णांक op_flags);
पूर्णांक submit_bh(पूर्णांक, पूर्णांक, काष्ठा buffer_head *);
व्योम ग_लिखो_boundary_block(काष्ठा block_device *bdev,
			sector_t bblock, अचिन्हित blocksize);
पूर्णांक bh_uptodate_or_lock(काष्ठा buffer_head *bh);
पूर्णांक bh_submit_पढ़ो(काष्ठा buffer_head *bh);

बाह्य पूर्णांक buffer_heads_over_limit;

/*
 * Generic address_space_operations implementations क्रम buffer_head-backed
 * address_spaces.
 */
व्योम block_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			  अचिन्हित पूर्णांक length);
पूर्णांक block_ग_लिखो_full_page(काष्ठा page *page, get_block_t *get_block,
				काष्ठा ग_लिखोback_control *wbc);
पूर्णांक __block_ग_लिखो_full_page(काष्ठा inode *inode, काष्ठा page *page,
			get_block_t *get_block, काष्ठा ग_लिखोback_control *wbc,
			bh_end_io_t *handler);
पूर्णांक block_पढ़ो_full_page(काष्ठा page*, get_block_t*);
पूर्णांक block_is_partially_uptodate(काष्ठा page *page, अचिन्हित दीर्घ from,
				अचिन्हित दीर्घ count);
पूर्णांक block_ग_लिखो_begin(काष्ठा address_space *mapping, loff_t pos, अचिन्हित len,
		अचिन्हित flags, काष्ठा page **pagep, get_block_t *get_block);
पूर्णांक __block_ग_लिखो_begin(काष्ठा page *page, loff_t pos, अचिन्हित len,
		get_block_t *get_block);
पूर्णांक block_ग_लिखो_end(काष्ठा file *, काष्ठा address_space *,
				loff_t, अचिन्हित, अचिन्हित,
				काष्ठा page *, व्योम *);
पूर्णांक generic_ग_लिखो_end(काष्ठा file *, काष्ठा address_space *,
				loff_t, अचिन्हित, अचिन्हित,
				काष्ठा page *, व्योम *);
व्योम page_zero_new_buffers(काष्ठा page *page, अचिन्हित from, अचिन्हित to);
व्योम clean_page_buffers(काष्ठा page *page);
पूर्णांक cont_ग_लिखो_begin(काष्ठा file *, काष्ठा address_space *, loff_t,
			अचिन्हित, अचिन्हित, काष्ठा page **, व्योम **,
			get_block_t *, loff_t *);
पूर्णांक generic_cont_expand_simple(काष्ठा inode *inode, loff_t size);
पूर्णांक block_commit_ग_लिखो(काष्ठा page *page, अचिन्हित from, अचिन्हित to);
पूर्णांक block_page_mkग_लिखो(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf,
				get_block_t get_block);
/* Convert त्रुटि_सं to वापस value from ->page_mkग_लिखो() call */
अटल अंतरभूत vm_fault_t block_page_mkग_लिखो_वापस(पूर्णांक err)
अणु
	अगर (err == 0)
		वापस VM_FAULT_LOCKED;
	अगर (err == -EFAULT || err == -EAGAIN)
		वापस VM_FAULT_NOPAGE;
	अगर (err == -ENOMEM)
		वापस VM_FAULT_OOM;
	/* -ENOSPC, -EDQUOT, -EIO ... */
	वापस VM_FAULT_SIGBUS;
पूर्ण
sector_t generic_block_bmap(काष्ठा address_space *, sector_t, get_block_t *);
पूर्णांक block_truncate_page(काष्ठा address_space *, loff_t, get_block_t *);
पूर्णांक nobh_ग_लिखो_begin(काष्ठा address_space *, loff_t, अचिन्हित, अचिन्हित,
				काष्ठा page **, व्योम **, get_block_t*);
पूर्णांक nobh_ग_लिखो_end(काष्ठा file *, काष्ठा address_space *,
				loff_t, अचिन्हित, अचिन्हित,
				काष्ठा page *, व्योम *);
पूर्णांक nobh_truncate_page(काष्ठा address_space *, loff_t, get_block_t *);
पूर्णांक nobh_ग_लिखोpage(काष्ठा page *page, get_block_t *get_block,
                        काष्ठा ग_लिखोback_control *wbc);

व्योम buffer_init(व्योम);

/*
 * अंतरभूत definitions
 */

अटल अंतरभूत व्योम get_bh(काष्ठा buffer_head *bh)
अणु
        atomic_inc(&bh->b_count);
पूर्ण

अटल अंतरभूत व्योम put_bh(काष्ठा buffer_head *bh)
अणु
        smp_mb__beक्रमe_atomic();
        atomic_dec(&bh->b_count);
पूर्ण

अटल अंतरभूत व्योम brअन्यथा(काष्ठा buffer_head *bh)
अणु
	अगर (bh)
		__brअन्यथा(bh);
पूर्ण

अटल अंतरभूत व्योम bक्रमget(काष्ठा buffer_head *bh)
अणु
	अगर (bh)
		__bक्रमget(bh);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
sb_bपढ़ो(काष्ठा super_block *sb, sector_t block)
अणु
	वापस __bपढ़ो_gfp(sb->s_bdev, block, sb->s_blocksize, __GFP_MOVABLE);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
sb_bपढ़ो_unmovable(काष्ठा super_block *sb, sector_t block)
अणु
	वापस __bपढ़ो_gfp(sb->s_bdev, block, sb->s_blocksize, 0);
पूर्ण

अटल अंतरभूत व्योम
sb_bपढ़ोahead(काष्ठा super_block *sb, sector_t block)
अणु
	__bपढ़ोahead(sb->s_bdev, block, sb->s_blocksize);
पूर्ण

अटल अंतरभूत व्योम
sb_bपढ़ोahead_unmovable(काष्ठा super_block *sb, sector_t block)
अणु
	__bपढ़ोahead_gfp(sb->s_bdev, block, sb->s_blocksize, 0);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
sb_getblk(काष्ठा super_block *sb, sector_t block)
अणु
	वापस __getblk_gfp(sb->s_bdev, block, sb->s_blocksize, __GFP_MOVABLE);
पूर्ण


अटल अंतरभूत काष्ठा buffer_head *
sb_getblk_gfp(काष्ठा super_block *sb, sector_t block, gfp_t gfp)
अणु
	वापस __getblk_gfp(sb->s_bdev, block, sb->s_blocksize, gfp);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *
sb_find_get_block(काष्ठा super_block *sb, sector_t block)
अणु
	वापस __find_get_block(sb->s_bdev, block, sb->s_blocksize);
पूर्ण

अटल अंतरभूत व्योम
map_bh(काष्ठा buffer_head *bh, काष्ठा super_block *sb, sector_t block)
अणु
	set_buffer_mapped(bh);
	bh->b_bdev = sb->s_bdev;
	bh->b_blocknr = block;
	bh->b_size = sb->s_blocksize;
पूर्ण

अटल अंतरभूत व्योम रुको_on_buffer(काष्ठा buffer_head *bh)
अणु
	might_sleep();
	अगर (buffer_locked(bh))
		__रुको_on_buffer(bh);
पूर्ण

अटल अंतरभूत पूर्णांक trylock_buffer(काष्ठा buffer_head *bh)
अणु
	वापस likely(!test_and_set_bit_lock(BH_Lock, &bh->b_state));
पूर्ण

अटल अंतरभूत व्योम lock_buffer(काष्ठा buffer_head *bh)
अणु
	might_sleep();
	अगर (!trylock_buffer(bh))
		__lock_buffer(bh);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *getblk_unmovable(काष्ठा block_device *bdev,
						   sector_t block,
						   अचिन्हित size)
अणु
	वापस __getblk_gfp(bdev, block, size, 0);
पूर्ण

अटल अंतरभूत काष्ठा buffer_head *__getblk(काष्ठा block_device *bdev,
					   sector_t block,
					   अचिन्हित size)
अणु
	वापस __getblk_gfp(bdev, block, size, __GFP_MOVABLE);
पूर्ण

/**
 *  __bपढ़ो() - पढ़ोs a specअगरied block and वापसs the bh
 *  @bdev: the block_device to पढ़ो from
 *  @block: number of block
 *  @size: size (in bytes) to पढ़ो
 *
 *  Reads a specअगरied block, and वापसs buffer head that contains it.
 *  The page cache is allocated from movable area so that it can be migrated.
 *  It वापसs शून्य अगर the block was unपढ़ोable.
 */
अटल अंतरभूत काष्ठा buffer_head *
__bपढ़ो(काष्ठा block_device *bdev, sector_t block, अचिन्हित size)
अणु
	वापस __bपढ़ो_gfp(bdev, block, size, __GFP_MOVABLE);
पूर्ण

बाह्य पूर्णांक __set_page_dirty_buffers(काष्ठा page *page);

#अन्यथा /* CONFIG_BLOCK */

अटल अंतरभूत व्योम buffer_init(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक try_to_मुक्त_buffers(काष्ठा page *page) अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक inode_has_buffers(काष्ठा inode *inode) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम invalidate_inode_buffers(काष्ठा inode *inode) अणुपूर्ण
अटल अंतरभूत पूर्णांक हटाओ_inode_buffers(काष्ठा inode *inode) अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक sync_mapping_buffers(काष्ठा address_space *mapping) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम invalidate_bh_lrus_cpu(पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत bool has_bh_in_lru(पूर्णांक cpu, व्योम *dummy) अणु वापस 0; पूर्ण
#घोषणा buffer_heads_over_limit 0

#पूर्ण_अगर /* CONFIG_BLOCK */
#पूर्ण_अगर /* _LINUX_BUFFER_HEAD_H */
