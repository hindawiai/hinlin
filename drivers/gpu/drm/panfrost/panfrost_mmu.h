<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#अगर_अघोषित __PANFROST_MMU_H__
#घोषणा __PANFROST_MMU_H__

काष्ठा panfrost_gem_mapping;
काष्ठा panfrost_file_priv;
काष्ठा panfrost_mmu;

पूर्णांक panfrost_mmu_map(काष्ठा panfrost_gem_mapping *mapping);
व्योम panfrost_mmu_unmap(काष्ठा panfrost_gem_mapping *mapping);

पूर्णांक panfrost_mmu_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_mmu_fini(काष्ठा panfrost_device *pfdev);
व्योम panfrost_mmu_reset(काष्ठा panfrost_device *pfdev);

u32 panfrost_mmu_as_get(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu);
व्योम panfrost_mmu_as_put(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu);

पूर्णांक panfrost_mmu_pgtable_alloc(काष्ठा panfrost_file_priv *priv);
व्योम panfrost_mmu_pgtable_मुक्त(काष्ठा panfrost_file_priv *priv);

#पूर्ण_अगर
