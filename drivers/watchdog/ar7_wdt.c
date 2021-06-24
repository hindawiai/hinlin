<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/watchकरोg/ar7_wdt.c
 *
 * Copyright (C) 2007 Nicolas Thill <nico@खोलोwrt.org>
 * Copyright (c) 2005 Enrik Berkhan <Enrik.Berkhan@akk.org>
 *
 * Some code taken from:
 * National Semiconductor SCx200 Watchकरोg support
 * Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/mach-ar7/ar7.h>

#घोषणा LONGNAME "TI AR7 Watchdog Timer"

MODULE_AUTHOR("Nicolas Thill <nico@openwrt.org>");
MODULE_DESCRIPTION(LONGNAME);
MODULE_LICENSE("GPL");

अटल पूर्णांक margin = 60;
module_param(margin, पूर्णांक, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Disable watchdog shutdown on close");

#घोषणा READ_REG(x) पढ़ोl((व्योम __iomem *)&(x))
#घोषणा WRITE_REG(x, v) ग_लिखोl((v), (व्योम __iomem *)&(x))

काष्ठा ar7_wdt अणु
	u32 kick_lock;
	u32 kick;
	u32 change_lock;
	u32 change;
	u32 disable_lock;
	u32 disable;
	u32 prescale_lock;
	u32 prescale;
पूर्ण;

अटल अचिन्हित दीर्घ wdt_is_खोलो;
अटल अचिन्हित expect_बंद;
अटल DEFINE_SPINLOCK(wdt_lock);

/* XXX currently fixed, allows max margin ~68.72 secs */
#घोषणा prescale_value 0xffff

/* Resource of the WDT रेजिस्टरs */
अटल काष्ठा resource *ar7_regs_wdt;
/* Poपूर्णांकer to the remapped WDT IO space */
अटल काष्ठा ar7_wdt *ar7_wdt;

अटल काष्ठा clk *vbus_clk;

अटल व्योम ar7_wdt_kick(u32 value)
अणु
	WRITE_REG(ar7_wdt->kick_lock, 0x5555);
	अगर ((READ_REG(ar7_wdt->kick_lock) & 3) == 1) अणु
		WRITE_REG(ar7_wdt->kick_lock, 0xaaaa);
		अगर ((READ_REG(ar7_wdt->kick_lock) & 3) == 3) अणु
			WRITE_REG(ar7_wdt->kick, value);
			वापस;
		पूर्ण
	पूर्ण
	pr_err("failed to unlock WDT kick reg\n");
पूर्ण

अटल व्योम ar7_wdt_prescale(u32 value)
अणु
	WRITE_REG(ar7_wdt->prescale_lock, 0x5a5a);
	अगर ((READ_REG(ar7_wdt->prescale_lock) & 3) == 1) अणु
		WRITE_REG(ar7_wdt->prescale_lock, 0xa5a5);
		अगर ((READ_REG(ar7_wdt->prescale_lock) & 3) == 3) अणु
			WRITE_REG(ar7_wdt->prescale, value);
			वापस;
		पूर्ण
	पूर्ण
	pr_err("failed to unlock WDT prescale reg\n");
पूर्ण

अटल व्योम ar7_wdt_change(u32 value)
अणु
	WRITE_REG(ar7_wdt->change_lock, 0x6666);
	अगर ((READ_REG(ar7_wdt->change_lock) & 3) == 1) अणु
		WRITE_REG(ar7_wdt->change_lock, 0xbbbb);
		अगर ((READ_REG(ar7_wdt->change_lock) & 3) == 3) अणु
			WRITE_REG(ar7_wdt->change, value);
			वापस;
		पूर्ण
	पूर्ण
	pr_err("failed to unlock WDT change reg\n");
पूर्ण

अटल व्योम ar7_wdt_disable(u32 value)
अणु
	WRITE_REG(ar7_wdt->disable_lock, 0x7777);
	अगर ((READ_REG(ar7_wdt->disable_lock) & 3) == 1) अणु
		WRITE_REG(ar7_wdt->disable_lock, 0xcccc);
		अगर ((READ_REG(ar7_wdt->disable_lock) & 3) == 2) अणु
			WRITE_REG(ar7_wdt->disable_lock, 0xdddd);
			अगर ((READ_REG(ar7_wdt->disable_lock) & 3) == 3) अणु
				WRITE_REG(ar7_wdt->disable, value);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	pr_err("failed to unlock WDT disable reg\n");
पूर्ण

अटल व्योम ar7_wdt_update_margin(पूर्णांक new_margin)
अणु
	u32 change;
	u32 vbus_rate;

	vbus_rate = clk_get_rate(vbus_clk);
	change = new_margin * (vbus_rate / prescale_value);
	अगर (change < 1)
		change = 1;
	अगर (change > 0xffff)
		change = 0xffff;
	ar7_wdt_change(change);
	margin = change * prescale_value / vbus_rate;
	pr_info("timer margin %d seconds (prescale %d, change %d, freq %d)\n",
		margin, prescale_value, change, vbus_rate);
पूर्ण

अटल व्योम ar7_wdt_enable_wdt(व्योम)
अणु
	pr_debug("enabling watchdog timer\n");
	ar7_wdt_disable(1);
	ar7_wdt_kick(1);
पूर्ण

अटल व्योम ar7_wdt_disable_wdt(व्योम)
अणु
	pr_debug("disabling watchdog timer\n");
	ar7_wdt_disable(0);
पूर्ण

अटल पूर्णांक ar7_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* only allow one at a समय */
	अगर (test_and_set_bit(0, &wdt_is_खोलो))
		वापस -EBUSY;
	ar7_wdt_enable_wdt();
	expect_बंद = 0;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक ar7_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!expect_बंद)
		pr_warn("watchdog device closed unexpectedly, will not disable the watchdog timer\n");
	अन्यथा अगर (!nowayout)
		ar7_wdt_disable_wdt();
	clear_bit(0, &wdt_is_खोलो);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ar7_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
			     माप_प्रकार len, loff_t *ppos)
अणु
	/* check क्रम a magic बंद अक्षरacter */
	अगर (len) अणु
		माप_प्रकार i;

		spin_lock(&wdt_lock);
		ar7_wdt_kick(1);
		spin_unlock(&wdt_lock);

		expect_बंद = 0;
		क्रम (i = 0; i < len; ++i) अणु
			अक्षर c;
			अगर (get_user(c, data + i))
				वापस -EFAULT;
			अगर (c == 'V')
				expect_बंद = 1;
		पूर्ण

	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ ar7_wdt_ioctl(काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.identity = LONGNAME,
		.firmware_version = 1,
		.options = (WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
						WDIOF_MAGICCLOSE),
	पूर्ण;
	पूर्णांक new_margin;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user((काष्ठा watchकरोg_info *)arg, &ident,
				माप(ident)))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		अगर (put_user(0, (पूर्णांक *)arg))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_KEEPALIVE:
		ar7_wdt_kick(1);
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_margin, (पूर्णांक *)arg))
			वापस -EFAULT;
		अगर (new_margin < 1)
			वापस -EINVAL;

		spin_lock(&wdt_lock);
		ar7_wdt_update_margin(new_margin);
		ar7_wdt_kick(1);
		spin_unlock(&wdt_lock);
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		अगर (put_user(margin, (पूर्णांक *)arg))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations ar7_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= ar7_wdt_ग_लिखो,
	.unlocked_ioctl	= ar7_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= ar7_wdt_खोलो,
	.release	= ar7_wdt_release,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice ar7_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &ar7_wdt_fops,
पूर्ण;

अटल पूर्णांक ar7_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;

	ar7_regs_wdt =
		platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	ar7_wdt = devm_ioremap_resource(&pdev->dev, ar7_regs_wdt);
	अगर (IS_ERR(ar7_wdt))
		वापस PTR_ERR(ar7_wdt);

	vbus_clk = clk_get(शून्य, "vbus");
	अगर (IS_ERR(vbus_clk)) अणु
		pr_err("could not get vbus clock\n");
		वापस PTR_ERR(vbus_clk);
	पूर्ण

	ar7_wdt_disable_wdt();
	ar7_wdt_prescale(prescale_value);
	ar7_wdt_update_margin(margin);

	rc = misc_रेजिस्टर(&ar7_wdt_miscdev);
	अगर (rc) अणु
		pr_err("unable to register misc device\n");
		जाओ out;
	पूर्ण
	वापस 0;

out:
	clk_put(vbus_clk);
	vbus_clk = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक ar7_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&ar7_wdt_miscdev);
	clk_put(vbus_clk);
	vbus_clk = शून्य;
	वापस 0;
पूर्ण

अटल व्योम ar7_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!nowayout)
		ar7_wdt_disable_wdt();
पूर्ण

अटल काष्ठा platक्रमm_driver ar7_wdt_driver = अणु
	.probe = ar7_wdt_probe,
	.हटाओ = ar7_wdt_हटाओ,
	.shutकरोwn = ar7_wdt_shutकरोwn,
	.driver = अणु
		.name = "ar7_wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ar7_wdt_driver);
