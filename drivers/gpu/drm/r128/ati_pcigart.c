<शैली गुरु>
/*
 * \पile ati_pcigart.c
 * ATI PCI GART support
 *
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Wed Dec 13 21:52:19 2000 by gareth@valinux.com
 *
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "ati_pcigart.h"

# define ATI_PCIGART_PAGE_SIZE		4096	/**< PCI GART page size */

अटल पूर्णांक drm_ati_alloc_pcigart_table(काष्ठा drm_device *dev,
				       काष्ठा drm_ati_pcigart_info *gart_info)
अणु
	gart_info->table_handle = drm_pci_alloc(dev, gart_info->table_size,
						PAGE_SIZE);
	अगर (gart_info->table_handle == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम drm_ati_मुक्त_pcigart_table(काष्ठा drm_device *dev,
				       काष्ठा drm_ati_pcigart_info *gart_info)
अणु
	drm_pci_मुक्त(dev, gart_info->table_handle);
	gart_info->table_handle = शून्य;
पूर्ण

पूर्णांक drm_ati_pcigart_cleanup(काष्ठा drm_device *dev, काष्ठा drm_ati_pcigart_info *gart_info)
अणु
	काष्ठा drm_sg_mem *entry = dev->sg;
	अचिन्हित दीर्घ pages;
	पूर्णांक i;
	पूर्णांक max_pages;

	/* we need to support large memory configurations */
	अगर (!entry) अणु
		DRM_ERROR("no scatter/gather memory!\n");
		वापस 0;
	पूर्ण

	अगर (gart_info->bus_addr) अणु

		max_pages = (gart_info->table_size / माप(u32));
		pages = (entry->pages <= max_pages)
		  ? entry->pages : max_pages;

		क्रम (i = 0; i < pages; i++) अणु
			अगर (!entry->busaddr[i])
				अवरोध;
			pci_unmap_page(dev->pdev, entry->busaddr[i],
					 PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
		पूर्ण

		अगर (gart_info->gart_table_location == DRM_ATI_GART_MAIN)
			gart_info->bus_addr = 0;
	पूर्ण

	अगर (gart_info->gart_table_location == DRM_ATI_GART_MAIN &&
	    gart_info->table_handle) अणु
		drm_ati_मुक्त_pcigart_table(dev, gart_info);
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक drm_ati_pcigart_init(काष्ठा drm_device *dev, काष्ठा drm_ati_pcigart_info *gart_info)
अणु
	काष्ठा drm_local_map *map = &gart_info->mapping;
	काष्ठा drm_sg_mem *entry = dev->sg;
	व्योम *address = शून्य;
	अचिन्हित दीर्घ pages;
	u32 *pci_gart = शून्य, page_base, gart_idx;
	dma_addr_t bus_address = 0;
	पूर्णांक i, j, ret = -ENOMEM;
	पूर्णांक max_ati_pages, max_real_pages;

	अगर (!entry) अणु
		DRM_ERROR("no scatter/gather memory!\n");
		जाओ करोne;
	पूर्ण

	अगर (gart_info->gart_table_location == DRM_ATI_GART_MAIN) अणु
		DRM_DEBUG("PCI: no table in VRAM: using normal RAM\n");

		अगर (pci_set_dma_mask(dev->pdev, gart_info->table_mask)) अणु
			DRM_ERROR("fail to set dma mask to 0x%Lx\n",
				  (अचिन्हित दीर्घ दीर्घ)gart_info->table_mask);
			ret = -EFAULT;
			जाओ करोne;
		पूर्ण

		ret = drm_ati_alloc_pcigart_table(dev, gart_info);
		अगर (ret) अणु
			DRM_ERROR("cannot allocate PCI GART page!\n");
			जाओ करोne;
		पूर्ण

		pci_gart = gart_info->table_handle->vaddr;
		address = gart_info->table_handle->vaddr;
		bus_address = gart_info->table_handle->busaddr;
	पूर्ण अन्यथा अणु
		address = gart_info->addr;
		bus_address = gart_info->bus_addr;
		DRM_DEBUG("PCI: Gart Table: VRAM %08LX mapped at %08lX\n",
			  (अचिन्हित दीर्घ दीर्घ)bus_address,
			  (अचिन्हित दीर्घ)address);
	पूर्ण


	max_ati_pages = (gart_info->table_size / माप(u32));
	max_real_pages = max_ati_pages / (PAGE_SIZE / ATI_PCIGART_PAGE_SIZE);
	pages = (entry->pages <= max_real_pages)
	    ? entry->pages : max_real_pages;

	अगर (gart_info->gart_table_location == DRM_ATI_GART_MAIN) अणु
		स_रखो(pci_gart, 0, max_ati_pages * माप(u32));
	पूर्ण अन्यथा अणु
		स_रखो_io((व्योम __iomem *)map->handle, 0, max_ati_pages * माप(u32));
	पूर्ण

	gart_idx = 0;
	क्रम (i = 0; i < pages; i++) अणु
		/* we need to support large memory configurations */
		entry->busaddr[i] = pci_map_page(dev->pdev, entry->pagelist[i],
						 0, PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
		अगर (pci_dma_mapping_error(dev->pdev, entry->busaddr[i])) अणु
			DRM_ERROR("unable to map PCIGART pages!\n");
			drm_ati_pcigart_cleanup(dev, gart_info);
			address = शून्य;
			bus_address = 0;
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		page_base = (u32) entry->busaddr[i];

		क्रम (j = 0; j < (PAGE_SIZE / ATI_PCIGART_PAGE_SIZE); j++) अणु
			u32 offset;
			u32 val;

			चयन(gart_info->gart_reg_अगर) अणु
			हाल DRM_ATI_GART_IGP:
				val = page_base | 0xc;
				अवरोध;
			हाल DRM_ATI_GART_PCIE:
				val = (page_base >> 8) | 0xc;
				अवरोध;
			शेष:
			हाल DRM_ATI_GART_PCI:
				val = page_base;
				अवरोध;
			पूर्ण
			अगर (gart_info->gart_table_location ==
			    DRM_ATI_GART_MAIN) अणु
				pci_gart[gart_idx] = cpu_to_le32(val);
			पूर्ण अन्यथा अणु
				offset = gart_idx * माप(u32);
				ग_लिखोl(val, (व्योम __iomem *)map->handle + offset);
			पूर्ण
			gart_idx++;
			page_base += ATI_PCIGART_PAGE_SIZE;
		पूर्ण
	पूर्ण
	ret = 0;

#अगर defined(__i386__) || defined(__x86_64__)
	wbinvd();
#अन्यथा
	mb();
#पूर्ण_अगर

      करोne:
	gart_info->addr = address;
	gart_info->bus_addr = bus_address;
	वापस ret;
पूर्ण
