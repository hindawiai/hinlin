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
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"

/* object hierarchy -
 * this contains a helper + a radeon fb
 * the helper contains a poपूर्णांकer to radeon framebuffer baseclass.
 */
काष्ठा radeon_fbdev अणु
	काष्ठा drm_fb_helper helper; /* must be first */
	काष्ठा drm_framebuffer fb;
	काष्ठा radeon_device *rdev;
पूर्ण;

अटल पूर्णांक
radeonfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा radeon_fbdev *rfbdev = info->par;
	काष्ठा radeon_device *rdev = rfbdev->rdev;
	पूर्णांक ret = pm_runसमय_get_sync(rdev->ddev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_mark_last_busy(rdev->ddev->dev);
		pm_runसमय_put_स्वतःsuspend(rdev->ddev->dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
radeonfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा radeon_fbdev *rfbdev = info->par;
	काष्ठा radeon_device *rdev = rfbdev->rdev;

	pm_runसमय_mark_last_busy(rdev->ddev->dev);
	pm_runसमय_put_स्वतःsuspend(rdev->ddev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops radeonfb_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_खोलो = radeonfb_खोलो,
	.fb_release = radeonfb_release,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
पूर्ण;


पूर्णांक radeon_align_pitch(काष्ठा radeon_device *rdev, पूर्णांक width, पूर्णांक cpp, bool tiled)
अणु
	पूर्णांक aligned = width;
	पूर्णांक align_large = (ASIC_IS_AVIVO(rdev)) || tiled;
	पूर्णांक pitch_mask = 0;

	चयन (cpp) अणु
	हाल 1:
		pitch_mask = align_large ? 255 : 127;
		अवरोध;
	हाल 2:
		pitch_mask = align_large ? 127 : 31;
		अवरोध;
	हाल 3:
	हाल 4:
		pitch_mask = align_large ? 63 : 15;
		अवरोध;
	पूर्ण

	aligned += pitch_mask;
	aligned &= ~pitch_mask;
	वापस aligned * cpp;
पूर्ण

अटल व्योम radeonfb_destroy_pinned_object(काष्ठा drm_gem_object *gobj)
अणु
	काष्ठा radeon_bo *rbo = gem_to_radeon_bo(gobj);
	पूर्णांक ret;

	ret = radeon_bo_reserve(rbo, false);
	अगर (likely(ret == 0)) अणु
		radeon_bo_kunmap(rbo);
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	पूर्ण
	drm_gem_object_put(gobj);
पूर्ण

अटल पूर्णांक radeonfb_create_pinned_object(काष्ठा radeon_fbdev *rfbdev,
					 काष्ठा drm_mode_fb_cmd2 *mode_cmd,
					 काष्ठा drm_gem_object **gobj_p)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	काष्ठा radeon_device *rdev = rfbdev->rdev;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा radeon_bo *rbo = शून्य;
	bool fb_tiled = false; /* useful क्रम testing */
	u32 tiling_flags = 0;
	पूर्णांक ret;
	पूर्णांक aligned_size, size;
	पूर्णांक height = mode_cmd->height;
	u32 cpp;

	info = drm_get_क्रमmat_info(rdev->ddev, mode_cmd);
	cpp = info->cpp[0];

	/* need to align pitch with crtc limits */
	mode_cmd->pitches[0] = radeon_align_pitch(rdev, mode_cmd->width, cpp,
						  fb_tiled);

	अगर (rdev->family >= CHIP_R600)
		height = ALIGN(mode_cmd->height, 8);
	size = mode_cmd->pitches[0] * height;
	aligned_size = ALIGN(size, PAGE_SIZE);
	ret = radeon_gem_object_create(rdev, aligned_size, 0,
				       RADEON_GEM_DOMAIN_VRAM,
				       0, true, &gobj);
	अगर (ret) अणु
		pr_err("failed to allocate framebuffer (%d)\n", aligned_size);
		वापस -ENOMEM;
	पूर्ण
	rbo = gem_to_radeon_bo(gobj);

	अगर (fb_tiled)
		tiling_flags = RADEON_TILING_MACRO;

#अगर_घोषित __BIG_ENDIAN
	चयन (cpp) अणु
	हाल 4:
		tiling_flags |= RADEON_TILING_SWAP_32BIT;
		अवरोध;
	हाल 2:
		tiling_flags |= RADEON_TILING_SWAP_16BIT;
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	अगर (tiling_flags) अणु
		ret = radeon_bo_set_tiling_flags(rbo,
						 tiling_flags | RADEON_TILING_SURFACE,
						 mode_cmd->pitches[0]);
		अगर (ret)
			dev_err(rdev->dev, "FB failed to set tiling flags\n");
	पूर्ण


	ret = radeon_bo_reserve(rbo, false);
	अगर (unlikely(ret != 0))
		जाओ out_unref;
	/* Only 27 bit offset क्रम legacy CRTC */
	ret = radeon_bo_pin_restricted(rbo, RADEON_GEM_DOMAIN_VRAM,
				       ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27,
				       शून्य);
	अगर (ret) अणु
		radeon_bo_unreserve(rbo);
		जाओ out_unref;
	पूर्ण
	अगर (fb_tiled)
		radeon_bo_check_tiling(rbo, 0, 0);
	ret = radeon_bo_kmap(rbo, शून्य);
	radeon_bo_unreserve(rbo);
	अगर (ret) अणु
		जाओ out_unref;
	पूर्ण

	*gobj_p = gobj;
	वापस 0;
out_unref:
	radeonfb_destroy_pinned_object(gobj);
	*gobj_p = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक radeonfb_create(काष्ठा drm_fb_helper *helper,
			   काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा radeon_fbdev *rfbdev =
		container_of(helper, काष्ठा radeon_fbdev, helper);
	काष्ठा radeon_device *rdev = rfbdev->rdev;
	काष्ठा fb_info *info;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_mode_fb_cmd2 mode_cmd;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा radeon_bo *rbo = शून्य;
	पूर्णांक ret;
	अचिन्हित दीर्घ पंचांगp;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	/* avivo can't scanout real 24bpp */
	अगर ((sizes->surface_bpp == 24) && ASIC_IS_AVIVO(rdev))
		sizes->surface_bpp = 32;

	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(sizes->surface_bpp,
							  sizes->surface_depth);

	ret = radeonfb_create_pinned_object(rfbdev, &mode_cmd, &gobj);
	अगर (ret) अणु
		DRM_ERROR("failed to create fbcon object %d\n", ret);
		वापस ret;
	पूर्ण

	rbo = gem_to_radeon_bo(gobj);

	/* okay we have an object now allocate the framebuffer */
	info = drm_fb_helper_alloc_fbi(helper);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण

	/* radeon resume is fragile and needs a vt चयन to help it aदीर्घ */
	info->skip_vt_चयन = false;

	ret = radeon_framebuffer_init(rdev->ddev, &rfbdev->fb, &mode_cmd, gobj);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize framebuffer %d\n", ret);
		जाओ out;
	पूर्ण

	fb = &rfbdev->fb;

	/* setup helper */
	rfbdev->helper.fb = fb;

	स_रखो_io(rbo->kptr, 0x0, radeon_bo_size(rbo));

	info->fbops = &radeonfb_ops;

	पंचांगp = radeon_bo_gpu_offset(rbo) - rdev->mc.vram_start;
	info->fix.smem_start = rdev->mc.aper_base + पंचांगp;
	info->fix.smem_len = radeon_bo_size(rbo);
	info->screen_base = rbo->kptr;
	info->screen_size = radeon_bo_size(rbo);

	drm_fb_helper_fill_info(info, &rfbdev->helper, sizes);

	/* setup aperture base/size क्रम vesafb takeover */
	info->apertures->ranges[0].base = rdev->ddev->mode_config.fb_base;
	info->apertures->ranges[0].size = rdev->mc.aper_size;

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	अगर (info->screen_base == शून्य) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	DRM_INFO("fb mappable at 0x%lX\n",  info->fix.smem_start);
	DRM_INFO("vram apper at 0x%lX\n",  (अचिन्हित दीर्घ)rdev->mc.aper_base);
	DRM_INFO("size %lu\n", (अचिन्हित दीर्घ)radeon_bo_size(rbo));
	DRM_INFO("fb depth is %d\n", fb->क्रमmat->depth);
	DRM_INFO("   pitch is %d\n", fb->pitches[0]);

	vga_चयनeroo_client_fb_set(rdev->pdev, info);
	वापस 0;

out:
	अगर (rbo) अणु

	पूर्ण
	अगर (fb && ret) अणु
		drm_gem_object_put(gobj);
		drm_framebuffer_unरेजिस्टर_निजी(fb);
		drm_framebuffer_cleanup(fb);
		kमुक्त(fb);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक radeon_fbdev_destroy(काष्ठा drm_device *dev, काष्ठा radeon_fbdev *rfbdev)
अणु
	काष्ठा drm_framebuffer *fb = &rfbdev->fb;

	drm_fb_helper_unरेजिस्टर_fbi(&rfbdev->helper);

	अगर (fb->obj[0]) अणु
		radeonfb_destroy_pinned_object(fb->obj[0]);
		fb->obj[0] = शून्य;
		drm_framebuffer_unरेजिस्टर_निजी(fb);
		drm_framebuffer_cleanup(fb);
	पूर्ण
	drm_fb_helper_fini(&rfbdev->helper);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs radeon_fb_helper_funcs = अणु
	.fb_probe = radeonfb_create,
पूर्ण;

पूर्णांक radeon_fbdev_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_fbdev *rfbdev;
	पूर्णांक bpp_sel = 32;
	पूर्णांक ret;

	/* करोn't enable fbdev अगर no connectors */
	अगर (list_empty(&rdev->ddev->mode_config.connector_list))
		वापस 0;

	/* select 8 bpp console on 8MB cards, or 16 bpp on RN50 or 32MB */
	अगर (rdev->mc.real_vram_size <= (8*1024*1024))
		bpp_sel = 8;
	अन्यथा अगर (ASIC_IS_RN50(rdev) ||
		 rdev->mc.real_vram_size <= (32*1024*1024))
		bpp_sel = 16;

	rfbdev = kzalloc(माप(काष्ठा radeon_fbdev), GFP_KERNEL);
	अगर (!rfbdev)
		वापस -ENOMEM;

	rfbdev->rdev = rdev;
	rdev->mode_info.rfbdev = rfbdev;

	drm_fb_helper_prepare(rdev->ddev, &rfbdev->helper,
			      &radeon_fb_helper_funcs);

	ret = drm_fb_helper_init(rdev->ddev, &rfbdev->helper);
	अगर (ret)
		जाओ मुक्त;

	/* disable all the possible outमाला_दो/crtcs beक्रमe entering KMS mode */
	drm_helper_disable_unused_functions(rdev->ddev);

	ret = drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	अगर (ret)
		जाओ fini;

	वापस 0;

fini:
	drm_fb_helper_fini(&rfbdev->helper);
मुक्त:
	kमुक्त(rfbdev);
	वापस ret;
पूर्ण

व्योम radeon_fbdev_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (!rdev->mode_info.rfbdev)
		वापस;

	radeon_fbdev_destroy(rdev->ddev, rdev->mode_info.rfbdev);
	kमुक्त(rdev->mode_info.rfbdev);
	rdev->mode_info.rfbdev = शून्य;
पूर्ण

व्योम radeon_fbdev_set_suspend(काष्ठा radeon_device *rdev, पूर्णांक state)
अणु
	अगर (rdev->mode_info.rfbdev)
		drm_fb_helper_set_suspend(&rdev->mode_info.rfbdev->helper, state);
पूर्ण

bool radeon_fbdev_robj_is_fb(काष्ठा radeon_device *rdev, काष्ठा radeon_bo *robj)
अणु
	अगर (!rdev->mode_info.rfbdev)
		वापस false;

	अगर (robj == gem_to_radeon_bo(rdev->mode_info.rfbdev->fb.obj[0]))
		वापस true;
	वापस false;
पूर्ण
