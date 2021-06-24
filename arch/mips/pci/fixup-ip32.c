<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>
/*
 * O2 has up to 5 PCI devices connected पूर्णांकo the MACE bridge.  The device
 * map looks like this:
 *
 * 0  aic7xxx 0
 * 1  aic7xxx 1
 * 2  expansion slot
 * 3  N/C
 * 4  N/C
 */

#घोषणा SCSI0  MACEPCI_SCSI0_IRQ
#घोषणा SCSI1  MACEPCI_SCSI1_IRQ
#घोषणा INTA0  MACEPCI_SLOT0_IRQ
#घोषणा INTA1  MACEPCI_SLOT1_IRQ
#घोषणा INTA2  MACEPCI_SLOT2_IRQ
#घोषणा INTB   MACEPCI_SHARED0_IRQ
#घोषणा INTC   MACEPCI_SHARED1_IRQ
#घोषणा INTD   MACEPCI_SHARED2_IRQ
अटल अक्षर irq_tab_mace[][5] = अणु
      /* Dummy	INT#A  INT#B  INT#C  INT#D */
	अणु0,	    0,	   0,	  0,	 0पूर्ण, /* This is placeholder row - never used */
	अणु0,	SCSI0, SCSI0, SCSI0, SCSI0पूर्ण,
	अणु0,	SCSI1, SCSI1, SCSI1, SCSI1पूर्ण,
	अणु0,	INTA0,	INTB,  INTC,  INTDपूर्ण,
	अणु0,	INTA1,	INTC,  INTD,  INTBपूर्ण,
	अणु0,	INTA2,	INTD,  INTB,  INTCपूर्ण,
पूर्ण;


/*
 * Given a PCI slot number (a la PCI_SLOT(...)) and the पूर्णांकerrupt pin of
 * the device (1-4 => A-D), tell what irq to use.  Note that we करोn't
 * in theory have slots 4 and 5, and we never normally use the shared
 * irqs.  I suppose a device without a pin A will thank us क्रम करोing it
 * right अगर there exists such a broken piece of crap.
 */
पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस irq_tab_mace[slot][pin];
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
