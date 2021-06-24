<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * compress.c - NTFS kernel compressed attributes handling.
 *		Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>

#समावेश "attrib.h"
#समावेश "inode.h"
#समावेश "debug.h"
#समावेश "ntfs.h"

/**
 * ntfs_compression_स्थिरants - क्रमागत of स्थिरants used in the compression code
 */
प्रकार क्रमागत अणु
	/* Token types and access mask. */
	NTFS_SYMBOL_TOKEN	=	0,
	NTFS_PHRASE_TOKEN	=	1,
	NTFS_TOKEN_MASK		=	1,

	/* Compression sub-block स्थिरants. */
	NTFS_SB_SIZE_MASK	=	0x0fff,
	NTFS_SB_SIZE		=	0x1000,
	NTFS_SB_IS_COMPRESSED	=	0x8000,

	/*
	 * The maximum compression block size is by definition 16 * the cluster
	 * size, with the maximum supported cluster size being 4kiB. Thus the
	 * maximum compression buffer size is 64kiB, so we use this when
	 * initializing the compression buffer.
	 */
	NTFS_MAX_CB_SIZE	= 64 * 1024,
पूर्ण ntfs_compression_स्थिरants;

/**
 * ntfs_compression_buffer - one buffer क्रम the decompression engine
 */
अटल u8 *ntfs_compression_buffer;

/**
 * ntfs_cb_lock - spinlock which protects ntfs_compression_buffer
 */
अटल DEFINE_SPINLOCK(ntfs_cb_lock);

/**
 * allocate_compression_buffers - allocate the decompression buffers
 *
 * Caller has to hold the ntfs_lock mutex.
 *
 * Return 0 on success or -ENOMEM अगर the allocations failed.
 */
पूर्णांक allocate_compression_buffers(व्योम)
अणु
	BUG_ON(ntfs_compression_buffer);

	ntfs_compression_buffer = vदो_स्मृति(NTFS_MAX_CB_SIZE);
	अगर (!ntfs_compression_buffer)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * मुक्त_compression_buffers - मुक्त the decompression buffers
 *
 * Caller has to hold the ntfs_lock mutex.
 */
व्योम मुक्त_compression_buffers(व्योम)
अणु
	BUG_ON(!ntfs_compression_buffer);
	vमुक्त(ntfs_compression_buffer);
	ntfs_compression_buffer = शून्य;
पूर्ण

/**
 * zero_partial_compressed_page - zero out of bounds compressed page region
 */
अटल व्योम zero_partial_compressed_page(काष्ठा page *page,
		स्थिर s64 initialized_size)
अणु
	u8 *kp = page_address(page);
	अचिन्हित पूर्णांक kp_ofs;

	ntfs_debug("Zeroing page region outside initialized size.");
	अगर (((s64)page->index << PAGE_SHIFT) >= initialized_size) अणु
		clear_page(kp);
		वापस;
	पूर्ण
	kp_ofs = initialized_size & ~PAGE_MASK;
	स_रखो(kp + kp_ofs, 0, PAGE_SIZE - kp_ofs);
	वापस;
पूर्ण

/**
 * handle_bounds_compressed_page - test क्रम&handle out of bounds compressed page
 */
अटल अंतरभूत व्योम handle_bounds_compressed_page(काष्ठा page *page,
		स्थिर loff_t i_size, स्थिर s64 initialized_size)
अणु
	अगर ((page->index >= (initialized_size >> PAGE_SHIFT)) &&
			(initialized_size < i_size))
		zero_partial_compressed_page(page, initialized_size);
	वापस;
पूर्ण

/**
 * ntfs_decompress - decompress a compression block पूर्णांकo an array of pages
 * @dest_pages:		destination array of pages
 * @completed_pages:	scratch space to track completed pages
 * @dest_index:		current index पूर्णांकo @dest_pages (IN/OUT)
 * @dest_ofs:		current offset within @dest_pages[@dest_index] (IN/OUT)
 * @dest_max_index:	maximum index पूर्णांकo @dest_pages (IN)
 * @dest_max_ofs:	maximum offset within @dest_pages[@dest_max_index] (IN)
 * @xpage:		the target page (-1 अगर none) (IN)
 * @xpage_करोne:		set to 1 अगर xpage was completed successfully (IN/OUT)
 * @cb_start:		compression block to decompress (IN)
 * @cb_size:		size of compression block @cb_start in bytes (IN)
 * @i_size:		file size when we started the पढ़ो (IN)
 * @initialized_size:	initialized file size when we started the पढ़ो (IN)
 *
 * The caller must have disabled preemption. ntfs_decompress() reenables it when
 * the critical section is finished.
 *
 * This decompresses the compression block @cb_start पूर्णांकo the array of
 * destination pages @dest_pages starting at index @dest_index पूर्णांकo @dest_pages
 * and at offset @dest_pos पूर्णांकo the page @dest_pages[@dest_index].
 *
 * When the page @dest_pages[@xpage] is completed, @xpage_करोne is set to 1.
 * If xpage is -1 or @xpage has not been completed, @xpage_करोne is not modअगरied.
 *
 * @cb_start is a poपूर्णांकer to the compression block which needs decompressing
 * and @cb_size is the size of @cb_start in bytes (8-64kiB).
 *
 * Return 0 अगर success or -EOVERFLOW on error in the compressed stream.
 * @xpage_करोne indicates whether the target page (@dest_pages[@xpage]) was
 * completed during the decompression of the compression block (@cb_start).
 *
 * Warning: This function *REQUIRES* PAGE_SIZE >= 4096 or it will blow up
 * unpredicatbly! You have been warned!
 *
 * Note to hackers: This function may not sleep until it has finished accessing
 * the compression block @cb_start as it is a per-CPU buffer.
 */
अटल पूर्णांक ntfs_decompress(काष्ठा page *dest_pages[], पूर्णांक completed_pages[],
		पूर्णांक *dest_index, पूर्णांक *dest_ofs, स्थिर पूर्णांक dest_max_index,
		स्थिर पूर्णांक dest_max_ofs, स्थिर पूर्णांक xpage, अक्षर *xpage_करोne,
		u8 *स्थिर cb_start, स्थिर u32 cb_size, स्थिर loff_t i_size,
		स्थिर s64 initialized_size)
अणु
	/*
	 * Poपूर्णांकers पूर्णांकo the compressed data, i.e. the compression block (cb),
	 * and the therein contained sub-blocks (sb).
	 */
	u8 *cb_end = cb_start + cb_size; /* End of cb. */
	u8 *cb = cb_start;	/* Current position in cb. */
	u8 *cb_sb_start = cb;	/* Beginning of the current sb in the cb. */
	u8 *cb_sb_end;		/* End of current sb / beginning of next sb. */

	/* Variables क्रम uncompressed data / destination. */
	काष्ठा page *dp;	/* Current destination page being worked on. */
	u8 *dp_addr;		/* Current poपूर्णांकer पूर्णांकo dp. */
	u8 *dp_sb_start;	/* Start of current sub-block in dp. */
	u8 *dp_sb_end;		/* End of current sb in dp (dp_sb_start +
				   NTFS_SB_SIZE). */
	u16 करो_sb_start;	/* @dest_ofs when starting this sub-block. */
	u16 करो_sb_end;		/* @dest_ofs of end of this sb (करो_sb_start +
				   NTFS_SB_SIZE). */

	/* Variables क्रम tag and token parsing. */
	u8 tag;			/* Current tag. */
	पूर्णांक token;		/* Loop counter क्रम the eight tokens in tag. */
	पूर्णांक nr_completed_pages = 0;

	/* Default error code. */
	पूर्णांक err = -EOVERFLOW;

	ntfs_debug("Entering, cb_size = 0x%x.", cb_size);
करो_next_sb:
	ntfs_debug("Beginning sub-block at offset = 0x%zx in the cb.",
			cb - cb_start);
	/*
	 * Have we reached the end of the compression block or the end of the
	 * decompressed data?  The latter can happen क्रम example अगर the current
	 * position in the compression block is one byte beक्रमe its end so the
	 * first two checks करो not detect it.
	 */
	अगर (cb == cb_end || !le16_to_cpup((le16*)cb) ||
			(*dest_index == dest_max_index &&
			*dest_ofs == dest_max_ofs)) अणु
		पूर्णांक i;

		ntfs_debug("Completed. Returning success (0).");
		err = 0;
वापस_error:
		/* We can sleep from now on, so we drop lock. */
		spin_unlock(&ntfs_cb_lock);
		/* Second stage: finalize completed pages. */
		अगर (nr_completed_pages > 0) अणु
			क्रम (i = 0; i < nr_completed_pages; i++) अणु
				पूर्णांक di = completed_pages[i];

				dp = dest_pages[di];
				/*
				 * If we are outside the initialized size, zero
				 * the out of bounds page range.
				 */
				handle_bounds_compressed_page(dp, i_size,
						initialized_size);
				flush_dcache_page(dp);
				kunmap(dp);
				SetPageUptodate(dp);
				unlock_page(dp);
				अगर (di == xpage)
					*xpage_करोne = 1;
				अन्यथा
					put_page(dp);
				dest_pages[di] = शून्य;
			पूर्ण
		पूर्ण
		वापस err;
	पूर्ण

	/* Setup offsets क्रम the current sub-block destination. */
	करो_sb_start = *dest_ofs;
	करो_sb_end = करो_sb_start + NTFS_SB_SIZE;

	/* Check that we are still within allowed boundaries. */
	अगर (*dest_index == dest_max_index && करो_sb_end > dest_max_ofs)
		जाओ वापस_overflow;

	/* Does the minimum size of a compressed sb overflow valid range? */
	अगर (cb + 6 > cb_end)
		जाओ वापस_overflow;

	/* Setup the current sub-block source poपूर्णांकers and validate range. */
	cb_sb_start = cb;
	cb_sb_end = cb_sb_start + (le16_to_cpup((le16*)cb) & NTFS_SB_SIZE_MASK)
			+ 3;
	अगर (cb_sb_end > cb_end)
		जाओ वापस_overflow;

	/* Get the current destination page. */
	dp = dest_pages[*dest_index];
	अगर (!dp) अणु
		/* No page present. Skip decompression of this sub-block. */
		cb = cb_sb_end;

		/* Advance destination position to next sub-block. */
		*dest_ofs = (*dest_ofs + NTFS_SB_SIZE) & ~PAGE_MASK;
		अगर (!*dest_ofs && (++*dest_index > dest_max_index))
			जाओ वापस_overflow;
		जाओ करो_next_sb;
	पूर्ण

	/* We have a valid destination page. Setup the destination poपूर्णांकers. */
	dp_addr = (u8*)page_address(dp) + करो_sb_start;

	/* Now, we are पढ़ोy to process the current sub-block (sb). */
	अगर (!(le16_to_cpup((le16*)cb) & NTFS_SB_IS_COMPRESSED)) अणु
		ntfs_debug("Found uncompressed sub-block.");
		/* This sb is not compressed, just copy it पूर्णांकo destination. */

		/* Advance source position to first data byte. */
		cb += 2;

		/* An uncompressed sb must be full size. */
		अगर (cb_sb_end - cb != NTFS_SB_SIZE)
			जाओ वापस_overflow;

		/* Copy the block and advance the source position. */
		स_नकल(dp_addr, cb, NTFS_SB_SIZE);
		cb += NTFS_SB_SIZE;

		/* Advance destination position to next sub-block. */
		*dest_ofs += NTFS_SB_SIZE;
		अगर (!(*dest_ofs &= ~PAGE_MASK)) अणु
finalize_page:
			/*
			 * First stage: add current page index to array of
			 * completed pages.
			 */
			completed_pages[nr_completed_pages++] = *dest_index;
			अगर (++*dest_index > dest_max_index)
				जाओ वापस_overflow;
		पूर्ण
		जाओ करो_next_sb;
	पूर्ण
	ntfs_debug("Found compressed sub-block.");
	/* This sb is compressed, decompress it पूर्णांकo destination. */

	/* Setup destination poपूर्णांकers. */
	dp_sb_start = dp_addr;
	dp_sb_end = dp_sb_start + NTFS_SB_SIZE;

	/* Forward to the first tag in the sub-block. */
	cb += 2;
करो_next_tag:
	अगर (cb == cb_sb_end) अणु
		/* Check अगर the decompressed sub-block was not full-length. */
		अगर (dp_addr < dp_sb_end) अणु
			पूर्णांक nr_bytes = करो_sb_end - *dest_ofs;

			ntfs_debug("Filling incomplete sub-block with "
					"zeroes.");
			/* Zero reमुख्यder and update destination position. */
			स_रखो(dp_addr, 0, nr_bytes);
			*dest_ofs += nr_bytes;
		पूर्ण
		/* We have finished the current sub-block. */
		अगर (!(*dest_ofs &= ~PAGE_MASK))
			जाओ finalize_page;
		जाओ करो_next_sb;
	पूर्ण

	/* Check we are still in range. */
	अगर (cb > cb_sb_end || dp_addr > dp_sb_end)
		जाओ वापस_overflow;

	/* Get the next tag and advance to first token. */
	tag = *cb++;

	/* Parse the eight tokens described by the tag. */
	क्रम (token = 0; token < 8; token++, tag >>= 1) अणु
		u16 lg, pt, length, max_non_overlap;
		रेजिस्टर u16 i;
		u8 *dp_back_addr;

		/* Check अगर we are करोne / still in range. */
		अगर (cb >= cb_sb_end || dp_addr > dp_sb_end)
			अवरोध;

		/* Determine token type and parse appropriately.*/
		अगर ((tag & NTFS_TOKEN_MASK) == NTFS_SYMBOL_TOKEN) अणु
			/*
			 * We have a symbol token, copy the symbol across, and
			 * advance the source and destination positions.
			 */
			*dp_addr++ = *cb++;
			++*dest_ofs;

			/* Continue with the next token. */
			जारी;
		पूर्ण

		/*
		 * We have a phrase token. Make sure it is not the first tag in
		 * the sb as this is illegal and would confuse the code below.
		 */
		अगर (dp_addr == dp_sb_start)
			जाओ वापस_overflow;

		/*
		 * Determine the number of bytes to go back (p) and the number
		 * of bytes to copy (l). We use an optimized algorithm in which
		 * we first calculate log2(current destination position in sb),
		 * which allows determination of l and p in O(1) rather than
		 * O(n). We just need an arch-optimized log2() function now.
		 */
		lg = 0;
		क्रम (i = *dest_ofs - करो_sb_start - 1; i >= 0x10; i >>= 1)
			lg++;

		/* Get the phrase token पूर्णांकo i. */
		pt = le16_to_cpup((le16*)cb);

		/*
		 * Calculate starting position of the byte sequence in
		 * the destination using the fact that p = (pt >> (12 - lg)) + 1
		 * and make sure we करोn't go too far back.
		 */
		dp_back_addr = dp_addr - (pt >> (12 - lg)) - 1;
		अगर (dp_back_addr < dp_sb_start)
			जाओ वापस_overflow;

		/* Now calculate the length of the byte sequence. */
		length = (pt & (0xfff >> lg)) + 3;

		/* Advance destination position and verअगरy it is in range. */
		*dest_ofs += length;
		अगर (*dest_ofs > करो_sb_end)
			जाओ वापस_overflow;

		/* The number of non-overlapping bytes. */
		max_non_overlap = dp_addr - dp_back_addr;

		अगर (length <= max_non_overlap) अणु
			/* The byte sequence करोesn't overlap, just copy it. */
			स_नकल(dp_addr, dp_back_addr, length);

			/* Advance destination poपूर्णांकer. */
			dp_addr += length;
		पूर्ण अन्यथा अणु
			/*
			 * The byte sequence करोes overlap, copy non-overlapping
			 * part and then करो a slow byte by byte copy क्रम the
			 * overlapping part. Also, advance the destination
			 * poपूर्णांकer.
			 */
			स_नकल(dp_addr, dp_back_addr, max_non_overlap);
			dp_addr += max_non_overlap;
			dp_back_addr += max_non_overlap;
			length -= max_non_overlap;
			जबतक (length--)
				*dp_addr++ = *dp_back_addr++;
		पूर्ण

		/* Advance source position and जारी with the next token. */
		cb += 2;
	पूर्ण

	/* No tokens left in the current tag. Continue with the next tag. */
	जाओ करो_next_tag;

वापस_overflow:
	ntfs_error(शून्य, "Failed. Returning -EOVERFLOW.");
	जाओ वापस_error;
पूर्ण

/**
 * ntfs_पढ़ो_compressed_block - पढ़ो a compressed block पूर्णांकo the page cache
 * @page:	locked page in the compression block(s) we need to पढ़ो
 *
 * When we are called the page has alपढ़ोy been verअगरied to be locked and the
 * attribute is known to be non-resident, not encrypted, but compressed.
 *
 * 1. Determine which compression block(s) @page is in.
 * 2. Get hold of all pages corresponding to this/these compression block(s).
 * 3. Read the (first) compression block.
 * 4. Decompress it पूर्णांकo the corresponding pages.
 * 5. Throw the compressed data away and proceed to 3. क्रम the next compression
 *    block or वापस success अगर no more compression blocks left.
 *
 * Warning: We have to be careful what we करो about existing pages. They might
 * have been written to so that we would lose data अगर we were to just overग_लिखो
 * them with the out-of-date uncompressed data.
 *
 * FIXME: For PAGE_SIZE > cb_size we are not करोing the Right Thing(TM) at
 * the end of the file I think. We need to detect this हाल and zero the out
 * of bounds reमुख्यder of the page in question and mark it as handled. At the
 * moment we would just वापस -EIO on such a page. This bug will only become
 * apparent अगर pages are above 8kiB and the NTFS volume only uses 512 byte
 * clusters so is probably not going to be seen by anyone. Still this should
 * be fixed. (AIA)
 *
 * FIXME: Again क्रम PAGE_SIZE > cb_size we are screwing up both in
 * handling sparse and compressed cbs. (AIA)
 *
 * FIXME: At the moment we करोn't करो any zeroing out in the हाल that
 * initialized_size is less than data_size. This should be safe because of the
 * nature of the compression algorithm used. Just in हाल we check and output
 * an error message in पढ़ो inode अगर the two sizes are not equal क्रम a
 * compressed file. (AIA)
 */
पूर्णांक ntfs_पढ़ो_compressed_block(काष्ठा page *page)
अणु
	loff_t i_size;
	s64 initialized_size;
	काष्ठा address_space *mapping = page->mapping;
	ntfs_inode *ni = NTFS_I(mapping->host);
	ntfs_volume *vol = ni->vol;
	काष्ठा super_block *sb = vol->sb;
	runlist_element *rl;
	अचिन्हित दीर्घ flags, block_size = sb->s_blocksize;
	अचिन्हित अक्षर block_size_bits = sb->s_blocksize_bits;
	u8 *cb, *cb_pos, *cb_end;
	काष्ठा buffer_head **bhs;
	अचिन्हित दीर्घ offset, index = page->index;
	u32 cb_size = ni->itype.compressed.block_size;
	u64 cb_size_mask = cb_size - 1UL;
	VCN vcn;
	LCN lcn;
	/* The first wanted vcn (minimum alignment is PAGE_SIZE). */
	VCN start_vcn = (((s64)index << PAGE_SHIFT) & ~cb_size_mask) >>
			vol->cluster_size_bits;
	/*
	 * The first vcn after the last wanted vcn (minimum alignment is again
	 * PAGE_SIZE.
	 */
	VCN end_vcn = ((((s64)(index + 1UL) << PAGE_SHIFT) + cb_size - 1)
			& ~cb_size_mask) >> vol->cluster_size_bits;
	/* Number of compression blocks (cbs) in the wanted vcn range. */
	अचिन्हित पूर्णांक nr_cbs = (end_vcn - start_vcn) << vol->cluster_size_bits
			>> ni->itype.compressed.block_size_bits;
	/*
	 * Number of pages required to store the uncompressed data from all
	 * compression blocks (cbs) overlapping @page. Due to alignment
	 * guarantees of start_vcn and end_vcn, no need to round up here.
	 */
	अचिन्हित पूर्णांक nr_pages = (end_vcn - start_vcn) <<
			vol->cluster_size_bits >> PAGE_SHIFT;
	अचिन्हित पूर्णांक xpage, max_page, cur_page, cur_ofs, i;
	अचिन्हित पूर्णांक cb_clusters, cb_max_ofs;
	पूर्णांक block, max_block, cb_max_page, bhs_size, nr_bhs, err = 0;
	काष्ठा page **pages;
	पूर्णांक *completed_pages;
	अचिन्हित अक्षर xpage_करोne = 0;

	ntfs_debug("Entering, page->index = 0x%lx, cb_size = 0x%x, nr_pages = "
			"%i.", index, cb_size, nr_pages);
	/*
	 * Bad things happen अगर we get here क्रम anything that is not an
	 * unnamed $DATA attribute.
	 */
	BUG_ON(ni->type != AT_DATA);
	BUG_ON(ni->name_len);

	pages = kदो_स्मृति_array(nr_pages, माप(काष्ठा page *), GFP_NOFS);
	completed_pages = kदो_स्मृति_array(nr_pages + 1, माप(पूर्णांक), GFP_NOFS);

	/* Allocate memory to store the buffer heads we need. */
	bhs_size = cb_size / block_size * माप(काष्ठा buffer_head *);
	bhs = kदो_स्मृति(bhs_size, GFP_NOFS);

	अगर (unlikely(!pages || !bhs || !completed_pages)) अणु
		kमुक्त(bhs);
		kमुक्त(pages);
		kमुक्त(completed_pages);
		unlock_page(page);
		ntfs_error(vol->sb, "Failed to allocate internal buffers.");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * We have alपढ़ोy been given one page, this is the one we must करो.
	 * Once again, the alignment guarantees keep it simple.
	 */
	offset = start_vcn << vol->cluster_size_bits >> PAGE_SHIFT;
	xpage = index - offset;
	pages[xpage] = page;
	/*
	 * The reमुख्यing pages need to be allocated and inserted पूर्णांकo the page
	 * cache, alignment guarantees keep all the below much simpler. (-8
	 */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	i_size = i_size_पढ़ो(VFS_I(ni));
	initialized_size = ni->initialized_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	max_page = ((i_size + PAGE_SIZE - 1) >> PAGE_SHIFT) -
			offset;
	/* Is the page fully outside i_size? (truncate in progress) */
	अगर (xpage >= max_page) अणु
		kमुक्त(bhs);
		kमुक्त(pages);
		kमुक्त(completed_pages);
		zero_user(page, 0, PAGE_SIZE);
		ntfs_debug("Compressed read outside i_size - truncated?");
		SetPageUptodate(page);
		unlock_page(page);
		वापस 0;
	पूर्ण
	अगर (nr_pages < max_page)
		max_page = nr_pages;
	क्रम (i = 0; i < max_page; i++, offset++) अणु
		अगर (i != xpage)
			pages[i] = grab_cache_page_noरुको(mapping, offset);
		page = pages[i];
		अगर (page) अणु
			/*
			 * We only (re)पढ़ो the page अगर it isn't alपढ़ोy पढ़ो
			 * in and/or dirty or we would be losing data or at
			 * least wasting our समय.
			 */
			अगर (!PageDirty(page) && (!PageUptodate(page) ||
					PageError(page))) अणु
				ClearPageError(page);
				kmap(page);
				जारी;
			पूर्ण
			unlock_page(page);
			put_page(page);
			pages[i] = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * We have the runlist, and all the destination pages we need to fill.
	 * Now पढ़ो the first compression block.
	 */
	cur_page = 0;
	cur_ofs = 0;
	cb_clusters = ni->itype.compressed.block_clusters;
करो_next_cb:
	nr_cbs--;
	nr_bhs = 0;

	/* Read all cb buffer heads one cluster at a समय. */
	rl = शून्य;
	क्रम (vcn = start_vcn, start_vcn += cb_clusters; vcn < start_vcn;
			vcn++) अणु
		bool is_retry = false;

		अगर (!rl) अणु
lock_retry_remap:
			करोwn_पढ़ो(&ni->runlist.lock);
			rl = ni->runlist.rl;
		पूर्ण
		अगर (likely(rl != शून्य)) अणु
			/* Seek to element containing target vcn. */
			जबतक (rl->length && rl[1].vcn <= vcn)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
		पूर्ण अन्यथा
			lcn = LCN_RL_NOT_MAPPED;
		ntfs_debug("Reading vcn = 0x%llx, lcn = 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)vcn,
				(अचिन्हित दीर्घ दीर्घ)lcn);
		अगर (lcn < 0) अणु
			/*
			 * When we reach the first sparse cluster we have
			 * finished with the cb.
			 */
			अगर (lcn == LCN_HOLE)
				अवरोध;
			अगर (is_retry || lcn != LCN_RL_NOT_MAPPED)
				जाओ rl_err;
			is_retry = true;
			/*
			 * Attempt to map runlist, dropping lock क्रम the
			 * duration.
			 */
			up_पढ़ो(&ni->runlist.lock);
			अगर (!ntfs_map_runlist(ni, vcn))
				जाओ lock_retry_remap;
			जाओ map_rl_err;
		पूर्ण
		block = lcn << vol->cluster_size_bits >> block_size_bits;
		/* Read the lcn from device in chunks of block_size bytes. */
		max_block = block + (vol->cluster_size >> block_size_bits);
		करो अणु
			ntfs_debug("block = 0x%x.", block);
			अगर (unlikely(!(bhs[nr_bhs] = sb_getblk(sb, block))))
				जाओ getblk_err;
			nr_bhs++;
		पूर्ण जबतक (++block < max_block);
	पूर्ण

	/* Release the lock अगर we took it. */
	अगर (rl)
		up_पढ़ो(&ni->runlist.lock);

	/* Setup and initiate io on all buffer heads. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		काष्ठा buffer_head *tbh = bhs[i];

		अगर (!trylock_buffer(tbh))
			जारी;
		अगर (unlikely(buffer_uptodate(tbh))) अणु
			unlock_buffer(tbh);
			जारी;
		पूर्ण
		get_bh(tbh);
		tbh->b_end_io = end_buffer_पढ़ो_sync;
		submit_bh(REQ_OP_READ, 0, tbh);
	पूर्ण

	/* Wait क्रम io completion on all buffer heads. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		काष्ठा buffer_head *tbh = bhs[i];

		अगर (buffer_uptodate(tbh))
			जारी;
		रुको_on_buffer(tbh);
		/*
		 * We need an optimization barrier here, otherwise we start
		 * hitting the below fixup code when accessing a loopback
		 * mounted ntfs partition. This indicates either there is a
		 * race condition in the loop driver or, more likely, gcc
		 * overoptimises the code without the barrier and it करोesn't
		 * करो the Right Thing(TM).
		 */
		barrier();
		अगर (unlikely(!buffer_uptodate(tbh))) अणु
			ntfs_warning(vol->sb, "Buffer is unlocked but not "
					"uptodate! Unplugging the disk queue "
					"and rescheduling.");
			get_bh(tbh);
			io_schedule();
			put_bh(tbh);
			अगर (unlikely(!buffer_uptodate(tbh)))
				जाओ पढ़ो_err;
			ntfs_warning(vol->sb, "Buffer is now uptodate. Good.");
		पूर्ण
	पूर्ण

	/*
	 * Get the compression buffer. We must not sleep any more
	 * until we are finished with it.
	 */
	spin_lock(&ntfs_cb_lock);
	cb = ntfs_compression_buffer;

	BUG_ON(!cb);

	cb_pos = cb;
	cb_end = cb + cb_size;

	/* Copy the buffer heads पूर्णांकo the contiguous buffer. */
	क्रम (i = 0; i < nr_bhs; i++) अणु
		स_नकल(cb_pos, bhs[i]->b_data, block_size);
		cb_pos += block_size;
	पूर्ण

	/* Just a precaution. */
	अगर (cb_pos + 2 <= cb + cb_size)
		*(u16*)cb_pos = 0;

	/* Reset cb_pos back to the beginning. */
	cb_pos = cb;

	/* We now have both source (अगर present) and destination. */
	ntfs_debug("Successfully read the compression block.");

	/* The last page and maximum offset within it क्रम the current cb. */
	cb_max_page = (cur_page << PAGE_SHIFT) + cur_ofs + cb_size;
	cb_max_ofs = cb_max_page & ~PAGE_MASK;
	cb_max_page >>= PAGE_SHIFT;

	/* Catch end of file inside a compression block. */
	अगर (cb_max_page > max_page)
		cb_max_page = max_page;

	अगर (vcn == start_vcn - cb_clusters) अणु
		/* Sparse cb, zero out page range overlapping the cb. */
		ntfs_debug("Found sparse compression block.");
		/* We can sleep from now on, so we drop lock. */
		spin_unlock(&ntfs_cb_lock);
		अगर (cb_max_ofs)
			cb_max_page--;
		क्रम (; cur_page < cb_max_page; cur_page++) अणु
			page = pages[cur_page];
			अगर (page) अणु
				अगर (likely(!cur_ofs))
					clear_page(page_address(page));
				अन्यथा
					स_रखो(page_address(page) + cur_ofs, 0,
							PAGE_SIZE -
							cur_ofs);
				flush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unlock_page(page);
				अगर (cur_page == xpage)
					xpage_करोne = 1;
				अन्यथा
					put_page(page);
				pages[cur_page] = शून्य;
			पूर्ण
			cb_pos += PAGE_SIZE - cur_ofs;
			cur_ofs = 0;
			अगर (cb_pos >= cb_end)
				अवरोध;
		पूर्ण
		/* If we have a partial final page, deal with it now. */
		अगर (cb_max_ofs && cb_pos < cb_end) अणु
			page = pages[cur_page];
			अगर (page)
				स_रखो(page_address(page) + cur_ofs, 0,
						cb_max_ofs - cur_ofs);
			/*
			 * No need to update cb_pos at this stage:
			 *	cb_pos += cb_max_ofs - cur_ofs;
			 */
			cur_ofs = cb_max_ofs;
		पूर्ण
	पूर्ण अन्यथा अगर (vcn == start_vcn) अणु
		/* We can't sleep so we need two stages. */
		अचिन्हित पूर्णांक cur2_page = cur_page;
		अचिन्हित पूर्णांक cur_ofs2 = cur_ofs;
		u8 *cb_pos2 = cb_pos;

		ntfs_debug("Found uncompressed compression block.");
		/* Uncompressed cb, copy it to the destination pages. */
		/*
		 * TODO: As a big optimization, we could detect this हाल
		 * beक्रमe we पढ़ो all the pages and use block_पढ़ो_full_page()
		 * on all full pages instead (we still have to treat partial
		 * pages especially but at least we are getting rid of the
		 * synchronous io क्रम the majority of pages.
		 * Or अगर we choose not to करो the पढ़ो-ahead/-behind stuff, we
		 * could just वापस block_पढ़ो_full_page(pages[xpage]) as दीर्घ
		 * as PAGE_SIZE <= cb_size.
		 */
		अगर (cb_max_ofs)
			cb_max_page--;
		/* First stage: copy data पूर्णांकo destination pages. */
		क्रम (; cur_page < cb_max_page; cur_page++) अणु
			page = pages[cur_page];
			अगर (page)
				स_नकल(page_address(page) + cur_ofs, cb_pos,
						PAGE_SIZE - cur_ofs);
			cb_pos += PAGE_SIZE - cur_ofs;
			cur_ofs = 0;
			अगर (cb_pos >= cb_end)
				अवरोध;
		पूर्ण
		/* If we have a partial final page, deal with it now. */
		अगर (cb_max_ofs && cb_pos < cb_end) अणु
			page = pages[cur_page];
			अगर (page)
				स_नकल(page_address(page) + cur_ofs, cb_pos,
						cb_max_ofs - cur_ofs);
			cb_pos += cb_max_ofs - cur_ofs;
			cur_ofs = cb_max_ofs;
		पूर्ण
		/* We can sleep from now on, so drop lock. */
		spin_unlock(&ntfs_cb_lock);
		/* Second stage: finalize pages. */
		क्रम (; cur2_page < cb_max_page; cur2_page++) अणु
			page = pages[cur2_page];
			अगर (page) अणु
				/*
				 * If we are outside the initialized size, zero
				 * the out of bounds page range.
				 */
				handle_bounds_compressed_page(page, i_size,
						initialized_size);
				flush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unlock_page(page);
				अगर (cur2_page == xpage)
					xpage_करोne = 1;
				अन्यथा
					put_page(page);
				pages[cur2_page] = शून्य;
			पूर्ण
			cb_pos2 += PAGE_SIZE - cur_ofs2;
			cur_ofs2 = 0;
			अगर (cb_pos2 >= cb_end)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Compressed cb, decompress it पूर्णांकo the destination page(s). */
		अचिन्हित पूर्णांक prev_cur_page = cur_page;

		ntfs_debug("Found compressed compression block.");
		err = ntfs_decompress(pages, completed_pages, &cur_page,
				&cur_ofs, cb_max_page, cb_max_ofs, xpage,
				&xpage_करोne, cb_pos, cb_size - (cb_pos - cb),
				i_size, initialized_size);
		/*
		 * We can sleep from now on, lock alपढ़ोy dropped by
		 * ntfs_decompress().
		 */
		अगर (err) अणु
			ntfs_error(vol->sb, "ntfs_decompress() failed in inode "
					"0x%lx with error code %i. Skipping "
					"this compression block.",
					ni->mft_no, -err);
			/* Release the unfinished pages. */
			क्रम (; prev_cur_page < cur_page; prev_cur_page++) अणु
				page = pages[prev_cur_page];
				अगर (page) अणु
					flush_dcache_page(page);
					kunmap(page);
					unlock_page(page);
					अगर (prev_cur_page != xpage)
						put_page(page);
					pages[prev_cur_page] = शून्य;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Release the buffer heads. */
	क्रम (i = 0; i < nr_bhs; i++)
		brअन्यथा(bhs[i]);

	/* Do we have more work to करो? */
	अगर (nr_cbs)
		जाओ करो_next_cb;

	/* We no दीर्घer need the list of buffer heads. */
	kमुक्त(bhs);

	/* Clean up अगर we have any pages left. Should never happen. */
	क्रम (cur_page = 0; cur_page < max_page; cur_page++) अणु
		page = pages[cur_page];
		अगर (page) अणु
			ntfs_error(vol->sb, "Still have pages left! "
					"Terminating them with extreme "
					"prejudice.  Inode 0x%lx, page index "
					"0x%lx.", ni->mft_no, page->index);
			flush_dcache_page(page);
			kunmap(page);
			unlock_page(page);
			अगर (cur_page != xpage)
				put_page(page);
			pages[cur_page] = शून्य;
		पूर्ण
	पूर्ण

	/* We no दीर्घer need the list of pages. */
	kमुक्त(pages);
	kमुक्त(completed_pages);

	/* If we have completed the requested page, we वापस success. */
	अगर (likely(xpage_करोne))
		वापस 0;

	ntfs_debug("Failed. Returning error code %s.", err == -EOVERFLOW ?
			"EOVERFLOW" : (!err ? "EIO" : "unknown error"));
	वापस err < 0 ? err : -EIO;

पढ़ो_err:
	ntfs_error(vol->sb, "IO error while reading compressed data.");
	/* Release the buffer heads. */
	क्रम (i = 0; i < nr_bhs; i++)
		brअन्यथा(bhs[i]);
	जाओ err_out;

map_rl_err:
	ntfs_error(vol->sb, "ntfs_map_runlist() failed. Cannot read "
			"compression block.");
	जाओ err_out;

rl_err:
	up_पढ़ो(&ni->runlist.lock);
	ntfs_error(vol->sb, "ntfs_rl_vcn_to_lcn() failed. Cannot read "
			"compression block.");
	जाओ err_out;

getblk_err:
	up_पढ़ो(&ni->runlist.lock);
	ntfs_error(vol->sb, "getblk() failed. Cannot read compression block.");

err_out:
	kमुक्त(bhs);
	क्रम (i = cur_page; i < max_page; i++) अणु
		page = pages[i];
		अगर (page) अणु
			flush_dcache_page(page);
			kunmap(page);
			unlock_page(page);
			अगर (i != xpage)
				put_page(page);
		पूर्ण
	पूर्ण
	kमुक्त(pages);
	kमुक्त(completed_pages);
	वापस -EIO;
पूर्ण
