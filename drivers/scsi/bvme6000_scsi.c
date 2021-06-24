<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Detection routine क्रम the NCR53c710 based BVME6000 SCSI Controllers क्रम Linux.
 *
 * Based on work by Alan Hourihane and Kars de Jong
 *
 * Rewritten to use 53c700.c by Riअक्षरd Hirst <riअक्षरd@sleepie.demon.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/bvme6000hw.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

MODULE_AUTHOR("Richard Hirst <richard@sleepie.demon.co.uk>");
MODULE_DESCRIPTION("BVME6000 NCR53C710 driver");
MODULE_LICENSE("GPL");

अटल काष्ठा scsi_host_ढाँचा bvme6000_scsi_driver_ढाँचा = अणु
	.name			= "BVME6000 NCR53c710 SCSI",
	.proc_name		= "BVME6000",
	.this_id		= 7,
	.module			= THIS_MODULE,
पूर्ण;

अटल काष्ठा platक्रमm_device *bvme6000_scsi_device;

अटल पूर्णांक
bvme6000_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा NCR_700_Host_Parameters *hostdata;

	अगर (!MACH_IS_BVME6000)
		जाओ out;

	hostdata = kzalloc(माप(काष्ठा NCR_700_Host_Parameters), GFP_KERNEL);
	अगर (!hostdata) अणु
		prपूर्णांकk(KERN_ERR "bvme6000-scsi: "
				"Failed to allocate host data\n");
		जाओ out;
	पूर्ण

	/* Fill in the required pieces of hostdata */
	hostdata->base = (व्योम __iomem *)BVME_NCR53C710_BASE;
	hostdata->घड़ी = 40;	/* XXX - depends on the CPU घड़ी! */
	hostdata->chip710 = 1;
	hostdata->dmode_extra = DMODE_FC2;
	hostdata->dcntl_extra = EA_710;
	hostdata->ctest7_extra = CTEST7_TT1;

	/* and रेजिस्टर the chip */
	host = NCR_700_detect(&bvme6000_scsi_driver_ढाँचा, hostdata,
			      &dev->dev);
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR "bvme6000-scsi: No host detected; "
				"board configuration problem?\n");
		जाओ out_मुक्त;
	पूर्ण
	host->base = BVME_NCR53C710_BASE;
	host->this_id = 7;
	host->irq = BVME_IRQ_SCSI;
	अगर (request_irq(BVME_IRQ_SCSI, NCR_700_पूर्णांकr, 0, "bvme6000-scsi",
			host)) अणु
		prपूर्णांकk(KERN_ERR "bvme6000-scsi: request_irq failed\n");
		जाओ out_put_host;
	पूर्ण

	platक्रमm_set_drvdata(dev, host);
	scsi_scan_host(host);

	वापस 0;

 out_put_host:
	scsi_host_put(host);
 out_मुक्त:
	kमुक्त(hostdata);
 out:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
bvme6000_device_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा Scsi_Host *host = platक्रमm_get_drvdata(dev);
	काष्ठा NCR_700_Host_Parameters *hostdata = shost_priv(host);

	scsi_हटाओ_host(host);
	NCR_700_release(host);
	kमुक्त(hostdata);
	मुक्त_irq(host->irq, host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bvme6000_scsi_driver = अणु
	.driver = अणु
		.name		= "bvme6000-scsi",
	पूर्ण,
	.probe		= bvme6000_probe,
	.हटाओ		= bvme6000_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init bvme6000_scsi_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&bvme6000_scsi_driver);
	अगर (err)
		वापस err;

	bvme6000_scsi_device = platक्रमm_device_रेजिस्टर_simple("bvme6000-scsi",
							       -1, शून्य, 0);
	अगर (IS_ERR(bvme6000_scsi_device)) अणु
		platक्रमm_driver_unरेजिस्टर(&bvme6000_scsi_driver);
		वापस PTR_ERR(bvme6000_scsi_device);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास bvme6000_scsi_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(bvme6000_scsi_device);
	platक्रमm_driver_unरेजिस्टर(&bvme6000_scsi_driver);
पूर्ण

module_init(bvme6000_scsi_init);
module_निकास(bvme6000_scsi_निकास);
