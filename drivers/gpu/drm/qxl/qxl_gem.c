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

#समावेश <drm/drm.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

व्योम qxl_gem_object_मुक्त(काष्ठा drm_gem_object *gobj)
अणु
	काष्ठा qxl_bo *qobj = gem_to_qxl_bo(gobj);
	काष्ठा qxl_device *qdev;
	काष्ठा tपंचांग_buffer_object *tbo;

	qdev = to_qxl(gobj->dev);

	qxl_surface_evict(qdev, qobj, false);

	tbo = &qobj->tbo;
	tपंचांग_bo_put(tbo);
पूर्ण

पूर्णांक qxl_gem_object_create(काष्ठा qxl_device *qdev, पूर्णांक size,
			  पूर्णांक alignment, पूर्णांक initial_करोमुख्य,
			  bool discardable, bool kernel,
			  काष्ठा qxl_surface *surf,
			  काष्ठा drm_gem_object **obj)
अणु
	काष्ठा qxl_bo *qbo;
	पूर्णांक r;

	*obj = शून्य;
	/* At least align on page size */
	अगर (alignment < PAGE_SIZE)
		alignment = PAGE_SIZE;
	r = qxl_bo_create(qdev, size, kernel, false, initial_करोमुख्य, 0, surf, &qbo);
	अगर (r) अणु
		अगर (r != -ERESTARTSYS)
			DRM_ERROR(
			"Failed to allocate GEM object (%d, %d, %u, %d)\n",
				  size, initial_करोमुख्य, alignment, r);
		वापस r;
	पूर्ण
	*obj = &qbo->tbo.base;

	mutex_lock(&qdev->gem.mutex);
	list_add_tail(&qbo->list, &qdev->gem.objects);
	mutex_unlock(&qdev->gem.mutex);

	वापस 0;
पूर्ण

पूर्णांक qxl_gem_object_create_with_handle(काष्ठा qxl_device *qdev,
				      काष्ठा drm_file *file_priv,
				      u32 करोमुख्य,
				      माप_प्रकार size,
				      काष्ठा qxl_surface *surf,
				      काष्ठा qxl_bo **qobj,
				      uपूर्णांक32_t *handle)
अणु
	काष्ठा drm_gem_object *gobj;
	पूर्णांक r;

	BUG_ON(!qobj);
	BUG_ON(!handle);

	r = qxl_gem_object_create(qdev, size, 0,
				  करोमुख्य,
				  false, false, surf,
				  &gobj);
	अगर (r)
		वापस -ENOMEM;
	r = drm_gem_handle_create(file_priv, gobj, handle);
	अगर (r)
		वापस r;
	/* drop reference from allocate - handle holds it now */
	*qobj = gem_to_qxl_bo(gobj);
	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण

पूर्णांक qxl_gem_object_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv)
अणु
	वापस 0;
पूर्ण

व्योम qxl_gem_object_बंद(काष्ठा drm_gem_object *obj,
			  काष्ठा drm_file *file_priv)
अणु
पूर्ण

व्योम qxl_gem_init(काष्ठा qxl_device *qdev)
अणु
	INIT_LIST_HEAD(&qdev->gem.objects);
पूर्ण

व्योम qxl_gem_fini(काष्ठा qxl_device *qdev)
अणु
	qxl_bo_क्रमce_delete(qdev);
पूर्ण
