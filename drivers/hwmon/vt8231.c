<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vt8231.c - Part of lm_sensors, Linux kernel modules
 *	      क्रम hardware monitoring
 *
 * Copyright (c) 2005 Roger Lucas <vt8231@hiddenengine.co.uk>
 * Copyright (c) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
 *		      Aaron M. Marsh <amarsh@sdf.lonestar.org>
 */

/*
 * Supports VIA VT8231 South Bridge embedded sensors
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल पूर्णांक क्रमce_addr;
module_param(क्रमce_addr, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce_addr, "Initialize the base address of the sensors");

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा VT8231_EXTENT 0x80
#घोषणा VT8231_BASE_REG 0x70
#घोषणा VT8231_ENABLE_REG 0x74

/*
 * The VT8231 रेजिस्टरs
 *
 * The reset value क्रम the input channel configuration is used (Reg 0x4A=0x07)
 * which sets the selected inमाला_दो marked with '*' below अगर multiple options are
 * possible:
 *
 *		    Voltage Mode	  Temperature Mode
 *	Sensor	      Linux Id	      Linux Id	      VIA Id
 *	--------      --------	      --------	      ------
 *	CPU Diode	N/A		temp1		0
 *	UIC1		in0		temp2 *		1
 *	UIC2		in1 *		temp3		2
 *	UIC3		in2 *		temp4		3
 *	UIC4		in3 *		temp5		4
 *	UIC5		in4 *		temp6		5
 *	3.3V		in5		N/A
 *
 * Note that the BIOS may set the configuration रेजिस्टर to a dअगरferent value
 * to match the motherboard configuration.
 */

/* fans numbered 0-1 */
#घोषणा VT8231_REG_FAN_MIN(nr)	(0x3b + (nr))
#घोषणा VT8231_REG_FAN(nr)	(0x29 + (nr))

/* Voltage inमाला_दो numbered 0-5 */

अटल स्थिर u8 regvolt[]    = अणु 0x21, 0x22, 0x23, 0x24, 0x25, 0x26 पूर्ण;
अटल स्थिर u8 regvolपंचांगax[] = अणु 0x3d, 0x2b, 0x2d, 0x2f, 0x31, 0x33 पूर्ण;
अटल स्थिर u8 regvolपंचांगin[] = अणु 0x3e, 0x2c, 0x2e, 0x30, 0x32, 0x34 पूर्ण;

/*
 * Temperatures are numbered 1-6 according to the Linux kernel specअगरication.
 *
 * In the VIA datasheet, however, the temperatures are numbered from zero.
 * Since it is important that this driver can easily be compared to the VIA
 * datasheet, we will use the VIA numbering within this driver and map the
 * kernel sysfs device name to the VIA number in the sysfs callback.
 */

#घोषणा VT8231_REG_TEMP_LOW01	0x49
#घोषणा VT8231_REG_TEMP_LOW25	0x4d

अटल स्थिर u8 regtemp[]    = अणु 0x1f, 0x21, 0x22, 0x23, 0x24, 0x25 पूर्ण;
अटल स्थिर u8 regtempmax[] = अणु 0x39, 0x3d, 0x2b, 0x2d, 0x2f, 0x31 पूर्ण;
अटल स्थिर u8 regtempmin[] = अणु 0x3a, 0x3e, 0x2c, 0x2e, 0x30, 0x32 पूर्ण;

#घोषणा TEMP_FROM_REG(reg)		(((253 * 4 - (reg)) * 550 + 105) / 210)
#घोषणा TEMP_MAXMIN_FROM_REG(reg)	(((253 - (reg)) * 2200 + 105) / 210)
#घोषणा TEMP_MAXMIN_TO_REG(val)		(253 - ((val) * 210 + 1100) / 2200)

#घोषणा VT8231_REG_CONFIG 0x40
#घोषणा VT8231_REG_ALARM1 0x41
#घोषणा VT8231_REG_ALARM2 0x42
#घोषणा VT8231_REG_FANDIV 0x47
#घोषणा VT8231_REG_UCH_CONFIG 0x4a
#घोषणा VT8231_REG_TEMP1_CONFIG 0x4b
#घोषणा VT8231_REG_TEMP2_CONFIG 0x4c

/*
 * temps 0-5 as numbered in VIA datasheet - see later क्रम mapping to Linux
 * numbering
 */
#घोषणा ISTEMP(i, ch_config) ((i) == 0 ? 1 : \
			      ((ch_config) >> ((i)+1)) & 0x01)
/* voltages 0-5 */
#घोषणा ISVOLT(i, ch_config) ((i) == 5 ? 1 : \
			      !(((ch_config) >> ((i)+2)) & 0x01))

#घोषणा DIV_FROM_REG(val) (1 << (val))

/*
 * NB  The values वापसed here are NOT temperatures.  The calibration curves
 *     क्रम the thermistor curves are board-specअगरic and must go in the
 *     sensors.conf file.  Temperature sensors are actually ten bits, but the
 *     VIA datasheet only considers the 8 MSBs obtained from the regtemp[]
 *     रेजिस्टर.  The temperature value वापसed should have a magnitude of 3,
 *     so we use the VIA scaling as the "true" scaling and use the reमुख्यing 2
 *     LSBs as fractional precision.
 *
 *     All the on-chip hardware temperature comparisons क्रम the alarms are only
 *     8-bits wide, and compare against the 8 MSBs of the temperature.  The bits
 *     in the रेजिस्टरs VT8231_REG_TEMP_LOW01 and VT8231_REG_TEMP_LOW25 are
 *     ignored.
 */

/*
 ****** FAN RPM CONVERSIONS ********
 * This chip saturates back at 0, not at 255 like many the other chips.
 * So, 0 means 0 RPM
 */
अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm <= 0 || rpm > 1310720)
		वापस 0;
	वापस clamp_val(1310720 / (rpm * भाग), 1, 255);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग) ((val) == 0 ? 0 : 1310720 / ((val) * (भाग)))

काष्ठा vt8231_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;

	काष्ठा mutex update_lock;
	काष्ठा device *hwmon_dev;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[6];		/* Register value */
	u8 in_max[6];		/* Register value */
	u8 in_min[6];		/* Register value */
	u16 temp[6];		/* Register value 10 bit, right aligned */
	u8 temp_max[6];		/* Register value */
	u8 temp_min[6];		/* Register value */
	u8 fan[2];		/* Register value */
	u8 fan_min[2];		/* Register value */
	u8 fan_भाग[2];		/* Register encoding, shअगरted right */
	u16 alarms;		/* Register encoding */
	u8 uch_config;
पूर्ण;

अटल काष्ठा pci_dev *s_bridge;
अटल पूर्णांक vt8231_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक vt8231_हटाओ(काष्ठा platक्रमm_device *pdev);
अटल काष्ठा vt8231_data *vt8231_update_device(काष्ठा device *dev);
अटल व्योम vt8231_init_device(काष्ठा vt8231_data *data);

अटल अंतरभूत पूर्णांक vt8231_पढ़ो_value(काष्ठा vt8231_data *data, u8 reg)
अणु
	वापस inb_p(data->addr + reg);
पूर्ण

अटल अंतरभूत व्योम vt8231_ग_लिखो_value(काष्ठा vt8231_data *data, u8 reg,
					u8 value)
अणु
	outb_p(value, data->addr + reg);
पूर्ण

/* following are the sysfs callback functions */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", ((data->in[nr] - 3) * 10000) / 958);
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", ((data->in_min[nr] - 3) * 10000) / 958);
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", (((data->in_max[nr] - 3) * 10000) / 958));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = clamp_val(((val * 958) / 10000) + 3, 0, 255);
	vt8231_ग_लिखो_value(data, regvolपंचांगin[nr], data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = clamp_val(((val * 958) / 10000) + 3, 0, 255);
	vt8231_ग_लिखो_value(data, regvolपंचांगax[nr], data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* Special हाल क्रम input 5 as this has 3.3V scaling built पूर्णांकo the chip */
अटल sमाप_प्रकार in5_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n",
		(((data->in[5] - 3) * 10000 * 54) / (958 * 34)));
पूर्ण

अटल sमाप_प्रकार in5_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n",
		(((data->in_min[5] - 3) * 10000 * 54) / (958 * 34)));
पूर्ण

अटल sमाप_प्रकार in5_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n",
		(((data->in_max[5] - 3) * 10000 * 54) / (958 * 34)));
पूर्ण

अटल sमाप_प्रकार in5_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[5] = clamp_val(((val * 958 * 34) / (10000 * 54)) + 3,
				    0, 255);
	vt8231_ग_लिखो_value(data, regvolपंचांगin[5], data->in_min[5]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in5_max_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[5] = clamp_val(((val * 958 * 34) / (10000 * 54)) + 3,
				    0, 255);
	vt8231_ग_लिखो_value(data, regvolपंचांगax[5], data->in_max[5]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);

अटल DEVICE_ATTR_RO(in5_input);
अटल DEVICE_ATTR_RW(in5_min);
अटल DEVICE_ATTR_RW(in5_max);

/* Temperatures */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp[0] * 250);
पूर्ण

अटल sमाप_प्रकार temp1_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_max[0] * 1000);
पूर्ण

अटल sमाप_प्रकार temp1_max_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_min[0] * 1000);
पूर्ण

अटल sमाप_प्रकार temp1_max_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[0] = clamp_val((val + 500) / 1000, 0, 255);
	vt8231_ग_लिखो_value(data, regtempmax[0], data->temp_max[0]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp1_max_hyst_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[0] = clamp_val((val + 500) / 1000, 0, 255);
	vt8231_ग_लिखो_value(data, regtempmin[0], data->temp_min[0]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_MAXMIN_FROM_REG(data->temp_max[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_MAXMIN_FROM_REG(data->temp_min[nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = clamp_val(TEMP_MAXMIN_TO_REG(val), 0, 255);
	vt8231_ग_लिखो_value(data, regtempmax[nr], data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = clamp_val(TEMP_MAXMIN_TO_REG(val), 0, 255);
	vt8231_ग_लिखो_value(data, regtempmin[nr], data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Note that these map the Linux temperature sensor numbering (1-6) to the VIA
 * temperature sensor numbering (0-5)
 */

अटल DEVICE_ATTR_RO(temp1_input);
अटल DEVICE_ATTR_RW(temp1_max);
अटल DEVICE_ATTR_RW(temp1_max_hyst);

अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max_hyst, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max_hyst, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp_max, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max_hyst, temp_min, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp5_max, temp_max, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp5_max_hyst, temp_min, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_input, temp, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp6_max, temp_max, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp6_max_hyst, temp_min, 5);

/* Fans */
अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
				DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
			DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	vt8231_ग_लिखो_value(data, VT8231_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	अचिन्हित दीर्घ val;
	पूर्णांक nr = sensor_attr->index;
	पूर्णांक old = vt8231_पढ़ो_value(data, VT8231_REG_FANDIV);
	दीर्घ min = FAN_FROM_REG(data->fan_min[nr],
				 DIV_FROM_REG(data->fan_भाग[nr]));
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 1:
		data->fan_भाग[nr] = 0;
		अवरोध;
	हाल 2:
		data->fan_भाग[nr] = 1;
		अवरोध;
	हाल 4:
		data->fan_भाग[nr] = 2;
		अवरोध;
	हाल 8:
		data->fan_भाग[nr] = 3;
		अवरोध;
	शेष:
		dev_err(dev,
			"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n",
			val);
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	/* Correct the fan minimum speed */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	vt8231_ग_लिखो_value(data, VT8231_REG_FAN_MIN(nr), data->fan_min[nr]);

	old = (old & 0x0f) | (data->fan_भाग[1] << 6) | (data->fan_भाग[0] << 4);
	vt8231_ग_लिखो_value(data, VT8231_REG_FANDIV, old);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा vt8231_data *data = vt8231_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp4_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp5_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp6_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute
			 *devattr, अक्षर *buf)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *vt8231_attributes_temps[6][5] = अणु
	अणु
		&dev_attr_temp1_input.attr,
		&dev_attr_temp1_max_hyst.attr,
		&dev_attr_temp1_max.attr,
		&sensor_dev_attr_temp1_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp2_input.dev_attr.attr,
		&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
		&sensor_dev_attr_temp2_max.dev_attr.attr,
		&sensor_dev_attr_temp2_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp3_input.dev_attr.attr,
		&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
		&sensor_dev_attr_temp3_max.dev_attr.attr,
		&sensor_dev_attr_temp3_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp4_input.dev_attr.attr,
		&sensor_dev_attr_temp4_max_hyst.dev_attr.attr,
		&sensor_dev_attr_temp4_max.dev_attr.attr,
		&sensor_dev_attr_temp4_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp5_input.dev_attr.attr,
		&sensor_dev_attr_temp5_max_hyst.dev_attr.attr,
		&sensor_dev_attr_temp5_max.dev_attr.attr,
		&sensor_dev_attr_temp5_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp6_input.dev_attr.attr,
		&sensor_dev_attr_temp6_max_hyst.dev_attr.attr,
		&sensor_dev_attr_temp6_max.dev_attr.attr,
		&sensor_dev_attr_temp6_alarm.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group vt8231_group_temps[6] = अणु
	अणु .attrs = vt8231_attributes_temps[0] पूर्ण,
	अणु .attrs = vt8231_attributes_temps[1] पूर्ण,
	अणु .attrs = vt8231_attributes_temps[2] पूर्ण,
	अणु .attrs = vt8231_attributes_temps[3] पूर्ण,
	अणु .attrs = vt8231_attributes_temps[4] पूर्ण,
	अणु .attrs = vt8231_attributes_temps[5] पूर्ण,
पूर्ण;

अटल काष्ठा attribute *vt8231_attributes_volts[6][5] = अणु
	अणु
		&sensor_dev_attr_in0_input.dev_attr.attr,
		&sensor_dev_attr_in0_min.dev_attr.attr,
		&sensor_dev_attr_in0_max.dev_attr.attr,
		&sensor_dev_attr_in0_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in1_input.dev_attr.attr,
		&sensor_dev_attr_in1_min.dev_attr.attr,
		&sensor_dev_attr_in1_max.dev_attr.attr,
		&sensor_dev_attr_in1_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in2_input.dev_attr.attr,
		&sensor_dev_attr_in2_min.dev_attr.attr,
		&sensor_dev_attr_in2_max.dev_attr.attr,
		&sensor_dev_attr_in2_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in3_input.dev_attr.attr,
		&sensor_dev_attr_in3_min.dev_attr.attr,
		&sensor_dev_attr_in3_max.dev_attr.attr,
		&sensor_dev_attr_in3_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in4_input.dev_attr.attr,
		&sensor_dev_attr_in4_min.dev_attr.attr,
		&sensor_dev_attr_in4_max.dev_attr.attr,
		&sensor_dev_attr_in4_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&dev_attr_in5_input.attr,
		&dev_attr_in5_min.attr,
		&dev_attr_in5_max.attr,
		&sensor_dev_attr_in5_alarm.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group vt8231_group_volts[6] = अणु
	अणु .attrs = vt8231_attributes_volts[0] पूर्ण,
	अणु .attrs = vt8231_attributes_volts[1] पूर्ण,
	अणु .attrs = vt8231_attributes_volts[2] पूर्ण,
	अणु .attrs = vt8231_attributes_volts[3] पूर्ण,
	अणु .attrs = vt8231_attributes_volts[4] पूर्ण,
	अणु .attrs = vt8231_attributes_volts[5] पूर्ण,
पूर्ण;

अटल काष्ठा attribute *vt8231_attributes[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group vt8231_group = अणु
	.attrs = vt8231_attributes,
पूर्ण;

अटल काष्ठा platक्रमm_driver vt8231_driver = अणु
	.driver = अणु
		.name	= "vt8231",
	पूर्ण,
	.probe	= vt8231_probe,
	.हटाओ	= vt8231_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id vt8231_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8231_4) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, vt8231_pci_ids);

अटल पूर्णांक vt8231_pci_probe(काष्ठा pci_dev *dev,
				      स्थिर काष्ठा pci_device_id *id);

अटल काष्ठा pci_driver vt8231_pci_driver = अणु
	.name		= "vt8231",
	.id_table	= vt8231_pci_ids,
	.probe		= vt8231_pci_probe,
पूर्ण;

अटल पूर्णांक vt8231_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा vt8231_data *data;
	पूर्णांक err = 0, i;

	/* Reserve the ISA region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start, VT8231_EXTENT,
				 vt8231_driver.driver.name)) अणु
		dev_err(&pdev->dev, "Region 0x%lx-0x%lx already in use!\n",
			(अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end);
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा vt8231_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);
	data->addr = res->start;
	data->name = "vt8231";

	mutex_init(&data->update_lock);
	vt8231_init_device(data);

	/* Register sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &vt8231_group);
	अगर (err)
		वापस err;

	/* Must update device inक्रमmation to find out the config field */
	data->uch_config = vt8231_पढ़ो_value(data, VT8231_REG_UCH_CONFIG);

	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++) अणु
		अगर (ISTEMP(i, data->uch_config)) अणु
			err = sysfs_create_group(&pdev->dev.kobj,
						 &vt8231_group_temps[i]);
			अगर (err)
				जाओ निकास_हटाओ_files;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++) अणु
		अगर (ISVOLT(i, data->uch_config)) अणु
			err = sysfs_create_group(&pdev->dev.kobj,
						 &vt8231_group_volts[i]);
			अगर (err)
				जाओ निकास_हटाओ_files;
		पूर्ण
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण
	वापस 0;

निकास_हटाओ_files:
	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group_volts[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group_temps[i]);

	sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group);
	वापस err;
पूर्ण

अटल पूर्णांक vt8231_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8231_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_volts); i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group_volts[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vt8231_group_temps); i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group_temps[i]);

	sysfs_हटाओ_group(&pdev->dev.kobj, &vt8231_group);

	वापस 0;
पूर्ण

अटल व्योम vt8231_init_device(काष्ठा vt8231_data *data)
अणु
	vt8231_ग_लिखो_value(data, VT8231_REG_TEMP1_CONFIG, 0);
	vt8231_ग_लिखो_value(data, VT8231_REG_TEMP2_CONFIG, 0);
पूर्ण

अटल काष्ठा vt8231_data *vt8231_update_device(काष्ठा device *dev)
अणु
	काष्ठा vt8231_data *data = dev_get_drvdata(dev);
	पूर्णांक i;
	u16 low;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		क्रम (i = 0; i < 6; i++) अणु
			अगर (ISVOLT(i, data->uch_config)) अणु
				data->in[i] = vt8231_पढ़ो_value(data,
						regvolt[i]);
				data->in_min[i] = vt8231_पढ़ो_value(data,
						regvolपंचांगin[i]);
				data->in_max[i] = vt8231_पढ़ो_value(data,
						regvolपंचांगax[i]);
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			data->fan[i] = vt8231_पढ़ो_value(data,
						VT8231_REG_FAN(i));
			data->fan_min[i] = vt8231_पढ़ो_value(data,
						VT8231_REG_FAN_MIN(i));
		पूर्ण

		low = vt8231_पढ़ो_value(data, VT8231_REG_TEMP_LOW01);
		low = (low >> 6) | ((low & 0x30) >> 2)
		    | (vt8231_पढ़ो_value(data, VT8231_REG_TEMP_LOW25) << 4);
		क्रम (i = 0; i < 6; i++) अणु
			अगर (ISTEMP(i, data->uch_config)) अणु
				data->temp[i] = (vt8231_पढ़ो_value(data,
						       regtemp[i]) << 2)
						| ((low >> (2 * i)) & 0x03);
				data->temp_max[i] = vt8231_पढ़ो_value(data,
						      regtempmax[i]);
				data->temp_min[i] = vt8231_पढ़ो_value(data,
						      regtempmin[i]);
			पूर्ण
		पूर्ण

		i = vt8231_पढ़ो_value(data, VT8231_REG_FANDIV);
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = i >> 6;
		data->alarms = vt8231_पढ़ो_value(data, VT8231_REG_ALARM1) |
			(vt8231_पढ़ो_value(data, VT8231_REG_ALARM2) << 8);

		/* Set alarm flags correctly */
		अगर (!data->fan[0] && data->fan_min[0])
			data->alarms |= 0x40;
		अन्यथा अगर (data->fan[0] && !data->fan_min[0])
			data->alarms &= ~0x40;

		अगर (!data->fan[1] && data->fan_min[1])
			data->alarms |= 0x80;
		अन्यथा अगर (data->fan[1] && !data->fan_min[1])
			data->alarms &= ~0x80;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल पूर्णांक vt8231_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + VT8231_EXTENT - 1,
		.name	= "vt8231",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc("vt8231", address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक vt8231_pci_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	u16 address, val;
	अगर (क्रमce_addr) अणु
		address = क्रमce_addr & 0xff00;
		dev_warn(&dev->dev, "Forcing ISA address 0x%x\n",
			 address);

		अगर (PCIBIOS_SUCCESSFUL !=
		    pci_ग_लिखो_config_word(dev, VT8231_BASE_REG, address | 1))
			वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_word(dev, VT8231_BASE_REG, &val);
	अगर (val == (u16)~0)
		वापस -ENODEV;

	address = val & ~(VT8231_EXTENT - 1);
	अगर (address == 0) अणु
		dev_err(&dev->dev, "base address not set - upgrade BIOS or use force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_word(dev, VT8231_ENABLE_REG, &val);
	अगर (val == (u16)~0)
		वापस -ENODEV;

	अगर (!(val & 0x0001)) अणु
		dev_warn(&dev->dev, "enabling sensors\n");
		अगर (PCIBIOS_SUCCESSFUL !=
			pci_ग_लिखो_config_word(dev, VT8231_ENABLE_REG,
							val | 0x0001))
			वापस -ENODEV;
	पूर्ण

	अगर (platक्रमm_driver_रेजिस्टर(&vt8231_driver))
		जाओ निकास;

	/* Sets global pdev as a side effect */
	अगर (vt8231_device_add(address))
		जाओ निकास_unरेजिस्टर;

	/*
	 * Always वापस failure here.  This is to allow other drivers to bind
	 * to this pci device.  We करोn't really want to have control over the
	 * pci device, we only wanted to पढ़ो as few रेजिस्टर values from it.
	 */

	/*
	 * We करो, however, mark ourselves as using the PCI device to stop it
	 * getting unloaded.
	 */
	s_bridge = pci_dev_get(dev);
	वापस -ENODEV;

निकास_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&vt8231_driver);
निकास:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init sm_vt8231_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&vt8231_pci_driver);
पूर्ण

अटल व्योम __निकास sm_vt8231_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vt8231_pci_driver);
	अगर (s_bridge != शून्य) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&vt8231_driver);
		pci_dev_put(s_bridge);
		s_bridge = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("Roger Lucas <vt8231@hiddenengine.co.uk>");
MODULE_DESCRIPTION("VT8231 sensors");
MODULE_LICENSE("GPL");

module_init(sm_vt8231_init);
module_निकास(sm_vt8231_निकास);
