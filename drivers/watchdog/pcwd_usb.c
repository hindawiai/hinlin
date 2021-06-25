<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Berkshire USB-PC Watchकरोg Card Driver
 *
 *	(c) Copyright 2004-2007 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	Based on source code of the following authors:
 *	  Ken Hollis <kenji@bitgate.com>,
 *	  Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *	  Matt Domsch <Matt_Domsch@dell.com>,
 *	  Rob Radez <rob@osinvestor.com>,
 *	  Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 *	Neither Wim Van Sebroeck nor Iguana vzw. admit liability nor
 *	provide warranty क्रम any of this software. This material is
 *	provided "AS-IS" and at no अक्षरge.
 *
 *	Thanks also to Simon Machell at Berkshire Products Inc. क्रम
 *	providing the test hardware. More info is available at
 *	http://www.berkprod.com/ or http://www.pcwatchकरोg.com/
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
#समावेश <linux/usb.h>		/* For USB functions */
#समावेश <linux/slab.h>		/* For kदो_स्मृति, ... */
#समावेश <linux/mutex.h>	/* For mutex locking */
#समावेश <linux/hid.h>		/* For HID_REQ_SET_REPORT & HID_DT_REPORT */
#समावेश <linux/uaccess.h>	/* For copy_to_user/put_user/... */


/* Module and Version Inक्रमmation */
#घोषणा DRIVER_VERSION "1.02"
#घोषणा DRIVER_AUTHOR "Wim Van Sebroeck <wim@iguana.be>"
#घोषणा DRIVER_DESC "Berkshire USB-PC Watchdog driver"
#घोषणा DRIVER_NAME "pcwd_usb"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

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

/* The venकरोr and product id's क्रम the USB-PC Watchकरोg card */
#घोषणा USB_PCWD_VENDOR_ID	0x0c98
#घोषणा USB_PCWD_PRODUCT_ID	0x1140

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id usb_pcwd_table[] = अणु
	अणु USB_DEVICE(USB_PCWD_VENDOR_ID, USB_PCWD_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usb_pcwd_table);

/* according to करोcumentation max. समय to process a command क्रम the USB
 * watchकरोg card is 100 or 200 ms, so we give it 250 ms to करो it's job */
#घोषणा USB_COMMAND_TIMEOUT	250

/* Watchकरोg's पूर्णांकernal commands */
#घोषणा CMD_READ_TEMP			0x02	/* Read Temperature;
							Re-trigger Watchकरोg */
#घोषणा CMD_TRIGGER			CMD_READ_TEMP
#घोषणा CMD_GET_STATUS			0x04	/* Get Status Inक्रमmation */
#घोषणा CMD_GET_FIRMWARE_VERSION	0x08	/* Get Firmware Version */
#घोषणा CMD_GET_DIP_SWITCH_SETTINGS	0x0c	/* Get Dip Switch Settings */
#घोषणा CMD_READ_WATCHDOG_TIMEOUT	0x18	/* Read Current Watchकरोg Time */
#घोषणा CMD_WRITE_WATCHDOG_TIMEOUT	0x19	/* Write Current WatchकरोgTime */
#घोषणा CMD_ENABLE_WATCHDOG		0x30	/* Enable / Disable Watchकरोg */
#घोषणा CMD_DISABLE_WATCHDOG		CMD_ENABLE_WATCHDOG

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

/* some पूर्णांकernal variables */
अटल अचिन्हित दीर्घ is_active;
अटल अक्षर expect_release;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_pcwd_निजी अणु
	/* save off the usb device poपूर्णांकer */
	काष्ठा usb_device	*udev;
	/* the पूर्णांकerface क्रम this device */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;

	/* the पूर्णांकerface number used क्रम cmd's */
	अचिन्हित पूर्णांक		पूर्णांकerface_number;

	/* the buffer to पूर्णांकr data */
	अचिन्हित अक्षर		*पूर्णांकr_buffer;
	/* the dma address क्रम the पूर्णांकr buffer */
	dma_addr_t		पूर्णांकr_dma;
	/* the size of the पूर्णांकr buffer */
	माप_प्रकार			पूर्णांकr_size;
	/* the urb used क्रम the पूर्णांकr pipe */
	काष्ठा urb		*पूर्णांकr_urb;

	/* The command that is reported back */
	अचिन्हित अक्षर		cmd_command;
	/* The data MSB that is reported back */
	अचिन्हित अक्षर		cmd_data_msb;
	/* The data LSB that is reported back */
	अचिन्हित अक्षर		cmd_data_lsb;
	/* true अगर we received a report after a command */
	atomic_t		cmd_received;

	/* Wether or not the device exists */
	पूर्णांक			exists;
	/* locks this काष्ठाure */
	काष्ठा mutex		mtx;
पूर्ण;
अटल काष्ठा usb_pcwd_निजी *usb_pcwd_device;

/* prevent races between खोलो() and disconnect() */
अटल DEFINE_MUTEX(disconnect_mutex);

/* local function prototypes */
अटल पूर्णांक usb_pcwd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
						स्थिर काष्ठा usb_device_id *id);
अटल व्योम usb_pcwd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver usb_pcwd_driver = अणु
	.name =		DRIVER_NAME,
	.probe =	usb_pcwd_probe,
	.disconnect =	usb_pcwd_disconnect,
	.id_table =	usb_pcwd_table,
पूर्ण;


अटल व्योम usb_pcwd_पूर्णांकr_करोne(काष्ठा urb *urb)
अणु
	काष्ठा usb_pcwd_निजी *usb_pcwd =
				(काष्ठा usb_pcwd_निजी *)urb->context;
	अचिन्हित अक्षर *data = usb_pcwd->पूर्णांकr_buffer;
	काष्ठा device *dev = &usb_pcwd->पूर्णांकerface->dev;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d",
			__func__, urb->status);
		वापस;
	/* -EPIPE:  should clear the halt */
	शेष:		/* error */
		dev_dbg(dev, "%s - nonzero urb status received: %d",
			__func__, urb->status);
		जाओ resubmit;
	पूर्ण

	dev_dbg(dev, "received following data cmd=0x%02x msb=0x%02x lsb=0x%02x",
		data[0], data[1], data[2]);

	usb_pcwd->cmd_command  = data[0];
	usb_pcwd->cmd_data_msb = data[1];
	usb_pcwd->cmd_data_lsb = data[2];

	/* notअगरy anyone रुकोing that the cmd has finished */
	atomic_set(&usb_pcwd->cmd_received, 1);

resubmit:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		pr_err("can't resubmit intr, usb_submit_urb failed with result %d\n",
		       retval);
पूर्ण

अटल पूर्णांक usb_pcwd_send_command(काष्ठा usb_pcwd_निजी *usb_pcwd,
		अचिन्हित अक्षर cmd, अचिन्हित अक्षर *msb, अचिन्हित अक्षर *lsb)
अणु
	पूर्णांक got_response, count;
	अचिन्हित अक्षर *buf;

	/* We will not send any commands अगर the USB PCWD device करोes
	 * not exist */
	अगर ((!usb_pcwd) || (!usb_pcwd->exists))
		वापस -1;

	buf = kदो_स्मृति(6, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस 0;

	/* The USB PC Watchकरोg uses a 6 byte report क्रमmat.
	 * The board currently uses only 3 of the six bytes of the report. */
	buf[0] = cmd;			/* Byte 0 = CMD */
	buf[1] = *msb;			/* Byte 1 = Data MSB */
	buf[2] = *lsb;			/* Byte 2 = Data LSB */
	buf[3] = buf[4] = buf[5] = 0;	/* All other bytes not used */

	dev_dbg(&usb_pcwd->पूर्णांकerface->dev,
		"sending following data cmd=0x%02x msb=0x%02x lsb=0x%02x",
		buf[0], buf[1], buf[2]);

	atomic_set(&usb_pcwd->cmd_received, 0);

	अगर (usb_control_msg(usb_pcwd->udev, usb_sndctrlpipe(usb_pcwd->udev, 0),
			HID_REQ_SET_REPORT, HID_DT_REPORT,
			0x0200, usb_pcwd->पूर्णांकerface_number, buf, 6,
			USB_COMMAND_TIMEOUT) != 6) अणु
		dev_dbg(&usb_pcwd->पूर्णांकerface->dev,
			"usb_pcwd_send_command: error in usb_control_msg for cmd 0x%x 0x%x 0x%x\n",
			cmd, *msb, *lsb);
	पूर्ण
	/* रुको till the usb card processed the command,
	 * with a max. समयout of USB_COMMAND_TIMEOUT */
	got_response = 0;
	क्रम (count = 0; (count < USB_COMMAND_TIMEOUT) && (!got_response);
								count++) अणु
		mdelay(1);
		अगर (atomic_पढ़ो(&usb_pcwd->cmd_received))
			got_response = 1;
	पूर्ण

	अगर ((got_response) && (cmd == usb_pcwd->cmd_command)) अणु
		/* पढ़ो back response */
		*msb = usb_pcwd->cmd_data_msb;
		*lsb = usb_pcwd->cmd_data_lsb;
	पूर्ण

	kमुक्त(buf);

	वापस got_response;
पूर्ण

अटल पूर्णांक usb_pcwd_start(काष्ठा usb_pcwd_निजी *usb_pcwd)
अणु
	अचिन्हित अक्षर msb = 0x00;
	अचिन्हित अक्षर lsb = 0x00;
	पूर्णांक retval;

	/* Enable Watchकरोg */
	retval = usb_pcwd_send_command(usb_pcwd, CMD_ENABLE_WATCHDOG,
								&msb, &lsb);

	अगर ((retval == 0) || (lsb == 0)) अणु
		pr_err("Card did not acknowledge enable attempt\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_pcwd_stop(काष्ठा usb_pcwd_निजी *usb_pcwd)
अणु
	अचिन्हित अक्षर msb = 0xA5;
	अचिन्हित अक्षर lsb = 0xC3;
	पूर्णांक retval;

	/* Disable Watchकरोg */
	retval = usb_pcwd_send_command(usb_pcwd, CMD_DISABLE_WATCHDOG,
								&msb, &lsb);

	अगर ((retval == 0) || (lsb != 0)) अणु
		pr_err("Card did not acknowledge disable attempt\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_pcwd_keepalive(काष्ठा usb_pcwd_निजी *usb_pcwd)
अणु
	अचिन्हित अक्षर dummy;

	/* Re-trigger Watchकरोg */
	usb_pcwd_send_command(usb_pcwd, CMD_TRIGGER, &dummy, &dummy);

	वापस 0;
पूर्ण

अटल पूर्णांक usb_pcwd_set_heartbeat(काष्ठा usb_pcwd_निजी *usb_pcwd, पूर्णांक t)
अणु
	अचिन्हित अक्षर msb = t / 256;
	अचिन्हित अक्षर lsb = t % 256;

	अगर ((t < 0x0001) || (t > 0xFFFF))
		वापस -EINVAL;

	/* Write new heartbeat to watchकरोg */
	usb_pcwd_send_command(usb_pcwd, CMD_WRITE_WATCHDOG_TIMEOUT, &msb, &lsb);

	heartbeat = t;
	वापस 0;
पूर्ण

अटल पूर्णांक usb_pcwd_get_temperature(काष्ठा usb_pcwd_निजी *usb_pcwd,
							पूर्णांक *temperature)
अणु
	अचिन्हित अक्षर msb, lsb;

	usb_pcwd_send_command(usb_pcwd, CMD_READ_TEMP, &msb, &lsb);

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' क्रम this वापस value.
	 */
	*temperature = (lsb * 9 / 5) + 32;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_pcwd_get_समयleft(काष्ठा usb_pcwd_निजी *usb_pcwd,
								पूर्णांक *समय_left)
अणु
	अचिन्हित अक्षर msb, lsb;

	/* Read the समय that's left beक्रमe rebooting */
	/* Note: अगर the board is not yet armed then we will पढ़ो 0xFFFF */
	usb_pcwd_send_command(usb_pcwd, CMD_READ_WATCHDOG_TIMEOUT, &msb, &lsb);

	*समय_left = (msb << 8) + lsb;

	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार usb_pcwd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
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
		usb_pcwd_keepalive(usb_pcwd_device);
	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ usb_pcwd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	1,
		.identity =		DRIVER_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_GETTEMP:
	अणु
		पूर्णांक temperature;

		अगर (usb_pcwd_get_temperature(usb_pcwd_device, &temperature))
			वापस -EFAULT;

		वापस put_user(temperature, p);
	पूर्ण

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक new_options, retval = -EINVAL;

		अगर (get_user(new_options, p))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD) अणु
			usb_pcwd_stop(usb_pcwd_device);
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_ENABLECARD) अणु
			usb_pcwd_start(usb_pcwd_device);
			retval = 0;
		पूर्ण

		वापस retval;
	पूर्ण

	हाल WDIOC_KEEPALIVE:
		usb_pcwd_keepalive(usb_pcwd_device);
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
	अणु
		पूर्णांक new_heartbeat;

		अगर (get_user(new_heartbeat, p))
			वापस -EFAULT;

		अगर (usb_pcwd_set_heartbeat(usb_pcwd_device, new_heartbeat))
			वापस -EINVAL;

		usb_pcwd_keepalive(usb_pcwd_device);
	पूर्ण
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);

	हाल WDIOC_GETTIMELEFT:
	अणु
		पूर्णांक समय_left;

		अगर (usb_pcwd_get_समयleft(usb_pcwd_device, &समय_left))
			वापस -EFAULT;

		वापस put_user(समय_left, p);
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक usb_pcwd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &is_active))
		वापस -EBUSY;

	/* Activate */
	usb_pcwd_start(usb_pcwd_device);
	usb_pcwd_keepalive(usb_pcwd_device);
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक usb_pcwd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 *      Shut off the समयr.
	 */
	अगर (expect_release == 42) अणु
		usb_pcwd_stop(usb_pcwd_device);
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		usb_pcwd_keepalive(usb_pcwd_device);
	पूर्ण
	expect_release = 0;
	clear_bit(0, &is_active);
	वापस 0;
पूर्ण

/*
 *	/dev/temperature handling
 */

अटल sमाप_प्रकार usb_pcwd_temperature_पढ़ो(काष्ठा file *file, अक्षर __user *data,
				माप_प्रकार len, loff_t *ppos)
अणु
	पूर्णांक temperature;

	अगर (usb_pcwd_get_temperature(usb_pcwd_device, &temperature))
		वापस -EFAULT;

	अगर (copy_to_user(data, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

अटल पूर्णांक usb_pcwd_temperature_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक usb_pcwd_temperature_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 *	Notअगरy प्रणाली
 */

अटल पूर्णांक usb_pcwd_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
								व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		usb_pcwd_stop(usb_pcwd_device);	/* Turn the WDT off */

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations usb_pcwd_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.ग_लिखो =	usb_pcwd_ग_लिखो,
	.unlocked_ioctl = usb_pcwd_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो =		usb_pcwd_खोलो,
	.release =	usb_pcwd_release,
पूर्ण;

अटल काष्ठा miscdevice usb_pcwd_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&usb_pcwd_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations usb_pcwd_temperature_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.पढ़ो =		usb_pcwd_temperature_पढ़ो,
	.खोलो =		usb_pcwd_temperature_खोलो,
	.release =	usb_pcwd_temperature_release,
पूर्ण;

अटल काष्ठा miscdevice usb_pcwd_temperature_miscdev = अणु
	.minor =	TEMP_MINOR,
	.name =		"temperature",
	.fops =		&usb_pcwd_temperature_fops,
पूर्ण;

अटल काष्ठा notअगरier_block usb_pcwd_notअगरier = अणु
	.notअगरier_call =	usb_pcwd_notअगरy_sys,
पूर्ण;

/**
 *	usb_pcwd_delete
 */
अटल अंतरभूत व्योम usb_pcwd_delete(काष्ठा usb_pcwd_निजी *usb_pcwd)
अणु
	usb_मुक्त_urb(usb_pcwd->पूर्णांकr_urb);
	usb_मुक्त_coherent(usb_pcwd->udev, usb_pcwd->पूर्णांकr_size,
			  usb_pcwd->पूर्णांकr_buffer, usb_pcwd->पूर्णांकr_dma);
	kमुक्त(usb_pcwd);
पूर्ण

/**
 *	usb_pcwd_probe
 *
 *	Called by the usb core when a new device is connected that it thinks
 *	this driver might be पूर्णांकerested in.
 */
अटल पूर्णांक usb_pcwd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
						स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_pcwd_निजी *usb_pcwd = शून्य;
	पूर्णांक pipe;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक got_fw_rev;
	अचिन्हित अक्षर fw_rev_major, fw_rev_minor;
	अक्षर fw_ver_str[20];
	अचिन्हित अक्षर option_चयनes, dummy;

	cards_found++;
	अगर (cards_found > 1) अणु
		pr_err("This driver only supports 1 device\n");
		वापस -ENODEV;
	पूर्ण

	/* get the active पूर्णांकerface descriptor */
	अगरace_desc = पूर्णांकerface->cur_altsetting;

	/* check out that we have a HID device */
	अगर (!(अगरace_desc->desc.bInterfaceClass == USB_CLASS_HID)) अणु
		pr_err("The device isn't a Human Interface Device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	/* check out the endpoपूर्णांक: it has to be Interrupt & IN */
	endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[0].desc;

	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक)) अणु
		/* we didn't find a Interrupt endpoपूर्णांक with direction IN */
		pr_err("Couldn't find an INTR & IN endpoint\n");
		वापस -ENODEV;
	पूर्ण

	/* get a handle to the पूर्णांकerrupt data pipe */
	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress);

	/* allocate memory क्रम our device and initialize it */
	usb_pcwd = kzalloc(माप(काष्ठा usb_pcwd_निजी), GFP_KERNEL);
	अगर (usb_pcwd == शून्य)
		जाओ error;

	usb_pcwd_device = usb_pcwd;

	mutex_init(&usb_pcwd->mtx);
	usb_pcwd->udev = udev;
	usb_pcwd->पूर्णांकerface = पूर्णांकerface;
	usb_pcwd->पूर्णांकerface_number = अगरace_desc->desc.bInterfaceNumber;
	usb_pcwd->पूर्णांकr_size = (le16_to_cpu(endpoपूर्णांक->wMaxPacketSize) > 8 ?
				le16_to_cpu(endpoपूर्णांक->wMaxPacketSize) : 8);

	/* set up the memory buffer's */
	usb_pcwd->पूर्णांकr_buffer = usb_alloc_coherent(udev, usb_pcwd->पूर्णांकr_size,
					GFP_KERNEL, &usb_pcwd->पूर्णांकr_dma);
	अगर (!usb_pcwd->पूर्णांकr_buffer) अणु
		pr_err("Out of memory\n");
		जाओ error;
	पूर्ण

	/* allocate the urb's */
	usb_pcwd->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!usb_pcwd->पूर्णांकr_urb)
		जाओ error;

	/* initialise the पूर्णांकr urb's */
	usb_fill_पूर्णांक_urb(usb_pcwd->पूर्णांकr_urb, udev, pipe,
			usb_pcwd->पूर्णांकr_buffer, usb_pcwd->पूर्णांकr_size,
			usb_pcwd_पूर्णांकr_करोne, usb_pcwd, endpoपूर्णांक->bInterval);
	usb_pcwd->पूर्णांकr_urb->transfer_dma = usb_pcwd->पूर्णांकr_dma;
	usb_pcwd->पूर्णांकr_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* रेजिस्टर our पूर्णांकerrupt URB with the USB प्रणाली */
	अगर (usb_submit_urb(usb_pcwd->पूर्णांकr_urb, GFP_KERNEL)) अणु
		pr_err("Problem registering interrupt URB\n");
		retval = -EIO; /* failure */
		जाओ error;
	पूर्ण

	/* The device exists and can be communicated with */
	usb_pcwd->exists = 1;

	/* disable card */
	usb_pcwd_stop(usb_pcwd);

	/* Get the Firmware Version */
	got_fw_rev = usb_pcwd_send_command(usb_pcwd, CMD_GET_FIRMWARE_VERSION,
						&fw_rev_major, &fw_rev_minor);
	अगर (got_fw_rev)
		प्र_लिखो(fw_ver_str, "%u.%02u", fw_rev_major, fw_rev_minor);
	अन्यथा
		प्र_लिखो(fw_ver_str, "<card no answer>");

	pr_info("Found card (Firmware: %s) with temp option\n", fw_ver_str);

	/* Get चयन settings */
	usb_pcwd_send_command(usb_pcwd, CMD_GET_DIP_SWITCH_SETTINGS, &dummy,
							&option_चयनes);

	pr_info("Option switches (0x%02x): Temperature Reset Enable=%s, Power On Delay=%s\n",
		option_चयनes,
		((option_चयनes & 0x10) ? "ON" : "OFF"),
		((option_चयनes & 0x08) ? "ON" : "OFF"));

	/* If heartbeat = 0 then we use the heartbeat from the dip-चयनes */
	अगर (heartbeat == 0)
		heartbeat = heartbeat_tbl[(option_चयनes & 0x07)];

	/* Check that the heartbeat value is within it's range ;
	 * अगर not reset to the शेष */
	अगर (usb_pcwd_set_heartbeat(usb_pcwd, heartbeat)) अणु
		usb_pcwd_set_heartbeat(usb_pcwd, WATCHDOG_HEARTBEAT);
		pr_info("heartbeat value must be 0<heartbeat<65536, using %d\n",
			WATCHDOG_HEARTBEAT);
	पूर्ण

	retval = रेजिस्टर_reboot_notअगरier(&usb_pcwd_notअगरier);
	अगर (retval != 0) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", retval);
		जाओ error;
	पूर्ण

	retval = misc_रेजिस्टर(&usb_pcwd_temperature_miscdev);
	अगर (retval != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       TEMP_MINOR, retval);
		जाओ err_out_unरेजिस्टर_reboot;
	पूर्ण

	retval = misc_रेजिस्टर(&usb_pcwd_miscdev);
	अगर (retval != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, retval);
		जाओ err_out_misc_deरेजिस्टर;
	पूर्ण

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, usb_pcwd);

	pr_info("initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);

	वापस 0;

err_out_misc_deरेजिस्टर:
	misc_deरेजिस्टर(&usb_pcwd_temperature_miscdev);
err_out_unरेजिस्टर_reboot:
	unरेजिस्टर_reboot_notअगरier(&usb_pcwd_notअगरier);
error:
	अगर (usb_pcwd)
		usb_pcwd_delete(usb_pcwd);
	usb_pcwd_device = शून्य;
	वापस retval;
पूर्ण


/**
 *	usb_pcwd_disconnect
 *
 *	Called by the usb core when the device is हटाओd from the प्रणाली.
 *
 *	This routine guarantees that the driver will not submit any more urbs
 *	by clearing dev->udev.
 */
अटल व्योम usb_pcwd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_pcwd_निजी *usb_pcwd;

	/* prevent races with खोलो() */
	mutex_lock(&disconnect_mutex);

	usb_pcwd = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	mutex_lock(&usb_pcwd->mtx);

	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout)
		usb_pcwd_stop(usb_pcwd);

	/* We should now stop communicating with the USB PCWD device */
	usb_pcwd->exists = 0;

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&usb_pcwd_miscdev);
	misc_deरेजिस्टर(&usb_pcwd_temperature_miscdev);
	unरेजिस्टर_reboot_notअगरier(&usb_pcwd_notअगरier);

	mutex_unlock(&usb_pcwd->mtx);

	/* Delete the USB PCWD device */
	usb_pcwd_delete(usb_pcwd);

	cards_found--;

	mutex_unlock(&disconnect_mutex);

	pr_info("USB PC Watchdog disconnected\n");
पूर्ण

module_usb_driver(usb_pcwd_driver);
