<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *      NS pc87413-wdt Watchकरोg Timer driver क्रम Linux 2.6.x.x
 *
 *      This code is based on wdt.c with original copyright.
 *
 *      (C) Copyright 2006 Sven Anders, <anders@anduras.de>
 *                     and Marcus Junker, <junker@anduras.de>
 *
 *      Neither Sven Anders, Marcus Junker nor ANDURAS AG
 *      admit liability nor provide warranty क्रम any of this software.
 *      This material is provided "AS-IS" and at no अक्षरge.
 *
 *      Release 1.1
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


/* #घोषणा DEBUG 1 */

#घोषणा DEFAULT_TIMEOUT     1		/* 1 minute */
#घोषणा MAX_TIMEOUT         255

#घोषणा VERSION             "1.1"
#घोषणा MODNAME             "pc87413 WDT"
#घोषणा DPFX                MODNAME " - DEBUG: "

#घोषणा WDT_INDEX_IO_PORT   (io+0)	/* I/O port base (index रेजिस्टर) */
#घोषणा WDT_DATA_IO_PORT    (WDT_INDEX_IO_PORT+1)
#घोषणा SWC_LDN             0x04
#घोषणा SIOCFG2             0x22	/* Serial IO रेजिस्टर */
#घोषणा WDCTL               0x10	/* Watchकरोg-Timer-Control-Register */
#घोषणा WDTO                0x11	/* Watchकरोg समयout रेजिस्टर */
#घोषणा WDCFG               0x12	/* Watchकरोg config रेजिस्टर */

#घोषणा IO_DEFAULT	0x2E		/* Address used on Portwell Boards */

अटल पूर्णांक io = IO_DEFAULT;
अटल पूर्णांक swc_base_addr = -1;

अटल पूर्णांक समयout = DEFAULT_TIMEOUT;	/* समयout value */
अटल अचिन्हित दीर्घ समयr_enabled;	/* is the समयr enabled? */

अटल अक्षर expect_बंद;		/* is the बंद expected? */

अटल DEFINE_SPINLOCK(io_lock);	/* to guard us from io races */

अटल bool nowayout = WATCHDOG_NOWAYOUT;

/* -- Low level function ----------------------------------------*/

/* Select pins क्रम Watchकरोg output */

अटल अंतरभूत व्योम pc87413_select_wdt_out(व्योम)
अणु
	अचिन्हित पूर्णांक cr_data = 0;

	/* Step 1: Select multiple pin,pin55,as WDT output */

	outb_p(SIOCFG2, WDT_INDEX_IO_PORT);

	cr_data = inb(WDT_DATA_IO_PORT);

	cr_data |= 0x80; /* Set Bit7 to 1*/
	outb_p(SIOCFG2, WDT_INDEX_IO_PORT);

	outb_p(cr_data, WDT_DATA_IO_PORT);

#अगर_घोषित DEBUG
	pr_info(DPFX
		"Select multiple pin,pin55,as WDT output: Bit7 to 1: %d\n",
								cr_data);
#पूर्ण_अगर
पूर्ण

/* Enable SWC functions */

अटल अंतरभूत व्योम pc87413_enable_swc(व्योम)
अणु
	अचिन्हित पूर्णांक cr_data = 0;

	/* Step 2: Enable SWC functions */

	outb_p(0x07, WDT_INDEX_IO_PORT);	/* Poपूर्णांक SWC_LDN (LDN=4) */
	outb_p(SWC_LDN, WDT_DATA_IO_PORT);

	outb_p(0x30, WDT_INDEX_IO_PORT);	/* Read Index 0x30 First */
	cr_data = inb(WDT_DATA_IO_PORT);
	cr_data |= 0x01;			/* Set Bit0 to 1 */
	outb_p(0x30, WDT_INDEX_IO_PORT);
	outb_p(cr_data, WDT_DATA_IO_PORT);	/* Index0x30_bit0P1 */

#अगर_घोषित DEBUG
	pr_info(DPFX "pc87413 - Enable SWC functions\n");
#पूर्ण_अगर
पूर्ण

/* Read SWC I/O base address */

अटल व्योम pc87413_get_swc_base_addr(व्योम)
अणु
	अचिन्हित अक्षर addr_l, addr_h = 0;

	/* Step 3: Read SWC I/O Base Address */

	outb_p(0x60, WDT_INDEX_IO_PORT);	/* Read Index 0x60 */
	addr_h = inb(WDT_DATA_IO_PORT);

	outb_p(0x61, WDT_INDEX_IO_PORT);	/* Read Index 0x61 */

	addr_l = inb(WDT_DATA_IO_PORT);

	swc_base_addr = (addr_h << 8) + addr_l;
#अगर_घोषित DEBUG
	pr_info(DPFX
		"Read SWC I/O Base Address: low %d, high %d, res %d\n",
						addr_l, addr_h, swc_base_addr);
#पूर्ण_अगर
पूर्ण

/* Select Bank 3 of SWC */

अटल अंतरभूत व्योम pc87413_swc_bank3(व्योम)
अणु
	/* Step 4: Select Bank3 of SWC */
	outb_p(inb(swc_base_addr + 0x0f) | 0x03, swc_base_addr + 0x0f);
#अगर_घोषित DEBUG
	pr_info(DPFX "Select Bank3 of SWC\n");
#पूर्ण_अगर
पूर्ण

/* Set watchकरोg समयout to x minutes */

अटल अंतरभूत व्योम pc87413_programm_wdto(अक्षर pc87413_समय)
अणु
	/* Step 5: Programm WDTO, Twd. */
	outb_p(pc87413_समय, swc_base_addr + WDTO);
#अगर_घोषित DEBUG
	pr_info(DPFX "Set WDTO to %d minutes\n", pc87413_समय);
#पूर्ण_अगर
पूर्ण

/* Enable WDEN */

अटल अंतरभूत व्योम pc87413_enable_wden(व्योम)
अणु
	/* Step 6: Enable WDEN */
	outb_p(inb(swc_base_addr + WDCTL) | 0x01, swc_base_addr + WDCTL);
#अगर_घोषित DEBUG
	pr_info(DPFX "Enable WDEN\n");
#पूर्ण_अगर
पूर्ण

/* Enable SW_WD_TREN */
अटल अंतरभूत व्योम pc87413_enable_sw_wd_tren(व्योम)
अणु
	/* Enable SW_WD_TREN */
	outb_p(inb(swc_base_addr + WDCFG) | 0x80, swc_base_addr + WDCFG);
#अगर_घोषित DEBUG
	pr_info(DPFX "Enable SW_WD_TREN\n");
#पूर्ण_अगर
पूर्ण

/* Disable SW_WD_TREN */

अटल अंतरभूत व्योम pc87413_disable_sw_wd_tren(व्योम)
अणु
	/* Disable SW_WD_TREN */
	outb_p(inb(swc_base_addr + WDCFG) & 0x7f, swc_base_addr + WDCFG);
#अगर_घोषित DEBUG
	pr_info(DPFX "pc87413 - Disable SW_WD_TREN\n");
#पूर्ण_अगर
पूर्ण

/* Enable SW_WD_TRG */

अटल अंतरभूत व्योम pc87413_enable_sw_wd_trg(व्योम)
अणु
	/* Enable SW_WD_TRG */
	outb_p(inb(swc_base_addr + WDCTL) | 0x80, swc_base_addr + WDCTL);
#अगर_घोषित DEBUG
	pr_info(DPFX "pc87413 - Enable SW_WD_TRG\n");
#पूर्ण_अगर
पूर्ण

/* Disable SW_WD_TRG */

अटल अंतरभूत व्योम pc87413_disable_sw_wd_trg(व्योम)
अणु
	/* Disable SW_WD_TRG */
	outb_p(inb(swc_base_addr + WDCTL) & 0x7f, swc_base_addr + WDCTL);
#अगर_घोषित DEBUG
	pr_info(DPFX "Disable SW_WD_TRG\n");
#पूर्ण_अगर
पूर्ण

/* -- Higher level functions ------------------------------------*/

/* Enable the watchकरोg */

अटल व्योम pc87413_enable(व्योम)
अणु
	spin_lock(&io_lock);

	pc87413_swc_bank3();
	pc87413_programm_wdto(समयout);
	pc87413_enable_wden();
	pc87413_enable_sw_wd_tren();
	pc87413_enable_sw_wd_trg();

	spin_unlock(&io_lock);
पूर्ण

/* Disable the watchकरोg */

अटल व्योम pc87413_disable(व्योम)
अणु
	spin_lock(&io_lock);

	pc87413_swc_bank3();
	pc87413_disable_sw_wd_tren();
	pc87413_disable_sw_wd_trg();
	pc87413_programm_wdto(0);

	spin_unlock(&io_lock);
पूर्ण

/* Refresh the watchकरोg */

अटल व्योम pc87413_refresh(व्योम)
अणु
	spin_lock(&io_lock);

	pc87413_swc_bank3();
	pc87413_disable_sw_wd_tren();
	pc87413_disable_sw_wd_trg();
	pc87413_programm_wdto(समयout);
	pc87413_enable_wden();
	pc87413_enable_sw_wd_tren();
	pc87413_enable_sw_wd_trg();

	spin_unlock(&io_lock);
पूर्ण

/* -- File operations -------------------------------------------*/

/**
 *	pc87413_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 */

अटल पूर्णांक pc87413_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */

	अगर (test_and_set_bit(0, &समयr_enabled))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Reload and activate समयr */
	pc87413_refresh();

	pr_info("Watchdog enabled. Timeout set to %d minute(s).\n", समयout);

	वापस stream_खोलो(inode, file);
पूर्ण

/**
 *	pc87413_release:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 *	The watchकरोg has a configurable API. There is a religious dispute
 *	between people who want their watchकरोg to be able to shut करोwn and
 *	those who want to be sure अगर the watchकरोg manager dies the machine
 *	reboots. In the क्रमmer हाल we disable the counters, in the latter
 *	हाल you have to खोलो it again very soon.
 */

अटल पूर्णांक pc87413_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Shut off the समयr. */

	अगर (expect_बंद == 42) अणु
		pc87413_disable();
		pr_info("Watchdog disabled, sleeping again...\n");
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		pc87413_refresh();
	पूर्ण
	clear_bit(0, &समयr_enabled);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/**
 *	pc87413_status:
 *
 *      वापस, अगर the watchकरोg is enabled (समयout is set...)
 */


अटल पूर्णांक pc87413_status(व्योम)
अणु
	  वापस 0; /* currently not supported */
पूर्ण

/**
 *	pc87413_ग_लिखो:
 *	@file: file handle to the watchकरोg
 *	@data: data buffer to ग_लिखो
 *	@len: length in bytes
 *	@ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *	A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *	ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार pc87413_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			     माप_प्रकार len, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* reset expect flag */
			expect_बंद = 0;

			/* scan to see whether or not we got the
			   magic अक्षरacter */
			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should reload the समयr */
		pc87413_refresh();
	पूर्ण
	वापस len;
पूर्ण

/**
 *	pc87413_ioctl:
 *	@file: file handle to the device
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *	according to their available features. We only actually usefully support
 *	querying capabilities and current status.
 */

अटल दीर्घ pc87413_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_समयout;

	जोड़ अणु
		काष्ठा watchकरोg_info __user *ident;
		पूर्णांक __user *i;
	पूर्ण uarg;

	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options          = WDIOF_KEEPALIVEPING |
				    WDIOF_SETTIMEOUT |
				    WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity         = "PC87413(HF/F) watchdog",
	पूर्ण;

	uarg.i = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(uarg.ident, &ident,
					माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
		वापस put_user(pc87413_status(), uarg.i);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, uarg.i);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, retval = -EINVAL;
		अगर (get_user(options, uarg.i))
			वापस -EFAULT;
		अगर (options & WDIOS_DISABLECARD) अणु
			pc87413_disable();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			pc87413_enable();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		pc87413_refresh();
#अगर_घोषित DEBUG
		pr_info(DPFX "keepalive\n");
#पूर्ण_अगर
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, uarg.i))
			वापस -EFAULT;
		/* the API states this is given in secs */
		new_समयout /= 60;
		अगर (new_समयout < 0 || new_समयout > MAX_TIMEOUT)
			वापस -EINVAL;
		समयout = new_समयout;
		pc87413_refresh();
		fallthrough;	/* and वापस the new समयout */
	हाल WDIOC_GETTIMEOUT:
		new_समयout = समयout * 60;
		वापस put_user(new_समयout, uarg.i);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/* -- Notअगरier funtions -----------------------------------------*/

/**
 *	notअगरy_sys:
 *	@this: our notअगरier block
 *	@code: the event being reported
 *	@unused: unused
 *
 *	Our notअगरier is called on प्रणाली shutकरोwns. We want to turn the card
 *	off at reboot otherwise the machine will reboot again during memory
 *	test or worse yet during the following fsck. This would suck, in fact
 *	trust me - अगर it happens it करोes suck.
 */

अटल पूर्णांक pc87413_notअगरy_sys(काष्ठा notअगरier_block *this,
			      अचिन्हित दीर्घ code,
			      व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		/* Turn the card off */
		pc87413_disable();
	वापस NOTIFY_DONE;
पूर्ण

/* -- Module's काष्ठाures ---------------------------------------*/

अटल स्थिर काष्ठा file_operations pc87413_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= pc87413_ग_लिखो,
	.unlocked_ioctl	= pc87413_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= pc87413_खोलो,
	.release	= pc87413_release,
पूर्ण;

अटल काष्ठा notअगरier_block pc87413_notअगरier = अणु
	.notअगरier_call  = pc87413_notअगरy_sys,
पूर्ण;

अटल काष्ठा miscdevice pc87413_miscdev = अणु
	.minor          = WATCHDOG_MINOR,
	.name           = "watchdog",
	.fops           = &pc87413_fops,
पूर्ण;

/* -- Module init functions -------------------------------------*/

/**
 *	pc87413_init: module's "constructor"
 *
 *	Set up the WDT watchकरोg board. All we have to करो is grab the
 *	resources we require and bitch अगर anyone beat us to them.
 *	The खोलो() function will actually kick the board off.
 */

अटल पूर्णांक __init pc87413_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("Version " VERSION " at io 0x%X\n",
							WDT_INDEX_IO_PORT);

	अगर (!request_muxed_region(io, 2, MODNAME))
		वापस -EBUSY;

	ret = रेजिस्टर_reboot_notअगरier(&pc87413_notअगरier);
	अगर (ret != 0)
		pr_err("cannot register reboot notifier (err=%d)\n", ret);

	ret = misc_रेजिस्टर(&pc87413_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ reboot_unreg;
	पूर्ण
	pr_info("initialized. timeout=%d min\n", समयout);

	pc87413_select_wdt_out();
	pc87413_enable_swc();
	pc87413_get_swc_base_addr();

	अगर (!request_region(swc_base_addr, 0x20, MODNAME)) अणु
		pr_err("cannot request SWC region at 0x%x\n", swc_base_addr);
		ret = -EBUSY;
		जाओ misc_unreg;
	पूर्ण

	pc87413_enable();

	release_region(io, 2);
	वापस 0;

misc_unreg:
	misc_deरेजिस्टर(&pc87413_miscdev);
reboot_unreg:
	unरेजिस्टर_reboot_notअगरier(&pc87413_notअगरier);
	release_region(io, 2);
	वापस ret;
पूर्ण

/**
 *	pc87413_निकास: module's "destructor"
 *
 *	Unload the watchकरोg. You cannot करो this with any file handles खोलो.
 *	If your watchकरोg is set to जारी ticking on बंद and you unload
 *	it, well it keeps ticking. We won't get the पूर्णांकerrupt but the board
 *	will not touch PC memory so all is fine. You just have to load a new
 *	module in 60 seconds or reboot.
 */

अटल व्योम __निकास pc87413_निकास(व्योम)
अणु
	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout) अणु
		pc87413_disable();
		pr_info("Watchdog disabled\n");
	पूर्ण

	misc_deरेजिस्टर(&pc87413_miscdev);
	unरेजिस्टर_reboot_notअगरier(&pc87413_notअगरier);
	release_region(swc_base_addr, 0x20);

	pr_info("watchdog component driver removed\n");
पूर्ण

module_init(pc87413_init);
module_निकास(pc87413_निकास);

MODULE_AUTHOR("Sven Anders <anders@anduras.de>");
MODULE_AUTHOR("Marcus Junker <junker@anduras.de>");
MODULE_DESCRIPTION("PC87413 WDT driver");
MODULE_LICENSE("GPL");

module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, MODNAME " I/O port (default: "
					__MODULE_STRING(IO_DEFAULT) ").");

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in minutes (default="
				__MODULE_STRING(DEFAULT_TIMEOUT) ").");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

