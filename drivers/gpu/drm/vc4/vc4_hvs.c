<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Broadcom
 */

/**
 * DOC: VC4 HVS module.
 *
 * The Hardware Video Scaler (HVS) is the piece of hardware that करोes
 * translation, scaling, colorspace conversion, and compositing of
 * pixels stored in framebuffers पूर्णांकo a FIFO of pixels going out to
 * the Pixel Valve (CRTC).  It operates at the प्रणाली घड़ी rate (the
 * प्रणाली audio घड़ी gate, specअगरically), which is much higher than
 * the pixel घड़ी rate.
 *
 * There is a single global HVS, with multiple output FIFOs that can
 * be consumed by the PVs.  This file just manages the resources क्रम
 * the HVS, जबतक the vc4_crtc.c code actually drives HVS setup क्रम
 * each CRTC.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

अटल स्थिर काष्ठा debugfs_reg32 hvs_regs[] = अणु
	VC4_REG32(SCALER_DISPCTRL),
	VC4_REG32(SCALER_DISPSTAT),
	VC4_REG32(SCALER_DISPID),
	VC4_REG32(SCALER_DISPECTRL),
	VC4_REG32(SCALER_DISPPROF),
	VC4_REG32(SCALER_DISPDITHER),
	VC4_REG32(SCALER_DISPEOLN),
	VC4_REG32(SCALER_DISPLIST0),
	VC4_REG32(SCALER_DISPLIST1),
	VC4_REG32(SCALER_DISPLIST2),
	VC4_REG32(SCALER_DISPLSTAT),
	VC4_REG32(SCALER_DISPLACT0),
	VC4_REG32(SCALER_DISPLACT1),
	VC4_REG32(SCALER_DISPLACT2),
	VC4_REG32(SCALER_DISPCTRL0),
	VC4_REG32(SCALER_DISPBKGND0),
	VC4_REG32(SCALER_DISPSTAT0),
	VC4_REG32(SCALER_DISPBASE0),
	VC4_REG32(SCALER_DISPCTRL1),
	VC4_REG32(SCALER_DISPBKGND1),
	VC4_REG32(SCALER_DISPSTAT1),
	VC4_REG32(SCALER_DISPBASE1),
	VC4_REG32(SCALER_DISPCTRL2),
	VC4_REG32(SCALER_DISPBKGND2),
	VC4_REG32(SCALER_DISPSTAT2),
	VC4_REG32(SCALER_DISPBASE2),
	VC4_REG32(SCALER_DISPALPHA2),
	VC4_REG32(SCALER_OLEDOFFS),
	VC4_REG32(SCALER_OLEDCOEF0),
	VC4_REG32(SCALER_OLEDCOEF1),
	VC4_REG32(SCALER_OLEDCOEF2),
पूर्ण;

व्योम vc4_hvs_dump_state(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(&vc4->hvs->pdev->dev);
	पूर्णांक i;

	drm_prपूर्णांक_regset32(&p, &vc4->hvs->regset);

	DRM_INFO("HVS ctx:\n");
	क्रम (i = 0; i < 64; i += 4) अणु
		DRM_INFO("0x%08x (%s): 0x%08x 0x%08x 0x%08x 0x%08x\n",
			 i * 4, i < HVS_BOOTLOADER_DLIST_END ? "B" : "D",
			 पढ़ोl((u32 __iomem *)vc4->hvs->dlist + i + 0),
			 पढ़ोl((u32 __iomem *)vc4->hvs->dlist + i + 1),
			 पढ़ोl((u32 __iomem *)vc4->hvs->dlist + i + 2),
			 पढ़ोl((u32 __iomem *)vc4->hvs->dlist + i + 3));
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_hvs_debugfs_underrun(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_म_लिखो(&p, "%d\n", atomic_पढ़ो(&vc4->underrun));

	वापस 0;
पूर्ण

/* The filter kernel is composed of dwords each containing 3 9-bit
 * चिन्हित पूर्णांकegers packed next to each other.
 */
#घोषणा VC4_INT_TO_COEFF(coeff) (coeff & 0x1ff)
#घोषणा VC4_PPF_FILTER_WORD(c0, c1, c2)				\
	((((c0) & 0x1ff) << 0) |				\
	 (((c1) & 0x1ff) << 9) |				\
	 (((c2) & 0x1ff) << 18))

/* The whole filter kernel is arranged as the coefficients 0-16 going
 * up, then a pad, then 17-31 going करोwn and reversed within the
 * dwords.  This means that a linear phase kernel (where it's
 * symmetrical at the boundary between 15 and 16) has the last 5
 * dwords matching the first 5, but reversed.
 */
#घोषणा VC4_LINEAR_PHASE_KERNEL(c0, c1, c2, c3, c4, c5, c6, c7, c8,	\
				c9, c10, c11, c12, c13, c14, c15)	\
	अणुVC4_PPF_FILTER_WORD(c0, c1, c2),				\
	 VC4_PPF_FILTER_WORD(c3, c4, c5),				\
	 VC4_PPF_FILTER_WORD(c6, c7, c8),				\
	 VC4_PPF_FILTER_WORD(c9, c10, c11),				\
	 VC4_PPF_FILTER_WORD(c12, c13, c14),				\
	 VC4_PPF_FILTER_WORD(c15, c15, 0)पूर्ण

#घोषणा VC4_LINEAR_PHASE_KERNEL_DWORDS 6
#घोषणा VC4_KERNEL_DWORDS (VC4_LINEAR_PHASE_KERNEL_DWORDS * 2 - 1)

/* Recommended B=1/3, C=1/3 filter choice from Mitchell/Netravali.
 * http://www.cs.utexas.edu/~fussell/courses/cs384g/lectures/mitchell/Mitchell.pdf
 */
अटल स्थिर u32 mitchell_netravali_1_3_1_3_kernel[] =
	VC4_LINEAR_PHASE_KERNEL(0, -2, -6, -8, -10, -8, -3, 2, 18,
				50, 82, 119, 155, 187, 213, 227);

अटल पूर्णांक vc4_hvs_upload_linear_kernel(काष्ठा vc4_hvs *hvs,
					काष्ठा drm_mm_node *space,
					स्थिर u32 *kernel)
अणु
	पूर्णांक ret, i;
	u32 __iomem *dst_kernel;

	ret = drm_mm_insert_node(&hvs->dlist_mm, space, VC4_KERNEL_DWORDS);
	अगर (ret) अणु
		DRM_ERROR("Failed to allocate space for filter kernel: %d\n",
			  ret);
		वापस ret;
	पूर्ण

	dst_kernel = hvs->dlist + space->start;

	क्रम (i = 0; i < VC4_KERNEL_DWORDS; i++) अणु
		अगर (i < VC4_LINEAR_PHASE_KERNEL_DWORDS)
			ग_लिखोl(kernel[i], &dst_kernel[i]);
		अन्यथा अणु
			ग_लिखोl(kernel[VC4_KERNEL_DWORDS - i - 1],
			       &dst_kernel[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vc4_hvs_lut_load(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	u32 i;

	/* The LUT memory is laid out with each HVS channel in order,
	 * each of which takes 256 ग_लिखोs क्रम R, 256 क्रम G, then 256
	 * क्रम B.
	 */
	HVS_WRITE(SCALER_GAMADDR,
		  SCALER_GAMADDR_AUTOINC |
		  (vc4_state->asचिन्हित_channel * 3 * crtc->gamma_size));

	क्रम (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_r[i]);
	क्रम (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_g[i]);
	क्रम (i = 0; i < crtc->gamma_size; i++)
		HVS_WRITE(SCALER_GAMDATA, vc4_crtc->lut_b[i]);
पूर्ण

अटल व्योम vc4_hvs_update_gamma_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा drm_color_lut *lut = crtc->state->gamma_lut->data;
	u32 length = drm_color_lut_size(crtc->state->gamma_lut);
	u32 i;

	क्रम (i = 0; i < length; i++) अणु
		vc4_crtc->lut_r[i] = drm_color_lut_extract(lut[i].red, 8);
		vc4_crtc->lut_g[i] = drm_color_lut_extract(lut[i].green, 8);
		vc4_crtc->lut_b[i] = drm_color_lut_extract(lut[i].blue, 8);
	पूर्ण

	vc4_hvs_lut_load(crtc);
पूर्ण

पूर्णांक vc4_hvs_get_fअगरo_from_output(काष्ठा drm_device *dev, अचिन्हित पूर्णांक output)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	u32 reg;
	पूर्णांक ret;

	अगर (!vc4->hvs->hvs5)
		वापस output;

	चयन (output) अणु
	हाल 0:
		वापस 0;

	हाल 1:
		वापस 1;

	हाल 2:
		reg = HVS_READ(SCALER_DISPECTRL);
		ret = FIELD_GET(SCALER_DISPECTRL_DSP2_MUX_MASK, reg);
		अगर (ret == 0)
			वापस 2;

		वापस 0;

	हाल 3:
		reg = HVS_READ(SCALER_DISPCTRL);
		ret = FIELD_GET(SCALER_DISPCTRL_DSP3_MUX_MASK, reg);
		अगर (ret == 3)
			वापस -EPIPE;

		वापस ret;

	हाल 4:
		reg = HVS_READ(SCALER_DISPEOLN);
		ret = FIELD_GET(SCALER_DISPEOLN_DSP4_MUX_MASK, reg);
		अगर (ret == 3)
			वापस -EPIPE;

		वापस ret;

	हाल 5:
		reg = HVS_READ(SCALER_DISPDITHER);
		ret = FIELD_GET(SCALER_DISPDITHER_DSP5_MUX_MASK, reg);
		अगर (ret == 3)
			वापस -EPIPE;

		वापस ret;

	शेष:
		वापस -EPIPE;
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_hvs_init_channel(काष्ठा vc4_dev *vc4, काष्ठा drm_crtc *crtc,
				काष्ठा drm_display_mode *mode, bool oneshot)
अणु
	काष्ठा vc4_crtc_state *vc4_crtc_state = to_vc4_crtc_state(crtc->state);
	अचिन्हित पूर्णांक chan = vc4_crtc_state->asचिन्हित_channel;
	bool पूर्णांकerlace = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 dispbkgndx;
	u32 dispctrl;

	HVS_WRITE(SCALER_DISPCTRLX(chan), 0);
	HVS_WRITE(SCALER_DISPCTRLX(chan), SCALER_DISPCTRLX_RESET);
	HVS_WRITE(SCALER_DISPCTRLX(chan), 0);

	/* Turn on the scaler, which will रुको क्रम vstart to start
	 * compositing.
	 * When feeding the transposer, we should operate in oneshot
	 * mode.
	 */
	dispctrl = SCALER_DISPCTRLX_ENABLE;

	अगर (!vc4->hvs->hvs5)
		dispctrl |= VC4_SET_FIELD(mode->hdisplay,
					  SCALER_DISPCTRLX_WIDTH) |
			    VC4_SET_FIELD(mode->vdisplay,
					  SCALER_DISPCTRLX_HEIGHT) |
			    (oneshot ? SCALER_DISPCTRLX_ONESHOT : 0);
	अन्यथा
		dispctrl |= VC4_SET_FIELD(mode->hdisplay,
					  SCALER5_DISPCTRLX_WIDTH) |
			    VC4_SET_FIELD(mode->vdisplay,
					  SCALER5_DISPCTRLX_HEIGHT) |
			    (oneshot ? SCALER5_DISPCTRLX_ONESHOT : 0);

	HVS_WRITE(SCALER_DISPCTRLX(chan), dispctrl);

	dispbkgndx = HVS_READ(SCALER_DISPBKGNDX(chan));
	dispbkgndx &= ~SCALER_DISPBKGND_GAMMA;
	dispbkgndx &= ~SCALER_DISPBKGND_INTERLACE;

	HVS_WRITE(SCALER_DISPBKGNDX(chan), dispbkgndx |
		  SCALER_DISPBKGND_AUTOHS |
		  ((!vc4->hvs->hvs5) ? SCALER_DISPBKGND_GAMMA : 0) |
		  (पूर्णांकerlace ? SCALER_DISPBKGND_INTERLACE : 0));

	/* Reload the LUT, since the SRAMs would have been disabled अगर
	 * all CRTCs had SCALER_DISPBKGND_GAMMA unset at once.
	 */
	vc4_hvs_lut_load(crtc);

	वापस 0;
पूर्ण

व्योम vc4_hvs_stop_channel(काष्ठा drm_device *dev, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	अगर (HVS_READ(SCALER_DISPCTRLX(chan)) & SCALER_DISPCTRLX_ENABLE)
		वापस;

	HVS_WRITE(SCALER_DISPCTRLX(chan),
		  HVS_READ(SCALER_DISPCTRLX(chan)) | SCALER_DISPCTRLX_RESET);
	HVS_WRITE(SCALER_DISPCTRLX(chan),
		  HVS_READ(SCALER_DISPCTRLX(chan)) & ~SCALER_DISPCTRLX_ENABLE);

	/* Once we leave, the scaler should be disabled and its fअगरo empty. */
	WARN_ON_ONCE(HVS_READ(SCALER_DISPCTRLX(chan)) & SCALER_DISPCTRLX_RESET);

	WARN_ON_ONCE(VC4_GET_FIELD(HVS_READ(SCALER_DISPSTATX(chan)),
				   SCALER_DISPSTATX_MODE) !=
		     SCALER_DISPSTATX_MODE_DISABLED);

	WARN_ON_ONCE((HVS_READ(SCALER_DISPSTATX(chan)) &
		      (SCALER_DISPSTATX_FULL | SCALER_DISPSTATX_EMPTY)) !=
		     SCALER_DISPSTATX_EMPTY);
पूर्ण

पूर्णांक vc4_hvs_atomic_check(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc_state);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_plane *plane;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा drm_plane_state *plane_state;
	u32 dlist_count = 0;
	पूर्णांक ret;

	/* The pixelvalve can only feed one encoder (and encoders are
	 * 1:1 with connectors.)
	 */
	अगर (hweight32(crtc_state->connector_mask) > 1)
		वापस -EINVAL;

	drm_atomic_crtc_state_क्रम_each_plane_state(plane, plane_state, crtc_state)
		dlist_count += vc4_plane_dlist_size(plane_state);

	dlist_count++; /* Account क्रम SCALER_CTL0_END. */

	spin_lock_irqsave(&vc4->hvs->mm_lock, flags);
	ret = drm_mm_insert_node(&vc4->hvs->dlist_mm, &vc4_state->mm,
				 dlist_count);
	spin_unlock_irqrestore(&vc4->hvs->mm_lock, flags);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम vc4_hvs_update_dlist(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);

	अगर (crtc->state->event) अणु
		अचिन्हित दीर्घ flags;

		crtc->state->event->pipe = drm_crtc_index(crtc);

		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&dev->event_lock, flags);

		अगर (!vc4_state->feed_txp || vc4_state->txp_armed) अणु
			vc4_crtc->event = crtc->state->event;
			crtc->state->event = शून्य;
		पूर्ण

		HVS_WRITE(SCALER_DISPLISTX(vc4_state->asचिन्हित_channel),
			  vc4_state->mm.start);

		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण अन्यथा अणु
		HVS_WRITE(SCALER_DISPLISTX(vc4_state->asचिन्हित_channel),
			  vc4_state->mm.start);
	पूर्ण
पूर्ण

व्योम vc4_hvs_atomic_enable(काष्ठा drm_crtc *crtc,
			   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_crtc_state *new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(new_crtc_state);
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	bool oneshot = vc4_state->feed_txp;

	vc4_hvs_update_dlist(crtc);
	vc4_hvs_init_channel(vc4, crtc, mode, oneshot);
पूर्ण

व्योम vc4_hvs_atomic_disable(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state, crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(old_state);
	अचिन्हित पूर्णांक chan = vc4_state->asचिन्हित_channel;

	vc4_hvs_stop_channel(dev, chan);
पूर्ण

व्योम vc4_hvs_atomic_flush(काष्ठा drm_crtc *crtc,
			  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	काष्ठा drm_plane *plane;
	काष्ठा vc4_plane_state *vc4_plane_state;
	bool debug_dump_regs = false;
	bool enable_bg_fill = false;
	u32 __iomem *dlist_start = vc4->hvs->dlist + vc4_state->mm.start;
	u32 __iomem *dlist_next = dlist_start;

	अगर (debug_dump_regs) अणु
		DRM_INFO("CRTC %d HVS before:\n", drm_crtc_index(crtc));
		vc4_hvs_dump_state(dev);
	पूर्ण

	/* Copy all the active planes' dlist contents to the hardware dlist. */
	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		/* Is this the first active plane? */
		अगर (dlist_next == dlist_start) अणु
			/* We need to enable background fill when a plane
			 * could be alpha blending from the background, i.e.
			 * where no other plane is underneath. It suffices to
			 * consider the first active plane here since we set
			 * needs_bg_fill such that either the first plane
			 * alपढ़ोy needs it or all planes on top blend from
			 * the first or a lower plane.
			 */
			vc4_plane_state = to_vc4_plane_state(plane->state);
			enable_bg_fill = vc4_plane_state->needs_bg_fill;
		पूर्ण

		dlist_next += vc4_plane_ग_लिखो_dlist(plane, dlist_next);
	पूर्ण

	ग_लिखोl(SCALER_CTL0_END, dlist_next);
	dlist_next++;

	WARN_ON_ONCE(dlist_next - dlist_start != vc4_state->mm.size);

	अगर (enable_bg_fill)
		/* This sets a black background color fill, as is the हाल
		 * with other DRM drivers.
		 */
		HVS_WRITE(SCALER_DISPBKGNDX(vc4_state->asचिन्हित_channel),
			  HVS_READ(SCALER_DISPBKGNDX(vc4_state->asचिन्हित_channel)) |
			  SCALER_DISPBKGND_FILL);

	/* Only update DISPLIST अगर the CRTC was alपढ़ोy running and is not
	 * being disabled.
	 * vc4_crtc_enable() takes care of updating the dlist just after
	 * re-enabling VBLANK पूर्णांकerrupts and beक्रमe enabling the engine.
	 * If the CRTC is being disabled, there's no poपूर्णांक in updating this
	 * inक्रमmation.
	 */
	अगर (crtc->state->active && old_state->active)
		vc4_hvs_update_dlist(crtc);

	अगर (crtc->state->color_mgmt_changed) अणु
		u32 dispbkgndx = HVS_READ(SCALER_DISPBKGNDX(vc4_state->asचिन्हित_channel));

		अगर (crtc->state->gamma_lut) अणु
			vc4_hvs_update_gamma_lut(crtc);
			dispbkgndx |= SCALER_DISPBKGND_GAMMA;
		पूर्ण अन्यथा अणु
			/* Unsetting DISPBKGND_GAMMA skips the gamma lut step
			 * in hardware, which is the same as a linear lut that
			 * DRM expects us to use in असलence of a user lut.
			 */
			dispbkgndx &= ~SCALER_DISPBKGND_GAMMA;
		पूर्ण
		HVS_WRITE(SCALER_DISPBKGNDX(vc4_state->asचिन्हित_channel), dispbkgndx);
	पूर्ण

	अगर (debug_dump_regs) अणु
		DRM_INFO("CRTC %d HVS after:\n", drm_crtc_index(crtc));
		vc4_hvs_dump_state(dev);
	पूर्ण
पूर्ण

व्योम vc4_hvs_mask_underrun(काष्ठा drm_device *dev, पूर्णांक channel)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	u32 dispctrl = HVS_READ(SCALER_DISPCTRL);

	dispctrl &= ~SCALER_DISPCTRL_DSPEISLUR(channel);

	HVS_WRITE(SCALER_DISPCTRL, dispctrl);
पूर्ण

व्योम vc4_hvs_unmask_underrun(काष्ठा drm_device *dev, पूर्णांक channel)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	u32 dispctrl = HVS_READ(SCALER_DISPCTRL);

	dispctrl |= SCALER_DISPCTRL_DSPEISLUR(channel);

	HVS_WRITE(SCALER_DISPSTAT,
		  SCALER_DISPSTAT_EUFLOW(channel));
	HVS_WRITE(SCALER_DISPCTRL, dispctrl);
पूर्ण

अटल व्योम vc4_hvs_report_underrun(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	atomic_inc(&vc4->underrun);
	DRM_DEV_ERROR(dev->dev, "HVS underrun\n");
पूर्ण

अटल irqवापस_t vc4_hvs_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा drm_device *dev = data;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	irqवापस_t irqret = IRQ_NONE;
	पूर्णांक channel;
	u32 control;
	u32 status;

	status = HVS_READ(SCALER_DISPSTAT);
	control = HVS_READ(SCALER_DISPCTRL);

	क्रम (channel = 0; channel < SCALER_CHANNELS_COUNT; channel++) अणु
		/* Interrupt masking is not always honored, so check it here. */
		अगर (status & SCALER_DISPSTAT_EUFLOW(channel) &&
		    control & SCALER_DISPCTRL_DSPEISLUR(channel)) अणु
			vc4_hvs_mask_underrun(dev, channel);
			vc4_hvs_report_underrun(dev);

			irqret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* Clear every per-channel पूर्णांकerrupt flag. */
	HVS_WRITE(SCALER_DISPSTAT, SCALER_DISPSTAT_IRQMASK(0) |
				   SCALER_DISPSTAT_IRQMASK(1) |
				   SCALER_DISPSTAT_IRQMASK(2));

	वापस irqret;
पूर्ण

अटल पूर्णांक vc4_hvs_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_hvs *hvs = शून्य;
	पूर्णांक ret;
	u32 dispctrl;

	hvs = devm_kzalloc(&pdev->dev, माप(*hvs), GFP_KERNEL);
	अगर (!hvs)
		वापस -ENOMEM;

	hvs->pdev = pdev;

	अगर (of_device_is_compatible(pdev->dev.of_node, "brcm,bcm2711-hvs"))
		hvs->hvs5 = true;

	hvs->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(hvs->regs))
		वापस PTR_ERR(hvs->regs);

	hvs->regset.base = hvs->regs;
	hvs->regset.regs = hvs_regs;
	hvs->regset.nregs = ARRAY_SIZE(hvs_regs);

	अगर (hvs->hvs5) अणु
		hvs->core_clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(hvs->core_clk)) अणु
			dev_err(&pdev->dev, "Couldn't get core clock\n");
			वापस PTR_ERR(hvs->core_clk);
		पूर्ण

		ret = clk_prepare_enable(hvs->core_clk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Couldn't enable the core clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!hvs->hvs5)
		hvs->dlist = hvs->regs + SCALER_DLIST_START;
	अन्यथा
		hvs->dlist = hvs->regs + SCALER5_DLIST_START;

	spin_lock_init(&hvs->mm_lock);

	/* Set up the HVS display list memory manager.  We never
	 * overग_लिखो the setup from the bootloader (just 128b out of
	 * our 16K), since we करोn't want to scramble the screen when
	 * transitioning from the firmware's boot setup to runसमय.
	 */
	drm_mm_init(&hvs->dlist_mm,
		    HVS_BOOTLOADER_DLIST_END,
		    (SCALER_DLIST_SIZE >> 2) - HVS_BOOTLOADER_DLIST_END);

	/* Set up the HVS LBM memory manager.  We could have some more
	 * complicated data काष्ठाure that allowed reuse of LBM areas
	 * between planes when they करोn't overlap on the screen, but
	 * क्रम now we just allocate globally.
	 */
	अगर (!hvs->hvs5)
		/* 48k words of 2x12-bit pixels */
		drm_mm_init(&hvs->lbm_mm, 0, 48 * 1024);
	अन्यथा
		/* 60k words of 4x12-bit pixels */
		drm_mm_init(&hvs->lbm_mm, 0, 60 * 1024);

	/* Upload filter kernels.  We only have the one क्रम now, so we
	 * keep it around क्रम the lअगरeसमय of the driver.
	 */
	ret = vc4_hvs_upload_linear_kernel(hvs,
					   &hvs->mitchell_netravali_filter,
					   mitchell_netravali_1_3_1_3_kernel);
	अगर (ret)
		वापस ret;

	vc4->hvs = hvs;

	dispctrl = HVS_READ(SCALER_DISPCTRL);

	dispctrl |= SCALER_DISPCTRL_ENABLE;
	dispctrl |= SCALER_DISPCTRL_DISPEIRQ(0) |
		    SCALER_DISPCTRL_DISPEIRQ(1) |
		    SCALER_DISPCTRL_DISPEIRQ(2);

	/* Set DSP3 (PV1) to use HVS channel 2, which would otherwise
	 * be unused.
	 */
	dispctrl &= ~SCALER_DISPCTRL_DSP3_MUX_MASK;
	dispctrl &= ~(SCALER_DISPCTRL_DMAEIRQ |
		      SCALER_DISPCTRL_SLVWREIRQ |
		      SCALER_DISPCTRL_SLVRDEIRQ |
		      SCALER_DISPCTRL_DSPEIखातापूर्ण(0) |
		      SCALER_DISPCTRL_DSPEIखातापूर्ण(1) |
		      SCALER_DISPCTRL_DSPEIखातापूर्ण(2) |
		      SCALER_DISPCTRL_DSPEIEOLN(0) |
		      SCALER_DISPCTRL_DSPEIEOLN(1) |
		      SCALER_DISPCTRL_DSPEIEOLN(2) |
		      SCALER_DISPCTRL_DSPEISLUR(0) |
		      SCALER_DISPCTRL_DSPEISLUR(1) |
		      SCALER_DISPCTRL_DSPEISLUR(2) |
		      SCALER_DISPCTRL_SCLEIRQ);
	dispctrl |= VC4_SET_FIELD(2, SCALER_DISPCTRL_DSP3_MUX);

	HVS_WRITE(SCALER_DISPCTRL, dispctrl);

	ret = devm_request_irq(dev, platक्रमm_get_irq(pdev, 0),
			       vc4_hvs_irq_handler, 0, "vc4 hvs", drm);
	अगर (ret)
		वापस ret;

	vc4_debugfs_add_regset32(drm, "hvs_regs", &hvs->regset);
	vc4_debugfs_add_file(drm, "hvs_underrun", vc4_hvs_debugfs_underrun,
			     शून्य);

	वापस 0;
पूर्ण

अटल व्योम vc4_hvs_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_hvs *hvs = vc4->hvs;

	अगर (drm_mm_node_allocated(&vc4->hvs->mitchell_netravali_filter))
		drm_mm_हटाओ_node(&vc4->hvs->mitchell_netravali_filter);

	drm_mm_takeकरोwn(&vc4->hvs->dlist_mm);
	drm_mm_takeकरोwn(&vc4->hvs->lbm_mm);

	clk_disable_unprepare(hvs->core_clk);

	vc4->hvs = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_hvs_ops = अणु
	.bind   = vc4_hvs_bind,
	.unbind = vc4_hvs_unbind,
पूर्ण;

अटल पूर्णांक vc4_hvs_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_hvs_ops);
पूर्ण

अटल पूर्णांक vc4_hvs_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_hvs_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vc4_hvs_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2711-hvs" पूर्ण,
	अणु .compatible = "brcm,bcm2835-hvs" पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा platक्रमm_driver vc4_hvs_driver = अणु
	.probe = vc4_hvs_dev_probe,
	.हटाओ = vc4_hvs_dev_हटाओ,
	.driver = अणु
		.name = "vc4_hvs",
		.of_match_table = vc4_hvs_dt_match,
	पूर्ण,
पूर्ण;
