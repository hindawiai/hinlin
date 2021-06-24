<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da7219-aad.h - DA7322 ASoC AAD Driver
 *
 * Copyright (c) 2015 Dialog Semiconductor Ltd.
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __DA7219_AAD_H
#घोषणा __DA7219_AAD_H

#समावेश <linux/समयr.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/da7219-aad.h>

/*
 * Registers
 */

#घोषणा DA7219_ACCDET_STATUS_A		0xC0
#घोषणा DA7219_ACCDET_STATUS_B		0xC1
#घोषणा DA7219_ACCDET_IRQ_EVENT_A	0xC2
#घोषणा DA7219_ACCDET_IRQ_EVENT_B	0xC3
#घोषणा DA7219_ACCDET_IRQ_MASK_A	0xC4
#घोषणा DA7219_ACCDET_IRQ_MASK_B	0xC5
#घोषणा DA7219_ACCDET_CONFIG_1		0xC6
#घोषणा DA7219_ACCDET_CONFIG_2		0xC7
#घोषणा DA7219_ACCDET_CONFIG_3		0xC8
#घोषणा DA7219_ACCDET_CONFIG_4		0xC9
#घोषणा DA7219_ACCDET_CONFIG_5		0xCA
#घोषणा DA7219_ACCDET_CONFIG_6		0xCB
#घोषणा DA7219_ACCDET_CONFIG_7		0xCC
#घोषणा DA7219_ACCDET_CONFIG_8		0xCD


/*
 * Bit Fields
 */

/* DA7219_ACCDET_STATUS_A = 0xC0 */
#घोषणा DA7219_JACK_INSERTION_STS_SHIFT	0
#घोषणा DA7219_JACK_INSERTION_STS_MASK	(0x1 << 0)
#घोषणा DA7219_JACK_TYPE_STS_SHIFT	1
#घोषणा DA7219_JACK_TYPE_STS_MASK	(0x1 << 1)
#घोषणा DA7219_JACK_PIN_ORDER_STS_SHIFT	2
#घोषणा DA7219_JACK_PIN_ORDER_STS_MASK	(0x1 << 2)
#घोषणा DA7219_MICBIAS_UP_STS_SHIFT	3
#घोषणा DA7219_MICBIAS_UP_STS_MASK	(0x1 << 3)

/* DA7219_ACCDET_STATUS_B = 0xC1 */
#घोषणा DA7219_BUTTON_TYPE_STS_SHIFT	0
#घोषणा DA7219_BUTTON_TYPE_STS_MASK	(0xFF << 0)

/* DA7219_ACCDET_IRQ_EVENT_A = 0xC2 */
#घोषणा DA7219_E_JACK_INSERTED_SHIFT		0
#घोषणा DA7219_E_JACK_INSERTED_MASK		(0x1 << 0)
#घोषणा DA7219_E_JACK_REMOVED_SHIFT		1
#घोषणा DA7219_E_JACK_REMOVED_MASK		(0x1 << 1)
#घोषणा DA7219_E_JACK_DETECT_COMPLETE_SHIFT	2
#घोषणा DA7219_E_JACK_DETECT_COMPLETE_MASK	(0x1 << 2)

/* DA7219_ACCDET_IRQ_EVENT_B = 0xC3 */
#घोषणा DA7219_E_BUTTON_A_PRESSED_SHIFT		0
#घोषणा DA7219_E_BUTTON_A_PRESSED_MASK		(0x1 << 0)
#घोषणा DA7219_E_BUTTON_B_PRESSED_SHIFT		1
#घोषणा DA7219_E_BUTTON_B_PRESSED_MASK		(0x1 << 1)
#घोषणा DA7219_E_BUTTON_C_PRESSED_SHIFT		2
#घोषणा DA7219_E_BUTTON_C_PRESSED_MASK		(0x1 << 2)
#घोषणा DA7219_E_BUTTON_D_PRESSED_SHIFT		3
#घोषणा DA7219_E_BUTTON_D_PRESSED_MASK		(0x1 << 3)
#घोषणा DA7219_E_BUTTON_D_RELEASED_SHIFT	4
#घोषणा DA7219_E_BUTTON_D_RELEASED_MASK		(0x1 << 4)
#घोषणा DA7219_E_BUTTON_C_RELEASED_SHIFT	5
#घोषणा DA7219_E_BUTTON_C_RELEASED_MASK		(0x1 << 5)
#घोषणा DA7219_E_BUTTON_B_RELEASED_SHIFT	6
#घोषणा DA7219_E_BUTTON_B_RELEASED_MASK		(0x1 << 6)
#घोषणा DA7219_E_BUTTON_A_RELEASED_SHIFT	7
#घोषणा DA7219_E_BUTTON_A_RELEASED_MASK		(0x1 << 7)

/* DA7219_ACCDET_IRQ_MASK_A = 0xC4 */
#घोषणा DA7219_M_JACK_INSERTED_SHIFT		0
#घोषणा DA7219_M_JACK_INSERTED_MASK		(0x1 << 0)
#घोषणा DA7219_M_JACK_REMOVED_SHIFT		1
#घोषणा DA7219_M_JACK_REMOVED_MASK		(0x1 << 1)
#घोषणा DA7219_M_JACK_DETECT_COMPLETE_SHIFT	2
#घोषणा DA7219_M_JACK_DETECT_COMPLETE_MASK	(0x1 << 2)

/* DA7219_ACCDET_IRQ_MASK_B = 0xC5 */
#घोषणा DA7219_M_BUTTON_A_PRESSED_SHIFT		0
#घोषणा DA7219_M_BUTTON_A_PRESSED_MASK		(0x1 << 0)
#घोषणा DA7219_M_BUTTON_B_PRESSED_SHIFT		1
#घोषणा DA7219_M_BUTTON_B_PRESSED_MASK		(0x1 << 1)
#घोषणा DA7219_M_BUTTON_C_PRESSED_SHIFT		2
#घोषणा DA7219_M_BUTTON_C_PRESSED_MASK		(0x1 << 2)
#घोषणा DA7219_M_BUTTON_D_PRESSED_SHIFT		3
#घोषणा DA7219_M_BUTTON_D_PRESSED_MASK		(0x1 << 3)
#घोषणा DA7219_M_BUTTON_D_RELEASED_SHIFT	4
#घोषणा DA7219_M_BUTTON_D_RELEASED_MASK		(0x1 << 4)
#घोषणा DA7219_M_BUTTON_C_RELEASED_SHIFT	5
#घोषणा DA7219_M_BUTTON_C_RELEASED_MASK		(0x1 << 5)
#घोषणा DA7219_M_BUTTON_B_RELEASED_SHIFT	6
#घोषणा DA7219_M_BUTTON_B_RELEASED_MASK		(0x1 << 6)
#घोषणा DA7219_M_BUTTON_A_RELEASED_SHIFT	7
#घोषणा DA7219_M_BUTTON_A_RELEASED_MASK		(0x1 << 7)

/* DA7219_ACCDET_CONFIG_1 = 0xC6 */
#घोषणा DA7219_ACCDET_EN_SHIFT		0
#घोषणा DA7219_ACCDET_EN_MASK		(0x1 << 0)
#घोषणा DA7219_BUTTON_CONFIG_SHIFT	1
#घोषणा DA7219_BUTTON_CONFIG_MASK	(0x7 << 1)
#घोषणा DA7219_MIC_DET_THRESH_SHIFT	4
#घोषणा DA7219_MIC_DET_THRESH_MASK	(0x3 << 4)
#घोषणा DA7219_JACK_TYPE_DET_EN_SHIFT	6
#घोषणा DA7219_JACK_TYPE_DET_EN_MASK	(0x1 << 6)
#घोषणा DA7219_PIN_ORDER_DET_EN_SHIFT	7
#घोषणा DA7219_PIN_ORDER_DET_EN_MASK	(0x1 << 7)

/* DA7219_ACCDET_CONFIG_2 = 0xC7 */
#घोषणा DA7219_ACCDET_PAUSE_SHIFT	0
#घोषणा DA7219_ACCDET_PAUSE_MASK	(0x1 << 0)
#घोषणा DA7219_JACKDET_DEBOUNCE_SHIFT	1
#घोषणा DA7219_JACKDET_DEBOUNCE_MASK	(0x7 << 1)
#घोषणा DA7219_JACK_DETECT_RATE_SHIFT	4
#घोषणा DA7219_JACK_DETECT_RATE_MASK	(0x3 << 4)
#घोषणा DA7219_JACKDET_REM_DEB_SHIFT	6
#घोषणा DA7219_JACKDET_REM_DEB_MASK	(0x3 << 6)

/* DA7219_ACCDET_CONFIG_3 = 0xC8 */
#घोषणा DA7219_A_D_BUTTON_THRESH_SHIFT	0
#घोषणा DA7219_A_D_BUTTON_THRESH_MASK	(0xFF << 0)

/* DA7219_ACCDET_CONFIG_4 = 0xC9 */
#घोषणा DA7219_D_B_BUTTON_THRESH_SHIFT	0
#घोषणा DA7219_D_B_BUTTON_THRESH_MASK	(0xFF << 0)

/* DA7219_ACCDET_CONFIG_5 = 0xCA */
#घोषणा DA7219_B_C_BUTTON_THRESH_SHIFT	0
#घोषणा DA7219_B_C_BUTTON_THRESH_MASK	(0xFF << 0)

/* DA7219_ACCDET_CONFIG_6 = 0xCB */
#घोषणा DA7219_C_MIC_BUTTON_THRESH_SHIFT	0
#घोषणा DA7219_C_MIC_BUTTON_THRESH_MASK		(0xFF << 0)

/* DA7219_ACCDET_CONFIG_7 = 0xCC */
#घोषणा DA7219_BUTTON_AVERAGE_SHIFT	0
#घोषणा DA7219_BUTTON_AVERAGE_MASK	(0x3 << 0)
#घोषणा DA7219_ADC_1_BIT_REPEAT_SHIFT	2
#घोषणा DA7219_ADC_1_BIT_REPEAT_MASK	(0x3 << 2)
#घोषणा DA7219_PIN_ORDER_FORCE_SHIFT	4
#घोषणा DA7219_PIN_ORDER_FORCE_MASK	(0x1 << 4)
#घोषणा DA7219_JACK_TYPE_FORCE_SHIFT	5
#घोषणा DA7219_JACK_TYPE_FORCE_MASK	(0x1 << 5)

/* DA7219_ACCDET_CONFIG_8 = 0xCD */
#घोषणा DA7219_HPTEST_EN_SHIFT		0
#घोषणा DA7219_HPTEST_EN_MASK		(0x1 << 0)
#घोषणा DA7219_HPTEST_RES_SEL_SHIFT	1
#घोषणा DA7219_HPTEST_RES_SEL_MASK	(0x3 << 1)
#घोषणा DA7219_HPTEST_RES_SEL_1KOHMS	(0x0 << 1)
#घोषणा DA7219_HPTEST_COMP_SHIFT	4
#घोषणा DA7219_HPTEST_COMP_MASK		(0x1 << 4)


#घोषणा DA7219_AAD_MAX_BUTTONS		4
#घोषणा DA7219_AAD_REPORT_ALL_MASK	(SND_JACK_MECHANICAL |			\
					 SND_JACK_HEADSET | SND_JACK_LINEOUT |	\
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |	\
					 SND_JACK_BTN_2 | SND_JACK_BTN_3)

#घोषणा DA7219_AAD_MICBIAS_CHK_DELAY	10
#घोषणा DA7219_AAD_MICBIAS_CHK_RETRIES	5

#घोषणा DA7219_AAD_HPTEST_RAMP_FREQ		0x28
#घोषणा DA7219_AAD_HPTEST_RAMP_FREQ_INT_OSC	0x4D
#घोषणा DA7219_AAD_HPTEST_PERIOD		65
#घोषणा DA7219_AAD_HPTEST_INT_OSC_PATH_DELAY	20

क्रमागत da7219_aad_event_regs अणु
	DA7219_AAD_IRQ_REG_A = 0,
	DA7219_AAD_IRQ_REG_B,
	DA7219_AAD_IRQ_REG_MAX,
पूर्ण;

/* Private data */
काष्ठा da7219_aad_priv अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक irq;

	u8 micbias_pulse_lvl;
	u32 micbias_pulse_समय;

	u8 btn_cfg;

	काष्ठा work_काष्ठा btn_det_work;
	काष्ठा work_काष्ठा hptest_work;

	काष्ठा snd_soc_jack *jack;
	bool micbias_resume_enable;
	bool jack_inserted;
पूर्ण;

/* AAD control */
व्योम da7219_aad_jack_det(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack);

/* Suspend/Resume */
व्योम da7219_aad_suspend(काष्ठा snd_soc_component *component);
व्योम da7219_aad_resume(काष्ठा snd_soc_component *component);

/* Init/Exit */
पूर्णांक da7219_aad_init(काष्ठा snd_soc_component *component);
व्योम da7219_aad_निकास(काष्ठा snd_soc_component *component);

/* I2C Probe */
पूर्णांक da7219_aad_probe(काष्ठा i2c_client *i2c);

#पूर्ण_अगर /* __DA7219_AAD_H */
