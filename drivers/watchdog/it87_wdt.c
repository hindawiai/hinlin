<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Watchकरोg Timer Driver
 *	   क्रम ITE IT87xx Environment Control - Low Pin Count Input / Output
 *
 *	(c) Copyright 2007  Oliver Schuster <olivers137@aol.com>
 *
 *	Based on softकरोg.c	by Alan Cox,
 *		 83977f_wdt.c	by Jose Goncalves,
 *		 it87.c		by Chris Gauthron, Jean Delvare
 *
 *	Data-sheets: Publicly available at the ITE website
 *		    http://www.ite.com.tw/
 *
 *	Support of the watchकरोg समयrs, which are available on
 *	IT8607, IT8620, IT8622, IT8625, IT8628, IT8655, IT8665, IT8686,
 *	IT8702, IT8712, IT8716, IT8718, IT8720, IT8721, IT8726, IT8728,
 *	IT8772, IT8783 and IT8784.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा WATCHDOG_NAME		"IT87 WDT"

/* Defaults क्रम Module Parameter */
#घोषणा DEFAULT_TIMEOUT		60
#घोषणा DEFAULT_TESTMODE	0
#घोषणा DEFAULT_NOWAYOUT	WATCHDOG_NOWAYOUT

/* IO Ports */
#घोषणा REG		0x2e
#घोषणा VAL		0x2f

/* Logical device Numbers LDN */
#घोषणा GPIO		0x07

/* Configuration Registers and Functions */
#घोषणा LDNREG		0x07
#घोषणा CHIPID		0x20
#घोषणा CHIPREV		0x22

/* Chip Id numbers */
#घोषणा NO_DEV_ID	0xffff
#घोषणा IT8607_ID	0x8607
#घोषणा IT8620_ID	0x8620
#घोषणा IT8622_ID	0x8622
#घोषणा IT8625_ID	0x8625
#घोषणा IT8628_ID	0x8628
#घोषणा IT8655_ID	0x8655
#घोषणा IT8665_ID	0x8665
#घोषणा IT8686_ID	0x8686
#घोषणा IT8702_ID	0x8702
#घोषणा IT8705_ID	0x8705
#घोषणा IT8712_ID	0x8712
#घोषणा IT8716_ID	0x8716
#घोषणा IT8718_ID	0x8718
#घोषणा IT8720_ID	0x8720
#घोषणा IT8721_ID	0x8721
#घोषणा IT8726_ID	0x8726	/* the data sheet suggest wrongly 0x8716 */
#घोषणा IT8728_ID	0x8728
#घोषणा IT8772_ID	0x8772
#घोषणा IT8783_ID	0x8783
#घोषणा IT8784_ID	0x8784
#घोषणा IT8786_ID	0x8786

/* GPIO Configuration Registers LDN=0x07 */
#घोषणा WDTCTRL		0x71
#घोषणा WDTCFG		0x72
#घोषणा WDTVALLSB	0x73
#घोषणा WDTVALMSB	0x74

/* GPIO Bits WDTCFG */
#घोषणा WDT_TOV1	0x80
#घोषणा WDT_KRST	0x40
#घोषणा WDT_TOVE	0x20
#घोषणा WDT_PWROK	0x10 /* not in it8721 */
#घोषणा WDT_INT_MASK	0x0f

अटल अचिन्हित पूर्णांक max_units, chip_type;

अटल अचिन्हित पूर्णांक समयout = DEFAULT_TIMEOUT;
अटल पूर्णांक tesपंचांगode = DEFAULT_TESTMODE;
अटल bool nowayout = DEFAULT_NOWAYOUT;

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds, default="
		__MODULE_STRING(DEFAULT_TIMEOUT));
module_param(tesपंचांगode, पूर्णांक, 0);
MODULE_PARM_DESC(tesपंचांगode, "Watchdog test mode (1 = no reboot), default="
		__MODULE_STRING(DEFAULT_TESTMODE));
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started, default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT));

/* Superio Chip */

अटल अंतरभूत पूर्णांक superio_enter(व्योम)
अणु
	/*
	 * Try to reserve REG and REG + 1 क्रम exclusive access.
	 */
	अगर (!request_muxed_region(REG, 2, WATCHDOG_NAME))
		वापस -EBUSY;

	outb(0x87, REG);
	outb(0x01, REG);
	outb(0x55, REG);
	outb(0x55, REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(व्योम)
अणु
	outb(0x02, REG);
	outb(0x02, VAL);
	release_region(REG, 2);
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक ldn)
अणु
	outb(LDNREG, REG);
	outb(ldn, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक reg)
अणु
	outb(reg, REG);
	वापस inb(VAL);
पूर्ण

अटल अंतरभूत व्योम superio_outb(पूर्णांक val, पूर्णांक reg)
अणु
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inw(पूर्णांक reg)
अणु
	पूर्णांक val;
	outb(reg++, REG);
	val = inb(VAL) << 8;
	outb(reg, REG);
	val |= inb(VAL);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_outw(पूर्णांक val, पूर्णांक reg)
अणु
	outb(reg++, REG);
	outb(val >> 8, VAL);
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

/* Internal function, should be called after superio_select(GPIO) */
अटल व्योम _wdt_update_समयout(अचिन्हित पूर्णांक t)
अणु
	अचिन्हित अक्षर cfg = WDT_KRST;

	अगर (tesपंचांगode)
		cfg = 0;

	अगर (t <= max_units)
		cfg |= WDT_TOV1;
	अन्यथा
		t /= 60;

	अगर (chip_type != IT8721_ID)
		cfg |= WDT_PWROK;

	superio_outb(cfg, WDTCFG);
	superio_outb(t, WDTVALLSB);
	अगर (max_units > 255)
		superio_outb(t >> 8, WDTVALMSB);
पूर्ण

अटल पूर्णांक wdt_update_समयout(अचिन्हित पूर्णांक t)
अणु
	पूर्णांक ret;

	ret = superio_enter();
	अगर (ret)
		वापस ret;

	superio_select(GPIO);
	_wdt_update_समयout(t);
	superio_निकास();

	वापस 0;
पूर्ण

अटल पूर्णांक wdt_round_समय(पूर्णांक t)
अणु
	t += 59;
	t -= t % 60;
	वापस t;
पूर्ण

/* watchकरोg समयr handling */

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdt_update_समयout(wdd->समयout);
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdt_update_समयout(0);
पूर्ण

/**
 *	wdt_set_समयout - set a new समयout value with watchकरोg ioctl
 *	@t: समयout value in seconds
 *
 *	The hardware device has a 8 or 16 bit watchकरोg समयr (depends on
 *	chip version) that can be configured to count seconds or minutes.
 *
 *	Used within WDIOC_SETTIMEOUT watchकरोg device ioctl.
 */

अटल पूर्णांक wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक t)
अणु
	पूर्णांक ret = 0;

	अगर (t > max_units)
		t = wdt_round_समय(t);

	wdd->समयout = t;

	अगर (watchकरोg_hw_running(wdd))
		ret = wdt_update_समयout(t);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.firmware_version = 1,
	.identity = WATCHDOG_NAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdt_start,
	.stop = wdt_stop,
	.set_समयout = wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device wdt_dev = अणु
	.info = &ident,
	.ops = &wdt_ops,
	.min_समयout = 1,
पूर्ण;

अटल पूर्णांक __init it87_wdt_init(व्योम)
अणु
	u8  chip_rev;
	पूर्णांक rc;

	rc = superio_enter();
	अगर (rc)
		वापस rc;

	chip_type = superio_inw(CHIPID);
	chip_rev  = superio_inb(CHIPREV) & 0x0f;
	superio_निकास();

	चयन (chip_type) अणु
	हाल IT8702_ID:
		max_units = 255;
		अवरोध;
	हाल IT8712_ID:
		max_units = (chip_rev < 8) ? 255 : 65535;
		अवरोध;
	हाल IT8716_ID:
	हाल IT8726_ID:
		max_units = 65535;
		अवरोध;
	हाल IT8607_ID:
	हाल IT8620_ID:
	हाल IT8622_ID:
	हाल IT8625_ID:
	हाल IT8628_ID:
	हाल IT8655_ID:
	हाल IT8665_ID:
	हाल IT8686_ID:
	हाल IT8718_ID:
	हाल IT8720_ID:
	हाल IT8721_ID:
	हाल IT8728_ID:
	हाल IT8772_ID:
	हाल IT8783_ID:
	हाल IT8784_ID:
	हाल IT8786_ID:
		max_units = 65535;
		अवरोध;
	हाल IT8705_ID:
		pr_err("Unsupported Chip found, Chip %04x Revision %02x\n",
		       chip_type, chip_rev);
		वापस -ENODEV;
	हाल NO_DEV_ID:
		pr_err("no device\n");
		वापस -ENODEV;
	शेष:
		pr_err("Unknown Chip found, Chip %04x Revision %04x\n",
		       chip_type, chip_rev);
		वापस -ENODEV;
	पूर्ण

	rc = superio_enter();
	अगर (rc)
		वापस rc;

	superio_select(GPIO);
	superio_outb(WDT_TOV1, WDTCFG);
	superio_outb(0x00, WDTCTRL);
	superio_निकास();

	अगर (समयout < 1 || समयout > max_units * 60) अणु
		समयout = DEFAULT_TIMEOUT;
		pr_warn("Timeout value out of range, use default %d sec\n",
			DEFAULT_TIMEOUT);
	पूर्ण

	अगर (समयout > max_units)
		समयout = wdt_round_समय(समयout);

	wdt_dev.समयout = समयout;
	wdt_dev.max_समयout = max_units * 60;

	watchकरोg_stop_on_reboot(&wdt_dev);
	rc = watchकरोg_रेजिस्टर_device(&wdt_dev);
	अगर (rc) अणु
		pr_err("Cannot register watchdog device (err=%d)\n", rc);
		वापस rc;
	पूर्ण

	pr_info("Chip IT%04x revision %d initialized. timeout=%d sec (nowayout=%d testmode=%d)\n",
		chip_type, chip_rev, समयout, nowayout, tesपंचांगode);

	वापस 0;
पूर्ण

अटल व्योम __निकास it87_wdt_निकास(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&wdt_dev);
पूर्ण

module_init(it87_wdt_init);
module_निकास(it87_wdt_निकास);

MODULE_AUTHOR("Oliver Schuster");
MODULE_DESCRIPTION("Hardware Watchdog Device Driver for IT87xx EC-LPC I/O");
MODULE_LICENSE("GPL");
