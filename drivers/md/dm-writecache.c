<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/device-mapper.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/dax.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/libnvdimm.h>

#घोषणा DM_MSG_PREFIX "writecache"

#घोषणा HIGH_WATERMARK			50
#घोषणा LOW_WATERMARK			45
#घोषणा MAX_WRITEBACK_JOBS		0
#घोषणा ENDIO_LATENCY			16
#घोषणा WRITEBACK_LATENCY		64
#घोषणा AUTOCOMMIT_BLOCKS_SSD		65536
#घोषणा AUTOCOMMIT_BLOCKS_PMEM		64
#घोषणा AUTOCOMMIT_MSEC			1000
#घोषणा MAX_AGE_DIV			16
#घोषणा MAX_AGE_UNSPECIFIED		-1UL

#घोषणा BITMAP_GRANULARITY	65536
#अगर BITMAP_GRANULARITY < PAGE_SIZE
#अघोषित BITMAP_GRANULARITY
#घोषणा BITMAP_GRANULARITY	PAGE_SIZE
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ARCH_HAS_PMEM_API) && IS_ENABLED(CONFIG_DAX_DRIVER)
#घोषणा DM_WRITECACHE_HAS_PMEM
#पूर्ण_अगर

#अगर_घोषित DM_WRITECACHE_HAS_PMEM
#घोषणा pmem_assign(dest, src)					\
करो अणु								\
	typeof(dest) uniq = (src);				\
	स_नकल_flushcache(&(dest), &uniq, माप(dest));	\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा pmem_assign(dest, src)	((dest) = (src))
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ARCH_HAS_COPY_MC) && defined(DM_WRITECACHE_HAS_PMEM)
#घोषणा DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
#पूर्ण_अगर

#घोषणा MEMORY_SUPERBLOCK_MAGIC		0x23489321
#घोषणा MEMORY_SUPERBLOCK_VERSION	1

काष्ठा wc_memory_entry अणु
	__le64 original_sector;
	__le64 seq_count;
पूर्ण;

काष्ठा wc_memory_superblock अणु
	जोड़ अणु
		काष्ठा अणु
			__le32 magic;
			__le32 version;
			__le32 block_size;
			__le32 pad;
			__le64 n_blocks;
			__le64 seq_count;
		पूर्ण;
		__le64 padding[8];
	पूर्ण;
	काष्ठा wc_memory_entry entries[];
पूर्ण;

काष्ठा wc_entry अणु
	काष्ठा rb_node rb_node;
	काष्ठा list_head lru;
	अचिन्हित लघु wc_list_contiguous;
	bool ग_लिखो_in_progress
#अगर BITS_PER_LONG == 64
		:1
#पूर्ण_अगर
	;
	अचिन्हित दीर्घ index
#अगर BITS_PER_LONG == 64
		:47
#पूर्ण_अगर
	;
	अचिन्हित दीर्घ age;
#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	uपूर्णांक64_t original_sector;
	uपूर्णांक64_t seq_count;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित DM_WRITECACHE_HAS_PMEM
#घोषणा WC_MODE_PMEM(wc)			((wc)->pmem_mode)
#घोषणा WC_MODE_FUA(wc)				((wc)->ग_लिखोback_fua)
#अन्यथा
#घोषणा WC_MODE_PMEM(wc)			false
#घोषणा WC_MODE_FUA(wc)				false
#पूर्ण_अगर
#घोषणा WC_MODE_SORT_FREELIST(wc)		(!WC_MODE_PMEM(wc))

काष्ठा dm_ग_लिखोcache अणु
	काष्ठा mutex lock;
	काष्ठा list_head lru;
	जोड़ अणु
		काष्ठा list_head मुक्तlist;
		काष्ठा अणु
			काष्ठा rb_root मुक्तtree;
			काष्ठा wc_entry *current_मुक्त;
		पूर्ण;
	पूर्ण;
	काष्ठा rb_root tree;

	माप_प्रकार मुक्तlist_size;
	माप_प्रकार ग_लिखोback_size;
	माप_प्रकार मुक्तlist_high_watermark;
	माप_प्रकार मुक्तlist_low_watermark;
	अचिन्हित दीर्घ max_age;

	अचिन्हित uncommitted_blocks;
	अचिन्हित स्वतःcommit_blocks;
	अचिन्हित max_ग_लिखोback_jobs;

	पूर्णांक error;

	अचिन्हित दीर्घ स्वतःcommit_jअगरfies;
	काष्ठा समयr_list स्वतःcommit_समयr;
	काष्ठा रुको_queue_head मुक्तlist_रुको;

	काष्ठा समयr_list max_age_समयr;

	atomic_t bio_in_progress[2];
	काष्ठा रुको_queue_head bio_in_progress_रुको[2];

	काष्ठा dm_target *ti;
	काष्ठा dm_dev *dev;
	काष्ठा dm_dev *ssd_dev;
	sector_t start_sector;
	व्योम *memory_map;
	uपूर्णांक64_t memory_map_size;
	माप_प्रकार metadata_sectors;
	माप_प्रकार n_blocks;
	uपूर्णांक64_t seq_count;
	sector_t data_device_sectors;
	व्योम *block_start;
	काष्ठा wc_entry *entries;
	अचिन्हित block_size;
	अचिन्हित अक्षर block_size_bits;

	bool pmem_mode:1;
	bool ग_लिखोback_fua:1;

	bool overwrote_committed:1;
	bool memory_vmapped:1;

	bool start_sector_set:1;
	bool high_wm_percent_set:1;
	bool low_wm_percent_set:1;
	bool max_ग_लिखोback_jobs_set:1;
	bool स्वतःcommit_blocks_set:1;
	bool स्वतःcommit_समय_set:1;
	bool max_age_set:1;
	bool ग_लिखोback_fua_set:1;
	bool flush_on_suspend:1;
	bool cleaner:1;
	bool cleaner_set:1;

	अचिन्हित high_wm_percent_value;
	अचिन्हित low_wm_percent_value;
	अचिन्हित स्वतःcommit_समय_value;
	अचिन्हित max_age_value;

	अचिन्हित ग_लिखोback_all;
	काष्ठा workqueue_काष्ठा *ग_लिखोback_wq;
	काष्ठा work_काष्ठा ग_लिखोback_work;
	काष्ठा work_काष्ठा flush_work;

	काष्ठा dm_io_client *dm_io;

	raw_spinlock_t endio_list_lock;
	काष्ठा list_head endio_list;
	काष्ठा task_काष्ठा *endio_thपढ़ो;

	काष्ठा task_काष्ठा *flush_thपढ़ो;
	काष्ठा bio_list flush_list;

	काष्ठा dm_kcopyd_client *dm_kcopyd;
	अचिन्हित दीर्घ *dirty_biपंचांगap;
	अचिन्हित dirty_biपंचांगap_size;

	काष्ठा bio_set bio_set;
	mempool_t copy_pool;
पूर्ण;

#घोषणा WB_LIST_INLINE		16

काष्ठा ग_लिखोback_काष्ठा अणु
	काष्ठा list_head endio_entry;
	काष्ठा dm_ग_लिखोcache *wc;
	काष्ठा wc_entry **wc_list;
	अचिन्हित wc_list_n;
	काष्ठा wc_entry *wc_list_अंतरभूत[WB_LIST_INLINE];
	काष्ठा bio bio;
पूर्ण;

काष्ठा copy_काष्ठा अणु
	काष्ठा list_head endio_entry;
	काष्ठा dm_ग_लिखोcache *wc;
	काष्ठा wc_entry *e;
	अचिन्हित n_entries;
	पूर्णांक error;
पूर्ण;

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(dm_ग_लिखोcache_throttle,
					    "A percentage of time allocated for data copying");

अटल व्योम wc_lock(काष्ठा dm_ग_लिखोcache *wc)
अणु
	mutex_lock(&wc->lock);
पूर्ण

अटल व्योम wc_unlock(काष्ठा dm_ग_लिखोcache *wc)
अणु
	mutex_unlock(&wc->lock);
पूर्ण

#अगर_घोषित DM_WRITECACHE_HAS_PMEM
अटल पूर्णांक persistent_memory_claim(काष्ठा dm_ग_लिखोcache *wc)
अणु
	पूर्णांक r;
	loff_t s;
	दीर्घ p, da;
	pfn_t pfn;
	पूर्णांक id;
	काष्ठा page **pages;
	sector_t offset;

	wc->memory_vmapped = false;

	s = wc->memory_map_size;
	p = s >> PAGE_SHIFT;
	अगर (!p) अणु
		r = -EINVAL;
		जाओ err1;
	पूर्ण
	अगर (p != s >> PAGE_SHIFT) अणु
		r = -EOVERFLOW;
		जाओ err1;
	पूर्ण

	offset = get_start_sect(wc->ssd_dev->bdev);
	अगर (offset & (PAGE_SIZE / 512 - 1)) अणु
		r = -EINVAL;
		जाओ err1;
	पूर्ण
	offset >>= PAGE_SHIFT - 9;

	id = dax_पढ़ो_lock();

	da = dax_direct_access(wc->ssd_dev->dax_dev, offset, p, &wc->memory_map, &pfn);
	अगर (da < 0) अणु
		wc->memory_map = शून्य;
		r = da;
		जाओ err2;
	पूर्ण
	अगर (!pfn_t_has_page(pfn)) अणु
		wc->memory_map = शून्य;
		r = -EOPNOTSUPP;
		जाओ err2;
	पूर्ण
	अगर (da != p) अणु
		दीर्घ i;
		wc->memory_map = शून्य;
		pages = kvदो_स्मृति_array(p, माप(काष्ठा page *), GFP_KERNEL);
		अगर (!pages) अणु
			r = -ENOMEM;
			जाओ err2;
		पूर्ण
		i = 0;
		करो अणु
			दीर्घ daa;
			daa = dax_direct_access(wc->ssd_dev->dax_dev, offset + i, p - i,
						शून्य, &pfn);
			अगर (daa <= 0) अणु
				r = daa ? daa : -EINVAL;
				जाओ err3;
			पूर्ण
			अगर (!pfn_t_has_page(pfn)) अणु
				r = -EOPNOTSUPP;
				जाओ err3;
			पूर्ण
			जबतक (daa-- && i < p) अणु
				pages[i++] = pfn_t_to_page(pfn);
				pfn.val++;
				अगर (!(i & 15))
					cond_resched();
			पूर्ण
		पूर्ण जबतक (i < p);
		wc->memory_map = vmap(pages, p, VM_MAP, PAGE_KERNEL);
		अगर (!wc->memory_map) अणु
			r = -ENOMEM;
			जाओ err3;
		पूर्ण
		kvमुक्त(pages);
		wc->memory_vmapped = true;
	पूर्ण

	dax_पढ़ो_unlock(id);

	wc->memory_map += (माप_प्रकार)wc->start_sector << SECTOR_SHIFT;
	wc->memory_map_size -= (माप_प्रकार)wc->start_sector << SECTOR_SHIFT;

	वापस 0;
err3:
	kvमुक्त(pages);
err2:
	dax_पढ़ो_unlock(id);
err1:
	वापस r;
पूर्ण
#अन्यथा
अटल पूर्णांक persistent_memory_claim(काष्ठा dm_ग_लिखोcache *wc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल व्योम persistent_memory_release(काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (wc->memory_vmapped)
		vunmap(wc->memory_map - ((माप_प्रकार)wc->start_sector << SECTOR_SHIFT));
पूर्ण

अटल काष्ठा page *persistent_memory_page(व्योम *addr)
अणु
	अगर (is_vदो_स्मृति_addr(addr))
		वापस vदो_स्मृति_to_page(addr);
	अन्यथा
		वापस virt_to_page(addr);
पूर्ण

अटल अचिन्हित persistent_memory_page_offset(व्योम *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr & (PAGE_SIZE - 1);
पूर्ण

अटल व्योम persistent_memory_flush_cache(व्योम *ptr, माप_प्रकार size)
अणु
	अगर (is_vदो_स्मृति_addr(ptr))
		flush_kernel_vmap_range(ptr, size);
पूर्ण

अटल व्योम persistent_memory_invalidate_cache(व्योम *ptr, माप_प्रकार size)
अणु
	अगर (is_vदो_स्मृति_addr(ptr))
		invalidate_kernel_vmap_range(ptr, size);
पूर्ण

अटल काष्ठा wc_memory_superblock *sb(काष्ठा dm_ग_लिखोcache *wc)
अणु
	वापस wc->memory_map;
पूर्ण

अटल काष्ठा wc_memory_entry *memory_entry(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	वापस &sb(wc)->entries[e->index];
पूर्ण

अटल व्योम *memory_data(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	वापस (अक्षर *)wc->block_start + (e->index << wc->block_size_bits);
पूर्ण

अटल sector_t cache_sector(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	वापस wc->start_sector + wc->metadata_sectors +
		((sector_t)e->index << (wc->block_size_bits - SECTOR_SHIFT));
पूर्ण

अटल uपूर्णांक64_t पढ़ो_original_sector(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	वापस e->original_sector;
#अन्यथा
	वापस le64_to_cpu(memory_entry(wc, e)->original_sector);
#पूर्ण_अगर
पूर्ण

अटल uपूर्णांक64_t पढ़ो_seq_count(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	वापस e->seq_count;
#अन्यथा
	वापस le64_to_cpu(memory_entry(wc, e)->seq_count);
#पूर्ण_अगर
पूर्ण

अटल व्योम clear_seq_count(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	e->seq_count = -1;
#पूर्ण_अगर
	pmem_assign(memory_entry(wc, e)->seq_count, cpu_to_le64(-1));
पूर्ण

अटल व्योम ग_लिखो_original_sector_seq_count(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e,
					    uपूर्णांक64_t original_sector, uपूर्णांक64_t seq_count)
अणु
	काष्ठा wc_memory_entry me;
#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	e->original_sector = original_sector;
	e->seq_count = seq_count;
#पूर्ण_अगर
	me.original_sector = cpu_to_le64(original_sector);
	me.seq_count = cpu_to_le64(seq_count);
	pmem_assign(*memory_entry(wc, e), me);
पूर्ण

#घोषणा ग_लिखोcache_error(wc, err, msg, arg...)				\
करो अणु									\
	अगर (!cmpxchg(&(wc)->error, 0, err))				\
		DMERR(msg, ##arg);					\
	wake_up(&(wc)->मुक्तlist_रुको);					\
पूर्ण जबतक (0)

#घोषणा ग_लिखोcache_has_error(wc)	(unlikely(READ_ONCE((wc)->error)))

अटल व्योम ग_लिखोcache_flush_all_metadata(काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (!WC_MODE_PMEM(wc))
		स_रखो(wc->dirty_biपंचांगap, -1, wc->dirty_biपंचांगap_size);
पूर्ण

अटल व्योम ग_लिखोcache_flush_region(काष्ठा dm_ग_लिखोcache *wc, व्योम *ptr, माप_प्रकार size)
अणु
	अगर (!WC_MODE_PMEM(wc))
		__set_bit(((अक्षर *)ptr - (अक्षर *)wc->memory_map) / BITMAP_GRANULARITY,
			  wc->dirty_biपंचांगap);
पूर्ण

अटल व्योम ग_लिखोcache_disk_flush(काष्ठा dm_ग_लिखोcache *wc, काष्ठा dm_dev *dev);

काष्ठा io_notअगरy अणु
	काष्ठा dm_ग_लिखोcache *wc;
	काष्ठा completion c;
	atomic_t count;
पूर्ण;

अटल व्योम ग_लिखोcache_notअगरy_io(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा io_notअगरy *endio = context;

	अगर (unlikely(error != 0))
		ग_लिखोcache_error(endio->wc, -EIO, "error writing metadata");
	BUG_ON(atomic_पढ़ो(&endio->count) <= 0);
	अगर (atomic_dec_and_test(&endio->count))
		complete(&endio->c);
पूर्ण

अटल व्योम ग_लिखोcache_रुको_क्रम_ios(काष्ठा dm_ग_लिखोcache *wc, पूर्णांक direction)
अणु
	रुको_event(wc->bio_in_progress_रुको[direction],
		   !atomic_पढ़ो(&wc->bio_in_progress[direction]));
पूर्ण

अटल व्योम ssd_commit_flushed(काष्ठा dm_ग_लिखोcache *wc, bool रुको_क्रम_ios)
अणु
	काष्ठा dm_io_region region;
	काष्ठा dm_io_request req;
	काष्ठा io_notअगरy endio = अणु
		wc,
		COMPLETION_INITIALIZER_ONSTACK(endio.c),
		ATOMIC_INIT(1),
	पूर्ण;
	अचिन्हित biपंचांगap_bits = wc->dirty_biपंचांगap_size * 8;
	अचिन्हित i = 0;

	जबतक (1) अणु
		अचिन्हित j;
		i = find_next_bit(wc->dirty_biपंचांगap, biपंचांगap_bits, i);
		अगर (unlikely(i == biपंचांगap_bits))
			अवरोध;
		j = find_next_zero_bit(wc->dirty_biपंचांगap, biपंचांगap_bits, i);

		region.bdev = wc->ssd_dev->bdev;
		region.sector = (sector_t)i * (BITMAP_GRANULARITY >> SECTOR_SHIFT);
		region.count = (sector_t)(j - i) * (BITMAP_GRANULARITY >> SECTOR_SHIFT);

		अगर (unlikely(region.sector >= wc->metadata_sectors))
			अवरोध;
		अगर (unlikely(region.sector + region.count > wc->metadata_sectors))
			region.count = wc->metadata_sectors - region.sector;

		region.sector += wc->start_sector;
		atomic_inc(&endio.count);
		req.bi_op = REQ_OP_WRITE;
		req.bi_op_flags = REQ_SYNC;
		req.mem.type = DM_IO_VMA;
		req.mem.ptr.vma = (अक्षर *)wc->memory_map + (माप_प्रकार)i * BITMAP_GRANULARITY;
		req.client = wc->dm_io;
		req.notअगरy.fn = ग_लिखोcache_notअगरy_io;
		req.notअगरy.context = &endio;

		/* writing via async dm-io (implied by notअगरy.fn above) won't वापस an error */
	        (व्योम) dm_io(&req, 1, &region, शून्य);
		i = j;
	पूर्ण

	ग_लिखोcache_notअगरy_io(0, &endio);
	रुको_क्रम_completion_io(&endio.c);

	अगर (रुको_क्रम_ios)
		ग_लिखोcache_रुको_क्रम_ios(wc, WRITE);

	ग_लिखोcache_disk_flush(wc, wc->ssd_dev);

	स_रखो(wc->dirty_biपंचांगap, 0, wc->dirty_biपंचांगap_size);
पूर्ण

अटल व्योम ssd_commit_superblock(काष्ठा dm_ग_लिखोcache *wc)
अणु
	पूर्णांक r;
	काष्ठा dm_io_region region;
	काष्ठा dm_io_request req;

	region.bdev = wc->ssd_dev->bdev;
	region.sector = 0;
	region.count = PAGE_SIZE >> SECTOR_SHIFT;

	अगर (unlikely(region.sector + region.count > wc->metadata_sectors))
		region.count = wc->metadata_sectors - region.sector;

	region.sector += wc->start_sector;

	req.bi_op = REQ_OP_WRITE;
	req.bi_op_flags = REQ_SYNC | REQ_FUA;
	req.mem.type = DM_IO_VMA;
	req.mem.ptr.vma = (अक्षर *)wc->memory_map;
	req.client = wc->dm_io;
	req.notअगरy.fn = शून्य;
	req.notअगरy.context = शून्य;

	r = dm_io(&req, 1, &region, शून्य);
	अगर (unlikely(r))
		ग_लिखोcache_error(wc, r, "error writing superblock");
पूर्ण

अटल व्योम ग_लिखोcache_commit_flushed(काष्ठा dm_ग_लिखोcache *wc, bool रुको_क्रम_ios)
अणु
	अगर (WC_MODE_PMEM(wc))
		pmem_wmb();
	अन्यथा
		ssd_commit_flushed(wc, रुको_क्रम_ios);
पूर्ण

अटल व्योम ग_लिखोcache_disk_flush(काष्ठा dm_ग_लिखोcache *wc, काष्ठा dm_dev *dev)
अणु
	पूर्णांक r;
	काष्ठा dm_io_region region;
	काष्ठा dm_io_request req;

	region.bdev = dev->bdev;
	region.sector = 0;
	region.count = 0;
	req.bi_op = REQ_OP_WRITE;
	req.bi_op_flags = REQ_PREFLUSH;
	req.mem.type = DM_IO_KMEM;
	req.mem.ptr.addr = शून्य;
	req.client = wc->dm_io;
	req.notअगरy.fn = शून्य;

	r = dm_io(&req, 1, &region, शून्य);
	अगर (unlikely(r))
		ग_लिखोcache_error(wc, r, "error flushing metadata: %d", r);
पूर्ण

#घोषणा WFE_RETURN_FOLLOWING	1
#घोषणा WFE_LOWEST_SEQ		2

अटल काष्ठा wc_entry *ग_लिखोcache_find_entry(काष्ठा dm_ग_लिखोcache *wc,
					      uपूर्णांक64_t block, पूर्णांक flags)
अणु
	काष्ठा wc_entry *e;
	काष्ठा rb_node *node = wc->tree.rb_node;

	अगर (unlikely(!node))
		वापस शून्य;

	जबतक (1) अणु
		e = container_of(node, काष्ठा wc_entry, rb_node);
		अगर (पढ़ो_original_sector(wc, e) == block)
			अवरोध;

		node = (पढ़ो_original_sector(wc, e) >= block ?
			e->rb_node.rb_left : e->rb_node.rb_right);
		अगर (unlikely(!node)) अणु
			अगर (!(flags & WFE_RETURN_FOLLOWING))
				वापस शून्य;
			अगर (पढ़ो_original_sector(wc, e) >= block) अणु
				वापस e;
			पूर्ण अन्यथा अणु
				node = rb_next(&e->rb_node);
				अगर (unlikely(!node))
					वापस शून्य;
				e = container_of(node, काष्ठा wc_entry, rb_node);
				वापस e;
			पूर्ण
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		काष्ठा wc_entry *e2;
		अगर (flags & WFE_LOWEST_SEQ)
			node = rb_prev(&e->rb_node);
		अन्यथा
			node = rb_next(&e->rb_node);
		अगर (unlikely(!node))
			वापस e;
		e2 = container_of(node, काष्ठा wc_entry, rb_node);
		अगर (पढ़ो_original_sector(wc, e2) != block)
			वापस e;
		e = e2;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखोcache_insert_entry(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *ins)
अणु
	काष्ठा wc_entry *e;
	काष्ठा rb_node **node = &wc->tree.rb_node, *parent = शून्य;

	जबतक (*node) अणु
		e = container_of(*node, काष्ठा wc_entry, rb_node);
		parent = &e->rb_node;
		अगर (पढ़ो_original_sector(wc, e) > पढ़ो_original_sector(wc, ins))
			node = &parent->rb_left;
		अन्यथा
			node = &parent->rb_right;
	पूर्ण
	rb_link_node(&ins->rb_node, parent, node);
	rb_insert_color(&ins->rb_node, &wc->tree);
	list_add(&ins->lru, &wc->lru);
	ins->age = jअगरfies;
पूर्ण

अटल व्योम ग_लिखोcache_unlink(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	list_del(&e->lru);
	rb_erase(&e->rb_node, &wc->tree);
पूर्ण

अटल व्योम ग_लिखोcache_add_to_मुक्तlist(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	अगर (WC_MODE_SORT_FREELIST(wc)) अणु
		काष्ठा rb_node **node = &wc->मुक्तtree.rb_node, *parent = शून्य;
		अगर (unlikely(!*node))
			wc->current_मुक्त = e;
		जबतक (*node) अणु
			parent = *node;
			अगर (&e->rb_node < *node)
				node = &parent->rb_left;
			अन्यथा
				node = &parent->rb_right;
		पूर्ण
		rb_link_node(&e->rb_node, parent, node);
		rb_insert_color(&e->rb_node, &wc->मुक्तtree);
	पूर्ण अन्यथा अणु
		list_add_tail(&e->lru, &wc->मुक्तlist);
	पूर्ण
	wc->मुक्तlist_size++;
पूर्ण

अटल अंतरभूत व्योम ग_लिखोcache_verअगरy_watermark(काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (unlikely(wc->मुक्तlist_size + wc->ग_लिखोback_size <= wc->मुक्तlist_high_watermark))
		queue_work(wc->ग_लिखोback_wq, &wc->ग_लिखोback_work);
पूर्ण

अटल व्योम ग_लिखोcache_max_age_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dm_ग_लिखोcache *wc = from_समयr(wc, t, max_age_समयr);

	अगर (!dm_suspended(wc->ti) && !ग_लिखोcache_has_error(wc)) अणु
		queue_work(wc->ग_लिखोback_wq, &wc->ग_लिखोback_work);
		mod_समयr(&wc->max_age_समयr, jअगरfies + wc->max_age / MAX_AGE_DIV);
	पूर्ण
पूर्ण

अटल काष्ठा wc_entry *ग_लिखोcache_pop_from_मुक्तlist(काष्ठा dm_ग_लिखोcache *wc, sector_t expected_sector)
अणु
	काष्ठा wc_entry *e;

	अगर (WC_MODE_SORT_FREELIST(wc)) अणु
		काष्ठा rb_node *next;
		अगर (unlikely(!wc->current_मुक्त))
			वापस शून्य;
		e = wc->current_मुक्त;
		अगर (expected_sector != (sector_t)-1 && unlikely(cache_sector(wc, e) != expected_sector))
			वापस शून्य;
		next = rb_next(&e->rb_node);
		rb_erase(&e->rb_node, &wc->मुक्तtree);
		अगर (unlikely(!next))
			next = rb_first(&wc->मुक्तtree);
		wc->current_मुक्त = next ? container_of(next, काष्ठा wc_entry, rb_node) : शून्य;
	पूर्ण अन्यथा अणु
		अगर (unlikely(list_empty(&wc->मुक्तlist)))
			वापस शून्य;
		e = container_of(wc->मुक्तlist.next, काष्ठा wc_entry, lru);
		अगर (expected_sector != (sector_t)-1 && unlikely(cache_sector(wc, e) != expected_sector))
			वापस शून्य;
		list_del(&e->lru);
	पूर्ण
	wc->मुक्तlist_size--;

	ग_लिखोcache_verअगरy_watermark(wc);

	वापस e;
पूर्ण

अटल व्योम ग_लिखोcache_मुक्त_entry(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	ग_लिखोcache_unlink(wc, e);
	ग_लिखोcache_add_to_मुक्तlist(wc, e);
	clear_seq_count(wc, e);
	ग_लिखोcache_flush_region(wc, memory_entry(wc, e), माप(काष्ठा wc_memory_entry));
	अगर (unlikely(रुकोqueue_active(&wc->मुक्तlist_रुको)))
		wake_up(&wc->मुक्तlist_रुको);
पूर्ण

अटल व्योम ग_लिखोcache_रुको_on_मुक्तlist(काष्ठा dm_ग_लिखोcache *wc)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(&wc->मुक्तlist_रुको, &रुको, TASK_UNINTERRUPTIBLE);
	wc_unlock(wc);
	io_schedule();
	finish_रुको(&wc->मुक्तlist_रुको, &रुको);
	wc_lock(wc);
पूर्ण

अटल व्योम ग_लिखोcache_poison_lists(काष्ठा dm_ग_लिखोcache *wc)
अणु
	/*
	 * Catch incorrect access to these values जबतक the device is suspended.
	 */
	स_रखो(&wc->tree, -1, माप wc->tree);
	wc->lru.next = LIST_POISON1;
	wc->lru.prev = LIST_POISON2;
	wc->मुक्तlist.next = LIST_POISON1;
	wc->मुक्तlist.prev = LIST_POISON2;
पूर्ण

अटल व्योम ग_लिखोcache_flush_entry(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	ग_लिखोcache_flush_region(wc, memory_entry(wc, e), माप(काष्ठा wc_memory_entry));
	अगर (WC_MODE_PMEM(wc))
		ग_लिखोcache_flush_region(wc, memory_data(wc, e), wc->block_size);
पूर्ण

अटल bool ग_लिखोcache_entry_is_committed(काष्ठा dm_ग_लिखोcache *wc, काष्ठा wc_entry *e)
अणु
	वापस पढ़ो_seq_count(wc, e) < wc->seq_count;
पूर्ण

अटल व्योम ग_लिखोcache_flush(काष्ठा dm_ग_लिखोcache *wc)
अणु
	काष्ठा wc_entry *e, *e2;
	bool need_flush_after_मुक्त;

	wc->uncommitted_blocks = 0;
	del_समयr(&wc->स्वतःcommit_समयr);

	अगर (list_empty(&wc->lru))
		वापस;

	e = container_of(wc->lru.next, काष्ठा wc_entry, lru);
	अगर (ग_लिखोcache_entry_is_committed(wc, e)) अणु
		अगर (wc->overwrote_committed) अणु
			ग_लिखोcache_रुको_क्रम_ios(wc, WRITE);
			ग_लिखोcache_disk_flush(wc, wc->ssd_dev);
			wc->overwrote_committed = false;
		पूर्ण
		वापस;
	पूर्ण
	जबतक (1) अणु
		ग_लिखोcache_flush_entry(wc, e);
		अगर (unlikely(e->lru.next == &wc->lru))
			अवरोध;
		e2 = container_of(e->lru.next, काष्ठा wc_entry, lru);
		अगर (ग_लिखोcache_entry_is_committed(wc, e2))
			अवरोध;
		e = e2;
		cond_resched();
	पूर्ण
	ग_लिखोcache_commit_flushed(wc, true);

	wc->seq_count++;
	pmem_assign(sb(wc)->seq_count, cpu_to_le64(wc->seq_count));
	अगर (WC_MODE_PMEM(wc))
		ग_लिखोcache_commit_flushed(wc, false);
	अन्यथा
		ssd_commit_superblock(wc);

	wc->overwrote_committed = false;

	need_flush_after_मुक्त = false;
	जबतक (1) अणु
		/* Free another committed entry with lower seq-count */
		काष्ठा rb_node *rb_node = rb_prev(&e->rb_node);

		अगर (rb_node) अणु
			e2 = container_of(rb_node, काष्ठा wc_entry, rb_node);
			अगर (पढ़ो_original_sector(wc, e2) == पढ़ो_original_sector(wc, e) &&
			    likely(!e2->ग_लिखो_in_progress)) अणु
				ग_लिखोcache_मुक्त_entry(wc, e2);
				need_flush_after_मुक्त = true;
			पूर्ण
		पूर्ण
		अगर (unlikely(e->lru.prev == &wc->lru))
			अवरोध;
		e = container_of(e->lru.prev, काष्ठा wc_entry, lru);
		cond_resched();
	पूर्ण

	अगर (need_flush_after_मुक्त)
		ग_लिखोcache_commit_flushed(wc, false);
पूर्ण

अटल व्योम ग_लिखोcache_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_ग_लिखोcache *wc = container_of(work, काष्ठा dm_ग_लिखोcache, flush_work);

	wc_lock(wc);
	ग_लिखोcache_flush(wc);
	wc_unlock(wc);
पूर्ण

अटल व्योम ग_लिखोcache_स्वतःcommit_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dm_ग_लिखोcache *wc = from_समयr(wc, t, स्वतःcommit_समयr);
	अगर (!ग_लिखोcache_has_error(wc))
		queue_work(wc->ग_लिखोback_wq, &wc->flush_work);
पूर्ण

अटल व्योम ग_लिखोcache_schedule_स्वतःcommit(काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (!समयr_pending(&wc->स्वतःcommit_समयr))
		mod_समयr(&wc->स्वतःcommit_समयr, jअगरfies + wc->स्वतःcommit_jअगरfies);
पूर्ण

अटल व्योम ग_लिखोcache_discard(काष्ठा dm_ग_लिखोcache *wc, sector_t start, sector_t end)
अणु
	काष्ठा wc_entry *e;
	bool discarded_something = false;

	e = ग_लिखोcache_find_entry(wc, start, WFE_RETURN_FOLLOWING | WFE_LOWEST_SEQ);
	अगर (unlikely(!e))
		वापस;

	जबतक (पढ़ो_original_sector(wc, e) < end) अणु
		काष्ठा rb_node *node = rb_next(&e->rb_node);

		अगर (likely(!e->ग_लिखो_in_progress)) अणु
			अगर (!discarded_something) अणु
				अगर (!WC_MODE_PMEM(wc)) अणु
					ग_लिखोcache_रुको_क्रम_ios(wc, READ);
					ग_लिखोcache_रुको_क्रम_ios(wc, WRITE);
				पूर्ण
				discarded_something = true;
			पूर्ण
			अगर (!ग_लिखोcache_entry_is_committed(wc, e))
				wc->uncommitted_blocks--;
			ग_लिखोcache_मुक्त_entry(wc, e);
		पूर्ण

		अगर (unlikely(!node))
			अवरोध;

		e = container_of(node, काष्ठा wc_entry, rb_node);
	पूर्ण

	अगर (discarded_something)
		ग_लिखोcache_commit_flushed(wc, false);
पूर्ण

अटल bool ग_लिखोcache_रुको_क्रम_ग_लिखोback(काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (wc->ग_लिखोback_size) अणु
		ग_लिखोcache_रुको_on_मुक्तlist(wc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम ग_लिखोcache_suspend(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;
	bool flush_on_suspend;

	del_समयr_sync(&wc->स्वतःcommit_समयr);
	del_समयr_sync(&wc->max_age_समयr);

	wc_lock(wc);
	ग_लिखोcache_flush(wc);
	flush_on_suspend = wc->flush_on_suspend;
	अगर (flush_on_suspend) अणु
		wc->flush_on_suspend = false;
		wc->ग_लिखोback_all++;
		queue_work(wc->ग_लिखोback_wq, &wc->ग_लिखोback_work);
	पूर्ण
	wc_unlock(wc);

	drain_workqueue(wc->ग_लिखोback_wq);

	wc_lock(wc);
	अगर (flush_on_suspend)
		wc->ग_लिखोback_all--;
	जबतक (ग_लिखोcache_रुको_क्रम_ग_लिखोback(wc));

	अगर (WC_MODE_PMEM(wc))
		persistent_memory_flush_cache(wc->memory_map, wc->memory_map_size);

	ग_लिखोcache_poison_lists(wc);

	wc_unlock(wc);
पूर्ण

अटल पूर्णांक ग_लिखोcache_alloc_entries(काष्ठा dm_ग_लिखोcache *wc)
अणु
	माप_प्रकार b;

	अगर (wc->entries)
		वापस 0;
	wc->entries = vदो_स्मृति(array_size(माप(काष्ठा wc_entry), wc->n_blocks));
	अगर (!wc->entries)
		वापस -ENOMEM;
	क्रम (b = 0; b < wc->n_blocks; b++) अणु
		काष्ठा wc_entry *e = &wc->entries[b];
		e->index = b;
		e->ग_लिखो_in_progress = false;
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखोcache_पढ़ो_metadata(काष्ठा dm_ग_लिखोcache *wc, sector_t n_sectors)
अणु
	काष्ठा dm_io_region region;
	काष्ठा dm_io_request req;

	region.bdev = wc->ssd_dev->bdev;
	region.sector = wc->start_sector;
	region.count = n_sectors;
	req.bi_op = REQ_OP_READ;
	req.bi_op_flags = REQ_SYNC;
	req.mem.type = DM_IO_VMA;
	req.mem.ptr.vma = (अक्षर *)wc->memory_map;
	req.client = wc->dm_io;
	req.notअगरy.fn = शून्य;

	वापस dm_io(&req, 1, &region, शून्य);
पूर्ण

अटल व्योम ग_लिखोcache_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;
	माप_प्रकार b;
	bool need_flush = false;
	__le64 sb_seq_count;
	पूर्णांक r;

	wc_lock(wc);

	wc->data_device_sectors = bdev_nr_sectors(wc->dev->bdev);

	अगर (WC_MODE_PMEM(wc)) अणु
		persistent_memory_invalidate_cache(wc->memory_map, wc->memory_map_size);
	पूर्ण अन्यथा अणु
		r = ग_लिखोcache_पढ़ो_metadata(wc, wc->metadata_sectors);
		अगर (r) अणु
			माप_प्रकार sb_entries_offset;
			ग_लिखोcache_error(wc, r, "unable to read metadata: %d", r);
			sb_entries_offset = दुरत्व(काष्ठा wc_memory_superblock, entries);
			स_रखो((अक्षर *)wc->memory_map + sb_entries_offset, -1,
			       (wc->metadata_sectors << SECTOR_SHIFT) - sb_entries_offset);
		पूर्ण
	पूर्ण

	wc->tree = RB_ROOT;
	INIT_LIST_HEAD(&wc->lru);
	अगर (WC_MODE_SORT_FREELIST(wc)) अणु
		wc->मुक्तtree = RB_ROOT;
		wc->current_मुक्त = शून्य;
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&wc->मुक्तlist);
	पूर्ण
	wc->मुक्तlist_size = 0;

	r = copy_mc_to_kernel(&sb_seq_count, &sb(wc)->seq_count,
			      माप(uपूर्णांक64_t));
	अगर (r) अणु
		ग_लिखोcache_error(wc, r, "hardware memory error when reading superblock: %d", r);
		sb_seq_count = cpu_to_le64(0);
	पूर्ण
	wc->seq_count = le64_to_cpu(sb_seq_count);

#अगर_घोषित DM_WRITECACHE_HANDLE_HARDWARE_ERRORS
	क्रम (b = 0; b < wc->n_blocks; b++) अणु
		काष्ठा wc_entry *e = &wc->entries[b];
		काष्ठा wc_memory_entry wme;
		अगर (ग_लिखोcache_has_error(wc)) अणु
			e->original_sector = -1;
			e->seq_count = -1;
			जारी;
		पूर्ण
		r = copy_mc_to_kernel(&wme, memory_entry(wc, e),
				      माप(काष्ठा wc_memory_entry));
		अगर (r) अणु
			ग_लिखोcache_error(wc, r, "hardware memory error when reading metadata entry %lu: %d",
					 (अचिन्हित दीर्घ)b, r);
			e->original_sector = -1;
			e->seq_count = -1;
		पूर्ण अन्यथा अणु
			e->original_sector = le64_to_cpu(wme.original_sector);
			e->seq_count = le64_to_cpu(wme.seq_count);
		पूर्ण
		cond_resched();
	पूर्ण
#पूर्ण_अगर
	क्रम (b = 0; b < wc->n_blocks; b++) अणु
		काष्ठा wc_entry *e = &wc->entries[b];
		अगर (!ग_लिखोcache_entry_is_committed(wc, e)) अणु
			अगर (पढ़ो_seq_count(wc, e) != -1) अणु
erase_this:
				clear_seq_count(wc, e);
				need_flush = true;
			पूर्ण
			ग_लिखोcache_add_to_मुक्तlist(wc, e);
		पूर्ण अन्यथा अणु
			काष्ठा wc_entry *old;

			old = ग_लिखोcache_find_entry(wc, पढ़ो_original_sector(wc, e), 0);
			अगर (!old) अणु
				ग_लिखोcache_insert_entry(wc, e);
			पूर्ण अन्यथा अणु
				अगर (पढ़ो_seq_count(wc, old) == पढ़ो_seq_count(wc, e)) अणु
					ग_लिखोcache_error(wc, -EINVAL,
						 "two identical entries, position %llu, sector %llu, sequence %llu",
						 (अचिन्हित दीर्घ दीर्घ)b, (अचिन्हित दीर्घ दीर्घ)पढ़ो_original_sector(wc, e),
						 (अचिन्हित दीर्घ दीर्घ)पढ़ो_seq_count(wc, e));
				पूर्ण
				अगर (पढ़ो_seq_count(wc, old) > पढ़ो_seq_count(wc, e)) अणु
					जाओ erase_this;
				पूर्ण अन्यथा अणु
					ग_लिखोcache_मुक्त_entry(wc, old);
					ग_लिखोcache_insert_entry(wc, e);
					need_flush = true;
				पूर्ण
			पूर्ण
		पूर्ण
		cond_resched();
	पूर्ण

	अगर (need_flush) अणु
		ग_लिखोcache_flush_all_metadata(wc);
		ग_लिखोcache_commit_flushed(wc, false);
	पूर्ण

	ग_लिखोcache_verअगरy_watermark(wc);

	अगर (wc->max_age != MAX_AGE_UNSPECIFIED)
		mod_समयr(&wc->max_age_समयr, jअगरfies + wc->max_age / MAX_AGE_DIV);

	wc_unlock(wc);
पूर्ण

अटल पूर्णांक process_flush_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (argc != 1)
		वापस -EINVAL;

	wc_lock(wc);
	अगर (dm_suspended(wc->ti)) अणु
		wc_unlock(wc);
		वापस -EBUSY;
	पूर्ण
	अगर (ग_लिखोcache_has_error(wc)) अणु
		wc_unlock(wc);
		वापस -EIO;
	पूर्ण

	ग_लिखोcache_flush(wc);
	wc->ग_लिखोback_all++;
	queue_work(wc->ग_लिखोback_wq, &wc->ग_लिखोback_work);
	wc_unlock(wc);

	flush_workqueue(wc->ग_लिखोback_wq);

	wc_lock(wc);
	wc->ग_लिखोback_all--;
	अगर (ग_लिखोcache_has_error(wc)) अणु
		wc_unlock(wc);
		वापस -EIO;
	पूर्ण
	wc_unlock(wc);

	वापस 0;
पूर्ण

अटल पूर्णांक process_flush_on_suspend_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (argc != 1)
		वापस -EINVAL;

	wc_lock(wc);
	wc->flush_on_suspend = true;
	wc_unlock(wc);

	वापस 0;
पूर्ण

अटल व्योम activate_cleaner(काष्ठा dm_ग_लिखोcache *wc)
अणु
	wc->flush_on_suspend = true;
	wc->cleaner = true;
	wc->मुक्तlist_high_watermark = wc->n_blocks;
	wc->मुक्तlist_low_watermark = wc->n_blocks;
पूर्ण

अटल पूर्णांक process_cleaner_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा dm_ग_लिखोcache *wc)
अणु
	अगर (argc != 1)
		वापस -EINVAL;

	wc_lock(wc);
	activate_cleaner(wc);
	अगर (!dm_suspended(wc->ti))
		ग_लिखोcache_verअगरy_watermark(wc);
	wc_unlock(wc);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखोcache_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			      अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	अगर (!strहालcmp(argv[0], "flush"))
		r = process_flush_mesg(argc, argv, wc);
	अन्यथा अगर (!strहालcmp(argv[0], "flush_on_suspend"))
		r = process_flush_on_suspend_mesg(argc, argv, wc);
	अन्यथा अगर (!strहालcmp(argv[0], "cleaner"))
		r = process_cleaner_mesg(argc, argv, wc);
	अन्यथा
		DMERR("unrecognised message received: %s", argv[0]);

	वापस r;
पूर्ण

अटल व्योम स_नकल_flushcache_optimized(व्योम *dest, व्योम *source, माप_प्रकार size)
अणु
	/*
	 * clflushopt perक्रमms better with block size 1024, 2048, 4096
	 * non-temporal stores perक्रमm better with block size 512
	 *
	 * block size   512             1024            2048            4096
	 * movnti       496 MB/s        642 MB/s        725 MB/s        744 MB/s
	 * clflushopt   373 MB/s        688 MB/s        1.1 GB/s        1.2 GB/s
	 *
	 * We see that movnti perक्रमms better क्रम 512-byte blocks, and
	 * clflushopt perक्रमms better क्रम 1024-byte and larger blocks. So, we
	 * prefer clflushopt क्रम sizes >= 768.
	 *
	 * NOTE: this happens to be the हाल now (with dm-ग_लिखोcache's single
	 * thपढ़ोed model) but re-evaluate this once स_नकल_flushcache() is
	 * enabled to use movdir64b which might invalidate this perक्रमmance
	 * advantage seen with cache-allocating-ग_लिखोs plus flushing.
	 */
#अगर_घोषित CONFIG_X86
	अगर (अटल_cpu_has(X86_FEATURE_CLFLUSHOPT) &&
	    likely(boot_cpu_data.x86_clflush_size == 64) &&
	    likely(size >= 768)) अणु
		करो अणु
			स_नकल((व्योम *)dest, (व्योम *)source, 64);
			clflushopt((व्योम *)dest);
			dest += 64;
			source += 64;
			size -= 64;
		पूर्ण जबतक (size >= 64);
		वापस;
	पूर्ण
#पूर्ण_अगर
	स_नकल_flushcache(dest, source, size);
पूर्ण

अटल व्योम bio_copy_block(काष्ठा dm_ग_लिखोcache *wc, काष्ठा bio *bio, व्योम *data)
अणु
	व्योम *buf;
	अचिन्हित दीर्घ flags;
	अचिन्हित size;
	पूर्णांक rw = bio_data_dir(bio);
	अचिन्हित reमुख्यing_size = wc->block_size;

	करो अणु
		काष्ठा bio_vec bv = bio_iter_iovec(bio, bio->bi_iter);
		buf = bvec_kmap_irq(&bv, &flags);
		size = bv.bv_len;
		अगर (unlikely(size > reमुख्यing_size))
			size = reमुख्यing_size;

		अगर (rw == READ) अणु
			पूर्णांक r;
			r = copy_mc_to_kernel(buf, data, size);
			flush_dcache_page(bio_page(bio));
			अगर (unlikely(r)) अणु
				ग_लिखोcache_error(wc, r, "hardware memory error when reading data: %d", r);
				bio->bi_status = BLK_STS_IOERR;
			पूर्ण
		पूर्ण अन्यथा अणु
			flush_dcache_page(bio_page(bio));
			स_नकल_flushcache_optimized(data, buf, size);
		पूर्ण

		bvec_kunmap_irq(buf, &flags);

		data = (अक्षर *)data + size;
		reमुख्यing_size -= size;
		bio_advance(bio, size);
	पूर्ण जबतक (unlikely(reमुख्यing_size));
पूर्ण

अटल पूर्णांक ग_लिखोcache_flush_thपढ़ो(व्योम *data)
अणु
	काष्ठा dm_ग_लिखोcache *wc = data;

	जबतक (1) अणु
		काष्ठा bio *bio;

		wc_lock(wc);
		bio = bio_list_pop(&wc->flush_list);
		अगर (!bio) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			wc_unlock(wc);

			अगर (unlikely(kthपढ़ो_should_stop())) अणु
				set_current_state(TASK_RUNNING);
				अवरोध;
			पूर्ण

			schedule();
			जारी;
		पूर्ण

		अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
			ग_लिखोcache_discard(wc, bio->bi_iter.bi_sector,
					   bio_end_sector(bio));
			wc_unlock(wc);
			bio_set_dev(bio, wc->dev->bdev);
			submit_bio_noacct(bio);
		पूर्ण अन्यथा अणु
			ग_लिखोcache_flush(wc);
			wc_unlock(wc);
			अगर (ग_लिखोcache_has_error(wc))
				bio->bi_status = BLK_STS_IOERR;
			bio_endio(bio);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ग_लिखोcache_offload_bio(काष्ठा dm_ग_लिखोcache *wc, काष्ठा bio *bio)
अणु
	अगर (bio_list_empty(&wc->flush_list))
		wake_up_process(wc->flush_thपढ़ो);
	bio_list_add(&wc->flush_list, bio);
पूर्ण

अटल पूर्णांक ग_लिखोcache_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा wc_entry *e;
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	bio->bi_निजी = शून्य;

	wc_lock(wc);

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)) अणु
		अगर (ग_लिखोcache_has_error(wc))
			जाओ unlock_error;
		अगर (WC_MODE_PMEM(wc)) अणु
			ग_लिखोcache_flush(wc);
			अगर (ग_लिखोcache_has_error(wc))
				जाओ unlock_error;
			जाओ unlock_submit;
		पूर्ण अन्यथा अणु
			ग_लिखोcache_offload_bio(wc, bio);
			जाओ unlock_वापस;
		पूर्ण
	पूर्ण

	bio->bi_iter.bi_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);

	अगर (unlikely((((अचिन्हित)bio->bi_iter.bi_sector | bio_sectors(bio)) &
				(wc->block_size / 512 - 1)) != 0)) अणु
		DMERR("I/O is not aligned, sector %llu, size %u, block size %u",
		      (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
		      bio->bi_iter.bi_size, wc->block_size);
		जाओ unlock_error;
	पूर्ण

	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD)) अणु
		अगर (ग_लिखोcache_has_error(wc))
			जाओ unlock_error;
		अगर (WC_MODE_PMEM(wc)) अणु
			ग_लिखोcache_discard(wc, bio->bi_iter.bi_sector, bio_end_sector(bio));
			जाओ unlock_remap_origin;
		पूर्ण अन्यथा अणु
			ग_लिखोcache_offload_bio(wc, bio);
			जाओ unlock_वापस;
		पूर्ण
	पूर्ण

	अगर (bio_data_dir(bio) == READ) अणु
पढ़ो_next_block:
		e = ग_लिखोcache_find_entry(wc, bio->bi_iter.bi_sector, WFE_RETURN_FOLLOWING);
		अगर (e && पढ़ो_original_sector(wc, e) == bio->bi_iter.bi_sector) अणु
			अगर (WC_MODE_PMEM(wc)) अणु
				bio_copy_block(wc, bio, memory_data(wc, e));
				अगर (bio->bi_iter.bi_size)
					जाओ पढ़ो_next_block;
				जाओ unlock_submit;
			पूर्ण अन्यथा अणु
				dm_accept_partial_bio(bio, wc->block_size >> SECTOR_SHIFT);
				bio_set_dev(bio, wc->ssd_dev->bdev);
				bio->bi_iter.bi_sector = cache_sector(wc, e);
				अगर (!ग_लिखोcache_entry_is_committed(wc, e))
					ग_लिखोcache_रुको_क्रम_ios(wc, WRITE);
				जाओ unlock_remap;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (e) अणु
				sector_t next_boundary =
					पढ़ो_original_sector(wc, e) - bio->bi_iter.bi_sector;
				अगर (next_boundary < bio->bi_iter.bi_size >> SECTOR_SHIFT) अणु
					dm_accept_partial_bio(bio, next_boundary);
				पूर्ण
			पूर्ण
			जाओ unlock_remap_origin;
		पूर्ण
	पूर्ण अन्यथा अणु
		करो अणु
			bool found_entry = false;
			अगर (ग_लिखोcache_has_error(wc))
				जाओ unlock_error;
			e = ग_लिखोcache_find_entry(wc, bio->bi_iter.bi_sector, 0);
			अगर (e) अणु
				अगर (!ग_लिखोcache_entry_is_committed(wc, e))
					जाओ bio_copy;
				अगर (!WC_MODE_PMEM(wc) && !e->ग_लिखो_in_progress) अणु
					wc->overwrote_committed = true;
					जाओ bio_copy;
				पूर्ण
				found_entry = true;
			पूर्ण अन्यथा अणु
				अगर (unlikely(wc->cleaner))
					जाओ direct_ग_लिखो;
			पूर्ण
			e = ग_लिखोcache_pop_from_मुक्तlist(wc, (sector_t)-1);
			अगर (unlikely(!e)) अणु
				अगर (!found_entry) अणु
direct_ग_लिखो:
					e = ग_लिखोcache_find_entry(wc, bio->bi_iter.bi_sector, WFE_RETURN_FOLLOWING);
					अगर (e) अणु
						sector_t next_boundary = पढ़ो_original_sector(wc, e) - bio->bi_iter.bi_sector;
						BUG_ON(!next_boundary);
						अगर (next_boundary < bio->bi_iter.bi_size >> SECTOR_SHIFT) अणु
							dm_accept_partial_bio(bio, next_boundary);
						पूर्ण
					पूर्ण
					जाओ unlock_remap_origin;
				पूर्ण
				ग_लिखोcache_रुको_on_मुक्तlist(wc);
				जारी;
			पूर्ण
			ग_लिखो_original_sector_seq_count(wc, e, bio->bi_iter.bi_sector, wc->seq_count);
			ग_लिखोcache_insert_entry(wc, e);
			wc->uncommitted_blocks++;
bio_copy:
			अगर (WC_MODE_PMEM(wc)) अणु
				bio_copy_block(wc, bio, memory_data(wc, e));
			पूर्ण अन्यथा अणु
				अचिन्हित bio_size = wc->block_size;
				sector_t start_cache_sec = cache_sector(wc, e);
				sector_t current_cache_sec = start_cache_sec + (bio_size >> SECTOR_SHIFT);

				जबतक (bio_size < bio->bi_iter.bi_size) अणु
					काष्ठा wc_entry *f = ग_लिखोcache_pop_from_मुक्तlist(wc, current_cache_sec);
					अगर (!f)
						अवरोध;
					ग_लिखो_original_sector_seq_count(wc, f, bio->bi_iter.bi_sector +
									(bio_size >> SECTOR_SHIFT), wc->seq_count);
					ग_लिखोcache_insert_entry(wc, f);
					wc->uncommitted_blocks++;
					bio_size += wc->block_size;
					current_cache_sec += wc->block_size >> SECTOR_SHIFT;
				पूर्ण

				bio_set_dev(bio, wc->ssd_dev->bdev);
				bio->bi_iter.bi_sector = start_cache_sec;
				dm_accept_partial_bio(bio, bio_size >> SECTOR_SHIFT);

				अगर (unlikely(wc->uncommitted_blocks >= wc->स्वतःcommit_blocks)) अणु
					wc->uncommitted_blocks = 0;
					queue_work(wc->ग_लिखोback_wq, &wc->flush_work);
				पूर्ण अन्यथा अणु
					ग_लिखोcache_schedule_स्वतःcommit(wc);
				पूर्ण
				जाओ unlock_remap;
			पूर्ण
		पूर्ण जबतक (bio->bi_iter.bi_size);

		अगर (unlikely(bio->bi_opf & REQ_FUA ||
			     wc->uncommitted_blocks >= wc->स्वतःcommit_blocks))
			ग_लिखोcache_flush(wc);
		अन्यथा
			ग_लिखोcache_schedule_स्वतःcommit(wc);
		जाओ unlock_submit;
	पूर्ण

unlock_remap_origin:
	bio_set_dev(bio, wc->dev->bdev);
	wc_unlock(wc);
	वापस DM_MAPIO_REMAPPED;

unlock_remap:
	/* make sure that ग_लिखोcache_end_io decrements bio_in_progress: */
	bio->bi_निजी = (व्योम *)1;
	atomic_inc(&wc->bio_in_progress[bio_data_dir(bio)]);
	wc_unlock(wc);
	वापस DM_MAPIO_REMAPPED;

unlock_submit:
	wc_unlock(wc);
	bio_endio(bio);
	वापस DM_MAPIO_SUBMITTED;

unlock_वापस:
	wc_unlock(wc);
	वापस DM_MAPIO_SUBMITTED;

unlock_error:
	wc_unlock(wc);
	bio_io_error(bio);
	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल पूर्णांक ग_लिखोcache_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio, blk_status_t *status)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	अगर (bio->bi_निजी != शून्य) अणु
		पूर्णांक dir = bio_data_dir(bio);
		अगर (atomic_dec_and_test(&wc->bio_in_progress[dir]))
			अगर (unlikely(रुकोqueue_active(&wc->bio_in_progress_रुको[dir])))
				wake_up(&wc->bio_in_progress_रुको[dir]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखोcache_iterate_devices(काष्ठा dm_target *ti,
				      iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	वापस fn(ti, wc->dev, 0, ti->len, data);
पूर्ण

अटल व्योम ग_लिखोcache_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	अगर (limits->logical_block_size < wc->block_size)
		limits->logical_block_size = wc->block_size;

	अगर (limits->physical_block_size < wc->block_size)
		limits->physical_block_size = wc->block_size;

	अगर (limits->io_min < wc->block_size)
		limits->io_min = wc->block_size;
पूर्ण


अटल व्योम ग_लिखोcache_ग_लिखोback_endio(काष्ठा bio *bio)
अणु
	काष्ठा ग_लिखोback_काष्ठा *wb = container_of(bio, काष्ठा ग_लिखोback_काष्ठा, bio);
	काष्ठा dm_ग_लिखोcache *wc = wb->wc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&wc->endio_list_lock, flags);
	अगर (unlikely(list_empty(&wc->endio_list)))
		wake_up_process(wc->endio_thपढ़ो);
	list_add_tail(&wb->endio_entry, &wc->endio_list);
	raw_spin_unlock_irqrestore(&wc->endio_list_lock, flags);
पूर्ण

अटल व्योम ग_लिखोcache_copy_endio(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *ptr)
अणु
	काष्ठा copy_काष्ठा *c = ptr;
	काष्ठा dm_ग_लिखोcache *wc = c->wc;

	c->error = likely(!(पढ़ो_err | ग_लिखो_err)) ? 0 : -EIO;

	raw_spin_lock_irq(&wc->endio_list_lock);
	अगर (unlikely(list_empty(&wc->endio_list)))
		wake_up_process(wc->endio_thपढ़ो);
	list_add_tail(&c->endio_entry, &wc->endio_list);
	raw_spin_unlock_irq(&wc->endio_list_lock);
पूर्ण

अटल व्योम __ग_लिखोcache_endio_pmem(काष्ठा dm_ग_लिखोcache *wc, काष्ठा list_head *list)
अणु
	अचिन्हित i;
	काष्ठा ग_लिखोback_काष्ठा *wb;
	काष्ठा wc_entry *e;
	अचिन्हित दीर्घ n_walked = 0;

	करो अणु
		wb = list_entry(list->next, काष्ठा ग_लिखोback_काष्ठा, endio_entry);
		list_del(&wb->endio_entry);

		अगर (unlikely(wb->bio.bi_status != BLK_STS_OK))
			ग_लिखोcache_error(wc, blk_status_to_त्रुटि_सं(wb->bio.bi_status),
					"write error %d", wb->bio.bi_status);
		i = 0;
		करो अणु
			e = wb->wc_list[i];
			BUG_ON(!e->ग_लिखो_in_progress);
			e->ग_लिखो_in_progress = false;
			INIT_LIST_HEAD(&e->lru);
			अगर (!ग_लिखोcache_has_error(wc))
				ग_लिखोcache_मुक्त_entry(wc, e);
			BUG_ON(!wc->ग_लिखोback_size);
			wc->ग_लिखोback_size--;
			n_walked++;
			अगर (unlikely(n_walked >= ENDIO_LATENCY)) अणु
				ग_लिखोcache_commit_flushed(wc, false);
				wc_unlock(wc);
				wc_lock(wc);
				n_walked = 0;
			पूर्ण
		पूर्ण जबतक (++i < wb->wc_list_n);

		अगर (wb->wc_list != wb->wc_list_अंतरभूत)
			kमुक्त(wb->wc_list);
		bio_put(&wb->bio);
	पूर्ण जबतक (!list_empty(list));
पूर्ण

अटल व्योम __ग_लिखोcache_endio_ssd(काष्ठा dm_ग_लिखोcache *wc, काष्ठा list_head *list)
अणु
	काष्ठा copy_काष्ठा *c;
	काष्ठा wc_entry *e;

	करो अणु
		c = list_entry(list->next, काष्ठा copy_काष्ठा, endio_entry);
		list_del(&c->endio_entry);

		अगर (unlikely(c->error))
			ग_लिखोcache_error(wc, c->error, "copy error");

		e = c->e;
		करो अणु
			BUG_ON(!e->ग_लिखो_in_progress);
			e->ग_लिखो_in_progress = false;
			INIT_LIST_HEAD(&e->lru);
			अगर (!ग_लिखोcache_has_error(wc))
				ग_लिखोcache_मुक्त_entry(wc, e);

			BUG_ON(!wc->ग_लिखोback_size);
			wc->ग_लिखोback_size--;
			e++;
		पूर्ण जबतक (--c->n_entries);
		mempool_मुक्त(c, &wc->copy_pool);
	पूर्ण जबतक (!list_empty(list));
पूर्ण

अटल पूर्णांक ग_लिखोcache_endio_thपढ़ो(व्योम *data)
अणु
	काष्ठा dm_ग_लिखोcache *wc = data;

	जबतक (1) अणु
		काष्ठा list_head list;

		raw_spin_lock_irq(&wc->endio_list_lock);
		अगर (!list_empty(&wc->endio_list))
			जाओ pop_from_list;
		set_current_state(TASK_INTERRUPTIBLE);
		raw_spin_unlock_irq(&wc->endio_list_lock);

		अगर (unlikely(kthपढ़ो_should_stop())) अणु
			set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण

		schedule();

		जारी;

pop_from_list:
		list = wc->endio_list;
		list.next->prev = list.prev->next = &list;
		INIT_LIST_HEAD(&wc->endio_list);
		raw_spin_unlock_irq(&wc->endio_list_lock);

		अगर (!WC_MODE_FUA(wc))
			ग_लिखोcache_disk_flush(wc, wc->dev);

		wc_lock(wc);

		अगर (WC_MODE_PMEM(wc)) अणु
			__ग_लिखोcache_endio_pmem(wc, &list);
		पूर्ण अन्यथा अणु
			__ग_लिखोcache_endio_ssd(wc, &list);
			ग_लिखोcache_रुको_क्रम_ios(wc, READ);
		पूर्ण

		ग_लिखोcache_commit_flushed(wc, false);

		wc_unlock(wc);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool wc_add_block(काष्ठा ग_लिखोback_काष्ठा *wb, काष्ठा wc_entry *e, gfp_t gfp)
अणु
	काष्ठा dm_ग_लिखोcache *wc = wb->wc;
	अचिन्हित block_size = wc->block_size;
	व्योम *address = memory_data(wc, e);

	persistent_memory_flush_cache(address, block_size);

	अगर (unlikely(bio_end_sector(&wb->bio) >= wc->data_device_sectors))
		वापस true;

	वापस bio_add_page(&wb->bio, persistent_memory_page(address),
			    block_size, persistent_memory_page_offset(address)) != 0;
पूर्ण

काष्ठा ग_लिखोback_list अणु
	काष्ठा list_head list;
	माप_प्रकार size;
पूर्ण;

अटल व्योम __ग_लिखोback_throttle(काष्ठा dm_ग_लिखोcache *wc, काष्ठा ग_लिखोback_list *wbl)
अणु
	अगर (unlikely(wc->max_ग_लिखोback_jobs)) अणु
		अगर (READ_ONCE(wc->ग_लिखोback_size) - wbl->size >= wc->max_ग_लिखोback_jobs) अणु
			wc_lock(wc);
			जबतक (wc->ग_लिखोback_size - wbl->size >= wc->max_ग_लिखोback_jobs)
				ग_लिखोcache_रुको_on_मुक्तlist(wc);
			wc_unlock(wc);
		पूर्ण
	पूर्ण
	cond_resched();
पूर्ण

अटल व्योम __ग_लिखोcache_ग_लिखोback_pmem(काष्ठा dm_ग_लिखोcache *wc, काष्ठा ग_लिखोback_list *wbl)
अणु
	काष्ठा wc_entry *e, *f;
	काष्ठा bio *bio;
	काष्ठा ग_लिखोback_काष्ठा *wb;
	अचिन्हित max_pages;

	जबतक (wbl->size) अणु
		wbl->size--;
		e = container_of(wbl->list.prev, काष्ठा wc_entry, lru);
		list_del(&e->lru);

		max_pages = e->wc_list_contiguous;

		bio = bio_alloc_bioset(GFP_NOIO, max_pages, &wc->bio_set);
		wb = container_of(bio, काष्ठा ग_लिखोback_काष्ठा, bio);
		wb->wc = wc;
		bio->bi_end_io = ग_लिखोcache_ग_लिखोback_endio;
		bio_set_dev(bio, wc->dev->bdev);
		bio->bi_iter.bi_sector = पढ़ो_original_sector(wc, e);
		अगर (max_pages <= WB_LIST_INLINE ||
		    unlikely(!(wb->wc_list = kदो_स्मृति_array(max_pages, माप(काष्ठा wc_entry *),
							   GFP_NOIO | __GFP_NORETRY |
							   __GFP_NOMEMALLOC | __GFP_NOWARN)))) अणु
			wb->wc_list = wb->wc_list_अंतरभूत;
			max_pages = WB_LIST_INLINE;
		पूर्ण

		BUG_ON(!wc_add_block(wb, e, GFP_NOIO));

		wb->wc_list[0] = e;
		wb->wc_list_n = 1;

		जबतक (wbl->size && wb->wc_list_n < max_pages) अणु
			f = container_of(wbl->list.prev, काष्ठा wc_entry, lru);
			अगर (पढ़ो_original_sector(wc, f) !=
			    पढ़ो_original_sector(wc, e) + (wc->block_size >> SECTOR_SHIFT))
				अवरोध;
			अगर (!wc_add_block(wb, f, GFP_NOWAIT | __GFP_NOWARN))
				अवरोध;
			wbl->size--;
			list_del(&f->lru);
			wb->wc_list[wb->wc_list_n++] = f;
			e = f;
		पूर्ण
		bio_set_op_attrs(bio, REQ_OP_WRITE, WC_MODE_FUA(wc) * REQ_FUA);
		अगर (ग_लिखोcache_has_error(wc)) अणु
			bio->bi_status = BLK_STS_IOERR;
			bio_endio(bio);
		पूर्ण अन्यथा अगर (unlikely(!bio_sectors(bio))) अणु
			bio->bi_status = BLK_STS_OK;
			bio_endio(bio);
		पूर्ण अन्यथा अणु
			submit_bio(bio);
		पूर्ण

		__ग_लिखोback_throttle(wc, wbl);
	पूर्ण
पूर्ण

अटल व्योम __ग_लिखोcache_ग_लिखोback_ssd(काष्ठा dm_ग_लिखोcache *wc, काष्ठा ग_लिखोback_list *wbl)
अणु
	काष्ठा wc_entry *e, *f;
	काष्ठा dm_io_region from, to;
	काष्ठा copy_काष्ठा *c;

	जबतक (wbl->size) अणु
		अचिन्हित n_sectors;

		wbl->size--;
		e = container_of(wbl->list.prev, काष्ठा wc_entry, lru);
		list_del(&e->lru);

		n_sectors = e->wc_list_contiguous << (wc->block_size_bits - SECTOR_SHIFT);

		from.bdev = wc->ssd_dev->bdev;
		from.sector = cache_sector(wc, e);
		from.count = n_sectors;
		to.bdev = wc->dev->bdev;
		to.sector = पढ़ो_original_sector(wc, e);
		to.count = n_sectors;

		c = mempool_alloc(&wc->copy_pool, GFP_NOIO);
		c->wc = wc;
		c->e = e;
		c->n_entries = e->wc_list_contiguous;

		जबतक ((n_sectors -= wc->block_size >> SECTOR_SHIFT)) अणु
			wbl->size--;
			f = container_of(wbl->list.prev, काष्ठा wc_entry, lru);
			BUG_ON(f != e + 1);
			list_del(&f->lru);
			e = f;
		पूर्ण

		अगर (unlikely(to.sector + to.count > wc->data_device_sectors)) अणु
			अगर (to.sector >= wc->data_device_sectors) अणु
				ग_लिखोcache_copy_endio(0, 0, c);
				जारी;
			पूर्ण
			from.count = to.count = wc->data_device_sectors - to.sector;
		पूर्ण

		dm_kcopyd_copy(wc->dm_kcopyd, &from, 1, &to, 0, ग_लिखोcache_copy_endio, c);

		__ग_लिखोback_throttle(wc, wbl);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखोcache_ग_लिखोback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_ग_लिखोcache *wc = container_of(work, काष्ठा dm_ग_लिखोcache, ग_लिखोback_work);
	काष्ठा blk_plug plug;
	काष्ठा wc_entry *f, *g, *e = शून्य;
	काष्ठा rb_node *node, *next_node;
	काष्ठा list_head skipped;
	काष्ठा ग_लिखोback_list wbl;
	अचिन्हित दीर्घ n_walked;

	wc_lock(wc);
restart:
	अगर (ग_लिखोcache_has_error(wc)) अणु
		wc_unlock(wc);
		वापस;
	पूर्ण

	अगर (unlikely(wc->ग_लिखोback_all)) अणु
		अगर (ग_लिखोcache_रुको_क्रम_ग_लिखोback(wc))
			जाओ restart;
	पूर्ण

	अगर (wc->overwrote_committed) अणु
		ग_लिखोcache_रुको_क्रम_ios(wc, WRITE);
	पूर्ण

	n_walked = 0;
	INIT_LIST_HEAD(&skipped);
	INIT_LIST_HEAD(&wbl.list);
	wbl.size = 0;
	जबतक (!list_empty(&wc->lru) &&
	       (wc->ग_लिखोback_all ||
		wc->मुक्तlist_size + wc->ग_लिखोback_size <= wc->मुक्तlist_low_watermark ||
		(jअगरfies - container_of(wc->lru.prev, काष्ठा wc_entry, lru)->age >=
		 wc->max_age - wc->max_age / MAX_AGE_DIV))) अणु

		n_walked++;
		अगर (unlikely(n_walked > WRITEBACK_LATENCY) &&
		    likely(!wc->ग_लिखोback_all) && likely(!dm_suspended(wc->ti))) अणु
			queue_work(wc->ग_लिखोback_wq, &wc->ग_लिखोback_work);
			अवरोध;
		पूर्ण

		अगर (unlikely(wc->ग_लिखोback_all)) अणु
			अगर (unlikely(!e)) अणु
				ग_लिखोcache_flush(wc);
				e = container_of(rb_first(&wc->tree), काष्ठा wc_entry, rb_node);
			पूर्ण अन्यथा
				e = g;
		पूर्ण अन्यथा
			e = container_of(wc->lru.prev, काष्ठा wc_entry, lru);
		BUG_ON(e->ग_लिखो_in_progress);
		अगर (unlikely(!ग_लिखोcache_entry_is_committed(wc, e))) अणु
			ग_लिखोcache_flush(wc);
		पूर्ण
		node = rb_prev(&e->rb_node);
		अगर (node) अणु
			f = container_of(node, काष्ठा wc_entry, rb_node);
			अगर (unlikely(पढ़ो_original_sector(wc, f) ==
				     पढ़ो_original_sector(wc, e))) अणु
				BUG_ON(!f->ग_लिखो_in_progress);
				list_del(&e->lru);
				list_add(&e->lru, &skipped);
				cond_resched();
				जारी;
			पूर्ण
		पूर्ण
		wc->ग_लिखोback_size++;
		list_del(&e->lru);
		list_add(&e->lru, &wbl.list);
		wbl.size++;
		e->ग_लिखो_in_progress = true;
		e->wc_list_contiguous = 1;

		f = e;

		जबतक (1) अणु
			next_node = rb_next(&f->rb_node);
			अगर (unlikely(!next_node))
				अवरोध;
			g = container_of(next_node, काष्ठा wc_entry, rb_node);
			अगर (unlikely(पढ़ो_original_sector(wc, g) ==
			    पढ़ो_original_sector(wc, f))) अणु
				f = g;
				जारी;
			पूर्ण
			अगर (पढ़ो_original_sector(wc, g) !=
			    पढ़ो_original_sector(wc, f) + (wc->block_size >> SECTOR_SHIFT))
				अवरोध;
			अगर (unlikely(g->ग_लिखो_in_progress))
				अवरोध;
			अगर (unlikely(!ग_लिखोcache_entry_is_committed(wc, g)))
				अवरोध;

			अगर (!WC_MODE_PMEM(wc)) अणु
				अगर (g != f + 1)
					अवरोध;
			पूर्ण

			n_walked++;
			//अगर (unlikely(n_walked > WRITEBACK_LATENCY) && likely(!wc->ग_लिखोback_all))
			//	अवरोध;

			wc->ग_लिखोback_size++;
			list_del(&g->lru);
			list_add(&g->lru, &wbl.list);
			wbl.size++;
			g->ग_लिखो_in_progress = true;
			g->wc_list_contiguous = BIO_MAX_VECS;
			f = g;
			e->wc_list_contiguous++;
			अगर (unlikely(e->wc_list_contiguous == BIO_MAX_VECS)) अणु
				अगर (unlikely(wc->ग_लिखोback_all)) अणु
					next_node = rb_next(&f->rb_node);
					अगर (likely(next_node))
						g = container_of(next_node, काष्ठा wc_entry, rb_node);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		cond_resched();
	पूर्ण

	अगर (!list_empty(&skipped)) अणु
		list_splice_tail(&skipped, &wc->lru);
		/*
		 * If we didn't करो any progress, we must रुको until some
		 * ग_लिखोback finishes to aव्योम burning CPU in a loop
		 */
		अगर (unlikely(!wbl.size))
			ग_लिखोcache_रुको_क्रम_ग_लिखोback(wc);
	पूर्ण

	wc_unlock(wc);

	blk_start_plug(&plug);

	अगर (WC_MODE_PMEM(wc))
		__ग_लिखोcache_ग_लिखोback_pmem(wc, &wbl);
	अन्यथा
		__ग_लिखोcache_ग_लिखोback_ssd(wc, &wbl);

	blk_finish_plug(&plug);

	अगर (unlikely(wc->ग_लिखोback_all)) अणु
		wc_lock(wc);
		जबतक (ग_लिखोcache_रुको_क्रम_ग_लिखोback(wc));
		wc_unlock(wc);
	पूर्ण
पूर्ण

अटल पूर्णांक calculate_memory_size(uपूर्णांक64_t device_size, अचिन्हित block_size,
				 माप_प्रकार *n_blocks_p, माप_प्रकार *n_metadata_blocks_p)
अणु
	uपूर्णांक64_t n_blocks, offset;
	काष्ठा wc_entry e;

	n_blocks = device_size;
	करो_भाग(n_blocks, block_size + माप(काष्ठा wc_memory_entry));

	जबतक (1) अणु
		अगर (!n_blocks)
			वापस -ENOSPC;
		/* Verअगरy the following entries[n_blocks] won't overflow */
		अगर (n_blocks >= ((माप_प्रकार)-माप(काष्ठा wc_memory_superblock) /
				 माप(काष्ठा wc_memory_entry)))
			वापस -EFBIG;
		offset = दुरत्व(काष्ठा wc_memory_superblock, entries[n_blocks]);
		offset = (offset + block_size - 1) & ~(uपूर्णांक64_t)(block_size - 1);
		अगर (offset + n_blocks * block_size <= device_size)
			अवरोध;
		n_blocks--;
	पूर्ण

	/* check अगर the bit field overflows */
	e.index = n_blocks;
	अगर (e.index != n_blocks)
		वापस -EFBIG;

	अगर (n_blocks_p)
		*n_blocks_p = n_blocks;
	अगर (n_metadata_blocks_p)
		*n_metadata_blocks_p = offset >> __ffs(block_size);
	वापस 0;
पूर्ण

अटल पूर्णांक init_memory(काष्ठा dm_ग_लिखोcache *wc)
अणु
	माप_प्रकार b;
	पूर्णांक r;

	r = calculate_memory_size(wc->memory_map_size, wc->block_size, &wc->n_blocks, शून्य);
	अगर (r)
		वापस r;

	r = ग_लिखोcache_alloc_entries(wc);
	अगर (r)
		वापस r;

	क्रम (b = 0; b < ARRAY_SIZE(sb(wc)->padding); b++)
		pmem_assign(sb(wc)->padding[b], cpu_to_le64(0));
	pmem_assign(sb(wc)->version, cpu_to_le32(MEMORY_SUPERBLOCK_VERSION));
	pmem_assign(sb(wc)->block_size, cpu_to_le32(wc->block_size));
	pmem_assign(sb(wc)->n_blocks, cpu_to_le64(wc->n_blocks));
	pmem_assign(sb(wc)->seq_count, cpu_to_le64(0));

	क्रम (b = 0; b < wc->n_blocks; b++) अणु
		ग_लिखो_original_sector_seq_count(wc, &wc->entries[b], -1, -1);
		cond_resched();
	पूर्ण

	ग_लिखोcache_flush_all_metadata(wc);
	ग_लिखोcache_commit_flushed(wc, false);
	pmem_assign(sb(wc)->magic, cpu_to_le32(MEMORY_SUPERBLOCK_MAGIC));
	ग_लिखोcache_flush_region(wc, &sb(wc)->magic, माप sb(wc)->magic);
	ग_लिखोcache_commit_flushed(wc, false);

	वापस 0;
पूर्ण

अटल व्योम ग_लिखोcache_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;

	अगर (!wc)
		वापस;

	अगर (wc->endio_thपढ़ो)
		kthपढ़ो_stop(wc->endio_thपढ़ो);

	अगर (wc->flush_thपढ़ो)
		kthपढ़ो_stop(wc->flush_thपढ़ो);

	bioset_निकास(&wc->bio_set);

	mempool_निकास(&wc->copy_pool);

	अगर (wc->ग_लिखोback_wq)
		destroy_workqueue(wc->ग_लिखोback_wq);

	अगर (wc->dev)
		dm_put_device(ti, wc->dev);

	अगर (wc->ssd_dev)
		dm_put_device(ti, wc->ssd_dev);

	vमुक्त(wc->entries);

	अगर (wc->memory_map) अणु
		अगर (WC_MODE_PMEM(wc))
			persistent_memory_release(wc);
		अन्यथा
			vमुक्त(wc->memory_map);
	पूर्ण

	अगर (wc->dm_kcopyd)
		dm_kcopyd_client_destroy(wc->dm_kcopyd);

	अगर (wc->dm_io)
		dm_io_client_destroy(wc->dm_io);

	vमुक्त(wc->dirty_biपंचांगap);

	kमुक्त(wc);
पूर्ण

अटल पूर्णांक ग_लिखोcache_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा dm_ग_लिखोcache *wc;
	काष्ठा dm_arg_set as;
	स्थिर अक्षर *string;
	अचिन्हित opt_params;
	माप_प्रकार offset, data_size;
	पूर्णांक i, r;
	अक्षर dummy;
	पूर्णांक high_wm_percent = HIGH_WATERMARK;
	पूर्णांक low_wm_percent = LOW_WATERMARK;
	uपूर्णांक64_t x;
	काष्ठा wc_memory_superblock s;

	अटल काष्ठा dm_arg _args[] = अणु
		अणु0, 16, "Invalid number of feature args"पूर्ण,
	पूर्ण;

	as.argc = argc;
	as.argv = argv;

	wc = kzalloc(माप(काष्ठा dm_ग_लिखोcache), GFP_KERNEL);
	अगर (!wc) अणु
		ti->error = "Cannot allocate writecache structure";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	ti->निजी = wc;
	wc->ti = ti;

	mutex_init(&wc->lock);
	wc->max_age = MAX_AGE_UNSPECIFIED;
	ग_लिखोcache_poison_lists(wc);
	init_रुकोqueue_head(&wc->मुक्तlist_रुको);
	समयr_setup(&wc->स्वतःcommit_समयr, ग_लिखोcache_स्वतःcommit_समयr, 0);
	समयr_setup(&wc->max_age_समयr, ग_लिखोcache_max_age_समयr, 0);

	क्रम (i = 0; i < 2; i++) अणु
		atomic_set(&wc->bio_in_progress[i], 0);
		init_रुकोqueue_head(&wc->bio_in_progress_रुको[i]);
	पूर्ण

	wc->dm_io = dm_io_client_create();
	अगर (IS_ERR(wc->dm_io)) अणु
		r = PTR_ERR(wc->dm_io);
		ti->error = "Unable to allocate dm-io client";
		wc->dm_io = शून्य;
		जाओ bad;
	पूर्ण

	wc->ग_लिखोback_wq = alloc_workqueue("writecache-writeback", WQ_MEM_RECLAIM, 1);
	अगर (!wc->ग_लिखोback_wq) अणु
		r = -ENOMEM;
		ti->error = "Could not allocate writeback workqueue";
		जाओ bad;
	पूर्ण
	INIT_WORK(&wc->ग_लिखोback_work, ग_लिखोcache_ग_लिखोback);
	INIT_WORK(&wc->flush_work, ग_लिखोcache_flush_work);

	raw_spin_lock_init(&wc->endio_list_lock);
	INIT_LIST_HEAD(&wc->endio_list);
	wc->endio_thपढ़ो = kthपढ़ो_create(ग_लिखोcache_endio_thपढ़ो, wc, "writecache_endio");
	अगर (IS_ERR(wc->endio_thपढ़ो)) अणु
		r = PTR_ERR(wc->endio_thपढ़ो);
		wc->endio_thपढ़ो = शून्य;
		ti->error = "Couldn't spawn endio thread";
		जाओ bad;
	पूर्ण
	wake_up_process(wc->endio_thपढ़ो);

	/*
	 * Parse the mode (pmem or ssd)
	 */
	string = dm_shअगरt_arg(&as);
	अगर (!string)
		जाओ bad_arguments;

	अगर (!strहालcmp(string, "s")) अणु
		wc->pmem_mode = false;
	पूर्ण अन्यथा अगर (!strहालcmp(string, "p")) अणु
#अगर_घोषित DM_WRITECACHE_HAS_PMEM
		wc->pmem_mode = true;
		wc->ग_लिखोback_fua = true;
#अन्यथा
		/*
		 * If the architecture करोesn't support persistent memory or
		 * the kernel करोesn't support any DAX drivers, this driver can
		 * only be used in SSD-only mode.
		 */
		r = -EOPNOTSUPP;
		ti->error = "Persistent memory or DAX not supported on this system";
		जाओ bad;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		जाओ bad_arguments;
	पूर्ण

	अगर (WC_MODE_PMEM(wc)) अणु
		r = bioset_init(&wc->bio_set, BIO_POOL_SIZE,
				दुरत्व(काष्ठा ग_लिखोback_काष्ठा, bio),
				BIOSET_NEED_BVECS);
		अगर (r) अणु
			ti->error = "Could not allocate bio set";
			जाओ bad;
		पूर्ण
	पूर्ण अन्यथा अणु
		r = mempool_init_kदो_स्मृति_pool(&wc->copy_pool, 1, माप(काष्ठा copy_काष्ठा));
		अगर (r) अणु
			ti->error = "Could not allocate mempool";
			जाओ bad;
		पूर्ण
	पूर्ण

	/*
	 * Parse the origin data device
	 */
	string = dm_shअगरt_arg(&as);
	अगर (!string)
		जाओ bad_arguments;
	r = dm_get_device(ti, string, dm_table_get_mode(ti->table), &wc->dev);
	अगर (r) अणु
		ti->error = "Origin data device lookup failed";
		जाओ bad;
	पूर्ण

	/*
	 * Parse cache data device (be it pmem or ssd)
	 */
	string = dm_shअगरt_arg(&as);
	अगर (!string)
		जाओ bad_arguments;

	r = dm_get_device(ti, string, dm_table_get_mode(ti->table), &wc->ssd_dev);
	अगर (r) अणु
		ti->error = "Cache data device lookup failed";
		जाओ bad;
	पूर्ण
	wc->memory_map_size = i_size_पढ़ो(wc->ssd_dev->bdev->bd_inode);

	/*
	 * Parse the cache block size
	 */
	string = dm_shअगरt_arg(&as);
	अगर (!string)
		जाओ bad_arguments;
	अगर (माला_पूछो(string, "%u%c", &wc->block_size, &dummy) != 1 ||
	    wc->block_size < 512 || wc->block_size > PAGE_SIZE ||
	    (wc->block_size & (wc->block_size - 1))) अणु
		r = -EINVAL;
		ti->error = "Invalid block size";
		जाओ bad;
	पूर्ण
	अगर (wc->block_size < bdev_logical_block_size(wc->dev->bdev) ||
	    wc->block_size < bdev_logical_block_size(wc->ssd_dev->bdev)) अणु
		r = -EINVAL;
		ti->error = "Block size is smaller than device logical block size";
		जाओ bad;
	पूर्ण
	wc->block_size_bits = __ffs(wc->block_size);

	wc->max_ग_लिखोback_jobs = MAX_WRITEBACK_JOBS;
	wc->स्वतःcommit_blocks = !WC_MODE_PMEM(wc) ? AUTOCOMMIT_BLOCKS_SSD : AUTOCOMMIT_BLOCKS_PMEM;
	wc->स्वतःcommit_jअगरfies = msecs_to_jअगरfies(AUTOCOMMIT_MSEC);

	/*
	 * Parse optional arguments
	 */
	r = dm_पढ़ो_arg_group(_args, &as, &opt_params, &ti->error);
	अगर (r)
		जाओ bad;

	जबतक (opt_params) अणु
		string = dm_shअगरt_arg(&as), opt_params--;
		अगर (!strहालcmp(string, "start_sector") && opt_params >= 1) अणु
			अचिन्हित दीर्घ दीर्घ start_sector;
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%llu%c", &start_sector, &dummy) != 1)
				जाओ invalid_optional;
			wc->start_sector = start_sector;
			wc->start_sector_set = true;
			अगर (wc->start_sector != start_sector ||
			    wc->start_sector >= wc->memory_map_size >> SECTOR_SHIFT)
				जाओ invalid_optional;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "high_watermark") && opt_params >= 1) अणु
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%d%c", &high_wm_percent, &dummy) != 1)
				जाओ invalid_optional;
			अगर (high_wm_percent < 0 || high_wm_percent > 100)
				जाओ invalid_optional;
			wc->high_wm_percent_value = high_wm_percent;
			wc->high_wm_percent_set = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "low_watermark") && opt_params >= 1) अणु
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%d%c", &low_wm_percent, &dummy) != 1)
				जाओ invalid_optional;
			अगर (low_wm_percent < 0 || low_wm_percent > 100)
				जाओ invalid_optional;
			wc->low_wm_percent_value = low_wm_percent;
			wc->low_wm_percent_set = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "writeback_jobs") && opt_params >= 1) अणु
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%u%c", &wc->max_ग_लिखोback_jobs, &dummy) != 1)
				जाओ invalid_optional;
			wc->max_ग_लिखोback_jobs_set = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "autocommit_blocks") && opt_params >= 1) अणु
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%u%c", &wc->स्वतःcommit_blocks, &dummy) != 1)
				जाओ invalid_optional;
			wc->स्वतःcommit_blocks_set = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "autocommit_time") && opt_params >= 1) अणु
			अचिन्हित स्वतःcommit_msecs;
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%u%c", &स्वतःcommit_msecs, &dummy) != 1)
				जाओ invalid_optional;
			अगर (स्वतःcommit_msecs > 3600000)
				जाओ invalid_optional;
			wc->स्वतःcommit_jअगरfies = msecs_to_jअगरfies(स्वतःcommit_msecs);
			wc->स्वतःcommit_समय_value = स्वतःcommit_msecs;
			wc->स्वतःcommit_समय_set = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "max_age") && opt_params >= 1) अणु
			अचिन्हित max_age_msecs;
			string = dm_shअगरt_arg(&as), opt_params--;
			अगर (माला_पूछो(string, "%u%c", &max_age_msecs, &dummy) != 1)
				जाओ invalid_optional;
			अगर (max_age_msecs > 86400000)
				जाओ invalid_optional;
			wc->max_age = msecs_to_jअगरfies(max_age_msecs);
			wc->max_age_set = true;
			wc->max_age_value = max_age_msecs;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "cleaner")) अणु
			wc->cleaner_set = true;
			wc->cleaner = true;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "fua")) अणु
			अगर (WC_MODE_PMEM(wc)) अणु
				wc->ग_लिखोback_fua = true;
				wc->ग_लिखोback_fua_set = true;
			पूर्ण अन्यथा जाओ invalid_optional;
		पूर्ण अन्यथा अगर (!strहालcmp(string, "nofua")) अणु
			अगर (WC_MODE_PMEM(wc)) अणु
				wc->ग_लिखोback_fua = false;
				wc->ग_लिखोback_fua_set = true;
			पूर्ण अन्यथा जाओ invalid_optional;
		पूर्ण अन्यथा अणु
invalid_optional:
			r = -EINVAL;
			ti->error = "Invalid optional argument";
			जाओ bad;
		पूर्ण
	पूर्ण

	अगर (high_wm_percent < low_wm_percent) अणु
		r = -EINVAL;
		ti->error = "High watermark must be greater than or equal to low watermark";
		जाओ bad;
	पूर्ण

	अगर (WC_MODE_PMEM(wc)) अणु
		अगर (!dax_synchronous(wc->ssd_dev->dax_dev)) अणु
			r = -EOPNOTSUPP;
			ti->error = "Asynchronous persistent memory not supported as pmem cache";
			जाओ bad;
		पूर्ण

		r = persistent_memory_claim(wc);
		अगर (r) अणु
			ti->error = "Unable to map persistent memory for cache";
			जाओ bad;
		पूर्ण
	पूर्ण अन्यथा अणु
		माप_प्रकार n_blocks, n_metadata_blocks;
		uपूर्णांक64_t n_biपंचांगap_bits;

		wc->memory_map_size -= (uपूर्णांक64_t)wc->start_sector << SECTOR_SHIFT;

		bio_list_init(&wc->flush_list);
		wc->flush_thपढ़ो = kthपढ़ो_create(ग_लिखोcache_flush_thपढ़ो, wc, "dm_writecache_flush");
		अगर (IS_ERR(wc->flush_thपढ़ो)) अणु
			r = PTR_ERR(wc->flush_thपढ़ो);
			wc->flush_thपढ़ो = शून्य;
			ti->error = "Couldn't spawn flush thread";
			जाओ bad;
		पूर्ण
		wake_up_process(wc->flush_thपढ़ो);

		r = calculate_memory_size(wc->memory_map_size, wc->block_size,
					  &n_blocks, &n_metadata_blocks);
		अगर (r) अणु
			ti->error = "Invalid device size";
			जाओ bad;
		पूर्ण

		n_biपंचांगap_bits = (((uपूर्णांक64_t)n_metadata_blocks << wc->block_size_bits) +
				 BITMAP_GRANULARITY - 1) / BITMAP_GRANULARITY;
		/* this is limitation of test_bit functions */
		अगर (n_biपंचांगap_bits > 1U << 31) अणु
			r = -EFBIG;
			ti->error = "Invalid device size";
			जाओ bad;
		पूर्ण

		wc->memory_map = vदो_स्मृति(n_metadata_blocks << wc->block_size_bits);
		अगर (!wc->memory_map) अणु
			r = -ENOMEM;
			ti->error = "Unable to allocate memory for metadata";
			जाओ bad;
		पूर्ण

		wc->dm_kcopyd = dm_kcopyd_client_create(&dm_kcopyd_throttle);
		अगर (IS_ERR(wc->dm_kcopyd)) अणु
			r = PTR_ERR(wc->dm_kcopyd);
			ti->error = "Unable to allocate dm-kcopyd client";
			wc->dm_kcopyd = शून्य;
			जाओ bad;
		पूर्ण

		wc->metadata_sectors = n_metadata_blocks << (wc->block_size_bits - SECTOR_SHIFT);
		wc->dirty_biपंचांगap_size = (n_biपंचांगap_bits + BITS_PER_LONG - 1) /
			BITS_PER_LONG * माप(अचिन्हित दीर्घ);
		wc->dirty_biपंचांगap = vzalloc(wc->dirty_biपंचांगap_size);
		अगर (!wc->dirty_biपंचांगap) अणु
			r = -ENOMEM;
			ti->error = "Unable to allocate dirty bitmap";
			जाओ bad;
		पूर्ण

		r = ग_लिखोcache_पढ़ो_metadata(wc, wc->block_size >> SECTOR_SHIFT);
		अगर (r) अणु
			ti->error = "Unable to read first block of metadata";
			जाओ bad;
		पूर्ण
	पूर्ण

	r = copy_mc_to_kernel(&s, sb(wc), माप(काष्ठा wc_memory_superblock));
	अगर (r) अणु
		ti->error = "Hardware memory error when reading superblock";
		जाओ bad;
	पूर्ण
	अगर (!le32_to_cpu(s.magic) && !le32_to_cpu(s.version)) अणु
		r = init_memory(wc);
		अगर (r) अणु
			ti->error = "Unable to initialize device";
			जाओ bad;
		पूर्ण
		r = copy_mc_to_kernel(&s, sb(wc),
				      माप(काष्ठा wc_memory_superblock));
		अगर (r) अणु
			ti->error = "Hardware memory error when reading superblock";
			जाओ bad;
		पूर्ण
	पूर्ण

	अगर (le32_to_cpu(s.magic) != MEMORY_SUPERBLOCK_MAGIC) अणु
		ti->error = "Invalid magic in the superblock";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (le32_to_cpu(s.version) != MEMORY_SUPERBLOCK_VERSION) अणु
		ti->error = "Invalid version in the superblock";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (le32_to_cpu(s.block_size) != wc->block_size) अणु
		ti->error = "Block size does not match superblock";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	wc->n_blocks = le64_to_cpu(s.n_blocks);

	offset = wc->n_blocks * माप(काष्ठा wc_memory_entry);
	अगर (offset / माप(काष्ठा wc_memory_entry) != le64_to_cpu(sb(wc)->n_blocks)) अणु
overflow:
		ti->error = "Overflow in size calculation";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	offset += माप(काष्ठा wc_memory_superblock);
	अगर (offset < माप(काष्ठा wc_memory_superblock))
		जाओ overflow;
	offset = (offset + wc->block_size - 1) & ~(माप_प्रकार)(wc->block_size - 1);
	data_size = wc->n_blocks * (माप_प्रकार)wc->block_size;
	अगर (!offset || (data_size / wc->block_size != wc->n_blocks) ||
	    (offset + data_size < offset))
		जाओ overflow;
	अगर (offset + data_size > wc->memory_map_size) अणु
		ti->error = "Memory area is too small";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	wc->metadata_sectors = offset >> SECTOR_SHIFT;
	wc->block_start = (अक्षर *)sb(wc) + offset;

	x = (uपूर्णांक64_t)wc->n_blocks * (100 - high_wm_percent);
	x += 50;
	करो_भाग(x, 100);
	wc->मुक्तlist_high_watermark = x;
	x = (uपूर्णांक64_t)wc->n_blocks * (100 - low_wm_percent);
	x += 50;
	करो_भाग(x, 100);
	wc->मुक्तlist_low_watermark = x;

	अगर (wc->cleaner)
		activate_cleaner(wc);

	r = ग_लिखोcache_alloc_entries(wc);
	अगर (r) अणु
		ti->error = "Cannot allocate memory";
		जाओ bad;
	पूर्ण

	ti->num_flush_bios = 1;
	ti->flush_supported = true;
	ti->num_discard_bios = 1;

	अगर (WC_MODE_PMEM(wc))
		persistent_memory_flush_cache(wc->memory_map, wc->memory_map_size);

	वापस 0;

bad_arguments:
	r = -EINVAL;
	ti->error = "Bad arguments";
bad:
	ग_लिखोcache_dtr(ti);
	वापस r;
पूर्ण

अटल व्योम ग_लिखोcache_status(काष्ठा dm_target *ti, status_type_t type,
			      अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा dm_ग_लिखोcache *wc = ti->निजी;
	अचिन्हित extra_args;
	अचिन्हित sz = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%ld %llu %llu %llu", ग_लिखोcache_has_error(wc),
		       (अचिन्हित दीर्घ दीर्घ)wc->n_blocks, (अचिन्हित दीर्घ दीर्घ)wc->मुक्तlist_size,
		       (अचिन्हित दीर्घ दीर्घ)wc->ग_लिखोback_size);
		अवरोध;
	हाल STATUSTYPE_TABLE:
		DMEMIT("%c %s %s %u ", WC_MODE_PMEM(wc) ? 'p' : 's',
				wc->dev->name, wc->ssd_dev->name, wc->block_size);
		extra_args = 0;
		अगर (wc->start_sector_set)
			extra_args += 2;
		अगर (wc->high_wm_percent_set)
			extra_args += 2;
		अगर (wc->low_wm_percent_set)
			extra_args += 2;
		अगर (wc->max_ग_लिखोback_jobs_set)
			extra_args += 2;
		अगर (wc->स्वतःcommit_blocks_set)
			extra_args += 2;
		अगर (wc->स्वतःcommit_समय_set)
			extra_args += 2;
		अगर (wc->max_age_set)
			extra_args += 2;
		अगर (wc->cleaner_set)
			extra_args++;
		अगर (wc->ग_लिखोback_fua_set)
			extra_args++;

		DMEMIT("%u", extra_args);
		अगर (wc->start_sector_set)
			DMEMIT(" start_sector %llu", (अचिन्हित दीर्घ दीर्घ)wc->start_sector);
		अगर (wc->high_wm_percent_set)
			DMEMIT(" high_watermark %u", wc->high_wm_percent_value);
		अगर (wc->low_wm_percent_set)
			DMEMIT(" low_watermark %u", wc->low_wm_percent_value);
		अगर (wc->max_ग_लिखोback_jobs_set)
			DMEMIT(" writeback_jobs %u", wc->max_ग_लिखोback_jobs);
		अगर (wc->स्वतःcommit_blocks_set)
			DMEMIT(" autocommit_blocks %u", wc->स्वतःcommit_blocks);
		अगर (wc->स्वतःcommit_समय_set)
			DMEMIT(" autocommit_time %u", wc->स्वतःcommit_समय_value);
		अगर (wc->max_age_set)
			DMEMIT(" max_age %u", wc->max_age_value);
		अगर (wc->cleaner_set)
			DMEMIT(" cleaner");
		अगर (wc->ग_लिखोback_fua_set)
			DMEMIT(" %sfua", wc->ग_लिखोback_fua ? "" : "no");
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा target_type ग_लिखोcache_target = अणु
	.name			= "writecache",
	.version		= अणु1, 4, 0पूर्ण,
	.module			= THIS_MODULE,
	.ctr			= ग_लिखोcache_ctr,
	.dtr			= ग_लिखोcache_dtr,
	.status			= ग_लिखोcache_status,
	.postsuspend		= ग_लिखोcache_suspend,
	.resume			= ग_लिखोcache_resume,
	.message		= ग_लिखोcache_message,
	.map			= ग_लिखोcache_map,
	.end_io			= ग_लिखोcache_end_io,
	.iterate_devices	= ग_लिखोcache_iterate_devices,
	.io_hपूर्णांकs		= ग_लिखोcache_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_ग_लिखोcache_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&ग_लिखोcache_target);
	अगर (r < 0) अणु
		DMERR("register failed %d", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dm_ग_लिखोcache_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&ग_लिखोcache_target);
पूर्ण

module_init(dm_ग_लिखोcache_init);
module_निकास(dm_ग_लिखोcache_निकास);

MODULE_DESCRIPTION(DM_NAME " writecache target");
MODULE_AUTHOR("Mikulas Patocka <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
