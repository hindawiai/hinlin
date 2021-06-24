<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD5592R / AD5593R Digital <-> Analog converters driver
 *
 * Copyright 2015-2016 Analog Devices Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
 */

#अगर_अघोषित __DRIVERS_IIO_DAC_AD5592R_BASE_H__
#घोषणा __DRIVERS_IIO_DAC_AD5592R_BASE_H__

#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gpio/driver.h>

काष्ठा device;
काष्ठा ad5592r_state;

क्रमागत ad5592r_रेजिस्टरs अणु
	AD5592R_REG_NOOP		= 0x0,
	AD5592R_REG_DAC_READBACK	= 0x1,
	AD5592R_REG_ADC_SEQ		= 0x2,
	AD5592R_REG_CTRL		= 0x3,
	AD5592R_REG_ADC_EN		= 0x4,
	AD5592R_REG_DAC_EN		= 0x5,
	AD5592R_REG_PULLDOWN		= 0x6,
	AD5592R_REG_LDAC		= 0x7,
	AD5592R_REG_GPIO_OUT_EN		= 0x8,
	AD5592R_REG_GPIO_SET		= 0x9,
	AD5592R_REG_GPIO_IN_EN		= 0xA,
	AD5592R_REG_PD			= 0xB,
	AD5592R_REG_OPEN_DRAIN		= 0xC,
	AD5592R_REG_TRISTATE		= 0xD,
	AD5592R_REG_RESET		= 0xF,
पूर्ण;

#घोषणा AD5592R_REG_PD_EN_REF		BIT(9)
#घोषणा AD5592R_REG_CTRL_ADC_RANGE	BIT(5)
#घोषणा AD5592R_REG_CTRL_DAC_RANGE	BIT(4)

काष्ठा ad5592r_rw_ops अणु
	पूर्णांक (*ग_लिखो_dac)(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 value);
	पूर्णांक (*पढ़ो_adc)(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 *value);
	पूर्णांक (*reg_ग_लिखो)(काष्ठा ad5592r_state *st, u8 reg, u16 value);
	पूर्णांक (*reg_पढ़ो)(काष्ठा ad5592r_state *st, u8 reg, u16 *value);
	पूर्णांक (*gpio_पढ़ो)(काष्ठा ad5592r_state *st, u8 *value);
पूर्ण;

काष्ठा ad5592r_state अणु
	काष्ठा device *dev;
	काष्ठा regulator *reg;
	काष्ठा gpio_chip gpiochip;
	काष्ठा mutex gpio_lock;	/* Protect cached gpio_out, gpio_val, etc. */
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा ad5592r_rw_ops *ops;
	पूर्णांक scale_avail[2][2];
	u16 cached_dac[8];
	u16 cached_gp_ctrl;
	u8 channel_modes[8];
	u8 channel_ofख_स्थितिe[8];
	u8 gpio_map;
	u8 gpio_out;
	u8 gpio_in;
	u8 gpio_val;

	__be16 spi_msg ____cacheline_aligned;
	__be16 spi_msg_nop;
पूर्ण;

पूर्णांक ad5592r_probe(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर काष्ठा ad5592r_rw_ops *ops);
पूर्णांक ad5592r_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर /* __DRIVERS_IIO_DAC_AD5592R_BASE_H__ */
