<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SCATTERLIST_H
#घोषणा SCATTERLIST_H
#समावेश <linux/kernel.h>

काष्ठा scatterlist अणु
	अचिन्हित दीर्घ	page_link;
	अचिन्हित पूर्णांक	offset;
	अचिन्हित पूर्णांक	length;
	dma_addr_t	dma_address;
पूर्ण;

/* Scatterlist helpers, stolen from linux/scatterlist.h */
#घोषणा sg_is_chain(sg)		((sg)->page_link & 0x01)
#घोषणा sg_is_last(sg)		((sg)->page_link & 0x02)
#घोषणा sg_chain_ptr(sg)	\
	((काष्ठा scatterlist *) ((sg)->page_link & ~0x03))

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
	अचिन्हित दीर्घ page_link = sg->page_link & 0x3;

	/*
	 * In order क्रम the low bit stealing approach to work, pages
	 * must be aligned at a 32-bit boundary as a minimum.
	 */
	BUG_ON((अचिन्हित दीर्घ) page & 0x03);
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
	वापस (काष्ठा page *)((sg)->page_link & ~0x3);
पूर्ण

/*
 * Loop over each sg element, following the poपूर्णांकer to a new list अगर necessary
 */
#घोषणा क्रम_each_sg(sglist, sg, nr, __i)	\
	क्रम (__i = 0, sg = (sglist); __i < (nr); __i++, sg = sg_next(sg))

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
	/*
	 * offset and length are unused क्रम chain entry.  Clear them.
	 */
	prv[prv_nents - 1].offset = 0;
	prv[prv_nents - 1].length = 0;

	/*
	 * Set lowest bit to indicate a link poपूर्णांकer, and make sure to clear
	 * the termination bit अगर it happens to be set.
	 */
	prv[prv_nents - 1].page_link = ((अचिन्हित दीर्घ) sgl | 0x01) & ~0x02;
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
	sg->page_link |= 0x02;
	sg->page_link &= ~0x01;
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
	sg->page_link &= ~0x02;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *sg_next(काष्ठा scatterlist *sg)
अणु
	अगर (sg_is_last(sg))
		वापस शून्य;

	sg++;
	अगर (unlikely(sg_is_chain(sg)))
		sg = sg_chain_ptr(sg);

	वापस sg;
पूर्ण

अटल अंतरभूत व्योम sg_init_table(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents)
अणु
	स_रखो(sgl, 0, माप(*sgl) * nents);
	sg_mark_end(&sgl[nents - 1]);
पूर्ण

अटल अंतरभूत dma_addr_t sg_phys(काष्ठा scatterlist *sg)
अणु
	वापस page_to_phys(sg_page(sg)) + sg->offset;
पूर्ण

अटल अंतरभूत व्योम sg_set_buf(काष्ठा scatterlist *sg, स्थिर व्योम *buf,
			      अचिन्हित पूर्णांक buflen)
अणु
	sg_set_page(sg, virt_to_page(buf), buflen, offset_in_page(buf));
पूर्ण

अटल अंतरभूत व्योम sg_init_one(काष्ठा scatterlist *sg,
			       स्थिर व्योम *buf, अचिन्हित पूर्णांक buflen)
अणु
	sg_init_table(sg, 1);
	sg_set_buf(sg, buf, buflen);
पूर्ण
#पूर्ण_अगर /* SCATTERLIST_H */
