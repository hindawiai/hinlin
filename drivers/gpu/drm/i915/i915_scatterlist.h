<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित I915_SCATTERLIST_H
#घोषणा I915_SCATTERLIST_H

#समावेश <linux/pfn.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/swiotlb.h>

#समावेश "i915_gem.h"

/*
 * Optimised SGL iterator क्रम GEM objects
 */
अटल __always_अंतरभूत काष्ठा sgt_iter अणु
	काष्ठा scatterlist *sgp;
	जोड़ अणु
		अचिन्हित दीर्घ pfn;
		dma_addr_t dma;
	पूर्ण;
	अचिन्हित पूर्णांक curr;
	अचिन्हित पूर्णांक max;
पूर्ण __sgt_iter(काष्ठा scatterlist *sgl, bool dma) अणु
	काष्ठा sgt_iter s = अणु .sgp = sgl पूर्ण;

	अगर (dma && s.sgp && sg_dma_len(s.sgp) == 0) अणु
		s.sgp = शून्य;
	पूर्ण अन्यथा अगर (s.sgp) अणु
		s.max = s.curr = s.sgp->offset;
		अगर (dma) अणु
			s.dma = sg_dma_address(s.sgp);
			s.max += sg_dma_len(s.sgp);
		पूर्ण अन्यथा अणु
			s.pfn = page_to_pfn(sg_page(s.sgp));
			s.max += s.sgp->length;
		पूर्ण
	पूर्ण

	वापस s;
पूर्ण

अटल अंतरभूत पूर्णांक __sg_page_count(स्थिर काष्ठा scatterlist *sg)
अणु
	वापस sg->length >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक __sg_dma_page_count(स्थिर काष्ठा scatterlist *sg)
अणु
	वापस sg_dma_len(sg) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *____sg_next(काष्ठा scatterlist *sg)
अणु
	++sg;
	अगर (unlikely(sg_is_chain(sg)))
		sg = sg_chain_ptr(sg);
	वापस sg;
पूर्ण

/**
 * __sg_next - वापस the next scatterlist entry in a list
 * @sg:		The current sg entry
 *
 * Description:
 *   If the entry is the last, वापस शून्य; otherwise, step to the next
 *   element in the array (@sg@+1). If that's a chain poपूर्णांकer, follow it;
 *   otherwise just वापस the poपूर्णांकer to the current element.
 **/
अटल अंतरभूत काष्ठा scatterlist *__sg_next(काष्ठा scatterlist *sg)
अणु
	वापस sg_is_last(sg) ? शून्य : ____sg_next(sg);
पूर्ण

/**
 * __क्रम_each_sgt_daddr - iterate over the device addresses of the given sg_table
 * @__dp:	Device address (output)
 * @__iter:	'struct sgt_iter' (iterator state, पूर्णांकernal)
 * @__sgt:	sg_table to iterate over (input)
 * @__step:	step size
 */
#घोषणा __क्रम_each_sgt_daddr(__dp, __iter, __sgt, __step)		\
	क्रम ((__iter) = __sgt_iter((__sgt)->sgl, true);			\
	     ((__dp) = (__iter).dma + (__iter).curr), (__iter).sgp;	\
	     (((__iter).curr += (__step)) >= (__iter).max) ?		\
	     (__iter) = __sgt_iter(__sg_next((__iter).sgp), true), 0 : 0)

/**
 * क्रम_each_sgt_page - iterate over the pages of the given sg_table
 * @__pp:	page poपूर्णांकer (output)
 * @__iter:	'struct sgt_iter' (iterator state, पूर्णांकernal)
 * @__sgt:	sg_table to iterate over (input)
 */
#घोषणा क्रम_each_sgt_page(__pp, __iter, __sgt)				\
	क्रम ((__iter) = __sgt_iter((__sgt)->sgl, false);		\
	     ((__pp) = (__iter).pfn == 0 ? शून्य :			\
	      pfn_to_page((__iter).pfn + ((__iter).curr >> PAGE_SHIFT))); \
	     (((__iter).curr += PAGE_SIZE) >= (__iter).max) ?		\
	     (__iter) = __sgt_iter(__sg_next((__iter).sgp), false), 0 : 0)

अटल अंतरभूत अचिन्हित पूर्णांक i915_sg_page_sizes(काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक page_sizes;

	page_sizes = 0;
	जबतक (sg) अणु
		GEM_BUG_ON(sg->offset);
		GEM_BUG_ON(!IS_ALIGNED(sg->length, PAGE_SIZE));
		page_sizes |= sg->length;
		sg = __sg_next(sg);
	पूर्ण

	वापस page_sizes;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक i915_sg_segment_size(व्योम)
अणु
	अचिन्हित पूर्णांक size = swiotlb_max_segment();

	अगर (size == 0)
		size = अच_पूर्णांक_उच्च;

	size = roundकरोwn(size, PAGE_SIZE);
	/* swiotlb_max_segment_size can वापस 1 byte when it means one page. */
	अगर (size < PAGE_SIZE)
		size = PAGE_SIZE;

	वापस size;
पूर्ण

bool i915_sg_trim(काष्ठा sg_table *orig_st);

#पूर्ण_अगर
