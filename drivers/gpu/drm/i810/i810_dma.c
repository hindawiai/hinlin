<शैली गुरु>
/* i810_dma.c -- DMA support क्रम the i810 -*- linux-c -*-
 * Created: Mon Dec 13 01:50:01 1999 by jharपंचांगann@precisioninsight.com
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors: Rickard E. (Rik) Faith <faith@valinux.com>
 *	    Jeff Harपंचांगann <jharपंचांगann@valinux.com>
 *          Keith Whitwell <keith@tungstengraphics.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/mman.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/i810_drm.h>

#समावेश "i810_drv.h"

#घोषणा I810_BUF_FREE		2
#घोषणा I810_BUF_CLIENT		1
#घोषणा I810_BUF_HARDWARE	0

#घोषणा I810_BUF_UNMAPPED 0
#घोषणा I810_BUF_MAPPED   1

अटल काष्ठा drm_buf *i810_मुक्तlist_get(काष्ठा drm_device * dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;
	पूर्णांक used;

	/* Linear search might not be the best solution */

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
		/* In use is alपढ़ोy a poपूर्णांकer */
		used = cmpxchg(buf_priv->in_use, I810_BUF_FREE,
			       I810_BUF_CLIENT);
		अगर (used == I810_BUF_FREE)
			वापस buf;
	पूर्ण
	वापस शून्य;
पूर्ण

/* This should only be called अगर the buffer is not sent to the hardware
 * yet, the hardware updates in use क्रम us once its on the ring buffer.
 */

अटल पूर्णांक i810_मुक्तlist_put(काष्ठा drm_device *dev, काष्ठा drm_buf *buf)
अणु
	drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
	पूर्णांक used;

	/* In use is alपढ़ोy a poपूर्णांकer */
	used = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT, I810_BUF_FREE);
	अगर (used != I810_BUF_CLIENT) अणु
		DRM_ERROR("Freeing buffer thats not in use : %d\n", buf->idx);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i810_mmap_buffers(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev;
	drm_i810_निजी_t *dev_priv;
	काष्ठा drm_buf *buf;
	drm_i810_buf_priv_t *buf_priv;

	dev = priv->minor->dev;
	dev_priv = dev->dev_निजी;
	buf = dev_priv->mmap_buffer;
	buf_priv = buf->dev_निजी;

	vma->vm_flags |= VM_DONTCOPY;

	buf_priv->currently_mapped = I810_BUF_MAPPED;

	अगर (io_remap_pfn_range(vma, vma->vm_start,
			       vma->vm_pgoff,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot))
		वापस -EAGAIN;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations i810_buffer_fops = अणु
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = i810_mmap_buffers,
	.compat_ioctl = drm_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक i810_map_buffer(काष्ठा drm_buf *buf, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device *dev = file_priv->minor->dev;
	drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	स्थिर काष्ठा file_operations *old_fops;
	पूर्णांक retcode = 0;

	अगर (buf_priv->currently_mapped == I810_BUF_MAPPED)
		वापस -EINVAL;

	/* This is all entirely broken */
	old_fops = file_priv->filp->f_op;
	file_priv->filp->f_op = &i810_buffer_fops;
	dev_priv->mmap_buffer = buf;
	buf_priv->भव = (व्योम *)vm_mmap(file_priv->filp, 0, buf->total,
					    PROT_READ | PROT_WRITE,
					    MAP_SHARED, buf->bus_address);
	dev_priv->mmap_buffer = शून्य;
	file_priv->filp->f_op = old_fops;
	अगर (IS_ERR(buf_priv->भव)) अणु
		/* Real error */
		DRM_ERROR("mmap error\n");
		retcode = PTR_ERR(buf_priv->भव);
		buf_priv->भव = शून्य;
	पूर्ण

	वापस retcode;
पूर्ण

अटल पूर्णांक i810_unmap_buffer(काष्ठा drm_buf *buf)
अणु
	drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
	पूर्णांक retcode = 0;

	अगर (buf_priv->currently_mapped != I810_BUF_MAPPED)
		वापस -EINVAL;

	retcode = vm_munmap((अचिन्हित दीर्घ)buf_priv->भव,
			    (माप_प्रकार) buf->total);

	buf_priv->currently_mapped = I810_BUF_UNMAPPED;
	buf_priv->भव = शून्य;

	वापस retcode;
पूर्ण

अटल पूर्णांक i810_dma_get_buffer(काष्ठा drm_device *dev, drm_i810_dma_t *d,
			       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_buf *buf;
	drm_i810_buf_priv_t *buf_priv;
	पूर्णांक retcode = 0;

	buf = i810_मुक्तlist_get(dev);
	अगर (!buf) अणु
		retcode = -ENOMEM;
		DRM_DEBUG("retcode=%d\n", retcode);
		वापस retcode;
	पूर्ण

	retcode = i810_map_buffer(buf, file_priv);
	अगर (retcode) अणु
		i810_मुक्तlist_put(dev, buf);
		DRM_ERROR("mapbuf failed, retcode %d\n", retcode);
		वापस retcode;
	पूर्ण
	buf->file_priv = file_priv;
	buf_priv = buf->dev_निजी;
	d->granted = 1;
	d->request_idx = buf->idx;
	d->request_size = buf->total;
	d->भव = buf_priv->भव;

	वापस retcode;
पूर्ण

अटल पूर्णांक i810_dma_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;

	/* Make sure पूर्णांकerrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_निजी
	 * is मुक्तd, it's too late.
	 */
	अगर (drm_core_check_feature(dev, DRIVER_HAVE_IRQ) && dev->irq_enabled)
		drm_irq_uninstall(dev);

	अगर (dev->dev_निजी) अणु
		पूर्णांक i;
		drm_i810_निजी_t *dev_priv =
		    (drm_i810_निजी_t *) dev->dev_निजी;

		अगर (dev_priv->ring.भव_start)
			drm_legacy_ioremapमुक्त(&dev_priv->ring.map, dev);
		अगर (dev_priv->hw_status_page) अणु
			dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
					  dev_priv->hw_status_page,
					  dev_priv->dma_status_page);
		पूर्ण
		kमुक्त(dev->dev_निजी);
		dev->dev_निजी = शून्य;

		क्रम (i = 0; i < dma->buf_count; i++) अणु
			काष्ठा drm_buf *buf = dma->buflist[i];
			drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;

			अगर (buf_priv->kernel_भव && buf->total)
				drm_legacy_ioremapमुक्त(&buf_priv->map, dev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i810_रुको_ring(काष्ठा drm_device *dev, पूर्णांक n)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_ring_buffer_t *ring = &(dev_priv->ring);
	पूर्णांक iters = 0;
	अचिन्हित दीर्घ end;
	अचिन्हित पूर्णांक last_head = I810_READ(LP_RING + RING_HEAD) & HEAD_ADDR;

	end = jअगरfies + (HZ * 3);
	जबतक (ring->space < n) अणु
		ring->head = I810_READ(LP_RING + RING_HEAD) & HEAD_ADDR;
		ring->space = ring->head - (ring->tail + 8);
		अगर (ring->space < 0)
			ring->space += ring->Size;

		अगर (ring->head != last_head) अणु
			end = jअगरfies + (HZ * 3);
			last_head = ring->head;
		पूर्ण

		iters++;
		अगर (समय_beक्रमe(end, jअगरfies)) अणु
			DRM_ERROR("space: %d wanted %d\n", ring->space, n);
			DRM_ERROR("lockup\n");
			जाओ out_रुको_ring;
		पूर्ण
		udelay(1);
	पूर्ण

out_रुको_ring:
	वापस iters;
पूर्ण

अटल व्योम i810_kernel_lost_context(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_ring_buffer_t *ring = &(dev_priv->ring);

	ring->head = I810_READ(LP_RING + RING_HEAD) & HEAD_ADDR;
	ring->tail = I810_READ(LP_RING + RING_TAIL);
	ring->space = ring->head - (ring->tail + 8);
	अगर (ring->space < 0)
		ring->space += ring->Size;
पूर्ण

अटल पूर्णांक i810_मुक्तlist_init(काष्ठा drm_device *dev, drm_i810_निजी_t *dev_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक my_idx = 24;
	u32 *hw_status = (u32 *) (dev_priv->hw_status_page + my_idx);
	पूर्णांक i;

	अगर (dma->buf_count > 1019) अणु
		/* Not enough space in the status page क्रम the मुक्तlist */
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;

		buf_priv->in_use = hw_status++;
		buf_priv->my_use_idx = my_idx;
		my_idx += 4;

		*buf_priv->in_use = I810_BUF_FREE;

		buf_priv->map.offset = buf->bus_address;
		buf_priv->map.size = buf->total;
		buf_priv->map.type = _DRM_AGP;
		buf_priv->map.flags = 0;
		buf_priv->map.mtrr = 0;

		drm_legacy_ioremap(&buf_priv->map, dev);
		buf_priv->kernel_भव = buf_priv->map.handle;

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i810_dma_initialize(काष्ठा drm_device *dev,
			       drm_i810_निजी_t *dev_priv,
			       drm_i810_init_t *init)
अणु
	काष्ठा drm_map_list *r_list;
	स_रखो(dev_priv, 0, माप(drm_i810_निजी_t));

	list_क्रम_each_entry(r_list, &dev->maplist, head) अणु
		अगर (r_list->map &&
		    r_list->map->type == _DRM_SHM &&
		    r_list->map->flags & _DRM_CONTAINS_LOCK) अणु
			dev_priv->sarea_map = r_list->map;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!dev_priv->sarea_map) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("can not find sarea!\n");
		वापस -EINVAL;
	पूर्ण
	dev_priv->mmio_map = drm_legacy_findmap(dev, init->mmio_offset);
	अगर (!dev_priv->mmio_map) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("can not find mmio map!\n");
		वापस -EINVAL;
	पूर्ण
	dev->agp_buffer_token = init->buffers_offset;
	dev->agp_buffer_map = drm_legacy_findmap(dev, init->buffers_offset);
	अगर (!dev->agp_buffer_map) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("can not find dma buffer map!\n");
		वापस -EINVAL;
	पूर्ण

	dev_priv->sarea_priv = (drm_i810_sarea_t *)
	    ((u8 *) dev_priv->sarea_map->handle + init->sarea_priv_offset);

	dev_priv->ring.Start = init->ring_start;
	dev_priv->ring.End = init->ring_end;
	dev_priv->ring.Size = init->ring_size;

	dev_priv->ring.map.offset = dev->agp->base + init->ring_start;
	dev_priv->ring.map.size = init->ring_size;
	dev_priv->ring.map.type = _DRM_AGP;
	dev_priv->ring.map.flags = 0;
	dev_priv->ring.map.mtrr = 0;

	drm_legacy_ioremap(&dev_priv->ring.map, dev);

	अगर (dev_priv->ring.map.handle == शून्य) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("can not ioremap virtual address for"
			  " ring buffer\n");
		वापस -ENOMEM;
	पूर्ण

	dev_priv->ring.भव_start = dev_priv->ring.map.handle;

	dev_priv->ring.tail_mask = dev_priv->ring.Size - 1;

	dev_priv->w = init->w;
	dev_priv->h = init->h;
	dev_priv->pitch = init->pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->front_offset = init->front_offset;

	dev_priv->overlay_offset = init->overlay_offset;
	dev_priv->overlay_physical = init->overlay_physical;

	dev_priv->front_di1 = init->front_offset | init->pitch_bits;
	dev_priv->back_di1 = init->back_offset | init->pitch_bits;
	dev_priv->zi1 = init->depth_offset | init->pitch_bits;

	/* Program Hardware Status Page */
	dev_priv->hw_status_page =
		dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
				   &dev_priv->dma_status_page, GFP_KERNEL);
	अगर (!dev_priv->hw_status_page) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("Can not allocate hardware status page\n");
		वापस -ENOMEM;
	पूर्ण
	DRM_DEBUG("hw status page @ %p\n", dev_priv->hw_status_page);

	I810_WRITE(0x02080, dev_priv->dma_status_page);
	DRM_DEBUG("Enabled hardware status page\n");

	/* Now we need to init our मुक्तlist */
	अगर (i810_मुक्तlist_init(dev, dev_priv) != 0) अणु
		dev->dev_निजी = (व्योम *)dev_priv;
		i810_dma_cleanup(dev);
		DRM_ERROR("Not enough space in the status page for"
			  " the freelist\n");
		वापस -ENOMEM;
	पूर्ण
	dev->dev_निजी = (व्योम *)dev_priv;

	वापस 0;
पूर्ण

अटल पूर्णांक i810_dma_init(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv;
	drm_i810_init_t *init = data;
	पूर्णांक retcode = 0;

	चयन (init->func) अणु
	हाल I810_INIT_DMA_1_4:
		DRM_INFO("Using v1.4 init.\n");
		dev_priv = kदो_स्मृति(माप(drm_i810_निजी_t), GFP_KERNEL);
		अगर (dev_priv == शून्य)
			वापस -ENOMEM;
		retcode = i810_dma_initialize(dev, dev_priv, init);
		अवरोध;

	हाल I810_CLEANUP_DMA:
		DRM_INFO("DMA Cleanup\n");
		retcode = i810_dma_cleanup(dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस retcode;
पूर्ण

/* Most efficient way to verअगरy state क्रम the i810 is as it is
 * emitted.  Non-conक्रमmant state is silently dropped.
 *
 * Use 'volatile' & local var पंचांगp to क्रमce the emitted values to be
 * identical to the verअगरied ones.
 */
अटल व्योम i810EmitContextVerअगरied(काष्ठा drm_device *dev,
				    अस्थिर अचिन्हित पूर्णांक *code)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक i, j = 0;
	अचिन्हित पूर्णांक पंचांगp;
	RING_LOCALS;

	BEGIN_LP_RING(I810_CTX_SETUP_SIZE);

	OUT_RING(GFX_OP_COLOR_FACTOR);
	OUT_RING(code[I810_CTXREG_CF1]);

	OUT_RING(GFX_OP_STIPPLE);
	OUT_RING(code[I810_CTXREG_ST1]);

	क्रम (i = 4; i < I810_CTX_SETUP_SIZE; i++) अणु
		पंचांगp = code[i];

		अगर ((पंचांगp & (7 << 29)) == (3 << 29) &&
		    (पंचांगp & (0x1f << 24)) < (0x1d << 24)) अणु
			OUT_RING(पंचांगp);
			j++;
		पूर्ण अन्यथा
			prपूर्णांकk("constext state dropped!!!\n");
	पूर्ण

	अगर (j & 1)
		OUT_RING(0);

	ADVANCE_LP_RING();
पूर्ण

अटल व्योम i810EmitTexVerअगरied(काष्ठा drm_device *dev, अस्थिर अचिन्हित पूर्णांक *code)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक i, j = 0;
	अचिन्हित पूर्णांक पंचांगp;
	RING_LOCALS;

	BEGIN_LP_RING(I810_TEX_SETUP_SIZE);

	OUT_RING(GFX_OP_MAP_INFO);
	OUT_RING(code[I810_TEXREG_MI1]);
	OUT_RING(code[I810_TEXREG_MI2]);
	OUT_RING(code[I810_TEXREG_MI3]);

	क्रम (i = 4; i < I810_TEX_SETUP_SIZE; i++) अणु
		पंचांगp = code[i];

		अगर ((पंचांगp & (7 << 29)) == (3 << 29) &&
		    (पंचांगp & (0x1f << 24)) < (0x1d << 24)) अणु
			OUT_RING(पंचांगp);
			j++;
		पूर्ण अन्यथा
			prपूर्णांकk("texture state dropped!!!\n");
	पूर्ण

	अगर (j & 1)
		OUT_RING(0);

	ADVANCE_LP_RING();
पूर्ण

/* Need to करो some additional checking when setting the dest buffer.
 */
अटल व्योम i810EmitDestVerअगरied(काष्ठा drm_device *dev,
				 अस्थिर अचिन्हित पूर्णांक *code)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	अचिन्हित पूर्णांक पंचांगp;
	RING_LOCALS;

	BEGIN_LP_RING(I810_DEST_SETUP_SIZE + 2);

	पंचांगp = code[I810_DESTREG_DI1];
	अगर (पंचांगp == dev_priv->front_di1 || पंचांगp == dev_priv->back_di1) अणु
		OUT_RING(CMD_OP_DESTBUFFER_INFO);
		OUT_RING(पंचांगp);
	पूर्ण अन्यथा
		DRM_DEBUG("bad di1 %x (allow %x or %x)\n",
			  पंचांगp, dev_priv->front_di1, dev_priv->back_di1);

	/* invarient:
	 */
	OUT_RING(CMD_OP_Z_BUFFER_INFO);
	OUT_RING(dev_priv->zi1);

	OUT_RING(GFX_OP_DESTBUFFER_VARS);
	OUT_RING(code[I810_DESTREG_DV1]);

	OUT_RING(GFX_OP_DRAWRECT_INFO);
	OUT_RING(code[I810_DESTREG_DR1]);
	OUT_RING(code[I810_DESTREG_DR2]);
	OUT_RING(code[I810_DESTREG_DR3]);
	OUT_RING(code[I810_DESTREG_DR4]);
	OUT_RING(0);

	ADVANCE_LP_RING();
पूर्ण

अटल व्योम i810EmitState(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित पूर्णांक dirty = sarea_priv->dirty;

	DRM_DEBUG("%x\n", dirty);

	अगर (dirty & I810_UPLOAD_BUFFERS) अणु
		i810EmitDestVerअगरied(dev, sarea_priv->BufferState);
		sarea_priv->dirty &= ~I810_UPLOAD_BUFFERS;
	पूर्ण

	अगर (dirty & I810_UPLOAD_CTX) अणु
		i810EmitContextVerअगरied(dev, sarea_priv->ContextState);
		sarea_priv->dirty &= ~I810_UPLOAD_CTX;
	पूर्ण

	अगर (dirty & I810_UPLOAD_TEX0) अणु
		i810EmitTexVerअगरied(dev, sarea_priv->TexState[0]);
		sarea_priv->dirty &= ~I810_UPLOAD_TEX0;
	पूर्ण

	अगर (dirty & I810_UPLOAD_TEX1) अणु
		i810EmitTexVerअगरied(dev, sarea_priv->TexState[1]);
		sarea_priv->dirty &= ~I810_UPLOAD_TEX1;
	पूर्ण
पूर्ण

/* need to verअगरy
 */
अटल व्योम i810_dma_dispatch_clear(काष्ठा drm_device *dev, पूर्णांक flags,
				    अचिन्हित पूर्णांक clear_color,
				    अचिन्हित पूर्णांक clear_zval)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक nbox = sarea_priv->nbox;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक pitch = dev_priv->pitch;
	पूर्णांक cpp = 2;
	पूर्णांक i;
	RING_LOCALS;

	अगर (dev_priv->current_page == 1) अणु
		अचिन्हित पूर्णांक पंचांगp = flags;

		flags &= ~(I810_FRONT | I810_BACK);
		अगर (पंचांगp & I810_FRONT)
			flags |= I810_BACK;
		अगर (पंचांगp & I810_BACK)
			flags |= I810_FRONT;
	पूर्ण

	i810_kernel_lost_context(dev);

	अगर (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	क्रम (i = 0; i < nbox; i++, pbox++) अणु
		अचिन्हित पूर्णांक x = pbox->x1;
		अचिन्हित पूर्णांक y = pbox->y1;
		अचिन्हित पूर्णांक width = (pbox->x2 - x) * cpp;
		अचिन्हित पूर्णांक height = pbox->y2 - y;
		अचिन्हित पूर्णांक start = y * pitch + x * cpp;

		अगर (pbox->x1 > pbox->x2 ||
		    pbox->y1 > pbox->y2 ||
		    pbox->x2 > dev_priv->w || pbox->y2 > dev_priv->h)
			जारी;

		अगर (flags & I810_FRONT) अणु
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(start);
			OUT_RING(clear_color);
			OUT_RING(0);
			ADVANCE_LP_RING();
		पूर्ण

		अगर (flags & I810_BACK) अणु
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(dev_priv->back_offset + start);
			OUT_RING(clear_color);
			OUT_RING(0);
			ADVANCE_LP_RING();
		पूर्ण

		अगर (flags & I810_DEPTH) अणु
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(dev_priv->depth_offset + start);
			OUT_RING(clear_zval);
			OUT_RING(0);
			ADVANCE_LP_RING();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम i810_dma_dispatch_swap(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	पूर्णांक nbox = sarea_priv->nbox;
	काष्ठा drm_clip_rect *pbox = sarea_priv->boxes;
	पूर्णांक pitch = dev_priv->pitch;
	पूर्णांक cpp = 2;
	पूर्णांक i;
	RING_LOCALS;

	DRM_DEBUG("swapbuffers\n");

	i810_kernel_lost_context(dev);

	अगर (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	क्रम (i = 0; i < nbox; i++, pbox++) अणु
		अचिन्हित पूर्णांक w = pbox->x2 - pbox->x1;
		अचिन्हित पूर्णांक h = pbox->y2 - pbox->y1;
		अचिन्हित पूर्णांक dst = pbox->x1 * cpp + pbox->y1 * pitch;
		अचिन्हित पूर्णांक start = dst;

		अगर (pbox->x1 > pbox->x2 ||
		    pbox->y1 > pbox->y2 ||
		    pbox->x2 > dev_priv->w || pbox->y2 > dev_priv->h)
			जारी;

		BEGIN_LP_RING(6);
		OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_SRC_COPY_BLT | 0x4);
		OUT_RING(pitch | (0xCC << 16));
		OUT_RING((h << 16) | (w * cpp));
		अगर (dev_priv->current_page == 0)
			OUT_RING(dev_priv->front_offset + start);
		अन्यथा
			OUT_RING(dev_priv->back_offset + start);
		OUT_RING(pitch);
		अगर (dev_priv->current_page == 0)
			OUT_RING(dev_priv->back_offset + start);
		अन्यथा
			OUT_RING(dev_priv->front_offset + start);
		ADVANCE_LP_RING();
	पूर्ण
पूर्ण

अटल व्योम i810_dma_dispatch_vertex(काष्ठा drm_device *dev,
				     काष्ठा drm_buf *buf, पूर्णांक discard, पूर्णांक used)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	काष्ठा drm_clip_rect *box = sarea_priv->boxes;
	पूर्णांक nbox = sarea_priv->nbox;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)buf->bus_address;
	अचिन्हित दीर्घ start = address - dev->agp->base;
	पूर्णांक i = 0;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	अगर (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	अगर (used < 0 || used > 4 * 1024)
		used = 0;

	अगर (sarea_priv->dirty)
		i810EmitState(dev);

	अगर (buf_priv->currently_mapped == I810_BUF_MAPPED) अणु
		अचिन्हित पूर्णांक prim = (sarea_priv->vertex_prim & PR_MASK);

		*(u32 *) buf_priv->kernel_भव =
		    ((GFX_OP_PRIMITIVE | prim | ((used / 4) - 2)));

		अगर (used & 4) अणु
			*(u32 *) ((अक्षर *) buf_priv->kernel_भव + used) = 0;
			used += 4;
		पूर्ण

		i810_unmap_buffer(buf);
	पूर्ण

	अगर (used) अणु
		करो अणु
			अगर (i < nbox) अणु
				BEGIN_LP_RING(4);
				OUT_RING(GFX_OP_SCISSOR | SC_UPDATE_SCISSOR |
					 SC_ENABLE);
				OUT_RING(GFX_OP_SCISSOR_INFO);
				OUT_RING(box[i].x1 | (box[i].y1 << 16));
				OUT_RING((box[i].x2 -
					  1) | ((box[i].y2 - 1) << 16));
				ADVANCE_LP_RING();
			पूर्ण

			BEGIN_LP_RING(4);
			OUT_RING(CMD_OP_BATCH_BUFFER);
			OUT_RING(start | BB1_PROTECTED);
			OUT_RING(start + used - 4);
			OUT_RING(0);
			ADVANCE_LP_RING();

		पूर्ण जबतक (++i < nbox);
	पूर्ण

	अगर (discard) अणु
		dev_priv->counter++;

		(व्योम)cmpxchg(buf_priv->in_use, I810_BUF_CLIENT,
			      I810_BUF_HARDWARE);

		BEGIN_LP_RING(8);
		OUT_RING(CMD_STORE_DWORD_IDX);
		OUT_RING(20);
		OUT_RING(dev_priv->counter);
		OUT_RING(CMD_STORE_DWORD_IDX);
		OUT_RING(buf_priv->my_use_idx);
		OUT_RING(I810_BUF_FREE);
		OUT_RING(CMD_REPORT_HEAD);
		OUT_RING(0);
		ADVANCE_LP_RING();
	पूर्ण
पूर्ण

अटल व्योम i810_dma_dispatch_flip(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक pitch = dev_priv->pitch;
	RING_LOCALS;

	DRM_DEBUG("page=%d pfCurrentPage=%d\n",
		  dev_priv->current_page,
		  dev_priv->sarea_priv->pf_current_page);

	i810_kernel_lost_context(dev);

	BEGIN_LP_RING(2);
	OUT_RING(INST_PARSER_CLIENT | INST_OP_FLUSH | INST_FLUSH_MAP_CACHE);
	OUT_RING(0);
	ADVANCE_LP_RING();

	BEGIN_LP_RING(I810_DEST_SETUP_SIZE + 2);
	/* On i815 at least ASYNC is buggy */
	/* pitch<<5 is from 11.2.8 p158,
	   its the pitch / 8 then left shअगरted 8,
	   so (pitch >> 3) << 8 */
	OUT_RING(CMD_OP_FRONTBUFFER_INFO | (pitch << 5) /*| ASYNC_FLIP */ );
	अगर (dev_priv->current_page == 0) अणु
		OUT_RING(dev_priv->back_offset);
		dev_priv->current_page = 1;
	पूर्ण अन्यथा अणु
		OUT_RING(dev_priv->front_offset);
		dev_priv->current_page = 0;
	पूर्ण
	OUT_RING(0);
	ADVANCE_LP_RING();

	BEGIN_LP_RING(2);
	OUT_RING(CMD_OP_WAIT_FOR_EVENT | WAIT_FOR_PLANE_A_FLIP);
	OUT_RING(0);
	ADVANCE_LP_RING();

	/* Increment the frame counter.  The client-side 3D driver must
	 * throttle the framerate by रुकोing क्रम this value beक्रमe
	 * perक्रमming the swapbuffer ioctl.
	 */
	dev_priv->sarea_priv->pf_current_page = dev_priv->current_page;

पूर्ण

अटल व्योम i810_dma_quiescent(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	BEGIN_LP_RING(4);
	OUT_RING(INST_PARSER_CLIENT | INST_OP_FLUSH | INST_FLUSH_MAP_CACHE);
	OUT_RING(CMD_REPORT_HEAD);
	OUT_RING(0);
	OUT_RING(0);
	ADVANCE_LP_RING();

	i810_रुको_ring(dev, dev_priv->ring.Size - 8);
पूर्ण

अटल व्योम i810_flush_queue(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	BEGIN_LP_RING(2);
	OUT_RING(CMD_REPORT_HEAD);
	OUT_RING(0);
	ADVANCE_LP_RING();

	i810_रुको_ring(dev, dev_priv->ring.Size - 8);

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;

		पूर्णांक used = cmpxchg(buf_priv->in_use, I810_BUF_HARDWARE,
				   I810_BUF_FREE);

		अगर (used == I810_BUF_HARDWARE)
			DRM_DEBUG("reclaimed from HARDWARE\n");
		अगर (used == I810_BUF_CLIENT)
			DRM_DEBUG("still on client\n");
	पूर्ण

	वापस;
पूर्ण

/* Must be called with the lock held */
व्योम i810_driver_reclaim_buffers(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;

	अगर (!dma)
		वापस;
	अगर (!dev->dev_निजी)
		वापस;
	अगर (!dma->buflist)
		वापस;

	i810_flush_queue(dev);

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;

		अगर (buf->file_priv == file_priv && buf_priv) अणु
			पूर्णांक used = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT,
					   I810_BUF_FREE);

			अगर (used == I810_BUF_CLIENT)
				DRM_DEBUG("reclaimed from client\n");
			अगर (buf_priv->currently_mapped == I810_BUF_MAPPED)
				buf_priv->currently_mapped = I810_BUF_UNMAPPED;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक i810_flush_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	LOCK_TEST_WITH_RETURN(dev, file_priv);

	i810_flush_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक i810_dma_vertex(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;
	drm_i810_vertex_t *vertex = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("idx %d used %d discard %d\n",
		  vertex->idx, vertex->used, vertex->discard);

	अगर (vertex->idx < 0 || vertex->idx >= dma->buf_count)
		वापस -EINVAL;

	i810_dma_dispatch_vertex(dev,
				 dma->buflist[vertex->idx],
				 vertex->discard, vertex->used);

	sarea_priv->last_enqueue = dev_priv->counter - 1;
	sarea_priv->last_dispatch = (पूर्णांक)hw_status[5];

	वापस 0;
पूर्ण

अटल पूर्णांक i810_clear_bufs(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	drm_i810_clear_t *clear = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	/* GH: Someone's करोing nasty things... */
	अगर (!dev->dev_निजी)
		वापस -EINVAL;

	i810_dma_dispatch_clear(dev, clear->flags,
				clear->clear_color, clear->clear_depth);
	वापस 0;
पूर्ण

अटल पूर्णांक i810_swap_bufs(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	i810_dma_dispatch_swap(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक i810_getage(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;

	sarea_priv->last_dispatch = (पूर्णांक)hw_status[5];
	वापस 0;
पूर्ण

अटल पूर्णांक i810_getbuf(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	पूर्णांक retcode = 0;
	drm_i810_dma_t *d = data;
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	d->granted = 0;

	retcode = i810_dma_get_buffer(dev, d, file_priv);

	DRM_DEBUG("i810_dma: %d returning %d, granted = %d\n",
		  task_pid_nr(current), retcode, d->granted);

	sarea_priv->last_dispatch = (पूर्णांक)hw_status[5];

	वापस retcode;
पूर्ण

अटल पूर्णांक i810_copybuf(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	/* Never copy - 2.4.x करोesn't need it */
	वापस 0;
पूर्ण

अटल पूर्णांक i810_करोcopy(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	/* Never copy - 2.4.x करोesn't need it */
	वापस 0;
पूर्ण

अटल व्योम i810_dma_dispatch_mc(काष्ठा drm_device *dev, काष्ठा drm_buf *buf, पूर्णांक used,
				 अचिन्हित पूर्णांक last_render)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;
	drm_i810_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)buf->bus_address;
	अचिन्हित दीर्घ start = address - dev->agp->base;
	पूर्णांक u;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	u = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT, I810_BUF_HARDWARE);
	अगर (u != I810_BUF_CLIENT)
		DRM_DEBUG("MC found buffer that isn't mine!\n");

	अगर (used < 0 || used > 4 * 1024)
		used = 0;

	sarea_priv->dirty = 0x7f;

	DRM_DEBUG("addr 0x%lx, used 0x%x\n", address, used);

	dev_priv->counter++;
	DRM_DEBUG("dispatch counter : %ld\n", dev_priv->counter);
	DRM_DEBUG("start : %lx\n", start);
	DRM_DEBUG("used : %d\n", used);
	DRM_DEBUG("start + used - 4 : %ld\n", start + used - 4);

	अगर (buf_priv->currently_mapped == I810_BUF_MAPPED) अणु
		अगर (used & 4) अणु
			*(u32 *) ((अक्षर *) buf_priv->भव + used) = 0;
			used += 4;
		पूर्ण

		i810_unmap_buffer(buf);
	पूर्ण
	BEGIN_LP_RING(4);
	OUT_RING(CMD_OP_BATCH_BUFFER);
	OUT_RING(start | BB1_PROTECTED);
	OUT_RING(start + used - 4);
	OUT_RING(0);
	ADVANCE_LP_RING();

	BEGIN_LP_RING(8);
	OUT_RING(CMD_STORE_DWORD_IDX);
	OUT_RING(buf_priv->my_use_idx);
	OUT_RING(I810_BUF_FREE);
	OUT_RING(0);

	OUT_RING(CMD_STORE_DWORD_IDX);
	OUT_RING(16);
	OUT_RING(last_render);
	OUT_RING(0);
	ADVANCE_LP_RING();
पूर्ण

अटल पूर्णांक i810_dma_mc(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;
	drm_i810_mc_t *mc = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (mc->idx >= dma->buf_count || mc->idx < 0)
		वापस -EINVAL;

	i810_dma_dispatch_mc(dev, dma->buflist[mc->idx], mc->used,
			     mc->last_render);

	sarea_priv->last_enqueue = dev_priv->counter - 1;
	sarea_priv->last_dispatch = (पूर्णांक)hw_status[5];

	वापस 0;
पूर्ण

अटल पूर्णांक i810_rstatus(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;

	वापस (पूर्णांक)(((u32 *) (dev_priv->hw_status_page))[4]);
पूर्ण

अटल पूर्णांक i810_ov0_info(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;
	drm_i810_overlay_t *ov = data;

	ov->offset = dev_priv->overlay_offset;
	ov->physical = dev_priv->overlay_physical;

	वापस 0;
पूर्ण

अटल पूर्णांक i810_ख_स्थितिus(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;

	LOCK_TEST_WITH_RETURN(dev, file_priv);
	वापस I810_READ(0x30008);
पूर्ण

अटल पूर्णांक i810_ov0_flip(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = (drm_i810_निजी_t *) dev->dev_निजी;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	/* Tell the overlay to update */
	I810_WRITE(0x30000, dev_priv->overlay_physical | 0x80000000);

	वापस 0;
पूर्ण

/* Not sure why this isn't set all the समय:
 */
अटल व्योम i810_करो_init_pageflip(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;

	DRM_DEBUG("\n");
	dev_priv->page_flipping = 1;
	dev_priv->current_page = 0;
	dev_priv->sarea_priv->pf_current_page = dev_priv->current_page;
पूर्ण

अटल पूर्णांक i810_करो_cleanup_pageflip(काष्ठा drm_device *dev)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;

	DRM_DEBUG("\n");
	अगर (dev_priv->current_page != 0)
		i810_dma_dispatch_flip(dev);

	dev_priv->page_flipping = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक i810_flip_bufs(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	drm_i810_निजी_t *dev_priv = dev->dev_निजी;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	अगर (!dev_priv->page_flipping)
		i810_करो_init_pageflip(dev);

	i810_dma_dispatch_flip(dev);
	वापस 0;
पूर्ण

पूर्णांक i810_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	dev->agp = drm_agp_init(dev);
	अगर (dev->agp) अणु
		dev->agp->agp_mtrr = arch_phys_wc_add(
			dev->agp->agp_info.aper_base,
			dev->agp->agp_info.aper_size *
			1024 * 1024);
	पूर्ण

	/* Our userspace depends upon the agp mapping support. */
	अगर (!dev->agp)
		वापस -EINVAL;

	pci_set_master(dev->pdev);

	वापस 0;
पूर्ण

व्योम i810_driver_lastबंद(काष्ठा drm_device *dev)
अणु
	i810_dma_cleanup(dev);
पूर्ण

व्योम i810_driver_preबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	अगर (dev->dev_निजी) अणु
		drm_i810_निजी_t *dev_priv = dev->dev_निजी;
		अगर (dev_priv->page_flipping)
			i810_करो_cleanup_pageflip(dev);
	पूर्ण

	अगर (file_priv->master && file_priv->master->lock.hw_lock) अणु
		drm_legacy_idlelock_take(&file_priv->master->lock);
		i810_driver_reclaim_buffers(dev, file_priv);
		drm_legacy_idlelock_release(&file_priv->master->lock);
	पूर्ण अन्यथा अणु
		/* master disappeared, clean up stuff anyway and hope nothing
		 * goes wrong */
		i810_driver_reclaim_buffers(dev, file_priv);
	पूर्ण

पूर्ण

पूर्णांक i810_driver_dma_quiescent(काष्ठा drm_device *dev)
अणु
	i810_dma_quiescent(dev);
	वापस 0;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc i810_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(I810_INIT, i810_dma_init, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_VERTEX, i810_dma_vertex, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_CLEAR, i810_clear_bufs, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_FLUSH, i810_flush_ioctl, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_GETAGE, i810_getage, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_GETBUF, i810_getbuf, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_SWAP, i810_swap_bufs, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_COPY, i810_copybuf, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_DOCOPY, i810_करोcopy, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_OV0INFO, i810_ov0_info, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_FSTATUS, i810_ख_स्थितिus, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_OV0FLIP, i810_ov0_flip, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_MC, i810_dma_mc, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_RSTATUS, i810_rstatus, DRM_AUTH|DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(I810_FLIP, i810_flip_bufs, DRM_AUTH|DRM_UNLOCKED),
पूर्ण;

पूर्णांक i810_max_ioctl = ARRAY_SIZE(i810_ioctls);
