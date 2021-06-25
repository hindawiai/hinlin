<शैली गुरु>
/*
 *  Amiga Gayle IDE Driver
 *
 *     Created 9 Jul 1997 by Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/zorro.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigayle.h>


    /*
     *  Offsets from one of the above bases
     */

#घोषणा GAYLE_CONTROL	0x101a

    /*
     *  These are at dअगरferent offsets from the base
     */

#घोषणा GAYLE_IRQ_4000	0xdd3020	/* MSB = 1, Harddisk is source of */
#घोषणा GAYLE_IRQ_1200	0xda9000	/* पूर्णांकerrupt */


    /*
     *  Offset of the secondary port क्रम IDE द्विगुनrs
     *  Note that GAYLE_CONTROL is NOT available then!
     */

#घोषणा GAYLE_NEXT_PORT	0x1000

#घोषणा GAYLE_NUM_HWIFS		2
#घोषणा GAYLE_NUM_PROBE_HWIFS	(ide_द्विगुनr ? GAYLE_NUM_HWIFS : \
					       GAYLE_NUM_HWIFS-1)
#घोषणा GAYLE_HAS_CONTROL_REG	(!ide_द्विगुनr)

अटल bool ide_द्विगुनr;
module_param_named(द्विगुनr, ide_द्विगुनr, bool, 0);
MODULE_PARM_DESC(द्विगुनr, "enable support for IDE doublers");

    /*
     *  Check and acknowledge the पूर्णांकerrupt status
     */

अटल पूर्णांक gayle_test_irq(ide_hwअगर_t *hwअगर)
अणु
	अचिन्हित अक्षर ch;

	ch = z_पढ़ोb(hwअगर->io_ports.irq_addr);
	अगर (!(ch & GAYLE_IRQ_IDE))
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम gayle_a1200_clear_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	(व्योम)z_पढ़ोb(hwअगर->io_ports.status_addr);
	z_ग_लिखोb(0x7c, hwअगर->io_ports.irq_addr);
पूर्ण

अटल व्योम __init gayle_setup_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base,
				     अचिन्हित दीर्घ ctl, अचिन्हित दीर्घ irq_port)
अणु
	पूर्णांक i;

	स_रखो(hw, 0, माप(*hw));

	hw->io_ports.data_addr = base;

	क्रम (i = 1; i < 8; i++)
		hw->io_ports_array[i] = base + 2 + i * 4;

	hw->io_ports.ctl_addr = ctl;
	hw->io_ports.irq_addr = irq_port;

	hw->irq = IRQ_AMIGA_PORTS;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops gayle_a4000_port_ops = अणु
	.test_irq		= gayle_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops gayle_a1200_port_ops = अणु
	.clear_irq		= gayle_a1200_clear_irq,
	.test_irq		= gayle_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info gayle_port_info = अणु
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_SERIALIZE |
				  IDE_HFLAG_NO_DMA,
	.irq_flags		= IRQF_SHARED,
	.chipset		= ide_generic,
पूर्ण;

    /*
     *  Probe क्रम a Gayle IDE पूर्णांकerface (and optionally क्रम an IDE द्विगुनr)
     */

अटल पूर्णांक __init amiga_gayle_ide_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा gayle_ide_platक्रमm_data *pdata;
	अचिन्हित दीर्घ base, ctrlport, irqport;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;
	काष्ठा ide_hw hw[GAYLE_NUM_HWIFS], *hws[GAYLE_NUM_HWIFS];
	काष्ठा ide_port_info d = gayle_port_info;
	काष्ठा ide_host *host;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!request_mem_region(res->start, resource_size(res), "IDE"))
		वापस -EBUSY;

	pdata = dev_get_platdata(&pdev->dev);
	pr_info("ide: Gayle IDE controller (A%u style%s)\n",
		pdata->explicit_ack ? 1200 : 4000,
		ide_द्विगुनr ? ", IDE doubler" : "");

	base = (अचिन्हित दीर्घ)ZTWO_VADDR(pdata->base);
	ctrlport = 0;
	irqport = (अचिन्हित दीर्घ)ZTWO_VADDR(pdata->irqport);
	अगर (pdata->explicit_ack)
		d.port_ops = &gayle_a1200_port_ops;
	अन्यथा
		d.port_ops = &gayle_a4000_port_ops;

	क्रम (i = 0; i < GAYLE_NUM_PROBE_HWIFS; i++, base += GAYLE_NEXT_PORT) अणु
		अगर (GAYLE_HAS_CONTROL_REG)
			ctrlport = base + GAYLE_CONTROL;

		gayle_setup_ports(&hw[i], base, ctrlport, irqport);
		hws[i] = &hw[i];
	पूर्ण

	error = ide_host_add(&d, hws, i, &host);
	अगर (error)
		जाओ out;

	platक्रमm_set_drvdata(pdev, host);
	वापस 0;

out:
	release_mem_region(res->start, resource_size(res));
	वापस error;
पूर्ण

अटल पूर्णांक __निकास amiga_gayle_ide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	ide_host_हटाओ(host);
	release_mem_region(res->start, resource_size(res));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_gayle_ide_driver = अणु
	.हटाओ = __निकास_p(amiga_gayle_ide_हटाओ),
	.driver   = अणु
		.name	= "amiga-gayle-ide",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_gayle_ide_driver, amiga_gayle_ide_probe);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-gayle-ide");
