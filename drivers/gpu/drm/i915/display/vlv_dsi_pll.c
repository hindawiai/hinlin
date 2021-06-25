<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Shobhit Kumar <shobhit.kumar@पूर्णांकel.com>
 *	Yogesh Mohan Marimuthu <yogesh.mohan.marimuthu@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_sideband.h"

अटल स्थिर u16 lfsr_converts[] = अणु
	426, 469, 234, 373, 442, 221, 110, 311, 411,		/* 62 - 70 */
	461, 486, 243, 377, 188, 350, 175, 343, 427, 213,	/* 71 - 80 */
	106, 53, 282, 397, 454, 227, 113, 56, 284, 142,		/* 81 - 90 */
	71, 35, 273, 136, 324, 418, 465, 488, 500, 506		/* 91 - 100 */
पूर्ण;

/* Get DSI घड़ी from pixel घड़ी */
अटल u32 dsi_clk_from_pclk(u32 pclk, क्रमागत mipi_dsi_pixel_क्रमmat fmt,
			     पूर्णांक lane_count)
अणु
	u32 dsi_clk_khz;
	u32 bpp = mipi_dsi_pixel_क्रमmat_to_bpp(fmt);

	/* DSI data rate = pixel घड़ी * bits per pixel / lane count
	   pixel घड़ी is converted from KHz to Hz */
	dsi_clk_khz = DIV_ROUND_CLOSEST(pclk * bpp, lane_count);

	वापस dsi_clk_khz;
पूर्ण

अटल पूर्णांक dsi_calc_mnp(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा पूर्णांकel_crtc_state *config,
			पूर्णांक target_dsi_clk)
अणु
	अचिन्हित पूर्णांक m_min, m_max, p_min = 2, p_max = 6;
	अचिन्हित पूर्णांक m, n, p;
	अचिन्हित पूर्णांक calc_m, calc_p;
	पूर्णांक delta, ref_clk;

	/* target_dsi_clk is expected in kHz */
	अगर (target_dsi_clk < 300000 || target_dsi_clk > 1150000) अणु
		drm_err(&dev_priv->drm, "DSI CLK Out of Range\n");
		वापस -ECHRNG;
	पूर्ण

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		ref_clk = 100000;
		n = 4;
		m_min = 70;
		m_max = 96;
	पूर्ण अन्यथा अणु
		ref_clk = 25000;
		n = 1;
		m_min = 62;
		m_max = 92;
	पूर्ण

	calc_p = p_min;
	calc_m = m_min;
	delta = असल(target_dsi_clk - (m_min * ref_clk) / (p_min * n));

	क्रम (m = m_min; m <= m_max && delta; m++) अणु
		क्रम (p = p_min; p <= p_max && delta; p++) अणु
			/*
			 * Find the optimal m and p भागisors with minimal delta
			 * +/- the required घड़ी
			 */
			पूर्णांक calc_dsi_clk = (m * ref_clk) / (p * n);
			पूर्णांक d = असल(target_dsi_clk - calc_dsi_clk);
			अगर (d < delta) अणु
				delta = d;
				calc_m = m;
				calc_p = p;
			पूर्ण
		पूर्ण
	पूर्ण

	/* रेजिस्टर has log2(N1), this works fine क्रम घातers of two */
	config->dsi_pll.ctrl = 1 << (DSI_PLL_P1_POST_DIV_SHIFT + calc_p - 2);
	config->dsi_pll.भाग =
		(ffs(n) - 1) << DSI_PLL_N1_DIV_SHIFT |
		(u32)lfsr_converts[calc_m - 62] << DSI_PLL_M1_DIV_SHIFT;

	वापस 0;
पूर्ण

/*
 * XXX: The muxing and gating is hard coded क्रम now. Need to add support क्रम
 * sharing PLLs with two DSI outमाला_दो.
 */
पूर्णांक vlv_dsi_pll_compute(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	पूर्णांक ret;
	u32 dsi_clk;

	dsi_clk = dsi_clk_from_pclk(पूर्णांकel_dsi->pclk, पूर्णांकel_dsi->pixel_क्रमmat,
				    पूर्णांकel_dsi->lane_count);

	ret = dsi_calc_mnp(dev_priv, config, dsi_clk);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm, "dsi_calc_mnp failed\n");
		वापस ret;
	पूर्ण

	अगर (पूर्णांकel_dsi->ports & (1 << PORT_A))
		config->dsi_pll.ctrl |= DSI_PLL_CLK_GATE_DSI0_DSIPLL;

	अगर (पूर्णांकel_dsi->ports & (1 << PORT_C))
		config->dsi_pll.ctrl |= DSI_PLL_CLK_GATE_DSI1_DSIPLL;

	config->dsi_pll.ctrl |= DSI_PLL_VCO_EN;

	drm_dbg_kms(&dev_priv->drm, "dsi pll div %08x, ctrl %08x\n",
		    config->dsi_pll.भाग, config->dsi_pll.ctrl);

	वापस 0;
पूर्ण

व्योम vlv_dsi_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	drm_dbg_kms(&dev_priv->drm, "\n");

	vlv_cck_get(dev_priv);

	vlv_cck_ग_लिखो(dev_priv, CCK_REG_DSI_PLL_CONTROL, 0);
	vlv_cck_ग_लिखो(dev_priv, CCK_REG_DSI_PLL_DIVIDER, config->dsi_pll.भाग);
	vlv_cck_ग_लिखो(dev_priv, CCK_REG_DSI_PLL_CONTROL,
		      config->dsi_pll.ctrl & ~DSI_PLL_VCO_EN);

	/* रुको at least 0.5 us after ungating beक्रमe enabling VCO,
	 * allow hrसमयr subप्रणाली optimization by relaxing timing
	 */
	usleep_range(10, 50);

	vlv_cck_ग_लिखो(dev_priv, CCK_REG_DSI_PLL_CONTROL, config->dsi_pll.ctrl);

	अगर (रुको_क्रम(vlv_cck_पढ़ो(dev_priv, CCK_REG_DSI_PLL_CONTROL) &
						DSI_PLL_LOCK, 20)) अणु

		vlv_cck_put(dev_priv);
		drm_err(&dev_priv->drm, "DSI PLL lock failed\n");
		वापस;
	पूर्ण
	vlv_cck_put(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "DSI PLL locked\n");
पूर्ण

व्योम vlv_dsi_pll_disable(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 पंचांगp;

	drm_dbg_kms(&dev_priv->drm, "\n");

	vlv_cck_get(dev_priv);

	पंचांगp = vlv_cck_पढ़ो(dev_priv, CCK_REG_DSI_PLL_CONTROL);
	पंचांगp &= ~DSI_PLL_VCO_EN;
	पंचांगp |= DSI_PLL_LDO_GATE;
	vlv_cck_ग_लिखो(dev_priv, CCK_REG_DSI_PLL_CONTROL, पंचांगp);

	vlv_cck_put(dev_priv);
पूर्ण

bool bxt_dsi_pll_is_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	bool enabled;
	u32 val;
	u32 mask;

	mask = BXT_DSI_PLL_DO_ENABLE | BXT_DSI_PLL_LOCKED;
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DSI_PLL_ENABLE);
	enabled = (val & mask) == mask;

	अगर (!enabled)
		वापस false;

	/*
	 * Dividers must be programmed with valid values. As per BSEPC, क्रम
	 * GEMINLAKE only PORT A भागider values are checked जबतक क्रम BXT
	 * both भागider values are validated. Check this here क्रम
	 * paranoia, since BIOS is known to misconfigure PLLs in this way at
	 * बार, and since accessing DSI रेजिस्टरs with invalid भागiders
	 * causes a प्रणाली hang.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DSI_PLL_CTL);
	अगर (IS_GEMINILAKE(dev_priv)) अणु
		अगर (!(val & BXT_DSIA_16X_MASK)) अणु
			drm_dbg(&dev_priv->drm,
				"Invalid PLL divider (%08x)\n", val);
			enabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(val & BXT_DSIA_16X_MASK) || !(val & BXT_DSIC_16X_MASK)) अणु
			drm_dbg(&dev_priv->drm,
				"Invalid PLL divider (%08x)\n", val);
			enabled = false;
		पूर्ण
	पूर्ण

	वापस enabled;
पूर्ण

व्योम bxt_dsi_pll_disable(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "\n");

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DSI_PLL_ENABLE);
	val &= ~BXT_DSI_PLL_DO_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DSI_PLL_ENABLE, val);

	/*
	 * PLL lock should deनिश्चित within 200us.
	 * Wait up to 1ms beक्रमe timing out.
	 */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, BXT_DSI_PLL_ENABLE,
				    BXT_DSI_PLL_LOCKED, 1))
		drm_err(&dev_priv->drm,
			"Timeout waiting for PLL lock deassertion\n");
पूर्ण

u32 vlv_dsi_get_pclk(काष्ठा पूर्णांकel_encoder *encoder,
		     काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);
	u32 dsi_घड़ी, pclk;
	u32 pll_ctl, pll_भाग;
	u32 m = 0, p = 0, n;
	पूर्णांक refclk = IS_CHERRYVIEW(dev_priv) ? 100000 : 25000;
	पूर्णांक i;

	drm_dbg_kms(&dev_priv->drm, "\n");

	vlv_cck_get(dev_priv);
	pll_ctl = vlv_cck_पढ़ो(dev_priv, CCK_REG_DSI_PLL_CONTROL);
	pll_भाग = vlv_cck_पढ़ो(dev_priv, CCK_REG_DSI_PLL_DIVIDER);
	vlv_cck_put(dev_priv);

	config->dsi_pll.ctrl = pll_ctl & ~DSI_PLL_LOCK;
	config->dsi_pll.भाग = pll_भाग;

	/* mask out other bits and extract the P1 भागisor */
	pll_ctl &= DSI_PLL_P1_POST_DIV_MASK;
	pll_ctl = pll_ctl >> (DSI_PLL_P1_POST_DIV_SHIFT - 2);

	/* N1 भागisor */
	n = (pll_भाग & DSI_PLL_N1_DIV_MASK) >> DSI_PLL_N1_DIV_SHIFT;
	n = 1 << n; /* रेजिस्टर has log2(N1) */

	/* mask out the other bits and extract the M1 भागisor */
	pll_भाग &= DSI_PLL_M1_DIV_MASK;
	pll_भाग = pll_भाग >> DSI_PLL_M1_DIV_SHIFT;

	जबतक (pll_ctl) अणु
		pll_ctl = pll_ctl >> 1;
		p++;
	पूर्ण
	p--;

	अगर (!p) अणु
		drm_err(&dev_priv->drm, "wrong P1 divisor\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(lfsr_converts); i++) अणु
		अगर (lfsr_converts[i] == pll_भाग)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(lfsr_converts)) अणु
		drm_err(&dev_priv->drm, "wrong m_seed programmed\n");
		वापस 0;
	पूर्ण

	m = i + 62;

	dsi_घड़ी = (m * refclk) / (p * n);

	pclk = DIV_ROUND_CLOSEST(dsi_घड़ी * पूर्णांकel_dsi->lane_count, bpp);

	वापस pclk;
पूर्ण

u32 bxt_dsi_get_pclk(काष्ठा पूर्णांकel_encoder *encoder,
		     काष्ठा पूर्णांकel_crtc_state *config)
अणु
	u32 pclk;
	u32 dsi_clk;
	u32 dsi_ratio;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);

	config->dsi_pll.ctrl = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DSI_PLL_CTL);

	dsi_ratio = config->dsi_pll.ctrl & BXT_DSI_PLL_RATIO_MASK;

	dsi_clk = (dsi_ratio * BXT_REF_CLOCK_KHZ) / 2;

	pclk = DIV_ROUND_CLOSEST(dsi_clk * पूर्णांकel_dsi->lane_count, bpp);

	drm_dbg(&dev_priv->drm, "Calculated pclk=%u\n", pclk);
	वापस pclk;
पूर्ण

व्योम vlv_dsi_reset_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत port port)
अणु
	u32 temp;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	temp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
	temp &= ~ESCAPE_CLOCK_DIVIDER_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port),
		       temp | पूर्णांकel_dsi->escape_clk_भाग << ESCAPE_CLOCK_DIVIDER_SHIFT);
पूर्ण

अटल व्योम glk_dsi_program_esc_घड़ी(काष्ठा drm_device *dev,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 dsi_rate = 0;
	u32 pll_ratio = 0;
	u32 ddr_clk = 0;
	u32 भाग1_value = 0;
	u32 भाग2_value = 0;
	u32 txesc1_भाग = 0;
	u32 txesc2_भाग = 0;

	pll_ratio = config->dsi_pll.ctrl & BXT_DSI_PLL_RATIO_MASK;

	dsi_rate = (BXT_REF_CLOCK_KHZ * pll_ratio) / 2;

	ddr_clk = dsi_rate / 2;

	/* Variable भागider value */
	भाग1_value = DIV_ROUND_CLOSEST(ddr_clk, 20000);

	/* Calculate TXESC1 भागider */
	अगर (भाग1_value <= 10)
		txesc1_भाग = भाग1_value;
	अन्यथा अगर ((भाग1_value > 10) && (भाग1_value <= 20))
		txesc1_भाग = DIV_ROUND_UP(भाग1_value, 2);
	अन्यथा अगर ((भाग1_value > 20) && (भाग1_value <= 30))
		txesc1_भाग = DIV_ROUND_UP(भाग1_value, 4);
	अन्यथा अगर ((भाग1_value > 30) && (भाग1_value <= 40))
		txesc1_भाग = DIV_ROUND_UP(भाग1_value, 6);
	अन्यथा अगर ((भाग1_value > 40) && (भाग1_value <= 50))
		txesc1_भाग = DIV_ROUND_UP(भाग1_value, 8);
	अन्यथा
		txesc1_भाग = 10;

	/* Calculate TXESC2 भागider */
	भाग2_value = DIV_ROUND_UP(भाग1_value, txesc1_भाग);

	अगर (भाग2_value < 10)
		txesc2_भाग = भाग2_value;
	अन्यथा
		txesc2_भाग = 10;

	पूर्णांकel_de_ग_लिखो(dev_priv, MIPIO_TXESC_CLK_DIV1,
		       (1 << (txesc1_भाग - 1)) & GLK_TX_ESC_CLK_DIV1_MASK);
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPIO_TXESC_CLK_DIV2,
		       (1 << (txesc2_भाग - 1)) & GLK_TX_ESC_CLK_DIV2_MASK);
पूर्ण

/* Program BXT Mipi घड़ीs and भागiders */
अटल व्योम bxt_dsi_program_घड़ीs(काष्ठा drm_device *dev, क्रमागत port port,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 पंचांगp;
	u32 dsi_rate = 0;
	u32 pll_ratio = 0;
	u32 rx_भाग;
	u32 tx_भाग;
	u32 rx_भाग_upper;
	u32 rx_भाग_lower;
	u32 mipi_8by3_भागider;

	/* Clear old configurations */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_MIPI_CLOCK_CTL);
	पंचांगp &= ~(BXT_MIPI_TX_ESCLK_FIXDIV_MASK(port));
	पंचांगp &= ~(BXT_MIPI_RX_ESCLK_UPPER_FIXDIV_MASK(port));
	पंचांगp &= ~(BXT_MIPI_8X_BY3_DIVIDER_MASK(port));
	पंचांगp &= ~(BXT_MIPI_RX_ESCLK_LOWER_FIXDIV_MASK(port));

	/* Get the current DSI rate(actual) */
	pll_ratio = config->dsi_pll.ctrl & BXT_DSI_PLL_RATIO_MASK;
	dsi_rate = (BXT_REF_CLOCK_KHZ * pll_ratio) / 2;

	/*
	 * tx घड़ी should be <= 20MHz and the भाग value must be
	 * subtracted by 1 as per bspec
	 */
	tx_भाग = DIV_ROUND_UP(dsi_rate, 20000) - 1;
	/*
	 * rx घड़ी should be <= 150MHz and the भाग value must be
	 * subtracted by 1 as per bspec
	 */
	rx_भाग = DIV_ROUND_UP(dsi_rate, 150000) - 1;

	/*
	 * rx भागider value needs to be updated in the
	 * two dअगरfernt bit fields in the रेजिस्टर hence splitting the
	 * rx भागider value accordingly
	 */
	rx_भाग_lower = rx_भाग & RX_DIVIDER_BIT_1_2;
	rx_भाग_upper = (rx_भाग & RX_DIVIDER_BIT_3_4) >> 2;

	mipi_8by3_भागider = 0x2;

	पंचांगp |= BXT_MIPI_8X_BY3_DIVIDER(port, mipi_8by3_भागider);
	पंचांगp |= BXT_MIPI_TX_ESCLK_DIVIDER(port, tx_भाग);
	पंचांगp |= BXT_MIPI_RX_ESCLK_LOWER_DIVIDER(port, rx_भाग_lower);
	पंचांगp |= BXT_MIPI_RX_ESCLK_UPPER_DIVIDER(port, rx_भाग_upper);

	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_CLOCK_CTL, पंचांगp);
पूर्ण

पूर्णांक bxt_dsi_pll_compute(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u8 dsi_ratio, dsi_ratio_min, dsi_ratio_max;
	u32 dsi_clk;

	dsi_clk = dsi_clk_from_pclk(पूर्णांकel_dsi->pclk, पूर्णांकel_dsi->pixel_क्रमmat,
				    पूर्णांकel_dsi->lane_count);

	/*
	 * From घड़ी diagram, to get PLL ratio भागider, भागide द्विगुन of DSI
	 * link rate (i.e., 2*8x=16x frequency value) by ref घड़ी. Make sure to
	 * round 'up' the result
	 */
	dsi_ratio = DIV_ROUND_UP(dsi_clk * 2, BXT_REF_CLOCK_KHZ);

	अगर (IS_BROXTON(dev_priv)) अणु
		dsi_ratio_min = BXT_DSI_PLL_RATIO_MIN;
		dsi_ratio_max = BXT_DSI_PLL_RATIO_MAX;
	पूर्ण अन्यथा अणु
		dsi_ratio_min = GLK_DSI_PLL_RATIO_MIN;
		dsi_ratio_max = GLK_DSI_PLL_RATIO_MAX;
	पूर्ण

	अगर (dsi_ratio < dsi_ratio_min || dsi_ratio > dsi_ratio_max) अणु
		drm_err(&dev_priv->drm,
			"Can't get a suitable ratio from DSI PLL ratios\n");
		वापस -ECHRNG;
	पूर्ण अन्यथा
		drm_dbg_kms(&dev_priv->drm, "DSI PLL calculation is Done!!\n");

	/*
	 * Program DSI ratio and Select MIPIC and MIPIA PLL output as 8x
	 * Spec says both have to be programmed, even अगर one is not getting
	 * used. Configure MIPI_CLOCK_CTL भागiders in modeset
	 */
	config->dsi_pll.ctrl = dsi_ratio | BXT_DSIA_16X_BY2 | BXT_DSIC_16X_BY2;

	/* As per recommendation from hardware team,
	 * Prog PVD ratio =1 अगर dsi ratio <= 50
	 */
	अगर (IS_BROXTON(dev_priv) && dsi_ratio <= 50)
		config->dsi_pll.ctrl |= BXT_DSI_PLL_PVD_RATIO_1;

	वापस 0;
पूर्ण

व्योम bxt_dsi_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "\n");

	/* Configure PLL vales */
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DSI_PLL_CTL, config->dsi_pll.ctrl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BXT_DSI_PLL_CTL);

	/* Program TX, RX, Dphy घड़ीs */
	अगर (IS_BROXTON(dev_priv)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports)
			bxt_dsi_program_घड़ीs(encoder->base.dev, port, config);
	पूर्ण अन्यथा अणु
		glk_dsi_program_esc_घड़ी(encoder->base.dev, config);
	पूर्ण

	/* Enable DSI PLL */
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DSI_PLL_ENABLE);
	val |= BXT_DSI_PLL_DO_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DSI_PLL_ENABLE, val);

	/* Timeout and fail अगर PLL not locked */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, BXT_DSI_PLL_ENABLE,
				  BXT_DSI_PLL_LOCKED, 1)) अणु
		drm_err(&dev_priv->drm,
			"Timed out waiting for DSI PLL to lock\n");
		वापस;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "DSI PLL locked\n");
पूर्ण

व्योम bxt_dsi_reset_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत port port)
अणु
	u32 पंचांगp;
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	/* Clear old configurations */
	अगर (IS_BROXTON(dev_priv)) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_MIPI_CLOCK_CTL);
		पंचांगp &= ~(BXT_MIPI_TX_ESCLK_FIXDIV_MASK(port));
		पंचांगp &= ~(BXT_MIPI_RX_ESCLK_UPPER_FIXDIV_MASK(port));
		पंचांगp &= ~(BXT_MIPI_8X_BY3_DIVIDER_MASK(port));
		पंचांगp &= ~(BXT_MIPI_RX_ESCLK_LOWER_FIXDIV_MASK(port));
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_CLOCK_CTL, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPIO_TXESC_CLK_DIV1);
		पंचांगp &= ~GLK_TX_ESC_CLK_DIV1_MASK;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPIO_TXESC_CLK_DIV1, पंचांगp);

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPIO_TXESC_CLK_DIV2);
		पंचांगp &= ~GLK_TX_ESC_CLK_DIV2_MASK;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPIO_TXESC_CLK_DIV2, पंचांगp);
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_EOT_DISABLE(port), CLOCKSTOP);
पूर्ण
