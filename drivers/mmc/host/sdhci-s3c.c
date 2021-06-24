<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/mmc/host/sdhci-s3c.c
 *
 * Copyright 2008 Openmoko Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * SDHCI (HSMMC) support क्रम Samsung SoC
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/mmc-sdhci-s3c.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mmc/host.h>

#समावेश "sdhci.h"

#घोषणा MAX_BUS_CLK	(4)

#घोषणा S3C_SDHCI_CONTROL2			(0x80)
#घोषणा S3C_SDHCI_CONTROL3			(0x84)
#घोषणा S3C64XX_SDHCI_CONTROL4			(0x8C)

#घोषणा S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR	BIT(31)
#घोषणा S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK		BIT(30)
#घोषणा S3C_SDHCI_CTRL2_CDINVRXD3		BIT(29)
#घोषणा S3C_SDHCI_CTRL2_SLCARDOUT		BIT(28)

#घोषणा S3C_SDHCI_CTRL2_FLTCLKSEL_MASK		(0xf << 24)
#घोषणा S3C_SDHCI_CTRL2_FLTCLKSEL_SHIFT		(24)
#घोषणा S3C_SDHCI_CTRL2_FLTCLKSEL(_x)		((_x) << 24)

#घोषणा S3C_SDHCI_CTRL2_LVLDAT_MASK		(0xff << 16)
#घोषणा S3C_SDHCI_CTRL2_LVLDAT_SHIFT		(16)
#घोषणा S3C_SDHCI_CTRL2_LVLDAT(_x)		((_x) << 16)

#घोषणा S3C_SDHCI_CTRL2_ENFBCLKTX		BIT(15)
#घोषणा S3C_SDHCI_CTRL2_ENFBCLKRX		BIT(14)
#घोषणा S3C_SDHCI_CTRL2_SDCDSEL			BIT(13)
#घोषणा S3C_SDHCI_CTRL2_SDSIGPC			BIT(12)
#घोषणा S3C_SDHCI_CTRL2_ENBUSYCHKTXSTART	BIT(11)

#घोषणा S3C_SDHCI_CTRL2_DFCNT_MASK		(0x3 << 9)
#घोषणा S3C_SDHCI_CTRL2_DFCNT_SHIFT		(9)
#घोषणा S3C_SDHCI_CTRL2_DFCNT_NONE		(0x0 << 9)
#घोषणा S3C_SDHCI_CTRL2_DFCNT_4SDCLK		(0x1 << 9)
#घोषणा S3C_SDHCI_CTRL2_DFCNT_16SDCLK		(0x2 << 9)
#घोषणा S3C_SDHCI_CTRL2_DFCNT_64SDCLK		(0x3 << 9)

#घोषणा S3C_SDHCI_CTRL2_ENCLKOUTHOLD		BIT(8)
#घोषणा S3C_SDHCI_CTRL2_RWAITMODE		BIT(7)
#घोषणा S3C_SDHCI_CTRL2_DISBUFRD		BIT(6)

#घोषणा S3C_SDHCI_CTRL2_SELBASECLK_MASK		(0x3 << 4)
#घोषणा S3C_SDHCI_CTRL2_SELBASECLK_SHIFT	(4)
#घोषणा S3C_SDHCI_CTRL2_PWRSYNC			BIT(3)
#घोषणा S3C_SDHCI_CTRL2_ENCLKOUTMSKCON		BIT(1)
#घोषणा S3C_SDHCI_CTRL2_HWINITFIN		BIT(0)

#घोषणा S3C_SDHCI_CTRL3_FCSEL3			BIT(31)
#घोषणा S3C_SDHCI_CTRL3_FCSEL2			BIT(23)
#घोषणा S3C_SDHCI_CTRL3_FCSEL1			BIT(15)
#घोषणा S3C_SDHCI_CTRL3_FCSEL0			BIT(7)

#घोषणा S3C_SDHCI_CTRL3_FIA3_MASK		(0x7f << 24)
#घोषणा S3C_SDHCI_CTRL3_FIA3_SHIFT		(24)
#घोषणा S3C_SDHCI_CTRL3_FIA3(_x)		((_x) << 24)

#घोषणा S3C_SDHCI_CTRL3_FIA2_MASK		(0x7f << 16)
#घोषणा S3C_SDHCI_CTRL3_FIA2_SHIFT		(16)
#घोषणा S3C_SDHCI_CTRL3_FIA2(_x)		((_x) << 16)

#घोषणा S3C_SDHCI_CTRL3_FIA1_MASK		(0x7f << 8)
#घोषणा S3C_SDHCI_CTRL3_FIA1_SHIFT		(8)
#घोषणा S3C_SDHCI_CTRL3_FIA1(_x)		((_x) << 8)

#घोषणा S3C_SDHCI_CTRL3_FIA0_MASK		(0x7f << 0)
#घोषणा S3C_SDHCI_CTRL3_FIA0_SHIFT		(0)
#घोषणा S3C_SDHCI_CTRL3_FIA0(_x)		((_x) << 0)

#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_MASK	(0x3 << 16)
#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_SHIFT	(16)
#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_2mA	(0x0 << 16)
#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_4mA	(0x1 << 16)
#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_7mA	(0x2 << 16)
#घोषणा S3C64XX_SDHCI_CONTROL4_DRIVE_9mA	(0x3 << 16)

#घोषणा S3C64XX_SDHCI_CONTROL4_BUSY		(1)

/**
 * काष्ठा sdhci_s3c - S3C SDHCI instance
 * @host: The SDHCI host created
 * @pdev: The platक्रमm device we where created from.
 * @ioarea: The resource created when we claimed the IO area.
 * @pdata: The platक्रमm data क्रम this controller.
 * @cur_clk: The index of the current bus घड़ी.
 * @ext_cd_irq: External card detect पूर्णांकerrupt.
 * @clk_io: The घड़ी क्रम the पूर्णांकernal bus पूर्णांकerface.
 * @clk_rates: Clock frequencies.
 * @clk_bus: The घड़ीs that are available क्रम the SD/MMC bus घड़ी.
 * @no_भागider: No or non-standard पूर्णांकernal घड़ी भागider.
 */
काष्ठा sdhci_s3c अणु
	काष्ठा sdhci_host	*host;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा resource		*ioarea;
	काष्ठा s3c_sdhci_platdata *pdata;
	पूर्णांक			cur_clk;
	पूर्णांक			ext_cd_irq;

	काष्ठा clk		*clk_io;
	काष्ठा clk		*clk_bus[MAX_BUS_CLK];
	अचिन्हित दीर्घ		clk_rates[MAX_BUS_CLK];

	bool			no_भागider;
पूर्ण;

/**
 * काष्ठा sdhci_s3c_drv_data - S3C SDHCI platक्रमm specअगरic driver data
 * @sdhci_quirks: sdhci host specअगरic quirks.
 * @no_भागider: no or non-standard पूर्णांकernal घड़ी भागider.
 *
 * Specअगरies platक्रमm specअगरic configuration of sdhci controller.
 * Note: A काष्ठाure क्रम driver specअगरic platक्रमm data is used क्रम future
 * expansion of its usage.
 */
काष्ठा sdhci_s3c_drv_data अणु
	अचिन्हित पूर्णांक	sdhci_quirks;
	bool		no_भागider;
पूर्ण;

अटल अंतरभूत काष्ठा sdhci_s3c *to_s3c(काष्ठा sdhci_host *host)
अणु
	वापस sdhci_priv(host);
पूर्ण

/**
 * sdhci_s3c_get_max_clk - callback to get maximum घड़ी frequency.
 * @host: The SDHCI host instance.
 *
 * Callback to वापस the maximum घड़ी rate acheivable by the controller.
*/
अटल अचिन्हित पूर्णांक sdhci_s3c_get_max_clk(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	अचिन्हित दीर्घ rate, max = 0;
	पूर्णांक src;

	क्रम (src = 0; src < MAX_BUS_CLK; src++) अणु
		rate = ourhost->clk_rates[src];
		अगर (rate > max)
			max = rate;
	पूर्ण

	वापस max;
पूर्ण

/**
 * sdhci_s3c_consider_घड़ी - consider one the bus घड़ीs क्रम current setting
 * @ourhost: Our SDHCI instance.
 * @src: The source घड़ी index.
 * @wanted: The घड़ी frequency wanted.
 */
अटल अचिन्हित पूर्णांक sdhci_s3c_consider_घड़ी(काष्ठा sdhci_s3c *ourhost,
					     अचिन्हित पूर्णांक src,
					     अचिन्हित पूर्णांक wanted)
अणु
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clksrc = ourhost->clk_bus[src];
	पूर्णांक shअगरt;

	अगर (IS_ERR(clksrc))
		वापस अच_पूर्णांक_उच्च;

	/*
	 * If controller uses a non-standard घड़ी भागision, find the best घड़ी
	 * speed possible with selected घड़ी source and skip the भागision.
	 */
	अगर (ourhost->no_भागider) अणु
		rate = clk_round_rate(clksrc, wanted);
		वापस wanted - rate;
	पूर्ण

	rate = ourhost->clk_rates[src];

	क्रम (shअगरt = 0; shअगरt <= 8; ++shअगरt) अणु
		अगर ((rate >> shअगरt) <= wanted)
			अवरोध;
	पूर्ण

	अगर (shअगरt > 8) अणु
		dev_dbg(&ourhost->pdev->dev,
			"clk %d: rate %ld, min rate %lu > wanted %u\n",
			src, rate, rate / 256, wanted);
		वापस अच_पूर्णांक_उच्च;
	पूर्ण

	dev_dbg(&ourhost->pdev->dev, "clk %d: rate %ld, want %d, got %ld\n",
		src, rate, wanted, rate >> shअगरt);

	वापस wanted - (rate >> shअगरt);
पूर्ण

/**
 * sdhci_s3c_set_घड़ी - callback on घड़ी change
 * @host: The SDHCI host being changed
 * @घड़ी: The घड़ी rate being requested.
 *
 * When the card's घड़ी is going to be changed, look at the new frequency
 * and find the best घड़ी source to go with it.
*/
अटल व्योम sdhci_s3c_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	अचिन्हित पूर्णांक best = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक delta;
	पूर्णांक best_src = 0;
	पूर्णांक src;
	u32 ctrl;

	host->mmc->actual_घड़ी = 0;

	/* करोn't bother अगर the घड़ी is going off. */
	अगर (घड़ी == 0) अणु
		sdhci_set_घड़ी(host, घड़ी);
		वापस;
	पूर्ण

	क्रम (src = 0; src < MAX_BUS_CLK; src++) अणु
		delta = sdhci_s3c_consider_घड़ी(ourhost, src, घड़ी);
		अगर (delta < best) अणु
			best = delta;
			best_src = src;
		पूर्ण
	पूर्ण

	dev_dbg(&ourhost->pdev->dev,
		"selected source %d, clock %d, delta %d\n",
		 best_src, घड़ी, best);

	/* select the new घड़ी source */
	अगर (ourhost->cur_clk != best_src) अणु
		काष्ठा clk *clk = ourhost->clk_bus[best_src];

		clk_prepare_enable(clk);
		अगर (ourhost->cur_clk >= 0)
			clk_disable_unprepare(
					ourhost->clk_bus[ourhost->cur_clk]);

		ourhost->cur_clk = best_src;
		host->max_clk = ourhost->clk_rates[best_src];
	पूर्ण

	/* turn घड़ी off to card beक्रमe changing घड़ी source */
	ग_लिखोw(0, host->ioaddr + SDHCI_CLOCK_CONTROL);

	ctrl = पढ़ोl(host->ioaddr + S3C_SDHCI_CONTROL2);
	ctrl &= ~S3C_SDHCI_CTRL2_SELBASECLK_MASK;
	ctrl |= best_src << S3C_SDHCI_CTRL2_SELBASECLK_SHIFT;
	ग_लिखोl(ctrl, host->ioaddr + S3C_SDHCI_CONTROL2);

	/* reprogram शेष hardware configuration */
	ग_लिखोl(S3C64XX_SDHCI_CONTROL4_DRIVE_9mA,
		host->ioaddr + S3C64XX_SDHCI_CONTROL4);

	ctrl = पढ़ोl(host->ioaddr + S3C_SDHCI_CONTROL2);
	ctrl |= (S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR |
		  S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK |
		  S3C_SDHCI_CTRL2_ENFBCLKRX |
		  S3C_SDHCI_CTRL2_DFCNT_NONE |
		  S3C_SDHCI_CTRL2_ENCLKOUTHOLD);
	ग_लिखोl(ctrl, host->ioaddr + S3C_SDHCI_CONTROL2);

	/* reconfigure the controller क्रम new घड़ी rate */
	ctrl = (S3C_SDHCI_CTRL3_FCSEL1 | S3C_SDHCI_CTRL3_FCSEL0);
	अगर (घड़ी < 25 * 1000000)
		ctrl |= (S3C_SDHCI_CTRL3_FCSEL3 | S3C_SDHCI_CTRL3_FCSEL2);
	ग_लिखोl(ctrl, host->ioaddr + S3C_SDHCI_CONTROL3);

	sdhci_set_घड़ी(host, घड़ी);
पूर्ण

/**
 * sdhci_s3c_get_min_घड़ी - callback to get minimal supported घड़ी value
 * @host: The SDHCI host being queried
 *
 * To init mmc host properly a minimal घड़ी value is needed. For high प्रणाली
 * bus घड़ी's values the standard क्रमmula gives values out of allowed range.
 * The घड़ी still can be set to lower values, अगर घड़ी source other then
 * प्रणाली bus is selected.
*/
अटल अचिन्हित पूर्णांक sdhci_s3c_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	अचिन्हित दीर्घ rate, min = अच_दीर्घ_उच्च;
	पूर्णांक src;

	क्रम (src = 0; src < MAX_BUS_CLK; src++) अणु
		rate = ourhost->clk_rates[src] / 256;
		अगर (!rate)
			जारी;
		अगर (rate < min)
			min = rate;
	पूर्ण

	वापस min;
पूर्ण

/* sdhci_cmu_get_max_clk - callback to get maximum घड़ी frequency.*/
अटल अचिन्हित पूर्णांक sdhci_cmu_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	अचिन्हित दीर्घ rate, max = 0;
	पूर्णांक src;

	क्रम (src = 0; src < MAX_BUS_CLK; src++) अणु
		काष्ठा clk *clk;

		clk = ourhost->clk_bus[src];
		अगर (IS_ERR(clk))
			जारी;

		rate = clk_round_rate(clk, अच_दीर्घ_उच्च);
		अगर (rate > max)
			max = rate;
	पूर्ण

	वापस max;
पूर्ण

/* sdhci_cmu_get_min_घड़ी - callback to get minimal supported घड़ी value. */
अटल अचिन्हित पूर्णांक sdhci_cmu_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	अचिन्हित दीर्घ rate, min = अच_दीर्घ_उच्च;
	पूर्णांक src;

	क्रम (src = 0; src < MAX_BUS_CLK; src++) अणु
		काष्ठा clk *clk;

		clk = ourhost->clk_bus[src];
		अगर (IS_ERR(clk))
			जारी;

		rate = clk_round_rate(clk, 0);
		अगर (rate < min)
			min = rate;
	पूर्ण

	वापस min;
पूर्ण

/* sdhci_cmu_set_घड़ी - callback on घड़ी change.*/
अटल व्योम sdhci_cmu_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	काष्ठा device *dev = &ourhost->pdev->dev;
	अचिन्हित दीर्घ समयout;
	u16 clk = 0;
	पूर्णांक ret;

	host->mmc->actual_घड़ी = 0;

	/* If the घड़ी is going off, set to 0 at घड़ी control रेजिस्टर */
	अगर (घड़ी == 0) अणु
		sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);
		वापस;
	पूर्ण

	sdhci_s3c_set_घड़ी(host, घड़ी);

	/* Reset SD Clock Enable */
	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	ret = clk_set_rate(ourhost->clk_bus[ourhost->cur_clk], घड़ी);
	अगर (ret != 0) अणु
		dev_err(dev, "%s: failed to set clock rate %uHz\n",
			mmc_hostname(host->mmc), घड़ी);
		वापस;
	पूर्ण

	clk = SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 20 ms */
	समयout = 20;
	जबतक (!((clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL))
		& SDHCI_CLOCK_INT_STABLE)) अणु
		अगर (समयout == 0) अणु
			dev_err(dev, "%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			वापस;
		पूर्ण
		समयout--;
		mdelay(1);
	पूर्ण

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
पूर्ण

अटल काष्ठा sdhci_ops sdhci_s3c_ops = अणु
	.get_max_घड़ी		= sdhci_s3c_get_max_clk,
	.set_घड़ी		= sdhci_s3c_set_घड़ी,
	.get_min_घड़ी		= sdhci_s3c_get_min_घड़ी,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_reset,
	.set_uhs_संकेतing	= sdhci_set_uhs_संकेतing,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक sdhci_s3c_parse_dt(काष्ठा device *dev,
		काष्ठा sdhci_host *host, काष्ठा s3c_sdhci_platdata *pdata)
अणु
	काष्ठा device_node *node = dev->of_node;
	u32 max_width;

	/* अगर the bus-width property is not specअगरied, assume width as 1 */
	अगर (of_property_पढ़ो_u32(node, "bus-width", &max_width))
		max_width = 1;
	pdata->max_width = max_width;

	/* get the card detection method */
	अगर (of_get_property(node, "broken-cd", शून्य)) अणु
		pdata->cd_type = S3C_SDHCI_CD_NONE;
		वापस 0;
	पूर्ण

	अगर (of_get_property(node, "non-removable", शून्य)) अणु
		pdata->cd_type = S3C_SDHCI_CD_PERMANENT;
		वापस 0;
	पूर्ण

	अगर (of_get_named_gpio(node, "cd-gpios", 0))
		वापस 0;

	/* assuming पूर्णांकernal card detect that will be configured by pinctrl */
	pdata->cd_type = S3C_SDHCI_CD_INTERNAL;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक sdhci_s3c_parse_dt(काष्ठा device *dev,
		काष्ठा sdhci_host *host, काष्ठा s3c_sdhci_platdata *pdata)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत स्थिर काष्ठा sdhci_s3c_drv_data *sdhci_s3c_get_driver_data(
			काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_OF
	अगर (pdev->dev.of_node)
		वापस of_device_get_match_data(&pdev->dev);
#पूर्ण_अगर
	वापस (स्थिर काष्ठा sdhci_s3c_drv_data *)
			platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक sdhci_s3c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_sdhci_platdata *pdata;
	स्थिर काष्ठा sdhci_s3c_drv_data *drv_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_s3c *sc;
	पूर्णांक ret, irq, ptr, clks;

	अगर (!pdev->dev.platक्रमm_data && !pdev->dev.of_node) अणु
		dev_err(dev, "no device data specified\n");
		वापस -ENOENT;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	host = sdhci_alloc_host(dev, माप(काष्ठा sdhci_s3c));
	अगर (IS_ERR(host)) अणु
		dev_err(dev, "sdhci_alloc_host() failed\n");
		वापस PTR_ERR(host);
	पूर्ण
	sc = sdhci_priv(host);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		ret = -ENOMEM;
		जाओ err_pdata_io_clk;
	पूर्ण

	अगर (pdev->dev.of_node) अणु
		ret = sdhci_s3c_parse_dt(&pdev->dev, host, pdata);
		अगर (ret)
			जाओ err_pdata_io_clk;
	पूर्ण अन्यथा अणु
		स_नकल(pdata, pdev->dev.platक्रमm_data, माप(*pdata));
	पूर्ण

	drv_data = sdhci_s3c_get_driver_data(pdev);

	sc->host = host;
	sc->pdev = pdev;
	sc->pdata = pdata;
	sc->cur_clk = -1;

	platक्रमm_set_drvdata(pdev, host);

	sc->clk_io = devm_clk_get(dev, "hsmmc");
	अगर (IS_ERR(sc->clk_io)) अणु
		dev_err(dev, "failed to get io clock\n");
		ret = PTR_ERR(sc->clk_io);
		जाओ err_pdata_io_clk;
	पूर्ण

	/* enable the local io घड़ी and keep it running क्रम the moment. */
	clk_prepare_enable(sc->clk_io);

	क्रम (clks = 0, ptr = 0; ptr < MAX_BUS_CLK; ptr++) अणु
		अक्षर name[14];

		snम_लिखो(name, 14, "mmc_busclk.%d", ptr);
		sc->clk_bus[ptr] = devm_clk_get(dev, name);
		अगर (IS_ERR(sc->clk_bus[ptr]))
			जारी;

		clks++;
		sc->clk_rates[ptr] = clk_get_rate(sc->clk_bus[ptr]);

		dev_info(dev, "clock source %d: %s (%ld Hz)\n",
				ptr, name, sc->clk_rates[ptr]);
	पूर्ण

	अगर (clks == 0) अणु
		dev_err(dev, "failed to find any bus clocks\n");
		ret = -ENOENT;
		जाओ err_no_busclks;
	पूर्ण

	host->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->ioaddr)) अणु
		ret = PTR_ERR(host->ioaddr);
		जाओ err_req_regs;
	पूर्ण

	/* Ensure we have minimal gpio selected CMD/CLK/Detect */
	अगर (pdata->cfg_gpio)
		pdata->cfg_gpio(pdev, pdata->max_width);

	host->hw_name = "samsung-hsmmc";
	host->ops = &sdhci_s3c_ops;
	host->quirks = 0;
	host->quirks2 = 0;
	host->irq = irq;

	/* Setup quirks क्रम the controller */
	host->quirks |= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC;
	host->quirks |= SDHCI_QUIRK_NO_HISPD_BIT;
	अगर (drv_data) अणु
		host->quirks |= drv_data->sdhci_quirks;
		sc->no_भागider = drv_data->no_भागider;
	पूर्ण

#अगर_अघोषित CONFIG_MMC_SDHCI_S3C_DMA

	/* we currently see overruns on errors, so disable the SDMA
	 * support as well. */
	host->quirks |= SDHCI_QUIRK_BROKEN_DMA;

#पूर्ण_अगर /* CONFIG_MMC_SDHCI_S3C_DMA */

	/* It seems we करो not get an DATA transfer complete on non-busy
	 * transfers, not sure अगर this is a problem with this specअगरic
	 * SDHCI block, or a missing configuration that needs to be set. */
	host->quirks |= SDHCI_QUIRK_NO_BUSY_IRQ;

	/* This host supports the Auto CMD12 */
	host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

	/* Samsung SoCs need BROKEN_ADMA_ZEROLEN_DESC */
	host->quirks |= SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC;

	अगर (pdata->cd_type == S3C_SDHCI_CD_NONE ||
	    pdata->cd_type == S3C_SDHCI_CD_PERMANENT)
		host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	अगर (pdata->cd_type == S3C_SDHCI_CD_PERMANENT)
		host->mmc->caps = MMC_CAP_NONREMOVABLE;

	चयन (pdata->max_width) अणु
	हाल 8:
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;
		fallthrough;
	हाल 4:
		host->mmc->caps |= MMC_CAP_4_BIT_DATA;
		अवरोध;
	पूर्ण

	अगर (pdata->pm_caps)
		host->mmc->pm_caps |= pdata->pm_caps;

	host->quirks |= (SDHCI_QUIRK_32BIT_DMA_ADDR |
			 SDHCI_QUIRK_32BIT_DMA_SIZE);

	/* HSMMC on Samsung SoCs uses SDCLK as समयout घड़ी */
	host->quirks |= SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK;

	/*
	 * If controller करोes not have पूर्णांकernal घड़ी भागider,
	 * we can use overriding functions instead of शेष.
	 */
	अगर (sc->no_भागider) अणु
		sdhci_s3c_ops.set_घड़ी = sdhci_cmu_set_घड़ी;
		sdhci_s3c_ops.get_min_घड़ी = sdhci_cmu_get_min_घड़ी;
		sdhci_s3c_ops.get_max_घड़ी = sdhci_cmu_get_max_घड़ी;
	पूर्ण

	/* It supports additional host capabilities अगर needed */
	अगर (pdata->host_caps)
		host->mmc->caps |= pdata->host_caps;

	अगर (pdata->host_caps2)
		host->mmc->caps2 |= pdata->host_caps2;

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_req_regs;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_req_regs;

#अगर_घोषित CONFIG_PM
	अगर (pdata->cd_type != S3C_SDHCI_CD_INTERNAL)
		clk_disable_unprepare(sc->clk_io);
#पूर्ण_अगर
	वापस 0;

 err_req_regs:
	pm_runसमय_disable(&pdev->dev);

 err_no_busclks:
	clk_disable_unprepare(sc->clk_io);

 err_pdata_io_clk:
	sdhci_मुक्त_host(host);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_s3c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host =  platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_s3c *sc = sdhci_priv(host);

	अगर (sc->ext_cd_irq)
		मुक्त_irq(sc->ext_cd_irq, sc);

#अगर_घोषित CONFIG_PM
	अगर (sc->pdata->cd_type != S3C_SDHCI_CD_INTERNAL)
		clk_prepare_enable(sc->clk_io);
#पूर्ण_अगर
	sdhci_हटाओ_host(host, 1);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(sc->clk_io);

	sdhci_मुक्त_host(host);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_s3c_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	वापस sdhci_suspend_host(host);
पूर्ण

अटल पूर्णांक sdhci_s3c_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);

	वापस sdhci_resume_host(host);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_s3c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	काष्ठा clk *busclk = ourhost->clk_io;
	पूर्णांक ret;

	ret = sdhci_runसमय_suspend_host(host);

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	अगर (ourhost->cur_clk >= 0)
		clk_disable_unprepare(ourhost->clk_bus[ourhost->cur_clk]);
	clk_disable_unprepare(busclk);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_s3c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_s3c *ourhost = to_s3c(host);
	काष्ठा clk *busclk = ourhost->clk_io;
	पूर्णांक ret;

	clk_prepare_enable(busclk);
	अगर (ourhost->cur_clk >= 0)
		clk_prepare_enable(ourhost->clk_bus[ourhost->cur_clk]);
	ret = sdhci_runसमय_resume_host(host, 0);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_s3c_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_s3c_suspend, sdhci_s3c_resume)
	SET_RUNTIME_PM_OPS(sdhci_s3c_runसमय_suspend, sdhci_s3c_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id sdhci_s3c_driver_ids[] = अणु
	अणु
		.name		= "s3c-sdhci",
		.driver_data	= (kernel_uदीर्घ_t)शून्य,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sdhci_s3c_driver_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा sdhci_s3c_drv_data exynos4_sdhci_drv_data = अणु
	.no_भागider = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_s3c_dt_match[] = अणु
	अणु .compatible = "samsung,s3c6410-sdhci", पूर्ण,
	अणु .compatible = "samsung,exynos4210-sdhci",
		.data = &exynos4_sdhci_drv_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_s3c_dt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sdhci_s3c_driver = अणु
	.probe		= sdhci_s3c_probe,
	.हटाओ		= sdhci_s3c_हटाओ,
	.id_table	= sdhci_s3c_driver_ids,
	.driver		= अणु
		.name	= "s3c-sdhci",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(sdhci_s3c_dt_match),
		.pm	= &sdhci_s3c_pmops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sdhci_s3c_driver);

MODULE_DESCRIPTION("Samsung SDHCI (HSMMC) glue");
MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:s3c-sdhci");
