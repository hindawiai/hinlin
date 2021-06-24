<शैली गुरु>
/*
 *  Macपूर्णांकosh IDE Driver
 *
 *     Copyright (C) 1998 by Michael Schmitz
 *
 *  This driver was written based on inक्रमmation obtained from the MacOS IDE
 *  driver binary by Mikael Forselius
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/macपूर्णांकosh.h>

#घोषणा DRV_NAME "mac_ide"

#घोषणा IDE_BASE 0x50F1A000	/* Base address of IDE controller */

/*
 * Generic IDE रेजिस्टरs as offsets from the base
 * These match MkLinux so they should be correct.
 */

#घोषणा IDE_CONTROL	0x38	/* control/altstatus */

/*
 * Mac-specअगरic रेजिस्टरs
 */

/*
 * this रेजिस्टर is odd; it करोesn't seem to do much and it's
 * not word-aligned like भवly every other hardware रेजिस्टर
 * on the Mac...
 */

#घोषणा IDE_IFR		0x101	/* (0x101) IDE पूर्णांकerrupt flags on Quadra:
				 *
				 * Bit 0+1: some पूर्णांकerrupt flags
				 * Bit 2+3: some पूर्णांकerrupt enable
				 * Bit 4:   ??
				 * Bit 5:   IDE पूर्णांकerrupt flag (any hwअगर)
				 * Bit 6:   maybe IDE पूर्णांकerrupt enable (any hwअगर) ??
				 * Bit 7:   Any पूर्णांकerrupt condition
				 */

अस्थिर अचिन्हित अक्षर *ide_अगरr = (अचिन्हित अक्षर *) (IDE_BASE + IDE_IFR);

पूर्णांक macide_test_irq(ide_hwअगर_t *hwअगर)
अणु
	अगर (*ide_अगरr & 0x20)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम macide_clear_irq(ide_drive_t *drive)
अणु
	*ide_अगरr &= ~0x20;
पूर्ण

अटल व्योम __init macide_setup_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base,
				      पूर्णांक irq)
अणु
	पूर्णांक i;

	स_रखो(hw, 0, माप(*hw));

	क्रम (i = 0; i < 8; i++)
		hw->io_ports_array[i] = base + i * 4;

	hw->io_ports.ctl_addr = base + IDE_CONTROL;

	hw->irq = irq;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops macide_port_ops = अणु
	.clear_irq		= macide_clear_irq,
	.test_irq		= macide_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info macide_port_info = अणु
	.port_ops		= &macide_port_ops,
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_generic,
पूर्ण;

अटल स्थिर अक्षर *mac_ide_name[] =
	अणु "Quadra", "Powerbook", "Powerbook Baboon" पूर्ण;

/*
 * Probe क्रम a Macपूर्णांकosh IDE पूर्णांकerface
 */

अटल पूर्णांक mac_ide_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem, *irq;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	काष्ठा ide_port_info d = macide_port_info;
	काष्ठा ide_host *host;
	पूर्णांक rc;

	अगर (!MACH_IS_MAC)
		वापस -ENODEV;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -ENODEV;

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, mem->start,
				     resource_size(mem), DRV_NAME)) अणु
		dev_err(&pdev->dev, "resources busy\n");
		वापस -EBUSY;
	पूर्ण

	prपूर्णांकk(KERN_INFO "ide: Macintosh %s IDE controller\n",
			 mac_ide_name[macपूर्णांकosh_config->ide_type - 1]);

	macide_setup_ports(&hw, mem->start, irq->start);

	rc = ide_host_add(&d, hws, 1, &host);
	अगर (rc)
		वापस rc;

	platक्रमm_set_drvdata(pdev, host);
	वापस 0;
पूर्ण

अटल पूर्णांक mac_ide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(pdev);

	ide_host_हटाओ(host);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac_ide_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe  = mac_ide_probe,
	.हटाओ = mac_ide_हटाओ,
पूर्ण;

module_platक्रमm_driver(mac_ide_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_LICENSE("GPL");
