<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test driver to test endpoपूर्णांक functionality
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/अक्रमom.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/pci_regs.h>

#घोषणा IRQ_TYPE_LEGACY			0
#घोषणा IRQ_TYPE_MSI			1
#घोषणा IRQ_TYPE_MSIX			2

#घोषणा COMMAND_RAISE_LEGACY_IRQ	BIT(0)
#घोषणा COMMAND_RAISE_MSI_IRQ		BIT(1)
#घोषणा COMMAND_RAISE_MSIX_IRQ		BIT(2)
#घोषणा COMMAND_READ			BIT(3)
#घोषणा COMMAND_WRITE			BIT(4)
#घोषणा COMMAND_COPY			BIT(5)

#घोषणा STATUS_READ_SUCCESS		BIT(0)
#घोषणा STATUS_READ_FAIL		BIT(1)
#घोषणा STATUS_WRITE_SUCCESS		BIT(2)
#घोषणा STATUS_WRITE_FAIL		BIT(3)
#घोषणा STATUS_COPY_SUCCESS		BIT(4)
#घोषणा STATUS_COPY_FAIL		BIT(5)
#घोषणा STATUS_IRQ_RAISED		BIT(6)
#घोषणा STATUS_SRC_ADDR_INVALID		BIT(7)
#घोषणा STATUS_DST_ADDR_INVALID		BIT(8)

#घोषणा FLAG_USE_DMA			BIT(0)

#घोषणा TIMER_RESOLUTION		1

अटल काष्ठा workqueue_काष्ठा *kpcitest_workqueue;

काष्ठा pci_epf_test अणु
	व्योम			*reg[PCI_STD_NUM_BARS];
	काष्ठा pci_epf		*epf;
	क्रमागत pci_barno		test_reg_bar;
	माप_प्रकार			msix_table_offset;
	काष्ठा delayed_work	cmd_handler;
	काष्ठा dma_chan		*dma_chan;
	काष्ठा completion	transfer_complete;
	bool			dma_supported;
	स्थिर काष्ठा pci_epc_features *epc_features;
पूर्ण;

काष्ठा pci_epf_test_reg अणु
	u32	magic;
	u32	command;
	u32	status;
	u64	src_addr;
	u64	dst_addr;
	u32	size;
	u32	checksum;
	u32	irq_type;
	u32	irq_number;
	u32	flags;
पूर्ण __packed;

अटल काष्ठा pci_epf_header test_header = अणु
	.venकरोrid	= PCI_ANY_ID,
	.deviceid	= PCI_ANY_ID,
	.baseclass_code = PCI_CLASS_OTHERS,
	.पूर्णांकerrupt_pin	= PCI_INTERRUPT_INTA,
पूर्ण;

अटल माप_प्रकार bar_size[] = अणु 512, 512, 1024, 16384, 131072, 1048576 पूर्ण;

अटल व्योम pci_epf_test_dma_callback(व्योम *param)
अणु
	काष्ठा pci_epf_test *epf_test = param;

	complete(&epf_test->transfer_complete);
पूर्ण

/**
 * pci_epf_test_data_transfer() - Function that uses dmaengine API to transfer
 *				  data between PCIe EP and remote PCIe RC
 * @epf_test: the EPF test device that perक्रमms the data transfer operation
 * @dma_dst: The destination address of the data transfer. It can be a physical
 *	     address given by pci_epc_mem_alloc_addr or DMA mapping APIs.
 * @dma_src: The source address of the data transfer. It can be a physical
 *	     address given by pci_epc_mem_alloc_addr or DMA mapping APIs.
 * @len: The size of the data transfer
 *
 * Function that uses dmaengine API to transfer data between PCIe EP and remote
 * PCIe RC. The source and destination address can be a physical address given
 * by pci_epc_mem_alloc_addr or the one obtained using DMA mapping APIs.
 *
 * The function वापसs '0' on success and negative value on failure.
 */
अटल पूर्णांक pci_epf_test_data_transfer(काष्ठा pci_epf_test *epf_test,
				      dma_addr_t dma_dst, dma_addr_t dma_src,
				      माप_प्रकार len)
अणु
	क्रमागत dma_ctrl_flags flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	काष्ठा dma_chan *chan = epf_test->dma_chan;
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा device *dev = &epf->dev;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(chan)) अणु
		dev_err(dev, "Invalid DMA memcpy channel\n");
		वापस -EINVAL;
	पूर्ण

	tx = dmaengine_prep_dma_स_नकल(chan, dma_dst, dma_src, len, flags);
	अगर (!tx) अणु
		dev_err(dev, "Failed to prepare DMA memcpy\n");
		वापस -EIO;
	पूर्ण

	tx->callback = pci_epf_test_dma_callback;
	tx->callback_param = epf_test;
	cookie = tx->tx_submit(tx);
	reinit_completion(&epf_test->transfer_complete);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(dev, "Failed to do DMA tx_submit %d\n", cookie);
		वापस -EIO;
	पूर्ण

	dma_async_issue_pending(chan);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&epf_test->transfer_complete);
	अगर (ret < 0) अणु
		dmaengine_terminate_sync(chan);
		dev_err(dev, "DMA wait_for_completion_timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pci_epf_test_init_dma_chan() - Function to initialize EPF test DMA channel
 * @epf_test: the EPF test device that perक्रमms data transfer operation
 *
 * Function to initialize EPF test DMA channel.
 */
अटल पूर्णांक pci_epf_test_init_dma_chan(काष्ठा pci_epf_test *epf_test)
अणु
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा dma_chan *dma_chan;
	dma_cap_mask_t mask;
	पूर्णांक ret;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dma_chan = dma_request_chan_by_mask(&mask);
	अगर (IS_ERR(dma_chan)) अणु
		ret = PTR_ERR(dma_chan);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get DMA channel\n");
		वापस ret;
	पूर्ण
	init_completion(&epf_test->transfer_complete);

	epf_test->dma_chan = dma_chan;

	वापस 0;
पूर्ण

/**
 * pci_epf_test_clean_dma_chan() - Function to cleanup EPF test DMA channel
 * @epf_test: the EPF test device that perक्रमms data transfer operation
 *
 * Helper to cleanup EPF test DMA channel.
 */
अटल व्योम pci_epf_test_clean_dma_chan(काष्ठा pci_epf_test *epf_test)
अणु
	अगर (!epf_test->dma_supported)
		वापस;

	dma_release_channel(epf_test->dma_chan);
	epf_test->dma_chan = शून्य;
पूर्ण

अटल व्योम pci_epf_test_prपूर्णांक_rate(स्थिर अक्षर *ops, u64 size,
				    काष्ठा बारpec64 *start,
				    काष्ठा बारpec64 *end, bool dma)
अणु
	काष्ठा बारpec64 ts;
	u64 rate, ns;

	ts = बारpec64_sub(*end, *start);

	/* convert both size (stored in 'rate') and time in terms of 'ns' */
	ns = बारpec64_to_ns(&ts);
	rate = size * NSEC_PER_SEC;

	/* Divide both size (stored in 'rate') and ns by a common factor */
	जबतक (ns > अच_पूर्णांक_उच्च) अणु
		rate >>= 1;
		ns >>= 1;
	पूर्ण

	अगर (!ns)
		वापस;

	/* calculate the rate */
	करो_भाग(rate, (uपूर्णांक32_t)ns);

	pr_info("\n%s => Size: %llu bytes\t DMA: %s\t Time: %llu.%09u seconds\t"
		"Rate: %llu KB/s\n", ops, size, dma ? "YES" : "NO",
		(u64)ts.tv_sec, (u32)ts.tv_nsec, rate / 1024);
पूर्ण

अटल पूर्णांक pci_epf_test_copy(काष्ठा pci_epf_test *epf_test)
अणु
	पूर्णांक ret;
	bool use_dma;
	व्योम __iomem *src_addr;
	व्योम __iomem *dst_addr;
	phys_addr_t src_phys_addr;
	phys_addr_t dst_phys_addr;
	काष्ठा बारpec64 start, end;
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epc *epc = epf->epc;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	काष्ठा pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	src_addr = pci_epc_mem_alloc_addr(epc, &src_phys_addr, reg->size);
	अगर (!src_addr) अणु
		dev_err(dev, "Failed to allocate source address\n");
		reg->status = STATUS_SRC_ADDR_INVALID;
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = pci_epc_map_addr(epc, epf->func_no, src_phys_addr, reg->src_addr,
			       reg->size);
	अगर (ret) अणु
		dev_err(dev, "Failed to map source address\n");
		reg->status = STATUS_SRC_ADDR_INVALID;
		जाओ err_src_addr;
	पूर्ण

	dst_addr = pci_epc_mem_alloc_addr(epc, &dst_phys_addr, reg->size);
	अगर (!dst_addr) अणु
		dev_err(dev, "Failed to allocate destination address\n");
		reg->status = STATUS_DST_ADDR_INVALID;
		ret = -ENOMEM;
		जाओ err_src_map_addr;
	पूर्ण

	ret = pci_epc_map_addr(epc, epf->func_no, dst_phys_addr, reg->dst_addr,
			       reg->size);
	अगर (ret) अणु
		dev_err(dev, "Failed to map destination address\n");
		reg->status = STATUS_DST_ADDR_INVALID;
		जाओ err_dst_addr;
	पूर्ण

	kसमय_get_ts64(&start);
	use_dma = !!(reg->flags & FLAG_USE_DMA);
	अगर (use_dma) अणु
		अगर (!epf_test->dma_supported) अणु
			dev_err(dev, "Cannot transfer data using DMA\n");
			ret = -EINVAL;
			जाओ err_map_addr;
		पूर्ण

		ret = pci_epf_test_data_transfer(epf_test, dst_phys_addr,
						 src_phys_addr, reg->size);
		अगर (ret)
			dev_err(dev, "Data transfer failed\n");
	पूर्ण अन्यथा अणु
		स_नकल(dst_addr, src_addr, reg->size);
	पूर्ण
	kसमय_get_ts64(&end);
	pci_epf_test_prपूर्णांक_rate("COPY", reg->size, &start, &end, use_dma);

err_map_addr:
	pci_epc_unmap_addr(epc, epf->func_no, dst_phys_addr);

err_dst_addr:
	pci_epc_mem_मुक्त_addr(epc, dst_phys_addr, dst_addr, reg->size);

err_src_map_addr:
	pci_epc_unmap_addr(epc, epf->func_no, src_phys_addr);

err_src_addr:
	pci_epc_mem_मुक्त_addr(epc, src_phys_addr, src_addr, reg->size);

err:
	वापस ret;
पूर्ण

अटल पूर्णांक pci_epf_test_पढ़ो(काष्ठा pci_epf_test *epf_test)
अणु
	पूर्णांक ret;
	व्योम __iomem *src_addr;
	व्योम *buf;
	u32 crc32;
	bool use_dma;
	phys_addr_t phys_addr;
	phys_addr_t dst_phys_addr;
	काष्ठा बारpec64 start, end;
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epc *epc = epf->epc;
	काष्ठा device *dma_dev = epf->epc->dev.parent;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	काष्ठा pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	src_addr = pci_epc_mem_alloc_addr(epc, &phys_addr, reg->size);
	अगर (!src_addr) अणु
		dev_err(dev, "Failed to allocate address\n");
		reg->status = STATUS_SRC_ADDR_INVALID;
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = pci_epc_map_addr(epc, epf->func_no, phys_addr, reg->src_addr,
			       reg->size);
	अगर (ret) अणु
		dev_err(dev, "Failed to map address\n");
		reg->status = STATUS_SRC_ADDR_INVALID;
		जाओ err_addr;
	पूर्ण

	buf = kzalloc(reg->size, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_map_addr;
	पूर्ण

	use_dma = !!(reg->flags & FLAG_USE_DMA);
	अगर (use_dma) अणु
		अगर (!epf_test->dma_supported) अणु
			dev_err(dev, "Cannot transfer data using DMA\n");
			ret = -EINVAL;
			जाओ err_dma_map;
		पूर्ण

		dst_phys_addr = dma_map_single(dma_dev, buf, reg->size,
					       DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dma_dev, dst_phys_addr)) अणु
			dev_err(dev, "Failed to map destination buffer addr\n");
			ret = -ENOMEM;
			जाओ err_dma_map;
		पूर्ण

		kसमय_get_ts64(&start);
		ret = pci_epf_test_data_transfer(epf_test, dst_phys_addr,
						 phys_addr, reg->size);
		अगर (ret)
			dev_err(dev, "Data transfer failed\n");
		kसमय_get_ts64(&end);

		dma_unmap_single(dma_dev, dst_phys_addr, reg->size,
				 DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		kसमय_get_ts64(&start);
		स_नकल_fromio(buf, src_addr, reg->size);
		kसमय_get_ts64(&end);
	पूर्ण

	pci_epf_test_prपूर्णांक_rate("READ", reg->size, &start, &end, use_dma);

	crc32 = crc32_le(~0, buf, reg->size);
	अगर (crc32 != reg->checksum)
		ret = -EIO;

err_dma_map:
	kमुक्त(buf);

err_map_addr:
	pci_epc_unmap_addr(epc, epf->func_no, phys_addr);

err_addr:
	pci_epc_mem_मुक्त_addr(epc, phys_addr, src_addr, reg->size);

err:
	वापस ret;
पूर्ण

अटल पूर्णांक pci_epf_test_ग_लिखो(काष्ठा pci_epf_test *epf_test)
अणु
	पूर्णांक ret;
	व्योम __iomem *dst_addr;
	व्योम *buf;
	bool use_dma;
	phys_addr_t phys_addr;
	phys_addr_t src_phys_addr;
	काष्ठा बारpec64 start, end;
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epc *epc = epf->epc;
	काष्ठा device *dma_dev = epf->epc->dev.parent;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	काष्ठा pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	dst_addr = pci_epc_mem_alloc_addr(epc, &phys_addr, reg->size);
	अगर (!dst_addr) अणु
		dev_err(dev, "Failed to allocate address\n");
		reg->status = STATUS_DST_ADDR_INVALID;
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = pci_epc_map_addr(epc, epf->func_no, phys_addr, reg->dst_addr,
			       reg->size);
	अगर (ret) अणु
		dev_err(dev, "Failed to map address\n");
		reg->status = STATUS_DST_ADDR_INVALID;
		जाओ err_addr;
	पूर्ण

	buf = kzalloc(reg->size, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_map_addr;
	पूर्ण

	get_अक्रमom_bytes(buf, reg->size);
	reg->checksum = crc32_le(~0, buf, reg->size);

	use_dma = !!(reg->flags & FLAG_USE_DMA);
	अगर (use_dma) अणु
		अगर (!epf_test->dma_supported) अणु
			dev_err(dev, "Cannot transfer data using DMA\n");
			ret = -EINVAL;
			जाओ err_map_addr;
		पूर्ण

		src_phys_addr = dma_map_single(dma_dev, buf, reg->size,
					       DMA_TO_DEVICE);
		अगर (dma_mapping_error(dma_dev, src_phys_addr)) अणु
			dev_err(dev, "Failed to map source buffer addr\n");
			ret = -ENOMEM;
			जाओ err_dma_map;
		पूर्ण

		kसमय_get_ts64(&start);
		ret = pci_epf_test_data_transfer(epf_test, phys_addr,
						 src_phys_addr, reg->size);
		अगर (ret)
			dev_err(dev, "Data transfer failed\n");
		kसमय_get_ts64(&end);

		dma_unmap_single(dma_dev, src_phys_addr, reg->size,
				 DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		kसमय_get_ts64(&start);
		स_नकल_toio(dst_addr, buf, reg->size);
		kसमय_get_ts64(&end);
	पूर्ण

	pci_epf_test_prपूर्णांक_rate("WRITE", reg->size, &start, &end, use_dma);

	/*
	 * रुको 1ms inorder क्रम the ग_लिखो to complete. Without this delay L3
	 * error in observed in the host प्रणाली.
	 */
	usleep_range(1000, 2000);

err_dma_map:
	kमुक्त(buf);

err_map_addr:
	pci_epc_unmap_addr(epc, epf->func_no, phys_addr);

err_addr:
	pci_epc_mem_मुक्त_addr(epc, phys_addr, dst_addr, reg->size);

err:
	वापस ret;
पूर्ण

अटल व्योम pci_epf_test_उठाओ_irq(काष्ठा pci_epf_test *epf_test, u8 irq_type,
				   u16 irq)
अणु
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epc *epc = epf->epc;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	काष्ठा pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	reg->status |= STATUS_IRQ_RAISED;

	चयन (irq_type) अणु
	हाल IRQ_TYPE_LEGACY:
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_LEGACY, 0);
		अवरोध;
	हाल IRQ_TYPE_MSI:
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_MSI, irq);
		अवरोध;
	हाल IRQ_TYPE_MSIX:
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_MSIX, irq);
		अवरोध;
	शेष:
		dev_err(dev, "Failed to raise IRQ, unknown type\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pci_epf_test_cmd_handler(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	पूर्णांक count;
	u32 command;
	काष्ठा pci_epf_test *epf_test = container_of(work, काष्ठा pci_epf_test,
						     cmd_handler.work);
	काष्ठा pci_epf *epf = epf_test->epf;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epc *epc = epf->epc;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	काष्ठा pci_epf_test_reg *reg = epf_test->reg[test_reg_bar];

	command = reg->command;
	अगर (!command)
		जाओ reset_handler;

	reg->command = 0;
	reg->status = 0;

	अगर (reg->irq_type > IRQ_TYPE_MSIX) अणु
		dev_err(dev, "Failed to detect IRQ type\n");
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_RAISE_LEGACY_IRQ) अणु
		reg->status = STATUS_IRQ_RAISED;
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_LEGACY, 0);
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_WRITE) अणु
		ret = pci_epf_test_ग_लिखो(epf_test);
		अगर (ret)
			reg->status |= STATUS_WRITE_FAIL;
		अन्यथा
			reg->status |= STATUS_WRITE_SUCCESS;
		pci_epf_test_उठाओ_irq(epf_test, reg->irq_type,
				       reg->irq_number);
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_READ) अणु
		ret = pci_epf_test_पढ़ो(epf_test);
		अगर (!ret)
			reg->status |= STATUS_READ_SUCCESS;
		अन्यथा
			reg->status |= STATUS_READ_FAIL;
		pci_epf_test_उठाओ_irq(epf_test, reg->irq_type,
				       reg->irq_number);
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_COPY) अणु
		ret = pci_epf_test_copy(epf_test);
		अगर (!ret)
			reg->status |= STATUS_COPY_SUCCESS;
		अन्यथा
			reg->status |= STATUS_COPY_FAIL;
		pci_epf_test_उठाओ_irq(epf_test, reg->irq_type,
				       reg->irq_number);
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_RAISE_MSI_IRQ) अणु
		count = pci_epc_get_msi(epc, epf->func_no);
		अगर (reg->irq_number > count || count <= 0)
			जाओ reset_handler;
		reg->status = STATUS_IRQ_RAISED;
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_MSI,
				  reg->irq_number);
		जाओ reset_handler;
	पूर्ण

	अगर (command & COMMAND_RAISE_MSIX_IRQ) अणु
		count = pci_epc_get_msix(epc, epf->func_no);
		अगर (reg->irq_number > count || count <= 0)
			जाओ reset_handler;
		reg->status = STATUS_IRQ_RAISED;
		pci_epc_उठाओ_irq(epc, epf->func_no, PCI_EPC_IRQ_MSIX,
				  reg->irq_number);
		जाओ reset_handler;
	पूर्ण

reset_handler:
	queue_delayed_work(kpcitest_workqueue, &epf_test->cmd_handler,
			   msecs_to_jअगरfies(1));
पूर्ण

अटल व्योम pci_epf_test_unbind(काष्ठा pci_epf *epf)
अणु
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	काष्ठा pci_epc *epc = epf->epc;
	काष्ठा pci_epf_bar *epf_bar;
	पूर्णांक bar;

	cancel_delayed_work(&epf_test->cmd_handler);
	pci_epf_test_clean_dma_chan(epf_test);
	pci_epc_stop(epc);
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		epf_bar = &epf->bar[bar];

		अगर (epf_test->reg[bar]) अणु
			pci_epc_clear_bar(epc, epf->func_no, epf_bar);
			pci_epf_मुक्त_space(epf, epf_test->reg[bar], bar,
					   PRIMARY_INTERFACE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pci_epf_test_set_bar(काष्ठा pci_epf *epf)
अणु
	पूर्णांक bar, add;
	पूर्णांक ret;
	काष्ठा pci_epf_bar *epf_bar;
	काष्ठा pci_epc *epc = epf->epc;
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	स्थिर काष्ठा pci_epc_features *epc_features;

	epc_features = epf_test->epc_features;

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar += add) अणु
		epf_bar = &epf->bar[bar];
		/*
		 * pci_epc_set_bar() sets PCI_BASE_ADDRESS_MEM_TYPE_64
		 * अगर the specअगरic implementation required a 64-bit BAR,
		 * even अगर we only requested a 32-bit BAR.
		 */
		add = (epf_bar->flags & PCI_BASE_ADDRESS_MEM_TYPE_64) ? 2 : 1;

		अगर (!!(epc_features->reserved_bar & (1 << bar)))
			जारी;

		ret = pci_epc_set_bar(epc, epf->func_no, epf_bar);
		अगर (ret) अणु
			pci_epf_मुक्त_space(epf, epf_test->reg[bar], bar,
					   PRIMARY_INTERFACE);
			dev_err(dev, "Failed to set BAR%d\n", bar);
			अगर (bar == test_reg_bar)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_epf_test_core_init(काष्ठा pci_epf *epf)
अणु
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	काष्ठा pci_epf_header *header = epf->header;
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा pci_epc *epc = epf->epc;
	काष्ठा device *dev = &epf->dev;
	bool msix_capable = false;
	bool msi_capable = true;
	पूर्णांक ret;

	epc_features = pci_epc_get_features(epc, epf->func_no);
	अगर (epc_features) अणु
		msix_capable = epc_features->msix_capable;
		msi_capable = epc_features->msi_capable;
	पूर्ण

	ret = pci_epc_ग_लिखो_header(epc, epf->func_no, header);
	अगर (ret) अणु
		dev_err(dev, "Configuration header write failed\n");
		वापस ret;
	पूर्ण

	ret = pci_epf_test_set_bar(epf);
	अगर (ret)
		वापस ret;

	अगर (msi_capable) अणु
		ret = pci_epc_set_msi(epc, epf->func_no, epf->msi_पूर्णांकerrupts);
		अगर (ret) अणु
			dev_err(dev, "MSI configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (msix_capable) अणु
		ret = pci_epc_set_msix(epc, epf->func_no, epf->msix_पूर्णांकerrupts,
				       epf_test->test_reg_bar,
				       epf_test->msix_table_offset);
		अगर (ret) अणु
			dev_err(dev, "MSI-X configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_epf_test_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				 व्योम *data)
अणु
	काष्ठा pci_epf *epf = container_of(nb, काष्ठा pci_epf, nb);
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	पूर्णांक ret;

	चयन (val) अणु
	हाल CORE_INIT:
		ret = pci_epf_test_core_init(epf);
		अगर (ret)
			वापस NOTIFY_BAD;
		अवरोध;

	हाल LINK_UP:
		queue_delayed_work(kpcitest_workqueue, &epf_test->cmd_handler,
				   msecs_to_jअगरfies(1));
		अवरोध;

	शेष:
		dev_err(&epf->dev, "Invalid EPF test notifier event\n");
		वापस NOTIFY_BAD;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक pci_epf_test_alloc_space(काष्ठा pci_epf *epf)
अणु
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	काष्ठा device *dev = &epf->dev;
	काष्ठा pci_epf_bar *epf_bar;
	माप_प्रकार msix_table_size = 0;
	माप_प्रकार test_reg_bar_size;
	माप_प्रकार pba_size = 0;
	bool msix_capable;
	व्योम *base;
	पूर्णांक bar, add;
	क्रमागत pci_barno test_reg_bar = epf_test->test_reg_bar;
	स्थिर काष्ठा pci_epc_features *epc_features;
	माप_प्रकार test_reg_size;

	epc_features = epf_test->epc_features;

	test_reg_bar_size = ALIGN(माप(काष्ठा pci_epf_test_reg), 128);

	msix_capable = epc_features->msix_capable;
	अगर (msix_capable) अणु
		msix_table_size = PCI_MSIX_ENTRY_SIZE * epf->msix_पूर्णांकerrupts;
		epf_test->msix_table_offset = test_reg_bar_size;
		/* Align to QWORD or 8 Bytes */
		pba_size = ALIGN(DIV_ROUND_UP(epf->msix_पूर्णांकerrupts, 8), 8);
	पूर्ण
	test_reg_size = test_reg_bar_size + msix_table_size + pba_size;

	अगर (epc_features->bar_fixed_size[test_reg_bar]) अणु
		अगर (test_reg_size > bar_size[test_reg_bar])
			वापस -ENOMEM;
		test_reg_size = bar_size[test_reg_bar];
	पूर्ण

	base = pci_epf_alloc_space(epf, test_reg_size, test_reg_bar,
				   epc_features->align, PRIMARY_INTERFACE);
	अगर (!base) अणु
		dev_err(dev, "Failed to allocated register space\n");
		वापस -ENOMEM;
	पूर्ण
	epf_test->reg[test_reg_bar] = base;

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar += add) अणु
		epf_bar = &epf->bar[bar];
		add = (epf_bar->flags & PCI_BASE_ADDRESS_MEM_TYPE_64) ? 2 : 1;

		अगर (bar == test_reg_bar)
			जारी;

		अगर (!!(epc_features->reserved_bar & (1 << bar)))
			जारी;

		base = pci_epf_alloc_space(epf, bar_size[bar], bar,
					   epc_features->align,
					   PRIMARY_INTERFACE);
		अगर (!base)
			dev_err(dev, "Failed to allocate space for BAR%d\n",
				bar);
		epf_test->reg[bar] = base;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_epf_configure_bar(काष्ठा pci_epf *epf,
				  स्थिर काष्ठा pci_epc_features *epc_features)
अणु
	काष्ठा pci_epf_bar *epf_bar;
	bool bar_fixed_64bit;
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		epf_bar = &epf->bar[i];
		bar_fixed_64bit = !!(epc_features->bar_fixed_64bit & (1 << i));
		अगर (bar_fixed_64bit)
			epf_bar->flags |= PCI_BASE_ADDRESS_MEM_TYPE_64;
		अगर (epc_features->bar_fixed_size[i])
			bar_size[i] = epc_features->bar_fixed_size[i];
	पूर्ण
पूर्ण

अटल पूर्णांक pci_epf_test_bind(काष्ठा pci_epf *epf)
अणु
	पूर्णांक ret;
	काष्ठा pci_epf_test *epf_test = epf_get_drvdata(epf);
	स्थिर काष्ठा pci_epc_features *epc_features;
	क्रमागत pci_barno test_reg_bar = BAR_0;
	काष्ठा pci_epc *epc = epf->epc;
	bool linkup_notअगरier = false;
	bool core_init_notअगरier = false;

	अगर (WARN_ON_ONCE(!epc))
		वापस -EINVAL;

	epc_features = pci_epc_get_features(epc, epf->func_no);
	अगर (!epc_features) अणु
		dev_err(&epf->dev, "epc_features not implemented\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	linkup_notअगरier = epc_features->linkup_notअगरier;
	core_init_notअगरier = epc_features->core_init_notअगरier;
	test_reg_bar = pci_epc_get_first_मुक्त_bar(epc_features);
	अगर (test_reg_bar < 0)
		वापस -EINVAL;
	pci_epf_configure_bar(epf, epc_features);

	epf_test->test_reg_bar = test_reg_bar;
	epf_test->epc_features = epc_features;

	ret = pci_epf_test_alloc_space(epf);
	अगर (ret)
		वापस ret;

	अगर (!core_init_notअगरier) अणु
		ret = pci_epf_test_core_init(epf);
		अगर (ret)
			वापस ret;
	पूर्ण

	epf_test->dma_supported = true;

	ret = pci_epf_test_init_dma_chan(epf_test);
	अगर (ret)
		epf_test->dma_supported = false;

	अगर (linkup_notअगरier) अणु
		epf->nb.notअगरier_call = pci_epf_test_notअगरier;
		pci_epc_रेजिस्टर_notअगरier(epc, &epf->nb);
	पूर्ण अन्यथा अणु
		queue_work(kpcitest_workqueue, &epf_test->cmd_handler.work);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epf_device_id pci_epf_test_ids[] = अणु
	अणु
		.name = "pci_epf_test",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक pci_epf_test_probe(काष्ठा pci_epf *epf)
अणु
	काष्ठा pci_epf_test *epf_test;
	काष्ठा device *dev = &epf->dev;

	epf_test = devm_kzalloc(dev, माप(*epf_test), GFP_KERNEL);
	अगर (!epf_test)
		वापस -ENOMEM;

	epf->header = &test_header;
	epf_test->epf = epf;

	INIT_DELAYED_WORK(&epf_test->cmd_handler, pci_epf_test_cmd_handler);

	epf_set_drvdata(epf, epf_test);
	वापस 0;
पूर्ण

अटल काष्ठा pci_epf_ops ops = अणु
	.unbind	= pci_epf_test_unbind,
	.bind	= pci_epf_test_bind,
पूर्ण;

अटल काष्ठा pci_epf_driver test_driver = अणु
	.driver.name	= "pci_epf_test",
	.probe		= pci_epf_test_probe,
	.id_table	= pci_epf_test_ids,
	.ops		= &ops,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pci_epf_test_init(व्योम)
अणु
	पूर्णांक ret;

	kpcitest_workqueue = alloc_workqueue("kpcitest",
					     WQ_MEM_RECLAIM | WQ_HIGHPRI, 0);
	अगर (!kpcitest_workqueue) अणु
		pr_err("Failed to allocate the kpcitest work queue\n");
		वापस -ENOMEM;
	पूर्ण

	ret = pci_epf_रेजिस्टर_driver(&test_driver);
	अगर (ret) अणु
		destroy_workqueue(kpcitest_workqueue);
		pr_err("Failed to register pci epf test driver --> %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(pci_epf_test_init);

अटल व्योम __निकास pci_epf_test_निकास(व्योम)
अणु
	अगर (kpcitest_workqueue)
		destroy_workqueue(kpcitest_workqueue);
	pci_epf_unरेजिस्टर_driver(&test_driver);
पूर्ण
module_निकास(pci_epf_test_निकास);

MODULE_DESCRIPTION("PCI EPF TEST DRIVER");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
