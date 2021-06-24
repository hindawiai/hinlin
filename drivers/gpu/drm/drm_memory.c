<शैली गुरु>
/*
 * \पile drm_memory.c
 * Memory management wrappers क्रम DRM
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Thu Feb  4 14:00:34 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_cache.h>
#समावेश <drm/drm_device.h>

#समावेश "drm_legacy.h"

#अगर IS_ENABLED(CONFIG_AGP)

#अगर_घोषित HAVE_PAGE_AGP
# include <यंत्र/agp.h>
#अन्यथा
# अगरdef __घातerpc__
#  define PAGE_AGP	pgprot_noncached_wc(PAGE_KERNEL)
# अन्यथा
#  define PAGE_AGP	PAGE_KERNEL
# endअगर
#पूर्ण_अगर

अटल व्योम *agp_remap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
		       काष्ठा drm_device *dev)
अणु
	अचिन्हित दीर्घ i, num_pages =
	    PAGE_ALIGN(size) / PAGE_SIZE;
	काष्ठा drm_agp_mem *agpmem;
	काष्ठा page **page_map;
	काष्ठा page **phys_page_map;
	व्योम *addr;

	size = PAGE_ALIGN(size);

#अगर_घोषित __alpha__
	offset -= dev->hose->mem_space->start;
#पूर्ण_अगर

	list_क्रम_each_entry(agpmem, &dev->agp->memory, head)
		अगर (agpmem->bound <= offset
		    && (agpmem->bound + (agpmem->pages << PAGE_SHIFT)) >=
		    (offset + size))
			अवरोध;
	अगर (&agpmem->head == &dev->agp->memory)
		वापस शून्य;

	/*
	 * OK, we're mapping AGP space on a chipset/platक्रमm on which memory accesses by
	 * the CPU करो not get remapped by the GART.  We fix this by using the kernel's
	 * page-table instead (that's probably faster anyhow...).
	 */
	/* note: use vदो_स्मृति() because num_pages could be large... */
	page_map = vदो_स्मृति(array_size(num_pages, माप(काष्ठा page *)));
	अगर (!page_map)
		वापस शून्य;

	phys_page_map = (agpmem->memory->pages + (offset - agpmem->bound) / PAGE_SIZE);
	क्रम (i = 0; i < num_pages; ++i)
		page_map[i] = phys_page_map[i];
	addr = vmap(page_map, num_pages, VM_IOREMAP, PAGE_AGP);
	vमुक्त(page_map);

	वापस addr;
पूर्ण

#अन्यथा /*  CONFIG_AGP  */
अटल अंतरभूत व्योम *agp_remap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
			      काष्ठा drm_device *dev)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_AGP */

व्योम drm_legacy_ioremap(काष्ठा drm_local_map *map, काष्ठा drm_device *dev)
अणु
	अगर (dev->agp && dev->agp->cant_use_aperture && map->type == _DRM_AGP)
		map->handle = agp_remap(map->offset, map->size, dev);
	अन्यथा
		map->handle = ioremap(map->offset, map->size);
पूर्ण
EXPORT_SYMBOL(drm_legacy_ioremap);

व्योम drm_legacy_ioremap_wc(काष्ठा drm_local_map *map, काष्ठा drm_device *dev)
अणु
	अगर (dev->agp && dev->agp->cant_use_aperture && map->type == _DRM_AGP)
		map->handle = agp_remap(map->offset, map->size, dev);
	अन्यथा
		map->handle = ioremap_wc(map->offset, map->size);
पूर्ण
EXPORT_SYMBOL(drm_legacy_ioremap_wc);

व्योम drm_legacy_ioremapमुक्त(काष्ठा drm_local_map *map, काष्ठा drm_device *dev)
अणु
	अगर (!map->handle || !map->size)
		वापस;

	अगर (dev->agp && dev->agp->cant_use_aperture && map->type == _DRM_AGP)
		vunmap(map->handle);
	अन्यथा
		iounmap(map->handle);
पूर्ण
EXPORT_SYMBOL(drm_legacy_ioremapमुक्त);
