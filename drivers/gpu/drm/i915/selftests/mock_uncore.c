<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
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

#समावेश "mock_uncore.h"

#घोषणा __nop_ग_लिखो(x) \
अटल व्योम \
nop_ग_लिखो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u##x val, bool trace) अणु पूर्ण
__nop_ग_लिखो(8)
__nop_ग_लिखो(16)
__nop_ग_लिखो(32)

#घोषणा __nop_पढ़ो(x) \
अटल u##x \
nop_पढ़ो##x(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, bool trace) अणु वापस 0; पूर्ण
__nop_पढ़ो(8)
__nop_पढ़ो(16)
__nop_पढ़ो(32)
__nop_पढ़ो(64)

व्योम mock_uncore_init(काष्ठा पूर्णांकel_uncore *uncore,
		      काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_uncore_init_early(uncore, i915);

	ASSIGN_RAW_WRITE_MMIO_VFUNCS(uncore, nop);
	ASSIGN_RAW_READ_MMIO_VFUNCS(uncore, nop);
पूर्ण
