<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 IBM Corp.
 *
 * Joel Stanley <joel@jms.id.au>
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/aspeed.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>

/*
 * These two headers aren't meant to be used by GPIO drivers. We need
 * them in order to access gpio_chip_hwgpio() which we need to implement
 * the aspeed specअगरic API which allows the coprocessor to request
 * access to some GPIOs and to arbitrate between coprocessor and ARM.
 */
#समावेश <linux/gpio/consumer.h>
#समावेश "gpiolib.h"

काष्ठा aspeed_bank_props अणु
	अचिन्हित पूर्णांक bank;
	u32 input;
	u32 output;
पूर्ण;

काष्ठा aspeed_gpio_config अणु
	अचिन्हित पूर्णांक nr_gpios;
	स्थिर काष्ठा aspeed_bank_props *props;
पूर्ण;

/*
 * @offset_समयr: Maps an offset to an @समयr_users index, or zero अगर disabled
 * @समयr_users: Tracks the number of users क्रम each समयr
 *
 * The @समयr_users has four elements but the first element is unused. This is
 * to simplअगरy accounting and indexing, as a zero value in @offset_समयr
 * represents disabled debouncing क्रम the GPIO. Any other value क्रम an element
 * of @offset_समयr is used as an index पूर्णांकo @समयr_users. This behaviour of
 * the zero value aligns with the behaviour of zero built from the समयr
 * configuration रेजिस्टरs (i.e. debouncing is disabled).
 */
काष्ठा aspeed_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irqc;
	spinlock_t lock;
	व्योम __iomem *base;
	पूर्णांक irq;
	स्थिर काष्ठा aspeed_gpio_config *config;

	u8 *offset_समयr;
	अचिन्हित पूर्णांक समयr_users[4];
	काष्ठा clk *clk;

	u32 *dcache;
	u8 *cf_copro_bankmap;
पूर्ण;

काष्ठा aspeed_gpio_bank अणु
	uपूर्णांक16_t	val_regs;	/* +0: Rd: पढ़ो input value, Wr: set ग_लिखो latch
					 * +4: Rd/Wr: Direction (0=in, 1=out)
					 */
	uपूर्णांक16_t	rdata_reg;	/*     Rd: पढ़ो ग_लिखो latch, Wr: <none>  */
	uपूर्णांक16_t	irq_regs;
	uपूर्णांक16_t	debounce_regs;
	uपूर्णांक16_t	tolerance_regs;
	uपूर्णांक16_t	cmdsrc_regs;
	स्थिर अक्षर	names[4][3];
पूर्ण;

/*
 * Note: The "value" रेजिस्टर वापसs the input value sampled on the
 *       line even when the GPIO is configured as an output. Since
 *       that input goes through synchronizers, writing, then पढ़ोing
 *       back may not वापस the written value right away.
 *
 *       The "rdata" रेजिस्टर वापसs the content of the ग_लिखो latch
 *       and thus can be used to पढ़ो back what was last written
 *       reliably.
 */

अटल स्थिर पूर्णांक debounce_समयrs[4] = अणु 0x00, 0x50, 0x54, 0x58 पूर्ण;

अटल स्थिर काष्ठा aspeed_gpio_copro_ops *copro_ops;
अटल व्योम *copro_data;

अटल स्थिर काष्ठा aspeed_gpio_bank aspeed_gpio_banks[] = अणु
	अणु
		.val_regs = 0x0000,
		.rdata_reg = 0x00c0,
		.irq_regs = 0x0008,
		.debounce_regs = 0x0040,
		.tolerance_regs = 0x001c,
		.cmdsrc_regs = 0x0060,
		.names = अणु "A", "B", "C", "D" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0020,
		.rdata_reg = 0x00c4,
		.irq_regs = 0x0028,
		.debounce_regs = 0x0048,
		.tolerance_regs = 0x003c,
		.cmdsrc_regs = 0x0068,
		.names = अणु "E", "F", "G", "H" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0070,
		.rdata_reg = 0x00c8,
		.irq_regs = 0x0098,
		.debounce_regs = 0x00b0,
		.tolerance_regs = 0x00ac,
		.cmdsrc_regs = 0x0090,
		.names = अणु "I", "J", "K", "L" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0078,
		.rdata_reg = 0x00cc,
		.irq_regs = 0x00e8,
		.debounce_regs = 0x0100,
		.tolerance_regs = 0x00fc,
		.cmdsrc_regs = 0x00e0,
		.names = अणु "M", "N", "O", "P" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0080,
		.rdata_reg = 0x00d0,
		.irq_regs = 0x0118,
		.debounce_regs = 0x0130,
		.tolerance_regs = 0x012c,
		.cmdsrc_regs = 0x0110,
		.names = अणु "Q", "R", "S", "T" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0088,
		.rdata_reg = 0x00d4,
		.irq_regs = 0x0148,
		.debounce_regs = 0x0160,
		.tolerance_regs = 0x015c,
		.cmdsrc_regs = 0x0140,
		.names = अणु "U", "V", "W", "X" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x01E0,
		.rdata_reg = 0x00d8,
		.irq_regs = 0x0178,
		.debounce_regs = 0x0190,
		.tolerance_regs = 0x018c,
		.cmdsrc_regs = 0x0170,
		.names = अणु "Y", "Z", "AA", "AB" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x01e8,
		.rdata_reg = 0x00dc,
		.irq_regs = 0x01a8,
		.debounce_regs = 0x01c0,
		.tolerance_regs = 0x01bc,
		.cmdsrc_regs = 0x01a0,
		.names = अणु "AC", "", "", "" पूर्ण,
	पूर्ण,
पूर्ण;

क्रमागत aspeed_gpio_reg अणु
	reg_val,
	reg_rdata,
	reg_dir,
	reg_irq_enable,
	reg_irq_type0,
	reg_irq_type1,
	reg_irq_type2,
	reg_irq_status,
	reg_debounce_sel1,
	reg_debounce_sel2,
	reg_tolerance,
	reg_cmdsrc0,
	reg_cmdsrc1,
पूर्ण;

#घोषणा GPIO_VAL_VALUE	0x00
#घोषणा GPIO_VAL_सूची	0x04

#घोषणा GPIO_IRQ_ENABLE	0x00
#घोषणा GPIO_IRQ_TYPE0	0x04
#घोषणा GPIO_IRQ_TYPE1	0x08
#घोषणा GPIO_IRQ_TYPE2	0x0c
#घोषणा GPIO_IRQ_STATUS	0x10

#घोषणा GPIO_DEBOUNCE_SEL1 0x00
#घोषणा GPIO_DEBOUNCE_SEL2 0x04

#घोषणा GPIO_CMDSRC_0	0x00
#घोषणा GPIO_CMDSRC_1	0x04
#घोषणा  GPIO_CMDSRC_ARM		0
#घोषणा  GPIO_CMDSRC_LPC		1
#घोषणा  GPIO_CMDSRC_COLDFIRE		2
#घोषणा  GPIO_CMDSRC_RESERVED		3

/* This will be resolved at compile समय */
अटल अंतरभूत व्योम __iomem *bank_reg(काष्ठा aspeed_gpio *gpio,
				     स्थिर काष्ठा aspeed_gpio_bank *bank,
				     स्थिर क्रमागत aspeed_gpio_reg reg)
अणु
	चयन (reg) अणु
	हाल reg_val:
		वापस gpio->base + bank->val_regs + GPIO_VAL_VALUE;
	हाल reg_rdata:
		वापस gpio->base + bank->rdata_reg;
	हाल reg_dir:
		वापस gpio->base + bank->val_regs + GPIO_VAL_सूची;
	हाल reg_irq_enable:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_ENABLE;
	हाल reg_irq_type0:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE0;
	हाल reg_irq_type1:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE1;
	हाल reg_irq_type2:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE2;
	हाल reg_irq_status:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_STATUS;
	हाल reg_debounce_sel1:
		वापस gpio->base + bank->debounce_regs + GPIO_DEBOUNCE_SEL1;
	हाल reg_debounce_sel2:
		वापस gpio->base + bank->debounce_regs + GPIO_DEBOUNCE_SEL2;
	हाल reg_tolerance:
		वापस gpio->base + bank->tolerance_regs;
	हाल reg_cmdsrc0:
		वापस gpio->base + bank->cmdsrc_regs + GPIO_CMDSRC_0;
	हाल reg_cmdsrc1:
		वापस gpio->base + bank->cmdsrc_regs + GPIO_CMDSRC_1;
	पूर्ण
	BUG();
पूर्ण

#घोषणा GPIO_BANK(x)	((x) >> 5)
#घोषणा GPIO_OFFSET(x)	((x) & 0x1f)
#घोषणा GPIO_BIT(x)	BIT(GPIO_OFFSET(x))

#घोषणा _GPIO_SET_DEBOUNCE(t, o, i) ((!!((t) & BIT(i))) << GPIO_OFFSET(o))
#घोषणा GPIO_SET_DEBOUNCE1(t, o) _GPIO_SET_DEBOUNCE(t, o, 1)
#घोषणा GPIO_SET_DEBOUNCE2(t, o) _GPIO_SET_DEBOUNCE(t, o, 0)

अटल स्थिर काष्ठा aspeed_gpio_bank *to_bank(अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक bank = GPIO_BANK(offset);

	WARN_ON(bank >= ARRAY_SIZE(aspeed_gpio_banks));
	वापस &aspeed_gpio_banks[bank];
पूर्ण

अटल अंतरभूत bool is_bank_props_sentinel(स्थिर काष्ठा aspeed_bank_props *props)
अणु
	वापस !(props->input || props->output);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा aspeed_bank_props *find_bank_props(
		काष्ठा aspeed_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_bank_props *props = gpio->config->props;

	जबतक (!is_bank_props_sentinel(props)) अणु
		अगर (props->bank == GPIO_BANK(offset))
			वापस props;
		props++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool have_gpio(काष्ठा aspeed_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_bank_props *props = find_bank_props(gpio, offset);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	अचिन्हित पूर्णांक group = GPIO_OFFSET(offset) / 8;

	वापस bank->names[group][0] != '\0' &&
		(!props || ((props->input | props->output) & GPIO_BIT(offset)));
पूर्ण

अटल अंतरभूत bool have_input(काष्ठा aspeed_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_bank_props *props = find_bank_props(gpio, offset);

	वापस !props || (props->input & GPIO_BIT(offset));
पूर्ण

#घोषणा have_irq(g, o) have_input((g), (o))
#घोषणा have_debounce(g, o) have_input((g), (o))

अटल अंतरभूत bool have_output(काष्ठा aspeed_gpio *gpio, अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_bank_props *props = find_bank_props(gpio, offset);

	वापस !props || (props->output & GPIO_BIT(offset));
पूर्ण

अटल व्योम aspeed_gpio_change_cmd_source(काष्ठा aspeed_gpio *gpio,
					  स्थिर काष्ठा aspeed_gpio_bank *bank,
					  पूर्णांक bindex, पूर्णांक cmdsrc)
अणु
	व्योम __iomem *c0 = bank_reg(gpio, bank, reg_cmdsrc0);
	व्योम __iomem *c1 = bank_reg(gpio, bank, reg_cmdsrc1);
	u32 bit, reg;

	/*
	 * Each रेजिस्टर controls 4 banks, so take the bottom 2
	 * bits of the bank index, and use them to select the
	 * right control bit (0, 8, 16 or 24).
	 */
	bit = BIT((bindex & 3) << 3);

	/* Source 1 first to aव्योम illegal 11 combination */
	reg = ioपढ़ो32(c1);
	अगर (cmdsrc & 2)
		reg |= bit;
	अन्यथा
		reg &= ~bit;
	ioग_लिखो32(reg, c1);

	/* Then Source 0 */
	reg = ioपढ़ो32(c0);
	अगर (cmdsrc & 1)
		reg |= bit;
	अन्यथा
		reg &= ~bit;
	ioग_लिखो32(reg, c0);
पूर्ण

अटल bool aspeed_gpio_copro_request(काष्ठा aspeed_gpio *gpio,
				      अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);

	अगर (!copro_ops || !gpio->cf_copro_bankmap)
		वापस false;
	अगर (!gpio->cf_copro_bankmap[offset >> 3])
		वापस false;
	अगर (!copro_ops->request_access)
		वापस false;

	/* Pause the coprocessor */
	copro_ops->request_access(copro_data);

	/* Change command source back to ARM */
	aspeed_gpio_change_cmd_source(gpio, bank, offset >> 3, GPIO_CMDSRC_ARM);

	/* Update cache */
	gpio->dcache[GPIO_BANK(offset)] = ioपढ़ो32(bank_reg(gpio, bank, reg_rdata));

	वापस true;
पूर्ण

अटल व्योम aspeed_gpio_copro_release(काष्ठा aspeed_gpio *gpio,
				      अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);

	अगर (!copro_ops || !gpio->cf_copro_bankmap)
		वापस;
	अगर (!gpio->cf_copro_bankmap[offset >> 3])
		वापस;
	अगर (!copro_ops->release_access)
		वापस;

	/* Change command source back to ColdFire */
	aspeed_gpio_change_cmd_source(gpio, bank, offset >> 3,
				      GPIO_CMDSRC_COLDFIRE);

	/* Restart the coprocessor */
	copro_ops->release_access(copro_data);
पूर्ण

अटल पूर्णांक aspeed_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);

	वापस !!(ioपढ़ो32(bank_reg(gpio, bank, reg_val)) & GPIO_BIT(offset));
पूर्ण

अटल व्योम __aspeed_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			      पूर्णांक val)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	व्योम __iomem *addr;
	u32 reg;

	addr = bank_reg(gpio, bank, reg_val);
	reg = gpio->dcache[GPIO_BANK(offset)];

	अगर (val)
		reg |= GPIO_BIT(offset);
	अन्यथा
		reg &= ~GPIO_BIT(offset);
	gpio->dcache[GPIO_BANK(offset)] = reg;

	ioग_लिखो32(reg, addr);
पूर्ण

अटल व्योम aspeed_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			    पूर्णांक val)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	bool copro;

	spin_lock_irqsave(&gpio->lock, flags);
	copro = aspeed_gpio_copro_request(gpio, offset);

	__aspeed_gpio_set(gc, offset, val);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल पूर्णांक aspeed_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	व्योम __iomem *addr = bank_reg(gpio, bank, reg_dir);
	अचिन्हित दीर्घ flags;
	bool copro;
	u32 reg;

	अगर (!have_input(gpio, offset))
		वापस -ENOTSUPP;

	spin_lock_irqsave(&gpio->lock, flags);

	reg = ioपढ़ो32(addr);
	reg &= ~GPIO_BIT(offset);

	copro = aspeed_gpio_copro_request(gpio, offset);
	ioग_लिखो32(reg, addr);
	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);

	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_gpio_dir_out(काष्ठा gpio_chip *gc,
			       अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	व्योम __iomem *addr = bank_reg(gpio, bank, reg_dir);
	अचिन्हित दीर्घ flags;
	bool copro;
	u32 reg;

	अगर (!have_output(gpio, offset))
		वापस -ENOTSUPP;

	spin_lock_irqsave(&gpio->lock, flags);

	reg = ioपढ़ो32(addr);
	reg |= GPIO_BIT(offset);

	copro = aspeed_gpio_copro_request(gpio, offset);
	__aspeed_gpio_set(gc, offset, val);
	ioग_लिखो32(reg, addr);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!have_input(gpio, offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	अगर (!have_output(gpio, offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	spin_lock_irqsave(&gpio->lock, flags);

	val = ioपढ़ो32(bank_reg(gpio, bank, reg_dir)) & GPIO_BIT(offset);

	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस val ? GPIO_LINE_सूचीECTION_OUT : GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल अंतरभूत पूर्णांक irqd_to_aspeed_gpio_data(काष्ठा irq_data *d,
					   काष्ठा aspeed_gpio **gpio,
					   स्थिर काष्ठा aspeed_gpio_bank **bank,
					   u32 *bit, पूर्णांक *offset)
अणु
	काष्ठा aspeed_gpio *पूर्णांकernal;

	*offset = irqd_to_hwirq(d);

	पूर्णांकernal = irq_data_get_irq_chip_data(d);

	/* This might be a bit of a questionable place to check */
	अगर (!have_irq(पूर्णांकernal, *offset))
		वापस -ENOTSUPP;

	*gpio = पूर्णांकernal;
	*bank = to_bank(*offset);
	*bit = GPIO_BIT(*offset);

	वापस 0;
पूर्ण

अटल व्योम aspeed_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	स्थिर काष्ठा aspeed_gpio_bank *bank;
	काष्ठा aspeed_gpio *gpio;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *status_addr;
	पूर्णांक rc, offset;
	bool copro;
	u32 bit;

	rc = irqd_to_aspeed_gpio_data(d, &gpio, &bank, &bit, &offset);
	अगर (rc)
		वापस;

	status_addr = bank_reg(gpio, bank, reg_irq_status);

	spin_lock_irqsave(&gpio->lock, flags);
	copro = aspeed_gpio_copro_request(gpio, offset);

	ioग_लिखो32(bit, status_addr);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल व्योम aspeed_gpio_irq_set_mask(काष्ठा irq_data *d, bool set)
अणु
	स्थिर काष्ठा aspeed_gpio_bank *bank;
	काष्ठा aspeed_gpio *gpio;
	अचिन्हित दीर्घ flags;
	u32 reg, bit;
	व्योम __iomem *addr;
	पूर्णांक rc, offset;
	bool copro;

	rc = irqd_to_aspeed_gpio_data(d, &gpio, &bank, &bit, &offset);
	अगर (rc)
		वापस;

	addr = bank_reg(gpio, bank, reg_irq_enable);

	spin_lock_irqsave(&gpio->lock, flags);
	copro = aspeed_gpio_copro_request(gpio, offset);

	reg = ioपढ़ो32(addr);
	अगर (set)
		reg |= bit;
	अन्यथा
		reg &= ~bit;
	ioग_लिखो32(reg, addr);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल व्योम aspeed_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	aspeed_gpio_irq_set_mask(d, false);
पूर्ण

अटल व्योम aspeed_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	aspeed_gpio_irq_set_mask(d, true);
पूर्ण

अटल पूर्णांक aspeed_gpio_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	u32 type0 = 0;
	u32 type1 = 0;
	u32 type2 = 0;
	u32 bit, reg;
	स्थिर काष्ठा aspeed_gpio_bank *bank;
	irq_flow_handler_t handler;
	काष्ठा aspeed_gpio *gpio;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;
	पूर्णांक rc, offset;
	bool copro;

	rc = irqd_to_aspeed_gpio_data(d, &gpio, &bank, &bit, &offset);
	अगर (rc)
		वापस -EINVAL;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		type2 |= bit;
		fallthrough;
	हाल IRQ_TYPE_EDGE_RISING:
		type0 |= bit;
		fallthrough;
	हाल IRQ_TYPE_EDGE_FALLING:
		handler = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		type0 |= bit;
		fallthrough;
	हाल IRQ_TYPE_LEVEL_LOW:
		type1 |= bit;
		handler = handle_level_irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&gpio->lock, flags);
	copro = aspeed_gpio_copro_request(gpio, offset);

	addr = bank_reg(gpio, bank, reg_irq_type0);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type0;
	ioग_लिखो32(reg, addr);

	addr = bank_reg(gpio, bank, reg_irq_type1);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type1;
	ioग_लिखो32(reg, addr);

	addr = bank_reg(gpio, bank, reg_irq_type2);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type2;
	ioग_लिखो32(reg, addr);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);

	irq_set_handler_locked(d, handler);

	वापस 0;
पूर्ण

अटल व्योम aspeed_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	काष्ठा aspeed_gpio *data = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक i, p, girq, banks;
	अचिन्हित दीर्घ reg;
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);

	chained_irq_enter(ic, desc);

	banks = DIV_ROUND_UP(gpio->chip.ngpio, 32);
	क्रम (i = 0; i < banks; i++) अणु
		स्थिर काष्ठा aspeed_gpio_bank *bank = &aspeed_gpio_banks[i];

		reg = ioपढ़ो32(bank_reg(data, bank, reg_irq_status));

		क्रम_each_set_bit(p, &reg, 32) अणु
			girq = irq_find_mapping(gc->irq.करोमुख्य, i * 32 + p);
			generic_handle_irq(girq);
		पूर्ण

	पूर्ण

	chained_irq_निकास(ic, desc);
पूर्ण

अटल व्योम aspeed_init_irq_valid_mask(काष्ठा gpio_chip *gc,
				       अचिन्हित दीर्घ *valid_mask,
				       अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_bank_props *props = gpio->config->props;

	जबतक (!is_bank_props_sentinel(props)) अणु
		अचिन्हित पूर्णांक offset;
		स्थिर अचिन्हित दीर्घ पूर्णांक input = props->input;

		/* Pretty crummy approach, but similar to GPIO core */
		क्रम_each_clear_bit(offset, &input, 32) अणु
			अचिन्हित पूर्णांक i = props->bank * 32 + offset;

			अगर (i >= gpio->chip.ngpio)
				अवरोध;

			clear_bit(i, valid_mask);
		पूर्ण

		props++;
	पूर्ण
पूर्ण

अटल पूर्णांक aspeed_gpio_reset_tolerance(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, bool enable)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *treg;
	bool copro;
	u32 val;

	treg = bank_reg(gpio, to_bank(offset), reg_tolerance);

	spin_lock_irqsave(&gpio->lock, flags);
	copro = aspeed_gpio_copro_request(gpio, offset);

	val = पढ़ोl(treg);

	अगर (enable)
		val |= GPIO_BIT(offset);
	अन्यथा
		val &= ~GPIO_BIT(offset);

	ग_लिखोl(val, treg);

	अगर (copro)
		aspeed_gpio_copro_release(gpio, offset);
	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	अगर (!have_gpio(gpiochip_get_data(chip), offset))
		वापस -ENODEV;

	वापस pinctrl_gpio_request(chip->base + offset);
पूर्ण

अटल व्योम aspeed_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	pinctrl_gpio_मुक्त(chip->base + offset);
पूर्ण

अटल पूर्णांक usecs_to_cycles(काष्ठा aspeed_gpio *gpio, अचिन्हित दीर्घ usecs,
		u32 *cycles)
अणु
	u64 rate;
	u64 n;
	u32 r;

	rate = clk_get_rate(gpio->clk);
	अगर (!rate)
		वापस -ENOTSUPP;

	n = rate * usecs;
	r = करो_भाग(n, 1000000);

	अगर (n >= U32_MAX)
		वापस -दुस्फल;

	/* At least as दीर्घ as the requested समय */
	*cycles = n + (!!r);

	वापस 0;
पूर्ण

/* Call under gpio->lock */
अटल पूर्णांक रेजिस्टर_allocated_समयr(काष्ठा aspeed_gpio *gpio,
		अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक समयr)
अणु
	अगर (WARN(gpio->offset_समयr[offset] != 0,
				"Offset %d already allocated timer %d\n",
				offset, gpio->offset_समयr[offset]))
		वापस -EINVAL;

	अगर (WARN(gpio->समयr_users[समयr] == अच_पूर्णांक_उच्च,
				"Timer user count would overflow\n"))
		वापस -EPERM;

	gpio->offset_समयr[offset] = समयr;
	gpio->समयr_users[समयr]++;

	वापस 0;
पूर्ण

/* Call under gpio->lock */
अटल पूर्णांक unरेजिस्टर_allocated_समयr(काष्ठा aspeed_gpio *gpio,
		अचिन्हित पूर्णांक offset)
अणु
	अगर (WARN(gpio->offset_समयr[offset] == 0,
				"No timer allocated to offset %d\n", offset))
		वापस -EINVAL;

	अगर (WARN(gpio->समयr_users[gpio->offset_समयr[offset]] == 0,
				"No users recorded for timer %d\n",
				gpio->offset_समयr[offset]))
		वापस -EINVAL;

	gpio->समयr_users[gpio->offset_समयr[offset]]--;
	gpio->offset_समयr[offset] = 0;

	वापस 0;
पूर्ण

/* Call under gpio->lock */
अटल अंतरभूत bool समयr_allocation_रेजिस्टरed(काष्ठा aspeed_gpio *gpio,
		अचिन्हित पूर्णांक offset)
अणु
	वापस gpio->offset_समयr[offset] > 0;
पूर्ण

/* Call under gpio->lock */
अटल व्योम configure_समयr(काष्ठा aspeed_gpio *gpio, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक समयr)
अणु
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	स्थिर u32 mask = GPIO_BIT(offset);
	व्योम __iomem *addr;
	u32 val;

	/* Note: Debounce समयr isn't under control of the command
	 * source रेजिस्टरs, so no need to sync with the coprocessor
	 */
	addr = bank_reg(gpio, bank, reg_debounce_sel1);
	val = ioपढ़ो32(addr);
	ioग_लिखो32((val & ~mask) | GPIO_SET_DEBOUNCE1(समयr, offset), addr);

	addr = bank_reg(gpio, bank, reg_debounce_sel2);
	val = ioपढ़ो32(addr);
	ioग_लिखो32((val & ~mask) | GPIO_SET_DEBOUNCE2(समयr, offset), addr);
पूर्ण

अटल पूर्णांक enable_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    अचिन्हित दीर्घ usecs)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);
	u32 requested_cycles;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	पूर्णांक i;

	अगर (!gpio->clk)
		वापस -EINVAL;

	rc = usecs_to_cycles(gpio, usecs, &requested_cycles);
	अगर (rc < 0) अणु
		dev_warn(chip->parent, "Failed to convert %luus to cycles at %luHz: %d\n",
				usecs, clk_get_rate(gpio->clk), rc);
		वापस rc;
	पूर्ण

	spin_lock_irqsave(&gpio->lock, flags);

	अगर (समयr_allocation_रेजिस्टरed(gpio, offset)) अणु
		rc = unरेजिस्टर_allocated_समयr(gpio, offset);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	/* Try to find a समयr alपढ़ोy configured क्रम the debounce period */
	क्रम (i = 1; i < ARRAY_SIZE(debounce_समयrs); i++) अणु
		u32 cycles;

		cycles = ioपढ़ो32(gpio->base + debounce_समयrs[i]);
		अगर (requested_cycles == cycles)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(debounce_समयrs)) अणु
		पूर्णांक j;

		/*
		 * As there are no समयrs configured क्रम the requested debounce
		 * period, find an unused समयr instead
		 */
		क्रम (j = 1; j < ARRAY_SIZE(gpio->समयr_users); j++) अणु
			अगर (gpio->समयr_users[j] == 0)
				अवरोध;
		पूर्ण

		अगर (j == ARRAY_SIZE(gpio->समयr_users)) अणु
			dev_warn(chip->parent,
					"Debounce timers exhausted, cannot debounce for period %luus\n",
					usecs);

			rc = -EPERM;

			/*
			 * We alपढ़ोy adjusted the accounting to हटाओ @offset
			 * as a user of its previous समयr, so also configure
			 * the hardware so @offset has समयrs disabled क्रम
			 * consistency.
			 */
			configure_समयr(gpio, offset, 0);
			जाओ out;
		पूर्ण

		i = j;

		ioग_लिखो32(requested_cycles, gpio->base + debounce_समयrs[i]);
	पूर्ण

	अगर (WARN(i == 0, "Cannot register index of disabled timer\n")) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	रेजिस्टर_allocated_समयr(gpio, offset, i);
	configure_समयr(gpio, offset, i);

out:
	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक disable_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&gpio->lock, flags);

	rc = unरेजिस्टर_allocated_समयr(gpio, offset);
	अगर (!rc)
		configure_समयr(gpio, offset, 0);

	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक set_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    अचिन्हित दीर्घ usecs)
अणु
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);

	अगर (!have_debounce(gpio, offset))
		वापस -ENOTSUPP;

	अगर (usecs)
		वापस enable_debounce(chip, offset, usecs);

	वापस disable_debounce(chip, offset);
पूर्ण

अटल पूर्णांक aspeed_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);

	अगर (param == PIN_CONFIG_INPUT_DEBOUNCE)
		वापस set_debounce(chip, offset, arg);
	अन्यथा अगर (param == PIN_CONFIG_BIAS_DISABLE ||
			param == PIN_CONFIG_BIAS_PULL_DOWN ||
			param == PIN_CONFIG_DRIVE_STRENGTH)
		वापस pinctrl_gpio_set_config(offset, config);
	अन्यथा अगर (param == PIN_CONFIG_DRIVE_OPEN_DRAIN ||
			param == PIN_CONFIG_DRIVE_OPEN_SOURCE)
		/* Return -ENOTSUPP to trigger emulation, as per datasheet */
		वापस -ENOTSUPP;
	अन्यथा अगर (param == PIN_CONFIG_PERSIST_STATE)
		वापस aspeed_gpio_reset_tolerance(chip, offset, arg);

	वापस -ENOTSUPP;
पूर्ण

/**
 * aspeed_gpio_copro_set_ops - Sets the callbacks used क्रम handshaking with
 *                             the coprocessor क्रम shared GPIO banks
 * @ops: The callbacks
 * @data: Poपूर्णांकer passed back to the callbacks
 */
पूर्णांक aspeed_gpio_copro_set_ops(स्थिर काष्ठा aspeed_gpio_copro_ops *ops, व्योम *data)
अणु
	copro_data = data;
	copro_ops = ops;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(aspeed_gpio_copro_set_ops);

/**
 * aspeed_gpio_copro_grab_gpio - Mark a GPIO used by the coprocessor. The entire
 *                               bank माला_लो marked and any access from the ARM will
 *                               result in handshaking via callbacks.
 * @desc: The GPIO to be marked
 * @vreg_offset: If non-शून्य, वापसs the value रेजिस्टर offset in the GPIO space
 * @dreg_offset: If non-शून्य, वापसs the data latch रेजिस्टर offset in the GPIO space
 * @bit: If non-शून्य, वापसs the bit number of the GPIO in the रेजिस्टरs
 */
पूर्णांक aspeed_gpio_copro_grab_gpio(काष्ठा gpio_desc *desc,
				u16 *vreg_offset, u16 *dreg_offset, u8 *bit)
अणु
	काष्ठा gpio_chip *chip = gpiod_to_chip(desc);
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक rc = 0, bindex, offset = gpio_chip_hwgpio(desc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	अचिन्हित दीर्घ flags;

	अगर (!gpio->cf_copro_bankmap)
		gpio->cf_copro_bankmap = kzalloc(gpio->chip.ngpio >> 3, GFP_KERNEL);
	अगर (!gpio->cf_copro_bankmap)
		वापस -ENOMEM;
	अगर (offset < 0 || offset > gpio->chip.ngpio)
		वापस -EINVAL;
	bindex = offset >> 3;

	spin_lock_irqsave(&gpio->lock, flags);

	/* Sanity check, this shouldn't happen */
	अगर (gpio->cf_copro_bankmap[bindex] == 0xff) अणु
		rc = -EIO;
		जाओ bail;
	पूर्ण
	gpio->cf_copro_bankmap[bindex]++;

	/* Switch command source */
	अगर (gpio->cf_copro_bankmap[bindex] == 1)
		aspeed_gpio_change_cmd_source(gpio, bank, bindex,
					      GPIO_CMDSRC_COLDFIRE);

	अगर (vreg_offset)
		*vreg_offset = bank->val_regs;
	अगर (dreg_offset)
		*dreg_offset = bank->rdata_reg;
	अगर (bit)
		*bit = GPIO_OFFSET(offset);
 bail:
	spin_unlock_irqrestore(&gpio->lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(aspeed_gpio_copro_grab_gpio);

/**
 * aspeed_gpio_copro_release_gpio - Unmark a GPIO used by the coprocessor.
 * @desc: The GPIO to be marked
 */
पूर्णांक aspeed_gpio_copro_release_gpio(काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpio_chip *chip = gpiod_to_chip(desc);
	काष्ठा aspeed_gpio *gpio = gpiochip_get_data(chip);
	पूर्णांक rc = 0, bindex, offset = gpio_chip_hwgpio(desc);
	स्थिर काष्ठा aspeed_gpio_bank *bank = to_bank(offset);
	अचिन्हित दीर्घ flags;

	अगर (!gpio->cf_copro_bankmap)
		वापस -ENXIO;

	अगर (offset < 0 || offset > gpio->chip.ngpio)
		वापस -EINVAL;
	bindex = offset >> 3;

	spin_lock_irqsave(&gpio->lock, flags);

	/* Sanity check, this shouldn't happen */
	अगर (gpio->cf_copro_bankmap[bindex] == 0) अणु
		rc = -EIO;
		जाओ bail;
	पूर्ण
	gpio->cf_copro_bankmap[bindex]--;

	/* Switch command source */
	अगर (gpio->cf_copro_bankmap[bindex] == 0)
		aspeed_gpio_change_cmd_source(gpio, bank, bindex,
					      GPIO_CMDSRC_ARM);
 bail:
	spin_unlock_irqrestore(&gpio->lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(aspeed_gpio_copro_release_gpio);

/*
 * Any banks not specअगरied in a काष्ठा aspeed_bank_props array are assumed to
 * have the properties:
 *
 *     अणु .input = 0xffffffff, .output = 0xffffffff पूर्ण
 */

अटल स्थिर काष्ठा aspeed_bank_props ast2400_bank_props[] = अणु
	/*     input	  output   */
	अणु 5, 0xffffffff, 0x0000ffff पूर्ण, /* U/V/W/X */
	अणु 6, 0x0000000f, 0x0fffff0f पूर्ण, /* Y/Z/AA/AB, two 4-GPIO holes */
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aspeed_gpio_config ast2400_config =
	/* 220 क्रम simplicity, really 216 with two 4-GPIO holes, four at end */
	अणु .nr_gpios = 220, .props = ast2400_bank_props, पूर्ण;

अटल स्थिर काष्ठा aspeed_bank_props ast2500_bank_props[] = अणु
	/*     input	  output   */
	अणु 5, 0xffffffff, 0x0000ffff पूर्ण, /* U/V/W/X */
	अणु 6, 0x0fffffff, 0x0fffffff पूर्ण, /* Y/Z/AA/AB, 4-GPIO hole */
	अणु 7, 0x000000ff, 0x000000ff पूर्ण, /* AC */
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aspeed_gpio_config ast2500_config =
	/* 232 क्रम simplicity, actual number is 228 (4-GPIO hole in GPIOAB) */
	अणु .nr_gpios = 232, .props = ast2500_bank_props, पूर्ण;

अटल स्थिर काष्ठा aspeed_bank_props ast2600_bank_props[] = अणु
	/*     input	  output   */
	अणु4, 0xffffffff,  0x00ffffffपूर्ण, /* Q/R/S/T */
	अणु5, 0xffffffff,  0xffffff00पूर्ण, /* U/V/W/X */
	अणु6, 0x0000ffff,  0x0000ffffपूर्ण, /* Y/Z */
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aspeed_gpio_config ast2600_config =
	/*
	 * ast2600 has two controllers one with 208 GPIOs and one with 36 GPIOs.
	 * We expect ngpio being set in the device tree and this is a fallback
	 * option.
	 */
	अणु .nr_gpios = 208, .props = ast2600_bank_props, पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_gpio_of_table[] = अणु
	अणु .compatible = "aspeed,ast2400-gpio", .data = &ast2400_config, पूर्ण,
	अणु .compatible = "aspeed,ast2500-gpio", .data = &ast2500_config, पूर्ण,
	अणु .compatible = "aspeed,ast2600-gpio", .data = &ast2600_config, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_gpio_of_table);

अटल पूर्णांक __init aspeed_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *gpio_id;
	काष्ठा aspeed_gpio *gpio;
	पूर्णांक rc, i, banks, err;
	u32 ngpio;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->base))
		वापस PTR_ERR(gpio->base);

	spin_lock_init(&gpio->lock);

	gpio_id = of_match_node(aspeed_gpio_of_table, pdev->dev.of_node);
	अगर (!gpio_id)
		वापस -EINVAL;

	gpio->clk = of_clk_get(pdev->dev.of_node, 0);
	अगर (IS_ERR(gpio->clk)) अणु
		dev_warn(&pdev->dev,
				"Failed to get clock from devicetree, debouncing disabled\n");
		gpio->clk = शून्य;
	पूर्ण

	gpio->config = gpio_id->data;

	gpio->chip.parent = &pdev->dev;
	err = of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &ngpio);
	gpio->chip.ngpio = (u16) ngpio;
	अगर (err)
		gpio->chip.ngpio = gpio->config->nr_gpios;
	gpio->chip.direction_input = aspeed_gpio_dir_in;
	gpio->chip.direction_output = aspeed_gpio_dir_out;
	gpio->chip.get_direction = aspeed_gpio_get_direction;
	gpio->chip.request = aspeed_gpio_request;
	gpio->chip.मुक्त = aspeed_gpio_मुक्त;
	gpio->chip.get = aspeed_gpio_get;
	gpio->chip.set = aspeed_gpio_set;
	gpio->chip.set_config = aspeed_gpio_set_config;
	gpio->chip.label = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	/* Allocate a cache of the output रेजिस्टरs */
	banks = DIV_ROUND_UP(gpio->chip.ngpio, 32);
	gpio->dcache = devm_kसुस्मृति(&pdev->dev,
				    banks, माप(u32), GFP_KERNEL);
	अगर (!gpio->dcache)
		वापस -ENOMEM;

	/*
	 * Populate it with initial values पढ़ो from the HW and चयन
	 * all command sources to the ARM by शेष
	 */
	क्रम (i = 0; i < banks; i++) अणु
		स्थिर काष्ठा aspeed_gpio_bank *bank = &aspeed_gpio_banks[i];
		व्योम __iomem *addr = bank_reg(gpio, bank, reg_rdata);
		gpio->dcache[i] = ioपढ़ो32(addr);
		aspeed_gpio_change_cmd_source(gpio, bank, 0, GPIO_CMDSRC_ARM);
		aspeed_gpio_change_cmd_source(gpio, bank, 1, GPIO_CMDSRC_ARM);
		aspeed_gpio_change_cmd_source(gpio, bank, 2, GPIO_CMDSRC_ARM);
		aspeed_gpio_change_cmd_source(gpio, bank, 3, GPIO_CMDSRC_ARM);
	पूर्ण

	/* Optionally set up an irqchip अगर there is an IRQ */
	rc = platक्रमm_get_irq(pdev, 0);
	अगर (rc > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		gpio->irq = rc;
		girq = &gpio->chip.irq;
		girq->chip = &gpio->irqc;
		girq->chip->name = dev_name(&pdev->dev);
		girq->chip->irq_ack = aspeed_gpio_irq_ack;
		girq->chip->irq_mask = aspeed_gpio_irq_mask;
		girq->chip->irq_unmask = aspeed_gpio_irq_unmask;
		girq->chip->irq_set_type = aspeed_gpio_set_type;
		girq->parent_handler = aspeed_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = gpio->irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
		girq->init_valid_mask = aspeed_init_irq_valid_mask;
	पूर्ण

	gpio->offset_समयr =
		devm_kzalloc(&pdev->dev, gpio->chip.ngpio, GFP_KERNEL);
	अगर (!gpio->offset_समयr)
		वापस -ENOMEM;

	rc = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_gpio_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = aspeed_gpio_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(aspeed_gpio_driver, aspeed_gpio_probe);

MODULE_DESCRIPTION("Aspeed GPIO Driver");
MODULE_LICENSE("GPL");
