<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Watchकरोg समयr क्रम machines with the CS5535/CS5536 companion chip
 *
 * Copyright (C) 2006-2007, Advanced Micro Devices, Inc.
 * Copyright (C) 2009  Andres Salomon <dilinger@collabora.co.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/cs5535.h>

#घोषणा GEODEWDT_HZ 500
#घोषणा GEODEWDT_SCALE 6
#घोषणा GEODEWDT_MAX_SECONDS 131

#घोषणा WDT_FLAGS_OPEN 1
#घोषणा WDT_FLAGS_ORPHAN 2

#घोषणा DRV_NAME "geodewdt"
#घोषणा WATCHDOG_NAME "Geode GX/LX WDT"
#घोषणा WATCHDOG_TIMEOUT 60

अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. 1<= timeout <=131, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल काष्ठा platक्रमm_device *geodewdt_platक्रमm_device;
अटल अचिन्हित दीर्घ wdt_flags;
अटल काष्ठा cs5535_mfgpt_समयr *wdt_समयr;
अटल पूर्णांक safe_बंद;

अटल व्योम geodewdt_ping(व्योम)
अणु
	/* Stop the counter */
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP, 0);

	/* Reset the counter */
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_COUNTER, 0);

	/* Enable the counter */
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP, MFGPT_SETUP_CNTEN);
पूर्ण

अटल व्योम geodewdt_disable(व्योम)
अणु
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP, 0);
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_COUNTER, 0);
पूर्ण

अटल पूर्णांक geodewdt_set_heartbeat(पूर्णांक val)
अणु
	अगर (val < 1 || val > GEODEWDT_MAX_SECONDS)
		वापस -EINVAL;

	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP, 0);
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_CMP2, val * GEODEWDT_HZ);
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_COUNTER, 0);
	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP, MFGPT_SETUP_CNTEN);

	समयout = val;
	वापस 0;
पूर्ण

अटल पूर्णांक geodewdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_FLAGS_OPEN, &wdt_flags))
		वापस -EBUSY;

	अगर (!test_and_clear_bit(WDT_FLAGS_ORPHAN, &wdt_flags))
		__module_get(THIS_MODULE);

	geodewdt_ping();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक geodewdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (safe_बंद) अणु
		geodewdt_disable();
		module_put(THIS_MODULE);
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close - watchdog is not stopping\n");
		geodewdt_ping();

		set_bit(WDT_FLAGS_ORPHAN, &wdt_flags);
	पूर्ण

	clear_bit(WDT_FLAGS_OPEN, &wdt_flags);
	safe_बंद = 0;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार geodewdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;
			safe_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, data + i))
					वापस -EFAULT;

				अगर (c == 'V')
					safe_बंद = 1;
			पूर्ण
		पूर्ण

		geodewdt_ping();
	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ geodewdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक पूर्णांकerval;

	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING
		| WDIOF_MAGICCLOSE,
		.firmware_version =     1,
		.identity =             WATCHDOG_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident,
				    माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, ret = -EINVAL;

		अगर (get_user(options, p))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			geodewdt_disable();
			ret = 0;
		पूर्ण

		अगर (options & WDIOS_ENABLECARD) अणु
			geodewdt_ping();
			ret = 0;
		पूर्ण

		वापस ret;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		geodewdt_ping();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(पूर्णांकerval, p))
			वापस -EFAULT;

		अगर (geodewdt_set_heartbeat(पूर्णांकerval))
			वापस -EINVAL;
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations geodewdt_fops = अणु
	.owner          = THIS_MODULE,
	.llseek         = no_llseek,
	.ग_लिखो          = geodewdt_ग_लिखो,
	.unlocked_ioctl = geodewdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो           = geodewdt_खोलो,
	.release        = geodewdt_release,
पूर्ण;

अटल काष्ठा miscdevice geodewdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &geodewdt_fops,
पूर्ण;

अटल पूर्णांक __init geodewdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	wdt_समयr = cs5535_mfgpt_alloc_समयr(MFGPT_TIMER_ANY, MFGPT_DOMAIN_WORKING);
	अगर (!wdt_समयr) अणु
		pr_err("No timers were available\n");
		वापस -ENODEV;
	पूर्ण

	/* Set up the समयr */

	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_SETUP,
			  GEODEWDT_SCALE | (3 << 8));

	/* Set up comparator 2 to reset when the event fires */
	cs5535_mfgpt_toggle_event(wdt_समयr, MFGPT_CMP2, MFGPT_EVENT_RESET, 1);

	/* Set up the initial समयout */

	cs5535_mfgpt_ग_लिखो(wdt_समयr, MFGPT_REG_CMP2,
		समयout * GEODEWDT_HZ);

	ret = misc_रेजिस्टर(&geodewdt_miscdev);

	वापस ret;
पूर्ण

अटल पूर्णांक geodewdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&geodewdt_miscdev);
	वापस 0;
पूर्ण

अटल व्योम geodewdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	geodewdt_disable();
पूर्ण

अटल काष्ठा platक्रमm_driver geodewdt_driver = अणु
	.हटाओ		= geodewdt_हटाओ,
	.shutकरोwn	= geodewdt_shutकरोwn,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init geodewdt_init(व्योम)
अणु
	पूर्णांक ret;

	geodewdt_platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(DRV_NAME,
								-1, शून्य, 0);
	अगर (IS_ERR(geodewdt_platक्रमm_device))
		वापस PTR_ERR(geodewdt_platक्रमm_device);

	ret = platक्रमm_driver_probe(&geodewdt_driver, geodewdt_probe);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	platक्रमm_device_unरेजिस्टर(geodewdt_platक्रमm_device);
	वापस ret;
पूर्ण

अटल व्योम __निकास geodewdt_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(geodewdt_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&geodewdt_driver);
पूर्ण

module_init(geodewdt_init);
module_निकास(geodewdt_निकास);

MODULE_AUTHOR("Advanced Micro Devices, Inc");
MODULE_DESCRIPTION("Geode GX/LX Watchdog Driver");
MODULE_LICENSE("GPL");
