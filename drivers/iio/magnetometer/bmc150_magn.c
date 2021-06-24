<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bosch BMC150 three-axis magnetic field sensor driver
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * This code is based on bmm050_api.c authored by contact@bosch.sensortec.com:
 *
 * (C) Copyright 2011~2014 Bosch Sensortec GmbH All Rights Reserved
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "bmc150_magn.h"

#घोषणा BMC150_MAGN_DRV_NAME			"bmc150_magn"
#घोषणा BMC150_MAGN_IRQ_NAME			"bmc150_magn_event"

#घोषणा BMC150_MAGN_REG_CHIP_ID			0x40
#घोषणा BMC150_MAGN_CHIP_ID_VAL			0x32

#घोषणा BMC150_MAGN_REG_X_L			0x42
#घोषणा BMC150_MAGN_REG_X_M			0x43
#घोषणा BMC150_MAGN_REG_Y_L			0x44
#घोषणा BMC150_MAGN_REG_Y_M			0x45
#घोषणा BMC150_MAGN_SHIFT_XY_L			3
#घोषणा BMC150_MAGN_REG_Z_L			0x46
#घोषणा BMC150_MAGN_REG_Z_M			0x47
#घोषणा BMC150_MAGN_SHIFT_Z_L			1
#घोषणा BMC150_MAGN_REG_RHALL_L			0x48
#घोषणा BMC150_MAGN_REG_RHALL_M			0x49
#घोषणा BMC150_MAGN_SHIFT_RHALL_L		2

#घोषणा BMC150_MAGN_REG_INT_STATUS		0x4A

#घोषणा BMC150_MAGN_REG_POWER			0x4B
#घोषणा BMC150_MAGN_MASK_POWER_CTL		BIT(0)

#घोषणा BMC150_MAGN_REG_OPMODE_ODR		0x4C
#घोषणा BMC150_MAGN_MASK_OPMODE			GENMASK(2, 1)
#घोषणा BMC150_MAGN_SHIFT_OPMODE		1
#घोषणा BMC150_MAGN_MODE_NORMAL			0x00
#घोषणा BMC150_MAGN_MODE_FORCED			0x01
#घोषणा BMC150_MAGN_MODE_SLEEP			0x03
#घोषणा BMC150_MAGN_MASK_ODR			GENMASK(5, 3)
#घोषणा BMC150_MAGN_SHIFT_ODR			3

#घोषणा BMC150_MAGN_REG_INT			0x4D

#घोषणा BMC150_MAGN_REG_INT_DRDY		0x4E
#घोषणा BMC150_MAGN_MASK_DRDY_EN		BIT(7)
#घोषणा BMC150_MAGN_SHIFT_DRDY_EN		7
#घोषणा BMC150_MAGN_MASK_DRDY_INT3		BIT(6)
#घोषणा BMC150_MAGN_MASK_DRDY_Z_EN		BIT(5)
#घोषणा BMC150_MAGN_MASK_DRDY_Y_EN		BIT(4)
#घोषणा BMC150_MAGN_MASK_DRDY_X_EN		BIT(3)
#घोषणा BMC150_MAGN_MASK_DRDY_DR_POLARITY	BIT(2)
#घोषणा BMC150_MAGN_MASK_DRDY_LATCHING		BIT(1)
#घोषणा BMC150_MAGN_MASK_DRDY_INT3_POLARITY	BIT(0)

#घोषणा BMC150_MAGN_REG_LOW_THRESH		0x4F
#घोषणा BMC150_MAGN_REG_HIGH_THRESH		0x50
#घोषणा BMC150_MAGN_REG_REP_XY			0x51
#घोषणा BMC150_MAGN_REG_REP_Z			0x52
#घोषणा BMC150_MAGN_REG_REP_DATAMASK		GENMASK(7, 0)

#घोषणा BMC150_MAGN_REG_TRIM_START		0x5D
#घोषणा BMC150_MAGN_REG_TRIM_END		0x71

#घोषणा BMC150_MAGN_XY_OVERFLOW_VAL		-4096
#घोषणा BMC150_MAGN_Z_OVERFLOW_VAL		-16384

/* Time from SUSPEND to SLEEP */
#घोषणा BMC150_MAGN_START_UP_TIME_MS		3

#घोषणा BMC150_MAGN_AUTO_SUSPEND_DELAY_MS	2000

#घोषणा BMC150_MAGN_REGVAL_TO_REPXY(regval) (((regval) * 2) + 1)
#घोषणा BMC150_MAGN_REGVAL_TO_REPZ(regval) ((regval) + 1)
#घोषणा BMC150_MAGN_REPXY_TO_REGVAL(rep) (((rep) - 1) / 2)
#घोषणा BMC150_MAGN_REPZ_TO_REGVAL(rep) ((rep) - 1)

क्रमागत bmc150_magn_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	RHALL,
	AXIS_XYZ_MAX = RHALL,
	AXIS_XYZR_MAX,
पूर्ण;

क्रमागत bmc150_magn_घातer_modes अणु
	BMC150_MAGN_POWER_MODE_SUSPEND,
	BMC150_MAGN_POWER_MODE_SLEEP,
	BMC150_MAGN_POWER_MODE_NORMAL,
पूर्ण;

काष्ठा bmc150_magn_trim_regs अणु
	s8 x1;
	s8 y1;
	__le16 reserved1;
	u8 reserved2;
	__le16 z4;
	s8 x2;
	s8 y2;
	__le16 reserved3;
	__le16 z2;
	__le16 z1;
	__le16 xyz1;
	__le16 z3;
	s8 xy2;
	u8 xy1;
पूर्ण __packed;

काष्ठा bmc150_magn_data अणु
	काष्ठा device *dev;
	/*
	 * 1. Protect this काष्ठाure.
	 * 2. Serialize sequences that घातer on/off the device and access HW.
	 */
	काष्ठा mutex mutex;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा iio_mount_matrix orientation;
	/* 4 x 32 bits क्रम x, y z, 4 bytes align, 64 bits बारtamp */
	s32 buffer[6];
	काष्ठा iio_trigger *dपढ़ोy_trig;
	bool dपढ़ोy_trigger_on;
	पूर्णांक max_odr;
	पूर्णांक irq;
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक freq;
	u8 reg_val;
पूर्ण bmc150_magn_samp_freq_table[] = अणु अणु2, 0x01पूर्ण,
				    अणु6, 0x02पूर्ण,
				    अणु8, 0x03पूर्ण,
				    अणु10, 0x00पूर्ण,
				    अणु15, 0x04पूर्ण,
				    अणु20, 0x05पूर्ण,
				    अणु25, 0x06पूर्ण,
				    अणु30, 0x07पूर्ण पूर्ण;

क्रमागत bmc150_magn_presets अणु
	LOW_POWER_PRESET,
	REGULAR_PRESET,
	ENHANCED_REGULAR_PRESET,
	HIGH_ACCURACY_PRESET
पूर्ण;

अटल स्थिर काष्ठा bmc150_magn_preset अणु
	u8 rep_xy;
	u8 rep_z;
	u8 odr;
पूर्ण bmc150_magn_presets_table[] = अणु
	[LOW_POWER_PRESET] = अणु3, 3, 10पूर्ण,
	[REGULAR_PRESET] =  अणु9, 15, 10पूर्ण,
	[ENHANCED_REGULAR_PRESET] =  अणु15, 27, 10पूर्ण,
	[HIGH_ACCURACY_PRESET] =  अणु47, 83, 20पूर्ण,
पूर्ण;

#घोषणा BMC150_MAGN_DEFAULT_PRESET REGULAR_PRESET

अटल bool bmc150_magn_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMC150_MAGN_REG_POWER:
	हाल BMC150_MAGN_REG_OPMODE_ODR:
	हाल BMC150_MAGN_REG_INT:
	हाल BMC150_MAGN_REG_INT_DRDY:
	हाल BMC150_MAGN_REG_LOW_THRESH:
	हाल BMC150_MAGN_REG_HIGH_THRESH:
	हाल BMC150_MAGN_REG_REP_XY:
	हाल BMC150_MAGN_REG_REP_Z:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool bmc150_magn_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMC150_MAGN_REG_X_L:
	हाल BMC150_MAGN_REG_X_M:
	हाल BMC150_MAGN_REG_Y_L:
	हाल BMC150_MAGN_REG_Y_M:
	हाल BMC150_MAGN_REG_Z_L:
	हाल BMC150_MAGN_REG_Z_M:
	हाल BMC150_MAGN_REG_RHALL_L:
	हाल BMC150_MAGN_REG_RHALL_M:
	हाल BMC150_MAGN_REG_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config bmc150_magn_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BMC150_MAGN_REG_TRIM_END,
	.cache_type = REGCACHE_RBTREE,

	.ग_लिखोable_reg = bmc150_magn_is_ग_लिखोable_reg,
	.अस्थिर_reg = bmc150_magn_is_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL(bmc150_magn_regmap_config);

अटल पूर्णांक bmc150_magn_set_घातer_mode(काष्ठा bmc150_magn_data *data,
				      क्रमागत bmc150_magn_घातer_modes mode,
				      bool state)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल BMC150_MAGN_POWER_MODE_SUSPEND:
		ret = regmap_update_bits(data->regmap, BMC150_MAGN_REG_POWER,
					 BMC150_MAGN_MASK_POWER_CTL, !state);
		अगर (ret < 0)
			वापस ret;
		usleep_range(BMC150_MAGN_START_UP_TIME_MS * 1000, 20000);
		वापस 0;
	हाल BMC150_MAGN_POWER_MODE_SLEEP:
		वापस regmap_update_bits(data->regmap,
					  BMC150_MAGN_REG_OPMODE_ODR,
					  BMC150_MAGN_MASK_OPMODE,
					  BMC150_MAGN_MODE_SLEEP <<
					  BMC150_MAGN_SHIFT_OPMODE);
	हाल BMC150_MAGN_POWER_MODE_NORMAL:
		वापस regmap_update_bits(data->regmap,
					  BMC150_MAGN_REG_OPMODE_ODR,
					  BMC150_MAGN_MASK_OPMODE,
					  BMC150_MAGN_MODE_NORMAL <<
					  BMC150_MAGN_SHIFT_OPMODE);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmc150_magn_set_घातer_state(काष्ठा bmc150_magn_data *data, bool on)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(data->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(data->dev);
		ret = pm_runसमय_put_स्वतःsuspend(data->dev);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(data->dev,
			"failed to change power state to %d\n", on);
		अगर (on)
			pm_runसमय_put_noidle(data->dev);

		वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_magn_get_odr(काष्ठा bmc150_magn_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, reg_val;
	u8 i, odr_val;

	ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_OPMODE_ODR, &reg_val);
	अगर (ret < 0)
		वापस ret;
	odr_val = (reg_val & BMC150_MAGN_MASK_ODR) >> BMC150_MAGN_SHIFT_ODR;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_magn_samp_freq_table); i++)
		अगर (bmc150_magn_samp_freq_table[i].reg_val == odr_val) अणु
			*val = bmc150_magn_samp_freq_table[i].freq;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmc150_magn_set_odr(काष्ठा bmc150_magn_data *data, पूर्णांक val)
अणु
	पूर्णांक ret;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_magn_samp_freq_table); i++) अणु
		अगर (bmc150_magn_samp_freq_table[i].freq == val) अणु
			ret = regmap_update_bits(data->regmap,
						 BMC150_MAGN_REG_OPMODE_ODR,
						 BMC150_MAGN_MASK_ODR,
						 bmc150_magn_samp_freq_table[i].
						 reg_val <<
						 BMC150_MAGN_SHIFT_ODR);
			अगर (ret < 0)
				वापस ret;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmc150_magn_set_max_odr(काष्ठा bmc150_magn_data *data, पूर्णांक rep_xy,
				   पूर्णांक rep_z, पूर्णांक odr)
अणु
	पूर्णांक ret, reg_val, max_odr;

	अगर (rep_xy <= 0) अणु
		ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_REP_XY,
				  &reg_val);
		अगर (ret < 0)
			वापस ret;
		rep_xy = BMC150_MAGN_REGVAL_TO_REPXY(reg_val);
	पूर्ण
	अगर (rep_z <= 0) अणु
		ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_REP_Z,
				  &reg_val);
		अगर (ret < 0)
			वापस ret;
		rep_z = BMC150_MAGN_REGVAL_TO_REPZ(reg_val);
	पूर्ण
	अगर (odr <= 0) अणु
		ret = bmc150_magn_get_odr(data, &odr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	/* the maximum selectable पढ़ो-out frequency from datasheet */
	max_odr = 1000000 / (145 * rep_xy + 500 * rep_z + 980);
	अगर (odr > max_odr) अणु
		dev_err(data->dev,
			"Can't set oversampling with sampling freq %d\n",
			odr);
		वापस -EINVAL;
	पूर्ण
	data->max_odr = max_odr;

	वापस 0;
पूर्ण

अटल s32 bmc150_magn_compensate_x(काष्ठा bmc150_magn_trim_regs *tregs, s16 x,
				    u16 rhall)
अणु
	s16 val;
	u16 xyz1 = le16_to_cpu(tregs->xyz1);

	अगर (x == BMC150_MAGN_XY_OVERFLOW_VAL)
		वापस S32_MIN;

	अगर (!rhall)
		rhall = xyz1;

	val = ((s16)(((u16)((((s32)xyz1) << 14) / rhall)) - ((u16)0x4000)));
	val = ((s16)((((s32)x) * ((((((((s32)tregs->xy2) * ((((s32)val) *
	      ((s32)val)) >> 7)) + (((s32)val) *
	      ((s32)(((s16)tregs->xy1) << 7)))) >> 9) + ((s32)0x100000)) *
	      ((s32)(((s16)tregs->x2) + ((s16)0xA0)))) >> 12)) >> 13)) +
	      (((s16)tregs->x1) << 3);

	वापस (s32)val;
पूर्ण

अटल s32 bmc150_magn_compensate_y(काष्ठा bmc150_magn_trim_regs *tregs, s16 y,
				    u16 rhall)
अणु
	s16 val;
	u16 xyz1 = le16_to_cpu(tregs->xyz1);

	अगर (y == BMC150_MAGN_XY_OVERFLOW_VAL)
		वापस S32_MIN;

	अगर (!rhall)
		rhall = xyz1;

	val = ((s16)(((u16)((((s32)xyz1) << 14) / rhall)) - ((u16)0x4000)));
	val = ((s16)((((s32)y) * ((((((((s32)tregs->xy2) * ((((s32)val) *
	      ((s32)val)) >> 7)) + (((s32)val) *
	      ((s32)(((s16)tregs->xy1) << 7)))) >> 9) + ((s32)0x100000)) *
	      ((s32)(((s16)tregs->y2) + ((s16)0xA0)))) >> 12)) >> 13)) +
	      (((s16)tregs->y1) << 3);

	वापस (s32)val;
पूर्ण

अटल s32 bmc150_magn_compensate_z(काष्ठा bmc150_magn_trim_regs *tregs, s16 z,
				    u16 rhall)
अणु
	s32 val;
	u16 xyz1 = le16_to_cpu(tregs->xyz1);
	u16 z1 = le16_to_cpu(tregs->z1);
	s16 z2 = le16_to_cpu(tregs->z2);
	s16 z3 = le16_to_cpu(tregs->z3);
	s16 z4 = le16_to_cpu(tregs->z4);

	अगर (z == BMC150_MAGN_Z_OVERFLOW_VAL)
		वापस S32_MIN;

	val = (((((s32)(z - z4)) << 15) - ((((s32)z3) * ((s32)(((s16)rhall) -
	      ((s16)xyz1)))) >> 2)) / (z2 + ((s16)(((((s32)z1) *
	      ((((s16)rhall) << 1))) + (1 << 15)) >> 16))));

	वापस val;
पूर्ण

अटल पूर्णांक bmc150_magn_पढ़ो_xyz(काष्ठा bmc150_magn_data *data, s32 *buffer)
अणु
	पूर्णांक ret;
	__le16 values[AXIS_XYZR_MAX];
	s16 raw_x, raw_y, raw_z;
	u16 rhall;
	काष्ठा bmc150_magn_trim_regs tregs;

	ret = regmap_bulk_पढ़ो(data->regmap, BMC150_MAGN_REG_X_L,
			       values, माप(values));
	अगर (ret < 0)
		वापस ret;

	raw_x = (s16)le16_to_cpu(values[AXIS_X]) >> BMC150_MAGN_SHIFT_XY_L;
	raw_y = (s16)le16_to_cpu(values[AXIS_Y]) >> BMC150_MAGN_SHIFT_XY_L;
	raw_z = (s16)le16_to_cpu(values[AXIS_Z]) >> BMC150_MAGN_SHIFT_Z_L;
	rhall = le16_to_cpu(values[RHALL]) >> BMC150_MAGN_SHIFT_RHALL_L;

	ret = regmap_bulk_पढ़ो(data->regmap, BMC150_MAGN_REG_TRIM_START,
			       &tregs, माप(tregs));
	अगर (ret < 0)
		वापस ret;

	buffer[AXIS_X] = bmc150_magn_compensate_x(&tregs, raw_x, rhall);
	buffer[AXIS_Y] = bmc150_magn_compensate_y(&tregs, raw_y, rhall);
	buffer[AXIS_Z] = bmc150_magn_compensate_z(&tregs, raw_z, rhall);

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_magn_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret, पंचांगp;
	s32 values[AXIS_XYZ_MAX];

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;
		mutex_lock(&data->mutex);

		ret = bmc150_magn_set_घातer_state(data, true);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण

		ret = bmc150_magn_पढ़ो_xyz(data, values);
		अगर (ret < 0) अणु
			bmc150_magn_set_घातer_state(data, false);
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		*val = values[chan->scan_index];

		ret = bmc150_magn_set_घातer_state(data, false);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण

		mutex_unlock(&data->mutex);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * The API/driver perक्रमms an off-chip temperature
		 * compensation and outमाला_दो x/y/z magnetic field data in
		 * 16 LSB/uT to the upper application layer.
		 */
		*val = 0;
		*val2 = 625;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = bmc150_magn_get_odr(data, val);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->channel2) अणु
		हाल IIO_MOD_X:
		हाल IIO_MOD_Y:
			ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_REP_XY,
					  &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = BMC150_MAGN_REGVAL_TO_REPXY(पंचांगp);
			वापस IIO_VAL_INT;
		हाल IIO_MOD_Z:
			ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_REP_Z,
					  &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = BMC150_MAGN_REGVAL_TO_REPZ(पंचांगp);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bmc150_magn_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val > data->max_odr)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = bmc150_magn_set_odr(data, val);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->channel2) अणु
		हाल IIO_MOD_X:
		हाल IIO_MOD_Y:
			अगर (val < 1 || val > 511)
				वापस -EINVAL;
			mutex_lock(&data->mutex);
			ret = bmc150_magn_set_max_odr(data, val, 0, 0);
			अगर (ret < 0) अणु
				mutex_unlock(&data->mutex);
				वापस ret;
			पूर्ण
			ret = regmap_update_bits(data->regmap,
						 BMC150_MAGN_REG_REP_XY,
						 BMC150_MAGN_REG_REP_DATAMASK,
						 BMC150_MAGN_REPXY_TO_REGVAL
						 (val));
			mutex_unlock(&data->mutex);
			वापस ret;
		हाल IIO_MOD_Z:
			अगर (val < 1 || val > 256)
				वापस -EINVAL;
			mutex_lock(&data->mutex);
			ret = bmc150_magn_set_max_odr(data, 0, val, 0);
			अगर (ret < 0) अणु
				mutex_unlock(&data->mutex);
				वापस ret;
			पूर्ण
			ret = regmap_update_bits(data->regmap,
						 BMC150_MAGN_REG_REP_Z,
						 BMC150_MAGN_REG_REP_DATAMASK,
						 BMC150_MAGN_REPZ_TO_REGVAL
						 (val));
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार bmc150_magn_show_samp_freq_avail(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	माप_प्रकार len = 0;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(bmc150_magn_samp_freq_table); i++) अणु
		अगर (bmc150_magn_samp_freq_table[i].freq > data->max_odr)
			अवरोध;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ",
				 bmc150_magn_samp_freq_table[i].freq);
	पूर्ण
	/* replace last space with a newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
bmc150_magn_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info bmc150_magn_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bmc150_magn_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(bmc150_magn_show_samp_freq_avail);

अटल काष्ठा attribute *bmc150_magn_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bmc150_magn_attrs_group = अणु
	.attrs = bmc150_magn_attributes,
पूर्ण;

#घोषणा BMC150_MAGN_CHANNEL(_axis) अणु					\
	.type = IIO_MAGN,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
			      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) |	\
				    BIT(IIO_CHAN_INFO_SCALE),		\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 32,						\
		.storagebits = 32,					\
		.endianness = IIO_LE					\
	पूर्ण,								\
	.ext_info = bmc150_magn_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bmc150_magn_channels[] = अणु
	BMC150_MAGN_CHANNEL(X),
	BMC150_MAGN_CHANNEL(Y),
	BMC150_MAGN_CHANNEL(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_info bmc150_magn_info = अणु
	.attrs = &bmc150_magn_attrs_group,
	.पढ़ो_raw = bmc150_magn_पढ़ो_raw,
	.ग_लिखो_raw = bmc150_magn_ग_लिखो_raw,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bmc150_magn_scan_masks[] = अणु
					BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
					0पूर्ण;

अटल irqवापस_t bmc150_magn_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_पढ़ो_xyz(data, data->buffer);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);

err:
	mutex_unlock(&data->mutex);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bmc150_magn_init(काष्ठा bmc150_magn_data *data)
अणु
	पूर्णांक ret, chip_id;
	काष्ठा bmc150_magn_preset preset;

	ret = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				    data->regulators);
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण
	/*
	 * 3ms घातer-on समय according to datasheet, let's better
	 * be safe than sorry and set this delay to 5ms.
	 */
	msleep(5);

	ret = bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND,
					 false);
	अगर (ret < 0) अणु
		dev_err(data->dev,
			"Failed to bring up device from suspend mode\n");
		जाओ err_regulator_disable;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_CHIP_ID, &chip_id);
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed reading chip id\n");
		जाओ err_घातeroff;
	पूर्ण
	अगर (chip_id != BMC150_MAGN_CHIP_ID_VAL) अणु
		dev_err(data->dev, "Invalid chip id 0x%x\n", chip_id);
		ret = -ENODEV;
		जाओ err_घातeroff;
	पूर्ण
	dev_dbg(data->dev, "Chip id %x\n", chip_id);

	preset = bmc150_magn_presets_table[BMC150_MAGN_DEFAULT_PRESET];
	ret = bmc150_magn_set_odr(data, preset.odr);
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed to set ODR to %d\n",
			preset.odr);
		जाओ err_घातeroff;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, BMC150_MAGN_REG_REP_XY,
			   BMC150_MAGN_REPXY_TO_REGVAL(preset.rep_xy));
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed to set REP XY to %d\n",
			preset.rep_xy);
		जाओ err_घातeroff;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, BMC150_MAGN_REG_REP_Z,
			   BMC150_MAGN_REPZ_TO_REGVAL(preset.rep_z));
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed to set REP Z to %d\n",
			preset.rep_z);
		जाओ err_घातeroff;
	पूर्ण

	ret = bmc150_magn_set_max_odr(data, preset.rep_xy, preset.rep_z,
				      preset.odr);
	अगर (ret < 0)
		जाओ err_घातeroff;

	ret = bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_NORMAL,
					 true);
	अगर (ret < 0) अणु
		dev_err(data->dev, "Failed to power on device\n");
		जाओ err_घातeroff;
	पूर्ण

	वापस 0;

err_घातeroff:
	bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND, true);
err_regulator_disable:
	regulator_bulk_disable(ARRAY_SIZE(data->regulators), data->regulators);
	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_magn_reset_पूर्णांकr(काष्ठा bmc150_magn_data *data)
अणु
	पूर्णांक पंचांगp;

	/*
	 * Data Ready (DRDY) is always cleared after
	 * पढ़ोout of data रेजिस्टरs ends.
	 */
	वापस regmap_पढ़ो(data->regmap, BMC150_MAGN_REG_X_L, &पंचांगp);
पूर्ण

अटल व्योम bmc150_magn_trig_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (!data->dपढ़ोy_trigger_on)
		वापस;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_reset_पूर्णांकr(data);
	mutex_unlock(&data->mutex);
	अगर (ret)
		dev_err(data->dev, "Failed to reset interrupt\n");
पूर्ण

अटल पूर्णांक bmc150_magn_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
						  bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	mutex_lock(&data->mutex);
	अगर (state == data->dपढ़ोy_trigger_on)
		जाओ err_unlock;

	ret = regmap_update_bits(data->regmap, BMC150_MAGN_REG_INT_DRDY,
				 BMC150_MAGN_MASK_DRDY_EN,
				 state << BMC150_MAGN_SHIFT_DRDY_EN);
	अगर (ret < 0)
		जाओ err_unlock;

	data->dपढ़ोy_trigger_on = state;

	अगर (state) अणु
		ret = bmc150_magn_reset_पूर्णांकr(data);
		अगर (ret < 0)
			जाओ err_unlock;
	पूर्ण
	mutex_unlock(&data->mutex);

	वापस 0;

err_unlock:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops bmc150_magn_trigger_ops = अणु
	.set_trigger_state = bmc150_magn_data_rdy_trigger_set_state,
	.reenable = bmc150_magn_trig_reen,
पूर्ण;

अटल पूर्णांक bmc150_magn_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);

	वापस bmc150_magn_set_घातer_state(data, true);
पूर्ण

अटल पूर्णांक bmc150_magn_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);

	वापस bmc150_magn_set_घातer_state(data, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops bmc150_magn_buffer_setup_ops = अणु
	.preenable = bmc150_magn_buffer_preenable,
	.postdisable = bmc150_magn_buffer_postdisable,
पूर्ण;

अटल स्थिर अक्षर *bmc150_magn_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

पूर्णांक bmc150_magn_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		      पूर्णांक irq, स्थिर अक्षर *name)
अणु
	काष्ठा bmc150_magn_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	data->irq = irq;
	data->dev = dev;

	data->regulators[0].supply = "vdd";
	data->regulators[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	अगर (ret)
		वापस ret;

	अगर (!name && ACPI_HANDLE(dev))
		name = bmc150_magn_match_acpi_device(dev);

	mutex_init(&data->mutex);

	ret = bmc150_magn_init(data);
	अगर (ret < 0)
		वापस ret;

	indio_dev->channels = bmc150_magn_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmc150_magn_channels);
	indio_dev->available_scan_masks = bmc150_magn_scan_masks;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bmc150_magn_info;

	अगर (irq > 0) अणु
		data->dपढ़ोy_trig = devm_iio_trigger_alloc(dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		अगर (!data->dपढ़ोy_trig) अणु
			ret = -ENOMEM;
			dev_err(dev, "iio trigger alloc failed\n");
			जाओ err_घातeroff;
		पूर्ण

		data->dपढ़ोy_trig->ops = &bmc150_magn_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->dपढ़ोy_trig);
		अगर (ret) अणु
			dev_err(dev, "iio trigger register failed\n");
			जाओ err_घातeroff;
		पूर्ण

		ret = request_thपढ़ोed_irq(irq,
					   iio_trigger_generic_data_rdy_poll,
					   शून्य,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   BMC150_MAGN_IRQ_NAME,
					   data->dपढ़ोy_trig);
		अगर (ret < 0) अणु
			dev_err(dev, "request irq %d failed\n", irq);
			जाओ err_trigger_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_समय,
					 bmc150_magn_trigger_handler,
					 &bmc150_magn_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(dev, "iio triggered buffer setup failed\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev,
					 BMC150_MAGN_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	dev_dbg(dev, "Registered device %s\n", name);
	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_मुक्त_irq:
	अगर (irq > 0)
		मुक्त_irq(irq, data->dपढ़ोy_trig);
err_trigger_unरेजिस्टर:
	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
err_घातeroff:
	bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND, true);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(bmc150_magn_probe);

पूर्णांक bmc150_magn_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	iio_triggered_buffer_cleanup(indio_dev);

	अगर (data->irq > 0)
		मुक्त_irq(data->irq, data->dपढ़ोy_trig);

	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);

	mutex_lock(&data->mutex);
	bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND, true);
	mutex_unlock(&data->mutex);

	regulator_bulk_disable(ARRAY_SIZE(data->regulators), data->regulators);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bmc150_magn_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmc150_magn_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SLEEP,
					 true);
	mutex_unlock(&data->mutex);
	अगर (ret < 0) अणु
		dev_err(dev, "powering off device failed\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Should be called with data->mutex held.
 */
अटल पूर्णांक bmc150_magn_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);

	वापस bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_NORMAL,
					  true);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bmc150_magn_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_SLEEP,
					 true);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक bmc150_magn_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmc150_magn_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_set_घातer_mode(data, BMC150_MAGN_POWER_MODE_NORMAL,
					 true);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops bmc150_magn_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bmc150_magn_suspend, bmc150_magn_resume)
	SET_RUNTIME_PM_OPS(bmc150_magn_runसमय_suspend,
			   bmc150_magn_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL(bmc150_magn_pm_ops);

MODULE_AUTHOR("Irina Tirdea <irina.tirdea@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMC150 magnetometer core driver");
