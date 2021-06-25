<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/prefetch.h>

/**
 * iommu_fill_pdir - Insert coalesced scatter/gather chunks पूर्णांकo the I/O Pdir.
 * @ioc: The I/O Controller.
 * @startsg: The scatter/gather list of coalesced chunks.
 * @nents: The number of entries in the scatter/gather list.
 * @hपूर्णांक: The DMA Hपूर्णांक.
 *
 * This function inserts the coalesced scatter/gather list chunks पूर्णांकo the
 * I/O Controller's I/O Pdir.
 */ 
अटल अंतरभूत अचिन्हित पूर्णांक
iommu_fill_pdir(काष्ठा ioc *ioc, काष्ठा scatterlist *startsg, पूर्णांक nents, 
		अचिन्हित दीर्घ hपूर्णांक,
		व्योम (*iommu_io_pdir_entry)(u64 *, space_t, अचिन्हित दीर्घ,
					    अचिन्हित दीर्घ))
अणु
	काष्ठा scatterlist *dma_sg = startsg;	/* poपूर्णांकer to current DMA */
	अचिन्हित पूर्णांक n_mappings = 0;
	अचिन्हित दीर्घ dma_offset = 0, dma_len = 0;
	u64 *pdirp = शून्य;

	/* Horrible hack.  For efficiency's sake, dma_sg starts one 
	 * entry below the true start (it is immediately incremented
	 * in the loop) */
	 dma_sg--;

	जबतक (nents-- > 0) अणु
		अचिन्हित दीर्घ vaddr;
		दीर्घ size;

		DBG_RUN_SG(" %d : %08lx/%05x %p/%05x\n", nents,
			   (अचिन्हित दीर्घ)sg_dma_address(startsg), cnt,
			   sg_virt(startsg), startsg->length
		);


		/*
		** Look क्रम the start of a new DMA stream
		*/
		
		अगर (sg_dma_address(startsg) & PIDE_FLAG) अणु
			u32 pide = sg_dma_address(startsg) & ~PIDE_FLAG;

			BUG_ON(pdirp && (dma_len != sg_dma_len(dma_sg)));

			dma_sg++;

			dma_len = sg_dma_len(startsg);
			sg_dma_len(startsg) = 0;
			dma_offset = (अचिन्हित दीर्घ) pide & ~IOVP_MASK;
			n_mappings++;
#अगर defined(ZX1_SUPPORT)
			/* Pluto IOMMU IO Virt Address is not zero based */
			sg_dma_address(dma_sg) = pide | ioc->ibase;
#अन्यथा
			/* SBA, ccio, and dino are zero based.
			 * Trying to save a few CPU cycles क्रम most users.
			 */
			sg_dma_address(dma_sg) = pide;
#पूर्ण_अगर
			pdirp = &(ioc->pdir_base[pide >> IOVP_SHIFT]);
			prefetchw(pdirp);
		पूर्ण
		
		BUG_ON(pdirp == शून्य);
		
		vaddr = (अचिन्हित दीर्घ)sg_virt(startsg);
		sg_dma_len(dma_sg) += startsg->length;
		size = startsg->length + dma_offset;
		dma_offset = 0;
#अगर_घोषित IOMMU_MAP_STATS
		ioc->msg_pages += startsg->length >> IOVP_SHIFT;
#पूर्ण_अगर
		करो अणु
			iommu_io_pdir_entry(pdirp, KERNEL_SPACE, 
					    vaddr, hपूर्णांक);
			vaddr += IOVP_SIZE;
			size -= IOVP_SIZE;
			pdirp++;
		पूर्ण जबतक(unlikely(size > 0));
		startsg++;
	पूर्ण
	वापस(n_mappings);
पूर्ण


/*
** First pass is to walk the SG list and determine where the अवरोधs are
** in the DMA stream. Allocates Pसूची entries but करोes not fill them.
** Returns the number of DMA chunks.
**
** Doing the fill separate from the coalescing/allocation keeps the
** code simpler. Future enhancement could make one pass through
** the sglist करो both.
*/

अटल अंतरभूत अचिन्हित पूर्णांक
iommu_coalesce_chunks(काष्ठा ioc *ioc, काष्ठा device *dev,
		काष्ठा scatterlist *startsg, पूर्णांक nents,
		पूर्णांक (*iommu_alloc_range)(काष्ठा ioc *, काष्ठा device *, माप_प्रकार))
अणु
	काष्ठा scatterlist *contig_sg;	   /* contig chunk head */
	अचिन्हित दीर्घ dma_offset, dma_len; /* start/len of DMA stream */
	अचिन्हित पूर्णांक n_mappings = 0;
	अचिन्हित पूर्णांक max_seg_size = min(dma_get_max_seg_size(dev),
					(अचिन्हित)DMA_CHUNK_SIZE);
	अचिन्हित पूर्णांक max_seg_boundary = dma_get_seg_boundary(dev) + 1;
	अगर (max_seg_boundary)	/* check अगर the addition above didn't overflow */
		max_seg_size = min(max_seg_size, max_seg_boundary);

	जबतक (nents > 0) अणु

		/*
		** Prepare क्रम first/next DMA stream
		*/
		contig_sg = startsg;
		dma_len = startsg->length;
		dma_offset = startsg->offset;

		/* PARANOID: clear entries */
		sg_dma_address(startsg) = 0;
		sg_dma_len(startsg) = 0;

		/*
		** This loop terminates one iteration "early" since
		** it's always looking one "ahead".
		*/
		जबतक(--nents > 0) अणु
			अचिन्हित दीर्घ prev_end, sg_start;

			prev_end = (अचिन्हित दीर्घ)sg_virt(startsg) +
							startsg->length;

			startsg++;
			sg_start = (अचिन्हित दीर्घ)sg_virt(startsg);

			/* PARANOID: clear entries */
			sg_dma_address(startsg) = 0;
			sg_dma_len(startsg) = 0;

			/*
			** First make sure current dma stream won't
			** exceed max_seg_size अगर we coalesce the
			** next entry.
			*/   
			अगर (unlikely(ALIGN(dma_len + dma_offset + startsg->length, IOVP_SIZE) >
				     max_seg_size))
				अवरोध;

			/*
			* Next see अगर we can append the next chunk (i.e.
			* it must end on one page and begin on another, or
			* it must start on the same address as the previous
			* entry ended.
			*/
			अगर (unlikely((prev_end != sg_start) ||
				((prev_end | sg_start) & ~PAGE_MASK)))
				अवरोध;
			
			dma_len += startsg->length;
		पूर्ण

		/*
		** End of DMA Stream
		** Terminate last VCONTIG block.
		** Allocate space क्रम DMA stream.
		*/
		sg_dma_len(contig_sg) = dma_len;
		dma_len = ALIGN(dma_len + dma_offset, IOVP_SIZE);
		sg_dma_address(contig_sg) =
			PIDE_FLAG 
			| (iommu_alloc_range(ioc, dev, dma_len) << IOVP_SHIFT)
			| dma_offset;
		n_mappings++;
	पूर्ण

	वापस n_mappings;
पूर्ण

