<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_buf.c
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>

#समावेश "comedidev.h"
#समावेश "comedi_internal.h"

#अगर_घोषित PAGE_KERNEL_NOCACHE
#घोषणा COMEDI_PAGE_PROTECTION		PAGE_KERNEL_NOCACHE
#अन्यथा
#घोषणा COMEDI_PAGE_PROTECTION		PAGE_KERNEL
#पूर्ण_अगर

अटल व्योम comedi_buf_map_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा comedi_buf_map *bm =
		container_of(kref, काष्ठा comedi_buf_map, refcount);
	काष्ठा comedi_buf_page *buf;
	अचिन्हित पूर्णांक i;

	अगर (bm->page_list) अणु
		अगर (bm->dma_dir != DMA_NONE) अणु
			/*
			 * DMA buffer was allocated as a single block.
			 * Address is in page_list[0].
			 */
			buf = &bm->page_list[0];
			dma_मुक्त_coherent(bm->dma_hw_dev,
					  PAGE_SIZE * bm->n_pages,
					  buf->virt_addr, buf->dma_addr);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < bm->n_pages; i++) अणु
				buf = &bm->page_list[i];
				ClearPageReserved(virt_to_page(buf->virt_addr));
				मुक्त_page((अचिन्हित दीर्घ)buf->virt_addr);
			पूर्ण
		पूर्ण
		vमुक्त(bm->page_list);
	पूर्ण
	अगर (bm->dma_dir != DMA_NONE)
		put_device(bm->dma_hw_dev);
	kमुक्त(bm);
पूर्ण

अटल व्योम __comedi_buf_मुक्त(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_buf_map *bm;
	अचिन्हित दीर्घ flags;

	अगर (async->pपुनः_स्मृति_buf) अणु
		अगर (s->async_dma_dir == DMA_NONE)
			vunmap(async->pपुनः_स्मृति_buf);
		async->pपुनः_स्मृति_buf = शून्य;
		async->pपुनः_स्मृति_bufsz = 0;
	पूर्ण

	spin_lock_irqsave(&s->spin_lock, flags);
	bm = async->buf_map;
	async->buf_map = शून्य;
	spin_unlock_irqrestore(&s->spin_lock, flags);
	comedi_buf_map_put(bm);
पूर्ण

अटल काष्ठा comedi_buf_map *
comedi_buf_map_alloc(काष्ठा comedi_device *dev, क्रमागत dma_data_direction dma_dir,
		     अचिन्हित पूर्णांक n_pages)
अणु
	काष्ठा comedi_buf_map *bm;
	काष्ठा comedi_buf_page *buf;
	अचिन्हित पूर्णांक i;

	bm = kzalloc(माप(*bm), GFP_KERNEL);
	अगर (!bm)
		वापस शून्य;

	kref_init(&bm->refcount);
	bm->dma_dir = dma_dir;
	अगर (bm->dma_dir != DMA_NONE) अणु
		/* Need ref to hardware device to मुक्त buffer later. */
		bm->dma_hw_dev = get_device(dev->hw_dev);
	पूर्ण

	bm->page_list = vzalloc(माप(*buf) * n_pages);
	अगर (!bm->page_list)
		जाओ err;

	अगर (bm->dma_dir != DMA_NONE) अणु
		व्योम *virt_addr;
		dma_addr_t dma_addr;

		/*
		 * Currently, the DMA buffer needs to be allocated as a
		 * single block so that it can be mmap()'ed.
		 */
		virt_addr = dma_alloc_coherent(bm->dma_hw_dev,
					       PAGE_SIZE * n_pages, &dma_addr,
					       GFP_KERNEL);
		अगर (!virt_addr)
			जाओ err;

		क्रम (i = 0; i < n_pages; i++) अणु
			buf = &bm->page_list[i];
			buf->virt_addr = virt_addr + (i << PAGE_SHIFT);
			buf->dma_addr = dma_addr + (i << PAGE_SHIFT);
		पूर्ण

		bm->n_pages = i;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < n_pages; i++) अणु
			buf = &bm->page_list[i];
			buf->virt_addr = (व्योम *)get_zeroed_page(GFP_KERNEL);
			अगर (!buf->virt_addr)
				अवरोध;

			SetPageReserved(virt_to_page(buf->virt_addr));
		पूर्ण

		bm->n_pages = i;
		अगर (i < n_pages)
			जाओ err;
	पूर्ण

	वापस bm;

err:
	comedi_buf_map_put(bm);
	वापस शून्य;
पूर्ण

अटल व्योम __comedi_buf_alloc(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित पूर्णांक n_pages)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा page **pages = शून्य;
	काष्ठा comedi_buf_map *bm;
	काष्ठा comedi_buf_page *buf;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_HAS_DMA) && s->async_dma_dir != DMA_NONE) अणु
		dev_err(dev->class_dev,
			"dma buffer allocation not supported\n");
		वापस;
	पूर्ण

	bm = comedi_buf_map_alloc(dev, s->async_dma_dir, n_pages);
	अगर (!bm)
		वापस;

	spin_lock_irqsave(&s->spin_lock, flags);
	async->buf_map = bm;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	अगर (bm->dma_dir != DMA_NONE) अणु
		/*
		 * DMA buffer was allocated as a single block.
		 * Address is in page_list[0].
		 */
		buf = &bm->page_list[0];
		async->pपुनः_स्मृति_buf = buf->virt_addr;
	पूर्ण अन्यथा अणु
		pages = vदो_स्मृति(माप(काष्ठा page *) * n_pages);
		अगर (!pages)
			वापस;

		क्रम (i = 0; i < n_pages; i++) अणु
			buf = &bm->page_list[i];
			pages[i] = virt_to_page(buf->virt_addr);
		पूर्ण

		/* vmap the pages to pपुनः_स्मृति_buf */
		async->pपुनः_स्मृति_buf = vmap(pages, n_pages, VM_MAP,
					   COMEDI_PAGE_PROTECTION);

		vमुक्त(pages);
	पूर्ण
पूर्ण

व्योम comedi_buf_map_get(काष्ठा comedi_buf_map *bm)
अणु
	अगर (bm)
		kref_get(&bm->refcount);
पूर्ण

पूर्णांक comedi_buf_map_put(काष्ठा comedi_buf_map *bm)
अणु
	अगर (bm)
		वापस kref_put(&bm->refcount, comedi_buf_map_kref_release);
	वापस 1;
पूर्ण

/* helper क्रम "access" vm operation */
पूर्णांक comedi_buf_map_access(काष्ठा comedi_buf_map *bm, अचिन्हित दीर्घ offset,
			  व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	अचिन्हित पूर्णांक pgoff = offset_in_page(offset);
	अचिन्हित दीर्घ pg = offset >> PAGE_SHIFT;
	पूर्णांक करोne = 0;

	जबतक (करोne < len && pg < bm->n_pages) अणु
		पूर्णांक l = min_t(पूर्णांक, len - करोne, PAGE_SIZE - pgoff);
		व्योम *b = bm->page_list[pg].virt_addr + pgoff;

		अगर (ग_लिखो)
			स_नकल(b, buf, l);
		अन्यथा
			स_नकल(buf, b, l);
		buf += l;
		करोne += l;
		pg++;
		pgoff = 0;
	पूर्ण
	वापस करोne;
पूर्ण

/* वापसs s->async->buf_map and increments its kref refcount */
काष्ठा comedi_buf_map *
comedi_buf_map_from_subdev_get(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_buf_map *bm = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (!async)
		वापस शून्य;

	spin_lock_irqsave(&s->spin_lock, flags);
	bm = async->buf_map;
	/* only want it अगर buffer pages allocated */
	अगर (bm && bm->n_pages)
		comedi_buf_map_get(bm);
	अन्यथा
		bm = शून्य;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	वापस bm;
पूर्ण

bool comedi_buf_is_mmapped(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_buf_map *bm = s->async->buf_map;

	वापस bm && (kref_पढ़ो(&bm->refcount) > 1);
पूर्ण

पूर्णांक comedi_buf_alloc(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     अचिन्हित दीर्घ new_size)
अणु
	काष्ठा comedi_async *async = s->async;

	lockdep_निश्चित_held(&dev->mutex);

	/* Round up new_size to multiple of PAGE_SIZE */
	new_size = (new_size + PAGE_SIZE - 1) & PAGE_MASK;

	/* अगर no change is required, करो nothing */
	अगर (async->pपुनः_स्मृति_buf && async->pपुनः_स्मृति_bufsz == new_size)
		वापस 0;

	/* deallocate old buffer */
	__comedi_buf_मुक्त(dev, s);

	/* allocate new buffer */
	अगर (new_size) अणु
		अचिन्हित पूर्णांक n_pages = new_size >> PAGE_SHIFT;

		__comedi_buf_alloc(dev, s, n_pages);

		अगर (!async->pपुनः_स्मृति_buf) अणु
			/* allocation failed */
			__comedi_buf_मुक्त(dev, s);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	async->pपुनः_स्मृति_bufsz = new_size;

	वापस 0;
पूर्ण

व्योम comedi_buf_reset(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;

	async->buf_ग_लिखो_alloc_count = 0;
	async->buf_ग_लिखो_count = 0;
	async->buf_पढ़ो_alloc_count = 0;
	async->buf_पढ़ो_count = 0;

	async->buf_ग_लिखो_ptr = 0;
	async->buf_पढ़ो_ptr = 0;

	async->cur_chan = 0;
	async->scans_करोne = 0;
	async->scan_progress = 0;
	async->munge_chan = 0;
	async->munge_count = 0;
	async->munge_ptr = 0;

	async->events = 0;
पूर्ण

अटल अचिन्हित पूर्णांक comedi_buf_ग_लिखो_n_unalloc(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक मुक्त_end = async->buf_पढ़ो_count + async->pपुनः_स्मृति_bufsz;

	वापस मुक्त_end - async->buf_ग_लिखो_alloc_count;
पूर्ण

अचिन्हित पूर्णांक comedi_buf_ग_लिखो_n_available(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक मुक्त_end = async->buf_पढ़ो_count + async->pपुनः_स्मृति_bufsz;

	वापस मुक्त_end - async->buf_ग_लिखो_count;
पूर्ण

/**
 * comedi_buf_ग_लिखो_alloc() - Reserve buffer space क्रम writing
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to reserve in bytes.
 *
 * Reserve up to @nbytes bytes of space to be written in the COMEDI acquisition
 * data buffer associated with the subdevice.  The amount reserved is limited
 * by the space available.
 *
 * Return: The amount of space reserved in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_alloc(काष्ठा comedi_subdevice *s,
				    अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक unalloc = comedi_buf_ग_लिखो_n_unalloc(s);

	अगर (nbytes > unalloc)
		nbytes = unalloc;

	async->buf_ग_लिखो_alloc_count += nbytes;

	/*
	 * ensure the async buffer 'counts' are पढ़ो and updated
	 * beक्रमe we ग_लिखो data to the ग_लिखो-alloc'ed buffer space
	 */
	smp_mb();

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_ग_लिखो_alloc);

/*
 * munging is applied to data by core as it passes between user
 * and kernel space
 */
अटल अचिन्हित पूर्णांक comedi_buf_munge(काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक num_bytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक count = 0;
	स्थिर अचिन्हित पूर्णांक num_sample_bytes = comedi_bytes_per_sample(s);

	अगर (!s->munge || (async->cmd.flags & CMDF_RAWDATA)) अणु
		async->munge_count += num_bytes;
		वापस num_bytes;
	पूर्ण

	/* करोn't munge partial samples */
	num_bytes -= num_bytes % num_sample_bytes;
	जबतक (count < num_bytes) अणु
		पूर्णांक block_size = num_bytes - count;
		अचिन्हित पूर्णांक buf_end;

		buf_end = async->pपुनः_स्मृति_bufsz - async->munge_ptr;
		अगर (block_size > buf_end)
			block_size = buf_end;

		s->munge(s->device, s,
			 async->pपुनः_स्मृति_buf + async->munge_ptr,
			 block_size, async->munge_chan);

		/*
		 * ensure data is munged in buffer beक्रमe the
		 * async buffer munge_count is incremented
		 */
		smp_wmb();

		async->munge_chan += block_size / num_sample_bytes;
		async->munge_chan %= async->cmd.chanlist_len;
		async->munge_count += block_size;
		async->munge_ptr += block_size;
		async->munge_ptr %= async->pपुनः_स्मृति_bufsz;
		count += block_size;
	पूर्ण

	वापस count;
पूर्ण

अचिन्हित पूर्णांक comedi_buf_ग_लिखो_n_allocated(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;

	वापस async->buf_ग_लिखो_alloc_count - async->buf_ग_लिखो_count;
पूर्ण

/**
 * comedi_buf_ग_लिखो_मुक्त() - Free buffer space after it is written
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to मुक्त in bytes.
 *
 * Free up to @nbytes bytes of space previously reserved क्रम writing in the
 * COMEDI acquisition data buffer associated with the subdevice.  The amount of
 * space मुक्तd is limited to the amount that was reserved.  The मुक्तd space is
 * assumed to have been filled with sample data by the ग_लिखोr.
 *
 * If the samples in the मुक्तd space need to be "munged", करो so here.  The
 * मुक्तd space becomes available क्रम allocation by the पढ़ोer.
 *
 * Return: The amount of space मुक्तd in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_मुक्त(काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक allocated = comedi_buf_ग_लिखो_n_allocated(s);

	अगर (nbytes > allocated)
		nbytes = allocated;

	async->buf_ग_लिखो_count += nbytes;
	async->buf_ग_लिखो_ptr += nbytes;
	comedi_buf_munge(s, async->buf_ग_लिखो_count - async->munge_count);
	अगर (async->buf_ग_लिखो_ptr >= async->pपुनः_स्मृति_bufsz)
		async->buf_ग_लिखो_ptr %= async->pपुनः_स्मृति_bufsz;

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_ग_लिखो_मुक्त);

/**
 * comedi_buf_पढ़ो_n_available() - Determine amount of पढ़ोable buffer space
 * @s: COMEDI subdevice.
 *
 * Determine the amount of पढ़ोable buffer space in the COMEDI acquisition data
 * buffer associated with the subdevice.  The पढ़ोable buffer space is that
 * which has been मुक्तd by the ग_लिखोr and "munged" to the sample data क्रमmat
 * expected by COMEDI अगर necessary.
 *
 * Return: The amount of पढ़ोable buffer space.
 */
अचिन्हित पूर्णांक comedi_buf_पढ़ो_n_available(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक num_bytes;

	अगर (!async)
		वापस 0;

	num_bytes = async->munge_count - async->buf_पढ़ो_count;

	/*
	 * ensure the async buffer 'counts' are पढ़ो beक्रमe we
	 * attempt to पढ़ो data from the buffer
	 */
	smp_rmb();

	वापस num_bytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_पढ़ो_n_available);

/**
 * comedi_buf_पढ़ो_alloc() - Reserve buffer space क्रम पढ़ोing
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to reserve in bytes.
 *
 * Reserve up to @nbytes bytes of previously written and "munged" buffer space
 * क्रम पढ़ोing in the COMEDI acquisition data buffer associated with the
 * subdevice.  The amount reserved is limited to the space available.  The
 * पढ़ोer can पढ़ो from the reserved space and then मुक्त it.  A पढ़ोer is also
 * allowed to पढ़ो from the space beक्रमe reserving it as दीर्घ as it determines
 * the amount of पढ़ोable data available, but the space needs to be marked as
 * reserved beक्रमe it can be मुक्तd.
 *
 * Return: The amount of space reserved in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_पढ़ो_alloc(काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक available;

	available = async->munge_count - async->buf_पढ़ो_alloc_count;
	अगर (nbytes > available)
		nbytes = available;

	async->buf_पढ़ो_alloc_count += nbytes;

	/*
	 * ensure the async buffer 'counts' are पढ़ो beक्रमe we
	 * attempt to पढ़ो data from the पढ़ो-alloc'ed buffer space
	 */
	smp_rmb();

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_पढ़ो_alloc);

अटल अचिन्हित पूर्णांक comedi_buf_पढ़ो_n_allocated(काष्ठा comedi_async *async)
अणु
	वापस async->buf_पढ़ो_alloc_count - async->buf_पढ़ो_count;
पूर्ण

/**
 * comedi_buf_पढ़ो_मुक्त() - Free buffer space after it has been पढ़ो
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to मुक्त in bytes.
 *
 * Free up to @nbytes bytes of buffer space previously reserved क्रम पढ़ोing in
 * the COMEDI acquisition data buffer associated with the subdevice.  The
 * amount of space मुक्तd is limited to the amount that was reserved.
 *
 * The मुक्तd space becomes available क्रम allocation by the ग_लिखोr.
 *
 * Return: The amount of space मुक्तd in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_पढ़ो_मुक्त(काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक allocated;

	/*
	 * ensure data has been पढ़ो out of buffer beक्रमe
	 * the async पढ़ो count is incremented
	 */
	smp_mb();

	allocated = comedi_buf_पढ़ो_n_allocated(async);
	अगर (nbytes > allocated)
		nbytes = allocated;

	async->buf_पढ़ो_count += nbytes;
	async->buf_पढ़ो_ptr += nbytes;
	async->buf_पढ़ो_ptr %= async->pपुनः_स्मृति_bufsz;
	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_पढ़ो_मुक्त);

अटल व्योम comedi_buf_स_नकल_to(काष्ठा comedi_subdevice *s,
				 स्थिर व्योम *data, अचिन्हित पूर्णांक num_bytes)
अणु
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक ग_लिखो_ptr = async->buf_ग_लिखो_ptr;

	जबतक (num_bytes) अणु
		अचिन्हित पूर्णांक block_size;

		अगर (ग_लिखो_ptr + num_bytes > async->pपुनः_स्मृति_bufsz)
			block_size = async->pपुनः_स्मृति_bufsz - ग_लिखो_ptr;
		अन्यथा
			block_size = num_bytes;

		स_नकल(async->pपुनः_स्मृति_buf + ग_लिखो_ptr, data, block_size);

		data += block_size;
		num_bytes -= block_size;

		ग_लिखो_ptr = 0;
	पूर्ण
पूर्ण

अटल व्योम comedi_buf_स_नकल_from(काष्ठा comedi_subdevice *s,
				   व्योम *dest, अचिन्हित पूर्णांक nbytes)
अणु
	व्योम *src;
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक पढ़ो_ptr = async->buf_पढ़ो_ptr;

	जबतक (nbytes) अणु
		अचिन्हित पूर्णांक block_size;

		src = async->pपुनः_स्मृति_buf + पढ़ो_ptr;

		अगर (nbytes >= async->pपुनः_स्मृति_bufsz - पढ़ो_ptr)
			block_size = async->pपुनः_स्मृति_bufsz - पढ़ो_ptr;
		अन्यथा
			block_size = nbytes;

		स_नकल(dest, src, block_size);
		nbytes -= block_size;
		dest += block_size;
		पढ़ो_ptr = 0;
	पूर्ण
पूर्ण

/**
 * comedi_buf_ग_लिखो_samples() - Write sample data to COMEDI buffer
 * @s: COMEDI subdevice.
 * @data: Poपूर्णांकer to source samples.
 * @nsamples: Number of samples to ग_लिखो.
 *
 * Write up to @nsamples samples to the COMEDI acquisition data buffer
 * associated with the subdevice, mark it as written and update the
 * acquisition scan progress.  If there is not enough room क्रम the specअगरied
 * number of samples, the number of samples written is limited to the number
 * that will fit and the %COMEDI_CB_OVERFLOW event flag is set to cause the
 * acquisition to terminate with an overrun error.  Set the %COMEDI_CB_BLOCK
 * event flag अगर any samples are written to cause रुकोing tasks to be woken
 * when the event flags are processed.
 *
 * Return: The amount of data written in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_samples(काष्ठा comedi_subdevice *s,
				      स्थिर व्योम *data, अचिन्हित पूर्णांक nsamples)
अणु
	अचिन्हित पूर्णांक max_samples;
	अचिन्हित पूर्णांक nbytes;

	/*
	 * Make sure there is enough room in the buffer क्रम all the samples.
	 * If not, clamp the nsamples to the number that will fit, flag the
	 * buffer overrun and add the samples that fit.
	 */
	max_samples = comedi_bytes_to_samples(s, comedi_buf_ग_लिखो_n_unalloc(s));
	अगर (nsamples > max_samples) अणु
		dev_warn(s->device->class_dev, "buffer overrun\n");
		s->async->events |= COMEDI_CB_OVERFLOW;
		nsamples = max_samples;
	पूर्ण

	अगर (nsamples == 0)
		वापस 0;

	nbytes = comedi_buf_ग_लिखो_alloc(s,
					comedi_samples_to_bytes(s, nsamples));
	comedi_buf_स_नकल_to(s, data, nbytes);
	comedi_buf_ग_लिखो_मुक्त(s, nbytes);
	comedi_inc_scan_progress(s, nbytes);
	s->async->events |= COMEDI_CB_BLOCK;

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_ग_लिखो_samples);

/**
 * comedi_buf_पढ़ो_samples() - Read sample data from COMEDI buffer
 * @s: COMEDI subdevice.
 * @data: Poपूर्णांकer to destination.
 * @nsamples: Maximum number of samples to पढ़ो.
 *
 * Read up to @nsamples samples from the COMEDI acquisition data buffer
 * associated with the subdevice, mark it as पढ़ो and update the acquisition
 * scan progress.  Limit the number of samples पढ़ो to the number available.
 * Set the %COMEDI_CB_BLOCK event flag अगर any samples are पढ़ो to cause रुकोing
 * tasks to be woken when the event flags are processed.
 *
 * Return: The amount of data पढ़ो in bytes.
 */
अचिन्हित पूर्णांक comedi_buf_पढ़ो_samples(काष्ठा comedi_subdevice *s,
				     व्योम *data, अचिन्हित पूर्णांक nsamples)
अणु
	अचिन्हित पूर्णांक max_samples;
	अचिन्हित पूर्णांक nbytes;

	/* clamp nsamples to the number of full samples available */
	max_samples = comedi_bytes_to_samples(s,
					      comedi_buf_पढ़ो_n_available(s));
	अगर (nsamples > max_samples)
		nsamples = max_samples;

	अगर (nsamples == 0)
		वापस 0;

	nbytes = comedi_buf_पढ़ो_alloc(s,
				       comedi_samples_to_bytes(s, nsamples));
	comedi_buf_स_नकल_from(s, data, nbytes);
	comedi_buf_पढ़ो_मुक्त(s, nbytes);
	comedi_inc_scan_progress(s, nbytes);
	s->async->events |= COMEDI_CB_BLOCK;

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_buf_पढ़ो_samples);
