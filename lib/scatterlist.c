<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Jens Axboe <jens.axboe@oracle.com>
 *
 * Scatterlist handling helpers.
 */
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kmemleak.h>

/**
 * sg_next - वापस the next scatterlist entry in a list
 * @sg:		The current sg entry
 *
 * Description:
 *   Usually the next entry will be @sg@ + 1, but अगर this sg element is part
 *   of a chained scatterlist, it could jump to the start of a new
 *   scatterlist array.
 *
 **/
काष्ठा scatterlist *sg_next(काष्ठा scatterlist *sg)
अणु
	अगर (sg_is_last(sg))
		वापस शून्य;

	sg++;
	अगर (unlikely(sg_is_chain(sg)))
		sg = sg_chain_ptr(sg);

	वापस sg;
पूर्ण
EXPORT_SYMBOL(sg_next);

/**
 * sg_nents - वापस total count of entries in scatterlist
 * @sg:		The scatterlist
 *
 * Description:
 * Allows to know how many entries are in sg, taking पूर्णांकo acount
 * chaining as well
 *
 **/
पूर्णांक sg_nents(काष्ठा scatterlist *sg)
अणु
	पूर्णांक nents;
	क्रम (nents = 0; sg; sg = sg_next(sg))
		nents++;
	वापस nents;
पूर्ण
EXPORT_SYMBOL(sg_nents);

/**
 * sg_nents_क्रम_len - वापस total count of entries in scatterlist
 *                    needed to satisfy the supplied length
 * @sg:		The scatterlist
 * @len:	The total required length
 *
 * Description:
 * Determines the number of entries in sg that are required to meet
 * the supplied length, taking पूर्णांकo acount chaining as well
 *
 * Returns:
 *   the number of sg entries needed, negative error on failure
 *
 **/
पूर्णांक sg_nents_क्रम_len(काष्ठा scatterlist *sg, u64 len)
अणु
	पूर्णांक nents;
	u64 total;

	अगर (!len)
		वापस 0;

	क्रम (nents = 0, total = 0; sg; sg = sg_next(sg)) अणु
		nents++;
		total += sg->length;
		अगर (total >= len)
			वापस nents;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(sg_nents_क्रम_len);

/**
 * sg_last - वापस the last scatterlist entry in a list
 * @sgl:	First entry in the scatterlist
 * @nents:	Number of entries in the scatterlist
 *
 * Description:
 *   Should only be used casually, it (currently) scans the entire list
 *   to get the last entry.
 *
 *   Note that the @sgl@ poपूर्णांकer passed in need not be the first one,
 *   the important bit is that @nents@ denotes the number of entries that
 *   exist from @sgl@.
 *
 **/
काष्ठा scatterlist *sg_last(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents)
अणु
	काष्ठा scatterlist *sg, *ret = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		ret = sg;

	BUG_ON(!sg_is_last(ret));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sg_last);

/**
 * sg_init_table - Initialize SG table
 * @sgl:	   The SG table
 * @nents:	   Number of entries in table
 *
 * Notes:
 *   If this is part of a chained sg table, sg_mark_end() should be
 *   used only on the last table part.
 *
 **/
व्योम sg_init_table(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents)
अणु
	स_रखो(sgl, 0, माप(*sgl) * nents);
	sg_init_marker(sgl, nents);
पूर्ण
EXPORT_SYMBOL(sg_init_table);

/**
 * sg_init_one - Initialize a single entry sg list
 * @sg:		 SG entry
 * @buf:	 Virtual address क्रम IO
 * @buflen:	 IO length
 *
 **/
व्योम sg_init_one(काष्ठा scatterlist *sg, स्थिर व्योम *buf, अचिन्हित पूर्णांक buflen)
अणु
	sg_init_table(sg, 1);
	sg_set_buf(sg, buf, buflen);
पूर्ण
EXPORT_SYMBOL(sg_init_one);

/*
 * The शेष behaviour of sg_alloc_table() is to use these kदो_स्मृति/kमुक्त
 * helpers.
 */
अटल काष्ठा scatterlist *sg_kदो_स्मृति(अचिन्हित पूर्णांक nents, gfp_t gfp_mask)
अणु
	अगर (nents == SG_MAX_SINGLE_ALLOC) अणु
		/*
		 * Kmemleak करोesn't track page allocations as they are not
		 * commonly used (in a raw क्रमm) क्रम kernel data काष्ठाures.
		 * As we chain together a list of pages and then a normal
		 * kदो_स्मृति (tracked by kmemleak), in order to क्रम that last
		 * allocation not to become decoupled (and thus a
		 * false-positive) we need to inक्रमm kmemleak of all the
		 * पूर्णांकermediate allocations.
		 */
		व्योम *ptr = (व्योम *) __get_मुक्त_page(gfp_mask);
		kmemleak_alloc(ptr, PAGE_SIZE, 1, gfp_mask);
		वापस ptr;
	पूर्ण अन्यथा
		वापस kदो_स्मृति_array(nents, माप(काष्ठा scatterlist),
				     gfp_mask);
पूर्ण

अटल व्योम sg_kमुक्त(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents)
अणु
	अगर (nents == SG_MAX_SINGLE_ALLOC) अणु
		kmemleak_मुक्त(sg);
		मुक्त_page((अचिन्हित दीर्घ) sg);
	पूर्ण अन्यथा
		kमुक्त(sg);
पूर्ण

/**
 * __sg_मुक्त_table - Free a previously mapped sg table
 * @table:	The sg table header to use
 * @max_ents:	The maximum number of entries per single scatterlist
 * @nents_first_chunk: Number of entries पूर्णांक the (pपुनः_स्मृतिated) first
 * 	scatterlist chunk, 0 means no such pपुनः_स्मृतिated first chunk
 * @मुक्त_fn:	Free function
 *
 *  Description:
 *    Free an sg table previously allocated and setup with
 *    __sg_alloc_table().  The @max_ents value must be identical to
 *    that previously used with __sg_alloc_table().
 *
 **/
व्योम __sg_मुक्त_table(काष्ठा sg_table *table, अचिन्हित पूर्णांक max_ents,
		     अचिन्हित पूर्णांक nents_first_chunk, sg_मुक्त_fn *मुक्त_fn)
अणु
	काष्ठा scatterlist *sgl, *next;
	अचिन्हित curr_max_ents = nents_first_chunk ?: max_ents;

	अगर (unlikely(!table->sgl))
		वापस;

	sgl = table->sgl;
	जबतक (table->orig_nents) अणु
		अचिन्हित पूर्णांक alloc_size = table->orig_nents;
		अचिन्हित पूर्णांक sg_size;

		/*
		 * If we have more than max_ents segments left,
		 * then assign 'next' to the sg table after the current one.
		 * sg_size is then one less than alloc size, since the last
		 * element is the chain poपूर्णांकer.
		 */
		अगर (alloc_size > curr_max_ents) अणु
			next = sg_chain_ptr(&sgl[curr_max_ents - 1]);
			alloc_size = curr_max_ents;
			sg_size = alloc_size - 1;
		पूर्ण अन्यथा अणु
			sg_size = alloc_size;
			next = शून्य;
		पूर्ण

		table->orig_nents -= sg_size;
		अगर (nents_first_chunk)
			nents_first_chunk = 0;
		अन्यथा
			मुक्त_fn(sgl, alloc_size);
		sgl = next;
		curr_max_ents = max_ents;
	पूर्ण

	table->sgl = शून्य;
पूर्ण
EXPORT_SYMBOL(__sg_मुक्त_table);

/**
 * sg_मुक्त_table - Free a previously allocated sg table
 * @table:	The mapped sg table header
 *
 **/
व्योम sg_मुक्त_table(काष्ठा sg_table *table)
अणु
	__sg_मुक्त_table(table, SG_MAX_SINGLE_ALLOC, false, sg_kमुक्त);
पूर्ण
EXPORT_SYMBOL(sg_मुक्त_table);

/**
 * __sg_alloc_table - Allocate and initialize an sg table with given allocator
 * @table:	The sg table header to use
 * @nents:	Number of entries in sg list
 * @max_ents:	The maximum number of entries the allocator वापसs per call
 * @nents_first_chunk: Number of entries पूर्णांक the (pपुनः_स्मृतिated) first
 * 	scatterlist chunk, 0 means no such pपुनः_स्मृतिated chunk provided by user
 * @gfp_mask:	GFP allocation mask
 * @alloc_fn:	Allocator to use
 *
 * Description:
 *   This function वापसs a @table @nents दीर्घ. The allocator is
 *   defined to वापस scatterlist chunks of maximum size @max_ents.
 *   Thus अगर @nents is bigger than @max_ents, the scatterlists will be
 *   chained in units of @max_ents.
 *
 * Notes:
 *   If this function वापसs non-0 (eg failure), the caller must call
 *   __sg_मुक्त_table() to cleanup any leftover allocations.
 *
 **/
पूर्णांक __sg_alloc_table(काष्ठा sg_table *table, अचिन्हित पूर्णांक nents,
		     अचिन्हित पूर्णांक max_ents, काष्ठा scatterlist *first_chunk,
		     अचिन्हित पूर्णांक nents_first_chunk, gfp_t gfp_mask,
		     sg_alloc_fn *alloc_fn)
अणु
	काष्ठा scatterlist *sg, *prv;
	अचिन्हित पूर्णांक left;
	अचिन्हित curr_max_ents = nents_first_chunk ?: max_ents;
	अचिन्हित prv_max_ents;

	स_रखो(table, 0, माप(*table));

	अगर (nents == 0)
		वापस -EINVAL;
#अगर_घोषित CONFIG_ARCH_NO_SG_CHAIN
	अगर (WARN_ON_ONCE(nents > max_ents))
		वापस -EINVAL;
#पूर्ण_अगर

	left = nents;
	prv = शून्य;
	करो अणु
		अचिन्हित पूर्णांक sg_size, alloc_size = left;

		अगर (alloc_size > curr_max_ents) अणु
			alloc_size = curr_max_ents;
			sg_size = alloc_size - 1;
		पूर्ण अन्यथा
			sg_size = alloc_size;

		left -= sg_size;

		अगर (first_chunk) अणु
			sg = first_chunk;
			first_chunk = शून्य;
		पूर्ण अन्यथा अणु
			sg = alloc_fn(alloc_size, gfp_mask);
		पूर्ण
		अगर (unlikely(!sg)) अणु
			/*
			 * Adjust entry count to reflect that the last
			 * entry of the previous table won't be used क्रम
			 * linkage.  Without this, sg_kमुक्त() may get
			 * confused.
			 */
			अगर (prv)
				table->nents = ++table->orig_nents;

			वापस -ENOMEM;
		पूर्ण

		sg_init_table(sg, alloc_size);
		table->nents = table->orig_nents += sg_size;

		/*
		 * If this is the first mapping, assign the sg table header.
		 * If this is not the first mapping, chain previous part.
		 */
		अगर (prv)
			sg_chain(prv, prv_max_ents, sg);
		अन्यथा
			table->sgl = sg;

		/*
		 * If no more entries after this one, mark the end
		 */
		अगर (!left)
			sg_mark_end(&sg[sg_size - 1]);

		prv = sg;
		prv_max_ents = curr_max_ents;
		curr_max_ents = max_ents;
	पूर्ण जबतक (left);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__sg_alloc_table);

/**
 * sg_alloc_table - Allocate and initialize an sg table
 * @table:	The sg table header to use
 * @nents:	Number of entries in sg list
 * @gfp_mask:	GFP allocation mask
 *
 *  Description:
 *    Allocate and initialize an sg table. If @nents@ is larger than
 *    SG_MAX_SINGLE_ALLOC a chained sg table will be setup.
 *
 **/
पूर्णांक sg_alloc_table(काष्ठा sg_table *table, अचिन्हित पूर्णांक nents, gfp_t gfp_mask)
अणु
	पूर्णांक ret;

	ret = __sg_alloc_table(table, nents, SG_MAX_SINGLE_ALLOC,
			       शून्य, 0, gfp_mask, sg_kदो_स्मृति);
	अगर (unlikely(ret))
		__sg_मुक्त_table(table, SG_MAX_SINGLE_ALLOC, 0, sg_kमुक्त);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sg_alloc_table);

अटल काष्ठा scatterlist *get_next_sg(काष्ठा sg_table *table,
				       काष्ठा scatterlist *cur,
				       अचिन्हित दीर्घ needed_sges,
				       gfp_t gfp_mask)
अणु
	काष्ठा scatterlist *new_sg, *next_sg;
	अचिन्हित पूर्णांक alloc_size;

	अगर (cur) अणु
		next_sg = sg_next(cur);
		/* Check अगर last entry should be keeped क्रम chainning */
		अगर (!sg_is_last(next_sg) || needed_sges == 1)
			वापस next_sg;
	पूर्ण

	alloc_size = min_t(अचिन्हित दीर्घ, needed_sges, SG_MAX_SINGLE_ALLOC);
	new_sg = sg_kदो_स्मृति(alloc_size, gfp_mask);
	अगर (!new_sg)
		वापस ERR_PTR(-ENOMEM);
	sg_init_table(new_sg, alloc_size);
	अगर (cur) अणु
		__sg_chain(next_sg, new_sg);
		table->orig_nents += alloc_size - 1;
	पूर्ण अन्यथा अणु
		table->sgl = new_sg;
		table->orig_nents = alloc_size;
		table->nents = 0;
	पूर्ण
	वापस new_sg;
पूर्ण

/**
 * __sg_alloc_table_from_pages - Allocate and initialize an sg table from
 *			         an array of pages
 * @sgt:	 The sg table header to use
 * @pages:	 Poपूर्णांकer to an array of page poपूर्णांकers
 * @n_pages:	 Number of pages in the pages array
 * @offset:      Offset from start of the first page to the start of a buffer
 * @size:        Number of valid bytes in the buffer (after offset)
 * @max_segment: Maximum size of a scatterlist element in bytes
 * @prv:	 Last populated sge in sgt
 * @left_pages:  Left pages caller have to set after this call
 * @gfp_mask:	 GFP allocation mask
 *
 * Description:
 *    If @prv is शून्य, allocate and initialize an sg table from a list of pages,
 *    अन्यथा reuse the scatterlist passed in at @prv.
 *    Contiguous ranges of the pages are squashed पूर्णांकo a single scatterlist
 *    entry up to the maximum size specअगरied in @max_segment.  A user may
 *    provide an offset at a start and a size of valid data in a buffer
 *    specअगरied by the page array.
 *
 * Returns:
 *   Last SGE in sgt on success, PTR_ERR on otherwise.
 *   The allocation in @sgt must be released by sg_मुक्त_table.
 *
 * Notes:
 *   If this function वापसs non-0 (eg failure), the caller must call
 *   sg_मुक्त_table() to cleanup any leftover allocations.
 */
काष्ठा scatterlist *__sg_alloc_table_from_pages(काष्ठा sg_table *sgt,
		काष्ठा page **pages, अचिन्हित पूर्णांक n_pages, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ size, अचिन्हित पूर्णांक max_segment,
		काष्ठा scatterlist *prv, अचिन्हित पूर्णांक left_pages,
		gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक chunks, cur_page, seg_len, i, prv_len = 0;
	अचिन्हित पूर्णांक added_nents = 0;
	काष्ठा scatterlist *s = prv;

	/*
	 * The algorithm below requires max_segment to be aligned to PAGE_SIZE
	 * otherwise it can overshoot.
	 */
	max_segment = ALIGN_DOWN(max_segment, PAGE_SIZE);
	अगर (WARN_ON(max_segment < PAGE_SIZE))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ENABLED(CONFIG_ARCH_NO_SG_CHAIN) && prv)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (prv) अणु
		अचिन्हित दीर्घ paddr = (page_to_pfn(sg_page(prv)) * PAGE_SIZE +
				       prv->offset + prv->length) /
				      PAGE_SIZE;

		अगर (WARN_ON(offset))
			वापस ERR_PTR(-EINVAL);

		/* Merge contiguous pages पूर्णांकo the last SG */
		prv_len = prv->length;
		जबतक (n_pages && page_to_pfn(pages[0]) == paddr) अणु
			अगर (prv->length + PAGE_SIZE > max_segment)
				अवरोध;
			prv->length += PAGE_SIZE;
			paddr++;
			pages++;
			n_pages--;
		पूर्ण
		अगर (!n_pages)
			जाओ out;
	पूर्ण

	/* compute number of contiguous chunks */
	chunks = 1;
	seg_len = 0;
	क्रम (i = 1; i < n_pages; i++) अणु
		seg_len += PAGE_SIZE;
		अगर (seg_len >= max_segment ||
		    page_to_pfn(pages[i]) != page_to_pfn(pages[i - 1]) + 1) अणु
			chunks++;
			seg_len = 0;
		पूर्ण
	पूर्ण

	/* merging chunks and putting them पूर्णांकo the scatterlist */
	cur_page = 0;
	क्रम (i = 0; i < chunks; i++) अणु
		अचिन्हित पूर्णांक j, chunk_size;

		/* look क्रम the end of the current chunk */
		seg_len = 0;
		क्रम (j = cur_page + 1; j < n_pages; j++) अणु
			seg_len += PAGE_SIZE;
			अगर (seg_len >= max_segment ||
			    page_to_pfn(pages[j]) !=
			    page_to_pfn(pages[j - 1]) + 1)
				अवरोध;
		पूर्ण

		/* Pass how many chunks might be left */
		s = get_next_sg(sgt, s, chunks - i + left_pages, gfp_mask);
		अगर (IS_ERR(s)) अणु
			/*
			 * Adjust entry length to be as beक्रमe function was
			 * called.
			 */
			अगर (prv)
				prv->length = prv_len;
			वापस s;
		पूर्ण
		chunk_size = ((j - cur_page) << PAGE_SHIFT) - offset;
		sg_set_page(s, pages[cur_page],
			    min_t(अचिन्हित दीर्घ, size, chunk_size), offset);
		added_nents++;
		size -= chunk_size;
		offset = 0;
		cur_page = j;
	पूर्ण
	sgt->nents += added_nents;
out:
	अगर (!left_pages)
		sg_mark_end(s);
	वापस s;
पूर्ण
EXPORT_SYMBOL(__sg_alloc_table_from_pages);

/**
 * sg_alloc_table_from_pages - Allocate and initialize an sg table from
 *			       an array of pages
 * @sgt:	 The sg table header to use
 * @pages:	 Poपूर्णांकer to an array of page poपूर्णांकers
 * @n_pages:	 Number of pages in the pages array
 * @offset:      Offset from start of the first page to the start of a buffer
 * @size:        Number of valid bytes in the buffer (after offset)
 * @gfp_mask:	 GFP allocation mask
 *
 *  Description:
 *    Allocate and initialize an sg table from a list of pages. Contiguous
 *    ranges of the pages are squashed पूर्णांकo a single scatterlist node. A user
 *    may provide an offset at a start and a size of valid data in a buffer
 *    specअगरied by the page array. The वापसed sg table is released by
 *    sg_मुक्त_table.
 *
 * Returns:
 *   0 on success, negative error on failure
 */
पूर्णांक sg_alloc_table_from_pages(काष्ठा sg_table *sgt, काष्ठा page **pages,
			      अचिन्हित पूर्णांक n_pages, अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ size, gfp_t gfp_mask)
अणु
	वापस PTR_ERR_OR_ZERO(__sg_alloc_table_from_pages(sgt, pages, n_pages,
			offset, size, अच_पूर्णांक_उच्च, शून्य, 0, gfp_mask));
पूर्ण
EXPORT_SYMBOL(sg_alloc_table_from_pages);

#अगर_घोषित CONFIG_SGL_ALLOC

/**
 * sgl_alloc_order - allocate a scatterlist and its pages
 * @length: Length in bytes of the scatterlist. Must be at least one
 * @order: Second argument क्रम alloc_pages()
 * @chainable: Whether or not to allocate an extra element in the scatterlist
 *	क्रम scatterlist chaining purposes
 * @gfp: Memory allocation flags
 * @nent_p: [out] Number of entries in the scatterlist that have pages
 *
 * Returns: A poपूर्णांकer to an initialized scatterlist or %शून्य upon failure.
 */
काष्ठा scatterlist *sgl_alloc_order(अचिन्हित दीर्घ दीर्घ length,
				    अचिन्हित पूर्णांक order, bool chainable,
				    gfp_t gfp, अचिन्हित पूर्णांक *nent_p)
अणु
	काष्ठा scatterlist *sgl, *sg;
	काष्ठा page *page;
	अचिन्हित पूर्णांक nent, nalloc;
	u32 elem_len;

	nent = round_up(length, PAGE_SIZE << order) >> (PAGE_SHIFT + order);
	/* Check क्रम पूर्णांकeger overflow */
	अगर (length > (nent << (PAGE_SHIFT + order)))
		वापस शून्य;
	nalloc = nent;
	अगर (chainable) अणु
		/* Check क्रम पूर्णांकeger overflow */
		अगर (nalloc + 1 < nalloc)
			वापस शून्य;
		nalloc++;
	पूर्ण
	sgl = kदो_स्मृति_array(nalloc, माप(काष्ठा scatterlist),
			    gfp & ~GFP_DMA);
	अगर (!sgl)
		वापस शून्य;

	sg_init_table(sgl, nalloc);
	sg = sgl;
	जबतक (length) अणु
		elem_len = min_t(u64, length, PAGE_SIZE << order);
		page = alloc_pages(gfp, order);
		अगर (!page) अणु
			sgl_मुक्त_order(sgl, order);
			वापस शून्य;
		पूर्ण

		sg_set_page(sg, page, elem_len, 0);
		length -= elem_len;
		sg = sg_next(sg);
	पूर्ण
	WARN_ONCE(length, "length = %lld\n", length);
	अगर (nent_p)
		*nent_p = nent;
	वापस sgl;
पूर्ण
EXPORT_SYMBOL(sgl_alloc_order);

/**
 * sgl_alloc - allocate a scatterlist and its pages
 * @length: Length in bytes of the scatterlist
 * @gfp: Memory allocation flags
 * @nent_p: [out] Number of entries in the scatterlist
 *
 * Returns: A poपूर्णांकer to an initialized scatterlist or %शून्य upon failure.
 */
काष्ठा scatterlist *sgl_alloc(अचिन्हित दीर्घ दीर्घ length, gfp_t gfp,
			      अचिन्हित पूर्णांक *nent_p)
अणु
	वापस sgl_alloc_order(length, 0, false, gfp, nent_p);
पूर्ण
EXPORT_SYMBOL(sgl_alloc);

/**
 * sgl_मुक्त_n_order - मुक्त a scatterlist and its pages
 * @sgl: Scatterlist with one or more elements
 * @nents: Maximum number of elements to मुक्त
 * @order: Second argument क्रम __मुक्त_pages()
 *
 * Notes:
 * - If several scatterlists have been chained and each chain element is
 *   मुक्तd separately then it's essential to set nents correctly to aव्योम that a
 *   page would get मुक्तd twice.
 * - All pages in a chained scatterlist can be मुक्तd at once by setting @nents
 *   to a high number.
 */
व्योम sgl_मुक्त_n_order(काष्ठा scatterlist *sgl, पूर्णांक nents, पूर्णांक order)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा page *page;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		अगर (!sg)
			अवरोध;
		page = sg_page(sg);
		अगर (page)
			__मुक्त_pages(page, order);
	पूर्ण
	kमुक्त(sgl);
पूर्ण
EXPORT_SYMBOL(sgl_मुक्त_n_order);

/**
 * sgl_मुक्त_order - मुक्त a scatterlist and its pages
 * @sgl: Scatterlist with one or more elements
 * @order: Second argument क्रम __मुक्त_pages()
 */
व्योम sgl_मुक्त_order(काष्ठा scatterlist *sgl, पूर्णांक order)
अणु
	sgl_मुक्त_n_order(sgl, पूर्णांक_उच्च, order);
पूर्ण
EXPORT_SYMBOL(sgl_मुक्त_order);

/**
 * sgl_मुक्त - मुक्त a scatterlist and its pages
 * @sgl: Scatterlist with one or more elements
 */
व्योम sgl_मुक्त(काष्ठा scatterlist *sgl)
अणु
	sgl_मुक्त_order(sgl, 0);
पूर्ण
EXPORT_SYMBOL(sgl_मुक्त);

#पूर्ण_अगर /* CONFIG_SGL_ALLOC */

व्योम __sg_page_iter_start(काष्ठा sg_page_iter *piter,
			  काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक nents,
			  अचिन्हित दीर्घ pgoffset)
अणु
	piter->__pg_advance = 0;
	piter->__nents = nents;

	piter->sg = sglist;
	piter->sg_pgoffset = pgoffset;
पूर्ण
EXPORT_SYMBOL(__sg_page_iter_start);

अटल पूर्णांक sg_page_count(काष्ठा scatterlist *sg)
अणु
	वापस PAGE_ALIGN(sg->offset + sg->length) >> PAGE_SHIFT;
पूर्ण

bool __sg_page_iter_next(काष्ठा sg_page_iter *piter)
अणु
	अगर (!piter->__nents || !piter->sg)
		वापस false;

	piter->sg_pgoffset += piter->__pg_advance;
	piter->__pg_advance = 1;

	जबतक (piter->sg_pgoffset >= sg_page_count(piter->sg)) अणु
		piter->sg_pgoffset -= sg_page_count(piter->sg);
		piter->sg = sg_next(piter->sg);
		अगर (!--piter->__nents || !piter->sg)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(__sg_page_iter_next);

अटल पूर्णांक sg_dma_page_count(काष्ठा scatterlist *sg)
अणु
	वापस PAGE_ALIGN(sg->offset + sg_dma_len(sg)) >> PAGE_SHIFT;
पूर्ण

bool __sg_page_iter_dma_next(काष्ठा sg_dma_page_iter *dma_iter)
अणु
	काष्ठा sg_page_iter *piter = &dma_iter->base;

	अगर (!piter->__nents || !piter->sg)
		वापस false;

	piter->sg_pgoffset += piter->__pg_advance;
	piter->__pg_advance = 1;

	जबतक (piter->sg_pgoffset >= sg_dma_page_count(piter->sg)) अणु
		piter->sg_pgoffset -= sg_dma_page_count(piter->sg);
		piter->sg = sg_next(piter->sg);
		अगर (!--piter->__nents || !piter->sg)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(__sg_page_iter_dma_next);

/**
 * sg_miter_start - start mapping iteration over a sg list
 * @miter: sg mapping iter to be started
 * @sgl: sg list to iterate over
 * @nents: number of sg entries
 *
 * Description:
 *   Starts mapping iterator @miter.
 *
 * Context:
 *   Don't care.
 */
व्योम sg_miter_start(काष्ठा sg_mapping_iter *miter, काष्ठा scatterlist *sgl,
		    अचिन्हित पूर्णांक nents, अचिन्हित पूर्णांक flags)
अणु
	स_रखो(miter, 0, माप(काष्ठा sg_mapping_iter));

	__sg_page_iter_start(&miter->piter, sgl, nents, 0);
	WARN_ON(!(flags & (SG_MITER_TO_SG | SG_MITER_FROM_SG)));
	miter->__flags = flags;
पूर्ण
EXPORT_SYMBOL(sg_miter_start);

अटल bool sg_miter_get_next_page(काष्ठा sg_mapping_iter *miter)
अणु
	अगर (!miter->__reमुख्यing) अणु
		काष्ठा scatterlist *sg;

		अगर (!__sg_page_iter_next(&miter->piter))
			वापस false;

		sg = miter->piter.sg;

		miter->__offset = miter->piter.sg_pgoffset ? 0 : sg->offset;
		miter->piter.sg_pgoffset += miter->__offset >> PAGE_SHIFT;
		miter->__offset &= PAGE_SIZE - 1;
		miter->__reमुख्यing = sg->offset + sg->length -
				     (miter->piter.sg_pgoffset << PAGE_SHIFT) -
				     miter->__offset;
		miter->__reमुख्यing = min_t(अचिन्हित दीर्घ, miter->__reमुख्यing,
					   PAGE_SIZE - miter->__offset);
	पूर्ण

	वापस true;
पूर्ण

/**
 * sg_miter_skip - reposition mapping iterator
 * @miter: sg mapping iter to be skipped
 * @offset: number of bytes to plus the current location
 *
 * Description:
 *   Sets the offset of @miter to its current location plus @offset bytes.
 *   If mapping iterator @miter has been proceeded by sg_miter_next(), this
 *   stops @miter.
 *
 * Context:
 *   Don't care अगर @miter is stopped, or not proceeded yet.
 *   Otherwise, preemption disabled अगर the SG_MITER_ATOMIC is set.
 *
 * Returns:
 *   true अगर @miter contains the valid mapping.  false अगर end of sg
 *   list is reached.
 */
bool sg_miter_skip(काष्ठा sg_mapping_iter *miter, off_t offset)
अणु
	sg_miter_stop(miter);

	जबतक (offset) अणु
		off_t consumed;

		अगर (!sg_miter_get_next_page(miter))
			वापस false;

		consumed = min_t(off_t, offset, miter->__reमुख्यing);
		miter->__offset += consumed;
		miter->__reमुख्यing -= consumed;
		offset -= consumed;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(sg_miter_skip);

/**
 * sg_miter_next - proceed mapping iterator to the next mapping
 * @miter: sg mapping iter to proceed
 *
 * Description:
 *   Proceeds @miter to the next mapping.  @miter should have been started
 *   using sg_miter_start().  On successful वापस, @miter->page,
 *   @miter->addr and @miter->length poपूर्णांक to the current mapping.
 *
 * Context:
 *   Preemption disabled अगर SG_MITER_ATOMIC.  Preemption must stay disabled
 *   till @miter is stopped.  May sleep अगर !SG_MITER_ATOMIC.
 *
 * Returns:
 *   true अगर @miter contains the next mapping.  false अगर end of sg
 *   list is reached.
 */
bool sg_miter_next(काष्ठा sg_mapping_iter *miter)
अणु
	sg_miter_stop(miter);

	/*
	 * Get to the next page अगर necessary.
	 * __reमुख्यing, __offset is adjusted by sg_miter_stop
	 */
	अगर (!sg_miter_get_next_page(miter))
		वापस false;

	miter->page = sg_page_iter_page(&miter->piter);
	miter->consumed = miter->length = miter->__reमुख्यing;

	अगर (miter->__flags & SG_MITER_ATOMIC)
		miter->addr = kmap_atomic(miter->page) + miter->__offset;
	अन्यथा
		miter->addr = kmap(miter->page) + miter->__offset;

	वापस true;
पूर्ण
EXPORT_SYMBOL(sg_miter_next);

/**
 * sg_miter_stop - stop mapping iteration
 * @miter: sg mapping iter to be stopped
 *
 * Description:
 *   Stops mapping iterator @miter.  @miter should have been started
 *   using sg_miter_start().  A stopped iteration can be resumed by
 *   calling sg_miter_next() on it.  This is useful when resources (kmap)
 *   need to be released during iteration.
 *
 * Context:
 *   Preemption disabled अगर the SG_MITER_ATOMIC is set.  Don't care
 *   otherwise.
 */
व्योम sg_miter_stop(काष्ठा sg_mapping_iter *miter)
अणु
	WARN_ON(miter->consumed > miter->length);

	/* drop resources from the last iteration */
	अगर (miter->addr) अणु
		miter->__offset += miter->consumed;
		miter->__reमुख्यing -= miter->consumed;

		अगर ((miter->__flags & SG_MITER_TO_SG) &&
		    !PageSlab(miter->page))
			flush_kernel_dcache_page(miter->page);

		अगर (miter->__flags & SG_MITER_ATOMIC) अणु
			WARN_ON_ONCE(preemptible());
			kunmap_atomic(miter->addr);
		पूर्ण अन्यथा
			kunmap(miter->page);

		miter->page = शून्य;
		miter->addr = शून्य;
		miter->length = 0;
		miter->consumed = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sg_miter_stop);

/**
 * sg_copy_buffer - Copy data between a linear buffer and an SG list
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buf:		 Where to copy from
 * @buflen:		 The number of bytes to copy
 * @skip:		 Number of bytes to skip beक्रमe copying
 * @to_buffer:		 transfer direction (true == from an sg list to a
 *			 buffer, false == from a buffer to an sg list)
 *
 * Returns the number of copied bytes.
 *
 **/
माप_प्रकार sg_copy_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents, व्योम *buf,
		      माप_प्रकार buflen, off_t skip, bool to_buffer)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक sg_flags = SG_MITER_ATOMIC;

	अगर (to_buffer)
		sg_flags |= SG_MITER_FROM_SG;
	अन्यथा
		sg_flags |= SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	अगर (!sg_miter_skip(&miter, skip))
		वापस 0;

	जबतक ((offset < buflen) && sg_miter_next(&miter)) अणु
		अचिन्हित पूर्णांक len;

		len = min(miter.length, buflen - offset);

		अगर (to_buffer)
			स_नकल(buf + offset, miter.addr, len);
		अन्यथा
			स_नकल(miter.addr, buf + offset, len);

		offset += len;
	पूर्ण

	sg_miter_stop(&miter);

	वापस offset;
पूर्ण
EXPORT_SYMBOL(sg_copy_buffer);

/**
 * sg_copy_from_buffer - Copy from a linear buffer to an SG list
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buf:		 Where to copy from
 * @buflen:		 The number of bytes to copy
 *
 * Returns the number of copied bytes.
 *
 **/
माप_प्रकार sg_copy_from_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			   स्थिर व्योम *buf, माप_प्रकार buflen)
अणु
	वापस sg_copy_buffer(sgl, nents, (व्योम *)buf, buflen, 0, false);
पूर्ण
EXPORT_SYMBOL(sg_copy_from_buffer);

/**
 * sg_copy_to_buffer - Copy from an SG list to a linear buffer
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buf:		 Where to copy to
 * @buflen:		 The number of bytes to copy
 *
 * Returns the number of copied bytes.
 *
 **/
माप_प्रकार sg_copy_to_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			 व्योम *buf, माप_प्रकार buflen)
अणु
	वापस sg_copy_buffer(sgl, nents, buf, buflen, 0, true);
पूर्ण
EXPORT_SYMBOL(sg_copy_to_buffer);

/**
 * sg_pcopy_from_buffer - Copy from a linear buffer to an SG list
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buf:		 Where to copy from
 * @buflen:		 The number of bytes to copy
 * @skip:		 Number of bytes to skip beक्रमe copying
 *
 * Returns the number of copied bytes.
 *
 **/
माप_प्रकार sg_pcopy_from_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			    स्थिर व्योम *buf, माप_प्रकार buflen, off_t skip)
अणु
	वापस sg_copy_buffer(sgl, nents, (व्योम *)buf, buflen, skip, false);
पूर्ण
EXPORT_SYMBOL(sg_pcopy_from_buffer);

/**
 * sg_pcopy_to_buffer - Copy from an SG list to a linear buffer
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buf:		 Where to copy to
 * @buflen:		 The number of bytes to copy
 * @skip:		 Number of bytes to skip beक्रमe copying
 *
 * Returns the number of copied bytes.
 *
 **/
माप_प्रकार sg_pcopy_to_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			  व्योम *buf, माप_प्रकार buflen, off_t skip)
अणु
	वापस sg_copy_buffer(sgl, nents, buf, buflen, skip, true);
पूर्ण
EXPORT_SYMBOL(sg_pcopy_to_buffer);

/**
 * sg_zero_buffer - Zero-out a part of a SG list
 * @sgl:		 The SG list
 * @nents:		 Number of SG entries
 * @buflen:		 The number of bytes to zero out
 * @skip:		 Number of bytes to skip beक्रमe zeroing
 *
 * Returns the number of bytes zeroed.
 **/
माप_प्रकार sg_zero_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
		       माप_प्रकार buflen, off_t skip)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक sg_flags = SG_MITER_ATOMIC | SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	अगर (!sg_miter_skip(&miter, skip))
		वापस false;

	जबतक (offset < buflen && sg_miter_next(&miter)) अणु
		अचिन्हित पूर्णांक len;

		len = min(miter.length, buflen - offset);
		स_रखो(miter.addr, 0, len);

		offset += len;
	पूर्ण

	sg_miter_stop(&miter);
	वापस offset;
पूर्ण
EXPORT_SYMBOL(sg_zero_buffer);
