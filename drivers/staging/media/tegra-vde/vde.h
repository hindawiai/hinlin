<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * NVIDIA Tegra Video decoder driver
 *
 * Copyright (C) 2016-2019 GRATE-DRIVER project
 */

#अगर_अघोषित TEGRA_VDE_H
#घोषणा TEGRA_VDE_H

#समावेश <linux/completion.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/iova.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

काष्ठा clk;
काष्ठा dma_buf;
काष्ठा gen_pool;
काष्ठा iommu_group;
काष्ठा iommu_करोमुख्य;
काष्ठा reset_control;
काष्ठा dma_buf_attachment;

काष्ठा tegra_vde अणु
	व्योम __iomem *sxe;
	व्योम __iomem *bsev;
	व्योम __iomem *mbe;
	व्योम __iomem *ppe;
	व्योम __iomem *mce;
	व्योम __iomem *tfe;
	व्योम __iomem *ppb;
	व्योम __iomem *vdma;
	व्योम __iomem *frameid;
	काष्ठा mutex lock;
	काष्ठा mutex map_lock;
	काष्ठा list_head map_list;
	काष्ठा miscdevice miscdev;
	काष्ठा reset_control *rst;
	काष्ठा reset_control *rst_mc;
	काष्ठा gen_pool *iram_pool;
	काष्ठा completion decode_completion;
	काष्ठा clk *clk;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा iommu_group *group;
	काष्ठा iova_करोमुख्य iova;
	काष्ठा iova *iova_resv_अटल_addresses;
	काष्ठा iova *iova_resv_last_page;
	dma_addr_t iram_lists_addr;
	u32 *iram;
पूर्ण;

पूर्णांक tegra_vde_iommu_init(काष्ठा tegra_vde *vde);
व्योम tegra_vde_iommu_deinit(काष्ठा tegra_vde *vde);
पूर्णांक tegra_vde_iommu_map(काष्ठा tegra_vde *vde,
			काष्ठा sg_table *sgt,
			काष्ठा iova **iovap,
			माप_प्रकार size);
व्योम tegra_vde_iommu_unmap(काष्ठा tegra_vde *vde, काष्ठा iova *iova);

पूर्णांक tegra_vde_dmabuf_cache_map(काष्ठा tegra_vde *vde,
			       काष्ठा dma_buf *dmabuf,
			       क्रमागत dma_data_direction dma_dir,
			       काष्ठा dma_buf_attachment **ap,
			       dma_addr_t *addrp);
व्योम tegra_vde_dmabuf_cache_unmap(काष्ठा tegra_vde *vde,
				  काष्ठा dma_buf_attachment *a,
				  bool release);
व्योम tegra_vde_dmabuf_cache_unmap_sync(काष्ठा tegra_vde *vde);
व्योम tegra_vde_dmabuf_cache_unmap_all(काष्ठा tegra_vde *vde);

अटल __maybe_unused अक्षर स्थिर *
tegra_vde_reg_base_name(काष्ठा tegra_vde *vde, व्योम __iomem *base)
अणु
	अगर (vde->sxe == base)
		वापस "SXE";

	अगर (vde->bsev == base)
		वापस "BSEV";

	अगर (vde->mbe == base)
		वापस "MBE";

	अगर (vde->ppe == base)
		वापस "PPE";

	अगर (vde->mce == base)
		वापस "MCE";

	अगर (vde->tfe == base)
		वापस "TFE";

	अगर (vde->ppb == base)
		वापस "PPB";

	अगर (vde->vdma == base)
		वापस "VDMA";

	अगर (vde->frameid == base)
		वापस "FRAMEID";

	वापस "???";
पूर्ण

#पूर्ण_अगर /* TEGRA_VDE_H */
