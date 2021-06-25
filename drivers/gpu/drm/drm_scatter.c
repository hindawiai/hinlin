<शैली गुरु>
/*
 * \पile drm_scatter.c
 * IOCTLs to manage scatter/gather memory
 *
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Mon Dec 18 23:20:54 2000 by gareth@valinux.com
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

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_legacy.h"

#घोषणा DEBUG_SCATTER 0

अटल व्योम drm_sg_cleanup(काष्ठा drm_sg_mem * entry)
अणु
	काष्ठा page *page;
	पूर्णांक i;

	क्रम (i = 0; i < entry->pages; i++) अणु
		page = entry->pagelist[i];
		अगर (page)
			ClearPageReserved(page);
	पूर्ण

	vमुक्त(entry->भव);

	kमुक्त(entry->busaddr);
	kमुक्त(entry->pagelist);
	kमुक्त(entry);
पूर्ण

व्योम drm_legacy_sg_cleanup(काष्ठा drm_device *dev)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_SG) && dev->sg &&
	    drm_core_check_feature(dev, DRIVER_LEGACY)) अणु
		drm_sg_cleanup(dev->sg);
		dev->sg = शून्य;
	पूर्ण
पूर्ण
#अगर_घोषित _LP64
# define ScatterHandle(x) (अचिन्हित पूर्णांक)((x >> 32) + (x & ((1L << 32) - 1)))
#अन्यथा
# define ScatterHandle(x) (अचिन्हित पूर्णांक)(x)
#पूर्ण_अगर

पूर्णांक drm_legacy_sg_alloc(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_scatter_gather *request = data;
	काष्ठा drm_sg_mem *entry;
	अचिन्हित दीर्घ pages, i, j;

	DRM_DEBUG("\n");

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_SG))
		वापस -EOPNOTSUPP;

	अगर (request->size > SIZE_MAX - PAGE_SIZE)
		वापस -EINVAL;

	अगर (dev->sg)
		वापस -EINVAL;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	pages = (request->size + PAGE_SIZE - 1) / PAGE_SIZE;
	DRM_DEBUG("size=%ld pages=%ld\n", request->size, pages);

	entry->pages = pages;
	entry->pagelist = kसुस्मृति(pages, माप(*entry->pagelist), GFP_KERNEL);
	अगर (!entry->pagelist) अणु
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण

	entry->busaddr = kसुस्मृति(pages, माप(*entry->busaddr), GFP_KERNEL);
	अगर (!entry->busaddr) अणु
		kमुक्त(entry->pagelist);
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण

	entry->भव = vदो_स्मृति_32(pages << PAGE_SHIFT);
	अगर (!entry->भव) अणु
		kमुक्त(entry->busaddr);
		kमुक्त(entry->pagelist);
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण

	/* This also क्रमces the mapping of COW pages, so our page list
	 * will be valid.  Please करोn't हटाओ it...
	 */
	स_रखो(entry->भव, 0, pages << PAGE_SHIFT);

	entry->handle = ScatterHandle((अचिन्हित दीर्घ)entry->भव);

	DRM_DEBUG("handle  = %08lx\n", entry->handle);
	DRM_DEBUG("virtual = %p\n", entry->भव);

	क्रम (i = (अचिन्हित दीर्घ)entry->भव, j = 0; j < pages;
	     i += PAGE_SIZE, j++) अणु
		entry->pagelist[j] = vदो_स्मृति_to_page((व्योम *)i);
		अगर (!entry->pagelist[j])
			जाओ failed;
		SetPageReserved(entry->pagelist[j]);
	पूर्ण

	request->handle = entry->handle;

	dev->sg = entry;

#अगर DEBUG_SCATTER
	/* Verअगरy that each page poपूर्णांकs to its भव address, and vice
	 * versa.
	 */
	अणु
		पूर्णांक error = 0;

		क्रम (i = 0; i < pages; i++) अणु
			अचिन्हित दीर्घ *पंचांगp;

			पंचांगp = page_address(entry->pagelist[i]);
			क्रम (j = 0;
			     j < PAGE_SIZE / माप(अचिन्हित दीर्घ);
			     j++, पंचांगp++) अणु
				*पंचांगp = 0xcafebabe;
			पूर्ण
			पंचांगp = (अचिन्हित दीर्घ *)((u8 *) entry->भव +
						(PAGE_SIZE * i));
			क्रम (j = 0;
			     j < PAGE_SIZE / माप(अचिन्हित दीर्घ);
			     j++, पंचांगp++) अणु
				अगर (*पंचांगp != 0xcafebabe && error == 0) अणु
					error = 1;
					DRM_ERROR("Scatter allocation error, "
						  "pagelist does not match "
						  "virtual mapping\n");
				पूर्ण
			पूर्ण
			पंचांगp = page_address(entry->pagelist[i]);
			क्रम (j = 0;
			     j < PAGE_SIZE / माप(अचिन्हित दीर्घ);
			     j++, पंचांगp++) अणु
				*पंचांगp = 0;
			पूर्ण
		पूर्ण
		अगर (error == 0)
			DRM_ERROR("Scatter allocation matches pagelist\n");
	पूर्ण
#पूर्ण_अगर

	वापस 0;

      failed:
	drm_sg_cleanup(entry);
	वापस -ENOMEM;
पूर्ण

पूर्णांक drm_legacy_sg_मुक्त(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_scatter_gather *request = data;
	काष्ठा drm_sg_mem *entry;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_SG))
		वापस -EOPNOTSUPP;

	entry = dev->sg;
	dev->sg = शून्य;

	अगर (!entry || entry->handle != request->handle)
		वापस -EINVAL;

	DRM_DEBUG("virtual  = %p\n", entry->भव);

	drm_sg_cleanup(entry);

	वापस 0;
पूर्ण
