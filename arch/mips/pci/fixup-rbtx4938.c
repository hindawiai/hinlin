<शैली गुरु>
/*
 * Toshiba rbtx4938 pci routines
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#समावेश <linux/types.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/rbtx4938.h>

पूर्णांक rbtx4938_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = tx4938_pcic1_map_irq(dev, slot);

	अगर (irq >= 0)
		वापस irq;
	irq = pin;
	/* IRQ rotation */
	irq--;	/* 0-3 */
	अगर (slot == TX4927_PCIC_IDSEL_AD_TO_SLOT(23)) अणु
		/* PCI CardSlot (IDSEL=A23) */
		/* PCIA => PCIA (IDSEL=A23) */
		irq = (irq + 0 + slot) % 4;
	पूर्ण अन्यथा अणु
		/* PCI Backplane */
		अगर (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		अन्यथा
			irq = (irq + 3 + slot) % 4;
	पूर्ण
	irq++;	/* 1-4 */

	चयन (irq) अणु
	हाल 1:
		irq = RBTX4938_IRQ_IOC_PCIA;
		अवरोध;
	हाल 2:
		irq = RBTX4938_IRQ_IOC_PCIB;
		अवरोध;
	हाल 3:
		irq = RBTX4938_IRQ_IOC_PCIC;
		अवरोध;
	हाल 4:
		irq = RBTX4938_IRQ_IOC_PCID;
		अवरोध;
	पूर्ण
	वापस irq;
पूर्ण
