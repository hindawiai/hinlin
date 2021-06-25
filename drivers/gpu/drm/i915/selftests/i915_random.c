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

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "i915_random.h"
#समावेश "i915_utils.h"

u64 i915_pअक्रमom_u64_state(काष्ठा rnd_state *rnd)
अणु
	u64 x;

	x = pअक्रमom_u32_state(rnd);
	x <<= 32;
	x |= pअक्रमom_u32_state(rnd);

	वापस x;
पूर्ण

व्योम i915_pअक्रमom_shuffle(व्योम *arr, माप_प्रकार elsz, माप_प्रकार count,
			  काष्ठा rnd_state *state)
अणु
	अक्षर stack[128];

	अगर (WARN_ON(elsz > माप(stack) || count > U32_MAX))
		वापस;

	अगर (!elsz || !count)
		वापस;

	/* Fisher-Yates shuffle courtesy of Knuth */
	जबतक (--count) अणु
		माप_प्रकार swp;

		swp = i915_pअक्रमom_u32_max_state(count + 1, state);
		अगर (swp == count)
			जारी;

		स_नकल(stack, arr + count * elsz, elsz);
		स_नकल(arr + count * elsz, arr + swp * elsz, elsz);
		स_नकल(arr + swp * elsz, stack, elsz);
	पूर्ण
पूर्ण

व्योम i915_अक्रमom_reorder(अचिन्हित पूर्णांक *order, अचिन्हित पूर्णांक count,
			 काष्ठा rnd_state *state)
अणु
	i915_pअक्रमom_shuffle(order, माप(*order), count, state);
पूर्ण

अचिन्हित पूर्णांक *i915_अक्रमom_order(अचिन्हित पूर्णांक count, काष्ठा rnd_state *state)
अणु
	अचिन्हित पूर्णांक *order, i;

	order = kदो_स्मृति_array(count, माप(*order),
			      GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (!order)
		वापस order;

	क्रम (i = 0; i < count; i++)
		order[i] = i;

	i915_अक्रमom_reorder(order, count, state);
	वापस order;
पूर्ण

u64 igt_अक्रमom_offset(काष्ठा rnd_state *state,
		      u64 start, u64 end,
		      u64 len, u64 align)
अणु
	u64 range, addr;

	BUG_ON(range_overflows(start, len, end));
	BUG_ON(round_up(start, align) > round_करोwn(end - len, align));

	range = round_करोwn(end - len, align) - round_up(start, align);
	अगर (range) अणु
		addr = i915_pअक्रमom_u64_state(state);
		भाग64_u64_rem(addr, range, &addr);
		start += addr;
	पूर्ण

	वापस round_up(start, align);
पूर्ण
