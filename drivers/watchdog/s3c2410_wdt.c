<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 Watchकरोg Timer Support
 *
 * Based on, softकरोg.c by Alan Cox,
 *     (c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>

#घोषणा S3C2410_WTCON		0x00
#घोषणा S3C2410_WTDAT		0x04
#घोषणा S3C2410_WTCNT		0x08
#घोषणा S3C2410_WTCLRINT	0x0c

#घोषणा S3C2410_WTCNT_MAXCNT	0xffff

#घोषणा S3C2410_WTCON_RSTEN	(1 << 0)
#घोषणा S3C2410_WTCON_INTEN	(1 << 2)
#घोषणा S3C2410_WTCON_ENABLE	(1 << 5)

#घोषणा S3C2410_WTCON_DIV16	(0 << 3)
#घोषणा S3C2410_WTCON_DIV32	(1 << 3)
#घोषणा S3C2410_WTCON_DIV64	(2 << 3)
#घोषणा S3C2410_WTCON_DIV128	(3 << 3)

#घोषणा S3C2410_WTCON_MAXDIV	0x80

#घोषणा S3C2410_WTCON_PRESCALE(x)	((x) << 8)
#घोषणा S3C2410_WTCON_PRESCALE_MASK	(0xff << 8)
#घोषणा S3C2410_WTCON_PRESCALE_MAX	0xff

#घोषणा S3C2410_WATCHDOG_ATBOOT		(0)
#घोषणा S3C2410_WATCHDOG_DEFAULT_TIME	(15)

#घोषणा EXYNOS5_RST_STAT_REG_OFFSET		0x0404
#घोषणा EXYNOS5_WDT_DISABLE_REG_OFFSET		0x0408
#घोषणा EXYNOS5_WDT_MASK_RESET_REG_OFFSET	0x040c
#घोषणा QUIRK_HAS_PMU_CONFIG			(1 << 0)
#घोषणा QUIRK_HAS_RST_STAT			(1 << 1)
#घोषणा QUIRK_HAS_WTCLRINT_REG			(1 << 2)

/* These quirks require that we have a PMU रेजिस्टर map */
#घोषणा QUIRKS_HAVE_PMUREG			(QUIRK_HAS_PMU_CONFIG | \
						 QUIRK_HAS_RST_STAT)

अटल bool nowayout	= WATCHDOG_NOWAYOUT;
अटल पूर्णांक पंचांगr_margin;
अटल पूर्णांक पंचांगr_atboot	= S3C2410_WATCHDOG_ATBOOT;
अटल पूर्णांक soft_noboot;

module_param(पंचांगr_margin,  पूर्णांक, 0);
module_param(पंचांगr_atboot,  पूर्णांक, 0);
module_param(nowayout,   bool, 0);
module_param(soft_noboot, पूर्णांक, 0);

MODULE_PARM_DESC(पंचांगr_margin, "Watchdog tmr_margin in seconds. (default="
		__MODULE_STRING(S3C2410_WATCHDOG_DEFAULT_TIME) ")");
MODULE_PARM_DESC(पंचांगr_atboot,
		"Watchdog is started at boot time if set to 1, default="
			__MODULE_STRING(S3C2410_WATCHDOG_ATBOOT));
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
MODULE_PARM_DESC(soft_noboot, "Watchdog action, set to 1 to ignore reboots, 0 to reboot (default 0)");

/**
 * काष्ठा s3c2410_wdt_variant - Per-variant config data
 *
 * @disable_reg: Offset in pmureg क्रम the रेजिस्टर that disables the watchकरोg
 * समयr reset functionality.
 * @mask_reset_reg: Offset in pmureg क्रम the रेजिस्टर that masks the watchकरोg
 * समयr reset functionality.
 * @mask_bit: Bit number क्रम the watchकरोg समयr in the disable रेजिस्टर and the
 * mask reset रेजिस्टर.
 * @rst_stat_reg: Offset in pmureg क्रम the रेजिस्टर that has the reset status.
 * @rst_stat_bit: Bit number in the rst_stat रेजिस्टर indicating a watchकरोg
 * reset.
 * @quirks: A bitfield of quirks.
 */

काष्ठा s3c2410_wdt_variant अणु
	पूर्णांक disable_reg;
	पूर्णांक mask_reset_reg;
	पूर्णांक mask_bit;
	पूर्णांक rst_stat_reg;
	पूर्णांक rst_stat_bit;
	u32 quirks;
पूर्ण;

काष्ठा s3c2410_wdt अणु
	काष्ठा device		*dev;
	काष्ठा clk		*घड़ी;
	व्योम __iomem		*reg_base;
	अचिन्हित पूर्णांक		count;
	spinlock_t		lock;
	अचिन्हित दीर्घ		wtcon_save;
	अचिन्हित दीर्घ		wtdat_save;
	काष्ठा watchकरोg_device	wdt_device;
	काष्ठा notअगरier_block	freq_transition;
	स्थिर काष्ठा s3c2410_wdt_variant *drv_data;
	काष्ठा regmap *pmureg;
पूर्ण;

अटल स्थिर काष्ठा s3c2410_wdt_variant drv_data_s3c2410 = अणु
	.quirks = 0
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा s3c2410_wdt_variant drv_data_s3c6410 = अणु
	.quirks = QUIRK_HAS_WTCLRINT_REG,
पूर्ण;

अटल स्थिर काष्ठा s3c2410_wdt_variant drv_data_exynos5250  = अणु
	.disable_reg = EXYNOS5_WDT_DISABLE_REG_OFFSET,
	.mask_reset_reg = EXYNOS5_WDT_MASK_RESET_REG_OFFSET,
	.mask_bit = 20,
	.rst_stat_reg = EXYNOS5_RST_STAT_REG_OFFSET,
	.rst_stat_bit = 20,
	.quirks = QUIRK_HAS_PMU_CONFIG | QUIRK_HAS_RST_STAT \
		  | QUIRK_HAS_WTCLRINT_REG,
पूर्ण;

अटल स्थिर काष्ठा s3c2410_wdt_variant drv_data_exynos5420 = अणु
	.disable_reg = EXYNOS5_WDT_DISABLE_REG_OFFSET,
	.mask_reset_reg = EXYNOS5_WDT_MASK_RESET_REG_OFFSET,
	.mask_bit = 0,
	.rst_stat_reg = EXYNOS5_RST_STAT_REG_OFFSET,
	.rst_stat_bit = 9,
	.quirks = QUIRK_HAS_PMU_CONFIG | QUIRK_HAS_RST_STAT \
		  | QUIRK_HAS_WTCLRINT_REG,
पूर्ण;

अटल स्थिर काष्ठा s3c2410_wdt_variant drv_data_exynos7 = अणु
	.disable_reg = EXYNOS5_WDT_DISABLE_REG_OFFSET,
	.mask_reset_reg = EXYNOS5_WDT_MASK_RESET_REG_OFFSET,
	.mask_bit = 23,
	.rst_stat_reg = EXYNOS5_RST_STAT_REG_OFFSET,
	.rst_stat_bit = 23,	/* A57 WDTRESET */
	.quirks = QUIRK_HAS_PMU_CONFIG | QUIRK_HAS_RST_STAT \
		  | QUIRK_HAS_WTCLRINT_REG,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s3c2410_wdt_match[] = अणु
	अणु .compatible = "samsung,s3c2410-wdt",
	  .data = &drv_data_s3c2410 पूर्ण,
	अणु .compatible = "samsung,s3c6410-wdt",
	  .data = &drv_data_s3c6410 पूर्ण,
	अणु .compatible = "samsung,exynos5250-wdt",
	  .data = &drv_data_exynos5250 पूर्ण,
	अणु .compatible = "samsung,exynos5420-wdt",
	  .data = &drv_data_exynos5420 पूर्ण,
	अणु .compatible = "samsung,exynos7-wdt",
	  .data = &drv_data_exynos7 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c2410_wdt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id s3c2410_wdt_ids[] = अणु
	अणु
		.name = "s3c2410-wdt",
		.driver_data = (अचिन्हित दीर्घ)&drv_data_s3c2410,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c2410_wdt_ids);

/* functions */

अटल अंतरभूत अचिन्हित पूर्णांक s3c2410wdt_max_समयout(काष्ठा clk *घड़ी)
अणु
	अचिन्हित दीर्घ freq = clk_get_rate(घड़ी);

	वापस S3C2410_WTCNT_MAXCNT / (freq / (S3C2410_WTCON_PRESCALE_MAX + 1)
				       / S3C2410_WTCON_MAXDIV);
पूर्ण

अटल अंतरभूत काष्ठा s3c2410_wdt *freq_to_wdt(काष्ठा notअगरier_block *nb)
अणु
	वापस container_of(nb, काष्ठा s3c2410_wdt, freq_transition);
पूर्ण

अटल पूर्णांक s3c2410wdt_mask_and_disable_reset(काष्ठा s3c2410_wdt *wdt, bool mask)
अणु
	पूर्णांक ret;
	u32 mask_val = 1 << wdt->drv_data->mask_bit;
	u32 val = 0;

	/* No need to करो anything अगर no PMU CONFIG needed */
	अगर (!(wdt->drv_data->quirks & QUIRK_HAS_PMU_CONFIG))
		वापस 0;

	अगर (mask)
		val = mask_val;

	ret = regmap_update_bits(wdt->pmureg,
			wdt->drv_data->disable_reg,
			mask_val, val);
	अगर (ret < 0)
		जाओ error;

	ret = regmap_update_bits(wdt->pmureg,
			wdt->drv_data->mask_reset_reg,
			mask_val, val);
 error:
	अगर (ret < 0)
		dev_err(wdt->dev, "failed to update reg(%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c2410wdt_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा s3c2410_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->lock);
	ग_लिखोl(wdt->count, wdt->reg_base + S3C2410_WTCNT);
	spin_unlock(&wdt->lock);

	वापस 0;
पूर्ण

अटल व्योम __s3c2410wdt_stop(काष्ठा s3c2410_wdt *wdt)
अणु
	अचिन्हित दीर्घ wtcon;

	wtcon = पढ़ोl(wdt->reg_base + S3C2410_WTCON);
	wtcon &= ~(S3C2410_WTCON_ENABLE | S3C2410_WTCON_RSTEN);
	ग_लिखोl(wtcon, wdt->reg_base + S3C2410_WTCON);
पूर्ण

अटल पूर्णांक s3c2410wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा s3c2410_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->lock);
	__s3c2410wdt_stop(wdt);
	spin_unlock(&wdt->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	अचिन्हित दीर्घ wtcon;
	काष्ठा s3c2410_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->lock);

	__s3c2410wdt_stop(wdt);

	wtcon = पढ़ोl(wdt->reg_base + S3C2410_WTCON);
	wtcon |= S3C2410_WTCON_ENABLE | S3C2410_WTCON_DIV128;

	अगर (soft_noboot) अणु
		wtcon |= S3C2410_WTCON_INTEN;
		wtcon &= ~S3C2410_WTCON_RSTEN;
	पूर्ण अन्यथा अणु
		wtcon &= ~S3C2410_WTCON_INTEN;
		wtcon |= S3C2410_WTCON_RSTEN;
	पूर्ण

	dev_dbg(wdt->dev, "Starting watchdog: count=0x%08x, wtcon=%08lx\n",
		wdt->count, wtcon);

	ग_लिखोl(wdt->count, wdt->reg_base + S3C2410_WTDAT);
	ग_लिखोl(wdt->count, wdt->reg_base + S3C2410_WTCNT);
	ग_लिखोl(wtcon, wdt->reg_base + S3C2410_WTCON);
	spin_unlock(&wdt->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410wdt_is_running(काष्ठा s3c2410_wdt *wdt)
अणु
	वापस पढ़ोl(wdt->reg_base + S3C2410_WTCON) & S3C2410_WTCON_ENABLE;
पूर्ण

अटल पूर्णांक s3c2410wdt_set_heartbeat(काष्ठा watchकरोg_device *wdd,
				    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा s3c2410_wdt *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित दीर्घ freq = clk_get_rate(wdt->घड़ी);
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक भागisor = 1;
	अचिन्हित दीर्घ wtcon;

	अगर (समयout < 1)
		वापस -EINVAL;

	freq = DIV_ROUND_UP(freq, 128);
	count = समयout * freq;

	dev_dbg(wdt->dev, "Heartbeat: count=%d, timeout=%d, freq=%lu\n",
		count, समयout, freq);

	/* अगर the count is bigger than the watchकरोg रेजिस्टर,
	   then work out what we need to करो (and अगर) we can
	   actually make this value
	*/

	अगर (count >= 0x10000) अणु
		भागisor = DIV_ROUND_UP(count, 0xffff);

		अगर (भागisor > 0x100) अणु
			dev_err(wdt->dev, "timeout %d too big\n", समयout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(wdt->dev, "Heartbeat: timeout=%d, divisor=%d, count=%d (%08x)\n",
		समयout, भागisor, count, DIV_ROUND_UP(count, भागisor));

	count = DIV_ROUND_UP(count, भागisor);
	wdt->count = count;

	/* update the pre-scaler */
	wtcon = पढ़ोl(wdt->reg_base + S3C2410_WTCON);
	wtcon &= ~S3C2410_WTCON_PRESCALE_MASK;
	wtcon |= S3C2410_WTCON_PRESCALE(भागisor-1);

	ग_लिखोl(count, wdt->reg_base + S3C2410_WTDAT);
	ग_लिखोl(wtcon, wdt->reg_base + S3C2410_WTCON);

	wdd->समयout = (count * भागisor) / freq;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410wdt_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	काष्ठा s3c2410_wdt *wdt = watchकरोg_get_drvdata(wdd);
	व्योम __iomem *wdt_base = wdt->reg_base;

	/* disable watchकरोg, to be safe  */
	ग_लिखोl(0, wdt_base + S3C2410_WTCON);

	/* put initial values पूर्णांकo count and data */
	ग_लिखोl(0x80, wdt_base + S3C2410_WTCNT);
	ग_लिखोl(0x80, wdt_base + S3C2410_WTDAT);

	/* set the watchकरोg to go and reset... */
	ग_लिखोl(S3C2410_WTCON_ENABLE | S3C2410_WTCON_DIV16 |
		S3C2410_WTCON_RSTEN | S3C2410_WTCON_PRESCALE(0x20),
		wdt_base + S3C2410_WTCON);

	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	वापस 0;
पूर्ण

#घोषणा OPTIONS (WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE)

अटल स्थिर काष्ठा watchकरोg_info s3c2410_wdt_ident = अणु
	.options          =     OPTIONS,
	.firmware_version =	0,
	.identity         =	"S3C2410 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops s3c2410wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = s3c2410wdt_start,
	.stop = s3c2410wdt_stop,
	.ping = s3c2410wdt_keepalive,
	.set_समयout = s3c2410wdt_set_heartbeat,
	.restart = s3c2410wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_device s3c2410_wdd = अणु
	.info = &s3c2410_wdt_ident,
	.ops = &s3c2410wdt_ops,
	.समयout = S3C2410_WATCHDOG_DEFAULT_TIME,
पूर्ण;

/* पूर्णांकerrupt handler code */

अटल irqवापस_t s3c2410wdt_irq(पूर्णांक irqno, व्योम *param)
अणु
	काष्ठा s3c2410_wdt *wdt = platक्रमm_get_drvdata(param);

	dev_info(wdt->dev, "watchdog timer expired (irq)\n");

	s3c2410wdt_keepalive(&wdt->wdt_device);

	अगर (wdt->drv_data->quirks & QUIRK_HAS_WTCLRINT_REG)
		ग_लिखोl(0x1, wdt->reg_base + S3C2410_WTCLRINT);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ

अटल पूर्णांक s3c2410wdt_cpufreq_transition(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ val, व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा s3c2410_wdt *wdt = freq_to_wdt(nb);

	अगर (!s3c2410wdt_is_running(wdt))
		जाओ करोne;

	अगर (val == CPUFREQ_PRECHANGE) अणु
		/* To ensure that over the change we करोn't cause the
		 * watchकरोg to trigger, we perक्रमm an keep-alive अगर
		 * the watchकरोg is running.
		 */

		s3c2410wdt_keepalive(&wdt->wdt_device);
	पूर्ण अन्यथा अगर (val == CPUFREQ_POSTCHANGE) अणु
		s3c2410wdt_stop(&wdt->wdt_device);

		ret = s3c2410wdt_set_heartbeat(&wdt->wdt_device,
						wdt->wdt_device.समयout);

		अगर (ret >= 0)
			s3c2410wdt_start(&wdt->wdt_device);
		अन्यथा
			जाओ err;
	पूर्ण

करोne:
	वापस 0;

 err:
	dev_err(wdt->dev, "cannot set new value for timeout %d\n",
				wdt->wdt_device.समयout);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410wdt_cpufreq_रेजिस्टर(काष्ठा s3c2410_wdt *wdt)
अणु
	wdt->freq_transition.notअगरier_call = s3c2410wdt_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&wdt->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम s3c2410wdt_cpufreq_deरेजिस्टर(काष्ठा s3c2410_wdt *wdt)
अणु
	wdt->freq_transition.notअगरier_call = s3c2410wdt_cpufreq_transition;

	cpufreq_unरेजिस्टर_notअगरier(&wdt->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक s3c2410wdt_cpufreq_रेजिस्टर(काष्ठा s3c2410_wdt *wdt)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s3c2410wdt_cpufreq_deरेजिस्टर(काष्ठा s3c2410_wdt *wdt)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक s3c2410wdt_get_bootstatus(काष्ठा s3c2410_wdt *wdt)
अणु
	अचिन्हित पूर्णांक rst_stat;
	पूर्णांक ret;

	अगर (!(wdt->drv_data->quirks & QUIRK_HAS_RST_STAT))
		वापस 0;

	ret = regmap_पढ़ो(wdt->pmureg, wdt->drv_data->rst_stat_reg, &rst_stat);
	अगर (ret)
		dev_warn(wdt->dev, "Couldn't get RST_STAT register\n");
	अन्यथा अगर (rst_stat & BIT(wdt->drv_data->rst_stat_bit))
		वापस WDIOF_CARDRESET;

	वापस 0;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा s3c2410_wdt_variant *
s3c2410_get_wdt_drv_data(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा s3c2410_wdt_variant *variant;

	variant = of_device_get_match_data(&pdev->dev);
	अगर (!variant) अणु
		/* Device matched by platक्रमm_device_id */
		variant = (काष्ठा s3c2410_wdt_variant *)
			   platक्रमm_get_device_id(pdev)->driver_data;
	पूर्ण

	वापस variant;
पूर्ण

अटल पूर्णांक s3c2410wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s3c2410_wdt *wdt;
	काष्ठा resource *wdt_irq;
	अचिन्हित पूर्णांक wtcon;
	पूर्णांक started = 0;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->dev = dev;
	spin_lock_init(&wdt->lock);
	wdt->wdt_device = s3c2410_wdd;

	wdt->drv_data = s3c2410_get_wdt_drv_data(pdev);
	अगर (wdt->drv_data->quirks & QUIRKS_HAVE_PMUREG) अणु
		wdt->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
						"samsung,syscon-phandle");
		अगर (IS_ERR(wdt->pmureg)) अणु
			dev_err(dev, "syscon regmap lookup failed.\n");
			वापस PTR_ERR(wdt->pmureg);
		पूर्ण
	पूर्ण

	wdt_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (wdt_irq == शून्य) अणु
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	/* get the memory region क्रम the watchकरोg समयr */
	wdt->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->reg_base)) अणु
		ret = PTR_ERR(wdt->reg_base);
		जाओ err;
	पूर्ण

	wdt->घड़ी = devm_clk_get(dev, "watchdog");
	अगर (IS_ERR(wdt->घड़ी)) अणु
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = PTR_ERR(wdt->घड़ी);
		जाओ err;
	पूर्ण

	ret = clk_prepare_enable(wdt->घड़ी);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	wdt->wdt_device.min_समयout = 1;
	wdt->wdt_device.max_समयout = s3c2410wdt_max_समयout(wdt->घड़ी);

	ret = s3c2410wdt_cpufreq_रेजिस्टर(wdt);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register cpufreq\n");
		जाओ err_clk;
	पूर्ण

	watchकरोg_set_drvdata(&wdt->wdt_device, wdt);

	/* see अगर we can actually set the requested समयr margin, and अगर
	 * not, try the शेष value */

	watchकरोg_init_समयout(&wdt->wdt_device, पंचांगr_margin, dev);
	ret = s3c2410wdt_set_heartbeat(&wdt->wdt_device,
					wdt->wdt_device.समयout);
	अगर (ret) अणु
		started = s3c2410wdt_set_heartbeat(&wdt->wdt_device,
					S3C2410_WATCHDOG_DEFAULT_TIME);

		अगर (started == 0)
			dev_info(dev,
				 "tmr_margin value out of range, default %d used\n",
				 S3C2410_WATCHDOG_DEFAULT_TIME);
		अन्यथा
			dev_info(dev, "default timer value is out of range, cannot start\n");
	पूर्ण

	ret = devm_request_irq(dev, wdt_irq->start, s3c2410wdt_irq, 0,
				pdev->name, pdev);
	अगर (ret != 0) अणु
		dev_err(dev, "failed to install irq (%d)\n", ret);
		जाओ err_cpufreq;
	पूर्ण

	watchकरोg_set_nowayout(&wdt->wdt_device, nowayout);
	watchकरोg_set_restart_priority(&wdt->wdt_device, 128);

	wdt->wdt_device.bootstatus = s3c2410wdt_get_bootstatus(wdt);
	wdt->wdt_device.parent = dev;

	ret = watchकरोg_रेजिस्टर_device(&wdt->wdt_device);
	अगर (ret)
		जाओ err_cpufreq;

	ret = s3c2410wdt_mask_and_disable_reset(wdt, false);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर;

	अगर (पंचांगr_atboot && started == 0) अणु
		dev_info(dev, "starting watchdog timer\n");
		s3c2410wdt_start(&wdt->wdt_device);
	पूर्ण अन्यथा अगर (!पंचांगr_atboot) अणु
		/* अगर we're not enabling the watchकरोg, then ensure it is
		 * disabled अगर it has been left running from the bootloader
		 * or other source */

		s3c2410wdt_stop(&wdt->wdt_device);
	पूर्ण

	platक्रमm_set_drvdata(pdev, wdt);

	/* prपूर्णांक out a statement of पढ़ोiness */

	wtcon = पढ़ोl(wdt->reg_base + S3C2410_WTCON);

	dev_info(dev, "watchdog %sactive, reset %sabled, irq %sabled\n",
		 (wtcon & S3C2410_WTCON_ENABLE) ?  "" : "in",
		 (wtcon & S3C2410_WTCON_RSTEN) ? "en" : "dis",
		 (wtcon & S3C2410_WTCON_INTEN) ? "en" : "dis");

	वापस 0;

 err_unरेजिस्टर:
	watchकरोg_unरेजिस्टर_device(&wdt->wdt_device);

 err_cpufreq:
	s3c2410wdt_cpufreq_deरेजिस्टर(wdt);

 err_clk:
	clk_disable_unprepare(wdt->घड़ी);

 err:
	वापस ret;
पूर्ण

अटल पूर्णांक s3c2410wdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा s3c2410_wdt *wdt = platक्रमm_get_drvdata(dev);

	ret = s3c2410wdt_mask_and_disable_reset(wdt, true);
	अगर (ret < 0)
		वापस ret;

	watchकरोg_unरेजिस्टर_device(&wdt->wdt_device);

	s3c2410wdt_cpufreq_deरेजिस्टर(wdt);

	clk_disable_unprepare(wdt->घड़ी);

	वापस 0;
पूर्ण

अटल व्योम s3c2410wdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c2410_wdt *wdt = platक्रमm_get_drvdata(dev);

	s3c2410wdt_mask_and_disable_reset(wdt, true);

	s3c2410wdt_stop(&wdt->wdt_device);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक s3c2410wdt_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा s3c2410_wdt *wdt = dev_get_drvdata(dev);

	/* Save watchकरोg state, and turn it off. */
	wdt->wtcon_save = पढ़ोl(wdt->reg_base + S3C2410_WTCON);
	wdt->wtdat_save = पढ़ोl(wdt->reg_base + S3C2410_WTDAT);

	ret = s3c2410wdt_mask_and_disable_reset(wdt, true);
	अगर (ret < 0)
		वापस ret;

	/* Note that WTCNT करोesn't need to be saved. */
	s3c2410wdt_stop(&wdt->wdt_device);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410wdt_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा s3c2410_wdt *wdt = dev_get_drvdata(dev);

	/* Restore watchकरोg state. */
	ग_लिखोl(wdt->wtdat_save, wdt->reg_base + S3C2410_WTDAT);
	ग_लिखोl(wdt->wtdat_save, wdt->reg_base + S3C2410_WTCNT);/* Reset count */
	ग_लिखोl(wdt->wtcon_save, wdt->reg_base + S3C2410_WTCON);

	ret = s3c2410wdt_mask_and_disable_reset(wdt, false);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "watchdog %sabled\n",
		(wdt->wtcon_save & S3C2410_WTCON_ENABLE) ? "en" : "dis");

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(s3c2410wdt_pm_ops, s3c2410wdt_suspend,
			s3c2410wdt_resume);

अटल काष्ठा platक्रमm_driver s3c2410wdt_driver = अणु
	.probe		= s3c2410wdt_probe,
	.हटाओ		= s3c2410wdt_हटाओ,
	.shutकरोwn	= s3c2410wdt_shutकरोwn,
	.id_table	= s3c2410_wdt_ids,
	.driver		= अणु
		.name	= "s3c2410-wdt",
		.pm	= &s3c2410wdt_pm_ops,
		.of_match_table	= of_match_ptr(s3c2410_wdt_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c2410wdt_driver);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>, Dimitry Andric <dimitry.andric@tomtom.com>");
MODULE_DESCRIPTION("S3C2410 Watchdog Device Driver");
MODULE_LICENSE("GPL");
