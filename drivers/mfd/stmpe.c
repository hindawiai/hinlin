<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST Microelectronics MFD: sपंचांगpe's driver
 *
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश "stmpe.h"

/**
 * काष्ठा sपंचांगpe_platक्रमm_data - STMPE platक्रमm data
 * @id: device id to distinguish between multiple STMPEs on the same board
 * @blocks: biपंचांगask of blocks to enable (use STMPE_BLOCK_*)
 * @irq_trigger: IRQ trigger to use क्रम the पूर्णांकerrupt to the host
 * @स्वतःsleep: bool to enable/disable sपंचांगpe स्वतःsleep
 * @स्वतःsleep_समयout: inactivity समयout in milliseconds क्रम स्वतःsleep
 * @irq_over_gpio: true अगर gpio is used to get irq
 * @irq_gpio: gpio number over which irq will be requested (signअगरicant only अगर
 *	      irq_over_gpio is true)
 */
काष्ठा sपंचांगpe_platक्रमm_data अणु
	पूर्णांक id;
	अचिन्हित पूर्णांक blocks;
	अचिन्हित पूर्णांक irq_trigger;
	bool स्वतःsleep;
	bool irq_over_gpio;
	पूर्णांक irq_gpio;
	पूर्णांक स्वतःsleep_समयout;
पूर्ण;

अटल पूर्णांक __sपंचांगpe_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks)
अणु
	वापस sपंचांगpe->variant->enable(sपंचांगpe, blocks, true);
पूर्ण

अटल पूर्णांक __sपंचांगpe_disable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks)
अणु
	वापस sपंचांगpe->variant->enable(sपंचांगpe, blocks, false);
पूर्ण

अटल पूर्णांक __sपंचांगpe_reg_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg)
अणु
	पूर्णांक ret;

	ret = sपंचांगpe->ci->पढ़ो_byte(sपंचांगpe, reg);
	अगर (ret < 0)
		dev_err(sपंचांगpe->dev, "failed to read reg %#x: %d\n", reg, ret);

	dev_vdbg(sपंचांगpe->dev, "rd: reg %#x => data %#x\n", reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __sपंचांगpe_reg_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	dev_vdbg(sपंचांगpe->dev, "wr: reg %#x <= %#x\n", reg, val);

	ret = sपंचांगpe->ci->ग_लिखो_byte(sपंचांगpe, reg, val);
	अगर (ret < 0)
		dev_err(sपंचांगpe->dev, "failed to write reg %#x: %d\n", reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __sपंचांगpe_set_bits(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = __sपंचांगpe_reg_पढ़ो(sपंचांगpe, reg);
	अगर (ret < 0)
		वापस ret;

	ret &= ~mask;
	ret |= val;

	वापस __sपंचांगpe_reg_ग_लिखो(sपंचांगpe, reg, ret);
पूर्ण

अटल पूर्णांक __sपंचांगpe_block_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
			      u8 *values)
अणु
	पूर्णांक ret;

	ret = sपंचांगpe->ci->पढ़ो_block(sपंचांगpe, reg, length, values);
	अगर (ret < 0)
		dev_err(sपंचांगpe->dev, "failed to read regs %#x: %d\n", reg, ret);

	dev_vdbg(sपंचांगpe->dev, "rd: reg %#x (%d) => ret %#x\n", reg, length, ret);
	sपंचांगpe_dump_bytes("stmpe rd: ", values, length);

	वापस ret;
पूर्ण

अटल पूर्णांक __sपंचांगpe_block_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
			स्थिर u8 *values)
अणु
	पूर्णांक ret;

	dev_vdbg(sपंचांगpe->dev, "wr: regs %#x (%d)\n", reg, length);
	sपंचांगpe_dump_bytes("stmpe wr: ", values, length);

	ret = sपंचांगpe->ci->ग_लिखो_block(sपंचांगpe, reg, length, values);
	अगर (ret < 0)
		dev_err(sपंचांगpe->dev, "failed to write regs %#x: %d\n", reg, ret);

	वापस ret;
पूर्ण

/**
 * sपंचांगpe_enable - enable blocks on an STMPE device
 * @sपंचांगpe:	Device to work on
 * @blocks:	Mask of blocks (क्रमागत sपंचांगpe_block values) to enable
 */
पूर्णांक sपंचांगpe_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_enable(sपंचांगpe, blocks);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_enable);

/**
 * sपंचांगpe_disable - disable blocks on an STMPE device
 * @sपंचांगpe:	Device to work on
 * @blocks:	Mask of blocks (क्रमागत sपंचांगpe_block values) to enable
 */
पूर्णांक sपंचांगpe_disable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_disable(sपंचांगpe, blocks);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_disable);

/**
 * sपंचांगpe_reg_पढ़ो() - पढ़ो a single STMPE रेजिस्टर
 * @sपंचांगpe:	Device to पढ़ो from
 * @reg:	Register to पढ़ो
 */
पूर्णांक sपंचांगpe_reg_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_reg_पढ़ो(sपंचांगpe, reg);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_reg_पढ़ो);

/**
 * sपंचांगpe_reg_ग_लिखो() - ग_लिखो a single STMPE रेजिस्टर
 * @sपंचांगpe:	Device to ग_लिखो to
 * @reg:	Register to ग_लिखो
 * @val:	Value to ग_लिखो
 */
पूर्णांक sपंचांगpe_reg_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_reg_ग_लिखो(sपंचांगpe, reg, val);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_reg_ग_लिखो);

/**
 * sपंचांगpe_set_bits() - set the value of a bitfield in a STMPE रेजिस्टर
 * @sपंचांगpe:	Device to ग_लिखो to
 * @reg:	Register to ग_लिखो
 * @mask:	Mask of bits to set
 * @val:	Value to set
 */
पूर्णांक sपंचांगpe_set_bits(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_set_bits(sपंचांगpe, reg, mask, val);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_set_bits);

/**
 * sपंचांगpe_block_पढ़ो() - पढ़ो multiple STMPE रेजिस्टरs
 * @sपंचांगpe:	Device to पढ़ो from
 * @reg:	First रेजिस्टर
 * @length:	Number of रेजिस्टरs
 * @values:	Buffer to ग_लिखो to
 */
पूर्णांक sपंचांगpe_block_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length, u8 *values)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_block_पढ़ो(sपंचांगpe, reg, length, values);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_block_पढ़ो);

/**
 * sपंचांगpe_block_ग_लिखो() - ग_लिखो multiple STMPE रेजिस्टरs
 * @sपंचांगpe:	Device to ग_लिखो to
 * @reg:	First रेजिस्टर
 * @length:	Number of रेजिस्टरs
 * @values:	Values to ग_लिखो
 */
पूर्णांक sपंचांगpe_block_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
		      स्थिर u8 *values)
अणु
	पूर्णांक ret;

	mutex_lock(&sपंचांगpe->lock);
	ret = __sपंचांगpe_block_ग_लिखो(sपंचांगpe, reg, length, values);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_block_ग_लिखो);

/**
 * sपंचांगpe_set_altfunc()- set the alternate function क्रम STMPE pins
 * @sपंचांगpe:	Device to configure
 * @pins:	Biपंचांगask of pins to affect
 * @block:	block to enable alternate functions क्रम
 *
 * @pins is assumed to have a bit set क्रम each of the bits whose alternate
 * function is to be changed, numbered according to the GPIOXY numbers.
 *
 * If the GPIO module is not enabled, this function स्वतःmatically enables it in
 * order to perक्रमm the change.
 */
पूर्णांक sपंचांगpe_set_altfunc(काष्ठा sपंचांगpe *sपंचांगpe, u32 pins, क्रमागत sपंचांगpe_block block)
अणु
	काष्ठा sपंचांगpe_variant_info *variant = sपंचांगpe->variant;
	u8 regaddr = sपंचांगpe->regs[STMPE_IDX_GPAFR_U_MSB];
	पूर्णांक af_bits = variant->af_bits;
	पूर्णांक numregs = DIV_ROUND_UP(sपंचांगpe->num_gpios * af_bits, 8);
	पूर्णांक mask = (1 << af_bits) - 1;
	u8 regs[8];
	पूर्णांक af, afperreg, ret;

	अगर (!variant->get_altfunc)
		वापस 0;

	afperreg = 8 / af_bits;
	mutex_lock(&sपंचांगpe->lock);

	ret = __sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_GPIO);
	अगर (ret < 0)
		जाओ out;

	ret = __sपंचांगpe_block_पढ़ो(sपंचांगpe, regaddr, numregs, regs);
	अगर (ret < 0)
		जाओ out;

	af = variant->get_altfunc(sपंचांगpe, block);

	जबतक (pins) अणु
		पूर्णांक pin = __ffs(pins);
		पूर्णांक regoffset = numregs - (pin / afperreg) - 1;
		पूर्णांक pos = (pin % afperreg) * (8 / afperreg);

		regs[regoffset] &= ~(mask << pos);
		regs[regoffset] |= af << pos;

		pins &= ~(1 << pin);
	पूर्ण

	ret = __sपंचांगpe_block_ग_लिखो(sपंचांगpe, regaddr, numregs, regs);

out:
	mutex_unlock(&sपंचांगpe->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe_set_altfunc);

/*
 * GPIO (all variants)
 */

अटल काष्ठा resource sपंचांगpe_gpio_resources[] = अणु
	/* Start and end filled dynamically */
	अणु
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_gpio_cell = अणु
	.name		= "stmpe-gpio",
	.of_compatible	= "st,stmpe-gpio",
	.resources	= sपंचांगpe_gpio_resources,
	.num_resources	= ARRAY_SIZE(sपंचांगpe_gpio_resources),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_gpio_cell_noirq = अणु
	.name		= "stmpe-gpio",
	.of_compatible	= "st,stmpe-gpio",
	/* gpio cell resources consist of an irq only so no resources here */
पूर्ण;

/*
 * Keypad (1601, 2401, 2403)
 */

अटल काष्ठा resource sपंचांगpe_keypad_resources[] = अणु
	/* Start and end filled dynamically */
	अणु
		.name	= "KEYPAD",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "KEYPAD_OVER",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_keypad_cell = अणु
	.name		= "stmpe-keypad",
	.of_compatible  = "st,stmpe-keypad",
	.resources	= sपंचांगpe_keypad_resources,
	.num_resources	= ARRAY_SIZE(sपंचांगpe_keypad_resources),
पूर्ण;

/*
 * PWM (1601, 2401, 2403)
 */
अटल काष्ठा resource sपंचांगpe_pwm_resources[] = अणु
	/* Start and end filled dynamically */
	अणु
		.name	= "PWM0",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "PWM1",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "PWM2",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_pwm_cell = अणु
	.name		= "stmpe-pwm",
	.of_compatible  = "st,stmpe-pwm",
	.resources	= sपंचांगpe_pwm_resources,
	.num_resources	= ARRAY_SIZE(sपंचांगpe_pwm_resources),
पूर्ण;

/*
 * STMPE801
 */
अटल स्थिर u8 sपंचांगpe801_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE801_REG_CHIP_ID,
	[STMPE_IDX_ICR_LSB]	= STMPE801_REG_SYS_CTRL,
	[STMPE_IDX_GPMR_LSB]	= STMPE801_REG_GPIO_MP_STA,
	[STMPE_IDX_GPSR_LSB]	= STMPE801_REG_GPIO_SET_PIN,
	[STMPE_IDX_GPCR_LSB]	= STMPE801_REG_GPIO_SET_PIN,
	[STMPE_IDX_GPDR_LSB]	= STMPE801_REG_GPIO_सूची,
	[STMPE_IDX_IEGPIOR_LSB] = STMPE801_REG_GPIO_INT_EN,
	[STMPE_IDX_ISGPIOR_MSB] = STMPE801_REG_GPIO_INT_STA,

पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe801_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= 0,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe801_blocks_noirq[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell_noirq,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांगpe801_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			   bool enable)
अणु
	अगर (blocks & STMPE_BLOCK_GPIO)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe801 = अणु
	.name		= "stmpe801",
	.id_val		= STMPE801_ID,
	.id_mask	= 0xffff,
	.num_gpios	= 8,
	.regs		= sपंचांगpe801_regs,
	.blocks		= sपंचांगpe801_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe801_blocks),
	.num_irqs	= STMPE801_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe801_enable,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe801_noirq = अणु
	.name		= "stmpe801",
	.id_val		= STMPE801_ID,
	.id_mask	= 0xffff,
	.num_gpios	= 8,
	.regs		= sपंचांगpe801_regs,
	.blocks		= sपंचांगpe801_blocks_noirq,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe801_blocks_noirq),
	.enable		= sपंचांगpe801_enable,
पूर्ण;

/*
 * Touchscreen (STMPE811 or STMPE610)
 */

अटल काष्ठा resource sपंचांगpe_ts_resources[] = अणु
	/* Start and end filled dynamically */
	अणु
		.name	= "TOUCH_DET",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "FIFO_TH",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_ts_cell = अणु
	.name		= "stmpe-ts",
	.of_compatible	= "st,stmpe-ts",
	.resources	= sपंचांगpe_ts_resources,
	.num_resources	= ARRAY_SIZE(sपंचांगpe_ts_resources),
पूर्ण;

/*
 * ADC (STMPE811)
 */

अटल काष्ठा resource sपंचांगpe_adc_resources[] = अणु
	/* Start and end filled dynamically */
	अणु
		.name	= "STMPE_TEMP_SENS",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "STMPE_ADC",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell sपंचांगpe_adc_cell = अणु
	.name		= "stmpe-adc",
	.of_compatible	= "st,stmpe-adc",
	.resources	= sपंचांगpe_adc_resources,
	.num_resources	= ARRAY_SIZE(sपंचांगpe_adc_resources),
पूर्ण;

/*
 * STMPE811 or STMPE610
 */

अटल स्थिर u8 sपंचांगpe811_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE811_REG_CHIP_ID,
	[STMPE_IDX_SYS_CTRL]	= STMPE811_REG_SYS_CTRL,
	[STMPE_IDX_SYS_CTRL2]	= STMPE811_REG_SYS_CTRL2,
	[STMPE_IDX_ICR_LSB]	= STMPE811_REG_INT_CTRL,
	[STMPE_IDX_IER_LSB]	= STMPE811_REG_INT_EN,
	[STMPE_IDX_ISR_MSB]	= STMPE811_REG_INT_STA,
	[STMPE_IDX_GPMR_LSB]	= STMPE811_REG_GPIO_MP_STA,
	[STMPE_IDX_GPSR_LSB]	= STMPE811_REG_GPIO_SET_PIN,
	[STMPE_IDX_GPCR_LSB]	= STMPE811_REG_GPIO_CLR_PIN,
	[STMPE_IDX_GPDR_LSB]	= STMPE811_REG_GPIO_सूची,
	[STMPE_IDX_GPRER_LSB]	= STMPE811_REG_GPIO_RE,
	[STMPE_IDX_GPFER_LSB]	= STMPE811_REG_GPIO_FE,
	[STMPE_IDX_GPAFR_U_MSB]	= STMPE811_REG_GPIO_AF,
	[STMPE_IDX_IEGPIOR_LSB]	= STMPE811_REG_GPIO_INT_EN,
	[STMPE_IDX_ISGPIOR_MSB]	= STMPE811_REG_GPIO_INT_STA,
	[STMPE_IDX_GPEDR_LSB]	= STMPE811_REG_GPIO_ED,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe811_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= STMPE811_IRQ_GPIOC,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_ts_cell,
		.irq	= STMPE811_IRQ_TOUCH_DET,
		.block	= STMPE_BLOCK_TOUCHSCREEN,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_adc_cell,
		.irq	= STMPE811_IRQ_TEMP_SENS,
		.block	= STMPE_BLOCK_ADC,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांगpe811_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			   bool enable)
अणु
	अचिन्हित पूर्णांक mask = 0;

	अगर (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE811_SYS_CTRL2_GPIO_OFF;

	अगर (blocks & STMPE_BLOCK_ADC)
		mask |= STMPE811_SYS_CTRL2_ADC_OFF;

	अगर (blocks & STMPE_BLOCK_TOUCHSCREEN)
		mask |= STMPE811_SYS_CTRL2_TSC_OFF;

	वापस __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL2], mask,
				enable ? 0 : mask);
पूर्ण

पूर्णांक sपंचांगpe811_adc_common_init(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	पूर्णांक ret;
	u8 adc_ctrl1, adc_ctrl1_mask;

	adc_ctrl1 = STMPE_SAMPLE_TIME(sपंचांगpe->sample_समय) |
		    STMPE_MOD_12B(sपंचांगpe->mod_12b) |
		    STMPE_REF_SEL(sपंचांगpe->ref_sel);
	adc_ctrl1_mask = STMPE_SAMPLE_TIME(0xff) | STMPE_MOD_12B(0xff) |
			 STMPE_REF_SEL(0xff);

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE811_REG_ADC_CTRL1,
			adc_ctrl1_mask, adc_ctrl1);
	अगर (ret) अणु
		dev_err(sपंचांगpe->dev, "Could not setup ADC\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE811_REG_ADC_CTRL2,
			STMPE_ADC_FREQ(0xff), STMPE_ADC_FREQ(sपंचांगpe->adc_freq));
	अगर (ret) अणु
		dev_err(sपंचांगpe->dev, "Could not setup ADC\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगpe811_adc_common_init);

अटल पूर्णांक sपंचांगpe811_get_altfunc(काष्ठा sपंचांगpe *sपंचांगpe, क्रमागत sपंचांगpe_block block)
अणु
	/* 0 क्रम touchscreen, 1 क्रम GPIO */
	वापस block != STMPE_BLOCK_TOUCHSCREEN;
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe811 = अणु
	.name		= "stmpe811",
	.id_val		= 0x0811,
	.id_mask	= 0xffff,
	.num_gpios	= 8,
	.af_bits	= 1,
	.regs		= sपंचांगpe811_regs,
	.blocks		= sपंचांगpe811_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe811_blocks),
	.num_irqs	= STMPE811_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe811_enable,
	.get_altfunc	= sपंचांगpe811_get_altfunc,
पूर्ण;

/* Similar to 811, except number of gpios */
अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe610 = अणु
	.name		= "stmpe610",
	.id_val		= 0x0811,
	.id_mask	= 0xffff,
	.num_gpios	= 6,
	.af_bits	= 1,
	.regs		= sपंचांगpe811_regs,
	.blocks		= sपंचांगpe811_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe811_blocks),
	.num_irqs	= STMPE811_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe811_enable,
	.get_altfunc	= sपंचांगpe811_get_altfunc,
पूर्ण;

/*
 * STMPE1600
 * Compared to all others STMPE variant, LSB and MSB regs are located in this
 * order :	LSB   addr
 *		MSB   addr + 1
 * As there is only 2 * 8bits रेजिस्टरs क्रम GPMR/GPSR/IEGPIOPR, CSB index is MSB रेजिस्टरs
 */

अटल स्थिर u8 sपंचांगpe1600_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE1600_REG_CHIP_ID,
	[STMPE_IDX_SYS_CTRL]	= STMPE1600_REG_SYS_CTRL,
	[STMPE_IDX_ICR_LSB]	= STMPE1600_REG_SYS_CTRL,
	[STMPE_IDX_GPMR_LSB]	= STMPE1600_REG_GPMR_LSB,
	[STMPE_IDX_GPMR_CSB]	= STMPE1600_REG_GPMR_MSB,
	[STMPE_IDX_GPSR_LSB]	= STMPE1600_REG_GPSR_LSB,
	[STMPE_IDX_GPSR_CSB]	= STMPE1600_REG_GPSR_MSB,
	[STMPE_IDX_GPCR_LSB]	= STMPE1600_REG_GPSR_LSB,
	[STMPE_IDX_GPCR_CSB]	= STMPE1600_REG_GPSR_MSB,
	[STMPE_IDX_GPDR_LSB]	= STMPE1600_REG_GPDR_LSB,
	[STMPE_IDX_GPDR_CSB]	= STMPE1600_REG_GPDR_MSB,
	[STMPE_IDX_IEGPIOR_LSB]	= STMPE1600_REG_IEGPIOR_LSB,
	[STMPE_IDX_IEGPIOR_CSB]	= STMPE1600_REG_IEGPIOR_MSB,
	[STMPE_IDX_ISGPIOR_LSB]	= STMPE1600_REG_ISGPIOR_LSB,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe1600_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= 0,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांगpe1600_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			   bool enable)
अणु
	अगर (blocks & STMPE_BLOCK_GPIO)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe1600 = अणु
	.name		= "stmpe1600",
	.id_val		= STMPE1600_ID,
	.id_mask	= 0xffff,
	.num_gpios	= 16,
	.af_bits	= 0,
	.regs		= sपंचांगpe1600_regs,
	.blocks		= sपंचांगpe1600_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe1600_blocks),
	.num_irqs	= STMPE1600_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe1600_enable,
पूर्ण;

/*
 * STMPE1601
 */

अटल स्थिर u8 sपंचांगpe1601_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE1601_REG_CHIP_ID,
	[STMPE_IDX_SYS_CTRL]	= STMPE1601_REG_SYS_CTRL,
	[STMPE_IDX_SYS_CTRL2]	= STMPE1601_REG_SYS_CTRL2,
	[STMPE_IDX_ICR_LSB]	= STMPE1601_REG_ICR_LSB,
	[STMPE_IDX_IER_MSB]	= STMPE1601_REG_IER_MSB,
	[STMPE_IDX_IER_LSB]	= STMPE1601_REG_IER_LSB,
	[STMPE_IDX_ISR_MSB]	= STMPE1601_REG_ISR_MSB,
	[STMPE_IDX_GPMR_LSB]	= STMPE1601_REG_GPIO_MP_LSB,
	[STMPE_IDX_GPMR_CSB]	= STMPE1601_REG_GPIO_MP_MSB,
	[STMPE_IDX_GPSR_LSB]	= STMPE1601_REG_GPIO_SET_LSB,
	[STMPE_IDX_GPSR_CSB]	= STMPE1601_REG_GPIO_SET_MSB,
	[STMPE_IDX_GPCR_LSB]	= STMPE1601_REG_GPIO_CLR_LSB,
	[STMPE_IDX_GPCR_CSB]	= STMPE1601_REG_GPIO_CLR_MSB,
	[STMPE_IDX_GPDR_LSB]	= STMPE1601_REG_GPIO_SET_सूची_LSB,
	[STMPE_IDX_GPDR_CSB]	= STMPE1601_REG_GPIO_SET_सूची_MSB,
	[STMPE_IDX_GPEDR_LSB]	= STMPE1601_REG_GPIO_ED_LSB,
	[STMPE_IDX_GPEDR_CSB]	= STMPE1601_REG_GPIO_ED_MSB,
	[STMPE_IDX_GPRER_LSB]	= STMPE1601_REG_GPIO_RE_LSB,
	[STMPE_IDX_GPRER_CSB]	= STMPE1601_REG_GPIO_RE_MSB,
	[STMPE_IDX_GPFER_LSB]	= STMPE1601_REG_GPIO_FE_LSB,
	[STMPE_IDX_GPFER_CSB]	= STMPE1601_REG_GPIO_FE_MSB,
	[STMPE_IDX_GPPUR_LSB]	= STMPE1601_REG_GPIO_PU_LSB,
	[STMPE_IDX_GPAFR_U_MSB]	= STMPE1601_REG_GPIO_AF_U_MSB,
	[STMPE_IDX_IEGPIOR_LSB]	= STMPE1601_REG_INT_EN_GPIO_MASK_LSB,
	[STMPE_IDX_IEGPIOR_CSB]	= STMPE1601_REG_INT_EN_GPIO_MASK_MSB,
	[STMPE_IDX_ISGPIOR_MSB]	= STMPE1601_REG_INT_STA_GPIO_MSB,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe1601_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= STMPE1601_IRQ_GPIOC,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_keypad_cell,
		.irq	= STMPE1601_IRQ_KEYPAD,
		.block	= STMPE_BLOCK_KEYPAD,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_pwm_cell,
		.irq	= STMPE1601_IRQ_PWM0,
		.block	= STMPE_BLOCK_PWM,
	पूर्ण,
पूर्ण;

/* supported स्वतःsleep समयout delay (in msecs) */
अटल स्थिर पूर्णांक sपंचांगpe_स्वतःsleep_delay[] = अणु
	4, 16, 32, 64, 128, 256, 512, 1024,
पूर्ण;

अटल पूर्णांक sपंचांगpe_round_समयout(पूर्णांक समयout)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांगpe_स्वतःsleep_delay); i++) अणु
		अगर (sपंचांगpe_स्वतःsleep_delay[i] >= समयout)
			वापस i;
	पूर्ण

	/*
	 * requests क्रम delays दीर्घer than supported should not वापस the
	 * दीर्घest supported delay
	 */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांगpe_स्वतःsleep(काष्ठा sपंचांगpe *sपंचांगpe, पूर्णांक स्वतःsleep_समयout)
अणु
	पूर्णांक ret;

	अगर (!sपंचांगpe->variant->enable_स्वतःsleep)
		वापस -ENOSYS;

	mutex_lock(&sपंचांगpe->lock);
	ret = sपंचांगpe->variant->enable_स्वतःsleep(sपंचांगpe, स्वतःsleep_समयout);
	mutex_unlock(&sपंचांगpe->lock);

	वापस ret;
पूर्ण

/*
 * Both sपंचांगpe 1601/2403 support same layout क्रम स्वतःsleep
 */
अटल पूर्णांक sपंचांगpe1601_स्वतःsleep(काष्ठा sपंचांगpe *sपंचांगpe,
		पूर्णांक स्वतःsleep_समयout)
अणु
	पूर्णांक ret, समयout;

	/* choose the best available समयout */
	समयout = sपंचांगpe_round_समयout(स्वतःsleep_समयout);
	अगर (समयout < 0) अणु
		dev_err(sपंचांगpe->dev, "invalid timeout\n");
		वापस समयout;
	पूर्ण

	ret = __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL2],
			STMPE1601_AUTOSLEEP_TIMEOUT_MASK,
			समयout);
	अगर (ret < 0)
		वापस ret;

	वापस __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL2],
			STPME1601_AUTOSLEEP_ENABLE,
			STPME1601_AUTOSLEEP_ENABLE);
पूर्ण

अटल पूर्णांक sपंचांगpe1601_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			    bool enable)
अणु
	अचिन्हित पूर्णांक mask = 0;

	अगर (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE1601_SYS_CTRL_ENABLE_GPIO;
	अन्यथा
		mask &= ~STMPE1601_SYS_CTRL_ENABLE_GPIO;

	अगर (blocks & STMPE_BLOCK_KEYPAD)
		mask |= STMPE1601_SYS_CTRL_ENABLE_KPC;
	अन्यथा
		mask &= ~STMPE1601_SYS_CTRL_ENABLE_KPC;

	अगर (blocks & STMPE_BLOCK_PWM)
		mask |= STMPE1601_SYS_CTRL_ENABLE_SPWM;
	अन्यथा
		mask &= ~STMPE1601_SYS_CTRL_ENABLE_SPWM;

	वापस __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL], mask,
				enable ? mask : 0);
पूर्ण

अटल पूर्णांक sपंचांगpe1601_get_altfunc(काष्ठा sपंचांगpe *sपंचांगpe, क्रमागत sपंचांगpe_block block)
अणु
	चयन (block) अणु
	हाल STMPE_BLOCK_PWM:
		वापस 2;

	हाल STMPE_BLOCK_KEYPAD:
		वापस 1;

	हाल STMPE_BLOCK_GPIO:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe1601 = अणु
	.name		= "stmpe1601",
	.id_val		= 0x0210,
	.id_mask	= 0xfff0,	/* at least 0x0210 and 0x0212 */
	.num_gpios	= 16,
	.af_bits	= 2,
	.regs		= sपंचांगpe1601_regs,
	.blocks		= sपंचांगpe1601_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe1601_blocks),
	.num_irqs	= STMPE1601_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe1601_enable,
	.get_altfunc	= sपंचांगpe1601_get_altfunc,
	.enable_स्वतःsleep	= sपंचांगpe1601_स्वतःsleep,
पूर्ण;

/*
 * STMPE1801
 */
अटल स्थिर u8 sपंचांगpe1801_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE1801_REG_CHIP_ID,
	[STMPE_IDX_SYS_CTRL]	= STMPE1801_REG_SYS_CTRL,
	[STMPE_IDX_ICR_LSB]	= STMPE1801_REG_INT_CTRL_LOW,
	[STMPE_IDX_IER_LSB]	= STMPE1801_REG_INT_EN_MASK_LOW,
	[STMPE_IDX_ISR_LSB]	= STMPE1801_REG_INT_STA_LOW,
	[STMPE_IDX_GPMR_LSB]	= STMPE1801_REG_GPIO_MP_LOW,
	[STMPE_IDX_GPMR_CSB]	= STMPE1801_REG_GPIO_MP_MID,
	[STMPE_IDX_GPMR_MSB]	= STMPE1801_REG_GPIO_MP_HIGH,
	[STMPE_IDX_GPSR_LSB]	= STMPE1801_REG_GPIO_SET_LOW,
	[STMPE_IDX_GPSR_CSB]	= STMPE1801_REG_GPIO_SET_MID,
	[STMPE_IDX_GPSR_MSB]	= STMPE1801_REG_GPIO_SET_HIGH,
	[STMPE_IDX_GPCR_LSB]	= STMPE1801_REG_GPIO_CLR_LOW,
	[STMPE_IDX_GPCR_CSB]	= STMPE1801_REG_GPIO_CLR_MID,
	[STMPE_IDX_GPCR_MSB]	= STMPE1801_REG_GPIO_CLR_HIGH,
	[STMPE_IDX_GPDR_LSB]	= STMPE1801_REG_GPIO_SET_सूची_LOW,
	[STMPE_IDX_GPDR_CSB]	= STMPE1801_REG_GPIO_SET_सूची_MID,
	[STMPE_IDX_GPDR_MSB]	= STMPE1801_REG_GPIO_SET_सूची_HIGH,
	[STMPE_IDX_GPRER_LSB]	= STMPE1801_REG_GPIO_RE_LOW,
	[STMPE_IDX_GPRER_CSB]	= STMPE1801_REG_GPIO_RE_MID,
	[STMPE_IDX_GPRER_MSB]	= STMPE1801_REG_GPIO_RE_HIGH,
	[STMPE_IDX_GPFER_LSB]	= STMPE1801_REG_GPIO_FE_LOW,
	[STMPE_IDX_GPFER_CSB]	= STMPE1801_REG_GPIO_FE_MID,
	[STMPE_IDX_GPFER_MSB]	= STMPE1801_REG_GPIO_FE_HIGH,
	[STMPE_IDX_GPPUR_LSB]	= STMPE1801_REG_GPIO_PULL_UP_LOW,
	[STMPE_IDX_IEGPIOR_LSB]	= STMPE1801_REG_INT_EN_GPIO_MASK_LOW,
	[STMPE_IDX_IEGPIOR_CSB]	= STMPE1801_REG_INT_EN_GPIO_MASK_MID,
	[STMPE_IDX_IEGPIOR_MSB]	= STMPE1801_REG_INT_EN_GPIO_MASK_HIGH,
	[STMPE_IDX_ISGPIOR_MSB]	= STMPE1801_REG_INT_STA_GPIO_HIGH,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe1801_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= STMPE1801_IRQ_GPIOC,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_keypad_cell,
		.irq	= STMPE1801_IRQ_KEYPAD,
		.block	= STMPE_BLOCK_KEYPAD,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांगpe1801_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			    bool enable)
अणु
	अचिन्हित पूर्णांक mask = 0;
	अगर (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE1801_MSK_INT_EN_GPIO;

	अगर (blocks & STMPE_BLOCK_KEYPAD)
		mask |= STMPE1801_MSK_INT_EN_KPC;

	वापस __sपंचांगpe_set_bits(sपंचांगpe, STMPE1801_REG_INT_EN_MASK_LOW, mask,
				enable ? mask : 0);
पूर्ण

अटल पूर्णांक sपंचांगpe_reset(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	u16 id_val = sपंचांगpe->variant->id_val;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;
	u8 reset_bit;

	अगर (id_val == STMPE811_ID)
		/* STMPE801 and STMPE610 use bit 1 of SYS_CTRL रेजिस्टर */
		reset_bit = STMPE811_SYS_CTRL_RESET;
	अन्यथा
		/* all other STMPE variant use bit 7 of SYS_CTRL रेजिस्टर */
		reset_bit = STMPE_SYS_CTRL_RESET;

	ret = __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL],
			       reset_bit, reset_bit);
	अगर (ret < 0)
		वापस ret;

	msleep(10);

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ret = __sपंचांगpe_reg_पढ़ो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL]);
		अगर (ret < 0)
			वापस ret;
		अगर (!(ret & reset_bit))
			वापस 0;
		usleep_range(100, 200);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe1801 = अणु
	.name		= "stmpe1801",
	.id_val		= STMPE1801_ID,
	.id_mask	= 0xfff0,
	.num_gpios	= 18,
	.af_bits	= 0,
	.regs		= sपंचांगpe1801_regs,
	.blocks		= sपंचांगpe1801_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe1801_blocks),
	.num_irqs	= STMPE1801_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe1801_enable,
	/* sपंचांगpe1801 करो not have any gpio alternate function */
	.get_altfunc	= शून्य,
पूर्ण;

/*
 * STMPE24XX
 */

अटल स्थिर u8 sपंचांगpe24xx_regs[] = अणु
	[STMPE_IDX_CHIP_ID]	= STMPE24XX_REG_CHIP_ID,
	[STMPE_IDX_SYS_CTRL]	= STMPE24XX_REG_SYS_CTRL,
	[STMPE_IDX_SYS_CTRL2]	= STMPE24XX_REG_SYS_CTRL2,
	[STMPE_IDX_ICR_LSB]	= STMPE24XX_REG_ICR_LSB,
	[STMPE_IDX_IER_MSB]	= STMPE24XX_REG_IER_MSB,
	[STMPE_IDX_IER_LSB]	= STMPE24XX_REG_IER_LSB,
	[STMPE_IDX_ISR_MSB]	= STMPE24XX_REG_ISR_MSB,
	[STMPE_IDX_GPMR_LSB]	= STMPE24XX_REG_GPMR_LSB,
	[STMPE_IDX_GPMR_CSB]	= STMPE24XX_REG_GPMR_CSB,
	[STMPE_IDX_GPMR_MSB]	= STMPE24XX_REG_GPMR_MSB,
	[STMPE_IDX_GPSR_LSB]	= STMPE24XX_REG_GPSR_LSB,
	[STMPE_IDX_GPSR_CSB]	= STMPE24XX_REG_GPSR_CSB,
	[STMPE_IDX_GPSR_MSB]	= STMPE24XX_REG_GPSR_MSB,
	[STMPE_IDX_GPCR_LSB]	= STMPE24XX_REG_GPCR_LSB,
	[STMPE_IDX_GPCR_CSB]	= STMPE24XX_REG_GPCR_CSB,
	[STMPE_IDX_GPCR_MSB]	= STMPE24XX_REG_GPCR_MSB,
	[STMPE_IDX_GPDR_LSB]	= STMPE24XX_REG_GPDR_LSB,
	[STMPE_IDX_GPDR_CSB]	= STMPE24XX_REG_GPDR_CSB,
	[STMPE_IDX_GPDR_MSB]	= STMPE24XX_REG_GPDR_MSB,
	[STMPE_IDX_GPRER_LSB]	= STMPE24XX_REG_GPRER_LSB,
	[STMPE_IDX_GPRER_CSB]	= STMPE24XX_REG_GPRER_CSB,
	[STMPE_IDX_GPRER_MSB]	= STMPE24XX_REG_GPRER_MSB,
	[STMPE_IDX_GPFER_LSB]	= STMPE24XX_REG_GPFER_LSB,
	[STMPE_IDX_GPFER_CSB]	= STMPE24XX_REG_GPFER_CSB,
	[STMPE_IDX_GPFER_MSB]	= STMPE24XX_REG_GPFER_MSB,
	[STMPE_IDX_GPPUR_LSB]	= STMPE24XX_REG_GPPUR_LSB,
	[STMPE_IDX_GPPDR_LSB]	= STMPE24XX_REG_GPPDR_LSB,
	[STMPE_IDX_GPAFR_U_MSB]	= STMPE24XX_REG_GPAFR_U_MSB,
	[STMPE_IDX_IEGPIOR_LSB]	= STMPE24XX_REG_IEGPIOR_LSB,
	[STMPE_IDX_IEGPIOR_CSB]	= STMPE24XX_REG_IEGPIOR_CSB,
	[STMPE_IDX_IEGPIOR_MSB]	= STMPE24XX_REG_IEGPIOR_MSB,
	[STMPE_IDX_ISGPIOR_MSB]	= STMPE24XX_REG_ISGPIOR_MSB,
	[STMPE_IDX_GPEDR_LSB]	= STMPE24XX_REG_GPEDR_LSB,
	[STMPE_IDX_GPEDR_CSB]	= STMPE24XX_REG_GPEDR_CSB,
	[STMPE_IDX_GPEDR_MSB]	= STMPE24XX_REG_GPEDR_MSB,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_block sपंचांगpe24xx_blocks[] = अणु
	अणु
		.cell	= &sपंचांगpe_gpio_cell,
		.irq	= STMPE24XX_IRQ_GPIOC,
		.block	= STMPE_BLOCK_GPIO,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_keypad_cell,
		.irq	= STMPE24XX_IRQ_KEYPAD,
		.block	= STMPE_BLOCK_KEYPAD,
	पूर्ण,
	अणु
		.cell	= &sपंचांगpe_pwm_cell,
		.irq	= STMPE24XX_IRQ_PWM0,
		.block	= STMPE_BLOCK_PWM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांगpe24xx_enable(काष्ठा sपंचांगpe *sपंचांगpe, अचिन्हित पूर्णांक blocks,
			    bool enable)
अणु
	अचिन्हित पूर्णांक mask = 0;

	अगर (blocks & STMPE_BLOCK_GPIO)
		mask |= STMPE24XX_SYS_CTRL_ENABLE_GPIO;

	अगर (blocks & STMPE_BLOCK_KEYPAD)
		mask |= STMPE24XX_SYS_CTRL_ENABLE_KPC;

	वापस __sपंचांगpe_set_bits(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_SYS_CTRL], mask,
				enable ? mask : 0);
पूर्ण

अटल पूर्णांक sपंचांगpe24xx_get_altfunc(काष्ठा sपंचांगpe *sपंचांगpe, क्रमागत sपंचांगpe_block block)
अणु
	चयन (block) अणु
	हाल STMPE_BLOCK_ROTATOR:
		वापस 2;

	हाल STMPE_BLOCK_KEYPAD:
	हाल STMPE_BLOCK_PWM:
		वापस 1;

	हाल STMPE_BLOCK_GPIO:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe2401 = अणु
	.name		= "stmpe2401",
	.id_val		= 0x0101,
	.id_mask	= 0xffff,
	.num_gpios	= 24,
	.af_bits	= 2,
	.regs		= sपंचांगpe24xx_regs,
	.blocks		= sपंचांगpe24xx_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe24xx_blocks),
	.num_irqs	= STMPE24XX_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe24xx_enable,
	.get_altfunc	= sपंचांगpe24xx_get_altfunc,
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_info sपंचांगpe2403 = अणु
	.name		= "stmpe2403",
	.id_val		= 0x0120,
	.id_mask	= 0xffff,
	.num_gpios	= 24,
	.af_bits	= 2,
	.regs		= sपंचांगpe24xx_regs,
	.blocks		= sपंचांगpe24xx_blocks,
	.num_blocks	= ARRAY_SIZE(sपंचांगpe24xx_blocks),
	.num_irqs	= STMPE24XX_NR_INTERNAL_IRQS,
	.enable		= sपंचांगpe24xx_enable,
	.get_altfunc	= sपंचांगpe24xx_get_altfunc,
	.enable_स्वतःsleep	= sपंचांगpe1601_स्वतःsleep, /* same as sपंचांगpe1601 */
पूर्ण;

अटल काष्ठा sपंचांगpe_variant_info *sपंचांगpe_variant_info[STMPE_NBR_PARTS] = अणु
	[STMPE610]	= &sपंचांगpe610,
	[STMPE801]	= &sपंचांगpe801,
	[STMPE811]	= &sपंचांगpe811,
	[STMPE1600]	= &sपंचांगpe1600,
	[STMPE1601]	= &sपंचांगpe1601,
	[STMPE1801]	= &sपंचांगpe1801,
	[STMPE2401]	= &sपंचांगpe2401,
	[STMPE2403]	= &sपंचांगpe2403,
पूर्ण;

/*
 * These devices can be connected in a 'no-irq' configuration - the irq pin
 * is not used and the device cannot पूर्णांकerrupt the CPU. Here we only list
 * devices which support this configuration - the driver will fail probing
 * क्रम any devices not listed here which are configured in this way.
 */
अटल काष्ठा sपंचांगpe_variant_info *sपंचांगpe_noirq_variant_info[STMPE_NBR_PARTS] = अणु
	[STMPE801]	= &sपंचांगpe801_noirq,
पूर्ण;

अटल irqवापस_t sपंचांगpe_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = data;
	काष्ठा sपंचांगpe_variant_info *variant = sपंचांगpe->variant;
	पूर्णांक num = DIV_ROUND_UP(variant->num_irqs, 8);
	u8 israddr;
	u8 isr[3];
	पूर्णांक ret;
	पूर्णांक i;

	अगर (variant->id_val == STMPE801_ID ||
	    variant->id_val == STMPE1600_ID) अणु
		पूर्णांक base = irq_create_mapping(sपंचांगpe->करोमुख्य, 0);

		handle_nested_irq(base);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (variant->id_val == STMPE1801_ID)
		israddr = sपंचांगpe->regs[STMPE_IDX_ISR_LSB];
	अन्यथा
		israddr = sपंचांगpe->regs[STMPE_IDX_ISR_MSB];

	ret = sपंचांगpe_block_पढ़ो(sपंचांगpe, israddr, num, isr);
	अगर (ret < 0)
		वापस IRQ_NONE;

	क्रम (i = 0; i < num; i++) अणु
		पूर्णांक bank = num - i - 1;
		u8 status = isr[i];
		u8 clear;

		status &= sपंचांगpe->ier[bank];
		अगर (!status)
			जारी;

		clear = status;
		जबतक (status) अणु
			पूर्णांक bit = __ffs(status);
			पूर्णांक line = bank * 8 + bit;
			पूर्णांक nestedirq = irq_create_mapping(sपंचांगpe->करोमुख्य, line);

			handle_nested_irq(nestedirq);
			status &= ~(1 << bit);
		पूर्ण

		sपंचांगpe_reg_ग_लिखो(sपंचांगpe, israddr + i, clear);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांगpe_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = irq_data_get_irq_chip_data(data);

	mutex_lock(&sपंचांगpe->irq_lock);
पूर्ण

अटल व्योम sपंचांगpe_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = irq_data_get_irq_chip_data(data);
	काष्ठा sपंचांगpe_variant_info *variant = sपंचांगpe->variant;
	पूर्णांक num = DIV_ROUND_UP(variant->num_irqs, 8);
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		u8 new = sपंचांगpe->ier[i];
		u8 old = sपंचांगpe->oldier[i];

		अगर (new == old)
			जारी;

		sपंचांगpe->oldier[i] = new;
		sपंचांगpe_reg_ग_लिखो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_IER_LSB + i], new);
	पूर्ण

	mutex_unlock(&sपंचांगpe->irq_lock);
पूर्ण

अटल व्योम sपंचांगpe_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = irq_data_get_irq_chip_data(data);
	पूर्णांक offset = data->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = 1 << (offset % 8);

	sपंचांगpe->ier[regoffset] &= ~mask;
पूर्ण

अटल व्योम sपंचांगpe_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = irq_data_get_irq_chip_data(data);
	पूर्णांक offset = data->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = 1 << (offset % 8);

	sपंचांगpe->ier[regoffset] |= mask;
पूर्ण

अटल काष्ठा irq_chip sपंचांगpe_irq_chip = अणु
	.name			= "stmpe",
	.irq_bus_lock		= sपंचांगpe_irq_lock,
	.irq_bus_sync_unlock	= sपंचांगpe_irq_sync_unlock,
	.irq_mask		= sपंचांगpe_irq_mask,
	.irq_unmask		= sपंचांगpe_irq_unmask,
पूर्ण;

अटल पूर्णांक sपंचांगpe_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
                                irq_hw_number_t hwirq)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = d->host_data;
	काष्ठा irq_chip *chip = शून्य;

	अगर (sपंचांगpe->variant->id_val != STMPE801_ID)
		chip = &sपंचांगpe_irq_chip;

	irq_set_chip_data(virq, sपंचांगpe);
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल व्योम sपंचांगpe_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
		irq_set_chip_and_handler(virq, शून्य, शून्य);
		irq_set_chip_data(virq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sपंचांगpe_irq_ops = अणु
        .map    = sपंचांगpe_irq_map,
        .unmap  = sपंचांगpe_irq_unmap,
        .xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक sपंचांगpe_irq_init(काष्ठा sपंचांगpe *sपंचांगpe, काष्ठा device_node *np)
अणु
	पूर्णांक base = 0;
	पूर्णांक num_irqs = sपंचांगpe->variant->num_irqs;

	sपंचांगpe->करोमुख्य = irq_करोमुख्य_add_simple(np, num_irqs, base,
					      &sपंचांगpe_irq_ops, sपंचांगpe);
	अगर (!sपंचांगpe->करोमुख्य) अणु
		dev_err(sपंचांगpe->dev, "Failed to create irqdomain\n");
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_chip_init(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	अचिन्हित पूर्णांक irq_trigger = sपंचांगpe->pdata->irq_trigger;
	पूर्णांक स्वतःsleep_समयout = sपंचांगpe->pdata->स्वतःsleep_समयout;
	काष्ठा sपंचांगpe_variant_info *variant = sपंचांगpe->variant;
	u8 icr = 0;
	अचिन्हित पूर्णांक id;
	u8 data[2];
	पूर्णांक ret;

	ret = sपंचांगpe_block_पढ़ो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_CHIP_ID],
			       ARRAY_SIZE(data), data);
	अगर (ret < 0)
		वापस ret;

	id = (data[0] << 8) | data[1];
	अगर ((id & variant->id_mask) != variant->id_val) अणु
		dev_err(sपंचांगpe->dev, "unknown chip id: %#x\n", id);
		वापस -EINVAL;
	पूर्ण

	dev_info(sपंचांगpe->dev, "%s detected, chip id: %#x\n", variant->name, id);

	/* Disable all modules -- subdrivers should enable what they need. */
	ret = sपंचांगpe_disable(sपंचांगpe, ~0);
	अगर (ret)
		वापस ret;

	ret =  sपंचांगpe_reset(sपंचांगpe);
	अगर (ret < 0)
		वापस ret;

	अगर (sपंचांगpe->irq >= 0) अणु
		अगर (id == STMPE801_ID || id == STMPE1600_ID)
			icr = STMPE_SYS_CTRL_INT_EN;
		अन्यथा
			icr = STMPE_ICR_LSB_GIM;

		/* STMPE801 and STMPE1600 करोn't support Edge पूर्णांकerrupts */
		अगर (id != STMPE801_ID && id != STMPE1600_ID) अणु
			अगर (irq_trigger == IRQF_TRIGGER_FALLING ||
					irq_trigger == IRQF_TRIGGER_RISING)
				icr |= STMPE_ICR_LSB_EDGE;
		पूर्ण

		अगर (irq_trigger == IRQF_TRIGGER_RISING ||
				irq_trigger == IRQF_TRIGGER_HIGH) अणु
			अगर (id == STMPE801_ID || id == STMPE1600_ID)
				icr |= STMPE_SYS_CTRL_INT_HI;
			अन्यथा
				icr |= STMPE_ICR_LSB_HIGH;
		पूर्ण
	पूर्ण

	अगर (sपंचांगpe->pdata->स्वतःsleep) अणु
		ret = sपंचांगpe_स्वतःsleep(sपंचांगpe, स्वतःsleep_समयout);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस sपंचांगpe_reg_ग_लिखो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_ICR_LSB], icr);
पूर्ण

अटल पूर्णांक sपंचांगpe_add_device(काष्ठा sपंचांगpe *sपंचांगpe, स्थिर काष्ठा mfd_cell *cell)
अणु
	वापस mfd_add_devices(sपंचांगpe->dev, sपंचांगpe->pdata->id, cell, 1,
			       शून्य, 0, sपंचांगpe->करोमुख्य);
पूर्ण

अटल पूर्णांक sपंचांगpe_devices_init(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	काष्ठा sपंचांगpe_variant_info *variant = sपंचांगpe->variant;
	अचिन्हित पूर्णांक platक्रमm_blocks = sपंचांगpe->pdata->blocks;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i, j;

	क्रम (i = 0; i < variant->num_blocks; i++) अणु
		काष्ठा sपंचांगpe_variant_block *block = &variant->blocks[i];

		अगर (!(platक्रमm_blocks & block->block))
			जारी;

		क्रम (j = 0; j < block->cell->num_resources; j++) अणु
			काष्ठा resource *res =
				(काष्ठा resource *) &block->cell->resources[j];

			/* Dynamically fill in a variant's IRQ. */
			अगर (res->flags & IORESOURCE_IRQ)
				res->start = res->end = block->irq + j;
		पूर्ण

		platक्रमm_blocks &= ~block->block;
		ret = sपंचांगpe_add_device(sपंचांगpe, block->cell);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (platक्रमm_blocks)
		dev_warn(sपंचांगpe->dev,
			 "platform wants blocks (%#x) not present on variant",
			 platक्रमm_blocks);

	वापस ret;
पूर्ण

अटल व्योम sपंचांगpe_of_probe(काष्ठा sपंचांगpe_platक्रमm_data *pdata,
			   काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;

	pdata->id = of_alias_get_id(np, "stmpe-i2c");
	अगर (pdata->id < 0)
		pdata->id = -1;

	pdata->irq_gpio = of_get_named_gpio_flags(np, "irq-gpio", 0,
				&pdata->irq_trigger);
	अगर (gpio_is_valid(pdata->irq_gpio))
		pdata->irq_over_gpio = 1;
	अन्यथा
		pdata->irq_trigger = IRQF_TRIGGER_NONE;

	of_property_पढ़ो_u32(np, "st,autosleep-timeout",
			&pdata->स्वतःsleep_समयout);

	pdata->स्वतःsleep = (pdata->स्वतःsleep_समयout) ? true : false;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_node_name_eq(child, "stmpe_gpio")) अणु
			pdata->blocks |= STMPE_BLOCK_GPIO;
		पूर्ण अन्यथा अगर (of_node_name_eq(child, "stmpe_keypad")) अणु
			pdata->blocks |= STMPE_BLOCK_KEYPAD;
		पूर्ण अन्यथा अगर (of_node_name_eq(child, "stmpe_touchscreen")) अणु
			pdata->blocks |= STMPE_BLOCK_TOUCHSCREEN;
		पूर्ण अन्यथा अगर (of_node_name_eq(child, "stmpe_adc")) अणु
			pdata->blocks |= STMPE_BLOCK_ADC;
		पूर्ण अन्यथा अगर (of_node_name_eq(child, "stmpe_pwm")) अणु
			pdata->blocks |= STMPE_BLOCK_PWM;
		पूर्ण अन्यथा अगर (of_node_name_eq(child, "stmpe_rotator")) अणु
			pdata->blocks |= STMPE_BLOCK_ROTATOR;
		पूर्ण
	पूर्ण
पूर्ण

/* Called from client specअगरic probe routines */
पूर्णांक sपंचांगpe_probe(काष्ठा sपंचांगpe_client_info *ci, क्रमागत sपंचांगpe_partnum partnum)
अणु
	काष्ठा sपंचांगpe_platक्रमm_data *pdata;
	काष्ठा device_node *np = ci->dev->of_node;
	काष्ठा sपंचांगpe *sपंचांगpe;
	पूर्णांक ret;
	u32 val;

	pdata = devm_kzalloc(ci->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	sपंचांगpe_of_probe(pdata, np);

	अगर (of_find_property(np, "interrupts", शून्य) == शून्य)
		ci->irq = -1;

	sपंचांगpe = devm_kzalloc(ci->dev, माप(काष्ठा sपंचांगpe), GFP_KERNEL);
	अगर (!sपंचांगpe)
		वापस -ENOMEM;

	mutex_init(&sपंचांगpe->irq_lock);
	mutex_init(&sपंचांगpe->lock);

	अगर (!of_property_पढ़ो_u32(np, "st,sample-time", &val))
		sपंचांगpe->sample_समय = val;
	अगर (!of_property_पढ़ो_u32(np, "st,mod-12b", &val))
		sपंचांगpe->mod_12b = val;
	अगर (!of_property_पढ़ो_u32(np, "st,ref-sel", &val))
		sपंचांगpe->ref_sel = val;
	अगर (!of_property_पढ़ो_u32(np, "st,adc-freq", &val))
		sपंचांगpe->adc_freq = val;

	sपंचांगpe->dev = ci->dev;
	sपंचांगpe->client = ci->client;
	sपंचांगpe->pdata = pdata;
	sपंचांगpe->ci = ci;
	sपंचांगpe->partnum = partnum;
	sपंचांगpe->variant = sपंचांगpe_variant_info[partnum];
	sपंचांगpe->regs = sपंचांगpe->variant->regs;
	sपंचांगpe->num_gpios = sपंचांगpe->variant->num_gpios;
	sपंचांगpe->vcc = devm_regulator_get_optional(ci->dev, "vcc");
	अगर (!IS_ERR(sपंचांगpe->vcc)) अणु
		ret = regulator_enable(sपंचांगpe->vcc);
		अगर (ret)
			dev_warn(ci->dev, "failed to enable VCC supply\n");
	पूर्ण
	sपंचांगpe->vio = devm_regulator_get_optional(ci->dev, "vio");
	अगर (!IS_ERR(sपंचांगpe->vio)) अणु
		ret = regulator_enable(sपंचांगpe->vio);
		अगर (ret)
			dev_warn(ci->dev, "failed to enable VIO supply\n");
	पूर्ण
	dev_set_drvdata(sपंचांगpe->dev, sपंचांगpe);

	अगर (ci->init)
		ci->init(sपंचांगpe);

	अगर (pdata->irq_over_gpio) अणु
		ret = devm_gpio_request_one(ci->dev, pdata->irq_gpio,
				GPIOF_सूची_IN, "stmpe");
		अगर (ret) अणु
			dev_err(sपंचांगpe->dev, "failed to request IRQ GPIO: %d\n",
					ret);
			वापस ret;
		पूर्ण

		sपंचांगpe->irq = gpio_to_irq(pdata->irq_gpio);
	पूर्ण अन्यथा अणु
		sपंचांगpe->irq = ci->irq;
	पूर्ण

	अगर (sपंचांगpe->irq < 0) अणु
		/* use alternate variant info क्रम no-irq mode, अगर supported */
		dev_info(sपंचांगpe->dev,
			"%s configured in no-irq mode by platform data\n",
			sपंचांगpe->variant->name);
		अगर (!sपंचांगpe_noirq_variant_info[sपंचांगpe->partnum]) अणु
			dev_err(sपंचांगpe->dev,
				"%s does not support no-irq mode!\n",
				sपंचांगpe->variant->name);
			वापस -ENODEV;
		पूर्ण
		sपंचांगpe->variant = sपंचांगpe_noirq_variant_info[sपंचांगpe->partnum];
	पूर्ण अन्यथा अगर (pdata->irq_trigger == IRQF_TRIGGER_NONE) अणु
		pdata->irq_trigger = irq_get_trigger_type(sपंचांगpe->irq);
	पूर्ण

	ret = sपंचांगpe_chip_init(sपंचांगpe);
	अगर (ret)
		वापस ret;

	अगर (sपंचांगpe->irq >= 0) अणु
		ret = sपंचांगpe_irq_init(sपंचांगpe, np);
		अगर (ret)
			वापस ret;

		ret = devm_request_thपढ़ोed_irq(ci->dev, sपंचांगpe->irq, शून्य,
				sपंचांगpe_irq, pdata->irq_trigger | IRQF_ONESHOT,
				"stmpe", sपंचांगpe);
		अगर (ret) अणु
			dev_err(sपंचांगpe->dev, "failed to request IRQ: %d\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = sपंचांगpe_devices_init(sपंचांगpe);
	अगर (!ret)
		वापस 0;

	dev_err(sपंचांगpe->dev, "failed to add children\n");
	mfd_हटाओ_devices(sपंचांगpe->dev);

	वापस ret;
पूर्ण

पूर्णांक sपंचांगpe_हटाओ(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	अगर (!IS_ERR(sपंचांगpe->vio))
		regulator_disable(sपंचांगpe->vio);
	अगर (!IS_ERR(sपंचांगpe->vcc))
		regulator_disable(sपंचांगpe->vcc);

	__sपंचांगpe_disable(sपंचांगpe, STMPE_BLOCK_ADC);

	mfd_हटाओ_devices(sपंचांगpe->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांगpe_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(dev);

	अगर (sपंचांगpe->irq >= 0 && device_may_wakeup(dev))
		enable_irq_wake(sपंचांगpe->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(dev);

	अगर (sपंचांगpe->irq >= 0 && device_may_wakeup(dev))
		disable_irq_wake(sपंचांगpe->irq);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops sपंचांगpe_dev_pm_ops = अणु
	.suspend	= sपंचांगpe_suspend,
	.resume		= sपंचांगpe_resume,
पूर्ण;
#पूर्ण_अगर
