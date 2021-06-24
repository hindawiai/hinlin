<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Traphandler
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Jean-Jacques Hiblot <jjhiblot@traphandler.com>
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/mfd/aपंचांगel-hlcdc.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "atmel_hlcdc_dc.h"

/**
 * काष्ठा aपंचांगel_hlcdc_crtc_state - Aपंचांगel HLCDC CRTC state काष्ठाure
 *
 * @base: base CRTC state
 * @output_mode: RGBXXX output mode
 */
काष्ठा aपंचांगel_hlcdc_crtc_state अणु
	काष्ठा drm_crtc_state base;
	अचिन्हित पूर्णांक output_mode;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_crtc_state *
drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(काष्ठा drm_crtc_state *state)
अणु
	वापस container_of(state, काष्ठा aपंचांगel_hlcdc_crtc_state, base);
पूर्ण

/**
 * काष्ठा aपंचांगel_hlcdc_crtc - Aपंचांगel HLCDC CRTC काष्ठाure
 *
 * @base: base DRM CRTC काष्ठाure
 * @dc: poपूर्णांकer to the aपंचांगel_hlcdc काष्ठाure provided by the MFD device
 * @event: poपूर्णांकer to the current page flip event
 * @id: CRTC id (वापसed by drm_crtc_index)
 */
काष्ठा aपंचांगel_hlcdc_crtc अणु
	काष्ठा drm_crtc base;
	काष्ठा aपंचांगel_hlcdc_dc *dc;
	काष्ठा drm_pending_vblank_event *event;
	पूर्णांक id;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_crtc *
drm_crtc_to_aपंचांगel_hlcdc_crtc(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा aपंचांगel_hlcdc_crtc, base);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_mode_set_nofb(काष्ठा drm_crtc *c)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);
	काष्ठा regmap *regmap = crtc->dc->hlcdc->regmap;
	काष्ठा drm_display_mode *adj = &c->state->adjusted_mode;
	काष्ठा aपंचांगel_hlcdc_crtc_state *state;
	अचिन्हित दीर्घ mode_rate;
	काष्ठा videomode vm;
	अचिन्हित दीर्घ prate;
	अचिन्हित पूर्णांक mask = ATMEL_HLCDC_CLKDIV_MASK | ATMEL_HLCDC_CLKPOL;
	अचिन्हित पूर्णांक cfg = 0;
	पूर्णांक भाग, ret;

	ret = clk_prepare_enable(crtc->dc->hlcdc->sys_clk);
	अगर (ret)
		वापस;

	vm.vfront_porch = adj->crtc_vsync_start - adj->crtc_vdisplay;
	vm.vback_porch = adj->crtc_vtotal - adj->crtc_vsync_end;
	vm.vsync_len = adj->crtc_vsync_end - adj->crtc_vsync_start;
	vm.hfront_porch = adj->crtc_hsync_start - adj->crtc_hdisplay;
	vm.hback_porch = adj->crtc_htotal - adj->crtc_hsync_end;
	vm.hsync_len = adj->crtc_hsync_end - adj->crtc_hsync_start;

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_CFG(1),
		     (vm.hsync_len - 1) | ((vm.vsync_len - 1) << 16));

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_CFG(2),
		     (vm.vfront_porch - 1) | (vm.vback_porch << 16));

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_CFG(3),
		     (vm.hfront_porch - 1) | ((vm.hback_porch - 1) << 16));

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_CFG(4),
		     (adj->crtc_hdisplay - 1) |
		     ((adj->crtc_vdisplay - 1) << 16));

	prate = clk_get_rate(crtc->dc->hlcdc->sys_clk);
	mode_rate = adj->crtc_घड़ी * 1000;
	अगर (!crtc->dc->desc->fixed_clksrc) अणु
		prate *= 2;
		cfg |= ATMEL_HLCDC_CLKSEL;
		mask |= ATMEL_HLCDC_CLKSEL;
	पूर्ण

	भाग = DIV_ROUND_UP(prate, mode_rate);
	अगर (भाग < 2) अणु
		भाग = 2;
	पूर्ण अन्यथा अगर (ATMEL_HLCDC_CLKDIV(भाग) & ~ATMEL_HLCDC_CLKDIV_MASK) अणु
		/* The भागider ended up too big, try a lower base rate. */
		cfg &= ~ATMEL_HLCDC_CLKSEL;
		prate /= 2;
		भाग = DIV_ROUND_UP(prate, mode_rate);
		अगर (ATMEL_HLCDC_CLKDIV(भाग) & ~ATMEL_HLCDC_CLKDIV_MASK)
			भाग = ATMEL_HLCDC_CLKDIV_MASK;
	पूर्ण अन्यथा अणु
		पूर्णांक भाग_low = prate / mode_rate;

		अगर (भाग_low >= 2 &&
		    (10 * (prate / भाग_low - mode_rate) <
		     (mode_rate - prate / भाग)))
			/*
			 * At least 10 बार better when using a higher
			 * frequency than requested, instead of a lower.
			 * So, go with that.
			 */
			भाग = भाग_low;
	पूर्ण

	cfg |= ATMEL_HLCDC_CLKDIV(भाग);

	regmap_update_bits(regmap, ATMEL_HLCDC_CFG(0), mask, cfg);

	state = drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(c->state);
	cfg = state->output_mode << 8;

	अगर (adj->flags & DRM_MODE_FLAG_NVSYNC)
		cfg |= ATMEL_HLCDC_VSPOL;

	अगर (adj->flags & DRM_MODE_FLAG_NHSYNC)
		cfg |= ATMEL_HLCDC_HSPOL;

	regmap_update_bits(regmap, ATMEL_HLCDC_CFG(5),
			   ATMEL_HLCDC_HSPOL | ATMEL_HLCDC_VSPOL |
			   ATMEL_HLCDC_VSPDLYS | ATMEL_HLCDC_VSPDLYE |
			   ATMEL_HLCDC_DISPPOL | ATMEL_HLCDC_DISPDLY |
			   ATMEL_HLCDC_VSPSU | ATMEL_HLCDC_VSPHO |
			   ATMEL_HLCDC_GUARDTIME_MASK | ATMEL_HLCDC_MODE_MASK,
			   cfg);

	clk_disable_unprepare(crtc->dc->hlcdc->sys_clk);
पूर्ण

अटल क्रमागत drm_mode_status
aपंचांगel_hlcdc_crtc_mode_valid(काष्ठा drm_crtc *c,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);

	वापस aपंचांगel_hlcdc_dc_mode_valid(crtc->dc, mode);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_atomic_disable(काष्ठा drm_crtc *c,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = c->dev;
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);
	काष्ठा regmap *regmap = crtc->dc->hlcdc->regmap;
	अचिन्हित पूर्णांक status;

	drm_crtc_vblank_off(c);

	pm_runसमय_get_sync(dev->dev);

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_DISP);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_DISP))
		cpu_relax();

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_SYNC);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_SYNC))
		cpu_relax();

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_DIS, ATMEL_HLCDC_PIXEL_CLK);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       (status & ATMEL_HLCDC_PIXEL_CLK))
		cpu_relax();

	clk_disable_unprepare(crtc->dc->hlcdc->sys_clk);
	pinctrl_pm_select_sleep_state(dev->dev);

	pm_runसमय_allow(dev->dev);

	pm_runसमय_put_sync(dev->dev);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_atomic_enable(काष्ठा drm_crtc *c,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = c->dev;
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);
	काष्ठा regmap *regmap = crtc->dc->hlcdc->regmap;
	अचिन्हित पूर्णांक status;

	pm_runसमय_get_sync(dev->dev);

	pm_runसमय_क्रमbid(dev->dev);

	pinctrl_pm_select_शेष_state(dev->dev);
	clk_prepare_enable(crtc->dc->hlcdc->sys_clk);

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_EN, ATMEL_HLCDC_PIXEL_CLK);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       !(status & ATMEL_HLCDC_PIXEL_CLK))
		cpu_relax();


	regmap_ग_लिखो(regmap, ATMEL_HLCDC_EN, ATMEL_HLCDC_SYNC);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       !(status & ATMEL_HLCDC_SYNC))
		cpu_relax();

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_EN, ATMEL_HLCDC_DISP);
	जबतक (!regmap_पढ़ो(regmap, ATMEL_HLCDC_SR, &status) &&
	       !(status & ATMEL_HLCDC_DISP))
		cpu_relax();

	pm_runसमय_put_sync(dev->dev);

	drm_crtc_vblank_on(c);
पूर्ण

#घोषणा ATMEL_HLCDC_RGB444_OUTPUT	BIT(0)
#घोषणा ATMEL_HLCDC_RGB565_OUTPUT	BIT(1)
#घोषणा ATMEL_HLCDC_RGB666_OUTPUT	BIT(2)
#घोषणा ATMEL_HLCDC_RGB888_OUTPUT	BIT(3)
#घोषणा ATMEL_HLCDC_OUTPUT_MODE_MASK	GENMASK(3, 0)

अटल पूर्णांक aपंचांगel_hlcdc_connector_output_mode(काष्ठा drm_connector_state *state)
अणु
	काष्ठा drm_connector *connector = state->connector;
	काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा drm_encoder *encoder;
	अचिन्हित पूर्णांक supported_fmts = 0;
	पूर्णांक j;

	encoder = state->best_encoder;
	अगर (!encoder)
		encoder = connector->encoder;

	चयन (aपंचांगel_hlcdc_encoder_get_bus_fmt(encoder)) अणु
	हाल 0:
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB444_1X12:
		वापस ATMEL_HLCDC_RGB444_OUTPUT;
	हाल MEDIA_BUS_FMT_RGB565_1X16:
		वापस ATMEL_HLCDC_RGB565_OUTPUT;
	हाल MEDIA_BUS_FMT_RGB666_1X18:
		वापस ATMEL_HLCDC_RGB666_OUTPUT;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		वापस ATMEL_HLCDC_RGB888_OUTPUT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (j = 0; j < info->num_bus_क्रमmats; j++) अणु
		चयन (info->bus_क्रमmats[j]) अणु
		हाल MEDIA_BUS_FMT_RGB444_1X12:
			supported_fmts |= ATMEL_HLCDC_RGB444_OUTPUT;
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB565_1X16:
			supported_fmts |= ATMEL_HLCDC_RGB565_OUTPUT;
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB666_1X18:
			supported_fmts |= ATMEL_HLCDC_RGB666_OUTPUT;
			अवरोध;
		हाल MEDIA_BUS_FMT_RGB888_1X24:
			supported_fmts |= ATMEL_HLCDC_RGB888_OUTPUT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस supported_fmts;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_crtc_select_output_mode(काष्ठा drm_crtc_state *state)
अणु
	अचिन्हित पूर्णांक output_fmts = ATMEL_HLCDC_OUTPUT_MODE_MASK;
	काष्ठा aपंचांगel_hlcdc_crtc_state *hstate;
	काष्ठा drm_connector_state *cstate;
	काष्ठा drm_connector *connector;
	काष्ठा aपंचांगel_hlcdc_crtc *crtc;
	पूर्णांक i;

	crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(state->crtc);

	क्रम_each_new_connector_in_state(state->state, connector, cstate, i) अणु
		अचिन्हित पूर्णांक supported_fmts = 0;

		अगर (!cstate->crtc)
			जारी;

		supported_fmts = aपंचांगel_hlcdc_connector_output_mode(cstate);

		अगर (crtc->dc->desc->conflicting_output_क्रमmats)
			output_fmts &= supported_fmts;
		अन्यथा
			output_fmts |= supported_fmts;
	पूर्ण

	अगर (!output_fmts)
		वापस -EINVAL;

	hstate = drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(state);
	hstate->output_mode = fls(output_fmts) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_crtc_atomic_check(काष्ठा drm_crtc *c,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *s = drm_atomic_get_new_crtc_state(state, c);
	पूर्णांक ret;

	ret = aपंचांगel_hlcdc_crtc_select_output_mode(s);
	अगर (ret)
		वापस ret;

	ret = aपंचांगel_hlcdc_plane_prepare_disc_area(s);
	अगर (ret)
		वापस ret;

	वापस aपंचांगel_hlcdc_plane_prepare_ahb_routing(s);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_atomic_begin(काष्ठा drm_crtc *c,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);

	अगर (c->state->event) अणु
		c->state->event->pipe = drm_crtc_index(c);

		WARN_ON(drm_crtc_vblank_get(c) != 0);

		crtc->event = c->state->event;
		c->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	/* TODO: ग_लिखो common plane control रेजिस्टर अगर available */
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs lcdc_crtc_helper_funcs = अणु
	.mode_valid = aपंचांगel_hlcdc_crtc_mode_valid,
	.mode_set_nofb = aपंचांगel_hlcdc_crtc_mode_set_nofb,
	.atomic_check = aपंचांगel_hlcdc_crtc_atomic_check,
	.atomic_begin = aपंचांगel_hlcdc_crtc_atomic_begin,
	.atomic_flush = aपंचांगel_hlcdc_crtc_atomic_flush,
	.atomic_enable = aपंचांगel_hlcdc_crtc_atomic_enable,
	.atomic_disable = aपंचांगel_hlcdc_crtc_atomic_disable,
पूर्ण;

अटल व्योम aपंचांगel_hlcdc_crtc_destroy(काष्ठा drm_crtc *c)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);

	drm_crtc_cleanup(c);
	kमुक्त(crtc);
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_finish_page_flip(काष्ठा aपंचांगel_hlcdc_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (crtc->event) अणु
		drm_crtc_send_vblank_event(&crtc->base, crtc->event);
		drm_crtc_vblank_put(&crtc->base);
		crtc->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

व्योम aपंचांगel_hlcdc_crtc_irq(काष्ठा drm_crtc *c)
अणु
	drm_crtc_handle_vblank(c);
	aपंचांगel_hlcdc_crtc_finish_page_flip(drm_crtc_to_aपंचांगel_hlcdc_crtc(c));
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc_state *state;

	अगर (crtc->state) अणु
		__drm_atomic_helper_crtc_destroy_state(crtc->state);
		state = drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(crtc->state);
		kमुक्त(state);
		crtc->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
aपंचांगel_hlcdc_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc_state *state, *cur;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;
	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	cur = drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(crtc->state);
	state->output_mode = cur->output_mode;

	वापस &state->base;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_destroy_state(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_crtc_state *s)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc_state *state;

	state = drm_crtc_state_to_aपंचांगel_hlcdc_crtc_state(s);
	__drm_atomic_helper_crtc_destroy_state(s);
	kमुक्त(state);
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_crtc_enable_vblank(काष्ठा drm_crtc *c)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);
	काष्ठा regmap *regmap = crtc->dc->hlcdc->regmap;

	/* Enable SOF (Start Of Frame) पूर्णांकerrupt क्रम vblank counting */
	regmap_ग_लिखो(regmap, ATMEL_HLCDC_IER, ATMEL_HLCDC_SOF);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_crtc_disable_vblank(काष्ठा drm_crtc *c)
अणु
	काष्ठा aपंचांगel_hlcdc_crtc *crtc = drm_crtc_to_aपंचांगel_hlcdc_crtc(c);
	काष्ठा regmap *regmap = crtc->dc->hlcdc->regmap;

	regmap_ग_लिखो(regmap, ATMEL_HLCDC_IDR, ATMEL_HLCDC_SOF);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs aपंचांगel_hlcdc_crtc_funcs = अणु
	.page_flip = drm_atomic_helper_page_flip,
	.set_config = drm_atomic_helper_set_config,
	.destroy = aपंचांगel_hlcdc_crtc_destroy,
	.reset = aपंचांगel_hlcdc_crtc_reset,
	.atomic_duplicate_state =  aपंचांगel_hlcdc_crtc_duplicate_state,
	.atomic_destroy_state = aपंचांगel_hlcdc_crtc_destroy_state,
	.enable_vblank = aपंचांगel_hlcdc_crtc_enable_vblank,
	.disable_vblank = aपंचांगel_hlcdc_crtc_disable_vblank,
पूर्ण;

पूर्णांक aपंचांगel_hlcdc_crtc_create(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_plane *primary = शून्य, *cursor = शून्य;
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	काष्ठा aपंचांगel_hlcdc_crtc *crtc;
	पूर्णांक ret;
	पूर्णांक i;

	crtc = kzalloc(माप(*crtc), GFP_KERNEL);
	अगर (!crtc)
		वापस -ENOMEM;

	crtc->dc = dc;

	क्रम (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) अणु
		अगर (!dc->layers[i])
			जारी;

		चयन (dc->layers[i]->desc->type) अणु
		हाल ATMEL_HLCDC_BASE_LAYER:
			primary = aपंचांगel_hlcdc_layer_to_plane(dc->layers[i]);
			अवरोध;

		हाल ATMEL_HLCDC_CURSOR_LAYER:
			cursor = aपंचांगel_hlcdc_layer_to_plane(dc->layers[i]);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ret = drm_crtc_init_with_planes(dev, &crtc->base, &primary->base,
					&cursor->base, &aपंचांगel_hlcdc_crtc_funcs,
					शून्य);
	अगर (ret < 0)
		जाओ fail;

	crtc->id = drm_crtc_index(&crtc->base);

	क्रम (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) अणु
		काष्ठा aपंचांगel_hlcdc_plane *overlay;

		अगर (dc->layers[i] &&
		    dc->layers[i]->desc->type == ATMEL_HLCDC_OVERLAY_LAYER) अणु
			overlay = aपंचांगel_hlcdc_layer_to_plane(dc->layers[i]);
			overlay->base.possible_crtcs = 1 << crtc->id;
		पूर्ण
	पूर्ण

	drm_crtc_helper_add(&crtc->base, &lcdc_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(&crtc->base, ATMEL_HLCDC_CLUT_SIZE);
	drm_crtc_enable_color_mgmt(&crtc->base, 0, false,
				   ATMEL_HLCDC_CLUT_SIZE);

	dc->crtc = &crtc->base;

	वापस 0;

fail:
	aपंचांगel_hlcdc_crtc_destroy(&crtc->base);
	वापस ret;
पूर्ण
