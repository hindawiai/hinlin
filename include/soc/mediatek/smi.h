<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Yong Wu <yong.wu@mediatek.com>
 */
#अगर_अघोषित MTK_IOMMU_SMI_H
#घोषणा MTK_IOMMU_SMI_H

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>

#अगर IS_ENABLED(CONFIG_MTK_SMI)

#घोषणा MTK_SMI_MMU_EN(port)	BIT(port)

काष्ठा mtk_smi_larb_iommu अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक   mmu;
	अचिन्हित अक्षर  bank[32];
पूर्ण;

/*
 * mtk_smi_larb_get: Enable the घातer करोमुख्य and घड़ीs क्रम this local arbiter.
 *                   It also initialize some basic setting(like iommu).
 * mtk_smi_larb_put: Disable the घातer करोमुख्य and घड़ीs क्रम this local arbiter.
 * Both should be called in non-atomic context.
 *
 * Returns 0 अगर successful, negative on failure.
 */
पूर्णांक mtk_smi_larb_get(काष्ठा device *larbdev);
व्योम mtk_smi_larb_put(काष्ठा device *larbdev);

#अन्यथा

अटल अंतरभूत पूर्णांक mtk_smi_larb_get(काष्ठा device *larbdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mtk_smi_larb_put(काष्ठा device *larbdev) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
