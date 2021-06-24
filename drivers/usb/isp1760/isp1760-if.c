<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Glue code क्रम the ISP1760 driver and bus
 * Currently there is support क्रम
 * - OpenFirmware
 * - PCI
 * - PDEV (generic platक्रमm device centralized driver model)
 *
 * (c) 2007 Sebastian Siewior <bigeasy@linutronix.de>
 *
 */

#समावेश <linux/usb.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/isp1760.h>
#समावेश <linux/usb/hcd.h>

#समावेश "isp1760-core.h"
#समावेश "isp1760-regs.h"

#अगर_घोषित CONFIG_USB_PCI
#समावेश <linux/pci.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_PCI
अटल पूर्णांक isp1761_pci_init(काष्ठा pci_dev *dev)
अणु
	resource_माप_प्रकार mem_start;
	resource_माप_प्रकार mem_length;
	u8 __iomem *iobase;
	u8 latency, limit;
	पूर्णांक retry_count;
	u32 reg_data;

	/* Grab the PLX PCI shared memory of the ISP 1761 we need  */
	mem_start = pci_resource_start(dev, 3);
	mem_length = pci_resource_len(dev, 3);
	अगर (mem_length < 0xffff) अणु
		prपूर्णांकk(KERN_ERR "memory length for this resource is wrong\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!request_mem_region(mem_start, mem_length, "ISP-PCI")) अणु
		prपूर्णांकk(KERN_ERR "host controller already in use\n");
		वापस -EBUSY;
	पूर्ण

	/* map available memory */
	iobase = ioremap(mem_start, mem_length);
	अगर (!iobase) अणु
		prपूर्णांकk(KERN_ERR "Error ioremap failed\n");
		release_mem_region(mem_start, mem_length);
		वापस -ENOMEM;
	पूर्ण

	/* bad pci latencies can contribute to overruns */
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &latency);
	अगर (latency) अणु
		pci_पढ़ो_config_byte(dev, PCI_MAX_LAT, &limit);
		अगर (limit && limit < latency)
			pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, limit);
	पूर्ण

	/* Try to check whether we can access Scratch Register of
	 * Host Controller or not. The initial PCI access is retried until
	 * local init क्रम the PCI bridge is completed
	 */
	retry_count = 20;
	reg_data = 0;
	जबतक ((reg_data != 0xFACE) && retry_count) अणु
		/*by शेष host is in 16bit mode, so
		 * io operations at this stage must be 16 bit
		 * */
		ग_लिखोl(0xface, iobase + HC_SCRATCH_REG);
		udelay(100);
		reg_data = पढ़ोl(iobase + HC_SCRATCH_REG) & 0x0000ffff;
		retry_count--;
	पूर्ण

	iounmap(iobase);
	release_mem_region(mem_start, mem_length);

	/* Host Controller presence is detected by writing to scratch रेजिस्टर
	 * and पढ़ोing back and checking the contents are same or not
	 */
	अगर (reg_data != 0xFACE) अणु
		dev_err(&dev->dev, "scratch register mismatch %x\n", reg_data);
		वापस -ENOMEM;
	पूर्ण

	/* Grab the PLX PCI mem maped port start address we need  */
	mem_start = pci_resource_start(dev, 0);
	mem_length = pci_resource_len(dev, 0);

	अगर (!request_mem_region(mem_start, mem_length, "ISP1761 IO MEM")) अणु
		prपूर्णांकk(KERN_ERR "request region #1\n");
		वापस -EBUSY;
	पूर्ण

	iobase = ioremap(mem_start, mem_length);
	अगर (!iobase) अणु
		prपूर्णांकk(KERN_ERR "ioremap #1\n");
		release_mem_region(mem_start, mem_length);
		वापस -ENOMEM;
	पूर्ण

	/* configure PLX PCI chip to pass पूर्णांकerrupts */
#घोषणा PLX_INT_CSR_REG 0x68
	reg_data = पढ़ोl(iobase + PLX_INT_CSR_REG);
	reg_data |= 0x900;
	ग_लिखोl(reg_data, iobase + PLX_INT_CSR_REG);

	/* करोne with PLX IO access */
	iounmap(iobase);
	release_mem_region(mem_start, mem_length);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1761_pci_probe(काष्ठा pci_dev *dev,
		स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित पूर्णांक devflags = 0;
	पूर्णांक ret;

	अगर (!dev->irq)
		वापस -ENODEV;

	अगर (pci_enable_device(dev) < 0)
		वापस -ENODEV;

	ret = isp1761_pci_init(dev);
	अगर (ret < 0)
		जाओ error;

	pci_set_master(dev);

	ret = isp1760_रेजिस्टर(&dev->resource[3], dev->irq, 0, &dev->dev,
			       devflags);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	pci_disable_device(dev);
	वापस ret;
पूर्ण

अटल व्योम isp1761_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	isp1760_unरेजिस्टर(&dev->dev);

	pci_disable_device(dev);
पूर्ण

अटल व्योम isp1761_pci_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	prपूर्णांकk(KERN_ERR "ips1761_pci_shutdown\n");
पूर्ण

अटल स्थिर काष्ठा pci_device_id isp1760_plx[] = अणु
	अणु
		.class          = PCI_CLASS_BRIDGE_OTHER << 8,
		.class_mask     = ~0,
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= 0x5406,
		.subvenकरोr	= PCI_VENDOR_ID_PLX,
		.subdevice	= 0x9054,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, isp1760_plx);

अटल काष्ठा pci_driver isp1761_pci_driver = अणु
	.name =         "isp1760",
	.id_table =     isp1760_plx,
	.probe =        isp1761_pci_probe,
	.हटाओ =       isp1761_pci_हटाओ,
	.shutकरोwn =     isp1761_pci_shutकरोwn,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक isp1760_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक devflags = 0;
	काष्ठा resource *mem_res;
	काष्ठा resource *irq_res;
	पूर्णांक ret;

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq_res) अणु
		pr_warn("isp1760: IRQ resource not available\n");
		वापस -ENODEV;
	पूर्ण
	irqflags = irq_res->flags & IRQF_TRIGGER_MASK;

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		काष्ठा device_node *dp = pdev->dev.of_node;
		u32 bus_width = 0;

		अगर (of_device_is_compatible(dp, "nxp,usb-isp1761"))
			devflags |= ISP1760_FLAG_ISP1761;

		/* Some प्रणालीs wire up only 16 of the 32 data lines */
		of_property_पढ़ो_u32(dp, "bus-width", &bus_width);
		अगर (bus_width == 16)
			devflags |= ISP1760_FLAG_BUS_WIDTH_16;

		अगर (of_property_पढ़ो_bool(dp, "port1-otg"))
			devflags |= ISP1760_FLAG_OTG_EN;

		अगर (of_property_पढ़ो_bool(dp, "analog-oc"))
			devflags |= ISP1760_FLAG_ANALOG_OC;

		अगर (of_property_पढ़ो_bool(dp, "dack-polarity"))
			devflags |= ISP1760_FLAG_DACK_POL_HIGH;

		अगर (of_property_पढ़ो_bool(dp, "dreq-polarity"))
			devflags |= ISP1760_FLAG_DREQ_POL_HIGH;
	पूर्ण अन्यथा अगर (dev_get_platdata(&pdev->dev)) अणु
		काष्ठा isp1760_platक्रमm_data *pdata =
			dev_get_platdata(&pdev->dev);

		अगर (pdata->is_isp1761)
			devflags |= ISP1760_FLAG_ISP1761;
		अगर (pdata->bus_width_16)
			devflags |= ISP1760_FLAG_BUS_WIDTH_16;
		अगर (pdata->port1_otg)
			devflags |= ISP1760_FLAG_OTG_EN;
		अगर (pdata->analog_oc)
			devflags |= ISP1760_FLAG_ANALOG_OC;
		अगर (pdata->dack_polarity_high)
			devflags |= ISP1760_FLAG_DACK_POL_HIGH;
		अगर (pdata->dreq_polarity_high)
			devflags |= ISP1760_FLAG_DREQ_POL_HIGH;
	पूर्ण

	ret = isp1760_रेजिस्टर(mem_res, irq_res->start, irqflags, &pdev->dev,
			       devflags);
	अगर (ret < 0)
		वापस ret;

	pr_info("ISP1760 USB device initialised\n");
	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	isp1760_unरेजिस्टर(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id isp1760_of_match[] = अणु
	अणु .compatible = "nxp,usb-isp1760", पूर्ण,
	अणु .compatible = "nxp,usb-isp1761", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isp1760_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver isp1760_plat_driver = अणु
	.probe	= isp1760_plat_probe,
	.हटाओ	= isp1760_plat_हटाओ,
	.driver	= अणु
		.name	= "isp1760",
		.of_match_table = of_match_ptr(isp1760_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init isp1760_init(व्योम)
अणु
	पूर्णांक ret, any_ret = -ENODEV;

	isp1760_init_kmem_once();

	ret = platक्रमm_driver_रेजिस्टर(&isp1760_plat_driver);
	अगर (!ret)
		any_ret = 0;
#अगर_घोषित CONFIG_USB_PCI
	ret = pci_रेजिस्टर_driver(&isp1761_pci_driver);
	अगर (!ret)
		any_ret = 0;
#पूर्ण_अगर

	अगर (any_ret)
		isp1760_deinit_kmem_cache();
	वापस any_ret;
पूर्ण
module_init(isp1760_init);

अटल व्योम __निकास isp1760_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&isp1760_plat_driver);
#अगर_घोषित CONFIG_USB_PCI
	pci_unरेजिस्टर_driver(&isp1761_pci_driver);
#पूर्ण_अगर
	isp1760_deinit_kmem_cache();
पूर्ण
module_निकास(isp1760_निकास);
