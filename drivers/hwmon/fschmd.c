<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * fschmd.c
 *
 * Copyright (C) 2007 - 2009 Hans de Goede <hdegoede@redhat.com>
 */

/*
 *  Merged Fujitsu Siemens hwmon driver, supporting the Poseiकरोn, Hermes,
 *  Scylla, Heracles, Heimdall, Hades and Syleus chips
 *
 *  Based on the original 2.4 fscscy, 2.6 fscpos, 2.6 fscher and 2.6
 *  (candidate) fschmd drivers:
 *  Copyright (C) 2006 Thilo Cestonaro
 *			<thilo.cestonaro.बाह्यal@fujitsu-siemens.com>
 *  Copyright (C) 2004, 2005 Stefan Ott <stefan@desire.ch>
 *  Copyright (C) 2003, 2004 Reinhard Nissl <rnissl@gmx.de>
 *  Copyright (c) 2001 Martin Knoblauch <mkn@teraport.de, knobi@knobisoft.de>
 *  Copyright (C) 2000 Hermann Jung <hej@odn.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/dmi.h>
#समावेश <linux/fs.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kref.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x73, I2C_CLIENT_END पूर्ण;

/* Insmod parameters */
अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

क्रमागत chips अणु fscpos, fscher, fscscy, fschrc, fschmd, fschds, fscsyl पूर्ण;

/*
 * The FSCHMD रेजिस्टरs and other defines
 */

/* chip identअगरication */
#घोषणा FSCHMD_REG_IDENT_0		0x00
#घोषणा FSCHMD_REG_IDENT_1		0x01
#घोषणा FSCHMD_REG_IDENT_2		0x02
#घोषणा FSCHMD_REG_REVISION		0x03

/* global control and status */
#घोषणा FSCHMD_REG_EVENT_STATE		0x04
#घोषणा FSCHMD_REG_CONTROL		0x05

#घोषणा FSCHMD_CONTROL_ALERT_LED	0x01

/* watchकरोg */
अटल स्थिर u8 FSCHMD_REG_WDOG_CONTROL[7] = अणु
	0x21, 0x21, 0x21, 0x21, 0x21, 0x28, 0x28 पूर्ण;
अटल स्थिर u8 FSCHMD_REG_WDOG_STATE[7] = अणु
	0x23, 0x23, 0x23, 0x23, 0x23, 0x29, 0x29 पूर्ण;
अटल स्थिर u8 FSCHMD_REG_WDOG_PRESET[7] = अणु
	0x28, 0x28, 0x28, 0x28, 0x28, 0x2a, 0x2a पूर्ण;

#घोषणा FSCHMD_WDOG_CONTROL_TRIGGER	0x10
#घोषणा FSCHMD_WDOG_CONTROL_STARTED	0x10 /* the same as trigger */
#घोषणा FSCHMD_WDOG_CONTROL_STOP	0x20
#घोषणा FSCHMD_WDOG_CONTROL_RESOLUTION	0x40

#घोषणा FSCHMD_WDOG_STATE_CARDRESET	0x02

/* voltages, weird order is to keep the same order as the old drivers */
अटल स्थिर u8 FSCHMD_REG_VOLT[7][6] = अणु
	अणु 0x45, 0x42, 0x48 पूर्ण,				/* pos */
	अणु 0x45, 0x42, 0x48 पूर्ण,				/* her */
	अणु 0x45, 0x42, 0x48 पूर्ण,				/* scy */
	अणु 0x45, 0x42, 0x48 पूर्ण,				/* hrc */
	अणु 0x45, 0x42, 0x48 पूर्ण,				/* hmd */
	अणु 0x21, 0x20, 0x22 पूर्ण,				/* hds */
	अणु 0x21, 0x20, 0x22, 0x23, 0x24, 0x25 पूर्ण,		/* syl */
पूर्ण;

अटल स्थिर पूर्णांक FSCHMD_NO_VOLT_SENSORS[7] = अणु 3, 3, 3, 3, 3, 3, 6 पूर्ण;

/*
 * minimum pwm at which the fan is driven (pwm can be increased depending on
 * the temp. Notice that क्रम the scy some fans share there minimum speed.
 * Also notice that with the scy the sensor order is dअगरferent than with the
 * other chips, this order was in the 2.4 driver and kept क्रम consistency.
 */
अटल स्थिर u8 FSCHMD_REG_FAN_MIN[7][7] = अणु
	अणु 0x55, 0x65 पूर्ण,					/* pos */
	अणु 0x55, 0x65, 0xb5 पूर्ण,				/* her */
	अणु 0x65, 0x65, 0x55, 0xa5, 0x55, 0xa5 पूर्ण,		/* scy */
	अणु 0x55, 0x65, 0xa5, 0xb5 पूर्ण,			/* hrc */
	अणु 0x55, 0x65, 0xa5, 0xb5, 0xc5 पूर्ण,		/* hmd */
	अणु 0x55, 0x65, 0xa5, 0xb5, 0xc5 पूर्ण,		/* hds */
	अणु 0x54, 0x64, 0x74, 0x84, 0x94, 0xa4, 0xb4 पूर्ण,	/* syl */
पूर्ण;

/* actual fan speed */
अटल स्थिर u8 FSCHMD_REG_FAN_ACT[7][7] = अणु
	अणु 0x0e, 0x6b, 0xab पूर्ण,				/* pos */
	अणु 0x0e, 0x6b, 0xbb पूर्ण,				/* her */
	अणु 0x6b, 0x6c, 0x0e, 0xab, 0x5c, 0xbb पूर्ण,		/* scy */
	अणु 0x0e, 0x6b, 0xab, 0xbb पूर्ण,			/* hrc */
	अणु 0x5b, 0x6b, 0xab, 0xbb, 0xcb पूर्ण,		/* hmd */
	अणु 0x5b, 0x6b, 0xab, 0xbb, 0xcb पूर्ण,		/* hds */
	अणु 0x57, 0x67, 0x77, 0x87, 0x97, 0xa7, 0xb7 पूर्ण,	/* syl */
पूर्ण;

/* fan status रेजिस्टरs */
अटल स्थिर u8 FSCHMD_REG_FAN_STATE[7][7] = अणु
	अणु 0x0d, 0x62, 0xa2 पूर्ण,				/* pos */
	अणु 0x0d, 0x62, 0xb2 पूर्ण,				/* her */
	अणु 0x62, 0x61, 0x0d, 0xa2, 0x52, 0xb2 पूर्ण,		/* scy */
	अणु 0x0d, 0x62, 0xa2, 0xb2 पूर्ण,			/* hrc */
	अणु 0x52, 0x62, 0xa2, 0xb2, 0xc2 पूर्ण,		/* hmd */
	अणु 0x52, 0x62, 0xa2, 0xb2, 0xc2 पूर्ण,		/* hds */
	अणु 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0 पूर्ण,	/* syl */
पूर्ण;

/* fan ripple / भागider रेजिस्टरs */
अटल स्थिर u8 FSCHMD_REG_FAN_RIPPLE[7][7] = अणु
	अणु 0x0f, 0x6f, 0xaf पूर्ण,				/* pos */
	अणु 0x0f, 0x6f, 0xbf पूर्ण,				/* her */
	अणु 0x6f, 0x6f, 0x0f, 0xaf, 0x0f, 0xbf पूर्ण,		/* scy */
	अणु 0x0f, 0x6f, 0xaf, 0xbf पूर्ण,			/* hrc */
	अणु 0x5f, 0x6f, 0xaf, 0xbf, 0xcf पूर्ण,		/* hmd */
	अणु 0x5f, 0x6f, 0xaf, 0xbf, 0xcf पूर्ण,		/* hds */
	अणु 0x56, 0x66, 0x76, 0x86, 0x96, 0xa6, 0xb6 पूर्ण,	/* syl */
पूर्ण;

अटल स्थिर पूर्णांक FSCHMD_NO_FAN_SENSORS[7] = अणु 3, 3, 6, 4, 5, 5, 7 पूर्ण;

/* Fan status रेजिस्टर biपंचांगasks */
#घोषणा FSCHMD_FAN_ALARM	0x04 /* called fault by FSC! */
#घोषणा FSCHMD_FAN_NOT_PRESENT	0x08
#घोषणा FSCHMD_FAN_DISABLED	0x80


/* actual temperature रेजिस्टरs */
अटल स्थिर u8 FSCHMD_REG_TEMP_ACT[7][11] = अणु
	अणु 0x64, 0x32, 0x35 पूर्ण,				/* pos */
	अणु 0x64, 0x32, 0x35 पूर्ण,				/* her */
	अणु 0x64, 0xD0, 0x32, 0x35 पूर्ण,			/* scy */
	अणु 0x64, 0x32, 0x35 पूर्ण,				/* hrc */
	अणु 0x70, 0x80, 0x90, 0xd0, 0xe0 पूर्ण,		/* hmd */
	अणु 0x70, 0x80, 0x90, 0xd0, 0xe0 पूर्ण,		/* hds */
	अणु 0x58, 0x68, 0x78, 0x88, 0x98, 0xa8,		/* syl */
	  0xb8, 0xc8, 0xd8, 0xe8, 0xf8 पूर्ण,
पूर्ण;

/* temperature state रेजिस्टरs */
अटल स्थिर u8 FSCHMD_REG_TEMP_STATE[7][11] = अणु
	अणु 0x71, 0x81, 0x91 पूर्ण,				/* pos */
	अणु 0x71, 0x81, 0x91 पूर्ण,				/* her */
	अणु 0x71, 0xd1, 0x81, 0x91 पूर्ण,			/* scy */
	अणु 0x71, 0x81, 0x91 पूर्ण,				/* hrc */
	अणु 0x71, 0x81, 0x91, 0xd1, 0xe1 पूर्ण,		/* hmd */
	अणु 0x71, 0x81, 0x91, 0xd1, 0xe1 पूर्ण,		/* hds */
	अणु 0x59, 0x69, 0x79, 0x89, 0x99, 0xa9,		/* syl */
	  0xb9, 0xc9, 0xd9, 0xe9, 0xf9 पूर्ण,
पूर्ण;

/*
 * temperature high limit रेजिस्टरs, FSC करोes not करोcument these. Proven to be
 * there with field testing on the fscher and fschrc, alपढ़ोy supported / used
 * in the fscscy 2.4 driver. FSC has confirmed that the fschmd has रेजिस्टरs
 * at these addresses, but करोesn't want to confirm they are the same as with
 * the fscher??
 */
अटल स्थिर u8 FSCHMD_REG_TEMP_LIMIT[7][11] = अणु
	अणु 0, 0, 0 पूर्ण,					/* pos */
	अणु 0x76, 0x86, 0x96 पूर्ण,				/* her */
	अणु 0x76, 0xd6, 0x86, 0x96 पूर्ण,			/* scy */
	अणु 0x76, 0x86, 0x96 पूर्ण,				/* hrc */
	अणु 0x76, 0x86, 0x96, 0xd6, 0xe6 पूर्ण,		/* hmd */
	अणु 0x76, 0x86, 0x96, 0xd6, 0xe6 पूर्ण,		/* hds */
	अणु 0x5a, 0x6a, 0x7a, 0x8a, 0x9a, 0xaa,		/* syl */
	  0xba, 0xca, 0xda, 0xea, 0xfa पूर्ण,
पूर्ण;

/*
 * These were found through experimenting with an fscher, currently they are
 * not used, but we keep them around क्रम future reference.
 * On the fscsyl AUTOP1 lives at 0x#c (so 0x5c क्रम fan1, 0x6c क्रम fan2, etc),
 * AUTOP2 lives at 0x#e, and 0x#1 is a biपंचांगask defining which temps influence
 * the fan speed.
 * अटल स्थिर u8 FSCHER_REG_TEMP_AUTOP1[] =	अणु 0x73, 0x83, 0x93 पूर्ण;
 * अटल स्थिर u8 FSCHER_REG_TEMP_AUTOP2[] =	अणु 0x75, 0x85, 0x95 पूर्ण;
 */

अटल स्थिर पूर्णांक FSCHMD_NO_TEMP_SENSORS[7] = अणु 3, 3, 4, 3, 5, 5, 11 पूर्ण;

/* temp status रेजिस्टर biपंचांगasks */
#घोषणा FSCHMD_TEMP_WORKING	0x01
#घोषणा FSCHMD_TEMP_ALERT	0x02
#घोषणा FSCHMD_TEMP_DISABLED	0x80
/* there only really is an alarm अगर the sensor is working and alert == 1 */
#घोषणा FSCHMD_TEMP_ALARM_MASK \
	(FSCHMD_TEMP_WORKING | FSCHMD_TEMP_ALERT)

/*
 * Functions declarations
 */

अटल पूर्णांक fschmd_probe(काष्ठा i2c_client *client);
अटल पूर्णांक fschmd_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info);
अटल पूर्णांक fschmd_हटाओ(काष्ठा i2c_client *client);
अटल काष्ठा fschmd_data *fschmd_update_device(काष्ठा device *dev);

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id fschmd_id[] = अणु
	अणु "fscpos", fscpos पूर्ण,
	अणु "fscher", fscher पूर्ण,
	अणु "fscscy", fscscy पूर्ण,
	अणु "fschrc", fschrc पूर्ण,
	अणु "fschmd", fschmd पूर्ण,
	अणु "fschds", fschds पूर्ण,
	अणु "fscsyl", fscsyl पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fschmd_id);

अटल काष्ठा i2c_driver fschmd_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "fschmd",
	पूर्ण,
	.probe_new	= fschmd_probe,
	.हटाओ		= fschmd_हटाओ,
	.id_table	= fschmd_id,
	.detect		= fschmd_detect,
	.address_list	= normal_i2c,
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा fschmd_data अणु
	काष्ठा i2c_client *client;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;
	काष्ठा mutex watchकरोg_lock;
	काष्ठा list_head list; /* member of the watchकरोg_data_list */
	काष्ठा kref kref;
	काष्ठा miscdevice watchकरोg_miscdev;
	क्रमागत chips kind;
	अचिन्हित दीर्घ watchकरोg_is_खोलो;
	अक्षर watchकरोg_expect_बंद;
	अक्षर watchकरोg_name[10]; /* must be unique to aव्योम sysfs conflict */
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टर values */
	u8 revision;            /* chip revision */
	u8 global_control;	/* global control रेजिस्टर */
	u8 watchकरोg_control;    /* watchकरोg control रेजिस्टर */
	u8 watchकरोg_state;      /* watchकरोg status रेजिस्टर */
	u8 watchकरोg_preset;     /* watchकरोg counter preset on trigger val */
	u8 volt[6];		/* voltage */
	u8 temp_act[11];	/* temperature */
	u8 temp_status[11];	/* status of sensor */
	u8 temp_max[11];	/* high temp limit, notice: unकरोcumented! */
	u8 fan_act[7];		/* fans revolutions per second */
	u8 fan_status[7];	/* fan status */
	u8 fan_min[7];		/* fan min value क्रम rps */
	u8 fan_ripple[7];	/* भागider क्रम rps */
पूर्ण;

/*
 * Global variables to hold inक्रमmation पढ़ो from special DMI tables, which are
 * available on FSC machines with an fscher or later chip. There is no need to
 * protect these with a lock as they are only modअगरied from our attach function
 * which always माला_लो called with the i2c-core lock held and never accessed
 * beक्रमe the attach function is करोne with them.
 */
अटल पूर्णांक dmi_mult[6] = अणु 490, 200, 100, 100, 200, 100 पूर्ण;
अटल पूर्णांक dmi_offset[6] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
अटल पूर्णांक dmi_vref = -1;

/*
 * Somewhat ugly :( global data poपूर्णांकer list with all fschmd devices, so that
 * we can find our device data as when using misc_रेजिस्टर there is no other
 * method to get to ones device data from the खोलो fop.
 */
अटल LIST_HEAD(watchकरोg_data_list);
/* Note this lock not only protect list access, but also data.kref access */
अटल DEFINE_MUTEX(watchकरोg_data_mutex);

/*
 * Release our data काष्ठा when we're detached from the i2c client *and* all
 * references to our watchकरोg device are released
 */
अटल व्योम fschmd_release_resources(काष्ठा kref *ref)
अणु
	काष्ठा fschmd_data *data = container_of(ref, काष्ठा fschmd_data, kref);
	kमुक्त(data);
पूर्ण

/*
 * Sysfs attr show / store functions
 */

अटल sमाप_प्रकार in_value_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	स्थिर पूर्णांक max_पढ़ोing[3] = अणु 14200, 6600, 3300 पूर्ण;
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	अगर (data->kind == fscher || data->kind >= fschrc)
		वापस प्र_लिखो(buf, "%d\n", (data->volt[index] * dmi_vref *
			dmi_mult[index]) / 255 + dmi_offset[index]);
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", (data->volt[index] *
			max_पढ़ोing[index] + 128) / 255);
पूर्ण


#घोषणा TEMP_FROM_REG(val)	(((val) - 128) * 1000)

अटल sमाप_प्रकार temp_value_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_act[index]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[index]));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = dev_get_drvdata(dev);
	दीर्घ v;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	v = clamp_val(v / 1000, -128, 127) + 128;

	mutex_lock(&data->update_lock);
	i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev),
		FSCHMD_REG_TEMP_LIMIT[data->kind][index], v);
	data->temp_max[index] = v;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	/* bit 0 set means sensor working ok, so no fault! */
	अगर (data->temp_status[index] & FSCHMD_TEMP_WORKING)
		वापस प्र_लिखो(buf, "0\n");
	अन्यथा
		वापस प्र_लिखो(buf, "1\n");
पूर्ण

अटल sमाप_प्रकार temp_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	अगर ((data->temp_status[index] & FSCHMD_TEMP_ALARM_MASK) ==
			FSCHMD_TEMP_ALARM_MASK)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण


#घोषणा RPM_FROM_REG(val)	((val) * 60)

अटल sमाप_प्रकार fan_value_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	वापस प्र_लिखो(buf, "%u\n", RPM_FROM_REG(data->fan_act[index]));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	/* bits 2..7 reserved => mask with 3 */
	वापस प्र_लिखो(buf, "%d\n", 1 << (data->fan_ripple[index] & 3));
पूर्ण

अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 reg;
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = dev_get_drvdata(dev);
	/* supported values: 2, 4, 8 */
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	चयन (v) अणु
	हाल 2:
		v = 1;
		अवरोध;
	हाल 4:
		v = 2;
		अवरोध;
	हाल 8:
		v = 3;
		अवरोध;
	शेष:
		dev_err(dev,
			"fan_div value %lu not supported. Choose one of 2, 4 or 8!\n",
			v);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);

	reg = i2c_smbus_पढ़ो_byte_data(to_i2c_client(dev),
		FSCHMD_REG_FAN_RIPPLE[data->kind][index]);

	/* bits 2..7 reserved => mask with 0x03 */
	reg &= ~0x03;
	reg |= v;

	i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev),
		FSCHMD_REG_FAN_RIPPLE[data->kind][index], reg);

	data->fan_ripple[index] = reg;

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	अगर (data->fan_status[index] & FSCHMD_FAN_ALARM)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार fan_fault_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	अगर (data->fan_status[index] & FSCHMD_FAN_NOT_PRESENT)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण


अटल sमाप_प्रकार pwm_स्वतः_poपूर्णांक1_pwm_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = fschmd_update_device(dev);
	पूर्णांक val = data->fan_min[index];

	/* 0 = allow turning off (except on the syl), 1-255 = 50-100% */
	अगर (val || data->kind == fscsyl)
		val = val / 2 + 128;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_poपूर्णांक1_pwm_store(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा fschmd_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	/* reg: 0 = allow turning off (except on the syl), 1-255 = 50-100% */
	अगर (v || data->kind == fscsyl) अणु
		v = clamp_val(v, 128, 255);
		v = (v - 128) * 2 + 1;
	पूर्ण

	mutex_lock(&data->update_lock);

	i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev),
		FSCHMD_REG_FAN_MIN[data->kind][index], v);
	data->fan_min[index] = v;

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण


/*
 * The FSC hwmon family has the ability to क्रमce an attached alert led to flash
 * from software, we export this as an alert_led sysfs attr
 */
अटल sमाप_प्रकार alert_led_show(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fschmd_data *data = fschmd_update_device(dev);

	अगर (data->global_control & FSCHMD_CONTROL_ALERT_LED)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार alert_led_store(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 reg;
	काष्ठा fschmd_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	reg = i2c_smbus_पढ़ो_byte_data(to_i2c_client(dev), FSCHMD_REG_CONTROL);

	अगर (v)
		reg |= FSCHMD_CONTROL_ALERT_LED;
	अन्यथा
		reg &= ~FSCHMD_CONTROL_ALERT_LED;

	i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev), FSCHMD_REG_CONTROL, reg);

	data->global_control = reg;

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(alert_led);

अटल काष्ठा sensor_device_attribute fschmd_attr[] = अणु
	SENSOR_ATTR_RO(in0_input, in_value, 0),
	SENSOR_ATTR_RO(in1_input, in_value, 1),
	SENSOR_ATTR_RO(in2_input, in_value, 2),
	SENSOR_ATTR_RO(in3_input, in_value, 3),
	SENSOR_ATTR_RO(in4_input, in_value, 4),
	SENSOR_ATTR_RO(in5_input, in_value, 5),
पूर्ण;

अटल काष्ठा sensor_device_attribute fschmd_temp_attr[] = अणु
	SENSOR_ATTR_RO(temp1_input, temp_value, 0),
	SENSOR_ATTR_RW(temp1_max, temp_max, 0),
	SENSOR_ATTR_RO(temp1_fault, temp_fault, 0),
	SENSOR_ATTR_RO(temp1_alarm, temp_alarm, 0),
	SENSOR_ATTR_RO(temp2_input, temp_value, 1),
	SENSOR_ATTR_RW(temp2_max, temp_max, 1),
	SENSOR_ATTR_RO(temp2_fault, temp_fault, 1),
	SENSOR_ATTR_RO(temp2_alarm, temp_alarm, 1),
	SENSOR_ATTR_RO(temp3_input, temp_value, 2),
	SENSOR_ATTR_RW(temp3_max, temp_max, 2),
	SENSOR_ATTR_RO(temp3_fault, temp_fault, 2),
	SENSOR_ATTR_RO(temp3_alarm, temp_alarm, 2),
	SENSOR_ATTR_RO(temp4_input, temp_value, 3),
	SENSOR_ATTR_RW(temp4_max, temp_max, 3),
	SENSOR_ATTR_RO(temp4_fault, temp_fault, 3),
	SENSOR_ATTR_RO(temp4_alarm, temp_alarm, 3),
	SENSOR_ATTR_RO(temp5_input, temp_value, 4),
	SENSOR_ATTR_RW(temp5_max, temp_max, 4),
	SENSOR_ATTR_RO(temp5_fault, temp_fault, 4),
	SENSOR_ATTR_RO(temp5_alarm, temp_alarm, 4),
	SENSOR_ATTR_RO(temp6_input, temp_value, 5),
	SENSOR_ATTR_RW(temp6_max, temp_max, 5),
	SENSOR_ATTR_RO(temp6_fault, temp_fault, 5),
	SENSOR_ATTR_RO(temp6_alarm, temp_alarm, 5),
	SENSOR_ATTR_RO(temp7_input, temp_value, 6),
	SENSOR_ATTR_RW(temp7_max, temp_max, 6),
	SENSOR_ATTR_RO(temp7_fault, temp_fault, 6),
	SENSOR_ATTR_RO(temp7_alarm, temp_alarm, 6),
	SENSOR_ATTR_RO(temp8_input, temp_value, 7),
	SENSOR_ATTR_RW(temp8_max, temp_max, 7),
	SENSOR_ATTR_RO(temp8_fault, temp_fault, 7),
	SENSOR_ATTR_RO(temp8_alarm, temp_alarm, 7),
	SENSOR_ATTR_RO(temp9_input, temp_value, 8),
	SENSOR_ATTR_RW(temp9_max, temp_max, 8),
	SENSOR_ATTR_RO(temp9_fault, temp_fault, 8),
	SENSOR_ATTR_RO(temp9_alarm, temp_alarm, 8),
	SENSOR_ATTR_RO(temp10_input, temp_value, 9),
	SENSOR_ATTR_RW(temp10_max, temp_max, 9),
	SENSOR_ATTR_RO(temp10_fault, temp_fault, 9),
	SENSOR_ATTR_RO(temp10_alarm, temp_alarm, 9),
	SENSOR_ATTR_RO(temp11_input, temp_value, 10),
	SENSOR_ATTR_RW(temp11_max, temp_max, 10),
	SENSOR_ATTR_RO(temp11_fault, temp_fault, 10),
	SENSOR_ATTR_RO(temp11_alarm, temp_alarm, 10),
पूर्ण;

अटल काष्ठा sensor_device_attribute fschmd_fan_attr[] = अणु
	SENSOR_ATTR_RO(fan1_input, fan_value, 0),
	SENSOR_ATTR_RW(fan1_भाग, fan_भाग, 0),
	SENSOR_ATTR_RO(fan1_alarm, fan_alarm, 0),
	SENSOR_ATTR_RO(fan1_fault, fan_fault, 0),
	SENSOR_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 0),
	SENSOR_ATTR_RO(fan2_input, fan_value, 1),
	SENSOR_ATTR_RW(fan2_भाग, fan_भाग, 1),
	SENSOR_ATTR_RO(fan2_alarm, fan_alarm, 1),
	SENSOR_ATTR_RO(fan2_fault, fan_fault, 1),
	SENSOR_ATTR_RW(pwm2_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 1),
	SENSOR_ATTR_RO(fan3_input, fan_value, 2),
	SENSOR_ATTR_RW(fan3_भाग, fan_भाग, 2),
	SENSOR_ATTR_RO(fan3_alarm, fan_alarm, 2),
	SENSOR_ATTR_RO(fan3_fault, fan_fault, 2),
	SENSOR_ATTR_RW(pwm3_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 2),
	SENSOR_ATTR_RO(fan4_input, fan_value, 3),
	SENSOR_ATTR_RW(fan4_भाग, fan_भाग, 3),
	SENSOR_ATTR_RO(fan4_alarm, fan_alarm, 3),
	SENSOR_ATTR_RO(fan4_fault, fan_fault, 3),
	SENSOR_ATTR_RW(pwm4_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 3),
	SENSOR_ATTR_RO(fan5_input, fan_value, 4),
	SENSOR_ATTR_RW(fan5_भाग, fan_भाग, 4),
	SENSOR_ATTR_RO(fan5_alarm, fan_alarm, 4),
	SENSOR_ATTR_RO(fan5_fault, fan_fault, 4),
	SENSOR_ATTR_RW(pwm5_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 4),
	SENSOR_ATTR_RO(fan6_input, fan_value, 5),
	SENSOR_ATTR_RW(fan6_भाग, fan_भाग, 5),
	SENSOR_ATTR_RO(fan6_alarm, fan_alarm, 5),
	SENSOR_ATTR_RO(fan6_fault, fan_fault, 5),
	SENSOR_ATTR_RW(pwm6_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 5),
	SENSOR_ATTR_RO(fan7_input, fan_value, 6),
	SENSOR_ATTR_RW(fan7_भाग, fan_भाग, 6),
	SENSOR_ATTR_RO(fan7_alarm, fan_alarm, 6),
	SENSOR_ATTR_RO(fan7_fault, fan_fault, 6),
	SENSOR_ATTR_RW(pwm7_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक1_pwm, 6),
पूर्ण;


/*
 * Watchकरोg routines
 */

अटल पूर्णांक watchकरोg_set_समयout(काष्ठा fschmd_data *data, पूर्णांक समयout)
अणु
	पूर्णांक ret, resolution;
	पूर्णांक kind = data->kind + 1; /* 0-x array index -> 1-x module param */

	/* 2 second or 60 second resolution? */
	अगर (समयout <= 510 || kind == fscpos || kind == fscscy)
		resolution = 2;
	अन्यथा
		resolution = 60;

	अगर (समयout < resolution || समयout > (resolution * 255))
		वापस -EINVAL;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	अगर (resolution == 2)
		data->watchकरोg_control &= ~FSCHMD_WDOG_CONTROL_RESOLUTION;
	अन्यथा
		data->watchकरोg_control |= FSCHMD_WDOG_CONTROL_RESOLUTION;

	data->watchकरोg_preset = DIV_ROUND_UP(समयout, resolution);

	/* Write new समयout value */
	i2c_smbus_ग_लिखो_byte_data(data->client,
		FSCHMD_REG_WDOG_PRESET[data->kind], data->watchकरोg_preset);
	/* Write new control रेजिस्टर, करो not trigger! */
	i2c_smbus_ग_लिखो_byte_data(data->client,
		FSCHMD_REG_WDOG_CONTROL[data->kind],
		data->watchकरोg_control & ~FSCHMD_WDOG_CONTROL_TRIGGER);

	ret = data->watchकरोg_preset * resolution;

leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_get_समयout(काष्ठा fschmd_data *data)
अणु
	पूर्णांक समयout;

	mutex_lock(&data->watchकरोg_lock);
	अगर (data->watchकरोg_control & FSCHMD_WDOG_CONTROL_RESOLUTION)
		समयout = data->watchकरोg_preset * 60;
	अन्यथा
		समयout = data->watchकरोg_preset * 2;
	mutex_unlock(&data->watchकरोg_lock);

	वापस समयout;
पूर्ण

अटल पूर्णांक watchकरोg_trigger(काष्ठा fschmd_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	data->watchकरोg_control |= FSCHMD_WDOG_CONTROL_TRIGGER;
	i2c_smbus_ग_लिखो_byte_data(data->client,
				  FSCHMD_REG_WDOG_CONTROL[data->kind],
				  data->watchकरोg_control);
leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_stop(काष्ठा fschmd_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	data->watchकरोg_control &= ~FSCHMD_WDOG_CONTROL_STARTED;
	/*
	 * Don't store the stop flag in our watchकरोg control रेजिस्टर copy, as
	 * its a ग_लिखो only bit (पढ़ो always वापसs 0)
	 */
	i2c_smbus_ग_लिखो_byte_data(data->client,
		FSCHMD_REG_WDOG_CONTROL[data->kind],
		data->watchकरोg_control | FSCHMD_WDOG_CONTROL_STOP);
leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fschmd_data *pos, *data = शून्य;
	पूर्णांक watchकरोg_is_खोलो;

	/*
	 * We get called from drivers/अक्षर/misc.c with misc_mtx hold, and we
	 * call misc_रेजिस्टर() from fschmd_probe() with watchकरोg_data_mutex
	 * hold, as misc_रेजिस्टर() takes the misc_mtx lock, this is a possible
	 * deadlock, so we use mutex_trylock here.
	 */
	अगर (!mutex_trylock(&watchकरोg_data_mutex))
		वापस -ERESTARTSYS;
	list_क्रम_each_entry(pos, &watchकरोg_data_list, list) अणु
		अगर (pos->watchकरोg_miscdev.minor == iminor(inode)) अणु
			data = pos;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Note we can never not have found data, so we करोn't check क्रम this */
	watchकरोg_is_खोलो = test_and_set_bit(0, &data->watchकरोg_is_खोलो);
	अगर (!watchकरोg_is_खोलो)
		kref_get(&data->kref);
	mutex_unlock(&watchकरोg_data_mutex);

	अगर (watchकरोg_is_खोलो)
		वापस -EBUSY;

	/* Start the watchकरोg */
	watchकरोg_trigger(data);
	filp->निजी_data = data;

	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक watchकरोg_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fschmd_data *data = filp->निजी_data;

	अगर (data->watchकरोg_expect_बंद) अणु
		watchकरोg_stop(data);
		data->watchकरोg_expect_बंद = 0;
	पूर्ण अन्यथा अणु
		watchकरोg_trigger(data);
		dev_crit(&data->client->dev,
			"unexpected close, not stopping watchdog!\n");
	पूर्ण

	clear_bit(0, &data->watchकरोg_is_खोलो);

	mutex_lock(&watchकरोg_data_mutex);
	kref_put(&data->kref, fschmd_release_resources);
	mutex_unlock(&watchकरोg_data_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार watchकरोg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *offset)
अणु
	पूर्णांक ret;
	काष्ठा fschmd_data *data = filp->निजी_data;

	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* Clear it in हाल it was set with a previous ग_लिखो */
			data->watchकरोg_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					data->watchकरोg_expect_बंद = 1;
			पूर्ण
		पूर्ण
		ret = watchकरोg_trigger(data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ watchकरोg_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
				WDIOF_CARDRESET,
		.identity = "FSC watchdog"
	पूर्ण;
	पूर्णांक i, ret = 0;
	काष्ठा fschmd_data *data = filp->निजी_data;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		ident.firmware_version = data->revision;
		अगर (!nowayout)
			ident.options |= WDIOF_MAGICCLOSE;
		अगर (copy_to_user((व्योम __user *)arg, &ident, माप(ident)))
			ret = -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		ret = put_user(0, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		अगर (data->watchकरोg_state & FSCHMD_WDOG_STATE_CARDRESET)
			ret = put_user(WDIOF_CARDRESET, (पूर्णांक __user *)arg);
		अन्यथा
			ret = put_user(0, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		ret = watchकरोg_trigger(data);
		अवरोध;

	हाल WDIOC_GETTIMEOUT:
		i = watchकरोg_get_समयout(data);
		ret = put_user(i, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(i, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = watchकरोg_set_समयout(data, i);
		अगर (ret > 0)
			ret = put_user(ret, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(i, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (i & WDIOS_DISABLECARD)
			ret = watchकरोg_stop(data);
		अन्यथा अगर (i & WDIOS_ENABLECARD)
			ret = watchकरोg_trigger(data);
		अन्यथा
			ret = -EINVAL;

		अवरोध;
	शेष:
		ret = -ENOTTY;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations watchकरोg_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.खोलो = watchकरोg_खोलो,
	.release = watchकरोg_release,
	.ग_लिखो = watchकरोg_ग_लिखो,
	.unlocked_ioctl = watchकरोg_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;


/*
 * Detect, रेजिस्टर, unरेजिस्टर and update device functions
 */

/*
 * DMI decode routine to पढ़ो voltage scaling factors from special DMI tables,
 * which are available on FSC machines with an fscher or later chip.
 */
अटल व्योम fschmd_dmi_decode(स्थिर काष्ठा dmi_header *header, व्योम *dummy)
अणु
	पूर्णांक i, mult[3] = अणु 0 पूर्ण, offset[3] = अणु 0 पूर्ण, vref = 0, found = 0;

	/*
	 * dmi code ugliness, we get passed the address of the contents of
	 * a complete DMI record, but in the क्रमm of a dmi_header poपूर्णांकer, in
	 * reality this address holds header->length bytes of which the header
	 * are the first 4 bytes
	 */
	u8 *dmi_data = (u8 *)header;

	/* We are looking क्रम OEM-specअगरic type 185 */
	अगर (header->type != 185)
		वापस;

	/*
	 * we are looking क्रम what Siemens calls "subtype" 19, the subtype
	 * is stored in byte 5 of the dmi block
	 */
	अगर (header->length < 5 || dmi_data[4] != 19)
		वापस;

	/*
	 * After the subtype comes 1 unknown byte and then blocks of 5 bytes,
	 * consisting of what Siemens calls an "Entity" number, followed by
	 * 2 16-bit words in LSB first order
	 */
	क्रम (i = 6; (i + 4) < header->length; i += 5) अणु
		/* entity 1 - 3: voltage multiplier and offset */
		अगर (dmi_data[i] >= 1 && dmi_data[i] <= 3) अणु
			/* Our in sensors order and the DMI order dअगरfer */
			स्थिर पूर्णांक shuffle[3] = अणु 1, 0, 2 पूर्ण;
			पूर्णांक in = shuffle[dmi_data[i] - 1];

			/* Check क्रम twice the same entity */
			अगर (found & (1 << in))
				वापस;

			mult[in] = dmi_data[i + 1] | (dmi_data[i + 2] << 8);
			offset[in] = dmi_data[i + 3] | (dmi_data[i + 4] << 8);

			found |= 1 << in;
		पूर्ण

		/* entity 7: reference voltage */
		अगर (dmi_data[i] == 7) अणु
			/* Check क्रम twice the same entity */
			अगर (found & 0x08)
				वापस;

			vref = dmi_data[i + 1] | (dmi_data[i + 2] << 8);

			found |= 0x08;
		पूर्ण
	पूर्ण

	अगर (found == 0x0F) अणु
		क्रम (i = 0; i < 3; i++) अणु
			dmi_mult[i] = mult[i] * 10;
			dmi_offset[i] = offset[i] * 10;
		पूर्ण
		/*
		 * According to the करोcs there should be separate dmi entries
		 * क्रम the mult's and offsets of in3-5 of the syl, but on
		 * my test machine these are not present
		 */
		dmi_mult[3] = dmi_mult[2];
		dmi_mult[4] = dmi_mult[1];
		dmi_mult[5] = dmi_mult[2];
		dmi_offset[3] = dmi_offset[2];
		dmi_offset[4] = dmi_offset[1];
		dmi_offset[5] = dmi_offset[2];
		dmi_vref = vref;
	पूर्ण
पूर्ण

अटल पूर्णांक fschmd_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	क्रमागत chips kind;
	काष्ठा i2c_adapter *adapter = client->adapter;
	अक्षर id[4];

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Detect & Identअगरy the chip */
	id[0] = i2c_smbus_पढ़ो_byte_data(client, FSCHMD_REG_IDENT_0);
	id[1] = i2c_smbus_पढ़ो_byte_data(client, FSCHMD_REG_IDENT_1);
	id[2] = i2c_smbus_पढ़ो_byte_data(client, FSCHMD_REG_IDENT_2);
	id[3] = '\0';

	अगर (!म_भेद(id, "PEG"))
		kind = fscpos;
	अन्यथा अगर (!म_भेद(id, "HER"))
		kind = fscher;
	अन्यथा अगर (!म_भेद(id, "SCY"))
		kind = fscscy;
	अन्यथा अगर (!म_भेद(id, "HRC"))
		kind = fschrc;
	अन्यथा अगर (!म_भेद(id, "HMD"))
		kind = fschmd;
	अन्यथा अगर (!म_भेद(id, "HDS"))
		kind = fschds;
	अन्यथा अगर (!म_भेद(id, "SYL"))
		kind = fscsyl;
	अन्यथा
		वापस -ENODEV;

	strlcpy(info->type, fschmd_id[kind].name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक fschmd_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा fschmd_data *data;
	स्थिर अक्षर * स्थिर names[7] = अणु "Poseidon", "Hermes", "Scylla",
				"Heracles", "Heimdall", "Hades", "Syleus" पूर्ण;
	स्थिर पूर्णांक watchकरोg_minors[] = अणु WATCHDOG_MINOR, 212, 213, 214, 215 पूर्ण;
	पूर्णांक i, err;
	क्रमागत chips kind = i2c_match_id(fschmd_id, client)->driver_data;

	data = kzalloc(माप(काष्ठा fschmd_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	mutex_init(&data->watchकरोg_lock);
	INIT_LIST_HEAD(&data->list);
	kref_init(&data->kref);
	/*
	 * Store client poपूर्णांकer in our data काष्ठा क्रम watchकरोg usage
	 * (where the client is found through a data ptr instead of the
	 * otherway around)
	 */
	data->client = client;
	data->kind = kind;

	अगर (kind == fscpos) अणु
		/*
		 * The Poseiकरोn has hardwired temp limits, fill these
		 * in क्रम the alarm resetting code
		 */
		data->temp_max[0] = 70 + 128;
		data->temp_max[1] = 50 + 128;
		data->temp_max[2] = 50 + 128;
	पूर्ण

	/* Read the special DMI table क्रम fscher and newer chips */
	अगर ((kind == fscher || kind >= fschrc) && dmi_vref == -1) अणु
		dmi_walk(fschmd_dmi_decode, शून्य);
		अगर (dmi_vref == -1) अणु
			dev_warn(&client->dev,
				"Couldn't get voltage scaling factors from "
				"BIOS DMI table, using builtin defaults\n");
			dmi_vref = 33;
		पूर्ण
	पूर्ण

	/* Read in some never changing रेजिस्टरs */
	data->revision = i2c_smbus_पढ़ो_byte_data(client, FSCHMD_REG_REVISION);
	data->global_control = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_CONTROL);
	data->watchकरोg_control = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_WDOG_CONTROL[data->kind]);
	data->watchकरोg_state = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_WDOG_STATE[data->kind]);
	data->watchकरोg_preset = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_WDOG_PRESET[data->kind]);

	err = device_create_file(&client->dev, &dev_attr_alert_led);
	अगर (err)
		जाओ निकास_detach;

	क्रम (i = 0; i < FSCHMD_NO_VOLT_SENSORS[data->kind]; i++) अणु
		err = device_create_file(&client->dev,
					&fschmd_attr[i].dev_attr);
		अगर (err)
			जाओ निकास_detach;
	पूर्ण

	क्रम (i = 0; i < (FSCHMD_NO_TEMP_SENSORS[data->kind] * 4); i++) अणु
		/* Poseiकरोn करोesn't have TEMP_LIMIT रेजिस्टरs */
		अगर (kind == fscpos && fschmd_temp_attr[i].dev_attr.show ==
				temp_max_show)
			जारी;

		अगर (kind == fscsyl) अणु
			अगर (i % 4 == 0)
				data->temp_status[i / 4] =
					i2c_smbus_पढ़ो_byte_data(client,
						FSCHMD_REG_TEMP_STATE
						[data->kind][i / 4]);
			अगर (data->temp_status[i / 4] & FSCHMD_TEMP_DISABLED)
				जारी;
		पूर्ण

		err = device_create_file(&client->dev,
					&fschmd_temp_attr[i].dev_attr);
		अगर (err)
			जाओ निकास_detach;
	पूर्ण

	क्रम (i = 0; i < (FSCHMD_NO_FAN_SENSORS[data->kind] * 5); i++) अणु
		/* Poseiकरोn करोesn't have a FAN_MIN रेजिस्टर क्रम its 3rd fan */
		अगर (kind == fscpos &&
				!म_भेद(fschmd_fan_attr[i].dev_attr.attr.name,
					"pwm3_auto_point1_pwm"))
			जारी;

		अगर (kind == fscsyl) अणु
			अगर (i % 5 == 0)
				data->fan_status[i / 5] =
					i2c_smbus_पढ़ो_byte_data(client,
						FSCHMD_REG_FAN_STATE
						[data->kind][i / 5]);
			अगर (data->fan_status[i / 5] & FSCHMD_FAN_DISABLED)
				जारी;
		पूर्ण

		err = device_create_file(&client->dev,
					&fschmd_fan_attr[i].dev_attr);
		अगर (err)
			जाओ निकास_detach;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = शून्य;
		जाओ निकास_detach;
	पूर्ण

	/*
	 * We take the data_mutex lock early so that watchकरोg_खोलो() cannot
	 * run when misc_रेजिस्टर() has completed, but we've not yet added
	 * our data to the watchकरोg_data_list (and set the शेष समयout)
	 */
	mutex_lock(&watchकरोg_data_mutex);
	क्रम (i = 0; i < ARRAY_SIZE(watchकरोg_minors); i++) अणु
		/* Register our watchकरोg part */
		snम_लिखो(data->watchकरोg_name, माप(data->watchकरोg_name),
			"watchdog%c", (i == 0) ? '\0' : ('0' + i));
		data->watchकरोg_miscdev.name = data->watchकरोg_name;
		data->watchकरोg_miscdev.fops = &watchकरोg_fops;
		data->watchकरोg_miscdev.minor = watchकरोg_minors[i];
		err = misc_रेजिस्टर(&data->watchकरोg_miscdev);
		अगर (err == -EBUSY)
			जारी;
		अगर (err) अणु
			data->watchकरोg_miscdev.minor = 0;
			dev_err(&client->dev,
				"Registering watchdog chardev: %d\n", err);
			अवरोध;
		पूर्ण

		list_add(&data->list, &watchकरोg_data_list);
		watchकरोg_set_समयout(data, 60);
		dev_info(&client->dev,
			"Registered watchdog chardev major 10, minor: %d\n",
			watchकरोg_minors[i]);
		अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(watchकरोg_minors)) अणु
		data->watchकरोg_miscdev.minor = 0;
		dev_warn(&client->dev,
			 "Couldn't register watchdog chardev (due to no free minor)\n");
	पूर्ण
	mutex_unlock(&watchकरोg_data_mutex);

	dev_info(&client->dev, "Detected FSC %s chip, revision: %d\n",
		names[data->kind], (पूर्णांक) data->revision);

	वापस 0;

निकास_detach:
	fschmd_हटाओ(client); /* will also मुक्त data क्रम us */
	वापस err;
पूर्ण

अटल पूर्णांक fschmd_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fschmd_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	/* Unरेजिस्टर the watchकरोg (अगर रेजिस्टरed) */
	अगर (data->watchकरोg_miscdev.minor) अणु
		misc_deरेजिस्टर(&data->watchकरोg_miscdev);
		अगर (data->watchकरोg_is_खोलो) अणु
			dev_warn(&client->dev,
				"i2c client detached with watchdog open! "
				"Stopping watchdog.\n");
			watchकरोg_stop(data);
		पूर्ण
		mutex_lock(&watchकरोg_data_mutex);
		list_del(&data->list);
		mutex_unlock(&watchकरोg_data_mutex);
		/* Tell the watchकरोg code the client is gone */
		mutex_lock(&data->watchकरोg_lock);
		data->client = शून्य;
		mutex_unlock(&data->watchकरोg_lock);
	पूर्ण

	/*
	 * Check अगर रेजिस्टरed in हाल we're called from fschmd_detect
	 * to cleanup after an error
	 */
	अगर (data->hwmon_dev)
		hwmon_device_unरेजिस्टर(data->hwmon_dev);

	device_हटाओ_file(&client->dev, &dev_attr_alert_led);
	क्रम (i = 0; i < (FSCHMD_NO_VOLT_SENSORS[data->kind]); i++)
		device_हटाओ_file(&client->dev, &fschmd_attr[i].dev_attr);
	क्रम (i = 0; i < (FSCHMD_NO_TEMP_SENSORS[data->kind] * 4); i++)
		device_हटाओ_file(&client->dev,
					&fschmd_temp_attr[i].dev_attr);
	क्रम (i = 0; i < (FSCHMD_NO_FAN_SENSORS[data->kind] * 5); i++)
		device_हटाओ_file(&client->dev,
					&fschmd_fan_attr[i].dev_attr);

	mutex_lock(&watchकरोg_data_mutex);
	kref_put(&data->kref, fschmd_release_resources);
	mutex_unlock(&watchकरोg_data_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा fschmd_data *fschmd_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा fschmd_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + 2 * HZ) || !data->valid) अणु

		क्रम (i = 0; i < FSCHMD_NO_TEMP_SENSORS[data->kind]; i++) अणु
			data->temp_act[i] = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_TEMP_ACT[data->kind][i]);
			data->temp_status[i] = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_TEMP_STATE[data->kind][i]);

			/* The fscpos करोesn't have TEMP_LIMIT रेजिस्टरs */
			अगर (FSCHMD_REG_TEMP_LIMIT[data->kind][i])
				data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(
					client,
					FSCHMD_REG_TEMP_LIMIT[data->kind][i]);

			/*
			 * reset alarm अगर the alarm condition is gone,
			 * the chip करोesn't करो this itself
			 */
			अगर ((data->temp_status[i] & FSCHMD_TEMP_ALARM_MASK) ==
					FSCHMD_TEMP_ALARM_MASK &&
					data->temp_act[i] < data->temp_max[i])
				i2c_smbus_ग_लिखो_byte_data(client,
					FSCHMD_REG_TEMP_STATE[data->kind][i],
					data->temp_status[i]);
		पूर्ण

		क्रम (i = 0; i < FSCHMD_NO_FAN_SENSORS[data->kind]; i++) अणु
			data->fan_act[i] = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_FAN_ACT[data->kind][i]);
			data->fan_status[i] = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_FAN_STATE[data->kind][i]);
			data->fan_ripple[i] = i2c_smbus_पढ़ो_byte_data(client,
					FSCHMD_REG_FAN_RIPPLE[data->kind][i]);

			/* The fscpos third fan करोesn't have a fan_min */
			अगर (FSCHMD_REG_FAN_MIN[data->kind][i])
				data->fan_min[i] = i2c_smbus_पढ़ो_byte_data(
					client,
					FSCHMD_REG_FAN_MIN[data->kind][i]);

			/* reset fan status अगर speed is back to > 0 */
			अगर ((data->fan_status[i] & FSCHMD_FAN_ALARM) &&
					data->fan_act[i])
				i2c_smbus_ग_लिखो_byte_data(client,
					FSCHMD_REG_FAN_STATE[data->kind][i],
					data->fan_status[i]);
		पूर्ण

		क्रम (i = 0; i < FSCHMD_NO_VOLT_SENSORS[data->kind]; i++)
			data->volt[i] = i2c_smbus_पढ़ो_byte_data(client,
					       FSCHMD_REG_VOLT[data->kind][i]);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

module_i2c_driver(fschmd_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("FSC Poseidon, Hermes, Scylla, Heracles, Heimdall, Hades "
			"and Syleus driver");
MODULE_LICENSE("GPL");
