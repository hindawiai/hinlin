<शैली गुरु>
/*
 * Copyright 1998-2003 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2003 S3 Graphics, Inc. All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * VIA, S3 GRAPHICS, AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"

अटल पूर्णांक via_करो_init_map(काष्ठा drm_device *dev, drm_via_init_t *init)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;

	DRM_DEBUG("\n");

	dev_priv->sarea = drm_legacy_माला_लोarea(dev);
	अगर (!dev_priv->sarea) अणु
		DRM_ERROR("could not find sarea!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		via_करो_cleanup_map(dev);
		वापस -EINVAL;
	पूर्ण

	dev_priv->fb = drm_legacy_findmap(dev, init->fb_offset);
	अगर (!dev_priv->fb) अणु
		DRM_ERROR("could not find framebuffer!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		via_करो_cleanup_map(dev);
		वापस -EINVAL;
	पूर्ण
	dev_priv->mmio = drm_legacy_findmap(dev, init->mmio_offset);
	अगर (!dev_priv->mmio) अणु
		DRM_ERROR("could not find mmio region!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		via_करो_cleanup_map(dev);
		वापस -EINVAL;
	पूर्ण

	dev_priv->sarea_priv =
	    (drm_via_sarea_t *) ((u8 *) dev_priv->sarea->handle +
				 init->sarea_priv_offset);

	dev_priv->agpAddr = init->agpAddr;

	via_init_futex(dev_priv);

	via_init_dmablit(dev);

	dev->dev_निजी = (व्योम *)dev_priv;
	वापस 0;
पूर्ण

पूर्णांक via_करो_cleanup_map(काष्ठा drm_device *dev)
अणु
	via_dma_cleanup(dev);

	वापस 0;
पूर्ण

पूर्णांक via_map_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_init_t *init = data;

	DRM_DEBUG("\n");

	चयन (init->func) अणु
	हाल VIA_INIT_MAP:
		वापस via_करो_init_map(dev, init);
	हाल VIA_CLEANUP_MAP:
		वापस via_करो_cleanup_map(dev);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक via_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ chipset)
अणु
	drm_via_निजी_t *dev_priv;
	पूर्णांक ret = 0;

	dev_priv = kzalloc(माप(drm_via_निजी_t), GFP_KERNEL);
	अगर (dev_priv == शून्य)
		वापस -ENOMEM;

	idr_init(&dev_priv->object_idr);
	dev->dev_निजी = (व्योम *)dev_priv;

	dev_priv->chipset = chipset;

	pci_set_master(dev->pdev);

	ret = drm_vblank_init(dev, 1);
	अगर (ret) अणु
		kमुक्त(dev_priv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम via_driver_unload(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;

	idr_destroy(&dev_priv->object_idr);

	kमुक्त(dev_priv);
पूर्ण
