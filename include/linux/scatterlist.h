<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCATTERLIST_H
#घोषणा _LINUX_SCATTERLIST_H

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/पन.स>

काष्ठा scatterlist अणु
	अचिन्हित दीर्घ	page_link;
	अचिन्हित पूर्णांक	offset;
	अचिन्हित पूर्णांक	length;
	dma_addr_t	dma_address;
#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
	अचिन्हित पूर्णांक	dma_length;
#पूर्ण_अगर
पूर्ण;

/*
 * These macros should be used after a dma_map_sg call has been करोne
 * to get bus addresses of each of the SG entries and their lengths.
 * You should only work with the number of sg entries dma_map_sg
 * वापसs, or alternatively stop on the first sg_dma_len(sg) which
 * is 0.
 */
#घोषणा sg_dma_address(sg)	((sg)->dma_address)

#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
#घोषणा sg_dma_len(sg)		((sg)->dma_length)
#अन्यथा
#घोषणा sg_dma_len(sg)		((sg)->length)
#पूर्ण_अगर

काष्ठा sg_table अणु
	काष्ठा scatterlist *sgl;	/* the list */
	अचिन्हित पूर्णांक nents;		/* number of mapped entries */
	अचिन्हित पूर्णांक orig_nents;	/* original size of list */
पूर्ण;

/*
 * Notes on SG table design.
 *
 * We use the अचिन्हित दीर्घ page_link field in the scatterlist काष्ठा to place
 * the page poपूर्णांकer AND encode inक्रमmation about the sg table as well. The two
 * lower bits are reserved क्रम this inक्रमmation.
 *
 * If bit 0 is set, then the page_link contains a poपूर्णांकer to the next sg
 * table list. Otherwise the next entry is at sg + 1.
 *
 * If bit 1 is set, then this sg entry is the last element in a list.
 *
 * See sg_next().
 *
 */

#घोषणा SG_CHAIN	0x01UL
#घोषणा SG_END		0x02UL

/*
 * We overload the LSB of the page poपूर्णांकer to indicate whether it's
 * a valid sg entry, or whether it poपूर्णांकs to the start of a new scatterlist.
 * Those low bits are there क्रम everyone! (thanks mason :-)
 */
#घोषणा sg_is_chain(sg)		((sg)->page_link & SG_CHAIN)
#घोषणा sg_is_last(sg)		((sg)->page_link & SG_END)
#घोषणा sg_chain_ptr(sg)	\
	((काष्ठा scatterlist *) ((sg)->page_link & ~(SG_CHAIN | SG_END)))

/**
 * sg_assign_page - Assign a given page to an SG entry
 * @sg:		    SG entry
 * @page:	    The page
 *
 * Description:
 *   Assign page to sg entry. Also see sg_set_page(), the most commonly used
 *   variant.
 *
 **/
अटल अंतरभूत व्योम sg_assign_page(काष्ठा scatterlist *sg, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ page_link = sg->page_link & (SG_CHAIN | SG_END);

	/*
	 * In order क्रम the low bit stealing approach to work, pages
	 * must be aligned at a 32-bit boundary as a minimum.
	 */
	BUG_ON((अचिन्हित दीर्घ) page & (SG_CHAIN | SG_END));
#अगर_घोषित CONFIG_DEBUG_SG
	BUG_ON(sg_is_chain(sg));
#पूर्ण_अगर
	sg->page_link = page_link | (अचिन्हित दीर्घ) page;
पूर्ण

/**
 * sg_set_page - Set sg entry to poपूर्णांक at given page
 * @sg:		 SG entry
 * @page:	 The page
 * @len:	 Length of data
 * @offset:	 Offset पूर्णांकo page
 *
 * Description:
 *   Use this function to set an sg entry poपूर्णांकing at a page, never assign
 *   the page directly. We encode sg table inक्रमmation in the lower bits
 *   of the page poपूर्णांकer. See sg_page() क्रम looking up the page beदीर्घing
 *   to an sg entry.
 *
 **/
अटल अंतरभूत व्योम sg_set_page(काष्ठा scatterlist *sg, काष्ठा page *page,
			       अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	sg_assign_page(sg, page);
	sg->offset = offset;
	sg->length = len;
पूर्ण

अटल अंतरभूत काष्ठा page *sg_page(काष्ठा scatterlist *sg)
अणु
#अगर_घोषित CONFIG_DEBUG_SG
	BUG_ON(sg_is_chain(sg));
#पूर्ण_अगर
	वापस (काष्ठा page *)((sg)->page_link & ~(SG_CHAIN | SG_END));
पूर्ण

/**
 * sg_set_buf - Set sg entry to poपूर्णांक at given data
 * @sg:		 SG entry
 * @buf:	 Data
 * @buflen:	 Data length
 *
 **/
अटल अंतरभूत व्योम sg_set_buf(काष्ठा scatterlist *sg, स्थिर व्योम *buf,
			      अचिन्हित पूर्णांक buflen)
अणु
#अगर_घोषित CONFIG_DEBUG_SG
	BUG_ON(!virt_addr_valid(buf));
#पूर्ण_अगर
	sg_set_page(sg, virt_to_page(buf), buflen, offset_in_page(buf));
पूर्ण

/*
 * Loop over each sg element, following the poपूर्णांकer to a new list अगर necessary
 */
#घोषणा क्रम_each_sg(sglist, sg, nr, __i)	\
	क्रम (__i = 0, sg = (sglist); __i < (nr); __i++, sg = sg_next(sg))

/*
 * Loop over each sg element in the given sg_table object.
 */
#घोषणा क्रम_each_sgtable_sg(sgt, sg, i)		\
	क्रम_each_sg((sgt)->sgl, sg, (sgt)->orig_nents, i)

/*
 * Loop over each sg element in the given *DMA mapped* sg_table object.
 * Please use sg_dma_address(sg) and sg_dma_len(sg) to extract DMA addresses
 * of the each element.
 */
#घोषणा क्रम_each_sgtable_dma_sg(sgt, sg, i)	\
	क्रम_each_sg((sgt)->sgl, sg, (sgt)->nents, i)

अटल अंतरभूत व्योम __sg_chain(काष्ठा scatterlist *chain_sg,
			      काष्ठा scatterlist *sgl)
अणु
	/*
	 * offset and length are unused क्रम chain entry. Clear them.
	 */
	chain_sg->offset = 0;
	chain_sg->length = 0;

	/*
	 * Set lowest bit to indicate a link poपूर्णांकer, and make sure to clear
	 * the termination bit अगर it happens to be set.
	 */
	chain_sg->page_link = ((अचिन्हित दीर्घ) sgl | SG_CHAIN) & ~SG_END;
पूर्ण

/**
 * sg_chain - Chain two sglists together
 * @prv:	First scatterlist
 * @prv_nents:	Number of entries in prv
 * @sgl:	Second scatterlist
 *
 * Description:
 *   Links @prv@ and @sgl@ together, to क्रमm a दीर्घer scatterlist.
 *
 **/
अटल अंतरभूत व्योम sg_chain(काष्ठा scatterlist *prv, अचिन्हित पूर्णांक prv_nents,
			    काष्ठा scatterlist *sgl)
अणु
	__sg_chain(&prv[prv_nents - 1], sgl);
पूर्ण

/**
 * sg_mark_end - Mark the end of the scatterlist
 * @sg:		 SG entryScatterlist
 *
 * Description:
 *   Marks the passed in sg entry as the termination poपूर्णांक क्रम the sg
 *   table. A call to sg_next() on this entry will वापस शून्य.
 *
 **/
अटल अंतरभूत व्योम sg_mark_end(काष्ठा scatterlist *sg)
अणु
	/*
	 * Set termination bit, clear potential chain bit
	 */
	sg->page_link |= SG_END;
	sg->page_link &= ~SG_CHAIN;
पूर्ण

/**
 * sg_unmark_end - Unकरो setting the end of the scatterlist
 * @sg:		 SG entryScatterlist
 *
 * Description:
 *   Removes the termination marker from the given entry of the scatterlist.
 *
 **/
अटल अंतरभूत व्योम sg_unmark_end(काष्ठा scatterlist *sg)
अणु
	sg->page_link &= ~SG_END;
पूर्ण

/**
 * sg_phys - Return physical address of an sg entry
 * @sg:	     SG entry
 *
 * Description:
 *   This calls page_to_phys() on the page in this sg entry, and adds the
 *   sg offset. The caller must know that it is legal to call page_to_phys()
 *   on the sg page.
 *
 **/
अटल अंतरभूत dma_addr_t sg_phys(काष्ठा scatterlist *sg)
अणु
	वापस page_to_phys(sg_page(sg)) + sg->offset;
पूर्ण

/**
 * sg_virt - Return भव address of an sg entry
 * @sg:      SG entry
 *
 * Description:
 *   This calls page_address() on the page in this sg entry, and adds the
 *   sg offset. The caller must know that the sg page has a valid भव
 *   mapping.
 *
 **/
अटल अंतरभूत व्योम *sg_virt(काष्ठा scatterlist *sg)
अणु
	वापस page_address(sg_page(sg)) + sg->offset;
पूर्ण

/**
 * sg_init_marker - Initialize markers in sg table
 * @sgl:	   The SG table
 * @nents:	   Number of entries in table
 *
 **/
अटल अंतरभूत व्योम sg_init_marker(काष्ठा scatterlist *sgl,
				  अचिन्हित पूर्णांक nents)
अणु
	sg_mark_end(&sgl[nents - 1]);
पूर्ण

पूर्णांक sg_nents(काष्ठा scatterlist *sg);
पूर्णांक sg_nents_क्रम_len(काष्ठा scatterlist *sg, u64 len);
काष्ठा scatterlist *sg_next(काष्ठा scatterlist *);
काष्ठा scatterlist *sg_last(काष्ठा scatterlist *s, अचिन्हित पूर्णांक);
व्योम sg_init_table(काष्ठा scatterlist *, अचिन्हित पूर्णांक);
व्योम sg_init_one(काष्ठा scatterlist *, स्थिर व्योम *, अचिन्हित पूर्णांक);
पूर्णांक sg_split(काष्ठा scatterlist *in, स्थिर पूर्णांक in_mapped_nents,
	     स्थिर off_t skip, स्थिर पूर्णांक nb_splits,
	     स्थिर माप_प्रकार *split_sizes,
	     काष्ठा scatterlist **out, पूर्णांक *out_mapped_nents,
	     gfp_t gfp_mask);

प्रकार काष्ठा scatterlist *(sg_alloc_fn)(अचिन्हित पूर्णांक, gfp_t);
प्रकार व्योम (sg_मुक्त_fn)(काष्ठा scatterlist *, अचिन्हित पूर्णांक);

व्योम __sg_मुक्त_table(काष्ठा sg_table *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
		     sg_मुक्त_fn *);
व्योम sg_मुक्त_table(काष्ठा sg_table *);
पूर्णांक __sg_alloc_table(काष्ठा sg_table *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
		     काष्ठा scatterlist *, अचिन्हित पूर्णांक, gfp_t, sg_alloc_fn *);
पूर्णांक sg_alloc_table(काष्ठा sg_table *, अचिन्हित पूर्णांक, gfp_t);
काष्ठा scatterlist *__sg_alloc_table_from_pages(काष्ठा sg_table *sgt,
		काष्ठा page **pages, अचिन्हित पूर्णांक n_pages, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ size, अचिन्हित पूर्णांक max_segment,
		काष्ठा scatterlist *prv, अचिन्हित पूर्णांक left_pages,
		gfp_t gfp_mask);
पूर्णांक sg_alloc_table_from_pages(काष्ठा sg_table *sgt, काष्ठा page **pages,
			      अचिन्हित पूर्णांक n_pages, अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ size, gfp_t gfp_mask);

#अगर_घोषित CONFIG_SGL_ALLOC
काष्ठा scatterlist *sgl_alloc_order(अचिन्हित दीर्घ दीर्घ length,
				    अचिन्हित पूर्णांक order, bool chainable,
				    gfp_t gfp, अचिन्हित पूर्णांक *nent_p);
काष्ठा scatterlist *sgl_alloc(अचिन्हित दीर्घ दीर्घ length, gfp_t gfp,
			      अचिन्हित पूर्णांक *nent_p);
व्योम sgl_मुक्त_n_order(काष्ठा scatterlist *sgl, पूर्णांक nents, पूर्णांक order);
व्योम sgl_मुक्त_order(काष्ठा scatterlist *sgl, पूर्णांक order);
व्योम sgl_मुक्त(काष्ठा scatterlist *sgl);
#पूर्ण_अगर /* CONFIG_SGL_ALLOC */

माप_प्रकार sg_copy_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents, व्योम *buf,
		      माप_प्रकार buflen, off_t skip, bool to_buffer);

माप_प्रकार sg_copy_from_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			   स्थिर व्योम *buf, माप_प्रकार buflen);
माप_प्रकार sg_copy_to_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			 व्योम *buf, माप_प्रकार buflen);

माप_प्रकार sg_pcopy_from_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			    स्थिर व्योम *buf, माप_प्रकार buflen, off_t skip);
माप_प्रकार sg_pcopy_to_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
			  व्योम *buf, माप_प्रकार buflen, off_t skip);
माप_प्रकार sg_zero_buffer(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
		       माप_प्रकार buflen, off_t skip);

/*
 * Maximum number of entries that will be allocated in one piece, अगर
 * a list larger than this is required then chaining will be utilized.
 */
#घोषणा SG_MAX_SINGLE_ALLOC		(PAGE_SIZE / माप(काष्ठा scatterlist))

/*
 * The maximum number of SG segments that we will put inside a
 * scatterlist (unless chaining is used). Should ideally fit inside a
 * single page, to aव्योम a higher order allocation.  We could define this
 * to SG_MAX_SINGLE_ALLOC to pack correctly at the highest order.  The
 * minimum value is 32
 */
#घोषणा SG_CHUNK_SIZE	128

/*
 * Like SG_CHUNK_SIZE, but क्रम archs that have sg chaining. This limit
 * is totally arbitrary, a setting of 2048 will get you at least 8mb ios.
 */
#अगर_घोषित CONFIG_ARCH_NO_SG_CHAIN
#घोषणा SG_MAX_SEGMENTS	SG_CHUNK_SIZE
#अन्यथा
#घोषणा SG_MAX_SEGMENTS	2048
#पूर्ण_अगर

#अगर_घोषित CONFIG_SG_POOL
व्योम sg_मुक्त_table_chained(काष्ठा sg_table *table,
			   अचिन्हित nents_first_chunk);
पूर्णांक sg_alloc_table_chained(काष्ठा sg_table *table, पूर्णांक nents,
			   काष्ठा scatterlist *first_chunk,
			   अचिन्हित nents_first_chunk);
#पूर्ण_अगर

/*
 * sg page iterator
 *
 * Iterates over sg entries page-by-page.  On each successful iteration, you
 * can call sg_page_iter_page(@piter) to get the current page.
 * @piter->sg will poपूर्णांक to the sg holding this page and @piter->sg_pgoffset to
 * the page's page offset within the sg. The iteration will stop either when a
 * maximum number of sg entries was reached or a terminating sg
 * (sg_last(sg) == true) was reached.
 */
काष्ठा sg_page_iter अणु
	काष्ठा scatterlist	*sg;		/* sg holding the page */
	अचिन्हित पूर्णांक		sg_pgoffset;	/* page offset within the sg */

	/* these are पूर्णांकernal states, keep away */
	अचिन्हित पूर्णांक		__nents;	/* reमुख्यing sg entries */
	पूर्णांक			__pg_advance;	/* nr pages to advance at the
						 * next step */
पूर्ण;

/*
 * sg page iterator क्रम DMA addresses
 *
 * This is the same as sg_page_iter however you can call
 * sg_page_iter_dma_address(@dma_iter) to get the page's DMA
 * address. sg_page_iter_page() cannot be called on this iterator.
 */
काष्ठा sg_dma_page_iter अणु
	काष्ठा sg_page_iter base;
पूर्ण;

bool __sg_page_iter_next(काष्ठा sg_page_iter *piter);
bool __sg_page_iter_dma_next(काष्ठा sg_dma_page_iter *dma_iter);
व्योम __sg_page_iter_start(काष्ठा sg_page_iter *piter,
			  काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक nents,
			  अचिन्हित दीर्घ pgoffset);
/**
 * sg_page_iter_page - get the current page held by the page iterator
 * @piter:	page iterator holding the page
 */
अटल अंतरभूत काष्ठा page *sg_page_iter_page(काष्ठा sg_page_iter *piter)
अणु
	वापस nth_page(sg_page(piter->sg), piter->sg_pgoffset);
पूर्ण

/**
 * sg_page_iter_dma_address - get the dma address of the current page held by
 * the page iterator.
 * @dma_iter:	page iterator holding the page
 */
अटल अंतरभूत dma_addr_t
sg_page_iter_dma_address(काष्ठा sg_dma_page_iter *dma_iter)
अणु
	वापस sg_dma_address(dma_iter->base.sg) +
	       (dma_iter->base.sg_pgoffset << PAGE_SHIFT);
पूर्ण

/**
 * क्रम_each_sg_page - iterate over the pages of the given sg list
 * @sglist:	sglist to iterate over
 * @piter:	page iterator to hold current page, sg, sg_pgoffset
 * @nents:	maximum number of sg entries to iterate over
 * @pgoffset:	starting page offset (in pages)
 *
 * Callers may use sg_page_iter_page() to get each page poपूर्णांकer.
 * In each loop it operates on PAGE_SIZE unit.
 */
#घोषणा क्रम_each_sg_page(sglist, piter, nents, pgoffset)		   \
	क्रम (__sg_page_iter_start((piter), (sglist), (nents), (pgoffset)); \
	     __sg_page_iter_next(piter);)

/**
 * क्रम_each_sg_dma_page - iterate over the pages of the given sg list
 * @sglist:	sglist to iterate over
 * @dma_iter:	DMA page iterator to hold current page
 * @dma_nents:	maximum number of sg entries to iterate over, this is the value
 *              वापसed from dma_map_sg
 * @pgoffset:	starting page offset (in pages)
 *
 * Callers may use sg_page_iter_dma_address() to get each page's DMA address.
 * In each loop it operates on PAGE_SIZE unit.
 */
#घोषणा क्रम_each_sg_dma_page(sglist, dma_iter, dma_nents, pgoffset)            \
	क्रम (__sg_page_iter_start(&(dma_iter)->base, sglist, dma_nents,        \
				  pgoffset);                                   \
	     __sg_page_iter_dma_next(dma_iter);)

/**
 * क्रम_each_sgtable_page - iterate over all pages in the sg_table object
 * @sgt:	sg_table object to iterate over
 * @piter:	page iterator to hold current page
 * @pgoffset:	starting page offset (in pages)
 *
 * Iterates over the all memory pages in the buffer described by
 * a scatterlist stored in the given sg_table object.
 * See also क्रम_each_sg_page(). In each loop it operates on PAGE_SIZE unit.
 */
#घोषणा क्रम_each_sgtable_page(sgt, piter, pgoffset)	\
	क्रम_each_sg_page((sgt)->sgl, piter, (sgt)->orig_nents, pgoffset)

/**
 * क्रम_each_sgtable_dma_page - iterate over the DMA mapped sg_table object
 * @sgt:	sg_table object to iterate over
 * @dma_iter:	DMA page iterator to hold current page
 * @pgoffset:	starting page offset (in pages)
 *
 * Iterates over the all DMA mapped pages in the buffer described by
 * a scatterlist stored in the given sg_table object.
 * See also क्रम_each_sg_dma_page(). In each loop it operates on PAGE_SIZE
 * unit.
 */
#घोषणा क्रम_each_sgtable_dma_page(sgt, dma_iter, pgoffset)	\
	क्रम_each_sg_dma_page((sgt)->sgl, dma_iter, (sgt)->nents, pgoffset)


/*
 * Mapping sg iterator
 *
 * Iterates over sg entries mapping page-by-page.  On each successful
 * iteration, @miter->page poपूर्णांकs to the mapped page and
 * @miter->length bytes of data can be accessed at @miter->addr.  As
 * दीर्घ as an पूर्णांकeration is enबंदd between start and stop, the user
 * is मुक्त to choose control काष्ठाure and when to stop.
 *
 * @miter->consumed is set to @miter->length on each iteration.  It
 * can be adjusted अगर the user can't consume all the bytes in one go.
 * Also, a stopped iteration can be resumed by calling next on it.
 * This is useful when iteration needs to release all resources and
 * जारी later (e.g. at the next पूर्णांकerrupt).
 */

#घोषणा SG_MITER_ATOMIC		(1 << 0)	 /* use kmap_atomic */
#घोषणा SG_MITER_TO_SG		(1 << 1)	/* flush back to phys on unmap */
#घोषणा SG_MITER_FROM_SG	(1 << 2)	/* nop */

काष्ठा sg_mapping_iter अणु
	/* the following three fields can be accessed directly */
	काष्ठा page		*page;		/* currently mapped page */
	व्योम			*addr;		/* poपूर्णांकer to the mapped area */
	माप_प्रकार			length;		/* length of the mapped area */
	माप_प्रकार			consumed;	/* number of consumed bytes */
	काष्ठा sg_page_iter	piter;		/* page iterator */

	/* these are पूर्णांकernal states, keep away */
	अचिन्हित पूर्णांक		__offset;	/* offset within page */
	अचिन्हित पूर्णांक		__reमुख्यing;	/* reमुख्यing bytes on page */
	अचिन्हित पूर्णांक		__flags;
पूर्ण;

व्योम sg_miter_start(काष्ठा sg_mapping_iter *miter, काष्ठा scatterlist *sgl,
		    अचिन्हित पूर्णांक nents, अचिन्हित पूर्णांक flags);
bool sg_miter_skip(काष्ठा sg_mapping_iter *miter, off_t offset);
bool sg_miter_next(काष्ठा sg_mapping_iter *miter);
व्योम sg_miter_stop(काष्ठा sg_mapping_iter *miter);

#पूर्ण_अगर /* _LINUX_SCATTERLIST_H */
