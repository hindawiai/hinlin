<शैली गुरु>
/*
 * \पile drm_dma.c
 * DMA IOCTL and function support
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Fri Mar 19 14:30:16 1999 by faith@valinux.com
 *
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
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
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_legacy.h"

/**
 * drm_legacy_dma_setup() - Initialize the DMA data.
 *
 * @dev: DRM device.
 * Return: zero on success or a negative value on failure.
 *
 * Allocate and initialize a drm_device_dma काष्ठाure.
 */
पूर्णांक drm_legacy_dma_setup(काष्ठा drm_device *dev)
अणु
	पूर्णांक i;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA) ||
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस 0;

	dev->buf_use = 0;
	atomic_set(&dev->buf_alloc, 0);

	dev->dma = kzalloc(माप(*dev->dma), GFP_KERNEL);
	अगर (!dev->dma)
		वापस -ENOMEM;

	क्रम (i = 0; i <= DRM_MAX_ORDER; i++)
		स_रखो(&dev->dma->bufs[i], 0, माप(dev->dma->bufs[0]));

	वापस 0;
पूर्ण

/**
 * drm_legacy_dma_takeकरोwn() - Cleanup the DMA resources.
 *
 * @dev: DRM device.
 *
 * Free all pages associated with DMA buffers, the buffers and pages lists, and
 * finally the drm_device::dma काष्ठाure itself.
 */
व्योम drm_legacy_dma_takeकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i, j;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA) ||
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	अगर (!dma)
		वापस;

	/* Clear dma buffers */
	क्रम (i = 0; i <= DRM_MAX_ORDER; i++) अणु
		अगर (dma->bufs[i].seg_count) अणु
			DRM_DEBUG("order %d: buf_count = %d,"
				  " seg_count = %d\n",
				  i,
				  dma->bufs[i].buf_count,
				  dma->bufs[i].seg_count);
			क्रम (j = 0; j < dma->bufs[i].seg_count; j++) अणु
				अगर (dma->bufs[i].seglist[j]) अणु
					drm_pci_मुक्त(dev, dma->bufs[i].seglist[j]);
				पूर्ण
			पूर्ण
			kमुक्त(dma->bufs[i].seglist);
		पूर्ण
		अगर (dma->bufs[i].buf_count) अणु
			क्रम (j = 0; j < dma->bufs[i].buf_count; j++) अणु
				kमुक्त(dma->bufs[i].buflist[j].dev_निजी);
			पूर्ण
			kमुक्त(dma->bufs[i].buflist);
		पूर्ण
	पूर्ण

	kमुक्त(dma->buflist);
	kमुक्त(dma->pagelist);
	kमुक्त(dev->dma);
	dev->dma = शून्य;
पूर्ण

/**
 * drm_legacy_मुक्त_buffer() - Free a buffer.
 *
 * @dev: DRM device.
 * @buf: buffer to मुक्त.
 *
 * Resets the fields of \p buf.
 */
व्योम drm_legacy_मुक्त_buffer(काष्ठा drm_device *dev, काष्ठा drm_buf * buf)
अणु
	अगर (!buf)
		वापस;

	buf->रुकोing = 0;
	buf->pending = 0;
	buf->file_priv = शून्य;
	buf->used = 0;
पूर्ण

/**
 * drm_legacy_reclaim_buffers() - Reclaim the buffers.
 *
 * @dev: DRM device.
 * @file_priv: DRM file निजी.
 *
 * Frees each buffer associated with \p file_priv not alपढ़ोy on the hardware.
 */
व्योम drm_legacy_reclaim_buffers(काष्ठा drm_device *dev,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;

	अगर (!dma)
		वापस;
	क्रम (i = 0; i < dma->buf_count; i++) अणु
		अगर (dma->buflist[i]->file_priv == file_priv) अणु
			चयन (dma->buflist[i]->list) अणु
			हाल DRM_LIST_NONE:
				drm_legacy_मुक्त_buffer(dev, dma->buflist[i]);
				अवरोध;
			हाल DRM_LIST_WAIT:
				dma->buflist[i]->list = DRM_LIST_RECLAIM;
				अवरोध;
			शेष:
				/* Buffer alपढ़ोy on hardware. */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
