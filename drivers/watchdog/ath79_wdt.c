<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Atheros AR71XX/AR724X/AR913X built-in hardware watchकरोg समयr.
 *
 * Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 * This driver was based on: drivers/watchकरोg/ixp4xx_wdt.c
 *	Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *	Copyright 2004 (c) MontaVista, Software, Inc.
 *
 * which again was based on sa1100 driver,
 *	Copyright (C) 2000 Oleg Drokin <green@crimea.edu>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/uaccess.h>

#घोषणा DRIVER_NAME	"ath79-wdt"

#घोषणा WDT_TIMEOUT	15	/* seconds */

#घोषणा WDOG_REG_CTRL		0x00
#घोषणा WDOG_REG_TIMER		0x04

#घोषणा WDOG_CTRL_LAST_RESET	BIT(31)
#घोषणा WDOG_CTRL_ACTION_MASK	3
#घोषणा WDOG_CTRL_ACTION_NONE	0	/* no action */
#घोषणा WDOG_CTRL_ACTION_GPI	1	/* general purpose पूर्णांकerrupt */
#घोषणा WDOG_CTRL_ACTION_NMI	2	/* NMI */
#घोषणा WDOG_CTRL_ACTION_FCR	3	/* full chip reset */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
			   "(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक समयout = WDT_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds "
			  "(default=" __MODULE_STRING(WDT_TIMEOUT) "s)");

अटल अचिन्हित दीर्घ wdt_flags;

#घोषणा WDT_FLAGS_BUSY		0
#घोषणा WDT_FLAGS_EXPECT_CLOSE	1

अटल काष्ठा clk *wdt_clk;
अटल अचिन्हित दीर्घ wdt_freq;
अटल पूर्णांक boot_status;
अटल पूर्णांक max_समयout;
अटल व्योम __iomem *wdt_base;

अटल अंतरभूत व्योम ath79_wdt_wr(अचिन्हित reg, u32 val)
अणु
	ioग_लिखो32(val, wdt_base + reg);
पूर्ण

अटल अंतरभूत u32 ath79_wdt_rr(अचिन्हित reg)
अणु
	वापस ioपढ़ो32(wdt_base + reg);
पूर्ण

अटल अंतरभूत व्योम ath79_wdt_keepalive(व्योम)
अणु
	ath79_wdt_wr(WDOG_REG_TIMER, wdt_freq * समयout);
	/* flush ग_लिखो */
	ath79_wdt_rr(WDOG_REG_TIMER);
पूर्ण

अटल अंतरभूत व्योम ath79_wdt_enable(व्योम)
अणु
	ath79_wdt_keepalive();

	/*
	 * Updating the TIMER रेजिस्टर requires a few microseconds
	 * on the AR934x SoCs at least. Use a small delay to ensure
	 * that the TIMER रेजिस्टर is updated within the hardware
	 * beक्रमe enabling the watchकरोg.
	 */
	udelay(2);

	ath79_wdt_wr(WDOG_REG_CTRL, WDOG_CTRL_ACTION_FCR);
	/* flush ग_लिखो */
	ath79_wdt_rr(WDOG_REG_CTRL);
पूर्ण

अटल अंतरभूत व्योम ath79_wdt_disable(व्योम)
अणु
	ath79_wdt_wr(WDOG_REG_CTRL, WDOG_CTRL_ACTION_NONE);
	/* flush ग_लिखो */
	ath79_wdt_rr(WDOG_REG_CTRL);
पूर्ण

अटल पूर्णांक ath79_wdt_set_समयout(पूर्णांक val)
अणु
	अगर (val < 1 || val > max_समयout)
		वापस -EINVAL;

	समयout = val;
	ath79_wdt_keepalive();

	वापस 0;
पूर्ण

अटल पूर्णांक ath79_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_FLAGS_BUSY, &wdt_flags))
		वापस -EBUSY;

	clear_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags);
	ath79_wdt_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक ath79_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags))
		ath79_wdt_disable();
	अन्यथा अणु
		pr_crit("device closed unexpectedly, watchdog timer will not stop!\n");
		ath79_wdt_keepalive();
	पूर्ण

	clear_bit(WDT_FLAGS_BUSY, &wdt_flags);
	clear_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath79_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			clear_bit(WDT_FLAGS_EXPECT_CLOSE, &wdt_flags);

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, data + i))
					वापस -EFAULT;

				अगर (c == 'V')
					set_bit(WDT_FLAGS_EXPECT_CLOSE,
						&wdt_flags);
			पूर्ण
		पूर्ण

		ath79_wdt_keepalive();
	पूर्ण

	वापस len;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ath79_wdt_info = अणु
	.options		= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
				  WDIOF_MAGICCLOSE | WDIOF_CARDRESET,
	.firmware_version	= 0,
	.identity		= "ATH79 watchdog",
पूर्ण;

अटल दीर्घ ath79_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक err;
	पूर्णांक t;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		err = copy_to_user(argp, &ath79_wdt_info,
				   माप(ath79_wdt_info)) ? -EFAULT : 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		err = put_user(0, p);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		err = put_user(boot_status, p);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		ath79_wdt_keepalive();
		err = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		err = get_user(t, p);
		अगर (err)
			अवरोध;

		err = ath79_wdt_set_समयout(t);
		अगर (err)
			अवरोध;
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		err = put_user(समयout, p);
		अवरोध;

	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations ath79_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= ath79_wdt_ग_लिखो,
	.unlocked_ioctl	= ath79_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= ath79_wdt_खोलो,
	.release	= ath79_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice ath79_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &ath79_wdt_fops,
पूर्ण;

अटल पूर्णांक ath79_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 ctrl;
	पूर्णांक err;

	अगर (wdt_base)
		वापस -EBUSY;

	wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt_base))
		वापस PTR_ERR(wdt_base);

	wdt_clk = devm_clk_get(&pdev->dev, "wdt");
	अगर (IS_ERR(wdt_clk))
		वापस PTR_ERR(wdt_clk);

	err = clk_prepare_enable(wdt_clk);
	अगर (err)
		वापस err;

	wdt_freq = clk_get_rate(wdt_clk);
	अगर (!wdt_freq) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	max_समयout = (0xfffffffful / wdt_freq);
	अगर (समयout < 1 || समयout > max_समयout) अणु
		समयout = max_समयout;
		dev_info(&pdev->dev,
			"timeout value must be 0 < timeout < %d, using %d\n",
			max_समयout, समयout);
	पूर्ण

	ctrl = ath79_wdt_rr(WDOG_REG_CTRL);
	boot_status = (ctrl & WDOG_CTRL_LAST_RESET) ? WDIOF_CARDRESET : 0;

	err = misc_रेजिस्टर(&ath79_wdt_miscdev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"unable to register misc device, err=%d\n", err);
		जाओ err_clk_disable;
	पूर्ण

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(wdt_clk);
	वापस err;
पूर्ण

अटल पूर्णांक ath79_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&ath79_wdt_miscdev);
	clk_disable_unprepare(wdt_clk);
	वापस 0;
पूर्ण

अटल व्योम ath79_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	ath79_wdt_disable();
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ath79_wdt_match[] = अणु
	अणु .compatible = "qca,ar7130-wdt" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ath79_wdt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ath79_wdt_driver = अणु
	.probe		= ath79_wdt_probe,
	.हटाओ		= ath79_wdt_हटाओ,
	.shutकरोwn	= ath79_wdt_shutकरोwn,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(ath79_wdt_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ath79_wdt_driver);

MODULE_DESCRIPTION("Atheros AR71XX/AR724X/AR913X hardware watchdog driver");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org");
MODULE_AUTHOR("Imre Kaloz <kaloz@openwrt.org");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
