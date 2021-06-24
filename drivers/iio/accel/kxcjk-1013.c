<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KXCJK-1013 3-axis accelerometer driver
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/accel/kxcjk_1013.h>

#घोषणा KXCJK1013_DRV_NAME "kxcjk1013"
#घोषणा KXCJK1013_IRQ_NAME "kxcjk1013_event"

#घोषणा KXTF9_REG_HP_XOUT_L		0x00
#घोषणा KXTF9_REG_HP_XOUT_H		0x01
#घोषणा KXTF9_REG_HP_YOUT_L		0x02
#घोषणा KXTF9_REG_HP_YOUT_H		0x03
#घोषणा KXTF9_REG_HP_ZOUT_L		0x04
#घोषणा KXTF9_REG_HP_ZOUT_H		0x05

#घोषणा KXCJK1013_REG_XOUT_L		0x06
/*
 * From low byte X axis रेजिस्टर, all the other addresses of Y and Z can be
 * obtained by just applying axis offset. The following axis defines are just
 * provide clarity, but not used.
 */
#घोषणा KXCJK1013_REG_XOUT_H		0x07
#घोषणा KXCJK1013_REG_YOUT_L		0x08
#घोषणा KXCJK1013_REG_YOUT_H		0x09
#घोषणा KXCJK1013_REG_ZOUT_L		0x0A
#घोषणा KXCJK1013_REG_ZOUT_H		0x0B

#घोषणा KXCJK1013_REG_DCST_RESP		0x0C
#घोषणा KXCJK1013_REG_WHO_AM_I		0x0F
#घोषणा KXTF9_REG_TILT_POS_CUR		0x10
#घोषणा KXTF9_REG_TILT_POS_PREV		0x11
#घोषणा KXTF9_REG_INT_SRC1		0x15
#घोषणा KXCJK1013_REG_INT_SRC1		0x16	/* compatible, but called INT_SRC2 in KXTF9 ds */
#घोषणा KXCJK1013_REG_INT_SRC2		0x17
#घोषणा KXCJK1013_REG_STATUS_REG	0x18
#घोषणा KXCJK1013_REG_INT_REL		0x1A
#घोषणा KXCJK1013_REG_CTRL1		0x1B
#घोषणा KXTF9_REG_CTRL2			0x1C
#घोषणा KXCJK1013_REG_CTRL2		0x1D	/* mostly compatible, CTRL_REG3 in KTXF9 ds */
#घोषणा KXCJK1013_REG_INT_CTRL1		0x1E
#घोषणा KXCJK1013_REG_INT_CTRL2		0x1F
#घोषणा KXTF9_REG_INT_CTRL3		0x20
#घोषणा KXCJK1013_REG_DATA_CTRL		0x21
#घोषणा KXTF9_REG_TILT_TIMER		0x28
#घोषणा KXCJK1013_REG_WAKE_TIMER	0x29
#घोषणा KXTF9_REG_TDT_TIMER		0x2B
#घोषणा KXTF9_REG_TDT_THRESH_H		0x2C
#घोषणा KXTF9_REG_TDT_THRESH_L		0x2D
#घोषणा KXTF9_REG_TDT_TAP_TIMER		0x2E
#घोषणा KXTF9_REG_TDT_TOTAL_TIMER	0x2F
#घोषणा KXTF9_REG_TDT_LATENCY_TIMER	0x30
#घोषणा KXTF9_REG_TDT_WINDOW_TIMER	0x31
#घोषणा KXCJK1013_REG_SELF_TEST		0x3A
#घोषणा KXTF9_REG_WAKE_THRESH		0x5A
#घोषणा KXTF9_REG_TILT_ANGLE		0x5C
#घोषणा KXTF9_REG_HYST_SET		0x5F
#घोषणा KXCJK1013_REG_WAKE_THRES	0x6A

#घोषणा KXCJK1013_REG_CTRL1_BIT_PC1	BIT(7)
#घोषणा KXCJK1013_REG_CTRL1_BIT_RES	BIT(6)
#घोषणा KXCJK1013_REG_CTRL1_BIT_DRDY	BIT(5)
#घोषणा KXCJK1013_REG_CTRL1_BIT_GSEL1	BIT(4)
#घोषणा KXCJK1013_REG_CTRL1_BIT_GSEL0	BIT(3)
#घोषणा KXCJK1013_REG_CTRL1_BIT_WUFE	BIT(1)

#घोषणा KXCJK1013_REG_INT_CTRL1_BIT_IEU	BIT(2)	/* KXTF9 */
#घोषणा KXCJK1013_REG_INT_CTRL1_BIT_IEL	BIT(3)
#घोषणा KXCJK1013_REG_INT_CTRL1_BIT_IEA	BIT(4)
#घोषणा KXCJK1013_REG_INT_CTRL1_BIT_IEN	BIT(5)

#घोषणा KXTF9_REG_TILT_BIT_LEFT_EDGE	BIT(5)
#घोषणा KXTF9_REG_TILT_BIT_RIGHT_EDGE	BIT(4)
#घोषणा KXTF9_REG_TILT_BIT_LOWER_EDGE	BIT(3)
#घोषणा KXTF9_REG_TILT_BIT_UPPER_EDGE	BIT(2)
#घोषणा KXTF9_REG_TILT_BIT_FACE_DOWN	BIT(1)
#घोषणा KXTF9_REG_TILT_BIT_FACE_UP	BIT(0)

#घोषणा KXCJK1013_DATA_MASK_12_BIT	0x0FFF
#घोषणा KXCJK1013_MAX_STARTUP_TIME_US	100000

#घोषणा KXCJK1013_SLEEP_DELAY_MS	2000

#घोषणा KXCJK1013_REG_INT_SRC1_BIT_TPS	BIT(0)	/* KXTF9 */
#घोषणा KXCJK1013_REG_INT_SRC1_BIT_WUFS	BIT(1)
#घोषणा KXCJK1013_REG_INT_SRC1_MASK_TDTS	(BIT(2) | BIT(3))	/* KXTF9 */
#घोषणा KXCJK1013_REG_INT_SRC1_TAP_NONE		0
#घोषणा KXCJK1013_REG_INT_SRC1_TAP_SINGLE		BIT(2)
#घोषणा KXCJK1013_REG_INT_SRC1_TAP_DOUBLE		BIT(3)
#घोषणा KXCJK1013_REG_INT_SRC1_BIT_DRDY	BIT(4)

/* KXCJK: INT_SOURCE2: motion detect, KXTF9: INT_SRC_REG1: tap detect */
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_ZP	BIT(0)
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_ZN	BIT(1)
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_YP	BIT(2)
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_YN	BIT(3)
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_XP	BIT(4)
#घोषणा KXCJK1013_REG_INT_SRC2_BIT_XN	BIT(5)

#घोषणा KXCJK1013_DEFAULT_WAKE_THRES	1

क्रमागत kx_chipset अणु
	KXCJK1013,
	KXCJ91008,
	KXTJ21009,
	KXTF9,
	KX_MAX_CHIPS /* this must be last */
पूर्ण;

क्रमागत kx_acpi_type अणु
	ACPI_GENERIC,
	ACPI_SMO8500,
	ACPI_KIOX010A,
पूर्ण;

काष्ठा kxcjk1013_data अणु
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा i2c_client *client;
	काष्ठा iio_trigger *dपढ़ोy_trig;
	काष्ठा iio_trigger *motion_trig;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा mutex mutex;
	s16 buffer[8];
	u8 odr_bits;
	u8 range;
	पूर्णांक wake_thres;
	पूर्णांक wake_dur;
	bool active_high_पूर्णांकr;
	bool dपढ़ोy_trigger_on;
	पूर्णांक ev_enable_state;
	bool motion_trigger_on;
	पूर्णांक64_t बारtamp;
	क्रमागत kx_chipset chipset;
	क्रमागत kx_acpi_type acpi_type;
पूर्ण;

क्रमागत kxcjk1013_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
पूर्ण;

क्रमागत kxcjk1013_mode अणु
	STANDBY,
	OPERATION,
पूर्ण;

क्रमागत kxcjk1013_range अणु
	KXCJK1013_RANGE_2G,
	KXCJK1013_RANGE_4G,
	KXCJK1013_RANGE_8G,
पूर्ण;

काष्ठा kx_odr_map अणु
	पूर्णांक val;
	पूर्णांक val2;
	पूर्णांक odr_bits;
	पूर्णांक wuf_bits;
पूर्ण;

अटल स्थिर काष्ठा kx_odr_map samp_freq_table[] = अणु
	अणु 0, 781000, 0x08, 0x00 पूर्ण,
	अणु 1, 563000, 0x09, 0x01 पूर्ण,
	अणु 3, 125000, 0x0A, 0x02 पूर्ण,
	अणु 6, 250000, 0x0B, 0x03 पूर्ण,
	अणु 12, 500000, 0x00, 0x04 पूर्ण,
	अणु 25, 0, 0x01, 0x05 पूर्ण,
	अणु 50, 0, 0x02, 0x06 पूर्ण,
	अणु 100, 0, 0x03, 0x06 पूर्ण,
	अणु 200, 0, 0x04, 0x06 पूर्ण,
	अणु 400, 0, 0x05, 0x06 पूर्ण,
	अणु 800, 0, 0x06, 0x06 पूर्ण,
	अणु 1600, 0, 0x07, 0x06 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर kxcjk1013_samp_freq_avail =
	"0.781000 1.563000 3.125000 6.250000 12.500000 25 50 100 200 400 800 1600";

अटल स्थिर काष्ठा kx_odr_map kxtf9_samp_freq_table[] = अणु
	अणु 25, 0, 0x01, 0x00 पूर्ण,
	अणु 50, 0, 0x02, 0x01 पूर्ण,
	अणु 100, 0, 0x03, 0x01 पूर्ण,
	अणु 200, 0, 0x04, 0x01 पूर्ण,
	अणु 400, 0, 0x05, 0x01 पूर्ण,
	अणु 800, 0, 0x06, 0x01 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर kxtf9_samp_freq_avail =
	"25 50 100 200 400 800";

/* Refer to section 4 of the specअगरication */
अटल स्थिर काष्ठा अणु
	पूर्णांक odr_bits;
	पूर्णांक usec;
पूर्ण odr_start_up_बार[KX_MAX_CHIPS][12] = अणु
	/* KXCJK-1013 */
	अणु
		अणु0x08, 100000पूर्ण,
		अणु0x09, 100000पूर्ण,
		अणु0x0A, 100000पूर्ण,
		अणु0x0B, 100000पूर्ण,
		अणु0, 80000पूर्ण,
		अणु0x01, 41000पूर्ण,
		अणु0x02, 21000पूर्ण,
		अणु0x03, 11000पूर्ण,
		अणु0x04, 6400पूर्ण,
		अणु0x05, 3900पूर्ण,
		अणु0x06, 2700पूर्ण,
		अणु0x07, 2100पूर्ण,
	पूर्ण,
	/* KXCJ9-1008 */
	अणु
		अणु0x08, 100000पूर्ण,
		अणु0x09, 100000पूर्ण,
		अणु0x0A, 100000पूर्ण,
		अणु0x0B, 100000पूर्ण,
		अणु0, 80000पूर्ण,
		अणु0x01, 41000पूर्ण,
		अणु0x02, 21000पूर्ण,
		अणु0x03, 11000पूर्ण,
		अणु0x04, 6400पूर्ण,
		अणु0x05, 3900पूर्ण,
		अणु0x06, 2700पूर्ण,
		अणु0x07, 2100पूर्ण,
	पूर्ण,
	/* KXCTJ2-1009 */
	अणु
		अणु0x08, 1240000पूर्ण,
		अणु0x09, 621000पूर्ण,
		अणु0x0A, 309000पूर्ण,
		अणु0x0B, 151000पूर्ण,
		अणु0, 80000पूर्ण,
		अणु0x01, 41000पूर्ण,
		अणु0x02, 21000पूर्ण,
		अणु0x03, 11000पूर्ण,
		अणु0x04, 6000पूर्ण,
		अणु0x05, 4000पूर्ण,
		अणु0x06, 3000पूर्ण,
		अणु0x07, 2000पूर्ण,
	पूर्ण,
	/* KXTF9 */
	अणु
		अणु0x01, 81000पूर्ण,
		अणु0x02, 41000पूर्ण,
		अणु0x03, 21000पूर्ण,
		अणु0x04, 11000पूर्ण,
		अणु0x05, 5100पूर्ण,
		अणु0x06, 2700पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u16 scale;
	u8 gsel_0;
	u8 gsel_1;
पूर्ण KXCJK1013_scale_table[] = अणु अणु9582, 0, 0पूर्ण,
			      अणु19163, 1, 0पूर्ण,
			      अणु38326, 0, 1पूर्ण पूर्ण;

#अगर_घोषित CONFIG_ACPI
क्रमागत kiox010a_fn_index अणु
	KIOX010A_SET_LAPTOP_MODE = 1,
	KIOX010A_SET_TABLET_MODE = 2,
पूर्ण;

अटल पूर्णांक kiox010a_dsm(काष्ठा device *dev, पूर्णांक fn_index)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	guid_t kiox010a_dsm_guid;
	जोड़ acpi_object *obj;

	अगर (!handle)
		वापस -ENODEV;

	guid_parse("1f339696-d475-4e26-8cad-2e9f8e6d7a91", &kiox010a_dsm_guid);

	obj = acpi_evaluate_dsm(handle, &kiox010a_dsm_guid, 1, fn_index, शून्य);
	अगर (!obj)
		वापस -EIO;

	ACPI_FREE(obj);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kxcjk1013_set_mode(काष्ठा kxcjk1013_data *data,
			      क्रमागत kxcjk1013_mode mode)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (mode == STANDBY)
		ret &= ~KXCJK1013_REG_CTRL1_BIT_PC1;
	अन्यथा
		ret |= KXCJK1013_REG_CTRL1_BIT_PC1;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KXCJK1013_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_get_mode(काष्ठा kxcjk1013_data *data,
			      क्रमागत kxcjk1013_mode *mode)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (ret & KXCJK1013_REG_CTRL1_BIT_PC1)
		*mode = OPERATION;
	अन्यथा
		*mode = STANDBY;

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_set_range(काष्ठा kxcjk1013_data *data, पूर्णांक range_index)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	ret &= ~(KXCJK1013_REG_CTRL1_BIT_GSEL0 |
		 KXCJK1013_REG_CTRL1_BIT_GSEL1);
	ret |= (KXCJK1013_scale_table[range_index].gsel_0 << 3);
	ret |= (KXCJK1013_scale_table[range_index].gsel_1 << 4);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KXCJK1013_REG_CTRL1,
					ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	data->range = range_index;

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_chip_init(काष्ठा kxcjk1013_data *data)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_ACPI
	अगर (data->acpi_type == ACPI_KIOX010A) अणु
		/* Make sure the kbd and touchpad on 2-in-1s using 2 KXCJ91008-s work */
		kiox010a_dsm(&data->client->dev, KIOX010A_SET_LAPTOP_MODE);
	पूर्ण
#पूर्ण_अगर

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_WHO_AM_I);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading who_am_i\n");
		वापस ret;
	पूर्ण

	dev_dbg(&data->client->dev, "KXCJK1013 Chip Id %x\n", ret);

	ret = kxcjk1013_set_mode(data, STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	/* Set 12 bit mode */
	ret |= KXCJK1013_REG_CTRL1_BIT_RES;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_CTRL1,
					ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl\n");
		वापस ret;
	पूर्ण

	/* Setting range to 4G */
	ret = kxcjk1013_set_range(data, KXCJK1013_RANGE_4G);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_DATA_CTRL);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_data_ctrl\n");
		वापस ret;
	पूर्ण

	data->odr_bits = ret;

	/* Set up INT polarity */
	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (data->active_high_पूर्णांकr)
		ret |= KXCJK1013_REG_INT_CTRL1_BIT_IEA;
	अन्यथा
		ret &= ~KXCJK1013_REG_INT_CTRL1_BIT_IEA;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1,
					ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	ret = kxcjk1013_set_mode(data, OPERATION);
	अगर (ret < 0)
		वापस ret;

	data->wake_thres = KXCJK1013_DEFAULT_WAKE_THRES;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक kxcjk1013_get_startup_बार(काष्ठा kxcjk1013_data *data)
अणु
	पूर्णांक i;
	पूर्णांक idx = data->chipset;

	क्रम (i = 0; i < ARRAY_SIZE(odr_start_up_बार[idx]); ++i) अणु
		अगर (odr_start_up_बार[idx][i].odr_bits == data->odr_bits)
			वापस odr_start_up_बार[idx][i].usec;
	पूर्ण

	वापस KXCJK1013_MAX_STARTUP_TIME_US;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kxcjk1013_set_घातer_state(काष्ठा kxcjk1013_data *data, bool on)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (on)
		ret = pm_runसमय_get_sync(&data->client->dev);
	अन्यथा अणु
		pm_runसमय_mark_last_busy(&data->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Failed: %s for %d\n", __func__, on);
		अगर (on)
			pm_runसमय_put_noidle(&data->client->dev);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_chip_update_thresholds(काष्ठा kxcjk1013_data *data)
अणु
	पूर्णांक waketh_reg, ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KXCJK1013_REG_WAKE_TIMER,
					data->wake_dur);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Error writing reg_wake_timer\n");
		वापस ret;
	पूर्ण

	waketh_reg = data->chipset == KXTF9 ?
		KXTF9_REG_WAKE_THRESH : KXCJK1013_REG_WAKE_THRES;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, waketh_reg,
					data->wake_thres);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_wake_thres\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_setup_any_motion_पूर्णांकerrupt(काष्ठा kxcjk1013_data *data,
						bool status)
अणु
	पूर्णांक ret;
	क्रमागत kxcjk1013_mode store_mode;

	ret = kxcjk1013_get_mode(data, &store_mode);
	अगर (ret < 0)
		वापस ret;

	/* This is requirement by spec to change state to STANDBY */
	ret = kxcjk1013_set_mode(data, STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = kxcjk1013_chip_update_thresholds(data);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KXCJK1013_REG_INT_CTRL1_BIT_IEN;
	अन्यथा
		ret &= ~KXCJK1013_REG_INT_CTRL1_BIT_IEN;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1,
					ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KXCJK1013_REG_CTRL1_BIT_WUFE;
	अन्यथा
		ret &= ~KXCJK1013_REG_CTRL1_BIT_WUFE;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KXCJK1013_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (store_mode == OPERATION) अणु
		ret = kxcjk1013_set_mode(data, OPERATION);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_setup_new_data_पूर्णांकerrupt(काष्ठा kxcjk1013_data *data,
					      bool status)
अणु
	पूर्णांक ret;
	क्रमागत kxcjk1013_mode store_mode;

	ret = kxcjk1013_get_mode(data, &store_mode);
	अगर (ret < 0)
		वापस ret;

	/* This is requirement by spec to change state to STANDBY */
	ret = kxcjk1013_set_mode(data, STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KXCJK1013_REG_INT_CTRL1_BIT_IEN;
	अन्यथा
		ret &= ~KXCJK1013_REG_INT_CTRL1_BIT_IEN;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_INT_CTRL1,
					ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KXCJK1013_REG_CTRL1_BIT_DRDY;
	अन्यथा
		ret &= ~KXCJK1013_REG_CTRL1_BIT_DRDY;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KXCJK1013_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (store_mode == OPERATION) अणु
		ret = kxcjk1013_set_mode(data, OPERATION);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kx_odr_map *kxcjk1013_find_odr_value(
	स्थिर काष्ठा kx_odr_map *map, माप_प्रकार map_size, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < map_size; ++i) अणु
		अगर (map[i].val == val && map[i].val2 == val2)
			वापस &map[i];
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक kxcjk1013_convert_odr_value(स्थिर काष्ठा kx_odr_map *map,
				       माप_प्रकार map_size, पूर्णांक odr_bits,
				       पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < map_size; ++i) अणु
		अगर (map[i].odr_bits == odr_bits) अणु
			*val = map[i].val;
			*val2 = map[i].val2;
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kxcjk1013_set_odr(काष्ठा kxcjk1013_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret;
	क्रमागत kxcjk1013_mode store_mode;
	स्थिर काष्ठा kx_odr_map *odr_setting;

	ret = kxcjk1013_get_mode(data, &store_mode);
	अगर (ret < 0)
		वापस ret;

	अगर (data->chipset == KXTF9)
		odr_setting = kxcjk1013_find_odr_value(kxtf9_samp_freq_table,
						       ARRAY_SIZE(kxtf9_samp_freq_table),
						       val, val2);
	अन्यथा
		odr_setting = kxcjk1013_find_odr_value(samp_freq_table,
						       ARRAY_SIZE(samp_freq_table),
						       val, val2);

	अगर (IS_ERR(odr_setting))
		वापस PTR_ERR(odr_setting);

	/* To change ODR, the chip must be set to STANDBY as per spec */
	ret = kxcjk1013_set_mode(data, STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_DATA_CTRL,
					odr_setting->odr_bits);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing data_ctrl\n");
		वापस ret;
	पूर्ण

	data->odr_bits = odr_setting->odr_bits;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KXCJK1013_REG_CTRL2,
					odr_setting->wuf_bits);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl2\n");
		वापस ret;
	पूर्ण

	अगर (store_mode == OPERATION) अणु
		ret = kxcjk1013_set_mode(data, OPERATION);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_get_odr(काष्ठा kxcjk1013_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	अगर (data->chipset == KXTF9)
		वापस kxcjk1013_convert_odr_value(kxtf9_samp_freq_table,
						   ARRAY_SIZE(kxtf9_samp_freq_table),
						   data->odr_bits, val, val2);
	अन्यथा
		वापस kxcjk1013_convert_odr_value(samp_freq_table,
						   ARRAY_SIZE(samp_freq_table),
						   data->odr_bits, val, val2);
पूर्ण

अटल पूर्णांक kxcjk1013_get_acc_reg(काष्ठा kxcjk1013_data *data, पूर्णांक axis)
अणु
	u8 reg = KXCJK1013_REG_XOUT_L + axis * 2;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(data->client, reg);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"failed to read accel_%c registers\n", 'x' + axis);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kxcjk1013_set_scale(काष्ठा kxcjk1013_data *data, पूर्णांक val)
अणु
	पूर्णांक ret, i;
	क्रमागत kxcjk1013_mode store_mode;

	क्रम (i = 0; i < ARRAY_SIZE(KXCJK1013_scale_table); ++i) अणु
		अगर (KXCJK1013_scale_table[i].scale == val) अणु
			ret = kxcjk1013_get_mode(data, &store_mode);
			अगर (ret < 0)
				वापस ret;

			ret = kxcjk1013_set_mode(data, STANDBY);
			अगर (ret < 0)
				वापस ret;

			ret = kxcjk1013_set_range(data, i);
			अगर (ret < 0)
				वापस ret;

			अगर (store_mode == OPERATION) अणु
				ret = kxcjk1013_set_mode(data, OPERATION);
				अगर (ret)
					वापस ret;
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kxcjk1013_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			      पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		अगर (iio_buffer_enabled(indio_dev))
			ret = -EBUSY;
		अन्यथा अणु
			ret = kxcjk1013_set_घातer_state(data, true);
			अगर (ret < 0) अणु
				mutex_unlock(&data->mutex);
				वापस ret;
			पूर्ण
			ret = kxcjk1013_get_acc_reg(data, chan->scan_index);
			अगर (ret < 0) अणु
				kxcjk1013_set_घातer_state(data, false);
				mutex_unlock(&data->mutex);
				वापस ret;
			पूर्ण
			*val = sign_extend32(ret >> 4, 11);
			ret = kxcjk1013_set_घातer_state(data, false);
		पूर्ण
		mutex_unlock(&data->mutex);

		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = KXCJK1013_scale_table[data->range].scale;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = kxcjk1013_get_odr(data, val, val2);
		mutex_unlock(&data->mutex);
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kxcjk1013_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			       पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = kxcjk1013_set_odr(data, val, val2);
		mutex_unlock(&data->mutex);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		ret = kxcjk1013_set_scale(data, val2);
		mutex_unlock(&data->mutex);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kxcjk1013_पढ़ो_event(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir,
				   क्रमागत iio_event_info info,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	*val2 = 0;
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = data->wake_thres;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		*val = data->wake_dur;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक kxcjk1013_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	अगर (data->ev_enable_state)
		वापस -EBUSY;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		data->wake_thres = val;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		data->wake_dur = val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  क्रमागत iio_event_type type,
					  क्रमागत iio_event_direction dir)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	वापस data->ev_enable_state;
पूर्ण

अटल पूर्णांक kxcjk1013_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   क्रमागत iio_event_type type,
					   क्रमागत iio_event_direction dir,
					   पूर्णांक state)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state && data->ev_enable_state)
		वापस 0;

	mutex_lock(&data->mutex);

	अगर (!state && data->motion_trigger_on) अणु
		data->ev_enable_state = 0;
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण

	/*
	 * We will expect the enable and disable to करो operation in
	 * in reverse order. This will happen here anyway as our
	 * resume operation uses sync mode runसमय pm calls, the
	 * suspend operation will be delayed by स्वतःsuspend delay
	 * So the disable operation will still happen in reverse of
	 * enable operation. When runसमय pm is disabled the mode
	 * is always on so sequence करोesn't matter
	 */
	ret = kxcjk1013_set_घातer_state(data, state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	ret =  kxcjk1013_setup_any_motion_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		kxcjk1013_set_घातer_state(data, false);
		data->ev_enable_state = 0;
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	data->ev_enable_state = state;
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	वापस kxcjk1013_set_घातer_state(data, true);
पूर्ण

अटल पूर्णांक kxcjk1013_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	वापस kxcjk1013_set_घातer_state(data, false);
पूर्ण

अटल sमाप_प्रकार kxcjk1013_get_samp_freq_avail(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	स्थिर अक्षर *str;

	अगर (data->chipset == KXTF9)
		str = kxtf9_samp_freq_avail;
	अन्यथा
		str = kxcjk1013_samp_freq_avail;

	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल IIO_DEVICE_ATTR(in_accel_sampling_frequency_available, S_IRUGO,
		       kxcjk1013_get_samp_freq_avail, शून्य, 0);

अटल IIO_CONST_ATTR(in_accel_scale_available, "0.009582 0.019163 0.038326");

अटल काष्ठा attribute *kxcjk1013_attributes[] = अणु
	&iio_dev_attr_in_accel_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kxcjk1013_attrs_group = अणु
	.attrs = kxcjk1013_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec kxcjk1013_event = अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_PERIOD)
पूर्ण;

अटल स्थिर काष्ठा iio_mount_matrix *
kxcjk1013_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info kxcjk1013_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_TYPE, kxcjk1013_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा KXCJK1013_CHANNEL(_axis) अणु					\
	.type = IIO_ACCEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),		\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 12,						\
		.storagebits = 16,					\
		.shअगरt = 4,						\
		.endianness = IIO_LE,					\
	पूर्ण,								\
	.event_spec = &kxcjk1013_event,				\
	.ext_info = kxcjk1013_ext_info,					\
	.num_event_specs = 1						\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec kxcjk1013_channels[] = अणु
	KXCJK1013_CHANNEL(X),
	KXCJK1013_CHANNEL(Y),
	KXCJK1013_CHANNEL(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_buffer_setup_ops kxcjk1013_buffer_setup_ops = अणु
	.preenable		= kxcjk1013_buffer_preenable,
	.postdisable		= kxcjk1013_buffer_postdisable,
पूर्ण;

अटल स्थिर काष्ठा iio_info kxcjk1013_info = अणु
	.attrs			= &kxcjk1013_attrs_group,
	.पढ़ो_raw		= kxcjk1013_पढ़ो_raw,
	.ग_लिखो_raw		= kxcjk1013_ग_लिखो_raw,
	.पढ़ो_event_value	= kxcjk1013_पढ़ो_event,
	.ग_लिखो_event_value	= kxcjk1013_ग_लिखो_event,
	.ग_लिखो_event_config	= kxcjk1013_ग_लिखो_event_config,
	.पढ़ो_event_config	= kxcjk1013_पढ़ो_event_config,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ kxcjk1013_scan_masks[] = अणु0x7, 0पूर्ण;

अटल irqवापस_t kxcjk1013_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(data->client,
							KXCJK1013_REG_XOUT_L,
							AXIS_MAX * 2,
							(u8 *)data->buffer);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   data->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम kxcjk1013_trig_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_REL);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_int_rel\n");
पूर्ण

अटल पूर्णांक kxcjk1013_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
						bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (!state && data->ev_enable_state && data->motion_trigger_on) अणु
		data->motion_trigger_on = false;
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण

	ret = kxcjk1013_set_घातer_state(data, state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	अगर (data->motion_trig == trig)
		ret = kxcjk1013_setup_any_motion_पूर्णांकerrupt(data, state);
	अन्यथा
		ret = kxcjk1013_setup_new_data_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		kxcjk1013_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	अगर (data->motion_trig == trig)
		data->motion_trigger_on = state;
	अन्यथा
		data->dपढ़ोy_trigger_on = state;

	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops kxcjk1013_trigger_ops = अणु
	.set_trigger_state = kxcjk1013_data_rdy_trigger_set_state,
	.reenable = kxcjk1013_trig_reen,
पूर्ण;

अटल व्योम kxcjk1013_report_motion_event(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(data->client,
					   KXCJK1013_REG_INT_SRC2);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_int_src2\n");
		वापस;
	पूर्ण

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_XN)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_FALLING),
			       data->बारtamp);

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_XP)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_RISING),
			       data->बारtamp);

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_YN)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_FALLING),
			       data->बारtamp);

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_YP)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_RISING),
			       data->बारtamp);

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_ZN)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_FALLING),
			       data->बारtamp);

	अगर (ret & KXCJK1013_REG_INT_SRC2_BIT_ZP)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_THRESH,
						  IIO_EV_सूची_RISING),
			       data->बारtamp);
पूर्ण

अटल irqवापस_t kxcjk1013_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_SRC1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_int_src1\n");
		जाओ ack_पूर्णांकr;
	पूर्ण

	अगर (ret & KXCJK1013_REG_INT_SRC1_BIT_WUFS) अणु
		अगर (data->chipset == KXTF9)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X_AND_Y_AND_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_RISING),
				       data->बारtamp);
		अन्यथा
			kxcjk1013_report_motion_event(indio_dev);
	पूर्ण

ack_पूर्णांकr:
	अगर (data->dपढ़ोy_trigger_on)
		वापस IRQ_HANDLED;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KXCJK1013_REG_INT_REL);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_int_rel\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t kxcjk1013_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	data->बारtamp = iio_get_समय_ns(indio_dev);

	अगर (data->dपढ़ोy_trigger_on)
		iio_trigger_poll(data->dपढ़ोy_trig);
	अन्यथा अगर (data->motion_trigger_on)
		iio_trigger_poll(data->motion_trig);

	अगर (data->ev_enable_state)
		वापस IRQ_WAKE_THREAD;
	अन्यथा
		वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर *kxcjk1013_match_acpi_device(काष्ठा device *dev,
					       क्रमागत kx_chipset *chipset,
					       क्रमागत kx_acpi_type *acpi_type,
					       स्थिर अक्षर **label)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	अगर (म_भेद(id->id, "SMO8500") == 0) अणु
		*acpi_type = ACPI_SMO8500;
	पूर्ण अन्यथा अगर (म_भेद(id->id, "KIOX010A") == 0) अणु
		*acpi_type = ACPI_KIOX010A;
		*label = "accel-display";
	पूर्ण अन्यथा अगर (म_भेद(id->id, "KIOX020A") == 0) अणु
		*label = "accel-base";
	पूर्ण

	*chipset = (क्रमागत kx_chipset)id->driver_data;

	वापस dev_name(dev);
पूर्ण

अटल व्योम kxcjk1013_disable_regulators(व्योम *d)
अणु
	काष्ठा kxcjk1013_data *data = d;

	regulator_bulk_disable(ARRAY_SIZE(data->regulators), data->regulators);
पूर्ण

अटल पूर्णांक kxcjk1013_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा kxcjk1013_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा kxcjk_1013_platक्रमm_data *pdata;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	pdata = dev_get_platdata(&client->dev);
	अगर (pdata) अणु
		data->active_high_पूर्णांकr = pdata->active_high_पूर्णांकr;
		data->orientation = pdata->orientation;
	पूर्ण अन्यथा अणु
		data->active_high_पूर्णांकr = true; /* शेष polarity */

		ret = iio_पढ़ो_mount_matrix(&client->dev, "mount-matrix",
					    &data->orientation);
		अगर (ret)
			वापस ret;
	पूर्ण

	data->regulators[0].supply = "vdd";
	data->regulators[1].supply = "vddio";
	ret = devm_regulator_bulk_get(&client->dev, ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (ret)
		वापस dev_err_probe(&client->dev, ret, "Failed to get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				    data->regulators);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&client->dev, kxcjk1013_disable_regulators, data);
	अगर (ret)
		वापस ret;

	/*
	 * A typical delay of 10ms is required क्रम घातering up
	 * according to the data sheets of supported chips.
	 * Hence द्विगुन that to play safe.
	 */
	msleep(20);

	अगर (id) अणु
		data->chipset = (क्रमागत kx_chipset)(id->driver_data);
		name = id->name;
	पूर्ण अन्यथा अगर (ACPI_HANDLE(&client->dev)) अणु
		name = kxcjk1013_match_acpi_device(&client->dev,
						   &data->chipset,
						   &data->acpi_type,
						   &indio_dev->label);
	पूर्ण अन्यथा
		वापस -ENODEV;

	ret = kxcjk1013_chip_init(data);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&data->mutex);

	indio_dev->channels = kxcjk1013_channels;
	indio_dev->num_channels = ARRAY_SIZE(kxcjk1013_channels);
	indio_dev->available_scan_masks = kxcjk1013_scan_masks;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &kxcjk1013_info;

	अगर (client->irq > 0 && data->acpi_type != ACPI_SMO8500) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						kxcjk1013_data_rdy_trig_poll,
						kxcjk1013_event_handler,
						IRQF_TRIGGER_RISING,
						KXCJK1013_IRQ_NAME,
						indio_dev);
		अगर (ret)
			जाओ err_घातeroff;

		data->dपढ़ोy_trig = devm_iio_trigger_alloc(&client->dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		अगर (!data->dपढ़ोy_trig) अणु
			ret = -ENOMEM;
			जाओ err_घातeroff;
		पूर्ण

		data->motion_trig = devm_iio_trigger_alloc(&client->dev,
							  "%s-any-motion-dev%d",
							  indio_dev->name,
							  indio_dev->id);
		अगर (!data->motion_trig) अणु
			ret = -ENOMEM;
			जाओ err_घातeroff;
		पूर्ण

		data->dपढ़ोy_trig->ops = &kxcjk1013_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		indio_dev->trig = data->dपढ़ोy_trig;
		iio_trigger_get(indio_dev->trig);
		ret = iio_trigger_रेजिस्टर(data->dपढ़ोy_trig);
		अगर (ret)
			जाओ err_घातeroff;

		data->motion_trig->ops = &kxcjk1013_trigger_ops;
		iio_trigger_set_drvdata(data->motion_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->motion_trig);
		अगर (ret) अणु
			data->motion_trig = शून्य;
			जाओ err_trigger_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 &iio_pollfunc_store_समय,
					 kxcjk1013_trigger_handler,
					 &kxcjk1013_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 KXCJK1013_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस 0;

err_buffer_cleanup:
	अगर (data->dपढ़ोy_trig)
		iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
	अगर (data->motion_trig)
		iio_trigger_unरेजिस्टर(data->motion_trig);
err_घातeroff:
	kxcjk1013_set_mode(data, STANDBY);

	वापस ret;
पूर्ण

अटल पूर्णांक kxcjk1013_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	अगर (data->dपढ़ोy_trig) अणु
		iio_triggered_buffer_cleanup(indio_dev);
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
		iio_trigger_unरेजिस्टर(data->motion_trig);
	पूर्ण

	mutex_lock(&data->mutex);
	kxcjk1013_set_mode(data, STANDBY);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक kxcjk1013_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = kxcjk1013_set_mode(data, STANDBY);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक kxcjk1013_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	mutex_lock(&data->mutex);
	ret = kxcjk1013_set_mode(data, OPERATION);
	अगर (ret == 0)
		ret = kxcjk1013_set_range(data, data->range);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक kxcjk1013_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = kxcjk1013_set_mode(data, STANDBY);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "powering off device failed\n");
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kxcjk1013_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा kxcjk1013_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक sleep_val;

	ret = kxcjk1013_set_mode(data, OPERATION);
	अगर (ret < 0)
		वापस ret;

	sleep_val = kxcjk1013_get_startup_बार(data);
	अगर (sleep_val < 20000)
		usleep_range(sleep_val, 20000);
	अन्यथा
		msleep_पूर्णांकerruptible(sleep_val/1000);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops kxcjk1013_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(kxcjk1013_suspend, kxcjk1013_resume)
	SET_RUNTIME_PM_OPS(kxcjk1013_runसमय_suspend,
			   kxcjk1013_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id kx_acpi_match[] = अणु
	अणु"KXCJ1013", KXCJK1013पूर्ण,
	अणु"KXCJ1008", KXCJ91008पूर्ण,
	अणु"KXCJ9000", KXCJ91008पूर्ण,
	अणु"KIOX0008", KXCJ91008पूर्ण,
	अणु"KIOX0009", KXTJ21009पूर्ण,
	अणु"KIOX000A", KXCJ91008पूर्ण,
	अणु"KIOX010A", KXCJ91008पूर्ण, /* KXCJ91008 in the display of a yoga 2-in-1 */
	अणु"KIOX020A", KXCJ91008पूर्ण, /* KXCJ91008 in the base of a yoga 2-in-1 */
	अणु"KXTJ1009", KXTJ21009पूर्ण,
	अणु"KXJ2109",  KXTJ21009पूर्ण,
	अणु"SMO8500",  KXCJ91008पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, kx_acpi_match);

अटल स्थिर काष्ठा i2c_device_id kxcjk1013_id[] = अणु
	अणु"kxcjk1013", KXCJK1013पूर्ण,
	अणु"kxcj91008", KXCJ91008पूर्ण,
	अणु"kxtj21009", KXTJ21009पूर्ण,
	अणु"kxtf9",     KXTF9पूर्ण,
	अणु"SMO8500",   KXCJ91008पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, kxcjk1013_id);

अटल स्थिर काष्ठा of_device_id kxcjk1013_of_match[] = अणु
	अणु .compatible = "kionix,kxcjk1013", पूर्ण,
	अणु .compatible = "kionix,kxcj91008", पूर्ण,
	अणु .compatible = "kionix,kxtj21009", पूर्ण,
	अणु .compatible = "kionix,kxtf9", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, kxcjk1013_of_match);

अटल काष्ठा i2c_driver kxcjk1013_driver = अणु
	.driver = अणु
		.name	= KXCJK1013_DRV_NAME,
		.acpi_match_table = ACPI_PTR(kx_acpi_match),
		.of_match_table = kxcjk1013_of_match,
		.pm	= &kxcjk1013_pm_ops,
	पूर्ण,
	.probe		= kxcjk1013_probe,
	.हटाओ		= kxcjk1013_हटाओ,
	.id_table	= kxcjk1013_id,
पूर्ण;
module_i2c_driver(kxcjk1013_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("KXCJK1013 accelerometer driver");
