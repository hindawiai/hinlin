<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * IIO features supported by the driver:
 *
 * Read-only raw channels:
 *   - illuminance_clear [lux]
 *   - illuminance_ir
 *   - proximity
 *
 * Triggered buffer:
 *   - illuminance_clear
 *   - illuminance_ir
 *   - proximity
 *
 * Events:
 *   - illuminance_clear (rising and falling)
 *   - proximity (rising and falling)
 *     - both falling and rising thresholds क्रम the proximity events
 *       must be set to the values greater than 0.
 *
 * The driver supports triggered buffers क्रम all the three
 * channels as well as high and low threshold events क्रम the
 * illuminance_clear and proxmimity channels. Triggers
 * can be enabled simultaneously with both illuminance_clear
 * events. Proximity events cannot be enabled simultaneously
 * with any triggers or illuminance events. Enabling/disabling
 * one of the proximity events स्वतःmatically enables/disables
 * the other one.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा GP2A_I2C_NAME "gp2ap020a00f"

/* Registers */
#घोषणा GP2AP020A00F_OP_REG	0x00 /* Basic operations */
#घोषणा GP2AP020A00F_ALS_REG	0x01 /* ALS related settings */
#घोषणा GP2AP020A00F_PS_REG	0x02 /* PS related settings */
#घोषणा GP2AP020A00F_LED_REG	0x03 /* LED reg */
#घोषणा GP2AP020A00F_TL_L_REG	0x04 /* ALS: Threshold low LSB */
#घोषणा GP2AP020A00F_TL_H_REG	0x05 /* ALS: Threshold low MSB */
#घोषणा GP2AP020A00F_TH_L_REG	0x06 /* ALS: Threshold high LSB */
#घोषणा GP2AP020A00F_TH_H_REG	0x07 /* ALS: Threshold high MSB */
#घोषणा GP2AP020A00F_PL_L_REG	0x08 /* PS: Threshold low LSB */
#घोषणा GP2AP020A00F_PL_H_REG	0x09 /* PS: Threshold low MSB */
#घोषणा GP2AP020A00F_PH_L_REG	0x0a /* PS: Threshold high LSB */
#घोषणा GP2AP020A00F_PH_H_REG	0x0b /* PS: Threshold high MSB */
#घोषणा GP2AP020A00F_D0_L_REG	0x0c /* ALS result: Clear/Illuminance LSB */
#घोषणा GP2AP020A00F_D0_H_REG	0x0d /* ALS result: Clear/Illuminance MSB */
#घोषणा GP2AP020A00F_D1_L_REG	0x0e /* ALS result: IR LSB */
#घोषणा GP2AP020A00F_D1_H_REG	0x0f /* ALS result: IR LSB */
#घोषणा GP2AP020A00F_D2_L_REG	0x10 /* PS result LSB */
#घोषणा GP2AP020A00F_D2_H_REG	0x11 /* PS result MSB */
#घोषणा GP2AP020A00F_NUM_REGS	0x12 /* Number of रेजिस्टरs */

/* OP_REG bits */
#घोषणा GP2AP020A00F_OP3_MASK		0x80 /* Software shutकरोwn */
#घोषणा GP2AP020A00F_OP3_SHUTDOWN	0x00
#घोषणा GP2AP020A00F_OP3_OPERATION	0x80
#घोषणा GP2AP020A00F_OP2_MASK		0x40 /* Auto shutकरोwn/Continuous mode */
#घोषणा GP2AP020A00F_OP2_AUTO_SHUTDOWN	0x00
#घोषणा GP2AP020A00F_OP2_CONT_OPERATION	0x40
#घोषणा GP2AP020A00F_OP_MASK		0x30 /* Operating mode selection  */
#घोषणा GP2AP020A00F_OP_ALS_AND_PS	0x00
#घोषणा GP2AP020A00F_OP_ALS		0x10
#घोषणा GP2AP020A00F_OP_PS		0x20
#घोषणा GP2AP020A00F_OP_DEBUG		0x30
#घोषणा GP2AP020A00F_PROX_MASK		0x08 /* PS: detection/non-detection */
#घोषणा GP2AP020A00F_PROX_NON_DETECT	0x00
#घोषणा GP2AP020A00F_PROX_DETECT	0x08
#घोषणा GP2AP020A00F_FLAG_P		0x04 /* PS: पूर्णांकerrupt result  */
#घोषणा GP2AP020A00F_FLAG_A		0x02 /* ALS: पूर्णांकerrupt result  */
#घोषणा GP2AP020A00F_TYPE_MASK		0x01 /* Output data type selection */
#घोषणा GP2AP020A00F_TYPE_MANUAL_CALC	0x00
#घोषणा GP2AP020A00F_TYPE_AUTO_CALC	0x01

/* ALS_REG bits */
#घोषणा GP2AP020A00F_PRST_MASK		0xc0 /* Number of measurement cycles */
#घोषणा GP2AP020A00F_PRST_ONCE		0x00
#घोषणा GP2AP020A00F_PRST_4_CYCLES	0x40
#घोषणा GP2AP020A00F_PRST_8_CYCLES	0x80
#घोषणा GP2AP020A00F_PRST_16_CYCLES	0xc0
#घोषणा GP2AP020A00F_RES_A_MASK		0x38 /* ALS: Resolution */
#घोषणा GP2AP020A00F_RES_A_800ms	0x00
#घोषणा GP2AP020A00F_RES_A_400ms	0x08
#घोषणा GP2AP020A00F_RES_A_200ms	0x10
#घोषणा GP2AP020A00F_RES_A_100ms	0x18
#घोषणा GP2AP020A00F_RES_A_25ms		0x20
#घोषणा GP2AP020A00F_RES_A_6_25ms	0x28
#घोषणा GP2AP020A00F_RES_A_1_56ms	0x30
#घोषणा GP2AP020A00F_RES_A_0_39ms	0x38
#घोषणा GP2AP020A00F_RANGE_A_MASK	0x07 /* ALS: Max measurable range */
#घोषणा GP2AP020A00F_RANGE_A_x1		0x00
#घोषणा GP2AP020A00F_RANGE_A_x2		0x01
#घोषणा GP2AP020A00F_RANGE_A_x4		0x02
#घोषणा GP2AP020A00F_RANGE_A_x8		0x03
#घोषणा GP2AP020A00F_RANGE_A_x16	0x04
#घोषणा GP2AP020A00F_RANGE_A_x32	0x05
#घोषणा GP2AP020A00F_RANGE_A_x64	0x06
#घोषणा GP2AP020A00F_RANGE_A_x128	0x07

/* PS_REG bits */
#घोषणा GP2AP020A00F_ALC_MASK		0x80 /* Auto light cancel */
#घोषणा GP2AP020A00F_ALC_ON		0x80
#घोषणा GP2AP020A00F_ALC_OFF		0x00
#घोषणा GP2AP020A00F_INTTYPE_MASK	0x40 /* Interrupt type setting */
#घोषणा GP2AP020A00F_INTTYPE_LEVEL	0x00
#घोषणा GP2AP020A00F_INTTYPE_PULSE	0x40
#घोषणा GP2AP020A00F_RES_P_MASK		0x38 /* PS: Resolution */
#घोषणा GP2AP020A00F_RES_P_800ms_x2	0x00
#घोषणा GP2AP020A00F_RES_P_400ms_x2	0x08
#घोषणा GP2AP020A00F_RES_P_200ms_x2	0x10
#घोषणा GP2AP020A00F_RES_P_100ms_x2	0x18
#घोषणा GP2AP020A00F_RES_P_25ms_x2	0x20
#घोषणा GP2AP020A00F_RES_P_6_25ms_x2	0x28
#घोषणा GP2AP020A00F_RES_P_1_56ms_x2	0x30
#घोषणा GP2AP020A00F_RES_P_0_39ms_x2	0x38
#घोषणा GP2AP020A00F_RANGE_P_MASK	0x07 /* PS: Max measurable range */
#घोषणा GP2AP020A00F_RANGE_P_x1		0x00
#घोषणा GP2AP020A00F_RANGE_P_x2		0x01
#घोषणा GP2AP020A00F_RANGE_P_x4		0x02
#घोषणा GP2AP020A00F_RANGE_P_x8		0x03
#घोषणा GP2AP020A00F_RANGE_P_x16	0x04
#घोषणा GP2AP020A00F_RANGE_P_x32	0x05
#घोषणा GP2AP020A00F_RANGE_P_x64	0x06
#घोषणा GP2AP020A00F_RANGE_P_x128	0x07

/* LED reg bits */
#घोषणा GP2AP020A00F_INTVAL_MASK	0xc0 /* Intermittent operating */
#घोषणा GP2AP020A00F_INTVAL_0		0x00
#घोषणा GP2AP020A00F_INTVAL_4		0x40
#घोषणा GP2AP020A00F_INTVAL_8		0x80
#घोषणा GP2AP020A00F_INTVAL_16		0xc0
#घोषणा GP2AP020A00F_IS_MASK		0x30 /* ILED drive peak current */
#घोषणा GP2AP020A00F_IS_13_8mA		0x00
#घोषणा GP2AP020A00F_IS_27_5mA		0x10
#घोषणा GP2AP020A00F_IS_55mA		0x20
#घोषणा GP2AP020A00F_IS_110mA		0x30
#घोषणा GP2AP020A00F_PIN_MASK		0x0c /* INT terminal setting */
#घोषणा GP2AP020A00F_PIN_ALS_OR_PS	0x00
#घोषणा GP2AP020A00F_PIN_ALS		0x04
#घोषणा GP2AP020A00F_PIN_PS		0x08
#घोषणा GP2AP020A00F_PIN_PS_DETECT	0x0c
#घोषणा GP2AP020A00F_FREQ_MASK		0x02 /* LED modulation frequency */
#घोषणा GP2AP020A00F_FREQ_327_5kHz	0x00
#घोषणा GP2AP020A00F_FREQ_81_8kHz	0x02
#घोषणा GP2AP020A00F_RST		0x01 /* Software reset */

#घोषणा GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR	0
#घोषणा GP2AP020A00F_SCAN_MODE_LIGHT_IR		1
#घोषणा GP2AP020A00F_SCAN_MODE_PROXIMITY	2
#घोषणा GP2AP020A00F_CHAN_TIMESTAMP		3

#घोषणा GP2AP020A00F_DATA_READY_TIMEOUT		msecs_to_jअगरfies(1000)
#घोषणा GP2AP020A00F_DATA_REG(chan)		(GP2AP020A00F_D0_L_REG + \
							(chan) * 2)
#घोषणा GP2AP020A00F_THRESH_REG(th_val_id)	(GP2AP020A00F_TL_L_REG + \
							(th_val_id) * 2)
#घोषणा GP2AP020A00F_THRESH_VAL_ID(reg_addr)	((reg_addr - 4) / 2)

#घोषणा GP2AP020A00F_SUBTRACT_MODE	0
#घोषणा GP2AP020A00F_ADD_MODE		1

#घोषणा GP2AP020A00F_MAX_CHANNELS	3

क्रमागत gp2ap020a00f_opmode अणु
	GP2AP020A00F_OPMODE_READ_RAW_CLEAR,
	GP2AP020A00F_OPMODE_READ_RAW_IR,
	GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY,
	GP2AP020A00F_OPMODE_ALS,
	GP2AP020A00F_OPMODE_PS,
	GP2AP020A00F_OPMODE_ALS_AND_PS,
	GP2AP020A00F_OPMODE_PROX_DETECT,
	GP2AP020A00F_OPMODE_SHUTDOWN,
	GP2AP020A00F_NUM_OPMODES,
पूर्ण;

क्रमागत gp2ap020a00f_cmd अणु
	GP2AP020A00F_CMD_READ_RAW_CLEAR,
	GP2AP020A00F_CMD_READ_RAW_IR,
	GP2AP020A00F_CMD_READ_RAW_PROXIMITY,
	GP2AP020A00F_CMD_TRIGGER_CLEAR_EN,
	GP2AP020A00F_CMD_TRIGGER_CLEAR_DIS,
	GP2AP020A00F_CMD_TRIGGER_IR_EN,
	GP2AP020A00F_CMD_TRIGGER_IR_DIS,
	GP2AP020A00F_CMD_TRIGGER_PROX_EN,
	GP2AP020A00F_CMD_TRIGGER_PROX_DIS,
	GP2AP020A00F_CMD_ALS_HIGH_EV_EN,
	GP2AP020A00F_CMD_ALS_HIGH_EV_DIS,
	GP2AP020A00F_CMD_ALS_LOW_EV_EN,
	GP2AP020A00F_CMD_ALS_LOW_EV_DIS,
	GP2AP020A00F_CMD_PROX_HIGH_EV_EN,
	GP2AP020A00F_CMD_PROX_HIGH_EV_DIS,
	GP2AP020A00F_CMD_PROX_LOW_EV_EN,
	GP2AP020A00F_CMD_PROX_LOW_EV_DIS,
पूर्ण;

क्रमागत gp2ap020a00f_flags अणु
	GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER,
	GP2AP020A00F_FLAG_ALS_IR_TRIGGER,
	GP2AP020A00F_FLAG_PROX_TRIGGER,
	GP2AP020A00F_FLAG_PROX_RISING_EV,
	GP2AP020A00F_FLAG_PROX_FALLING_EV,
	GP2AP020A00F_FLAG_ALS_RISING_EV,
	GP2AP020A00F_FLAG_ALS_FALLING_EV,
	GP2AP020A00F_FLAG_LUX_MODE_HI,
	GP2AP020A00F_FLAG_DATA_READY,
पूर्ण;

क्रमागत gp2ap020a00f_thresh_val_id अणु
	GP2AP020A00F_THRESH_TL,
	GP2AP020A00F_THRESH_TH,
	GP2AP020A00F_THRESH_PL,
	GP2AP020A00F_THRESH_PH,
पूर्ण;

काष्ठा gp2ap020a00f_data अणु
	स्थिर काष्ठा gp2ap020a00f_platक्रमm_data *pdata;
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	अक्षर *buffer;
	काष्ठा regulator *vled_reg;
	अचिन्हित दीर्घ flags;
	क्रमागत gp2ap020a00f_opmode cur_opmode;
	काष्ठा iio_trigger *trig;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक thresh_val[4];
	u8 debug_reg_addr;
	काष्ठा irq_work work;
	रुको_queue_head_t data_पढ़ोy_queue;
पूर्ण;

अटल स्थिर u8 gp2ap020a00f_reg_init_tab[] = अणु
	[GP2AP020A00F_OP_REG] = GP2AP020A00F_OP3_SHUTDOWN,
	[GP2AP020A00F_ALS_REG] = GP2AP020A00F_RES_A_25ms |
				 GP2AP020A00F_RANGE_A_x8,
	[GP2AP020A00F_PS_REG] = GP2AP020A00F_ALC_ON |
				GP2AP020A00F_RES_P_1_56ms_x2 |
				GP2AP020A00F_RANGE_P_x4,
	[GP2AP020A00F_LED_REG] = GP2AP020A00F_INTVAL_0 |
				 GP2AP020A00F_IS_110mA |
				 GP2AP020A00F_FREQ_327_5kHz,
	[GP2AP020A00F_TL_L_REG] = 0,
	[GP2AP020A00F_TL_H_REG] = 0,
	[GP2AP020A00F_TH_L_REG] = 0,
	[GP2AP020A00F_TH_H_REG] = 0,
	[GP2AP020A00F_PL_L_REG] = 0,
	[GP2AP020A00F_PL_H_REG] = 0,
	[GP2AP020A00F_PH_L_REG] = 0,
	[GP2AP020A00F_PH_H_REG] = 0,
पूर्ण;

अटल bool gp2ap020a00f_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल GP2AP020A00F_OP_REG:
	हाल GP2AP020A00F_D0_L_REG:
	हाल GP2AP020A00F_D0_H_REG:
	हाल GP2AP020A00F_D1_L_REG:
	हाल GP2AP020A00F_D1_H_REG:
	हाल GP2AP020A00F_D2_L_REG:
	हाल GP2AP020A00F_D2_H_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config gp2ap020a00f_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = GP2AP020A00F_D2_H_REG,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = gp2ap020a00f_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा gp2ap020a00f_mutable_config_regs अणु
	u8 op_reg;
	u8 als_reg;
	u8 ps_reg;
	u8 led_reg;
पूर्ण opmode_regs_settings[GP2AP020A00F_NUM_OPMODES] = अणु
	[GP2AP020A00F_OPMODE_READ_RAW_CLEAR] = अणु
		GP2AP020A00F_OP_ALS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_AUTO_CALC,
		GP2AP020A00F_PRST_ONCE,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_ALS
	पूर्ण,
	[GP2AP020A00F_OPMODE_READ_RAW_IR] = अणु
		GP2AP020A00F_OP_ALS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_MANUAL_CALC,
		GP2AP020A00F_PRST_ONCE,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_ALS
	पूर्ण,
	[GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY] = अणु
		GP2AP020A00F_OP_PS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_MANUAL_CALC,
		GP2AP020A00F_PRST_ONCE,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_PS
	पूर्ण,
	[GP2AP020A00F_OPMODE_PROX_DETECT] = अणु
		GP2AP020A00F_OP_PS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_MANUAL_CALC,
		GP2AP020A00F_PRST_4_CYCLES,
		GP2AP020A00F_INTTYPE_PULSE,
		GP2AP020A00F_PIN_PS_DETECT
	पूर्ण,
	[GP2AP020A00F_OPMODE_ALS] = अणु
		GP2AP020A00F_OP_ALS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_AUTO_CALC,
		GP2AP020A00F_PRST_ONCE,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_ALS
	पूर्ण,
	[GP2AP020A00F_OPMODE_PS] = अणु
		GP2AP020A00F_OP_PS | GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_MANUAL_CALC,
		GP2AP020A00F_PRST_4_CYCLES,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_PS
	पूर्ण,
	[GP2AP020A00F_OPMODE_ALS_AND_PS] = अणु
		GP2AP020A00F_OP_ALS_AND_PS
		| GP2AP020A00F_OP2_CONT_OPERATION
		| GP2AP020A00F_OP3_OPERATION
		| GP2AP020A00F_TYPE_AUTO_CALC,
		GP2AP020A00F_PRST_4_CYCLES,
		GP2AP020A00F_INTTYPE_LEVEL,
		GP2AP020A00F_PIN_ALS_OR_PS
	पूर्ण,
	[GP2AP020A00F_OPMODE_SHUTDOWN] = अणु GP2AP020A00F_OP3_SHUTDOWN, पूर्ण,
पूर्ण;

अटल पूर्णांक gp2ap020a00f_set_operation_mode(काष्ठा gp2ap020a00f_data *data,
					क्रमागत gp2ap020a00f_opmode op)
अणु
	अचिन्हित पूर्णांक op_reg_val;
	पूर्णांक err;

	अगर (op != GP2AP020A00F_OPMODE_SHUTDOWN) अणु
		err = regmap_पढ़ो(data->regmap, GP2AP020A00F_OP_REG,
					&op_reg_val);
		अगर (err < 0)
			वापस err;
		/*
		 * Shutकरोwn the device अगर the operation being executed entails
		 * mode transition.
		 */
		अगर ((opmode_regs_settings[op].op_reg & GP2AP020A00F_OP_MASK) !=
		    (op_reg_val & GP2AP020A00F_OP_MASK)) अणु
			/* set shutकरोwn mode */
			err = regmap_update_bits(data->regmap,
				GP2AP020A00F_OP_REG, GP2AP020A00F_OP3_MASK,
				GP2AP020A00F_OP3_SHUTDOWN);
			अगर (err < 0)
				वापस err;
		पूर्ण

		err = regmap_update_bits(data->regmap, GP2AP020A00F_ALS_REG,
			GP2AP020A00F_PRST_MASK, opmode_regs_settings[op]
								.als_reg);
		अगर (err < 0)
			वापस err;

		err = regmap_update_bits(data->regmap, GP2AP020A00F_PS_REG,
			GP2AP020A00F_INTTYPE_MASK, opmode_regs_settings[op]
								.ps_reg);
		अगर (err < 0)
			वापस err;

		err = regmap_update_bits(data->regmap, GP2AP020A00F_LED_REG,
			GP2AP020A00F_PIN_MASK, opmode_regs_settings[op]
								.led_reg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Set OP_REG and apply operation mode (घातer on / off) */
	err = regmap_update_bits(data->regmap,
				 GP2AP020A00F_OP_REG,
				 GP2AP020A00F_OP_MASK | GP2AP020A00F_OP2_MASK |
				 GP2AP020A00F_OP3_MASK | GP2AP020A00F_TYPE_MASK,
				 opmode_regs_settings[op].op_reg);
	अगर (err < 0)
		वापस err;

	data->cur_opmode = op;

	वापस 0;
पूर्ण

अटल bool gp2ap020a00f_als_enabled(काष्ठा gp2ap020a00f_data *data)
अणु
	वापस test_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &data->flags) ||
	       test_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &data->flags) ||
	       test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags) ||
	       test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags);
पूर्ण

अटल bool gp2ap020a00f_prox_detect_enabled(काष्ठा gp2ap020a00f_data *data)
अणु
	वापस test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags) ||
	       test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags);
पूर्ण

अटल पूर्णांक gp2ap020a00f_ग_लिखो_event_threshold(काष्ठा gp2ap020a00f_data *data,
				क्रमागत gp2ap020a00f_thresh_val_id th_val_id,
				bool enable)
अणु
	__le16 thresh_buf = 0;
	अचिन्हित पूर्णांक thresh_reg_val;

	अगर (!enable)
		thresh_reg_val = 0;
	अन्यथा अगर (test_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags) &&
		 th_val_id != GP2AP020A00F_THRESH_PL &&
		 th_val_id != GP2AP020A00F_THRESH_PH)
		/*
		 * For the high lux mode ALS threshold has to be scaled करोwn
		 * to allow क्रम proper comparison with the output value.
		 */
		thresh_reg_val = data->thresh_val[th_val_id] / 16;
	अन्यथा
		thresh_reg_val = data->thresh_val[th_val_id] > 16000 ?
					16000 :
					data->thresh_val[th_val_id];

	thresh_buf = cpu_to_le16(thresh_reg_val);

	वापस regmap_bulk_ग_लिखो(data->regmap,
				 GP2AP020A00F_THRESH_REG(th_val_id),
				 (u8 *)&thresh_buf, 2);
पूर्ण

अटल पूर्णांक gp2ap020a00f_alter_opmode(काष्ठा gp2ap020a00f_data *data,
			क्रमागत gp2ap020a00f_opmode dअगरf_mode, पूर्णांक add_sub)
अणु
	क्रमागत gp2ap020a00f_opmode new_mode;

	अगर (dअगरf_mode != GP2AP020A00F_OPMODE_ALS &&
	    dअगरf_mode != GP2AP020A00F_OPMODE_PS)
		वापस -EINVAL;

	अगर (add_sub == GP2AP020A00F_ADD_MODE) अणु
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_SHUTDOWN)
			new_mode =  dअगरf_mode;
		अन्यथा
			new_mode = GP2AP020A00F_OPMODE_ALS_AND_PS;
	पूर्ण अन्यथा अणु
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_ALS_AND_PS)
			new_mode = (dअगरf_mode == GP2AP020A00F_OPMODE_ALS) ?
					GP2AP020A00F_OPMODE_PS :
					GP2AP020A00F_OPMODE_ALS;
		अन्यथा
			new_mode = GP2AP020A00F_OPMODE_SHUTDOWN;
	पूर्ण

	वापस gp2ap020a00f_set_operation_mode(data, new_mode);
पूर्ण

अटल पूर्णांक gp2ap020a00f_exec_cmd(काष्ठा gp2ap020a00f_data *data,
					क्रमागत gp2ap020a00f_cmd cmd)
अणु
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल GP2AP020A00F_CMD_READ_RAW_CLEAR:
		अगर (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			वापस -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_CLEAR);
		अवरोध;
	हाल GP2AP020A00F_CMD_READ_RAW_IR:
		अगर (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			वापस -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_IR);
		अवरोध;
	हाल GP2AP020A00F_CMD_READ_RAW_PROXIMITY:
		अगर (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			वापस -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_CLEAR_EN:
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_als_enabled(data))
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &data->flags);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_CLEAR_DIS:
		clear_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &data->flags);
		अगर (gp2ap020a00f_als_enabled(data))
			अवरोध;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_IR_EN:
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_als_enabled(data))
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &data->flags);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_IR_DIS:
		clear_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &data->flags);
		अगर (gp2ap020a00f_als_enabled(data))
			अवरोध;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_PROX_EN:
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			वापस -EBUSY;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_PS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &data->flags);
		अवरोध;
	हाल GP2AP020A00F_CMD_TRIGGER_PROX_DIS:
		clear_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &data->flags);
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_PS,
						GP2AP020A00F_SUBTRACT_MODE);
		अवरोध;
	हाल GP2AP020A00F_CMD_ALS_HIGH_EV_EN:
		अगर (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags))
			वापस 0;
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_als_enabled(data)) अणु
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
			अगर (err < 0)
				वापस err;
		पूर्ण
		set_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags);
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TH, true);
		अवरोध;
	हाल GP2AP020A00F_CMD_ALS_HIGH_EV_DIS:
		अगर (!test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags))
			वापस 0;
		clear_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags);
		अगर (!gp2ap020a00f_als_enabled(data)) अणु
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
			अगर (err < 0)
				वापस err;
		पूर्ण
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TH, false);
		अवरोध;
	हाल GP2AP020A00F_CMD_ALS_LOW_EV_EN:
		अगर (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags))
			वापस 0;
		अगर (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_als_enabled(data)) अणु
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
			अगर (err < 0)
				वापस err;
		पूर्ण
		set_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags);
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TL, true);
		अवरोध;
	हाल GP2AP020A00F_CMD_ALS_LOW_EV_DIS:
		अगर (!test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags))
			वापस 0;
		clear_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags);
		अगर (!gp2ap020a00f_als_enabled(data)) अणु
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
			अगर (err < 0)
				वापस err;
		पूर्ण
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TL, false);
		अवरोध;
	हाल GP2AP020A00F_CMD_PROX_HIGH_EV_EN:
		अगर (test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags))
			वापस 0;
		अगर (gp2ap020a00f_als_enabled(data) ||
		    data->cur_opmode == GP2AP020A00F_OPMODE_PS)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_prox_detect_enabled(data)) अणु
			err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_PROX_DETECT);
			अगर (err < 0)
				वापस err;
		पूर्ण
		set_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags);
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_PH, true);
		अवरोध;
	हाल GP2AP020A00F_CMD_PROX_HIGH_EV_DIS:
		अगर (!test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags))
			वापस 0;
		clear_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags);
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
		अगर (err < 0)
			वापस err;
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_PH, false);
		अवरोध;
	हाल GP2AP020A00F_CMD_PROX_LOW_EV_EN:
		अगर (test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags))
			वापस 0;
		अगर (gp2ap020a00f_als_enabled(data) ||
		    data->cur_opmode == GP2AP020A00F_OPMODE_PS)
			वापस -EBUSY;
		अगर (!gp2ap020a00f_prox_detect_enabled(data)) अणु
			err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_PROX_DETECT);
			अगर (err < 0)
				वापस err;
		पूर्ण
		set_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags);
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_PL, true);
		अवरोध;
	हाल GP2AP020A00F_CMD_PROX_LOW_EV_DIS:
		अगर (!test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags))
			वापस 0;
		clear_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags);
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
		अगर (err < 0)
			वापस err;
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_PL, false);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक रुको_conversion_complete_irq(काष्ठा gp2ap020a00f_data *data)
अणु
	पूर्णांक ret;

	ret = रुको_event_समयout(data->data_पढ़ोy_queue,
				 test_bit(GP2AP020A00F_FLAG_DATA_READY,
					  &data->flags),
				 GP2AP020A00F_DATA_READY_TIMEOUT);
	clear_bit(GP2AP020A00F_FLAG_DATA_READY, &data->flags);

	वापस ret > 0 ? 0 : -ETIME;
पूर्ण

अटल पूर्णांक gp2ap020a00f_पढ़ो_output(काष्ठा gp2ap020a00f_data *data,
					अचिन्हित पूर्णांक output_reg, पूर्णांक *val)
अणु
	u8 reg_buf[2];
	पूर्णांक err;

	err = रुको_conversion_complete_irq(data);
	अगर (err < 0)
		dev_dbg(&data->client->dev, "data ready timeout\n");

	err = regmap_bulk_पढ़ो(data->regmap, output_reg, reg_buf, 2);
	अगर (err < 0)
		वापस err;

	*val = le16_to_cpup((__le16 *)reg_buf);

	वापस err;
पूर्ण

अटल bool gp2ap020a00f_adjust_lux_mode(काष्ठा gp2ap020a00f_data *data,
				 पूर्णांक output_val)
अणु
	u8 new_range = 0xff;
	पूर्णांक err;

	अगर (!test_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags)) अणु
		अगर (output_val > 16000) अणु
			set_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags);
			new_range = GP2AP020A00F_RANGE_A_x128;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (output_val < 1000) अणु
			clear_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags);
			new_range = GP2AP020A00F_RANGE_A_x8;
		पूर्ण
	पूर्ण

	अगर (new_range != 0xff) अणु
		/* Clear als threshold रेजिस्टरs to aव्योम spurious
		 * events caused by lux mode transition.
		 */
		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TH, false);
		अगर (err < 0) अणु
			dev_err(&data->client->dev,
				"Clearing als threshold register failed.\n");
			वापस false;
		पूर्ण

		err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TL, false);
		अगर (err < 0) अणु
			dev_err(&data->client->dev,
				"Clearing als threshold register failed.\n");
			वापस false;
		पूर्ण

		/* Change lux mode */
		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_OP_REG,
			GP2AP020A00F_OP3_MASK,
			GP2AP020A00F_OP3_SHUTDOWN);

		अगर (err < 0) अणु
			dev_err(&data->client->dev,
				"Shutting down the device failed.\n");
			वापस false;
		पूर्ण

		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_ALS_REG,
			GP2AP020A00F_RANGE_A_MASK,
			new_range);

		अगर (err < 0) अणु
			dev_err(&data->client->dev,
				"Adjusting device lux mode failed.\n");
			वापस false;
		पूर्ण

		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_OP_REG,
			GP2AP020A00F_OP3_MASK,
			GP2AP020A00F_OP3_OPERATION);

		अगर (err < 0) अणु
			dev_err(&data->client->dev,
				"Powering up the device failed.\n");
			वापस false;
		पूर्ण

		/* Adjust als threshold रेजिस्टर values to the new lux mode */
		अगर (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags)) अणु
			err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TH, true);
			अगर (err < 0) अणु
				dev_err(&data->client->dev,
				"Adjusting als threshold value failed.\n");
				वापस false;
			पूर्ण
		पूर्ण

		अगर (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags)) अणु
			err =  gp2ap020a00f_ग_लिखो_event_threshold(data,
					GP2AP020A00F_THRESH_TL, true);
			अगर (err < 0) अणु
				dev_err(&data->client->dev,
				"Adjusting als threshold value failed.\n");
				वापस false;
			पूर्ण
		पूर्ण

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम gp2ap020a00f_output_to_lux(काष्ठा gp2ap020a00f_data *data,
						पूर्णांक *output_val)
अणु
	अगर (test_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags))
		*output_val *= 16;
पूर्ण

अटल व्योम gp2ap020a00f_iio_trigger_work(काष्ठा irq_work *work)
अणु
	काष्ठा gp2ap020a00f_data *data =
		container_of(work, काष्ठा gp2ap020a00f_data, work);

	iio_trigger_poll(data->trig);
पूर्ण

अटल irqवापस_t gp2ap020a00f_prox_sensing_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा gp2ap020a00f_data *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक op_reg_val;
	पूर्णांक ret;

	/* Read पूर्णांकerrupt flags */
	ret = regmap_पढ़ो(priv->regmap, GP2AP020A00F_OP_REG, &op_reg_val);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	अगर (gp2ap020a00f_prox_detect_enabled(priv)) अणु
		अगर (op_reg_val & GP2AP020A00F_PROX_DETECT) अणु
			iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(
				    IIO_PROXIMITY,
				    GP2AP020A00F_SCAN_MODE_PROXIMITY,
				    IIO_EV_TYPE_ROC,
				    IIO_EV_सूची_RISING),
			       iio_get_समय_ns(indio_dev));
		पूर्ण अन्यथा अणु
			iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(
				    IIO_PROXIMITY,
				    GP2AP020A00F_SCAN_MODE_PROXIMITY,
				    IIO_EV_TYPE_ROC,
				    IIO_EV_सूची_FALLING),
			       iio_get_समय_ns(indio_dev));
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gp2ap020a00f_thresh_event_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा gp2ap020a00f_data *priv = iio_priv(indio_dev);
	u8 op_reg_flags, d0_reg_buf[2];
	अचिन्हित पूर्णांक output_val, op_reg_val;
	पूर्णांक thresh_val_id, ret;

	/* Read पूर्णांकerrupt flags */
	ret = regmap_पढ़ो(priv->regmap, GP2AP020A00F_OP_REG,
							&op_reg_val);
	अगर (ret < 0)
		जाओ करोne;

	op_reg_flags = op_reg_val & (GP2AP020A00F_FLAG_A | GP2AP020A00F_FLAG_P
					| GP2AP020A00F_PROX_DETECT);

	op_reg_val &= (~GP2AP020A00F_FLAG_A & ~GP2AP020A00F_FLAG_P
					& ~GP2AP020A00F_PROX_DETECT);

	/* Clear पूर्णांकerrupt flags (अगर not in INTTYPE_PULSE mode) */
	अगर (priv->cur_opmode != GP2AP020A00F_OPMODE_PROX_DETECT) अणु
		ret = regmap_ग_लिखो(priv->regmap, GP2AP020A00F_OP_REG,
								op_reg_val);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (op_reg_flags & GP2AP020A00F_FLAG_A) अणु
		/* Check D0 रेजिस्टर to assess अगर the lux mode
		 * transition is required.
		 */
		ret = regmap_bulk_पढ़ो(priv->regmap, GP2AP020A00F_D0_L_REG,
							d0_reg_buf, 2);
		अगर (ret < 0)
			जाओ करोne;

		output_val = le16_to_cpup((__le16 *)d0_reg_buf);

		अगर (gp2ap020a00f_adjust_lux_mode(priv, output_val))
			जाओ करोne;

		gp2ap020a00f_output_to_lux(priv, &output_val);

		/*
		 * We need to check output value to distinguish
		 * between high and low ambient light threshold event.
		 */
		अगर (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &priv->flags)) अणु
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TH_L_REG);
			अगर (output_val > priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_RISING),
				       iio_get_समय_ns(indio_dev));
		पूर्ण

		अगर (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &priv->flags)) अणु
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TL_L_REG);
			अगर (output_val < priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_FALLING),
				       iio_get_समय_ns(indio_dev));
		पूर्ण
	पूर्ण

	अगर (priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_CLEAR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_IR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY) अणु
		set_bit(GP2AP020A00F_FLAG_DATA_READY, &priv->flags);
		wake_up(&priv->data_पढ़ोy_queue);
		जाओ करोne;
	पूर्ण

	अगर (test_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &priv->flags))
		/* This fires off the trigger. */
		irq_work_queue(&priv->work);

करोne:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gp2ap020a00f_trigger_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_poll_func *pf = data;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा gp2ap020a00f_data *priv = iio_priv(indio_dev);
	माप_प्रकार d_size = 0;
	पूर्णांक i, out_val, ret;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		ret = regmap_bulk_पढ़ो(priv->regmap,
				GP2AP020A00F_DATA_REG(i),
				&priv->buffer[d_size], 2);
		अगर (ret < 0)
			जाओ करोne;

		अगर (i == GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR ||
		    i == GP2AP020A00F_SCAN_MODE_LIGHT_IR) अणु
			out_val = le16_to_cpup((__le16 *)&priv->buffer[d_size]);
			gp2ap020a00f_output_to_lux(priv, &out_val);

			put_unaligned_le32(out_val, &priv->buffer[d_size]);
			d_size += 4;
		पूर्ण अन्यथा अणु
			d_size += 2;
		पूर्ण
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, priv->buffer,
		pf->बारtamp);
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल u8 gp2ap020a00f_get_thresh_reg(स्थिर काष्ठा iio_chan_spec *chan,
					     क्रमागत iio_event_direction event_dir)
अणु
	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (event_dir == IIO_EV_सूची_RISING)
			वापस GP2AP020A00F_PH_L_REG;
		अन्यथा
			वापस GP2AP020A00F_PL_L_REG;
	हाल IIO_LIGHT:
		अगर (event_dir == IIO_EV_सूची_RISING)
			वापस GP2AP020A00F_TH_L_REG;
		अन्यथा
			वापस GP2AP020A00F_TL_L_REG;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gp2ap020a00f_ग_लिखो_event_val(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					क्रमागत iio_event_info info,
					पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	bool event_en = false;
	u8 thresh_val_id;
	u8 thresh_reg_l;
	पूर्णांक err = 0;

	mutex_lock(&data->lock);

	thresh_reg_l = gp2ap020a00f_get_thresh_reg(chan, dir);
	thresh_val_id = GP2AP020A00F_THRESH_VAL_ID(thresh_reg_l);

	अगर (thresh_val_id > GP2AP020A00F_THRESH_PH) अणु
		err = -EINVAL;
		जाओ error_unlock;
	पूर्ण

	चयन (thresh_reg_l) अणु
	हाल GP2AP020A00F_TH_L_REG:
		event_en = test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV,
							&data->flags);
		अवरोध;
	हाल GP2AP020A00F_TL_L_REG:
		event_en = test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV,
							&data->flags);
		अवरोध;
	हाल GP2AP020A00F_PH_L_REG:
		अगर (val == 0) अणु
			err = -EINVAL;
			जाओ error_unlock;
		पूर्ण
		event_en = test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV,
							&data->flags);
		अवरोध;
	हाल GP2AP020A00F_PL_L_REG:
		अगर (val == 0) अणु
			err = -EINVAL;
			जाओ error_unlock;
		पूर्ण
		event_en = test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV,
							&data->flags);
		अवरोध;
	पूर्ण

	data->thresh_val[thresh_val_id] = val;
	err =  gp2ap020a00f_ग_लिखो_event_threshold(data, thresh_val_id,
							event_en);
error_unlock:
	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_पढ़ो_event_val(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       क्रमागत iio_event_info info,
				       पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	u8 thresh_reg_l;
	पूर्णांक err = IIO_VAL_INT;

	mutex_lock(&data->lock);

	thresh_reg_l = gp2ap020a00f_get_thresh_reg(chan, dir);

	अगर (thresh_reg_l > GP2AP020A00F_PH_L_REG) अणु
		err = -EINVAL;
		जाओ error_unlock;
	पूर्ण

	*val = data->thresh_val[GP2AP020A00F_THRESH_VAL_ID(thresh_reg_l)];

error_unlock:
	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_ग_लिखो_prox_event_config(काष्ठा iio_dev *indio_dev,
						पूर्णांक state)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	क्रमागत gp2ap020a00f_cmd cmd_high_ev, cmd_low_ev;
	पूर्णांक err;

	cmd_high_ev = state ? GP2AP020A00F_CMD_PROX_HIGH_EV_EN :
			      GP2AP020A00F_CMD_PROX_HIGH_EV_DIS;
	cmd_low_ev = state ? GP2AP020A00F_CMD_PROX_LOW_EV_EN :
			     GP2AP020A00F_CMD_PROX_LOW_EV_DIS;

	/*
	 * In order to enable proximity detection feature in the device
	 * both high and low threshold रेजिस्टरs have to be written
	 * with dअगरferent values, greater than zero.
	 */
	अगर (state) अणु
		अगर (data->thresh_val[GP2AP020A00F_THRESH_PL] == 0)
			वापस -EINVAL;

		अगर (data->thresh_val[GP2AP020A00F_THRESH_PH] == 0)
			वापस -EINVAL;
	पूर्ण

	err = gp2ap020a00f_exec_cmd(data, cmd_high_ev);
	अगर (err < 0)
		वापस err;

	err = gp2ap020a00f_exec_cmd(data, cmd_low_ev);
	अगर (err < 0)
		वापस err;

	मुक्त_irq(data->client->irq, indio_dev);

	अगर (state)
		err = request_thपढ़ोed_irq(data->client->irq, शून्य,
					   &gp2ap020a00f_prox_sensing_handler,
					   IRQF_TRIGGER_RISING |
					   IRQF_TRIGGER_FALLING |
					   IRQF_ONESHOT,
					   "gp2ap020a00f_prox_sensing",
					   indio_dev);
	अन्यथा अणु
		err = request_thपढ़ोed_irq(data->client->irq, शून्य,
					   &gp2ap020a00f_thresh_event_handler,
					   IRQF_TRIGGER_FALLING |
					   IRQF_ONESHOT,
					   "gp2ap020a00f_thresh_event",
					   indio_dev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   क्रमागत iio_event_type type,
					   क्रमागत iio_event_direction dir,
					   पूर्णांक state)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	क्रमागत gp2ap020a00f_cmd cmd;
	पूर्णांक err;

	mutex_lock(&data->lock);

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		err = gp2ap020a00f_ग_लिखो_prox_event_config(indio_dev, state);
		अवरोध;
	हाल IIO_LIGHT:
		अगर (dir == IIO_EV_सूची_RISING) अणु
			cmd = state ? GP2AP020A00F_CMD_ALS_HIGH_EV_EN :
				      GP2AP020A00F_CMD_ALS_HIGH_EV_DIS;
			err = gp2ap020a00f_exec_cmd(data, cmd);
		पूर्ण अन्यथा अणु
			cmd = state ? GP2AP020A00F_CMD_ALS_LOW_EV_EN :
				      GP2AP020A00F_CMD_ALS_LOW_EV_DIS;
			err = gp2ap020a00f_exec_cmd(data, cmd);
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   क्रमागत iio_event_type type,
					   क्रमागत iio_event_direction dir)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	पूर्णांक event_en = 0;

	mutex_lock(&data->lock);

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (dir == IIO_EV_सूची_RISING)
			event_en = test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV,
								&data->flags);
		अन्यथा
			event_en = test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV,
								&data->flags);
		अवरोध;
	हाल IIO_LIGHT:
		अगर (dir == IIO_EV_सूची_RISING)
			event_en = test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV,
								&data->flags);
		अन्यथा
			event_en = test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV,
								&data->flags);
		अवरोध;
	शेष:
		event_en = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस event_en;
पूर्ण

अटल पूर्णांक gp2ap020a00f_पढ़ो_channel(काष्ठा gp2ap020a00f_data *data,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	क्रमागत gp2ap020a00f_cmd cmd;
	पूर्णांक err;

	चयन (chan->scan_index) अणु
	हाल GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR:
		cmd = GP2AP020A00F_CMD_READ_RAW_CLEAR;
		अवरोध;
	हाल GP2AP020A00F_SCAN_MODE_LIGHT_IR:
		cmd = GP2AP020A00F_CMD_READ_RAW_IR;
		अवरोध;
	हाल GP2AP020A00F_SCAN_MODE_PROXIMITY:
		cmd = GP2AP020A00F_CMD_READ_RAW_PROXIMITY;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = gp2ap020a00f_exec_cmd(data, cmd);
	अगर (err < 0) अणु
		dev_err(&data->client->dev,
			"gp2ap020a00f_exec_cmd failed\n");
		जाओ error_ret;
	पूर्ण

	err = gp2ap020a00f_पढ़ो_output(data, chan->address, val);
	अगर (err < 0)
		dev_err(&data->client->dev,
			"gp2ap020a00f_read_output failed\n");

	err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
	अगर (err < 0)
		dev_err(&data->client->dev,
			"Failed to shut down the device.\n");

	अगर (cmd == GP2AP020A00F_CMD_READ_RAW_CLEAR ||
	    cmd == GP2AP020A00F_CMD_READ_RAW_IR)
		gp2ap020a00f_output_to_lux(data, val);

error_ret:
	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	पूर्णांक err = -EINVAL;

	अगर (mask == IIO_CHAN_INFO_RAW) अणु
		err = iio_device_claim_direct_mode(indio_dev);
		अगर (err)
			वापस err;

		err = gp2ap020a00f_पढ़ो_channel(data, chan, val);
		iio_device_release_direct_mode(indio_dev);
	पूर्ण
	वापस err < 0 ? err : IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec gp2ap020a00f_event_spec_light[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec gp2ap020a00f_event_spec_prox[] = अणु
	अणु
		.type = IIO_EV_TYPE_ROC,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_ROC,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec gp2ap020a00f_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.channel2 = IIO_MOD_LIGHT_CLEAR,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_type = अणु
			.sign = 'u',
			.realbits = 24,
			.shअगरt = 0,
			.storagebits = 32,
			.endianness = IIO_LE,
		पूर्ण,
		.scan_index = GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
		.address = GP2AP020A00F_D0_L_REG,
		.event_spec = gp2ap020a00f_event_spec_light,
		.num_event_specs = ARRAY_SIZE(gp2ap020a00f_event_spec_light),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.channel2 = IIO_MOD_LIGHT_IR,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_type = अणु
			.sign = 'u',
			.realbits = 24,
			.shअगरt = 0,
			.storagebits = 32,
			.endianness = IIO_LE,
		पूर्ण,
		.scan_index = GP2AP020A00F_SCAN_MODE_LIGHT_IR,
		.address = GP2AP020A00F_D1_L_REG,
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.modअगरied = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.shअगरt = 0,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
		.scan_index = GP2AP020A00F_SCAN_MODE_PROXIMITY,
		.address = GP2AP020A00F_D2_L_REG,
		.event_spec = gp2ap020a00f_event_spec_prox,
		.num_event_specs = ARRAY_SIZE(gp2ap020a00f_event_spec_prox),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(GP2AP020A00F_CHAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_info gp2ap020a00f_info = अणु
	.पढ़ो_raw = &gp2ap020a00f_पढ़ो_raw,
	.पढ़ो_event_value = &gp2ap020a00f_पढ़ो_event_val,
	.पढ़ो_event_config = &gp2ap020a00f_पढ़ो_event_config,
	.ग_लिखो_event_value = &gp2ap020a00f_ग_लिखो_event_val,
	.ग_लिखो_event_config = &gp2ap020a00f_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक gp2ap020a00f_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	पूर्णांक i, err = 0;

	mutex_lock(&data->lock);

	/*
	 * Enable triggers according to the scan_mask. Enabling either
	 * LIGHT_CLEAR or LIGHT_IR scan mode results in enabling ALS
	 * module in the device, which generates samples in both D0 (clear)
	 * and D1 (ir) रेजिस्टरs. As the two रेजिस्टरs are bound to the
	 * two separate IIO channels they are treated in the driver logic
	 * as अगर they were controlled independently.
	 */
	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		चयन (i) अणु
		हाल GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_CLEAR_EN);
			अवरोध;
		हाल GP2AP020A00F_SCAN_MODE_LIGHT_IR:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_IR_EN);
			अवरोध;
		हाल GP2AP020A00F_SCAN_MODE_PROXIMITY:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_PROX_EN);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err < 0)
		जाओ error_unlock;

	data->buffer = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL);
	अगर (!data->buffer)
		err = -ENOMEM;

error_unlock:
	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	पूर्णांक i, err = 0;

	mutex_lock(&data->lock);

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		चयन (i) अणु
		हाल GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_CLEAR_DIS);
			अवरोध;
		हाल GP2AP020A00F_SCAN_MODE_LIGHT_IR:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_IR_DIS);
			अवरोध;
		हाल GP2AP020A00F_SCAN_MODE_PROXIMITY:
			err = gp2ap020a00f_exec_cmd(data,
					GP2AP020A00F_CMD_TRIGGER_PROX_DIS);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err == 0)
		kमुक्त(data->buffer);

	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops gp2ap020a00f_buffer_setup_ops = अणु
	.postenable = &gp2ap020a00f_buffer_postenable,
	.predisable = &gp2ap020a00f_buffer_predisable,
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops gp2ap020a00f_trigger_ops = अणु
पूर्ण;

अटल पूर्णांक gp2ap020a00f_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा gp2ap020a00f_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक err;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);

	data->vled_reg = devm_regulator_get(&client->dev, "vled");
	अगर (IS_ERR(data->vled_reg))
		वापस PTR_ERR(data->vled_reg);

	err = regulator_enable(data->vled_reg);
	अगर (err)
		वापस err;

	regmap = devm_regmap_init_i2c(client, &gp2ap020a00f_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Regmap initialization failed.\n");
		err = PTR_ERR(regmap);
		जाओ error_regulator_disable;
	पूर्ण

	/* Initialize device रेजिस्टरs */
	err = regmap_bulk_ग_लिखो(regmap, GP2AP020A00F_OP_REG,
			gp2ap020a00f_reg_init_tab,
			ARRAY_SIZE(gp2ap020a00f_reg_init_tab));

	अगर (err < 0) अणु
		dev_err(&client->dev, "Device initialization failed.\n");
		जाओ error_regulator_disable;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->cur_opmode = GP2AP020A00F_OPMODE_SHUTDOWN;
	data->regmap = regmap;
	init_रुकोqueue_head(&data->data_पढ़ोy_queue);

	mutex_init(&data->lock);
	indio_dev->channels = gp2ap020a00f_channels;
	indio_dev->num_channels = ARRAY_SIZE(gp2ap020a00f_channels);
	indio_dev->info = &gp2ap020a00f_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* Allocate buffer */
	err = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
		&gp2ap020a00f_trigger_handler, &gp2ap020a00f_buffer_setup_ops);
	अगर (err < 0)
		जाओ error_regulator_disable;

	/* Allocate trigger */
	data->trig = devm_iio_trigger_alloc(&client->dev, "%s-trigger",
							indio_dev->name);
	अगर (data->trig == शून्य) अणु
		err = -ENOMEM;
		dev_err(&indio_dev->dev, "Failed to allocate iio trigger.\n");
		जाओ error_uninit_buffer;
	पूर्ण

	/* This needs to be requested here क्रम पढ़ो_raw calls to work. */
	err = request_thपढ़ोed_irq(client->irq, शून्य,
				   &gp2ap020a00f_thresh_event_handler,
				   IRQF_TRIGGER_FALLING |
				   IRQF_ONESHOT,
				   "gp2ap020a00f_als_event",
				   indio_dev);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Irq request failed.\n");
		जाओ error_uninit_buffer;
	पूर्ण

	data->trig->ops = &gp2ap020a00f_trigger_ops;

	init_irq_work(&data->work, gp2ap020a00f_iio_trigger_work);

	err = iio_trigger_रेजिस्टर(data->trig);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Failed to register iio trigger.\n");
		जाओ error_मुक्त_irq;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err < 0)
		जाओ error_trigger_unरेजिस्टर;

	वापस 0;

error_trigger_unरेजिस्टर:
	iio_trigger_unरेजिस्टर(data->trig);
error_मुक्त_irq:
	मुक्त_irq(client->irq, indio_dev);
error_uninit_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
error_regulator_disable:
	regulator_disable(data->vled_reg);

	वापस err;
पूर्ण

अटल पूर्णांक gp2ap020a00f_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा gp2ap020a00f_data *data = iio_priv(indio_dev);
	पूर्णांक err;

	err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
	अगर (err < 0)
		dev_err(&indio_dev->dev, "Failed to power off the device.\n");

	iio_device_unरेजिस्टर(indio_dev);
	iio_trigger_unरेजिस्टर(data->trig);
	मुक्त_irq(client->irq, indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(data->vled_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id gp2ap020a00f_id[] = अणु
	अणु GP2A_I2C_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, gp2ap020a00f_id);

अटल स्थिर काष्ठा of_device_id gp2ap020a00f_of_match[] = अणु
	अणु .compatible = "sharp,gp2ap020a00f" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gp2ap020a00f_of_match);

अटल काष्ठा i2c_driver gp2ap020a00f_driver = अणु
	.driver = अणु
		.name	= GP2A_I2C_NAME,
		.of_match_table = gp2ap020a00f_of_match,
	पूर्ण,
	.probe		= gp2ap020a00f_probe,
	.हटाओ		= gp2ap020a00f_हटाओ,
	.id_table	= gp2ap020a00f_id,
पूर्ण;

module_i2c_driver(gp2ap020a00f_driver);

MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_DESCRIPTION("Sharp GP2AP020A00F Proximity/ALS sensor driver");
MODULE_LICENSE("GPL v2");
