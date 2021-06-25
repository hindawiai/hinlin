<शैली गुरु>
/*
 * Copyright तऊ 2017 Broadcom
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
 */

#समावेश "vc4_drv.h"

अटल स्थिर अक्षर *vc4_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "vc4";
पूर्ण

अटल स्थिर अक्षर *vc4_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	वापस "vc4-v3d";
पूर्ण

अटल bool vc4_fence_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा vc4_fence *f = to_vc4_fence(fence);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(f->dev);

	वापस vc4->finished_seqno >= f->seqno;
पूर्ण

स्थिर काष्ठा dma_fence_ops vc4_fence_ops = अणु
	.get_driver_name = vc4_fence_get_driver_name,
	.get_समयline_name = vc4_fence_get_समयline_name,
	.संकेतed = vc4_fence_संकेतed,
पूर्ण;
