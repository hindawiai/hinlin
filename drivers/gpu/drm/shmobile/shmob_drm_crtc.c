<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * shmob_drm_crtc.c  --  SH Mobile DRM CRTCs
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/backlight.h>
#समावेश <linux/clk.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "shmob_drm_backlight.h"
#समावेश "shmob_drm_crtc.h"
#समावेश "shmob_drm_drv.h"
#समावेश "shmob_drm_kms.h"
#समावेश "shmob_drm_plane.h"
#समावेश "shmob_drm_regs.h"

/*
 * TODO: panel support
 */

/* -----------------------------------------------------------------------------
 * Clock management
 */

अटल पूर्णांक shmob_drm_clk_on(काष्ठा shmob_drm_device *sdev)
अणु
	पूर्णांक ret;

	अगर (sdev->घड़ी) अणु
		ret = clk_prepare_enable(sdev->घड़ी);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम shmob_drm_clk_off(काष्ठा shmob_drm_device *sdev)
अणु
	अगर (sdev->घड़ी)
		clk_disable_unprepare(sdev->घड़ी);
पूर्ण

/* -----------------------------------------------------------------------------
 * CRTC
 */

अटल व्योम shmob_drm_crtc_setup_geometry(काष्ठा shmob_drm_crtc *scrtc)
अणु
	काष्ठा drm_crtc *crtc = &scrtc->crtc;
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_पूर्णांकerface_data *idata = &sdev->pdata->अगरace;
	स्थिर काष्ठा drm_display_mode *mode = &crtc->mode;
	u32 value;

	value = sdev->ldmt1r
	      | ((mode->flags & DRM_MODE_FLAG_PVSYNC) ? 0 : LDMT1R_VPOL)
	      | ((mode->flags & DRM_MODE_FLAG_PHSYNC) ? 0 : LDMT1R_HPOL)
	      | ((idata->flags & SHMOB_DRM_IFACE_FL_DWPOL) ? LDMT1R_DWPOL : 0)
	      | ((idata->flags & SHMOB_DRM_IFACE_FL_DIPOL) ? LDMT1R_DIPOL : 0)
	      | ((idata->flags & SHMOB_DRM_IFACE_FL_DAPOL) ? LDMT1R_DAPOL : 0)
	      | ((idata->flags & SHMOB_DRM_IFACE_FL_HSCNT) ? LDMT1R_HSCNT : 0)
	      | ((idata->flags & SHMOB_DRM_IFACE_FL_DWCNT) ? LDMT1R_DWCNT : 0);
	lcdc_ग_लिखो(sdev, LDMT1R, value);

	अगर (idata->पूर्णांकerface >= SHMOB_DRM_IFACE_SYS8A &&
	    idata->पूर्णांकerface <= SHMOB_DRM_IFACE_SYS24) अणु
		/* Setup SYS bus. */
		value = (idata->sys.cs_setup << LDMT2R_CSUP_SHIFT)
		      | (idata->sys.vsync_active_high ? LDMT2R_RSV : 0)
		      | (idata->sys.vsync_dir_input ? LDMT2R_VSEL : 0)
		      | (idata->sys.ग_लिखो_setup << LDMT2R_WCSC_SHIFT)
		      | (idata->sys.ग_लिखो_cycle << LDMT2R_WCEC_SHIFT)
		      | (idata->sys.ग_लिखो_strobe << LDMT2R_WCLW_SHIFT);
		lcdc_ग_लिखो(sdev, LDMT2R, value);

		value = (idata->sys.पढ़ो_latch << LDMT3R_RDLC_SHIFT)
		      | (idata->sys.पढ़ो_setup << LDMT3R_RCSC_SHIFT)
		      | (idata->sys.पढ़ो_cycle << LDMT3R_RCEC_SHIFT)
		      | (idata->sys.पढ़ो_strobe << LDMT3R_RCLW_SHIFT);
		lcdc_ग_लिखो(sdev, LDMT3R, value);
	पूर्ण

	value = ((mode->hdisplay / 8) << 16)			/* HDCN */
	      | (mode->htotal / 8);				/* HTCN */
	lcdc_ग_लिखो(sdev, LDHCNR, value);

	value = (((mode->hsync_end - mode->hsync_start) / 8) << 16) /* HSYNW */
	      | (mode->hsync_start / 8);			/* HSYNP */
	lcdc_ग_लिखो(sdev, LDHSYNR, value);

	value = ((mode->hdisplay & 7) << 24) | ((mode->htotal & 7) << 16)
	      | (((mode->hsync_end - mode->hsync_start) & 7) << 8)
	      | (mode->hsync_start & 7);
	lcdc_ग_लिखो(sdev, LDHAJR, value);

	value = ((mode->vdisplay) << 16)			/* VDLN */
	      | mode->vtotal;					/* VTLN */
	lcdc_ग_लिखो(sdev, LDVLNR, value);

	value = ((mode->vsync_end - mode->vsync_start) << 16)	/* VSYNW */
	      | mode->vsync_start;				/* VSYNP */
	lcdc_ग_लिखो(sdev, LDVSYNR, value);
पूर्ण

अटल व्योम shmob_drm_crtc_start_stop(काष्ठा shmob_drm_crtc *scrtc, bool start)
अणु
	काष्ठा shmob_drm_device *sdev = scrtc->crtc.dev->dev_निजी;
	u32 value;

	value = lcdc_पढ़ो(sdev, LDCNT2R);
	अगर (start)
		lcdc_ग_लिखो(sdev, LDCNT2R, value | LDCNT2R_DO);
	अन्यथा
		lcdc_ग_लिखो(sdev, LDCNT2R, value & ~LDCNT2R_DO);

	/* Wait until घातer is applied/stopped. */
	जबतक (1) अणु
		value = lcdc_पढ़ो(sdev, LDPMR) & LDPMR_LPS;
		अगर ((start && value) || (!start && !value))
			अवरोध;

		cpu_relax();
	पूर्ण

	अगर (!start) अणु
		/* Stop the करोt घड़ी. */
		lcdc_ग_लिखो(sdev, LDDCKSTPR, LDDCKSTPR_DCKSTP);
	पूर्ण
पूर्ण

/*
 * shmob_drm_crtc_start - Configure and start the LCDC
 * @scrtc: the SH Mobile CRTC
 *
 * Configure and start the LCDC device. External devices (घड़ीs, MERAM, panels,
 * ...) are not touched by this function.
 */
अटल व्योम shmob_drm_crtc_start(काष्ठा shmob_drm_crtc *scrtc)
अणु
	काष्ठा drm_crtc *crtc = &scrtc->crtc;
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_पूर्णांकerface_data *idata = &sdev->pdata->अगरace;
	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;
	काष्ठा drm_device *dev = sdev->ddev;
	काष्ठा drm_plane *plane;
	u32 value;
	पूर्णांक ret;

	अगर (scrtc->started)
		वापस;

	क्रमmat = shmob_drm_क्रमmat_info(crtc->primary->fb->क्रमmat->क्रमmat);
	अगर (WARN_ON(क्रमmat == शून्य))
		वापस;

	/* Enable घड़ीs beक्रमe accessing the hardware. */
	ret = shmob_drm_clk_on(sdev);
	अगर (ret < 0)
		वापस;

	/* Reset and enable the LCDC. */
	lcdc_ग_लिखो(sdev, LDCNT2R, lcdc_पढ़ो(sdev, LDCNT2R) | LDCNT2R_BR);
	lcdc_रुको_bit(sdev, LDCNT2R, LDCNT2R_BR, 0);
	lcdc_ग_लिखो(sdev, LDCNT2R, LDCNT2R_ME);

	/* Stop the LCDC first and disable all पूर्णांकerrupts. */
	shmob_drm_crtc_start_stop(scrtc, false);
	lcdc_ग_लिखो(sdev, LDINTR, 0);

	/* Configure घातer supply, करोt घड़ीs and start them. */
	lcdc_ग_लिखो(sdev, LDPMR, 0);

	value = sdev->lddckr;
	अगर (idata->clk_भाग) अणु
		/* FIXME: sh7724 can only use 42, 48, 54 and 60 क्रम the भागider
		 * denominator.
		 */
		lcdc_ग_लिखो(sdev, LDDCKPAT1R, 0);
		lcdc_ग_लिखो(sdev, LDDCKPAT2R, (1 << (idata->clk_भाग / 2)) - 1);

		अगर (idata->clk_भाग == 1)
			value |= LDDCKR_MOSEL;
		अन्यथा
			value |= idata->clk_भाग;
	पूर्ण

	lcdc_ग_लिखो(sdev, LDDCKR, value);
	lcdc_ग_लिखो(sdev, LDDCKSTPR, 0);
	lcdc_रुको_bit(sdev, LDDCKSTPR, ~0, 0);

	/* TODO: Setup SYS panel */

	/* Setup geometry, क्रमmat, frame buffer memory and operation mode. */
	shmob_drm_crtc_setup_geometry(scrtc);

	/* TODO: Handle YUV colorspaces. Hardcode REC709 क्रम now. */
	lcdc_ग_लिखो(sdev, LDDFR, क्रमmat->lddfr | LDDFR_CF1);
	lcdc_ग_लिखो(sdev, LDMLSR, scrtc->line_size);
	lcdc_ग_लिखो(sdev, LDSA1R, scrtc->dma[0]);
	अगर (क्रमmat->yuv)
		lcdc_ग_लिखो(sdev, LDSA2R, scrtc->dma[1]);
	lcdc_ग_लिखो(sdev, LDSM1R, 0);

	/* Word and दीर्घ word swap. */
	चयन (क्रमmat->fourcc) अणु
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV61:
	हाल DRM_FORMAT_NV42:
		value = LDDDSR_LS | LDDDSR_WS;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV24:
		value = LDDDSR_LS | LDDDSR_WS | LDDDSR_BS;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	शेष:
		value = LDDDSR_LS;
		अवरोध;
	पूर्ण
	lcdc_ग_लिखो(sdev, LDDDSR, value);

	/* Setup planes. */
	drm_क्रम_each_legacy_plane(plane, dev) अणु
		अगर (plane->crtc == crtc)
			shmob_drm_plane_setup(plane);
	पूर्ण

	/* Enable the display output. */
	lcdc_ग_लिखो(sdev, LDCNT1R, LDCNT1R_DE);

	shmob_drm_crtc_start_stop(scrtc, true);

	scrtc->started = true;
पूर्ण

अटल व्योम shmob_drm_crtc_stop(काष्ठा shmob_drm_crtc *scrtc)
अणु
	काष्ठा drm_crtc *crtc = &scrtc->crtc;
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;

	अगर (!scrtc->started)
		वापस;

	/* Stop the LCDC. */
	shmob_drm_crtc_start_stop(scrtc, false);

	/* Disable the display output. */
	lcdc_ग_लिखो(sdev, LDCNT1R, 0);

	/* Stop घड़ीs. */
	shmob_drm_clk_off(sdev);

	scrtc->started = false;
पूर्ण

व्योम shmob_drm_crtc_suspend(काष्ठा shmob_drm_crtc *scrtc)
अणु
	shmob_drm_crtc_stop(scrtc);
पूर्ण

व्योम shmob_drm_crtc_resume(काष्ठा shmob_drm_crtc *scrtc)
अणु
	अगर (scrtc->dpms != DRM_MODE_DPMS_ON)
		वापस;

	shmob_drm_crtc_start(scrtc);
पूर्ण

अटल व्योम shmob_drm_crtc_compute_base(काष्ठा shmob_drm_crtc *scrtc,
					पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_crtc *crtc = &scrtc->crtc;
	काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	काष्ठा drm_gem_cma_object *gem;
	अचिन्हित पूर्णांक bpp;

	bpp = scrtc->क्रमmat->yuv ? 8 : scrtc->क्रमmat->bpp;
	gem = drm_fb_cma_get_gem_obj(fb, 0);
	scrtc->dma[0] = gem->paddr + fb->offsets[0]
		      + y * fb->pitches[0] + x * bpp / 8;

	अगर (scrtc->क्रमmat->yuv) अणु
		bpp = scrtc->क्रमmat->bpp - 8;
		gem = drm_fb_cma_get_gem_obj(fb, 1);
		scrtc->dma[1] = gem->paddr + fb->offsets[1]
			      + y / (bpp == 4 ? 2 : 1) * fb->pitches[1]
			      + x * (bpp == 16 ? 2 : 1);
	पूर्ण
पूर्ण

अटल व्योम shmob_drm_crtc_update_base(काष्ठा shmob_drm_crtc *scrtc)
अणु
	काष्ठा drm_crtc *crtc = &scrtc->crtc;
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;

	shmob_drm_crtc_compute_base(scrtc, crtc->x, crtc->y);

	lcdc_ग_लिखो_mirror(sdev, LDSA1R, scrtc->dma[0]);
	अगर (scrtc->क्रमmat->yuv)
		lcdc_ग_लिखो_mirror(sdev, LDSA2R, scrtc->dma[1]);

	lcdc_ग_लिखो(sdev, LDRCNTR, lcdc_पढ़ो(sdev, LDRCNTR) ^ LDRCNTR_MRS);
पूर्ण

#घोषणा to_shmob_crtc(c)	container_of(c, काष्ठा shmob_drm_crtc, crtc)

अटल व्योम shmob_drm_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा shmob_drm_crtc *scrtc = to_shmob_crtc(crtc);

	अगर (scrtc->dpms == mode)
		वापस;

	अगर (mode == DRM_MODE_DPMS_ON)
		shmob_drm_crtc_start(scrtc);
	अन्यथा
		shmob_drm_crtc_stop(scrtc);

	scrtc->dpms = mode;
पूर्ण

अटल व्योम shmob_drm_crtc_mode_prepare(काष्ठा drm_crtc *crtc)
अणु
	shmob_drm_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
पूर्ण

अटल पूर्णांक shmob_drm_crtc_mode_set(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode,
				   पूर्णांक x, पूर्णांक y,
				   काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा shmob_drm_crtc *scrtc = to_shmob_crtc(crtc);
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;

	क्रमmat = shmob_drm_क्रमmat_info(crtc->primary->fb->क्रमmat->क्रमmat);
	अगर (क्रमmat == शून्य) अणु
		dev_dbg(sdev->dev, "mode_set: unsupported format %08x\n",
			crtc->primary->fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	scrtc->क्रमmat = क्रमmat;
	scrtc->line_size = crtc->primary->fb->pitches[0];

	shmob_drm_crtc_compute_base(scrtc, x, y);

	वापस 0;
पूर्ण

अटल व्योम shmob_drm_crtc_mode_commit(काष्ठा drm_crtc *crtc)
अणु
	shmob_drm_crtc_dpms(crtc, DRM_MODE_DPMS_ON);
पूर्ण

अटल पूर्णांक shmob_drm_crtc_mode_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
					काष्ठा drm_framebuffer *old_fb)
अणु
	shmob_drm_crtc_update_base(to_shmob_crtc(crtc));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs crtc_helper_funcs = अणु
	.dpms = shmob_drm_crtc_dpms,
	.prepare = shmob_drm_crtc_mode_prepare,
	.commit = shmob_drm_crtc_mode_commit,
	.mode_set = shmob_drm_crtc_mode_set,
	.mode_set_base = shmob_drm_crtc_mode_set_base,
पूर्ण;

व्योम shmob_drm_crtc_finish_page_flip(काष्ठा shmob_drm_crtc *scrtc)
अणु
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा drm_device *dev = scrtc->crtc.dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = scrtc->event;
	scrtc->event = शून्य;
	अगर (event) अणु
		drm_crtc_send_vblank_event(&scrtc->crtc, event);
		drm_crtc_vblank_put(&scrtc->crtc);
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

अटल पूर्णांक shmob_drm_crtc_page_flip(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_framebuffer *fb,
				    काष्ठा drm_pending_vblank_event *event,
				    uपूर्णांक32_t page_flip_flags,
				    काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा shmob_drm_crtc *scrtc = to_shmob_crtc(crtc);
	काष्ठा drm_device *dev = scrtc->crtc.dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (scrtc->event != शून्य) अणु
		spin_unlock_irqrestore(&dev->event_lock, flags);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);

	crtc->primary->fb = fb;
	shmob_drm_crtc_update_base(scrtc);

	अगर (event) अणु
		event->pipe = 0;
		drm_crtc_vblank_get(&scrtc->crtc);
		spin_lock_irqsave(&dev->event_lock, flags);
		scrtc->event = event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम shmob_drm_crtc_enable_vblank(काष्ठा shmob_drm_device *sdev,
					 bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 ldपूर्णांकr;

	/* Be careful not to acknowledge any pending पूर्णांकerrupt. */
	spin_lock_irqsave(&sdev->irq_lock, flags);
	ldपूर्णांकr = lcdc_पढ़ो(sdev, LDINTR) | LDINTR_STATUS_MASK;
	अगर (enable)
		ldपूर्णांकr |= LDINTR_VEE;
	अन्यथा
		ldपूर्णांकr &= ~LDINTR_VEE;
	lcdc_ग_लिखो(sdev, LDINTR, ldपूर्णांकr);
	spin_unlock_irqrestore(&sdev->irq_lock, flags);
पूर्ण

अटल पूर्णांक shmob_drm_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;

	shmob_drm_crtc_enable_vblank(sdev, true);

	वापस 0;
पूर्ण

अटल व्योम shmob_drm_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा shmob_drm_device *sdev = crtc->dev->dev_निजी;

	shmob_drm_crtc_enable_vblank(sdev, false);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs crtc_funcs = अणु
	.destroy = drm_crtc_cleanup,
	.set_config = drm_crtc_helper_set_config,
	.page_flip = shmob_drm_crtc_page_flip,
	.enable_vblank = shmob_drm_enable_vblank,
	.disable_vblank = shmob_drm_disable_vblank,
पूर्ण;

पूर्णांक shmob_drm_crtc_create(काष्ठा shmob_drm_device *sdev)
अणु
	काष्ठा drm_crtc *crtc = &sdev->crtc.crtc;
	पूर्णांक ret;

	sdev->crtc.dpms = DRM_MODE_DPMS_OFF;

	ret = drm_crtc_init(sdev->ddev, crtc, &crtc_funcs);
	अगर (ret < 0)
		वापस ret;

	drm_crtc_helper_add(crtc, &crtc_helper_funcs);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Encoder
 */

#घोषणा to_shmob_encoder(e) \
	container_of(e, काष्ठा shmob_drm_encoder, encoder)

अटल व्योम shmob_drm_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा shmob_drm_encoder *senc = to_shmob_encoder(encoder);
	काष्ठा shmob_drm_device *sdev = encoder->dev->dev_निजी;
	काष्ठा shmob_drm_connector *scon = &sdev->connector;

	अगर (senc->dpms == mode)
		वापस;

	shmob_drm_backlight_dpms(scon, mode);

	senc->dpms = mode;
पूर्ण

अटल bool shmob_drm_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
					 स्थिर काष्ठा drm_display_mode *mode,
					 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा shmob_drm_device *sdev = dev->dev_निजी;
	काष्ठा drm_connector *connector = &sdev->connector.connector;
	स्थिर काष्ठा drm_display_mode *panel_mode;

	अगर (list_empty(&connector->modes)) अणु
		dev_dbg(dev->dev, "mode_fixup: empty modes list\n");
		वापस false;
	पूर्ण

	/* The flat panel mode is fixed, just copy it to the adjusted mode. */
	panel_mode = list_first_entry(&connector->modes,
				      काष्ठा drm_display_mode, head);
	drm_mode_copy(adjusted_mode, panel_mode);

	वापस true;
पूर्ण

अटल व्योम shmob_drm_encoder_mode_prepare(काष्ठा drm_encoder *encoder)
अणु
	/* No-op, everything is handled in the CRTC code. */
पूर्ण

अटल व्योम shmob_drm_encoder_mode_set(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* No-op, everything is handled in the CRTC code. */
पूर्ण

अटल व्योम shmob_drm_encoder_mode_commit(काष्ठा drm_encoder *encoder)
अणु
	/* No-op, everything is handled in the CRTC code. */
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs encoder_helper_funcs = अणु
	.dpms = shmob_drm_encoder_dpms,
	.mode_fixup = shmob_drm_encoder_mode_fixup,
	.prepare = shmob_drm_encoder_mode_prepare,
	.commit = shmob_drm_encoder_mode_commit,
	.mode_set = shmob_drm_encoder_mode_set,
पूर्ण;

पूर्णांक shmob_drm_encoder_create(काष्ठा shmob_drm_device *sdev)
अणु
	काष्ठा drm_encoder *encoder = &sdev->encoder.encoder;
	पूर्णांक ret;

	sdev->encoder.dpms = DRM_MODE_DPMS_OFF;

	encoder->possible_crtcs = 1;

	ret = drm_simple_encoder_init(sdev->ddev, encoder,
				      DRM_MODE_ENCODER_LVDS);
	अगर (ret < 0)
		वापस ret;

	drm_encoder_helper_add(encoder, &encoder_helper_funcs);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Connector
 */

#घोषणा to_shmob_connector(c) \
	container_of(c, काष्ठा shmob_drm_connector, connector)

अटल पूर्णांक shmob_drm_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा shmob_drm_device *sdev = connector->dev->dev_निजी;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_create(connector->dev);
	अगर (mode == शून्य)
		वापस 0;

	mode->type = DRM_MODE_TYPE_PREFERRED | DRM_MODE_TYPE_DRIVER;
	mode->घड़ी = sdev->pdata->panel.mode.घड़ी;
	mode->hdisplay = sdev->pdata->panel.mode.hdisplay;
	mode->hsync_start = sdev->pdata->panel.mode.hsync_start;
	mode->hsync_end = sdev->pdata->panel.mode.hsync_end;
	mode->htotal = sdev->pdata->panel.mode.htotal;
	mode->vdisplay = sdev->pdata->panel.mode.vdisplay;
	mode->vsync_start = sdev->pdata->panel.mode.vsync_start;
	mode->vsync_end = sdev->pdata->panel.mode.vsync_end;
	mode->vtotal = sdev->pdata->panel.mode.vtotal;
	mode->flags = sdev->pdata->panel.mode.flags;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = sdev->pdata->panel.width_mm;
	connector->display_info.height_mm = sdev->pdata->panel.height_mm;

	वापस 1;
पूर्ण

अटल काष्ठा drm_encoder *
shmob_drm_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा shmob_drm_connector *scon = to_shmob_connector(connector);

	वापस scon->encoder;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs connector_helper_funcs = अणु
	.get_modes = shmob_drm_connector_get_modes,
	.best_encoder = shmob_drm_connector_best_encoder,
पूर्ण;

अटल व्योम shmob_drm_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा shmob_drm_connector *scon = to_shmob_connector(connector);

	shmob_drm_backlight_निकास(scon);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = shmob_drm_connector_destroy,
पूर्ण;

पूर्णांक shmob_drm_connector_create(काष्ठा shmob_drm_device *sdev,
			       काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector = &sdev->connector.connector;
	पूर्णांक ret;

	sdev->connector.encoder = encoder;

	connector->display_info.width_mm = sdev->pdata->panel.width_mm;
	connector->display_info.height_mm = sdev->pdata->panel.height_mm;

	ret = drm_connector_init(sdev->ddev, connector, &connector_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	अगर (ret < 0)
		वापस ret;

	drm_connector_helper_add(connector, &connector_helper_funcs);

	ret = shmob_drm_backlight_init(&sdev->connector);
	अगर (ret < 0)
		जाओ err_cleanup;

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret < 0)
		जाओ err_backlight;

	drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
	drm_object_property_set_value(&connector->base,
		sdev->ddev->mode_config.dpms_property, DRM_MODE_DPMS_OFF);

	वापस 0;

err_backlight:
	shmob_drm_backlight_निकास(&sdev->connector);
err_cleanup:
	drm_connector_cleanup(connector);
	वापस ret;
पूर्ण
