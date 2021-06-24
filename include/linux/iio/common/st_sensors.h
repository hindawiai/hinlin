<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics sensors library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#अगर_अघोषित ST_SENSORS_H
#घोषणा ST_SENSORS_H

#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>

#समावेश <linux/platक्रमm_data/st_sensors_pdata.h>

/*
 * Buffer size max हाल: 2bytes per channel, 3 channels in total +
 *			 8bytes बारtamp channel (s64)
 */
#घोषणा ST_SENSORS_MAX_BUFFER_SIZE		(ALIGN(2 * 3, माप(s64)) + \
						 माप(s64))

#घोषणा ST_SENSORS_ODR_LIST_MAX			10
#घोषणा ST_SENSORS_FULLSCALE_AVL_MAX		10

#घोषणा ST_SENSORS_NUMBER_ALL_CHANNELS		4
#घोषणा ST_SENSORS_ENABLE_ALL_AXIS		0x07
#घोषणा ST_SENSORS_SCAN_X			0
#घोषणा ST_SENSORS_SCAN_Y			1
#घोषणा ST_SENSORS_SCAN_Z			2
#घोषणा ST_SENSORS_DEFAULT_POWER_ON_VALUE	0x01
#घोषणा ST_SENSORS_DEFAULT_POWER_OFF_VALUE	0x00
#घोषणा ST_SENSORS_DEFAULT_WAI_ADDRESS		0x0f
#घोषणा ST_SENSORS_DEFAULT_AXIS_ADDR		0x20
#घोषणा ST_SENSORS_DEFAULT_AXIS_MASK		0x07
#घोषणा ST_SENSORS_DEFAULT_AXIS_N_BIT		3
#घोषणा ST_SENSORS_DEFAULT_STAT_ADDR		0x27

#घोषणा ST_SENSORS_MAX_NAME			17
#घोषणा ST_SENSORS_MAX_4WAI			8

#घोषणा ST_SENSORS_LSM_CHANNELS(device_type, mask, index, mod, \
					ch2, s, endian, rbits, sbits, addr) \
अणु \
	.type = device_type, \
	.modअगरied = mod, \
	.info_mask_separate = mask, \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_index = index, \
	.channel2 = ch2, \
	.address = addr, \
	.scan_type = अणु \
		.sign = s, \
		.realbits = rbits, \
		.shअगरt = sbits - rbits, \
		.storagebits = sbits, \
		.endianness = endian, \
	पूर्ण, \
पूर्ण

#घोषणा ST_SENSORS_DEV_ATTR_SAMP_FREQ_AVAIL() \
		IIO_DEV_ATTR_SAMP_FREQ_AVAIL( \
			st_sensors_sysfs_sampling_frequency_avail)

#घोषणा ST_SENSORS_DEV_ATTR_SCALE_AVAIL(name) \
		IIO_DEVICE_ATTR(name, S_IRUGO, \
			st_sensors_sysfs_scale_avail, शून्य , 0);

काष्ठा st_sensor_odr_avl अणु
	अचिन्हित पूर्णांक hz;
	u8 value;
पूर्ण;

काष्ठा st_sensor_odr अणु
	u8 addr;
	u8 mask;
	काष्ठा st_sensor_odr_avl odr_avl[ST_SENSORS_ODR_LIST_MAX];
पूर्ण;

काष्ठा st_sensor_घातer अणु
	u8 addr;
	u8 mask;
	u8 value_off;
	u8 value_on;
पूर्ण;

काष्ठा st_sensor_axis अणु
	u8 addr;
	u8 mask;
पूर्ण;

काष्ठा st_sensor_fullscale_avl अणु
	अचिन्हित पूर्णांक num;
	u8 value;
	अचिन्हित पूर्णांक gain;
	अचिन्हित पूर्णांक gain2;
पूर्ण;

काष्ठा st_sensor_fullscale अणु
	u8 addr;
	u8 mask;
	काष्ठा st_sensor_fullscale_avl fs_avl[ST_SENSORS_FULLSCALE_AVL_MAX];
पूर्ण;

काष्ठा st_sensor_sim अणु
	u8 addr;
	u8 value;
पूर्ण;

/**
 * काष्ठा st_sensor_bdu - ST sensor device block data update
 * @addr: address of the रेजिस्टर.
 * @mask: mask to ग_लिखो the block data update flag.
 */
काष्ठा st_sensor_bdu अणु
	u8 addr;
	u8 mask;
पूर्ण;

/**
 * काष्ठा st_sensor_das - ST sensor device data alignment selection
 * @addr: address of the रेजिस्टर.
 * @mask: mask to ग_लिखो the das flag क्रम left alignment.
 */
काष्ठा st_sensor_das अणु
	u8 addr;
	u8 mask;
पूर्ण;

/**
 * काष्ठा st_sensor_पूर्णांक_drdy - ST sensor device drdy line parameters
 * @addr: address of INT drdy रेजिस्टर.
 * @mask: mask to enable drdy line.
 * @addr_od: address to enable/disable Open Drain on the INT line.
 * @mask_od: mask to enable/disable Open Drain on the INT line.
 */
काष्ठा st_sensor_पूर्णांक_drdy अणु
	u8 addr;
	u8 mask;
	u8 addr_od;
	u8 mask_od;
पूर्ण;

/**
 * काष्ठा st_sensor_data_पढ़ोy_irq - ST sensor device data-पढ़ोy पूर्णांकerrupt
 * काष्ठा पूर्णांक1 - data-पढ़ोy configuration रेजिस्टर क्रम INT1 pin.
 * काष्ठा पूर्णांक2 - data-पढ़ोy configuration रेजिस्टर क्रम INT2 pin.
 * @addr_ihl: address to enable/disable active low on the INT lines.
 * @mask_ihl: mask to enable/disable active low on the INT lines.
 * काष्ठा stat_drdy - status रेजिस्टर of DRDY (data पढ़ोy) पूर्णांकerrupt.
 * काष्ठा ig1 - represents the Interrupt Generator 1 of sensors.
 * @en_addr: address of the enable ig1 रेजिस्टर.
 * @en_mask: mask to ग_लिखो the on/off value क्रम enable.
 */
काष्ठा st_sensor_data_पढ़ोy_irq अणु
	काष्ठा st_sensor_पूर्णांक_drdy पूर्णांक1;
	काष्ठा st_sensor_पूर्णांक_drdy पूर्णांक2;
	u8 addr_ihl;
	u8 mask_ihl;
	काष्ठा अणु
		u8 addr;
		u8 mask;
	पूर्ण stat_drdy;
	काष्ठा अणु
		u8 en_addr;
		u8 en_mask;
	पूर्ण ig1;
पूर्ण;

/**
 * काष्ठा st_sensor_settings - ST specअगरic sensor settings
 * @wai: Contents of WhoAmI रेजिस्टर.
 * @wai_addr: The address of WhoAmI रेजिस्टर.
 * @sensors_supported: List of supported sensors by काष्ठा itself.
 * @ch: IIO channels क्रम the sensor.
 * @odr: Output data rate रेजिस्टर and ODR list available.
 * @pw: Power रेजिस्टर of the sensor.
 * @enable_axis: Enable one or more axis of the sensor.
 * @fs: Full scale रेजिस्टर and full scale list available.
 * @bdu: Block data update रेजिस्टर.
 * @das: Data Alignment Selection रेजिस्टर.
 * @drdy_irq: Data पढ़ोy रेजिस्टर of the sensor.
 * @sim: SPI serial पूर्णांकerface mode रेजिस्टर of the sensor.
 * @multi_पढ़ो_bit: Use or not particular bit क्रम [I2C/SPI] multi-पढ़ो.
 * @booसमय: samples to discard when sensor passing from घातer-करोwn to घातer-up.
 */
काष्ठा st_sensor_settings अणु
	u8 wai;
	u8 wai_addr;
	अक्षर sensors_supported[ST_SENSORS_MAX_4WAI][ST_SENSORS_MAX_NAME];
	काष्ठा iio_chan_spec *ch;
	पूर्णांक num_ch;
	काष्ठा st_sensor_odr odr;
	काष्ठा st_sensor_घातer pw;
	काष्ठा st_sensor_axis enable_axis;
	काष्ठा st_sensor_fullscale fs;
	काष्ठा st_sensor_bdu bdu;
	काष्ठा st_sensor_das das;
	काष्ठा st_sensor_data_पढ़ोy_irq drdy_irq;
	काष्ठा st_sensor_sim sim;
	bool multi_पढ़ो_bit;
	अचिन्हित पूर्णांक booसमय;
पूर्ण;

/**
 * काष्ठा st_sensor_data - ST sensor device status
 * @dev: Poपूर्णांकer to instance of काष्ठा device (I2C or SPI).
 * @trig: The trigger in use by the core driver.
 * @sensor_settings: Poपूर्णांकer to the specअगरic sensor settings in use.
 * @current_fullscale: Maximum range of measure by the sensor.
 * @vdd: Poपूर्णांकer to sensor's Vdd घातer supply
 * @vdd_io: Poपूर्णांकer to sensor's Vdd-IO घातer supply
 * @regmap: Poपूर्णांकer to specअगरic sensor regmap configuration.
 * @enabled: Status of the sensor (false->off, true->on).
 * @odr: Output data rate of the sensor [Hz].
 * num_data_channels: Number of data channels used in buffer.
 * @drdy_पूर्णांक_pin: Redirect DRDY on pin 1 (1) or pin 2 (2).
 * @पूर्णांक_pin_खोलो_drain: Set the पूर्णांकerrupt/DRDY to खोलो drain.
 * @irq: the IRQ number.
 * @edge_irq: the IRQ triggers on edges and need special handling.
 * @hw_irq_trigger: अगर we're using the hardware पूर्णांकerrupt on the sensor.
 * @hw_बारtamp: Latest बारtamp from the पूर्णांकerrupt handler, when in use.
 * @buffer_data: Data used by buffer part.
 */
काष्ठा st_sensor_data अणु
	काष्ठा device *dev;
	काष्ठा iio_trigger *trig;
	काष्ठा iio_mount_matrix *mount_matrix;
	काष्ठा st_sensor_settings *sensor_settings;
	काष्ठा st_sensor_fullscale_avl *current_fullscale;
	काष्ठा regulator *vdd;
	काष्ठा regulator *vdd_io;
	काष्ठा regmap *regmap;

	bool enabled;

	अचिन्हित पूर्णांक odr;
	अचिन्हित पूर्णांक num_data_channels;

	u8 drdy_पूर्णांक_pin;
	bool पूर्णांक_pin_खोलो_drain;
	पूर्णांक irq;

	bool edge_irq;
	bool hw_irq_trigger;
	s64 hw_बारtamp;

	अक्षर buffer_data[ST_SENSORS_MAX_BUFFER_SIZE] ____cacheline_aligned;
पूर्ण;

#अगर_घोषित CONFIG_IIO_BUFFER
irqवापस_t st_sensors_trigger_handler(पूर्णांक irq, व्योम *p);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IIO_TRIGGER
पूर्णांक st_sensors_allocate_trigger(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_trigger_ops *trigger_ops);

व्योम st_sensors_deallocate_trigger(काष्ठा iio_dev *indio_dev);
पूर्णांक st_sensors_validate_device(काष्ठा iio_trigger *trig,
			       काष्ठा iio_dev *indio_dev);
#अन्यथा
अटल अंतरभूत पूर्णांक st_sensors_allocate_trigger(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_trigger_ops *trigger_ops)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम st_sensors_deallocate_trigger(काष्ठा iio_dev *indio_dev)
अणु
	वापस;
पूर्ण
#घोषणा st_sensors_validate_device शून्य
#पूर्ण_अगर

पूर्णांक st_sensors_init_sensor(काष्ठा iio_dev *indio_dev,
					काष्ठा st_sensors_platक्रमm_data *pdata);

पूर्णांक st_sensors_set_enable(काष्ठा iio_dev *indio_dev, bool enable);

पूर्णांक st_sensors_set_axis_enable(काष्ठा iio_dev *indio_dev, u8 axis_enable);

पूर्णांक st_sensors_घातer_enable(काष्ठा iio_dev *indio_dev);

व्योम st_sensors_घातer_disable(काष्ठा iio_dev *indio_dev);

पूर्णांक st_sensors_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
				  अचिन्हित reg, अचिन्हित ग_लिखोval,
				  अचिन्हित *पढ़ोval);

पूर्णांक st_sensors_set_odr(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक odr);

पूर्णांक st_sensors_set_dataपढ़ोy_irq(काष्ठा iio_dev *indio_dev, bool enable);

पूर्णांक st_sensors_set_fullscale_by_gain(काष्ठा iio_dev *indio_dev, पूर्णांक scale);

पूर्णांक st_sensors_पढ़ो_info_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val);

पूर्णांक st_sensors_get_settings_index(स्थिर अक्षर *name,
				  स्थिर काष्ठा st_sensor_settings *list,
				  स्थिर पूर्णांक list_length);

पूर्णांक st_sensors_verअगरy_id(काष्ठा iio_dev *indio_dev);

sमाप_प्रकार st_sensors_sysfs_sampling_frequency_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf);

sमाप_प्रकार st_sensors_sysfs_scale_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf);

व्योम st_sensors_dev_name_probe(काष्ठा device *dev, अक्षर *name, पूर्णांक len);

#पूर्ण_अगर /* ST_SENSORS_H */
