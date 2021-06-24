<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/dma-direct.h>
#समावेश <linux/init.h>
#समावेश <linux/swiotlb.h>
#समावेश <boot_param.h>

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	/* We extract 2bit node id (bit 44~47, only bit 44~45 used now) from
	 * Loongson-3's 48bit address space and embed it पूर्णांकo 40bit */
	दीर्घ nid = (paddr >> 44) & 0x3;

	वापस ((nid << 44) ^ paddr) | (nid << node_id_offset);
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
	/* We extract 2bit node id (bit 44~47, only bit 44~45 used now) from
	 * Loongson-3's 48bit address space and embed it पूर्णांकo 40bit */
	दीर्घ nid = (daddr >> node_id_offset) & 0x3;

	वापस ((nid << node_id_offset) ^ daddr) | (nid << 44);
पूर्ण

व्योम __init plat_swiotlb_setup(व्योम)
अणु
	swiotlb_init(1);
पूर्ण
