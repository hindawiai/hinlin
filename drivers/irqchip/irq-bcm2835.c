<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2010 Broadcom
 * Copyright 2012 Simon Arlott, Chris Boot, Stephen Warren
 *
 * Quirk 1: Shortcut पूर्णांकerrupts करोn't set the bank 1/2 रेजिस्टर pending bits
 *
 * If an पूर्णांकerrupt fires on bank 1 that isn't in the लघुcuts list, bit 8
 * on bank 0 is set to signअगरy that an पूर्णांकerrupt in bank 1 has fired, and
 * to look in the bank 1 status रेजिस्टर क्रम more inक्रमmation.
 *
 * If an पूर्णांकerrupt fires on bank 1 that _is_ in the लघुcuts list, its
 * लघुcut bit in bank 0 is set as well as its पूर्णांकerrupt bit in the bank 1
 * status रेजिस्टर, but bank 0 bit 8 is _not_ set.
 *
 * Quirk 2: You can't mask the रेजिस्टर 1/2 pending पूर्णांकerrupts
 *
 * In a proper cascaded पूर्णांकerrupt controller, the पूर्णांकerrupt lines with
 * cascaded पूर्णांकerrupt controllers on them are just normal पूर्णांकerrupt lines.
 * You can mask the पूर्णांकerrupts and get on with things. With this controller
 * you can't करो that.
 *
 * Quirk 3: The लघुcut पूर्णांकerrupts can't be (un)masked in bank 0
 *
 * Those पूर्णांकerrupts that have लघुcuts can only be masked/unmasked in
 * their respective banks' enable/disable रेजिस्टरs. Doing so in the bank 0
 * enable/disable रेजिस्टरs has no effect.
 *
 * The FIQ control रेजिस्टर:
 *  Bits 0-6: IRQ (index in order of पूर्णांकerrupts from banks 1, 2, then 0)
 *  Bit    7: Enable FIQ generation
 *  Bits  8+: Unused
 *
 * An पूर्णांकerrupt must be disabled beक्रमe configuring it क्रम FIQ generation
 * otherwise both handlers will fire at the same समय!
 */

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/exception.h>

/* Put the bank and irq (32 bits) पूर्णांकo the hwirq */
#घोषणा MAKE_HWIRQ(b, n)	((b << 5) | (n))
#घोषणा HWIRQ_BANK(i)		(i >> 5)
#घोषणा HWIRQ_BIT(i)		BIT(i & 0x1f)

#घोषणा NR_IRQS_BANK0		8
#घोषणा BANK0_HWIRQ_MASK	0xff
/* Shortcuts can't be disabled so any unknown new ones need to be masked */
#घोषणा SHORTCUT1_MASK		0x00007c00
#घोषणा SHORTCUT2_MASK		0x001f8000
#घोषणा SHORTCUT_SHIFT		10
#घोषणा BANK1_HWIRQ		BIT(8)
#घोषणा BANK2_HWIRQ		BIT(9)
#घोषणा BANK0_VALID_MASK	(BANK0_HWIRQ_MASK | BANK1_HWIRQ | BANK2_HWIRQ \
					| SHORTCUT1_MASK | SHORTCUT2_MASK)

#घोषणा REG_FIQ_CONTROL		0x0c
#घोषणा FIQ_CONTROL_ENABLE	BIT(7)

#घोषणा NR_BANKS		3
#घोषणा IRQS_PER_BANK		32

अटल स्थिर पूर्णांक reg_pending[] __initस्थिर = अणु 0x00, 0x04, 0x08 पूर्ण;
अटल स्थिर पूर्णांक reg_enable[] __initस्थिर = अणु 0x18, 0x10, 0x14 पूर्ण;
अटल स्थिर पूर्णांक reg_disable[] __initस्थिर = अणु 0x24, 0x1c, 0x20 पूर्ण;
अटल स्थिर पूर्णांक bank_irqs[] __initस्थिर = अणु 8, 32, 32 पूर्ण;

अटल स्थिर पूर्णांक लघुcuts[] = अणु
	7, 9, 10, 18, 19,		/* Bank 1 */
	21, 22, 23, 24, 25, 30		/* Bank 2 */
पूर्ण;

काष्ठा armctrl_ic अणु
	व्योम __iomem *base;
	व्योम __iomem *pending[NR_BANKS];
	व्योम __iomem *enable[NR_BANKS];
	व्योम __iomem *disable[NR_BANKS];
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

अटल काष्ठा armctrl_ic पूर्णांकc __पढ़ो_mostly;
अटल व्योम __exception_irq_entry bcm2835_handle_irq(
	काष्ठा pt_regs *regs);
अटल व्योम bcm2836_chained_handle_irq(काष्ठा irq_desc *desc);

अटल व्योम armctrl_mask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl_relaxed(HWIRQ_BIT(d->hwirq), पूर्णांकc.disable[HWIRQ_BANK(d->hwirq)]);
पूर्ण

अटल व्योम armctrl_unmask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl_relaxed(HWIRQ_BIT(d->hwirq), पूर्णांकc.enable[HWIRQ_BANK(d->hwirq)]);
पूर्ण

अटल काष्ठा irq_chip armctrl_chip = अणु
	.name = "ARMCTRL-level",
	.irq_mask = armctrl_mask_irq,
	.irq_unmask = armctrl_unmask_irq
पूर्ण;

अटल पूर्णांक armctrl_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
	स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
	अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize != 2))
		वापस -EINVAL;

	अगर (WARN_ON(पूर्णांकspec[0] >= NR_BANKS))
		वापस -EINVAL;

	अगर (WARN_ON(पूर्णांकspec[1] >= IRQS_PER_BANK))
		वापस -EINVAL;

	अगर (WARN_ON(पूर्णांकspec[0] == 0 && पूर्णांकspec[1] >= NR_IRQS_BANK0))
		वापस -EINVAL;

	*out_hwirq = MAKE_HWIRQ(पूर्णांकspec[0], पूर्णांकspec[1]);
	*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops armctrl_ops = अणु
	.xlate = armctrl_xlate
पूर्ण;

अटल पूर्णांक __init armctrl_of_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent,
				  bool is_2836)
अणु
	व्योम __iomem *base;
	पूर्णांक irq, b, i;
	u32 reg;

	base = of_iomap(node, 0);
	अगर (!base)
		panic("%pOF: unable to map IC registers\n", node);

	पूर्णांकc.करोमुख्य = irq_करोमुख्य_add_linear(node, MAKE_HWIRQ(NR_BANKS, 0),
			&armctrl_ops, शून्य);
	अगर (!पूर्णांकc.करोमुख्य)
		panic("%pOF: unable to create IRQ domain\n", node);

	क्रम (b = 0; b < NR_BANKS; b++) अणु
		पूर्णांकc.pending[b] = base + reg_pending[b];
		पूर्णांकc.enable[b] = base + reg_enable[b];
		पूर्णांकc.disable[b] = base + reg_disable[b];

		क्रम (i = 0; i < bank_irqs[b]; i++) अणु
			irq = irq_create_mapping(पूर्णांकc.करोमुख्य, MAKE_HWIRQ(b, i));
			BUG_ON(irq <= 0);
			irq_set_chip_and_handler(irq, &armctrl_chip,
				handle_level_irq);
			irq_set_probe(irq);
		पूर्ण

		reg = पढ़ोl_relaxed(पूर्णांकc.enable[b]);
		अगर (reg) अणु
			ग_लिखोl_relaxed(reg, पूर्णांकc.disable[b]);
			pr_err(FW_BUG "Bootloader left irq enabled: "
			       "bank %d irq %*pbl\n", b, IRQS_PER_BANK, &reg);
		पूर्ण
	पूर्ण

	reg = पढ़ोl_relaxed(base + REG_FIQ_CONTROL);
	अगर (reg & FIQ_CONTROL_ENABLE) अणु
		ग_लिखोl_relaxed(0, base + REG_FIQ_CONTROL);
		pr_err(FW_BUG "Bootloader left fiq enabled\n");
	पूर्ण

	अगर (is_2836) अणु
		पूर्णांक parent_irq = irq_of_parse_and_map(node, 0);

		अगर (!parent_irq) अणु
			panic("%pOF: unable to get parent interrupt.\n",
			      node);
		पूर्ण
		irq_set_chained_handler(parent_irq, bcm2836_chained_handle_irq);
	पूर्ण अन्यथा अणु
		set_handle_irq(bcm2835_handle_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init bcm2835_armctrl_of_init(काष्ठा device_node *node,
					  काष्ठा device_node *parent)
अणु
	वापस armctrl_of_init(node, parent, false);
पूर्ण

अटल पूर्णांक __init bcm2836_armctrl_of_init(काष्ठा device_node *node,
					  काष्ठा device_node *parent)
अणु
	वापस armctrl_of_init(node, parent, true);
पूर्ण


/*
 * Handle each पूर्णांकerrupt across the entire पूर्णांकerrupt controller.  This पढ़ोs the
 * status रेजिस्टर beक्रमe handling each पूर्णांकerrupt, which is necessary given that
 * handle_IRQ may briefly re-enable पूर्णांकerrupts क्रम soft IRQ handling.
 */

अटल u32 armctrl_translate_bank(पूर्णांक bank)
अणु
	u32 stat = पढ़ोl_relaxed(पूर्णांकc.pending[bank]);

	वापस MAKE_HWIRQ(bank, ffs(stat) - 1);
पूर्ण

अटल u32 armctrl_translate_लघुcut(पूर्णांक bank, u32 stat)
अणु
	वापस MAKE_HWIRQ(bank, लघुcuts[ffs(stat >> SHORTCUT_SHIFT) - 1]);
पूर्ण

अटल u32 get_next_armctrl_hwirq(व्योम)
अणु
	u32 stat = पढ़ोl_relaxed(पूर्णांकc.pending[0]) & BANK0_VALID_MASK;

	अगर (stat == 0)
		वापस ~0;
	अन्यथा अगर (stat & BANK0_HWIRQ_MASK)
		वापस MAKE_HWIRQ(0, ffs(stat & BANK0_HWIRQ_MASK) - 1);
	अन्यथा अगर (stat & SHORTCUT1_MASK)
		वापस armctrl_translate_लघुcut(1, stat & SHORTCUT1_MASK);
	अन्यथा अगर (stat & SHORTCUT2_MASK)
		वापस armctrl_translate_लघुcut(2, stat & SHORTCUT2_MASK);
	अन्यथा अगर (stat & BANK1_HWIRQ)
		वापस armctrl_translate_bank(1);
	अन्यथा अगर (stat & BANK2_HWIRQ)
		वापस armctrl_translate_bank(2);
	अन्यथा
		BUG();
पूर्ण

अटल व्योम __exception_irq_entry bcm2835_handle_irq(
	काष्ठा pt_regs *regs)
अणु
	u32 hwirq;

	जबतक ((hwirq = get_next_armctrl_hwirq()) != ~0)
		handle_करोमुख्य_irq(पूर्णांकc.करोमुख्य, hwirq, regs);
पूर्ण

अटल व्योम bcm2836_chained_handle_irq(काष्ठा irq_desc *desc)
अणु
	u32 hwirq;

	जबतक ((hwirq = get_next_armctrl_hwirq()) != ~0)
		generic_handle_irq(irq_linear_revmap(पूर्णांकc.करोमुख्य, hwirq));
पूर्ण

IRQCHIP_DECLARE(bcm2835_armctrl_ic, "brcm,bcm2835-armctrl-ic",
		bcm2835_armctrl_of_init);
IRQCHIP_DECLARE(bcm2836_armctrl_ic, "brcm,bcm2836-armctrl-ic",
		bcm2836_armctrl_of_init);
