<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2014-2018 Nuvoton Technology corporation.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>

/* NPCM7XX PWM रेजिस्टरs */
#घोषणा NPCM7XX_PWM_REG_BASE(base, n)    ((base) + ((n) * 0x1000L))

#घोषणा NPCM7XX_PWM_REG_PR(base, n)	(NPCM7XX_PWM_REG_BASE(base, n) + 0x00)
#घोषणा NPCM7XX_PWM_REG_CSR(base, n)	(NPCM7XX_PWM_REG_BASE(base, n) + 0x04)
#घोषणा NPCM7XX_PWM_REG_CR(base, n)	(NPCM7XX_PWM_REG_BASE(base, n) + 0x08)
#घोषणा NPCM7XX_PWM_REG_CNRx(base, n, ch) \
			(NPCM7XX_PWM_REG_BASE(base, n) + 0x0C + (12 * (ch)))
#घोषणा NPCM7XX_PWM_REG_CMRx(base, n, ch) \
			(NPCM7XX_PWM_REG_BASE(base, n) + 0x10 + (12 * (ch)))
#घोषणा NPCM7XX_PWM_REG_PDRx(base, n, ch) \
			(NPCM7XX_PWM_REG_BASE(base, n) + 0x14 + (12 * (ch)))
#घोषणा NPCM7XX_PWM_REG_PIER(base, n)	(NPCM7XX_PWM_REG_BASE(base, n) + 0x3C)
#घोषणा NPCM7XX_PWM_REG_PIIR(base, n)	(NPCM7XX_PWM_REG_BASE(base, n) + 0x40)

#घोषणा NPCM7XX_PWM_CTRL_CH0_MODE_BIT		BIT(3)
#घोषणा NPCM7XX_PWM_CTRL_CH1_MODE_BIT		BIT(11)
#घोषणा NPCM7XX_PWM_CTRL_CH2_MODE_BIT		BIT(15)
#घोषणा NPCM7XX_PWM_CTRL_CH3_MODE_BIT		BIT(19)

#घोषणा NPCM7XX_PWM_CTRL_CH0_INV_BIT		BIT(2)
#घोषणा NPCM7XX_PWM_CTRL_CH1_INV_BIT		BIT(10)
#घोषणा NPCM7XX_PWM_CTRL_CH2_INV_BIT		BIT(14)
#घोषणा NPCM7XX_PWM_CTRL_CH3_INV_BIT		BIT(18)

#घोषणा NPCM7XX_PWM_CTRL_CH0_EN_BIT		BIT(0)
#घोषणा NPCM7XX_PWM_CTRL_CH1_EN_BIT		BIT(8)
#घोषणा NPCM7XX_PWM_CTRL_CH2_EN_BIT		BIT(12)
#घोषणा NPCM7XX_PWM_CTRL_CH3_EN_BIT		BIT(16)

/* Define the maximum PWM channel number */
#घोषणा NPCM7XX_PWM_MAX_CHN_NUM			8
#घोषणा NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE	4
#घोषणा NPCM7XX_PWM_MAX_MODULES                 2

/* Define the Counter Register, value = 100 क्रम match 100% */
#घोषणा NPCM7XX_PWM_COUNTER_DEFAULT_NUM		255
#घोषणा NPCM7XX_PWM_CMR_DEFAULT_NUM		255
#घोषणा NPCM7XX_PWM_CMR_MAX			255

/* शेष all PWM channels PRESCALE2 = 1 */
#घोषणा NPCM7XX_PWM_PRESCALE2_DEFAULT_CH0	0x4
#घोषणा NPCM7XX_PWM_PRESCALE2_DEFAULT_CH1	0x40
#घोषणा NPCM7XX_PWM_PRESCALE2_DEFAULT_CH2	0x400
#घोषणा NPCM7XX_PWM_PRESCALE2_DEFAULT_CH3	0x4000

#घोषणा PWM_OUTPUT_FREQ_25KHZ			25000
#घोषणा PWN_CNT_DEFAULT				256
#घोषणा MIN_PRESCALE1				2
#घोषणा NPCM7XX_PWM_PRESCALE_SHIFT_CH01		8

#घोषणा NPCM7XX_PWM_PRESCALE2_DEFAULT	(NPCM7XX_PWM_PRESCALE2_DEFAULT_CH0 | \
					NPCM7XX_PWM_PRESCALE2_DEFAULT_CH1 | \
					NPCM7XX_PWM_PRESCALE2_DEFAULT_CH2 | \
					NPCM7XX_PWM_PRESCALE2_DEFAULT_CH3)

#घोषणा NPCM7XX_PWM_CTRL_MODE_DEFAULT	(NPCM7XX_PWM_CTRL_CH0_MODE_BIT | \
					NPCM7XX_PWM_CTRL_CH1_MODE_BIT | \
					NPCM7XX_PWM_CTRL_CH2_MODE_BIT | \
					NPCM7XX_PWM_CTRL_CH3_MODE_BIT)

/* NPCM7XX FAN Tacho रेजिस्टरs */
#घोषणा NPCM7XX_FAN_REG_BASE(base, n)	((base) + ((n) * 0x1000L))

#घोषणा NPCM7XX_FAN_REG_TCNT1(base, n)    (NPCM7XX_FAN_REG_BASE(base, n) + 0x00)
#घोषणा NPCM7XX_FAN_REG_TCRA(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x02)
#घोषणा NPCM7XX_FAN_REG_TCRB(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x04)
#घोषणा NPCM7XX_FAN_REG_TCNT2(base, n)    (NPCM7XX_FAN_REG_BASE(base, n) + 0x06)
#घोषणा NPCM7XX_FAN_REG_TPRSC(base, n)    (NPCM7XX_FAN_REG_BASE(base, n) + 0x08)
#घोषणा NPCM7XX_FAN_REG_TCKC(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x0A)
#घोषणा NPCM7XX_FAN_REG_TMCTRL(base, n)   (NPCM7XX_FAN_REG_BASE(base, n) + 0x0C)
#घोषणा NPCM7XX_FAN_REG_TICTRL(base, n)   (NPCM7XX_FAN_REG_BASE(base, n) + 0x0E)
#घोषणा NPCM7XX_FAN_REG_TICLR(base, n)    (NPCM7XX_FAN_REG_BASE(base, n) + 0x10)
#घोषणा NPCM7XX_FAN_REG_TIEN(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x12)
#घोषणा NPCM7XX_FAN_REG_TCPA(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x14)
#घोषणा NPCM7XX_FAN_REG_TCPB(base, n)     (NPCM7XX_FAN_REG_BASE(base, n) + 0x16)
#घोषणा NPCM7XX_FAN_REG_TCPCFG(base, n)   (NPCM7XX_FAN_REG_BASE(base, n) + 0x18)
#घोषणा NPCM7XX_FAN_REG_TINASEL(base, n)  (NPCM7XX_FAN_REG_BASE(base, n) + 0x1A)
#घोषणा NPCM7XX_FAN_REG_TINBSEL(base, n)  (NPCM7XX_FAN_REG_BASE(base, n) + 0x1C)

#घोषणा NPCM7XX_FAN_TCKC_CLKX_NONE	0
#घोषणा NPCM7XX_FAN_TCKC_CLK1_APB	BIT(0)
#घोषणा NPCM7XX_FAN_TCKC_CLK2_APB	BIT(3)

#घोषणा NPCM7XX_FAN_TMCTRL_TBEN		BIT(6)
#घोषणा NPCM7XX_FAN_TMCTRL_TAEN		BIT(5)
#घोषणा NPCM7XX_FAN_TMCTRL_TBEDG	BIT(4)
#घोषणा NPCM7XX_FAN_TMCTRL_TAEDG	BIT(3)
#घोषणा NPCM7XX_FAN_TMCTRL_MODE_5	BIT(2)

#घोषणा NPCM7XX_FAN_TICLR_CLEAR_ALL	GENMASK(5, 0)
#घोषणा NPCM7XX_FAN_TICLR_TFCLR		BIT(5)
#घोषणा NPCM7XX_FAN_TICLR_TECLR		BIT(4)
#घोषणा NPCM7XX_FAN_TICLR_TDCLR		BIT(3)
#घोषणा NPCM7XX_FAN_TICLR_TCCLR		BIT(2)
#घोषणा NPCM7XX_FAN_TICLR_TBCLR		BIT(1)
#घोषणा NPCM7XX_FAN_TICLR_TACLR		BIT(0)

#घोषणा NPCM7XX_FAN_TIEN_ENABLE_ALL	GENMASK(5, 0)
#घोषणा NPCM7XX_FAN_TIEN_TFIEN		BIT(5)
#घोषणा NPCM7XX_FAN_TIEN_TEIEN		BIT(4)
#घोषणा NPCM7XX_FAN_TIEN_TDIEN		BIT(3)
#घोषणा NPCM7XX_FAN_TIEN_TCIEN		BIT(2)
#घोषणा NPCM7XX_FAN_TIEN_TBIEN		BIT(1)
#घोषणा NPCM7XX_FAN_TIEN_TAIEN		BIT(0)

#घोषणा NPCM7XX_FAN_TICTRL_TFPND	BIT(5)
#घोषणा NPCM7XX_FAN_TICTRL_TEPND	BIT(4)
#घोषणा NPCM7XX_FAN_TICTRL_TDPND	BIT(3)
#घोषणा NPCM7XX_FAN_TICTRL_TCPND	BIT(2)
#घोषणा NPCM7XX_FAN_TICTRL_TBPND	BIT(1)
#घोषणा NPCM7XX_FAN_TICTRL_TAPND	BIT(0)

#घोषणा NPCM7XX_FAN_TCPCFG_HIBEN	BIT(7)
#घोषणा NPCM7XX_FAN_TCPCFG_EQBEN	BIT(6)
#घोषणा NPCM7XX_FAN_TCPCFG_LOBEN	BIT(5)
#घोषणा NPCM7XX_FAN_TCPCFG_CPBSEL	BIT(4)
#घोषणा NPCM7XX_FAN_TCPCFG_HIAEN	BIT(3)
#घोषणा NPCM7XX_FAN_TCPCFG_EQAEN	BIT(2)
#घोषणा NPCM7XX_FAN_TCPCFG_LOAEN	BIT(1)
#घोषणा NPCM7XX_FAN_TCPCFG_CPASEL	BIT(0)

/* FAN General Definition */
/* Define the maximum FAN channel number */
#घोषणा NPCM7XX_FAN_MAX_MODULE			8
#घोषणा NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE	2
#घोषणा NPCM7XX_FAN_MAX_CHN_NUM			16

/*
 * Get Fan Tach Timeout (base on घड़ी 214843.75Hz, 1 cnt = 4.654us)
 * Timeout 94ms ~= 0x5000
 * (The minimum FAN speed could to support ~640RPM/pulse 1,
 * 320RPM/pulse 2, ...-- 10.6Hz)
 */
#घोषणा NPCM7XX_FAN_TIMEOUT	0x5000
#घोषणा NPCM7XX_FAN_TCNT	0xFFFF
#घोषणा NPCM7XX_FAN_TCPA	(NPCM7XX_FAN_TCNT - NPCM7XX_FAN_TIMEOUT)
#घोषणा NPCM7XX_FAN_TCPB	(NPCM7XX_FAN_TCNT - NPCM7XX_FAN_TIMEOUT)

#घोषणा NPCM7XX_FAN_POLL_TIMER_200MS			200
#घोषणा NPCM7XX_FAN_DEFAULT_PULSE_PER_REVOLUTION	2
#घोषणा NPCM7XX_FAN_TINASEL_FANIN_DEFAULT		0
#घोषणा NPCM7XX_FAN_CLK_PRESCALE			255

#घोषणा NPCM7XX_FAN_CMPA				0
#घोषणा NPCM7XX_FAN_CMPB				1

/* Obtain the fan number */
#घोषणा NPCM7XX_FAN_INPUT(fan, cmp)		(((fan) << 1) + (cmp))

/* fan sample status */
#घोषणा FAN_DISABLE				0xFF
#घोषणा FAN_INIT				0x00
#घोषणा FAN_PREPARE_TO_GET_FIRST_CAPTURE	0x01
#घोषणा FAN_ENOUGH_SAMPLE			0x02

काष्ठा npcm7xx_fan_dev अणु
	u8 fan_st_flg;
	u8 fan_pls_per_rev;
	u16 fan_cnt;
	u32 fan_cnt_पंचांगp;
पूर्ण;

काष्ठा npcm7xx_cooling_device अणु
	अक्षर name[THERMAL_NAME_LENGTH];
	काष्ठा npcm7xx_pwm_fan_data *data;
	काष्ठा thermal_cooling_device *tcdev;
	पूर्णांक pwm_port;
	u8 *cooling_levels;
	u8 max_state;
	u8 cur_state;
पूर्ण;

काष्ठा npcm7xx_pwm_fan_data अणु
	व्योम __iomem *pwm_base;
	व्योम __iomem *fan_base;
	अचिन्हित दीर्घ pwm_clk_freq;
	अचिन्हित दीर्घ fan_clk_freq;
	काष्ठा clk *pwm_clk;
	काष्ठा clk *fan_clk;
	काष्ठा mutex pwm_lock[NPCM7XX_PWM_MAX_MODULES];
	spinlock_t fan_lock[NPCM7XX_FAN_MAX_MODULE];
	पूर्णांक fan_irq[NPCM7XX_FAN_MAX_MODULE];
	bool pwm_present[NPCM7XX_PWM_MAX_CHN_NUM];
	bool fan_present[NPCM7XX_FAN_MAX_CHN_NUM];
	u32 input_clk_freq;
	काष्ठा समयr_list fan_समयr;
	काष्ठा npcm7xx_fan_dev fan_dev[NPCM7XX_FAN_MAX_CHN_NUM];
	काष्ठा npcm7xx_cooling_device *cdev[NPCM7XX_PWM_MAX_CHN_NUM];
	u8 fan_select;
पूर्ण;

अटल पूर्णांक npcm7xx_pwm_config_set(काष्ठा npcm7xx_pwm_fan_data *data,
				  पूर्णांक channel, u16 val)
अणु
	u32 pwm_ch = (channel % NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);
	u32 module = (channel / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);
	u32 पंचांगp_buf, ctrl_en_bit, env_bit;

	/*
	 * Config PWM Comparator रेजिस्टर क्रम setting duty cycle
	 */
	mutex_lock(&data->pwm_lock[module]);

	/* ग_लिखो new CMR value  */
	ioग_लिखो32(val, NPCM7XX_PWM_REG_CMRx(data->pwm_base, module, pwm_ch));
	पंचांगp_buf = ioपढ़ो32(NPCM7XX_PWM_REG_CR(data->pwm_base, module));

	चयन (pwm_ch) अणु
	हाल 0:
		ctrl_en_bit = NPCM7XX_PWM_CTRL_CH0_EN_BIT;
		env_bit = NPCM7XX_PWM_CTRL_CH0_INV_BIT;
		अवरोध;
	हाल 1:
		ctrl_en_bit = NPCM7XX_PWM_CTRL_CH1_EN_BIT;
		env_bit = NPCM7XX_PWM_CTRL_CH1_INV_BIT;
		अवरोध;
	हाल 2:
		ctrl_en_bit = NPCM7XX_PWM_CTRL_CH2_EN_BIT;
		env_bit = NPCM7XX_PWM_CTRL_CH2_INV_BIT;
		अवरोध;
	हाल 3:
		ctrl_en_bit = NPCM7XX_PWM_CTRL_CH3_EN_BIT;
		env_bit = NPCM7XX_PWM_CTRL_CH3_INV_BIT;
		अवरोध;
	शेष:
		mutex_unlock(&data->pwm_lock[module]);
		वापस -ENODEV;
	पूर्ण

	अगर (val == 0) अणु
		/* Disable PWM */
		पंचांगp_buf &= ~ctrl_en_bit;
		पंचांगp_buf |= env_bit;
	पूर्ण अन्यथा अणु
		/* Enable PWM */
		पंचांगp_buf |= ctrl_en_bit;
		पंचांगp_buf &= ~env_bit;
	पूर्ण

	ioग_लिखो32(पंचांगp_buf, NPCM7XX_PWM_REG_CR(data->pwm_base, module));
	mutex_unlock(&data->pwm_lock[module]);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम npcm7xx_fan_start_capture(काष्ठा npcm7xx_pwm_fan_data *data,
					     u8 fan, u8 cmp)
अणु
	u8 fan_id;
	u8 reg_mode;
	u8 reg_पूर्णांक;
	अचिन्हित दीर्घ flags;

	fan_id = NPCM7XX_FAN_INPUT(fan, cmp);

	/* to check whether any fan tach is enable */
	अगर (data->fan_dev[fan_id].fan_st_flg != FAN_DISABLE) अणु
		/* reset status */
		spin_lock_irqsave(&data->fan_lock[fan], flags);

		data->fan_dev[fan_id].fan_st_flg = FAN_INIT;
		reg_पूर्णांक = ioपढ़ो8(NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

		/*
		 * the पूर्णांकerrupt enable bits करो not need to be cleared beक्रमe
		 * it sets, the पूर्णांकerrupt enable bits are cleared only on reset.
		 * the घड़ी unit control रेजिस्टर is behaving in the same
		 * manner that the पूर्णांकerrupt enable रेजिस्टर behave.
		 */
		अगर (cmp == NPCM7XX_FAN_CMPA) अणु
			/* enable पूर्णांकerrupt */
			ioग_लिखो8(reg_पूर्णांक | (NPCM7XX_FAN_TIEN_TAIEN |
					    NPCM7XX_FAN_TIEN_TEIEN),
				 NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

			reg_mode = NPCM7XX_FAN_TCKC_CLK1_APB
				| ioपढ़ो8(NPCM7XX_FAN_REG_TCKC(data->fan_base,
							       fan));

			/* start to Capture */
			ioग_लिखो8(reg_mode, NPCM7XX_FAN_REG_TCKC(data->fan_base,
								fan));
		पूर्ण अन्यथा अणु
			/* enable पूर्णांकerrupt */
			ioग_लिखो8(reg_पूर्णांक | (NPCM7XX_FAN_TIEN_TBIEN |
					    NPCM7XX_FAN_TIEN_TFIEN),
				 NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

			reg_mode =
				NPCM7XX_FAN_TCKC_CLK2_APB
				| ioपढ़ो8(NPCM7XX_FAN_REG_TCKC(data->fan_base,
							       fan));

			/* start to Capture */
			ioग_लिखो8(reg_mode,
				 NPCM7XX_FAN_REG_TCKC(data->fan_base, fan));
		पूर्ण

		spin_unlock_irqrestore(&data->fan_lock[fan], flags);
	पूर्ण
पूर्ण

/*
 * Enable a background समयr to poll fan tach value, (200ms * 4)
 * to polling all fan
 */
अटल व्योम npcm7xx_fan_polling(काष्ठा समयr_list *t)
अणु
	काष्ठा npcm7xx_pwm_fan_data *data;
	पूर्णांक i;

	data = from_समयr(data, t, fan_समयr);

	/*
	 * Polling two module per one round,
	 * FAN01 & FAN89 / FAN23 & FAN1011 / FAN45 & FAN1213 / FAN67 & FAN1415
	 */
	क्रम (i = data->fan_select; i < NPCM7XX_FAN_MAX_MODULE;
	      i = i + 4) अणु
		/* clear the flag and reset the counter (TCNT) */
		ioग_लिखो8(NPCM7XX_FAN_TICLR_CLEAR_ALL,
			 NPCM7XX_FAN_REG_TICLR(data->fan_base, i));

		अगर (data->fan_present[i * 2]) अणु
			ioग_लिखो16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_REG_TCNT1(data->fan_base, i));
			npcm7xx_fan_start_capture(data, i, NPCM7XX_FAN_CMPA);
		पूर्ण
		अगर (data->fan_present[(i * 2) + 1]) अणु
			ioग_लिखो16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_REG_TCNT2(data->fan_base, i));
			npcm7xx_fan_start_capture(data, i, NPCM7XX_FAN_CMPB);
		पूर्ण
	पूर्ण

	data->fan_select++;
	data->fan_select &= 0x3;

	/* reset the समयr पूर्णांकerval */
	data->fan_समयr.expires = jअगरfies +
		msecs_to_jअगरfies(NPCM7XX_FAN_POLL_TIMER_200MS);
	add_समयr(&data->fan_समयr);
पूर्ण

अटल अंतरभूत व्योम npcm7xx_fan_compute(काष्ठा npcm7xx_pwm_fan_data *data,
				       u8 fan, u8 cmp, u8 fan_id, u8 flag_पूर्णांक,
				       u8 flag_mode, u8 flag_clear)
अणु
	u8  reg_पूर्णांक;
	u8  reg_mode;
	u16 fan_cap;

	अगर (cmp == NPCM7XX_FAN_CMPA)
		fan_cap = ioपढ़ो16(NPCM7XX_FAN_REG_TCRA(data->fan_base, fan));
	अन्यथा
		fan_cap = ioपढ़ो16(NPCM7XX_FAN_REG_TCRB(data->fan_base, fan));

	/* clear capature flag, H/W will स्वतः reset the NPCM7XX_FAN_TCNTx */
	ioग_लिखो8(flag_clear, NPCM7XX_FAN_REG_TICLR(data->fan_base, fan));

	अगर (data->fan_dev[fan_id].fan_st_flg == FAN_INIT) अणु
		/* First capture, drop it */
		data->fan_dev[fan_id].fan_st_flg =
			FAN_PREPARE_TO_GET_FIRST_CAPTURE;

		/* reset counter */
		data->fan_dev[fan_id].fan_cnt_पंचांगp = 0;
	पूर्ण अन्यथा अगर (data->fan_dev[fan_id].fan_st_flg < FAN_ENOUGH_SAMPLE) अणु
		/*
		 * collect the enough sample,
		 * (ex: 2 pulse fan need to get 2 sample)
		 */
		data->fan_dev[fan_id].fan_cnt_पंचांगp +=
			(NPCM7XX_FAN_TCNT - fan_cap);

		data->fan_dev[fan_id].fan_st_flg++;
	पूर्ण अन्यथा अणु
		/* get enough sample or fan disable */
		अगर (data->fan_dev[fan_id].fan_st_flg == FAN_ENOUGH_SAMPLE) अणु
			data->fan_dev[fan_id].fan_cnt_पंचांगp +=
				(NPCM7XX_FAN_TCNT - fan_cap);

			/* compute finial average cnt per pulse */
			data->fan_dev[fan_id].fan_cnt =
				data->fan_dev[fan_id].fan_cnt_पंचांगp /
				FAN_ENOUGH_SAMPLE;

			data->fan_dev[fan_id].fan_st_flg = FAN_INIT;
		पूर्ण

		reg_पूर्णांक =  ioपढ़ो8(NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

		/* disable पूर्णांकerrupt */
		ioग_लिखो8((reg_पूर्णांक & ~flag_पूर्णांक),
			 NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));
		reg_mode =  ioपढ़ो8(NPCM7XX_FAN_REG_TCKC(data->fan_base, fan));

		/* stop capturing */
		ioग_लिखो8((reg_mode & ~flag_mode),
			 NPCM7XX_FAN_REG_TCKC(data->fan_base, fan));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम npcm7xx_check_cmp(काष्ठा npcm7xx_pwm_fan_data *data,
				     u8 fan, u8 cmp, u8 flag)
अणु
	u8 reg_पूर्णांक;
	u8 reg_mode;
	u8 flag_समयout;
	u8 flag_cap;
	u8 flag_clear;
	u8 flag_पूर्णांक;
	u8 flag_mode;
	u8 fan_id;

	fan_id = NPCM7XX_FAN_INPUT(fan, cmp);

	अगर (cmp == NPCM7XX_FAN_CMPA) अणु
		flag_cap = NPCM7XX_FAN_TICTRL_TAPND;
		flag_समयout = NPCM7XX_FAN_TICTRL_TEPND;
		flag_पूर्णांक = NPCM7XX_FAN_TIEN_TAIEN | NPCM7XX_FAN_TIEN_TEIEN;
		flag_mode = NPCM7XX_FAN_TCKC_CLK1_APB;
		flag_clear = NPCM7XX_FAN_TICLR_TACLR | NPCM7XX_FAN_TICLR_TECLR;
	पूर्ण अन्यथा अणु
		flag_cap = NPCM7XX_FAN_TICTRL_TBPND;
		flag_समयout = NPCM7XX_FAN_TICTRL_TFPND;
		flag_पूर्णांक = NPCM7XX_FAN_TIEN_TBIEN | NPCM7XX_FAN_TIEN_TFIEN;
		flag_mode = NPCM7XX_FAN_TCKC_CLK2_APB;
		flag_clear = NPCM7XX_FAN_TICLR_TBCLR | NPCM7XX_FAN_TICLR_TFCLR;
	पूर्ण

	अगर (flag & flag_समयout) अणु
		reg_पूर्णांक =  ioपढ़ो8(NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

		/* disable पूर्णांकerrupt */
		ioग_लिखो8((reg_पूर्णांक & ~flag_पूर्णांक),
			 NPCM7XX_FAN_REG_TIEN(data->fan_base, fan));

		/* clear पूर्णांकerrupt flag */
		ioग_लिखो8(flag_clear,
			 NPCM7XX_FAN_REG_TICLR(data->fan_base, fan));

		reg_mode =  ioपढ़ो8(NPCM7XX_FAN_REG_TCKC(data->fan_base, fan));

		/* stop capturing */
		ioग_लिखो8((reg_mode & ~flag_mode),
			 NPCM7XX_FAN_REG_TCKC(data->fan_base, fan));

		/*
		 *  If समयout occurs (NPCM7XX_FAN_TIMEOUT), the fan करोesn't
		 *  connect or speed is lower than 10.6Hz (320RPM/pulse2).
		 *  In these situation, the RPM output should be zero.
		 */
		data->fan_dev[fan_id].fan_cnt = 0;
	पूर्ण अन्यथा अणु
	    /* input capture is occurred */
		अगर (flag & flag_cap)
			npcm7xx_fan_compute(data, fan, cmp, fan_id, flag_पूर्णांक,
					    flag_mode, flag_clear);
	पूर्ण
पूर्ण

अटल irqवापस_t npcm7xx_fan_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा npcm7xx_pwm_fan_data *data = dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक module;
	u8 flag;

	module = irq - data->fan_irq[0];
	spin_lock_irqsave(&data->fan_lock[module], flags);

	flag = ioपढ़ो8(NPCM7XX_FAN_REG_TICTRL(data->fan_base, module));
	अगर (flag > 0) अणु
		npcm7xx_check_cmp(data, module, NPCM7XX_FAN_CMPA, flag);
		npcm7xx_check_cmp(data, module, NPCM7XX_FAN_CMPB, flag);
		spin_unlock_irqrestore(&data->fan_lock[module], flags);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&data->fan_lock[module], flags);

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक npcm7xx_पढ़ो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ *val)
अणु
	काष्ठा npcm7xx_pwm_fan_data *data = dev_get_drvdata(dev);
	u32 pmw_ch = (channel % NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);
	u32 module = (channel / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE);

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		*val = ioपढ़ो32
			(NPCM7XX_PWM_REG_CMRx(data->pwm_base, module, pmw_ch));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm7xx_ग_लिखो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ val)
अणु
	काष्ठा npcm7xx_pwm_fan_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		अगर (val < 0 || val > NPCM7XX_PWM_CMR_MAX)
			वापस -EINVAL;
		err = npcm7xx_pwm_config_set(data, channel, (u16)val);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल umode_t npcm7xx_pwm_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा npcm7xx_pwm_fan_data *data = _data;

	अगर (!data->pwm_present[channel])
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm7xx_पढ़ो_fan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ *val)
अणु
	काष्ठा npcm7xx_pwm_fan_data *data = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_fan_input:
		*val = 0;
		अगर (data->fan_dev[channel].fan_cnt <= 0)
			वापस data->fan_dev[channel].fan_cnt;

		/* Convert the raw पढ़ोing to RPM */
		अगर (data->fan_dev[channel].fan_cnt > 0 &&
		    data->fan_dev[channel].fan_pls_per_rev > 0)
			*val = ((data->input_clk_freq * 60) /
				(data->fan_dev[channel].fan_cnt *
				 data->fan_dev[channel].fan_pls_per_rev));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t npcm7xx_fan_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा npcm7xx_pwm_fan_data *data = _data;

	अगर (!data->fan_present[channel])
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm7xx_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_pwm:
		वापस npcm7xx_पढ़ो_pwm(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस npcm7xx_पढ़ो_fan(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm7xx_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_pwm:
		वापस npcm7xx_ग_लिखो_pwm(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t npcm7xx_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_pwm:
		वापस npcm7xx_pwm_is_visible(data, attr, channel);
	हाल hwmon_fan:
		वापस npcm7xx_fan_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *npcm7xx_info[] = अणु
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops npcm7xx_hwmon_ops = अणु
	.is_visible = npcm7xx_is_visible,
	.पढ़ो = npcm7xx_पढ़ो,
	.ग_लिखो = npcm7xx_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info npcm7xx_chip_info = अणु
	.ops = &npcm7xx_hwmon_ops,
	.info = npcm7xx_info,
पूर्ण;

अटल u32 npcm7xx_pwm_init(काष्ठा npcm7xx_pwm_fan_data *data)
अणु
	पूर्णांक m, ch;
	u32 prescale_val, output_freq;

	data->pwm_clk_freq = clk_get_rate(data->pwm_clk);

	/* Adjust NPCM7xx PWMs output frequency to ~25Khz */
	output_freq = data->pwm_clk_freq / PWN_CNT_DEFAULT;
	prescale_val = DIV_ROUND_CLOSEST(output_freq, PWM_OUTPUT_FREQ_25KHZ);

	/* If prescale_val = 0, then the prescale output घड़ी is stopped */
	अगर (prescale_val < MIN_PRESCALE1)
		prescale_val = MIN_PRESCALE1;
	/*
	 * prescale_val need to decrement in one because in the PWM Prescale
	 * रेजिस्टर the Prescale value increment by one
	 */
	prescale_val--;

	/* Setting PWM Prescale Register value रेजिस्टर to both modules */
	prescale_val |= (prescale_val << NPCM7XX_PWM_PRESCALE_SHIFT_CH01);

	क्रम (m = 0; m < NPCM7XX_PWM_MAX_MODULES  ; m++) अणु
		ioग_लिखो32(prescale_val, NPCM7XX_PWM_REG_PR(data->pwm_base, m));
		ioग_लिखो32(NPCM7XX_PWM_PRESCALE2_DEFAULT,
			  NPCM7XX_PWM_REG_CSR(data->pwm_base, m));
		ioग_लिखो32(NPCM7XX_PWM_CTRL_MODE_DEFAULT,
			  NPCM7XX_PWM_REG_CR(data->pwm_base, m));

		क्रम (ch = 0; ch < NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODULE; ch++) अणु
			ioग_लिखो32(NPCM7XX_PWM_COUNTER_DEFAULT_NUM,
				  NPCM7XX_PWM_REG_CNRx(data->pwm_base, m, ch));
		पूर्ण
	पूर्ण

	वापस output_freq / ((prescale_val & 0xf) + 1);
पूर्ण

अटल व्योम npcm7xx_fan_init(काष्ठा npcm7xx_pwm_fan_data *data)
अणु
	पूर्णांक md;
	पूर्णांक ch;
	पूर्णांक i;
	u32 apb_clk_freq;

	क्रम (md = 0; md < NPCM7XX_FAN_MAX_MODULE; md++) अणु
		/* stop FAN0~7 घड़ी */
		ioग_लिखो8(NPCM7XX_FAN_TCKC_CLKX_NONE,
			 NPCM7XX_FAN_REG_TCKC(data->fan_base, md));

		/* disable all पूर्णांकerrupt */
		ioग_लिखो8(0x00, NPCM7XX_FAN_REG_TIEN(data->fan_base, md));

		/* clear all पूर्णांकerrupt */
		ioग_लिखो8(NPCM7XX_FAN_TICLR_CLEAR_ALL,
			 NPCM7XX_FAN_REG_TICLR(data->fan_base, md));

		/* set FAN0~7 घड़ी prescaler */
		ioग_लिखो8(NPCM7XX_FAN_CLK_PRESCALE,
			 NPCM7XX_FAN_REG_TPRSC(data->fan_base, md));

		/* set FAN0~7 mode (high-to-low transition) */
		ioग_लिखो8((NPCM7XX_FAN_TMCTRL_MODE_5 | NPCM7XX_FAN_TMCTRL_TBEN |
			  NPCM7XX_FAN_TMCTRL_TAEN),
			 NPCM7XX_FAN_REG_TMCTRL(data->fan_base, md));

		/* set FAN0~7 Initial Count/Cap */
		ioग_लिखो16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_REG_TCNT1(data->fan_base, md));
		ioग_लिखो16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_REG_TCNT2(data->fan_base, md));

		/* set FAN0~7 compare (equal to count) */
		ioग_लिखो8((NPCM7XX_FAN_TCPCFG_EQAEN | NPCM7XX_FAN_TCPCFG_EQBEN),
			 NPCM7XX_FAN_REG_TCPCFG(data->fan_base, md));

		/* set FAN0~7 compare value */
		ioग_लिखो16(NPCM7XX_FAN_TCPA,
			  NPCM7XX_FAN_REG_TCPA(data->fan_base, md));
		ioग_लिखो16(NPCM7XX_FAN_TCPB,
			  NPCM7XX_FAN_REG_TCPB(data->fan_base, md));

		/* set FAN0~7 fan input FANIN 0~15 */
		ioग_लिखो8(NPCM7XX_FAN_TINASEL_FANIN_DEFAULT,
			 NPCM7XX_FAN_REG_TINASEL(data->fan_base, md));
		ioग_लिखो8(NPCM7XX_FAN_TINASEL_FANIN_DEFAULT,
			 NPCM7XX_FAN_REG_TINBSEL(data->fan_base, md));

		क्रम (i = 0; i < NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE; i++) अणु
			ch = md * NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE + i;
			data->fan_dev[ch].fan_st_flg = FAN_DISABLE;
			data->fan_dev[ch].fan_pls_per_rev =
				NPCM7XX_FAN_DEFAULT_PULSE_PER_REVOLUTION;
			data->fan_dev[ch].fan_cnt = 0;
		पूर्ण
	पूर्ण

	apb_clk_freq = clk_get_rate(data->fan_clk);

	/* Fan tach input घड़ी = APB घड़ी / prescalar, शेष is 255. */
	data->input_clk_freq = apb_clk_freq / (NPCM7XX_FAN_CLK_PRESCALE + 1);
पूर्ण

अटल पूर्णांक
npcm7xx_pwm_cz_get_max_state(काष्ठा thermal_cooling_device *tcdev,
			     अचिन्हित दीर्घ *state)
अणु
	काष्ठा npcm7xx_cooling_device *cdev = tcdev->devdata;

	*state = cdev->max_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
npcm7xx_pwm_cz_get_cur_state(काष्ठा thermal_cooling_device *tcdev,
			     अचिन्हित दीर्घ *state)
अणु
	काष्ठा npcm7xx_cooling_device *cdev = tcdev->devdata;

	*state = cdev->cur_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
npcm7xx_pwm_cz_set_cur_state(काष्ठा thermal_cooling_device *tcdev,
			     अचिन्हित दीर्घ state)
अणु
	काष्ठा npcm7xx_cooling_device *cdev = tcdev->devdata;
	पूर्णांक ret;

	अगर (state > cdev->max_state)
		वापस -EINVAL;

	cdev->cur_state = state;
	ret = npcm7xx_pwm_config_set(cdev->data, cdev->pwm_port,
				     cdev->cooling_levels[cdev->cur_state]);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops npcm7xx_pwm_cool_ops = अणु
	.get_max_state = npcm7xx_pwm_cz_get_max_state,
	.get_cur_state = npcm7xx_pwm_cz_get_cur_state,
	.set_cur_state = npcm7xx_pwm_cz_set_cur_state,
पूर्ण;

अटल पूर्णांक npcm7xx_create_pwm_cooling(काष्ठा device *dev,
				      काष्ठा device_node *child,
				      काष्ठा npcm7xx_pwm_fan_data *data,
				      u32 pwm_port, u8 num_levels)
अणु
	पूर्णांक ret;
	काष्ठा npcm7xx_cooling_device *cdev;

	cdev = devm_kzalloc(dev, माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	cdev->cooling_levels = devm_kzalloc(dev, num_levels, GFP_KERNEL);
	अगर (!cdev->cooling_levels)
		वापस -ENOMEM;

	cdev->max_state = num_levels - 1;
	ret = of_property_पढ़ो_u8_array(child, "cooling-levels",
					cdev->cooling_levels,
					num_levels);
	अगर (ret) अणु
		dev_err(dev, "Property 'cooling-levels' cannot be read.\n");
		वापस ret;
	पूर्ण
	snम_लिखो(cdev->name, THERMAL_NAME_LENGTH, "%pOFn%d", child,
		 pwm_port);

	cdev->tcdev = devm_thermal_of_cooling_device_रेजिस्टर(dev, child,
				cdev->name, cdev, &npcm7xx_pwm_cool_ops);
	अगर (IS_ERR(cdev->tcdev))
		वापस PTR_ERR(cdev->tcdev);

	cdev->data = data;
	cdev->pwm_port = pwm_port;

	data->cdev[pwm_port] = cdev;

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_en_pwm_fan(काष्ठा device *dev,
			      काष्ठा device_node *child,
			      काष्ठा npcm7xx_pwm_fan_data *data)
अणु
	u8 *fan_ch;
	u32 pwm_port;
	पूर्णांक ret, fan_cnt;
	u8 index, ch;

	ret = of_property_पढ़ो_u32(child, "reg", &pwm_port);
	अगर (ret)
		वापस ret;

	data->pwm_present[pwm_port] = true;
	ret = npcm7xx_pwm_config_set(data, pwm_port,
				     NPCM7XX_PWM_CMR_DEFAULT_NUM);

	ret = of_property_count_u8_elems(child, "cooling-levels");
	अगर (ret > 0) अणु
		ret = npcm7xx_create_pwm_cooling(dev, child, data, pwm_port,
						 ret);
		अगर (ret)
			वापस ret;
	पूर्ण

	fan_cnt = of_property_count_u8_elems(child, "fan-tach-ch");
	अगर (fan_cnt < 1)
		वापस -EINVAL;

	fan_ch = devm_kसुस्मृति(dev, fan_cnt, माप(*fan_ch), GFP_KERNEL);
	अगर (!fan_ch)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u8_array(child, "fan-tach-ch", fan_ch, fan_cnt);
	अगर (ret)
		वापस ret;

	क्रम (ch = 0; ch < fan_cnt; ch++) अणु
		index = fan_ch[ch];
		data->fan_present[index] = true;
		data->fan_dev[index].fan_st_flg = FAN_INIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_pwm_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np, *child;
	काष्ठा npcm7xx_pwm_fan_data *data;
	काष्ठा resource *res;
	काष्ठा device *hwmon;
	अक्षर name[20];
	पूर्णांक ret, cnt;
	u32 output_freq;
	u32 i;

	np = dev->of_node;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pwm");
	अगर (!res) अणु
		dev_err(dev, "pwm resource not found\n");
		वापस -ENODEV;
	पूर्ण

	data->pwm_base = devm_ioremap_resource(dev, res);
	dev_dbg(dev, "pwm base resource is %pR\n", res);
	अगर (IS_ERR(data->pwm_base))
		वापस PTR_ERR(data->pwm_base);

	data->pwm_clk = devm_clk_get(dev, "pwm");
	अगर (IS_ERR(data->pwm_clk)) अणु
		dev_err(dev, "couldn't get pwm clock\n");
		वापस PTR_ERR(data->pwm_clk);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "fan");
	अगर (!res) अणु
		dev_err(dev, "fan resource not found\n");
		वापस -ENODEV;
	पूर्ण

	data->fan_base = devm_ioremap_resource(dev, res);
	dev_dbg(dev, "fan base resource is %pR\n", res);
	अगर (IS_ERR(data->fan_base))
		वापस PTR_ERR(data->fan_base);

	data->fan_clk = devm_clk_get(dev, "fan");
	अगर (IS_ERR(data->fan_clk)) अणु
		dev_err(dev, "couldn't get fan clock\n");
		वापस PTR_ERR(data->fan_clk);
	पूर्ण

	output_freq = npcm7xx_pwm_init(data);
	npcm7xx_fan_init(data);

	क्रम (cnt = 0; cnt < NPCM7XX_PWM_MAX_MODULES  ; cnt++)
		mutex_init(&data->pwm_lock[cnt]);

	क्रम (i = 0; i < NPCM7XX_FAN_MAX_MODULE; i++) अणु
		spin_lock_init(&data->fan_lock[i]);

		data->fan_irq[i] = platक्रमm_get_irq(pdev, i);
		अगर (data->fan_irq[i] < 0)
			वापस data->fan_irq[i];

		प्र_लिखो(name, "NPCM7XX-FAN-MD%d", i);
		ret = devm_request_irq(dev, data->fan_irq[i], npcm7xx_fan_isr,
				       0, name, (व्योम *)data);
		अगर (ret) अणु
			dev_err(dev, "register IRQ fan%d failed\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		ret = npcm7xx_en_pwm_fan(dev, child, data);
		अगर (ret) अणु
			dev_err(dev, "enable pwm and fan failed\n");
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	hwmon = devm_hwmon_device_रेजिस्टर_with_info(dev, "npcm7xx_pwm_fan",
						     data, &npcm7xx_chip_info,
						     शून्य);
	अगर (IS_ERR(hwmon)) अणु
		dev_err(dev, "unable to register hwmon device\n");
		वापस PTR_ERR(hwmon);
	पूर्ण

	क्रम (i = 0; i < NPCM7XX_FAN_MAX_CHN_NUM; i++) अणु
		अगर (data->fan_present[i]) अणु
			/* fan समयr initialization */
			data->fan_समयr.expires = jअगरfies +
				msecs_to_jअगरfies(NPCM7XX_FAN_POLL_TIMER_200MS);
			समयr_setup(&data->fan_समयr,
				    npcm7xx_fan_polling, 0);
			add_समयr(&data->fan_समयr);
			अवरोध;
		पूर्ण
	पूर्ण

	pr_info("NPCM7XX PWM-FAN Driver probed, output Freq %dHz[PWM], input Freq %dHz[FAN]\n",
		output_freq, data->input_clk_freq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pwm_fan_match_table[] = अणु
	अणु .compatible = "nuvoton,npcm750-pwm-fan", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pwm_fan_match_table);

अटल काष्ठा platक्रमm_driver npcm7xx_pwm_fan_driver = अणु
	.probe		= npcm7xx_pwm_fan_probe,
	.driver		= अणु
		.name	= "npcm7xx_pwm_fan",
		.of_match_table = of_pwm_fan_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(npcm7xx_pwm_fan_driver);

MODULE_DESCRIPTION("Nuvoton NPCM7XX PWM and Fan Tacho driver");
MODULE_AUTHOR("Tomer Maimon <tomer.maimon@nuvoton.com>");
MODULE_LICENSE("GPL v2");
