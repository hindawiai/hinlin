<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम the ACCES PCIe-IDIO-24 family
 * Copyright (C) 2018 William Breathitt Gray
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * This driver supports the following ACCES devices: PCIe-IDIO-24,
 * PCIe-IDI-24, PCIe-IDO-24, and PCIe-IDIO-12.
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/*
 * PLX PEX8311 PCI LCS_INTCSR Interrupt Control/Status
 *
 * Bit: Description
 *   0: Enable Interrupt Sources (Bit 0)
 *   1: Enable Interrupt Sources (Bit 1)
 *   2: Generate Internal PCI Bus Internal SERR# Interrupt
 *   3: Mailbox Interrupt Enable
 *   4: Power Management Interrupt Enable
 *   5: Power Management Interrupt
 *   6: Slave Read Local Data Parity Check Error Enable
 *   7: Slave Read Local Data Parity Check Error Status
 *   8: Internal PCI Wire Interrupt Enable
 *   9: PCI Express Doorbell Interrupt Enable
 *  10: PCI Abort Interrupt Enable
 *  11: Local Interrupt Input Enable
 *  12: Retry Abort Enable
 *  13: PCI Express Doorbell Interrupt Active
 *  14: PCI Abort Interrupt Active
 *  15: Local Interrupt Input Active
 *  16: Local Interrupt Output Enable
 *  17: Local Doorbell Interrupt Enable
 *  18: DMA Channel 0 Interrupt Enable
 *  19: DMA Channel 1 Interrupt Enable
 *  20: Local Doorbell Interrupt Active
 *  21: DMA Channel 0 Interrupt Active
 *  22: DMA Channel 1 Interrupt Active
 *  23: Built-In Self-Test (BIST) Interrupt Active
 *  24: Direct Master was the Bus Master during a Master or Target Abort
 *  25: DMA Channel 0 was the Bus Master during a Master or Target Abort
 *  26: DMA Channel 1 was the Bus Master during a Master or Target Abort
 *  27: Target Abort after पूर्णांकernal 256 consecutive Master Retrys
 *  28: PCI Bus wrote data to LCS_MBOX0
 *  29: PCI Bus wrote data to LCS_MBOX1
 *  30: PCI Bus wrote data to LCS_MBOX2
 *  31: PCI Bus wrote data to LCS_MBOX3
 */
#घोषणा PLX_PEX8311_PCI_LCS_INTCSR  0x68
#घोषणा INTCSR_INTERNAL_PCI_WIRE    BIT(8)
#घोषणा INTCSR_LOCAL_INPUT          BIT(11)

/**
 * काष्ठा idio_24_gpio_reg - GPIO device रेजिस्टरs काष्ठाure
 * @out0_7:	Read: FET Outमाला_दो 0-7
 *		Write: FET Outमाला_दो 0-7
 * @out8_15:	Read: FET Outमाला_दो 8-15
 *		Write: FET Outमाला_दो 8-15
 * @out16_23:	Read: FET Outमाला_दो 16-23
 *		Write: FET Outमाला_दो 16-23
 * @ttl_out0_7:	Read: TTL/CMOS Outमाला_दो 0-7
 *		Write: TTL/CMOS Outमाला_दो 0-7
 * @in0_7:	Read: Isolated Inमाला_दो 0-7
 *		Write: Reserved
 * @in8_15:	Read: Isolated Inमाला_दो 8-15
 *		Write: Reserved
 * @in16_23:	Read: Isolated Inमाला_दो 16-23
 *		Write: Reserved
 * @ttl_in0_7:	Read: TTL/CMOS Inमाला_दो 0-7
 *		Write: Reserved
 * @cos0_7:	Read: COS Status Inमाला_दो 0-7
 *		Write: COS Clear Inमाला_दो 0-7
 * @cos8_15:	Read: COS Status Inमाला_दो 8-15
 *		Write: COS Clear Inमाला_दो 8-15
 * @cos16_23:	Read: COS Status Inमाला_दो 16-23
 *		Write: COS Clear Inमाला_दो 16-23
 * @cos_ttl0_7:	Read: COS Status TTL/CMOS 0-7
 *		Write: COS Clear TTL/CMOS 0-7
 * @ctl:	Read: Control Register
 *		Write: Control Register
 * @reserved:	Read: Reserved
 *		Write: Reserved
 * @cos_enable:	Read: COS Enable
 *		Write: COS Enable
 * @soft_reset:	Read: IRQ Output Pin Status
 *		Write: Software Board Reset
 */
काष्ठा idio_24_gpio_reg अणु
	u8 out0_7;
	u8 out8_15;
	u8 out16_23;
	u8 ttl_out0_7;
	u8 in0_7;
	u8 in8_15;
	u8 in16_23;
	u8 ttl_in0_7;
	u8 cos0_7;
	u8 cos8_15;
	u8 cos16_23;
	u8 cos_ttl0_7;
	u8 ctl;
	u8 reserved;
	u8 cos_enable;
	u8 soft_reset;
पूर्ण;

/**
 * काष्ठा idio_24_gpio - GPIO device निजी data काष्ठाure
 * @chip:	instance of the gpio_chip
 * @lock:	synchronization lock to prevent I/O race conditions
 * @reg:	I/O address offset क्रम the GPIO device रेजिस्टरs
 * @irq_mask:	I/O bits affected by पूर्णांकerrupts
 */
काष्ठा idio_24_gpio अणु
	काष्ठा gpio_chip chip;
	raw_spinlock_t lock;
	__u8 __iomem *plx;
	काष्ठा idio_24_gpio_reg __iomem *reg;
	अचिन्हित दीर्घ irq_mask;
पूर्ण;

अटल पूर्णांक idio_24_gpio_get_direction(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	/* FET Outमाला_दो */
	अगर (offset < 24)
		वापस GPIO_LINE_सूचीECTION_OUT;

	/* Isolated Inमाला_दो */
	अगर (offset < 48)
		वापस GPIO_LINE_सूचीECTION_IN;

	/* TTL/CMOS I/O */
	/* OUT MODE = 1 when TTL/CMOS Output Mode is set */
	अगर (ioपढ़ो8(&idio24gpio->reg->ctl) & out_mode_mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक idio_24_gpio_direction_input(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ctl_state;
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	/* TTL/CMOS I/O */
	अगर (offset > 47) अणु
		raw_spin_lock_irqsave(&idio24gpio->lock, flags);

		/* Clear TTL/CMOS Output Mode */
		ctl_state = ioपढ़ो8(&idio24gpio->reg->ctl) & ~out_mode_mask;
		ioग_लिखो8(ctl_state, &idio24gpio->reg->ctl);

		raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idio_24_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ctl_state;
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	/* TTL/CMOS I/O */
	अगर (offset > 47) अणु
		raw_spin_lock_irqsave(&idio24gpio->lock, flags);

		/* Set TTL/CMOS Output Mode */
		ctl_state = ioपढ़ो8(&idio24gpio->reg->ctl) | out_mode_mask;
		ioग_लिखो8(ctl_state, &idio24gpio->reg->ctl);

		raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
	पूर्ण

	chip->set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक idio_24_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ offset_mask = BIT(offset % 8);
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	/* FET Outमाला_दो */
	अगर (offset < 8)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->out0_7) & offset_mask);

	अगर (offset < 16)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->out8_15) & offset_mask);

	अगर (offset < 24)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->out16_23) & offset_mask);

	/* Isolated Inमाला_दो */
	अगर (offset < 32)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->in0_7) & offset_mask);

	अगर (offset < 40)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->in8_15) & offset_mask);

	अगर (offset < 48)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->in16_23) & offset_mask);

	/* TTL/CMOS Outमाला_दो */
	अगर (ioपढ़ो8(&idio24gpio->reg->ctl) & out_mode_mask)
		वापस !!(ioपढ़ो8(&idio24gpio->reg->ttl_out0_7) & offset_mask);

	/* TTL/CMOS Inमाला_दो */
	वापस !!(ioपढ़ो8(&idio24gpio->reg->ttl_in0_7) & offset_mask);
पूर्ण

अटल पूर्णांक idio_24_gpio_get_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	व्योम __iomem *ports[] = अणु
		&idio24gpio->reg->out0_7, &idio24gpio->reg->out8_15,
		&idio24gpio->reg->out16_23, &idio24gpio->reg->in0_7,
		&idio24gpio->reg->in8_15, &idio24gpio->reg->in16_23,
	पूर्ण;
	माप_प्रकार index;
	अचिन्हित दीर्घ port_state;
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	/* clear bits array to a clean slate */
	biपंचांगap_zero(bits, chip->ngpio);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		index = offset / 8;

		/* पढ़ो bits from current gpio port (port 6 is TTL GPIO) */
		अगर (index < 6)
			port_state = ioपढ़ो8(ports[index]);
		अन्यथा अगर (ioपढ़ो8(&idio24gpio->reg->ctl) & out_mode_mask)
			port_state = ioपढ़ो8(&idio24gpio->reg->ttl_out0_7);
		अन्यथा
			port_state = ioपढ़ो8(&idio24gpio->reg->ttl_in0_7);

		port_state &= gpio_mask;

		biपंचांगap_set_value8(bits, port_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idio_24_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
	पूर्णांक value)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);
	व्योम __iomem *base;
	स्थिर अचिन्हित पूर्णांक mask = BIT(offset % 8);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक out_state;

	/* Isolated Inमाला_दो */
	अगर (offset > 23 && offset < 48)
		वापस;

	/* TTL/CMOS Inमाला_दो */
	अगर (offset > 47 && !(ioपढ़ो8(&idio24gpio->reg->ctl) & out_mode_mask))
		वापस;

	/* TTL/CMOS Outमाला_दो */
	अगर (offset > 47)
		base = &idio24gpio->reg->ttl_out0_7;
	/* FET Outमाला_दो */
	अन्यथा अगर (offset > 15)
		base = &idio24gpio->reg->out16_23;
	अन्यथा अगर (offset > 7)
		base = &idio24gpio->reg->out8_15;
	अन्यथा
		base = &idio24gpio->reg->out0_7;

	raw_spin_lock_irqsave(&idio24gpio->lock, flags);

	अगर (value)
		out_state = ioपढ़ो8(base) | mask;
	अन्यथा
		out_state = ioपढ़ो8(base) & ~mask;

	ioग_लिखो8(out_state, base);

	raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
पूर्ण

अटल व्योम idio_24_gpio_set_multiple(काष्ठा gpio_chip *chip,
	अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	व्योम __iomem *ports[] = अणु
		&idio24gpio->reg->out0_7, &idio24gpio->reg->out8_15,
		&idio24gpio->reg->out16_23
	पूर्ण;
	माप_प्रकार index;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ out_state;
	स्थिर अचिन्हित दीर्घ out_mode_mask = BIT(1);

	क्रम_each_set_clump8(offset, gpio_mask, mask, ARRAY_SIZE(ports) * 8) अणु
		index = offset / 8;

		biपंचांगask = biपंचांगap_get_value8(bits, offset) & gpio_mask;

		raw_spin_lock_irqsave(&idio24gpio->lock, flags);

		/* पढ़ो bits from current gpio port (port 6 is TTL GPIO) */
		अगर (index < 6) अणु
			out_state = ioपढ़ो8(ports[index]);
		पूर्ण अन्यथा अगर (ioपढ़ो8(&idio24gpio->reg->ctl) & out_mode_mask) अणु
			out_state = ioपढ़ो8(&idio24gpio->reg->ttl_out0_7);
		पूर्ण अन्यथा अणु
			/* skip TTL GPIO अगर set क्रम input */
			raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
			जारी;
		पूर्ण

		/* set requested bit states */
		out_state &= ~gpio_mask;
		out_state |= biपंचांगask;

		/* ग_लिखो bits क्रम current gpio port (port 6 is TTL GPIO) */
		अगर (index < 6)
			ioग_लिखो8(out_state, ports[index]);
		अन्यथा
			ioग_लिखो8(out_state, &idio24gpio->reg->ttl_out0_7);

		raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम idio_24_irq_ack(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम idio_24_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *स्थिर chip = irq_data_get_irq_chip_data(data);
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	स्थिर अचिन्हित दीर्घ bit_offset = irqd_to_hwirq(data) - 24;
	अचिन्हित अक्षर new_irq_mask;
	स्थिर अचिन्हित दीर्घ bank_offset = bit_offset / 8;
	अचिन्हित अक्षर cos_enable_state;

	raw_spin_lock_irqsave(&idio24gpio->lock, flags);

	idio24gpio->irq_mask &= ~BIT(bit_offset);
	new_irq_mask = idio24gpio->irq_mask >> bank_offset * 8;

	अगर (!new_irq_mask) अणु
		cos_enable_state = ioपढ़ो8(&idio24gpio->reg->cos_enable);

		/* Disable Rising Edge detection */
		cos_enable_state &= ~BIT(bank_offset);
		/* Disable Falling Edge detection */
		cos_enable_state &= ~BIT(bank_offset + 4);

		ioग_लिखो8(cos_enable_state, &idio24gpio->reg->cos_enable);
	पूर्ण

	raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
पूर्ण

अटल व्योम idio_24_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *स्थिर chip = irq_data_get_irq_chip_data(data);
	काष्ठा idio_24_gpio *स्थिर idio24gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर prev_irq_mask;
	स्थिर अचिन्हित दीर्घ bit_offset = irqd_to_hwirq(data) - 24;
	स्थिर अचिन्हित दीर्घ bank_offset = bit_offset / 8;
	अचिन्हित अक्षर cos_enable_state;

	raw_spin_lock_irqsave(&idio24gpio->lock, flags);

	prev_irq_mask = idio24gpio->irq_mask >> bank_offset * 8;
	idio24gpio->irq_mask |= BIT(bit_offset);

	अगर (!prev_irq_mask) अणु
		cos_enable_state = ioपढ़ो8(&idio24gpio->reg->cos_enable);

		/* Enable Rising Edge detection */
		cos_enable_state |= BIT(bank_offset);
		/* Enable Falling Edge detection */
		cos_enable_state |= BIT(bank_offset + 4);

		ioग_लिखो8(cos_enable_state, &idio24gpio->reg->cos_enable);
	पूर्ण

	raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
पूर्ण

अटल पूर्णांक idio_24_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	/* The only valid irq types are none and both-edges */
	अगर (flow_type != IRQ_TYPE_NONE &&
		(flow_type & IRQ_TYPE_EDGE_BOTH) != IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip idio_24_irqchip = अणु
	.name = "pcie-idio-24",
	.irq_ack = idio_24_irq_ack,
	.irq_mask = idio_24_irq_mask,
	.irq_unmask = idio_24_irq_unmask,
	.irq_set_type = idio_24_irq_set_type
पूर्ण;

अटल irqवापस_t idio_24_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idio_24_gpio *स्थिर idio24gpio = dev_id;
	अचिन्हित दीर्घ irq_status;
	काष्ठा gpio_chip *स्थिर chip = &idio24gpio->chip;
	अचिन्हित दीर्घ irq_mask;
	पूर्णांक gpio;

	raw_spin_lock(&idio24gpio->lock);

	/* Read Change-Of-State status */
	irq_status = ioपढ़ो32(&idio24gpio->reg->cos0_7);

	raw_spin_unlock(&idio24gpio->lock);

	/* Make sure our device generated IRQ */
	अगर (!irq_status)
		वापस IRQ_NONE;

	/* Handle only unmasked IRQ */
	irq_mask = idio24gpio->irq_mask & irq_status;

	क्रम_each_set_bit(gpio, &irq_mask, chip->ngpio - 24)
		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य,
			gpio + 24));

	raw_spin_lock(&idio24gpio->lock);

	/* Clear Change-Of-State status */
	ioग_लिखो32(irq_status, &idio24gpio->reg->cos0_7);

	raw_spin_unlock(&idio24gpio->lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा IDIO_24_NGPIO 56
अटल स्थिर अक्षर *idio_24_names[IDIO_24_NGPIO] = अणु
	"OUT0", "OUT1", "OUT2", "OUT3", "OUT4", "OUT5", "OUT6", "OUT7",
	"OUT8", "OUT9", "OUT10", "OUT11", "OUT12", "OUT13", "OUT14", "OUT15",
	"OUT16", "OUT17", "OUT18", "OUT19", "OUT20", "OUT21", "OUT22", "OUT23",
	"IIN0", "IIN1", "IIN2", "IIN3", "IIN4", "IIN5", "IIN6", "IIN7",
	"IIN8", "IIN9", "IIN10", "IIN11", "IIN12", "IIN13", "IIN14", "IIN15",
	"IIN16", "IIN17", "IIN18", "IIN19", "IIN20", "IIN21", "IIN22", "IIN23",
	"TTL0", "TTL1", "TTL2", "TTL3", "TTL4", "TTL5", "TTL6", "TTL7"
पूर्ण;

अटल पूर्णांक idio_24_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *स्थिर dev = &pdev->dev;
	काष्ठा idio_24_gpio *idio24gpio;
	पूर्णांक err;
	स्थिर माप_प्रकार pci_plx_bar_index = 1;
	स्थिर माप_प्रकार pci_bar_index = 2;
	स्थिर अक्षर *स्थिर name = pci_name(pdev);
	काष्ठा gpio_irq_chip *girq;

	idio24gpio = devm_kzalloc(dev, माप(*idio24gpio), GFP_KERNEL);
	अगर (!idio24gpio)
		वापस -ENOMEM;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device (%d)\n", err);
		वापस err;
	पूर्ण

	err = pcim_iomap_regions(pdev, BIT(pci_plx_bar_index) | BIT(pci_bar_index), name);
	अगर (err) अणु
		dev_err(dev, "Unable to map PCI I/O addresses (%d)\n", err);
		वापस err;
	पूर्ण

	idio24gpio->plx = pcim_iomap_table(pdev)[pci_plx_bar_index];
	idio24gpio->reg = pcim_iomap_table(pdev)[pci_bar_index];

	idio24gpio->chip.label = name;
	idio24gpio->chip.parent = dev;
	idio24gpio->chip.owner = THIS_MODULE;
	idio24gpio->chip.base = -1;
	idio24gpio->chip.ngpio = IDIO_24_NGPIO;
	idio24gpio->chip.names = idio_24_names;
	idio24gpio->chip.get_direction = idio_24_gpio_get_direction;
	idio24gpio->chip.direction_input = idio_24_gpio_direction_input;
	idio24gpio->chip.direction_output = idio_24_gpio_direction_output;
	idio24gpio->chip.get = idio_24_gpio_get;
	idio24gpio->chip.get_multiple = idio_24_gpio_get_multiple;
	idio24gpio->chip.set = idio_24_gpio_set;
	idio24gpio->chip.set_multiple = idio_24_gpio_set_multiple;

	girq = &idio24gpio->chip.irq;
	girq->chip = &idio_24_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	raw_spin_lock_init(&idio24gpio->lock);

	/* Software board reset */
	ioग_लिखो8(0, &idio24gpio->reg->soft_reset);
	/*
	 * enable PLX PEX8311 पूर्णांकernal PCI wire पूर्णांकerrupt and local पूर्णांकerrupt
	 * input
	 */
	ioग_लिखो8((INTCSR_INTERNAL_PCI_WIRE | INTCSR_LOCAL_INPUT) >> 8,
		 idio24gpio->plx + PLX_PEX8311_PCI_LCS_INTCSR + 1);

	err = devm_gpiochip_add_data(dev, &idio24gpio->chip, idio24gpio);
	अगर (err) अणु
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(dev, pdev->irq, idio_24_irq_handler, IRQF_SHARED,
		name, idio24gpio);
	अगर (err) अणु
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id idio_24_pci_dev_id[] = अणु
	अणु PCI_DEVICE(0x494F, 0x0FD0) पूर्ण, अणु PCI_DEVICE(0x494F, 0x0BD0) पूर्ण,
	अणु PCI_DEVICE(0x494F, 0x07D0) पूर्ण, अणु PCI_DEVICE(0x494F, 0x0FC0) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, idio_24_pci_dev_id);

अटल काष्ठा pci_driver idio_24_driver = अणु
	.name = "pcie-idio-24",
	.id_table = idio_24_pci_dev_id,
	.probe = idio_24_probe
पूर्ण;

module_pci_driver(idio_24_driver);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES PCIe-IDIO-24 GPIO driver");
MODULE_LICENSE("GPL v2");
