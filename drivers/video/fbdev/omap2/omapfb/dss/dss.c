<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/dss.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DSS"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/gfp.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/suspend.h>
#समावेश <linux/component.h>
#समावेश <linux/pinctrl/consumer.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

#घोषणा DSS_SZ_REGS			SZ_512

काष्ठा dss_reg अणु
	u16 idx;
पूर्ण;

#घोषणा DSS_REG(idx)			((स्थिर काष्ठा dss_reg) अणु idx पूर्ण)

#घोषणा DSS_REVISION			DSS_REG(0x0000)
#घोषणा DSS_SYSCONFIG			DSS_REG(0x0010)
#घोषणा DSS_SYSSTATUS			DSS_REG(0x0014)
#घोषणा DSS_CONTROL			DSS_REG(0x0040)
#घोषणा DSS_SDI_CONTROL			DSS_REG(0x0044)
#घोषणा DSS_PLL_CONTROL			DSS_REG(0x0048)
#घोषणा DSS_SDI_STATUS			DSS_REG(0x005C)

#घोषणा REG_GET(idx, start, end) \
	FLD_GET(dss_पढ़ो_reg(idx), start, end)

#घोषणा REG_FLD_MOD(idx, val, start, end) \
	dss_ग_लिखो_reg(idx, FLD_MOD(dss_पढ़ो_reg(idx), val, start, end))

काष्ठा dss_features अणु
	u8 fck_भाग_max;
	u8 dss_fck_multiplier;
	स्थिर अक्षर *parent_clk_name;
	स्थिर क्रमागत omap_display_type *ports;
	पूर्णांक num_ports;
	पूर्णांक (*dpi_select_source)(पूर्णांक port, क्रमागत omap_channel channel);
पूर्ण;

अटल काष्ठा अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem    *base;
	काष्ठा regmap	*syscon_pll_ctrl;
	u32		syscon_pll_ctrl_offset;

	काष्ठा clk	*parent_clk;
	काष्ठा clk	*dss_clk;
	अचिन्हित दीर्घ	dss_clk_rate;

	अचिन्हित दीर्घ	cache_req_pck;
	अचिन्हित दीर्घ	cache_prate;
	काष्ठा dispc_घड़ी_info cache_dispc_cinfo;

	क्रमागत omap_dss_clk_source dsi_clk_source[MAX_NUM_DSI];
	क्रमागत omap_dss_clk_source dispc_clk_source;
	क्रमागत omap_dss_clk_source lcd_clk_source[MAX_DSS_LCD_MANAGERS];

	bool		ctx_valid;
	u32		ctx[DSS_SZ_REGS / माप(u32)];

	स्थिर काष्ठा dss_features *feat;

	काष्ठा dss_pll	*video1_pll;
	काष्ठा dss_pll	*video2_pll;
पूर्ण dss;

अटल स्थिर अक्षर * स्थिर dss_generic_clk_source_names[] = अणु
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC]	= "DSI_PLL_HSDIV_DISPC",
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI]	= "DSI_PLL_HSDIV_DSI",
	[OMAP_DSS_CLK_SRC_FCK]			= "DSS_FCK",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC]	= "DSI_PLL2_HSDIV_DISPC",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI]	= "DSI_PLL2_HSDIV_DSI",
पूर्ण;

अटल bool dss_initialized;

bool omapdss_is_initialized(व्योम)
अणु
	वापस dss_initialized;
पूर्ण
EXPORT_SYMBOL(omapdss_is_initialized);

अटल अंतरभूत व्योम dss_ग_लिखो_reg(स्थिर काष्ठा dss_reg idx, u32 val)
अणु
	__raw_ग_लिखोl(val, dss.base + idx.idx);
पूर्ण

अटल अंतरभूत u32 dss_पढ़ो_reg(स्थिर काष्ठा dss_reg idx)
अणु
	वापस __raw_पढ़ोl(dss.base + idx.idx);
पूर्ण

#घोषणा SR(reg) \
	dss.ctx[(DSS_##reg).idx / माप(u32)] = dss_पढ़ो_reg(DSS_##reg)
#घोषणा RR(reg) \
	dss_ग_लिखो_reg(DSS_##reg, dss.ctx[(DSS_##reg).idx / माप(u32)])

अटल व्योम dss_save_context(व्योम)
अणु
	DSSDBG("dss_save_context\n");

	SR(CONTROL);

	अगर (dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_LCD) &
			OMAP_DISPLAY_TYPE_SDI) अणु
		SR(SDI_CONTROL);
		SR(PLL_CONTROL);
	पूर्ण

	dss.ctx_valid = true;

	DSSDBG("context saved\n");
पूर्ण

अटल व्योम dss_restore_context(व्योम)
अणु
	DSSDBG("dss_restore_context\n");

	अगर (!dss.ctx_valid)
		वापस;

	RR(CONTROL);

	अगर (dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_LCD) &
			OMAP_DISPLAY_TYPE_SDI) अणु
		RR(SDI_CONTROL);
		RR(PLL_CONTROL);
	पूर्ण

	DSSDBG("context restored\n");
पूर्ण

#अघोषित SR
#अघोषित RR

व्योम dss_ctrl_pll_enable(क्रमागत dss_pll_id pll_id, bool enable)
अणु
	अचिन्हित shअगरt;
	अचिन्हित val;

	अगर (!dss.syscon_pll_ctrl)
		वापस;

	val = !enable;

	चयन (pll_id) अणु
	हाल DSS_PLL_VIDEO1:
		shअगरt = 0;
		अवरोध;
	हाल DSS_PLL_VIDEO2:
		shअगरt = 1;
		अवरोध;
	हाल DSS_PLL_HDMI:
		shअगरt = 2;
		अवरोध;
	शेष:
		DSSERR("illegal DSS PLL ID %d\n", pll_id);
		वापस;
	पूर्ण

	regmap_update_bits(dss.syscon_pll_ctrl, dss.syscon_pll_ctrl_offset,
		1 << shअगरt, val << shअगरt);
पूर्ण

व्योम dss_ctrl_pll_set_control_mux(क्रमागत dss_pll_id pll_id,
	क्रमागत omap_channel channel)
अणु
	अचिन्हित shअगरt, val;

	अगर (!dss.syscon_pll_ctrl)
		वापस;

	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		shअगरt = 3;

		चयन (pll_id) अणु
		हाल DSS_PLL_VIDEO1:
			val = 0; अवरोध;
		हाल DSS_PLL_HDMI:
			val = 1; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD\n");
			वापस;
		पूर्ण

		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD2:
		shअगरt = 5;

		चयन (pll_id) अणु
		हाल DSS_PLL_VIDEO1:
			val = 0; अवरोध;
		हाल DSS_PLL_VIDEO2:
			val = 1; अवरोध;
		हाल DSS_PLL_HDMI:
			val = 2; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD2\n");
			वापस;
		पूर्ण

		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD3:
		shअगरt = 7;

		चयन (pll_id) अणु
		हाल DSS_PLL_VIDEO1:
			val = 1; अवरोध;
		हाल DSS_PLL_VIDEO2:
			val = 0; अवरोध;
		हाल DSS_PLL_HDMI:
			val = 2; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD3\n");
			वापस;
		पूर्ण

		अवरोध;
	शेष:
		DSSERR("error in PLL mux config\n");
		वापस;
	पूर्ण

	regmap_update_bits(dss.syscon_pll_ctrl, dss.syscon_pll_ctrl_offset,
		0x3 << shअगरt, val << shअगरt);
पूर्ण

व्योम dss_sdi_init(पूर्णांक datapairs)
अणु
	u32 l;

	BUG_ON(datapairs > 3 || datapairs < 1);

	l = dss_पढ़ो_reg(DSS_SDI_CONTROL);
	l = FLD_MOD(l, 0xf, 19, 15);		/* SDI_PDIV */
	l = FLD_MOD(l, datapairs-1, 3, 2);	/* SDI_PRSEL */
	l = FLD_MOD(l, 2, 1, 0);		/* SDI_BWSEL */
	dss_ग_लिखो_reg(DSS_SDI_CONTROL, l);

	l = dss_पढ़ो_reg(DSS_PLL_CONTROL);
	l = FLD_MOD(l, 0x7, 25, 22);	/* SDI_PLL_FREQSEL */
	l = FLD_MOD(l, 0xb, 16, 11);	/* SDI_PLL_REGN */
	l = FLD_MOD(l, 0xb4, 10, 1);	/* SDI_PLL_REGM */
	dss_ग_लिखो_reg(DSS_PLL_CONTROL, l);
पूर्ण

पूर्णांक dss_sdi_enable(व्योम)
अणु
	अचिन्हित दीर्घ समयout;

	dispc_pck_मुक्त_enable(1);

	/* Reset SDI PLL */
	REG_FLD_MOD(DSS_PLL_CONTROL, 1, 18, 18); /* SDI_PLL_SYSRESET */
	udelay(1);	/* रुको 2x PCLK */

	/* Lock SDI PLL */
	REG_FLD_MOD(DSS_PLL_CONTROL, 1, 28, 28); /* SDI_PLL_GOBIT */

	/* Waiting क्रम PLL lock request to complete */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (dss_पढ़ो_reg(DSS_SDI_STATUS) & (1 << 6)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("PLL lock request timed out\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	/* Clearing PLL_GO bit */
	REG_FLD_MOD(DSS_PLL_CONTROL, 0, 28, 28);

	/* Waiting क्रम PLL to lock */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (!(dss_पढ़ो_reg(DSS_SDI_STATUS) & (1 << 5))) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("PLL lock timed out\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	dispc_lcd_enable_संकेत(1);

	/* Waiting क्रम SDI reset to complete */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (!(dss_पढ़ो_reg(DSS_SDI_STATUS) & (1 << 2))) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("SDI reset timed out\n");
			जाओ err2;
		पूर्ण
	पूर्ण

	वापस 0;

 err2:
	dispc_lcd_enable_संकेत(0);
 err1:
	/* Reset SDI PLL */
	REG_FLD_MOD(DSS_PLL_CONTROL, 0, 18, 18); /* SDI_PLL_SYSRESET */

	dispc_pck_मुक्त_enable(0);

	वापस -ETIMEDOUT;
पूर्ण

व्योम dss_sdi_disable(व्योम)
अणु
	dispc_lcd_enable_संकेत(0);

	dispc_pck_मुक्त_enable(0);

	/* Reset SDI PLL */
	REG_FLD_MOD(DSS_PLL_CONTROL, 0, 18, 18); /* SDI_PLL_SYSRESET */
पूर्ण

स्थिर अक्षर *dss_get_generic_clk_source_name(क्रमागत omap_dss_clk_source clk_src)
अणु
	वापस dss_generic_clk_source_names[clk_src];
पूर्ण

व्योम dss_dump_घड़ीs(काष्ठा seq_file *s)
अणु
	स्थिर अक्षर *fclk_name, *fclk_real_name;
	अचिन्हित दीर्घ fclk_rate;

	अगर (dss_runसमय_get())
		वापस;

	seq_म_लिखो(s, "- DSS -\n");

	fclk_name = dss_get_generic_clk_source_name(OMAP_DSS_CLK_SRC_FCK);
	fclk_real_name = dss_feat_get_clk_source_name(OMAP_DSS_CLK_SRC_FCK);
	fclk_rate = clk_get_rate(dss.dss_clk);

	seq_म_लिखो(s, "%s (%s) = %lu\n",
			fclk_name, fclk_real_name,
			fclk_rate);

	dss_runसमय_put();
पूर्ण

अटल व्योम dss_dump_regs(काष्ठा seq_file *s)
अणु
#घोषणा DUMPREG(r) seq_म_लिखो(s, "%-35s %08x\n", #r, dss_पढ़ो_reg(r))

	अगर (dss_runसमय_get())
		वापस;

	DUMPREG(DSS_REVISION);
	DUMPREG(DSS_SYSCONFIG);
	DUMPREG(DSS_SYSSTATUS);
	DUMPREG(DSS_CONTROL);

	अगर (dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_LCD) &
			OMAP_DISPLAY_TYPE_SDI) अणु
		DUMPREG(DSS_SDI_CONTROL);
		DUMPREG(DSS_PLL_CONTROL);
		DUMPREG(DSS_SDI_STATUS);
	पूर्ण

	dss_runसमय_put();
#अघोषित DUMPREG
पूर्ण

अटल व्योम dss_select_dispc_clk_source(क्रमागत omap_dss_clk_source clk_src)
अणु
	पूर्णांक b;
	u8 start, end;

	चयन (clk_src) अणु
	हाल OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
		b = 1;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
		b = 2;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	dss_feat_get_reg_field(FEAT_REG_DISPC_CLK_SWITCH, &start, &end);

	REG_FLD_MOD(DSS_CONTROL, b, start, end);	/* DISPC_CLK_SWITCH */

	dss.dispc_clk_source = clk_src;
पूर्ण

व्योम dss_select_dsi_clk_source(पूर्णांक dsi_module,
		क्रमागत omap_dss_clk_source clk_src)
अणु
	पूर्णांक b, pos;

	चयन (clk_src) अणु
	हाल OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI:
		BUG_ON(dsi_module != 0);
		b = 1;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI:
		BUG_ON(dsi_module != 1);
		b = 1;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	pos = dsi_module == 0 ? 1 : 10;
	REG_FLD_MOD(DSS_CONTROL, b, pos, pos);	/* DSIx_CLK_SWITCH */

	dss.dsi_clk_source[dsi_module] = clk_src;
पूर्ण

व्योम dss_select_lcd_clk_source(क्रमागत omap_channel channel,
		क्रमागत omap_dss_clk_source clk_src)
अणु
	पूर्णांक b, ix, pos;

	अगर (!dss_has_feature(FEAT_LCD_CLK_SRC)) अणु
		dss_select_dispc_clk_source(clk_src);
		वापस;
	पूर्ण

	चयन (clk_src) अणु
	हाल OMAP_DSS_CLK_SRC_FCK:
		b = 0;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC:
		BUG_ON(channel != OMAP_DSS_CHANNEL_LCD);
		b = 1;
		अवरोध;
	हाल OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC:
		BUG_ON(channel != OMAP_DSS_CHANNEL_LCD2 &&
		       channel != OMAP_DSS_CHANNEL_LCD3);
		b = 1;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	pos = channel == OMAP_DSS_CHANNEL_LCD ? 0 :
	     (channel == OMAP_DSS_CHANNEL_LCD2 ? 12 : 19);
	REG_FLD_MOD(DSS_CONTROL, b, pos, pos);	/* LCDx_CLK_SWITCH */

	ix = channel == OMAP_DSS_CHANNEL_LCD ? 0 :
	    (channel == OMAP_DSS_CHANNEL_LCD2 ? 1 : 2);
	dss.lcd_clk_source[ix] = clk_src;
पूर्ण

क्रमागत omap_dss_clk_source dss_get_dispc_clk_source(व्योम)
अणु
	वापस dss.dispc_clk_source;
पूर्ण

क्रमागत omap_dss_clk_source dss_get_dsi_clk_source(पूर्णांक dsi_module)
अणु
	वापस dss.dsi_clk_source[dsi_module];
पूर्ण

क्रमागत omap_dss_clk_source dss_get_lcd_clk_source(क्रमागत omap_channel channel)
अणु
	अगर (dss_has_feature(FEAT_LCD_CLK_SRC)) अणु
		पूर्णांक ix = channel == OMAP_DSS_CHANNEL_LCD ? 0 :
			(channel == OMAP_DSS_CHANNEL_LCD2 ? 1 : 2);
		वापस dss.lcd_clk_source[ix];
	पूर्ण अन्यथा अणु
		/* LCD_CLK source is the same as DISPC_FCLK source क्रम
		 * OMAP2 and OMAP3 */
		वापस dss.dispc_clk_source;
	पूर्ण
पूर्ण

bool dss_भाग_calc(अचिन्हित दीर्घ pck, अचिन्हित दीर्घ fck_min,
		dss_भाग_calc_func func, व्योम *data)
अणु
	पूर्णांक fckd, fckd_start, fckd_stop;
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ fck_hw_max;
	अचिन्हित दीर्घ fckd_hw_max;
	अचिन्हित दीर्घ prate;
	अचिन्हित m;

	fck_hw_max = dss_feat_get_param_max(FEAT_PARAM_DSS_FCK);

	अगर (dss.parent_clk == शून्य) अणु
		अचिन्हित pckd;

		pckd = fck_hw_max / pck;

		fck = pck * pckd;

		fck = clk_round_rate(dss.dss_clk, fck);

		वापस func(fck, data);
	पूर्ण

	fckd_hw_max = dss.feat->fck_भाग_max;

	m = dss.feat->dss_fck_multiplier;
	prate = clk_get_rate(dss.parent_clk);

	fck_min = fck_min ? fck_min : 1;

	fckd_start = min(prate * m / fck_min, fckd_hw_max);
	fckd_stop = max(DIV_ROUND_UP(prate * m, fck_hw_max), 1ul);

	क्रम (fckd = fckd_start; fckd >= fckd_stop; --fckd) अणु
		fck = DIV_ROUND_UP(prate, fckd) * m;

		अगर (func(fck, data))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक dss_set_fck_rate(अचिन्हित दीर्घ rate)
अणु
	पूर्णांक r;

	DSSDBG("set fck to %lu\n", rate);

	r = clk_set_rate(dss.dss_clk, rate);
	अगर (r)
		वापस r;

	dss.dss_clk_rate = clk_get_rate(dss.dss_clk);

	WARN_ONCE(dss.dss_clk_rate != rate,
			"clk rate mismatch: %lu != %lu", dss.dss_clk_rate,
			rate);

	वापस 0;
पूर्ण

अचिन्हित दीर्घ dss_get_dispc_clk_rate(व्योम)
अणु
	वापस dss.dss_clk_rate;
पूर्ण

अटल पूर्णांक dss_setup_शेष_घड़ी(व्योम)
अणु
	अचिन्हित दीर्घ max_dss_fck, prate;
	अचिन्हित दीर्घ fck;
	अचिन्हित fck_भाग;
	पूर्णांक r;

	max_dss_fck = dss_feat_get_param_max(FEAT_PARAM_DSS_FCK);

	अगर (dss.parent_clk == शून्य) अणु
		fck = clk_round_rate(dss.dss_clk, max_dss_fck);
	पूर्ण अन्यथा अणु
		prate = clk_get_rate(dss.parent_clk);

		fck_भाग = DIV_ROUND_UP(prate * dss.feat->dss_fck_multiplier,
				max_dss_fck);
		fck = DIV_ROUND_UP(prate, fck_भाग) * dss.feat->dss_fck_multiplier;
	पूर्ण

	r = dss_set_fck_rate(fck);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

व्योम dss_set_venc_output(क्रमागत omap_dss_venc_type type)
अणु
	पूर्णांक l = 0;

	अगर (type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l = 0;
	अन्यथा अगर (type == OMAP_DSS_VENC_TYPE_SVIDEO)
		l = 1;
	अन्यथा
		BUG();

	/* venc out selection. 0 = comp, 1 = svideo */
	REG_FLD_MOD(DSS_CONTROL, l, 6, 6);
पूर्ण

व्योम dss_set_dac_pwrdn_bgz(bool enable)
अणु
	REG_FLD_MOD(DSS_CONTROL, enable, 5, 5);	/* DAC Power-Down Control */
पूर्ण

व्योम dss_select_hdmi_venc_clk_source(क्रमागत dss_hdmi_venc_clk_source_select src)
अणु
	क्रमागत omap_display_type dp;
	dp = dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_DIGIT);

	/* Complain about invalid selections */
	WARN_ON((src == DSS_VENC_TV_CLK) && !(dp & OMAP_DISPLAY_TYPE_VENC));
	WARN_ON((src == DSS_HDMI_M_PCLK) && !(dp & OMAP_DISPLAY_TYPE_HDMI));

	/* Select only अगर we have options */
	अगर ((dp & OMAP_DISPLAY_TYPE_VENC) && (dp & OMAP_DISPLAY_TYPE_HDMI))
		REG_FLD_MOD(DSS_CONTROL, src, 15, 15);	/* VENC_HDMI_SWITCH */
पूर्ण

क्रमागत dss_hdmi_venc_clk_source_select dss_get_hdmi_venc_clk_source(व्योम)
अणु
	क्रमागत omap_display_type displays;

	displays = dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_DIGIT);
	अगर ((displays & OMAP_DISPLAY_TYPE_HDMI) == 0)
		वापस DSS_VENC_TV_CLK;

	अगर ((displays & OMAP_DISPLAY_TYPE_VENC) == 0)
		वापस DSS_HDMI_M_PCLK;

	वापस REG_GET(DSS_CONTROL, 15, 15);
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap2_omap3(पूर्णांक port, क्रमागत omap_channel channel)
अणु
	अगर (channel != OMAP_DSS_CHANNEL_LCD)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap4(पूर्णांक port, क्रमागत omap_channel channel)
अणु
	पूर्णांक val;

	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD2:
		val = 0;
		अवरोध;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	REG_FLD_MOD(DSS_CONTROL, val, 17, 17);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap5(पूर्णांक port, क्रमागत omap_channel channel)
अणु
	पूर्णांक val;

	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		val = 1;
		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD2:
		val = 2;
		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD3:
		val = 3;
		अवरोध;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	REG_FLD_MOD(DSS_CONTROL, val, 17, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_dra7xx(पूर्णांक port, क्रमागत omap_channel channel)
अणु
	चयन (port) अणु
	हाल 0:
		वापस dss_dpi_select_source_omap5(port, channel);
	हाल 1:
		अगर (channel != OMAP_DSS_CHANNEL_LCD2)
			वापस -EINVAL;
		अवरोध;
	हाल 2:
		अगर (channel != OMAP_DSS_CHANNEL_LCD3)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dss_dpi_select_source(पूर्णांक port, क्रमागत omap_channel channel)
अणु
	वापस dss.feat->dpi_select_source(port, channel);
पूर्ण

अटल पूर्णांक dss_get_घड़ीs(व्योम)
अणु
	काष्ठा clk *clk;

	clk = devm_clk_get(&dss.pdev->dev, "fck");
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get clock fck\n");
		वापस PTR_ERR(clk);
	पूर्ण

	dss.dss_clk = clk;

	अगर (dss.feat->parent_clk_name) अणु
		clk = clk_get(शून्य, dss.feat->parent_clk_name);
		अगर (IS_ERR(clk)) अणु
			DSSERR("Failed to get %s\n", dss.feat->parent_clk_name);
			वापस PTR_ERR(clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk = शून्य;
	पूर्ण

	dss.parent_clk = clk;

	वापस 0;
पूर्ण

अटल व्योम dss_put_घड़ीs(व्योम)
अणु
	अगर (dss.parent_clk)
		clk_put(dss.parent_clk);
पूर्ण

पूर्णांक dss_runसमय_get(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("dss_runtime_get\n");

	r = pm_runसमय_get_sync(&dss.pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_sync(&dss.pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dss_runसमय_put(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("dss_runtime_put\n");

	r = pm_runसमय_put_sync(&dss.pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS && r != -EBUSY);
पूर्ण

/* DEBUGFS */
#अगर defined(CONFIG_FB_OMAP2_DSS_DEBUGFS)
व्योम dss_debug_dump_घड़ीs(काष्ठा seq_file *s)
अणु
	dss_dump_घड़ीs(s);
	dispc_dump_घड़ीs(s);
#अगर_घोषित CONFIG_FB_OMAP2_DSS_DSI
	dsi_dump_घड़ीs(s);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर


अटल स्थिर क्रमागत omap_display_type omap2plus_ports[] = अणु
	OMAP_DISPLAY_TYPE_DPI,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap34xx_ports[] = अणु
	OMAP_DISPLAY_TYPE_DPI,
	OMAP_DISPLAY_TYPE_SDI,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type dra7xx_ports[] = अणु
	OMAP_DISPLAY_TYPE_DPI,
	OMAP_DISPLAY_TYPE_DPI,
	OMAP_DISPLAY_TYPE_DPI,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap24xx_dss_feats = अणु
	/*
	 * fck भाग max is really 16, but the भागider range has gaps. The range
	 * from 1 to 6 has no gaps, so let's use that as a max.
	 */
	.fck_भाग_max		=	6,
	.dss_fck_multiplier	=	2,
	.parent_clk_name	=	"core_ck",
	.dpi_select_source	=	&dss_dpi_select_source_omap2_omap3,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features omap34xx_dss_feats = अणु
	.fck_भाग_max		=	16,
	.dss_fck_multiplier	=	2,
	.parent_clk_name	=	"dpll4_ck",
	.dpi_select_source	=	&dss_dpi_select_source_omap2_omap3,
	.ports			=	omap34xx_ports,
	.num_ports		=	ARRAY_SIZE(omap34xx_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features omap3630_dss_feats = अणु
	.fck_भाग_max		=	31,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll4_ck",
	.dpi_select_source	=	&dss_dpi_select_source_omap2_omap3,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features omap44xx_dss_feats = अणु
	.fck_भाग_max		=	32,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.dpi_select_source	=	&dss_dpi_select_source_omap4,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features omap54xx_dss_feats = अणु
	.fck_भाग_max		=	64,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.dpi_select_source	=	&dss_dpi_select_source_omap5,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features am43xx_dss_feats = अणु
	.fck_भाग_max		=	0,
	.dss_fck_multiplier	=	0,
	.parent_clk_name	=	शून्य,
	.dpi_select_source	=	&dss_dpi_select_source_omap2_omap3,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features dra7xx_dss_feats = अणु
	.fck_भाग_max		=	64,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.dpi_select_source	=	&dss_dpi_select_source_dra7xx,
	.ports			=	dra7xx_ports,
	.num_ports		=	ARRAY_SIZE(dra7xx_ports),
पूर्ण;

अटल स्थिर काष्ठा dss_features *dss_get_features(व्योम)
अणु
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP24xx:
		वापस &omap24xx_dss_feats;

	हाल OMAPDSS_VER_OMAP34xx_ES1:
	हाल OMAPDSS_VER_OMAP34xx_ES3:
	हाल OMAPDSS_VER_AM35xx:
		वापस &omap34xx_dss_feats;

	हाल OMAPDSS_VER_OMAP3630:
		वापस &omap3630_dss_feats;

	हाल OMAPDSS_VER_OMAP4430_ES1:
	हाल OMAPDSS_VER_OMAP4430_ES2:
	हाल OMAPDSS_VER_OMAP4:
		वापस &omap44xx_dss_feats;

	हाल OMAPDSS_VER_OMAP5:
		वापस &omap54xx_dss_feats;

	हाल OMAPDSS_VER_AM43xx:
		वापस &am43xx_dss_feats;

	हाल OMAPDSS_VER_DRA7xx:
		वापस &dra7xx_dss_feats;

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम dss_uninit_ports(काष्ठा platक्रमm_device *pdev);

अटल पूर्णांक dss_init_ports(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *parent = pdev->dev.of_node;
	काष्ठा device_node *port;
	पूर्णांक r, ret = 0;

	अगर (parent == शून्य)
		वापस 0;

	port = omapdss_of_get_next_port(parent, शून्य);
	अगर (!port)
		वापस 0;

	अगर (dss.feat->num_ports == 0)
		वापस 0;

	करो अणु
		क्रमागत omap_display_type port_type;
		u32 reg;

		r = of_property_पढ़ो_u32(port, "reg", &reg);
		अगर (r)
			reg = 0;

		अगर (reg >= dss.feat->num_ports)
			जारी;

		port_type = dss.feat->ports[reg];

		चयन (port_type) अणु
		हाल OMAP_DISPLAY_TYPE_DPI:
			ret = dpi_init_port(pdev, port);
			अवरोध;
		हाल OMAP_DISPLAY_TYPE_SDI:
			ret = sdi_init_port(pdev, port);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!ret &&
		 (port = omapdss_of_get_next_port(parent, port)) != शून्य);

	अगर (ret)
		dss_uninit_ports(pdev);

	वापस ret;
पूर्ण

अटल व्योम dss_uninit_ports(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *parent = pdev->dev.of_node;
	काष्ठा device_node *port;

	अगर (parent == शून्य)
		वापस;

	port = omapdss_of_get_next_port(parent, शून्य);
	अगर (!port)
		वापस;

	अगर (dss.feat->num_ports == 0)
		वापस;

	करो अणु
		क्रमागत omap_display_type port_type;
		u32 reg;
		पूर्णांक r;

		r = of_property_पढ़ो_u32(port, "reg", &reg);
		अगर (r)
			reg = 0;

		अगर (reg >= dss.feat->num_ports)
			जारी;

		port_type = dss.feat->ports[reg];

		चयन (port_type) अणु
		हाल OMAP_DISPLAY_TYPE_DPI:
			dpi_uninit_port(port);
			अवरोध;
		हाल OMAP_DISPLAY_TYPE_SDI:
			sdi_uninit_port(port);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((port = omapdss_of_get_next_port(parent, port)) != शून्य);
पूर्ण

अटल पूर्णांक dss_video_pll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regulator *pll_regulator;
	पूर्णांक r;

	अगर (!np)
		वापस 0;

	अगर (of_property_पढ़ो_bool(np, "syscon-pll-ctrl")) अणु
		dss.syscon_pll_ctrl = syscon_regmap_lookup_by_phandle(np,
			"syscon-pll-ctrl");
		अगर (IS_ERR(dss.syscon_pll_ctrl)) अणु
			dev_err(&pdev->dev,
				"failed to get syscon-pll-ctrl regmap\n");
			वापस PTR_ERR(dss.syscon_pll_ctrl);
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(np, "syscon-pll-ctrl", 1,
				&dss.syscon_pll_ctrl_offset)) अणु
			dev_err(&pdev->dev,
				"failed to get syscon-pll-ctrl offset\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pll_regulator = devm_regulator_get(&pdev->dev, "vdda_video");
	अगर (IS_ERR(pll_regulator)) अणु
		r = PTR_ERR(pll_regulator);

		चयन (r) अणु
		हाल -ENOENT:
			pll_regulator = शून्य;
			अवरोध;

		हाल -EPROBE_DEFER:
			वापस -EPROBE_DEFER;

		शेष:
			DSSERR("can't get DPLL VDDA regulator\n");
			वापस r;
		पूर्ण
	पूर्ण

	अगर (of_property_match_string(np, "reg-names", "pll1") >= 0) अणु
		dss.video1_pll = dss_video_pll_init(pdev, 0, pll_regulator);
		अगर (IS_ERR(dss.video1_pll))
			वापस PTR_ERR(dss.video1_pll);
	पूर्ण

	अगर (of_property_match_string(np, "reg-names", "pll2") >= 0) अणु
		dss.video2_pll = dss_video_pll_init(pdev, 1, pll_regulator);
		अगर (IS_ERR(dss.video2_pll)) अणु
			dss_video_pll_uninit(dss.video1_pll);
			वापस PTR_ERR(dss.video2_pll);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* DSS HW IP initialisation */
अटल पूर्णांक dss_bind(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *dss_mem;
	u32 rev;
	पूर्णांक r;

	dss.pdev = pdev;

	dss.feat = dss_get_features();
	अगर (!dss.feat)
		वापस -ENODEV;

	dss_mem = platक्रमm_get_resource(dss.pdev, IORESOURCE_MEM, 0);
	अगर (!dss_mem) अणु
		DSSERR("can't get IORESOURCE_MEM DSS\n");
		वापस -EINVAL;
	पूर्ण

	dss.base = devm_ioremap(&pdev->dev, dss_mem->start,
				resource_size(dss_mem));
	अगर (!dss.base) अणु
		DSSERR("can't ioremap DSS\n");
		वापस -ENOMEM;
	पूर्ण

	r = dss_get_घड़ीs();
	अगर (r)
		वापस r;

	r = dss_setup_शेष_घड़ी();
	अगर (r)
		जाओ err_setup_घड़ीs;

	r = dss_video_pll_probe(pdev);
	अगर (r)
		जाओ err_pll_init;

	r = dss_init_ports(pdev);
	अगर (r)
		जाओ err_init_ports;

	pm_runसमय_enable(&pdev->dev);

	r = dss_runसमय_get();
	अगर (r)
		जाओ err_runसमय_get;

	dss.dss_clk_rate = clk_get_rate(dss.dss_clk);

	/* Select DPLL */
	REG_FLD_MOD(DSS_CONTROL, 0, 0, 0);

	dss_select_dispc_clk_source(OMAP_DSS_CLK_SRC_FCK);

#अगर_घोषित CONFIG_FB_OMAP2_DSS_VENC
	REG_FLD_MOD(DSS_CONTROL, 1, 4, 4);	/* venc dac demen */
	REG_FLD_MOD(DSS_CONTROL, 1, 3, 3);	/* venc घड़ी 4x enable */
	REG_FLD_MOD(DSS_CONTROL, 0, 2, 2);	/* venc घड़ी mode = normal */
#पूर्ण_अगर
	dss.dsi_clk_source[0] = OMAP_DSS_CLK_SRC_FCK;
	dss.dsi_clk_source[1] = OMAP_DSS_CLK_SRC_FCK;
	dss.dispc_clk_source = OMAP_DSS_CLK_SRC_FCK;
	dss.lcd_clk_source[0] = OMAP_DSS_CLK_SRC_FCK;
	dss.lcd_clk_source[1] = OMAP_DSS_CLK_SRC_FCK;

	rev = dss_पढ़ो_reg(DSS_REVISION);
	prपूर्णांकk(KERN_INFO "OMAP DSS rev %d.%d\n",
			FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dss_runसमय_put();

	r = component_bind_all(&pdev->dev, शून्य);
	अगर (r)
		जाओ err_component;

	dss_debugfs_create_file("dss", dss_dump_regs);

	pm_set_vt_चयन(0);

	dss_initialized = true;

	वापस 0;

err_component:
err_runसमय_get:
	pm_runसमय_disable(&pdev->dev);
	dss_uninit_ports(pdev);
err_init_ports:
	अगर (dss.video1_pll)
		dss_video_pll_uninit(dss.video1_pll);

	अगर (dss.video2_pll)
		dss_video_pll_uninit(dss.video2_pll);
err_pll_init:
err_setup_घड़ीs:
	dss_put_घड़ीs();
	वापस r;
पूर्ण

अटल व्योम dss_unbind(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	dss_initialized = false;

	component_unbind_all(&pdev->dev, शून्य);

	अगर (dss.video1_pll)
		dss_video_pll_uninit(dss.video1_pll);

	अगर (dss.video2_pll)
		dss_video_pll_uninit(dss.video2_pll);

	dss_uninit_ports(pdev);

	pm_runसमय_disable(&pdev->dev);

	dss_put_घड़ीs();
पूर्ण

अटल स्थिर काष्ठा component_master_ops dss_component_ops = अणु
	.bind = dss_bind,
	.unbind = dss_unbind,
पूर्ण;

अटल पूर्णांक dss_component_compare(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device *child = data;
	वापस dev == child;
पूर्ण

अटल पूर्णांक dss_add_child_component(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा component_match **match = data;

	/*
	 * HACK
	 * We करोn't have a working driver क्रम rfbi, so skip it here always.
	 * Otherwise dss will never get probed successfully, as it will रुको
	 * क्रम rfbi to get probed.
	 */
	अगर (म_माला(dev_name(dev), "rfbi"))
		वापस 0;

	component_match_add(dev->parent, match, dss_component_compare, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	पूर्णांक r;

	/* add all the child devices as components */
	device_क्रम_each_child(&pdev->dev, &match, dss_add_child_component);

	r = component_master_add_with_match(&pdev->dev, &dss_component_ops, match);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक dss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &dss_component_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक dss_runसमय_suspend(काष्ठा device *dev)
अणु
	dss_save_context();
	dss_set_min_bus_tput(dev, 0);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक r;

	pinctrl_pm_select_शेष_state(dev);

	/*
	 * Set an arbitrarily high tput request to ensure OPP100.
	 * What we should really करो is to make a request to stay in OPP100,
	 * without any tput requirements, but that is not currently possible
	 * via the PM layer.
	 */

	r = dss_set_min_bus_tput(dev, 1000000000);
	अगर (r)
		वापस r;

	dss_restore_context();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dss_pm_ops = अणु
	.runसमय_suspend = dss_runसमय_suspend,
	.runसमय_resume = dss_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dss_of_match[] = अणु
	अणु .compatible = "ti,omap2-dss", पूर्ण,
	अणु .compatible = "ti,omap3-dss", पूर्ण,
	अणु .compatible = "ti,omap4-dss", पूर्ण,
	अणु .compatible = "ti,omap5-dss", पूर्ण,
	अणु .compatible = "ti,dra7-dss", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dss_of_match);

अटल काष्ठा platक्रमm_driver omap_dsshw_driver = अणु
	.probe		= dss_probe,
	.हटाओ		= dss_हटाओ,
	.driver         = अणु
		.name   = "omapdss_dss",
		.pm	= &dss_pm_ops,
		.of_match_table = dss_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init dss_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_dsshw_driver);
पूर्ण

व्योम dss_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_dsshw_driver);
पूर्ण
