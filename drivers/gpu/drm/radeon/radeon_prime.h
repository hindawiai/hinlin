<शैली गुरु>
/* radeon_prime.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __RADEON_PRIME_H__
#घोषणा __RADEON_PRIME_H__

काष्ठा dma_buf *radeon_gem_prime_export(काष्ठा drm_gem_object *gobj,
					पूर्णांक flags);
काष्ठा sg_table *radeon_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
पूर्णांक radeon_gem_prime_pin(काष्ठा drm_gem_object *obj);
व्योम radeon_gem_prime_unpin(काष्ठा drm_gem_object *obj);
व्योम *radeon_gem_prime_vmap(काष्ठा drm_gem_object *obj);
व्योम radeon_gem_prime_vunmap(काष्ठा drm_gem_object *obj, व्योम *vaddr);
काष्ठा drm_gem_object *radeon_gem_prime_import_sg_table(काष्ठा drm_device *dev,
							काष्ठा dma_buf_attachment *,
							काष्ठा sg_table *sg);

#पूर्ण_अगर				/* __RADEON_PRIME_H__ */
