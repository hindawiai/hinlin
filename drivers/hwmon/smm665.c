<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम SMM665 Power Controller / Monitor
 *
 * Copyright (C) 2010 Ericsson AB.
 *
 * This driver should also work क्रम SMM465, SMM764, and SMM766, but is untested
 * क्रम those chips. Only monitoring functionality is implemented.
 *
 * Datasheets:
 * http://www.summiपंचांगicro.com/prod_select/summary/SMM665/SMM665B_2089_20.pdf
 * http://www.summiपंचांगicro.com/prod_select/summary/SMM766B/SMM766B_2122.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>

/* Internal reference voltage (VREF, x 1000 */
#घोषणा SMM665_VREF_ADC_X1000	1250

/* module parameters */
अटल पूर्णांक vref = SMM665_VREF_ADC_X1000;
module_param(vref, पूर्णांक, 0);
MODULE_PARM_DESC(vref, "Reference voltage in mV");

क्रमागत chips अणु smm465, smm665, smm665c, smm764, smm766 पूर्ण;

/*
 * ADC channel addresses
 */
#घोषणा	SMM665_MISC16_ADC_DATA_A	0x00
#घोषणा	SMM665_MISC16_ADC_DATA_B	0x01
#घोषणा	SMM665_MISC16_ADC_DATA_C	0x02
#घोषणा	SMM665_MISC16_ADC_DATA_D	0x03
#घोषणा	SMM665_MISC16_ADC_DATA_E	0x04
#घोषणा	SMM665_MISC16_ADC_DATA_F	0x05
#घोषणा	SMM665_MISC16_ADC_DATA_VDD	0x06
#घोषणा	SMM665_MISC16_ADC_DATA_12V	0x07
#घोषणा	SMM665_MISC16_ADC_DATA_INT_TEMP	0x08
#घोषणा	SMM665_MISC16_ADC_DATA_AIN1	0x09
#घोषणा	SMM665_MISC16_ADC_DATA_AIN2	0x0a

/*
 * Command रेजिस्टरs
 */
#घोषणा	SMM665_MISC8_CMD_STS		0x80
#घोषणा	SMM665_MISC8_STATUS1		0x81
#घोषणा	SMM665_MISC8_STATUSS2		0x82
#घोषणा	SMM665_MISC8_IO_POLARITY	0x83
#घोषणा	SMM665_MISC8_PUP_POLARITY	0x84
#घोषणा	SMM665_MISC8_ADOC_STATUS1	0x85
#घोषणा	SMM665_MISC8_ADOC_STATUS2	0x86
#घोषणा	SMM665_MISC8_WRITE_PROT		0x87
#घोषणा	SMM665_MISC8_STS_TRACK		0x88

/*
 * Configuration रेजिस्टरs and रेजिस्टर groups
 */
#घोषणा SMM665_ADOC_ENABLE		0x0d
#घोषणा SMM665_LIMIT_BASE		0x80	/* First limit रेजिस्टर */

/*
 * Limit रेजिस्टर bit masks
 */
#घोषणा SMM665_TRIGGER_RST		0x8000
#घोषणा SMM665_TRIGGER_HEALTHY		0x4000
#घोषणा SMM665_TRIGGER_POWEROFF		0x2000
#घोषणा SMM665_TRIGGER_SHUTDOWN		0x1000
#घोषणा SMM665_ADC_MASK			0x03ff

#घोषणा smm665_is_critical(lim)	((lim) & (SMM665_TRIGGER_RST \
					| SMM665_TRIGGER_POWEROFF \
					| SMM665_TRIGGER_SHUTDOWN))
/*
 * Fault रेजिस्टर bit definitions
 * Values are merged from status रेजिस्टरs 1/2,
 * with status रेजिस्टर 1 providing the upper 8 bits.
 */
#घोषणा SMM665_FAULT_A		0x0001
#घोषणा SMM665_FAULT_B		0x0002
#घोषणा SMM665_FAULT_C		0x0004
#घोषणा SMM665_FAULT_D		0x0008
#घोषणा SMM665_FAULT_E		0x0010
#घोषणा SMM665_FAULT_F		0x0020
#घोषणा SMM665_FAULT_VDD	0x0040
#घोषणा SMM665_FAULT_12V	0x0080
#घोषणा SMM665_FAULT_TEMP	0x0100
#घोषणा SMM665_FAULT_AIN1	0x0200
#घोषणा SMM665_FAULT_AIN2	0x0400

/*
 * I2C Register addresses
 *
 * The configuration रेजिस्टर needs to be the configured base रेजिस्टर.
 * The command/status रेजिस्टर address is derived from it.
 */
#घोषणा SMM665_REGMASK		0x78
#घोषणा SMM665_CMDREG_BASE	0x48
#घोषणा SMM665_CONFREG_BASE	0x50

/*
 *  Equations given by chip manufacturer to calculate voltage/temperature values
 *  vref = Reference voltage on VREF_ADC pin (module parameter)
 *  adc  = 10bit ADC value पढ़ो back from रेजिस्टरs
 */

/* Voltage A-F and VDD */
#घोषणा SMM665_VMON_ADC_TO_VOLTS(adc)  ((adc) * vref / 256)

/* Voltage 12VIN */
#घोषणा SMM665_12VIN_ADC_TO_VOLTS(adc) ((adc) * vref * 3 / 256)

/* Voltage AIN1, AIN2 */
#घोषणा SMM665_AIN_ADC_TO_VOLTS(adc)   ((adc) * vref / 512)

/* Temp Sensor */
#घोषणा SMM665_TEMP_ADC_TO_CELSIUS(adc) (((adc) <= 511) ?		   \
					 ((पूर्णांक)(adc) * 1000 / 4) :	   \
					 (((पूर्णांक)(adc) - 0x400) * 1000 / 4))

#घोषणा SMM665_NUM_ADC		11

/*
 * Chip dependent ADC conversion समय, in uS
 */
#घोषणा SMM665_ADC_WAIT_SMM665	70
#घोषणा SMM665_ADC_WAIT_SMM766	185

काष्ठा smm665_data अणु
	क्रमागत chips type;
	पूर्णांक conversion_समय;		/* ADC conversion समय */
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */
	u16 adc[SMM665_NUM_ADC];	/* adc values (raw) */
	u16 faults;			/* fault status */
	/* The following values are in mV */
	पूर्णांक critical_min_limit[SMM665_NUM_ADC];
	पूर्णांक alarm_min_limit[SMM665_NUM_ADC];
	पूर्णांक critical_max_limit[SMM665_NUM_ADC];
	पूर्णांक alarm_max_limit[SMM665_NUM_ADC];
	काष्ठा i2c_client *cmdreg;
पूर्ण;

/*
 * smm665_पढ़ो16()
 *
 * Read 16 bit value from <reg>, <reg+1>. Upper 8 bits are in <reg>.
 */
अटल पूर्णांक smm665_पढ़ो16(काष्ठा i2c_client *client, पूर्णांक reg)
अणु
	पूर्णांक rv, val;

	rv = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (rv < 0)
		वापस rv;
	val = rv << 8;
	rv = i2c_smbus_पढ़ो_byte_data(client, reg + 1);
	अगर (rv < 0)
		वापस rv;
	val |= rv;
	वापस val;
पूर्ण

/*
 * Read adc value.
 */
अटल पूर्णांक smm665_पढ़ो_adc(काष्ठा smm665_data *data, पूर्णांक adc)
अणु
	काष्ठा i2c_client *client = data->cmdreg;
	पूर्णांक rv;
	पूर्णांक radc;

	/*
	 * Algorithm क्रम पढ़ोing ADC, per SMM665 datasheet
	 *
	 *  अणु[S][addr][W][Ack]पूर्ण अणु[offset][Ack]पूर्ण अणु[S][addr][R][Nack]पूर्ण
	 * [रुको conversion समय]
	 *  अणु[S][addr][R][Ack]पूर्ण अणु[datahi][Ack]पूर्ण अणु[datalo][Ack][P]पूर्ण
	 *
	 * To implement the first part of this exchange,
	 * करो a full पढ़ो transaction and expect a failure/Nack.
	 * This sets up the address poपूर्णांकer on the SMM665
	 * and starts the ADC conversion.
	 * Then करो a two-byte पढ़ो transaction.
	 */
	rv = i2c_smbus_पढ़ो_byte_data(client, adc << 3);
	अगर (rv != -ENXIO) अणु
		/*
		 * We expect ENXIO to reflect NACK
		 * (per Documentation/i2c/fault-codes.rst).
		 * Everything अन्यथा is an error.
		 */
		dev_dbg(&client->dev,
			"Unexpected return code %d when setting ADC index", rv);
		वापस (rv < 0) ? rv : -EIO;
	पूर्ण

	udelay(data->conversion_समय);

	/*
	 * Now पढ़ो two bytes.
	 *
	 * Neither i2c_smbus_पढ़ो_byte() nor
	 * i2c_smbus_पढ़ो_block_data() worked here,
	 * so use i2c_smbus_पढ़ो_word_swapped() instead.
	 * We could also try to use i2c_master_recv(),
	 * but that is not always supported.
	 */
	rv = i2c_smbus_पढ़ो_word_swapped(client, 0);
	अगर (rv < 0) अणु
		dev_dbg(&client->dev, "Failed to read ADC value: error %d", rv);
		वापस rv;
	पूर्ण
	/*
	 * Validate/verअगरy पढ़ोback adc channel (in bit 11..14).
	 */
	radc = (rv >> 11) & 0x0f;
	अगर (radc != adc) अणु
		dev_dbg(&client->dev, "Unexpected RADC: Expected %d got %d",
			adc, radc);
		वापस -EIO;
	पूर्ण

	वापस rv & SMM665_ADC_MASK;
पूर्ण

अटल काष्ठा smm665_data *smm665_update_device(काष्ठा device *dev)
अणु
	काष्ठा smm665_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा smm665_data *ret = data;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		पूर्णांक i, val;

		/*
		 * पढ़ो status रेजिस्टरs
		 */
		val = smm665_पढ़ो16(client, SMM665_MISC8_STATUS1);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->faults = val;

		/* Read adc रेजिस्टरs */
		क्रम (i = 0; i < SMM665_NUM_ADC; i++) अणु
			val = smm665_पढ़ो_adc(data, i);
			अगर (unlikely(val < 0)) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->adc[i] = val;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

/* Return converted value from given adc */
अटल पूर्णांक smm665_convert(u16 adcval, पूर्णांक index)
अणु
	पूर्णांक val = 0;

	चयन (index) अणु
	हाल SMM665_MISC16_ADC_DATA_12V:
		val = SMM665_12VIN_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		अवरोध;

	हाल SMM665_MISC16_ADC_DATA_VDD:
	हाल SMM665_MISC16_ADC_DATA_A:
	हाल SMM665_MISC16_ADC_DATA_B:
	हाल SMM665_MISC16_ADC_DATA_C:
	हाल SMM665_MISC16_ADC_DATA_D:
	हाल SMM665_MISC16_ADC_DATA_E:
	हाल SMM665_MISC16_ADC_DATA_F:
		val = SMM665_VMON_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		अवरोध;

	हाल SMM665_MISC16_ADC_DATA_AIN1:
	हाल SMM665_MISC16_ADC_DATA_AIN2:
		val = SMM665_AIN_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		अवरोध;

	हाल SMM665_MISC16_ADC_DATA_INT_TEMP:
		val = SMM665_TEMP_ADC_TO_CELSIUS(adcval & SMM665_ADC_MASK);
		अवरोध;

	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक smm665_get_min(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा smm665_data *data = dev_get_drvdata(dev);

	वापस data->alarm_min_limit[index];
पूर्ण

अटल पूर्णांक smm665_get_max(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा smm665_data *data = dev_get_drvdata(dev);

	वापस data->alarm_max_limit[index];
पूर्ण

अटल पूर्णांक smm665_get_lcrit(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा smm665_data *data = dev_get_drvdata(dev);

	वापस data->critical_min_limit[index];
पूर्ण

अटल पूर्णांक smm665_get_crit(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा smm665_data *data = dev_get_drvdata(dev);

	वापस data->critical_max_limit[index];
पूर्ण

अटल sमाप_प्रकार smm665_show_crit_alarm(काष्ठा device *dev,
				      काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा smm665_data *data = smm665_update_device(dev);
	पूर्णांक val = 0;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (data->faults & (1 << attr->index))
		val = 1;

	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार smm665_show_input(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा smm665_data *data = smm665_update_device(dev);
	पूर्णांक adc = attr->index;
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = smm665_convert(data->adc[adc], adc);
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

#घोषणा SMM665_SHOW(what) \
अटल sमाप_प्रकार smm665_show_##what(काष्ठा device *dev, \
				    काष्ठा device_attribute *da, अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	स्थिर पूर्णांक val = smm665_get_##what(dev, attr->index); \
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val); \
पूर्ण

SMM665_SHOW(min);
SMM665_SHOW(max);
SMM665_SHOW(lcrit);
SMM665_SHOW(crit);

/*
 * These macros are used below in स्थिरructing device attribute objects
 * क्रम use with sysfs_create_group() to make a sysfs device file
 * क्रम each रेजिस्टर.
 */

#घोषणा SMM665_ATTR(name, type, cmd_idx) \
	अटल SENSOR_DEVICE_ATTR(name##_##type, S_IRUGO, \
				  smm665_show_##type, शून्य, cmd_idx)

/* Conकाष्ठा a sensor_device_attribute काष्ठाure क्रम each रेजिस्टर */

/* Input voltages */
SMM665_ATTR(in1, input, SMM665_MISC16_ADC_DATA_12V);
SMM665_ATTR(in2, input, SMM665_MISC16_ADC_DATA_VDD);
SMM665_ATTR(in3, input, SMM665_MISC16_ADC_DATA_A);
SMM665_ATTR(in4, input, SMM665_MISC16_ADC_DATA_B);
SMM665_ATTR(in5, input, SMM665_MISC16_ADC_DATA_C);
SMM665_ATTR(in6, input, SMM665_MISC16_ADC_DATA_D);
SMM665_ATTR(in7, input, SMM665_MISC16_ADC_DATA_E);
SMM665_ATTR(in8, input, SMM665_MISC16_ADC_DATA_F);
SMM665_ATTR(in9, input, SMM665_MISC16_ADC_DATA_AIN1);
SMM665_ATTR(in10, input, SMM665_MISC16_ADC_DATA_AIN2);

/* Input voltages min */
SMM665_ATTR(in1, min, SMM665_MISC16_ADC_DATA_12V);
SMM665_ATTR(in2, min, SMM665_MISC16_ADC_DATA_VDD);
SMM665_ATTR(in3, min, SMM665_MISC16_ADC_DATA_A);
SMM665_ATTR(in4, min, SMM665_MISC16_ADC_DATA_B);
SMM665_ATTR(in5, min, SMM665_MISC16_ADC_DATA_C);
SMM665_ATTR(in6, min, SMM665_MISC16_ADC_DATA_D);
SMM665_ATTR(in7, min, SMM665_MISC16_ADC_DATA_E);
SMM665_ATTR(in8, min, SMM665_MISC16_ADC_DATA_F);
SMM665_ATTR(in9, min, SMM665_MISC16_ADC_DATA_AIN1);
SMM665_ATTR(in10, min, SMM665_MISC16_ADC_DATA_AIN2);

/* Input voltages max */
SMM665_ATTR(in1, max, SMM665_MISC16_ADC_DATA_12V);
SMM665_ATTR(in2, max, SMM665_MISC16_ADC_DATA_VDD);
SMM665_ATTR(in3, max, SMM665_MISC16_ADC_DATA_A);
SMM665_ATTR(in4, max, SMM665_MISC16_ADC_DATA_B);
SMM665_ATTR(in5, max, SMM665_MISC16_ADC_DATA_C);
SMM665_ATTR(in6, max, SMM665_MISC16_ADC_DATA_D);
SMM665_ATTR(in7, max, SMM665_MISC16_ADC_DATA_E);
SMM665_ATTR(in8, max, SMM665_MISC16_ADC_DATA_F);
SMM665_ATTR(in9, max, SMM665_MISC16_ADC_DATA_AIN1);
SMM665_ATTR(in10, max, SMM665_MISC16_ADC_DATA_AIN2);

/* Input voltages lcrit */
SMM665_ATTR(in1, lcrit, SMM665_MISC16_ADC_DATA_12V);
SMM665_ATTR(in2, lcrit, SMM665_MISC16_ADC_DATA_VDD);
SMM665_ATTR(in3, lcrit, SMM665_MISC16_ADC_DATA_A);
SMM665_ATTR(in4, lcrit, SMM665_MISC16_ADC_DATA_B);
SMM665_ATTR(in5, lcrit, SMM665_MISC16_ADC_DATA_C);
SMM665_ATTR(in6, lcrit, SMM665_MISC16_ADC_DATA_D);
SMM665_ATTR(in7, lcrit, SMM665_MISC16_ADC_DATA_E);
SMM665_ATTR(in8, lcrit, SMM665_MISC16_ADC_DATA_F);
SMM665_ATTR(in9, lcrit, SMM665_MISC16_ADC_DATA_AIN1);
SMM665_ATTR(in10, lcrit, SMM665_MISC16_ADC_DATA_AIN2);

/* Input voltages crit */
SMM665_ATTR(in1, crit, SMM665_MISC16_ADC_DATA_12V);
SMM665_ATTR(in2, crit, SMM665_MISC16_ADC_DATA_VDD);
SMM665_ATTR(in3, crit, SMM665_MISC16_ADC_DATA_A);
SMM665_ATTR(in4, crit, SMM665_MISC16_ADC_DATA_B);
SMM665_ATTR(in5, crit, SMM665_MISC16_ADC_DATA_C);
SMM665_ATTR(in6, crit, SMM665_MISC16_ADC_DATA_D);
SMM665_ATTR(in7, crit, SMM665_MISC16_ADC_DATA_E);
SMM665_ATTR(in8, crit, SMM665_MISC16_ADC_DATA_F);
SMM665_ATTR(in9, crit, SMM665_MISC16_ADC_DATA_AIN1);
SMM665_ATTR(in10, crit, SMM665_MISC16_ADC_DATA_AIN2);

/* critical alarms */
SMM665_ATTR(in1, crit_alarm, SMM665_FAULT_12V);
SMM665_ATTR(in2, crit_alarm, SMM665_FAULT_VDD);
SMM665_ATTR(in3, crit_alarm, SMM665_FAULT_A);
SMM665_ATTR(in4, crit_alarm, SMM665_FAULT_B);
SMM665_ATTR(in5, crit_alarm, SMM665_FAULT_C);
SMM665_ATTR(in6, crit_alarm, SMM665_FAULT_D);
SMM665_ATTR(in7, crit_alarm, SMM665_FAULT_E);
SMM665_ATTR(in8, crit_alarm, SMM665_FAULT_F);
SMM665_ATTR(in9, crit_alarm, SMM665_FAULT_AIN1);
SMM665_ATTR(in10, crit_alarm, SMM665_FAULT_AIN2);

/* Temperature */
SMM665_ATTR(temp1, input, SMM665_MISC16_ADC_DATA_INT_TEMP);
SMM665_ATTR(temp1, min, SMM665_MISC16_ADC_DATA_INT_TEMP);
SMM665_ATTR(temp1, max, SMM665_MISC16_ADC_DATA_INT_TEMP);
SMM665_ATTR(temp1, lcrit, SMM665_MISC16_ADC_DATA_INT_TEMP);
SMM665_ATTR(temp1, crit, SMM665_MISC16_ADC_DATA_INT_TEMP);
SMM665_ATTR(temp1, crit_alarm, SMM665_FAULT_TEMP);

/*
 * Finally, स्थिरruct an array of poपूर्णांकers to members of the above objects,
 * as required क्रम sysfs_create_group()
 */
अटल काष्ठा attribute *smm665_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_lcrit.dev_attr.attr,
	&sensor_dev_attr_in1_crit.dev_attr.attr,
	&sensor_dev_attr_in1_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_lcrit.dev_attr.attr,
	&sensor_dev_attr_in2_crit.dev_attr.attr,
	&sensor_dev_attr_in2_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_lcrit.dev_attr.attr,
	&sensor_dev_attr_in3_crit.dev_attr.attr,
	&sensor_dev_attr_in3_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_lcrit.dev_attr.attr,
	&sensor_dev_attr_in4_crit.dev_attr.attr,
	&sensor_dev_attr_in4_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_lcrit.dev_attr.attr,
	&sensor_dev_attr_in5_crit.dev_attr.attr,
	&sensor_dev_attr_in5_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_lcrit.dev_attr.attr,
	&sensor_dev_attr_in6_crit.dev_attr.attr,
	&sensor_dev_attr_in6_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_lcrit.dev_attr.attr,
	&sensor_dev_attr_in7_crit.dev_attr.attr,
	&sensor_dev_attr_in7_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in8_min.dev_attr.attr,
	&sensor_dev_attr_in8_max.dev_attr.attr,
	&sensor_dev_attr_in8_lcrit.dev_attr.attr,
	&sensor_dev_attr_in8_crit.dev_attr.attr,
	&sensor_dev_attr_in8_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in9_min.dev_attr.attr,
	&sensor_dev_attr_in9_max.dev_attr.attr,
	&sensor_dev_attr_in9_lcrit.dev_attr.attr,
	&sensor_dev_attr_in9_crit.dev_attr.attr,
	&sensor_dev_attr_in9_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in10_min.dev_attr.attr,
	&sensor_dev_attr_in10_max.dev_attr.attr,
	&sensor_dev_attr_in10_lcrit.dev_attr.attr,
	&sensor_dev_attr_in10_crit.dev_attr.attr,
	&sensor_dev_attr_in10_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_lcrit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,

	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(smm665);

अटल स्थिर काष्ठा i2c_device_id smm665_id[];

अटल पूर्णांक smm665_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा smm665_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक i, ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	अगर (i2c_smbus_पढ़ो_byte_data(client, SMM665_ADOC_ENABLE) < 0)
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	data->client = client;
	data->type = i2c_match_id(smm665_id, client)->driver_data;
	data->cmdreg = i2c_new_dummy_device(adapter, (client->addr & ~SMM665_REGMASK)
				     | SMM665_CMDREG_BASE);
	अगर (IS_ERR(data->cmdreg))
		वापस PTR_ERR(data->cmdreg);

	चयन (data->type) अणु
	हाल smm465:
	हाल smm665:
		data->conversion_समय = SMM665_ADC_WAIT_SMM665;
		अवरोध;
	हाल smm665c:
	हाल smm764:
	हाल smm766:
		data->conversion_समय = SMM665_ADC_WAIT_SMM766;
		अवरोध;
	पूर्ण

	ret = -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(data->cmdreg, SMM665_MISC8_CMD_STS) < 0)
		जाओ out_unरेजिस्टर;

	/*
	 * Read limits.
	 *
	 * Limit रेजिस्टरs start with रेजिस्टर SMM665_LIMIT_BASE.
	 * Each channel uses 8 रेजिस्टरs, providing four limit values
	 * per channel. Each limit value requires two रेजिस्टरs, with the
	 * high byte in the first रेजिस्टर and the low byte in the second
	 * रेजिस्टर. The first two limits are under limit values, followed
	 * by two over limit values.
	 *
	 * Limit रेजिस्टर order matches the ADC रेजिस्टर order, so we use
	 * ADC रेजिस्टर defines throughout the code to index limit रेजिस्टरs.
	 *
	 * We save the first retrieved value both as "critical" and "alarm"
	 * value. The second value overग_लिखोs either the critical or the
	 * alarm value, depending on its configuration. This ensures that both
	 * critical and alarm values are initialized, even अगर both रेजिस्टरs are
	 * configured as critical or non-critical.
	 */
	क्रम (i = 0; i < SMM665_NUM_ADC; i++) अणु
		पूर्णांक val;

		val = smm665_पढ़ो16(client, SMM665_LIMIT_BASE + i * 8);
		अगर (unlikely(val < 0))
			जाओ out_unरेजिस्टर;
		data->critical_min_limit[i] = data->alarm_min_limit[i]
		  = smm665_convert(val, i);
		val = smm665_पढ़ो16(client, SMM665_LIMIT_BASE + i * 8 + 2);
		अगर (unlikely(val < 0))
			जाओ out_unरेजिस्टर;
		अगर (smm665_is_critical(val))
			data->critical_min_limit[i] = smm665_convert(val, i);
		अन्यथा
			data->alarm_min_limit[i] = smm665_convert(val, i);
		val = smm665_पढ़ो16(client, SMM665_LIMIT_BASE + i * 8 + 4);
		अगर (unlikely(val < 0))
			जाओ out_unरेजिस्टर;
		data->critical_max_limit[i] = data->alarm_max_limit[i]
		  = smm665_convert(val, i);
		val = smm665_पढ़ो16(client, SMM665_LIMIT_BASE + i * 8 + 6);
		अगर (unlikely(val < 0))
			जाओ out_unरेजिस्टर;
		अगर (smm665_is_critical(val))
			data->critical_max_limit[i] = smm665_convert(val, i);
		अन्यथा
			data->alarm_max_limit[i] = smm665_convert(val, i);
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   smm665_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		ret = PTR_ERR(hwmon_dev);
		जाओ out_unरेजिस्टर;
	पूर्ण

	वापस 0;

out_unरेजिस्टर:
	i2c_unरेजिस्टर_device(data->cmdreg);
	वापस ret;
पूर्ण

अटल पूर्णांक smm665_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा smm665_data *data = i2c_get_clientdata(client);

	i2c_unरेजिस्टर_device(data->cmdreg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id smm665_id[] = अणु
	अणु"smm465", smm465पूर्ण,
	अणु"smm665", smm665पूर्ण,
	अणु"smm665c", smm665cपूर्ण,
	अणु"smm764", smm764पूर्ण,
	अणु"smm766", smm766पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, smm665_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver smm665_driver = अणु
	.driver = अणु
		   .name = "smm665",
		   पूर्ण,
	.probe_new = smm665_probe,
	.हटाओ = smm665_हटाओ,
	.id_table = smm665_id,
पूर्ण;

module_i2c_driver(smm665_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("SMM665 driver");
MODULE_LICENSE("GPL");
