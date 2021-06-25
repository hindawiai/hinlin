<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Nuvoton Technology corporation.
// Copyright (c) 2018 IBM Corp.

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

#घोषणा NPCM_WTCR	0x1C

#घोषणा NPCM_WTCLK	(BIT(10) | BIT(11))	/* Clock भागider */
#घोषणा NPCM_WTE	BIT(7)			/* Enable */
#घोषणा NPCM_WTIE	BIT(6)			/* Enable irq */
#घोषणा NPCM_WTIS	(BIT(4) | BIT(5))	/* Interval selection */
#घोषणा NPCM_WTIF	BIT(3)			/* Interrupt flag*/
#घोषणा NPCM_WTRF	BIT(2)			/* Reset flag */
#घोषणा NPCM_WTRE	BIT(1)			/* Reset enable */
#घोषणा NPCM_WTR	BIT(0)			/* Reset counter */

/*
 * Watchकरोg समयouts
 *
 * 170     msec:    WTCLK=01 WTIS=00     VAL= 0x400
 * 670     msec:    WTCLK=01 WTIS=01     VAL= 0x410
 * 1360    msec:    WTCLK=10 WTIS=00     VAL= 0x800
 * 2700    msec:    WTCLK=01 WTIS=10     VAL= 0x420
 * 5360    msec:    WTCLK=10 WTIS=01     VAL= 0x810
 * 10700   msec:    WTCLK=01 WTIS=11     VAL= 0x430
 * 21600   msec:    WTCLK=10 WTIS=10     VAL= 0x820
 * 43000   msec:    WTCLK=11 WTIS=00     VAL= 0xC00
 * 85600   msec:    WTCLK=10 WTIS=11     VAL= 0x830
 * 172000  msec:    WTCLK=11 WTIS=01     VAL= 0xC10
 * 687000  msec:    WTCLK=11 WTIS=10     VAL= 0xC20
 * 2750000 msec:    WTCLK=11 WTIS=11     VAL= 0xC30
 */

काष्ठा npcm_wdt अणु
	काष्ठा watchकरोg_device  wdd;
	व्योम __iomem		*reg;
पूर्ण;

अटल अंतरभूत काष्ठा npcm_wdt *to_npcm_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा npcm_wdt, wdd);
पूर्ण

अटल पूर्णांक npcm_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा npcm_wdt *wdt = to_npcm_wdt(wdd);
	u32 val;

	val = पढ़ोl(wdt->reg);
	ग_लिखोl(val | NPCM_WTR, wdt->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा npcm_wdt *wdt = to_npcm_wdt(wdd);
	u32 val;

	अगर (wdd->समयout < 2)
		val = 0x800;
	अन्यथा अगर (wdd->समयout < 3)
		val = 0x420;
	अन्यथा अगर (wdd->समयout < 6)
		val = 0x810;
	अन्यथा अगर (wdd->समयout < 11)
		val = 0x430;
	अन्यथा अगर (wdd->समयout < 22)
		val = 0x820;
	अन्यथा अगर (wdd->समयout < 44)
		val = 0xC00;
	अन्यथा अगर (wdd->समयout < 87)
		val = 0x830;
	अन्यथा अगर (wdd->समयout < 173)
		val = 0xC10;
	अन्यथा अगर (wdd->समयout < 688)
		val = 0xC20;
	अन्यथा
		val = 0xC30;

	val |= NPCM_WTRE | NPCM_WTE | NPCM_WTR | NPCM_WTIE;

	ग_लिखोl(val, wdt->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा npcm_wdt *wdt = to_npcm_wdt(wdd);

	ग_लिखोl(0, wdt->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				अचिन्हित पूर्णांक समयout)
अणु
	अगर (समयout < 2)
		wdd->समयout = 1;
	अन्यथा अगर (समयout < 3)
		wdd->समयout = 2;
	अन्यथा अगर (समयout < 6)
		wdd->समयout = 5;
	अन्यथा अगर (समयout < 11)
		wdd->समयout = 10;
	अन्यथा अगर (समयout < 22)
		wdd->समयout = 21;
	अन्यथा अगर (समयout < 44)
		wdd->समयout = 43;
	अन्यथा अगर (समयout < 87)
		wdd->समयout = 86;
	अन्यथा अगर (समयout < 173)
		wdd->समयout = 172;
	अन्यथा अगर (समयout < 688)
		wdd->समयout = 687;
	अन्यथा
		wdd->समयout = 2750;

	अगर (watchकरोg_active(wdd))
		npcm_wdt_start(wdd);

	वापस 0;
पूर्ण

अटल irqवापस_t npcm_wdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा npcm_wdt *wdt = data;

	watchकरोg_notअगरy_preसमयout(&wdt->wdd);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक npcm_wdt_restart(काष्ठा watchकरोg_device *wdd,
			    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा npcm_wdt *wdt = to_npcm_wdt(wdd);

	ग_लिखोl(NPCM_WTR | NPCM_WTRE | NPCM_WTE, wdt->reg);
	udelay(1000);

	वापस 0;
पूर्ण

अटल bool npcm_is_running(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा npcm_wdt *wdt = to_npcm_wdt(wdd);

	वापस पढ़ोl(wdt->reg) & NPCM_WTE;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info npcm_wdt_info = अणु
	.identity	= KBUILD_MODNAME,
	.options	= WDIOF_SETTIMEOUT
			| WDIOF_KEEPALIVEPING
			| WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops npcm_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = npcm_wdt_start,
	.stop = npcm_wdt_stop,
	.ping = npcm_wdt_ping,
	.set_समयout = npcm_wdt_set_समयout,
	.restart = npcm_wdt_restart,
पूर्ण;

अटल पूर्णांक npcm_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा npcm_wdt *wdt;
	पूर्णांक irq;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->reg))
		वापस PTR_ERR(wdt->reg);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	wdt->wdd.info = &npcm_wdt_info;
	wdt->wdd.ops = &npcm_wdt_ops;
	wdt->wdd.min_समयout = 1;
	wdt->wdd.max_समयout = 2750;
	wdt->wdd.parent = dev;

	wdt->wdd.समयout = 86;
	watchकरोg_init_समयout(&wdt->wdd, 0, dev);

	/* Ensure समयout is able to be represented by the hardware */
	npcm_wdt_set_समयout(&wdt->wdd, wdt->wdd.समयout);

	अगर (npcm_is_running(&wdt->wdd)) अणु
		/* Restart with the शेष or device-tree specअगरied समयout */
		npcm_wdt_start(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	पूर्ण

	ret = devm_request_irq(dev, irq, npcm_wdt_पूर्णांकerrupt, 0, "watchdog",
			       wdt);
	अगर (ret)
		वापस ret;

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev, "NPCM watchdog driver enabled\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id npcm_wdt_match[] = अणु
	अणु.compatible = "nuvoton,wpcm450-wdt"पूर्ण,
	अणु.compatible = "nuvoton,npcm750-wdt"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm_wdt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver npcm_wdt_driver = अणु
	.probe		= npcm_wdt_probe,
	.driver		= अणु
		.name	= "npcm-wdt",
		.of_match_table = of_match_ptr(npcm_wdt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(npcm_wdt_driver);

MODULE_AUTHOR("Joel Stanley");
MODULE_DESCRIPTION("Watchdog driver for NPCM");
MODULE_LICENSE("GPL v2");
