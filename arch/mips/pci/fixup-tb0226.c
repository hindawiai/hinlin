<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fixup-tb0226.c, The TANBAC TB0226 specअगरic PCI fixups.
 *
 *  Copyright (C) 2002-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/vr41xx/giu.h>
#समावेश <यंत्र/vr41xx/tb0226.h>

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = -1;

	चयन (slot) अणु
	हाल 12:
		vr41xx_set_irq_trigger(GD82559_1_PIN,
				       IRQ_TRIGGER_LEVEL,
				       IRQ_SIGNAL_THROUGH);
		vr41xx_set_irq_level(GD82559_1_PIN, IRQ_LEVEL_LOW);
		irq = GD82559_1_IRQ;
		अवरोध;
	हाल 13:
		vr41xx_set_irq_trigger(GD82559_2_PIN,
				       IRQ_TRIGGER_LEVEL,
				       IRQ_SIGNAL_THROUGH);
		vr41xx_set_irq_level(GD82559_2_PIN, IRQ_LEVEL_LOW);
		irq = GD82559_2_IRQ;
		अवरोध;
	हाल 14:
		चयन (pin) अणु
		हाल 1:
			vr41xx_set_irq_trigger(UPD720100_INTA_PIN,
					       IRQ_TRIGGER_LEVEL,
					       IRQ_SIGNAL_THROUGH);
			vr41xx_set_irq_level(UPD720100_INTA_PIN,
					     IRQ_LEVEL_LOW);
			irq = UPD720100_INTA_IRQ;
			अवरोध;
		हाल 2:
			vr41xx_set_irq_trigger(UPD720100_INTB_PIN,
					       IRQ_TRIGGER_LEVEL,
					       IRQ_SIGNAL_THROUGH);
			vr41xx_set_irq_level(UPD720100_INTB_PIN,
					     IRQ_LEVEL_LOW);
			irq = UPD720100_INTB_IRQ;
			अवरोध;
		हाल 3:
			vr41xx_set_irq_trigger(UPD720100_INTC_PIN,
					       IRQ_TRIGGER_LEVEL,
					       IRQ_SIGNAL_THROUGH);
			vr41xx_set_irq_level(UPD720100_INTC_PIN,
					     IRQ_LEVEL_LOW);
			irq = UPD720100_INTC_IRQ;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस irq;
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
