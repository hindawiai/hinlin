<शैली गुरु>
/*
 * Watchकरोg driver क्रम SBC-FITPC2 board
 *
 * Author: Denis Turischev <denis@compulab.co.il>
 *
 * Adapted from the IXP2000 watchकरोg driver by Deepak Saxena.
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME " WATCHDOG: " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक margin = 60;	/* (secs) Default is 1 minute */
अटल अचिन्हित दीर्घ wdt_status;
अटल DEFINE_MUTEX(wdt_lock);

#घोषणा WDT_IN_USE		0
#घोषणा WDT_OK_TO_CLOSE		1

#घोषणा COMMAND_PORT		0x4c
#घोषणा DATA_PORT		0x48

#घोषणा IFACE_ON_COMMAND	1
#घोषणा REBOOT_COMMAND		2

#घोषणा WATCHDOG_NAME		"SBC-FITPC2 Watchdog"

अटल व्योम wdt_send_data(अचिन्हित अक्षर command, अचिन्हित अक्षर data)
अणु
	outb(data, DATA_PORT);
	msleep(200);
	outb(command, COMMAND_PORT);
	msleep(100);
पूर्ण

अटल व्योम wdt_enable(व्योम)
अणु
	mutex_lock(&wdt_lock);
	wdt_send_data(IFACE_ON_COMMAND, 1);
	wdt_send_data(REBOOT_COMMAND, margin);
	mutex_unlock(&wdt_lock);
पूर्ण

अटल व्योम wdt_disable(व्योम)
अणु
	mutex_lock(&wdt_lock);
	wdt_send_data(IFACE_ON_COMMAND, 0);
	wdt_send_data(REBOOT_COMMAND, 0);
	mutex_unlock(&wdt_lock);
पूर्ण

अटल पूर्णांक fitpc2_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(WDT_IN_USE, &wdt_status))
		वापस -EBUSY;

	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	wdt_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार fitpc2_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	माप_प्रकार i;

	अगर (!len)
		वापस 0;

	अगर (nowayout) अणु
		len = 0;
		जाओ out;
	पूर्ण

	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	क्रम (i = 0; i != len; i++) अणु
		अक्षर c;

		अगर (get_user(c, data + i))
			वापस -EFAULT;

		अगर (c == 'V')
			set_bit(WDT_OK_TO_CLOSE, &wdt_status);
	पूर्ण

out:
	wdt_enable();

	वापस len;
पूर्ण


अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options	= WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT |
				WDIOF_KEEPALIVEPING,
	.identity	= WATCHDOG_NAME,
पूर्ण;


अटल दीर्घ fitpc2_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -ENOTTY;
	पूर्णांक समय;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ret = copy_to_user((काष्ठा watchकरोg_info __user *)arg, &ident,
				   माप(ident)) ? -EFAULT : 0;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		ret = put_user(0, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(0, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		wdt_enable();
		ret = 0;
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		ret = get_user(समय, (पूर्णांक __user *)arg);
		अगर (ret)
			अवरोध;

		अगर (समय < 31 || समय > 255) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		margin = समय;
		wdt_enable();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		ret = put_user(margin, (पूर्णांक __user *)arg);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fitpc2_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_bit(WDT_OK_TO_CLOSE, &wdt_status)) अणु
		wdt_disable();
		pr_info("Device disabled\n");
	पूर्ण अन्यथा अणु
		pr_warn("Device closed unexpectedly - timer will not stop\n");
		wdt_enable();
	पूर्ण

	clear_bit(WDT_IN_USE, &wdt_status);
	clear_bit(WDT_OK_TO_CLOSE, &wdt_status);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations fitpc2_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= fitpc2_wdt_ग_लिखो,
	.unlocked_ioctl	= fitpc2_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= fitpc2_wdt_खोलो,
	.release	= fitpc2_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice fitpc2_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &fitpc2_wdt_fops,
पूर्ण;

अटल पूर्णांक __init fitpc2_wdt_init(व्योम)
अणु
	पूर्णांक err;
	स्थिर अक्षर *brd_name;

	brd_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);

	अगर (!brd_name || !म_माला(brd_name, "SBC-FITPC2"))
		वापस -ENODEV;

	pr_info("%s found\n", brd_name);

	अगर (!request_region(COMMAND_PORT, 1, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", COMMAND_PORT);
		वापस -EIO;
	पूर्ण

	अगर (!request_region(DATA_PORT, 1, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", DATA_PORT);
		err = -EIO;
		जाओ err_data_port;
	पूर्ण

	अगर (margin < 31 || margin > 255) अणु
		pr_err("margin must be in range 31 - 255 seconds, you tried to set %d\n",
		       margin);
		err = -EINVAL;
		जाओ err_margin;
	पूर्ण

	err = misc_रेजिस्टर(&fitpc2_wdt_miscdev);
	अगर (err) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, err);
		जाओ err_margin;
	पूर्ण

	वापस 0;

err_margin:
	release_region(DATA_PORT, 1);
err_data_port:
	release_region(COMMAND_PORT, 1);

	वापस err;
पूर्ण

अटल व्योम __निकास fitpc2_wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&fitpc2_wdt_miscdev);
	release_region(DATA_PORT, 1);
	release_region(COMMAND_PORT, 1);
पूर्ण

module_init(fitpc2_wdt_init);
module_निकास(fitpc2_wdt_निकास);

MODULE_AUTHOR("Denis Turischev <denis@compulab.co.il>");
MODULE_DESCRIPTION("SBC-FITPC2 Watchdog");

module_param(margin, पूर्णांक, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds (default 60s)");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");

MODULE_LICENSE("GPL");
