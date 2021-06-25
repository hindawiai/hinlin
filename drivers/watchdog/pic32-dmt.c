<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PIC32 deadman समयr driver
 *
 * Purna Chandra Mandal <purna.mandal@microchip.com>
 * Copyright (c) 2016, Microchip Technology Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/watchकरोg.h>

#समावेश <यंत्र/mach-pic32/pic32.h>

/* Deadman Timer Regs */
#घोषणा DMTCON_REG	0x00
#घोषणा DMTPRECLR_REG	0x10
#घोषणा DMTCLR_REG	0x20
#घोषणा DMTSTAT_REG	0x30
#घोषणा DMTCNT_REG	0x40
#घोषणा DMTPSCNT_REG	0x60
#घोषणा DMTPSINTV_REG	0x70

/* Deadman Timer Regs fields */
#घोषणा DMT_ON			BIT(15)
#घोषणा DMT_STEP1_KEY		BIT(6)
#घोषणा DMT_STEP2_KEY		BIT(3)
#घोषणा DMTSTAT_WINOPN		BIT(0)
#घोषणा DMTSTAT_EVENT		BIT(5)
#घोषणा DMTSTAT_BAD2		BIT(6)
#घोषणा DMTSTAT_BAD1		BIT(7)

/* Reset Control Register fields क्रम watchकरोg */
#घोषणा RESETCON_DMT_TIMEOUT	BIT(5)

काष्ठा pic32_dmt अणु
	व्योम __iomem	*regs;
	काष्ठा clk	*clk;
पूर्ण;

अटल अंतरभूत व्योम dmt_enable(काष्ठा pic32_dmt *dmt)
अणु
	ग_लिखोl(DMT_ON, PIC32_SET(dmt->regs + DMTCON_REG));
पूर्ण

अटल अंतरभूत व्योम dmt_disable(काष्ठा pic32_dmt *dmt)
अणु
	ग_लिखोl(DMT_ON, PIC32_CLR(dmt->regs + DMTCON_REG));
	/*
	 * Cannot touch रेजिस्टरs in the CPU cycle following clearing the
	 * ON bit.
	 */
	nop();
पूर्ण

अटल अंतरभूत पूर्णांक dmt_bad_status(काष्ठा pic32_dmt *dmt)
अणु
	u32 val;

	val = पढ़ोl(dmt->regs + DMTSTAT_REG);
	val &= (DMTSTAT_BAD1 | DMTSTAT_BAD2 | DMTSTAT_EVENT);
	अगर (val)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dmt_keepalive(काष्ठा pic32_dmt *dmt)
अणु
	u32 v;
	u32 समयout = 500;

	/* set pre-clear key */
	ग_लिखोl(DMT_STEP1_KEY << 8, dmt->regs + DMTPRECLR_REG);

	/* रुको क्रम DMT winकरोw to खोलो */
	जबतक (--समयout) अणु
		v = पढ़ोl(dmt->regs + DMTSTAT_REG) & DMTSTAT_WINOPN;
		अगर (v == DMTSTAT_WINOPN)
			अवरोध;
	पूर्ण

	/* apply key2 */
	ग_लिखोl(DMT_STEP2_KEY, dmt->regs + DMTCLR_REG);

	/* check whether keys are latched correctly */
	वापस dmt_bad_status(dmt);
पूर्ण

अटल अंतरभूत u32 pic32_dmt_get_समयout_secs(काष्ठा pic32_dmt *dmt)
अणु
	अचिन्हित दीर्घ rate;

	rate = clk_get_rate(dmt->clk);
	अगर (rate)
		वापस पढ़ोl(dmt->regs + DMTPSCNT_REG) / rate;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 pic32_dmt_bootstatus(काष्ठा pic32_dmt *dmt)
अणु
	u32 v;
	व्योम __iomem *rst_base;

	rst_base = ioremap(PIC32_BASE_RESET, 0x10);
	अगर (!rst_base)
		वापस 0;

	v = पढ़ोl(rst_base);

	ग_लिखोl(RESETCON_DMT_TIMEOUT, PIC32_CLR(rst_base));

	iounmap(rst_base);
	वापस v & RESETCON_DMT_TIMEOUT;
पूर्ण

अटल पूर्णांक pic32_dmt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_dmt *dmt = watchकरोg_get_drvdata(wdd);

	dmt_enable(dmt);
	वापस dmt_keepalive(dmt);
पूर्ण

अटल पूर्णांक pic32_dmt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_dmt *dmt = watchकरोg_get_drvdata(wdd);

	dmt_disable(dmt);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_dmt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_dmt *dmt = watchकरोg_get_drvdata(wdd);

	वापस dmt_keepalive(dmt);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops pic32_dmt_fops = अणु
	.owner		= THIS_MODULE,
	.start		= pic32_dmt_start,
	.stop		= pic32_dmt_stop,
	.ping		= pic32_dmt_ping,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info pic32_dmt_ident = अणु
	.options	= WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
	.identity	= "PIC32 Deadman Timer",
पूर्ण;

अटल काष्ठा watchकरोg_device pic32_dmt_wdd = अणु
	.info		= &pic32_dmt_ident,
	.ops		= &pic32_dmt_fops,
पूर्ण;

अटल व्योम pic32_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक pic32_dmt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	काष्ठा pic32_dmt *dmt;
	काष्ठा watchकरोg_device *wdd = &pic32_dmt_wdd;

	dmt = devm_kzalloc(dev, माप(*dmt), GFP_KERNEL);
	अगर (!dmt)
		वापस -ENOMEM;

	dmt->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dmt->regs))
		वापस PTR_ERR(dmt->regs);

	dmt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(dmt->clk)) अणु
		dev_err(dev, "clk not found\n");
		वापस PTR_ERR(dmt->clk);
	पूर्ण

	ret = clk_prepare_enable(dmt->clk);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(dev, pic32_clk_disable_unprepare,
				       dmt->clk);
	अगर (ret)
		वापस ret;

	wdd->समयout = pic32_dmt_get_समयout_secs(dmt);
	अगर (!wdd->समयout) अणु
		dev_err(dev, "failed to read watchdog register timeout\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "timeout %d\n", wdd->समयout);

	wdd->bootstatus = pic32_dmt_bootstatus(dmt) ? WDIOF_CARDRESET : 0;

	watchकरोg_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchकरोg_set_drvdata(wdd, dmt);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_dmt_of_ids[] = अणु
	अणु .compatible = "microchip,pic32mzda-dmt",पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_dmt_of_ids);

अटल काष्ठा platक्रमm_driver pic32_dmt_driver = अणु
	.probe		= pic32_dmt_probe,
	.driver		= अणु
		.name		= "pic32-dmt",
		.of_match_table = of_match_ptr(pic32_dmt_of_ids),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(pic32_dmt_driver);

MODULE_AUTHOR("Purna Chandra Mandal <purna.mandal@microchip.com>");
MODULE_DESCRIPTION("Microchip PIC32 DMT Driver");
MODULE_LICENSE("GPL");
