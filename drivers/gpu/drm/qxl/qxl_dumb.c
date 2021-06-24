<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

/* dumb ioctls implementation */

पूर्णांक qxl_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा qxl_bo *qobj;
	uपूर्णांक32_t handle;
	पूर्णांक r;
	काष्ठा qxl_surface surf;
	uपूर्णांक32_t pitch, क्रमmat;

	pitch = args->width * ((args->bpp + 1) / 8);
	args->size = pitch * args->height;
	args->size = ALIGN(args->size, PAGE_SIZE);

	चयन (args->bpp) अणु
	हाल 16:
		क्रमmat = SPICE_SURFACE_FMT_16_565;
		अवरोध;
	हाल 32:
		क्रमmat = SPICE_SURFACE_FMT_32_xRGB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	surf.width = args->width;
	surf.height = args->height;
	surf.stride = pitch;
	surf.क्रमmat = क्रमmat;
	r = qxl_gem_object_create_with_handle(qdev, file_priv,
					      QXL_GEM_DOMAIN_CPU,
					      args->size, &surf, &qobj,
					      &handle);
	अगर (r)
		वापस r;
	qobj->is_dumb = true;
	args->pitch = pitch;
	args->handle = handle;
	वापस 0;
पूर्ण

पूर्णांक qxl_mode_dumb_mmap(काष्ठा drm_file *file_priv,
		       काष्ठा drm_device *dev,
		       uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा qxl_bo *qobj;

	BUG_ON(!offset_p);
	gobj = drm_gem_object_lookup(file_priv, handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;
	qobj = gem_to_qxl_bo(gobj);
	*offset_p = qxl_bo_mmap_offset(qobj);
	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण
