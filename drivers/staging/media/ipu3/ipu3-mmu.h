<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */
/* Copyright 2018 Google LLC. */

#अगर_अघोषित __IPU3_MMU_H
#घोषणा __IPU3_MMU_H

#घोषणा IPU3_PAGE_SHIFT		12
#घोषणा IPU3_PAGE_SIZE		(1UL << IPU3_PAGE_SHIFT)

/**
 * काष्ठा imgu_mmu_info - Describes mmu geometry
 *
 * @aperture_start:	First address that can be mapped
 * @aperture_end:	Last address that can be mapped
 */
काष्ठा imgu_mmu_info अणु
	dma_addr_t aperture_start;
	dma_addr_t aperture_end;
पूर्ण;

काष्ठा device;
काष्ठा scatterlist;

काष्ठा imgu_mmu_info *imgu_mmu_init(काष्ठा device *parent, व्योम __iomem *base);
व्योम imgu_mmu_निकास(काष्ठा imgu_mmu_info *info);
व्योम imgu_mmu_suspend(काष्ठा imgu_mmu_info *info);
व्योम imgu_mmu_resume(काष्ठा imgu_mmu_info *info);

पूर्णांक imgu_mmu_map(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		 phys_addr_t paddr, माप_प्रकार size);
माप_प्रकार imgu_mmu_unmap(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		      माप_प्रकार size);
माप_प्रकार imgu_mmu_map_sg(काष्ठा imgu_mmu_info *info, अचिन्हित दीर्घ iova,
		       काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents);
#पूर्ण_अगर
