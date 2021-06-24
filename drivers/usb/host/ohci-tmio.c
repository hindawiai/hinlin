<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OHCI HCD(Host Controller Driver) क्रम USB.
 *
 *(C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 *(C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *(C) Copyright 2002 Hewlett-Packard Company
 *
 * Bus glue क्रम Toshiba Mobile IO(TMIO) Controller's OHCI core
 * (C) Copyright 2005 Chris Humbert <mahadri-usb@drigon.com>
 * (C) Copyright 2007, 2008 Dmitry Baryshkov <dbaryshkov@gmail.com>
 *
 * This is known to work with the following variants:
 *	TC6393XB revision 3	(32kB SRAM)
 *
 * The TMIO's OHCI core DMAs through a small पूर्णांकernal buffer that
 * is directly addressable by the CPU.
 *
 * Written from sparse करोcumentation from Toshiba and Sharp's driver
 * क्रम the 2.4 kernel,
 *	usb-ohci-tc6393.c(C) Copyright 2004 Lineo Solutions, Inc.
 */

/*#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>*/
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/dma-mapping.h>

/*-------------------------------------------------------------------------*/

/*
 * USB Host Controller Configuration Register
 */
#घोषणा CCR_REVID	0x08	/* b Revision ID				*/
#घोषणा CCR_BASE	0x10	/* l USB Control Register Base Address Low	*/
#घोषणा CCR_ILME	0x40	/* b Internal Local Memory Enable		*/
#घोषणा CCR_PM		0x4c	/* w Power Management			*/
#घोषणा CCR_INTC	0x50	/* b INT Control				*/
#घोषणा CCR_LMW1L	0x54	/* w Local Memory Winकरोw 1 LMADRS Low	*/
#घोषणा CCR_LMW1H	0x56	/* w Local Memory Winकरोw 1 LMADRS High	*/
#घोषणा CCR_LMW1BL	0x58	/* w Local Memory Winकरोw 1 Base Address Low	*/
#घोषणा CCR_LMW1BH	0x5A	/* w Local Memory Winकरोw 1 Base Address High	*/
#घोषणा CCR_LMW2L	0x5C	/* w Local Memory Winकरोw 2 LMADRS Low	*/
#घोषणा CCR_LMW2H	0x5E	/* w Local Memory Winकरोw 2 LMADRS High	*/
#घोषणा CCR_LMW2BL	0x60	/* w Local Memory Winकरोw 2 Base Address Low	*/
#घोषणा CCR_LMW2BH	0x62	/* w Local Memory Winकरोw 2 Base Address High	*/
#घोषणा CCR_MISC	0xFC	/* b MISC					*/

#घोषणा CCR_PM_GKEN      0x0001
#घोषणा CCR_PM_CKRNEN    0x0002
#घोषणा CCR_PM_USBPW1    0x0004
#घोषणा CCR_PM_USBPW2    0x0008
#घोषणा CCR_PM_USBPW3    0x0010
#घोषणा CCR_PM_PMEE      0x0100
#घोषणा CCR_PM_PMES      0x8000

/*-------------------------------------------------------------------------*/

काष्ठा पंचांगio_hcd अणु
	व्योम __iomem		*ccr;
	spinlock_t		lock; /* protects RMW cycles */
पूर्ण;

#घोषणा hcd_to_पंचांगio(hcd)	((काष्ठा पंचांगio_hcd *)(hcd_to_ohci(hcd) + 1))

/*-------------------------------------------------------------------------*/

अटल व्योम पंचांगio_ग_लिखो_pm(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	u16 pm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पंचांगio->lock, flags);

	pm = CCR_PM_GKEN | CCR_PM_CKRNEN |
	     CCR_PM_PMEE | CCR_PM_PMES;

	पंचांगio_ioग_लिखो16(pm, पंचांगio->ccr + CCR_PM);
	spin_unlock_irqrestore(&पंचांगio->lock, flags);
पूर्ण

अटल व्योम पंचांगio_stop_hc(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	u16 pm;

	pm = CCR_PM_GKEN | CCR_PM_CKRNEN;
	चयन (ohci->num_ports) अणु
		शेष:
			dev_err(&dev->dev, "Unsupported amount of ports: %d\n", ohci->num_ports);
			fallthrough;
		हाल 3:
			pm |= CCR_PM_USBPW3;
			fallthrough;
		हाल 2:
			pm |= CCR_PM_USBPW2;
			fallthrough;
		हाल 1:
			pm |= CCR_PM_USBPW1;
	पूर्ण
	पंचांगio_ioग_लिखो8(0, पंचांगio->ccr + CCR_INTC);
	पंचांगio_ioग_लिखो8(0, पंचांगio->ccr + CCR_ILME);
	पंचांगio_ioग_लिखो16(0, पंचांगio->ccr + CCR_BASE);
	पंचांगio_ioग_लिखो16(0, पंचांगio->ccr + CCR_BASE + 2);
	पंचांगio_ioग_लिखो16(pm, पंचांगio->ccr + CCR_PM);
पूर्ण

अटल व्योम पंचांगio_start_hc(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	अचिन्हित दीर्घ base = hcd->rsrc_start;

	पंचांगio_ग_लिखो_pm(dev);
	पंचांगio_ioग_लिखो16(base, पंचांगio->ccr + CCR_BASE);
	पंचांगio_ioग_लिखो16(base >> 16, पंचांगio->ccr + CCR_BASE + 2);
	पंचांगio_ioग_लिखो8(1, पंचांगio->ccr + CCR_ILME);
	पंचांगio_ioग_लिखो8(2, पंचांगio->ccr + CCR_INTC);

	dev_info(&dev->dev, "revision %d @ 0x%08llx, irq %d\n",
			पंचांगio_ioपढ़ो8(पंचांगio->ccr + CCR_REVID),
			(u64) hcd->rsrc_start, hcd->irq);
पूर्ण

अटल पूर्णांक ohci_पंचांगio_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	पूर्णांक ret;

	अगर ((ret = ohci_init(ohci)) < 0)
		वापस ret;

	अगर ((ret = ohci_run(ohci)) < 0) अणु
		dev_err(hcd->self.controller, "can't start %s\n",
			hcd->self.bus_name);
		ohci_stop(hcd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver ohci_पंचांगio_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"TMIO OHCI USB Host Controller",
	.hcd_priv_size =	माप(काष्ठा ohci_hcd) + माप (काष्ठा पंचांगio_hcd),

	/* generic hardware linkage */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/* basic lअगरecycle operations */
	.start =		ohci_पंचांगio_start,
	.stop =			ohci_stop,
	.shutकरोwn =		ohci_shutकरोwn,

	/* managing i/o requests and associated device resources */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoपूर्णांक_disable =	ohci_endpoपूर्णांक_disable,

	/* scheduling support */
	.get_frame_number =	ohci_get_frame,

	/* root hub support */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#अगर_घोषित	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#पूर्ण_अगर
	.start_port_reset =	ohci_start_port_reset,
पूर्ण;

/*-------------------------------------------------------------------------*/
अटल काष्ठा platक्रमm_driver ohci_hcd_पंचांगio_driver;

अटल पूर्णांक ohci_hcd_पंचांगio_drv_probe(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा resource *regs = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	काष्ठा resource *config = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	काष्ठा resource *sram = platक्रमm_get_resource(dev, IORESOURCE_MEM, 2);
	पूर्णांक irq = platक्रमm_get_irq(dev, 0);
	काष्ठा पंचांगio_hcd *पंचांगio;
	काष्ठा ohci_hcd *ohci;
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (!cell)
		वापस -EINVAL;

	hcd = usb_create_hcd(&ohci_पंचांगio_hc_driver, &dev->dev, dev_name(&dev->dev));
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ err_usb_create_hcd;
	पूर्ण

	hcd->rsrc_start = regs->start;
	hcd->rsrc_len = resource_size(regs);

	पंचांगio = hcd_to_पंचांगio(hcd);

	spin_lock_init(&पंचांगio->lock);

	पंचांगio->ccr = ioremap(config->start, resource_size(config));
	अगर (!पंचांगio->ccr) अणु
		ret = -ENOMEM;
		जाओ err_ioremap_ccr;
	पूर्ण

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	अगर (!hcd->regs) अणु
		ret = -ENOMEM;
		जाओ err_ioremap_regs;
	पूर्ण

	अगर (cell->enable) अणु
		ret = cell->enable(dev);
		अगर (ret)
			जाओ err_enable;
	पूर्ण

	पंचांगio_start_hc(dev);
	ohci = hcd_to_ohci(hcd);
	ohci_hcd_init(ohci);

	ret = usb_hcd_setup_local_mem(hcd, sram->start, sram->start,
				      resource_size(sram));
	अगर (ret < 0)
		जाओ err_enable;

	ret = usb_add_hcd(hcd, irq, 0);
	अगर (ret)
		जाओ err_add_hcd;

	device_wakeup_enable(hcd->self.controller);
	अगर (ret == 0)
		वापस ret;

	usb_हटाओ_hcd(hcd);

err_add_hcd:
	पंचांगio_stop_hc(dev);
	अगर (cell->disable)
		cell->disable(dev);
err_enable:
	iounmap(hcd->regs);
err_ioremap_regs:
	iounmap(पंचांगio->ccr);
err_ioremap_ccr:
	usb_put_hcd(hcd);
err_usb_create_hcd:

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_hcd_पंचांगio_drv_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);

	usb_हटाओ_hcd(hcd);
	पंचांगio_stop_hc(dev);
	अगर (cell->disable)
		cell->disable(dev);
	iounmap(hcd->regs);
	iounmap(पंचांगio->ccr);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ohci_hcd_पंचांगio_drv_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	अचिन्हित दीर्घ flags;
	u8 misc;
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	spin_lock_irqsave(&पंचांगio->lock, flags);

	misc = पंचांगio_ioपढ़ो8(पंचांगio->ccr + CCR_MISC);
	misc |= 1 << 3; /* USSUSP */
	पंचांगio_ioग_लिखो8(misc, पंचांगio->ccr + CCR_MISC);

	spin_unlock_irqrestore(&पंचांगio->lock, flags);

	अगर (cell->suspend) अणु
		ret = cell->suspend(dev);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ohci_hcd_पंचांगio_drv_resume(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(dev);
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	काष्ठा पंचांगio_hcd *पंचांगio = hcd_to_पंचांगio(hcd);
	अचिन्हित दीर्घ flags;
	u8 misc;
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	अगर (cell->resume) अणु
		ret = cell->resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	पंचांगio_start_hc(dev);

	spin_lock_irqsave(&पंचांगio->lock, flags);

	misc = पंचांगio_ioपढ़ो8(पंचांगio->ccr + CCR_MISC);
	misc &= ~(1 << 3); /* USSUSP */
	पंचांगio_ioग_लिखो8(misc, पंचांगio->ccr + CCR_MISC);

	spin_unlock_irqrestore(&पंचांगio->lock, flags);

	ohci_resume(hcd, false);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ohci_hcd_पंचांगio_drv_suspend शून्य
#घोषणा ohci_hcd_पंचांगio_drv_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ohci_hcd_पंचांगio_driver = अणु
	.probe		= ohci_hcd_पंचांगio_drv_probe,
	.हटाओ		= ohci_hcd_पंचांगio_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.suspend	= ohci_hcd_पंचांगio_drv_suspend,
	.resume		= ohci_hcd_पंचांगio_drv_resume,
	.driver		= अणु
		.name	= "tmio-ohci",
	पूर्ण,
पूर्ण;
