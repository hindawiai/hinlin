<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Traphandler
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Jean-Jacques Hiblot <jjhiblot@traphandler.com>
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/mfd/aपंचांगel-hlcdc.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "atmel_hlcdc_dc.h"

#घोषणा ATMEL_HLCDC_LAYER_IRQS_OFFSET		8

अटल स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc aपंचांगel_hlcdc_at91sam9n12_layers[] = अणु
	अणु
		.name = "base",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x40,
		.id = 0,
		.type = ATMEL_HLCDC_BASE_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.xstride = अणु 2 पूर्ण,
			.शेष_color = 3,
			.general_config = 4,
		पूर्ण,
		.clut_offset = 0x400,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc aपंचांगel_hlcdc_dc_at91sam9n12 = अणु
	.min_width = 0,
	.min_height = 0,
	.max_width = 1280,
	.max_height = 860,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0xff,
	.conflicting_output_क्रमmats = true,
	.nlayers = ARRAY_SIZE(aपंचांगel_hlcdc_at91sam9n12_layers),
	.layers = aपंचांगel_hlcdc_at91sam9n12_layers,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc aपंचांगel_hlcdc_at91sam9x5_layers[] = अणु
	अणु
		.name = "base",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x40,
		.id = 0,
		.type = ATMEL_HLCDC_BASE_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.xstride = अणु 2 पूर्ण,
			.शेष_color = 3,
			.general_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		पूर्ण,
		.clut_offset = 0x400,
	पूर्ण,
	अणु
		.name = "overlay1",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x100,
		.id = 1,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0x800,
	पूर्ण,
	अणु
		.name = "high-end-overlay",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats,
		.regs_offset = 0x280,
		.id = 2,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x4c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstride = अणु 5, 7 पूर्ण,
			.pstride = अणु 6, 8 पूर्ण,
			.शेष_color = 9,
			.chroma_key = 10,
			.chroma_key_mask = 11,
			.general_config = 12,
			.scaler_config = 13,
			.csc = 14,
		पूर्ण,
		.clut_offset = 0x1000,
	पूर्ण,
	अणु
		.name = "cursor",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x340,
		.id = 3,
		.type = ATMEL_HLCDC_CURSOR_LAYER,
		.max_width = 128,
		.max_height = 128,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0x1400,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc aपंचांगel_hlcdc_dc_at91sam9x5 = अणु
	.min_width = 0,
	.min_height = 0,
	.max_width = 800,
	.max_height = 600,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0xff,
	.conflicting_output_क्रमmats = true,
	.nlayers = ARRAY_SIZE(aपंचांगel_hlcdc_at91sam9x5_layers),
	.layers = aपंचांगel_hlcdc_at91sam9x5_layers,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc aपंचांगel_hlcdc_sama5d3_layers[] = अणु
	अणु
		.name = "base",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x40,
		.id = 0,
		.type = ATMEL_HLCDC_BASE_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.xstride = अणु 2 पूर्ण,
			.शेष_color = 3,
			.general_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		पूर्ण,
		.clut_offset = 0x600,
	पूर्ण,
	अणु
		.name = "overlay1",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x140,
		.id = 1,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xa00,
	पूर्ण,
	अणु
		.name = "overlay2",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x240,
		.id = 2,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xe00,
	पूर्ण,
	अणु
		.name = "high-end-overlay",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats,
		.regs_offset = 0x340,
		.id = 3,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x4c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstride = अणु 5, 7 पूर्ण,
			.pstride = अणु 6, 8 पूर्ण,
			.शेष_color = 9,
			.chroma_key = 10,
			.chroma_key_mask = 11,
			.general_config = 12,
			.scaler_config = 13,
			.phicoeffs = अणु
				.x = 17,
				.y = 33,
			पूर्ण,
			.csc = 14,
		पूर्ण,
		.clut_offset = 0x1200,
	पूर्ण,
	अणु
		.name = "cursor",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x440,
		.id = 4,
		.type = ATMEL_HLCDC_CURSOR_LAYER,
		.max_width = 128,
		.max_height = 128,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
			.scaler_config = 13,
		पूर्ण,
		.clut_offset = 0x1600,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc aपंचांगel_hlcdc_dc_sama5d3 = अणु
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0x1ff,
	.conflicting_output_क्रमmats = true,
	.nlayers = ARRAY_SIZE(aपंचांगel_hlcdc_sama5d3_layers),
	.layers = aपंचांगel_hlcdc_sama5d3_layers,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc aपंचांगel_hlcdc_sama5d4_layers[] = अणु
	अणु
		.name = "base",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x40,
		.id = 0,
		.type = ATMEL_HLCDC_BASE_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.xstride = अणु 2 पूर्ण,
			.शेष_color = 3,
			.general_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		पूर्ण,
		.clut_offset = 0x600,
	पूर्ण,
	अणु
		.name = "overlay1",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x140,
		.id = 1,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xa00,
	पूर्ण,
	अणु
		.name = "overlay2",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x240,
		.id = 2,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xe00,
	पूर्ण,
	अणु
		.name = "high-end-overlay",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats,
		.regs_offset = 0x340,
		.id = 3,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x4c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstride = अणु 5, 7 पूर्ण,
			.pstride = अणु 6, 8 पूर्ण,
			.शेष_color = 9,
			.chroma_key = 10,
			.chroma_key_mask = 11,
			.general_config = 12,
			.scaler_config = 13,
			.phicoeffs = अणु
				.x = 17,
				.y = 33,
			पूर्ण,
			.csc = 14,
		पूर्ण,
		.clut_offset = 0x1200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc aपंचांगel_hlcdc_dc_sama5d4 = अणु
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0xff,
	.max_vpw = 0xff,
	.max_hpw = 0x3ff,
	.nlayers = ARRAY_SIZE(aपंचांगel_hlcdc_sama5d4_layers),
	.layers = aपंचांगel_hlcdc_sama5d4_layers,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc aपंचांगel_hlcdc_sam9x60_layers[] = अणु
	अणु
		.name = "base",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x60,
		.id = 0,
		.type = ATMEL_HLCDC_BASE_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.xstride = अणु 2 पूर्ण,
			.शेष_color = 3,
			.general_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		पूर्ण,
		.clut_offset = 0x600,
	पूर्ण,
	अणु
		.name = "overlay1",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x160,
		.id = 1,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xa00,
	पूर्ण,
	अणु
		.name = "overlay2",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_क्रमmats,
		.regs_offset = 0x260,
		.id = 2,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x2c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.xstride = अणु 4 पूर्ण,
			.pstride = अणु 5 पूर्ण,
			.शेष_color = 6,
			.chroma_key = 7,
			.chroma_key_mask = 8,
			.general_config = 9,
		पूर्ण,
		.clut_offset = 0xe00,
	पूर्ण,
	अणु
		.name = "high-end-overlay",
		.क्रमmats = &aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats,
		.regs_offset = 0x360,
		.id = 3,
		.type = ATMEL_HLCDC_OVERLAY_LAYER,
		.cfgs_offset = 0x4c,
		.layout = अणु
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstride = अणु 5, 7 पूर्ण,
			.pstride = अणु 6, 8 पूर्ण,
			.शेष_color = 9,
			.chroma_key = 10,
			.chroma_key_mask = 11,
			.general_config = 12,
			.scaler_config = 13,
			.phicoeffs = अणु
				.x = 17,
				.y = 33,
			पूर्ण,
			.csc = 14,
		पूर्ण,
		.clut_offset = 0x1200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc aपंचांगel_hlcdc_dc_sam9x60 = अणु
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0xff,
	.max_vpw = 0xff,
	.max_hpw = 0x3ff,
	.fixed_clksrc = true,
	.nlayers = ARRAY_SIZE(aपंचांगel_hlcdc_sam9x60_layers),
	.layers = aपंचांगel_hlcdc_sam9x60_layers,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_hlcdc_of_match[] = अणु
	अणु
		.compatible = "atmel,at91sam9n12-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_at91sam9n12,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9x5-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_at91sam9x5,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d2-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_sama5d4,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d3-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_sama5d3,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d4-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_sama5d4,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-hlcdc",
		.data = &aपंचांगel_hlcdc_dc_sam9x60,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_hlcdc_of_match);

क्रमागत drm_mode_status
aपंचांगel_hlcdc_dc_mode_valid(काष्ठा aपंचांगel_hlcdc_dc *dc,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक vfront_porch = mode->vsync_start - mode->vdisplay;
	पूर्णांक vback_porch = mode->vtotal - mode->vsync_end;
	पूर्णांक vsync_len = mode->vsync_end - mode->vsync_start;
	पूर्णांक hfront_porch = mode->hsync_start - mode->hdisplay;
	पूर्णांक hback_porch = mode->htotal - mode->hsync_end;
	पूर्णांक hsync_len = mode->hsync_end - mode->hsync_start;

	अगर (hsync_len > dc->desc->max_spw + 1 || hsync_len < 1)
		वापस MODE_HSYNC;

	अगर (vsync_len > dc->desc->max_spw + 1 || vsync_len < 1)
		वापस MODE_VSYNC;

	अगर (hfront_porch > dc->desc->max_hpw + 1 || hfront_porch < 1 ||
	    hback_porch > dc->desc->max_hpw + 1 || hback_porch < 1 ||
	    mode->hdisplay < 1)
		वापस MODE_H_ILLEGAL;

	अगर (vfront_porch > dc->desc->max_vpw + 1 || vfront_porch < 1 ||
	    vback_porch > dc->desc->max_vpw || vback_porch < 0 ||
	    mode->vdisplay < 1)
		वापस MODE_V_ILLEGAL;

	वापस MODE_OK;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_layer_irq(काष्ठा aपंचांगel_hlcdc_layer *layer)
अणु
	अगर (!layer)
		वापस;

	अगर (layer->desc->type == ATMEL_HLCDC_BASE_LAYER ||
	    layer->desc->type == ATMEL_HLCDC_OVERLAY_LAYER ||
	    layer->desc->type == ATMEL_HLCDC_CURSOR_LAYER)
		aपंचांगel_hlcdc_plane_irq(aपंचांगel_hlcdc_layer_to_plane(layer));
पूर्ण

अटल irqवापस_t aपंचांगel_hlcdc_dc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा drm_device *dev = data;
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक imr, isr;
	पूर्णांक i;

	regmap_पढ़ो(dc->hlcdc->regmap, ATMEL_HLCDC_IMR, &imr);
	regmap_पढ़ो(dc->hlcdc->regmap, ATMEL_HLCDC_ISR, &isr);
	status = imr & isr;
	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & ATMEL_HLCDC_SOF)
		aपंचांगel_hlcdc_crtc_irq(dc->crtc);

	क्रम (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) अणु
		अगर (ATMEL_HLCDC_LAYER_STATUS(i) & status)
			aपंचांगel_hlcdc_layer_irq(dc->layers[i]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_dc_modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	पूर्णांक ret;

	drm_mode_config_init(dev);

	ret = aपंचांगel_hlcdc_create_outमाला_दो(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to create HLCDC outputs: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = aपंचांगel_hlcdc_create_planes(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to create planes: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = aपंचांगel_hlcdc_crtc_create(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to create crtc\n");
		वापस ret;
	पूर्ण

	dev->mode_config.min_width = dc->desc->min_width;
	dev->mode_config.min_height = dc->desc->min_height;
	dev->mode_config.max_width = dc->desc->max_width;
	dev->mode_config.max_height = dc->desc->max_height;
	dev->mode_config.funcs = &mode_config_funcs;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_dc_load(काष्ठा drm_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aपंचांगel_hlcdc_dc *dc;
	पूर्णांक ret;

	match = of_match_node(aपंचांगel_hlcdc_of_match, dev->dev->parent->of_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "invalid compatible string\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!match->data) अणु
		dev_err(&pdev->dev, "invalid hlcdc description\n");
		वापस -EINVAL;
	पूर्ण

	dc = devm_kzalloc(dev->dev, माप(*dc), GFP_KERNEL);
	अगर (!dc)
		वापस -ENOMEM;

	dc->desc = match->data;
	dc->hlcdc = dev_get_drvdata(dev->dev->parent);
	dev->dev_निजी = dc;

	ret = clk_prepare_enable(dc->hlcdc->periph_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to enable periph_clk\n");
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev->dev);

	ret = drm_vblank_init(dev, 1);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to initialize vblank\n");
		जाओ err_periph_clk_disable;
	पूर्ण

	ret = aपंचांगel_hlcdc_dc_modeset_init(dev);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to initialize mode setting\n");
		जाओ err_periph_clk_disable;
	पूर्ण

	drm_mode_config_reset(dev);

	pm_runसमय_get_sync(dev->dev);
	ret = drm_irq_install(dev, dc->hlcdc->irq);
	pm_runसमय_put_sync(dev->dev);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to install IRQ handler\n");
		जाओ err_periph_clk_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	drm_kms_helper_poll_init(dev);

	वापस 0;

err_periph_clk_disable:
	pm_runसमय_disable(dev->dev);
	clk_disable_unprepare(dc->hlcdc->periph_clk);

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_dc_unload(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;

	drm_kms_helper_poll_fini(dev);
	drm_atomic_helper_shutकरोwn(dev);
	drm_mode_config_cleanup(dev);

	pm_runसमय_get_sync(dev->dev);
	drm_irq_uninstall(dev);
	pm_runसमय_put_sync(dev->dev);

	dev->dev_निजी = शून्य;

	pm_runसमय_disable(dev->dev);
	clk_disable_unprepare(dc->hlcdc->periph_clk);
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_dc_irq_postinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	अचिन्हित पूर्णांक cfg = 0;
	पूर्णांक i;

	/* Enable पूर्णांकerrupts on activated layers */
	क्रम (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) अणु
		अगर (dc->layers[i])
			cfg |= ATMEL_HLCDC_LAYER_STATUS(i);
	पूर्ण

	regmap_ग_लिखो(dc->hlcdc->regmap, ATMEL_HLCDC_IER, cfg);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_hlcdc_dc_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_dc *dc = dev->dev_निजी;
	अचिन्हित पूर्णांक isr;

	regmap_ग_लिखो(dc->hlcdc->regmap, ATMEL_HLCDC_IDR, 0xffffffff);
	regmap_पढ़ो(dc->hlcdc->regmap, ATMEL_HLCDC_ISR, &isr);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver aपंचांगel_hlcdc_dc_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.irq_handler = aपंचांगel_hlcdc_dc_irq_handler,
	.irq_preinstall = aपंचांगel_hlcdc_dc_irq_uninstall,
	.irq_postinstall = aपंचांगel_hlcdc_dc_irq_postinstall,
	.irq_uninstall = aपंचांगel_hlcdc_dc_irq_uninstall,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops = &fops,
	.name = "atmel-hlcdc",
	.desc = "Atmel HLCD Controller DRM",
	.date = "20141504",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_dc_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *ddev;
	पूर्णांक ret;

	ddev = drm_dev_alloc(&aपंचांगel_hlcdc_dc_driver, &pdev->dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ret = aपंचांगel_hlcdc_dc_load(ddev);
	अगर (ret)
		जाओ err_put;

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ err_unload;

	drm_fbdev_generic_setup(ddev, 24);

	वापस 0;

err_unload:
	aपंचांगel_hlcdc_dc_unload(ddev);

err_put:
	drm_dev_put(ddev);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_dc_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *ddev = platक्रमm_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(ddev);
	aपंचांगel_hlcdc_dc_unload(ddev);
	drm_dev_put(ddev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_hlcdc_dc_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_hlcdc_dc *dc = drm_dev->dev_निजी;
	काष्ठा regmap *regmap = dc->hlcdc->regmap;
	काष्ठा drm_atomic_state *state;

	state = drm_atomic_helper_suspend(drm_dev);
	अगर (IS_ERR(state))
		वापस PTR_ERR(state);

	dc->suspend.state = state;

	regmap_पढ़ो(regmap, ATMEL_HLCDC_IMR, &dc->suspend.imr);
	regmap_ग_लिखो(regmap, ATMEL_HLCDC_IDR, dc->suspend.imr);
	clk_disable_unprepare(dc->hlcdc->periph_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_dc_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_hlcdc_dc *dc = drm_dev->dev_निजी;

	clk_prepare_enable(dc->hlcdc->periph_clk);
	regmap_ग_लिखो(dc->hlcdc->regmap, ATMEL_HLCDC_IER, dc->suspend.imr);

	वापस drm_atomic_helper_resume(drm_dev, dc->suspend.state);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_hlcdc_dc_drm_pm_ops,
		aपंचांगel_hlcdc_dc_drm_suspend, aपंचांगel_hlcdc_dc_drm_resume);

अटल स्थिर काष्ठा of_device_id aपंचांगel_hlcdc_dc_of_match[] = अणु
	अणु .compatible = "atmel,hlcdc-display-controller" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aपंचांगel_hlcdc_dc_platक्रमm_driver = अणु
	.probe	= aपंचांगel_hlcdc_dc_drm_probe,
	.हटाओ	= aपंचांगel_hlcdc_dc_drm_हटाओ,
	.driver	= अणु
		.name	= "atmel-hlcdc-display-controller",
		.pm	= &aपंचांगel_hlcdc_dc_drm_pm_ops,
		.of_match_table = aपंचांगel_hlcdc_dc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_hlcdc_dc_platक्रमm_driver);

MODULE_AUTHOR("Jean-Jacques Hiblot <jjhiblot@traphandler.com>");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("Atmel HLCDC Display Controller DRM Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:atmel-hlcdc-dc");
