<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Google, Inc.
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Colin Cross <ccross@android.com>
 */

#अगर_अघोषित __DRIVERS_MISC_TEGRA_FUSE_H
#घोषणा __DRIVERS_MISC_TEGRA_FUSE_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/types.h>

काष्ठा nvmem_cell_lookup;
काष्ठा nvmem_device;
काष्ठा tegra_fuse;

काष्ठा tegra_fuse_info अणु
	u32 (*पढ़ो)(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset);
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक spare;
पूर्ण;

काष्ठा tegra_fuse_soc अणु
	व्योम (*init)(काष्ठा tegra_fuse *fuse);
	व्योम (*speeकरो_init)(काष्ठा tegra_sku_info *info);
	पूर्णांक (*probe)(काष्ठा tegra_fuse *fuse);

	स्थिर काष्ठा tegra_fuse_info *info;

	स्थिर काष्ठा nvmem_cell_lookup *lookups;
	अचिन्हित पूर्णांक num_lookups;

	स्थिर काष्ठा attribute_group *soc_attr_group;
पूर्ण;

काष्ठा tegra_fuse अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	phys_addr_t phys;
	काष्ठा clk *clk;

	u32 (*पढ़ो_early)(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset);
	u32 (*पढ़ो)(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset);
	स्थिर काष्ठा tegra_fuse_soc *soc;

	/* APBDMA on Tegra20 */
	काष्ठा अणु
		काष्ठा mutex lock;
		काष्ठा completion रुको;
		काष्ठा dma_chan *chan;
		काष्ठा dma_slave_config config;
		dma_addr_t phys;
		u32 *virt;
	पूर्ण apbdma;

	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_cell_lookup *lookups;
पूर्ण;

व्योम tegra_init_revision(व्योम);
व्योम tegra_init_apbmisc(व्योम);

bool __init tegra_fuse_पढ़ो_spare(अचिन्हित पूर्णांक spare);
u32 __init tegra_fuse_पढ़ो_early(अचिन्हित पूर्णांक offset);

u8 tegra_get_major_rev(व्योम);
u8 tegra_get_minor_rev(व्योम);

बाह्य स्थिर काष्ठा attribute_group tegra_soc_attr_group;

#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
व्योम tegra20_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
व्योम tegra30_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
व्योम tegra114_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info);
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC)
व्योम tegra124_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
व्योम tegra210_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra20_fuse_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra30_fuse_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra114_fuse_soc;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC)
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra124_fuse_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra210_fuse_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_186_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra186_fuse_soc;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_234_SOC)
बाह्य स्थिर काष्ठा attribute_group tegra194_soc_attr_group;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_194_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra194_fuse_soc;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_234_SOC
बाह्य स्थिर काष्ठा tegra_fuse_soc tegra234_fuse_soc;
#पूर्ण_अगर

#पूर्ण_अगर
