<शैली गुरु>
/*
 * Aपंचांगel SAMA5D2-Compatible Shutकरोwn Controller (SHDWC) driver.
 * Found on some SoCs as the sama5d2 (obviously).
 *
 * Copyright (C) 2015 Aपंचांगel Corporation,
 *                    Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *
 * Evolved from driver at91-घातeroff.c.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * TODO:
 * - addition to status of other wake-up inमाला_दो [1 - 15]
 * - Analog Comparator wake-up alarm
 * - Serial RX wake-up alarm
 * - low घातer debouncer
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <soc/at91/at91sam9_ddrsdr.h>

#घोषणा SLOW_CLOCK_FREQ	32768

#घोषणा AT91_SHDW_CR	0x00		/* Shut Down Control Register */
#घोषणा AT91_SHDW_SHDW		BIT(0)			/* Shut Down command */
#घोषणा AT91_SHDW_KEY		(0xa5UL << 24)		/* KEY Password */

#घोषणा AT91_SHDW_MR	0x04		/* Shut Down Mode Register */
#घोषणा AT91_SHDW_WKUPDBC_SHIFT	24
#घोषणा AT91_SHDW_WKUPDBC_MASK	GENMASK(26, 24)
#घोषणा AT91_SHDW_WKUPDBC(x)	(((x) << AT91_SHDW_WKUPDBC_SHIFT) \
						& AT91_SHDW_WKUPDBC_MASK)

#घोषणा AT91_SHDW_SR	0x08		/* Shut Down Status Register */
#घोषणा AT91_SHDW_WKUPIS_SHIFT	16
#घोषणा AT91_SHDW_WKUPIS_MASK	GENMASK(31, 16)
#घोषणा AT91_SHDW_WKUPIS(x)	((1 << (x)) << AT91_SHDW_WKUPIS_SHIFT \
						& AT91_SHDW_WKUPIS_MASK)

#घोषणा AT91_SHDW_WUIR	0x0c		/* Shutकरोwn Wake-up Inमाला_दो Register */
#घोषणा AT91_SHDW_WKUPEN_MASK	GENMASK(15, 0)
#घोषणा AT91_SHDW_WKUPEN(x)	((1 << (x)) & AT91_SHDW_WKUPEN_MASK)
#घोषणा AT91_SHDW_WKUPT_SHIFT	16
#घोषणा AT91_SHDW_WKUPT_MASK	GENMASK(31, 16)
#घोषणा AT91_SHDW_WKUPT(x)	((1 << (x)) << AT91_SHDW_WKUPT_SHIFT \
						& AT91_SHDW_WKUPT_MASK)

#घोषणा SHDW_WK_PIN(reg, cfg)	((reg) & AT91_SHDW_WKUPIS((cfg)->wkup_pin_input))
#घोषणा SHDW_RTCWK(reg, cfg)	(((reg) >> ((cfg)->sr_rtcwk_shअगरt)) & 0x1)
#घोषणा SHDW_RTTWK(reg, cfg)	(((reg) >> ((cfg)->sr_rttwk_shअगरt)) & 0x1)
#घोषणा SHDW_RTCWKEN(cfg)	(1 << ((cfg)->mr_rtcwk_shअगरt))
#घोषणा SHDW_RTTWKEN(cfg)	(1 << ((cfg)->mr_rttwk_shअगरt))

#घोषणा DBC_PERIOD_US(x)	DIV_ROUND_UP_ULL((1000000 * (x)), \
							SLOW_CLOCK_FREQ)

#घोषणा SHDW_CFG_NOT_USED	(32)

काष्ठा shdwc_reg_config अणु
	u8 wkup_pin_input;
	u8 mr_rtcwk_shअगरt;
	u8 mr_rttwk_shअगरt;
	u8 sr_rtcwk_shअगरt;
	u8 sr_rttwk_shअगरt;
पूर्ण;

काष्ठा pmc_reg_config अणु
	u8 mckr;
पूर्ण;

काष्ठा ddrc_reg_config अणु
	u32 type_offset;
	u32 type_mask;
पूर्ण;

काष्ठा reg_config अणु
	काष्ठा shdwc_reg_config shdwc;
	काष्ठा pmc_reg_config pmc;
	काष्ठा ddrc_reg_config ddrc;
पूर्ण;

काष्ठा shdwc अणु
	स्थिर काष्ठा reg_config *rcfg;
	काष्ठा clk *sclk;
	व्योम __iomem *shdwc_base;
	व्योम __iomem *mpddrc_base;
	व्योम __iomem *pmc_base;
पूर्ण;

/*
 * Hold configuration here, cannot be more than one instance of the driver
 * since pm_घातer_off itself is global.
 */
अटल काष्ठा shdwc *at91_shdwc;

अटल स्थिर अचिन्हित दीर्घ दीर्घ sdwc_dbc_period[] = अणु
	0, 3, 32, 512, 4096, 32768,
पूर्ण;

अटल व्योम __init at91_wakeup_status(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shdwc *shdw = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा reg_config *rcfg = shdw->rcfg;
	u32 reg;
	अक्षर *reason = "unknown";

	reg = पढ़ोl(shdw->shdwc_base + AT91_SHDW_SR);

	dev_dbg(&pdev->dev, "%s: status = %#x\n", __func__, reg);

	/* Simple घातer-on, just bail out */
	अगर (!reg)
		वापस;

	अगर (SHDW_WK_PIN(reg, &rcfg->shdwc))
		reason = "WKUP pin";
	अन्यथा अगर (SHDW_RTCWK(reg, &rcfg->shdwc))
		reason = "RTC";
	अन्यथा अगर (SHDW_RTTWK(reg, &rcfg->shdwc))
		reason = "RTT";

	pr_info("AT91: Wake-Up source: %s\n", reason);
पूर्ण

अटल व्योम at91_घातeroff(व्योम)
अणु
	यंत्र अस्थिर(
		/* Align to cache lines */
		".balign 32\n\t"

		/* Ensure AT91_SHDW_CR is in the TLB by पढ़ोing it */
		"	ldr	r6, [%2, #" __stringअगरy(AT91_SHDW_CR) "]\n\t"

		/* Power करोwn SDRAM0 */
		"	tst	%0, #0\n\t"
		"	beq	1f\n\t"
		"	str	%1, [%0, #" __stringअगरy(AT91_DDRSDRC_LPR) "]\n\t"

		/* Switch the master घड़ी source to slow घड़ी. */
		"1:	ldr	r6, [%4, %5]\n\t"
		"	bic	r6, r6,  #" __stringअगरy(AT91_PMC_CSS) "\n\t"
		"	str	r6, [%4, %5]\n\t"
		/* Wait क्रम घड़ी चयन. */
		"2:	ldr	r6, [%4, #" __stringअगरy(AT91_PMC_SR) "]\n\t"
		"	tst	r6, #"	    __stringअगरy(AT91_PMC_MCKRDY) "\n\t"
		"	beq	2b\n\t"

		/* Shutकरोwn CPU */
		"	str	%3, [%2, #" __stringअगरy(AT91_SHDW_CR) "]\n\t"

		"	b	.\n\t"
		:
		: "r" (at91_shdwc->mpddrc_base),
		  "r" cpu_to_le32(AT91_DDRSDRC_LPDDR2_PWOFF),
		  "r" (at91_shdwc->shdwc_base),
		  "r" cpu_to_le32(AT91_SHDW_KEY | AT91_SHDW_SHDW),
		  "r" (at91_shdwc->pmc_base),
		  "r" (at91_shdwc->rcfg->pmc.mckr)
		: "r6");
पूर्ण

अटल u32 at91_shdwc_debouncer_value(काष्ठा platक्रमm_device *pdev,
				      u32 in_period_us)
अणु
	पूर्णांक i;
	पूर्णांक max_idx = ARRAY_SIZE(sdwc_dbc_period) - 1;
	अचिन्हित दीर्घ दीर्घ period_us;
	अचिन्हित दीर्घ दीर्घ max_period_us = DBC_PERIOD_US(sdwc_dbc_period[max_idx]);

	अगर (in_period_us > max_period_us) अणु
		dev_warn(&pdev->dev,
			 "debouncer period %u too big, reduced to %llu us\n",
			 in_period_us, max_period_us);
		वापस max_idx;
	पूर्ण

	क्रम (i = max_idx - 1; i > 0; i--) अणु
		period_us = DBC_PERIOD_US(sdwc_dbc_period[i]);
		dev_dbg(&pdev->dev, "%s: ref[%d] = %llu\n",
						__func__, i, period_us);
		अगर (in_period_us > period_us)
			अवरोध;
	पूर्ण

	वापस i + 1;
पूर्ण

अटल u32 at91_shdwc_get_wakeup_input(काष्ठा platक्रमm_device *pdev,
				       काष्ठा device_node *np)
अणु
	काष्ठा device_node *cnp;
	u32 wk_input_mask;
	u32 wuir = 0;
	u32 wk_input;

	क्रम_each_child_of_node(np, cnp) अणु
		अगर (of_property_पढ़ो_u32(cnp, "reg", &wk_input)) अणु
			dev_warn(&pdev->dev, "reg property is missing for %pOF\n",
				 cnp);
			जारी;
		पूर्ण

		wk_input_mask = 1 << wk_input;
		अगर (!(wk_input_mask & AT91_SHDW_WKUPEN_MASK)) अणु
			dev_warn(&pdev->dev,
				 "wake-up input %d out of bounds ignore\n",
				 wk_input);
			जारी;
		पूर्ण
		wuir |= wk_input_mask;

		अगर (of_property_पढ़ो_bool(cnp, "atmel,wakeup-active-high"))
			wuir |= AT91_SHDW_WKUPT(wk_input);

		dev_dbg(&pdev->dev, "%s: (child %d) wuir = %#x\n",
						__func__, wk_input, wuir);
	पूर्ण

	वापस wuir;
पूर्ण

अटल व्योम at91_shdwc_dt_configure(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shdwc *shdw = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा reg_config *rcfg = shdw->rcfg;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 mode = 0, पंचांगp, input;

	अगर (!np) अणु
		dev_err(&pdev->dev, "device node not found\n");
		वापस;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "debounce-delay-us", &पंचांगp))
		mode |= AT91_SHDW_WKUPDBC(at91_shdwc_debouncer_value(pdev, पंचांगp));

	अगर (of_property_पढ़ो_bool(np, "atmel,wakeup-rtc-timer"))
		mode |= SHDW_RTCWKEN(&rcfg->shdwc);

	अगर (of_property_पढ़ो_bool(np, "atmel,wakeup-rtt-timer"))
		mode |= SHDW_RTTWKEN(&rcfg->shdwc);

	dev_dbg(&pdev->dev, "%s: mode = %#x\n", __func__, mode);
	ग_लिखोl(mode, shdw->shdwc_base + AT91_SHDW_MR);

	input = at91_shdwc_get_wakeup_input(pdev, np);
	ग_लिखोl(input, shdw->shdwc_base + AT91_SHDW_WUIR);
पूर्ण

अटल स्थिर काष्ठा reg_config sama5d2_reg_config = अणु
	.shdwc = अणु
		.wkup_pin_input = 0,
		.mr_rtcwk_shअगरt = 17,
		.mr_rttwk_shअगरt	= SHDW_CFG_NOT_USED,
		.sr_rtcwk_shअगरt = 5,
		.sr_rttwk_shअगरt = SHDW_CFG_NOT_USED,
	पूर्ण,
	.pmc = अणु
		.mckr		= 0x30,
	पूर्ण,
	.ddrc = अणु
		.type_offset	= AT91_DDRSDRC_MDR,
		.type_mask	= AT91_DDRSDRC_MD
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_config sam9x60_reg_config = अणु
	.shdwc = अणु
		.wkup_pin_input = 0,
		.mr_rtcwk_shअगरt = 17,
		.mr_rttwk_shअगरt = 16,
		.sr_rtcwk_shअगरt = 5,
		.sr_rttwk_shअगरt = 4,
	पूर्ण,
	.pmc = अणु
		.mckr		= 0x28,
	पूर्ण,
	.ddrc = अणु
		.type_offset	= AT91_DDRSDRC_MDR,
		.type_mask	= AT91_DDRSDRC_MD
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_config sama7g5_reg_config = अणु
	.shdwc = अणु
		.wkup_pin_input = 0,
		.mr_rtcwk_shअगरt = 17,
		.mr_rttwk_shअगरt = 16,
		.sr_rtcwk_shअगरt = 5,
		.sr_rttwk_shअगरt = 4,
	पूर्ण,
	.pmc = अणु
		.mckr		= 0x28,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_shdwc_of_match[] = अणु
	अणु
		.compatible = "atmel,sama5d2-shdwc",
		.data = &sama5d2_reg_config,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-shdwc",
		.data = &sam9x60_reg_config,
	पूर्ण,
	अणु
		.compatible = "microchip,sama7g5-shdwc",
		.data = &sama7g5_reg_config,
	पूर्ण, अणु
		/*sentinel*/
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_shdwc_of_match);

अटल स्थिर काष्ठा of_device_id at91_pmc_ids[] = अणु
	अणु .compatible = "atmel,sama5d2-pmc" पूर्ण,
	अणु .compatible = "microchip,sam9x60-pmc" पूर्ण,
	अणु .compatible = "microchip,sama7g5-pmc" पूर्ण,
	अणु /* Sentinel. */ पूर्ण
पूर्ण;

अटल पूर्णांक __init at91_shdwc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	u32 ddr_type;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	अगर (at91_shdwc)
		वापस -EBUSY;

	at91_shdwc = devm_kzalloc(&pdev->dev, माप(*at91_shdwc), GFP_KERNEL);
	अगर (!at91_shdwc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, at91_shdwc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	at91_shdwc->shdwc_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(at91_shdwc->shdwc_base)) अणु
		dev_err(&pdev->dev, "Could not map reset controller address\n");
		वापस PTR_ERR(at91_shdwc->shdwc_base);
	पूर्ण

	match = of_match_node(at91_shdwc_of_match, pdev->dev.of_node);
	at91_shdwc->rcfg = match->data;

	at91_shdwc->sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(at91_shdwc->sclk))
		वापस PTR_ERR(at91_shdwc->sclk);

	ret = clk_prepare_enable(at91_shdwc->sclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	at91_wakeup_status(pdev);

	at91_shdwc_dt_configure(pdev);

	np = of_find_matching_node(शून्य, at91_pmc_ids);
	अगर (!np) अणु
		ret = -ENODEV;
		जाओ clk_disable;
	पूर्ण

	at91_shdwc->pmc_base = of_iomap(np, 0);
	of_node_put(np);

	अगर (!at91_shdwc->pmc_base) अणु
		ret = -ENOMEM;
		जाओ clk_disable;
	पूर्ण

	अगर (at91_shdwc->rcfg->ddrc.type_mask) अणु
		np = of_find_compatible_node(शून्य, शून्य,
					     "atmel,sama5d3-ddramc");
		अगर (!np) अणु
			ret = -ENODEV;
			जाओ unmap;
		पूर्ण

		at91_shdwc->mpddrc_base = of_iomap(np, 0);
		of_node_put(np);

		अगर (!at91_shdwc->mpddrc_base) अणु
			ret = -ENOMEM;
			जाओ unmap;
		पूर्ण

		ddr_type = पढ़ोl(at91_shdwc->mpddrc_base +
				 at91_shdwc->rcfg->ddrc.type_offset) &
				 at91_shdwc->rcfg->ddrc.type_mask;
		अगर (ddr_type != AT91_DDRSDRC_MD_LPDDR2 &&
		    ddr_type != AT91_DDRSDRC_MD_LPDDR3) अणु
			iounmap(at91_shdwc->mpddrc_base);
			at91_shdwc->mpddrc_base = शून्य;
		पूर्ण
	पूर्ण

	pm_घातer_off = at91_घातeroff;

	वापस 0;

unmap:
	iounmap(at91_shdwc->pmc_base);
clk_disable:
	clk_disable_unprepare(at91_shdwc->sclk);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास at91_shdwc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shdwc *shdw = platक्रमm_get_drvdata(pdev);

	अगर (pm_घातer_off == at91_घातeroff)
		pm_घातer_off = शून्य;

	/* Reset values to disable wake-up features  */
	ग_लिखोl(0, shdw->shdwc_base + AT91_SHDW_MR);
	ग_लिखोl(0, shdw->shdwc_base + AT91_SHDW_WUIR);

	अगर (shdw->mpddrc_base)
		iounmap(shdw->mpddrc_base);
	iounmap(shdw->pmc_base);

	clk_disable_unprepare(shdw->sclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver at91_shdwc_driver = अणु
	.हटाओ = __निकास_p(at91_shdwc_हटाओ),
	.driver = अणु
		.name = "at91-shdwc",
		.of_match_table = at91_shdwc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(at91_shdwc_driver, at91_shdwc_probe);

MODULE_AUTHOR("Nicolas Ferre <nicolas.ferre@atmel.com>");
MODULE_DESCRIPTION("Atmel shutdown controller driver");
MODULE_LICENSE("GPL v2");
