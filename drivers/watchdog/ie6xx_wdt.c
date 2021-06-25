<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *      Intel Atom E6xx Watchकरोg driver
 *
 *      Copyright (C) 2011 Alexander Stein
 *                <alexander.stein@systec-electronic.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/spinlock.h>

#घोषणा DRIVER_NAME "ie6xx_wdt"

#घोषणा PV1	0x00
#घोषणा PV2	0x04

#घोषणा RR0	0x0c
#घोषणा RR1	0x0d
#घोषणा WDT_RELOAD	0x01
#घोषणा WDT_TOUT	0x02

#घोषणा WDTCR	0x10
#घोषणा WDT_PRE_SEL	0x04
#घोषणा WDT_RESET_SEL	0x08
#घोषणा WDT_RESET_EN	0x10
#घोषणा WDT_TOUT_EN	0x20

#घोषणा DCR	0x14

#घोषणा WDTLR	0x18
#घोषणा WDT_LOCK	0x01
#घोषणा WDT_ENABLE	0x02
#घोषणा WDT_TOUT_CNF	0x03

#घोषणा MIN_TIME	1
#घोषणा MAX_TIME	(10 * 60) /* 10 minutes */
#घोषणा DEFAULT_TIME	60

अटल अचिन्हित पूर्णांक समयout = DEFAULT_TIME;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Default Watchdog timer setting ("
		__MODULE_STRING(DEFAULT_TIME) "s)."
		"The range is from 1 to 600");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल u8 reseपंचांगode = 0x10;
module_param(reseपंचांगode, byte, 0);
MODULE_PARM_DESC(reseपंचांगode,
	"Resetmode bits: 0x08 warm reset (cold reset otherwise), "
	"0x10 reset enable, 0x20 disable toggle GPIO[4] (default=0x10)");

अटल काष्ठा अणु
	अचिन्हित लघु sch_wdtba;
	spinlock_t unlock_sequence;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
पूर्ण ie6xx_wdt_data;

/*
 * This is needed to ग_लिखो to preload and reload रेजिस्टरs
 * काष्ठा ie6xx_wdt_data.unlock_sequence must be used
 * to prevent sequence पूर्णांकerrupts
 */
अटल व्योम ie6xx_wdt_unlock_रेजिस्टरs(व्योम)
अणु
	outb(0x80, ie6xx_wdt_data.sch_wdtba + RR0);
	outb(0x86, ie6xx_wdt_data.sch_wdtba + RR0);
पूर्ण

अटल पूर्णांक ie6xx_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	spin_lock(&ie6xx_wdt_data.unlock_sequence);
	ie6xx_wdt_unlock_रेजिस्टरs();
	outb(WDT_RELOAD, ie6xx_wdt_data.sch_wdtba + RR1);
	spin_unlock(&ie6xx_wdt_data.unlock_sequence);
	वापस 0;
पूर्ण

अटल पूर्णांक ie6xx_wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक t)
अणु
	u32 preload;
	u64 घड़ी;
	u8 wdtcr;

	/* Watchकरोg घड़ी is PCI Clock (33MHz) */
	घड़ी = 33000000;
	/* and the preload value is loaded पूर्णांकo [34:15] of the करोwn counter */
	preload = (t * घड़ी) >> 15;
	/*
	 * Manual states preload must be one less.
	 * Does not wrap as t is at least 1
	 */
	preload -= 1;

	spin_lock(&ie6xx_wdt_data.unlock_sequence);

	/* Set ResetMode & Enable prescaler क्रम range 10ms to 10 min */
	wdtcr = reseपंचांगode & 0x38;
	outb(wdtcr, ie6xx_wdt_data.sch_wdtba + WDTCR);

	ie6xx_wdt_unlock_रेजिस्टरs();
	outl(0, ie6xx_wdt_data.sch_wdtba + PV1);

	ie6xx_wdt_unlock_रेजिस्टरs();
	outl(preload, ie6xx_wdt_data.sch_wdtba + PV2);

	ie6xx_wdt_unlock_रेजिस्टरs();
	outb(WDT_RELOAD | WDT_TOUT, ie6xx_wdt_data.sch_wdtba + RR1);

	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	wdd->समयout = t;
	वापस 0;
पूर्ण

अटल पूर्णांक ie6xx_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	ie6xx_wdt_set_समयout(wdd, wdd->समयout);

	/* Enable the watchकरोg समयr */
	spin_lock(&ie6xx_wdt_data.unlock_sequence);
	outb(WDT_ENABLE, ie6xx_wdt_data.sch_wdtba + WDTLR);
	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	वापस 0;
पूर्ण

अटल पूर्णांक ie6xx_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	अगर (inb(ie6xx_wdt_data.sch_wdtba + WDTLR) & WDT_LOCK)
		वापस -1;

	/* Disable the watchकरोg समयr */
	spin_lock(&ie6xx_wdt_data.unlock_sequence);
	outb(0, ie6xx_wdt_data.sch_wdtba + WDTLR);
	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ie6xx_wdt_info = अणु
	.identity =	"Intel Atom E6xx Watchdog",
	.options =	WDIOF_SETTIMEOUT |
			WDIOF_MAGICCLOSE |
			WDIOF_KEEPALIVEPING,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ie6xx_wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	ie6xx_wdt_start,
	.stop =		ie6xx_wdt_stop,
	.ping =		ie6xx_wdt_ping,
	.set_समयout =	ie6xx_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device ie6xx_wdt_dev = अणु
	.info =		&ie6xx_wdt_info,
	.ops =		&ie6xx_wdt_ops,
	.min_समयout =	MIN_TIME,
	.max_समयout =	MAX_TIME,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक ie6xx_wdt_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	seq_म_लिखो(s, "PV1   = 0x%08x\n",
		inl(ie6xx_wdt_data.sch_wdtba + PV1));
	seq_म_लिखो(s, "PV2   = 0x%08x\n",
		inl(ie6xx_wdt_data.sch_wdtba + PV2));
	seq_म_लिखो(s, "RR    = 0x%08x\n",
		inw(ie6xx_wdt_data.sch_wdtba + RR0));
	seq_म_लिखो(s, "WDTCR = 0x%08x\n",
		inw(ie6xx_wdt_data.sch_wdtba + WDTCR));
	seq_म_लिखो(s, "DCR   = 0x%08x\n",
		inl(ie6xx_wdt_data.sch_wdtba + DCR));
	seq_म_लिखो(s, "WDTLR = 0x%08x\n",
		inw(ie6xx_wdt_data.sch_wdtba + WDTLR));

	seq_म_लिखो(s, "\n");
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ie6xx_wdt);

अटल व्योम ie6xx_wdt_debugfs_init(व्योम)
अणु
	/* /sys/kernel/debug/ie6xx_wdt */
	ie6xx_wdt_data.debugfs = debugfs_create_file("ie6xx_wdt",
		S_IFREG | S_IRUGO, शून्य, शून्य, &ie6xx_wdt_fops);
पूर्ण

अटल व्योम ie6xx_wdt_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ(ie6xx_wdt_data.debugfs);
पूर्ण

#अन्यथा
अटल व्योम ie6xx_wdt_debugfs_init(व्योम)
अणु
पूर्ण

अटल व्योम ie6xx_wdt_debugfs_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ie6xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	u8 wdtlr;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!request_region(res->start, resource_size(res), pdev->name)) अणु
		dev_err(&pdev->dev, "Watchdog region 0x%llx already in use!\n",
			(u64)res->start);
		वापस -EBUSY;
	पूर्ण

	ie6xx_wdt_data.sch_wdtba = res->start;
	dev_dbg(&pdev->dev, "WDT = 0x%X\n", ie6xx_wdt_data.sch_wdtba);

	ie6xx_wdt_dev.समयout = समयout;
	watchकरोg_set_nowayout(&ie6xx_wdt_dev, nowayout);
	ie6xx_wdt_dev.parent = &pdev->dev;

	spin_lock_init(&ie6xx_wdt_data.unlock_sequence);

	wdtlr = inb(ie6xx_wdt_data.sch_wdtba + WDTLR);
	अगर (wdtlr & WDT_LOCK)
		dev_warn(&pdev->dev,
			"Watchdog Timer is Locked (Reg=0x%x)\n", wdtlr);

	ie6xx_wdt_debugfs_init();

	ret = watchकरोg_रेजिस्टर_device(&ie6xx_wdt_dev);
	अगर (ret)
		जाओ misc_रेजिस्टर_error;

	वापस 0;

misc_रेजिस्टर_error:
	ie6xx_wdt_debugfs_निकास();
	release_region(res->start, resource_size(res));
	ie6xx_wdt_data.sch_wdtba = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक ie6xx_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	ie6xx_wdt_stop(शून्य);
	watchकरोg_unरेजिस्टर_device(&ie6xx_wdt_dev);
	ie6xx_wdt_debugfs_निकास();
	release_region(res->start, resource_size(res));
	ie6xx_wdt_data.sch_wdtba = 0;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ie6xx_wdt_driver = अणु
	.probe		= ie6xx_wdt_probe,
	.हटाओ		= ie6xx_wdt_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ie6xx_wdt_init(व्योम)
अणु
	/* Check boot parameters to verअगरy that their initial values */
	/* are in range. */
	अगर ((समयout < MIN_TIME) ||
	    (समयout > MAX_TIME)) अणु
		pr_err("Watchdog timer: value of timeout %d (dec) "
		  "is out of range from %d to %d (dec)\n",
		  समयout, MIN_TIME, MAX_TIME);
		वापस -EINVAL;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&ie6xx_wdt_driver);
पूर्ण

अटल व्योम __निकास ie6xx_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ie6xx_wdt_driver);
पूर्ण

late_initcall(ie6xx_wdt_init);
module_निकास(ie6xx_wdt_निकास);

MODULE_AUTHOR("Alexander Stein <alexander.stein@systec-electronic.com>");
MODULE_DESCRIPTION("Intel Atom E6xx Watchdog Device Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
