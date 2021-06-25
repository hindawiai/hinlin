<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Honghui Zhang <honghui.zhang@mediatek.com>
 */

#अगर_अघोषित _MTK_IOMMU_H_
#घोषणा _MTK_IOMMU_H_

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <soc/mediatek/smi.h>
#समावेश <dt-bindings/memory/mtk-memory-port.h>

#घोषणा MTK_LARB_COM_MAX	8
#घोषणा MTK_LARB_SUBCOM_MAX	4

#घोषणा MTK_IOMMU_GROUP_MAX	8

काष्ठा mtk_iommu_suspend_reg अणु
	जोड़ अणु
		u32			standard_axi_mode;/* v1 */
		u32			misc_ctrl;/* v2 */
	पूर्ण;
	u32				dcm_dis;
	u32				ctrl_reg;
	u32				पूर्णांक_control0;
	u32				पूर्णांक_मुख्य_control;
	u32				ivrp_paddr;
	u32				vld_pa_rng;
	u32				wr_len_ctrl;
पूर्ण;

क्रमागत mtk_iommu_plat अणु
	M4U_MT2701,
	M4U_MT2712,
	M4U_MT6779,
	M4U_MT8167,
	M4U_MT8173,
	M4U_MT8183,
	M4U_MT8192,
पूर्ण;

काष्ठा mtk_iommu_iova_region;

काष्ठा mtk_iommu_plat_data अणु
	क्रमागत mtk_iommu_plat m4u_plat;
	u32                 flags;
	u32                 inv_sel_reg;

	अचिन्हित पूर्णांक				iova_region_nr;
	स्थिर काष्ठा mtk_iommu_iova_region	*iova_region;
	अचिन्हित अक्षर       larbid_remap[MTK_LARB_COM_MAX][MTK_LARB_SUBCOM_MAX];
पूर्ण;

काष्ठा mtk_iommu_करोमुख्य;

काष्ठा mtk_iommu_data अणु
	व्योम __iomem			*base;
	पूर्णांक				irq;
	काष्ठा device			*dev;
	काष्ठा clk			*bclk;
	phys_addr_t			protect_base; /* protect memory base */
	काष्ठा mtk_iommu_suspend_reg	reg;
	काष्ठा mtk_iommu_करोमुख्य		*m4u_करोm;
	काष्ठा iommu_group		*m4u_group[MTK_IOMMU_GROUP_MAX];
	bool                            enable_4GB;
	spinlock_t			tlb_lock; /* lock क्रम tlb range flush */

	काष्ठा iommu_device		iommu;
	स्थिर काष्ठा mtk_iommu_plat_data *plat_data;
	काष्ठा device			*smicomm_dev;

	काष्ठा dma_iommu_mapping	*mapping; /* For mtk_iommu_v1.c */

	काष्ठा list_head		list;
	काष्ठा mtk_smi_larb_iommu	larb_imu[MTK_LARB_NR_MAX];
पूर्ण;

अटल अंतरभूत पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल अंतरभूत व्योम release_of(काष्ठा device *dev, व्योम *data)
अणु
	of_node_put(data);
पूर्ण

अटल अंतरभूत पूर्णांक mtk_iommu_bind(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);

	वापस component_bind_all(dev, &data->larb_imu);
पूर्ण

अटल अंतरभूत व्योम mtk_iommu_unbind(काष्ठा device *dev)
अणु
	काष्ठा mtk_iommu_data *data = dev_get_drvdata(dev);

	component_unbind_all(dev, &data->larb_imu);
पूर्ण

#पूर्ण_अगर
