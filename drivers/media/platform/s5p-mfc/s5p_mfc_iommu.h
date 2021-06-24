<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Samsung Electronics Co.Ltd
 * Authors: Marek Szyprowski <m.szyprowski@samsung.com>
 */

#अगर_अघोषित S5P_MFC_IOMMU_H_
#घोषणा S5P_MFC_IOMMU_H_

#अगर defined(CONFIG_EXYNOS_IOMMU)

#समावेश <linux/iommu.h>

अटल अंतरभूत bool exynos_is_iommu_available(काष्ठा device *dev)
अणु
	वापस dev_iommu_priv_get(dev) != शून्य;
पूर्ण

#अन्यथा

अटल अंतरभूत bool exynos_is_iommu_available(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* S5P_MFC_IOMMU_H_ */
