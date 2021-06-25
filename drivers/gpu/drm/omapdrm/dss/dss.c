<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DSS"

#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/clk.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/gfp.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/suspend.h>
#समावेश <linux/component.h>
#समावेश <linux/sys_soc.h>

#समावेश "omapdss.h"
#समावेश "dss.h"

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

#घोषणा REG_GET(dss, idx, start, end) \
	FLD_GET(dss_पढ़ो_reg(dss, idx), start, end)

#घोषणा REG_FLD_MOD(dss, idx, val, start, end) \
	dss_ग_लिखो_reg(dss, idx, \
		      FLD_MOD(dss_पढ़ो_reg(dss, idx), val, start, end))

काष्ठा dss_ops अणु
	पूर्णांक (*dpi_select_source)(काष्ठा dss_device *dss, पूर्णांक port,
				 क्रमागत omap_channel channel);
	पूर्णांक (*select_lcd_source)(काष्ठा dss_device *dss,
				 क्रमागत omap_channel channel,
				 क्रमागत dss_clk_source clk_src);
पूर्ण;

काष्ठा dss_features अणु
	क्रमागत dss_model model;
	u8 fck_भाग_max;
	अचिन्हित पूर्णांक fck_freq_max;
	u8 dss_fck_multiplier;
	स्थिर अक्षर *parent_clk_name;
	स्थिर क्रमागत omap_display_type *ports;
	पूर्णांक num_ports;
	स्थिर क्रमागत omap_dss_output_id *outमाला_दो;
	स्थिर काष्ठा dss_ops *ops;
	काष्ठा dss_reg_field dispc_clk_चयन;
	bool has_lcd_clk_src;
पूर्ण;

अटल स्थिर अक्षर * स्थिर dss_generic_clk_source_names[] = अणु
	[DSS_CLK_SRC_FCK]	= "FCK",
	[DSS_CLK_SRC_PLL1_1]	= "PLL1:1",
	[DSS_CLK_SRC_PLL1_2]	= "PLL1:2",
	[DSS_CLK_SRC_PLL1_3]	= "PLL1:3",
	[DSS_CLK_SRC_PLL2_1]	= "PLL2:1",
	[DSS_CLK_SRC_PLL2_2]	= "PLL2:2",
	[DSS_CLK_SRC_PLL2_3]	= "PLL2:3",
	[DSS_CLK_SRC_HDMI_PLL]	= "HDMI PLL",
पूर्ण;

अटल अंतरभूत व्योम dss_ग_लिखो_reg(काष्ठा dss_device *dss,
				 स्थिर काष्ठा dss_reg idx, u32 val)
अणु
	__raw_ग_लिखोl(val, dss->base + idx.idx);
पूर्ण

अटल अंतरभूत u32 dss_पढ़ो_reg(काष्ठा dss_device *dss, स्थिर काष्ठा dss_reg idx)
अणु
	वापस __raw_पढ़ोl(dss->base + idx.idx);
पूर्ण

#घोषणा SR(dss, reg) \
	dss->ctx[(DSS_##reg).idx / माप(u32)] = dss_पढ़ो_reg(dss, DSS_##reg)
#घोषणा RR(dss, reg) \
	dss_ग_लिखो_reg(dss, DSS_##reg, dss->ctx[(DSS_##reg).idx / माप(u32)])

अटल व्योम dss_save_context(काष्ठा dss_device *dss)
अणु
	DSSDBG("dss_save_context\n");

	SR(dss, CONTROL);

	अगर (dss->feat->outमाला_दो[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) अणु
		SR(dss, SDI_CONTROL);
		SR(dss, PLL_CONTROL);
	पूर्ण

	dss->ctx_valid = true;

	DSSDBG("context saved\n");
पूर्ण

अटल व्योम dss_restore_context(काष्ठा dss_device *dss)
अणु
	DSSDBG("dss_restore_context\n");

	अगर (!dss->ctx_valid)
		वापस;

	RR(dss, CONTROL);

	अगर (dss->feat->outमाला_दो[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) अणु
		RR(dss, SDI_CONTROL);
		RR(dss, PLL_CONTROL);
	पूर्ण

	DSSDBG("context restored\n");
पूर्ण

#अघोषित SR
#अघोषित RR

व्योम dss_ctrl_pll_enable(काष्ठा dss_pll *pll, bool enable)
अणु
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक val;

	अगर (!pll->dss->syscon_pll_ctrl)
		वापस;

	val = !enable;

	चयन (pll->id) अणु
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
		DSSERR("illegal DSS PLL ID %d\n", pll->id);
		वापस;
	पूर्ण

	regmap_update_bits(pll->dss->syscon_pll_ctrl,
			   pll->dss->syscon_pll_ctrl_offset,
			   1 << shअगरt, val << shअगरt);
पूर्ण

अटल पूर्णांक dss_ctrl_pll_set_control_mux(काष्ठा dss_device *dss,
					क्रमागत dss_clk_source clk_src,
					क्रमागत omap_channel channel)
अणु
	अचिन्हित पूर्णांक shअगरt, val;

	अगर (!dss->syscon_pll_ctrl)
		वापस -EINVAL;

	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		shअगरt = 3;

		चयन (clk_src) अणु
		हाल DSS_CLK_SRC_PLL1_1:
			val = 0; अवरोध;
		हाल DSS_CLK_SRC_HDMI_PLL:
			val = 1; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD\n");
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD2:
		shअगरt = 5;

		चयन (clk_src) अणु
		हाल DSS_CLK_SRC_PLL1_3:
			val = 0; अवरोध;
		हाल DSS_CLK_SRC_PLL2_3:
			val = 1; अवरोध;
		हाल DSS_CLK_SRC_HDMI_PLL:
			val = 2; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD2\n");
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल OMAP_DSS_CHANNEL_LCD3:
		shअगरt = 7;

		चयन (clk_src) अणु
		हाल DSS_CLK_SRC_PLL2_1:
			val = 0; अवरोध;
		हाल DSS_CLK_SRC_PLL1_3:
			val = 1; अवरोध;
		हाल DSS_CLK_SRC_HDMI_PLL:
			val = 2; अवरोध;
		शेष:
			DSSERR("error in PLL mux config for LCD3\n");
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	शेष:
		DSSERR("error in PLL mux config\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(dss->syscon_pll_ctrl, dss->syscon_pll_ctrl_offset,
		0x3 << shअगरt, val << shअगरt);

	वापस 0;
पूर्ण

व्योम dss_sdi_init(काष्ठा dss_device *dss, पूर्णांक datapairs)
अणु
	u32 l;

	BUG_ON(datapairs > 3 || datapairs < 1);

	l = dss_पढ़ो_reg(dss, DSS_SDI_CONTROL);
	l = FLD_MOD(l, 0xf, 19, 15);		/* SDI_PDIV */
	l = FLD_MOD(l, datapairs-1, 3, 2);	/* SDI_PRSEL */
	l = FLD_MOD(l, 2, 1, 0);		/* SDI_BWSEL */
	dss_ग_लिखो_reg(dss, DSS_SDI_CONTROL, l);

	l = dss_पढ़ो_reg(dss, DSS_PLL_CONTROL);
	l = FLD_MOD(l, 0x7, 25, 22);	/* SDI_PLL_FREQSEL */
	l = FLD_MOD(l, 0xb, 16, 11);	/* SDI_PLL_REGN */
	l = FLD_MOD(l, 0xb4, 10, 1);	/* SDI_PLL_REGM */
	dss_ग_लिखो_reg(dss, DSS_PLL_CONTROL, l);
पूर्ण

पूर्णांक dss_sdi_enable(काष्ठा dss_device *dss)
अणु
	अचिन्हित दीर्घ समयout;

	dispc_pck_मुक्त_enable(dss->dispc, 1);

	/* Reset SDI PLL */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 1, 18, 18); /* SDI_PLL_SYSRESET */
	udelay(1);	/* रुको 2x PCLK */

	/* Lock SDI PLL */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 1, 28, 28); /* SDI_PLL_GOBIT */

	/* Waiting क्रम PLL lock request to complete */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (dss_पढ़ो_reg(dss, DSS_SDI_STATUS) & (1 << 6)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("PLL lock request timed out\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	/* Clearing PLL_GO bit */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 0, 28, 28);

	/* Waiting क्रम PLL to lock */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (!(dss_पढ़ो_reg(dss, DSS_SDI_STATUS) & (1 << 5))) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("PLL lock timed out\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	dispc_lcd_enable_संकेत(dss->dispc, 1);

	/* Waiting क्रम SDI reset to complete */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (!(dss_पढ़ो_reg(dss, DSS_SDI_STATUS) & (1 << 2))) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			DSSERR("SDI reset timed out\n");
			जाओ err2;
		पूर्ण
	पूर्ण

	वापस 0;

 err2:
	dispc_lcd_enable_संकेत(dss->dispc, 0);
 err1:
	/* Reset SDI PLL */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 0, 18, 18); /* SDI_PLL_SYSRESET */

	dispc_pck_मुक्त_enable(dss->dispc, 0);

	वापस -ETIMEDOUT;
पूर्ण

व्योम dss_sdi_disable(काष्ठा dss_device *dss)
अणु
	dispc_lcd_enable_संकेत(dss->dispc, 0);

	dispc_pck_मुक्त_enable(dss->dispc, 0);

	/* Reset SDI PLL */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 0, 18, 18); /* SDI_PLL_SYSRESET */
पूर्ण

स्थिर अक्षर *dss_get_clk_source_name(क्रमागत dss_clk_source clk_src)
अणु
	वापस dss_generic_clk_source_names[clk_src];
पूर्ण

अटल व्योम dss_dump_घड़ीs(काष्ठा dss_device *dss, काष्ठा seq_file *s)
अणु
	स्थिर अक्षर *fclk_name;
	अचिन्हित दीर्घ fclk_rate;

	अगर (dss_runसमय_get(dss))
		वापस;

	seq_म_लिखो(s, "- DSS -\n");

	fclk_name = dss_get_clk_source_name(DSS_CLK_SRC_FCK);
	fclk_rate = clk_get_rate(dss->dss_clk);

	seq_म_लिखो(s, "%s = %lu\n",
			fclk_name,
			fclk_rate);

	dss_runसमय_put(dss);
पूर्ण

अटल पूर्णांक dss_dump_regs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dss_device *dss = s->निजी;

#घोषणा DUMPREG(dss, r) seq_म_लिखो(s, "%-35s %08x\n", #r, dss_पढ़ो_reg(dss, r))

	अगर (dss_runसमय_get(dss))
		वापस 0;

	DUMPREG(dss, DSS_REVISION);
	DUMPREG(dss, DSS_SYSCONFIG);
	DUMPREG(dss, DSS_SYSSTATUS);
	DUMPREG(dss, DSS_CONTROL);

	अगर (dss->feat->outमाला_दो[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) अणु
		DUMPREG(dss, DSS_SDI_CONTROL);
		DUMPREG(dss, DSS_PLL_CONTROL);
		DUMPREG(dss, DSS_SDI_STATUS);
	पूर्ण

	dss_runसमय_put(dss);
#अघोषित DUMPREG
	वापस 0;
पूर्ण

अटल पूर्णांक dss_debug_dump_घड़ीs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dss_device *dss = s->निजी;

	dss_dump_घड़ीs(dss, s);
	dispc_dump_घड़ीs(dss->dispc, s);
	वापस 0;
पूर्ण

अटल पूर्णांक dss_get_channel_index(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 1;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 2;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम dss_select_dispc_clk_source(काष्ठा dss_device *dss,
					क्रमागत dss_clk_source clk_src)
अणु
	पूर्णांक b;

	/*
	 * We always use PRCM घड़ी as the DISPC func घड़ी, except on DSS3,
	 * where we करोn't have separate DISPC and LCD घड़ी sources.
	 */
	अगर (WARN_ON(dss->feat->has_lcd_clk_src && clk_src != DSS_CLK_SRC_FCK))
		वापस;

	चयन (clk_src) अणु
	हाल DSS_CLK_SRC_FCK:
		b = 0;
		अवरोध;
	हाल DSS_CLK_SRC_PLL1_1:
		b = 1;
		अवरोध;
	हाल DSS_CLK_SRC_PLL2_1:
		b = 2;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	REG_FLD_MOD(dss, DSS_CONTROL, b,		/* DISPC_CLK_SWITCH */
		    dss->feat->dispc_clk_चयन.start,
		    dss->feat->dispc_clk_चयन.end);

	dss->dispc_clk_source = clk_src;
पूर्ण

व्योम dss_select_dsi_clk_source(काष्ठा dss_device *dss, पूर्णांक dsi_module,
			       क्रमागत dss_clk_source clk_src)
अणु
	पूर्णांक b, pos;

	चयन (clk_src) अणु
	हाल DSS_CLK_SRC_FCK:
		b = 0;
		अवरोध;
	हाल DSS_CLK_SRC_PLL1_2:
		BUG_ON(dsi_module != 0);
		b = 1;
		अवरोध;
	हाल DSS_CLK_SRC_PLL2_2:
		BUG_ON(dsi_module != 1);
		b = 1;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	pos = dsi_module == 0 ? 1 : 10;
	REG_FLD_MOD(dss, DSS_CONTROL, b, pos, pos);	/* DSIx_CLK_SWITCH */

	dss->dsi_clk_source[dsi_module] = clk_src;
पूर्ण

अटल पूर्णांक dss_lcd_clk_mux_dra7(काष्ठा dss_device *dss,
				क्रमागत omap_channel channel,
				क्रमागत dss_clk_source clk_src)
अणु
	स्थिर u8 ctrl_bits[] = अणु
		[OMAP_DSS_CHANNEL_LCD] = 0,
		[OMAP_DSS_CHANNEL_LCD2] = 12,
		[OMAP_DSS_CHANNEL_LCD3] = 19,
	पूर्ण;

	u8 ctrl_bit = ctrl_bits[channel];
	पूर्णांक r;

	अगर (clk_src == DSS_CLK_SRC_FCK) अणु
		/* LCDx_CLK_SWITCH */
		REG_FLD_MOD(dss, DSS_CONTROL, 0, ctrl_bit, ctrl_bit);
		वापस -EINVAL;
	पूर्ण

	r = dss_ctrl_pll_set_control_mux(dss, clk_src, channel);
	अगर (r)
		वापस r;

	REG_FLD_MOD(dss, DSS_CONTROL, 1, ctrl_bit, ctrl_bit);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_lcd_clk_mux_omap5(काष्ठा dss_device *dss,
				 क्रमागत omap_channel channel,
				 क्रमागत dss_clk_source clk_src)
अणु
	स्थिर u8 ctrl_bits[] = अणु
		[OMAP_DSS_CHANNEL_LCD] = 0,
		[OMAP_DSS_CHANNEL_LCD2] = 12,
		[OMAP_DSS_CHANNEL_LCD3] = 19,
	पूर्ण;
	स्थिर क्रमागत dss_clk_source allowed_plls[] = अणु
		[OMAP_DSS_CHANNEL_LCD] = DSS_CLK_SRC_PLL1_1,
		[OMAP_DSS_CHANNEL_LCD2] = DSS_CLK_SRC_FCK,
		[OMAP_DSS_CHANNEL_LCD3] = DSS_CLK_SRC_PLL2_1,
	पूर्ण;

	u8 ctrl_bit = ctrl_bits[channel];

	अगर (clk_src == DSS_CLK_SRC_FCK) अणु
		/* LCDx_CLK_SWITCH */
		REG_FLD_MOD(dss, DSS_CONTROL, 0, ctrl_bit, ctrl_bit);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(allowed_plls[channel] != clk_src))
		वापस -EINVAL;

	REG_FLD_MOD(dss, DSS_CONTROL, 1, ctrl_bit, ctrl_bit);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_lcd_clk_mux_omap4(काष्ठा dss_device *dss,
				 क्रमागत omap_channel channel,
				 क्रमागत dss_clk_source clk_src)
अणु
	स्थिर u8 ctrl_bits[] = अणु
		[OMAP_DSS_CHANNEL_LCD] = 0,
		[OMAP_DSS_CHANNEL_LCD2] = 12,
	पूर्ण;
	स्थिर क्रमागत dss_clk_source allowed_plls[] = अणु
		[OMAP_DSS_CHANNEL_LCD] = DSS_CLK_SRC_PLL1_1,
		[OMAP_DSS_CHANNEL_LCD2] = DSS_CLK_SRC_PLL2_1,
	पूर्ण;

	u8 ctrl_bit = ctrl_bits[channel];

	अगर (clk_src == DSS_CLK_SRC_FCK) अणु
		/* LCDx_CLK_SWITCH */
		REG_FLD_MOD(dss, DSS_CONTROL, 0, ctrl_bit, ctrl_bit);
		वापस 0;
	पूर्ण

	अगर (WARN_ON(allowed_plls[channel] != clk_src))
		वापस -EINVAL;

	REG_FLD_MOD(dss, DSS_CONTROL, 1, ctrl_bit, ctrl_bit);

	वापस 0;
पूर्ण

व्योम dss_select_lcd_clk_source(काष्ठा dss_device *dss,
			       क्रमागत omap_channel channel,
			       क्रमागत dss_clk_source clk_src)
अणु
	पूर्णांक idx = dss_get_channel_index(channel);
	पूर्णांक r;

	अगर (!dss->feat->has_lcd_clk_src) अणु
		dss_select_dispc_clk_source(dss, clk_src);
		dss->lcd_clk_source[idx] = clk_src;
		वापस;
	पूर्ण

	r = dss->feat->ops->select_lcd_source(dss, channel, clk_src);
	अगर (r)
		वापस;

	dss->lcd_clk_source[idx] = clk_src;
पूर्ण

क्रमागत dss_clk_source dss_get_dispc_clk_source(काष्ठा dss_device *dss)
अणु
	वापस dss->dispc_clk_source;
पूर्ण

क्रमागत dss_clk_source dss_get_dsi_clk_source(काष्ठा dss_device *dss,
					   पूर्णांक dsi_module)
अणु
	वापस dss->dsi_clk_source[dsi_module];
पूर्ण

क्रमागत dss_clk_source dss_get_lcd_clk_source(काष्ठा dss_device *dss,
					   क्रमागत omap_channel channel)
अणु
	अगर (dss->feat->has_lcd_clk_src) अणु
		पूर्णांक idx = dss_get_channel_index(channel);
		वापस dss->lcd_clk_source[idx];
	पूर्ण अन्यथा अणु
		/* LCD_CLK source is the same as DISPC_FCLK source क्रम
		 * OMAP2 and OMAP3 */
		वापस dss->dispc_clk_source;
	पूर्ण
पूर्ण

bool dss_भाग_calc(काष्ठा dss_device *dss, अचिन्हित दीर्घ pck,
		  अचिन्हित दीर्घ fck_min, dss_भाग_calc_func func, व्योम *data)
अणु
	पूर्णांक fckd, fckd_start, fckd_stop;
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ fck_hw_max;
	अचिन्हित दीर्घ fckd_hw_max;
	अचिन्हित दीर्घ prate;
	अचिन्हित पूर्णांक m;

	fck_hw_max = dss->feat->fck_freq_max;

	अगर (dss->parent_clk == शून्य) अणु
		अचिन्हित पूर्णांक pckd;

		pckd = fck_hw_max / pck;

		fck = pck * pckd;

		fck = clk_round_rate(dss->dss_clk, fck);

		वापस func(fck, data);
	पूर्ण

	fckd_hw_max = dss->feat->fck_भाग_max;

	m = dss->feat->dss_fck_multiplier;
	prate = clk_get_rate(dss->parent_clk);

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

पूर्णांक dss_set_fck_rate(काष्ठा dss_device *dss, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक r;

	DSSDBG("set fck to %lu\n", rate);

	r = clk_set_rate(dss->dss_clk, rate);
	अगर (r)
		वापस r;

	dss->dss_clk_rate = clk_get_rate(dss->dss_clk);

	WARN_ONCE(dss->dss_clk_rate != rate, "clk rate mismatch: %lu != %lu",
		  dss->dss_clk_rate, rate);

	वापस 0;
पूर्ण

अचिन्हित दीर्घ dss_get_dispc_clk_rate(काष्ठा dss_device *dss)
अणु
	वापस dss->dss_clk_rate;
पूर्ण

अचिन्हित दीर्घ dss_get_max_fck_rate(काष्ठा dss_device *dss)
अणु
	वापस dss->feat->fck_freq_max;
पूर्ण

अटल पूर्णांक dss_setup_शेष_घड़ी(काष्ठा dss_device *dss)
अणु
	अचिन्हित दीर्घ max_dss_fck, prate;
	अचिन्हित दीर्घ fck;
	अचिन्हित पूर्णांक fck_भाग;
	पूर्णांक r;

	max_dss_fck = dss->feat->fck_freq_max;

	अगर (dss->parent_clk == शून्य) अणु
		fck = clk_round_rate(dss->dss_clk, max_dss_fck);
	पूर्ण अन्यथा अणु
		prate = clk_get_rate(dss->parent_clk);

		fck_भाग = DIV_ROUND_UP(prate * dss->feat->dss_fck_multiplier,
				max_dss_fck);
		fck = DIV_ROUND_UP(prate, fck_भाग)
		    * dss->feat->dss_fck_multiplier;
	पूर्ण

	r = dss_set_fck_rate(dss, fck);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

व्योम dss_set_venc_output(काष्ठा dss_device *dss, क्रमागत omap_dss_venc_type type)
अणु
	पूर्णांक l = 0;

	अगर (type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l = 0;
	अन्यथा अगर (type == OMAP_DSS_VENC_TYPE_SVIDEO)
		l = 1;
	अन्यथा
		BUG();

	/* venc out selection. 0 = comp, 1 = svideo */
	REG_FLD_MOD(dss, DSS_CONTROL, l, 6, 6);
पूर्ण

व्योम dss_set_dac_pwrdn_bgz(काष्ठा dss_device *dss, bool enable)
अणु
	/* DAC Power-Down Control */
	REG_FLD_MOD(dss, DSS_CONTROL, enable, 5, 5);
पूर्ण

व्योम dss_select_hdmi_venc_clk_source(काष्ठा dss_device *dss,
				     क्रमागत dss_hdmi_venc_clk_source_select src)
अणु
	क्रमागत omap_dss_output_id outमाला_दो;

	outमाला_दो = dss->feat->outमाला_दो[OMAP_DSS_CHANNEL_DIGIT];

	/* Complain about invalid selections */
	WARN_ON((src == DSS_VENC_TV_CLK) && !(outमाला_दो & OMAP_DSS_OUTPUT_VENC));
	WARN_ON((src == DSS_HDMI_M_PCLK) && !(outमाला_दो & OMAP_DSS_OUTPUT_HDMI));

	/* Select only अगर we have options */
	अगर ((outमाला_दो & OMAP_DSS_OUTPUT_VENC) &&
	    (outमाला_दो & OMAP_DSS_OUTPUT_HDMI))
		/* VENC_HDMI_SWITCH */
		REG_FLD_MOD(dss, DSS_CONTROL, src, 15, 15);
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap2_omap3(काष्ठा dss_device *dss, पूर्णांक port,
					     क्रमागत omap_channel channel)
अणु
	अगर (channel != OMAP_DSS_CHANNEL_LCD)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap4(काष्ठा dss_device *dss, पूर्णांक port,
				       क्रमागत omap_channel channel)
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

	REG_FLD_MOD(dss, DSS_CONTROL, val, 17, 17);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_omap5(काष्ठा dss_device *dss, पूर्णांक port,
				       क्रमागत omap_channel channel)
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

	REG_FLD_MOD(dss, DSS_CONTROL, val, 17, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_dpi_select_source_dra7xx(काष्ठा dss_device *dss, पूर्णांक port,
					क्रमागत omap_channel channel)
अणु
	चयन (port) अणु
	हाल 0:
		वापस dss_dpi_select_source_omap5(dss, port, channel);
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

पूर्णांक dss_dpi_select_source(काष्ठा dss_device *dss, पूर्णांक port,
			  क्रमागत omap_channel channel)
अणु
	वापस dss->feat->ops->dpi_select_source(dss, port, channel);
पूर्ण

अटल पूर्णांक dss_get_घड़ीs(काष्ठा dss_device *dss)
अणु
	काष्ठा clk *clk;

	clk = devm_clk_get(&dss->pdev->dev, "fck");
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get clock fck\n");
		वापस PTR_ERR(clk);
	पूर्ण

	dss->dss_clk = clk;

	अगर (dss->feat->parent_clk_name) अणु
		clk = clk_get(शून्य, dss->feat->parent_clk_name);
		अगर (IS_ERR(clk)) अणु
			DSSERR("Failed to get %s\n",
			       dss->feat->parent_clk_name);
			वापस PTR_ERR(clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk = शून्य;
	पूर्ण

	dss->parent_clk = clk;

	वापस 0;
पूर्ण

अटल व्योम dss_put_घड़ीs(काष्ठा dss_device *dss)
अणु
	अगर (dss->parent_clk)
		clk_put(dss->parent_clk);
पूर्ण

पूर्णांक dss_runसमय_get(काष्ठा dss_device *dss)
अणु
	पूर्णांक r;

	DSSDBG("dss_runtime_get\n");

	r = pm_runसमय_get_sync(&dss->pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_noidle(&dss->pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dss_runसमय_put(काष्ठा dss_device *dss)
अणु
	पूर्णांक r;

	DSSDBG("dss_runtime_put\n");

	r = pm_runसमय_put_sync(&dss->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS && r != -EBUSY);
पूर्ण

काष्ठा dss_device *dss_get_device(काष्ठा device *dev)
अणु
	वापस dev_get_drvdata(dev);
पूर्ण

/* DEBUGFS */
#अगर defined(CONFIG_OMAP2_DSS_DEBUGFS)
अटल पूर्णांक dss_initialize_debugfs(काष्ठा dss_device *dss)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("omapdss", शून्य);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	dss->debugfs.root = dir;

	वापस 0;
पूर्ण

अटल व्योम dss_uninitialize_debugfs(काष्ठा dss_device *dss)
अणु
	debugfs_हटाओ_recursive(dss->debugfs.root);
पूर्ण

काष्ठा dss_debugfs_entry अणु
	काष्ठा dentry *dentry;
	पूर्णांक (*show_fn)(काष्ठा seq_file *s, व्योम *data);
	व्योम *data;
पूर्ण;

अटल पूर्णांक dss_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dss_debugfs_entry *entry = inode->i_निजी;

	वापस single_खोलो(file, entry->show_fn, entry->data);
पूर्ण

अटल स्थिर काष्ठा file_operations dss_debug_fops = अणु
	.खोलो		= dss_debug_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

काष्ठा dss_debugfs_entry *
dss_debugfs_create_file(काष्ठा dss_device *dss, स्थिर अक्षर *name,
			पूर्णांक (*show_fn)(काष्ठा seq_file *s, व्योम *data),
			व्योम *data)
अणु
	काष्ठा dss_debugfs_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);

	entry->show_fn = show_fn;
	entry->data = data;
	entry->dentry = debugfs_create_file(name, 0444, dss->debugfs.root,
					    entry, &dss_debug_fops);

	वापस entry;
पूर्ण

व्योम dss_debugfs_हटाओ_file(काष्ठा dss_debugfs_entry *entry)
अणु
	अगर (IS_ERR_OR_शून्य(entry))
		वापस;

	debugfs_हटाओ(entry->dentry);
	kमुक्त(entry);
पूर्ण

#अन्यथा /* CONFIG_OMAP2_DSS_DEBUGFS */
अटल अंतरभूत पूर्णांक dss_initialize_debugfs(काष्ठा dss_device *dss)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dss_uninitialize_debugfs(काष्ठा dss_device *dss)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_OMAP2_DSS_DEBUGFS */

अटल स्थिर काष्ठा dss_ops dss_ops_omap2_omap3 = अणु
	.dpi_select_source = &dss_dpi_select_source_omap2_omap3,
पूर्ण;

अटल स्थिर काष्ठा dss_ops dss_ops_omap4 = अणु
	.dpi_select_source = &dss_dpi_select_source_omap4,
	.select_lcd_source = &dss_lcd_clk_mux_omap4,
पूर्ण;

अटल स्थिर काष्ठा dss_ops dss_ops_omap5 = अणु
	.dpi_select_source = &dss_dpi_select_source_omap5,
	.select_lcd_source = &dss_lcd_clk_mux_omap5,
पूर्ण;

अटल स्थिर काष्ठा dss_ops dss_ops_dra7 = अणु
	.dpi_select_source = &dss_dpi_select_source_dra7xx,
	.select_lcd_source = &dss_lcd_clk_mux_dra7,
पूर्ण;

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

अटल स्थिर क्रमागत omap_dss_output_id omap2_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap3430_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_SDI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap3630_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id am43xx_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap4_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DBI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC | OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap5_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1 | OMAP_DSS_OUTPUT_DSI2,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_LCD3 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap24xx_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP2,
	/*
	 * fck भाग max is really 16, but the भागider range has gaps. The range
	 * from 1 to 6 has no gaps, so let's use that as a max.
	 */
	.fck_भाग_max		=	6,
	.fck_freq_max		=	133000000,
	.dss_fck_multiplier	=	2,
	.parent_clk_name	=	"core_ck",
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
	.outमाला_दो		=	omap2_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_omap2_omap3,
	.dispc_clk_चयन	=	अणु 0, 0 पूर्ण,
	.has_lcd_clk_src	=	false,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap34xx_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP3,
	.fck_भाग_max		=	16,
	.fck_freq_max		=	173000000,
	.dss_fck_multiplier	=	2,
	.parent_clk_name	=	"dpll4_ck",
	.ports			=	omap34xx_ports,
	.outमाला_दो		=	omap3430_dss_supported_outमाला_दो,
	.num_ports		=	ARRAY_SIZE(omap34xx_ports),
	.ops			=	&dss_ops_omap2_omap3,
	.dispc_clk_चयन	=	अणु 0, 0 पूर्ण,
	.has_lcd_clk_src	=	false,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap3630_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP3,
	.fck_भाग_max		=	31,
	.fck_freq_max		=	173000000,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll4_ck",
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
	.outमाला_दो		=	omap3630_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_omap2_omap3,
	.dispc_clk_चयन	=	अणु 0, 0 पूर्ण,
	.has_lcd_clk_src	=	false,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap44xx_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP4,
	.fck_भाग_max		=	32,
	.fck_freq_max		=	186000000,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
	.outमाला_दो		=	omap4_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_omap4,
	.dispc_clk_चयन	=	अणु 9, 8 पूर्ण,
	.has_lcd_clk_src	=	true,
पूर्ण;

अटल स्थिर काष्ठा dss_features omap54xx_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP5,
	.fck_भाग_max		=	64,
	.fck_freq_max		=	209250000,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
	.outमाला_दो		=	omap5_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_omap5,
	.dispc_clk_चयन	=	अणु 9, 7 पूर्ण,
	.has_lcd_clk_src	=	true,
पूर्ण;

अटल स्थिर काष्ठा dss_features am43xx_dss_feats = अणु
	.model			=	DSS_MODEL_OMAP3,
	.fck_भाग_max		=	0,
	.fck_freq_max		=	200000000,
	.dss_fck_multiplier	=	0,
	.parent_clk_name	=	शून्य,
	.ports			=	omap2plus_ports,
	.num_ports		=	ARRAY_SIZE(omap2plus_ports),
	.outमाला_दो		=	am43xx_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_omap2_omap3,
	.dispc_clk_चयन	=	अणु 0, 0 पूर्ण,
	.has_lcd_clk_src	=	true,
पूर्ण;

अटल स्थिर काष्ठा dss_features dra7xx_dss_feats = अणु
	.model			=	DSS_MODEL_DRA7,
	.fck_भाग_max		=	64,
	.fck_freq_max		=	209250000,
	.dss_fck_multiplier	=	1,
	.parent_clk_name	=	"dpll_per_x2_ck",
	.ports			=	dra7xx_ports,
	.num_ports		=	ARRAY_SIZE(dra7xx_ports),
	.outमाला_दो		=	omap5_dss_supported_outमाला_दो,
	.ops			=	&dss_ops_dra7,
	.dispc_clk_चयन	=	अणु 9, 7 पूर्ण,
	.has_lcd_clk_src	=	true,
पूर्ण;

अटल व्योम __dss_uninit_ports(काष्ठा dss_device *dss, अचिन्हित पूर्णांक num_ports)
अणु
	काष्ठा platक्रमm_device *pdev = dss->pdev;
	काष्ठा device_node *parent = pdev->dev.of_node;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_ports; i++) अणु
		port = of_graph_get_port_by_id(parent, i);
		अगर (!port)
			जारी;

		चयन (dss->feat->ports[i]) अणु
		हाल OMAP_DISPLAY_TYPE_DPI:
			dpi_uninit_port(port);
			अवरोध;
		हाल OMAP_DISPLAY_TYPE_SDI:
			sdi_uninit_port(port);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dss_init_ports(काष्ठा dss_device *dss)
अणु
	काष्ठा platक्रमm_device *pdev = dss->pdev;
	काष्ठा device_node *parent = pdev->dev.of_node;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < dss->feat->num_ports; i++) अणु
		port = of_graph_get_port_by_id(parent, i);
		अगर (!port)
			जारी;

		चयन (dss->feat->ports[i]) अणु
		हाल OMAP_DISPLAY_TYPE_DPI:
			r = dpi_init_port(dss, pdev, port, dss->feat->model);
			अगर (r)
				जाओ error;
			अवरोध;

		हाल OMAP_DISPLAY_TYPE_SDI:
			r = sdi_init_port(dss, pdev, port);
			अगर (r)
				जाओ error;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	__dss_uninit_ports(dss, i);
	वापस r;
पूर्ण

अटल व्योम dss_uninit_ports(काष्ठा dss_device *dss)
अणु
	__dss_uninit_ports(dss, dss->feat->num_ports);
पूर्ण

अटल पूर्णांक dss_video_pll_probe(काष्ठा dss_device *dss)
अणु
	काष्ठा platक्रमm_device *pdev = dss->pdev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regulator *pll_regulator;
	पूर्णांक r;

	अगर (!np)
		वापस 0;

	अगर (of_property_पढ़ो_bool(np, "syscon-pll-ctrl")) अणु
		dss->syscon_pll_ctrl = syscon_regmap_lookup_by_phandle(np,
			"syscon-pll-ctrl");
		अगर (IS_ERR(dss->syscon_pll_ctrl)) अणु
			dev_err(&pdev->dev,
				"failed to get syscon-pll-ctrl regmap\n");
			वापस PTR_ERR(dss->syscon_pll_ctrl);
		पूर्ण

		अगर (of_property_पढ़ो_u32_index(np, "syscon-pll-ctrl", 1,
				&dss->syscon_pll_ctrl_offset)) अणु
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
		dss->video1_pll = dss_video_pll_init(dss, pdev, 0,
						     pll_regulator);
		अगर (IS_ERR(dss->video1_pll))
			वापस PTR_ERR(dss->video1_pll);
	पूर्ण

	अगर (of_property_match_string(np, "reg-names", "pll2") >= 0) अणु
		dss->video2_pll = dss_video_pll_init(dss, pdev, 1,
						     pll_regulator);
		अगर (IS_ERR(dss->video2_pll)) अणु
			dss_video_pll_uninit(dss->video1_pll);
			वापस PTR_ERR(dss->video2_pll);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* DSS HW IP initialisation */
अटल स्थिर काष्ठा of_device_id dss_of_match[] = अणु
	अणु .compatible = "ti,omap2-dss", .data = &omap24xx_dss_feats पूर्ण,
	अणु .compatible = "ti,omap3-dss", .data = &omap3630_dss_feats पूर्ण,
	अणु .compatible = "ti,omap4-dss", .data = &omap44xx_dss_feats पूर्ण,
	अणु .compatible = "ti,omap5-dss", .data = &omap54xx_dss_feats पूर्ण,
	अणु .compatible = "ti,dra7-dss",  .data = &dra7xx_dss_feats पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dss_of_match);

अटल स्थिर काष्ठा soc_device_attribute dss_soc_devices[] = अणु
	अणु .machine = "OMAP3430/3530", .data = &omap34xx_dss_feats पूर्ण,
	अणु .machine = "AM35??",        .data = &omap34xx_dss_feats पूर्ण,
	अणु .family  = "AM43xx",        .data = &am43xx_dss_feats पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक dss_bind(काष्ठा device *dev)
अणु
	काष्ठा dss_device *dss = dev_get_drvdata(dev);
	काष्ठा platक्रमm_device *drm_pdev;
	काष्ठा dss_pdata pdata;
	पूर्णांक r;

	r = component_bind_all(dev, शून्य);
	अगर (r)
		वापस r;

	pm_set_vt_चयन(0);

	pdata.dss = dss;
	drm_pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "omapdrm", 0,
						 &pdata, माप(pdata));
	अगर (IS_ERR(drm_pdev)) अणु
		component_unbind_all(dev, शून्य);
		वापस PTR_ERR(drm_pdev);
	पूर्ण

	dss->drm_pdev = drm_pdev;

	वापस 0;
पूर्ण

अटल व्योम dss_unbind(काष्ठा device *dev)
अणु
	काष्ठा dss_device *dss = dev_get_drvdata(dev);

	platक्रमm_device_unरेजिस्टर(dss->drm_pdev);

	component_unbind_all(dev, शून्य);
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

काष्ठा dss_component_match_data अणु
	काष्ठा device *dev;
	काष्ठा component_match **match;
पूर्ण;

अटल पूर्णांक dss_add_child_component(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा dss_component_match_data *cmatch = data;
	काष्ठा component_match **match = cmatch->match;

	/*
	 * HACK
	 * We करोn't have a working driver क्रम rfbi, so skip it here always.
	 * Otherwise dss will never get probed successfully, as it will रुको
	 * क्रम rfbi to get probed.
	 */
	अगर (म_माला(dev_name(dev), "rfbi"))
		वापस 0;

	/*
	 * Handle possible पूर्णांकerconnect target modules defined within the DSS.
	 * The DSS components can be children of an पूर्णांकerconnect target module
	 * after the device tree has been updated क्रम the module data.
	 * See also omapdss_boot_init() क्रम compatible fixup.
	 */
	अगर (म_माला(dev_name(dev), "target-module"))
		वापस device_क्रम_each_child(dev, cmatch,
					     dss_add_child_component);

	component_match_add(cmatch->dev, match, dss_component_compare, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_probe_hardware(काष्ठा dss_device *dss)
अणु
	u32 rev;
	पूर्णांक r;

	r = dss_runसमय_get(dss);
	अगर (r)
		वापस r;

	dss->dss_clk_rate = clk_get_rate(dss->dss_clk);

	/* Select DPLL */
	REG_FLD_MOD(dss, DSS_CONTROL, 0, 0, 0);

	dss_select_dispc_clk_source(dss, DSS_CLK_SRC_FCK);

#अगर_घोषित CONFIG_OMAP2_DSS_VENC
	REG_FLD_MOD(dss, DSS_CONTROL, 1, 4, 4);	/* venc dac demen */
	REG_FLD_MOD(dss, DSS_CONTROL, 1, 3, 3);	/* venc घड़ी 4x enable */
	REG_FLD_MOD(dss, DSS_CONTROL, 0, 2, 2);	/* venc घड़ी mode = normal */
#पूर्ण_अगर
	dss->dsi_clk_source[0] = DSS_CLK_SRC_FCK;
	dss->dsi_clk_source[1] = DSS_CLK_SRC_FCK;
	dss->dispc_clk_source = DSS_CLK_SRC_FCK;
	dss->lcd_clk_source[0] = DSS_CLK_SRC_FCK;
	dss->lcd_clk_source[1] = DSS_CLK_SRC_FCK;

	rev = dss_पढ़ो_reg(dss, DSS_REVISION);
	pr_info("OMAP DSS rev %d.%d\n", FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dss_runसमय_put(dss);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा dss_component_match_data cmatch;
	काष्ठा component_match *match = शून्य;
	काष्ठा resource *dss_mem;
	काष्ठा dss_device *dss;
	पूर्णांक r;

	dss = kzalloc(माप(*dss), GFP_KERNEL);
	अगर (!dss)
		वापस -ENOMEM;

	dss->pdev = pdev;
	platक्रमm_set_drvdata(pdev, dss);

	r = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to set the DMA mask\n");
		जाओ err_मुक्त_dss;
	पूर्ण

	/*
	 * The various OMAP3-based SoCs can't be told apart using the compatible
	 * string, use SoC device matching.
	 */
	soc = soc_device_match(dss_soc_devices);
	अगर (soc)
		dss->feat = soc->data;
	अन्यथा
		dss->feat = of_match_device(dss_of_match, &pdev->dev)->data;

	/* Map I/O रेजिस्टरs, get and setup घड़ीs. */
	dss_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dss->base = devm_ioremap_resource(&pdev->dev, dss_mem);
	अगर (IS_ERR(dss->base)) अणु
		r = PTR_ERR(dss->base);
		जाओ err_मुक्त_dss;
	पूर्ण

	r = dss_get_घड़ीs(dss);
	अगर (r)
		जाओ err_मुक्त_dss;

	r = dss_setup_शेष_घड़ी(dss);
	अगर (r)
		जाओ err_put_घड़ीs;

	/* Setup the video PLLs and the DPI and SDI ports. */
	r = dss_video_pll_probe(dss);
	अगर (r)
		जाओ err_put_घड़ीs;

	r = dss_init_ports(dss);
	अगर (r)
		जाओ err_uninit_plls;

	/* Enable runसमय PM and probe the hardware. */
	pm_runसमय_enable(&pdev->dev);

	r = dss_probe_hardware(dss);
	अगर (r)
		जाओ err_pm_runसमय_disable;

	/* Initialize debugfs. */
	r = dss_initialize_debugfs(dss);
	अगर (r)
		जाओ err_pm_runसमय_disable;

	dss->debugfs.clk = dss_debugfs_create_file(dss, "clk",
						   dss_debug_dump_घड़ीs, dss);
	dss->debugfs.dss = dss_debugfs_create_file(dss, "dss", dss_dump_regs,
						   dss);

	/* Add all the child devices as components. */
	r = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (r)
		जाओ err_uninit_debugfs;

	omapdss_gather_components(&pdev->dev);

	cmatch.dev = &pdev->dev;
	cmatch.match = &match;
	device_क्रम_each_child(&pdev->dev, &cmatch, dss_add_child_component);

	r = component_master_add_with_match(&pdev->dev, &dss_component_ops, match);
	अगर (r)
		जाओ err_of_depopulate;

	वापस 0;

err_of_depopulate:
	of_platक्रमm_depopulate(&pdev->dev);

err_uninit_debugfs:
	dss_debugfs_हटाओ_file(dss->debugfs.clk);
	dss_debugfs_हटाओ_file(dss->debugfs.dss);
	dss_uninitialize_debugfs(dss);

err_pm_runसमय_disable:
	pm_runसमय_disable(&pdev->dev);
	dss_uninit_ports(dss);

err_uninit_plls:
	अगर (dss->video1_pll)
		dss_video_pll_uninit(dss->video1_pll);
	अगर (dss->video2_pll)
		dss_video_pll_uninit(dss->video2_pll);

err_put_घड़ीs:
	dss_put_घड़ीs(dss);

err_मुक्त_dss:
	kमुक्त(dss);

	वापस r;
पूर्ण

अटल पूर्णांक dss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dss_device *dss = platक्रमm_get_drvdata(pdev);

	of_platक्रमm_depopulate(&pdev->dev);

	component_master_del(&pdev->dev, &dss_component_ops);

	dss_debugfs_हटाओ_file(dss->debugfs.clk);
	dss_debugfs_हटाओ_file(dss->debugfs.dss);
	dss_uninitialize_debugfs(dss);

	pm_runसमय_disable(&pdev->dev);

	dss_uninit_ports(dss);

	अगर (dss->video1_pll)
		dss_video_pll_uninit(dss->video1_pll);

	अगर (dss->video2_pll)
		dss_video_pll_uninit(dss->video2_pll);

	dss_put_घड़ीs(dss);

	kमुक्त(dss);

	वापस 0;
पूर्ण

अटल व्योम dss_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	DSSDBG("shutdown\n");
पूर्ण

अटल पूर्णांक dss_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dss_device *dss = dev_get_drvdata(dev);

	dss_save_context(dss);
	dss_set_min_bus_tput(dev, 0);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dss_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dss_device *dss = dev_get_drvdata(dev);
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

	dss_restore_context(dss);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dss_pm_ops = अणु
	.runसमय_suspend = dss_runसमय_suspend,
	.runसमय_resume = dss_runसमय_resume,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver omap_dsshw_driver = अणु
	.probe		= dss_probe,
	.हटाओ		= dss_हटाओ,
	.shutकरोwn	= dss_shutकरोwn,
	.driver         = अणु
		.name   = "omapdss_dss",
		.pm	= &dss_pm_ops,
		.of_match_table = dss_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

/* INIT */
अटल काष्ठा platक्रमm_driver * स्थिर omap_dss_drivers[] = अणु
	&omap_dsshw_driver,
	&omap_dispchw_driver,
#अगर_घोषित CONFIG_OMAP2_DSS_DSI
	&omap_dsihw_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP2_DSS_VENC
	&omap_venchw_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP4_DSS_HDMI
	&omapdss_hdmi4hw_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP5_DSS_HDMI
	&omapdss_hdmi5hw_driver,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init omap_dss_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(omap_dss_drivers,
					 ARRAY_SIZE(omap_dss_drivers));
पूर्ण

व्योम omap_dss_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(omap_dss_drivers,
				    ARRAY_SIZE(omap_dss_drivers));
पूर्ण
