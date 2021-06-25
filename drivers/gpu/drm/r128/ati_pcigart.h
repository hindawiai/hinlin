<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DRM_ATI_PCIGART_H
#घोषणा DRM_ATI_PCIGART_H

#समावेश <drm/drm_legacy.h>

/* location of GART table */
#घोषणा DRM_ATI_GART_MAIN 1
#घोषणा DRM_ATI_GART_FB   2

#घोषणा DRM_ATI_GART_PCI 1
#घोषणा DRM_ATI_GART_PCIE 2
#घोषणा DRM_ATI_GART_IGP 3

काष्ठा drm_ati_pcigart_info अणु
	पूर्णांक gart_table_location;
	पूर्णांक gart_reg_अगर;
	व्योम *addr;
	dma_addr_t bus_addr;
	dma_addr_t table_mask;
	काष्ठा drm_dma_handle *table_handle;
	काष्ठा drm_local_map mapping;
	पूर्णांक table_size;
पूर्ण;

बाह्य पूर्णांक drm_ati_pcigart_init(काष्ठा drm_device *dev,
				काष्ठा drm_ati_pcigart_info * gart_info);
बाह्य पूर्णांक drm_ati_pcigart_cleanup(काष्ठा drm_device *dev,
				   काष्ठा drm_ati_pcigart_info * gart_info);

#पूर्ण_अगर
