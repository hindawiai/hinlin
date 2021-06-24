<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Broadcom
 */

/**
 * DOC: VC4 CRTC module
 *
 * In VC4, the Pixel Valve is what most बंदly corresponds to the
 * DRM's concept of a CRTC.  The PV generates video timings from the
 * encoder's घड़ी plus its configuration.  It pulls scaled pixels from
 * the HVS at that timing, and feeds it to the encoder.
 *
 * However, the DRM CRTC also collects the configuration of all the
 * DRM planes attached to it.  As a result, the CRTC is also
 * responsible क्रम writing the display list क्रम the HVS channel that
 * the CRTC will use.
 *
 * The 2835 has 3 dअगरferent pixel valves.  pv0 in the audio घातer
 * करोमुख्य feeds DSI0 or DPI, जबतक pv1 feeds DS1 or SMI.  pv2 in the
 * image करोमुख्य can feed either HDMI or the SDTV controller.  The
 * pixel valve chooses from the CPRMAN घड़ीs (HSM क्रम HDMI, VEC क्रम
 * SDTV, etc.) according to which output type is chosen in the mux.
 *
 * For घातer management, the pixel valve's रेजिस्टरs are all घड़ीed
 * by the AXI घड़ी, जबतक the timings and FIFOs make use of the
 * output-specअगरic घड़ी.  Since the encoders also directly consume
 * the CPRMAN घड़ीs, and know what timings they need, they are the
 * ones that set the घड़ी.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/of_device.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा HVS_FIFO_LATENCY_PIX	6

#घोषणा CRTC_WRITE(offset, val) ग_लिखोl(val, vc4_crtc->regs + (offset))
#घोषणा CRTC_READ(offset) पढ़ोl(vc4_crtc->regs + (offset))

अटल स्थिर काष्ठा debugfs_reg32 crtc_regs[] = अणु
	VC4_REG32(PV_CONTROL),
	VC4_REG32(PV_V_CONTROL),
	VC4_REG32(PV_VSYNCD_EVEN),
	VC4_REG32(PV_HORZA),
	VC4_REG32(PV_HORZB),
	VC4_REG32(PV_VERTA),
	VC4_REG32(PV_VERTB),
	VC4_REG32(PV_VERTA_EVEN),
	VC4_REG32(PV_VERTB_EVEN),
	VC4_REG32(PV_INTEN),
	VC4_REG32(PV_INTSTAT),
	VC4_REG32(PV_STAT),
	VC4_REG32(PV_HACT_ACT),
पूर्ण;

अटल अचिन्हित पूर्णांक
vc4_crtc_get_cob_allocation(काष्ठा vc4_dev *vc4, अचिन्हित पूर्णांक channel)
अणु
	u32 dispbase = HVS_READ(SCALER_DISPBASEX(channel));
	/* Top/base are supposed to be 4-pixel aligned, but the
	 * Raspberry Pi firmware fills the low bits (which are
	 * presumably ignored).
	 */
	u32 top = VC4_GET_FIELD(dispbase, SCALER_DISPBASEX_TOP) & ~3;
	u32 base = VC4_GET_FIELD(dispbase, SCALER_DISPBASEX_BASE) & ~3;

	वापस top - base + 4;
पूर्ण

अटल bool vc4_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
					  bool in_vblank_irq,
					  पूर्णांक *vpos, पूर्णांक *hpos,
					  kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
					  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा vc4_crtc_state *vc4_crtc_state = to_vc4_crtc_state(crtc->state);
	अचिन्हित पूर्णांक cob_size;
	u32 val;
	पूर्णांक fअगरo_lines;
	पूर्णांक vblank_lines;
	bool ret = false;

	/* preempt_disable_rt() should go right here in PREEMPT_RT patchset. */

	/* Get optional प्रणाली बारtamp beक्रमe query. */
	अगर (sसमय)
		*sसमय = kसमय_get();

	/*
	 * Read vertical scanline which is currently composed क्रम our
	 * pixelvalve by the HVS, and also the scaler status.
	 */
	val = HVS_READ(SCALER_DISPSTATX(vc4_crtc_state->asचिन्हित_channel));

	/* Get optional प्रणाली बारtamp after query. */
	अगर (eसमय)
		*eसमय = kसमय_get();

	/* preempt_enable_rt() should go right here in PREEMPT_RT patchset. */

	/* Vertical position of hvs composed scanline. */
	*vpos = VC4_GET_FIELD(val, SCALER_DISPSTATX_LINE);
	*hpos = 0;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		*vpos /= 2;

		/* Use hpos to correct क्रम field offset in पूर्णांकerlaced mode. */
		अगर (VC4_GET_FIELD(val, SCALER_DISPSTATX_FRAME_COUNT) % 2)
			*hpos += mode->crtc_htotal / 2;
	पूर्ण

	cob_size = vc4_crtc_get_cob_allocation(vc4, vc4_crtc_state->asचिन्हित_channel);
	/* This is the offset we need क्रम translating hvs -> pv scanout pos. */
	fअगरo_lines = cob_size / mode->crtc_hdisplay;

	अगर (fअगरo_lines > 0)
		ret = true;

	/* HVS more than fअगरo_lines पूर्णांकo frame क्रम compositing? */
	अगर (*vpos > fअगरo_lines) अणु
		/*
		 * We are in active scanout and can get some meaningful results
		 * from HVS. The actual PV scanout can not trail behind more
		 * than fअगरo_lines as that is the fअगरo's capacity. Assume that
		 * in active scanout the HVS and PV work in lockstep wrt. HVS
		 * refilling the fअगरo and PV consuming from the fअगरo, ie.
		 * whenever the PV consumes and मुक्तs up a scanline in the
		 * fअगरo, the HVS will immediately refill it, thereक्रमe
		 * incrementing vpos. Thereक्रमe we choose HVS पढ़ो position -
		 * fअगरo size in scanlines as a estimate of the real scanout
		 * position of the PV.
		 */
		*vpos -= fअगरo_lines + 1;

		वापस ret;
	पूर्ण

	/*
	 * Less: This happens when we are in vblank and the HVS, after getting
	 * the VSTART restart संकेत from the PV, just started refilling its
	 * fअगरo with new lines from the top-most lines of the new framebuffers.
	 * The PV करोes not scan out in vblank, so करोes not हटाओ lines from
	 * the fअगरo, so the fअगरo will be full quickly and the HVS has to छोड़ो.
	 * We can't get meaningful पढ़ोings wrt. scanline position of the PV
	 * and need to make things up in a approximative but consistent way.
	 */
	vblank_lines = mode->vtotal - mode->vdisplay;

	अगर (in_vblank_irq) अणु
		/*
		 * Assume the irq handler got called बंद to first
		 * line of vblank, so PV has about a full vblank
		 * scanlines to go, and as a base बारtamp use the
		 * one taken at entry पूर्णांकo vblank irq handler, so it
		 * is not affected by अक्रमom delays due to lock
		 * contention on event_lock or vblank_समय lock in
		 * the core.
		 */
		*vpos = -vblank_lines;

		अगर (sसमय)
			*sसमय = vc4_crtc->t_vblank;
		अगर (eसमय)
			*eसमय = vc4_crtc->t_vblank;

		/*
		 * If the HVS fअगरo is not yet full then we know क्रम certain
		 * we are at the very beginning of vblank, as the hvs just
		 * started refilling, and the sसमय and eसमय बारtamps
		 * truly correspond to start of vblank.
		 *
		 * Unक्रमtunately there's no way to report this to upper levels
		 * and make it more useful.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * No clue where we are inside vblank. Return a vpos of zero,
		 * which will cause calling code to just वापस the eसमय
		 * बारtamp uncorrected. At least this is no worse than the
		 * standard fallback.
		 */
		*vpos = 0;
	पूर्ण

	वापस ret;
पूर्ण

व्योम vc4_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	drm_crtc_cleanup(crtc);
पूर्ण

अटल u32 vc4_get_fअगरo_full_level(काष्ठा vc4_crtc *vc4_crtc, u32 क्रमmat)
अणु
	स्थिर काष्ठा vc4_crtc_data *crtc_data = vc4_crtc_to_vc4_crtc_data(vc4_crtc);
	स्थिर काष्ठा vc4_pv_data *pv_data = vc4_crtc_to_vc4_pv_data(vc4_crtc);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(vc4_crtc->base.dev);
	u32 fअगरo_len_bytes = pv_data->fअगरo_depth;

	/*
	 * Pixels are pulled from the HVS अगर the number of bytes is
	 * lower than the FIFO full level.
	 *
	 * The latency of the pixel fetch mechanism is 6 pixels, so we
	 * need to convert those 6 pixels in bytes, depending on the
	 * क्रमmat, and then subtract that from the length of the FIFO
	 * to make sure we never end up in a situation where the FIFO
	 * is full.
	 */
	चयन (क्रमmat) अणु
	हाल PV_CONTROL_FORMAT_DSIV_16:
	हाल PV_CONTROL_FORMAT_DSIC_16:
		वापस fअगरo_len_bytes - 2 * HVS_FIFO_LATENCY_PIX;
	हाल PV_CONTROL_FORMAT_DSIV_18:
		वापस fअगरo_len_bytes - 14;
	हाल PV_CONTROL_FORMAT_24:
	हाल PV_CONTROL_FORMAT_DSIV_24:
	शेष:
		/*
		 * For some reason, the pixelvalve4 करोesn't work with
		 * the usual क्रमmula and will only work with 32.
		 */
		अगर (crtc_data->hvs_output == 5)
			वापस 32;

		/*
		 * It looks like in some situations, we will overflow
		 * the PixelValve FIFO (with the bit 10 of PV stat being
		 * set) and stall the HVS / PV, eventually resulting in
		 * a page flip समयout.
		 *
		 * Displaying the video overlay during a playback with
		 * Kodi on an RPi3 seems to be a great solution with a
		 * failure rate around 50%.
		 *
		 * Removing 1 from the FIFO full level however
		 * seems to completely हटाओ that issue.
		 */
		अगर (!vc4->hvs->hvs5)
			वापस fअगरo_len_bytes - 3 * HVS_FIFO_LATENCY_PIX - 1;

		वापस fअगरo_len_bytes - 3 * HVS_FIFO_LATENCY_PIX;
	पूर्ण
पूर्ण

अटल u32 vc4_crtc_get_fअगरo_full_level_bits(काष्ठा vc4_crtc *vc4_crtc,
					     u32 क्रमmat)
अणु
	u32 level = vc4_get_fअगरo_full_level(vc4_crtc, क्रमmat);
	u32 ret = 0;

	ret |= VC4_SET_FIELD((level >> 6),
			     PV5_CONTROL_FIFO_LEVEL_HIGH);

	वापस ret | VC4_SET_FIELD(level & 0x3f,
				   PV_CONTROL_FIFO_LEVEL);
पूर्ण

/*
 * Returns the encoder attached to the CRTC.
 *
 * VC4 can only scan out to one encoder at a समय, जबतक the DRM core
 * allows drivers to push pixels to more than one encoder from the
 * same CRTC.
 */
अटल काष्ठा drm_encoder *vc4_get_crtc_encoder(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(crtc->dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->state->crtc == crtc) अणु
			drm_connector_list_iter_end(&conn_iter);
			वापस connector->encoder;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस शून्य;
पूर्ण

अटल व्योम vc4_crtc_pixelvalve_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);

	/* The PV needs to be disabled beक्रमe it can be flushed */
	CRTC_WRITE(PV_CONTROL, CRTC_READ(PV_CONTROL) & ~PV_CONTROL_EN);
	CRTC_WRITE(PV_CONTROL, CRTC_READ(PV_CONTROL) | PV_CONTROL_FIFO_CLR);
पूर्ण

अटल व्योम vc4_crtc_config_pv(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_encoder *encoder = vc4_get_crtc_encoder(crtc);
	काष्ठा vc4_encoder *vc4_encoder = to_vc4_encoder(encoder);
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	स्थिर काष्ठा vc4_pv_data *pv_data = vc4_crtc_to_vc4_pv_data(vc4_crtc);
	काष्ठा drm_crtc_state *state = crtc->state;
	काष्ठा drm_display_mode *mode = &state->adjusted_mode;
	bool पूर्णांकerlace = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 pixel_rep = (mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1;
	bool is_dsi = (vc4_encoder->type == VC4_ENCODER_TYPE_DSI0 ||
		       vc4_encoder->type == VC4_ENCODER_TYPE_DSI1);
	u32 क्रमmat = is_dsi ? PV_CONTROL_FORMAT_DSIV_24 : PV_CONTROL_FORMAT_24;
	u8 ppc = pv_data->pixels_per_घड़ी;
	bool debug_dump_regs = false;

	अगर (debug_dump_regs) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(&vc4_crtc->pdev->dev);
		dev_info(&vc4_crtc->pdev->dev, "CRTC %d regs before:\n",
			 drm_crtc_index(crtc));
		drm_prपूर्णांक_regset32(&p, &vc4_crtc->regset);
	पूर्ण

	vc4_crtc_pixelvalve_reset(crtc);

	CRTC_WRITE(PV_HORZA,
		   VC4_SET_FIELD((mode->htotal - mode->hsync_end) * pixel_rep / ppc,
				 PV_HORZA_HBP) |
		   VC4_SET_FIELD((mode->hsync_end - mode->hsync_start) * pixel_rep / ppc,
				 PV_HORZA_HSYNC));

	CRTC_WRITE(PV_HORZB,
		   VC4_SET_FIELD((mode->hsync_start - mode->hdisplay) * pixel_rep / ppc,
				 PV_HORZB_HFP) |
		   VC4_SET_FIELD(mode->hdisplay * pixel_rep / ppc,
				 PV_HORZB_HACTIVE));

	CRTC_WRITE(PV_VERTA,
		   VC4_SET_FIELD(mode->crtc_vtotal - mode->crtc_vsync_end,
				 PV_VERTA_VBP) |
		   VC4_SET_FIELD(mode->crtc_vsync_end - mode->crtc_vsync_start,
				 PV_VERTA_VSYNC));
	CRTC_WRITE(PV_VERTB,
		   VC4_SET_FIELD(mode->crtc_vsync_start - mode->crtc_vdisplay,
				 PV_VERTB_VFP) |
		   VC4_SET_FIELD(mode->crtc_vdisplay, PV_VERTB_VACTIVE));

	अगर (पूर्णांकerlace) अणु
		CRTC_WRITE(PV_VERTA_EVEN,
			   VC4_SET_FIELD(mode->crtc_vtotal -
					 mode->crtc_vsync_end - 1,
					 PV_VERTA_VBP) |
			   VC4_SET_FIELD(mode->crtc_vsync_end -
					 mode->crtc_vsync_start,
					 PV_VERTA_VSYNC));
		CRTC_WRITE(PV_VERTB_EVEN,
			   VC4_SET_FIELD(mode->crtc_vsync_start -
					 mode->crtc_vdisplay,
					 PV_VERTB_VFP) |
			   VC4_SET_FIELD(mode->crtc_vdisplay, PV_VERTB_VACTIVE));

		/* We set up first field even mode क्रम HDMI.  VEC's
		 * NTSC mode would want first field odd instead, once
		 * we support it (to करो so, set ODD_FIRST and put the
		 * delay in VSYNCD_EVEN instead).
		 */
		CRTC_WRITE(PV_V_CONTROL,
			   PV_VCONTROL_CONTINUOUS |
			   (is_dsi ? PV_VCONTROL_DSI : 0) |
			   PV_VCONTROL_INTERLACE |
			   VC4_SET_FIELD(mode->htotal * pixel_rep / 2,
					 PV_VCONTROL_ODD_DELAY));
		CRTC_WRITE(PV_VSYNCD_EVEN, 0);
	पूर्ण अन्यथा अणु
		CRTC_WRITE(PV_V_CONTROL,
			   PV_VCONTROL_CONTINUOUS |
			   (is_dsi ? PV_VCONTROL_DSI : 0));
	पूर्ण

	अगर (is_dsi)
		CRTC_WRITE(PV_HACT_ACT, mode->hdisplay * pixel_rep);

	अगर (vc4->hvs->hvs5)
		CRTC_WRITE(PV_MUX_CFG,
			   VC4_SET_FIELD(PV_MUX_CFG_RGB_PIXEL_MUX_MODE_NO_SWAP,
					 PV_MUX_CFG_RGB_PIXEL_MUX_MODE));

	CRTC_WRITE(PV_CONTROL, PV_CONTROL_FIFO_CLR |
		   vc4_crtc_get_fअगरo_full_level_bits(vc4_crtc, क्रमmat) |
		   VC4_SET_FIELD(क्रमmat, PV_CONTROL_FORMAT) |
		   VC4_SET_FIELD(pixel_rep - 1, PV_CONTROL_PIXEL_REP) |
		   PV_CONTROL_CLR_AT_START |
		   PV_CONTROL_TRIGGER_UNDERFLOW |
		   PV_CONTROL_WAIT_HSTART |
		   VC4_SET_FIELD(vc4_encoder->घड़ी_select,
				 PV_CONTROL_CLK_SELECT));

	अगर (debug_dump_regs) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(&vc4_crtc->pdev->dev);
		dev_info(&vc4_crtc->pdev->dev, "CRTC %d regs after:\n",
			 drm_crtc_index(crtc));
		drm_prपूर्णांक_regset32(&p, &vc4_crtc->regset);
	पूर्ण
पूर्ण

अटल व्योम require_hvs_enabled(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	WARN_ON_ONCE((HVS_READ(SCALER_DISPCTRL) & SCALER_DISPCTRL_ENABLE) !=
		     SCALER_DISPCTRL_ENABLE);
पूर्ण

अटल पूर्णांक vc4_crtc_disable(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_atomic_state *state,
			    अचिन्हित पूर्णांक channel)
अणु
	काष्ठा drm_encoder *encoder = vc4_get_crtc_encoder(crtc);
	काष्ठा vc4_encoder *vc4_encoder = to_vc4_encoder(encoder);
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	पूर्णांक ret;

	CRTC_WRITE(PV_V_CONTROL,
		   CRTC_READ(PV_V_CONTROL) & ~PV_VCONTROL_VIDEN);
	ret = रुको_क्रम(!(CRTC_READ(PV_V_CONTROL) & PV_VCONTROL_VIDEN), 1);
	WARN_ONCE(ret, "Timeout waiting for !PV_VCONTROL_VIDEN\n");

	/*
	 * This delay is needed to aव्योम to get a pixel stuck in an
	 * unflushable FIFO between the pixelvalve and the HDMI
	 * controllers on the BCM2711.
	 *
	 * Timing is fairly sensitive here, so mdelay is the safest
	 * approach.
	 *
	 * If it was to be reworked, the stuck pixel happens on a
	 * BCM2711 when changing mode with a good probability, so a
	 * script that changes mode on a regular basis should trigger
	 * the bug after less than 10 attempts. It manअगरests itself with
	 * every pixels being shअगरted by one to the right, and thus the
	 * last pixel of a line actually being displayed as the first
	 * pixel on the next line.
	 */
	mdelay(20);

	अगर (vc4_encoder && vc4_encoder->post_crtc_disable)
		vc4_encoder->post_crtc_disable(encoder, state);

	vc4_crtc_pixelvalve_reset(crtc);
	vc4_hvs_stop_channel(dev, channel);

	अगर (vc4_encoder && vc4_encoder->post_crtc_घातerकरोwn)
		vc4_encoder->post_crtc_घातerकरोwn(encoder, state);

	वापस 0;
पूर्ण

पूर्णांक vc4_crtc_disable_at_boot(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	पूर्णांक channel;

	अगर (!(of_device_is_compatible(vc4_crtc->pdev->dev.of_node,
				      "brcm,bcm2711-pixelvalve2") ||
	      of_device_is_compatible(vc4_crtc->pdev->dev.of_node,
				      "brcm,bcm2711-pixelvalve4")))
		वापस 0;

	अगर (!(CRTC_READ(PV_CONTROL) & PV_CONTROL_EN))
		वापस 0;

	अगर (!(CRTC_READ(PV_V_CONTROL) & PV_VCONTROL_VIDEN))
		वापस 0;

	channel = vc4_hvs_get_fअगरo_from_output(drm, vc4_crtc->data->hvs_output);
	अगर (channel < 0)
		वापस 0;

	वापस vc4_crtc_disable(crtc, शून्य, channel);
पूर्ण

अटल व्योम vc4_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा vc4_crtc_state *old_vc4_state = to_vc4_crtc_state(old_state);
	काष्ठा drm_device *dev = crtc->dev;

	require_hvs_enabled(dev);

	/* Disable vblank irq handling beक्रमe crtc is disabled. */
	drm_crtc_vblank_off(crtc);

	vc4_crtc_disable(crtc, state, old_vc4_state->asचिन्हित_channel);

	/*
	 * Make sure we issue a vblank event after disabling the CRTC अगर
	 * someone was रुकोing it.
	 */
	अगर (crtc->state->event) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम vc4_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	काष्ठा drm_encoder *encoder = vc4_get_crtc_encoder(crtc);
	काष्ठा vc4_encoder *vc4_encoder = to_vc4_encoder(encoder);

	require_hvs_enabled(dev);

	/* Enable vblank irq handling beक्रमe crtc is started otherwise
	 * drm_crtc_get_vblank() fails in vc4_crtc_update_dlist().
	 */
	drm_crtc_vblank_on(crtc);

	vc4_hvs_atomic_enable(crtc, state);

	अगर (vc4_encoder->pre_crtc_configure)
		vc4_encoder->pre_crtc_configure(encoder, state);

	vc4_crtc_config_pv(crtc);

	CRTC_WRITE(PV_CONTROL, CRTC_READ(PV_CONTROL) | PV_CONTROL_EN);

	अगर (vc4_encoder->pre_crtc_enable)
		vc4_encoder->pre_crtc_enable(encoder, state);

	/* When feeding the transposer block the pixelvalve is unneeded and
	 * should not be enabled.
	 */
	CRTC_WRITE(PV_V_CONTROL,
		   CRTC_READ(PV_V_CONTROL) | PV_VCONTROL_VIDEN);

	अगर (vc4_encoder->post_crtc_enable)
		vc4_encoder->post_crtc_enable(encoder, state);
पूर्ण

अटल क्रमागत drm_mode_status vc4_crtc_mode_valid(काष्ठा drm_crtc *crtc,
						स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* Do not allow द्विगुनscan modes from user space */
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN) अणु
		DRM_DEBUG_KMS("[CRTC:%d] Doublescan mode rejected.\n",
			      crtc->base.id);
		वापस MODE_NO_DBLESCAN;
	पूर्ण

	वापस MODE_OK;
पूर्ण

व्योम vc4_crtc_get_margins(काष्ठा drm_crtc_state *state,
			  अचिन्हित पूर्णांक *left, अचिन्हित पूर्णांक *right,
			  अचिन्हित पूर्णांक *top, अचिन्हित पूर्णांक *bottom)
अणु
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(state);
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	*left = vc4_state->margins.left;
	*right = vc4_state->margins.right;
	*top = vc4_state->margins.top;
	*bottom = vc4_state->margins.bottom;

	/* We have to पूर्णांकerate over all new connector states because
	 * vc4_crtc_get_margins() might be called beक्रमe
	 * vc4_crtc_atomic_check() which means margins info in vc4_crtc_state
	 * might be outdated.
	 */
	क्रम_each_new_connector_in_state(state->state, conn, conn_state, i) अणु
		अगर (conn_state->crtc != state->crtc)
			जारी;

		*left = conn_state->tv.margins.left;
		*right = conn_state->tv.margins.right;
		*top = conn_state->tv.margins.top;
		*bottom = conn_state->tv.margins.bottom;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc_state);
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *conn_state;
	पूर्णांक ret, i;

	ret = vc4_hvs_atomic_check(crtc, state);
	अगर (ret)
		वापस ret;

	क्रम_each_new_connector_in_state(state, conn, conn_state,
					i) अणु
		अगर (conn_state->crtc != crtc)
			जारी;

		vc4_state->margins.left = conn_state->tv.margins.left;
		vc4_state->margins.right = conn_state->tv.margins.right;
		vc4_state->margins.top = conn_state->tv.margins.top;
		vc4_state->margins.bottom = conn_state->tv.margins.bottom;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);

	CRTC_WRITE(PV_INTEN, PV_INT_VFP_START);

	वापस 0;
पूर्ण

अटल व्योम vc4_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);

	CRTC_WRITE(PV_INTEN, 0);
पूर्ण

अटल व्योम vc4_crtc_handle_page_flip(काष्ठा vc4_crtc *vc4_crtc)
अणु
	काष्ठा drm_crtc *crtc = &vc4_crtc->base;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc->state);
	u32 chan = vc4_state->asचिन्हित_channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (vc4_crtc->event &&
	    (vc4_state->mm.start == HVS_READ(SCALER_DISPLACTX(chan)) ||
	     vc4_state->feed_txp)) अणु
		drm_crtc_send_vblank_event(crtc, vc4_crtc->event);
		vc4_crtc->event = शून्य;
		drm_crtc_vblank_put(crtc);

		/* Wait क्रम the page flip to unmask the underrun to ensure that
		 * the display list was updated by the hardware. Beक्रमe that
		 * happens, the HVS will be using the previous display list with
		 * the CRTC and encoder alपढ़ोy reconfigured, leading to
		 * underruns. This can be seen when reconfiguring the CRTC.
		 */
		vc4_hvs_unmask_underrun(dev, chan);
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

व्योम vc4_crtc_handle_vblank(काष्ठा vc4_crtc *crtc)
अणु
	crtc->t_vblank = kसमय_get();
	drm_crtc_handle_vblank(&crtc->base);
	vc4_crtc_handle_page_flip(crtc);
पूर्ण

अटल irqवापस_t vc4_crtc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vc4_crtc *vc4_crtc = data;
	u32 stat = CRTC_READ(PV_INTSTAT);
	irqवापस_t ret = IRQ_NONE;

	अगर (stat & PV_INT_VFP_START) अणु
		CRTC_WRITE(PV_INTSTAT, PV_INT_VFP_START);
		vc4_crtc_handle_vblank(vc4_crtc);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा vc4_async_flip_state अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_framebuffer *old_fb;
	काष्ठा drm_pending_vblank_event *event;

	काष्ठा vc4_seqno_cb cb;
पूर्ण;

/* Called when the V3D execution क्रम the BO being flipped to is करोne, so that
 * we can actually update the plane's address to poपूर्णांक to it.
 */
अटल व्योम
vc4_async_page_flip_complete(काष्ठा vc4_seqno_cb *cb)
अणु
	काष्ठा vc4_async_flip_state *flip_state =
		container_of(cb, काष्ठा vc4_async_flip_state, cb);
	काष्ठा drm_crtc *crtc = flip_state->crtc;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_plane *plane = crtc->primary;

	vc4_plane_async_set_fb(plane, flip_state->fb);
	अगर (flip_state->event) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, flip_state->event);
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण

	drm_crtc_vblank_put(crtc);
	drm_framebuffer_put(flip_state->fb);

	/* Decrement the BO usecnt in order to keep the inc/dec calls balanced
	 * when the planes are updated through the async update path.
	 * FIXME: we should move to generic async-page-flip when it's
	 * available, so that we can get rid of this hand-made cleanup_fb()
	 * logic.
	 */
	अगर (flip_state->old_fb) अणु
		काष्ठा drm_gem_cma_object *cma_bo;
		काष्ठा vc4_bo *bo;

		cma_bo = drm_fb_cma_get_gem_obj(flip_state->old_fb, 0);
		bo = to_vc4_bo(&cma_bo->base);
		vc4_bo_dec_usecnt(bo);
		drm_framebuffer_put(flip_state->old_fb);
	पूर्ण

	kमुक्त(flip_state);
पूर्ण

/* Implements async (non-vblank-synced) page flips.
 *
 * The page flip ioctl needs to वापस immediately, so we grab the
 * modeset semaphore on the pipe, and queue the address update क्रम
 * when V3D is करोne with the BO being flipped to.
 */
अटल पूर्णांक vc4_async_page_flip(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_pending_vblank_event *event,
			       uपूर्णांक32_t flags)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_plane *plane = crtc->primary;
	पूर्णांक ret = 0;
	काष्ठा vc4_async_flip_state *flip_state;
	काष्ठा drm_gem_cma_object *cma_bo = drm_fb_cma_get_gem_obj(fb, 0);
	काष्ठा vc4_bo *bo = to_vc4_bo(&cma_bo->base);

	/* Increment the BO usecnt here, so that we never end up with an
	 * unbalanced number of vc4_bo_अणुdec,incपूर्ण_usecnt() calls when the
	 * plane is later updated through the non-async path.
	 * FIXME: we should move to generic async-page-flip when it's
	 * available, so that we can get rid of this hand-made prepare_fb()
	 * logic.
	 */
	ret = vc4_bo_inc_usecnt(bo);
	अगर (ret)
		वापस ret;

	flip_state = kzalloc(माप(*flip_state), GFP_KERNEL);
	अगर (!flip_state) अणु
		vc4_bo_dec_usecnt(bo);
		वापस -ENOMEM;
	पूर्ण

	drm_framebuffer_get(fb);
	flip_state->fb = fb;
	flip_state->crtc = crtc;
	flip_state->event = event;

	/* Save the current FB beक्रमe it's replaced by the new one in
	 * drm_atomic_set_fb_क्रम_plane(). We'll need the old FB in
	 * vc4_async_page_flip_complete() to decrement the BO usecnt and keep
	 * it consistent.
	 * FIXME: we should move to generic async-page-flip when it's
	 * available, so that we can get rid of this hand-made cleanup_fb()
	 * logic.
	 */
	flip_state->old_fb = plane->state->fb;
	अगर (flip_state->old_fb)
		drm_framebuffer_get(flip_state->old_fb);

	WARN_ON(drm_crtc_vblank_get(crtc) != 0);

	/* Immediately update the plane's legacy fb poपूर्णांकer, so that later
	 * modeset prep sees the state that will be present when the semaphore
	 * is released.
	 */
	drm_atomic_set_fb_क्रम_plane(plane->state, fb);

	vc4_queue_seqno_cb(dev, &flip_state->cb, bo->seqno,
			   vc4_async_page_flip_complete);

	/* Driver takes ownership of state on successful async commit. */
	वापस 0;
पूर्ण

पूर्णांक vc4_page_flip(काष्ठा drm_crtc *crtc,
		  काष्ठा drm_framebuffer *fb,
		  काष्ठा drm_pending_vblank_event *event,
		  uपूर्णांक32_t flags,
		  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	अगर (flags & DRM_MODE_PAGE_FLIP_ASYNC)
		वापस vc4_async_page_flip(crtc, fb, event, flags);
	अन्यथा
		वापस drm_atomic_helper_page_flip(crtc, fb, event, flags, ctx);
पूर्ण

काष्ठा drm_crtc_state *vc4_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc_state *vc4_state, *old_vc4_state;

	vc4_state = kzalloc(माप(*vc4_state), GFP_KERNEL);
	अगर (!vc4_state)
		वापस शून्य;

	old_vc4_state = to_vc4_crtc_state(crtc->state);
	vc4_state->feed_txp = old_vc4_state->feed_txp;
	vc4_state->margins = old_vc4_state->margins;
	vc4_state->asचिन्हित_channel = old_vc4_state->asचिन्हित_channel;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &vc4_state->base);
	वापस &vc4_state->base;
पूर्ण

व्योम vc4_crtc_destroy_state(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_crtc_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(crtc->dev);
	काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(state);

	अगर (drm_mm_node_allocated(&vc4_state->mm)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&vc4->hvs->mm_lock, flags);
		drm_mm_हटाओ_node(&vc4_state->mm);
		spin_unlock_irqrestore(&vc4->hvs->mm_lock, flags);

	पूर्ण

	drm_atomic_helper_crtc_destroy_state(crtc, state);
पूर्ण

व्योम vc4_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc_state *vc4_crtc_state;

	अगर (crtc->state)
		vc4_crtc_destroy_state(crtc, crtc->state);

	vc4_crtc_state = kzalloc(माप(*vc4_crtc_state), GFP_KERNEL);
	अगर (!vc4_crtc_state) अणु
		crtc->state = शून्य;
		वापस;
	पूर्ण

	vc4_crtc_state->asचिन्हित_channel = VC4_HVS_CHANNEL_DISABLED;
	__drm_atomic_helper_crtc_reset(crtc, &vc4_crtc_state->base);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vc4_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = vc4_crtc_destroy,
	.page_flip = vc4_page_flip,
	.set_property = शून्य,
	.cursor_set = शून्य, /* handled by drm_mode_cursor_universal */
	.cursor_move = शून्य, /* handled by drm_mode_cursor_universal */
	.reset = vc4_crtc_reset,
	.atomic_duplicate_state = vc4_crtc_duplicate_state,
	.atomic_destroy_state = vc4_crtc_destroy_state,
	.enable_vblank = vc4_enable_vblank,
	.disable_vblank = vc4_disable_vblank,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs vc4_crtc_helper_funcs = अणु
	.mode_valid = vc4_crtc_mode_valid,
	.atomic_check = vc4_crtc_atomic_check,
	.atomic_flush = vc4_hvs_atomic_flush,
	.atomic_enable = vc4_crtc_atomic_enable,
	.atomic_disable = vc4_crtc_atomic_disable,
	.get_scanout_position = vc4_crtc_get_scanout_position,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2835_pv0_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(0),
		.hvs_output = 0,
	पूर्ण,
	.debugfs_name = "crtc0_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[PV_CONTROL_CLK_SELECT_DSI] = VC4_ENCODER_TYPE_DSI0,
		[PV_CONTROL_CLK_SELECT_DPI_SMI_HDMI] = VC4_ENCODER_TYPE_DPI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2835_pv1_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(2),
		.hvs_output = 2,
	पूर्ण,
	.debugfs_name = "crtc1_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[PV_CONTROL_CLK_SELECT_DSI] = VC4_ENCODER_TYPE_DSI1,
		[PV_CONTROL_CLK_SELECT_DPI_SMI_HDMI] = VC4_ENCODER_TYPE_SMI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2835_pv2_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(1),
		.hvs_output = 1,
	पूर्ण,
	.debugfs_name = "crtc2_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[PV_CONTROL_CLK_SELECT_DPI_SMI_HDMI] = VC4_ENCODER_TYPE_HDMI0,
		[PV_CONTROL_CLK_SELECT_VEC] = VC4_ENCODER_TYPE_VEC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2711_pv0_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(0),
		.hvs_output = 0,
	पूर्ण,
	.debugfs_name = "crtc0_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[0] = VC4_ENCODER_TYPE_DSI0,
		[1] = VC4_ENCODER_TYPE_DPI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2711_pv1_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 3,
	पूर्ण,
	.debugfs_name = "crtc1_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[0] = VC4_ENCODER_TYPE_DSI1,
		[1] = VC4_ENCODER_TYPE_SMI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2711_pv2_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 4,
	पूर्ण,
	.debugfs_name = "crtc2_regs",
	.fअगरo_depth = 256,
	.pixels_per_घड़ी = 2,
	.encoder_types = अणु
		[0] = VC4_ENCODER_TYPE_HDMI0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2711_pv3_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(1),
		.hvs_output = 1,
	पूर्ण,
	.debugfs_name = "crtc3_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 1,
	.encoder_types = अणु
		[0] = VC4_ENCODER_TYPE_VEC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vc4_pv_data bcm2711_pv4_data = अणु
	.base = अणु
		.hvs_available_channels = BIT(0) | BIT(1) | BIT(2),
		.hvs_output = 5,
	पूर्ण,
	.debugfs_name = "crtc4_regs",
	.fअगरo_depth = 64,
	.pixels_per_घड़ी = 2,
	.encoder_types = अणु
		[0] = VC4_ENCODER_TYPE_HDMI1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vc4_crtc_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-pixelvalve0", .data = &bcm2835_pv0_data पूर्ण,
	अणु .compatible = "brcm,bcm2835-pixelvalve1", .data = &bcm2835_pv1_data पूर्ण,
	अणु .compatible = "brcm,bcm2835-pixelvalve2", .data = &bcm2835_pv2_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-pixelvalve0", .data = &bcm2711_pv0_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-pixelvalve1", .data = &bcm2711_pv1_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-pixelvalve2", .data = &bcm2711_pv2_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-pixelvalve3", .data = &bcm2711_pv3_data पूर्ण,
	अणु .compatible = "brcm,bcm2711-pixelvalve4", .data = &bcm2711_pv4_data पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम vc4_set_crtc_possible_masks(काष्ठा drm_device *drm,
					काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	स्थिर काष्ठा vc4_pv_data *pv_data = vc4_crtc_to_vc4_pv_data(vc4_crtc);
	स्थिर क्रमागत vc4_encoder_type *encoder_types = pv_data->encoder_types;
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder(encoder, drm) अणु
		काष्ठा vc4_encoder *vc4_encoder;
		पूर्णांक i;

		vc4_encoder = to_vc4_encoder(encoder);
		क्रम (i = 0; i < ARRAY_SIZE(pv_data->encoder_types); i++) अणु
			अगर (vc4_encoder->type == encoder_types[i]) अणु
				vc4_encoder->घड़ी_select = i;
				encoder->possible_crtcs |= drm_crtc_mask(crtc);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक vc4_crtc_init(काष्ठा drm_device *drm, काष्ठा vc4_crtc *vc4_crtc,
		  स्थिर काष्ठा drm_crtc_funcs *crtc_funcs,
		  स्थिर काष्ठा drm_crtc_helper_funcs *crtc_helper_funcs)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा drm_crtc *crtc = &vc4_crtc->base;
	काष्ठा drm_plane *primary_plane;
	अचिन्हित पूर्णांक i;

	/* For now, we create just the primary and the legacy cursor
	 * planes.  We should be able to stack more planes on easily,
	 * but to करो that we would need to compute the bandwidth
	 * requirement of the plane configuration, and reject ones
	 * that will take too much.
	 */
	primary_plane = vc4_plane_init(drm, DRM_PLANE_TYPE_PRIMARY);
	अगर (IS_ERR(primary_plane)) अणु
		dev_err(drm->dev, "failed to construct primary plane\n");
		वापस PTR_ERR(primary_plane);
	पूर्ण

	drm_crtc_init_with_planes(drm, crtc, primary_plane, शून्य,
				  crtc_funcs, शून्य);
	drm_crtc_helper_add(crtc, crtc_helper_funcs);

	अगर (!vc4->hvs->hvs5) अणु
		drm_mode_crtc_set_gamma_size(crtc, ARRAY_SIZE(vc4_crtc->lut_r));

		drm_crtc_enable_color_mgmt(crtc, 0, false, crtc->gamma_size);

		/* We support CTM, but only क्रम one CRTC at a समय. It's thereक्रमe
		 * implemented as निजी driver state in vc4_kms, not here.
		 */
		drm_crtc_enable_color_mgmt(crtc, 0, true, crtc->gamma_size);
	पूर्ण

	क्रम (i = 0; i < crtc->gamma_size; i++) अणु
		vc4_crtc->lut_r[i] = i;
		vc4_crtc->lut_g[i] = i;
		vc4_crtc->lut_b[i] = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_crtc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	स्थिर काष्ठा vc4_pv_data *pv_data;
	काष्ठा vc4_crtc *vc4_crtc;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *destroy_plane, *temp;
	पूर्णांक ret;

	vc4_crtc = devm_kzalloc(dev, माप(*vc4_crtc), GFP_KERNEL);
	अगर (!vc4_crtc)
		वापस -ENOMEM;
	crtc = &vc4_crtc->base;

	pv_data = of_device_get_match_data(dev);
	अगर (!pv_data)
		वापस -ENODEV;
	vc4_crtc->data = &pv_data->base;
	vc4_crtc->pdev = pdev;

	vc4_crtc->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(vc4_crtc->regs))
		वापस PTR_ERR(vc4_crtc->regs);

	vc4_crtc->regset.base = vc4_crtc->regs;
	vc4_crtc->regset.regs = crtc_regs;
	vc4_crtc->regset.nregs = ARRAY_SIZE(crtc_regs);

	ret = vc4_crtc_init(drm, vc4_crtc,
			    &vc4_crtc_funcs, &vc4_crtc_helper_funcs);
	अगर (ret)
		वापस ret;
	vc4_set_crtc_possible_masks(drm, crtc);

	CRTC_WRITE(PV_INTEN, 0);
	CRTC_WRITE(PV_INTSTAT, PV_INT_VFP_START);
	ret = devm_request_irq(dev, platक्रमm_get_irq(pdev, 0),
			       vc4_crtc_irq_handler,
			       IRQF_SHARED,
			       "vc4 crtc", vc4_crtc);
	अगर (ret)
		जाओ err_destroy_planes;

	platक्रमm_set_drvdata(pdev, vc4_crtc);

	vc4_debugfs_add_regset32(drm, pv_data->debugfs_name,
				 &vc4_crtc->regset);

	वापस 0;

err_destroy_planes:
	list_क्रम_each_entry_safe(destroy_plane, temp,
				 &drm->mode_config.plane_list, head) अणु
		अगर (destroy_plane->possible_crtcs == drm_crtc_mask(crtc))
		    destroy_plane->funcs->destroy(destroy_plane);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vc4_crtc_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा vc4_crtc *vc4_crtc = dev_get_drvdata(dev);

	vc4_crtc_destroy(&vc4_crtc->base);

	CRTC_WRITE(PV_INTEN, 0);

	platक्रमm_set_drvdata(pdev, शून्य);
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_crtc_ops = अणु
	.bind   = vc4_crtc_bind,
	.unbind = vc4_crtc_unbind,
पूर्ण;

अटल पूर्णांक vc4_crtc_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_crtc_ops);
पूर्ण

अटल पूर्णांक vc4_crtc_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_crtc_ops);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vc4_crtc_driver = अणु
	.probe = vc4_crtc_dev_probe,
	.हटाओ = vc4_crtc_dev_हटाओ,
	.driver = अणु
		.name = "vc4_crtc",
		.of_match_table = vc4_crtc_dt_match,
	पूर्ण,
पूर्ण;
