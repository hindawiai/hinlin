<शैली गुरु>
/*
 * OMAP2plus display device setup / initialization.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 *	Senthilvaभागu Guruswamy
 *	Sumit Semwal
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <linux/platक्रमm_data/omapdss.h>
#समावेश "omap_hwmod.h"
#समावेश "omap_device.h"
#समावेश "common.h"

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "control.h"
#समावेश "display.h"
#समावेश "prm.h"

#घोषणा DISPC_CONTROL		0x0040
#घोषणा DISPC_CONTROL2		0x0238
#घोषणा DISPC_CONTROL3		0x0848
#घोषणा DISPC_IRQSTATUS		0x0018

#घोषणा DSS_CONTROL		0x40
#घोषणा DSS_SDI_CONTROL		0x44
#घोषणा DSS_PLL_CONTROL		0x48

#घोषणा LCD_EN_MASK		(0x1 << 0)
#घोषणा DIGIT_EN_MASK		(0x1 << 1)

#घोषणा FRAMEDONE_IRQ_SHIFT	0
#घोषणा EVSYNC_EVEN_IRQ_SHIFT	2
#घोषणा EVSYNC_ODD_IRQ_SHIFT	3
#घोषणा FRAMEDONE2_IRQ_SHIFT	22
#घोषणा FRAMEDONE3_IRQ_SHIFT	30
#घोषणा FRAMEDONETV_IRQ_SHIFT	24

/*
 * FRAMEDONE_IRQ_TIMEOUT: how दीर्घ (in milliseconds) to रुको during DISPC
 *     reset beक्रमe deciding that something has gone wrong
 */
#घोषणा FRAMEDONE_IRQ_TIMEOUT		100

#अगर defined(CONFIG_FB_OMAP2)
अटल काष्ठा platक्रमm_device omap_display_device = अणु
	.name          = "omapdss",
	.id            = -1,
	.dev            = अणु
		.platक्रमm_data = शून्य,
	पूर्ण,
पूर्ण;

#घोषणा OMAP4_DSIPHY_SYSCON_OFFSET		0x78

अटल काष्ठा regmap *omap4_dsi_mux_syscon;

अटल पूर्णांक omap4_dsi_mux_pads(पूर्णांक dsi_id, अचिन्हित lanes)
अणु
	u32 enable_mask, enable_shअगरt;
	u32 pipd_mask, pipd_shअगरt;
	u32 reg;
	पूर्णांक ret;

	अगर (dsi_id == 0) अणु
		enable_mask = OMAP4_DSI1_LANEENABLE_MASK;
		enable_shअगरt = OMAP4_DSI1_LANEENABLE_SHIFT;
		pipd_mask = OMAP4_DSI1_PIPD_MASK;
		pipd_shअगरt = OMAP4_DSI1_PIPD_SHIFT;
	पूर्ण अन्यथा अगर (dsi_id == 1) अणु
		enable_mask = OMAP4_DSI2_LANEENABLE_MASK;
		enable_shअगरt = OMAP4_DSI2_LANEENABLE_SHIFT;
		pipd_mask = OMAP4_DSI2_PIPD_MASK;
		pipd_shअगरt = OMAP4_DSI2_PIPD_SHIFT;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(omap4_dsi_mux_syscon,
					  OMAP4_DSIPHY_SYSCON_OFFSET,
					  &reg);
	अगर (ret)
		वापस ret;

	reg &= ~enable_mask;
	reg &= ~pipd_mask;

	reg |= (lanes << enable_shअगरt) & enable_mask;
	reg |= (lanes << pipd_shअगरt) & pipd_mask;

	regmap_ग_लिखो(omap4_dsi_mux_syscon, OMAP4_DSIPHY_SYSCON_OFFSET, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dsi_enable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask)
अणु
	अगर (cpu_is_omap44xx())
		वापस omap4_dsi_mux_pads(dsi_id, lane_mask);

	वापस 0;
पूर्ण

अटल व्योम omap_dsi_disable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask)
अणु
	अगर (cpu_is_omap44xx())
		omap4_dsi_mux_pads(dsi_id, 0);
पूर्ण

अटल क्रमागत omapdss_version __init omap_display_get_version(व्योम)
अणु
	अगर (cpu_is_omap24xx())
		वापस OMAPDSS_VER_OMAP24xx;
	अन्यथा अगर (cpu_is_omap3630())
		वापस OMAPDSS_VER_OMAP3630;
	अन्यथा अगर (cpu_is_omap34xx()) अणु
		अगर (soc_is_am35xx()) अणु
			वापस OMAPDSS_VER_AM35xx;
		पूर्ण अन्यथा अणु
			अगर (omap_rev() < OMAP3430_REV_ES3_0)
				वापस OMAPDSS_VER_OMAP34xx_ES1;
			अन्यथा
				वापस OMAPDSS_VER_OMAP34xx_ES3;
		पूर्ण
	पूर्ण अन्यथा अगर (omap_rev() == OMAP4430_REV_ES1_0)
		वापस OMAPDSS_VER_OMAP4430_ES1;
	अन्यथा अगर (omap_rev() == OMAP4430_REV_ES2_0 ||
			omap_rev() == OMAP4430_REV_ES2_1 ||
			omap_rev() == OMAP4430_REV_ES2_2)
		वापस OMAPDSS_VER_OMAP4430_ES2;
	अन्यथा अगर (cpu_is_omap44xx())
		वापस OMAPDSS_VER_OMAP4;
	अन्यथा अगर (soc_is_omap54xx())
		वापस OMAPDSS_VER_OMAP5;
	अन्यथा अगर (soc_is_am43xx())
		वापस OMAPDSS_VER_AM43xx;
	अन्यथा अगर (soc_is_dra7xx())
		वापस OMAPDSS_VER_DRA7xx;
	अन्यथा
		वापस OMAPDSS_VER_UNKNOWN;
पूर्ण

अटल पूर्णांक __init omapdss_init_fbdev(व्योम)
अणु
	अटल काष्ठा omap_dss_board_info board_data = अणु
		.dsi_enable_pads = omap_dsi_enable_pads,
		.dsi_disable_pads = omap_dsi_disable_pads,
	पूर्ण;
	काष्ठा device_node *node;
	पूर्णांक r;

	board_data.version = omap_display_get_version();
	अगर (board_data.version == OMAPDSS_VER_UNKNOWN) अणु
		pr_err("DSS not supported on this SoC\n");
		वापस -ENODEV;
	पूर्ण

	omap_display_device.dev.platक्रमm_data = &board_data;

	r = platक्रमm_device_रेजिस्टर(&omap_display_device);
	अगर (r < 0) अणु
		pr_err("Unable to register omapdss device\n");
		वापस r;
	पूर्ण

	/* create vrfb device */
	r = omap_init_vrfb();
	अगर (r < 0) अणु
		pr_err("Unable to register omapvrfb device\n");
		वापस r;
	पूर्ण

	/* create FB device */
	r = omap_init_fb();
	अगर (r < 0) अणु
		pr_err("Unable to register omapfb device\n");
		वापस r;
	पूर्ण

	/* create V4L2 display device */
	r = omap_init_vout();
	अगर (r < 0) अणु
		pr_err("Unable to register omap_vout device\n");
		वापस r;
	पूर्ण

	/* add DSI info क्रम omap4 */
	node = of_find_node_by_name(शून्य, "omap4_padconf_global");
	अगर (node)
		omap4_dsi_mux_syscon = syscon_node_to_regmap(node);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर omapdss_compat_names[] __initस्थिर = अणु
	"ti,omap2-dss",
	"ti,omap3-dss",
	"ti,omap4-dss",
	"ti,omap5-dss",
	"ti,dra7-dss",
पूर्ण;

अटल काष्ठा device_node * __init omapdss_find_dss_of_node(व्योम)
अणु
	काष्ठा device_node *node;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(omapdss_compat_names); ++i) अणु
		node = of_find_compatible_node(शून्य, शून्य,
			omapdss_compat_names[i]);
		अगर (node)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __init omapdss_init_of(व्योम)
अणु
	पूर्णांक r;
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;

	/* only create dss helper devices अगर dss is enabled in the .dts */

	node = omapdss_find_dss_of_node();
	अगर (!node)
		वापस 0;

	अगर (!of_device_is_available(node)) अणु
		of_node_put(node);
		वापस 0;
	पूर्ण

	pdev = of_find_device_by_node(node);

	अगर (!pdev) अणु
		pr_err("Unable to find DSS platform device\n");
		वापस -ENODEV;
	पूर्ण

	r = of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	अगर (r) अणु
		pr_err("Unable to populate DSS submodule devices\n");
		put_device(&pdev->dev);
		वापस r;
	पूर्ण

	वापस omapdss_init_fbdev();
पूर्ण
omap_device_initcall(omapdss_init_of);
#पूर्ण_अगर /* CONFIG_FB_OMAP2 */

अटल व्योम dispc_disable_outमाला_दो(व्योम)
अणु
	u32 v, irq_mask = 0;
	bool lcd_en, digit_en, lcd2_en = false, lcd3_en = false;
	पूर्णांक i;
	काष्ठा omap_dss_dispc_dev_attr *da;
	काष्ठा omap_hwmod *oh;

	oh = omap_hwmod_lookup("dss_dispc");
	अगर (!oh) अणु
		WARN(1, "display: could not disable outputs during reset - could not find dss_dispc hwmod\n");
		वापस;
	पूर्ण

	अगर (!oh->dev_attr) अणु
		pr_err("display: could not disable outputs during reset due to missing dev_attr\n");
		वापस;
	पूर्ण

	da = (काष्ठा omap_dss_dispc_dev_attr *)oh->dev_attr;

	/* store value of LCDENABLE and DIGITENABLE bits */
	v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL);
	lcd_en = v & LCD_EN_MASK;
	digit_en = v & DIGIT_EN_MASK;

	/* store value of LCDENABLE क्रम LCD2 */
	अगर (da->manager_count > 2) अणु
		v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL2);
		lcd2_en = v & LCD_EN_MASK;
	पूर्ण

	/* store value of LCDENABLE क्रम LCD3 */
	अगर (da->manager_count > 3) अणु
		v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL3);
		lcd3_en = v & LCD_EN_MASK;
	पूर्ण

	अगर (!(lcd_en | digit_en | lcd2_en | lcd3_en))
		वापस; /* no managers currently enabled */

	/*
	 * If any manager was enabled, we need to disable it beक्रमe
	 * DSS घड़ीs are disabled or DISPC module is reset
	 */
	अगर (lcd_en)
		irq_mask |= 1 << FRAMEDONE_IRQ_SHIFT;

	अगर (digit_en) अणु
		अगर (da->has_frameकरोnetv_irq) अणु
			irq_mask |= 1 << FRAMEDONETV_IRQ_SHIFT;
		पूर्ण अन्यथा अणु
			irq_mask |= 1 << EVSYNC_EVEN_IRQ_SHIFT |
				1 << EVSYNC_ODD_IRQ_SHIFT;
		पूर्ण
	पूर्ण

	अगर (lcd2_en)
		irq_mask |= 1 << FRAMEDONE2_IRQ_SHIFT;
	अगर (lcd3_en)
		irq_mask |= 1 << FRAMEDONE3_IRQ_SHIFT;

	/*
	 * clear any previous FRAMEDONE, FRAMEDONETV,
	 * EVSYNC_EVEN/ODD, FRAMEDONE2 or FRAMEDONE3 पूर्णांकerrupts
	 */
	omap_hwmod_ग_लिखो(irq_mask, oh, DISPC_IRQSTATUS);

	/* disable LCD and TV managers */
	v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL);
	v &= ~(LCD_EN_MASK | DIGIT_EN_MASK);
	omap_hwmod_ग_लिखो(v, oh, DISPC_CONTROL);

	/* disable LCD2 manager */
	अगर (da->manager_count > 2) अणु
		v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL2);
		v &= ~LCD_EN_MASK;
		omap_hwmod_ग_लिखो(v, oh, DISPC_CONTROL2);
	पूर्ण

	/* disable LCD3 manager */
	अगर (da->manager_count > 3) अणु
		v = omap_hwmod_पढ़ो(oh, DISPC_CONTROL3);
		v &= ~LCD_EN_MASK;
		omap_hwmod_ग_लिखो(v, oh, DISPC_CONTROL3);
	पूर्ण

	i = 0;
	जबतक ((omap_hwmod_पढ़ो(oh, DISPC_IRQSTATUS) & irq_mask) !=
	       irq_mask) अणु
		i++;
		अगर (i > FRAMEDONE_IRQ_TIMEOUT) अणु
			pr_err("didn't get FRAMEDONE1/2/3 or TV interrupt\n");
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण
पूर्ण

पूर्णांक omap_dss_reset(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_opt_clk *oc;
	पूर्णांक c = 0;
	पूर्णांक i, r;

	अगर (!(oh->class->sysc->sysc_flags & SYSS_HAS_RESET_STATUS)) अणु
		pr_err("dss_core: hwmod data doesn't contain reset data\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		clk_prepare_enable(oc->_clk);

	dispc_disable_outमाला_दो();

	/* clear SDI रेजिस्टरs */
	अगर (cpu_is_omap3430()) अणु
		omap_hwmod_ग_लिखो(0x0, oh, DSS_SDI_CONTROL);
		omap_hwmod_ग_लिखो(0x0, oh, DSS_PLL_CONTROL);
	पूर्ण

	/*
	 * clear DSS_CONTROL रेजिस्टर to चयन DSS घड़ी sources to
	 * PRCM घड़ी, अगर any
	 */
	omap_hwmod_ग_लिखो(0x0, oh, DSS_CONTROL);

	omap_test_समयout((omap_hwmod_पढ़ो(oh, oh->class->sysc->syss_offs)
				& SYSS_RESETDONE_MASK),
			MAX_MODULE_SOFTRESET_WAIT, c);

	अगर (c == MAX_MODULE_SOFTRESET_WAIT)
		pr_warn("dss_core: waiting for reset to finish failed\n");
	अन्यथा
		pr_debug("dss_core: softreset done\n");

	क्रम (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		clk_disable_unprepare(oc->_clk);

	r = (c == MAX_MODULE_SOFTRESET_WAIT) ? -ETIMEDOUT : 0;

	वापस r;
पूर्ण
