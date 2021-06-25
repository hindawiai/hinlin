<शैली गुरु>
/**************************************************************************
 *
 * Copyright तऊ 2007 David Airlie
 * Copyright तऊ 2009-2015 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
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

#समावेश <linux/pci.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_kms.h"

#घोषणा VMW_सूचीTY_DELAY (HZ / 30)

काष्ठा vmw_fb_par अणु
	काष्ठा vmw_निजी *vmw_priv;

	व्योम *vदो_स्मृति;

	काष्ठा mutex bo_mutex;
	काष्ठा vmw_buffer_object *vmw_bo;
	अचिन्हित bo_size;
	काष्ठा drm_framebuffer *set_fb;
	काष्ठा drm_display_mode *set_mode;
	u32 fb_x;
	u32 fb_y;
	bool bo_ioग_लिखो;

	u32 pseuकरो_palette[17];

	अचिन्हित max_width;
	अचिन्हित max_height;

	काष्ठा अणु
		spinlock_t lock;
		bool active;
		अचिन्हित x1;
		अचिन्हित y1;
		अचिन्हित x2;
		अचिन्हित y2;
	पूर्ण dirty;

	काष्ठा drm_crtc *crtc;
	काष्ठा drm_connector *con;
	काष्ठा delayed_work local_work;
पूर्ण;

अटल पूर्णांक vmw_fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			    अचिन्हित blue, अचिन्हित transp,
			    काष्ठा fb_info *info)
अणु
	काष्ठा vmw_fb_par *par = info->par;
	u32 *pal = par->pseuकरो_palette;

	अगर (regno > 15) अणु
		DRM_ERROR("Bad regno %u.\n", regno);
		वापस 1;
	पूर्ण

	चयन (par->set_fb->क्रमmat->depth) अणु
	हाल 24:
	हाल 32:
		pal[regno] = ((red & 0xff00) << 8) |
			      (green & 0xff00) |
			     ((blue  & 0xff00) >> 8);
		अवरोध;
	शेष:
		DRM_ERROR("Bad depth %u, bpp %u.\n",
			  par->set_fb->क्रमmat->depth,
			  par->set_fb->क्रमmat->cpp[0] * 8);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_fb_check_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_info *info)
अणु
	पूर्णांक depth = var->bits_per_pixel;
	काष्ठा vmw_fb_par *par = info->par;
	काष्ठा vmw_निजी *vmw_priv = par->vmw_priv;

	चयन (var->bits_per_pixel) अणु
	हाल 32:
		depth = (var->transp.length > 0) ? 32 : 24;
		अवरोध;
	शेष:
		DRM_ERROR("Bad bpp %u.\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	चयन (depth) अणु
	हाल 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 0;
		var->transp.offset = 0;
		अवरोध;
	हाल 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 8;
		var->transp.offset = 24;
		अवरोध;
	शेष:
		DRM_ERROR("Bad depth %u.\n", depth);
		वापस -EINVAL;
	पूर्ण

	अगर ((var->xoffset + var->xres) > par->max_width ||
	    (var->yoffset + var->yres) > par->max_height) अणु
		DRM_ERROR("Requested geom can not fit in framebuffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!vmw_kms_validate_mode_vram(vmw_priv,
					var->xres * var->bits_per_pixel/8,
					var->yoffset + var->yres)) अणु
		DRM_ERROR("Requested geom can not fit in framebuffer\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

/**
 * vmw_fb_dirty_flush - flush dirty regions to the kms framebuffer
 *
 * @work: The काष्ठा work_काष्ठा associated with this task.
 *
 * This function flushes the dirty regions of the vदो_स्मृति framebuffer to the
 * kms framebuffer, and अगर the kms framebuffer is visible, also updated the
 * corresponding displays. Note that this function runs even अगर the kms
 * framebuffer is not bound to a crtc and thus not visible, but it's turned
 * off during hibernation using the par->dirty.active bool.
 */
अटल व्योम vmw_fb_dirty_flush(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmw_fb_par *par = container_of(work, काष्ठा vmw_fb_par,
					      local_work.work);
	काष्ठा vmw_निजी *vmw_priv = par->vmw_priv;
	काष्ठा fb_info *info = vmw_priv->fb_info;
	अचिन्हित दीर्घ irq_flags;
	s32 dst_x1, dst_x2, dst_y1, dst_y2, w = 0, h = 0;
	u32 cpp, max_x, max_y;
	काष्ठा drm_clip_rect clip;
	काष्ठा drm_framebuffer *cur_fb;
	u8 *src_ptr, *dst_ptr;
	काष्ठा vmw_buffer_object *vbo = par->vmw_bo;
	व्योम *भव;

	अगर (!READ_ONCE(par->dirty.active))
		वापस;

	mutex_lock(&par->bo_mutex);
	cur_fb = par->set_fb;
	अगर (!cur_fb)
		जाओ out_unlock;

	(व्योम) tपंचांग_पढ़ो_lock(&vmw_priv->reservation_sem, false);
	(व्योम) tपंचांग_bo_reserve(&vbo->base, false, false, शून्य);
	भव = vmw_bo_map_and_cache(vbo);
	अगर (!भव)
		जाओ out_unreserve;

	spin_lock_irqsave(&par->dirty.lock, irq_flags);
	अगर (!par->dirty.active) अणु
		spin_unlock_irqrestore(&par->dirty.lock, irq_flags);
		जाओ out_unreserve;
	पूर्ण

	/*
	 * Handle panning when copying from vदो_स्मृति to framebuffer.
	 * Clip dirty area to framebuffer.
	 */
	cpp = cur_fb->क्रमmat->cpp[0];
	max_x = par->fb_x + cur_fb->width;
	max_y = par->fb_y + cur_fb->height;

	dst_x1 = par->dirty.x1 - par->fb_x;
	dst_y1 = par->dirty.y1 - par->fb_y;
	dst_x1 = max_t(s32, dst_x1, 0);
	dst_y1 = max_t(s32, dst_y1, 0);

	dst_x2 = par->dirty.x2 - par->fb_x;
	dst_y2 = par->dirty.y2 - par->fb_y;
	dst_x2 = min_t(s32, dst_x2, max_x);
	dst_y2 = min_t(s32, dst_y2, max_y);
	w = dst_x2 - dst_x1;
	h = dst_y2 - dst_y1;
	w = max_t(s32, 0, w);
	h = max_t(s32, 0, h);

	par->dirty.x1 = par->dirty.x2 = 0;
	par->dirty.y1 = par->dirty.y2 = 0;
	spin_unlock_irqrestore(&par->dirty.lock, irq_flags);

	अगर (w && h) अणु
		dst_ptr = (u8 *)भव  +
			(dst_y1 * par->set_fb->pitches[0] + dst_x1 * cpp);
		src_ptr = (u8 *)par->vदो_स्मृति +
			((dst_y1 + par->fb_y) * info->fix.line_length +
			 (dst_x1 + par->fb_x) * cpp);

		जबतक (h-- > 0) अणु
			स_नकल(dst_ptr, src_ptr, w*cpp);
			dst_ptr += par->set_fb->pitches[0];
			src_ptr += info->fix.line_length;
		पूर्ण

		clip.x1 = dst_x1;
		clip.x2 = dst_x2;
		clip.y1 = dst_y1;
		clip.y2 = dst_y2;
	पूर्ण

out_unreserve:
	tपंचांग_bo_unreserve(&vbo->base);
	tपंचांग_पढ़ो_unlock(&vmw_priv->reservation_sem);
	अगर (w && h) अणु
		WARN_ON_ONCE(par->set_fb->funcs->dirty(cur_fb, शून्य, 0, 0,
						       &clip, 1));
		vmw_cmd_flush(vmw_priv, false);
	पूर्ण
out_unlock:
	mutex_unlock(&par->bo_mutex);
पूर्ण

अटल व्योम vmw_fb_dirty_mark(काष्ठा vmw_fb_par *par,
			      अचिन्हित x1, अचिन्हित y1,
			      अचिन्हित width, अचिन्हित height)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित x2 = x1 + width;
	अचिन्हित y2 = y1 + height;

	spin_lock_irqsave(&par->dirty.lock, flags);
	अगर (par->dirty.x1 == par->dirty.x2) अणु
		par->dirty.x1 = x1;
		par->dirty.y1 = y1;
		par->dirty.x2 = x2;
		par->dirty.y2 = y2;
		/* अगर we are active start the dirty work
		 * we share the work with the defio प्रणाली */
		अगर (par->dirty.active)
			schedule_delayed_work(&par->local_work,
					      VMW_सूचीTY_DELAY);
	पूर्ण अन्यथा अणु
		अगर (x1 < par->dirty.x1)
			par->dirty.x1 = x1;
		अगर (y1 < par->dirty.y1)
			par->dirty.y1 = y1;
		अगर (x2 > par->dirty.x2)
			par->dirty.x2 = x2;
		अगर (y2 > par->dirty.y2)
			par->dirty.y2 = y2;
	पूर्ण
	spin_unlock_irqrestore(&par->dirty.lock, flags);
पूर्ण

अटल पूर्णांक vmw_fb_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा vmw_fb_par *par = info->par;

	अगर ((var->xoffset + var->xres) > var->xres_भव ||
	    (var->yoffset + var->yres) > var->yres_भव) अणु
		DRM_ERROR("Requested panning can not fit in framebuffer\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&par->bo_mutex);
	par->fb_x = var->xoffset;
	par->fb_y = var->yoffset;
	अगर (par->set_fb)
		vmw_fb_dirty_mark(par, par->fb_x, par->fb_y, par->set_fb->width,
				  par->set_fb->height);
	mutex_unlock(&par->bo_mutex);

	वापस 0;
पूर्ण

अटल व्योम vmw_deferred_io(काष्ठा fb_info *info,
			    काष्ठा list_head *pagelist)
अणु
	काष्ठा vmw_fb_par *par = info->par;
	अचिन्हित दीर्घ start, end, min, max;
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;
	पूर्णांक y1, y2;

	min = अच_दीर्घ_उच्च;
	max = 0;
	list_क्रम_each_entry(page, pagelist, lru) अणु
		start = page->index << PAGE_SHIFT;
		end = start + PAGE_SIZE - 1;
		min = min(min, start);
		max = max(max, end);
	पूर्ण

	अगर (min < max) अणु
		y1 = min / info->fix.line_length;
		y2 = (max / info->fix.line_length) + 1;

		spin_lock_irqsave(&par->dirty.lock, flags);
		par->dirty.x1 = 0;
		par->dirty.y1 = y1;
		par->dirty.x2 = info->var.xres;
		par->dirty.y2 = y2;
		spin_unlock_irqrestore(&par->dirty.lock, flags);

		/*
		 * Since we've alपढ़ोy रुकोed on this work once, try to
		 * execute asap.
		 */
		cancel_delayed_work(&par->local_work);
		schedule_delayed_work(&par->local_work, 0);
	पूर्ण
पूर्ण;

अटल काष्ठा fb_deferred_io vmw_defio = अणु
	.delay		= VMW_सूचीTY_DELAY,
	.deferred_io	= vmw_deferred_io,
पूर्ण;

/*
 * Draw code
 */

अटल व्योम vmw_fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	cfb_fillrect(info, rect);
	vmw_fb_dirty_mark(info->par, rect->dx, rect->dy,
			  rect->width, rect->height);
पूर्ण

अटल व्योम vmw_fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	cfb_copyarea(info, region);
	vmw_fb_dirty_mark(info->par, region->dx, region->dy,
			  region->width, region->height);
पूर्ण

अटल व्योम vmw_fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	cfb_imageblit(info, image);
	vmw_fb_dirty_mark(info->par, image->dx, image->dy,
			  image->width, image->height);
पूर्ण

/*
 * Bring up code
 */

अटल पूर्णांक vmw_fb_create_bo(काष्ठा vmw_निजी *vmw_priv,
			    माप_प्रकार size, काष्ठा vmw_buffer_object **out)
अणु
	काष्ठा vmw_buffer_object *vmw_bo;
	पूर्णांक ret;

	(व्योम) tपंचांग_ग_लिखो_lock(&vmw_priv->reservation_sem, false);

	vmw_bo = kदो_स्मृति(माप(*vmw_bo), GFP_KERNEL);
	अगर (!vmw_bo) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	ret = vmw_bo_init(vmw_priv, vmw_bo, size,
			      &vmw_sys_placement,
			      false, false,
			      &vmw_bo_bo_मुक्त);
	अगर (unlikely(ret != 0))
		जाओ err_unlock; /* init मुक्तs the buffer on failure */

	*out = vmw_bo;
	tपंचांग_ग_लिखो_unlock(&vmw_priv->reservation_sem);

	वापस 0;

err_unlock:
	tपंचांग_ग_लिखो_unlock(&vmw_priv->reservation_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_fb_compute_depth(काष्ठा fb_var_screeninfo *var,
				पूर्णांक *depth)
अणु
	चयन (var->bits_per_pixel) अणु
	हाल 32:
		*depth = (var->transp.length > 0) ? 32 : 24;
		अवरोध;
	शेष:
		DRM_ERROR("Bad bpp %u.\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmwgfx_set_config_पूर्णांकernal(काष्ठा drm_mode_set *set)
अणु
	काष्ठा drm_crtc *crtc = set->crtc;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	drm_modeset_acquire_init(&ctx, 0);

restart:
	ret = crtc->funcs->set_config(set, &ctx);

	अगर (ret == -EDEADLK) अणु
		drm_modeset_backoff(&ctx);
		जाओ restart;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_fb_kms_detach(काष्ठा vmw_fb_par *par,
			     bool detach_bo,
			     bool unref_bo)
अणु
	काष्ठा drm_framebuffer *cur_fb = par->set_fb;
	पूर्णांक ret;

	/* Detach the KMS framebuffer from crtcs */
	अगर (par->set_mode) अणु
		काष्ठा drm_mode_set set;

		set.crtc = par->crtc;
		set.x = 0;
		set.y = 0;
		set.mode = शून्य;
		set.fb = शून्य;
		set.num_connectors = 0;
		set.connectors = &par->con;
		ret = vmwgfx_set_config_पूर्णांकernal(&set);
		अगर (ret) अणु
			DRM_ERROR("Could not unset a mode.\n");
			वापस ret;
		पूर्ण
		drm_mode_destroy(&par->vmw_priv->drm, par->set_mode);
		par->set_mode = शून्य;
	पूर्ण

	अगर (cur_fb) अणु
		drm_framebuffer_put(cur_fb);
		par->set_fb = शून्य;
	पूर्ण

	अगर (par->vmw_bo && detach_bo && unref_bo)
		vmw_bo_unreference(&par->vmw_bo);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_fb_kms_framebuffer(काष्ठा fb_info *info)
अणु
	काष्ठा drm_mode_fb_cmd2 mode_cmd;
	काष्ठा vmw_fb_par *par = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा drm_framebuffer *cur_fb;
	काष्ठा vmw_framebuffer *vfb;
	पूर्णांक ret = 0, depth;
	माप_प्रकार new_bo_size;

	ret = vmw_fb_compute_depth(var, &depth);
	अगर (ret)
		वापस ret;

	mode_cmd.width = var->xres;
	mode_cmd.height = var->yres;
	mode_cmd.pitches[0] = ((var->bits_per_pixel + 7) / 8) * mode_cmd.width;
	mode_cmd.pixel_क्रमmat =
		drm_mode_legacy_fb_क्रमmat(var->bits_per_pixel, depth);

	cur_fb = par->set_fb;
	अगर (cur_fb && cur_fb->width == mode_cmd.width &&
	    cur_fb->height == mode_cmd.height &&
	    cur_fb->क्रमmat->क्रमmat == mode_cmd.pixel_क्रमmat &&
	    cur_fb->pitches[0] == mode_cmd.pitches[0])
		वापस 0;

	/* Need new buffer object ? */
	new_bo_size = (माप_प्रकार) mode_cmd.pitches[0] * (माप_प्रकार) mode_cmd.height;
	ret = vmw_fb_kms_detach(par,
				par->bo_size < new_bo_size ||
				par->bo_size > 2*new_bo_size,
				true);
	अगर (ret)
		वापस ret;

	अगर (!par->vmw_bo) अणु
		ret = vmw_fb_create_bo(par->vmw_priv, new_bo_size,
				       &par->vmw_bo);
		अगर (ret) अणु
			DRM_ERROR("Failed creating a buffer object for "
				  "fbdev.\n");
			वापस ret;
		पूर्ण
		par->bo_size = new_bo_size;
	पूर्ण

	vfb = vmw_kms_new_framebuffer(par->vmw_priv, par->vmw_bo, शून्य,
				      true, &mode_cmd);
	अगर (IS_ERR(vfb))
		वापस PTR_ERR(vfb);

	par->set_fb = &vfb->base;

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा vmw_fb_par *par = info->par;
	काष्ठा vmw_निजी *vmw_priv = par->vmw_priv;
	काष्ठा drm_mode_set set;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा drm_display_mode new_mode = अणु DRM_MODE("fb_mode",
		DRM_MODE_TYPE_DRIVER,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
	पूर्ण;
	काष्ठा drm_display_mode *mode;
	पूर्णांक ret;

	mode = drm_mode_duplicate(&vmw_priv->drm, &new_mode);
	अगर (!mode) अणु
		DRM_ERROR("Could not create new fb mode.\n");
		वापस -ENOMEM;
	पूर्ण

	mode->hdisplay = var->xres;
	mode->vdisplay = var->yres;
	vmw_guess_mode_timing(mode);

	अगर (!vmw_kms_validate_mode_vram(vmw_priv,
					mode->hdisplay *
					DIV_ROUND_UP(var->bits_per_pixel, 8),
					mode->vdisplay)) अणु
		drm_mode_destroy(&vmw_priv->drm, mode);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&par->bo_mutex);
	ret = vmw_fb_kms_framebuffer(info);
	अगर (ret)
		जाओ out_unlock;

	par->fb_x = var->xoffset;
	par->fb_y = var->yoffset;

	set.crtc = par->crtc;
	set.x = 0;
	set.y = 0;
	set.mode = mode;
	set.fb = par->set_fb;
	set.num_connectors = 1;
	set.connectors = &par->con;

	ret = vmwgfx_set_config_पूर्णांकernal(&set);
	अगर (ret)
		जाओ out_unlock;

	vmw_fb_dirty_mark(par, par->fb_x, par->fb_y,
			  par->set_fb->width, par->set_fb->height);

	/* If there alपढ़ोy was stuff dirty we wont
	 * schedule a new work, so lets करो it now */

	schedule_delayed_work(&par->local_work, 0);

out_unlock:
	अगर (par->set_mode)
		drm_mode_destroy(&vmw_priv->drm, par->set_mode);
	par->set_mode = mode;

	mutex_unlock(&par->bo_mutex);

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा fb_ops vmw_fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var = vmw_fb_check_var,
	.fb_set_par = vmw_fb_set_par,
	.fb_setcolreg = vmw_fb_setcolreg,
	.fb_fillrect = vmw_fb_fillrect,
	.fb_copyarea = vmw_fb_copyarea,
	.fb_imageblit = vmw_fb_imageblit,
	.fb_pan_display = vmw_fb_pan_display,
	.fb_blank = vmw_fb_blank,
पूर्ण;

पूर्णांक vmw_fb_init(काष्ठा vmw_निजी *vmw_priv)
अणु
	काष्ठा device *device = vmw_priv->drm.dev;
	काष्ठा vmw_fb_par *par;
	काष्ठा fb_info *info;
	अचिन्हित fb_width, fb_height;
	अचिन्हित पूर्णांक fb_bpp, fb_pitch, fb_size;
	काष्ठा drm_display_mode *init_mode;
	पूर्णांक ret;

	fb_bpp = 32;

	/* XXX As shouldn't these be as well. */
	fb_width = min(vmw_priv->fb_max_width, (अचिन्हित)2048);
	fb_height = min(vmw_priv->fb_max_height, (अचिन्हित)2048);

	fb_pitch = fb_width * fb_bpp / 8;
	fb_size = fb_pitch * fb_height;

	info = framebuffer_alloc(माप(*par), device);
	अगर (!info)
		वापस -ENOMEM;

	/*
	 * Par
	 */
	vmw_priv->fb_info = info;
	par = info->par;
	स_रखो(par, 0, माप(*par));
	INIT_DELAYED_WORK(&par->local_work, &vmw_fb_dirty_flush);
	par->vmw_priv = vmw_priv;
	par->vदो_स्मृति = शून्य;
	par->max_width = fb_width;
	par->max_height = fb_height;

	ret = vmw_kms_fbdev_init_data(vmw_priv, 0, par->max_width,
				      par->max_height, &par->con,
				      &par->crtc, &init_mode);
	अगर (ret)
		जाओ err_kms;

	info->var.xres = init_mode->hdisplay;
	info->var.yres = init_mode->vdisplay;

	/*
	 * Create buffers and alloc memory
	 */
	par->vदो_स्मृति = vzalloc(fb_size);
	अगर (unlikely(par->vदो_स्मृति == शून्य)) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	/*
	 * Fixed and var
	 */
	म_नकल(info->fix.id, "svgadrmfb");
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 1; /* करोing it in hw */
	info->fix.ypanstep = 1; /* करोing it in hw */
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->fix.line_length = fb_pitch;

	info->fix.smem_start = 0;
	info->fix.smem_len = fb_size;

	info->pseuकरो_palette = par->pseuकरो_palette;
	info->screen_base = (अक्षर __iomem *)par->vदो_स्मृति;
	info->screen_size = fb_size;

	info->fbops = &vmw_fb_ops;

	/* 24 depth per शेष */
	info->var.red.offset = 16;
	info->var.green.offset = 8;
	info->var.blue.offset = 0;
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;
	info->var.transp.offset = 0;
	info->var.transp.length = 0;

	info->var.xres_भव = fb_width;
	info->var.yres_भव = fb_height;
	info->var.bits_per_pixel = fb_bpp;
	info->var.xoffset = 0;
	info->var.yoffset = 0;
	info->var.activate = FB_ACTIVATE_NOW;
	info->var.height = -1;
	info->var.width = -1;

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */
	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ err_aper;
	पूर्ण
	info->apertures->ranges[0].base = vmw_priv->vram_start;
	info->apertures->ranges[0].size = vmw_priv->vram_size;

	/*
	 * Dirty & Deferred IO
	 */
	par->dirty.x1 = par->dirty.x2 = 0;
	par->dirty.y1 = par->dirty.y2 = 0;
	par->dirty.active = true;
	spin_lock_init(&par->dirty.lock);
	mutex_init(&par->bo_mutex);
	info->fbdefio = &vmw_defio;
	fb_deferred_io_init(info);

	ret = रेजिस्टर_framebuffer(info);
	अगर (unlikely(ret != 0))
		जाओ err_defio;

	vmw_fb_set_par(info);

	वापस 0;

err_defio:
	fb_deferred_io_cleanup(info);
err_aper:
err_मुक्त:
	vमुक्त(par->vदो_स्मृति);
err_kms:
	framebuffer_release(info);
	vmw_priv->fb_info = शून्य;

	वापस ret;
पूर्ण

पूर्णांक vmw_fb_बंद(काष्ठा vmw_निजी *vmw_priv)
अणु
	काष्ठा fb_info *info;
	काष्ठा vmw_fb_par *par;

	अगर (!vmw_priv->fb_info)
		वापस 0;

	info = vmw_priv->fb_info;
	par = info->par;

	/* ??? order */
	fb_deferred_io_cleanup(info);
	cancel_delayed_work_sync(&par->local_work);
	unरेजिस्टर_framebuffer(info);

	mutex_lock(&par->bo_mutex);
	(व्योम) vmw_fb_kms_detach(par, true, true);
	mutex_unlock(&par->bo_mutex);

	vमुक्त(par->vदो_स्मृति);
	framebuffer_release(info);

	वापस 0;
पूर्ण

पूर्णांक vmw_fb_off(काष्ठा vmw_निजी *vmw_priv)
अणु
	काष्ठा fb_info *info;
	काष्ठा vmw_fb_par *par;
	अचिन्हित दीर्घ flags;

	अगर (!vmw_priv->fb_info)
		वापस -EINVAL;

	info = vmw_priv->fb_info;
	par = info->par;

	spin_lock_irqsave(&par->dirty.lock, flags);
	par->dirty.active = false;
	spin_unlock_irqrestore(&par->dirty.lock, flags);

	flush_delayed_work(&info->deferred_work);
	flush_delayed_work(&par->local_work);

	वापस 0;
पूर्ण

पूर्णांक vmw_fb_on(काष्ठा vmw_निजी *vmw_priv)
अणु
	काष्ठा fb_info *info;
	काष्ठा vmw_fb_par *par;
	अचिन्हित दीर्घ flags;

	अगर (!vmw_priv->fb_info)
		वापस -EINVAL;

	info = vmw_priv->fb_info;
	par = info->par;

	spin_lock_irqsave(&par->dirty.lock, flags);
	par->dirty.active = true;
	spin_unlock_irqrestore(&par->dirty.lock, flags);

	/*
	 * Need to reschedule a dirty update, because otherwise that's
	 * only करोne in dirty_mark() अगर the previous coalesced
	 * dirty region was empty.
	 */
	schedule_delayed_work(&par->local_work, 0);

	वापस 0;
पूर्ण
