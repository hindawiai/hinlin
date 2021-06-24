<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_MMU_H__
#घोषणा __MSM_MMU_H__

#समावेश <linux/iommu.h>

काष्ठा msm_mmu_funcs अणु
	व्योम (*detach)(काष्ठा msm_mmu *mmu);
	पूर्णांक (*map)(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova, काष्ठा sg_table *sgt,
			माप_प्रकार len, पूर्णांक prot);
	पूर्णांक (*unmap)(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova, माप_प्रकार len);
	व्योम (*destroy)(काष्ठा msm_mmu *mmu);
पूर्ण;

क्रमागत msm_mmu_type अणु
	MSM_MMU_GPUMMU,
	MSM_MMU_IOMMU,
	MSM_MMU_IOMMU_PAGETABLE,
पूर्ण;

काष्ठा msm_mmu अणु
	स्थिर काष्ठा msm_mmu_funcs *funcs;
	काष्ठा device *dev;
	पूर्णांक (*handler)(व्योम *arg, अचिन्हित दीर्घ iova, पूर्णांक flags);
	व्योम *arg;
	क्रमागत msm_mmu_type type;
पूर्ण;

अटल अंतरभूत व्योम msm_mmu_init(काष्ठा msm_mmu *mmu, काष्ठा device *dev,
		स्थिर काष्ठा msm_mmu_funcs *funcs, क्रमागत msm_mmu_type type)
अणु
	mmu->dev = dev;
	mmu->funcs = funcs;
	mmu->type = type;
पूर्ण

काष्ठा msm_mmu *msm_iommu_new(काष्ठा device *dev, काष्ठा iommu_करोमुख्य *करोमुख्य);
काष्ठा msm_mmu *msm_gpummu_new(काष्ठा device *dev, काष्ठा msm_gpu *gpu);

अटल अंतरभूत व्योम msm_mmu_set_fault_handler(काष्ठा msm_mmu *mmu, व्योम *arg,
		पूर्णांक (*handler)(व्योम *arg, अचिन्हित दीर्घ iova, पूर्णांक flags))
अणु
	mmu->arg = arg;
	mmu->handler = handler;
पूर्ण

काष्ठा msm_mmu *msm_iommu_pagetable_create(काष्ठा msm_mmu *parent);

व्योम msm_gpummu_params(काष्ठा msm_mmu *mmu, dma_addr_t *pt_base,
		dma_addr_t *tran_error);


पूर्णांक msm_iommu_pagetable_params(काष्ठा msm_mmu *mmu, phys_addr_t *ttbr,
		पूर्णांक *asid);

#पूर्ण_अगर /* __MSM_MMU_H__ */
