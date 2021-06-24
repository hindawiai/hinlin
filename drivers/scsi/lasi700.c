<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* PARISC LASI driver क्रम the 53c700 chip
 *
 * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com
**-----------------------------------------------------------------------------
**  
**
**-----------------------------------------------------------------------------
 */

/*
 * Many thanks to Riअक्षरd Hirst <rhirst@linuxcare.com> क्रम patiently
 * debugging this driver on the parisc architecture and suggesting
 * many improvements and bug fixes.
 *
 * Thanks also go to Linuxcare Inc. क्रम providing several PARISC
 * machines क्रम me to debug the driver on.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/delay.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

MODULE_AUTHOR("James Bottomley");
MODULE_DESCRIPTION("lasi700 SCSI Driver");
MODULE_LICENSE("GPL");

#घोषणा LASI_700_SVERSION 0x00071
#घोषणा LASI_710_SVERSION 0x00082

#घोषणा LASI700_ID_TABLE अणु			\
	.hw_type	= HPHW_FIO,		\
	.sversion	= LASI_700_SVERSION,	\
	.hversion	= HVERSION_ANY_ID,	\
	.hversion_rev	= HVERSION_REV_ANY_ID,	\
पूर्ण

#घोषणा LASI710_ID_TABLE अणु			\
	.hw_type	= HPHW_FIO,		\
	.sversion	= LASI_710_SVERSION,	\
	.hversion	= HVERSION_ANY_ID,	\
	.hversion_rev	= HVERSION_REV_ANY_ID,	\
पूर्ण

#घोषणा LASI700_CLOCK	25
#घोषणा LASI710_CLOCK	40
#घोषणा LASI_SCSI_CORE_OFFSET 0x100

अटल स्थिर काष्ठा parisc_device_id lasi700_ids[] __initस्थिर = अणु
	LASI700_ID_TABLE,
	LASI710_ID_TABLE,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा lasi700_ढाँचा = अणु
	.name		= "LASI SCSI 53c700",
	.proc_name	= "lasi700",
	.this_id	= 7,
	.module		= THIS_MODULE,
पूर्ण;
MODULE_DEVICE_TABLE(parisc, lasi700_ids);

अटल पूर्णांक __init
lasi700_probe(काष्ठा parisc_device *dev)
अणु
	अचिन्हित दीर्घ base = dev->hpa.start + LASI_SCSI_CORE_OFFSET;
	काष्ठा NCR_700_Host_Parameters *hostdata;
	काष्ठा Scsi_Host *host;

	hostdata = kzalloc(माप(*hostdata), GFP_KERNEL);
	अगर (!hostdata) अणु
		dev_prपूर्णांकk(KERN_ERR, &dev->dev, "Failed to allocate host data\n");
		वापस -ENOMEM;
	पूर्ण

	hostdata->dev = &dev->dev;
	dma_set_mask(&dev->dev, DMA_BIT_MASK(32));
	hostdata->base = ioremap(base, 0x100);
	hostdata->dअगरferential = 0;

	अगर (dev->id.sversion == LASI_700_SVERSION) अणु
		hostdata->घड़ी = LASI700_CLOCK;
		hostdata->क्रमce_le_on_be = 1;
	पूर्ण अन्यथा अणु
		hostdata->घड़ी = LASI710_CLOCK;
		hostdata->क्रमce_le_on_be = 0;
		hostdata->chip710 = 1;
		hostdata->dmode_extra = DMODE_FC2;
		hostdata->burst_length = 8;
	पूर्ण

	host = NCR_700_detect(&lasi700_ढाँचा, hostdata, &dev->dev);
	अगर (!host)
		जाओ out_kमुक्त;
	host->this_id = 7;
	host->base = base;
	host->irq = dev->irq;
	अगर(request_irq(dev->irq, NCR_700_पूर्णांकr, IRQF_SHARED, "lasi700", host)) अणु
		prपूर्णांकk(KERN_ERR "lasi700: request_irq failed!\n");
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

अटल पूर्णांक __निकास
lasi700_driver_हटाओ(काष्ठा parisc_device *dev)
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

अटल काष्ठा parisc_driver lasi700_driver __refdata = अणु
	.name =		"lasi_scsi",
	.id_table =	lasi700_ids,
	.probe =	lasi700_probe,
	.हटाओ =	__निकास_p(lasi700_driver_हटाओ),
पूर्ण;

अटल पूर्णांक __init
lasi700_init(व्योम)
अणु
	वापस रेजिस्टर_parisc_driver(&lasi700_driver);
पूर्ण

अटल व्योम __निकास
lasi700_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&lasi700_driver);
पूर्ण

module_init(lasi700_init);
module_निकास(lasi700_निकास);
