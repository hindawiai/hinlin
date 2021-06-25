<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *   
 *   Copyright 2001 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * linux/fs/isofs/compress.c
 *
 * Transparent decompression of files on an iso9660 fileप्रणाली
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/zlib.h>

#समावेश "isofs.h"
#समावेश "zisofs.h"

/* This should probably be global. */
अटल अक्षर zisofs_sink_page[PAGE_SIZE];

/*
 * This contains the zlib memory allocation and the mutex क्रम the
 * allocation; this aव्योमs failures at block-decompression समय.
 */
अटल व्योम *zisofs_zlib_workspace;
अटल DEFINE_MUTEX(zisofs_zlib_lock);

/*
 * Read data of @inode from @block_start to @block_end and uncompress
 * to one zisofs block. Store the data in the @pages array with @pcount
 * entries. Start storing at offset @poffset of the first page.
 */
अटल loff_t zisofs_uncompress_block(काष्ठा inode *inode, loff_t block_start,
				      loff_t block_end, पूर्णांक pcount,
				      काष्ठा page **pages, अचिन्हित poffset,
				      पूर्णांक *errp)
अणु
	अचिन्हित पूर्णांक zisofs_block_shअगरt = ISOFS_I(inode)->i_क्रमmat_parm[1];
	अचिन्हित पूर्णांक bufsize = ISOFS_BUFFER_SIZE(inode);
	अचिन्हित पूर्णांक bufshअगरt = ISOFS_BUFFER_BITS(inode);
	अचिन्हित पूर्णांक bufmask = bufsize - 1;
	पूर्णांक i, block_size = block_end - block_start;
	z_stream stream = अणु .total_out = 0,
			    .avail_in = 0,
			    .avail_out = 0, पूर्ण;
	पूर्णांक zerr;
	पूर्णांक needblocks = (block_size + (block_start & bufmask) + bufmask)
				>> bufshअगरt;
	पूर्णांक haveblocks;
	blkcnt_t blocknum;
	काष्ठा buffer_head **bhs;
	पूर्णांक curbh, curpage;

	अगर (block_size > deflateBound(1UL << zisofs_block_shअगरt)) अणु
		*errp = -EIO;
		वापस 0;
	पूर्ण
	/* Empty block? */
	अगर (block_size == 0) अणु
		क्रम ( i = 0 ; i < pcount ; i++ ) अणु
			अगर (!pages[i])
				जारी;
			स_रखो(page_address(pages[i]), 0, PAGE_SIZE);
			flush_dcache_page(pages[i]);
			SetPageUptodate(pages[i]);
		पूर्ण
		वापस ((loff_t)pcount) << PAGE_SHIFT;
	पूर्ण

	/* Because zlib is not thपढ़ो-safe, करो all the I/O at the top. */
	blocknum = block_start >> bufshअगरt;
	bhs = kसुस्मृति(needblocks + 1, माप(*bhs), GFP_KERNEL);
	अगर (!bhs) अणु
		*errp = -ENOMEM;
		वापस 0;
	पूर्ण
	haveblocks = isofs_get_blocks(inode, blocknum, bhs, needblocks);
	ll_rw_block(REQ_OP_READ, 0, haveblocks, bhs);

	curbh = 0;
	curpage = 0;
	/*
	 * First block is special since it may be fractional.  We also रुको क्रम
	 * it beक्रमe grabbing the zlib mutex; odds are that the subsequent
	 * blocks are going to come in in लघु order so we करोn't hold the zlib
	 * mutex दीर्घer than necessary.
	 */

	अगर (!bhs[0])
		जाओ b_eio;

	रुको_on_buffer(bhs[0]);
	अगर (!buffer_uptodate(bhs[0])) अणु
		*errp = -EIO;
		जाओ b_eio;
	पूर्ण

	stream.workspace = zisofs_zlib_workspace;
	mutex_lock(&zisofs_zlib_lock);
		
	zerr = zlib_inflateInit(&stream);
	अगर (zerr != Z_OK) अणु
		अगर (zerr == Z_MEM_ERROR)
			*errp = -ENOMEM;
		अन्यथा
			*errp = -EIO;
		prपूर्णांकk(KERN_DEBUG "zisofs: zisofs_inflateInit returned %d\n",
			       zerr);
		जाओ z_eio;
	पूर्ण

	जबतक (curpage < pcount && curbh < haveblocks &&
	       zerr != Z_STREAM_END) अणु
		अगर (!stream.avail_out) अणु
			अगर (pages[curpage]) अणु
				stream.next_out = page_address(pages[curpage])
						+ poffset;
				stream.avail_out = PAGE_SIZE - poffset;
				poffset = 0;
			पूर्ण अन्यथा अणु
				stream.next_out = (व्योम *)&zisofs_sink_page;
				stream.avail_out = PAGE_SIZE;
			पूर्ण
		पूर्ण
		अगर (!stream.avail_in) अणु
			रुको_on_buffer(bhs[curbh]);
			अगर (!buffer_uptodate(bhs[curbh])) अणु
				*errp = -EIO;
				अवरोध;
			पूर्ण
			stream.next_in  = bhs[curbh]->b_data +
						(block_start & bufmask);
			stream.avail_in = min_t(अचिन्हित, bufsize -
						(block_start & bufmask),
						block_size);
			block_size -= stream.avail_in;
			block_start = 0;
		पूर्ण

		जबतक (stream.avail_out && stream.avail_in) अणु
			zerr = zlib_inflate(&stream, Z_SYNC_FLUSH);
			अगर (zerr == Z_BUF_ERROR && stream.avail_in == 0)
				अवरोध;
			अगर (zerr == Z_STREAM_END)
				अवरोध;
			अगर (zerr != Z_OK) अणु
				/* खातापूर्ण, error, or trying to पढ़ो beyond end of input */
				अगर (zerr == Z_MEM_ERROR)
					*errp = -ENOMEM;
				अन्यथा अणु
					prपूर्णांकk(KERN_DEBUG
					       "zisofs: zisofs_inflate returned"
					       " %d, inode = %lu,"
					       " page idx = %d, bh idx = %d,"
					       " avail_in = %ld,"
					       " avail_out = %ld\n",
					       zerr, inode->i_ino, curpage,
					       curbh, stream.avail_in,
					       stream.avail_out);
					*errp = -EIO;
				पूर्ण
				जाओ inflate_out;
			पूर्ण
		पूर्ण

		अगर (!stream.avail_out) अणु
			/* This page completed */
			अगर (pages[curpage]) अणु
				flush_dcache_page(pages[curpage]);
				SetPageUptodate(pages[curpage]);
			पूर्ण
			curpage++;
		पूर्ण
		अगर (!stream.avail_in)
			curbh++;
	पूर्ण
inflate_out:
	zlib_inflateEnd(&stream);

z_eio:
	mutex_unlock(&zisofs_zlib_lock);

b_eio:
	क्रम (i = 0; i < haveblocks; i++)
		brअन्यथा(bhs[i]);
	kमुक्त(bhs);
	वापस stream.total_out;
पूर्ण

/*
 * Uncompress data so that pages[full_page] is fully uptodate and possibly
 * fills in other pages अगर we have data क्रम them.
 */
अटल पूर्णांक zisofs_fill_pages(काष्ठा inode *inode, पूर्णांक full_page, पूर्णांक pcount,
			     काष्ठा page **pages)
अणु
	loff_t start_off, end_off;
	loff_t block_start, block_end;
	अचिन्हित पूर्णांक header_size = ISOFS_I(inode)->i_क्रमmat_parm[0];
	अचिन्हित पूर्णांक zisofs_block_shअगरt = ISOFS_I(inode)->i_क्रमmat_parm[1];
	अचिन्हित पूर्णांक blockptr;
	loff_t poffset = 0;
	blkcnt_t cstart_block, cend_block;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक blkbits = ISOFS_BUFFER_BITS(inode);
	अचिन्हित पूर्णांक blksize = 1 << blkbits;
	पूर्णांक err;
	loff_t ret;

	BUG_ON(!pages[full_page]);

	/*
	 * We want to पढ़ो at least 'full_page' page. Because we have to
	 * uncompress the whole compression block anyway, fill the surrounding
	 * pages with the data we have anyway...
	 */
	start_off = page_offset(pages[full_page]);
	end_off = min_t(loff_t, start_off + PAGE_SIZE, inode->i_size);

	cstart_block = start_off >> zisofs_block_shअगरt;
	cend_block = (end_off + (1 << zisofs_block_shअगरt) - 1)
			>> zisofs_block_shअगरt;

	WARN_ON(start_off - (full_page << PAGE_SHIFT) !=
		((cstart_block << zisofs_block_shअगरt) & PAGE_MASK));

	/* Find the poपूर्णांकer to this specअगरic chunk */
	/* Note: we're not using isonum_731() here because the data is known aligned */
	/* Note: header_size is in 32-bit words (4 bytes) */
	blockptr = (header_size + cstart_block) << 2;
	bh = isofs_bपढ़ो(inode, blockptr >> blkbits);
	अगर (!bh)
		वापस -EIO;
	block_start = le32_to_cpu(*(__le32 *)
				(bh->b_data + (blockptr & (blksize - 1))));

	जबतक (cstart_block < cend_block && pcount > 0) अणु
		/* Load end of the compressed block in the file */
		blockptr += 4;
		/* Traversed to next block? */
		अगर (!(blockptr & (blksize - 1))) अणु
			brअन्यथा(bh);

			bh = isofs_bपढ़ो(inode, blockptr >> blkbits);
			अगर (!bh)
				वापस -EIO;
		पूर्ण
		block_end = le32_to_cpu(*(__le32 *)
				(bh->b_data + (blockptr & (blksize - 1))));
		अगर (block_start > block_end) अणु
			brअन्यथा(bh);
			वापस -EIO;
		पूर्ण
		err = 0;
		ret = zisofs_uncompress_block(inode, block_start, block_end,
					      pcount, pages, poffset, &err);
		poffset += ret;
		pages += poffset >> PAGE_SHIFT;
		pcount -= poffset >> PAGE_SHIFT;
		full_page -= poffset >> PAGE_SHIFT;
		poffset &= ~PAGE_MASK;

		अगर (err) अणु
			brअन्यथा(bh);
			/*
			 * Did we finish पढ़ोing the page we really wanted
			 * to पढ़ो?
			 */
			अगर (full_page < 0)
				वापस 0;
			वापस err;
		पूर्ण

		block_start = block_end;
		cstart_block++;
	पूर्ण

	अगर (poffset && *pages) अणु
		स_रखो(page_address(*pages) + poffset, 0,
		       PAGE_SIZE - poffset);
		flush_dcache_page(*pages);
		SetPageUptodate(*pages);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * When decompressing, we typically obtain more than one page
 * per reference.  We inject the additional pages पूर्णांकo the page
 * cache as a क्रमm of पढ़ोahead.
 */
अटल पूर्णांक zisofs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा address_space *mapping = inode->i_mapping;
	पूर्णांक err;
	पूर्णांक i, pcount, full_page;
	अचिन्हित पूर्णांक zisofs_block_shअगरt = ISOFS_I(inode)->i_क्रमmat_parm[1];
	अचिन्हित पूर्णांक zisofs_pages_per_cblock =
		PAGE_SHIFT <= zisofs_block_shअगरt ?
		(1 << (zisofs_block_shअगरt - PAGE_SHIFT)) : 0;
	काष्ठा page **pages;
	pgoff_t index = page->index, end_index;

	end_index = (inode->i_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	/*
	 * If this page is wholly outside i_size we just वापस zero;
	 * करो_generic_file_पढ़ो() will handle this क्रम us
	 */
	अगर (index >= end_index) अणु
		SetPageUptodate(page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	अगर (PAGE_SHIFT <= zisofs_block_shअगरt) अणु
		/* We have alपढ़ोy been given one page, this is the one
		   we must करो. */
		full_page = index & (zisofs_pages_per_cblock - 1);
		pcount = min_t(पूर्णांक, zisofs_pages_per_cblock,
			end_index - (index & ~(zisofs_pages_per_cblock - 1)));
		index -= full_page;
	पूर्ण अन्यथा अणु
		full_page = 0;
		pcount = 1;
	पूर्ण
	pages = kसुस्मृति(max_t(अचिन्हित पूर्णांक, zisofs_pages_per_cblock, 1),
					माप(*pages), GFP_KERNEL);
	अगर (!pages) अणु
		unlock_page(page);
		वापस -ENOMEM;
	पूर्ण
	pages[full_page] = page;

	क्रम (i = 0; i < pcount; i++, index++) अणु
		अगर (i != full_page)
			pages[i] = grab_cache_page_noरुको(mapping, index);
		अगर (pages[i]) अणु
			ClearPageError(pages[i]);
			kmap(pages[i]);
		पूर्ण
	पूर्ण

	err = zisofs_fill_pages(inode, full_page, pcount, pages);

	/* Release any residual pages, करो not SetPageUptodate */
	क्रम (i = 0; i < pcount; i++) अणु
		अगर (pages[i]) अणु
			flush_dcache_page(pages[i]);
			अगर (i == full_page && err)
				SetPageError(pages[i]);
			kunmap(pages[i]);
			unlock_page(pages[i]);
			अगर (i != full_page)
				put_page(pages[i]);
		पूर्ण
	पूर्ण			

	/* At this poपूर्णांक, err contains 0 or -EIO depending on the "critical" page */
	kमुक्त(pages);
	वापस err;
पूर्ण

स्थिर काष्ठा address_space_operations zisofs_aops = अणु
	.पढ़ोpage = zisofs_पढ़ोpage,
	/* No bmap operation supported */
पूर्ण;

पूर्णांक __init zisofs_init(व्योम)
अणु
	zisofs_zlib_workspace = vदो_स्मृति(zlib_inflate_workspacesize());
	अगर ( !zisofs_zlib_workspace )
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम zisofs_cleanup(व्योम)
अणु
	vमुक्त(zisofs_zlib_workspace);
पूर्ण
