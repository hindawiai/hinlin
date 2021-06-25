<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Keem Bay OCS AES Crypto Driver.
 *
 * Copyright (C) 2018-2020 Intel Corporation
 */

#अगर_अघोषित _CRYPTO_OCS_AES_H
#घोषणा _CRYPTO_OCS_AES_H

#समावेश <linux/dma-mapping.h>

क्रमागत ocs_cipher अणु
	OCS_AES = 0,
	OCS_SM4 = 1,
पूर्ण;

क्रमागत ocs_mode अणु
	OCS_MODE_ECB = 0,
	OCS_MODE_CBC = 1,
	OCS_MODE_CTR = 2,
	OCS_MODE_CCM = 6,
	OCS_MODE_GCM = 7,
	OCS_MODE_CTS = 9,
पूर्ण;

क्रमागत ocs_inकाष्ठाion अणु
	OCS_ENCRYPT = 0,
	OCS_DECRYPT = 1,
	OCS_EXPAND  = 2,
	OCS_BYPASS  = 3,
पूर्ण;

/**
 * काष्ठा ocs_aes_dev - AES device context.
 * @list:			List head क्रम insertion पूर्णांकo device list hold
 *				by driver.
 * @dev:			OCS AES device.
 * @irq:			IRQ number.
 * @base_reg:			IO base address of OCS AES.
 * @irq_copy_completion:	Completion to indicate IRQ has been triggered.
 * @dma_err_mask:		Error reported by OCS DMA पूर्णांकerrupts.
 * @engine:			Crypto engine क्रम the device.
 */
काष्ठा ocs_aes_dev अणु
	काष्ठा list_head list;
	काष्ठा device *dev;
	पूर्णांक irq;
	व्योम __iomem *base_reg;
	काष्ठा completion irq_completion;
	u32 dma_err_mask;
	काष्ठा crypto_engine *engine;
पूर्ण;

/**
 * काष्ठा ocs_dll_desc - Descriptor of an OCS DMA Linked List.
 * @vaddr:	Virtual address of the linked list head.
 * @dma_addr:	DMA address of the linked list head.
 * @size:	Size (in bytes) of the linked list.
 */
काष्ठा ocs_dll_desc अणु
	व्योम		*vaddr;
	dma_addr_t	dma_addr;
	माप_प्रकार		size;
पूर्ण;

पूर्णांक ocs_aes_set_key(काष्ठा ocs_aes_dev *aes_dev, स्थिर u32 key_size,
		    स्थिर u8 *key, स्थिर क्रमागत ocs_cipher cipher);

पूर्णांक ocs_aes_op(काष्ठा ocs_aes_dev *aes_dev,
	       क्रमागत ocs_mode mode,
	       क्रमागत ocs_cipher cipher,
	       क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
	       dma_addr_t dst_dma_list,
	       dma_addr_t src_dma_list,
	       u32 src_size,
	       u8 *iv,
	       u32 iv_size);

/**
 * ocs_aes_bypass_op() - Use OCS DMA to copy data.
 * @aes_dev:            The OCS AES device to use.
 * @dst_dma_list:	The OCS DMA list mapping the memory where input data
 *			will be copied to.
 * @src_dma_list:	The OCS DMA list mapping input data.
 * @src_size:		The amount of data to copy.
 */
अटल अंतरभूत पूर्णांक ocs_aes_bypass_op(काष्ठा ocs_aes_dev *aes_dev,
				    dma_addr_t dst_dma_list,
				    dma_addr_t src_dma_list, u32 src_size)
अणु
	वापस ocs_aes_op(aes_dev, OCS_MODE_ECB, OCS_AES, OCS_BYPASS,
			  dst_dma_list, src_dma_list, src_size, शून्य, 0);
पूर्ण

पूर्णांक ocs_aes_gcm_op(काष्ठा ocs_aes_dev *aes_dev,
		   क्रमागत ocs_cipher cipher,
		   क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
		   dma_addr_t dst_dma_list,
		   dma_addr_t src_dma_list,
		   u32 src_size,
		   स्थिर u8 *iv,
		   dma_addr_t aad_dma_list,
		   u32 aad_size,
		   u8 *out_tag,
		   u32 tag_size);

पूर्णांक ocs_aes_ccm_op(काष्ठा ocs_aes_dev *aes_dev,
		   क्रमागत ocs_cipher cipher,
		   क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
		   dma_addr_t dst_dma_list,
		   dma_addr_t src_dma_list,
		   u32 src_size,
		   u8 *iv,
		   dma_addr_t adata_dma_list,
		   u32 adata_size,
		   u8 *in_tag,
		   u32 tag_size);

पूर्णांक ocs_create_linked_list_from_sg(स्थिर काष्ठा ocs_aes_dev *aes_dev,
				   काष्ठा scatterlist *sg,
				   पूर्णांक sg_dma_count,
				   काष्ठा ocs_dll_desc *dll_desc,
				   माप_प्रकार data_size,
				   माप_प्रकार data_offset);

irqवापस_t ocs_aes_irq_handler(पूर्णांक irq, व्योम *dev_id);

#पूर्ण_अगर
