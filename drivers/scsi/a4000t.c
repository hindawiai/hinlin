<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Detection routine क्रम the NCR53c710 based Amiga SCSI Controllers क्रम Linux.
 *		Amiga Technologies A4000T SCSI controller.
 *
 * Written 1997 by Alan Hourihane <alanh@fairlite.demon.co.uk>
 * plus modअगरications of the 53c7xx.c driver to support the Amiga.
 *
 * Rewritten to use 53c700.c by Kars de Jong <jongk@linux-m68k.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"


अटल काष्ठा scsi_host_ढाँचा a4000t_scsi_driver_ढाँचा = अणु
	.name		= "A4000T builtin SCSI",
	.proc_name	= "A4000t",
	.this_id	= 7,
	.module		= THIS_MODULE,
पूर्ण;


#घोषणा A4000T_SCSI_OFFSET	0x40

अटल पूर्णांक __init amiga_a4000t_scsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	phys_addr_t scsi_addr;
	काष्ठा NCR_700_Host_Parameters *hostdata;
	काष्ठा Scsi_Host *host;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!request_mem_region(res->start, resource_size(res),
				"A4000T builtin SCSI"))
		वापस -EBUSY;

	hostdata = kzalloc(माप(काष्ठा NCR_700_Host_Parameters),
			   GFP_KERNEL);
	अगर (!hostdata) अणु
		dev_err(&pdev->dev, "Failed to allocate host data\n");
		जाओ out_release;
	पूर्ण

	scsi_addr = res->start + A4000T_SCSI_OFFSET;

	/* Fill in the required pieces of hostdata */
	hostdata->base = ZTWO_VADDR(scsi_addr);
	hostdata->घड़ी = 50;
	hostdata->chip710 = 1;
	hostdata->dmode_extra = DMODE_FC2;
	hostdata->dcntl_extra = EA_710;

	/* and रेजिस्टर the chip */
	host = NCR_700_detect(&a4000t_scsi_driver_ढाँचा, hostdata,
			      &pdev->dev);
	अगर (!host) अणु
		dev_err(&pdev->dev,
			"No host detected; board configuration problem?\n");
		जाओ out_मुक्त;
	पूर्ण

	host->this_id = 7;
	host->base = scsi_addr;
	host->irq = IRQ_AMIGA_PORTS;

	अगर (request_irq(host->irq, NCR_700_पूर्णांकr, IRQF_SHARED, "a4000t-scsi",
			host)) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ out_put_host;
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);
	scsi_scan_host(host);
	वापस 0;

 out_put_host:
	scsi_host_put(host);
 out_मुक्त:
	kमुक्त(hostdata);
 out_release:
	release_mem_region(res->start, resource_size(res));
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __निकास amiga_a4000t_scsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा NCR_700_Host_Parameters *hostdata = shost_priv(host);
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	scsi_हटाओ_host(host);
	NCR_700_release(host);
	kमुक्त(hostdata);
	मुक्त_irq(host->irq, host);
	release_mem_region(res->start, resource_size(res));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_a4000t_scsi_driver = अणु
	.हटाओ = __निकास_p(amiga_a4000t_scsi_हटाओ),
	.driver   = अणु
		.name	= "amiga-a4000t-scsi",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_a4000t_scsi_driver, amiga_a4000t_scsi_probe);

MODULE_AUTHOR("Alan Hourihane <alanh@fairlite.demon.co.uk> / "
	      "Kars de Jong <jongk@linux-m68k.org>");
MODULE_DESCRIPTION("Amiga A4000T NCR53C710 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-a4000t-scsi");
