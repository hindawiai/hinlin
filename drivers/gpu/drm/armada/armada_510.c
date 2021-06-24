<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *
 * Armada 510 (aka Dove) variant support
 */
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <drm/drm_probe_helper.h>
#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_hw.h"

काष्ठा armada510_variant_data अणु
	काष्ठा clk *clks[4];
	काष्ठा clk *sel_clk;
पूर्ण;

अटल पूर्णांक armada510_crtc_init(काष्ठा armada_crtc *dcrtc, काष्ठा device *dev)
अणु
	काष्ठा armada510_variant_data *v;
	काष्ठा clk *clk;
	पूर्णांक idx;

	v = devm_kzalloc(dev, माप(*v), GFP_KERNEL);
	अगर (!v)
		वापस -ENOMEM;

	dcrtc->variant_data = v;

	अगर (dev->of_node) अणु
		काष्ठा property *prop;
		स्थिर अक्षर *s;

		of_property_क्रम_each_string(dev->of_node, "clock-names", prop,
					    s) अणु
			अगर (!म_भेद(s, "ext_ref_clk0"))
				idx = 0;
			अन्यथा अगर (!म_भेद(s, "ext_ref_clk1"))
				idx = 1;
			अन्यथा अगर (!म_भेद(s, "plldivider"))
				idx = 2;
			अन्यथा अगर (!म_भेद(s, "axibus"))
				idx = 3;
			अन्यथा
				जारी;

			clk = devm_clk_get(dev, s);
			अगर (IS_ERR(clk))
				वापस PTR_ERR(clk) == -ENOENT ? -EPROBE_DEFER :
					PTR_ERR(clk);
			v->clks[idx] = clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk = devm_clk_get(dev, "ext_ref_clk1");
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk) == -ENOENT ? -EPROBE_DEFER :
				PTR_ERR(clk);

		v->clks[1] = clk;
	पूर्ण

	/*
	 * Lower the watermark so to eliminate jitter at higher bandwidths.
	 * Disable SRAM पढ़ो रुको state to aव्योम प्रणाली hang with बाह्यal
	 * घड़ी.
	 */
	armada_updatel(CFG_DMA_WM(0x20), CFG_SRAM_WAIT | CFG_DMA_WM_MASK,
		       dcrtc->base + LCD_CFG_RDREG4F);

	/* Initialise SPU रेजिस्टर */
	ग_लिखोl_relaxed(ADV_HWC32ENABLE | ADV_HWC32ARGB | ADV_HWC32BLEND,
		       dcrtc->base + LCD_SPU_ADV_REG);

	वापस 0;
पूर्ण

अटल स्थिर u32 armada510_clk_sels[] = अणु
	SCLK_510_EXTCLK0,
	SCLK_510_EXTCLK1,
	SCLK_510_PLL,
	SCLK_510_AXI,
पूर्ण;

अटल स्थिर काष्ठा armada_घड़ीing_params armada510_घड़ीing = अणु
	/* HDMI requires -0.6%..+0.5% */
	.permillage_min = 994,
	.permillage_max = 1005,
	.settable = BIT(0) | BIT(1),
	.भाग_max = SCLK_510_INT_DIV_MASK,
पूर्ण;

/*
 * Armada510 specअगरic SCLK रेजिस्टर selection.
 * This माला_लो called with sclk = शून्य to test whether the mode is
 * supportable, and again with sclk != शून्य to set the घड़ीs up क्रम
 * that.  The क्रमmer can वापस an error, but the latter is expected
 * not to.
 */
अटल पूर्णांक armada510_crtc_compute_घड़ी(काष्ठा armada_crtc *dcrtc,
	स्थिर काष्ठा drm_display_mode *mode, uपूर्णांक32_t *sclk)
अणु
	काष्ठा armada510_variant_data *v = dcrtc->variant_data;
	अचिन्हित दीर्घ desired_khz = mode->crtc_घड़ी;
	काष्ठा armada_clk_result res;
	पूर्णांक ret, idx;

	idx = armada_crtc_select_घड़ी(dcrtc, &res, &armada510_घड़ीing,
				       v->clks, ARRAY_SIZE(v->clks),
				       desired_khz);
	अगर (idx < 0)
		वापस idx;

	ret = clk_prepare_enable(res.clk);
	अगर (ret)
		वापस ret;

	अगर (sclk) अणु
		clk_set_rate(res.clk, res.desired_clk_hz);

		*sclk = res.भाग | armada510_clk_sels[idx];

		/* We are now using this घड़ी */
		v->sel_clk = res.clk;
		swap(dcrtc->clk, res.clk);
	पूर्ण

	clk_disable_unprepare(res.clk);

	वापस 0;
पूर्ण

अटल व्योम armada510_crtc_disable(काष्ठा armada_crtc *dcrtc)
अणु
	अगर (dcrtc->clk) अणु
		clk_disable_unprepare(dcrtc->clk);
		dcrtc->clk = शून्य;
	पूर्ण
पूर्ण

अटल व्योम armada510_crtc_enable(काष्ठा armada_crtc *dcrtc,
	स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा armada510_variant_data *v = dcrtc->variant_data;

	अगर (!dcrtc->clk && v->sel_clk) अणु
		अगर (!WARN_ON(clk_prepare_enable(v->sel_clk)))
			dcrtc->clk = v->sel_clk;
	पूर्ण
पूर्ण

स्थिर काष्ठा armada_variant armada510_ops = अणु
	.has_spu_adv_reg = true,
	.init = armada510_crtc_init,
	.compute_घड़ी = armada510_crtc_compute_घड़ी,
	.disable = armada510_crtc_disable,
	.enable = armada510_crtc_enable,
पूर्ण;
