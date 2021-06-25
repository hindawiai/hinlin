<शैली गुरु>
/* r128_cce.c -- ATI Rage 128 driver -*- linux-c -*-
 * Created: Wed Apr  5 19:24:19 2000 by kevin@precisioninsight.com
 */
/*
 * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.
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
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/r128_drm.h>

#समावेश "r128_drv.h"

#घोषणा R128_FIFO_DEBUG		0

#घोषणा FIRMWARE_NAME		"r128/r128_cce.bin"

MODULE_FIRMWARE(FIRMWARE_NAME);

अटल पूर्णांक R128_READ_PLL(काष्ठा drm_device *dev, पूर्णांक addr)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;

	R128_WRITE8(R128_CLOCK_CNTL_INDEX, addr & 0x1f);
	वापस R128_READ(R128_CLOCK_CNTL_DATA);
पूर्ण

#अगर R128_FIFO_DEBUG
अटल व्योम r128_status(drm_r128_निजी_t *dev_priv)
अणु
	prपूर्णांकk("GUI_STAT           = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_GUI_STAT));
	prपूर्णांकk("PM4_STAT           = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_PM4_STAT));
	prपूर्णांकk("PM4_BUFFER_DL_WPTR = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_PM4_BUFFER_DL_WPTR));
	prपूर्णांकk("PM4_BUFFER_DL_RPTR = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_PM4_BUFFER_DL_RPTR));
	prपूर्णांकk("PM4_MICRO_CNTL     = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_PM4_MICRO_CNTL));
	prपूर्णांकk("PM4_BUFFER_CNTL    = 0x%08x\n",
	       (अचिन्हित पूर्णांक)R128_READ(R128_PM4_BUFFER_CNTL));
पूर्ण
#पूर्ण_अगर

/* ================================================================
 * Engine, FIFO control
 */

अटल पूर्णांक r128_करो_pixcache_flush(drm_r128_निजी_t *dev_priv)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	पंचांगp = R128_READ(R128_PC_NGUI_CTLSTAT) | R128_PC_FLUSH_ALL;
	R128_WRITE(R128_PC_NGUI_CTLSTAT, पंचांगp);

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		अगर (!(R128_READ(R128_PC_NGUI_CTLSTAT) & R128_PC_BUSY))
			वापस 0;
		udelay(1);
	पूर्ण

#अगर R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक r128_करो_रुको_क्रम_fअगरo(drm_r128_निजी_t *dev_priv, पूर्णांक entries)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		पूर्णांक slots = R128_READ(R128_GUI_STAT) & R128_GUI_FIFOCNT_MASK;
		अगर (slots >= entries)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक r128_करो_रुको_क्रम_idle(drm_r128_निजी_t *dev_priv)
अणु
	पूर्णांक i, ret;

	ret = r128_करो_रुको_क्रम_fअगरo(dev_priv, 64);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		अगर (!(R128_READ(R128_GUI_STAT) & R128_GUI_ACTIVE)) अणु
			r128_करो_pixcache_flush(dev_priv);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

#अगर R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

/* ================================================================
 * CCE control, initialization
 */

/* Load the microcode क्रम the CCE */
अटल पूर्णांक r128_cce_load_microcode(drm_r128_निजी_t *dev_priv)
अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा firmware *fw;
	स्थिर __be32 *fw_data;
	पूर्णांक rc, i;

	DRM_DEBUG("\n");

	pdev = platक्रमm_device_रेजिस्टर_simple("r128_cce", 0, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		pr_err("r128_cce: Failed to register firmware\n");
		वापस PTR_ERR(pdev);
	पूर्ण
	rc = request_firmware(&fw, FIRMWARE_NAME, &pdev->dev);
	platक्रमm_device_unरेजिस्टर(pdev);
	अगर (rc) अणु
		pr_err("r128_cce: Failed to load firmware \"%s\"\n",
		       FIRMWARE_NAME);
		वापस rc;
	पूर्ण

	अगर (fw->size != 256 * 8) अणु
		pr_err("r128_cce: Bogus length %zu in firmware \"%s\"\n",
		       fw->size, FIRMWARE_NAME);
		rc = -EINVAL;
		जाओ out_release;
	पूर्ण

	r128_करो_रुको_क्रम_idle(dev_priv);

	fw_data = (स्थिर __be32 *)fw->data;
	R128_WRITE(R128_PM4_MICROCODE_ADDR, 0);
	क्रम (i = 0; i < 256; i++) अणु
		R128_WRITE(R128_PM4_MICROCODE_DATAH,
			   be32_to_cpup(&fw_data[i * 2]));
		R128_WRITE(R128_PM4_MICROCODE_DATAL,
			   be32_to_cpup(&fw_data[i * 2 + 1]));
	पूर्ण

out_release:
	release_firmware(fw);
	वापस rc;
पूर्ण

/* Flush any pending commands to the CCE.  This should only be used just
 * prior to a रुको क्रम idle, as it inक्रमms the engine that the command
 * stream is ending.
 */
अटल व्योम r128_करो_cce_flush(drm_r128_निजी_t *dev_priv)
अणु
	u32 पंचांगp;

	पंचांगp = R128_READ(R128_PM4_BUFFER_DL_WPTR) | R128_PM4_BUFFER_DL_DONE;
	R128_WRITE(R128_PM4_BUFFER_DL_WPTR, पंचांगp);
पूर्ण

/* Wait क्रम the CCE to go idle.
 */
पूर्णांक r128_करो_cce_idle(drm_r128_निजी_t *dev_priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		अगर (GET_RING_HEAD(dev_priv) == dev_priv->ring.tail) अणु
			पूर्णांक pm4stat = R128_READ(R128_PM4_STAT);
			अगर (((pm4stat & R128_PM4_FIFOCNT_MASK) >=
			     dev_priv->cce_fअगरo_size) &&
			    !(pm4stat & (R128_PM4_BUSY |
					 R128_PM4_GUI_ACTIVE))) अणु
				वापस r128_करो_pixcache_flush(dev_priv);
			पूर्ण
		पूर्ण
		udelay(1);
	पूर्ण

#अगर R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
	r128_status(dev_priv);
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

/* Start the Concurrent Command Engine.
 */
अटल व्योम r128_करो_cce_start(drm_r128_निजी_t *dev_priv)
अणु
	r128_करो_रुको_क्रम_idle(dev_priv);

	R128_WRITE(R128_PM4_BUFFER_CNTL,
		   dev_priv->cce_mode | dev_priv->ring.size_l2qw
		   | R128_PM4_BUFFER_CNTL_NOUPDATE);
	R128_READ(R128_PM4_BUFFER_ADDR);	/* as per the sample code */
	R128_WRITE(R128_PM4_MICRO_CNTL, R128_PM4_MICRO_FREERUN);

	dev_priv->cce_running = 1;
पूर्ण

/* Reset the Concurrent Command Engine.  This will not flush any pending
 * commands, so you must रुको क्रम the CCE command stream to complete
 * beक्रमe calling this routine.
 */
अटल व्योम r128_करो_cce_reset(drm_r128_निजी_t *dev_priv)
अणु
	R128_WRITE(R128_PM4_BUFFER_DL_WPTR, 0);
	R128_WRITE(R128_PM4_BUFFER_DL_RPTR, 0);
	dev_priv->ring.tail = 0;
पूर्ण

/* Stop the Concurrent Command Engine.  This will not flush any pending
 * commands, so you must flush the command stream and रुको क्रम the CCE
 * to go idle beक्रमe calling this routine.
 */
अटल व्योम r128_करो_cce_stop(drm_r128_निजी_t *dev_priv)
अणु
	R128_WRITE(R128_PM4_MICRO_CNTL, 0);
	R128_WRITE(R128_PM4_BUFFER_CNTL,
		   R128_PM4_NONPM4 | R128_PM4_BUFFER_CNTL_NOUPDATE);

	dev_priv->cce_running = 0;
पूर्ण

/* Reset the engine.  This will stop the CCE अगर it is running.
 */
अटल पूर्णांक r128_करो_engine_reset(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	u32 घड़ी_cntl_index, mclk_cntl, gen_reset_cntl;

	r128_करो_pixcache_flush(dev_priv);

	घड़ी_cntl_index = R128_READ(R128_CLOCK_CNTL_INDEX);
	mclk_cntl = R128_READ_PLL(dev, R128_MCLK_CNTL);

	R128_WRITE_PLL(R128_MCLK_CNTL,
		       mclk_cntl | R128_FORCE_GCP | R128_FORCE_PIPE3D_CP);

	gen_reset_cntl = R128_READ(R128_GEN_RESET_CNTL);

	/* Taken from the sample code - करो not change */
	R128_WRITE(R128_GEN_RESET_CNTL, gen_reset_cntl | R128_SOFT_RESET_GUI);
	R128_READ(R128_GEN_RESET_CNTL);
	R128_WRITE(R128_GEN_RESET_CNTL, gen_reset_cntl & ~R128_SOFT_RESET_GUI);
	R128_READ(R128_GEN_RESET_CNTL);

	R128_WRITE_PLL(R128_MCLK_CNTL, mclk_cntl);
	R128_WRITE(R128_CLOCK_CNTL_INDEX, घड़ी_cntl_index);
	R128_WRITE(R128_GEN_RESET_CNTL, gen_reset_cntl);

	/* Reset the CCE ring */
	r128_करो_cce_reset(dev_priv);

	/* The CCE is no दीर्घer running after an engine reset */
	dev_priv->cce_running = 0;

	/* Reset any pending vertex, indirect buffers */
	r128_मुक्तlist_reset(dev);

	वापस 0;
पूर्ण

अटल व्योम r128_cce_init_ring_buffer(काष्ठा drm_device *dev,
				      drm_r128_निजी_t *dev_priv)
अणु
	u32 ring_start;
	u32 पंचांगp;

	DRM_DEBUG("\n");

	/* The manual (p. 2) says this address is in "VM space".  This
	 * means it's an offset from the start of AGP space.
	 */
#अगर IS_ENABLED(CONFIG_AGP)
	अगर (!dev_priv->is_pci)
		ring_start = dev_priv->cce_ring->offset - dev->agp->base;
	अन्यथा
#पूर्ण_अगर
		ring_start = dev_priv->cce_ring->offset -
		    (अचिन्हित दीर्घ)dev->sg->भव;

	R128_WRITE(R128_PM4_BUFFER_OFFSET, ring_start | R128_AGP_OFFSET);

	R128_WRITE(R128_PM4_BUFFER_DL_WPTR, 0);
	R128_WRITE(R128_PM4_BUFFER_DL_RPTR, 0);

	/* Set watermark control */
	R128_WRITE(R128_PM4_BUFFER_WM_CNTL,
		   ((R128_WATERMARK_L / 4) << R128_WMA_SHIFT)
		   | ((R128_WATERMARK_M / 4) << R128_WMB_SHIFT)
		   | ((R128_WATERMARK_N / 4) << R128_WMC_SHIFT)
		   | ((R128_WATERMARK_K / 64) << R128_WB_WM_SHIFT));

	/* Force पढ़ो.  Why?  Because it's in the examples... */
	R128_READ(R128_PM4_BUFFER_ADDR);

	/* Turn on bus mastering */
	पंचांगp = R128_READ(R128_BUS_CNTL) & ~R128_BUS_MASTER_DIS;
	R128_WRITE(R128_BUS_CNTL, पंचांगp);
पूर्ण

अटल पूर्णांक r128_करो_init_cce(काष्ठा drm_device *dev, drm_r128_init_t *init)
अणु
	drm_r128_निजी_t *dev_priv;
	पूर्णांक rc;

	DRM_DEBUG("\n");

	अगर (dev->dev_निजी) अणु
		DRM_DEBUG("called when already initialized\n");
		वापस -EINVAL;
	पूर्ण

	dev_priv = kzalloc(माप(drm_r128_निजी_t), GFP_KERNEL);
	अगर (dev_priv == शून्य)
		वापस -ENOMEM;

	dev_priv->is_pci = init->is_pci;

	अगर (dev_priv->is_pci && !dev->sg) अणु
		DRM_ERROR("PCI GART memory not allocated!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण

	dev_priv->usec_समयout = init->usec_समयout;
	अगर (dev_priv->usec_समयout < 1 ||
	    dev_priv->usec_समयout > R128_MAX_USEC_TIMEOUT) अणु
		DRM_DEBUG("TIMEOUT problem!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण

	dev_priv->cce_mode = init->cce_mode;

	/* GH: Simple idle check.
	 */
	atomic_set(&dev_priv->idle_count, 0);

	/* We करोn't support anything other than bus-mastering ring mode,
	 * but the ring can be in either AGP or PCI space क्रम the ring
	 * पढ़ो poपूर्णांकer.
	 */
	अगर ((init->cce_mode != R128_PM4_192BM) &&
	    (init->cce_mode != R128_PM4_128BM_64INDBM) &&
	    (init->cce_mode != R128_PM4_64BM_128INDBM) &&
	    (init->cce_mode != R128_PM4_64BM_64VCBM_64INDBM)) अणु
		DRM_DEBUG("Bad cce_mode!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण

	चयन (init->cce_mode) अणु
	हाल R128_PM4_NONPM4:
		dev_priv->cce_fअगरo_size = 0;
		अवरोध;
	हाल R128_PM4_192PIO:
	हाल R128_PM4_192BM:
		dev_priv->cce_fअगरo_size = 192;
		अवरोध;
	हाल R128_PM4_128PIO_64INDBM:
	हाल R128_PM4_128BM_64INDBM:
		dev_priv->cce_fअगरo_size = 128;
		अवरोध;
	हाल R128_PM4_64PIO_128INDBM:
	हाल R128_PM4_64BM_128INDBM:
	हाल R128_PM4_64PIO_64VCBM_64INDBM:
	हाल R128_PM4_64BM_64VCBM_64INDBM:
	हाल R128_PM4_64PIO_64VCPIO_64INDPIO:
		dev_priv->cce_fअगरo_size = 64;
		अवरोध;
	पूर्ण

	चयन (init->fb_bpp) अणु
	हाल 16:
		dev_priv->color_fmt = R128_DATATYPE_RGB565;
		अवरोध;
	हाल 32:
	शेष:
		dev_priv->color_fmt = R128_DATATYPE_ARGB8888;
		अवरोध;
	पूर्ण
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;

	चयन (init->depth_bpp) अणु
	हाल 16:
		dev_priv->depth_fmt = R128_DATATYPE_RGB565;
		अवरोध;
	हाल 24:
	हाल 32:
	शेष:
		dev_priv->depth_fmt = R128_DATATYPE_ARGB8888;
		अवरोध;
	पूर्ण
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->depth_pitch = init->depth_pitch;
	dev_priv->span_offset = init->span_offset;

	dev_priv->front_pitch_offset_c = (((dev_priv->front_pitch / 8) << 21) |
					  (dev_priv->front_offset >> 5));
	dev_priv->back_pitch_offset_c = (((dev_priv->back_pitch / 8) << 21) |
					 (dev_priv->back_offset >> 5));
	dev_priv->depth_pitch_offset_c = (((dev_priv->depth_pitch / 8) << 21) |
					  (dev_priv->depth_offset >> 5) |
					  R128_DST_TILE);
	dev_priv->span_pitch_offset_c = (((dev_priv->depth_pitch / 8) << 21) |
					 (dev_priv->span_offset >> 5));

	dev_priv->sarea = drm_legacy_माला_लोarea(dev);
	अगर (!dev_priv->sarea) अणु
		DRM_ERROR("could not find sarea!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण

	dev_priv->mmio = drm_legacy_findmap(dev, init->mmio_offset);
	अगर (!dev_priv->mmio) अणु
		DRM_ERROR("could not find mmio region!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण
	dev_priv->cce_ring = drm_legacy_findmap(dev, init->ring_offset);
	अगर (!dev_priv->cce_ring) अणु
		DRM_ERROR("could not find cce ring region!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण
	dev_priv->ring_rptr = drm_legacy_findmap(dev, init->ring_rptr_offset);
	अगर (!dev_priv->ring_rptr) अणु
		DRM_ERROR("could not find ring read pointer!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण
	dev->agp_buffer_token = init->buffers_offset;
	dev->agp_buffer_map = drm_legacy_findmap(dev, init->buffers_offset);
	अगर (!dev->agp_buffer_map) अणु
		DRM_ERROR("could not find dma buffer region!\n");
		dev->dev_निजी = (व्योम *)dev_priv;
		r128_करो_cleanup_cce(dev);
		वापस -EINVAL;
	पूर्ण

	अगर (!dev_priv->is_pci) अणु
		dev_priv->agp_textures =
		    drm_legacy_findmap(dev, init->agp_textures_offset);
		अगर (!dev_priv->agp_textures) अणु
			DRM_ERROR("could not find agp texture region!\n");
			dev->dev_निजी = (व्योम *)dev_priv;
			r128_करो_cleanup_cce(dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_priv->sarea_priv =
	    (drm_r128_sarea_t *) ((u8 *) dev_priv->sarea->handle +
				  init->sarea_priv_offset);

#अगर IS_ENABLED(CONFIG_AGP)
	अगर (!dev_priv->is_pci) अणु
		drm_legacy_ioremap_wc(dev_priv->cce_ring, dev);
		drm_legacy_ioremap_wc(dev_priv->ring_rptr, dev);
		drm_legacy_ioremap_wc(dev->agp_buffer_map, dev);
		अगर (!dev_priv->cce_ring->handle ||
		    !dev_priv->ring_rptr->handle ||
		    !dev->agp_buffer_map->handle) अणु
			DRM_ERROR("Could not ioremap agp regions!\n");
			dev->dev_निजी = (व्योम *)dev_priv;
			r128_करो_cleanup_cce(dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		dev_priv->cce_ring->handle =
			(व्योम *)(अचिन्हित दीर्घ)dev_priv->cce_ring->offset;
		dev_priv->ring_rptr->handle =
			(व्योम *)(अचिन्हित दीर्घ)dev_priv->ring_rptr->offset;
		dev->agp_buffer_map->handle =
			(व्योम *)(अचिन्हित दीर्घ)dev->agp_buffer_map->offset;
	पूर्ण

#अगर IS_ENABLED(CONFIG_AGP)
	अगर (!dev_priv->is_pci)
		dev_priv->cce_buffers_offset = dev->agp->base;
	अन्यथा
#पूर्ण_अगर
		dev_priv->cce_buffers_offset = (अचिन्हित दीर्घ)dev->sg->भव;

	dev_priv->ring.start = (u32 *) dev_priv->cce_ring->handle;
	dev_priv->ring.end = ((u32 *) dev_priv->cce_ring->handle
			      + init->ring_size / माप(u32));
	dev_priv->ring.size = init->ring_size;
	dev_priv->ring.size_l2qw = order_base_2(init->ring_size / 8);

	dev_priv->ring.tail_mask = (dev_priv->ring.size / माप(u32)) - 1;

	dev_priv->ring.high_mark = 128;

	dev_priv->sarea_priv->last_frame = 0;
	R128_WRITE(R128_LAST_FRAME_REG, dev_priv->sarea_priv->last_frame);

	dev_priv->sarea_priv->last_dispatch = 0;
	R128_WRITE(R128_LAST_DISPATCH_REG, dev_priv->sarea_priv->last_dispatch);

#अगर IS_ENABLED(CONFIG_AGP)
	अगर (dev_priv->is_pci) अणु
#पूर्ण_अगर
		dev_priv->gart_info.table_mask = DMA_BIT_MASK(32);
		dev_priv->gart_info.gart_table_location = DRM_ATI_GART_MAIN;
		dev_priv->gart_info.table_size = R128_PCIGART_TABLE_SIZE;
		dev_priv->gart_info.addr = शून्य;
		dev_priv->gart_info.bus_addr = 0;
		dev_priv->gart_info.gart_reg_अगर = DRM_ATI_GART_PCI;
		rc = drm_ati_pcigart_init(dev, &dev_priv->gart_info);
		अगर (rc) अणु
			DRM_ERROR("failed to init PCI GART!\n");
			dev->dev_निजी = (व्योम *)dev_priv;
			r128_करो_cleanup_cce(dev);
			वापस rc;
		पूर्ण
		R128_WRITE(R128_PCI_GART_PAGE, dev_priv->gart_info.bus_addr);
#अगर IS_ENABLED(CONFIG_AGP)
	पूर्ण
#पूर्ण_अगर

	r128_cce_init_ring_buffer(dev, dev_priv);
	rc = r128_cce_load_microcode(dev_priv);

	dev->dev_निजी = (व्योम *)dev_priv;

	r128_करो_engine_reset(dev);

	अगर (rc) अणु
		DRM_ERROR("Failed to load firmware!\n");
		r128_करो_cleanup_cce(dev);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक r128_करो_cleanup_cce(काष्ठा drm_device *dev)
अणु

	/* Make sure पूर्णांकerrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_निजी
	 * is मुक्तd, it's too late.
	 */
	अगर (dev->irq_enabled)
		drm_irq_uninstall(dev);

	अगर (dev->dev_निजी) अणु
		drm_r128_निजी_t *dev_priv = dev->dev_निजी;

#अगर IS_ENABLED(CONFIG_AGP)
		अगर (!dev_priv->is_pci) अणु
			अगर (dev_priv->cce_ring != शून्य)
				drm_legacy_ioremapमुक्त(dev_priv->cce_ring, dev);
			अगर (dev_priv->ring_rptr != शून्य)
				drm_legacy_ioremapमुक्त(dev_priv->ring_rptr, dev);
			अगर (dev->agp_buffer_map != शून्य) अणु
				drm_legacy_ioremapमुक्त(dev->agp_buffer_map, dev);
				dev->agp_buffer_map = शून्य;
			पूर्ण
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			अगर (dev_priv->gart_info.bus_addr)
				अगर (!drm_ati_pcigart_cleanup(dev,
							&dev_priv->gart_info))
					DRM_ERROR
					    ("failed to cleanup PCI GART!\n");
		पूर्ण

		kमुक्त(dev->dev_निजी);
		dev->dev_निजी = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक r128_cce_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_init_t *init = data;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	चयन (init->func) अणु
	हाल R128_INIT_CCE:
		वापस r128_करो_init_cce(dev, init);
	हाल R128_CLEANUP_CCE:
		वापस r128_करो_cleanup_cce(dev);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक r128_cce_start(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	अगर (dev_priv->cce_running || dev_priv->cce_mode == R128_PM4_NONPM4) अणु
		DRM_DEBUG("while CCE running\n");
		वापस 0;
	पूर्ण

	r128_करो_cce_start(dev_priv);

	वापस 0;
पूर्ण

/* Stop the CCE.  The engine must have been idled beक्रमe calling this
 * routine.
 */
पूर्णांक r128_cce_stop(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_cce_stop_t *stop = data;
	पूर्णांक ret;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	/* Flush any pending CCE commands.  This ensures any outstanding
	 * commands are exectuted by the engine beक्रमe we turn it off.
	 */
	अगर (stop->flush)
		r128_करो_cce_flush(dev_priv);

	/* If we fail to make the engine go idle, we वापस an error
	 * code so that the DRM ioctl wrapper can try again.
	 */
	अगर (stop->idle) अणु
		ret = r128_करो_cce_idle(dev_priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Finally, we can turn off the CCE.  If the engine isn't idle,
	 * we will get some dropped triangles as they won't be fully
	 * rendered beक्रमe the CCE is shut करोwn.
	 */
	r128_करो_cce_stop(dev_priv);

	/* Reset the engine */
	r128_करो_engine_reset(dev);

	वापस 0;
पूर्ण

/* Just reset the CCE ring.  Called as part of an X Server engine reset.
 */
पूर्णांक r128_cce_reset(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	r128_करो_cce_reset(dev_priv);

	/* The CCE is no दीर्घer running after an engine reset */
	dev_priv->cce_running = 0;

	वापस 0;
पूर्ण

पूर्णांक r128_cce_idle(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	अगर (dev_priv->cce_running)
		r128_करो_cce_flush(dev_priv);

	वापस r128_करो_cce_idle(dev_priv);
पूर्ण

पूर्णांक r128_engine_reset(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev->dev_निजी);

	वापस r128_करो_engine_reset(dev);
पूर्ण

पूर्णांक r128_fullscreen(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस -EINVAL;
पूर्ण

/* ================================================================
 * Freelist management
 */
#घोषणा R128_BUFFER_USED	0xffffffff
#घोषणा R128_BUFFER_FREE	0

#अगर 0
अटल पूर्णांक r128_मुक्तlist_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_buf *buf;
	drm_r128_buf_priv_t *buf_priv;
	drm_r128_मुक्तlist_t *entry;
	पूर्णांक i;

	dev_priv->head = kzalloc(माप(drm_r128_मुक्तlist_t), GFP_KERNEL);
	अगर (dev_priv->head == शून्य)
		वापस -ENOMEM;

	dev_priv->head->age = R128_BUFFER_USED;

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		buf = dma->buflist[i];
		buf_priv = buf->dev_निजी;

		entry = kदो_स्मृति(माप(drm_r128_मुक्तlist_t), GFP_KERNEL);
		अगर (!entry)
			वापस -ENOMEM;

		entry->age = R128_BUFFER_FREE;
		entry->buf = buf;
		entry->prev = dev_priv->head;
		entry->next = dev_priv->head->next;
		अगर (!entry->next)
			dev_priv->tail = entry;

		buf_priv->discard = 0;
		buf_priv->dispatched = 0;
		buf_priv->list_entry = entry;

		dev_priv->head->next = entry;

		अगर (dev_priv->head->next)
			dev_priv->head->next->prev = entry;
	पूर्ण

	वापस 0;

पूर्ण
#पूर्ण_अगर

अटल काष्ठा drm_buf *r128_मुक्तlist_get(काष्ठा drm_device * dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;
	drm_r128_buf_priv_t *buf_priv;
	काष्ठा drm_buf *buf;
	पूर्णांक i, t;

	/* FIXME: Optimize -- use मुक्तlist code */

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		buf = dma->buflist[i];
		buf_priv = buf->dev_निजी;
		अगर (!buf->file_priv)
			वापस buf;
	पूर्ण

	क्रम (t = 0; t < dev_priv->usec_समयout; t++) अणु
		u32 करोne_age = R128_READ(R128_LAST_DISPATCH_REG);

		क्रम (i = 0; i < dma->buf_count; i++) अणु
			buf = dma->buflist[i];
			buf_priv = buf->dev_निजी;
			अगर (buf->pending && buf_priv->age <= करोne_age) अणु
				/* The buffer has been processed, so it
				 * can now be used.
				 */
				buf->pending = 0;
				वापस buf;
			पूर्ण
		पूर्ण
		udelay(1);
	पूर्ण

	DRM_DEBUG("returning NULL!\n");
	वापस शून्य;
पूर्ण

व्योम r128_मुक्तlist_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_r128_buf_priv_t *buf_priv = buf->dev_निजी;
		buf_priv->age = 0;
	पूर्ण
पूर्ण

/* ================================================================
 * CCE command submission
 */

पूर्णांक r128_रुको_ring(drm_r128_निजी_t *dev_priv, पूर्णांक n)
अणु
	drm_r128_ring_buffer_t *ring = &dev_priv->ring;
	पूर्णांक i;

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		r128_update_ring_snapshot(dev_priv);
		अगर (ring->space >= n)
			वापस 0;
		udelay(1);
	पूर्ण

	/* FIXME: This is being ignored... */
	DRM_ERROR("failed!\n");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक r128_cce_get_buffers(काष्ठा drm_device *dev,
				काष्ठा drm_file *file_priv,
				काष्ठा drm_dma *d)
अणु
	पूर्णांक i;
	काष्ठा drm_buf *buf;

	क्रम (i = d->granted_count; i < d->request_count; i++) अणु
		buf = r128_मुक्तlist_get(dev);
		अगर (!buf)
			वापस -EAGAIN;

		buf->file_priv = file_priv;

		अगर (copy_to_user(&d->request_indices[i], &buf->idx,
				     माप(buf->idx)))
			वापस -EFAULT;
		अगर (copy_to_user(&d->request_sizes[i], &buf->total,
				     माप(buf->total)))
			वापस -EFAULT;

		d->granted_count++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r128_cce_buffers(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक ret = 0;
	काष्ठा drm_dma *d = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	/* Please करोn't send us buffers.
	 */
	अगर (d->send_count != 0) अणु
		DRM_ERROR("Process %d trying to send %d buffers via drmDMA\n",
			  task_pid_nr(current), d->send_count);
		वापस -EINVAL;
	पूर्ण

	/* We'll send you buffers.
	 */
	अगर (d->request_count < 0 || d->request_count > dma->buf_count) अणु
		DRM_ERROR("Process %d trying to get %d buffers (of %d max)\n",
			  task_pid_nr(current), d->request_count, dma->buf_count);
		वापस -EINVAL;
	पूर्ण

	d->granted_count = 0;

	अगर (d->request_count)
		ret = r128_cce_get_buffers(dev, file_priv, d);

	वापस ret;
पूर्ण
