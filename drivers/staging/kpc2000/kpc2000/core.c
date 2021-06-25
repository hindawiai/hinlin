<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/kernel.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cdev.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>
#समावेश <linux/jअगरfies.h>
#समावेश "pcie.h"
#समावेश "uapi.h"

अटल DEFINE_IDA(card_num_ida);

/*******************************************************
 * SysFS Attributes
 ******************************************************/

अटल sमाप_प्रकार ssid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%016llx\n", pcard->ssid);
पूर्ण
अटल DEVICE_ATTR_RO(ssid);

अटल sमाप_प्रकार ddna_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%016llx\n", pcard->ddna);
पूर्ण
अटल DEVICE_ATTR_RO(ddna);

अटल sमाप_प्रकार card_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->card_id);
पूर्ण
अटल DEVICE_ATTR_RO(card_id);

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->hardware_revision);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार build_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->build_version);
पूर्ण
अटल DEVICE_ATTR_RO(build);

अटल sमाप_प्रकार build_date_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->build_datestamp);
पूर्ण
अटल DEVICE_ATTR_RO(build_date);

अटल sमाप_प्रकार build_समय_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->build_बारtamp);
पूर्ण
अटल DEVICE_ATTR_RO(build_समय);

अटल sमाप_प्रकार cpld_reg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);
	u64 val;

	val = पढ़ोq(pcard->sysinfo_regs_base + REG_CPLD_CONFIG);
	वापस प्र_लिखो(buf, "%016llx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(cpld_reg);

अटल sमाप_प्रकार cpld_reconfigure(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);
	अचिन्हित दीर्घ wr_val;
	पूर्णांक rv;

	rv = kम_से_अदीर्घ(buf, 0, &wr_val);
	अगर (rv < 0)
		वापस rv;
	अगर (wr_val > 7)
		वापस -EINVAL;

	wr_val = wr_val << 8;
	wr_val |= 0x1; // Set the "Configure Go" bit
	ग_लिखोq(wr_val, pcard->sysinfo_regs_base + REG_CPLD_CONFIG);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(cpld_reconfigure, 0220, शून्य, cpld_reconfigure);

अटल sमाप_प्रकार irq_mask_reg_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);
	u64 val;

	val = पढ़ोq(pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	वापस प्र_लिखो(buf, "%016llx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(irq_mask_reg);

अटल sमाप_प्रकार irq_active_reg_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);
	u64 val;

	val = पढ़ोq(pcard->sysinfo_regs_base + REG_INTERRUPT_ACTIVE);
	वापस प्र_लिखो(buf, "%016llx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(irq_active_reg);

अटल sमाप_प्रकार pcie_error_count_reg_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);
	u64 val;

	val = पढ़ोq(pcard->sysinfo_regs_base + REG_PCIE_ERROR_COUNT);
	वापस प्र_लिखो(buf, "%016llx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(pcie_error_count_reg);

अटल sमाप_प्रकार core_table_offset_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->core_table_offset);
पूर्ण
अटल DEVICE_ATTR_RO(core_table_offset);

अटल sमाप_प्रकार core_table_length_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kp2000_device *pcard = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%08x\n", pcard->core_table_length);
पूर्ण
अटल DEVICE_ATTR_RO(core_table_length);

अटल स्थिर काष्ठा attribute *kp_attr_list[] = अणु
	&dev_attr_ssid.attr,
	&dev_attr_ddna.attr,
	&dev_attr_card_id.attr,
	&dev_attr_hw_rev.attr,
	&dev_attr_build.attr,
	&dev_attr_build_date.attr,
	&dev_attr_build_समय.attr,
	&dev_attr_cpld_reg.attr,
	&dev_attr_cpld_reconfigure.attr,
	&dev_attr_irq_mask_reg.attr,
	&dev_attr_irq_active_reg.attr,
	&dev_attr_pcie_error_count_reg.attr,
	&dev_attr_core_table_offset.attr,
	&dev_attr_core_table_length.attr,
	शून्य,
पूर्ण;

/*******************************************************
 * Functions
 ******************************************************/

अटल व्योम रुको_and_पढ़ो_ssid(काष्ठा kp2000_device *pcard)
अणु
	u64 पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_FPGA_SSID);
	अचिन्हित दीर्घ समयout;

	अगर (पढ़ो_val & 0x8000000000000000UL) अणु
		pcard->ssid = पढ़ो_val;
		वापस;
	पूर्ण

	समयout = jअगरfies + (HZ * 2);
	करो अणु
		पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_FPGA_SSID);
		अगर (पढ़ो_val & 0x8000000000000000UL) अणु
			pcard->ssid = पढ़ो_val;
			वापस;
		पूर्ण
		cpu_relax();
		//schedule();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	dev_notice(&pcard->pdev->dev, "SSID didn't show up!\n");

	// Timed out रुकोing क्रम the SSID to show up, stick all zeros in the
	// value
	pcard->ssid = 0;
पूर्ण

अटल पूर्णांक  पढ़ो_प्रणाली_regs(काष्ठा kp2000_device *pcard)
अणु
	u64 पढ़ो_val;

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_MAGIC_NUMBER);
	अगर (पढ़ो_val != KP2000_MAGIC_VALUE) अणु
		dev_err(&pcard->pdev->dev,
			"Invalid magic!  Got: 0x%016llx  Want: 0x%016llx\n",
			पढ़ो_val, KP2000_MAGIC_VALUE);
		वापस -EILSEQ;
	पूर्ण

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_CARD_ID_AND_BUILD);
	pcard->card_id = (पढ़ो_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->build_version = (पढ़ो_val & 0x00000000FFFFFFFFUL) >> 0;

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_DATE_AND_TIME_STAMPS);
	pcard->build_datestamp = (पढ़ो_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->build_बारtamp = (पढ़ो_val & 0x00000000FFFFFFFFUL) >> 0;

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_CORE_TABLE_OFFSET);
	pcard->core_table_length = (पढ़ो_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->core_table_offset = (पढ़ो_val & 0x00000000FFFFFFFFUL) >> 0;

	रुको_and_पढ़ो_ssid(pcard);

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_FPGA_HW_ID);
	pcard->core_table_rev    = (पढ़ो_val & 0x0000000000000F00) >> 8;
	pcard->hardware_revision = (पढ़ो_val & 0x000000000000001F);

	पढ़ो_val = पढ़ोq(pcard->sysinfo_regs_base + REG_FPGA_DDNA);
	pcard->ddna = पढ़ो_val;

	dev_info(&pcard->pdev->dev,
		 "system_regs: %08x %08x %08x %08x  %02x  %d %d  %016llx  %016llx\n",
		 pcard->card_id,
		 pcard->build_version,
		 pcard->build_datestamp,
		 pcard->build_बारtamp,
		 pcard->hardware_revision,
		 pcard->core_table_rev,
		 pcard->core_table_length,
		 pcard->ssid,
		 pcard->ddna);

	अगर (pcard->core_table_rev > 1) अणु
		dev_err(&pcard->pdev->dev,
			"core table entry revision is higher than we can deal with, cannot continue with this card!\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t kp2000_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा kp2000_device *pcard = dev_id;

	ग_लिखोl(KPC_DMA_CARD_IRQ_ENABLE |
	       KPC_DMA_CARD_USER_INTERRUPT_MODE |
	       KPC_DMA_CARD_USER_INTERRUPT_ACTIVE,
	       pcard->dma_common_regs);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक kp2000_pcie_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err = 0;
	काष्ठा kp2000_device *pcard;
	अचिन्हित दीर्घ reg_bar_phys_addr;
	अचिन्हित दीर्घ reg_bar_phys_len;
	अचिन्हित दीर्घ dma_bar_phys_addr;
	अचिन्हित दीर्घ dma_bar_phys_len;
	u16 regval;

	pcard = kzalloc(माप(*pcard), GFP_KERNEL);
	अगर (!pcard)
		वापस -ENOMEM;
	dev_dbg(&pdev->dev, "probe: allocated struct kp2000_device @ %p\n",
		pcard);

	err = ida_simple_get(&card_num_ida, 1, पूर्णांक_उच्च, GFP_KERNEL);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "probe: failed to get card number (%d)\n",
			err);
		जाओ err_मुक्त_pcard;
	पूर्ण
	pcard->card_num = err;
	scnम_लिखो(pcard->name, 16, "kpcard%u", pcard->card_num);

	mutex_init(&pcard->sem);
	mutex_lock(&pcard->sem);

	pcard->pdev = pdev;
	pci_set_drvdata(pdev, pcard);

	err = pci_enable_device(pcard->pdev);
	अगर (err) अणु
		dev_err(&pcard->pdev->dev,
			"probe: failed to enable PCIE2000 PCIe device (%d)\n",
			err);
		जाओ err_हटाओ_ida;
	पूर्ण

	/* Setup the Register BAR */
	reg_bar_phys_addr = pci_resource_start(pcard->pdev, REG_BAR);
	reg_bar_phys_len = pci_resource_len(pcard->pdev, REG_BAR);

	pcard->regs_bar_base = ioremap(reg_bar_phys_addr, PAGE_SIZE);
	अगर (!pcard->regs_bar_base) अणु
		dev_err(&pcard->pdev->dev,
			"probe: REG_BAR could not remap memory to virtual space\n");
		err = -ENODEV;
		जाओ err_disable_device;
	पूर्ण
	dev_dbg(&pcard->pdev->dev,
		"probe: REG_BAR virt hardware address start [%p]\n",
		pcard->regs_bar_base);

	err = pci_request_region(pcard->pdev, REG_BAR, KP_DRIVER_NAME_KP2000);
	अगर (err) अणु
		dev_err(&pcard->pdev->dev,
			"probe: failed to acquire PCI region (%d)\n",
			err);
		err = -ENODEV;
		जाओ err_unmap_regs;
	पूर्ण

	pcard->regs_base_resource.start = reg_bar_phys_addr;
	pcard->regs_base_resource.end   = reg_bar_phys_addr +
					  reg_bar_phys_len - 1;
	pcard->regs_base_resource.flags = IORESOURCE_MEM;

	/* Setup the DMA BAR */
	dma_bar_phys_addr = pci_resource_start(pcard->pdev, DMA_BAR);
	dma_bar_phys_len = pci_resource_len(pcard->pdev, DMA_BAR);

	pcard->dma_bar_base = ioremap(dma_bar_phys_addr,
				      dma_bar_phys_len);
	अगर (!pcard->dma_bar_base) अणु
		dev_err(&pcard->pdev->dev,
			"probe: DMA_BAR could not remap memory to virtual space\n");
		err = -ENODEV;
		जाओ err_release_regs;
	पूर्ण
	dev_dbg(&pcard->pdev->dev,
		"probe: DMA_BAR virt hardware address start [%p]\n",
		pcard->dma_bar_base);

	pcard->dma_common_regs = pcard->dma_bar_base + KPC_DMA_COMMON_OFFSET;

	err = pci_request_region(pcard->pdev, DMA_BAR, "kp2000_pcie");
	अगर (err) अणु
		dev_err(&pcard->pdev->dev,
			"probe: failed to acquire PCI region (%d)\n", err);
		err = -ENODEV;
		जाओ err_unmap_dma;
	पूर्ण

	pcard->dma_base_resource.start = dma_bar_phys_addr;
	pcard->dma_base_resource.end   = dma_bar_phys_addr +
					 dma_bar_phys_len - 1;
	pcard->dma_base_resource.flags = IORESOURCE_MEM;

	/* Read System Regs */
	pcard->sysinfo_regs_base = pcard->regs_bar_base;
	err = पढ़ो_प्रणाली_regs(pcard);
	अगर (err)
		जाओ err_release_dma;

	// Disable all "user" पूर्णांकerrupts because they're not used yet.
	ग_लिखोq(0xFFFFFFFFFFFFFFFFUL,
	       pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);

	// let the card master PCIe
	pci_set_master(pcard->pdev);

	// enable IO and mem अगर not alपढ़ोy करोne
	pci_पढ़ो_config_word(pcard->pdev, PCI_COMMAND, &regval);
	regval |= (PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	pci_ग_लिखो_config_word(pcard->pdev, PCI_COMMAND, regval);

	// Clear relaxed ordering bit
	pcie_capability_clear_and_set_word(pcard->pdev, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_RELAX_EN, 0);

	// Set Max_Payload_Size and Max_Read_Request_Size
	regval = (0x0) << 5; // Max_Payload_Size = 128 B
	pcie_capability_clear_and_set_word(pcard->pdev, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_PAYLOAD, regval);
	regval = (0x0) << 12; // Max_Read_Request_Size = 128 B
	pcie_capability_clear_and_set_word(pcard->pdev, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_READRQ, regval);

	// Enable error reporting क्रम: Correctable Errors, Non-Fatal Errors,
	// Fatal Errors, Unsupported Requests
	pcie_capability_clear_and_set_word(pcard->pdev, PCI_EXP_DEVCTL, 0,
					   PCI_EXP_DEVCTL_CERE |
					   PCI_EXP_DEVCTL_NFERE |
					   PCI_EXP_DEVCTL_FERE |
					   PCI_EXP_DEVCTL_URRE);

	err = dma_set_mask(PCARD_TO_DEV(pcard), DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_err(&pcard->pdev->dev,
			"CANNOT use DMA mask %0llx\n", DMA_BIT_MASK(64));
		जाओ err_release_dma;
	पूर्ण
	dev_dbg(&pcard->pdev->dev,
		"Using DMA mask %0llx\n", dma_get_mask(PCARD_TO_DEV(pcard)));

	err = pci_enable_msi(pcard->pdev);
	अगर (err < 0)
		जाओ err_release_dma;

	err = request_irq(pcard->pdev->irq, kp2000_irq_handler, IRQF_SHARED,
			  pcard->name, pcard);
	अगर (err) अणु
		dev_err(&pcard->pdev->dev,
			"%s: failed to request_irq: %d\n", __func__, err);
		जाओ err_disable_msi;
	पूर्ण

	err = sysfs_create_files(&pdev->dev.kobj, kp_attr_list);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add sysfs files: %d\n", err);
		जाओ err_मुक्त_irq;
	पूर्ण

	err = kp2000_probe_cores(pcard);
	अगर (err)
		जाओ err_हटाओ_sysfs;

	/* Enable IRQs in HW */
	ग_लिखोl(KPC_DMA_CARD_IRQ_ENABLE | KPC_DMA_CARD_USER_INTERRUPT_MODE,
	       pcard->dma_common_regs);

	mutex_unlock(&pcard->sem);
	वापस 0;

err_हटाओ_sysfs:
	sysfs_हटाओ_files(&pdev->dev.kobj, kp_attr_list);
err_मुक्त_irq:
	मुक्त_irq(pcard->pdev->irq, pcard);
err_disable_msi:
	pci_disable_msi(pcard->pdev);
err_release_dma:
	pci_release_region(pdev, DMA_BAR);
err_unmap_dma:
	iounmap(pcard->dma_bar_base);
err_release_regs:
	pci_release_region(pdev, REG_BAR);
err_unmap_regs:
	iounmap(pcard->regs_bar_base);
err_disable_device:
	pci_disable_device(pcard->pdev);
err_हटाओ_ida:
	mutex_unlock(&pcard->sem);
	ida_simple_हटाओ(&card_num_ida, pcard->card_num);
err_मुक्त_pcard:
	kमुक्त(pcard);
	वापस err;
पूर्ण

अटल व्योम kp2000_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा kp2000_device *pcard = pci_get_drvdata(pdev);

	अगर (!pcard)
		वापस;

	mutex_lock(&pcard->sem);
	kp2000_हटाओ_cores(pcard);
	mfd_हटाओ_devices(PCARD_TO_DEV(pcard));
	sysfs_हटाओ_files(&pdev->dev.kobj, kp_attr_list);
	मुक्त_irq(pcard->pdev->irq, pcard);
	pci_disable_msi(pcard->pdev);
	अगर (pcard->dma_bar_base) अणु
		iounmap(pcard->dma_bar_base);
		pci_release_region(pdev, DMA_BAR);
		pcard->dma_bar_base = शून्य;
	पूर्ण
	अगर (pcard->regs_bar_base) अणु
		iounmap(pcard->regs_bar_base);
		pci_release_region(pdev, REG_BAR);
		pcard->regs_bar_base = शून्य;
	पूर्ण
	pci_disable_device(pcard->pdev);
	pci_set_drvdata(pdev, शून्य);
	mutex_unlock(&pcard->sem);
	ida_simple_हटाओ(&card_num_ida, pcard->card_num);
	kमुक्त(pcard);
पूर्ण

काष्ठा class *kpc_uio_class;
ATTRIBUTE_GROUPS(kpc_uio_class);

अटल स्थिर काष्ठा pci_device_id kp2000_pci_device_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_DAKTRONICS, PCI_DEVICE_ID_DAKTRONICS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_DAKTRONICS, PCI_DEVICE_ID_DAKTRONICS_KADOKA_P2KR0) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, kp2000_pci_device_ids);

अटल काष्ठा pci_driver kp2000_driver_inst = अणु
	.name =		"kp2000_pcie",
	.id_table =	kp2000_pci_device_ids,
	.probe =	kp2000_pcie_probe,
	.हटाओ =	kp2000_pcie_हटाओ,
पूर्ण;

अटल पूर्णांक __init kp2000_pcie_init(व्योम)
अणु
	kpc_uio_class = class_create(THIS_MODULE, "kpc_uio");
	अगर (IS_ERR(kpc_uio_class))
		वापस PTR_ERR(kpc_uio_class);

	kpc_uio_class->dev_groups = kpc_uio_class_groups;
	वापस pci_रेजिस्टर_driver(&kp2000_driver_inst);
पूर्ण
module_init(kp2000_pcie_init);

अटल व्योम __निकास kp2000_pcie_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&kp2000_driver_inst);
	class_destroy(kpc_uio_class);
	ida_destroy(&card_num_ida);
पूर्ण
module_निकास(kp2000_pcie_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lee.Brooke@Daktronics.com, Matt.Sickler@Daktronics.com");
MODULE_SOFTDEP("pre: uio post: kpc_nwl_dma kpc_i2c kpc_spi");
