<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 1-Wire implementation क्रम the ds2438 chip
 *
 * Copyright (c) 2017 Mariusz Bialonczyk <manio@skyboo.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS2438		0x26

#घोषणा W1_DS2438_RETRIES		3

/* Memory commands */
#घोषणा W1_DS2438_READ_SCRATCH		0xBE
#घोषणा W1_DS2438_WRITE_SCRATCH		0x4E
#घोषणा W1_DS2438_COPY_SCRATCH		0x48
#घोषणा W1_DS2438_RECALL_MEMORY		0xB8
/* Register commands */
#घोषणा W1_DS2438_CONVERT_TEMP		0x44
#घोषणा W1_DS2438_CONVERT_VOLTAGE	0xB4

#घोषणा DS2438_PAGE_SIZE		8
#घोषणा DS2438_ADC_INPUT_VAD		0
#घोषणा DS2438_ADC_INPUT_VDD		1
#घोषणा DS2438_MAX_CONVERSION_TIME	10		/* ms */

/* Page #0 definitions */
#घोषणा DS2438_STATUS_REG		0x00		/* Status/Configuration Register */
#घोषणा DS2438_STATUS_IAD		(1 << 0)	/* Current A/D Control Bit */
#घोषणा DS2438_STATUS_CA		(1 << 1)	/* Current Accumulator Configuration */
#घोषणा DS2438_STATUS_EE		(1 << 2)	/* Current Accumulator Shaकरोw Selector bit */
#घोषणा DS2438_STATUS_AD		(1 << 3)	/* Voltage A/D Input Select Bit */
#घोषणा DS2438_STATUS_TB		(1 << 4)	/* Temperature Busy Flag */
#घोषणा DS2438_STATUS_NVB		(1 << 5)	/* Nonअस्थिर Memory Busy Flag */
#घोषणा DS2438_STATUS_ADB		(1 << 6)	/* A/D Converter Busy Flag */

#घोषणा DS2438_TEMP_LSB			0x01
#घोषणा DS2438_TEMP_MSB			0x02
#घोषणा DS2438_VOLTAGE_LSB		0x03
#घोषणा DS2438_VOLTAGE_MSB		0x04
#घोषणा DS2438_CURRENT_LSB		0x05
#घोषणा DS2438_CURRENT_MSB		0x06
#घोषणा DS2438_THRESHOLD		0x07

अटल पूर्णांक w1_ds2438_get_page(काष्ठा w1_slave *sl, पूर्णांक pageno, u8 *buf)
अणु
	अचिन्हित पूर्णांक retries = W1_DS2438_RETRIES;
	u8 w1_buf[2];
	u8 crc;
	माप_प्रकार count;

	जबतक (retries--) अणु
		crc = 0;

		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_buf[0] = W1_DS2438_RECALL_MEMORY;
		w1_buf[1] = 0x00;
		w1_ग_लिखो_block(sl->master, w1_buf, 2);

		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_buf[0] = W1_DS2438_READ_SCRATCH;
		w1_buf[1] = 0x00;
		w1_ग_लिखो_block(sl->master, w1_buf, 2);

		count = w1_पढ़ो_block(sl->master, buf, DS2438_PAGE_SIZE + 1);
		अगर (count == DS2438_PAGE_SIZE + 1) अणु
			crc = w1_calc_crc8(buf, DS2438_PAGE_SIZE);

			/* check क्रम correct CRC */
			अगर ((u8)buf[DS2438_PAGE_SIZE] == crc)
				वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक w1_ds2438_get_temperature(काष्ठा w1_slave *sl, पूर्णांक16_t *temperature)
अणु
	अचिन्हित पूर्णांक retries = W1_DS2438_RETRIES;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*क्रम CRC*/];
	अचिन्हित पूर्णांक पंचांग = DS2438_MAX_CONVERSION_TIME;
	अचिन्हित दीर्घ sleep_rem;
	पूर्णांक ret;

	mutex_lock(&sl->master->bus_mutex);

	जबतक (retries--) अणु
		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_ग_लिखो_8(sl->master, W1_DS2438_CONVERT_TEMP);

		mutex_unlock(&sl->master->bus_mutex);
		sleep_rem = msleep_पूर्णांकerruptible(पंचांग);
		अगर (sleep_rem != 0) अणु
			ret = -1;
			जाओ post_unlock;
		पूर्ण

		अगर (mutex_lock_पूर्णांकerruptible(&sl->master->bus_mutex) != 0) अणु
			ret = -1;
			जाओ post_unlock;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (w1_ds2438_get_page(sl, 0, w1_buf) == 0) अणु
		*temperature = (((पूर्णांक16_t) w1_buf[DS2438_TEMP_MSB]) << 8) | ((uपूर्णांक16_t) w1_buf[DS2438_TEMP_LSB]);
		ret = 0;
	पूर्ण अन्यथा
		ret = -1;

	mutex_unlock(&sl->master->bus_mutex);

post_unlock:
	वापस ret;
पूर्ण

अटल पूर्णांक w1_ds2438_change_config_bit(काष्ठा w1_slave *sl, u8 mask, u8 value)
अणु
	अचिन्हित पूर्णांक retries = W1_DS2438_RETRIES;
	u8 w1_buf[3];
	u8 status;
	पूर्णांक perक्रमm_ग_लिखो = 0;

	जबतक (retries--) अणु
		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_buf[0] = W1_DS2438_RECALL_MEMORY;
		w1_buf[1] = 0x00;
		w1_ग_लिखो_block(sl->master, w1_buf, 2);

		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_buf[0] = W1_DS2438_READ_SCRATCH;
		w1_buf[1] = 0x00;
		w1_ग_लिखो_block(sl->master, w1_buf, 2);

		/* पढ़ोing one byte of result */
		status = w1_पढ़ो_8(sl->master);

		/* अगर bit0=1, set a value to a mask क्रम easy compare */
		अगर (value)
			value = mask;

		अगर ((status & mask) == value)
			वापस 0;	/* alपढ़ोy set as requested */
		अन्यथा अणु
			/* changing bit */
			status ^= mask;
			perक्रमm_ग_लिखो = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (perक्रमm_ग_लिखो) अणु
		retries = W1_DS2438_RETRIES;
		जबतक (retries--) अणु
			अगर (w1_reset_select_slave(sl))
				जारी;
			w1_buf[0] = W1_DS2438_WRITE_SCRATCH;
			w1_buf[1] = 0x00;
			w1_buf[2] = status;
			w1_ग_लिखो_block(sl->master, w1_buf, 3);

			अगर (w1_reset_select_slave(sl))
				जारी;
			w1_buf[0] = W1_DS2438_COPY_SCRATCH;
			w1_buf[1] = 0x00;
			w1_ग_लिखो_block(sl->master, w1_buf, 2);

			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक w1_ds2438_get_voltage(काष्ठा w1_slave *sl,
				 पूर्णांक adc_input, uपूर्णांक16_t *voltage)
अणु
	अचिन्हित पूर्णांक retries = W1_DS2438_RETRIES;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*क्रम CRC*/];
	अचिन्हित पूर्णांक पंचांग = DS2438_MAX_CONVERSION_TIME;
	अचिन्हित दीर्घ sleep_rem;
	पूर्णांक ret;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_ds2438_change_config_bit(sl, DS2438_STATUS_AD, adc_input)) अणु
		ret = -1;
		जाओ pre_unlock;
	पूर्ण

	जबतक (retries--) अणु
		अगर (w1_reset_select_slave(sl))
			जारी;
		w1_ग_लिखो_8(sl->master, W1_DS2438_CONVERT_VOLTAGE);

		mutex_unlock(&sl->master->bus_mutex);
		sleep_rem = msleep_पूर्णांकerruptible(पंचांग);
		अगर (sleep_rem != 0) अणु
			ret = -1;
			जाओ post_unlock;
		पूर्ण

		अगर (mutex_lock_पूर्णांकerruptible(&sl->master->bus_mutex) != 0) अणु
			ret = -1;
			जाओ post_unlock;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (w1_ds2438_get_page(sl, 0, w1_buf) == 0) अणु
		*voltage = (((uपूर्णांक16_t) w1_buf[DS2438_VOLTAGE_MSB]) << 8) | ((uपूर्णांक16_t) w1_buf[DS2438_VOLTAGE_LSB]);
		ret = 0;
	पूर्ण अन्यथा
		ret = -1;

pre_unlock:
	mutex_unlock(&sl->master->bus_mutex);

post_unlock:
	वापस ret;
पूर्ण

अटल पूर्णांक w1_ds2438_get_current(काष्ठा w1_slave *sl, पूर्णांक16_t *voltage)
अणु
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*क्रम CRC*/];
	पूर्णांक ret;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_ds2438_get_page(sl, 0, w1_buf) == 0) अणु
		/* The voltage measured across current sense resistor RSENS. */
		*voltage = (((पूर्णांक16_t) w1_buf[DS2438_CURRENT_MSB]) << 8) | ((पूर्णांक16_t) w1_buf[DS2438_CURRENT_LSB]);
		ret = 0;
	पूर्ण अन्यथा
		ret = -1;

	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iad_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			 loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;

	अगर (count != 1 || off != 0)
		वापस -EFAULT;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_ds2438_change_config_bit(sl, DS2438_STATUS_IAD, *buf & 0x01) == 0)
		ret = 1;
	अन्यथा
		ret = -EIO;

	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iad_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;
	पूर्णांक16_t voltage;

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	अगर (w1_ds2438_get_current(sl, &voltage) == 0) अणु
		ret = snम_लिखो(buf, count, "%i\n", voltage);
	पूर्ण अन्यथा
		ret = -EIO;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार page0_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			  loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*क्रम CRC*/];

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	/* Read no more than page0 size */
	अगर (count > DS2438_PAGE_SIZE)
		count = DS2438_PAGE_SIZE;

	अगर (w1_ds2438_get_page(sl, 0, w1_buf) == 0) अणु
		स_नकल(buf, &w1_buf, count);
		ret = count;
	पूर्ण अन्यथा
		ret = -EIO;

	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temperature_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;
	पूर्णांक16_t temp;

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	अगर (w1_ds2438_get_temperature(sl, &temp) == 0) अणु
		ret = snम_लिखो(buf, count, "%i\n", temp);
	पूर्ण अन्यथा
		ret = -EIO;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vad_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;
	uपूर्णांक16_t voltage;

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	अगर (w1_ds2438_get_voltage(sl, DS2438_ADC_INPUT_VAD, &voltage) == 0) अणु
		ret = snम_लिखो(buf, count, "%u\n", voltage);
	पूर्ण अन्यथा
		ret = -EIO;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vdd_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			loff_t off, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);
	पूर्णांक ret;
	uपूर्णांक16_t voltage;

	अगर (off != 0)
		वापस 0;
	अगर (!buf)
		वापस -EINVAL;

	अगर (w1_ds2438_get_voltage(sl, DS2438_ADC_INPUT_VDD, &voltage) == 0) अणु
		ret = snम_लिखो(buf, count, "%u\n", voltage);
	पूर्ण अन्यथा
		ret = -EIO;

	वापस ret;
पूर्ण

अटल BIN_ATTR(iad, S_IRUGO | S_IWUSR | S_IWGRP, iad_पढ़ो, iad_ग_लिखो, 0);
अटल BIN_ATTR_RO(page0, DS2438_PAGE_SIZE);
अटल BIN_ATTR_RO(temperature, 0/* real length varies */);
अटल BIN_ATTR_RO(vad, 0/* real length varies */);
अटल BIN_ATTR_RO(vdd, 0/* real length varies */);

अटल काष्ठा bin_attribute *w1_ds2438_bin_attrs[] = अणु
	&bin_attr_iad,
	&bin_attr_page0,
	&bin_attr_temperature,
	&bin_attr_vad,
	&bin_attr_vdd,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_ds2438_group = अणु
	.bin_attrs = w1_ds2438_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_ds2438_groups[] = अणु
	&w1_ds2438_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_ds2438_fops = अणु
	.groups		= w1_ds2438_groups,
पूर्ण;

अटल काष्ठा w1_family w1_ds2438_family = अणु
	.fid = W1_FAMILY_DS2438,
	.fops = &w1_ds2438_fops,
पूर्ण;
module_w1_family(w1_ds2438_family);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mariusz Bialonczyk <manio@skyboo.net>");
MODULE_DESCRIPTION("1-wire driver for Maxim/Dallas DS2438 Smart Battery Monitor");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2438));
