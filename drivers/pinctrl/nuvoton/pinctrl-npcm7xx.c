<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2016-2018 Nuvoton Technology corporation.
// Copyright (c) 2016, Dell Inc

#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* GCR रेजिस्टरs */
#घोषणा NPCM7XX_GCR_PDID	0x00
#घोषणा NPCM7XX_GCR_MFSEL1	0x0C
#घोषणा NPCM7XX_GCR_MFSEL2	0x10
#घोषणा NPCM7XX_GCR_MFSEL3	0x64
#घोषणा NPCM7XX_GCR_MFSEL4	0xb0
#घोषणा NPCM7XX_GCR_CPCTL	0xD0
#घोषणा NPCM7XX_GCR_CP2BST	0xD4
#घोषणा NPCM7XX_GCR_B2CPNT	0xD8
#घोषणा NPCM7XX_GCR_I2CSEGSEL	0xE0
#घोषणा NPCM7XX_GCR_I2CSEGCTL	0xE4
#घोषणा NPCM7XX_GCR_SRCNT	0x68
#घोषणा NPCM7XX_GCR_FLOCKR1	0x74
#घोषणा NPCM7XX_GCR_DSCNT	0x78

#घोषणा SRCNT_ESPI		BIT(3)

/* GPIO रेजिस्टरs */
#घोषणा NPCM7XX_GP_N_TLOCK1	0x00
#घोषणा NPCM7XX_GP_N_DIN	0x04 /* Data IN */
#घोषणा NPCM7XX_GP_N_POL	0x08 /* Polarity */
#घोषणा NPCM7XX_GP_N_DOUT	0x0c /* Data OUT */
#घोषणा NPCM7XX_GP_N_OE		0x10 /* Output Enable */
#घोषणा NPCM7XX_GP_N_OTYP	0x14
#घोषणा NPCM7XX_GP_N_MP		0x18
#घोषणा NPCM7XX_GP_N_PU		0x1c /* Pull-up */
#घोषणा NPCM7XX_GP_N_PD		0x20 /* Pull-करोwn */
#घोषणा NPCM7XX_GP_N_DBNC	0x24 /* Debounce */
#घोषणा NPCM7XX_GP_N_EVTYP	0x28 /* Event Type */
#घोषणा NPCM7XX_GP_N_EVBE	0x2c /* Event Both Edge */
#घोषणा NPCM7XX_GP_N_OBL0	0x30
#घोषणा NPCM7XX_GP_N_OBL1	0x34
#घोषणा NPCM7XX_GP_N_OBL2	0x38
#घोषणा NPCM7XX_GP_N_OBL3	0x3c
#घोषणा NPCM7XX_GP_N_EVEN	0x40 /* Event Enable */
#घोषणा NPCM7XX_GP_N_EVENS	0x44 /* Event Set (enable) */
#घोषणा NPCM7XX_GP_N_EVENC	0x48 /* Event Clear (disable) */
#घोषणा NPCM7XX_GP_N_EVST	0x4c /* Event Status */
#घोषणा NPCM7XX_GP_N_SPLCK	0x50
#घोषणा NPCM7XX_GP_N_MPLCK	0x54
#घोषणा NPCM7XX_GP_N_IEM	0x58 /* Input Enable */
#घोषणा NPCM7XX_GP_N_OSRC	0x5c
#घोषणा NPCM7XX_GP_N_ODSC	0x60
#घोषणा NPCM7XX_GP_N_DOS	0x68 /* Data OUT Set */
#घोषणा NPCM7XX_GP_N_DOC	0x6c /* Data OUT Clear */
#घोषणा NPCM7XX_GP_N_OES	0x70 /* Output Enable Set */
#घोषणा NPCM7XX_GP_N_OEC	0x74 /* Output Enable Clear */
#घोषणा NPCM7XX_GP_N_TLOCK2	0x7c

#घोषणा NPCM7XX_GPIO_PER_BANK	32
#घोषणा NPCM7XX_GPIO_BANK_NUM	8
#घोषणा NPCM7XX_GCR_NONE	0

/* Structure क्रम रेजिस्टर banks */
काष्ठा npcm7xx_gpio अणु
	व्योम __iomem		*base;
	काष्ठा gpio_chip	gc;
	पूर्णांक			irqbase;
	पूर्णांक			irq;
	व्योम			*priv;
	काष्ठा irq_chip		irq_chip;
	u32			pinctrl_id;
	पूर्णांक (*direction_input)(काष्ठा gpio_chip *chip, अचिन्हित offset);
	पूर्णांक (*direction_output)(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक value);
	पूर्णांक (*request)(काष्ठा gpio_chip *chip, अचिन्हित offset);
	व्योम (*मुक्त)(काष्ठा gpio_chip *chip, अचिन्हित offset);
पूर्ण;

काष्ठा npcm7xx_pinctrl अणु
	काष्ठा pinctrl_dev	*pctldev;
	काष्ठा device		*dev;
	काष्ठा npcm7xx_gpio	gpio_bank[NPCM7XX_GPIO_BANK_NUM];
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा regmap		*gcr_regmap;
	व्योम __iomem		*regs;
	u32			bank_num;
पूर्ण;

/* GPIO handling in the pinctrl driver */
अटल व्योम npcm_gpio_set(काष्ठा gpio_chip *gc, व्योम __iomem *reg,
			  अचिन्हित पूर्णांक pinmask)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	val = ioपढ़ो32(reg) | pinmask;
	ioग_लिखो32(val, reg);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम npcm_gpio_clr(काष्ठा gpio_chip *gc, व्योम __iomem *reg,
			  अचिन्हित पूर्णांक pinmask)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	val = ioपढ़ो32(reg) & ~pinmask;
	ioग_लिखो32(val, reg);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम npcmgpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा npcm7xx_gpio *bank = gpiochip_get_data(chip);

	seq_म_लिखो(s, "-- module %d [gpio%d - %d]\n",
		   bank->gc.base / bank->gc.ngpio,
		   bank->gc.base,
		   bank->gc.base + bank->gc.ngpio);
	seq_म_लिखो(s, "DIN :%.8x DOUT:%.8x IE  :%.8x OE	 :%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_DIN),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_DOUT),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_IEM),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OE));
	seq_म_लिखो(s, "PU  :%.8x PD  :%.8x DB  :%.8x POL :%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_PU),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_PD),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_DBNC),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_POL));
	seq_म_लिखो(s, "ETYP:%.8x EVBE:%.8x EVEN:%.8x EVST:%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVTYP),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVBE),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVEN),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVST));
	seq_म_लिखो(s, "OTYP:%.8x OSRC:%.8x ODSC:%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OTYP),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OSRC),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_ODSC));
	seq_म_लिखो(s, "OBL0:%.8x OBL1:%.8x OBL2:%.8x OBL3:%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OBL0),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OBL1),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OBL2),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_OBL3));
	seq_म_लिखो(s, "SLCK:%.8x MLCK:%.8x\n",
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_SPLCK),
		   ioपढ़ो32(bank->base + NPCM7XX_GP_N_MPLCK));
पूर्ण

अटल पूर्णांक npcmgpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा npcm7xx_gpio *bank = gpiochip_get_data(chip);
	पूर्णांक ret;

	ret = pinctrl_gpio_direction_input(offset + chip->base);
	अगर (ret)
		वापस ret;

	वापस bank->direction_input(chip, offset);
पूर्ण

/* Set GPIO to Output with initial value */
अटल पूर्णांक npcmgpio_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा npcm7xx_gpio *bank = gpiochip_get_data(chip);
	पूर्णांक ret;

	dev_dbg(chip->parent, "gpio_direction_output: offset%d = %x\n", offset,
		value);

	ret = pinctrl_gpio_direction_output(offset + chip->base);
	अगर (ret)
		वापस ret;

	वापस bank->direction_output(chip, offset, value);
पूर्ण

अटल पूर्णांक npcmgpio_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा npcm7xx_gpio *bank = gpiochip_get_data(chip);
	पूर्णांक ret;

	dev_dbg(chip->parent, "gpio_request: offset%d\n", offset);
	ret = pinctrl_gpio_request(offset + chip->base);
	अगर (ret)
		वापस ret;

	वापस bank->request(chip, offset);
पूर्ण

अटल व्योम npcmgpio_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	dev_dbg(chip->parent, "gpio_free: offset%d\n", offset);
	pinctrl_gpio_मुक्त(offset + chip->base);
पूर्ण

अटल व्योम npcmgpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा irq_chip *chip;
	काष्ठा npcm7xx_gpio *bank;
	u32 sts, en, bit;

	gc = irq_desc_get_handler_data(desc);
	bank = gpiochip_get_data(gc);
	chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);
	sts = ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVST);
	en  = ioपढ़ो32(bank->base + NPCM7XX_GP_N_EVEN);
	dev_dbg(chip->parent_device, "==> got irq sts %.8x %.8x\n", sts,
		en);

	sts &= en;
	क्रम_each_set_bit(bit, (स्थिर व्योम *)&sts, NPCM7XX_GPIO_PER_BANK)
		generic_handle_irq(irq_linear_revmap(gc->irq.करोमुख्य, bit));
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक npcmgpio_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक gpio = BIT(d->hwirq);

	dev_dbg(d->chip->parent_device, "setirqtype: %u.%u = %u\n", gpio,
		d->irq, type);
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		dev_dbg(d->chip->parent_device, "edge.rising\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		dev_dbg(d->chip->parent_device, "edge.falling\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		dev_dbg(d->chip->parent_device, "edge.both\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVBE, gpio);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		dev_dbg(d->chip->parent_device, "level.low\n");
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		dev_dbg(d->chip->parent_device, "level.high\n");
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_POL, gpio);
		अवरोध;
	शेष:
		dev_dbg(d->chip->parent_device, "invalid irq type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (type & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) अणु
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		irq_set_handler_locked(d, handle_level_irq);
	पूर्ण अन्यथा अगर (type & (IRQ_TYPE_EDGE_BOTH | IRQ_TYPE_EDGE_RISING
			   | IRQ_TYPE_EDGE_FALLING)) अणु
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_EVTYP, gpio);
		irq_set_handler_locked(d, handle_edge_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम npcmgpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक gpio = d->hwirq;

	dev_dbg(d->chip->parent_device, "irq_ack: %u.%u\n", gpio, d->irq);
	ioग_लिखो32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVST);
पूर्ण

/* Disable GPIO पूर्णांकerrupt */
अटल व्योम npcmgpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक gpio = d->hwirq;

	/* Clear events */
	dev_dbg(d->chip->parent_device, "irq_mask: %u.%u\n", gpio, d->irq);
	ioग_लिखो32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVENC);
पूर्ण

/* Enable GPIO पूर्णांकerrupt */
अटल व्योम npcmgpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	अचिन्हित पूर्णांक gpio = d->hwirq;

	/* Enable events */
	dev_dbg(d->chip->parent_device, "irq_unmask: %u.%u\n", gpio, d->irq);
	ioग_लिखो32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVENS);
पूर्ण

अटल अचिन्हित पूर्णांक npcmgpio_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = d->hwirq;

	/* active-high, input, clear पूर्णांकerrupt, enable पूर्णांकerrupt */
	dev_dbg(d->chip->parent_device, "startup: %u.%u\n", gpio, d->irq);
	npcmgpio_direction_input(gc, gpio);
	npcmgpio_irq_ack(d);
	npcmgpio_irq_unmask(d);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_chip npcmgpio_irqchip = अणु
	.name = "NPCM7XX-GPIO-IRQ",
	.irq_ack = npcmgpio_irq_ack,
	.irq_unmask = npcmgpio_irq_unmask,
	.irq_mask = npcmgpio_irq_mask,
	.irq_set_type = npcmgpio_set_irq_type,
	.irq_startup = npcmgpio_irq_startup,
पूर्ण;

/* pinmux handing in the pinctrl driver*/
अटल स्थिर पूर्णांक smb0_pins[]  = अणु 115, 114 पूर्ण;
अटल स्थिर पूर्णांक smb0b_pins[] = अणु 195, 194 पूर्ण;
अटल स्थिर पूर्णांक smb0c_pins[] = अणु 202, 196 पूर्ण;
अटल स्थिर पूर्णांक smb0d_pins[] = अणु 198, 199 पूर्ण;
अटल स्थिर पूर्णांक smb0den_pins[] = अणु 197 पूर्ण;

अटल स्थिर पूर्णांक smb1_pins[]  = अणु 117, 116 पूर्ण;
अटल स्थिर पूर्णांक smb1b_pins[] = अणु 126, 127 पूर्ण;
अटल स्थिर पूर्णांक smb1c_pins[] = अणु 124, 125 पूर्ण;
अटल स्थिर पूर्णांक smb1d_pins[] = अणु 4, 5 पूर्ण;

अटल स्थिर पूर्णांक smb2_pins[]  = अणु 119, 118 पूर्ण;
अटल स्थिर पूर्णांक smb2b_pins[] = अणु 122, 123 पूर्ण;
अटल स्थिर पूर्णांक smb2c_pins[] = अणु 120, 121 पूर्ण;
अटल स्थिर पूर्णांक smb2d_pins[] = अणु 6, 7 पूर्ण;

अटल स्थिर पूर्णांक smb3_pins[]  = अणु 30, 31 पूर्ण;
अटल स्थिर पूर्णांक smb3b_pins[] = अणु 39, 40 पूर्ण;
अटल स्थिर पूर्णांक smb3c_pins[] = अणु 37, 38 पूर्ण;
अटल स्थिर पूर्णांक smb3d_pins[] = अणु 59, 60 पूर्ण;

अटल स्थिर पूर्णांक smb4_pins[]  = अणु 28, 29 पूर्ण;
अटल स्थिर पूर्णांक smb4b_pins[] = अणु 18, 19 पूर्ण;
अटल स्थिर पूर्णांक smb4c_pins[] = अणु 20, 21 पूर्ण;
अटल स्थिर पूर्णांक smb4d_pins[] = अणु 22, 23 पूर्ण;
अटल स्थिर पूर्णांक smb4den_pins[] = अणु 17 पूर्ण;

अटल स्थिर पूर्णांक smb5_pins[]  = अणु 26, 27 पूर्ण;
अटल स्थिर पूर्णांक smb5b_pins[] = अणु 13, 12 पूर्ण;
अटल स्थिर पूर्णांक smb5c_pins[] = अणु 15, 14 पूर्ण;
अटल स्थिर पूर्णांक smb5d_pins[] = अणु 94, 93 पूर्ण;
अटल स्थिर पूर्णांक ga20kbc_pins[] = अणु 94, 93 पूर्ण;

अटल स्थिर पूर्णांक smb6_pins[]  = अणु 172, 171 पूर्ण;
अटल स्थिर पूर्णांक smb7_pins[]  = अणु 174, 173 पूर्ण;
अटल स्थिर पूर्णांक smb8_pins[]  = अणु 129, 128 पूर्ण;
अटल स्थिर पूर्णांक smb9_pins[]  = अणु 131, 130 पूर्ण;
अटल स्थिर पूर्णांक smb10_pins[] = अणु 133, 132 पूर्ण;
अटल स्थिर पूर्णांक smb11_pins[] = अणु 135, 134 पूर्ण;
अटल स्थिर पूर्णांक smb12_pins[] = अणु 221, 220 पूर्ण;
अटल स्थिर पूर्णांक smb13_pins[] = अणु 223, 222 पूर्ण;
अटल स्थिर पूर्णांक smb14_pins[] = अणु 22, 23 पूर्ण;
अटल स्थिर पूर्णांक smb15_pins[] = अणु 20, 21 पूर्ण;

अटल स्थिर पूर्णांक fanin0_pins[] = अणु 64 पूर्ण;
अटल स्थिर पूर्णांक fanin1_pins[] = अणु 65 पूर्ण;
अटल स्थिर पूर्णांक fanin2_pins[] = अणु 66 पूर्ण;
अटल स्थिर पूर्णांक fanin3_pins[] = अणु 67 पूर्ण;
अटल स्थिर पूर्णांक fanin4_pins[] = अणु 68 पूर्ण;
अटल स्थिर पूर्णांक fanin5_pins[] = अणु 69 पूर्ण;
अटल स्थिर पूर्णांक fanin6_pins[] = अणु 70 पूर्ण;
अटल स्थिर पूर्णांक fanin7_pins[] = अणु 71 पूर्ण;
अटल स्थिर पूर्णांक fanin8_pins[] = अणु 72 पूर्ण;
अटल स्थिर पूर्णांक fanin9_pins[] = अणु 73 पूर्ण;
अटल स्थिर पूर्णांक fanin10_pins[] = अणु 74 पूर्ण;
अटल स्थिर पूर्णांक fanin11_pins[] = अणु 75 पूर्ण;
अटल स्थिर पूर्णांक fanin12_pins[] = अणु 76 पूर्ण;
अटल स्थिर पूर्णांक fanin13_pins[] = अणु 77 पूर्ण;
अटल स्थिर पूर्णांक fanin14_pins[] = अणु 78 पूर्ण;
अटल स्थिर पूर्णांक fanin15_pins[] = अणु 79 पूर्ण;
अटल स्थिर पूर्णांक faninx_pins[] = अणु 175, 176, 177, 203 पूर्ण;

अटल स्थिर पूर्णांक pwm0_pins[] = अणु 80 पूर्ण;
अटल स्थिर पूर्णांक pwm1_pins[] = अणु 81 पूर्ण;
अटल स्थिर पूर्णांक pwm2_pins[] = अणु 82 पूर्ण;
अटल स्थिर पूर्णांक pwm3_pins[] = अणु 83 पूर्ण;
अटल स्थिर पूर्णांक pwm4_pins[] = अणु 144 पूर्ण;
अटल स्थिर पूर्णांक pwm5_pins[] = अणु 145 पूर्ण;
अटल स्थिर पूर्णांक pwm6_pins[] = अणु 146 पूर्ण;
अटल स्थिर पूर्णांक pwm7_pins[] = अणु 147 पूर्ण;

अटल स्थिर पूर्णांक uart1_pins[] = अणु 43, 44, 45, 46, 47, 61, 62, 63 पूर्ण;
अटल स्थिर पूर्णांक uart2_pins[] = अणु 48, 49, 50, 51, 52, 53, 54, 55 पूर्ण;

/* RGMII 1 pin group */
अटल स्थिर पूर्णांक rg1_pins[] = अणु 96, 97, 98, 99, 100, 101, 102, 103, 104, 105,
	106, 107 पूर्ण;
/* RGMII 1 MD पूर्णांकerface pin group */
अटल स्थिर पूर्णांक rg1mdio_pins[] = अणु 108, 109 पूर्ण;

/* RGMII 2 pin group */
अटल स्थिर पूर्णांक rg2_pins[] = अणु 110, 111, 112, 113, 208, 209, 210, 211, 212,
	213, 214, 215 पूर्ण;
/* RGMII 2 MD पूर्णांकerface pin group */
अटल स्थिर पूर्णांक rg2mdio_pins[] = अणु 216, 217 पूर्ण;

अटल स्थिर पूर्णांक ddr_pins[] = अणु 110, 111, 112, 113, 208, 209, 210, 211, 212,
	213, 214, 215, 216, 217 पूर्ण;
/* Serial I/O Expander 1 */
अटल स्थिर पूर्णांक iox1_pins[] = अणु 0, 1, 2, 3 पूर्ण;
/* Serial I/O Expander 2 */
अटल स्थिर पूर्णांक iox2_pins[] = अणु 4, 5, 6, 7 पूर्ण;
/* Host Serial I/O Expander 2 */
अटल स्थिर पूर्णांक ioxh_pins[] = अणु 10, 11, 24, 25 पूर्ण;

अटल स्थिर पूर्णांक mmc_pins[] = अणु 152, 154, 156, 157, 158, 159 पूर्ण;
अटल स्थिर पूर्णांक mmcwp_pins[] = अणु 153 पूर्ण;
अटल स्थिर पूर्णांक mmccd_pins[] = अणु 155 पूर्ण;
अटल स्थिर पूर्णांक mmcrst_pins[] = अणु 155 पूर्ण;
अटल स्थिर पूर्णांक mmc8_pins[] = अणु 148, 149, 150, 151 पूर्ण;

/* RMII 1 pin groups */
अटल स्थिर पूर्णांक r1_pins[] = अणु 178, 179, 180, 181, 182, 193, 201 पूर्ण;
अटल स्थिर पूर्णांक r1err_pins[] = अणु 56 पूर्ण;
अटल स्थिर पूर्णांक r1md_pins[] = अणु 57, 58 पूर्ण;

/* RMII 2 pin groups */
अटल स्थिर पूर्णांक r2_pins[] = अणु 84, 85, 86, 87, 88, 89, 200 पूर्ण;
अटल स्थिर पूर्णांक r2err_pins[] = अणु 90 पूर्ण;
अटल स्थिर पूर्णांक r2md_pins[] = अणु 91, 92 पूर्ण;

अटल स्थिर पूर्णांक sd1_pins[] = अणु 136, 137, 138, 139, 140, 141, 142, 143 पूर्ण;
अटल स्थिर पूर्णांक sd1pwr_pins[] = अणु 143 पूर्ण;

अटल स्थिर पूर्णांक wकरोg1_pins[] = अणु 218 पूर्ण;
अटल स्थिर पूर्णांक wकरोg2_pins[] = अणु 219 पूर्ण;

/* BMC serial port 0 */
अटल स्थिर पूर्णांक bmcuart0a_pins[] = अणु 41, 42 पूर्ण;
अटल स्थिर पूर्णांक bmcuart0b_pins[] = अणु 48, 49 पूर्ण;

अटल स्थिर पूर्णांक bmcuart1_pins[] = अणु 43, 44, 62, 63 पूर्ण;

/* System Control Interrupt and Power Management Event pin group */
अटल स्थिर पूर्णांक scipme_pins[] = अणु 169 पूर्ण;
/* System Management Interrupt pin group */
अटल स्थिर पूर्णांक sci_pins[] = अणु 170 पूर्ण;
/* Serial Interrupt Line pin group */
अटल स्थिर पूर्णांक serirq_pins[] = अणु 162 पूर्ण;

अटल स्थिर पूर्णांक clkout_pins[] = अणु 160 पूर्ण;
अटल स्थिर पूर्णांक clkreq_pins[] = अणु 231 पूर्ण;

अटल स्थिर पूर्णांक jtag2_pins[] = अणु 43, 44, 45, 46, 47 पूर्ण;
/* Graphics SPI Clock pin group */
अटल स्थिर पूर्णांक gspi_pins[] = अणु 12, 13, 14, 15 पूर्ण;

अटल स्थिर पूर्णांक spix_pins[] = अणु 224, 225, 226, 227, 229, 230 पूर्ण;
अटल स्थिर पूर्णांक spixcs1_pins[] = अणु 228 पूर्ण;

अटल स्थिर पूर्णांक pspi1_pins[] = अणु 175, 176, 177 पूर्ण;
अटल स्थिर पूर्णांक pspi2_pins[] = अणु 17, 18, 19 पूर्ण;

अटल स्थिर पूर्णांक spi0cs1_pins[] = अणु 32 पूर्ण;

अटल स्थिर पूर्णांक spi3_pins[] = अणु 183, 184, 185, 186 पूर्ण;
अटल स्थिर पूर्णांक spi3cs1_pins[] = अणु 187 पूर्ण;
अटल स्थिर पूर्णांक spi3quad_pins[] = अणु 188, 189 पूर्ण;
अटल स्थिर पूर्णांक spi3cs2_pins[] = अणु 188 पूर्ण;
अटल स्थिर पूर्णांक spi3cs3_pins[] = अणु 189 पूर्ण;

अटल स्थिर पूर्णांक ddc_pins[] = अणु 204, 205, 206, 207 पूर्ण;

अटल स्थिर पूर्णांक lpc_pins[] = अणु 95, 161, 163, 164, 165, 166, 167 पूर्ण;
अटल स्थिर पूर्णांक lpcclk_pins[] = अणु 168 पूर्ण;
अटल स्थिर पूर्णांक espi_pins[] = अणु 95, 161, 163, 164, 165, 166, 167, 168 पूर्ण;

अटल स्थिर पूर्णांक lkgpo0_pins[] = अणु 16 पूर्ण;
अटल स्थिर पूर्णांक lkgpo1_pins[] = अणु 8 पूर्ण;
अटल स्थिर पूर्णांक lkgpo2_pins[] = अणु 9 पूर्ण;

अटल स्थिर पूर्णांक nprd_smi_pins[] = अणु 190 पूर्ण;

/*
 * pin:	     name, number
 * group:    name, npins,   pins
 * function: name, ngroups, groups
 */
काष्ठा npcm7xx_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	पूर्णांक npins;
पूर्ण;

#घोषणा NPCM7XX_GRPS \
	NPCM7XX_GRP(smb0), \
	NPCM7XX_GRP(smb0b), \
	NPCM7XX_GRP(smb0c), \
	NPCM7XX_GRP(smb0d), \
	NPCM7XX_GRP(smb0den), \
	NPCM7XX_GRP(smb1), \
	NPCM7XX_GRP(smb1b), \
	NPCM7XX_GRP(smb1c), \
	NPCM7XX_GRP(smb1d), \
	NPCM7XX_GRP(smb2), \
	NPCM7XX_GRP(smb2b), \
	NPCM7XX_GRP(smb2c), \
	NPCM7XX_GRP(smb2d), \
	NPCM7XX_GRP(smb3), \
	NPCM7XX_GRP(smb3b), \
	NPCM7XX_GRP(smb3c), \
	NPCM7XX_GRP(smb3d), \
	NPCM7XX_GRP(smb4), \
	NPCM7XX_GRP(smb4b), \
	NPCM7XX_GRP(smb4c), \
	NPCM7XX_GRP(smb4d), \
	NPCM7XX_GRP(smb4den), \
	NPCM7XX_GRP(smb5), \
	NPCM7XX_GRP(smb5b), \
	NPCM7XX_GRP(smb5c), \
	NPCM7XX_GRP(smb5d), \
	NPCM7XX_GRP(ga20kbc), \
	NPCM7XX_GRP(smb6), \
	NPCM7XX_GRP(smb7), \
	NPCM7XX_GRP(smb8), \
	NPCM7XX_GRP(smb9), \
	NPCM7XX_GRP(smb10), \
	NPCM7XX_GRP(smb11), \
	NPCM7XX_GRP(smb12), \
	NPCM7XX_GRP(smb13), \
	NPCM7XX_GRP(smb14), \
	NPCM7XX_GRP(smb15), \
	NPCM7XX_GRP(fanin0), \
	NPCM7XX_GRP(fanin1), \
	NPCM7XX_GRP(fanin2), \
	NPCM7XX_GRP(fanin3), \
	NPCM7XX_GRP(fanin4), \
	NPCM7XX_GRP(fanin5), \
	NPCM7XX_GRP(fanin6), \
	NPCM7XX_GRP(fanin7), \
	NPCM7XX_GRP(fanin8), \
	NPCM7XX_GRP(fanin9), \
	NPCM7XX_GRP(fanin10), \
	NPCM7XX_GRP(fanin11), \
	NPCM7XX_GRP(fanin12), \
	NPCM7XX_GRP(fanin13), \
	NPCM7XX_GRP(fanin14), \
	NPCM7XX_GRP(fanin15), \
	NPCM7XX_GRP(faninx), \
	NPCM7XX_GRP(pwm0), \
	NPCM7XX_GRP(pwm1), \
	NPCM7XX_GRP(pwm2), \
	NPCM7XX_GRP(pwm3), \
	NPCM7XX_GRP(pwm4), \
	NPCM7XX_GRP(pwm5), \
	NPCM7XX_GRP(pwm6), \
	NPCM7XX_GRP(pwm7), \
	NPCM7XX_GRP(rg1), \
	NPCM7XX_GRP(rg1mdio), \
	NPCM7XX_GRP(rg2), \
	NPCM7XX_GRP(rg2mdio), \
	NPCM7XX_GRP(ddr), \
	NPCM7XX_GRP(uart1), \
	NPCM7XX_GRP(uart2), \
	NPCM7XX_GRP(bmcuart0a), \
	NPCM7XX_GRP(bmcuart0b), \
	NPCM7XX_GRP(bmcuart1), \
	NPCM7XX_GRP(iox1), \
	NPCM7XX_GRP(iox2), \
	NPCM7XX_GRP(ioxh), \
	NPCM7XX_GRP(gspi), \
	NPCM7XX_GRP(mmc), \
	NPCM7XX_GRP(mmcwp), \
	NPCM7XX_GRP(mmccd), \
	NPCM7XX_GRP(mmcrst), \
	NPCM7XX_GRP(mmc8), \
	NPCM7XX_GRP(r1), \
	NPCM7XX_GRP(r1err), \
	NPCM7XX_GRP(r1md), \
	NPCM7XX_GRP(r2), \
	NPCM7XX_GRP(r2err), \
	NPCM7XX_GRP(r2md), \
	NPCM7XX_GRP(sd1), \
	NPCM7XX_GRP(sd1pwr), \
	NPCM7XX_GRP(wकरोg1), \
	NPCM7XX_GRP(wकरोg2), \
	NPCM7XX_GRP(scipme), \
	NPCM7XX_GRP(sci), \
	NPCM7XX_GRP(serirq), \
	NPCM7XX_GRP(jtag2), \
	NPCM7XX_GRP(spix), \
	NPCM7XX_GRP(spixcs1), \
	NPCM7XX_GRP(pspi1), \
	NPCM7XX_GRP(pspi2), \
	NPCM7XX_GRP(ddc), \
	NPCM7XX_GRP(clkreq), \
	NPCM7XX_GRP(clkout), \
	NPCM7XX_GRP(spi3), \
	NPCM7XX_GRP(spi3cs1), \
	NPCM7XX_GRP(spi3quad), \
	NPCM7XX_GRP(spi3cs2), \
	NPCM7XX_GRP(spi3cs3), \
	NPCM7XX_GRP(spi0cs1), \
	NPCM7XX_GRP(lpc), \
	NPCM7XX_GRP(lpcclk), \
	NPCM7XX_GRP(espi), \
	NPCM7XX_GRP(lkgpo0), \
	NPCM7XX_GRP(lkgpo1), \
	NPCM7XX_GRP(lkgpo2), \
	NPCM7XX_GRP(nprd_smi), \
	\

क्रमागत अणु
#घोषणा NPCM7XX_GRP(x) fn_ ## x
	NPCM7XX_GRPS
	/* add placeholder क्रम none/gpio */
	NPCM7XX_GRP(none),
	NPCM7XX_GRP(gpio),
#अघोषित NPCM7XX_GRP
पूर्ण;

अटल काष्ठा npcm7xx_group npcm7xx_groups[] = अणु
#घोषणा NPCM7XX_GRP(x) अणु .name = #x, .pins = x ## _pins, \
			.npins = ARRAY_SIZE(x ## _pins) पूर्ण
	NPCM7XX_GRPS
#अघोषित NPCM7XX_GRP
पूर्ण;

#घोषणा NPCM7XX_SFUNC(a) NPCM7XX_FUNC(a, #a)
#घोषणा NPCM7XX_FUNC(a, b...) अटल स्थिर अक्षर *a ## _grp[] = अणु b पूर्ण
#घोषणा NPCM7XX_MKFUNC(nm) अणु .name = #nm, .ngroups = ARRAY_SIZE(nm ## _grp), \
			.groups = nm ## _grp पूर्ण
काष्ठा npcm7xx_func अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक ngroups;
	स्थिर अक्षर *स्थिर *groups;
पूर्ण;

NPCM7XX_SFUNC(smb0);
NPCM7XX_SFUNC(smb0b);
NPCM7XX_SFUNC(smb0c);
NPCM7XX_SFUNC(smb0d);
NPCM7XX_SFUNC(smb0den);
NPCM7XX_SFUNC(smb1);
NPCM7XX_SFUNC(smb1b);
NPCM7XX_SFUNC(smb1c);
NPCM7XX_SFUNC(smb1d);
NPCM7XX_SFUNC(smb2);
NPCM7XX_SFUNC(smb2b);
NPCM7XX_SFUNC(smb2c);
NPCM7XX_SFUNC(smb2d);
NPCM7XX_SFUNC(smb3);
NPCM7XX_SFUNC(smb3b);
NPCM7XX_SFUNC(smb3c);
NPCM7XX_SFUNC(smb3d);
NPCM7XX_SFUNC(smb4);
NPCM7XX_SFUNC(smb4b);
NPCM7XX_SFUNC(smb4c);
NPCM7XX_SFUNC(smb4d);
NPCM7XX_SFUNC(smb4den);
NPCM7XX_SFUNC(smb5);
NPCM7XX_SFUNC(smb5b);
NPCM7XX_SFUNC(smb5c);
NPCM7XX_SFUNC(smb5d);
NPCM7XX_SFUNC(ga20kbc);
NPCM7XX_SFUNC(smb6);
NPCM7XX_SFUNC(smb7);
NPCM7XX_SFUNC(smb8);
NPCM7XX_SFUNC(smb9);
NPCM7XX_SFUNC(smb10);
NPCM7XX_SFUNC(smb11);
NPCM7XX_SFUNC(smb12);
NPCM7XX_SFUNC(smb13);
NPCM7XX_SFUNC(smb14);
NPCM7XX_SFUNC(smb15);
NPCM7XX_SFUNC(fanin0);
NPCM7XX_SFUNC(fanin1);
NPCM7XX_SFUNC(fanin2);
NPCM7XX_SFUNC(fanin3);
NPCM7XX_SFUNC(fanin4);
NPCM7XX_SFUNC(fanin5);
NPCM7XX_SFUNC(fanin6);
NPCM7XX_SFUNC(fanin7);
NPCM7XX_SFUNC(fanin8);
NPCM7XX_SFUNC(fanin9);
NPCM7XX_SFUNC(fanin10);
NPCM7XX_SFUNC(fanin11);
NPCM7XX_SFUNC(fanin12);
NPCM7XX_SFUNC(fanin13);
NPCM7XX_SFUNC(fanin14);
NPCM7XX_SFUNC(fanin15);
NPCM7XX_SFUNC(faninx);
NPCM7XX_SFUNC(pwm0);
NPCM7XX_SFUNC(pwm1);
NPCM7XX_SFUNC(pwm2);
NPCM7XX_SFUNC(pwm3);
NPCM7XX_SFUNC(pwm4);
NPCM7XX_SFUNC(pwm5);
NPCM7XX_SFUNC(pwm6);
NPCM7XX_SFUNC(pwm7);
NPCM7XX_SFUNC(rg1);
NPCM7XX_SFUNC(rg1mdio);
NPCM7XX_SFUNC(rg2);
NPCM7XX_SFUNC(rg2mdio);
NPCM7XX_SFUNC(ddr);
NPCM7XX_SFUNC(uart1);
NPCM7XX_SFUNC(uart2);
NPCM7XX_SFUNC(bmcuart0a);
NPCM7XX_SFUNC(bmcuart0b);
NPCM7XX_SFUNC(bmcuart1);
NPCM7XX_SFUNC(iox1);
NPCM7XX_SFUNC(iox2);
NPCM7XX_SFUNC(ioxh);
NPCM7XX_SFUNC(gspi);
NPCM7XX_SFUNC(mmc);
NPCM7XX_SFUNC(mmcwp);
NPCM7XX_SFUNC(mmccd);
NPCM7XX_SFUNC(mmcrst);
NPCM7XX_SFUNC(mmc8);
NPCM7XX_SFUNC(r1);
NPCM7XX_SFUNC(r1err);
NPCM7XX_SFUNC(r1md);
NPCM7XX_SFUNC(r2);
NPCM7XX_SFUNC(r2err);
NPCM7XX_SFUNC(r2md);
NPCM7XX_SFUNC(sd1);
NPCM7XX_SFUNC(sd1pwr);
NPCM7XX_SFUNC(wकरोg1);
NPCM7XX_SFUNC(wकरोg2);
NPCM7XX_SFUNC(scipme);
NPCM7XX_SFUNC(sci);
NPCM7XX_SFUNC(serirq);
NPCM7XX_SFUNC(jtag2);
NPCM7XX_SFUNC(spix);
NPCM7XX_SFUNC(spixcs1);
NPCM7XX_SFUNC(pspi1);
NPCM7XX_SFUNC(pspi2);
NPCM7XX_SFUNC(ddc);
NPCM7XX_SFUNC(clkreq);
NPCM7XX_SFUNC(clkout);
NPCM7XX_SFUNC(spi3);
NPCM7XX_SFUNC(spi3cs1);
NPCM7XX_SFUNC(spi3quad);
NPCM7XX_SFUNC(spi3cs2);
NPCM7XX_SFUNC(spi3cs3);
NPCM7XX_SFUNC(spi0cs1);
NPCM7XX_SFUNC(lpc);
NPCM7XX_SFUNC(lpcclk);
NPCM7XX_SFUNC(espi);
NPCM7XX_SFUNC(lkgpo0);
NPCM7XX_SFUNC(lkgpo1);
NPCM7XX_SFUNC(lkgpo2);
NPCM7XX_SFUNC(nprd_smi);

/* Function names */
अटल काष्ठा npcm7xx_func npcm7xx_funcs[] = अणु
	NPCM7XX_MKFUNC(smb0),
	NPCM7XX_MKFUNC(smb0b),
	NPCM7XX_MKFUNC(smb0c),
	NPCM7XX_MKFUNC(smb0d),
	NPCM7XX_MKFUNC(smb0den),
	NPCM7XX_MKFUNC(smb1),
	NPCM7XX_MKFUNC(smb1b),
	NPCM7XX_MKFUNC(smb1c),
	NPCM7XX_MKFUNC(smb1d),
	NPCM7XX_MKFUNC(smb2),
	NPCM7XX_MKFUNC(smb2b),
	NPCM7XX_MKFUNC(smb2c),
	NPCM7XX_MKFUNC(smb2d),
	NPCM7XX_MKFUNC(smb3),
	NPCM7XX_MKFUNC(smb3b),
	NPCM7XX_MKFUNC(smb3c),
	NPCM7XX_MKFUNC(smb3d),
	NPCM7XX_MKFUNC(smb4),
	NPCM7XX_MKFUNC(smb4b),
	NPCM7XX_MKFUNC(smb4c),
	NPCM7XX_MKFUNC(smb4d),
	NPCM7XX_MKFUNC(smb4den),
	NPCM7XX_MKFUNC(smb5),
	NPCM7XX_MKFUNC(smb5b),
	NPCM7XX_MKFUNC(smb5c),
	NPCM7XX_MKFUNC(smb5d),
	NPCM7XX_MKFUNC(ga20kbc),
	NPCM7XX_MKFUNC(smb6),
	NPCM7XX_MKFUNC(smb7),
	NPCM7XX_MKFUNC(smb8),
	NPCM7XX_MKFUNC(smb9),
	NPCM7XX_MKFUNC(smb10),
	NPCM7XX_MKFUNC(smb11),
	NPCM7XX_MKFUNC(smb12),
	NPCM7XX_MKFUNC(smb13),
	NPCM7XX_MKFUNC(smb14),
	NPCM7XX_MKFUNC(smb15),
	NPCM7XX_MKFUNC(fanin0),
	NPCM7XX_MKFUNC(fanin1),
	NPCM7XX_MKFUNC(fanin2),
	NPCM7XX_MKFUNC(fanin3),
	NPCM7XX_MKFUNC(fanin4),
	NPCM7XX_MKFUNC(fanin5),
	NPCM7XX_MKFUNC(fanin6),
	NPCM7XX_MKFUNC(fanin7),
	NPCM7XX_MKFUNC(fanin8),
	NPCM7XX_MKFUNC(fanin9),
	NPCM7XX_MKFUNC(fanin10),
	NPCM7XX_MKFUNC(fanin11),
	NPCM7XX_MKFUNC(fanin12),
	NPCM7XX_MKFUNC(fanin13),
	NPCM7XX_MKFUNC(fanin14),
	NPCM7XX_MKFUNC(fanin15),
	NPCM7XX_MKFUNC(faninx),
	NPCM7XX_MKFUNC(pwm0),
	NPCM7XX_MKFUNC(pwm1),
	NPCM7XX_MKFUNC(pwm2),
	NPCM7XX_MKFUNC(pwm3),
	NPCM7XX_MKFUNC(pwm4),
	NPCM7XX_MKFUNC(pwm5),
	NPCM7XX_MKFUNC(pwm6),
	NPCM7XX_MKFUNC(pwm7),
	NPCM7XX_MKFUNC(rg1),
	NPCM7XX_MKFUNC(rg1mdio),
	NPCM7XX_MKFUNC(rg2),
	NPCM7XX_MKFUNC(rg2mdio),
	NPCM7XX_MKFUNC(ddr),
	NPCM7XX_MKFUNC(uart1),
	NPCM7XX_MKFUNC(uart2),
	NPCM7XX_MKFUNC(bmcuart0a),
	NPCM7XX_MKFUNC(bmcuart0b),
	NPCM7XX_MKFUNC(bmcuart1),
	NPCM7XX_MKFUNC(iox1),
	NPCM7XX_MKFUNC(iox2),
	NPCM7XX_MKFUNC(ioxh),
	NPCM7XX_MKFUNC(gspi),
	NPCM7XX_MKFUNC(mmc),
	NPCM7XX_MKFUNC(mmcwp),
	NPCM7XX_MKFUNC(mmccd),
	NPCM7XX_MKFUNC(mmcrst),
	NPCM7XX_MKFUNC(mmc8),
	NPCM7XX_MKFUNC(r1),
	NPCM7XX_MKFUNC(r1err),
	NPCM7XX_MKFUNC(r1md),
	NPCM7XX_MKFUNC(r2),
	NPCM7XX_MKFUNC(r2err),
	NPCM7XX_MKFUNC(r2md),
	NPCM7XX_MKFUNC(sd1),
	NPCM7XX_MKFUNC(sd1pwr),
	NPCM7XX_MKFUNC(wकरोg1),
	NPCM7XX_MKFUNC(wकरोg2),
	NPCM7XX_MKFUNC(scipme),
	NPCM7XX_MKFUNC(sci),
	NPCM7XX_MKFUNC(serirq),
	NPCM7XX_MKFUNC(jtag2),
	NPCM7XX_MKFUNC(spix),
	NPCM7XX_MKFUNC(spixcs1),
	NPCM7XX_MKFUNC(pspi1),
	NPCM7XX_MKFUNC(pspi2),
	NPCM7XX_MKFUNC(ddc),
	NPCM7XX_MKFUNC(clkreq),
	NPCM7XX_MKFUNC(clkout),
	NPCM7XX_MKFUNC(spi3),
	NPCM7XX_MKFUNC(spi3cs1),
	NPCM7XX_MKFUNC(spi3quad),
	NPCM7XX_MKFUNC(spi3cs2),
	NPCM7XX_MKFUNC(spi3cs3),
	NPCM7XX_MKFUNC(spi0cs1),
	NPCM7XX_MKFUNC(lpc),
	NPCM7XX_MKFUNC(lpcclk),
	NPCM7XX_MKFUNC(espi),
	NPCM7XX_MKFUNC(lkgpo0),
	NPCM7XX_MKFUNC(lkgpo1),
	NPCM7XX_MKFUNC(lkgpo2),
	NPCM7XX_MKFUNC(nprd_smi),
पूर्ण;

#घोषणा NPCM7XX_PINCFG(a, b, c, d, e, f, g, h, i, j, k) \
	[a] अणु .fn0 = fn_ ## b, .reg0 = NPCM7XX_GCR_ ## c, .bit0 = d, \
			.fn1 = fn_ ## e, .reg1 = NPCM7XX_GCR_ ## f, .bit1 = g, \
			.fn2 = fn_ ## h, .reg2 = NPCM7XX_GCR_ ## i, .bit2 = j, \
			.flag = k पूर्ण

/* Drive strength controlled by NPCM7XX_GP_N_ODSC */
#घोषणा DRIVE_STRENGTH_LO_SHIFT		8
#घोषणा DRIVE_STRENGTH_HI_SHIFT		12
#घोषणा DRIVE_STRENGTH_MASK		0x0000FF00

#घोषणा DS(lo, hi)	(((lo) << DRIVE_STRENGTH_LO_SHIFT) | \
			 ((hi) << DRIVE_STRENGTH_HI_SHIFT))
#घोषणा DSLO(x)		(((x) >> DRIVE_STRENGTH_LO_SHIFT) & 0xF)
#घोषणा DSHI(x)		(((x) >> DRIVE_STRENGTH_HI_SHIFT) & 0xF)

#घोषणा GPI		0x1 /* Not GPO */
#घोषणा GPO		0x2 /* Not GPI */
#घोषणा SLEW		0x4 /* Has Slew Control, NPCM7XX_GP_N_OSRC */
#घोषणा SLEWLPC		0x8 /* Has Slew Control, SRCNT.3 */

काष्ठा npcm7xx_pincfg अणु
	पूर्णांक flag;
	पूर्णांक fn0, reg0, bit0;
	पूर्णांक fn1, reg1, bit1;
	पूर्णांक fn2, reg2, bit2;
पूर्ण;

अटल स्थिर काष्ठा npcm7xx_pincfg pincfg[] = अणु
	/*		PIN	  FUNCTION 1		   FUNCTION 2		  FUNCTION 3	    FLAGS */
	NPCM7XX_PINCFG(0,	 iox1, MFSEL1, 30,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(1,	 iox1, MFSEL1, 30,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(2,	 iox1, MFSEL1, 30,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(3,	 iox1, MFSEL1, 30,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(4,	 iox2, MFSEL3, 14,	 smb1d, I2CSEGSEL, 7,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(5,	 iox2, MFSEL3, 14,	 smb1d, I2CSEGSEL, 7,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(6,	 iox2, MFSEL3, 14,	 smb2d, I2CSEGSEL, 10,  none, NONE, 0,       SLEW),
	NPCM7XX_PINCFG(7,	 iox2, MFSEL3, 14,	 smb2d, I2CSEGSEL, 10,  none, NONE, 0,       SLEW),
	NPCM7XX_PINCFG(8,      lkgpo1, FLOCKR1, 4,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(9,      lkgpo2, FLOCKR1, 8,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(10,	 ioxh, MFSEL3, 18,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(11,	 ioxh, MFSEL3, 18,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(12,	 gspi, MFSEL1, 24,	 smb5b, I2CSEGSEL, 19,  none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(13,	 gspi, MFSEL1, 24,	 smb5b, I2CSEGSEL, 19,  none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(14,	 gspi, MFSEL1, 24,	 smb5c, I2CSEGSEL, 20,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(15,	 gspi, MFSEL1, 24,	 smb5c, I2CSEGSEL, 20,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(16,     lkgpo0, FLOCKR1, 0,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(17,      pspi2, MFSEL3, 13,     smb4den, I2CSEGSEL, 23,  none, NONE, 0,       DS(8, 12)),
	NPCM7XX_PINCFG(18,      pspi2, MFSEL3, 13,	 smb4b, I2CSEGSEL, 14,  none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(19,      pspi2, MFSEL3, 13,	 smb4b, I2CSEGSEL, 14,  none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(20,	smb4c, I2CSEGSEL, 15,    smb15, MFSEL3, 8,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(21,	smb4c, I2CSEGSEL, 15,    smb15, MFSEL3, 8,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(22,      smb4d, I2CSEGSEL, 16,	 smb14, MFSEL3, 7,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(23,      smb4d, I2CSEGSEL, 16,	 smb14, MFSEL3, 7,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(24,	 ioxh, MFSEL3, 18,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(25,	 ioxh, MFSEL3, 18,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(26,	 smb5, MFSEL1, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(27,	 smb5, MFSEL1, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(28,	 smb4, MFSEL1, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(29,	 smb4, MFSEL1, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(30,	 smb3, MFSEL1, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(31,	 smb3, MFSEL1, 0,	  none, NONE, 0,	none, NONE, 0,	     0),

	NPCM7XX_PINCFG(32,    spi0cs1, MFSEL1, 3,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(33,   none, NONE, 0,     none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(34,   none, NONE, 0,     none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(37,	smb3c, I2CSEGSEL, 12,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(38,	smb3c, I2CSEGSEL, 12,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(39,	smb3b, I2CSEGSEL, 11,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(40,	smb3b, I2CSEGSEL, 11,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(41,  bmcuart0a, MFSEL1, 9,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(42,  bmcuart0a, MFSEL1, 9,         none, NONE, 0,	none, NONE, 0,	     DS(2, 4) | GPO),
	NPCM7XX_PINCFG(43,      uart1, MFSEL1, 10,	 jtag2, MFSEL4, 0,  bmcuart1, MFSEL3, 24,    0),
	NPCM7XX_PINCFG(44,      uart1, MFSEL1, 10,	 jtag2, MFSEL4, 0,  bmcuart1, MFSEL3, 24,    0),
	NPCM7XX_PINCFG(45,      uart1, MFSEL1, 10,	 jtag2, MFSEL4, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(46,      uart1, MFSEL1, 10,	 jtag2, MFSEL4, 0,	none, NONE, 0,	     DS(2, 8)),
	NPCM7XX_PINCFG(47,      uart1, MFSEL1, 10,	 jtag2, MFSEL4, 0,	none, NONE, 0,	     DS(2, 8)),
	NPCM7XX_PINCFG(48,	uart2, MFSEL1, 11,   bmcuart0b, MFSEL4, 1,      none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(49,	uart2, MFSEL1, 11,   bmcuart0b, MFSEL4, 1,      none, NONE, 0,	     0),
	NPCM7XX_PINCFG(50,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(51,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(52,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(53,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     GPO),
	NPCM7XX_PINCFG(54,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(55,	uart2, MFSEL1, 11,	  none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(56,	r1err, MFSEL1, 12,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(57,       r1md, MFSEL1, 13,        none, NONE, 0,        none, NONE, 0,       DS(2, 4)),
	NPCM7XX_PINCFG(58,       r1md, MFSEL1, 13,        none, NONE, 0,	none, NONE, 0,	     DS(2, 4)),
	NPCM7XX_PINCFG(59,	smb3d, I2CSEGSEL, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(60,	smb3d, I2CSEGSEL, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(61,      uart1, MFSEL1, 10,	  none, NONE, 0,	none, NONE, 0,     GPO),
	NPCM7XX_PINCFG(62,      uart1, MFSEL1, 10,    bmcuart1, MFSEL3, 24,	none, NONE, 0,     GPO),
	NPCM7XX_PINCFG(63,      uart1, MFSEL1, 10,    bmcuart1, MFSEL3, 24,	none, NONE, 0,     GPO),

	NPCM7XX_PINCFG(64,    fanin0, MFSEL2, 0,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(65,    fanin1, MFSEL2, 1,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(66,    fanin2, MFSEL2, 2,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(67,    fanin3, MFSEL2, 3,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(68,    fanin4, MFSEL2, 4,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(69,    fanin5, MFSEL2, 5,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(70,    fanin6, MFSEL2, 6,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(71,    fanin7, MFSEL2, 7,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(72,    fanin8, MFSEL2, 8,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(73,    fanin9, MFSEL2, 9,          none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(74,    fanin10, MFSEL2, 10,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(75,    fanin11, MFSEL2, 11,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(76,    fanin12, MFSEL2, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(77,    fanin13, MFSEL2, 13,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(78,    fanin14, MFSEL2, 14,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(79,    fanin15, MFSEL2, 15,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(80,	 pwm0, MFSEL2, 16,        none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(81,	 pwm1, MFSEL2, 17,        none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(82,	 pwm2, MFSEL2, 18,        none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(83,	 pwm3, MFSEL2, 19,        none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(84,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(85,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(86,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(87,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(88,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(89,         r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(90,      r2err, MFSEL1, 15,        none, NONE, 0,        none, NONE, 0,       0),
	NPCM7XX_PINCFG(91,       r2md, MFSEL1, 16,	  none, NONE, 0,        none, NONE, 0,	     DS(2, 4)),
	NPCM7XX_PINCFG(92,       r2md, MFSEL1, 16,	  none, NONE, 0,        none, NONE, 0,	     DS(2, 4)),
	NPCM7XX_PINCFG(93,    ga20kbc, MFSEL1, 17,	 smb5d, I2CSEGSEL, 21,  none, NONE, 0,	     0),
	NPCM7XX_PINCFG(94,    ga20kbc, MFSEL1, 17,	 smb5d, I2CSEGSEL, 21,  none, NONE, 0,	     0),
	NPCM7XX_PINCFG(95,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    0),

	NPCM7XX_PINCFG(96,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(97,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(98,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(99,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(100,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(101,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(102,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(103,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(104,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(105,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(106,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(107,	  rg1, MFSEL4, 22,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(108,   rg1mdio, MFSEL4, 21,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(109,   rg1mdio, MFSEL4, 21,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(110,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(111,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(112,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(113,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(114,	 smb0, MFSEL1, 6,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(115,	 smb0, MFSEL1, 6,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(116,	 smb1, MFSEL1, 7,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(117,	 smb1, MFSEL1, 7,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(118,	 smb2, MFSEL1, 8,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(119,	 smb2, MFSEL1, 8,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(120,	smb2c, I2CSEGSEL, 9,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(121,	smb2c, I2CSEGSEL, 9,      none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(122,	smb2b, I2CSEGSEL, 8,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(123,	smb2b, I2CSEGSEL, 8,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(124,	smb1c, I2CSEGSEL, 6,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(125,	smb1c, I2CSEGSEL, 6,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(126,	smb1b, I2CSEGSEL, 5,	  none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(127,	smb1b, I2CSEGSEL, 5,	  none, NONE, 0,	none, NONE, 0,	     SLEW),

	NPCM7XX_PINCFG(128,	 smb8, MFSEL4, 11,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(129,	 smb8, MFSEL4, 11,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(130,	 smb9, MFSEL4, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(131,	 smb9, MFSEL4, 12,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(132,	smb10, MFSEL4, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(133,	smb10, MFSEL4, 13,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(134,	smb11, MFSEL4, 14,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(135,	smb11, MFSEL4, 14,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(136,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(137,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(138,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(139,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(140,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(141,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(142,	  sd1, MFSEL3, 12,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(143,       sd1, MFSEL3, 12,      sd1pwr, MFSEL4, 5,      none, NONE, 0,       0),
	NPCM7XX_PINCFG(144,	 pwm4, MFSEL2, 20,	  none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(145,	 pwm5, MFSEL2, 21,	  none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(146,	 pwm6, MFSEL2, 22,	  none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(147,	 pwm7, MFSEL2, 23,	  none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(148,	 mmc8, MFSEL3, 11,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(149,	 mmc8, MFSEL3, 11,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(150,	 mmc8, MFSEL3, 11,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(151,	 mmc8, MFSEL3, 11,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(152,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(153,     mmcwp, FLOCKR1, 24,       none, NONE, 0,	none, NONE, 0,	     0),  /* Z1/A1 */
	NPCM7XX_PINCFG(154,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(155,     mmccd, MFSEL3, 25,      mmcrst, MFSEL4, 6,      none, NONE, 0,       0),  /* Z1/A1 */
	NPCM7XX_PINCFG(156,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(157,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(158,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(159,	  mmc, MFSEL3, 10,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),

	NPCM7XX_PINCFG(160,    clkout, MFSEL1, 21,        none, NONE, 0,        none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(161,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    DS(8, 12)),
	NPCM7XX_PINCFG(162,    serirq, NONE, 0,           gpio, MFSEL1, 31,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(163,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    0),
	NPCM7XX_PINCFG(164,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    SLEWLPC),
	NPCM7XX_PINCFG(165,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    SLEWLPC),
	NPCM7XX_PINCFG(166,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    SLEWLPC),
	NPCM7XX_PINCFG(167,	  lpc, NONE, 0,		  espi, MFSEL4, 8,      gpio, MFSEL1, 26,    SLEWLPC),
	NPCM7XX_PINCFG(168,    lpcclk, NONE, 0,           espi, MFSEL4, 8,      gpio, MFSEL3, 16,    0),
	NPCM7XX_PINCFG(169,    scipme, MFSEL3, 0,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(170,	  sci, MFSEL1, 22,        none, NONE, 0,        none, NONE, 0,	     0),
	NPCM7XX_PINCFG(171,	 smb6, MFSEL3, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(172,	 smb6, MFSEL3, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(173,	 smb7, MFSEL3, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(174,	 smb7, MFSEL3, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(175,	pspi1, MFSEL3, 4,       faninx, MFSEL3, 3,      none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(176,     pspi1, MFSEL3, 4,       faninx, MFSEL3, 3,      none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(177,     pspi1, MFSEL3, 4,       faninx, MFSEL3, 3,      none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(178,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(179,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(180,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(181,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(182,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(183,     spi3, MFSEL4, 16,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(184,     spi3, MFSEL4, 16,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW | GPO),
	NPCM7XX_PINCFG(185,     spi3, MFSEL4, 16,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW | GPO),
	NPCM7XX_PINCFG(186,     spi3, MFSEL4, 16,	  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(187,   spi3cs1, MFSEL4, 17,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(188,  spi3quad, MFSEL4, 20,     spi3cs2, MFSEL4, 18,     none, NONE, 0,    DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(189,  spi3quad, MFSEL4, 20,     spi3cs3, MFSEL4, 19,     none, NONE, 0,    DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(190,      gpio, FLOCKR1, 20,   nprd_smi, NONE, 0,	none, NONE, 0,	     DS(2, 4)),
	NPCM7XX_PINCFG(191,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),  /* XX */

	NPCM7XX_PINCFG(192,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),  /* XX */
	NPCM7XX_PINCFG(193,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(194,	smb0b, I2CSEGSEL, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(195,	smb0b, I2CSEGSEL, 0,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(196,	smb0c, I2CSEGSEL, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(197,   smb0den, I2CSEGSEL, 22,     none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(198,	smb0d, I2CSEGSEL, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(199,	smb0d, I2CSEGSEL, 2,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(200,        r2, MFSEL1, 14,        none, NONE, 0,        none, NONE, 0,       0),
	NPCM7XX_PINCFG(201,	   r1, MFSEL3, 9,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(202,	smb0c, I2CSEGSEL, 1,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(203,    faninx, MFSEL3, 3,         none, NONE, 0,	none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(204,	  ddc, NONE, 0,           gpio, MFSEL3, 22,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(205,	  ddc, NONE, 0,           gpio, MFSEL3, 22,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(206,	  ddc, NONE, 0,           gpio, MFSEL3, 22,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(207,	  ddc, NONE, 0,           gpio, MFSEL3, 22,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(208,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(209,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(210,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(211,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(212,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(213,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(214,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(215,       rg2, MFSEL4, 24,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(216,   rg2mdio, MFSEL4, 23,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(217,   rg2mdio, MFSEL4, 23,         ddr, MFSEL3, 26,     none, NONE, 0,       0),
	NPCM7XX_PINCFG(218,     wकरोg1, MFSEL3, 19,        none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(219,     wकरोg2, MFSEL3, 20,        none, NONE, 0,	none, NONE, 0,	     DS(4, 8)),
	NPCM7XX_PINCFG(220,	smb12, MFSEL3, 5,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(221,	smb12, MFSEL3, 5,	  none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(222,     smb13, MFSEL3, 6,         none, NONE, 0,	none, NONE, 0,	     0),
	NPCM7XX_PINCFG(223,     smb13, MFSEL3, 6,         none, NONE, 0,	none, NONE, 0,	     0),

	NPCM7XX_PINCFG(224,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     SLEW),
	NPCM7XX_PINCFG(225,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW | GPO),
	NPCM7XX_PINCFG(226,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW | GPO),
	NPCM7XX_PINCFG(227,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(228,   spixcs1, MFSEL4, 28,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(229,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(230,	 spix, MFSEL4, 27,        none, NONE, 0,	none, NONE, 0,	     DS(8, 12) | SLEW),
	NPCM7XX_PINCFG(231,    clkreq, MFSEL4, 9,         none, NONE, 0,        none, NONE, 0,	     DS(8, 12)),
	NPCM7XX_PINCFG(253,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* SDHC1 घातer */
	NPCM7XX_PINCFG(254,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* SDHC2 घातer */
	NPCM7XX_PINCFG(255,	 none, NONE, 0,		  none, NONE, 0,	none, NONE, 0,	     GPI), /* DACOSEL */
पूर्ण;

/* number, name, drv_data */
अटल स्थिर काष्ठा pinctrl_pin_desc npcm7xx_pins[] = अणु
	PINCTRL_PIN(0,	"GPIO0/IOX1DI"),
	PINCTRL_PIN(1,	"GPIO1/IOX1LD"),
	PINCTRL_PIN(2,	"GPIO2/IOX1CK"),
	PINCTRL_PIN(3,	"GPIO3/IOX1D0"),
	PINCTRL_PIN(4,	"GPIO4/IOX2DI/SMB1DSDA"),
	PINCTRL_PIN(5,	"GPIO5/IOX2LD/SMB1DSCL"),
	PINCTRL_PIN(6,	"GPIO6/IOX2CK/SMB2DSDA"),
	PINCTRL_PIN(7,	"GPIO7/IOX2D0/SMB2DSCL"),
	PINCTRL_PIN(8,	"GPIO8/LKGPO1"),
	PINCTRL_PIN(9,	"GPIO9/LKGPO2"),
	PINCTRL_PIN(10, "GPIO10/IOXHLD"),
	PINCTRL_PIN(11, "GPIO11/IOXHCK"),
	PINCTRL_PIN(12, "GPIO12/GSPICK/SMB5BSCL"),
	PINCTRL_PIN(13, "GPIO13/GSPIDO/SMB5BSDA"),
	PINCTRL_PIN(14, "GPIO14/GSPIDI/SMB5CSCL"),
	PINCTRL_PIN(15, "GPIO15/GSPICS/SMB5CSDA"),
	PINCTRL_PIN(16, "GPIO16/LKGPO0"),
	PINCTRL_PIN(17, "GPIO17/PSPI2DI/SMB4DEN"),
	PINCTRL_PIN(18, "GPIO18/PSPI2D0/SMB4BSDA"),
	PINCTRL_PIN(19, "GPIO19/PSPI2CK/SMB4BSCL"),
	PINCTRL_PIN(20, "GPIO20/SMB4CSDA/SMB15SDA"),
	PINCTRL_PIN(21, "GPIO21/SMB4CSCL/SMB15SCL"),
	PINCTRL_PIN(22, "GPIO22/SMB4DSDA/SMB14SDA"),
	PINCTRL_PIN(23, "GPIO23/SMB4DSCL/SMB14SCL"),
	PINCTRL_PIN(24, "GPIO24/IOXHDO"),
	PINCTRL_PIN(25, "GPIO25/IOXHDI"),
	PINCTRL_PIN(26, "GPIO26/SMB5SDA"),
	PINCTRL_PIN(27, "GPIO27/SMB5SCL"),
	PINCTRL_PIN(28, "GPIO28/SMB4SDA"),
	PINCTRL_PIN(29, "GPIO29/SMB4SCL"),
	PINCTRL_PIN(30, "GPIO30/SMB3SDA"),
	PINCTRL_PIN(31, "GPIO31/SMB3SCL"),

	PINCTRL_PIN(32, "GPIO32/nSPI0CS1"),
	PINCTRL_PIN(33, "SPI0D2"),
	PINCTRL_PIN(34, "SPI0D3"),
	PINCTRL_PIN(37, "GPIO37/SMB3CSDA"),
	PINCTRL_PIN(38, "GPIO38/SMB3CSCL"),
	PINCTRL_PIN(39, "GPIO39/SMB3BSDA"),
	PINCTRL_PIN(40, "GPIO40/SMB3BSCL"),
	PINCTRL_PIN(41, "GPIO41/BSPRXD"),
	PINCTRL_PIN(42, "GPO42/BSPTXD/STRAP11"),
	PINCTRL_PIN(43, "GPIO43/RXD1/JTMS2/BU1RXD"),
	PINCTRL_PIN(44, "GPIO44/nCTS1/JTDI2/BU1CTS"),
	PINCTRL_PIN(45, "GPIO45/nDCD1/JTDO2"),
	PINCTRL_PIN(46, "GPIO46/nDSR1/JTCK2"),
	PINCTRL_PIN(47, "GPIO47/nRI1/JCP_RDY2"),
	PINCTRL_PIN(48, "GPIO48/TXD2/BSPTXD"),
	PINCTRL_PIN(49, "GPIO49/RXD2/BSPRXD"),
	PINCTRL_PIN(50, "GPIO50/nCTS2"),
	PINCTRL_PIN(51, "GPO51/nRTS2/STRAP2"),
	PINCTRL_PIN(52, "GPIO52/nDCD2"),
	PINCTRL_PIN(53, "GPO53/nDTR2_BOUT2/STRAP1"),
	PINCTRL_PIN(54, "GPIO54/nDSR2"),
	PINCTRL_PIN(55, "GPIO55/nRI2"),
	PINCTRL_PIN(56, "GPIO56/R1RXERR"),
	PINCTRL_PIN(57, "GPIO57/R1MDC"),
	PINCTRL_PIN(58, "GPIO58/R1MDIO"),
	PINCTRL_PIN(59, "GPIO59/SMB3DSDA"),
	PINCTRL_PIN(60, "GPIO60/SMB3DSCL"),
	PINCTRL_PIN(61, "GPO61/nDTR1_BOUT1/STRAP6"),
	PINCTRL_PIN(62, "GPO62/nRTST1/STRAP5"),
	PINCTRL_PIN(63, "GPO63/TXD1/STRAP4"),

	PINCTRL_PIN(64, "GPIO64/FANIN0"),
	PINCTRL_PIN(65, "GPIO65/FANIN1"),
	PINCTRL_PIN(66, "GPIO66/FANIN2"),
	PINCTRL_PIN(67, "GPIO67/FANIN3"),
	PINCTRL_PIN(68, "GPIO68/FANIN4"),
	PINCTRL_PIN(69, "GPIO69/FANIN5"),
	PINCTRL_PIN(70, "GPIO70/FANIN6"),
	PINCTRL_PIN(71, "GPIO71/FANIN7"),
	PINCTRL_PIN(72, "GPIO72/FANIN8"),
	PINCTRL_PIN(73, "GPIO73/FANIN9"),
	PINCTRL_PIN(74, "GPIO74/FANIN10"),
	PINCTRL_PIN(75, "GPIO75/FANIN11"),
	PINCTRL_PIN(76, "GPIO76/FANIN12"),
	PINCTRL_PIN(77, "GPIO77/FANIN13"),
	PINCTRL_PIN(78, "GPIO78/FANIN14"),
	PINCTRL_PIN(79, "GPIO79/FANIN15"),
	PINCTRL_PIN(80, "GPIO80/PWM0"),
	PINCTRL_PIN(81, "GPIO81/PWM1"),
	PINCTRL_PIN(82, "GPIO82/PWM2"),
	PINCTRL_PIN(83, "GPIO83/PWM3"),
	PINCTRL_PIN(84, "GPIO84/R2TXD0"),
	PINCTRL_PIN(85, "GPIO85/R2TXD1"),
	PINCTRL_PIN(86, "GPIO86/R2TXEN"),
	PINCTRL_PIN(87, "GPIO87/R2RXD0"),
	PINCTRL_PIN(88, "GPIO88/R2RXD1"),
	PINCTRL_PIN(89, "GPIO89/R2CRSDV"),
	PINCTRL_PIN(90, "GPIO90/R2RXERR"),
	PINCTRL_PIN(91, "GPIO91/R2MDC"),
	PINCTRL_PIN(92, "GPIO92/R2MDIO"),
	PINCTRL_PIN(93, "GPIO93/GA20/SMB5DSCL"),
	PINCTRL_PIN(94, "GPIO94/nKBRST/SMB5DSDA"),
	PINCTRL_PIN(95, "GPIO95/nLRESET/nESPIRST"),

	PINCTRL_PIN(96, "GPIO96/RG1TXD0"),
	PINCTRL_PIN(97, "GPIO97/RG1TXD1"),
	PINCTRL_PIN(98, "GPIO98/RG1TXD2"),
	PINCTRL_PIN(99, "GPIO99/RG1TXD3"),
	PINCTRL_PIN(100, "GPIO100/RG1TXC"),
	PINCTRL_PIN(101, "GPIO101/RG1TXCTL"),
	PINCTRL_PIN(102, "GPIO102/RG1RXD0"),
	PINCTRL_PIN(103, "GPIO103/RG1RXD1"),
	PINCTRL_PIN(104, "GPIO104/RG1RXD2"),
	PINCTRL_PIN(105, "GPIO105/RG1RXD3"),
	PINCTRL_PIN(106, "GPIO106/RG1RXC"),
	PINCTRL_PIN(107, "GPIO107/RG1RXCTL"),
	PINCTRL_PIN(108, "GPIO108/RG1MDC"),
	PINCTRL_PIN(109, "GPIO109/RG1MDIO"),
	PINCTRL_PIN(110, "GPIO110/RG2TXD0/DDRV0"),
	PINCTRL_PIN(111, "GPIO111/RG2TXD1/DDRV1"),
	PINCTRL_PIN(112, "GPIO112/RG2TXD2/DDRV2"),
	PINCTRL_PIN(113, "GPIO113/RG2TXD3/DDRV3"),
	PINCTRL_PIN(114, "GPIO114/SMB0SCL"),
	PINCTRL_PIN(115, "GPIO115/SMB0SDA"),
	PINCTRL_PIN(116, "GPIO116/SMB1SCL"),
	PINCTRL_PIN(117, "GPIO117/SMB1SDA"),
	PINCTRL_PIN(118, "GPIO118/SMB2SCL"),
	PINCTRL_PIN(119, "GPIO119/SMB2SDA"),
	PINCTRL_PIN(120, "GPIO120/SMB2CSDA"),
	PINCTRL_PIN(121, "GPIO121/SMB2CSCL"),
	PINCTRL_PIN(122, "GPIO122/SMB2BSDA"),
	PINCTRL_PIN(123, "GPIO123/SMB2BSCL"),
	PINCTRL_PIN(124, "GPIO124/SMB1CSDA"),
	PINCTRL_PIN(125, "GPIO125/SMB1CSCL"),
	PINCTRL_PIN(126, "GPIO126/SMB1BSDA"),
	PINCTRL_PIN(127, "GPIO127/SMB1BSCL"),

	PINCTRL_PIN(128, "GPIO128/SMB8SCL"),
	PINCTRL_PIN(129, "GPIO129/SMB8SDA"),
	PINCTRL_PIN(130, "GPIO130/SMB9SCL"),
	PINCTRL_PIN(131, "GPIO131/SMB9SDA"),
	PINCTRL_PIN(132, "GPIO132/SMB10SCL"),
	PINCTRL_PIN(133, "GPIO133/SMB10SDA"),
	PINCTRL_PIN(134, "GPIO134/SMB11SCL"),
	PINCTRL_PIN(135, "GPIO135/SMB11SDA"),
	PINCTRL_PIN(136, "GPIO136/SD1DT0"),
	PINCTRL_PIN(137, "GPIO137/SD1DT1"),
	PINCTRL_PIN(138, "GPIO138/SD1DT2"),
	PINCTRL_PIN(139, "GPIO139/SD1DT3"),
	PINCTRL_PIN(140, "GPIO140/SD1CLK"),
	PINCTRL_PIN(141, "GPIO141/SD1WP"),
	PINCTRL_PIN(142, "GPIO142/SD1CMD"),
	PINCTRL_PIN(143, "GPIO143/SD1CD/SD1PWR"),
	PINCTRL_PIN(144, "GPIO144/PWM4"),
	PINCTRL_PIN(145, "GPIO145/PWM5"),
	PINCTRL_PIN(146, "GPIO146/PWM6"),
	PINCTRL_PIN(147, "GPIO147/PWM7"),
	PINCTRL_PIN(148, "GPIO148/MMCDT4"),
	PINCTRL_PIN(149, "GPIO149/MMCDT5"),
	PINCTRL_PIN(150, "GPIO150/MMCDT6"),
	PINCTRL_PIN(151, "GPIO151/MMCDT7"),
	PINCTRL_PIN(152, "GPIO152/MMCCLK"),
	PINCTRL_PIN(153, "GPIO153/MMCWP"),
	PINCTRL_PIN(154, "GPIO154/MMCCMD"),
	PINCTRL_PIN(155, "GPIO155/nMMCCD/nMMCRST"),
	PINCTRL_PIN(156, "GPIO156/MMCDT0"),
	PINCTRL_PIN(157, "GPIO157/MMCDT1"),
	PINCTRL_PIN(158, "GPIO158/MMCDT2"),
	PINCTRL_PIN(159, "GPIO159/MMCDT3"),

	PINCTRL_PIN(160, "GPIO160/CLKOUT/RNGOSCOUT"),
	PINCTRL_PIN(161, "GPIO161/nLFRAME/nESPICS"),
	PINCTRL_PIN(162, "GPIO162/SERIRQ"),
	PINCTRL_PIN(163, "GPIO163/LCLK/ESPICLK"),
	PINCTRL_PIN(164, "GPIO164/LAD0/ESPI_IO0"/*dscnt6*/),
	PINCTRL_PIN(165, "GPIO165/LAD1/ESPI_IO1"/*dscnt6*/),
	PINCTRL_PIN(166, "GPIO166/LAD2/ESPI_IO2"/*dscnt6*/),
	PINCTRL_PIN(167, "GPIO167/LAD3/ESPI_IO3"/*dscnt6*/),
	PINCTRL_PIN(168, "GPIO168/nCLKRUN/nESPIALERT"),
	PINCTRL_PIN(169, "GPIO169/nSCIPME"),
	PINCTRL_PIN(170, "GPIO170/nSMI"),
	PINCTRL_PIN(171, "GPIO171/SMB6SCL"),
	PINCTRL_PIN(172, "GPIO172/SMB6SDA"),
	PINCTRL_PIN(173, "GPIO173/SMB7SCL"),
	PINCTRL_PIN(174, "GPIO174/SMB7SDA"),
	PINCTRL_PIN(175, "GPIO175/PSPI1CK/FANIN19"),
	PINCTRL_PIN(176, "GPIO176/PSPI1DO/FANIN18"),
	PINCTRL_PIN(177, "GPIO177/PSPI1DI/FANIN17"),
	PINCTRL_PIN(178, "GPIO178/R1TXD0"),
	PINCTRL_PIN(179, "GPIO179/R1TXD1"),
	PINCTRL_PIN(180, "GPIO180/R1TXEN"),
	PINCTRL_PIN(181, "GPIO181/R1RXD0"),
	PINCTRL_PIN(182, "GPIO182/R1RXD1"),
	PINCTRL_PIN(183, "GPIO183/SPI3CK"),
	PINCTRL_PIN(184, "GPO184/SPI3D0/STRAP9"),
	PINCTRL_PIN(185, "GPO185/SPI3D1/STRAP10"),
	PINCTRL_PIN(186, "GPIO186/nSPI3CS0"),
	PINCTRL_PIN(187, "GPIO187/nSPI3CS1"),
	PINCTRL_PIN(188, "GPIO188/SPI3D2/nSPI3CS2"),
	PINCTRL_PIN(189, "GPIO189/SPI3D3/nSPI3CS3"),
	PINCTRL_PIN(190, "GPIO190/nPRD_SMI"),
	PINCTRL_PIN(191, "GPIO191"),

	PINCTRL_PIN(192, "GPIO192"),
	PINCTRL_PIN(193, "GPIO193/R1CRSDV"),
	PINCTRL_PIN(194, "GPIO194/SMB0BSCL"),
	PINCTRL_PIN(195, "GPIO195/SMB0BSDA"),
	PINCTRL_PIN(196, "GPIO196/SMB0CSCL"),
	PINCTRL_PIN(197, "GPIO197/SMB0DEN"),
	PINCTRL_PIN(198, "GPIO198/SMB0DSDA"),
	PINCTRL_PIN(199, "GPIO199/SMB0DSCL"),
	PINCTRL_PIN(200, "GPIO200/R2CK"),
	PINCTRL_PIN(201, "GPIO201/R1CK"),
	PINCTRL_PIN(202, "GPIO202/SMB0CSDA"),
	PINCTRL_PIN(203, "GPIO203/FANIN16"),
	PINCTRL_PIN(204, "GPIO204/DDC2SCL"),
	PINCTRL_PIN(205, "GPIO205/DDC2SDA"),
	PINCTRL_PIN(206, "GPIO206/HSYNC2"),
	PINCTRL_PIN(207, "GPIO207/VSYNC2"),
	PINCTRL_PIN(208, "GPIO208/RG2TXC/DVCK"),
	PINCTRL_PIN(209, "GPIO209/RG2TXCTL/DDRV4"),
	PINCTRL_PIN(210, "GPIO210/RG2RXD0/DDRV5"),
	PINCTRL_PIN(211, "GPIO211/RG2RXD1/DDRV6"),
	PINCTRL_PIN(212, "GPIO212/RG2RXD2/DDRV7"),
	PINCTRL_PIN(213, "GPIO213/RG2RXD3/DDRV8"),
	PINCTRL_PIN(214, "GPIO214/RG2RXC/DDRV9"),
	PINCTRL_PIN(215, "GPIO215/RG2RXCTL/DDRV10"),
	PINCTRL_PIN(216, "GPIO216/RG2MDC/DDRV11"),
	PINCTRL_PIN(217, "GPIO217/RG2MDIO/DVHSYNC"),
	PINCTRL_PIN(218, "GPIO218/nWDO1"),
	PINCTRL_PIN(219, "GPIO219/nWDO2"),
	PINCTRL_PIN(220, "GPIO220/SMB12SCL"),
	PINCTRL_PIN(221, "GPIO221/SMB12SDA"),
	PINCTRL_PIN(222, "GPIO222/SMB13SCL"),
	PINCTRL_PIN(223, "GPIO223/SMB13SDA"),

	PINCTRL_PIN(224, "GPIO224/SPIXCK"),
	PINCTRL_PIN(225, "GPO225/SPIXD0/STRAP12"),
	PINCTRL_PIN(226, "GPO226/SPIXD1/STRAP13"),
	PINCTRL_PIN(227, "GPIO227/nSPIXCS0"),
	PINCTRL_PIN(228, "GPIO228/nSPIXCS1"),
	PINCTRL_PIN(229, "GPO229/SPIXD2/STRAP3"),
	PINCTRL_PIN(230, "GPIO230/SPIXD3"),
	PINCTRL_PIN(231, "GPIO231/nCLKREQ"),
	PINCTRL_PIN(255, "GPI255/DACOSEL"),
पूर्ण;

/* Enable mode in pin group */
अटल व्योम npcm7xx_setfunc(काष्ठा regmap *gcr_regmap, स्थिर अचिन्हित पूर्णांक *pin,
			    पूर्णांक pin_number, पूर्णांक mode)
अणु
	स्थिर काष्ठा npcm7xx_pincfg *cfg;
	पूर्णांक i;

	क्रम (i = 0 ; i < pin_number ; i++) अणु
		cfg = &pincfg[pin[i]];
		अगर (mode == fn_gpio || cfg->fn0 == mode || cfg->fn1 == mode || cfg->fn2 == mode) अणु
			अगर (cfg->reg0)
				regmap_update_bits(gcr_regmap, cfg->reg0,
						   BIT(cfg->bit0),
						   !!(cfg->fn0 == mode) ?
						   BIT(cfg->bit0) : 0);
			अगर (cfg->reg1)
				regmap_update_bits(gcr_regmap, cfg->reg1,
						   BIT(cfg->bit1),
						   !!(cfg->fn1 == mode) ?
						   BIT(cfg->bit1) : 0);
			अगर (cfg->reg2)
				regmap_update_bits(gcr_regmap, cfg->reg2,
						   BIT(cfg->bit2),
						   !!(cfg->fn2 == mode) ?
						   BIT(cfg->bit2) : 0);
		पूर्ण
	पूर्ण
पूर्ण

/* Get slew rate of pin (high/low) */
अटल पूर्णांक npcm7xx_get_slew_rate(काष्ठा npcm7xx_gpio *bank,
				 काष्ठा regmap *gcr_regmap, अचिन्हित पूर्णांक pin)
अणु
	u32 val;
	पूर्णांक gpio = (pin % bank->gc.ngpio);
	अचिन्हित दीर्घ pinmask = BIT(gpio);

	अगर (pincfg[pin].flag & SLEW)
		वापस ioपढ़ो32(bank->base + NPCM7XX_GP_N_OSRC)
		& pinmask;
	/* LPC Slew rate in SRCNT रेजिस्टर */
	अगर (pincfg[pin].flag & SLEWLPC) अणु
		regmap_पढ़ो(gcr_regmap, NPCM7XX_GCR_SRCNT, &val);
		वापस !!(val & SRCNT_ESPI);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Set slew rate of pin (high/low) */
अटल पूर्णांक npcm7xx_set_slew_rate(काष्ठा npcm7xx_gpio *bank,
				 काष्ठा regmap *gcr_regmap, अचिन्हित पूर्णांक pin,
				 पूर्णांक arg)
अणु
	पूर्णांक gpio = BIT(pin % bank->gc.ngpio);

	अगर (pincfg[pin].flag & SLEW) अणु
		चयन (arg) अणु
		हाल 0:
			npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_OSRC,
				      gpio);
			वापस 0;
		हाल 1:
			npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_OSRC,
				      gpio);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* LPC Slew rate in SRCNT रेजिस्टर */
	अगर (pincfg[pin].flag & SLEWLPC) अणु
		चयन (arg) अणु
		हाल 0:
			regmap_update_bits(gcr_regmap, NPCM7XX_GCR_SRCNT,
					   SRCNT_ESPI, 0);
			वापस 0;
		हाल 1:
			regmap_update_bits(gcr_regmap, NPCM7XX_GCR_SRCNT,
					   SRCNT_ESPI, SRCNT_ESPI);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Get drive strength क्रम a pin, अगर supported */
अटल पूर्णांक npcm7xx_get_drive_strength(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक pin)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	पूर्णांक gpio = (pin % bank->gc.ngpio);
	अचिन्हित दीर्घ pinmask = BIT(gpio);
	u32 ds = 0;
	पूर्णांक flg, val;

	flg = pincfg[pin].flag;
	अगर (flg & DRIVE_STRENGTH_MASK) अणु
		/* Get standard पढ़ोing */
		val = ioपढ़ो32(bank->base + NPCM7XX_GP_N_ODSC)
		& pinmask;
		ds = val ? DSHI(flg) : DSLO(flg);
		dev_dbg(bank->gc.parent,
			"pin %d strength %d = %d\n", pin, val, ds);
		वापस ds;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Set drive strength क्रम a pin, अगर supported */
अटल पूर्णांक npcm7xx_set_drive_strength(काष्ठा npcm7xx_pinctrl *npcm,
				      अचिन्हित पूर्णांक pin, पूर्णांक nval)
अणु
	पूर्णांक v;
	काष्ठा npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	पूर्णांक gpio = BIT(pin % bank->gc.ngpio);

	v = (pincfg[pin].flag & DRIVE_STRENGTH_MASK);
	अगर (!nval || !v)
		वापस -ENOTSUPP;
	अगर (DSLO(v) == nval) अणु
		dev_dbg(bank->gc.parent,
			"setting pin %d to low strength [%d]\n", pin, nval);
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_ODSC, gpio);
		वापस 0;
	पूर्ण अन्यथा अगर (DSHI(v) == nval) अणु
		dev_dbg(bank->gc.parent,
			"setting pin %d to high strength [%d]\n", pin, nval);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_ODSC, gpio);
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

/* pinctrl_ops */
अटल व्योम npcm7xx_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, "pinctrl_ops.dbg: %d", offset);
पूर्ण

अटल पूर्णांक npcm7xx_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npcm->dev, "group size: %d\n", ARRAY_SIZE(npcm7xx_groups));
	वापस ARRAY_SIZE(npcm7xx_groups);
पूर्ण

अटल स्थिर अक्षर *npcm7xx_get_group_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक selector)
अणु
	वापस npcm7xx_groups[selector].name;
पूर्ण

अटल पूर्णांक npcm7xx_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  स्थिर अचिन्हित पूर्णांक **pins,
				  अचिन्हित पूर्णांक *npins)
अणु
	*npins = npcm7xx_groups[selector].npins;
	*pins  = npcm7xx_groups[selector].pins;

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा device_node *np_config,
				  काष्ठा pinctrl_map **map,
				  u32 *num_maps)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npcm->dev, "dt_node_to_map: %s\n", np_config->name);
	वापस pinconf_generic_dt_node_to_map(pctldev, np_config,
					      map, num_maps,
					      PIN_MAP_TYPE_INVALID);
पूर्ण

अटल व्योम npcm7xx_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, u32 num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops npcm7xx_pinctrl_ops = अणु
	.get_groups_count = npcm7xx_get_groups_count,
	.get_group_name = npcm7xx_get_group_name,
	.get_group_pins = npcm7xx_get_group_pins,
	.pin_dbg_show = npcm7xx_pin_dbg_show,
	.dt_node_to_map = npcm7xx_dt_node_to_map,
	.dt_मुक्त_map = npcm7xx_dt_मुक्त_map,
पूर्ण;

/* pinmux_ops  */
अटल पूर्णांक npcm7xx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(npcm7xx_funcs);
पूर्ण

अटल स्थिर अक्षर *npcm7xx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक function)
अणु
	वापस npcm7xx_funcs[function].name;
पूर्ण

अटल पूर्णांक npcm7xx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक function,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित पूर्णांक * स्थिर ngroups)
अणु
	*ngroups = npcm7xx_funcs[function].ngroups;
	*groups	 = npcm7xx_funcs[function].groups;

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक function,
				  अचिन्हित पूर्णांक group)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npcm->dev, "set_mux: %d, %d[%s]\n", function, group,
		npcm7xx_groups[group].name);

	npcm7xx_setfunc(npcm->gcr_regmap, npcm7xx_groups[group].pins,
			npcm7xx_groups[group].npins, group);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	अगर (!range) अणु
		dev_err(npcm->dev, "invalid range\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!range->gc) अणु
		dev_err(npcm->dev, "invalid gpiochip\n");
		वापस -EINVAL;
	पूर्ण

	npcm7xx_setfunc(npcm->gcr_regmap, &offset, 1, fn_gpio);

	वापस 0;
पूर्ण

/* Release GPIO back to pinctrl mode */
अटल व्योम npcm7xx_gpio_request_मुक्त(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक virq;

	virq = irq_find_mapping(npcm->करोमुख्य, offset);
	अगर (virq)
		irq_dispose_mapping(virq);
पूर्ण

/* Set GPIO direction */
अटल पूर्णांक npcm_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा npcm7xx_gpio *bank =
		&npcm->gpio_bank[offset / NPCM7XX_GPIO_PER_BANK];
	पूर्णांक gpio = BIT(offset % bank->gc.ngpio);

	dev_dbg(bank->gc.parent, "GPIO Set Direction: %d = %d\n", offset,
		input);
	अगर (input)
		ioग_लिखो32(gpio, bank->base + NPCM7XX_GP_N_OEC);
	अन्यथा
		ioग_लिखो32(gpio, bank->base + NPCM7XX_GP_N_OES);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops npcm7xx_pinmux_ops = अणु
	.get_functions_count = npcm7xx_get_functions_count,
	.get_function_name = npcm7xx_get_function_name,
	.get_function_groups = npcm7xx_get_function_groups,
	.set_mux = npcm7xx_pinmux_set_mux,
	.gpio_request_enable = npcm7xx_gpio_request_enable,
	.gpio_disable_मुक्त = npcm7xx_gpio_request_मुक्त,
	.gpio_set_direction = npcm_gpio_set_direction,
पूर्ण;

/* pinconf_ops */
अटल पूर्णांक npcm7xx_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	पूर्णांक gpio = (pin % bank->gc.ngpio);
	अचिन्हित दीर्घ pinmask = BIT(gpio);
	u32 ie, oe, pu, pd;
	पूर्णांक rc = 0;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		pu = ioपढ़ो32(bank->base + NPCM7XX_GP_N_PU) & pinmask;
		pd = ioपढ़ो32(bank->base + NPCM7XX_GP_N_PD) & pinmask;
		अगर (param == PIN_CONFIG_BIAS_DISABLE)
			rc = (!pu && !pd);
		अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_UP)
			rc = (pu && !pd);
		अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_DOWN)
			rc = (!pu && pd);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
	हाल PIN_CONFIG_INPUT_ENABLE:
		ie = ioपढ़ो32(bank->base + NPCM7XX_GP_N_IEM) & pinmask;
		oe = ioपढ़ो32(bank->base + NPCM7XX_GP_N_OE) & pinmask;
		अगर (param == PIN_CONFIG_INPUT_ENABLE)
			rc = (ie && !oe);
		अन्यथा अगर (param == PIN_CONFIG_OUTPUT)
			rc = (!ie && oe);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		rc = !(ioपढ़ो32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		rc = ioपढ़ो32(bank->base + NPCM7XX_GP_N_OTYP) & pinmask;
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		rc = ioपढ़ो32(bank->base + NPCM7XX_GP_N_DBNC) & pinmask;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		rc = npcm7xx_get_drive_strength(pctldev, pin);
		अगर (rc)
			*config = pinconf_to_config_packed(param, rc);
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		rc = npcm7xx_get_slew_rate(bank, npcm->gcr_regmap, pin);
		अगर (rc >= 0)
			*config = pinconf_to_config_packed(param, rc);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!rc)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_config_set_one(काष्ठा npcm7xx_pinctrl *npcm,
				  अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(config);
	u16 arg = pinconf_to_config_argument(config);
	काष्ठा npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	पूर्णांक gpio = BIT(pin % bank->gc.ngpio);

	dev_dbg(bank->gc.parent, "param=%d %d[GPIO]\n", param, pin);
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_PD, gpio);
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_PU, gpio);
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		ioग_लिखो32(gpio, bank->base + NPCM7XX_GP_N_OEC);
		bank->direction_input(&bank->gc, pin % bank->gc.ngpio);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		ioग_लिखो32(gpio, bank->base + NPCM7XX_GP_N_OES);
		bank->direction_output(&bank->gc, pin % bank->gc.ngpio, arg);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		npcm_gpio_clr(&bank->gc, bank->base + NPCM7XX_GP_N_OTYP, gpio);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_OTYP, gpio);
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		npcm_gpio_set(&bank->gc, bank->base + NPCM7XX_GP_N_DBNC, gpio);
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		वापस npcm7xx_set_slew_rate(bank, npcm->gcr_regmap, pin, arg);
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		वापस npcm7xx_set_drive_strength(npcm, pin, arg);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/* Set multiple configuration settings क्रम a pin */
अटल पूर्णांक npcm7xx_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक rc;

	जबतक (num_configs--) अणु
		rc = npcm7xx_config_set_one(npcm, pin, *configs++);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops npcm7xx_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = npcm7xx_config_get,
	.pin_config_set = npcm7xx_config_set,
पूर्ण;

/* pinctrl_desc */
अटल काष्ठा pinctrl_desc npcm7xx_pinctrl_desc = अणु
	.name = "npcm7xx-pinctrl",
	.pins = npcm7xx_pins,
	.npins = ARRAY_SIZE(npcm7xx_pins),
	.pctlops = &npcm7xx_pinctrl_ops,
	.pmxops = &npcm7xx_pinmux_ops,
	.confops = &npcm7xx_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक npcm7xx_gpio_of(काष्ठा npcm7xx_pinctrl *pctrl)
अणु
	पूर्णांक ret = -ENXIO;
	काष्ठा resource res;
	पूर्णांक id = 0, irq;
	काष्ठा device_node *np;
	काष्ठा of_phandle_args pinspec;

	क्रम_each_available_child_of_node(pctrl->dev->of_node, np)
		अगर (of_find_property(np, "gpio-controller", शून्य)) अणु
			ret = of_address_to_resource(np, 0, &res);
			अगर (ret < 0) अणु
				dev_err(pctrl->dev,
					"Resource fail for GPIO bank %u\n", id);
				वापस ret;
			पूर्ण

			pctrl->gpio_bank[id].base =
				ioremap(res.start, resource_size(&res));

			irq = irq_of_parse_and_map(np, 0);
			अगर (irq < 0) अणु
				dev_err(pctrl->dev,
					"No IRQ for GPIO bank %u\n", id);
				ret = irq;
				वापस ret;
			पूर्ण

			ret = bgpio_init(&pctrl->gpio_bank[id].gc,
					 pctrl->dev, 4,
					 pctrl->gpio_bank[id].base +
					 NPCM7XX_GP_N_DIN,
					 pctrl->gpio_bank[id].base +
					 NPCM7XX_GP_N_DOUT,
					 शून्य,
					 शून्य,
					 pctrl->gpio_bank[id].base +
					 NPCM7XX_GP_N_IEM,
					 BGPIOF_READ_OUTPUT_REG_SET);
			अगर (ret) अणु
				dev_err(pctrl->dev, "bgpio_init() failed\n");
				वापस ret;
			पूर्ण

			ret = of_parse_phandle_with_fixed_args(np,
							       "gpio-ranges", 3,
							       0, &pinspec);
			अगर (ret < 0) अणु
				dev_err(pctrl->dev,
					"gpio-ranges fail for GPIO bank %u\n",
					id);
				वापस ret;
			पूर्ण

			pctrl->gpio_bank[id].irq = irq;
			pctrl->gpio_bank[id].irq_chip = npcmgpio_irqchip;
			pctrl->gpio_bank[id].gc.parent = pctrl->dev;
			pctrl->gpio_bank[id].irqbase =
				id * NPCM7XX_GPIO_PER_BANK;
			pctrl->gpio_bank[id].pinctrl_id = pinspec.args[0];
			pctrl->gpio_bank[id].gc.base = pinspec.args[1];
			pctrl->gpio_bank[id].gc.ngpio = pinspec.args[2];
			pctrl->gpio_bank[id].gc.owner = THIS_MODULE;
			pctrl->gpio_bank[id].gc.label =
				devm_kaप्र_लिखो(pctrl->dev, GFP_KERNEL, "%pOF",
					       np);
			अगर (pctrl->gpio_bank[id].gc.label == शून्य)
				वापस -ENOMEM;

			pctrl->gpio_bank[id].gc.dbg_show = npcmgpio_dbg_show;
			pctrl->gpio_bank[id].direction_input =
				pctrl->gpio_bank[id].gc.direction_input;
			pctrl->gpio_bank[id].gc.direction_input =
				npcmgpio_direction_input;
			pctrl->gpio_bank[id].direction_output =
				pctrl->gpio_bank[id].gc.direction_output;
			pctrl->gpio_bank[id].gc.direction_output =
				npcmgpio_direction_output;
			pctrl->gpio_bank[id].request =
				pctrl->gpio_bank[id].gc.request;
			pctrl->gpio_bank[id].gc.request = npcmgpio_gpio_request;
			pctrl->gpio_bank[id].gc.मुक्त = npcmgpio_gpio_मुक्त;
			pctrl->gpio_bank[id].gc.of_node = np;
			id++;
		पूर्ण

	pctrl->bank_num = id;
	वापस ret;
पूर्ण

अटल पूर्णांक npcm7xx_gpio_रेजिस्टर(काष्ठा npcm7xx_pinctrl *pctrl)
अणु
	पूर्णांक ret, id;

	क्रम (id = 0 ; id < pctrl->bank_num ; id++) अणु
		काष्ठा gpio_irq_chip *girq;

		girq = &pctrl->gpio_bank[id].gc.irq;
		girq->chip = &pctrl->gpio_bank[id].irq_chip;
		girq->parent_handler = npcmgpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(pctrl->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents) अणु
			ret = -ENOMEM;
			जाओ err_रेजिस्टर;
		पूर्ण
		girq->parents[0] = pctrl->gpio_bank[id].irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
		ret = devm_gpiochip_add_data(pctrl->dev,
					     &pctrl->gpio_bank[id].gc,
					     &pctrl->gpio_bank[id]);
		अगर (ret) अणु
			dev_err(pctrl->dev, "Failed to add GPIO chip %u\n", id);
			जाओ err_रेजिस्टर;
		पूर्ण

		ret = gpiochip_add_pin_range(&pctrl->gpio_bank[id].gc,
					     dev_name(pctrl->dev),
					     pctrl->gpio_bank[id].pinctrl_id,
					     pctrl->gpio_bank[id].gc.base,
					     pctrl->gpio_bank[id].gc.ngpio);
		अगर (ret < 0) अणु
			dev_err(pctrl->dev, "Failed to add GPIO bank %u\n", id);
			gpiochip_हटाओ(&pctrl->gpio_bank[id].gc);
			जाओ err_रेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	क्रम (; id > 0; id--)
		gpiochip_हटाओ(&pctrl->gpio_bank[id - 1].gc);

	वापस ret;
पूर्ण

अटल पूर्णांक npcm7xx_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm7xx_pinctrl *pctrl;
	पूर्णांक ret;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, pctrl);

	pctrl->gcr_regmap =
		syscon_regmap_lookup_by_compatible("nuvoton,npcm750-gcr");
	अगर (IS_ERR(pctrl->gcr_regmap)) अणु
		dev_err(pctrl->dev, "didn't find nuvoton,npcm750-gcr\n");
		वापस PTR_ERR(pctrl->gcr_regmap);
	पूर्ण

	ret = npcm7xx_gpio_of(pctrl);
	अगर (ret < 0) अणु
		dev_err(pctrl->dev, "Failed to gpio dt-binding %u\n", ret);
		वापस ret;
	पूर्ण

	pctrl->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev,
					       &npcm7xx_pinctrl_desc, pctrl);
	अगर (IS_ERR(pctrl->pctldev)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl device\n");
		वापस PTR_ERR(pctrl->pctldev);
	पूर्ण

	ret = npcm7xx_gpio_रेजिस्टर(pctrl);
	अगर (ret < 0) अणु
		dev_err(pctrl->dev, "Failed to register gpio %u\n", ret);
		वापस ret;
	पूर्ण

	pr_info("NPCM7xx Pinctrl driver probed\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm7xx_pinctrl_match[] = अणु
	अणु .compatible = "nuvoton,npcm750-pinctrl" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm7xx_pinctrl_match);

अटल काष्ठा platक्रमm_driver npcm7xx_pinctrl_driver = अणु
	.probe = npcm7xx_pinctrl_probe,
	.driver = अणु
		.name = "npcm7xx-pinctrl",
		.of_match_table = npcm7xx_pinctrl_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init npcm7xx_pinctrl_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&npcm7xx_pinctrl_driver);
पूर्ण
arch_initcall(npcm7xx_pinctrl_रेजिस्टर);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("jordan_hargrave@dell.com");
MODULE_AUTHOR("tomer.maimon@nuvoton.com");
MODULE_DESCRIPTION("Nuvoton NPCM7XX Pinctrl and GPIO driver");
