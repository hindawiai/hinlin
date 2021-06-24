<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2009-2010 Pengutronix
 * Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>
 */
#अगर_अघोषित __LINUX_MFD_MC13XXX_H
#घोषणा __LINUX_MFD_MC13XXX_H

#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा mc13xxx;

व्योम mc13xxx_lock(काष्ठा mc13xxx *mc13xxx);
व्योम mc13xxx_unlock(काष्ठा mc13xxx *mc13xxx);

पूर्णांक mc13xxx_reg_पढ़ो(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset, u32 *val);
पूर्णांक mc13xxx_reg_ग_लिखो(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset, u32 val);
पूर्णांक mc13xxx_reg_rmw(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset,
		u32 mask, u32 val);

पूर्णांक mc13xxx_irq_request(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq,
		irq_handler_t handler, स्थिर अक्षर *name, व्योम *dev);
पूर्णांक mc13xxx_irq_मुक्त(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq, व्योम *dev);

पूर्णांक mc13xxx_irq_status(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq,
		पूर्णांक *enabled, पूर्णांक *pending);

पूर्णांक mc13xxx_get_flags(काष्ठा mc13xxx *mc13xxx);

पूर्णांक mc13xxx_adc_करो_conversion(काष्ठा mc13xxx *mc13xxx,
		अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक channel,
		u8 ato, bool atox, अचिन्हित पूर्णांक *sample);

/* Deprecated calls */
अटल अंतरभूत पूर्णांक mc13xxx_irq_ack(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mc13xxx_irq_request_nounmask(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq,
					       irq_handler_t handler,
					       स्थिर अक्षर *name, व्योम *dev)
अणु
	वापस mc13xxx_irq_request(mc13xxx, irq, handler, name, dev);
पूर्ण

पूर्णांक mc13xxx_irq_mask(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq);
पूर्णांक mc13xxx_irq_unmask(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq);

#घोषणा MC13783_AUDIO_RX0	36
#घोषणा MC13783_AUDIO_RX1	37
#घोषणा MC13783_AUDIO_TX	38
#घोषणा MC13783_SSI_NETWORK	39
#घोषणा MC13783_AUDIO_CODEC	40
#घोषणा MC13783_AUDIO_DAC	41

#घोषणा MC13XXX_IRQ_ADCDONE	0
#घोषणा MC13XXX_IRQ_ADCBISDONE	1
#घोषणा MC13XXX_IRQ_TS		2
#घोषणा MC13XXX_IRQ_CHGDET	6
#घोषणा MC13XXX_IRQ_CHGREV	8
#घोषणा MC13XXX_IRQ_CHGSHORT	9
#घोषणा MC13XXX_IRQ_CCCV	10
#घोषणा MC13XXX_IRQ_CHGCURR	11
#घोषणा MC13XXX_IRQ_BPON	12
#घोषणा MC13XXX_IRQ_LOBATL	13
#घोषणा MC13XXX_IRQ_LOBATH	14
#घोषणा MC13XXX_IRQ_1HZ		24
#घोषणा MC13XXX_IRQ_TODA	25
#घोषणा MC13XXX_IRQ_SYSRST	30
#घोषणा MC13XXX_IRQ_RTCRST	31
#घोषणा MC13XXX_IRQ_PC		32
#घोषणा MC13XXX_IRQ_WARM	33
#घोषणा MC13XXX_IRQ_MEMHLD	34
#घोषणा MC13XXX_IRQ_THWARNL	36
#घोषणा MC13XXX_IRQ_THWARNH	37
#घोषणा MC13XXX_IRQ_CLK		38

काष्ठा regulator_init_data;

काष्ठा mc13xxx_regulator_init_data अणु
	पूर्णांक id;
	काष्ठा regulator_init_data *init_data;
	काष्ठा device_node *node;
पूर्ण;

काष्ठा mc13xxx_regulator_platक्रमm_data अणु
	पूर्णांक num_regulators;
	काष्ठा mc13xxx_regulator_init_data *regulators;
पूर्ण;

क्रमागत अणु
	/* MC13783 LED IDs */
	MC13783_LED_MD,
	MC13783_LED_AD,
	MC13783_LED_KP,
	MC13783_LED_R1,
	MC13783_LED_G1,
	MC13783_LED_B1,
	MC13783_LED_R2,
	MC13783_LED_G2,
	MC13783_LED_B2,
	MC13783_LED_R3,
	MC13783_LED_G3,
	MC13783_LED_B3,
	/* MC13892 LED IDs */
	MC13892_LED_MD,
	MC13892_LED_AD,
	MC13892_LED_KP,
	MC13892_LED_R,
	MC13892_LED_G,
	MC13892_LED_B,
	/* MC34708 LED IDs */
	MC34708_LED_R,
	MC34708_LED_G,
पूर्ण;

काष्ठा mc13xxx_led_platक्रमm_data अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
पूर्ण;

#घोषणा MAX_LED_CONTROL_REGS	6

/* MC13783 LED Control 0 */
#घोषणा MC13783_LED_C0_ENABLE		(1 << 0)
#घोषणा MC13783_LED_C0_TRIODE_MD	(1 << 7)
#घोषणा MC13783_LED_C0_TRIODE_AD	(1 << 8)
#घोषणा MC13783_LED_C0_TRIODE_KP	(1 << 9)
#घोषणा MC13783_LED_C0_BOOST		(1 << 10)
#घोषणा MC13783_LED_C0_ABMODE(x)	(((x) & 0x7) << 11)
#घोषणा MC13783_LED_C0_ABREF(x)		(((x) & 0x3) << 14)
/* MC13783 LED Control 1 */
#घोषणा MC13783_LED_C1_TC1HALF		(1 << 18)
#घोषणा MC13783_LED_C1_SLEWLIM		(1 << 23)
/* MC13783 LED Control 2 */
#घोषणा MC13783_LED_C2_CURRENT_MD(x)	(((x) & 0x7) << 0)
#घोषणा MC13783_LED_C2_CURRENT_AD(x)	(((x) & 0x7) << 3)
#घोषणा MC13783_LED_C2_CURRENT_KP(x)	(((x) & 0x7) << 6)
#घोषणा MC13783_LED_C2_PERIOD(x)	(((x) & 0x3) << 21)
#घोषणा MC13783_LED_C2_SLEWLIM		(1 << 23)
/* MC13783 LED Control 3 */
#घोषणा MC13783_LED_C3_CURRENT_R1(x)	(((x) & 0x3) << 0)
#घोषणा MC13783_LED_C3_CURRENT_G1(x)	(((x) & 0x3) << 2)
#घोषणा MC13783_LED_C3_CURRENT_B1(x)	(((x) & 0x3) << 4)
#घोषणा MC13783_LED_C3_PERIOD(x)	(((x) & 0x3) << 21)
#घोषणा MC13783_LED_C3_TRIODE_TC1	(1 << 23)
/* MC13783 LED Control 4 */
#घोषणा MC13783_LED_C4_CURRENT_R2(x)	(((x) & 0x3) << 0)
#घोषणा MC13783_LED_C4_CURRENT_G2(x)	(((x) & 0x3) << 2)
#घोषणा MC13783_LED_C4_CURRENT_B2(x)	(((x) & 0x3) << 4)
#घोषणा MC13783_LED_C4_PERIOD(x)	(((x) & 0x3) << 21)
#घोषणा MC13783_LED_C4_TRIODE_TC2	(1 << 23)
/* MC13783 LED Control 5 */
#घोषणा MC13783_LED_C5_CURRENT_R3(x)	(((x) & 0x3) << 0)
#घोषणा MC13783_LED_C5_CURRENT_G3(x)	(((x) & 0x3) << 2)
#घोषणा MC13783_LED_C5_CURRENT_B3(x)	(((x) & 0x3) << 4)
#घोषणा MC13783_LED_C5_PERIOD(x)	(((x) & 0x3) << 21)
#घोषणा MC13783_LED_C5_TRIODE_TC3	(1 << 23)
/* MC13892 LED Control 0 */
#घोषणा MC13892_LED_C0_CURRENT_MD(x)	(((x) & 0x7) << 9)
#घोषणा MC13892_LED_C0_CURRENT_AD(x)	(((x) & 0x7) << 21)
/* MC13892 LED Control 1 */
#घोषणा MC13892_LED_C1_CURRENT_KP(x)	(((x) & 0x7) << 9)
/* MC13892 LED Control 2 */
#घोषणा MC13892_LED_C2_CURRENT_R(x)	(((x) & 0x7) << 9)
#घोषणा MC13892_LED_C2_CURRENT_G(x)	(((x) & 0x7) << 21)
/* MC13892 LED Control 3 */
#घोषणा MC13892_LED_C3_CURRENT_B(x)	(((x) & 0x7) << 9)
/* MC34708 LED Control 0 */
#घोषणा MC34708_LED_C0_CURRENT_R(x)	(((x) & 0x3) << 9)
#घोषणा MC34708_LED_C0_CURRENT_G(x)	(((x) & 0x3) << 21)

काष्ठा mc13xxx_leds_platक्रमm_data अणु
	काष्ठा mc13xxx_led_platक्रमm_data *led;
	पूर्णांक num_leds;
	u32 led_control[MAX_LED_CONTROL_REGS];
पूर्ण;

#घोषणा MC13783_BUTTON_DBNC_0MS		0
#घोषणा MC13783_BUTTON_DBNC_30MS	1
#घोषणा MC13783_BUTTON_DBNC_150MS	2
#घोषणा MC13783_BUTTON_DBNC_750MS	3
#घोषणा MC13783_BUTTON_ENABLE		(1 << 2)
#घोषणा MC13783_BUTTON_POL_INVERT	(1 << 3)
#घोषणा MC13783_BUTTON_RESET_EN		(1 << 4)

काष्ठा mc13xxx_buttons_platक्रमm_data अणु
	पूर्णांक b1on_flags;
	अचिन्हित लघु b1on_key;
	पूर्णांक b2on_flags;
	अचिन्हित लघु b2on_key;
	पूर्णांक b3on_flags;
	अचिन्हित लघु b3on_key;
पूर्ण;

#घोषणा MC13783_TS_ATO_FIRST	false
#घोषणा MC13783_TS_ATO_EACH	true

काष्ठा mc13xxx_ts_platक्रमm_data अणु
	/* Delay between Touchscreen polarization and ADC Conversion.
	 * Given in घड़ी ticks of a 32 kHz घड़ी which gives a granularity of
	 * about 30.5ms */
	u8 ato;
	/* Use the ATO delay only क्रम the first conversion or क्रम each one */
	bool atox;
पूर्ण;

क्रमागत mc13783_ssi_port अणु
	MC13783_SSI1_PORT,
	MC13783_SSI2_PORT,
पूर्ण;

काष्ठा mc13xxx_codec_platक्रमm_data अणु
	क्रमागत mc13783_ssi_port adc_ssi_port;
	क्रमागत mc13783_ssi_port dac_ssi_port;
पूर्ण;

#घोषणा MC13XXX_USE_TOUCHSCREEN	(1 << 0)
#घोषणा MC13XXX_USE_CODEC	(1 << 1)
#घोषणा MC13XXX_USE_ADC		(1 << 2)
#घोषणा MC13XXX_USE_RTC		(1 << 3)

काष्ठा mc13xxx_platक्रमm_data अणु
	अचिन्हित पूर्णांक flags;

	काष्ठा mc13xxx_regulator_platक्रमm_data regulators;
	काष्ठा mc13xxx_leds_platक्रमm_data *leds;
	काष्ठा mc13xxx_buttons_platक्रमm_data *buttons;
	काष्ठा mc13xxx_ts_platक्रमm_data touch;
	काष्ठा mc13xxx_codec_platक्रमm_data *codec;
पूर्ण;

#घोषणा MC13XXX_ADC_MODE_TS		1
#घोषणा MC13XXX_ADC_MODE_SINGLE_CHAN	2
#घोषणा MC13XXX_ADC_MODE_MULT_CHAN	3

#घोषणा MC13XXX_ADC0		43
#घोषणा MC13XXX_ADC0_LICELLCON		(1 << 0)
#घोषणा MC13XXX_ADC0_CHRGICON		(1 << 1)
#घोषणा MC13XXX_ADC0_BATICON		(1 << 2)
#घोषणा MC13XXX_ADC0_ADIN7SEL_DIE	(1 << 4)
#घोषणा MC13XXX_ADC0_ADIN7SEL_UID	(2 << 4)
#घोषणा MC13XXX_ADC0_ADREFEN		(1 << 10)
#घोषणा MC13XXX_ADC0_TSMOD0		(1 << 12)
#घोषणा MC13XXX_ADC0_TSMOD1		(1 << 13)
#घोषणा MC13XXX_ADC0_TSMOD2		(1 << 14)
#घोषणा MC13XXX_ADC0_CHRGRAWDIV		(1 << 15)
#घोषणा MC13XXX_ADC0_ADINC1		(1 << 16)
#घोषणा MC13XXX_ADC0_ADINC2		(1 << 17)

#घोषणा MC13XXX_ADC0_TSMOD_MASK		(MC13XXX_ADC0_TSMOD0 | \
					MC13XXX_ADC0_TSMOD1 | \
					MC13XXX_ADC0_TSMOD2)

#घोषणा MC13XXX_ADC0_CONFIG_MASK	(MC13XXX_ADC0_TSMOD_MASK | \
					MC13XXX_ADC0_LICELLCON | \
					MC13XXX_ADC0_CHRGICON | \
					MC13XXX_ADC0_BATICON)

#पूर्ण_अगर /* अगरndef __LINUX_MFD_MC13XXX_H */
