<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/sपंचांगpe.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bitops.h>

/*
 * These रेजिस्टरs are modअगरied under the irq bus lock and cached to aव्योम
 * unnecessary ग_लिखोs in bus_sync_unlock.
 */
क्रमागत अणु REG_RE, REG_FE, REG_IE पूर्ण;

क्रमागत अणु LSB, CSB, MSB पूर्ण;

#घोषणा CACHE_NR_REGS	3
/* No variant has more than 24 GPIOs */
#घोषणा CACHE_NR_BANKS	(24 / 8)

काष्ठा sपंचांगpe_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा sपंचांगpe *sपंचांगpe;
	काष्ठा device *dev;
	काष्ठा mutex irq_lock;
	u32 norequest_mask;
	/* Caches of पूर्णांकerrupt control रेजिस्टरs क्रम bus_lock */
	u8 regs[CACHE_NR_REGS][CACHE_NR_BANKS];
	u8 oldregs[CACHE_NR_REGS][CACHE_NR_BANKS];
पूर्ण;

अटल पूर्णांक sपंचांगpe_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	u8 reg = sपंचांगpe->regs[STMPE_IDX_GPMR_LSB + (offset / 8)];
	u8 mask = BIT(offset % 8);
	पूर्णांक ret;

	ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, reg);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & mask);
पूर्ण

अटल व्योम sपंचांगpe_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	पूर्णांक which = val ? STMPE_IDX_GPSR_LSB : STMPE_IDX_GPCR_LSB;
	u8 reg = sपंचांगpe->regs[which + (offset / 8)];
	u8 mask = BIT(offset % 8);

	/*
	 * Some variants have single रेजिस्टर क्रम gpio set/clear functionality.
	 * For them we need to ग_लिखो 0 to clear and 1 to set.
	 */
	अगर (sपंचांगpe->regs[STMPE_IDX_GPSR_LSB] == sपंचांगpe->regs[STMPE_IDX_GPCR_LSB])
		sपंचांगpe_set_bits(sपंचांगpe, reg, mask, val ? mask : 0);
	अन्यथा
		sपंचांगpe_reg_ग_लिखो(sपंचांगpe, reg, mask);
पूर्ण

अटल पूर्णांक sपंचांगpe_gpio_get_direction(काष्ठा gpio_chip *chip,
				    अचिन्हित offset)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	u8 reg = sपंचांगpe->regs[STMPE_IDX_GPDR_LSB] - (offset / 8);
	u8 mask = BIT(offset % 8);
	पूर्णांक ret;

	ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, reg);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक sपंचांगpe_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	u8 reg = sपंचांगpe->regs[STMPE_IDX_GPDR_LSB + (offset / 8)];
	u8 mask = BIT(offset % 8);

	sपंचांगpe_gpio_set(chip, offset, val);

	वापस sपंचांगpe_set_bits(sपंचांगpe, reg, mask, mask);
पूर्ण

अटल पूर्णांक sपंचांगpe_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	u8 reg = sपंचांगpe->regs[STMPE_IDX_GPDR_LSB + (offset / 8)];
	u8 mask = BIT(offset % 8);

	वापस sपंचांगpe_set_bits(sपंचांगpe, reg, mask, 0);
पूर्ण

अटल पूर्णांक sपंचांगpe_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(chip);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;

	अगर (sपंचांगpe_gpio->norequest_mask & BIT(offset))
		वापस -EINVAL;

	वापस sपंचांगpe_set_altfunc(sपंचांगpe, BIT(offset), STMPE_BLOCK_GPIO);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "stmpe",
	.owner			= THIS_MODULE,
	.get_direction		= sपंचांगpe_gpio_get_direction,
	.direction_input	= sपंचांगpe_gpio_direction_input,
	.get			= sपंचांगpe_gpio_get,
	.direction_output	= sपंचांगpe_gpio_direction_output,
	.set			= sपंचांगpe_gpio_set,
	.request		= sपंचांगpe_gpio_request,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक sपंचांगpe_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	अगर (type & IRQ_TYPE_LEVEL_LOW || type & IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;

	/* STMPE801 and STMPE 1600 करोn't have RE and FE रेजिस्टरs */
	अगर (sपंचांगpe_gpio->sपंचांगpe->partnum == STMPE801 ||
	    sपंचांगpe_gpio->sपंचांगpe->partnum == STMPE1600)
		वापस 0;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		sपंचांगpe_gpio->regs[REG_RE][regoffset] |= mask;
	अन्यथा
		sपंचांगpe_gpio->regs[REG_RE][regoffset] &= ~mask;

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		sपंचांगpe_gpio->regs[REG_FE][regoffset] |= mask;
	अन्यथा
		sपंचांगpe_gpio->regs[REG_FE][regoffset] &= ~mask;

	वापस 0;
पूर्ण

अटल व्योम sपंचांगpe_gpio_irq_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);

	mutex_lock(&sपंचांगpe_gpio->irq_lock);
पूर्ण

अटल व्योम sपंचांगpe_gpio_irq_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	पूर्णांक num_banks = DIV_ROUND_UP(sपंचांगpe->num_gpios, 8);
	अटल स्थिर u8 regmap[CACHE_NR_REGS][CACHE_NR_BANKS] = अणु
		[REG_RE][LSB] = STMPE_IDX_GPRER_LSB,
		[REG_RE][CSB] = STMPE_IDX_GPRER_CSB,
		[REG_RE][MSB] = STMPE_IDX_GPRER_MSB,
		[REG_FE][LSB] = STMPE_IDX_GPFER_LSB,
		[REG_FE][CSB] = STMPE_IDX_GPFER_CSB,
		[REG_FE][MSB] = STMPE_IDX_GPFER_MSB,
		[REG_IE][LSB] = STMPE_IDX_IEGPIOR_LSB,
		[REG_IE][CSB] = STMPE_IDX_IEGPIOR_CSB,
		[REG_IE][MSB] = STMPE_IDX_IEGPIOR_MSB,
	पूर्ण;
	पूर्णांक i, j;

	/*
	 * STMPE1600: to be able to get IRQ from pins,
	 * a पढ़ो must be करोne on GPMR रेजिस्टर, or a ग_लिखो in
	 * GPSR or GPCR रेजिस्टरs
	 */
	अगर (sपंचांगpe->partnum == STMPE1600) अणु
		sपंचांगpe_reg_पढ़ो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_GPMR_LSB]);
		sपंचांगpe_reg_पढ़ो(sपंचांगpe, sपंचांगpe->regs[STMPE_IDX_GPMR_CSB]);
	पूर्ण

	क्रम (i = 0; i < CACHE_NR_REGS; i++) अणु
		/* STMPE801 and STMPE1600 करोn't have RE and FE रेजिस्टरs */
		अगर ((sपंचांगpe->partnum == STMPE801 ||
		     sपंचांगpe->partnum == STMPE1600) &&
		     (i != REG_IE))
			जारी;

		क्रम (j = 0; j < num_banks; j++) अणु
			u8 old = sपंचांगpe_gpio->oldregs[i][j];
			u8 new = sपंचांगpe_gpio->regs[i][j];

			अगर (new == old)
				जारी;

			sपंचांगpe_gpio->oldregs[i][j] = new;
			sपंचांगpe_reg_ग_लिखो(sपंचांगpe, sपंचांगpe->regs[regmap[i][j]], new);
		पूर्ण
	पूर्ण

	mutex_unlock(&sपंचांगpe_gpio->irq_lock);
पूर्ण

अटल व्योम sपंचांगpe_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	sपंचांगpe_gpio->regs[REG_IE][regoffset] &= ~mask;
पूर्ण

अटल व्योम sपंचांगpe_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	पूर्णांक offset = d->hwirq;
	पूर्णांक regoffset = offset / 8;
	पूर्णांक mask = BIT(offset % 8);

	sपंचांगpe_gpio->regs[REG_IE][regoffset] |= mask;
पूर्ण

अटल व्योम sपंचांगpe_dbg_show_one(काष्ठा seq_file *s,
			       काष्ठा gpio_chip *gc,
			       अचिन्हित offset, अचिन्हित gpio)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	स्थिर अक्षर *label = gpiochip_is_requested(gc, offset);
	bool val = !!sपंचांगpe_gpio_get(gc, offset);
	u8 bank = offset / 8;
	u8 dir_reg = sपंचांगpe->regs[STMPE_IDX_GPDR_LSB + bank];
	u8 mask = BIT(offset % 8);
	पूर्णांक ret;
	u8 dir;

	ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, dir_reg);
	अगर (ret < 0)
		वापस;
	dir = !!(ret & mask);

	अगर (dir) अणु
		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) out %s",
			   gpio, label ?: "(none)",
			   val ? "hi" : "lo");
	पूर्ण अन्यथा अणु
		u8 edge_det_reg;
		u8 rise_reg;
		u8 fall_reg;
		u8 irqen_reg;

		अटल स्थिर अक्षर * स्थिर edge_det_values[] = अणु
			"edge-inactive",
			"edge-asserted",
			"not-supported"
		पूर्ण;
		अटल स्थिर अक्षर * स्थिर rise_values[] = अणु
			"no-rising-edge-detection",
			"rising-edge-detection",
			"not-supported"
		पूर्ण;
		अटल स्थिर अक्षर * स्थिर fall_values[] = अणु
			"no-falling-edge-detection",
			"falling-edge-detection",
			"not-supported"
		पूर्ण;
		#घोषणा NOT_SUPPORTED_IDX 2
		u8 edge_det = NOT_SUPPORTED_IDX;
		u8 rise = NOT_SUPPORTED_IDX;
		u8 fall = NOT_SUPPORTED_IDX;
		bool irqen;

		चयन (sपंचांगpe->partnum) अणु
		हाल STMPE610:
		हाल STMPE811:
		हाल STMPE1601:
		हाल STMPE2401:
		हाल STMPE2403:
			edge_det_reg = sपंचांगpe->regs[STMPE_IDX_GPEDR_LSB + bank];
			ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, edge_det_reg);
			अगर (ret < 0)
				वापस;
			edge_det = !!(ret & mask);
			fallthrough;
		हाल STMPE1801:
			rise_reg = sपंचांगpe->regs[STMPE_IDX_GPRER_LSB + bank];
			fall_reg = sपंचांगpe->regs[STMPE_IDX_GPFER_LSB + bank];

			ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, rise_reg);
			अगर (ret < 0)
				वापस;
			rise = !!(ret & mask);
			ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, fall_reg);
			अगर (ret < 0)
				वापस;
			fall = !!(ret & mask);
			fallthrough;
		हाल STMPE801:
		हाल STMPE1600:
			irqen_reg = sपंचांगpe->regs[STMPE_IDX_IEGPIOR_LSB + bank];
			अवरोध;

		शेष:
			वापस;
		पूर्ण

		ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, irqen_reg);
		अगर (ret < 0)
			वापस;
		irqen = !!(ret & mask);

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) in  %s %13s %13s %25s %25s",
			   gpio, label ?: "(none)",
			   val ? "hi" : "lo",
			   edge_det_values[edge_det],
			   irqen ? "IRQ-enabled" : "IRQ-disabled",
			   rise_values[rise],
			   fall_values[fall]);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगpe_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *gc)
अणु
	अचिन्हित i;
	अचिन्हित gpio = gc->base;

	क्रम (i = 0; i < gc->ngpio; i++, gpio++) अणु
		sपंचांगpe_dbg_show_one(s, gc, i, gpio);
		seq_अ_दो(s, '\n');
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip sपंचांगpe_gpio_irq_chip = अणु
	.name			= "stmpe-gpio",
	.irq_bus_lock		= sपंचांगpe_gpio_irq_lock,
	.irq_bus_sync_unlock	= sपंचांगpe_gpio_irq_sync_unlock,
	.irq_mask		= sपंचांगpe_gpio_irq_mask,
	.irq_unmask		= sपंचांगpe_gpio_irq_unmask,
	.irq_set_type		= sपंचांगpe_gpio_irq_set_type,
पूर्ण;

#घोषणा MAX_GPIOS 24

अटल irqवापस_t sपंचांगpe_gpio_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = dev;
	काष्ठा sपंचांगpe *sपंचांगpe = sपंचांगpe_gpio->sपंचांगpe;
	u8 staपंचांगsbreg;
	पूर्णांक num_banks = DIV_ROUND_UP(sपंचांगpe->num_gpios, 8);
	u8 status[DIV_ROUND_UP(MAX_GPIOS, 8)];
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * the sपंचांगpe_block_पढ़ो() call below, imposes to set staपंचांगsbreg
	 * with the रेजिस्टर located at the lowest address. As STMPE1600
	 * variant is the only one which respect रेजिस्टरs address's order
	 * (LSB regs located at lowest address than MSB ones) whereas all
	 * the others have a रेजिस्टरs layout with MSB located beक्रमe the
	 * LSB regs.
	 */
	अगर (sपंचांगpe->partnum == STMPE1600)
		staपंचांगsbreg = sपंचांगpe->regs[STMPE_IDX_ISGPIOR_LSB];
	अन्यथा
		staपंचांगsbreg = sपंचांगpe->regs[STMPE_IDX_ISGPIOR_MSB];

	ret = sपंचांगpe_block_पढ़ो(sपंचांगpe, staपंचांगsbreg, num_banks, status);
	अगर (ret < 0)
		वापस IRQ_NONE;

	क्रम (i = 0; i < num_banks; i++) अणु
		पूर्णांक bank = (sपंचांगpe_gpio->sपंचांगpe->partnum == STMPE1600) ? i :
			   num_banks - i - 1;
		अचिन्हित पूर्णांक enabled = sपंचांगpe_gpio->regs[REG_IE][bank];
		अचिन्हित पूर्णांक stat = status[i];

		stat &= enabled;
		अगर (!stat)
			जारी;

		जबतक (stat) अणु
			पूर्णांक bit = __ffs(stat);
			पूर्णांक line = bank * 8 + bit;
			पूर्णांक child_irq = irq_find_mapping(sपंचांगpe_gpio->chip.irq.करोमुख्य,
							 line);

			handle_nested_irq(child_irq);
			stat &= ~BIT(bit);
		पूर्ण

		/*
		 * पूर्णांकerrupt status रेजिस्टर ग_लिखो has no effect on
		 * 801/1801/1600, bits are cleared when पढ़ो.
		 * Edge detect रेजिस्टर is not present on 801/1600/1801
		 */
		अगर (sपंचांगpe->partnum != STMPE801 && sपंचांगpe->partnum != STMPE1600 &&
		    sपंचांगpe->partnum != STMPE1801) अणु
			sपंचांगpe_reg_ग_लिखो(sपंचांगpe, staपंचांगsbreg + i, status[i]);
			sपंचांगpe_reg_ग_लिखो(sपंचांगpe,
					sपंचांगpe->regs[STMPE_IDX_GPEDR_MSB] + i,
					status[i]);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांगpe_init_irq_valid_mask(काष्ठा gpio_chip *gc,
				      अचिन्हित दीर्घ *valid_mask,
				      अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio = gpiochip_get_data(gc);
	पूर्णांक i;

	अगर (!sपंचांगpe_gpio->norequest_mask)
		वापस;

	/* Forbid unused lines to be mapped as IRQs */
	क्रम (i = 0; i < माप(u32); i++) अणु
		अगर (sपंचांगpe_gpio->norequest_mask & BIT(i))
			clear_bit(i, valid_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगpe_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sपंचांगpe_gpio *sपंचांगpe_gpio;
	पूर्णांक ret, irq;

	अगर (sपंचांगpe->num_gpios > MAX_GPIOS) अणु
		dev_err(&pdev->dev, "Need to increase maximum GPIO number\n");
		वापस -EINVAL;
	पूर्ण

	sपंचांगpe_gpio = kzalloc(माप(*sपंचांगpe_gpio), GFP_KERNEL);
	अगर (!sपंचांगpe_gpio)
		वापस -ENOMEM;

	mutex_init(&sपंचांगpe_gpio->irq_lock);

	sपंचांगpe_gpio->dev = &pdev->dev;
	sपंचांगpe_gpio->sपंचांगpe = sपंचांगpe;
	sपंचांगpe_gpio->chip = ढाँचा_chip;
	sपंचांगpe_gpio->chip.ngpio = sपंचांगpe->num_gpios;
	sपंचांगpe_gpio->chip.parent = &pdev->dev;
	sपंचांगpe_gpio->chip.of_node = np;
	sपंचांगpe_gpio->chip.base = -1;

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
                sपंचांगpe_gpio->chip.dbg_show = sपंचांगpe_dbg_show;

	of_property_पढ़ो_u32(np, "st,norequest-mask",
			&sपंचांगpe_gpio->norequest_mask);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		dev_info(&pdev->dev,
			"device configured in no-irq mode: "
			"irqs are not available\n");

	ret = sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_GPIO);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				sपंचांगpe_gpio_irq, IRQF_ONESHOT,
				"stmpe-gpio", sपंचांगpe_gpio);
		अगर (ret) अणु
			dev_err(&pdev->dev, "unable to get irq: %d\n", ret);
			जाओ out_disable;
		पूर्ण

		girq = &sपंचांगpe_gpio->chip.irq;
		girq->chip = &sपंचांगpe_gpio_irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		girq->thपढ़ोed = true;
		girq->init_valid_mask = sपंचांगpe_init_irq_valid_mask;
	पूर्ण

	ret = gpiochip_add_data(&sपंचांगpe_gpio->chip, sपंचांगpe_gpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add gpiochip: %d\n", ret);
		जाओ out_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sपंचांगpe_gpio);

	वापस 0;

out_disable:
	sपंचांगpe_disable(sपंचांगpe, STMPE_BLOCK_GPIO);
	gpiochip_हटाओ(&sपंचांगpe_gpio->chip);
out_मुक्त:
	kमुक्त(sपंचांगpe_gpio);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांगpe_gpio_driver = अणु
	.driver = अणु
		.suppress_bind_attrs	= true,
		.name			= "stmpe-gpio",
	पूर्ण,
	.probe		= sपंचांगpe_gpio_probe,
पूर्ण;

अटल पूर्णांक __init sपंचांगpe_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांगpe_gpio_driver);
पूर्ण
subsys_initcall(sपंचांगpe_gpio_init);
