<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "mtk_disp_drv.h"
#समावेश "mtk_dpi_regs.h"
#समावेश "mtk_drm_ddp_comp.h"

क्रमागत mtk_dpi_out_bit_num अणु
	MTK_DPI_OUT_BIT_NUM_8BITS,
	MTK_DPI_OUT_BIT_NUM_10BITS,
	MTK_DPI_OUT_BIT_NUM_12BITS,
	MTK_DPI_OUT_BIT_NUM_16BITS
पूर्ण;

क्रमागत mtk_dpi_out_yc_map अणु
	MTK_DPI_OUT_YC_MAP_RGB,
	MTK_DPI_OUT_YC_MAP_CYCY,
	MTK_DPI_OUT_YC_MAP_YCYC,
	MTK_DPI_OUT_YC_MAP_CY,
	MTK_DPI_OUT_YC_MAP_YC
पूर्ण;

क्रमागत mtk_dpi_out_channel_swap अणु
	MTK_DPI_OUT_CHANNEL_SWAP_RGB,
	MTK_DPI_OUT_CHANNEL_SWAP_GBR,
	MTK_DPI_OUT_CHANNEL_SWAP_BRG,
	MTK_DPI_OUT_CHANNEL_SWAP_RBG,
	MTK_DPI_OUT_CHANNEL_SWAP_GRB,
	MTK_DPI_OUT_CHANNEL_SWAP_BGR
पूर्ण;

क्रमागत mtk_dpi_out_color_क्रमmat अणु
	MTK_DPI_COLOR_FORMAT_RGB,
	MTK_DPI_COLOR_FORMAT_RGB_FULL,
	MTK_DPI_COLOR_FORMAT_YCBCR_444,
	MTK_DPI_COLOR_FORMAT_YCBCR_422,
	MTK_DPI_COLOR_FORMAT_XV_YCC,
	MTK_DPI_COLOR_FORMAT_YCBCR_444_FULL,
	MTK_DPI_COLOR_FORMAT_YCBCR_422_FULL
पूर्ण;

काष्ठा mtk_dpi अणु
	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_connector *connector;
	व्योम __iomem *regs;
	काष्ठा device *dev;
	काष्ठा clk *engine_clk;
	काष्ठा clk *pixel_clk;
	काष्ठा clk *tvd_clk;
	पूर्णांक irq;
	काष्ठा drm_display_mode mode;
	स्थिर काष्ठा mtk_dpi_conf *conf;
	क्रमागत mtk_dpi_out_color_क्रमmat color_क्रमmat;
	क्रमागत mtk_dpi_out_yc_map yc_map;
	क्रमागत mtk_dpi_out_bit_num bit_num;
	क्रमागत mtk_dpi_out_channel_swap channel_swap;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_gpio;
	काष्ठा pinctrl_state *pins_dpi;
	पूर्णांक refcount;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_dpi *bridge_to_dpi(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा mtk_dpi, bridge);
पूर्ण

क्रमागत mtk_dpi_polarity अणु
	MTK_DPI_POLARITY_RISING,
	MTK_DPI_POLARITY_FALLING,
पूर्ण;

काष्ठा mtk_dpi_polarities अणु
	क्रमागत mtk_dpi_polarity de_pol;
	क्रमागत mtk_dpi_polarity ck_pol;
	क्रमागत mtk_dpi_polarity hsync_pol;
	क्रमागत mtk_dpi_polarity vsync_pol;
पूर्ण;

काष्ठा mtk_dpi_sync_param अणु
	u32 sync_width;
	u32 front_porch;
	u32 back_porch;
	bool shअगरt_half_line;
पूर्ण;

काष्ठा mtk_dpi_yc_limit अणु
	u16 y_top;
	u16 y_bottom;
	u16 c_top;
	u16 c_bottom;
पूर्ण;

काष्ठा mtk_dpi_conf अणु
	अचिन्हित पूर्णांक (*cal_factor)(पूर्णांक घड़ी);
	u32 reg_h_fre_con;
	u32 max_घड़ी_khz;
	bool edge_sel_en;
पूर्ण;

अटल व्योम mtk_dpi_mask(काष्ठा mtk_dpi *dpi, u32 offset, u32 val, u32 mask)
अणु
	u32 पंचांगp = पढ़ोl(dpi->regs + offset) & ~mask;

	पंचांगp |= (val & mask);
	ग_लिखोl(पंचांगp, dpi->regs + offset);
पूर्ण

अटल व्योम mtk_dpi_sw_reset(काष्ठा mtk_dpi *dpi, bool reset)
अणु
	mtk_dpi_mask(dpi, DPI_RET, reset ? RST : 0, RST);
पूर्ण

अटल व्योम mtk_dpi_enable(काष्ठा mtk_dpi *dpi)
अणु
	mtk_dpi_mask(dpi, DPI_EN, EN, EN);
पूर्ण

अटल व्योम mtk_dpi_disable(काष्ठा mtk_dpi *dpi)
अणु
	mtk_dpi_mask(dpi, DPI_EN, 0, EN);
पूर्ण

अटल व्योम mtk_dpi_config_hsync(काष्ठा mtk_dpi *dpi,
				 काष्ठा mtk_dpi_sync_param *sync)
अणु
	mtk_dpi_mask(dpi, DPI_TGEN_HWIDTH,
		     sync->sync_width << HPW, HPW_MASK);
	mtk_dpi_mask(dpi, DPI_TGEN_HPORCH,
		     sync->back_porch << HBP, HBP_MASK);
	mtk_dpi_mask(dpi, DPI_TGEN_HPORCH, sync->front_porch << HFP,
		     HFP_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_vsync(काष्ठा mtk_dpi *dpi,
				 काष्ठा mtk_dpi_sync_param *sync,
				 u32 width_addr, u32 porch_addr)
अणु
	mtk_dpi_mask(dpi, width_addr,
		     sync->sync_width << VSYNC_WIDTH_SHIFT,
		     VSYNC_WIDTH_MASK);
	mtk_dpi_mask(dpi, width_addr,
		     sync->shअगरt_half_line << VSYNC_HALF_LINE_SHIFT,
		     VSYNC_HALF_LINE_MASK);
	mtk_dpi_mask(dpi, porch_addr,
		     sync->back_porch << VSYNC_BACK_PORCH_SHIFT,
		     VSYNC_BACK_PORCH_MASK);
	mtk_dpi_mask(dpi, porch_addr,
		     sync->front_porch << VSYNC_FRONT_PORCH_SHIFT,
		     VSYNC_FRONT_PORCH_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_vsync_lodd(काष्ठा mtk_dpi *dpi,
				      काष्ठा mtk_dpi_sync_param *sync)
अणु
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH, DPI_TGEN_VPORCH);
पूर्ण

अटल व्योम mtk_dpi_config_vsync_leven(काष्ठा mtk_dpi *dpi,
				       काष्ठा mtk_dpi_sync_param *sync)
अणु
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_LEVEN,
			     DPI_TGEN_VPORCH_LEVEN);
पूर्ण

अटल व्योम mtk_dpi_config_vsync_rodd(काष्ठा mtk_dpi *dpi,
				      काष्ठा mtk_dpi_sync_param *sync)
अणु
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_RODD,
			     DPI_TGEN_VPORCH_RODD);
पूर्ण

अटल व्योम mtk_dpi_config_vsync_reven(काष्ठा mtk_dpi *dpi,
				       काष्ठा mtk_dpi_sync_param *sync)
अणु
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_REVEN,
			     DPI_TGEN_VPORCH_REVEN);
पूर्ण

अटल व्योम mtk_dpi_config_pol(काष्ठा mtk_dpi *dpi,
			       काष्ठा mtk_dpi_polarities *dpi_pol)
अणु
	अचिन्हित पूर्णांक pol;

	pol = (dpi_pol->ck_pol == MTK_DPI_POLARITY_RISING ? 0 : CK_POL) |
	      (dpi_pol->de_pol == MTK_DPI_POLARITY_RISING ? 0 : DE_POL) |
	      (dpi_pol->hsync_pol == MTK_DPI_POLARITY_RISING ? 0 : HSYNC_POL) |
	      (dpi_pol->vsync_pol == MTK_DPI_POLARITY_RISING ? 0 : VSYNC_POL);
	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, pol,
		     CK_POL | DE_POL | HSYNC_POL | VSYNC_POL);
पूर्ण

अटल व्योम mtk_dpi_config_3d(काष्ठा mtk_dpi *dpi, bool en_3d)
अणु
	mtk_dpi_mask(dpi, DPI_CON, en_3d ? TDFP_EN : 0, TDFP_EN);
पूर्ण

अटल व्योम mtk_dpi_config_पूर्णांकerface(काष्ठा mtk_dpi *dpi, bool पूर्णांकer)
अणु
	mtk_dpi_mask(dpi, DPI_CON, पूर्णांकer ? INTL_EN : 0, INTL_EN);
पूर्ण

अटल व्योम mtk_dpi_config_fb_size(काष्ठा mtk_dpi *dpi, u32 width, u32 height)
अणु
	mtk_dpi_mask(dpi, DPI_SIZE, width << HSIZE, HSIZE_MASK);
	mtk_dpi_mask(dpi, DPI_SIZE, height << VSIZE, VSIZE_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_channel_limit(काष्ठा mtk_dpi *dpi,
					 काष्ठा mtk_dpi_yc_limit *limit)
अणु
	mtk_dpi_mask(dpi, DPI_Y_LIMIT, limit->y_bottom << Y_LIMINT_BOT,
		     Y_LIMINT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_Y_LIMIT, limit->y_top << Y_LIMINT_TOP,
		     Y_LIMINT_TOP_MASK);
	mtk_dpi_mask(dpi, DPI_C_LIMIT, limit->c_bottom << C_LIMIT_BOT,
		     C_LIMIT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_C_LIMIT, limit->c_top << C_LIMIT_TOP,
		     C_LIMIT_TOP_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_bit_num(काष्ठा mtk_dpi *dpi,
				   क्रमागत mtk_dpi_out_bit_num num)
अणु
	u32 val;

	चयन (num) अणु
	हाल MTK_DPI_OUT_BIT_NUM_8BITS:
		val = OUT_BIT_8;
		अवरोध;
	हाल MTK_DPI_OUT_BIT_NUM_10BITS:
		val = OUT_BIT_10;
		अवरोध;
	हाल MTK_DPI_OUT_BIT_NUM_12BITS:
		val = OUT_BIT_12;
		अवरोध;
	हाल MTK_DPI_OUT_BIT_NUM_16BITS:
		val = OUT_BIT_16;
		अवरोध;
	शेष:
		val = OUT_BIT_8;
		अवरोध;
	पूर्ण
	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << OUT_BIT,
		     OUT_BIT_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_yc_map(काष्ठा mtk_dpi *dpi,
				  क्रमागत mtk_dpi_out_yc_map map)
अणु
	u32 val;

	चयन (map) अणु
	हाल MTK_DPI_OUT_YC_MAP_RGB:
		val = YC_MAP_RGB;
		अवरोध;
	हाल MTK_DPI_OUT_YC_MAP_CYCY:
		val = YC_MAP_CYCY;
		अवरोध;
	हाल MTK_DPI_OUT_YC_MAP_YCYC:
		val = YC_MAP_YCYC;
		अवरोध;
	हाल MTK_DPI_OUT_YC_MAP_CY:
		val = YC_MAP_CY;
		अवरोध;
	हाल MTK_DPI_OUT_YC_MAP_YC:
		val = YC_MAP_YC;
		अवरोध;
	शेष:
		val = YC_MAP_RGB;
		अवरोध;
	पूर्ण

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << YC_MAP, YC_MAP_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_channel_swap(काष्ठा mtk_dpi *dpi,
					क्रमागत mtk_dpi_out_channel_swap swap)
अणु
	u32 val;

	चयन (swap) अणु
	हाल MTK_DPI_OUT_CHANNEL_SWAP_RGB:
		val = SWAP_RGB;
		अवरोध;
	हाल MTK_DPI_OUT_CHANNEL_SWAP_GBR:
		val = SWAP_GBR;
		अवरोध;
	हाल MTK_DPI_OUT_CHANNEL_SWAP_BRG:
		val = SWAP_BRG;
		अवरोध;
	हाल MTK_DPI_OUT_CHANNEL_SWAP_RBG:
		val = SWAP_RBG;
		अवरोध;
	हाल MTK_DPI_OUT_CHANNEL_SWAP_GRB:
		val = SWAP_GRB;
		अवरोध;
	हाल MTK_DPI_OUT_CHANNEL_SWAP_BGR:
		val = SWAP_BGR;
		अवरोध;
	शेष:
		val = SWAP_RGB;
		अवरोध;
	पूर्ण

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, val << CH_SWAP, CH_SWAP_MASK);
पूर्ण

अटल व्योम mtk_dpi_config_yuv422_enable(काष्ठा mtk_dpi *dpi, bool enable)
अणु
	mtk_dpi_mask(dpi, DPI_CON, enable ? YUV422_EN : 0, YUV422_EN);
पूर्ण

अटल व्योम mtk_dpi_config_csc_enable(काष्ठा mtk_dpi *dpi, bool enable)
अणु
	mtk_dpi_mask(dpi, DPI_CON, enable ? CSC_ENABLE : 0, CSC_ENABLE);
पूर्ण

अटल व्योम mtk_dpi_config_swap_input(काष्ठा mtk_dpi *dpi, bool enable)
अणु
	mtk_dpi_mask(dpi, DPI_CON, enable ? IN_RB_SWAP : 0, IN_RB_SWAP);
पूर्ण

अटल व्योम mtk_dpi_config_2n_h_fre(काष्ठा mtk_dpi *dpi)
अणु
	mtk_dpi_mask(dpi, dpi->conf->reg_h_fre_con, H_FRE_2N, H_FRE_2N);
पूर्ण

अटल व्योम mtk_dpi_config_disable_edge(काष्ठा mtk_dpi *dpi)
अणु
	अगर (dpi->conf->edge_sel_en)
		mtk_dpi_mask(dpi, dpi->conf->reg_h_fre_con, 0, EDGE_SEL_EN);
पूर्ण

अटल व्योम mtk_dpi_config_color_क्रमmat(काष्ठा mtk_dpi *dpi,
					क्रमागत mtk_dpi_out_color_क्रमmat क्रमmat)
अणु
	अगर ((क्रमmat == MTK_DPI_COLOR_FORMAT_YCBCR_444) ||
	    (क्रमmat == MTK_DPI_COLOR_FORMAT_YCBCR_444_FULL)) अणु
		mtk_dpi_config_yuv422_enable(dpi, false);
		mtk_dpi_config_csc_enable(dpi, true);
		mtk_dpi_config_swap_input(dpi, false);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_BGR);
	पूर्ण अन्यथा अगर ((क्रमmat == MTK_DPI_COLOR_FORMAT_YCBCR_422) ||
		   (क्रमmat == MTK_DPI_COLOR_FORMAT_YCBCR_422_FULL)) अणु
		mtk_dpi_config_yuv422_enable(dpi, true);
		mtk_dpi_config_csc_enable(dpi, true);
		mtk_dpi_config_swap_input(dpi, true);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_RGB);
	पूर्ण अन्यथा अणु
		mtk_dpi_config_yuv422_enable(dpi, false);
		mtk_dpi_config_csc_enable(dpi, false);
		mtk_dpi_config_swap_input(dpi, false);
		mtk_dpi_config_channel_swap(dpi, MTK_DPI_OUT_CHANNEL_SWAP_RGB);
	पूर्ण
पूर्ण

अटल व्योम mtk_dpi_घातer_off(काष्ठा mtk_dpi *dpi)
अणु
	अगर (WARN_ON(dpi->refcount == 0))
		वापस;

	अगर (--dpi->refcount != 0)
		वापस;

	अगर (dpi->pinctrl && dpi->pins_gpio)
		pinctrl_select_state(dpi->pinctrl, dpi->pins_gpio);

	mtk_dpi_disable(dpi);
	clk_disable_unprepare(dpi->pixel_clk);
	clk_disable_unprepare(dpi->engine_clk);
पूर्ण

अटल पूर्णांक mtk_dpi_घातer_on(काष्ठा mtk_dpi *dpi)
अणु
	पूर्णांक ret;

	अगर (++dpi->refcount != 1)
		वापस 0;

	ret = clk_prepare_enable(dpi->engine_clk);
	अगर (ret) अणु
		dev_err(dpi->dev, "Failed to enable engine clock: %d\n", ret);
		जाओ err_refcount;
	पूर्ण

	ret = clk_prepare_enable(dpi->pixel_clk);
	अगर (ret) अणु
		dev_err(dpi->dev, "Failed to enable pixel clock: %d\n", ret);
		जाओ err_pixel;
	पूर्ण

	अगर (dpi->pinctrl && dpi->pins_dpi)
		pinctrl_select_state(dpi->pinctrl, dpi->pins_dpi);

	mtk_dpi_enable(dpi);
	वापस 0;

err_pixel:
	clk_disable_unprepare(dpi->engine_clk);
err_refcount:
	dpi->refcount--;
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_dpi_set_display_mode(काष्ठा mtk_dpi *dpi,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mtk_dpi_yc_limit limit;
	काष्ठा mtk_dpi_polarities dpi_pol;
	काष्ठा mtk_dpi_sync_param hsync;
	काष्ठा mtk_dpi_sync_param vsync_lodd = अणु 0 पूर्ण;
	काष्ठा mtk_dpi_sync_param vsync_leven = अणु 0 पूर्ण;
	काष्ठा mtk_dpi_sync_param vsync_rodd = अणु 0 पूर्ण;
	काष्ठा mtk_dpi_sync_param vsync_reven = अणु 0 पूर्ण;
	काष्ठा videomode vm = अणु 0 पूर्ण;
	अचिन्हित दीर्घ pll_rate;
	अचिन्हित पूर्णांक factor;

	/* let pll_rate can fix the valid range of tvdpll (1G~2GHz) */
	factor = dpi->conf->cal_factor(mode->घड़ी);
	drm_display_mode_to_videomode(mode, &vm);
	pll_rate = vm.pixelघड़ी * factor;

	dev_dbg(dpi->dev, "Want PLL %lu Hz, pixel clock %lu Hz\n",
		pll_rate, vm.pixelघड़ी);

	clk_set_rate(dpi->tvd_clk, pll_rate);
	pll_rate = clk_get_rate(dpi->tvd_clk);

	vm.pixelघड़ी = pll_rate / factor;
	clk_set_rate(dpi->pixel_clk, vm.pixelघड़ी);
	vm.pixelघड़ी = clk_get_rate(dpi->pixel_clk);

	dev_dbg(dpi->dev, "Got  PLL %lu Hz, pixel clock %lu Hz\n",
		pll_rate, vm.pixelघड़ी);

	limit.c_bottom = 0x0010;
	limit.c_top = 0x0FE0;
	limit.y_bottom = 0x0010;
	limit.y_top = 0x0FE0;

	dpi_pol.ck_pol = MTK_DPI_POLARITY_FALLING;
	dpi_pol.de_pol = MTK_DPI_POLARITY_RISING;
	dpi_pol.hsync_pol = vm.flags & DISPLAY_FLAGS_HSYNC_HIGH ?
			    MTK_DPI_POLARITY_FALLING : MTK_DPI_POLARITY_RISING;
	dpi_pol.vsync_pol = vm.flags & DISPLAY_FLAGS_VSYNC_HIGH ?
			    MTK_DPI_POLARITY_FALLING : MTK_DPI_POLARITY_RISING;
	hsync.sync_width = vm.hsync_len;
	hsync.back_porch = vm.hback_porch;
	hsync.front_porch = vm.hfront_porch;
	hsync.shअगरt_half_line = false;
	vsync_lodd.sync_width = vm.vsync_len;
	vsync_lodd.back_porch = vm.vback_porch;
	vsync_lodd.front_porch = vm.vfront_porch;
	vsync_lodd.shअगरt_half_line = false;

	अगर (vm.flags & DISPLAY_FLAGS_INTERLACED &&
	    mode->flags & DRM_MODE_FLAG_3D_MASK) अणु
		vsync_leven = vsync_lodd;
		vsync_rodd = vsync_lodd;
		vsync_reven = vsync_lodd;
		vsync_leven.shअगरt_half_line = true;
		vsync_reven.shअगरt_half_line = true;
	पूर्ण अन्यथा अगर (vm.flags & DISPLAY_FLAGS_INTERLACED &&
		   !(mode->flags & DRM_MODE_FLAG_3D_MASK)) अणु
		vsync_leven = vsync_lodd;
		vsync_leven.shअगरt_half_line = true;
	पूर्ण अन्यथा अगर (!(vm.flags & DISPLAY_FLAGS_INTERLACED) &&
		   mode->flags & DRM_MODE_FLAG_3D_MASK) अणु
		vsync_rodd = vsync_lodd;
	पूर्ण
	mtk_dpi_sw_reset(dpi, true);
	mtk_dpi_config_pol(dpi, &dpi_pol);

	mtk_dpi_config_hsync(dpi, &hsync);
	mtk_dpi_config_vsync_lodd(dpi, &vsync_lodd);
	mtk_dpi_config_vsync_rodd(dpi, &vsync_rodd);
	mtk_dpi_config_vsync_leven(dpi, &vsync_leven);
	mtk_dpi_config_vsync_reven(dpi, &vsync_reven);

	mtk_dpi_config_3d(dpi, !!(mode->flags & DRM_MODE_FLAG_3D_MASK));
	mtk_dpi_config_पूर्णांकerface(dpi, !!(vm.flags &
					 DISPLAY_FLAGS_INTERLACED));
	अगर (vm.flags & DISPLAY_FLAGS_INTERLACED)
		mtk_dpi_config_fb_size(dpi, vm.hactive, vm.vactive >> 1);
	अन्यथा
		mtk_dpi_config_fb_size(dpi, vm.hactive, vm.vactive);

	mtk_dpi_config_channel_limit(dpi, &limit);
	mtk_dpi_config_bit_num(dpi, dpi->bit_num);
	mtk_dpi_config_channel_swap(dpi, dpi->channel_swap);
	mtk_dpi_config_yc_map(dpi, dpi->yc_map);
	mtk_dpi_config_color_क्रमmat(dpi, dpi->color_क्रमmat);
	mtk_dpi_config_2n_h_fre(dpi);
	mtk_dpi_config_disable_edge(dpi);
	mtk_dpi_sw_reset(dpi, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dpi_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा mtk_dpi *dpi = bridge_to_dpi(bridge);

	वापस drm_bridge_attach(bridge->encoder, dpi->next_bridge,
				 &dpi->bridge, flags);
पूर्ण

अटल व्योम mtk_dpi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mtk_dpi *dpi = bridge_to_dpi(bridge);

	drm_mode_copy(&dpi->mode, adjusted_mode);
पूर्ण

अटल व्योम mtk_dpi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mtk_dpi *dpi = bridge_to_dpi(bridge);

	mtk_dpi_घातer_off(dpi);
पूर्ण

अटल व्योम mtk_dpi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mtk_dpi *dpi = bridge_to_dpi(bridge);

	mtk_dpi_घातer_on(dpi);
	mtk_dpi_set_display_mode(dpi, &dpi->mode);
पूर्ण

अटल क्रमागत drm_mode_status
mtk_dpi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mtk_dpi *dpi = bridge_to_dpi(bridge);

	अगर (mode->घड़ी > dpi->conf->max_घड़ी_khz)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs mtk_dpi_bridge_funcs = अणु
	.attach = mtk_dpi_bridge_attach,
	.mode_set = mtk_dpi_bridge_mode_set,
	.mode_valid = mtk_dpi_bridge_mode_valid,
	.disable = mtk_dpi_bridge_disable,
	.enable = mtk_dpi_bridge_enable,
पूर्ण;

व्योम mtk_dpi_start(काष्ठा device *dev)
अणु
	काष्ठा mtk_dpi *dpi = dev_get_drvdata(dev);

	mtk_dpi_घातer_on(dpi);
पूर्ण

व्योम mtk_dpi_stop(काष्ठा device *dev)
अणु
	काष्ठा mtk_dpi *dpi = dev_get_drvdata(dev);

	mtk_dpi_घातer_off(dpi);
पूर्ण

अटल पूर्णांक mtk_dpi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा mtk_dpi *dpi = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	पूर्णांक ret;

	ret = drm_simple_encoder_init(drm_dev, &dpi->encoder,
				      DRM_MODE_ENCODER_TMDS);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize decoder: %d\n", ret);
		वापस ret;
	पूर्ण

	dpi->encoder.possible_crtcs = mtk_drm_find_possible_crtc_by_comp(drm_dev, dpi->dev);

	ret = drm_bridge_attach(&dpi->encoder, &dpi->bridge, शून्य,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret) अणु
		dev_err(dev, "Failed to attach bridge: %d\n", ret);
		जाओ err_cleanup;
	पूर्ण

	dpi->connector = drm_bridge_connector_init(drm_dev, &dpi->encoder);
	अगर (IS_ERR(dpi->connector)) अणु
		dev_err(dev, "Unable to create bridge connector\n");
		ret = PTR_ERR(dpi->connector);
		जाओ err_cleanup;
	पूर्ण
	drm_connector_attach_encoder(dpi->connector, &dpi->encoder);

	dpi->bit_num = MTK_DPI_OUT_BIT_NUM_8BITS;
	dpi->channel_swap = MTK_DPI_OUT_CHANNEL_SWAP_RGB;
	dpi->yc_map = MTK_DPI_OUT_YC_MAP_RGB;
	dpi->color_क्रमmat = MTK_DPI_COLOR_FORMAT_RGB;

	वापस 0;

err_cleanup:
	drm_encoder_cleanup(&dpi->encoder);
	वापस ret;
पूर्ण

अटल व्योम mtk_dpi_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा mtk_dpi *dpi = dev_get_drvdata(dev);

	drm_encoder_cleanup(&dpi->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops mtk_dpi_component_ops = अणु
	.bind = mtk_dpi_bind,
	.unbind = mtk_dpi_unbind,
पूर्ण;

अटल अचिन्हित पूर्णांक mt8173_calculate_factor(पूर्णांक घड़ी)
अणु
	अगर (घड़ी <= 27000)
		वापस 3 << 4;
	अन्यथा अगर (घड़ी <= 84000)
		वापस 3 << 3;
	अन्यथा अगर (घड़ी <= 167000)
		वापस 3 << 2;
	अन्यथा
		वापस 3 << 1;
पूर्ण

अटल अचिन्हित पूर्णांक mt2701_calculate_factor(पूर्णांक घड़ी)
अणु
	अगर (घड़ी <= 64000)
		वापस 4;
	अन्यथा अगर (घड़ी <= 128000)
		वापस 2;
	अन्यथा
		वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक mt8183_calculate_factor(पूर्णांक घड़ी)
अणु
	अगर (घड़ी <= 27000)
		वापस 8;
	अन्यथा अगर (घड़ी <= 167000)
		वापस 4;
	अन्यथा
		वापस 2;
पूर्ण

अटल स्थिर काष्ठा mtk_dpi_conf mt8173_conf = अणु
	.cal_factor = mt8173_calculate_factor,
	.reg_h_fre_con = 0xe0,
	.max_घड़ी_khz = 300000,
पूर्ण;

अटल स्थिर काष्ठा mtk_dpi_conf mt2701_conf = अणु
	.cal_factor = mt2701_calculate_factor,
	.reg_h_fre_con = 0xb0,
	.edge_sel_en = true,
	.max_घड़ी_khz = 150000,
पूर्ण;

अटल स्थिर काष्ठा mtk_dpi_conf mt8183_conf = अणु
	.cal_factor = mt8183_calculate_factor,
	.reg_h_fre_con = 0xe0,
	.max_घड़ी_khz = 100000,
पूर्ण;

अटल स्थिर काष्ठा mtk_dpi_conf mt8192_conf = अणु
	.cal_factor = mt8183_calculate_factor,
	.reg_h_fre_con = 0xe0,
	.max_घड़ी_khz = 150000,
पूर्ण;

अटल पूर्णांक mtk_dpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_dpi *dpi;
	काष्ठा resource *mem;
	पूर्णांक ret;

	dpi = devm_kzalloc(dev, माप(*dpi), GFP_KERNEL);
	अगर (!dpi)
		वापस -ENOMEM;

	dpi->dev = dev;
	dpi->conf = (काष्ठा mtk_dpi_conf *)of_device_get_match_data(dev);

	dpi->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(dpi->pinctrl)) अणु
		dpi->pinctrl = शून्य;
		dev_dbg(&pdev->dev, "Cannot find pinctrl!\n");
	पूर्ण
	अगर (dpi->pinctrl) अणु
		dpi->pins_gpio = pinctrl_lookup_state(dpi->pinctrl, "sleep");
		अगर (IS_ERR(dpi->pins_gpio)) अणु
			dpi->pins_gpio = शून्य;
			dev_dbg(&pdev->dev, "Cannot find pinctrl idle!\n");
		पूर्ण
		अगर (dpi->pins_gpio)
			pinctrl_select_state(dpi->pinctrl, dpi->pins_gpio);

		dpi->pins_dpi = pinctrl_lookup_state(dpi->pinctrl, "default");
		अगर (IS_ERR(dpi->pins_dpi)) अणु
			dpi->pins_dpi = शून्य;
			dev_dbg(&pdev->dev, "Cannot find pinctrl active!\n");
		पूर्ण
	पूर्ण
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dpi->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(dpi->regs)) अणु
		ret = PTR_ERR(dpi->regs);
		dev_err(dev, "Failed to ioremap mem resource: %d\n", ret);
		वापस ret;
	पूर्ण

	dpi->engine_clk = devm_clk_get(dev, "engine");
	अगर (IS_ERR(dpi->engine_clk)) अणु
		ret = PTR_ERR(dpi->engine_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get engine clock: %d\n", ret);

		वापस ret;
	पूर्ण

	dpi->pixel_clk = devm_clk_get(dev, "pixel");
	अगर (IS_ERR(dpi->pixel_clk)) अणु
		ret = PTR_ERR(dpi->pixel_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get pixel clock: %d\n", ret);

		वापस ret;
	पूर्ण

	dpi->tvd_clk = devm_clk_get(dev, "pll");
	अगर (IS_ERR(dpi->tvd_clk)) अणु
		ret = PTR_ERR(dpi->tvd_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get tvdpll clock: %d\n", ret);

		वापस ret;
	पूर्ण

	dpi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dpi->irq <= 0)
		वापस -EINVAL;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0,
					  शून्य, &dpi->next_bridge);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Found bridge node: %pOF\n", dpi->next_bridge->of_node);

	platक्रमm_set_drvdata(pdev, dpi);

	dpi->bridge.funcs = &mtk_dpi_bridge_funcs;
	dpi->bridge.of_node = dev->of_node;
	dpi->bridge.type = DRM_MODE_CONNECTOR_DPI;

	drm_bridge_add(&dpi->bridge);

	ret = component_add(dev, &mtk_dpi_component_ops);
	अगर (ret) अणु
		drm_bridge_हटाओ(&dpi->bridge);
		dev_err(dev, "Failed to add component: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_dpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_dpi *dpi = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &mtk_dpi_component_ops);
	drm_bridge_हटाओ(&dpi->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_dpi_of_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-dpi",
	  .data = &mt2701_conf,
	पूर्ण,
	अणु .compatible = "mediatek,mt8173-dpi",
	  .data = &mt8173_conf,
	पूर्ण,
	अणु .compatible = "mediatek,mt8183-dpi",
	  .data = &mt8183_conf,
	पूर्ण,
	अणु .compatible = "mediatek,mt8192-dpi",
	  .data = &mt8192_conf,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_dpi_of_ids);

काष्ठा platक्रमm_driver mtk_dpi_driver = अणु
	.probe = mtk_dpi_probe,
	.हटाओ = mtk_dpi_हटाओ,
	.driver = अणु
		.name = "mediatek-dpi",
		.of_match_table = mtk_dpi_of_ids,
	पूर्ण,
पूर्ण;
