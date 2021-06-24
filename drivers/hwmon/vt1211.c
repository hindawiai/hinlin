<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vt1211.c - driver क्रम the VIA VT1211 Super-I/O chip पूर्णांकegrated hardware
 *            monitoring features
 * Copyright (C) 2006 Juerg Haefliger <juergh@gmail.com>
 *
 * This driver is based on the driver क्रम kernel 2.4 by Mark D. Studebaker
 * and its port to kernel 2.6 by Lars Ekman.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल पूर्णांक uch_config = -1;
module_param(uch_config, पूर्णांक, 0);
MODULE_PARM_DESC(uch_config, "Initialize the universal channel configuration");

अटल पूर्णांक पूर्णांक_mode = -1;
module_param(पूर्णांक_mode, पूर्णांक, 0);
MODULE_PARM_DESC(पूर्णांक_mode, "Force the temperature interrupt mode");

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा DRVNAME "vt1211"

/* ---------------------------------------------------------------------
 * Registers
 *
 * The sensors are defined as follows.
 *
 * Sensor          Voltage Mode   Temp Mode   Notes (from the datasheet)
 * --------        ------------   ---------   --------------------------
 * Reading 1                      temp1       Intel thermal diode
 * Reading 3                      temp2       Internal thermal diode
 * UCH1/Reading2   in0            temp3       NTC type thermistor
 * UCH2            in1            temp4       +2.5V
 * UCH3            in2            temp5       VccP
 * UCH4            in3            temp6       +5V
 * UCH5            in4            temp7       +12V
 * 3.3V            in5                        Internal VDD (+3.3V)
 *
 * --------------------------------------------------------------------- */

/* Voltages (in) numbered 0-5 (ix) */
#घोषणा VT1211_REG_IN(ix)		(0x21 + (ix))
#घोषणा VT1211_REG_IN_MIN(ix)		((ix) == 0 ? 0x3e : 0x2a + 2 * (ix))
#घोषणा VT1211_REG_IN_MAX(ix)		((ix) == 0 ? 0x3d : 0x29 + 2 * (ix))

/* Temperatures (temp) numbered 0-6 (ix) */
अटल u8 regtemp[]	= अणु0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25पूर्ण;
अटल u8 regtempmax[]	= अणु0x39, 0x1d, 0x3d, 0x2b, 0x2d, 0x2f, 0x31पूर्ण;
अटल u8 regtemphyst[]	= अणु0x3a, 0x1e, 0x3e, 0x2c, 0x2e, 0x30, 0x32पूर्ण;

/* Fans numbered 0-1 (ix) */
#घोषणा VT1211_REG_FAN(ix)		(0x29 + (ix))
#घोषणा VT1211_REG_FAN_MIN(ix)		(0x3b + (ix))
#घोषणा VT1211_REG_FAN_DIV		 0x47

/* PWMs numbered 0-1 (ix) */
/* Auto poपूर्णांकs numbered 0-3 (ap) */
#घोषणा VT1211_REG_PWM(ix)		(0x60 + (ix))
#घोषणा VT1211_REG_PWM_CLK		 0x50
#घोषणा VT1211_REG_PWM_CTL		 0x51
#घोषणा VT1211_REG_PWM_AUTO_TEMP(ap)	(0x55 - (ap))
#घोषणा VT1211_REG_PWM_AUTO_PWM(ix, ap)	(0x58 + 2 * (ix) - (ap))

/* Miscellaneous रेजिस्टरs */
#घोषणा VT1211_REG_CONFIG		0x40
#घोषणा VT1211_REG_ALARM1		0x41
#घोषणा VT1211_REG_ALARM2		0x42
#घोषणा VT1211_REG_VID			0x45
#घोषणा VT1211_REG_UCH_CONFIG		0x4a
#घोषणा VT1211_REG_TEMP1_CONFIG		0x4b
#घोषणा VT1211_REG_TEMP2_CONFIG		0x4c

/* In, temp & fan alarm bits */
अटल स्थिर u8 bitalarmin[]	= अणु11, 0, 1, 3, 8, 2, 9पूर्ण;
अटल स्थिर u8 bitalarmtemp[]	= अणु4, 15, 11, 0, 1, 3, 8पूर्ण;
अटल स्थिर u8 bitalarmfan[]	= अणु6, 7पूर्ण;

/* ---------------------------------------------------------------------
 * Data काष्ठाures and manipulation thereof
 * --------------------------------------------------------------------- */

काष्ठा vt1211_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;

	काष्ठा mutex update_lock;
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* Register values */
	u8  in[6];
	u8  in_max[6];
	u8  in_min[6];
	u8  temp[7];
	u8  temp_max[7];
	u8  temp_hyst[7];
	u8  fan[2];
	u8  fan_min[2];
	u8  fan_भाग[2];
	u8  fan_ctl;
	u8  pwm[2];
	u8  pwm_ctl[2];
	u8  pwm_clk;
	u8  pwm_स्वतः_temp[4];
	u8  pwm_स्वतः_pwm[2][4];
	u8  vid;		/* Read once at init समय */
	u8  vrm;
	u8  uch_config;		/* Read once at init समय */
	u16 alarms;
पूर्ण;

/* ix = [0-5] */
#घोषणा ISVOLT(ix, uch_config)	((ix) > 4 ? 1 : \
				 !(((uch_config) >> ((ix) + 2)) & 1))

/* ix = [0-6] */
#घोषणा ISTEMP(ix, uch_config)	((ix) < 2 ? 1 : \
				 ((uch_config) >> (ix)) & 1)

/*
 * in5 (ix = 5) is special. It's the internal 3.3V so it's scaled in the
 * driver according to the VT1211 BIOS porting guide
 */
#घोषणा IN_FROM_REG(ix, reg)	((reg) < 3 ? 0 : (ix) == 5 ? \
				 (((reg) - 3) * 15882 + 479) / 958 : \
				 (((reg) - 3) * 10000 + 479) / 958)
#घोषणा IN_TO_REG(ix, val)	(clamp_val((ix) == 5 ? \
				 ((val) * 958 + 7941) / 15882 + 3 : \
				 ((val) * 958 + 5000) / 10000 + 3, 0, 255))

/*
 * temp1 (ix = 0) is an पूर्णांकel thermal diode which is scaled in user space.
 * temp2 (ix = 1) is the पूर्णांकernal temp diode so it's scaled in the driver
 * according to some measurements that I took on an EPIA M10000.
 * temp3-7 are thermistor based so the driver वापसs the voltage measured at
 * the pin (range 0V - 2.2V).
 */
#घोषणा TEMP_FROM_REG(ix, reg)	((ix) == 0 ? (reg) * 1000 : \
				 (ix) == 1 ? (reg) < 51 ? 0 : \
				 ((reg) - 51) * 1000 : \
				 ((253 - (reg)) * 2200 + 105) / 210)
#घोषणा TEMP_TO_REG(ix, val)	clamp_val( \
				 ((ix) == 0 ? ((val) + 500) / 1000 : \
				  (ix) == 1 ? ((val) + 500) / 1000 + 51 : \
				  253 - ((val) * 210 + 1100) / 2200), 0, 255)

#घोषणा DIV_FROM_REG(reg)	(1 << (reg))

#घोषणा RPM_FROM_REG(reg, भाग)	(((reg) == 0) || ((reg) == 255) ? 0 : \
				 1310720 / (reg) / DIV_FROM_REG(भाग))
#घोषणा RPM_TO_REG(val, भाग)	((val) == 0 ? 255 : \
				 clamp_val((1310720 / (val) / \
				 DIV_FROM_REG(भाग)), 1, 254))

/* ---------------------------------------------------------------------
 * Super-I/O स्थिरants and functions
 * --------------------------------------------------------------------- */

/*
 * Configuration index port रेजिस्टरs
 * The vt1211 can live at 2 dअगरferent addresses so we need to probe both
 */
#घोषणा SIO_REG_CIP1		0x2e
#घोषणा SIO_REG_CIP2		0x4e

/* Configuration रेजिस्टरs */
#घोषणा SIO_VT1211_LDN		0x07	/* logical device number */
#घोषणा SIO_VT1211_DEVID	0x20	/* device ID */
#घोषणा SIO_VT1211_DEVREV	0x21	/* device revision */
#घोषणा SIO_VT1211_ACTIVE	0x30	/* HW monitor active */
#घोषणा SIO_VT1211_BADDR	0x60	/* base I/O address */
#घोषणा SIO_VT1211_ID		0x3c	/* VT1211 device ID */

/* VT1211 logical device numbers */
#घोषणा SIO_VT1211_LDN_HWMON	0x0b	/* HW monitor */

अटल अंतरभूत व्योम superio_outb(पूर्णांक sio_cip, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sio_cip);
	outb(val, sio_cip + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक sio_cip, पूर्णांक reg)
अणु
	outb(reg, sio_cip);
	वापस inb(sio_cip + 1);
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक sio_cip, पूर्णांक ldn)
अणु
	outb(SIO_VT1211_LDN, sio_cip);
	outb(ldn, sio_cip + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक sio_cip)
अणु
	अगर (!request_muxed_region(sio_cip, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x87, sio_cip);
	outb(0x87, sio_cip);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक sio_cip)
अणु
	outb(0xaa, sio_cip);
	release_region(sio_cip, 2);
पूर्ण

/* ---------------------------------------------------------------------
 * Device I/O access
 * --------------------------------------------------------------------- */

अटल अंतरभूत u8 vt1211_पढ़ो8(काष्ठा vt1211_data *data, u8 reg)
अणु
	वापस inb(data->addr + reg);
पूर्ण

अटल अंतरभूत व्योम vt1211_ग_लिखो8(काष्ठा vt1211_data *data, u8 reg, u8 val)
अणु
	outb(val, data->addr + reg);
पूर्ण

अटल काष्ठा vt1211_data *vt1211_update_device(काष्ठा device *dev)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	पूर्णांक ix, val;

	mutex_lock(&data->update_lock);

	/* रेजिस्टरs cache is refreshed after 1 second */
	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		/* पढ़ो VID */
		data->vid = vt1211_पढ़ो8(data, VT1211_REG_VID) & 0x1f;

		/* voltage (in) रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->in); ix++) अणु
			अगर (ISVOLT(ix, data->uch_config)) अणु
				data->in[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_IN(ix));
				data->in_min[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_IN_MIN(ix));
				data->in_max[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_IN_MAX(ix));
			पूर्ण
		पूर्ण

		/* temp रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) अणु
			अगर (ISTEMP(ix, data->uch_config)) अणु
				data->temp[ix] = vt1211_पढ़ो8(data,
						regtemp[ix]);
				data->temp_max[ix] = vt1211_पढ़ो8(data,
						regtempmax[ix]);
				data->temp_hyst[ix] = vt1211_पढ़ो8(data,
						regtemphyst[ix]);
			पूर्ण
		पूर्ण

		/* fan & pwm रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->fan); ix++) अणु
			data->fan[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_FAN(ix));
			data->fan_min[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_FAN_MIN(ix));
			data->pwm[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM(ix));
		पूर्ण
		val = vt1211_पढ़ो8(data, VT1211_REG_FAN_DIV);
		data->fan_भाग[0] = (val >> 4) & 3;
		data->fan_भाग[1] = (val >> 6) & 3;
		data->fan_ctl = val & 0xf;

		val = vt1211_पढ़ो8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = val & 0xf;
		data->pwm_ctl[1] = (val >> 4) & 0xf;

		data->pwm_clk = vt1211_पढ़ो8(data, VT1211_REG_PWM_CLK);

		/* pwm & temp स्वतः poपूर्णांक रेजिस्टरs */
		data->pwm_स्वतः_pwm[0][1] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM_AUTO_PWM(0, 1));
		data->pwm_स्वतः_pwm[0][2] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM_AUTO_PWM(0, 2));
		data->pwm_स्वतः_pwm[1][1] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM_AUTO_PWM(1, 1));
		data->pwm_स्वतः_pwm[1][2] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM_AUTO_PWM(1, 2));
		क्रम (ix = 0; ix < ARRAY_SIZE(data->pwm_स्वतः_temp); ix++) अणु
			data->pwm_स्वतः_temp[ix] = vt1211_पढ़ो8(data,
						VT1211_REG_PWM_AUTO_TEMP(ix));
		पूर्ण

		/* alarm रेजिस्टरs */
		data->alarms = (vt1211_पढ़ो8(data, VT1211_REG_ALARM2) << 8) |
				vt1211_पढ़ो8(data, VT1211_REG_ALARM1);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* ---------------------------------------------------------------------
 * Voltage sysfs पूर्णांकerfaces
 * ix = [0-5]
 * --------------------------------------------------------------------- */

#घोषणा SHOW_IN_INPUT	0
#घोषणा SHOW_SET_IN_MIN	1
#घोषणा SHOW_SET_IN_MAX	2
#घोषणा SHOW_IN_ALARM	3

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SHOW_IN_INPUT:
		res = IN_FROM_REG(ix, data->in[ix]);
		अवरोध;
	हाल SHOW_SET_IN_MIN:
		res = IN_FROM_REG(ix, data->in_min[ix]);
		अवरोध;
	हाल SHOW_SET_IN_MAX:
		res = IN_FROM_REG(ix, data->in_max[ix]);
		अवरोध;
	हाल SHOW_IN_ALARM:
		res = (data->alarms >> bitalarmin[ix]) & 1;
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SHOW_SET_IN_MIN:
		data->in_min[ix] = IN_TO_REG(ix, val);
		vt1211_ग_लिखो8(data, VT1211_REG_IN_MIN(ix), data->in_min[ix]);
		अवरोध;
	हाल SHOW_SET_IN_MAX:
		data->in_max[ix] = IN_TO_REG(ix, val);
		vt1211_ग_लिखो8(data, VT1211_REG_IN_MAX(ix), data->in_max[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Temperature sysfs पूर्णांकerfaces
 * ix = [0-6]
 * --------------------------------------------------------------------- */

#घोषणा SHOW_TEMP_INPUT		0
#घोषणा SHOW_SET_TEMP_MAX	1
#घोषणा SHOW_SET_TEMP_MAX_HYST	2
#घोषणा SHOW_TEMP_ALARM		3

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SHOW_TEMP_INPUT:
		res = TEMP_FROM_REG(ix, data->temp[ix]);
		अवरोध;
	हाल SHOW_SET_TEMP_MAX:
		res = TEMP_FROM_REG(ix, data->temp_max[ix]);
		अवरोध;
	हाल SHOW_SET_TEMP_MAX_HYST:
		res = TEMP_FROM_REG(ix, data->temp_hyst[ix]);
		अवरोध;
	हाल SHOW_TEMP_ALARM:
		res = (data->alarms >> bitalarmtemp[ix]) & 1;
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SHOW_SET_TEMP_MAX:
		data->temp_max[ix] = TEMP_TO_REG(ix, val);
		vt1211_ग_लिखो8(data, regtempmax[ix],
			      data->temp_max[ix]);
		अवरोध;
	हाल SHOW_SET_TEMP_MAX_HYST:
		data->temp_hyst[ix] = TEMP_TO_REG(ix, val);
		vt1211_ग_लिखो8(data, regtemphyst[ix],
			      data->temp_hyst[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Fan sysfs पूर्णांकerfaces
 * ix = [0-1]
 * --------------------------------------------------------------------- */

#घोषणा SHOW_FAN_INPUT		0
#घोषणा SHOW_SET_FAN_MIN	1
#घोषणा SHOW_SET_FAN_DIV	2
#घोषणा SHOW_FAN_ALARM		3

अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SHOW_FAN_INPUT:
		res = RPM_FROM_REG(data->fan[ix], data->fan_भाग[ix]);
		अवरोध;
	हाल SHOW_SET_FAN_MIN:
		res = RPM_FROM_REG(data->fan_min[ix], data->fan_भाग[ix]);
		अवरोध;
	हाल SHOW_SET_FAN_DIV:
		res = DIV_FROM_REG(data->fan_भाग[ix]);
		अवरोध;
	हाल SHOW_FAN_ALARM:
		res = (data->alarms >> bitalarmfan[ix]) & 1;
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	/* sync the data cache */
	reg = vt1211_पढ़ो8(data, VT1211_REG_FAN_DIV);
	data->fan_भाग[0] = (reg >> 4) & 3;
	data->fan_भाग[1] = (reg >> 6) & 3;
	data->fan_ctl = reg & 0xf;

	चयन (fn) अणु
	हाल SHOW_SET_FAN_MIN:
		data->fan_min[ix] = RPM_TO_REG(val, data->fan_भाग[ix]);
		vt1211_ग_लिखो8(data, VT1211_REG_FAN_MIN(ix),
			      data->fan_min[ix]);
		अवरोध;
	हाल SHOW_SET_FAN_DIV:
		चयन (val) अणु
		हाल 1:
			data->fan_भाग[ix] = 0;
			अवरोध;
		हाल 2:
			data->fan_भाग[ix] = 1;
			अवरोध;
		हाल 4:
			data->fan_भाग[ix] = 2;
			अवरोध;
		हाल 8:
			data->fan_भाग[ix] = 3;
			अवरोध;
		शेष:
			count = -EINVAL;
			dev_warn(dev,
				 "fan div value %ld not supported. Choose one of 1, 2, 4, or 8.\n",
				 val);
			जाओ EXIT;
		पूर्ण
		vt1211_ग_लिखो8(data, VT1211_REG_FAN_DIV,
			      ((data->fan_भाग[1] << 6) |
			       (data->fan_भाग[0] << 4) |
				data->fan_ctl));
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

EXIT:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * PWM sysfs पूर्णांकerfaces
 * ix = [0-1]
 * --------------------------------------------------------------------- */

#घोषणा SHOW_PWM			0
#घोषणा SHOW_SET_PWM_ENABLE		1
#घोषणा SHOW_SET_PWM_FREQ		2
#घोषणा SHOW_SET_PWM_AUTO_CHANNELS_TEMP	3

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SHOW_PWM:
		res = data->pwm[ix];
		अवरोध;
	हाल SHOW_SET_PWM_ENABLE:
		res = ((data->pwm_ctl[ix] >> 3) & 1) ? 2 : 0;
		अवरोध;
	हाल SHOW_SET_PWM_FREQ:
		res = 90000 >> (data->pwm_clk & 7);
		अवरोध;
	हाल SHOW_SET_PWM_AUTO_CHANNELS_TEMP:
		res = (data->pwm_ctl[ix] & 7) + 1;
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक पंचांगp, reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	चयन (fn) अणु
	हाल SHOW_SET_PWM_ENABLE:
		/* sync the data cache */
		reg = vt1211_पढ़ो8(data, VT1211_REG_FAN_DIV);
		data->fan_भाग[0] = (reg >> 4) & 3;
		data->fan_भाग[1] = (reg >> 6) & 3;
		data->fan_ctl = reg & 0xf;
		reg = vt1211_पढ़ो8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = reg & 0xf;
		data->pwm_ctl[1] = (reg >> 4) & 0xf;
		चयन (val) अणु
		हाल 0:
			data->pwm_ctl[ix] &= 7;
			/*
			 * disable SmartGuardian अगर both PWM outमाला_दो are
			 * disabled
			 */
			अगर ((data->pwm_ctl[ix ^ 1] & 1) == 0)
				data->fan_ctl &= 0xe;
			अवरोध;
		हाल 2:
			data->pwm_ctl[ix] |= 8;
			data->fan_ctl |= 1;
			अवरोध;
		शेष:
			count = -EINVAL;
			dev_warn(dev,
				 "pwm mode %ld not supported. Choose one of 0 or 2.\n",
				 val);
			जाओ EXIT;
		पूर्ण
		vt1211_ग_लिखो8(data, VT1211_REG_PWM_CTL,
			      ((data->pwm_ctl[1] << 4) |
				data->pwm_ctl[0]));
		vt1211_ग_लिखो8(data, VT1211_REG_FAN_DIV,
			      ((data->fan_भाग[1] << 6) |
			       (data->fan_भाग[0] << 4) |
				data->fan_ctl));
		अवरोध;
	हाल SHOW_SET_PWM_FREQ:
		val = 135000 / clamp_val(val, 135000 >> 7, 135000);
		/* calculate पंचांगp = log2(val) */
		पंचांगp = 0;
		क्रम (val >>= 1; val > 0; val >>= 1)
			पंचांगp++;
		/* sync the data cache */
		reg = vt1211_पढ़ो8(data, VT1211_REG_PWM_CLK);
		data->pwm_clk = (reg & 0xf8) | पंचांगp;
		vt1211_ग_लिखो8(data, VT1211_REG_PWM_CLK, data->pwm_clk);
		अवरोध;
	हाल SHOW_SET_PWM_AUTO_CHANNELS_TEMP:
		अगर (val < 1 || val > 7) अणु
			count = -EINVAL;
			dev_warn(dev,
				 "temp channel %ld not supported. Choose a value between 1 and 7.\n",
				 val);
			जाओ EXIT;
		पूर्ण
		अगर (!ISTEMP(val - 1, data->uch_config)) अणु
			count = -EINVAL;
			dev_warn(dev, "temp channel %ld is not available.\n",
				 val);
			जाओ EXIT;
		पूर्ण
		/* sync the data cache */
		reg = vt1211_पढ़ो8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = reg & 0xf;
		data->pwm_ctl[1] = (reg >> 4) & 0xf;
		data->pwm_ctl[ix] = (data->pwm_ctl[ix] & 8) | (val - 1);
		vt1211_ग_लिखो8(data, VT1211_REG_PWM_CTL,
			      ((data->pwm_ctl[1] << 4) | data->pwm_ctl[0]));
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	पूर्ण

EXIT:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * PWM स्वतः poपूर्णांक definitions
 * ix = [0-1]
 * ap = [0-3]
 * --------------------------------------------------------------------- */

/*
 * pwm[ix+1]_स्वतः_poपूर्णांक[ap+1]_temp mapping table:
 * Note that there is only a single set of temp स्वतः poपूर्णांकs that controls both
 * PWM controllers. We still create 2 sets of sysfs files to make it look
 * more consistent even though they map to the same रेजिस्टरs.
 *
 * ix ap : description
 * -------------------
 * 0  0  : pwm1/2 off temperature        (pwm_स्वतः_temp[0])
 * 0  1  : pwm1/2 low speed temperature  (pwm_स्वतः_temp[1])
 * 0  2  : pwm1/2 high speed temperature (pwm_स्वतः_temp[2])
 * 0  3  : pwm1/2 full speed temperature (pwm_स्वतः_temp[3])
 * 1  0  : pwm1/2 off temperature        (pwm_स्वतः_temp[0])
 * 1  1  : pwm1/2 low speed temperature  (pwm_स्वतः_temp[1])
 * 1  2  : pwm1/2 high speed temperature (pwm_स्वतः_temp[2])
 * 1  3  : pwm1/2 full speed temperature (pwm_स्वतः_temp[3])
 */

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक ap = sensor_attr_2->nr;

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->pwm_ctl[ix] & 7,
		       data->pwm_स्वतः_temp[ap]));
पूर्ण

अटल sमाप_प्रकार set_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक ap = sensor_attr_2->nr;
	पूर्णांक reg;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;


	mutex_lock(&data->update_lock);

	/* sync the data cache */
	reg = vt1211_पढ़ो8(data, VT1211_REG_PWM_CTL);
	data->pwm_ctl[0] = reg & 0xf;
	data->pwm_ctl[1] = (reg >> 4) & 0xf;

	data->pwm_स्वतः_temp[ap] = TEMP_TO_REG(data->pwm_ctl[ix] & 7, val);
	vt1211_ग_लिखो8(data, VT1211_REG_PWM_AUTO_TEMP(ap),
		      data->pwm_स्वतः_temp[ap]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/*
 * pwm[ix+1]_स्वतः_poपूर्णांक[ap+1]_pwm mapping table:
 * Note that the PWM स्वतः poपूर्णांकs 0 & 3 are hard-wired in the VT1211 and can't
 * be changed.
 *
 * ix ap : description
 * -------------------
 * 0  0  : pwm1 off                   (pwm_स्वतः_pwm[0][0], hard-wired to 0)
 * 0  1  : pwm1 low speed duty cycle  (pwm_स्वतः_pwm[0][1])
 * 0  2  : pwm1 high speed duty cycle (pwm_स्वतः_pwm[0][2])
 * 0  3  : pwm1 full speed            (pwm_स्वतः_pwm[0][3], hard-wired to 255)
 * 1  0  : pwm2 off                   (pwm_स्वतः_pwm[1][0], hard-wired to 0)
 * 1  1  : pwm2 low speed duty cycle  (pwm_स्वतः_pwm[1][1])
 * 1  2  : pwm2 high speed duty cycle (pwm_स्वतः_pwm[1][2])
 * 1  3  : pwm2 full speed            (pwm_स्वतः_pwm[1][3], hard-wired to 255)
 */

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक ap = sensor_attr_2->nr;

	वापस प्र_लिखो(buf, "%d\n", data->pwm_स्वतः_pwm[ix][ap]);
पूर्ण

अटल sमाप_प्रकार set_pwm_स्वतः_poपूर्णांक_pwm(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक ap = sensor_attr_2->nr;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm_स्वतः_pwm[ix][ap] = clamp_val(val, 0, 255);
	vt1211_ग_लिखो8(data, VT1211_REG_PWM_AUTO_PWM(ix, ap),
		      data->pwm_स्वतः_pwm[ix][ap]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Miscellaneous sysfs पूर्णांकerfaces (VRM, VID, name, and (legacy) alarms)
 * --------------------------------------------------------------------- */

अटल sमाप_प्रकार show_vrm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार set_vrm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;

	data->vrm = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_vid(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

अटल sमाप_प्रकार show_alarms(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vt1211_data *data = vt1211_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

/* ---------------------------------------------------------------------
 * Device attribute काष्ठाs
 * --------------------------------------------------------------------- */

#घोषणा SENSOR_ATTR_IN(ix) \
अणु	SENSOR_ATTR_2(in##ix##_input, S_IRUGO, \
		show_in, शून्य, SHOW_IN_INPUT, ix), \
	SENSOR_ATTR_2(in##ix##_min, S_IRUGO | S_IWUSR, \
		show_in, set_in, SHOW_SET_IN_MIN, ix), \
	SENSOR_ATTR_2(in##ix##_max, S_IRUGO | S_IWUSR, \
		show_in, set_in, SHOW_SET_IN_MAX, ix), \
	SENSOR_ATTR_2(in##ix##_alarm, S_IRUGO, \
		show_in, शून्य, SHOW_IN_ALARM, ix) \
पूर्ण

अटल काष्ठा sensor_device_attribute_2 vt1211_sysfs_in[][4] = अणु
	SENSOR_ATTR_IN(0),
	SENSOR_ATTR_IN(1),
	SENSOR_ATTR_IN(2),
	SENSOR_ATTR_IN(3),
	SENSOR_ATTR_IN(4),
	SENSOR_ATTR_IN(5)
पूर्ण;

#घोषणा IN_UNIT_ATTRS(X)			\
अणु	&vt1211_sysfs_in[X][0].dev_attr.attr,	\
	&vt1211_sysfs_in[X][1].dev_attr.attr,	\
	&vt1211_sysfs_in[X][2].dev_attr.attr,	\
	&vt1211_sysfs_in[X][3].dev_attr.attr,	\
	शून्य					\
पूर्ण

अटल काष्ठा attribute *vt1211_in_attr[][5] = अणु
	IN_UNIT_ATTRS(0),
	IN_UNIT_ATTRS(1),
	IN_UNIT_ATTRS(2),
	IN_UNIT_ATTRS(3),
	IN_UNIT_ATTRS(4),
	IN_UNIT_ATTRS(5)
पूर्ण;

अटल स्थिर काष्ठा attribute_group vt1211_in_attr_group[] = अणु
	अणु .attrs = vt1211_in_attr[0] पूर्ण,
	अणु .attrs = vt1211_in_attr[1] पूर्ण,
	अणु .attrs = vt1211_in_attr[2] पूर्ण,
	अणु .attrs = vt1211_in_attr[3] पूर्ण,
	अणु .attrs = vt1211_in_attr[4] पूर्ण,
	अणु .attrs = vt1211_in_attr[5] पूर्ण
पूर्ण;

#घोषणा SENSOR_ATTR_TEMP(ix) \
अणु	SENSOR_ATTR_2(temp##ix##_input, S_IRUGO, \
		show_temp, शून्य, SHOW_TEMP_INPUT, ix-1), \
	SENSOR_ATTR_2(temp##ix##_max, S_IRUGO | S_IWUSR, \
		show_temp, set_temp, SHOW_SET_TEMP_MAX, ix-1), \
	SENSOR_ATTR_2(temp##ix##_max_hyst, S_IRUGO | S_IWUSR, \
		show_temp, set_temp, SHOW_SET_TEMP_MAX_HYST, ix-1), \
	SENSOR_ATTR_2(temp##ix##_alarm, S_IRUGO, \
		show_temp, शून्य, SHOW_TEMP_ALARM, ix-1) \
पूर्ण

अटल काष्ठा sensor_device_attribute_2 vt1211_sysfs_temp[][4] = अणु
	SENSOR_ATTR_TEMP(1),
	SENSOR_ATTR_TEMP(2),
	SENSOR_ATTR_TEMP(3),
	SENSOR_ATTR_TEMP(4),
	SENSOR_ATTR_TEMP(5),
	SENSOR_ATTR_TEMP(6),
	SENSOR_ATTR_TEMP(7),
पूर्ण;

#घोषणा TEMP_UNIT_ATTRS(X)			\
अणु	&vt1211_sysfs_temp[X][0].dev_attr.attr,	\
	&vt1211_sysfs_temp[X][1].dev_attr.attr,	\
	&vt1211_sysfs_temp[X][2].dev_attr.attr,	\
	&vt1211_sysfs_temp[X][3].dev_attr.attr,	\
	शून्य					\
पूर्ण

अटल काष्ठा attribute *vt1211_temp_attr[][5] = अणु
	TEMP_UNIT_ATTRS(0),
	TEMP_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(2),
	TEMP_UNIT_ATTRS(3),
	TEMP_UNIT_ATTRS(4),
	TEMP_UNIT_ATTRS(5),
	TEMP_UNIT_ATTRS(6)
पूर्ण;

अटल स्थिर काष्ठा attribute_group vt1211_temp_attr_group[] = अणु
	अणु .attrs = vt1211_temp_attr[0] पूर्ण,
	अणु .attrs = vt1211_temp_attr[1] पूर्ण,
	अणु .attrs = vt1211_temp_attr[2] पूर्ण,
	अणु .attrs = vt1211_temp_attr[3] पूर्ण,
	अणु .attrs = vt1211_temp_attr[4] पूर्ण,
	अणु .attrs = vt1211_temp_attr[5] पूर्ण,
	अणु .attrs = vt1211_temp_attr[6] पूर्ण
पूर्ण;

#घोषणा SENSOR_ATTR_FAN(ix) \
	SENSOR_ATTR_2(fan##ix##_input, S_IRUGO, \
		show_fan, शून्य, SHOW_FAN_INPUT, ix-1), \
	SENSOR_ATTR_2(fan##ix##_min, S_IRUGO | S_IWUSR, \
		show_fan, set_fan, SHOW_SET_FAN_MIN, ix-1), \
	SENSOR_ATTR_2(fan##ix##_भाग, S_IRUGO | S_IWUSR, \
		show_fan, set_fan, SHOW_SET_FAN_DIV, ix-1), \
	SENSOR_ATTR_2(fan##ix##_alarm, S_IRUGO, \
		show_fan, शून्य, SHOW_FAN_ALARM, ix-1)

#घोषणा SENSOR_ATTR_PWM(ix) \
	SENSOR_ATTR_2(pwm##ix, S_IRUGO, \
		show_pwm, शून्य, SHOW_PWM, ix-1), \
	SENSOR_ATTR_2(pwm##ix##_enable, S_IRUGO | S_IWUSR, \
		show_pwm, set_pwm, SHOW_SET_PWM_ENABLE, ix-1), \
	SENSOR_ATTR_2(pwm##ix##_स्वतः_channels_temp, S_IRUGO | S_IWUSR, \
		show_pwm, set_pwm, SHOW_SET_PWM_AUTO_CHANNELS_TEMP, ix-1)

#घोषणा SENSOR_ATTR_PWM_FREQ(ix) \
	SENSOR_ATTR_2(pwm##ix##_freq, S_IRUGO | S_IWUSR, \
		show_pwm, set_pwm, SHOW_SET_PWM_FREQ, ix-1)

#घोषणा SENSOR_ATTR_PWM_FREQ_RO(ix) \
	SENSOR_ATTR_2(pwm##ix##_freq, S_IRUGO, \
		show_pwm, शून्य, SHOW_SET_PWM_FREQ, ix-1)

#घोषणा SENSOR_ATTR_PWM_AUTO_POINT_TEMP(ix, ap) \
	SENSOR_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक##ap##_temp, S_IRUGO | S_IWUSR, \
		show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp, \
		ap-1, ix-1)

#घोषणा SENSOR_ATTR_PWM_AUTO_POINT_TEMP_RO(ix, ap) \
	SENSOR_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक##ap##_temp, S_IRUGO, \
		show_pwm_स्वतः_poपूर्णांक_temp, शून्य, \
		ap-1, ix-1)

#घोषणा SENSOR_ATTR_PWM_AUTO_POINT_PWM(ix, ap) \
	SENSOR_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक##ap##_pwm, S_IRUGO | S_IWUSR, \
		show_pwm_स्वतः_poपूर्णांक_pwm, set_pwm_स्वतः_poपूर्णांक_pwm, \
		ap-1, ix-1)

#घोषणा SENSOR_ATTR_PWM_AUTO_POINT_PWM_RO(ix, ap) \
	SENSOR_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक##ap##_pwm, S_IRUGO, \
		show_pwm_स्वतः_poपूर्णांक_pwm, शून्य, \
		ap-1, ix-1)

अटल काष्ठा sensor_device_attribute_2 vt1211_sysfs_fan_pwm[] = अणु
	SENSOR_ATTR_FAN(1),
	SENSOR_ATTR_FAN(2),
	SENSOR_ATTR_PWM(1),
	SENSOR_ATTR_PWM(2),
	SENSOR_ATTR_PWM_FREQ(1),
	SENSOR_ATTR_PWM_FREQ_RO(2),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP(1, 1),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP(1, 2),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP(1, 3),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP(1, 4),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP_RO(2, 1),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP_RO(2, 2),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP_RO(2, 3),
	SENSOR_ATTR_PWM_AUTO_POINT_TEMP_RO(2, 4),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM_RO(1, 1),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM(1, 2),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM(1, 3),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM_RO(1, 4),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM_RO(2, 1),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM(2, 2),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM(2, 3),
	SENSOR_ATTR_PWM_AUTO_POINT_PWM_RO(2, 4),
पूर्ण;

अटल काष्ठा device_attribute vt1211_sysfs_misc[] = अणु
	__ATTR(vrm, S_IRUGO | S_IWUSR, show_vrm, set_vrm),
	__ATTR(cpu0_vid, S_IRUGO, show_vid, शून्य),
	__ATTR(name, S_IRUGO, show_name, शून्य),
	__ATTR(alarms, S_IRUGO, show_alarms, शून्य),
पूर्ण;

/* ---------------------------------------------------------------------
 * Device registration and initialization
 * --------------------------------------------------------------------- */

अटल व्योम vt1211_init_device(काष्ठा vt1211_data *data)
अणु
	/* set VRM */
	data->vrm = vid_which_vrm();

	/* Read (and initialize) UCH config */
	data->uch_config = vt1211_पढ़ो8(data, VT1211_REG_UCH_CONFIG);
	अगर (uch_config > -1) अणु
		data->uch_config = (data->uch_config & 0x83) |
				   (uch_config << 2);
		vt1211_ग_लिखो8(data, VT1211_REG_UCH_CONFIG, data->uch_config);
	पूर्ण

	/*
	 * Initialize the पूर्णांकerrupt mode (अगर request at module load समय).
	 * The VT1211 implements 3 dअगरferent modes क्रम clearing पूर्णांकerrupts:
	 * 0: Clear INT when status रेजिस्टर is पढ़ो. Regenerate INT as दीर्घ
	 *    as temp stays above hysteresis limit.
	 * 1: Clear INT when status रेजिस्टर is पढ़ो. DON'T regenerate INT
	 *    until temp falls below hysteresis limit and exceeds hot limit
	 *    again.
	 * 2: Clear INT when temp falls below max limit.
	 *
	 * The driver only allows to क्रमce mode 0 since that's the only one
	 * that makes sense क्रम 'sensors'
	 */
	अगर (पूर्णांक_mode == 0) अणु
		vt1211_ग_लिखो8(data, VT1211_REG_TEMP1_CONFIG, 0);
		vt1211_ग_लिखो8(data, VT1211_REG_TEMP2_CONFIG, 0);
	पूर्ण

	/* Fill in some hard wired values पूर्णांकo our data काष्ठा */
	data->pwm_स्वतः_pwm[0][3] = 255;
	data->pwm_स्वतः_pwm[1][3] = 255;
पूर्ण

अटल व्योम vt1211_हटाओ_sysfs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vt1211_in_attr_group); i++)
		sysfs_हटाओ_group(&dev->kobj, &vt1211_in_attr_group[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vt1211_temp_attr_group); i++)
		sysfs_हटाओ_group(&dev->kobj, &vt1211_temp_attr_group[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vt1211_sysfs_fan_pwm); i++) अणु
		device_हटाओ_file(dev,
			&vt1211_sysfs_fan_pwm[i].dev_attr);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(vt1211_sysfs_misc); i++)
		device_हटाओ_file(dev, &vt1211_sysfs_misc[i]);
पूर्ण

अटल पूर्णांक vt1211_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vt1211_data *data;
	काष्ठा resource *res;
	पूर्णांक i, err;

	data = devm_kzalloc(dev, माप(काष्ठा vt1211_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start, resource_size(res),
				 DRVNAME)) अणु
		dev_err(dev, "Failed to request region 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end);
		वापस -EBUSY;
	पूर्ण
	data->addr = res->start;
	data->name = DRVNAME;
	mutex_init(&data->update_lock);

	platक्रमm_set_drvdata(pdev, data);

	/* Initialize the VT1211 chip */
	vt1211_init_device(data);

	/* Create sysfs पूर्णांकerface files */
	क्रम (i = 0; i < ARRAY_SIZE(vt1211_in_attr_group); i++) अणु
		अगर (ISVOLT(i, data->uch_config)) अणु
			err = sysfs_create_group(&dev->kobj,
						 &vt1211_in_attr_group[i]);
			अगर (err)
				जाओ EXIT_DEV_REMOVE;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(vt1211_temp_attr_group); i++) अणु
		अगर (ISTEMP(i, data->uch_config)) अणु
			err = sysfs_create_group(&dev->kobj,
						 &vt1211_temp_attr_group[i]);
			अगर (err)
				जाओ EXIT_DEV_REMOVE;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(vt1211_sysfs_fan_pwm); i++) अणु
		err = device_create_file(dev,
			&vt1211_sysfs_fan_pwm[i].dev_attr);
		अगर (err)
			जाओ EXIT_DEV_REMOVE;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(vt1211_sysfs_misc); i++) अणु
		err = device_create_file(dev,
		       &vt1211_sysfs_misc[i]);
		अगर (err)
			जाओ EXIT_DEV_REMOVE;
	पूर्ण

	/* Register device */
	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		dev_err(dev, "Class registration failed (%d)\n", err);
		जाओ EXIT_DEV_REMOVE_SILENT;
	पूर्ण

	वापस 0;

EXIT_DEV_REMOVE:
	dev_err(dev, "Sysfs interface creation failed (%d)\n", err);
EXIT_DEV_REMOVE_SILENT:
	vt1211_हटाओ_sysfs(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक vt1211_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt1211_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	vt1211_हटाओ_sysfs(pdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vt1211_driver = अणु
	.driver = अणु
		.name  = DRVNAME,
	पूर्ण,
	.probe  = vt1211_probe,
	.हटाओ = vt1211_हटाओ,
पूर्ण;

अटल पूर्णांक __init vt1211_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + 0x7f,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed (%d)\n", err);
		जाओ EXIT;
	पूर्ण

	res.name = pdev->name;
	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ EXIT_DEV_PUT;

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ EXIT_DEV_PUT;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ EXIT_DEV_PUT;
	पूर्ण

	वापस 0;

EXIT_DEV_PUT:
	platक्रमm_device_put(pdev);
EXIT:
	वापस err;
पूर्ण

अटल पूर्णांक __init vt1211_find(पूर्णांक sio_cip, अचिन्हित लघु *address)
अणु
	पूर्णांक err;
	पूर्णांक devid;

	err = superio_enter(sio_cip);
	अगर (err)
		वापस err;

	err = -ENODEV;
	devid = क्रमce_id ? क्रमce_id : superio_inb(sio_cip, SIO_VT1211_DEVID);
	अगर (devid != SIO_VT1211_ID)
		जाओ EXIT;

	superio_select(sio_cip, SIO_VT1211_LDN_HWMON);

	अगर ((superio_inb(sio_cip, SIO_VT1211_ACTIVE) & 1) == 0) अणु
		pr_warn("HW monitor is disabled, skipping\n");
		जाओ EXIT;
	पूर्ण

	*address = ((superio_inb(sio_cip, SIO_VT1211_BADDR) << 8) |
		    (superio_inb(sio_cip, SIO_VT1211_BADDR + 1))) & 0xff00;
	अगर (*address == 0) अणु
		pr_warn("Base address is not set, skipping\n");
		जाओ EXIT;
	पूर्ण

	err = 0;
	pr_info("Found VT1211 chip at 0x%04x, revision %u\n",
		*address, superio_inb(sio_cip, SIO_VT1211_DEVREV));

EXIT:
	superio_निकास(sio_cip);
	वापस err;
पूर्ण

अटल पूर्णांक __init vt1211_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु address = 0;

	err = vt1211_find(SIO_REG_CIP1, &address);
	अगर (err) अणु
		err = vt1211_find(SIO_REG_CIP2, &address);
		अगर (err)
			जाओ EXIT;
	पूर्ण

	अगर ((uch_config < -1) || (uch_config > 31)) अणु
		err = -EINVAL;
		pr_warn("Invalid UCH configuration %d. Choose a value between 0 and 31.\n",
			uch_config);
		जाओ EXIT;
	पूर्ण

	अगर ((पूर्णांक_mode < -1) || (पूर्णांक_mode > 0)) अणु
		err = -EINVAL;
		pr_warn("Invalid interrupt mode %d. Only mode 0 is supported.\n",
			पूर्णांक_mode);
		जाओ EXIT;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&vt1211_driver);
	अगर (err)
		जाओ EXIT;

	/* Sets global pdev as a side effect */
	err = vt1211_device_add(address);
	अगर (err)
		जाओ EXIT_DRV_UNREGISTER;

	वापस 0;

EXIT_DRV_UNREGISTER:
	platक्रमm_driver_unरेजिस्टर(&vt1211_driver);
EXIT:
	वापस err;
पूर्ण

अटल व्योम __निकास vt1211_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&vt1211_driver);
पूर्ण

MODULE_AUTHOR("Juerg Haefliger <juergh@gmail.com>");
MODULE_DESCRIPTION("VT1211 sensors");
MODULE_LICENSE("GPL");

module_init(vt1211_init);
module_निकास(vt1211_निकास);
