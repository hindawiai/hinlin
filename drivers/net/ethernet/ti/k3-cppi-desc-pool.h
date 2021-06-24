<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* TI K3 CPPI5 descriptors pool
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 */

#अगर_अघोषित K3_CPPI_DESC_POOL_H_
#घोषणा K3_CPPI_DESC_POOL_H_

#समावेश <linux/device.h>
#समावेश <linux/types.h>

काष्ठा k3_cppi_desc_pool;

व्योम k3_cppi_desc_pool_destroy(काष्ठा k3_cppi_desc_pool *pool);
काष्ठा k3_cppi_desc_pool *
k3_cppi_desc_pool_create_name(काष्ठा device *dev, माप_प्रकार size,
			      माप_प्रकार desc_size,
			      स्थिर अक्षर *name);
#घोषणा k3_cppi_desc_pool_create(dev, size, desc_size) \
		k3_cppi_desc_pool_create_name(dev, size, desc_size, शून्य)
dma_addr_t
k3_cppi_desc_pool_virt2dma(काष्ठा k3_cppi_desc_pool *pool, व्योम *addr);
व्योम *
k3_cppi_desc_pool_dma2virt(काष्ठा k3_cppi_desc_pool *pool, dma_addr_t dma);
व्योम *k3_cppi_desc_pool_alloc(काष्ठा k3_cppi_desc_pool *pool);
व्योम k3_cppi_desc_pool_मुक्त(काष्ठा k3_cppi_desc_pool *pool, व्योम *addr);
माप_प्रकार k3_cppi_desc_pool_avail(काष्ठा k3_cppi_desc_pool *pool);

#पूर्ण_अगर /* K3_CPPI_DESC_POOL_H_ */
