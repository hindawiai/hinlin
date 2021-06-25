<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 *          Alex Deucher
 */

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/gcd.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_kms.h"

अटल व्योम avivo_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u16 *r, *g, *b;
	पूर्णांक i;

	DRM_DEBUG_KMS("%d\n", radeon_crtc->crtc_id);
	WREG32(AVIVO_DC_LUTA_CONTROL + radeon_crtc->crtc_offset, 0);

	WREG32(AVIVO_DC_LUTA_BLACK_OFFSET_BLUE + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_DC_LUTA_BLACK_OFFSET_GREEN + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_DC_LUTA_BLACK_OFFSET_RED + radeon_crtc->crtc_offset, 0);

	WREG32(AVIVO_DC_LUTA_WHITE_OFFSET_BLUE + radeon_crtc->crtc_offset, 0xffff);
	WREG32(AVIVO_DC_LUTA_WHITE_OFFSET_GREEN + radeon_crtc->crtc_offset, 0xffff);
	WREG32(AVIVO_DC_LUTA_WHITE_OFFSET_RED + radeon_crtc->crtc_offset, 0xffff);

	WREG32(AVIVO_DC_LUT_RW_SELECT, radeon_crtc->crtc_id);
	WREG32(AVIVO_DC_LUT_RW_MODE, 0);
	WREG32(AVIVO_DC_LUT_WRITE_EN_MASK, 0x0000003f);

	WREG8(AVIVO_DC_LUT_RW_INDEX, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(AVIVO_DC_LUT_30_COLOR,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	पूर्ण

	/* Only change bit 0 of LUT_SEL, other bits are set अन्यथाwhere */
	WREG32_P(AVIVO_D1GRPH_LUT_SEL + radeon_crtc->crtc_offset, radeon_crtc->crtc_id, ~1);
पूर्ण

अटल व्योम dce4_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u16 *r, *g, *b;
	पूर्णांक i;

	DRM_DEBUG_KMS("%d\n", radeon_crtc->crtc_id);
	WREG32(EVERGREEN_DC_LUT_CONTROL + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_BLUE + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_GREEN + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_RED + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_BLUE + radeon_crtc->crtc_offset, 0xffff);
	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_GREEN + radeon_crtc->crtc_offset, 0xffff);
	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_RED + radeon_crtc->crtc_offset, 0xffff);

	WREG32(EVERGREEN_DC_LUT_RW_MODE + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_WRITE_EN_MASK + radeon_crtc->crtc_offset, 0x00000007);

	WREG32(EVERGREEN_DC_LUT_RW_INDEX + radeon_crtc->crtc_offset, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(EVERGREEN_DC_LUT_30_COLOR + radeon_crtc->crtc_offset,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	पूर्ण
पूर्ण

अटल व्योम dce5_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u16 *r, *g, *b;
	पूर्णांक i;

	DRM_DEBUG_KMS("%d\n", radeon_crtc->crtc_id);

	msleep(10);

	WREG32(NI_INPUT_CSC_CONTROL + radeon_crtc->crtc_offset,
	       (NI_INPUT_CSC_GRPH_MODE(NI_INPUT_CSC_BYPASS) |
		NI_INPUT_CSC_OVL_MODE(NI_INPUT_CSC_BYPASS)));
	WREG32(NI_PRESCALE_GRPH_CONTROL + radeon_crtc->crtc_offset,
	       NI_GRPH_PRESCALE_BYPASS);
	WREG32(NI_PRESCALE_OVL_CONTROL + radeon_crtc->crtc_offset,
	       NI_OVL_PRESCALE_BYPASS);
	WREG32(NI_INPUT_GAMMA_CONTROL + radeon_crtc->crtc_offset,
	       (NI_GRPH_INPUT_GAMMA_MODE(NI_INPUT_GAMMA_USE_LUT) |
		NI_OVL_INPUT_GAMMA_MODE(NI_INPUT_GAMMA_USE_LUT)));

	WREG32(EVERGREEN_DC_LUT_CONTROL + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_BLUE + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_GREEN + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_BLACK_OFFSET_RED + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_BLUE + radeon_crtc->crtc_offset, 0xffff);
	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_GREEN + radeon_crtc->crtc_offset, 0xffff);
	WREG32(EVERGREEN_DC_LUT_WHITE_OFFSET_RED + radeon_crtc->crtc_offset, 0xffff);

	WREG32(EVERGREEN_DC_LUT_RW_MODE + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_DC_LUT_WRITE_EN_MASK + radeon_crtc->crtc_offset, 0x00000007);

	WREG32(EVERGREEN_DC_LUT_RW_INDEX + radeon_crtc->crtc_offset, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(EVERGREEN_DC_LUT_30_COLOR + radeon_crtc->crtc_offset,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	पूर्ण

	WREG32(NI_DEGAMMA_CONTROL + radeon_crtc->crtc_offset,
	       (NI_GRPH_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_OVL_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_ICON_DEGAMMA_MODE(NI_DEGAMMA_BYPASS) |
		NI_CURSOR_DEGAMMA_MODE(NI_DEGAMMA_BYPASS)));
	WREG32(NI_GAMUT_REMAP_CONTROL + radeon_crtc->crtc_offset,
	       (NI_GRPH_GAMUT_REMAP_MODE(NI_GAMUT_REMAP_BYPASS) |
		NI_OVL_GAMUT_REMAP_MODE(NI_GAMUT_REMAP_BYPASS)));
	WREG32(NI_REGAMMA_CONTROL + radeon_crtc->crtc_offset,
	       (NI_GRPH_REGAMMA_MODE(NI_REGAMMA_BYPASS) |
		NI_OVL_REGAMMA_MODE(NI_REGAMMA_BYPASS)));
	WREG32(NI_OUTPUT_CSC_CONTROL + radeon_crtc->crtc_offset,
	       (NI_OUTPUT_CSC_GRPH_MODE(radeon_crtc->output_csc) |
		NI_OUTPUT_CSC_OVL_MODE(NI_OUTPUT_CSC_BYPASS)));
	/* XXX match this to the depth of the crtc fmt block, move to modeset? */
	WREG32(0x6940 + radeon_crtc->crtc_offset, 0);
	अगर (ASIC_IS_DCE8(rdev)) अणु
		/* XXX this only needs to be programmed once per crtc at startup,
		 * not sure where the best place क्रम it is
		 */
		WREG32(CIK_ALPHA_CONTROL + radeon_crtc->crtc_offset,
		       CIK_CURSOR_ALPHA_BLND_ENA);
	पूर्ण
पूर्ण

अटल व्योम legacy_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u16 *r, *g, *b;
	पूर्णांक i;
	uपूर्णांक32_t dac2_cntl;

	dac2_cntl = RREG32(RADEON_DAC_CNTL2);
	अगर (radeon_crtc->crtc_id == 0)
		dac2_cntl &= (uपूर्णांक32_t)~RADEON_DAC2_PALETTE_ACC_CTL;
	अन्यथा
		dac2_cntl |= RADEON_DAC2_PALETTE_ACC_CTL;
	WREG32(RADEON_DAC_CNTL2, dac2_cntl);

	WREG8(RADEON_PALETTE_INDEX, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(RADEON_PALETTE_30_DATA,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	पूर्ण
पूर्ण

व्योम radeon_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (!crtc->enabled)
		वापस;

	अगर (ASIC_IS_DCE5(rdev))
		dce5_crtc_load_lut(crtc);
	अन्यथा अगर (ASIC_IS_DCE4(rdev))
		dce4_crtc_load_lut(crtc);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		avivo_crtc_load_lut(crtc);
	अन्यथा
		legacy_crtc_load_lut(crtc);
पूर्ण

अटल पूर्णांक radeon_crtc_gamma_set(काष्ठा drm_crtc *crtc, u16 *red, u16 *green,
				 u16 *blue, uपूर्णांक32_t size,
				 काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	radeon_crtc_load_lut(crtc);

	वापस 0;
पूर्ण

अटल व्योम radeon_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	drm_crtc_cleanup(crtc);
	destroy_workqueue(radeon_crtc->flip_queue);
	kमुक्त(radeon_crtc);
पूर्ण

/**
 * radeon_unpin_work_func - unpin old buffer object
 *
 * @__work: kernel work item
 *
 * Unpin the old frame buffer object outside of the पूर्णांकerrupt handler
 */
अटल व्योम radeon_unpin_work_func(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा radeon_flip_work *work =
		container_of(__work, काष्ठा radeon_flip_work, unpin_work);
	पूर्णांक r;

	/* unpin of the old buffer */
	r = radeon_bo_reserve(work->old_rbo, false);
	अगर (likely(r == 0)) अणु
		radeon_bo_unpin(work->old_rbo);
		radeon_bo_unreserve(work->old_rbo);
	पूर्ण अन्यथा
		DRM_ERROR("failed to reserve buffer after flip\n");

	drm_gem_object_put(&work->old_rbo->tbo.base);
	kमुक्त(work);
पूर्ण

व्योम radeon_crtc_handle_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	अचिन्हित दीर्घ flags;
	u32 update_pending;
	पूर्णांक vpos, hpos;

	/* can happen during initialization */
	अगर (radeon_crtc == शून्य)
		वापस;

	/* Skip the pageflip completion check below (based on polling) on
	 * asics which reliably support hw pageflip completion irqs. pflip
	 * irqs are a reliable and race-मुक्त method of handling pageflip
	 * completion detection. A use_pflipirq module parameter < 2 allows
	 * to override this in हाल of asics with faulty pflip irqs.
	 * A module parameter of 0 would only use this polling based path,
	 * a parameter of 1 would use pflip irq only as a backup to this
	 * path, as in Linux 3.16.
	 */
	अगर ((radeon_use_pflipirq == 2) && ASIC_IS_DCE4(rdev))
		वापस;

	spin_lock_irqsave(&rdev->ddev->event_lock, flags);
	अगर (radeon_crtc->flip_status != RADEON_FLIP_SUBMITTED) अणु
		DRM_DEBUG_DRIVER("radeon_crtc->flip_status = %d != "
				 "RADEON_FLIP_SUBMITTED(%d)\n",
				 radeon_crtc->flip_status,
				 RADEON_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
		वापस;
	पूर्ण

	update_pending = radeon_page_flip_pending(rdev, crtc_id);

	/* Has the pageflip alपढ़ोy completed in crtc, or is it certain
	 * to complete in this vblank? GET_DISTANCE_TO_VBLANKSTART provides
	 * distance to start of "fudged earlier" vblank in vpos, distance to
	 * start of real vblank in hpos. vpos >= 0 && hpos < 0 means we are in
	 * the last few scanlines beक्रमe start of real vblank, where the vblank
	 * irq can fire, so we have sampled update_pending a bit too early and
	 * know the flip will complete at leading edge of the upcoming real
	 * vblank. On pre-AVIVO hardware, flips also complete inside the real
	 * vblank, not only at leading edge, so अगर update_pending क्रम hpos >= 0
	 *  == inside real vblank, the flip will complete almost immediately.
	 * Note that this method of completion handling is still not 100% race
	 * मुक्त, as we could execute beक्रमe the radeon_flip_work_func managed
	 * to run and set the RADEON_FLIP_SUBMITTED status, thereby we no-op,
	 * but the flip still माला_लो programmed पूर्णांकo hw and completed during
	 * vblank, leading to a delayed emission of the flip completion event.
	 * This applies at least to pre-AVIVO hardware, where flips are always
	 * completing inside vblank, not only at leading edge of vblank.
	 */
	अगर (update_pending &&
	    (DRM_SCANOUTPOS_VALID &
	     radeon_get_crtc_scanoutpos(rdev->ddev, crtc_id,
					GET_DISTANCE_TO_VBLANKSTART,
					&vpos, &hpos, शून्य, शून्य,
					&rdev->mode_info.crtcs[crtc_id]->base.hwmode)) &&
	    ((vpos >= 0 && hpos < 0) || (hpos >= 0 && !ASIC_IS_AVIVO(rdev)))) अणु
		/* crtc didn't flip in this target vblank पूर्णांकerval,
		 * but flip is pending in crtc. Based on the current
		 * scanout position we know that the current frame is
		 * (nearly) complete and the flip will (likely)
		 * complete beक्रमe the start of the next frame.
		 */
		update_pending = 0;
	पूर्ण
	spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
	अगर (!update_pending)
		radeon_crtc_handle_flip(rdev, crtc_id);
पूर्ण

/**
 * radeon_crtc_handle_flip - page flip completed
 *
 * @rdev: radeon device poपूर्णांकer
 * @crtc_id: crtc number this event is क्रम
 *
 * Called when we are sure that a page flip क्रम this crtc is completed.
 */
व्योम radeon_crtc_handle_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	काष्ठा radeon_flip_work *work;
	अचिन्हित दीर्घ flags;

	/* this can happen at init */
	अगर (radeon_crtc == शून्य)
		वापस;

	spin_lock_irqsave(&rdev->ddev->event_lock, flags);
	work = radeon_crtc->flip_work;
	अगर (radeon_crtc->flip_status != RADEON_FLIP_SUBMITTED) अणु
		DRM_DEBUG_DRIVER("radeon_crtc->flip_status = %d != "
				 "RADEON_FLIP_SUBMITTED(%d)\n",
				 radeon_crtc->flip_status,
				 RADEON_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
		वापस;
	पूर्ण

	/* Pageflip completed. Clean up. */
	radeon_crtc->flip_status = RADEON_FLIP_NONE;
	radeon_crtc->flip_work = शून्य;

	/* wakeup userspace */
	अगर (work->event)
		drm_crtc_send_vblank_event(&radeon_crtc->base, work->event);

	spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);

	drm_crtc_vblank_put(&radeon_crtc->base);
	radeon_irq_kms_pflip_irq_put(rdev, work->crtc_id);
	queue_work(radeon_crtc->flip_queue, &work->unpin_work);
पूर्ण

/**
 * radeon_flip_work_func - page flip framebuffer
 *
 * @__work: kernel work item
 *
 * Wait क्रम the buffer object to become idle and करो the actual page flip
 */
अटल व्योम radeon_flip_work_func(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा radeon_flip_work *work =
		container_of(__work, काष्ठा radeon_flip_work, flip_work);
	काष्ठा radeon_device *rdev = work->rdev;
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[work->crtc_id];

	काष्ठा drm_crtc *crtc = &radeon_crtc->base;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;
	पूर्णांक vpos, hpos;

	करोwn_पढ़ो(&rdev->exclusive_lock);
	अगर (work->fence) अणु
		काष्ठा radeon_fence *fence;

		fence = to_radeon_fence(work->fence);
		अगर (fence && fence->rdev == rdev) अणु
			r = radeon_fence_रुको(fence, false);
			अगर (r == -EDEADLK) अणु
				up_पढ़ो(&rdev->exclusive_lock);
				करो अणु
					r = radeon_gpu_reset(rdev);
				पूर्ण जबतक (r == -EAGAIN);
				करोwn_पढ़ो(&rdev->exclusive_lock);
			पूर्ण
		पूर्ण अन्यथा
			r = dma_fence_रुको(work->fence, false);

		अगर (r)
			DRM_ERROR("failed to wait on page flip fence (%d)!\n", r);

		/* We जारी with the page flip even अगर we failed to रुको on
		 * the fence, otherwise the DRM core and userspace will be
		 * confused about which BO the CRTC is scanning out
		 */

		dma_fence_put(work->fence);
		work->fence = शून्य;
	पूर्ण

	/* Wait until we're out of the vertical blank period beक्रमe the one
	 * targeted by the flip. Always रुको on pre DCE4 to aव्योम races with
	 * flip completion handling from vblank irq, as these old asics करोn't
	 * have reliable pageflip completion पूर्णांकerrupts.
	 */
	जबतक (radeon_crtc->enabled &&
		(radeon_get_crtc_scanoutpos(dev, work->crtc_id, 0,
					    &vpos, &hpos, शून्य, शून्य,
					    &crtc->hwmode)
		& (DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK)) ==
		(DRM_SCANOUTPOS_VALID | DRM_SCANOUTPOS_IN_VBLANK) &&
		(!ASIC_IS_AVIVO(rdev) ||
		((पूर्णांक) (work->target_vblank -
		crtc->funcs->get_vblank_counter(crtc)) > 0)))
		usleep_range(1000, 2000);

	/* We borrow the event spin lock क्रम protecting flip_status */
	spin_lock_irqsave(&crtc->dev->event_lock, flags);

	/* set the proper पूर्णांकerrupt */
	radeon_irq_kms_pflip_irq_get(rdev, radeon_crtc->crtc_id);

	/* करो the flip (mmio) */
	radeon_page_flip(rdev, radeon_crtc->crtc_id, work->base, work->async);

	radeon_crtc->flip_status = RADEON_FLIP_SUBMITTED;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	up_पढ़ो(&rdev->exclusive_lock);
पूर्ण

अटल पूर्णांक radeon_crtc_page_flip_target(काष्ठा drm_crtc *crtc,
					काष्ठा drm_framebuffer *fb,
					काष्ठा drm_pending_vblank_event *event,
					uपूर्णांक32_t page_flip_flags,
					uपूर्णांक32_t target,
					काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_gem_object *obj;
	काष्ठा radeon_flip_work *work;
	काष्ठा radeon_bo *new_rbo;
	uपूर्णांक32_t tiling_flags, pitch_pixels;
	uपूर्णांक64_t base;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	work = kzalloc(माप *work, GFP_KERNEL);
	अगर (work == शून्य)
		वापस -ENOMEM;

	INIT_WORK(&work->flip_work, radeon_flip_work_func);
	INIT_WORK(&work->unpin_work, radeon_unpin_work_func);

	work->rdev = rdev;
	work->crtc_id = radeon_crtc->crtc_id;
	work->event = event;
	work->async = (page_flip_flags & DRM_MODE_PAGE_FLIP_ASYNC) != 0;

	/* schedule unpin of the old buffer */
	obj = crtc->primary->fb->obj[0];

	/* take a reference to the old object */
	drm_gem_object_get(obj);
	work->old_rbo = gem_to_radeon_bo(obj);

	obj = fb->obj[0];
	new_rbo = gem_to_radeon_bo(obj);

	/* pin the new buffer */
	DRM_DEBUG_DRIVER("flip-ioctl() cur_rbo = %p, new_rbo = %p\n",
			 work->old_rbo, new_rbo);

	r = radeon_bo_reserve(new_rbo, false);
	अगर (unlikely(r != 0)) अणु
		DRM_ERROR("failed to reserve new rbo buffer before flip\n");
		जाओ cleanup;
	पूर्ण
	/* Only 27 bit offset क्रम legacy CRTC */
	r = radeon_bo_pin_restricted(new_rbo, RADEON_GEM_DOMAIN_VRAM,
				     ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27, &base);
	अगर (unlikely(r != 0)) अणु
		radeon_bo_unreserve(new_rbo);
		r = -EINVAL;
		DRM_ERROR("failed to pin new rbo buffer before flip\n");
		जाओ cleanup;
	पूर्ण
	work->fence = dma_fence_get(dma_resv_get_excl(new_rbo->tbo.base.resv));
	radeon_bo_get_tiling_flags(new_rbo, &tiling_flags, शून्य);
	radeon_bo_unreserve(new_rbo);

	अगर (!ASIC_IS_AVIVO(rdev)) अणु
		/* crtc offset is from display base addr not FB location */
		base -= radeon_crtc->legacy_display_base_addr;
		pitch_pixels = fb->pitches[0] / fb->क्रमmat->cpp[0];

		अगर (tiling_flags & RADEON_TILING_MACRO) अणु
			अगर (ASIC_IS_R300(rdev)) अणु
				base &= ~0x7ff;
			पूर्ण अन्यथा अणु
				पूर्णांक byteshअगरt = fb->क्रमmat->cpp[0] * 8 >> 4;
				पूर्णांक tile_addr = (((crtc->y >> 3) * pitch_pixels +  crtc->x) >> (8 - byteshअगरt)) << 11;
				base += tile_addr + ((crtc->x << byteshअगरt) % 256) + ((crtc->y % 8) << 8);
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक offset = crtc->y * pitch_pixels + crtc->x;
			चयन (fb->क्रमmat->cpp[0] * 8) अणु
			हाल 8:
			शेष:
				offset *= 1;
				अवरोध;
			हाल 15:
			हाल 16:
				offset *= 2;
				अवरोध;
			हाल 24:
				offset *= 3;
				अवरोध;
			हाल 32:
				offset *= 4;
				अवरोध;
			पूर्ण
			base += offset;
		पूर्ण
		base &= ~7;
	पूर्ण
	work->base = base;
	work->target_vblank = target - (uपूर्णांक32_t)drm_crtc_vblank_count(crtc) +
		crtc->funcs->get_vblank_counter(crtc);

	/* We borrow the event spin lock क्रम protecting flip_work */
	spin_lock_irqsave(&crtc->dev->event_lock, flags);

	अगर (radeon_crtc->flip_status != RADEON_FLIP_NONE) अणु
		DRM_DEBUG_DRIVER("flip queue: crtc already busy\n");
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		r = -EBUSY;
		जाओ pflip_cleanup;
	पूर्ण
	radeon_crtc->flip_status = RADEON_FLIP_PENDING;
	radeon_crtc->flip_work = work;

	/* update crtc fb */
	crtc->primary->fb = fb;

	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

	queue_work(radeon_crtc->flip_queue, &work->flip_work);
	वापस 0;

pflip_cleanup:
	अगर (unlikely(radeon_bo_reserve(new_rbo, false) != 0)) अणु
		DRM_ERROR("failed to reserve new rbo in error path\n");
		जाओ cleanup;
	पूर्ण
	radeon_bo_unpin(new_rbo);
	radeon_bo_unreserve(new_rbo);

cleanup:
	drm_gem_object_put(&work->old_rbo->tbo.base);
	dma_fence_put(work->fence);
	kमुक्त(work);
	वापस r;
पूर्ण

अटल पूर्णांक
radeon_crtc_set_config(काष्ठा drm_mode_set *set,
		       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev;
	काष्ठा radeon_device *rdev;
	काष्ठा drm_crtc *crtc;
	bool active = false;
	पूर्णांक ret;

	अगर (!set || !set->crtc)
		वापस -EINVAL;

	dev = set->crtc->dev;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	ret = drm_crtc_helper_set_config(set, ctx);

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head)
		अगर (crtc->enabled)
			active = true;

	pm_runसमय_mark_last_busy(dev->dev);

	rdev = dev->dev_निजी;
	/* अगर we have active crtcs and we करोn't have a घातer ref,
	   take the current one */
	अगर (active && !rdev->have_disp_घातer_ref) अणु
		rdev->have_disp_घातer_ref = true;
		वापस ret;
	पूर्ण
	/* अगर we have no active crtcs, then drop the घातer ref
	   we got beक्रमe */
	अगर (!active && rdev->have_disp_घातer_ref) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		rdev->have_disp_घातer_ref = false;
	पूर्ण

	/* drop the घातer reference we got coming in here */
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs radeon_crtc_funcs = अणु
	.cursor_set2 = radeon_crtc_cursor_set2,
	.cursor_move = radeon_crtc_cursor_move,
	.gamma_set = radeon_crtc_gamma_set,
	.set_config = radeon_crtc_set_config,
	.destroy = radeon_crtc_destroy,
	.page_flip_target = radeon_crtc_page_flip_target,
	.get_vblank_counter = radeon_get_vblank_counter_kms,
	.enable_vblank = radeon_enable_vblank_kms,
	.disable_vblank = radeon_disable_vblank_kms,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल व्योम radeon_crtc_init(काष्ठा drm_device *dev, पूर्णांक index)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc;

	radeon_crtc = kzalloc(माप(काष्ठा radeon_crtc) + (RADEONFB_CONN_LIMIT * माप(काष्ठा drm_connector *)), GFP_KERNEL);
	अगर (radeon_crtc == शून्य)
		वापस;

	drm_crtc_init(dev, &radeon_crtc->base, &radeon_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&radeon_crtc->base, 256);
	radeon_crtc->crtc_id = index;
	radeon_crtc->flip_queue = alloc_workqueue("radeon-crtc", WQ_HIGHPRI, 0);
	rdev->mode_info.crtcs[index] = radeon_crtc;

	अगर (rdev->family >= CHIP_BONAIRE) अणु
		radeon_crtc->max_cursor_width = CIK_CURSOR_WIDTH;
		radeon_crtc->max_cursor_height = CIK_CURSOR_HEIGHT;
	पूर्ण अन्यथा अणु
		radeon_crtc->max_cursor_width = CURSOR_WIDTH;
		radeon_crtc->max_cursor_height = CURSOR_HEIGHT;
	पूर्ण
	dev->mode_config.cursor_width = radeon_crtc->max_cursor_width;
	dev->mode_config.cursor_height = radeon_crtc->max_cursor_height;

#अगर 0
	radeon_crtc->mode_set.crtc = &radeon_crtc->base;
	radeon_crtc->mode_set.connectors = (काष्ठा drm_connector **)(radeon_crtc + 1);
	radeon_crtc->mode_set.num_connectors = 0;
#पूर्ण_अगर

	अगर (rdev->is_atom_bios && (ASIC_IS_AVIVO(rdev) || radeon_r4xx_atom))
		radeon_atombios_init_crtc(dev, radeon_crtc);
	अन्यथा
		radeon_legacy_init_crtc(dev, radeon_crtc);
पूर्ण

अटल स्थिर अक्षर *encoder_names[38] = अणु
	"NONE",
	"INTERNAL_LVDS",
	"INTERNAL_TMDS1",
	"INTERNAL_TMDS2",
	"INTERNAL_DAC1",
	"INTERNAL_DAC2",
	"INTERNAL_SDVOA",
	"INTERNAL_SDVOB",
	"SI170B",
	"CH7303",
	"CH7301",
	"INTERNAL_DVO1",
	"EXTERNAL_SDVOA",
	"EXTERNAL_SDVOB",
	"TITFP513",
	"INTERNAL_LVTM1",
	"VT1623",
	"HDMI_SI1930",
	"HDMI_INTERNAL",
	"INTERNAL_KLDSCP_TMDS1",
	"INTERNAL_KLDSCP_DVO1",
	"INTERNAL_KLDSCP_DAC1",
	"INTERNAL_KLDSCP_DAC2",
	"SI178",
	"MVPU_FPGA",
	"INTERNAL_DDI",
	"VT1625",
	"HDMI_SI1932",
	"DP_AN9801",
	"DP_DP501",
	"INTERNAL_UNIPHY",
	"INTERNAL_KLDSCP_LVTMA",
	"INTERNAL_UNIPHY1",
	"INTERNAL_UNIPHY2",
	"NUTMEG",
	"TRAVIS",
	"INTERNAL_VCE",
	"INTERNAL_UNIPHY3",
पूर्ण;

अटल स्थिर अक्षर *hpd_names[6] = अणु
	"HPD1",
	"HPD2",
	"HPD3",
	"HPD4",
	"HPD5",
	"HPD6",
पूर्ण;

अटल व्योम radeon_prपूर्णांक_display_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;
	uपूर्णांक32_t devices;
	पूर्णांक i = 0;

	DRM_INFO("Radeon Display Connectors\n");
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		DRM_INFO("Connector %d:\n", i);
		DRM_INFO("  %s\n", connector->name);
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			DRM_INFO("  %s\n", hpd_names[radeon_connector->hpd.hpd]);
		अगर (radeon_connector->ddc_bus) अणु
			DRM_INFO("  DDC: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				 radeon_connector->ddc_bus->rec.mask_clk_reg,
				 radeon_connector->ddc_bus->rec.mask_data_reg,
				 radeon_connector->ddc_bus->rec.a_clk_reg,
				 radeon_connector->ddc_bus->rec.a_data_reg,
				 radeon_connector->ddc_bus->rec.en_clk_reg,
				 radeon_connector->ddc_bus->rec.en_data_reg,
				 radeon_connector->ddc_bus->rec.y_clk_reg,
				 radeon_connector->ddc_bus->rec.y_data_reg);
			अगर (radeon_connector->router.ddc_valid)
				DRM_INFO("  DDC Router 0x%x/0x%x\n",
					 radeon_connector->router.ddc_mux_control_pin,
					 radeon_connector->router.ddc_mux_state);
			अगर (radeon_connector->router.cd_valid)
				DRM_INFO("  Clock/Data Router 0x%x/0x%x\n",
					 radeon_connector->router.cd_mux_control_pin,
					 radeon_connector->router.cd_mux_state);
		पूर्ण अन्यथा अणु
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_VGA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVII ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVID ||
			    connector->connector_type == DRM_MODE_CONNECTOR_DVIA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
			    connector->connector_type == DRM_MODE_CONNECTOR_HDMIB)
				DRM_INFO("  DDC: no ddc bus - possible BIOS bug - please report to xorg-driver-ati@lists.x.org\n");
		पूर्ण
		DRM_INFO("  Encoders:\n");
		list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
			radeon_encoder = to_radeon_encoder(encoder);
			devices = radeon_encoder->devices & radeon_connector->devices;
			अगर (devices) अणु
				अगर (devices & ATOM_DEVICE_CRT1_SUPPORT)
					DRM_INFO("    CRT1: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_CRT2_SUPPORT)
					DRM_INFO("    CRT2: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_LCD1_SUPPORT)
					DRM_INFO("    LCD1: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP1_SUPPORT)
					DRM_INFO("    DFP1: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP2_SUPPORT)
					DRM_INFO("    DFP2: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP3_SUPPORT)
					DRM_INFO("    DFP3: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP4_SUPPORT)
					DRM_INFO("    DFP4: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP5_SUPPORT)
					DRM_INFO("    DFP5: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_DFP6_SUPPORT)
					DRM_INFO("    DFP6: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_TV1_SUPPORT)
					DRM_INFO("    TV1: %s\n", encoder_names[radeon_encoder->encoder_id]);
				अगर (devices & ATOM_DEVICE_CV_SUPPORT)
					DRM_INFO("    CV: %s\n", encoder_names[radeon_encoder->encoder_id]);
			पूर्ण
		पूर्ण
		i++;
	पूर्ण
पूर्ण

अटल bool radeon_setup_enc_conn(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	bool ret = false;

	अगर (rdev->bios) अणु
		अगर (rdev->is_atom_bios) अणु
			ret = radeon_get_atom_connector_info_from_supported_devices_table(dev);
			अगर (!ret)
				ret = radeon_get_atom_connector_info_from_object_table(dev);
		पूर्ण अन्यथा अणु
			ret = radeon_get_legacy_connector_info_from_bios(dev);
			अगर (!ret)
				ret = radeon_get_legacy_connector_info_from_table(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!ASIC_IS_AVIVO(rdev))
			ret = radeon_get_legacy_connector_info_from_table(dev);
	पूर्ण
	अगर (ret) अणु
		radeon_setup_encoder_clones(dev);
		radeon_prपूर्णांक_display_setup(dev);
	पूर्ण

	वापस ret;
पूर्ण

/* avivo */

/**
 * avivo_reduce_ratio - fractional number reduction
 *
 * @nom: nominator
 * @den: denominator
 * @nom_min: minimum value क्रम nominator
 * @den_min: minimum value क्रम denominator
 *
 * Find the greatest common भागisor and apply it on both nominator and
 * denominator, but make nominator and denominator are at least as large
 * as their minimum values.
 */
अटल व्योम avivo_reduce_ratio(अचिन्हित *nom, अचिन्हित *den,
			       अचिन्हित nom_min, अचिन्हित den_min)
अणु
	अचिन्हित पंचांगp;

	/* reduce the numbers to a simpler ratio */
	पंचांगp = gcd(*nom, *den);
	*nom /= पंचांगp;
	*den /= पंचांगp;

	/* make sure nominator is large enough */
	अगर (*nom < nom_min) अणु
		पंचांगp = DIV_ROUND_UP(nom_min, *nom);
		*nom *= पंचांगp;
		*den *= पंचांगp;
	पूर्ण

	/* make sure the denominator is large enough */
	अगर (*den < den_min) अणु
		पंचांगp = DIV_ROUND_UP(den_min, *den);
		*nom *= पंचांगp;
		*den *= पंचांगp;
	पूर्ण
पूर्ण

/**
 * avivo_get_fb_ref_भाग - feedback and ref भागider calculation
 *
 * @nom: nominator
 * @den: denominator
 * @post_भाग: post भागider
 * @fb_भाग_max: feedback भागider maximum
 * @ref_भाग_max: reference भागider maximum
 * @fb_भाग: resulting feedback भागider
 * @ref_भाग: resulting reference भागider
 *
 * Calculate feedback and reference भागider क्रम a given post भागider. Makes
 * sure we stay within the limits.
 */
अटल व्योम avivo_get_fb_ref_भाग(अचिन्हित nom, अचिन्हित den, अचिन्हित post_भाग,
				 अचिन्हित fb_भाग_max, अचिन्हित ref_भाग_max,
				 अचिन्हित *fb_भाग, अचिन्हित *ref_भाग)
अणु
	/* limit reference * post भागider to a maximum */
	ref_भाग_max = max(min(100 / post_भाग, ref_भाग_max), 1u);

	/* get matching reference and feedback भागider */
	*ref_भाग = min(max(den/post_भाग, 1u), ref_भाग_max);
	*fb_भाग = DIV_ROUND_CLOSEST(nom * *ref_भाग * post_भाग, den);

	/* limit fb भागider to its maximum */
	अगर (*fb_भाग > fb_भाग_max) अणु
		*ref_भाग = (*ref_भाग * fb_भाग_max)/(*fb_भाग);
		*fb_भाग = fb_भाग_max;
	पूर्ण
पूर्ण

/**
 * radeon_compute_pll_avivo - compute PLL paramaters
 *
 * @pll: inक्रमmation about the PLL
 * @freq: target frequency
 * @करोt_घड़ी_p: resulting pixel घड़ी
 * @fb_भाग_p: resulting feedback भागider
 * @frac_fb_भाग_p: fractional part of the feedback भागider
 * @ref_भाग_p: resulting reference भागider
 * @post_भाग_p: resulting reference भागider
 *
 * Try to calculate the PLL parameters to generate the given frequency:
 * करोt_घड़ी = (ref_freq * feedback_भाग) / (ref_भाग * post_भाग)
 */
व्योम radeon_compute_pll_avivo(काष्ठा radeon_pll *pll,
			      u32 freq,
			      u32 *करोt_घड़ी_p,
			      u32 *fb_भाग_p,
			      u32 *frac_fb_भाग_p,
			      u32 *ref_भाग_p,
			      u32 *post_भाग_p)
अणु
	अचिन्हित target_घड़ी = pll->flags & RADEON_PLL_USE_FRAC_FB_DIV ?
		freq : freq / 10;

	अचिन्हित fb_भाग_min, fb_भाग_max, fb_भाग;
	अचिन्हित post_भाग_min, post_भाग_max, post_भाग;
	अचिन्हित ref_भाग_min, ref_भाग_max, ref_भाग;
	अचिन्हित post_भाग_best, dअगरf_best;
	अचिन्हित nom, den;

	/* determine allowed feedback भागider range */
	fb_भाग_min = pll->min_feedback_भाग;
	fb_भाग_max = pll->max_feedback_भाग;

	अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) अणु
		fb_भाग_min *= 10;
		fb_भाग_max *= 10;
	पूर्ण

	/* determine allowed ref भागider range */
	अगर (pll->flags & RADEON_PLL_USE_REF_DIV)
		ref_भाग_min = pll->reference_भाग;
	अन्यथा
		ref_भाग_min = pll->min_ref_भाग;

	अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV &&
	    pll->flags & RADEON_PLL_USE_REF_DIV)
		ref_भाग_max = pll->reference_भाग;
	अन्यथा अगर (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP)
		/* fix क्रम problems on RS880 */
		ref_भाग_max = min(pll->max_ref_भाग, 7u);
	अन्यथा
		ref_भाग_max = pll->max_ref_भाग;

	/* determine allowed post भागider range */
	अगर (pll->flags & RADEON_PLL_USE_POST_DIV) अणु
		post_भाग_min = pll->post_भाग;
		post_भाग_max = pll->post_भाग;
	पूर्ण अन्यथा अणु
		अचिन्हित vco_min, vco_max;

		अगर (pll->flags & RADEON_PLL_IS_LCD) अणु
			vco_min = pll->lcd_pll_out_min;
			vco_max = pll->lcd_pll_out_max;
		पूर्ण अन्यथा अणु
			vco_min = pll->pll_out_min;
			vco_max = pll->pll_out_max;
		पूर्ण

		अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) अणु
			vco_min *= 10;
			vco_max *= 10;
		पूर्ण

		post_भाग_min = vco_min / target_घड़ी;
		अगर ((target_घड़ी * post_भाग_min) < vco_min)
			++post_भाग_min;
		अगर (post_भाग_min < pll->min_post_भाग)
			post_भाग_min = pll->min_post_भाग;

		post_भाग_max = vco_max / target_घड़ी;
		अगर ((target_घड़ी * post_भाग_max) > vco_max)
			--post_भाग_max;
		अगर (post_भाग_max > pll->max_post_भाग)
			post_भाग_max = pll->max_post_भाग;
	पूर्ण

	/* represent the searched ratio as fractional number */
	nom = target_घड़ी;
	den = pll->reference_freq;

	/* reduce the numbers to a simpler ratio */
	avivo_reduce_ratio(&nom, &den, fb_भाग_min, post_भाग_min);

	/* now search क्रम a post भागider */
	अगर (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP)
		post_भाग_best = post_भाग_min;
	अन्यथा
		post_भाग_best = post_भाग_max;
	dअगरf_best = ~0;

	क्रम (post_भाग = post_भाग_min; post_भाग <= post_भाग_max; ++post_भाग) अणु
		अचिन्हित dअगरf;
		avivo_get_fb_ref_भाग(nom, den, post_भाग, fb_भाग_max,
				     ref_भाग_max, &fb_भाग, &ref_भाग);
		dअगरf = असल(target_घड़ी - (pll->reference_freq * fb_भाग) /
			(ref_भाग * post_भाग));

		अगर (dअगरf < dअगरf_best || (dअगरf == dअगरf_best &&
		    !(pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP))) अणु

			post_भाग_best = post_भाग;
			dअगरf_best = dअगरf;
		पूर्ण
	पूर्ण
	post_भाग = post_भाग_best;

	/* get the feedback and reference भागider क्रम the optimal value */
	avivo_get_fb_ref_भाग(nom, den, post_भाग, fb_भाग_max, ref_भाग_max,
			     &fb_भाग, &ref_भाग);

	/* reduce the numbers to a simpler ratio once more */
	/* this also makes sure that the reference भागider is large enough */
	avivo_reduce_ratio(&fb_भाग, &ref_भाग, fb_भाग_min, ref_भाग_min);

	/* aव्योम high jitter with small fractional भागiders */
	अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV && (fb_भाग % 10)) अणु
		fb_भाग_min = max(fb_भाग_min, (9 - (fb_भाग % 10)) * 20 + 50);
		अगर (fb_भाग < fb_भाग_min) अणु
			अचिन्हित पंचांगp = DIV_ROUND_UP(fb_भाग_min, fb_भाग);
			fb_भाग *= पंचांगp;
			ref_भाग *= पंचांगp;
		पूर्ण
	पूर्ण

	/* and finally save the result */
	अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) अणु
		*fb_भाग_p = fb_भाग / 10;
		*frac_fb_भाग_p = fb_भाग % 10;
	पूर्ण अन्यथा अणु
		*fb_भाग_p = fb_भाग;
		*frac_fb_भाग_p = 0;
	पूर्ण

	*करोt_घड़ी_p = ((pll->reference_freq * *fb_भाग_p * 10) +
			(pll->reference_freq * *frac_fb_भाग_p)) /
		       (ref_भाग * post_भाग * 10);
	*ref_भाग_p = ref_भाग;
	*post_भाग_p = post_भाग;

	DRM_DEBUG_KMS("%d - %d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      freq, *करोt_घड़ी_p * 10, *fb_भाग_p, *frac_fb_भाग_p,
		      ref_भाग, post_भाग);
पूर्ण

/* pre-avivo */
अटल अंतरभूत uपूर्णांक32_t radeon_भाग(uपूर्णांक64_t n, uपूर्णांक32_t d)
अणु
	n += d / 2;

	करो_भाग(n, d);
	वापस n;
पूर्ण

व्योम radeon_compute_pll_legacy(काष्ठा radeon_pll *pll,
			       uपूर्णांक64_t freq,
			       uपूर्णांक32_t *करोt_घड़ी_p,
			       uपूर्णांक32_t *fb_भाग_p,
			       uपूर्णांक32_t *frac_fb_भाग_p,
			       uपूर्णांक32_t *ref_भाग_p,
			       uपूर्णांक32_t *post_भाग_p)
अणु
	uपूर्णांक32_t min_ref_भाग = pll->min_ref_भाग;
	uपूर्णांक32_t max_ref_भाग = pll->max_ref_भाग;
	uपूर्णांक32_t min_post_भाग = pll->min_post_भाग;
	uपूर्णांक32_t max_post_भाग = pll->max_post_भाग;
	uपूर्णांक32_t min_fractional_feed_भाग = 0;
	uपूर्णांक32_t max_fractional_feed_भाग = 0;
	uपूर्णांक32_t best_vco = pll->best_vco;
	uपूर्णांक32_t best_post_भाग = 1;
	uपूर्णांक32_t best_ref_भाग = 1;
	uपूर्णांक32_t best_feedback_भाग = 1;
	uपूर्णांक32_t best_frac_feedback_भाग = 0;
	uपूर्णांक32_t best_freq = -1;
	uपूर्णांक32_t best_error = 0xffffffff;
	uपूर्णांक32_t best_vco_dअगरf = 1;
	uपूर्णांक32_t post_भाग;
	u32 pll_out_min, pll_out_max;

	DRM_DEBUG_KMS("PLL freq %llu %u %u\n", freq, pll->min_ref_भाग, pll->max_ref_भाग);
	freq = freq * 1000;

	अगर (pll->flags & RADEON_PLL_IS_LCD) अणु
		pll_out_min = pll->lcd_pll_out_min;
		pll_out_max = pll->lcd_pll_out_max;
	पूर्ण अन्यथा अणु
		pll_out_min = pll->pll_out_min;
		pll_out_max = pll->pll_out_max;
	पूर्ण

	अगर (pll_out_min > 64800)
		pll_out_min = 64800;

	अगर (pll->flags & RADEON_PLL_USE_REF_DIV)
		min_ref_भाग = max_ref_भाग = pll->reference_भाग;
	अन्यथा अणु
		जबतक (min_ref_भाग < max_ref_भाग-1) अणु
			uपूर्णांक32_t mid = (min_ref_भाग + max_ref_भाग) / 2;
			uपूर्णांक32_t pll_in = pll->reference_freq / mid;
			अगर (pll_in < pll->pll_in_min)
				max_ref_भाग = mid;
			अन्यथा अगर (pll_in > pll->pll_in_max)
				min_ref_भाग = mid;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (pll->flags & RADEON_PLL_USE_POST_DIV)
		min_post_भाग = max_post_भाग = pll->post_भाग;

	अगर (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) अणु
		min_fractional_feed_भाग = pll->min_frac_feedback_भाग;
		max_fractional_feed_भाग = pll->max_frac_feedback_भाग;
	पूर्ण

	क्रम (post_भाग = max_post_भाग; post_भाग >= min_post_भाग; --post_भाग) अणु
		uपूर्णांक32_t ref_भाग;

		अगर ((pll->flags & RADEON_PLL_NO_ODD_POST_DIV) && (post_भाग & 1))
			जारी;

		/* legacy radeons only have a few post_भागs */
		अगर (pll->flags & RADEON_PLL_LEGACY) अणु
			अगर ((post_भाग == 5) ||
			    (post_भाग == 7) ||
			    (post_भाग == 9) ||
			    (post_भाग == 10) ||
			    (post_भाग == 11) ||
			    (post_भाग == 13) ||
			    (post_भाग == 14) ||
			    (post_भाग == 15))
				जारी;
		पूर्ण

		क्रम (ref_भाग = min_ref_भाग; ref_भाग <= max_ref_भाग; ++ref_भाग) अणु
			uपूर्णांक32_t feedback_भाग, current_freq = 0, error, vco_dअगरf;
			uपूर्णांक32_t pll_in = pll->reference_freq / ref_भाग;
			uपूर्णांक32_t min_feed_भाग = pll->min_feedback_भाग;
			uपूर्णांक32_t max_feed_भाग = pll->max_feedback_भाग + 1;

			अगर (pll_in < pll->pll_in_min || pll_in > pll->pll_in_max)
				जारी;

			जबतक (min_feed_भाग < max_feed_भाग) अणु
				uपूर्णांक32_t vco;
				uपूर्णांक32_t min_frac_feed_भाग = min_fractional_feed_भाग;
				uपूर्णांक32_t max_frac_feed_भाग = max_fractional_feed_भाग + 1;
				uपूर्णांक32_t frac_feedback_भाग;
				uपूर्णांक64_t पंचांगp;

				feedback_भाग = (min_feed_भाग + max_feed_भाग) / 2;

				पंचांगp = (uपूर्णांक64_t)pll->reference_freq * feedback_भाग;
				vco = radeon_भाग(पंचांगp, ref_भाग);

				अगर (vco < pll_out_min) अणु
					min_feed_भाग = feedback_भाग + 1;
					जारी;
				पूर्ण अन्यथा अगर (vco > pll_out_max) अणु
					max_feed_भाग = feedback_भाग;
					जारी;
				पूर्ण

				जबतक (min_frac_feed_भाग < max_frac_feed_भाग) अणु
					frac_feedback_भाग = (min_frac_feed_भाग + max_frac_feed_भाग) / 2;
					पंचांगp = (uपूर्णांक64_t)pll->reference_freq * 10000 * feedback_भाग;
					पंचांगp += (uपूर्णांक64_t)pll->reference_freq * 1000 * frac_feedback_भाग;
					current_freq = radeon_भाग(पंचांगp, ref_भाग * post_भाग);

					अगर (pll->flags & RADEON_PLL_PREFER_CLOSEST_LOWER) अणु
						अगर (freq < current_freq)
							error = 0xffffffff;
						अन्यथा
							error = freq - current_freq;
					पूर्ण अन्यथा
						error = असल(current_freq - freq);
					vco_dअगरf = असल(vco - best_vco);

					अगर ((best_vco == 0 && error < best_error) ||
					    (best_vco != 0 &&
					     ((best_error > 100 && error < best_error - 100) ||
					      (असल(error - best_error) < 100 && vco_dअगरf < best_vco_dअगरf)))) अणु
						best_post_भाग = post_भाग;
						best_ref_भाग = ref_भाग;
						best_feedback_भाग = feedback_भाग;
						best_frac_feedback_भाग = frac_feedback_भाग;
						best_freq = current_freq;
						best_error = error;
						best_vco_dअगरf = vco_dअगरf;
					पूर्ण अन्यथा अगर (current_freq == freq) अणु
						अगर (best_freq == -1) अणु
							best_post_भाग = post_भाग;
							best_ref_भाग = ref_भाग;
							best_feedback_भाग = feedback_भाग;
							best_frac_feedback_भाग = frac_feedback_भाग;
							best_freq = current_freq;
							best_error = error;
							best_vco_dअगरf = vco_dअगरf;
						पूर्ण अन्यथा अगर (((pll->flags & RADEON_PLL_PREFER_LOW_REF_DIV) && (ref_भाग < best_ref_भाग)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_REF_DIV) && (ref_भाग > best_ref_भाग)) ||
							   ((pll->flags & RADEON_PLL_PREFER_LOW_FB_DIV) && (feedback_भाग < best_feedback_भाग)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_FB_DIV) && (feedback_भाग > best_feedback_भाग)) ||
							   ((pll->flags & RADEON_PLL_PREFER_LOW_POST_DIV) && (post_भाग < best_post_भाग)) ||
							   ((pll->flags & RADEON_PLL_PREFER_HIGH_POST_DIV) && (post_भाग > best_post_भाग))) अणु
							best_post_भाग = post_भाग;
							best_ref_भाग = ref_भाग;
							best_feedback_भाग = feedback_भाग;
							best_frac_feedback_भाग = frac_feedback_भाग;
							best_freq = current_freq;
							best_error = error;
							best_vco_dअगरf = vco_dअगरf;
						पूर्ण
					पूर्ण
					अगर (current_freq < freq)
						min_frac_feed_भाग = frac_feedback_भाग + 1;
					अन्यथा
						max_frac_feed_भाग = frac_feedback_भाग;
				पूर्ण
				अगर (current_freq < freq)
					min_feed_भाग = feedback_भाग + 1;
				अन्यथा
					max_feed_भाग = feedback_भाग;
			पूर्ण
		पूर्ण
	पूर्ण

	*करोt_घड़ी_p = best_freq / 10000;
	*fb_भाग_p = best_feedback_भाग;
	*frac_fb_भाग_p = best_frac_feedback_भाग;
	*ref_भाग_p = best_ref_भाग;
	*post_भाग_p = best_post_भाग;
	DRM_DEBUG_KMS("%lld %d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      (दीर्घ दीर्घ)freq,
		      best_freq / 1000, best_feedback_भाग, best_frac_feedback_भाग,
		      best_ref_भाग, best_post_भाग);

पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs radeon_fb_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

पूर्णांक
radeon_framebuffer_init(काष्ठा drm_device *dev,
			काष्ठा drm_framebuffer *fb,
			स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret;
	fb->obj[0] = obj;
	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);
	ret = drm_framebuffer_init(dev, fb, &radeon_fb_funcs);
	अगर (ret) अणु
		fb->obj[0] = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा drm_framebuffer *
radeon_user_framebuffer_create(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;

	obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[0]);
	अगर (obj ==  शून्य) अणु
		dev_err(dev->dev, "No GEM object associated to handle 0x%08X, "
			"can't create framebuffer\n", mode_cmd->handles[0]);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	/* Handle is imported dma-buf, so cannot be migrated to VRAM क्रम scanout */
	अगर (obj->import_attach) अणु
		DRM_DEBUG_KMS("Cannot create framebuffer from imported dma_buf\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (fb == शून्य) अणु
		drm_gem_object_put(obj);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ret = radeon_framebuffer_init(dev, fb, mode_cmd, obj);
	अगर (ret) अणु
		kमुक्त(fb);
		drm_gem_object_put(obj);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस fb;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs radeon_mode_funcs = अणु
	.fb_create = radeon_user_framebuffer_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_पंचांगds_pll_क्रमागत_list[] =
अणु	अणु 0, "driver" पूर्ण,
	अणु 1, "bios" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_tv_std_क्रमागत_list[] =
अणु	अणु TV_STD_NTSC, "ntsc" पूर्ण,
	अणु TV_STD_PAL, "pal" पूर्ण,
	अणु TV_STD_PAL_M, "pal-m" पूर्ण,
	अणु TV_STD_PAL_60, "pal-60" पूर्ण,
	अणु TV_STD_NTSC_J, "ntsc-j" पूर्ण,
	अणु TV_STD_SCART_PAL, "scart-pal" पूर्ण,
	अणु TV_STD_PAL_CN, "pal-cn" पूर्ण,
	अणु TV_STD_SECAM, "secam" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_underscan_क्रमागत_list[] =
अणु	अणु UNDERSCAN_OFF, "off" पूर्ण,
	अणु UNDERSCAN_ON, "on" पूर्ण,
	अणु UNDERSCAN_AUTO, "auto" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_audio_क्रमागत_list[] =
अणु	अणु RADEON_AUDIO_DISABLE, "off" पूर्ण,
	अणु RADEON_AUDIO_ENABLE, "on" पूर्ण,
	अणु RADEON_AUDIO_AUTO, "auto" पूर्ण,
पूर्ण;

/* XXX support dअगरferent dither options? spatial, temporal, both, etc. */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_dither_क्रमागत_list[] =
अणु	अणु RADEON_FMT_DITHER_DISABLE, "off" पूर्ण,
	अणु RADEON_FMT_DITHER_ENABLE, "on" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list radeon_output_csc_क्रमागत_list[] =
अणु	अणु RADEON_OUTPUT_CSC_BYPASS, "bypass" पूर्ण,
	अणु RADEON_OUTPUT_CSC_TVRGB, "tvrgb" पूर्ण,
	अणु RADEON_OUTPUT_CSC_YCBCR601, "ycbcr601" पूर्ण,
	अणु RADEON_OUTPUT_CSC_YCBCR709, "ycbcr709" पूर्ण,
पूर्ण;

अटल पूर्णांक radeon_modeset_create_props(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक sz;

	अगर (rdev->is_atom_bios) अणु
		rdev->mode_info.coherent_mode_property =
			drm_property_create_range(rdev->ddev, 0 , "coherent", 0, 1);
		अगर (!rdev->mode_info.coherent_mode_property)
			वापस -ENOMEM;
	पूर्ण

	अगर (!ASIC_IS_AVIVO(rdev)) अणु
		sz = ARRAY_SIZE(radeon_पंचांगds_pll_क्रमागत_list);
		rdev->mode_info.पंचांगds_pll_property =
			drm_property_create_क्रमागत(rdev->ddev, 0,
					    "tmds_pll",
					    radeon_पंचांगds_pll_क्रमागत_list, sz);
	पूर्ण

	rdev->mode_info.load_detect_property =
		drm_property_create_range(rdev->ddev, 0, "load detection", 0, 1);
	अगर (!rdev->mode_info.load_detect_property)
		वापस -ENOMEM;

	drm_mode_create_scaling_mode_property(rdev->ddev);

	sz = ARRAY_SIZE(radeon_tv_std_क्रमागत_list);
	rdev->mode_info.tv_std_property =
		drm_property_create_क्रमागत(rdev->ddev, 0,
				    "tv standard",
				    radeon_tv_std_क्रमागत_list, sz);

	sz = ARRAY_SIZE(radeon_underscan_क्रमागत_list);
	rdev->mode_info.underscan_property =
		drm_property_create_क्रमागत(rdev->ddev, 0,
				    "underscan",
				    radeon_underscan_क्रमागत_list, sz);

	rdev->mode_info.underscan_hborder_property =
		drm_property_create_range(rdev->ddev, 0,
					"underscan hborder", 0, 128);
	अगर (!rdev->mode_info.underscan_hborder_property)
		वापस -ENOMEM;

	rdev->mode_info.underscan_vborder_property =
		drm_property_create_range(rdev->ddev, 0,
					"underscan vborder", 0, 128);
	अगर (!rdev->mode_info.underscan_vborder_property)
		वापस -ENOMEM;

	sz = ARRAY_SIZE(radeon_audio_क्रमागत_list);
	rdev->mode_info.audio_property =
		drm_property_create_क्रमागत(rdev->ddev, 0,
					 "audio",
					 radeon_audio_क्रमागत_list, sz);

	sz = ARRAY_SIZE(radeon_dither_क्रमागत_list);
	rdev->mode_info.dither_property =
		drm_property_create_क्रमागत(rdev->ddev, 0,
					 "dither",
					 radeon_dither_क्रमागत_list, sz);

	sz = ARRAY_SIZE(radeon_output_csc_क्रमागत_list);
	rdev->mode_info.output_csc_property =
		drm_property_create_क्रमागत(rdev->ddev, 0,
					 "output_csc",
					 radeon_output_csc_क्रमागत_list, sz);

	वापस 0;
पूर्ण

व्योम radeon_update_display_priority(काष्ठा radeon_device *rdev)
अणु
	/* adjusपंचांगent options क्रम the display watermarks */
	अगर ((radeon_disp_priority == 0) || (radeon_disp_priority > 2)) अणु
		/* set display priority to high क्रम r3xx, rv515 chips
		 * this aव्योमs flickering due to underflow to the
		 * display controllers during heavy acceleration.
		 * Don't क्रमce high on rs4xx igp chips as it seems to
		 * affect the sound card.  See kernel bug 15982.
		 */
		अगर ((ASIC_IS_R300(rdev) || (rdev->family == CHIP_RV515)) &&
		    !(rdev->flags & RADEON_IS_IGP))
			rdev->disp_priority = 2;
		अन्यथा
			rdev->disp_priority = 0;
	पूर्ण अन्यथा
		rdev->disp_priority = radeon_disp_priority;

पूर्ण

/*
 * Allocate hdmi काष्ठाs and determine रेजिस्टर offsets
 */
अटल व्योम radeon_afmt_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RADEON_MAX_AFMT_BLOCKS; i++)
		rdev->mode_info.afmt[i] = शून्य;

	अगर (ASIC_IS_NODCE(rdev)) अणु
		/* nothing to करो */
	पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		अटल uपूर्णांक32_t eg_offsets[] = अणु
			EVERGREEN_CRTC0_REGISTER_OFFSET,
			EVERGREEN_CRTC1_REGISTER_OFFSET,
			EVERGREEN_CRTC2_REGISTER_OFFSET,
			EVERGREEN_CRTC3_REGISTER_OFFSET,
			EVERGREEN_CRTC4_REGISTER_OFFSET,
			EVERGREEN_CRTC5_REGISTER_OFFSET,
			0x13830 - 0x7030,
		पूर्ण;
		पूर्णांक num_afmt;

		/* DCE8 has 7 audio blocks tied to DIG encoders */
		/* DCE6 has 6 audio blocks tied to DIG encoders */
		/* DCE4/5 has 6 audio blocks tied to DIG encoders */
		/* DCE4.1 has 2 audio blocks tied to DIG encoders */
		अगर (ASIC_IS_DCE8(rdev))
			num_afmt = 7;
		अन्यथा अगर (ASIC_IS_DCE6(rdev))
			num_afmt = 6;
		अन्यथा अगर (ASIC_IS_DCE5(rdev))
			num_afmt = 6;
		अन्यथा अगर (ASIC_IS_DCE41(rdev))
			num_afmt = 2;
		अन्यथा /* DCE4 */
			num_afmt = 6;

		BUG_ON(num_afmt > ARRAY_SIZE(eg_offsets));
		क्रम (i = 0; i < num_afmt; i++) अणु
			rdev->mode_info.afmt[i] = kzalloc(माप(काष्ठा radeon_afmt), GFP_KERNEL);
			अगर (rdev->mode_info.afmt[i]) अणु
				rdev->mode_info.afmt[i]->offset = eg_offsets[i];
				rdev->mode_info.afmt[i]->id = i;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (ASIC_IS_DCE3(rdev)) अणु
		/* DCE3.x has 2 audio blocks tied to DIG encoders */
		rdev->mode_info.afmt[0] = kzalloc(माप(काष्ठा radeon_afmt), GFP_KERNEL);
		अगर (rdev->mode_info.afmt[0]) अणु
			rdev->mode_info.afmt[0]->offset = DCE3_HDMI_OFFSET0;
			rdev->mode_info.afmt[0]->id = 0;
		पूर्ण
		rdev->mode_info.afmt[1] = kzalloc(माप(काष्ठा radeon_afmt), GFP_KERNEL);
		अगर (rdev->mode_info.afmt[1]) अणु
			rdev->mode_info.afmt[1]->offset = DCE3_HDMI_OFFSET1;
			rdev->mode_info.afmt[1]->id = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (ASIC_IS_DCE2(rdev)) अणु
		/* DCE2 has at least 1 routable audio block */
		rdev->mode_info.afmt[0] = kzalloc(माप(काष्ठा radeon_afmt), GFP_KERNEL);
		अगर (rdev->mode_info.afmt[0]) अणु
			rdev->mode_info.afmt[0]->offset = DCE2_HDMI_OFFSET0;
			rdev->mode_info.afmt[0]->id = 0;
		पूर्ण
		/* r6xx has 2 routable audio blocks */
		अगर (rdev->family >= CHIP_R600) अणु
			rdev->mode_info.afmt[1] = kzalloc(माप(काष्ठा radeon_afmt), GFP_KERNEL);
			अगर (rdev->mode_info.afmt[1]) अणु
				rdev->mode_info.afmt[1]->offset = DCE2_HDMI_OFFSET1;
				rdev->mode_info.afmt[1]->id = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_afmt_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RADEON_MAX_AFMT_BLOCKS; i++) अणु
		kमुक्त(rdev->mode_info.afmt[i]);
		rdev->mode_info.afmt[i] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक radeon_modeset_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	drm_mode_config_init(rdev->ddev);
	rdev->mode_info.mode_config_initialized = true;

	rdev->ddev->mode_config.funcs = &radeon_mode_funcs;

	अगर (radeon_use_pflipirq == 2 && rdev->family >= CHIP_R600)
		rdev->ddev->mode_config.async_page_flip = true;

	अगर (ASIC_IS_DCE5(rdev)) अणु
		rdev->ddev->mode_config.max_width = 16384;
		rdev->ddev->mode_config.max_height = 16384;
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		rdev->ddev->mode_config.max_width = 8192;
		rdev->ddev->mode_config.max_height = 8192;
	पूर्ण अन्यथा अणु
		rdev->ddev->mode_config.max_width = 4096;
		rdev->ddev->mode_config.max_height = 4096;
	पूर्ण

	rdev->ddev->mode_config.preferred_depth = 24;
	rdev->ddev->mode_config.prefer_shaकरोw = 1;

	rdev->ddev->mode_config.fb_base = rdev->mc.aper_base;

	ret = radeon_modeset_create_props(rdev);
	अगर (ret) अणु
		वापस ret;
	पूर्ण

	/* init i2c buses */
	radeon_i2c_init(rdev);

	/* check combios क्रम a valid hardcoded EDID - Sun servers */
	अगर (!rdev->is_atom_bios) अणु
		/* check क्रम hardcoded EDID in BIOS */
		radeon_combios_check_hardcoded_edid(rdev);
	पूर्ण

	/* allocate crtcs */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		radeon_crtc_init(rdev->ddev, i);
	पूर्ण

	/* okay we should have all the bios connectors */
	ret = radeon_setup_enc_conn(rdev->ddev);
	अगर (!ret) अणु
		वापस ret;
	पूर्ण

	/* init dig PHYs, disp eng pll */
	अगर (rdev->is_atom_bios) अणु
		radeon_atom_encoder_init(rdev);
		radeon_atom_disp_eng_pll_init(rdev);
	पूर्ण

	/* initialize hpd */
	radeon_hpd_init(rdev);

	/* setup afmt */
	radeon_afmt_init(rdev);

	radeon_fbdev_init(rdev);
	drm_kms_helper_poll_init(rdev->ddev);

	/* करो pm late init */
	ret = radeon_pm_late_init(rdev);

	वापस 0;
पूर्ण

व्योम radeon_modeset_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->mode_info.mode_config_initialized) अणु
		drm_kms_helper_poll_fini(rdev->ddev);
		radeon_hpd_fini(rdev);
		drm_helper_क्रमce_disable_all(rdev->ddev);
		radeon_fbdev_fini(rdev);
		radeon_afmt_fini(rdev);
		drm_mode_config_cleanup(rdev->ddev);
		rdev->mode_info.mode_config_initialized = false;
	पूर्ण

	kमुक्त(rdev->mode_info.bios_hardcoded_edid);

	/* मुक्त i2c buses */
	radeon_i2c_fini(rdev);
पूर्ण

अटल bool is_hdtv_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* try and guess अगर this is a tv or a monitor */
	अगर ((mode->vdisplay == 480 && mode->hdisplay == 720) || /* 480p */
	    (mode->vdisplay == 576) || /* 576p */
	    (mode->vdisplay == 720) || /* 720p */
	    (mode->vdisplay == 1080)) /* 1080p */
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

bool radeon_crtc_scaling_mode_fixup(काष्ठा drm_crtc *crtc,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा drm_connector *connector;
	bool first = true;
	u32 src_v = 1, dst_v = 1;
	u32 src_h = 1, dst_h = 1;

	radeon_crtc->h_border = 0;
	radeon_crtc->v_border = 0;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc != crtc)
			जारी;
		radeon_encoder = to_radeon_encoder(encoder);
		connector = radeon_get_connector_क्रम_encoder(encoder);

		अगर (first) अणु
			/* set scaling */
			अगर (radeon_encoder->rmx_type == RMX_OFF)
				radeon_crtc->rmx_type = RMX_OFF;
			अन्यथा अगर (mode->hdisplay < radeon_encoder->native_mode.hdisplay ||
				 mode->vdisplay < radeon_encoder->native_mode.vdisplay)
				radeon_crtc->rmx_type = radeon_encoder->rmx_type;
			अन्यथा
				radeon_crtc->rmx_type = RMX_OFF;
			/* copy native mode */
			स_नकल(&radeon_crtc->native_mode,
			       &radeon_encoder->native_mode,
				माप(काष्ठा drm_display_mode));
			src_v = crtc->mode.vdisplay;
			dst_v = radeon_crtc->native_mode.vdisplay;
			src_h = crtc->mode.hdisplay;
			dst_h = radeon_crtc->native_mode.hdisplay;

			/* fix up क्रम overscan on hdmi */
			अगर (ASIC_IS_AVIVO(rdev) &&
			    (!(mode->flags & DRM_MODE_FLAG_INTERLACE)) &&
			    ((radeon_encoder->underscan_type == UNDERSCAN_ON) ||
			     ((radeon_encoder->underscan_type == UNDERSCAN_AUTO) &&
			      drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
			      is_hdtv_mode(mode)))) अणु
				अगर (radeon_encoder->underscan_hborder != 0)
					radeon_crtc->h_border = radeon_encoder->underscan_hborder;
				अन्यथा
					radeon_crtc->h_border = (mode->hdisplay >> 5) + 16;
				अगर (radeon_encoder->underscan_vborder != 0)
					radeon_crtc->v_border = radeon_encoder->underscan_vborder;
				अन्यथा
					radeon_crtc->v_border = (mode->vdisplay >> 5) + 16;
				radeon_crtc->rmx_type = RMX_FULL;
				src_v = crtc->mode.vdisplay;
				dst_v = crtc->mode.vdisplay - (radeon_crtc->v_border * 2);
				src_h = crtc->mode.hdisplay;
				dst_h = crtc->mode.hdisplay - (radeon_crtc->h_border * 2);
			पूर्ण
			first = false;
		पूर्ण अन्यथा अणु
			अगर (radeon_crtc->rmx_type != radeon_encoder->rmx_type) अणु
				/* WARNING: Right now this can't happen but
				 * in the future we need to check that scaling
				 * are consistent across dअगरferent encoder
				 * (ie all encoder can work with the same
				 *  scaling).
				 */
				DRM_ERROR("Scaling not consistent across encoder.\n");
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (radeon_crtc->rmx_type != RMX_OFF) अणु
		fixed20_12 a, b;
		a.full = dfixed_स्थिर(src_v);
		b.full = dfixed_स्थिर(dst_v);
		radeon_crtc->vsc.full = dfixed_भाग(a, b);
		a.full = dfixed_स्थिर(src_h);
		b.full = dfixed_स्थिर(dst_h);
		radeon_crtc->hsc.full = dfixed_भाग(a, b);
	पूर्ण अन्यथा अणु
		radeon_crtc->vsc.full = dfixed_स्थिर(1);
		radeon_crtc->hsc.full = dfixed_स्थिर(1);
	पूर्ण
	वापस true;
पूर्ण

/*
 * Retrieve current video scanout position of crtc on a given gpu, and
 * an optional accurate बारtamp of when query happened.
 *
 * \param dev Device to query.
 * \param crtc Crtc to query.
 * \param flags Flags from caller (DRM_CALLED_FROM_VBLIRQ or 0).
 *              For driver पूर्णांकernal use only also supports these flags:
 *
 *              USE_REAL_VBLANKSTART to use the real start of vblank instead
 *              of a fudged earlier start of vblank.
 *
 *              GET_DISTANCE_TO_VBLANKSTART to वापस distance to the
 *              fudged earlier start of vblank in *vpos and the distance
 *              to true start of vblank in *hpos.
 *
 * \param *vpos Location where vertical scanout position should be stored.
 * \param *hpos Location where horizontal scanout position should go.
 * \param *sसमय Target location क्रम बारtamp taken immediately beक्रमe
 *               scanout position query. Can be शून्य to skip बारtamp.
 * \param *eसमय Target location क्रम बारtamp taken immediately after
 *               scanout position query. Can be शून्य to skip बारtamp.
 *
 * Returns vpos as a positive number जबतक in active scanout area.
 * Returns vpos as a negative number inside vblank, counting the number
 * of scanlines to go until end of vblank, e.g., -1 means "one scanline
 * until start of active scanout / end of vblank."
 *
 * \लeturn Flags, or'ed together as follows:
 *
 * DRM_SCANOUTPOS_VALID = Query successful.
 * DRM_SCANOUTPOS_INVBL = Inside vblank.
 * DRM_SCANOUTPOS_ACCURATE = Returned position is accurate. A lack of
 * this flag means that वापसed position may be offset by a स्थिरant but
 * unknown small number of scanlines wrt. real scanout position.
 *
 */
पूर्णांक radeon_get_crtc_scanoutpos(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
			       अचिन्हित पूर्णांक flags, पूर्णांक *vpos, पूर्णांक *hpos,
			       kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			       स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 stat_crtc = 0, vbl = 0, position = 0;
	पूर्णांक vbl_start, vbl_end, vtotal, ret = 0;
	bool in_vbl = true;

	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional प्रणाली बारtamp beक्रमe query. */
	अगर (sसमय)
		*sसमय = kसमय_get();

	अगर (ASIC_IS_DCE4(rdev)) अणु
		अगर (pipe == 0) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC0_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC0_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 1) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC1_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC1_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 2) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC2_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC2_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 3) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC3_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC3_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 4) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC4_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC4_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 5) अणु
			vbl = RREG32(EVERGREEN_CRTC_V_BLANK_START_END +
				     EVERGREEN_CRTC5_REGISTER_OFFSET);
			position = RREG32(EVERGREEN_CRTC_STATUS_POSITION +
					  EVERGREEN_CRTC5_REGISTER_OFFSET);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		अगर (pipe == 0) अणु
			vbl = RREG32(AVIVO_D1CRTC_V_BLANK_START_END);
			position = RREG32(AVIVO_D1CRTC_STATUS_POSITION);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 1) अणु
			vbl = RREG32(AVIVO_D2CRTC_V_BLANK_START_END);
			position = RREG32(AVIVO_D2CRTC_STATUS_POSITION);
			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Pre-AVIVO: Dअगरferent encoding of scanout pos and vblank पूर्णांकerval. */
		अगर (pipe == 0) अणु
			/* Assume vbl_end == 0, get vbl_start from
			 * upper 16 bits.
			 */
			vbl = (RREG32(RADEON_CRTC_V_TOTAL_DISP) &
				RADEON_CRTC_V_DISP) >> RADEON_CRTC_V_DISP_SHIFT;
			/* Only retrieve vpos from upper 16 bits, set hpos == 0. */
			position = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
			stat_crtc = RREG32(RADEON_CRTC_STATUS);
			अगर (!(stat_crtc & 1))
				in_vbl = false;

			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
		अगर (pipe == 1) अणु
			vbl = (RREG32(RADEON_CRTC2_V_TOTAL_DISP) &
				RADEON_CRTC_V_DISP) >> RADEON_CRTC_V_DISP_SHIFT;
			position = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
			stat_crtc = RREG32(RADEON_CRTC2_STATUS);
			अगर (!(stat_crtc & 1))
				in_vbl = false;

			ret |= DRM_SCANOUTPOS_VALID;
		पूर्ण
	पूर्ण

	/* Get optional प्रणाली बारtamp after query. */
	अगर (eसमय)
		*eसमय = kसमय_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	/* Decode पूर्णांकo vertical and horizontal scanout position. */
	*vpos = position & 0x1fff;
	*hpos = (position >> 16) & 0x1fff;

	/* Valid vblank area boundaries from gpu retrieved? */
	अगर (vbl > 0) अणु
		/* Yes: Decode. */
		ret |= DRM_SCANOUTPOS_ACCURATE;
		vbl_start = vbl & 0x1fff;
		vbl_end = (vbl >> 16) & 0x1fff;
	पूर्ण
	अन्यथा अणु
		/* No: Fake something reasonable which gives at least ok results. */
		vbl_start = mode->crtc_vdisplay;
		vbl_end = 0;
	पूर्ण

	/* Called from driver पूर्णांकernal vblank counter query code? */
	अगर (flags & GET_DISTANCE_TO_VBLANKSTART) अणु
	    /* Caller wants distance from real vbl_start in *hpos */
	    *hpos = *vpos - vbl_start;
	पूर्ण

	/* Fudge vblank to start a few scanlines earlier to handle the
	 * problem that vblank irqs fire a few scanlines beक्रमe start
	 * of vblank. Some driver पूर्णांकernal callers need the true vblank
	 * start to be used and संकेत this via the USE_REAL_VBLANKSTART flag.
	 *
	 * The cause of the "early" vblank irq is that the irq is triggered
	 * by the line buffer logic when the line buffer पढ़ो position enters
	 * the vblank, whereas our crtc scanout position naturally lags the
	 * line buffer पढ़ो position.
	 */
	अगर (!(flags & USE_REAL_VBLANKSTART))
		vbl_start -= rdev->mode_info.crtcs[pipe]->lb_vblank_lead_lines;

	/* Test scanout position against vblank region. */
	अगर ((*vpos < vbl_start) && (*vpos >= vbl_end))
		in_vbl = false;

	/* In vblank? */
	अगर (in_vbl)
	    ret |= DRM_SCANOUTPOS_IN_VBLANK;

	/* Called from driver पूर्णांकernal vblank counter query code? */
	अगर (flags & GET_DISTANCE_TO_VBLANKSTART) अणु
		/* Caller wants distance from fudged earlier vbl_start */
		*vpos -= vbl_start;
		वापस ret;
	पूर्ण

	/* Check अगर inside vblank area and apply corrective offsets:
	 * vpos will then be >=0 in video scanout area, but negative
	 * within vblank area, counting करोwn the number of lines until
	 * start of scanout.
	 */

	/* Inside "upper part" of vblank area? Apply corrective offset अगर so: */
	अगर (in_vbl && (*vpos >= vbl_start)) अणु
		vtotal = mode->crtc_vtotal;
		*vpos = *vpos - vtotal;
	पूर्ण

	/* Correct क्रम shअगरted end of vbl at vbl_end. */
	*vpos = *vpos - vbl_end;

	वापस ret;
पूर्ण

bool
radeon_get_crtc_scanout_position(काष्ठा drm_crtc *crtc,
				 bool in_vblank_irq, पूर्णांक *vpos, पूर्णांक *hpos,
				 kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;

	वापस radeon_get_crtc_scanoutpos(dev, pipe, 0, vpos, hpos,
					  sसमय, eसमय, mode);
पूर्ण
