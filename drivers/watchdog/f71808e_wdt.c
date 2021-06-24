<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2006 by Hans Edgington <hans@edgington.nl>              *
 *   Copyright (C) 2007-2009 Hans de Goede <hdegoede@redhat.com>           *
 *   Copyright (C) 2010 Giel van Schijndel <me@mortis.eu>                  *
 *                                                                         *
 ***************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DRVNAME "f71808e_wdt"

#घोषणा SIO_F71808FG_LD_WDT	0x07	/* Watchकरोg समयr logical device */
#घोषणा SIO_UNLOCK_KEY		0x87	/* Key to enable Super-I/O */
#घोषणा SIO_LOCK_KEY		0xAA	/* Key to disable Super-I/O */

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_DEVREV		0x22	/* Device revision */
#घोषणा SIO_REG_MANID		0x23	/* Fपूर्णांकek ID (2 bytes) */
#घोषणा SIO_REG_CLOCK_SEL	0x26	/* Clock select */
#घोषणा SIO_REG_ROM_ADDR_SEL	0x27	/* ROM address select */
#घोषणा SIO_F81866_REG_PORT_SEL	0x27	/* F81866 Multi-Function Register */
#घोषणा SIO_REG_TSI_LEVEL_SEL	0x28	/* TSI Level select */
#घोषणा SIO_REG_MFUNCT1		0x29	/* Multi function select 1 */
#घोषणा SIO_REG_MFUNCT2		0x2a	/* Multi function select 2 */
#घोषणा SIO_REG_MFUNCT3		0x2b	/* Multi function select 3 */
#घोषणा SIO_F81866_REG_GPIO1	0x2c	/* F81866 GPIO1 Enable Register */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */

#घोषणा SIO_FINTEK_ID		0x1934	/* Manufacturers ID */
#घोषणा SIO_F71808_ID		0x0901	/* Chipset ID */
#घोषणा SIO_F71858_ID		0x0507	/* Chipset ID */
#घोषणा SIO_F71862_ID		0x0601	/* Chipset ID */
#घोषणा SIO_F71868_ID		0x1106	/* Chipset ID */
#घोषणा SIO_F71869_ID		0x0814	/* Chipset ID */
#घोषणा SIO_F71869A_ID		0x1007	/* Chipset ID */
#घोषणा SIO_F71882_ID		0x0541	/* Chipset ID */
#घोषणा SIO_F71889_ID		0x0723	/* Chipset ID */
#घोषणा SIO_F81803_ID		0x1210	/* Chipset ID */
#घोषणा SIO_F81865_ID		0x0704	/* Chipset ID */
#घोषणा SIO_F81866_ID		0x1010	/* Chipset ID */

#घोषणा F71808FG_REG_WDO_CONF		0xf0
#घोषणा F71808FG_REG_WDT_CONF		0xf5
#घोषणा F71808FG_REG_WD_TIME		0xf6

#घोषणा F71808FG_FLAG_WDOUT_EN		7

#घोषणा F71808FG_FLAG_WDTMOUT_STS	6
#घोषणा F71808FG_FLAG_WD_EN		5
#घोषणा F71808FG_FLAG_WD_PULSE		4
#घोषणा F71808FG_FLAG_WD_UNIT		3

#घोषणा F81865_REG_WDO_CONF		0xfa
#घोषणा F81865_FLAG_WDOUT_EN		0

/* Default values */
#घोषणा WATCHDOG_TIMEOUT	60	/* 1 minute शेष समयout */
#घोषणा WATCHDOG_MAX_TIMEOUT	(60 * 255)
#घोषणा WATCHDOG_PULSE_WIDTH	125	/* 125 ms, शेष pulse width क्रम
					   watchकरोg संकेत */
#घोषणा WATCHDOG_F71862FG_PIN	63	/* शेष watchकरोg reset output
					   pin number 63 */

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल स्थिर पूर्णांक max_समयout = WATCHDOG_MAX_TIMEOUT;
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;	/* शेष समयout in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. 1<= timeout <="
			__MODULE_STRING(WATCHDOG_MAX_TIMEOUT) " (default="
			__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल अचिन्हित पूर्णांक pulse_width = WATCHDOG_PULSE_WIDTH;
module_param(pulse_width, uपूर्णांक, 0);
MODULE_PARM_DESC(pulse_width,
	"Watchdog signal pulse width. 0(=level), 1, 25, 30, 125, 150, 5000 or 6000 ms"
			" (default=" __MODULE_STRING(WATCHDOG_PULSE_WIDTH) ")");

अटल अचिन्हित पूर्णांक f71862fg_pin = WATCHDOG_F71862FG_PIN;
module_param(f71862fg_pin, uपूर्णांक, 0);
MODULE_PARM_DESC(f71862fg_pin,
	"Watchdog f71862fg reset output pin configuration. Choose pin 56 or 63"
			" (default=" __MODULE_STRING(WATCHDOG_F71862FG_PIN)")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0444);
MODULE_PARM_DESC(nowayout, "Disable watchdog shutdown on close");

अटल अचिन्हित पूर्णांक start_withसमयout;
module_param(start_withसमयout, uपूर्णांक, 0);
MODULE_PARM_DESC(start_withसमयout, "Start watchdog timer on module load with"
	" given initial timeout. Zero (default) disables this feature.");

क्रमागत chips अणु f71808fg, f71858fg, f71862fg, f71868, f71869, f71882fg, f71889fg,
	     f81803, f81865, f81866पूर्ण;

अटल स्थिर अक्षर *f71808e_names[] = अणु
	"f71808fg",
	"f71858fg",
	"f71862fg",
	"f71868",
	"f71869",
	"f71882fg",
	"f71889fg",
	"f81803",
	"f81865",
	"f81866",
पूर्ण;

/* Super-I/O Function prototypes */
अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक base, पूर्णांक reg);
अटल अंतरभूत पूर्णांक superio_inw(पूर्णांक base, पूर्णांक reg);
अटल अंतरभूत व्योम superio_outb(पूर्णांक base, पूर्णांक reg, u8 val);
अटल अंतरभूत व्योम superio_set_bit(पूर्णांक base, पूर्णांक reg, पूर्णांक bit);
अटल अंतरभूत व्योम superio_clear_bit(पूर्णांक base, पूर्णांक reg, पूर्णांक bit);
अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base);
अटल अंतरभूत व्योम superio_select(पूर्णांक base, पूर्णांक ld);
अटल अंतरभूत व्योम superio_निकास(पूर्णांक base);

काष्ठा watchकरोg_data अणु
	अचिन्हित लघु	sioaddr;
	क्रमागत chips	type;
	अचिन्हित दीर्घ	खोलोed;
	काष्ठा mutex	lock;
	अक्षर		expect_बंद;
	काष्ठा watchकरोg_info ident;

	अचिन्हित लघु	समयout;
	u8		समयr_val;	/* content क्रम the wd_समय रेजिस्टर */
	अक्षर		minutes_mode;
	u8		pulse_val;	/* pulse width flag */
	अक्षर		pulse_mode;	/* enable pulse output mode? */
	अक्षर		caused_reboot;	/* last reboot was by the watchकरोg */
पूर्ण;

अटल काष्ठा watchकरोg_data watchकरोg = अणु
	.lock = __MUTEX_INITIALIZER(watchकरोg.lock),
पूर्ण;

/* Super I/O functions */
अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक base, पूर्णांक reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल पूर्णांक superio_inw(पूर्णांक base, पूर्णांक reg)
अणु
	पूर्णांक val;
	val  = superio_inb(base, reg) << 8;
	val |= superio_inb(base, reg + 1);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम superio_outb(पूर्णांक base, पूर्णांक reg, u8 val)
अणु
	outb(reg, base);
	outb(val, base + 1);
पूर्ण

अटल अंतरभूत व्योम superio_set_bit(पूर्णांक base, पूर्णांक reg, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ val = superio_inb(base, reg);
	__set_bit(bit, &val);
	superio_outb(base, reg, val);
पूर्ण

अटल अंतरभूत व्योम superio_clear_bit(पूर्णांक base, पूर्णांक reg, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ val = superio_inb(base, reg);
	__clear_bit(bit, &val);
	superio_outb(base, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base)
अणु
	/* Don't step on other drivers' I/O space by accident */
	अगर (!request_muxed_region(base, 2, DRVNAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", (पूर्णांक)base);
		वापस -EBUSY;
	पूर्ण

	/* according to the datasheet the key must be sent twice! */
	outb(SIO_UNLOCK_KEY, base);
	outb(SIO_UNLOCK_KEY, base);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक base, पूर्णांक ld)
अणु
	outb(SIO_REG_LDSEL, base);
	outb(ld, base + 1);
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक base)
अणु
	outb(SIO_LOCK_KEY, base);
	release_region(base, 2);
पूर्ण

अटल पूर्णांक watchकरोg_set_समयout(पूर्णांक समयout)
अणु
	अगर (समयout <= 0
	 || समयout >  max_समयout) अणु
		pr_err("watchdog timeout out of range\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&watchकरोg.lock);

	watchकरोg.समयout = समयout;
	अगर (समयout > 0xff) अणु
		watchकरोg.समयr_val = DIV_ROUND_UP(समयout, 60);
		watchकरोg.minutes_mode = true;
	पूर्ण अन्यथा अणु
		watchकरोg.समयr_val = समयout;
		watchकरोg.minutes_mode = false;
	पूर्ण

	mutex_unlock(&watchकरोg.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक watchकरोg_set_pulse_width(अचिन्हित पूर्णांक pw)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक t1 = 25, t2 = 125, t3 = 5000;

	अगर (watchकरोg.type == f71868) अणु
		t1 = 30;
		t2 = 150;
		t3 = 6000;
	पूर्ण

	mutex_lock(&watchकरोg.lock);

	अगर        (pw <=  1) अणु
		watchकरोg.pulse_val = 0;
	पूर्ण अन्यथा अगर (pw <= t1) अणु
		watchकरोg.pulse_val = 1;
	पूर्ण अन्यथा अगर (pw <= t2) अणु
		watchकरोg.pulse_val = 2;
	पूर्ण अन्यथा अगर (pw <= t3) अणु
		watchकरोg.pulse_val = 3;
	पूर्ण अन्यथा अणु
		pr_err("pulse width out of range\n");
		err = -EINVAL;
		जाओ निकास_unlock;
	पूर्ण

	watchकरोg.pulse_mode = pw;

निकास_unlock:
	mutex_unlock(&watchकरोg.lock);
	वापस err;
पूर्ण

अटल पूर्णांक watchकरोg_keepalive(व्योम)
अणु
	पूर्णांक err = 0;

	mutex_lock(&watchकरोg.lock);
	err = superio_enter(watchकरोg.sioaddr);
	अगर (err)
		जाओ निकास_unlock;
	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

	अगर (watchकरोg.minutes_mode)
		/* select minutes क्रम समयr units */
		superio_set_bit(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_UNIT);
	अन्यथा
		/* select seconds क्रम समयr units */
		superio_clear_bit(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_UNIT);

	/* Set समयr value */
	superio_outb(watchकरोg.sioaddr, F71808FG_REG_WD_TIME,
			   watchकरोg.समयr_val);

	superio_निकास(watchकरोg.sioaddr);

निकास_unlock:
	mutex_unlock(&watchकरोg.lock);
	वापस err;
पूर्ण

अटल पूर्णांक watchकरोg_start(व्योम)
अणु
	पूर्णांक err;
	u8 पंचांगp;

	/* Make sure we करोn't die as soon as the watchकरोg is enabled below */
	err = watchकरोg_keepalive();
	अगर (err)
		वापस err;

	mutex_lock(&watchकरोg.lock);
	err = superio_enter(watchकरोg.sioaddr);
	अगर (err)
		जाओ निकास_unlock;
	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

	/* Watchकरोg pin configuration */
	चयन (watchकरोg.type) अणु
	हाल f71808fg:
		/* Set pin 21 to GPIO23/WDTRST#, then to WDTRST# */
		superio_clear_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT2, 3);
		superio_clear_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT3, 3);
		अवरोध;

	हाल f71862fg:
		अगर (f71862fg_pin == 63) अणु
			/* SPI must be disabled first to use this pin! */
			superio_clear_bit(watchकरोg.sioaddr, SIO_REG_ROM_ADDR_SEL, 6);
			superio_set_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT3, 4);
		पूर्ण अन्यथा अगर (f71862fg_pin == 56) अणु
			superio_set_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT1, 1);
		पूर्ण
		अवरोध;

	हाल f71868:
	हाल f71869:
		/* GPIO14 --> WDTRST# */
		superio_clear_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT1, 4);
		अवरोध;

	हाल f71882fg:
		/* Set pin 56 to WDTRST# */
		superio_set_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT1, 1);
		अवरोध;

	हाल f71889fg:
		/* set pin 40 to WDTRST# */
		superio_outb(watchकरोg.sioaddr, SIO_REG_MFUNCT3,
			superio_inb(watchकरोg.sioaddr, SIO_REG_MFUNCT3) & 0xcf);
		अवरोध;

	हाल f81803:
		/* Enable TSI Level रेजिस्टर bank */
		superio_clear_bit(watchकरोg.sioaddr, SIO_REG_CLOCK_SEL, 3);
		/* Set pin 27 to WDTRST# */
		superio_outb(watchकरोg.sioaddr, SIO_REG_TSI_LEVEL_SEL, 0x5f &
			superio_inb(watchकरोg.sioaddr, SIO_REG_TSI_LEVEL_SEL));
		अवरोध;

	हाल f81865:
		/* Set pin 70 to WDTRST# */
		superio_clear_bit(watchकरोg.sioaddr, SIO_REG_MFUNCT3, 5);
		अवरोध;

	हाल f81866:
		/*
		 * GPIO1 Control Register when 27h BIT3:2 = 01 & BIT0 = 0.
		 * The PIN 70(GPIO15/WDTRST) is controlled by 2Ch:
		 *     BIT5: 0 -> WDTRST#
		 *           1 -> GPIO15
		 */
		पंचांगp = superio_inb(watchकरोg.sioaddr, SIO_F81866_REG_PORT_SEL);
		पंचांगp &= ~(BIT(3) | BIT(0));
		पंचांगp |= BIT(2);
		superio_outb(watchकरोg.sioaddr, SIO_F81866_REG_PORT_SEL, पंचांगp);

		superio_clear_bit(watchकरोg.sioaddr, SIO_F81866_REG_GPIO1, 5);
		अवरोध;

	शेष:
		/*
		 * 'default' label to shut up the compiler and catch
		 * programmer errors
		 */
		err = -ENODEV;
		जाओ निकास_superio;
	पूर्ण

	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);
	superio_set_bit(watchकरोg.sioaddr, SIO_REG_ENABLE, 0);

	अगर (watchकरोg.type == f81865 || watchकरोg.type == f81866)
		superio_set_bit(watchकरोg.sioaddr, F81865_REG_WDO_CONF,
				F81865_FLAG_WDOUT_EN);
	अन्यथा
		superio_set_bit(watchकरोg.sioaddr, F71808FG_REG_WDO_CONF,
				F71808FG_FLAG_WDOUT_EN);

	superio_set_bit(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
			F71808FG_FLAG_WD_EN);

	अगर (watchकरोg.pulse_mode) अणु
		/* Select "pulse" output mode with given duration */
		u8 wdt_conf = superio_inb(watchकरोg.sioaddr,
				F71808FG_REG_WDT_CONF);

		/* Set WD_PSWIDTH bits (1:0) */
		wdt_conf = (wdt_conf & 0xfc) | (watchकरोg.pulse_val & 0x03);
		/* Set WD_PULSE to "pulse" mode */
		wdt_conf |= BIT(F71808FG_FLAG_WD_PULSE);

		superio_outb(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
				wdt_conf);
	पूर्ण अन्यथा अणु
		/* Select "level" output mode */
		superio_clear_bit(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_PULSE);
	पूर्ण

निकास_superio:
	superio_निकास(watchकरोg.sioaddr);
निकास_unlock:
	mutex_unlock(&watchकरोg.lock);

	वापस err;
पूर्ण

अटल पूर्णांक watchकरोg_stop(व्योम)
अणु
	पूर्णांक err = 0;

	mutex_lock(&watchकरोg.lock);
	err = superio_enter(watchकरोg.sioaddr);
	अगर (err)
		जाओ निकास_unlock;
	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

	superio_clear_bit(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF,
			F71808FG_FLAG_WD_EN);

	superio_निकास(watchकरोg.sioaddr);

निकास_unlock:
	mutex_unlock(&watchकरोg.lock);

	वापस err;
पूर्ण

अटल पूर्णांक watchकरोg_get_status(व्योम)
अणु
	पूर्णांक status = 0;

	mutex_lock(&watchकरोg.lock);
	status = (watchकरोg.caused_reboot) ? WDIOF_CARDRESET : 0;
	mutex_unlock(&watchकरोg.lock);

	वापस status;
पूर्ण

अटल bool watchकरोg_is_running(व्योम)
अणु
	/*
	 * अगर we fail to determine the watchकरोg's status assume it to be
	 * running to be on the safe side
	 */
	bool is_running = true;

	mutex_lock(&watchकरोg.lock);
	अगर (superio_enter(watchकरोg.sioaddr))
		जाओ निकास_unlock;
	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

	is_running = (superio_inb(watchकरोg.sioaddr, SIO_REG_ENABLE) & BIT(0))
		&& (superio_inb(watchकरोg.sioaddr, F71808FG_REG_WDT_CONF)
			& BIT(F71808FG_FLAG_WD_EN));

	superio_निकास(watchकरोg.sioaddr);

निकास_unlock:
	mutex_unlock(&watchकरोg.lock);
	वापस is_running;
पूर्ण

/* /dev/watchकरोg api */

अटल पूर्णांक watchकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err;

	/* If the watchकरोg is alive we करोn't need to start it again */
	अगर (test_and_set_bit(0, &watchकरोg.खोलोed))
		वापस -EBUSY;

	err = watchकरोg_start();
	अगर (err) अणु
		clear_bit(0, &watchकरोg.खोलोed);
		वापस err;
	पूर्ण

	अगर (nowayout)
		__module_get(THIS_MODULE);

	watchकरोg.expect_बंद = 0;
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक watchकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	clear_bit(0, &watchकरोg.खोलोed);

	अगर (!watchकरोg.expect_बंद) अणु
		watchकरोg_keepalive();
		pr_crit("Unexpected close, not stopping watchdog!\n");
	पूर्ण अन्यथा अगर (!nowayout) अणु
		watchकरोg_stop();
	पूर्ण
	वापस 0;
पूर्ण

/*
 *      watchकरोg_ग_लिखो:
 *      @file: file handle to the watchकरोg
 *      @buf: buffer to ग_लिखो
 *      @count: count of bytes
 *      @ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *      A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *      ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार watchकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			bool expect_बंद = false;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = true;
			पूर्ण

			/* Properly order ग_लिखोs across विभाजन()ed processes */
			mutex_lock(&watchकरोg.lock);
			watchकरोg.expect_बंद = expect_बंद;
			mutex_unlock(&watchकरोg.lock);
		पूर्ण

		/* someone wrote to us, we should restart समयr */
		watchकरोg_keepalive();
	पूर्ण
	वापस count;
पूर्ण

/*
 *      watchकरोg_ioctl:
 *      @inode: inode of the device
 *      @file: file handle to the device
 *      @cmd: watchकरोg command
 *      @arg: argument poपूर्णांकer
 *
 *      The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *      according to their available features.
 */
अटल दीर्घ watchकरोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	पूर्णांक status;
	पूर्णांक new_options;
	पूर्णांक new_समयout;
	जोड़ अणु
		काष्ठा watchकरोg_info __user *ident;
		पूर्णांक __user *i;
	पूर्ण uarg;

	uarg.i = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(uarg.ident, &watchकरोg.ident,
			माप(watchकरोg.ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
		status = watchकरोg_get_status();
		अगर (status < 0)
			वापस status;
		वापस put_user(status, uarg.i);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, uarg.i);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_options, uarg.i))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD)
			watchकरोg_stop();

		अगर (new_options & WDIOS_ENABLECARD)
			वापस watchकरोg_start();
		fallthrough;

	हाल WDIOC_KEEPALIVE:
		watchकरोg_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, uarg.i))
			वापस -EFAULT;

		अगर (watchकरोg_set_समयout(new_समयout))
			वापस -EINVAL;

		watchकरोg_keepalive();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(watchकरोg.समयout, uarg.i);

	शेष:
		वापस -ENOTTY;

	पूर्ण
पूर्ण

अटल पूर्णांक watchकरोg_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		watchकरोg_stop();
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations watchकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.खोलो		= watchकरोg_खोलो,
	.release	= watchकरोg_release,
	.ग_लिखो		= watchकरोg_ग_लिखो,
	.unlocked_ioctl	= watchकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice watchकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &watchकरोg_fops,
पूर्ण;

अटल काष्ठा notअगरier_block watchकरोg_notअगरier = अणु
	.notअगरier_call = watchकरोg_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init watchकरोg_init(पूर्णांक sioaddr)
अणु
	पूर्णांक wdt_conf, err = 0;

	/* No need to lock watchकरोg.lock here because no entry poपूर्णांकs
	 * पूर्णांकo the module have been रेजिस्टरed yet.
	 */
	watchकरोg.sioaddr = sioaddr;
	watchकरोg.ident.options = WDIOF_MAGICCLOSE
				| WDIOF_KEEPALIVEPING
				| WDIOF_CARDRESET;

	snम_लिखो(watchकरोg.ident.identity,
		माप(watchकरोg.ident.identity), "%s watchdog",
		f71808e_names[watchकरोg.type]);

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;
	superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

	wdt_conf = superio_inb(sioaddr, F71808FG_REG_WDT_CONF);
	watchकरोg.caused_reboot = wdt_conf & BIT(F71808FG_FLAG_WDTMOUT_STS);

	/*
	 * We करोn't want WDTMOUT_STS to stick around till regular reboot.
	 * Write 1 to the bit to clear it to zero.
	 */
	superio_outb(sioaddr, F71808FG_REG_WDT_CONF,
		     wdt_conf | BIT(F71808FG_FLAG_WDTMOUT_STS));

	superio_निकास(sioaddr);

	err = watchकरोg_set_समयout(समयout);
	अगर (err)
		वापस err;
	err = watchकरोg_set_pulse_width(pulse_width);
	अगर (err)
		वापस err;

	err = रेजिस्टर_reboot_notअगरier(&watchकरोg_notअगरier);
	अगर (err)
		वापस err;

	err = misc_रेजिस्टर(&watchकरोg_miscdev);
	अगर (err) अणु
		pr_err("cannot register miscdev on minor=%d\n",
		       watchकरोg_miscdev.minor);
		जाओ निकास_reboot;
	पूर्ण

	अगर (start_withसमयout) अणु
		अगर (start_withसमयout <= 0
		 || start_withसमयout >  max_समयout) अणु
			pr_err("starting timeout out of range\n");
			err = -EINVAL;
			जाओ निकास_miscdev;
		पूर्ण

		err = watchकरोg_start();
		अगर (err) अणु
			pr_err("cannot start watchdog timer\n");
			जाओ निकास_miscdev;
		पूर्ण

		mutex_lock(&watchकरोg.lock);
		err = superio_enter(sioaddr);
		अगर (err)
			जाओ निकास_unlock;
		superio_select(watchकरोg.sioaddr, SIO_F71808FG_LD_WDT);

		अगर (start_withसमयout > 0xff) अणु
			/* select minutes क्रम समयr units */
			superio_set_bit(sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_UNIT);
			superio_outb(sioaddr, F71808FG_REG_WD_TIME,
				DIV_ROUND_UP(start_withसमयout, 60));
		पूर्ण अन्यथा अणु
			/* select seconds क्रम समयr units */
			superio_clear_bit(sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_UNIT);
			superio_outb(sioaddr, F71808FG_REG_WD_TIME,
				start_withसमयout);
		पूर्ण

		superio_निकास(sioaddr);
		mutex_unlock(&watchकरोg.lock);

		अगर (nowayout)
			__module_get(THIS_MODULE);

		pr_info("watchdog started with initial timeout of %u sec\n",
			start_withसमयout);
	पूर्ण

	वापस 0;

निकास_unlock:
	mutex_unlock(&watchकरोg.lock);
निकास_miscdev:
	misc_deरेजिस्टर(&watchकरोg_miscdev);
निकास_reboot:
	unरेजिस्टर_reboot_notअगरier(&watchकरोg_notअगरier);

	वापस err;
पूर्ण

अटल पूर्णांक __init f71808e_find(पूर्णांक sioaddr)
अणु
	u16 devid;
	पूर्णांक err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	devid = superio_inw(sioaddr, SIO_REG_MANID);
	अगर (devid != SIO_FINTEK_ID) अणु
		pr_debug("Not a Fintek device\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	devid = क्रमce_id ? क्रमce_id : superio_inw(sioaddr, SIO_REG_DEVID);
	चयन (devid) अणु
	हाल SIO_F71808_ID:
		watchकरोg.type = f71808fg;
		अवरोध;
	हाल SIO_F71862_ID:
		watchकरोg.type = f71862fg;
		अवरोध;
	हाल SIO_F71868_ID:
		watchकरोg.type = f71868;
		अवरोध;
	हाल SIO_F71869_ID:
	हाल SIO_F71869A_ID:
		watchकरोg.type = f71869;
		अवरोध;
	हाल SIO_F71882_ID:
		watchकरोg.type = f71882fg;
		अवरोध;
	हाल SIO_F71889_ID:
		watchकरोg.type = f71889fg;
		अवरोध;
	हाल SIO_F71858_ID:
		/* Confirmed (by datasheet) not to have a watchकरोg. */
		err = -ENODEV;
		जाओ निकास;
	हाल SIO_F81803_ID:
		watchकरोg.type = f81803;
		अवरोध;
	हाल SIO_F81865_ID:
		watchकरोg.type = f81865;
		अवरोध;
	हाल SIO_F81866_ID:
		watchकरोg.type = f81866;
		अवरोध;
	शेष:
		pr_info("Unrecognized Fintek device: %04x\n",
			(अचिन्हित पूर्णांक)devid);
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	pr_info("Found %s watchdog chip, revision %d\n",
		f71808e_names[watchकरोg.type],
		(पूर्णांक)superio_inb(sioaddr, SIO_REG_DEVREV));
निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

अटल पूर्णांक __init f71808e_init(व्योम)
अणु
	अटल स्थिर अचिन्हित लघु addrs[] = अणु 0x2e, 0x4e पूर्ण;
	पूर्णांक err = -ENODEV;
	पूर्णांक i;

	अगर (f71862fg_pin != 63 && f71862fg_pin != 56) अणु
		pr_err("Invalid argument f71862fg_pin=%d\n", f71862fg_pin);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(addrs); i++) अणु
		err = f71808e_find(addrs[i]);
		अगर (err == 0)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(addrs))
		वापस err;

	वापस watchकरोg_init(addrs[i]);
पूर्ण

अटल व्योम __निकास f71808e_निकास(व्योम)
अणु
	अगर (watchकरोg_is_running()) अणु
		pr_warn("Watchdog timer still running, stopping it\n");
		watchकरोg_stop();
	पूर्ण
	misc_deरेजिस्टर(&watchकरोg_miscdev);
	unरेजिस्टर_reboot_notअगरier(&watchकरोg_notअगरier);
पूर्ण

MODULE_DESCRIPTION("F71808E Watchdog Driver");
MODULE_AUTHOR("Giel van Schijndel <me@mortis.eu>");
MODULE_LICENSE("GPL");

module_init(f71808e_init);
module_निकास(f71808e_निकास);
