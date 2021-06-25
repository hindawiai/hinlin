<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	LED driver क्रम TI lp3952 controller
 *
 *	Copyright (C) 2016, DAQRI, LLC.
 *	Author: Tony Makkiel <tony.makkiel@daqri.com>
 */

#अगर_अघोषित LEDS_LP3952_H_
#घोषणा LEDS_LP3952_H_

#घोषणा LP3952_NAME                         "lp3952"
#घोषणा LP3952_CMD_REG_COUNT                8
#घोषणा LP3952_BRIGHT_MAX                   4
#घोषणा LP3952_LABEL_MAX_LEN                15

#घोषणा LP3952_REG_LED_CTRL                 0x00
#घोषणा LP3952_REG_R1_BLNK_TIME_CTRL        0x01
#घोषणा LP3952_REG_R1_BLNK_CYCLE_CTRL       0x02
#घोषणा LP3952_REG_G1_BLNK_TIME_CTRL        0x03
#घोषणा LP3952_REG_G1_BLNK_CYCLE_CTRL       0x04
#घोषणा LP3952_REG_B1_BLNK_TIME_CTRL        0x05
#घोषणा LP3952_REG_B1_BLNK_CYCLE_CTRL       0x06
#घोषणा LP3952_REG_ENABLES                  0x0B
#घोषणा LP3952_REG_PAT_GEN_CTRL             0x11
#घोषणा LP3952_REG_RGB1_MAX_I_CTRL          0x12
#घोषणा LP3952_REG_RGB2_MAX_I_CTRL          0x13
#घोषणा LP3952_REG_CMD_0                    0x50
#घोषणा LP3952_REG_RESET                    0x60
#घोषणा REG_MAX                             LP3952_REG_RESET

#घोषणा LP3952_PATRN_LOOP                   BIT(1)
#घोषणा LP3952_PATRN_GEN_EN                 BIT(2)
#घोषणा LP3952_INT_B00ST_LDR                BIT(2)
#घोषणा LP3952_ACTIVE_MODE                  BIT(6)
#घोषणा LP3952_LED_MASK_ALL                 0x3f

/* Transition Time in ms */
क्रमागत lp3952_tt अणु
	TT0,
	TT55,
	TT110,
	TT221,
	TT422,
	TT885,
	TT1770,
	TT3539
पूर्ण;

/* Command Execution Time in ms */
क्रमागत lp3952_cet अणु
	CET197,
	CET393,
	CET590,
	CET786,
	CET1180,
	CET1376,
	CET1573,
	CET1769,
	CET1966,
	CET2163,
	CET2359,
	CET2556,
	CET2763,
	CET2949,
	CET3146
पूर्ण;

/* Max Current in % */
क्रमागत lp3952_colour_I_log_0 अणु
	I0,
	I7,
	I14,
	I21,
	I32,
	I46,
	I71,
	I100
पूर्ण;

क्रमागत lp3952_leds अणु
	LP3952_BLUE_2,
	LP3952_GREEN_2,
	LP3952_RED_2,
	LP3952_BLUE_1,
	LP3952_GREEN_1,
	LP3952_RED_1,
	LP3952_LED_ALL
पूर्ण;

काष्ठा lp3952_ctrl_hdl अणु
	काष्ठा led_classdev cdev;
	अक्षर name[LP3952_LABEL_MAX_LEN];
	क्रमागत lp3952_leds channel;
	व्योम *priv;
पूर्ण;

काष्ठा ptrn_gen_cmd अणु
	जोड़ अणु
		काष्ठा अणु
			u16 tt:3;
			u16 b:3;
			u16 cet:4;
			u16 g:3;
			u16 r:3;
		पूर्ण;
		काष्ठा अणु
			u8 lsb;
			u8 msb;
		पूर्ण bytes;
	पूर्ण;
पूर्ण __packed;

काष्ठा lp3952_led_array अणु
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *client;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा lp3952_ctrl_hdl leds[LP3952_LED_ALL];
पूर्ण;

#पूर्ण_अगर /* LEDS_LP3952_H_ */
