<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ps3vram - Use extra PS3 video ram as block device.
 *
 * Copyright 2009 Sony Corporation
 *
 * Based on the MTD ps3vram driver, which is
 * Copyright (c) 2007-2008 Jim Paris <jim@jtan.com>
 * Added support RSX DMA Vivien Chappelier <vivien.chappelier@मुक्त.fr>
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cell-regs.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/ps3gpu.h>


#घोषणा DEVICE_NAME		"ps3vram"


#घोषणा XDR_BUF_SIZE (2 * 1024 * 1024) /* XDR buffer (must be 1MiB aligned) */
#घोषणा XDR_IOIF 0x0c000000

#घोषणा FIFO_BASE XDR_IOIF
#घोषणा FIFO_SIZE (64 * 1024)

#घोषणा DMA_PAGE_SIZE (4 * 1024)

#घोषणा CACHE_PAGE_SIZE (256 * 1024)
#घोषणा CACHE_PAGE_COUNT ((XDR_BUF_SIZE - FIFO_SIZE) / CACHE_PAGE_SIZE)

#घोषणा CACHE_OFFSET CACHE_PAGE_SIZE
#घोषणा FIFO_OFFSET 0

#घोषणा CTRL_PUT 0x10
#घोषणा CTRL_GET 0x11
#घोषणा CTRL_TOP 0x15

#घोषणा UPLOAD_SUBCH	1
#घोषणा DOWNLOAD_SUBCH	2

#घोषणा NV_MEMORY_TO_MEMORY_FORMAT_OFFSET_IN	0x0000030c
#घोषणा NV_MEMORY_TO_MEMORY_FORMAT_NOTIFY	0x00000104

#घोषणा CACHE_PAGE_PRESENT 1
#घोषणा CACHE_PAGE_सूचीTY   2

काष्ठा ps3vram_tag अणु
	अचिन्हित पूर्णांक address;
	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा ps3vram_cache अणु
	अचिन्हित पूर्णांक page_count;
	अचिन्हित पूर्णांक page_size;
	काष्ठा ps3vram_tag *tags;
	अचिन्हित पूर्णांक hit;
	अचिन्हित पूर्णांक miss;
पूर्ण;

काष्ठा ps3vram_priv अणु
	काष्ठा request_queue *queue;
	काष्ठा gendisk *gendisk;

	u64 size;

	u64 memory_handle;
	u64 context_handle;
	u32 __iomem *ctrl;
	व्योम __iomem *reports;
	u8 *xdr_buf;

	u32 *fअगरo_base;
	u32 *fअगरo_ptr;

	काष्ठा ps3vram_cache cache;

	spinlock_t lock;	/* protecting list of bios */
	काष्ठा bio_list list;
पूर्ण;


अटल पूर्णांक ps3vram_major;

#घोषणा DMA_NOTIFIER_HANDLE_BASE 0x66604200 /* first DMA notअगरier handle */
#घोषणा DMA_NOTIFIER_OFFSET_BASE 0x1000     /* first DMA notअगरier offset */
#घोषणा DMA_NOTIFIER_SIZE        0x40
#घोषणा NOTIFIER 7	/* notअगरier used क्रम completion report */

अटल अक्षर *size = "256M";
module_param(size, अक्षरp, 0);
MODULE_PARM_DESC(size, "memory size");

अटल u32 __iomem *ps3vram_get_notअगरier(व्योम __iomem *reports, पूर्णांक notअगरier)
अणु
	वापस reports + DMA_NOTIFIER_OFFSET_BASE +
	       DMA_NOTIFIER_SIZE * notअगरier;
पूर्ण

अटल व्योम ps3vram_notअगरier_reset(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	u32 __iomem *notअगरy = ps3vram_get_notअगरier(priv->reports, NOTIFIER);
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		ioग_लिखो32be(0xffffffff, notअगरy + i);
पूर्ण

अटल पूर्णांक ps3vram_notअगरier_रुको(काष्ठा ps3_प्रणाली_bus_device *dev,
				 अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	u32 __iomem *notअगरy = ps3vram_get_notअगरier(priv->reports, NOTIFIER);
	अचिन्हित दीर्घ समयout;

	क्रम (समयout = 20; समयout; समयout--) अणु
		अगर (!ioपढ़ो32be(notअगरy + 3))
			वापस 0;
		udelay(10);
	पूर्ण

	समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);

	करो अणु
		अगर (!ioपढ़ो32be(notअगरy + 3))
			वापस 0;
		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम ps3vram_init_ring(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	ioग_लिखो32be(FIFO_BASE + FIFO_OFFSET, priv->ctrl + CTRL_PUT);
	ioग_लिखो32be(FIFO_BASE + FIFO_OFFSET, priv->ctrl + CTRL_GET);
पूर्ण

अटल पूर्णांक ps3vram_रुको_ring(काष्ठा ps3_प्रणाली_bus_device *dev,
			     अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);

	करो अणु
		अगर (ioपढ़ो32be(priv->ctrl + CTRL_PUT) == ioपढ़ो32be(priv->ctrl + CTRL_GET))
			वापस 0;
		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	dev_warn(&dev->core, "FIFO timeout (%08x/%08x/%08x)\n",
		 ioपढ़ो32be(priv->ctrl + CTRL_PUT), ioपढ़ो32be(priv->ctrl + CTRL_GET),
		 ioपढ़ो32be(priv->ctrl + CTRL_TOP));

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम ps3vram_out_ring(काष्ठा ps3vram_priv *priv, u32 data)
अणु
	*(priv->fअगरo_ptr)++ = data;
पूर्ण

अटल व्योम ps3vram_begin_ring(काष्ठा ps3vram_priv *priv, u32 chan, u32 tag,
			       u32 size)
अणु
	ps3vram_out_ring(priv, (size << 18) | (chan << 13) | tag);
पूर्ण

अटल व्योम ps3vram_शुरुआत_ring(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	पूर्णांक status;

	ps3vram_out_ring(priv, 0x20000000 | (FIFO_BASE + FIFO_OFFSET));

	ioग_लिखो32be(FIFO_BASE + FIFO_OFFSET, priv->ctrl + CTRL_PUT);

	/* asking the HV क्रम a blit will kick the FIFO */
	status = lv1_gpu_fb_blit(priv->context_handle, 0, 0, 0, 0);
	अगर (status)
		dev_err(&dev->core, "%s: lv1_gpu_fb_blit failed %d\n",
			__func__, status);

	priv->fअगरo_ptr = priv->fअगरo_base;
पूर्ण

अटल व्योम ps3vram_fire_ring(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	पूर्णांक status;

	mutex_lock(&ps3_gpu_mutex);

	ioग_लिखो32be(FIFO_BASE + FIFO_OFFSET + (priv->fअगरo_ptr - priv->fअगरo_base)
		* माप(u32), priv->ctrl + CTRL_PUT);

	/* asking the HV क्रम a blit will kick the FIFO */
	status = lv1_gpu_fb_blit(priv->context_handle, 0, 0, 0, 0);
	अगर (status)
		dev_err(&dev->core, "%s: lv1_gpu_fb_blit failed %d\n",
			__func__, status);

	अगर ((priv->fअगरo_ptr - priv->fअगरo_base) * माप(u32) >
	    FIFO_SIZE - 1024) अणु
		dev_dbg(&dev->core, "FIFO full, rewinding\n");
		ps3vram_रुको_ring(dev, 200);
		ps3vram_शुरुआत_ring(dev);
	पूर्ण

	mutex_unlock(&ps3_gpu_mutex);
पूर्ण

अटल व्योम ps3vram_bind(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	ps3vram_begin_ring(priv, UPLOAD_SUBCH, 0, 1);
	ps3vram_out_ring(priv, 0x31337303);
	ps3vram_begin_ring(priv, UPLOAD_SUBCH, 0x180, 3);
	ps3vram_out_ring(priv, DMA_NOTIFIER_HANDLE_BASE + NOTIFIER);
	ps3vram_out_ring(priv, 0xfeed0001);	/* DMA प्रणाली RAM instance */
	ps3vram_out_ring(priv, 0xfeed0000);     /* DMA video RAM instance */

	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH, 0, 1);
	ps3vram_out_ring(priv, 0x3137c0de);
	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH, 0x180, 3);
	ps3vram_out_ring(priv, DMA_NOTIFIER_HANDLE_BASE + NOTIFIER);
	ps3vram_out_ring(priv, 0xfeed0000);	/* DMA video RAM instance */
	ps3vram_out_ring(priv, 0xfeed0001);	/* DMA प्रणाली RAM instance */

	ps3vram_fire_ring(dev);
पूर्ण

अटल पूर्णांक ps3vram_upload(काष्ठा ps3_प्रणाली_bus_device *dev,
			  अचिन्हित पूर्णांक src_offset, अचिन्हित पूर्णांक dst_offset,
			  पूर्णांक len, पूर्णांक count)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	ps3vram_begin_ring(priv, UPLOAD_SUBCH,
			   NV_MEMORY_TO_MEMORY_FORMAT_OFFSET_IN, 8);
	ps3vram_out_ring(priv, XDR_IOIF + src_offset);
	ps3vram_out_ring(priv, dst_offset);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, count);
	ps3vram_out_ring(priv, (1 << 8) | 1);
	ps3vram_out_ring(priv, 0);

	ps3vram_notअगरier_reset(dev);
	ps3vram_begin_ring(priv, UPLOAD_SUBCH,
			   NV_MEMORY_TO_MEMORY_FORMAT_NOTIFY, 1);
	ps3vram_out_ring(priv, 0);
	ps3vram_begin_ring(priv, UPLOAD_SUBCH, 0x100, 1);
	ps3vram_out_ring(priv, 0);
	ps3vram_fire_ring(dev);
	अगर (ps3vram_notअगरier_रुको(dev, 200) < 0) अणु
		dev_warn(&dev->core, "%s: Notifier timeout\n", __func__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3vram_करोwnload(काष्ठा ps3_प्रणाली_bus_device *dev,
			    अचिन्हित पूर्णांक src_offset, अचिन्हित पूर्णांक dst_offset,
			    पूर्णांक len, पूर्णांक count)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH,
			   NV_MEMORY_TO_MEMORY_FORMAT_OFFSET_IN, 8);
	ps3vram_out_ring(priv, src_offset);
	ps3vram_out_ring(priv, XDR_IOIF + dst_offset);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, len);
	ps3vram_out_ring(priv, count);
	ps3vram_out_ring(priv, (1 << 8) | 1);
	ps3vram_out_ring(priv, 0);

	ps3vram_notअगरier_reset(dev);
	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH,
			   NV_MEMORY_TO_MEMORY_FORMAT_NOTIFY, 1);
	ps3vram_out_ring(priv, 0);
	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH, 0x100, 1);
	ps3vram_out_ring(priv, 0);
	ps3vram_fire_ring(dev);
	अगर (ps3vram_notअगरier_रुको(dev, 200) < 0) अणु
		dev_warn(&dev->core, "%s: Notifier timeout\n", __func__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ps3vram_cache_evict(काष्ठा ps3_प्रणाली_bus_device *dev, पूर्णांक entry)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा ps3vram_cache *cache = &priv->cache;

	अगर (!(cache->tags[entry].flags & CACHE_PAGE_सूचीTY))
		वापस;

	dev_dbg(&dev->core, "Flushing %d: 0x%08x\n", entry,
		cache->tags[entry].address);
	अगर (ps3vram_upload(dev, CACHE_OFFSET + entry * cache->page_size,
			   cache->tags[entry].address, DMA_PAGE_SIZE,
			   cache->page_size / DMA_PAGE_SIZE) < 0) अणु
		dev_err(&dev->core,
			"Failed to upload from 0x%x to " "0x%x size 0x%x\n",
			entry * cache->page_size, cache->tags[entry].address,
			cache->page_size);
	पूर्ण
	cache->tags[entry].flags &= ~CACHE_PAGE_सूचीTY;
पूर्ण

अटल व्योम ps3vram_cache_load(काष्ठा ps3_प्रणाली_bus_device *dev, पूर्णांक entry,
			       अचिन्हित पूर्णांक address)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा ps3vram_cache *cache = &priv->cache;

	dev_dbg(&dev->core, "Fetching %d: 0x%08x\n", entry, address);
	अगर (ps3vram_करोwnload(dev, address,
			     CACHE_OFFSET + entry * cache->page_size,
			     DMA_PAGE_SIZE,
			     cache->page_size / DMA_PAGE_SIZE) < 0) अणु
		dev_err(&dev->core,
			"Failed to download from 0x%x to 0x%x size 0x%x\n",
			address, entry * cache->page_size, cache->page_size);
	पूर्ण

	cache->tags[entry].address = address;
	cache->tags[entry].flags |= CACHE_PAGE_PRESENT;
पूर्ण


अटल व्योम ps3vram_cache_flush(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा ps3vram_cache *cache = &priv->cache;
	पूर्णांक i;

	dev_dbg(&dev->core, "FLUSH\n");
	क्रम (i = 0; i < cache->page_count; i++) अणु
		ps3vram_cache_evict(dev, i);
		cache->tags[i].flags = 0;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ps3vram_cache_match(काष्ठा ps3_प्रणाली_bus_device *dev,
					loff_t address)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा ps3vram_cache *cache = &priv->cache;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक offset;
	पूर्णांक i;
	अटल पूर्णांक counter;

	offset = (अचिन्हित पूर्णांक) (address & (cache->page_size - 1));
	base = (अचिन्हित पूर्णांक) (address - offset);

	/* fully associative check */
	क्रम (i = 0; i < cache->page_count; i++) अणु
		अगर ((cache->tags[i].flags & CACHE_PAGE_PRESENT) &&
		    cache->tags[i].address == base) अणु
			cache->hit++;
			dev_dbg(&dev->core, "Found entry %d: 0x%08x\n", i,
				cache->tags[i].address);
			वापस i;
		पूर्ण
	पूर्ण

	/* choose a अक्रमom entry */
	i = (jअगरfies + (counter++)) % cache->page_count;
	dev_dbg(&dev->core, "Using entry %d\n", i);

	ps3vram_cache_evict(dev, i);
	ps3vram_cache_load(dev, i, base);

	cache->miss++;
	वापस i;
पूर्ण

अटल पूर्णांक ps3vram_cache_init(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	priv->cache.page_count = CACHE_PAGE_COUNT;
	priv->cache.page_size = CACHE_PAGE_SIZE;
	priv->cache.tags = kसुस्मृति(CACHE_PAGE_COUNT,
				   माप(काष्ठा ps3vram_tag),
				   GFP_KERNEL);
	अगर (!priv->cache.tags)
		वापस -ENOMEM;

	dev_info(&dev->core, "Created ram cache: %d entries, %d KiB each\n",
		CACHE_PAGE_COUNT, CACHE_PAGE_SIZE / 1024);

	वापस 0;
पूर्ण

अटल व्योम ps3vram_cache_cleanup(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	ps3vram_cache_flush(dev);
	kमुक्त(priv->cache.tags);
पूर्ण

अटल blk_status_t ps3vram_पढ़ो(काष्ठा ps3_प्रणाली_bus_device *dev, loff_t from,
			माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	अचिन्हित पूर्णांक cached, count;

	dev_dbg(&dev->core, "%s: from=0x%08x len=0x%zx\n", __func__,
		(अचिन्हित पूर्णांक)from, len);

	अगर (from >= priv->size)
		वापस BLK_STS_IOERR;

	अगर (len > priv->size - from)
		len = priv->size - from;

	/* Copy from vram to buf */
	count = len;
	जबतक (count) अणु
		अचिन्हित पूर्णांक offset, avail;
		अचिन्हित पूर्णांक entry;

		offset = (अचिन्हित पूर्णांक) (from & (priv->cache.page_size - 1));
		avail  = priv->cache.page_size - offset;

		entry = ps3vram_cache_match(dev, from);
		cached = CACHE_OFFSET + entry * priv->cache.page_size + offset;

		dev_dbg(&dev->core, "%s: from=%08x cached=%08x offset=%08x "
			"avail=%08x count=%08x\n", __func__,
			(अचिन्हित पूर्णांक)from, cached, offset, avail, count);

		अगर (avail > count)
			avail = count;
		स_नकल(buf, priv->xdr_buf + cached, avail);

		buf += avail;
		count -= avail;
		from += avail;
	पूर्ण

	*retlen = len;
	वापस 0;
पूर्ण

अटल blk_status_t ps3vram_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev, loff_t to,
			 माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	अचिन्हित पूर्णांक cached, count;

	अगर (to >= priv->size)
		वापस BLK_STS_IOERR;

	अगर (len > priv->size - to)
		len = priv->size - to;

	/* Copy from buf to vram */
	count = len;
	जबतक (count) अणु
		अचिन्हित पूर्णांक offset, avail;
		अचिन्हित पूर्णांक entry;

		offset = (अचिन्हित पूर्णांक) (to & (priv->cache.page_size - 1));
		avail  = priv->cache.page_size - offset;

		entry = ps3vram_cache_match(dev, to);
		cached = CACHE_OFFSET + entry * priv->cache.page_size + offset;

		dev_dbg(&dev->core, "%s: to=%08x cached=%08x offset=%08x "
			"avail=%08x count=%08x\n", __func__, (अचिन्हित पूर्णांक)to,
			cached, offset, avail, count);

		अगर (avail > count)
			avail = count;
		स_नकल(priv->xdr_buf + cached, buf, avail);

		priv->cache.tags[entry].flags |= CACHE_PAGE_सूचीTY;

		buf += avail;
		count -= avail;
		to += avail;
	पूर्ण

	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक ps3vram_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ps3vram_priv *priv = m->निजी;

	seq_म_लिखो(m, "hit:%u\nmiss:%u\n", priv->cache.hit, priv->cache.miss);
	वापस 0;
पूर्ण

अटल व्योम ps3vram_proc_init(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	काष्ठा proc_dir_entry *pde;

	pde = proc_create_single_data(DEVICE_NAME, 0444, शून्य,
			ps3vram_proc_show, priv);
	अगर (!pde)
		dev_warn(&dev->core, "failed to create /proc entry\n");
पूर्ण

अटल काष्ठा bio *ps3vram_करो_bio(काष्ठा ps3_प्रणाली_bus_device *dev,
				  काष्ठा bio *bio)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	पूर्णांक ग_लिखो = bio_data_dir(bio) == WRITE;
	स्थिर अक्षर *op = ग_लिखो ? "write" : "read";
	loff_t offset = bio->bi_iter.bi_sector << 9;
	blk_status_t error = 0;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	काष्ठा bio *next;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		/* PS3 is ppc64, so we करोn't handle highmem */
		अक्षर *ptr = page_address(bvec.bv_page) + bvec.bv_offset;
		माप_प्रकार len = bvec.bv_len, retlen;

		dev_dbg(&dev->core, "    %s %zu bytes at offset %llu\n", op,
			len, offset);
		अगर (ग_लिखो)
			error = ps3vram_ग_लिखो(dev, offset, len, &retlen, ptr);
		अन्यथा
			error = ps3vram_पढ़ो(dev, offset, len, &retlen, ptr);

		अगर (error) अणु
			dev_err(&dev->core, "%s failed\n", op);
			जाओ out;
		पूर्ण

		अगर (retlen != len) अणु
			dev_err(&dev->core, "Short %s\n", op);
			error = BLK_STS_IOERR;
			जाओ out;
		पूर्ण

		offset += len;
	पूर्ण

	dev_dbg(&dev->core, "%s completed\n", op);

out:
	spin_lock_irq(&priv->lock);
	bio_list_pop(&priv->list);
	next = bio_list_peek(&priv->list);
	spin_unlock_irq(&priv->lock);

	bio->bi_status = error;
	bio_endio(bio);
	वापस next;
पूर्ण

अटल blk_qc_t ps3vram_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);
	पूर्णांक busy;

	dev_dbg(&dev->core, "%s\n", __func__);

	blk_queue_split(&bio);

	spin_lock_irq(&priv->lock);
	busy = !bio_list_empty(&priv->list);
	bio_list_add(&priv->list, bio);
	spin_unlock_irq(&priv->lock);

	अगर (busy)
		वापस BLK_QC_T_NONE;

	करो अणु
		bio = ps3vram_करो_bio(dev, bio);
	पूर्ण जबतक (bio);

	वापस BLK_QC_T_NONE;
पूर्ण

अटल स्थिर काष्ठा block_device_operations ps3vram_fops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= ps3vram_submit_bio,
पूर्ण;

अटल पूर्णांक ps3vram_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv;
	पूर्णांक error, status;
	काष्ठा request_queue *queue;
	काष्ठा gendisk *gendisk;
	u64 ddr_size, ddr_lpar, ctrl_lpar, info_lpar, reports_lpar,
	    reports_size, xdr_lpar;
	अक्षर *rest;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	spin_lock_init(&priv->lock);
	bio_list_init(&priv->list);
	ps3_प्रणाली_bus_set_drvdata(dev, priv);

	/* Allocate XDR buffer (1MiB aligned) */
	priv->xdr_buf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL,
		get_order(XDR_BUF_SIZE));
	अगर (priv->xdr_buf == शून्य) अणु
		dev_err(&dev->core, "Could not allocate XDR buffer\n");
		error = -ENOMEM;
		जाओ fail_मुक्त_priv;
	पूर्ण

	/* Put FIFO at begginning of XDR buffer */
	priv->fअगरo_base = (u32 *) (priv->xdr_buf + FIFO_OFFSET);
	priv->fअगरo_ptr = priv->fअगरo_base;

	/* XXX: Need to खोलो GPU, in हाल ps3fb or snd_ps3 aren't loaded */
	अगर (ps3_खोलो_hv_device(dev)) अणु
		dev_err(&dev->core, "ps3_open_hv_device failed\n");
		error = -EAGAIN;
		जाओ out_मुक्त_xdr_buf;
	पूर्ण

	/* Request memory */
	status = -1;
	ddr_size = ALIGN(memparse(size, &rest), 1024*1024);
	अगर (!ddr_size) अणु
		dev_err(&dev->core, "Specified size is too small\n");
		error = -EINVAL;
		जाओ out_बंद_gpu;
	पूर्ण

	जबतक (ddr_size > 0) अणु
		status = lv1_gpu_memory_allocate(ddr_size, 0, 0, 0, 0,
						 &priv->memory_handle,
						 &ddr_lpar);
		अगर (!status)
			अवरोध;
		ddr_size -= 1024*1024;
	पूर्ण
	अगर (status) अणु
		dev_err(&dev->core, "lv1_gpu_memory_allocate failed %d\n",
			status);
		error = -ENOMEM;
		जाओ out_बंद_gpu;
	पूर्ण

	/* Request context */
	status = lv1_gpu_context_allocate(priv->memory_handle, 0,
					  &priv->context_handle, &ctrl_lpar,
					  &info_lpar, &reports_lpar,
					  &reports_size);
	अगर (status) अणु
		dev_err(&dev->core, "lv1_gpu_context_allocate failed %d\n",
			status);
		error = -ENOMEM;
		जाओ out_मुक्त_memory;
	पूर्ण

	/* Map XDR buffer to RSX */
	xdr_lpar = ps3_mm_phys_to_lpar(__pa(priv->xdr_buf));
	status = lv1_gpu_context_iomap(priv->context_handle, XDR_IOIF,
				       xdr_lpar, XDR_BUF_SIZE,
				       CBE_IOPTE_PP_W | CBE_IOPTE_PP_R |
				       CBE_IOPTE_M);
	अगर (status) अणु
		dev_err(&dev->core, "lv1_gpu_context_iomap failed %d\n",
			status);
		error = -ENOMEM;
		जाओ out_मुक्त_context;
	पूर्ण

	priv->ctrl = ioremap(ctrl_lpar, 64 * 1024);
	अगर (!priv->ctrl) अणु
		dev_err(&dev->core, "ioremap CTRL failed\n");
		error = -ENOMEM;
		जाओ out_unmap_context;
	पूर्ण

	priv->reports = ioremap(reports_lpar, reports_size);
	अगर (!priv->reports) अणु
		dev_err(&dev->core, "ioremap REPORTS failed\n");
		error = -ENOMEM;
		जाओ out_unmap_ctrl;
	पूर्ण

	mutex_lock(&ps3_gpu_mutex);
	ps3vram_init_ring(dev);
	mutex_unlock(&ps3_gpu_mutex);

	priv->size = ddr_size;

	ps3vram_bind(dev);

	mutex_lock(&ps3_gpu_mutex);
	error = ps3vram_रुको_ring(dev, 100);
	mutex_unlock(&ps3_gpu_mutex);
	अगर (error < 0) अणु
		dev_err(&dev->core, "Failed to initialize channels\n");
		error = -ETIMEDOUT;
		जाओ out_unmap_reports;
	पूर्ण

	error = ps3vram_cache_init(dev);
	अगर (error < 0) अणु
		जाओ out_unmap_reports;
	पूर्ण

	ps3vram_proc_init(dev);

	queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!queue) अणु
		dev_err(&dev->core, "blk_alloc_queue failed\n");
		error = -ENOMEM;
		जाओ out_cache_cleanup;
	पूर्ण

	priv->queue = queue;
	blk_queue_max_segments(queue, BLK_MAX_SEGMENTS);
	blk_queue_max_segment_size(queue, BLK_MAX_SEGMENT_SIZE);
	blk_queue_max_hw_sectors(queue, BLK_SAFE_MAX_SECTORS);

	gendisk = alloc_disk(1);
	अगर (!gendisk) अणु
		dev_err(&dev->core, "alloc_disk failed\n");
		error = -ENOMEM;
		जाओ fail_cleanup_queue;
	पूर्ण

	priv->gendisk = gendisk;
	gendisk->major = ps3vram_major;
	gendisk->first_minor = 0;
	gendisk->fops = &ps3vram_fops;
	gendisk->queue = queue;
	gendisk->निजी_data = dev;
	strlcpy(gendisk->disk_name, DEVICE_NAME, माप(gendisk->disk_name));
	set_capacity(gendisk, priv->size >> 9);

	dev_info(&dev->core, "%s: Using %llu MiB of GPU memory\n",
		 gendisk->disk_name, get_capacity(gendisk) >> 11);

	device_add_disk(&dev->core, gendisk, शून्य);
	वापस 0;

fail_cleanup_queue:
	blk_cleanup_queue(queue);
out_cache_cleanup:
	हटाओ_proc_entry(DEVICE_NAME, शून्य);
	ps3vram_cache_cleanup(dev);
out_unmap_reports:
	iounmap(priv->reports);
out_unmap_ctrl:
	iounmap(priv->ctrl);
out_unmap_context:
	lv1_gpu_context_iomap(priv->context_handle, XDR_IOIF, xdr_lpar,
			      XDR_BUF_SIZE, CBE_IOPTE_M);
out_मुक्त_context:
	lv1_gpu_context_मुक्त(priv->context_handle);
out_मुक्त_memory:
	lv1_gpu_memory_मुक्त(priv->memory_handle);
out_बंद_gpu:
	ps3_बंद_hv_device(dev);
out_मुक्त_xdr_buf:
	मुक्त_pages((अचिन्हित दीर्घ) priv->xdr_buf, get_order(XDR_BUF_SIZE));
fail_मुक्त_priv:
	kमुक्त(priv);
	ps3_प्रणाली_bus_set_drvdata(dev, शून्य);
fail:
	वापस error;
पूर्ण

अटल व्योम ps3vram_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3vram_priv *priv = ps3_प्रणाली_bus_get_drvdata(dev);

	del_gendisk(priv->gendisk);
	put_disk(priv->gendisk);
	blk_cleanup_queue(priv->queue);
	हटाओ_proc_entry(DEVICE_NAME, शून्य);
	ps3vram_cache_cleanup(dev);
	iounmap(priv->reports);
	iounmap(priv->ctrl);
	lv1_gpu_context_iomap(priv->context_handle, XDR_IOIF,
			      ps3_mm_phys_to_lpar(__pa(priv->xdr_buf)),
			      XDR_BUF_SIZE, CBE_IOPTE_M);
	lv1_gpu_context_मुक्त(priv->context_handle);
	lv1_gpu_memory_मुक्त(priv->memory_handle);
	ps3_बंद_hv_device(dev);
	मुक्त_pages((अचिन्हित दीर्घ) priv->xdr_buf, get_order(XDR_BUF_SIZE));
	kमुक्त(priv);
	ps3_प्रणाली_bus_set_drvdata(dev, शून्य);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3vram = अणु
	.match_id	= PS3_MATCH_ID_GPU,
	.match_sub_id	= PS3_MATCH_SUB_ID_GPU_RAMDISK,
	.core.name	= DEVICE_NAME,
	.core.owner	= THIS_MODULE,
	.probe		= ps3vram_probe,
	.हटाओ		= ps3vram_हटाओ,
	.shutकरोwn	= ps3vram_हटाओ,
पूर्ण;


अटल पूर्णांक __init ps3vram_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	error = रेजिस्टर_blkdev(0, DEVICE_NAME);
	अगर (error <= 0) अणु
		pr_err("%s: register_blkdev failed %d\n", DEVICE_NAME, error);
		वापस error;
	पूर्ण
	ps3vram_major = error;

	pr_info("%s: registered block device major %d\n", DEVICE_NAME,
		ps3vram_major);

	error = ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3vram);
	अगर (error)
		unरेजिस्टर_blkdev(ps3vram_major, DEVICE_NAME);

	वापस error;
पूर्ण

अटल व्योम __निकास ps3vram_निकास(व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3vram);
	unरेजिस्टर_blkdev(ps3vram_major, DEVICE_NAME);
पूर्ण

module_init(ps3vram_init);
module_निकास(ps3vram_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 Video RAM Storage Driver");
MODULE_AUTHOR("Sony Corporation");
MODULE_ALIAS(PS3_MODULE_ALIAS_GPU_RAMDISK);
