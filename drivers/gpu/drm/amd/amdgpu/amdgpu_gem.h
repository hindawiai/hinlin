<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित __AMDGPU_GEM_H__
#घोषणा __AMDGPU_GEM_H__

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_gem.h>

/*
 * GEM.
 */

#घोषणा AMDGPU_GEM_DOMAIN_MAX		0x3
#घोषणा gem_to_amdgpu_bo(gobj) container_of((gobj), काष्ठा amdgpu_bo, tbo.base)

अचिन्हित दीर्घ amdgpu_gem_समयout(uपूर्णांक64_t समयout_ns);

/*
 * GEM objects.
 */
व्योम amdgpu_gem_क्रमce_release(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gem_object_create(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ size,
			     पूर्णांक alignment, u32 initial_करोमुख्य,
			     u64 flags, क्रमागत tपंचांग_bo_type type,
			     काष्ठा dma_resv *resv,
			     काष्ठा drm_gem_object **obj);

पूर्णांक amdgpu_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args);
पूर्णांक amdgpu_mode_dumb_mmap(काष्ठा drm_file *filp,
			  काष्ठा drm_device *dev,
			  uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p);

पूर्णांक amdgpu_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *filp);
पूर्णांक amdgpu_gem_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक amdgpu_gem_userptr_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *filp);
पूर्णांक amdgpu_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक amdgpu_gem_रुको_idle_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *filp);
uपूर्णांक64_t amdgpu_gem_va_map_flags(काष्ठा amdgpu_device *adev, uपूर्णांक32_t flags);
पूर्णांक amdgpu_gem_va_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक amdgpu_gem_op_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *filp);

पूर्णांक amdgpu_gem_metadata_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);

#पूर्ण_अगर
