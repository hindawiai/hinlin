<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * core.h  -- Core driver क्रम NXP PCF50633
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * All rights reserved.
 */

#अगर_अघोषित __LINUX_MFD_PCF50633_CORE_H
#घोषणा __LINUX_MFD_PCF50633_CORE_H

#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/pcf50633/backlight.h>

काष्ठा pcf50633;
काष्ठा regmap;

#घोषणा PCF50633_NUM_REGULATORS	11

काष्ठा pcf50633_platक्रमm_data अणु
	काष्ठा regulator_init_data reg_init_data[PCF50633_NUM_REGULATORS];

	अक्षर **batteries;
	पूर्णांक num_batteries;

	/*
	 * Should be set accordingly to the reference resistor used, see
	 * I_अणुch(ref)पूर्ण अक्षरger reference current in the pcf50633 User
	 * Manual.
	 */
	पूर्णांक अक्षरger_reference_current_ma;

	/* Callbacks */
	व्योम (*probe_करोne)(काष्ठा pcf50633 *);
	व्योम (*mbc_event_callback)(काष्ठा pcf50633 *, पूर्णांक);
	व्योम (*regulator_रेजिस्टरed)(काष्ठा pcf50633 *, पूर्णांक);
	व्योम (*क्रमce_shutकरोwn)(काष्ठा pcf50633 *);

	u8 resumers[5];

	काष्ठा pcf50633_bl_platक्रमm_data *backlight_data;
पूर्ण;

काष्ठा pcf50633_irq अणु
	व्योम (*handler) (पूर्णांक, व्योम *);
	व्योम *data;
पूर्ण;

पूर्णांक pcf50633_रेजिस्टर_irq(काष्ठा pcf50633 *pcf, पूर्णांक irq,
			व्योम (*handler) (पूर्णांक, व्योम *), व्योम *data);
पूर्णांक pcf50633_मुक्त_irq(काष्ठा pcf50633 *pcf, पूर्णांक irq);

पूर्णांक pcf50633_irq_mask(काष्ठा pcf50633 *pcf, पूर्णांक irq);
पूर्णांक pcf50633_irq_unmask(काष्ठा pcf50633 *pcf, पूर्णांक irq);
पूर्णांक pcf50633_irq_mask_get(काष्ठा pcf50633 *pcf, पूर्णांक irq);

पूर्णांक pcf50633_पढ़ो_block(काष्ठा pcf50633 *, u8 reg,
					पूर्णांक nr_regs, u8 *data);
पूर्णांक pcf50633_ग_लिखो_block(काष्ठा pcf50633 *pcf, u8 reg,
					पूर्णांक nr_regs, u8 *data);
u8 pcf50633_reg_पढ़ो(काष्ठा pcf50633 *, u8 reg);
पूर्णांक pcf50633_reg_ग_लिखो(काष्ठा pcf50633 *pcf, u8 reg, u8 val);

पूर्णांक pcf50633_reg_set_bit_mask(काष्ठा pcf50633 *pcf, u8 reg, u8 mask, u8 val);
पूर्णांक pcf50633_reg_clear_bits(काष्ठा pcf50633 *pcf, u8 reg, u8 bits);

/* Interrupt रेजिस्टरs */

#घोषणा PCF50633_REG_INT1	0x02
#घोषणा PCF50633_REG_INT2	0x03
#घोषणा PCF50633_REG_INT3	0x04
#घोषणा PCF50633_REG_INT4	0x05
#घोषणा PCF50633_REG_INT5	0x06

#घोषणा PCF50633_REG_INT1M	0x07
#घोषणा PCF50633_REG_INT2M	0x08
#घोषणा PCF50633_REG_INT3M	0x09
#घोषणा PCF50633_REG_INT4M	0x0a
#घोषणा PCF50633_REG_INT5M	0x0b

क्रमागत अणु
	/* Chip IRQs */
	PCF50633_IRQ_ADPINS,
	PCF50633_IRQ_ADPREM,
	PCF50633_IRQ_USBINS,
	PCF50633_IRQ_USBREM,
	PCF50633_IRQ_RESERVED1,
	PCF50633_IRQ_RESERVED2,
	PCF50633_IRQ_ALARM,
	PCF50633_IRQ_SECOND,
	PCF50633_IRQ_ONKEYR,
	PCF50633_IRQ_ONKEYF,
	PCF50633_IRQ_EXTON1R,
	PCF50633_IRQ_EXTON1F,
	PCF50633_IRQ_EXTON2R,
	PCF50633_IRQ_EXTON2F,
	PCF50633_IRQ_EXTON3R,
	PCF50633_IRQ_EXTON3F,
	PCF50633_IRQ_BATFULL,
	PCF50633_IRQ_CHGHALT,
	PCF50633_IRQ_THLIMON,
	PCF50633_IRQ_THLIMOFF,
	PCF50633_IRQ_USBLIMON,
	PCF50633_IRQ_USBLIMOFF,
	PCF50633_IRQ_ADCRDY,
	PCF50633_IRQ_ONKEY1S,
	PCF50633_IRQ_LOWSYS,
	PCF50633_IRQ_LOWBAT,
	PCF50633_IRQ_HIGHTMP,
	PCF50633_IRQ_AUTOPWRFAIL,
	PCF50633_IRQ_DWN1PWRFAIL,
	PCF50633_IRQ_DWN2PWRFAIL,
	PCF50633_IRQ_LEDPWRFAIL,
	PCF50633_IRQ_LEDOVP,
	PCF50633_IRQ_LDO1PWRFAIL,
	PCF50633_IRQ_LDO2PWRFAIL,
	PCF50633_IRQ_LDO3PWRFAIL,
	PCF50633_IRQ_LDO4PWRFAIL,
	PCF50633_IRQ_LDO5PWRFAIL,
	PCF50633_IRQ_LDO6PWRFAIL,
	PCF50633_IRQ_HCLDOPWRFAIL,
	PCF50633_IRQ_HCLDOOVL,

	/* Always last */
	PCF50633_NUM_IRQ,
पूर्ण;

काष्ठा pcf50633 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	काष्ठा pcf50633_platक्रमm_data *pdata;
	पूर्णांक irq;
	काष्ठा pcf50633_irq irq_handler[PCF50633_NUM_IRQ];
	काष्ठा work_काष्ठा irq_work;
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा mutex lock;

	u8 mask_regs[5];

	u8 suspend_irq_masks[5];
	u8 resume_reason[5];
	पूर्णांक is_suspended;

	पूर्णांक onkey1s_held;

	काष्ठा platक्रमm_device *rtc_pdev;
	काष्ठा platक्रमm_device *mbc_pdev;
	काष्ठा platक्रमm_device *adc_pdev;
	काष्ठा platक्रमm_device *input_pdev;
	काष्ठा platक्रमm_device *bl_pdev;
	काष्ठा platक्रमm_device *regulator_pdev[PCF50633_NUM_REGULATORS];
पूर्ण;

क्रमागत pcf50633_reg_पूर्णांक1 अणु
	PCF50633_INT1_ADPINS	= 0x01,	/* Adapter inserted */
	PCF50633_INT1_ADPREM	= 0x02,	/* Adapter हटाओd */
	PCF50633_INT1_USBINS	= 0x04,	/* USB inserted */
	PCF50633_INT1_USBREM	= 0x08,	/* USB हटाओd */
	/* reserved */
	PCF50633_INT1_ALARM	= 0x40, /* RTC alarm समय is reached */
	PCF50633_INT1_SECOND	= 0x80,	/* RTC periodic second पूर्णांकerrupt */
पूर्ण;

क्रमागत pcf50633_reg_पूर्णांक2 अणु
	PCF50633_INT2_ONKEYR	= 0x01, /* ONKEY rising edge */
	PCF50633_INT2_ONKEYF	= 0x02, /* ONKEY falling edge */
	PCF50633_INT2_EXTON1R	= 0x04, /* EXTON1 rising edge */
	PCF50633_INT2_EXTON1F	= 0x08, /* EXTON1 falling edge */
	PCF50633_INT2_EXTON2R	= 0x10, /* EXTON2 rising edge */
	PCF50633_INT2_EXTON2F	= 0x20, /* EXTON2 falling edge */
	PCF50633_INT2_EXTON3R	= 0x40, /* EXTON3 rising edge */
	PCF50633_INT2_EXTON3F	= 0x80, /* EXTON3 falling edge */
पूर्ण;

क्रमागत pcf50633_reg_पूर्णांक3 अणु
	PCF50633_INT3_BATFULL	= 0x01, /* Battery full */
	PCF50633_INT3_CHGHALT	= 0x02,	/* Charger halt */
	PCF50633_INT3_THLIMON	= 0x04,
	PCF50633_INT3_THLIMOFF	= 0x08,
	PCF50633_INT3_USBLIMON	= 0x10,
	PCF50633_INT3_USBLIMOFF	= 0x20,
	PCF50633_INT3_ADCRDY	= 0x40, /* ADC result पढ़ोy */
	PCF50633_INT3_ONKEY1S	= 0x80,	/* ONKEY pressed 1 second */
पूर्ण;

क्रमागत pcf50633_reg_पूर्णांक4 अणु
	PCF50633_INT4_LOWSYS		= 0x01,
	PCF50633_INT4_LOWBAT		= 0x02,
	PCF50633_INT4_HIGHTMP		= 0x04,
	PCF50633_INT4_AUTOPWRFAIL	= 0x08,
	PCF50633_INT4_DWN1PWRFAIL	= 0x10,
	PCF50633_INT4_DWN2PWRFAIL	= 0x20,
	PCF50633_INT4_LEDPWRFAIL	= 0x40,
	PCF50633_INT4_LEDOVP		= 0x80,
पूर्ण;

क्रमागत pcf50633_reg_पूर्णांक5 अणु
	PCF50633_INT5_LDO1PWRFAIL	= 0x01,
	PCF50633_INT5_LDO2PWRFAIL	= 0x02,
	PCF50633_INT5_LDO3PWRFAIL	= 0x04,
	PCF50633_INT5_LDO4PWRFAIL	= 0x08,
	PCF50633_INT5_LDO5PWRFAIL	= 0x10,
	PCF50633_INT5_LDO6PWRFAIL	= 0x20,
	PCF50633_INT5_HCLDOPWRFAIL	= 0x40,
	PCF50633_INT5_HCLDOOVL		= 0x80,
पूर्ण;

/* misc. रेजिस्टरs */
#घोषणा PCF50633_REG_OOCSHDWN	0x0c

/* LED रेजिस्टरs */
#घोषणा PCF50633_REG_LEDOUT 0x28
#घोषणा PCF50633_REG_LEDENA 0x29
#घोषणा PCF50633_REG_LEDCTL 0x2a
#घोषणा PCF50633_REG_LEDDIM 0x2b

अटल अंतरभूत काष्ठा pcf50633 *dev_to_pcf50633(काष्ठा device *dev)
अणु
	वापस dev_get_drvdata(dev);
पूर्ण

पूर्णांक pcf50633_irq_init(काष्ठा pcf50633 *pcf, पूर्णांक irq);
व्योम pcf50633_irq_मुक्त(काष्ठा pcf50633 *pcf);
#अगर_घोषित CONFIG_PM
पूर्णांक pcf50633_irq_suspend(काष्ठा pcf50633 *pcf);
पूर्णांक pcf50633_irq_resume(काष्ठा pcf50633 *pcf);
#पूर्ण_अगर

#पूर्ण_अगर
