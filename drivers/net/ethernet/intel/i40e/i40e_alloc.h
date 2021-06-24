<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_ALLOC_H_
#घोषणा _I40E_ALLOC_H_

काष्ठा i40e_hw;

/* Memory allocation types */
क्रमागत i40e_memory_type अणु
	i40e_mem_arq_buf = 0,		/* ARQ indirect command buffer */
	i40e_mem_asq_buf = 1,
	i40e_mem_atq_buf = 2,		/* ATQ indirect command buffer */
	i40e_mem_arq_ring = 3,		/* ARQ descriptor ring */
	i40e_mem_atq_ring = 4,		/* ATQ descriptor ring */
	i40e_mem_pd = 5,		/* Page Descriptor */
	i40e_mem_bp = 6,		/* Backing Page - 4KB */
	i40e_mem_bp_jumbo = 7,		/* Backing Page - > 4KB */
	i40e_mem_reserved
पूर्ण;

/* prototype क्रम functions used क्रम dynamic memory allocation */
i40e_status i40e_allocate_dma_mem(काष्ठा i40e_hw *hw,
					    काष्ठा i40e_dma_mem *mem,
					    क्रमागत i40e_memory_type type,
					    u64 size, u32 alignment);
i40e_status i40e_मुक्त_dma_mem(काष्ठा i40e_hw *hw,
					काष्ठा i40e_dma_mem *mem);
i40e_status i40e_allocate_virt_mem(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_virt_mem *mem,
					     u32 size);
i40e_status i40e_मुक्त_virt_mem(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_virt_mem *mem);

#पूर्ण_अगर /* _I40E_ALLOC_H_ */
