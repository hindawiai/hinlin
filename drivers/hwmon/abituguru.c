<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * abituguru.c Copyright (c) 2005-2006 Hans de Goede <hdegoede@redhat.com>
 */
/*
 * This driver supports the sensor part of the first and second revision of
 * the custom Abit uGuru chip found on Abit uGuru motherboards. Note: because
 * of lack of specs the CPU/RAM voltage & frequency control is not supported!
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>

/* Banks */
#घोषणा ABIT_UGURU_ALARM_BANK			0x20 /* 1x 3 bytes */
#घोषणा ABIT_UGURU_SENSOR_BANK1			0x21 /* 16x volt and temp */
#घोषणा ABIT_UGURU_FAN_PWM			0x24 /* 3x 5 bytes */
#घोषणा ABIT_UGURU_SENSOR_BANK2			0x26 /* fans */
/* max nr of sensors in bank1, a bank1 sensor can be in, temp or nc */
#घोषणा ABIT_UGURU_MAX_BANK1_SENSORS		16
/*
 * Warning अगर you increase one of the 2 MAX defines below to 10 or higher you
 * should adjust the beदीर्घing _NAMES_LENGTH macro क्रम the 2 digit number!
 */
/* max nr of sensors in bank2, currently mb's with max 6 fans are known */
#घोषणा ABIT_UGURU_MAX_BANK2_SENSORS		6
/* max nr of pwm outमाला_दो, currently mb's with max 5 pwm outमाला_दो are known */
#घोषणा ABIT_UGURU_MAX_PWMS			5
/* uGuru sensor bank 1 flags */			     /* Alarm अगर: */
#घोषणा ABIT_UGURU_TEMP_HIGH_ALARM_ENABLE	0x01 /*  temp over warn */
#घोषणा ABIT_UGURU_VOLT_HIGH_ALARM_ENABLE	0x02 /*  volt over max */
#घोषणा ABIT_UGURU_VOLT_LOW_ALARM_ENABLE	0x04 /*  volt under min */
#घोषणा ABIT_UGURU_TEMP_HIGH_ALARM_FLAG		0x10 /* temp is over warn */
#घोषणा ABIT_UGURU_VOLT_HIGH_ALARM_FLAG		0x20 /* volt is over max */
#घोषणा ABIT_UGURU_VOLT_LOW_ALARM_FLAG		0x40 /* volt is under min */
/* uGuru sensor bank 2 flags */			     /* Alarm अगर: */
#घोषणा ABIT_UGURU_FAN_LOW_ALARM_ENABLE		0x01 /*   fan under min */
/* uGuru sensor bank common flags */
#घोषणा ABIT_UGURU_BEEP_ENABLE			0x08 /* beep अगर alarm */
#घोषणा ABIT_UGURU_SHUTDOWN_ENABLE		0x80 /* shutकरोwn अगर alarm */
/* uGuru fan PWM (speed control) flags */
#घोषणा ABIT_UGURU_FAN_PWM_ENABLE		0x80 /* enable speed control */
/* Values used क्रम conversion */
#घोषणा ABIT_UGURU_FAN_MAX			15300 /* RPM */
/* Bank1 sensor types */
#घोषणा ABIT_UGURU_IN_SENSOR			0
#घोषणा ABIT_UGURU_TEMP_SENSOR			1
#घोषणा ABIT_UGURU_NC				2
/*
 * In many हालs we need to रुको क्रम the uGuru to reach a certain status, most
 * of the समय it will reach this status within 30 - 90 ISA पढ़ोs, and thus we
 * can best busy रुको. This define gives the total amount of पढ़ोs to try.
 */
#घोषणा ABIT_UGURU_WAIT_TIMEOUT			125
/*
 * However someबार older versions of the uGuru seem to be distracted and they
 * करो not respond क्रम a दीर्घ समय. To handle this we sleep beक्रमe each of the
 * last ABIT_UGURU_WAIT_TIMEOUT_SLEEP tries.
 */
#घोषणा ABIT_UGURU_WAIT_TIMEOUT_SLEEP		5
/*
 * Normally all expected status in abituguru_पढ़ोy, are reported after the
 * first पढ़ो, but someबार not and we need to poll.
 */
#घोषणा ABIT_UGURU_READY_TIMEOUT		5
/* Maximum 3 retries on समयकरोut पढ़ोs/ग_लिखोs, delay 200 ms beक्रमe retrying */
#घोषणा ABIT_UGURU_MAX_RETRIES			3
#घोषणा ABIT_UGURU_RETRY_DELAY			(HZ/5)
/* Maximum 2 समयouts in abituguru_update_device, iow 3 in a row is an error */
#घोषणा ABIT_UGURU_MAX_TIMEOUTS			2
/* utility macros */
#घोषणा ABIT_UGURU_NAME				"abituguru"
#घोषणा ABIT_UGURU_DEBUG(level, क्रमmat, arg...)		\
	करो अणु						\
		अगर (level <= verbose)			\
			pr_debug(क्रमmat , ## arg);	\
	पूर्ण जबतक (0)

/* Macros to help calculate the sysfs_names array length */
/*
 * sum of म_माप of: in??_input\0, in??_अणुmin,maxपूर्ण\0, in??_अणुmin,maxपूर्ण_alarm\0,
 * in??_अणुmin,maxपूर्ण_alarm_enable\0, in??_beep\0, in??_shutकरोwn\0
 */
#घोषणा ABITUGURU_IN_NAMES_LENGTH	(11 + 2 * 9 + 2 * 15 + 2 * 22 + 10 + 14)
/*
 * sum of म_माप of: temp??_input\0, temp??_max\0, temp??_crit\0,
 * temp??_alarm\0, temp??_alarm_enable\0, temp??_beep\0, temp??_shutकरोwn\0
 */
#घोषणा ABITUGURU_TEMP_NAMES_LENGTH	(13 + 11 + 12 + 13 + 20 + 12 + 16)
/*
 * sum of म_माप of: fan?_input\0, fan?_min\0, fan?_alarm\0,
 * fan?_alarm_enable\0, fan?_beep\0, fan?_shutकरोwn\0
 */
#घोषणा ABITUGURU_FAN_NAMES_LENGTH	(11 + 9 + 11 + 18 + 10 + 14)
/*
 * sum of म_माप of: pwm?_enable\0, pwm?_स्वतः_channels_temp\0,
 * pwm?_स्वतः_poपूर्णांकअणु1,2पूर्ण_pwm\0, pwm?_स्वतः_poपूर्णांकअणु1,2पूर्ण_temp\0
 */
#घोषणा ABITUGURU_PWM_NAMES_LENGTH	(12 + 24 + 2 * 21 + 2 * 22)
/* IN_NAMES_LENGTH > TEMP_NAMES_LENGTH so assume all bank1 sensors are in */
#घोषणा ABITUGURU_SYSFS_NAMES_LENGTH	( \
	ABIT_UGURU_MAX_BANK1_SENSORS * ABITUGURU_IN_NAMES_LENGTH + \
	ABIT_UGURU_MAX_BANK2_SENSORS * ABITUGURU_FAN_NAMES_LENGTH + \
	ABIT_UGURU_MAX_PWMS * ABITUGURU_PWM_NAMES_LENGTH)

/*
 * All the macros below are named identical to the oguru and oguru2 programs
 * reverse engineered by Olle Sandberg, hence the names might not be 100%
 * logical. I could come up with better names, but I prefer keeping the names
 * identical so that this driver can be compared with his work more easily.
 */
/* Two i/o-ports are used by uGuru */
#घोषणा ABIT_UGURU_BASE				0x00E0
/* Used to tell uGuru what to पढ़ो and to पढ़ो the actual data */
#घोषणा ABIT_UGURU_CMD				0x00
/* Mostly used to check अगर uGuru is busy */
#घोषणा ABIT_UGURU_DATA				0x04
#घोषणा ABIT_UGURU_REGION_LENGTH		5
/* uGuru status' */
#घोषणा ABIT_UGURU_STATUS_WRITE			0x00 /* Ready to be written */
#घोषणा ABIT_UGURU_STATUS_READ			0x01 /* Ready to be पढ़ो */
#घोषणा ABIT_UGURU_STATUS_INPUT			0x08 /* More input */
#घोषणा ABIT_UGURU_STATUS_READY			0x09 /* Ready to be written */

/* Constants */
/* in (Volt) sensors go up to 3494 mV, temp to 255000 millidegrees Celsius */
अटल स्थिर पूर्णांक abituguru_bank1_max_value[2] = अणु 3494, 255000 पूर्ण;
/*
 * Min / Max allowed values क्रम sensor2 (fan) alarm threshold, these values
 * correspond to 300-3000 RPM
 */
अटल स्थिर u8 abituguru_bank2_min_threshold = 5;
अटल स्थिर u8 abituguru_bank2_max_threshold = 50;
/*
 * Register 0 is a bitfield, 1 and 2 are pwm settings (255 = 100%), 3 and 4
 * are temperature trip poपूर्णांकs.
 */
अटल स्थिर पूर्णांक abituguru_pwm_settings_multiplier[5] = अणु 0, 1, 1, 1000, 1000 पूर्ण;
/*
 * Min / Max allowed values क्रम pwm_settings. Note: pwm1 (CPU fan) is a
 * special हाल the minimum allowed pwm% setting क्रम this is 30% (77) on
 * some MB's this special हाल is handled in the code!
 */
अटल स्थिर u8 abituguru_pwm_min[5] = अणु 0, 170, 170, 25, 25 पूर्ण;
अटल स्थिर u8 abituguru_pwm_max[5] = अणु 0, 255, 255, 75, 75 पूर्ण;


/* Insmod parameters */
अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Set to one to force detection.");
अटल पूर्णांक bank1_types[ABIT_UGURU_MAX_BANK1_SENSORS] = अणु -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
module_param_array(bank1_types, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(bank1_types, "Bank1 sensortype autodetection override:\n"
	"   -1 autodetect\n"
	"    0 volt sensor\n"
	"    1 temp sensor\n"
	"    2 not connected");
अटल पूर्णांक fan_sensors;
module_param(fan_sensors, पूर्णांक, 0);
MODULE_PARM_DESC(fan_sensors, "Number of fan sensors on the uGuru "
	"(0 = autodetect)");
अटल पूर्णांक pwms;
module_param(pwms, पूर्णांक, 0);
MODULE_PARM_DESC(pwms, "Number of PWMs on the uGuru "
	"(0 = autodetect)");

/* Default verbose is 2, since this driver is still in the testing phase */
अटल पूर्णांक verbose = 2;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "How verbose should the driver be? (0-3):\n"
	"   0 normal output\n"
	"   1 + verbose error reporting\n"
	"   2 + sensors type probing info\n"
	"   3 + retryable error reporting");


/*
 * For the Abit uGuru, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated, at the same समय when a new
 * abituguru device is allocated.
 */
काष्ठा abituguru_data अणु
	काष्ठा device *hwmon_dev;	/* hwmon रेजिस्टरed device */
	काष्ठा mutex update_lock;	/* protect access to data and uGuru */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित लघु addr;		/* uguru base address */
	अक्षर uguru_पढ़ोy;		/* is the uguru in पढ़ोy state? */
	अचिन्हित अक्षर update_समयouts;	/*
					 * number of update समयouts since last
					 * successful update
					 */

	/*
	 * The sysfs attr and their names are generated स्वतःmatically, क्रम bank1
	 * we cannot use a predefined array because we करोn't know beक्रमehand
	 * of a sensor is a volt or a temp sensor, क्रम bank2 and the pwms its
	 * easier toकरो things the same way.  For in sensors we have 9 (temp 7)
	 * sysfs entries per sensor, क्रम bank2 and pwms 6.
	 */
	काष्ठा sensor_device_attribute_2 sysfs_attr[
		ABIT_UGURU_MAX_BANK1_SENSORS * 9 +
		ABIT_UGURU_MAX_BANK2_SENSORS * 6 + ABIT_UGURU_MAX_PWMS * 6];
	/* Buffer to store the dynamically generated sysfs names */
	अक्षर sysfs_names[ABITUGURU_SYSFS_NAMES_LENGTH];

	/* Bank 1 data */
	/* number of and addresses of [0] in, [1] temp sensors */
	u8 bank1_sensors[2];
	u8 bank1_address[2][ABIT_UGURU_MAX_BANK1_SENSORS];
	u8 bank1_value[ABIT_UGURU_MAX_BANK1_SENSORS];
	/*
	 * This array holds 3 entries per sensor क्रम the bank 1 sensor settings
	 * (flags, min, max क्रम voltage / flags, warn, shutकरोwn क्रम temp).
	 */
	u8 bank1_settings[ABIT_UGURU_MAX_BANK1_SENSORS][3];
	/*
	 * Maximum value क्रम each sensor used क्रम scaling in mV/millidegrees
	 * Celsius.
	 */
	पूर्णांक bank1_max_value[ABIT_UGURU_MAX_BANK1_SENSORS];

	/* Bank 2 data, ABIT_UGURU_MAX_BANK2_SENSORS entries क्रम bank2 */
	u8 bank2_sensors; /* actual number of bank2 sensors found */
	u8 bank2_value[ABIT_UGURU_MAX_BANK2_SENSORS];
	u8 bank2_settings[ABIT_UGURU_MAX_BANK2_SENSORS][2]; /* flags, min */

	/* Alarms 2 bytes क्रम bank1, 1 byte क्रम bank2 */
	u8 alarms[3];

	/* Fan PWM (speed control) 5 bytes per PWM */
	u8 pwms; /* actual number of pwms found */
	u8 pwm_settings[ABIT_UGURU_MAX_PWMS][5];
पूर्ण;

अटल स्थिर अक्षर *never_happen = "This should never happen.";
अटल स्थिर अक्षर *report_this =
	"Please report this to the abituguru maintainer (see MAINTAINERS)";

/* रुको till the uguru is in the specअगरied state */
अटल पूर्णांक abituguru_रुको(काष्ठा abituguru_data *data, u8 state)
अणु
	पूर्णांक समयout = ABIT_UGURU_WAIT_TIMEOUT;

	जबतक (inb_p(data->addr + ABIT_UGURU_DATA) != state) अणु
		समयout--;
		अगर (समयout == 0)
			वापस -EBUSY;
		/*
		 * sleep a bit beक्रमe our last few tries, see the comment on
		 * this where ABIT_UGURU_WAIT_TIMEOUT_SLEEP is defined.
		 */
		अगर (समयout <= ABIT_UGURU_WAIT_TIMEOUT_SLEEP)
			msleep(0);
	पूर्ण
	वापस 0;
पूर्ण

/* Put the uguru in पढ़ोy क्रम input state */
अटल पूर्णांक abituguru_पढ़ोy(काष्ठा abituguru_data *data)
अणु
	पूर्णांक समयout = ABIT_UGURU_READY_TIMEOUT;

	अगर (data->uguru_पढ़ोy)
		वापस 0;

	/* Reset? / Prepare क्रम next पढ़ो/ग_लिखो cycle */
	outb(0x00, data->addr + ABIT_UGURU_DATA);

	/* Wait till the uguru is पढ़ोy */
	अगर (abituguru_रुको(data, ABIT_UGURU_STATUS_READY)) अणु
		ABIT_UGURU_DEBUG(1,
			"timeout exceeded waiting for ready state\n");
		वापस -EIO;
	पूर्ण

	/* Cmd port MUST be पढ़ो now and should contain 0xAC */
	जबतक (inb_p(data->addr + ABIT_UGURU_CMD) != 0xAC) अणु
		समयout--;
		अगर (समयout == 0) अणु
			ABIT_UGURU_DEBUG(1,
			   "CMD reg does not hold 0xAC after ready command\n");
			वापस -EIO;
		पूर्ण
		msleep(0);
	पूर्ण

	/*
	 * After this the ABIT_UGURU_DATA port should contain
	 * ABIT_UGURU_STATUS_INPUT
	 */
	समयout = ABIT_UGURU_READY_TIMEOUT;
	जबतक (inb_p(data->addr + ABIT_UGURU_DATA) != ABIT_UGURU_STATUS_INPUT) अणु
		समयout--;
		अगर (समयout == 0) अणु
			ABIT_UGURU_DEBUG(1,
				"state != more input after ready command\n");
			वापस -EIO;
		पूर्ण
		msleep(0);
	पूर्ण

	data->uguru_पढ़ोy = 1;
	वापस 0;
पूर्ण

/*
 * Send the bank and then sensor address to the uGuru क्रम the next पढ़ो/ग_लिखो
 * cycle. This function माला_लो called as the first part of a पढ़ो/ग_लिखो by
 * abituguru_पढ़ो and abituguru_ग_लिखो. This function should never be
 * called by any other function.
 */
अटल पूर्णांक abituguru_send_address(काष्ठा abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, पूर्णांक retries)
अणु
	/*
	 * assume the caller करोes error handling itself अगर it has not requested
	 * any retries, and thus be quiet.
	 */
	पूर्णांक report_errors = retries;

	क्रम (;;) अणु
		/*
		 * Make sure the uguru is पढ़ोy and then send the bank address,
		 * after this the uguru is no दीर्घer "ready".
		 */
		अगर (abituguru_पढ़ोy(data) != 0)
			वापस -EIO;
		outb(bank_addr, data->addr + ABIT_UGURU_DATA);
		data->uguru_पढ़ोy = 0;

		/*
		 * Wait till the uguru is ABIT_UGURU_STATUS_INPUT state again
		 * and send the sensor addr
		 */
		अगर (abituguru_रुको(data, ABIT_UGURU_STATUS_INPUT)) अणु
			अगर (retries) अणु
				ABIT_UGURU_DEBUG(3, "timeout exceeded "
					"waiting for more input state, %d "
					"tries remaining\n", retries);
				set_current_state(TASK_UNINTERRUPTIBLE);
				schedule_समयout(ABIT_UGURU_RETRY_DELAY);
				retries--;
				जारी;
			पूर्ण
			अगर (report_errors)
				ABIT_UGURU_DEBUG(1, "timeout exceeded "
					"waiting for more input state "
					"(bank: %d)\n", (पूर्णांक)bank_addr);
			वापस -EBUSY;
		पूर्ण
		outb(sensor_addr, data->addr + ABIT_UGURU_CMD);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Read count bytes from sensor sensor_addr in bank bank_addr and store the
 * result in buf, retry the send address part of the पढ़ो retries बार.
 */
अटल पूर्णांक abituguru_पढ़ो(काष्ठा abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, u8 *buf, पूर्णांक count, पूर्णांक retries)
अणु
	पूर्णांक i;

	/* Send the address */
	i = abituguru_send_address(data, bank_addr, sensor_addr, retries);
	अगर (i)
		वापस i;

	/* And पढ़ो the data */
	क्रम (i = 0; i < count; i++) अणु
		अगर (abituguru_रुको(data, ABIT_UGURU_STATUS_READ)) अणु
			ABIT_UGURU_DEBUG(retries ? 1 : 3,
				"timeout exceeded waiting for "
				"read state (bank: %d, sensor: %d)\n",
				(पूर्णांक)bank_addr, (पूर्णांक)sensor_addr);
			अवरोध;
		पूर्ण
		buf[i] = inb(data->addr + ABIT_UGURU_CMD);
	पूर्ण

	/* Last put the chip back in पढ़ोy state */
	abituguru_पढ़ोy(data);

	वापस i;
पूर्ण

/*
 * Write count bytes from buf to sensor sensor_addr in bank bank_addr, the send
 * address part of the ग_लिखो is always retried ABIT_UGURU_MAX_RETRIES बार.
 */
अटल पूर्णांक abituguru_ग_लिखो(काष्ठा abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, u8 *buf, पूर्णांक count)
अणु
	/*
	 * We use the पढ़ोy समयout as we have to रुको क्रम 0xAC just like the
	 * पढ़ोy function
	 */
	पूर्णांक i, समयout = ABIT_UGURU_READY_TIMEOUT;

	/* Send the address */
	i = abituguru_send_address(data, bank_addr, sensor_addr,
		ABIT_UGURU_MAX_RETRIES);
	अगर (i)
		वापस i;

	/* And ग_लिखो the data */
	क्रम (i = 0; i < count; i++) अणु
		अगर (abituguru_रुको(data, ABIT_UGURU_STATUS_WRITE)) अणु
			ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for "
				"write state (bank: %d, sensor: %d)\n",
				(पूर्णांक)bank_addr, (पूर्णांक)sensor_addr);
			अवरोध;
		पूर्ण
		outb(buf[i], data->addr + ABIT_UGURU_CMD);
	पूर्ण

	/*
	 * Now we need to रुको till the chip is पढ़ोy to be पढ़ो again,
	 * so that we can पढ़ो 0xAC as confirmation that our ग_लिखो has
	 * succeeded.
	 */
	अगर (abituguru_रुको(data, ABIT_UGURU_STATUS_READ)) अणु
		ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for read state "
			"after write (bank: %d, sensor: %d)\n", (पूर्णांक)bank_addr,
			(पूर्णांक)sensor_addr);
		वापस -EIO;
	पूर्ण

	/* Cmd port MUST be पढ़ो now and should contain 0xAC */
	जबतक (inb_p(data->addr + ABIT_UGURU_CMD) != 0xAC) अणु
		समयout--;
		अगर (समयout == 0) अणु
			ABIT_UGURU_DEBUG(1, "CMD reg does not hold 0xAC after "
				"write (bank: %d, sensor: %d)\n",
				(पूर्णांक)bank_addr, (पूर्णांक)sensor_addr);
			वापस -EIO;
		पूर्ण
		msleep(0);
	पूर्ण

	/* Last put the chip back in पढ़ोy state */
	abituguru_पढ़ोy(data);

	वापस i;
पूर्ण

/*
 * Detect sensor type. Temp and Volt sensors are enabled with
 * dअगरferent masks and will ignore enable masks not meant क्रम them.
 * This enables us to test what kind of sensor we're dealing with.
 * By setting the alarm thresholds so that we will always get an
 * alarm क्रम sensor type X and then enabling the sensor as sensor type
 * X, अगर we then get an alarm it is a sensor of type X.
 */
अटल पूर्णांक
abituguru_detect_bank1_sensor_type(काष्ठा abituguru_data *data,
				   u8 sensor_addr)
अणु
	u8 val, test_flag, buf[3];
	पूर्णांक i, ret = -ENODEV; /* error is the most common used retval :| */

	/* If overriden by the user वापस the user selected type */
	अगर (bank1_types[sensor_addr] >= ABIT_UGURU_IN_SENSOR &&
			bank1_types[sensor_addr] <= ABIT_UGURU_NC) अणु
		ABIT_UGURU_DEBUG(2, "assuming sensor type %d for bank1 sensor "
			"%d because of \"bank1_types\" module param\n",
			bank1_types[sensor_addr], (पूर्णांक)sensor_addr);
		वापस bank1_types[sensor_addr];
	पूर्ण

	/* First पढ़ो the sensor and the current settings */
	अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1, sensor_addr, &val,
			1, ABIT_UGURU_MAX_RETRIES) != 1)
		वापस -ENODEV;

	/* Test val is sane / usable क्रम sensor type detection. */
	अगर ((val < 10u) || (val > 250u)) अणु
		pr_warn("bank1-sensor: %d reading (%d) too close to limits, "
			"unable to determine sensor type, skipping sensor\n",
			(पूर्णांक)sensor_addr, (पूर्णांक)val);
		/*
		 * assume no sensor is there क्रम sensors क्रम which we can't
		 * determine the sensor type because their पढ़ोing is too बंद
		 * to their limits, this usually means no sensor is there.
		 */
		वापस ABIT_UGURU_NC;
	पूर्ण

	ABIT_UGURU_DEBUG(2, "testing bank1 sensor %d\n", (पूर्णांक)sensor_addr);
	/*
	 * Volt sensor test, enable volt low alarm, set min value ridiculously
	 * high, or vica versa अगर the पढ़ोing is very high. If its a volt
	 * sensor this should always give us an alarm.
	 */
	अगर (val <= 240u) अणु
		buf[0] = ABIT_UGURU_VOLT_LOW_ALARM_ENABLE;
		buf[1] = 245;
		buf[2] = 250;
		test_flag = ABIT_UGURU_VOLT_LOW_ALARM_FLAG;
	पूर्ण अन्यथा अणु
		buf[0] = ABIT_UGURU_VOLT_HIGH_ALARM_ENABLE;
		buf[1] = 5;
		buf[2] = 10;
		test_flag = ABIT_UGURU_VOLT_HIGH_ALARM_FLAG;
	पूर्ण

	अगर (abituguru_ग_लिखो(data, ABIT_UGURU_SENSOR_BANK1 + 2, sensor_addr,
			buf, 3) != 3)
		जाओ abituguru_detect_bank1_sensor_type_निकास;
	/*
	 * Now we need 20 ms to give the uguru समय to पढ़ो the sensors
	 * and उठाओ a voltage alarm
	 */
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(HZ/50);
	/* Check क्रम alarm and check the alarm is a volt low alarm. */
	अगर (abituguru_पढ़ो(data, ABIT_UGURU_ALARM_BANK, 0, buf, 3,
			ABIT_UGURU_MAX_RETRIES) != 3)
		जाओ abituguru_detect_bank1_sensor_type_निकास;
	अगर (buf[sensor_addr/8] & (0x01 << (sensor_addr % 8))) अणु
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1 + 1,
				sensor_addr, buf, 3,
				ABIT_UGURU_MAX_RETRIES) != 3)
			जाओ abituguru_detect_bank1_sensor_type_निकास;
		अगर (buf[0] & test_flag) अणु
			ABIT_UGURU_DEBUG(2, "  found volt sensor\n");
			ret = ABIT_UGURU_IN_SENSOR;
			जाओ abituguru_detect_bank1_sensor_type_निकास;
		पूर्ण अन्यथा
			ABIT_UGURU_DEBUG(2, "  alarm raised during volt "
				"sensor test, but volt range flag not set\n");
	पूर्ण अन्यथा
		ABIT_UGURU_DEBUG(2, "  alarm not raised during volt sensor "
			"test\n");

	/*
	 * Temp sensor test, enable sensor as a temp sensor, set beep value
	 * ridiculously low (but not too low, otherwise uguru ignores it).
	 * If its a temp sensor this should always give us an alarm.
	 */
	buf[0] = ABIT_UGURU_TEMP_HIGH_ALARM_ENABLE;
	buf[1] = 5;
	buf[2] = 10;
	अगर (abituguru_ग_लिखो(data, ABIT_UGURU_SENSOR_BANK1 + 2, sensor_addr,
			buf, 3) != 3)
		जाओ abituguru_detect_bank1_sensor_type_निकास;
	/*
	 * Now we need 50 ms to give the uguru समय to पढ़ो the sensors
	 * and उठाओ a temp alarm
	 */
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout(HZ/20);
	/* Check क्रम alarm and check the alarm is a temp high alarm. */
	अगर (abituguru_पढ़ो(data, ABIT_UGURU_ALARM_BANK, 0, buf, 3,
			ABIT_UGURU_MAX_RETRIES) != 3)
		जाओ abituguru_detect_bank1_sensor_type_निकास;
	अगर (buf[sensor_addr/8] & (0x01 << (sensor_addr % 8))) अणु
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1 + 1,
				sensor_addr, buf, 3,
				ABIT_UGURU_MAX_RETRIES) != 3)
			जाओ abituguru_detect_bank1_sensor_type_निकास;
		अगर (buf[0] & ABIT_UGURU_TEMP_HIGH_ALARM_FLAG) अणु
			ABIT_UGURU_DEBUG(2, "  found temp sensor\n");
			ret = ABIT_UGURU_TEMP_SENSOR;
			जाओ abituguru_detect_bank1_sensor_type_निकास;
		पूर्ण अन्यथा
			ABIT_UGURU_DEBUG(2, "  alarm raised during temp "
				"sensor test, but temp high flag not set\n");
	पूर्ण अन्यथा
		ABIT_UGURU_DEBUG(2, "  alarm not raised during temp sensor "
			"test\n");

	ret = ABIT_UGURU_NC;
abituguru_detect_bank1_sensor_type_निकास:
	/*
	 * Restore original settings, failing here is really BAD, it has been
	 * reported that some BIOS-es hang when entering the uGuru menu with
	 * invalid settings present in the uGuru, so we try this 3 बार.
	 */
	क्रम (i = 0; i < 3; i++)
		अगर (abituguru_ग_लिखो(data, ABIT_UGURU_SENSOR_BANK1 + 2,
				sensor_addr, data->bank1_settings[sensor_addr],
				3) == 3)
			अवरोध;
	अगर (i == 3) अणु
		pr_err("Fatal error could not restore original settings. %s %s\n",
		       never_happen, report_this);
		वापस -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * These functions try to find out how many sensors there are in bank2 and how
 * many pwms there are. The purpose of this is to make sure that we करोn't give
 * the user the possibility to change settings क्रम non-existent sensors / pwm.
 * The uGuru will happily पढ़ो / ग_लिखो whatever memory happens to be after the
 * memory storing the PWM settings when पढ़ोing/writing to a PWM which is not
 * there. Notice even अगर we detect a PWM which करोesn't exist we normally won't
 * ग_लिखो to it, unless the user tries to change the settings.
 *
 * Although the uGuru allows पढ़ोing (settings) from non existing bank2
 * sensors, my version of the uGuru करोes seem to stop writing to them, the
 * ग_लिखो function above पातs in this हाल with:
 * "CMD reg does not hold 0xAC after write"
 *
 * Notice these 2 tests are non deकाष्ठाive iow पढ़ो-only tests, otherwise
 * they would defeat their purpose. Although क्रम the bank2_sensors detection a
 * पढ़ो/ग_लिखो test would be feasible because of the reaction above, I've
 * however opted to stay on the safe side.
 */
अटल व्योम
abituguru_detect_no_bank2_sensors(काष्ठा abituguru_data *data)
अणु
	पूर्णांक i;

	अगर (fan_sensors > 0 && fan_sensors <= ABIT_UGURU_MAX_BANK2_SENSORS) अणु
		data->bank2_sensors = fan_sensors;
		ABIT_UGURU_DEBUG(2, "assuming %d fan sensors because of "
			"\"fan_sensors\" module param\n",
			(पूर्णांक)data->bank2_sensors);
		वापस;
	पूर्ण

	ABIT_UGURU_DEBUG(2, "detecting number of fan sensors\n");
	क्रम (i = 0; i < ABIT_UGURU_MAX_BANK2_SENSORS; i++) अणु
		/*
		 * 0x89 are the known used bits:
		 * -0x80 enable shutकरोwn
		 * -0x08 enable beep
		 * -0x01 enable alarm
		 * All other bits should be 0, but on some motherboards
		 * 0x40 (bit 6) is also high क्रम some of the fans??
		 */
		अगर (data->bank2_settings[i][0] & ~0xC9) अणु
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: settings[0] = %02X\n",
				i, (अचिन्हित पूर्णांक)data->bank2_settings[i][0]);
			अवरोध;
		पूर्ण

		/* check अगर the threshold is within the allowed range */
		अगर (data->bank2_settings[i][1] <
				abituguru_bank2_min_threshold) अणु
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: the threshold (%d) is "
				"below the minimum (%d)\n", i,
				(पूर्णांक)data->bank2_settings[i][1],
				(पूर्णांक)abituguru_bank2_min_threshold);
			अवरोध;
		पूर्ण
		अगर (data->bank2_settings[i][1] >
				abituguru_bank2_max_threshold) अणु
			ABIT_UGURU_DEBUG(2, "  bank2 sensor %d does not seem "
				"to be a fan sensor: the threshold (%d) is "
				"above the maximum (%d)\n", i,
				(पूर्णांक)data->bank2_settings[i][1],
				(पूर्णांक)abituguru_bank2_max_threshold);
			अवरोध;
		पूर्ण
	पूर्ण

	data->bank2_sensors = i;
	ABIT_UGURU_DEBUG(2, " found: %d fan sensors\n",
		(पूर्णांक)data->bank2_sensors);
पूर्ण

अटल व्योम
abituguru_detect_no_pwms(काष्ठा abituguru_data *data)
अणु
	पूर्णांक i, j;

	अगर (pwms > 0 && pwms <= ABIT_UGURU_MAX_PWMS) अणु
		data->pwms = pwms;
		ABIT_UGURU_DEBUG(2, "assuming %d PWM outputs because of "
			"\"pwms\" module param\n", (पूर्णांक)data->pwms);
		वापस;
	पूर्ण

	ABIT_UGURU_DEBUG(2, "detecting number of PWM outputs\n");
	क्रम (i = 0; i < ABIT_UGURU_MAX_PWMS; i++) अणु
		/*
		 * 0x80 is the enable bit and the low
		 * nibble is which temp sensor to use,
		 * the other bits should be 0
		 */
		अगर (data->pwm_settings[i][0] & ~0x8F) अणु
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: settings[0] = %02X\n",
				i, (अचिन्हित पूर्णांक)data->pwm_settings[i][0]);
			अवरोध;
		पूर्ण

		/*
		 * the low nibble must correspond to one of the temp sensors
		 * we've found
		 */
		क्रम (j = 0; j < data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR];
				j++) अणु
			अगर (data->bank1_address[ABIT_UGURU_TEMP_SENSOR][j] ==
					(data->pwm_settings[i][0] & 0x0F))
				अवरोध;
		पूर्ण
		अगर (j == data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR]) अणु
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: %d is not a valid temp "
				"sensor address\n", i,
				data->pwm_settings[i][0] & 0x0F);
			अवरोध;
		पूर्ण

		/* check अगर all other settings are within the allowed range */
		क्रम (j = 1; j < 5; j++) अणु
			u8 min;
			/* special हाल pwm1 min pwm% */
			अगर ((i == 0) && ((j == 1) || (j == 2)))
				min = 77;
			अन्यथा
				min = abituguru_pwm_min[j];
			अगर (data->pwm_settings[i][j] < min) अणु
				ABIT_UGURU_DEBUG(2, "  pwm channel %d does "
					"not seem to be a pwm channel: "
					"setting %d (%d) is below the minimum "
					"value (%d)\n", i, j,
					(पूर्णांक)data->pwm_settings[i][j],
					(पूर्णांक)min);
				जाओ abituguru_detect_no_pwms_निकास;
			पूर्ण
			अगर (data->pwm_settings[i][j] > abituguru_pwm_max[j]) अणु
				ABIT_UGURU_DEBUG(2, "  pwm channel %d does "
					"not seem to be a pwm channel: "
					"setting %d (%d) is above the maximum "
					"value (%d)\n", i, j,
					(पूर्णांक)data->pwm_settings[i][j],
					(पूर्णांक)abituguru_pwm_max[j]);
				जाओ abituguru_detect_no_pwms_निकास;
			पूर्ण
		पूर्ण

		/* check that min temp < max temp and min pwm < max pwm */
		अगर (data->pwm_settings[i][1] >= data->pwm_settings[i][2]) अणु
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: min pwm (%d) >= "
				"max pwm (%d)\n", i,
				(पूर्णांक)data->pwm_settings[i][1],
				(पूर्णांक)data->pwm_settings[i][2]);
			अवरोध;
		पूर्ण
		अगर (data->pwm_settings[i][3] >= data->pwm_settings[i][4]) अणु
			ABIT_UGURU_DEBUG(2, "  pwm channel %d does not seem "
				"to be a pwm channel: min temp (%d) >= "
				"max temp (%d)\n", i,
				(पूर्णांक)data->pwm_settings[i][3],
				(पूर्णांक)data->pwm_settings[i][4]);
			अवरोध;
		पूर्ण
	पूर्ण

abituguru_detect_no_pwms_निकास:
	data->pwms = i;
	ABIT_UGURU_DEBUG(2, " found: %d PWM outputs\n", (पूर्णांक)data->pwms);
पूर्ण

/*
 * Following are the sysfs callback functions. These functions expect:
 * sensor_device_attribute_2->index:   sensor address/offset in the bank
 * sensor_device_attribute_2->nr:      रेजिस्टर offset, biपंचांगask or NA.
 */
अटल काष्ठा abituguru_data *abituguru_update_device(काष्ठा device *dev);

अटल sमाप_प्रकार show_bank1_value(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = abituguru_update_device(dev);
	अगर (!data)
		वापस -EIO;
	वापस प्र_लिखो(buf, "%d\n", (data->bank1_value[attr->index] *
		data->bank1_max_value[attr->index] + 128) / 255);
पूर्ण

अटल sमाप_प्रकार show_bank1_setting(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		(data->bank1_settings[attr->index][attr->nr] *
		data->bank1_max_value[attr->index] + 128) / 255);
पूर्ण

अटल sमाप_प्रकार show_bank2_value(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = abituguru_update_device(dev);
	अगर (!data)
		वापस -EIO;
	वापस प्र_लिखो(buf, "%d\n", (data->bank2_value[attr->index] *
		ABIT_UGURU_FAN_MAX + 128) / 255);
पूर्ण

अटल sमाप_प्रकार show_bank2_setting(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n",
		(data->bank2_settings[attr->index][attr->nr] *
		ABIT_UGURU_FAN_MAX + 128) / 255);
पूर्ण

अटल sमाप_प्रकार store_bank1_setting(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = count;
	val = (val * 255 + data->bank1_max_value[attr->index] / 2) /
		data->bank1_max_value[attr->index];
	अगर (val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (data->bank1_settings[attr->index][attr->nr] != val) अणु
		u8 orig_val = data->bank1_settings[attr->index][attr->nr];
		data->bank1_settings[attr->index][attr->nr] = val;
		अगर (abituguru_ग_लिखो(data, ABIT_UGURU_SENSOR_BANK1 + 2,
				attr->index, data->bank1_settings[attr->index],
				3) <= attr->nr) अणु
			data->bank1_settings[attr->index][attr->nr] = orig_val;
			ret = -EIO;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_bank2_setting(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = count;
	val = (val * 255 + ABIT_UGURU_FAN_MAX / 2) / ABIT_UGURU_FAN_MAX;

	/* this check can be करोne beक्रमe taking the lock */
	अगर (val < abituguru_bank2_min_threshold ||
			val > abituguru_bank2_max_threshold)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (data->bank2_settings[attr->index][attr->nr] != val) अणु
		u8 orig_val = data->bank2_settings[attr->index][attr->nr];
		data->bank2_settings[attr->index][attr->nr] = val;
		अगर (abituguru_ग_लिखो(data, ABIT_UGURU_SENSOR_BANK2 + 2,
				attr->index, data->bank2_settings[attr->index],
				2) <= attr->nr) अणु
			data->bank2_settings[attr->index][attr->nr] = orig_val;
			ret = -EIO;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_bank1_alarm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = abituguru_update_device(dev);
	अगर (!data)
		वापस -EIO;
	/*
	 * See अगर the alarm bit क्रम this sensor is set, and अगर the
	 * alarm matches the type of alarm we're looking क्रम (क्रम volt
	 * it can be either low or high). The type is stored in a few
	 * पढ़ोonly bits in the settings part of the relevant sensor.
	 * The biपंचांगask of the type is passed to us in attr->nr.
	 */
	अगर ((data->alarms[attr->index / 8] & (0x01 << (attr->index % 8))) &&
			(data->bank1_settings[attr->index][0] & attr->nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_bank2_alarm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = abituguru_update_device(dev);
	अगर (!data)
		वापस -EIO;
	अगर (data->alarms[2] & (0x01 << attr->index))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_bank1_mask(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	अगर (data->bank1_settings[attr->index][0] & attr->nr)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_bank2_mask(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	अगर (data->bank2_settings[attr->index][0] & attr->nr)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_bank1_mask(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	sमाप_प्रकार ret;
	u8 orig_val;
	अचिन्हित दीर्घ mask;

	ret = kम_से_अदीर्घ(buf, 10, &mask);
	अगर (ret)
		वापस ret;

	ret = count;
	mutex_lock(&data->update_lock);
	orig_val = data->bank1_settings[attr->index][0];

	अगर (mask)
		data->bank1_settings[attr->index][0] |= attr->nr;
	अन्यथा
		data->bank1_settings[attr->index][0] &= ~attr->nr;

	अगर ((data->bank1_settings[attr->index][0] != orig_val) &&
			(abituguru_ग_लिखो(data,
			ABIT_UGURU_SENSOR_BANK1 + 2, attr->index,
			data->bank1_settings[attr->index], 3) < 1)) अणु
		data->bank1_settings[attr->index][0] = orig_val;
		ret = -EIO;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_bank2_mask(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	sमाप_प्रकार ret;
	u8 orig_val;
	अचिन्हित दीर्घ mask;

	ret = kम_से_अदीर्घ(buf, 10, &mask);
	अगर (ret)
		वापस ret;

	ret = count;
	mutex_lock(&data->update_lock);
	orig_val = data->bank2_settings[attr->index][0];

	अगर (mask)
		data->bank2_settings[attr->index][0] |= attr->nr;
	अन्यथा
		data->bank2_settings[attr->index][0] &= ~attr->nr;

	अगर ((data->bank2_settings[attr->index][0] != orig_val) &&
			(abituguru_ग_लिखो(data,
			ABIT_UGURU_SENSOR_BANK2 + 2, attr->index,
			data->bank2_settings[attr->index], 2) < 1)) अणु
		data->bank2_settings[attr->index][0] = orig_val;
		ret = -EIO;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

/* Fan PWM (speed control) */
अटल sमाप_प्रकार show_pwm_setting(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_settings[attr->index][attr->nr] *
		abituguru_pwm_settings_multiplier[attr->nr]);
पूर्ण

अटल sमाप_प्रकार store_pwm_setting(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	u8 min;
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = count;
	val = (val + abituguru_pwm_settings_multiplier[attr->nr] / 2) /
				abituguru_pwm_settings_multiplier[attr->nr];

	/* special हाल pwm1 min pwm% */
	अगर ((attr->index == 0) && ((attr->nr == 1) || (attr->nr == 2)))
		min = 77;
	अन्यथा
		min = abituguru_pwm_min[attr->nr];

	/* this check can be करोne beक्रमe taking the lock */
	अगर (val < min || val > abituguru_pwm_max[attr->nr])
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	/* this check needs to be करोne after taking the lock */
	अगर ((attr->nr & 1) &&
			(val >= data->pwm_settings[attr->index][attr->nr + 1]))
		ret = -EINVAL;
	अन्यथा अगर (!(attr->nr & 1) &&
			(val <= data->pwm_settings[attr->index][attr->nr - 1]))
		ret = -EINVAL;
	अन्यथा अगर (data->pwm_settings[attr->index][attr->nr] != val) अणु
		u8 orig_val = data->pwm_settings[attr->index][attr->nr];
		data->pwm_settings[attr->index][attr->nr] = val;
		अगर (abituguru_ग_लिखो(data, ABIT_UGURU_FAN_PWM + 1,
				attr->index, data->pwm_settings[attr->index],
				5) <= attr->nr) अणु
			data->pwm_settings[attr->index][attr->nr] =
				orig_val;
			ret = -EIO;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_pwm_sensor(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	पूर्णांक i;
	/*
	 * We need to walk to the temp sensor addresses to find what
	 * the userspace id of the configured temp sensor is.
	 */
	क्रम (i = 0; i < data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR]; i++)
		अगर (data->bank1_address[ABIT_UGURU_TEMP_SENSOR][i] ==
				(data->pwm_settings[attr->index][0] & 0x0F))
			वापस प्र_लिखो(buf, "%d\n", i+1);

	वापस -ENXIO;
पूर्ण

अटल sमाप_प्रकार store_pwm_sensor(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ val;
	u8 orig_val;
	u8 address;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 0 || val > data->bank1_sensors[ABIT_UGURU_TEMP_SENSOR])
		वापस -EINVAL;

	val -= 1;
	ret = count;
	mutex_lock(&data->update_lock);
	orig_val = data->pwm_settings[attr->index][0];
	address = data->bank1_address[ABIT_UGURU_TEMP_SENSOR][val];
	data->pwm_settings[attr->index][0] &= 0xF0;
	data->pwm_settings[attr->index][0] |= address;
	अगर (data->pwm_settings[attr->index][0] != orig_val) अणु
		अगर (abituguru_ग_लिखो(data, ABIT_UGURU_FAN_PWM + 1, attr->index,
				    data->pwm_settings[attr->index], 5) < 1) अणु
			data->pwm_settings[attr->index][0] = orig_val;
			ret = -EIO;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	पूर्णांक res = 0;
	अगर (data->pwm_settings[attr->index][0] & ABIT_UGURU_FAN_PWM_ENABLE)
		res = 2;
	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार store_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	u8 orig_val;
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ user_val;

	ret = kम_से_अदीर्घ(buf, 10, &user_val);
	अगर (ret)
		वापस ret;

	ret = count;
	mutex_lock(&data->update_lock);
	orig_val = data->pwm_settings[attr->index][0];
	चयन (user_val) अणु
	हाल 0:
		data->pwm_settings[attr->index][0] &=
			~ABIT_UGURU_FAN_PWM_ENABLE;
		अवरोध;
	हाल 2:
		data->pwm_settings[attr->index][0] |= ABIT_UGURU_FAN_PWM_ENABLE;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर ((data->pwm_settings[attr->index][0] != orig_val) &&
			(abituguru_ग_लिखो(data, ABIT_UGURU_FAN_PWM + 1,
			attr->index, data->pwm_settings[attr->index],
			5) < 1)) अणु
		data->pwm_settings[attr->index][0] = orig_val;
		ret = -EIO;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", ABIT_UGURU_NAME);
पूर्ण

/* Sysfs attr ढाँचाs, the real entries are generated स्वतःmatically. */
अटल स्थिर
काष्ठा sensor_device_attribute_2 abituguru_sysfs_bank1_templ[2][9] = अणु
	अणु
	SENSOR_ATTR_2(in%d_input, 0444, show_bank1_value, शून्य, 0, 0),
	SENSOR_ATTR_2(in%d_min, 0644, show_bank1_setting,
		store_bank1_setting, 1, 0),
	SENSOR_ATTR_2(in%d_min_alarm, 0444, show_bank1_alarm, शून्य,
		ABIT_UGURU_VOLT_LOW_ALARM_FLAG, 0),
	SENSOR_ATTR_2(in%d_max, 0644, show_bank1_setting,
		store_bank1_setting, 2, 0),
	SENSOR_ATTR_2(in%d_max_alarm, 0444, show_bank1_alarm, शून्य,
		ABIT_UGURU_VOLT_HIGH_ALARM_FLAG, 0),
	SENSOR_ATTR_2(in%d_beep, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(in%d_shutकरोwn, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(in%d_min_alarm_enable, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_VOLT_LOW_ALARM_ENABLE, 0),
	SENSOR_ATTR_2(in%d_max_alarm_enable, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_VOLT_HIGH_ALARM_ENABLE, 0),
	पूर्ण, अणु
	SENSOR_ATTR_2(temp%d_input, 0444, show_bank1_value, शून्य, 0, 0),
	SENSOR_ATTR_2(temp%d_alarm, 0444, show_bank1_alarm, शून्य,
		ABIT_UGURU_TEMP_HIGH_ALARM_FLAG, 0),
	SENSOR_ATTR_2(temp%d_max, 0644, show_bank1_setting,
		store_bank1_setting, 1, 0),
	SENSOR_ATTR_2(temp%d_crit, 0644, show_bank1_setting,
		store_bank1_setting, 2, 0),
	SENSOR_ATTR_2(temp%d_beep, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(temp%d_shutकरोwn, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(temp%d_alarm_enable, 0644, show_bank1_mask,
		store_bank1_mask, ABIT_UGURU_TEMP_HIGH_ALARM_ENABLE, 0),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 abituguru_sysfs_fan_templ[6] = अणु
	SENSOR_ATTR_2(fan%d_input, 0444, show_bank2_value, शून्य, 0, 0),
	SENSOR_ATTR_2(fan%d_alarm, 0444, show_bank2_alarm, शून्य, 0, 0),
	SENSOR_ATTR_2(fan%d_min, 0644, show_bank2_setting,
		store_bank2_setting, 1, 0),
	SENSOR_ATTR_2(fan%d_beep, 0644, show_bank2_mask,
		store_bank2_mask, ABIT_UGURU_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(fan%d_shutकरोwn, 0644, show_bank2_mask,
		store_bank2_mask, ABIT_UGURU_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(fan%d_alarm_enable, 0644, show_bank2_mask,
		store_bank2_mask, ABIT_UGURU_FAN_LOW_ALARM_ENABLE, 0),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 abituguru_sysfs_pwm_templ[6] = अणु
	SENSOR_ATTR_2(pwm%d_enable, 0644, show_pwm_enable,
		store_pwm_enable, 0, 0),
	SENSOR_ATTR_2(pwm%d_स्वतः_channels_temp, 0644, show_pwm_sensor,
		store_pwm_sensor, 0, 0),
	SENSOR_ATTR_2(pwm%d_स्वतः_poपूर्णांक1_pwm, 0644, show_pwm_setting,
		store_pwm_setting, 1, 0),
	SENSOR_ATTR_2(pwm%d_स्वतः_poपूर्णांक2_pwm, 0644, show_pwm_setting,
		store_pwm_setting, 2, 0),
	SENSOR_ATTR_2(pwm%d_स्वतः_poपूर्णांक1_temp, 0644, show_pwm_setting,
		store_pwm_setting, 3, 0),
	SENSOR_ATTR_2(pwm%d_स्वतः_poपूर्णांक2_temp, 0644, show_pwm_setting,
		store_pwm_setting, 4, 0),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 abituguru_sysfs_attr[] = अणु
	SENSOR_ATTR_2(name, 0444, show_name, शून्य, 0, 0),
पूर्ण;

अटल पूर्णांक abituguru_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा abituguru_data *data;
	पूर्णांक i, j, used, sysfs_names_मुक्त, sysfs_attr_i, res = -ENODEV;
	अक्षर *sysfs_filename;

	/*
	 * El weirकरो probe order, to keep the sysfs order identical to the
	 * BIOS and winकरोw-appliction listing order.
	 */
	अटल स्थिर u8 probe_order[ABIT_UGURU_MAX_BANK1_SENSORS] = अणु
		0x00, 0x01, 0x03, 0x04, 0x0A, 0x08, 0x0E, 0x02,
		0x09, 0x06, 0x05, 0x0B, 0x0F, 0x0D, 0x07, 0x0C पूर्ण;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा abituguru_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	/* See अगर the uGuru is पढ़ोy */
	अगर (inb_p(data->addr + ABIT_UGURU_DATA) == ABIT_UGURU_STATUS_INPUT)
		data->uguru_पढ़ोy = 1;

	/*
	 * Completely पढ़ो the uGuru this has 2 purposes:
	 * - testपढ़ो / see अगर one really is there.
	 * - make an in memory copy of all the uguru settings क्रम future use.
	 */
	अगर (abituguru_पढ़ो(data, ABIT_UGURU_ALARM_BANK, 0,
			data->alarms, 3, ABIT_UGURU_MAX_RETRIES) != 3)
		जाओ abituguru_probe_error;

	क्रम (i = 0; i < ABIT_UGURU_MAX_BANK1_SENSORS; i++) अणु
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1, i,
				&data->bank1_value[i], 1,
				ABIT_UGURU_MAX_RETRIES) != 1)
			जाओ abituguru_probe_error;
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1+1, i,
				data->bank1_settings[i], 3,
				ABIT_UGURU_MAX_RETRIES) != 3)
			जाओ abituguru_probe_error;
	पूर्ण
	/*
	 * Note: We करोn't know how many bank2 sensors / pwms there really are,
	 * but in order to "detect" this we need to पढ़ो the maximum amount
	 * anyways. If we पढ़ो sensors/pwms not there we'll just पढ़ो crap
	 * this can't hurt. We need the detection because we don't want
	 * unwanted ग_लिखोs, which will hurt!
	 */
	क्रम (i = 0; i < ABIT_UGURU_MAX_BANK2_SENSORS; i++) अणु
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK2, i,
				&data->bank2_value[i], 1,
				ABIT_UGURU_MAX_RETRIES) != 1)
			जाओ abituguru_probe_error;
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK2+1, i,
				data->bank2_settings[i], 2,
				ABIT_UGURU_MAX_RETRIES) != 2)
			जाओ abituguru_probe_error;
	पूर्ण
	क्रम (i = 0; i < ABIT_UGURU_MAX_PWMS; i++) अणु
		अगर (abituguru_पढ़ो(data, ABIT_UGURU_FAN_PWM, i,
				data->pwm_settings[i], 5,
				ABIT_UGURU_MAX_RETRIES) != 5)
			जाओ abituguru_probe_error;
	पूर्ण
	data->last_updated = jअगरfies;

	/* Detect sensor types and fill the sysfs attr क्रम bank1 */
	sysfs_attr_i = 0;
	sysfs_filename = data->sysfs_names;
	sysfs_names_मुक्त = ABITUGURU_SYSFS_NAMES_LENGTH;
	क्रम (i = 0; i < ABIT_UGURU_MAX_BANK1_SENSORS; i++) अणु
		res = abituguru_detect_bank1_sensor_type(data, probe_order[i]);
		अगर (res < 0)
			जाओ abituguru_probe_error;
		अगर (res == ABIT_UGURU_NC)
			जारी;

		/* res 1 (temp) sensors have 7 sysfs entries, 0 (in) 9 */
		क्रम (j = 0; j < (res ? 7 : 9); j++) अणु
			used = snम_लिखो(sysfs_filename, sysfs_names_मुक्त,
				abituguru_sysfs_bank1_templ[res][j].dev_attr.
				attr.name, data->bank1_sensors[res] + res)
				+ 1;
			data->sysfs_attr[sysfs_attr_i] =
				abituguru_sysfs_bank1_templ[res][j];
			data->sysfs_attr[sysfs_attr_i].dev_attr.attr.name =
				sysfs_filename;
			data->sysfs_attr[sysfs_attr_i].index = probe_order[i];
			sysfs_filename += used;
			sysfs_names_मुक्त -= used;
			sysfs_attr_i++;
		पूर्ण
		data->bank1_max_value[probe_order[i]] =
			abituguru_bank1_max_value[res];
		data->bank1_address[res][data->bank1_sensors[res]] =
			probe_order[i];
		data->bank1_sensors[res]++;
	पूर्ण
	/* Detect number of sensors and fill the sysfs attr क्रम bank2 (fans) */
	abituguru_detect_no_bank2_sensors(data);
	क्रम (i = 0; i < data->bank2_sensors; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(abituguru_sysfs_fan_templ); j++) अणु
			used = snम_लिखो(sysfs_filename, sysfs_names_मुक्त,
				abituguru_sysfs_fan_templ[j].dev_attr.attr.name,
				i + 1) + 1;
			data->sysfs_attr[sysfs_attr_i] =
				abituguru_sysfs_fan_templ[j];
			data->sysfs_attr[sysfs_attr_i].dev_attr.attr.name =
				sysfs_filename;
			data->sysfs_attr[sysfs_attr_i].index = i;
			sysfs_filename += used;
			sysfs_names_मुक्त -= used;
			sysfs_attr_i++;
		पूर्ण
	पूर्ण
	/* Detect number of sensors and fill the sysfs attr क्रम pwms */
	abituguru_detect_no_pwms(data);
	क्रम (i = 0; i < data->pwms; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(abituguru_sysfs_pwm_templ); j++) अणु
			used = snम_लिखो(sysfs_filename, sysfs_names_मुक्त,
				abituguru_sysfs_pwm_templ[j].dev_attr.attr.name,
				i + 1) + 1;
			data->sysfs_attr[sysfs_attr_i] =
				abituguru_sysfs_pwm_templ[j];
			data->sysfs_attr[sysfs_attr_i].dev_attr.attr.name =
				sysfs_filename;
			data->sysfs_attr[sysfs_attr_i].index = i;
			sysfs_filename += used;
			sysfs_names_मुक्त -= used;
			sysfs_attr_i++;
		पूर्ण
	पूर्ण
	/* Fail safe check, this should never happen! */
	अगर (sysfs_names_मुक्त < 0) अणु
		pr_err("Fatal error ran out of space for sysfs attr names. %s %s",
		       never_happen, report_this);
		res = -ENAMETOOLONG;
		जाओ abituguru_probe_error;
	पूर्ण
	pr_info("found Abit uGuru\n");

	/* Register sysfs hooks */
	क्रम (i = 0; i < sysfs_attr_i; i++) अणु
		res = device_create_file(&pdev->dev,
					 &data->sysfs_attr[i].dev_attr);
		अगर (res)
			जाओ abituguru_probe_error;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(abituguru_sysfs_attr); i++) अणु
		res = device_create_file(&pdev->dev,
					 &abituguru_sysfs_attr[i].dev_attr);
		अगर (res)
			जाओ abituguru_probe_error;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (!IS_ERR(data->hwmon_dev))
		वापस 0; /* success */

	res = PTR_ERR(data->hwmon_dev);
abituguru_probe_error:
	क्रम (i = 0; data->sysfs_attr[i].dev_attr.attr.name; i++)
		device_हटाओ_file(&pdev->dev, &data->sysfs_attr[i].dev_attr);
	क्रम (i = 0; i < ARRAY_SIZE(abituguru_sysfs_attr); i++)
		device_हटाओ_file(&pdev->dev,
			&abituguru_sysfs_attr[i].dev_attr);
	वापस res;
पूर्ण

अटल पूर्णांक abituguru_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा abituguru_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	क्रम (i = 0; data->sysfs_attr[i].dev_attr.attr.name; i++)
		device_हटाओ_file(&pdev->dev, &data->sysfs_attr[i].dev_attr);
	क्रम (i = 0; i < ARRAY_SIZE(abituguru_sysfs_attr); i++)
		device_हटाओ_file(&pdev->dev,
			&abituguru_sysfs_attr[i].dev_attr);

	वापस 0;
पूर्ण

अटल काष्ठा abituguru_data *abituguru_update_device(काष्ठा device *dev)
अणु
	पूर्णांक i, err;
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	/* fake a complete successful पढ़ो अगर no update necessary. */
	अक्षर success = 1;

	mutex_lock(&data->update_lock);
	अगर (समय_after(jअगरfies, data->last_updated + HZ)) अणु
		success = 0;
		err = abituguru_पढ़ो(data, ABIT_UGURU_ALARM_BANK, 0,
				     data->alarms, 3, 0);
		अगर (err != 3)
			जाओ LEAVE_UPDATE;
		क्रम (i = 0; i < ABIT_UGURU_MAX_BANK1_SENSORS; i++) अणु
			err = abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1,
					     i, &data->bank1_value[i], 1, 0);
			अगर (err != 1)
				जाओ LEAVE_UPDATE;
			err = abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK1 + 1,
					     i, data->bank1_settings[i], 3, 0);
			अगर (err != 3)
				जाओ LEAVE_UPDATE;
		पूर्ण
		क्रम (i = 0; i < data->bank2_sensors; i++) अणु
			err = abituguru_पढ़ो(data, ABIT_UGURU_SENSOR_BANK2, i,
					     &data->bank2_value[i], 1, 0);
			अगर (err != 1)
				जाओ LEAVE_UPDATE;
		पूर्ण
		/* success! */
		success = 1;
		data->update_समयouts = 0;
LEAVE_UPDATE:
		/* handle समयout condition */
		अगर (!success && (err == -EBUSY || err >= 0)) अणु
			/* No overflow please */
			अगर (data->update_समयouts < 255u)
				data->update_समयouts++;
			अगर (data->update_समयouts <= ABIT_UGURU_MAX_TIMEOUTS) अणु
				ABIT_UGURU_DEBUG(3, "timeout exceeded, will "
					"try again next update\n");
				/* Just a समयout, fake a successful पढ़ो */
				success = 1;
			पूर्ण अन्यथा
				ABIT_UGURU_DEBUG(1, "timeout exceeded %d "
					"times waiting for more input state\n",
					(पूर्णांक)data->update_समयouts);
		पूर्ण
		/* On success set last_updated */
		अगर (success)
			data->last_updated = jअगरfies;
	पूर्ण
	mutex_unlock(&data->update_lock);

	अगर (success)
		वापस data;
	अन्यथा
		वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक abituguru_suspend(काष्ठा device *dev)
अणु
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	/*
	 * make sure all communications with the uguru are करोne and no new
	 * ones are started
	 */
	mutex_lock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक abituguru_resume(काष्ठा device *dev)
अणु
	काष्ठा abituguru_data *data = dev_get_drvdata(dev);
	/* See अगर the uGuru is still पढ़ोy */
	अगर (inb_p(data->addr + ABIT_UGURU_DATA) != ABIT_UGURU_STATUS_INPUT)
		data->uguru_पढ़ोy = 0;
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(abituguru_pm, abituguru_suspend, abituguru_resume);
#घोषणा ABIT_UGURU_PM	(&abituguru_pm)
#अन्यथा
#घोषणा ABIT_UGURU_PM	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver abituguru_driver = अणु
	.driver = अणु
		.name	= ABIT_UGURU_NAME,
		.pm	= ABIT_UGURU_PM,
	पूर्ण,
	.probe		= abituguru_probe,
	.हटाओ		= abituguru_हटाओ,
पूर्ण;

अटल पूर्णांक __init abituguru_detect(व्योम)
अणु
	/*
	 * See अगर there is an uguru there. After a reboot uGuru will hold 0x00
	 * at DATA and 0xAC, when this driver has alपढ़ोy been loaded once
	 * DATA will hold 0x08. For most uGuru's CMD will hold 0xAC in either
	 * scenario but some will hold 0x00.
	 * Some uGuru's initially hold 0x09 at DATA and will only hold 0x08
	 * after पढ़ोing CMD first, so CMD must be पढ़ो first!
	 */
	u8 cmd_val = inb_p(ABIT_UGURU_BASE + ABIT_UGURU_CMD);
	u8 data_val = inb_p(ABIT_UGURU_BASE + ABIT_UGURU_DATA);
	अगर (((data_val == 0x00) || (data_val == 0x08)) &&
	    ((cmd_val == 0x00) || (cmd_val == 0xAC)))
		वापस ABIT_UGURU_BASE;

	ABIT_UGURU_DEBUG(2, "no Abit uGuru found, data = 0x%02X, cmd = "
		"0x%02X\n", (अचिन्हित पूर्णांक)data_val, (अचिन्हित पूर्णांक)cmd_val);

	अगर (क्रमce) अणु
		pr_info("Assuming Abit uGuru is present because of \"force\" parameter\n");
		वापस ABIT_UGURU_BASE;
	पूर्ण

	/* No uGuru found */
	वापस -ENODEV;
पूर्ण

अटल काष्ठा platक्रमm_device *abituguru_pdev;

अटल पूर्णांक __init abituguru_init(व्योम)
अणु
	पूर्णांक address, err;
	काष्ठा resource res = अणु .flags = IORESOURCE_IO पूर्ण;
	स्थिर अक्षर *board_venकरोr = dmi_get_प्रणाली_info(DMI_BOARD_VENDOR);

	/* safety check, refuse to load on non Abit motherboards */
	अगर (!क्रमce && (!board_venकरोr ||
			म_भेद(board_venकरोr, "http://www.abit.com.tw/")))
		वापस -ENODEV;

	address = abituguru_detect();
	अगर (address < 0)
		वापस address;

	err = platक्रमm_driver_रेजिस्टर(&abituguru_driver);
	अगर (err)
		जाओ निकास;

	abituguru_pdev = platक्रमm_device_alloc(ABIT_UGURU_NAME, address);
	अगर (!abituguru_pdev) अणु
		pr_err("Device allocation failed\n");
		err = -ENOMEM;
		जाओ निकास_driver_unरेजिस्टर;
	पूर्ण

	res.start = address;
	res.end = address + ABIT_UGURU_REGION_LENGTH - 1;
	res.name = ABIT_UGURU_NAME;

	err = platक्रमm_device_add_resources(abituguru_pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(abituguru_pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(abituguru_pdev);
निकास_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&abituguru_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास abituguru_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(abituguru_pdev);
	platक्रमm_driver_unरेजिस्टर(&abituguru_driver);
पूर्ण

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Abit uGuru Sensor device");
MODULE_LICENSE("GPL");

module_init(abituguru_init);
module_निकास(abituguru_निकास);
