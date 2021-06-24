<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2005
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mempool.h>
#समावेश <linux/seq_file.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_txnmgr.h"
#समावेश "jfs_debug.h"

#अगर_घोषित CONFIG_JFS_STATISTICS
अटल काष्ठा अणु
	uपूर्णांक	pagealloc;	/* # of page allocations */
	uपूर्णांक	pageमुक्त;	/* # of page मुक्तs */
	uपूर्णांक	lockरुको;	/* # of sleeping lock_metapage() calls */
पूर्ण mpStat;
#पूर्ण_अगर

#घोषणा metapage_locked(mp) test_bit(META_locked, &(mp)->flag)
#घोषणा trylock_metapage(mp) test_and_set_bit_lock(META_locked, &(mp)->flag)

अटल अंतरभूत व्योम unlock_metapage(काष्ठा metapage *mp)
अणु
	clear_bit_unlock(META_locked, &mp->flag);
	wake_up(&mp->रुको);
पूर्ण

अटल अंतरभूत व्योम __lock_metapage(काष्ठा metapage *mp)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	INCREMENT(mpStat.lockरुको);
	add_रुको_queue_exclusive(&mp->रुको, &रुको);
	करो अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (metapage_locked(mp)) अणु
			unlock_page(mp->page);
			io_schedule();
			lock_page(mp->page);
		पूर्ण
	पूर्ण जबतक (trylock_metapage(mp));
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&mp->रुको, &रुको);
पूर्ण

/*
 * Must have mp->page locked
 */
अटल अंतरभूत व्योम lock_metapage(काष्ठा metapage *mp)
अणु
	अगर (trylock_metapage(mp))
		__lock_metapage(mp);
पूर्ण

#घोषणा METAPOOL_MIN_PAGES 32
अटल काष्ठा kmem_cache *metapage_cache;
अटल mempool_t *metapage_mempool;

#घोषणा MPS_PER_PAGE (PAGE_SIZE >> L2PSIZE)

#अगर MPS_PER_PAGE > 1

काष्ठा meta_anchor अणु
	पूर्णांक mp_count;
	atomic_t io_count;
	काष्ठा metapage *mp[MPS_PER_PAGE];
पूर्ण;
#घोषणा mp_anchor(page) ((काष्ठा meta_anchor *)page_निजी(page))

अटल अंतरभूत काष्ठा metapage *page_to_mp(काष्ठा page *page, पूर्णांक offset)
अणु
	अगर (!PagePrivate(page))
		वापस शून्य;
	वापस mp_anchor(page)->mp[offset >> L2PSIZE];
पूर्ण

अटल अंतरभूत पूर्णांक insert_metapage(काष्ठा page *page, काष्ठा metapage *mp)
अणु
	काष्ठा meta_anchor *a;
	पूर्णांक index;
	पूर्णांक l2mp_blocks;	/* log2 blocks per metapage */

	अगर (PagePrivate(page))
		a = mp_anchor(page);
	अन्यथा अणु
		a = kzalloc(माप(काष्ठा meta_anchor), GFP_NOFS);
		अगर (!a)
			वापस -ENOMEM;
		set_page_निजी(page, (अचिन्हित दीर्घ)a);
		SetPagePrivate(page);
		kmap(page);
	पूर्ण

	अगर (mp) अणु
		l2mp_blocks = L2PSIZE - page->mapping->host->i_blkbits;
		index = (mp->index >> l2mp_blocks) & (MPS_PER_PAGE - 1);
		a->mp_count++;
		a->mp[index] = mp;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम हटाओ_metapage(काष्ठा page *page, काष्ठा metapage *mp)
अणु
	काष्ठा meta_anchor *a = mp_anchor(page);
	पूर्णांक l2mp_blocks = L2PSIZE - page->mapping->host->i_blkbits;
	पूर्णांक index;

	index = (mp->index >> l2mp_blocks) & (MPS_PER_PAGE - 1);

	BUG_ON(a->mp[index] != mp);

	a->mp[index] = शून्य;
	अगर (--a->mp_count == 0) अणु
		kमुक्त(a);
		set_page_निजी(page, 0);
		ClearPagePrivate(page);
		kunmap(page);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम inc_io(काष्ठा page *page)
अणु
	atomic_inc(&mp_anchor(page)->io_count);
पूर्ण

अटल अंतरभूत व्योम dec_io(काष्ठा page *page, व्योम (*handler) (काष्ठा page *))
अणु
	अगर (atomic_dec_and_test(&mp_anchor(page)->io_count))
		handler(page);
पूर्ण

#अन्यथा
अटल अंतरभूत काष्ठा metapage *page_to_mp(काष्ठा page *page, पूर्णांक offset)
अणु
	वापस PagePrivate(page) ? (काष्ठा metapage *)page_निजी(page) : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक insert_metapage(काष्ठा page *page, काष्ठा metapage *mp)
अणु
	अगर (mp) अणु
		set_page_निजी(page, (अचिन्हित दीर्घ)mp);
		SetPagePrivate(page);
		kmap(page);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम हटाओ_metapage(काष्ठा page *page, काष्ठा metapage *mp)
अणु
	set_page_निजी(page, 0);
	ClearPagePrivate(page);
	kunmap(page);
पूर्ण

#घोषणा inc_io(page) करो अणुपूर्ण जबतक(0)
#घोषणा dec_io(page, handler) handler(page)

#पूर्ण_अगर

अटल अंतरभूत काष्ठा metapage *alloc_metapage(gfp_t gfp_mask)
अणु
	काष्ठा metapage *mp = mempool_alloc(metapage_mempool, gfp_mask);

	अगर (mp) अणु
		mp->lid = 0;
		mp->lsn = 0;
		mp->data = शून्य;
		mp->clsn = 0;
		mp->log = शून्य;
		init_रुकोqueue_head(&mp->रुको);
	पूर्ण
	वापस mp;
पूर्ण

अटल अंतरभूत व्योम मुक्त_metapage(काष्ठा metapage *mp)
अणु
	mempool_मुक्त(mp, metapage_mempool);
पूर्ण

पूर्णांक __init metapage_init(व्योम)
अणु
	/*
	 * Allocate the metapage काष्ठाures
	 */
	metapage_cache = kmem_cache_create("jfs_mp", माप(काष्ठा metapage),
					   0, 0, शून्य);
	अगर (metapage_cache == शून्य)
		वापस -ENOMEM;

	metapage_mempool = mempool_create_slab_pool(METAPOOL_MIN_PAGES,
						    metapage_cache);

	अगर (metapage_mempool == शून्य) अणु
		kmem_cache_destroy(metapage_cache);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम metapage_निकास(व्योम)
अणु
	mempool_destroy(metapage_mempool);
	kmem_cache_destroy(metapage_cache);
पूर्ण

अटल अंतरभूत व्योम drop_metapage(काष्ठा page *page, काष्ठा metapage *mp)
अणु
	अगर (mp->count || mp->nohomeok || test_bit(META_dirty, &mp->flag) ||
	    test_bit(META_io, &mp->flag))
		वापस;
	हटाओ_metapage(page, mp);
	INCREMENT(mpStat.pageमुक्त);
	मुक्त_metapage(mp);
पूर्ण

/*
 * Metapage address space operations
 */

अटल sector_t metapage_get_blocks(काष्ठा inode *inode, sector_t lblock,
				    पूर्णांक *len)
अणु
	पूर्णांक rc = 0;
	पूर्णांक xflag;
	s64 xaddr;
	sector_t file_blocks = (inode->i_size + inode->i_sb->s_blocksize - 1) >>
			       inode->i_blkbits;

	अगर (lblock >= file_blocks)
		वापस 0;
	अगर (lblock + *len > file_blocks)
		*len = file_blocks - lblock;

	अगर (inode->i_ino) अणु
		rc = xtLookup(inode, (s64)lblock, *len, &xflag, &xaddr, len, 0);
		अगर ((rc == 0) && *len)
			lblock = (sector_t)xaddr;
		अन्यथा
			lblock = 0;
	पूर्ण /* अन्यथा no mapping */

	वापस lblock;
पूर्ण

अटल व्योम last_पढ़ो_complete(काष्ठा page *page)
अणु
	अगर (!PageError(page))
		SetPageUptodate(page);
	unlock_page(page);
पूर्ण

अटल व्योम metapage_पढ़ो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		prपूर्णांकk(KERN_ERR "metapage_read_end_io: I/O error\n");
		SetPageError(page);
	पूर्ण

	dec_io(page, last_पढ़ो_complete);
	bio_put(bio);
पूर्ण

अटल व्योम हटाओ_from_logsync(काष्ठा metapage *mp)
अणु
	काष्ठा jfs_log *log = mp->log;
	अचिन्हित दीर्घ flags;
/*
 * This can race.  Recheck that log hasn't been set to null, and after
 * acquiring logsync lock, recheck lsn
 */
	अगर (!log)
		वापस;

	LOGSYNC_LOCK(log, flags);
	अगर (mp->lsn) अणु
		mp->log = शून्य;
		mp->lsn = 0;
		mp->clsn = 0;
		log->count--;
		list_del(&mp->synclist);
	पूर्ण
	LOGSYNC_UNLOCK(log, flags);
पूर्ण

अटल व्योम last_ग_लिखो_complete(काष्ठा page *page)
अणु
	काष्ठा metapage *mp;
	अचिन्हित पूर्णांक offset;

	क्रम (offset = 0; offset < PAGE_SIZE; offset += PSIZE) अणु
		mp = page_to_mp(page, offset);
		अगर (mp && test_bit(META_io, &mp->flag)) अणु
			अगर (mp->lsn)
				हटाओ_from_logsync(mp);
			clear_bit(META_io, &mp->flag);
		पूर्ण
		/*
		 * I'd like to call drop_metapage here, but I don't think it's
		 * safe unless I have the page locked
		 */
	पूर्ण
	end_page_ग_लिखोback(page);
पूर्ण

अटल व्योम metapage_ग_लिखो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio->bi_निजी;

	BUG_ON(!PagePrivate(page));

	अगर (bio->bi_status) अणु
		prपूर्णांकk(KERN_ERR "metapage_write_end_io: I/O error\n");
		SetPageError(page);
	पूर्ण
	dec_io(page, last_ग_लिखो_complete);
	bio_put(bio);
पूर्ण

अटल पूर्णांक metapage_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा bio *bio = शून्य;
	पूर्णांक block_offset;	/* block offset of mp within page */
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक blocks_per_mp = JFS_SBI(inode->i_sb)->nbperpage;
	पूर्णांक len;
	पूर्णांक xlen;
	काष्ठा metapage *mp;
	पूर्णांक redirty = 0;
	sector_t lblock;
	पूर्णांक nr_underway = 0;
	sector_t pblock;
	sector_t next_block = 0;
	sector_t page_start;
	अचिन्हित दीर्घ bio_bytes = 0;
	अचिन्हित दीर्घ bio_offset = 0;
	पूर्णांक offset;
	पूर्णांक bad_blocks = 0;

	page_start = (sector_t)page->index <<
		     (PAGE_SHIFT - inode->i_blkbits);
	BUG_ON(!PageLocked(page));
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);

	क्रम (offset = 0; offset < PAGE_SIZE; offset += PSIZE) अणु
		mp = page_to_mp(page, offset);

		अगर (!mp || !test_bit(META_dirty, &mp->flag))
			जारी;

		अगर (mp->nohomeok && !test_bit(META_क्रमceग_लिखो, &mp->flag)) अणु
			redirty = 1;
			/*
			 * Make sure this page isn't blocked indefinitely.
			 * If the journal isn't undergoing I/O, push it
			 */
			अगर (mp->log && !(mp->log->cflag & logGC_PAGEOUT))
				jfs_flush_journal(mp->log, 0);
			जारी;
		पूर्ण

		clear_bit(META_dirty, &mp->flag);
		set_bit(META_io, &mp->flag);
		block_offset = offset >> inode->i_blkbits;
		lblock = page_start + block_offset;
		अगर (bio) अणु
			अगर (xlen && lblock == next_block) अणु
				/* Contiguous, in memory & on disk */
				len = min(xlen, blocks_per_mp);
				xlen -= len;
				bio_bytes += len << inode->i_blkbits;
				जारी;
			पूर्ण
			/* Not contiguous */
			अगर (bio_add_page(bio, page, bio_bytes, bio_offset) <
			    bio_bytes)
				जाओ add_failed;
			/*
			 * Increment counter beक्रमe submitting i/o to keep
			 * count from hitting zero beक्रमe we're through
			 */
			inc_io(page);
			अगर (!bio->bi_iter.bi_size)
				जाओ dump_bio;
			submit_bio(bio);
			nr_underway++;
			bio = शून्य;
		पूर्ण अन्यथा
			inc_io(page);
		xlen = (PAGE_SIZE - offset) >> inode->i_blkbits;
		pblock = metapage_get_blocks(inode, lblock, &xlen);
		अगर (!pblock) अणु
			prपूर्णांकk(KERN_ERR "JFS: metapage_get_blocks failed\n");
			/*
			 * We alपढ़ोy called inc_io(), but can't cancel it
			 * with dec_io() until we're करोne with the page
			 */
			bad_blocks++;
			जारी;
		पूर्ण
		len = min(xlen, (पूर्णांक)JFS_SBI(inode->i_sb)->nbperpage);

		bio = bio_alloc(GFP_NOFS, 1);
		bio_set_dev(bio, inode->i_sb->s_bdev);
		bio->bi_iter.bi_sector = pblock << (inode->i_blkbits - 9);
		bio->bi_end_io = metapage_ग_लिखो_end_io;
		bio->bi_निजी = page;
		bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

		/* Don't call bio_add_page yet, we may add to this vec */
		bio_offset = offset;
		bio_bytes = len << inode->i_blkbits;

		xlen -= len;
		next_block = lblock + len;
	पूर्ण
	अगर (bio) अणु
		अगर (bio_add_page(bio, page, bio_bytes, bio_offset) < bio_bytes)
				जाओ add_failed;
		अगर (!bio->bi_iter.bi_size)
			जाओ dump_bio;

		submit_bio(bio);
		nr_underway++;
	पूर्ण
	अगर (redirty)
		redirty_page_क्रम_ग_लिखोpage(wbc, page);

	unlock_page(page);

	अगर (bad_blocks)
		जाओ err_out;

	अगर (nr_underway == 0)
		end_page_ग_लिखोback(page);

	वापस 0;
add_failed:
	/* We should never reach here, since we're only adding one vec */
	prपूर्णांकk(KERN_ERR "JFS: bio_add_page failed unexpectedly\n");
	जाओ skip;
dump_bio:
	prपूर्णांक_hex_dump(KERN_ERR, "JFS: dump of bio: ", DUMP_PREFIX_ADDRESS, 16,
		       4, bio, माप(*bio), 0);
skip:
	bio_put(bio);
	unlock_page(page);
	dec_io(page, last_ग_लिखो_complete);
err_out:
	जबतक (bad_blocks--)
		dec_io(page, last_ग_लिखो_complete);
	वापस -EIO;
पूर्ण

अटल पूर्णांक metapage_पढ़ोpage(काष्ठा file *fp, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा bio *bio = शून्य;
	पूर्णांक block_offset;
	पूर्णांक blocks_per_page = i_blocks_per_page(inode, page);
	sector_t page_start;	/* address of page in fs blocks */
	sector_t pblock;
	पूर्णांक xlen;
	अचिन्हित पूर्णांक len;
	पूर्णांक offset;

	BUG_ON(!PageLocked(page));
	page_start = (sector_t)page->index <<
		     (PAGE_SHIFT - inode->i_blkbits);

	block_offset = 0;
	जबतक (block_offset < blocks_per_page) अणु
		xlen = blocks_per_page - block_offset;
		pblock = metapage_get_blocks(inode, page_start + block_offset,
					     &xlen);
		अगर (pblock) अणु
			अगर (!PagePrivate(page))
				insert_metapage(page, शून्य);
			inc_io(page);
			अगर (bio)
				submit_bio(bio);

			bio = bio_alloc(GFP_NOFS, 1);
			bio_set_dev(bio, inode->i_sb->s_bdev);
			bio->bi_iter.bi_sector =
				pblock << (inode->i_blkbits - 9);
			bio->bi_end_io = metapage_पढ़ो_end_io;
			bio->bi_निजी = page;
			bio_set_op_attrs(bio, REQ_OP_READ, 0);
			len = xlen << inode->i_blkbits;
			offset = block_offset << inode->i_blkbits;
			अगर (bio_add_page(bio, page, len, offset) < len)
				जाओ add_failed;
			block_offset += xlen;
		पूर्ण अन्यथा
			block_offset++;
	पूर्ण
	अगर (bio)
		submit_bio(bio);
	अन्यथा
		unlock_page(page);

	वापस 0;

add_failed:
	prपूर्णांकk(KERN_ERR "JFS: bio_add_page failed unexpectedly\n");
	bio_put(bio);
	dec_io(page, last_पढ़ो_complete);
	वापस -EIO;
पूर्ण

अटल पूर्णांक metapage_releasepage(काष्ठा page *page, gfp_t gfp_mask)
अणु
	काष्ठा metapage *mp;
	पूर्णांक ret = 1;
	पूर्णांक offset;

	क्रम (offset = 0; offset < PAGE_SIZE; offset += PSIZE) अणु
		mp = page_to_mp(page, offset);

		अगर (!mp)
			जारी;

		jfs_info("metapage_releasepage: mp = 0x%p", mp);
		अगर (mp->count || mp->nohomeok ||
		    test_bit(META_dirty, &mp->flag)) अणु
			jfs_info("count = %ld, nohomeok = %d", mp->count,
				 mp->nohomeok);
			ret = 0;
			जारी;
		पूर्ण
		अगर (mp->lsn)
			हटाओ_from_logsync(mp);
		हटाओ_metapage(page, mp);
		INCREMENT(mpStat.pageमुक्त);
		मुक्त_metapage(mp);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम metapage_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				    अचिन्हित पूर्णांक length)
अणु
	BUG_ON(offset || length < PAGE_SIZE);

	BUG_ON(PageWriteback(page));

	metapage_releasepage(page, 0);
पूर्ण

स्थिर काष्ठा address_space_operations jfs_metapage_aops = अणु
	.पढ़ोpage	= metapage_पढ़ोpage,
	.ग_लिखोpage	= metapage_ग_लिखोpage,
	.releasepage	= metapage_releasepage,
	.invalidatepage	= metapage_invalidatepage,
	.set_page_dirty	= __set_page_dirty_nobuffers,
पूर्ण;

काष्ठा metapage *__get_metapage(काष्ठा inode *inode, अचिन्हित दीर्घ lblock,
				अचिन्हित पूर्णांक size, पूर्णांक असलolute,
				अचिन्हित दीर्घ new)
अणु
	पूर्णांक l2BlocksPerPage;
	पूर्णांक l2bsize;
	काष्ठा address_space *mapping;
	काष्ठा metapage *mp = शून्य;
	काष्ठा page *page;
	अचिन्हित दीर्घ page_index;
	अचिन्हित दीर्घ page_offset;

	jfs_info("__get_metapage: ino = %ld, lblock = 0x%lx, abs=%d",
		 inode->i_ino, lblock, असलolute);

	l2bsize = inode->i_blkbits;
	l2BlocksPerPage = PAGE_SHIFT - l2bsize;
	page_index = lblock >> l2BlocksPerPage;
	page_offset = (lblock - (page_index << l2BlocksPerPage)) << l2bsize;
	अगर ((page_offset + size) > PAGE_SIZE) अणु
		jfs_err("MetaData crosses page boundary!!");
		jfs_err("lblock = %lx, size  = %d", lblock, size);
		dump_stack();
		वापस शून्य;
	पूर्ण
	अगर (असलolute)
		mapping = JFS_SBI(inode->i_sb)->direct_inode->i_mapping;
	अन्यथा अणु
		/*
		 * If an nfs client tries to पढ़ो an inode that is larger
		 * than any existing inodes, we may try to पढ़ो past the
		 * end of the inode map
		 */
		अगर ((lblock << inode->i_blkbits) >= inode->i_size)
			वापस शून्य;
		mapping = inode->i_mapping;
	पूर्ण

	अगर (new && (PSIZE == PAGE_SIZE)) अणु
		page = grab_cache_page(mapping, page_index);
		अगर (!page) अणु
			jfs_err("grab_cache_page failed!");
			वापस शून्य;
		पूर्ण
		SetPageUptodate(page);
	पूर्ण अन्यथा अणु
		page = पढ़ो_mapping_page(mapping, page_index, शून्य);
		अगर (IS_ERR(page) || !PageUptodate(page)) अणु
			jfs_err("read_mapping_page failed!");
			वापस शून्य;
		पूर्ण
		lock_page(page);
	पूर्ण

	mp = page_to_mp(page, page_offset);
	अगर (mp) अणु
		अगर (mp->logical_size != size) अणु
			jfs_error(inode->i_sb,
				  "get_mp->logical_size != size\n");
			jfs_err("logical_size = %d, size = %d",
				mp->logical_size, size);
			dump_stack();
			जाओ unlock;
		पूर्ण
		mp->count++;
		lock_metapage(mp);
		अगर (test_bit(META_discard, &mp->flag)) अणु
			अगर (!new) अणु
				jfs_error(inode->i_sb,
					  "using a discarded metapage\n");
				discard_metapage(mp);
				जाओ unlock;
			पूर्ण
			clear_bit(META_discard, &mp->flag);
		पूर्ण
	पूर्ण अन्यथा अणु
		INCREMENT(mpStat.pagealloc);
		mp = alloc_metapage(GFP_NOFS);
		अगर (!mp)
			जाओ unlock;
		mp->page = page;
		mp->sb = inode->i_sb;
		mp->flag = 0;
		mp->xflag = COMMIT_PAGE;
		mp->count = 1;
		mp->nohomeok = 0;
		mp->logical_size = size;
		mp->data = page_address(page) + page_offset;
		mp->index = lblock;
		अगर (unlikely(insert_metapage(page, mp))) अणु
			मुक्त_metapage(mp);
			जाओ unlock;
		पूर्ण
		lock_metapage(mp);
	पूर्ण

	अगर (new) अणु
		jfs_info("zeroing mp = 0x%p", mp);
		स_रखो(mp->data, 0, PSIZE);
	पूर्ण

	unlock_page(page);
	jfs_info("__get_metapage: returning = 0x%p data = 0x%p", mp, mp->data);
	वापस mp;

unlock:
	unlock_page(page);
	वापस शून्य;
पूर्ण

व्योम grab_metapage(काष्ठा metapage * mp)
अणु
	jfs_info("grab_metapage: mp = 0x%p", mp);
	get_page(mp->page);
	lock_page(mp->page);
	mp->count++;
	lock_metapage(mp);
	unlock_page(mp->page);
पूर्ण

व्योम क्रमce_metapage(काष्ठा metapage *mp)
अणु
	काष्ठा page *page = mp->page;
	jfs_info("force_metapage: mp = 0x%p", mp);
	set_bit(META_क्रमceग_लिखो, &mp->flag);
	clear_bit(META_sync, &mp->flag);
	get_page(page);
	lock_page(page);
	set_page_dirty(page);
	अगर (ग_लिखो_one_page(page))
		jfs_error(mp->sb, "write_one_page() failed\n");
	clear_bit(META_क्रमceग_लिखो, &mp->flag);
	put_page(page);
पूर्ण

व्योम hold_metapage(काष्ठा metapage *mp)
अणु
	lock_page(mp->page);
पूर्ण

व्योम put_metapage(काष्ठा metapage *mp)
अणु
	अगर (mp->count || mp->nohomeok) अणु
		/* Someone अन्यथा will release this */
		unlock_page(mp->page);
		वापस;
	पूर्ण
	get_page(mp->page);
	mp->count++;
	lock_metapage(mp);
	unlock_page(mp->page);
	release_metapage(mp);
पूर्ण

व्योम release_metapage(काष्ठा metapage * mp)
अणु
	काष्ठा page *page = mp->page;
	jfs_info("release_metapage: mp = 0x%p, flag = 0x%lx", mp, mp->flag);

	BUG_ON(!page);

	lock_page(page);
	unlock_metapage(mp);

	निश्चित(mp->count);
	अगर (--mp->count || mp->nohomeok) अणु
		unlock_page(page);
		put_page(page);
		वापस;
	पूर्ण

	अगर (test_bit(META_dirty, &mp->flag)) अणु
		set_page_dirty(page);
		अगर (test_bit(META_sync, &mp->flag)) अणु
			clear_bit(META_sync, &mp->flag);
			अगर (ग_लिखो_one_page(page))
				jfs_error(mp->sb, "write_one_page() failed\n");
			lock_page(page); /* ग_लिखो_one_page unlocks the page */
		पूर्ण
	पूर्ण अन्यथा अगर (mp->lsn)	/* discard_metapage करोesn't हटाओ it */
		हटाओ_from_logsync(mp);

	/* Try to keep metapages from using up too much memory */
	drop_metapage(page, mp);

	unlock_page(page);
	put_page(page);
पूर्ण

व्योम __invalidate_metapages(काष्ठा inode *ip, s64 addr, पूर्णांक len)
अणु
	sector_t lblock;
	पूर्णांक l2BlocksPerPage = PAGE_SHIFT - ip->i_blkbits;
	पूर्णांक BlocksPerPage = 1 << l2BlocksPerPage;
	/* All callers are पूर्णांकerested in block device's mapping */
	काष्ठा address_space *mapping =
		JFS_SBI(ip->i_sb)->direct_inode->i_mapping;
	काष्ठा metapage *mp;
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset;

	/*
	 * Mark metapages to discard.  They will eventually be
	 * released, but should not be written.
	 */
	क्रम (lblock = addr & ~(BlocksPerPage - 1); lblock < addr + len;
	     lblock += BlocksPerPage) अणु
		page = find_lock_page(mapping, lblock >> l2BlocksPerPage);
		अगर (!page)
			जारी;
		क्रम (offset = 0; offset < PAGE_SIZE; offset += PSIZE) अणु
			mp = page_to_mp(page, offset);
			अगर (!mp)
				जारी;
			अगर (mp->index < addr)
				जारी;
			अगर (mp->index >= addr + len)
				अवरोध;

			clear_bit(META_dirty, &mp->flag);
			set_bit(META_discard, &mp->flag);
			अगर (mp->lsn)
				हटाओ_from_logsync(mp);
		पूर्ण
		unlock_page(page);
		put_page(page);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_JFS_STATISTICS
पूर्णांक jfs_mpstat_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m,
		       "JFS Metapage statistics\n"
		       "=======================\n"
		       "page allocations = %d\n"
		       "page frees = %d\n"
		       "lock waits = %d\n",
		       mpStat.pagealloc,
		       mpStat.pageमुक्त,
		       mpStat.lockरुको);
	वापस 0;
पूर्ण
#पूर्ण_अगर
