<शैली गुरु>
/* mga_dma.c -- DMA support क्रम mga g200/g400 -*- linux-c -*-
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
 */

/*
 * \पile mga_dma.c
 * DMA support क्रम MGA G200 / G400.
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Jeff Harपंचांगann <jharपंचांगann@valinux.com>
 * \चuthor Keith Whitwell <keith@tungstengraphics.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

#समावेश <linux/delay.h>

#समावेश "mga_drv.h"

#घोषणा MGA_DEFAULT_USEC_TIMEOUT	10000
#घोषणा MGA_FREELIST_DEBUG		0

#घोषणा MINIMAL_CLEANUP 0
#घोषणा FULL_CLEANUP 1
अटल पूर्णांक mga_करो_cleanup_dma(काष्ठा drm_device *dev, पूर्णांक full_cleanup);

/* ================================================================
 * Engine control
 */

पूर्णांक mga_करो_रुको_क्रम_idle(drm_mga_निजी_t *dev_priv)
अणु
	u32 status = 0;
	पूर्णांक i;
	DRM_DEBUG("\n");

	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
		अगर (status == MGA_ENDPRDMASTS) अणु
			MGA_WRITE8(MGA_CRTC_INDEX, 0);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

#अगर MGA_DMA_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x\n", status);
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mga_करो_dma_reset(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;

	DRM_DEBUG("\n");

	/* The primary DMA stream should look like new right about now.
	 */
	primary->tail = 0;
	primary->space = primary->size;
	primary->last_flush = 0;

	sarea_priv->last_wrap = 0;

	/* FIXME: Reset counters, buffer ages etc...
	 */

	/* FIXME: What अन्यथा करो we need to reinitialize?  WARP stuff?
	 */

	वापस 0;
पूर्ण

/* ================================================================
 * Primary DMA stream
 */

व्योम mga_करो_dma_flush(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	u32 status = 0;
	पूर्णांक i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	/* We need to रुको so that we can करो an safe flush */
	क्रम (i = 0; i < dev_priv->usec_समयout; i++) अणु
		status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
		अगर (status == MGA_ENDPRDMASTS)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (primary->tail == primary->last_flush) अणु
		DRM_DEBUG("   bailing out...\n");
		वापस;
	पूर्ण

	tail = primary->tail + dev_priv->primary->offset;

	/* We need to pad the stream between flushes, as the card
	 * actually (partially?) पढ़ोs the first of these commands.
	 * See page 4-16 in the G400 manual, middle of the page or so.
	 */
	BEGIN_DMA(1);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();

	primary->last_flush = primary->tail;

	head = MGA_READ(MGA_PRIMADDRESS);

	अगर (head <= tail)
		primary->space = primary->size - primary->tail;
	अन्यथा
		primary->space = head - tail;

	DRM_DEBUG("   head = 0x%06lx\n", (अचिन्हित दीर्घ)(head - dev_priv->primary->offset));
	DRM_DEBUG("   tail = 0x%06lx\n", (अचिन्हित दीर्घ)(tail - dev_priv->primary->offset));
	DRM_DEBUG("  space = 0x%06x\n", primary->space);

	mga_flush_ग_लिखो_combine();
	MGA_WRITE(MGA_PRIMEND, tail | dev_priv->dma_access);

	DRM_DEBUG("done.\n");
पूर्ण

व्योम mga_करो_dma_wrap_start(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	u32 head, tail;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_DMA_WRAP();

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	ADVANCE_DMA();

	tail = primary->tail + dev_priv->primary->offset;

	primary->tail = 0;
	primary->last_flush = 0;
	primary->last_wrap++;

	head = MGA_READ(MGA_PRIMADDRESS);

	अगर (head == dev_priv->primary->offset)
		primary->space = primary->size;
	अन्यथा
		primary->space = head - dev_priv->primary->offset;

	DRM_DEBUG("   head = 0x%06lx\n", (अचिन्हित दीर्घ)(head - dev_priv->primary->offset));
	DRM_DEBUG("   tail = 0x%06x\n", primary->tail);
	DRM_DEBUG("   wrap = %d\n", primary->last_wrap);
	DRM_DEBUG("  space = 0x%06x\n", primary->space);

	mga_flush_ग_लिखो_combine();
	MGA_WRITE(MGA_PRIMEND, tail | dev_priv->dma_access);

	set_bit(0, &primary->wrapped);
	DRM_DEBUG("done.\n");
पूर्ण

व्योम mga_करो_dma_wrap_end(drm_mga_निजी_t *dev_priv)
अणु
	drm_mga_primary_buffer_t *primary = &dev_priv->prim;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	u32 head = dev_priv->primary->offset;
	DRM_DEBUG("\n");

	sarea_priv->last_wrap++;
	DRM_DEBUG("   wrap = %d\n", sarea_priv->last_wrap);

	mga_flush_ग_लिखो_combine();
	MGA_WRITE(MGA_PRIMADDRESS, head | MGA_DMA_GENERAL);

	clear_bit(0, &primary->wrapped);
	DRM_DEBUG("done.\n");
पूर्ण

/* ================================================================
 * Freelist management
 */

#घोषणा MGA_BUFFER_USED		(~0)
#घोषणा MGA_BUFFER_FREE		0

#अगर MGA_FREELIST_DEBUG
अटल व्योम mga_मुक्तlist_prपूर्णांक(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_मुक्तlist_t *entry;

	DRM_INFO("\n");
	DRM_INFO("current dispatch: last=0x%x done=0x%x\n",
		 dev_priv->sarea_priv->last_dispatch,
		 (अचिन्हित पूर्णांक)(MGA_READ(MGA_PRIMADDRESS) -
				dev_priv->primary->offset));
	DRM_INFO("current freelist:\n");

	क्रम (entry = dev_priv->head->next; entry; entry = entry->next) अणु
		DRM_INFO("   %p   idx=%2d  age=0x%x 0x%06lx\n",
			 entry, entry->buf->idx, entry->age.head,
			 (अचिन्हित दीर्घ)(entry->age.head - dev_priv->primary->offset));
	पूर्ण
	DRM_INFO("\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mga_मुक्तlist_init(काष्ठा drm_device *dev, drm_mga_निजी_t *dev_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_मुक्तlist_t *entry;
	पूर्णांक i;
	DRM_DEBUG("count=%d\n", dma->buf_count);

	dev_priv->head = kzalloc(माप(drm_mga_मुक्तlist_t), GFP_KERNEL);
	अगर (dev_priv->head == शून्य)
		वापस -ENOMEM;

	SET_AGE(&dev_priv->head->age, MGA_BUFFER_USED, 0);

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		buf = dma->buflist[i];
		buf_priv = buf->dev_निजी;

		entry = kzalloc(माप(drm_mga_मुक्तlist_t), GFP_KERNEL);
		अगर (entry == शून्य)
			वापस -ENOMEM;

		entry->next = dev_priv->head->next;
		entry->prev = dev_priv->head;
		SET_AGE(&entry->age, MGA_BUFFER_FREE, 0);
		entry->buf = buf;

		अगर (dev_priv->head->next != शून्य)
			dev_priv->head->next->prev = entry;
		अगर (entry->next == शून्य)
			dev_priv->tail = entry;

		buf_priv->list_entry = entry;
		buf_priv->discard = 0;
		buf_priv->dispatched = 0;

		dev_priv->head->next = entry;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mga_मुक्तlist_cleanup(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_मुक्तlist_t *entry;
	drm_mga_मुक्तlist_t *next;
	DRM_DEBUG("\n");

	entry = dev_priv->head;
	जबतक (entry) अणु
		next = entry->next;
		kमुक्त(entry);
		entry = next;
	पूर्ण

	dev_priv->head = dev_priv->tail = शून्य;
पूर्ण

#अगर 0
/* FIXME: Still needed?
 */
अटल व्योम mga_मुक्तlist_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	पूर्णांक i;

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		buf = dma->buflist[i];
		buf_priv = buf->dev_निजी;
		SET_AGE(&buf_priv->list_entry->age, MGA_BUFFER_FREE, 0);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा drm_buf *mga_मुक्तlist_get(काष्ठा drm_device * dev)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_मुक्तlist_t *next;
	drm_mga_मुक्तlist_t *prev;
	drm_mga_मुक्तlist_t *tail = dev_priv->tail;
	u32 head, wrap;
	DRM_DEBUG("\n");

	head = MGA_READ(MGA_PRIMADDRESS);
	wrap = dev_priv->sarea_priv->last_wrap;

	DRM_DEBUG("   tail=0x%06lx %d\n",
		  tail->age.head ?
		  (अचिन्हित दीर्घ)(tail->age.head - dev_priv->primary->offset) : 0,
		  tail->age.wrap);
	DRM_DEBUG("   head=0x%06lx %d\n",
		  (अचिन्हित दीर्घ)(head - dev_priv->primary->offset), wrap);

	अगर (TEST_AGE(&tail->age, head, wrap)) अणु
		prev = dev_priv->tail->prev;
		next = dev_priv->tail;
		prev->next = शून्य;
		next->prev = next->next = शून्य;
		dev_priv->tail = prev;
		SET_AGE(&next->age, MGA_BUFFER_USED, 0);
		वापस next->buf;
	पूर्ण

	DRM_DEBUG("returning NULL!\n");
	वापस शून्य;
पूर्ण

पूर्णांक mga_मुक्तlist_put(काष्ठा drm_device *dev, काष्ठा drm_buf *buf)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	drm_mga_buf_priv_t *buf_priv = buf->dev_निजी;
	drm_mga_मुक्तlist_t *head, *entry, *prev;

	DRM_DEBUG("age=0x%06lx wrap=%d\n",
		  (अचिन्हित दीर्घ)(buf_priv->list_entry->age.head -
				  dev_priv->primary->offset),
		  buf_priv->list_entry->age.wrap);

	entry = buf_priv->list_entry;
	head = dev_priv->head;

	अगर (buf_priv->list_entry->age.head == MGA_BUFFER_USED) अणु
		SET_AGE(&entry->age, MGA_BUFFER_FREE, 0);
		prev = dev_priv->tail;
		prev->next = entry;
		entry->prev = prev;
		entry->next = शून्य;
	पूर्ण अन्यथा अणु
		prev = head->next;
		head->next = entry;
		prev->prev = entry;
		entry->prev = head;
		entry->next = prev;
	पूर्ण

	वापस 0;
पूर्ण

/* ================================================================
 * DMA initialization, cleanup
 */

पूर्णांक mga_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	drm_mga_निजी_t *dev_priv;
	पूर्णांक ret;

	/* There are PCI versions of the G450.  These cards have the
	 * same PCI ID as the AGP G450, but have an additional PCI-to-PCI
	 * bridge chip.  We detect these cards, which are not currently
	 * supported by this driver, by looking at the device ID of the
	 * bus the "card" is on.  If venकरोr is 0x3388 (Hपूर्णांक Corp) and the
	 * device is 0x0021 (HB6 Universal PCI-PCI bridge), we reject the
	 * device.
	 */
	अगर ((dev->pdev->device == 0x0525) && dev->pdev->bus->self
	    && (dev->pdev->bus->self->venकरोr == 0x3388)
	    && (dev->pdev->bus->self->device == 0x0021)
	    && dev->agp) अणु
		/* FIXME: This should be quirked in the pci core, but oh well
		 * the hw probably stopped existing. */
		arch_phys_wc_del(dev->agp->agp_mtrr);
		kमुक्त(dev->agp);
		dev->agp = शून्य;
	पूर्ण
	dev_priv = kzalloc(माप(drm_mga_निजी_t), GFP_KERNEL);
	अगर (!dev_priv)
		वापस -ENOMEM;

	dev->dev_निजी = (व्योम *)dev_priv;

	dev_priv->usec_समयout = MGA_DEFAULT_USEC_TIMEOUT;
	dev_priv->chipset = flags;

	pci_set_master(dev->pdev);

	dev_priv->mmio_base = pci_resource_start(dev->pdev, 1);
	dev_priv->mmio_size = pci_resource_len(dev->pdev, 1);

	ret = drm_vblank_init(dev, 1);

	अगर (ret) अणु
		(व्योम) mga_driver_unload(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP)
/*
 * Bootstrap the driver क्रम AGP DMA.
 *
 * \टoकरो
 * Investigate whether there is any benefit to storing the WARP microcode in
 * AGP memory.  If not, the microcode may as well always be put in PCI
 * memory.
 *
 * \टoकरो
 * This routine needs to set dma_bs->agp_mode to the mode actually configured
 * in the hardware.  Looking just at the Linux AGP driver code, I करोn't see
 * an easy way to determine this.
 *
 * \sa mga_करो_dma_bootstrap, mga_करो_pci_dma_bootstrap
 */
अटल पूर्णांक mga_करो_agp_dma_bootstrap(काष्ठा drm_device *dev,
				    drm_mga_dma_bootstrap_t *dma_bs)
अणु
	drm_mga_निजी_t *स्थिर dev_priv =
	    (drm_mga_निजी_t *) dev->dev_निजी;
	अचिन्हित पूर्णांक warp_size = MGA_WARP_UCODE_SIZE;
	पूर्णांक err;
	अचिन्हित offset;
	स्थिर अचिन्हित secondary_size = dma_bs->secondary_bin_count
	    * dma_bs->secondary_bin_size;
	स्थिर अचिन्हित agp_size = (dma_bs->agp_size << 20);
	काष्ठा drm_buf_desc req;
	काष्ठा drm_agp_mode mode;
	काष्ठा drm_agp_info info;
	काष्ठा drm_agp_buffer agp_req;
	काष्ठा drm_agp_binding bind_req;

	/* Acquire AGP. */
	err = drm_agp_acquire(dev);
	अगर (err) अणु
		DRM_ERROR("Unable to acquire AGP: %d\n", err);
		वापस err;
	पूर्ण

	err = drm_agp_info(dev, &info);
	अगर (err) अणु
		DRM_ERROR("Unable to get AGP info: %d\n", err);
		वापस err;
	पूर्ण

	mode.mode = (info.mode & ~0x07) | dma_bs->agp_mode;
	err = drm_agp_enable(dev, mode);
	अगर (err) अणु
		DRM_ERROR("Unable to enable AGP (mode = 0x%lx)\n", mode.mode);
		वापस err;
	पूर्ण

	/* In addition to the usual AGP mode configuration, the G200 AGP cards
	 * need to have the AGP mode "manually" set.
	 */

	अगर (dev_priv->chipset == MGA_CARD_TYPE_G200) अणु
		अगर (mode.mode & 0x02)
			MGA_WRITE(MGA_AGP_PLL, MGA_AGP2XPLL_ENABLE);
		अन्यथा
			MGA_WRITE(MGA_AGP_PLL, MGA_AGP2XPLL_DISABLE);
	पूर्ण

	/* Allocate and bind AGP memory. */
	agp_req.size = agp_size;
	agp_req.type = 0;
	err = drm_agp_alloc(dev, &agp_req);
	अगर (err) अणु
		dev_priv->agp_size = 0;
		DRM_ERROR("Unable to allocate %uMB AGP memory\n",
			  dma_bs->agp_size);
		वापस err;
	पूर्ण

	dev_priv->agp_size = agp_size;
	dev_priv->agp_handle = agp_req.handle;

	bind_req.handle = agp_req.handle;
	bind_req.offset = 0;
	err = drm_agp_bind(dev, &bind_req);
	अगर (err) अणु
		DRM_ERROR("Unable to bind AGP memory: %d\n", err);
		वापस err;
	पूर्ण

	/* Make drm_legacy_addbufs happy by not trying to create a mapping क्रम
	 * less than a page.
	 */
	अगर (warp_size < PAGE_SIZE)
		warp_size = PAGE_SIZE;

	offset = 0;
	err = drm_legacy_addmap(dev, offset, warp_size,
				_DRM_AGP, _DRM_READ_ONLY, &dev_priv->warp);
	अगर (err) अणु
		DRM_ERROR("Unable to map WARP microcode: %d\n", err);
		वापस err;
	पूर्ण

	offset += warp_size;
	err = drm_legacy_addmap(dev, offset, dma_bs->primary_size,
				_DRM_AGP, _DRM_READ_ONLY, &dev_priv->primary);
	अगर (err) अणु
		DRM_ERROR("Unable to map primary DMA region: %d\n", err);
		वापस err;
	पूर्ण

	offset += dma_bs->primary_size;
	err = drm_legacy_addmap(dev, offset, secondary_size,
				_DRM_AGP, 0, &dev->agp_buffer_map);
	अगर (err) अणु
		DRM_ERROR("Unable to map secondary DMA region: %d\n", err);
		वापस err;
	पूर्ण

	(व्योम)स_रखो(&req, 0, माप(req));
	req.count = dma_bs->secondary_bin_count;
	req.size = dma_bs->secondary_bin_size;
	req.flags = _DRM_AGP_BUFFER;
	req.agp_start = offset;

	err = drm_legacy_addbufs_agp(dev, &req);
	अगर (err) अणु
		DRM_ERROR("Unable to add secondary DMA buffers: %d\n", err);
		वापस err;
	पूर्ण

	अणु
		काष्ठा drm_map_list *_entry;
		अचिन्हित दीर्घ agp_token = 0;

		list_क्रम_each_entry(_entry, &dev->maplist, head) अणु
			अगर (_entry->map == dev->agp_buffer_map)
				agp_token = _entry->user_token;
		पूर्ण
		अगर (!agp_token)
			वापस -EFAULT;

		dev->agp_buffer_token = agp_token;
	पूर्ण

	offset += secondary_size;
	err = drm_legacy_addmap(dev, offset, agp_size - offset,
				_DRM_AGP, 0, &dev_priv->agp_textures);
	अगर (err) अणु
		DRM_ERROR("Unable to map AGP texture region %d\n", err);
		वापस err;
	पूर्ण

	drm_legacy_ioremap(dev_priv->warp, dev);
	drm_legacy_ioremap(dev_priv->primary, dev);
	drm_legacy_ioremap(dev->agp_buffer_map, dev);

	अगर (!dev_priv->warp->handle ||
	    !dev_priv->primary->handle || !dev->agp_buffer_map->handle) अणु
		DRM_ERROR("failed to ioremap agp regions! (%p, %p, %p)\n",
			  dev_priv->warp->handle, dev_priv->primary->handle,
			  dev->agp_buffer_map->handle);
		वापस -ENOMEM;
	पूर्ण

	dev_priv->dma_access = MGA_PAGPXFER;
	dev_priv->wagp_enable = MGA_WAGP_ENABLE;

	DRM_INFO("Initialized card for AGP DMA.\n");
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक mga_करो_agp_dma_bootstrap(काष्ठा drm_device *dev,
				    drm_mga_dma_bootstrap_t *dma_bs)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * Bootstrap the driver क्रम PCI DMA.
 *
 * \टoकरो
 * The algorithm क्रम decreasing the size of the primary DMA buffer could be
 * better.  The size should be rounded up to the nearest page size, then
 * decrease the request size by a single page each pass through the loop.
 *
 * \टoकरो
 * Determine whether the maximum address passed to drm_pci_alloc is correct.
 * The same goes क्रम drm_legacy_addbufs_pci.
 *
 * \sa mga_करो_dma_bootstrap, mga_करो_agp_dma_bootstrap
 */
अटल पूर्णांक mga_करो_pci_dma_bootstrap(काष्ठा drm_device *dev,
				    drm_mga_dma_bootstrap_t *dma_bs)
अणु
	drm_mga_निजी_t *स्थिर dev_priv =
	    (drm_mga_निजी_t *) dev->dev_निजी;
	अचिन्हित पूर्णांक warp_size = MGA_WARP_UCODE_SIZE;
	अचिन्हित पूर्णांक primary_size;
	अचिन्हित पूर्णांक bin_count;
	पूर्णांक err;
	काष्ठा drm_buf_desc req;

	अगर (dev->dma == शून्य) अणु
		DRM_ERROR("dev->dma is NULL\n");
		वापस -EFAULT;
	पूर्ण

	/* Make drm_legacy_addbufs happy by not trying to create a mapping क्रम
	 * less than a page.
	 */
	अगर (warp_size < PAGE_SIZE)
		warp_size = PAGE_SIZE;

	/* The proper alignment is 0x100 क्रम this mapping */
	err = drm_legacy_addmap(dev, 0, warp_size, _DRM_CONSISTENT,
				_DRM_READ_ONLY, &dev_priv->warp);
	अगर (err != 0) अणु
		DRM_ERROR("Unable to create mapping for WARP microcode: %d\n",
			  err);
		वापस err;
	पूर्ण

	/* Other than the bottom two bits being used to encode other
	 * inक्रमmation, there करोn't appear to be any restrictions on the
	 * alignment of the primary or secondary DMA buffers.
	 */

	क्रम (primary_size = dma_bs->primary_size; primary_size != 0;
	     primary_size >>= 1) अणु
		/* The proper alignment क्रम this mapping is 0x04 */
		err = drm_legacy_addmap(dev, 0, primary_size, _DRM_CONSISTENT,
					_DRM_READ_ONLY, &dev_priv->primary);
		अगर (!err)
			अवरोध;
	पूर्ण

	अगर (err != 0) अणु
		DRM_ERROR("Unable to allocate primary DMA region: %d\n", err);
		वापस -ENOMEM;
	पूर्ण

	अगर (dev_priv->primary->size != dma_bs->primary_size) अणु
		DRM_INFO("Primary DMA buffer size reduced from %u to %u.\n",
			 dma_bs->primary_size,
			 (अचिन्हित)dev_priv->primary->size);
		dma_bs->primary_size = dev_priv->primary->size;
	पूर्ण

	क्रम (bin_count = dma_bs->secondary_bin_count; bin_count > 0;
	     bin_count--) अणु
		(व्योम)स_रखो(&req, 0, माप(req));
		req.count = bin_count;
		req.size = dma_bs->secondary_bin_size;

		err = drm_legacy_addbufs_pci(dev, &req);
		अगर (!err)
			अवरोध;
	पूर्ण

	अगर (bin_count == 0) अणु
		DRM_ERROR("Unable to add secondary DMA buffers: %d\n", err);
		वापस err;
	पूर्ण

	अगर (bin_count != dma_bs->secondary_bin_count) अणु
		DRM_INFO("Secondary PCI DMA buffer bin count reduced from %u "
			 "to %u.\n", dma_bs->secondary_bin_count, bin_count);

		dma_bs->secondary_bin_count = bin_count;
	पूर्ण

	dev_priv->dma_access = 0;
	dev_priv->wagp_enable = 0;

	dma_bs->agp_mode = 0;

	DRM_INFO("Initialized card for PCI DMA.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक mga_करो_dma_bootstrap(काष्ठा drm_device *dev,
				drm_mga_dma_bootstrap_t *dma_bs)
अणु
	स्थिर पूर्णांक is_agp = (dma_bs->agp_mode != 0) && dev->agp;
	पूर्णांक err;
	drm_mga_निजी_t *स्थिर dev_priv =
	    (drm_mga_निजी_t *) dev->dev_निजी;

	dev_priv->used_new_dma_init = 1;

	/* The first steps are the same क्रम both PCI and AGP based DMA.  Map
	 * the cards MMIO रेजिस्टरs and map a status page.
	 */
	err = drm_legacy_addmap(dev, dev_priv->mmio_base, dev_priv->mmio_size,
				_DRM_REGISTERS, _DRM_READ_ONLY,
				&dev_priv->mmio);
	अगर (err) अणु
		DRM_ERROR("Unable to map MMIO region: %d\n", err);
		वापस err;
	पूर्ण

	err = drm_legacy_addmap(dev, 0, SAREA_MAX, _DRM_SHM,
				_DRM_READ_ONLY | _DRM_LOCKED | _DRM_KERNEL,
			 &dev_priv->status);
	अगर (err) अणु
		DRM_ERROR("Unable to map status region: %d\n", err);
		वापस err;
	पूर्ण

	/* The DMA initialization procedure is slightly dअगरferent क्रम PCI and
	 * AGP cards.  AGP cards just allocate a large block of AGP memory and
	 * carve off portions of it क्रम पूर्णांकernal uses.  The reमुख्यing memory
	 * is वापसed to user-mode to be used क्रम AGP textures.
	 */
	अगर (is_agp)
		err = mga_करो_agp_dma_bootstrap(dev, dma_bs);

	/* If we attempted to initialize the card क्रम AGP DMA but failed,
	 * clean-up any mess that may have been created.
	 */

	अगर (err)
		mga_करो_cleanup_dma(dev, MINIMAL_CLEANUP);

	/* Not only करो we want to try and initialized PCI cards क्रम PCI DMA,
	 * but we also try to initialized AGP cards that could not be
	 * initialized क्रम AGP DMA.  This covers the हाल where we have an AGP
	 * card in a प्रणाली with an unsupported AGP chipset.  In that हाल the
	 * card will be detected as AGP, but we won't be able to allocate any
	 * AGP memory, etc.
	 */

	अगर (!is_agp || err)
		err = mga_करो_pci_dma_bootstrap(dev, dma_bs);

	वापस err;
पूर्ण

पूर्णांक mga_dma_bootstrap(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	drm_mga_dma_bootstrap_t *bootstrap = data;
	पूर्णांक err;
	अटल स्थिर पूर्णांक modes[] = अणु 0, 1, 2, 2, 4, 4, 4, 4 पूर्ण;
	स्थिर drm_mga_निजी_t *स्थिर dev_priv =
		(drm_mga_निजी_t *) dev->dev_निजी;

	err = mga_करो_dma_bootstrap(dev, bootstrap);
	अगर (err) अणु
		mga_करो_cleanup_dma(dev, FULL_CLEANUP);
		वापस err;
	पूर्ण

	अगर (dev_priv->agp_textures != शून्य) अणु
		bootstrap->texture_handle = dev_priv->agp_textures->offset;
		bootstrap->texture_size = dev_priv->agp_textures->size;
	पूर्ण अन्यथा अणु
		bootstrap->texture_handle = 0;
		bootstrap->texture_size = 0;
	पूर्ण

	bootstrap->agp_mode = modes[bootstrap->agp_mode & 0x07];

	वापस err;
पूर्ण

अटल पूर्णांक mga_करो_init_dma(काष्ठा drm_device *dev, drm_mga_init_t *init)
अणु
	drm_mga_निजी_t *dev_priv;
	पूर्णांक ret;
	DRM_DEBUG("\n");

	dev_priv = dev->dev_निजी;

	अगर (init->sgram)
		dev_priv->clear_cmd = MGA_DWGCTL_CLEAR | MGA_ATYPE_BLK;
	अन्यथा
		dev_priv->clear_cmd = MGA_DWGCTL_CLEAR | MGA_ATYPE_RSTR;
	dev_priv->maccess = init->maccess;

	dev_priv->fb_cpp = init->fb_cpp;
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;

	dev_priv->depth_cpp = init->depth_cpp;
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->depth_pitch = init->depth_pitch;

	/* FIXME: Need to support AGP textures...
	 */
	dev_priv->texture_offset = init->texture_offset[0];
	dev_priv->texture_size = init->texture_size[0];

	dev_priv->sarea = drm_legacy_माला_लोarea(dev);
	अगर (!dev_priv->sarea) अणु
		DRM_ERROR("failed to find sarea!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!dev_priv->used_new_dma_init) अणु

		dev_priv->dma_access = MGA_PAGPXFER;
		dev_priv->wagp_enable = MGA_WAGP_ENABLE;

		dev_priv->status = drm_legacy_findmap(dev, init->status_offset);
		अगर (!dev_priv->status) अणु
			DRM_ERROR("failed to find status page!\n");
			वापस -EINVAL;
		पूर्ण
		dev_priv->mmio = drm_legacy_findmap(dev, init->mmio_offset);
		अगर (!dev_priv->mmio) अणु
			DRM_ERROR("failed to find mmio region!\n");
			वापस -EINVAL;
		पूर्ण
		dev_priv->warp = drm_legacy_findmap(dev, init->warp_offset);
		अगर (!dev_priv->warp) अणु
			DRM_ERROR("failed to find warp microcode region!\n");
			वापस -EINVAL;
		पूर्ण
		dev_priv->primary = drm_legacy_findmap(dev, init->primary_offset);
		अगर (!dev_priv->primary) अणु
			DRM_ERROR("failed to find primary dma region!\n");
			वापस -EINVAL;
		पूर्ण
		dev->agp_buffer_token = init->buffers_offset;
		dev->agp_buffer_map =
		    drm_legacy_findmap(dev, init->buffers_offset);
		अगर (!dev->agp_buffer_map) अणु
			DRM_ERROR("failed to find dma buffer region!\n");
			वापस -EINVAL;
		पूर्ण

		drm_legacy_ioremap(dev_priv->warp, dev);
		drm_legacy_ioremap(dev_priv->primary, dev);
		drm_legacy_ioremap(dev->agp_buffer_map, dev);
	पूर्ण

	dev_priv->sarea_priv =
	    (drm_mga_sarea_t *) ((u8 *) dev_priv->sarea->handle +
				 init->sarea_priv_offset);

	अगर (!dev_priv->warp->handle ||
	    !dev_priv->primary->handle ||
	    ((dev_priv->dma_access != 0) &&
	     ((dev->agp_buffer_map == शून्य) ||
	      (dev->agp_buffer_map->handle == शून्य)))) अणु
		DRM_ERROR("failed to ioremap agp regions!\n");
		वापस -ENOMEM;
	पूर्ण

	ret = mga_warp_install_microcode(dev_priv);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to install WARP ucode!: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mga_warp_init(dev_priv);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to init WARP engine!: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_priv->prim.status = (u32 *) dev_priv->status->handle;

	mga_करो_रुको_क्रम_idle(dev_priv);

	/* Init the primary DMA रेजिस्टरs.
	 */
	MGA_WRITE(MGA_PRIMADDRESS, dev_priv->primary->offset | MGA_DMA_GENERAL);
#अगर 0
	MGA_WRITE(MGA_PRIMPTR, virt_to_bus((व्योम *)dev_priv->prim.status) | MGA_PRIMPTREN0 |	/* Soft trap, SECEND, SETUPEND */
		  MGA_PRIMPTREN1);	/* DWGSYNC */
#पूर्ण_अगर

	dev_priv->prim.start = (u8 *) dev_priv->primary->handle;
	dev_priv->prim.end = ((u8 *) dev_priv->primary->handle
			      + dev_priv->primary->size);
	dev_priv->prim.size = dev_priv->primary->size;

	dev_priv->prim.tail = 0;
	dev_priv->prim.space = dev_priv->prim.size;
	dev_priv->prim.wrapped = 0;

	dev_priv->prim.last_flush = 0;
	dev_priv->prim.last_wrap = 0;

	dev_priv->prim.high_mark = 256 * DMA_BLOCK_SIZE;

	dev_priv->prim.status[0] = dev_priv->primary->offset;
	dev_priv->prim.status[1] = 0;

	dev_priv->sarea_priv->last_wrap = 0;
	dev_priv->sarea_priv->last_frame.head = 0;
	dev_priv->sarea_priv->last_frame.wrap = 0;

	अगर (mga_मुक्तlist_init(dev, dev_priv) < 0) अणु
		DRM_ERROR("could not initialize freelist\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mga_करो_cleanup_dma(काष्ठा drm_device *dev, पूर्णांक full_cleanup)
अणु
	पूर्णांक err = 0;
	DRM_DEBUG("\n");

	/* Make sure पूर्णांकerrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_निजी
	 * is मुक्तd, it's too late.
	 */
	अगर (dev->irq_enabled)
		drm_irq_uninstall(dev);

	अगर (dev->dev_निजी) अणु
		drm_mga_निजी_t *dev_priv = dev->dev_निजी;

		अगर ((dev_priv->warp != शून्य)
		    && (dev_priv->warp->type != _DRM_CONSISTENT))
			drm_legacy_ioremapमुक्त(dev_priv->warp, dev);

		अगर ((dev_priv->primary != शून्य)
		    && (dev_priv->primary->type != _DRM_CONSISTENT))
			drm_legacy_ioremapमुक्त(dev_priv->primary, dev);

		अगर (dev->agp_buffer_map != शून्य)
			drm_legacy_ioremapमुक्त(dev->agp_buffer_map, dev);

		अगर (dev_priv->used_new_dma_init) अणु
#अगर IS_ENABLED(CONFIG_AGP)
			अगर (dev_priv->agp_handle != 0) अणु
				काष्ठा drm_agp_binding unbind_req;
				काष्ठा drm_agp_buffer मुक्त_req;

				unbind_req.handle = dev_priv->agp_handle;
				drm_agp_unbind(dev, &unbind_req);

				मुक्त_req.handle = dev_priv->agp_handle;
				drm_agp_मुक्त(dev, &मुक्त_req);

				dev_priv->agp_textures = शून्य;
				dev_priv->agp_size = 0;
				dev_priv->agp_handle = 0;
			पूर्ण

			अगर ((dev->agp != शून्य) && dev->agp->acquired)
				err = drm_agp_release(dev);
#पूर्ण_अगर
		पूर्ण

		dev_priv->warp = शून्य;
		dev_priv->primary = शून्य;
		dev_priv->sarea = शून्य;
		dev_priv->sarea_priv = शून्य;
		dev->agp_buffer_map = शून्य;

		अगर (full_cleanup) अणु
			dev_priv->mmio = शून्य;
			dev_priv->status = शून्य;
			dev_priv->used_new_dma_init = 0;
		पूर्ण

		स_रखो(&dev_priv->prim, 0, माप(dev_priv->prim));
		dev_priv->warp_pipe = 0;
		स_रखो(dev_priv->warp_pipe_phys, 0,
		       माप(dev_priv->warp_pipe_phys));

		अगर (dev_priv->head != शून्य)
			mga_मुक्तlist_cleanup(dev);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mga_dma_init(काष्ठा drm_device *dev, व्योम *data,
		 काष्ठा drm_file *file_priv)
अणु
	drm_mga_init_t *init = data;
	पूर्णांक err;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	चयन (init->func) अणु
	हाल MGA_INIT_DMA:
		err = mga_करो_init_dma(dev, init);
		अगर (err)
			(व्योम)mga_करो_cleanup_dma(dev, FULL_CLEANUP);
		वापस err;
	हाल MGA_CLEANUP_DMA:
		वापस mga_करो_cleanup_dma(dev, FULL_CLEANUP);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* ================================================================
 * Primary DMA stream management
 */

पूर्णांक mga_dma_flush(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;
	काष्ठा drm_lock *lock = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("%s%s%s\n",
		  (lock->flags & _DRM_LOCK_FLUSH) ? "flush, " : "",
		  (lock->flags & _DRM_LOCK_FLUSH_ALL) ? "flush all, " : "",
		  (lock->flags & _DRM_LOCK_QUIESCENT) ? "idle, " : "");

	WRAP_WAIT_WITH_RETURN(dev_priv);

	अगर (lock->flags & (_DRM_LOCK_FLUSH | _DRM_LOCK_FLUSH_ALL))
		mga_करो_dma_flush(dev_priv);

	अगर (lock->flags & _DRM_LOCK_QUIESCENT) अणु
#अगर MGA_DMA_DEBUG
		पूर्णांक ret = mga_करो_रुको_क्रम_idle(dev_priv);
		अगर (ret < 0)
			DRM_INFO("-EBUSY\n");
		वापस ret;
#अन्यथा
		वापस mga_करो_रुको_क्रम_idle(dev_priv);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक mga_dma_reset(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	वापस mga_करो_dma_reset(dev_priv);
पूर्ण

/* ================================================================
 * DMA buffer management
 */

अटल पूर्णांक mga_dma_get_buffers(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv, काष्ठा drm_dma *d)
अणु
	काष्ठा drm_buf *buf;
	पूर्णांक i;

	क्रम (i = d->granted_count; i < d->request_count; i++) अणु
		buf = mga_मुक्तlist_get(dev);
		अगर (!buf)
			वापस -EAGAIN;

		buf->file_priv = file_priv;

		अगर (copy_to_user(&d->request_indices[i],
				     &buf->idx, माप(buf->idx)))
			वापस -EFAULT;
		अगर (copy_to_user(&d->request_sizes[i],
				     &buf->total, माप(buf->total)))
			वापस -EFAULT;

		d->granted_count++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mga_dma_buffers(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;
	काष्ठा drm_dma *d = data;
	पूर्णांक ret = 0;

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
			  task_pid_nr(current), d->request_count,
			  dma->buf_count);
		वापस -EINVAL;
	पूर्ण

	WRAP_TEST_WITH_RETURN(dev_priv);

	d->granted_count = 0;

	अगर (d->request_count)
		ret = mga_dma_get_buffers(dev, file_priv, d);

	वापस ret;
पूर्ण

/*
 * Called just beक्रमe the module is unloaded.
 */
व्योम mga_driver_unload(काष्ठा drm_device *dev)
अणु
	kमुक्त(dev->dev_निजी);
	dev->dev_निजी = शून्य;
पूर्ण

/*
 * Called when the last खोलोer of the device is बंदd.
 */
व्योम mga_driver_lastबंद(काष्ठा drm_device *dev)
अणु
	mga_करो_cleanup_dma(dev, FULL_CLEANUP);
पूर्ण

पूर्णांक mga_driver_dma_quiescent(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = dev->dev_निजी;
	वापस mga_करो_रुको_क्रम_idle(dev_priv);
पूर्ण
