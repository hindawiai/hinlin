<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Zalon 53c7xx device driver.
 * By Riअक्षरd Hirst (rhirst@linuxcare.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/पन.स>

#समावेश "../parisc/gsc.h"

#समावेश "ncr53c8xx.h"

MODULE_AUTHOR("Richard Hirst");
MODULE_DESCRIPTION("Bluefish/Zalon 720 SCSI Driver");
MODULE_LICENSE("GPL");

#घोषणा GSC_SCSI_ZALON_OFFSET 0x800

#घोषणा IO_MODULE_EIM		(1*4)
#घोषणा IO_MODULE_DC_ADATA	(2*4)
#घोषणा IO_MODULE_II_CDATA	(3*4)
#घोषणा IO_MODULE_IO_COMMAND	(12*4)
#घोषणा IO_MODULE_IO_STATUS	(13*4)

#घोषणा IOSTATUS_RY		0x40
#घोषणा IOSTATUS_FE		0x80
#घोषणा IOIIDATA_SMINT5L	0x40000000
#घोषणा IOIIDATA_MINT5EN	0x20000000
#घोषणा IOIIDATA_PACKEN		0x10000000
#घोषणा IOIIDATA_PREFETCHEN	0x08000000
#घोषणा IOIIDATA_IOII		0x00000020

#घोषणा CMD_RESET		5

अटल काष्ठा ncr_chip zalon720_chip __initdata = अणु
	.revision_id =	0x0f,
	.burst_max =	3,
	.offset_max =	8,
	.nr_भागisor =	4,
	.features =	FE_WIDE | FE_DIFF | FE_EHP| FE_MUX | FE_EA,
पूर्ण;



#अगर 0
/* FIXME:
 * Is this function dead code? or is someone planning on using it in the
 * future.  The घड़ी = (पूर्णांक) pdc_result[16] करोes not look correct to
 * me ... I think it should be iodc_data[16].  Since this cause a compile
 * error with the new encapsulated PDC, I'm not compiling in this function.
 * - RB
 */
/* poke SCSI घड़ी out of iodc data */

अटल u8 iodc_data[32] __attribute__ ((aligned (64)));
अटल अचिन्हित दीर्घ pdc_result[32] __attribute__ ((aligned (16))) =अणु0,0,0,0पूर्ण;

अटल पूर्णांक 
lasi_scsi_घड़ी(व्योम * hpa, पूर्णांक शेषघड़ी)
अणु
	पूर्णांक घड़ी, status;

	status = pdc_iodc_पढ़ो(&pdc_result, hpa, 0, &iodc_data, 32 );
	अगर (status == PDC_RET_OK) अणु
		घड़ी = (पूर्णांक) pdc_result[16];
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s: pdc_iodc_read returned %d\n", __func__, status);
		घड़ी = शेषघड़ी; 
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: SCSI clock %d\n", __func__, घड़ी);
 	वापस घड़ी;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा zalon7xx_ढाँचा = अणु
	.module		= THIS_MODULE,
	.proc_name	= "zalon7xx",
पूर्ण;

अटल पूर्णांक __init
zalon_probe(काष्ठा parisc_device *dev)
अणु
	काष्ठा gsc_irq gsc_irq;
	u32 zalon_vers;
	पूर्णांक error = -ENODEV;
	व्योम __iomem *zalon = ioremap(dev->hpa.start, 4096);
	व्योम __iomem *io_port = zalon + GSC_SCSI_ZALON_OFFSET;
	अटल पूर्णांक unit = 0;
	काष्ठा Scsi_Host *host;
	काष्ठा ncr_device device;

	__raw_ग_लिखोl(CMD_RESET, zalon + IO_MODULE_IO_COMMAND);
	जबतक (!(__raw_पढ़ोl(zalon + IO_MODULE_IO_STATUS) & IOSTATUS_RY))
		cpu_relax();
	__raw_ग_लिखोl(IOIIDATA_MINT5EN | IOIIDATA_PACKEN | IOIIDATA_PREFETCHEN,
		zalon + IO_MODULE_II_CDATA);

	/* XXX: Save the Zalon version क्रम bug workarounds? */
	zalon_vers = (__raw_पढ़ोl(zalon + IO_MODULE_II_CDATA) >> 24) & 0x07;

	/* Setup the पूर्णांकerrupts first.
	** Later on request_irq() will रेजिस्टर the handler.
	*/
	dev->irq = gsc_alloc_irq(&gsc_irq);

	prपूर्णांकk(KERN_INFO "%s: Zalon version %d, IRQ %d\n", __func__,
		zalon_vers, dev->irq);

	__raw_ग_लिखोl(gsc_irq.txn_addr | gsc_irq.txn_data, zalon + IO_MODULE_EIM);

	अगर (zalon_vers == 0)
		prपूर्णांकk(KERN_WARNING "%s: Zalon 1.1 or earlier\n", __func__);

	स_रखो(&device, 0, माप(काष्ठा ncr_device));

	/* The following three are needed beक्रमe any other access. */
	__raw_ग_लिखोb(0x20, io_port + 0x38); /* DCNTL_REG,  EA  */
	__raw_ग_लिखोb(0x04, io_port + 0x1b); /* CTEST0_REG, EHP */
	__raw_ग_लिखोb(0x80, io_port + 0x22); /* CTEST4_REG, MUX */

	/* Initialise ncr_device काष्ठाure with items required by ncr_attach. */
	device.chip		= zalon720_chip;
	device.host_id		= 7;
	device.dev		= &dev->dev;
	device.slot.base	= dev->hpa.start + GSC_SCSI_ZALON_OFFSET;
	device.slot.base_v	= io_port;
	device.slot.irq		= dev->irq;
	device.dअगरferential	= 2;

	host = ncr_attach(&zalon7xx_ढाँचा, unit, &device);
	अगर (!host)
		वापस -ENODEV;

	अगर (request_irq(dev->irq, ncr53c8xx_पूर्णांकr, IRQF_SHARED, "zalon", host)) अणु
	  dev_prपूर्णांकk(KERN_ERR, &dev->dev, "irq problem with %d, detaching\n ",
		     dev->irq);
		जाओ fail;
	पूर्ण

	unit++;

	dev_set_drvdata(&dev->dev, host);

	error = scsi_add_host(host, &dev->dev);
	अगर (error)
		जाओ fail_मुक्त_irq;

	scsi_scan_host(host);
	वापस 0;

 fail_मुक्त_irq:
	मुक्त_irq(dev->irq, host);
 fail:
	ncr53c8xx_release(host);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id zalon_tbl[] __initस्थिर = अणु
	अणु HPHW_A_DMA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00089 पूर्ण, 
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, zalon_tbl);

अटल पूर्णांक __निकास zalon_हटाओ(काष्ठा parisc_device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(&dev->dev);

	scsi_हटाओ_host(host);
	ncr53c8xx_release(host);
	मुक्त_irq(dev->irq, host);

	वापस 0;
पूर्ण

अटल काष्ठा parisc_driver zalon_driver __refdata = अणु
	.name =		"zalon",
	.id_table =	zalon_tbl,
	.probe =	zalon_probe,
	.हटाओ =	__निकास_p(zalon_हटाओ),
पूर्ण;

अटल पूर्णांक __init zalon7xx_init(व्योम)
अणु
	पूर्णांक ret = ncr53c8xx_init();
	अगर (!ret)
		ret = रेजिस्टर_parisc_driver(&zalon_driver);
	अगर (ret)
		ncr53c8xx_निकास();
	वापस ret;
पूर्ण

अटल व्योम __निकास zalon7xx_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&zalon_driver);
	ncr53c8xx_निकास();
पूर्ण

module_init(zalon7xx_init);
module_निकास(zalon7xx_निकास);
