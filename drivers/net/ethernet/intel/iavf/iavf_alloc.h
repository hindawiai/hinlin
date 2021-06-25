<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_ALLOC_H_
#घोषणा _IAVF_ALLOC_H_

काष्ठा iavf_hw;

/* Memory allocation types */
क्रमागत iavf_memory_type अणु
	iavf_mem_arq_buf = 0,		/* ARQ indirect command buffer */
	iavf_mem_asq_buf = 1,
	iavf_mem_atq_buf = 2,		/* ATQ indirect command buffer */
	iavf_mem_arq_ring = 3,		/* ARQ descriptor ring */
	iavf_mem_atq_ring = 4,		/* ATQ descriptor ring */
	iavf_mem_pd = 5,		/* Page Descriptor */
	iavf_mem_bp = 6,		/* Backing Page - 4KB */
	iavf_mem_bp_jumbo = 7,		/* Backing Page - > 4KB */
	iavf_mem_reserved
पूर्ण;

/* prototype क्रम functions used क्रम dynamic memory allocation */
क्रमागत iavf_status iavf_allocate_dma_mem(काष्ठा iavf_hw *hw,
				       काष्ठा iavf_dma_mem *mem,
				       क्रमागत iavf_memory_type type,
				       u64 size, u32 alignment);
क्रमागत iavf_status iavf_मुक्त_dma_mem(काष्ठा iavf_hw *hw,
				   काष्ठा iavf_dma_mem *mem);
क्रमागत iavf_status iavf_allocate_virt_mem(काष्ठा iavf_hw *hw,
					काष्ठा iavf_virt_mem *mem, u32 size);
क्रमागत iavf_status iavf_मुक्त_virt_mem(काष्ठा iavf_hw *hw,
				    काष्ठा iavf_virt_mem *mem);

#पूर्ण_अगर /* _IAVF_ALLOC_H_ */
