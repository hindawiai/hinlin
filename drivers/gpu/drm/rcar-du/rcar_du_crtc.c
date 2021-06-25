<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_crtc.c  --  R-Car Display Unit CRTCs
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "rcar_cmm.h"
#समावेश "rcar_du_crtc.h"
#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_encoder.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_plane.h"
#समावेश "rcar_du_regs.h"
#समावेश "rcar_du_vsp.h"
#समावेश "rcar_lvds.h"

अटल u32 rcar_du_crtc_पढ़ो(काष्ठा rcar_du_crtc *rcrtc, u32 reg)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	वापस rcar_du_पढ़ो(rcdu, rcrtc->mmio_offset + reg);
पूर्ण

अटल व्योम rcar_du_crtc_ग_लिखो(काष्ठा rcar_du_crtc *rcrtc, u32 reg, u32 data)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_ग_लिखो(rcdu, rcrtc->mmio_offset + reg, data);
पूर्ण

अटल व्योम rcar_du_crtc_clr(काष्ठा rcar_du_crtc *rcrtc, u32 reg, u32 clr)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_ग_लिखो(rcdu, rcrtc->mmio_offset + reg,
		      rcar_du_पढ़ो(rcdu, rcrtc->mmio_offset + reg) & ~clr);
पूर्ण

अटल व्योम rcar_du_crtc_set(काष्ठा rcar_du_crtc *rcrtc, u32 reg, u32 set)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_ग_लिखो(rcdu, rcrtc->mmio_offset + reg,
		      rcar_du_पढ़ो(rcdu, rcrtc->mmio_offset + reg) | set);
पूर्ण

व्योम rcar_du_crtc_dsysr_clr_set(काष्ठा rcar_du_crtc *rcrtc, u32 clr, u32 set)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	rcrtc->dsysr = (rcrtc->dsysr & ~clr) | set;
	rcar_du_ग_लिखो(rcdu, rcrtc->mmio_offset + DSYSR, rcrtc->dsysr);
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware Setup
 */

काष्ठा dpll_info अणु
	अचिन्हित पूर्णांक output;
	अचिन्हित पूर्णांक fdpll;
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक m;
पूर्ण;

अटल व्योम rcar_du_dpll_भागider(काष्ठा rcar_du_crtc *rcrtc,
				 काष्ठा dpll_info *dpll,
				 अचिन्हित दीर्घ input,
				 अचिन्हित दीर्घ target)
अणु
	अचिन्हित दीर्घ best_dअगरf = (अचिन्हित दीर्घ)-1;
	अचिन्हित दीर्घ dअगरf;
	अचिन्हित पूर्णांक fdpll;
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक n;

	/*
	 *   fin                                 fvco        fout       fclkout
	 * in --> [1/M] --> |PD| -> [LPF] -> [VCO] -> [1/P] -+-> [1/FDPLL] -> out
	 *              +-> |  |                             |
	 *              |                                    |
	 *              +---------------- [1/N] <------------+
	 *
	 *	fclkout = fvco / P / FDPLL -- (1)
	 *
	 * fin/M = fvco/P/N
	 *
	 *	fvco = fin * P *  N / M -- (2)
	 *
	 * (1) + (2) indicates
	 *
	 *	fclkout = fin * N / M / FDPLL
	 *
	 * NOTES
	 *	N	: (n + 1)
	 *	M	: (m + 1)
	 *	FDPLL	: (fdpll + 1)
	 *	P	: 2
	 *	2kHz < fvco < 4096MHz
	 *
	 * To minimize the jitter,
	 * N : as large as possible
	 * M : as small as possible
	 */
	क्रम (m = 0; m < 4; m++) अणु
		क्रम (n = 119; n > 38; n--) अणु
			/*
			 * This code only runs on 64-bit architectures, the
			 * अचिन्हित दीर्घ type can thus be used क्रम 64-bit
			 * computation. It will still compile without any
			 * warning on 32-bit architectures.
			 *
			 * To optimize calculations, use fout instead of fvco
			 * to verअगरy the VCO frequency स्थिरraपूर्णांक.
			 */
			अचिन्हित दीर्घ fout = input * (n + 1) / (m + 1);

			अगर (fout < 1000 || fout > 2048 * 1000 * 1000U)
				जारी;

			क्रम (fdpll = 1; fdpll < 32; fdpll++) अणु
				अचिन्हित दीर्घ output;

				output = fout / (fdpll + 1);
				अगर (output >= 400 * 1000 * 1000)
					जारी;

				dअगरf = असल((दीर्घ)output - (दीर्घ)target);
				अगर (best_dअगरf > dअगरf) अणु
					best_dअगरf = dअगरf;
					dpll->n = n;
					dpll->m = m;
					dpll->fdpll = fdpll;
					dpll->output = output;
				पूर्ण

				अगर (dअगरf == 0)
					जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	dev_dbg(rcrtc->dev->dev,
		"output:%u, fdpll:%u, n:%u, m:%u, diff:%lu\n",
		 dpll->output, dpll->fdpll, dpll->n, dpll->m, best_dअगरf);
पूर्ण

काष्ठा du_clk_params अणु
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ dअगरf;
	u32 escr;
पूर्ण;

अटल व्योम rcar_du_escr_भागider(काष्ठा clk *clk, अचिन्हित दीर्घ target,
				 u32 escr, काष्ठा du_clk_params *params)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ dअगरf;
	u32 भाग;

	/*
	 * If the target rate has alपढ़ोy been achieved perfectly we can't करो
	 * better.
	 */
	अगर (params->dअगरf == 0)
		वापस;

	/*
	 * Compute the input घड़ी rate and पूर्णांकernal भागisor values to obtain
	 * the घड़ी rate बंदst to the target frequency.
	 */
	rate = clk_round_rate(clk, target);
	भाग = clamp(DIV_ROUND_CLOSEST(rate, target), 1UL, 64UL) - 1;
	dअगरf = असल(rate / (भाग + 1) - target);

	/*
	 * Store the parameters अगर the resulting frequency is better than any
	 * previously calculated value.
	 */
	अगर (dअगरf < params->dअगरf) अणु
		params->clk = clk;
		params->rate = rate;
		params->dअगरf = dअगरf;
		params->escr = escr | भाग;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute rcar_du_r8a7795_es1[] = अणु
	अणु .soc_id = "r8a7795", .revision = "ES1.*" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम rcar_du_crtc_set_display_timing(काष्ठा rcar_du_crtc *rcrtc)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &rcrtc->crtc.state->adjusted_mode;
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	अचिन्हित दीर्घ mode_घड़ी = mode->घड़ी * 1000;
	u32 dsmr;
	u32 escr;

	अगर (rcdu->info->dpll_mask & (1 << rcrtc->index)) अणु
		अचिन्हित दीर्घ target = mode_घड़ी;
		काष्ठा dpll_info dpll = अणु 0 पूर्ण;
		अचिन्हित दीर्घ extclk;
		u32 dpllcr;
		u32 भाग = 0;

		/*
		 * DU channels that have a display PLL can't use the पूर्णांकernal
		 * प्रणाली घड़ी, and have no पूर्णांकernal घड़ी भागider.
		 */

		/*
		 * The H3 ES1.x exhibits करोt घड़ी duty cycle stability issues.
		 * We can work around them by configuring the DPLL to twice the
		 * desired frequency, coupled with a /2 post-भागider. Restrict
		 * the workaround to H3 ES1.x as ES2.0 and all other SoCs have
		 * no post-भागider when a display PLL is present (as shown by
		 * the workaround अवरोधing HDMI output on M3-W during testing).
		 */
		अगर (soc_device_match(rcar_du_r8a7795_es1)) अणु
			target *= 2;
			भाग = 1;
		पूर्ण

		extclk = clk_get_rate(rcrtc->extघड़ी);
		rcar_du_dpll_भागider(rcrtc, &dpll, extclk, target);

		dpllcr = DPLLCR_CODE | DPLLCR_CLKE
		       | DPLLCR_FDPLL(dpll.fdpll)
		       | DPLLCR_N(dpll.n) | DPLLCR_M(dpll.m)
		       | DPLLCR_STBY;

		अगर (rcrtc->index == 1)
			dpllcr |= DPLLCR_PLCS1
			       |  DPLLCR_INCS_DOTCLKIN1;
		अन्यथा
			dpllcr |= DPLLCR_PLCS0
			       |  DPLLCR_INCS_DOTCLKIN0;

		rcar_du_group_ग_लिखो(rcrtc->group, DPLLCR, dpllcr);

		escr = ESCR_DCLKSEL_DCLKIN | भाग;
	पूर्ण अन्यथा अगर (rcdu->info->lvds_clk_mask & BIT(rcrtc->index)) अणु
		/*
		 * Use the LVDS PLL output as the करोt घड़ी when outputting to
		 * the LVDS encoder on an SoC that supports this घड़ी routing
		 * option. We use the घड़ी directly in that हाल, without any
		 * additional भागider.
		 */
		escr = ESCR_DCLKSEL_DCLKIN;
	पूर्ण अन्यथा अणु
		काष्ठा du_clk_params params = अणु .dअगरf = (अचिन्हित दीर्घ)-1 पूर्ण;

		rcar_du_escr_भागider(rcrtc->घड़ी, mode_घड़ी,
				     ESCR_DCLKSEL_CLKS, &params);
		अगर (rcrtc->extघड़ी)
			rcar_du_escr_भागider(rcrtc->extघड़ी, mode_घड़ी,
					     ESCR_DCLKSEL_DCLKIN, &params);

		dev_dbg(rcrtc->dev->dev, "mode clock %lu %s rate %lu\n",
			mode_घड़ी, params.clk == rcrtc->घड़ी ? "cpg" : "ext",
			params.rate);

		clk_set_rate(params.clk, params.rate);
		escr = params.escr;
	पूर्ण

	dev_dbg(rcrtc->dev->dev, "%s: ESCR 0x%08x\n", __func__, escr);

	rcar_du_crtc_ग_लिखो(rcrtc, rcrtc->index % 2 ? ESCR13 : ESCR02, escr);
	rcar_du_crtc_ग_लिखो(rcrtc, rcrtc->index % 2 ? OTAR13 : OTAR02, 0);

	/* Signal polarities */
	dsmr = ((mode->flags & DRM_MODE_FLAG_PVSYNC) ? DSMR_VSL : 0)
	     | ((mode->flags & DRM_MODE_FLAG_PHSYNC) ? DSMR_HSL : 0)
	     | ((mode->flags & DRM_MODE_FLAG_INTERLACE) ? DSMR_ODEV : 0)
	     | DSMR_DIPM_DISP | DSMR_CSPM;
	rcar_du_crtc_ग_लिखो(rcrtc, DSMR, dsmr);

	/* Display timings */
	rcar_du_crtc_ग_लिखो(rcrtc, HDSR, mode->htotal - mode->hsync_start - 19);
	rcar_du_crtc_ग_लिखो(rcrtc, HDER, mode->htotal - mode->hsync_start +
					mode->hdisplay - 19);
	rcar_du_crtc_ग_लिखो(rcrtc, HSWR, mode->hsync_end -
					mode->hsync_start - 1);
	rcar_du_crtc_ग_लिखो(rcrtc, HCR,  mode->htotal - 1);

	rcar_du_crtc_ग_लिखो(rcrtc, VDSR, mode->crtc_vtotal -
					mode->crtc_vsync_end - 2);
	rcar_du_crtc_ग_लिखो(rcrtc, VDER, mode->crtc_vtotal -
					mode->crtc_vsync_end +
					mode->crtc_vdisplay - 2);
	rcar_du_crtc_ग_लिखो(rcrtc, VSPR, mode->crtc_vtotal -
					mode->crtc_vsync_end +
					mode->crtc_vsync_start - 1);
	rcar_du_crtc_ग_लिखो(rcrtc, VCR,  mode->crtc_vtotal - 1);

	rcar_du_crtc_ग_लिखो(rcrtc, DESR,  mode->htotal - mode->hsync_start - 1);
	rcar_du_crtc_ग_लिखो(rcrtc, DEWR,  mode->hdisplay);
पूर्ण

अटल अचिन्हित पूर्णांक plane_zpos(काष्ठा rcar_du_plane *plane)
अणु
	वापस plane->plane.state->normalized_zpos;
पूर्ण

अटल स्थिर काष्ठा rcar_du_क्रमmat_info *
plane_क्रमmat(काष्ठा rcar_du_plane *plane)
अणु
	वापस to_rcar_plane_state(plane->plane.state)->क्रमmat;
पूर्ण

अटल व्योम rcar_du_crtc_update_planes(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा rcar_du_plane *planes[RCAR_DU_NUM_HW_PLANES];
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	अचिन्हित पूर्णांक num_planes = 0;
	अचिन्हित पूर्णांक dptsr_planes;
	अचिन्हित पूर्णांक hwplanes = 0;
	अचिन्हित पूर्णांक prio = 0;
	अचिन्हित पूर्णांक i;
	u32 dspr = 0;

	क्रम (i = 0; i < rcrtc->group->num_planes; ++i) अणु
		काष्ठा rcar_du_plane *plane = &rcrtc->group->planes[i];
		अचिन्हित पूर्णांक j;

		अगर (plane->plane.state->crtc != &rcrtc->crtc ||
		    !plane->plane.state->visible)
			जारी;

		/* Insert the plane in the sorted planes array. */
		क्रम (j = num_planes++; j > 0; --j) अणु
			अगर (plane_zpos(planes[j-1]) <= plane_zpos(plane))
				अवरोध;
			planes[j] = planes[j-1];
		पूर्ण

		planes[j] = plane;
		prio += plane_क्रमmat(plane)->planes * 4;
	पूर्ण

	क्रम (i = 0; i < num_planes; ++i) अणु
		काष्ठा rcar_du_plane *plane = planes[i];
		काष्ठा drm_plane_state *state = plane->plane.state;
		अचिन्हित पूर्णांक index = to_rcar_plane_state(state)->hwindex;

		prio -= 4;
		dspr |= (index + 1) << prio;
		hwplanes |= 1 << index;

		अगर (plane_क्रमmat(plane)->planes == 2) अणु
			index = (index + 1) % 8;

			prio -= 4;
			dspr |= (index + 1) << prio;
			hwplanes |= 1 << index;
		पूर्ण
	पूर्ण

	/* If VSP+DU पूर्णांकegration is enabled the plane assignment is fixed. */
	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE)) अणु
		अगर (rcdu->info->gen < 3) अणु
			dspr = (rcrtc->index % 2) + 1;
			hwplanes = 1 << (rcrtc->index % 2);
		पूर्ण अन्यथा अणु
			dspr = (rcrtc->index % 2) ? 3 : 1;
			hwplanes = 1 << ((rcrtc->index % 2) ? 2 : 0);
		पूर्ण
	पूर्ण

	/*
	 * Update the planes to display timing and करोt घड़ी generator
	 * associations.
	 *
	 * Updating the DPTSR रेजिस्टर requires restarting the CRTC group,
	 * resulting in visible flicker. To mitigate the issue only update the
	 * association अगर needed by enabled planes. Planes being disabled will
	 * keep their current association.
	 */
	mutex_lock(&rcrtc->group->lock);

	dptsr_planes = rcrtc->index % 2 ? rcrtc->group->dptsr_planes | hwplanes
		     : rcrtc->group->dptsr_planes & ~hwplanes;

	अगर (dptsr_planes != rcrtc->group->dptsr_planes) अणु
		rcar_du_group_ग_लिखो(rcrtc->group, DPTSR,
				    (dptsr_planes << 16) | dptsr_planes);
		rcrtc->group->dptsr_planes = dptsr_planes;

		अगर (rcrtc->group->used_crtcs)
			rcar_du_group_restart(rcrtc->group);
	पूर्ण

	/* Restart the group अगर plane sources have changed. */
	अगर (rcrtc->group->need_restart)
		rcar_du_group_restart(rcrtc->group);

	mutex_unlock(&rcrtc->group->lock);

	rcar_du_group_ग_लिखो(rcrtc->group, rcrtc->index % 2 ? DS2PR : DS1PR,
			    dspr);
पूर्ण

/* -----------------------------------------------------------------------------
 * Page Flip
 */

व्योम rcar_du_crtc_finish_page_flip(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा drm_device *dev = rcrtc->crtc.dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = rcrtc->event;
	rcrtc->event = शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	अगर (event == शून्य)
		वापस;

	spin_lock_irqsave(&dev->event_lock, flags);
	drm_crtc_send_vblank_event(&rcrtc->crtc, event);
	wake_up(&rcrtc->flip_रुको);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	drm_crtc_vblank_put(&rcrtc->crtc);
पूर्ण

अटल bool rcar_du_crtc_page_flip_pending(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा drm_device *dev = rcrtc->crtc.dev;
	अचिन्हित दीर्घ flags;
	bool pending;

	spin_lock_irqsave(&dev->event_lock, flags);
	pending = rcrtc->event != शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	वापस pending;
पूर्ण

अटल व्योम rcar_du_crtc_रुको_page_flip(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	अगर (रुको_event_समयout(rcrtc->flip_रुको,
			       !rcar_du_crtc_page_flip_pending(rcrtc),
			       msecs_to_jअगरfies(50)))
		वापस;

	dev_warn(rcdu->dev, "page flip timeout\n");

	rcar_du_crtc_finish_page_flip(rcrtc);
पूर्ण

/* -----------------------------------------------------------------------------
 * Color Management Module (CMM)
 */

अटल पूर्णांक rcar_du_cmm_check(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_crtc_state *state)
अणु
	काष्ठा drm_property_blob *drm_lut = state->gamma_lut;
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा device *dev = rcrtc->dev->dev;

	अगर (!drm_lut)
		वापस 0;

	/* We only accept fully populated LUT tables. */
	अगर (drm_color_lut_size(drm_lut) != CM2_LUT_SIZE) अणु
		dev_err(dev, "invalid gamma lut size: %zu bytes\n",
			drm_lut->length);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcar_du_cmm_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_property_blob *drm_lut = crtc->state->gamma_lut;
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा rcar_cmm_config cmm_config = अणुपूर्ण;

	अगर (!rcrtc->cmm)
		वापस;

	अगर (drm_lut)
		cmm_config.lut.table = (काष्ठा drm_color_lut *)drm_lut->data;

	rcar_cmm_setup(rcrtc->cmm, &cmm_config);
पूर्ण

/* -----------------------------------------------------------------------------
 * Start/Stop and Suspend/Resume
 */

अटल व्योम rcar_du_crtc_setup(काष्ठा rcar_du_crtc *rcrtc)
अणु
	/* Set display off and background to black */
	rcar_du_crtc_ग_लिखो(rcrtc, DOOR, DOOR_RGB(0, 0, 0));
	rcar_du_crtc_ग_लिखो(rcrtc, BPOR, BPOR_RGB(0, 0, 0));

	/* Configure display timings and output routing */
	rcar_du_crtc_set_display_timing(rcrtc);
	rcar_du_group_set_routing(rcrtc->group);

	/* Start with all planes disabled. */
	rcar_du_group_ग_लिखो(rcrtc->group, rcrtc->index % 2 ? DS2PR : DS1PR, 0);

	/* Enable the VSP compositor. */
	अगर (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_enable(rcrtc);

	/* Turn vertical blanking पूर्णांकerrupt reporting on. */
	drm_crtc_vblank_on(&rcrtc->crtc);
पूर्ण

अटल पूर्णांक rcar_du_crtc_get(काष्ठा rcar_du_crtc *rcrtc)
अणु
	पूर्णांक ret;

	/*
	 * Guard against द्विगुन-get, as the function is called from both the
	 * .atomic_enable() and .atomic_begin() handlers.
	 */
	अगर (rcrtc->initialized)
		वापस 0;

	ret = clk_prepare_enable(rcrtc->घड़ी);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(rcrtc->extघड़ी);
	अगर (ret < 0)
		जाओ error_घड़ी;

	ret = rcar_du_group_get(rcrtc->group);
	अगर (ret < 0)
		जाओ error_group;

	rcar_du_crtc_setup(rcrtc);
	rcrtc->initialized = true;

	वापस 0;

error_group:
	clk_disable_unprepare(rcrtc->extघड़ी);
error_घड़ी:
	clk_disable_unprepare(rcrtc->घड़ी);
	वापस ret;
पूर्ण

अटल व्योम rcar_du_crtc_put(काष्ठा rcar_du_crtc *rcrtc)
अणु
	rcar_du_group_put(rcrtc->group);

	clk_disable_unprepare(rcrtc->extघड़ी);
	clk_disable_unprepare(rcrtc->घड़ी);

	rcrtc->initialized = false;
पूर्ण

अटल व्योम rcar_du_crtc_start(काष्ठा rcar_du_crtc *rcrtc)
अणु
	bool पूर्णांकerlaced;

	/*
	 * Select master sync mode. This enables display operation in master
	 * sync mode (with the HSYNC and VSYNC संकेतs configured as outमाला_दो and
	 * actively driven).
	 */
	पूर्णांकerlaced = rcrtc->crtc.mode.flags & DRM_MODE_FLAG_INTERLACE;
	rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_TVM_MASK | DSYSR_SCM_MASK,
				   (पूर्णांकerlaced ? DSYSR_SCM_INT_VIDEO : 0) |
				   DSYSR_TVM_MASTER);

	rcar_du_group_start_stop(rcrtc->group, true);
पूर्ण

अटल व्योम rcar_du_crtc_disable_planes(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	काष्ठा drm_crtc *crtc = &rcrtc->crtc;
	u32 status;

	/* Make sure vblank पूर्णांकerrupts are enabled. */
	drm_crtc_vblank_get(crtc);

	/*
	 * Disable planes and calculate how many vertical blanking पूर्णांकerrupts we
	 * have to रुको क्रम. If a vertical blanking पूर्णांकerrupt has been triggered
	 * but not processed yet, we करोn't know whether it occurred beक्रमe or
	 * after the planes got disabled. We thus have to रुको क्रम two vblank
	 * पूर्णांकerrupts in that हाल.
	 */
	spin_lock_irq(&rcrtc->vblank_lock);
	rcar_du_group_ग_लिखो(rcrtc->group, rcrtc->index % 2 ? DS2PR : DS1PR, 0);
	status = rcar_du_crtc_पढ़ो(rcrtc, DSSR);
	rcrtc->vblank_count = status & DSSR_VBK ? 2 : 1;
	spin_unlock_irq(&rcrtc->vblank_lock);

	अगर (!रुको_event_समयout(rcrtc->vblank_रुको, rcrtc->vblank_count == 0,
				msecs_to_jअगरfies(100)))
		dev_warn(rcdu->dev, "vertical blanking timeout\n");

	drm_crtc_vblank_put(crtc);
पूर्ण

अटल व्योम rcar_du_crtc_stop(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा drm_crtc *crtc = &rcrtc->crtc;

	/*
	 * Disable all planes and रुको क्रम the change to take effect. This is
	 * required as the plane enable रेजिस्टरs are updated on vblank, and no
	 * vblank will occur once the CRTC is stopped. Disabling planes when
	 * starting the CRTC thus wouldn't be enough as it would start scanning
	 * out immediately from old frame buffers until the next vblank.
	 *
	 * This increases the CRTC stop delay, especially when multiple CRTCs
	 * are stopped in one operation as we now रुको क्रम one vblank per CRTC.
	 * Whether this can be improved needs to be researched.
	 */
	rcar_du_crtc_disable_planes(rcrtc);

	/*
	 * Disable vertical blanking पूर्णांकerrupt reporting. We first need to रुको
	 * क्रम page flip completion beक्रमe stopping the CRTC as userspace
	 * expects page flips to eventually complete.
	 */
	rcar_du_crtc_रुको_page_flip(rcrtc);
	drm_crtc_vblank_off(crtc);

	/* Disable the VSP compositor. */
	अगर (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_disable(rcrtc);

	अगर (rcrtc->cmm)
		rcar_cmm_disable(rcrtc->cmm);

	/*
	 * Select चयन sync mode. This stops display operation and configures
	 * the HSYNC and VSYNC संकेतs as inमाला_दो.
	 *
	 * TODO: Find another way to stop the display क्रम DUs that करोn't support
	 * TVM sync.
	 */
	अगर (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_TVM_SYNC))
		rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_TVM_MASK,
					   DSYSR_TVM_SWITCH);

	rcar_du_group_start_stop(rcrtc->group, false);
पूर्ण

/* -----------------------------------------------------------------------------
 * CRTC Functions
 */

अटल पूर्णांक rcar_du_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा rcar_du_crtc_state *rstate = to_rcar_crtc_state(crtc_state);
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	ret = rcar_du_cmm_check(crtc, crtc_state);
	अगर (ret)
		वापस ret;

	/* Store the routes from the CRTC output to the DU outमाला_दो. */
	rstate->outमाला_दो = 0;

	drm_क्रम_each_encoder_mask(encoder, crtc->dev,
				  crtc_state->encoder_mask) अणु
		काष्ठा rcar_du_encoder *renc;

		/* Skip the ग_लिखोback encoder. */
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_VIRTUAL)
			जारी;

		renc = to_rcar_encoder(encoder);
		rstate->outमाला_दो |= BIT(renc->output);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcar_du_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा rcar_du_crtc_state *rstate = to_rcar_crtc_state(crtc->state);
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	अगर (rcrtc->cmm)
		rcar_cmm_enable(rcrtc->cmm);
	rcar_du_crtc_get(rcrtc);

	/*
	 * On D3/E3 the करोt घड़ी is provided by the LVDS encoder attached to
	 * the DU channel. We need to enable its घड़ी output explicitly अगर
	 * the LVDS output is disabled.
	 */
	अगर (rcdu->info->lvds_clk_mask & BIT(rcrtc->index) &&
	    rstate->outमाला_दो == BIT(RCAR_DU_OUTPUT_DPAD0)) अणु
		काष्ठा drm_bridge *bridge = rcdu->lvds[rcrtc->index];
		स्थिर काष्ठा drm_display_mode *mode =
			&crtc->state->adjusted_mode;

		rcar_lvds_clk_enable(bridge, mode->घड़ी * 1000);
	पूर्ण

	rcar_du_crtc_start(rcrtc);

	/*
	 * TODO: The chip manual indicates that CMM tables should be written
	 * after the DU channel has been activated. Investigate the impact
	 * of this restriction on the first displayed frame.
	 */
	rcar_du_cmm_setup(crtc);
पूर्ण

अटल व्योम rcar_du_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा rcar_du_crtc_state *rstate = to_rcar_crtc_state(old_state);
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;

	rcar_du_crtc_stop(rcrtc);
	rcar_du_crtc_put(rcrtc);

	अगर (rcdu->info->lvds_clk_mask & BIT(rcrtc->index) &&
	    rstate->outमाला_दो == BIT(RCAR_DU_OUTPUT_DPAD0)) अणु
		काष्ठा drm_bridge *bridge = rcdu->lvds[rcrtc->index];

		/*
		 * Disable the LVDS घड़ी output, see
		 * rcar_du_crtc_atomic_enable().
		 */
		rcar_lvds_clk_disable(bridge);
	पूर्ण

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल व्योम rcar_du_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	WARN_ON(!crtc->state->enable);

	/*
	 * If a mode set is in progress we can be called with the CRTC disabled.
	 * We thus need to first get and setup the CRTC in order to configure
	 * planes. We must *not* put the CRTC in .atomic_flush(), as it must be
	 * kept awake until the .atomic_enable() call that will follow. The get
	 * operation in .atomic_enable() will in that हाल be a no-op, and the
	 * CRTC will be put later in .atomic_disable().
	 *
	 * If a mode set is not in progress the CRTC is enabled, and the
	 * following get call will be a no-op. There is thus no need to balance
	 * it in .atomic_flush() either.
	 */
	rcar_du_crtc_get(rcrtc);

	/* If the active state changed, we let .atomic_enable handle CMM. */
	अगर (crtc->state->color_mgmt_changed && !crtc->state->active_changed)
		rcar_du_cmm_setup(crtc);

	अगर (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_atomic_begin(rcrtc);
पूर्ण

अटल व्योम rcar_du_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा drm_device *dev = rcrtc->crtc.dev;
	अचिन्हित दीर्घ flags;

	rcar_du_crtc_update_planes(rcrtc);

	अगर (crtc->state->event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&dev->event_lock, flags);
		rcrtc->event = crtc->state->event;
		crtc->state->event = शून्य;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण

	अगर (rcar_du_has(rcrtc->dev, RCAR_DU_FEATURE_VSP1_SOURCE))
		rcar_du_vsp_atomic_flush(rcrtc);
पूर्ण

अटल क्रमागत drm_mode_status
rcar_du_crtc_mode_valid(काष्ठा drm_crtc *crtc,
			स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	bool पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	अचिन्हित पूर्णांक vbp;

	अगर (पूर्णांकerlaced && !rcar_du_has(rcdu, RCAR_DU_FEATURE_INTERLACED))
		वापस MODE_NO_INTERLACE;

	/*
	 * The hardware requires a minimum combined horizontal sync and back
	 * porch of 20 pixels and a minimum vertical back porch of 3 lines.
	 */
	अगर (mode->htotal - mode->hsync_start < 20)
		वापस MODE_HBLANK_NARROW;

	vbp = (mode->vtotal - mode->vsync_end) / (पूर्णांकerlaced ? 2 : 1);
	अगर (vbp < 3)
		वापस MODE_VBLANK_NARROW;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs crtc_helper_funcs = अणु
	.atomic_check = rcar_du_crtc_atomic_check,
	.atomic_begin = rcar_du_crtc_atomic_begin,
	.atomic_flush = rcar_du_crtc_atomic_flush,
	.atomic_enable = rcar_du_crtc_atomic_enable,
	.atomic_disable = rcar_du_crtc_atomic_disable,
	.mode_valid = rcar_du_crtc_mode_valid,
पूर्ण;

अटल व्योम rcar_du_crtc_crc_init(काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	स्थिर अक्षर **sources;
	अचिन्हित पूर्णांक count;
	पूर्णांक i = -1;

	/* CRC available only on Gen3 HW. */
	अगर (rcdu->info->gen < 3)
		वापस;

	/* Reserve 1 क्रम "auto" source. */
	count = rcrtc->vsp->num_planes + 1;

	sources = kदो_स्मृति_array(count, माप(*sources), GFP_KERNEL);
	अगर (!sources)
		वापस;

	sources[0] = kstrdup("auto", GFP_KERNEL);
	अगर (!sources[0])
		जाओ error;

	क्रम (i = 0; i < rcrtc->vsp->num_planes; ++i) अणु
		काष्ठा drm_plane *plane = &rcrtc->vsp->planes[i].plane;
		अक्षर name[16];

		प्र_लिखो(name, "plane%u", plane->base.id);
		sources[i + 1] = kstrdup(name, GFP_KERNEL);
		अगर (!sources[i + 1])
			जाओ error;
	पूर्ण

	rcrtc->sources = sources;
	rcrtc->sources_count = count;
	वापस;

error:
	जबतक (i >= 0) अणु
		kमुक्त(sources[i]);
		i--;
	पूर्ण
	kमुक्त(sources);
पूर्ण

अटल व्योम rcar_du_crtc_crc_cleanup(काष्ठा rcar_du_crtc *rcrtc)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!rcrtc->sources)
		वापस;

	क्रम (i = 0; i < rcrtc->sources_count; i++)
		kमुक्त(rcrtc->sources[i]);
	kमुक्त(rcrtc->sources);

	rcrtc->sources = शून्य;
	rcrtc->sources_count = 0;
पूर्ण

अटल काष्ठा drm_crtc_state *
rcar_du_crtc_atomic_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rcar_du_crtc_state *state;
	काष्ठा rcar_du_crtc_state *copy;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	state = to_rcar_crtc_state(crtc->state);
	copy = kmemdup(state, माप(*state), GFP_KERNEL);
	अगर (copy == शून्य)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &copy->state);

	वापस &copy->state;
पूर्ण

अटल व्योम rcar_du_crtc_atomic_destroy_state(काष्ठा drm_crtc *crtc,
					      काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(to_rcar_crtc_state(state));
पूर्ण

अटल व्योम rcar_du_crtc_cleanup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_crc_cleanup(rcrtc);

	वापस drm_crtc_cleanup(crtc);
पूर्ण

अटल व्योम rcar_du_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rcar_du_crtc_state *state;

	अगर (crtc->state) अणु
		rcar_du_crtc_atomic_destroy_state(crtc, crtc->state);
		crtc->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस;

	state->crc.source = VSP1_DU_CRC_NONE;
	state->crc.index = 0;

	__drm_atomic_helper_crtc_reset(crtc, &state->state);
पूर्ण

अटल पूर्णांक rcar_du_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_ग_लिखो(rcrtc, DSRCR, DSRCR_VBCL);
	rcar_du_crtc_set(rcrtc, DIER, DIER_VBE);
	rcrtc->vblank_enable = true;

	वापस 0;
पूर्ण

अटल व्योम rcar_du_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_clr(rcrtc, DIER, DIER_VBE);
	rcrtc->vblank_enable = false;
पूर्ण

अटल पूर्णांक rcar_du_crtc_parse_crc_source(काष्ठा rcar_du_crtc *rcrtc,
					 स्थिर अक्षर *source_name,
					 क्रमागत vsp1_du_crc_source *source)
अणु
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	/*
	 * Parse the source name. Supported values are "plane%u" to compute the
	 * CRC on an input plane (%u is the plane ID), and "auto" to compute the
	 * CRC on the composer (VSP) output.
	 */

	अगर (!source_name) अणु
		*source = VSP1_DU_CRC_NONE;
		वापस 0;
	पूर्ण अन्यथा अगर (!म_भेद(source_name, "auto")) अणु
		*source = VSP1_DU_CRC_OUTPUT;
		वापस 0;
	पूर्ण अन्यथा अगर (strstarts(source_name, "plane")) अणु
		अचिन्हित पूर्णांक i;

		*source = VSP1_DU_CRC_PLANE;

		ret = kstrtouपूर्णांक(source_name + म_माप("plane"), 10, &index);
		अगर (ret < 0)
			वापस ret;

		क्रम (i = 0; i < rcrtc->vsp->num_planes; ++i) अणु
			अगर (index == rcrtc->vsp->planes[i].plane.base.id)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rcar_du_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc,
					  स्थिर अक्षर *source_name,
					  माप_प्रकार *values_cnt)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	क्रमागत vsp1_du_crc_source source;

	अगर (rcar_du_crtc_parse_crc_source(rcrtc, source_name, &source) < 0) अणु
		DRM_DEBUG_DRIVER("unknown source %s\n", source_name);
		वापस -EINVAL;
	पूर्ण

	*values_cnt = 1;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर *
rcar_du_crtc_get_crc_sources(काष्ठा drm_crtc *crtc, माप_प्रकार *count)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	*count = rcrtc->sources_count;
	वापस rcrtc->sources;
पूर्ण

अटल पूर्णांक rcar_du_crtc_set_crc_source(काष्ठा drm_crtc *crtc,
				       स्थिर अक्षर *source_name)
अणु
	काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_atomic_state *state;
	क्रमागत vsp1_du_crc_source source;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	ret = rcar_du_crtc_parse_crc_source(rcrtc, source_name, &source);
	अगर (ret < 0)
		वापस ret;

	index = ret;

	/* Perक्रमm an atomic commit to set the CRC source. */
	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(crtc->dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	state->acquire_ctx = &ctx;

retry:
	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (!IS_ERR(crtc_state)) अणु
		काष्ठा rcar_du_crtc_state *rcrtc_state;

		rcrtc_state = to_rcar_crtc_state(crtc_state);
		rcrtc_state->crc.source = source;
		rcrtc_state->crc.index = index;

		ret = drm_atomic_commit(state);
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(crtc_state);
	पूर्ण

	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

unlock:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs crtc_funcs_gen2 = अणु
	.reset = rcar_du_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = rcar_du_crtc_atomic_duplicate_state,
	.atomic_destroy_state = rcar_du_crtc_atomic_destroy_state,
	.enable_vblank = rcar_du_crtc_enable_vblank,
	.disable_vblank = rcar_du_crtc_disable_vblank,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs crtc_funcs_gen3 = अणु
	.reset = rcar_du_crtc_reset,
	.destroy = rcar_du_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = rcar_du_crtc_atomic_duplicate_state,
	.atomic_destroy_state = rcar_du_crtc_atomic_destroy_state,
	.enable_vblank = rcar_du_crtc_enable_vblank,
	.disable_vblank = rcar_du_crtc_disable_vblank,
	.set_crc_source = rcar_du_crtc_set_crc_source,
	.verअगरy_crc_source = rcar_du_crtc_verअगरy_crc_source,
	.get_crc_sources = rcar_du_crtc_get_crc_sources,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

अटल irqवापस_t rcar_du_crtc_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा rcar_du_crtc *rcrtc = arg;
	काष्ठा rcar_du_device *rcdu = rcrtc->dev;
	irqवापस_t ret = IRQ_NONE;
	u32 status;

	spin_lock(&rcrtc->vblank_lock);

	status = rcar_du_crtc_पढ़ो(rcrtc, DSSR);
	rcar_du_crtc_ग_लिखो(rcrtc, DSRCR, status & DSRCR_MASK);

	अगर (status & DSSR_VBK) अणु
		/*
		 * Wake up the vblank रुको अगर the counter reaches 0. This must
		 * be रक्षित by the vblank_lock to aव्योम races in
		 * rcar_du_crtc_disable_planes().
		 */
		अगर (rcrtc->vblank_count) अणु
			अगर (--rcrtc->vblank_count == 0)
				wake_up(&rcrtc->vblank_रुको);
		पूर्ण
	पूर्ण

	spin_unlock(&rcrtc->vblank_lock);

	अगर (status & DSSR_VBK) अणु
		अगर (rcdu->info->gen < 3) अणु
			drm_crtc_handle_vblank(&rcrtc->crtc);
			rcar_du_crtc_finish_page_flip(rcrtc);
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization
 */

पूर्णांक rcar_du_crtc_create(काष्ठा rcar_du_group *rgrp, अचिन्हित पूर्णांक swindex,
			अचिन्हित पूर्णांक hwindex)
अणु
	अटल स्थिर अचिन्हित पूर्णांक mmio_offsets[] = अणु
		DU0_REG_OFFSET, DU1_REG_OFFSET, DU2_REG_OFFSET, DU3_REG_OFFSET
	पूर्ण;

	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(rcdu->dev);
	काष्ठा rcar_du_crtc *rcrtc = &rcdu->crtcs[swindex];
	काष्ठा drm_crtc *crtc = &rcrtc->crtc;
	काष्ठा drm_plane *primary;
	अचिन्हित पूर्णांक irqflags;
	काष्ठा clk *clk;
	अक्षर clk_name[9];
	अक्षर *name;
	पूर्णांक irq;
	पूर्णांक ret;

	/* Get the CRTC घड़ी and the optional बाह्यal घड़ी. */
	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_CRTC_IRQ_CLOCK)) अणु
		प्र_लिखो(clk_name, "du.%u", hwindex);
		name = clk_name;
	पूर्ण अन्यथा अणु
		name = शून्य;
	पूर्ण

	rcrtc->घड़ी = devm_clk_get(rcdu->dev, name);
	अगर (IS_ERR(rcrtc->घड़ी)) अणु
		dev_err(rcdu->dev, "no clock for DU channel %u\n", hwindex);
		वापस PTR_ERR(rcrtc->घड़ी);
	पूर्ण

	प्र_लिखो(clk_name, "dclkin.%u", hwindex);
	clk = devm_clk_get(rcdu->dev, clk_name);
	अगर (!IS_ERR(clk)) अणु
		rcrtc->extघड़ी = clk;
	पूर्ण अन्यथा अगर (PTR_ERR(clk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (rcdu->info->dpll_mask & BIT(hwindex)) अणु
		/*
		 * DU channels that have a display PLL can't use the पूर्णांकernal
		 * प्रणाली घड़ी and thus require an बाह्यal घड़ी.
		 */
		ret = PTR_ERR(clk);
		dev_err(rcdu->dev, "can't get dclkin.%u: %d\n", hwindex, ret);
		वापस ret;
	पूर्ण

	init_रुकोqueue_head(&rcrtc->flip_रुको);
	init_रुकोqueue_head(&rcrtc->vblank_रुको);
	spin_lock_init(&rcrtc->vblank_lock);

	rcrtc->dev = rcdu;
	rcrtc->group = rgrp;
	rcrtc->mmio_offset = mmio_offsets[hwindex];
	rcrtc->index = hwindex;
	rcrtc->dsysr = (rcrtc->index % 2 ? 0 : DSYSR_DRES) | DSYSR_TVM_TVSYNC;

	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE))
		primary = &rcrtc->vsp->planes[rcrtc->vsp_pipe].plane;
	अन्यथा
		primary = &rgrp->planes[swindex % 2].plane;

	ret = drm_crtc_init_with_planes(&rcdu->ddev, crtc, primary, शून्य,
					rcdu->info->gen <= 2 ?
					&crtc_funcs_gen2 : &crtc_funcs_gen3,
					शून्य);
	अगर (ret < 0)
		वापस ret;

	/* CMM might be disabled क्रम this CRTC. */
	अगर (rcdu->cmms[swindex]) अणु
		rcrtc->cmm = rcdu->cmms[swindex];
		rgrp->cmms_mask |= BIT(hwindex % 2);

		drm_mode_crtc_set_gamma_size(crtc, CM2_LUT_SIZE);
		drm_crtc_enable_color_mgmt(crtc, 0, false, CM2_LUT_SIZE);
	पूर्ण

	drm_crtc_helper_add(crtc, &crtc_helper_funcs);

	/* Register the पूर्णांकerrupt handler. */
	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_CRTC_IRQ_CLOCK)) अणु
		/* The IRQ's are associated with the CRTC (sw)index. */
		irq = platक्रमm_get_irq(pdev, swindex);
		irqflags = 0;
	पूर्ण अन्यथा अणु
		irq = platक्रमm_get_irq(pdev, 0);
		irqflags = IRQF_SHARED;
	पूर्ण

	अगर (irq < 0) अणु
		dev_err(rcdu->dev, "no IRQ for CRTC %u\n", swindex);
		वापस irq;
	पूर्ण

	ret = devm_request_irq(rcdu->dev, irq, rcar_du_crtc_irq, irqflags,
			       dev_name(rcdu->dev), rcrtc);
	अगर (ret < 0) अणु
		dev_err(rcdu->dev,
			"failed to register IRQ for CRTC %u\n", swindex);
		वापस ret;
	पूर्ण

	rcar_du_crtc_crc_init(rcrtc);

	वापस 0;
पूर्ण
