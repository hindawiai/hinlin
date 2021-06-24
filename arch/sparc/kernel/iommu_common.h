<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* iommu_common.h: UltraSparc SBUS/PCI common iommu declarations.
 *
 * Copyright (C) 1999, 2008 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _IOMMU_COMMON_H
#घोषणा _IOMMU_COMMON_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <linux/iommu-helper.h>

#समावेश <यंत्र/iommu.h>

/*
 * These give mapping size of each iommu pte/tlb.
 */
#घोषणा IO_PAGE_SHIFT			13
#घोषणा IO_PAGE_SIZE			(1UL << IO_PAGE_SHIFT)
#घोषणा IO_PAGE_MASK			(~(IO_PAGE_SIZE-1))
#घोषणा IO_PAGE_ALIGN(addr)		ALIGN(addr, IO_PAGE_SIZE)

#घोषणा IO_TSB_ENTRIES			(128*1024)
#घोषणा IO_TSB_SIZE			(IO_TSB_ENTRIES * 8)

/*
 * This is the hardwired shअगरt in the iotlb tag/data parts.
 */
#घोषणा IOMMU_PAGE_SHIFT		13

#घोषणा SG_ENT_PHYS_ADDRESS(SG)	(__pa(sg_virt((SG))))

अटल अंतरभूत पूर्णांक is_span_boundary(अचिन्हित दीर्घ entry,
				   अचिन्हित दीर्घ shअगरt,
				   अचिन्हित दीर्घ boundary_size,
				   काष्ठा scatterlist *outs,
				   काष्ठा scatterlist *sg)
अणु
	अचिन्हित दीर्घ paddr = SG_ENT_PHYS_ADDRESS(outs);
	पूर्णांक nr = iommu_num_pages(paddr, outs->dma_length + sg->length,
				 IO_PAGE_SIZE);

	वापस iommu_is_span_boundary(entry, nr, shअगरt, boundary_size);
पूर्ण

#पूर्ण_अगर /* _IOMMU_COMMON_H */
