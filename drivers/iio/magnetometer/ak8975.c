<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A sensor driver क्रम the magnetometer AK8975.
 *
 * Magnetic compass sensor driver क्रम monitoring magnetic flux inक्रमmation.
 *
 * Copyright (c) 2010, NVIDIA Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/*
 * Register definitions, as well as various shअगरts and masks to get at the
 * inभागidual fields of the रेजिस्टरs.
 */
#घोषणा AK8975_REG_WIA			0x00
#घोषणा AK8975_DEVICE_ID		0x48

#घोषणा AK8975_REG_INFO			0x01

#घोषणा AK8975_REG_ST1			0x02
#घोषणा AK8975_REG_ST1_DRDY_SHIFT	0
#घोषणा AK8975_REG_ST1_DRDY_MASK	(1 << AK8975_REG_ST1_DRDY_SHIFT)

#घोषणा AK8975_REG_HXL			0x03
#घोषणा AK8975_REG_HXH			0x04
#घोषणा AK8975_REG_HYL			0x05
#घोषणा AK8975_REG_HYH			0x06
#घोषणा AK8975_REG_HZL			0x07
#घोषणा AK8975_REG_HZH			0x08
#घोषणा AK8975_REG_ST2			0x09
#घोषणा AK8975_REG_ST2_DERR_SHIFT	2
#घोषणा AK8975_REG_ST2_DERR_MASK	(1 << AK8975_REG_ST2_DERR_SHIFT)

#घोषणा AK8975_REG_ST2_HOFL_SHIFT	3
#घोषणा AK8975_REG_ST2_HOFL_MASK	(1 << AK8975_REG_ST2_HOFL_SHIFT)

#घोषणा AK8975_REG_CNTL			0x0A
#घोषणा AK8975_REG_CNTL_MODE_SHIFT	0
#घोषणा AK8975_REG_CNTL_MODE_MASK	(0xF << AK8975_REG_CNTL_MODE_SHIFT)
#घोषणा AK8975_REG_CNTL_MODE_POWER_DOWN	0x00
#घोषणा AK8975_REG_CNTL_MODE_ONCE	0x01
#घोषणा AK8975_REG_CNTL_MODE_SELF_TEST	0x08
#घोषणा AK8975_REG_CNTL_MODE_FUSE_ROM	0x0F

#घोषणा AK8975_REG_RSVC			0x0B
#घोषणा AK8975_REG_ASTC			0x0C
#घोषणा AK8975_REG_TS1			0x0D
#घोषणा AK8975_REG_TS2			0x0E
#घोषणा AK8975_REG_I2CDIS		0x0F
#घोषणा AK8975_REG_ASAX			0x10
#घोषणा AK8975_REG_ASAY			0x11
#घोषणा AK8975_REG_ASAZ			0x12

#घोषणा AK8975_MAX_REGS			AK8975_REG_ASAZ

/*
 * AK09912 Register definitions
 */
#घोषणा AK09912_REG_WIA1		0x00
#घोषणा AK09912_REG_WIA2		0x01
#घोषणा AK09912_DEVICE_ID		0x04
#घोषणा AK09911_DEVICE_ID		0x05

#घोषणा AK09911_REG_INFO1		0x02
#घोषणा AK09911_REG_INFO2		0x03

#घोषणा AK09912_REG_ST1			0x10

#घोषणा AK09912_REG_ST1_DRDY_SHIFT	0
#घोषणा AK09912_REG_ST1_DRDY_MASK	(1 << AK09912_REG_ST1_DRDY_SHIFT)

#घोषणा AK09912_REG_HXL			0x11
#घोषणा AK09912_REG_HXH			0x12
#घोषणा AK09912_REG_HYL			0x13
#घोषणा AK09912_REG_HYH			0x14
#घोषणा AK09912_REG_HZL			0x15
#घोषणा AK09912_REG_HZH			0x16
#घोषणा AK09912_REG_TMPS		0x17

#घोषणा AK09912_REG_ST2			0x18
#घोषणा AK09912_REG_ST2_HOFL_SHIFT	3
#घोषणा AK09912_REG_ST2_HOFL_MASK	(1 << AK09912_REG_ST2_HOFL_SHIFT)

#घोषणा AK09912_REG_CNTL1		0x30

#घोषणा AK09912_REG_CNTL2		0x31
#घोषणा AK09912_REG_CNTL_MODE_POWER_DOWN	0x00
#घोषणा AK09912_REG_CNTL_MODE_ONCE	0x01
#घोषणा AK09912_REG_CNTL_MODE_SELF_TEST	0x10
#घोषणा AK09912_REG_CNTL_MODE_FUSE_ROM	0x1F
#घोषणा AK09912_REG_CNTL2_MODE_SHIFT	0
#घोषणा AK09912_REG_CNTL2_MODE_MASK	(0x1F << AK09912_REG_CNTL2_MODE_SHIFT)

#घोषणा AK09912_REG_CNTL3		0x32

#घोषणा AK09912_REG_TS1			0x33
#घोषणा AK09912_REG_TS2			0x34
#घोषणा AK09912_REG_TS3			0x35
#घोषणा AK09912_REG_I2CDIS		0x36
#घोषणा AK09912_REG_TS4			0x37

#घोषणा AK09912_REG_ASAX		0x60
#घोषणा AK09912_REG_ASAY		0x61
#घोषणा AK09912_REG_ASAZ		0x62

#घोषणा AK09912_MAX_REGS		AK09912_REG_ASAZ

/*
 * Miscellaneous values.
 */
#घोषणा AK8975_MAX_CONVERSION_TIMEOUT	500
#घोषणा AK8975_CONVERSION_DONE_POLL_TIME 10
#घोषणा AK8975_DATA_READY_TIMEOUT	((100*HZ)/1000)

/*
 * Precalculate scale factor (in Gauss units) क्रम each axis and
 * store in the device data.
 *
 * This scale factor is axis-dependent, and is derived from 3 calibration
 * factors ASA(x), ASA(y), and ASA(z).
 *
 * These ASA values are पढ़ो from the sensor device at start of day, and
 * cached in the device context काष्ठा.
 *
 * Adjusting the flux value with the sensitivity adjusपंचांगent value should be
 * करोne via the following क्रमmula:
 *
 * Hadj = H * ( ( ( (ASA-128)*0.5 ) / 128 ) + 1 )
 * where H is the raw value, ASA is the sensitivity adjusपंचांगent, and Hadj
 * is the resultant adjusted value.
 *
 * We reduce the क्रमmula to:
 *
 * Hadj = H * (ASA + 128) / 256
 *
 * H is in the range of -4096 to 4095.  The magnetometer has a range of
 * +-1229uT.  To go from the raw value to uT is:
 *
 * HuT = H * 1229/4096, or roughly, 3/10.
 *
 * Since 1uT = 0.01 gauss, our final scale factor becomes:
 *
 * Hadj = H * ((ASA + 128) / 256) * 3/10 * 1/100
 * Hadj = H * ((ASA + 128) * 0.003) / 256
 *
 * Since ASA करोesn't change, we cache the resultant scale factor पूर्णांकo the
 * device context in ak8975_setup().
 *
 * Given we use IIO_VAL_INT_PLUS_MICRO bit when displaying the scale, we
 * multiply the stored scale value by 1e6.
 */
अटल दीर्घ ak8975_raw_to_gauss(u16 data)
अणु
	वापस (((दीर्घ)data + 128) * 3000) / 256;
पूर्ण

/*
 * For AK8963 and AK09911, same calculation, but the device is less sensitive:
 *
 * H is in the range of +-8190.  The magnetometer has a range of
 * +-4912uT.  To go from the raw value to uT is:
 *
 * HuT = H * 4912/8190, or roughly, 6/10, instead of 3/10.
 */

अटल दीर्घ ak8963_09911_raw_to_gauss(u16 data)
अणु
	वापस (((दीर्घ)data + 128) * 6000) / 256;
पूर्ण

/*
 * For AK09912, same calculation, except the device is more sensitive:
 *
 * H is in the range of -32752 to 32752.  The magnetometer has a range of
 * +-4912uT.  To go from the raw value to uT is:
 *
 * HuT = H * 4912/32752, or roughly, 3/20, instead of 3/10.
 */
अटल दीर्घ ak09912_raw_to_gauss(u16 data)
अणु
	वापस (((दीर्घ)data + 128) * 1500) / 256;
पूर्ण

/* Compatible Asahi Kasei Compass parts */
क्रमागत asahi_compass_chipset अणु
	AKXXXX		= 0,
	AK8975,
	AK8963,
	AK09911,
	AK09912,
पूर्ण;

क्रमागत ak_ctrl_reg_addr अणु
	ST1,
	ST2,
	CNTL,
	ASA_BASE,
	MAX_REGS,
	REGS_END,
पूर्ण;

क्रमागत ak_ctrl_reg_mask अणु
	ST1_DRDY,
	ST2_HOFL,
	ST2_DERR,
	CNTL_MODE,
	MASK_END,
पूर्ण;

क्रमागत ak_ctrl_mode अणु
	POWER_DOWN,
	MODE_ONCE,
	SELF_TEST,
	FUSE_ROM,
	MODE_END,
पूर्ण;

काष्ठा ak_def अणु
	क्रमागत asahi_compass_chipset type;
	दीर्घ (*raw_to_gauss)(u16 data);
	u16 range;
	u8 ctrl_regs[REGS_END];
	u8 ctrl_masks[MASK_END];
	u8 ctrl_modes[MODE_END];
	u8 data_regs[3];
पूर्ण;

अटल स्थिर काष्ठा ak_def ak_def_array[] = अणु
	अणु
		.type = AK8975,
		.raw_to_gauss = ak8975_raw_to_gauss,
		.range = 4096,
		.ctrl_regs = अणु
			AK8975_REG_ST1,
			AK8975_REG_ST2,
			AK8975_REG_CNTL,
			AK8975_REG_ASAX,
			AK8975_MAX_REGSपूर्ण,
		.ctrl_masks = अणु
			AK8975_REG_ST1_DRDY_MASK,
			AK8975_REG_ST2_HOFL_MASK,
			AK8975_REG_ST2_DERR_MASK,
			AK8975_REG_CNTL_MODE_MASKपूर्ण,
		.ctrl_modes = अणु
			AK8975_REG_CNTL_MODE_POWER_DOWN,
			AK8975_REG_CNTL_MODE_ONCE,
			AK8975_REG_CNTL_MODE_SELF_TEST,
			AK8975_REG_CNTL_MODE_FUSE_ROMपूर्ण,
		.data_regs = अणु
			AK8975_REG_HXL,
			AK8975_REG_HYL,
			AK8975_REG_HZLपूर्ण,
	पूर्ण,
	अणु
		.type = AK8963,
		.raw_to_gauss = ak8963_09911_raw_to_gauss,
		.range = 8190,
		.ctrl_regs = अणु
			AK8975_REG_ST1,
			AK8975_REG_ST2,
			AK8975_REG_CNTL,
			AK8975_REG_ASAX,
			AK8975_MAX_REGSपूर्ण,
		.ctrl_masks = अणु
			AK8975_REG_ST1_DRDY_MASK,
			AK8975_REG_ST2_HOFL_MASK,
			0,
			AK8975_REG_CNTL_MODE_MASKपूर्ण,
		.ctrl_modes = अणु
			AK8975_REG_CNTL_MODE_POWER_DOWN,
			AK8975_REG_CNTL_MODE_ONCE,
			AK8975_REG_CNTL_MODE_SELF_TEST,
			AK8975_REG_CNTL_MODE_FUSE_ROMपूर्ण,
		.data_regs = अणु
			AK8975_REG_HXL,
			AK8975_REG_HYL,
			AK8975_REG_HZLपूर्ण,
	पूर्ण,
	अणु
		.type = AK09911,
		.raw_to_gauss = ak8963_09911_raw_to_gauss,
		.range = 8192,
		.ctrl_regs = अणु
			AK09912_REG_ST1,
			AK09912_REG_ST2,
			AK09912_REG_CNTL2,
			AK09912_REG_ASAX,
			AK09912_MAX_REGSपूर्ण,
		.ctrl_masks = अणु
			AK09912_REG_ST1_DRDY_MASK,
			AK09912_REG_ST2_HOFL_MASK,
			0,
			AK09912_REG_CNTL2_MODE_MASKपूर्ण,
		.ctrl_modes = अणु
			AK09912_REG_CNTL_MODE_POWER_DOWN,
			AK09912_REG_CNTL_MODE_ONCE,
			AK09912_REG_CNTL_MODE_SELF_TEST,
			AK09912_REG_CNTL_MODE_FUSE_ROMपूर्ण,
		.data_regs = अणु
			AK09912_REG_HXL,
			AK09912_REG_HYL,
			AK09912_REG_HZLपूर्ण,
	पूर्ण,
	अणु
		.type = AK09912,
		.raw_to_gauss = ak09912_raw_to_gauss,
		.range = 32752,
		.ctrl_regs = अणु
			AK09912_REG_ST1,
			AK09912_REG_ST2,
			AK09912_REG_CNTL2,
			AK09912_REG_ASAX,
			AK09912_MAX_REGSपूर्ण,
		.ctrl_masks = अणु
			AK09912_REG_ST1_DRDY_MASK,
			AK09912_REG_ST2_HOFL_MASK,
			0,
			AK09912_REG_CNTL2_MODE_MASKपूर्ण,
		.ctrl_modes = अणु
			AK09912_REG_CNTL_MODE_POWER_DOWN,
			AK09912_REG_CNTL_MODE_ONCE,
			AK09912_REG_CNTL_MODE_SELF_TEST,
			AK09912_REG_CNTL_MODE_FUSE_ROMपूर्ण,
		.data_regs = अणु
			AK09912_REG_HXL,
			AK09912_REG_HYL,
			AK09912_REG_HZLपूर्ण,
	पूर्ण
पूर्ण;

/*
 * Per-instance context data क्रम the device.
 */
काष्ठा ak8975_data अणु
	काष्ठा i2c_client	*client;
	स्थिर काष्ठा ak_def	*def;
	काष्ठा mutex		lock;
	u8			asa[3];
	दीर्घ			raw_to_gauss[3];
	काष्ठा gpio_desc	*eoc_gpiod;
	काष्ठा gpio_desc	*reset_gpiod;
	पूर्णांक			eoc_irq;
	रुको_queue_head_t	data_पढ़ोy_queue;
	अचिन्हित दीर्घ		flags;
	u8			cntl_cache;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regulator	*vdd;
	काष्ठा regulator	*vid;

	/* Ensure natural alignment of बारtamp */
	काष्ठा अणु
		s16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

/* Enable attached घातer regulator अगर any. */
अटल पूर्णांक ak8975_घातer_on(स्थिर काष्ठा ak8975_data *data)
अणु
	पूर्णांक ret;

	ret = regulator_enable(data->vdd);
	अगर (ret) अणु
		dev_warn(&data->client->dev,
			 "Failed to enable specified Vdd supply\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(data->vid);
	अगर (ret) अणु
		dev_warn(&data->client->dev,
			 "Failed to enable specified Vid supply\n");
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(data->reset_gpiod, 0);

	/*
	 * According to the datasheet the घातer supply rise समय is 200us
	 * and the minimum रुको समय beक्रमe mode setting is 100us, in
	 * total 300us. Add some margin and say minimum 500us here.
	 */
	usleep_range(500, 1000);
	वापस 0;
पूर्ण

/* Disable attached घातer regulator अगर any. */
अटल व्योम ak8975_घातer_off(स्थिर काष्ठा ak8975_data *data)
अणु
	gpiod_set_value_cansleep(data->reset_gpiod, 1);

	regulator_disable(data->vid);
	regulator_disable(data->vdd);
पूर्ण

/*
 * Return 0 अगर the i2c device is the one we expect.
 * वापस a negative error number otherwise
 */
अटल पूर्णांक ak8975_who_i_am(काष्ठा i2c_client *client,
			   क्रमागत asahi_compass_chipset type)
अणु
	u8 wia_val[2];
	पूर्णांक ret;

	/*
	 * Signature क्रम each device:
	 * Device   |  WIA1      |  WIA2
	 * AK09912  |  DEVICE_ID |  AK09912_DEVICE_ID
	 * AK09911  |  DEVICE_ID |  AK09911_DEVICE_ID
	 * AK8975   |  DEVICE_ID |  NA
	 * AK8963   |  DEVICE_ID |  NA
	 */
	ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(
			client, AK09912_REG_WIA1, 2, wia_val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading WIA\n");
		वापस ret;
	पूर्ण

	अगर (wia_val[0] != AK8975_DEVICE_ID)
		वापस -ENODEV;

	चयन (type) अणु
	हाल AK8975:
	हाल AK8963:
		वापस 0;
	हाल AK09911:
		अगर (wia_val[1] == AK09911_DEVICE_ID)
			वापस 0;
		अवरोध;
	हाल AK09912:
		अगर (wia_val[1] == AK09912_DEVICE_ID)
			वापस 0;
		अवरोध;
	शेष:
		dev_err(&client->dev, "Type %d unknown\n", type);
	पूर्ण
	वापस -ENODEV;
पूर्ण

/*
 * Helper function to ग_लिखो to CNTL रेजिस्टर.
 */
अटल पूर्णांक ak8975_set_mode(काष्ठा ak8975_data *data, क्रमागत ak_ctrl_mode mode)
अणु
	u8 regval;
	पूर्णांक ret;

	regval = (data->cntl_cache & ~data->def->ctrl_masks[CNTL_MODE]) |
		 data->def->ctrl_modes[mode];
	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					data->def->ctrl_regs[CNTL], regval);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण
	data->cntl_cache = regval;
	/* After mode change रुको atleast 100us */
	usleep_range(100, 500);

	वापस 0;
पूर्ण

/*
 * Handle data पढ़ोy irq
 */
अटल irqवापस_t ak8975_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ak8975_data *ak8975 = data;

	set_bit(0, &ak8975->flags);
	wake_up(&ak8975->data_पढ़ोy_queue);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Install data पढ़ोy पूर्णांकerrupt handler
 */
अटल पूर्णांक ak8975_setup_irq(काष्ठा ak8975_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक rc;
	पूर्णांक irq;

	init_रुकोqueue_head(&data->data_पढ़ोy_queue);
	clear_bit(0, &data->flags);
	अगर (client->irq)
		irq = client->irq;
	अन्यथा
		irq = gpiod_to_irq(data->eoc_gpiod);

	rc = devm_request_irq(&client->dev, irq, ak8975_irq_handler,
			      IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			      dev_name(&client->dev), data);
	अगर (rc < 0) अणु
		dev_err(&client->dev, "irq %d request failed: %d\n", irq, rc);
		वापस rc;
	पूर्ण

	data->eoc_irq = irq;

	वापस rc;
पूर्ण


/*
 * Perक्रमm some start-of-day setup, including पढ़ोing the asa calibration
 * values and caching them.
 */
अटल पूर्णांक ak8975_setup(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ak8975_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Write the fused rom access mode. */
	ret = ak8975_set_mode(data, FUSE_ROM);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error in setting fuse access mode\n");
		वापस ret;
	पूर्ण

	/* Get asa data and store in the device data. */
	ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(
			client, data->def->ctrl_regs[ASA_BASE],
			3, data->asa);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Not able to read asa data\n");
		वापस ret;
	पूर्ण

	/* After पढ़ोing fuse ROM data set घातer-करोwn mode */
	ret = ak8975_set_mode(data, POWER_DOWN);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error in setting power-down mode\n");
		वापस ret;
	पूर्ण

	अगर (data->eoc_gpiod || client->irq > 0) अणु
		ret = ak8975_setup_irq(data);
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"Error setting data ready interrupt\n");
			वापस ret;
		पूर्ण
	पूर्ण

	data->raw_to_gauss[0] = data->def->raw_to_gauss(data->asa[0]);
	data->raw_to_gauss[1] = data->def->raw_to_gauss(data->asa[1]);
	data->raw_to_gauss[2] = data->def->raw_to_gauss(data->asa[2]);

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_conversion_complete_gpio(काष्ठा ak8975_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	u32 समयout_ms = AK8975_MAX_CONVERSION_TIMEOUT;
	पूर्णांक ret;

	/* Wait क्रम the conversion to complete. */
	जबतक (समयout_ms) अणु
		msleep(AK8975_CONVERSION_DONE_POLL_TIME);
		अगर (gpiod_get_value(data->eoc_gpiod))
			अवरोध;
		समयout_ms -= AK8975_CONVERSION_DONE_POLL_TIME;
	पूर्ण
	अगर (!समयout_ms) अणु
		dev_err(&client->dev, "Conversion timeout happened\n");
		वापस -EINVAL;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, data->def->ctrl_regs[ST1]);
	अगर (ret < 0)
		dev_err(&client->dev, "Error in reading ST1\n");

	वापस ret;
पूर्ण

अटल पूर्णांक रुको_conversion_complete_polled(काष्ठा ak8975_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	u8 पढ़ो_status;
	u32 समयout_ms = AK8975_MAX_CONVERSION_TIMEOUT;
	पूर्णांक ret;

	/* Wait क्रम the conversion to complete. */
	जबतक (समयout_ms) अणु
		msleep(AK8975_CONVERSION_DONE_POLL_TIME);
		ret = i2c_smbus_पढ़ो_byte_data(client,
					       data->def->ctrl_regs[ST1]);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Error in reading ST1\n");
			वापस ret;
		पूर्ण
		पढ़ो_status = ret;
		अगर (पढ़ो_status)
			अवरोध;
		समयout_ms -= AK8975_CONVERSION_DONE_POLL_TIME;
	पूर्ण
	अगर (!समयout_ms) अणु
		dev_err(&client->dev, "Conversion timeout happened\n");
		वापस -EINVAL;
	पूर्ण

	वापस पढ़ो_status;
पूर्ण

/* Returns 0 अगर the end of conversion पूर्णांकerrupt occured or -ETIME otherwise */
अटल पूर्णांक रुको_conversion_complete_पूर्णांकerrupt(काष्ठा ak8975_data *data)
अणु
	पूर्णांक ret;

	ret = रुको_event_समयout(data->data_पढ़ोy_queue,
				 test_bit(0, &data->flags),
				 AK8975_DATA_READY_TIMEOUT);
	clear_bit(0, &data->flags);

	वापस ret > 0 ? 0 : -ETIME;
पूर्ण

अटल पूर्णांक ak8975_start_पढ़ो_axis(काष्ठा ak8975_data *data,
				  स्थिर काष्ठा i2c_client *client)
अणु
	/* Set up the device क्रम taking a sample. */
	पूर्णांक ret = ak8975_set_mode(data, MODE_ONCE);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error in setting operating mode\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम the conversion to complete. */
	अगर (data->eoc_irq)
		ret = रुको_conversion_complete_पूर्णांकerrupt(data);
	अन्यथा अगर (data->eoc_gpiod)
		ret = रुको_conversion_complete_gpio(data);
	अन्यथा
		ret = रुको_conversion_complete_polled(data);
	अगर (ret < 0)
		वापस ret;

	/* This will be executed only क्रम non-पूर्णांकerrupt based रुकोing हाल */
	अगर (ret & data->def->ctrl_masks[ST1_DRDY]) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client,
					       data->def->ctrl_regs[ST2]);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Error in reading ST2\n");
			वापस ret;
		पूर्ण
		अगर (ret & (data->def->ctrl_masks[ST2_DERR] |
			   data->def->ctrl_masks[ST2_HOFL])) अणु
			dev_err(&client->dev, "ST2 status error 0x%x\n", ret);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Retrieve raw flux value क्रम one of the x, y, or z axis.  */
अटल पूर्णांक ak8975_पढ़ो_axis(काष्ठा iio_dev *indio_dev, पूर्णांक index, पूर्णांक *val)
अणु
	काष्ठा ak8975_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा i2c_client *client = data->client;
	स्थिर काष्ठा ak_def *def = data->def;
	__le16 rval;
	u16 buff;
	पूर्णांक ret;

	pm_runसमय_get_sync(&data->client->dev);

	mutex_lock(&data->lock);

	ret = ak8975_start_पढ़ो_axis(data, client);
	अगर (ret)
		जाओ निकास;

	ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(
			client, def->data_regs[index],
			माप(rval), (u8*)&rval);
	अगर (ret < 0)
		जाओ निकास;

	mutex_unlock(&data->lock);

	pm_runसमय_mark_last_busy(&data->client->dev);
	pm_runसमय_put_स्वतःsuspend(&data->client->dev);

	/* Swap bytes and convert to valid range. */
	buff = le16_to_cpu(rval);
	*val = clamp_t(s16, buff, -def->range, def->range);
	वापस IIO_VAL_INT;

निकास:
	mutex_unlock(&data->lock);
	dev_err(&client->dev, "Error in reading axis\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ak8975_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा ak8975_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस ak8975_पढ़ो_axis(indio_dev, chan->address, val);
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = data->raw_to_gauss[chan->address];
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
ak8975_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ak8975_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ak8975_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, ak8975_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा AK8975_CHANNEL(axis, index)					\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			     BIT(IIO_CHAN_INFO_SCALE),			\
		.address = index,					\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
			.endianness = IIO_CPU				\
		पूर्ण,							\
		.ext_info = ak8975_ext_info,				\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ak8975_channels[] = अणु
	AK8975_CHANNEL(X, 0), AK8975_CHANNEL(Y, 1), AK8975_CHANNEL(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ak8975_scan_masks[] = अणु 0x7, 0 पूर्ण;

अटल स्थिर काष्ठा iio_info ak8975_info = अणु
	.पढ़ो_raw = &ak8975_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id ak_acpi_match[] = अणु
	अणु"AK8975", AK8975पूर्ण,
	अणु"AK8963", AK8963पूर्ण,
	अणु"INVN6500", AK8963पूर्ण,
	अणु"AK009911", AK09911पूर्ण,
	अणु"AK09911", AK09911पूर्ण,
	अणु"AKM9911", AK09911पूर्ण,
	अणु"AK09912", AK09912पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ak_acpi_match);

अटल व्योम ak8975_fill_buffer(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ak8975_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा i2c_client *client = data->client;
	स्थिर काष्ठा ak_def *def = data->def;
	पूर्णांक ret;
	__le16 fval[3];

	mutex_lock(&data->lock);

	ret = ak8975_start_पढ़ो_axis(data, client);
	अगर (ret)
		जाओ unlock;

	/*
	 * For each axis, पढ़ो the flux value from the appropriate रेजिस्टर
	 * (the रेजिस्टर is specअगरied in the iio device attributes).
	 */
	ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(client,
							def->data_regs[0],
							3 * माप(fval[0]),
							(u8 *)fval);
	अगर (ret < 0)
		जाओ unlock;

	mutex_unlock(&data->lock);

	/* Clamp to valid range. */
	data->scan.channels[0] = clamp_t(s16, le16_to_cpu(fval[0]), -def->range, def->range);
	data->scan.channels[1] = clamp_t(s16, le16_to_cpu(fval[1]), -def->range, def->range);
	data->scan.channels[2] = clamp_t(s16, le16_to_cpu(fval[2]), -def->range, def->range);

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   iio_get_समय_ns(indio_dev));

	वापस;

unlock:
	mutex_unlock(&data->lock);
	dev_err(&client->dev, "Error in reading axes block\n");
पूर्ण

अटल irqवापस_t ak8975_handle_trigger(पूर्णांक irq, व्योम *p)
अणु
	स्थिर काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;

	ak8975_fill_buffer(indio_dev);
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ak8975_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ak8975_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा gpio_desc *eoc_gpiod;
	काष्ठा gpio_desc *reset_gpiod;
	स्थिर व्योम *match;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	क्रमागत asahi_compass_chipset chipset;
	स्थिर अक्षर *name = शून्य;

	/*
	 * Grab and set up the supplied GPIO.
	 * We may not have a GPIO based IRQ to scan, that is fine, we will
	 * poll अगर so.
	 */
	eoc_gpiod = devm_gpiod_get_optional(&client->dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(eoc_gpiod))
		वापस PTR_ERR(eoc_gpiod);
	अगर (eoc_gpiod)
		gpiod_set_consumer_name(eoc_gpiod, "ak_8975");

	/*
	 * According to AK09911 datasheet, अगर reset GPIO is provided then
	 * deनिश्चित reset on ak8975_घातer_on() and निश्चित reset on
	 * ak8975_घातer_off().
	 */
	reset_gpiod = devm_gpiod_get_optional(&client->dev,
					      "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset_gpiod))
		वापस PTR_ERR(reset_gpiod);

	/* Register with IIO */
	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->eoc_gpiod = eoc_gpiod;
	data->reset_gpiod = reset_gpiod;
	data->eoc_irq = 0;

	err = iio_पढ़ो_mount_matrix(&client->dev, "mount-matrix", &data->orientation);
	अगर (err)
		वापस err;

	/* id will be शून्य when क्रमागतerated via ACPI */
	match = device_get_match_data(&client->dev);
	अगर (match) अणु
		chipset = (क्रमागत asahi_compass_chipset)(match);
		name = dev_name(&client->dev);
	पूर्ण अन्यथा अगर (id) अणु
		chipset = (क्रमागत asahi_compass_chipset)(id->driver_data);
		name = id->name;
	पूर्ण अन्यथा
		वापस -ENOSYS;

	क्रम (i = 0; i < ARRAY_SIZE(ak_def_array); i++)
		अगर (ak_def_array[i].type == chipset)
			अवरोध;

	अगर (i == ARRAY_SIZE(ak_def_array)) अणु
		dev_err(&client->dev, "AKM device type unsupported: %d\n",
			chipset);
		वापस -ENODEV;
	पूर्ण

	data->def = &ak_def_array[i];

	/* Fetch the regulators */
	data->vdd = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(data->vdd))
		वापस PTR_ERR(data->vdd);
	data->vid = devm_regulator_get(&client->dev, "vid");
	अगर (IS_ERR(data->vid))
		वापस PTR_ERR(data->vid);

	err = ak8975_घातer_on(data);
	अगर (err)
		वापस err;

	err = ak8975_who_i_am(client, data->def->type);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unexpected device\n");
		जाओ घातer_off;
	पूर्ण
	dev_dbg(&client->dev, "Asahi compass chip %s\n", name);

	/* Perक्रमm some basic start-of-day setup of the device. */
	err = ak8975_setup(client);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s initialization fails\n", name);
		जाओ घातer_off;
	पूर्ण

	mutex_init(&data->lock);
	indio_dev->channels = ak8975_channels;
	indio_dev->num_channels = ARRAY_SIZE(ak8975_channels);
	indio_dev->info = &ak8975_info;
	indio_dev->available_scan_masks = ak8975_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = name;

	err = iio_triggered_buffer_setup(indio_dev, शून्य, ak8975_handle_trigger,
					 शून्य);
	अगर (err) अणु
		dev_err(&client->dev, "triggered buffer setup failed\n");
		जाओ घातer_off;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err) अणु
		dev_err(&client->dev, "device register failed\n");
		जाओ cleanup_buffer;
	पूर्ण

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(&client->dev);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	/*
	 * The device comes online in 500us, so add two orders of magnitude
	 * of delay beक्रमe स्वतःsuspending: 50 ms.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_put(&client->dev);

	वापस 0;

cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
घातer_off:
	ak8975_घातer_off(data);
	वापस err;
पूर्ण

अटल पूर्णांक ak8975_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ak8975_data *data = iio_priv(indio_dev);

	pm_runसमय_get_sync(&client->dev);
	pm_runसमय_put_noidle(&client->dev);
	pm_runसमय_disable(&client->dev);
	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	ak8975_set_mode(data, POWER_DOWN);
	ak8975_घातer_off(data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ak8975_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ak8975_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Set the device in घातer करोwn अगर it wasn't alपढ़ोy */
	ret = ak8975_set_mode(data, POWER_DOWN);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error in setting power-down mode\n");
		वापस ret;
	पूर्ण
	/* Next cut the regulators */
	ak8975_घातer_off(data);

	वापस 0;
पूर्ण

अटल पूर्णांक ak8975_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ak8975_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Take up the regulators */
	ak8975_घातer_on(data);
	/*
	 * We come up in घातered करोwn mode, the पढ़ोing routines will
	 * put us in the mode to पढ़ो values later.
	 */
	ret = ak8975_set_mode(data, POWER_DOWN);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error in setting power-down mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops ak8975_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(ak8975_runसमय_suspend,
			   ak8975_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ak8975_id[] = अणु
	अणु"ak8975", AK8975पूर्ण,
	अणु"ak8963", AK8963पूर्ण,
	अणु"AK8963", AK8963पूर्ण,
	अणु"ak09911", AK09911पूर्ण,
	अणु"ak09912", AK09912पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ak8975_id);

अटल स्थिर काष्ठा of_device_id ak8975_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak8975", पूर्ण,
	अणु .compatible = "ak8975", पूर्ण,
	अणु .compatible = "asahi-kasei,ak8963", पूर्ण,
	अणु .compatible = "ak8963", पूर्ण,
	अणु .compatible = "asahi-kasei,ak09911", पूर्ण,
	अणु .compatible = "ak09911", पूर्ण,
	अणु .compatible = "asahi-kasei,ak09912", पूर्ण,
	अणु .compatible = "ak09912", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak8975_of_match);

अटल काष्ठा i2c_driver ak8975_driver = अणु
	.driver = अणु
		.name	= "ak8975",
		.pm = &ak8975_dev_pm_ops,
		.of_match_table = ak8975_of_match,
		.acpi_match_table = ak_acpi_match,
	पूर्ण,
	.probe		= ak8975_probe,
	.हटाओ		= ak8975_हटाओ,
	.id_table	= ak8975_id,
पूर्ण;
module_i2c_driver(ak8975_driver);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("AK8975 magnetometer driver");
MODULE_LICENSE("GPL");
