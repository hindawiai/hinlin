<शैली गुरु>
/*
 * Aपंचांगel AT91 SAM9 & SAMA5 SoCs reset code
 *
 * Copyright (C) 2007 Aपंचांगel Corporation.
 * Copyright (C) BitBox Ltd 2010
 * Copyright (C) 2011 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcosoft.com>
 * Copyright (C) 2014 Free Electrons
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>

#समावेश <soc/at91/at91sam9_ddrsdr.h>
#समावेश <soc/at91/at91sam9_sdramc.h>

#घोषणा AT91_RSTC_CR	0x00		/* Reset Controller Control Register */
#घोषणा AT91_RSTC_PROCRST	BIT(0)		/* Processor Reset */
#घोषणा AT91_RSTC_PERRST	BIT(2)		/* Peripheral Reset */
#घोषणा AT91_RSTC_EXTRST	BIT(3)		/* External Reset */
#घोषणा AT91_RSTC_KEY		(0xa5 << 24)	/* KEY Password */

#घोषणा AT91_RSTC_SR	0x04		/* Reset Controller Status Register */
#घोषणा AT91_RSTC_URSTS		BIT(0)		/* User Reset Status */
#घोषणा AT91_RSTC_RSTTYP	GENMASK(10, 8)	/* Reset Type */
#घोषणा AT91_RSTC_NRSTL		BIT(16)		/* NRST Pin Level */
#घोषणा AT91_RSTC_SRCMP		BIT(17)		/* Software Reset Command in Progress */

#घोषणा AT91_RSTC_MR	0x08		/* Reset Controller Mode Register */
#घोषणा AT91_RSTC_URSTEN	BIT(0)		/* User Reset Enable */
#घोषणा AT91_RSTC_URSTASYNC	BIT(2)		/* User Reset Asynchronous Control */
#घोषणा AT91_RSTC_URSTIEN	BIT(4)		/* User Reset Interrupt Enable */
#घोषणा AT91_RSTC_ERSTL		GENMASK(11, 8)	/* External Reset Length */

क्रमागत reset_type अणु
	RESET_TYPE_GENERAL	= 0,
	RESET_TYPE_WAKEUP	= 1,
	RESET_TYPE_WATCHDOG	= 2,
	RESET_TYPE_SOFTWARE	= 3,
	RESET_TYPE_USER		= 4,
	RESET_TYPE_CPU_FAIL	= 6,
	RESET_TYPE_XTAL_FAIL	= 7,
	RESET_TYPE_ULP2		= 8,
पूर्ण;

काष्ठा at91_reset अणु
	व्योम __iomem *rstc_base;
	व्योम __iomem *ramc_base[2];
	काष्ठा clk *sclk;
	काष्ठा notअगरier_block nb;
	u32 args;
	u32 ramc_lpr;
पूर्ण;

/*
* unless the SDRAM is cleanly shutकरोwn beक्रमe we hit the
* reset रेजिस्टर it can be left driving the data bus and
* समाप्तing the chance of a subsequent boot from न_अंकD
*/
अटल पूर्णांक at91_reset(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
		      व्योम *cmd)
अणु
	काष्ठा at91_reset *reset = container_of(this, काष्ठा at91_reset, nb);

	यंत्र अस्थिर(
		/* Align to cache lines */
		".balign 32\n\t"

		/* Disable SDRAM0 accesses */
		"	tst	%0, #0\n\t"
		"	beq	1f\n\t"
		"	str	%3, [%0, #" __stringअगरy(AT91_DDRSDRC_RTR) "]\n\t"
		/* Power करोwn SDRAM0 */
		"	str	%4, [%0, %6]\n\t"
		/* Disable SDRAM1 accesses */
		"1:	tst	%1, #0\n\t"
		"	beq	2f\n\t"
		"	strne	%3, [%1, #" __stringअगरy(AT91_DDRSDRC_RTR) "]\n\t"
		/* Power करोwn SDRAM1 */
		"	strne	%4, [%1, %6]\n\t"
		/* Reset CPU */
		"2:	str	%5, [%2, #" __stringअगरy(AT91_RSTC_CR) "]\n\t"

		"	b	.\n\t"
		:
		: "r" (reset->ramc_base[0]),
		  "r" (reset->ramc_base[1]),
		  "r" (reset->rstc_base),
		  "r" (1),
		  "r" cpu_to_le32(AT91_DDRSDRC_LPCB_POWER_DOWN),
		  "r" (reset->args),
		  "r" (reset->ramc_lpr)
		: "r4");

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम __init at91_reset_status(काष्ठा platक्रमm_device *pdev,
				     व्योम __iomem *base)
अणु
	स्थिर अक्षर *reason;
	u32 reg = पढ़ोl(base + AT91_RSTC_SR);

	चयन ((reg & AT91_RSTC_RSTTYP) >> 8) अणु
	हाल RESET_TYPE_GENERAL:
		reason = "general reset";
		अवरोध;
	हाल RESET_TYPE_WAKEUP:
		reason = "wakeup";
		अवरोध;
	हाल RESET_TYPE_WATCHDOG:
		reason = "watchdog reset";
		अवरोध;
	हाल RESET_TYPE_SOFTWARE:
		reason = "software reset";
		अवरोध;
	हाल RESET_TYPE_USER:
		reason = "user reset";
		अवरोध;
	हाल RESET_TYPE_CPU_FAIL:
		reason = "CPU clock failure detection";
		अवरोध;
	हाल RESET_TYPE_XTAL_FAIL:
		reason = "32.768 kHz crystal failure detection";
		अवरोध;
	हाल RESET_TYPE_ULP2:
		reason = "ULP2 reset";
		अवरोध;
	शेष:
		reason = "unknown reset";
		अवरोध;
	पूर्ण

	dev_info(&pdev->dev, "Starting after %s\n", reason);
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_ramc_of_match[] = अणु
	अणु
		.compatible = "atmel,at91sam9260-sdramc",
		.data = (व्योम *)AT91_SDRAMC_LPR,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9g45-ddramc",
		.data = (व्योम *)AT91_DDRSDRC_LPR,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_reset_of_match[] = अणु
	अणु
		.compatible = "atmel,at91sam9260-rstc",
		.data = (व्योम *)(AT91_RSTC_KEY | AT91_RSTC_PERRST |
				 AT91_RSTC_PROCRST),
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9g45-rstc",
		.data = (व्योम *)(AT91_RSTC_KEY | AT91_RSTC_PERRST |
				 AT91_RSTC_PROCRST)
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d3-rstc",
		.data = (व्योम *)(AT91_RSTC_KEY | AT91_RSTC_PERRST |
				 AT91_RSTC_PROCRST)
	पूर्ण,
	अणु
		.compatible = "atmel,samx7-rstc",
		.data = (व्योम *)(AT91_RSTC_KEY | AT91_RSTC_PROCRST)
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-rstc",
		.data = (व्योम *)(AT91_RSTC_KEY | AT91_RSTC_PROCRST)
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_reset_of_match);

अटल पूर्णांक __init at91_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा at91_reset *reset;
	काष्ठा device_node *np;
	पूर्णांक ret, idx = 0;

	reset = devm_kzalloc(&pdev->dev, माप(*reset), GFP_KERNEL);
	अगर (!reset)
		वापस -ENOMEM;

	reset->rstc_base = devm_of_iomap(&pdev->dev, pdev->dev.of_node, 0, शून्य);
	अगर (!reset->rstc_base) अणु
		dev_err(&pdev->dev, "Could not map reset controller address\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_compatible(pdev->dev.of_node, "atmel,sama5d3-rstc")) अणु
		/* we need to shutकरोwn the ddr controller, so get ramc base */
		क्रम_each_matching_node_and_match(np, at91_ramc_of_match, &match) अणु
			reset->ramc_lpr = (u32)match->data;
			reset->ramc_base[idx] = devm_of_iomap(&pdev->dev, np, 0, शून्य);
			अगर (!reset->ramc_base[idx]) अणु
				dev_err(&pdev->dev, "Could not map ram controller address\n");
				of_node_put(np);
				वापस -ENODEV;
			पूर्ण
			idx++;
		पूर्ण
	पूर्ण

	match = of_match_node(at91_reset_of_match, pdev->dev.of_node);
	reset->nb.notअगरier_call = at91_reset;
	reset->nb.priority = 192;
	reset->args = (u32)match->data;

	reset->sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(reset->sclk))
		वापस PTR_ERR(reset->sclk);

	ret = clk_prepare_enable(reset->sclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, reset);

	अगर (of_device_is_compatible(pdev->dev.of_node, "microchip,sam9x60-rstc")) अणु
		u32 val = पढ़ोl(reset->rstc_base + AT91_RSTC_MR);

		ग_लिखोl(AT91_RSTC_KEY | AT91_RSTC_URSTASYNC | val,
		       reset->rstc_base + AT91_RSTC_MR);
	पूर्ण

	ret = रेजिस्टर_restart_handler(&reset->nb);
	अगर (ret) अणु
		clk_disable_unprepare(reset->sclk);
		वापस ret;
	पूर्ण

	at91_reset_status(pdev, reset->rstc_base);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास at91_reset_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_reset *reset = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_restart_handler(&reset->nb);
	clk_disable_unprepare(reset->sclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver at91_reset_driver = अणु
	.हटाओ = __निकास_p(at91_reset_हटाओ),
	.driver = अणु
		.name = "at91-reset",
		.of_match_table = at91_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(at91_reset_driver, at91_reset_probe);

MODULE_AUTHOR("Atmel Corporation");
MODULE_DESCRIPTION("Reset driver for Atmel SoCs");
MODULE_LICENSE("GPL v2");
