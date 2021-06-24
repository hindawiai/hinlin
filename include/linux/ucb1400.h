<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definitions and functions क्रम:
 *  Philips UCB1400 driver
 *
 * Based on ucb1400_ts:
 *  Author:	Nicolas Pitre
 *  Created:	September 25, 2006
 *  Copyright:	MontaVista Software, Inc.
 *
 * Spliting करोne by: Marek Vasut <marek.vasut@gmail.com>
 * If something करोesn't work and it worked beक्रमe spliting, e-mail me,
 * करोnt bother Nicolas please ;-)
 *
 * This code is heavily based on ucb1x00-*.c copyrighted by Russell King
 * covering the UCB1100, UCB1200 and UCB1300..  Support क्रम the UCB1400 has
 * been made separate from ucb1x00-core/ucb1x00-ts on Russell's request.
 */

#अगर_अघोषित _LINUX__UCB1400_H
#घोषणा _LINUX__UCB1400_H

#समावेश <sound/ac97_codec.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

/*
 * UCB1400 AC-link रेजिस्टरs
 */

#घोषणा UCB_IO_DATA		0x5a
#घोषणा UCB_IO_सूची		0x5c
#घोषणा UCB_IE_RIS		0x5e
#घोषणा UCB_IE_FAL		0x60
#घोषणा UCB_IE_STATUS		0x62
#घोषणा UCB_IE_CLEAR		0x62
#घोषणा UCB_IE_ADC		(1 << 11)
#घोषणा UCB_IE_TSPX		(1 << 12)

#घोषणा UCB_TS_CR		0x64
#घोषणा UCB_TS_CR_TSMX_POW	(1 << 0)
#घोषणा UCB_TS_CR_TSPX_POW	(1 << 1)
#घोषणा UCB_TS_CR_TSMY_POW	(1 << 2)
#घोषणा UCB_TS_CR_TSPY_POW	(1 << 3)
#घोषणा UCB_TS_CR_TSMX_GND	(1 << 4)
#घोषणा UCB_TS_CR_TSPX_GND	(1 << 5)
#घोषणा UCB_TS_CR_TSMY_GND	(1 << 6)
#घोषणा UCB_TS_CR_TSPY_GND	(1 << 7)
#घोषणा UCB_TS_CR_MODE_INT	(0 << 8)
#घोषणा UCB_TS_CR_MODE_PRES	(1 << 8)
#घोषणा UCB_TS_CR_MODE_POS	(2 << 8)
#घोषणा UCB_TS_CR_BIAS_ENA	(1 << 11)
#घोषणा UCB_TS_CR_TSPX_LOW	(1 << 12)
#घोषणा UCB_TS_CR_TSMX_LOW	(1 << 13)

#घोषणा UCB_ADC_CR		0x66
#घोषणा UCB_ADC_SYNC_ENA	(1 << 0)
#घोषणा UCB_ADC_VREFBYP_CON	(1 << 1)
#घोषणा UCB_ADC_INP_TSPX	(0 << 2)
#घोषणा UCB_ADC_INP_TSMX	(1 << 2)
#घोषणा UCB_ADC_INP_TSPY	(2 << 2)
#घोषणा UCB_ADC_INP_TSMY	(3 << 2)
#घोषणा UCB_ADC_INP_AD0		(4 << 2)
#घोषणा UCB_ADC_INP_AD1		(5 << 2)
#घोषणा UCB_ADC_INP_AD2		(6 << 2)
#घोषणा UCB_ADC_INP_AD3		(7 << 2)
#घोषणा UCB_ADC_EXT_REF		(1 << 5)
#घोषणा UCB_ADC_START		(1 << 7)
#घोषणा UCB_ADC_ENA		(1 << 15)

#घोषणा UCB_ADC_DATA		0x68
#घोषणा UCB_ADC_DAT_VALID	(1 << 15)

#घोषणा UCB_FCSR		0x6c
#घोषणा UCB_FCSR_AVE		(1 << 12)

#घोषणा UCB_ADC_DAT_MASK	0x3ff

#घोषणा UCB_ID			0x7e
#घोषणा UCB_ID_1400             0x4304

काष्ठा ucb1400_gpio अणु
	काष्ठा gpio_chip	gc;
	काष्ठा snd_ac97		*ac97;
	पूर्णांक			gpio_offset;
	पूर्णांक			(*gpio_setup)(काष्ठा device *dev, पूर्णांक ngpio);
	पूर्णांक			(*gpio_tearकरोwn)(काष्ठा device *dev, पूर्णांक ngpio);
पूर्ण;

काष्ठा ucb1400_ts अणु
	काष्ठा input_dev	*ts_idev;
	पूर्णांक			id;
	पूर्णांक			irq;
	काष्ठा snd_ac97		*ac97;
	रुको_queue_head_t	ts_रुको;
	bool			stopped;
पूर्ण;

काष्ठा ucb1400 अणु
	काष्ठा platक्रमm_device	*ucb1400_ts;
	काष्ठा platक्रमm_device	*ucb1400_gpio;
पूर्ण;

काष्ठा ucb1400_pdata अणु
	पूर्णांक	irq;
	पूर्णांक	gpio_offset;
	पूर्णांक	(*gpio_setup)(काष्ठा device *dev, पूर्णांक ngpio);
	पूर्णांक	(*gpio_tearकरोwn)(काष्ठा device *dev, पूर्णांक ngpio);
पूर्ण;

अटल अंतरभूत u16 ucb1400_reg_पढ़ो(काष्ठा snd_ac97 *ac97, u16 reg)
अणु
	वापस ac97->bus->ops->पढ़ो(ac97, reg);
पूर्ण

अटल अंतरभूत व्योम ucb1400_reg_ग_लिखो(काष्ठा snd_ac97 *ac97, u16 reg, u16 val)
अणु
	ac97->bus->ops->ग_लिखो(ac97, reg, val);
पूर्ण

अटल अंतरभूत u16 ucb1400_gpio_get_value(काष्ठा snd_ac97 *ac97, u16 gpio)
अणु
	वापस ucb1400_reg_पढ़ो(ac97, UCB_IO_DATA) & (1 << gpio);
पूर्ण

अटल अंतरभूत व्योम ucb1400_gpio_set_value(काष्ठा snd_ac97 *ac97, u16 gpio,
						u16 val)
अणु
	ucb1400_reg_ग_लिखो(ac97, UCB_IO_DATA, val ?
			ucb1400_reg_पढ़ो(ac97, UCB_IO_DATA) | (1 << gpio) :
			ucb1400_reg_पढ़ो(ac97, UCB_IO_DATA) & ~(1 << gpio));
पूर्ण

अटल अंतरभूत u16 ucb1400_gpio_get_direction(काष्ठा snd_ac97 *ac97, u16 gpio)
अणु
	वापस ucb1400_reg_पढ़ो(ac97, UCB_IO_सूची) & (1 << gpio);
पूर्ण

अटल अंतरभूत व्योम ucb1400_gpio_set_direction(काष्ठा snd_ac97 *ac97, u16 gpio,
						u16 dir)
अणु
	ucb1400_reg_ग_लिखो(ac97, UCB_IO_सूची, dir ?
			ucb1400_reg_पढ़ो(ac97, UCB_IO_सूची) | (1 << gpio) :
			ucb1400_reg_पढ़ो(ac97, UCB_IO_सूची) & ~(1 << gpio));
पूर्ण

अटल अंतरभूत व्योम ucb1400_adc_enable(काष्ठा snd_ac97 *ac97)
अणु
	ucb1400_reg_ग_लिखो(ac97, UCB_ADC_CR, UCB_ADC_ENA);
पूर्ण

अटल अंतरभूत व्योम ucb1400_adc_disable(काष्ठा snd_ac97 *ac97)
अणु
	ucb1400_reg_ग_लिखो(ac97, UCB_ADC_CR, 0);
पूर्ण


अचिन्हित पूर्णांक ucb1400_adc_पढ़ो(काष्ठा snd_ac97 *ac97, u16 adc_channel,
			      पूर्णांक adcsync);

#पूर्ण_अगर
