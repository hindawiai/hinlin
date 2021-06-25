<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Berkshire PCI-PC Watchकरोg Card Driver
 *
 *	(c) Copyright 2003-2007 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	Based on source code of the following authors:
 *	  Ken Hollis <kenji@bitgate.com>,
 *	  Lindsay Harris <lindsay@bluegum.com>,
 *	  Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *	  Matt Domsch <Matt_Domsch@dell.com>,
 *	  Rob Radez <rob@osinvestor.com>
 *
 *	Neither Wim Van Sebroeck nor Iguana vzw. admit liability nor
 *	provide warranty क्रम any of this software. This material is
 *	provided "AS-IS" and at no अक्षरge.
 */

/*
 *	A bells and whistles driver is available from:
 *	http://www.kernel.org/pub/linux/kernel/people/wim/pcwd/pcwd_pci/
 *
 *	More info available at
 *	http://www.berkprod.com/ or http://www.pcwatchकरोg.com/
 */

/*
 *	Includes, defines, variables, module parameters, ...
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>	/* For module specअगरic items */
#समावेश <linux/moduleparam.h>	/* For new moduleparam's */
#समावेश <linux/types.h>	/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>	/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>	/* For prपूर्णांकk/panic/... */
#समावेश <linux/delay.h>	/* For mdelay function */
#समावेश <linux/miscdevice.h>	/* For काष्ठा miscdevice */
#समावेश <linux/watchकरोg.h>	/* For the watchकरोg specअगरic items */
#समावेश <linux/notअगरier.h>	/* For notअगरier support */
#समावेश <linux/reboot.h>	/* For reboot_notअगरier stuff */
#समावेश <linux/init.h>		/* For __init/__निकास/... */
#समावेश <linux/fs.h>		/* For file operations */
#समावेश <linux/pci.h>		/* For pci functions */
#समावेश <linux/ioport.h>	/* For io-port access */
#समावेश <linux/spinlock.h>	/* For spin_lock/spin_unlock/... */
#समावेश <linux/uaccess.h>	/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>		/* For inb/outb/... */

/* Module and version inक्रमmation */
#घोषणा WATCHDOG_VERSION "1.03"
#घोषणा WATCHDOG_DRIVER_NAME "PCI-PC Watchdog"
#घोषणा WATCHDOG_NAME "pcwd_pci"
#घोषणा DRIVER_VERSION WATCHDOG_DRIVER_NAME " driver, v" WATCHDOG_VERSION

/* Stuff क्रम the PCI ID's  */
#अगर_अघोषित PCI_VENDOR_ID_QUICKLOGIC
#घोषणा PCI_VENDOR_ID_QUICKLOGIC    0x11e3
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_WATCHDOG_PCIPCWD
#घोषणा PCI_DEVICE_ID_WATCHDOG_PCIPCWD 0x5030
#पूर्ण_अगर

/*
 * These are the defines that describe the control status bits क्रम the
 * PCI-PC Watchकरोg card.
 */
/* Port 1 : Control Status #1 */
#घोषणा WD_PCI_WTRP		0x01	/* Watchकरोg Trip status */
#घोषणा WD_PCI_HRBT		0x02	/* Watchकरोg Heartbeat */
#घोषणा WD_PCI_TTRP		0x04	/* Temperature Trip status */
#घोषणा WD_PCI_RL2A		0x08	/* Relay 2 Active */
#घोषणा WD_PCI_RL1A		0x10	/* Relay 1 Active */
#घोषणा WD_PCI_R2DS		0x40	/* Relay 2 Disable Temperature-trip /
									reset */
#घोषणा WD_PCI_RLY2		0x80	/* Activate Relay 2 on the board */
/* Port 2 : Control Status #2 */
#घोषणा WD_PCI_WDIS		0x10	/* Watchकरोg Disable */
#घोषणा WD_PCI_ENTP		0x20	/* Enable Temperature Trip Reset */
#घोषणा WD_PCI_WRSP		0x40	/* Watchकरोg wrote response */
#घोषणा WD_PCI_PCMD		0x80	/* PC has sent command */

/* according to करोcumentation max. समय to process a command क्रम the pci
 * watchकरोg card is 100 ms, so we give it 150 ms to करो it's job */
#घोषणा PCI_COMMAND_TIMEOUT	150

/* Watchकरोg's पूर्णांकernal commands */
#घोषणा CMD_GET_STATUS				0x04
#घोषणा CMD_GET_FIRMWARE_VERSION		0x08
#घोषणा CMD_READ_WATCHDOG_TIMEOUT		0x18
#घोषणा CMD_WRITE_WATCHDOG_TIMEOUT		0x19
#घोषणा CMD_GET_CLEAR_RESET_COUNT		0x84

/* Watchकरोg's Dip Switch heartbeat values */
अटल स्थिर पूर्णांक heartbeat_tbl[] = अणु
	5,	/* OFF-OFF-OFF	=  5 Sec  */
	10,	/* OFF-OFF-ON	= 10 Sec  */
	30,	/* OFF-ON-OFF	= 30 Sec  */
	60,	/* OFF-ON-ON	=  1 Min  */
	300,	/* ON-OFF-OFF	=  5 Min  */
	600,	/* ON-OFF-ON	= 10 Min  */
	1800,	/* ON-ON-OFF	= 30 Min  */
	3600,	/* ON-ON-ON	=  1 hour */
पूर्ण;

/* We can only use 1 card due to the /dev/watchकरोg restriction */
अटल पूर्णांक cards_found;

/* पूर्णांकernal variables */
अटल पूर्णांक temp_panic;
अटल अचिन्हित दीर्घ is_active;
अटल अक्षर expect_release;
/* this is निजी data क्रम each PCI-PC watchकरोg card */
अटल काष्ठा अणु
	/* Wether or not the card has a temperature device */
	पूर्णांक supports_temp;
	/* The card's boot status */
	पूर्णांक boot_status;
	/* The cards I/O address */
	अचिन्हित दीर्घ io_addr;
	/* the lock क्रम io operations */
	spinlock_t io_lock;
	/* the PCI-device */
	काष्ठा pci_dev *pdev;
पूर्ण pcipcwd_निजी;

/* module parameters */
#घोषणा QUIET	0	/* Default */
#घोषणा VERBOSE	1	/* Verbose */
#घोषणा DEBUG	2	/* prपूर्णांक fancy stuff too */
अटल पूर्णांक debug = QUIET;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level: 0=Quiet, 1=Verbose, 2=Debug (default=0)");

#घोषणा WATCHDOG_HEARTBEAT 0	/* शेष heartbeat =
						delay-समय from dip-चयनes */
अटल पूर्णांक heartbeat = WATCHDOG_HEARTBEAT;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds. "
	"(0<heartbeat<65536 or 0=delay-time from dip-switches, default="
				__MODULE_STRING(WATCHDOG_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
					__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Internal functions
 */

अटल पूर्णांक send_command(पूर्णांक cmd, पूर्णांक *msb, पूर्णांक *lsb)
अणु
	पूर्णांक got_response, count;

	अगर (debug >= DEBUG)
		pr_debug("sending following data cmd=0x%02x msb=0x%02x lsb=0x%02x\n",
			 cmd, *msb, *lsb);

	spin_lock(&pcipcwd_निजी.io_lock);
	/* If a command requires data it should be written first.
	 * Data क्रम commands with 8 bits of data should be written to port 4.
	 * Commands with 16 bits of data, should be written as LSB to port 4
	 * and MSB to port 5.
	 * After the required data has been written then ग_लिखो the command to
	 * port 6. */
	outb_p(*lsb, pcipcwd_निजी.io_addr + 4);
	outb_p(*msb, pcipcwd_निजी.io_addr + 5);
	outb_p(cmd, pcipcwd_निजी.io_addr + 6);

	/* रुको till the pci card processed the command, संकेतed by
	 * the WRSP bit in port 2 and give it a max. समयout of
	 * PCI_COMMAND_TIMEOUT to process */
	got_response = inb_p(pcipcwd_निजी.io_addr + 2) & WD_PCI_WRSP;
	क्रम (count = 0; (count < PCI_COMMAND_TIMEOUT) && (!got_response);
								count++) अणु
		mdelay(1);
		got_response = inb_p(pcipcwd_निजी.io_addr + 2) & WD_PCI_WRSP;
	पूर्ण

	अगर (debug >= DEBUG) अणु
		अगर (got_response) अणु
			pr_debug("time to process command was: %d ms\n",
				 count);
		पूर्ण अन्यथा अणु
			pr_debug("card did not respond on command!\n");
		पूर्ण
	पूर्ण

	अगर (got_response) अणु
		/* पढ़ो back response */
		*lsb = inb_p(pcipcwd_निजी.io_addr + 4);
		*msb = inb_p(pcipcwd_निजी.io_addr + 5);

		/* clear WRSP bit */
		inb_p(pcipcwd_निजी.io_addr + 6);

		अगर (debug >= DEBUG)
			pr_debug("received following data for cmd=0x%02x: msb=0x%02x lsb=0x%02x\n",
				 cmd, *msb, *lsb);
	पूर्ण

	spin_unlock(&pcipcwd_निजी.io_lock);

	वापस got_response;
पूर्ण

अटल अंतरभूत व्योम pcipcwd_check_temperature_support(व्योम)
अणु
	अगर (inb_p(pcipcwd_निजी.io_addr) != 0xF0)
		pcipcwd_निजी.supports_temp = 1;
पूर्ण

अटल पूर्णांक pcipcwd_get_option_चयनes(व्योम)
अणु
	पूर्णांक option_चयनes;

	option_चयनes = inb_p(pcipcwd_निजी.io_addr + 3);
	वापस option_चयनes;
पूर्ण

अटल व्योम pcipcwd_show_card_info(व्योम)
अणु
	पूर्णांक got_fw_rev, fw_rev_major, fw_rev_minor;
	अक्षर fw_ver_str[20];		/* The cards firmware version */
	पूर्णांक option_चयनes;

	got_fw_rev = send_command(CMD_GET_FIRMWARE_VERSION, &fw_rev_major,
								&fw_rev_minor);
	अगर (got_fw_rev)
		प्र_लिखो(fw_ver_str, "%u.%02u", fw_rev_major, fw_rev_minor);
	अन्यथा
		प्र_लिखो(fw_ver_str, "<card no answer>");

	/* Get चयन settings */
	option_चयनes = pcipcwd_get_option_चयनes();

	pr_info("Found card at port 0x%04x (Firmware: %s) %s temp option\n",
		(पूर्णांक) pcipcwd_निजी.io_addr, fw_ver_str,
		(pcipcwd_निजी.supports_temp ? "with" : "without"));

	pr_info("Option switches (0x%02x): Temperature Reset Enable=%s, Power On Delay=%s\n",
		option_चयनes,
		((option_चयनes & 0x10) ? "ON" : "OFF"),
		((option_चयनes & 0x08) ? "ON" : "OFF"));

	अगर (pcipcwd_निजी.boot_status & WDIOF_CARDRESET)
		pr_info("Previous reset was caused by the Watchdog card\n");

	अगर (pcipcwd_निजी.boot_status & WDIOF_OVERHEAT)
		pr_info("Card sensed a CPU Overheat\n");

	अगर (pcipcwd_निजी.boot_status == 0)
		pr_info("No previous trip detected - Cold boot or reset\n");
पूर्ण

अटल पूर्णांक pcipcwd_start(व्योम)
अणु
	पूर्णांक stat_reg;

	spin_lock(&pcipcwd_निजी.io_lock);
	outb_p(0x00, pcipcwd_निजी.io_addr + 3);
	udelay(1000);

	stat_reg = inb_p(pcipcwd_निजी.io_addr + 2);
	spin_unlock(&pcipcwd_निजी.io_lock);

	अगर (stat_reg & WD_PCI_WDIS) अणु
		pr_err("Card timer not enabled\n");
		वापस -1;
	पूर्ण

	अगर (debug >= VERBOSE)
		pr_debug("Watchdog started\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_stop(व्योम)
अणु
	पूर्णांक stat_reg;

	spin_lock(&pcipcwd_निजी.io_lock);
	outb_p(0xA5, pcipcwd_निजी.io_addr + 3);
	udelay(1000);

	outb_p(0xA5, pcipcwd_निजी.io_addr + 3);
	udelay(1000);

	stat_reg = inb_p(pcipcwd_निजी.io_addr + 2);
	spin_unlock(&pcipcwd_निजी.io_lock);

	अगर (!(stat_reg & WD_PCI_WDIS)) अणु
		pr_err("Card did not acknowledge disable attempt\n");
		वापस -1;
	पूर्ण

	अगर (debug >= VERBOSE)
		pr_debug("Watchdog stopped\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_keepalive(व्योम)
अणु
	/* Re-trigger watchकरोg by writing to port 0 */
	spin_lock(&pcipcwd_निजी.io_lock);
	outb_p(0x42, pcipcwd_निजी.io_addr);	/* send out any data */
	spin_unlock(&pcipcwd_निजी.io_lock);

	अगर (debug >= DEBUG)
		pr_debug("Watchdog keepalive signal send\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_set_heartbeat(पूर्णांक t)
अणु
	पूर्णांक t_msb = t / 256;
	पूर्णांक t_lsb = t % 256;

	अगर ((t < 0x0001) || (t > 0xFFFF))
		वापस -EINVAL;

	/* Write new heartbeat to watchकरोg */
	send_command(CMD_WRITE_WATCHDOG_TIMEOUT, &t_msb, &t_lsb);

	heartbeat = t;
	अगर (debug >= VERBOSE)
		pr_debug("New heartbeat: %d\n", heartbeat);

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_get_status(पूर्णांक *status)
अणु
	पूर्णांक control_status;

	*status = 0;
	control_status = inb_p(pcipcwd_निजी.io_addr + 1);
	अगर (control_status & WD_PCI_WTRP)
		*status |= WDIOF_CARDRESET;
	अगर (control_status & WD_PCI_TTRP) अणु
		*status |= WDIOF_OVERHEAT;
		अगर (temp_panic)
			panic(KBUILD_MODNAME ": Temperature overheat trip!\n");
	पूर्ण

	अगर (debug >= DEBUG)
		pr_debug("Control Status #1: 0x%02x\n", control_status);

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_clear_status(व्योम)
अणु
	पूर्णांक control_status;
	पूर्णांक msb;
	पूर्णांक reset_counter;

	अगर (debug >= VERBOSE)
		pr_info("clearing watchdog trip status & LED\n");

	control_status = inb_p(pcipcwd_निजी.io_addr + 1);

	अगर (debug >= DEBUG) अणु
		pr_debug("status was: 0x%02x\n", control_status);
		pr_debug("sending: 0x%02x\n",
			 (control_status & WD_PCI_R2DS) | WD_PCI_WTRP);
	पूर्ण

	/* clear trip status & LED and keep mode of relay 2 */
	outb_p((control_status & WD_PCI_R2DS) | WD_PCI_WTRP,
						pcipcwd_निजी.io_addr + 1);

	/* clear reset counter */
	msb = 0;
	reset_counter = 0xff;
	send_command(CMD_GET_CLEAR_RESET_COUNT, &msb, &reset_counter);

	अगर (debug >= DEBUG) अणु
		pr_debug("reset count was: 0x%02x\n", reset_counter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_get_temperature(पूर्णांक *temperature)
अणु
	*temperature = 0;
	अगर (!pcipcwd_निजी.supports_temp)
		वापस -ENODEV;

	spin_lock(&pcipcwd_निजी.io_lock);
	*temperature = inb_p(pcipcwd_निजी.io_addr);
	spin_unlock(&pcipcwd_निजी.io_lock);

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' क्रम this वापस value.
	 */
	*temperature = (*temperature * 9 / 5) + 32;

	अगर (debug >= DEBUG) अणु
		pr_debug("temperature is: %d F\n", *temperature);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcipcwd_get_समयleft(पूर्णांक *समय_left)
अणु
	पूर्णांक msb;
	पूर्णांक lsb;

	/* Read the समय that's left beक्रमe rebooting */
	/* Note: अगर the board is not yet armed then we will पढ़ो 0xFFFF */
	send_command(CMD_READ_WATCHDOG_TIMEOUT, &msb, &lsb);

	*समय_left = (msb << 8) + lsb;

	अगर (debug >= VERBOSE)
		pr_debug("Time left before next reboot: %d\n", *समय_left);

	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार pcipcwd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			     माप_प्रकार len, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* note: just in हाल someone wrote the magic अक्षरacter
			 * five months ago... */
			expect_release = 0;

			/* scan to see whether or not we got the
			 * magic अक्षरacter */
			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_release = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should reload the समयr */
		pcipcwd_keepalive();
	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ pcipcwd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_OVERHEAT |
					WDIOF_CARDRESET |
					WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	1,
		.identity =		WATCHDOG_DRIVER_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	अणु
		पूर्णांक status;
		pcipcwd_get_status(&status);
		वापस put_user(status, p);
	पूर्ण

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(pcipcwd_निजी.boot_status, p);

	हाल WDIOC_GETTEMP:
	अणु
		पूर्णांक temperature;

		अगर (pcipcwd_get_temperature(&temperature))
			वापस -EFAULT;

		वापस put_user(temperature, p);
	पूर्ण

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक new_options, retval = -EINVAL;

		अगर (get_user(new_options, p))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD) अणु
			अगर (pcipcwd_stop())
				वापस -EIO;
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_ENABLECARD) अणु
			अगर (pcipcwd_start())
				वापस -EIO;
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_TEMPPANIC) अणु
			temp_panic = 1;
			retval = 0;
		पूर्ण

		वापस retval;
	पूर्ण

	हाल WDIOC_KEEPALIVE:
		pcipcwd_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
	अणु
		पूर्णांक new_heartbeat;

		अगर (get_user(new_heartbeat, p))
			वापस -EFAULT;

		अगर (pcipcwd_set_heartbeat(new_heartbeat))
			वापस -EINVAL;

		pcipcwd_keepalive();
	पूर्ण
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);

	हाल WDIOC_GETTIMELEFT:
	अणु
		पूर्णांक समय_left;

		अगर (pcipcwd_get_समयleft(&समय_left))
			वापस -EFAULT;

		वापस put_user(समय_left, p);
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक pcipcwd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &is_active)) अणु
		अगर (debug >= VERBOSE)
			pr_err("Attempt to open already opened device\n");
		वापस -EBUSY;
	पूर्ण

	/* Activate */
	pcipcwd_start();
	pcipcwd_keepalive();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक pcipcwd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 *      Shut off the समयr.
	 */
	अगर (expect_release == 42) अणु
		pcipcwd_stop();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		pcipcwd_keepalive();
	पूर्ण
	expect_release = 0;
	clear_bit(0, &is_active);
	वापस 0;
पूर्ण

/*
 *	/dev/temperature handling
 */

अटल sमाप_प्रकार pcipcwd_temp_पढ़ो(काष्ठा file *file, अक्षर __user *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	पूर्णांक temperature;

	अगर (pcipcwd_get_temperature(&temperature))
		वापस -EFAULT;

	अगर (copy_to_user(data, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

अटल पूर्णांक pcipcwd_temp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!pcipcwd_निजी.supports_temp)
		वापस -ENODEV;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक pcipcwd_temp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 *	Notअगरy प्रणाली
 */

अटल पूर्णांक pcipcwd_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
								व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		pcipcwd_stop();	/* Turn the WDT off */

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations pcipcwd_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.ग_लिखो =	pcipcwd_ग_लिखो,
	.unlocked_ioctl = pcipcwd_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो =		pcipcwd_खोलो,
	.release =	pcipcwd_release,
पूर्ण;

अटल काष्ठा miscdevice pcipcwd_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&pcipcwd_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations pcipcwd_temp_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.पढ़ो =		pcipcwd_temp_पढ़ो,
	.खोलो =		pcipcwd_temp_खोलो,
	.release =	pcipcwd_temp_release,
पूर्ण;

अटल काष्ठा miscdevice pcipcwd_temp_miscdev = अणु
	.minor =	TEMP_MINOR,
	.name =		"temperature",
	.fops =		&pcipcwd_temp_fops,
पूर्ण;

अटल काष्ठा notअगरier_block pcipcwd_notअगरier = अणु
	.notअगरier_call =	pcipcwd_notअगरy_sys,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक pcipcwd_card_init(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret = -EIO;

	cards_found++;
	अगर (cards_found == 1)
		pr_info("%s\n", DRIVER_VERSION);

	अगर (cards_found > 1) अणु
		pr_err("This driver only supports 1 device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_enable_device(pdev)) अणु
		pr_err("Not possible to enable PCI Device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_resource_start(pdev, 0) == 0x0000) अणु
		pr_err("No I/O-Address for card detected\n");
		ret = -ENODEV;
		जाओ err_out_disable_device;
	पूर्ण

	spin_lock_init(&pcipcwd_निजी.io_lock);
	pcipcwd_निजी.pdev = pdev;
	pcipcwd_निजी.io_addr = pci_resource_start(pdev, 0);

	अगर (pci_request_regions(pdev, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n",
		       (पूर्णांक) pcipcwd_निजी.io_addr);
		ret = -EIO;
		जाओ err_out_disable_device;
	पूर्ण

	/* get the boot_status */
	pcipcwd_get_status(&pcipcwd_निजी.boot_status);

	/* clear the "card caused reboot" flag */
	pcipcwd_clear_status();

	/* disable card */
	pcipcwd_stop();

	/* Check whether or not the card supports the temperature device */
	pcipcwd_check_temperature_support();

	/* Show info about the card itself */
	pcipcwd_show_card_info();

	/* If heartbeat = 0 then we use the heartbeat from the dip-चयनes */
	अगर (heartbeat == 0)
		heartbeat =
			heartbeat_tbl[(pcipcwd_get_option_चयनes() & 0x07)];

	/* Check that the heartbeat value is within it's range ;
	 * अगर not reset to the शेष */
	अगर (pcipcwd_set_heartbeat(heartbeat)) अणु
		pcipcwd_set_heartbeat(WATCHDOG_HEARTBEAT);
		pr_info("heartbeat value must be 0<heartbeat<65536, using %d\n",
			WATCHDOG_HEARTBEAT);
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&pcipcwd_notअगरier);
	अगर (ret != 0) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ err_out_release_region;
	पूर्ण

	अगर (pcipcwd_निजी.supports_temp) अणु
		ret = misc_रेजिस्टर(&pcipcwd_temp_miscdev);
		अगर (ret != 0) अणु
			pr_err("cannot register miscdev on minor=%d (err=%d)\n",
			       TEMP_MINOR, ret);
			जाओ err_out_unरेजिस्टर_reboot;
		पूर्ण
	पूर्ण

	ret = misc_रेजिस्टर(&pcipcwd_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ err_out_misc_deरेजिस्टर;
	पूर्ण

	pr_info("initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);

	वापस 0;

err_out_misc_deरेजिस्टर:
	अगर (pcipcwd_निजी.supports_temp)
		misc_deरेजिस्टर(&pcipcwd_temp_miscdev);
err_out_unरेजिस्टर_reboot:
	unरेजिस्टर_reboot_notअगरier(&pcipcwd_notअगरier);
err_out_release_region:
	pci_release_regions(pdev);
err_out_disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम pcipcwd_card_निकास(काष्ठा pci_dev *pdev)
अणु
	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout)
		pcipcwd_stop();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&pcipcwd_miscdev);
	अगर (pcipcwd_निजी.supports_temp)
		misc_deरेजिस्टर(&pcipcwd_temp_miscdev);
	unरेजिस्टर_reboot_notअगरier(&pcipcwd_notअगरier);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	cards_found--;
पूर्ण

अटल स्थिर काष्ठा pci_device_id pcipcwd_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_QUICKLOGIC, PCI_DEVICE_ID_WATCHDOG_PCIPCWD,
		PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0 पूर्ण,			/* End of list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pcipcwd_pci_tbl);

अटल काष्ठा pci_driver pcipcwd_driver = अणु
	.name		= WATCHDOG_NAME,
	.id_table	= pcipcwd_pci_tbl,
	.probe		= pcipcwd_card_init,
	.हटाओ		= pcipcwd_card_निकास,
पूर्ण;

module_pci_driver(pcipcwd_driver);

MODULE_AUTHOR("Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("Berkshire PCI-PC Watchdog driver");
MODULE_LICENSE("GPL");
