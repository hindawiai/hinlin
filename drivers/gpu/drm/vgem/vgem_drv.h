<शैली गुरु>
/*
 * Copyright तऊ 2012 Intel Corporation
 * Copyright तऊ 2014 The Chromium OS Authors
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
 * Authors:
 *    Ben Widawsky <ben@bwidawsk.net>
 *
 */

#अगर_अघोषित _VGEM_DRV_H_
#घोषणा _VGEM_DRV_H_

#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_cache.h>

#समावेश <uapi/drm/vgem_drm.h>

काष्ठा vgem_file अणु
	काष्ठा idr fence_idr;
	काष्ठा mutex fence_mutex;
पूर्ण;

#घोषणा to_vgem_bo(x) container_of(x, काष्ठा drm_vgem_gem_object, base)
काष्ठा drm_vgem_gem_object अणु
	काष्ठा drm_gem_object base;

	काष्ठा page **pages;
	अचिन्हित पूर्णांक pages_pin_count;
	काष्ठा mutex pages_lock;

	काष्ठा sg_table *table;
पूर्ण;

पूर्णांक vgem_fence_खोलो(काष्ठा vgem_file *file);
पूर्णांक vgem_fence_attach_ioctl(काष्ठा drm_device *dev,
			    व्योम *data,
			    काष्ठा drm_file *file);
पूर्णांक vgem_fence_संकेत_ioctl(काष्ठा drm_device *dev,
			    व्योम *data,
			    काष्ठा drm_file *file);
व्योम vgem_fence_बंद(काष्ठा vgem_file *file);

#पूर्ण_अगर
