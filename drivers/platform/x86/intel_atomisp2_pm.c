<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dummy driver क्रम Intel's Image Signal Processor found on Bay Trail
 * and Cherry Trail devices. The sole purpose of this driver is to allow
 * the ISP to be put in D3.
 *
 * Copyright (C) 2018 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches क्रम ISP support:
 * Copyright (C) 2010-2017 Intel Corporation. All rights reserved.
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <यंत्र/iosf_mbi.h>

/* PCI configuration regs */
#घोषणा PCI_INTERRUPT_CTRL		0x9c

#घोषणा PCI_CSI_CONTROL			0xe8
#घोषणा PCI_CSI_CONTROL_PORTS_OFF_MASK	0x7

/* IOSF BT_MBI_UNIT_PMC regs */
#घोषणा ISPSSPM0			0x39
#घोषणा ISPSSPM0_ISPSSC_OFFSET		0
#घोषणा ISPSSPM0_ISPSSC_MASK		0x00000003
#घोषणा ISPSSPM0_ISPSSS_OFFSET		24
#घोषणा ISPSSPM0_ISPSSS_MASK		0x03000000
#घोषणा ISPSSPM0_IUNIT_POWER_ON		0x0
#घोषणा ISPSSPM0_IUNIT_POWER_OFF	0x3

अटल पूर्णांक isp_set_घातer(काष्ठा pci_dev *dev, bool enable)
अणु
	अचिन्हित दीर्घ समयout;
	u32 val = enable ? ISPSSPM0_IUNIT_POWER_ON : ISPSSPM0_IUNIT_POWER_OFF;

	/* Write to ISPSSPM0 bit[1:0] to घातer on/off the IUNIT */
	iosf_mbi_modअगरy(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0,
			val, ISPSSPM0_ISPSSC_MASK);

	/*
	 * There should be no IUNIT access जबतक घातer-करोwn is
	 * in progress. HW sighting: 4567865.
	 * Wait up to 50 ms क्रम the IUNIT to shut करोwn.
	 * And we करो the same क्रम घातer on.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(50);
	करो अणु
		u32 पंचांगp;

		/* Wait until ISPSSPM0 bit[25:24] shows the right value */
		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0, &पंचांगp);
		पंचांगp = (पंचांगp & ISPSSPM0_ISPSSS_MASK) >> ISPSSPM0_ISPSSS_OFFSET;
		अगर (पंचांगp == val)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	dev_err(&dev->dev, "IUNIT power-%s timeout.\n", enable ? "on" : "off");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक isp_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	pm_runसमय_allow(&dev->dev);
	pm_runसमय_put_sync_suspend(&dev->dev);

	वापस 0;
पूर्ण

अटल व्योम isp_हटाओ(काष्ठा pci_dev *dev)
अणु
	pm_runसमय_get_sync(&dev->dev);
	pm_runसमय_क्रमbid(&dev->dev);
पूर्ण

अटल पूर्णांक isp_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u32 val;

	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, 0);

	/*
	 * MRFLD IUNIT DPHY is located in an always-घातer-on island
	 * MRFLD HW design need all CSI ports are disabled beक्रमe
	 * घातering करोwn the IUNIT.
	 */
	pci_पढ़ो_config_dword(pdev, PCI_CSI_CONTROL, &val);
	val |= PCI_CSI_CONTROL_PORTS_OFF_MASK;
	pci_ग_लिखो_config_dword(pdev, PCI_CSI_CONTROL, val);

	/*
	 * We lose config space access when punit घातer gates
	 * the ISP. Can't use pci_set_घातer_state() because
	 * pmcsr won't actually change when we ग_लिखो to it.
	 */
	pci_save_state(pdev);
	pdev->current_state = PCI_D3cold;
	isp_set_घातer(pdev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक isp_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	isp_set_घातer(pdev, true);
	pdev->current_state = PCI_D0;
	pci_restore_state(pdev);

	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(isp_pm_ops, isp_pci_suspend,
			    isp_pci_resume, शून्य);

अटल स्थिर काष्ठा pci_device_id isp_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0f38), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22b8), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, isp_id_table);

अटल काष्ठा pci_driver isp_pci_driver = अणु
	.name = "intel_atomisp2_pm",
	.id_table = isp_id_table,
	.probe = isp_probe,
	.हटाओ = isp_हटाओ,
	.driver.pm = &isp_pm_ops,
पूर्ण;

module_pci_driver(isp_pci_driver);

MODULE_DESCRIPTION("Intel AtomISP2 dummy / power-management drv (for suspend)");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
