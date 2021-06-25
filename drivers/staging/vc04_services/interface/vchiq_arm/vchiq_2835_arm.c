<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#घोषणा TOTAL_SLOTS (VCHIQ_SLOT_ZERO_SLOTS + 2 * 32)

#समावेश "vchiq_arm.h"
#समावेश "vchiq_connected.h"
#समावेश "vchiq_pagelist.h"

#घोषणा MAX_FRAGMENTS (VCHIQ_NUM_CURRENT_BULKS * 2)

#घोषणा VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX 0
#घोषणा VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX  1

#घोषणा BELL0	0x00
#घोषणा BELL2	0x08

काष्ठा vchiq_2835_state अणु
	पूर्णांक inited;
	काष्ठा vchiq_arm_state arm_state;
पूर्ण;

काष्ठा vchiq_pagelist_info अणु
	काष्ठा pagelist *pagelist;
	माप_प्रकार pagelist_buffer_size;
	dma_addr_t dma_addr;
	क्रमागत dma_data_direction dma_dir;
	अचिन्हित पूर्णांक num_pages;
	अचिन्हित पूर्णांक pages_need_release;
	काष्ठा page **pages;
	काष्ठा scatterlist *scatterlist;
	अचिन्हित पूर्णांक scatterlist_mapped;
पूर्ण;

अटल व्योम __iomem *g_regs;
/* This value is the size of the L2 cache lines as understood by the
 * VPU firmware, which determines the required alignment of the
 * offsets/sizes in pagelists.
 *
 * Modern VPU firmware looks क्रम a DT "cache-line-size" property in
 * the VCHIQ node and will overग_लिखो it with the actual L2 cache size,
 * which the kernel must then respect.  That property was rejected
 * upstream, so we have to use the VPU firmware's compatibility value
 * of 32.
 */
अटल अचिन्हित पूर्णांक g_cache_line_size = 32;
अटल अचिन्हित पूर्णांक g_fragments_size;
अटल अक्षर *g_fragments_base;
अटल अक्षर *g_मुक्त_fragments;
अटल काष्ठा semaphore g_मुक्त_fragments_sema;
अटल काष्ठा device *g_dev;

अटल DEFINE_SEMAPHORE(g_मुक्त_fragments_mutex);

अटल irqवापस_t
vchiq_करोorbell_irq(पूर्णांक irq, व्योम *dev_id);

अटल काष्ठा vchiq_pagelist_info *
create_pagelist(अक्षर *buf, अक्षर __user *ubuf, माप_प्रकार count, अचिन्हित लघु type);

अटल व्योम
मुक्त_pagelist(काष्ठा vchiq_pagelist_info *pagelistinfo,
	      पूर्णांक actual);

पूर्णांक vchiq_platक्रमm_init(काष्ठा platक्रमm_device *pdev, काष्ठा vchiq_state *state)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vchiq_drvdata *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा rpi_firmware *fw = drvdata->fw;
	काष्ठा vchiq_slot_zero *vchiq_slot_zero;
	व्योम *slot_mem;
	dma_addr_t slot_phys;
	u32 channelbase;
	पूर्णांक slot_mem_size, frag_mem_size;
	पूर्णांक err, irq, i;

	/*
	 * VCHI messages between the CPU and firmware use
	 * 32-bit bus addresses.
	 */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	अगर (err < 0)
		वापस err;

	g_cache_line_size = drvdata->cache_line_size;
	g_fragments_size = 2 * g_cache_line_size;

	/* Allocate space क्रम the channels in coherent memory */
	slot_mem_size = PAGE_ALIGN(TOTAL_SLOTS * VCHIQ_SLOT_SIZE);
	frag_mem_size = PAGE_ALIGN(g_fragments_size * MAX_FRAGMENTS);

	slot_mem = dmam_alloc_coherent(dev, slot_mem_size + frag_mem_size,
				       &slot_phys, GFP_KERNEL);
	अगर (!slot_mem) अणु
		dev_err(dev, "could not allocate DMA memory\n");
		वापस -ENOMEM;
	पूर्ण

	WARN_ON(((अचिन्हित दीर्घ)slot_mem & (PAGE_SIZE - 1)) != 0);

	vchiq_slot_zero = vchiq_init_slots(slot_mem, slot_mem_size);
	अगर (!vchiq_slot_zero)
		वापस -EINVAL;

	vchiq_slot_zero->platक्रमm_data[VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX] =
		(पूर्णांक)slot_phys + slot_mem_size;
	vchiq_slot_zero->platक्रमm_data[VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX] =
		MAX_FRAGMENTS;

	g_fragments_base = (अक्षर *)slot_mem + slot_mem_size;

	g_मुक्त_fragments = g_fragments_base;
	क्रम (i = 0; i < (MAX_FRAGMENTS - 1); i++) अणु
		*(अक्षर **)&g_fragments_base[i*g_fragments_size] =
			&g_fragments_base[(i + 1)*g_fragments_size];
	पूर्ण
	*(अक्षर **)&g_fragments_base[i * g_fragments_size] = शून्य;
	sema_init(&g_मुक्त_fragments_sema, MAX_FRAGMENTS);

	अगर (vchiq_init_state(state, vchiq_slot_zero) != VCHIQ_SUCCESS)
		वापस -EINVAL;

	g_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(g_regs))
		वापस PTR_ERR(g_regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	err = devm_request_irq(dev, irq, vchiq_करोorbell_irq, IRQF_IRQPOLL,
			       "VCHIQ doorbell", state);
	अगर (err) अणु
		dev_err(dev, "failed to register irq=%d\n", irq);
		वापस err;
	पूर्ण

	/* Send the base address of the slots to VideoCore */
	channelbase = slot_phys;
	err = rpi_firmware_property(fw, RPI_FIRMWARE_VCHIQ_INIT,
				    &channelbase, माप(channelbase));
	अगर (err || channelbase) अणु
		dev_err(dev, "failed to set channelbase\n");
		वापस err ? : -ENXIO;
	पूर्ण

	g_dev = dev;
	vchiq_log_info(vchiq_arm_log_level,
		"vchiq_init - done (slots %pK, phys %pad)",
		vchiq_slot_zero, &slot_phys);

	vchiq_call_connected_callbacks();

	वापस 0;
पूर्ण

क्रमागत vchiq_status
vchiq_platक्रमm_init_state(काष्ठा vchiq_state *state)
अणु
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;
	काष्ठा vchiq_2835_state *platक्रमm_state;

	state->platक्रमm_state = kzalloc(माप(*platक्रमm_state), GFP_KERNEL);
	अगर (!state->platक्रमm_state)
		वापस VCHIQ_ERROR;

	platक्रमm_state = (काष्ठा vchiq_2835_state *)state->platक्रमm_state;

	platक्रमm_state->inited = 1;
	status = vchiq_arm_init_state(state, &platक्रमm_state->arm_state);

	अगर (status != VCHIQ_SUCCESS)
		platक्रमm_state->inited = 0;

	वापस status;
पूर्ण

काष्ठा vchiq_arm_state*
vchiq_platक्रमm_get_arm_state(काष्ठा vchiq_state *state)
अणु
	काष्ठा vchiq_2835_state *platक्रमm_state;

	platक्रमm_state   = (काष्ठा vchiq_2835_state *)state->platक्रमm_state;

	WARN_ON_ONCE(!platक्रमm_state->inited);

	वापस &platक्रमm_state->arm_state;
पूर्ण

व्योम
remote_event_संकेत(काष्ठा remote_event *event)
अणु
	wmb();

	event->fired = 1;

	dsb(sy);         /* data barrier operation */

	अगर (event->armed)
		ग_लिखोl(0, g_regs + BELL2); /* trigger vc पूर्णांकerrupt */
पूर्ण

क्रमागत vchiq_status
vchiq_prepare_bulk_data(काष्ठा vchiq_bulk *bulk, व्योम *offset,
			व्योम __user *uoffset, पूर्णांक size, पूर्णांक dir)
अणु
	काष्ठा vchiq_pagelist_info *pagelistinfo;

	pagelistinfo = create_pagelist(offset, uoffset, size,
				       (dir == VCHIQ_BULK_RECEIVE)
				       ? PAGELIST_READ
				       : PAGELIST_WRITE);

	अगर (!pagelistinfo)
		वापस VCHIQ_ERROR;

	bulk->data = pagelistinfo->dma_addr;

	/*
	 * Store the pagelistinfo address in remote_data,
	 * which isn't used by the slave.
	 */
	bulk->remote_data = pagelistinfo;

	वापस VCHIQ_SUCCESS;
पूर्ण

व्योम
vchiq_complete_bulk(काष्ठा vchiq_bulk *bulk)
अणु
	अगर (bulk && bulk->remote_data && bulk->actual)
		मुक्त_pagelist((काष्ठा vchiq_pagelist_info *)bulk->remote_data,
			      bulk->actual);
पूर्ण

पूर्णांक vchiq_dump_platक्रमm_state(व्योम *dump_context)
अणु
	अक्षर buf[80];
	पूर्णांक len;

	len = snम_लिखो(buf, माप(buf),
		"  Platform: 2835 (VC master)");
	वापस vchiq_dump(dump_context, buf, len + 1);
पूर्ण

/*
 * Local functions
 */

अटल irqवापस_t
vchiq_करोorbell_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vchiq_state *state = dev_id;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित पूर्णांक status;

	/* Read (and clear) the करोorbell */
	status = पढ़ोl(g_regs + BELL0);

	अगर (status & 0x4) अणु  /* Was the करोorbell rung? */
		remote_event_pollall(state);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
cleanup_pagelistinfo(काष्ठा vchiq_pagelist_info *pagelistinfo)
अणु
	अगर (pagelistinfo->scatterlist_mapped) अणु
		dma_unmap_sg(g_dev, pagelistinfo->scatterlist,
			     pagelistinfo->num_pages, pagelistinfo->dma_dir);
	पूर्ण

	अगर (pagelistinfo->pages_need_release)
		unpin_user_pages(pagelistinfo->pages, pagelistinfo->num_pages);

	dma_मुक्त_coherent(g_dev, pagelistinfo->pagelist_buffer_size,
			  pagelistinfo->pagelist, pagelistinfo->dma_addr);
पूर्ण

/* There is a potential problem with partial cache lines (pages?)
 * at the ends of the block when पढ़ोing. If the CPU accessed anything in
 * the same line (page?) then it may have pulled old data पूर्णांकo the cache,
 * obscuring the new data underneath. We can solve this by transferring the
 * partial cache lines separately, and allowing the ARM to copy पूर्णांकo the
 * cached area.
 */

अटल काष्ठा vchiq_pagelist_info *
create_pagelist(अक्षर *buf, अक्षर __user *ubuf,
		माप_प्रकार count, अचिन्हित लघु type)
अणु
	काष्ठा pagelist *pagelist;
	काष्ठा vchiq_pagelist_info *pagelistinfo;
	काष्ठा page **pages;
	u32 *addrs;
	अचिन्हित पूर्णांक num_pages, offset, i, k;
	पूर्णांक actual_pages;
	माप_प्रकार pagelist_size;
	काष्ठा scatterlist *scatterlist, *sg;
	पूर्णांक dma_buffers;
	dma_addr_t dma_addr;

	अगर (count >= पूर्णांक_उच्च - PAGE_SIZE)
		वापस शून्य;

	अगर (buf)
		offset = (uपूर्णांकptr_t)buf & (PAGE_SIZE - 1);
	अन्यथा
		offset = (uपूर्णांकptr_t)ubuf & (PAGE_SIZE - 1);
	num_pages = DIV_ROUND_UP(count + offset, PAGE_SIZE);

	अगर (num_pages > (SIZE_MAX - माप(काष्ठा pagelist) -
			 माप(काष्ठा vchiq_pagelist_info)) /
			(माप(u32) + माप(pages[0]) +
			 माप(काष्ठा scatterlist)))
		वापस शून्य;

	pagelist_size = माप(काष्ठा pagelist) +
			(num_pages * माप(u32)) +
			(num_pages * माप(pages[0]) +
			(num_pages * माप(काष्ठा scatterlist))) +
			माप(काष्ठा vchiq_pagelist_info);

	/* Allocate enough storage to hold the page poपूर्णांकers and the page
	 * list
	 */
	pagelist = dma_alloc_coherent(g_dev, pagelist_size, &dma_addr,
				      GFP_KERNEL);

	vchiq_log_trace(vchiq_arm_log_level, "%s - %pK", __func__, pagelist);

	अगर (!pagelist)
		वापस शून्य;

	addrs		= pagelist->addrs;
	pages		= (काष्ठा page **)(addrs + num_pages);
	scatterlist	= (काष्ठा scatterlist *)(pages + num_pages);
	pagelistinfo	= (काष्ठा vchiq_pagelist_info *)
			  (scatterlist + num_pages);

	pagelist->length = count;
	pagelist->type = type;
	pagelist->offset = offset;

	/* Populate the fields of the pagelistinfo काष्ठाure */
	pagelistinfo->pagelist = pagelist;
	pagelistinfo->pagelist_buffer_size = pagelist_size;
	pagelistinfo->dma_addr = dma_addr;
	pagelistinfo->dma_dir =  (type == PAGELIST_WRITE) ?
				  DMA_TO_DEVICE : DMA_FROM_DEVICE;
	pagelistinfo->num_pages = num_pages;
	pagelistinfo->pages_need_release = 0;
	pagelistinfo->pages = pages;
	pagelistinfo->scatterlist = scatterlist;
	pagelistinfo->scatterlist_mapped = 0;

	अगर (buf) अणु
		अचिन्हित दीर्घ length = count;
		अचिन्हित पूर्णांक off = offset;

		क्रम (actual_pages = 0; actual_pages < num_pages;
		     actual_pages++) अणु
			काष्ठा page *pg =
				vदो_स्मृति_to_page((buf +
						 (actual_pages * PAGE_SIZE)));
			माप_प्रकार bytes = PAGE_SIZE - off;

			अगर (!pg) अणु
				cleanup_pagelistinfo(pagelistinfo);
				वापस शून्य;
			पूर्ण

			अगर (bytes > length)
				bytes = length;
			pages[actual_pages] = pg;
			length -= bytes;
			off = 0;
		पूर्ण
		/* करो not try and release vदो_स्मृति pages */
	पूर्ण अन्यथा अणु
		actual_pages = pin_user_pages_fast(
					  (अचिन्हित दीर्घ)ubuf & PAGE_MASK,
					  num_pages,
					  type == PAGELIST_READ,
					  pages);

		अगर (actual_pages != num_pages) अणु
			vchiq_log_info(vchiq_arm_log_level,
				       "%s - only %d/%d pages locked",
				       __func__, actual_pages, num_pages);

			/* This is probably due to the process being समाप्तed */
			अगर (actual_pages > 0)
				unpin_user_pages(pages, actual_pages);
			cleanup_pagelistinfo(pagelistinfo);
			वापस शून्य;
		पूर्ण
		 /* release user pages */
		pagelistinfo->pages_need_release = 1;
	पूर्ण

	/*
	 * Initialize the scatterlist so that the magic cookie
	 *  is filled अगर debugging is enabled
	 */
	sg_init_table(scatterlist, num_pages);
	/* Now set the pages क्रम each scatterlist */
	क्रम (i = 0; i < num_pages; i++)	अणु
		अचिन्हित पूर्णांक len = PAGE_SIZE - offset;

		अगर (len > count)
			len = count;
		sg_set_page(scatterlist + i, pages[i], len, offset);
		offset = 0;
		count -= len;
	पूर्ण

	dma_buffers = dma_map_sg(g_dev,
				 scatterlist,
				 num_pages,
				 pagelistinfo->dma_dir);

	अगर (dma_buffers == 0) अणु
		cleanup_pagelistinfo(pagelistinfo);
		वापस शून्य;
	पूर्ण

	pagelistinfo->scatterlist_mapped = 1;

	/* Combine adjacent blocks क्रम perक्रमmance */
	k = 0;
	क्रम_each_sg(scatterlist, sg, dma_buffers, i) अणु
		u32 len = sg_dma_len(sg);
		u32 addr = sg_dma_address(sg);

		/* Note: addrs is the address + page_count - 1
		 * The firmware expects blocks after the first to be page-
		 * aligned and a multiple of the page size
		 */
		WARN_ON(len == 0);
		WARN_ON(i && (i != (dma_buffers - 1)) && (len & ~PAGE_MASK));
		WARN_ON(i && (addr & ~PAGE_MASK));
		अगर (k > 0 &&
		    ((addrs[k - 1] & PAGE_MASK) +
		     (((addrs[k - 1] & ~PAGE_MASK) + 1) << PAGE_SHIFT))
		    == (addr & PAGE_MASK))
			addrs[k - 1] += ((len + PAGE_SIZE - 1) >> PAGE_SHIFT);
		अन्यथा
			addrs[k++] = (addr & PAGE_MASK) |
				(((len + PAGE_SIZE - 1) >> PAGE_SHIFT) - 1);
	पूर्ण

	/* Partial cache lines (fragments) require special measures */
	अगर ((type == PAGELIST_READ) &&
		((pagelist->offset & (g_cache_line_size - 1)) ||
		((pagelist->offset + pagelist->length) &
		(g_cache_line_size - 1)))) अणु
		अक्षर *fragments;

		अगर (करोwn_पूर्णांकerruptible(&g_मुक्त_fragments_sema)) अणु
			cleanup_pagelistinfo(pagelistinfo);
			वापस शून्य;
		पूर्ण

		WARN_ON(!g_मुक्त_fragments);

		करोwn(&g_मुक्त_fragments_mutex);
		fragments = g_मुक्त_fragments;
		WARN_ON(!fragments);
		g_मुक्त_fragments = *(अक्षर **) g_मुक्त_fragments;
		up(&g_मुक्त_fragments_mutex);
		pagelist->type = PAGELIST_READ_WITH_FRAGMENTS +
			(fragments - g_fragments_base) / g_fragments_size;
	पूर्ण

	वापस pagelistinfo;
पूर्ण

अटल व्योम
मुक्त_pagelist(काष्ठा vchiq_pagelist_info *pagelistinfo,
	      पूर्णांक actual)
अणु
	काष्ठा pagelist *pagelist = pagelistinfo->pagelist;
	काष्ठा page **pages = pagelistinfo->pages;
	अचिन्हित पूर्णांक num_pages = pagelistinfo->num_pages;

	vchiq_log_trace(vchiq_arm_log_level, "%s - %pK, %d",
			__func__, pagelistinfo->pagelist, actual);

	/*
	 * NOTE: dma_unmap_sg must be called beक्रमe the
	 * cpu can touch any of the data/pages.
	 */
	dma_unmap_sg(g_dev, pagelistinfo->scatterlist,
		     pagelistinfo->num_pages, pagelistinfo->dma_dir);
	pagelistinfo->scatterlist_mapped = 0;

	/* Deal with any partial cache lines (fragments) */
	अगर (pagelist->type >= PAGELIST_READ_WITH_FRAGMENTS) अणु
		अक्षर *fragments = g_fragments_base +
			(pagelist->type - PAGELIST_READ_WITH_FRAGMENTS) *
			g_fragments_size;
		पूर्णांक head_bytes, tail_bytes;

		head_bytes = (g_cache_line_size - pagelist->offset) &
			(g_cache_line_size - 1);
		tail_bytes = (pagelist->offset + actual) &
			(g_cache_line_size - 1);

		अगर ((actual >= 0) && (head_bytes != 0)) अणु
			अगर (head_bytes > actual)
				head_bytes = actual;

			स_नकल((अक्षर *)kmap(pages[0]) +
				pagelist->offset,
				fragments,
				head_bytes);
			kunmap(pages[0]);
		पूर्ण
		अगर ((actual >= 0) && (head_bytes < actual) &&
			(tail_bytes != 0)) अणु
			स_नकल((अक्षर *)kmap(pages[num_pages - 1]) +
				((pagelist->offset + actual) &
				(PAGE_SIZE - 1) & ~(g_cache_line_size - 1)),
				fragments + g_cache_line_size,
				tail_bytes);
			kunmap(pages[num_pages - 1]);
		पूर्ण

		करोwn(&g_मुक्त_fragments_mutex);
		*(अक्षर **)fragments = g_मुक्त_fragments;
		g_मुक्त_fragments = fragments;
		up(&g_मुक्त_fragments_mutex);
		up(&g_मुक्त_fragments_sema);
	पूर्ण

	/* Need to mark all the pages dirty. */
	अगर (pagelist->type != PAGELIST_WRITE &&
	    pagelistinfo->pages_need_release) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < num_pages; i++)
			set_page_dirty(pages[i]);
	पूर्ण

	cleanup_pagelistinfo(pagelistinfo);
पूर्ण
