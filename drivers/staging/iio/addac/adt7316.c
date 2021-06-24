<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADT7316 digital temperature sensor driver supporting ADT7316/7/8 ADT7516/7/9
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/irq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/sysfs.h>
#समावेश "adt7316.h"

/*
 * ADT7316 रेजिस्टरs definition
 */
#घोषणा ADT7316_INT_STAT1		0x0
#घोषणा ADT7316_INT_STAT2		0x1
#घोषणा ADT7316_LSB_IN_TEMP_VDD		0x3
#घोषणा ADT7316_LSB_IN_TEMP_MASK	0x3
#घोषणा ADT7316_LSB_VDD_MASK		0xC
#घोषणा ADT7316_LSB_VDD_OFFSET		2
#घोषणा ADT7316_LSB_EX_TEMP_AIN		0x4
#घोषणा ADT7316_LSB_EX_TEMP_MASK	0x3
#घोषणा ADT7516_LSB_AIN_SHIFT		2
#घोषणा ADT7316_AD_MSB_DATA_BASE        0x6
#घोषणा ADT7316_AD_MSB_DATA_REGS        3
#घोषणा ADT7516_AD_MSB_DATA_REGS        6
#घोषणा ADT7316_MSB_VDD			0x6
#घोषणा ADT7316_MSB_IN_TEMP		0x7
#घोषणा ADT7316_MSB_EX_TEMP		0x8
#घोषणा ADT7516_MSB_AIN1		0x8
#घोषणा ADT7516_MSB_AIN2		0x9
#घोषणा ADT7516_MSB_AIN3		0xA
#घोषणा ADT7516_MSB_AIN4		0xB
#घोषणा ADT7316_DA_DATA_BASE		0x10
#घोषणा ADT7316_DA_10_BIT_LSB_SHIFT	6
#घोषणा ADT7316_DA_12_BIT_LSB_SHIFT	4
#घोषणा ADT7316_DA_MSB_DATA_REGS	4
#घोषणा ADT7316_LSB_DAC_A		0x10
#घोषणा ADT7316_MSB_DAC_A		0x11
#घोषणा ADT7316_LSB_DAC_B		0x12
#घोषणा ADT7316_MSB_DAC_B		0x13
#घोषणा ADT7316_LSB_DAC_C		0x14
#घोषणा ADT7316_MSB_DAC_C		0x15
#घोषणा ADT7316_LSB_DAC_D		0x16
#घोषणा ADT7316_MSB_DAC_D		0x17
#घोषणा ADT7316_CONFIG1			0x18
#घोषणा ADT7316_CONFIG2			0x19
#घोषणा ADT7316_CONFIG3			0x1A
#घोषणा ADT7316_DAC_CONFIG		0x1B
#घोषणा ADT7316_LDAC_CONFIG		0x1C
#घोषणा ADT7316_INT_MASK1		0x1D
#घोषणा ADT7316_INT_MASK2		0x1E
#घोषणा ADT7316_IN_TEMP_OFFSET		0x1F
#घोषणा ADT7316_EX_TEMP_OFFSET		0x20
#घोषणा ADT7316_IN_ANALOG_TEMP_OFFSET	0x21
#घोषणा ADT7316_EX_ANALOG_TEMP_OFFSET	0x22
#घोषणा ADT7316_VDD_HIGH		0x23
#घोषणा ADT7316_VDD_LOW			0x24
#घोषणा ADT7316_IN_TEMP_HIGH		0x25
#घोषणा ADT7316_IN_TEMP_LOW		0x26
#घोषणा ADT7316_EX_TEMP_HIGH		0x27
#घोषणा ADT7316_EX_TEMP_LOW		0x28
#घोषणा ADT7516_AIN2_HIGH		0x2B
#घोषणा ADT7516_AIN2_LOW		0x2C
#घोषणा ADT7516_AIN3_HIGH		0x2D
#घोषणा ADT7516_AIN3_LOW		0x2E
#घोषणा ADT7516_AIN4_HIGH		0x2F
#घोषणा ADT7516_AIN4_LOW		0x30
#घोषणा ADT7316_DEVICE_ID		0x4D
#घोषणा ADT7316_MANUFACTURE_ID		0x4E
#घोषणा ADT7316_DEVICE_REV		0x4F
#घोषणा ADT7316_SPI_LOCK_STAT		0x7F

/*
 * ADT7316 config1
 */
#घोषणा ADT7316_EN			0x1
#घोषणा ADT7516_SEL_EX_TEMP		0x4
#घोषणा ADT7516_SEL_AIN1_2_EX_TEMP_MASK	0x6
#घोषणा ADT7516_SEL_AIN3		0x8
#घोषणा ADT7316_INT_EN			0x20
#घोषणा ADT7316_INT_POLARITY		0x40
#घोषणा ADT7316_PD			0x80

/*
 * ADT7316 config2
 */
#घोषणा ADT7316_AD_SINGLE_CH_MASK	0x3
#घोषणा ADT7516_AD_SINGLE_CH_MASK	0x7
#घोषणा ADT7316_AD_SINGLE_CH_VDD	0
#घोषणा ADT7316_AD_SINGLE_CH_IN		1
#घोषणा ADT7316_AD_SINGLE_CH_EX		2
#घोषणा ADT7516_AD_SINGLE_CH_AIN1	2
#घोषणा ADT7516_AD_SINGLE_CH_AIN2	3
#घोषणा ADT7516_AD_SINGLE_CH_AIN3	4
#घोषणा ADT7516_AD_SINGLE_CH_AIN4	5
#घोषणा ADT7316_AD_SINGLE_CH_MODE	0x10
#घोषणा ADT7316_DISABLE_AVERAGING	0x20
#घोषणा ADT7316_EN_SMBUS_TIMEOUT	0x40
#घोषणा ADT7316_RESET			0x80

/*
 * ADT7316 config3
 */
#घोषणा ADT7316_ADCLK_22_5		0x1
#घोषणा ADT7316_DA_HIGH_RESOLUTION	0x2
#घोषणा ADT7316_DA_EN_VIA_DAC_LDAC	0x8
#घोषणा ADT7516_AIN_IN_VREF		0x10
#घोषणा ADT7316_EN_IN_TEMP_PROP_DACA	0x20
#घोषणा ADT7316_EN_EX_TEMP_PROP_DACB	0x40

/*
 * ADT7316 DAC config
 */
#घोषणा ADT7316_DA_2VREF_CH_MASK	0xF
#घोषणा ADT7316_DA_EN_MODE_MASK		0x30
#घोषणा ADT7316_DA_EN_MODE_SHIFT	4
#घोषणा ADT7316_DA_EN_MODE_SINGLE	0x00
#घोषणा ADT7316_DA_EN_MODE_AB_CD	0x10
#घोषणा ADT7316_DA_EN_MODE_ABCD		0x20
#घोषणा ADT7316_DA_EN_MODE_LDAC		0x30
#घोषणा ADT7316_VREF_BYPASS_DAC_AB	0x40
#घोषणा ADT7316_VREF_BYPASS_DAC_CD	0x80

/*
 * ADT7316 LDAC config
 */
#घोषणा ADT7316_LDAC_EN_DA_MASK		0xF
#घोषणा ADT7316_DAC_IN_VREF		0x10
#घोषणा ADT7516_DAC_AB_IN_VREF		0x10
#घोषणा ADT7516_DAC_CD_IN_VREF		0x20
#घोषणा ADT7516_DAC_IN_VREF_OFFSET	4
#घोषणा ADT7516_DAC_IN_VREF_MASK	0x30

/*
 * ADT7316 INT_MASK2
 */
#घोषणा ADT7316_INT_MASK2_VDD		0x10

/*
 * ADT7316 value masks
 */
#घोषणा ADT7316_VALUE_MASK		0xfff
#घोषणा ADT7316_T_VALUE_SIGN		0x400
#घोषणा ADT7316_T_VALUE_FLOAT_OFFSET	2
#घोषणा ADT7316_T_VALUE_FLOAT_MASK	0x2

/*
 * Chip ID
 */
#घोषणा ID_ADT7316		0x1
#घोषणा ID_ADT7317		0x2
#घोषणा ID_ADT7318		0x3
#घोषणा ID_ADT7516		0x11
#घोषणा ID_ADT7517		0x12
#घोषणा ID_ADT7519		0x14

#घोषणा ID_FAMILY_MASK		0xF0
#घोषणा ID_ADT73XX		0x0
#घोषणा ID_ADT75XX		0x10

/*
 * काष्ठा adt7316_chip_info - chip specअगरic inक्रमmation
 */

काष्ठा adt7316_chip_info अणु
	काष्ठा adt7316_bus	bus;
	काष्ठा gpio_desc	*ldac_pin;
	u16			पूर्णांक_mask;	/* 0x2f */
	u8			config1;
	u8			config2;
	u8			config3;
	u8			dac_config;	/* DAC config */
	u8			ldac_config;	/* LDAC config */
	u8			dac_bits;	/* 8, 10, 12 */
	u8			id;		/* chip id */
पूर्ण;

/*
 * Logic पूर्णांकerrupt mask क्रम user application to enable
 * पूर्णांकerrupts.
 */
#घोषणा ADT7316_IN_TEMP_HIGH_INT_MASK	0x1
#घोषणा ADT7316_IN_TEMP_LOW_INT_MASK	0x2
#घोषणा ADT7316_EX_TEMP_HIGH_INT_MASK	0x4
#घोषणा ADT7316_EX_TEMP_LOW_INT_MASK	0x8
#घोषणा ADT7316_EX_TEMP_FAULT_INT_MASK	0x10
#घोषणा ADT7516_AIN1_INT_MASK		0x4
#घोषणा ADT7516_AIN2_INT_MASK		0x20
#घोषणा ADT7516_AIN3_INT_MASK		0x40
#घोषणा ADT7516_AIN4_INT_MASK		0x80
#घोषणा ADT7316_VDD_INT_MASK		0x100
#घोषणा ADT7316_TEMP_INT_MASK		0x1F
#घोषणा ADT7516_AIN_INT_MASK		0xE0
#घोषणा ADT7316_TEMP_AIN_INT_MASK	\
	(ADT7316_TEMP_INT_MASK)

/*
 * काष्ठा adt7316_chip_info - chip specअगरic inक्रमmation
 */

काष्ठा adt7316_limit_regs अणु
	u16	data_high;
	u16	data_low;
पूर्ण;

अटल sमाप_प्रकार adt7316_show_enabled(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n", !!(chip->config1 & ADT7316_EN));
पूर्ण

अटल sमाप_प्रकार _adt7316_store_enabled(काष्ठा adt7316_chip_info *chip,
				      पूर्णांक enable)
अणु
	u8 config1;
	पूर्णांक ret;

	अगर (enable)
		config1 = chip->config1 | ADT7316_EN;
	अन्यथा
		config1 = chip->config1 & ~ADT7316_EN;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG1, config1);
	अगर (ret)
		वापस -EIO;

	chip->config1 = config1;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार adt7316_store_enabled(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	पूर्णांक enable;

	अगर (buf[0] == '1')
		enable = 1;
	अन्यथा
		enable = 0;

	अगर (_adt7316_store_enabled(chip, enable) < 0)
		वापस -EIO;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(enabled, 0644,
		adt7316_show_enabled,
		adt7316_store_enabled,
		0);

अटल sमाप_प्रकार adt7316_show_select_ex_temp(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
		वापस -EPERM;

	वापस प्र_लिखो(buf, "%d\n", !!(chip->config1 & ADT7516_SEL_EX_TEMP));
पूर्ण

अटल sमाप_प्रकार adt7316_store_select_ex_temp(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config1;
	पूर्णांक ret;

	अगर ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
		वापस -EPERM;

	config1 = chip->config1 & (~ADT7516_SEL_EX_TEMP);
	अगर (buf[0] == '1')
		config1 |= ADT7516_SEL_EX_TEMP;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG1, config1);
	अगर (ret)
		वापस -EIO;

	chip->config1 = config1;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(select_ex_temp, 0644,
		adt7316_show_select_ex_temp,
		adt7316_store_select_ex_temp,
		0);

अटल sमाप_प्रकार adt7316_show_mode(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (chip->config2 & ADT7316_AD_SINGLE_CH_MODE)
		वापस प्र_लिखो(buf, "single_channel\n");

	वापस प्र_लिखो(buf, "round_robin\n");
पूर्ण

अटल sमाप_प्रकार adt7316_store_mode(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config2;
	पूर्णांक ret;

	config2 = chip->config2 & (~ADT7316_AD_SINGLE_CH_MODE);
	अगर (!स_भेद(buf, "single_channel", 14))
		config2 |= ADT7316_AD_SINGLE_CH_MODE;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG2, config2);
	अगर (ret)
		वापस -EIO;

	chip->config2 = config2;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(mode, 0644,
		adt7316_show_mode,
		adt7316_store_mode,
		0);

अटल sमाप_प्रकार adt7316_show_all_modes(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "single_channel\nround_robin\n");
पूर्ण

अटल IIO_DEVICE_ATTR(all_modes, 0444, adt7316_show_all_modes, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_ad_channel(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (!(chip->config2 & ADT7316_AD_SINGLE_CH_MODE))
		वापस -EPERM;

	चयन (chip->config2 & ADT7516_AD_SINGLE_CH_MASK) अणु
	हाल ADT7316_AD_SINGLE_CH_VDD:
		वापस प्र_लिखो(buf, "0 - VDD\n");
	हाल ADT7316_AD_SINGLE_CH_IN:
		वापस प्र_लिखो(buf, "1 - Internal Temperature\n");
	हाल ADT7316_AD_SINGLE_CH_EX:
		अगर (((chip->id & ID_FAMILY_MASK) == ID_ADT75XX) &&
		    (chip->config1 & ADT7516_SEL_AIN1_2_EX_TEMP_MASK) == 0)
			वापस प्र_लिखो(buf, "2 - AIN1\n");

		वापस प्र_लिखो(buf, "2 - External Temperature\n");
	हाल ADT7516_AD_SINGLE_CH_AIN2:
		अगर ((chip->config1 & ADT7516_SEL_AIN1_2_EX_TEMP_MASK) == 0)
			वापस प्र_लिखो(buf, "3 - AIN2\n");

		वापस प्र_लिखो(buf, "N/A\n");
	हाल ADT7516_AD_SINGLE_CH_AIN3:
		अगर (chip->config1 & ADT7516_SEL_AIN3)
			वापस प्र_लिखो(buf, "4 - AIN3\n");

		वापस प्र_लिखो(buf, "N/A\n");
	हाल ADT7516_AD_SINGLE_CH_AIN4:
		वापस प्र_लिखो(buf, "5 - AIN4\n");
	शेष:
		वापस प्र_लिखो(buf, "N/A\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार adt7316_store_ad_channel(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf,
					माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config2;
	u8 data;
	पूर्णांक ret;

	अगर (!(chip->config2 & ADT7316_AD_SINGLE_CH_MODE))
		वापस -EPERM;

	ret = kstrtou8(buf, 10, &data);
	अगर (ret)
		वापस -EINVAL;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX) अणु
		अगर (data > 5)
			वापस -EINVAL;

		config2 = chip->config2 & (~ADT7516_AD_SINGLE_CH_MASK);
	पूर्ण अन्यथा अणु
		अगर (data > 2)
			वापस -EINVAL;

		config2 = chip->config2 & (~ADT7316_AD_SINGLE_CH_MASK);
	पूर्ण

	config2 |= data;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG2, config2);
	अगर (ret)
		वापस -EIO;

	chip->config2 = config2;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(ad_channel, 0644,
		adt7316_show_ad_channel,
		adt7316_store_ad_channel,
		0);

अटल sमाप_प्रकार adt7316_show_all_ad_channels(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (!(chip->config2 & ADT7316_AD_SINGLE_CH_MODE))
		वापस -EPERM;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		वापस प्र_लिखो(buf, "0 - VDD\n1 - Internal Temperature\n"
				"2 - External Temperature or AIN1\n"
				"3 - AIN2\n4 - AIN3\n5 - AIN4\n");
	वापस प्र_लिखो(buf, "0 - VDD\n1 - Internal Temperature\n"
			"2 - External Temperature\n");
पूर्ण

अटल IIO_DEVICE_ATTR(all_ad_channels, 0444,
		adt7316_show_all_ad_channels, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_disable_averaging(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->config2 & ADT7316_DISABLE_AVERAGING));
पूर्ण

अटल sमाप_प्रकार adt7316_store_disable_averaging(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config2;
	पूर्णांक ret;

	config2 = chip->config2 & (~ADT7316_DISABLE_AVERAGING);
	अगर (buf[0] == '1')
		config2 |= ADT7316_DISABLE_AVERAGING;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG2, config2);
	अगर (ret)
		वापस -EIO;

	chip->config2 = config2;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(disable_averaging, 0644,
		adt7316_show_disable_averaging,
		adt7316_store_disable_averaging,
		0);

अटल sमाप_प्रकार adt7316_show_enable_smbus_समयout(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->config2 & ADT7316_EN_SMBUS_TIMEOUT));
पूर्ण

अटल sमाप_प्रकार adt7316_store_enable_smbus_समयout(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  स्थिर अक्षर *buf,
						  माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config2;
	पूर्णांक ret;

	config2 = chip->config2 & (~ADT7316_EN_SMBUS_TIMEOUT);
	अगर (buf[0] == '1')
		config2 |= ADT7316_EN_SMBUS_TIMEOUT;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG2, config2);
	अगर (ret)
		वापस -EIO;

	chip->config2 = config2;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(enable_smbus_समयout, 0644,
		adt7316_show_enable_smbus_समयout,
		adt7316_store_enable_smbus_समयout,
		0);

अटल sमाप_प्रकार adt7316_show_घातerकरोwn(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n", !!(chip->config1 & ADT7316_PD));
पूर्ण

अटल sमाप_प्रकार adt7316_store_घातerकरोwn(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config1;
	पूर्णांक ret;

	config1 = chip->config1 & (~ADT7316_PD);
	अगर (buf[0] == '1')
		config1 |= ADT7316_PD;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG1, config1);
	अगर (ret)
		वापस -EIO;

	chip->config1 = config1;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(घातerकरोwn, 0644,
		adt7316_show_घातerकरोwn,
		adt7316_store_घातerकरोwn,
		0);

अटल sमाप_प्रकार adt7316_show_fast_ad_घड़ी(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n", !!(chip->config3 & ADT7316_ADCLK_22_5));
पूर्ण

अटल sमाप_प्रकार adt7316_store_fast_ad_घड़ी(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf,
					   माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	पूर्णांक ret;

	config3 = chip->config3 & (~ADT7316_ADCLK_22_5);
	अगर (buf[0] == '1')
		config3 |= ADT7316_ADCLK_22_5;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, config3);
	अगर (ret)
		वापस -EIO;

	chip->config3 = config3;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(fast_ad_घड़ी, 0644,
		adt7316_show_fast_ad_घड़ी,
		adt7316_store_fast_ad_घड़ी,
		0);

अटल sमाप_प्रकार adt7316_show_da_high_resolution(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (chip->config3 & ADT7316_DA_HIGH_RESOLUTION) अणु
		अगर (chip->id != ID_ADT7318 && chip->id != ID_ADT7519)
			वापस प्र_लिखो(buf, "1 (10 bits)\n");
	पूर्ण

	वापस प्र_लिखो(buf, "0 (8 bits)\n");
पूर्ण

अटल sमाप_प्रकार adt7316_store_da_high_resolution(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	पूर्णांक ret;

	अगर (chip->id == ID_ADT7318 || chip->id == ID_ADT7519)
		वापस -EPERM;

	config3 = chip->config3 & (~ADT7316_DA_HIGH_RESOLUTION);
	अगर (buf[0] == '1')
		config3 |= ADT7316_DA_HIGH_RESOLUTION;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, config3);
	अगर (ret)
		वापस -EIO;

	chip->config3 = config3;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(da_high_resolution, 0644,
		adt7316_show_da_high_resolution,
		adt7316_store_da_high_resolution,
		0);

अटल sमाप_प्रकार adt7316_show_AIN_पूर्णांकernal_Vref(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
		वापस -EPERM;

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->config3 & ADT7516_AIN_IN_VREF));
पूर्ण

अटल sमाप_प्रकार adt7316_store_AIN_पूर्णांकernal_Vref(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	पूर्णांक ret;

	अगर ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
		वापस -EPERM;

	अगर (buf[0] != '1')
		config3 = chip->config3 & (~ADT7516_AIN_IN_VREF);
	अन्यथा
		config3 = chip->config3 | ADT7516_AIN_IN_VREF;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, config3);
	अगर (ret)
		वापस -EIO;

	chip->config3 = config3;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(AIN_पूर्णांकernal_Vref, 0644,
		adt7316_show_AIN_पूर्णांकernal_Vref,
		adt7316_store_AIN_पूर्णांकernal_Vref,
		0);

अटल sमाप_प्रकार adt7316_show_enable_prop_DACA(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->config3 & ADT7316_EN_IN_TEMP_PROP_DACA));
पूर्ण

अटल sमाप_प्रकार adt7316_store_enable_prop_DACA(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf,
					      माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	पूर्णांक ret;

	config3 = chip->config3 & (~ADT7316_EN_IN_TEMP_PROP_DACA);
	अगर (buf[0] == '1')
		config3 |= ADT7316_EN_IN_TEMP_PROP_DACA;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, config3);
	अगर (ret)
		वापस -EIO;

	chip->config3 = config3;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(enable_proportion_DACA, 0644,
		       adt7316_show_enable_prop_DACA,
		       adt7316_store_enable_prop_DACA,
		       0);

अटल sमाप_प्रकार adt7316_show_enable_prop_DACB(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->config3 & ADT7316_EN_EX_TEMP_PROP_DACB));
पूर्ण

अटल sमाप_प्रकार adt7316_store_enable_prop_DACB(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf,
					      माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	पूर्णांक ret;

	config3 = chip->config3 & (~ADT7316_EN_EX_TEMP_PROP_DACB);
	अगर (buf[0] == '1')
		config3 |= ADT7316_EN_EX_TEMP_PROP_DACB;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, config3);
	अगर (ret)
		वापस -EIO;

	chip->config3 = config3;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(enable_proportion_DACB, 0644,
		       adt7316_show_enable_prop_DACB,
		       adt7316_store_enable_prop_DACB,
		       0);

अटल sमाप_प्रकार adt7316_show_DAC_2Vref_ch_mask(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "0x%x\n",
		chip->dac_config & ADT7316_DA_2VREF_CH_MASK);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_2Vref_ch_mask(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 dac_config;
	u8 data;
	पूर्णांक ret;

	ret = kstrtou8(buf, 16, &data);
	अगर (ret || data > ADT7316_DA_2VREF_CH_MASK)
		वापस -EINVAL;

	dac_config = chip->dac_config & (~ADT7316_DA_2VREF_CH_MASK);
	dac_config |= data;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_DAC_CONFIG, dac_config);
	अगर (ret)
		वापस -EIO;

	chip->dac_config = dac_config;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_2Vref_channels_mask, 0644,
		       adt7316_show_DAC_2Vref_ch_mask,
		       adt7316_store_DAC_2Vref_ch_mask,
		       0);

अटल sमाप_प्रकार adt7316_show_DAC_update_mode(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (!(chip->config3 & ADT7316_DA_EN_VIA_DAC_LDAC))
		वापस प्र_लिखो(buf, "manual\n");

	चयन (chip->dac_config & ADT7316_DA_EN_MODE_MASK) अणु
	हाल ADT7316_DA_EN_MODE_SINGLE:
		वापस प्र_लिखो(buf,
			"0 - auto at any MSB DAC writing\n");
	हाल ADT7316_DA_EN_MODE_AB_CD:
		वापस प्र_लिखो(buf,
			"1 - auto at MSB DAC AB and CD writing\n");
	हाल ADT7316_DA_EN_MODE_ABCD:
		वापस प्र_लिखो(buf,
			"2 - auto at MSB DAC ABCD writing\n");
	शेष: /* ADT7316_DA_EN_MODE_LDAC */
		वापस प्र_लिखो(buf, "3 - manual\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_update_mode(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf,
					     माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 dac_config;
	u8 data;
	पूर्णांक ret;

	अगर (!(chip->config3 & ADT7316_DA_EN_VIA_DAC_LDAC))
		वापस -EPERM;

	ret = kstrtou8(buf, 10, &data);
	अगर (ret || data > (ADT7316_DA_EN_MODE_MASK >> ADT7316_DA_EN_MODE_SHIFT))
		वापस -EINVAL;

	dac_config = chip->dac_config & (~ADT7316_DA_EN_MODE_MASK);
	dac_config |= data << ADT7316_DA_EN_MODE_SHIFT;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_DAC_CONFIG, dac_config);
	अगर (ret)
		वापस -EIO;

	chip->dac_config = dac_config;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_update_mode, 0644,
		       adt7316_show_DAC_update_mode,
		       adt7316_store_DAC_update_mode,
		       0);

अटल sमाप_प्रकार adt7316_show_all_DAC_update_modes(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर (chip->config3 & ADT7316_DA_EN_VIA_DAC_LDAC)
		वापस प्र_लिखो(buf, "0 - auto at any MSB DAC writing\n"
				"1 - auto at MSB DAC AB and CD writing\n"
				"2 - auto at MSB DAC ABCD writing\n"
				"3 - manual\n");
	वापस प्र_लिखो(buf, "manual\n");
पूर्ण

अटल IIO_DEVICE_ATTR(all_DAC_update_modes, 0444,
		       adt7316_show_all_DAC_update_modes, शून्य, 0);

अटल sमाप_प्रकार adt7316_store_update_DAC(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf,
					माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 ldac_config;
	u8 data;
	पूर्णांक ret;

	अगर (chip->config3 & ADT7316_DA_EN_VIA_DAC_LDAC) अणु
		अगर ((chip->dac_config & ADT7316_DA_EN_MODE_MASK) !=
			ADT7316_DA_EN_MODE_LDAC)
			वापस -EPERM;

		ret = kstrtou8(buf, 16, &data);
		अगर (ret || data > ADT7316_LDAC_EN_DA_MASK)
			वापस -EINVAL;

		ldac_config = chip->ldac_config & (~ADT7316_LDAC_EN_DA_MASK);
		ldac_config |= data;

		ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_LDAC_CONFIG,
			ldac_config);
		अगर (ret)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		gpiod_set_value(chip->ldac_pin, 0);
		gpiod_set_value(chip->ldac_pin, 1);
	पूर्ण

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(update_DAC, 0644,
		       शून्य,
		       adt7316_store_update_DAC,
		       0);

अटल sमाप_प्रकार adt7316_show_DA_AB_Vref_bypass(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->dac_config & ADT7316_VREF_BYPASS_DAC_AB));
पूर्ण

अटल sमाप_प्रकार adt7316_store_DA_AB_Vref_bypass(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 dac_config;
	पूर्णांक ret;

	dac_config = chip->dac_config & (~ADT7316_VREF_BYPASS_DAC_AB);
	अगर (buf[0] == '1')
		dac_config |= ADT7316_VREF_BYPASS_DAC_AB;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_DAC_CONFIG, dac_config);
	अगर (ret)
		वापस -EIO;

	chip->dac_config = dac_config;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(DA_AB_Vref_bypass, 0644,
		       adt7316_show_DA_AB_Vref_bypass,
		       adt7316_store_DA_AB_Vref_bypass,
		       0);

अटल sमाप_प्रकार adt7316_show_DA_CD_Vref_bypass(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n",
		!!(chip->dac_config & ADT7316_VREF_BYPASS_DAC_CD));
पूर्ण

अटल sमाप_प्रकार adt7316_store_DA_CD_Vref_bypass(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 dac_config;
	पूर्णांक ret;

	dac_config = chip->dac_config & (~ADT7316_VREF_BYPASS_DAC_CD);
	अगर (buf[0] == '1')
		dac_config |= ADT7316_VREF_BYPASS_DAC_CD;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_DAC_CONFIG, dac_config);
	अगर (ret)
		वापस -EIO;

	chip->dac_config = dac_config;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(DA_CD_Vref_bypass, 0644,
		       adt7316_show_DA_CD_Vref_bypass,
		       adt7316_store_DA_CD_Vref_bypass,
		       0);

अटल sमाप_प्रकार adt7316_show_DAC_पूर्णांकernal_Vref(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		वापस प्र_लिखो(buf, "0x%x\n",
			(chip->ldac_config & ADT7516_DAC_IN_VREF_MASK) >>
			ADT7516_DAC_IN_VREF_OFFSET);
	वापस प्र_लिखो(buf, "%d\n",
		       !!(chip->ldac_config & ADT7316_DAC_IN_VREF));
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_पूर्णांकernal_Vref(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf,
					       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 ldac_config;
	u8 data;
	पूर्णांक ret;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX) अणु
		ret = kstrtou8(buf, 16, &data);
		अगर (ret || data > 3)
			वापस -EINVAL;

		ldac_config = chip->ldac_config & (~ADT7516_DAC_IN_VREF_MASK);
		अगर (data & 0x1)
			ldac_config |= ADT7516_DAC_AB_IN_VREF;
		अगर (data & 0x2)
			ldac_config |= ADT7516_DAC_CD_IN_VREF;
	पूर्ण अन्यथा अणु
		ret = kstrtou8(buf, 16, &data);
		अगर (ret)
			वापस -EINVAL;

		ldac_config = chip->ldac_config & (~ADT7316_DAC_IN_VREF);
		अगर (data)
			ldac_config = chip->ldac_config | ADT7316_DAC_IN_VREF;
	पूर्ण

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_LDAC_CONFIG,
			ldac_config);
	अगर (ret)
		वापस -EIO;

	chip->ldac_config = ldac_config;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_पूर्णांकernal_Vref, 0644,
		       adt7316_show_DAC_पूर्णांकernal_Vref,
		       adt7316_store_DAC_पूर्णांकernal_Vref,
		       0);

अटल sमाप_प्रकार adt7316_show_ad(काष्ठा adt7316_chip_info *chip,
			       पूर्णांक channel, अक्षर *buf)
अणु
	u16 data;
	u8 msb, lsb;
	अक्षर sign = ' ';
	पूर्णांक ret;

	अगर ((chip->config2 & ADT7316_AD_SINGLE_CH_MODE) &&
	    channel != (chip->config2 & ADT7516_AD_SINGLE_CH_MASK))
		वापस -EPERM;

	चयन (channel) अणु
	हाल ADT7316_AD_SINGLE_CH_IN:
		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_LSB_IN_TEMP_VDD, &lsb);
		अगर (ret)
			वापस -EIO;

		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		अगर (ret)
			वापस -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= lsb & ADT7316_LSB_IN_TEMP_MASK;
		अवरोध;
	हाल ADT7316_AD_SINGLE_CH_VDD:
		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_LSB_IN_TEMP_VDD, &lsb);
		अगर (ret)
			वापस -EIO;

		ret = chip->bus.पढ़ो(chip->bus.client,

			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		अगर (ret)
			वापस -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= (lsb & ADT7316_LSB_VDD_MASK) >> ADT7316_LSB_VDD_OFFSET;
		वापस प्र_लिखो(buf, "%d\n", data);
	शेष: /* ex_temp and ain */
		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_LSB_EX_TEMP_AIN, &lsb);
		अगर (ret)
			वापस -EIO;

		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_AD_MSB_DATA_BASE + channel, &msb);
		अगर (ret)
			वापस -EIO;

		data = msb << ADT7316_T_VALUE_FLOAT_OFFSET;
		data |= lsb & (ADT7316_LSB_EX_TEMP_MASK <<
			(ADT7516_LSB_AIN_SHIFT * (channel -
			(ADT7316_MSB_EX_TEMP - ADT7316_AD_MSB_DATA_BASE))));

		अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
			वापस प्र_लिखो(buf, "%d\n", data);

		अवरोध;
	पूर्ण

	अगर (data & ADT7316_T_VALUE_SIGN) अणु
		/* convert supplement to positive value */
		data = (ADT7316_T_VALUE_SIGN << 1) - data;
		sign = '-';
	पूर्ण

	वापस प्र_लिखो(buf, "%c%d.%.2d\n", sign,
		(data >> ADT7316_T_VALUE_FLOAT_OFFSET),
		(data & ADT7316_T_VALUE_FLOAT_MASK) * 25);
पूर्ण

अटल sमाप_प्रकार adt7316_show_VDD(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7316_AD_SINGLE_CH_VDD, buf);
पूर्ण
अटल IIO_DEVICE_ATTR(VDD, 0444, adt7316_show_VDD, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_in_temp(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7316_AD_SINGLE_CH_IN, buf);
पूर्ण

अटल IIO_DEVICE_ATTR(in_temp, 0444, adt7316_show_in_temp, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_ex_temp_AIN1(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7316_AD_SINGLE_CH_EX, buf);
पूर्ण

अटल IIO_DEVICE_ATTR(ex_temp_AIN1, 0444, adt7316_show_ex_temp_AIN1,
		       शून्य, 0);
अटल IIO_DEVICE_ATTR(ex_temp, 0444, adt7316_show_ex_temp_AIN1, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_AIN2(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7516_AD_SINGLE_CH_AIN2, buf);
पूर्ण
अटल IIO_DEVICE_ATTR(AIN2, 0444, adt7316_show_AIN2, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_AIN3(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7516_AD_SINGLE_CH_AIN3, buf);
पूर्ण
अटल IIO_DEVICE_ATTR(AIN3, 0444, adt7316_show_AIN3, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_AIN4(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_ad(chip, ADT7516_AD_SINGLE_CH_AIN4, buf);
पूर्ण
अटल IIO_DEVICE_ATTR(AIN4, 0444, adt7316_show_AIN4, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_temp_offset(काष्ठा adt7316_chip_info *chip,
					पूर्णांक offset_addr, अक्षर *buf)
अणु
	पूर्णांक data;
	u8 val;
	पूर्णांक ret;

	ret = chip->bus.पढ़ो(chip->bus.client, offset_addr, &val);
	अगर (ret)
		वापस -EIO;

	data = (पूर्णांक)val;
	अगर (val & 0x80)
		data -= 256;

	वापस प्र_लिखो(buf, "%d\n", data);
पूर्ण

अटल sमाप_प्रकार adt7316_store_temp_offset(काष्ठा adt7316_chip_info *chip,
					 पूर्णांक offset_addr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	पूर्णांक data;
	u8 val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &data);
	अगर (ret || data > 127 || data < -128)
		वापस -EINVAL;

	अगर (data < 0)
		data += 256;

	val = (u8)data;

	ret = chip->bus.ग_लिखो(chip->bus.client, offset_addr, val);
	अगर (ret)
		वापस -EIO;

	वापस len;
पूर्ण

अटल sमाप_प्रकार adt7316_show_in_temp_offset(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_temp_offset(chip, ADT7316_IN_TEMP_OFFSET, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_in_temp_offset(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_temp_offset(chip, ADT7316_IN_TEMP_OFFSET, buf,
			len);
पूर्ण

अटल IIO_DEVICE_ATTR(in_temp_offset, 0644,
		       adt7316_show_in_temp_offset,
		       adt7316_store_in_temp_offset, 0);

अटल sमाप_प्रकार adt7316_show_ex_temp_offset(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_temp_offset(chip, ADT7316_EX_TEMP_OFFSET, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_ex_temp_offset(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_temp_offset(chip, ADT7316_EX_TEMP_OFFSET, buf,
			len);
पूर्ण

अटल IIO_DEVICE_ATTR(ex_temp_offset, 0644,
		       adt7316_show_ex_temp_offset,
		       adt7316_store_ex_temp_offset, 0);

अटल sमाप_प्रकार adt7316_show_in_analog_temp_offset(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_temp_offset(chip,
			ADT7316_IN_ANALOG_TEMP_OFFSET, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_in_analog_temp_offset(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_temp_offset(chip,
			ADT7316_IN_ANALOG_TEMP_OFFSET, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(in_analog_temp_offset, 0644,
		       adt7316_show_in_analog_temp_offset,
		       adt7316_store_in_analog_temp_offset, 0);

अटल sमाप_प्रकार adt7316_show_ex_analog_temp_offset(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_temp_offset(chip,
			ADT7316_EX_ANALOG_TEMP_OFFSET, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_ex_analog_temp_offset(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf,
						माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_temp_offset(chip,
			ADT7316_EX_ANALOG_TEMP_OFFSET, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(ex_analog_temp_offset, 0644,
		       adt7316_show_ex_analog_temp_offset,
		       adt7316_store_ex_analog_temp_offset, 0);

अटल sमाप_प्रकार adt7316_show_DAC(काष्ठा adt7316_chip_info *chip,
				पूर्णांक channel, अक्षर *buf)
अणु
	u16 data = 0;
	u8 msb, lsb, offset;
	पूर्णांक ret;

	अगर (channel >= ADT7316_DA_MSB_DATA_REGS ||
	    (channel == 0 &&
	    (chip->config3 & ADT7316_EN_IN_TEMP_PROP_DACA)) ||
	    (channel == 1 &&
	    (chip->config3 & ADT7316_EN_EX_TEMP_PROP_DACB)))
		वापस -EPERM;

	offset = chip->dac_bits - 8;

	अगर (chip->dac_bits > 8) अणु
		ret = chip->bus.पढ़ो(chip->bus.client,
			ADT7316_DA_DATA_BASE + channel * 2, &lsb);
		अगर (ret)
			वापस -EIO;
	पूर्ण

	ret = chip->bus.पढ़ो(chip->bus.client,
		ADT7316_DA_DATA_BASE + 1 + channel * 2, &msb);
	अगर (ret)
		वापस -EIO;

	अगर (chip->dac_bits == 12)
		data = lsb >> ADT7316_DA_12_BIT_LSB_SHIFT;
	अन्यथा अगर (chip->dac_bits == 10)
		data = lsb >> ADT7316_DA_10_BIT_LSB_SHIFT;
	data |= msb << offset;

	वापस प्र_लिखो(buf, "%d\n", data);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC(काष्ठा adt7316_chip_info *chip,
				 पूर्णांक channel, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	u8 msb, lsb, lsb_reg, offset;
	u16 data;
	पूर्णांक ret;

	अगर (channel >= ADT7316_DA_MSB_DATA_REGS ||
	    (channel == 0 &&
	    (chip->config3 & ADT7316_EN_IN_TEMP_PROP_DACA)) ||
	    (channel == 1 &&
	    (chip->config3 & ADT7316_EN_EX_TEMP_PROP_DACB)))
		वापस -EPERM;

	offset = chip->dac_bits - 8;

	ret = kstrtou16(buf, 10, &data);
	अगर (ret || data >= (1 << chip->dac_bits))
		वापस -EINVAL;

	अगर (chip->dac_bits > 8) अणु
		lsb = data & ((1 << offset) - 1);
		अगर (chip->dac_bits == 12)
			lsb_reg = lsb << ADT7316_DA_12_BIT_LSB_SHIFT;
		अन्यथा
			lsb_reg = lsb << ADT7316_DA_10_BIT_LSB_SHIFT;
		ret = chip->bus.ग_लिखो(chip->bus.client,
			ADT7316_DA_DATA_BASE + channel * 2, lsb_reg);
		अगर (ret)
			वापस -EIO;
	पूर्ण

	msb = data >> offset;
	ret = chip->bus.ग_लिखो(chip->bus.client,
		ADT7316_DA_DATA_BASE + 1 + channel * 2, msb);
	अगर (ret)
		वापस -EIO;

	वापस len;
पूर्ण

अटल sमाप_प्रकार adt7316_show_DAC_A(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_DAC(chip, 0, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_A(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_DAC(chip, 0, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_A, 0644, adt7316_show_DAC_A,
		       adt7316_store_DAC_A, 0);

अटल sमाप_प्रकार adt7316_show_DAC_B(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_DAC(chip, 1, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_B(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_DAC(chip, 1, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_B, 0644, adt7316_show_DAC_B,
		       adt7316_store_DAC_B, 0);

अटल sमाप_प्रकार adt7316_show_DAC_C(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_DAC(chip, 2, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_C(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_DAC(chip, 2, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_C, 0644, adt7316_show_DAC_C,
		       adt7316_store_DAC_C, 0);

अटल sमाप_प्रकार adt7316_show_DAC_D(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_show_DAC(chip, 3, buf);
पूर्ण

अटल sमाप_प्रकार adt7316_store_DAC_D(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस adt7316_store_DAC(chip, 3, buf, len);
पूर्ण

अटल IIO_DEVICE_ATTR(DAC_D, 0644, adt7316_show_DAC_D,
		       adt7316_store_DAC_D, 0);

अटल sमाप_प्रकार adt7316_show_device_id(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 id;
	पूर्णांक ret;

	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_DEVICE_ID, &id);
	अगर (ret)
		वापस -EIO;

	वापस प्र_लिखो(buf, "%d\n", id);
पूर्ण

अटल IIO_DEVICE_ATTR(device_id, 0444, adt7316_show_device_id, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_manufactorer_id(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 id;
	पूर्णांक ret;

	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_MANUFACTURE_ID, &id);
	अगर (ret)
		वापस -EIO;

	वापस प्र_लिखो(buf, "%d\n", id);
पूर्ण

अटल IIO_DEVICE_ATTR(manufactorer_id, 0444,
		       adt7316_show_manufactorer_id, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_device_rev(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 rev;
	पूर्णांक ret;

	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_DEVICE_REV, &rev);
	अगर (ret)
		वापस -EIO;

	वापस प्र_लिखो(buf, "%d\n", rev);
पूर्ण

अटल IIO_DEVICE_ATTR(device_rev, 0444, adt7316_show_device_rev, शून्य, 0);

अटल sमाप_प्रकार adt7316_show_bus_type(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 stat;
	पूर्णांक ret;

	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_SPI_LOCK_STAT, &stat);
	अगर (ret)
		वापस -EIO;

	अगर (stat)
		वापस प्र_लिखो(buf, "spi\n");

	वापस प्र_लिखो(buf, "i2c\n");
पूर्ण

अटल IIO_DEVICE_ATTR(bus_type, 0444, adt7316_show_bus_type, शून्य, 0);

अटल काष्ठा attribute *adt7316_attributes[] = अणु
	&iio_dev_attr_all_modes.dev_attr.attr,
	&iio_dev_attr_mode.dev_attr.attr,
	&iio_dev_attr_enabled.dev_attr.attr,
	&iio_dev_attr_ad_channel.dev_attr.attr,
	&iio_dev_attr_all_ad_channels.dev_attr.attr,
	&iio_dev_attr_disable_averaging.dev_attr.attr,
	&iio_dev_attr_enable_smbus_समयout.dev_attr.attr,
	&iio_dev_attr_घातerकरोwn.dev_attr.attr,
	&iio_dev_attr_fast_ad_घड़ी.dev_attr.attr,
	&iio_dev_attr_da_high_resolution.dev_attr.attr,
	&iio_dev_attr_enable_proportion_DACA.dev_attr.attr,
	&iio_dev_attr_enable_proportion_DACB.dev_attr.attr,
	&iio_dev_attr_DAC_2Vref_channels_mask.dev_attr.attr,
	&iio_dev_attr_DAC_update_mode.dev_attr.attr,
	&iio_dev_attr_all_DAC_update_modes.dev_attr.attr,
	&iio_dev_attr_update_DAC.dev_attr.attr,
	&iio_dev_attr_DA_AB_Vref_bypass.dev_attr.attr,
	&iio_dev_attr_DA_CD_Vref_bypass.dev_attr.attr,
	&iio_dev_attr_DAC_पूर्णांकernal_Vref.dev_attr.attr,
	&iio_dev_attr_VDD.dev_attr.attr,
	&iio_dev_attr_in_temp.dev_attr.attr,
	&iio_dev_attr_ex_temp.dev_attr.attr,
	&iio_dev_attr_in_temp_offset.dev_attr.attr,
	&iio_dev_attr_ex_temp_offset.dev_attr.attr,
	&iio_dev_attr_in_analog_temp_offset.dev_attr.attr,
	&iio_dev_attr_ex_analog_temp_offset.dev_attr.attr,
	&iio_dev_attr_DAC_A.dev_attr.attr,
	&iio_dev_attr_DAC_B.dev_attr.attr,
	&iio_dev_attr_DAC_C.dev_attr.attr,
	&iio_dev_attr_DAC_D.dev_attr.attr,
	&iio_dev_attr_device_id.dev_attr.attr,
	&iio_dev_attr_manufactorer_id.dev_attr.attr,
	&iio_dev_attr_device_rev.dev_attr.attr,
	&iio_dev_attr_bus_type.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7316_attribute_group = अणु
	.attrs = adt7316_attributes,
पूर्ण;

अटल काष्ठा attribute *adt7516_attributes[] = अणु
	&iio_dev_attr_all_modes.dev_attr.attr,
	&iio_dev_attr_mode.dev_attr.attr,
	&iio_dev_attr_select_ex_temp.dev_attr.attr,
	&iio_dev_attr_enabled.dev_attr.attr,
	&iio_dev_attr_ad_channel.dev_attr.attr,
	&iio_dev_attr_all_ad_channels.dev_attr.attr,
	&iio_dev_attr_disable_averaging.dev_attr.attr,
	&iio_dev_attr_enable_smbus_समयout.dev_attr.attr,
	&iio_dev_attr_घातerकरोwn.dev_attr.attr,
	&iio_dev_attr_fast_ad_घड़ी.dev_attr.attr,
	&iio_dev_attr_AIN_पूर्णांकernal_Vref.dev_attr.attr,
	&iio_dev_attr_da_high_resolution.dev_attr.attr,
	&iio_dev_attr_enable_proportion_DACA.dev_attr.attr,
	&iio_dev_attr_enable_proportion_DACB.dev_attr.attr,
	&iio_dev_attr_DAC_2Vref_channels_mask.dev_attr.attr,
	&iio_dev_attr_DAC_update_mode.dev_attr.attr,
	&iio_dev_attr_all_DAC_update_modes.dev_attr.attr,
	&iio_dev_attr_update_DAC.dev_attr.attr,
	&iio_dev_attr_DAC_पूर्णांकernal_Vref.dev_attr.attr,
	&iio_dev_attr_VDD.dev_attr.attr,
	&iio_dev_attr_in_temp.dev_attr.attr,
	&iio_dev_attr_ex_temp_AIN1.dev_attr.attr,
	&iio_dev_attr_AIN2.dev_attr.attr,
	&iio_dev_attr_AIN3.dev_attr.attr,
	&iio_dev_attr_AIN4.dev_attr.attr,
	&iio_dev_attr_in_temp_offset.dev_attr.attr,
	&iio_dev_attr_ex_temp_offset.dev_attr.attr,
	&iio_dev_attr_in_analog_temp_offset.dev_attr.attr,
	&iio_dev_attr_ex_analog_temp_offset.dev_attr.attr,
	&iio_dev_attr_DAC_A.dev_attr.attr,
	&iio_dev_attr_DAC_B.dev_attr.attr,
	&iio_dev_attr_DAC_C.dev_attr.attr,
	&iio_dev_attr_DAC_D.dev_attr.attr,
	&iio_dev_attr_device_id.dev_attr.attr,
	&iio_dev_attr_manufactorer_id.dev_attr.attr,
	&iio_dev_attr_device_rev.dev_attr.attr,
	&iio_dev_attr_bus_type.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7516_attribute_group = अणु
	.attrs = adt7516_attributes,
पूर्ण;

अटल irqवापस_t adt7316_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा adt7316_chip_info *chip = iio_priv(indio_dev);
	u8 stat1, stat2;
	पूर्णांक ret;
	s64 समय;

	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_INT_STAT1, &stat1);
	अगर (!ret) अणु
		अगर ((chip->id & ID_FAMILY_MASK) != ID_ADT75XX)
			stat1 &= 0x1F;

		समय = iio_get_समय_ns(indio_dev);
		अगर (stat1 & BIT(0))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_RISING),
				       समय);
		अगर (stat1 & BIT(1))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_FALLING),
				       समय);
		अगर (stat1 & BIT(2))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_RISING),
				       समय);
		अगर (stat1 & BIT(3))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_TEMP, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_FALLING),
				       समय);
		अगर (stat1 & BIT(5))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 1,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_EITHER),
				       समय);
		अगर (stat1 & BIT(6))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 2,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_EITHER),
				       समय);
		अगर (stat1 & BIT(7))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, 3,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_EITHER),
				       समय);
		पूर्ण
	ret = chip->bus.पढ़ो(chip->bus.client, ADT7316_INT_STAT2, &stat2);
	अगर (!ret) अणु
		अगर (stat2 & ADT7316_INT_MASK2_VDD)
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    0,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_RISING),
				       iio_get_समय_ns(indio_dev));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adt7316_setup_irq(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adt7316_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक irq_type, ret;

	irq_type = irqd_get_trigger_type(irq_get_irq_data(chip->bus.irq));

	चयन (irq_type) अणु
	हाल IRQF_TRIGGER_HIGH:
	हाल IRQF_TRIGGER_RISING:
		अवरोध;
	हाल IRQF_TRIGGER_LOW:
	हाल IRQF_TRIGGER_FALLING:
		अवरोध;
	शेष:
		dev_info(&indio_dev->dev, "mode %d unsupported, using IRQF_TRIGGER_LOW\n",
			 irq_type);
		irq_type = IRQF_TRIGGER_LOW;
		अवरोध;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&indio_dev->dev, chip->bus.irq,
					शून्य, adt7316_event_handler,
					irq_type | IRQF_ONESHOT,
					indio_dev->name, indio_dev);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to request irq %d\n",
			chip->bus.irq);
		वापस ret;
	पूर्ण

	अगर (irq_type & IRQF_TRIGGER_HIGH)
		chip->config1 |= ADT7316_INT_POLARITY;

	वापस 0;
पूर्ण

/*
 * Show mask of enabled पूर्णांकerrupts in Hex.
 */
अटल sमाप_प्रकार adt7316_show_पूर्णांक_mask(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "0x%x\n", chip->पूर्णांक_mask);
पूर्ण

/*
 * Set 1 to the mask in Hex to enabled पूर्णांकerrupts.
 */
अटल sमाप_प्रकार adt7316_set_पूर्णांक_mask(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u16 data;
	पूर्णांक ret;
	u8 mask;

	ret = kstrtou16(buf, 16, &data);
	अगर (ret || data >= ADT7316_VDD_INT_MASK + 1)
		वापस -EINVAL;

	अगर (data & ADT7316_VDD_INT_MASK)
		mask = 0;			/* enable vdd पूर्णांक */
	अन्यथा
		mask = ADT7316_INT_MASK2_VDD;	/* disable vdd पूर्णांक */

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_INT_MASK2, mask);
	अगर (!ret) अणु
		chip->पूर्णांक_mask &= ~ADT7316_VDD_INT_MASK;
		chip->पूर्णांक_mask |= data & ADT7316_VDD_INT_MASK;
	पूर्ण

	अगर (data & ADT7316_TEMP_AIN_INT_MASK) अणु
		अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT73XX)
			/* mask in reg is opposite, set 1 to disable */
			mask = (~data) & ADT7316_TEMP_INT_MASK;
		अन्यथा
			/* mask in reg is opposite, set 1 to disable */
			mask = (~data) & ADT7316_TEMP_AIN_INT_MASK;
	पूर्ण
	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_INT_MASK1, mask);

	chip->पूर्णांक_mask = mask;

	वापस len;
पूर्ण

अटल अंतरभूत sमाप_प्रकार adt7316_show_ad_bound(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 val;
	पूर्णांक data;
	पूर्णांक ret;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT73XX &&
	    this_attr->address > ADT7316_EX_TEMP_LOW)
		वापस -EPERM;

	ret = chip->bus.पढ़ो(chip->bus.client, this_attr->address, &val);
	अगर (ret)
		वापस -EIO;

	data = (पूर्णांक)val;

	अगर (!((chip->id & ID_FAMILY_MASK) == ID_ADT75XX &&
	      (chip->config1 & ADT7516_SEL_AIN1_2_EX_TEMP_MASK) == 0)) अणु
		अगर (data & 0x80)
			data -= 256;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", data);
पूर्ण

अटल अंतरभूत sमाप_प्रकार adt7316_set_ad_bound(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf,
					   माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	पूर्णांक data;
	u8 val;
	पूर्णांक ret;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT73XX &&
	    this_attr->address > ADT7316_EX_TEMP_LOW)
		वापस -EPERM;

	ret = kstrtoपूर्णांक(buf, 10, &data);
	अगर (ret)
		वापस -EINVAL;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX &&
	    (chip->config1 & ADT7516_SEL_AIN1_2_EX_TEMP_MASK) == 0) अणु
		अगर (data > 255 || data < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (data > 127 || data < -128)
			वापस -EINVAL;

		अगर (data < 0)
			data += 256;
	पूर्ण

	val = (u8)data;

	ret = chip->bus.ग_लिखो(chip->bus.client, this_attr->address, val);
	अगर (ret)
		वापस -EIO;

	वापस len;
पूर्ण

अटल sमाप_प्रकार adt7316_show_पूर्णांक_enabled(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस प्र_लिखो(buf, "%d\n", !!(chip->config1 & ADT7316_INT_EN));
पूर्ण

अटल sमाप_प्रकार adt7316_set_पूर्णांक_enabled(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार len)
अणु
	काष्ठा iio_dev *dev_info = dev_to_iio_dev(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config1;
	पूर्णांक ret;

	config1 = chip->config1 & (~ADT7316_INT_EN);
	अगर (buf[0] == '1')
		config1 |= ADT7316_INT_EN;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG1, config1);
	अगर (ret)
		वापस -EIO;

	chip->config1 = config1;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(पूर्णांक_mask,
		       0644,
		       adt7316_show_पूर्णांक_mask, adt7316_set_पूर्णांक_mask,
		       0);
अटल IIO_DEVICE_ATTR(in_temp_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_IN_TEMP_HIGH);
अटल IIO_DEVICE_ATTR(in_temp_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_IN_TEMP_LOW);
अटल IIO_DEVICE_ATTR(ex_temp_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_EX_TEMP_HIGH);
अटल IIO_DEVICE_ATTR(ex_temp_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_EX_TEMP_LOW);

/* NASTY duplication to be fixed */
अटल IIO_DEVICE_ATTR(ex_temp_ain1_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_EX_TEMP_HIGH);
अटल IIO_DEVICE_ATTR(ex_temp_ain1_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7316_EX_TEMP_LOW);
अटल IIO_DEVICE_ATTR(ain2_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN2_HIGH);
अटल IIO_DEVICE_ATTR(ain2_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN2_LOW);
अटल IIO_DEVICE_ATTR(ain3_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN3_HIGH);
अटल IIO_DEVICE_ATTR(ain3_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN3_LOW);
अटल IIO_DEVICE_ATTR(ain4_high_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN4_HIGH);
अटल IIO_DEVICE_ATTR(ain4_low_value,
		       0644,
		       adt7316_show_ad_bound, adt7316_set_ad_bound,
		       ADT7516_AIN4_LOW);
अटल IIO_DEVICE_ATTR(पूर्णांक_enabled,
		       0644,
		       adt7316_show_पूर्णांक_enabled,
		       adt7316_set_पूर्णांक_enabled, 0);

अटल काष्ठा attribute *adt7316_event_attributes[] = अणु
	&iio_dev_attr_पूर्णांक_mask.dev_attr.attr,
	&iio_dev_attr_in_temp_high_value.dev_attr.attr,
	&iio_dev_attr_in_temp_low_value.dev_attr.attr,
	&iio_dev_attr_ex_temp_high_value.dev_attr.attr,
	&iio_dev_attr_ex_temp_low_value.dev_attr.attr,
	&iio_dev_attr_पूर्णांक_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7316_event_attribute_group = अणु
	.attrs = adt7316_event_attributes,
	.name = "events",
पूर्ण;

अटल काष्ठा attribute *adt7516_event_attributes[] = अणु
	&iio_dev_attr_पूर्णांक_mask.dev_attr.attr,
	&iio_dev_attr_in_temp_high_value.dev_attr.attr,
	&iio_dev_attr_in_temp_low_value.dev_attr.attr,
	&iio_dev_attr_ex_temp_ain1_high_value.dev_attr.attr,
	&iio_dev_attr_ex_temp_ain1_low_value.dev_attr.attr,
	&iio_dev_attr_ain2_high_value.dev_attr.attr,
	&iio_dev_attr_ain2_low_value.dev_attr.attr,
	&iio_dev_attr_ain3_high_value.dev_attr.attr,
	&iio_dev_attr_ain3_low_value.dev_attr.attr,
	&iio_dev_attr_ain4_high_value.dev_attr.attr,
	&iio_dev_attr_ain4_low_value.dev_attr.attr,
	&iio_dev_attr_पूर्णांक_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7516_event_attribute_group = अणु
	.attrs = adt7516_event_attributes,
	.name = "events",
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adt7316_disable(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *dev_info = dev_get_drvdata(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस _adt7316_store_enabled(chip, 0);
पूर्ण

अटल पूर्णांक adt7316_enable(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *dev_info = dev_get_drvdata(dev);
	काष्ठा adt7316_chip_info *chip = iio_priv(dev_info);

	वापस _adt7316_store_enabled(chip, 1);
पूर्ण
EXPORT_SYMBOL_GPL(adt7316_pm_ops);
SIMPLE_DEV_PM_OPS(adt7316_pm_ops, adt7316_disable, adt7316_enable);
#पूर्ण_अगर

अटल स्थिर काष्ठा iio_info adt7316_info = अणु
	.attrs = &adt7316_attribute_group,
	.event_attrs = &adt7316_event_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info adt7516_info = अणु
	.attrs = &adt7516_attribute_group,
	.event_attrs = &adt7516_event_attribute_group,
पूर्ण;

/*
 * device probe and हटाओ
 */
पूर्णांक adt7316_probe(काष्ठा device *dev, काष्ठा adt7316_bus *bus,
		  स्थिर अक्षर *name)
अणु
	काष्ठा adt7316_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used क्रम device removal purposes */
	dev_set_drvdata(dev, indio_dev);

	chip->bus = *bus;

	अगर (name[4] == '3')
		chip->id = ID_ADT7316 + (name[6] - '6');
	अन्यथा अगर (name[4] == '5')
		chip->id = ID_ADT7516 + (name[6] - '6');
	अन्यथा
		वापस -ENODEV;

	अगर (chip->id == ID_ADT7316 || chip->id == ID_ADT7516)
		chip->dac_bits = 12;
	अन्यथा अगर (chip->id == ID_ADT7317 || chip->id == ID_ADT7517)
		chip->dac_bits = 10;
	अन्यथा
		chip->dac_bits = 8;

	chip->ldac_pin = devm_gpiod_get_optional(dev, "adi,ldac",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(chip->ldac_pin)) अणु
		ret = PTR_ERR(chip->ldac_pin);
		dev_err(dev, "Failed to request ldac GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!chip->ldac_pin) अणु
		chip->config3 |= ADT7316_DA_EN_VIA_DAC_LDAC;
		अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
			chip->config1 |= ADT7516_SEL_AIN3;
	पूर्ण
	chip->पूर्णांक_mask = ADT7316_TEMP_INT_MASK | ADT7316_VDD_INT_MASK;
	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		chip->पूर्णांक_mask |= ADT7516_AIN_INT_MASK;

	अगर ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		indio_dev->info = &adt7516_info;
	अन्यथा
		indio_dev->info = &adt7316_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (chip->bus.irq > 0) अणु
		ret = adt7316_setup_irq(indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG1, chip->config1);
	अगर (ret)
		वापस -EIO;

	ret = chip->bus.ग_लिखो(chip->bus.client, ADT7316_CONFIG3, chip->config3);
	अगर (ret)
		वापस -EIO;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		वापस ret;

	dev_info(dev, "%s temperature sensor, ADC and DAC registered.\n",
		 indio_dev->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(adt7316_probe);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADT7316/7/8 and ADT7516/7/9 digital temperature sensor, ADC and DAC driver");
MODULE_LICENSE("GPL v2");
