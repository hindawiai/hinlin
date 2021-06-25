<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bug.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/qcom/sस्मृति.स>

#समावेश "ipa.h"
#समावेश "ipa_reg.h"
#समावेश "ipa_data.h"
#समावेश "ipa_cmd.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_table.h"
#समावेश "gsi_trans.h"

/* "Canary" value placed between memory regions to detect overflow */
#घोषणा IPA_MEM_CANARY_VAL		cpu_to_le32(0xdeadbeef)

/* SMEM host id representing the modem. */
#घोषणा QCOM_SMEM_HOST_MODEM	1

/* Add an immediate command to a transaction that zeroes a memory region */
अटल व्योम
ipa_mem_zero_region_add(काष्ठा gsi_trans *trans, स्थिर काष्ठा ipa_mem *mem)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);
	dma_addr_t addr = ipa->zero_addr;

	अगर (!mem->size)
		वापस;

	ipa_cmd_dma_shared_mem_add(trans, mem->offset, mem->size, addr, true);
पूर्ण

/**
 * ipa_mem_setup() - Set up IPA AP and modem shared memory areas
 * @ipa:	IPA poपूर्णांकer
 *
 * Set up the shared memory regions in IPA local memory.  This involves
 * zero-filling memory regions, and in the हाल of header memory, telling
 * the IPA where it's located.
 *
 * This function perक्रमms the initial setup of this memory.  If the modem
 * crashes, its regions are re-zeroed in ipa_mem_zero_modem().
 *
 * The AP inक्रमms the modem where its portions of memory are located
 * in a QMI exchange that occurs at modem startup.
 *
 * There is no need क्रम a matching ipa_mem_tearकरोwn() function.
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक ipa_mem_setup(काष्ठा ipa *ipa)
अणु
	dma_addr_t addr = ipa->zero_addr;
	काष्ठा gsi_trans *trans;
	u32 offset;
	u16 size;
	u32 val;

	/* Get a transaction to define the header memory region and to zero
	 * the processing context and modem memory regions.
	 */
	trans = ipa_cmd_trans_alloc(ipa, 4);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev, "no transaction for memory setup\n");
		वापस -EBUSY;
	पूर्ण

	/* Initialize IPA-local header memory.  The modem and AP header
	 * regions are contiguous, and initialized together.
	 */
	offset = ipa->mem[IPA_MEM_MODEM_HEADER].offset;
	size = ipa->mem[IPA_MEM_MODEM_HEADER].size;
	size += ipa->mem[IPA_MEM_AP_HEADER].size;

	ipa_cmd_hdr_init_local_add(trans, offset, size, addr);

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_MODEM_PROC_CTX]);

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_AP_PROC_CTX]);

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_MODEM]);

	gsi_trans_commit_रुको(trans);

	/* Tell the hardware where the processing context area is located */
	offset = ipa->mem_offset + ipa->mem[IPA_MEM_MODEM_PROC_CTX].offset;
	val = proc_cntxt_base_addr_encoded(ipa->version, offset);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_LOCAL_PKT_PROC_CNTXT_OFFSET);

	वापस 0;
पूर्ण

#अगर_घोषित IPA_VALIDATE

अटल bool ipa_mem_valid(काष्ठा ipa *ipa, क्रमागत ipa_mem_id mem_id)
अणु
	स्थिर काष्ठा ipa_mem *mem = &ipa->mem[mem_id];
	काष्ठा device *dev = &ipa->pdev->dev;
	u16 size_multiple;

	/* Other than modem memory, sizes must be a multiple of 8 */
	size_multiple = mem_id == IPA_MEM_MODEM ? 4 : 8;
	अगर (mem->size % size_multiple)
		dev_err(dev, "region %u size not a multiple of %u bytes\n",
			mem_id, size_multiple);
	अन्यथा अगर (mem->offset % 8)
		dev_err(dev, "region %u offset not 8-byte aligned\n", mem_id);
	अन्यथा अगर (mem->offset < mem->canary_count * माप(__le32))
		dev_err(dev, "region %u offset too small for %hu canaries\n",
			mem_id, mem->canary_count);
	अन्यथा अगर (mem->offset + mem->size > ipa->mem_size)
		dev_err(dev, "region %u ends beyond memory limit (0x%08x)\n",
			mem_id, ipa->mem_size);
	अन्यथा
		वापस true;

	वापस false;
पूर्ण

#अन्यथा /* !IPA_VALIDATE */

अटल bool ipa_mem_valid(काष्ठा ipa *ipa, क्रमागत ipa_mem_id mem_id)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /*! IPA_VALIDATE */

/**
 * ipa_mem_config() - Configure IPA shared memory
 * @ipa:	IPA poपूर्णांकer
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक ipa_mem_config(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	क्रमागत ipa_mem_id mem_id;
	dma_addr_t addr;
	u32 mem_size;
	व्योम *virt;
	u32 val;

	/* Check the advertised location and size of the shared memory area */
	val = ioपढ़ो32(ipa->reg_virt + IPA_REG_SHARED_MEM_SIZE_OFFSET);

	/* The fields in the रेजिस्टर are in 8 byte units */
	ipa->mem_offset = 8 * u32_get_bits(val, SHARED_MEM_BADDR_FMASK);
	/* Make sure the end is within the region's mapped space */
	mem_size = 8 * u32_get_bits(val, SHARED_MEM_SIZE_FMASK);

	/* If the sizes करोn't match, issue a warning */
	अगर (ipa->mem_offset + mem_size < ipa->mem_size) अणु
		dev_warn(dev, "limiting IPA memory size to 0x%08x\n",
			 mem_size);
		ipa->mem_size = mem_size;
	पूर्ण अन्यथा अगर (ipa->mem_offset + mem_size > ipa->mem_size) अणु
		dev_dbg(dev, "ignoring larger reported memory size: 0x%08x\n",
			mem_size);
	पूर्ण

	/* Pपुनः_स्मृति DMA memory क्रम zeroing regions */
	virt = dma_alloc_coherent(dev, IPA_MEM_MAX, &addr, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;
	ipa->zero_addr = addr;
	ipa->zero_virt = virt;
	ipa->zero_size = IPA_MEM_MAX;

	/* Verअगरy each defined memory region is valid, and अगर indicated
	 * क्रम the region, ग_लिखो "canary" values in the space prior to
	 * the region's base address.
	 */
	क्रम (mem_id = 0; mem_id < ipa->mem_count; mem_id++) अणु
		स्थिर काष्ठा ipa_mem *mem = &ipa->mem[mem_id];
		u16 canary_count;
		__le32 *canary;

		/* Validate all regions (even undefined ones) */
		अगर (!ipa_mem_valid(ipa, mem_id))
			जाओ err_dma_मुक्त;

		/* Skip over undefined regions */
		अगर (!mem->offset && !mem->size)
			जारी;

		canary_count = mem->canary_count;
		अगर (!canary_count)
			जारी;

		/* Write canary values in the space beक्रमe the region */
		canary = ipa->mem_virt + ipa->mem_offset + mem->offset;
		करो
			*--canary = IPA_MEM_CANARY_VAL;
		जबतक (--canary_count);
	पूर्ण

	/* Make sure filter and route table memory regions are valid */
	अगर (!ipa_table_valid(ipa))
		जाओ err_dma_मुक्त;

	/* Validate memory-related properties relevant to immediate commands */
	अगर (!ipa_cmd_data_valid(ipa))
		जाओ err_dma_मुक्त;

	/* Verअगरy the microcontroller ring alignment (0 is OK too) */
	अगर (ipa->mem[IPA_MEM_UC_EVENT_RING].offset % 1024) अणु
		dev_err(dev, "microcontroller ring not 1024-byte aligned\n");
		जाओ err_dma_मुक्त;
	पूर्ण

	वापस 0;

err_dma_मुक्त:
	dma_मुक्त_coherent(dev, IPA_MEM_MAX, ipa->zero_virt, ipa->zero_addr);

	वापस -EINVAL;
पूर्ण

/* Inverse of ipa_mem_config() */
व्योम ipa_mem_deconfig(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;

	dma_मुक्त_coherent(dev, ipa->zero_size, ipa->zero_virt, ipa->zero_addr);
	ipa->zero_size = 0;
	ipa->zero_virt = शून्य;
	ipa->zero_addr = 0;
पूर्ण

/**
 * ipa_mem_zero_modem() - Zero IPA-local memory regions owned by the modem
 * @ipa:	IPA poपूर्णांकer
 *
 * Zero regions of IPA-local memory used by the modem.  These are configured
 * (and initially zeroed) by ipa_mem_setup(), but अगर the modem crashes and
 * restarts via SSR we need to re-initialize them.  A QMI message tells the
 * modem where to find regions of IPA local memory it needs to know about
 * (these included).
 */
पूर्णांक ipa_mem_zero_modem(काष्ठा ipa *ipa)
अणु
	काष्ठा gsi_trans *trans;

	/* Get a transaction to zero the modem memory, modem header,
	 * and modem processing context regions.
	 */
	trans = ipa_cmd_trans_alloc(ipa, 3);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev,
			"no transaction to zero modem memory\n");
		वापस -EBUSY;
	पूर्ण

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_MODEM_HEADER]);

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_MODEM_PROC_CTX]);

	ipa_mem_zero_region_add(trans, &ipa->mem[IPA_MEM_MODEM]);

	gsi_trans_commit_रुको(trans);

	वापस 0;
पूर्ण

/**
 * ipa_imem_init() - Initialize IMEM memory used by the IPA
 * @ipa:	IPA poपूर्णांकer
 * @addr:	Physical address of the IPA region in IMEM
 * @size:	Size (bytes) of the IPA region in IMEM
 *
 * IMEM is a block of shared memory separate from प्रणाली DRAM, and
 * a portion of this memory is available क्रम the IPA to use.  The
 * modem accesses this memory directly, but the IPA accesses it
 * via the IOMMU, using the AP's credentials.
 *
 * If this region exists (size > 0) we map it क्रम पढ़ो/ग_लिखो access
 * through the IOMMU using the IPA device.
 *
 * Note: @addr and @size are not guaranteed to be page-aligned.
 */
अटल पूर्णांक ipa_imem_init(काष्ठा ipa *ipa, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ iova;
	phys_addr_t phys;
	पूर्णांक ret;

	अगर (!size)
		वापस 0;	/* IMEM memory not used */

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (!करोमुख्य) अणु
		dev_err(dev, "no IOMMU domain found for IMEM\n");
		वापस -EINVAL;
	पूर्ण

	/* Align the address करोwn and the size up to page boundaries */
	phys = addr & PAGE_MASK;
	size = PAGE_ALIGN(size + addr - phys);
	iova = phys;	/* We just want a direct mapping */

	ret = iommu_map(करोमुख्य, iova, phys, size, IOMMU_READ | IOMMU_WRITE);
	अगर (ret)
		वापस ret;

	ipa->imem_iova = iova;
	ipa->imem_size = size;

	वापस 0;
पूर्ण

अटल व्योम ipa_imem_निकास(काष्ठा ipa *ipa)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा device *dev;

	अगर (!ipa->imem_size)
		वापस;

	dev = &ipa->pdev->dev;
	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (करोमुख्य) अणु
		माप_प्रकार size;

		size = iommu_unmap(करोमुख्य, ipa->imem_iova, ipa->imem_size);
		अगर (size != ipa->imem_size)
			dev_warn(dev, "unmapped %zu IMEM bytes, expected %zu\n",
				 size, ipa->imem_size);
	पूर्ण अन्यथा अणु
		dev_err(dev, "couldn't get IPA IOMMU domain for IMEM\n");
	पूर्ण

	ipa->imem_size = 0;
	ipa->imem_iova = 0;
पूर्ण

/**
 * ipa_smem_init() - Initialize SMEM memory used by the IPA
 * @ipa:	IPA poपूर्णांकer
 * @item:	Item ID of SMEM memory
 * @size:	Size (bytes) of SMEM memory region
 *
 * SMEM is a managed block of shared DRAM, from which numbered "items"
 * can be allocated.  One item is designated क्रम use by the IPA.
 *
 * The modem accesses SMEM memory directly, but the IPA accesses it
 * via the IOMMU, using the AP's credentials.
 *
 * If size provided is non-zero, we allocate it and map it क्रम
 * access through the IOMMU.
 *
 * Note: @size and the item address are is not guaranteed to be page-aligned.
 */
अटल पूर्णांक ipa_smem_init(काष्ठा ipa *ipa, u32 item, माप_प्रकार size)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ iova;
	phys_addr_t phys;
	phys_addr_t addr;
	माप_प्रकार actual;
	व्योम *virt;
	पूर्णांक ret;

	अगर (!size)
		वापस 0;	/* SMEM memory not used */

	/* SMEM is memory shared between the AP and another प्रणाली entity
	 * (in this हाल, the modem).  An allocation from SMEM is persistent
	 * until the AP reboots; there is no way to मुक्त an allocated SMEM
	 * region.  Allocation only reserves the space; to use it you need
	 * to "get" a poपूर्णांकer it (this implies no reference counting).
	 * The item might have alपढ़ोy been allocated, in which हाल we
	 * use it unless the size isn't what we expect.
	 */
	ret = qcom_smem_alloc(QCOM_SMEM_HOST_MODEM, item, size);
	अगर (ret && ret != -EEXIST) अणु
		dev_err(dev, "error %d allocating size %zu SMEM item %u\n",
			ret, size, item);
		वापस ret;
	पूर्ण

	/* Now get the address of the SMEM memory region */
	virt = qcom_smem_get(QCOM_SMEM_HOST_MODEM, item, &actual);
	अगर (IS_ERR(virt)) अणु
		ret = PTR_ERR(virt);
		dev_err(dev, "error %d getting SMEM item %u\n", ret, item);
		वापस ret;
	पूर्ण

	/* In हाल the region was alपढ़ोy allocated, verअगरy the size */
	अगर (ret && actual != size) अणु
		dev_err(dev, "SMEM item %u has size %zu, expected %zu\n",
			item, actual, size);
		वापस -EINVAL;
	पूर्ण

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (!करोमुख्य) अणु
		dev_err(dev, "no IOMMU domain found for SMEM\n");
		वापस -EINVAL;
	पूर्ण

	/* Align the address करोwn and the size up to a page boundary */
	addr = qcom_smem_virt_to_phys(virt) & PAGE_MASK;
	phys = addr & PAGE_MASK;
	size = PAGE_ALIGN(size + addr - phys);
	iova = phys;	/* We just want a direct mapping */

	ret = iommu_map(करोमुख्य, iova, phys, size, IOMMU_READ | IOMMU_WRITE);
	अगर (ret)
		वापस ret;

	ipa->smem_iova = iova;
	ipa->smem_size = size;

	वापस 0;
पूर्ण

अटल व्योम ipa_smem_निकास(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (करोमुख्य) अणु
		माप_प्रकार size;

		size = iommu_unmap(करोमुख्य, ipa->smem_iova, ipa->smem_size);
		अगर (size != ipa->smem_size)
			dev_warn(dev, "unmapped %zu SMEM bytes, expected %zu\n",
				 size, ipa->smem_size);

	पूर्ण अन्यथा अणु
		dev_err(dev, "couldn't get IPA IOMMU domain for SMEM\n");
	पूर्ण

	ipa->smem_size = 0;
	ipa->smem_iova = 0;
पूर्ण

/* Perक्रमm memory region-related initialization */
पूर्णांक ipa_mem_init(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_mem_data *mem_data)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (mem_data->local_count > IPA_MEM_COUNT) अणु
		dev_err(dev, "to many memory regions (%u > %u)\n",
			mem_data->local_count, IPA_MEM_COUNT);
		वापस -EINVAL;
	पूर्ण

	ret = dma_set_mask_and_coherent(&ipa->pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		dev_err(dev, "error %d setting DMA mask\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(ipa->pdev, IORESOURCE_MEM,
					   "ipa-shared");
	अगर (!res) अणु
		dev_err(dev,
			"DT error getting \"ipa-shared\" memory property\n");
		वापस -ENODEV;
	पूर्ण

	ipa->mem_virt = memremap(res->start, resource_size(res), MEMREMAP_WC);
	अगर (!ipa->mem_virt) अणु
		dev_err(dev, "unable to remap \"ipa-shared\" memory\n");
		वापस -ENOMEM;
	पूर्ण

	ipa->mem_addr = res->start;
	ipa->mem_size = resource_size(res);

	/* The ipa->mem[] array is indexed by क्रमागत ipa_mem_id values */
	ipa->mem_count = mem_data->local_count;
	ipa->mem = mem_data->local;

	ret = ipa_imem_init(ipa, mem_data->imem_addr, mem_data->imem_size);
	अगर (ret)
		जाओ err_unmap;

	ret = ipa_smem_init(ipa, mem_data->smem_id, mem_data->smem_size);
	अगर (ret)
		जाओ err_imem_निकास;

	वापस 0;

err_imem_निकास:
	ipa_imem_निकास(ipa);
err_unmap:
	memunmap(ipa->mem_virt);

	वापस ret;
पूर्ण

/* Inverse of ipa_mem_init() */
व्योम ipa_mem_निकास(काष्ठा ipa *ipa)
अणु
	ipa_smem_निकास(ipa);
	ipa_imem_निकास(ipa);
	memunmap(ipa->mem_virt);
पूर्ण
