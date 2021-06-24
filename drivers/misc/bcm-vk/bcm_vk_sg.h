<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2018-2020 Broadcom.
 */

#अगर_अघोषित BCM_VK_SG_H
#घोषणा BCM_VK_SG_H

#समावेश <linux/dma-mapping.h>

काष्ठा bcm_vk_dma अणु
	/* क्रम userland buffer */
	काष्ठा page **pages;
	पूर्णांक nr_pages;

	/* common */
	dma_addr_t handle;
	/*
	 * sglist is of the following LE क्रमmat
	 * [U32] num_sg  = number of sg addresses (N)
	 * [U32] totalsize = totalsize of data being transferred in sglist
	 * [U32] size[0] = size of data in address0
	 * [U32] addr_l[0] = lower 32-bits of address0
	 * [U32] addr_h[0] = higher 32-bits of address0
	 * ..
	 * [U32] size[N-1] = size of data in addressN-1
	 * [U32] addr_l[N-1] = lower 32-bits of addressN-1
	 * [U32] addr_h[N-1] = higher 32-bits of addressN-1
	 */
	u32 *sglist;
#घोषणा SGLIST_NUM_SG		0
#घोषणा SGLIST_TOTALSIZE	1
#घोषणा SGLIST_VKDATA_START	2

	पूर्णांक sglen; /* Length (bytes) of sglist */
	पूर्णांक direction;
पूर्ण;

काष्ठा _vk_data अणु
	u32 size;    /* data size in bytes */
	u64 address; /* Poपूर्णांकer to data     */
पूर्ण __packed;

/*
 * Scatter-gather DMA buffer API.
 *
 * These functions provide a simple way to create a page list and a
 * scatter-gather list from userspace address and map the memory
 * क्रम DMA operation.
 */
पूर्णांक bcm_vk_sg_alloc(काष्ठा device *dev,
		    काष्ठा bcm_vk_dma *dma,
		    पूर्णांक dir,
		    काष्ठा _vk_data *vkdata,
		    पूर्णांक num);

पूर्णांक bcm_vk_sg_मुक्त(काष्ठा device *dev, काष्ठा bcm_vk_dma *dma, पूर्णांक num,
		   पूर्णांक *proc_cnt);

#पूर्ण_अगर

