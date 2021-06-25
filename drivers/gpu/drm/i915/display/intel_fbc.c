<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
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
 */

/**
 * DOC: Frame Buffer Compression (FBC)
 *
 * FBC tries to save memory bandwidth (and so घातer consumption) by
 * compressing the amount of memory used by the display. It is total
 * transparent to user space and completely handled in the kernel.
 *
 * The benefits of FBC are mostly visible with solid backgrounds and
 * variation-less patterns. It comes from keeping the memory footprपूर्णांक small
 * and having fewer memory pages खोलोed and accessed क्रम refreshing the display.
 *
 * i915 is responsible to reserve stolen memory क्रम FBC and configure its
 * offset on proper रेजिस्टरs. The hardware takes care of all
 * compress/decompress. However there are many known हालs where we have to
 * क्रमcibly disable it to allow proper screen updates.
 */

#समावेश <drm/drm_fourcc.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fbc.h"
#समावेश "intel_frontbuffer.h"

/*
 * For SKL+, the plane source size used by the hardware is based on the value we
 * ग_लिखो to the PLANE_SIZE रेजिस्टर. For BDW-, the hardware looks at the value
 * we wrote to PIPESRC.
 */
अटल व्योम पूर्णांकel_fbc_get_plane_source_size(स्थिर काष्ठा पूर्णांकel_fbc_state_cache *cache,
					    पूर्णांक *width, पूर्णांक *height)
अणु
	अगर (width)
		*width = cache->plane.src_w;
	अगर (height)
		*height = cache->plane.src_h;
पूर्ण

अटल पूर्णांक पूर्णांकel_fbc_calculate_cfb_size(काष्ठा drm_i915_निजी *dev_priv,
					स्थिर काष्ठा पूर्णांकel_fbc_state_cache *cache)
अणु
	पूर्णांक lines;

	पूर्णांकel_fbc_get_plane_source_size(cache, शून्य, &lines);
	अगर (IS_DISPLAY_VER(dev_priv, 7))
		lines = min(lines, 2048);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8)
		lines = min(lines, 2560);

	/* Hardware needs the full buffer stride, not just the active area. */
	वापस lines * cache->fb.stride;
पूर्ण

अटल व्योम i8xx_fbc_deactivate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 fbc_ctl;

	/* Disable compression */
	fbc_ctl = पूर्णांकel_de_पढ़ो(dev_priv, FBC_CONTROL);
	अगर ((fbc_ctl & FBC_CTL_EN) == 0)
		वापस;

	fbc_ctl &= ~FBC_CTL_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, FBC_CONTROL, fbc_ctl);

	/* Wait क्रम compressing bit to clear */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, FBC_STATUS,
				    FBC_STAT_COMPRESSING, 10)) अणु
		drm_dbg_kms(&dev_priv->drm, "FBC idle timed out\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम i8xx_fbc_activate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	पूर्णांक cfb_pitch;
	पूर्णांक i;
	u32 fbc_ctl;

	/* Note: fbc.threshold == 1 क्रम i8xx */
	cfb_pitch = params->cfb_size / FBC_LL_SIZE;
	अगर (params->fb.stride < cfb_pitch)
		cfb_pitch = params->fb.stride;

	/* FBC_CTL wants 32B or 64B units */
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		cfb_pitch = (cfb_pitch / 32) - 1;
	अन्यथा
		cfb_pitch = (cfb_pitch / 64) - 1;

	/* Clear old tags */
	क्रम (i = 0; i < (FBC_LL_SIZE / 32) + 1; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, FBC_TAG(i), 0);

	अगर (IS_DISPLAY_VER(dev_priv, 4)) अणु
		u32 fbc_ctl2;

		/* Set it up... */
		fbc_ctl2 = FBC_CTL_FENCE_DBL | FBC_CTL_IDLE_IMM;
		fbc_ctl2 |= FBC_CTL_PLANE(params->crtc.i9xx_plane);
		अगर (params->fence_id >= 0)
			fbc_ctl2 |= FBC_CTL_CPU_FENCE;
		पूर्णांकel_de_ग_लिखो(dev_priv, FBC_CONTROL2, fbc_ctl2);
		पूर्णांकel_de_ग_लिखो(dev_priv, FBC_FENCE_OFF,
			       params->fence_y_offset);
	पूर्ण

	/* enable it... */
	fbc_ctl = FBC_CTL_INTERVAL(params->पूर्णांकerval);
	fbc_ctl |= FBC_CTL_EN | FBC_CTL_PERIODIC;
	अगर (IS_I945GM(dev_priv))
		fbc_ctl |= FBC_CTL_C3_IDLE; /* 945 needs special SR handling */
	fbc_ctl |= FBC_CTL_STRIDE(cfb_pitch & 0xff);
	अगर (params->fence_id >= 0)
		fbc_ctl |= FBC_CTL_FENCENO(params->fence_id);
	पूर्णांकel_de_ग_लिखो(dev_priv, FBC_CONTROL, fbc_ctl);
पूर्ण

अटल bool i8xx_fbc_is_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, FBC_CONTROL) & FBC_CTL_EN;
पूर्ण

अटल व्योम g4x_fbc_activate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;

	dpfc_ctl = DPFC_CTL_PLANE(params->crtc.i9xx_plane) | DPFC_SR_EN;
	अगर (params->fb.क्रमmat->cpp[0] == 2)
		dpfc_ctl |= DPFC_CTL_LIMIT_2X;
	अन्यथा
		dpfc_ctl |= DPFC_CTL_LIMIT_1X;

	अगर (params->fence_id >= 0) अणु
		dpfc_ctl |= DPFC_CTL_FENCE_EN | params->fence_id;
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_FENCE_YOFF,
			       params->fence_y_offset);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_FENCE_YOFF, 0);
	पूर्ण

	/* enable it... */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);
पूर्ण

अटल व्योम g4x_fbc_deactivate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dpfc_ctl;

	/* Disable compression */
	dpfc_ctl = पूर्णांकel_de_पढ़ो(dev_priv, DPFC_CONTROL);
	अगर (dpfc_ctl & DPFC_CTL_EN) अणु
		dpfc_ctl &= ~DPFC_CTL_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CONTROL, dpfc_ctl);
	पूर्ण
पूर्ण

अटल bool g4x_fbc_is_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, DPFC_CONTROL) & DPFC_CTL_EN;
पूर्ण

अटल व्योम i8xx_fbc_recompress(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	क्रमागत i9xx_plane_id i9xx_plane = params->crtc.i9xx_plane;

	spin_lock_irq(&dev_priv->uncore.lock);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPADDR(i9xx_plane),
			  पूर्णांकel_de_पढ़ो_fw(dev_priv, DSPADDR(i9xx_plane)));
	spin_unlock_irq(&dev_priv->uncore.lock);
पूर्ण

अटल व्योम i965_fbc_recompress(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	क्रमागत i9xx_plane_id i9xx_plane = params->crtc.i9xx_plane;

	spin_lock_irq(&dev_priv->uncore.lock);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSURF(i9xx_plane),
			  पूर्णांकel_de_पढ़ो_fw(dev_priv, DSPSURF(i9xx_plane)));
	spin_unlock_irq(&dev_priv->uncore.lock);
पूर्ण

/* This function क्रमces a CFB recompression through the nuke operation. */
अटल व्योम snb_fbc_recompress(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	trace_पूर्णांकel_fbc_nuke(fbc->crtc);

	पूर्णांकel_de_ग_लिखो(dev_priv, MSG_FBC_REND_STATE, FBC_REND_NUKE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, MSG_FBC_REND_STATE);
पूर्ण

अटल व्योम पूर्णांकel_fbc_recompress(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 6)
		snb_fbc_recompress(dev_priv);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4)
		i965_fbc_recompress(dev_priv);
	अन्यथा
		i8xx_fbc_recompress(dev_priv);
पूर्ण

अटल व्योम ilk_fbc_activate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;
	पूर्णांक threshold = dev_priv->fbc.threshold;

	dpfc_ctl = DPFC_CTL_PLANE(params->crtc.i9xx_plane);
	अगर (params->fb.क्रमmat->cpp[0] == 2)
		threshold++;

	चयन (threshold) अणु
	हाल 4:
	हाल 3:
		dpfc_ctl |= DPFC_CTL_LIMIT_4X;
		अवरोध;
	हाल 2:
		dpfc_ctl |= DPFC_CTL_LIMIT_2X;
		अवरोध;
	हाल 1:
		dpfc_ctl |= DPFC_CTL_LIMIT_1X;
		अवरोध;
	पूर्ण

	अगर (params->fence_id >= 0) अणु
		dpfc_ctl |= DPFC_CTL_FENCE_EN;
		अगर (IS_IRONLAKE(dev_priv))
			dpfc_ctl |= params->fence_id;
		अगर (IS_SANDYBRIDGE(dev_priv)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, SNB_DPFC_CTL_SA,
				       SNB_CPU_FENCE_ENABLE | params->fence_id);
			पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CPU_FENCE_OFFSET,
				       params->fence_y_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IS_SANDYBRIDGE(dev_priv)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, SNB_DPFC_CTL_SA, 0);
			पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CPU_FENCE_OFFSET, 0);
		पूर्ण
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_FENCE_YOFF,
		       params->fence_y_offset);
	/* enable it... */
	पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);

	पूर्णांकel_fbc_recompress(dev_priv);
पूर्ण

अटल व्योम ilk_fbc_deactivate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dpfc_ctl;

	/* Disable compression */
	dpfc_ctl = पूर्णांकel_de_पढ़ो(dev_priv, ILK_DPFC_CONTROL);
	अगर (dpfc_ctl & DPFC_CTL_EN) अणु
		dpfc_ctl &= ~DPFC_CTL_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_CONTROL, dpfc_ctl);
	पूर्ण
पूर्ण

अटल bool ilk_fbc_is_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, ILK_DPFC_CONTROL) & DPFC_CTL_EN;
पूर्ण

अटल व्योम gen7_fbc_activate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc_reg_params *params = &dev_priv->fbc.params;
	u32 dpfc_ctl;
	पूर्णांक threshold = dev_priv->fbc.threshold;

	/* Display WA #0529: skl, kbl, bxt. */
	अगर (IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv)) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, CHICKEN_MISC_4);

		val &= ~(FBC_STRIDE_OVERRIDE | FBC_STRIDE_MASK);

		अगर (params->gen9_wa_cfb_stride)
			val |= FBC_STRIDE_OVERRIDE | params->gen9_wa_cfb_stride;

		पूर्णांकel_de_ग_लिखो(dev_priv, CHICKEN_MISC_4, val);
	पूर्ण

	dpfc_ctl = 0;
	अगर (IS_IVYBRIDGE(dev_priv))
		dpfc_ctl |= IVB_DPFC_CTL_PLANE(params->crtc.i9xx_plane);

	अगर (params->fb.क्रमmat->cpp[0] == 2)
		threshold++;

	चयन (threshold) अणु
	हाल 4:
	हाल 3:
		dpfc_ctl |= DPFC_CTL_LIMIT_4X;
		अवरोध;
	हाल 2:
		dpfc_ctl |= DPFC_CTL_LIMIT_2X;
		अवरोध;
	हाल 1:
		dpfc_ctl |= DPFC_CTL_LIMIT_1X;
		अवरोध;
	पूर्ण

	अगर (params->fence_id >= 0) अणु
		dpfc_ctl |= IVB_DPFC_CTL_FENCE_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, SNB_DPFC_CTL_SA,
			       SNB_CPU_FENCE_ENABLE | params->fence_id);
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CPU_FENCE_OFFSET,
			       params->fence_y_offset);
	पूर्ण अन्यथा अगर (dev_priv->ggtt.num_fences) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, SNB_DPFC_CTL_SA, 0);
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CPU_FENCE_OFFSET, 0);
	पूर्ण

	अगर (dev_priv->fbc.false_color)
		dpfc_ctl |= FBC_CTL_FALSE_COLOR;

	पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_CONTROL, dpfc_ctl | DPFC_CTL_EN);

	पूर्णांकel_fbc_recompress(dev_priv);
पूर्ण

अटल bool पूर्णांकel_fbc_hw_is_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 5)
		वापस ilk_fbc_is_active(dev_priv);
	अन्यथा अगर (IS_GM45(dev_priv))
		वापस g4x_fbc_is_active(dev_priv);
	अन्यथा
		वापस i8xx_fbc_is_active(dev_priv);
पूर्ण

अटल व्योम पूर्णांकel_fbc_hw_activate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	trace_पूर्णांकel_fbc_activate(fbc->crtc);

	fbc->active = true;
	fbc->activated = true;

	अगर (DISPLAY_VER(dev_priv) >= 7)
		gen7_fbc_activate(dev_priv);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5)
		ilk_fbc_activate(dev_priv);
	अन्यथा अगर (IS_GM45(dev_priv))
		g4x_fbc_activate(dev_priv);
	अन्यथा
		i8xx_fbc_activate(dev_priv);
पूर्ण

अटल व्योम पूर्णांकel_fbc_hw_deactivate(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	trace_पूर्णांकel_fbc_deactivate(fbc->crtc);

	fbc->active = false;

	अगर (DISPLAY_VER(dev_priv) >= 5)
		ilk_fbc_deactivate(dev_priv);
	अन्यथा अगर (IS_GM45(dev_priv))
		g4x_fbc_deactivate(dev_priv);
	अन्यथा
		i8xx_fbc_deactivate(dev_priv);
पूर्ण

/**
 * पूर्णांकel_fbc_is_active - Is FBC active?
 * @dev_priv: i915 device instance
 *
 * This function is used to verअगरy the current state of FBC.
 *
 * FIXME: This should be tracked in the plane config eventually
 * instead of queried at runसमय क्रम most callers.
 */
bool पूर्णांकel_fbc_is_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->fbc.active;
पूर्ण

अटल व्योम पूर्णांकel_fbc_deactivate(काष्ठा drm_i915_निजी *dev_priv,
				 स्थिर अक्षर *reason)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	drm_WARN_ON(&dev_priv->drm, !mutex_is_locked(&fbc->lock));

	अगर (fbc->active)
		पूर्णांकel_fbc_hw_deactivate(dev_priv);

	fbc->no_fbc_reason = reason;
पूर्ण

अटल u64 पूर्णांकel_fbc_cfb_base_max(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 5 || IS_G4X(i915))
		वापस BIT_ULL(28);
	अन्यथा
		वापस BIT_ULL(32);
पूर्ण

अटल पूर्णांक find_compression_threshold(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा drm_mm_node *node,
				      अचिन्हित पूर्णांक size,
				      अचिन्हित पूर्णांक fb_cpp)
अणु
	पूर्णांक compression_threshold = 1;
	पूर्णांक ret;
	u64 end;

	/* The FBC hardware क्रम BDW/SKL करोesn't have access to the stolen
	 * reserved range size, so it always assumes the maximum (8mb) is used.
	 * If we enable FBC using a CFB on that memory range we'll get FIFO
	 * underruns, even अगर that range is not reserved by the BIOS. */
	अगर (IS_BROADWELL(dev_priv) || IS_GEN9_BC(dev_priv))
		end = resource_size(&dev_priv->dsm) - 8 * 1024 * 1024;
	अन्यथा
		end = U64_MAX;

	end = min(end, पूर्णांकel_fbc_cfb_base_max(dev_priv));

	/* HACK: This code depends on what we will करो in *_enable_fbc. If that
	 * code changes, this code needs to change as well.
	 *
	 * The enable_fbc code will attempt to use one of our 2 compression
	 * thresholds, thereक्रमe, in that हाल, we only have 1 resort.
	 */

	/* Try to over-allocate to reduce पुनः_स्मृतिations and fragmentation. */
	ret = i915_gem_stolen_insert_node_in_range(dev_priv, node, size <<= 1,
						   4096, 0, end);
	अगर (ret == 0)
		वापस compression_threshold;

again:
	/* HW's ability to limit the CFB is 1:4 */
	अगर (compression_threshold > 4 ||
	    (fb_cpp == 2 && compression_threshold == 2))
		वापस 0;

	ret = i915_gem_stolen_insert_node_in_range(dev_priv, node, size >>= 1,
						   4096, 0, end);
	अगर (ret && DISPLAY_VER(dev_priv) <= 4) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (ret) अणु
		compression_threshold <<= 1;
		जाओ again;
	पूर्ण अन्यथा अणु
		वापस compression_threshold;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_fbc_alloc_cfb(काष्ठा drm_i915_निजी *dev_priv,
			       अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक fb_cpp)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा drm_mm_node *compressed_llb;
	पूर्णांक ret;

	drm_WARN_ON(&dev_priv->drm,
		    drm_mm_node_allocated(&fbc->compressed_fb));

	ret = find_compression_threshold(dev_priv, &fbc->compressed_fb,
					 size, fb_cpp);
	अगर (!ret)
		जाओ err_llb;
	अन्यथा अगर (ret > 1) अणु
		drm_info_once(&dev_priv->drm,
			      "Reducing the compressed framebuffer size. This may lead to less power savings than a non-reduced-size. Try to increase stolen memory size if available in BIOS.\n");
	पूर्ण

	fbc->threshold = ret;

	अगर (DISPLAY_VER(dev_priv) >= 5)
		पूर्णांकel_de_ग_लिखो(dev_priv, ILK_DPFC_CB_BASE,
			       fbc->compressed_fb.start);
	अन्यथा अगर (IS_GM45(dev_priv)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPFC_CB_BASE,
			       fbc->compressed_fb.start);
	पूर्ण अन्यथा अणु
		compressed_llb = kzalloc(माप(*compressed_llb), GFP_KERNEL);
		अगर (!compressed_llb)
			जाओ err_fb;

		ret = i915_gem_stolen_insert_node(dev_priv, compressed_llb,
						  4096, 4096);
		अगर (ret)
			जाओ err_fb;

		fbc->compressed_llb = compressed_llb;

		GEM_BUG_ON(range_overflows_end_t(u64, dev_priv->dsm.start,
						 fbc->compressed_fb.start,
						 U32_MAX));
		GEM_BUG_ON(range_overflows_end_t(u64, dev_priv->dsm.start,
						 fbc->compressed_llb->start,
						 U32_MAX));
		पूर्णांकel_de_ग_लिखो(dev_priv, FBC_CFB_BASE,
			       dev_priv->dsm.start + fbc->compressed_fb.start);
		पूर्णांकel_de_ग_लिखो(dev_priv, FBC_LL_BASE,
			       dev_priv->dsm.start + compressed_llb->start);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "reserved %llu bytes of contiguous stolen space for FBC, threshold: %d\n",
		    fbc->compressed_fb.size, fbc->threshold);

	वापस 0;

err_fb:
	kमुक्त(compressed_llb);
	i915_gem_stolen_हटाओ_node(dev_priv, &fbc->compressed_fb);
err_llb:
	अगर (drm_mm_initialized(&dev_priv->mm.stolen))
		drm_info_once(&dev_priv->drm, "not enough stolen space for compressed buffer (need %d more bytes), disabling. Hint: you may be able to increase stolen memory size in the BIOS to avoid this.\n", size);
	वापस -ENOSPC;
पूर्ण

अटल व्योम __पूर्णांकel_fbc_cleanup_cfb(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (WARN_ON(पूर्णांकel_fbc_hw_is_active(dev_priv)))
		वापस;

	अगर (!drm_mm_node_allocated(&fbc->compressed_fb))
		वापस;

	अगर (fbc->compressed_llb) अणु
		i915_gem_stolen_हटाओ_node(dev_priv, fbc->compressed_llb);
		kमुक्त(fbc->compressed_llb);
	पूर्ण

	i915_gem_stolen_हटाओ_node(dev_priv, &fbc->compressed_fb);
पूर्ण

व्योम पूर्णांकel_fbc_cleanup_cfb(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस;

	mutex_lock(&fbc->lock);
	__पूर्णांकel_fbc_cleanup_cfb(dev_priv);
	mutex_unlock(&fbc->lock);
पूर्ण

अटल bool stride_is_valid(काष्ठा drm_i915_निजी *dev_priv,
			    u64 modअगरier, अचिन्हित पूर्णांक stride)
अणु
	/* This should have been caught earlier. */
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, (stride & (64 - 1)) != 0))
		वापस false;

	/* Below are the additional FBC restrictions. */
	अगर (stride < 512)
		वापस false;

	अगर (IS_DISPLAY_VER(dev_priv, 2) || IS_DISPLAY_VER(dev_priv, 3))
		वापस stride == 4096 || stride == 8192;

	अगर (IS_DISPLAY_VER(dev_priv, 4) && !IS_G4X(dev_priv) && stride < 2048)
		वापस false;

	/* Display WA #1105: skl,bxt,kbl,cfl,glk */
	अगर ((IS_DISPLAY_VER(dev_priv, 9) || IS_GEMINILAKE(dev_priv)) &&
	    modअगरier == DRM_FORMAT_MOD_LINEAR && stride & 511)
		वापस false;

	अगर (stride > 16384)
		वापस false;

	वापस true;
पूर्ण

अटल bool pixel_क्रमmat_is_valid(काष्ठा drm_i915_निजी *dev_priv,
				  u32 pixel_क्रमmat)
अणु
	चयन (pixel_क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
		वापस true;
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_RGB565:
		/* 16bpp not supported on gen2 */
		अगर (IS_DISPLAY_VER(dev_priv, 2))
			वापस false;
		/* WaFbcOnly1to1Ratio:ctg */
		अगर (IS_G4X(dev_priv))
			वापस false;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rotation_is_valid(काष्ठा drm_i915_निजी *dev_priv,
			      u32 pixel_क्रमmat, अचिन्हित पूर्णांक rotation)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 9 && pixel_क्रमmat == DRM_FORMAT_RGB565 &&
	    drm_rotation_90_or_270(rotation))
		वापस false;
	अन्यथा अगर (DISPLAY_VER(dev_priv) <= 4 && !IS_G4X(dev_priv) &&
		 rotation != DRM_MODE_ROTATE_0)
		वापस false;

	वापस true;
पूर्ण

/*
 * For some reason, the hardware tracking starts looking at whatever we
 * programmed as the display plane base address रेजिस्टर. It करोes not look at
 * the X and Y offset रेजिस्टरs. That's why we include the src x/y offsets
 * instead of just looking at the plane size.
 */
अटल bool पूर्णांकel_fbc_hw_tracking_covers_screen(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	अचिन्हित पूर्णांक effective_w, effective_h, max_w, max_h;

	अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		max_w = 5120;
		max_h = 4096;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8 || IS_HASWELL(dev_priv)) अणु
		max_w = 4096;
		max_h = 4096;
	पूर्ण अन्यथा अगर (IS_G4X(dev_priv) || DISPLAY_VER(dev_priv) >= 5) अणु
		max_w = 4096;
		max_h = 2048;
	पूर्ण अन्यथा अणु
		max_w = 2048;
		max_h = 1536;
	पूर्ण

	पूर्णांकel_fbc_get_plane_source_size(&fbc->state_cache, &effective_w,
					&effective_h);
	effective_w += fbc->state_cache.plane.adjusted_x;
	effective_h += fbc->state_cache.plane.adjusted_y;

	वापस effective_w <= max_w && effective_h <= max_h;
पूर्ण

अटल bool tiling_is_valid(काष्ठा drm_i915_निजी *dev_priv,
			    u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		अगर (DISPLAY_VER(dev_priv) >= 9)
			वापस true;
		वापस false;
	हाल I915_FORMAT_MOD_X_TILED:
	हाल I915_FORMAT_MOD_Y_TILED:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_fbc_update_state_cache(काष्ठा पूर्णांकel_crtc *crtc,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;
	काष्ठा drm_framebuffer *fb = plane_state->hw.fb;

	cache->plane.visible = plane_state->uapi.visible;
	अगर (!cache->plane.visible)
		वापस;

	cache->crtc.mode_flags = crtc_state->hw.adjusted_mode.flags;
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		cache->crtc.hsw_bdw_pixel_rate = crtc_state->pixel_rate;

	cache->plane.rotation = plane_state->hw.rotation;
	/*
	 * Src coordinates are alपढ़ोy rotated by 270 degrees क्रम
	 * the 90/270 degree plane rotation हालs (to match the
	 * GTT mapping), hence no need to account क्रम rotation here.
	 */
	cache->plane.src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	cache->plane.src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	cache->plane.adjusted_x = plane_state->view.color_plane[0].x;
	cache->plane.adjusted_y = plane_state->view.color_plane[0].y;

	cache->plane.pixel_blend_mode = plane_state->hw.pixel_blend_mode;

	cache->fb.क्रमmat = fb->क्रमmat;
	cache->fb.modअगरier = fb->modअगरier;

	/* FIXME is this correct? */
	cache->fb.stride = plane_state->view.color_plane[0].stride;
	अगर (drm_rotation_90_or_270(plane_state->hw.rotation))
		cache->fb.stride *= fb->क्रमmat->cpp[0];

	/* FBC1 compression पूर्णांकerval: arbitrary choice of 1 second */
	cache->पूर्णांकerval = drm_mode_vrefresh(&crtc_state->hw.adjusted_mode);

	cache->fence_y_offset = पूर्णांकel_plane_fence_y_offset(plane_state);

	drm_WARN_ON(&dev_priv->drm, plane_state->flags & PLANE_HAS_FENCE &&
		    !plane_state->vma->fence);

	अगर (plane_state->flags & PLANE_HAS_FENCE &&
	    plane_state->vma->fence)
		cache->fence_id = plane_state->vma->fence->id;
	अन्यथा
		cache->fence_id = -1;

	cache->psr2_active = crtc_state->has_psr2;
पूर्ण

अटल bool पूर्णांकel_fbc_cfb_size_changed(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	वापस पूर्णांकel_fbc_calculate_cfb_size(dev_priv, &fbc->state_cache) >
		fbc->compressed_fb.size * fbc->threshold;
पूर्ण

अटल u16 पूर्णांकel_fbc_gen9_wa_cfb_stride(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;

	अगर ((IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv)) &&
	    cache->fb.modअगरier != I915_FORMAT_MOD_X_TILED)
		वापस DIV_ROUND_UP(cache->plane.src_w, 32 * fbc->threshold) * 8;
	अन्यथा
		वापस 0;
पूर्ण

अटल bool पूर्णांकel_fbc_gen9_wa_cfb_stride_changed(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	वापस fbc->params.gen9_wa_cfb_stride != पूर्णांकel_fbc_gen9_wa_cfb_stride(dev_priv);
पूर्ण

अटल bool पूर्णांकel_fbc_can_enable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (पूर्णांकel_vgpu_active(dev_priv)) अणु
		fbc->no_fbc_reason = "VGPU is active";
		वापस false;
	पूर्ण

	अगर (!dev_priv->params.enable_fbc) अणु
		fbc->no_fbc_reason = "disabled per module param or by default";
		वापस false;
	पूर्ण

	अगर (fbc->underrun_detected) अणु
		fbc->no_fbc_reason = "underrun detected";
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool पूर्णांकel_fbc_can_activate(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;

	अगर (!पूर्णांकel_fbc_can_enable(dev_priv))
		वापस false;

	अगर (!cache->plane.visible) अणु
		fbc->no_fbc_reason = "primary plane not visible";
		वापस false;
	पूर्ण

	/* We करोn't need to use a state cache here since this inक्रमmation is
	 * global क्रम all CRTC.
	 */
	अगर (fbc->underrun_detected) अणु
		fbc->no_fbc_reason = "underrun detected";
		वापस false;
	पूर्ण

	अगर (cache->crtc.mode_flags & DRM_MODE_FLAG_INTERLACE) अणु
		fbc->no_fbc_reason = "incompatible mode";
		वापस false;
	पूर्ण

	अगर (!पूर्णांकel_fbc_hw_tracking_covers_screen(crtc)) अणु
		fbc->no_fbc_reason = "mode too large for compression";
		वापस false;
	पूर्ण

	/* The use of a CPU fence is one of two ways to detect ग_लिखोs by the
	 * CPU to the scanout and trigger updates to the FBC.
	 *
	 * The other method is by software tracking (see
	 * पूर्णांकel_fbc_invalidate/flush()), it will manually notअगरy FBC and nuke
	 * the current compressed buffer and recompress it.
	 *
	 * Note that is possible क्रम a tiled surface to be unmappable (and
	 * so have no fence associated with it) due to aperture स्थिरraपूर्णांकs
	 * at the समय of pinning.
	 *
	 * FIXME with 90/270 degree rotation we should use the fence on
	 * the normal GTT view (the rotated view करोesn't even have a
	 * fence). Would need changes to the FBC fence Y offset as well.
	 * For now this will effectively disable FBC with 90/270 degree
	 * rotation.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9 && cache->fence_id < 0) अणु
		fbc->no_fbc_reason = "framebuffer not tiled or fenced";
		वापस false;
	पूर्ण

	अगर (!pixel_क्रमmat_is_valid(dev_priv, cache->fb.क्रमmat->क्रमmat)) अणु
		fbc->no_fbc_reason = "pixel format is invalid";
		वापस false;
	पूर्ण

	अगर (!rotation_is_valid(dev_priv, cache->fb.क्रमmat->क्रमmat,
			       cache->plane.rotation)) अणु
		fbc->no_fbc_reason = "rotation unsupported";
		वापस false;
	पूर्ण

	अगर (!tiling_is_valid(dev_priv, cache->fb.modअगरier)) अणु
		fbc->no_fbc_reason = "tiling unsupported";
		वापस false;
	पूर्ण

	अगर (!stride_is_valid(dev_priv, cache->fb.modअगरier, cache->fb.stride)) अणु
		fbc->no_fbc_reason = "framebuffer stride not supported";
		वापस false;
	पूर्ण

	अगर (cache->plane.pixel_blend_mode != DRM_MODE_BLEND_PIXEL_NONE &&
	    cache->fb.क्रमmat->has_alpha) अणु
		fbc->no_fbc_reason = "per-pixel alpha blending is incompatible with FBC";
		वापस false;
	पूर्ण

	/* WaFbcExceedCdClockThreshold:hsw,bdw */
	अगर ((IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) &&
	    cache->crtc.hsw_bdw_pixel_rate >= dev_priv->cdclk.hw.cdclk * 95 / 100) अणु
		fbc->no_fbc_reason = "pixel rate is too big";
		वापस false;
	पूर्ण

	/* It is possible क्रम the required CFB size change without a
	 * crtc->disable + crtc->enable since it is possible to change the
	 * stride without triggering a full modeset. Since we try to
	 * over-allocate the CFB, there's a chance we may keep FBC enabled even
	 * अगर this happens, but अगर we exceed the current CFB size we'll have to
	 * disable FBC. Notice that it would be possible to disable FBC, रुको
	 * क्रम a frame, मुक्त the stolen node, then try to reenable FBC in हाल
	 * we didn't get any invalidate/deactivate calls, but this would require
	 * a lot of tracking just क्रम a specअगरic हाल. If we conclude it's an
	 * important हाल, we can implement it later. */
	अगर (पूर्णांकel_fbc_cfb_size_changed(dev_priv)) अणु
		fbc->no_fbc_reason = "CFB requirements changed";
		वापस false;
	पूर्ण

	/*
	 * Work around a problem on GEN9+ HW, where enabling FBC on a plane
	 * having a Y offset that isn't भागisible by 4 causes FIFO underrun
	 * and screen flicker.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 9 &&
	    (fbc->state_cache.plane.adjusted_y & 3)) अणु
		fbc->no_fbc_reason = "plane Y offset is misaligned";
		वापस false;
	पूर्ण

	/* Wa_22010751166: icl, ehl, tgl, dg1, rkl */
	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    (cache->plane.src_h + cache->plane.adjusted_y) % 4) अणु
		fbc->no_fbc_reason = "plane height + offset is non-modulo of 4";
		वापस false;
	पूर्ण

	/*
	 * Tigerlake is not supporting FBC with PSR2.
	 * Recommendation is to keep this combination disabled
	 * Bspec: 50422 HSD: 14010260002
	 */
	अगर (fbc->state_cache.psr2_active && IS_TIGERLAKE(dev_priv)) अणु
		fbc->no_fbc_reason = "not supported with PSR2";
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_fbc_get_reg_params(काष्ठा पूर्णांकel_crtc *crtc,
				     काष्ठा पूर्णांकel_fbc_reg_params *params)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;

	/* Since all our fields are पूर्णांकeger types, use स_रखो here so the
	 * comparison function can rely on स_भेद because the padding will be
	 * zero. */
	स_रखो(params, 0, माप(*params));

	params->fence_id = cache->fence_id;
	params->fence_y_offset = cache->fence_y_offset;

	params->पूर्णांकerval = cache->पूर्णांकerval;

	params->crtc.pipe = crtc->pipe;
	params->crtc.i9xx_plane = to_पूर्णांकel_plane(crtc->base.primary)->i9xx_plane;

	params->fb.क्रमmat = cache->fb.क्रमmat;
	params->fb.modअगरier = cache->fb.modअगरier;
	params->fb.stride = cache->fb.stride;

	params->cfb_size = पूर्णांकel_fbc_calculate_cfb_size(dev_priv, cache);

	params->gen9_wa_cfb_stride = cache->gen9_wa_cfb_stride;

	params->plane_visible = cache->plane.visible;
पूर्ण

अटल bool पूर्णांकel_fbc_can_flip_nuke(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	स्थिर काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;
	स्थिर काष्ठा पूर्णांकel_fbc_reg_params *params = &fbc->params;

	अगर (drm_atomic_crtc_needs_modeset(&crtc_state->uapi))
		वापस false;

	अगर (!params->plane_visible)
		वापस false;

	अगर (!पूर्णांकel_fbc_can_activate(crtc))
		वापस false;

	अगर (params->fb.क्रमmat != cache->fb.क्रमmat)
		वापस false;

	अगर (params->fb.modअगरier != cache->fb.modअगरier)
		वापस false;

	अगर (params->fb.stride != cache->fb.stride)
		वापस false;

	अगर (params->cfb_size != पूर्णांकel_fbc_calculate_cfb_size(dev_priv, cache))
		वापस false;

	अगर (params->gen9_wa_cfb_stride != cache->gen9_wa_cfb_stride)
		वापस false;

	वापस true;
पूर्ण

bool पूर्णांकel_fbc_pre_update(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		पूर्णांकel_atomic_get_new_plane_state(state, plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	स्थिर अक्षर *reason = "update pending";
	bool need_vblank_रुको = false;

	अगर (!plane->has_fbc || !plane_state)
		वापस need_vblank_रुको;

	mutex_lock(&fbc->lock);

	अगर (fbc->crtc != crtc)
		जाओ unlock;

	पूर्णांकel_fbc_update_state_cache(crtc, crtc_state, plane_state);
	fbc->flip_pending = true;

	अगर (!पूर्णांकel_fbc_can_flip_nuke(crtc_state)) अणु
		पूर्णांकel_fbc_deactivate(dev_priv, reason);

		/*
		 * Display WA #1198: glk+
		 * Need an extra vblank रुको between FBC disable and most plane
		 * updates. Bspec says this is only needed क्रम plane disable, but
		 * that is not true. Touching most plane रेजिस्टरs will cause the
		 * corruption to appear. Also SKL/derivatives करो not seem to be
		 * affected.
		 *
		 * TODO: could optimize this a bit by sampling the frame
		 * counter when we disable FBC (अगर it was alपढ़ोy करोne earlier)
		 * and skipping the extra vblank रुको beक्रमe the plane update
		 * अगर at least one frame has alपढ़ोy passed.
		 */
		अगर (fbc->activated &&
		    DISPLAY_VER(dev_priv) >= 10)
			need_vblank_रुको = true;
		fbc->activated = false;
	पूर्ण
unlock:
	mutex_unlock(&fbc->lock);

	वापस need_vblank_रुको;
पूर्ण

/**
 * __पूर्णांकel_fbc_disable - disable FBC
 * @dev_priv: i915 device instance
 *
 * This is the low level function that actually disables FBC. Callers should
 * grab the FBC lock.
 */
अटल व्योम __पूर्णांकel_fbc_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_crtc *crtc = fbc->crtc;

	drm_WARN_ON(&dev_priv->drm, !mutex_is_locked(&fbc->lock));
	drm_WARN_ON(&dev_priv->drm, !fbc->crtc);
	drm_WARN_ON(&dev_priv->drm, fbc->active);

	drm_dbg_kms(&dev_priv->drm, "Disabling FBC on pipe %c\n",
		    pipe_name(crtc->pipe));

	__पूर्णांकel_fbc_cleanup_cfb(dev_priv);

	fbc->crtc = शून्य;
पूर्ण

अटल व्योम __पूर्णांकel_fbc_post_update(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	drm_WARN_ON(&dev_priv->drm, !mutex_is_locked(&fbc->lock));

	अगर (fbc->crtc != crtc)
		वापस;

	fbc->flip_pending = false;

	अगर (!dev_priv->params.enable_fbc) अणु
		पूर्णांकel_fbc_deactivate(dev_priv, "disabled at runtime per module param");
		__पूर्णांकel_fbc_disable(dev_priv);

		वापस;
	पूर्ण

	पूर्णांकel_fbc_get_reg_params(crtc, &fbc->params);

	अगर (!पूर्णांकel_fbc_can_activate(crtc))
		वापस;

	अगर (!fbc->busy_bits)
		पूर्णांकel_fbc_hw_activate(dev_priv);
	अन्यथा
		पूर्णांकel_fbc_deactivate(dev_priv, "frontbuffer write");
पूर्ण

व्योम पूर्णांकel_fbc_post_update(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		पूर्णांकel_atomic_get_new_plane_state(state, plane);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!plane->has_fbc || !plane_state)
		वापस;

	mutex_lock(&fbc->lock);
	__पूर्णांकel_fbc_post_update(crtc);
	mutex_unlock(&fbc->lock);
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_fbc_get_frontbuffer_bit(काष्ठा पूर्णांकel_fbc *fbc)
अणु
	अगर (fbc->crtc)
		वापस to_पूर्णांकel_plane(fbc->crtc->base.primary)->frontbuffer_bit;
	अन्यथा
		वापस fbc->possible_framebuffer_bits;
पूर्ण

व्योम पूर्णांकel_fbc_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित पूर्णांक frontbuffer_bits,
			  क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस;

	अगर (origin == ORIGIN_GTT || origin == ORIGIN_FLIP)
		वापस;

	mutex_lock(&fbc->lock);

	fbc->busy_bits |= पूर्णांकel_fbc_get_frontbuffer_bit(fbc) & frontbuffer_bits;

	अगर (fbc->crtc && fbc->busy_bits)
		पूर्णांकel_fbc_deactivate(dev_priv, "frontbuffer write");

	mutex_unlock(&fbc->lock);
पूर्ण

व्योम पूर्णांकel_fbc_flush(काष्ठा drm_i915_निजी *dev_priv,
		     अचिन्हित पूर्णांक frontbuffer_bits, क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस;

	/*
	 * GTT tracking करोes not nuke the entire cfb
	 * so करोn't clear busy_bits set क्रम some other
	 * reason.
	 */
	अगर (origin == ORIGIN_GTT)
		वापस;

	mutex_lock(&fbc->lock);

	fbc->busy_bits &= ~frontbuffer_bits;

	अगर (origin == ORIGIN_FLIP)
		जाओ out;

	अगर (!fbc->busy_bits && fbc->crtc &&
	    (frontbuffer_bits & पूर्णांकel_fbc_get_frontbuffer_bit(fbc))) अणु
		अगर (fbc->active)
			पूर्णांकel_fbc_recompress(dev_priv);
		अन्यथा अगर (!fbc->flip_pending)
			__पूर्णांकel_fbc_post_update(fbc->crtc);
	पूर्ण

out:
	mutex_unlock(&fbc->lock);
पूर्ण

/**
 * पूर्णांकel_fbc_choose_crtc - select a CRTC to enable FBC on
 * @dev_priv: i915 device instance
 * @state: the atomic state काष्ठाure
 *
 * This function looks at the proposed state क्रम CRTCs and planes, then chooses
 * which pipe is going to have FBC by setting पूर्णांकel_crtc_state->enable_fbc to
 * true.
 *
 * Later, पूर्णांकel_fbc_enable is going to look क्रम state->enable_fbc and then maybe
 * enable FBC क्रम the chosen CRTC. If it करोes, it will set dev_priv->fbc.crtc.
 */
व्योम पूर्णांकel_fbc_choose_crtc(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_plane_state *plane_state;
	bool crtc_chosen = false;
	पूर्णांक i;

	mutex_lock(&fbc->lock);

	/* Does this atomic commit involve the CRTC currently tied to FBC? */
	अगर (fbc->crtc &&
	    !पूर्णांकel_atomic_get_new_crtc_state(state, fbc->crtc))
		जाओ out;

	अगर (!पूर्णांकel_fbc_can_enable(dev_priv))
		जाओ out;

	/* Simply choose the first CRTC that is compatible and has a visible
	 * plane. We could go क्रम fancier schemes such as checking the plane
	 * size, but this would just affect the few platक्रमms that करोn't tie FBC
	 * to pipe or plane A. */
	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(plane_state->hw.crtc);

		अगर (!plane->has_fbc)
			जारी;

		अगर (!plane_state->uapi.visible)
			जारी;

		crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

		crtc_state->enable_fbc = true;
		crtc_chosen = true;
		अवरोध;
	पूर्ण

	अगर (!crtc_chosen)
		fbc->no_fbc_reason = "no suitable CRTC for FBC";

out:
	mutex_unlock(&fbc->lock);
पूर्ण

/**
 * पूर्णांकel_fbc_enable: tries to enable FBC on the CRTC
 * @crtc: the CRTC
 * @state: corresponding &drm_crtc_state क्रम @crtc
 *
 * This function checks अगर the given CRTC was chosen क्रम FBC, then enables it अगर
 * possible. Notice that it करोesn't activate FBC. It is valid to call
 * पूर्णांकel_fbc_enable multiple बार क्रम the same pipe without an
 * पूर्णांकel_fbc_disable in the middle, as दीर्घ as it is deactivated.
 */
व्योम पूर्णांकel_fbc_enable(काष्ठा पूर्णांकel_atomic_state *state,
		      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		पूर्णांकel_atomic_get_new_plane_state(state, plane);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;
	काष्ठा पूर्णांकel_fbc_state_cache *cache = &fbc->state_cache;

	अगर (!plane->has_fbc || !plane_state)
		वापस;

	mutex_lock(&fbc->lock);

	अगर (fbc->crtc) अणु
		अगर (fbc->crtc != crtc ||
		    (!पूर्णांकel_fbc_cfb_size_changed(dev_priv) &&
		     !पूर्णांकel_fbc_gen9_wa_cfb_stride_changed(dev_priv)))
			जाओ out;

		__पूर्णांकel_fbc_disable(dev_priv);
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, fbc->active);

	पूर्णांकel_fbc_update_state_cache(crtc, crtc_state, plane_state);

	/* FIXME crtc_state->enable_fbc lies :( */
	अगर (!cache->plane.visible)
		जाओ out;

	अगर (पूर्णांकel_fbc_alloc_cfb(dev_priv,
				पूर्णांकel_fbc_calculate_cfb_size(dev_priv, cache),
				plane_state->hw.fb->क्रमmat->cpp[0])) अणु
		cache->plane.visible = false;
		fbc->no_fbc_reason = "not enough stolen memory";
		जाओ out;
	पूर्ण

	cache->gen9_wa_cfb_stride = पूर्णांकel_fbc_gen9_wa_cfb_stride(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Enabling FBC on pipe %c\n",
		    pipe_name(crtc->pipe));
	fbc->no_fbc_reason = "FBC enabled but not active yet\n";

	fbc->crtc = crtc;
out:
	mutex_unlock(&fbc->lock);
पूर्ण

/**
 * पूर्णांकel_fbc_disable - disable FBC अगर it's associated with crtc
 * @crtc: the CRTC
 *
 * This function disables FBC अगर it's associated with the provided CRTC.
 */
व्योम पूर्णांकel_fbc_disable(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!plane->has_fbc)
		वापस;

	mutex_lock(&fbc->lock);
	अगर (fbc->crtc == crtc)
		__पूर्णांकel_fbc_disable(dev_priv);
	mutex_unlock(&fbc->lock);
पूर्ण

/**
 * पूर्णांकel_fbc_global_disable - globally disable FBC
 * @dev_priv: i915 device instance
 *
 * This function disables FBC regardless of which CRTC is associated with it.
 */
व्योम पूर्णांकel_fbc_global_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस;

	mutex_lock(&fbc->lock);
	अगर (fbc->crtc) अणु
		drm_WARN_ON(&dev_priv->drm, fbc->crtc->active);
		__पूर्णांकel_fbc_disable(dev_priv);
	पूर्ण
	mutex_unlock(&fbc->lock);
पूर्ण

अटल व्योम पूर्णांकel_fbc_underrun_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, काष्ठा drm_i915_निजी, fbc.underrun_work);
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	mutex_lock(&fbc->lock);

	/* Maybe we were scheduled twice. */
	अगर (fbc->underrun_detected || !fbc->crtc)
		जाओ out;

	drm_dbg_kms(&dev_priv->drm, "Disabling FBC due to FIFO underrun.\n");
	fbc->underrun_detected = true;

	पूर्णांकel_fbc_deactivate(dev_priv, "FIFO underrun");
out:
	mutex_unlock(&fbc->lock);
पूर्ण

/*
 * पूर्णांकel_fbc_reset_underrun - reset FBC fअगरo underrun status.
 * @dev_priv: i915 device instance
 *
 * See पूर्णांकel_fbc_handle_fअगरo_underrun_irq(). For स्वतःmated testing we
 * want to re-enable FBC after an underrun to increase test coverage.
 */
पूर्णांक पूर्णांकel_fbc_reset_underrun(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	cancel_work_sync(&dev_priv->fbc.underrun_work);

	ret = mutex_lock_पूर्णांकerruptible(&dev_priv->fbc.lock);
	अगर (ret)
		वापस ret;

	अगर (dev_priv->fbc.underrun_detected) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Re-allowing FBC after fifo underrun\n");
		dev_priv->fbc.no_fbc_reason = "FIFO underrun cleared";
	पूर्ण

	dev_priv->fbc.underrun_detected = false;
	mutex_unlock(&dev_priv->fbc.lock);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_fbc_handle_fअगरo_underrun_irq - disable FBC when we get a FIFO underrun
 * @dev_priv: i915 device instance
 *
 * Without FBC, most underruns are harmless and करोn't really cause too many
 * problems, except क्रम an annoying message on dmesg. With FBC, underruns can
 * become black screens or even worse, especially when paired with bad
 * watermarks. So in order क्रम us to be on the safe side, completely disable FBC
 * in हाल we ever detect a FIFO underrun on any pipe. An underrun on any pipe
 * alपढ़ोy suggests that watermarks may be bad, so try to be as safe as
 * possible.
 *
 * This function is called from the IRQ handler.
 */
व्योम पूर्णांकel_fbc_handle_fअगरo_underrun_irq(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस;

	/* There's no guarantee that underrun_detected won't be set to true
	 * right after this check and beक्रमe the work is scheduled, but that's
	 * not a problem since we'll check it again under the work function
	 * जबतक FBC is locked. This check here is just to prevent us from
	 * unnecessarily scheduling the work, and it relies on the fact that we
	 * never चयन underrun_detect back to false after it's true. */
	अगर (READ_ONCE(fbc->underrun_detected))
		वापस;

	schedule_work(&fbc->underrun_work);
पूर्ण

/*
 * The DDX driver changes its behavior depending on the value it पढ़ोs from
 * i915.enable_fbc, so sanitize it by translating the शेष value पूर्णांकo either
 * 0 or 1 in order to allow it to know what's going on.
 *
 * Notice that this is करोne at driver initialization and we still allow user
 * space to change the value during runसमय without sanitizing it again. IGT
 * relies on being able to change i915.enable_fbc at runसमय.
 */
अटल पूर्णांक पूर्णांकel_sanitize_fbc_option(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (dev_priv->params.enable_fbc >= 0)
		वापस !!dev_priv->params.enable_fbc;

	अगर (!HAS_FBC(dev_priv))
		वापस 0;

	अगर (IS_BROADWELL(dev_priv) || DISPLAY_VER(dev_priv) >= 9)
		वापस 1;

	वापस 0;
पूर्ण

अटल bool need_fbc_vtd_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* WaFbcTurnOffFbcWhenHyperVisorIsUsed:skl,bxt */
	अगर (पूर्णांकel_vtd_active() &&
	    (IS_SKYLAKE(dev_priv) || IS_BROXTON(dev_priv))) अणु
		drm_info(&dev_priv->drm,
			 "Disabling framebuffer compression (FBC) to prevent screen flicker with VT-d enabled\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * पूर्णांकel_fbc_init - Initialize FBC
 * @dev_priv: the i915 device
 *
 * This function might be called during PM init process.
 */
व्योम पूर्णांकel_fbc_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

	INIT_WORK(&fbc->underrun_work, पूर्णांकel_fbc_underrun_work_fn);
	mutex_init(&fbc->lock);
	fbc->active = false;

	अगर (!drm_mm_initialized(&dev_priv->mm.stolen))
		mkग_लिखो_device_info(dev_priv)->display.has_fbc = false;

	अगर (need_fbc_vtd_wa(dev_priv))
		mkग_लिखो_device_info(dev_priv)->display.has_fbc = false;

	dev_priv->params.enable_fbc = पूर्णांकel_sanitize_fbc_option(dev_priv);
	drm_dbg_kms(&dev_priv->drm, "Sanitized enable_fbc value: %d\n",
		    dev_priv->params.enable_fbc);

	अगर (!HAS_FBC(dev_priv)) अणु
		fbc->no_fbc_reason = "unsupported by this chipset";
		वापस;
	पूर्ण

	/* We still करोn't have any sort of hardware state पढ़ोout क्रम FBC, so
	 * deactivate it in हाल the BIOS activated it to make sure software
	 * matches the hardware state. */
	अगर (पूर्णांकel_fbc_hw_is_active(dev_priv))
		पूर्णांकel_fbc_hw_deactivate(dev_priv);
पूर्ण
