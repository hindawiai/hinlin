<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on sources as follows:
 *
 * Copyright (C) 2006-2008 Intel Corporation
 * Copyright (C) 2007 Amos Lee <amos_lee@storlinksemi.com>
 * Copyright (C) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 * Copyright (C) 2017 Eric Anholt
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/delay.h>

#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_vblank.h>

#समावेश "tve200_drm.h"

irqवापस_t tve200_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tve200_drm_dev_निजी *priv = data;
	u32 stat;
	u32 val;

	stat = पढ़ोl(priv->regs + TVE200_INT_STAT);

	अगर (!stat)
		वापस IRQ_NONE;

	/*
	 * Vblank IRQ
	 *
	 * The hardware is a bit tilted: the line stays high after clearing
	 * the vblank IRQ, firing many more पूर्णांकerrupts. We counter this
	 * by toggling the IRQ back and क्रमth from firing at vblank and
	 * firing at start of active image, which works around the problem
	 * since those occur strictly in sequence, and we get two IRQs क्रम each
	 * frame, one at start of Vblank (that we make call पूर्णांकo the CRTC) and
	 * another one at the start of the image (that we discard).
	 */
	अगर (stat & TVE200_INT_V_STATUS) अणु
		val = पढ़ोl(priv->regs + TVE200_CTRL);
		/* We have an actual start of vsync */
		अगर (!(val & TVE200_VSTSTYPE_BITS)) अणु
			drm_crtc_handle_vblank(&priv->pipe.crtc);
			/* Toggle trigger to start of active image */
			val |= TVE200_VSTSTYPE_VAI;
		पूर्ण अन्यथा अणु
			/* Toggle trigger back to start of vsync */
			val &= ~TVE200_VSTSTYPE_BITS;
		पूर्ण
		ग_लिखोl(val, priv->regs + TVE200_CTRL);
	पूर्ण अन्यथा
		dev_err(priv->drm->dev, "stray IRQ %08x\n", stat);

	/* Clear the पूर्णांकerrupt once करोne */
	ग_लिखोl(stat, priv->regs + TVE200_INT_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tve200_display_check(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_plane_state *pstate,
			       काष्ठा drm_crtc_state *cstate)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *old_fb = pipe->plane.state->fb;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	/*
	 * We support these specअगरic resolutions and nothing अन्यथा.
	 */
	अगर (!(mode->hdisplay == 352 && mode->vdisplay == 240) && /* SIF(525) */
	    !(mode->hdisplay == 352 && mode->vdisplay == 288) && /* CIF(625) */
	    !(mode->hdisplay == 640 && mode->vdisplay == 480) && /* VGA */
	    !(mode->hdisplay == 720 && mode->vdisplay == 480) && /* D1 */
	    !(mode->hdisplay == 720 && mode->vdisplay == 576)) अणु /* D1 */
		DRM_DEBUG_KMS("unsupported display mode (%u x %u)\n",
			mode->hdisplay, mode->vdisplay);
		वापस -EINVAL;
	पूर्ण

	अगर (fb) अणु
		u32 offset = drm_fb_cma_get_gem_addr(fb, pstate, 0);

		/* FB base address must be dword aligned. */
		अगर (offset & 3) अणु
			DRM_DEBUG_KMS("FB not 32-bit aligned\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * There's no pitch register, the mode's hdisplay
		 * controls this.
		 */
		अगर (fb->pitches[0] != mode->hdisplay * fb->क्रमmat->cpp[0]) अणु
			DRM_DEBUG_KMS("can't handle pitches\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * We can't change the FB क्रमmat in a flicker-मुक्त
		 * manner (and only update it during CRTC enable).
		 */
		अगर (old_fb && old_fb->क्रमmat != fb->क्रमmat)
			cstate->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tve200_display_enable(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_crtc_state *cstate,
				 काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *fb = plane->state->fb;
	काष्ठा drm_connector *connector = priv->connector;
	u32 क्रमmat = fb->क्रमmat->क्रमmat;
	u32 ctrl1 = 0;
	पूर्णांक retries;

	clk_prepare_enable(priv->clk);

	/* Reset the TVE200 and रुको क्रम it to come back online */
	ग_लिखोl(TVE200_CTRL_4_RESET, priv->regs + TVE200_CTRL_4);
	क्रम (retries = 0; retries < 5; retries++) अणु
		usleep_range(30000, 50000);
		अगर (पढ़ोl(priv->regs + TVE200_CTRL_4) & TVE200_CTRL_4_RESET)
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (retries == 5 &&
	    पढ़ोl(priv->regs + TVE200_CTRL_4) & TVE200_CTRL_4_RESET) अणु
		dev_err(drm->dev, "can't get hardware out of reset\n");
		वापस;
	पूर्ण

	/* Function 1 */
	ctrl1 |= TVE200_CTRL_CSMODE;
	/* Interlace mode क्रम CCIR656: parameterize? */
	ctrl1 |= TVE200_CTRL_NONINTERLACE;
	/* 32 words per burst */
	ctrl1 |= TVE200_CTRL_BURST_32_WORDS;
	/* 16 retries */
	ctrl1 |= TVE200_CTRL_RETRYCNT_16;
	/* NTSC mode: parametrize? */
	ctrl1 |= TVE200_CTRL_NTSC;

	/* Vsync IRQ at start of Vsync at first */
	ctrl1 |= TVE200_VSTSTYPE_VSYNC;

	अगर (connector->display_info.bus_flags &
	    DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		ctrl1 |= TVE200_CTRL_TVCLKP;

	अगर ((mode->hdisplay == 352 && mode->vdisplay == 240) || /* SIF(525) */
	    (mode->hdisplay == 352 && mode->vdisplay == 288)) अणु /* CIF(625) */
		ctrl1 |= TVE200_CTRL_IPRESOL_CIF;
		dev_info(drm->dev, "CIF mode\n");
	पूर्ण अन्यथा अगर (mode->hdisplay == 640 && mode->vdisplay == 480) अणु
		ctrl1 |= TVE200_CTRL_IPRESOL_VGA;
		dev_info(drm->dev, "VGA mode\n");
	पूर्ण अन्यथा अगर ((mode->hdisplay == 720 && mode->vdisplay == 480) ||
		   (mode->hdisplay == 720 && mode->vdisplay == 576)) अणु
		ctrl1 |= TVE200_CTRL_IPRESOL_D1;
		dev_info(drm->dev, "D1 mode\n");
	पूर्ण

	अगर (क्रमmat & DRM_FORMAT_BIG_ENDIAN) अणु
		ctrl1 |= TVE200_CTRL_BBBP;
		क्रमmat &= ~DRM_FORMAT_BIG_ENDIAN;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
		ctrl1 |= TVE200_IPDMOD_RGB888;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		ctrl1 |= TVE200_IPDMOD_RGB565;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		ctrl1 |= TVE200_IPDMOD_RGB555;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		ctrl1 |= TVE200_IPDMOD_RGB888 | TVE200_BGR;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		ctrl1 |= TVE200_IPDMOD_RGB565 | TVE200_BGR;
		अवरोध;
	हाल DRM_FORMAT_XBGR1555:
		ctrl1 |= TVE200_IPDMOD_RGB555 | TVE200_BGR;
		अवरोध;
	हाल DRM_FORMAT_YUYV:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_CR0Y1CB0Y0;
		अवरोध;
	हाल DRM_FORMAT_YVYU:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_CB0Y1CR0Y0;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_Y1CR0Y0CB0;
		अवरोध;
	हाल DRM_FORMAT_VYUY:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_Y1CB0Y0CR0;
		अवरोध;
	हाल DRM_FORMAT_YUV420:
		ctrl1 |= TVE200_CTRL_YUV420;
		ctrl1 |= TVE200_IPDMOD_YUV420;
		अवरोध;
	शेष:
		dev_err(drm->dev, "Unknown FB format 0x%08x\n",
			fb->क्रमmat->क्रमmat);
		अवरोध;
	पूर्ण

	ctrl1 |= TVE200_TVEEN;

	/* Turn it on */
	ग_लिखोl(ctrl1, priv->regs + TVE200_CTRL);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम tve200_display_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;

	drm_crtc_vblank_off(crtc);

	/* Disable put पूर्णांकo reset and Power Down */
	ग_लिखोl(0, priv->regs + TVE200_CTRL);
	ग_लिखोl(TVE200_CTRL_4_RESET, priv->regs + TVE200_CTRL_4);

	clk_disable_unprepare(priv->clk);
पूर्ण

अटल व्योम tve200_display_update(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_plane_state *old_pstate)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_plane_state *pstate = plane->state;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	अगर (fb) अणु
		/* For RGB, the Y component is used as base address */
		ग_लिखोl(drm_fb_cma_get_gem_addr(fb, pstate, 0),
		       priv->regs + TVE200_Y_FRAME_BASE_ADDR);

		/* For three plane YUV we need two more addresses */
		अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_YUV420) अणु
			ग_लिखोl(drm_fb_cma_get_gem_addr(fb, pstate, 1),
			       priv->regs + TVE200_U_FRAME_BASE_ADDR);
			ग_लिखोl(drm_fb_cma_get_gem_addr(fb, pstate, 2),
			       priv->regs + TVE200_V_FRAME_BASE_ADDR);
		पूर्ण
	पूर्ण

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (crtc->state->active && drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक tve200_display_enable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;

	/* Clear any IRQs and enable */
	ग_लिखोl(0xFF, priv->regs + TVE200_INT_CLR);
	ग_लिखोl(TVE200_INT_V_STATUS, priv->regs + TVE200_INT_EN);
	वापस 0;
पूर्ण

अटल व्योम tve200_display_disable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;

	ग_लिखोl(0, priv->regs + TVE200_INT_EN);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs tve200_display_funcs = अणु
	.check = tve200_display_check,
	.enable = tve200_display_enable,
	.disable = tve200_display_disable,
	.update = tve200_display_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
	.enable_vblank = tve200_display_enable_vblank,
	.disable_vblank = tve200_display_disable_vblank,
पूर्ण;

पूर्णांक tve200_display_init(काष्ठा drm_device *drm)
अणु
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;
	पूर्णांक ret;
	अटल स्थिर u32 क्रमmats[] = अणु
		DRM_FORMAT_XRGB8888,
		DRM_FORMAT_XBGR8888,
		DRM_FORMAT_RGB565,
		DRM_FORMAT_BGR565,
		DRM_FORMAT_XRGB1555,
		DRM_FORMAT_XBGR1555,
		/*
		 * The controller actually supports any YCbCr ordering,
		 * क्रम packed YCbCr. This just lists the orderings that
		 * DRM supports.
		 */
		DRM_FORMAT_YUYV,
		DRM_FORMAT_YVYU,
		DRM_FORMAT_UYVY,
		DRM_FORMAT_VYUY,
		/* This uses three planes */
		DRM_FORMAT_YUV420,
	पूर्ण;

	ret = drm_simple_display_pipe_init(drm, &priv->pipe,
					   &tve200_display_funcs,
					   क्रमmats, ARRAY_SIZE(क्रमmats),
					   शून्य,
					   priv->connector);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
