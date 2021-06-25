<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <uapi/drm/drm_mode.h>

#समावेश "sun4i_crtc.h"
#समावेश "sun4i_dotclock.h"
#समावेश "sun4i_drv.h"
#समावेश "sun4i_lvds.h"
#समावेश "sun4i_rgb.h"
#समावेश "sun4i_tcon.h"
#समावेश "sun6i_mipi_dsi.h"
#समावेश "sun8i_tcon_top.h"
#समावेश "sunxi_engine.h"

अटल काष्ठा drm_connector *sun4i_tcon_get_connector(स्थिर काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;

	drm_connector_list_iter_begin(encoder->dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter)
		अगर (connector->encoder == encoder) अणु
			drm_connector_list_iter_end(&iter);
			वापस connector;
		पूर्ण
	drm_connector_list_iter_end(&iter);

	वापस शून्य;
पूर्ण

अटल पूर्णांक sun4i_tcon_get_pixel_depth(स्थिर काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_display_info *info;

	connector = sun4i_tcon_get_connector(encoder);
	अगर (!connector)
		वापस -EINVAL;

	info = &connector->display_info;
	अगर (info->num_bus_क्रमmats != 1)
		वापस -EINVAL;

	चयन (info->bus_क्रमmats[0]) अणु
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		वापस 18;

	हाल MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		वापस 24;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम sun4i_tcon_channel_set_status(काष्ठा sun4i_tcon *tcon, पूर्णांक channel,
					  bool enabled)
अणु
	काष्ठा clk *clk;

	चयन (channel) अणु
	हाल 0:
		WARN_ON(!tcon->quirks->has_channel_0);
		regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
				   SUN4I_TCON0_CTL_TCON_ENABLE,
				   enabled ? SUN4I_TCON0_CTL_TCON_ENABLE : 0);
		clk = tcon->dclk;
		अवरोध;
	हाल 1:
		WARN_ON(!tcon->quirks->has_channel_1);
		regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
				   SUN4I_TCON1_CTL_TCON_ENABLE,
				   enabled ? SUN4I_TCON1_CTL_TCON_ENABLE : 0);
		clk = tcon->sclk1;
		अवरोध;
	शेष:
		DRM_WARN("Unknown channel... doing nothing\n");
		वापस;
	पूर्ण

	अगर (enabled) अणु
		clk_prepare_enable(clk);
		clk_rate_exclusive_get(clk);
	पूर्ण अन्यथा अणु
		clk_rate_exclusive_put(clk);
		clk_disable_unprepare(clk);
	पूर्ण
पूर्ण

अटल व्योम sun4i_tcon_setup_lvds_phy(काष्ठा sun4i_tcon *tcon,
				      स्थिर काष्ठा drm_encoder *encoder)
अणु
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
		     SUN4I_TCON0_LVDS_ANA0_CK_EN |
		     SUN4I_TCON0_LVDS_ANA0_REG_V |
		     SUN4I_TCON0_LVDS_ANA0_REG_C |
		     SUN4I_TCON0_LVDS_ANA0_EN_MB |
		     SUN4I_TCON0_LVDS_ANA0_PD |
		     SUN4I_TCON0_LVDS_ANA0_DCHS);

	udelay(2); /* delay at least 1200 ns */
	regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA1_REG,
			   SUN4I_TCON0_LVDS_ANA1_INIT,
			   SUN4I_TCON0_LVDS_ANA1_INIT);
	udelay(1); /* delay at least 120 ns */
	regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA1_REG,
			   SUN4I_TCON0_LVDS_ANA1_UPDATE,
			   SUN4I_TCON0_LVDS_ANA1_UPDATE);
	regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
			   SUN4I_TCON0_LVDS_ANA0_EN_MB,
			   SUN4I_TCON0_LVDS_ANA0_EN_MB);
पूर्ण

अटल व्योम sun6i_tcon_setup_lvds_phy(काष्ठा sun4i_tcon *tcon,
				      स्थिर काष्ठा drm_encoder *encoder)
अणु
	u8 val;

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
		     SUN6I_TCON0_LVDS_ANA0_C(2) |
		     SUN6I_TCON0_LVDS_ANA0_V(3) |
		     SUN6I_TCON0_LVDS_ANA0_PD(2) |
		     SUN6I_TCON0_LVDS_ANA0_EN_LDO);
	udelay(2);

	regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
			   SUN6I_TCON0_LVDS_ANA0_EN_MB,
			   SUN6I_TCON0_LVDS_ANA0_EN_MB);
	udelay(2);

	regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
			   SUN6I_TCON0_LVDS_ANA0_EN_DRVC,
			   SUN6I_TCON0_LVDS_ANA0_EN_DRVC);

	अगर (sun4i_tcon_get_pixel_depth(encoder) == 18)
		val = 7;
	अन्यथा
		val = 0xf;

	regmap_ग_लिखो_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
			  SUN6I_TCON0_LVDS_ANA0_EN_DRVD(0xf),
			  SUN6I_TCON0_LVDS_ANA0_EN_DRVD(val));
पूर्ण

अटल व्योम sun4i_tcon_lvds_set_status(काष्ठा sun4i_tcon *tcon,
				       स्थिर काष्ठा drm_encoder *encoder,
				       bool enabled)
अणु
	अगर (enabled) अणु
		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_IF_REG,
				   SUN4I_TCON0_LVDS_IF_EN,
				   SUN4I_TCON0_LVDS_IF_EN);
		अगर (tcon->quirks->setup_lvds_phy)
			tcon->quirks->setup_lvds_phy(tcon, encoder);
	पूर्ण अन्यथा अणु
		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_IF_REG,
				   SUN4I_TCON0_LVDS_IF_EN, 0);
	पूर्ण
पूर्ण

व्योम sun4i_tcon_set_status(काष्ठा sun4i_tcon *tcon,
			   स्थिर काष्ठा drm_encoder *encoder,
			   bool enabled)
अणु
	bool is_lvds = false;
	पूर्णांक channel;

	चयन (encoder->encoder_type) अणु
	हाल DRM_MODE_ENCODER_LVDS:
		is_lvds = true;
		fallthrough;
	हाल DRM_MODE_ENCODER_DSI:
	हाल DRM_MODE_ENCODER_NONE:
		channel = 0;
		अवरोध;
	हाल DRM_MODE_ENCODER_TMDS:
	हाल DRM_MODE_ENCODER_TVDAC:
		channel = 1;
		अवरोध;
	शेष:
		DRM_DEBUG_DRIVER("Unknown encoder type, doing nothing...\n");
		वापस;
	पूर्ण

	अगर (is_lvds && !enabled)
		sun4i_tcon_lvds_set_status(tcon, encoder, false);

	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_TCON_ENABLE,
			   enabled ? SUN4I_TCON_GCTL_TCON_ENABLE : 0);

	अगर (is_lvds && enabled)
		sun4i_tcon_lvds_set_status(tcon, encoder, true);

	sun4i_tcon_channel_set_status(tcon, channel, enabled);
पूर्ण

व्योम sun4i_tcon_enable_vblank(काष्ठा sun4i_tcon *tcon, bool enable)
अणु
	u32 mask, val = 0;

	DRM_DEBUG_DRIVER("%sabling VBLANK interrupt\n", enable ? "En" : "Dis");

	mask = SUN4I_TCON_GINT0_VBLANK_ENABLE(0) |
		SUN4I_TCON_GINT0_VBLANK_ENABLE(1) |
		SUN4I_TCON_GINT0_TCON0_TRI_FINISH_ENABLE;

	अगर (enable)
		val = mask;

	regmap_update_bits(tcon->regs, SUN4I_TCON_GINT0_REG, mask, val);
पूर्ण
EXPORT_SYMBOL(sun4i_tcon_enable_vblank);

/*
 * This function is a helper क्रम TCON output muxing. The TCON output
 * muxing control रेजिस्टर in earlier SoCs (without the TCON TOP block)
 * are located in TCON0. This helper वापसs a poपूर्णांकer to TCON0's
 * sun4i_tcon काष्ठाure, or शून्य अगर not found.
 */
अटल काष्ठा sun4i_tcon *sun4i_get_tcon0(काष्ठा drm_device *drm)
अणु
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sun4i_tcon *tcon;

	list_क्रम_each_entry(tcon, &drv->tcon_list, list)
		अगर (tcon->id == 0)
			वापस tcon;

	dev_warn(drm->dev,
		 "TCON0 not found, display output muxing may not work\n");

	वापस शून्य;
पूर्ण

अटल व्योम sun4i_tcon_set_mux(काष्ठा sun4i_tcon *tcon, पूर्णांक channel,
			       स्थिर काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (tcon->quirks->set_mux)
		ret = tcon->quirks->set_mux(tcon, encoder);

	DRM_DEBUG_DRIVER("Muxing encoder %s to CRTC %s: %d\n",
			 encoder->name, encoder->crtc->name, ret);
पूर्ण

अटल पूर्णांक sun4i_tcon_get_clk_delay(स्थिर काष्ठा drm_display_mode *mode,
				    पूर्णांक channel)
अणु
	पूर्णांक delay = mode->vtotal - mode->vdisplay;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		delay /= 2;

	अगर (channel == 1)
		delay -= 2;

	delay = min(delay, 30);

	DRM_DEBUG_DRIVER("TCON %d clock delay %u\n", channel, delay);

	वापस delay;
पूर्ण

अटल व्योम sun4i_tcon0_mode_set_common(काष्ठा sun4i_tcon *tcon,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* Configure the करोt घड़ी */
	clk_set_rate(tcon->dclk, mode->crtc_घड़ी * 1000);

	/* Set the resolution */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC0_REG,
		     SUN4I_TCON0_BASIC0_X(mode->crtc_hdisplay) |
		     SUN4I_TCON0_BASIC0_Y(mode->crtc_vdisplay));
पूर्ण

अटल व्योम sun4i_tcon0_mode_set_dithering(काष्ठा sun4i_tcon *tcon,
					   स्थिर काष्ठा drm_connector *connector)
अणु
	u32 bus_क्रमmat = 0;
	u32 val = 0;

	/* XXX Would this ever happen? */
	अगर (!connector)
		वापस;

	/*
	 * FIXME: Unकरोcumented bits
	 *
	 * The whole dithering process and these parameters are not
	 * explained in the venकरोr करोcuments or BSP kernel code.
	 */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_PR_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_PG_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_PB_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_LR_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_LG_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_SEED_LB_REG, 0x11111111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_TBL0_REG, 0x01010000);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_TBL1_REG, 0x15151111);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_TBL2_REG, 0x57575555);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_FRM_TBL3_REG, 0x7f7f7777);

	/* Do dithering अगर panel only supports 6 bits per color */
	अगर (connector->display_info.bpc == 6)
		val |= SUN4I_TCON0_FRM_CTL_EN;

	अगर (connector->display_info.num_bus_क्रमmats == 1)
		bus_क्रमmat = connector->display_info.bus_क्रमmats[0];

	/* Check the connection क्रमmat */
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB565_1X16:
		/* R and B components are only 5 bits deep */
		val |= SUN4I_TCON0_FRM_CTL_MODE_R;
		val |= SUN4I_TCON0_FRM_CTL_MODE_B;
		fallthrough;
	हाल MEDIA_BUS_FMT_RGB666_1X18:
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		/* Fall through: enable dithering */
		val |= SUN4I_TCON0_FRM_CTL_EN;
		अवरोध;
	पूर्ण

	/* Write dithering settings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_FRM_CTL_REG, val);
पूर्ण

अटल व्योम sun4i_tcon0_mode_set_cpu(काष्ठा sun4i_tcon *tcon,
				     स्थिर काष्ठा drm_encoder *encoder,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* TODO support normal CPU पूर्णांकerface modes */
	काष्ठा sun6i_dsi *dsi = encoder_to_sun6i_dsi(encoder);
	काष्ठा mipi_dsi_device *device = dsi->device;
	u8 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(device->क्रमmat);
	u8 lanes = device->lanes;
	u32 block_space, start_delay;
	u32 tcon_भाग;

	tcon->dclk_min_भाग = SUN6I_DSI_TCON_DIV;
	tcon->dclk_max_भाग = SUN6I_DSI_TCON_DIV;

	sun4i_tcon0_mode_set_common(tcon, mode);

	/* Set dithering अगर needed */
	sun4i_tcon0_mode_set_dithering(tcon, sun4i_tcon_get_connector(encoder));

	regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
			   SUN4I_TCON0_CTL_IF_MASK,
			   SUN4I_TCON0_CTL_IF_8080);

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_ECC_FIFO_REG,
		     SUN4I_TCON_ECC_FIFO_EN);

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_CPU_IF_REG,
		     SUN4I_TCON0_CPU_IF_MODE_DSI |
		     SUN4I_TCON0_CPU_IF_TRI_FIFO_FLUSH |
		     SUN4I_TCON0_CPU_IF_TRI_FIFO_EN |
		     SUN4I_TCON0_CPU_IF_TRI_EN);

	/*
	 * This looks suspicious, but it works...
	 *
	 * The datasheet says that this should be set higher than 20 *
	 * pixel cycle, but it's not clear what a pixel cycle is.
	 */
	regmap_पढ़ो(tcon->regs, SUN4I_TCON0_DCLK_REG, &tcon_भाग);
	tcon_भाग &= GENMASK(6, 0);
	block_space = mode->htotal * bpp / (tcon_भाग * lanes);
	block_space -= mode->hdisplay + 40;

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_CPU_TRI0_REG,
		     SUN4I_TCON0_CPU_TRI0_BLOCK_SPACE(block_space) |
		     SUN4I_TCON0_CPU_TRI0_BLOCK_SIZE(mode->hdisplay));

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_CPU_TRI1_REG,
		     SUN4I_TCON0_CPU_TRI1_BLOCK_NUM(mode->vdisplay));

	start_delay = (mode->crtc_vtotal - mode->crtc_vdisplay - 10 - 1);
	start_delay = start_delay * mode->crtc_htotal * 149;
	start_delay = start_delay / (mode->crtc_घड़ी / 1000) / 8;
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_CPU_TRI2_REG,
		     SUN4I_TCON0_CPU_TRI2_TRANS_START_SET(10) |
		     SUN4I_TCON0_CPU_TRI2_START_DELAY(start_delay));

	/*
	 * The Allwinner BSP has a comment that the period should be
	 * the display घड़ी * 15, but uses an hardcoded 3000...
	 */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_SAFE_PERIOD_REG,
		     SUN4I_TCON_SAFE_PERIOD_NUM(3000) |
		     SUN4I_TCON_SAFE_PERIOD_MODE(3));

	/* Enable the output on the pins */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_TRI_REG,
		     0xe0000000);
पूर्ण

अटल व्योम sun4i_tcon0_mode_set_lvds(काष्ठा sun4i_tcon *tcon,
				      स्थिर काष्ठा drm_encoder *encoder,
				      स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक bp;
	u8 clk_delay;
	u32 reg, val = 0;

	WARN_ON(!tcon->quirks->has_channel_0);

	tcon->dclk_min_भाग = 7;
	tcon->dclk_max_भाग = 7;
	sun4i_tcon0_mode_set_common(tcon, mode);

	/* Set dithering अगर needed */
	sun4i_tcon0_mode_set_dithering(tcon, sun4i_tcon_get_connector(encoder));

	/* Adjust घड़ी delay */
	clk_delay = sun4i_tcon_get_clk_delay(mode, 0);
	regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
			   SUN4I_TCON0_CTL_CLK_DELAY_MASK,
			   SUN4I_TCON0_CTL_CLK_DELAY(clk_delay));

	/*
	 * This is called a backporch in the रेजिस्टर करोcumentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_htotal - mode->crtc_hsync_start;
	DRM_DEBUG_DRIVER("Setting horizontal total %d, backporch %d\n",
			 mode->crtc_htotal, bp);

	/* Set horizontal display timings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC1_REG,
		     SUN4I_TCON0_BASIC1_H_TOTAL(mode->htotal) |
		     SUN4I_TCON0_BASIC1_H_BACKPORCH(bp));

	/*
	 * This is called a backporch in the रेजिस्टर करोcumentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_vtotal - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting vertical total %d, backporch %d\n",
			 mode->crtc_vtotal, bp);

	/* Set vertical display timings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC2_REG,
		     SUN4I_TCON0_BASIC2_V_TOTAL(mode->crtc_vtotal * 2) |
		     SUN4I_TCON0_BASIC2_V_BACKPORCH(bp));

	reg = SUN4I_TCON0_LVDS_IF_CLK_SEL_TCON0;
	अगर (sun4i_tcon_get_pixel_depth(encoder) == 24)
		reg |= SUN4I_TCON0_LVDS_IF_BITWIDTH_24BITS;
	अन्यथा
		reg |= SUN4I_TCON0_LVDS_IF_BITWIDTH_18BITS;

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_LVDS_IF_REG, reg);

	/* Setup the polarity of the various संकेतs */
	अगर (!(mode->flags & DRM_MODE_FLAG_PHSYNC))
		val |= SUN4I_TCON0_IO_POL_HSYNC_POSITIVE;

	अगर (!(mode->flags & DRM_MODE_FLAG_PVSYNC))
		val |= SUN4I_TCON0_IO_POL_VSYNC_POSITIVE;

	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_POL_REG, val);

	/* Map output pins to channel 0 */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_IOMAP_MASK,
			   SUN4I_TCON_GCTL_IOMAP_TCON0);

	/* Enable the output on the pins */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_TRI_REG, 0xe0000000);
पूर्ण

अटल व्योम sun4i_tcon0_mode_set_rgb(काष्ठा sun4i_tcon *tcon,
				     स्थिर काष्ठा drm_encoder *encoder,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_connector *connector = sun4i_tcon_get_connector(encoder);
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;
	अचिन्हित पूर्णांक bp, hsync, vsync;
	u8 clk_delay;
	u32 val = 0;

	WARN_ON(!tcon->quirks->has_channel_0);

	tcon->dclk_min_भाग = tcon->quirks->dclk_min_भाग;
	tcon->dclk_max_भाग = 127;
	sun4i_tcon0_mode_set_common(tcon, mode);

	/* Set dithering अगर needed */
	sun4i_tcon0_mode_set_dithering(tcon, connector);

	/* Adjust घड़ी delay */
	clk_delay = sun4i_tcon_get_clk_delay(mode, 0);
	regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
			   SUN4I_TCON0_CTL_CLK_DELAY_MASK,
			   SUN4I_TCON0_CTL_CLK_DELAY(clk_delay));

	/*
	 * This is called a backporch in the रेजिस्टर करोcumentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_htotal - mode->crtc_hsync_start;
	DRM_DEBUG_DRIVER("Setting horizontal total %d, backporch %d\n",
			 mode->crtc_htotal, bp);

	/* Set horizontal display timings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC1_REG,
		     SUN4I_TCON0_BASIC1_H_TOTAL(mode->crtc_htotal) |
		     SUN4I_TCON0_BASIC1_H_BACKPORCH(bp));

	/*
	 * This is called a backporch in the रेजिस्टर करोcumentation,
	 * but it really is the back porch + hsync
	 */
	bp = mode->crtc_vtotal - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting vertical total %d, backporch %d\n",
			 mode->crtc_vtotal, bp);

	/* Set vertical display timings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC2_REG,
		     SUN4I_TCON0_BASIC2_V_TOTAL(mode->crtc_vtotal * 2) |
		     SUN4I_TCON0_BASIC2_V_BACKPORCH(bp));

	/* Set Hsync and Vsync length */
	hsync = mode->crtc_hsync_end - mode->crtc_hsync_start;
	vsync = mode->crtc_vsync_end - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting HSYNC %d, VSYNC %d\n", hsync, vsync);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_BASIC3_REG,
		     SUN4I_TCON0_BASIC3_V_SYNC(vsync) |
		     SUN4I_TCON0_BASIC3_H_SYNC(hsync));

	/* Setup the polarity of the various संकेतs */
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		val |= SUN4I_TCON0_IO_POL_HSYNC_POSITIVE;

	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		val |= SUN4I_TCON0_IO_POL_VSYNC_POSITIVE;

	अगर (info->bus_flags & DRM_BUS_FLAG_DE_LOW)
		val |= SUN4I_TCON0_IO_POL_DE_NEGATIVE;

	अगर (info->bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		val |= SUN4I_TCON0_IO_POL_DCLK_DRIVE_NEGEDGE;

	regmap_update_bits(tcon->regs, SUN4I_TCON0_IO_POL_REG,
			   SUN4I_TCON0_IO_POL_HSYNC_POSITIVE |
			   SUN4I_TCON0_IO_POL_VSYNC_POSITIVE |
			   SUN4I_TCON0_IO_POL_DCLK_DRIVE_NEGEDGE |
			   SUN4I_TCON0_IO_POL_DE_NEGATIVE,
			   val);

	/* Map output pins to channel 0 */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_IOMAP_MASK,
			   SUN4I_TCON_GCTL_IOMAP_TCON0);

	/* Enable the output on the pins */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_TRI_REG, 0);
पूर्ण

अटल व्योम sun4i_tcon1_mode_set(काष्ठा sun4i_tcon *tcon,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक bp, hsync, vsync, vtotal;
	u8 clk_delay;
	u32 val;

	WARN_ON(!tcon->quirks->has_channel_1);

	/* Configure the करोt घड़ी */
	clk_set_rate(tcon->sclk1, mode->crtc_घड़ी * 1000);

	/* Adjust घड़ी delay */
	clk_delay = sun4i_tcon_get_clk_delay(mode, 1);
	regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
			   SUN4I_TCON1_CTL_CLK_DELAY_MASK,
			   SUN4I_TCON1_CTL_CLK_DELAY(clk_delay));

	/* Set पूर्णांकerlaced mode */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		val = SUN4I_TCON1_CTL_INTERLACE_ENABLE;
	अन्यथा
		val = 0;
	regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
			   SUN4I_TCON1_CTL_INTERLACE_ENABLE,
			   val);

	/* Set the input resolution */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC0_REG,
		     SUN4I_TCON1_BASIC0_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC0_Y(mode->crtc_vdisplay));

	/* Set the upscaling resolution */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC1_REG,
		     SUN4I_TCON1_BASIC1_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC1_Y(mode->crtc_vdisplay));

	/* Set the output resolution */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC2_REG,
		     SUN4I_TCON1_BASIC2_X(mode->crtc_hdisplay) |
		     SUN4I_TCON1_BASIC2_Y(mode->crtc_vdisplay));

	/* Set horizontal display timings */
	bp = mode->crtc_htotal - mode->crtc_hsync_start;
	DRM_DEBUG_DRIVER("Setting horizontal total %d, backporch %d\n",
			 mode->htotal, bp);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC3_REG,
		     SUN4I_TCON1_BASIC3_H_TOTAL(mode->crtc_htotal) |
		     SUN4I_TCON1_BASIC3_H_BACKPORCH(bp));

	bp = mode->crtc_vtotal - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting vertical total %d, backporch %d\n",
			 mode->crtc_vtotal, bp);

	/*
	 * The vertical resolution needs to be द्विगुनd in all
	 * हालs. We could use crtc_vtotal and always multiply by two,
	 * but that leads to a rounding error in पूर्णांकerlace when vtotal
	 * is odd.
	 *
	 * This happens with TV's PAL क्रम example, where vtotal will
	 * be 625, crtc_vtotal 312, and thus crtc_vtotal * 2 will be
	 * 624, which apparently confuses the hardware.
	 *
	 * To work around this, we will always use vtotal, and
	 * multiply by two only अगर we're not in पूर्णांकerlace.
	 */
	vtotal = mode->vtotal;
	अगर (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
		vtotal = vtotal * 2;

	/* Set vertical display timings */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC4_REG,
		     SUN4I_TCON1_BASIC4_V_TOTAL(vtotal) |
		     SUN4I_TCON1_BASIC4_V_BACKPORCH(bp));

	/* Set Hsync and Vsync length */
	hsync = mode->crtc_hsync_end - mode->crtc_hsync_start;
	vsync = mode->crtc_vsync_end - mode->crtc_vsync_start;
	DRM_DEBUG_DRIVER("Setting HSYNC %d, VSYNC %d\n", hsync, vsync);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_BASIC5_REG,
		     SUN4I_TCON1_BASIC5_V_SYNC(vsync) |
		     SUN4I_TCON1_BASIC5_H_SYNC(hsync));

	/* Setup the polarity of multiple संकेतs */
	अगर (tcon->quirks->polarity_in_ch0) अणु
		val = 0;

		अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
			val |= SUN4I_TCON0_IO_POL_HSYNC_POSITIVE;

		अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
			val |= SUN4I_TCON0_IO_POL_VSYNC_POSITIVE;

		regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_POL_REG, val);
	पूर्ण अन्यथा अणु
		/* according to venकरोr driver, this bit must be always set */
		val = SUN4I_TCON1_IO_POL_UNKNOWN;

		अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
			val |= SUN4I_TCON1_IO_POL_HSYNC_POSITIVE;

		अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
			val |= SUN4I_TCON1_IO_POL_VSYNC_POSITIVE;

		regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_IO_POL_REG, val);
	पूर्ण

	/* Map output pins to channel 1 */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_IOMAP_MASK,
			   SUN4I_TCON_GCTL_IOMAP_TCON1);
पूर्ण

व्योम sun4i_tcon_mode_set(काष्ठा sun4i_tcon *tcon,
			 स्थिर काष्ठा drm_encoder *encoder,
			 स्थिर काष्ठा drm_display_mode *mode)
अणु
	चयन (encoder->encoder_type) अणु
	हाल DRM_MODE_ENCODER_DSI:
		/* DSI is tied to special हाल of CPU पूर्णांकerface */
		sun4i_tcon0_mode_set_cpu(tcon, encoder, mode);
		अवरोध;
	हाल DRM_MODE_ENCODER_LVDS:
		sun4i_tcon0_mode_set_lvds(tcon, encoder, mode);
		अवरोध;
	हाल DRM_MODE_ENCODER_NONE:
		sun4i_tcon0_mode_set_rgb(tcon, encoder, mode);
		sun4i_tcon_set_mux(tcon, 0, encoder);
		अवरोध;
	हाल DRM_MODE_ENCODER_TVDAC:
	हाल DRM_MODE_ENCODER_TMDS:
		sun4i_tcon1_mode_set(tcon, mode);
		sun4i_tcon_set_mux(tcon, 1, encoder);
		अवरोध;
	शेष:
		DRM_DEBUG_DRIVER("Unknown encoder type, doing nothing...\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sun4i_tcon_mode_set);

अटल व्योम sun4i_tcon_finish_page_flip(काष्ठा drm_device *dev,
					काष्ठा sun4i_crtc *scrtc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (scrtc->event) अणु
		drm_crtc_send_vblank_event(&scrtc->crtc, scrtc->event);
		drm_crtc_vblank_put(&scrtc->crtc);
		scrtc->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

अटल irqवापस_t sun4i_tcon_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा sun4i_tcon *tcon = निजी;
	काष्ठा drm_device *drm = tcon->drm;
	काष्ठा sun4i_crtc *scrtc = tcon->crtc;
	काष्ठा sunxi_engine *engine = scrtc->engine;
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(tcon->regs, SUN4I_TCON_GINT0_REG, &status);

	अगर (!(status & (SUN4I_TCON_GINT0_VBLANK_INT(0) |
			SUN4I_TCON_GINT0_VBLANK_INT(1) |
			SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT)))
		वापस IRQ_NONE;

	drm_crtc_handle_vblank(&scrtc->crtc);
	sun4i_tcon_finish_page_flip(drm, scrtc);

	/* Acknowledge the पूर्णांकerrupt */
	regmap_update_bits(tcon->regs, SUN4I_TCON_GINT0_REG,
			   SUN4I_TCON_GINT0_VBLANK_INT(0) |
			   SUN4I_TCON_GINT0_VBLANK_INT(1) |
			   SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT,
			   0);

	अगर (engine->ops->vblank_quirk)
		engine->ops->vblank_quirk(engine);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_tcon_init_घड़ीs(काष्ठा device *dev,
				  काष्ठा sun4i_tcon *tcon)
अणु
	tcon->clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(tcon->clk)) अणु
		dev_err(dev, "Couldn't get the TCON bus clock\n");
		वापस PTR_ERR(tcon->clk);
	पूर्ण
	clk_prepare_enable(tcon->clk);

	अगर (tcon->quirks->has_channel_0) अणु
		tcon->sclk0 = devm_clk_get(dev, "tcon-ch0");
		अगर (IS_ERR(tcon->sclk0)) अणु
			dev_err(dev, "Couldn't get the TCON channel 0 clock\n");
			वापस PTR_ERR(tcon->sclk0);
		पूर्ण
	पूर्ण
	clk_prepare_enable(tcon->sclk0);

	अगर (tcon->quirks->has_channel_1) अणु
		tcon->sclk1 = devm_clk_get(dev, "tcon-ch1");
		अगर (IS_ERR(tcon->sclk1)) अणु
			dev_err(dev, "Couldn't get the TCON channel 1 clock\n");
			वापस PTR_ERR(tcon->sclk1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sun4i_tcon_मुक्त_घड़ीs(काष्ठा sun4i_tcon *tcon)
अणु
	clk_disable_unprepare(tcon->sclk0);
	clk_disable_unprepare(tcon->clk);
पूर्ण

अटल पूर्णांक sun4i_tcon_init_irq(काष्ठा device *dev,
			       काष्ठा sun4i_tcon *tcon)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, sun4i_tcon_handler, 0,
			       dev_name(dev), tcon);
	अगर (ret) अणु
		dev_err(dev, "Couldn't request the IRQ\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config sun4i_tcon_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x800,
पूर्ण;

अटल पूर्णांक sun4i_tcon_init_regmap(काष्ठा device *dev,
				  काष्ठा sun4i_tcon *tcon)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;
	व्योम __iomem *regs;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	tcon->regs = devm_regmap_init_mmio(dev, regs,
					   &sun4i_tcon_regmap_config);
	अगर (IS_ERR(tcon->regs)) अणु
		dev_err(dev, "Couldn't create the TCON regmap\n");
		वापस PTR_ERR(tcon->regs);
	पूर्ण

	/* Make sure the TCON is disabled and all IRQs are off */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_GCTL_REG, 0);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_GINT0_REG, 0);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON_GINT1_REG, 0);

	/* Disable IO lines and set them to tristate */
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON0_IO_TRI_REG, ~0);
	regmap_ग_लिखो(tcon->regs, SUN4I_TCON1_IO_TRI_REG, ~0);

	वापस 0;
पूर्ण

/*
 * On SoCs with the old display pipeline design (Display Engine 1.0),
 * the TCON is always tied to just one backend. Hence we can traverse
 * the of_graph upwards to find the backend our tcon is connected to,
 * and take its ID as our own.
 *
 * We can either identअगरy backends from their compatible strings, which
 * means मुख्यtaining a large list of them. Or, since the backend is
 * रेजिस्टरed and binded beक्रमe the TCON, we can just go through the
 * list of रेजिस्टरed backends and compare the device node.
 *
 * As the काष्ठाures now store engines instead of backends, here this
 * function in fact searches the corresponding engine, and the ID is
 * requested via the get_id function of the engine.
 */
अटल काष्ठा sunxi_engine *
sun4i_tcon_find_engine_traverse(काष्ठा sun4i_drv *drv,
				काष्ठा device_node *node,
				u32 port_id)
अणु
	काष्ठा device_node *port, *ep, *remote;
	काष्ठा sunxi_engine *engine = ERR_PTR(-EINVAL);
	u32 reg = 0;

	port = of_graph_get_port_by_id(node, port_id);
	अगर (!port)
		वापस ERR_PTR(-EINVAL);

	/*
	 * This only works अगर there is only one path from the TCON
	 * to any display engine. Otherwise the probe order of the
	 * TCONs and display engines is not guaranteed. They may
	 * either bind to the wrong one, or worse, bind to the same
	 * one अगर additional checks are not करोne.
	 *
	 * Bail out अगर there are multiple input connections.
	 */
	अगर (of_get_available_child_count(port) != 1)
		जाओ out_put_port;

	/* Get the first connection without specअगरying an ID */
	ep = of_get_next_available_child(port, शून्य);
	अगर (!ep)
		जाओ out_put_port;

	remote = of_graph_get_remote_port_parent(ep);
	अगर (!remote)
		जाओ out_put_ep;

	/* करोes this node match any रेजिस्टरed engines? */
	list_क्रम_each_entry(engine, &drv->engine_list, list)
		अगर (remote == engine->node)
			जाओ out_put_remote;

	/*
	 * According to device tree binding input ports have even id
	 * number and output ports have odd id. Since component with
	 * more than one input and one output (TCON TOP) निकासs, correct
	 * remote input id has to be calculated by subtracting 1 from
	 * remote output id. If this क्रम some reason can't be करोne, 0
	 * is used as input port id.
	 */
	of_node_put(port);
	port = of_graph_get_remote_port(ep);
	अगर (!of_property_पढ़ो_u32(port, "reg", &reg) && reg > 0)
		reg -= 1;

	/* keep looking through upstream ports */
	engine = sun4i_tcon_find_engine_traverse(drv, remote, reg);

out_put_remote:
	of_node_put(remote);
out_put_ep:
	of_node_put(ep);
out_put_port:
	of_node_put(port);

	वापस engine;
पूर्ण

/*
 * The device tree binding says that the remote endpoपूर्णांक ID of any
 * connection between components, up to and including the TCON, of
 * the display pipeline should be equal to the actual ID of the local
 * component. Thus we can look at any one of the input connections of
 * the TCONs, and use that connection's remote endpoपूर्णांक ID as our own.
 *
 * Since the user of this function alपढ़ोy finds the input port,
 * the port is passed in directly without further checks.
 */
अटल पूर्णांक sun4i_tcon_of_get_id_from_port(काष्ठा device_node *port)
अणु
	काष्ठा device_node *ep;
	पूर्णांक ret = -EINVAL;

	/* try finding an upstream endpoपूर्णांक */
	क्रम_each_available_child_of_node(port, ep) अणु
		काष्ठा device_node *remote;
		u32 reg;

		remote = of_graph_get_remote_endpoपूर्णांक(ep);
		अगर (!remote)
			जारी;

		ret = of_property_पढ़ो_u32(remote, "reg", &reg);
		अगर (ret)
			जारी;

		ret = reg;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Once we know the TCON's id, we can look through the list of
 * engines to find a matching one. We assume all engines have
 * been probed and added to the list.
 */
अटल काष्ठा sunxi_engine *sun4i_tcon_get_engine_by_id(काष्ठा sun4i_drv *drv,
							पूर्णांक id)
अणु
	काष्ठा sunxi_engine *engine;

	list_क्रम_each_entry(engine, &drv->engine_list, list)
		अगर (engine->id == id)
			वापस engine;

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल bool sun4i_tcon_connected_to_tcon_top(काष्ठा device_node *node)
अणु
	काष्ठा device_node *remote;
	bool ret = false;

	remote = of_graph_get_remote_node(node, 0, -1);
	अगर (remote) अणु
		ret = !!(IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
			 of_match_node(sun8i_tcon_top_of_table, remote));
		of_node_put(remote);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_tcon_get_index(काष्ठा sun4i_drv *drv)
अणु
	काष्ठा list_head *pos;
	पूर्णांक size = 0;

	/*
	 * Because TCON is added to the list at the end of the probe
	 * (after this function is called), index of the current TCON
	 * will be same as current TCON list size.
	 */
	list_क्रम_each(pos, &drv->tcon_list)
		++size;

	वापस size;
पूर्ण

/*
 * On SoCs with the old display pipeline design (Display Engine 1.0),
 * we assumed the TCON was always tied to just one backend. However
 * this proved not to be the हाल. On the A31, the TCON can select
 * either backend as its source. On the A20 (and likely on the A10),
 * the backend can choose which TCON to output to.
 *
 * The device tree binding says that the remote endpoपूर्णांक ID of any
 * connection between components, up to and including the TCON, of
 * the display pipeline should be equal to the actual ID of the local
 * component. Thus we should be able to look at any one of the input
 * connections of the TCONs, and use that connection's remote endpoपूर्णांक
 * ID as our own.
 *
 * However  the connections between the backend and TCON were assumed
 * to be always singular, and their endpoit IDs were all incorrectly
 * set to 0. This means क्रम these old device trees, we cannot just look
 * up the remote endpoपूर्णांक ID of a TCON input endpoपूर्णांक. TCON1 would be
 * incorrectly identअगरied as TCON0.
 *
 * This function first checks अगर the TCON node has 2 input endpoपूर्णांकs.
 * If so, then the device tree is a corrected version, and it will use
 * sun4i_tcon_of_get_id() and sun4i_tcon_get_engine_by_id() from above
 * to fetch the ID and engine directly. If not, then it is likely an
 * old device trees, where the endpoपूर्णांक IDs were incorrect, but did not
 * have endpoपूर्णांक connections between the backend and TCON across
 * dअगरferent display pipelines. It will fall back to the old method of
 * traversing the  of_graph to try and find a matching engine by device
 * node.
 *
 * In the हाल of single display pipeline device trees, either method
 * works.
 */
अटल काष्ठा sunxi_engine *sun4i_tcon_find_engine(काष्ठा sun4i_drv *drv,
						   काष्ठा device_node *node)
अणु
	काष्ठा device_node *port;
	काष्ठा sunxi_engine *engine;

	port = of_graph_get_port_by_id(node, 0);
	अगर (!port)
		वापस ERR_PTR(-EINVAL);

	/*
	 * Is this a corrected device tree with cross pipeline
	 * connections between the backend and TCON?
	 */
	अगर (of_get_child_count(port) > 1) अणु
		पूर्णांक id;

		/*
		 * When pipeline has the same number of TCONs and engines which
		 * are represented by frontends/backends (DE1) or mixers (DE2),
		 * we match them by their respective IDs. However, अगर pipeline
		 * contains TCON TOP, chances are that there are either more
		 * TCONs than engines (R40) or TCONs with non-consecutive ids.
		 * (H6). In that हाल it's easier just use TCON index in list
		 * as an id. That means that on R40, any 2 TCONs can be enabled
		 * in DT out of 4 (there are 2 mixers). Due to the design of
		 * TCON TOP, reमुख्यing 2 TCONs can't be connected to anything
		 * anyway.
		 */
		अगर (sun4i_tcon_connected_to_tcon_top(node))
			id = sun4i_tcon_get_index(drv);
		अन्यथा
			id = sun4i_tcon_of_get_id_from_port(port);

		/* Get our engine by matching our ID */
		engine = sun4i_tcon_get_engine_by_id(drv, id);

		of_node_put(port);
		वापस engine;
	पूर्ण

	/* Fallback to old method by traversing input endpoपूर्णांकs */
	of_node_put(port);
	वापस sun4i_tcon_find_engine_traverse(drv, node, 0);
पूर्ण

अटल पूर्णांक sun4i_tcon_bind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sunxi_engine *engine;
	काष्ठा device_node *remote;
	काष्ठा sun4i_tcon *tcon;
	काष्ठा reset_control *edp_rstc;
	bool has_lvds_rst, has_lvds_alt, can_lvds;
	पूर्णांक ret;

	engine = sun4i_tcon_find_engine(drv, dev->of_node);
	अगर (IS_ERR(engine)) अणु
		dev_err(dev, "Couldn't find matching engine\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	tcon = devm_kzalloc(dev, माप(*tcon), GFP_KERNEL);
	अगर (!tcon)
		वापस -ENOMEM;
	dev_set_drvdata(dev, tcon);
	tcon->drm = drm;
	tcon->dev = dev;
	tcon->id = engine->id;
	tcon->quirks = of_device_get_match_data(dev);

	tcon->lcd_rst = devm_reset_control_get(dev, "lcd");
	अगर (IS_ERR(tcon->lcd_rst)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(tcon->lcd_rst);
	पूर्ण

	अगर (tcon->quirks->needs_edp_reset) अणु
		edp_rstc = devm_reset_control_get_shared(dev, "edp");
		अगर (IS_ERR(edp_rstc)) अणु
			dev_err(dev, "Couldn't get edp reset line\n");
			वापस PTR_ERR(edp_rstc);
		पूर्ण

		ret = reset_control_deनिश्चित(edp_rstc);
		अगर (ret) अणु
			dev_err(dev, "Couldn't deassert edp reset line\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Make sure our TCON is reset */
	ret = reset_control_reset(tcon->lcd_rst);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert our reset line\n");
		वापस ret;
	पूर्ण

	अगर (tcon->quirks->supports_lvds) अणु
		/*
		 * This can only be made optional since we've had DT
		 * nodes without the LVDS reset properties.
		 *
		 * If the property is missing, just disable LVDS, and
		 * prपूर्णांक a warning.
		 */
		tcon->lvds_rst = devm_reset_control_get_optional(dev, "lvds");
		अगर (IS_ERR(tcon->lvds_rst)) अणु
			dev_err(dev, "Couldn't get our reset line\n");
			वापस PTR_ERR(tcon->lvds_rst);
		पूर्ण अन्यथा अगर (tcon->lvds_rst) अणु
			has_lvds_rst = true;
			reset_control_reset(tcon->lvds_rst);
		पूर्ण अन्यथा अणु
			has_lvds_rst = false;
		पूर्ण

		/*
		 * This can only be made optional since we've had DT
		 * nodes without the LVDS reset properties.
		 *
		 * If the property is missing, just disable LVDS, and
		 * prपूर्णांक a warning.
		 */
		अगर (tcon->quirks->has_lvds_alt) अणु
			tcon->lvds_pll = devm_clk_get(dev, "lvds-alt");
			अगर (IS_ERR(tcon->lvds_pll)) अणु
				अगर (PTR_ERR(tcon->lvds_pll) == -ENOENT) अणु
					has_lvds_alt = false;
				पूर्ण अन्यथा अणु
					dev_err(dev, "Couldn't get the LVDS PLL\n");
					वापस PTR_ERR(tcon->lvds_pll);
				पूर्ण
			पूर्ण अन्यथा अणु
				has_lvds_alt = true;
			पूर्ण
		पूर्ण

		अगर (!has_lvds_rst ||
		    (tcon->quirks->has_lvds_alt && !has_lvds_alt)) अणु
			dev_warn(dev, "Missing LVDS properties, Please upgrade your DT\n");
			dev_warn(dev, "LVDS output disabled\n");
			can_lvds = false;
		पूर्ण अन्यथा अणु
			can_lvds = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		can_lvds = false;
	पूर्ण

	ret = sun4i_tcon_init_घड़ीs(dev, tcon);
	अगर (ret) अणु
		dev_err(dev, "Couldn't init our TCON clocks\n");
		जाओ err_निश्चित_reset;
	पूर्ण

	ret = sun4i_tcon_init_regmap(dev, tcon);
	अगर (ret) अणु
		dev_err(dev, "Couldn't init our TCON regmap\n");
		जाओ err_मुक्त_घड़ीs;
	पूर्ण

	अगर (tcon->quirks->has_channel_0) अणु
		ret = sun4i_dclk_create(dev, tcon);
		अगर (ret) अणु
			dev_err(dev, "Couldn't create our TCON dot clock\n");
			जाओ err_मुक्त_घड़ीs;
		पूर्ण
	पूर्ण

	ret = sun4i_tcon_init_irq(dev, tcon);
	अगर (ret) अणु
		dev_err(dev, "Couldn't init our TCON interrupts\n");
		जाओ err_मुक्त_करोtघड़ी;
	पूर्ण

	tcon->crtc = sun4i_crtc_init(drm, engine, tcon);
	अगर (IS_ERR(tcon->crtc)) अणु
		dev_err(dev, "Couldn't create our CRTC\n");
		ret = PTR_ERR(tcon->crtc);
		जाओ err_मुक्त_करोtघड़ी;
	पूर्ण

	अगर (tcon->quirks->has_channel_0) अणु
		/*
		 * If we have an LVDS panel connected to the TCON, we should
		 * just probe the LVDS connector. Otherwise, just probe RGB as
		 * we used to.
		 */
		remote = of_graph_get_remote_node(dev->of_node, 1, 0);
		अगर (of_device_is_compatible(remote, "panel-lvds"))
			अगर (can_lvds)
				ret = sun4i_lvds_init(drm, tcon);
			अन्यथा
				ret = -EINVAL;
		अन्यथा
			ret = sun4i_rgb_init(drm, tcon);
		of_node_put(remote);

		अगर (ret < 0)
			जाओ err_मुक्त_करोtघड़ी;
	पूर्ण

	अगर (tcon->quirks->needs_de_be_mux) अणु
		/*
		 * We assume there is no dynamic muxing of backends
		 * and TCONs, so we select the backend with same ID.
		 *
		 * While dynamic selection might be पूर्णांकeresting, since
		 * the CRTC is tied to the TCON, जबतक the layers are
		 * tied to the backends, this means, we will need to
		 * चयन between groups of layers. There might not be
		 * a way to represent this स्थिरraपूर्णांक in DRM.
		 */
		regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
				   SUN4I_TCON0_CTL_SRC_SEL_MASK,
				   tcon->id);
		regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
				   SUN4I_TCON1_CTL_SRC_SEL_MASK,
				   tcon->id);
	पूर्ण

	list_add_tail(&tcon->list, &drv->tcon_list);

	वापस 0;

err_मुक्त_करोtघड़ी:
	अगर (tcon->quirks->has_channel_0)
		sun4i_dclk_मुक्त(tcon);
err_मुक्त_घड़ीs:
	sun4i_tcon_मुक्त_घड़ीs(tcon);
err_निश्चित_reset:
	reset_control_निश्चित(tcon->lcd_rst);
	वापस ret;
पूर्ण

अटल व्योम sun4i_tcon_unbind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा sun4i_tcon *tcon = dev_get_drvdata(dev);

	list_del(&tcon->list);
	अगर (tcon->quirks->has_channel_0)
		sun4i_dclk_मुक्त(tcon);
	sun4i_tcon_मुक्त_घड़ीs(tcon);
पूर्ण

अटल स्थिर काष्ठा component_ops sun4i_tcon_ops = अणु
	.bind	= sun4i_tcon_bind,
	.unbind	= sun4i_tcon_unbind,
पूर्ण;

अटल पूर्णांक sun4i_tcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा sun4i_tcon_quirks *quirks;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	quirks = of_device_get_match_data(&pdev->dev);

	/* panels and bridges are present only on TCONs with channel 0 */
	अगर (quirks->has_channel_0) अणु
		ret = drm_of_find_panel_or_bridge(node, 1, 0, &panel, &bridge);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
	पूर्ण

	वापस component_add(&pdev->dev, &sun4i_tcon_ops);
पूर्ण

अटल पूर्णांक sun4i_tcon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun4i_tcon_ops);

	वापस 0;
पूर्ण

/* platक्रमm specअगरic TCON muxing callbacks */
अटल पूर्णांक sun4i_a10_tcon_set_mux(काष्ठा sun4i_tcon *tcon,
				  स्थिर काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_tcon *tcon0 = sun4i_get_tcon0(encoder->dev);
	u32 shअगरt;

	अगर (!tcon0)
		वापस -EINVAL;

	चयन (encoder->encoder_type) अणु
	हाल DRM_MODE_ENCODER_TMDS:
		/* HDMI */
		shअगरt = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(tcon0->regs, SUN4I_TCON_MUX_CTRL_REG,
			   0x3 << shअगरt, tcon->id << shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक sun5i_a13_tcon_set_mux(काष्ठा sun4i_tcon *tcon,
				  स्थिर काष्ठा drm_encoder *encoder)
अणु
	u32 val;

	अगर (encoder->encoder_type == DRM_MODE_ENCODER_TVDAC)
		val = 1;
	अन्यथा
		val = 0;

	/*
	 * FIXME: Unकरोcumented bits
	 */
	वापस regmap_ग_लिखो(tcon->regs, SUN4I_TCON_MUX_CTRL_REG, val);
पूर्ण

अटल पूर्णांक sun6i_tcon_set_mux(काष्ठा sun4i_tcon *tcon,
			      स्थिर काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_tcon *tcon0 = sun4i_get_tcon0(encoder->dev);
	u32 shअगरt;

	अगर (!tcon0)
		वापस -EINVAL;

	चयन (encoder->encoder_type) अणु
	हाल DRM_MODE_ENCODER_TMDS:
		/* HDMI */
		shअगरt = 8;
		अवरोध;
	शेष:
		/* TODO A31 has MIPI DSI but A31s करोes not */
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(tcon0->regs, SUN4I_TCON_MUX_CTRL_REG,
			   0x3 << shअगरt, tcon->id << shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_r40_tcon_tv_set_mux(काष्ठा sun4i_tcon *tcon,
				     स्थिर काष्ठा drm_encoder *encoder)
अणु
	काष्ठा device_node *port, *remote;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक id, ret;

	/* find TCON TOP platक्रमm device and TCON id */

	port = of_graph_get_port_by_id(tcon->dev->of_node, 0);
	अगर (!port)
		वापस -EINVAL;

	id = sun4i_tcon_of_get_id_from_port(port);
	of_node_put(port);

	remote = of_graph_get_remote_node(tcon->dev->of_node, 0, -1);
	अगर (!remote)
		वापस -EINVAL;

	pdev = of_find_device_by_node(remote);
	of_node_put(remote);
	अगर (!pdev)
		वापस -EINVAL;

	अगर (IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
	    encoder->encoder_type == DRM_MODE_ENCODER_TMDS) अणु
		ret = sun8i_tcon_top_set_hdmi_src(&pdev->dev, id);
		अगर (ret) अणु
			put_device(&pdev->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP)) अणु
		ret = sun8i_tcon_top_de_config(&pdev->dev, tcon->id, id);
		अगर (ret) अणु
			put_device(&pdev->dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun4i_tcon_quirks sun4i_a10_quirks = अणु
	.has_channel_0		= true,
	.has_channel_1		= true,
	.dclk_min_भाग		= 4,
	.set_mux		= sun4i_a10_tcon_set_mux,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun5i_a13_quirks = अणु
	.has_channel_0		= true,
	.has_channel_1		= true,
	.dclk_min_भाग		= 4,
	.set_mux		= sun5i_a13_tcon_set_mux,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun6i_a31_quirks = अणु
	.has_channel_0		= true,
	.has_channel_1		= true,
	.has_lvds_alt		= true,
	.needs_de_be_mux	= true,
	.dclk_min_भाग		= 1,
	.set_mux		= sun6i_tcon_set_mux,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun6i_a31s_quirks = अणु
	.has_channel_0		= true,
	.has_channel_1		= true,
	.needs_de_be_mux	= true,
	.dclk_min_भाग		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun7i_a20_tcon0_quirks = अणु
	.supports_lvds		= true,
	.has_channel_0		= true,
	.has_channel_1		= true,
	.dclk_min_भाग		= 4,
	/* Same display pipeline काष्ठाure as A10 */
	.set_mux		= sun4i_a10_tcon_set_mux,
	.setup_lvds_phy		= sun4i_tcon_setup_lvds_phy,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun7i_a20_quirks = अणु
	.has_channel_0		= true,
	.has_channel_1		= true,
	.dclk_min_भाग		= 4,
	/* Same display pipeline काष्ठाure as A10 */
	.set_mux		= sun4i_a10_tcon_set_mux,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun8i_a33_quirks = अणु
	.has_channel_0		= true,
	.has_lvds_alt		= true,
	.dclk_min_भाग		= 1,
	.setup_lvds_phy		= sun6i_tcon_setup_lvds_phy,
	.supports_lvds		= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun8i_a83t_lcd_quirks = अणु
	.supports_lvds		= true,
	.has_channel_0		= true,
	.dclk_min_भाग		= 1,
	.setup_lvds_phy		= sun6i_tcon_setup_lvds_phy,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun8i_a83t_tv_quirks = अणु
	.has_channel_1		= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun8i_r40_tv_quirks = अणु
	.has_channel_1		= true,
	.polarity_in_ch0	= true,
	.set_mux		= sun8i_r40_tcon_tv_set_mux,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun8i_v3s_quirks = अणु
	.has_channel_0		= true,
	.dclk_min_भाग		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun9i_a80_tcon_lcd_quirks = अणु
	.has_channel_0		= true,
	.needs_edp_reset	= true,
	.dclk_min_भाग		= 1,
पूर्ण;

अटल स्थिर काष्ठा sun4i_tcon_quirks sun9i_a80_tcon_tv_quirks = अणु
	.has_channel_1	= true,
	.needs_edp_reset = true,
पूर्ण;

/* sun4i_drv uses this list to check अगर a device node is a TCON */
स्थिर काष्ठा of_device_id sun4i_tcon_of_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-tcon", .data = &sun4i_a10_quirks पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13-tcon", .data = &sun5i_a13_quirks पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-tcon", .data = &sun6i_a31_quirks पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31s-tcon", .data = &sun6i_a31s_quirks पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-tcon", .data = &sun7i_a20_quirks पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-tcon0", .data = &sun7i_a20_tcon0_quirks पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-tcon1", .data = &sun7i_a20_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-tcon", .data = &sun8i_a33_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-tcon", .data = &sun8i_a33_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-tcon-lcd", .data = &sun8i_a83t_lcd_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-tcon-tv", .data = &sun8i_a83t_tv_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-tcon-tv", .data = &sun8i_r40_tv_quirks पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-tcon", .data = &sun8i_v3s_quirks पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-tcon-lcd", .data = &sun9i_a80_tcon_lcd_quirks पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-tcon-tv", .data = &sun9i_a80_tcon_tv_quirks पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_tcon_of_table);
EXPORT_SYMBOL(sun4i_tcon_of_table);

अटल काष्ठा platक्रमm_driver sun4i_tcon_platक्रमm_driver = अणु
	.probe		= sun4i_tcon_probe,
	.हटाओ		= sun4i_tcon_हटाओ,
	.driver		= अणु
		.name		= "sun4i-tcon",
		.of_match_table	= sun4i_tcon_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_tcon_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 Timing Controller Driver");
MODULE_LICENSE("GPL");
