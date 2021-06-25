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

#अगर_अघोषित __MOCK_DRM_H
#घोषणा __MOCK_DRM_H

#समावेश <drm/drm_file.h>

#समावेश "i915_drv.h"

काष्ठा drm_file;
काष्ठा file;

अटल अंतरभूत काष्ठा file *mock_file(काष्ठा drm_i915_निजी *i915)
अणु
	वापस mock_drm_getfile(i915->drm.primary, O_RDWR);
पूर्ण

अटल अंतरभूत काष्ठा drm_file *to_drm_file(काष्ठा file *f)
अणु
	वापस f->निजी_data;
पूर्ण

#पूर्ण_अगर /* !__MOCK_DRM_H */
