<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 TDK-InvenSense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>

#समावेश "inv_mpu_aux.h"
#समावेश "inv_mpu_iio.h"
#समावेश "inv_mpu_magn.h"

/*
 * MPU9xxx magnetometer are AKM chips on I2C aux bus
 * MPU9150 is AK8975
 * MPU9250 is AK8963
 */
#घोषणा INV_MPU_MAGN_I2C_ADDR		0x0C

#घोषणा INV_MPU_MAGN_REG_WIA		0x00
#घोषणा INV_MPU_MAGN_BITS_WIA		0x48

#घोषणा INV_MPU_MAGN_REG_ST1		0x02
#घोषणा INV_MPU_MAGN_BIT_DRDY		0x01
#घोषणा INV_MPU_MAGN_BIT_DOR		0x02

#घोषणा INV_MPU_MAGN_REG_DATA		0x03

#घोषणा INV_MPU_MAGN_REG_ST2		0x09
#घोषणा INV_MPU_MAGN_BIT_HOFL		0x08
#घोषणा INV_MPU_MAGN_BIT_BITM		0x10

#घोषणा INV_MPU_MAGN_REG_CNTL1		0x0A
#घोषणा INV_MPU_MAGN_BITS_MODE_PWDN	0x00
#घोषणा INV_MPU_MAGN_BITS_MODE_SINGLE	0x01
#घोषणा INV_MPU_MAGN_BITS_MODE_FUSE	0x0F
#घोषणा INV_MPU9250_MAGN_BIT_OUTPUT_BIT	0x10

#घोषणा INV_MPU9250_MAGN_REG_CNTL2	0x0B
#घोषणा INV_MPU9250_MAGN_BIT_SRST	0x01

#घोषणा INV_MPU_MAGN_REG_ASAX		0x10
#घोषणा INV_MPU_MAGN_REG_ASAY		0x11
#घोषणा INV_MPU_MAGN_REG_ASAZ		0x12

अटल bool inv_magn_supported(स्थिर काष्ठा inv_mpu6050_state *st)
अणु
	चयन (st->chip_type) अणु
	हाल INV_MPU9150:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* init magnetometer chip */
अटल पूर्णांक inv_magn_init(काष्ठा inv_mpu6050_state *st)
अणु
	uपूर्णांक8_t val;
	uपूर्णांक8_t asa[3];
	पूर्णांक32_t sensitivity;
	पूर्णांक ret;

	/* check whoami */
	ret = inv_mpu_aux_पढ़ो(st, INV_MPU_MAGN_I2C_ADDR, INV_MPU_MAGN_REG_WIA,
			       &val, माप(val));
	अगर (ret)
		वापस ret;
	अगर (val != INV_MPU_MAGN_BITS_WIA)
		वापस -ENODEV;

	/* software reset क्रम MPU925x only */
	चयन (st->chip_type) अणु
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		ret = inv_mpu_aux_ग_लिखो(st, INV_MPU_MAGN_I2C_ADDR,
					INV_MPU9250_MAGN_REG_CNTL2,
					INV_MPU9250_MAGN_BIT_SRST);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* पढ़ो fuse ROM data */
	ret = inv_mpu_aux_ग_लिखो(st, INV_MPU_MAGN_I2C_ADDR,
				INV_MPU_MAGN_REG_CNTL1,
				INV_MPU_MAGN_BITS_MODE_FUSE);
	अगर (ret)
		वापस ret;

	ret = inv_mpu_aux_पढ़ो(st, INV_MPU_MAGN_I2C_ADDR, INV_MPU_MAGN_REG_ASAX,
			       asa, माप(asa));
	अगर (ret)
		वापस ret;

	/* चयन back to घातer-करोwn */
	ret = inv_mpu_aux_ग_लिखो(st, INV_MPU_MAGN_I2C_ADDR,
				INV_MPU_MAGN_REG_CNTL1,
				INV_MPU_MAGN_BITS_MODE_PWDN);
	अगर (ret)
		वापस ret;

	/*
	 * Sensor sentivity
	 * 1 uT = 0.01 G and value is in micron (1e6)
	 * sensitvity = x uT * 0.01 * 1e6
	 */
	चयन (st->chip_type) अणु
	हाल INV_MPU9150:
		/* sensor sensitivity is 0.3 uT */
		sensitivity = 3000;
		अवरोध;
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		/* sensor sensitivity in 16 bits mode: 0.15 uT */
		sensitivity = 1500;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Sensitivity adjustement and scale to Gauss
	 *
	 * Hadj = H * (((ASA - 128) * 0.5 / 128) + 1)
	 * Factor simplअगरication:
	 * Hadj = H * ((ASA + 128) / 256)
	 *
	 * raw_to_gauss = Hadj * sensitivity
	 */
	st->magn_raw_to_gauss[0] = (((पूर्णांक32_t)asa[0] + 128) * sensitivity) / 256;
	st->magn_raw_to_gauss[1] = (((पूर्णांक32_t)asa[1] + 128) * sensitivity) / 256;
	st->magn_raw_to_gauss[2] = (((पूर्णांक32_t)asa[2] + 128) * sensitivity) / 256;

	वापस 0;
पूर्ण

/**
 * inv_mpu_magn_probe() - probe and setup magnetometer chip
 * @st: driver पूर्णांकernal state
 *
 * Returns 0 on success, a negative error code otherwise
 *
 * It is probing the chip and setting up all needed i2c transfers.
 * Noop अगर there is no magnetometer in the chip.
 */
पूर्णांक inv_mpu_magn_probe(काष्ठा inv_mpu6050_state *st)
अणु
	uपूर्णांक8_t val;
	पूर्णांक ret;

	/* quit अगर chip is not supported */
	अगर (!inv_magn_supported(st))
		वापस 0;

	/* configure i2c master aux port */
	ret = inv_mpu_aux_init(st);
	अगर (ret)
		वापस ret;

	/* check and init mag chip */
	ret = inv_magn_init(st);
	अगर (ret)
		वापस ret;

	/*
	 * configure mpu i2c master accesses
	 * i2c SLV0: पढ़ो sensor data, 7 bytes data(6)-ST2
	 * Byte swap data to store them in big-endian in impair address groups
	 */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_ADDR(0),
			   INV_MPU6050_BIT_I2C_SLV_RNW | INV_MPU_MAGN_I2C_ADDR);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_REG(0),
			   INV_MPU_MAGN_REG_DATA);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0),
			   INV_MPU6050_BIT_SLV_EN |
			   INV_MPU6050_BIT_SLV_BYTE_SW |
			   INV_MPU6050_BIT_SLV_GRP |
			   INV_MPU9X50_BYTES_MAGN);
	अगर (ret)
		वापस ret;

	/* i2c SLV1: launch single measurement */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_ADDR(1),
			   INV_MPU_MAGN_I2C_ADDR);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_REG(1),
			   INV_MPU_MAGN_REG_CNTL1);
	अगर (ret)
		वापस ret;

	/* add 16 bits mode क्रम MPU925x */
	val = INV_MPU_MAGN_BITS_MODE_SINGLE;
	चयन (st->chip_type) अणु
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		val |= INV_MPU9250_MAGN_BIT_OUTPUT_BIT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_DO(1), val);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(1),
			    INV_MPU6050_BIT_SLV_EN | 1);
पूर्ण

/**
 * inv_mpu_magn_set_rate() - set magnetometer sampling rate
 * @st: driver पूर्णांकernal state
 * @fअगरo_rate: mpu set fअगरo rate
 *
 * Returns 0 on success, a negative error code otherwise
 *
 * Limit sampling frequency to the maximum value supported by the
 * magnetometer chip. Resulting in duplicated data क्रम higher frequencies.
 * Noop अगर there is no magnetometer in the chip.
 */
पूर्णांक inv_mpu_magn_set_rate(स्थिर काष्ठा inv_mpu6050_state *st, पूर्णांक fअगरo_rate)
अणु
	uपूर्णांक8_t d;

	/* quit अगर chip is not supported */
	अगर (!inv_magn_supported(st))
		वापस 0;

	/*
	 * update i2c master delay to limit mag sampling to max frequency
	 * compute fअगरo_rate भागider d: rate = fअगरo_rate / (d + 1)
	 */
	अगर (fअगरo_rate > INV_MPU_MAGN_FREQ_HZ_MAX)
		d = fअगरo_rate / INV_MPU_MAGN_FREQ_HZ_MAX - 1;
	अन्यथा
		d = 0;

	वापस regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV4_CTRL, d);
पूर्ण

/**
 * inv_mpu_magn_set_orient() - fill magnetometer mounting matrix
 * @st: driver पूर्णांकernal state
 *
 * Returns 0 on success, a negative error code otherwise
 *
 * Fill magnetometer mounting matrix using the provided chip matrix.
 */
पूर्णांक inv_mpu_magn_set_orient(काष्ठा inv_mpu6050_state *st)
अणु
	स्थिर अक्षर *orient;
	अक्षर *str;
	पूर्णांक i;

	/* fill magnetometer orientation */
	चयन (st->chip_type) अणु
	हाल INV_MPU9150:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		/* x <- y */
		st->magn_orient.rotation[0] = st->orientation.rotation[3];
		st->magn_orient.rotation[1] = st->orientation.rotation[4];
		st->magn_orient.rotation[2] = st->orientation.rotation[5];
		/* y <- x */
		st->magn_orient.rotation[3] = st->orientation.rotation[0];
		st->magn_orient.rotation[4] = st->orientation.rotation[1];
		st->magn_orient.rotation[5] = st->orientation.rotation[2];
		/* z <- -z */
		क्रम (i = 0; i < 3; ++i) अणु
			orient = st->orientation.rotation[6 + i];
			/* use length + 2 क्रम adding minus sign अगर needed */
			str = devm_kzalloc(regmap_get_device(st->map),
					   म_माप(orient) + 2, GFP_KERNEL);
			अगर (str == शून्य)
				वापस -ENOMEM;
			अगर (म_भेद(orient, "0") == 0) अणु
				म_नकल(str, orient);
			पूर्ण अन्यथा अगर (orient[0] == '-') अणु
				म_नकल(str, &orient[1]);
			पूर्ण अन्यथा अणु
				str[0] = '-';
				म_नकल(&str[1], orient);
			पूर्ण
			st->magn_orient.rotation[6 + i] = str;
		पूर्ण
		अवरोध;
	शेष:
		st->magn_orient = st->orientation;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * inv_mpu_magn_पढ़ो() - पढ़ो magnetometer data
 * @st: driver पूर्णांकernal state
 * @axis: IIO modअगरier axis value
 * @val: store corresponding axis value
 *
 * Returns 0 on success, a negative error code otherwise
 */
पूर्णांक inv_mpu_magn_पढ़ो(काष्ठा inv_mpu6050_state *st, पूर्णांक axis, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक status;
	__be16 data;
	uपूर्णांक8_t addr;
	पूर्णांक ret;

	/* quit अगर chip is not supported */
	अगर (!inv_magn_supported(st))
		वापस -ENODEV;

	/* Mag data: XH,XL,YH,YL,ZH,ZL */
	चयन (axis) अणु
	हाल IIO_MOD_X:
		addr = 0;
		अवरोध;
	हाल IIO_MOD_Y:
		addr = 2;
		अवरोध;
	हाल IIO_MOD_Z:
		addr = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	addr += INV_MPU6050_REG_EXT_SENS_DATA;

	/* check i2c status and पढ़ो raw data */
	ret = regmap_पढ़ो(st->map, INV_MPU6050_REG_I2C_MST_STATUS, &status);
	अगर (ret)
		वापस ret;

	अगर (status & INV_MPU6050_BIT_I2C_SLV0_NACK ||
			status & INV_MPU6050_BIT_I2C_SLV1_NACK)
		वापस -EIO;

	ret = regmap_bulk_पढ़ो(st->map, addr, &data, माप(data));
	अगर (ret)
		वापस ret;

	*val = (पूर्णांक16_t)be16_to_cpu(data);

	वापस IIO_VAL_INT;
पूर्ण
