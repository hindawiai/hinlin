<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * abituguru3.c
 *
 * Copyright (c) 2006-2008 Hans de Goede <hdegoede@redhat.com>
 * Copyright (c) 2008 Alistair John Strachan <alistair@devzero.co.uk>
 */
/*
 * This driver supports the sensor part of revision 3 of the custom Abit uGuru
 * chip found on newer Abit uGuru motherboards. Note: because of lack of specs
 * only पढ़ोing the sensors and their settings is supported.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
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

/* uGuru3 bank addresses */
#घोषणा ABIT_UGURU3_SETTINGS_BANK		0x01
#घोषणा ABIT_UGURU3_SENSORS_BANK		0x08
#घोषणा ABIT_UGURU3_MISC_BANK			0x09
#घोषणा ABIT_UGURU3_ALARMS_START		0x1E
#घोषणा ABIT_UGURU3_SETTINGS_START		0x24
#घोषणा ABIT_UGURU3_VALUES_START		0x80
#घोषणा ABIT_UGURU3_BOARD_ID			0x0A
/* uGuru3 sensor bank flags */			     /* Alarm अगर: */
#घोषणा ABIT_UGURU3_TEMP_HIGH_ALARM_ENABLE	0x01 /*  temp over warn */
#घोषणा ABIT_UGURU3_VOLT_HIGH_ALARM_ENABLE	0x02 /*  volt over max */
#घोषणा ABIT_UGURU3_VOLT_LOW_ALARM_ENABLE	0x04 /*  volt under min */
#घोषणा ABIT_UGURU3_TEMP_HIGH_ALARM_FLAG	0x10 /* temp is over warn */
#घोषणा ABIT_UGURU3_VOLT_HIGH_ALARM_FLAG	0x20 /* volt is over max */
#घोषणा ABIT_UGURU3_VOLT_LOW_ALARM_FLAG		0x40 /* volt is under min */
#घोषणा ABIT_UGURU3_FAN_LOW_ALARM_ENABLE	0x01 /*   fan under min */
#घोषणा ABIT_UGURU3_BEEP_ENABLE			0x08 /* beep अगर alarm */
#घोषणा ABIT_UGURU3_SHUTDOWN_ENABLE		0x80 /* shutकरोwn अगर alarm */
/* sensor types */
#घोषणा ABIT_UGURU3_IN_SENSOR			0
#घोषणा ABIT_UGURU3_TEMP_SENSOR			1
#घोषणा ABIT_UGURU3_FAN_SENSOR			2

/*
 * Timeouts / Retries, अगर these turn out to need a lot of fiddling we could
 * convert them to params. Determined by trial and error. I assume this is
 * cpu-speed independent, since the ISA-bus and not the CPU should be the
 * bottleneck.
 */
#घोषणा ABIT_UGURU3_WAIT_TIMEOUT		250
/*
 * Normally the 0xAC at the end of synchronize() is reported after the
 * first पढ़ो, but someबार not and we need to poll
 */
#घोषणा ABIT_UGURU3_SYNCHRONIZE_TIMEOUT		5
/* utility macros */
#घोषणा ABIT_UGURU3_NAME			"abituguru3"
#घोषणा ABIT_UGURU3_DEBUG(क्रमmat, arg...)		\
	करो अणु						\
		अगर (verbose)				\
			pr_debug(क्रमmat , ## arg);	\
	पूर्ण जबतक (0)

/* Macros to help calculate the sysfs_names array length */
#घोषणा ABIT_UGURU3_MAX_NO_SENSORS 26
/*
 * sum of म_माप +1 of: in??_input\0, in??_अणुmin,maxपूर्ण\0, in??_अणुmin,maxपूर्ण_alarm\0,
 * in??_अणुmin,maxपूर्ण_alarm_enable\0, in??_beep\0, in??_shutकरोwn\0, in??_label\0
 */
#घोषणा ABIT_UGURU3_IN_NAMES_LENGTH \
				(11 + 2 * 9 + 2 * 15 + 2 * 22 + 10 + 14 + 11)
/*
 * sum of म_माप +1 of: temp??_input\0, temp??_max\0, temp??_crit\0,
 * temp??_alarm\0, temp??_alarm_enable\0, temp??_beep\0, temp??_shutकरोwn\0,
 * temp??_label\0
 */
#घोषणा ABIT_UGURU3_TEMP_NAMES_LENGTH (13 + 11 + 12 + 13 + 20 + 12 + 16 + 13)
/*
 * sum of म_माप +1 of: fan??_input\0, fan??_min\0, fan??_alarm\0,
 * fan??_alarm_enable\0, fan??_beep\0, fan??_shutकरोwn\0, fan??_label\0
 */
#घोषणा ABIT_UGURU3_FAN_NAMES_LENGTH (12 + 10 + 12 + 19 + 11 + 15 + 12)
/*
 * Worst हाल scenario 16 in sensors (दीर्घest names_length) and the rest
 * temp sensors (second दीर्घest names_length).
 */
#घोषणा ABIT_UGURU3_SYSFS_NAMES_LENGTH (16 * ABIT_UGURU3_IN_NAMES_LENGTH + \
	(ABIT_UGURU3_MAX_NO_SENSORS - 16) * ABIT_UGURU3_TEMP_NAMES_LENGTH)

/*
 * All the macros below are named identical to the खोलोguru2 program
 * reverse engineered by Louis Kruger, hence the names might not be 100%
 * logical. I could come up with better names, but I prefer keeping the names
 * identical so that this driver can be compared with his work more easily.
 */
/* Two i/o-ports are used by uGuru */
#घोषणा ABIT_UGURU3_BASE			0x00E0
#घोषणा ABIT_UGURU3_CMD				0x00
#घोषणा ABIT_UGURU3_DATA			0x04
#घोषणा ABIT_UGURU3_REGION_LENGTH		5
/*
 * The रुको_xxx functions वापस this on success and the last contents
 * of the DATA रेजिस्टर (0-255) on failure.
 */
#घोषणा ABIT_UGURU3_SUCCESS			-1
/* uGuru status flags */
#घोषणा ABIT_UGURU3_STATUS_READY_FOR_READ	0x01
#घोषणा ABIT_UGURU3_STATUS_BUSY			0x02


/* Structures */
काष्ठा abituguru3_sensor_info अणु
	स्थिर अक्षर *name;
	पूर्णांक port;
	पूर्णांक type;
	पूर्णांक multiplier;
	पूर्णांक भागisor;
	पूर्णांक offset;
पूर्ण;

/* Aव्योम use of flexible array members */
#घोषणा ABIT_UGURU3_MAX_DMI_NAMES 2

काष्ठा abituguru3_motherboard_info अणु
	u16 id;
	स्थिर अक्षर *dmi_name[ABIT_UGURU3_MAX_DMI_NAMES + 1];
	/* + 1 -> end of sensors indicated by a sensor with name == शून्य */
	काष्ठा abituguru3_sensor_info sensors[ABIT_UGURU3_MAX_NO_SENSORS + 1];
पूर्ण;

/*
 * For the Abit uGuru, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated, at the same समय when a new
 * abituguru3 device is allocated.
 */
काष्ठा abituguru3_data अणु
	काष्ठा device *hwmon_dev;	/* hwmon रेजिस्टरed device */
	काष्ठा mutex update_lock;	/* protect access to data and uGuru */
	अचिन्हित लघु addr;		/* uguru base address */
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/*
	 * For convenience the sysfs attr and their names are generated
	 * स्वतःmatically. We have max 10 entries per sensor (क्रम in sensors)
	 */
	काष्ठा sensor_device_attribute_2 sysfs_attr[ABIT_UGURU3_MAX_NO_SENSORS
		* 10];

	/* Buffer to store the dynamically generated sysfs names */
	अक्षर sysfs_names[ABIT_UGURU3_SYSFS_NAMES_LENGTH];

	/* Poपूर्णांकer to the sensors info क्रम the detected motherboard */
	स्थिर काष्ठा abituguru3_sensor_info *sensors;

	/*
	 * The abituguru3 supports up to 48 sensors, and thus has रेजिस्टरs
	 * sets क्रम 48 sensors, क्रम convenience reasons / simplicity of the
	 * code we always पढ़ो and store all रेजिस्टरs क्रम all 48 sensors
	 */

	/* Alarms क्रम all 48 sensors (1 bit per sensor) */
	u8 alarms[48/8];

	/* Value of all 48 sensors */
	u8 value[48];

	/*
	 * Settings of all 48 sensors, note in and temp sensors (the first 32
	 * sensors) have 3 bytes of settings, जबतक fans only have 2 bytes,
	 * क्रम convenience we use 3 bytes क्रम all sensors
	 */
	u8 settings[48][3];
पूर्ण;


/* Constants */
अटल स्थिर काष्ठा abituguru3_motherboard_info abituguru3_motherboards[] = अणु
	अणु 0x000C, अणु शून्य पूर्ण /* Unknown, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS FAN",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x000D, अणु शून्य पूर्ण /* Abit AW8, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		37, 2, 60, 1, 0 पूर्ण,
		अणु "AUX4 Fan",		38, 2, 60, 1, 0 पूर्ण,
		अणु "AUX5 Fan",		39, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x000E, अणु शून्य पूर्ण /* AL-8, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x000F, अणु शून्य पूर्ण /* Unknown, need DMI string */, अणु

		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0010, अणु शून्य पूर्ण /* Abit NI8 SLI GR, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "NB 1.4V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "SB 1.5V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "SYS",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "OTES1 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0011, अणु "AT8 32X", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VDDA 2.5V",	 6, 0, 20, 1, 0 पूर्ण,
		अणु "NB 1.8V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "NB 1.8V Dual",	 5, 0, 10, 1, 0 पूर्ण,
		अणु "HTV 1.2",		 3, 0, 10, 1, 0 पूर्ण,
		अणु "PCIE 1.2V",		12, 0, 10, 1, 0 पूर्ण,
		अणु "NB 1.2V",		13, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "NB",			25, 1, 1, 1, 0 पूर्ण,
		अणु "System",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		27, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		37, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0012, अणु शून्य पूर्ण /* Abit AN8 32X, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "HyperTransport",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VDDA 2.5V",	 5, 0, 20, 1, 0 पूर्ण,
		अणु "NB",			 4, 0, 10, 1, 0 पूर्ण,
		अणु "SB",			 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "SYS",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0013, अणु शून्य पूर्ण /* Abit AW8D, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		37, 2, 60, 1, 0 पूर्ण,
		अणु "AUX4 Fan",		38, 2, 60, 1, 0 पूर्ण,
		अणु "AUX5 Fan",		39, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0014, अणु "AB9", "AB9 Pro", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 10, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0015, अणु शून्य पूर्ण /* Unknown, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "HyperTransport",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VDDA 2.5V",	 5, 0, 20, 1, 0 पूर्ण,
		अणु "NB",			 4, 0, 10, 1, 0 पूर्ण,
		अणु "SB",			 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "SYS",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0016, अणु "AW9D-MAX", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 2.5V",		 5, 0, 20, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "NB Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		37, 2, 60, 1, 0 पूर्ण,
		अणु "OTES1 Fan",		38, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0017, अणु शून्य पूर्ण /* Unknown, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "HyperTransport",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VDDA 2.5V",	 6, 0, 20, 1, 0 पूर्ण,
		अणु "NB 1.8V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "NB 1.2V ",		13, 0, 10, 1, 0 पूर्ण,
		अणु "SB 1.2V",		 5, 0, 10, 1, 0 पूर्ण,
		अणु "PCIE 1.2V",		12, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "ATX +3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "ATX 5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		27, 1, 1, 1, 0 पूर्ण,
		अणु "CPU FAN",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS FAN",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 FAN",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 FAN",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 FAN",		37, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0018, अणु "AB9 QuadGT", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT",		 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 1.25V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "ICHIO 1.5V",		 5, 0, 10, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase5",		30, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0019, अणु "IN9 32X MAX", शून्य पूर्ण, अणु
		अणु "CPU Core",		 7, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		13, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		14, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT",		 3, 0, 20, 1, 0 पूर्ण,
		अणु "NB 1.2V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "SB 1.5V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "HyperTransport",	 5, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	12, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "ATX +3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "ATX 5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase5",		30, 1, 1, 1, 0 पूर्ण,
		अणु "CPU FAN",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS FAN",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 FAN",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 FAN",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 FAN",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x001A, अणु "IP35 Pro", "IP35 Pro XE", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT 1.2V",	 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 1.25V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "ICHIO 1.5V",		 5, 0, 10, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase5",		30, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु "AUX4 Fan",		37, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x001B, अणु शून्य पूर्ण /* Unknown, need DMI string */, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR3",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR3 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT",		 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 1.25V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "ICHIO 1.5V",		 5, 0, 10, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase5",		30, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x001C, अणु "IX38 QuadGT", शून्य पूर्ण, अणु
		अणु "CPU Core",		 0, 0, 10, 1, 0 पूर्ण,
		अणु "DDR2",		 1, 0, 20, 1, 0 पूर्ण,
		अणु "DDR2 VTT",		 2, 0, 10, 1, 0 पूर्ण,
		अणु "CPU VTT",		 3, 0, 10, 1, 0 पूर्ण,
		अणु "MCH 1.25V",		 4, 0, 10, 1, 0 पूर्ण,
		अणु "ICHIO 1.5V",		 5, 0, 10, 1, 0 पूर्ण,
		अणु "ICH 1.05V",		 6, 0, 10, 1, 0 पूर्ण,
		अणु "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 पूर्ण,
		अणु "ATX +5V",		 9, 0, 30, 1, 0 पूर्ण,
		अणु "+3.3V",		10, 0, 20, 1, 0 पूर्ण,
		अणु "5VSB",		11, 0, 30, 1, 0 पूर्ण,
		अणु "CPU",		24, 1, 1, 1, 0 पूर्ण,
		अणु "System",		25, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase1",		26, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase2",		27, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase3",		28, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase4",		29, 1, 1, 1, 0 पूर्ण,
		अणु "PWM Phase5",		30, 1, 1, 1, 0 पूर्ण,
		अणु "CPU Fan",		32, 2, 60, 1, 0 पूर्ण,
		अणु "SYS Fan",		34, 2, 60, 1, 0 पूर्ण,
		अणु "AUX1 Fan",		33, 2, 60, 1, 0 पूर्ण,
		अणु "AUX2 Fan",		35, 2, 60, 1, 0 पूर्ण,
		अणु "AUX3 Fan",		36, 2, 60, 1, 0 पूर्ण,
		अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण
	पूर्ण,
	अणु 0x0000, अणु शून्य पूर्ण, अणु अणु शून्य, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण
पूर्ण;


/* Insmod parameters */
अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Set to one to force detection.");
/* Default verbose is 1, since this driver is still in the testing phase */
अटल bool verbose = 1;
module_param(verbose, bool, 0644);
MODULE_PARM_DESC(verbose, "Enable/disable verbose error reporting");

अटल स्थिर अक्षर *never_happen = "This should never happen.";
अटल स्थिर अक्षर *report_this =
	"Please report this to the abituguru3 maintainer (see MAINTAINERS)";

/* रुको जबतक the uguru is busy (usually after a ग_लिखो) */
अटल पूर्णांक abituguru3_रुको_जबतक_busy(काष्ठा abituguru3_data *data)
अणु
	u8 x;
	पूर्णांक समयout = ABIT_UGURU3_WAIT_TIMEOUT;

	जबतक ((x = inb_p(data->addr + ABIT_UGURU3_DATA)) &
			ABIT_UGURU3_STATUS_BUSY) अणु
		समयout--;
		अगर (समयout == 0)
			वापस x;
		/*
		 * sleep a bit beक्रमe our last try, to give the uGuru3 one
		 * last chance to respond.
		 */
		अगर (समयout == 1)
			msleep(1);
	पूर्ण
	वापस ABIT_UGURU3_SUCCESS;
पूर्ण

/* रुको till uguru is पढ़ोy to be पढ़ो */
अटल पूर्णांक abituguru3_रुको_क्रम_पढ़ो(काष्ठा abituguru3_data *data)
अणु
	u8 x;
	पूर्णांक समयout = ABIT_UGURU3_WAIT_TIMEOUT;

	जबतक (!((x = inb_p(data->addr + ABIT_UGURU3_DATA)) &
			ABIT_UGURU3_STATUS_READY_FOR_READ)) अणु
		समयout--;
		अगर (समयout == 0)
			वापस x;
		/*
		 * sleep a bit beक्रमe our last try, to give the uGuru3 one
		 * last chance to respond.
		 */
		अगर (समयout == 1)
			msleep(1);
	पूर्ण
	वापस ABIT_UGURU3_SUCCESS;
पूर्ण

/*
 * This synchronizes us with the uGuru3's protocol state machine, this
 * must be करोne beक्रमe each command.
 */
अटल पूर्णांक abituguru3_synchronize(काष्ठा abituguru3_data *data)
अणु
	पूर्णांक x, समयout = ABIT_UGURU3_SYNCHRONIZE_TIMEOUT;

	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("synchronize timeout during initial busy "
			"wait, status: 0x%02x\n", x);
		वापस -EIO;
	पूर्ण

	outb(0x20, data->addr + ABIT_UGURU3_DATA);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x20, "
			"status: 0x%02x\n", x);
		वापस -EIO;
	पूर्ण

	outb(0x10, data->addr + ABIT_UGURU3_CMD);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x10, "
			"status: 0x%02x\n", x);
		वापस -EIO;
	पूर्ण

	outb(0x00, data->addr + ABIT_UGURU3_CMD);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x00, "
			"status: 0x%02x\n", x);
		वापस -EIO;
	पूर्ण

	x = abituguru3_रुको_क्रम_पढ़ो(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("synchronize timeout waiting for read, "
			"status: 0x%02x\n", x);
		वापस -EIO;
	पूर्ण

	जबतक ((x = inb(data->addr + ABIT_UGURU3_CMD)) != 0xAC) अणु
		समयout--;
		अगर (समयout == 0) अणु
			ABIT_UGURU3_DEBUG("synchronize timeout cmd does not "
				"hold 0xAC after synchronize, cmd: 0x%02x\n",
				x);
			वापस -EIO;
		पूर्ण
		msleep(1);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read count bytes from sensor sensor_addr in bank bank_addr and store the
 * result in buf
 */
अटल पूर्णांक abituguru3_पढ़ो(काष्ठा abituguru3_data *data, u8 bank, u8 offset,
	u8 count, u8 *buf)
अणु
	पूर्णांक i, x;

	x = abituguru3_synchronize(data);
	अगर (x)
		वापस x;

	outb(0x1A, data->addr + ABIT_UGURU3_DATA);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending 0x1A, status: 0x%02x\n", (अचिन्हित पूर्णांक)bank,
			(अचिन्हित पूर्णांक)offset, x);
		वापस -EIO;
	पूर्ण

	outb(bank, data->addr + ABIT_UGURU3_CMD);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the bank, status: 0x%02x\n",
			(अचिन्हित पूर्णांक)bank, (अचिन्हित पूर्णांक)offset, x);
		वापस -EIO;
	पूर्ण

	outb(offset, data->addr + ABIT_UGURU3_CMD);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the offset, status: 0x%02x\n",
			(अचिन्हित पूर्णांक)bank, (अचिन्हित पूर्णांक)offset, x);
		वापस -EIO;
	पूर्ण

	outb(count, data->addr + ABIT_UGURU3_CMD);
	x = abituguru3_रुको_जबतक_busy(data);
	अगर (x != ABIT_UGURU3_SUCCESS) अणु
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the count, status: 0x%02x\n",
			(अचिन्हित पूर्णांक)bank, (अचिन्हित पूर्णांक)offset, x);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		x = abituguru3_रुको_क्रम_पढ़ो(data);
		अगर (x != ABIT_UGURU3_SUCCESS) अणु
			ABIT_UGURU3_DEBUG("timeout reading byte %d from "
				"0x%02x:0x%02x, status: 0x%02x\n", i,
				(अचिन्हित पूर्णांक)bank, (अचिन्हित पूर्णांक)offset, x);
			अवरोध;
		पूर्ण
		buf[i] = inb(data->addr + ABIT_UGURU3_CMD);
	पूर्ण
	वापस i;
पूर्ण

/*
 * Sensor settings are stored 1 byte per offset with the bytes
 * placed add consecutive offsets.
 */
अटल पूर्णांक abituguru3_पढ़ो_increment_offset(काष्ठा abituguru3_data *data,
					    u8 bank, u8 offset, u8 count,
					    u8 *buf, पूर्णांक offset_count)
अणु
	पूर्णांक i, x;

	क्रम (i = 0; i < offset_count; i++) अणु
		x = abituguru3_पढ़ो(data, bank, offset + i, count,
				    buf + i * count);
		अगर (x != count) अणु
			अगर (x < 0)
				वापस x;
			वापस i * count + x;
		पूर्ण
	पूर्ण

	वापस i * count;
पूर्ण

/*
 * Following are the sysfs callback functions. These functions expect:
 * sensor_device_attribute_2->index:   index पूर्णांकo the data->sensors array
 * sensor_device_attribute_2->nr:      रेजिस्टर offset, biपंचांगask or NA.
 */
अटल काष्ठा abituguru3_data *abituguru3_update_device(काष्ठा device *dev);

अटल sमाप_प्रकार show_value(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक value;
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru3_data *data = abituguru3_update_device(dev);
	स्थिर काष्ठा abituguru3_sensor_info *sensor;

	अगर (!data)
		वापस -EIO;

	sensor = &data->sensors[attr->index];

	/* are we पढ़ोing a setting, or is this a normal पढ़ो? */
	अगर (attr->nr)
		value = data->settings[sensor->port][attr->nr];
	अन्यथा
		value = data->value[sensor->port];

	/* convert the value */
	value = (value * sensor->multiplier) / sensor->भागisor +
		sensor->offset;

	/*
	 * alternatively we could update the sensors settings काष्ठा क्रम this,
	 * but then its contents would dअगरfer from the winकरोws sw ini files
	 */
	अगर (sensor->type == ABIT_UGURU3_TEMP_SENSOR)
		value *= 1000;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक port;
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru3_data *data = abituguru3_update_device(dev);

	अगर (!data)
		वापस -EIO;

	port = data->sensors[attr->index].port;

	/*
	 * See अगर the alarm bit क्रम this sensor is set and अगर a biपंचांगask is
	 * given in attr->nr also check अगर the alarm matches the type of alarm
	 * we're looking क्रम (क्रम volt it can be either low or high). The type
	 * is stored in a few पढ़ोonly bits in the settings of the sensor.
	 */
	अगर ((data->alarms[port / 8] & (0x01 << (port % 8))) &&
			(!attr->nr || (data->settings[port][0] & attr->nr)))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_mask(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru3_data *data = dev_get_drvdata(dev);

	अगर (data->settings[data->sensors[attr->index].port][0] & attr->nr)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_label(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा abituguru3_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->sensors[attr->index].name);
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", ABIT_UGURU3_NAME);
पूर्ण

/* Sysfs attr ढाँचाs, the real entries are generated स्वतःmatically. */
अटल स्थिर
काष्ठा sensor_device_attribute_2 abituguru3_sysfs_templ[3][10] = अणु अणु
	SENSOR_ATTR_2(in%d_input, 0444, show_value, शून्य, 0, 0),
	SENSOR_ATTR_2(in%d_min, 0444, show_value, शून्य, 1, 0),
	SENSOR_ATTR_2(in%d_max, 0444, show_value, शून्य, 2, 0),
	SENSOR_ATTR_2(in%d_min_alarm, 0444, show_alarm, शून्य,
		ABIT_UGURU3_VOLT_LOW_ALARM_FLAG, 0),
	SENSOR_ATTR_2(in%d_max_alarm, 0444, show_alarm, शून्य,
		ABIT_UGURU3_VOLT_HIGH_ALARM_FLAG, 0),
	SENSOR_ATTR_2(in%d_beep, 0444, show_mask, शून्य,
		ABIT_UGURU3_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(in%d_shutकरोwn, 0444, show_mask, शून्य,
		ABIT_UGURU3_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(in%d_min_alarm_enable, 0444, show_mask, शून्य,
		ABIT_UGURU3_VOLT_LOW_ALARM_ENABLE, 0),
	SENSOR_ATTR_2(in%d_max_alarm_enable, 0444, show_mask, शून्य,
		ABIT_UGURU3_VOLT_HIGH_ALARM_ENABLE, 0),
	SENSOR_ATTR_2(in%d_label, 0444, show_label, शून्य, 0, 0)
	पूर्ण, अणु
	SENSOR_ATTR_2(temp%d_input, 0444, show_value, शून्य, 0, 0),
	SENSOR_ATTR_2(temp%d_max, 0444, show_value, शून्य, 1, 0),
	SENSOR_ATTR_2(temp%d_crit, 0444, show_value, शून्य, 2, 0),
	SENSOR_ATTR_2(temp%d_alarm, 0444, show_alarm, शून्य, 0, 0),
	SENSOR_ATTR_2(temp%d_beep, 0444, show_mask, शून्य,
		ABIT_UGURU3_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(temp%d_shutकरोwn, 0444, show_mask, शून्य,
		ABIT_UGURU3_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(temp%d_alarm_enable, 0444, show_mask, शून्य,
		ABIT_UGURU3_TEMP_HIGH_ALARM_ENABLE, 0),
	SENSOR_ATTR_2(temp%d_label, 0444, show_label, शून्य, 0, 0)
	पूर्ण, अणु
	SENSOR_ATTR_2(fan%d_input, 0444, show_value, शून्य, 0, 0),
	SENSOR_ATTR_2(fan%d_min, 0444, show_value, शून्य, 1, 0),
	SENSOR_ATTR_2(fan%d_alarm, 0444, show_alarm, शून्य, 0, 0),
	SENSOR_ATTR_2(fan%d_beep, 0444, show_mask, शून्य,
		ABIT_UGURU3_BEEP_ENABLE, 0),
	SENSOR_ATTR_2(fan%d_shutकरोwn, 0444, show_mask, शून्य,
		ABIT_UGURU3_SHUTDOWN_ENABLE, 0),
	SENSOR_ATTR_2(fan%d_alarm_enable, 0444, show_mask, शून्य,
		ABIT_UGURU3_FAN_LOW_ALARM_ENABLE, 0),
	SENSOR_ATTR_2(fan%d_label, 0444, show_label, शून्य, 0, 0)
पूर्ण पूर्ण;

अटल काष्ठा sensor_device_attribute_2 abituguru3_sysfs_attr[] = अणु
	SENSOR_ATTR_2(name, 0444, show_name, शून्य, 0, 0),
पूर्ण;

अटल पूर्णांक abituguru3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर पूर्णांक no_sysfs_attr[3] = अणु 10, 8, 7 पूर्ण;
	पूर्णांक sensor_index[3] = अणु 0, 1, 1 पूर्ण;
	काष्ठा abituguru3_data *data;
	पूर्णांक i, j, type, used, sysfs_names_मुक्त, sysfs_attr_i, res = -ENODEV;
	अक्षर *sysfs_filename;
	u8 buf[2];
	u16 id;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा abituguru3_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	/* Read the motherboard ID */
	i = abituguru3_पढ़ो(data, ABIT_UGURU3_MISC_BANK, ABIT_UGURU3_BOARD_ID,
			    2, buf);
	अगर (i != 2)
		जाओ abituguru3_probe_error;

	/* Completely पढ़ो the uGuru to see अगर one really is there */
	अगर (!abituguru3_update_device(&pdev->dev))
		जाओ abituguru3_probe_error;

	/* lookup the ID in our motherboard table */
	id = ((u16)buf[0] << 8) | (u16)buf[1];
	क्रम (i = 0; abituguru3_motherboards[i].id; i++)
		अगर (abituguru3_motherboards[i].id == id)
			अवरोध;
	अगर (!abituguru3_motherboards[i].id) अणु
		pr_err("error unknown motherboard ID: %04X. %s\n",
		       (अचिन्हित पूर्णांक)id, report_this);
		जाओ abituguru3_probe_error;
	पूर्ण
	data->sensors = abituguru3_motherboards[i].sensors;

	pr_info("found Abit uGuru3, motherboard ID: %04X\n", (अचिन्हित पूर्णांक)id);

	/* Fill the sysfs attr array */
	sysfs_attr_i = 0;
	sysfs_filename = data->sysfs_names;
	sysfs_names_मुक्त = ABIT_UGURU3_SYSFS_NAMES_LENGTH;
	क्रम (i = 0; data->sensors[i].name; i++) अणु
		/* Fail safe check, this should never happen! */
		अगर (i >= ABIT_UGURU3_MAX_NO_SENSORS) अणु
			pr_err("Fatal error motherboard has more sensors then ABIT_UGURU3_MAX_NO_SENSORS. %s %s\n",
			       never_happen, report_this);
			res = -ENAMETOOLONG;
			जाओ abituguru3_probe_error;
		पूर्ण
		type = data->sensors[i].type;
		क्रम (j = 0; j < no_sysfs_attr[type]; j++) अणु
			used = snम_लिखो(sysfs_filename, sysfs_names_मुक्त,
				abituguru3_sysfs_templ[type][j].dev_attr.attr.
				name, sensor_index[type]) + 1;
			data->sysfs_attr[sysfs_attr_i] =
				abituguru3_sysfs_templ[type][j];
			data->sysfs_attr[sysfs_attr_i].dev_attr.attr.name =
				sysfs_filename;
			data->sysfs_attr[sysfs_attr_i].index = i;
			sysfs_filename += used;
			sysfs_names_मुक्त -= used;
			sysfs_attr_i++;
		पूर्ण
		sensor_index[type]++;
	पूर्ण
	/* Fail safe check, this should never happen! */
	अगर (sysfs_names_मुक्त < 0) अणु
		pr_err("Fatal error ran out of space for sysfs attr names. %s %s\n",
		       never_happen, report_this);
		res = -ENAMETOOLONG;
		जाओ abituguru3_probe_error;
	पूर्ण

	/* Register sysfs hooks */
	क्रम (i = 0; i < sysfs_attr_i; i++)
		अगर (device_create_file(&pdev->dev,
				&data->sysfs_attr[i].dev_attr))
			जाओ abituguru3_probe_error;
	क्रम (i = 0; i < ARRAY_SIZE(abituguru3_sysfs_attr); i++)
		अगर (device_create_file(&pdev->dev,
				&abituguru3_sysfs_attr[i].dev_attr))
			जाओ abituguru3_probe_error;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		res = PTR_ERR(data->hwmon_dev);
		जाओ abituguru3_probe_error;
	पूर्ण

	वापस 0; /* success */

abituguru3_probe_error:
	क्रम (i = 0; data->sysfs_attr[i].dev_attr.attr.name; i++)
		device_हटाओ_file(&pdev->dev, &data->sysfs_attr[i].dev_attr);
	क्रम (i = 0; i < ARRAY_SIZE(abituguru3_sysfs_attr); i++)
		device_हटाओ_file(&pdev->dev,
			&abituguru3_sysfs_attr[i].dev_attr);
	वापस res;
पूर्ण

अटल पूर्णांक abituguru3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा abituguru3_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	क्रम (i = 0; data->sysfs_attr[i].dev_attr.attr.name; i++)
		device_हटाओ_file(&pdev->dev, &data->sysfs_attr[i].dev_attr);
	क्रम (i = 0; i < ARRAY_SIZE(abituguru3_sysfs_attr); i++)
		device_हटाओ_file(&pdev->dev,
			&abituguru3_sysfs_attr[i].dev_attr);
	वापस 0;
पूर्ण

अटल काष्ठा abituguru3_data *abituguru3_update_device(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा abituguru3_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);
	अगर (!data->valid || समय_after(jअगरfies, data->last_updated + HZ)) अणु
		/* Clear data->valid जबतक updating */
		data->valid = 0;
		/* Read alarms */
		अगर (abituguru3_पढ़ो_increment_offset(data,
				ABIT_UGURU3_SETTINGS_BANK,
				ABIT_UGURU3_ALARMS_START,
				1, data->alarms, 48/8) != (48/8))
			जाओ LEAVE_UPDATE;
		/* Read in and temp sensors (3 byte settings / sensor) */
		क्रम (i = 0; i < 32; i++) अणु
			अगर (abituguru3_पढ़ो(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + i,
					1, &data->value[i]) != 1)
				जाओ LEAVE_UPDATE;
			अगर (abituguru3_पढ़ो_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + i * 3,
					1,
					data->settings[i], 3) != 3)
				जाओ LEAVE_UPDATE;
		पूर्ण
		/* Read temp sensors (2 byte settings / sensor) */
		क्रम (i = 0; i < 16; i++) अणु
			अगर (abituguru3_पढ़ो(data, ABIT_UGURU3_SENSORS_BANK,
					ABIT_UGURU3_VALUES_START + 32 + i,
					1, &data->value[32 + i]) != 1)
				जाओ LEAVE_UPDATE;
			अगर (abituguru3_पढ़ो_increment_offset(data,
					ABIT_UGURU3_SETTINGS_BANK,
					ABIT_UGURU3_SETTINGS_START + 32 * 3 +
						i * 2, 1,
					data->settings[32 + i], 2) != 2)
				जाओ LEAVE_UPDATE;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
LEAVE_UPDATE:
	mutex_unlock(&data->update_lock);
	अगर (data->valid)
		वापस data;
	अन्यथा
		वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक abituguru3_suspend(काष्ठा device *dev)
अणु
	काष्ठा abituguru3_data *data = dev_get_drvdata(dev);
	/*
	 * make sure all communications with the uguru3 are करोne and no new
	 * ones are started
	 */
	mutex_lock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक abituguru3_resume(काष्ठा device *dev)
अणु
	काष्ठा abituguru3_data *data = dev_get_drvdata(dev);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(abituguru3_pm, abituguru3_suspend, abituguru3_resume);
#घोषणा ABIT_UGURU3_PM	(&abituguru3_pm)
#अन्यथा
#घोषणा ABIT_UGURU3_PM	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver abituguru3_driver = अणु
	.driver = अणु
		.name	= ABIT_UGURU3_NAME,
		.pm	= ABIT_UGURU3_PM
	पूर्ण,
	.probe	= abituguru3_probe,
	.हटाओ	= abituguru3_हटाओ,
पूर्ण;

अटल पूर्णांक __init abituguru3_dmi_detect(व्योम)
अणु
	स्थिर अक्षर *board_venकरोr, *board_name;
	पूर्णांक i, err = (क्रमce) ? 1 : -ENODEV;
	स्थिर अक्षर *स्थिर *dmi_name;
	माप_प्रकार sublen;

	board_venकरोr = dmi_get_प्रणाली_info(DMI_BOARD_VENDOR);
	अगर (!board_venकरोr || म_भेद(board_venकरोr, "http://www.abit.com.tw/"))
		वापस err;

	board_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
	अगर (!board_name)
		वापस err;

	/*
	 * At the moment, we करोn't care about the part of the venकरोr
	 * DMI string contained in brackets. Truncate the string at
	 * the first occurrence of a bracket. Trim any trailing space
	 * from the substring.
	 */
	sublen = म_खोज(board_name, "(");
	जबतक (sublen > 0 && board_name[sublen - 1] == ' ')
		sublen--;

	क्रम (i = 0; abituguru3_motherboards[i].id; i++) अणु
		dmi_name = abituguru3_motherboards[i].dmi_name;
		क्रम ( ; *dmi_name; dmi_name++) अणु
			अगर (म_माप(*dmi_name) != sublen)
				जारी;
			अगर (!strnहालcmp(board_name, *dmi_name, sublen))
				वापस 0;
		पूर्ण
	पूर्ण

	/* No match found */
	वापस 1;
पूर्ण

/*
 * FIXME: Manual detection should die eventually; we need to collect stable
 *        DMI model names first beक्रमe we can rely entirely on CONFIG_DMI.
 */

अटल पूर्णांक __init abituguru3_detect(व्योम)
अणु
	/*
	 * See अगर there is an uguru3 there. An idle uGuru3 will hold 0x00 or
	 * 0x08 at DATA and 0xAC at CMD. Someबार the uGuru3 will hold 0x05
	 * or 0x55 at CMD instead, why is unknown.
	 */
	u8 data_val = inb_p(ABIT_UGURU3_BASE + ABIT_UGURU3_DATA);
	u8 cmd_val = inb_p(ABIT_UGURU3_BASE + ABIT_UGURU3_CMD);
	अगर (((data_val == 0x00) || (data_val == 0x08)) &&
			((cmd_val == 0xAC) || (cmd_val == 0x05) ||
			 (cmd_val == 0x55)))
		वापस 0;

	ABIT_UGURU3_DEBUG("no Abit uGuru3 found, data = 0x%02X, cmd = "
		"0x%02X\n", (अचिन्हित पूर्णांक)data_val, (अचिन्हित पूर्णांक)cmd_val);

	अगर (क्रमce) अणु
		pr_info("Assuming Abit uGuru3 is present because of \"force\" parameter\n");
		वापस 0;
	पूर्ण

	/* No uGuru3 found */
	वापस -ENODEV;
पूर्ण

अटल काष्ठा platक्रमm_device *abituguru3_pdev;

अटल पूर्णांक __init abituguru3_init(व्योम)
अणु
	काष्ठा resource res = अणु .flags = IORESOURCE_IO पूर्ण;
	पूर्णांक err;

	/* Attempt DMI detection first */
	err = abituguru3_dmi_detect();
	अगर (err < 0)
		वापस err;

	/*
	 * Fall back to manual detection अगर there was no exact
	 * board name match, or क्रमce was specअगरied.
	 */
	अगर (err > 0) अणु
		err = abituguru3_detect();
		अगर (err)
			वापस err;

		pr_warn("this motherboard was not detected using DMI. "
			"Please send the output of \"dmidecode\" to the abituguru3 maintainer (see MAINTAINERS)\n");
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&abituguru3_driver);
	अगर (err)
		जाओ निकास;

	abituguru3_pdev = platक्रमm_device_alloc(ABIT_UGURU3_NAME,
						ABIT_UGURU3_BASE);
	अगर (!abituguru3_pdev) अणु
		pr_err("Device allocation failed\n");
		err = -ENOMEM;
		जाओ निकास_driver_unरेजिस्टर;
	पूर्ण

	res.start = ABIT_UGURU3_BASE;
	res.end = ABIT_UGURU3_BASE + ABIT_UGURU3_REGION_LENGTH - 1;
	res.name = ABIT_UGURU3_NAME;

	err = platक्रमm_device_add_resources(abituguru3_pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(abituguru3_pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(abituguru3_pdev);
निकास_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&abituguru3_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास abituguru3_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(abituguru3_pdev);
	platक्रमm_driver_unरेजिस्टर(&abituguru3_driver);
पूर्ण

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Abit uGuru3 Sensor device");
MODULE_LICENSE("GPL");

module_init(abituguru3_init);
module_निकास(abituguru3_निकास);
