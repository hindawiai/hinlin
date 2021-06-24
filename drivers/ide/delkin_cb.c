<शैली गुरु>
/*
 *  Created 20 Oct 2004 by Mark Lord
 *
 *  Basic support क्रम Delkin/ASKA/Workbit Cardbus CompactFlash adapter
 *
 *  Modeled after the 16-bit PCMCIA driver: ide-cs.c
 *
 *  This is slightly peculiar, in that it is a PCI driver,
 *  but is NOT an IDE PCI driver -- the IDE layer करोes not directly
 *  support hot insertion/removal of PCI पूर्णांकerfaces, so this driver
 *  is unable to use the IDE PCI पूर्णांकerfaces.  Instead, it uses the
 *  same पूर्णांकerfaces as the ide-cs (PCMCIA) driver uses.
 *  On the plus side, the driver is also smaller/simpler this way.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/पन.स>

/*
 * No chip करोcumentation has yet been found,
 * so these configuration values were pulled from
 * a running Win98 प्रणाली using "debug".
 * This gives around 3MByte/second पढ़ो perक्रमmance,
 * which is about 2/3 of what the chip is capable of.
 *
 * There is also a 4KByte mmio region on the card,
 * but its purpose has yet to be reverse-engineered.
 */
अटल स्थिर u8 setup[] = अणु
	0x00, 0x05, 0xbe, 0x01, 0x20, 0x8f, 0x00, 0x00,
	0xa4, 0x1f, 0xb3, 0x1b, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xa4, 0x83, 0x02, 0x13,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops delkin_cb_port_ops = अणु
	.quirkproc		= ide_undecoded_slave,
पूर्ण;

अटल पूर्णांक delkin_cb_init_chipset(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ base = pci_resource_start(dev, 0);
	पूर्णांक i;

	outb(0x02, base + 0x1e);	/* set nIEN to block पूर्णांकerrupts */
	inb(base + 0x17);		/* पढ़ो status to clear पूर्णांकerrupts */

	क्रम (i = 0; i < माप(setup); ++i) अणु
		अगर (setup[i])
			outb(setup[i], base + i);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_info delkin_cb_port_info = अणु
	.port_ops		= &delkin_cb_port_ops,
	.host_flags		= IDE_HFLAG_IO_32BIT | IDE_HFLAG_UNMASK_IRQS |
				  IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.init_chipset		= delkin_cb_init_chipset,
	.chipset		= ide_pci,
पूर्ण;

अटल पूर्णांक delkin_cb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_host *host;
	अचिन्हित दीर्घ base;
	पूर्णांक rc;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;

	rc = pci_enable_device(dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "delkin_cb: pci_enable_device failed (%d)\n", rc);
		वापस rc;
	पूर्ण
	rc = pci_request_regions(dev, "delkin_cb");
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "delkin_cb: pci_request_regions failed (%d)\n", rc);
		pci_disable_device(dev);
		वापस rc;
	पूर्ण
	base = pci_resource_start(dev, 0);

	delkin_cb_init_chipset(dev);

	स_रखो(&hw, 0, माप(hw));
	ide_std_init_ports(&hw, base + 0x10, base + 0x1e);
	hw.irq = dev->irq;
	hw.dev = &dev->dev;

	rc = ide_host_add(&delkin_cb_port_info, hws, 1, &host);
	अगर (rc)
		जाओ out_disable;

	pci_set_drvdata(dev, host);

	वापस 0;

out_disable:
	pci_release_regions(dev);
	pci_disable_device(dev);
	वापस rc;
पूर्ण

अटल व्योम
delkin_cb_हटाओ (काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);

	ide_host_हटाओ(host);

	pci_release_regions(dev);
	pci_disable_device(dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक delkin_cb_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_घातer_state(dev, pci_choose_state(dev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक delkin_cb_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	पूर्णांक rc;

	pci_set_घातer_state(dev, PCI_D0);

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	pci_restore_state(dev);
	pci_set_master(dev);

	अगर (host->init_chipset)
		host->init_chipset(dev);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा delkin_cb_suspend शून्य
#घोषणा delkin_cb_resume शून्य
#पूर्ण_अगर

अटल काष्ठा pci_device_id delkin_cb_pci_tbl[] = अणु
	अणु 0x1145, 0xf021, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु 0x1145, 0xf024, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, delkin_cb_pci_tbl);

अटल काष्ठा pci_driver delkin_cb_pci_driver = अणु
	.name		= "Delkin-ASKA-Workbit Cardbus IDE",
	.id_table	= delkin_cb_pci_tbl,
	.probe		= delkin_cb_probe,
	.हटाओ		= delkin_cb_हटाओ,
	.suspend	= delkin_cb_suspend,
	.resume		= delkin_cb_resume,
पूर्ण;

module_pci_driver(delkin_cb_pci_driver);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("Basic support for Delkin/ASKA/Workbit Cardbus IDE");
MODULE_LICENSE("GPL");

