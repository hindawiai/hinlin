<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rcar_lvds.c  --  R-Car LVDS Encoder
 *
 * Copyright (C) 2013-2018 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "rcar_lvds.h"
#समावेश "rcar_lvds_regs.h"

काष्ठा rcar_lvds;

/* Keep in sync with the LVDCR0.LVMD hardware रेजिस्टर values. */
क्रमागत rcar_lvds_mode अणु
	RCAR_LVDS_MODE_JEIDA = 0,
	RCAR_LVDS_MODE_MIRROR = 1,
	RCAR_LVDS_MODE_VESA = 4,
पूर्ण;

क्रमागत rcar_lvds_link_type अणु
	RCAR_LVDS_SINGLE_LINK = 0,
	RCAR_LVDS_DUAL_LINK_EVEN_ODD_PIXELS = 1,
	RCAR_LVDS_DUAL_LINK_ODD_EVEN_PIXELS = 2,
पूर्ण;

#घोषणा RCAR_LVDS_QUIRK_LANES		BIT(0)	/* LVDS lanes 1 and 3 inverted */
#घोषणा RCAR_LVDS_QUIRK_GEN3_LVEN	BIT(1)	/* LVEN bit needs to be set on R8A77970/R8A7799x */
#घोषणा RCAR_LVDS_QUIRK_PWD		BIT(2)	/* PWD bit available (all of Gen3 but E3) */
#घोषणा RCAR_LVDS_QUIRK_EXT_PLL		BIT(3)	/* Has extended PLL */
#घोषणा RCAR_LVDS_QUIRK_DUAL_LINK	BIT(4)	/* Supports dual-link operation */

काष्ठा rcar_lvds_device_info अणु
	अचिन्हित पूर्णांक gen;
	अचिन्हित पूर्णांक quirks;
	व्योम (*pll_setup)(काष्ठा rcar_lvds *lvds, अचिन्हित पूर्णांक freq);
पूर्ण;

काष्ठा rcar_lvds अणु
	काष्ठा device *dev;
	स्थिर काष्ठा rcar_lvds_device_info *info;

	काष्ठा drm_bridge bridge;

	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_connector connector;
	काष्ठा drm_panel *panel;

	व्योम __iomem *mmio;
	काष्ठा अणु
		काष्ठा clk *mod;		/* CPG module घड़ी */
		काष्ठा clk *extal;		/* External घड़ी */
		काष्ठा clk *करोtclkin[2];	/* External DU घड़ीs */
	पूर्ण घड़ीs;

	काष्ठा drm_bridge *companion;
	क्रमागत rcar_lvds_link_type link_type;
पूर्ण;

#घोषणा bridge_to_rcar_lvds(b) \
	container_of(b, काष्ठा rcar_lvds, bridge)

#घोषणा connector_to_rcar_lvds(c) \
	container_of(c, काष्ठा rcar_lvds, connector)

अटल व्योम rcar_lvds_ग_लिखो(काष्ठा rcar_lvds *lvds, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, lvds->mmio + reg);
पूर्ण

/* -----------------------------------------------------------------------------
 * Connector & Panel
 */

अटल पूर्णांक rcar_lvds_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा rcar_lvds *lvds = connector_to_rcar_lvds(connector);

	वापस drm_panel_get_modes(lvds->panel, connector);
पूर्ण

अटल पूर्णांक rcar_lvds_connector_atomic_check(काष्ठा drm_connector *connector,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_lvds *lvds = connector_to_rcar_lvds(connector);
	स्थिर काष्ठा drm_display_mode *panel_mode;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc_state *crtc_state;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (!conn_state->crtc)
		वापस 0;

	अगर (list_empty(&connector->modes)) अणु
		dev_dbg(lvds->dev, "connector: empty modes list\n");
		वापस -EINVAL;
	पूर्ण

	panel_mode = list_first_entry(&connector->modes,
				      काष्ठा drm_display_mode, head);

	/* We're not allowed to modअगरy the resolution. */
	crtc_state = drm_atomic_get_crtc_state(state, conn_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	अगर (crtc_state->mode.hdisplay != panel_mode->hdisplay ||
	    crtc_state->mode.vdisplay != panel_mode->vdisplay)
		वापस -EINVAL;

	/* The flat panel mode is fixed, just copy it to the adjusted mode. */
	drm_mode_copy(&crtc_state->adjusted_mode, panel_mode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs rcar_lvds_conn_helper_funcs = अणु
	.get_modes = rcar_lvds_connector_get_modes,
	.atomic_check = rcar_lvds_connector_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs rcar_lvds_conn_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

/* -----------------------------------------------------------------------------
 * PLL Setup
 */

अटल व्योम rcar_lvds_pll_setup_gen2(काष्ठा rcar_lvds *lvds, अचिन्हित पूर्णांक freq)
अणु
	u32 val;

	अगर (freq < 39000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_38M;
	अन्यथा अगर (freq < 61000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_60M;
	अन्यथा अगर (freq < 121000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_121M;
	अन्यथा
		val = LVDPLLCR_PLLDLYCNT_150M;

	rcar_lvds_ग_लिखो(lvds, LVDPLLCR, val);
पूर्ण

अटल व्योम rcar_lvds_pll_setup_gen3(काष्ठा rcar_lvds *lvds, अचिन्हित पूर्णांक freq)
अणु
	u32 val;

	अगर (freq < 42000000)
		val = LVDPLLCR_PLLDIVCNT_42M;
	अन्यथा अगर (freq < 85000000)
		val = LVDPLLCR_PLLDIVCNT_85M;
	अन्यथा अगर (freq < 128000000)
		val = LVDPLLCR_PLLDIVCNT_128M;
	अन्यथा
		val = LVDPLLCR_PLLDIVCNT_148M;

	rcar_lvds_ग_लिखो(lvds, LVDPLLCR, val);
पूर्ण

काष्ठा pll_info अणु
	अचिन्हित दीर्घ dअगरf;
	अचिन्हित पूर्णांक pll_m;
	अचिन्हित पूर्णांक pll_n;
	अचिन्हित पूर्णांक pll_e;
	अचिन्हित पूर्णांक भाग;
	u32 clksel;
पूर्ण;

अटल व्योम rcar_lvds_d3_e3_pll_calc(काष्ठा rcar_lvds *lvds, काष्ठा clk *clk,
				     अचिन्हित दीर्घ target, काष्ठा pll_info *pll,
				     u32 clksel, bool करोt_घड़ी_only)
अणु
	अचिन्हित पूर्णांक भाग7 = करोt_घड़ी_only ? 1 : 7;
	अचिन्हित दीर्घ output;
	अचिन्हित दीर्घ fin;
	अचिन्हित पूर्णांक m_min;
	अचिन्हित पूर्णांक m_max;
	अचिन्हित पूर्णांक m;
	पूर्णांक error;

	अगर (!clk)
		वापस;

	/*
	 * The LVDS PLL is made of a pre-भागider and a multiplier (strangely
	 * enough called M and N respectively), followed by a post-भागider E.
	 *
	 *         ,-----.         ,-----.     ,-----.         ,-----.
	 * Fin --> | 1/M | -Fpdf-> | PFD | --> | VCO | -Fvco-> | 1/E | --> Fout
	 *         `-----'     ,-> |     |     `-----'   |     `-----'
	 *                     |   `-----'               |
	 *                     |         ,-----.         |
	 *                     `-------- | 1/N | <-------'
	 *                               `-----'
	 *
	 * The घड़ी output by the PLL is then further भागided by a programmable
	 * भागider DIV to achieve the desired target frequency. Finally, an
	 * optional fixed /7 भागider is used to convert the bit घड़ी to a pixel
	 * घड़ी (as LVDS transmits 7 bits per lane per घड़ी sample).
	 *
	 *          ,-------.     ,-----.     |\
	 * Fout --> | 1/DIV | --> | 1/7 | --> | |
	 *          `-------'  |  `-----'     | | --> करोt घड़ी
	 *                     `------------> | |
	 *                                    |/
	 *
	 * The /7 भागider is optional, it is enabled when the LVDS PLL is used
	 * to drive the LVDS encoder, and disabled when  used to generate a करोt
	 * घड़ी क्रम the DU RGB output, without using the LVDS encoder.
	 *
	 * The PLL allowed input frequency range is 12 MHz to 192 MHz.
	 */

	fin = clk_get_rate(clk);
	अगर (fin < 12000000 || fin > 192000000)
		वापस;

	/*
	 * The comparison frequency range is 12 MHz to 24 MHz, which limits the
	 * allowed values क्रम the pre-भागider M (normal range 1-8).
	 *
	 * Fpfd = Fin / M
	 */
	m_min = max_t(अचिन्हित पूर्णांक, 1, DIV_ROUND_UP(fin, 24000000));
	m_max = min_t(अचिन्हित पूर्णांक, 8, fin / 12000000);

	क्रम (m = m_min; m <= m_max; ++m) अणु
		अचिन्हित दीर्घ fpfd;
		अचिन्हित पूर्णांक n_min;
		अचिन्हित पूर्णांक n_max;
		अचिन्हित पूर्णांक n;

		/*
		 * The VCO operating range is 900 Mhz to 1800 MHz, which limits
		 * the allowed values क्रम the multiplier N (normal range
		 * 60-120).
		 *
		 * Fvco = Fin * N / M
		 */
		fpfd = fin / m;
		n_min = max_t(अचिन्हित पूर्णांक, 60, DIV_ROUND_UP(900000000, fpfd));
		n_max = min_t(अचिन्हित पूर्णांक, 120, 1800000000 / fpfd);

		क्रम (n = n_min; n < n_max; ++n) अणु
			अचिन्हित दीर्घ fvco;
			अचिन्हित पूर्णांक e_min;
			अचिन्हित पूर्णांक e;

			/*
			 * The output frequency is limited to 1039.5 MHz,
			 * limiting again the allowed values क्रम the
			 * post-भागider E (normal value 1, 2 or 4).
			 *
			 * Fout = Fvco / E
			 */
			fvco = fpfd * n;
			e_min = fvco > 1039500000 ? 1 : 0;

			क्रम (e = e_min; e < 3; ++e) अणु
				अचिन्हित दीर्घ fout;
				अचिन्हित दीर्घ dअगरf;
				अचिन्हित पूर्णांक भाग;

				/*
				 * Finally we have a programable भागider after
				 * the PLL, followed by a an optional fixed /7
				 * भागider.
				 */
				fout = fvco / (1 << e) / भाग7;
				भाग = max(1UL, DIV_ROUND_CLOSEST(fout, target));
				dअगरf = असल(fout / भाग - target);

				अगर (dअगरf < pll->dअगरf) अणु
					pll->dअगरf = dअगरf;
					pll->pll_m = m;
					pll->pll_n = n;
					pll->pll_e = e;
					pll->भाग = भाग;
					pll->clksel = clksel;

					अगर (dअगरf == 0)
						जाओ करोne;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	output = fin * pll->pll_n / pll->pll_m / (1 << pll->pll_e)
	       / भाग7 / pll->भाग;
	error = (दीर्घ)(output - target) * 10000 / (दीर्घ)target;

	dev_dbg(lvds->dev,
		"%pC %lu Hz -> Fout %lu Hz (target %lu Hz, error %d.%02u%%), PLL M/N/E/DIV %u/%u/%u/%u\n",
		clk, fin, output, target, error / 100,
		error < 0 ? -error % 100 : error % 100,
		pll->pll_m, pll->pll_n, pll->pll_e, pll->भाग);
पूर्ण

अटल व्योम __rcar_lvds_pll_setup_d3_e3(काष्ठा rcar_lvds *lvds,
					अचिन्हित पूर्णांक freq, bool करोt_घड़ी_only)
अणु
	काष्ठा pll_info pll = अणु .dअगरf = (अचिन्हित दीर्घ)-1 पूर्ण;
	u32 lvdpllcr;

	rcar_lvds_d3_e3_pll_calc(lvds, lvds->घड़ीs.करोtclkin[0], freq, &pll,
				 LVDPLLCR_CKSEL_DU_DOTCLKIN(0), करोt_घड़ी_only);
	rcar_lvds_d3_e3_pll_calc(lvds, lvds->घड़ीs.करोtclkin[1], freq, &pll,
				 LVDPLLCR_CKSEL_DU_DOTCLKIN(1), करोt_घड़ी_only);
	rcar_lvds_d3_e3_pll_calc(lvds, lvds->घड़ीs.extal, freq, &pll,
				 LVDPLLCR_CKSEL_EXTAL, करोt_घड़ी_only);

	lvdpllcr = LVDPLLCR_PLLON | pll.clksel | LVDPLLCR_CLKOUT
		 | LVDPLLCR_PLLN(pll.pll_n - 1) | LVDPLLCR_PLLM(pll.pll_m - 1);

	अगर (pll.pll_e > 0)
		lvdpllcr |= LVDPLLCR_STP_CLKOUTE | LVDPLLCR_OUTCLKSEL
			 |  LVDPLLCR_PLLE(pll.pll_e - 1);

	अगर (करोt_घड़ी_only)
		lvdpllcr |= LVDPLLCR_OCKSEL;

	rcar_lvds_ग_लिखो(lvds, LVDPLLCR, lvdpllcr);

	अगर (pll.भाग > 1)
		/*
		 * The DIVRESET bit is a misnomer, setting it to 1 deनिश्चितs the
		 * भागisor reset.
		 */
		rcar_lvds_ग_लिखो(lvds, LVDDIV, LVDDIV_DIVSEL |
				LVDDIV_DIVRESET | LVDDIV_DIV(pll.भाग - 1));
	अन्यथा
		rcar_lvds_ग_लिखो(lvds, LVDDIV, 0);
पूर्ण

अटल व्योम rcar_lvds_pll_setup_d3_e3(काष्ठा rcar_lvds *lvds, अचिन्हित पूर्णांक freq)
अणु
	__rcar_lvds_pll_setup_d3_e3(lvds, freq, false);
पूर्ण

/* -----------------------------------------------------------------------------
 * Clock - D3/E3 only
 */

पूर्णांक rcar_lvds_clk_enable(काष्ठा drm_bridge *bridge, अचिन्हित दीर्घ freq)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	पूर्णांक ret;

	अगर (WARN_ON(!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)))
		वापस -ENODEV;

	dev_dbg(lvds->dev, "enabling LVDS PLL, freq=%luHz\n", freq);

	ret = clk_prepare_enable(lvds->घड़ीs.mod);
	अगर (ret < 0)
		वापस ret;

	__rcar_lvds_pll_setup_d3_e3(lvds, freq, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_lvds_clk_enable);

व्योम rcar_lvds_clk_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	अगर (WARN_ON(!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)))
		वापस;

	dev_dbg(lvds->dev, "disabling LVDS PLL\n");

	rcar_lvds_ग_लिखो(lvds, LVDPLLCR, 0);

	clk_disable_unprepare(lvds->घड़ीs.mod);
पूर्ण
EXPORT_SYMBOL_GPL(rcar_lvds_clk_disable);

/* -----------------------------------------------------------------------------
 * Bridge
 */

अटल क्रमागत rcar_lvds_mode rcar_lvds_get_lvds_mode(काष्ठा rcar_lvds *lvds,
					स्थिर काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा drm_display_info *info;
	क्रमागत rcar_lvds_mode mode;

	/*
	 * There is no API yet to retrieve LVDS mode from a bridge, only panels
	 * are supported.
	 */
	अगर (!lvds->panel)
		वापस RCAR_LVDS_MODE_JEIDA;

	info = &connector->display_info;
	अगर (!info->num_bus_क्रमmats || !info->bus_क्रमmats) अणु
		dev_warn(lvds->dev,
			 "no LVDS bus format reported, using JEIDA\n");
		वापस RCAR_LVDS_MODE_JEIDA;
	पूर्ण

	चयन (info->bus_क्रमmats[0]) अणु
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		mode = RCAR_LVDS_MODE_JEIDA;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
		mode = RCAR_LVDS_MODE_VESA;
		अवरोध;
	शेष:
		dev_warn(lvds->dev,
			 "unsupported LVDS bus format 0x%04x, using JEIDA\n",
			 info->bus_क्रमmats[0]);
		वापस RCAR_LVDS_MODE_JEIDA;
	पूर्ण

	अगर (info->bus_flags & DRM_BUS_FLAG_DATA_LSB_TO_MSB)
		mode |= RCAR_LVDS_MODE_MIRROR;

	वापस mode;
पूर्ण

अटल व्योम __rcar_lvds_atomic_enable(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_atomic_state *state,
				      काष्ठा drm_crtc *crtc,
				      काष्ठा drm_connector *connector)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	u32 lvdhcr;
	u32 lvdcr0;
	पूर्णांक ret;

	ret = clk_prepare_enable(lvds->घड़ीs.mod);
	अगर (ret < 0)
		वापस;

	/* Enable the companion LVDS encoder in dual-link mode. */
	अगर (lvds->link_type != RCAR_LVDS_SINGLE_LINK && lvds->companion)
		__rcar_lvds_atomic_enable(lvds->companion, state, crtc,
					  connector);

	/*
	 * Hardcode the channels and control संकेतs routing क्रम now.
	 *
	 * HSYNC -> CTRL0
	 * VSYNC -> CTRL1
	 * DISP  -> CTRL2
	 * 0     -> CTRL3
	 */
	rcar_lvds_ग_लिखो(lvds, LVDCTRCR, LVDCTRCR_CTR3SEL_ZERO |
			LVDCTRCR_CTR2SEL_DISP | LVDCTRCR_CTR1SEL_VSYNC |
			LVDCTRCR_CTR0SEL_HSYNC);

	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_LANES)
		lvdhcr = LVDCHCR_CHSEL_CH(0, 0) | LVDCHCR_CHSEL_CH(1, 3)
		       | LVDCHCR_CHSEL_CH(2, 2) | LVDCHCR_CHSEL_CH(3, 1);
	अन्यथा
		lvdhcr = LVDCHCR_CHSEL_CH(0, 0) | LVDCHCR_CHSEL_CH(1, 1)
		       | LVDCHCR_CHSEL_CH(2, 2) | LVDCHCR_CHSEL_CH(3, 3);

	rcar_lvds_ग_लिखो(lvds, LVDCHCR, lvdhcr);

	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_DUAL_LINK) अणु
		u32 lvdstripe = 0;

		अगर (lvds->link_type != RCAR_LVDS_SINGLE_LINK) अणु
			/*
			 * By शेष we generate even pixels from the primary
			 * encoder and odd pixels from the companion encoder.
			 * Swap pixels around अगर the sink requires odd pixels
			 * from the primary encoder and even pixels from the
			 * companion encoder.
			 */
			bool swap_pixels = lvds->link_type ==
				RCAR_LVDS_DUAL_LINK_ODD_EVEN_PIXELS;

			/*
			 * Configure vertical stripe since we are dealing with
			 * an LVDS dual-link connection.
			 *
			 * ST_SWAP is reserved क्रम the companion encoder, only
			 * set it in the primary encoder.
			 */
			lvdstripe = LVDSTRIPE_ST_ON
				  | (lvds->companion && swap_pixels ?
				     LVDSTRIPE_ST_SWAP : 0);
		पूर्ण
		rcar_lvds_ग_लिखो(lvds, LVDSTRIPE, lvdstripe);
	पूर्ण

	/*
	 * PLL घड़ी configuration on all instances but the companion in
	 * dual-link mode.
	 */
	अगर (lvds->link_type == RCAR_LVDS_SINGLE_LINK || lvds->companion) अणु
		स्थिर काष्ठा drm_crtc_state *crtc_state =
			drm_atomic_get_new_crtc_state(state, crtc);
		स्थिर काष्ठा drm_display_mode *mode =
			&crtc_state->adjusted_mode;

		lvds->info->pll_setup(lvds, mode->घड़ी * 1000);
	पूर्ण

	/* Set the LVDS mode and select the input. */
	lvdcr0 = rcar_lvds_get_lvds_mode(lvds, connector) << LVDCR0_LVMD_SHIFT;

	अगर (lvds->bridge.encoder) अणु
		अगर (drm_crtc_index(crtc) == 2)
			lvdcr0 |= LVDCR0_DUSEL;
	पूर्ण

	rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);

	/* Turn all the channels on. */
	rcar_lvds_ग_लिखो(lvds, LVDCR1,
			LVDCR1_CHSTBY(3) | LVDCR1_CHSTBY(2) |
			LVDCR1_CHSTBY(1) | LVDCR1_CHSTBY(0) | LVDCR1_CLKSTBY);

	अगर (lvds->info->gen < 3) अणु
		/* Enable LVDS operation and turn the bias circuitry on. */
		lvdcr0 |= LVDCR0_BEN | LVDCR0_LVEN;
		rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);
	पूर्ण

	अगर (!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)) अणु
		/*
		 * Turn the PLL on (simple PLL only, extended PLL is fully
		 * controlled through LVDPLLCR).
		 */
		lvdcr0 |= LVDCR0_PLLON;
		rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);
	पूर्ण

	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_PWD) अणु
		/* Set LVDS normal mode. */
		lvdcr0 |= LVDCR0_PWD;
		rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);
	पूर्ण

	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_GEN3_LVEN) अणु
		/*
		 * Turn on the LVDS PHY. On D3, the LVEN and LVRES bit must be
		 * set at the same समय, so करोn't ग_लिखो the रेजिस्टर yet.
		 */
		lvdcr0 |= LVDCR0_LVEN;
		अगर (!(lvds->info->quirks & RCAR_LVDS_QUIRK_PWD))
			rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);
	पूर्ण

	अगर (!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)) अणु
		/* Wait क्रम the PLL startup delay (simple PLL only). */
		usleep_range(100, 150);
	पूर्ण

	/* Turn the output on. */
	lvdcr0 |= LVDCR0_LVRES;
	rcar_lvds_ग_लिखो(lvds, LVDCR0, lvdcr0);

	अगर (lvds->panel) अणु
		drm_panel_prepare(lvds->panel);
		drm_panel_enable(lvds->panel);
	पूर्ण
पूर्ण

अटल व्योम rcar_lvds_atomic_enable(काष्ठा drm_bridge *bridge,
				    काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा drm_atomic_state *state = old_bridge_state->base.state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc *crtc;

	connector = drm_atomic_get_new_connector_क्रम_encoder(state,
							     bridge->encoder);
	crtc = drm_atomic_get_new_connector_state(state, connector)->crtc;

	__rcar_lvds_atomic_enable(bridge, state, crtc, connector);
पूर्ण

अटल व्योम rcar_lvds_atomic_disable(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	अगर (lvds->panel) अणु
		drm_panel_disable(lvds->panel);
		drm_panel_unprepare(lvds->panel);
	पूर्ण

	rcar_lvds_ग_लिखो(lvds, LVDCR0, 0);
	rcar_lvds_ग_लिखो(lvds, LVDCR1, 0);
	rcar_lvds_ग_लिखो(lvds, LVDPLLCR, 0);

	/* Disable the companion LVDS encoder in dual-link mode. */
	अगर (lvds->link_type != RCAR_LVDS_SINGLE_LINK && lvds->companion)
		lvds->companion->funcs->atomic_disable(lvds->companion,
						       old_bridge_state);

	clk_disable_unprepare(lvds->घड़ीs.mod);
पूर्ण

अटल bool rcar_lvds_mode_fixup(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	पूर्णांक min_freq;

	/*
	 * The पूर्णांकernal LVDS encoder has a restricted घड़ी frequency operating
	 * range, from 5MHz to 148.5MHz on D3 and E3, and from 31MHz to
	 * 148.5MHz on all other platक्रमms. Clamp the घड़ी accordingly.
	 */
	min_freq = lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL ? 5000 : 31000;
	adjusted_mode->घड़ी = clamp(adjusted_mode->घड़ी, min_freq, 148500);

	वापस true;
पूर्ण

अटल पूर्णांक rcar_lvds_attach(काष्ठा drm_bridge *bridge,
			    क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	काष्ठा drm_connector *connector = &lvds->connector;
	काष्ठा drm_encoder *encoder = bridge->encoder;
	पूर्णांक ret;

	/* If we have a next bridge just attach it. */
	अगर (lvds->next_bridge)
		वापस drm_bridge_attach(bridge->encoder, lvds->next_bridge,
					 bridge, flags);

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	/* Otherwise अगर we have a panel, create a connector. */
	अगर (!lvds->panel)
		वापस 0;

	ret = drm_connector_init(bridge->dev, connector, &rcar_lvds_conn_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	अगर (ret < 0)
		वापस ret;

	drm_connector_helper_add(connector, &rcar_lvds_conn_helper_funcs);

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम rcar_lvds_detach(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs rcar_lvds_bridge_ops = अणु
	.attach = rcar_lvds_attach,
	.detach = rcar_lvds_detach,
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_enable = rcar_lvds_atomic_enable,
	.atomic_disable = rcar_lvds_atomic_disable,
	.mode_fixup = rcar_lvds_mode_fixup,
पूर्ण;

bool rcar_lvds_dual_link(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	वापस lvds->link_type != RCAR_LVDS_SINGLE_LINK;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_lvds_dual_link);

/* -----------------------------------------------------------------------------
 * Probe & Remove
 */

अटल पूर्णांक rcar_lvds_parse_dt_companion(काष्ठा rcar_lvds *lvds)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *companion;
	काष्ठा device_node *port0, *port1;
	काष्ठा rcar_lvds *companion_lvds;
	काष्ठा device *dev = lvds->dev;
	पूर्णांक dual_link;
	पूर्णांक ret = 0;

	/* Locate the companion LVDS encoder क्रम dual-link operation, अगर any. */
	companion = of_parse_phandle(dev->of_node, "renesas,companion", 0);
	अगर (!companion)
		वापस 0;

	/*
	 * Sanity check: the companion encoder must have the same compatible
	 * string.
	 */
	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!of_device_is_compatible(companion, match->compatible)) अणु
		dev_err(dev, "Companion LVDS encoder is invalid\n");
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण

	/*
	 * We need to work out अगर the sink is expecting us to function in
	 * dual-link mode. We करो this by looking at the DT port nodes we are
	 * connected to, अगर they are marked as expecting even pixels and
	 * odd pixels than we need to enable vertical stripe output.
	 */
	port0 = of_graph_get_port_by_id(dev->of_node, 1);
	port1 = of_graph_get_port_by_id(companion, 1);
	dual_link = drm_of_lvds_get_dual_link_pixel_order(port0, port1);
	of_node_put(port0);
	of_node_put(port1);

	चयन (dual_link) अणु
	हाल DRM_LVDS_DUAL_LINK_ODD_EVEN_PIXELS:
		lvds->link_type = RCAR_LVDS_DUAL_LINK_ODD_EVEN_PIXELS;
		अवरोध;
	हाल DRM_LVDS_DUAL_LINK_EVEN_ODD_PIXELS:
		lvds->link_type = RCAR_LVDS_DUAL_LINK_EVEN_ODD_PIXELS;
		अवरोध;
	शेष:
		/*
		 * Early dual-link bridge specअगरic implementations populate the
		 * timings field of drm_bridge. If the flag is set, we assume
		 * that we are expected to generate even pixels from the primary
		 * encoder, and odd pixels from the companion encoder.
		 */
		अगर (lvds->next_bridge && lvds->next_bridge->timings &&
		    lvds->next_bridge->timings->dual_link)
			lvds->link_type = RCAR_LVDS_DUAL_LINK_EVEN_ODD_PIXELS;
		अन्यथा
			lvds->link_type = RCAR_LVDS_SINGLE_LINK;
	पूर्ण

	अगर (lvds->link_type == RCAR_LVDS_SINGLE_LINK) अणु
		dev_dbg(dev, "Single-link configuration detected\n");
		जाओ करोne;
	पूर्ण

	lvds->companion = of_drm_find_bridge(companion);
	अगर (!lvds->companion) अणु
		ret = -EPROBE_DEFER;
		जाओ करोne;
	पूर्ण

	dev_dbg(dev,
		"Dual-link configuration detected (companion encoder %pOF)\n",
		companion);

	अगर (lvds->link_type == RCAR_LVDS_DUAL_LINK_ODD_EVEN_PIXELS)
		dev_dbg(dev, "Data swapping required\n");

	/*
	 * FIXME: We should not be messing with the companion encoder निजी
	 * data from the primary encoder, we should rather let the companion
	 * encoder work things out on its own. However, the companion encoder
	 * करोesn't hold a reference to the primary encoder, and
	 * drm_of_lvds_get_dual_link_pixel_order needs to be given references
	 * to the output ports of both encoders, thereक्रमe leave it like this
	 * क्रम the समय being.
	 */
	companion_lvds = bridge_to_rcar_lvds(lvds->companion);
	companion_lvds->link_type = lvds->link_type;

करोne:
	of_node_put(companion);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_lvds_parse_dt(काष्ठा rcar_lvds *lvds)
अणु
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(lvds->dev->of_node, 1, 0,
					  &lvds->panel, &lvds->next_bridge);
	अगर (ret)
		जाओ करोne;

	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_DUAL_LINK)
		ret = rcar_lvds_parse_dt_companion(lvds);

करोne:
	/*
	 * On D3/E3 the LVDS encoder provides a घड़ी to the DU, which can be
	 * used क्रम the DPAD output even when the LVDS output is not connected.
	 * Don't fail probe in that हाल as the DU will need the bridge to
	 * control the घड़ी.
	 */
	अगर (lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)
		वापस ret == -ENODEV ? 0 : ret;

	वापस ret;
पूर्ण

अटल काष्ठा clk *rcar_lvds_get_घड़ी(काष्ठा rcar_lvds *lvds, स्थिर अक्षर *name,
				       bool optional)
अणु
	काष्ठा clk *clk;

	clk = devm_clk_get(lvds->dev, name);
	अगर (!IS_ERR(clk))
		वापस clk;

	अगर (PTR_ERR(clk) == -ENOENT && optional)
		वापस शून्य;

	अगर (PTR_ERR(clk) != -EPROBE_DEFER)
		dev_err(lvds->dev, "failed to get %s clock\n",
			name ? name : "module");

	वापस clk;
पूर्ण

अटल पूर्णांक rcar_lvds_get_घड़ीs(काष्ठा rcar_lvds *lvds)
अणु
	lvds->घड़ीs.mod = rcar_lvds_get_घड़ी(lvds, शून्य, false);
	अगर (IS_ERR(lvds->घड़ीs.mod))
		वापस PTR_ERR(lvds->घड़ीs.mod);

	/*
	 * LVDS encoders without an extended PLL have no बाह्यal घड़ी inमाला_दो.
	 */
	अगर (!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL))
		वापस 0;

	lvds->घड़ीs.extal = rcar_lvds_get_घड़ी(lvds, "extal", true);
	अगर (IS_ERR(lvds->घड़ीs.extal))
		वापस PTR_ERR(lvds->घड़ीs.extal);

	lvds->घड़ीs.करोtclkin[0] = rcar_lvds_get_घड़ी(lvds, "dclkin.0", true);
	अगर (IS_ERR(lvds->घड़ीs.करोtclkin[0]))
		वापस PTR_ERR(lvds->घड़ीs.करोtclkin[0]);

	lvds->घड़ीs.करोtclkin[1] = rcar_lvds_get_घड़ी(lvds, "dclkin.1", true);
	अगर (IS_ERR(lvds->घड़ीs.करोtclkin[1]))
		वापस PTR_ERR(lvds->घड़ीs.करोtclkin[1]);

	/* At least one input to the PLL must be available. */
	अगर (!lvds->घड़ीs.extal && !lvds->घड़ीs.करोtclkin[0] &&
	    !lvds->घड़ीs.करोtclkin[1]) अणु
		dev_err(lvds->dev,
			"no input clock (extal, dclkin.0 or dclkin.1)\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_r8a7790es1_info = अणु
	.gen = 2,
	.quirks = RCAR_LVDS_QUIRK_LANES,
	.pll_setup = rcar_lvds_pll_setup_gen2,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute lvds_quirk_matches[] = अणु
	अणु
		.soc_id = "r8a7790", .revision = "ES1.*",
		.data = &rcar_lvds_r8a7790es1_info,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक rcar_lvds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा rcar_lvds *lvds;
	काष्ठा resource *mem;
	पूर्णांक ret;

	lvds = devm_kzalloc(&pdev->dev, माप(*lvds), GFP_KERNEL);
	अगर (lvds == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, lvds);

	lvds->dev = &pdev->dev;
	lvds->info = of_device_get_match_data(&pdev->dev);

	attr = soc_device_match(lvds_quirk_matches);
	अगर (attr)
		lvds->info = attr->data;

	ret = rcar_lvds_parse_dt(lvds);
	अगर (ret < 0)
		वापस ret;

	lvds->bridge.driver_निजी = lvds;
	lvds->bridge.funcs = &rcar_lvds_bridge_ops;
	lvds->bridge.of_node = pdev->dev.of_node;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	lvds->mmio = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(lvds->mmio))
		वापस PTR_ERR(lvds->mmio);

	ret = rcar_lvds_get_घड़ीs(lvds);
	अगर (ret < 0)
		वापस ret;

	drm_bridge_add(&lvds->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_lvds_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_lvds *lvds = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&lvds->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_gen2_info = अणु
	.gen = 2,
	.pll_setup = rcar_lvds_pll_setup_gen2,
पूर्ण;

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_gen3_info = अणु
	.gen = 3,
	.quirks = RCAR_LVDS_QUIRK_PWD,
	.pll_setup = rcar_lvds_pll_setup_gen3,
पूर्ण;

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_r8a77970_info = अणु
	.gen = 3,
	.quirks = RCAR_LVDS_QUIRK_PWD | RCAR_LVDS_QUIRK_GEN3_LVEN,
	.pll_setup = rcar_lvds_pll_setup_gen2,
पूर्ण;

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_r8a77990_info = अणु
	.gen = 3,
	.quirks = RCAR_LVDS_QUIRK_GEN3_LVEN | RCAR_LVDS_QUIRK_EXT_PLL
		| RCAR_LVDS_QUIRK_DUAL_LINK,
	.pll_setup = rcar_lvds_pll_setup_d3_e3,
पूर्ण;

अटल स्थिर काष्ठा rcar_lvds_device_info rcar_lvds_r8a77995_info = अणु
	.gen = 3,
	.quirks = RCAR_LVDS_QUIRK_GEN3_LVEN | RCAR_LVDS_QUIRK_PWD
		| RCAR_LVDS_QUIRK_EXT_PLL | RCAR_LVDS_QUIRK_DUAL_LINK,
	.pll_setup = rcar_lvds_pll_setup_d3_e3,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_lvds_of_table[] = अणु
	अणु .compatible = "renesas,r8a7742-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a7743-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a7744-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a774a1-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a774b1-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a774c0-lvds", .data = &rcar_lvds_r8a77990_info पूर्ण,
	अणु .compatible = "renesas,r8a774e1-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a7790-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a7791-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a7793-lvds", .data = &rcar_lvds_gen2_info पूर्ण,
	अणु .compatible = "renesas,r8a7795-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a7796-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a77965-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a77970-lvds", .data = &rcar_lvds_r8a77970_info पूर्ण,
	अणु .compatible = "renesas,r8a77980-lvds", .data = &rcar_lvds_gen3_info पूर्ण,
	अणु .compatible = "renesas,r8a77990-lvds", .data = &rcar_lvds_r8a77990_info पूर्ण,
	अणु .compatible = "renesas,r8a77995-lvds", .data = &rcar_lvds_r8a77995_info पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rcar_lvds_of_table);

अटल काष्ठा platक्रमm_driver rcar_lvds_platक्रमm_driver = अणु
	.probe		= rcar_lvds_probe,
	.हटाओ		= rcar_lvds_हटाओ,
	.driver		= अणु
		.name	= "rcar-lvds",
		.of_match_table = rcar_lvds_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_lvds_platक्रमm_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas R-Car LVDS Encoder Driver");
MODULE_LICENSE("GPL");
