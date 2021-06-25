<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_pci236.c
 * Driver क्रम Amplicon PCI236 DIO boards.
 *
 * Copyright (C) 2002-2014 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */
/*
 * Driver: amplc_pci236
 * Description: Amplicon PCI236
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PCI236 (amplc_pci236)
 * Updated: Fri, 25 Jul 2014 15:32:40 +0000
 * Status: works
 *
 * Configuration options:
 *   none
 *
 * Manual configuration of PCI board (PCI236) is not supported; it is
 * configured स्वतःmatically.
 *
 * The PCI236 board has a single 8255 appearing as subdevice 0.
 *
 * Subdevice 1 pretends to be a digital input device, but it always
 * वापसs 0 when पढ़ो. However, अगर you run a command with
 * scan_begin_src=TRIG_EXT, a rising edge on port C bit 3 acts as an
 * बाह्यal trigger, which can be used to wake up tasks.  This is like
 * the comedi_parport device.  If no पूर्णांकerrupt is connected, then
 * subdevice 1 is unused.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "amplc_pc236.h"
#समावेश "plx9052.h"

/* Disable, and clear, पूर्णांकerrupts */
#घोषणा PCI236_INTR_DISABLE	(PLX9052_INTCSR_LI1POL |	\
				 PLX9052_INTCSR_LI2POL |	\
				 PLX9052_INTCSR_LI1SEL |	\
				 PLX9052_INTCSR_LI1CLRINT)

/* Enable, and clear, पूर्णांकerrupts */
#घोषणा PCI236_INTR_ENABLE	(PLX9052_INTCSR_LI1ENAB |	\
				 PLX9052_INTCSR_LI1POL |	\
				 PLX9052_INTCSR_LI2POL |	\
				 PLX9052_INTCSR_PCIENAB |	\
				 PLX9052_INTCSR_LI1SEL |	\
				 PLX9052_INTCSR_LI1CLRINT)

अटल व्योम pci236_पूर्णांकr_update_cb(काष्ठा comedi_device *dev, bool enable)
अणु
	काष्ठा pc236_निजी *devpriv = dev->निजी;

	/* this will also clear the "local interrupt 1" latch */
	outl(enable ? PCI236_INTR_ENABLE : PCI236_INTR_DISABLE,
	     devpriv->lcr_iobase + PLX9052_INTCSR);
पूर्ण

अटल bool pci236_पूर्णांकr_chk_clr_cb(काष्ठा comedi_device *dev)
अणु
	काष्ठा pc236_निजी *devpriv = dev->निजी;

	/* check अगर पूर्णांकerrupt occurred */
	अगर (!(inl(devpriv->lcr_iobase + PLX9052_INTCSR) &
	      PLX9052_INTCSR_LI1STAT))
		वापस false;
	/* clear the पूर्णांकerrupt */
	pci236_पूर्णांकr_update_cb(dev, devpriv->enable_irq);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा pc236_board pc236_pci_board = अणु
	.name = "pci236",
	.पूर्णांकr_update_cb = pci236_पूर्णांकr_update_cb,
	.पूर्णांकr_chk_clr_cb = pci236_पूर्णांकr_chk_clr_cb,
पूर्ण;

अटल पूर्णांक pci236_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pci_dev = comedi_to_pci_dev(dev);
	काष्ठा pc236_निजी *devpriv;
	अचिन्हित दीर्घ iobase;
	पूर्णांक ret;

	dev_info(dev->class_dev, "amplc_pci236: attach pci %s\n",
		 pci_name(pci_dev));

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	dev->board_ptr = &pc236_pci_board;
	dev->board_name = pc236_pci_board.name;
	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv->lcr_iobase = pci_resource_start(pci_dev, 1);
	iobase = pci_resource_start(pci_dev, 2);
	वापस amplc_pc236_common_attach(dev, iobase, pci_dev->irq,
					 IRQF_SHARED);
पूर्ण

अटल काष्ठा comedi_driver amplc_pci236_driver = अणु
	.driver_name = "amplc_pci236",
	.module = THIS_MODULE,
	.स्वतः_attach = pci236_स्वतः_attach,
	.detach = comedi_pci_detach,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci236_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMPLICON, 0x0009) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci236_pci_table);

अटल पूर्णांक amplc_pci236_pci_probe(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &amplc_pci236_driver,
				      id->driver_data);
पूर्ण

अटल काष्ठा pci_driver amplc_pci236_pci_driver = अणु
	.name		= "amplc_pci236",
	.id_table	= pci236_pci_table,
	.probe		= &amplc_pci236_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;

module_comedi_pci_driver(amplc_pci236_driver, amplc_pci236_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PCI236 DIO boards");
MODULE_LICENSE("GPL");
