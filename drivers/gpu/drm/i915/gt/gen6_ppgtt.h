<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __GEN6_PPGTT_H__
#घोषणा __GEN6_PPGTT_H__

#समावेश "intel_gtt.h"

काष्ठा i915_gem_ww_ctx;

काष्ठा gen6_ppgtt अणु
	काष्ठा i915_ppgtt base;

	काष्ठा mutex flush;
	काष्ठा i915_vma *vma;
	gen6_pte_t __iomem *pd_addr;
	u32 pp_dir;

	atomic_t pin_count;
	काष्ठा mutex pin_mutex;

	bool scan_क्रम_unused_pt;
पूर्ण;

अटल अंतरभूत u32 gen6_pte_index(u32 addr)
अणु
	वापस i915_pte_index(addr, GEN6_PDE_SHIFT);
पूर्ण

अटल अंतरभूत u32 gen6_pte_count(u32 addr, u32 length)
अणु
	वापस i915_pte_count(addr, length, GEN6_PDE_SHIFT);
पूर्ण

अटल अंतरभूत u32 gen6_pde_index(u32 addr)
अणु
	वापस i915_pde_index(addr, GEN6_PDE_SHIFT);
पूर्ण

#घोषणा __to_gen6_ppgtt(base) container_of(base, काष्ठा gen6_ppgtt, base)

अटल अंतरभूत काष्ठा gen6_ppgtt *to_gen6_ppgtt(काष्ठा i915_ppgtt *base)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा gen6_ppgtt, base));
	वापस __to_gen6_ppgtt(base);
पूर्ण

/*
 * gen6_क्रम_each_pde() iterates over every pde from start until start+length.
 * If start and start+length are not perfectly भागisible, the macro will round
 * करोwn and up as needed. Start=0 and length=2G effectively iterates over
 * every PDE in the प्रणाली. The macro modअगरies ALL its parameters except 'pd',
 * so each of the other parameters should preferably be a simple variable, or
 * at most an lvalue with no side-effects!
 */
#घोषणा gen6_क्रम_each_pde(pt, pd, start, length, iter)			\
	क्रम (iter = gen6_pde_index(start);				\
	     length > 0 && iter < I915_PDES &&				\
		     (pt = i915_pt_entry(pd, iter), true);		\
	     (अणु u32 temp = ALIGN(start + 1, 1 << GEN6_PDE_SHIFT);	\
		    temp = min(temp - start, length);			\
		    start += temp; length -= temp; पूर्ण), ++iter)

#घोषणा gen6_क्रम_all_pdes(pt, pd, iter)					\
	क्रम (iter = 0;							\
	     iter < I915_PDES &&					\
		     (pt = i915_pt_entry(pd, iter), true);		\
	     ++iter)

पूर्णांक gen6_ppgtt_pin(काष्ठा i915_ppgtt *base, काष्ठा i915_gem_ww_ctx *ww);
व्योम gen6_ppgtt_unpin(काष्ठा i915_ppgtt *base);
व्योम gen6_ppgtt_unpin_all(काष्ठा i915_ppgtt *base);
व्योम gen6_ppgtt_enable(काष्ठा पूर्णांकel_gt *gt);
व्योम gen7_ppgtt_enable(काष्ठा पूर्णांकel_gt *gt);
काष्ठा i915_ppgtt *gen6_ppgtt_create(काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर
