<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IOMMU_HELPER_H
#घोषणा _LINUX_IOMMU_HELPER_H

#समावेश <linux/bug.h>
#समावेश <linux/log2.h>
#समावेश <linux/गणित.स>
#समावेश <linux/types.h>

अटल अंतरभूत अचिन्हित दीर्घ iommu_device_max_index(अचिन्हित दीर्घ size,
						   अचिन्हित दीर्घ offset,
						   u64 dma_mask)
अणु
	अगर (size + offset > dma_mask)
		वापस dma_mask - offset + 1;
	अन्यथा
		वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_is_span_boundary(अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक nr,
		अचिन्हित दीर्घ shअगरt, अचिन्हित दीर्घ boundary_size)
अणु
	BUG_ON(!is_घातer_of_2(boundary_size));

	shअगरt = (shअगरt + index) & (boundary_size - 1);
	वापस shअगरt + nr > boundary_size;
पूर्ण

बाह्य अचिन्हित दीर्घ iommu_area_alloc(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ size,
				      अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr,
				      अचिन्हित दीर्घ shअगरt,
				      अचिन्हित दीर्घ boundary_size,
				      अचिन्हित दीर्घ align_mask);

अटल अंतरभूत अचिन्हित दीर्घ iommu_num_pages(अचिन्हित दीर्घ addr,
					    अचिन्हित दीर्घ len,
					    अचिन्हित दीर्घ io_page_size)
अणु
	अचिन्हित दीर्घ size = (addr & (io_page_size - 1)) + len;

	वापस DIV_ROUND_UP(size, io_page_size);
पूर्ण

#पूर्ण_अगर
