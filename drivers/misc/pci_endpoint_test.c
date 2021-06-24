<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Host side test driver to test endpoपूर्णांक functionality
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

#समावेश <linux/pci_regs.h>

#समावेश <uapi/linux/pcitest.h>

#घोषणा DRV_MODULE_NAME				"pci-endpoint-test"

#घोषणा IRQ_TYPE_UNDEFINED			-1
#घोषणा IRQ_TYPE_LEGACY				0
#घोषणा IRQ_TYPE_MSI				1
#घोषणा IRQ_TYPE_MSIX				2

#घोषणा PCI_ENDPOINT_TEST_MAGIC			0x0

#घोषणा PCI_ENDPOINT_TEST_COMMAND		0x4
#घोषणा COMMAND_RAISE_LEGACY_IRQ		BIT(0)
#घोषणा COMMAND_RAISE_MSI_IRQ			BIT(1)
#घोषणा COMMAND_RAISE_MSIX_IRQ			BIT(2)
#घोषणा COMMAND_READ				BIT(3)
#घोषणा COMMAND_WRITE				BIT(4)
#घोषणा COMMAND_COPY				BIT(5)

#घोषणा PCI_ENDPOINT_TEST_STATUS		0x8
#घोषणा STATUS_READ_SUCCESS			BIT(0)
#घोषणा STATUS_READ_FAIL			BIT(1)
#घोषणा STATUS_WRITE_SUCCESS			BIT(2)
#घोषणा STATUS_WRITE_FAIL			BIT(3)
#घोषणा STATUS_COPY_SUCCESS			BIT(4)
#घोषणा STATUS_COPY_FAIL			BIT(5)
#घोषणा STATUS_IRQ_RAISED			BIT(6)
#घोषणा STATUS_SRC_ADDR_INVALID			BIT(7)
#घोषणा STATUS_DST_ADDR_INVALID			BIT(8)

#घोषणा PCI_ENDPOINT_TEST_LOWER_SRC_ADDR	0x0c
#घोषणा PCI_ENDPOINT_TEST_UPPER_SRC_ADDR	0x10

#घोषणा PCI_ENDPOINT_TEST_LOWER_DST_ADDR	0x14
#घोषणा PCI_ENDPOINT_TEST_UPPER_DST_ADDR	0x18

#घोषणा PCI_ENDPOINT_TEST_SIZE			0x1c
#घोषणा PCI_ENDPOINT_TEST_CHECKSUM		0x20

#घोषणा PCI_ENDPOINT_TEST_IRQ_TYPE		0x24
#घोषणा PCI_ENDPOINT_TEST_IRQ_NUMBER		0x28

#घोषणा PCI_ENDPOINT_TEST_FLAGS			0x2c
#घोषणा FLAG_USE_DMA				BIT(0)

#घोषणा PCI_DEVICE_ID_TI_AM654			0xb00c
#घोषणा PCI_DEVICE_ID_LS1088A			0x80c0

#घोषणा is_am654_pci_dev(pdev)		\
		((pdev)->device == PCI_DEVICE_ID_TI_AM654)

#घोषणा PCI_DEVICE_ID_RENESAS_R8A774A1		0x0028
#घोषणा PCI_DEVICE_ID_RENESAS_R8A774B1		0x002b
#घोषणा PCI_DEVICE_ID_RENESAS_R8A774C0		0x002d
#घोषणा PCI_DEVICE_ID_RENESAS_R8A774E1		0x0025

अटल DEFINE_IDA(pci_endpoपूर्णांक_test_ida);

#घोषणा to_endpoपूर्णांक_test(priv) container_of((priv), काष्ठा pci_endpoपूर्णांक_test, \
					    miscdev)

अटल bool no_msi;
module_param(no_msi, bool, 0444);
MODULE_PARM_DESC(no_msi, "Disable MSI interrupt in pci_endpoint_test");

अटल पूर्णांक irq_type = IRQ_TYPE_MSI;
module_param(irq_type, पूर्णांक, 0444);
MODULE_PARM_DESC(irq_type, "IRQ mode selection in pci_endpoint_test (0 - Legacy, 1 - MSI, 2 - MSI-X)");

क्रमागत pci_barno अणु
	BAR_0,
	BAR_1,
	BAR_2,
	BAR_3,
	BAR_4,
	BAR_5,
पूर्ण;

काष्ठा pci_endpoपूर्णांक_test अणु
	काष्ठा pci_dev	*pdev;
	व्योम __iomem	*base;
	व्योम __iomem	*bar[PCI_STD_NUM_BARS];
	काष्ठा completion irq_उठाओd;
	पूर्णांक		last_irq;
	पूर्णांक		num_irqs;
	पूर्णांक		irq_type;
	/* mutex to protect the ioctls */
	काष्ठा mutex	mutex;
	काष्ठा miscdevice miscdev;
	क्रमागत pci_barno test_reg_bar;
	माप_प्रकार alignment;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा pci_endpoपूर्णांक_test_data अणु
	क्रमागत pci_barno test_reg_bar;
	माप_प्रकार alignment;
	पूर्णांक irq_type;
पूर्ण;

अटल अंतरभूत u32 pci_endpoपूर्णांक_test_पढ़ोl(काष्ठा pci_endpoपूर्णांक_test *test,
					  u32 offset)
अणु
	वापस पढ़ोl(test->base + offset);
पूर्ण

अटल अंतरभूत व्योम pci_endpoपूर्णांक_test_ग_लिखोl(काष्ठा pci_endpoपूर्णांक_test *test,
					    u32 offset, u32 value)
अणु
	ग_लिखोl(value, test->base + offset);
पूर्ण

अटल अंतरभूत u32 pci_endpoपूर्णांक_test_bar_पढ़ोl(काष्ठा pci_endpoपूर्णांक_test *test,
					      पूर्णांक bar, पूर्णांक offset)
अणु
	वापस पढ़ोl(test->bar[bar] + offset);
पूर्ण

अटल अंतरभूत व्योम pci_endpoपूर्णांक_test_bar_ग_लिखोl(काष्ठा pci_endpoपूर्णांक_test *test,
						पूर्णांक bar, u32 offset, u32 value)
अणु
	ग_लिखोl(value, test->bar[bar] + offset);
पूर्ण

अटल irqवापस_t pci_endpoपूर्णांक_test_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_endpoपूर्णांक_test *test = dev_id;
	u32 reg;

	reg = pci_endpoपूर्णांक_test_पढ़ोl(test, PCI_ENDPOINT_TEST_STATUS);
	अगर (reg & STATUS_IRQ_RAISED) अणु
		test->last_irq = irq;
		complete(&test->irq_उठाओd);
		reg &= ~STATUS_IRQ_RAISED;
	पूर्ण
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_STATUS,
				 reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pci_endpoपूर्णांक_test_मुक्त_irq_vectors(काष्ठा pci_endpoपूर्णांक_test *test)
अणु
	काष्ठा pci_dev *pdev = test->pdev;

	pci_मुक्त_irq_vectors(pdev);
	test->irq_type = IRQ_TYPE_UNDEFINED;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_alloc_irq_vectors(काष्ठा pci_endpoपूर्णांक_test *test,
						पूर्णांक type)
अणु
	पूर्णांक irq = -1;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;
	bool res = true;

	चयन (type) अणु
	हाल IRQ_TYPE_LEGACY:
		irq = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_LEGACY);
		अगर (irq < 0)
			dev_err(dev, "Failed to get Legacy interrupt\n");
		अवरोध;
	हाल IRQ_TYPE_MSI:
		irq = pci_alloc_irq_vectors(pdev, 1, 32, PCI_IRQ_MSI);
		अगर (irq < 0)
			dev_err(dev, "Failed to get MSI interrupts\n");
		अवरोध;
	हाल IRQ_TYPE_MSIX:
		irq = pci_alloc_irq_vectors(pdev, 1, 2048, PCI_IRQ_MSIX);
		अगर (irq < 0)
			dev_err(dev, "Failed to get MSI-X interrupts\n");
		अवरोध;
	शेष:
		dev_err(dev, "Invalid IRQ type selected\n");
	पूर्ण

	अगर (irq < 0) अणु
		irq = 0;
		res = false;
	पूर्ण

	test->irq_type = type;
	test->num_irqs = irq;

	वापस res;
पूर्ण

अटल व्योम pci_endpoपूर्णांक_test_release_irq(काष्ठा pci_endpoपूर्णांक_test *test)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;

	क्रम (i = 0; i < test->num_irqs; i++)
		devm_मुक्त_irq(dev, pci_irq_vector(pdev, i), test);

	test->num_irqs = 0;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_request_irq(काष्ठा pci_endpoपूर्णांक_test *test)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;

	क्रम (i = 0; i < test->num_irqs; i++) अणु
		err = devm_request_irq(dev, pci_irq_vector(pdev, i),
				       pci_endpoपूर्णांक_test_irqhandler,
				       IRQF_SHARED, test->name, test);
		अगर (err)
			जाओ fail;
	पूर्ण

	वापस true;

fail:
	चयन (irq_type) अणु
	हाल IRQ_TYPE_LEGACY:
		dev_err(dev, "Failed to request IRQ %d for Legacy\n",
			pci_irq_vector(pdev, i));
		अवरोध;
	हाल IRQ_TYPE_MSI:
		dev_err(dev, "Failed to request IRQ %d for MSI %d\n",
			pci_irq_vector(pdev, i),
			i + 1);
		अवरोध;
	हाल IRQ_TYPE_MSIX:
		dev_err(dev, "Failed to request IRQ %d for MSI-X %d\n",
			pci_irq_vector(pdev, i),
			i + 1);
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_bar(काष्ठा pci_endpoपूर्णांक_test *test,
				  क्रमागत pci_barno barno)
अणु
	पूर्णांक j;
	u32 val;
	पूर्णांक size;
	काष्ठा pci_dev *pdev = test->pdev;

	अगर (!test->bar[barno])
		वापस false;

	size = pci_resource_len(pdev, barno);

	अगर (barno == test->test_reg_bar)
		size = 0x4;

	क्रम (j = 0; j < size; j += 4)
		pci_endpoपूर्णांक_test_bar_ग_लिखोl(test, barno, j, 0xA0A0A0A0);

	क्रम (j = 0; j < size; j += 4) अणु
		val = pci_endpoपूर्णांक_test_bar_पढ़ोl(test, barno, j);
		अगर (val != 0xA0A0A0A0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_legacy_irq(काष्ठा pci_endpoपूर्णांक_test *test)
अणु
	u32 val;

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_TYPE,
				 IRQ_TYPE_LEGACY);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, 0);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_RAISE_LEGACY_IRQ);
	val = रुको_क्रम_completion_समयout(&test->irq_उठाओd,
					  msecs_to_jअगरfies(1000));
	अगर (!val)
		वापस false;

	वापस true;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_msi_irq(काष्ठा pci_endpoपूर्णांक_test *test,
				       u16 msi_num, bool msix)
अणु
	u32 val;
	काष्ठा pci_dev *pdev = test->pdev;

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_TYPE,
				 msix == false ? IRQ_TYPE_MSI :
				 IRQ_TYPE_MSIX);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, msi_num);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_COMMAND,
				 msix == false ? COMMAND_RAISE_MSI_IRQ :
				 COMMAND_RAISE_MSIX_IRQ);
	val = रुको_क्रम_completion_समयout(&test->irq_उठाओd,
					  msecs_to_jअगरfies(1000));
	अगर (!val)
		वापस false;

	अगर (pci_irq_vector(pdev, msi_num - 1) == test->last_irq)
		वापस true;

	वापस false;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_copy(काष्ठा pci_endpoपूर्णांक_test *test,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा pci_endpoपूर्णांक_test_xfer_param param;
	bool ret = false;
	व्योम *src_addr;
	व्योम *dst_addr;
	u32 flags = 0;
	bool use_dma;
	माप_प्रकार size;
	dma_addr_t src_phys_addr;
	dma_addr_t dst_phys_addr;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;
	व्योम *orig_src_addr;
	dma_addr_t orig_src_phys_addr;
	व्योम *orig_dst_addr;
	dma_addr_t orig_dst_phys_addr;
	माप_प्रकार offset;
	माप_प्रकार alignment = test->alignment;
	पूर्णांक irq_type = test->irq_type;
	u32 src_crc32;
	u32 dst_crc32;
	पूर्णांक err;

	err = copy_from_user(&param, (व्योम __user *)arg, माप(param));
	अगर (err) अणु
		dev_err(dev, "Failed to get transfer param\n");
		वापस false;
	पूर्ण

	size = param.size;
	अगर (size > SIZE_MAX - alignment)
		जाओ err;

	use_dma = !!(param.flags & PCITEST_FLAGS_USE_DMA);
	अगर (use_dma)
		flags |= FLAG_USE_DMA;

	अगर (irq_type < IRQ_TYPE_LEGACY || irq_type > IRQ_TYPE_MSIX) अणु
		dev_err(dev, "Invalid IRQ type option\n");
		जाओ err;
	पूर्ण

	orig_src_addr = kzalloc(size + alignment, GFP_KERNEL);
	अगर (!orig_src_addr) अणु
		dev_err(dev, "Failed to allocate source buffer\n");
		ret = false;
		जाओ err;
	पूर्ण

	get_अक्रमom_bytes(orig_src_addr, size + alignment);
	orig_src_phys_addr = dma_map_single(dev, orig_src_addr,
					    size + alignment, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, orig_src_phys_addr)) अणु
		dev_err(dev, "failed to map source buffer address\n");
		ret = false;
		जाओ err_src_phys_addr;
	पूर्ण

	अगर (alignment && !IS_ALIGNED(orig_src_phys_addr, alignment)) अणु
		src_phys_addr = PTR_ALIGN(orig_src_phys_addr, alignment);
		offset = src_phys_addr - orig_src_phys_addr;
		src_addr = orig_src_addr + offset;
	पूर्ण अन्यथा अणु
		src_phys_addr = orig_src_phys_addr;
		src_addr = orig_src_addr;
	पूर्ण

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_LOWER_SRC_ADDR,
				 lower_32_bits(src_phys_addr));

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_UPPER_SRC_ADDR,
				 upper_32_bits(src_phys_addr));

	src_crc32 = crc32_le(~0, src_addr, size);

	orig_dst_addr = kzalloc(size + alignment, GFP_KERNEL);
	अगर (!orig_dst_addr) अणु
		dev_err(dev, "Failed to allocate destination address\n");
		ret = false;
		जाओ err_dst_addr;
	पूर्ण

	orig_dst_phys_addr = dma_map_single(dev, orig_dst_addr,
					    size + alignment, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, orig_dst_phys_addr)) अणु
		dev_err(dev, "failed to map destination buffer address\n");
		ret = false;
		जाओ err_dst_phys_addr;
	पूर्ण

	अगर (alignment && !IS_ALIGNED(orig_dst_phys_addr, alignment)) अणु
		dst_phys_addr = PTR_ALIGN(orig_dst_phys_addr, alignment);
		offset = dst_phys_addr - orig_dst_phys_addr;
		dst_addr = orig_dst_addr + offset;
	पूर्ण अन्यथा अणु
		dst_phys_addr = orig_dst_phys_addr;
		dst_addr = orig_dst_addr;
	पूर्ण

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_LOWER_DST_ADDR,
				 lower_32_bits(dst_phys_addr));
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_UPPER_DST_ADDR,
				 upper_32_bits(dst_phys_addr));

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_SIZE,
				 size);

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_FLAGS, flags);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_TYPE, irq_type);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, 1);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_COPY);

	रुको_क्रम_completion(&test->irq_उठाओd);

	dma_unmap_single(dev, orig_dst_phys_addr, size + alignment,
			 DMA_FROM_DEVICE);

	dst_crc32 = crc32_le(~0, dst_addr, size);
	अगर (dst_crc32 == src_crc32)
		ret = true;

err_dst_phys_addr:
	kमुक्त(orig_dst_addr);

err_dst_addr:
	dma_unmap_single(dev, orig_src_phys_addr, size + alignment,
			 DMA_TO_DEVICE);

err_src_phys_addr:
	kमुक्त(orig_src_addr);

err:
	वापस ret;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_ग_लिखो(काष्ठा pci_endpoपूर्णांक_test *test,
				    अचिन्हित दीर्घ arg)
अणु
	काष्ठा pci_endpoपूर्णांक_test_xfer_param param;
	bool ret = false;
	u32 flags = 0;
	bool use_dma;
	u32 reg;
	व्योम *addr;
	dma_addr_t phys_addr;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;
	व्योम *orig_addr;
	dma_addr_t orig_phys_addr;
	माप_प्रकार offset;
	माप_प्रकार alignment = test->alignment;
	पूर्णांक irq_type = test->irq_type;
	माप_प्रकार size;
	u32 crc32;
	पूर्णांक err;

	err = copy_from_user(&param, (व्योम __user *)arg, माप(param));
	अगर (err != 0) अणु
		dev_err(dev, "Failed to get transfer param\n");
		वापस false;
	पूर्ण

	size = param.size;
	अगर (size > SIZE_MAX - alignment)
		जाओ err;

	use_dma = !!(param.flags & PCITEST_FLAGS_USE_DMA);
	अगर (use_dma)
		flags |= FLAG_USE_DMA;

	अगर (irq_type < IRQ_TYPE_LEGACY || irq_type > IRQ_TYPE_MSIX) अणु
		dev_err(dev, "Invalid IRQ type option\n");
		जाओ err;
	पूर्ण

	orig_addr = kzalloc(size + alignment, GFP_KERNEL);
	अगर (!orig_addr) अणु
		dev_err(dev, "Failed to allocate address\n");
		ret = false;
		जाओ err;
	पूर्ण

	get_अक्रमom_bytes(orig_addr, size + alignment);

	orig_phys_addr = dma_map_single(dev, orig_addr, size + alignment,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, orig_phys_addr)) अणु
		dev_err(dev, "failed to map source buffer address\n");
		ret = false;
		जाओ err_phys_addr;
	पूर्ण

	अगर (alignment && !IS_ALIGNED(orig_phys_addr, alignment)) अणु
		phys_addr =  PTR_ALIGN(orig_phys_addr, alignment);
		offset = phys_addr - orig_phys_addr;
		addr = orig_addr + offset;
	पूर्ण अन्यथा अणु
		phys_addr = orig_phys_addr;
		addr = orig_addr;
	पूर्ण

	crc32 = crc32_le(~0, addr, size);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_CHECKSUM,
				 crc32);

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_LOWER_SRC_ADDR,
				 lower_32_bits(phys_addr));
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_UPPER_SRC_ADDR,
				 upper_32_bits(phys_addr));

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_SIZE, size);

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_FLAGS, flags);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_TYPE, irq_type);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, 1);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_READ);

	रुको_क्रम_completion(&test->irq_उठाओd);

	reg = pci_endpoपूर्णांक_test_पढ़ोl(test, PCI_ENDPOINT_TEST_STATUS);
	अगर (reg & STATUS_READ_SUCCESS)
		ret = true;

	dma_unmap_single(dev, orig_phys_addr, size + alignment,
			 DMA_TO_DEVICE);

err_phys_addr:
	kमुक्त(orig_addr);

err:
	वापस ret;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_पढ़ो(काष्ठा pci_endpoपूर्णांक_test *test,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा pci_endpoपूर्णांक_test_xfer_param param;
	bool ret = false;
	u32 flags = 0;
	bool use_dma;
	माप_प्रकार size;
	व्योम *addr;
	dma_addr_t phys_addr;
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;
	व्योम *orig_addr;
	dma_addr_t orig_phys_addr;
	माप_प्रकार offset;
	माप_प्रकार alignment = test->alignment;
	पूर्णांक irq_type = test->irq_type;
	u32 crc32;
	पूर्णांक err;

	err = copy_from_user(&param, (व्योम __user *)arg, माप(param));
	अगर (err) अणु
		dev_err(dev, "Failed to get transfer param\n");
		वापस false;
	पूर्ण

	size = param.size;
	अगर (size > SIZE_MAX - alignment)
		जाओ err;

	use_dma = !!(param.flags & PCITEST_FLAGS_USE_DMA);
	अगर (use_dma)
		flags |= FLAG_USE_DMA;

	अगर (irq_type < IRQ_TYPE_LEGACY || irq_type > IRQ_TYPE_MSIX) अणु
		dev_err(dev, "Invalid IRQ type option\n");
		जाओ err;
	पूर्ण

	orig_addr = kzalloc(size + alignment, GFP_KERNEL);
	अगर (!orig_addr) अणु
		dev_err(dev, "Failed to allocate destination address\n");
		ret = false;
		जाओ err;
	पूर्ण

	orig_phys_addr = dma_map_single(dev, orig_addr, size + alignment,
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, orig_phys_addr)) अणु
		dev_err(dev, "failed to map source buffer address\n");
		ret = false;
		जाओ err_phys_addr;
	पूर्ण

	अगर (alignment && !IS_ALIGNED(orig_phys_addr, alignment)) अणु
		phys_addr = PTR_ALIGN(orig_phys_addr, alignment);
		offset = phys_addr - orig_phys_addr;
		addr = orig_addr + offset;
	पूर्ण अन्यथा अणु
		phys_addr = orig_phys_addr;
		addr = orig_addr;
	पूर्ण

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_LOWER_DST_ADDR,
				 lower_32_bits(phys_addr));
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_UPPER_DST_ADDR,
				 upper_32_bits(phys_addr));

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_SIZE, size);

	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_FLAGS, flags);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_TYPE, irq_type);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_IRQ_NUMBER, 1);
	pci_endpoपूर्णांक_test_ग_लिखोl(test, PCI_ENDPOINT_TEST_COMMAND,
				 COMMAND_WRITE);

	रुको_क्रम_completion(&test->irq_उठाओd);

	dma_unmap_single(dev, orig_phys_addr, size + alignment,
			 DMA_FROM_DEVICE);

	crc32 = crc32_le(~0, addr, size);
	अगर (crc32 == pci_endpoपूर्णांक_test_पढ़ोl(test, PCI_ENDPOINT_TEST_CHECKSUM))
		ret = true;

err_phys_addr:
	kमुक्त(orig_addr);
err:
	वापस ret;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_clear_irq(काष्ठा pci_endpoपूर्णांक_test *test)
अणु
	pci_endpoपूर्णांक_test_release_irq(test);
	pci_endpoपूर्णांक_test_मुक्त_irq_vectors(test);
	वापस true;
पूर्ण

अटल bool pci_endpoपूर्णांक_test_set_irq(काष्ठा pci_endpoपूर्णांक_test *test,
				      पूर्णांक req_irq_type)
अणु
	काष्ठा pci_dev *pdev = test->pdev;
	काष्ठा device *dev = &pdev->dev;

	अगर (req_irq_type < IRQ_TYPE_LEGACY || req_irq_type > IRQ_TYPE_MSIX) अणु
		dev_err(dev, "Invalid IRQ type option\n");
		वापस false;
	पूर्ण

	अगर (test->irq_type == req_irq_type)
		वापस true;

	pci_endpoपूर्णांक_test_release_irq(test);
	pci_endpoपूर्णांक_test_मुक्त_irq_vectors(test);

	अगर (!pci_endpoपूर्णांक_test_alloc_irq_vectors(test, req_irq_type))
		जाओ err;

	अगर (!pci_endpoपूर्णांक_test_request_irq(test))
		जाओ err;

	वापस true;

err:
	pci_endpoपूर्णांक_test_मुक्त_irq_vectors(test);
	वापस false;
पूर्ण

अटल दीर्घ pci_endpoपूर्णांक_test_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -EINVAL;
	क्रमागत pci_barno bar;
	काष्ठा pci_endpoपूर्णांक_test *test = to_endpoपूर्णांक_test(file->निजी_data);
	काष्ठा pci_dev *pdev = test->pdev;

	mutex_lock(&test->mutex);
	चयन (cmd) अणु
	हाल PCITEST_BAR:
		bar = arg;
		अगर (bar > BAR_5)
			जाओ ret;
		अगर (is_am654_pci_dev(pdev) && bar == BAR_0)
			जाओ ret;
		ret = pci_endpoपूर्णांक_test_bar(test, bar);
		अवरोध;
	हाल PCITEST_LEGACY_IRQ:
		ret = pci_endpoपूर्णांक_test_legacy_irq(test);
		अवरोध;
	हाल PCITEST_MSI:
	हाल PCITEST_MSIX:
		ret = pci_endpoपूर्णांक_test_msi_irq(test, arg, cmd == PCITEST_MSIX);
		अवरोध;
	हाल PCITEST_WRITE:
		ret = pci_endpoपूर्णांक_test_ग_लिखो(test, arg);
		अवरोध;
	हाल PCITEST_READ:
		ret = pci_endpoपूर्णांक_test_पढ़ो(test, arg);
		अवरोध;
	हाल PCITEST_COPY:
		ret = pci_endpoपूर्णांक_test_copy(test, arg);
		अवरोध;
	हाल PCITEST_SET_IRQTYPE:
		ret = pci_endpoपूर्णांक_test_set_irq(test, arg);
		अवरोध;
	हाल PCITEST_GET_IRQTYPE:
		ret = irq_type;
		अवरोध;
	हाल PCITEST_CLEAR_IRQ:
		ret = pci_endpoपूर्णांक_test_clear_irq(test);
		अवरोध;
	पूर्ण

ret:
	mutex_unlock(&test->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations pci_endpoपूर्णांक_test_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = pci_endpoपूर्णांक_test_ioctl,
पूर्ण;

अटल पूर्णांक pci_endpoपूर्णांक_test_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	पूर्णांक id;
	अक्षर name[24];
	क्रमागत pci_barno bar;
	व्योम __iomem *base;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_endpoपूर्णांक_test *test;
	काष्ठा pci_endpoपूर्णांक_test_data *data;
	क्रमागत pci_barno test_reg_bar = BAR_0;
	काष्ठा miscdevice *misc_device;

	अगर (pci_is_bridge(pdev))
		वापस -ENODEV;

	test = devm_kzalloc(dev, माप(*test), GFP_KERNEL);
	अगर (!test)
		वापस -ENOMEM;

	test->test_reg_bar = 0;
	test->alignment = 0;
	test->pdev = pdev;
	test->irq_type = IRQ_TYPE_UNDEFINED;

	अगर (no_msi)
		irq_type = IRQ_TYPE_LEGACY;

	data = (काष्ठा pci_endpoपूर्णांक_test_data *)ent->driver_data;
	अगर (data) अणु
		test_reg_bar = data->test_reg_bar;
		test->test_reg_bar = test_reg_bar;
		test->alignment = data->alignment;
		irq_type = data->irq_type;
	पूर्ण

	init_completion(&test->irq_उठाओd);
	mutex_init(&test->mutex);

	अगर ((dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48)) != 0) &&
	    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)) != 0) अणु
		dev_err(dev, "Cannot set DMA mask\n");
		वापस -EINVAL;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Cannot enable PCI device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (err) अणु
		dev_err(dev, "Cannot obtain PCI resources\n");
		जाओ err_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	अगर (!pci_endpoपूर्णांक_test_alloc_irq_vectors(test, irq_type)) अणु
		err = -EINVAL;
		जाओ err_disable_irq;
	पूर्ण

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		अगर (pci_resource_flags(pdev, bar) & IORESOURCE_MEM) अणु
			base = pci_ioremap_bar(pdev, bar);
			अगर (!base) अणु
				dev_err(dev, "Failed to read BAR%d\n", bar);
				WARN_ON(bar == test_reg_bar);
			पूर्ण
			test->bar[bar] = base;
		पूर्ण
	पूर्ण

	test->base = test->bar[test_reg_bar];
	अगर (!test->base) अणु
		err = -ENOMEM;
		dev_err(dev, "Cannot perform PCI test without BAR%d\n",
			test_reg_bar);
		जाओ err_iounmap;
	पूर्ण

	pci_set_drvdata(pdev, test);

	id = ida_simple_get(&pci_endpoपूर्णांक_test_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		err = id;
		dev_err(dev, "Unable to get id\n");
		जाओ err_iounmap;
	पूर्ण

	snम_लिखो(name, माप(name), DRV_MODULE_NAME ".%d", id);
	test->name = kstrdup(name, GFP_KERNEL);
	अगर (!test->name) अणु
		err = -ENOMEM;
		जाओ err_ida_हटाओ;
	पूर्ण

	अगर (!pci_endpoपूर्णांक_test_request_irq(test)) अणु
		err = -EINVAL;
		जाओ err_kमुक्त_test_name;
	पूर्ण

	misc_device = &test->miscdev;
	misc_device->minor = MISC_DYNAMIC_MINOR;
	misc_device->name = kstrdup(name, GFP_KERNEL);
	अगर (!misc_device->name) अणु
		err = -ENOMEM;
		जाओ err_release_irq;
	पूर्ण
	misc_device->fops = &pci_endpoपूर्णांक_test_fops,

	err = misc_रेजिस्टर(misc_device);
	अगर (err) अणु
		dev_err(dev, "Failed to register device\n");
		जाओ err_kमुक्त_name;
	पूर्ण

	वापस 0;

err_kमुक्त_name:
	kमुक्त(misc_device->name);

err_release_irq:
	pci_endpoपूर्णांक_test_release_irq(test);

err_kमुक्त_test_name:
	kमुक्त(test->name);

err_ida_हटाओ:
	ida_simple_हटाओ(&pci_endpoपूर्णांक_test_ida, id);

err_iounmap:
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		अगर (test->bar[bar])
			pci_iounmap(pdev, test->bar[bar]);
	पूर्ण

err_disable_irq:
	pci_endpoपूर्णांक_test_मुक्त_irq_vectors(test);
	pci_release_regions(pdev);

err_disable_pdev:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम pci_endpoपूर्णांक_test_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक id;
	क्रमागत pci_barno bar;
	काष्ठा pci_endpoपूर्णांक_test *test = pci_get_drvdata(pdev);
	काष्ठा miscdevice *misc_device = &test->miscdev;

	अगर (माला_पूछो(misc_device->name, DRV_MODULE_NAME ".%d", &id) != 1)
		वापस;
	अगर (id < 0)
		वापस;

	misc_deरेजिस्टर(&test->miscdev);
	kमुक्त(misc_device->name);
	kमुक्त(test->name);
	ida_simple_हटाओ(&pci_endpoपूर्णांक_test_ida, id);
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		अगर (test->bar[bar])
			pci_iounmap(pdev, test->bar[bar]);
	पूर्ण

	pci_endpoपूर्णांक_test_release_irq(test);
	pci_endpoपूर्णांक_test_मुक्त_irq_vectors(test);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_endpoपूर्णांक_test_data शेष_data = अणु
	.test_reg_bar = BAR_0,
	.alignment = SZ_4K,
	.irq_type = IRQ_TYPE_MSI,
पूर्ण;

अटल स्थिर काष्ठा pci_endpoपूर्णांक_test_data am654_data = अणु
	.test_reg_bar = BAR_2,
	.alignment = SZ_64K,
	.irq_type = IRQ_TYPE_MSI,
पूर्ण;

अटल स्थिर काष्ठा pci_endpoपूर्णांक_test_data j721e_data = अणु
	.alignment = 256,
	.irq_type = IRQ_TYPE_MSI,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_endpoपूर्णांक_test_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_DRA74x),
	  .driver_data = (kernel_uदीर्घ_t)&शेष_data,
	पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_DRA72x),
	  .driver_data = (kernel_uदीर्घ_t)&शेष_data,
	पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, 0x81c0),
	  .driver_data = (kernel_uदीर्घ_t)&शेष_data,
	पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, PCI_DEVICE_ID_LS1088A),
	  .driver_data = (kernel_uदीर्घ_t)&शेष_data,
	पूर्ण,
	अणु PCI_DEVICE_DATA(SYNOPSYS, EDDA, शून्य) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_AM654),
	  .driver_data = (kernel_uदीर्घ_t)&am654_data
	पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_RENESAS, PCI_DEVICE_ID_RENESAS_R8A774A1),पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_RENESAS, PCI_DEVICE_ID_RENESAS_R8A774B1),पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_RENESAS, PCI_DEVICE_ID_RENESAS_R8A774C0),पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_RENESAS, PCI_DEVICE_ID_RENESAS_R8A774E1),पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_J721E),
	  .driver_data = (kernel_uदीर्घ_t)&j721e_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_endpoपूर्णांक_test_tbl);

अटल काष्ठा pci_driver pci_endpoपूर्णांक_test_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= pci_endpoपूर्णांक_test_tbl,
	.probe		= pci_endpoपूर्णांक_test_probe,
	.हटाओ		= pci_endpoपूर्णांक_test_हटाओ,
पूर्ण;
module_pci_driver(pci_endpoपूर्णांक_test_driver);

MODULE_DESCRIPTION("PCI ENDPOINT TEST HOST DRIVER");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
