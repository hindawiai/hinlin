<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AMD SoC Power Management Controller Driver
 *
 * Copyright (c) 2020, Advanced Micro Devices, Inc.
 * All Rights Reserved.
 *
 * Author: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

/* SMU communication रेजिस्टरs */
#घोषणा AMD_PMC_REGISTER_MESSAGE	0x538
#घोषणा AMD_PMC_REGISTER_RESPONSE	0x980
#घोषणा AMD_PMC_REGISTER_ARGUMENT	0x9BC

/* Base address of SMU क्रम mapping physical address to भव address */
#घोषणा AMD_PMC_SMU_INDEX_ADDRESS	0xB8
#घोषणा AMD_PMC_SMU_INDEX_DATA		0xBC
#घोषणा AMD_PMC_MAPPING_SIZE		0x01000
#घोषणा AMD_PMC_BASE_ADDR_OFFSET	0x10000
#घोषणा AMD_PMC_BASE_ADDR_LO		0x13B102E8
#घोषणा AMD_PMC_BASE_ADDR_HI		0x13B102EC
#घोषणा AMD_PMC_BASE_ADDR_LO_MASK	GENMASK(15, 0)
#घोषणा AMD_PMC_BASE_ADDR_HI_MASK	GENMASK(31, 20)

/* SMU Response Codes */
#घोषणा AMD_PMC_RESULT_OK                    0x01
#घोषणा AMD_PMC_RESULT_CMD_REJECT_BUSY       0xFC
#घोषणा AMD_PMC_RESULT_CMD_REJECT_PREREQ     0xFD
#घोषणा AMD_PMC_RESULT_CMD_UNKNOWN           0xFE
#घोषणा AMD_PMC_RESULT_FAILED                0xFF

/* List of supported CPU ids */
#घोषणा AMD_CPU_ID_RV			0x15D0
#घोषणा AMD_CPU_ID_RN			0x1630
#घोषणा AMD_CPU_ID_PCO			AMD_CPU_ID_RV
#घोषणा AMD_CPU_ID_CZN			AMD_CPU_ID_RN

#घोषणा AMD_SMU_FW_VERSION		0x0
#घोषणा PMC_MSG_DELAY_MIN_US		100
#घोषणा RESPONSE_REGISTER_LOOP_MAX	200

क्रमागत amd_pmc_def अणु
	MSG_TEST = 0x01,
	MSG_OS_HINT_PCO,
	MSG_OS_HINT_RN,
पूर्ण;

काष्ठा amd_pmc_dev अणु
	व्योम __iomem *regbase;
	व्योम __iomem *smu_base;
	u32 base_addr;
	u32 cpu_id;
	काष्ठा device *dev;
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
पूर्ण;

अटल काष्ठा amd_pmc_dev pmc;

अटल अंतरभूत u32 amd_pmc_reg_पढ़ो(काष्ठा amd_pmc_dev *dev, पूर्णांक reg_offset)
अणु
	वापस ioपढ़ो32(dev->regbase + reg_offset);
पूर्ण

अटल अंतरभूत व्योम amd_pmc_reg_ग_लिखो(काष्ठा amd_pmc_dev *dev, पूर्णांक reg_offset, u32 val)
अणु
	ioग_लिखो32(val, dev->regbase + reg_offset);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक smu_fw_info_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा amd_pmc_dev *dev = s->निजी;
	u32 value;

	value = ioपढ़ो32(dev->smu_base + AMD_SMU_FW_VERSION);
	seq_म_लिखो(s, "SMU FW Info: %x\n", value);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(smu_fw_info);

अटल व्योम amd_pmc_dbgfs_unरेजिस्टर(काष्ठा amd_pmc_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->dbgfs_dir);
पूर्ण

अटल व्योम amd_pmc_dbgfs_रेजिस्टर(काष्ठा amd_pmc_dev *dev)
अणु
	dev->dbgfs_dir = debugfs_create_dir("amd_pmc", शून्य);
	debugfs_create_file("smu_fw_info", 0644, dev->dbgfs_dir, dev,
			    &smu_fw_info_fops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम amd_pmc_dbgfs_रेजिस्टर(काष्ठा amd_pmc_dev *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम amd_pmc_dbgfs_unरेजिस्टर(काष्ठा amd_pmc_dev *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल व्योम amd_pmc_dump_रेजिस्टरs(काष्ठा amd_pmc_dev *dev)
अणु
	u32 value;

	value = amd_pmc_reg_पढ़ो(dev, AMD_PMC_REGISTER_RESPONSE);
	dev_dbg(dev->dev, "AMD_PMC_REGISTER_RESPONSE:%x\n", value);

	value = amd_pmc_reg_पढ़ो(dev, AMD_PMC_REGISTER_ARGUMENT);
	dev_dbg(dev->dev, "AMD_PMC_REGISTER_ARGUMENT:%x\n", value);

	value = amd_pmc_reg_पढ़ो(dev, AMD_PMC_REGISTER_MESSAGE);
	dev_dbg(dev->dev, "AMD_PMC_REGISTER_MESSAGE:%x\n", value);
पूर्ण

अटल पूर्णांक amd_pmc_send_cmd(काष्ठा amd_pmc_dev *dev, bool set)
अणु
	पूर्णांक rc;
	u8 msg;
	u32 val;

	/* Wait until we get a valid response */
	rc = पढ़ोx_poll_समयout(ioपढ़ो32, dev->regbase + AMD_PMC_REGISTER_RESPONSE,
				val, val > 0, PMC_MSG_DELAY_MIN_US,
				PMC_MSG_DELAY_MIN_US * RESPONSE_REGISTER_LOOP_MAX);
	अगर (rc) अणु
		dev_err(dev->dev, "failed to talk to SMU\n");
		वापस rc;
	पूर्ण

	/* Write zero to response रेजिस्टर */
	amd_pmc_reg_ग_लिखो(dev, AMD_PMC_REGISTER_RESPONSE, 0);

	/* Write argument पूर्णांकo response रेजिस्टर */
	amd_pmc_reg_ग_लिखो(dev, AMD_PMC_REGISTER_ARGUMENT, set);

	/* Write message ID to message ID रेजिस्टर */
	msg = (dev->cpu_id == AMD_CPU_ID_RN) ? MSG_OS_HINT_RN : MSG_OS_HINT_PCO;
	amd_pmc_reg_ग_लिखो(dev, AMD_PMC_REGISTER_MESSAGE, msg);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused amd_pmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा amd_pmc_dev *pdev = dev_get_drvdata(dev);
	पूर्णांक rc;

	rc = amd_pmc_send_cmd(pdev, 1);
	अगर (rc)
		dev_err(pdev->dev, "suspend failed\n");

	amd_pmc_dump_रेजिस्टरs(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused amd_pmc_resume(काष्ठा device *dev)
अणु
	काष्ठा amd_pmc_dev *pdev = dev_get_drvdata(dev);
	पूर्णांक rc;

	rc = amd_pmc_send_cmd(pdev, 0);
	अगर (rc)
		dev_err(pdev->dev, "resume failed\n");

	amd_pmc_dump_रेजिस्टरs(pdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops amd_pmc_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(amd_pmc_suspend, amd_pmc_resume)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pmc_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, AMD_CPU_ID_CZN) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, AMD_CPU_ID_RN) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, AMD_CPU_ID_PCO) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, AMD_CPU_ID_RV) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक amd_pmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amd_pmc_dev *dev = &pmc;
	काष्ठा pci_dev *rdev;
	u32 base_addr_lo;
	u32 base_addr_hi;
	u64 base_addr;
	पूर्णांक err;
	u32 val;

	dev->dev = &pdev->dev;

	rdev = pci_get_करोमुख्य_bus_and_slot(0, 0, PCI_DEVFN(0, 0));
	अगर (!rdev || !pci_match_id(pmc_pci_ids, rdev)) अणु
		pci_dev_put(rdev);
		वापस -ENODEV;
	पूर्ण

	dev->cpu_id = rdev->device;
	err = pci_ग_लिखो_config_dword(rdev, AMD_PMC_SMU_INDEX_ADDRESS, AMD_PMC_BASE_ADDR_LO);
	अगर (err) अणु
		dev_err(dev->dev, "error writing to 0x%x\n", AMD_PMC_SMU_INDEX_ADDRESS);
		pci_dev_put(rdev);
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	err = pci_पढ़ो_config_dword(rdev, AMD_PMC_SMU_INDEX_DATA, &val);
	अगर (err) अणु
		pci_dev_put(rdev);
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	base_addr_lo = val & AMD_PMC_BASE_ADDR_HI_MASK;

	err = pci_ग_लिखो_config_dword(rdev, AMD_PMC_SMU_INDEX_ADDRESS, AMD_PMC_BASE_ADDR_HI);
	अगर (err) अणु
		dev_err(dev->dev, "error writing to 0x%x\n", AMD_PMC_SMU_INDEX_ADDRESS);
		pci_dev_put(rdev);
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	err = pci_पढ़ो_config_dword(rdev, AMD_PMC_SMU_INDEX_DATA, &val);
	अगर (err) अणु
		pci_dev_put(rdev);
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	base_addr_hi = val & AMD_PMC_BASE_ADDR_LO_MASK;
	pci_dev_put(rdev);
	base_addr = ((u64)base_addr_hi << 32 | base_addr_lo);

	dev->smu_base = devm_ioremap(dev->dev, base_addr, AMD_PMC_MAPPING_SIZE);
	अगर (!dev->smu_base)
		वापस -ENOMEM;

	dev->regbase = devm_ioremap(dev->dev, base_addr + AMD_PMC_BASE_ADDR_OFFSET,
				    AMD_PMC_MAPPING_SIZE);
	अगर (!dev->regbase)
		वापस -ENOMEM;

	amd_pmc_dump_रेजिस्टरs(dev);

	platक्रमm_set_drvdata(pdev, dev);
	amd_pmc_dbgfs_रेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक amd_pmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amd_pmc_dev *dev = platक्रमm_get_drvdata(pdev);

	amd_pmc_dbgfs_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id amd_pmc_acpi_ids[] = अणु
	अणु"AMDI0005", 0पूर्ण,
	अणु"AMD0004", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, amd_pmc_acpi_ids);

अटल काष्ठा platक्रमm_driver amd_pmc_driver = अणु
	.driver = अणु
		.name = "amd_pmc",
		.acpi_match_table = amd_pmc_acpi_ids,
		.pm = &amd_pmc_pm_ops,
	पूर्ण,
	.probe = amd_pmc_probe,
	.हटाओ = amd_pmc_हटाओ,
पूर्ण;
module_platक्रमm_driver(amd_pmc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("AMD PMC Driver");
