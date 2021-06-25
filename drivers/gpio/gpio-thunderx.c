<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016, 2017 Cavium Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र-generic/msi.h>


#घोषणा GPIO_RX_DAT	0x0
#घोषणा GPIO_TX_SET	0x8
#घोषणा GPIO_TX_CLR	0x10
#घोषणा GPIO_CONST	0x90
#घोषणा  GPIO_CONST_GPIOS_MASK 0xff
#घोषणा GPIO_BIT_CFG	0x400
#घोषणा  GPIO_BIT_CFG_TX_OE		BIT(0)
#घोषणा  GPIO_BIT_CFG_PIN_XOR		BIT(1)
#घोषणा  GPIO_BIT_CFG_INT_EN		BIT(2)
#घोषणा  GPIO_BIT_CFG_INT_TYPE		BIT(3)
#घोषणा  GPIO_BIT_CFG_FIL_MASK		GENMASK(11, 4)
#घोषणा  GPIO_BIT_CFG_FIL_CNT_SHIFT	4
#घोषणा  GPIO_BIT_CFG_FIL_SEL_SHIFT	8
#घोषणा  GPIO_BIT_CFG_TX_OD		BIT(12)
#घोषणा  GPIO_BIT_CFG_PIN_SEL_MASK	GENMASK(25, 16)
#घोषणा GPIO_INTR	0x800
#घोषणा  GPIO_INTR_INTR			BIT(0)
#घोषणा  GPIO_INTR_INTR_W1S		BIT(1)
#घोषणा  GPIO_INTR_ENA_W1C		BIT(2)
#घोषणा  GPIO_INTR_ENA_W1S		BIT(3)
#घोषणा GPIO_2ND_BANK	0x1400

#घोषणा GLITCH_FILTER_400NS ((4u << GPIO_BIT_CFG_FIL_SEL_SHIFT) | \
			     (9u << GPIO_BIT_CFG_FIL_CNT_SHIFT))

काष्ठा thunderx_gpio;

काष्ठा thunderx_line अणु
	काष्ठा thunderx_gpio	*txgpio;
	अचिन्हित पूर्णांक		line;
	अचिन्हित पूर्णांक		fil_bits;
पूर्ण;

काष्ठा thunderx_gpio अणु
	काष्ठा gpio_chip	chip;
	u8 __iomem		*रेजिस्टर_base;
	काष्ठा msix_entry	*msix_entries;	/* per line MSI-X */
	काष्ठा thunderx_line	*line_entries;	/* per line irq info */
	raw_spinlock_t		lock;
	अचिन्हित दीर्घ		invert_mask[2];
	अचिन्हित दीर्घ		od_mask[2];
	पूर्णांक			base_msi;
पूर्ण;

अटल अचिन्हित पूर्णांक bit_cfg_reg(अचिन्हित पूर्णांक line)
अणु
	वापस 8 * line + GPIO_BIT_CFG;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकr_reg(अचिन्हित पूर्णांक line)
अणु
	वापस 8 * line + GPIO_INTR;
पूर्ण

अटल bool thunderx_gpio_is_gpio_nowarn(काष्ठा thunderx_gpio *txgpio,
					 अचिन्हित पूर्णांक line)
अणु
	u64 bit_cfg = पढ़ोq(txgpio->रेजिस्टर_base + bit_cfg_reg(line));

	वापस (bit_cfg & GPIO_BIT_CFG_PIN_SEL_MASK) == 0;
पूर्ण

/*
 * Check (and WARN) that the pin is available क्रम GPIO.  We will not
 * allow modअगरication of the state of non-GPIO pins from this driver.
 */
अटल bool thunderx_gpio_is_gpio(काष्ठा thunderx_gpio *txgpio,
				  अचिन्हित पूर्णांक line)
अणु
	bool rv = thunderx_gpio_is_gpio_nowarn(txgpio, line);

	WARN_RATELIMIT(!rv, "Pin %d not available for GPIO\n", line);

	वापस rv;
पूर्ण

अटल पूर्णांक thunderx_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);

	वापस thunderx_gpio_is_gpio(txgpio, line) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक thunderx_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);

	अगर (!thunderx_gpio_is_gpio(txgpio, line))
		वापस -EIO;

	raw_spin_lock(&txgpio->lock);
	clear_bit(line, txgpio->invert_mask);
	clear_bit(line, txgpio->od_mask);
	ग_लिखोq(txgpio->line_entries[line].fil_bits,
	       txgpio->रेजिस्टर_base + bit_cfg_reg(line));
	raw_spin_unlock(&txgpio->lock);
	वापस 0;
पूर्ण

अटल व्योम thunderx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line,
			      पूर्णांक value)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);
	पूर्णांक bank = line / 64;
	पूर्णांक bank_bit = line % 64;

	व्योम __iomem *reg = txgpio->रेजिस्टर_base +
		(bank * GPIO_2ND_BANK) + (value ? GPIO_TX_SET : GPIO_TX_CLR);

	ग_लिखोq(BIT_ULL(bank_bit), reg);
पूर्ण

अटल पूर्णांक thunderx_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line,
				 पूर्णांक value)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg = txgpio->line_entries[line].fil_bits | GPIO_BIT_CFG_TX_OE;

	अगर (!thunderx_gpio_is_gpio(txgpio, line))
		वापस -EIO;

	raw_spin_lock(&txgpio->lock);

	thunderx_gpio_set(chip, line, value);

	अगर (test_bit(line, txgpio->invert_mask))
		bit_cfg |= GPIO_BIT_CFG_PIN_XOR;

	अगर (test_bit(line, txgpio->od_mask))
		bit_cfg |= GPIO_BIT_CFG_TX_OD;

	ग_लिखोq(bit_cfg, txgpio->रेजिस्टर_base + bit_cfg_reg(line));

	raw_spin_unlock(&txgpio->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक thunderx_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg;

	अगर (!thunderx_gpio_is_gpio_nowarn(txgpio, line))
		/*
		 * Say it is input क्रम now to aव्योम WARNing on
		 * gpiochip_add_data().  We will WARN अगर someone
		 * requests it or tries to use it.
		 */
		वापस 1;

	bit_cfg = पढ़ोq(txgpio->रेजिस्टर_base + bit_cfg_reg(line));

	अगर (bit_cfg & GPIO_BIT_CFG_TX_OE)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक thunderx_gpio_set_config(काष्ठा gpio_chip *chip,
				    अचिन्हित पूर्णांक line,
				    अचिन्हित दीर्घ cfg)
अणु
	bool orig_invert, orig_od, orig_dat, new_invert, new_od;
	u32 arg, sel;
	u64 bit_cfg;
	पूर्णांक bank = line / 64;
	पूर्णांक bank_bit = line % 64;
	पूर्णांक ret = -ENOTSUPP;
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);
	व्योम __iomem *reg = txgpio->रेजिस्टर_base + (bank * GPIO_2ND_BANK) + GPIO_TX_SET;

	अगर (!thunderx_gpio_is_gpio(txgpio, line))
		वापस -EIO;

	raw_spin_lock(&txgpio->lock);
	orig_invert = test_bit(line, txgpio->invert_mask);
	new_invert  = orig_invert;
	orig_od = test_bit(line, txgpio->od_mask);
	new_od = orig_od;
	orig_dat = ((पढ़ोq(reg) >> bank_bit) & 1) ^ orig_invert;
	bit_cfg = पढ़ोq(txgpio->रेजिस्टर_base + bit_cfg_reg(line));
	चयन (pinconf_to_config_param(cfg)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		/*
		 * Weird, setting खोलो-drain mode causes संकेत
		 * inversion.  Note this so we can compensate in the
		 * dir_out function.
		 */
		set_bit(line, txgpio->invert_mask);
		new_invert  = true;
		set_bit(line, txgpio->od_mask);
		new_od = true;
		ret = 0;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		clear_bit(line, txgpio->invert_mask);
		new_invert  = false;
		clear_bit(line, txgpio->od_mask);
		new_od  = false;
		ret = 0;
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		arg = pinconf_to_config_argument(cfg);
		अगर (arg > 1228) अणु /* 15 * 2^15 * 2.5nS maximum */
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		arg *= 400; /* scale to 2.5nS घड़ीs. */
		sel = 0;
		जबतक (arg > 15) अणु
			sel++;
			arg++; /* always round up */
			arg >>= 1;
		पूर्ण
		txgpio->line_entries[line].fil_bits =
			(sel << GPIO_BIT_CFG_FIL_SEL_SHIFT) |
			(arg << GPIO_BIT_CFG_FIL_CNT_SHIFT);
		bit_cfg &= ~GPIO_BIT_CFG_FIL_MASK;
		bit_cfg |= txgpio->line_entries[line].fil_bits;
		ग_लिखोq(bit_cfg, txgpio->रेजिस्टर_base + bit_cfg_reg(line));
		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	raw_spin_unlock(&txgpio->lock);

	/*
	 * If currently output and OPEN_DRAIN changed, install the new
	 * settings
	 */
	अगर ((new_invert != orig_invert || new_od != orig_od) &&
	    (bit_cfg & GPIO_BIT_CFG_TX_OE))
		ret = thunderx_gpio_dir_out(chip, line, orig_dat ^ new_invert);

	वापस ret;
पूर्ण

अटल पूर्णांक thunderx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक line)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);
	पूर्णांक bank = line / 64;
	पूर्णांक bank_bit = line % 64;
	u64 पढ़ो_bits = पढ़ोq(txgpio->रेजिस्टर_base + (bank * GPIO_2ND_BANK) + GPIO_RX_DAT);
	u64 masked_bits = पढ़ो_bits & BIT_ULL(bank_bit);

	अगर (test_bit(line, txgpio->invert_mask))
		वापस masked_bits == 0;
	अन्यथा
		वापस masked_bits != 0;
पूर्ण

अटल व्योम thunderx_gpio_set_multiple(काष्ठा gpio_chip *chip,
				       अचिन्हित दीर्घ *mask,
				       अचिन्हित दीर्घ *bits)
अणु
	पूर्णांक bank;
	u64 set_bits, clear_bits;
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(chip);

	क्रम (bank = 0; bank <= chip->ngpio / 64; bank++) अणु
		set_bits = bits[bank] & mask[bank];
		clear_bits = ~bits[bank] & mask[bank];
		ग_लिखोq(set_bits, txgpio->रेजिस्टर_base + (bank * GPIO_2ND_BANK) + GPIO_TX_SET);
		ग_लिखोq(clear_bits, txgpio->रेजिस्टर_base + (bank * GPIO_2ND_BANK) + GPIO_TX_CLR);
	पूर्ण
पूर्ण

अटल व्योम thunderx_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);

	ग_लिखोq(GPIO_INTR_INTR,
	       txgpio->रेजिस्टर_base + पूर्णांकr_reg(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम thunderx_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);

	ग_लिखोq(GPIO_INTR_ENA_W1C,
	       txgpio->रेजिस्टर_base + पूर्णांकr_reg(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम thunderx_gpio_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);

	ग_लिखोq(GPIO_INTR_ENA_W1C | GPIO_INTR_INTR,
	       txgpio->रेजिस्टर_base + पूर्णांकr_reg(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम thunderx_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);

	ग_लिखोq(GPIO_INTR_ENA_W1S,
	       txgpio->रेजिस्टर_base + पूर्णांकr_reg(irqd_to_hwirq(d)));
पूर्ण

अटल पूर्णांक thunderx_gpio_irq_set_type(काष्ठा irq_data *d,
				      अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);
	काष्ठा thunderx_line *txline =
		&txgpio->line_entries[irqd_to_hwirq(d)];
	u64 bit_cfg;

	irqd_set_trigger_type(d, flow_type);

	bit_cfg = txline->fil_bits | GPIO_BIT_CFG_INT_EN;

	अगर (flow_type & IRQ_TYPE_EDGE_BOTH) अणु
		irq_set_handler_locked(d, handle_fasteoi_ack_irq);
		bit_cfg |= GPIO_BIT_CFG_INT_TYPE;
	पूर्ण अन्यथा अणु
		irq_set_handler_locked(d, handle_fasteoi_mask_irq);
	पूर्ण

	raw_spin_lock(&txgpio->lock);
	अगर (flow_type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_LEVEL_LOW)) अणु
		bit_cfg |= GPIO_BIT_CFG_PIN_XOR;
		set_bit(txline->line, txgpio->invert_mask);
	पूर्ण अन्यथा अणु
		clear_bit(txline->line, txgpio->invert_mask);
	पूर्ण
	clear_bit(txline->line, txgpio->od_mask);
	ग_लिखोq(bit_cfg, txgpio->रेजिस्टर_base + bit_cfg_reg(txline->line));
	raw_spin_unlock(&txgpio->lock);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम thunderx_gpio_irq_enable(काष्ठा irq_data *data)
अणु
	irq_chip_enable_parent(data);
	thunderx_gpio_irq_unmask(data);
पूर्ण

अटल व्योम thunderx_gpio_irq_disable(काष्ठा irq_data *data)
अणु
	thunderx_gpio_irq_mask(data);
	irq_chip_disable_parent(data);
पूर्ण

/*
 * Interrupts are chained from underlying MSI-X vectors.  We have
 * these irq_chip functions to be able to handle level triggering
 * semantics and other acknowledgment tasks associated with the GPIO
 * mechanism.
 */
अटल काष्ठा irq_chip thunderx_gpio_irq_chip = अणु
	.name			= "GPIO",
	.irq_enable		= thunderx_gpio_irq_enable,
	.irq_disable		= thunderx_gpio_irq_disable,
	.irq_ack		= thunderx_gpio_irq_ack,
	.irq_mask		= thunderx_gpio_irq_mask,
	.irq_mask_ack		= thunderx_gpio_irq_mask_ack,
	.irq_unmask		= thunderx_gpio_irq_unmask,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_type		= thunderx_gpio_irq_set_type,

	.flags			= IRQCHIP_SET_TYPE_MASKED
पूर्ण;

अटल पूर्णांक thunderx_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *gc,
					       अचिन्हित पूर्णांक child,
					       अचिन्हित पूर्णांक child_type,
					       अचिन्हित पूर्णांक *parent,
					       अचिन्हित पूर्णांक *parent_type)
अणु
	काष्ठा thunderx_gpio *txgpio = gpiochip_get_data(gc);
	काष्ठा irq_data *irqd;
	अचिन्हित पूर्णांक irq;

	irq = txgpio->msix_entries[child].vector;
	irqd = irq_करोमुख्य_get_irq_data(gc->irq.parent_करोमुख्य, irq);
	अगर (!irqd)
		वापस -EINVAL;
	*parent = irqd_to_hwirq(irqd);
	*parent_type = IRQ_TYPE_LEVEL_HIGH;
	वापस 0;
पूर्ण

अटल व्योम *thunderx_gpio_populate_parent_alloc_info(काष्ठा gpio_chip *chip,
						      अचिन्हित पूर्णांक parent_hwirq,
						      अचिन्हित पूर्णांक parent_type)
अणु
	msi_alloc_info_t *info;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस शून्य;

	info->hwirq = parent_hwirq;
	वापस info;
पूर्ण

अटल पूर्णांक thunderx_gpio_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	व्योम __iomem * स्थिर *tbl;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा thunderx_gpio *txgpio;
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ngpio, i;
	पूर्णांक err = 0;

	txgpio = devm_kzalloc(dev, माप(*txgpio), GFP_KERNEL);
	अगर (!txgpio)
		वापस -ENOMEM;

	raw_spin_lock_init(&txgpio->lock);
	chip = &txgpio->chip;

	pci_set_drvdata(pdev, txgpio);

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device: err %d\n", err);
		जाओ out;
	पूर्ण

	err = pcim_iomap_regions(pdev, 1 << 0, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(dev, "Failed to iomap PCI device: err %d\n", err);
		जाओ out;
	पूर्ण

	tbl = pcim_iomap_table(pdev);
	txgpio->रेजिस्टर_base = tbl[0];
	अगर (!txgpio->रेजिस्टर_base) अणु
		dev_err(dev, "Cannot map PCI resource\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (pdev->subप्रणाली_device == 0xa10a) अणु
		/* CN88XX has no GPIO_CONST रेजिस्टर*/
		ngpio = 50;
		txgpio->base_msi = 48;
	पूर्ण अन्यथा अणु
		u64 c = पढ़ोq(txgpio->रेजिस्टर_base + GPIO_CONST);

		ngpio = c & GPIO_CONST_GPIOS_MASK;
		txgpio->base_msi = (c >> 8) & 0xff;
	पूर्ण

	txgpio->msix_entries = devm_kसुस्मृति(dev,
					    ngpio, माप(काष्ठा msix_entry),
					    GFP_KERNEL);
	अगर (!txgpio->msix_entries) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	txgpio->line_entries = devm_kसुस्मृति(dev,
					    ngpio,
					    माप(काष्ठा thunderx_line),
					    GFP_KERNEL);
	अगर (!txgpio->line_entries) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ngpio; i++) अणु
		u64 bit_cfg = पढ़ोq(txgpio->रेजिस्टर_base + bit_cfg_reg(i));

		txgpio->msix_entries[i].entry = txgpio->base_msi + (2 * i);
		txgpio->line_entries[i].line = i;
		txgpio->line_entries[i].txgpio = txgpio;
		/*
		 * If something has alपढ़ोy programmed the pin, use
		 * the existing glitch filter settings, otherwise go
		 * to 400nS.
		 */
		txgpio->line_entries[i].fil_bits = bit_cfg ?
			(bit_cfg & GPIO_BIT_CFG_FIL_MASK) : GLITCH_FILTER_400NS;

		अगर ((bit_cfg & GPIO_BIT_CFG_TX_OE) && (bit_cfg & GPIO_BIT_CFG_TX_OD))
			set_bit(i, txgpio->od_mask);
		अगर (bit_cfg & GPIO_BIT_CFG_PIN_XOR)
			set_bit(i, txgpio->invert_mask);
	पूर्ण


	/* Enable all MSI-X क्रम पूर्णांकerrupts on all possible lines. */
	err = pci_enable_msix_range(pdev, txgpio->msix_entries, ngpio, ngpio);
	अगर (err < 0)
		जाओ out;

	chip->label = KBUILD_MODNAME;
	chip->parent = dev;
	chip->owner = THIS_MODULE;
	chip->request = thunderx_gpio_request;
	chip->base = -1; /* System allocated */
	chip->can_sleep = false;
	chip->ngpio = ngpio;
	chip->get_direction = thunderx_gpio_get_direction;
	chip->direction_input = thunderx_gpio_dir_in;
	chip->get = thunderx_gpio_get;
	chip->direction_output = thunderx_gpio_dir_out;
	chip->set = thunderx_gpio_set;
	chip->set_multiple = thunderx_gpio_set_multiple;
	chip->set_config = thunderx_gpio_set_config;
	girq = &chip->irq;
	girq->chip = &thunderx_gpio_irq_chip;
	girq->fwnode = of_node_to_fwnode(dev->of_node);
	girq->parent_करोमुख्य =
		irq_get_irq_data(txgpio->msix_entries[0].vector)->करोमुख्य;
	girq->child_to_parent_hwirq = thunderx_gpio_child_to_parent_hwirq;
	girq->populate_parent_alloc_arg = thunderx_gpio_populate_parent_alloc_info;
	girq->handler = handle_bad_irq;
	girq->शेष_type = IRQ_TYPE_NONE;

	err = devm_gpiochip_add_data(dev, chip, txgpio);
	अगर (err)
		जाओ out;

	/* Push on irq_data and the करोमुख्य क्रम each line. */
	क्रम (i = 0; i < ngpio; i++) अणु
		काष्ठा irq_fwspec fwspec;

		fwspec.fwnode = of_node_to_fwnode(dev->of_node);
		fwspec.param_count = 2;
		fwspec.param[0] = i;
		fwspec.param[1] = IRQ_TYPE_NONE;
		err = irq_करोमुख्य_push_irq(girq->करोमुख्य,
					  txgpio->msix_entries[i].vector,
					  &fwspec);
		अगर (err < 0)
			dev_err(dev, "irq_domain_push_irq: %d\n", err);
	पूर्ण

	dev_info(dev, "ThunderX GPIO: %d lines with base %d.\n",
		 ngpio, chip->base);
	वापस 0;
out:
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम thunderx_gpio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा thunderx_gpio *txgpio = pci_get_drvdata(pdev);

	क्रम (i = 0; i < txgpio->chip.ngpio; i++)
		irq_करोमुख्य_pop_irq(txgpio->chip.irq.करोमुख्य,
				   txgpio->msix_entries[i].vector);

	irq_करोमुख्य_हटाओ(txgpio->chip.irq.करोमुख्य);

	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunderx_gpio_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xA00A) पूर्ण,
	अणु 0, पूर्ण	/* end of table */
पूर्ण;

MODULE_DEVICE_TABLE(pci, thunderx_gpio_id_table);

अटल काष्ठा pci_driver thunderx_gpio_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = thunderx_gpio_id_table,
	.probe = thunderx_gpio_probe,
	.हटाओ = thunderx_gpio_हटाओ,
पूर्ण;

module_pci_driver(thunderx_gpio_driver);

MODULE_DESCRIPTION("Cavium Inc. ThunderX/OCTEON-TX GPIO Driver");
MODULE_LICENSE("GPL");
