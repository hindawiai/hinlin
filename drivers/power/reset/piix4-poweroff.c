<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>

अटल काष्ठा pci_dev *pm_dev;
अटल resource_माप_प्रकार io_offset;

क्रमागत piix4_pm_io_reg अणु
	PIIX4_FUNC3IO_PMSTS			= 0x00,
#घोषणा PIIX4_FUNC3IO_PMSTS_PWRBTN_STS		BIT(8)
	PIIX4_FUNC3IO_PMCNTRL			= 0x04,
#घोषणा PIIX4_FUNC3IO_PMCNTRL_SUS_EN		BIT(13)
#घोषणा PIIX4_FUNC3IO_PMCNTRL_SUS_TYP_SOFF	(0x0 << 10)
पूर्ण;

#घोषणा PIIX4_SUSPEND_MAGIC			0x00120002

अटल स्थिर पूर्णांक piix4_pm_io_region = PCI_BRIDGE_RESOURCES;

अटल व्योम piix4_घातeroff(व्योम)
अणु
	पूर्णांक spec_devid;
	u16 sts;

	/* Ensure the घातer button status is clear */
	जबतक (1) अणु
		sts = inw(io_offset + PIIX4_FUNC3IO_PMSTS);
		अगर (!(sts & PIIX4_FUNC3IO_PMSTS_PWRBTN_STS))
			अवरोध;
		outw(sts, io_offset + PIIX4_FUNC3IO_PMSTS);
	पूर्ण

	/* Enable entry to suspend */
	outw(PIIX4_FUNC3IO_PMCNTRL_SUS_TYP_SOFF | PIIX4_FUNC3IO_PMCNTRL_SUS_EN,
	     io_offset + PIIX4_FUNC3IO_PMCNTRL);

	/* If the special cycle occurs too soon this करोesn't work... */
	mdelay(10);

	/*
	 * The PIIX4 will enter the suspend state only after seeing a special
	 * cycle with the correct magic data on the PCI bus. Generate that
	 * cycle now.
	 */
	spec_devid = PCI_DEVID(0, PCI_DEVFN(0x1f, 0x7));
	pci_bus_ग_लिखो_config_dword(pm_dev->bus, spec_devid, 0,
				   PIIX4_SUSPEND_MAGIC);

	/* Give the प्रणाली some समय to घातer करोwn, then error */
	mdelay(1000);
	pr_emerg("Unable to poweroff system\n");
पूर्ण

अटल पूर्णांक piix4_घातeroff_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक res;

	अगर (pm_dev)
		वापस -EINVAL;

	/* Request access to the PIIX4 PM IO रेजिस्टरs */
	res = pci_request_region(dev, piix4_pm_io_region,
				 "PIIX4 PM IO registers");
	अगर (res) अणु
		dev_err(&dev->dev, "failed to request PM IO registers: %d\n",
			res);
		वापस res;
	पूर्ण

	pm_dev = dev;
	io_offset = pci_resource_start(dev, piix4_pm_io_region);
	pm_घातer_off = piix4_घातeroff;

	वापस 0;
पूर्ण

अटल व्योम piix4_घातeroff_हटाओ(काष्ठा pci_dev *dev)
अणु
	अगर (pm_घातer_off == piix4_घातeroff)
		pm_घातer_off = शून्य;

	pci_release_region(dev, piix4_pm_io_region);
	pm_dev = शून्य;
पूर्ण

अटल स्थिर काष्ठा pci_device_id piix4_घातeroff_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_3) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver piix4_घातeroff_driver = अणु
	.name		= "piix4-poweroff",
	.id_table	= piix4_घातeroff_ids,
	.probe		= piix4_घातeroff_probe,
	.हटाओ		= piix4_घातeroff_हटाओ,
पूर्ण;

module_pci_driver(piix4_घातeroff_driver);
MODULE_AUTHOR("Paul Burton <paul.burton@mips.com>");
MODULE_LICENSE("GPL");
