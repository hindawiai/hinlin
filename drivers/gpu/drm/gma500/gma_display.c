<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2011 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Patrik Jakobsson <patrik.r.jakobsson@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>

#समावेश "framebuffer.h"
#समावेश "gma_display.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/*
 * Returns whether any output on the specअगरied pipe is of the specअगरied type
 */
bool gma_pipe_has_type(काष्ठा drm_crtc *crtc, पूर्णांक type)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *l_entry;

	list_क्रम_each_entry(l_entry, &mode_config->connector_list, head) अणु
		अगर (l_entry->encoder && l_entry->encoder->crtc == crtc) अणु
			काष्ठा gma_encoder *gma_encoder =
						gma_attached_encoder(l_entry);
			अगर (gma_encoder->type == type)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

व्योम gma_रुको_क्रम_vblank(काष्ठा drm_device *dev)
अणु
	/* Wait क्रम 20ms, i.e. one cycle at 50hz. */
	mdelay(20);
पूर्ण

पूर्णांक gma_pipe_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
		      काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	काष्ठा gtt_range *gtt;
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	अचिन्हित दीर्घ start, offset;
	u32 dspcntr;
	पूर्णांक ret = 0;

	अगर (!gma_घातer_begin(dev, true))
		वापस 0;

	/* no fb bound */
	अगर (!fb) अणु
		dev_err(dev->dev, "No FB bound\n");
		जाओ gma_pipe_cleaner;
	पूर्ण

	gtt = to_gtt_range(fb->obj[0]);

	/* We are displaying this buffer, make sure it is actually loaded
	   पूर्णांकo the GTT */
	ret = psb_gtt_pin(gtt);
	अगर (ret < 0)
		जाओ gma_pipe_set_base_निकास;
	start = gtt->offset;
	offset = y * fb->pitches[0] + x * fb->क्रमmat->cpp[0];

	REG_WRITE(map->stride, fb->pitches[0]);

	dspcntr = REG_READ(map->cntr);
	dspcntr &= ~DISPPLANE_PIXFORMAT_MASK;

	चयन (fb->क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		dspcntr |= DISPPLANE_8BPP;
		अवरोध;
	हाल 16:
		अगर (fb->क्रमmat->depth == 15)
			dspcntr |= DISPPLANE_15_16BPP;
		अन्यथा
			dspcntr |= DISPPLANE_16BPP;
		अवरोध;
	हाल 24:
	हाल 32:
		dspcntr |= DISPPLANE_32BPP_NO_ALPHA;
		अवरोध;
	शेष:
		dev_err(dev->dev, "Unknown color depth\n");
		ret = -EINVAL;
		जाओ gma_pipe_set_base_निकास;
	पूर्ण
	REG_WRITE(map->cntr, dspcntr);

	dev_dbg(dev->dev,
		"Writing base %08lX %08lX %d %d\n", start, offset, x, y);

	/* FIXME: Investigate whether this really is the base क्रम psb and why
		  the linear offset is named base क्रम the other chips. map->surf
		  should be the base and map->linoff the offset क्रम all chips */
	अगर (IS_PSB(dev)) अणु
		REG_WRITE(map->base, offset + start);
		REG_READ(map->base);
	पूर्ण अन्यथा अणु
		REG_WRITE(map->base, offset);
		REG_READ(map->base);
		REG_WRITE(map->surf, start);
		REG_READ(map->surf);
	पूर्ण

gma_pipe_cleaner:
	/* If there was a previous display we can now unpin it */
	अगर (old_fb)
		psb_gtt_unpin(to_gtt_range(old_fb->obj[0]));

gma_pipe_set_base_निकास:
	gma_घातer_end(dev);
	वापस ret;
पूर्ण

/* Loads the palette/gamma unit क्रम the CRTC with the prepared values */
व्योम gma_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[gma_crtc->pipe];
	पूर्णांक palreg = map->palette;
	u16 *r, *g, *b;
	पूर्णांक i;

	/* The घड़ीs have to be on to load the palette. */
	अगर (!crtc->enabled)
		वापस;

	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	अगर (gma_घातer_begin(dev, false)) अणु
		क्रम (i = 0; i < 256; i++) अणु
			REG_WRITE(palreg + 4 * i,
				  (((*r++ >> 8) + gma_crtc->lut_adj[i]) << 16) |
				  (((*g++ >> 8) + gma_crtc->lut_adj[i]) << 8) |
				  ((*b++ >> 8) + gma_crtc->lut_adj[i]));
		पूर्ण
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 256; i++) अणु
			/* FIXME: Why pipe[0] and not pipe[..._crtc->pipe]? */
			dev_priv->regs.pipe[0].palette[i] =
				(((*r++ >> 8) + gma_crtc->lut_adj[i]) << 16) |
				(((*g++ >> 8) + gma_crtc->lut_adj[i]) << 8) |
				((*b++ >> 8) + gma_crtc->lut_adj[i]);
		पूर्ण

	पूर्ण
पूर्ण

पूर्णांक gma_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red, u16 *green, u16 *blue,
		       u32 size,
		       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	gma_crtc_load_lut(crtc);

	वापस 0;
पूर्ण

/*
 * Sets the घातer management mode of the pipe and plane.
 *
 * This code should probably grow support क्रम turning the cursor off and back
 * on appropriately at the same समय as we're turning the pipe off/on.
 */
व्योम gma_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	u32 temp;

	/* XXX: When our outमाला_दो are all unaware of DPMS modes other than off
	 * and on, we should map those modes to DRM_MODE_DPMS_OFF in the CRTC.
	 */

	अगर (IS_CDV(dev))
		dev_priv->ops->disable_sr(dev);

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
		अगर (gma_crtc->active)
			अवरोध;

		gma_crtc->active = true;

		/* Enable the DPLL */
		temp = REG_READ(map->dpll);
		अगर ((temp & DPLL_VCO_ENABLE) == 0) अणु
			REG_WRITE(map->dpll, temp);
			REG_READ(map->dpll);
			/* Wait क्रम the घड़ीs to stabilize. */
			udelay(150);
			REG_WRITE(map->dpll, temp | DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
			/* Wait क्रम the घड़ीs to stabilize. */
			udelay(150);
			REG_WRITE(map->dpll, temp | DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
			/* Wait क्रम the घड़ीs to stabilize. */
			udelay(150);
		पूर्ण

		/* Enable the plane */
		temp = REG_READ(map->cntr);
		अगर ((temp & DISPLAY_PLANE_ENABLE) == 0) अणु
			REG_WRITE(map->cntr,
				  temp | DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
		पूर्ण

		udelay(150);

		/* Enable the pipe */
		temp = REG_READ(map->conf);
		अगर ((temp & PIPEACONF_ENABLE) == 0)
			REG_WRITE(map->conf, temp | PIPEACONF_ENABLE);

		temp = REG_READ(map->status);
		temp &= ~(0xFFFF);
		temp |= PIPE_FIFO_UNDERRUN;
		REG_WRITE(map->status, temp);
		REG_READ(map->status);

		gma_crtc_load_lut(crtc);

		/* Give the overlay scaler a chance to enable
		 * अगर it's on this pipe */
		/* psb_पूर्णांकel_crtc_dpms_video(crtc, true); TODO */

		drm_crtc_vblank_on(crtc);
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		अगर (!gma_crtc->active)
			अवरोध;

		gma_crtc->active = false;

		/* Give the overlay scaler a chance to disable
		 * अगर it's on this pipe */
		/* psb_पूर्णांकel_crtc_dpms_video(crtc, FALSE); TODO */

		/* Disable the VGA plane that we never use */
		REG_WRITE(VGACNTRL, VGA_DISP_DISABLE);

		/* Turn off vblank पूर्णांकerrupts */
		drm_crtc_vblank_off(crtc);

		/* Wait क्रम vblank क्रम the disable to take effect */
		gma_रुको_क्रम_vblank(dev);

		/* Disable plane */
		temp = REG_READ(map->cntr);
		अगर ((temp & DISPLAY_PLANE_ENABLE) != 0) अणु
			REG_WRITE(map->cntr,
				  temp & ~DISPLAY_PLANE_ENABLE);
			/* Flush the plane changes */
			REG_WRITE(map->base, REG_READ(map->base));
			REG_READ(map->base);
		पूर्ण

		/* Disable pipe */
		temp = REG_READ(map->conf);
		अगर ((temp & PIPEACONF_ENABLE) != 0) अणु
			REG_WRITE(map->conf, temp & ~PIPEACONF_ENABLE);
			REG_READ(map->conf);
		पूर्ण

		/* Wait क्रम vblank क्रम the disable to take effect. */
		gma_रुको_क्रम_vblank(dev);

		udelay(150);

		/* Disable DPLL */
		temp = REG_READ(map->dpll);
		अगर ((temp & DPLL_VCO_ENABLE) != 0) अणु
			REG_WRITE(map->dpll, temp & ~DPLL_VCO_ENABLE);
			REG_READ(map->dpll);
		पूर्ण

		/* Wait क्रम the घड़ीs to turn off. */
		udelay(150);
		अवरोध;
	पूर्ण

	अगर (IS_CDV(dev))
		dev_priv->ops->update_wm(dev, crtc);

	/* Set FIFO watermarks */
	REG_WRITE(DSPARB, 0x3F3E);
पूर्ण

पूर्णांक gma_crtc_cursor_set(काष्ठा drm_crtc *crtc,
			काष्ठा drm_file *file_priv,
			uपूर्णांक32_t handle,
			uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	uपूर्णांक32_t control = (pipe == 0) ? CURACNTR : CURBCNTR;
	uपूर्णांक32_t base = (pipe == 0) ? CURABASE : CURBBASE;
	uपूर्णांक32_t temp;
	माप_प्रकार addr = 0;
	काष्ठा gtt_range *gt;
	काष्ठा gtt_range *cursor_gt = gma_crtc->cursor_gt;
	काष्ठा drm_gem_object *obj;
	व्योम *पंचांगp_dst, *पंचांगp_src;
	पूर्णांक ret = 0, i, cursor_pages;

	/* If we didn't get a handle then turn the cursor off */
	अगर (!handle) अणु
		temp = CURSOR_MODE_DISABLE;
		अगर (gma_घातer_begin(dev, false)) अणु
			REG_WRITE(control, temp);
			REG_WRITE(base, 0);
			gma_घातer_end(dev);
		पूर्ण

		/* Unpin the old GEM object */
		अगर (gma_crtc->cursor_obj) अणु
			gt = container_of(gma_crtc->cursor_obj,
					  काष्ठा gtt_range, gem);
			psb_gtt_unpin(gt);
			drm_gem_object_put(gma_crtc->cursor_obj);
			gma_crtc->cursor_obj = शून्य;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Currently we only support 64x64 cursors */
	अगर (width != 64 || height != 64) अणु
		dev_dbg(dev->dev, "We currently only support 64x64 cursors\n");
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file_priv, handle);
	अगर (!obj) अणु
		ret = -ENOENT;
		जाओ unlock;
	पूर्ण

	अगर (obj->size < width * height * 4) अणु
		dev_dbg(dev->dev, "Buffer is too small\n");
		ret = -ENOMEM;
		जाओ unref_cursor;
	पूर्ण

	gt = container_of(obj, काष्ठा gtt_range, gem);

	/* Pin the memory पूर्णांकo the GTT */
	ret = psb_gtt_pin(gt);
	अगर (ret) अणु
		dev_err(dev->dev, "Can not pin down handle 0x%x\n", handle);
		जाओ unref_cursor;
	पूर्ण

	अगर (dev_priv->ops->cursor_needs_phys) अणु
		अगर (cursor_gt == शून्य) अणु
			dev_err(dev->dev, "No hardware cursor mem available");
			ret = -ENOMEM;
			जाओ unref_cursor;
		पूर्ण

		/* Prevent overflow */
		अगर (gt->npage > 4)
			cursor_pages = 4;
		अन्यथा
			cursor_pages = gt->npage;

		/* Copy the cursor to cursor mem */
		पंचांगp_dst = dev_priv->vram_addr + cursor_gt->offset;
		क्रम (i = 0; i < cursor_pages; i++) अणु
			पंचांगp_src = kmap(gt->pages[i]);
			स_नकल(पंचांगp_dst, पंचांगp_src, PAGE_SIZE);
			kunmap(gt->pages[i]);
			पंचांगp_dst += PAGE_SIZE;
		पूर्ण

		addr = gma_crtc->cursor_addr;
	पूर्ण अन्यथा अणु
		addr = gt->offset;
		gma_crtc->cursor_addr = addr;
	पूर्ण

	temp = 0;
	/* set the pipe क्रम the cursor */
	temp |= (pipe << 28);
	temp |= CURSOR_MODE_64_ARGB_AX | MCURSOR_GAMMA_ENABLE;

	अगर (gma_घातer_begin(dev, false)) अणु
		REG_WRITE(control, temp);
		REG_WRITE(base, addr);
		gma_घातer_end(dev);
	पूर्ण

	/* unpin the old bo */
	अगर (gma_crtc->cursor_obj) अणु
		gt = container_of(gma_crtc->cursor_obj, काष्ठा gtt_range, gem);
		psb_gtt_unpin(gt);
		drm_gem_object_put(gma_crtc->cursor_obj);
	पूर्ण

	gma_crtc->cursor_obj = obj;
unlock:
	वापस ret;

unref_cursor:
	drm_gem_object_put(obj);
	वापस ret;
पूर्ण

पूर्णांक gma_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	uपूर्णांक32_t temp = 0;
	uपूर्णांक32_t addr;

	अगर (x < 0) अणु
		temp |= (CURSOR_POS_SIGN << CURSOR_X_SHIFT);
		x = -x;
	पूर्ण
	अगर (y < 0) अणु
		temp |= (CURSOR_POS_SIGN << CURSOR_Y_SHIFT);
		y = -y;
	पूर्ण

	temp |= ((x & CURSOR_POS_MASK) << CURSOR_X_SHIFT);
	temp |= ((y & CURSOR_POS_MASK) << CURSOR_Y_SHIFT);

	addr = gma_crtc->cursor_addr;

	अगर (gma_घातer_begin(dev, false)) अणु
		REG_WRITE((pipe == 0) ? CURAPOS : CURBPOS, temp);
		REG_WRITE((pipe == 0) ? CURABASE : CURBBASE, addr);
		gma_घातer_end(dev);
	पूर्ण
	वापस 0;
पूर्ण

व्योम gma_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
	crtc_funcs->dpms(crtc, DRM_MODE_DPMS_OFF);
पूर्ण

व्योम gma_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
	crtc_funcs->dpms(crtc, DRM_MODE_DPMS_ON);
पूर्ण

व्योम gma_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा gtt_range *gt;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;

	crtc_funcs->dpms(crtc, DRM_MODE_DPMS_OFF);

	अगर (crtc->primary->fb) अणु
		gt = to_gtt_range(crtc->primary->fb->obj[0]);
		psb_gtt_unpin(gt);
	पूर्ण
पूर्ण

व्योम gma_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);

	kमुक्त(gma_crtc->crtc_state);
	drm_crtc_cleanup(crtc);
	kमुक्त(gma_crtc);
पूर्ण

पूर्णांक gma_crtc_page_flip(काष्ठा drm_crtc *crtc,
		       काष्ठा drm_framebuffer *fb,
		       काष्ठा drm_pending_vblank_event *event,
		       uपूर्णांक32_t page_flip_flags,
		       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा drm_framebuffer *current_fb = crtc->primary->fb;
	काष्ठा drm_framebuffer *old_fb = crtc->primary->old_fb;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!crtc_funcs->mode_set_base)
		वापस -EINVAL;

	/* Using mode_set_base requires the new fb to be set alपढ़ोy. */
	crtc->primary->fb = fb;

	अगर (event) अणु
		spin_lock_irqsave(&dev->event_lock, flags);

		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		gma_crtc->page_flip_event = event;

		/* Call this locked अगर we want an event at vblank पूर्णांकerrupt. */
		ret = crtc_funcs->mode_set_base(crtc, crtc->x, crtc->y, old_fb);
		अगर (ret) अणु
			gma_crtc->page_flip_event = शून्य;
			drm_crtc_vblank_put(crtc);
		पूर्ण

		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण अन्यथा अणु
		ret = crtc_funcs->mode_set_base(crtc, crtc->x, crtc->y, old_fb);
	पूर्ण

	/* Restore previous fb in हाल of failure. */
	अगर (ret)
		crtc->primary->fb = current_fb;

	वापस ret;
पूर्ण

पूर्णांक gma_crtc_set_config(काष्ठा drm_mode_set *set,
			काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev = set->crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret;

	अगर (!dev_priv->rpm_enabled)
		वापस drm_crtc_helper_set_config(set, ctx);

	pm_runसमय_क्रमbid(dev->dev);
	ret = drm_crtc_helper_set_config(set, ctx);
	pm_runसमय_allow(dev->dev);

	वापस ret;
पूर्ण

/*
 * Save HW states of given crtc
 */
व्योम gma_crtc_save(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा psb_पूर्णांकel_crtc_state *crtc_state = gma_crtc->crtc_state;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[gma_crtc->pipe];
	uपूर्णांक32_t palette_reg;
	पूर्णांक i;

	अगर (!crtc_state) अणु
		dev_err(dev->dev, "No CRTC state found\n");
		वापस;
	पूर्ण

	crtc_state->saveDSPCNTR = REG_READ(map->cntr);
	crtc_state->savePIPECONF = REG_READ(map->conf);
	crtc_state->savePIPESRC = REG_READ(map->src);
	crtc_state->saveFP0 = REG_READ(map->fp0);
	crtc_state->saveFP1 = REG_READ(map->fp1);
	crtc_state->saveDPLL = REG_READ(map->dpll);
	crtc_state->saveHTOTAL = REG_READ(map->htotal);
	crtc_state->saveHBLANK = REG_READ(map->hblank);
	crtc_state->saveHSYNC = REG_READ(map->hsync);
	crtc_state->saveVTOTAL = REG_READ(map->vtotal);
	crtc_state->saveVBLANK = REG_READ(map->vblank);
	crtc_state->saveVSYNC = REG_READ(map->vsync);
	crtc_state->saveDSPSTRIDE = REG_READ(map->stride);

	/* NOTE: DSPSIZE DSPPOS only क्रम psb */
	crtc_state->saveDSPSIZE = REG_READ(map->size);
	crtc_state->saveDSPPOS = REG_READ(map->pos);

	crtc_state->saveDSPBASE = REG_READ(map->base);

	palette_reg = map->palette;
	क्रम (i = 0; i < 256; ++i)
		crtc_state->savePalette[i] = REG_READ(palette_reg + (i << 2));
पूर्ण

/*
 * Restore HW states of given crtc
 */
व्योम gma_crtc_restore(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc =  to_gma_crtc(crtc);
	काष्ठा psb_पूर्णांकel_crtc_state *crtc_state = gma_crtc->crtc_state;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[gma_crtc->pipe];
	uपूर्णांक32_t palette_reg;
	पूर्णांक i;

	अगर (!crtc_state) अणु
		dev_err(dev->dev, "No crtc state\n");
		वापस;
	पूर्ण

	अगर (crtc_state->saveDPLL & DPLL_VCO_ENABLE) अणु
		REG_WRITE(map->dpll,
			crtc_state->saveDPLL & ~DPLL_VCO_ENABLE);
		REG_READ(map->dpll);
		udelay(150);
	पूर्ण

	REG_WRITE(map->fp0, crtc_state->saveFP0);
	REG_READ(map->fp0);

	REG_WRITE(map->fp1, crtc_state->saveFP1);
	REG_READ(map->fp1);

	REG_WRITE(map->dpll, crtc_state->saveDPLL);
	REG_READ(map->dpll);
	udelay(150);

	REG_WRITE(map->htotal, crtc_state->saveHTOTAL);
	REG_WRITE(map->hblank, crtc_state->saveHBLANK);
	REG_WRITE(map->hsync, crtc_state->saveHSYNC);
	REG_WRITE(map->vtotal, crtc_state->saveVTOTAL);
	REG_WRITE(map->vblank, crtc_state->saveVBLANK);
	REG_WRITE(map->vsync, crtc_state->saveVSYNC);
	REG_WRITE(map->stride, crtc_state->saveDSPSTRIDE);

	REG_WRITE(map->size, crtc_state->saveDSPSIZE);
	REG_WRITE(map->pos, crtc_state->saveDSPPOS);

	REG_WRITE(map->src, crtc_state->savePIPESRC);
	REG_WRITE(map->base, crtc_state->saveDSPBASE);
	REG_WRITE(map->conf, crtc_state->savePIPECONF);

	gma_रुको_क्रम_vblank(dev);

	REG_WRITE(map->cntr, crtc_state->saveDSPCNTR);
	REG_WRITE(map->base, crtc_state->saveDSPBASE);

	gma_रुको_क्रम_vblank(dev);

	palette_reg = map->palette;
	क्रम (i = 0; i < 256; ++i)
		REG_WRITE(palette_reg + (i << 2), crtc_state->savePalette[i]);
पूर्ण

व्योम gma_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs =
	    encoder->helper_निजी;
	/* lvds has its own version of prepare see psb_पूर्णांकel_lvds_prepare */
	encoder_funcs->dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

व्योम gma_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs =
	    encoder->helper_निजी;
	/* lvds has its own version of commit see psb_पूर्णांकel_lvds_commit */
	encoder_funcs->dpms(encoder, DRM_MODE_DPMS_ON);
पूर्ण

व्योम gma_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा gma_encoder *पूर्णांकel_encoder = to_gma_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(पूर्णांकel_encoder);
पूर्ण

/* Currently there is only a 1:1 mapping of encoders and connectors */
काष्ठा drm_encoder *gma_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);

	वापस &gma_encoder->base;
पूर्ण

व्योम gma_connector_attach_encoder(काष्ठा gma_connector *connector,
				  काष्ठा gma_encoder *encoder)
अणु
	connector->encoder = encoder;
	drm_connector_attach_encoder(&connector->base,
					  &encoder->base);
पूर्ण

#घोषणा GMA_PLL_INVALID(s) अणु /* DRM_ERROR(s); */ वापस false; पूर्ण

bool gma_pll_is_valid(काष्ठा drm_crtc *crtc,
		      स्थिर काष्ठा gma_limit_t *limit,
		      काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	अगर (घड़ी->p1 < limit->p1.min || limit->p1.max < घड़ी->p1)
		GMA_PLL_INVALID("p1 out of range");
	अगर (घड़ी->p < limit->p.min || limit->p.max < घड़ी->p)
		GMA_PLL_INVALID("p out of range");
	अगर (घड़ी->m2 < limit->m2.min || limit->m2.max < घड़ी->m2)
		GMA_PLL_INVALID("m2 out of range");
	अगर (घड़ी->m1 < limit->m1.min || limit->m1.max < घड़ी->m1)
		GMA_PLL_INVALID("m1 out of range");
	/* On CDV m1 is always 0 */
	अगर (घड़ी->m1 <= घड़ी->m2 && घड़ी->m1 != 0)
		GMA_PLL_INVALID("m1 <= m2 && m1 != 0");
	अगर (घड़ी->m < limit->m.min || limit->m.max < घड़ी->m)
		GMA_PLL_INVALID("m out of range");
	अगर (घड़ी->n < limit->n.min || limit->n.max < घड़ी->n)
		GMA_PLL_INVALID("n out of range");
	अगर (घड़ी->vco < limit->vco.min || limit->vco.max < घड़ी->vco)
		GMA_PLL_INVALID("vco out of range");
	/* XXX: We may need to be checking "Dot clock"
	 * depending on the multiplier, connector, etc.,
	 * rather than just a single range.
	 */
	अगर (घड़ी->करोt < limit->करोt.min || limit->करोt.max < घड़ी->करोt)
		GMA_PLL_INVALID("dot out of range");

	वापस true;
पूर्ण

bool gma_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
		       काष्ठा drm_crtc *crtc, पूर्णांक target, पूर्णांक refclk,
		       काष्ठा gma_घड़ी_प्रकार *best_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	स्थिर काष्ठा gma_घड़ी_funcs *घड़ी_funcs =
						to_gma_crtc(crtc)->घड़ी_funcs;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	पूर्णांक err = target;

	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS) &&
	    (REG_READ(LVDS) & LVDS_PORT_EN) != 0) अणु
		/*
		 * For LVDS, अगर the panel is on, just rely on its current
		 * settings क्रम dual-channel.  We haven't figured out how to
		 * reliably set up dअगरferent single/dual channel state, अगर we
		 * even can.
		 */
		अगर ((REG_READ(LVDS) & LVDS_CLKB_POWER_MASK) ==
		    LVDS_CLKB_POWER_UP)
			घड़ी.p2 = limit->p2.p2_fast;
		अन्यथा
			घड़ी.p2 = limit->p2.p2_slow;
	पूर्ण अन्यथा अणु
		अगर (target < limit->p2.करोt_limit)
			घड़ी.p2 = limit->p2.p2_slow;
		अन्यथा
			घड़ी.p2 = limit->p2.p2_fast;
	पूर्ण

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));

	/* m1 is always 0 on CDV so the ouपंचांगost loop will run just once */
	क्रम (घड़ी.m1 = limit->m1.min; घड़ी.m1 <= limit->m1.max; घड़ी.m1++) अणु
		क्रम (घड़ी.m2 = limit->m2.min;
		     (घड़ी.m2 < घड़ी.m1 || घड़ी.m1 == 0) &&
		      घड़ी.m2 <= limit->m2.max; घड़ी.m2++) अणु
			क्रम (घड़ी.n = limit->n.min;
			     घड़ी.n <= limit->n.max; घड़ी.n++) अणु
				क्रम (घड़ी.p1 = limit->p1.min;
				     घड़ी.p1 <= limit->p1.max;
				     घड़ी.p1++) अणु
					पूर्णांक this_err;

					घड़ी_funcs->घड़ी(refclk, &घड़ी);

					अगर (!घड़ी_funcs->pll_is_valid(crtc,
								limit, &घड़ी))
						जारी;

					this_err = असल(घड़ी.करोt - target);
					अगर (this_err < err) अणु
						*best_घड़ी = घड़ी;
						err = this_err;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err != target;
पूर्ण
