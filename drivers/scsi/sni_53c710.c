<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* SNI RM driver
 *
 * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com
**-----------------------------------------------------------------------------
**
**
**-----------------------------------------------------------------------------
 */

/*
 * Based on lasi700.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/sched.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/delay.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

MODULE_AUTHOR("Thomas Bogendथघrfer");
MODULE_DESCRIPTION("SNI RM 53c710 SCSI Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:snirm_53c710");

#घोषणा SNIRM710_CLOCK	32

अटल काष्ठा scsi_host_ढाँचा snirm710_ढाँचा = अणु
	.name		= "SNI RM SCSI 53c710",
	.proc_name	= "snirm_53c710",
	.this_id	= 7,
	.module		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक snirm710_probe(काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित दीर्घ base;
	काष्ठा NCR_700_Host_Parameters *hostdata;
	काष्ठा Scsi_Host *host;
	काष्ठा  resource *res;
	पूर्णांक rc;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	base = res->start;
	hostdata = kzalloc(माप(*hostdata), GFP_KERNEL);
	अगर (!hostdata)
		वापस -ENOMEM;

	hostdata->dev = &dev->dev;
	dma_set_mask(&dev->dev, DMA_BIT_MASK(32));
	hostdata->base = ioremap(base, 0x100);
	hostdata->dअगरferential = 0;

	hostdata->घड़ी = SNIRM710_CLOCK;
	hostdata->क्रमce_le_on_be = 1;
	hostdata->chip710 = 1;
	hostdata->burst_length = 4;

	host = NCR_700_detect(&snirm710_ढाँचा, hostdata, &dev->dev);
	अगर (!host)
		जाओ out_kमुक्त;
	host->this_id = 7;
	host->base = base;
	host->irq = rc = platक्रमm_get_irq(dev, 0);
	अगर (rc < 0)
		जाओ out_put_host;
	अगर(request_irq(host->irq, NCR_700_पूर्णांकr, IRQF_SHARED, "snirm710", host)) अणु
		prपूर्णांकk(KERN_ERR "snirm710: request_irq failed!\n");
		जाओ out_put_host;
	पूर्ण

	dev_set_drvdata(&dev->dev, host);
	scsi_scan_host(host);

	वापस 0;

 out_put_host:
	scsi_host_put(host);
 out_kमुक्त:
	iounmap(hostdata->base);
	kमुक्त(hostdata);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snirm710_driver_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(&dev->dev);
	काष्ठा NCR_700_Host_Parameters *hostdata =
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

	scsi_हटाओ_host(host);
	NCR_700_release(host);
	मुक्त_irq(host->irq, host);
	iounmap(hostdata->base);
	kमुक्त(hostdata);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snirm710_driver = अणु
	.probe	= snirm710_probe,
	.हटाओ	= snirm710_driver_हटाओ,
	.driver	= अणु
		.name	= "snirm_53c710",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snirm710_driver);
