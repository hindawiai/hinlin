<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PC Watchकरोg Driver
 * by Ken Hollis (khollis@bitgate.com)
 *
 * Permission granted from Simon Machell (smachell@berkprod.com)
 * Written क्रम the Linux Kernel, and GPLed by Ken Hollis
 *
 * 960107	Added request_region routines, modulized the whole thing.
 * 960108	Fixed end-of-file poपूर्णांकer (Thanks to Dan Hollis), added
 *		WD_TIMEOUT define.
 * 960216	Added eof marker on the file, and changed verbose messages.
 * 960716	Made functional and cosmetic changes to the source क्रम
 *		inclusion in Linux 2.0.x kernels, thanks to Alan Cox.
 * 960717	Removed पढ़ो/seek routines, replaced with ioctl.  Also, added
 *		check_region command due to Alan's suggestion.
 * 960821	Made changes to compile in newer 2.0.x kernels.  Added
 *		"cold reboot sense" entry.
 * 960825	Made a few changes to code, deleted some defines and made
 *		प्रकारs to replace them.  Made heartbeat reset only available
 *		via ioctl, and हटाओd the ग_लिखो routine.
 * 960828	Added new items क्रम PC Watchकरोg Rev.C card.
 * 960829	Changed around all of the IOCTLs, added new features,
 *		added watchकरोg disable/re-enable routines.  Added firmware
 *		version reporting.  Added पढ़ो routine क्रम temperature.
 *		Removed some extra defines, added an स्वतःdetect Revision
 *		routine.
 * 961006	Revised some करोcumentation, fixed some cosmetic bugs.  Made
 *		drivers to panic the प्रणाली अगर it's overheating at bootup.
 * 961118	Changed some verbiage on some of the output, tidied up
 *		code bits, and added compatibility to 2.1.x.
 * 970912	Enabled board on खोलो and disable on बंद.
 * 971107	Took account of recent VFS changes (broke पढ़ो).
 * 971210	Disable board on initialisation in हाल board alपढ़ोy ticking.
 * 971222	Changed खोलो/बंद क्रम temperature handling
 *		Michael Meskes <meskes@debian.org>.
 * 980112	Used minor numbers from include/linux/miscdevice.h
 * 990403	Clear reset status after पढ़ोing control status रेजिस्टर in
 *		pcwd_showprevstate(). [Marc Boucher <marc@mbsi.ca>]
 * 990605	Made changes to code to support Firmware 1.22a, added
 *		fairly useless proc entry.
 * 990610	हटाओd said useless proc code क्रम the merge <alan>
 * 000403	Removed last traces of proc code. <davej>
 * 011214	Added nowayout module option to override
 *		CONFIG_WATCHDOG_NOWAYOUT <Matt_Domsch@dell.com>
 *		Added समयout module option to override शेष
 */

/*
 *	A bells and whistles driver is available from http://www.pcwd.de/
 *	More info available at http://www.berkprod.com/ or
 *	http://www.pcwatchकरोg.com/
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>	/* For module specअगरic items */
#समावेश <linux/moduleparam.h>	/* For new moduleparam's */
#समावेश <linux/types.h>	/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>	/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>	/* For prपूर्णांकk/panic/... */
#समावेश <linux/delay.h>	/* For mdelay function */
#समावेश <linux/समयr.h>	/* For समयr related operations */
#समावेश <linux/jअगरfies.h>	/* For jअगरfies stuff */
#समावेश <linux/miscdevice.h>	/* For काष्ठा miscdevice */
#समावेश <linux/watchकरोg.h>	/* For the watchकरोg specअगरic items */
#समावेश <linux/reboot.h>	/* For kernel_घातer_off() */
#समावेश <linux/init.h>		/* For __init/__निकास/... */
#समावेश <linux/fs.h>		/* For file operations */
#समावेश <linux/isa.h>		/* For isa devices */
#समावेश <linux/ioport.h>	/* For io-port access */
#समावेश <linux/spinlock.h>	/* For spin_lock/spin_unlock/... */
#समावेश <linux/uaccess.h>	/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>		/* For inb/outb/... */

/* Module and version inक्रमmation */
#घोषणा WATCHDOG_VERSION "1.20"
#घोषणा WATCHDOG_DATE "18 Feb 2007"
#घोषणा WATCHDOG_DRIVER_NAME "ISA-PC Watchdog"
#घोषणा WATCHDOG_NAME "pcwd"
#घोषणा DRIVER_VERSION WATCHDOG_DRIVER_NAME " driver, v" WATCHDOG_VERSION "\n"

/*
 * It should be noted that PCWD_REVISION_B was हटाओd because A and B
 * are essentially the same types of card, with the exception that B
 * has temperature reporting.  Since I didn't receive a Rev.B card,
 * the Rev.B card is not supported.  (It's a good thing too, as they
 * are no दीर्घer in production.)
 */
#घोषणा	PCWD_REVISION_A		1
#घोषणा	PCWD_REVISION_C		2

/*
 * These are the स्वतः-probe addresses available.
 *
 * Revision A only uses ports 0x270 and 0x370.  Revision C पूर्णांकroduced 0x350.
 * Revision A has an address range of 2 addresses, जबतक Revision C has 4.
 */
#घोषणा PCWD_ISA_NR_CARDS	3
अटल पूर्णांक pcwd_ioports[] = अणु 0x270, 0x350, 0x370, 0x000 पूर्ण;

/*
 * These are the defines that describe the control status bits क्रम the
 * PCI-PC Watchकरोg card.
*/
/* Port 1 : Control Status #1 क्रम the PC Watchकरोg card, revision A. */
#घोषणा WD_WDRST		0x01	/* Previously reset state */
#घोषणा WD_T110			0x02	/* Temperature overheat sense */
#घोषणा WD_HRTBT		0x04	/* Heartbeat sense */
#घोषणा WD_RLY2			0x08	/* External relay triggered */
#घोषणा WD_SRLY2		0x80	/* Software बाह्यal relay triggered */
/* Port 1 : Control Status #1 क्रम the PC Watchकरोg card, revision C. */
#घोषणा WD_REVC_WTRP		0x01	/* Watchकरोg Trip status */
#घोषणा WD_REVC_HRBT		0x02	/* Watchकरोg Heartbeat */
#घोषणा WD_REVC_TTRP		0x04	/* Temperature Trip status */
#घोषणा WD_REVC_RL2A		0x08	/* Relay 2 activated by
							on-board processor */
#घोषणा WD_REVC_RL1A		0x10	/* Relay 1 active */
#घोषणा WD_REVC_R2DS		0x40	/* Relay 2 disable */
#घोषणा WD_REVC_RLY2		0x80	/* Relay 2 activated? */
/* Port 2 : Control Status #2 */
#घोषणा WD_WDIS			0x10	/* Watchकरोg Disabled */
#घोषणा WD_ENTP			0x20	/* Watchकरोg Enable Temperature Trip */
#घोषणा WD_SSEL			0x40	/* Watchकरोg Switch Select
							(1:SW1 <-> 0:SW2) */
#घोषणा WD_WCMD			0x80	/* Watchकरोg Command Mode */

/* max. समय we give an ISA watchकरोg card to process a command */
/* 500ms क्रम each 4 bit response (according to spec.) */
#घोषणा ISA_COMMAND_TIMEOUT     1000

/* Watchकरोg's पूर्णांकernal commands */
#घोषणा CMD_ISA_IDLE			0x00
#घोषणा CMD_ISA_VERSION_INTEGER		0x01
#घोषणा CMD_ISA_VERSION_TENTH		0x02
#घोषणा CMD_ISA_VERSION_HUNDRETH	0x03
#घोषणा CMD_ISA_VERSION_MINOR		0x04
#घोषणा CMD_ISA_SWITCH_SETTINGS		0x05
#घोषणा CMD_ISA_RESET_PC		0x06
#घोषणा CMD_ISA_ARM_0			0x07
#घोषणा CMD_ISA_ARM_30			0x08
#घोषणा CMD_ISA_ARM_60			0x09
#घोषणा CMD_ISA_DELAY_TIME_2SECS	0x0A
#घोषणा CMD_ISA_DELAY_TIME_4SECS	0x0B
#घोषणा CMD_ISA_DELAY_TIME_8SECS	0x0C
#घोषणा CMD_ISA_RESET_RELAYS		0x0D

/* Watchकरोg's Dip Switch heartbeat values */
अटल स्थिर पूर्णांक heartbeat_tbl[] = अणु
	20,	/* OFF-OFF-OFF	= 20 Sec  */
	40,	/* OFF-OFF-ON	= 40 Sec  */
	60,	/* OFF-ON-OFF	=  1 Min  */
	300,	/* OFF-ON-ON	=  5 Min  */
	600,	/* ON-OFF-OFF	= 10 Min  */
	1800,	/* ON-OFF-ON	= 30 Min  */
	3600,	/* ON-ON-OFF	=  1 Hour */
	7200,	/* ON-ON-ON	=  2 hour */
पूर्ण;

/*
 * We are using an kernel समयr to करो the pinging of the watchकरोg
 * every ~500ms. We try to set the पूर्णांकernal heartbeat of the
 * watchकरोg to 2 ms.
 */

#घोषणा WDT_INTERVAL (HZ/2+1)

/* We can only use 1 card due to the /dev/watchकरोg restriction */
अटल पूर्णांक cards_found;

/* पूर्णांकernal variables */
अटल अचिन्हित दीर्घ खोलो_allowed;
अटल अक्षर expect_बंद;
अटल पूर्णांक temp_panic;

/* this is निजी data क्रम each ISA-PC watchकरोg card */
अटल काष्ठा अणु
	अक्षर fw_ver_str[6];		/* The cards firmware version */
	पूर्णांक revision;			/* The card's revision */
	पूर्णांक supports_temp;		/* Whether or not the card has
						a temperature device */
	पूर्णांक command_mode;		/* Whether or not the card is in
						command mode */
	पूर्णांक boot_status;		/* The card's boot status */
	पूर्णांक io_addr;			/* The cards I/O address */
	spinlock_t io_lock;		/* the lock क्रम io operations */
	काष्ठा समयr_list समयr;	/* The समयr that pings the watchकरोg */
	अचिन्हित दीर्घ next_heartbeat;	/* the next_heartbeat क्रम the समयr */
पूर्ण pcwd_निजी;

/* module parameters */
#घोषणा QUIET	0	/* Default */
#घोषणा VERBOSE	1	/* Verbose */
#घोषणा DEBUG	2	/* prपूर्णांक fancy stuff too */
अटल पूर्णांक debug = QUIET;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug,
		"Debug level: 0=Quiet, 1=Verbose, 2=Debug (default=0)");

/* शेष heartbeat = delay-समय from dip-चयनes */
#घोषणा WATCHDOG_HEARTBEAT 0
अटल पूर्णांक heartbeat = WATCHDOG_HEARTBEAT;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds. "
	"(2 <= heartbeat <= 7200 or 0=delay-time from dip-switches, default="
				__MODULE_STRING(WATCHDOG_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Internal functions
 */

अटल पूर्णांक send_isa_command(पूर्णांक cmd)
अणु
	पूर्णांक i;
	पूर्णांक control_status;
	पूर्णांक port0, last_port0;	/* Double पढ़ो क्रम stabilising */

	अगर (debug >= DEBUG)
		pr_debug("sending following data cmd=0x%02x\n", cmd);

	/* The WCMD bit must be 1 and the command is only 4 bits in size */
	control_status = (cmd & 0x0F) | WD_WCMD;
	outb_p(control_status, pcwd_निजी.io_addr + 2);
	udelay(ISA_COMMAND_TIMEOUT);

	port0 = inb_p(pcwd_निजी.io_addr);
	क्रम (i = 0; i < 25; ++i) अणु
		last_port0 = port0;
		port0 = inb_p(pcwd_निजी.io_addr);

		अगर (port0 == last_port0)
			अवरोध;	/* Data is stable */

		udelay(250);
	पूर्ण

	अगर (debug >= DEBUG)
		pr_debug("received following data for cmd=0x%02x: port0=0x%02x last_port0=0x%02x\n",
			 cmd, port0, last_port0);

	वापस port0;
पूर्ण

अटल पूर्णांक set_command_mode(व्योम)
अणु
	पूर्णांक i, found = 0, count = 0;

	/* Set the card पूर्णांकo command mode */
	spin_lock(&pcwd_निजी.io_lock);
	जबतक ((!found) && (count < 3)) अणु
		i = send_isa_command(CMD_ISA_IDLE);

		अगर (i == 0x00)
			found = 1;
		अन्यथा अगर (i == 0xF3) अणु
			/* Card करोes not like what we've करोne to it */
			outb_p(0x00, pcwd_निजी.io_addr + 2);
			udelay(1200);	/* Spec says रुको 1ms */
			outb_p(0x00, pcwd_निजी.io_addr + 2);
			udelay(ISA_COMMAND_TIMEOUT);
		पूर्ण
		count++;
	पूर्ण
	spin_unlock(&pcwd_निजी.io_lock);
	pcwd_निजी.command_mode = found;

	अगर (debug >= DEBUG)
		pr_debug("command_mode=%d\n", pcwd_निजी.command_mode);

	वापस found;
पूर्ण

अटल व्योम unset_command_mode(व्योम)
अणु
	/* Set the card पूर्णांकo normal mode */
	spin_lock(&pcwd_निजी.io_lock);
	outb_p(0x00, pcwd_निजी.io_addr + 2);
	udelay(ISA_COMMAND_TIMEOUT);
	spin_unlock(&pcwd_निजी.io_lock);

	pcwd_निजी.command_mode = 0;

	अगर (debug >= DEBUG)
		pr_debug("command_mode=%d\n", pcwd_निजी.command_mode);
पूर्ण

अटल अंतरभूत व्योम pcwd_check_temperature_support(व्योम)
अणु
	अगर (inb(pcwd_निजी.io_addr) != 0xF0)
		pcwd_निजी.supports_temp = 1;
पूर्ण

अटल अंतरभूत व्योम pcwd_get_firmware(व्योम)
अणु
	पूर्णांक one, ten, hund, minor;

	म_नकल(pcwd_निजी.fw_ver_str, "ERROR");

	अगर (set_command_mode()) अणु
		one = send_isa_command(CMD_ISA_VERSION_INTEGER);
		ten = send_isa_command(CMD_ISA_VERSION_TENTH);
		hund = send_isa_command(CMD_ISA_VERSION_HUNDRETH);
		minor = send_isa_command(CMD_ISA_VERSION_MINOR);
		प्र_लिखो(pcwd_निजी.fw_ver_str, "%c.%c%c%c",
					one, ten, hund, minor);
	पूर्ण
	unset_command_mode();

	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक pcwd_get_option_चयनes(व्योम)
अणु
	पूर्णांक option_चयनes = 0;

	अगर (set_command_mode()) अणु
		/* Get चयन settings */
		option_चयनes = send_isa_command(CMD_ISA_SWITCH_SETTINGS);
	पूर्ण

	unset_command_mode();
	वापस option_चयनes;
पूर्ण

अटल व्योम pcwd_show_card_info(व्योम)
अणु
	पूर्णांक option_चयनes;

	/* Get some extra info from the hardware (in command/debug/diag mode) */
	अगर (pcwd_निजी.revision == PCWD_REVISION_A)
		pr_info("ISA-PC Watchdog (REV.A) detected at port 0x%04x\n",
			pcwd_निजी.io_addr);
	अन्यथा अगर (pcwd_निजी.revision == PCWD_REVISION_C) अणु
		pcwd_get_firmware();
		pr_info("ISA-PC Watchdog (REV.C) detected at port 0x%04x (Firmware version: %s)\n",
			pcwd_निजी.io_addr, pcwd_निजी.fw_ver_str);
		option_चयनes = pcwd_get_option_चयनes();
		pr_info("Option switches (0x%02x): Temperature Reset Enable=%s, Power On Delay=%s\n",
			option_चयनes,
			((option_चयनes & 0x10) ? "ON" : "OFF"),
			((option_चयनes & 0x08) ? "ON" : "OFF"));

		/* Reprogram पूर्णांकernal heartbeat to 2 seconds */
		अगर (set_command_mode()) अणु
			send_isa_command(CMD_ISA_DELAY_TIME_2SECS);
			unset_command_mode();
		पूर्ण
	पूर्ण

	अगर (pcwd_निजी.supports_temp)
		pr_info("Temperature Option Detected\n");

	अगर (pcwd_निजी.boot_status & WDIOF_CARDRESET)
		pr_info("Previous reboot was caused by the card\n");

	अगर (pcwd_निजी.boot_status & WDIOF_OVERHEAT) अणु
		pr_emerg("Card senses a CPU Overheat. Panicking!\n");
		pr_emerg("CPU Overheat\n");
	पूर्ण

	अगर (pcwd_निजी.boot_status == 0)
		pr_info("No previous trip detected - Cold boot or reset\n");
पूर्ण

अटल व्योम pcwd_समयr_ping(काष्ठा समयr_list *unused)
अणु
	पूर्णांक wdrst_stat;

	/* If we got a heartbeat pulse within the WDT_INTERVAL
	 * we agree to ping the WDT */
	अगर (समय_beक्रमe(jअगरfies, pcwd_निजी.next_heartbeat)) अणु
		/* Ping the watchकरोg */
		spin_lock(&pcwd_निजी.io_lock);
		अगर (pcwd_निजी.revision == PCWD_REVISION_A) अणु
			/*  Rev A cards are reset by setting the
			    WD_WDRST bit in रेजिस्टर 1 */
			wdrst_stat = inb_p(pcwd_निजी.io_addr);
			wdrst_stat &= 0x0F;
			wdrst_stat |= WD_WDRST;

			outb_p(wdrst_stat, pcwd_निजी.io_addr + 1);
		पूर्ण अन्यथा अणु
			/* Re-trigger watchकरोg by writing to port 0 */
			outb_p(0x00, pcwd_निजी.io_addr);
		पूर्ण

		/* Re-set the समयr पूर्णांकerval */
		mod_समयr(&pcwd_निजी.समयr, jअगरfies + WDT_INTERVAL);

		spin_unlock(&pcwd_निजी.io_lock);
	पूर्ण अन्यथा अणु
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
	पूर्ण
पूर्ण

अटल पूर्णांक pcwd_start(व्योम)
अणु
	पूर्णांक stat_reg;

	pcwd_निजी.next_heartbeat = jअगरfies + (heartbeat * HZ);

	/* Start the समयr */
	mod_समयr(&pcwd_निजी.समयr, jअगरfies + WDT_INTERVAL);

	/* Enable the port */
	अगर (pcwd_निजी.revision == PCWD_REVISION_C) अणु
		spin_lock(&pcwd_निजी.io_lock);
		outb_p(0x00, pcwd_निजी.io_addr + 3);
		udelay(ISA_COMMAND_TIMEOUT);
		stat_reg = inb_p(pcwd_निजी.io_addr + 2);
		spin_unlock(&pcwd_निजी.io_lock);
		अगर (stat_reg & WD_WDIS) अणु
			pr_info("Could not start watchdog\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (debug >= VERBOSE)
		pr_debug("Watchdog started\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_stop(व्योम)
अणु
	पूर्णांक stat_reg;

	/* Stop the समयr */
	del_समयr(&pcwd_निजी.समयr);

	/*  Disable the board  */
	अगर (pcwd_निजी.revision == PCWD_REVISION_C) अणु
		spin_lock(&pcwd_निजी.io_lock);
		outb_p(0xA5, pcwd_निजी.io_addr + 3);
		udelay(ISA_COMMAND_TIMEOUT);
		outb_p(0xA5, pcwd_निजी.io_addr + 3);
		udelay(ISA_COMMAND_TIMEOUT);
		stat_reg = inb_p(pcwd_निजी.io_addr + 2);
		spin_unlock(&pcwd_निजी.io_lock);
		अगर ((stat_reg & WD_WDIS) == 0) अणु
			pr_info("Could not stop watchdog\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (debug >= VERBOSE)
		pr_debug("Watchdog stopped\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_keepalive(व्योम)
अणु
	/* user land ping */
	pcwd_निजी.next_heartbeat = jअगरfies + (heartbeat * HZ);

	अगर (debug >= DEBUG)
		pr_debug("Watchdog keepalive signal send\n");

	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_set_heartbeat(पूर्णांक t)
अणु
	अगर (t < 2 || t > 7200) /* arbitrary upper limit */
		वापस -EINVAL;

	heartbeat = t;

	अगर (debug >= VERBOSE)
		pr_debug("New heartbeat: %d\n", heartbeat);

	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_get_status(पूर्णांक *status)
अणु
	पूर्णांक control_status;

	*status = 0;
	spin_lock(&pcwd_निजी.io_lock);
	अगर (pcwd_निजी.revision == PCWD_REVISION_A)
		/* Rev A cards वापस status inक्रमmation from
		 * the base रेजिस्टर, which is used क्रम the
		 * temperature in other cards. */
		control_status = inb(pcwd_निजी.io_addr);
	अन्यथा अणु
		/* Rev C cards वापस card status in the base
		 * address + 1 रेजिस्टर. And use dअगरferent bits
		 * to indicate a card initiated reset, and an
		 * over-temperature condition. And the reboot
		 * status can be reset. */
		control_status = inb(pcwd_निजी.io_addr + 1);
	पूर्ण
	spin_unlock(&pcwd_निजी.io_lock);

	अगर (pcwd_निजी.revision == PCWD_REVISION_A) अणु
		अगर (control_status & WD_WDRST)
			*status |= WDIOF_CARDRESET;

		अगर (control_status & WD_T110) अणु
			*status |= WDIOF_OVERHEAT;
			अगर (temp_panic) अणु
				pr_info("Temperature overheat trip!\n");
				kernel_घातer_off();
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (control_status & WD_REVC_WTRP)
			*status |= WDIOF_CARDRESET;

		अगर (control_status & WD_REVC_TTRP) अणु
			*status |= WDIOF_OVERHEAT;
			अगर (temp_panic) अणु
				pr_info("Temperature overheat trip!\n");
				kernel_घातer_off();
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_clear_status(व्योम)
अणु
	पूर्णांक control_status;

	अगर (pcwd_निजी.revision == PCWD_REVISION_C) अणु
		spin_lock(&pcwd_निजी.io_lock);

		अगर (debug >= VERBOSE)
			pr_info("clearing watchdog trip status\n");

		control_status = inb_p(pcwd_निजी.io_addr + 1);

		अगर (debug >= DEBUG) अणु
			pr_debug("status was: 0x%02x\n", control_status);
			pr_debug("sending: 0x%02x\n",
				 (control_status & WD_REVC_R2DS));
		पूर्ण

		/* clear reset status & Keep Relay 2 disable state as it is */
		outb_p((control_status & WD_REVC_R2DS),
						pcwd_निजी.io_addr + 1);

		spin_unlock(&pcwd_निजी.io_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcwd_get_temperature(पूर्णांक *temperature)
अणु
	/* check that port 0 gives temperature info and no command results */
	अगर (pcwd_निजी.command_mode)
		वापस -1;

	*temperature = 0;
	अगर (!pcwd_निजी.supports_temp)
		वापस -ENODEV;

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' क्रम this वापस value.
	 */
	spin_lock(&pcwd_निजी.io_lock);
	*temperature = ((inb(pcwd_निजी.io_addr)) * 9 / 5) + 32;
	spin_unlock(&pcwd_निजी.io_lock);

	अगर (debug >= DEBUG) अणु
		pr_debug("temperature is: %d F\n", *temperature);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल दीर्घ pcwd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rv;
	पूर्णांक status;
	पूर्णांक temperature;
	पूर्णांक new_heartbeat;
	पूर्णांक __user *argp = (पूर्णांक __user *)arg;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_OVERHEAT |
					WDIOF_CARDRESET |
					WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	1,
		.identity =		"PCWD",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;

	हाल WDIOC_GETSTATUS:
		pcwd_get_status(&status);
		वापस put_user(status, argp);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(pcwd_निजी.boot_status, argp);

	हाल WDIOC_GETTEMP:
		अगर (pcwd_get_temperature(&temperature))
			वापस -EFAULT;

		वापस put_user(temperature, argp);

	हाल WDIOC_SETOPTIONS:
		अगर (pcwd_निजी.revision == PCWD_REVISION_C) अणु
			अगर (get_user(rv, argp))
				वापस -EFAULT;

			अगर (rv & WDIOS_DISABLECARD) अणु
				status = pcwd_stop();
				अगर (status < 0)
					वापस status;
			पूर्ण
			अगर (rv & WDIOS_ENABLECARD) अणु
				status = pcwd_start();
				अगर (status < 0)
					वापस status;
			पूर्ण
			अगर (rv & WDIOS_TEMPPANIC)
				temp_panic = 1;
		पूर्ण
		वापस -EINVAL;

	हाल WDIOC_KEEPALIVE:
		pcwd_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_heartbeat, argp))
			वापस -EFAULT;

		अगर (pcwd_set_heartbeat(new_heartbeat))
			वापस -EINVAL;

		pcwd_keepalive();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, argp);

	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pcwd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार len,
			  loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		pcwd_keepalive();
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक pcwd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &खोलो_allowed))
		वापस -EBUSY;
	अगर (nowayout)
		__module_get(THIS_MODULE);
	/* Activate */
	pcwd_start();
	pcwd_keepalive();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक pcwd_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		pcwd_stop();
	अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		pcwd_keepalive();
	पूर्ण
	expect_बंद = 0;
	clear_bit(0, &खोलो_allowed);
	वापस 0;
पूर्ण

/*
 *	/dev/temperature handling
 */

अटल sमाप_प्रकार pcwd_temp_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			 loff_t *ppos)
अणु
	पूर्णांक temperature;

	अगर (pcwd_get_temperature(&temperature))
		वापस -EFAULT;

	अगर (copy_to_user(buf, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

अटल पूर्णांक pcwd_temp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!pcwd_निजी.supports_temp)
		वापस -ENODEV;

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक pcwd_temp_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations pcwd_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= pcwd_ग_लिखो,
	.unlocked_ioctl	= pcwd_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= pcwd_खोलो,
	.release	= pcwd_बंद,
पूर्ण;

अटल काष्ठा miscdevice pcwd_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&pcwd_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations pcwd_temp_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= pcwd_temp_पढ़ो,
	.खोलो		= pcwd_temp_खोलो,
	.release	= pcwd_temp_बंद,
पूर्ण;

अटल काष्ठा miscdevice temp_miscdev = अणु
	.minor =	TEMP_MINOR,
	.name =		"temperature",
	.fops =		&pcwd_temp_fops,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल अंतरभूत पूर्णांक get_revision(व्योम)
अणु
	पूर्णांक r = PCWD_REVISION_C;

	spin_lock(&pcwd_निजी.io_lock);
	/* REV A cards use only 2 io ports; test
	 * presumes a भग्नing bus पढ़ोs as 0xff. */
	अगर ((inb(pcwd_निजी.io_addr + 2) == 0xFF) ||
	    (inb(pcwd_निजी.io_addr + 3) == 0xFF))
		r = PCWD_REVISION_A;
	spin_unlock(&pcwd_निजी.io_lock);

	वापस r;
पूर्ण

/*
 *  The ISA cards have a heartbeat bit in one of the रेजिस्टरs, which
 *  रेजिस्टर is card dependent.  The heartbeat bit is monitored, and अगर
 *  found, is considered proof that a Berkshire card has been found.
 *  The initial rate is once per second at board start up, then twice
 *  per second क्रम normal operation.
 */
अटल पूर्णांक pcwd_isa_match(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक base_addr = pcwd_ioports[id];
	पूर्णांक port0, last_port0;	/* Reg 0, in हाल it's REV A */
	पूर्णांक port1, last_port1;	/* Register 1 क्रम REV C cards */
	पूर्णांक i;
	पूर्णांक retval;

	अगर (debug >= DEBUG)
		pr_debug("pcwd_isa_match id=%d\n", id);

	अगर (!request_region(base_addr, 4, "PCWD")) अणु
		pr_info("Port 0x%04x unavailable\n", base_addr);
		वापस 0;
	पूर्ण

	retval = 0;

	port0 = inb_p(base_addr);	/* For REV A boards */
	port1 = inb_p(base_addr + 1);	/* For REV C boards */
	अगर (port0 != 0xff || port1 != 0xff) अणु
		/* Not an 'ff' from a भग्नing bus, so must be a card! */
		क्रम (i = 0; i < 4; ++i) अणु

			msleep(500);

			last_port0 = port0;
			last_port1 = port1;

			port0 = inb_p(base_addr);
			port1 = inb_p(base_addr + 1);

			/* Has either hearbeat bit changed?  */
			अगर ((port0 ^ last_port0) & WD_HRTBT ||
			    (port1 ^ last_port1) & WD_REVC_HRBT) अणु
				retval = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	release_region(base_addr, 4);

	वापस retval;
पूर्ण

अटल पूर्णांक pcwd_isa_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक ret;

	अगर (debug >= DEBUG)
		pr_debug("pcwd_isa_probe id=%d\n", id);

	cards_found++;
	अगर (cards_found == 1)
		pr_info("v%s Ken Hollis (kenji@bitgate.com)\n",
							WATCHDOG_VERSION);

	अगर (cards_found > 1) अणु
		pr_err("This driver only supports 1 device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pcwd_ioports[id] == 0x0000) अणु
		pr_err("No I/O-Address for card detected\n");
		वापस -ENODEV;
	पूर्ण
	pcwd_निजी.io_addr = pcwd_ioports[id];

	spin_lock_init(&pcwd_निजी.io_lock);

	/* Check card's revision */
	pcwd_निजी.revision = get_revision();

	अगर (!request_region(pcwd_निजी.io_addr,
		(pcwd_निजी.revision == PCWD_REVISION_A) ? 2 : 4, "PCWD")) अणु
		pr_err("I/O address 0x%04x already in use\n",
		       pcwd_निजी.io_addr);
		ret = -EIO;
		जाओ error_request_region;
	पूर्ण

	/* Initial variables */
	pcwd_निजी.supports_temp = 0;
	temp_panic = 0;
	pcwd_निजी.boot_status = 0x0000;

	/* get the boot_status */
	pcwd_get_status(&pcwd_निजी.boot_status);

	/* clear the "card caused reboot" flag */
	pcwd_clear_status();

	समयr_setup(&pcwd_निजी.समयr, pcwd_समयr_ping, 0);

	/*  Disable the board  */
	pcwd_stop();

	/*  Check whether or not the card supports the temperature device */
	pcwd_check_temperature_support();

	/* Show info about the card itself */
	pcwd_show_card_info();

	/* If heartbeat = 0 then we use the heartbeat from the dip-चयनes */
	अगर (heartbeat == 0)
		heartbeat = heartbeat_tbl[(pcwd_get_option_चयनes() & 0x07)];

	/* Check that the heartbeat value is within it's range;
	   अगर not reset to the शेष */
	अगर (pcwd_set_heartbeat(heartbeat)) अणु
		pcwd_set_heartbeat(WATCHDOG_HEARTBEAT);
		pr_info("heartbeat value must be 2 <= heartbeat <= 7200, using %d\n",
			WATCHDOG_HEARTBEAT);
	पूर्ण

	अगर (pcwd_निजी.supports_temp) अणु
		ret = misc_रेजिस्टर(&temp_miscdev);
		अगर (ret) अणु
			pr_err("cannot register miscdev on minor=%d (err=%d)\n",
			       TEMP_MINOR, ret);
			जाओ error_misc_रेजिस्टर_temp;
		पूर्ण
	पूर्ण

	ret = misc_रेजिस्टर(&pcwd_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ error_misc_रेजिस्टर_watchकरोg;
	पूर्ण

	pr_info("initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);

	वापस 0;

error_misc_रेजिस्टर_watchकरोg:
	अगर (pcwd_निजी.supports_temp)
		misc_deरेजिस्टर(&temp_miscdev);
error_misc_रेजिस्टर_temp:
	release_region(pcwd_निजी.io_addr,
			(pcwd_निजी.revision == PCWD_REVISION_A) ? 2 : 4);
error_request_region:
	pcwd_निजी.io_addr = 0x0000;
	cards_found--;
	वापस ret;
पूर्ण

अटल व्योम pcwd_isa_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	अगर (debug >= DEBUG)
		pr_debug("pcwd_isa_remove id=%d\n", id);

	/*  Disable the board  */
	अगर (!nowayout)
		pcwd_stop();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&pcwd_miscdev);
	अगर (pcwd_निजी.supports_temp)
		misc_deरेजिस्टर(&temp_miscdev);
	release_region(pcwd_निजी.io_addr,
			(pcwd_निजी.revision == PCWD_REVISION_A) ? 2 : 4);
	pcwd_निजी.io_addr = 0x0000;
	cards_found--;
पूर्ण

अटल व्योम pcwd_isa_shutकरोwn(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	अगर (debug >= DEBUG)
		pr_debug("pcwd_isa_shutdown id=%d\n", id);

	pcwd_stop();
पूर्ण

अटल काष्ठा isa_driver pcwd_isa_driver = अणु
	.match		= pcwd_isa_match,
	.probe		= pcwd_isa_probe,
	.हटाओ		= pcwd_isa_हटाओ,
	.shutकरोwn	= pcwd_isa_shutकरोwn,
	.driver		= अणु
		.owner	= THIS_MODULE,
		.name	= WATCHDOG_NAME,
	पूर्ण,
पूर्ण;

module_isa_driver(pcwd_isa_driver, PCWD_ISA_NR_CARDS);

MODULE_AUTHOR("Ken Hollis <kenji@bitgate.com>, "
		"Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("Berkshire ISA-PC Watchdog driver");
MODULE_VERSION(WATCHDOG_VERSION);
MODULE_LICENSE("GPL");
