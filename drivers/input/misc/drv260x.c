<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DRV260X haptics driver family
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 *
 * Copyright:   (C) 2014 Texas Instruments, Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <dt-bindings/input/ti-drv260x.h>

#घोषणा DRV260X_STATUS		0x0
#घोषणा DRV260X_MODE		0x1
#घोषणा DRV260X_RT_PB_IN	0x2
#घोषणा DRV260X_LIB_SEL		0x3
#घोषणा DRV260X_WV_SEQ_1	0x4
#घोषणा DRV260X_WV_SEQ_2	0x5
#घोषणा DRV260X_WV_SEQ_3	0x6
#घोषणा DRV260X_WV_SEQ_4	0x7
#घोषणा DRV260X_WV_SEQ_5	0x8
#घोषणा DRV260X_WV_SEQ_6	0x9
#घोषणा DRV260X_WV_SEQ_7	0xa
#घोषणा DRV260X_WV_SEQ_8	0xb
#घोषणा DRV260X_GO				0xc
#घोषणा DRV260X_OVERDRIVE_OFF	0xd
#घोषणा DRV260X_SUSTAIN_P_OFF	0xe
#घोषणा DRV260X_SUSTAIN_N_OFF	0xf
#घोषणा DRV260X_BRAKE_OFF		0x10
#घोषणा DRV260X_A_TO_V_CTRL		0x11
#घोषणा DRV260X_A_TO_V_MIN_INPUT	0x12
#घोषणा DRV260X_A_TO_V_MAX_INPUT	0x13
#घोषणा DRV260X_A_TO_V_MIN_OUT	0x14
#घोषणा DRV260X_A_TO_V_MAX_OUT	0x15
#घोषणा DRV260X_RATED_VOLT		0x16
#घोषणा DRV260X_OD_CLAMP_VOLT	0x17
#घोषणा DRV260X_CAL_COMP		0x18
#घोषणा DRV260X_CAL_BACK_EMF	0x19
#घोषणा DRV260X_FEEDBACK_CTRL	0x1a
#घोषणा DRV260X_CTRL1			0x1b
#घोषणा DRV260X_CTRL2			0x1c
#घोषणा DRV260X_CTRL3			0x1d
#घोषणा DRV260X_CTRL4			0x1e
#घोषणा DRV260X_CTRL5			0x1f
#घोषणा DRV260X_LRA_LOOP_PERIOD	0x20
#घोषणा DRV260X_VBAT_MON		0x21
#घोषणा DRV260X_LRA_RES_PERIOD	0x22
#घोषणा DRV260X_MAX_REG			0x23

#घोषणा DRV260X_GO_BIT				0x01

/* Library Selection */
#घोषणा DRV260X_LIB_SEL_MASK		0x07
#घोषणा DRV260X_LIB_SEL_RAM			0x0
#घोषणा DRV260X_LIB_SEL_OD			0x1
#घोषणा DRV260X_LIB_SEL_40_60		0x2
#घोषणा DRV260X_LIB_SEL_60_80		0x3
#घोषणा DRV260X_LIB_SEL_100_140		0x4
#घोषणा DRV260X_LIB_SEL_140_PLUS	0x5

#घोषणा DRV260X_LIB_SEL_HIZ_MASK	0x10
#घोषणा DRV260X_LIB_SEL_HIZ_EN		0x01
#घोषणा DRV260X_LIB_SEL_HIZ_DIS		0

/* Mode रेजिस्टर */
#घोषणा DRV260X_STANDBY				(1 << 6)
#घोषणा DRV260X_STANDBY_MASK		0x40
#घोषणा DRV260X_INTERNAL_TRIGGER	0x00
#घोषणा DRV260X_EXT_TRIGGER_EDGE	0x01
#घोषणा DRV260X_EXT_TRIGGER_LEVEL	0x02
#घोषणा DRV260X_PWM_ANALOG_IN		0x03
#घोषणा DRV260X_AUDIOHAPTIC			0x04
#घोषणा DRV260X_RT_PLAYBACK			0x05
#घोषणा DRV260X_DIAGNOSTICS			0x06
#घोषणा DRV260X_AUTO_CAL			0x07

/* Audio to Haptics Control */
#घोषणा DRV260X_AUDIO_HAPTICS_PEAK_10MS		(0 << 2)
#घोषणा DRV260X_AUDIO_HAPTICS_PEAK_20MS		(1 << 2)
#घोषणा DRV260X_AUDIO_HAPTICS_PEAK_30MS		(2 << 2)
#घोषणा DRV260X_AUDIO_HAPTICS_PEAK_40MS		(3 << 2)

#घोषणा DRV260X_AUDIO_HAPTICS_FILTER_100HZ	0x00
#घोषणा DRV260X_AUDIO_HAPTICS_FILTER_125HZ	0x01
#घोषणा DRV260X_AUDIO_HAPTICS_FILTER_150HZ	0x02
#घोषणा DRV260X_AUDIO_HAPTICS_FILTER_200HZ	0x03

/* Min/Max Input/Output Voltages */
#घोषणा DRV260X_AUDIO_HAPTICS_MIN_IN_VOLT	0x19
#घोषणा DRV260X_AUDIO_HAPTICS_MAX_IN_VOLT	0x64
#घोषणा DRV260X_AUDIO_HAPTICS_MIN_OUT_VOLT	0x19
#घोषणा DRV260X_AUDIO_HAPTICS_MAX_OUT_VOLT	0xFF

/* Feedback रेजिस्टर */
#घोषणा DRV260X_FB_REG_ERM_MODE			0x7f
#घोषणा DRV260X_FB_REG_LRA_MODE			(1 << 7)

#घोषणा DRV260X_BRAKE_FACTOR_MASK	0x1f
#घोषणा DRV260X_BRAKE_FACTOR_2X		(1 << 0)
#घोषणा DRV260X_BRAKE_FACTOR_3X		(2 << 4)
#घोषणा DRV260X_BRAKE_FACTOR_4X		(3 << 4)
#घोषणा DRV260X_BRAKE_FACTOR_6X		(4 << 4)
#घोषणा DRV260X_BRAKE_FACTOR_8X		(5 << 4)
#घोषणा DRV260X_BRAKE_FACTOR_16		(6 << 4)
#घोषणा DRV260X_BRAKE_FACTOR_DIS	(7 << 4)

#घोषणा DRV260X_LOOP_GAIN_LOW		0xf3
#घोषणा DRV260X_LOOP_GAIN_MED		(1 << 2)
#घोषणा DRV260X_LOOP_GAIN_HIGH		(2 << 2)
#घोषणा DRV260X_LOOP_GAIN_VERY_HIGH	(3 << 2)

#घोषणा DRV260X_BEMF_GAIN_0			0xfc
#घोषणा DRV260X_BEMF_GAIN_1		(1 << 0)
#घोषणा DRV260X_BEMF_GAIN_2		(2 << 0)
#घोषणा DRV260X_BEMF_GAIN_3		(3 << 0)

/* Control 1 रेजिस्टर */
#घोषणा DRV260X_AC_CPLE_EN			(1 << 5)
#घोषणा DRV260X_STARTUP_BOOST		(1 << 7)

/* Control 2 रेजिस्टर */

#घोषणा DRV260X_IDISS_TIME_45		0
#घोषणा DRV260X_IDISS_TIME_75		(1 << 0)
#घोषणा DRV260X_IDISS_TIME_150		(1 << 1)
#घोषणा DRV260X_IDISS_TIME_225		0x03

#घोषणा DRV260X_BLANK_TIME_45	(0 << 2)
#घोषणा DRV260X_BLANK_TIME_75	(1 << 2)
#घोषणा DRV260X_BLANK_TIME_150	(2 << 2)
#घोषणा DRV260X_BLANK_TIME_225	(3 << 2)

#घोषणा DRV260X_SAMP_TIME_150	(0 << 4)
#घोषणा DRV260X_SAMP_TIME_200	(1 << 4)
#घोषणा DRV260X_SAMP_TIME_250	(2 << 4)
#घोषणा DRV260X_SAMP_TIME_300	(3 << 4)

#घोषणा DRV260X_BRAKE_STABILIZER	(1 << 6)
#घोषणा DRV260X_UNIसूची_IN			(0 << 7)
#घोषणा DRV260X_BIसूची_IN			(1 << 7)

/* Control 3 Register */
#घोषणा DRV260X_LRA_OPEN_LOOP		(1 << 0)
#घोषणा DRV260X_Aन_अंकLOG_IN			(1 << 1)
#घोषणा DRV260X_LRA_DRV_MODE		(1 << 2)
#घोषणा DRV260X_RTP_UNSIGNED_DATA	(1 << 3)
#घोषणा DRV260X_SUPPLY_COMP_DIS		(1 << 4)
#घोषणा DRV260X_ERM_OPEN_LOOP		(1 << 5)
#घोषणा DRV260X_NG_THRESH_0			(0 << 6)
#घोषणा DRV260X_NG_THRESH_2			(1 << 6)
#घोषणा DRV260X_NG_THRESH_4			(2 << 6)
#घोषणा DRV260X_NG_THRESH_8			(3 << 6)

/* Control 4 Register */
#घोषणा DRV260X_AUTOCAL_TIME_150MS		(0 << 4)
#घोषणा DRV260X_AUTOCAL_TIME_250MS		(1 << 4)
#घोषणा DRV260X_AUTOCAL_TIME_500MS		(2 << 4)
#घोषणा DRV260X_AUTOCAL_TIME_1000MS		(3 << 4)

/**
 * काष्ठा drv260x_data -
 * @input_dev: Poपूर्णांकer to the input device
 * @client: Poपूर्णांकer to the I2C client
 * @regmap: Register map of the device
 * @work: Work item used to off load the enable/disable of the vibration
 * @enable_gpio: Poपूर्णांकer to the gpio used क्रम enable/disabling
 * @regulator: Poपूर्णांकer to the regulator क्रम the IC
 * @magnitude: Magnitude of the vibration event
 * @mode: The operating mode of the IC (LRA_NO_CAL, ERM or LRA)
 * @library: The vibration library to be used
 * @rated_voltage: The rated_voltage of the actuator
 * @overdrive_voltage: The over drive voltage of the actuator
**/
काष्ठा drv260x_data अणु
	काष्ठा input_dev *input_dev;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा work_काष्ठा work;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
	u32 magnitude;
	u32 mode;
	u32 library;
	पूर्णांक rated_voltage;
	पूर्णांक overdrive_voltage;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष drv260x_reg_defs[] = अणु
	अणु DRV260X_STATUS, 0xe0 पूर्ण,
	अणु DRV260X_MODE, 0x40 पूर्ण,
	अणु DRV260X_RT_PB_IN, 0x00 पूर्ण,
	अणु DRV260X_LIB_SEL, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_1, 0x01 पूर्ण,
	अणु DRV260X_WV_SEQ_2, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_3, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_4, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_5, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_6, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_7, 0x00 पूर्ण,
	अणु DRV260X_WV_SEQ_8, 0x00 पूर्ण,
	अणु DRV260X_GO, 0x00 पूर्ण,
	अणु DRV260X_OVERDRIVE_OFF, 0x00 पूर्ण,
	अणु DRV260X_SUSTAIN_P_OFF, 0x00 पूर्ण,
	अणु DRV260X_SUSTAIN_N_OFF, 0x00 पूर्ण,
	अणु DRV260X_BRAKE_OFF, 0x00 पूर्ण,
	अणु DRV260X_A_TO_V_CTRL, 0x05 पूर्ण,
	अणु DRV260X_A_TO_V_MIN_INPUT, 0x19 पूर्ण,
	अणु DRV260X_A_TO_V_MAX_INPUT, 0xff पूर्ण,
	अणु DRV260X_A_TO_V_MIN_OUT, 0x19 पूर्ण,
	अणु DRV260X_A_TO_V_MAX_OUT, 0xff पूर्ण,
	अणु DRV260X_RATED_VOLT, 0x3e पूर्ण,
	अणु DRV260X_OD_CLAMP_VOLT, 0x8c पूर्ण,
	अणु DRV260X_CAL_COMP, 0x0c पूर्ण,
	अणु DRV260X_CAL_BACK_EMF, 0x6c पूर्ण,
	अणु DRV260X_FEEDBACK_CTRL, 0x36 पूर्ण,
	अणु DRV260X_CTRL1, 0x93 पूर्ण,
	अणु DRV260X_CTRL2, 0xfa पूर्ण,
	अणु DRV260X_CTRL3, 0xa0 पूर्ण,
	अणु DRV260X_CTRL4, 0x20 पूर्ण,
	अणु DRV260X_CTRL5, 0x80 पूर्ण,
	अणु DRV260X_LRA_LOOP_PERIOD, 0x33 पूर्ण,
	अणु DRV260X_VBAT_MON, 0x00 पूर्ण,
	अणु DRV260X_LRA_RES_PERIOD, 0x00 पूर्ण,
पूर्ण;

#घोषणा DRV260X_DEF_RATED_VOLT		0x90
#घोषणा DRV260X_DEF_OD_CLAMP_VOLT	0x90

/*
 * Rated and Overdriver Voltages:
 * Calculated using the क्रमmula r = v * 255 / 5.6
 * where r is what will be written to the रेजिस्टर
 * and v is the rated or overdriver voltage of the actuator
 */
अटल पूर्णांक drv260x_calculate_voltage(अचिन्हित पूर्णांक voltage)
अणु
	वापस (voltage * 255 / 5600);
पूर्ण

अटल व्योम drv260x_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drv260x_data *haptics = container_of(work, काष्ठा drv260x_data, work);
	पूर्णांक error;

	gpiod_set_value(haptics->enable_gpio, 1);
	/* Data sheet says to रुको 250us beक्रमe trying to communicate */
	udelay(250);

	error = regmap_ग_लिखो(haptics->regmap,
			     DRV260X_MODE, DRV260X_RT_PLAYBACK);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write set mode: %d\n", error);
	पूर्ण अन्यथा अणु
		error = regmap_ग_लिखो(haptics->regmap,
				     DRV260X_RT_PB_IN, haptics->magnitude);
		अगर (error)
			dev_err(&haptics->client->dev,
				"Failed to set magnitude: %d\n", error);
	पूर्ण
पूर्ण

अटल पूर्णांक drv260x_haptics_play(काष्ठा input_dev *input, व्योम *data,
				काष्ठा ff_effect *effect)
अणु
	काष्ठा drv260x_data *haptics = input_get_drvdata(input);

	haptics->mode = DRV260X_LRA_NO_CAL_MODE;

	अगर (effect->u.rumble.strong_magnitude > 0)
		haptics->magnitude = effect->u.rumble.strong_magnitude;
	अन्यथा अगर (effect->u.rumble.weak_magnitude > 0)
		haptics->magnitude = effect->u.rumble.weak_magnitude;
	अन्यथा
		haptics->magnitude = 0;

	schedule_work(&haptics->work);

	वापस 0;
पूर्ण

अटल व्योम drv260x_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा drv260x_data *haptics = input_get_drvdata(input);
	पूर्णांक error;

	cancel_work_sync(&haptics->work);

	error = regmap_ग_लिखो(haptics->regmap, DRV260X_MODE, DRV260X_STANDBY);
	अगर (error)
		dev_err(&haptics->client->dev,
			"Failed to enter standby mode: %d\n", error);

	gpiod_set_value(haptics->enable_gpio, 0);
पूर्ण

अटल स्थिर काष्ठा reg_sequence drv260x_lra_cal_regs[] = अणु
	अणु DRV260X_MODE, DRV260X_AUTO_CAL पूर्ण,
	अणु DRV260X_CTRL3, DRV260X_NG_THRESH_2 पूर्ण,
	अणु DRV260X_FEEDBACK_CTRL, DRV260X_FB_REG_LRA_MODE |
		DRV260X_BRAKE_FACTOR_4X | DRV260X_LOOP_GAIN_HIGH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence drv260x_lra_init_regs[] = अणु
	अणु DRV260X_MODE, DRV260X_RT_PLAYBACK पूर्ण,
	अणु DRV260X_A_TO_V_CTRL, DRV260X_AUDIO_HAPTICS_PEAK_20MS |
		DRV260X_AUDIO_HAPTICS_FILTER_125HZ पूर्ण,
	अणु DRV260X_A_TO_V_MIN_INPUT, DRV260X_AUDIO_HAPTICS_MIN_IN_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MAX_INPUT, DRV260X_AUDIO_HAPTICS_MAX_IN_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MIN_OUT, DRV260X_AUDIO_HAPTICS_MIN_OUT_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MAX_OUT, DRV260X_AUDIO_HAPTICS_MAX_OUT_VOLT पूर्ण,
	अणु DRV260X_FEEDBACK_CTRL, DRV260X_FB_REG_LRA_MODE |
		DRV260X_BRAKE_FACTOR_2X | DRV260X_LOOP_GAIN_MED |
		DRV260X_BEMF_GAIN_3 पूर्ण,
	अणु DRV260X_CTRL1, DRV260X_STARTUP_BOOST पूर्ण,
	अणु DRV260X_CTRL2, DRV260X_SAMP_TIME_250 पूर्ण,
	अणु DRV260X_CTRL3, DRV260X_NG_THRESH_2 | DRV260X_Aन_अंकLOG_IN पूर्ण,
	अणु DRV260X_CTRL4, DRV260X_AUTOCAL_TIME_500MS पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence drv260x_erm_cal_regs[] = अणु
	अणु DRV260X_MODE, DRV260X_AUTO_CAL पूर्ण,
	अणु DRV260X_A_TO_V_MIN_INPUT, DRV260X_AUDIO_HAPTICS_MIN_IN_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MAX_INPUT, DRV260X_AUDIO_HAPTICS_MAX_IN_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MIN_OUT, DRV260X_AUDIO_HAPTICS_MIN_OUT_VOLT पूर्ण,
	अणु DRV260X_A_TO_V_MAX_OUT, DRV260X_AUDIO_HAPTICS_MAX_OUT_VOLT पूर्ण,
	अणु DRV260X_FEEDBACK_CTRL, DRV260X_BRAKE_FACTOR_3X |
		DRV260X_LOOP_GAIN_MED | DRV260X_BEMF_GAIN_2 पूर्ण,
	अणु DRV260X_CTRL1, DRV260X_STARTUP_BOOST पूर्ण,
	अणु DRV260X_CTRL2, DRV260X_SAMP_TIME_250 | DRV260X_BLANK_TIME_75 |
		DRV260X_IDISS_TIME_75 पूर्ण,
	अणु DRV260X_CTRL3, DRV260X_NG_THRESH_2 | DRV260X_ERM_OPEN_LOOP पूर्ण,
	अणु DRV260X_CTRL4, DRV260X_AUTOCAL_TIME_500MS पूर्ण,
पूर्ण;

अटल पूर्णांक drv260x_init(काष्ठा drv260x_data *haptics)
अणु
	पूर्णांक error;
	अचिन्हित पूर्णांक cal_buf;

	error = regmap_ग_लिखो(haptics->regmap,
			     DRV260X_RATED_VOLT, haptics->rated_voltage);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write DRV260X_RATED_VOLT register: %d\n",
			error);
		वापस error;
	पूर्ण

	error = regmap_ग_लिखो(haptics->regmap,
			     DRV260X_OD_CLAMP_VOLT, haptics->overdrive_voltage);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write DRV260X_OD_CLAMP_VOLT register: %d\n",
			error);
		वापस error;
	पूर्ण

	चयन (haptics->mode) अणु
	हाल DRV260X_LRA_MODE:
		error = regmap_रेजिस्टर_patch(haptics->regmap,
					      drv260x_lra_cal_regs,
					      ARRAY_SIZE(drv260x_lra_cal_regs));
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write LRA calibration registers: %d\n",
				error);
			वापस error;
		पूर्ण

		अवरोध;

	हाल DRV260X_ERM_MODE:
		error = regmap_रेजिस्टर_patch(haptics->regmap,
					      drv260x_erm_cal_regs,
					      ARRAY_SIZE(drv260x_erm_cal_regs));
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write ERM calibration registers: %d\n",
				error);
			वापस error;
		पूर्ण

		error = regmap_update_bits(haptics->regmap, DRV260X_LIB_SEL,
					   DRV260X_LIB_SEL_MASK,
					   haptics->library);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write DRV260X_LIB_SEL register: %d\n",
				error);
			वापस error;
		पूर्ण

		अवरोध;

	शेष:
		error = regmap_रेजिस्टर_patch(haptics->regmap,
					      drv260x_lra_init_regs,
					      ARRAY_SIZE(drv260x_lra_init_regs));
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write LRA init registers: %d\n",
				error);
			वापस error;
		पूर्ण

		error = regmap_update_bits(haptics->regmap, DRV260X_LIB_SEL,
					   DRV260X_LIB_SEL_MASK,
					   haptics->library);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write DRV260X_LIB_SEL register: %d\n",
				error);
			वापस error;
		पूर्ण

		/* No need to set GO bit here */
		वापस 0;
	पूर्ण

	error = regmap_ग_लिखो(haptics->regmap, DRV260X_GO, DRV260X_GO_BIT);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write GO register: %d\n",
			error);
		वापस error;
	पूर्ण

	करो अणु
		error = regmap_पढ़ो(haptics->regmap, DRV260X_GO, &cal_buf);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to read GO register: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण जबतक (cal_buf == DRV260X_GO_BIT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config drv260x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = DRV260X_MAX_REG,
	.reg_शेषs = drv260x_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(drv260x_reg_defs),
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक drv260x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा drv260x_data *haptics;
	u32 voltage;
	पूर्णांक error;

	haptics = devm_kzalloc(dev, माप(*haptics), GFP_KERNEL);
	अगर (!haptics)
		वापस -ENOMEM;

	error = device_property_पढ़ो_u32(dev, "mode", &haptics->mode);
	अगर (error) अणु
		dev_err(dev, "Can't fetch 'mode' property: %d\n", error);
		वापस error;
	पूर्ण

	अगर (haptics->mode < DRV260X_LRA_MODE ||
	    haptics->mode > DRV260X_ERM_MODE) अणु
		dev_err(dev, "Vibrator mode is invalid: %i\n", haptics->mode);
		वापस -EINVAL;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "library-sel", &haptics->library);
	अगर (error) अणु
		dev_err(dev, "Can't fetch 'library-sel' property: %d\n", error);
		वापस error;
	पूर्ण

	अगर (haptics->library < DRV260X_LIB_EMPTY ||
	    haptics->library > DRV260X_ERM_LIB_F) अणु
		dev_err(dev,
			"Library value is invalid: %i\n", haptics->library);
		वापस -EINVAL;
	पूर्ण

	अगर (haptics->mode == DRV260X_LRA_MODE &&
	    haptics->library != DRV260X_LIB_EMPTY &&
	    haptics->library != DRV260X_LIB_LRA) अणु
		dev_err(dev, "LRA Mode with ERM Library mismatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (haptics->mode == DRV260X_ERM_MODE &&
	    (haptics->library == DRV260X_LIB_EMPTY ||
	     haptics->library == DRV260X_LIB_LRA)) अणु
		dev_err(dev, "ERM Mode with LRA Library mismatch\n");
		वापस -EINVAL;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "vib-rated-mv", &voltage);
	haptics->rated_voltage = error ? DRV260X_DEF_RATED_VOLT :
					 drv260x_calculate_voltage(voltage);

	error = device_property_पढ़ो_u32(dev, "vib-overdrive-mv", &voltage);
	haptics->overdrive_voltage = error ? DRV260X_DEF_OD_CLAMP_VOLT :
					     drv260x_calculate_voltage(voltage);

	haptics->regulator = devm_regulator_get(dev, "vbat");
	अगर (IS_ERR(haptics->regulator)) अणु
		error = PTR_ERR(haptics->regulator);
		dev_err(dev, "unable to get regulator, error: %d\n", error);
		वापस error;
	पूर्ण

	haptics->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						       GPIOD_OUT_HIGH);
	अगर (IS_ERR(haptics->enable_gpio))
		वापस PTR_ERR(haptics->enable_gpio);

	haptics->input_dev = devm_input_allocate_device(dev);
	अगर (!haptics->input_dev) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	haptics->input_dev->name = "drv260x:haptics";
	haptics->input_dev->बंद = drv260x_बंद;
	input_set_drvdata(haptics->input_dev, haptics);
	input_set_capability(haptics->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptics->input_dev, शून्य,
					drv260x_haptics_play);
	अगर (error) अणु
		dev_err(dev, "input_ff_create() failed: %d\n", error);
		वापस error;
	पूर्ण

	INIT_WORK(&haptics->work, drv260x_worker);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client, &drv260x_regmap_config);
	अगर (IS_ERR(haptics->regmap)) अणु
		error = PTR_ERR(haptics->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		वापस error;
	पूर्ण

	error = drv260x_init(haptics);
	अगर (error) अणु
		dev_err(dev, "Device init failed: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(haptics->input_dev);
	अगर (error) अणु
		dev_err(dev, "couldn't register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused drv260x_suspend(काष्ठा device *dev)
अणु
	काष्ठा drv260x_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regmap_update_bits(haptics->regmap,
					 DRV260X_MODE,
					 DRV260X_STANDBY_MASK,
					 DRV260X_STANDBY);
		अगर (ret) अणु
			dev_err(dev, "Failed to set standby mode\n");
			जाओ out;
		पूर्ण

		gpiod_set_value(haptics->enable_gpio, 0);

		ret = regulator_disable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to disable regulator\n");
			regmap_update_bits(haptics->regmap,
					   DRV260X_MODE,
					   DRV260X_STANDBY_MASK, 0);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&haptics->input_dev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused drv260x_resume(काष्ठा device *dev)
अणु
	काष्ठा drv260x_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regulator_enable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator\n");
			जाओ out;
		पूर्ण

		ret = regmap_update_bits(haptics->regmap,
					 DRV260X_MODE,
					 DRV260X_STANDBY_MASK, 0);
		अगर (ret) अणु
			dev_err(dev, "Failed to unset standby mode\n");
			regulator_disable(haptics->regulator);
			जाओ out;
		पूर्ण

		gpiod_set_value(haptics->enable_gpio, 1);
	पूर्ण

out:
	mutex_unlock(&haptics->input_dev->mutex);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(drv260x_pm_ops, drv260x_suspend, drv260x_resume);

अटल स्थिर काष्ठा i2c_device_id drv260x_id[] = अणु
	अणु "drv2605l", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, drv260x_id);

अटल स्थिर काष्ठा of_device_id drv260x_of_match[] = अणु
	अणु .compatible = "ti,drv2604", पूर्ण,
	अणु .compatible = "ti,drv2604l", पूर्ण,
	अणु .compatible = "ti,drv2605", पूर्ण,
	अणु .compatible = "ti,drv2605l", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, drv260x_of_match);

अटल काष्ठा i2c_driver drv260x_driver = अणु
	.probe		= drv260x_probe,
	.driver		= अणु
		.name	= "drv260x-haptics",
		.of_match_table = drv260x_of_match,
		.pm	= &drv260x_pm_ops,
	पूर्ण,
	.id_table = drv260x_id,
पूर्ण;
module_i2c_driver(drv260x_driver);

MODULE_DESCRIPTION("TI DRV260x haptics driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
