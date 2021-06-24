<शैली गुरु>
/* savage_bci.c -- BCI support क्रम Savage
 *
 * Copyright 2004  Felix Kuehling
 * All Rights Reserved.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT. IN NO EVENT SHALL FELIX KUEHLING BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/savage_drm.h>

#समावेश "savage_drv.h"

/* Need a दीर्घ समयout क्रम shaकरोw status updates can take a जबतक
 * and so can रुकोing क्रम events when the queue is full. */
#घोषणा SAVAGE_DEFAULT_USEC_TIMEOUT	1000000	/* 1s */
#घोषणा SAVAGE_EVENT_USEC_TIMEOUT	5000000	/* 5s */
#घोषणा SAVAGE_FREELIST_DEBUG		0

अटल पूर्णांक savage_करो_cleanup_bci(काष्ठा drm_device *dev);

अटल पूर्णांक
savage_bci_रुको_fअगरo_shaकरोw(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक n)
अणु
	uपूर्णांक32_t mask = dev_priv->status_used_mask;
	uपूर्णांक32_t threshold = dev_priv->bci_threshold_hi;
	uपूर्णांक32_t status;
	पूर्णांक i;

#अगर SAVAGE_BCI_DEBUG
	अगर (n > dev_priv->cob_size + SAVAGE_BCI_FIFO_SIZE - threshold)
		DRM_ERROR("Trying to emit %d words "
			  "(more than guaranteed space in COB)\n", n);
#पूर्ण_अगर

	क्रम (i = 0; i < SAVAGE_DEFAULT_USEC_TIMEOUT; i++) अणु
		mb();
		status = dev_priv->status_ptr[0];
		अगर ((status & mask) < threshold)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x, threshold=0x%08x\n", status, threshold);
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक
savage_bci_रुको_fअगरo_s3d(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक n)
अणु
	uपूर्णांक32_t maxUsed = dev_priv->cob_size + SAVAGE_BCI_FIFO_SIZE - n;
	uपूर्णांक32_t status;
	पूर्णांक i;

	क्रम (i = 0; i < SAVAGE_DEFAULT_USEC_TIMEOUT; i++) अणु
		status = SAVAGE_READ(SAVAGE_STATUS_WORD0);
		अगर ((status & SAVAGE_FIFO_USED_MASK_S3D) <= maxUsed)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x\n", status);
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक
savage_bci_रुको_fअगरo_s4(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक n)
अणु
	uपूर्णांक32_t maxUsed = dev_priv->cob_size + SAVAGE_BCI_FIFO_SIZE - n;
	uपूर्णांक32_t status;
	पूर्णांक i;

	क्रम (i = 0; i < SAVAGE_DEFAULT_USEC_TIMEOUT; i++) अणु
		status = SAVAGE_READ(SAVAGE_ALT_STATUS_WORD0);
		अगर ((status & SAVAGE_FIFO_USED_MASK_S4) <= maxUsed)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x\n", status);
#पूर्ण_अगर
	वापस -EBUSY;
पूर्ण

/*
 * Waiting क्रम events.
 *
 * The BIOSresets the event tag to 0 on mode changes. Thereक्रमe we
 * never emit 0 to the event tag. If we find a 0 event tag we know the
 * BIOS stomped on it and वापस success assuming that the BIOS रुकोed
 * क्रम engine idle.
 *
 * Note: अगर the Xserver uses the event tag it has to follow the same
 * rule. Otherwise there may be glitches every 2^16 events.
 */
अटल पूर्णांक
savage_bci_रुको_event_shaकरोw(drm_savage_निजी_t * dev_priv, uपूर्णांक16_t e)
अणु
	uपूर्णांक32_t status;
	पूर्णांक i;

	क्रम (i = 0; i < SAVAGE_EVENT_USEC_TIMEOUT; i++) अणु
		mb();
		status = dev_priv->status_ptr[1];
		अगर ((((status & 0xffff) - e) & 0xffff) <= 0x7fff ||
		    (status & 0xffff) == 0)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x, e=0x%04x\n", status, e);
#पूर्ण_अगर

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक
savage_bci_रुको_event_reg(drm_savage_निजी_t * dev_priv, uपूर्णांक16_t e)
अणु
	uपूर्णांक32_t status;
	पूर्णांक i;

	क्रम (i = 0; i < SAVAGE_EVENT_USEC_TIMEOUT; i++) अणु
		status = SAVAGE_READ(SAVAGE_STATUS_WORD1);
		अगर ((((status & 0xffff) - e) & 0xffff) <= 0x7fff ||
		    (status & 0xffff) == 0)
			वापस 0;
		udelay(1);
	पूर्ण

#अगर SAVAGE_BCI_DEBUG
	DRM_ERROR("failed!\n");
	DRM_INFO("   status=0x%08x, e=0x%04x\n", status, e);
#पूर्ण_अगर

	वापस -EBUSY;
पूर्ण

uपूर्णांक16_t savage_bci_emit_event(drm_savage_निजी_t * dev_priv,
			       अचिन्हित पूर्णांक flags)
अणु
	uपूर्णांक16_t count;
	BCI_LOCALS;

	अगर (dev_priv->status_ptr) अणु
		/* coordinate with Xserver */
		count = dev_priv->status_ptr[1023];
		अगर (count < dev_priv->event_counter)
			dev_priv->event_wrap++;
	पूर्ण अन्यथा अणु
		count = dev_priv->event_counter;
	पूर्ण
	count = (count + 1) & 0xffff;
	अगर (count == 0) अणु
		count++;	/* See the comment above savage_रुको_event_*. */
		dev_priv->event_wrap++;
	पूर्ण
	dev_priv->event_counter = count;
	अगर (dev_priv->status_ptr)
		dev_priv->status_ptr[1023] = (uपूर्णांक32_t) count;

	अगर ((flags & (SAVAGE_WAIT_2D | SAVAGE_WAIT_3D))) अणु
		अचिन्हित पूर्णांक रुको_cmd = BCI_CMD_WAIT;
		अगर ((flags & SAVAGE_WAIT_2D))
			रुको_cmd |= BCI_CMD_WAIT_2D;
		अगर ((flags & SAVAGE_WAIT_3D))
			रुको_cmd |= BCI_CMD_WAIT_3D;
		BEGIN_BCI(2);
		BCI_WRITE(रुको_cmd);
	पूर्ण अन्यथा अणु
		BEGIN_BCI(1);
	पूर्ण
	BCI_WRITE(BCI_CMD_UPDATE_EVENT_TAG | (uपूर्णांक32_t) count);

	वापस count;
पूर्ण

/*
 * Freelist management
 */
अटल पूर्णांक savage_मुक्तlist_init(काष्ठा drm_device * dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf *buf;
	drm_savage_buf_priv_t *entry;
	पूर्णांक i;
	DRM_DEBUG("count=%d\n", dma->buf_count);

	dev_priv->head.next = &dev_priv->tail;
	dev_priv->head.prev = शून्य;
	dev_priv->head.buf = शून्य;

	dev_priv->tail.next = शून्य;
	dev_priv->tail.prev = &dev_priv->head;
	dev_priv->tail.buf = शून्य;

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		buf = dma->buflist[i];
		entry = buf->dev_निजी;

		SET_AGE(&entry->age, 0, 0);
		entry->buf = buf;

		entry->next = dev_priv->head.next;
		entry->prev = &dev_priv->head;
		dev_priv->head.next->prev = entry;
		dev_priv->head.next = entry;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_buf *savage_मुक्तlist_get(काष्ठा drm_device * dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	drm_savage_buf_priv_t *tail = dev_priv->tail.prev;
	uपूर्णांक16_t event;
	अचिन्हित पूर्णांक wrap;
	DRM_DEBUG("\n");

	UPDATE_EVENT_COUNTER();
	अगर (dev_priv->status_ptr)
		event = dev_priv->status_ptr[1] & 0xffff;
	अन्यथा
		event = SAVAGE_READ(SAVAGE_STATUS_WORD1) & 0xffff;
	wrap = dev_priv->event_wrap;
	अगर (event > dev_priv->event_counter)
		wrap--;		/* hardware hasn't passed the last wrap yet */

	DRM_DEBUG("   tail=0x%04x %d\n", tail->age.event, tail->age.wrap);
	DRM_DEBUG("   head=0x%04x %d\n", event, wrap);

	अगर (tail->buf && (TEST_AGE(&tail->age, event, wrap) || event == 0)) अणु
		drm_savage_buf_priv_t *next = tail->next;
		drm_savage_buf_priv_t *prev = tail->prev;
		prev->next = next;
		next->prev = prev;
		tail->next = tail->prev = शून्य;
		वापस tail->buf;
	पूर्ण

	DRM_DEBUG("returning NULL, tail->buf=%p!\n", tail->buf);
	वापस शून्य;
पूर्ण

व्योम savage_मुक्तlist_put(काष्ठा drm_device * dev, काष्ठा drm_buf * buf)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	drm_savage_buf_priv_t *entry = buf->dev_निजी, *prev, *next;

	DRM_DEBUG("age=0x%04x wrap=%d\n", entry->age.event, entry->age.wrap);

	अगर (entry->next != शून्य || entry->prev != शून्य) अणु
		DRM_ERROR("entry already on freelist.\n");
		वापस;
	पूर्ण

	prev = &dev_priv->head;
	next = prev->next;
	prev->next = entry;
	next->prev = entry;
	entry->prev = prev;
	entry->next = next;
पूर्ण

/*
 * Command DMA
 */
अटल पूर्णांक savage_dma_init(drm_savage_निजी_t * dev_priv)
अणु
	अचिन्हित पूर्णांक i;

	dev_priv->nr_dma_pages = dev_priv->cmd_dma->size /
	    (SAVAGE_DMA_PAGE_SIZE * 4);
	dev_priv->dma_pages = kदो_स्मृति_array(dev_priv->nr_dma_pages,
					    माप(drm_savage_dma_page_t),
					    GFP_KERNEL);
	अगर (dev_priv->dma_pages == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev_priv->nr_dma_pages; ++i) अणु
		SET_AGE(&dev_priv->dma_pages[i].age, 0, 0);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	पूर्ण
	SET_AGE(&dev_priv->last_dma_age, 0, 0);

	dev_priv->first_dma_page = 0;
	dev_priv->current_dma_page = 0;

	वापस 0;
पूर्ण

व्योम savage_dma_reset(drm_savage_निजी_t * dev_priv)
अणु
	uपूर्णांक16_t event;
	अचिन्हित पूर्णांक wrap, i;
	event = savage_bci_emit_event(dev_priv, 0);
	wrap = dev_priv->event_wrap;
	क्रम (i = 0; i < dev_priv->nr_dma_pages; ++i) अणु
		SET_AGE(&dev_priv->dma_pages[i].age, event, wrap);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	पूर्ण
	SET_AGE(&dev_priv->last_dma_age, event, wrap);
	dev_priv->first_dma_page = dev_priv->current_dma_page = 0;
पूर्ण

व्योम savage_dma_रुको(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक page)
अणु
	uपूर्णांक16_t event;
	अचिन्हित पूर्णांक wrap;

	/* Faked DMA buffer pages करोn't age. */
	अगर (dev_priv->cmd_dma == &dev_priv->fake_dma)
		वापस;

	UPDATE_EVENT_COUNTER();
	अगर (dev_priv->status_ptr)
		event = dev_priv->status_ptr[1] & 0xffff;
	अन्यथा
		event = SAVAGE_READ(SAVAGE_STATUS_WORD1) & 0xffff;
	wrap = dev_priv->event_wrap;
	अगर (event > dev_priv->event_counter)
		wrap--;		/* hardware hasn't passed the last wrap yet */

	अगर (dev_priv->dma_pages[page].age.wrap > wrap ||
	    (dev_priv->dma_pages[page].age.wrap == wrap &&
	     dev_priv->dma_pages[page].age.event > event)) अणु
		अगर (dev_priv->रुको_evnt(dev_priv,
					dev_priv->dma_pages[page].age.event)
		    < 0)
			DRM_ERROR("wait_evnt failed!\n");
	पूर्ण
पूर्ण

uपूर्णांक32_t *savage_dma_alloc(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक cur = dev_priv->current_dma_page;
	अचिन्हित पूर्णांक rest = SAVAGE_DMA_PAGE_SIZE -
	    dev_priv->dma_pages[cur].used;
	अचिन्हित पूर्णांक nr_pages = (n - rest + SAVAGE_DMA_PAGE_SIZE - 1) /
	    SAVAGE_DMA_PAGE_SIZE;
	uपूर्णांक32_t *dma_ptr;
	अचिन्हित पूर्णांक i;

	DRM_DEBUG("cur=%u, cur->used=%u, n=%u, rest=%u, nr_pages=%u\n",
		  cur, dev_priv->dma_pages[cur].used, n, rest, nr_pages);

	अगर (cur + nr_pages < dev_priv->nr_dma_pages) अणु
		dma_ptr = (uपूर्णांक32_t *) dev_priv->cmd_dma->handle +
		    cur * SAVAGE_DMA_PAGE_SIZE + dev_priv->dma_pages[cur].used;
		अगर (n < rest)
			rest = n;
		dev_priv->dma_pages[cur].used += rest;
		n -= rest;
		cur++;
	पूर्ण अन्यथा अणु
		dev_priv->dma_flush(dev_priv);
		nr_pages =
		    (n + SAVAGE_DMA_PAGE_SIZE - 1) / SAVAGE_DMA_PAGE_SIZE;
		क्रम (i = cur; i < dev_priv->nr_dma_pages; ++i) अणु
			dev_priv->dma_pages[i].age = dev_priv->last_dma_age;
			dev_priv->dma_pages[i].used = 0;
			dev_priv->dma_pages[i].flushed = 0;
		पूर्ण
		dma_ptr = (uपूर्णांक32_t *) dev_priv->cmd_dma->handle;
		dev_priv->first_dma_page = cur = 0;
	पूर्ण
	क्रम (i = cur; nr_pages > 0; ++i, --nr_pages) अणु
#अगर SAVAGE_DMA_DEBUG
		अगर (dev_priv->dma_pages[i].used) अणु
			DRM_ERROR("unflushed page %u: used=%u\n",
				  i, dev_priv->dma_pages[i].used);
		पूर्ण
#पूर्ण_अगर
		अगर (n > SAVAGE_DMA_PAGE_SIZE)
			dev_priv->dma_pages[i].used = SAVAGE_DMA_PAGE_SIZE;
		अन्यथा
			dev_priv->dma_pages[i].used = n;
		n -= SAVAGE_DMA_PAGE_SIZE;
	पूर्ण
	dev_priv->current_dma_page = --i;

	DRM_DEBUG("cur=%u, cur->used=%u, n=%u\n",
		  i, dev_priv->dma_pages[i].used, n);

	savage_dma_रुको(dev_priv, dev_priv->current_dma_page);

	वापस dma_ptr;
पूर्ण

अटल व्योम savage_dma_flush(drm_savage_निजी_t * dev_priv)
अणु
	अचिन्हित पूर्णांक first = dev_priv->first_dma_page;
	अचिन्हित पूर्णांक cur = dev_priv->current_dma_page;
	uपूर्णांक16_t event;
	अचिन्हित पूर्णांक wrap, pad, align, len, i;
	अचिन्हित दीर्घ phys_addr;
	BCI_LOCALS;

	अगर (first == cur &&
	    dev_priv->dma_pages[cur].used == dev_priv->dma_pages[cur].flushed)
		वापस;

	/* pad length to multiples of 2 entries
	 * align start of next DMA block to multiles of 8 entries */
	pad = -dev_priv->dma_pages[cur].used & 1;
	align = -(dev_priv->dma_pages[cur].used + pad) & 7;

	DRM_DEBUG("first=%u, cur=%u, first->flushed=%u, cur->used=%u, "
		  "pad=%u, align=%u\n",
		  first, cur, dev_priv->dma_pages[first].flushed,
		  dev_priv->dma_pages[cur].used, pad, align);

	/* pad with noops */
	अगर (pad) अणु
		uपूर्णांक32_t *dma_ptr = (uपूर्णांक32_t *) dev_priv->cmd_dma->handle +
		    cur * SAVAGE_DMA_PAGE_SIZE + dev_priv->dma_pages[cur].used;
		dev_priv->dma_pages[cur].used += pad;
		जबतक (pad != 0) अणु
			*dma_ptr++ = BCI_CMD_WAIT;
			pad--;
		पूर्ण
	पूर्ण

	mb();

	/* करो flush ... */
	phys_addr = dev_priv->cmd_dma->offset +
	    (first * SAVAGE_DMA_PAGE_SIZE +
	     dev_priv->dma_pages[first].flushed) * 4;
	len = (cur - first) * SAVAGE_DMA_PAGE_SIZE +
	    dev_priv->dma_pages[cur].used - dev_priv->dma_pages[first].flushed;

	DRM_DEBUG("phys_addr=%lx, len=%u\n",
		  phys_addr | dev_priv->dma_type, len);

	BEGIN_BCI(3);
	BCI_SET_REGISTERS(SAVAGE_DMABUFADDR, 1);
	BCI_WRITE(phys_addr | dev_priv->dma_type);
	BCI_DMA(len);

	/* fix alignment of the start of the next block */
	dev_priv->dma_pages[cur].used += align;

	/* age DMA pages */
	event = savage_bci_emit_event(dev_priv, 0);
	wrap = dev_priv->event_wrap;
	क्रम (i = first; i < cur; ++i) अणु
		SET_AGE(&dev_priv->dma_pages[i].age, event, wrap);
		dev_priv->dma_pages[i].used = 0;
		dev_priv->dma_pages[i].flushed = 0;
	पूर्ण
	/* age the current page only when it's full */
	अगर (dev_priv->dma_pages[cur].used == SAVAGE_DMA_PAGE_SIZE) अणु
		SET_AGE(&dev_priv->dma_pages[cur].age, event, wrap);
		dev_priv->dma_pages[cur].used = 0;
		dev_priv->dma_pages[cur].flushed = 0;
		/* advance to next page */
		cur++;
		अगर (cur == dev_priv->nr_dma_pages)
			cur = 0;
		dev_priv->first_dma_page = dev_priv->current_dma_page = cur;
	पूर्ण अन्यथा अणु
		dev_priv->first_dma_page = cur;
		dev_priv->dma_pages[cur].flushed = dev_priv->dma_pages[i].used;
	पूर्ण
	SET_AGE(&dev_priv->last_dma_age, event, wrap);

	DRM_DEBUG("first=cur=%u, cur->used=%u, cur->flushed=%u\n", cur,
		  dev_priv->dma_pages[cur].used,
		  dev_priv->dma_pages[cur].flushed);
पूर्ण

अटल व्योम savage_fake_dma_flush(drm_savage_निजी_t * dev_priv)
अणु
	अचिन्हित पूर्णांक i, j;
	BCI_LOCALS;

	अगर (dev_priv->first_dma_page == dev_priv->current_dma_page &&
	    dev_priv->dma_pages[dev_priv->current_dma_page].used == 0)
		वापस;

	DRM_DEBUG("first=%u, cur=%u, cur->used=%u\n",
		  dev_priv->first_dma_page, dev_priv->current_dma_page,
		  dev_priv->dma_pages[dev_priv->current_dma_page].used);

	क्रम (i = dev_priv->first_dma_page;
	     i <= dev_priv->current_dma_page && dev_priv->dma_pages[i].used;
	     ++i) अणु
		uपूर्णांक32_t *dma_ptr = (uपूर्णांक32_t *) dev_priv->cmd_dma->handle +
		    i * SAVAGE_DMA_PAGE_SIZE;
#अगर SAVAGE_DMA_DEBUG
		/* Sanity check: all pages except the last one must be full. */
		अगर (i < dev_priv->current_dma_page &&
		    dev_priv->dma_pages[i].used != SAVAGE_DMA_PAGE_SIZE) अणु
			DRM_ERROR("partial DMA page %u: used=%u",
				  i, dev_priv->dma_pages[i].used);
		पूर्ण
#पूर्ण_अगर
		BEGIN_BCI(dev_priv->dma_pages[i].used);
		क्रम (j = 0; j < dev_priv->dma_pages[i].used; ++j) अणु
			BCI_WRITE(dma_ptr[j]);
		पूर्ण
		dev_priv->dma_pages[i].used = 0;
	पूर्ण

	/* reset to first page */
	dev_priv->first_dma_page = dev_priv->current_dma_page = 0;
पूर्ण

पूर्णांक savage_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ chipset)
अणु
	drm_savage_निजी_t *dev_priv;

	dev_priv = kzalloc(माप(drm_savage_निजी_t), GFP_KERNEL);
	अगर (dev_priv == शून्य)
		वापस -ENOMEM;

	dev->dev_निजी = (व्योम *)dev_priv;

	dev_priv->chipset = (क्रमागत savage_family)chipset;

	pci_set_master(dev->pdev);

	वापस 0;
पूर्ण


/*
 * Initialize mappings. On Savage4 and SavageIX the alignment
 * and size of the aperture is not suitable क्रम स्वतःmatic MTRR setup
 * in drm_legacy_addmap. Thereक्रमe we add them manually beक्रमe the maps are
 * initialized, and tear them करोwn on last बंद.
 */
पूर्णांक savage_driver_firstखोलो(काष्ठा drm_device *dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ mmio_base, fb_base, fb_size, aperture_base;
	पूर्णांक ret = 0;

	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		fb_base = pci_resource_start(dev->pdev, 0);
		fb_size = SAVAGE_FB_SIZE_S3;
		mmio_base = fb_base + SAVAGE_FB_SIZE_S3;
		aperture_base = fb_base + SAVAGE_APERTURE_OFFSET;
		/* this should always be true */
		अगर (pci_resource_len(dev->pdev, 0) == 0x08000000) अणु
			/* Don't make MMIO ग_लिखो-cobining! We need 3
			 * MTRRs. */
			dev_priv->mtrr_handles[0] =
				arch_phys_wc_add(fb_base, 0x01000000);
			dev_priv->mtrr_handles[1] =
				arch_phys_wc_add(fb_base + 0x02000000,
						 0x02000000);
			dev_priv->mtrr_handles[2] =
				arch_phys_wc_add(fb_base + 0x04000000,
						0x04000000);
		पूर्ण अन्यथा अणु
			DRM_ERROR("strange pci_resource_len %08llx\n",
				  (अचिन्हित दीर्घ दीर्घ)
				  pci_resource_len(dev->pdev, 0));
		पूर्ण
	पूर्ण अन्यथा अगर (dev_priv->chipset != S3_SUPERSAVAGE &&
		   dev_priv->chipset != S3_SAVAGE2000) अणु
		mmio_base = pci_resource_start(dev->pdev, 0);
		fb_base = pci_resource_start(dev->pdev, 1);
		fb_size = SAVAGE_FB_SIZE_S4;
		aperture_base = fb_base + SAVAGE_APERTURE_OFFSET;
		/* this should always be true */
		अगर (pci_resource_len(dev->pdev, 1) == 0x08000000) अणु
			/* Can use one MTRR to cover both fb and
			 * aperture. */
			dev_priv->mtrr_handles[0] =
				arch_phys_wc_add(fb_base,
						 0x08000000);
		पूर्ण अन्यथा अणु
			DRM_ERROR("strange pci_resource_len %08llx\n",
				  (अचिन्हित दीर्घ दीर्घ)
				  pci_resource_len(dev->pdev, 1));
		पूर्ण
	पूर्ण अन्यथा अणु
		mmio_base = pci_resource_start(dev->pdev, 0);
		fb_base = pci_resource_start(dev->pdev, 1);
		fb_size = pci_resource_len(dev->pdev, 1);
		aperture_base = pci_resource_start(dev->pdev, 2);
		/* Automatic MTRR setup will करो the right thing. */
	पूर्ण

	ret = drm_legacy_addmap(dev, mmio_base, SAVAGE_MMIO_SIZE,
				_DRM_REGISTERS, _DRM_READ_ONLY,
				&dev_priv->mmio);
	अगर (ret)
		वापस ret;

	ret = drm_legacy_addmap(dev, fb_base, fb_size, _DRM_FRAME_BUFFER,
				_DRM_WRITE_COMBINING, &dev_priv->fb);
	अगर (ret)
		वापस ret;

	ret = drm_legacy_addmap(dev, aperture_base, SAVAGE_APERTURE_SIZE,
				_DRM_FRAME_BUFFER, _DRM_WRITE_COMBINING,
				&dev_priv->aperture);
	वापस ret;
पूर्ण

/*
 * Delete MTRRs and मुक्त device-निजी data.
 */
व्योम savage_driver_lastबंद(काष्ठा drm_device *dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < 3; ++i) अणु
		arch_phys_wc_del(dev_priv->mtrr_handles[i]);
		dev_priv->mtrr_handles[i] = 0;
	पूर्ण
पूर्ण

व्योम savage_driver_unload(काष्ठा drm_device *dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;

	kमुक्त(dev_priv);
पूर्ण

अटल पूर्णांक savage_करो_init_bci(काष्ठा drm_device * dev, drm_savage_init_t * init)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;

	अगर (init->fb_bpp != 16 && init->fb_bpp != 32) अणु
		DRM_ERROR("invalid frame buffer bpp %d!\n", init->fb_bpp);
		वापस -EINVAL;
	पूर्ण
	अगर (init->depth_bpp != 16 && init->depth_bpp != 32) अणु
		DRM_ERROR("invalid depth buffer bpp %d!\n", init->fb_bpp);
		वापस -EINVAL;
	पूर्ण
	अगर (init->dma_type != SAVAGE_DMA_AGP &&
	    init->dma_type != SAVAGE_DMA_PCI) अणु
		DRM_ERROR("invalid dma memory type %d!\n", init->dma_type);
		वापस -EINVAL;
	पूर्ण

	dev_priv->cob_size = init->cob_size;
	dev_priv->bci_threshold_lo = init->bci_threshold_lo;
	dev_priv->bci_threshold_hi = init->bci_threshold_hi;
	dev_priv->dma_type = init->dma_type;

	dev_priv->fb_bpp = init->fb_bpp;
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;
	dev_priv->depth_bpp = init->depth_bpp;
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->depth_pitch = init->depth_pitch;

	dev_priv->texture_offset = init->texture_offset;
	dev_priv->texture_size = init->texture_size;

	dev_priv->sarea = drm_legacy_माला_लोarea(dev);
	अगर (!dev_priv->sarea) अणु
		DRM_ERROR("could not find sarea!\n");
		savage_करो_cleanup_bci(dev);
		वापस -EINVAL;
	पूर्ण
	अगर (init->status_offset != 0) अणु
		dev_priv->status = drm_legacy_findmap(dev, init->status_offset);
		अगर (!dev_priv->status) अणु
			DRM_ERROR("could not find shadow status region!\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_priv->status = शून्य;
	पूर्ण
	अगर (dev_priv->dma_type == SAVAGE_DMA_AGP && init->buffers_offset) अणु
		dev->agp_buffer_token = init->buffers_offset;
		dev->agp_buffer_map = drm_legacy_findmap(dev,
						       init->buffers_offset);
		अगर (!dev->agp_buffer_map) अणु
			DRM_ERROR("could not find DMA buffer region!\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
		drm_legacy_ioremap(dev->agp_buffer_map, dev);
		अगर (!dev->agp_buffer_map->handle) अणु
			DRM_ERROR("failed to ioremap DMA buffer region!\n");
			savage_करो_cleanup_bci(dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (init->agp_textures_offset) अणु
		dev_priv->agp_textures =
		    drm_legacy_findmap(dev, init->agp_textures_offset);
		अगर (!dev_priv->agp_textures) अणु
			DRM_ERROR("could not find agp texture region!\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_priv->agp_textures = शून्य;
	पूर्ण

	अगर (init->cmd_dma_offset) अणु
		अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
			DRM_ERROR("command DMA not supported on "
				  "Savage3D/MX/IX.\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
		अगर (dev->dma && dev->dma->buflist) अणु
			DRM_ERROR("command and vertex DMA not supported "
				  "at the same time.\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
		dev_priv->cmd_dma = drm_legacy_findmap(dev, init->cmd_dma_offset);
		अगर (!dev_priv->cmd_dma) अणु
			DRM_ERROR("could not find command DMA region!\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
		अगर (dev_priv->dma_type == SAVAGE_DMA_AGP) अणु
			अगर (dev_priv->cmd_dma->type != _DRM_AGP) अणु
				DRM_ERROR("AGP command DMA region is not a "
					  "_DRM_AGP map!\n");
				savage_करो_cleanup_bci(dev);
				वापस -EINVAL;
			पूर्ण
			drm_legacy_ioremap(dev_priv->cmd_dma, dev);
			अगर (!dev_priv->cmd_dma->handle) अणु
				DRM_ERROR("failed to ioremap command "
					  "DMA region!\n");
				savage_करो_cleanup_bci(dev);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अगर (dev_priv->cmd_dma->type != _DRM_CONSISTENT) अणु
			DRM_ERROR("PCI command DMA region is not a "
				  "_DRM_CONSISTENT map!\n");
			savage_करो_cleanup_bci(dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_priv->cmd_dma = शून्य;
	पूर्ण

	dev_priv->dma_flush = savage_dma_flush;
	अगर (!dev_priv->cmd_dma) अणु
		DRM_DEBUG("falling back to faked command DMA.\n");
		dev_priv->fake_dma.offset = 0;
		dev_priv->fake_dma.size = SAVAGE_FAKE_DMA_SIZE;
		dev_priv->fake_dma.type = _DRM_SHM;
		dev_priv->fake_dma.handle = kदो_स्मृति(SAVAGE_FAKE_DMA_SIZE,
						    GFP_KERNEL);
		अगर (!dev_priv->fake_dma.handle) अणु
			DRM_ERROR("could not allocate faked DMA buffer!\n");
			savage_करो_cleanup_bci(dev);
			वापस -ENOMEM;
		पूर्ण
		dev_priv->cmd_dma = &dev_priv->fake_dma;
		dev_priv->dma_flush = savage_fake_dma_flush;
	पूर्ण

	dev_priv->sarea_priv =
	    (drm_savage_sarea_t *) ((uपूर्णांक8_t *) dev_priv->sarea->handle +
				    init->sarea_priv_offset);

	/* setup biपंचांगap descriptors */
	अणु
		अचिन्हित पूर्णांक color_tile_क्रमmat;
		अचिन्हित पूर्णांक depth_tile_क्रमmat;
		अचिन्हित पूर्णांक front_stride, back_stride, depth_stride;
		अगर (dev_priv->chipset <= S3_SAVAGE4) अणु
			color_tile_क्रमmat = dev_priv->fb_bpp == 16 ?
			    SAVAGE_BD_TILE_16BPP : SAVAGE_BD_TILE_32BPP;
			depth_tile_क्रमmat = dev_priv->depth_bpp == 16 ?
			    SAVAGE_BD_TILE_16BPP : SAVAGE_BD_TILE_32BPP;
		पूर्ण अन्यथा अणु
			color_tile_क्रमmat = SAVAGE_BD_TILE_DEST;
			depth_tile_क्रमmat = SAVAGE_BD_TILE_DEST;
		पूर्ण
		front_stride = dev_priv->front_pitch / (dev_priv->fb_bpp / 8);
		back_stride = dev_priv->back_pitch / (dev_priv->fb_bpp / 8);
		depth_stride =
		    dev_priv->depth_pitch / (dev_priv->depth_bpp / 8);

		dev_priv->front_bd = front_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->fb_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (color_tile_क्रमmat << SAVAGE_BD_TILE_SHIFT);

		dev_priv->back_bd = back_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->fb_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (color_tile_क्रमmat << SAVAGE_BD_TILE_SHIFT);

		dev_priv->depth_bd = depth_stride | SAVAGE_BD_BW_DISABLE |
		    (dev_priv->depth_bpp << SAVAGE_BD_BPP_SHIFT) |
		    (depth_tile_क्रमmat << SAVAGE_BD_TILE_SHIFT);
	पूर्ण

	/* setup status and bci ptr */
	dev_priv->event_counter = 0;
	dev_priv->event_wrap = 0;
	dev_priv->bci_ptr = (अस्थिर uपूर्णांक32_t *)
	    ((uपूर्णांक8_t *) dev_priv->mmio->handle + SAVAGE_BCI_OFFSET);
	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
		dev_priv->status_used_mask = SAVAGE_FIFO_USED_MASK_S3D;
	पूर्ण अन्यथा अणु
		dev_priv->status_used_mask = SAVAGE_FIFO_USED_MASK_S4;
	पूर्ण
	अगर (dev_priv->status != शून्य) अणु
		dev_priv->status_ptr =
		    (अस्थिर uपूर्णांक32_t *)dev_priv->status->handle;
		dev_priv->रुको_fअगरo = savage_bci_रुको_fअगरo_shaकरोw;
		dev_priv->रुको_evnt = savage_bci_रुको_event_shaकरोw;
		dev_priv->status_ptr[1023] = dev_priv->event_counter;
	पूर्ण अन्यथा अणु
		dev_priv->status_ptr = शून्य;
		अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset)) अणु
			dev_priv->रुको_fअगरo = savage_bci_रुको_fअगरo_s3d;
		पूर्ण अन्यथा अणु
			dev_priv->रुको_fअगरo = savage_bci_रुको_fअगरo_s4;
		पूर्ण
		dev_priv->रुको_evnt = savage_bci_रुको_event_reg;
	पूर्ण

	/* cliprect functions */
	अगर (S3_SAVAGE3D_SERIES(dev_priv->chipset))
		dev_priv->emit_clip_rect = savage_emit_clip_rect_s3d;
	अन्यथा
		dev_priv->emit_clip_rect = savage_emit_clip_rect_s4;

	अगर (savage_मुक्तlist_init(dev) < 0) अणु
		DRM_ERROR("could not initialize freelist\n");
		savage_करो_cleanup_bci(dev);
		वापस -ENOMEM;
	पूर्ण

	अगर (savage_dma_init(dev_priv) < 0) अणु
		DRM_ERROR("could not initialize command DMA\n");
		savage_करो_cleanup_bci(dev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक savage_करो_cleanup_bci(काष्ठा drm_device * dev)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;

	अगर (dev_priv->cmd_dma == &dev_priv->fake_dma) अणु
		kमुक्त(dev_priv->fake_dma.handle);
	पूर्ण अन्यथा अगर (dev_priv->cmd_dma && dev_priv->cmd_dma->handle &&
		   dev_priv->cmd_dma->type == _DRM_AGP &&
		   dev_priv->dma_type == SAVAGE_DMA_AGP)
		drm_legacy_ioremapमुक्त(dev_priv->cmd_dma, dev);

	अगर (dev_priv->dma_type == SAVAGE_DMA_AGP &&
	    dev->agp_buffer_map && dev->agp_buffer_map->handle) अणु
		drm_legacy_ioremapमुक्त(dev->agp_buffer_map, dev);
		/* make sure the next instance (which may be running
		 * in PCI mode) करोesn't try to use an old
		 * agp_buffer_map. */
		dev->agp_buffer_map = शून्य;
	पूर्ण

	kमुक्त(dev_priv->dma_pages);

	वापस 0;
पूर्ण

अटल पूर्णांक savage_bci_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_savage_init_t *init = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	चयन (init->func) अणु
	हाल SAVAGE_INIT_BCI:
		वापस savage_करो_init_bci(dev, init);
	हाल SAVAGE_CLEANUP_BCI:
		वापस savage_करो_cleanup_bci(dev);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक savage_bci_event_emit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	drm_savage_event_emit_t *event = data;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	event->count = savage_bci_emit_event(dev_priv, event->flags);
	event->count |= dev_priv->event_wrap << 16;

	वापस 0;
पूर्ण

अटल पूर्णांक savage_bci_event_रुको(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	drm_savage_event_रुको_t *event = data;
	अचिन्हित पूर्णांक event_e, hw_e;
	अचिन्हित पूर्णांक event_w, hw_w;

	DRM_DEBUG("\n");

	UPDATE_EVENT_COUNTER();
	अगर (dev_priv->status_ptr)
		hw_e = dev_priv->status_ptr[1] & 0xffff;
	अन्यथा
		hw_e = SAVAGE_READ(SAVAGE_STATUS_WORD1) & 0xffff;
	hw_w = dev_priv->event_wrap;
	अगर (hw_e > dev_priv->event_counter)
		hw_w--;		/* hardware hasn't passed the last wrap yet */

	event_e = event->count & 0xffff;
	event_w = event->count >> 16;

	/* Don't need to रुको अगर
	 * - event counter wrapped since the event was emitted or
	 * - the hardware has advanced up to or over the event to रुको क्रम.
	 */
	अगर (event_w < hw_w || (event_w == hw_w && event_e <= hw_e))
		वापस 0;
	अन्यथा
		वापस dev_priv->रुको_evnt(dev_priv, event_e);
पूर्ण

/*
 * DMA buffer management
 */

अटल पूर्णांक savage_bci_get_buffers(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  काष्ठा drm_dma *d)
अणु
	काष्ठा drm_buf *buf;
	पूर्णांक i;

	क्रम (i = d->granted_count; i < d->request_count; i++) अणु
		buf = savage_मुक्तlist_get(dev);
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

पूर्णांक savage_bci_buffers(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
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
			  task_pid_nr(current), d->request_count, dma->buf_count);
		वापस -EINVAL;
	पूर्ण

	d->granted_count = 0;

	अगर (d->request_count) अणु
		ret = savage_bci_get_buffers(dev, file_priv, d);
	पूर्ण

	वापस ret;
पूर्ण

व्योम savage_reclaim_buffers(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	drm_savage_निजी_t *dev_priv = dev->dev_निजी;
	पूर्णांक release_idlelock = 0;
	पूर्णांक i;

	अगर (!dma)
		वापस;
	अगर (!dev_priv)
		वापस;
	अगर (!dma->buflist)
		वापस;

	अगर (file_priv->master && file_priv->master->lock.hw_lock) अणु
		drm_legacy_idlelock_take(&file_priv->master->lock);
		release_idlelock = 1;
	पूर्ण

	क्रम (i = 0; i < dma->buf_count; i++) अणु
		काष्ठा drm_buf *buf = dma->buflist[i];
		drm_savage_buf_priv_t *buf_priv = buf->dev_निजी;

		अगर (buf->file_priv == file_priv && buf_priv &&
		    buf_priv->next == शून्य && buf_priv->prev == शून्य) अणु
			uपूर्णांक16_t event;
			DRM_DEBUG("reclaimed from client\n");
			event = savage_bci_emit_event(dev_priv, SAVAGE_WAIT_3D);
			SET_AGE(&buf_priv->age, event, dev_priv->event_wrap);
			savage_मुक्तlist_put(dev, buf);
		पूर्ण
	पूर्ण

	अगर (release_idlelock)
		drm_legacy_idlelock_release(&file_priv->master->lock);
पूर्ण

स्थिर काष्ठा drm_ioctl_desc savage_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(SAVAGE_BCI_INIT, savage_bci_init, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(SAVAGE_BCI_CMDBUF, savage_bci_cmdbuf, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SAVAGE_BCI_EVENT_EMIT, savage_bci_event_emit, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SAVAGE_BCI_EVENT_WAIT, savage_bci_event_रुको, DRM_AUTH),
पूर्ण;

पूर्णांक savage_max_ioctl = ARRAY_SIZE(savage_ioctls);
