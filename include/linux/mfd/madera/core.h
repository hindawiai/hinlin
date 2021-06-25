<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MFD पूर्णांकernals क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic
 */

#अगर_अघोषित MADERA_CORE_H
#घोषणा MADERA_CORE_H

#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

क्रमागत madera_type अणु
	/* 0 is reserved क्रम indicating failure to identअगरy */
	CS47L35 = 1,
	CS47L85 = 2,
	CS47L90 = 3,
	CS47L91 = 4,
	CS47L92 = 5,
	CS47L93 = 6,
	WM1840 = 7,
	CS47L15 = 8,
	CS42L92 = 9,
पूर्ण;

क्रमागत अणु
	MADERA_MCLK1,
	MADERA_MCLK2,
	MADERA_MCLK3,
	MADERA_NUM_MCLK
पूर्ण;

#घोषणा MADERA_MAX_CORE_SUPPLIES	2
#घोषणा MADERA_MAX_GPIOS		40

#घोषणा CS47L15_NUM_GPIOS		15
#घोषणा CS47L35_NUM_GPIOS		16
#घोषणा CS47L85_NUM_GPIOS		40
#घोषणा CS47L90_NUM_GPIOS		38
#घोषणा CS47L92_NUM_GPIOS		16

#घोषणा MADERA_MAX_MICBIAS		4

#घोषणा MADERA_MAX_HP_OUTPUT		3

/* Notअगरier events */
#घोषणा MADERA_NOTIFY_VOICE_TRIGGER	0x1
#घोषणा MADERA_NOTIFY_HPDET		0x2
#घोषणा MADERA_NOTIFY_MICDET		0x4

/* GPIO Function Definitions */
#घोषणा MADERA_GP_FN_ALTERNATE		0x00
#घोषणा MADERA_GP_FN_GPIO		0x01
#घोषणा MADERA_GP_FN_DSP_GPIO		0x02
#घोषणा MADERA_GP_FN_IRQ1		0x03
#घोषणा MADERA_GP_FN_IRQ2		0x04
#घोषणा MADERA_GP_FN_FLL1_CLOCK		0x10
#घोषणा MADERA_GP_FN_FLL2_CLOCK		0x11
#घोषणा MADERA_GP_FN_FLL3_CLOCK		0x12
#घोषणा MADERA_GP_FN_FLLAO_CLOCK	0x13
#घोषणा MADERA_GP_FN_FLL1_LOCK		0x18
#घोषणा MADERA_GP_FN_FLL2_LOCK		0x19
#घोषणा MADERA_GP_FN_FLL3_LOCK		0x1A
#घोषणा MADERA_GP_FN_FLLAO_LOCK		0x1B
#घोषणा MADERA_GP_FN_OPCLK_OUT		0x40
#घोषणा MADERA_GP_FN_OPCLK_ASYNC_OUT	0x41
#घोषणा MADERA_GP_FN_PWM1		0x48
#घोषणा MADERA_GP_FN_PWM2		0x49
#घोषणा MADERA_GP_FN_SPDIF_OUT		0x4C
#घोषणा MADERA_GP_FN_HEADPHONE_DET	0x50
#घोषणा MADERA_GP_FN_MIC_DET		0x58
#घोषणा MADERA_GP_FN_DRC1_SIGNAL_DETECT	0x80
#घोषणा MADERA_GP_FN_DRC2_SIGNAL_DETECT	0x81
#घोषणा MADERA_GP_FN_ASRC1_IN1_LOCK	0x88
#घोषणा MADERA_GP_FN_ASRC1_IN2_LOCK	0x89
#घोषणा MADERA_GP_FN_ASRC2_IN1_LOCK	0x8A
#घोषणा MADERA_GP_FN_ASRC2_IN2_LOCK	0x8B
#घोषणा MADERA_GP_FN_DSP_IRQ1		0xA0
#घोषणा MADERA_GP_FN_DSP_IRQ2		0xA1
#घोषणा MADERA_GP_FN_DSP_IRQ3		0xA2
#घोषणा MADERA_GP_FN_DSP_IRQ4		0xA3
#घोषणा MADERA_GP_FN_DSP_IRQ5		0xA4
#घोषणा MADERA_GP_FN_DSP_IRQ6		0xA5
#घोषणा MADERA_GP_FN_DSP_IRQ7		0xA6
#घोषणा MADERA_GP_FN_DSP_IRQ8		0xA7
#घोषणा MADERA_GP_FN_DSP_IRQ9		0xA8
#घोषणा MADERA_GP_FN_DSP_IRQ10		0xA9
#घोषणा MADERA_GP_FN_DSP_IRQ11		0xAA
#घोषणा MADERA_GP_FN_DSP_IRQ12		0xAB
#घोषणा MADERA_GP_FN_DSP_IRQ13		0xAC
#घोषणा MADERA_GP_FN_DSP_IRQ14		0xAD
#घोषणा MADERA_GP_FN_DSP_IRQ15		0xAE
#घोषणा MADERA_GP_FN_DSP_IRQ16		0xAF
#घोषणा MADERA_GP_FN_HPOUT1L_SC		0xB0
#घोषणा MADERA_GP_FN_HPOUT1R_SC		0xB1
#घोषणा MADERA_GP_FN_HPOUT2L_SC		0xB2
#घोषणा MADERA_GP_FN_HPOUT2R_SC		0xB3
#घोषणा MADERA_GP_FN_HPOUT3L_SC		0xB4
#घोषणा MADERA_GP_FN_HPOUT4R_SC		0xB5
#घोषणा MADERA_GP_FN_SPKOUTL_SC		0xB6
#घोषणा MADERA_GP_FN_SPKOUTR_SC		0xB7
#घोषणा MADERA_GP_FN_HPOUT1L_ENA	0xC0
#घोषणा MADERA_GP_FN_HPOUT1R_ENA	0xC1
#घोषणा MADERA_GP_FN_HPOUT2L_ENA	0xC2
#घोषणा MADERA_GP_FN_HPOUT2R_ENA	0xC3
#घोषणा MADERA_GP_FN_HPOUT3L_ENA	0xC4
#घोषणा MADERA_GP_FN_HPOUT4R_ENA	0xC5
#घोषणा MADERA_GP_FN_SPKOUTL_ENA	0xC6
#घोषणा MADERA_GP_FN_SPKOUTR_ENA	0xC7
#घोषणा MADERA_GP_FN_HPOUT1L_DIS	0xD0
#घोषणा MADERA_GP_FN_HPOUT1R_DIS	0xD1
#घोषणा MADERA_GP_FN_HPOUT2L_DIS	0xD2
#घोषणा MADERA_GP_FN_HPOUT2R_DIS	0xD3
#घोषणा MADERA_GP_FN_HPOUT3L_DIS	0xD4
#घोषणा MADERA_GP_FN_HPOUT4R_DIS	0xD5
#घोषणा MADERA_GP_FN_SPKOUTL_DIS	0xD6
#घोषणा MADERA_GP_FN_SPKOUTR_DIS	0xD7
#घोषणा MADERA_GP_FN_SPK_SHUTDOWN	0xE0
#घोषणा MADERA_GP_FN_SPK_OVH_SHUTDOWN	0xE1
#घोषणा MADERA_GP_FN_SPK_OVH_WARN	0xE2
#घोषणा MADERA_GP_FN_TIMER1_STATUS	0x140
#घोषणा MADERA_GP_FN_TIMER2_STATUS	0x141
#घोषणा MADERA_GP_FN_TIMER3_STATUS	0x142
#घोषणा MADERA_GP_FN_TIMER4_STATUS	0x143
#घोषणा MADERA_GP_FN_TIMER5_STATUS	0x144
#घोषणा MADERA_GP_FN_TIMER6_STATUS	0x145
#घोषणा MADERA_GP_FN_TIMER7_STATUS	0x146
#घोषणा MADERA_GP_FN_TIMER8_STATUS	0x147
#घोषणा MADERA_GP_FN_EVENTLOG1_FIFO_STS	0x150
#घोषणा MADERA_GP_FN_EVENTLOG2_FIFO_STS	0x151
#घोषणा MADERA_GP_FN_EVENTLOG3_FIFO_STS	0x152
#घोषणा MADERA_GP_FN_EVENTLOG4_FIFO_STS	0x153
#घोषणा MADERA_GP_FN_EVENTLOG5_FIFO_STS	0x154
#घोषणा MADERA_GP_FN_EVENTLOG6_FIFO_STS	0x155
#घोषणा MADERA_GP_FN_EVENTLOG7_FIFO_STS	0x156
#घोषणा MADERA_GP_FN_EVENTLOG8_FIFO_STS	0x157

काष्ठा snd_soc_dapm_context;

/*
 * काष्ठा madera - पूर्णांकernal data shared by the set of Madera drivers
 *
 * This should not be used by anything except child drivers of the Madera MFD
 *
 * @regmap:		poपूर्णांकer to the regmap instance क्रम 16-bit रेजिस्टरs
 * @regmap_32bit:	poपूर्णांकer to the regmap instance क्रम 32-bit रेजिस्टरs
 * @dev:		poपूर्णांकer to the MFD device
 * @type:		type of codec
 * @rev:		silicon revision
 * @type_name:		display name of this codec
 * @num_core_supplies:	number of core supply regulators
 * @core_supplies:	list of core supplies that are always required
 * @dcvdd:		poपूर्णांकer to DCVDD regulator
 * @पूर्णांकernal_dcvdd:	true अगर DCVDD is supplied from the पूर्णांकernal LDO1
 * @pdata:		our pdata
 * @irq_dev:		the irqchip child driver device
 * @irq_data:		poपूर्णांकer to irqchip data क्रम the child irqchip driver
 * @irq:		host irq number from SPI or I2C configuration
 * @mclk:		Structure holding घड़ी supplies
 * @out_clamp:		indicates output clamp state क्रम each analogue output
 * @out_लघुed:	indicates लघु circuit state क्रम each analogue output
 * @hp_ena:		bitflags of enable state क्रम the headphone outमाला_दो
 * @num_micbias:	number of MICBIAS outमाला_दो
 * @num_childbias:	number of child biases क्रम each MICBIAS
 * @dapm:		poपूर्णांकer to codec driver DAPM context
 * @notअगरier:		notअगरier क्रम संकेतling events to ASoC machine driver
 */
काष्ठा madera अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap *regmap_32bit;

	काष्ठा device *dev;

	क्रमागत madera_type type;
	अचिन्हित पूर्णांक rev;
	स्थिर अक्षर *type_name;

	पूर्णांक num_core_supplies;
	काष्ठा regulator_bulk_data core_supplies[MADERA_MAX_CORE_SUPPLIES];
	काष्ठा regulator *dcvdd;
	bool पूर्णांकernal_dcvdd;
	bool reset_errata;

	काष्ठा madera_pdata pdata;

	काष्ठा device *irq_dev;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक irq;

	काष्ठा clk_bulk_data mclk[MADERA_NUM_MCLK];

	अचिन्हित पूर्णांक num_micbias;
	अचिन्हित पूर्णांक num_childbias[MADERA_MAX_MICBIAS];

	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा mutex dapm_ptr_lock;
	अचिन्हित पूर्णांक hp_ena;
	bool out_clamp[MADERA_MAX_HP_OUTPUT];
	bool out_लघुed[MADERA_MAX_HP_OUTPUT];

	काष्ठा blocking_notअगरier_head notअगरier;
पूर्ण;
#पूर्ण_अगर
