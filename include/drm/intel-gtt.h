<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Common header क्रम पूर्णांकel-gtt.ko and i915.ko */

#अगर_अघोषित _DRM_INTEL_GTT_H
#घोषणा	_DRM_INTEL_GTT_H

#समावेश <linux/agp_backend.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/kernel.h>

व्योम पूर्णांकel_gtt_get(u64 *gtt_total,
		   phys_addr_t *mappable_base,
		   resource_माप_प्रकार *mappable_end);

पूर्णांक पूर्णांकel_gmch_probe(काष्ठा pci_dev *bridge_pdev, काष्ठा pci_dev *gpu_pdev,
		     काष्ठा agp_bridge_data *bridge);
व्योम पूर्णांकel_gmch_हटाओ(व्योम);

bool पूर्णांकel_enable_gtt(व्योम);

व्योम पूर्णांकel_gtt_chipset_flush(व्योम);
व्योम पूर्णांकel_gtt_insert_page(dma_addr_t addr,
			   अचिन्हित पूर्णांक pg,
			   अचिन्हित पूर्णांक flags);
व्योम पूर्णांकel_gtt_insert_sg_entries(काष्ठा sg_table *st,
				 अचिन्हित पूर्णांक pg_start,
				 अचिन्हित पूर्णांक flags);
व्योम पूर्णांकel_gtt_clear_range(अचिन्हित पूर्णांक first_entry, अचिन्हित पूर्णांक num_entries);

/* Special gtt memory types */
#घोषणा AGP_DCACHE_MEMORY	1
#घोषणा AGP_PHYS_MEMORY		2

/* flag क्रम GFDT type */
#घोषणा AGP_USER_CACHED_MEMORY_GFDT (1 << 3)

#पूर्ण_अगर
