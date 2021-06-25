<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of the APDS990x sensor driver.
 * Chip is combined proximity and ambient light sensor.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/apds990x.h>

/* Register map */
#घोषणा APDS990X_ENABLE	 0x00 /* Enable of states and पूर्णांकerrupts */
#घोषणा APDS990X_ATIME	 0x01 /* ALS ADC समय  */
#घोषणा APDS990X_PTIME	 0x02 /* Proximity ADC समय  */
#घोषणा APDS990X_WTIME	 0x03 /* Wait समय  */
#घोषणा APDS990X_AILTL	 0x04 /* ALS पूर्णांकerrupt low threshold low byte */
#घोषणा APDS990X_AILTH	 0x05 /* ALS पूर्णांकerrupt low threshold hi byte */
#घोषणा APDS990X_AIHTL	 0x06 /* ALS पूर्णांकerrupt hi threshold low byte */
#घोषणा APDS990X_AIHTH	 0x07 /* ALS पूर्णांकerrupt hi threshold hi byte */
#घोषणा APDS990X_PILTL	 0x08 /* Proximity पूर्णांकerrupt low threshold low byte */
#घोषणा APDS990X_PILTH	 0x09 /* Proximity पूर्णांकerrupt low threshold hi byte */
#घोषणा APDS990X_PIHTL	 0x0a /* Proximity पूर्णांकerrupt hi threshold low byte */
#घोषणा APDS990X_PIHTH	 0x0b /* Proximity पूर्णांकerrupt hi threshold hi byte */
#घोषणा APDS990X_PERS	 0x0c /* Interrupt persistence filters */
#घोषणा APDS990X_CONFIG	 0x0d /* Configuration */
#घोषणा APDS990X_PPCOUNT 0x0e /* Proximity pulse count */
#घोषणा APDS990X_CONTROL 0x0f /* Gain control रेजिस्टर */
#घोषणा APDS990X_REV	 0x11 /* Revision Number */
#घोषणा APDS990X_ID	 0x12 /* Device ID */
#घोषणा APDS990X_STATUS	 0x13 /* Device status */
#घोषणा APDS990X_CDATAL	 0x14 /* Clear ADC low data रेजिस्टर */
#घोषणा APDS990X_CDATAH	 0x15 /* Clear ADC high data रेजिस्टर */
#घोषणा APDS990X_IRDATAL 0x16 /* IR ADC low data रेजिस्टर */
#घोषणा APDS990X_IRDATAH 0x17 /* IR ADC high data रेजिस्टर */
#घोषणा APDS990X_PDATAL	 0x18 /* Proximity ADC low data रेजिस्टर */
#घोषणा APDS990X_PDATAH	 0x19 /* Proximity ADC high data रेजिस्टर */

/* Control */
#घोषणा APDS990X_MAX_AGAIN	3

/* Enable रेजिस्टर */
#घोषणा APDS990X_EN_PIEN	(0x1 << 5)
#घोषणा APDS990X_EN_AIEN	(0x1 << 4)
#घोषणा APDS990X_EN_WEN		(0x1 << 3)
#घोषणा APDS990X_EN_PEN		(0x1 << 2)
#घोषणा APDS990X_EN_AEN		(0x1 << 1)
#घोषणा APDS990X_EN_PON		(0x1 << 0)
#घोषणा APDS990X_EN_DISABLE_ALL 0

/* Status रेजिस्टर */
#घोषणा APDS990X_ST_PINT	(0x1 << 5)
#घोषणा APDS990X_ST_AINT	(0x1 << 4)

/* I2C access types */
#घोषणा APDS990x_CMD_TYPE_MASK	(0x03 << 5)
#घोषणा APDS990x_CMD_TYPE_RB	(0x00 << 5) /* Repeated byte */
#घोषणा APDS990x_CMD_TYPE_INC	(0x01 << 5) /* Auto increment */
#घोषणा APDS990x_CMD_TYPE_SPE	(0x03 << 5) /* Special function */

#घोषणा APDS990x_ADDR_SHIFT	0
#घोषणा APDS990x_CMD		0x80

/* Interrupt ack commands */
#घोषणा APDS990X_INT_ACK_ALS	0x6
#घोषणा APDS990X_INT_ACK_PS	0x5
#घोषणा APDS990X_INT_ACK_BOTH	0x7

/* pसमय */
#घोषणा APDS990X_PTIME_DEFAULT	0xff /* Recommended conversion समय 2.7ms*/

/* wसमय */
#घोषणा APDS990X_WTIME_DEFAULT	0xee /* ~50ms रुको समय */

#घोषणा APDS990X_TIME_TO_ADC	1024 /* One समयtick as ADC count value */

/* Persistence */
#घोषणा APDS990X_APERS_SHIFT	0
#घोषणा APDS990X_PPERS_SHIFT	4

/* Supported ID:s */
#घोषणा APDS990X_ID_0		0x0
#घोषणा APDS990X_ID_4		0x4
#घोषणा APDS990X_ID_29		0x29

/* pgain and pdiode settings */
#घोषणा APDS_PGAIN_1X	       0x0
#घोषणा APDS_PDIODE_IR	       0x2

#घोषणा APDS990X_LUX_OUTPUT_SCALE 10

/* Reverse chip factors क्रम threshold calculation */
काष्ठा reverse_factors अणु
	u32 afactor;
	पूर्णांक cf1;
	पूर्णांक irf1;
	पूर्णांक cf2;
	पूर्णांक irf2;
पूर्ण;

काष्ठा apds990x_chip अणु
	काष्ठा apds990x_platक्रमm_data	*pdata;
	काष्ठा i2c_client		*client;
	काष्ठा mutex			mutex; /* aव्योम parallel access */
	काष्ठा regulator_bulk_data	regs[2];
	रुको_queue_head_t		रुको;

	पूर्णांक	prox_en;
	bool	prox_continuous_mode;
	bool	lux_रुको_fresh_res;

	/* Chip parameters */
	काष्ठा	apds990x_chip_factors	cf;
	काष्ठा	reverse_factors		rcf;
	u16	aसमय;		/* als पूर्णांकegration समय */
	u16	arate;		/* als reporting rate */
	u16	a_max_result;	/* Max possible ADC value with current aसमय */
	u8	again_meas;	/* Gain used in last measurement */
	u8	again_next;	/* Next calculated gain */
	u8	pgain;
	u8	pdiode;
	u8	pdrive;
	u8	lux_persistence;
	u8	prox_persistence;

	u32	lux_raw;
	u32	lux;
	u16	lux_clear;
	u16	lux_ir;
	u16	lux_calib;
	u32	lux_thres_hi;
	u32	lux_thres_lo;

	u32	prox_thres;
	u16	prox_data;
	u16	prox_calib;

	अक्षर	chipname[10];
	u8	revision;
पूर्ण;

#घोषणा APDS_CALIB_SCALER		8192
#घोषणा APDS_LUX_NEUTRAL_CALIB_VALUE	(1 * APDS_CALIB_SCALER)
#घोषणा APDS_PROX_NEUTRAL_CALIB_VALUE	(1 * APDS_CALIB_SCALER)

#घोषणा APDS_PROX_DEF_THRES		600
#घोषणा APDS_PROX_HYSTERESIS		50
#घोषणा APDS_LUX_DEF_THRES_HI		101
#घोषणा APDS_LUX_DEF_THRES_LO		100
#घोषणा APDS_DEFAULT_PROX_PERS		1

#घोषणा APDS_TIMEOUT			2000
#घोषणा APDS_STARTUP_DELAY		25000 /* us */
#घोषणा APDS_RANGE			65535
#घोषणा APDS_PROX_RANGE			1023
#घोषणा APDS_LUX_GAIN_LO_LIMIT		100
#घोषणा APDS_LUX_GAIN_LO_LIMIT_STRICT	25

#घोषणा TIMESTEP			87 /* 2.7ms is about 87 / 32 */
#घोषणा TIME_STEP_SCALER		32

#घोषणा APDS_LUX_AVERAGING_TIME		50 /* tolerates 50/60Hz ripple */
#घोषणा APDS_LUX_DEFAULT_RATE		200

अटल स्थिर u8 again[]	= अणु1, 8, 16, 120पूर्ण; /* ALS gain steps */

/* Following two tables must match i.e 10Hz rate means 1 as persistence value */
अटल स्थिर u16 arates_hz[] = अणु10, 5, 2, 1पूर्ण;
अटल स्थिर u8 apersis[] = अणु1, 2, 4, 5पूर्ण;

/* Regulators */
अटल स्थिर अक्षर reg_vcc[] = "Vdd";
अटल स्थिर अक्षर reg_vled[] = "Vled";

अटल पूर्णांक apds990x_पढ़ो_byte(काष्ठा apds990x_chip *chip, u8 reg, u8 *data)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;

	reg &= ~APDS990x_CMD_TYPE_MASK;
	reg |= APDS990x_CMD | APDS990x_CMD_TYPE_RB;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	*data = ret;
	वापस (पूर्णांक)ret;
पूर्ण

अटल पूर्णांक apds990x_पढ़ो_word(काष्ठा apds990x_chip *chip, u8 reg, u16 *data)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;

	reg &= ~APDS990x_CMD_TYPE_MASK;
	reg |= APDS990x_CMD | APDS990x_CMD_TYPE_INC;

	ret = i2c_smbus_पढ़ो_word_data(client, reg);
	*data = ret;
	वापस (पूर्णांक)ret;
पूर्ण

अटल पूर्णांक apds990x_ग_लिखो_byte(काष्ठा apds990x_chip *chip, u8 reg, u8 data)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;

	reg &= ~APDS990x_CMD_TYPE_MASK;
	reg |= APDS990x_CMD | APDS990x_CMD_TYPE_RB;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, data);
	वापस (पूर्णांक)ret;
पूर्ण

अटल पूर्णांक apds990x_ग_लिखो_word(काष्ठा apds990x_chip *chip, u8 reg, u16 data)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;

	reg &= ~APDS990x_CMD_TYPE_MASK;
	reg |= APDS990x_CMD | APDS990x_CMD_TYPE_INC;

	ret = i2c_smbus_ग_लिखो_word_data(client, reg, data);
	वापस (पूर्णांक)ret;
पूर्ण

अटल पूर्णांक apds990x_mode_on(काष्ठा apds990x_chip *chip)
अणु
	/* ALS is mandatory, proximity optional */
	u8 reg = APDS990X_EN_AIEN | APDS990X_EN_PON | APDS990X_EN_AEN |
		APDS990X_EN_WEN;

	अगर (chip->prox_en)
		reg |= APDS990X_EN_PIEN | APDS990X_EN_PEN;

	वापस apds990x_ग_लिखो_byte(chip, APDS990X_ENABLE, reg);
पूर्ण

अटल u16 apds990x_lux_to_threshold(काष्ठा apds990x_chip *chip, u32 lux)
अणु
	u32 thres;
	u32 cpl;
	u32 ir;

	अगर (lux == 0)
		वापस 0;
	अन्यथा अगर (lux == APDS_RANGE)
		वापस APDS_RANGE;

	/*
	 * Reported LUX value is a combination of the IR and CLEAR channel
	 * values. However, पूर्णांकerrupt threshold is only क्रम clear channel.
	 * This function approximates needed HW threshold value क्रम a given
	 * LUX value in the current lightning type.
	 * IR level compared to visible light varies heavily depending on the
	 * source of the light
	 *
	 * Calculate threshold value क्रम the next measurement period.
	 * Math: threshold = lux * cpl where
	 * cpl = aसमय * again / (glass_attenuation * device_factor)
	 * (count-per-lux)
	 *
	 * First हटाओ calibration. Division by four is to aव्योम overflow
	 */
	lux = lux * (APDS_CALIB_SCALER / 4) / (chip->lux_calib / 4);

	/* Multiplication by 64 is to increase accuracy */
	cpl = ((u32)chip->aसमय * (u32)again[chip->again_next] *
		APDS_PARAM_SCALE * 64) / (chip->cf.ga * chip->cf.df);

	thres = lux * cpl / 64;
	/*
	 * Convert IR light from the latest result to match with
	 * new gain step. This helps to adapt with the current
	 * source of light.
	 */
	ir = (u32)chip->lux_ir * (u32)again[chip->again_next] /
		(u32)again[chip->again_meas];

	/*
	 * Compensate count with IR light impact
	 * IAC1 > IAC2 (see apds990x_get_lux क्रम क्रमmulas)
	 */
	अगर (chip->lux_clear * APDS_PARAM_SCALE >=
		chip->rcf.afactor * chip->lux_ir)
		thres = (chip->rcf.cf1 * thres + chip->rcf.irf1 * ir) /
			APDS_PARAM_SCALE;
	अन्यथा
		thres = (chip->rcf.cf2 * thres + chip->rcf.irf2 * ir) /
			APDS_PARAM_SCALE;

	अगर (thres >= chip->a_max_result)
		thres = chip->a_max_result - 1;
	वापस thres;
पूर्ण

अटल अंतरभूत पूर्णांक apds990x_set_aसमय(काष्ठा apds990x_chip *chip, u32 समय_ms)
अणु
	u8 reg_value;

	chip->aसमय = समय_ms;
	/* Formula is specअगरied in the data sheet */
	reg_value = 256 - ((समय_ms * TIME_STEP_SCALER) / TIMESTEP);
	/* Calculate max ADC value क्रम given पूर्णांकegration समय */
	chip->a_max_result = (u16)(256 - reg_value) * APDS990X_TIME_TO_ADC;
	वापस apds990x_ग_लिखो_byte(chip, APDS990X_ATIME, reg_value);
पूर्ण

/* Called always with mutex locked */
अटल पूर्णांक apds990x_refresh_pthres(काष्ठा apds990x_chip *chip, पूर्णांक data)
अणु
	पूर्णांक ret, lo, hi;

	/* If the chip is not in use, करोn't try to access it */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	अगर (data < chip->prox_thres) अणु
		lo = 0;
		hi = chip->prox_thres;
	पूर्ण अन्यथा अणु
		lo = chip->prox_thres - APDS_PROX_HYSTERESIS;
		अगर (chip->prox_continuous_mode)
			hi = chip->prox_thres;
		अन्यथा
			hi = APDS_RANGE;
	पूर्ण

	ret = apds990x_ग_लिखो_word(chip, APDS990X_PILTL, lo);
	ret |= apds990x_ग_लिखो_word(chip, APDS990X_PIHTL, hi);
	वापस ret;
पूर्ण

/* Called always with mutex locked */
अटल पूर्णांक apds990x_refresh_athres(काष्ठा apds990x_chip *chip)
अणु
	पूर्णांक ret;
	/* If the chip is not in use, करोn't try to access it */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	ret = apds990x_ग_लिखो_word(chip, APDS990X_AILTL,
			apds990x_lux_to_threshold(chip, chip->lux_thres_lo));
	ret |= apds990x_ग_लिखो_word(chip, APDS990X_AIHTL,
			apds990x_lux_to_threshold(chip, chip->lux_thres_hi));

	वापस ret;
पूर्ण

/* Called always with mutex locked */
अटल व्योम apds990x_क्रमce_a_refresh(काष्ठा apds990x_chip *chip)
अणु
	/* This will क्रमce ALS पूर्णांकerrupt after the next measurement. */
	apds990x_ग_लिखो_word(chip, APDS990X_AILTL, APDS_LUX_DEF_THRES_LO);
	apds990x_ग_लिखो_word(chip, APDS990X_AIHTL, APDS_LUX_DEF_THRES_HI);
पूर्ण

/* Called always with mutex locked */
अटल व्योम apds990x_क्रमce_p_refresh(काष्ठा apds990x_chip *chip)
अणु
	/* This will क्रमce proximity पूर्णांकerrupt after the next measurement. */
	apds990x_ग_लिखो_word(chip, APDS990X_PILTL, APDS_PROX_DEF_THRES - 1);
	apds990x_ग_लिखो_word(chip, APDS990X_PIHTL, APDS_PROX_DEF_THRES);
पूर्ण

/* Called always with mutex locked */
अटल पूर्णांक apds990x_calc_again(काष्ठा apds990x_chip *chip)
अणु
	पूर्णांक curr_again = chip->again_meas;
	पूर्णांक next_again = chip->again_meas;
	पूर्णांक ret = 0;

	/* Calculate suitable als gain */
	अगर (chip->lux_clear == chip->a_max_result)
		next_again -= 2; /* ALS saturated. Decrease gain by 2 steps */
	अन्यथा अगर (chip->lux_clear > chip->a_max_result / 2)
		next_again--;
	अन्यथा अगर (chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT_STRICT)
		next_again += 2; /* Too dark. Increase gain by 2 steps */
	अन्यथा अगर (chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT)
		next_again++;

	/* Limit gain to available range */
	अगर (next_again < 0)
		next_again = 0;
	अन्यथा अगर (next_again > APDS990X_MAX_AGAIN)
		next_again = APDS990X_MAX_AGAIN;

	/* Let's check can we trust the measured result */
	अगर (chip->lux_clear == chip->a_max_result)
		/* Result can be totally garbage due to saturation */
		ret = -दुस्फल;
	अन्यथा अगर (next_again != curr_again &&
		chip->lux_clear < APDS_LUX_GAIN_LO_LIMIT_STRICT)
		/*
		 * Gain is changed and measurement result is very small.
		 * Result can be totally garbage due to underflow
		 */
		ret = -दुस्फल;

	chip->again_next = next_again;
	apds990x_ग_लिखो_byte(chip, APDS990X_CONTROL,
			(chip->pdrive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));

	/*
	 * Error means bad result -> re-measurement is needed. The क्रमced
	 * refresh uses fastest possible persistence setting to get result
	 * as soon as possible.
	 */
	अगर (ret < 0)
		apds990x_क्रमce_a_refresh(chip);
	अन्यथा
		apds990x_refresh_athres(chip);

	वापस ret;
पूर्ण

/* Called always with mutex locked */
अटल पूर्णांक apds990x_get_lux(काष्ठा apds990x_chip *chip, पूर्णांक clear, पूर्णांक ir)
अणु
	पूर्णांक iac, iac1, iac2; /* IR adjusted counts */
	u32 lpc; /* Lux per count */

	/* Formulas:
	 * iac1 = CF1 * CLEAR_CH - IRF1 * IR_CH
	 * iac2 = CF2 * CLEAR_CH - IRF2 * IR_CH
	 */
	iac1 = (chip->cf.cf1 * clear - chip->cf.irf1 * ir) / APDS_PARAM_SCALE;
	iac2 = (chip->cf.cf2 * clear - chip->cf.irf2 * ir) / APDS_PARAM_SCALE;

	iac = max(iac1, iac2);
	iac = max(iac, 0);

	lpc = APDS990X_LUX_OUTPUT_SCALE * (chip->cf.df * chip->cf.ga) /
		(u32)(again[chip->again_meas] * (u32)chip->aसमय);

	वापस (iac * lpc) / APDS_PARAM_SCALE;
पूर्ण

अटल पूर्णांक apds990x_ack_पूर्णांक(काष्ठा apds990x_chip *chip, u8 mode)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;
	u8 reg = APDS990x_CMD | APDS990x_CMD_TYPE_SPE;

	चयन (mode & (APDS990X_ST_AINT | APDS990X_ST_PINT)) अणु
	हाल APDS990X_ST_AINT:
		reg |= APDS990X_INT_ACK_ALS;
		अवरोध;
	हाल APDS990X_ST_PINT:
		reg |= APDS990X_INT_ACK_PS;
		अवरोध;
	शेष:
		reg |= APDS990X_INT_ACK_BOTH;
		अवरोध;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	वापस (पूर्णांक)ret;
पूर्ण

अटल irqवापस_t apds990x_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा apds990x_chip *chip = data;
	u8 status;

	apds990x_पढ़ो_byte(chip, APDS990X_STATUS, &status);
	apds990x_ack_पूर्णांक(chip, status);

	mutex_lock(&chip->mutex);
	अगर (!pm_runसमय_suspended(&chip->client->dev)) अणु
		अगर (status & APDS990X_ST_AINT) अणु
			apds990x_पढ़ो_word(chip, APDS990X_CDATAL,
					&chip->lux_clear);
			apds990x_पढ़ो_word(chip, APDS990X_IRDATAL,
					&chip->lux_ir);
			/* Store used gain क्रम calculations */
			chip->again_meas = chip->again_next;

			chip->lux_raw = apds990x_get_lux(chip,
							chip->lux_clear,
							chip->lux_ir);

			अगर (apds990x_calc_again(chip) == 0) अणु
				/* Result is valid */
				chip->lux = chip->lux_raw;
				chip->lux_रुको_fresh_res = false;
				wake_up(&chip->रुको);
				sysfs_notअगरy(&chip->client->dev.kobj,
					शून्य, "lux0_input");
			पूर्ण
		पूर्ण

		अगर ((status & APDS990X_ST_PINT) && chip->prox_en) अणु
			u16 clr_ch;

			apds990x_पढ़ो_word(chip, APDS990X_CDATAL, &clr_ch);
			/*
			 * If ALS channel is saturated at min gain,
			 * proximity gives false posivite values.
			 * Just ignore them.
			 */
			अगर (chip->again_meas == 0 &&
				clr_ch == chip->a_max_result)
				chip->prox_data = 0;
			अन्यथा
				apds990x_पढ़ो_word(chip,
						APDS990X_PDATAL,
						&chip->prox_data);

			apds990x_refresh_pthres(chip, chip->prox_data);
			अगर (chip->prox_data < chip->prox_thres)
				chip->prox_data = 0;
			अन्यथा अगर (!chip->prox_continuous_mode)
				chip->prox_data = APDS_PROX_RANGE;
			sysfs_notअगरy(&chip->client->dev.kobj,
				शून्य, "prox0_raw");
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apds990x_configure(काष्ठा apds990x_chip *chip)
अणु
	/* It is recommended to use disabled mode during these operations */
	apds990x_ग_लिखो_byte(chip, APDS990X_ENABLE, APDS990X_EN_DISABLE_ALL);

	/* conversion and रुको बार क्रम dअगरferent state machince states */
	apds990x_ग_लिखो_byte(chip, APDS990X_PTIME, APDS990X_PTIME_DEFAULT);
	apds990x_ग_लिखो_byte(chip, APDS990X_WTIME, APDS990X_WTIME_DEFAULT);
	apds990x_set_aसमय(chip, APDS_LUX_AVERAGING_TIME);

	apds990x_ग_लिखो_byte(chip, APDS990X_CONFIG, 0);

	/* Persistence levels */
	apds990x_ग_लिखो_byte(chip, APDS990X_PERS,
			(chip->lux_persistence << APDS990X_APERS_SHIFT) |
			(chip->prox_persistence << APDS990X_PPERS_SHIFT));

	apds990x_ग_लिखो_byte(chip, APDS990X_PPCOUNT, chip->pdata->ppcount);

	/* Start with relatively small gain */
	chip->again_meas = 1;
	chip->again_next = 1;
	apds990x_ग_लिखो_byte(chip, APDS990X_CONTROL,
			(chip->pdrive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));
	वापस 0;
पूर्ण

अटल पूर्णांक apds990x_detect(काष्ठा apds990x_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret;
	u8 id;

	ret = apds990x_पढ़ो_byte(chip, APDS990X_ID, &id);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "ID read failed\n");
		वापस ret;
	पूर्ण

	ret = apds990x_पढ़ो_byte(chip, APDS990X_REV, &chip->revision);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "REV read failed\n");
		वापस ret;
	पूर्ण

	चयन (id) अणु
	हाल APDS990X_ID_0:
	हाल APDS990X_ID_4:
	हाल APDS990X_ID_29:
		snम_लिखो(chip->chipname, माप(chip->chipname), "APDS-990x");
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक apds990x_chip_on(काष्ठा apds990x_chip *chip)
अणु
	पूर्णांक err	 = regulator_bulk_enable(ARRAY_SIZE(chip->regs),
					chip->regs);
	अगर (err < 0)
		वापस err;

	usleep_range(APDS_STARTUP_DELAY, 2 * APDS_STARTUP_DELAY);

	/* Refresh all configs in हाल of regulators were off */
	chip->prox_data = 0;
	apds990x_configure(chip);
	apds990x_mode_on(chip);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक apds990x_chip_off(काष्ठा apds990x_chip *chip)
अणु
	apds990x_ग_लिखो_byte(chip, APDS990X_ENABLE, APDS990X_EN_DISABLE_ALL);
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार apds990x_lux_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip = dev_get_drvdata(dev);
	sमाप_प्रकार ret;
	u32 result;
	दीर्घ समयout;

	अगर (pm_runसमय_suspended(dev))
		वापस -EIO;

	समयout = रुको_event_पूर्णांकerruptible_समयout(chip->रुको,
						!chip->lux_रुको_fresh_res,
						msecs_to_jअगरfies(APDS_TIMEOUT));
	अगर (!समयout)
		वापस -EIO;

	mutex_lock(&chip->mutex);
	result = (chip->lux * chip->lux_calib) / APDS_CALIB_SCALER;
	अगर (result > (APDS_RANGE * APDS990X_LUX_OUTPUT_SCALE))
		result = APDS_RANGE * APDS990X_LUX_OUTPUT_SCALE;

	ret = प्र_लिखो(buf, "%d.%d\n",
		result / APDS990X_LUX_OUTPUT_SCALE,
		result % APDS990X_LUX_OUTPUT_SCALE);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(lux0_input, S_IRUGO, apds990x_lux_show, शून्य);

अटल sमाप_प्रकार apds990x_lux_range_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", APDS_RANGE);
पूर्ण

अटल DEVICE_ATTR(lux0_sensor_range, S_IRUGO, apds990x_lux_range_show, शून्य);

अटल sमाप_प्रकार apds990x_lux_calib_क्रमmat_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", APDS_CALIB_SCALER);
पूर्ण

अटल DEVICE_ATTR(lux0_calibscale_शेष, S_IRUGO,
		apds990x_lux_calib_क्रमmat_show, शून्य);

अटल sमाप_प्रकार apds990x_lux_calib_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", chip->lux_calib);
पूर्ण

अटल sमाप_प्रकार apds990x_lux_calib_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	chip->lux_calib = value;

	वापस len;
पूर्ण

अटल DEVICE_ATTR(lux0_calibscale, S_IRUGO | S_IWUSR, apds990x_lux_calib_show,
		apds990x_lux_calib_store);

अटल sमाप_प्रकार apds990x_rate_avail(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	पूर्णांक pos = 0;

	क्रम (i = 0; i < ARRAY_SIZE(arates_hz); i++)
		pos += प्र_लिखो(buf + pos, "%d ", arates_hz[i]);
	प्र_लिखो(buf + pos - 1, "\n");
	वापस pos;
पूर्ण

अटल sमाप_प्रकार apds990x_rate_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->arate);
पूर्ण

अटल पूर्णांक apds990x_set_arate(काष्ठा apds990x_chip *chip, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(arates_hz); i++)
		अगर (rate >= arates_hz[i])
			अवरोध;

	अगर (i == ARRAY_SIZE(arates_hz))
		वापस -EINVAL;

	/* Pick up corresponding persistence value */
	chip->lux_persistence = apersis[i];
	chip->arate = arates_hz[i];

	/* If the chip is not in use, करोn't try to access it */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	/* Persistence levels */
	वापस apds990x_ग_लिखो_byte(chip, APDS990X_PERS,
			(chip->lux_persistence << APDS990X_APERS_SHIFT) |
			(chip->prox_persistence << APDS990X_PPERS_SHIFT));
पूर्ण

अटल sमाप_प्रकार apds990x_rate_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	ret = apds990x_set_arate(chip, value);
	mutex_unlock(&chip->mutex);

	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल DEVICE_ATTR(lux0_rate_avail, S_IRUGO, apds990x_rate_avail, शून्य);

अटल DEVICE_ATTR(lux0_rate, S_IRUGO | S_IWUSR, apds990x_rate_show,
						 apds990x_rate_store);

अटल sमाप_प्रकार apds990x_prox_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	अगर (pm_runसमय_suspended(dev) || !chip->prox_en)
		वापस -EIO;

	mutex_lock(&chip->mutex);
	ret = प्र_लिखो(buf, "%d\n", chip->prox_data);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(prox0_raw, S_IRUGO, apds990x_prox_show, शून्य);

अटल sमाप_प्रकार apds990x_prox_range_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", APDS_PROX_RANGE);
पूर्ण

अटल DEVICE_ATTR(prox0_sensor_range, S_IRUGO, apds990x_prox_range_show, शून्य);

अटल sमाप_प्रकार apds990x_prox_enable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->prox_en);
पूर्ण

अटल sमाप_प्रकार apds990x_prox_enable_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);

	अगर (!chip->prox_en)
		chip->prox_data = 0;

	अगर (value)
		chip->prox_en++;
	अन्यथा अगर (chip->prox_en > 0)
		chip->prox_en--;

	अगर (!pm_runसमय_suspended(dev))
		apds990x_mode_on(chip);
	mutex_unlock(&chip->mutex);
	वापस len;
पूर्ण

अटल DEVICE_ATTR(prox0_raw_en, S_IRUGO | S_IWUSR, apds990x_prox_enable_show,
						   apds990x_prox_enable_store);

अटल स्थिर अक्षर *reporting_modes[] = अणु"trigger", "periodic"पूर्ण;

अटल sमाप_प्रकार apds990x_prox_reporting_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n",
		reporting_modes[!!chip->prox_continuous_mode]);
पूर्ण

अटल sमाप_प्रकार apds990x_prox_reporting_mode_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sysfs_match_string(reporting_modes, buf);
	अगर (ret < 0)
		वापस ret;

	chip->prox_continuous_mode = ret;
	वापस len;
पूर्ण

अटल DEVICE_ATTR(prox0_reporting_mode, S_IRUGO | S_IWUSR,
		apds990x_prox_reporting_mode_show,
		apds990x_prox_reporting_mode_store);

अटल sमाप_प्रकार apds990x_prox_reporting_avail_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s %s\n", reporting_modes[0], reporting_modes[1]);
पूर्ण

अटल DEVICE_ATTR(prox0_reporting_mode_avail, S_IRUGO | S_IWUSR,
		apds990x_prox_reporting_avail_show, शून्य);


अटल sमाप_प्रकार apds990x_lux_thresh_above_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->lux_thres_hi);
पूर्ण

अटल sमाप_प्रकार apds990x_lux_thresh_below_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->lux_thres_lo);
पूर्ण

अटल sमाप_प्रकार apds990x_set_lux_thresh(काष्ठा apds990x_chip *chip, u32 *target,
				स्थिर अक्षर *buf)
अणु
	अचिन्हित दीर्घ thresh;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &thresh);
	अगर (ret)
		वापस ret;

	अगर (thresh > APDS_RANGE)
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	*target = thresh;
	/*
	 * Don't update values in HW अगर we are still रुकोing क्रम
	 * first पूर्णांकerrupt to come after device handle खोलो call.
	 */
	अगर (!chip->lux_रुको_fresh_res)
		apds990x_refresh_athres(chip);
	mutex_unlock(&chip->mutex);
	वापस ret;

पूर्ण

अटल sमाप_प्रकार apds990x_lux_thresh_above_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	पूर्णांक ret = apds990x_set_lux_thresh(chip, &chip->lux_thres_hi, buf);

	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल sमाप_प्रकार apds990x_lux_thresh_below_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	पूर्णांक ret = apds990x_set_lux_thresh(chip, &chip->lux_thres_lo, buf);

	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल DEVICE_ATTR(lux0_thresh_above_value, S_IRUGO | S_IWUSR,
		apds990x_lux_thresh_above_show,
		apds990x_lux_thresh_above_store);

अटल DEVICE_ATTR(lux0_thresh_below_value, S_IRUGO | S_IWUSR,
		apds990x_lux_thresh_below_show,
		apds990x_lux_thresh_below_store);

अटल sमाप_प्रकार apds990x_prox_threshold_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->prox_thres);
पूर्ण

अटल sमाप_प्रकार apds990x_prox_threshold_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर ((value > APDS_RANGE) || (value == 0) ||
		(value < APDS_PROX_HYSTERESIS))
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	chip->prox_thres = value;

	apds990x_क्रमce_p_refresh(chip);
	mutex_unlock(&chip->mutex);
	वापस len;
पूर्ण

अटल DEVICE_ATTR(prox0_thresh_above_value, S_IRUGO | S_IWUSR,
		apds990x_prox_threshold_show,
		apds990x_prox_threshold_store);

अटल sमाप_प्रकार apds990x_घातer_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", !pm_runसमय_suspended(dev));
	वापस 0;
पूर्ण

अटल sमाप_प्रकार apds990x_घातer_state_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value) अणु
		pm_runसमय_get_sync(dev);
		mutex_lock(&chip->mutex);
		chip->lux_रुको_fresh_res = true;
		apds990x_क्रमce_a_refresh(chip);
		apds990x_क्रमce_p_refresh(chip);
		mutex_unlock(&chip->mutex);
	पूर्ण अन्यथा अणु
		अगर (!pm_runसमय_suspended(dev))
			pm_runसमय_put(dev);
	पूर्ण
	वापस len;
पूर्ण

अटल DEVICE_ATTR(घातer_state, S_IRUGO | S_IWUSR,
		apds990x_घातer_state_show,
		apds990x_घातer_state_store);

अटल sमाप_प्रकार apds990x_chip_id_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा apds990x_chip *chip =  dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s %d\n", chip->chipname, chip->revision);
पूर्ण

अटल DEVICE_ATTR(chip_id, S_IRUGO, apds990x_chip_id_show, शून्य);

अटल काष्ठा attribute *sysfs_attrs_ctrl[] = अणु
	&dev_attr_lux0_calibscale.attr,
	&dev_attr_lux0_calibscale_शेष.attr,
	&dev_attr_lux0_input.attr,
	&dev_attr_lux0_sensor_range.attr,
	&dev_attr_lux0_rate.attr,
	&dev_attr_lux0_rate_avail.attr,
	&dev_attr_lux0_thresh_above_value.attr,
	&dev_attr_lux0_thresh_below_value.attr,
	&dev_attr_prox0_raw_en.attr,
	&dev_attr_prox0_raw.attr,
	&dev_attr_prox0_sensor_range.attr,
	&dev_attr_prox0_thresh_above_value.attr,
	&dev_attr_prox0_reporting_mode.attr,
	&dev_attr_prox0_reporting_mode_avail.attr,
	&dev_attr_chip_id.attr,
	&dev_attr_घातer_state.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group apds990x_attribute_group[] = अणु
	अणु.attrs = sysfs_attrs_ctrl पूर्ण,
पूर्ण;

अटल पूर्णांक apds990x_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा apds990x_chip *chip;
	पूर्णांक err;

	chip = kzalloc(माप *chip, GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->client  = client;

	init_रुकोqueue_head(&chip->रुको);
	mutex_init(&chip->mutex);
	chip->pdata	= client->dev.platक्रमm_data;

	अगर (chip->pdata == शून्य) अणु
		dev_err(&client->dev, "platform data is mandatory\n");
		err = -EINVAL;
		जाओ fail1;
	पूर्ण

	अगर (chip->pdata->cf.ga == 0) अणु
		/* set uncovered sensor शेष parameters */
		chip->cf.ga = 1966; /* 0.48 * APDS_PARAM_SCALE */
		chip->cf.cf1 = 4096; /* 1.00 * APDS_PARAM_SCALE */
		chip->cf.irf1 = 9134; /* 2.23 * APDS_PARAM_SCALE */
		chip->cf.cf2 = 2867; /* 0.70 * APDS_PARAM_SCALE */
		chip->cf.irf2 = 5816; /* 1.42 * APDS_PARAM_SCALE */
		chip->cf.df = 52;
	पूर्ण अन्यथा अणु
		chip->cf = chip->pdata->cf;
	पूर्ण

	/* precalculate inverse chip factors क्रम threshold control */
	chip->rcf.afactor =
		(chip->cf.irf1 - chip->cf.irf2) * APDS_PARAM_SCALE /
		(chip->cf.cf1 - chip->cf.cf2);
	chip->rcf.cf1 = APDS_PARAM_SCALE * APDS_PARAM_SCALE /
		chip->cf.cf1;
	chip->rcf.irf1 = chip->cf.irf1 * APDS_PARAM_SCALE /
		chip->cf.cf1;
	chip->rcf.cf2 = APDS_PARAM_SCALE * APDS_PARAM_SCALE /
		chip->cf.cf2;
	chip->rcf.irf2 = chip->cf.irf2 * APDS_PARAM_SCALE /
		chip->cf.cf2;

	/* Set something to start with */
	chip->lux_thres_hi = APDS_LUX_DEF_THRES_HI;
	chip->lux_thres_lo = APDS_LUX_DEF_THRES_LO;
	chip->lux_calib = APDS_LUX_NEUTRAL_CALIB_VALUE;

	chip->prox_thres = APDS_PROX_DEF_THRES;
	chip->pdrive = chip->pdata->pdrive;
	chip->pdiode = APDS_PDIODE_IR;
	chip->pgain = APDS_PGAIN_1X;
	chip->prox_calib = APDS_PROX_NEUTRAL_CALIB_VALUE;
	chip->prox_persistence = APDS_DEFAULT_PROX_PERS;
	chip->prox_continuous_mode = false;

	chip->regs[0].supply = reg_vcc;
	chip->regs[1].supply = reg_vled;

	err = regulator_bulk_get(&client->dev,
				 ARRAY_SIZE(chip->regs), chip->regs);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Cannot get regulators\n");
		जाओ fail1;
	पूर्ण

	err = regulator_bulk_enable(ARRAY_SIZE(chip->regs), chip->regs);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Cannot enable regulators\n");
		जाओ fail2;
	पूर्ण

	usleep_range(APDS_STARTUP_DELAY, 2 * APDS_STARTUP_DELAY);

	err = apds990x_detect(chip);
	अगर (err < 0) अणु
		dev_err(&client->dev, "APDS990X not found\n");
		जाओ fail3;
	पूर्ण

	pm_runसमय_set_active(&client->dev);

	apds990x_configure(chip);
	apds990x_set_arate(chip, APDS_LUX_DEFAULT_RATE);
	apds990x_mode_on(chip);

	pm_runसमय_enable(&client->dev);

	अगर (chip->pdata->setup_resources) अणु
		err = chip->pdata->setup_resources();
		अगर (err) अणु
			err = -EINVAL;
			जाओ fail3;
		पूर्ण
	पूर्ण

	err = sysfs_create_group(&chip->client->dev.kobj,
				apds990x_attribute_group);
	अगर (err < 0) अणु
		dev_err(&chip->client->dev, "Sysfs registration failed\n");
		जाओ fail4;
	पूर्ण

	err = request_thपढ़ोed_irq(client->irq, शून्य,
				apds990x_irq,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_LOW |
				IRQF_ONESHOT,
				"apds990x", chip);
	अगर (err) अणु
		dev_err(&client->dev, "could not get IRQ %d\n",
			client->irq);
		जाओ fail5;
	पूर्ण
	वापस err;
fail5:
	sysfs_हटाओ_group(&chip->client->dev.kobj,
			&apds990x_attribute_group[0]);
fail4:
	अगर (chip->pdata && chip->pdata->release_resources)
		chip->pdata->release_resources();
fail3:
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
fail2:
	regulator_bulk_मुक्त(ARRAY_SIZE(chip->regs), chip->regs);
fail1:
	kमुक्त(chip);
	वापस err;
पूर्ण

अटल पूर्णांक apds990x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा apds990x_chip *chip = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, chip);
	sysfs_हटाओ_group(&chip->client->dev.kobj,
			apds990x_attribute_group);

	अगर (chip->pdata && chip->pdata->release_resources)
		chip->pdata->release_resources();

	अगर (!pm_runसमय_suspended(&client->dev))
		apds990x_chip_off(chip);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	regulator_bulk_मुक्त(ARRAY_SIZE(chip->regs), chip->regs);

	kमुक्त(chip);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक apds990x_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा apds990x_chip *chip = i2c_get_clientdata(client);

	apds990x_chip_off(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक apds990x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा apds990x_chip *chip = i2c_get_clientdata(client);

	/*
	 * If we were enabled at suspend समय, it is expected
	 * everything works nice and smoothly. Chip_on is enough
	 */
	apds990x_chip_on(chip);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक apds990x_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा apds990x_chip *chip = i2c_get_clientdata(client);

	apds990x_chip_off(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक apds990x_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा apds990x_chip *chip = i2c_get_clientdata(client);

	apds990x_chip_on(chip);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id apds990x_id[] = अणु
	अणु"apds990x", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, apds990x_id);

अटल स्थिर काष्ठा dev_pm_ops apds990x_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(apds990x_suspend, apds990x_resume)
	SET_RUNTIME_PM_OPS(apds990x_runसमय_suspend,
			apds990x_runसमय_resume,
			शून्य)
पूर्ण;

अटल काष्ठा i2c_driver apds990x_driver = अणु
	.driver	 = अणु
		.name	= "apds990x",
		.pm	= &apds990x_pm_ops,
	पूर्ण,
	.probe	  = apds990x_probe,
	.हटाओ	  = apds990x_हटाओ,
	.id_table = apds990x_id,
पूर्ण;

module_i2c_driver(apds990x_driver);

MODULE_DESCRIPTION("APDS990X combined ALS and proximity sensor");
MODULE_AUTHOR("Samu Onkalo, Nokia Corporation");
MODULE_LICENSE("GPL v2");
