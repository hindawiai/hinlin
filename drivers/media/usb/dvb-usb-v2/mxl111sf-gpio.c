<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl111sf-gpio.c - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "mxl111sf-gpio.h"
#समावेश "mxl111sf-i2c.h"
#समावेश "mxl111sf.h"

/* ------------------------------------------------------------------------- */

#घोषणा MXL_GPIO_MUX_REG_0 0x84
#घोषणा MXL_GPIO_MUX_REG_1 0x89
#घोषणा MXL_GPIO_MUX_REG_2 0x82

#घोषणा MXL_GPIO_सूची_INPUT  0
#घोषणा MXL_GPIO_सूची_OUTPUT 1


अटल पूर्णांक mxl111sf_set_gpo_state(काष्ठा mxl111sf_state *state, u8 pin, u8 val)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	mxl_debug_adv("(%d, %d)", pin, val);

	अगर ((pin > 0) && (pin < 8)) अणु
		ret = mxl111sf_पढ़ो_reg(state, 0x19, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		पंचांगp &= ~(1 << (pin - 1));
		पंचांगp |= (val << (pin - 1));
		ret = mxl111sf_ग_लिखो_reg(state, 0x19, पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण अन्यथा अगर (pin <= 10) अणु
		अगर (pin == 0)
			pin += 7;
		ret = mxl111sf_पढ़ो_reg(state, 0x30, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		पंचांगp &= ~(1 << (pin - 3));
		पंचांगp |= (val << (pin - 3));
		ret = mxl111sf_ग_लिखो_reg(state, 0x30, पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
	पूर्ण अन्यथा
		ret = -EINVAL;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_get_gpi_state(काष्ठा mxl111sf_state *state, u8 pin, u8 *val)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	mxl_debug("(0x%02x)", pin);

	*val = 0;

	चयन (pin) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
		ret = mxl111sf_पढ़ो_reg(state, 0x23, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		*val = (पंचांगp >> (pin + 4)) & 0x01;
		अवरोध;
	हाल 4:
	हाल 5:
	हाल 6:
	हाल 7:
		ret = mxl111sf_पढ़ो_reg(state, 0x2f, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		*val = (पंचांगp >> pin) & 0x01;
		अवरोध;
	हाल 8:
	हाल 9:
	हाल 10:
		ret = mxl111sf_पढ़ो_reg(state, 0x22, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		*val = (पंचांगp >> (pin - 3)) & 0x01;
		अवरोध;
	शेष:
		वापस -EINVAL; /* invalid pin */
	पूर्ण
fail:
	वापस ret;
पूर्ण

काष्ठा mxl_gpio_cfg अणु
	u8 pin;
	u8 dir;
	u8 val;
पूर्ण;

अटल पूर्णांक mxl111sf_config_gpio_pins(काष्ठा mxl111sf_state *state,
				     काष्ठा mxl_gpio_cfg *gpio_cfg)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	mxl_debug_adv("(%d, %d)", gpio_cfg->pin, gpio_cfg->dir);

	चयन (gpio_cfg->pin) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
		ret = mxl111sf_पढ़ो_reg(state, MXL_GPIO_MUX_REG_0, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		पंचांगp &= ~(1 << (gpio_cfg->pin + 4));
		पंचांगp |= (gpio_cfg->dir << (gpio_cfg->pin + 4));
		ret = mxl111sf_ग_लिखो_reg(state, MXL_GPIO_MUX_REG_0, पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		अवरोध;
	हाल 4:
	हाल 5:
	हाल 6:
	हाल 7:
		ret = mxl111sf_पढ़ो_reg(state, MXL_GPIO_MUX_REG_1, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		पंचांगp &= ~(1 << gpio_cfg->pin);
		पंचांगp |= (gpio_cfg->dir << gpio_cfg->pin);
		ret = mxl111sf_ग_लिखो_reg(state, MXL_GPIO_MUX_REG_1, पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		अवरोध;
	हाल 8:
	हाल 9:
	हाल 10:
		ret = mxl111sf_पढ़ो_reg(state, MXL_GPIO_MUX_REG_2, &पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		पंचांगp &= ~(1 << (gpio_cfg->pin - 3));
		पंचांगp |= (gpio_cfg->dir << (gpio_cfg->pin - 3));
		ret = mxl111sf_ग_लिखो_reg(state, MXL_GPIO_MUX_REG_2, पंचांगp);
		अगर (mxl_fail(ret))
			जाओ fail;
		अवरोध;
	शेष:
		वापस -EINVAL; /* invalid pin */
	पूर्ण

	ret = (MXL_GPIO_सूची_OUTPUT == gpio_cfg->dir) ?
		mxl111sf_set_gpo_state(state,
				       gpio_cfg->pin, gpio_cfg->val) :
		mxl111sf_get_gpi_state(state,
				       gpio_cfg->pin, &gpio_cfg->val);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_hw_करो_set_gpio(काष्ठा mxl111sf_state *state,
				   पूर्णांक gpio, पूर्णांक direction, पूर्णांक val)
अणु
	काष्ठा mxl_gpio_cfg gpio_config = अणु
		.pin = gpio,
		.dir = direction,
		.val = val,
	पूर्ण;

	mxl_debug("(%d, %d, %d)", gpio, direction, val);

	वापस mxl111sf_config_gpio_pins(state, &gpio_config);
पूर्ण

/* ------------------------------------------------------------------------- */

#घोषणा PIN_MUX_MPEG_MODE_MASK          0x40   /* 0x17 <6> */
#घोषणा PIN_MUX_MPEG_PAR_EN_MASK        0x01   /* 0x18 <0> */
#घोषणा PIN_MUX_MPEG_SER_EN_MASK        0x02   /* 0x18 <1> */
#घोषणा PIN_MUX_MPG_IN_MUX_MASK         0x80   /* 0x3D <7> */
#घोषणा PIN_MUX_BT656_ENABLE_MASK       0x04   /* 0x12 <2> */
#घोषणा PIN_MUX_I2S_ENABLE_MASK         0x40   /* 0x15 <6> */
#घोषणा PIN_MUX_SPI_MODE_MASK           0x10   /* 0x3D <4> */
#घोषणा PIN_MUX_MCLK_EN_CTRL_MASK       0x10   /* 0x82 <4> */
#घोषणा PIN_MUX_MPSYN_EN_CTRL_MASK      0x20   /* 0x82 <5> */
#घोषणा PIN_MUX_MDVAL_EN_CTRL_MASK      0x40   /* 0x82 <6> */
#घोषणा PIN_MUX_MPERR_EN_CTRL_MASK      0x80   /* 0x82 <7> */
#घोषणा PIN_MUX_MDAT_EN_0_MASK          0x10   /* 0x84 <4> */
#घोषणा PIN_MUX_MDAT_EN_1_MASK          0x20   /* 0x84 <5> */
#घोषणा PIN_MUX_MDAT_EN_2_MASK          0x40   /* 0x84 <6> */
#घोषणा PIN_MUX_MDAT_EN_3_MASK          0x80   /* 0x84 <7> */
#घोषणा PIN_MUX_MDAT_EN_4_MASK          0x10   /* 0x89 <4> */
#घोषणा PIN_MUX_MDAT_EN_5_MASK          0x20   /* 0x89 <5> */
#घोषणा PIN_MUX_MDAT_EN_6_MASK          0x40   /* 0x89 <6> */
#घोषणा PIN_MUX_MDAT_EN_7_MASK          0x80   /* 0x89 <7> */

पूर्णांक mxl111sf_config_pin_mux_modes(काष्ठा mxl111sf_state *state,
				  क्रमागत mxl111sf_mux_config pin_mux_config)
अणु
	u8 r12, r15, r17, r18, r3D, r82, r84, r89;
	पूर्णांक ret;

	mxl_debug("(%d)", pin_mux_config);

	ret = mxl111sf_पढ़ो_reg(state, 0x17, &r17);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x18, &r18);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x12, &r12);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x15, &r15);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x82, &r82);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x84, &r84);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x89, &r89);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_पढ़ो_reg(state, 0x3D, &r3D);
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन (pin_mux_config) अणु
	हाल PIN_MUX_TS_OUT_PARALLEL:
		/* mpeg_mode = 1 */
		r17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 1 */
		r18 |= PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 0 */
		r18 &= ~PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 1 */
		r82 |= PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 1 */
		r82 |= PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 1 */
		r82 |= PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 1 */
		r82 |= PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0xF */
		r84 |= 0xF0;
		/* mdat_en_ctrl[7:4] = 0xF */
		r89 |= 0xF0;
		अवरोध;
	हाल PIN_MUX_TS_OUT_SERIAL:
		/* mpeg_mode = 1 */
		r17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 1 */
		r18 |= PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 1 */
		r82 |= PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 1 */
		r82 |= PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 1 */
		r82 |= PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 1 */
		r82 |= PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0xF */
		r84 |= 0xF0;
		/* mdat_en_ctrl[7:4] = 0xF */
		r89 |= 0xF0;
		अवरोध;
	हाल PIN_MUX_GPIO_MODE:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 0 */
		r18 &= ~PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_TS_SERIAL_IN_MODE_0:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 1 */
		r18 |= PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_TS_SERIAL_IN_MODE_1:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 1 */
		r18 |= PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 1 */
		r3D |= PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_TS_SPI_IN_MODE_1:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 1 */
		r18 |= PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 1 */
		r3D |= PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 1 */
		r15 |= PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 1 */
		r3D |= PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_TS_SPI_IN_MODE_0:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 1 */
		r18 |= PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 1 */
		r15 |= PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 1 */
		r3D |= PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_TS_PARALLEL_IN:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 1 */
		r18 |= PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 0 */
		r18 &= ~PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_BT656_I2S_MODE:
		/* mpeg_mode = 0 */
		r17 &= ~PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 0 */
		r18 &= ~PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 1 */
		r12 |= PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 1 */
		r15 |= PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	हाल PIN_MUX_DEFAULT:
	शेष:
		/* mpeg_mode = 1 */
		r17 |= PIN_MUX_MPEG_MODE_MASK;
		/* mpeg_par_en = 0 */
		r18 &= ~PIN_MUX_MPEG_PAR_EN_MASK;
		/* mpeg_ser_en = 0 */
		r18 &= ~PIN_MUX_MPEG_SER_EN_MASK;
		/* mpg_in_mux = 0 */
		r3D &= ~PIN_MUX_MPG_IN_MUX_MASK;
		/* bt656_enable = 0 */
		r12 &= ~PIN_MUX_BT656_ENABLE_MASK;
		/* i2s_enable = 0 */
		r15 &= ~PIN_MUX_I2S_ENABLE_MASK;
		/* spi_mode = 0 */
		r3D &= ~PIN_MUX_SPI_MODE_MASK;
		/* mclk_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MCLK_EN_CTRL_MASK;
		/* mperr_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPERR_EN_CTRL_MASK;
		/* mdval_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MDVAL_EN_CTRL_MASK;
		/* mpsyn_en_ctrl = 0 */
		r82 &= ~PIN_MUX_MPSYN_EN_CTRL_MASK;
		/* mdat_en_ctrl[3:0] = 0x0 */
		r84 &= 0x0F;
		/* mdat_en_ctrl[7:4] = 0x0 */
		r89 &= 0x0F;
		अवरोध;
	पूर्ण

	ret = mxl111sf_ग_लिखो_reg(state, 0x17, r17);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x18, r18);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x12, r12);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x15, r15);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x82, r82);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x84, r84);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x89, r89);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x3D, r3D);
	अगर (mxl_fail(ret))
		जाओ fail;
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl111sf_hw_set_gpio(काष्ठा mxl111sf_state *state, पूर्णांक gpio, पूर्णांक val)
अणु
	वापस mxl111sf_hw_करो_set_gpio(state, gpio, MXL_GPIO_सूची_OUTPUT, val);
पूर्ण

अटल पूर्णांक mxl111sf_hw_gpio_initialize(काष्ठा mxl111sf_state *state)
अणु
	u8 gpioval = 0x07; /* ग_लिखो protect enabled, संकेत LEDs off */
	पूर्णांक i, ret;

	mxl_debug("()");

	क्रम (i = 3; i < 8; i++) अणु
		ret = mxl111sf_hw_set_gpio(state, i, (gpioval >> i) & 0x01);
		अगर (mxl_fail(ret))
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा PCA9534_I2C_ADDR (0x40 >> 1)
अटल पूर्णांक pca9534_set_gpio(काष्ठा mxl111sf_state *state, पूर्णांक gpio, पूर्णांक val)
अणु
	u8 w[2] = अणु 1, 0 पूर्ण;
	u8 r = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = PCA9534_I2C_ADDR,
		  .flags = 0, .buf = w, .len = 1 पूर्ण,
		अणु .addr = PCA9534_I2C_ADDR,
		  .flags = I2C_M_RD, .buf = &r, .len = 1 पूर्ण,
	पूर्ण;

	mxl_debug("(%d, %d)", gpio, val);

	/* पढ़ो current GPIO levels from flip-flop */
	i2c_transfer(&state->d->i2c_adap, msg, 2);

	/* prepare ग_लिखो buffer with current GPIO levels */
	msg[0].len = 2;
#अगर 0
	w[0] = 1;
#पूर्ण_अगर
	w[1] = r;

	/* clear the desired GPIO */
	w[1] &= ~(1 << gpio);

	/* set the desired GPIO value */
	w[1] |= ((val ? 1 : 0) << gpio);

	/* ग_लिखो new GPIO levels to flip-flop */
	i2c_transfer(&state->d->i2c_adap, &msg[0], 1);

	वापस 0;
पूर्ण

अटल पूर्णांक pca9534_init_port_expander(काष्ठा mxl111sf_state *state)
अणु
	u8 w[2] = अणु 1, 0x07 पूर्ण; /* ग_लिखो protect enabled, संकेत LEDs off */

	काष्ठा i2c_msg msg = अणु
		.addr = PCA9534_I2C_ADDR,
		.flags = 0, .buf = w, .len = 2
	पूर्ण;

	mxl_debug("()");

	i2c_transfer(&state->d->i2c_adap, &msg, 1);

	/* configure all pins as outमाला_दो */
	w[0] = 3;
	w[1] = 0;

	i2c_transfer(&state->d->i2c_adap, &msg, 1);

	वापस 0;
पूर्ण

पूर्णांक mxl111sf_set_gpio(काष्ठा mxl111sf_state *state, पूर्णांक gpio, पूर्णांक val)
अणु
	mxl_debug("(%d, %d)", gpio, val);

	चयन (state->gpio_port_expander) अणु
	शेष:
		mxl_prपूर्णांकk(KERN_ERR,
			   "gpio_port_expander undefined, assuming PCA9534");
		fallthrough;
	हाल mxl111sf_PCA9534:
		वापस pca9534_set_gpio(state, gpio, val);
	हाल mxl111sf_gpio_hw:
		वापस mxl111sf_hw_set_gpio(state, gpio, val);
	पूर्ण
पूर्ण

अटल पूर्णांक mxl111sf_probe_port_expander(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;
	u8 w = 1;
	u8 r = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु .flags = 0,        .buf = &w, .len = 1 पूर्ण,
		अणु .flags = I2C_M_RD, .buf = &r, .len = 1 पूर्ण,
	पूर्ण;

	mxl_debug("()");

	msg[0].addr = 0x70 >> 1;
	msg[1].addr = 0x70 >> 1;

	/* पढ़ो current GPIO levels from flip-flop */
	ret = i2c_transfer(&state->d->i2c_adap, msg, 2);
	अगर (ret == 2) अणु
		state->port_expander_addr = msg[0].addr;
		state->gpio_port_expander = mxl111sf_PCA9534;
		mxl_debug("found port expander at 0x%02x",
			  state->port_expander_addr);
		वापस 0;
	पूर्ण

	msg[0].addr = 0x40 >> 1;
	msg[1].addr = 0x40 >> 1;

	ret = i2c_transfer(&state->d->i2c_adap, msg, 2);
	अगर (ret == 2) अणु
		state->port_expander_addr = msg[0].addr;
		state->gpio_port_expander = mxl111sf_PCA9534;
		mxl_debug("found port expander at 0x%02x",
			  state->port_expander_addr);
		वापस 0;
	पूर्ण
	state->port_expander_addr = 0xff;
	state->gpio_port_expander = mxl111sf_gpio_hw;
	mxl_debug("using hardware gpio");
	वापस 0;
पूर्ण

पूर्णांक mxl111sf_init_port_expander(काष्ठा mxl111sf_state *state)
अणु
	mxl_debug("()");

	अगर (0x00 == state->port_expander_addr)
		mxl111sf_probe_port_expander(state);

	चयन (state->gpio_port_expander) अणु
	शेष:
		mxl_prपूर्णांकk(KERN_ERR,
			   "gpio_port_expander undefined, assuming PCA9534");
		fallthrough;
	हाल mxl111sf_PCA9534:
		वापस pca9534_init_port_expander(state);
	हाल mxl111sf_gpio_hw:
		वापस mxl111sf_hw_gpio_initialize(state);
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------------ */

पूर्णांक mxl111sf_gpio_mode_चयन(काष्ठा mxl111sf_state *state, अचिन्हित पूर्णांक mode)
अणु
/*	GPO:
 *	3 - ATSC/MH#   | 1 = ATSC transport, 0 = MH transport      | शेष 0
 *	4 - ATSC_RST## | 1 = ATSC enable, 0 = ATSC Reset           | शेष 0
 *	5 - ATSC_EN    | 1 = ATSC घातer enable, 0 = ATSC घातer off | शेष 0
 *	6 - MH_RESET#  | 1 = MH enable, 0 = MH Reset               | शेष 0
 *	7 - MH_EN      | 1 = MH घातer enable, 0 = MH घातer off     | शेष 0
 */
	mxl_debug("(%d)", mode);

	चयन (mode) अणु
	हाल MXL111SF_GPIO_MOD_MH:
		mxl111sf_set_gpio(state, 4, 0);
		mxl111sf_set_gpio(state, 5, 0);
		msleep(50);
		mxl111sf_set_gpio(state, 7, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 6, 1);
		msleep(50);

		mxl111sf_set_gpio(state, 3, 0);
		अवरोध;
	हाल MXL111SF_GPIO_MOD_ATSC:
		mxl111sf_set_gpio(state, 6, 0);
		mxl111sf_set_gpio(state, 7, 0);
		msleep(50);
		mxl111sf_set_gpio(state, 5, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 4, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 3, 1);
		अवरोध;
	शेष: /* DVBT / STANDBY */
		mxl111sf_init_port_expander(state);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
