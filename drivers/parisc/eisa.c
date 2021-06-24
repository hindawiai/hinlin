<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eisa.c - provide support क्रम EISA adapters in PA-RISC machines
 *
 * Copyright (c) 2001 Matthew Wilcox क्रम Hewlett Packard
 * Copyright (c) 2001 Daniel Engstrom <5116@telia.com>
 *
 * There are two distinct EISA adapters.  Mongoose is found in machines
 * beक्रमe the 712; then the Wax ASIC is used.  To complicate matters, the
 * Wax ASIC also includes a PS/2 and RS-232 controller, but those are
 * dealt with अन्यथाwhere; this file is concerned only with the EISA portions
 * of Wax.
 *
 * HINT:
 * -----
 * To allow an ISA card to work properly in the EISA slot you need to
 * set an edge trigger level. This may be करोne on the palo command line
 * by adding the kernel parameter "eisa_irq_edge=n,n2,[...]]", with
 * n and n2 as the irq levels you want to use.
 *
 * Example: "eisa_irq_edge=10,11" allows ISA cards to operate at
 * irq levels 10 and 11.
 */

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/eisa.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/eisa_bus.h>
#समावेश <यंत्र/eisa_eeprom.h>

#समावेश "iommu.h"

#अगर 0
#घोषणा EISA_DBG(msg, arg...) prपूर्णांकk(KERN_DEBUG "eisa: " msg, ## arg)
#अन्यथा
#घोषणा EISA_DBG(msg, arg...)
#पूर्ण_अगर

#घोषणा SNAKES_EEPROM_BASE_ADDR 0xF0810400
#घोषणा MIRAGE_EEPROM_BASE_ADDR 0xF00C0400

अटल DEFINE_SPINLOCK(eisa_irq_lock);

व्योम __iomem *eisa_eeprom_addr __पढ़ो_mostly;

/* We can only have one EISA adapter in the प्रणाली because neither
 * implementation can be flexed.
 */
अटल काष्ठा eisa_ba अणु
	काष्ठा pci_hba_data	hba;
	अचिन्हित दीर्घ eeprom_addr;
	काष्ठा eisa_root_device root;
पूर्ण eisa_dev;

/* Port ops */

अटल अंतरभूत अचिन्हित दीर्घ eisa_permute(अचिन्हित लघु port)
अणु
	अगर (port & 0x300) अणु
		वापस 0xfc000000 | ((port & 0xfc00) >> 6)
			| ((port & 0x3f8) << 9) | (port & 7);
	पूर्ण अन्यथा अणु
		वापस 0xfc000000 | port;
	पूर्ण
पूर्ण

अचिन्हित अक्षर eisa_in8(अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		वापस gsc_पढ़ोb(eisa_permute(port));
	वापस 0xff;
पूर्ण

अचिन्हित लघु eisa_in16(अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		वापस le16_to_cpu(gsc_पढ़ोw(eisa_permute(port)));
	वापस 0xffff;
पूर्ण

अचिन्हित पूर्णांक eisa_in32(अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		वापस le32_to_cpu(gsc_पढ़ोl(eisa_permute(port)));
	वापस 0xffffffff;
पूर्ण

व्योम eisa_out8(अचिन्हित अक्षर data, अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		gsc_ग_लिखोb(data, eisa_permute(port));
पूर्ण

व्योम eisa_out16(अचिन्हित लघु data, अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		gsc_ग_लिखोw(cpu_to_le16(data), eisa_permute(port));
पूर्ण

व्योम eisa_out32(अचिन्हित पूर्णांक data, अचिन्हित लघु port)
अणु
	अगर (EISA_bus)
		gsc_ग_लिखोl(cpu_to_le32(data), eisa_permute(port));
पूर्ण

#अगर_अघोषित CONFIG_PCI
/* We call these directly without PCI.  See यंत्र/पन.स. */
EXPORT_SYMBOL(eisa_in8);
EXPORT_SYMBOL(eisa_in16);
EXPORT_SYMBOL(eisa_in32);
EXPORT_SYMBOL(eisa_out8);
EXPORT_SYMBOL(eisa_out16);
EXPORT_SYMBOL(eisa_out32);
#पूर्ण_अगर

/* Interrupt handling */

/* cached पूर्णांकerrupt mask रेजिस्टरs */
अटल पूर्णांक master_mask;
अटल पूर्णांक slave_mask;

/* the trig level can be set with the
 * eisa_irq_edge=n,n,n commandline parameter
 * We should really पढ़ो this from the EEPROM
 * in the furure.
 */
/* irq 13,8,2,1,0 must be edge */
अटल अचिन्हित पूर्णांक eisa_irq_level __पढ़ो_mostly; /* शेष to edge triggered */


/* called by मुक्त irq */
अटल व्योम eisa_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	अचिन्हित दीर्घ flags;

	EISA_DBG("disable irq %d\n", irq);
	/* just mask क्रम now */
	spin_lock_irqsave(&eisa_irq_lock, flags);
        अगर (irq & 8) अणु
		slave_mask |= (1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
	पूर्ण अन्यथा अणु
		master_mask |= (1 << (irq&7));
		eisa_out8(master_mask, 0x21);
	पूर्ण
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
पूर्ण

/* called by request irq */
अटल व्योम eisa_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	अचिन्हित दीर्घ flags;
	EISA_DBG("enable irq %d\n", irq);

	spin_lock_irqsave(&eisa_irq_lock, flags);
        अगर (irq & 8) अणु
		slave_mask &= ~(1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
	पूर्ण अन्यथा अणु
		master_mask &= ~(1 << (irq&7));
		eisa_out8(master_mask, 0x21);
	पूर्ण
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
पूर्ण

अटल काष्ठा irq_chip eisa_पूर्णांकerrupt_type = अणु
	.name		=	"EISA",
	.irq_unmask	=	eisa_unmask_irq,
	.irq_mask	=	eisa_mask_irq,
पूर्ण;

अटल irqवापस_t eisa_irq(पूर्णांक wax_irq, व्योम *पूर्णांकr_dev)
अणु
	पूर्णांक irq = gsc_पढ़ोb(0xfc01f000); /* EISA supports 16 irqs */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&eisa_irq_lock, flags);
	/* पढ़ो IRR command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);

	EISA_DBG("irq IAR %02x 8259-1 irr %02x 8259-2 irr %02x\n",
		   irq, eisa_in8(0x20), eisa_in8(0xa0));

	/* पढ़ो ISR command */
	eisa_out8(0x0a, 0x20);
	eisa_out8(0x0a, 0xa0);
	EISA_DBG("irq 8259-1 isr %02x imr %02x 8259-2 isr %02x imr %02x\n",
		 eisa_in8(0x20), eisa_in8(0x21), eisa_in8(0xa0), eisa_in8(0xa1));

	irq &= 0xf;

	/* mask irq and ग_लिखो eoi */
	अगर (irq & 8) अणु
		slave_mask |= (1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
		eisa_out8(0x60 | (irq&7),0xa0);/* 'Specific EOI' to slave */
		eisa_out8(0x62, 0x20);	/* 'Specific EOI' to master-IRQ2 */

	पूर्ण अन्यथा अणु
		master_mask |= (1 << (irq&7));
		eisa_out8(master_mask, 0x21);
		eisa_out8(0x60|irq, 0x20);	/* 'Specific EOI' to master */
	पूर्ण
	spin_unlock_irqrestore(&eisa_irq_lock, flags);

	generic_handle_irq(irq);

	spin_lock_irqsave(&eisa_irq_lock, flags);
	/* unmask */
        अगर (irq & 8) अणु
		slave_mask &= ~(1 << (irq&7));
		eisa_out8(slave_mask, 0xa1);
	पूर्ण अन्यथा अणु
		master_mask &= ~(1 << (irq&7));
		eisa_out8(master_mask, 0x21);
	पूर्ण
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dummy_irq2_handler(पूर्णांक _, व्योम *dev)
अणु
	prपूर्णांकk(KERN_ALERT "eisa: uhh, irq2?\n");
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम init_eisa_pic(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&eisa_irq_lock, flags);

	eisa_out8(0xff, 0x21); /* mask during init */
	eisa_out8(0xff, 0xa1); /* mask during init */

	/* master pic */
	eisa_out8(0x11, 0x20); /* ICW1 */
	eisa_out8(0x00, 0x21); /* ICW2 */
	eisa_out8(0x04, 0x21); /* ICW3 */
	eisa_out8(0x01, 0x21); /* ICW4 */
	eisa_out8(0x40, 0x20); /* OCW2 */

	/* slave pic */
	eisa_out8(0x11, 0xa0); /* ICW1 */
	eisa_out8(0x08, 0xa1); /* ICW2 */
	eisa_out8(0x02, 0xa1); /* ICW3 */
	eisa_out8(0x01, 0xa1); /* ICW4 */
	eisa_out8(0x40, 0xa0); /* OCW2 */

	udelay(100);

	slave_mask = 0xff;
	master_mask = 0xfb;
	eisa_out8(slave_mask, 0xa1); /* OCW1 */
	eisa_out8(master_mask, 0x21); /* OCW1 */

	/* setup trig level */
	EISA_DBG("EISA edge/level %04x\n", eisa_irq_level);

	eisa_out8(eisa_irq_level&0xff, 0x4d0); /* Set all irq's to edge  */
	eisa_out8((eisa_irq_level >> 8) & 0xff, 0x4d1);

	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
	EISA_DBG("pic0 edge/level %02x\n", eisa_in8(0x4d0));
	EISA_DBG("pic1 edge/level %02x\n", eisa_in8(0x4d1));

	spin_unlock_irqrestore(&eisa_irq_lock, flags);
पूर्ण

/* Device initialisation */

#घोषणा is_mongoose(dev) (dev->id.sversion == 0x00076)

अटल पूर्णांक __init eisa_probe(काष्ठा parisc_device *dev)
अणु
	पूर्णांक i, result;

	अक्षर *name = is_mongoose(dev) ? "Mongoose" : "Wax";

	prपूर्णांकk(KERN_INFO "%s EISA Adapter found at 0x%08lx\n",
		name, (अचिन्हित दीर्घ)dev->hpa.start);

	eisa_dev.hba.dev = dev;
	eisa_dev.hba.iommu = ccio_get_iommu(dev);

	eisa_dev.hba.lmmio_space.name = "EISA";
	eisa_dev.hba.lmmio_space.start = F_EXTEND(0xfc000000);
	eisa_dev.hba.lmmio_space.end = F_EXTEND(0xffbfffff);
	eisa_dev.hba.lmmio_space.flags = IORESOURCE_MEM;
	result = ccio_request_resource(dev, &eisa_dev.hba.lmmio_space);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "EISA: failed to claim EISA Bus address space!\n");
		वापस result;
	पूर्ण
	eisa_dev.hba.io_space.name = "EISA";
	eisa_dev.hba.io_space.start = 0;
	eisa_dev.hba.io_space.end = 0xffff;
	eisa_dev.hba.lmmio_space.flags = IORESOURCE_IO;
	result = request_resource(&ioport_resource, &eisa_dev.hba.io_space);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "EISA: failed to claim EISA Bus port space!\n");
		वापस result;
	पूर्ण
	pcibios_रेजिस्टर_hba(&eisa_dev.hba);

	result = request_irq(dev->irq, eisa_irq, IRQF_SHARED, "EISA", &eisa_dev);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "EISA: request_irq failed!\n");
		जाओ error_release;
	पूर्ण

	/* Reserve IRQ2 */
	अगर (request_irq(2, dummy_irq2_handler, 0, "cascade", शून्य))
		pr_err("Failed to request irq 2 (cascade)\n");
	क्रम (i = 0; i < 16; i++) अणु
		irq_set_chip_and_handler(i, &eisa_पूर्णांकerrupt_type,
					 handle_simple_irq);
	पूर्ण

	EISA_bus = 1;

	अगर (dev->num_addrs) अणु
		/* newer firmware hand out the eeprom address */
		eisa_dev.eeprom_addr = dev->addr[0];
	पूर्ण अन्यथा अणु
		/* old firmware, need to figure out the box */
		अगर (is_mongoose(dev)) अणु
			eisa_dev.eeprom_addr = SNAKES_EEPROM_BASE_ADDR;
		पूर्ण अन्यथा अणु
			eisa_dev.eeprom_addr = MIRAGE_EEPROM_BASE_ADDR;
		पूर्ण
	पूर्ण
	eisa_eeprom_addr = ioremap(eisa_dev.eeprom_addr, HPEE_MAX_LENGTH);
	अगर (!eisa_eeprom_addr) अणु
		result = -ENOMEM;
		prपूर्णांकk(KERN_ERR "EISA: ioremap failed!\n");
		जाओ error_मुक्त_irq;
	पूर्ण
	result = eisa_क्रमागतerator(eisa_dev.eeprom_addr, &eisa_dev.hba.io_space,
			&eisa_dev.hba.lmmio_space);
	init_eisa_pic();

	अगर (result >= 0) अणु
		/* FIXME : Don't क्रमागतerate the bus twice. */
		eisa_dev.root.dev = &dev->dev;
		dev_set_drvdata(&dev->dev, &eisa_dev.root);
		eisa_dev.root.bus_base_addr = 0;
		eisa_dev.root.res = &eisa_dev.hba.io_space;
		eisa_dev.root.slots = result;
		eisa_dev.root.dma_mask = 0xffffffff; /* wild guess */
		अगर (eisa_root_रेजिस्टर (&eisa_dev.root)) अणु
			prपूर्णांकk(KERN_ERR "EISA: Failed to register EISA root\n");
			result = -ENOMEM;
			जाओ error_iounmap;
		पूर्ण
	पूर्ण

	वापस 0;

error_iounmap:
	iounmap(eisa_eeprom_addr);
error_मुक्त_irq:
	मुक्त_irq(dev->irq, &eisa_dev);
error_release:
	release_resource(&eisa_dev.hba.io_space);
	वापस result;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id eisa_tbl[] __initस्थिर = अणु
	अणु HPHW_BA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00076 पूर्ण, /* Mongoose */
	अणु HPHW_BA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00090 पूर्ण, /* Wax EISA */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, eisa_tbl);

अटल काष्ठा parisc_driver eisa_driver __refdata = अणु
	.name =		"eisa_ba",
	.id_table =	eisa_tbl,
	.probe =	eisa_probe,
पूर्ण;

व्योम __init eisa_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&eisa_driver);
पूर्ण


अटल अचिन्हित पूर्णांक eisa_irq_configured;
व्योम eisa_make_irq_level(पूर्णांक num)
अणु
	अगर (eisa_irq_configured& (1<<num)) अणु
		prपूर्णांकk(KERN_WARNING
		       "IRQ %d polarity configured twice (last to level)\n",
		       num);
	पूर्ण
	eisa_irq_level |= (1<<num); /* set the corresponding bit */
	eisa_irq_configured |= (1<<num); /* set the corresponding bit */
पूर्ण

व्योम eisa_make_irq_edge(पूर्णांक num)
अणु
	अगर (eisa_irq_configured& (1<<num)) अणु
		prपूर्णांकk(KERN_WARNING
		       "IRQ %d polarity configured twice (last to edge)\n",
		       num);
	पूर्ण
	eisa_irq_level &= ~(1<<num); /* clear the corresponding bit */
	eisa_irq_configured |= (1<<num); /* set the corresponding bit */
पूर्ण

अटल पूर्णांक __init eisa_irq_setup(अक्षर *str)
अणु
	अक्षर *cur = str;
	पूर्णांक val;

	EISA_DBG("IRQ setup\n");
	जबतक (cur != शून्य) अणु
		अक्षर *pe;

		val = (पूर्णांक) simple_म_से_अदीर्घ(cur, &pe, 0);
		अगर (val > 15 || val < 0) अणु
			prपूर्णांकk(KERN_ERR "eisa: EISA irq value are 0-15\n");
			जारी;
		पूर्ण
		अगर (val == 2) अणु
			val = 9;
		पूर्ण
		eisa_make_irq_edge(val); /* clear the corresponding bit */
		EISA_DBG("setting IRQ %d to edge-triggered mode\n", val);

		अगर ((cur = म_अक्षर(cur, ','))) अणु
			cur++;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("eisa_irq_edge=", eisa_irq_setup);

