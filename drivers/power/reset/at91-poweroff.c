<शैली गुरु>
/*
 * Aपंचांगel AT91 SAM9 SoCs reset code
 *
 * Copyright (C) 2007 Aपंचांगel Corporation.
 * Copyright (C) 2011 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 * Copyright (C) 2014 Free Electrons
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <soc/at91/at91sam9_ddrsdr.h>

#घोषणा AT91_SHDW_CR	0x00		/* Shut Down Control Register */
#घोषणा AT91_SHDW_SHDW		BIT(0)			/* Shut Down command */
#घोषणा AT91_SHDW_KEY		(0xa5 << 24)		/* KEY Password */

#घोषणा AT91_SHDW_MR	0x04		/* Shut Down Mode Register */
#घोषणा AT91_SHDW_WKMODE0	GENMASK(2, 0)		/* Wake-up 0 Mode Selection */
#घोषणा AT91_SHDW_CPTWK0_MAX	0xf			/* Maximum Counter On Wake Up 0 */
#घोषणा AT91_SHDW_CPTWK0	(AT91_SHDW_CPTWK0_MAX << 4) /* Counter On Wake Up 0 */
#घोषणा AT91_SHDW_CPTWK0_(x)	((x) << 4)
#घोषणा AT91_SHDW_RTTWKEN	BIT(16)			/* Real Time Timer Wake-up Enable */
#घोषणा AT91_SHDW_RTCWKEN	BIT(17)			/* Real Time Clock Wake-up Enable */

#घोषणा AT91_SHDW_SR	0x08		/* Shut Down Status Register */
#घोषणा AT91_SHDW_WAKEUP0	BIT(0)			/* Wake-up 0 Status */
#घोषणा AT91_SHDW_RTTWK		BIT(16)			/* Real-समय Timer Wake-up */
#घोषणा AT91_SHDW_RTCWK		BIT(17)			/* Real-समय Clock Wake-up [SAM9RL] */

क्रमागत wakeup_type अणु
	AT91_SHDW_WKMODE0_NONE		= 0,
	AT91_SHDW_WKMODE0_HIGH		= 1,
	AT91_SHDW_WKMODE0_LOW		= 2,
	AT91_SHDW_WKMODE0_ANYLEVEL	= 3,
पूर्ण;

अटल स्थिर अक्षर *shdwc_wakeup_modes[] = अणु
	[AT91_SHDW_WKMODE0_NONE]	= "none",
	[AT91_SHDW_WKMODE0_HIGH]	= "high",
	[AT91_SHDW_WKMODE0_LOW]		= "low",
	[AT91_SHDW_WKMODE0_ANYLEVEL]	= "any",
पूर्ण;

अटल काष्ठा shdwc अणु
	काष्ठा clk *sclk;
	व्योम __iomem *shdwc_base;
	व्योम __iomem *mpddrc_base;
पूर्ण at91_shdwc;

अटल व्योम __init at91_wakeup_status(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *reason;
	u32 reg = पढ़ोl(at91_shdwc.shdwc_base + AT91_SHDW_SR);

	/* Simple घातer-on, just bail out */
	अगर (!reg)
		वापस;

	अगर (reg & AT91_SHDW_RTTWK)
		reason = "RTT";
	अन्यथा अगर (reg & AT91_SHDW_RTCWK)
		reason = "RTC";
	अन्यथा
		reason = "unknown";

	dev_info(&pdev->dev, "Wake-Up source: %s\n", reason);
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
		/* Shutकरोwn CPU */
		"1:	str	%3, [%2, #" __stringअगरy(AT91_SHDW_CR) "]\n\t"

		"	b	.\n\t"
		:
		: "r" (at91_shdwc.mpddrc_base),
		  "r" cpu_to_le32(AT91_DDRSDRC_LPDDR2_PWOFF),
		  "r" (at91_shdwc.shdwc_base),
		  "r" cpu_to_le32(AT91_SHDW_KEY | AT91_SHDW_SHDW)
		: "r6");
पूर्ण

अटल पूर्णांक at91_घातeroff_get_wakeup_mode(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *pm;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "atmel,wakeup-mode", &pm);
	अगर (err < 0)
		वापस AT91_SHDW_WKMODE0_ANYLEVEL;

	क्रम (i = 0; i < ARRAY_SIZE(shdwc_wakeup_modes); i++)
		अगर (!strहालcmp(pm, shdwc_wakeup_modes[i]))
			वापस i;

	वापस -ENODEV;
पूर्ण

अटल व्योम at91_घातeroff_dt_set_wakeup_mode(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक wakeup_mode;
	u32 mode = 0, पंचांगp;

	wakeup_mode = at91_घातeroff_get_wakeup_mode(np);
	अगर (wakeup_mode < 0) अणु
		dev_warn(&pdev->dev, "shdwc unknown wakeup mode\n");
		वापस;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "atmel,wakeup-counter", &पंचांगp)) अणु
		अगर (पंचांगp > AT91_SHDW_CPTWK0_MAX) अणु
			dev_warn(&pdev->dev,
				 "shdwc wakeup counter 0x%x > 0x%x reduce it to 0x%x\n",
				 पंचांगp, AT91_SHDW_CPTWK0_MAX, AT91_SHDW_CPTWK0_MAX);
			पंचांगp = AT91_SHDW_CPTWK0_MAX;
		पूर्ण
		mode |= AT91_SHDW_CPTWK0_(पंचांगp);
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "atmel,wakeup-rtc-timer"))
			mode |= AT91_SHDW_RTCWKEN;

	अगर (of_property_पढ़ो_bool(np, "atmel,wakeup-rtt-timer"))
			mode |= AT91_SHDW_RTTWKEN;

	ग_लिखोl(wakeup_mode | mode, at91_shdwc.shdwc_base + AT91_SHDW_MR);
पूर्ण

अटल पूर्णांक __init at91_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा device_node *np;
	u32 ddr_type;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	at91_shdwc.shdwc_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(at91_shdwc.shdwc_base))
		वापस PTR_ERR(at91_shdwc.shdwc_base);

	at91_shdwc.sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(at91_shdwc.sclk))
		वापस PTR_ERR(at91_shdwc.sclk);

	ret = clk_prepare_enable(at91_shdwc.sclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	at91_wakeup_status(pdev);

	अगर (pdev->dev.of_node)
		at91_घातeroff_dt_set_wakeup_mode(pdev);

	np = of_find_compatible_node(शून्य, शून्य, "atmel,sama5d3-ddramc");
	अगर (np) अणु
		at91_shdwc.mpddrc_base = of_iomap(np, 0);
		of_node_put(np);

		अगर (!at91_shdwc.mpddrc_base) अणु
			ret = -ENOMEM;
			जाओ clk_disable;
		पूर्ण

		ddr_type = पढ़ोl(at91_shdwc.mpddrc_base + AT91_DDRSDRC_MDR) &
				 AT91_DDRSDRC_MD;
		अगर (ddr_type != AT91_DDRSDRC_MD_LPDDR2 &&
		    ddr_type != AT91_DDRSDRC_MD_LPDDR3) अणु
			iounmap(at91_shdwc.mpddrc_base);
			at91_shdwc.mpddrc_base = शून्य;
		पूर्ण
	पूर्ण

	pm_घातer_off = at91_घातeroff;

	वापस 0;

clk_disable:
	clk_disable_unprepare(at91_shdwc.sclk);
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास at91_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == at91_घातeroff)
		pm_घातer_off = शून्य;

	अगर (at91_shdwc.mpddrc_base)
		iounmap(at91_shdwc.mpddrc_base);

	clk_disable_unprepare(at91_shdwc.sclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_घातeroff_of_match[] = अणु
	अणु .compatible = "atmel,at91sam9260-shdwc", पूर्ण,
	अणु .compatible = "atmel,at91sam9rl-shdwc", पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-shdwc", पूर्ण,
	अणु /*sentinel*/ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_घातeroff_of_match);

अटल काष्ठा platक्रमm_driver at91_घातeroff_driver = अणु
	.हटाओ = __निकास_p(at91_घातeroff_हटाओ),
	.driver = अणु
		.name = "at91-poweroff",
		.of_match_table = at91_घातeroff_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(at91_घातeroff_driver, at91_घातeroff_probe);

MODULE_AUTHOR("Atmel Corporation");
MODULE_DESCRIPTION("Shutdown driver for Atmel SoCs");
MODULE_LICENSE("GPL v2");
