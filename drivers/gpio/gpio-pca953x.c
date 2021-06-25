<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PCA953x 4/8/16/24/40 bit I/O ports
 *
 *  Copyright (C) 2005 Ben Gardner <bgardner@wabtec.com>
 *  Copyright (C) 2007 Marvell International Ltd.
 *
 *  Derived from drivers/i2c/chips/pca9539.c
 */

#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा PCA953X_INPUT		0x00
#घोषणा PCA953X_OUTPUT		0x01
#घोषणा PCA953X_INVERT		0x02
#घोषणा PCA953X_सूचीECTION	0x03

#घोषणा REG_ADDR_MASK		GENMASK(5, 0)
#घोषणा REG_ADDR_EXT		BIT(6)
#घोषणा REG_ADDR_AI		BIT(7)

#घोषणा PCA957X_IN		0x00
#घोषणा PCA957X_INVRT		0x01
#घोषणा PCA957X_BKEN		0x02
#घोषणा PCA957X_PUPD		0x03
#घोषणा PCA957X_CFG		0x04
#घोषणा PCA957X_OUT		0x05
#घोषणा PCA957X_MSK		0x06
#घोषणा PCA957X_INTS		0x07

#घोषणा PCAL953X_OUT_STRENGTH	0x20
#घोषणा PCAL953X_IN_LATCH	0x22
#घोषणा PCAL953X_PULL_EN	0x23
#घोषणा PCAL953X_PULL_SEL	0x24
#घोषणा PCAL953X_INT_MASK	0x25
#घोषणा PCAL953X_INT_STAT	0x26
#घोषणा PCAL953X_OUT_CONF	0x27

#घोषणा PCAL6524_INT_EDGE	0x28
#घोषणा PCAL6524_INT_CLR	0x2a
#घोषणा PCAL6524_IN_STATUS	0x2b
#घोषणा PCAL6524_OUT_INDCONF	0x2c
#घोषणा PCAL6524_DEBOUNCE	0x2d

#घोषणा PCA_GPIO_MASK		GENMASK(7, 0)

#घोषणा PCAL_GPIO_MASK		GENMASK(4, 0)
#घोषणा PCAL_PINCTRL_MASK	GENMASK(6, 5)

#घोषणा PCA_INT			BIT(8)
#घोषणा PCA_PCAL		BIT(9)
#घोषणा PCA_LATCH_INT		(PCA_PCAL | PCA_INT)
#घोषणा PCA953X_TYPE		BIT(12)
#घोषणा PCA957X_TYPE		BIT(13)
#घोषणा PCA_TYPE_MASK		GENMASK(15, 12)

#घोषणा PCA_CHIP_TYPE(x)	((x) & PCA_TYPE_MASK)

अटल स्थिर काष्ठा i2c_device_id pca953x_id[] = अणु
	अणु "pca6416", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9505", 40 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9506", 40 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9534", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9535", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9536", 4  | PCA953X_TYPE, पूर्ण,
	अणु "pca9537", 4  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9538", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9539", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9554", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9555", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9556", 8  | PCA953X_TYPE, पूर्ण,
	अणु "pca9557", 8  | PCA953X_TYPE, पूर्ण,
	अणु "pca9574", 8  | PCA957X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9575", 16 | PCA957X_TYPE | PCA_INT, पूर्ण,
	अणु "pca9698", 40 | PCA953X_TYPE, पूर्ण,

	अणु "pcal6416", 16 | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,
	अणु "pcal6524", 24 | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,
	अणु "pcal9535", 16 | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,
	अणु "pcal9554b", 8  | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,
	अणु "pcal9555a", 16 | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,

	अणु "max7310", 8  | PCA953X_TYPE, पूर्ण,
	अणु "max7312", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "max7313", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "max7315", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "max7318", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "pca6107", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "tca6408", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "tca6416", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "tca6424", 24 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "tca9539", 16 | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "tca9554", 8  | PCA953X_TYPE | PCA_INT, पूर्ण,
	अणु "xra1202", 8  | PCA953X_TYPE पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca953x_id);

#अगर_घोषित CONFIG_GPIO_PCA953X_IRQ

#समावेश <linux/dmi.h>

अटल स्थिर काष्ठा acpi_gpio_params pca953x_irq_gpios = अणु 0, 0, true पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping pca953x_acpi_irq_gpios[] = अणु
	अणु "irq-gpios", &pca953x_irq_gpios, 1, ACPI_GPIO_QUIRK_ABSOLUTE_NUMBER पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक pca953x_acpi_get_irq(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, pca953x_acpi_irq_gpios);
	अगर (ret)
		dev_warn(dev, "can't add GPIO ACPI mapping\n");

	ret = acpi_dev_gpio_irq_get_by(ACPI_COMPANION(dev), "irq-gpios", 0);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "ACPI interrupt quirk (IRQ %d)\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pca953x_dmi_acpi_irq_info[] = अणु
	अणु
		/*
		 * On Intel Galileo Gen 2 board the IRQ pin of one of
		 * the IतऑC GPIO expanders, which has GpioInt() resource,
		 * is provided as an असलolute number instead of being
		 * relative. Since first controller (gpio-sch.c) and
		 * second (gpio-dwapb.c) are at the fixed bases, we may
		 * safely refer to the number in the global space to get
		 * an IRQ out of it.
		 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "GalileoGen2"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा acpi_device_id pca953x_acpi_ids[] = अणु
	अणु "INT3491", 16 | PCA953X_TYPE | PCA_LATCH_INT, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pca953x_acpi_ids);

#घोषणा MAX_BANK 5
#घोषणा BANK_SZ 8
#घोषणा MAX_LINE	(MAX_BANK * BANK_SZ)

#घोषणा NBANK(chip) DIV_ROUND_UP(chip->gpio_chip.ngpio, BANK_SZ)

काष्ठा pca953x_reg_config अणु
	पूर्णांक direction;
	पूर्णांक output;
	पूर्णांक input;
	पूर्णांक invert;
पूर्ण;

अटल स्थिर काष्ठा pca953x_reg_config pca953x_regs = अणु
	.direction = PCA953X_सूचीECTION,
	.output = PCA953X_OUTPUT,
	.input = PCA953X_INPUT,
	.invert = PCA953X_INVERT,
पूर्ण;

अटल स्थिर काष्ठा pca953x_reg_config pca957x_regs = अणु
	.direction = PCA957X_CFG,
	.output = PCA957X_OUT,
	.input = PCA957X_IN,
	.invert = PCA957X_INVRT,
पूर्ण;

काष्ठा pca953x_chip अणु
	अचिन्हित gpio_start;
	काष्ठा mutex i2c_lock;
	काष्ठा regmap *regmap;

#अगर_घोषित CONFIG_GPIO_PCA953X_IRQ
	काष्ठा mutex irq_lock;
	DECLARE_BITMAP(irq_mask, MAX_LINE);
	DECLARE_BITMAP(irq_stat, MAX_LINE);
	DECLARE_BITMAP(irq_trig_उठाओ, MAX_LINE);
	DECLARE_BITMAP(irq_trig_fall, MAX_LINE);
	काष्ठा irq_chip irq_chip;
#पूर्ण_अगर
	atomic_t wakeup_path;

	काष्ठा i2c_client *client;
	काष्ठा gpio_chip gpio_chip;
	स्थिर अक्षर *स्थिर *names;
	अचिन्हित दीर्घ driver_data;
	काष्ठा regulator *regulator;

	स्थिर काष्ठा pca953x_reg_config *regs;
पूर्ण;

अटल पूर्णांक pca953x_bank_shअगरt(काष्ठा pca953x_chip *chip)
अणु
	वापस fls((chip->gpio_chip.ngpio - 1) / BANK_SZ);
पूर्ण

#घोषणा PCA953x_BANK_INPUT	BIT(0)
#घोषणा PCA953x_BANK_OUTPUT	BIT(1)
#घोषणा PCA953x_BANK_POLARITY	BIT(2)
#घोषणा PCA953x_BANK_CONFIG	BIT(3)

#घोषणा PCA957x_BANK_INPUT	BIT(0)
#घोषणा PCA957x_BANK_POLARITY	BIT(1)
#घोषणा PCA957x_BANK_BUSHOLD	BIT(2)
#घोषणा PCA957x_BANK_CONFIG	BIT(4)
#घोषणा PCA957x_BANK_OUTPUT	BIT(5)

#घोषणा PCAL9xxx_BANK_IN_LATCH	BIT(8 + 2)
#घोषणा PCAL9xxx_BANK_PULL_EN	BIT(8 + 3)
#घोषणा PCAL9xxx_BANK_PULL_SEL	BIT(8 + 4)
#घोषणा PCAL9xxx_BANK_IRQ_MASK	BIT(8 + 5)
#घोषणा PCAL9xxx_BANK_IRQ_STAT	BIT(8 + 6)

/*
 * We care about the following रेजिस्टरs:
 * - Standard set, below 0x40, each port can be replicated up to 8 बार
 *   - PCA953x standard
 *     Input port			0x00 + 0 * bank_size	R
 *     Output port			0x00 + 1 * bank_size	RW
 *     Polarity Inversion port		0x00 + 2 * bank_size	RW
 *     Configuration port		0x00 + 3 * bank_size	RW
 *   - PCA957x with mixed up रेजिस्टरs
 *     Input port			0x00 + 0 * bank_size	R
 *     Polarity Inversion port		0x00 + 1 * bank_size	RW
 *     Bus hold port			0x00 + 2 * bank_size	RW
 *     Configuration port		0x00 + 4 * bank_size	RW
 *     Output port			0x00 + 5 * bank_size	RW
 *
 * - Extended set, above 0x40, often chip specअगरic.
 *   - PCAL6524/PCAL9555A with custom PCAL IRQ handling:
 *     Input latch रेजिस्टर		0x40 + 2 * bank_size	RW
 *     Pull-up/pull-करोwn enable reg	0x40 + 3 * bank_size    RW
 *     Pull-up/pull-करोwn select reg	0x40 + 4 * bank_size    RW
 *     Interrupt mask रेजिस्टर		0x40 + 5 * bank_size	RW
 *     Interrupt status रेजिस्टर	0x40 + 6 * bank_size	R
 *
 * - Registers with bit 0x80 set, the AI bit
 *   The bit is cleared and the रेजिस्टरs fall पूर्णांकo one of the
 *   categories above.
 */

अटल bool pca953x_check_रेजिस्टर(काष्ठा pca953x_chip *chip, अचिन्हित पूर्णांक reg,
				   u32 checkbank)
अणु
	पूर्णांक bank_shअगरt = pca953x_bank_shअगरt(chip);
	पूर्णांक bank = (reg & REG_ADDR_MASK) >> bank_shअगरt;
	पूर्णांक offset = reg & (BIT(bank_shअगरt) - 1);

	/* Special PCAL extended रेजिस्टर check. */
	अगर (reg & REG_ADDR_EXT) अणु
		अगर (!(chip->driver_data & PCA_PCAL))
			वापस false;
		bank += 8;
	पूर्ण

	/* Register is not in the matching bank. */
	अगर (!(BIT(bank) & checkbank))
		वापस false;

	/* Register is not within allowed range of bank. */
	अगर (offset >= NBANK(chip))
		वापस false;

	वापस true;
पूर्ण

अटल bool pca953x_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);
	u32 bank;

	अगर (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE) अणु
		bank = PCA953x_BANK_INPUT | PCA953x_BANK_OUTPUT |
		       PCA953x_BANK_POLARITY | PCA953x_BANK_CONFIG;
	पूर्ण अन्यथा अणु
		bank = PCA957x_BANK_INPUT | PCA957x_BANK_OUTPUT |
		       PCA957x_BANK_POLARITY | PCA957x_BANK_CONFIG |
		       PCA957x_BANK_BUSHOLD;
	पूर्ण

	अगर (chip->driver_data & PCA_PCAL) अणु
		bank |= PCAL9xxx_BANK_IN_LATCH | PCAL9xxx_BANK_PULL_EN |
			PCAL9xxx_BANK_PULL_SEL | PCAL9xxx_BANK_IRQ_MASK |
			PCAL9xxx_BANK_IRQ_STAT;
	पूर्ण

	वापस pca953x_check_रेजिस्टर(chip, reg, bank);
पूर्ण

अटल bool pca953x_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);
	u32 bank;

	अगर (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE) अणु
		bank = PCA953x_BANK_OUTPUT | PCA953x_BANK_POLARITY |
			PCA953x_BANK_CONFIG;
	पूर्ण अन्यथा अणु
		bank = PCA957x_BANK_OUTPUT | PCA957x_BANK_POLARITY |
			PCA957x_BANK_CONFIG | PCA957x_BANK_BUSHOLD;
	पूर्ण

	अगर (chip->driver_data & PCA_PCAL)
		bank |= PCAL9xxx_BANK_IN_LATCH | PCAL9xxx_BANK_PULL_EN |
			PCAL9xxx_BANK_PULL_SEL | PCAL9xxx_BANK_IRQ_MASK;

	वापस pca953x_check_रेजिस्टर(chip, reg, bank);
पूर्ण

अटल bool pca953x_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);
	u32 bank;

	अगर (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE)
		bank = PCA953x_BANK_INPUT;
	अन्यथा
		bank = PCA957x_BANK_INPUT;

	अगर (chip->driver_data & PCA_PCAL)
		bank |= PCAL9xxx_BANK_IRQ_STAT;

	वापस pca953x_check_रेजिस्टर(chip, reg, bank);
पूर्ण

अटल स्थिर काष्ठा regmap_config pca953x_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = pca953x_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg = pca953x_ग_लिखोable_रेजिस्टर,
	.अस्थिर_reg = pca953x_अस्थिर_रेजिस्टर,

	.disable_locking = true,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 0x7f,
पूर्ण;

अटल स्थिर काष्ठा regmap_config pca953x_ai_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ो_flag_mask = REG_ADDR_AI,
	.ग_लिखो_flag_mask = REG_ADDR_AI,

	.पढ़ोable_reg = pca953x_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg = pca953x_ग_लिखोable_रेजिस्टर,
	.अस्थिर_reg = pca953x_अस्थिर_रेजिस्टर,

	.disable_locking = true,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 0x7f,
पूर्ण;

अटल u8 pca953x_recalc_addr(काष्ठा pca953x_chip *chip, पूर्णांक reg, पूर्णांक off)
अणु
	पूर्णांक bank_shअगरt = pca953x_bank_shअगरt(chip);
	पूर्णांक addr = (reg & PCAL_GPIO_MASK) << bank_shअगरt;
	पूर्णांक pinctrl = (reg & PCAL_PINCTRL_MASK) << 1;
	u8 regaddr = pinctrl | addr | (off / BANK_SZ);

	वापस regaddr;
पूर्ण

अटल पूर्णांक pca953x_ग_लिखो_regs(काष्ठा pca953x_chip *chip, पूर्णांक reg, अचिन्हित दीर्घ *val)
अणु
	u8 regaddr = pca953x_recalc_addr(chip, reg, 0);
	u8 value[MAX_BANK];
	पूर्णांक i, ret;

	क्रम (i = 0; i < NBANK(chip); i++)
		value[i] = biपंचांगap_get_value8(val, i * BANK_SZ);

	ret = regmap_bulk_ग_लिखो(chip->regmap, regaddr, value, NBANK(chip));
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "failed writing register\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pca953x_पढ़ो_regs(काष्ठा pca953x_chip *chip, पूर्णांक reg, अचिन्हित दीर्घ *val)
अणु
	u8 regaddr = pca953x_recalc_addr(chip, reg, 0);
	u8 value[MAX_BANK];
	पूर्णांक i, ret;

	ret = regmap_bulk_पढ़ो(chip->regmap, regaddr, value, NBANK(chip));
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "failed reading register\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < NBANK(chip); i++)
		biपंचांगap_set_value8(val, value[i], i * BANK_SZ);

	वापस 0;
पूर्ण

अटल पूर्णांक pca953x_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	u8 dirreg = pca953x_recalc_addr(chip, chip->regs->direction, off);
	u8 bit = BIT(off % BANK_SZ);
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	ret = regmap_ग_लिखो_bits(chip->regmap, dirreg, bit, bit);
	mutex_unlock(&chip->i2c_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pca953x_gpio_direction_output(काष्ठा gpio_chip *gc,
		अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	u8 dirreg = pca953x_recalc_addr(chip, chip->regs->direction, off);
	u8 outreg = pca953x_recalc_addr(chip, chip->regs->output, off);
	u8 bit = BIT(off % BANK_SZ);
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	/* set output level */
	ret = regmap_ग_लिखो_bits(chip->regmap, outreg, bit, val ? bit : 0);
	अगर (ret)
		जाओ निकास;

	/* then direction */
	ret = regmap_ग_लिखो_bits(chip->regmap, dirreg, bit, 0);
निकास:
	mutex_unlock(&chip->i2c_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pca953x_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	u8 inreg = pca953x_recalc_addr(chip, chip->regs->input, off);
	u8 bit = BIT(off % BANK_SZ);
	u32 reg_val;
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	ret = regmap_पढ़ो(chip->regmap, inreg, &reg_val);
	mutex_unlock(&chip->i2c_lock);
	अगर (ret < 0) अणु
		/*
		 * NOTE:
		 * diagnostic alपढ़ोy emitted; that's all we should
		 * करो unless gpio_*_value_cansleep() calls become dअगरferent
		 * from their nonsleeping siblings (and report faults).
		 */
		वापस 0;
	पूर्ण

	वापस !!(reg_val & bit);
पूर्ण

अटल व्योम pca953x_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	u8 outreg = pca953x_recalc_addr(chip, chip->regs->output, off);
	u8 bit = BIT(off % BANK_SZ);

	mutex_lock(&chip->i2c_lock);
	regmap_ग_लिखो_bits(chip->regmap, outreg, bit, val ? bit : 0);
	mutex_unlock(&chip->i2c_lock);
पूर्ण

अटल पूर्णांक pca953x_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	u8 dirreg = pca953x_recalc_addr(chip, chip->regs->direction, off);
	u8 bit = BIT(off % BANK_SZ);
	u32 reg_val;
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	ret = regmap_पढ़ो(chip->regmap, dirreg, &reg_val);
	mutex_unlock(&chip->i2c_lock);
	अगर (ret < 0)
		वापस ret;

	अगर (reg_val & bit)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक pca953x_gpio_get_multiple(काष्ठा gpio_chip *gc,
				     अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	DECLARE_BITMAP(reg_val, MAX_LINE);
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	ret = pca953x_पढ़ो_regs(chip, chip->regs->input, reg_val);
	mutex_unlock(&chip->i2c_lock);
	अगर (ret)
		वापस ret;

	biपंचांगap_replace(bits, bits, reg_val, mask, gc->ngpio);
	वापस 0;
पूर्ण

अटल व्योम pca953x_gpio_set_multiple(काष्ठा gpio_chip *gc,
				      अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	DECLARE_BITMAP(reg_val, MAX_LINE);
	पूर्णांक ret;

	mutex_lock(&chip->i2c_lock);
	ret = pca953x_पढ़ो_regs(chip, chip->regs->output, reg_val);
	अगर (ret)
		जाओ निकास;

	biपंचांगap_replace(reg_val, reg_val, bits, mask, gc->ngpio);

	pca953x_ग_लिखो_regs(chip, chip->regs->output, reg_val);
निकास:
	mutex_unlock(&chip->i2c_lock);
पूर्ण

अटल पूर्णांक pca953x_gpio_set_pull_up_करोwn(काष्ठा pca953x_chip *chip,
					 अचिन्हित पूर्णांक offset,
					 अचिन्हित दीर्घ config)
अणु
	u8 pull_en_reg = pca953x_recalc_addr(chip, PCAL953X_PULL_EN, offset);
	u8 pull_sel_reg = pca953x_recalc_addr(chip, PCAL953X_PULL_SEL, offset);
	u8 bit = BIT(offset % BANK_SZ);
	पूर्णांक ret;

	/*
	 * pull-up/pull-करोwn configuration requires PCAL extended
	 * रेजिस्टरs
	 */
	अगर (!(chip->driver_data & PCA_PCAL))
		वापस -ENOTSUPP;

	mutex_lock(&chip->i2c_lock);

	/* Disable pull-up/pull-करोwn */
	ret = regmap_ग_लिखो_bits(chip->regmap, pull_en_reg, bit, 0);
	अगर (ret)
		जाओ निकास;

	/* Configure pull-up/pull-करोwn */
	अगर (config == PIN_CONFIG_BIAS_PULL_UP)
		ret = regmap_ग_लिखो_bits(chip->regmap, pull_sel_reg, bit, bit);
	अन्यथा अगर (config == PIN_CONFIG_BIAS_PULL_DOWN)
		ret = regmap_ग_लिखो_bits(chip->regmap, pull_sel_reg, bit, 0);
	अगर (ret)
		जाओ निकास;

	/* Enable pull-up/pull-करोwn */
	ret = regmap_ग_लिखो_bits(chip->regmap, pull_en_reg, bit, bit);

निकास:
	mutex_unlock(&chip->i2c_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pca953x_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		वापस pca953x_gpio_set_pull_up_करोwn(chip, offset, config);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम pca953x_setup_gpio(काष्ठा pca953x_chip *chip, पूर्णांक gpios)
अणु
	काष्ठा gpio_chip *gc;

	gc = &chip->gpio_chip;

	gc->direction_input  = pca953x_gpio_direction_input;
	gc->direction_output = pca953x_gpio_direction_output;
	gc->get = pca953x_gpio_get_value;
	gc->set = pca953x_gpio_set_value;
	gc->get_direction = pca953x_gpio_get_direction;
	gc->get_multiple = pca953x_gpio_get_multiple;
	gc->set_multiple = pca953x_gpio_set_multiple;
	gc->set_config = pca953x_gpio_set_config;
	gc->can_sleep = true;

	gc->base = chip->gpio_start;
	gc->ngpio = gpios;
	gc->label = dev_name(&chip->client->dev);
	gc->parent = &chip->client->dev;
	gc->owner = THIS_MODULE;
	gc->names = chip->names;
पूर्ण

#अगर_घोषित CONFIG_GPIO_PCA953X_IRQ
अटल व्योम pca953x_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	clear_bit(hwirq, chip->irq_mask);
पूर्ण

अटल व्योम pca953x_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	set_bit(hwirq, chip->irq_mask);
पूर्ण

अटल पूर्णांक pca953x_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);

	अगर (on)
		atomic_inc(&chip->wakeup_path);
	अन्यथा
		atomic_dec(&chip->wakeup_path);

	वापस irq_set_irq_wake(chip->client->irq, on);
पूर्ण

अटल व्योम pca953x_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->irq_lock);
पूर्ण

अटल व्योम pca953x_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	DECLARE_BITMAP(irq_mask, MAX_LINE);
	DECLARE_BITMAP(reg_direction, MAX_LINE);
	पूर्णांक level;

	अगर (chip->driver_data & PCA_PCAL) अणु
		/* Enable latch on पूर्णांकerrupt-enabled inमाला_दो */
		pca953x_ग_लिखो_regs(chip, PCAL953X_IN_LATCH, chip->irq_mask);

		biपंचांगap_complement(irq_mask, chip->irq_mask, gc->ngpio);

		/* Unmask enabled पूर्णांकerrupts */
		pca953x_ग_लिखो_regs(chip, PCAL953X_INT_MASK, irq_mask);
	पूर्ण

	/* Switch direction to input अगर needed */
	pca953x_पढ़ो_regs(chip, chip->regs->direction, reg_direction);

	biपंचांगap_or(irq_mask, chip->irq_trig_fall, chip->irq_trig_उठाओ, gc->ngpio);
	biपंचांगap_complement(reg_direction, reg_direction, gc->ngpio);
	biपंचांगap_and(irq_mask, irq_mask, reg_direction, gc->ngpio);

	/* Look क्रम any newly setup पूर्णांकerrupt */
	क्रम_each_set_bit(level, irq_mask, gc->ngpio)
		pca953x_gpio_direction_input(&chip->gpio_chip, level);

	mutex_unlock(&chip->irq_lock);
पूर्ण

अटल पूर्णांक pca953x_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	अगर (!(type & IRQ_TYPE_EDGE_BOTH)) अणु
		dev_err(&chip->client->dev, "irq %d: unsupported type %d\n",
			d->irq, type);
		वापस -EINVAL;
	पूर्ण

	assign_bit(hwirq, chip->irq_trig_fall, type & IRQ_TYPE_EDGE_FALLING);
	assign_bit(hwirq, chip->irq_trig_उठाओ, type & IRQ_TYPE_EDGE_RISING);

	वापस 0;
पूर्ण

अटल व्योम pca953x_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pca953x_chip *chip = gpiochip_get_data(gc);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	clear_bit(hwirq, chip->irq_trig_उठाओ);
	clear_bit(hwirq, chip->irq_trig_fall);
पूर्ण

अटल bool pca953x_irq_pending(काष्ठा pca953x_chip *chip, अचिन्हित दीर्घ *pending)
अणु
	काष्ठा gpio_chip *gc = &chip->gpio_chip;
	DECLARE_BITMAP(reg_direction, MAX_LINE);
	DECLARE_BITMAP(old_stat, MAX_LINE);
	DECLARE_BITMAP(cur_stat, MAX_LINE);
	DECLARE_BITMAP(new_stat, MAX_LINE);
	DECLARE_BITMAP(trigger, MAX_LINE);
	पूर्णांक ret;

	अगर (chip->driver_data & PCA_PCAL) अणु
		/* Read the current पूर्णांकerrupt status from the device */
		ret = pca953x_पढ़ो_regs(chip, PCAL953X_INT_STAT, trigger);
		अगर (ret)
			वापस false;

		/* Check latched inमाला_दो and clear पूर्णांकerrupt status */
		ret = pca953x_पढ़ो_regs(chip, chip->regs->input, cur_stat);
		अगर (ret)
			वापस false;

		/* Apply filter क्रम rising/falling edge selection */
		biपंचांगap_replace(new_stat, chip->irq_trig_fall, chip->irq_trig_उठाओ, cur_stat, gc->ngpio);

		biपंचांगap_and(pending, new_stat, trigger, gc->ngpio);

		वापस !biपंचांगap_empty(pending, gc->ngpio);
	पूर्ण

	ret = pca953x_पढ़ो_regs(chip, chip->regs->input, cur_stat);
	अगर (ret)
		वापस false;

	/* Remove output pins from the equation */
	pca953x_पढ़ो_regs(chip, chip->regs->direction, reg_direction);

	biपंचांगap_copy(old_stat, chip->irq_stat, gc->ngpio);

	biपंचांगap_and(new_stat, cur_stat, reg_direction, gc->ngpio);
	biपंचांगap_xor(cur_stat, new_stat, old_stat, gc->ngpio);
	biपंचांगap_and(trigger, cur_stat, chip->irq_mask, gc->ngpio);

	अगर (biपंचांगap_empty(trigger, gc->ngpio))
		वापस false;

	biपंचांगap_copy(chip->irq_stat, new_stat, gc->ngpio);

	biपंचांगap_and(cur_stat, chip->irq_trig_fall, old_stat, gc->ngpio);
	biपंचांगap_and(old_stat, chip->irq_trig_उठाओ, new_stat, gc->ngpio);
	biपंचांगap_or(new_stat, old_stat, cur_stat, gc->ngpio);
	biपंचांगap_and(pending, new_stat, trigger, gc->ngpio);

	वापस !biपंचांगap_empty(pending, gc->ngpio);
पूर्ण

अटल irqवापस_t pca953x_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा pca953x_chip *chip = devid;
	काष्ठा gpio_chip *gc = &chip->gpio_chip;
	DECLARE_BITMAP(pending, MAX_LINE);
	पूर्णांक level;
	bool ret;

	biपंचांगap_zero(pending, MAX_LINE);

	mutex_lock(&chip->i2c_lock);
	ret = pca953x_irq_pending(chip, pending);
	mutex_unlock(&chip->i2c_lock);

	अगर (ret) अणु
		ret = 0;

		क्रम_each_set_bit(level, pending, gc->ngpio) अणु
			पूर्णांक nested_irq = irq_find_mapping(gc->irq.करोमुख्य, level);

			अगर (unlikely(nested_irq <= 0)) अणु
				dev_warn_ratelimited(gc->parent, "unmapped interrupt %d\n", level);
				जारी;
			पूर्ण

			handle_nested_irq(nested_irq);
			ret = 1;
		पूर्ण
	पूर्ण

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल पूर्णांक pca953x_irq_setup(काष्ठा pca953x_chip *chip, पूर्णांक irq_base)
अणु
	काष्ठा i2c_client *client = chip->client;
	काष्ठा irq_chip *irq_chip = &chip->irq_chip;
	DECLARE_BITMAP(reg_direction, MAX_LINE);
	DECLARE_BITMAP(irq_stat, MAX_LINE);
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret;

	अगर (dmi_first_match(pca953x_dmi_acpi_irq_info)) अणु
		ret = pca953x_acpi_get_irq(&client->dev);
		अगर (ret > 0)
			client->irq = ret;
	पूर्ण

	अगर (!client->irq)
		वापस 0;

	अगर (irq_base == -1)
		वापस 0;

	अगर (!(chip->driver_data & PCA_INT))
		वापस 0;

	ret = pca953x_पढ़ो_regs(chip, chip->regs->input, irq_stat);
	अगर (ret)
		वापस ret;

	/*
	 * There is no way to know which GPIO line generated the
	 * पूर्णांकerrupt.  We have to rely on the previous पढ़ो क्रम
	 * this purpose.
	 */
	pca953x_पढ़ो_regs(chip, chip->regs->direction, reg_direction);
	biपंचांगap_and(chip->irq_stat, irq_stat, reg_direction, chip->gpio_chip.ngpio);
	mutex_init(&chip->irq_lock);

	irq_chip->name = dev_name(&client->dev);
	irq_chip->irq_mask = pca953x_irq_mask;
	irq_chip->irq_unmask = pca953x_irq_unmask;
	irq_chip->irq_set_wake = pca953x_irq_set_wake;
	irq_chip->irq_bus_lock = pca953x_irq_bus_lock;
	irq_chip->irq_bus_sync_unlock = pca953x_irq_bus_sync_unlock;
	irq_chip->irq_set_type = pca953x_irq_set_type;
	irq_chip->irq_shutकरोwn = pca953x_irq_shutकरोwn;

	girq = &chip->gpio_chip.irq;
	girq->chip = irq_chip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;
	girq->thपढ़ोed = true;
	girq->first = irq_base; /* FIXME: get rid of this */

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, pca953x_irq_handler,
					IRQF_ONESHOT | IRQF_SHARED,
					dev_name(&client->dev), chip);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to request irq %d\n",
			client->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_GPIO_PCA953X_IRQ */
अटल पूर्णांक pca953x_irq_setup(काष्ठा pca953x_chip *chip,
			     पूर्णांक irq_base)
अणु
	काष्ठा i2c_client *client = chip->client;

	अगर (client->irq && irq_base != -1 && (chip->driver_data & PCA_INT))
		dev_warn(&client->dev, "interrupt support not compiled in\n");

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक device_pca95xx_init(काष्ठा pca953x_chip *chip, u32 invert)
अणु
	DECLARE_BITMAP(val, MAX_LINE);
	पूर्णांक ret;

	ret = regcache_sync_region(chip->regmap, chip->regs->output,
				   chip->regs->output + NBANK(chip));
	अगर (ret)
		जाओ out;

	ret = regcache_sync_region(chip->regmap, chip->regs->direction,
				   chip->regs->direction + NBANK(chip));
	अगर (ret)
		जाओ out;

	/* set platक्रमm specअगरic polarity inversion */
	अगर (invert)
		biपंचांगap_fill(val, MAX_LINE);
	अन्यथा
		biपंचांगap_zero(val, MAX_LINE);

	ret = pca953x_ग_लिखो_regs(chip, chip->regs->invert, val);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक device_pca957x_init(काष्ठा pca953x_chip *chip, u32 invert)
अणु
	DECLARE_BITMAP(val, MAX_LINE);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = device_pca95xx_init(chip, invert);
	अगर (ret)
		जाओ out;

	/* To enable रेजिस्टर 6, 7 to control pull up and pull करोwn */
	क्रम (i = 0; i < NBANK(chip); i++)
		biपंचांगap_set_value8(val, 0x02, i * BANK_SZ);

	ret = pca953x_ग_लिखो_regs(chip, PCA957X_BKEN, val);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pca953x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा pca953x_platक्रमm_data *pdata;
	काष्ठा pca953x_chip *chip;
	पूर्णांक irq_base = 0;
	पूर्णांक ret;
	u32 invert = 0;
	काष्ठा regulator *reg;
	स्थिर काष्ठा regmap_config *regmap_config;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	pdata = dev_get_platdata(&client->dev);
	अगर (pdata) अणु
		irq_base = pdata->irq_base;
		chip->gpio_start = pdata->gpio_base;
		invert = pdata->invert;
		chip->names = pdata->names;
	पूर्ण अन्यथा अणु
		काष्ठा gpio_desc *reset_gpio;

		chip->gpio_start = -1;
		irq_base = 0;

		/*
		 * See अगर we need to de-निश्चित a reset pin.
		 *
		 * There is no known ACPI-enabled platक्रमms that are
		 * using "reset" GPIO. Otherwise any of those platक्रमm
		 * must use _DSD method with corresponding property.
		 */
		reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						     GPIOD_OUT_LOW);
		अगर (IS_ERR(reset_gpio))
			वापस PTR_ERR(reset_gpio);
	पूर्ण

	chip->client = client;

	reg = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(reg), "reg get err\n");

	ret = regulator_enable(reg);
	अगर (ret) अणु
		dev_err(&client->dev, "reg en err: %d\n", ret);
		वापस ret;
	पूर्ण
	chip->regulator = reg;

	अगर (i2c_id) अणु
		chip->driver_data = i2c_id->driver_data;
	पूर्ण अन्यथा अणु
		स्थिर व्योम *match;

		match = device_get_match_data(&client->dev);
		अगर (!match) अणु
			ret = -ENODEV;
			जाओ err_निकास;
		पूर्ण

		chip->driver_data = (uपूर्णांकptr_t)match;
	पूर्ण

	i2c_set_clientdata(client, chip);

	pca953x_setup_gpio(chip, chip->driver_data & PCA_GPIO_MASK);

	अगर (NBANK(chip) > 2 || PCA_CHIP_TYPE(chip->driver_data) == PCA957X_TYPE) अणु
		dev_info(&client->dev, "using AI\n");
		regmap_config = &pca953x_ai_i2c_regmap;
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "using no AI\n");
		regmap_config = &pca953x_i2c_regmap;
	पूर्ण

	chip->regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		जाओ err_निकास;
	पूर्ण

	regcache_mark_dirty(chip->regmap);

	mutex_init(&chip->i2c_lock);
	/*
	 * In हाल we have an i2c-mux controlled by a GPIO provided by an
	 * expander using the same driver higher on the device tree, पढ़ो the
	 * i2c adapter nesting depth and use the retrieved value as lockdep
	 * subclass क्रम chip->i2c_lock.
	 *
	 * REVISIT: This solution is not complete. It protects us from lockdep
	 * false positives when the expander controlling the i2c-mux is on
	 * a dअगरferent level on the device tree, but not when it's on the same
	 * level on a dअगरferent branch (in which हाल the subclass number
	 * would be the same).
	 *
	 * TODO: Once a correct solution is developed, a similar fix should be
	 * applied to all other i2c-controlled GPIO expanders (and potentially
	 * regmap-i2c).
	 */
	lockdep_set_subclass(&chip->i2c_lock,
			     i2c_adapter_depth(client->adapter));

	/* initialize cached रेजिस्टरs from their original values.
	 * we can't share this chip with another i2c master.
	 */

	अगर (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE) अणु
		chip->regs = &pca953x_regs;
		ret = device_pca95xx_init(chip, invert);
	पूर्ण अन्यथा अणु
		chip->regs = &pca957x_regs;
		ret = device_pca957x_init(chip, invert);
	पूर्ण
	अगर (ret)
		जाओ err_निकास;

	ret = pca953x_irq_setup(chip, irq_base);
	अगर (ret)
		जाओ err_निकास;

	ret = devm_gpiochip_add_data(&client->dev, &chip->gpio_chip, chip);
	अगर (ret)
		जाओ err_निकास;

	अगर (pdata && pdata->setup) अणु
		ret = pdata->setup(client, chip->gpio_chip.base,
				   chip->gpio_chip.ngpio, pdata->context);
		अगर (ret < 0)
			dev_warn(&client->dev, "setup failed, %d\n", ret);
	पूर्ण

	वापस 0;

err_निकास:
	regulator_disable(chip->regulator);
	वापस ret;
पूर्ण

अटल पूर्णांक pca953x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pca953x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा pca953x_chip *chip = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (pdata && pdata->tearकरोwn) अणु
		ret = pdata->tearकरोwn(client, chip->gpio_chip.base,
				      chip->gpio_chip.ngpio, pdata->context);
		अगर (ret < 0)
			dev_err(&client->dev, "teardown failed, %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	regulator_disable(chip->regulator);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pca953x_regcache_sync(काष्ठा device *dev)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);
	पूर्णांक ret;

	/*
	 * The ordering between direction and output is important,
	 * sync these रेजिस्टरs first and only then sync the rest.
	 */
	ret = regcache_sync_region(chip->regmap, chip->regs->direction,
				   chip->regs->direction + NBANK(chip));
	अगर (ret) अणु
		dev_err(dev, "Failed to sync GPIO dir registers: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regcache_sync_region(chip->regmap, chip->regs->output,
				   chip->regs->output + NBANK(chip));
	अगर (ret) अणु
		dev_err(dev, "Failed to sync GPIO out registers: %d\n", ret);
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_GPIO_PCA953X_IRQ
	अगर (chip->driver_data & PCA_PCAL) अणु
		ret = regcache_sync_region(chip->regmap, PCAL953X_IN_LATCH,
					   PCAL953X_IN_LATCH + NBANK(chip));
		अगर (ret) अणु
			dev_err(dev, "Failed to sync INT latch registers: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = regcache_sync_region(chip->regmap, PCAL953X_INT_MASK,
					   PCAL953X_INT_MASK + NBANK(chip));
		अगर (ret) अणु
			dev_err(dev, "Failed to sync INT mask registers: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक pca953x_suspend(काष्ठा device *dev)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);

	regcache_cache_only(chip->regmap, true);

	अगर (atomic_पढ़ो(&chip->wakeup_path))
		device_set_wakeup_path(dev);
	अन्यथा
		regulator_disable(chip->regulator);

	वापस 0;
पूर्ण

अटल पूर्णांक pca953x_resume(काष्ठा device *dev)
अणु
	काष्ठा pca953x_chip *chip = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!atomic_पढ़ो(&chip->wakeup_path)) अणु
		ret = regulator_enable(chip->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator: %d\n", ret);
			वापस 0;
		पूर्ण
	पूर्ण

	regcache_cache_only(chip->regmap, false);
	regcache_mark_dirty(chip->regmap);
	ret = pca953x_regcache_sync(dev);
	अगर (ret)
		वापस ret;

	ret = regcache_sync(chip->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to restore register map: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* convenience to stop overदीर्घ match-table lines */
#घोषणा OF_953X(__nrgpio, __पूर्णांक) (व्योम *)(__nrgpio | PCA953X_TYPE | __पूर्णांक)
#घोषणा OF_957X(__nrgpio, __पूर्णांक) (व्योम *)(__nrgpio | PCA957X_TYPE | __पूर्णांक)

अटल स्थिर काष्ठा of_device_id pca953x_dt_ids[] = अणु
	अणु .compatible = "nxp,pca6416", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9505", .data = OF_953X(40, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9506", .data = OF_953X(40, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9534", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9535", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9536", .data = OF_953X( 4, 0), पूर्ण,
	अणु .compatible = "nxp,pca9537", .data = OF_953X( 4, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9538", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9539", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9554", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9555", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9556", .data = OF_953X( 8, 0), पूर्ण,
	अणु .compatible = "nxp,pca9557", .data = OF_953X( 8, 0), पूर्ण,
	अणु .compatible = "nxp,pca9574", .data = OF_957X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9575", .data = OF_957X(16, PCA_INT), पूर्ण,
	अणु .compatible = "nxp,pca9698", .data = OF_953X(40, 0), पूर्ण,

	अणु .compatible = "nxp,pcal6416", .data = OF_953X(16, PCA_LATCH_INT), पूर्ण,
	अणु .compatible = "nxp,pcal6524", .data = OF_953X(24, PCA_LATCH_INT), पूर्ण,
	अणु .compatible = "nxp,pcal9535", .data = OF_953X(16, PCA_LATCH_INT), पूर्ण,
	अणु .compatible = "nxp,pcal9554b", .data = OF_953X( 8, PCA_LATCH_INT), पूर्ण,
	अणु .compatible = "nxp,pcal9555a", .data = OF_953X(16, PCA_LATCH_INT), पूर्ण,

	अणु .compatible = "maxim,max7310", .data = OF_953X( 8, 0), पूर्ण,
	अणु .compatible = "maxim,max7312", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "maxim,max7313", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "maxim,max7315", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "maxim,max7318", .data = OF_953X(16, PCA_INT), पूर्ण,

	अणु .compatible = "ti,pca6107", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "ti,pca9536", .data = OF_953X( 4, 0), पूर्ण,
	अणु .compatible = "ti,tca6408", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "ti,tca6416", .data = OF_953X(16, PCA_INT), पूर्ण,
	अणु .compatible = "ti,tca6424", .data = OF_953X(24, PCA_INT), पूर्ण,
	अणु .compatible = "ti,tca9539", .data = OF_953X(16, PCA_INT), पूर्ण,

	अणु .compatible = "onnn,cat9554", .data = OF_953X( 8, PCA_INT), पूर्ण,
	अणु .compatible = "onnn,pca9654", .data = OF_953X( 8, PCA_INT), पूर्ण,

	अणु .compatible = "exar,xra1202", .data = OF_953X( 8, 0), पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, pca953x_dt_ids);

अटल SIMPLE_DEV_PM_OPS(pca953x_pm_ops, pca953x_suspend, pca953x_resume);

अटल काष्ठा i2c_driver pca953x_driver = अणु
	.driver = अणु
		.name	= "pca953x",
		.pm	= &pca953x_pm_ops,
		.of_match_table = pca953x_dt_ids,
		.acpi_match_table = pca953x_acpi_ids,
	पूर्ण,
	.probe		= pca953x_probe,
	.हटाओ		= pca953x_हटाओ,
	.id_table	= pca953x_id,
पूर्ण;

अटल पूर्णांक __init pca953x_init(व्योम)
अणु
	वापस i2c_add_driver(&pca953x_driver);
पूर्ण
/* रेजिस्टर after i2c postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(pca953x_init);

अटल व्योम __निकास pca953x_निकास(व्योम)
अणु
	i2c_del_driver(&pca953x_driver);
पूर्ण
module_निकास(pca953x_निकास);

MODULE_AUTHOR("eric miao <eric.miao@marvell.com>");
MODULE_DESCRIPTION("GPIO expander driver for PCA953x");
MODULE_LICENSE("GPL");
