<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Detection routine क्रम the NCR53c710 based MVME16x SCSI Controllers क्रम Linux.
 *
 * Based on work by Alan Hourihane
 *
 * Rewritten to use 53c700.c by Kars de Jong <jongk@linux-m68k.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/mvme16xhw.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

MODULE_AUTHOR("Kars de Jong <jongk@linux-m68k.org>");
MODULE_DESCRIPTION("MVME16x NCR53C710 driver");
MODULE_LICENSE("GPL");

अटल काष्ठा scsi_host_ढाँचा mvme16x_scsi_driver_ढाँचा = अणु
	.name			= "MVME16x NCR53c710 SCSI",
	.proc_name		= "MVME16x",
	.this_id		= 7,
	.module			= THIS_MODULE,
पूर्ण;

अटल काष्ठा platक्रमm_device *mvme16x_scsi_device;

अटल पूर्णांक mvme16x_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा Scsi_Host * host = शून्य;
	काष्ठा NCR_700_Host_Parameters *hostdata;

	अगर (!MACH_IS_MVME16x)
		जाओ out;

	अगर (mvme16x_config & MVME16x_CONFIG_NO_SCSICHIP) अणु
		prपूर्णांकk(KERN_INFO "mvme16x-scsi: detection disabled, "
				 "SCSI chip not present\n");
		जाओ out;
	पूर्ण

	hostdata = kzalloc(माप(काष्ठा NCR_700_Host_Parameters), GFP_KERNEL);
	अगर (hostdata == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mvme16x-scsi: "
				"Failed to allocate host data\n");
		जाओ out;
	पूर्ण

	/* Fill in the required pieces of hostdata */
	hostdata->base = (व्योम __iomem *)0xfff47000UL;
	hostdata->घड़ी = 50;	/* XXX - depends on the CPU घड़ी! */
	hostdata->chip710 = 1;
	hostdata->dmode_extra = DMODE_FC2;
	hostdata->dcntl_extra = EA_710;
	hostdata->ctest7_extra = CTEST7_TT1;

	/* and रेजिस्टर the chip */
	host = NCR_700_detect(&mvme16x_scsi_driver_ढाँचा, hostdata,
			      &dev->dev);
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR "mvme16x-scsi: No host detected; "
				"board configuration problem?\n");
		जाओ out_मुक्त;
	पूर्ण
	host->this_id = 7;
	host->base = 0xfff47000UL;
	host->irq = MVME16x_IRQ_SCSI;
	अगर (request_irq(host->irq, NCR_700_पूर्णांकr, 0, "mvme16x-scsi", host)) अणु
		prपूर्णांकk(KERN_ERR "mvme16x-scsi: request_irq failed\n");
		जाओ out_put_host;
	पूर्ण

	/* Enable scsi chip पूर्णांकs */
	अणु
		अस्थिर अचिन्हित दीर्घ v;

		/* Enable scsi पूर्णांकerrupts at level 4 in PCCchip2 */
		v = in_be32(0xfff4202c);
		v = (v & ~0xff) | 0x10 | 4;
		out_be32(0xfff4202c, v);
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

अटल पूर्णांक mvme16x_device_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा Scsi_Host *host = platक्रमm_get_drvdata(dev);
	काष्ठा NCR_700_Host_Parameters *hostdata = shost_priv(host);

	/* Disable scsi chip पूर्णांकs */
	अणु
		अस्थिर अचिन्हित दीर्घ v;

		v = in_be32(0xfff4202c);
		v &= ~0x10;
		out_be32(0xfff4202c, v);
	पूर्ण
	scsi_हटाओ_host(host);
	NCR_700_release(host);
	kमुक्त(hostdata);
	मुक्त_irq(host->irq, host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mvme16x_scsi_driver = अणु
	.driver = अणु
		.name           = "mvme16x-scsi",
	पूर्ण,
	.probe          = mvme16x_probe,
	.हटाओ         = mvme16x_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init mvme16x_scsi_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&mvme16x_scsi_driver);
	अगर (err)
		वापस err;

	mvme16x_scsi_device = platक्रमm_device_रेजिस्टर_simple("mvme16x-scsi",
							      -1, शून्य, 0);
	अगर (IS_ERR(mvme16x_scsi_device)) अणु
		platक्रमm_driver_unरेजिस्टर(&mvme16x_scsi_driver);
		वापस PTR_ERR(mvme16x_scsi_device);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास mvme16x_scsi_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(mvme16x_scsi_device);
	platक्रमm_driver_unरेजिस्टर(&mvme16x_scsi_driver);
पूर्ण

module_init(mvme16x_scsi_init);
module_निकास(mvme16x_scsi_निकास);
