<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub pci driver
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pci.h>

#समावेश "intel_th.h"

#घोषणा DRIVER_NAME "intel_th_pci"

क्रमागत अणु
	TH_PCI_CONFIG_BAR	= 0,
	TH_PCI_STH_SW_BAR	= 2,
	TH_PCI_RTIT_BAR		= 4,
पूर्ण;

#घोषणा BAR_MASK (BIT(TH_PCI_CONFIG_BAR) | BIT(TH_PCI_STH_SW_BAR))

#घोषणा PCI_REG_NPKDSC	0x80
#घोषणा NPKDSC_TSACT	BIT(5)

अटल पूर्णांक पूर्णांकel_th_pci_activate(काष्ठा पूर्णांकel_th *th)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(th->dev);
	u32 npkdsc;
	पूर्णांक err;

	अगर (!INTEL_TH_CAP(th, tscu_enable))
		वापस 0;

	err = pci_पढ़ो_config_dword(pdev, PCI_REG_NPKDSC, &npkdsc);
	अगर (!err) अणु
		npkdsc |= NPKDSC_TSACT;
		err = pci_ग_लिखो_config_dword(pdev, PCI_REG_NPKDSC, npkdsc);
	पूर्ण

	अगर (err)
		dev_err(&pdev->dev, "failed to read NPKDSC register\n");

	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_th_pci_deactivate(काष्ठा पूर्णांकel_th *th)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(th->dev);
	u32 npkdsc;
	पूर्णांक err;

	अगर (!INTEL_TH_CAP(th, tscu_enable))
		वापस;

	err = pci_पढ़ो_config_dword(pdev, PCI_REG_NPKDSC, &npkdsc);
	अगर (!err) अणु
		npkdsc |= NPKDSC_TSACT;
		err = pci_ग_लिखो_config_dword(pdev, PCI_REG_NPKDSC, npkdsc);
	पूर्ण

	अगर (err)
		dev_err(&pdev->dev, "failed to read NPKDSC register\n");
पूर्ण

अटल पूर्णांक पूर्णांकel_th_pci_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा पूर्णांकel_th_drvdata *drvdata = (व्योम *)id->driver_data;
	काष्ठा resource resource[TH_MMIO_END + TH_NVEC_MAX] = अणु
		[TH_MMIO_CONFIG]	= pdev->resource[TH_PCI_CONFIG_BAR],
		[TH_MMIO_SW]		= pdev->resource[TH_PCI_STH_SW_BAR],
	पूर्ण;
	पूर्णांक err, r = TH_MMIO_SW + 1, i;
	काष्ठा पूर्णांकel_th *th;

	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pcim_iomap_regions_request_all(pdev, BAR_MASK, DRIVER_NAME);
	अगर (err)
		वापस err;

	अगर (pdev->resource[TH_PCI_RTIT_BAR].start) अणु
		resource[TH_MMIO_RTIT] = pdev->resource[TH_PCI_RTIT_BAR];
		r++;
	पूर्ण

	err = pci_alloc_irq_vectors(pdev, 1, 8, PCI_IRQ_ALL_TYPES);
	अगर (err > 0)
		क्रम (i = 0; i < err; i++, r++) अणु
			resource[r].flags = IORESOURCE_IRQ;
			resource[r].start = pci_irq_vector(pdev, i);
		पूर्ण

	th = पूर्णांकel_th_alloc(&pdev->dev, drvdata, resource, r);
	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	th->activate   = पूर्णांकel_th_pci_activate;
	th->deactivate = पूर्णांकel_th_pci_deactivate;

	pci_set_master(pdev);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा पूर्णांकel_th *th = pci_get_drvdata(pdev);

	पूर्णांकel_th_मुक्त(th);

	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_th_drvdata पूर्णांकel_th_1x_multi_is_broken = अणु
	.multi_is_broken	= 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_th_drvdata पूर्णांकel_th_2x = अणु
	.tscu_enable	= 1,
	.has_mपूर्णांकctl	= 1,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_th_pci_id_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x9d26),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa126),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Apollo Lake */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x5a8e),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Broxton */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0a80),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Broxton B-step */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x1a8e),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Kaby Lake PCH-H */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa2a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_1x_multi_is_broken,
	पूर्ण,
	अणु
		/* Denverton */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x19e1),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Lewisburg PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa1a6),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Lewisburg PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa226),
		.driver_data = (kernel_uदीर्घ_t)0,
	पूर्ण,
	अणु
		/* Gemini Lake */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x318e),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Cannon Lake H */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa326),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Cannon Lake LP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x9da6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Cedar Fork PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x18e1),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Ice Lake PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x34a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Comet Lake */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x02a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Comet Lake PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x06a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Comet Lake PCH-V */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa3a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_1x_multi_is_broken,
	पूर्ण,
	अणु
		/* Ice Lake NNPI */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x45c5),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Ice Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8a29),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Tiger Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x9a33),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Tiger Lake PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xa0a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Tiger Lake PCH-H */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x43a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Jasper Lake PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4da6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Jasper Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4e29),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Elkhart Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4529),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Elkhart Lake */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4b26),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Emmitsburg PCH */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x1bcc),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Alder Lake */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7aa6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Alder Lake-P */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x51a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Alder Lake-M */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x54a6),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Alder Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x466f),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु
		/* Rocket Lake CPU */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x4c19),
		.driver_data = (kernel_uदीर्घ_t)&पूर्णांकel_th_2x,
	पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, पूर्णांकel_th_pci_id_table);

अटल काष्ठा pci_driver पूर्णांकel_th_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= पूर्णांकel_th_pci_id_table,
	.probe		= पूर्णांकel_th_pci_probe,
	.हटाओ		= पूर्णांकel_th_pci_हटाओ,
पूर्ण;

module_pci_driver(पूर्णांकel_th_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub PCI controller driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@intel.com>");
