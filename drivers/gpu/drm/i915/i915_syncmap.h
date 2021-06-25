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

#अगर_अघोषित __I915_SYNCMAP_H__
#घोषणा __I915_SYNCMAP_H__

#समावेश <linux/types.h>

काष्ठा i915_syncmap;
#घोषणा KSYNCMAP 16 /* radix of the tree, how many slots in each layer */

व्योम i915_syncmap_init(काष्ठा i915_syncmap **root);
पूर्णांक i915_syncmap_set(काष्ठा i915_syncmap **root, u64 id, u32 seqno);
bool i915_syncmap_is_later(काष्ठा i915_syncmap **root, u64 id, u32 seqno);
व्योम i915_syncmap_मुक्त(काष्ठा i915_syncmap **root);

#पूर्ण_अगर /* __I915_SYNCMAP_H__ */
