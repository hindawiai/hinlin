<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	w83627hf/thf WDT driver
 *
 *	(c) Copyright 2013 Guenter Roeck
 *		converted to watchकरोg infraकाष्ठाure
 *
 *	(c) Copyright 2007 Vlad Drukker <vlad@storewiz.com>
 *		added support क्रम W83627THF.
 *
 *	(c) Copyright 2003,2007 Pथँdraig Brady <P@draigBrady.com>
 *
 *	Based on advantechwdt.c which is based on wdt.c.
 *	Original copyright messages:
 *
 *	(c) Copyright 2000-2001 Marek Michalkiewicz <marekm@linux.org.pl>
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>

#घोषणा WATCHDOG_NAME "w83627hf/thf/hg/dhg WDT"
#घोषणा WATCHDOG_TIMEOUT 60		/* 60 sec शेष समयout */

अटल पूर्णांक wdt_io;
अटल पूर्णांक cr_wdt_समयout;	/* WDT समयout रेजिस्टर */
अटल पूर्णांक cr_wdt_control;	/* WDT control रेजिस्टर */
अटल पूर्णांक cr_wdt_csr;		/* WDT control & status रेजिस्टर */
अटल पूर्णांक wdt_cfg_enter = 0x87;/* key to unlock configuration space */
अटल पूर्णांक wdt_cfg_leave = 0xAA;/* key to lock configuration space */

क्रमागत chips अणु w83627hf, w83627s, w83697hf, w83697ug, w83637hf, w83627thf,
	     w83687thf, w83627ehf, w83627dhg, w83627uhg, w83667hg, w83627dhg_p,
	     w83667hg_b, nct6775, nct6776, nct6779, nct6791, nct6792, nct6793,
	     nct6795, nct6796, nct6102, nct6116 पूर्ण;

अटल पूर्णांक समयout;			/* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in seconds. 1 <= timeout <= 255, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक early_disable;
module_param(early_disable, पूर्णांक, 0);
MODULE_PARM_DESC(early_disable, "Disable watchdog at boot time (default=0)");

/*
 *	Kernel methods.
 */

#घोषणा WDT_EFER (wdt_io+0)   /* Extended Function Enable Registers */
#घोषणा WDT_EFIR (wdt_io+0)   /* Extended Function Index Register
							(same as EFER) */
#घोषणा WDT_EFDR (WDT_EFIR+1) /* Extended Function Data Register */

#घोषणा W83627HF_LD_WDT		0x08

#घोषणा W83627HF_ID		0x52
#घोषणा W83627S_ID		0x59
#घोषणा W83697HF_ID		0x60
#घोषणा W83697UG_ID		0x68
#घोषणा W83637HF_ID		0x70
#घोषणा W83627THF_ID		0x82
#घोषणा W83687THF_ID		0x85
#घोषणा W83627EHF_ID		0x88
#घोषणा W83627DHG_ID		0xa0
#घोषणा W83627UHG_ID		0xa2
#घोषणा W83667HG_ID		0xa5
#घोषणा W83627DHG_P_ID		0xb0
#घोषणा W83667HG_B_ID		0xb3
#घोषणा NCT6775_ID		0xb4
#घोषणा NCT6776_ID		0xc3
#घोषणा NCT6102_ID		0xc4
#घोषणा NCT6116_ID		0xd2
#घोषणा NCT6779_ID		0xc5
#घोषणा NCT6791_ID		0xc8
#घोषणा NCT6792_ID		0xc9
#घोषणा NCT6793_ID		0xd1
#घोषणा NCT6795_ID		0xd3
#घोषणा NCT6796_ID		0xd4	/* also NCT9697D, NCT9698D */

#घोषणा W83627HF_WDT_TIMEOUT	0xf6
#घोषणा W83697HF_WDT_TIMEOUT	0xf4
#घोषणा NCT6102D_WDT_TIMEOUT	0xf1

#घोषणा W83627HF_WDT_CONTROL	0xf5
#घोषणा W83697HF_WDT_CONTROL	0xf3
#घोषणा NCT6102D_WDT_CONTROL	0xf0

#घोषणा W836X7HF_WDT_CSR	0xf7
#घोषणा NCT6102D_WDT_CSR	0xf2

अटल व्योम superio_outb(पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, WDT_EFER);
	outb(val, WDT_EFDR);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक reg)
अणु
	outb(reg, WDT_EFER);
	वापस inb(WDT_EFDR);
पूर्ण

अटल पूर्णांक superio_enter(व्योम)
अणु
	अगर (!request_muxed_region(wdt_io, 2, WATCHDOG_NAME))
		वापस -EBUSY;

	outb_p(wdt_cfg_enter, WDT_EFER); /* Enter extended function mode */
	outb_p(wdt_cfg_enter, WDT_EFER); /* Again according to manual */

	वापस 0;
पूर्ण

अटल व्योम superio_select(पूर्णांक ld)
अणु
	superio_outb(0x07, ld);
पूर्ण

अटल व्योम superio_निकास(व्योम)
अणु
	outb_p(wdt_cfg_leave, WDT_EFER); /* Leave extended function mode */
	release_region(wdt_io, 2);
पूर्ण

अटल पूर्णांक w83627hf_init(काष्ठा watchकरोg_device *wकरोg, क्रमागत chips chip)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर t;

	ret = superio_enter();
	अगर (ret)
		वापस ret;

	superio_select(W83627HF_LD_WDT);

	/* set CR30 bit 0 to activate GPIO2 */
	t = superio_inb(0x30);
	अगर (!(t & 0x01))
		superio_outb(0x30, t | 0x01);

	चयन (chip) अणु
	हाल w83627hf:
	हाल w83627s:
		t = superio_inb(0x2B) & ~0x10;
		superio_outb(0x2B, t); /* set GPIO24 to WDT0 */
		अवरोध;
	हाल w83697hf:
		/* Set pin 119 to WDTO# mode (= CR29, WDT0) */
		t = superio_inb(0x29) & ~0x60;
		t |= 0x20;
		superio_outb(0x29, t);
		अवरोध;
	हाल w83697ug:
		/* Set pin 118 to WDTO# mode */
		t = superio_inb(0x2b) & ~0x04;
		superio_outb(0x2b, t);
		अवरोध;
	हाल w83627thf:
		t = (superio_inb(0x2B) & ~0x08) | 0x04;
		superio_outb(0x2B, t); /* set GPIO3 to WDT0 */
		अवरोध;
	हाल w83627dhg:
	हाल w83627dhg_p:
		t = superio_inb(0x2D) & ~0x01; /* PIN77 -> WDT0# */
		superio_outb(0x2D, t); /* set GPIO5 to WDT0 */
		t = superio_inb(cr_wdt_control);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_outb(cr_wdt_control, t);
		अवरोध;
	हाल w83637hf:
		अवरोध;
	हाल w83687thf:
		t = superio_inb(0x2C) & ~0x80; /* PIN47 -> WDT0# */
		superio_outb(0x2C, t);
		अवरोध;
	हाल w83627ehf:
	हाल w83627uhg:
	हाल w83667hg:
	हाल w83667hg_b:
	हाल nct6775:
	हाल nct6776:
	हाल nct6779:
	हाल nct6791:
	हाल nct6792:
	हाल nct6793:
	हाल nct6795:
	हाल nct6796:
	हाल nct6102:
	हाल nct6116:
		/*
		 * These chips have a fixed WDTO# output pin (W83627UHG),
		 * or support more than one WDTO# output pin.
		 * Don't touch its configuration, and hope the BIOS
		 * करोes the right thing.
		 */
		t = superio_inb(cr_wdt_control);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_outb(cr_wdt_control, t);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	t = superio_inb(cr_wdt_समयout);
	अगर (t != 0) अणु
		अगर (early_disable) अणु
			pr_warn("Stopping previously enabled watchdog until userland kicks in\n");
			superio_outb(cr_wdt_समयout, 0);
		पूर्ण अन्यथा अणु
			pr_info("Watchdog already running. Resetting timeout to %d sec\n",
				wकरोg->समयout);
			superio_outb(cr_wdt_समयout, wकरोg->समयout);
		पूर्ण
	पूर्ण

	/* set second mode & disable keyboard turning off watchकरोg */
	t = superio_inb(cr_wdt_control) & ~0x0C;
	superio_outb(cr_wdt_control, t);

	/* reset trigger, disable keyboard & mouse turning off watchकरोg */
	t = superio_inb(cr_wdt_csr) & ~0xD0;
	superio_outb(cr_wdt_csr, t);

	superio_निकास();

	वापस 0;
पूर्ण

अटल पूर्णांक wdt_set_समय(अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = superio_enter();
	अगर (ret)
		वापस ret;

	superio_select(W83627HF_LD_WDT);
	superio_outb(cr_wdt_समयout, समयout);
	superio_निकास();

	वापस 0;
पूर्ण

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस wdt_set_समय(wकरोg->समयout);
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस wdt_set_समय(0);
पूर्ण

अटल पूर्णांक wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg, अचिन्हित पूर्णांक समयout)
अणु
	wकरोg->समयout = समयout;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक wdt_get_समय(काष्ठा watchकरोg_device *wकरोg)
अणु
	अचिन्हित पूर्णांक समयleft;
	पूर्णांक ret;

	ret = superio_enter();
	अगर (ret)
		वापस 0;

	superio_select(W83627HF_LD_WDT);
	समयleft = superio_inb(cr_wdt_समयout);
	superio_निकास();

	वापस समयleft;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा watchकरोg_info wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "W83627HF Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdt_start,
	.stop = wdt_stop,
	.set_समयout = wdt_set_समयout,
	.get_समयleft = wdt_get_समय,
पूर्ण;

अटल काष्ठा watchकरोg_device wdt_dev = अणु
	.info = &wdt_info,
	.ops = &wdt_ops,
	.समयout = WATCHDOG_TIMEOUT,
	.min_समयout = 1,
	.max_समयout = 255,
पूर्ण;

/*
 *	The WDT needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल पूर्णांक wdt_find(पूर्णांक addr)
अणु
	u8 val;
	पूर्णांक ret;

	cr_wdt_समयout = W83627HF_WDT_TIMEOUT;
	cr_wdt_control = W83627HF_WDT_CONTROL;
	cr_wdt_csr = W836X7HF_WDT_CSR;

	ret = superio_enter();
	अगर (ret)
		वापस ret;
	superio_select(W83627HF_LD_WDT);
	val = superio_inb(0x20);
	चयन (val) अणु
	हाल W83627HF_ID:
		ret = w83627hf;
		अवरोध;
	हाल W83627S_ID:
		ret = w83627s;
		अवरोध;
	हाल W83697HF_ID:
		ret = w83697hf;
		cr_wdt_समयout = W83697HF_WDT_TIMEOUT;
		cr_wdt_control = W83697HF_WDT_CONTROL;
		अवरोध;
	हाल W83697UG_ID:
		ret = w83697ug;
		cr_wdt_समयout = W83697HF_WDT_TIMEOUT;
		cr_wdt_control = W83697HF_WDT_CONTROL;
		अवरोध;
	हाल W83637HF_ID:
		ret = w83637hf;
		अवरोध;
	हाल W83627THF_ID:
		ret = w83627thf;
		अवरोध;
	हाल W83687THF_ID:
		ret = w83687thf;
		अवरोध;
	हाल W83627EHF_ID:
		ret = w83627ehf;
		अवरोध;
	हाल W83627DHG_ID:
		ret = w83627dhg;
		अवरोध;
	हाल W83627DHG_P_ID:
		ret = w83627dhg_p;
		अवरोध;
	हाल W83627UHG_ID:
		ret = w83627uhg;
		अवरोध;
	हाल W83667HG_ID:
		ret = w83667hg;
		अवरोध;
	हाल W83667HG_B_ID:
		ret = w83667hg_b;
		अवरोध;
	हाल NCT6775_ID:
		ret = nct6775;
		अवरोध;
	हाल NCT6776_ID:
		ret = nct6776;
		अवरोध;
	हाल NCT6779_ID:
		ret = nct6779;
		अवरोध;
	हाल NCT6791_ID:
		ret = nct6791;
		अवरोध;
	हाल NCT6792_ID:
		ret = nct6792;
		अवरोध;
	हाल NCT6793_ID:
		ret = nct6793;
		अवरोध;
	हाल NCT6795_ID:
		ret = nct6795;
		अवरोध;
	हाल NCT6796_ID:
		ret = nct6796;
		अवरोध;
	हाल NCT6102_ID:
		ret = nct6102;
		cr_wdt_समयout = NCT6102D_WDT_TIMEOUT;
		cr_wdt_control = NCT6102D_WDT_CONTROL;
		cr_wdt_csr = NCT6102D_WDT_CSR;
		अवरोध;
	हाल NCT6116_ID:
		ret = nct6116;
		cr_wdt_समयout = NCT6102D_WDT_TIMEOUT;
		cr_wdt_control = NCT6102D_WDT_CONTROL;
		cr_wdt_csr = NCT6102D_WDT_CSR;
		अवरोध;
	हाल 0xff:
		ret = -ENODEV;
		अवरोध;
	शेष:
		ret = -ENODEV;
		pr_err("Unsupported chip ID: 0x%02x\n", val);
		अवरोध;
	पूर्ण
	superio_निकास();
	वापस ret;
पूर्ण

/*
 * On some प्रणालीs, the NCT6791D comes with a companion chip and the
 * watchकरोg function is in this companion chip. We must use a dअगरferent
 * unlocking sequence to access the companion chip.
 */
अटल पूर्णांक __init wdt_use_alt_key(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	wdt_cfg_enter = 0x88;
	wdt_cfg_leave = 0xBB;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id wdt_dmi_table[] __initस्थिर = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "INVES"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "CTS"),
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "INVES"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "SHARKBAY"),
		पूर्ण,
		.callback = wdt_use_alt_key,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init wdt_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक chip;
	अटल स्थिर अक्षर * स्थिर chip_name[] = अणु
		"W83627HF",
		"W83627S",
		"W83697HF",
		"W83697UG",
		"W83637HF",
		"W83627THF",
		"W83687THF",
		"W83627EHF",
		"W83627DHG",
		"W83627UHG",
		"W83667HG",
		"W83667DHG-P",
		"W83667HG-B",
		"NCT6775",
		"NCT6776",
		"NCT6779",
		"NCT6791",
		"NCT6792",
		"NCT6793",
		"NCT6795",
		"NCT6796",
		"NCT6102",
		"NCT6116",
	पूर्ण;

	/* Apply प्रणाली-specअगरic quirks */
	dmi_check_प्रणाली(wdt_dmi_table);

	wdt_io = 0x2e;
	chip = wdt_find(0x2e);
	अगर (chip < 0) अणु
		wdt_io = 0x4e;
		chip = wdt_find(0x4e);
		अगर (chip < 0)
			वापस chip;
	पूर्ण

	pr_info("WDT driver for %s Super I/O chip initialising\n",
		chip_name[chip]);

	watchकरोg_init_समयout(&wdt_dev, समयout, शून्य);
	watchकरोg_set_nowayout(&wdt_dev, nowayout);
	watchकरोg_stop_on_reboot(&wdt_dev);

	ret = w83627hf_init(&wdt_dev, chip);
	अगर (ret) अणु
		pr_err("failed to initialize watchdog (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = watchकरोg_रेजिस्टर_device(&wdt_dev);
	अगर (ret)
		वापस ret;

	pr_info("initialized. timeout=%d sec (nowayout=%d)\n",
		wdt_dev.समयout, nowayout);

	वापस ret;
पूर्ण

अटल व्योम __निकास wdt_निकास(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&wdt_dev);
पूर्ण

module_init(wdt_init);
module_निकास(wdt_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pथँdraig  Brady <P@draigBrady.com>");
MODULE_DESCRIPTION("w83627hf/thf WDT driver");
