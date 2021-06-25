<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register स्थिरants and other क्रमward declarations needed by the bma400
 * sources.
 *
 * Copyright 2019 Dan Robertson <dan@dlrobertson.com>
 */

#अगर_अघोषित _BMA400_H_
#घोषणा _BMA400_H_

#समावेश <linux/bits.h>
#समावेश <linux/regmap.h>

/*
 * Read-Only Registers
 */

/* Status and ID रेजिस्टरs */
#घोषणा BMA400_CHIP_ID_REG          0x00
#घोषणा BMA400_ERR_REG              0x02
#घोषणा BMA400_STATUS_REG           0x03

/* Acceleration रेजिस्टरs */
#घोषणा BMA400_X_AXIS_LSB_REG       0x04
#घोषणा BMA400_X_AXIS_MSB_REG       0x05
#घोषणा BMA400_Y_AXIS_LSB_REG       0x06
#घोषणा BMA400_Y_AXIS_MSB_REG       0x07
#घोषणा BMA400_Z_AXIS_LSB_REG       0x08
#घोषणा BMA400_Z_AXIS_MSB_REG       0x09

/* Sensor समय रेजिस्टरs */
#घोषणा BMA400_SENSOR_TIME0         0x0a
#घोषणा BMA400_SENSOR_TIME1         0x0b
#घोषणा BMA400_SENSOR_TIME2         0x0c

/* Event and पूर्णांकerrupt रेजिस्टरs */
#घोषणा BMA400_EVENT_REG            0x0d
#घोषणा BMA400_INT_STAT0_REG        0x0e
#घोषणा BMA400_INT_STAT1_REG        0x0f
#घोषणा BMA400_INT_STAT2_REG        0x10

/* Temperature रेजिस्टर */
#घोषणा BMA400_TEMP_DATA_REG        0x11

/* FIFO length and data रेजिस्टरs */
#घोषणा BMA400_FIFO_LENGTH0_REG     0x12
#घोषणा BMA400_FIFO_LENGTH1_REG     0x13
#घोषणा BMA400_FIFO_DATA_REG        0x14

/* Step count रेजिस्टरs */
#घोषणा BMA400_STEP_CNT0_REG        0x15
#घोषणा BMA400_STEP_CNT1_REG        0x16
#घोषणा BMA400_STEP_CNT3_REG        0x17
#घोषणा BMA400_STEP_STAT_REG        0x18

/*
 * Read-ग_लिखो configuration रेजिस्टरs
 */
#घोषणा BMA400_ACC_CONFIG0_REG      0x19
#घोषणा BMA400_ACC_CONFIG1_REG      0x1a
#घोषणा BMA400_ACC_CONFIG2_REG      0x1b
#घोषणा BMA400_CMD_REG              0x7e

/* Chip ID of BMA 400 devices found in the chip ID रेजिस्टर. */
#घोषणा BMA400_ID_REG_VAL           0x90

#घोषणा BMA400_LP_OSR_SHIFT         5
#घोषणा BMA400_NP_OSR_SHIFT         4
#घोषणा BMA400_SCALE_SHIFT          6

#घोषणा BMA400_TWO_BITS_MASK        GENMASK(1, 0)
#घोषणा BMA400_LP_OSR_MASK          GENMASK(6, 5)
#घोषणा BMA400_NP_OSR_MASK          GENMASK(5, 4)
#घोषणा BMA400_ACC_ODR_MASK         GENMASK(3, 0)
#घोषणा BMA400_ACC_SCALE_MASK       GENMASK(7, 6)

#घोषणा BMA400_ACC_ODR_MIN_RAW      0x05
#घोषणा BMA400_ACC_ODR_LP_RAW       0x06
#घोषणा BMA400_ACC_ODR_MAX_RAW      0x0b

#घोषणा BMA400_ACC_ODR_MAX_HZ       800
#घोषणा BMA400_ACC_ODR_MIN_WHOLE_HZ 25
#घोषणा BMA400_ACC_ODR_MIN_HZ       12

#घोषणा BMA400_SCALE_MIN            38357
#घोषणा BMA400_SCALE_MAX            306864

#घोषणा BMA400_NUM_REGULATORS       2
#घोषणा BMA400_VDD_REGULATOR        0
#घोषणा BMA400_VDDIO_REGULATOR      1

बाह्य स्थिर काष्ठा regmap_config bma400_regmap_config;

पूर्णांक bma400_probe(काष्ठा device *dev, काष्ठा regmap *regmap, स्थिर अक्षर *name);

पूर्णांक bma400_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर
