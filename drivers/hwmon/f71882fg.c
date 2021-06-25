<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2006 by Hans Edgington <hans@edgington.nl>              *
 *   Copyright (C) 2007-2011 Hans de Goede <hdegoede@redhat.com>           *
 *                                                                         *
 ***************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

#घोषणा DRVNAME "f71882fg"

#घोषणा SIO_F71858FG_LD_HWM	0x02	/* Hardware monitor logical device */
#घोषणा SIO_F71882FG_LD_HWM	0x04	/* Hardware monitor logical device */
#घोषणा SIO_UNLOCK_KEY		0x87	/* Key to enable Super-I/O */
#घोषणा SIO_LOCK_KEY		0xAA	/* Key to disable Super-I/O */

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_DEVREV		0x22	/* Device revision */
#घोषणा SIO_REG_MANID		0x23	/* Fपूर्णांकek ID (2 bytes) */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */

#घोषणा SIO_FINTEK_ID		0x1934	/* Manufacturers ID */
#घोषणा SIO_F71808E_ID		0x0901	/* Chipset ID */
#घोषणा SIO_F71808A_ID		0x1001	/* Chipset ID */
#घोषणा SIO_F71858_ID		0x0507  /* Chipset ID */
#घोषणा SIO_F71862_ID		0x0601	/* Chipset ID */
#घोषणा SIO_F71868_ID		0x1106	/* Chipset ID */
#घोषणा SIO_F71869_ID		0x0814	/* Chipset ID */
#घोषणा SIO_F71869A_ID		0x1007	/* Chipset ID */
#घोषणा SIO_F71882_ID		0x0541	/* Chipset ID */
#घोषणा SIO_F71889_ID		0x0723	/* Chipset ID */
#घोषणा SIO_F71889E_ID		0x0909	/* Chipset ID */
#घोषणा SIO_F71889A_ID		0x1005	/* Chipset ID */
#घोषणा SIO_F8000_ID		0x0581	/* Chipset ID */
#घोषणा SIO_F81768D_ID		0x1210	/* Chipset ID */
#घोषणा SIO_F81865_ID		0x0704	/* Chipset ID */
#घोषणा SIO_F81866_ID		0x1010	/* Chipset ID */

#घोषणा REGION_LENGTH		8
#घोषणा ADDR_REG_OFFSET		5
#घोषणा DATA_REG_OFFSET		6

#घोषणा F71882FG_REG_IN_STATUS		0x12 /* f7188x only */
#घोषणा F71882FG_REG_IN_BEEP		0x13 /* f7188x only */
#घोषणा F71882FG_REG_IN(nr)		(0x20  + (nr))
#घोषणा F71882FG_REG_IN1_HIGH		0x32 /* f7188x only */

#घोषणा F81866_REG_IN_STATUS		0x16 /* F81866 only */
#घोषणा F81866_REG_IN_BEEP			0x17 /* F81866 only */
#घोषणा F81866_REG_IN1_HIGH		0x3a /* F81866 only */

#घोषणा F71882FG_REG_FAN(nr)		(0xA0 + (16 * (nr)))
#घोषणा F71882FG_REG_FAN_TARGET(nr)	(0xA2 + (16 * (nr)))
#घोषणा F71882FG_REG_FAN_FULL_SPEED(nr)	(0xA4 + (16 * (nr)))
#घोषणा F71882FG_REG_FAN_STATUS		0x92
#घोषणा F71882FG_REG_FAN_BEEP		0x93

#घोषणा F71882FG_REG_TEMP(nr)		(0x70 + 2 * (nr))
#घोषणा F71882FG_REG_TEMP_OVT(nr)	(0x80 + 2 * (nr))
#घोषणा F71882FG_REG_TEMP_HIGH(nr)	(0x81 + 2 * (nr))
#घोषणा F71882FG_REG_TEMP_STATUS	0x62
#घोषणा F71882FG_REG_TEMP_BEEP		0x63
#घोषणा F71882FG_REG_TEMP_CONFIG	0x69
#घोषणा F71882FG_REG_TEMP_HYST(nr)	(0x6C + (nr))
#घोषणा F71882FG_REG_TEMP_TYPE		0x6B
#घोषणा F71882FG_REG_TEMP_DIODE_OPEN	0x6F

#घोषणा F71882FG_REG_PWM(nr)		(0xA3 + (16 * (nr)))
#घोषणा F71882FG_REG_PWM_TYPE		0x94
#घोषणा F71882FG_REG_PWM_ENABLE		0x96

#घोषणा F71882FG_REG_FAN_HYST(nr)	(0x98 + (nr))

#घोषणा F71882FG_REG_FAN_FAULT_T	0x9F
#घोषणा F71882FG_FAN_NEG_TEMP_EN	0x20
#घोषणा F71882FG_FAN_PROG_SEL		0x80

#घोषणा F71882FG_REG_POINT_PWM(pwm, poपूर्णांक)	(0xAA + (poपूर्णांक) + (16 * (pwm)))
#घोषणा F71882FG_REG_POINT_TEMP(pwm, poपूर्णांक)	(0xA6 + (poपूर्णांक) + (16 * (pwm)))
#घोषणा F71882FG_REG_POINT_MAPPING(nr)		(0xAF + 16 * (nr))

#घोषणा	F71882FG_REG_START		0x01

#घोषणा F71882FG_MAX_INS		11

#घोषणा FAN_MIN_DETECT			366 /* Lowest detectable fanspeed */

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

क्रमागत chips अणु f71808e, f71808a, f71858fg, f71862fg, f71868a, f71869, f71869a,
	f71882fg, f71889fg, f71889ed, f71889a, f8000, f81768d, f81865f,
	f81866aपूर्ण;

अटल स्थिर अक्षर *स्थिर f71882fg_names[] = अणु
	"f71808e",
	"f71808a",
	"f71858fg",
	"f71862fg",
	"f71868a",
	"f71869", /* Both f71869f and f71869e, reg. compatible and same id */
	"f71869a",
	"f71882fg",
	"f71889fg", /* f81801u too, same id */
	"f71889ed",
	"f71889a",
	"f8000",
	"f81768d",
	"f81865f",
	"f81866a",
पूर्ण;

अटल स्थिर अक्षर f71882fg_has_in[][F71882FG_MAX_INS] = अणु
	[f71808e]	= अणु 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0 पूर्ण,
	[f71808a]	= अणु 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0 पूर्ण,
	[f71858fg]	= अणु 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	[f71862fg]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71868a]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 पूर्ण,
	[f71869]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71869a]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71882fg]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71889fg]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71889ed]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f71889a]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 पूर्ण,
	[f8000]		= अणु 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
	[f81768d]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण,
	[f81865f]	= अणु 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 पूर्ण,
	[f81866a]	= अणु 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर f71882fg_has_in1_alarm[] = अणु
	[f71808e]	= 0,
	[f71808a]	= 0,
	[f71858fg]	= 0,
	[f71862fg]	= 0,
	[f71868a]	= 0,
	[f71869]	= 0,
	[f71869a]	= 0,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
पूर्ण;

अटल स्थिर अक्षर f71882fg_fan_has_beep[] = अणु
	[f71808e]	= 0,
	[f71808a]	= 0,
	[f71858fg]	= 0,
	[f71862fg]	= 1,
	[f71868a]	= 1,
	[f71869]	= 1,
	[f71869a]	= 1,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
पूर्ण;

अटल स्थिर अक्षर f71882fg_nr_fans[] = अणु
	[f71808e]	= 3,
	[f71808a]	= 2, /* +1 fan which is monitor + simple pwm only */
	[f71858fg]	= 3,
	[f71862fg]	= 3,
	[f71868a]	= 3,
	[f71869]	= 3,
	[f71869a]	= 3,
	[f71882fg]	= 4,
	[f71889fg]	= 3,
	[f71889ed]	= 3,
	[f71889a]	= 3,
	[f8000]		= 3, /* +1 fan which is monitor only */
	[f81768d]	= 3,
	[f81865f]	= 2,
	[f81866a]	= 3,
पूर्ण;

अटल स्थिर अक्षर f71882fg_temp_has_beep[] = अणु
	[f71808e]	= 0,
	[f71808a]	= 1,
	[f71858fg]	= 0,
	[f71862fg]	= 1,
	[f71868a]	= 1,
	[f71869]	= 1,
	[f71869a]	= 1,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
पूर्ण;

अटल स्थिर अक्षर f71882fg_nr_temps[] = अणु
	[f71808e]	= 2,
	[f71808a]	= 2,
	[f71858fg]	= 3,
	[f71862fg]	= 3,
	[f71868a]	= 3,
	[f71869]	= 3,
	[f71869a]	= 3,
	[f71882fg]	= 3,
	[f71889fg]	= 3,
	[f71889ed]	= 3,
	[f71889a]	= 3,
	[f8000]		= 3,
	[f81768d]	= 3,
	[f81865f]	= 2,
	[f81866a]	= 3,
पूर्ण;

अटल काष्ठा platक्रमm_device *f71882fg_pdev;

/* Super-I/O Function prototypes */
अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक base, पूर्णांक reg);
अटल अंतरभूत पूर्णांक superio_inw(पूर्णांक base, पूर्णांक reg);
अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base);
अटल अंतरभूत व्योम superio_select(पूर्णांक base, पूर्णांक ld);
अटल अंतरभूत व्योम superio_निकास(पूर्णांक base);

काष्ठा f71882fg_sio_data अणु
	क्रमागत chips type;
पूर्ण;

काष्ठा f71882fg_data अणु
	अचिन्हित लघु addr;
	क्रमागत chips type;
	काष्ठा device *hwmon_dev;

	काष्ठा mutex update_lock;
	पूर्णांक temp_start;			/* temp numbering start (0 or 1) */
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अक्षर स्वतः_poपूर्णांक_temp_चिन्हित;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ last_limits;	/* In jअगरfies */

	/* Register Values */
	u8	in[F71882FG_MAX_INS];
	u8	in1_max;
	u8	in_status;
	u8	in_beep;
	u16	fan[4];
	u16	fan_target[4];
	u16	fan_full_speed[4];
	u8	fan_status;
	u8	fan_beep;
	/*
	 * Note: all models have max 3 temperature channels, but on some
	 * they are addressed as 0-2 and on others as 1-3, so क्रम coding
	 * convenience we reserve space क्रम 4 channels
	 */
	u16	temp[4];
	u8	temp_ovt[4];
	u8	temp_high[4];
	u8	temp_hyst[2]; /* 2 hysts stored per reg */
	u8	temp_type[4];
	u8	temp_status;
	u8	temp_beep;
	u8	temp_diode_खोलो;
	u8	temp_config;
	u8	pwm[4];
	u8	pwm_enable;
	u8	pwm_स्वतः_poपूर्णांक_hyst[2];
	u8	pwm_स्वतः_poपूर्णांक_mapping[4];
	u8	pwm_स्वतः_poपूर्णांक_pwm[4][5];
	s8	pwm_स्वतः_poपूर्णांक_temp[4][4];
पूर्ण;

/* Sysfs in */
अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf);
अटल sमाप_प्रकार show_in_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_in_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_in_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_in_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_in_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
/* Sysfs Fan */
अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf);
अटल sमाप_प्रकार show_fan_full_speed(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_fan_full_speed(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_fan_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_fan_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_fan_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
/* Sysfs Temp */
अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार show_temp_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_temp_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_temp_max_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_temp_max_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_temp_crit(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_temp_crit(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_temp_crit_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार show_temp_type(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार show_temp_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार store_temp_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_temp_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
अटल sमाप_प्रकार show_temp_fault(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf);
/* PWM and Auto poपूर्णांक control */
अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf);
अटल sमाप_प्रकार store_pwm(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_simple_pwm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_simple_pwm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_enable(काष्ठा device *dev,
	काष्ठा device_attribute	*devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_पूर्णांकerpolate(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_पूर्णांकerpolate(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_channel(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_channel(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp_hyst(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_temp_hyst(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, अक्षर *buf);
अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
	काष्ठा device_attribute *devattr, स्थिर अक्षर *buf, माप_प्रकार count);
/* Sysfs misc */
अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf);

अटल पूर्णांक f71882fg_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक f71882fg_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल काष्ठा platक्रमm_driver f71882fg_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= f71882fg_probe,
	.हटाओ		= f71882fg_हटाओ,
पूर्ण;

अटल DEVICE_ATTR_RO(name);

/*
 * Temp attr क्रम the f71858fg, the f71858fg is special as it has its
 * temperature indexes start at 0 (the others start at 1)
 */
अटल काष्ठा sensor_device_attribute_2 f71858fg_temp_attr[] = अणु
	SENSOR_ATTR_2(temp1_input, S_IRUGO, show_temp, शून्य, 0, 0),
	SENSOR_ATTR_2(temp1_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 0),
	SENSOR_ATTR_2(temp1_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 0),
	SENSOR_ATTR_2(temp1_max_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 0),
	SENSOR_ATTR_2(temp1_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 0),
	SENSOR_ATTR_2(temp1_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 0),
	SENSOR_ATTR_2(temp1_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 4),
	SENSOR_ATTR_2(temp1_fault, S_IRUGO, show_temp_fault, शून्य, 0, 0),
	SENSOR_ATTR_2(temp2_input, S_IRUGO, show_temp, शून्य, 0, 1),
	SENSOR_ATTR_2(temp2_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 1),
	SENSOR_ATTR_2(temp2_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 1),
	SENSOR_ATTR_2(temp2_max_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 1),
	SENSOR_ATTR_2(temp2_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 1),
	SENSOR_ATTR_2(temp2_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 1),
	SENSOR_ATTR_2(temp2_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 5),
	SENSOR_ATTR_2(temp2_fault, S_IRUGO, show_temp_fault, शून्य, 0, 1),
	SENSOR_ATTR_2(temp3_input, S_IRUGO, show_temp, शून्य, 0, 2),
	SENSOR_ATTR_2(temp3_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 2),
	SENSOR_ATTR_2(temp3_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 2),
	SENSOR_ATTR_2(temp3_max_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 2),
	SENSOR_ATTR_2(temp3_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 2),
	SENSOR_ATTR_2(temp3_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 2),
	SENSOR_ATTR_2(temp3_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 6),
	SENSOR_ATTR_2(temp3_fault, S_IRUGO, show_temp_fault, शून्य, 0, 2),
पूर्ण;

/* Temp attr क्रम the standard models */
अटल काष्ठा sensor_device_attribute_2 fxxxx_temp_attr[3][9] = अणु अणु
	SENSOR_ATTR_2(temp1_input, S_IRUGO, show_temp, शून्य, 0, 1),
	SENSOR_ATTR_2(temp1_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 1),
	SENSOR_ATTR_2(temp1_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 1),
	/*
	 * Should really be temp1_max_alarm, but older versions did not handle
	 * the max and crit alarms separately and lm_sensors v2 depends on the
	 * presence of temp#_alarm files. The same goes क्रम temp2/3 _alarm.
	 */
	SENSOR_ATTR_2(temp1_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 1),
	SENSOR_ATTR_2(temp1_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 1),
	SENSOR_ATTR_2(temp1_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 1),
	SENSOR_ATTR_2(temp1_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 5),
	SENSOR_ATTR_2(temp1_type, S_IRUGO, show_temp_type, शून्य, 0, 1),
	SENSOR_ATTR_2(temp1_fault, S_IRUGO, show_temp_fault, शून्य, 0, 1),
पूर्ण, अणु
	SENSOR_ATTR_2(temp2_input, S_IRUGO, show_temp, शून्य, 0, 2),
	SENSOR_ATTR_2(temp2_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 2),
	SENSOR_ATTR_2(temp2_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 2),
	/* Should be temp2_max_alarm, see temp1_alarm note */
	SENSOR_ATTR_2(temp2_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 2),
	SENSOR_ATTR_2(temp2_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 2),
	SENSOR_ATTR_2(temp2_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 2),
	SENSOR_ATTR_2(temp2_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 6),
	SENSOR_ATTR_2(temp2_type, S_IRUGO, show_temp_type, शून्य, 0, 2),
	SENSOR_ATTR_2(temp2_fault, S_IRUGO, show_temp_fault, शून्य, 0, 2),
पूर्ण, अणु
	SENSOR_ATTR_2(temp3_input, S_IRUGO, show_temp, शून्य, 0, 3),
	SENSOR_ATTR_2(temp3_max, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 3),
	SENSOR_ATTR_2(temp3_max_hyst, S_IRUGO|S_IWUSR, show_temp_max_hyst,
		store_temp_max_hyst, 0, 3),
	/* Should be temp3_max_alarm, see temp1_alarm note */
	SENSOR_ATTR_2(temp3_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 3),
	SENSOR_ATTR_2(temp3_crit, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 3),
	SENSOR_ATTR_2(temp3_crit_hyst, S_IRUGO, show_temp_crit_hyst, शून्य,
		0, 3),
	SENSOR_ATTR_2(temp3_crit_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 7),
	SENSOR_ATTR_2(temp3_type, S_IRUGO, show_temp_type, शून्य, 0, 3),
	SENSOR_ATTR_2(temp3_fault, S_IRUGO, show_temp_fault, शून्य, 0, 3),
पूर्ण पूर्ण;

/* Temp attr क्रम models which can beep on temp alarm */
अटल काष्ठा sensor_device_attribute_2 fxxxx_temp_beep_attr[3][2] = अणु अणु
	SENSOR_ATTR_2(temp1_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 1),
	SENSOR_ATTR_2(temp1_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 5),
पूर्ण, अणु
	SENSOR_ATTR_2(temp2_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 2),
	SENSOR_ATTR_2(temp2_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 6),
पूर्ण, अणु
	SENSOR_ATTR_2(temp3_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 3),
	SENSOR_ATTR_2(temp3_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 7),
पूर्ण पूर्ण;

अटल काष्ठा sensor_device_attribute_2 f81866_temp_beep_attr[3][2] = अणु अणु
	SENSOR_ATTR_2(temp1_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 0),
	SENSOR_ATTR_2(temp1_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 4),
पूर्ण, अणु
	SENSOR_ATTR_2(temp2_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 1),
	SENSOR_ATTR_2(temp2_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 5),
पूर्ण, अणु
	SENSOR_ATTR_2(temp3_max_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 2),
	SENSOR_ATTR_2(temp3_crit_beep, S_IRUGO|S_IWUSR, show_temp_beep,
		store_temp_beep, 0, 6),
पूर्ण पूर्ण;

/*
 * Temp attr क्रम the f8000
 * Note on the f8000 temp_ovt (crit) is used as max, and temp_high (max)
 * is used as hysteresis value to clear alarms
 * Also like the f71858fg its temperature indexes start at 0
 */
अटल काष्ठा sensor_device_attribute_2 f8000_temp_attr[] = अणु
	SENSOR_ATTR_2(temp1_input, S_IRUGO, show_temp, शून्य, 0, 0),
	SENSOR_ATTR_2(temp1_max, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 0),
	SENSOR_ATTR_2(temp1_max_hyst, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 0),
	SENSOR_ATTR_2(temp1_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 4),
	SENSOR_ATTR_2(temp1_fault, S_IRUGO, show_temp_fault, शून्य, 0, 0),
	SENSOR_ATTR_2(temp2_input, S_IRUGO, show_temp, शून्य, 0, 1),
	SENSOR_ATTR_2(temp2_max, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 1),
	SENSOR_ATTR_2(temp2_max_hyst, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 1),
	SENSOR_ATTR_2(temp2_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 5),
	SENSOR_ATTR_2(temp2_fault, S_IRUGO, show_temp_fault, शून्य, 0, 1),
	SENSOR_ATTR_2(temp3_input, S_IRUGO, show_temp, शून्य, 0, 2),
	SENSOR_ATTR_2(temp3_max, S_IRUGO|S_IWUSR, show_temp_crit,
		store_temp_crit, 0, 2),
	SENSOR_ATTR_2(temp3_max_hyst, S_IRUGO|S_IWUSR, show_temp_max,
		store_temp_max, 0, 2),
	SENSOR_ATTR_2(temp3_alarm, S_IRUGO, show_temp_alarm, शून्य, 0, 6),
	SENSOR_ATTR_2(temp3_fault, S_IRUGO, show_temp_fault, शून्य, 0, 2),
पूर्ण;

/* in attr क्रम all models */
अटल काष्ठा sensor_device_attribute_2 fxxxx_in_attr[] = अणु
	SENSOR_ATTR_2(in0_input, S_IRUGO, show_in, शून्य, 0, 0),
	SENSOR_ATTR_2(in1_input, S_IRUGO, show_in, शून्य, 0, 1),
	SENSOR_ATTR_2(in2_input, S_IRUGO, show_in, शून्य, 0, 2),
	SENSOR_ATTR_2(in3_input, S_IRUGO, show_in, शून्य, 0, 3),
	SENSOR_ATTR_2(in4_input, S_IRUGO, show_in, शून्य, 0, 4),
	SENSOR_ATTR_2(in5_input, S_IRUGO, show_in, शून्य, 0, 5),
	SENSOR_ATTR_2(in6_input, S_IRUGO, show_in, शून्य, 0, 6),
	SENSOR_ATTR_2(in7_input, S_IRUGO, show_in, शून्य, 0, 7),
	SENSOR_ATTR_2(in8_input, S_IRUGO, show_in, शून्य, 0, 8),
	SENSOR_ATTR_2(in9_input, S_IRUGO, show_in, शून्य, 0, 9),
	SENSOR_ATTR_2(in10_input, S_IRUGO, show_in, शून्य, 0, 10),
पूर्ण;

/* For models with in1 alarm capability */
अटल काष्ठा sensor_device_attribute_2 fxxxx_in1_alarm_attr[] = अणु
	SENSOR_ATTR_2(in1_max, S_IRUGO|S_IWUSR, show_in_max, store_in_max,
		0, 1),
	SENSOR_ATTR_2(in1_beep, S_IRUGO|S_IWUSR, show_in_beep, store_in_beep,
		0, 1),
	SENSOR_ATTR_2(in1_alarm, S_IRUGO, show_in_alarm, शून्य, 0, 1),
पूर्ण;

/* Fan / PWM attr common to all models */
अटल काष्ठा sensor_device_attribute_2 fxxxx_fan_attr[4][6] = अणु अणु
	SENSOR_ATTR_2(fan1_input, S_IRUGO, show_fan, शून्य, 0, 0),
	SENSOR_ATTR_2(fan1_full_speed, S_IRUGO|S_IWUSR,
		      show_fan_full_speed,
		      store_fan_full_speed, 0, 0),
	SENSOR_ATTR_2(fan1_alarm, S_IRUGO, show_fan_alarm, शून्य, 0, 0),
	SENSOR_ATTR_2(pwm1, S_IRUGO|S_IWUSR, show_pwm, store_pwm, 0, 0),
	SENSOR_ATTR_2(pwm1_enable, S_IRUGO|S_IWUSR, show_pwm_enable,
		      store_pwm_enable, 0, 0),
	SENSOR_ATTR_2(pwm1_पूर्णांकerpolate, S_IRUGO|S_IWUSR,
		      show_pwm_पूर्णांकerpolate, store_pwm_पूर्णांकerpolate, 0, 0),
पूर्ण, अणु
	SENSOR_ATTR_2(fan2_input, S_IRUGO, show_fan, शून्य, 0, 1),
	SENSOR_ATTR_2(fan2_full_speed, S_IRUGO|S_IWUSR,
		      show_fan_full_speed,
		      store_fan_full_speed, 0, 1),
	SENSOR_ATTR_2(fan2_alarm, S_IRUGO, show_fan_alarm, शून्य, 0, 1),
	SENSOR_ATTR_2(pwm2, S_IRUGO|S_IWUSR, show_pwm, store_pwm, 0, 1),
	SENSOR_ATTR_2(pwm2_enable, S_IRUGO|S_IWUSR, show_pwm_enable,
		      store_pwm_enable, 0, 1),
	SENSOR_ATTR_2(pwm2_पूर्णांकerpolate, S_IRUGO|S_IWUSR,
		      show_pwm_पूर्णांकerpolate, store_pwm_पूर्णांकerpolate, 0, 1),
पूर्ण, अणु
	SENSOR_ATTR_2(fan3_input, S_IRUGO, show_fan, शून्य, 0, 2),
	SENSOR_ATTR_2(fan3_full_speed, S_IRUGO|S_IWUSR,
		      show_fan_full_speed,
		      store_fan_full_speed, 0, 2),
	SENSOR_ATTR_2(fan3_alarm, S_IRUGO, show_fan_alarm, शून्य, 0, 2),
	SENSOR_ATTR_2(pwm3, S_IRUGO|S_IWUSR, show_pwm, store_pwm, 0, 2),
	SENSOR_ATTR_2(pwm3_enable, S_IRUGO|S_IWUSR, show_pwm_enable,
		      store_pwm_enable, 0, 2),
	SENSOR_ATTR_2(pwm3_पूर्णांकerpolate, S_IRUGO|S_IWUSR,
		      show_pwm_पूर्णांकerpolate, store_pwm_पूर्णांकerpolate, 0, 2),
पूर्ण, अणु
	SENSOR_ATTR_2(fan4_input, S_IRUGO, show_fan, शून्य, 0, 3),
	SENSOR_ATTR_2(fan4_full_speed, S_IRUGO|S_IWUSR,
		      show_fan_full_speed,
		      store_fan_full_speed, 0, 3),
	SENSOR_ATTR_2(fan4_alarm, S_IRUGO, show_fan_alarm, शून्य, 0, 3),
	SENSOR_ATTR_2(pwm4, S_IRUGO|S_IWUSR, show_pwm, store_pwm, 0, 3),
	SENSOR_ATTR_2(pwm4_enable, S_IRUGO|S_IWUSR, show_pwm_enable,
		      store_pwm_enable, 0, 3),
	SENSOR_ATTR_2(pwm4_पूर्णांकerpolate, S_IRUGO|S_IWUSR,
		      show_pwm_पूर्णांकerpolate, store_pwm_पूर्णांकerpolate, 0, 3),
पूर्ण पूर्ण;

/* Attr क्रम the third fan of the f71808a, which only has manual pwm */
अटल काष्ठा sensor_device_attribute_2 f71808a_fan3_attr[] = अणु
	SENSOR_ATTR_2(fan3_input, S_IRUGO, show_fan, शून्य, 0, 2),
	SENSOR_ATTR_2(fan3_alarm, S_IRUGO, show_fan_alarm, शून्य, 0, 2),
	SENSOR_ATTR_2(pwm3, S_IRUGO|S_IWUSR,
		      show_simple_pwm, store_simple_pwm, 0, 2),
पूर्ण;

/* Attr क्रम models which can beep on Fan alarm */
अटल काष्ठा sensor_device_attribute_2 fxxxx_fan_beep_attr[] = अणु
	SENSOR_ATTR_2(fan1_beep, S_IRUGO|S_IWUSR, show_fan_beep,
		store_fan_beep, 0, 0),
	SENSOR_ATTR_2(fan2_beep, S_IRUGO|S_IWUSR, show_fan_beep,
		store_fan_beep, 0, 1),
	SENSOR_ATTR_2(fan3_beep, S_IRUGO|S_IWUSR, show_fan_beep,
		store_fan_beep, 0, 2),
	SENSOR_ATTR_2(fan4_beep, S_IRUGO|S_IWUSR, show_fan_beep,
		store_fan_beep, 0, 3),
पूर्ण;

/*
 * PWM attr क्रम the f71862fg, fewer pwms and fewer zones per pwm than the
 * standard models
 */
अटल काष्ठा sensor_device_attribute_2 f71862fg_स्वतः_pwm_attr[3][7] = अणु अणु
	SENSOR_ATTR_2(pwm1_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 0),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm2_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 1),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm3_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 2),
पूर्ण पूर्ण;

/*
 * PWM attr क्रम the f71808e/f71869, almost identical to the f71862fg, but the
 * pwm setting when the temperature is above the pwmX_स्वतः_poपूर्णांक1_temp can be
 * programmed instead of being hardcoded to 0xff
 */
अटल काष्ठा sensor_device_attribute_2 f71869_स्वतः_pwm_attr[3][8] = अणु अणु
	SENSOR_ATTR_2(pwm1_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 0),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm2_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 1),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm3_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 2),
पूर्ण पूर्ण;

/* PWM attr क्रम the standard models */
अटल काष्ठा sensor_device_attribute_2 fxxxx_स्वतः_pwm_attr[4][14] = अणु अणु
	SENSOR_ATTR_2(pwm1_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 0),
	SENSOR_ATTR_2(pwm1_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 0),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm2_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 1),
	SENSOR_ATTR_2(pwm2_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 1),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm3_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 2),
	SENSOR_ATTR_2(pwm3_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 2),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm4_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 3),
	SENSOR_ATTR_2(pwm4_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 3),
पूर्ण पूर्ण;

/* Fan attr specअगरic to the f8000 (4th fan input can only measure speed) */
अटल काष्ठा sensor_device_attribute_2 f8000_fan_attr[] = अणु
	SENSOR_ATTR_2(fan4_input, S_IRUGO, show_fan, शून्य, 0, 3),
पूर्ण;

/*
 * PWM attr क्रम the f8000, zones mapped to temp instead of to pwm!
 * Also the रेजिस्टर block at offset A0 maps to TEMP1 (so our temp2, as the
 * F8000 starts counting temps at 0), B0 maps the TEMP2 and C0 maps to TEMP0
 */
अटल काष्ठा sensor_device_attribute_2 f8000_स्वतः_pwm_attr[3][14] = अणु अणु
	SENSOR_ATTR_2(pwm1_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 0),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 2),
	SENSOR_ATTR_2(temp1_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 2),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm2_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 1),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 0),
	SENSOR_ATTR_2(temp2_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 0),
पूर्ण, अणु
	SENSOR_ATTR_2(pwm3_स्वतः_channels_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_channel,
		      store_pwm_स्वतः_poपूर्णांक_channel, 0, 2),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक1_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      0, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक2_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      1, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक3_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      2, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक4_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      3, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक5_pwm, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_pwm, store_pwm_स्वतः_poपूर्णांक_pwm,
		      4, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक1_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      0, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक2_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      1, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक3_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      2, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक4_temp, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp, store_pwm_स्वतः_poपूर्णांक_temp,
		      3, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO|S_IWUSR,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      store_pwm_स्वतः_poपूर्णांक_temp_hyst,
		      0, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 1, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 2, 1),
	SENSOR_ATTR_2(temp3_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
		      show_pwm_स्वतः_poपूर्णांक_temp_hyst, शून्य, 3, 1),
पूर्ण पूर्ण;

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

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base)
अणु
	/* Don't step on other drivers' I/O space by accident */
	अगर (!request_muxed_region(base, 2, DRVNAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", base);
		वापस -EBUSY;
	पूर्ण

	/* according to the datasheet the key must be send twice! */
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

अटल अंतरभूत पूर्णांक fan_from_reg(u16 reg)
अणु
	वापस reg ? (1500000 / reg) : 0;
पूर्ण

अटल अंतरभूत u16 fan_to_reg(पूर्णांक fan)
अणु
	वापस fan ? (1500000 / fan) : 0;
पूर्ण

अटल u8 f71882fg_पढ़ो8(काष्ठा f71882fg_data *data, u8 reg)
अणु
	u8 val;

	outb(reg, data->addr + ADDR_REG_OFFSET);
	val = inb(data->addr + DATA_REG_OFFSET);

	वापस val;
पूर्ण

अटल u16 f71882fg_पढ़ो16(काष्ठा f71882fg_data *data, u8 reg)
अणु
	u16 val;

	val  = f71882fg_पढ़ो8(data, reg) << 8;
	val |= f71882fg_पढ़ो8(data, reg + 1);

	वापस val;
पूर्ण

अटल व्योम f71882fg_ग_लिखो8(काष्ठा f71882fg_data *data, u8 reg, u8 val)
अणु
	outb(reg, data->addr + ADDR_REG_OFFSET);
	outb(val, data->addr + DATA_REG_OFFSET);
पूर्ण

अटल व्योम f71882fg_ग_लिखो16(काष्ठा f71882fg_data *data, u8 reg, u16 val)
अणु
	f71882fg_ग_लिखो8(data, reg,     val >> 8);
	f71882fg_ग_लिखो8(data, reg + 1, val & 0xff);
पूर्ण

अटल u16 f71882fg_पढ़ो_temp(काष्ठा f71882fg_data *data, पूर्णांक nr)
अणु
	अगर (data->type == f71858fg)
		वापस f71882fg_पढ़ो16(data, F71882FG_REG_TEMP(nr));
	अन्यथा
		वापस f71882fg_पढ़ो8(data, F71882FG_REG_TEMP(nr));
पूर्ण

अटल काष्ठा f71882fg_data *f71882fg_update_device(काष्ठा device *dev)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक nr_fans = f71882fg_nr_fans[data->type];
	पूर्णांक nr_temps = f71882fg_nr_temps[data->type];
	पूर्णांक nr, reg, poपूर्णांक;

	mutex_lock(&data->update_lock);

	/* Update once every 60 seconds */
	अगर (समय_after(jअगरfies, data->last_limits + 60 * HZ) ||
			!data->valid) अणु
		अगर (f71882fg_has_in1_alarm[data->type]) अणु
			अगर (data->type == f81866a) अणु
				data->in1_max =
					f71882fg_पढ़ो8(data,
						       F81866_REG_IN1_HIGH);
				data->in_beep =
					f71882fg_पढ़ो8(data,
						       F81866_REG_IN_BEEP);
			पूर्ण अन्यथा अणु
				data->in1_max =
					f71882fg_पढ़ो8(data,
						       F71882FG_REG_IN1_HIGH);
				data->in_beep =
					f71882fg_पढ़ो8(data,
						       F71882FG_REG_IN_BEEP);
			पूर्ण
		पूर्ण

		/* Get High & boundary temps*/
		क्रम (nr = data->temp_start; nr < nr_temps + data->temp_start;
									nr++) अणु
			data->temp_ovt[nr] = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_OVT(nr));
			data->temp_high[nr] = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_HIGH(nr));
		पूर्ण

		अगर (data->type != f8000) अणु
			data->temp_hyst[0] = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_HYST(0));
			data->temp_hyst[1] = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_HYST(1));
		पूर्ण
		/* All but the f71858fg / f8000 have this रेजिस्टर */
		अगर ((data->type != f71858fg) && (data->type != f8000)) अणु
			reg  = f71882fg_पढ़ो8(data, F71882FG_REG_TEMP_TYPE);
			data->temp_type[1] = (reg & 0x02) ? 2 : 4;
			data->temp_type[2] = (reg & 0x04) ? 2 : 4;
			data->temp_type[3] = (reg & 0x08) ? 2 : 4;
		पूर्ण

		अगर (f71882fg_fan_has_beep[data->type])
			data->fan_beep = f71882fg_पढ़ो8(data,
						F71882FG_REG_FAN_BEEP);

		अगर (f71882fg_temp_has_beep[data->type])
			data->temp_beep = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_BEEP);

		data->pwm_enable = f71882fg_पढ़ो8(data,
						  F71882FG_REG_PWM_ENABLE);
		data->pwm_स्वतः_poपूर्णांक_hyst[0] =
			f71882fg_पढ़ो8(data, F71882FG_REG_FAN_HYST(0));
		data->pwm_स्वतः_poपूर्णांक_hyst[1] =
			f71882fg_पढ़ो8(data, F71882FG_REG_FAN_HYST(1));

		क्रम (nr = 0; nr < nr_fans; nr++) अणु
			data->pwm_स्वतः_poपूर्णांक_mapping[nr] =
			    f71882fg_पढ़ो8(data,
					   F71882FG_REG_POINT_MAPPING(nr));

			चयन (data->type) अणु
			शेष:
				क्रम (poपूर्णांक = 0; poपूर्णांक < 5; poपूर्णांक++) अणु
					data->pwm_स्वतः_poपूर्णांक_pwm[nr][poपूर्णांक] =
						f71882fg_पढ़ो8(data,
							F71882FG_REG_POINT_PWM
							(nr, poपूर्णांक));
				पूर्ण
				क्रम (poपूर्णांक = 0; poपूर्णांक < 4; poपूर्णांक++) अणु
					data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक] =
						f71882fg_पढ़ो8(data,
							F71882FG_REG_POINT_TEMP
							(nr, poपूर्णांक));
				पूर्ण
				अवरोध;
			हाल f71808e:
			हाल f71869:
				data->pwm_स्वतः_poपूर्णांक_pwm[nr][0] =
					f71882fg_पढ़ो8(data,
						F71882FG_REG_POINT_PWM(nr, 0));
				fallthrough;
			हाल f71862fg:
				data->pwm_स्वतः_poपूर्णांक_pwm[nr][1] =
					f71882fg_पढ़ो8(data,
						F71882FG_REG_POINT_PWM
						(nr, 1));
				data->pwm_स्वतः_poपूर्णांक_pwm[nr][4] =
					f71882fg_पढ़ो8(data,
						F71882FG_REG_POINT_PWM
						(nr, 4));
				data->pwm_स्वतः_poपूर्णांक_temp[nr][0] =
					f71882fg_पढ़ो8(data,
						F71882FG_REG_POINT_TEMP
						(nr, 0));
				data->pwm_स्वतः_poपूर्णांक_temp[nr][3] =
					f71882fg_पढ़ो8(data,
						F71882FG_REG_POINT_TEMP
						(nr, 3));
				अवरोध;
			पूर्ण
		पूर्ण
		data->last_limits = jअगरfies;
	पूर्ण

	/* Update every second */
	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		data->temp_status = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_STATUS);
		data->temp_diode_खोलो = f71882fg_पढ़ो8(data,
						F71882FG_REG_TEMP_DIODE_OPEN);
		क्रम (nr = data->temp_start; nr < nr_temps + data->temp_start;
									nr++)
			data->temp[nr] = f71882fg_पढ़ो_temp(data, nr);

		data->fan_status = f71882fg_पढ़ो8(data,
						F71882FG_REG_FAN_STATUS);
		क्रम (nr = 0; nr < nr_fans; nr++) अणु
			data->fan[nr] = f71882fg_पढ़ो16(data,
						F71882FG_REG_FAN(nr));
			data->fan_target[nr] =
			    f71882fg_पढ़ो16(data, F71882FG_REG_FAN_TARGET(nr));
			data->fan_full_speed[nr] =
			    f71882fg_पढ़ो16(data,
					    F71882FG_REG_FAN_FULL_SPEED(nr));
			data->pwm[nr] =
			    f71882fg_पढ़ो8(data, F71882FG_REG_PWM(nr));
		पूर्ण
		/* Some models have 1 more fan with limited capabilities */
		अगर (data->type == f71808a) अणु
			data->fan[2] = f71882fg_पढ़ो16(data,
						F71882FG_REG_FAN(2));
			data->pwm[2] = f71882fg_पढ़ो8(data,
							F71882FG_REG_PWM(2));
		पूर्ण
		अगर (data->type == f8000)
			data->fan[3] = f71882fg_पढ़ो16(data,
						F71882FG_REG_FAN(3));

		अगर (f71882fg_has_in1_alarm[data->type]) अणु
			अगर (data->type == f81866a)
				data->in_status = f71882fg_पढ़ो8(data,
						F81866_REG_IN_STATUS);

			अन्यथा
				data->in_status = f71882fg_पढ़ो8(data,
						F71882FG_REG_IN_STATUS);
		पूर्ण

		क्रम (nr = 0; nr < F71882FG_MAX_INS; nr++)
			अगर (f71882fg_has_in[data->type][nr])
				data->in[nr] = f71882fg_पढ़ो8(data,
							F71882FG_REG_IN(nr));

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* Sysfs Interface */
अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक speed = fan_from_reg(data->fan[nr]);

	अगर (speed == FAN_MIN_DETECT)
		speed = 0;

	वापस प्र_लिखो(buf, "%d\n", speed);
पूर्ण

अटल sमाप_प्रकार show_fan_full_speed(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक speed = fan_from_reg(data->fan_full_speed[nr]);
	वापस प्र_लिखो(buf, "%d\n", speed);
पूर्ण

अटल sमाप_प्रकार store_fan_full_speed(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, 23, 1500000);
	val = fan_to_reg(val);

	mutex_lock(&data->update_lock);
	f71882fg_ग_लिखो16(data, F71882FG_REG_FAN_FULL_SPEED(nr), val);
	data->fan_full_speed[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fan_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->fan_beep & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_fan_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_beep = f71882fg_पढ़ो8(data, F71882FG_REG_FAN_BEEP);
	अगर (val)
		data->fan_beep |= 1 << nr;
	अन्यथा
		data->fan_beep &= ~(1 << nr);

	f71882fg_ग_लिखो8(data, F71882FG_REG_FAN_BEEP, data->fan_beep);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fan_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->fan_status & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", data->in[nr] * 8);
पूर्ण

अटल sमाप_प्रकार show_in_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->in1_max * 8);
पूर्ण

अटल sमाप_प्रकार store_in_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 8;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	अगर (data->type == f81866a)
		f71882fg_ग_लिखो8(data, F81866_REG_IN1_HIGH, val);
	अन्यथा
		f71882fg_ग_लिखो8(data, F71882FG_REG_IN1_HIGH, val);
	data->in1_max = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_in_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->in_beep & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_in_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (data->type == f81866a)
		data->in_beep = f71882fg_पढ़ो8(data, F81866_REG_IN_BEEP);
	अन्यथा
		data->in_beep = f71882fg_पढ़ो8(data, F71882FG_REG_IN_BEEP);

	अगर (val)
		data->in_beep |= 1 << nr;
	अन्यथा
		data->in_beep &= ~(1 << nr);

	अगर (data->type == f81866a)
		f71882fg_ग_लिखो8(data, F81866_REG_IN_BEEP, data->in_beep);
	अन्यथा
		f71882fg_ग_लिखो8(data, F71882FG_REG_IN_BEEP, data->in_beep);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_in_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->in_status & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक sign, temp;

	अगर (data->type == f71858fg) अणु
		/* TEMP_TABLE_SEL 1 or 3 ? */
		अगर (data->temp_config & 1) अणु
			sign = data->temp[nr] & 0x0001;
			temp = (data->temp[nr] >> 5) & 0x7ff;
		पूर्ण अन्यथा अणु
			sign = data->temp[nr] & 0x8000;
			temp = (data->temp[nr] >> 5) & 0x3ff;
		पूर्ण
		temp *= 125;
		अगर (sign)
			temp -= 128000;
	पूर्ण अन्यथा
		temp = data->temp[nr] * 1000;

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार show_temp_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", data->temp_high[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार store_temp_max(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 1000;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	f71882fg_ग_लिखो8(data, F71882FG_REG_TEMP_HIGH(nr), val);
	data->temp_high[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp_max_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक temp_max_hyst;

	mutex_lock(&data->update_lock);
	अगर (nr & 1)
		temp_max_hyst = data->temp_hyst[nr / 2] >> 4;
	अन्यथा
		temp_max_hyst = data->temp_hyst[nr / 2] & 0x0f;
	temp_max_hyst = (data->temp_high[nr] - temp_max_hyst) * 1000;
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", temp_max_hyst);
पूर्ण

अटल sमाप_प्रकार store_temp_max_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	sमाप_प्रकार ret = count;
	u8 reg;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 1000;

	mutex_lock(&data->update_lock);

	/* convert असल to relative and check */
	data->temp_high[nr] = f71882fg_पढ़ो8(data, F71882FG_REG_TEMP_HIGH(nr));
	val = clamp_val(val, data->temp_high[nr] - 15, data->temp_high[nr]);
	val = data->temp_high[nr] - val;

	/* convert value to रेजिस्टर contents */
	reg = f71882fg_पढ़ो8(data, F71882FG_REG_TEMP_HYST(nr / 2));
	अगर (nr & 1)
		reg = (reg & 0x0f) | (val << 4);
	अन्यथा
		reg = (reg & 0xf0) | val;
	f71882fg_ग_लिखो8(data, F71882FG_REG_TEMP_HYST(nr / 2), reg);
	data->temp_hyst[nr / 2] = reg;

	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_temp_crit(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", data->temp_ovt[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार store_temp_crit(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 1000;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	f71882fg_ग_लिखो8(data, F71882FG_REG_TEMP_OVT(nr), val);
	data->temp_ovt[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp_crit_hyst(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक temp_crit_hyst;

	mutex_lock(&data->update_lock);
	अगर (nr & 1)
		temp_crit_hyst = data->temp_hyst[nr / 2] >> 4;
	अन्यथा
		temp_crit_hyst = data->temp_hyst[nr / 2] & 0x0f;
	temp_crit_hyst = (data->temp_ovt[nr] - temp_crit_hyst) * 1000;
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", temp_crit_hyst);
पूर्ण

अटल sमाप_प्रकार show_temp_type(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", data->temp_type[nr]);
पूर्ण

अटल sमाप_प्रकार show_temp_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->temp_beep & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार store_temp_beep(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_beep = f71882fg_पढ़ो8(data, F71882FG_REG_TEMP_BEEP);
	अगर (val)
		data->temp_beep |= 1 << nr;
	अन्यथा
		data->temp_beep &= ~(1 << nr);

	f71882fg_ग_लिखो8(data, F71882FG_REG_TEMP_BEEP, data->temp_beep);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp_alarm(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->temp_status & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_temp_fault(काष्ठा device *dev, काष्ठा device_attribute
	*devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	अगर (data->temp_diode_खोलो & (1 << nr))
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक val, nr = to_sensor_dev_attr_2(devattr)->index;
	mutex_lock(&data->update_lock);
	अगर (data->pwm_enable & (1 << (2 * nr)))
		/* PWM mode */
		val = data->pwm[nr];
	अन्यथा अणु
		/* RPM mode */
		val = 255 * fan_from_reg(data->fan_target[nr])
			/ fan_from_reg(data->fan_full_speed[nr]);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार store_pwm(काष्ठा device *dev,
			 काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			 माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm_enable = f71882fg_पढ़ो8(data, F71882FG_REG_PWM_ENABLE);
	अगर ((data->type == f8000 && ((data->pwm_enable >> 2 * nr) & 3) != 2) ||
	    (data->type != f8000 && !((data->pwm_enable >> 2 * nr) & 2))) अणु
		count = -EROFS;
		जाओ leave;
	पूर्ण
	अगर (data->pwm_enable & (1 << (2 * nr))) अणु
		/* PWM mode */
		f71882fg_ग_लिखो8(data, F71882FG_REG_PWM(nr), val);
		data->pwm[nr] = val;
	पूर्ण अन्यथा अणु
		/* RPM mode */
		पूर्णांक target, full_speed;
		full_speed = f71882fg_पढ़ो16(data,
					     F71882FG_REG_FAN_FULL_SPEED(nr));
		target = fan_to_reg(val * fan_from_reg(full_speed) / 255);
		f71882fg_ग_लिखो16(data, F71882FG_REG_FAN_TARGET(nr), target);
		data->fan_target[nr] = target;
		data->fan_full_speed[nr] = full_speed;
	पूर्ण
leave:
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_simple_pwm(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक val, nr = to_sensor_dev_attr_2(devattr)->index;

	val = data->pwm[nr];
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार store_simple_pwm(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	f71882fg_ग_लिखो8(data, F71882FG_REG_PWM(nr), val);
	data->pwm[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक result = 0;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	चयन ((data->pwm_enable >> 2 * nr) & 3) अणु
	हाल 0:
	हाल 1:
		result = 2; /* Normal स्वतः mode */
		अवरोध;
	हाल 2:
		result = 1; /* Manual mode */
		अवरोध;
	हाल 3:
		अगर (data->type == f8000)
			result = 3; /* Thermostat mode */
		अन्यथा
			result = 1; /* Manual mode */
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार store_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute
				*devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/* Special हाल क्रम F8000 pwm channel 3 which only करोes स्वतः mode */
	अगर (data->type == f8000 && nr == 2 && val != 2)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm_enable = f71882fg_पढ़ो8(data, F71882FG_REG_PWM_ENABLE);
	/* Special हाल क्रम F8000 स्वतः PWM mode / Thermostat mode */
	अगर (data->type == f8000 && ((data->pwm_enable >> 2 * nr) & 1)) अणु
		चयन (val) अणु
		हाल 2:
			data->pwm_enable &= ~(2 << (2 * nr));
			अवरोध;		/* Normal स्वतः mode */
		हाल 3:
			data->pwm_enable |= 2 << (2 * nr);
			अवरोध;		/* Thermostat mode */
		शेष:
			count = -EINVAL;
			जाओ leave;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (val) अणु
		हाल 1:
			/* The f71858fg करोes not support manual RPM mode */
			अगर (data->type == f71858fg &&
			    ((data->pwm_enable >> (2 * nr)) & 1)) अणु
				count = -EINVAL;
				जाओ leave;
			पूर्ण
			data->pwm_enable |= 2 << (2 * nr);
			अवरोध;		/* Manual */
		हाल 2:
			data->pwm_enable &= ~(2 << (2 * nr));
			अवरोध;		/* Normal स्वतः mode */
		शेष:
			count = -EINVAL;
			जाओ leave;
		पूर्ण
	पूर्ण
	f71882fg_ग_लिखो8(data, F71882FG_REG_PWM_ENABLE, data->pwm_enable);
leave:
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
				       काष्ठा device_attribute *devattr,
				       अक्षर *buf)
अणु
	पूर्णांक result;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक pwm = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;

	mutex_lock(&data->update_lock);
	अगर (data->pwm_enable & (1 << (2 * pwm))) अणु
		/* PWM mode */
		result = data->pwm_स्वतः_poपूर्णांक_pwm[pwm][poपूर्णांक];
	पूर्ण अन्यथा अणु
		/* RPM mode */
		result = 32 * 255 / (32 + data->pwm_स्वतः_poपूर्णांक_pwm[pwm][poपूर्णांक]);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, pwm = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm_enable = f71882fg_पढ़ो8(data, F71882FG_REG_PWM_ENABLE);
	अगर (data->pwm_enable & (1 << (2 * pwm))) अणु
		/* PWM mode */
	पूर्ण अन्यथा अणु
		/* RPM mode */
		अगर (val < 29)	/* Prevent negative numbers */
			val = 255;
		अन्यथा
			val = (255 - val) * 32 / val;
	पूर्ण
	f71882fg_ग_लिखो8(data, F71882FG_REG_POINT_PWM(pwm, poपूर्णांक), val);
	data->pwm_स्वतः_poपूर्णांक_pwm[pwm][poपूर्णांक] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp_hyst(काष्ठा device *dev,
					     काष्ठा device_attribute *devattr,
					     अक्षर *buf)
अणु
	पूर्णांक result = 0;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;

	mutex_lock(&data->update_lock);
	अगर (nr & 1)
		result = data->pwm_स्वतः_poपूर्णांक_hyst[nr / 2] >> 4;
	अन्यथा
		result = data->pwm_स्वतः_poपूर्णांक_hyst[nr / 2] & 0x0f;
	result = 1000 * (data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक] - result);
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_temp_hyst(काष्ठा device *dev,
					      काष्ठा device_attribute *devattr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;
	u8 reg;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 1000;

	mutex_lock(&data->update_lock);
	data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक] =
		f71882fg_पढ़ो8(data, F71882FG_REG_POINT_TEMP(nr, poपूर्णांक));
	val = clamp_val(val, data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक] - 15,
			data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक]);
	val = data->pwm_स्वतः_poपूर्णांक_temp[nr][poपूर्णांक] - val;

	reg = f71882fg_पढ़ो8(data, F71882FG_REG_FAN_HYST(nr / 2));
	अगर (nr & 1)
		reg = (reg & 0x0f) | (val << 4);
	अन्यथा
		reg = (reg & 0xf0) | val;

	f71882fg_ग_लिखो8(data, F71882FG_REG_FAN_HYST(nr / 2), reg);
	data->pwm_स्वतः_poपूर्णांक_hyst[nr / 2] = reg;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_पूर्णांकerpolate(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक result;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	result = (data->pwm_स्वतः_poपूर्णांक_mapping[nr] >> 4) & 1;

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार store_pwm_पूर्णांकerpolate(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm_स्वतः_poपूर्णांक_mapping[nr] =
		f71882fg_पढ़ो8(data, F71882FG_REG_POINT_MAPPING(nr));
	अगर (val)
		val = data->pwm_स्वतः_poपूर्णांक_mapping[nr] | (1 << 4);
	अन्यथा
		val = data->pwm_स्वतः_poपूर्णांक_mapping[nr] & (~(1 << 4));
	f71882fg_ग_लिखो8(data, F71882FG_REG_POINT_MAPPING(nr), val);
	data->pwm_स्वतः_poपूर्णांक_mapping[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_channel(काष्ठा device *dev,
					   काष्ठा device_attribute *devattr,
					   अक्षर *buf)
अणु
	पूर्णांक result;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->index;

	result = 1 << ((data->pwm_स्वतः_poपूर्णांक_mapping[nr] & 3) -
		       data->temp_start);

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_channel(काष्ठा device *dev,
					    काष्ठा device_attribute *devattr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, nr = to_sensor_dev_attr_2(devattr)->index;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	चयन (val) अणु
	हाल 1:
		val = 0;
		अवरोध;
	हाल 2:
		val = 1;
		अवरोध;
	हाल 4:
		val = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	val += data->temp_start;
	mutex_lock(&data->update_lock);
	data->pwm_स्वतः_poपूर्णांक_mapping[nr] =
		f71882fg_पढ़ो8(data, F71882FG_REG_POINT_MAPPING(nr));
	val = (data->pwm_स्वतः_poपूर्णांक_mapping[nr] & 0xfc) | val;
	f71882fg_ग_लिखो8(data, F71882FG_REG_POINT_MAPPING(nr), val);
	data->pwm_स्वतः_poपूर्णांक_mapping[nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	पूर्णांक result;
	काष्ठा f71882fg_data *data = f71882fg_update_device(dev);
	पूर्णांक pwm = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;

	result = data->pwm_स्वतः_poपूर्णांक_temp[pwm][poपूर्णांक];
	वापस प्र_लिखो(buf, "%d\n", 1000 * result);
पूर्ण

अटल sमाप_प्रकार store_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	पूर्णांक err, pwm = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक poपूर्णांक = to_sensor_dev_attr_2(devattr)->nr;
	दीर्घ val;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 1000;

	अगर (data->स्वतः_poपूर्णांक_temp_चिन्हित)
		val = clamp_val(val, -128, 127);
	अन्यथा
		val = clamp_val(val, 0, 127);

	mutex_lock(&data->update_lock);
	f71882fg_ग_लिखो8(data, F71882FG_REG_POINT_TEMP(pwm, poपूर्णांक), val);
	data->pwm_स्वतः_poपूर्णांक_temp[pwm][poपूर्णांक] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf)
अणु
	काष्ठा f71882fg_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", f71882fg_names[data->type]);
पूर्ण

अटल पूर्णांक f71882fg_create_sysfs_files(काष्ठा platक्रमm_device *pdev,
	काष्ठा sensor_device_attribute_2 *attr, पूर्णांक count)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < count; i++) अणु
		err = device_create_file(&pdev->dev, &attr[i].dev_attr);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम f71882fg_हटाओ_sysfs_files(काष्ठा platक्रमm_device *pdev,
	काष्ठा sensor_device_attribute_2 *attr, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		device_हटाओ_file(&pdev->dev, &attr[i].dev_attr);
पूर्ण

अटल पूर्णांक f71882fg_create_fan_sysfs_files(
	काष्ठा platक्रमm_device *pdev, पूर्णांक idx)
अणु
	काष्ठा f71882fg_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	/* Sanity check the pwm setting */
	err = 0;
	चयन (data->type) अणु
	हाल f71858fg:
		अगर (((data->pwm_enable >> (idx * 2)) & 3) == 3)
			err = 1;
		अवरोध;
	हाल f71862fg:
		अगर (((data->pwm_enable >> (idx * 2)) & 1) != 1)
			err = 1;
		अवरोध;
	हाल f8000:
		अगर (idx == 2)
			err = data->pwm_enable & 0x20;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Invalid (reserved) pwm settings: 0x%02x, "
			"skipping fan %d\n",
			(data->pwm_enable >> (idx * 2)) & 3, idx + 1);
		वापस 0; /* This is a non fatal condition */
	पूर्ण

	err = f71882fg_create_sysfs_files(pdev, &fxxxx_fan_attr[idx][0],
					  ARRAY_SIZE(fxxxx_fan_attr[0]));
	अगर (err)
		वापस err;

	अगर (f71882fg_fan_has_beep[data->type]) अणु
		err = f71882fg_create_sysfs_files(pdev,
						  &fxxxx_fan_beep_attr[idx],
						  1);
		अगर (err)
			वापस err;
	पूर्ण

	dev_info(&pdev->dev, "Fan: %d is in %s mode\n", idx + 1,
		 (data->pwm_enable & (1 << (2 * idx))) ? "duty-cycle" : "RPM");

	/* Check क्रम unsupported स्वतः pwm settings */
	चयन (data->type) अणु
	हाल f71808e:
	हाल f71808a:
	हाल f71869:
	हाल f71869a:
	हाल f71889fg:
	हाल f71889ed:
	हाल f71889a:
		data->pwm_स्वतः_poपूर्णांक_mapping[idx] =
			f71882fg_पढ़ो8(data, F71882FG_REG_POINT_MAPPING(idx));
		अगर ((data->pwm_स्वतः_poपूर्णांक_mapping[idx] & 0x80) ||
		    (data->pwm_स्वतः_poपूर्णांक_mapping[idx] & 3) == 0) अणु
			dev_warn(&pdev->dev,
				 "Auto pwm controlled by raw digital "
				 "data, disabling pwm auto_point "
				 "sysfs attributes for fan %d\n", idx + 1);
			वापस 0; /* This is a non fatal condition */
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (data->type) अणु
	हाल f71862fg:
		err = f71882fg_create_sysfs_files(pdev,
					&f71862fg_स्वतः_pwm_attr[idx][0],
					ARRAY_SIZE(f71862fg_स्वतः_pwm_attr[0]));
		अवरोध;
	हाल f71808e:
	हाल f71869:
		err = f71882fg_create_sysfs_files(pdev,
					&f71869_स्वतः_pwm_attr[idx][0],
					ARRAY_SIZE(f71869_स्वतः_pwm_attr[0]));
		अवरोध;
	हाल f8000:
		err = f71882fg_create_sysfs_files(pdev,
					&f8000_स्वतः_pwm_attr[idx][0],
					ARRAY_SIZE(f8000_स्वतः_pwm_attr[0]));
		अवरोध;
	शेष:
		err = f71882fg_create_sysfs_files(pdev,
					&fxxxx_स्वतः_pwm_attr[idx][0],
					ARRAY_SIZE(fxxxx_स्वतः_pwm_attr[0]));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक f71882fg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा f71882fg_data *data;
	काष्ठा f71882fg_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	पूर्णांक nr_fans = f71882fg_nr_fans[sio_data->type];
	पूर्णांक nr_temps = f71882fg_nr_temps[sio_data->type];
	पूर्णांक err, i;
	पूर्णांक size;
	u8 start_reg, reg;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा f71882fg_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0)->start;
	data->type = sio_data->type;
	data->temp_start =
	    (data->type == f71858fg || data->type == f8000 ||
		data->type == f81866a) ? 0 : 1;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	start_reg = f71882fg_पढ़ो8(data, F71882FG_REG_START);
	अगर (start_reg & 0x04) अणु
		dev_warn(&pdev->dev, "Hardware monitor is powered down\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!(start_reg & 0x03)) अणु
		dev_warn(&pdev->dev, "Hardware monitoring not activated\n");
		वापस -ENODEV;
	पूर्ण

	/* Register sysfs पूर्णांकerface files */
	err = device_create_file(&pdev->dev, &dev_attr_name);
	अगर (err)
		जाओ निकास_unरेजिस्टर_sysfs;

	अगर (start_reg & 0x01) अणु
		चयन (data->type) अणु
		हाल f71858fg:
			data->temp_config =
				f71882fg_पढ़ो8(data, F71882FG_REG_TEMP_CONFIG);
			अगर (data->temp_config & 0x10)
				/*
				 * The f71858fg temperature alarms behave as
				 * the f8000 alarms in this mode
				 */
				err = f71882fg_create_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			अन्यथा
				err = f71882fg_create_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			अवरोध;
		हाल f8000:
			err = f71882fg_create_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			अवरोध;
		हाल f81866a:
			err = f71882fg_create_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			अवरोध;
		शेष:
			err = f71882fg_create_sysfs_files(pdev,
				&fxxxx_temp_attr[0][0],
				ARRAY_SIZE(fxxxx_temp_attr[0]) * nr_temps);
		पूर्ण
		अगर (err)
			जाओ निकास_unरेजिस्टर_sysfs;

		अगर (f71882fg_temp_has_beep[data->type]) अणु
			अगर (data->type == f81866a) अणु
				size = ARRAY_SIZE(f81866_temp_beep_attr[0]);
				err = f71882fg_create_sysfs_files(pdev,
						&f81866_temp_beep_attr[0][0],
						size * nr_temps);

			पूर्ण अन्यथा अणु
				size = ARRAY_SIZE(fxxxx_temp_beep_attr[0]);
				err = f71882fg_create_sysfs_files(pdev,
						&fxxxx_temp_beep_attr[0][0],
						size * nr_temps);
			पूर्ण
			अगर (err)
				जाओ निकास_unरेजिस्टर_sysfs;
		पूर्ण

		क्रम (i = 0; i < F71882FG_MAX_INS; i++) अणु
			अगर (f71882fg_has_in[data->type][i]) अणु
				err = device_create_file(&pdev->dev,
						&fxxxx_in_attr[i].dev_attr);
				अगर (err)
					जाओ निकास_unरेजिस्टर_sysfs;
			पूर्ण
		पूर्ण
		अगर (f71882fg_has_in1_alarm[data->type]) अणु
			err = f71882fg_create_sysfs_files(pdev,
					fxxxx_in1_alarm_attr,
					ARRAY_SIZE(fxxxx_in1_alarm_attr));
			अगर (err)
				जाओ निकास_unरेजिस्टर_sysfs;
		पूर्ण
	पूर्ण

	अगर (start_reg & 0x02) अणु
		चयन (data->type) अणु
		हाल f71808e:
		हाल f71808a:
		हाल f71869:
		हाल f71869a:
			/* These always have चिन्हित स्वतः poपूर्णांक temps */
			data->स्वतः_poपूर्णांक_temp_चिन्हित = 1;
			fallthrough;	/* to select correct fan/pwm reg bank! */
		हाल f71889fg:
		हाल f71889ed:
		हाल f71889a:
			reg = f71882fg_पढ़ो8(data, F71882FG_REG_FAN_FAULT_T);
			अगर (reg & F71882FG_FAN_NEG_TEMP_EN)
				data->स्वतः_poपूर्णांक_temp_चिन्हित = 1;
			/* Ensure banked pwm रेजिस्टरs poपूर्णांक to right bank */
			reg &= ~F71882FG_FAN_PROG_SEL;
			f71882fg_ग_लिखो8(data, F71882FG_REG_FAN_FAULT_T, reg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		data->pwm_enable =
			f71882fg_पढ़ो8(data, F71882FG_REG_PWM_ENABLE);

		क्रम (i = 0; i < nr_fans; i++) अणु
			err = f71882fg_create_fan_sysfs_files(pdev, i);
			अगर (err)
				जाओ निकास_unरेजिस्टर_sysfs;
		पूर्ण

		/* Some types have 1 extra fan with limited functionality */
		चयन (data->type) अणु
		हाल f71808a:
			err = f71882fg_create_sysfs_files(pdev,
					f71808a_fan3_attr,
					ARRAY_SIZE(f71808a_fan3_attr));
			अवरोध;
		हाल f8000:
			err = f71882fg_create_sysfs_files(pdev,
					f8000_fan_attr,
					ARRAY_SIZE(f8000_fan_attr));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (err)
			जाओ निकास_unरेजिस्टर_sysfs;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = शून्य;
		जाओ निकास_unरेजिस्टर_sysfs;
	पूर्ण

	वापस 0;

निकास_unरेजिस्टर_sysfs:
	f71882fg_हटाओ(pdev); /* Will unरेजिस्टर the sysfs files क्रम us */
	वापस err; /* f71882fg_हटाओ() also मुक्तs our data */
पूर्ण

अटल पूर्णांक f71882fg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा f71882fg_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक nr_fans = f71882fg_nr_fans[data->type];
	पूर्णांक nr_temps = f71882fg_nr_temps[data->type];
	पूर्णांक i;
	u8 start_reg = f71882fg_पढ़ो8(data, F71882FG_REG_START);

	अगर (data->hwmon_dev)
		hwmon_device_unरेजिस्टर(data->hwmon_dev);

	device_हटाओ_file(&pdev->dev, &dev_attr_name);

	अगर (start_reg & 0x01) अणु
		चयन (data->type) अणु
		हाल f71858fg:
			अगर (data->temp_config & 0x10)
				f71882fg_हटाओ_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			अन्यथा
				f71882fg_हटाओ_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			अवरोध;
		हाल f8000:
			f71882fg_हटाओ_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			अवरोध;
		हाल f81866a:
			f71882fg_हटाओ_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			अवरोध;
		शेष:
			f71882fg_हटाओ_sysfs_files(pdev,
				&fxxxx_temp_attr[0][0],
				ARRAY_SIZE(fxxxx_temp_attr[0]) * nr_temps);
		पूर्ण
		अगर (f71882fg_temp_has_beep[data->type]) अणु
			अगर (data->type == f81866a)
				f71882fg_हटाओ_sysfs_files(pdev,
					&f81866_temp_beep_attr[0][0],
					ARRAY_SIZE(f81866_temp_beep_attr[0])
						* nr_temps);
			अन्यथा
				f71882fg_हटाओ_sysfs_files(pdev,
					&fxxxx_temp_beep_attr[0][0],
					ARRAY_SIZE(fxxxx_temp_beep_attr[0])
						* nr_temps);
		पूर्ण

		क्रम (i = 0; i < F71882FG_MAX_INS; i++) अणु
			अगर (f71882fg_has_in[data->type][i]) अणु
				device_हटाओ_file(&pdev->dev,
						&fxxxx_in_attr[i].dev_attr);
			पूर्ण
		पूर्ण
		अगर (f71882fg_has_in1_alarm[data->type]) अणु
			f71882fg_हटाओ_sysfs_files(pdev,
					fxxxx_in1_alarm_attr,
					ARRAY_SIZE(fxxxx_in1_alarm_attr));
		पूर्ण
	पूर्ण

	अगर (start_reg & 0x02) अणु
		f71882fg_हटाओ_sysfs_files(pdev, &fxxxx_fan_attr[0][0],
				ARRAY_SIZE(fxxxx_fan_attr[0]) * nr_fans);

		अगर (f71882fg_fan_has_beep[data->type]) अणु
			f71882fg_हटाओ_sysfs_files(pdev,
					fxxxx_fan_beep_attr, nr_fans);
		पूर्ण

		चयन (data->type) अणु
		हाल f71808a:
			f71882fg_हटाओ_sysfs_files(pdev,
				&fxxxx_स्वतः_pwm_attr[0][0],
				ARRAY_SIZE(fxxxx_स्वतः_pwm_attr[0]) * nr_fans);
			f71882fg_हटाओ_sysfs_files(pdev,
					f71808a_fan3_attr,
					ARRAY_SIZE(f71808a_fan3_attr));
			अवरोध;
		हाल f71862fg:
			f71882fg_हटाओ_sysfs_files(pdev,
				&f71862fg_स्वतः_pwm_attr[0][0],
				ARRAY_SIZE(f71862fg_स्वतः_pwm_attr[0]) *
					nr_fans);
			अवरोध;
		हाल f71808e:
		हाल f71869:
			f71882fg_हटाओ_sysfs_files(pdev,
				&f71869_स्वतः_pwm_attr[0][0],
				ARRAY_SIZE(f71869_स्वतः_pwm_attr[0]) * nr_fans);
			अवरोध;
		हाल f8000:
			f71882fg_हटाओ_sysfs_files(pdev,
					f8000_fan_attr,
					ARRAY_SIZE(f8000_fan_attr));
			f71882fg_हटाओ_sysfs_files(pdev,
				&f8000_स्वतः_pwm_attr[0][0],
				ARRAY_SIZE(f8000_स्वतः_pwm_attr[0]) * nr_fans);
			अवरोध;
		शेष:
			f71882fg_हटाओ_sysfs_files(pdev,
				&fxxxx_स्वतः_pwm_attr[0][0],
				ARRAY_SIZE(fxxxx_स्वतः_pwm_attr[0]) * nr_fans);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init f71882fg_find(पूर्णांक sioaddr, काष्ठा f71882fg_sio_data *sio_data)
अणु
	u16 devid;
	अचिन्हित लघु address;
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
	हाल SIO_F71808E_ID:
		sio_data->type = f71808e;
		अवरोध;
	हाल SIO_F71808A_ID:
		sio_data->type = f71808a;
		अवरोध;
	हाल SIO_F71858_ID:
		sio_data->type = f71858fg;
		अवरोध;
	हाल SIO_F71862_ID:
		sio_data->type = f71862fg;
		अवरोध;
	हाल SIO_F71868_ID:
		sio_data->type = f71868a;
		अवरोध;
	हाल SIO_F71869_ID:
		sio_data->type = f71869;
		अवरोध;
	हाल SIO_F71869A_ID:
		sio_data->type = f71869a;
		अवरोध;
	हाल SIO_F71882_ID:
		sio_data->type = f71882fg;
		अवरोध;
	हाल SIO_F71889_ID:
		sio_data->type = f71889fg;
		अवरोध;
	हाल SIO_F71889E_ID:
		sio_data->type = f71889ed;
		अवरोध;
	हाल SIO_F71889A_ID:
		sio_data->type = f71889a;
		अवरोध;
	हाल SIO_F8000_ID:
		sio_data->type = f8000;
		अवरोध;
	हाल SIO_F81768D_ID:
		sio_data->type = f81768d;
		अवरोध;
	हाल SIO_F81865_ID:
		sio_data->type = f81865f;
		अवरोध;
	हाल SIO_F81866_ID:
		sio_data->type = f81866a;
		अवरोध;
	शेष:
		pr_info("Unsupported Fintek device: %04x\n",
			(अचिन्हित पूर्णांक)devid);
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (sio_data->type == f71858fg)
		superio_select(sioaddr, SIO_F71858FG_LD_HWM);
	अन्यथा
		superio_select(sioaddr, SIO_F71882FG_LD_HWM);

	अगर (!(superio_inb(sioaddr, SIO_REG_ENABLE) & 0x01)) अणु
		pr_warn("Device not activated\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	address = superio_inw(sioaddr, SIO_REG_ADDR);
	अगर (address == 0) अणु
		pr_warn("Base address not set\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	address &= ~(REGION_LENGTH - 1);	/* Ignore 3 LSB */

	err = address;
	pr_info("Found %s chip at %#x, revision %d\n",
		f71882fg_names[sio_data->type],	(अचिन्हित पूर्णांक)address,
		(पूर्णांक)superio_inb(sioaddr, SIO_REG_DEVREV));
निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

अटल पूर्णांक __init f71882fg_device_add(पूर्णांक address,
				      स्थिर काष्ठा f71882fg_sio_data *sio_data)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + REGION_LENGTH - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	f71882fg_pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!f71882fg_pdev)
		वापस -ENOMEM;

	res.name = f71882fg_pdev->name;
	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास_device_put;

	err = platक्रमm_device_add_resources(f71882fg_pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed\n");
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add_data(f71882fg_pdev, sio_data,
				       माप(काष्ठा f71882fg_sio_data));
	अगर (err) अणु
		pr_err("Platform data allocation failed\n");
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(f71882fg_pdev);
	अगर (err) अणु
		pr_err("Device addition failed\n");
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(f71882fg_pdev);

	वापस err;
पूर्ण

अटल पूर्णांक __init f71882fg_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक address;
	काष्ठा f71882fg_sio_data sio_data;

	स_रखो(&sio_data, 0, माप(sio_data));

	address = f71882fg_find(0x2e, &sio_data);
	अगर (address < 0)
		address = f71882fg_find(0x4e, &sio_data);
	अगर (address < 0)
		वापस address;

	err = platक्रमm_driver_रेजिस्टर(&f71882fg_driver);
	अगर (err)
		वापस err;

	err = f71882fg_device_add(address, &sio_data);
	अगर (err)
		जाओ निकास_driver;

	वापस 0;

निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&f71882fg_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास f71882fg_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(f71882fg_pdev);
	platक्रमm_driver_unरेजिस्टर(&f71882fg_driver);
पूर्ण

MODULE_DESCRIPTION("F71882FG Hardware Monitoring Driver");
MODULE_AUTHOR("Hans Edgington, Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");

module_init(f71882fg_init);
module_निकास(f71882fg_निकास);
