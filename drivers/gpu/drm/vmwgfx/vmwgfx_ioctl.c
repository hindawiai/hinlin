<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश "vmwgfx_drv.h"
#समावेश <drm/vmwgfx_drm.h>
#समावेश "vmwgfx_kms.h"
#समावेश "device_include/svga3d_caps.h"

काष्ठा svga_3d_compat_cap अणु
	SVGA3dCapsRecordHeader header;
	SVGA3dCapPair pairs[SVGA3D_DEVCAP_MAX];
पूर्ण;

पूर्णांक vmw_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_vmw_getparam_arg *param =
	    (काष्ठा drm_vmw_getparam_arg *)data;
	काष्ठा vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);

	चयन (param->param) अणु
	हाल DRM_VMW_PARAM_NUM_STREAMS:
		param->value = vmw_overlay_num_overlays(dev_priv);
		अवरोध;
	हाल DRM_VMW_PARAM_NUM_FREE_STREAMS:
		param->value = vmw_overlay_num_मुक्त_overlays(dev_priv);
		अवरोध;
	हाल DRM_VMW_PARAM_3D:
		param->value = vmw_supports_3d(dev_priv) ? 1 : 0;
		अवरोध;
	हाल DRM_VMW_PARAM_HW_CAPS:
		param->value = dev_priv->capabilities;
		अवरोध;
	हाल DRM_VMW_PARAM_HW_CAPS2:
		param->value = dev_priv->capabilities2;
		अवरोध;
	हाल DRM_VMW_PARAM_FIFO_CAPS:
		param->value = dev_priv->fअगरo.capabilities;
		अवरोध;
	हाल DRM_VMW_PARAM_MAX_FB_SIZE:
		param->value = dev_priv->prim_bb_mem;
		अवरोध;
	हाल DRM_VMW_PARAM_FIFO_HW_VERSION:
	अणु
		स्थिर काष्ठा vmw_fअगरo_state *fअगरo = &dev_priv->fअगरo;

		अगर ((dev_priv->capabilities & SVGA_CAP_GBOBJECTS)) अणु
			param->value = SVGA3D_HWVERSION_WS8_B1;
			अवरोध;
		पूर्ण

		param->value =
			vmw_fअगरo_mem_पढ़ो(dev_priv,
					  ((fअगरo->capabilities &
					    SVGA_FIFO_CAP_3D_HWVERSION_REVISED) ?
						   SVGA_FIFO_3D_HWVERSION_REVISED :
						   SVGA_FIFO_3D_HWVERSION));
		अवरोध;
	पूर्ण
	हाल DRM_VMW_PARAM_MAX_SURF_MEMORY:
		अगर ((dev_priv->capabilities & SVGA_CAP_GBOBJECTS) &&
		    !vmw_fp->gb_aware)
			param->value = dev_priv->max_mob_pages * PAGE_SIZE / 2;
		अन्यथा
			param->value = dev_priv->memory_size;
		अवरोध;
	हाल DRM_VMW_PARAM_3D_CAPS_SIZE:
		अगर ((dev_priv->capabilities & SVGA_CAP_GBOBJECTS) &&
		    vmw_fp->gb_aware)
			param->value = SVGA3D_DEVCAP_MAX * माप(uपूर्णांक32_t);
		अन्यथा अगर (dev_priv->capabilities & SVGA_CAP_GBOBJECTS)
			param->value = माप(काष्ठा svga_3d_compat_cap) +
				माप(uपूर्णांक32_t);
		अन्यथा
			param->value = (SVGA_FIFO_3D_CAPS_LAST -
					SVGA_FIFO_3D_CAPS + 1) *
				माप(uपूर्णांक32_t);
		अवरोध;
	हाल DRM_VMW_PARAM_MAX_MOB_MEMORY:
		vmw_fp->gb_aware = true;
		param->value = dev_priv->max_mob_pages * PAGE_SIZE;
		अवरोध;
	हाल DRM_VMW_PARAM_MAX_MOB_SIZE:
		param->value = dev_priv->max_mob_size;
		अवरोध;
	हाल DRM_VMW_PARAM_SCREEN_TARGET:
		param->value =
			(dev_priv->active_display_unit == vmw_du_screen_target);
		अवरोध;
	हाल DRM_VMW_PARAM_DX:
		param->value = has_sm4_context(dev_priv);
		अवरोध;
	हाल DRM_VMW_PARAM_SM4_1:
		param->value = has_sm4_1_context(dev_priv);
		अवरोध;
	हाल DRM_VMW_PARAM_SM5:
		param->value = has_sm5_context(dev_priv);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 vmw_mask_legacy_multisample(अचिन्हित पूर्णांक cap, u32 fmt_value)
अणु
	/*
	 * A version of user-space exists which use MULTISAMPLE_MASKABLESAMPLES
	 * to check the sample count supported by भव device. Since there
	 * never was support क्रम multisample count क्रम backing MOB वापस 0.
	 *
	 * MULTISAMPLE_MASKABLESAMPLES devcap is marked as deprecated by भव
	 * device.
	 */
	अगर (cap == SVGA3D_DEVCAP_DEAD5)
		वापस 0;

	वापस fmt_value;
पूर्ण

अटल पूर्णांक vmw_fill_compat_cap(काष्ठा vmw_निजी *dev_priv, व्योम *bounce,
			       माप_प्रकार size)
अणु
	काष्ठा svga_3d_compat_cap *compat_cap =
		(काष्ठा svga_3d_compat_cap *) bounce;
	अचिन्हित पूर्णांक i;
	माप_प्रकार pair_offset = दुरत्व(काष्ठा svga_3d_compat_cap, pairs);
	अचिन्हित पूर्णांक max_size;

	अगर (size < pair_offset)
		वापस -EINVAL;

	max_size = (size - pair_offset) / माप(SVGA3dCapPair);

	अगर (max_size > SVGA3D_DEVCAP_MAX)
		max_size = SVGA3D_DEVCAP_MAX;

	compat_cap->header.length =
		(pair_offset + max_size * माप(SVGA3dCapPair)) / माप(u32);
	compat_cap->header.type = SVGA3DCAPS_RECORD_DEVCAPS;

	spin_lock(&dev_priv->cap_lock);
	क्रम (i = 0; i < max_size; ++i) अणु
		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, i);
		compat_cap->pairs[i][0] = i;
		compat_cap->pairs[i][1] = vmw_mask_legacy_multisample
			(i, vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP));
	पूर्ण
	spin_unlock(&dev_priv->cap_lock);

	वापस 0;
पूर्ण


पूर्णांक vmw_get_cap_3d_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_get_3d_cap_arg *arg =
		(काष्ठा drm_vmw_get_3d_cap_arg *) data;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	uपूर्णांक32_t size;
	u32 *fअगरo_mem;
	व्योम __user *buffer = (व्योम __user *)((अचिन्हित दीर्घ)(arg->buffer));
	व्योम *bounce;
	पूर्णांक ret;
	bool gb_objects = !!(dev_priv->capabilities & SVGA_CAP_GBOBJECTS);
	काष्ठा vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);

	अगर (unlikely(arg->pad64 != 0 || arg->max_size == 0)) अणु
		VMW_DEBUG_USER("Illegal GET_3D_CAP argument.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gb_objects && vmw_fp->gb_aware)
		size = SVGA3D_DEVCAP_MAX * माप(uपूर्णांक32_t);
	अन्यथा अगर (gb_objects)
		size = माप(काष्ठा svga_3d_compat_cap) + माप(uपूर्णांक32_t);
	अन्यथा
		size = (SVGA_FIFO_3D_CAPS_LAST - SVGA_FIFO_3D_CAPS + 1) *
			माप(uपूर्णांक32_t);

	अगर (arg->max_size < size)
		size = arg->max_size;

	bounce = vzalloc(size);
	अगर (unlikely(bounce == शून्य)) अणु
		DRM_ERROR("Failed to allocate bounce buffer for 3D caps.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (gb_objects && vmw_fp->gb_aware) अणु
		पूर्णांक i, num;
		uपूर्णांक32_t *bounce32 = (uपूर्णांक32_t *) bounce;

		num = size / माप(uपूर्णांक32_t);
		अगर (num > SVGA3D_DEVCAP_MAX)
			num = SVGA3D_DEVCAP_MAX;

		spin_lock(&dev_priv->cap_lock);
		क्रम (i = 0; i < num; ++i) अणु
			vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, i);
			*bounce32++ = vmw_mask_legacy_multisample
				(i, vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP));
		पूर्ण
		spin_unlock(&dev_priv->cap_lock);
	पूर्ण अन्यथा अगर (gb_objects) अणु
		ret = vmw_fill_compat_cap(dev_priv, bounce, size);
		अगर (unlikely(ret != 0))
			जाओ out_err;
	पूर्ण अन्यथा अणु
		fअगरo_mem = dev_priv->fअगरo_mem;
		स_नकल(bounce, &fअगरo_mem[SVGA_FIFO_3D_CAPS], size);
	पूर्ण

	ret = copy_to_user(buffer, bounce, size);
	अगर (ret)
		ret = -EFAULT;
out_err:
	vमुक्त(bounce);

	अगर (unlikely(ret != 0))
		DRM_ERROR("Failed to report 3D caps info.\n");

	वापस ret;
पूर्ण

पूर्णांक vmw_present_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_vmw_present_arg *arg =
		(काष्ठा drm_vmw_present_arg *)data;
	काष्ठा vmw_surface *surface;
	काष्ठा drm_vmw_rect __user *clips_ptr;
	काष्ठा drm_vmw_rect *clips = शून्य;
	काष्ठा drm_framebuffer *fb;
	काष्ठा vmw_framebuffer *vfb;
	काष्ठा vmw_resource *res;
	uपूर्णांक32_t num_clips;
	पूर्णांक ret;

	num_clips = arg->num_clips;
	clips_ptr = (काष्ठा drm_vmw_rect __user *)(अचिन्हित दीर्घ)arg->clips_ptr;

	अगर (unlikely(num_clips == 0))
		वापस 0;

	अगर (clips_ptr == शून्य) अणु
		VMW_DEBUG_USER("Variable clips_ptr must be specified.\n");
		ret = -EINVAL;
		जाओ out_clips;
	पूर्ण

	clips = kसुस्मृति(num_clips, माप(*clips), GFP_KERNEL);
	अगर (clips == शून्य) अणु
		DRM_ERROR("Failed to allocate clip rect list.\n");
		ret = -ENOMEM;
		जाओ out_clips;
	पूर्ण

	ret = copy_from_user(clips, clips_ptr, num_clips * माप(*clips));
	अगर (ret) अणु
		DRM_ERROR("Failed to copy clip rects from userspace.\n");
		ret = -EFAULT;
		जाओ out_no_copy;
	पूर्ण

	drm_modeset_lock_all(dev);

	fb = drm_framebuffer_lookup(dev, file_priv, arg->fb_id);
	अगर (!fb) अणु
		VMW_DEBUG_USER("Invalid framebuffer id.\n");
		ret = -ENOENT;
		जाओ out_no_fb;
	पूर्ण
	vfb = vmw_framebuffer_to_vfb(fb);

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		जाओ out_no_tपंचांग_lock;

	ret = vmw_user_resource_lookup_handle(dev_priv, tfile, arg->sid,
					      user_surface_converter,
					      &res);
	अगर (ret)
		जाओ out_no_surface;

	surface = vmw_res_to_srf(res);
	ret = vmw_kms_present(dev_priv, file_priv,
			      vfb, surface, arg->sid,
			      arg->dest_x, arg->dest_y,
			      clips, num_clips);

	/* vmw_user_surface_lookup takes one ref so करोes new_fb */
	vmw_surface_unreference(&surface);

out_no_surface:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
out_no_tपंचांग_lock:
	drm_framebuffer_put(fb);
out_no_fb:
	drm_modeset_unlock_all(dev);
out_no_copy:
	kमुक्त(clips);
out_clips:
	वापस ret;
पूर्ण

पूर्णांक vmw_present_पढ़ोback_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_vmw_present_पढ़ोback_arg *arg =
		(काष्ठा drm_vmw_present_पढ़ोback_arg *)data;
	काष्ठा drm_vmw_fence_rep __user *user_fence_rep =
		(काष्ठा drm_vmw_fence_rep __user *)
		(अचिन्हित दीर्घ)arg->fence_rep;
	काष्ठा drm_vmw_rect __user *clips_ptr;
	काष्ठा drm_vmw_rect *clips = शून्य;
	काष्ठा drm_framebuffer *fb;
	काष्ठा vmw_framebuffer *vfb;
	uपूर्णांक32_t num_clips;
	पूर्णांक ret;

	num_clips = arg->num_clips;
	clips_ptr = (काष्ठा drm_vmw_rect __user *)(अचिन्हित दीर्घ)arg->clips_ptr;

	अगर (unlikely(num_clips == 0))
		वापस 0;

	अगर (clips_ptr == शून्य) अणु
		VMW_DEBUG_USER("Argument clips_ptr must be specified.\n");
		ret = -EINVAL;
		जाओ out_clips;
	पूर्ण

	clips = kसुस्मृति(num_clips, माप(*clips), GFP_KERNEL);
	अगर (clips == शून्य) अणु
		DRM_ERROR("Failed to allocate clip rect list.\n");
		ret = -ENOMEM;
		जाओ out_clips;
	पूर्ण

	ret = copy_from_user(clips, clips_ptr, num_clips * माप(*clips));
	अगर (ret) अणु
		DRM_ERROR("Failed to copy clip rects from userspace.\n");
		ret = -EFAULT;
		जाओ out_no_copy;
	पूर्ण

	drm_modeset_lock_all(dev);

	fb = drm_framebuffer_lookup(dev, file_priv, arg->fb_id);
	अगर (!fb) अणु
		VMW_DEBUG_USER("Invalid framebuffer id.\n");
		ret = -ENOENT;
		जाओ out_no_fb;
	पूर्ण

	vfb = vmw_framebuffer_to_vfb(fb);
	अगर (!vfb->bo) अणु
		VMW_DEBUG_USER("Framebuffer not buffer backed.\n");
		ret = -EINVAL;
		जाओ out_no_tपंचांग_lock;
	पूर्ण

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		जाओ out_no_tपंचांग_lock;

	ret = vmw_kms_पढ़ोback(dev_priv, file_priv,
			       vfb, user_fence_rep,
			       clips, num_clips);

	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
out_no_tपंचांग_lock:
	drm_framebuffer_put(fb);
out_no_fb:
	drm_modeset_unlock_all(dev);
out_no_copy:
	kमुक्त(clips);
out_clips:
	वापस ret;
पूर्ण


/**
 * vmw_fops_poll - wrapper around the drm_poll function
 *
 * @filp: See the linux fops poll करोcumentation.
 * @रुको: See the linux fops poll करोcumentation.
 *
 * Wrapper around the drm_poll function that makes sure the device is
 * processing the fअगरo अगर drm_poll decides to रुको.
 */
__poll_t vmw_fops_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा vmw_निजी *dev_priv =
		vmw_priv(file_priv->minor->dev);

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
	वापस drm_poll(filp, रुको);
पूर्ण


/**
 * vmw_fops_पढ़ो - wrapper around the drm_पढ़ो function
 *
 * @filp: See the linux fops पढ़ो करोcumentation.
 * @buffer: See the linux fops पढ़ो करोcumentation.
 * @count: See the linux fops पढ़ो करोcumentation.
 * @offset: See the linux fops पढ़ो करोcumentation.
 *
 * Wrapper around the drm_पढ़ो function that makes sure the device is
 * processing the fअगरo अगर drm_पढ़ो decides to रुको.
 */
sमाप_प्रकार vmw_fops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
		      माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा vmw_निजी *dev_priv =
		vmw_priv(file_priv->minor->dev);

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
	वापस drm_पढ़ो(filp, buffer, count, offset);
पूर्ण
