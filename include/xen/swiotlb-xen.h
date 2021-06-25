<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SWIOTLB_XEN_H
#घोषणा __LINUX_SWIOTLB_XEN_H

#समावेश <linux/swiotlb.h>
#समावेश <यंत्र/xen/swiotlb-xen.h>

व्योम xen_dma_sync_क्रम_cpu(काष्ठा device *dev, dma_addr_t handle,
			  माप_प्रकार size, क्रमागत dma_data_direction dir);
व्योम xen_dma_sync_क्रम_device(काष्ठा device *dev, dma_addr_t handle,
			     माप_प्रकार size, क्रमागत dma_data_direction dir);

पूर्णांक xen_swiotlb_init(व्योम);
व्योम __init xen_swiotlb_init_early(व्योम);
बाह्य स्थिर काष्ठा dma_map_ops xen_swiotlb_dma_ops;

#पूर्ण_अगर /* __LINUX_SWIOTLB_XEN_H */
