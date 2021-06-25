<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Base driver क्रम Maxim MAX8925
 *
 * Copyright (C) 2009-2010 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

अटल स्थिर काष्ठा resource bk_resources[] = अणु
	अणु 0x84, 0x84, "mode control", IORESOURCE_REG, पूर्ण,
	अणु 0x85, 0x85, "control",      IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell bk_devs[] = अणु
	अणु
		.name		= "max8925-backlight",
		.num_resources	= ARRAY_SIZE(bk_resources),
		.resources	= &bk_resources[0],
		.id		= -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource touch_resources[] = अणु
	अणु
		.name	= "max8925-tsc",
		.start	= MAX8925_TSC_IRQ,
		.end	= MAX8925_ADC_RES_END,
		.flags	= IORESOURCE_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell touch_devs[] = अणु
	अणु
		.name		= "max8925-touch",
		.num_resources	= 1,
		.resources	= &touch_resources[0],
		.id		= -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource घातer_supply_resources[] = अणु
	अणु
		.name	= "max8925-power",
		.start	= MAX8925_CHG_IRQ1,
		.end	= MAX8925_CHG_IRQ1_MASK,
		.flags	= IORESOURCE_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell घातer_devs[] = अणु
	अणु
		.name		= "max8925-power",
		.num_resources	= 1,
		.resources	= &घातer_supply_resources[0],
		.id		= -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource rtc_resources[] = अणु
	अणु
		.name	= "max8925-rtc",
		.start	= MAX8925_IRQ_RTC_ALARM0,
		.end	= MAX8925_IRQ_RTC_ALARM0,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rtc_devs[] = अणु
	अणु
		.name		= "max8925-rtc",
		.num_resources	= 1,
		.resources	= &rtc_resources[0],
		.id		= -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource onkey_resources[] = अणु
	अणु
		.name	= "max8925-onkey",
		.start	= MAX8925_IRQ_GPM_SW_R,
		.end	= MAX8925_IRQ_GPM_SW_R,
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.name	= "max8925-onkey",
		.start	= MAX8925_IRQ_GPM_SW_F,
		.end	= MAX8925_IRQ_GPM_SW_F,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell onkey_devs[] = अणु
	अणु
		.name		= "max8925-onkey",
		.num_resources	= 2,
		.resources	= &onkey_resources[0],
		.id		= -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sd1_resources[] = अणु
	अणु0x06, 0x06, "sdv", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sd2_resources[] = अणु
	अणु0x09, 0x09, "sdv", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource sd3_resources[] = अणु
	अणु0x0c, 0x0c, "sdv", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो1_resources[] = अणु
	अणु0x1a, 0x1a, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो2_resources[] = अणु
	अणु0x1e, 0x1e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो3_resources[] = अणु
	अणु0x22, 0x22, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो4_resources[] = अणु
	अणु0x26, 0x26, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो5_resources[] = अणु
	अणु0x2a, 0x2a, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो6_resources[] = अणु
	अणु0x2e, 0x2e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो7_resources[] = अणु
	अणु0x32, 0x32, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो8_resources[] = अणु
	अणु0x36, 0x36, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो9_resources[] = अणु
	अणु0x3a, 0x3a, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो10_resources[] = अणु
	अणु0x3e, 0x3e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो11_resources[] = अणु
	अणु0x42, 0x42, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो12_resources[] = अणु
	अणु0x46, 0x46, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो13_resources[] = अणु
	अणु0x4a, 0x4a, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो14_resources[] = अणु
	अणु0x4e, 0x4e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो15_resources[] = अणु
	अणु0x52, 0x52, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो16_resources[] = अणु
	अणु0x12, 0x12, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो17_resources[] = अणु
	अणु0x16, 0x16, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो18_resources[] = अणु
	अणु0x74, 0x74, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो19_resources[] = अणु
	अणु0x5e, 0x5e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource lकरो20_resources[] = अणु
	अणु0x9e, 0x9e, "ldov", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell reg_devs[] = अणु
	अणु
		.name = "max8925-regulator",
		.id = 0,
		.num_resources = ARRAY_SIZE(sd1_resources),
		.resources = sd1_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 1,
		.num_resources = ARRAY_SIZE(sd2_resources),
		.resources = sd2_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 2,
		.num_resources = ARRAY_SIZE(sd3_resources),
		.resources = sd3_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 3,
		.num_resources = ARRAY_SIZE(lकरो1_resources),
		.resources = lकरो1_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 4,
		.num_resources = ARRAY_SIZE(lकरो2_resources),
		.resources = lकरो2_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 5,
		.num_resources = ARRAY_SIZE(lकरो3_resources),
		.resources = lकरो3_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 6,
		.num_resources = ARRAY_SIZE(lकरो4_resources),
		.resources = lकरो4_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 7,
		.num_resources = ARRAY_SIZE(lकरो5_resources),
		.resources = lकरो5_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 8,
		.num_resources = ARRAY_SIZE(lकरो6_resources),
		.resources = lकरो6_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 9,
		.num_resources = ARRAY_SIZE(lकरो7_resources),
		.resources = lकरो7_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 10,
		.num_resources = ARRAY_SIZE(lकरो8_resources),
		.resources = lकरो8_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 11,
		.num_resources = ARRAY_SIZE(lकरो9_resources),
		.resources = lकरो9_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 12,
		.num_resources = ARRAY_SIZE(lकरो10_resources),
		.resources = lकरो10_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 13,
		.num_resources = ARRAY_SIZE(lकरो11_resources),
		.resources = lकरो11_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 14,
		.num_resources = ARRAY_SIZE(lकरो12_resources),
		.resources = lकरो12_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 15,
		.num_resources = ARRAY_SIZE(lकरो13_resources),
		.resources = lकरो13_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 16,
		.num_resources = ARRAY_SIZE(lकरो14_resources),
		.resources = lकरो14_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 17,
		.num_resources = ARRAY_SIZE(lकरो15_resources),
		.resources = lकरो15_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 18,
		.num_resources = ARRAY_SIZE(lकरो16_resources),
		.resources = lकरो16_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 19,
		.num_resources = ARRAY_SIZE(lकरो17_resources),
		.resources = lकरो17_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 20,
		.num_resources = ARRAY_SIZE(lकरो18_resources),
		.resources = lकरो18_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 21,
		.num_resources = ARRAY_SIZE(lकरो19_resources),
		.resources = lकरो19_resources,
	पूर्ण, अणु
		.name = "max8925-regulator",
		.id = 22,
		.num_resources = ARRAY_SIZE(lकरो20_resources),
		.resources = lकरो20_resources,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	FLAGS_ADC = 1,	/* रेजिस्टर in ADC component */
	FLAGS_RTC,	/* रेजिस्टर in RTC component */
पूर्ण;

काष्ठा max8925_irq_data अणु
	पूर्णांक	reg;
	पूर्णांक	mask_reg;
	पूर्णांक	enable;		/* enable or not */
	पूर्णांक	offs;		/* bit offset in mask रेजिस्टर */
	पूर्णांक	flags;
	पूर्णांक	tsc_irq;
पूर्ण;

अटल काष्ठा max8925_irq_data max8925_irqs[] = अणु
	[MAX8925_IRQ_VCHG_DC_OVP] = अणु
		.reg		= MAX8925_CHG_IRQ1,
		.mask_reg	= MAX8925_CHG_IRQ1_MASK,
		.offs		= 1 << 0,
	पूर्ण,
	[MAX8925_IRQ_VCHG_DC_F] = अणु
		.reg		= MAX8925_CHG_IRQ1,
		.mask_reg	= MAX8925_CHG_IRQ1_MASK,
		.offs		= 1 << 1,
	पूर्ण,
	[MAX8925_IRQ_VCHG_DC_R] = अणु
		.reg		= MAX8925_CHG_IRQ1,
		.mask_reg	= MAX8925_CHG_IRQ1_MASK,
		.offs		= 1 << 2,
	पूर्ण,
	[MAX8925_IRQ_VCHG_THM_OK_R] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 0,
	पूर्ण,
	[MAX8925_IRQ_VCHG_THM_OK_F] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 1,
	पूर्ण,
	[MAX8925_IRQ_VCHG_SYSLOW_F] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 2,
	पूर्ण,
	[MAX8925_IRQ_VCHG_SYSLOW_R] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 3,
	पूर्ण,
	[MAX8925_IRQ_VCHG_RST] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 4,
	पूर्ण,
	[MAX8925_IRQ_VCHG_DONE] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 5,
	पूर्ण,
	[MAX8925_IRQ_VCHG_TOPOFF] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 6,
	पूर्ण,
	[MAX8925_IRQ_VCHG_TMR_FAULT] = अणु
		.reg		= MAX8925_CHG_IRQ2,
		.mask_reg	= MAX8925_CHG_IRQ2_MASK,
		.offs		= 1 << 7,
	पूर्ण,
	[MAX8925_IRQ_GPM_RSTIN] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 0,
	पूर्ण,
	[MAX8925_IRQ_GPM_MPL] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 1,
	पूर्ण,
	[MAX8925_IRQ_GPM_SW_3SEC] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 2,
	पूर्ण,
	[MAX8925_IRQ_GPM_EXTON_F] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 3,
	पूर्ण,
	[MAX8925_IRQ_GPM_EXTON_R] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 4,
	पूर्ण,
	[MAX8925_IRQ_GPM_SW_1SEC] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 5,
	पूर्ण,
	[MAX8925_IRQ_GPM_SW_F] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 6,
	पूर्ण,
	[MAX8925_IRQ_GPM_SW_R] = अणु
		.reg		= MAX8925_ON_OFF_IRQ1,
		.mask_reg	= MAX8925_ON_OFF_IRQ1_MASK,
		.offs		= 1 << 7,
	पूर्ण,
	[MAX8925_IRQ_GPM_SYSCKEN_F] = अणु
		.reg		= MAX8925_ON_OFF_IRQ2,
		.mask_reg	= MAX8925_ON_OFF_IRQ2_MASK,
		.offs		= 1 << 0,
	पूर्ण,
	[MAX8925_IRQ_GPM_SYSCKEN_R] = अणु
		.reg		= MAX8925_ON_OFF_IRQ2,
		.mask_reg	= MAX8925_ON_OFF_IRQ2_MASK,
		.offs		= 1 << 1,
	पूर्ण,
	[MAX8925_IRQ_RTC_ALARM1] = अणु
		.reg		= MAX8925_RTC_IRQ,
		.mask_reg	= MAX8925_RTC_IRQ_MASK,
		.offs		= 1 << 2,
		.flags		= FLAGS_RTC,
	पूर्ण,
	[MAX8925_IRQ_RTC_ALARM0] = अणु
		.reg		= MAX8925_RTC_IRQ,
		.mask_reg	= MAX8925_RTC_IRQ_MASK,
		.offs		= 1 << 3,
		.flags		= FLAGS_RTC,
	पूर्ण,
	[MAX8925_IRQ_TSC_STICK] = अणु
		.reg		= MAX8925_TSC_IRQ,
		.mask_reg	= MAX8925_TSC_IRQ_MASK,
		.offs		= 1 << 0,
		.flags		= FLAGS_ADC,
		.tsc_irq	= 1,
	पूर्ण,
	[MAX8925_IRQ_TSC_NSTICK] = अणु
		.reg		= MAX8925_TSC_IRQ,
		.mask_reg	= MAX8925_TSC_IRQ_MASK,
		.offs		= 1 << 1,
		.flags		= FLAGS_ADC,
		.tsc_irq	= 1,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा max8925_irq_data *irq_to_max8925(काष्ठा max8925_chip *chip,
						      पूर्णांक irq)
अणु
	वापस &max8925_irqs[irq - chip->irq_base];
पूर्ण

अटल irqवापस_t max8925_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8925_chip *chip = data;
	काष्ठा max8925_irq_data *irq_data;
	काष्ठा i2c_client *i2c;
	पूर्णांक पढ़ो_reg = -1, value = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8925_irqs); i++) अणु
		irq_data = &max8925_irqs[i];
		/* TSC IRQ should be serviced in max8925_tsc_irq() */
		अगर (irq_data->tsc_irq)
			जारी;
		अगर (irq_data->flags == FLAGS_RTC)
			i2c = chip->rtc;
		अन्यथा अगर (irq_data->flags == FLAGS_ADC)
			i2c = chip->adc;
		अन्यथा
			i2c = chip->i2c;
		अगर (पढ़ो_reg != irq_data->reg) अणु
			पढ़ो_reg = irq_data->reg;
			value = max8925_reg_पढ़ो(i2c, irq_data->reg);
		पूर्ण
		अगर (value & irq_data->enable)
			handle_nested_irq(chip->irq_base + i);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max8925_tsc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8925_chip *chip = data;
	काष्ठा max8925_irq_data *irq_data;
	काष्ठा i2c_client *i2c;
	पूर्णांक पढ़ो_reg = -1, value = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8925_irqs); i++) अणु
		irq_data = &max8925_irqs[i];
		/* non TSC IRQ should be serviced in max8925_irq() */
		अगर (!irq_data->tsc_irq)
			जारी;
		अगर (irq_data->flags == FLAGS_RTC)
			i2c = chip->rtc;
		अन्यथा अगर (irq_data->flags == FLAGS_ADC)
			i2c = chip->adc;
		अन्यथा
			i2c = chip->i2c;
		अगर (पढ़ो_reg != irq_data->reg) अणु
			पढ़ो_reg = irq_data->reg;
			value = max8925_reg_पढ़ो(i2c, irq_data->reg);
		पूर्ण
		अगर (value & irq_data->enable)
			handle_nested_irq(chip->irq_base + i);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max8925_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा max8925_chip *chip = irq_data_get_irq_chip_data(data);

	mutex_lock(&chip->irq_lock);
पूर्ण

अटल व्योम max8925_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा max8925_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max8925_irq_data *irq_data;
	अटल अचिन्हित अक्षर cache_chg[2] = अणु0xff, 0xffपूर्ण;
	अटल अचिन्हित अक्षर cache_on[2] = अणु0xff, 0xffपूर्ण;
	अटल अचिन्हित अक्षर cache_rtc = 0xff, cache_tsc = 0xff;
	अचिन्हित अक्षर irq_chg[2], irq_on[2];
	अचिन्हित अक्षर irq_rtc, irq_tsc;
	पूर्णांक i;

	/* Load cached value. In initial, all IRQs are masked */
	irq_chg[0] = cache_chg[0];
	irq_chg[1] = cache_chg[1];
	irq_on[0] = cache_on[0];
	irq_on[1] = cache_on[1];
	irq_rtc = cache_rtc;
	irq_tsc = cache_tsc;
	क्रम (i = 0; i < ARRAY_SIZE(max8925_irqs); i++) अणु
		irq_data = &max8925_irqs[i];
		/* 1 -- disable, 0 -- enable */
		चयन (irq_data->mask_reg) अणु
		हाल MAX8925_CHG_IRQ1_MASK:
			irq_chg[0] &= ~irq_data->enable;
			अवरोध;
		हाल MAX8925_CHG_IRQ2_MASK:
			irq_chg[1] &= ~irq_data->enable;
			अवरोध;
		हाल MAX8925_ON_OFF_IRQ1_MASK:
			irq_on[0] &= ~irq_data->enable;
			अवरोध;
		हाल MAX8925_ON_OFF_IRQ2_MASK:
			irq_on[1] &= ~irq_data->enable;
			अवरोध;
		हाल MAX8925_RTC_IRQ_MASK:
			irq_rtc &= ~irq_data->enable;
			अवरोध;
		हाल MAX8925_TSC_IRQ_MASK:
			irq_tsc &= ~irq_data->enable;
			अवरोध;
		शेष:
			dev_err(chip->dev, "wrong IRQ\n");
			अवरोध;
		पूर्ण
	पूर्ण
	/* update mask पूर्णांकo रेजिस्टरs */
	अगर (cache_chg[0] != irq_chg[0]) अणु
		cache_chg[0] = irq_chg[0];
		max8925_reg_ग_लिखो(chip->i2c, MAX8925_CHG_IRQ1_MASK,
			irq_chg[0]);
	पूर्ण
	अगर (cache_chg[1] != irq_chg[1]) अणु
		cache_chg[1] = irq_chg[1];
		max8925_reg_ग_लिखो(chip->i2c, MAX8925_CHG_IRQ2_MASK,
			irq_chg[1]);
	पूर्ण
	अगर (cache_on[0] != irq_on[0]) अणु
		cache_on[0] = irq_on[0];
		max8925_reg_ग_लिखो(chip->i2c, MAX8925_ON_OFF_IRQ1_MASK,
				irq_on[0]);
	पूर्ण
	अगर (cache_on[1] != irq_on[1]) अणु
		cache_on[1] = irq_on[1];
		max8925_reg_ग_लिखो(chip->i2c, MAX8925_ON_OFF_IRQ2_MASK,
				irq_on[1]);
	पूर्ण
	अगर (cache_rtc != irq_rtc) अणु
		cache_rtc = irq_rtc;
		max8925_reg_ग_लिखो(chip->rtc, MAX8925_RTC_IRQ_MASK, irq_rtc);
	पूर्ण
	अगर (cache_tsc != irq_tsc) अणु
		cache_tsc = irq_tsc;
		max8925_reg_ग_लिखो(chip->adc, MAX8925_TSC_IRQ_MASK, irq_tsc);
	पूर्ण

	mutex_unlock(&chip->irq_lock);
पूर्ण

अटल व्योम max8925_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा max8925_chip *chip = irq_data_get_irq_chip_data(data);

	max8925_irqs[data->irq - chip->irq_base].enable
		= max8925_irqs[data->irq - chip->irq_base].offs;
पूर्ण

अटल व्योम max8925_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा max8925_chip *chip = irq_data_get_irq_chip_data(data);

	max8925_irqs[data->irq - chip->irq_base].enable = 0;
पूर्ण

अटल काष्ठा irq_chip max8925_irq_chip = अणु
	.name		= "max8925",
	.irq_bus_lock	= max8925_irq_lock,
	.irq_bus_sync_unlock = max8925_irq_sync_unlock,
	.irq_enable	= max8925_irq_enable,
	.irq_disable	= max8925_irq_disable,
पूर्ण;

अटल पूर्णांक max8925_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				 irq_hw_number_t hw)
अणु
	irq_set_chip_data(virq, d->host_data);
	irq_set_chip_and_handler(virq, &max8925_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops max8925_irq_करोमुख्य_ops = अणु
	.map	= max8925_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;


अटल पूर्णांक max8925_irq_init(काष्ठा max8925_chip *chip, पूर्णांक irq,
			    काष्ठा max8925_platक्रमm_data *pdata)
अणु
	अचिन्हित दीर्घ flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
	पूर्णांक ret;
	काष्ठा device_node *node = chip->dev->of_node;

	/* clear all पूर्णांकerrupts */
	max8925_reg_पढ़ो(chip->i2c, MAX8925_CHG_IRQ1);
	max8925_reg_पढ़ो(chip->i2c, MAX8925_CHG_IRQ2);
	max8925_reg_पढ़ो(chip->i2c, MAX8925_ON_OFF_IRQ1);
	max8925_reg_पढ़ो(chip->i2c, MAX8925_ON_OFF_IRQ2);
	max8925_reg_पढ़ो(chip->rtc, MAX8925_RTC_IRQ);
	max8925_reg_पढ़ो(chip->adc, MAX8925_TSC_IRQ);
	/* mask all पूर्णांकerrupts except क्रम TSC */
	max8925_reg_ग_लिखो(chip->rtc, MAX8925_ALARM0_CNTL, 0);
	max8925_reg_ग_लिखो(chip->rtc, MAX8925_ALARM1_CNTL, 0);
	max8925_reg_ग_लिखो(chip->i2c, MAX8925_CHG_IRQ1_MASK, 0xff);
	max8925_reg_ग_लिखो(chip->i2c, MAX8925_CHG_IRQ2_MASK, 0xff);
	max8925_reg_ग_लिखो(chip->i2c, MAX8925_ON_OFF_IRQ1_MASK, 0xff);
	max8925_reg_ग_लिखो(chip->i2c, MAX8925_ON_OFF_IRQ2_MASK, 0xff);
	max8925_reg_ग_लिखो(chip->rtc, MAX8925_RTC_IRQ_MASK, 0xff);

	mutex_init(&chip->irq_lock);
	chip->irq_base = irq_alloc_descs(-1, 0, MAX8925_NR_IRQS, 0);
	अगर (chip->irq_base < 0) अणु
		dev_err(chip->dev, "Failed to allocate interrupts, ret:%d\n",
			chip->irq_base);
		वापस -EBUSY;
	पूर्ण

	irq_करोमुख्य_add_legacy(node, MAX8925_NR_IRQS, chip->irq_base, 0,
			      &max8925_irq_करोमुख्य_ops, chip);

	/* request irq handler क्रम pmic मुख्य irq*/
	chip->core_irq = irq;
	अगर (!chip->core_irq)
		वापस -EBUSY;
	ret = request_thपढ़ोed_irq(irq, शून्य, max8925_irq, flags | IRQF_ONESHOT,
				   "max8925", chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to request core IRQ: %d\n", ret);
		chip->core_irq = 0;
		वापस -EBUSY;
	पूर्ण

	/* request irq handler क्रम pmic tsc irq*/

	/* mask TSC पूर्णांकerrupt */
	max8925_reg_ग_लिखो(chip->adc, MAX8925_TSC_IRQ_MASK, 0x0f);

	अगर (!pdata->tsc_irq) अणु
		dev_warn(chip->dev, "No interrupt support on TSC IRQ\n");
		वापस 0;
	पूर्ण
	chip->tsc_irq = pdata->tsc_irq;
	ret = request_thपढ़ोed_irq(chip->tsc_irq, शून्य, max8925_tsc_irq,
				   flags | IRQF_ONESHOT, "max8925-tsc", chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to request TSC IRQ: %d\n", ret);
		chip->tsc_irq = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_regulator(काष्ठा max8925_chip *chip,
				     काष्ठा max8925_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (!pdata)
		वापस;
	अगर (pdata->sd1) अणु
		reg_devs[0].platक्रमm_data = pdata->sd1;
		reg_devs[0].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->sd2) अणु
		reg_devs[1].platक्रमm_data = pdata->sd2;
		reg_devs[1].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->sd3) अणु
		reg_devs[2].platक्रमm_data = pdata->sd3;
		reg_devs[2].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो1) अणु
		reg_devs[3].platक्रमm_data = pdata->lकरो1;
		reg_devs[3].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो2) अणु
		reg_devs[4].platक्रमm_data = pdata->lकरो2;
		reg_devs[4].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो3) अणु
		reg_devs[5].platक्रमm_data = pdata->lकरो3;
		reg_devs[5].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो4) अणु
		reg_devs[6].platक्रमm_data = pdata->lकरो4;
		reg_devs[6].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो5) अणु
		reg_devs[7].platक्रमm_data = pdata->lकरो5;
		reg_devs[7].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो6) अणु
		reg_devs[8].platक्रमm_data = pdata->lकरो6;
		reg_devs[8].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो7) अणु
		reg_devs[9].platक्रमm_data = pdata->lकरो7;
		reg_devs[9].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो8) अणु
		reg_devs[10].platक्रमm_data = pdata->lकरो8;
		reg_devs[10].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो9) अणु
		reg_devs[11].platक्रमm_data = pdata->lकरो9;
		reg_devs[11].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो10) अणु
		reg_devs[12].platक्रमm_data = pdata->lकरो10;
		reg_devs[12].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो11) अणु
		reg_devs[13].platक्रमm_data = pdata->lकरो11;
		reg_devs[13].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो12) अणु
		reg_devs[14].platक्रमm_data = pdata->lकरो12;
		reg_devs[14].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो13) अणु
		reg_devs[15].platक्रमm_data = pdata->lकरो13;
		reg_devs[15].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो14) अणु
		reg_devs[16].platक्रमm_data = pdata->lकरो14;
		reg_devs[16].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो15) अणु
		reg_devs[17].platक्रमm_data = pdata->lकरो15;
		reg_devs[17].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो16) अणु
		reg_devs[18].platक्रमm_data = pdata->lकरो16;
		reg_devs[18].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो17) अणु
		reg_devs[19].platक्रमm_data = pdata->lकरो17;
		reg_devs[19].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो18) अणु
		reg_devs[20].platक्रमm_data = pdata->lकरो18;
		reg_devs[20].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो19) अणु
		reg_devs[21].platक्रमm_data = pdata->lकरो19;
		reg_devs[21].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो20) अणु
		reg_devs[22].platक्रमm_data = pdata->lकरो20;
		reg_devs[22].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, reg_devs, ARRAY_SIZE(reg_devs),
			      शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add regulator subdev\n");
		वापस;
	पूर्ण
पूर्ण

पूर्णांक max8925_device_init(काष्ठा max8925_chip *chip,
				  काष्ठा max8925_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	max8925_irq_init(chip, chip->i2c->irq, pdata);

	अगर (pdata && (pdata->घातer || pdata->touch)) अणु
		/* enable ADC to control पूर्णांकernal reference */
		max8925_set_bits(chip->i2c, MAX8925_RESET_CNFG, 1, 1);
		/* enable पूर्णांकernal reference क्रम ADC */
		max8925_set_bits(chip->adc, MAX8925_TSC_CNFG1, 3, 2);
		/* check क्रम पूर्णांकernal reference IRQ */
		करो अणु
			ret = max8925_reg_पढ़ो(chip->adc, MAX8925_TSC_IRQ);
		पूर्ण जबतक (ret & MAX8925_NREF_OK);
		/* enaable ADC scheduler, पूर्णांकerval is 1 second */
		max8925_set_bits(chip->adc, MAX8925_ADC_SCHED, 3, 2);
	पूर्ण

	/* enable Momentary Power Loss */
	max8925_set_bits(chip->rtc, MAX8925_MPL_CNTL, 1 << 4, 1 << 4);

	ret = mfd_add_devices(chip->dev, 0, &rtc_devs[0],
			      ARRAY_SIZE(rtc_devs),
			      शून्य, chip->irq_base, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add rtc subdev\n");
		जाओ out;
	पूर्ण

	ret = mfd_add_devices(chip->dev, 0, &onkey_devs[0],
			      ARRAY_SIZE(onkey_devs),
			      शून्य, chip->irq_base, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add onkey subdev\n");
		जाओ out_dev;
	पूर्ण

	init_regulator(chip, pdata);

	अगर (pdata && pdata->backlight) अणु
		bk_devs[0].platक्रमm_data = &pdata->backlight;
		bk_devs[0].pdata_size = माप(काष्ठा max8925_backlight_pdata);
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, bk_devs, ARRAY_SIZE(bk_devs),
			      शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add backlight subdev\n");
		जाओ out_dev;
	पूर्ण

	ret = mfd_add_devices(chip->dev, 0, &घातer_devs[0],
			      ARRAY_SIZE(घातer_devs),
			      शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev,
			"Failed to add power supply subdev, err = %d\n", ret);
		जाओ out_dev;
	पूर्ण

	अगर (pdata && pdata->touch) अणु
		ret = mfd_add_devices(chip->dev, 0, &touch_devs[0],
				      ARRAY_SIZE(touch_devs),
				      शून्य, chip->tsc_irq, शून्य);
		अगर (ret < 0) अणु
			dev_err(chip->dev, "Failed to add touch subdev\n");
			जाओ out_dev;
		पूर्ण
	पूर्ण

	वापस 0;
out_dev:
	mfd_हटाओ_devices(chip->dev);
out:
	वापस ret;
पूर्ण

व्योम max8925_device_निकास(काष्ठा max8925_chip *chip)
अणु
	अगर (chip->core_irq)
		मुक्त_irq(chip->core_irq, chip);
	अगर (chip->tsc_irq)
		मुक्त_irq(chip->tsc_irq, chip);
	mfd_हटाओ_devices(chip->dev);
पूर्ण
