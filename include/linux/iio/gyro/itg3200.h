<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * itg3200.h -- support InvenSense ITG3200
 *              Digital 3-Axis Gyroscope driver
 *
 * Copyright (c) 2011 Christian Strobel <christian.strobel@iis.fraunhofer.de>
 * Copyright (c) 2011 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 * Copyright (c) 2012 Thorsten Nowak <thorsten.nowak@iis.fraunhofer.de>
 */

#अगर_अघोषित I2C_ITG3200_H_
#घोषणा I2C_ITG3200_H_

#समावेश <linux/iio/iपन.स>

/* Register with I2C address (34h) */
#घोषणा ITG3200_REG_ADDRESS		0x00

/* Sample rate भागider
 * Range: 0 to 255
 * Default value: 0x00 */
#घोषणा ITG3200_REG_SAMPLE_RATE_DIV	0x15

/* Digital low pass filter settings */
#घोषणा ITG3200_REG_DLPF		0x16
/* DLPF full scale range */
#घोषणा ITG3200_DLPF_FS_SEL_2000	0x18
/* Bandwidth (Hz) and पूर्णांकernal sample rate
 * (kHz) of DLPF */
#घोषणा ITG3200_DLPF_256_8		0x00
#घोषणा ITG3200_DLPF_188_1		0x01
#घोषणा ITG3200_DLPF_98_1		0x02
#घोषणा ITG3200_DLPF_42_1		0x03
#घोषणा ITG3200_DLPF_20_1		0x04
#घोषणा ITG3200_DLPF_10_1		0x05
#घोषणा ITG3200_DLPF_5_1		0x06

#घोषणा ITG3200_DLPF_CFG_MASK		0x07

/* Configuration क्रम पूर्णांकerrupt operations */
#घोषणा ITG3200_REG_IRQ_CONFIG		0x17
/* Logic level */
#घोषणा ITG3200_IRQ_ACTIVE_LOW		0x80
#घोषणा ITG3200_IRQ_ACTIVE_HIGH		0x00
/* Drive type */
#घोषणा ITG3200_IRQ_OPEN_DRAIN		0x40
#घोषणा ITG3200_IRQ_PUSH_PULL		0x00
/* Latch mode */
#घोषणा ITG3200_IRQ_LATCH_UNTIL_CLEARED	0x20
#घोषणा ITG3200_IRQ_LATCH_50US_PULSE	0x00
/* Latch clear method */
#घोषणा ITG3200_IRQ_LATCH_CLEAR_ANY	0x10
#घोषणा ITG3200_IRQ_LATCH_CLEAR_STATUS	0x00
/* Enable पूर्णांकerrupt when device is पढ़ोy */
#घोषणा ITG3200_IRQ_DEVICE_RDY_ENABLE	0x04
/* Enable पूर्णांकerrupt when data is available */
#घोषणा ITG3200_IRQ_DATA_RDY_ENABLE	0x01

/* Determine the status of ITG-3200 पूर्णांकerrupts */
#घोषणा ITG3200_REG_IRQ_STATUS		0x1A
/* Status of 'device is ready'-पूर्णांकerrupt */
#घोषणा ITG3200_IRQ_DEVICE_RDY_STATUS	0x04
/* Status of 'data is available'-पूर्णांकerrupt */
#घोषणा ITG3200_IRQ_DATA_RDY_STATUS	0x01

/* Sensor रेजिस्टरs */
#घोषणा ITG3200_REG_TEMP_OUT_H		0x1B
#घोषणा ITG3200_REG_TEMP_OUT_L		0x1C
#घोषणा ITG3200_REG_GYRO_XOUT_H		0x1D
#घोषणा ITG3200_REG_GYRO_XOUT_L		0x1E
#घोषणा ITG3200_REG_GYRO_YOUT_H		0x1F
#घोषणा ITG3200_REG_GYRO_YOUT_L		0x20
#घोषणा ITG3200_REG_GYRO_ZOUT_H		0x21
#घोषणा ITG3200_REG_GYRO_ZOUT_L		0x22

/* Power management */
#घोषणा ITG3200_REG_POWER_MANAGEMENT	0x3E
/* Reset device and पूर्णांकernal रेजिस्टरs to the
 * घातer-up-शेष settings */
#घोषणा ITG3200_RESET			0x80
/* Enable low घातer sleep mode */
#घोषणा ITG3200_SLEEP			0x40
/* Put according gyroscope in standby mode */
#घोषणा ITG3200_STANDBY_GYRO_X		0x20
#घोषणा ITG3200_STANDBY_GYRO_Y		0x10
#घोषणा ITG3200_STANDBY_GYRO_Z		0x08
/* Determine the device घड़ी source */
#घोषणा ITG3200_CLK_INTERNAL		0x00
#घोषणा ITG3200_CLK_GYRO_X		0x01
#घोषणा ITG3200_CLK_GYRO_Y		0x02
#घोषणा ITG3200_CLK_GYRO_Z		0x03
#घोषणा ITG3200_CLK_EXT_32K		0x04
#घोषणा ITG3200_CLK_EXT_19M		0x05


/**
 * काष्ठा itg3200 - device instance specअगरic data
 * @i2c:    actual i2c_client
 * @trig:   data पढ़ोy trigger from itg3200 pin
 **/
काष्ठा itg3200 अणु
	काष्ठा i2c_client	*i2c;
	काष्ठा iio_trigger	*trig;
	काष्ठा iio_mount_matrix orientation;
पूर्ण;

क्रमागत ITG3200_SCAN_INDEX अणु
	ITG3200_SCAN_TEMP,
	ITG3200_SCAN_GYRO_X,
	ITG3200_SCAN_GYRO_Y,
	ITG3200_SCAN_GYRO_Z,
	ITG3200_SCAN_ELEMENTS,
पूर्ण;

पूर्णांक itg3200_ग_लिखो_reg_8(काष्ठा iio_dev *indio_dev,
		u8 reg_address, u8 val);

पूर्णांक itg3200_पढ़ो_reg_8(काष्ठा iio_dev *indio_dev,
		u8 reg_address, u8 *val);


#अगर_घोषित CONFIG_IIO_BUFFER

व्योम itg3200_हटाओ_trigger(काष्ठा iio_dev *indio_dev);
पूर्णांक itg3200_probe_trigger(काष्ठा iio_dev *indio_dev);

पूर्णांक itg3200_buffer_configure(काष्ठा iio_dev *indio_dev);
व्योम itg3200_buffer_unconfigure(काष्ठा iio_dev *indio_dev);

#अन्यथा /* CONFIG_IIO_BUFFER */

अटल अंतरभूत व्योम itg3200_हटाओ_trigger(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक itg3200_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक itg3200_buffer_configure(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम itg3200_buffer_unconfigure(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण

#पूर्ण_अगर  /* CONFIG_IIO_BUFFER */

#पूर्ण_अगर /* ITG3200_H_ */
