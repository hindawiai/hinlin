<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI/National Semiconductor LP3943 Device
 *
 * Copyright 2013 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#अगर_अघोषित __MFD_LP3943_H__
#घोषणा __MFD_LP3943_H__

#समावेश <linux/gpपन.स>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

/* Registers */
#घोषणा LP3943_REG_GPIO_A		0x00
#घोषणा LP3943_REG_GPIO_B		0x01
#घोषणा LP3943_REG_PRESCALE0		0x02
#घोषणा LP3943_REG_PWM0			0x03
#घोषणा LP3943_REG_PRESCALE1		0x04
#घोषणा LP3943_REG_PWM1			0x05
#घोषणा LP3943_REG_MUX0			0x06
#घोषणा LP3943_REG_MUX1			0x07
#घोषणा LP3943_REG_MUX2			0x08
#घोषणा LP3943_REG_MUX3			0x09

/* Bit description क्रम LP3943_REG_MUX0 ~ 3 */
#घोषणा LP3943_GPIO_IN			0x00
#घोषणा LP3943_GPIO_OUT_HIGH		0x00
#घोषणा LP3943_GPIO_OUT_LOW		0x01
#घोषणा LP3943_DIM_PWM0			0x02
#घोषणा LP3943_DIM_PWM1			0x03

#घोषणा LP3943_NUM_PWMS			2

क्रमागत lp3943_pwm_output अणु
	LP3943_PWM_OUT0,
	LP3943_PWM_OUT1,
	LP3943_PWM_OUT2,
	LP3943_PWM_OUT3,
	LP3943_PWM_OUT4,
	LP3943_PWM_OUT5,
	LP3943_PWM_OUT6,
	LP3943_PWM_OUT7,
	LP3943_PWM_OUT8,
	LP3943_PWM_OUT9,
	LP3943_PWM_OUT10,
	LP3943_PWM_OUT11,
	LP3943_PWM_OUT12,
	LP3943_PWM_OUT13,
	LP3943_PWM_OUT14,
	LP3943_PWM_OUT15,
पूर्ण;

/*
 * काष्ठा lp3943_pwm_map
 * @output: Output pins which are mapped to each PWM channel
 * @num_outमाला_दो: Number of outमाला_दो
 */
काष्ठा lp3943_pwm_map अणु
	क्रमागत lp3943_pwm_output *output;
	पूर्णांक num_outमाला_दो;
पूर्ण;

/*
 * काष्ठा lp3943_platक्रमm_data
 * @pwms: Output channel definitions क्रम PWM channel 0 and 1
 */
काष्ठा lp3943_platक्रमm_data अणु
	काष्ठा lp3943_pwm_map *pwms[LP3943_NUM_PWMS];
पूर्ण;

/*
 * काष्ठा lp3943_reg_cfg
 * @reg: Register address
 * @mask: Register bit mask to be updated
 * @shअगरt: Register bit shअगरt
 */
काष्ठा lp3943_reg_cfg अणु
	u8 reg;
	u8 mask;
	u8 shअगरt;
पूर्ण;

/*
 * काष्ठा lp3943
 * @dev: Parent device poपूर्णांकer
 * @regmap: Used क्रम I2C communication on accessing रेजिस्टरs
 * @pdata: LP3943 platक्रमm specअगरic data
 * @mux_cfg: Register configuration क्रम pin MUX
 * @pin_used: Bit mask क्रम output pin used.
 *	      This biपंचांगask is used क्रम pin assignment management.
 *	      1 = pin used, 0 = available.
 *	      Only LSB 16 bits are used, but it is अचिन्हित दीर्घ type
 *	      क्रम atomic bitwise operations.
 */
काष्ठा lp3943 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा lp3943_platक्रमm_data *pdata;
	स्थिर काष्ठा lp3943_reg_cfg *mux_cfg;
	अचिन्हित दीर्घ pin_used;
पूर्ण;

पूर्णांक lp3943_पढ़ो_byte(काष्ठा lp3943 *lp3943, u8 reg, u8 *पढ़ो);
पूर्णांक lp3943_ग_लिखो_byte(काष्ठा lp3943 *lp3943, u8 reg, u8 data);
पूर्णांक lp3943_update_bits(काष्ठा lp3943 *lp3943, u8 reg, u8 mask, u8 data);
#पूर्ण_अगर
