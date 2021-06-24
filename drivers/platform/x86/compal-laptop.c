<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*-*-linux-c-*-*/

/*
  Copyright (C) 2008 Cezary Jackiewicz <cezary.jackiewicz (at) gmail.com>

  based on MSI driver

  Copyright (C) 2006 Lennart Poettering <mzxreary (at) 0poपूर्णांकer (करोt) de>

 */

/*
 * compal-laptop.c - Compal laptop support.
 *
 * This driver exports a few files in /sys/devices/platक्रमm/compal-laptop/:
 *   wake_up_XXX   Whether or not we listen to such wake up events (rw)
 *
 * In addition to these platक्रमm device attributes the driver
 * रेजिस्टरs itself in the Linux backlight control, घातer_supply, rfसमाप्त
 * and hwmon subप्रणाली and is available to userspace under:
 *
 *   /sys/class/backlight/compal-laptop/
 *   /sys/class/घातer_supply/compal-laptop/
 *   /sys/class/rfसमाप्त/rfसमाप्तX/
 *   /sys/class/hwmon/hwmonX/
 *
 * Notes on the घातer_supply battery पूर्णांकerface:
 *   - the "minimum" design voltage is *the* design voltage
 *   - the ambient temperature is the average battery temperature
 *     and the value is an educated guess (see commented code below)
 *
 *
 * This driver might work on other laptops produced by Compal. If you
 * want to try it you can pass क्रमce=1 as argument to the module which
 * will क्रमce it to load even when the DMI data करोesn't identअगरy the
 * laptop as compatible.
 *
 * Lots of data available at:
 * http://service1.marasst.com/Compal/JHL90_91/Service%20Manual/
 * JHL90%20service%20manual-Final-0725.pdf
 *
 *
 *
 * Support क्रम the Compal JHL90 added by Roald Frederickx
 * (roald.frederickx@gmail.com):
 * Driver got large revision. Added functionalities: backlight
 * घातer, wake_on_XXX, a hwmon and घातer_supply पूर्णांकerface.
 *
 * In हाल this माला_लो merged पूर्णांकo the kernel source: I want to dedicate this
 * to Kasper Meerts, the awesome guy who showed me Linux and C!
 */

/* NOTE: currently the wake_on_XXX, hwmon and घातer_supply पूर्णांकerfaces are
 * only enabled on a JHL90 board until it is verअगरied that they work on the
 * other boards too.  See the extra_features variable. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/fb.h>
#समावेश <acpi/video.h>

/* ======= */
/* Defines */
/* ======= */
#घोषणा DRIVER_NAME "compal-laptop"
#घोषणा DRIVER_VERSION	"0.2.7"

#घोषणा BACKLIGHT_LEVEL_ADDR		0xB9
#घोषणा BACKLIGHT_LEVEL_MAX		7
#घोषणा BACKLIGHT_STATE_ADDR		0x59
#घोषणा BACKLIGHT_STATE_ON_DATA		0xE1
#घोषणा BACKLIGHT_STATE_OFF_DATA	0xE2

#घोषणा WAKE_UP_ADDR			0xA4
#घोषणा WAKE_UP_PME			(1 << 0)
#घोषणा WAKE_UP_MODEM			(1 << 1)
#घोषणा WAKE_UP_LAN			(1 << 2)
#घोषणा WAKE_UP_WLAN			(1 << 4)
#घोषणा WAKE_UP_KEY			(1 << 6)
#घोषणा WAKE_UP_MOUSE			(1 << 7)

#घोषणा WIRELESS_ADDR			0xBB
#घोषणा WIRELESS_WLAN			(1 << 0)
#घोषणा WIRELESS_BT			(1 << 1)
#घोषणा WIRELESS_WLAN_EXISTS		(1 << 2)
#घोषणा WIRELESS_BT_EXISTS		(1 << 3)
#घोषणा WIRELESS_KILLSWITCH		(1 << 4)

#घोषणा PWM_ADDRESS			0x46
#घोषणा PWM_DISABLE_ADDR		0x59
#घोषणा PWM_DISABLE_DATA		0xA5
#घोषणा PWM_ENABLE_ADDR			0x59
#घोषणा PWM_ENABLE_DATA			0xA8

#घोषणा FAN_ADDRESS			0x46
#घोषणा FAN_DATA			0x81
#घोषणा FAN_FULL_ON_CMD			0x59 /* Doesn't seem to work. Just */
#घोषणा FAN_FULL_ON_ENABLE		0x76 /* क्रमce the pwm संकेत to its */
#घोषणा FAN_FULL_ON_DISABLE		0x77 /* maximum value instead */

#घोषणा TEMP_CPU			0xB0
#घोषणा TEMP_CPU_LOCAL			0xB1
#घोषणा TEMP_CPU_DTS			0xB5
#घोषणा TEMP_NORTHBRIDGE		0xB6
#घोषणा TEMP_VGA			0xB4
#घोषणा TEMP_SKIN			0xB2

#घोषणा BAT_MANUFACTURER_NAME_ADDR	0x10
#घोषणा BAT_MANUFACTURER_NAME_LEN	9
#घोषणा BAT_MODEL_NAME_ADDR		0x19
#घोषणा BAT_MODEL_NAME_LEN		6
#घोषणा BAT_SERIAL_NUMBER_ADDR		0xC4
#घोषणा BAT_SERIAL_NUMBER_LEN		5
#घोषणा BAT_CHARGE_NOW			0xC2
#घोषणा BAT_CHARGE_DESIGN		0xCA
#घोषणा BAT_VOLTAGE_NOW			0xC6
#घोषणा BAT_VOLTAGE_DESIGN		0xC8
#घोषणा BAT_CURRENT_NOW			0xD0
#घोषणा BAT_CURRENT_AVG			0xD2
#घोषणा BAT_POWER			0xD4
#घोषणा BAT_CAPACITY			0xCE
#घोषणा BAT_TEMP			0xD6
#घोषणा BAT_TEMP_AVG			0xD7
#घोषणा BAT_STATUS0			0xC1
#घोषणा BAT_STATUS1			0xF0
#घोषणा BAT_STATUS2			0xF1
#घोषणा BAT_STOP_CHARGE1		0xF2
#घोषणा BAT_STOP_CHARGE2		0xF3
#घोषणा BAT_CHARGE_LIMIT		0x03
#घोषणा BAT_CHARGE_LIMIT_MAX		100

#घोषणा BAT_S0_DISCHARGE		(1 << 0)
#घोषणा BAT_S0_DISCHRG_CRITICAL		(1 << 2)
#घोषणा BAT_S0_LOW			(1 << 3)
#घोषणा BAT_S0_CHARGING			(1 << 1)
#घोषणा BAT_S0_AC			(1 << 7)
#घोषणा BAT_S1_EXISTS			(1 << 0)
#घोषणा BAT_S1_FULL			(1 << 1)
#घोषणा BAT_S1_EMPTY			(1 << 2)
#घोषणा BAT_S1_LiION_OR_NiMH		(1 << 7)
#घोषणा BAT_S2_LOW_LOW			(1 << 0)
#घोषणा BAT_STOP_CHRG1_BAD_CELL		(1 << 1)
#घोषणा BAT_STOP_CHRG1_COMM_FAIL	(1 << 2)
#घोषणा BAT_STOP_CHRG1_OVERVOLTAGE	(1 << 6)
#घोषणा BAT_STOP_CHRG1_OVERTEMPERATURE	(1 << 7)


/* ======= */
/* Structs */
/* ======= */
काष्ठा compal_dataअणु
	/* Fan control */
	पूर्णांक pwm_enable; /* 0:full on, 1:set by pwm1, 2:control by motherboard */
	अचिन्हित अक्षर curr_pwm;

	/* Power supply */
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_info psy_info;
	अक्षर bat_model_name[BAT_MODEL_NAME_LEN + 1];
	अक्षर bat_manufacturer_name[BAT_MANUFACTURER_NAME_LEN + 1];
	अक्षर bat_serial_number[BAT_SERIAL_NUMBER_LEN + 1];
पूर्ण;


/* =============== */
/* General globals */
/* =============== */
अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force driver load, ignore DMI data");

/* Support क्रम the wake_on_XXX, hwmon and घातer_supply पूर्णांकerface. Currently
 * only माला_लो enabled on a JHL90 board. Might work with the others too */
अटल bool extra_features;

/* Nasty stuff. For some reason the fan control is very un-linear.  I've
 * come up with these values by looping through the possible inमाला_दो and
 * watching the output of address 0x4F (करो an ec_transaction writing 0x33
 * पूर्णांकo 0x4F and पढ़ो a few bytes from the output, like so:
 *	u8 ग_लिखोData = 0x33;
 *	ec_transaction(0x4F, &ग_लिखोData, 1, buffer, 32);
 * That address is labeled "fan1 table information" in the service manual.
 * It should be clear which value in 'buffer' changes). This seems to be
 * related to fan speed. It isn't a proper 'realtime' fan speed value
 * though, because physically stopping or speeding up the fan करोesn't
 * change it. It might be the average voltage or current of the pwm output.
 * Nevertheless, it is more fine-grained than the actual RPM पढ़ोing */
अटल स्थिर अचिन्हित अक्षर pwm_lookup_table[256] = अणु
	0, 0, 0, 1, 1, 1, 2, 253, 254, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
	7, 7, 7, 8, 86, 86, 9, 9, 9, 10, 10, 10, 11, 92, 92, 12, 12, 95,
	13, 66, 66, 14, 14, 98, 15, 15, 15, 16, 16, 67, 17, 17, 72, 18, 70,
	75, 19, 90, 90, 73, 73, 73, 21, 21, 91, 91, 91, 96, 23, 94, 94, 94,
	94, 94, 94, 94, 94, 94, 94, 141, 141, 238, 223, 192, 139, 139, 139,
	139, 139, 142, 142, 142, 142, 142, 78, 78, 78, 78, 78, 76, 76, 76,
	76, 76, 79, 79, 79, 79, 79, 79, 79, 20, 20, 20, 20, 20, 22, 22, 22,
	22, 22, 24, 24, 24, 24, 24, 24, 219, 219, 219, 219, 219, 219, 219,
	219, 27, 27, 188, 188, 28, 28, 28, 29, 186, 186, 186, 186, 186,
	186, 186, 186, 186, 186, 31, 31, 31, 31, 31, 32, 32, 32, 41, 33,
	33, 33, 33, 33, 252, 252, 34, 34, 34, 43, 35, 35, 35, 36, 36, 38,
	206, 206, 206, 206, 206, 206, 206, 206, 206, 37, 37, 37, 46, 46,
	47, 47, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 48, 48,
	48, 48, 48, 40, 40, 40, 49, 42, 42, 42, 42, 42, 42, 42, 42, 44,
	189, 189, 189, 189, 54, 54, 45, 45, 45, 45, 45, 45, 45, 45, 251,
	191, 199, 199, 199, 199, 199, 215, 215, 215, 215, 187, 187, 187,
	187, 187, 193, 50
पूर्ण;




/* ========================= */
/* Hardware access functions */
/* ========================= */
/* General access */
अटल u8 ec_पढ़ो_u8(u8 addr)
अणु
	u8 value = 0;
	ec_पढ़ो(addr, &value);
	वापस value;
पूर्ण

अटल s8 ec_पढ़ो_s8(u8 addr)
अणु
	वापस (s8)ec_पढ़ो_u8(addr);
पूर्ण

अटल u16 ec_पढ़ो_u16(u8 addr)
अणु
	पूर्णांक hi, lo;
	lo = ec_पढ़ो_u8(addr);
	hi = ec_पढ़ो_u8(addr + 1);
	वापस (hi << 8) + lo;
पूर्ण

अटल s16 ec_पढ़ो_s16(u8 addr)
अणु
	वापस (s16) ec_पढ़ो_u16(addr);
पूर्ण

अटल व्योम ec_पढ़ो_sequence(u8 addr, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < len; i++)
		ec_पढ़ो(addr + i, buf + i);
पूर्ण


/* Backlight access */
अटल पूर्णांक set_backlight_level(पूर्णांक level)
अणु
	अगर (level < 0 || level > BACKLIGHT_LEVEL_MAX)
		वापस -EINVAL;

	ec_ग_लिखो(BACKLIGHT_LEVEL_ADDR, level);

	वापस 0;
पूर्ण

अटल पूर्णांक get_backlight_level(व्योम)
अणु
	वापस (पूर्णांक) ec_पढ़ो_u8(BACKLIGHT_LEVEL_ADDR);
पूर्ण

अटल व्योम set_backlight_state(bool on)
अणु
	u8 data = on ? BACKLIGHT_STATE_ON_DATA : BACKLIGHT_STATE_OFF_DATA;
	ec_transaction(BACKLIGHT_STATE_ADDR, &data, 1, शून्य, 0);
पूर्ण


/* Fan control access */
अटल व्योम pwm_enable_control(व्योम)
अणु
	अचिन्हित अक्षर ग_लिखोData = PWM_ENABLE_DATA;
	ec_transaction(PWM_ENABLE_ADDR, &ग_लिखोData, 1, शून्य, 0);
पूर्ण

अटल व्योम pwm_disable_control(व्योम)
अणु
	अचिन्हित अक्षर ग_लिखोData = PWM_DISABLE_DATA;
	ec_transaction(PWM_DISABLE_ADDR, &ग_लिखोData, 1, शून्य, 0);
पूर्ण

अटल व्योम set_pwm(पूर्णांक pwm)
अणु
	ec_transaction(PWM_ADDRESS, &pwm_lookup_table[pwm], 1, शून्य, 0);
पूर्ण

अटल पूर्णांक get_fan_rpm(व्योम)
अणु
	u8 value, data = FAN_DATA;
	ec_transaction(FAN_ADDRESS, &data, 1, &value, 1);
	वापस 100 * (पूर्णांक)value;
पूर्ण




/* =================== */
/* Interface functions */
/* =================== */

/* Backlight पूर्णांकerface */
अटल पूर्णांक bl_get_brightness(काष्ठा backlight_device *b)
अणु
	वापस get_backlight_level();
पूर्ण

अटल पूर्णांक bl_update_status(काष्ठा backlight_device *b)
अणु
	पूर्णांक ret = set_backlight_level(b->props.brightness);
	अगर (ret)
		वापस ret;

	set_backlight_state((b->props.घातer == FB_BLANK_UNBLANK)
		&&    !(b->props.state & BL_CORE_SUSPENDED)
		&&    !(b->props.state & BL_CORE_FBBLANK));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops compalbl_ops = अणु
	.get_brightness = bl_get_brightness,
	.update_status	= bl_update_status,
पूर्ण;


/* Wireless पूर्णांकerface */
अटल पूर्णांक compal_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	अचिन्हित दीर्घ radio = (अचिन्हित दीर्घ) data;
	u8 result = ec_पढ़ो_u8(WIRELESS_ADDR);
	u8 value;

	अगर (!blocked)
		value = (u8) (result | radio);
	अन्यथा
		value = (u8) (result & ~radio);
	ec_ग_लिखो(WIRELESS_ADDR, value);

	वापस 0;
पूर्ण

अटल व्योम compal_rfसमाप्त_poll(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	u8 result = ec_पढ़ो_u8(WIRELESS_ADDR);
	bool hw_blocked = !(result & WIRELESS_KILLSWITCH);
	rfसमाप्त_set_hw_state(rfसमाप्त, hw_blocked);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops compal_rfसमाप्त_ops = अणु
	.poll = compal_rfसमाप्त_poll,
	.set_block = compal_rfसमाप्त_set,
पूर्ण;


/* Wake_up पूर्णांकerface */
#घोषणा SIMPLE_MASKED_STORE_SHOW(NAME, ADDR, MASK)			\
अटल sमाप_प्रकार NAME##_show(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	वापस प्र_लिखो(buf, "%d\n", ((ec_पढ़ो_u8(ADDR) & MASK) != 0));	\
पूर्ण									\
अटल sमाप_प्रकार NAME##_store(काष्ठा device *dev,				\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	पूर्णांक state;							\
	u8 old_val = ec_पढ़ो_u8(ADDR);					\
	अगर (माला_पूछो(buf, "%d", &state) != 1 || (state < 0 || state > 1))	\
		वापस -EINVAL;						\
	ec_ग_लिखो(ADDR, state ? (old_val | MASK) : (old_val & ~MASK));	\
	वापस count;							\
पूर्ण

SIMPLE_MASKED_STORE_SHOW(wake_up_pme,	WAKE_UP_ADDR, WAKE_UP_PME)
SIMPLE_MASKED_STORE_SHOW(wake_up_modem,	WAKE_UP_ADDR, WAKE_UP_MODEM)
SIMPLE_MASKED_STORE_SHOW(wake_up_lan,	WAKE_UP_ADDR, WAKE_UP_LAN)
SIMPLE_MASKED_STORE_SHOW(wake_up_wlan,	WAKE_UP_ADDR, WAKE_UP_WLAN)
SIMPLE_MASKED_STORE_SHOW(wake_up_key,	WAKE_UP_ADDR, WAKE_UP_KEY)
SIMPLE_MASKED_STORE_SHOW(wake_up_mouse,	WAKE_UP_ADDR, WAKE_UP_MOUSE)

/* Fan control पूर्णांकerface */
अटल sमाप_प्रकार pwm_enable_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा compal_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_enable);
पूर्ण

अटल sमाप_प्रकार pwm_enable_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा compal_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val < 0)
		वापस -EINVAL;

	data->pwm_enable = val;

	चयन (val) अणु
	हाल 0:  /* Full speed */
		pwm_enable_control();
		set_pwm(255);
		अवरोध;
	हाल 1:  /* As set by pwm1 */
		pwm_enable_control();
		set_pwm(data->curr_pwm);
		अवरोध;
	शेष: /* Control by motherboard */
		pwm_disable_control();
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा compal_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%hhu\n", data->curr_pwm);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा compal_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val < 0 || val > 255)
		वापस -EINVAL;

	data->curr_pwm = val;

	अगर (data->pwm_enable != 1)
		वापस count;
	set_pwm(val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", get_fan_rpm());
पूर्ण


/* Temperature पूर्णांकerface */
#घोषणा TEMPERATURE_SHOW_TEMP_AND_LABEL(POSTFIX, ADDRESS, LABEL)	\
अटल sमाप_प्रकार temp_##POSTFIX(काष्ठा device *dev,			\
		काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	वापस प्र_लिखो(buf, "%d\n", 1000 * (पूर्णांक)ec_पढ़ो_s8(ADDRESS));	\
पूर्ण									\
अटल sमाप_प्रकार label_##POSTFIX(काष्ठा device *dev,			\
		काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	वापस प्र_लिखो(buf, "%s\n", LABEL);				\
पूर्ण

/* Labels as in service guide */
TEMPERATURE_SHOW_TEMP_AND_LABEL(cpu,        TEMP_CPU,        "CPU_TEMP");
TEMPERATURE_SHOW_TEMP_AND_LABEL(cpu_local,  TEMP_CPU_LOCAL,  "CPU_TEMP_LOCAL");
TEMPERATURE_SHOW_TEMP_AND_LABEL(cpu_DTS,    TEMP_CPU_DTS,    "CPU_DTS");
TEMPERATURE_SHOW_TEMP_AND_LABEL(northbridge,TEMP_NORTHBRIDGE,"NorthBridge");
TEMPERATURE_SHOW_TEMP_AND_LABEL(vga,        TEMP_VGA,        "VGA_TEMP");
TEMPERATURE_SHOW_TEMP_AND_LABEL(SKIN,       TEMP_SKIN,       "SKIN_TEMP90");


/* Power supply पूर्णांकerface */
अटल पूर्णांक bat_status(व्योम)
अणु
	u8 status0 = ec_पढ़ो_u8(BAT_STATUS0);
	u8 status1 = ec_पढ़ो_u8(BAT_STATUS1);

	अगर (status0 & BAT_S0_CHARGING)
		वापस POWER_SUPPLY_STATUS_CHARGING;
	अगर (status0 & BAT_S0_DISCHARGE)
		वापस POWER_SUPPLY_STATUS_DISCHARGING;
	अगर (status1 & BAT_S1_FULL)
		वापस POWER_SUPPLY_STATUS_FULL;
	वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
पूर्ण

अटल पूर्णांक bat_health(व्योम)
अणु
	u8 status = ec_पढ़ो_u8(BAT_STOP_CHARGE1);

	अगर (status & BAT_STOP_CHRG1_OVERTEMPERATURE)
		वापस POWER_SUPPLY_HEALTH_OVERHEAT;
	अगर (status & BAT_STOP_CHRG1_OVERVOLTAGE)
		वापस POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अगर (status & BAT_STOP_CHRG1_BAD_CELL)
		वापस POWER_SUPPLY_HEALTH_DEAD;
	अगर (status & BAT_STOP_CHRG1_COMM_FAIL)
		वापस POWER_SUPPLY_HEALTH_UNKNOWN;
	वापस POWER_SUPPLY_HEALTH_GOOD;
पूर्ण

अटल पूर्णांक bat_is_present(व्योम)
अणु
	u8 status = ec_पढ़ो_u8(BAT_STATUS2);
	वापस ((status & BAT_S1_EXISTS) != 0);
पूर्ण

अटल पूर्णांक bat_technology(व्योम)
अणु
	u8 status = ec_पढ़ो_u8(BAT_STATUS1);

	अगर (status & BAT_S1_LiION_OR_NiMH)
		वापस POWER_SUPPLY_TECHNOLOGY_LION;
	वापस POWER_SUPPLY_TECHNOLOGY_NiMH;
पूर्ण

अटल पूर्णांक bat_capacity_level(व्योम)
अणु
	u8 status0 = ec_पढ़ो_u8(BAT_STATUS0);
	u8 status1 = ec_पढ़ो_u8(BAT_STATUS1);
	u8 status2 = ec_पढ़ो_u8(BAT_STATUS2);

	अगर (status0 & BAT_S0_DISCHRG_CRITICAL
			|| status1 & BAT_S1_EMPTY
			|| status2 & BAT_S2_LOW_LOW)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
	अगर (status0 & BAT_S0_LOW)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_LOW;
	अगर (status1 & BAT_S1_FULL)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_FULL;
	वापस POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
पूर्ण

अटल पूर्णांक bat_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा compal_data *data = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = bat_status();
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = bat_health();
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = bat_is_present();
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = bat_technology();
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN: /* THE design voltage... */
		val->पूर्णांकval = ec_पढ़ो_u16(BAT_VOLTAGE_DESIGN) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = ec_पढ़ो_u16(BAT_VOLTAGE_NOW) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = ec_पढ़ो_s16(BAT_CURRENT_NOW) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval = ec_पढ़ो_s16(BAT_CURRENT_AVG) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		val->पूर्णांकval = ec_पढ़ो_u8(BAT_POWER) * 1000000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = ec_पढ़ो_u16(BAT_CHARGE_DESIGN) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = ec_पढ़ो_u16(BAT_CHARGE_NOW) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		val->पूर्णांकval = ec_पढ़ो_u8(BAT_CHARGE_LIMIT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX:
		val->पूर्णांकval = BAT_CHARGE_LIMIT_MAX;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = ec_पढ़ो_u8(BAT_CAPACITY);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		val->पूर्णांकval = bat_capacity_level();
		अवरोध;
	/* It smees that BAT_TEMP_AVG is a (2's complement?) value showing
	 * the number of degrees, whereas BAT_TEMP is somewhat more
	 * complicated. It looks like this is a negative nember with a
	 * 100/256 भागider and an offset of 222. Both were determined
	 * experimentally by comparing BAT_TEMP and BAT_TEMP_AVG. */
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = ((222 - (पूर्णांक)ec_पढ़ो_u8(BAT_TEMP)) * 1000) >> 8;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_AMBIENT: /* Ambient, Avg, ... same thing */
		val->पूर्णांकval = ec_पढ़ो_s8(BAT_TEMP_AVG) * 10;
		अवरोध;
	/* Neither the model name nor manufacturer name work क्रम me. */
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = data->bat_model_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = data->bat_manufacturer_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = data->bat_serial_number;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bat_set_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				स्थिर जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक level;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		level = val->पूर्णांकval;
		अगर (level < 0 || level > BAT_CHARGE_LIMIT_MAX)
			वापस -EINVAL;
		अगर (ec_ग_लिखो(BAT_CHARGE_LIMIT, level) < 0)
			वापस -EIO;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bat_ग_लिखोable_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण




/* ============== */
/* Driver Globals */
/* ============== */
अटल DEVICE_ATTR_RW(wake_up_pme);
अटल DEVICE_ATTR_RW(wake_up_modem);
अटल DEVICE_ATTR_RW(wake_up_lan);
अटल DEVICE_ATTR_RW(wake_up_wlan);
अटल DEVICE_ATTR_RW(wake_up_key);
अटल DEVICE_ATTR_RW(wake_up_mouse);

अटल DEVICE_ATTR(fan1_input,  S_IRUGO, fan_show,          शून्य);
अटल DEVICE_ATTR(temp1_input, S_IRUGO, temp_cpu,          शून्य);
अटल DEVICE_ATTR(temp2_input, S_IRUGO, temp_cpu_local,    शून्य);
अटल DEVICE_ATTR(temp3_input, S_IRUGO, temp_cpu_DTS,      शून्य);
अटल DEVICE_ATTR(temp4_input, S_IRUGO, temp_northbridge,  शून्य);
अटल DEVICE_ATTR(temp5_input, S_IRUGO, temp_vga,          शून्य);
अटल DEVICE_ATTR(temp6_input, S_IRUGO, temp_SKIN,         शून्य);
अटल DEVICE_ATTR(temp1_label, S_IRUGO, label_cpu,         शून्य);
अटल DEVICE_ATTR(temp2_label, S_IRUGO, label_cpu_local,   शून्य);
अटल DEVICE_ATTR(temp3_label, S_IRUGO, label_cpu_DTS,     शून्य);
अटल DEVICE_ATTR(temp4_label, S_IRUGO, label_northbridge, शून्य);
अटल DEVICE_ATTR(temp5_label, S_IRUGO, label_vga,         शून्य);
अटल DEVICE_ATTR(temp6_label, S_IRUGO, label_SKIN,        शून्य);
अटल DEVICE_ATTR(pwm1, S_IRUGO | S_IWUSR, pwm_show, pwm_store);
अटल DEVICE_ATTR(pwm1_enable,
		   S_IRUGO | S_IWUSR, pwm_enable_show, pwm_enable_store);

अटल काष्ठा attribute *compal_platक्रमm_attrs[] = अणु
	&dev_attr_wake_up_pme.attr,
	&dev_attr_wake_up_modem.attr,
	&dev_attr_wake_up_lan.attr,
	&dev_attr_wake_up_wlan.attr,
	&dev_attr_wake_up_key.attr,
	&dev_attr_wake_up_mouse.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group compal_platक्रमm_attr_group = अणु
	.attrs = compal_platक्रमm_attrs
पूर्ण;

अटल काष्ठा attribute *compal_hwmon_attrs[] = अणु
	&dev_attr_pwm1_enable.attr,
	&dev_attr_pwm1.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_temp1_input.attr,
	&dev_attr_temp2_input.attr,
	&dev_attr_temp3_input.attr,
	&dev_attr_temp4_input.attr,
	&dev_attr_temp5_input.attr,
	&dev_attr_temp6_input.attr,
	&dev_attr_temp1_label.attr,
	&dev_attr_temp2_label.attr,
	&dev_attr_temp3_label.attr,
	&dev_attr_temp4_label.attr,
	&dev_attr_temp5_label.attr,
	&dev_attr_temp6_label.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(compal_hwmon);

अटल पूर्णांक compal_probe(काष्ठा platक्रमm_device *);
अटल पूर्णांक compal_हटाओ(काष्ठा platक्रमm_device *);
अटल काष्ठा platक्रमm_driver compal_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
	पूर्ण,
	.probe	= compal_probe,
	.हटाओ	= compal_हटाओ,
पूर्ण;

अटल क्रमागत घातer_supply_property compal_bat_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TEMP_AMBIENT,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

अटल काष्ठा backlight_device *compalbl_device;

अटल काष्ठा platक्रमm_device *compal_device;

अटल काष्ठा rfसमाप्त *wअगरi_rfसमाप्त;
अटल काष्ठा rfसमाप्त *bt_rfसमाप्त;





/* =================================== */
/* Initialization & clean-up functions */
/* =================================== */

अटल पूर्णांक dmi_check_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Identified laptop model '%s'\n", id->ident);
	extra_features = false;
	वापस 1;
पूर्ण

अटल पूर्णांक dmi_check_cb_extra(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Identified laptop model '%s', enabling extra features\n",
		id->ident);
	extra_features = true;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id compal_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "FL90/IFL90",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "IFL90"),
			DMI_MATCH(DMI_BOARD_VERSION, "IFT00"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "FL90/IFL90",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "IFL90"),
			DMI_MATCH(DMI_BOARD_VERSION, "REFERENCE"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "FL91/IFL91",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "IFL91"),
			DMI_MATCH(DMI_BOARD_VERSION, "IFT00"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "FL92/JFL92",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "JFL92"),
			DMI_MATCH(DMI_BOARD_VERSION, "IFT00"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "FT00/IFT00",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "IFT00"),
			DMI_MATCH(DMI_BOARD_VERSION, "IFT00"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Mini 9",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 910"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Mini 10",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1010"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Mini 10v",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1011"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Mini 1012",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1012"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Inspiron 11z",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1110"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Dell Mini 12",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1210"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "JHL90",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "JHL90"),
			DMI_MATCH(DMI_BOARD_VERSION, "REFERENCE"),
		पूर्ण,
		.callback = dmi_check_cb_extra
	पूर्ण,
	अणु
		.ident = "KHLB2",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "KHLB2"),
			DMI_MATCH(DMI_BOARD_VERSION, "REFERENCE"),
		पूर्ण,
		.callback = dmi_check_cb_extra
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, compal_dmi_table);

अटल स्थिर काष्ठा घातer_supply_desc psy_bat_desc = अणु
	.name		= DRIVER_NAME,
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= compal_bat_properties,
	.num_properties	= ARRAY_SIZE(compal_bat_properties),
	.get_property	= bat_get_property,
	.set_property	= bat_set_property,
	.property_is_ग_लिखोable = bat_ग_लिखोable_property,
पूर्ण;

अटल व्योम initialize_घातer_supply_data(काष्ठा compal_data *data)
अणु
	ec_पढ़ो_sequence(BAT_MANUFACTURER_NAME_ADDR,
					data->bat_manufacturer_name,
					BAT_MANUFACTURER_NAME_LEN);
	data->bat_manufacturer_name[BAT_MANUFACTURER_NAME_LEN] = 0;

	ec_पढ़ो_sequence(BAT_MODEL_NAME_ADDR,
					data->bat_model_name,
					BAT_MODEL_NAME_LEN);
	data->bat_model_name[BAT_MODEL_NAME_LEN] = 0;

	scnम_लिखो(data->bat_serial_number, BAT_SERIAL_NUMBER_LEN + 1, "%d",
				ec_पढ़ो_u16(BAT_SERIAL_NUMBER_ADDR));
पूर्ण

अटल व्योम initialize_fan_control_data(काष्ठा compal_data *data)
अणु
	data->pwm_enable = 2; /* Keep motherboard in control क्रम now */
	data->curr_pwm = 255; /* Try not to cause a CPU_on_fire exception
				 अगर we take over... */
पूर्ण

अटल पूर्णांक setup_rfसमाप्त(व्योम)
अणु
	पूर्णांक ret;

	wअगरi_rfसमाप्त = rfसमाप्त_alloc("compal-wifi", &compal_device->dev,
				RFKILL_TYPE_WLAN, &compal_rfसमाप्त_ops,
				(व्योम *) WIRELESS_WLAN);
	अगर (!wअगरi_rfसमाप्त)
		वापस -ENOMEM;

	ret = rfसमाप्त_रेजिस्टर(wअगरi_rfसमाप्त);
	अगर (ret)
		जाओ err_wअगरi;

	bt_rfसमाप्त = rfसमाप्त_alloc("compal-bluetooth", &compal_device->dev,
				RFKILL_TYPE_BLUETOOTH, &compal_rfसमाप्त_ops,
				(व्योम *) WIRELESS_BT);
	अगर (!bt_rfसमाप्त) अणु
		ret = -ENOMEM;
		जाओ err_allocate_bt;
	पूर्ण
	ret = rfसमाप्त_रेजिस्टर(bt_rfसमाप्त);
	अगर (ret)
		जाओ err_रेजिस्टर_bt;

	वापस 0;

err_रेजिस्टर_bt:
	rfसमाप्त_destroy(bt_rfसमाप्त);

err_allocate_bt:
	rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);

err_wअगरi:
	rfसमाप्त_destroy(wअगरi_rfसमाप्त);

	वापस ret;
पूर्ण

अटल पूर्णांक __init compal_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled) अणु
		pr_err("ACPI needs to be enabled for this driver to work!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!क्रमce && !dmi_check_प्रणाली(compal_dmi_table)) अणु
		pr_err("Motherboard not recognized (You could try the module's force-parameter)\n");
		वापस -ENODEV;
	पूर्ण

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		काष्ठा backlight_properties props;
		स_रखो(&props, 0, माप(काष्ठा backlight_properties));
		props.type = BACKLIGHT_PLATFORM;
		props.max_brightness = BACKLIGHT_LEVEL_MAX;
		compalbl_device = backlight_device_रेजिस्टर(DRIVER_NAME,
							    शून्य, शून्य,
							    &compalbl_ops,
							    &props);
		अगर (IS_ERR(compalbl_device))
			वापस PTR_ERR(compalbl_device);
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&compal_driver);
	अगर (ret)
		जाओ err_backlight;

	compal_device = platक्रमm_device_alloc(DRIVER_NAME, -1);
	अगर (!compal_device) अणु
		ret = -ENOMEM;
		जाओ err_platक्रमm_driver;
	पूर्ण

	ret = platक्रमm_device_add(compal_device); /* This calls compal_probe */
	अगर (ret)
		जाओ err_platक्रमm_device;

	ret = setup_rfसमाप्त();
	अगर (ret)
		जाओ err_rfसमाप्त;

	pr_info("Driver " DRIVER_VERSION " successfully loaded\n");
	वापस 0;

err_rfसमाप्त:
	platक्रमm_device_del(compal_device);

err_platक्रमm_device:
	platक्रमm_device_put(compal_device);

err_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&compal_driver);

err_backlight:
	backlight_device_unरेजिस्टर(compalbl_device);

	वापस ret;
पूर्ण

अटल पूर्णांक compal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा compal_data *data;
	काष्ठा device *hwmon_dev;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	अगर (!extra_features)
		वापस 0;

	/* Fan control */
	data = devm_kzalloc(&pdev->dev, माप(काष्ठा compal_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	initialize_fan_control_data(data);

	err = sysfs_create_group(&pdev->dev.kobj, &compal_platक्रमm_attr_group);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
							   "compal", data,
							   compal_hwmon_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		err = PTR_ERR(hwmon_dev);
		जाओ हटाओ;
	पूर्ण

	/* Power supply */
	initialize_घातer_supply_data(data);
	psy_cfg.drv_data = data;
	data->psy = घातer_supply_रेजिस्टर(&compal_device->dev, &psy_bat_desc,
					  &psy_cfg);
	अगर (IS_ERR(data->psy)) अणु
		err = PTR_ERR(data->psy);
		जाओ हटाओ;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

हटाओ:
	sysfs_हटाओ_group(&pdev->dev.kobj, &compal_platक्रमm_attr_group);
	वापस err;
पूर्ण

अटल व्योम __निकास compal_cleanup(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(compal_device);
	platक्रमm_driver_unरेजिस्टर(&compal_driver);
	backlight_device_unरेजिस्टर(compalbl_device);
	rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);
	rfसमाप्त_unरेजिस्टर(bt_rfसमाप्त);
	rfसमाप्त_destroy(wअगरi_rfसमाप्त);
	rfसमाप्त_destroy(bt_rfसमाप्त);

	pr_info("Driver unloaded\n");
पूर्ण

अटल पूर्णांक compal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा compal_data *data;

	अगर (!extra_features)
		वापस 0;

	pr_info("Unloading: resetting fan control to motherboard\n");
	pwm_disable_control();

	data = platक्रमm_get_drvdata(pdev);
	घातer_supply_unरेजिस्टर(data->psy);

	sysfs_हटाओ_group(&pdev->dev.kobj, &compal_platक्रमm_attr_group);

	वापस 0;
पूर्ण


module_init(compal_init);
module_निकास(compal_cleanup);

MODULE_AUTHOR("Cezary Jackiewicz");
MODULE_AUTHOR("Roald Frederickx (roald.frederickx@gmail.com)");
MODULE_DESCRIPTION("Compal Laptop Support");
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL");
