<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FIXME: add wdrtas_get_status and wdrtas_get_boot_status as soon as
 * RTAS calls are available
 */

/*
 * RTAS watchकरोg driver
 *
 * (C) Copyright IBM Corp. 2005
 * device driver to exploit watchकरोg RTAS functions
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/rtas.h>

#घोषणा WDRTAS_MAGIC_CHAR		42
#घोषणा WDRTAS_SUPPORTED_MASK		(WDIOF_SETTIMEOUT | \
					 WDIOF_MAGICCLOSE)

MODULE_AUTHOR("Utz Bacher <utz.bacher@de.ibm.com>");
MODULE_DESCRIPTION("RTAS watchdog driver");
MODULE_LICENSE("GPL");

अटल bool wdrtas_nowayout = WATCHDOG_NOWAYOUT;
अटल atomic_t wdrtas_miscdev_खोलो = ATOMIC_INIT(0);
अटल अक्षर wdrtas_expect_बंद;

अटल पूर्णांक wdrtas_पूर्णांकerval;

#घोषणा WDRTAS_THERMAL_SENSOR		3
अटल पूर्णांक wdrtas_token_get_sensor_state;
#घोषणा WDRTAS_SURVEILLANCE_IND		9000
अटल पूर्णांक wdrtas_token_set_indicator;
#घोषणा WDRTAS_SP_SPI			28
अटल पूर्णांक wdrtas_token_get_sp;
अटल पूर्णांक wdrtas_token_event_scan;

#घोषणा WDRTAS_DEFAULT_INTERVAL		300

#घोषणा WDRTAS_LOGBUFFER_LEN		128
अटल अक्षर wdrtas_logbuffer[WDRTAS_LOGBUFFER_LEN];


/*** watchकरोg access functions */

/**
 * wdrtas_set_पूर्णांकerval - sets the watchकरोg पूर्णांकerval
 * @पूर्णांकerval: new पूर्णांकerval
 *
 * वापसs 0 on success, <0 on failures
 *
 * wdrtas_set_पूर्णांकerval sets the watchकरोg keepalive पूर्णांकerval by calling the
 * RTAS function set-indicator (surveillance). The unit of पूर्णांकerval is
 * seconds.
 */

अटल पूर्णांक wdrtas_set_पूर्णांकerval(पूर्णांक पूर्णांकerval)
अणु
	दीर्घ result;
	अटल पूर्णांक prपूर्णांक_msg = 10;

	/* rtas uses minutes */
	पूर्णांकerval = (पूर्णांकerval + 59) / 60;

	result = rtas_call(wdrtas_token_set_indicator, 3, 1, शून्य,
			   WDRTAS_SURVEILLANCE_IND, 0, पूर्णांकerval);
	अगर (result < 0 && prपूर्णांक_msg) अणु
		pr_err("setting the watchdog to %i timeout failed: %li\n",
		       पूर्णांकerval, result);
		prपूर्णांक_msg--;
	पूर्ण

	वापस result;
पूर्ण

#घोषणा WDRTAS_SP_SPI_LEN 4

/**
 * wdrtas_get_पूर्णांकerval - वापसs the current watchकरोg पूर्णांकerval
 * @fallback_value: value (in seconds) to use, अगर the RTAS call fails
 *
 * वापसs the पूर्णांकerval
 *
 * wdrtas_get_पूर्णांकerval वापसs the current watchकरोg keepalive पूर्णांकerval
 * as reported by the RTAS function ibm,get-प्रणाली-parameter. The unit
 * of the वापस value is seconds.
 */
अटल पूर्णांक wdrtas_get_पूर्णांकerval(पूर्णांक fallback_value)
अणु
	दीर्घ result;
	अक्षर value[WDRTAS_SP_SPI_LEN];

	spin_lock(&rtas_data_buf_lock);
	स_रखो(rtas_data_buf, 0, WDRTAS_SP_SPI_LEN);
	result = rtas_call(wdrtas_token_get_sp, 3, 1, शून्य,
			   WDRTAS_SP_SPI, __pa(rtas_data_buf),
			   WDRTAS_SP_SPI_LEN);

	स_नकल(value, rtas_data_buf, WDRTAS_SP_SPI_LEN);
	spin_unlock(&rtas_data_buf_lock);

	अगर (value[0] != 0 || value[1] != 2 || value[3] != 0 || result < 0) अणु
		pr_warn("could not get sp_spi watchdog timeout (%li). Continuing\n",
			result);
		वापस fallback_value;
	पूर्ण

	/* rtas uses minutes */
	वापस ((पूर्णांक)value[2]) * 60;
पूर्ण

/**
 * wdrtas_समयr_start - starts watchकरोg
 *
 * wdrtas_समयr_start starts the watchकरोg by calling the RTAS function
 * set-पूर्णांकerval (surveillance)
 */
अटल व्योम wdrtas_समयr_start(व्योम)
अणु
	wdrtas_set_पूर्णांकerval(wdrtas_पूर्णांकerval);
पूर्ण

/**
 * wdrtas_समयr_stop - stops watchकरोg
 *
 * wdrtas_समयr_stop stops the watchकरोg समयr by calling the RTAS function
 * set-पूर्णांकerval (surveillance)
 */
अटल व्योम wdrtas_समयr_stop(व्योम)
अणु
	wdrtas_set_पूर्णांकerval(0);
पूर्ण

/**
 * wdrtas_समयr_keepalive - resets watchकरोg समयr to keep प्रणाली alive
 *
 * wdrtas_समयr_keepalive restarts the watchकरोg समयr by calling the
 * RTAS function event-scan and repeats these calls as दीर्घ as there are
 * events available. All events will be dumped.
 */
अटल व्योम wdrtas_समयr_keepalive(व्योम)
अणु
	दीर्घ result;

	करो अणु
		result = rtas_call(wdrtas_token_event_scan, 4, 1, शून्य,
				   RTAS_EVENT_SCAN_ALL_EVENTS, 0,
				   (व्योम *)__pa(wdrtas_logbuffer),
				   WDRTAS_LOGBUFFER_LEN);
		अगर (result < 0)
			pr_err("event-scan failed: %li\n", result);
		अगर (result == 0)
			prपूर्णांक_hex_dump(KERN_INFO, "dumping event, data: ",
				DUMP_PREFIX_OFFSET, 16, 1,
				wdrtas_logbuffer, WDRTAS_LOGBUFFER_LEN, false);
	पूर्ण जबतक (result == 0);
पूर्ण

/**
 * wdrtas_get_temperature - वापसs current temperature
 *
 * वापसs temperature or <0 on failures
 *
 * wdrtas_get_temperature वापसs the current temperature in Fahrenheit. It
 * uses the RTAS call get-sensor-state, token 3 to करो so
 */
अटल पूर्णांक wdrtas_get_temperature(व्योम)
अणु
	पूर्णांक result;
	पूर्णांक temperature = 0;

	result = rtas_get_sensor(WDRTAS_THERMAL_SENSOR, 0, &temperature);

	अगर (result < 0)
		pr_warn("reading the thermal sensor failed: %i\n", result);
	अन्यथा
		temperature = ((temperature * 9) / 5) + 32; /* fahrenheit */

	वापस temperature;
पूर्ण

/**
 * wdrtas_get_status - वापसs the status of the watchकरोg
 *
 * वापसs a biपंचांगask of defines WDIOF_... as defined in
 * include/linux/watchकरोg.h
 */
अटल पूर्णांक wdrtas_get_status(व्योम)
अणु
	वापस 0; /* TODO */
पूर्ण

/**
 * wdrtas_get_boot_status - वापसs the reason क्रम the last boot
 *
 * वापसs a biपंचांगask of defines WDIOF_... as defined in
 * include/linux/watchकरोg.h, indicating why the watchकरोg rebooted the प्रणाली
 */
अटल पूर्णांक wdrtas_get_boot_status(व्योम)
अणु
	वापस 0; /* TODO */
पूर्ण

/*** watchकरोg API and operations stuff */

/* wdrtas_ग_लिखो - called when watchकरोg device is written to
 * @file: file काष्ठाure
 * @buf: user buffer with data
 * @len: amount to data written
 * @ppos: position in file
 *
 * वापसs the number of successfully processed अक्षरacters, which is always
 * the number of bytes passed to this function
 *
 * wdrtas_ग_लिखो processes all the data given to it and looks क्रम the magic
 * अक्षरacter 'V'. This अक्षरacter allows the watchकरोg device to be बंदd
 * properly.
 */
अटल sमाप_प्रकार wdrtas_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	     माप_प्रकार len, loff_t *ppos)
अणु
	पूर्णांक i;
	अक्षर c;

	अगर (!len)
		जाओ out;

	अगर (!wdrtas_nowayout) अणु
		wdrtas_expect_बंद = 0;
		/* look क्रम 'V' */
		क्रम (i = 0; i < len; i++) अणु
			अगर (get_user(c, buf + i))
				वापस -EFAULT;
			/* allow to बंद device */
			अगर (c == 'V')
				wdrtas_expect_बंद = WDRTAS_MAGIC_CHAR;
		पूर्ण
	पूर्ण

	wdrtas_समयr_keepalive();

out:
	वापस len;
पूर्ण

/**
 * wdrtas_ioctl - ioctl function क्रम the watchकरोg device
 * @file: file काष्ठाure
 * @cmd: command क्रम ioctl
 * @arg: argument poपूर्णांकer
 *
 * वापसs 0 on success, <0 on failure
 *
 * wdrtas_ioctl implements the watchकरोg API ioctls
 */

अटल दीर्घ wdrtas_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक __user *argp = (व्योम __user *)arg;
	पूर्णांक i;
	अटल स्थिर काष्ठा watchकरोg_info wdinfo = अणु
		.options = WDRTAS_SUPPORTED_MASK,
		.firmware_version = 0,
		.identity = "wdrtas",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &wdinfo, माप(wdinfo)))
			वापस -EFAULT;
		वापस 0;

	हाल WDIOC_GETSTATUS:
		i = wdrtas_get_status();
		वापस put_user(i, argp);

	हाल WDIOC_GETBOOTSTATUS:
		i = wdrtas_get_boot_status();
		वापस put_user(i, argp);

	हाल WDIOC_GETTEMP:
		अगर (wdrtas_token_get_sensor_state == RTAS_UNKNOWN_SERVICE)
			वापस -EOPNOTSUPP;

		i = wdrtas_get_temperature();
		वापस put_user(i, argp);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(i, argp))
			वापस -EFAULT;
		अगर (i & WDIOS_DISABLECARD)
			wdrtas_समयr_stop();
		अगर (i & WDIOS_ENABLECARD) अणु
			wdrtas_समयr_keepalive();
			wdrtas_समयr_start();
		पूर्ण
		/* not implemented. Done by H8
		अगर (i & WDIOS_TEMPPANIC) अणु
		पूर्ण */
		वापस 0;

	हाल WDIOC_KEEPALIVE:
		wdrtas_समयr_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(i, argp))
			वापस -EFAULT;

		अगर (wdrtas_set_पूर्णांकerval(i))
			वापस -EINVAL;

		wdrtas_समयr_keepalive();

		अगर (wdrtas_token_get_sp == RTAS_UNKNOWN_SERVICE)
			wdrtas_पूर्णांकerval = i;
		अन्यथा
			wdrtas_पूर्णांकerval = wdrtas_get_पूर्णांकerval(i);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(wdrtas_पूर्णांकerval, argp);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 * wdrtas_खोलो - खोलो function of watchकरोg device
 * @inode: inode काष्ठाure
 * @file: file काष्ठाure
 *
 * वापसs 0 on success, -EBUSY अगर the file has been खोलोed alपढ़ोy, <0 on
 * other failures
 *
 * function called when watchकरोg device is खोलोed
 */
अटल पूर्णांक wdrtas_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* only खोलो once */
	अगर (atomic_inc_वापस(&wdrtas_miscdev_खोलो) > 1) अणु
		atomic_dec(&wdrtas_miscdev_खोलो);
		वापस -EBUSY;
	पूर्ण

	wdrtas_समयr_start();
	wdrtas_समयr_keepalive();

	वापस stream_खोलो(inode, file);
पूर्ण

/**
 * wdrtas_बंद - बंद function of watchकरोg device
 * @inode: inode काष्ठाure
 * @file: file काष्ठाure
 *
 * वापसs 0 on success
 *
 * बंद function. Always succeeds
 */
अटल पूर्णांक wdrtas_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* only stop watchकरोg, अगर this was announced using 'V' beक्रमe */
	अगर (wdrtas_expect_बंद == WDRTAS_MAGIC_CHAR)
		wdrtas_समयr_stop();
	अन्यथा अणु
		pr_warn("got unexpected close. Watchdog not stopped.\n");
		wdrtas_समयr_keepalive();
	पूर्ण

	wdrtas_expect_बंद = 0;
	atomic_dec(&wdrtas_miscdev_खोलो);
	वापस 0;
पूर्ण

/**
 * wdrtas_temp_पढ़ो - gives back the temperature in fahrenheit
 * @file: file काष्ठाure
 * @buf: user buffer
 * @count: number of bytes to be पढ़ो
 * @ppos: position in file
 *
 * वापसs always 1 or -EFAULT in हाल of user space copy failures, <0 on
 * other failures
 *
 * wdrtas_temp_पढ़ो gives the temperature to the users by copying this
 * value as one byte पूर्णांकo the user space buffer. The unit is Fahrenheit...
 */
अटल sमाप_प्रकार wdrtas_temp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक temperature = 0;

	temperature = wdrtas_get_temperature();
	अगर (temperature < 0)
		वापस temperature;

	अगर (copy_to_user(buf, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

/**
 * wdrtas_temp_खोलो - खोलो function of temperature device
 * @inode: inode काष्ठाure
 * @file: file काष्ठाure
 *
 * वापसs 0 on success, <0 on failure
 *
 * function called when temperature device is खोलोed
 */
अटल पूर्णांक wdrtas_temp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 * wdrtas_temp_बंद - बंद function of temperature device
 * @inode: inode काष्ठाure
 * @file: file काष्ठाure
 *
 * वापसs 0 on success
 *
 * बंद function. Always succeeds
 */
अटल पूर्णांक wdrtas_temp_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/**
 * wdrtas_reboot - reboot notअगरier function
 * @nb: notअगरier block काष्ठाure
 * @code: reboot code
 * @ptr: unused
 *
 * वापसs NOTIFY_DONE
 *
 * wdrtas_reboot stops the watchकरोg in हाल of a reboot
 */
अटल पूर्णांक wdrtas_reboot(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *ptr)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdrtas_समयr_stop();

	वापस NOTIFY_DONE;
पूर्ण

/*** initialization stuff */

अटल स्थिर काष्ठा file_operations wdrtas_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wdrtas_ग_लिखो,
	.unlocked_ioctl	= wdrtas_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wdrtas_खोलो,
	.release	= wdrtas_बंद,
पूर्ण;

अटल काष्ठा miscdevice wdrtas_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&wdrtas_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations wdrtas_temp_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= wdrtas_temp_पढ़ो,
	.खोलो		= wdrtas_temp_खोलो,
	.release	= wdrtas_temp_बंद,
पूर्ण;

अटल काष्ठा miscdevice wdrtas_tempdev = अणु
	.minor =	TEMP_MINOR,
	.name =		"temperature",
	.fops =		&wdrtas_temp_fops,
पूर्ण;

अटल काष्ठा notअगरier_block wdrtas_notअगरier = अणु
	.notअगरier_call =	wdrtas_reboot,
पूर्ण;

/**
 * wdrtas_get_tokens - पढ़ोs in RTAS tokens
 *
 * वापसs 0 on success, <0 on failure
 *
 * wdrtas_get_tokens पढ़ोs in the tokens क्रम the RTAS calls used in
 * this watchकरोg driver. It tolerates, अगर "get-sensor-state" and
 * "ibm,get-system-parameter" are not available.
 */
अटल पूर्णांक wdrtas_get_tokens(व्योम)
अणु
	wdrtas_token_get_sensor_state = rtas_token("get-sensor-state");
	अगर (wdrtas_token_get_sensor_state == RTAS_UNKNOWN_SERVICE) अणु
		pr_warn("couldn't get token for get-sensor-state. Trying to continue without temperature support.\n");
	पूर्ण

	wdrtas_token_get_sp = rtas_token("ibm,get-system-parameter");
	अगर (wdrtas_token_get_sp == RTAS_UNKNOWN_SERVICE) अणु
		pr_warn("couldn't get token for ibm,get-system-parameter. Trying to continue with a default timeout value of %i seconds.\n",
			WDRTAS_DEFAULT_INTERVAL);
	पूर्ण

	wdrtas_token_set_indicator = rtas_token("set-indicator");
	अगर (wdrtas_token_set_indicator == RTAS_UNKNOWN_SERVICE) अणु
		pr_err("couldn't get token for set-indicator. Terminating watchdog code.\n");
		वापस -EIO;
	पूर्ण

	wdrtas_token_event_scan = rtas_token("event-scan");
	अगर (wdrtas_token_event_scan == RTAS_UNKNOWN_SERVICE) अणु
		pr_err("couldn't get token for event-scan. Terminating watchdog code.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wdrtas_unरेजिस्टर_devs - unरेजिस्टरs the misc dev handlers
 *
 * wdrtas_रेजिस्टर_devs unरेजिस्टरs the watchकरोg and temperature watchकरोg
 * misc devs
 */
अटल व्योम wdrtas_unरेजिस्टर_devs(व्योम)
अणु
	misc_deरेजिस्टर(&wdrtas_miscdev);
	अगर (wdrtas_token_get_sensor_state != RTAS_UNKNOWN_SERVICE)
		misc_deरेजिस्टर(&wdrtas_tempdev);
पूर्ण

/**
 * wdrtas_रेजिस्टर_devs - रेजिस्टरs the misc dev handlers
 *
 * वापसs 0 on success, <0 on failure
 *
 * wdrtas_रेजिस्टर_devs रेजिस्टरs the watchकरोg and temperature watchकरोg
 * misc devs
 */
अटल पूर्णांक wdrtas_रेजिस्टर_devs(व्योम)
अणु
	पूर्णांक result;

	result = misc_रेजिस्टर(&wdrtas_miscdev);
	अगर (result) अणु
		pr_err("couldn't register watchdog misc device. Terminating watchdog code.\n");
		वापस result;
	पूर्ण

	अगर (wdrtas_token_get_sensor_state != RTAS_UNKNOWN_SERVICE) अणु
		result = misc_रेजिस्टर(&wdrtas_tempdev);
		अगर (result) अणु
			pr_warn("couldn't register watchdog temperature misc device. Continuing without temperature support.\n");
			wdrtas_token_get_sensor_state = RTAS_UNKNOWN_SERVICE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wdrtas_init - init function of the watchकरोg driver
 *
 * वापसs 0 on success, <0 on failure
 *
 * रेजिस्टरs the file handlers and the reboot notअगरier
 */
अटल पूर्णांक __init wdrtas_init(व्योम)
अणु
	अगर (wdrtas_get_tokens())
		वापस -ENODEV;

	अगर (wdrtas_रेजिस्टर_devs())
		वापस -ENODEV;

	अगर (रेजिस्टर_reboot_notअगरier(&wdrtas_notअगरier)) अणु
		pr_err("could not register reboot notifier. Terminating watchdog code.\n");
		wdrtas_unरेजिस्टर_devs();
		वापस -ENODEV;
	पूर्ण

	अगर (wdrtas_token_get_sp == RTAS_UNKNOWN_SERVICE)
		wdrtas_पूर्णांकerval = WDRTAS_DEFAULT_INTERVAL;
	अन्यथा
		wdrtas_पूर्णांकerval = wdrtas_get_पूर्णांकerval(WDRTAS_DEFAULT_INTERVAL);

	वापस 0;
पूर्ण

/**
 * wdrtas_निकास - निकास function of the watchकरोg driver
 *
 * unरेजिस्टरs the file handlers and the reboot notअगरier
 */
अटल व्योम __निकास wdrtas_निकास(व्योम)
अणु
	अगर (!wdrtas_nowayout)
		wdrtas_समयr_stop();

	wdrtas_unरेजिस्टर_devs();

	unरेजिस्टर_reboot_notअगरier(&wdrtas_notअगरier);
पूर्ण

module_init(wdrtas_init);
module_निकास(wdrtas_निकास);
