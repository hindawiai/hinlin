<शैली गुरु>
/*
 * Copyright तऊ 2007 David Airlie
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *     David Airlie
 */

#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "amdgpu.h"
#समावेश "cikd.h"
#समावेश "amdgpu_gem.h"

#समावेश "amdgpu_display.h"

/* object hierarchy -
   this contains a helper + a amdgpu fb
   the helper contains a poपूर्णांकer to amdgpu framebuffer baseclass.
*/

अटल पूर्णांक
amdgpufb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	पूर्णांक ret = pm_runसमय_get_sync(fb_helper->dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_mark_last_busy(fb_helper->dev->dev);
		pm_runसमय_put_स्वतःsuspend(fb_helper->dev->dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
amdgpufb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;

	pm_runसमय_mark_last_busy(fb_helper->dev->dev);
	pm_runसमय_put_स्वतःsuspend(fb_helper->dev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops amdgpufb_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_खोलो = amdgpufb_खोलो,
	.fb_release = amdgpufb_release,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
पूर्ण;


पूर्णांक amdgpu_align_pitch(काष्ठा amdgpu_device *adev, पूर्णांक width, पूर्णांक cpp, bool tiled)
अणु
	पूर्णांक aligned = width;
	पूर्णांक pitch_mask = 0;

	चयन (cpp) अणु
	हाल 1:
		pitch_mask = 255;
		अवरोध;
	हाल 2:
		pitch_mask = 127;
		अवरोध;
	हाल 3:
	हाल 4:
		pitch_mask = 63;
		अवरोध;
	पूर्ण

	aligned += pitch_mask;
	aligned &= ~pitch_mask;
	वापस aligned * cpp;
पूर्ण

अटल व्योम amdgpufb_destroy_pinned_object(काष्ठा drm_gem_object *gobj)
अणु
	काष्ठा amdgpu_bo *abo = gem_to_amdgpu_bo(gobj);
	पूर्णांक ret;

	ret = amdgpu_bo_reserve(abo, true);
	अगर (likely(ret == 0)) अणु
		amdgpu_bo_kunmap(abo);
		amdgpu_bo_unpin(abo);
		amdgpu_bo_unreserve(abo);
	पूर्ण
	drm_gem_object_put(gobj);
पूर्ण

अटल पूर्णांक amdgpufb_create_pinned_object(काष्ठा amdgpu_fbdev *rfbdev,
					 काष्ठा drm_mode_fb_cmd2 *mode_cmd,
					 काष्ठा drm_gem_object **gobj_p)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	काष्ठा amdgpu_device *adev = rfbdev->adev;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा amdgpu_bo *abo = शून्य;
	bool fb_tiled = false; /* useful क्रम testing */
	u32 tiling_flags = 0, करोमुख्य;
	पूर्णांक ret;
	पूर्णांक aligned_size, size;
	पूर्णांक height = mode_cmd->height;
	u32 cpp;
	u64 flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
			       AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS     |
			       AMDGPU_GEM_CREATE_VRAM_CLEARED;

	info = drm_get_क्रमmat_info(adev_to_drm(adev), mode_cmd);
	cpp = info->cpp[0];

	/* need to align pitch with crtc limits */
	mode_cmd->pitches[0] = amdgpu_align_pitch(adev, mode_cmd->width, cpp,
						  fb_tiled);
	करोमुख्य = amdgpu_display_supported_करोमुख्यs(adev, flags);
	height = ALIGN(mode_cmd->height, 8);
	size = mode_cmd->pitches[0] * height;
	aligned_size = ALIGN(size, PAGE_SIZE);
	ret = amdgpu_gem_object_create(adev, aligned_size, 0, करोमुख्य, flags,
				       tपंचांग_bo_type_device, शून्य, &gobj);
	अगर (ret) अणु
		pr_err("failed to allocate framebuffer (%d)\n", aligned_size);
		वापस -ENOMEM;
	पूर्ण
	abo = gem_to_amdgpu_bo(gobj);

	अगर (fb_tiled)
		tiling_flags = AMDGPU_TILING_SET(ARRAY_MODE, GRPH_ARRAY_2D_TILED_THIN1);

	ret = amdgpu_bo_reserve(abo, false);
	अगर (unlikely(ret != 0))
		जाओ out_unref;

	अगर (tiling_flags) अणु
		ret = amdgpu_bo_set_tiling_flags(abo,
						 tiling_flags);
		अगर (ret)
			dev_err(adev->dev, "FB failed to set tiling flags\n");
	पूर्ण

	ret = amdgpu_bo_pin(abo, करोमुख्य);
	अगर (ret) अणु
		amdgpu_bo_unreserve(abo);
		जाओ out_unref;
	पूर्ण

	ret = amdgpu_tपंचांग_alloc_gart(&abo->tbo);
	अगर (ret) अणु
		amdgpu_bo_unreserve(abo);
		dev_err(adev->dev, "%p bind failed\n", abo);
		जाओ out_unref;
	पूर्ण

	ret = amdgpu_bo_kmap(abo, शून्य);
	amdgpu_bo_unreserve(abo);
	अगर (ret) अणु
		जाओ out_unref;
	पूर्ण

	*gobj_p = gobj;
	वापस 0;
out_unref:
	amdgpufb_destroy_pinned_object(gobj);
	*gobj_p = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक amdgpufb_create(काष्ठा drm_fb_helper *helper,
			   काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा amdgpu_fbdev *rfbdev = (काष्ठा amdgpu_fbdev *)helper;
	काष्ठा amdgpu_device *adev = rfbdev->adev;
	काष्ठा fb_info *info;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_mode_fb_cmd2 mode_cmd;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा amdgpu_bo *abo = शून्य;
	पूर्णांक ret;

	स_रखो(&mode_cmd, 0, माप(mode_cmd));
	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	अगर (sizes->surface_bpp == 24)
		sizes->surface_bpp = 32;

	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
							  sizes->surface_depth);

	ret = amdgpufb_create_pinned_object(rfbdev, &mode_cmd, &gobj);
	अगर (ret) अणु
		DRM_ERROR("failed to create fbcon object %d\n", ret);
		वापस ret;
	पूर्ण

	abo = gem_to_amdgpu_bo(gobj);

	/* okay we have an object now allocate the framebuffer */
	info = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण

	ret = amdgpu_display_gem_fb_init(adev_to_drm(adev), &rfbdev->rfb,
					 &mode_cmd, gobj);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize framebuffer %d\n", ret);
		जाओ out;
	पूर्ण

	fb = &rfbdev->rfb.base;

	/* setup helper */
	rfbdev->helper.fb = fb;

	info->fbops = &amdgpufb_ops;

	info->fix.smem_start = amdgpu_gmc_vram_cpu_pa(adev, abo);
	info->fix.smem_len = amdgpu_bo_size(abo);
	info->screen_base = amdgpu_bo_kptr(abo);
	info->screen_size = amdgpu_bo_size(abo);

	drm_fb_helper_fill_info(info, &rfbdev->helper, sizes);

	/* setup aperture base/size क्रम vesafb takeover */
	info->apertures->ranges[0].base = adev_to_drm(adev)->mode_config.fb_base;
	info->apertures->ranges[0].size = adev->gmc.aper_size;

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	अगर (info->screen_base == शून्य) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	DRM_INFO("fb mappable at 0x%lX\n",  info->fix.smem_start);
	DRM_INFO("vram apper at 0x%lX\n",  (अचिन्हित दीर्घ)adev->gmc.aper_base);
	DRM_INFO("size %lu\n", (अचिन्हित दीर्घ)amdgpu_bo_size(abo));
	DRM_INFO("fb depth is %d\n", fb->क्रमmat->depth);
	DRM_INFO("   pitch is %d\n", fb->pitches[0]);

	vga_चयनeroo_client_fb_set(adev->pdev, info);
	वापस 0;

out:
	अगर (abo) अणु

	पूर्ण
	अगर (fb && ret) अणु
		drm_gem_object_put(gobj);
		drm_framebuffer_unरेजिस्टर_निजी(fb);
		drm_framebuffer_cleanup(fb);
		kमुक्त(fb);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_fbdev_destroy(काष्ठा drm_device *dev, काष्ठा amdgpu_fbdev *rfbdev)
अणु
	काष्ठा amdgpu_framebuffer *rfb = &rfbdev->rfb;
	पूर्णांक i;

	drm_fb_helper_unरेजिस्टर_fbi(&rfbdev->helper);

	अगर (rfb->base.obj[0]) अणु
		क्रम (i = 0; i < rfb->base.क्रमmat->num_planes; i++)
			drm_gem_object_put(rfb->base.obj[0]);
		amdgpufb_destroy_pinned_object(rfb->base.obj[0]);
		rfb->base.obj[0] = शून्य;
		drm_framebuffer_unरेजिस्टर_निजी(&rfb->base);
		drm_framebuffer_cleanup(&rfb->base);
	पूर्ण
	drm_fb_helper_fini(&rfbdev->helper);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs amdgpu_fb_helper_funcs = अणु
	.fb_probe = amdgpufb_create,
पूर्ण;

पूर्णांक amdgpu_fbdev_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_fbdev *rfbdev;
	पूर्णांक bpp_sel = 32;
	पूर्णांक ret;

	/* करोn't init fbdev on hw without DCE */
	अगर (!adev->mode_info.mode_config_initialized)
		वापस 0;

	/* करोn't init fbdev अगर there are no connectors */
	अगर (list_empty(&adev_to_drm(adev)->mode_config.connector_list))
		वापस 0;

	/* select 8 bpp console on low vram cards */
	अगर (adev->gmc.real_vram_size <= (32*1024*1024))
		bpp_sel = 8;

	rfbdev = kzalloc(माप(काष्ठा amdgpu_fbdev), GFP_KERNEL);
	अगर (!rfbdev)
		वापस -ENOMEM;

	rfbdev->adev = adev;
	adev->mode_info.rfbdev = rfbdev;

	drm_fb_helper_prepare(adev_to_drm(adev), &rfbdev->helper,
			      &amdgpu_fb_helper_funcs);

	ret = drm_fb_helper_init(adev_to_drm(adev), &rfbdev->helper);
	अगर (ret) अणु
		kमुक्त(rfbdev);
		वापस ret;
	पूर्ण

	/* disable all the possible outमाला_दो/crtcs beक्रमe entering KMS mode */
	अगर (!amdgpu_device_has_dc_support(adev))
		drm_helper_disable_unused_functions(adev_to_drm(adev));

	drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	वापस 0;
पूर्ण

व्योम amdgpu_fbdev_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (!adev->mode_info.rfbdev)
		वापस;

	amdgpu_fbdev_destroy(adev_to_drm(adev), adev->mode_info.rfbdev);
	kमुक्त(adev->mode_info.rfbdev);
	adev->mode_info.rfbdev = शून्य;
पूर्ण

व्योम amdgpu_fbdev_set_suspend(काष्ठा amdgpu_device *adev, पूर्णांक state)
अणु
	अगर (adev->mode_info.rfbdev)
		drm_fb_helper_set_suspend_unlocked(&adev->mode_info.rfbdev->helper,
						   state);
पूर्ण

पूर्णांक amdgpu_fbdev_total_size(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_bo *robj;
	पूर्णांक size = 0;

	अगर (!adev->mode_info.rfbdev)
		वापस 0;

	robj = gem_to_amdgpu_bo(adev->mode_info.rfbdev->rfb.base.obj[0]);
	size += amdgpu_bo_size(robj);
	वापस size;
पूर्ण

bool amdgpu_fbdev_robj_is_fb(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *robj)
अणु
	अगर (!adev->mode_info.rfbdev)
		वापस false;
	अगर (robj == gem_to_amdgpu_bo(adev->mode_info.rfbdev->rfb.base.obj[0]))
		वापस true;
	वापस false;
पूर्ण
