<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __I915_SELFTESTS_RANDOM_H__
#घोषणा __I915_SELFTESTS_RANDOM_H__

#समावेश <linux/math64.h>
#समावेश <linux/अक्रमom.h>

#समावेश "../i915_selftest.h"

#घोषणा I915_RND_STATE_INITIALIZER(x) (अणु				\
	काष्ठा rnd_state state__;					\
	pअक्रमom_seed_state(&state__, (x));				\
	state__;							\
पूर्ण)

#घोषणा I915_RND_STATE(name__) \
	काष्ठा rnd_state name__ = I915_RND_STATE_INITIALIZER(i915_selftest.अक्रमom_seed)

#घोषणा I915_RND_SUBSTATE(name__, parent__) \
	काष्ठा rnd_state name__ = I915_RND_STATE_INITIALIZER(pअक्रमom_u32_state(&(parent__)))

u64 i915_pअक्रमom_u64_state(काष्ठा rnd_state *rnd);

अटल अंतरभूत u32 i915_pअक्रमom_u32_max_state(u32 ep_ro, काष्ठा rnd_state *state)
अणु
	वापस upper_32_bits(mul_u32_u32(pअक्रमom_u32_state(state), ep_ro));
पूर्ण

अचिन्हित पूर्णांक *i915_अक्रमom_order(अचिन्हित पूर्णांक count,
				काष्ठा rnd_state *state);
व्योम i915_अक्रमom_reorder(अचिन्हित पूर्णांक *order,
			 अचिन्हित पूर्णांक count,
			 काष्ठा rnd_state *state);

व्योम i915_pअक्रमom_shuffle(व्योम *arr, माप_प्रकार elsz, माप_प्रकार count,
			  काष्ठा rnd_state *state);

u64 igt_अक्रमom_offset(काष्ठा rnd_state *state,
		      u64 start, u64 end,
		      u64 len, u64 align);

#पूर्ण_अगर /* !__I915_SELFTESTS_RANDOM_H__ */
