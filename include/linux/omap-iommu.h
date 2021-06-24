<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap iommu: simple भव address space management
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 */

#अगर_अघोषित _OMAP_IOMMU_H_
#घोषणा _OMAP_IOMMU_H_

काष्ठा iommu_करोमुख्य;

#अगर_घोषित CONFIG_OMAP_IOMMU
बाह्य व्योम omap_iommu_save_ctx(काष्ठा device *dev);
बाह्य व्योम omap_iommu_restore_ctx(काष्ठा device *dev);

पूर्णांक omap_iommu_करोमुख्य_deactivate(काष्ठा iommu_करोमुख्य *करोमुख्य);
पूर्णांक omap_iommu_करोमुख्य_activate(काष्ठा iommu_करोमुख्य *करोमुख्य);
#अन्यथा
अटल अंतरभूत व्योम omap_iommu_save_ctx(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम omap_iommu_restore_ctx(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत पूर्णांक omap_iommu_करोमुख्य_deactivate(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक omap_iommu_करोमुख्य_activate(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
