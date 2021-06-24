<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Birger Koblitz <mail@birger-koblitz.de>
 * Copyright (C) 2020 Bert Vermeulen <bert@biot.com>
 * Copyright (C) 2020 John Crispin <john@phrozen.org>
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_address.h>
#समावेश <linux/irqchip/chained_irq.h>

/* Global Interrupt Mask Register */
#घोषणा RTL_ICTL_GIMR		0x00
/* Global Interrupt Status Register */
#घोषणा RTL_ICTL_GISR		0x04
/* Interrupt Routing Registers */
#घोषणा RTL_ICTL_IRR0		0x08
#घोषणा RTL_ICTL_IRR1		0x0c
#घोषणा RTL_ICTL_IRR2		0x10
#घोषणा RTL_ICTL_IRR3		0x14

#घोषणा REG(x)		(realtek_ictl_base + x)

अटल DEFINE_RAW_SPINLOCK(irq_lock);
अटल व्योम __iomem *realtek_ictl_base;

अटल व्योम realtek_ictl_unmask_irq(काष्ठा irq_data *i)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&irq_lock, flags);

	value = पढ़ोl(REG(RTL_ICTL_GIMR));
	value |= BIT(i->hwirq);
	ग_लिखोl(value, REG(RTL_ICTL_GIMR));

	raw_spin_unlock_irqrestore(&irq_lock, flags);
पूर्ण

अटल व्योम realtek_ictl_mask_irq(काष्ठा irq_data *i)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&irq_lock, flags);

	value = पढ़ोl(REG(RTL_ICTL_GIMR));
	value &= ~BIT(i->hwirq);
	ग_लिखोl(value, REG(RTL_ICTL_GIMR));

	raw_spin_unlock_irqrestore(&irq_lock, flags);
पूर्ण

अटल काष्ठा irq_chip realtek_ictl_irq = अणु
	.name = "realtek-rtl-intc",
	.irq_mask = realtek_ictl_mask_irq,
	.irq_unmask = realtek_ictl_unmask_irq,
पूर्ण;

अटल पूर्णांक पूर्णांकc_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(hw, &realtek_ictl_irq, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_करोमुख्य_ops = अणु
	.map = पूर्णांकc_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम realtek_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक pending;

	chained_irq_enter(chip, desc);
	pending = पढ़ोl(REG(RTL_ICTL_GIMR)) & पढ़ोl(REG(RTL_ICTL_GISR));
	अगर (unlikely(!pending)) अणु
		spurious_पूर्णांकerrupt();
		जाओ out;
	पूर्ण
	करोमुख्य = irq_desc_get_handler_data(desc);
	generic_handle_irq(irq_find_mapping(करोमुख्य, __ffs(pending)));

out:
	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * SoC पूर्णांकerrupts are cascaded to MIPS CPU पूर्णांकerrupts according to the
 * पूर्णांकerrupt-map in the device tree. Each SoC पूर्णांकerrupt माला_लो 4 bits क्रम
 * the CPU पूर्णांकerrupt in an Interrupt Routing Register. Max 32 SoC पूर्णांकerrupts
 * thus go पूर्णांकo 4 IRRs.
 */
अटल पूर्णांक __init map_पूर्णांकerrupts(काष्ठा device_node *node, काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_node *cpu_ictl;
	स्थिर __be32 *imap;
	u32 imaplen, soc_पूर्णांक, cpu_पूर्णांक, पंचांगp, regs[4];
	पूर्णांक ret, i, irr_regs[] = अणु
		RTL_ICTL_IRR3,
		RTL_ICTL_IRR2,
		RTL_ICTL_IRR1,
		RTL_ICTL_IRR0,
	पूर्ण;
	u8 mips_irqs_set;

	ret = of_property_पढ़ो_u32(node, "#address-cells", &पंचांगp);
	अगर (ret || पंचांगp)
		वापस -EINVAL;

	imap = of_get_property(node, "interrupt-map", &imaplen);
	अगर (!imap || imaplen % 3)
		वापस -EINVAL;

	mips_irqs_set = 0;
	स_रखो(regs, 0, माप(regs));
	क्रम (i = 0; i < imaplen; i += 3 * माप(u32)) अणु
		soc_पूर्णांक = be32_to_cpup(imap);
		अगर (soc_पूर्णांक > 31)
			वापस -EINVAL;

		cpu_ictl = of_find_node_by_phandle(be32_to_cpup(imap + 1));
		अगर (!cpu_ictl)
			वापस -EINVAL;
		ret = of_property_पढ़ो_u32(cpu_ictl, "#interrupt-cells", &पंचांगp);
		अगर (ret || पंचांगp != 1)
			वापस -EINVAL;
		of_node_put(cpu_ictl);

		cpu_पूर्णांक = be32_to_cpup(imap + 2);
		अगर (cpu_पूर्णांक > 7)
			वापस -EINVAL;

		अगर (!(mips_irqs_set & BIT(cpu_पूर्णांक))) अणु
			irq_set_chained_handler_and_data(cpu_पूर्णांक, realtek_irq_dispatch,
							 करोमुख्य);
			mips_irqs_set |= BIT(cpu_पूर्णांक);
		पूर्ण

		regs[(soc_पूर्णांक * 4) / 32] |= cpu_पूर्णांक << (soc_पूर्णांक * 4) % 32;
		imap += 3;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		ग_लिखोl(regs[i], REG(irr_regs[i]));

	वापस 0;
पूर्ण

अटल पूर्णांक __init realtek_rtl_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक ret;

	realtek_ictl_base = of_iomap(node, 0);
	अगर (!realtek_ictl_base)
		वापस -ENXIO;

	/* Disable all cascaded पूर्णांकerrupts */
	ग_लिखोl(0, REG(RTL_ICTL_GIMR));

	करोमुख्य = irq_करोमुख्य_add_simple(node, 32, 0,
				       &irq_करोमुख्य_ops, शून्य);

	ret = map_पूर्णांकerrupts(node, करोमुख्य);
	अगर (ret) अणु
		pr_err("invalid interrupt map\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(realtek_rtl_पूर्णांकc, "realtek,rtl-intc", realtek_rtl_of_init);
