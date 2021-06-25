<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "i915_scatterlist.h"

bool i915_sg_trim(काष्ठा sg_table *orig_st)
अणु
	काष्ठा sg_table new_st;
	काष्ठा scatterlist *sg, *new_sg;
	अचिन्हित पूर्णांक i;

	अगर (orig_st->nents == orig_st->orig_nents)
		वापस false;

	अगर (sg_alloc_table(&new_st, orig_st->nents, GFP_KERNEL | __GFP_NOWARN))
		वापस false;

	new_sg = new_st.sgl;
	क्रम_each_sg(orig_st->sgl, sg, orig_st->nents, i) अणु
		sg_set_page(new_sg, sg_page(sg), sg->length, 0);
		sg_dma_address(new_sg) = sg_dma_address(sg);
		sg_dma_len(new_sg) = sg_dma_len(sg);

		new_sg = sg_next(new_sg);
	पूर्ण
	GEM_BUG_ON(new_sg); /* Should walk exactly nents and hit the end */

	sg_मुक्त_table(orig_st);

	*orig_st = new_st;
	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/scatterlist.c"
#पूर्ण_अगर
