<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *      Driver क्रम the MTX-1 Watchकरोg.
 *
 *      (C) Copyright 2005 4G Systems <info@4g-प्रणालीs.biz>,
 *							All Rights Reserved.
 *                              http://www.4g-प्रणालीs.biz
 *
 *	(C) Copyright 2007 OpenWrt.org, Florian Fainelli <florian@खोलोwrt.org>
 *      (c) Copyright 2005    4G Systems <info@4g-प्रणालीs.biz>
 *
 *      Release 0.01.
 *      Author: Michael Stickel  michael.stickel@4g-प्रणालीs.biz
 *
 *      Release 0.02.
 *	Author: Florian Fainelli florian@खोलोwrt.org
 *		use the Linux watchकरोg/समयr APIs
 *
 *      The Watchकरोg is configured to reset the MTX-1
 *      अगर it is not triggered क्रम 100 seconds.
 *      It should not be triggered more often than 1.6 seconds.
 *
 *      A समयr triggers the watchकरोg every 5 seconds, until
 *      it is खोलोed क्रम the first समय. After the first खोलो
 *      it MUST be triggered every 2..95 seconds.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>

#घोषणा MTX1_WDT_INTERVAL	(5 * HZ)

अटल पूर्णांक ticks = 100 * HZ;

अटल काष्ठा अणु
	काष्ठा completion stop;
	spinlock_t lock;
	पूर्णांक running;
	काष्ठा समयr_list समयr;
	पूर्णांक queue;
	पूर्णांक शेष_ticks;
	अचिन्हित दीर्घ inuse;
	काष्ठा gpio_desc *gpiod;
	अचिन्हित पूर्णांक gstate;
पूर्ण mtx1_wdt_device;

अटल व्योम mtx1_wdt_trigger(काष्ठा समयr_list *unused)
अणु
	spin_lock(&mtx1_wdt_device.lock);
	अगर (mtx1_wdt_device.running)
		ticks--;

	/* toggle wdt gpio */
	mtx1_wdt_device.gstate = !mtx1_wdt_device.gstate;
	gpiod_set_value(mtx1_wdt_device.gpiod, mtx1_wdt_device.gstate);

	अगर (mtx1_wdt_device.queue && ticks)
		mod_समयr(&mtx1_wdt_device.समयr, jअगरfies + MTX1_WDT_INTERVAL);
	अन्यथा
		complete(&mtx1_wdt_device.stop);
	spin_unlock(&mtx1_wdt_device.lock);
पूर्ण

अटल व्योम mtx1_wdt_reset(व्योम)
अणु
	ticks = mtx1_wdt_device.शेष_ticks;
पूर्ण


अटल व्योम mtx1_wdt_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtx1_wdt_device.lock, flags);
	अगर (!mtx1_wdt_device.queue) अणु
		mtx1_wdt_device.queue = 1;
		mtx1_wdt_device.gstate = 1;
		gpiod_set_value(mtx1_wdt_device.gpiod, 1);
		mod_समयr(&mtx1_wdt_device.समयr, jअगरfies + MTX1_WDT_INTERVAL);
	पूर्ण
	mtx1_wdt_device.running++;
	spin_unlock_irqrestore(&mtx1_wdt_device.lock, flags);
पूर्ण

अटल पूर्णांक mtx1_wdt_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtx1_wdt_device.lock, flags);
	अगर (mtx1_wdt_device.queue) अणु
		mtx1_wdt_device.queue = 0;
		mtx1_wdt_device.gstate = 0;
		gpiod_set_value(mtx1_wdt_device.gpiod, 0);
	पूर्ण
	ticks = mtx1_wdt_device.शेष_ticks;
	spin_unlock_irqrestore(&mtx1_wdt_device.lock, flags);
	वापस 0;
पूर्ण

/* Fileप्रणाली functions */

अटल पूर्णांक mtx1_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &mtx1_wdt_device.inuse))
		वापस -EBUSY;
	वापस stream_खोलो(inode, file);
पूर्ण


अटल पूर्णांक mtx1_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	clear_bit(0, &mtx1_wdt_device.inuse);
	वापस 0;
पूर्ण

अटल दीर्घ mtx1_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = (पूर्णांक __user *)argp;
	अचिन्हित पूर्णांक value;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_CARDRESET,
		.identity = "MTX-1 WDT",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		put_user(0, p);
		अवरोध;
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(value, p))
			वापस -EFAULT;
		अगर (value & WDIOS_ENABLECARD)
			mtx1_wdt_start();
		अन्यथा अगर (value & WDIOS_DISABLECARD)
			mtx1_wdt_stop();
		अन्यथा
			वापस -EINVAL;
		वापस 0;
	हाल WDIOC_KEEPALIVE:
		mtx1_wdt_reset();
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण


अटल sमाप_प्रकार mtx1_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!count)
		वापस -EIO;
	mtx1_wdt_reset();
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mtx1_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= mtx1_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= mtx1_wdt_खोलो,
	.ग_लिखो		= mtx1_wdt_ग_लिखो,
	.release	= mtx1_wdt_release,
पूर्ण;


अटल काष्ठा miscdevice mtx1_wdt_misc = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &mtx1_wdt_fops,
पूर्ण;


अटल पूर्णांक mtx1_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	mtx1_wdt_device.gpiod = devm_gpiod_get(&pdev->dev,
					       शून्य, GPIOD_OUT_HIGH);
	अगर (IS_ERR(mtx1_wdt_device.gpiod)) अणु
		dev_err(&pdev->dev, "failed to request gpio");
		वापस PTR_ERR(mtx1_wdt_device.gpiod);
	पूर्ण

	spin_lock_init(&mtx1_wdt_device.lock);
	init_completion(&mtx1_wdt_device.stop);
	mtx1_wdt_device.queue = 0;
	clear_bit(0, &mtx1_wdt_device.inuse);
	समयr_setup(&mtx1_wdt_device.समयr, mtx1_wdt_trigger, 0);
	mtx1_wdt_device.शेष_ticks = ticks;

	ret = misc_रेजिस्टर(&mtx1_wdt_misc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register\n");
		वापस ret;
	पूर्ण
	mtx1_wdt_start();
	dev_info(&pdev->dev, "MTX-1 Watchdog driver\n");
	वापस 0;
पूर्ण

अटल पूर्णांक mtx1_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* FIXME: करो we need to lock this test ? */
	अगर (mtx1_wdt_device.queue) अणु
		mtx1_wdt_device.queue = 0;
		रुको_क्रम_completion(&mtx1_wdt_device.stop);
	पूर्ण

	misc_deरेजिस्टर(&mtx1_wdt_misc);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtx1_wdt_driver = अणु
	.probe = mtx1_wdt_probe,
	.हटाओ = mtx1_wdt_हटाओ,
	.driver.name = "mtx1-wdt",
	.driver.owner = THIS_MODULE,
पूर्ण;

module_platक्रमm_driver(mtx1_wdt_driver);

MODULE_AUTHOR("Michael Stickel, Florian Fainelli");
MODULE_DESCRIPTION("Driver for the MTX-1 watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mtx1-wdt");
