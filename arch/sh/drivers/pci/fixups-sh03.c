<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/sh_पूर्णांकc.h>

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	अगर (dev->bus->number == 0) अणु
		चयन (slot) अणु
		हाल 4: वापस evt2irq(0x2a0);	/* eth0       */
		हाल 8: वापस evt2irq(0x2a0);	/* eth1       */
		हाल 6: वापस evt2irq(0x240);	/* PCI bridge */
		शेष:
			prपूर्णांकk(KERN_ERR "PCI: Bad IRQ mapping request "
					"for slot %d\n", slot);
			वापस evt2irq(0x240);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (pin) अणु
		हाल 0:   irq =  evt2irq(0x240); अवरोध;
		हाल 1:   irq =  evt2irq(0x240); अवरोध;
		हाल 2:   irq =  evt2irq(0x240); अवरोध;
		हाल 3:   irq =  evt2irq(0x240); अवरोध;
		हाल 4:   irq =  evt2irq(0x240); अवरोध;
		शेष:  irq = -1; अवरोध;
		पूर्ण
	पूर्ण
	वापस irq;
पूर्ण
