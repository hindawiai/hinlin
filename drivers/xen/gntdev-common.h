<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Common functionality of grant device.
 *
 * Copyright (c) 2006-2007, D G Murray.
 *           (c) 2009 Gerd Hoffmann <kraxel@redhat.com>
 *           (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 */

#अगर_अघोषित _GNTDEV_COMMON_H
#घोषणा _GNTDEV_COMMON_H

#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/types.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>

काष्ठा gntdev_dmabuf_priv;

काष्ठा gntdev_priv अणु
	/* Maps with visible offsets in the file descriptor. */
	काष्ठा list_head maps;
	/* lock protects maps and मुक्तable_maps. */
	काष्ठा mutex lock;

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	/* Device क्रम which DMA memory is allocated. */
	काष्ठा device *dma_dev;
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_GNTDEV_DMABUF
	काष्ठा gntdev_dmabuf_priv *dmabuf_priv;
#पूर्ण_अगर
पूर्ण;

काष्ठा gntdev_unmap_notअगरy अणु
	पूर्णांक flags;
	/* Address relative to the start of the gntdev_grant_map. */
	पूर्णांक addr;
	evtchn_port_t event;
पूर्ण;

काष्ठा gntdev_grant_map अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier notअगरier;
	काष्ठा list_head next;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक index;
	पूर्णांक count;
	पूर्णांक flags;
	refcount_t users;
	काष्ठा gntdev_unmap_notअगरy notअगरy;
	काष्ठा ioctl_gntdev_grant_ref *grants;
	काष्ठा gnttab_map_grant_ref   *map_ops;
	काष्ठा gnttab_unmap_grant_ref *unmap_ops;
	काष्ठा gnttab_map_grant_ref   *kmap_ops;
	काष्ठा gnttab_unmap_grant_ref *kunmap_ops;
	काष्ठा page **pages;
	अचिन्हित दीर्घ pages_vm_start;

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	/*
	 * If dmabuf_vaddr is not शून्य then this mapping is backed by DMA
	 * capable memory.
	 */

	काष्ठा device *dma_dev;
	/* Flags used to create this DMA buffer: GNTDEV_DMA_FLAG_XXX. */
	पूर्णांक dma_flags;
	व्योम *dma_vaddr;
	dma_addr_t dma_bus_addr;
	/* Needed to aव्योम allocation in gnttab_dma_मुक्त_pages(). */
	xen_pfn_t *frames;
#पूर्ण_अगर
पूर्ण;

काष्ठा gntdev_grant_map *gntdev_alloc_map(काष्ठा gntdev_priv *priv, पूर्णांक count,
					  पूर्णांक dma_flags);

व्योम gntdev_add_map(काष्ठा gntdev_priv *priv, काष्ठा gntdev_grant_map *add);

व्योम gntdev_put_map(काष्ठा gntdev_priv *priv, काष्ठा gntdev_grant_map *map);

bool gntdev_test_page_count(अचिन्हित पूर्णांक count);

पूर्णांक gntdev_map_grant_pages(काष्ठा gntdev_grant_map *map);

#पूर्ण_अगर
