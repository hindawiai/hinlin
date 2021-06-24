<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा SECWDOG_CTRL_REG		0x00000000
#घोषणा SECWDOG_COUNT_REG		0x00000004

#घोषणा SECWDOG_RESERVED_MASK		0x1dffffff
#घोषणा SECWDOG_WD_LOAD_FLAG		0x10000000
#घोषणा SECWDOG_EN_MASK			0x08000000
#घोषणा SECWDOG_SRSTEN_MASK		0x04000000
#घोषणा SECWDOG_RES_MASK		0x00f00000
#घोषणा SECWDOG_COUNT_MASK		0x000fffff

#घोषणा SECWDOG_MAX_COUNT		SECWDOG_COUNT_MASK
#घोषणा SECWDOG_CLKS_SHIFT		20
#घोषणा SECWDOG_MAX_RES			15
#घोषणा SECWDOG_DEFAULT_RESOLUTION	4
#घोषणा SECWDOG_MAX_TRY			1000

#घोषणा SECS_TO_TICKS(x, w)		((x) << (w)->resolution)
#घोषणा TICKS_TO_SECS(x, w)		((x) >> (w)->resolution)

#घोषणा BCM_KONA_WDT_NAME		"bcm_kona_wdt"

काष्ठा bcm_kona_wdt अणु
	व्योम __iomem *base;
	/*
	 * One watchकरोg tick is 1/(2^resolution) seconds. Resolution can take
	 * the values 0-15, meaning one tick can be 1s to 30.52us. Our शेष
	 * resolution of 4 means one tick is 62.5ms.
	 *
	 * The watchकरोg counter is 20 bits. Depending on resolution, the maximum
	 * counter value of 0xfffff expires after about 12 days (resolution 0)
	 * करोwn to only 32s (resolution 15). The शेष resolution of 4 gives
	 * us a maximum of about 18 hours and 12 minutes beक्रमe the watchकरोg
	 * बार out.
	 */
	पूर्णांक resolution;
	spinlock_t lock;
#अगर_घोषित CONFIG_BCM_KONA_WDT_DEBUG
	अचिन्हित दीर्घ busy_count;
	काष्ठा dentry *debugfs;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक secure_रेजिस्टर_पढ़ो(काष्ठा bcm_kona_wdt *wdt, uपूर्णांक32_t offset)
अणु
	uपूर्णांक32_t val;
	अचिन्हित count = 0;

	/*
	 * If the WD_LOAD_FLAG is set, the watchकरोg counter field is being
	 * updated in hardware. Once the WD समयr is updated in hardware, it
	 * माला_लो cleared.
	 */
	करो अणु
		अगर (unlikely(count > 1))
			udelay(5);
		val = पढ़ोl_relaxed(wdt->base + offset);
		count++;
	पूर्ण जबतक ((val & SECWDOG_WD_LOAD_FLAG) && count < SECWDOG_MAX_TRY);

#अगर_घोषित CONFIG_BCM_KONA_WDT_DEBUG
	/* Remember the maximum number iterations due to WD_LOAD_FLAG */
	अगर (count > wdt->busy_count)
		wdt->busy_count = count;
#पूर्ण_अगर

	/* This is the only place we वापस a negative value. */
	अगर (val & SECWDOG_WD_LOAD_FLAG)
		वापस -ETIMEDOUT;

	/* We always mask out reserved bits. */
	val &= SECWDOG_RESERVED_MASK;

	वापस val;
पूर्ण

#अगर_घोषित CONFIG_BCM_KONA_WDT_DEBUG

अटल पूर्णांक bcm_kona_show(काष्ठा seq_file *s, व्योम *data)
अणु
	पूर्णांक ctl_val, cur_val;
	अचिन्हित दीर्घ flags;
	काष्ठा bcm_kona_wdt *wdt = s->निजी;

	अगर (!wdt) अणु
		seq_माला_दो(s, "No device pointer\n");
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&wdt->lock, flags);
	ctl_val = secure_रेजिस्टर_पढ़ो(wdt, SECWDOG_CTRL_REG);
	cur_val = secure_रेजिस्टर_पढ़ो(wdt, SECWDOG_COUNT_REG);
	spin_unlock_irqrestore(&wdt->lock, flags);

	अगर (ctl_val < 0 || cur_val < 0) अणु
		seq_माला_दो(s, "Error accessing hardware\n");
	पूर्ण अन्यथा अणु
		पूर्णांक ctl, cur, ctl_sec, cur_sec, res;

		ctl = ctl_val & SECWDOG_COUNT_MASK;
		res = (ctl_val & SECWDOG_RES_MASK) >> SECWDOG_CLKS_SHIFT;
		cur = cur_val & SECWDOG_COUNT_MASK;
		ctl_sec = TICKS_TO_SECS(ctl, wdt);
		cur_sec = TICKS_TO_SECS(cur, wdt);
		seq_म_लिखो(s,
			   "Resolution: %d / %d\n"
			   "Control: %d s / %d (%#x) ticks\n"
			   "Current: %d s / %d (%#x) ticks\n"
			   "Busy count: %lu\n",
			   res, wdt->resolution,
			   ctl_sec, ctl, ctl,
			   cur_sec, cur, cur,
			   wdt->busy_count);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(bcm_kona);

अटल व्योम bcm_kona_wdt_debug_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dentry *dir;
	काष्ठा bcm_kona_wdt *wdt = platक्रमm_get_drvdata(pdev);

	अगर (!wdt)
		वापस;

	wdt->debugfs = शून्य;

	dir = debugfs_create_dir(BCM_KONA_WDT_NAME, शून्य);

	debugfs_create_file("info", S_IFREG | S_IRUGO, dir, wdt,
			    &bcm_kona_fops);
	wdt->debugfs = dir;
पूर्ण

अटल व्योम bcm_kona_wdt_debug_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_kona_wdt *wdt = platक्रमm_get_drvdata(pdev);

	अगर (wdt)
		debugfs_हटाओ_recursive(wdt->debugfs);
पूर्ण

#अन्यथा

अटल व्योम bcm_kona_wdt_debug_init(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
अटल व्योम bcm_kona_wdt_debug_निकास(काष्ठा platक्रमm_device *pdev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_BCM_KONA_WDT_DEBUG */

अटल पूर्णांक bcm_kona_wdt_ctrl_reg_modअगरy(काष्ठा bcm_kona_wdt *wdt,
					अचिन्हित mask, अचिन्हित newval)
अणु
	पूर्णांक val;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&wdt->lock, flags);

	val = secure_रेजिस्टर_पढ़ो(wdt, SECWDOG_CTRL_REG);
	अगर (val < 0) अणु
		ret = val;
	पूर्ण अन्यथा अणु
		val &= ~mask;
		val |= newval;
		ग_लिखोl_relaxed(val, wdt->base + SECWDOG_CTRL_REG);
	पूर्ण

	spin_unlock_irqrestore(&wdt->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_kona_wdt_set_resolution_reg(काष्ठा bcm_kona_wdt *wdt)
अणु
	अगर (wdt->resolution > SECWDOG_MAX_RES)
		वापस -EINVAL;

	वापस bcm_kona_wdt_ctrl_reg_modअगरy(wdt, SECWDOG_RES_MASK,
					wdt->resolution << SECWDOG_CLKS_SHIFT);
पूर्ण

अटल पूर्णांक bcm_kona_wdt_set_समयout_reg(काष्ठा watchकरोg_device *wकरोg,
					अचिन्हित watchकरोg_flags)
अणु
	काष्ठा bcm_kona_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	वापस bcm_kona_wdt_ctrl_reg_modअगरy(wdt, SECWDOG_COUNT_MASK,
					SECS_TO_TICKS(wकरोg->समयout, wdt) |
					watchकरोg_flags);
पूर्ण

अटल पूर्णांक bcm_kona_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
	अचिन्हित पूर्णांक t)
अणु
	wकरोg->समयout = t;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक bcm_kona_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm_kona_wdt *wdt = watchकरोg_get_drvdata(wकरोg);
	पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt->lock, flags);
	val = secure_रेजिस्टर_पढ़ो(wdt, SECWDOG_COUNT_REG);
	spin_unlock_irqrestore(&wdt->lock, flags);

	अगर (val < 0)
		वापस val;

	वापस TICKS_TO_SECS(val & SECWDOG_COUNT_MASK, wdt);
पूर्ण

अटल पूर्णांक bcm_kona_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस bcm_kona_wdt_set_समयout_reg(wकरोg,
					SECWDOG_EN_MASK | SECWDOG_SRSTEN_MASK);
पूर्ण

अटल पूर्णांक bcm_kona_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm_kona_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	वापस bcm_kona_wdt_ctrl_reg_modअगरy(wdt, SECWDOG_EN_MASK |
					    SECWDOG_SRSTEN_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops bcm_kona_wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	bcm_kona_wdt_start,
	.stop =		bcm_kona_wdt_stop,
	.set_समयout =	bcm_kona_wdt_set_समयout,
	.get_समयleft =	bcm_kona_wdt_get_समयleft,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info bcm_kona_wdt_info = अणु
	.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE |
			WDIOF_KEEPALIVEPING,
	.identity =	"Broadcom Kona Watchdog Timer",
पूर्ण;

अटल काष्ठा watchकरोg_device bcm_kona_wdt_wdd = अणु
	.info =		&bcm_kona_wdt_info,
	.ops =		&bcm_kona_wdt_ops,
	.min_समयout =	1,
	.max_समयout =	SECWDOG_MAX_COUNT >> SECWDOG_DEFAULT_RESOLUTION,
	.समयout =	SECWDOG_MAX_COUNT >> SECWDOG_DEFAULT_RESOLUTION,
पूर्ण;

अटल पूर्णांक bcm_kona_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm_kona_wdt *wdt;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	spin_lock_init(&wdt->lock);

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->resolution = SECWDOG_DEFAULT_RESOLUTION;
	ret = bcm_kona_wdt_set_resolution_reg(wdt);
	अगर (ret) अणु
		dev_err(dev, "Failed to set resolution (error: %d)", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wdt);
	watchकरोg_set_drvdata(&bcm_kona_wdt_wdd, wdt);
	bcm_kona_wdt_wdd.parent = dev;

	ret = bcm_kona_wdt_set_समयout_reg(&bcm_kona_wdt_wdd, 0);
	अगर (ret) अणु
		dev_err(dev, "Failed set watchdog timeout");
		वापस ret;
	पूर्ण

	watchकरोg_stop_on_reboot(&bcm_kona_wdt_wdd);
	watchकरोg_stop_on_unरेजिस्टर(&bcm_kona_wdt_wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, &bcm_kona_wdt_wdd);
	अगर (ret)
		वापस ret;

	bcm_kona_wdt_debug_init(pdev);
	dev_dbg(dev, "Broadcom Kona Watchdog Timer");

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	bcm_kona_wdt_debug_निकास(pdev);
	dev_dbg(&pdev->dev, "Watchdog driver disabled");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_kona_wdt_of_match[] = अणु
	अणु .compatible = "brcm,kona-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_kona_wdt_of_match);

अटल काष्ठा platक्रमm_driver bcm_kona_wdt_driver = अणु
	.driver = अणु
			.name = BCM_KONA_WDT_NAME,
			.of_match_table = bcm_kona_wdt_of_match,
		  पूर्ण,
	.probe = bcm_kona_wdt_probe,
	.हटाओ = bcm_kona_wdt_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm_kona_wdt_driver);

MODULE_ALIAS("platform:" BCM_KONA_WDT_NAME);
MODULE_AUTHOR("Markus Mayer <mmayer@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Kona Watchdog Driver");
MODULE_LICENSE("GPL v2");
