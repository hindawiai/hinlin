<शैली गुरु>
/*
 * Compressed RAM block device
 *
 * Copyright (C) 2008, 2009, 2010  Nitin Gupta
 *               2012, 2013 Minchan Kim
 *
 * This code is released using a dual license strategy: BSD/GPL
 * You can choose the licence that better fits your requirements.
 *
 * Released under the terms of 3-clause BSD License
 * Released under the terms of GNU General Public License Version 2.0
 *
 */

#घोषणा KMSG_COMPONENT "zram"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bपन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/device.h>
#समावेश <linux/genhd.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/err.h>
#समावेश <linux/idr.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/part_स्थिति.स>

#समावेश "zram_drv.h"

अटल DEFINE_IDR(zram_index_idr);
/* idr index must be रक्षित */
अटल DEFINE_MUTEX(zram_index_mutex);

अटल पूर्णांक zram_major;
अटल स्थिर अक्षर *शेष_compressor = CONFIG_ZRAM_DEF_COMP;

/* Module params (करोcumentation at end) */
अटल अचिन्हित पूर्णांक num_devices = 1;
/*
 * Pages that compress to sizes equals or greater than this are stored
 * uncompressed in memory.
 */
अटल माप_प्रकार huge_class_size;

अटल स्थिर काष्ठा block_device_operations zram_devops;
अटल स्थिर काष्ठा block_device_operations zram_wb_devops;

अटल व्योम zram_मुक्त_page(काष्ठा zram *zram, माप_प्रकार index);
अटल पूर्णांक zram_bvec_पढ़ो(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				u32 index, पूर्णांक offset, काष्ठा bio *bio);


अटल पूर्णांक zram_slot_trylock(काष्ठा zram *zram, u32 index)
अणु
	वापस bit_spin_trylock(ZRAM_LOCK, &zram->table[index].flags);
पूर्ण

अटल व्योम zram_slot_lock(काष्ठा zram *zram, u32 index)
अणु
	bit_spin_lock(ZRAM_LOCK, &zram->table[index].flags);
पूर्ण

अटल व्योम zram_slot_unlock(काष्ठा zram *zram, u32 index)
अणु
	bit_spin_unlock(ZRAM_LOCK, &zram->table[index].flags);
पूर्ण

अटल अंतरभूत bool init_करोne(काष्ठा zram *zram)
अणु
	वापस zram->disksize;
पूर्ण

अटल अंतरभूत काष्ठा zram *dev_to_zram(काष्ठा device *dev)
अणु
	वापस (काष्ठा zram *)dev_to_disk(dev)->निजी_data;
पूर्ण

अटल अचिन्हित दीर्घ zram_get_handle(काष्ठा zram *zram, u32 index)
अणु
	वापस zram->table[index].handle;
पूर्ण

अटल व्योम zram_set_handle(काष्ठा zram *zram, u32 index, अचिन्हित दीर्घ handle)
अणु
	zram->table[index].handle = handle;
पूर्ण

/* flag operations require table entry bit_spin_lock() being held */
अटल bool zram_test_flag(काष्ठा zram *zram, u32 index,
			क्रमागत zram_pageflags flag)
अणु
	वापस zram->table[index].flags & BIT(flag);
पूर्ण

अटल व्योम zram_set_flag(काष्ठा zram *zram, u32 index,
			क्रमागत zram_pageflags flag)
अणु
	zram->table[index].flags |= BIT(flag);
पूर्ण

अटल व्योम zram_clear_flag(काष्ठा zram *zram, u32 index,
			क्रमागत zram_pageflags flag)
अणु
	zram->table[index].flags &= ~BIT(flag);
पूर्ण

अटल अंतरभूत व्योम zram_set_element(काष्ठा zram *zram, u32 index,
			अचिन्हित दीर्घ element)
अणु
	zram->table[index].element = element;
पूर्ण

अटल अचिन्हित दीर्घ zram_get_element(काष्ठा zram *zram, u32 index)
अणु
	वापस zram->table[index].element;
पूर्ण

अटल माप_प्रकार zram_get_obj_size(काष्ठा zram *zram, u32 index)
अणु
	वापस zram->table[index].flags & (BIT(ZRAM_FLAG_SHIFT) - 1);
पूर्ण

अटल व्योम zram_set_obj_size(काष्ठा zram *zram,
					u32 index, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags = zram->table[index].flags >> ZRAM_FLAG_SHIFT;

	zram->table[index].flags = (flags << ZRAM_FLAG_SHIFT) | size;
पूर्ण

अटल अंतरभूत bool zram_allocated(काष्ठा zram *zram, u32 index)
अणु
	वापस zram_get_obj_size(zram, index) ||
			zram_test_flag(zram, index, ZRAM_SAME) ||
			zram_test_flag(zram, index, ZRAM_WB);
पूर्ण

#अगर PAGE_SIZE != 4096
अटल अंतरभूत bool is_partial_io(काष्ठा bio_vec *bvec)
अणु
	वापस bvec->bv_len != PAGE_SIZE;
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_partial_io(काष्ठा bio_vec *bvec)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Check अगर request is within bounds and aligned on zram logical blocks.
 */
अटल अंतरभूत bool valid_io_request(काष्ठा zram *zram,
		sector_t start, अचिन्हित पूर्णांक size)
अणु
	u64 end, bound;

	/* unaligned request */
	अगर (unlikely(start & (ZRAM_SECTOR_PER_LOGICAL_BLOCK - 1)))
		वापस false;
	अगर (unlikely(size & (ZRAM_LOGICAL_BLOCK_SIZE - 1)))
		वापस false;

	end = start + (size >> SECTOR_SHIFT);
	bound = zram->disksize >> SECTOR_SHIFT;
	/* out of range range */
	अगर (unlikely(start >= bound || end > bound || start > end))
		वापस false;

	/* I/O request is valid */
	वापस true;
पूर्ण

अटल व्योम update_position(u32 *index, पूर्णांक *offset, काष्ठा bio_vec *bvec)
अणु
	*index  += (*offset + bvec->bv_len) / PAGE_SIZE;
	*offset = (*offset + bvec->bv_len) % PAGE_SIZE;
पूर्ण

अटल अंतरभूत व्योम update_used_max(काष्ठा zram *zram,
					स्थिर अचिन्हित दीर्घ pages)
अणु
	अचिन्हित दीर्घ old_max, cur_max;

	old_max = atomic_दीर्घ_पढ़ो(&zram->stats.max_used_pages);

	करो अणु
		cur_max = old_max;
		अगर (pages > cur_max)
			old_max = atomic_दीर्घ_cmpxchg(
				&zram->stats.max_used_pages, cur_max, pages);
	पूर्ण जबतक (old_max != cur_max);
पूर्ण

अटल अंतरभूत व्योम zram_fill_page(व्योम *ptr, अचिन्हित दीर्घ len,
					अचिन्हित दीर्घ value)
अणु
	WARN_ON_ONCE(!IS_ALIGNED(len, माप(अचिन्हित दीर्घ)));
	स_रखो_l(ptr, value, len / माप(अचिन्हित दीर्घ));
पूर्ण

अटल bool page_same_filled(व्योम *ptr, अचिन्हित दीर्घ *element)
अणु
	अचिन्हित दीर्घ *page;
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक pos, last_pos = PAGE_SIZE / माप(*page) - 1;

	page = (अचिन्हित दीर्घ *)ptr;
	val = page[0];

	अगर (val != page[last_pos])
		वापस false;

	क्रम (pos = 1; pos < last_pos; pos++) अणु
		अगर (val != page[pos])
			वापस false;
	पूर्ण

	*element = val;

	वापस true;
पूर्ण

अटल sमाप_प्रकार initstate_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 val;
	काष्ठा zram *zram = dev_to_zram(dev);

	करोwn_पढ़ो(&zram->init_lock);
	val = init_करोne(zram);
	up_पढ़ो(&zram->init_lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार disksize_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", zram->disksize);
पूर्ण

अटल sमाप_प्रकार mem_limit_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	u64 limit;
	अक्षर *पंचांगp;
	काष्ठा zram *zram = dev_to_zram(dev);

	limit = memparse(buf, &पंचांगp);
	अगर (buf == पंचांगp) /* no अक्षरs parsed, invalid input */
		वापस -EINVAL;

	करोwn_ग_लिखो(&zram->init_lock);
	zram->limit_pages = PAGE_ALIGN(limit) >> PAGE_SHIFT;
	up_ग_लिखो(&zram->init_lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार mem_used_max_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ val;
	काष्ठा zram *zram = dev_to_zram(dev);

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err || val != 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&zram->init_lock);
	अगर (init_करोne(zram)) अणु
		atomic_दीर्घ_set(&zram->stats.max_used_pages,
				zs_get_total_pages(zram->mem_pool));
	पूर्ण
	up_पढ़ो(&zram->init_lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार idle_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	अचिन्हित दीर्घ nr_pages = zram->disksize >> PAGE_SHIFT;
	पूर्णांक index;

	अगर (!sysfs_streq(buf, "all"))
		वापस -EINVAL;

	करोwn_पढ़ो(&zram->init_lock);
	अगर (!init_करोne(zram)) अणु
		up_पढ़ो(&zram->init_lock);
		वापस -EINVAL;
	पूर्ण

	क्रम (index = 0; index < nr_pages; index++) अणु
		/*
		 * Do not mark ZRAM_UNDER_WB slot as ZRAM_IDLE to बंद race.
		 * See the comment in ग_लिखोback_store.
		 */
		zram_slot_lock(zram, index);
		अगर (zram_allocated(zram, index) &&
				!zram_test_flag(zram, index, ZRAM_UNDER_WB))
			zram_set_flag(zram, index, ZRAM_IDLE);
		zram_slot_unlock(zram, index);
	पूर्ण

	up_पढ़ो(&zram->init_lock);

	वापस len;
पूर्ण

#अगर_घोषित CONFIG_ZRAM_WRITEBACK
अटल sमाप_प्रकार ग_लिखोback_limit_enable_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	u64 val;
	sमाप_प्रकार ret = -EINVAL;

	अगर (kम_से_अदीर्घl(buf, 10, &val))
		वापस ret;

	करोwn_पढ़ो(&zram->init_lock);
	spin_lock(&zram->wb_limit_lock);
	zram->wb_limit_enable = val;
	spin_unlock(&zram->wb_limit_lock);
	up_पढ़ो(&zram->init_lock);
	ret = len;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ग_लिखोback_limit_enable_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	bool val;
	काष्ठा zram *zram = dev_to_zram(dev);

	करोwn_पढ़ो(&zram->init_lock);
	spin_lock(&zram->wb_limit_lock);
	val = zram->wb_limit_enable;
	spin_unlock(&zram->wb_limit_lock);
	up_पढ़ो(&zram->init_lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार ग_लिखोback_limit_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	u64 val;
	sमाप_प्रकार ret = -EINVAL;

	अगर (kम_से_अदीर्घl(buf, 10, &val))
		वापस ret;

	करोwn_पढ़ो(&zram->init_lock);
	spin_lock(&zram->wb_limit_lock);
	zram->bd_wb_limit = val;
	spin_unlock(&zram->wb_limit_lock);
	up_पढ़ो(&zram->init_lock);
	ret = len;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ग_लिखोback_limit_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u64 val;
	काष्ठा zram *zram = dev_to_zram(dev);

	करोwn_पढ़ो(&zram->init_lock);
	spin_lock(&zram->wb_limit_lock);
	val = zram->bd_wb_limit;
	spin_unlock(&zram->wb_limit_lock);
	up_पढ़ो(&zram->init_lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", val);
पूर्ण

अटल व्योम reset_bdev(काष्ठा zram *zram)
अणु
	काष्ठा block_device *bdev;

	अगर (!zram->backing_dev)
		वापस;

	bdev = zram->bdev;
	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
	/* hope filp_बंद flush all of IO */
	filp_बंद(zram->backing_dev, शून्य);
	zram->backing_dev = शून्य;
	zram->bdev = शून्य;
	zram->disk->fops = &zram_devops;
	kvमुक्त(zram->biपंचांगap);
	zram->biपंचांगap = शून्य;
पूर्ण

अटल sमाप_प्रकार backing_dev_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा file *file;
	काष्ठा zram *zram = dev_to_zram(dev);
	अक्षर *p;
	sमाप_प्रकार ret;

	करोwn_पढ़ो(&zram->init_lock);
	file = zram->backing_dev;
	अगर (!file) अणु
		स_नकल(buf, "none\n", 5);
		up_पढ़ो(&zram->init_lock);
		वापस 5;
	पूर्ण

	p = file_path(file, buf, PAGE_SIZE - 1);
	अगर (IS_ERR(p)) अणु
		ret = PTR_ERR(p);
		जाओ out;
	पूर्ण

	ret = म_माप(p);
	स_हटाओ(buf, p, ret);
	buf[ret++] = '\n';
out:
	up_पढ़ो(&zram->init_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार backing_dev_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर *file_name;
	माप_प्रकार sz;
	काष्ठा file *backing_dev = शून्य;
	काष्ठा inode *inode;
	काष्ठा address_space *mapping;
	अचिन्हित पूर्णांक biपंचांगap_sz;
	अचिन्हित दीर्घ nr_pages, *biपंचांगap = शून्य;
	काष्ठा block_device *bdev = शून्य;
	पूर्णांक err;
	काष्ठा zram *zram = dev_to_zram(dev);

	file_name = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!file_name)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&zram->init_lock);
	अगर (init_करोne(zram)) अणु
		pr_info("Can't setup backing device for initialized device\n");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	strlcpy(file_name, buf, PATH_MAX);
	/* ignore trailing newline */
	sz = म_माप(file_name);
	अगर (sz > 0 && file_name[sz - 1] == '\n')
		file_name[sz - 1] = 0x00;

	backing_dev = filp_खोलो(file_name, O_RDWR|O_LARGEखाता, 0);
	अगर (IS_ERR(backing_dev)) अणु
		err = PTR_ERR(backing_dev);
		backing_dev = शून्य;
		जाओ out;
	पूर्ण

	mapping = backing_dev->f_mapping;
	inode = mapping->host;

	/* Support only block device in this moment */
	अगर (!S_ISBLK(inode->i_mode)) अणु
		err = -ENOTBLK;
		जाओ out;
	पूर्ण

	bdev = blkdev_get_by_dev(inode->i_rdev,
			FMODE_READ | FMODE_WRITE | FMODE_EXCL, zram);
	अगर (IS_ERR(bdev)) अणु
		err = PTR_ERR(bdev);
		bdev = शून्य;
		जाओ out;
	पूर्ण

	nr_pages = i_size_पढ़ो(inode) >> PAGE_SHIFT;
	biपंचांगap_sz = BITS_TO_LONGS(nr_pages) * माप(दीर्घ);
	biपंचांगap = kvzalloc(biपंचांगap_sz, GFP_KERNEL);
	अगर (!biपंचांगap) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	reset_bdev(zram);

	zram->bdev = bdev;
	zram->backing_dev = backing_dev;
	zram->biपंचांगap = biपंचांगap;
	zram->nr_pages = nr_pages;
	/*
	 * With ग_लिखोback feature, zram करोes asynchronous IO so it's no दीर्घer
	 * synchronous device so let's हटाओ synchronous io flag. Othewise,
	 * upper layer(e.g., swap) could रुको IO completion rather than
	 * (submit and वापस), which will cause प्रणाली sluggish.
	 * Furthermore, when the IO function वापसs(e.g., swap_पढ़ोpage),
	 * upper layer expects IO was करोne so it could deallocate the page
	 * मुक्तly but in fact, IO is going on so finally could cause
	 * use-after-मुक्त when the IO is really करोne.
	 */
	zram->disk->fops = &zram_wb_devops;
	up_ग_लिखो(&zram->init_lock);

	pr_info("setup backing device %s\n", file_name);
	kमुक्त(file_name);

	वापस len;
out:
	kvमुक्त(biपंचांगap);

	अगर (bdev)
		blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);

	अगर (backing_dev)
		filp_बंद(backing_dev, शून्य);

	up_ग_लिखो(&zram->init_lock);

	kमुक्त(file_name);

	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ alloc_block_bdev(काष्ठा zram *zram)
अणु
	अचिन्हित दीर्घ blk_idx = 1;
retry:
	/* skip 0 bit to confuse zram.handle = 0 */
	blk_idx = find_next_zero_bit(zram->biपंचांगap, zram->nr_pages, blk_idx);
	अगर (blk_idx == zram->nr_pages)
		वापस 0;

	अगर (test_and_set_bit(blk_idx, zram->biपंचांगap))
		जाओ retry;

	atomic64_inc(&zram->stats.bd_count);
	वापस blk_idx;
पूर्ण

अटल व्योम मुक्त_block_bdev(काष्ठा zram *zram, अचिन्हित दीर्घ blk_idx)
अणु
	पूर्णांक was_set;

	was_set = test_and_clear_bit(blk_idx, zram->biपंचांगap);
	WARN_ON_ONCE(!was_set);
	atomic64_dec(&zram->stats.bd_count);
पूर्ण

अटल व्योम zram_page_end_io(काष्ठा bio *bio)
अणु
	काष्ठा page *page = bio_first_page_all(bio);

	page_endio(page, op_is_ग_लिखो(bio_op(bio)),
			blk_status_to_त्रुटि_सं(bio->bi_status));
	bio_put(bio);
पूर्ण

/*
 * Returns 1 अगर the submission is successful.
 */
अटल पूर्णांक पढ़ो_from_bdev_async(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
			अचिन्हित दीर्घ entry, काष्ठा bio *parent)
अणु
	काष्ठा bio *bio;

	bio = bio_alloc(GFP_ATOMIC, 1);
	अगर (!bio)
		वापस -ENOMEM;

	bio->bi_iter.bi_sector = entry * (PAGE_SIZE >> 9);
	bio_set_dev(bio, zram->bdev);
	अगर (!bio_add_page(bio, bvec->bv_page, bvec->bv_len, bvec->bv_offset)) अणु
		bio_put(bio);
		वापस -EIO;
	पूर्ण

	अगर (!parent) अणु
		bio->bi_opf = REQ_OP_READ;
		bio->bi_end_io = zram_page_end_io;
	पूर्ण अन्यथा अणु
		bio->bi_opf = parent->bi_opf;
		bio_chain(bio, parent);
	पूर्ण

	submit_bio(bio);
	वापस 1;
पूर्ण

#घोषणा PAGE_WB_SIG "page_index="

#घोषणा PAGE_WRITEBACK 0
#घोषणा HUGE_WRITEBACK 1
#घोषणा IDLE_WRITEBACK 2


अटल sमाप_प्रकार ग_लिखोback_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	अचिन्हित दीर्घ nr_pages = zram->disksize >> PAGE_SHIFT;
	अचिन्हित दीर्घ index = 0;
	काष्ठा bio bio;
	काष्ठा bio_vec bio_vec;
	काष्ठा page *page;
	sमाप_प्रकार ret = len;
	पूर्णांक mode, err;
	अचिन्हित दीर्घ blk_idx = 0;

	अगर (sysfs_streq(buf, "idle"))
		mode = IDLE_WRITEBACK;
	अन्यथा अगर (sysfs_streq(buf, "huge"))
		mode = HUGE_WRITEBACK;
	अन्यथा अणु
		अगर (म_भेदन(buf, PAGE_WB_SIG, माप(PAGE_WB_SIG) - 1))
			वापस -EINVAL;

		अगर (kम_से_दीर्घ(buf + माप(PAGE_WB_SIG) - 1, 10, &index) ||
				index >= nr_pages)
			वापस -EINVAL;

		nr_pages = 1;
		mode = PAGE_WRITEBACK;
	पूर्ण

	करोwn_पढ़ो(&zram->init_lock);
	अगर (!init_करोne(zram)) अणु
		ret = -EINVAL;
		जाओ release_init_lock;
	पूर्ण

	अगर (!zram->backing_dev) अणु
		ret = -ENODEV;
		जाओ release_init_lock;
	पूर्ण

	page = alloc_page(GFP_KERNEL);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ release_init_lock;
	पूर्ण

	क्रम (; nr_pages != 0; index++, nr_pages--) अणु
		काष्ठा bio_vec bvec;

		bvec.bv_page = page;
		bvec.bv_len = PAGE_SIZE;
		bvec.bv_offset = 0;

		spin_lock(&zram->wb_limit_lock);
		अगर (zram->wb_limit_enable && !zram->bd_wb_limit) अणु
			spin_unlock(&zram->wb_limit_lock);
			ret = -EIO;
			अवरोध;
		पूर्ण
		spin_unlock(&zram->wb_limit_lock);

		अगर (!blk_idx) अणु
			blk_idx = alloc_block_bdev(zram);
			अगर (!blk_idx) अणु
				ret = -ENOSPC;
				अवरोध;
			पूर्ण
		पूर्ण

		zram_slot_lock(zram, index);
		अगर (!zram_allocated(zram, index))
			जाओ next;

		अगर (zram_test_flag(zram, index, ZRAM_WB) ||
				zram_test_flag(zram, index, ZRAM_SAME) ||
				zram_test_flag(zram, index, ZRAM_UNDER_WB))
			जाओ next;

		अगर (mode == IDLE_WRITEBACK &&
			  !zram_test_flag(zram, index, ZRAM_IDLE))
			जाओ next;
		अगर (mode == HUGE_WRITEBACK &&
			  !zram_test_flag(zram, index, ZRAM_HUGE))
			जाओ next;
		/*
		 * Clearing ZRAM_UNDER_WB is duty of caller.
		 * IOW, zram_मुक्त_page never clear it.
		 */
		zram_set_flag(zram, index, ZRAM_UNDER_WB);
		/* Need क्रम hugepage ग_लिखोback racing */
		zram_set_flag(zram, index, ZRAM_IDLE);
		zram_slot_unlock(zram, index);
		अगर (zram_bvec_पढ़ो(zram, &bvec, index, 0, शून्य)) अणु
			zram_slot_lock(zram, index);
			zram_clear_flag(zram, index, ZRAM_UNDER_WB);
			zram_clear_flag(zram, index, ZRAM_IDLE);
			zram_slot_unlock(zram, index);
			जारी;
		पूर्ण

		bio_init(&bio, &bio_vec, 1);
		bio_set_dev(&bio, zram->bdev);
		bio.bi_iter.bi_sector = blk_idx * (PAGE_SIZE >> 9);
		bio.bi_opf = REQ_OP_WRITE | REQ_SYNC;

		bio_add_page(&bio, bvec.bv_page, bvec.bv_len,
				bvec.bv_offset);
		/*
		 * XXX: A single page IO would be inefficient क्रम ग_लिखो
		 * but it would be not bad as starter.
		 */
		err = submit_bio_रुको(&bio);
		अगर (err) अणु
			zram_slot_lock(zram, index);
			zram_clear_flag(zram, index, ZRAM_UNDER_WB);
			zram_clear_flag(zram, index, ZRAM_IDLE);
			zram_slot_unlock(zram, index);
			/*
			 * Return last IO error unless every IO were
			 * not suceeded.
			 */
			ret = err;
			जारी;
		पूर्ण

		atomic64_inc(&zram->stats.bd_ग_लिखोs);
		/*
		 * We released zram_slot_lock so need to check अगर the slot was
		 * changed. If there is मुक्तing क्रम the slot, we can catch it
		 * easily by zram_allocated.
		 * A subtle हाल is the slot is मुक्तd/पुनः_स्मृतिated/marked as
		 * ZRAM_IDLE again. To बंद the race, idle_store करोesn't
		 * mark ZRAM_IDLE once it found the slot was ZRAM_UNDER_WB.
		 * Thus, we could बंद the race by checking ZRAM_IDLE bit.
		 */
		zram_slot_lock(zram, index);
		अगर (!zram_allocated(zram, index) ||
			  !zram_test_flag(zram, index, ZRAM_IDLE)) अणु
			zram_clear_flag(zram, index, ZRAM_UNDER_WB);
			zram_clear_flag(zram, index, ZRAM_IDLE);
			जाओ next;
		पूर्ण

		zram_मुक्त_page(zram, index);
		zram_clear_flag(zram, index, ZRAM_UNDER_WB);
		zram_set_flag(zram, index, ZRAM_WB);
		zram_set_element(zram, index, blk_idx);
		blk_idx = 0;
		atomic64_inc(&zram->stats.pages_stored);
		spin_lock(&zram->wb_limit_lock);
		अगर (zram->wb_limit_enable && zram->bd_wb_limit > 0)
			zram->bd_wb_limit -=  1UL << (PAGE_SHIFT - 12);
		spin_unlock(&zram->wb_limit_lock);
next:
		zram_slot_unlock(zram, index);
	पूर्ण

	अगर (blk_idx)
		मुक्त_block_bdev(zram, blk_idx);
	__मुक्त_page(page);
release_init_lock:
	up_पढ़ो(&zram->init_lock);

	वापस ret;
पूर्ण

काष्ठा zram_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा zram *zram;
	अचिन्हित दीर्घ entry;
	काष्ठा bio *bio;
	काष्ठा bio_vec bvec;
पूर्ण;

#अगर PAGE_SIZE != 4096
अटल व्योम zram_sync_पढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zram_work *zw = container_of(work, काष्ठा zram_work, work);
	काष्ठा zram *zram = zw->zram;
	अचिन्हित दीर्घ entry = zw->entry;
	काष्ठा bio *bio = zw->bio;

	पढ़ो_from_bdev_async(zram, &zw->bvec, entry, bio);
पूर्ण

/*
 * Block layer want one ->submit_bio to be active at a समय, so अगर we use
 * chained IO with parent IO in same context, it's a deadlock. To aव्योम that,
 * use a worker thपढ़ो context.
 */
अटल पूर्णांक पढ़ो_from_bdev_sync(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				अचिन्हित दीर्घ entry, काष्ठा bio *bio)
अणु
	काष्ठा zram_work work;

	work.bvec = *bvec;
	work.zram = zram;
	work.entry = entry;
	work.bio = bio;

	INIT_WORK_ONSTACK(&work.work, zram_sync_पढ़ो);
	queue_work(प्रणाली_unbound_wq, &work.work);
	flush_work(&work.work);
	destroy_work_on_stack(&work.work);

	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक पढ़ो_from_bdev_sync(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				अचिन्हित दीर्घ entry, काष्ठा bio *bio)
अणु
	WARN_ON(1);
	वापस -EIO;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पढ़ो_from_bdev(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
			अचिन्हित दीर्घ entry, काष्ठा bio *parent, bool sync)
अणु
	atomic64_inc(&zram->stats.bd_पढ़ोs);
	अगर (sync)
		वापस पढ़ो_from_bdev_sync(zram, bvec, entry, parent);
	अन्यथा
		वापस पढ़ो_from_bdev_async(zram, bvec, entry, parent);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reset_bdev(काष्ठा zram *zram) अणुपूर्ण;
अटल पूर्णांक पढ़ो_from_bdev(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
			अचिन्हित दीर्घ entry, काष्ठा bio *parent, bool sync)
अणु
	वापस -EIO;
पूर्ण

अटल व्योम मुक्त_block_bdev(काष्ठा zram *zram, अचिन्हित दीर्घ blk_idx) अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZRAM_MEMORY_TRACKING

अटल काष्ठा dentry *zram_debugfs_root;

अटल व्योम zram_debugfs_create(व्योम)
अणु
	zram_debugfs_root = debugfs_create_dir("zram", शून्य);
पूर्ण

अटल व्योम zram_debugfs_destroy(व्योम)
अणु
	debugfs_हटाओ_recursive(zram_debugfs_root);
पूर्ण

अटल व्योम zram_accessed(काष्ठा zram *zram, u32 index)
अणु
	zram_clear_flag(zram, index, ZRAM_IDLE);
	zram->table[index].ac_समय = kसमय_get_bootसमय();
पूर्ण

अटल sमाप_प्रकार पढ़ो_block_state(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *kbuf;
	sमाप_प्रकार index, written = 0;
	काष्ठा zram *zram = file->निजी_data;
	अचिन्हित दीर्घ nr_pages = zram->disksize >> PAGE_SHIFT;
	काष्ठा बारpec64 ts;

	kbuf = kvदो_स्मृति(count, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	करोwn_पढ़ो(&zram->init_lock);
	अगर (!init_करोne(zram)) अणु
		up_पढ़ो(&zram->init_lock);
		kvमुक्त(kbuf);
		वापस -EINVAL;
	पूर्ण

	क्रम (index = *ppos; index < nr_pages; index++) अणु
		पूर्णांक copied;

		zram_slot_lock(zram, index);
		अगर (!zram_allocated(zram, index))
			जाओ next;

		ts = kसमय_प्रकारo_बारpec64(zram->table[index].ac_समय);
		copied = snम_लिखो(kbuf + written, count,
			"%12zd %12lld.%06lu %c%c%c%c\n",
			index, (s64)ts.tv_sec,
			ts.tv_nsec / NSEC_PER_USEC,
			zram_test_flag(zram, index, ZRAM_SAME) ? 's' : '.',
			zram_test_flag(zram, index, ZRAM_WB) ? 'w' : '.',
			zram_test_flag(zram, index, ZRAM_HUGE) ? 'h' : '.',
			zram_test_flag(zram, index, ZRAM_IDLE) ? 'i' : '.');

		अगर (count < copied) अणु
			zram_slot_unlock(zram, index);
			अवरोध;
		पूर्ण
		written += copied;
		count -= copied;
next:
		zram_slot_unlock(zram, index);
		*ppos += 1;
	पूर्ण

	up_पढ़ो(&zram->init_lock);
	अगर (copy_to_user(buf, kbuf, written))
		written = -EFAULT;
	kvमुक्त(kbuf);

	वापस written;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_zram_block_state_op = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = पढ़ो_block_state,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम zram_debugfs_रेजिस्टर(काष्ठा zram *zram)
अणु
	अगर (!zram_debugfs_root)
		वापस;

	zram->debugfs_dir = debugfs_create_dir(zram->disk->disk_name,
						zram_debugfs_root);
	debugfs_create_file("block_state", 0400, zram->debugfs_dir,
				zram, &proc_zram_block_state_op);
पूर्ण

अटल व्योम zram_debugfs_unरेजिस्टर(काष्ठा zram *zram)
अणु
	debugfs_हटाओ_recursive(zram->debugfs_dir);
पूर्ण
#अन्यथा
अटल व्योम zram_debugfs_create(व्योम) अणुपूर्ण;
अटल व्योम zram_debugfs_destroy(व्योम) अणुपूर्ण;
अटल व्योम zram_accessed(काष्ठा zram *zram, u32 index)
अणु
	zram_clear_flag(zram, index, ZRAM_IDLE);
पूर्ण;
अटल व्योम zram_debugfs_रेजिस्टर(काष्ठा zram *zram) अणुपूर्ण;
अटल व्योम zram_debugfs_unरेजिस्टर(काष्ठा zram *zram) अणुपूर्ण;
#पूर्ण_अगर

/*
 * We चयनed to per-cpu streams and this attr is not needed anymore.
 * However, we will keep it around क्रम some समय, because:
 * a) we may revert per-cpu streams in the future
 * b) it's visible to user space and we need to follow our 2 years
 *    retirement rule; but we alपढ़ोy have a number of 'soon to be
 *    altered' attrs, so max_comp_streams need to रुको क्रम the next
 *    layoff cycle.
 */
अटल sमाप_प्रकार max_comp_streams_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", num_online_cpus());
पूर्ण

अटल sमाप_प्रकार max_comp_streams_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस len;
पूर्ण

अटल sमाप_प्रकार comp_algorithm_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	माप_प्रकार sz;
	काष्ठा zram *zram = dev_to_zram(dev);

	करोwn_पढ़ो(&zram->init_lock);
	sz = zcomp_available_show(zram->compressor, buf);
	up_पढ़ो(&zram->init_lock);

	वापस sz;
पूर्ण

अटल sमाप_प्रकार comp_algorithm_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	अक्षर compressor[ARRAY_SIZE(zram->compressor)];
	माप_प्रकार sz;

	strlcpy(compressor, buf, माप(compressor));
	/* ignore trailing newline */
	sz = म_माप(compressor);
	अगर (sz > 0 && compressor[sz - 1] == '\n')
		compressor[sz - 1] = 0x00;

	अगर (!zcomp_available_algorithm(compressor))
		वापस -EINVAL;

	करोwn_ग_लिखो(&zram->init_lock);
	अगर (init_करोne(zram)) अणु
		up_ग_लिखो(&zram->init_lock);
		pr_info("Can't change algorithm for initialized device\n");
		वापस -EBUSY;
	पूर्ण

	म_नकल(zram->compressor, compressor);
	up_ग_लिखो(&zram->init_lock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार compact_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);

	करोwn_पढ़ो(&zram->init_lock);
	अगर (!init_करोne(zram)) अणु
		up_पढ़ो(&zram->init_lock);
		वापस -EINVAL;
	पूर्ण

	zs_compact(zram->mem_pool);
	up_पढ़ो(&zram->init_lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार io_stat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	sमाप_प्रकार ret;

	करोwn_पढ़ो(&zram->init_lock);
	ret = scnम_लिखो(buf, PAGE_SIZE,
			"%8llu %8llu %8llu %8llu\n",
			(u64)atomic64_पढ़ो(&zram->stats.failed_पढ़ोs),
			(u64)atomic64_पढ़ो(&zram->stats.failed_ग_लिखोs),
			(u64)atomic64_पढ़ो(&zram->stats.invalid_io),
			(u64)atomic64_पढ़ो(&zram->stats.notअगरy_मुक्त));
	up_पढ़ो(&zram->init_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mm_stat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	काष्ठा zs_pool_stats pool_stats;
	u64 orig_size, mem_used = 0;
	दीर्घ max_used;
	sमाप_प्रकार ret;

	स_रखो(&pool_stats, 0x00, माप(काष्ठा zs_pool_stats));

	करोwn_पढ़ो(&zram->init_lock);
	अगर (init_करोne(zram)) अणु
		mem_used = zs_get_total_pages(zram->mem_pool);
		zs_pool_stats(zram->mem_pool, &pool_stats);
	पूर्ण

	orig_size = atomic64_पढ़ो(&zram->stats.pages_stored);
	max_used = atomic_दीर्घ_पढ़ो(&zram->stats.max_used_pages);

	ret = scnम_लिखो(buf, PAGE_SIZE,
			"%8llu %8llu %8llu %8lu %8ld %8llu %8lu %8llu %8llu\n",
			orig_size << PAGE_SHIFT,
			(u64)atomic64_पढ़ो(&zram->stats.compr_data_size),
			mem_used << PAGE_SHIFT,
			zram->limit_pages << PAGE_SHIFT,
			max_used << PAGE_SHIFT,
			(u64)atomic64_पढ़ो(&zram->stats.same_pages),
			atomic_दीर्घ_पढ़ो(&pool_stats.pages_compacted),
			(u64)atomic64_पढ़ो(&zram->stats.huge_pages),
			(u64)atomic64_पढ़ो(&zram->stats.huge_pages_since));
	up_पढ़ो(&zram->init_lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ZRAM_WRITEBACK
#घोषणा FOUR_K(x) ((x) * (1 << (PAGE_SHIFT - 12)))
अटल sमाप_प्रकार bd_stat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zram *zram = dev_to_zram(dev);
	sमाप_प्रकार ret;

	करोwn_पढ़ो(&zram->init_lock);
	ret = scnम_लिखो(buf, PAGE_SIZE,
		"%8llu %8llu %8llu\n",
			FOUR_K((u64)atomic64_पढ़ो(&zram->stats.bd_count)),
			FOUR_K((u64)atomic64_पढ़ो(&zram->stats.bd_पढ़ोs)),
			FOUR_K((u64)atomic64_पढ़ो(&zram->stats.bd_ग_लिखोs)));
	up_पढ़ो(&zram->init_lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार debug_stat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक version = 1;
	काष्ठा zram *zram = dev_to_zram(dev);
	sमाप_प्रकार ret;

	करोwn_पढ़ो(&zram->init_lock);
	ret = scnम_लिखो(buf, PAGE_SIZE,
			"version: %d\n%8llu %8llu\n",
			version,
			(u64)atomic64_पढ़ो(&zram->stats.ग_लिखोstall),
			(u64)atomic64_पढ़ो(&zram->stats.miss_मुक्त));
	up_पढ़ो(&zram->init_lock);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(io_stat);
अटल DEVICE_ATTR_RO(mm_stat);
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
अटल DEVICE_ATTR_RO(bd_stat);
#पूर्ण_अगर
अटल DEVICE_ATTR_RO(debug_stat);

अटल व्योम zram_meta_मुक्त(काष्ठा zram *zram, u64 disksize)
अणु
	माप_प्रकार num_pages = disksize >> PAGE_SHIFT;
	माप_प्रकार index;

	/* Free all pages that are still in this zram device */
	क्रम (index = 0; index < num_pages; index++)
		zram_मुक्त_page(zram, index);

	zs_destroy_pool(zram->mem_pool);
	vमुक्त(zram->table);
पूर्ण

अटल bool zram_meta_alloc(काष्ठा zram *zram, u64 disksize)
अणु
	माप_प्रकार num_pages;

	num_pages = disksize >> PAGE_SHIFT;
	zram->table = vzalloc(array_size(num_pages, माप(*zram->table)));
	अगर (!zram->table)
		वापस false;

	zram->mem_pool = zs_create_pool(zram->disk->disk_name);
	अगर (!zram->mem_pool) अणु
		vमुक्त(zram->table);
		वापस false;
	पूर्ण

	अगर (!huge_class_size)
		huge_class_size = zs_huge_class_size(zram->mem_pool);
	वापस true;
पूर्ण

/*
 * To protect concurrent access to the same index entry,
 * caller should hold this table index entry's bit_spinlock to
 * indicate this index entry is accessing.
 */
अटल व्योम zram_मुक्त_page(काष्ठा zram *zram, माप_प्रकार index)
अणु
	अचिन्हित दीर्घ handle;

#अगर_घोषित CONFIG_ZRAM_MEMORY_TRACKING
	zram->table[index].ac_समय = 0;
#पूर्ण_अगर
	अगर (zram_test_flag(zram, index, ZRAM_IDLE))
		zram_clear_flag(zram, index, ZRAM_IDLE);

	अगर (zram_test_flag(zram, index, ZRAM_HUGE)) अणु
		zram_clear_flag(zram, index, ZRAM_HUGE);
		atomic64_dec(&zram->stats.huge_pages);
	पूर्ण

	अगर (zram_test_flag(zram, index, ZRAM_WB)) अणु
		zram_clear_flag(zram, index, ZRAM_WB);
		मुक्त_block_bdev(zram, zram_get_element(zram, index));
		जाओ out;
	पूर्ण

	/*
	 * No memory is allocated क्रम same element filled pages.
	 * Simply clear same page flag.
	 */
	अगर (zram_test_flag(zram, index, ZRAM_SAME)) अणु
		zram_clear_flag(zram, index, ZRAM_SAME);
		atomic64_dec(&zram->stats.same_pages);
		जाओ out;
	पूर्ण

	handle = zram_get_handle(zram, index);
	अगर (!handle)
		वापस;

	zs_मुक्त(zram->mem_pool, handle);

	atomic64_sub(zram_get_obj_size(zram, index),
			&zram->stats.compr_data_size);
out:
	atomic64_dec(&zram->stats.pages_stored);
	zram_set_handle(zram, index, 0);
	zram_set_obj_size(zram, index, 0);
	WARN_ON_ONCE(zram->table[index].flags &
		~(1UL << ZRAM_LOCK | 1UL << ZRAM_UNDER_WB));
पूर्ण

अटल पूर्णांक __zram_bvec_पढ़ो(काष्ठा zram *zram, काष्ठा page *page, u32 index,
				काष्ठा bio *bio, bool partial_io)
अणु
	काष्ठा zcomp_strm *zstrm;
	अचिन्हित दीर्घ handle;
	अचिन्हित पूर्णांक size;
	व्योम *src, *dst;
	पूर्णांक ret;

	zram_slot_lock(zram, index);
	अगर (zram_test_flag(zram, index, ZRAM_WB)) अणु
		काष्ठा bio_vec bvec;

		zram_slot_unlock(zram, index);

		bvec.bv_page = page;
		bvec.bv_len = PAGE_SIZE;
		bvec.bv_offset = 0;
		वापस पढ़ो_from_bdev(zram, &bvec,
				zram_get_element(zram, index),
				bio, partial_io);
	पूर्ण

	handle = zram_get_handle(zram, index);
	अगर (!handle || zram_test_flag(zram, index, ZRAM_SAME)) अणु
		अचिन्हित दीर्घ value;
		व्योम *mem;

		value = handle ? zram_get_element(zram, index) : 0;
		mem = kmap_atomic(page);
		zram_fill_page(mem, PAGE_SIZE, value);
		kunmap_atomic(mem);
		zram_slot_unlock(zram, index);
		वापस 0;
	पूर्ण

	size = zram_get_obj_size(zram, index);

	अगर (size != PAGE_SIZE)
		zstrm = zcomp_stream_get(zram->comp);

	src = zs_map_object(zram->mem_pool, handle, ZS_MM_RO);
	अगर (size == PAGE_SIZE) अणु
		dst = kmap_atomic(page);
		स_नकल(dst, src, PAGE_SIZE);
		kunmap_atomic(dst);
		ret = 0;
	पूर्ण अन्यथा अणु
		dst = kmap_atomic(page);
		ret = zcomp_decompress(zstrm, src, size, dst);
		kunmap_atomic(dst);
		zcomp_stream_put(zram->comp);
	पूर्ण
	zs_unmap_object(zram->mem_pool, handle);
	zram_slot_unlock(zram, index);

	/* Should NEVER happen. Return bio error अगर it करोes. */
	अगर (WARN_ON(ret))
		pr_err("Decompression failed! err=%d, page=%u\n", ret, index);

	वापस ret;
पूर्ण

अटल पूर्णांक zram_bvec_पढ़ो(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				u32 index, पूर्णांक offset, काष्ठा bio *bio)
अणु
	पूर्णांक ret;
	काष्ठा page *page;

	page = bvec->bv_page;
	अगर (is_partial_io(bvec)) अणु
		/* Use a temporary buffer to decompress the page */
		page = alloc_page(GFP_NOIO|__GFP_HIGHMEM);
		अगर (!page)
			वापस -ENOMEM;
	पूर्ण

	ret = __zram_bvec_पढ़ो(zram, page, index, bio, is_partial_io(bvec));
	अगर (unlikely(ret))
		जाओ out;

	अगर (is_partial_io(bvec)) अणु
		व्योम *dst = kmap_atomic(bvec->bv_page);
		व्योम *src = kmap_atomic(page);

		स_नकल(dst + bvec->bv_offset, src + offset, bvec->bv_len);
		kunmap_atomic(src);
		kunmap_atomic(dst);
	पूर्ण
out:
	अगर (is_partial_io(bvec))
		__मुक्त_page(page);

	वापस ret;
पूर्ण

अटल पूर्णांक __zram_bvec_ग_लिखो(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				u32 index, काष्ठा bio *bio)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ alloced_pages;
	अचिन्हित दीर्घ handle = 0;
	अचिन्हित पूर्णांक comp_len = 0;
	व्योम *src, *dst, *mem;
	काष्ठा zcomp_strm *zstrm;
	काष्ठा page *page = bvec->bv_page;
	अचिन्हित दीर्घ element = 0;
	क्रमागत zram_pageflags flags = 0;

	mem = kmap_atomic(page);
	अगर (page_same_filled(mem, &element)) अणु
		kunmap_atomic(mem);
		/* Free memory associated with this sector now. */
		flags = ZRAM_SAME;
		atomic64_inc(&zram->stats.same_pages);
		जाओ out;
	पूर्ण
	kunmap_atomic(mem);

compress_again:
	zstrm = zcomp_stream_get(zram->comp);
	src = kmap_atomic(page);
	ret = zcomp_compress(zstrm, src, &comp_len);
	kunmap_atomic(src);

	अगर (unlikely(ret)) अणु
		zcomp_stream_put(zram->comp);
		pr_err("Compression failed! err=%d\n", ret);
		zs_मुक्त(zram->mem_pool, handle);
		वापस ret;
	पूर्ण

	अगर (comp_len >= huge_class_size)
		comp_len = PAGE_SIZE;
	/*
	 * handle allocation has 2 paths:
	 * a) fast path is executed with preemption disabled (क्रम
	 *  per-cpu streams) and has __GFP_सूचीECT_RECLAIM bit clear,
	 *  since we can't sleep;
	 * b) slow path enables preemption and attempts to allocate
	 *  the page with __GFP_सूचीECT_RECLAIM bit set. we have to
	 *  put per-cpu compression stream and, thus, to re-करो
	 *  the compression once handle is allocated.
	 *
	 * अगर we have a 'non-null' handle here then we are coming
	 * from the slow path and handle has alपढ़ोy been allocated.
	 */
	अगर (!handle)
		handle = zs_दो_स्मृति(zram->mem_pool, comp_len,
				__GFP_KSWAPD_RECLAIM |
				__GFP_NOWARN |
				__GFP_HIGHMEM |
				__GFP_MOVABLE);
	अगर (!handle) अणु
		zcomp_stream_put(zram->comp);
		atomic64_inc(&zram->stats.ग_लिखोstall);
		handle = zs_दो_स्मृति(zram->mem_pool, comp_len,
				GFP_NOIO | __GFP_HIGHMEM |
				__GFP_MOVABLE);
		अगर (handle)
			जाओ compress_again;
		वापस -ENOMEM;
	पूर्ण

	alloced_pages = zs_get_total_pages(zram->mem_pool);
	update_used_max(zram, alloced_pages);

	अगर (zram->limit_pages && alloced_pages > zram->limit_pages) अणु
		zcomp_stream_put(zram->comp);
		zs_मुक्त(zram->mem_pool, handle);
		वापस -ENOMEM;
	पूर्ण

	dst = zs_map_object(zram->mem_pool, handle, ZS_MM_WO);

	src = zstrm->buffer;
	अगर (comp_len == PAGE_SIZE)
		src = kmap_atomic(page);
	स_नकल(dst, src, comp_len);
	अगर (comp_len == PAGE_SIZE)
		kunmap_atomic(src);

	zcomp_stream_put(zram->comp);
	zs_unmap_object(zram->mem_pool, handle);
	atomic64_add(comp_len, &zram->stats.compr_data_size);
out:
	/*
	 * Free memory associated with this sector
	 * beक्रमe overwriting unused sectors.
	 */
	zram_slot_lock(zram, index);
	zram_मुक्त_page(zram, index);

	अगर (comp_len == PAGE_SIZE) अणु
		zram_set_flag(zram, index, ZRAM_HUGE);
		atomic64_inc(&zram->stats.huge_pages);
		atomic64_inc(&zram->stats.huge_pages_since);
	पूर्ण

	अगर (flags) अणु
		zram_set_flag(zram, index, flags);
		zram_set_element(zram, index, element);
	पूर्ण  अन्यथा अणु
		zram_set_handle(zram, index, handle);
		zram_set_obj_size(zram, index, comp_len);
	पूर्ण
	zram_slot_unlock(zram, index);

	/* Update stats */
	atomic64_inc(&zram->stats.pages_stored);
	वापस ret;
पूर्ण

अटल पूर्णांक zram_bvec_ग_लिखो(काष्ठा zram *zram, काष्ठा bio_vec *bvec,
				u32 index, पूर्णांक offset, काष्ठा bio *bio)
अणु
	पूर्णांक ret;
	काष्ठा page *page = शून्य;
	व्योम *src;
	काष्ठा bio_vec vec;

	vec = *bvec;
	अगर (is_partial_io(bvec)) अणु
		व्योम *dst;
		/*
		 * This is a partial IO. We need to पढ़ो the full page
		 * beक्रमe to ग_लिखो the changes.
		 */
		page = alloc_page(GFP_NOIO|__GFP_HIGHMEM);
		अगर (!page)
			वापस -ENOMEM;

		ret = __zram_bvec_पढ़ो(zram, page, index, bio, true);
		अगर (ret)
			जाओ out;

		src = kmap_atomic(bvec->bv_page);
		dst = kmap_atomic(page);
		स_नकल(dst + offset, src + bvec->bv_offset, bvec->bv_len);
		kunmap_atomic(dst);
		kunmap_atomic(src);

		vec.bv_page = page;
		vec.bv_len = PAGE_SIZE;
		vec.bv_offset = 0;
	पूर्ण

	ret = __zram_bvec_ग_लिखो(zram, &vec, index, bio);
out:
	अगर (is_partial_io(bvec))
		__मुक्त_page(page);
	वापस ret;
पूर्ण

/*
 * zram_bio_discard - handler on discard request
 * @index: physical block index in PAGE_SIZE units
 * @offset: byte offset within physical block
 */
अटल व्योम zram_bio_discard(काष्ठा zram *zram, u32 index,
			     पूर्णांक offset, काष्ठा bio *bio)
अणु
	माप_प्रकार n = bio->bi_iter.bi_size;

	/*
	 * zram manages data in physical block size units. Because logical block
	 * size isn't identical with physical block size on some arch, we
	 * could get a discard request poपूर्णांकing to a specअगरic offset within a
	 * certain physical block.  Although we can handle this request by
	 * पढ़ोing that physiclal block and decompressing and partially zeroing
	 * and re-compressing and then re-storing it, this isn't reasonable
	 * because our पूर्णांकent with a discard request is to save memory.  So
	 * skipping this logical block is appropriate here.
	 */
	अगर (offset) अणु
		अगर (n <= (PAGE_SIZE - offset))
			वापस;

		n -= (PAGE_SIZE - offset);
		index++;
	पूर्ण

	जबतक (n >= PAGE_SIZE) अणु
		zram_slot_lock(zram, index);
		zram_मुक्त_page(zram, index);
		zram_slot_unlock(zram, index);
		atomic64_inc(&zram->stats.notअगरy_मुक्त);
		index++;
		n -= PAGE_SIZE;
	पूर्ण
पूर्ण

/*
 * Returns त्रुटि_सं अगर it has some problem. Otherwise वापस 0 or 1.
 * Returns 0 अगर IO request was करोne synchronously
 * Returns 1 अगर IO request was successfully submitted.
 */
अटल पूर्णांक zram_bvec_rw(काष्ठा zram *zram, काष्ठा bio_vec *bvec, u32 index,
			पूर्णांक offset, अचिन्हित पूर्णांक op, काष्ठा bio *bio)
अणु
	पूर्णांक ret;

	अगर (!op_is_ग_लिखो(op)) अणु
		atomic64_inc(&zram->stats.num_पढ़ोs);
		ret = zram_bvec_पढ़ो(zram, bvec, index, offset, bio);
		flush_dcache_page(bvec->bv_page);
	पूर्ण अन्यथा अणु
		atomic64_inc(&zram->stats.num_ग_लिखोs);
		ret = zram_bvec_ग_लिखो(zram, bvec, index, offset, bio);
	पूर्ण

	zram_slot_lock(zram, index);
	zram_accessed(zram, index);
	zram_slot_unlock(zram, index);

	अगर (unlikely(ret < 0)) अणु
		अगर (!op_is_ग_लिखो(op))
			atomic64_inc(&zram->stats.failed_पढ़ोs);
		अन्यथा
			atomic64_inc(&zram->stats.failed_ग_लिखोs);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __zram_make_request(काष्ठा zram *zram, काष्ठा bio *bio)
अणु
	पूर्णांक offset;
	u32 index;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	अचिन्हित दीर्घ start_समय;

	index = bio->bi_iter.bi_sector >> SECTORS_PER_PAGE_SHIFT;
	offset = (bio->bi_iter.bi_sector &
		  (SECTORS_PER_PAGE - 1)) << SECTOR_SHIFT;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_WRITE_ZEROES:
		zram_bio_discard(zram, index, offset, bio);
		bio_endio(bio);
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	start_समय = bio_start_io_acct(bio);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		काष्ठा bio_vec bv = bvec;
		अचिन्हित पूर्णांक unwritten = bvec.bv_len;

		करो अणु
			bv.bv_len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - offset,
							unwritten);
			अगर (zram_bvec_rw(zram, &bv, index, offset,
					 bio_op(bio), bio) < 0) अणु
				bio->bi_status = BLK_STS_IOERR;
				अवरोध;
			पूर्ण

			bv.bv_offset += bv.bv_len;
			unwritten -= bv.bv_len;

			update_position(&index, &offset, &bv);
		पूर्ण जबतक (unwritten);
	पूर्ण
	bio_end_io_acct(bio, start_समय);
	bio_endio(bio);
पूर्ण

/*
 * Handler function क्रम all zram I/O requests.
 */
अटल blk_qc_t zram_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा zram *zram = bio->bi_bdev->bd_disk->निजी_data;

	अगर (!valid_io_request(zram, bio->bi_iter.bi_sector,
					bio->bi_iter.bi_size)) अणु
		atomic64_inc(&zram->stats.invalid_io);
		जाओ error;
	पूर्ण

	__zram_make_request(zram, bio);
	वापस BLK_QC_T_NONE;

error:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल व्योम zram_slot_मुक्त_notअगरy(काष्ठा block_device *bdev,
				अचिन्हित दीर्घ index)
अणु
	काष्ठा zram *zram;

	zram = bdev->bd_disk->निजी_data;

	atomic64_inc(&zram->stats.notअगरy_मुक्त);
	अगर (!zram_slot_trylock(zram, index)) अणु
		atomic64_inc(&zram->stats.miss_मुक्त);
		वापस;
	पूर्ण

	zram_मुक्त_page(zram, index);
	zram_slot_unlock(zram, index);
पूर्ण

अटल पूर्णांक zram_rw_page(काष्ठा block_device *bdev, sector_t sector,
		       काष्ठा page *page, अचिन्हित पूर्णांक op)
अणु
	पूर्णांक offset, ret;
	u32 index;
	काष्ठा zram *zram;
	काष्ठा bio_vec bv;
	अचिन्हित दीर्घ start_समय;

	अगर (PageTransHuge(page))
		वापस -ENOTSUPP;
	zram = bdev->bd_disk->निजी_data;

	अगर (!valid_io_request(zram, sector, PAGE_SIZE)) अणु
		atomic64_inc(&zram->stats.invalid_io);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	index = sector >> SECTORS_PER_PAGE_SHIFT;
	offset = (sector & (SECTORS_PER_PAGE - 1)) << SECTOR_SHIFT;

	bv.bv_page = page;
	bv.bv_len = PAGE_SIZE;
	bv.bv_offset = 0;

	start_समय = disk_start_io_acct(bdev->bd_disk, SECTORS_PER_PAGE, op);
	ret = zram_bvec_rw(zram, &bv, index, offset, op, शून्य);
	disk_end_io_acct(bdev->bd_disk, op, start_समय);
out:
	/*
	 * If I/O fails, just वापस error(ie, non-zero) without
	 * calling page_endio.
	 * It causes resubmit the I/O with bio request by upper functions
	 * of rw_page(e.g., swap_पढ़ोpage, __swap_ग_लिखोpage) and
	 * bio->bi_end_io करोes things to handle the error
	 * (e.g., SetPageError, set_page_dirty and extra works).
	 */
	अगर (unlikely(ret < 0))
		वापस ret;

	चयन (ret) अणु
	हाल 0:
		page_endio(page, op_is_ग_लिखो(op), 0);
		अवरोध;
	हाल 1:
		ret = 0;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम zram_reset_device(काष्ठा zram *zram)
अणु
	काष्ठा zcomp *comp;
	u64 disksize;

	करोwn_ग_लिखो(&zram->init_lock);

	zram->limit_pages = 0;

	अगर (!init_करोne(zram)) अणु
		up_ग_लिखो(&zram->init_lock);
		वापस;
	पूर्ण

	comp = zram->comp;
	disksize = zram->disksize;
	zram->disksize = 0;

	set_capacity_and_notअगरy(zram->disk, 0);
	part_stat_set_all(zram->disk->part0, 0);

	up_ग_लिखो(&zram->init_lock);
	/* I/O operation under all of CPU are करोne so let's मुक्त */
	zram_meta_मुक्त(zram, disksize);
	स_रखो(&zram->stats, 0, माप(zram->stats));
	zcomp_destroy(comp);
	reset_bdev(zram);
पूर्ण

अटल sमाप_प्रकार disksize_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	u64 disksize;
	काष्ठा zcomp *comp;
	काष्ठा zram *zram = dev_to_zram(dev);
	पूर्णांक err;

	disksize = memparse(buf, शून्य);
	अगर (!disksize)
		वापस -EINVAL;

	करोwn_ग_लिखो(&zram->init_lock);
	अगर (init_करोne(zram)) अणु
		pr_info("Cannot change disksize for initialized device\n");
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	disksize = PAGE_ALIGN(disksize);
	अगर (!zram_meta_alloc(zram, disksize)) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	comp = zcomp_create(zram->compressor);
	अगर (IS_ERR(comp)) अणु
		pr_err("Cannot initialise %s compressing backend\n",
				zram->compressor);
		err = PTR_ERR(comp);
		जाओ out_मुक्त_meta;
	पूर्ण

	zram->comp = comp;
	zram->disksize = disksize;
	set_capacity_and_notअगरy(zram->disk, zram->disksize >> SECTOR_SHIFT);
	up_ग_लिखो(&zram->init_lock);

	वापस len;

out_मुक्त_meta:
	zram_meta_मुक्त(zram, disksize);
out_unlock:
	up_ग_लिखो(&zram->init_lock);
	वापस err;
पूर्ण

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित लघु करो_reset;
	काष्ठा zram *zram;
	काष्ठा block_device *bdev;

	ret = kstrtou16(buf, 10, &करो_reset);
	अगर (ret)
		वापस ret;

	अगर (!करो_reset)
		वापस -EINVAL;

	zram = dev_to_zram(dev);
	bdev = zram->disk->part0;

	mutex_lock(&bdev->bd_mutex);
	/* Do not reset an active device or claimed device */
	अगर (bdev->bd_खोलोers || zram->claim) अणु
		mutex_unlock(&bdev->bd_mutex);
		वापस -EBUSY;
	पूर्ण

	/* From now on, anyone can't खोलो /dev/zram[0-9] */
	zram->claim = true;
	mutex_unlock(&bdev->bd_mutex);

	/* Make sure all the pending I/O are finished */
	fsync_bdev(bdev);
	zram_reset_device(zram);

	mutex_lock(&bdev->bd_mutex);
	zram->claim = false;
	mutex_unlock(&bdev->bd_mutex);

	वापस len;
पूर्ण

अटल पूर्णांक zram_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret = 0;
	काष्ठा zram *zram;

	WARN_ON(!mutex_is_locked(&bdev->bd_mutex));

	zram = bdev->bd_disk->निजी_data;
	/* zram was claimed to reset so खोलो request fails */
	अगर (zram->claim)
		ret = -EBUSY;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations zram_devops = अणु
	.खोलो = zram_खोलो,
	.submit_bio = zram_submit_bio,
	.swap_slot_मुक्त_notअगरy = zram_slot_मुक्त_notअगरy,
	.rw_page = zram_rw_page,
	.owner = THIS_MODULE
पूर्ण;

अटल स्थिर काष्ठा block_device_operations zram_wb_devops = अणु
	.खोलो = zram_खोलो,
	.submit_bio = zram_submit_bio,
	.swap_slot_मुक्त_notअगरy = zram_slot_मुक्त_notअगरy,
	.owner = THIS_MODULE
पूर्ण;

अटल DEVICE_ATTR_WO(compact);
अटल DEVICE_ATTR_RW(disksize);
अटल DEVICE_ATTR_RO(initstate);
अटल DEVICE_ATTR_WO(reset);
अटल DEVICE_ATTR_WO(mem_limit);
अटल DEVICE_ATTR_WO(mem_used_max);
अटल DEVICE_ATTR_WO(idle);
अटल DEVICE_ATTR_RW(max_comp_streams);
अटल DEVICE_ATTR_RW(comp_algorithm);
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
अटल DEVICE_ATTR_RW(backing_dev);
अटल DEVICE_ATTR_WO(ग_लिखोback);
अटल DEVICE_ATTR_RW(ग_लिखोback_limit);
अटल DEVICE_ATTR_RW(ग_लिखोback_limit_enable);
#पूर्ण_अगर

अटल काष्ठा attribute *zram_disk_attrs[] = अणु
	&dev_attr_disksize.attr,
	&dev_attr_initstate.attr,
	&dev_attr_reset.attr,
	&dev_attr_compact.attr,
	&dev_attr_mem_limit.attr,
	&dev_attr_mem_used_max.attr,
	&dev_attr_idle.attr,
	&dev_attr_max_comp_streams.attr,
	&dev_attr_comp_algorithm.attr,
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
	&dev_attr_backing_dev.attr,
	&dev_attr_ग_लिखोback.attr,
	&dev_attr_ग_लिखोback_limit.attr,
	&dev_attr_ग_लिखोback_limit_enable.attr,
#पूर्ण_अगर
	&dev_attr_io_stat.attr,
	&dev_attr_mm_stat.attr,
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
	&dev_attr_bd_stat.attr,
#पूर्ण_अगर
	&dev_attr_debug_stat.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group zram_disk_attr_group = अणु
	.attrs = zram_disk_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *zram_disk_attr_groups[] = अणु
	&zram_disk_attr_group,
	शून्य,
पूर्ण;

/*
 * Allocate and initialize new zram device. the function वापसs
 * '>= 0' device_id upon success, and negative value otherwise.
 */
अटल पूर्णांक zram_add(व्योम)
अणु
	काष्ठा zram *zram;
	काष्ठा request_queue *queue;
	पूर्णांक ret, device_id;

	zram = kzalloc(माप(काष्ठा zram), GFP_KERNEL);
	अगर (!zram)
		वापस -ENOMEM;

	ret = idr_alloc(&zram_index_idr, zram, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ out_मुक्त_dev;
	device_id = ret;

	init_rwsem(&zram->init_lock);
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
	spin_lock_init(&zram->wb_limit_lock);
#पूर्ण_अगर
	queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!queue) अणु
		pr_err("Error allocating disk queue for device %d\n",
			device_id);
		ret = -ENOMEM;
		जाओ out_मुक्त_idr;
	पूर्ण

	/* gendisk काष्ठाure */
	zram->disk = alloc_disk(1);
	अगर (!zram->disk) अणु
		pr_err("Error allocating disk structure for device %d\n",
			device_id);
		ret = -ENOMEM;
		जाओ out_मुक्त_queue;
	पूर्ण

	zram->disk->major = zram_major;
	zram->disk->first_minor = device_id;
	zram->disk->fops = &zram_devops;
	zram->disk->queue = queue;
	zram->disk->निजी_data = zram;
	snम_लिखो(zram->disk->disk_name, 16, "zram%d", device_id);

	/* Actual capacity set using syfs (/sys/block/zram<id>/disksize */
	set_capacity(zram->disk, 0);
	/* zram devices sort of resembles non-rotational disks */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, zram->disk->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, zram->disk->queue);

	/*
	 * To ensure that we always get PAGE_SIZE aligned
	 * and n*PAGE_SIZED sized I/O requests.
	 */
	blk_queue_physical_block_size(zram->disk->queue, PAGE_SIZE);
	blk_queue_logical_block_size(zram->disk->queue,
					ZRAM_LOGICAL_BLOCK_SIZE);
	blk_queue_io_min(zram->disk->queue, PAGE_SIZE);
	blk_queue_io_opt(zram->disk->queue, PAGE_SIZE);
	zram->disk->queue->limits.discard_granularity = PAGE_SIZE;
	blk_queue_max_discard_sectors(zram->disk->queue, अच_पूर्णांक_उच्च);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, zram->disk->queue);

	/*
	 * zram_bio_discard() will clear all logical blocks अगर logical block
	 * size is identical with physical block size(PAGE_SIZE). But अगर it is
	 * dअगरferent, we will skip discarding some parts of logical blocks in
	 * the part of the request range which isn't aligned to physical block
	 * size.  So we can't ensure that all discarded logical blocks are
	 * zeroed.
	 */
	अगर (ZRAM_LOGICAL_BLOCK_SIZE == PAGE_SIZE)
		blk_queue_max_ग_लिखो_zeroes_sectors(zram->disk->queue, अच_पूर्णांक_उच्च);

	blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, zram->disk->queue);
	device_add_disk(शून्य, zram->disk, zram_disk_attr_groups);

	strlcpy(zram->compressor, शेष_compressor, माप(zram->compressor));

	zram_debugfs_रेजिस्टर(zram);
	pr_info("Added device: %s\n", zram->disk->disk_name);
	वापस device_id;

out_मुक्त_queue:
	blk_cleanup_queue(queue);
out_मुक्त_idr:
	idr_हटाओ(&zram_index_idr, device_id);
out_मुक्त_dev:
	kमुक्त(zram);
	वापस ret;
पूर्ण

अटल पूर्णांक zram_हटाओ(काष्ठा zram *zram)
अणु
	काष्ठा block_device *bdev = zram->disk->part0;

	mutex_lock(&bdev->bd_mutex);
	अगर (bdev->bd_खोलोers || zram->claim) अणु
		mutex_unlock(&bdev->bd_mutex);
		वापस -EBUSY;
	पूर्ण

	zram->claim = true;
	mutex_unlock(&bdev->bd_mutex);

	zram_debugfs_unरेजिस्टर(zram);

	/* Make sure all the pending I/O are finished */
	fsync_bdev(bdev);
	zram_reset_device(zram);

	pr_info("Removed device: %s\n", zram->disk->disk_name);

	del_gendisk(zram->disk);
	blk_cleanup_queue(zram->disk->queue);
	put_disk(zram->disk);
	kमुक्त(zram);
	वापस 0;
पूर्ण

/* zram-control sysfs attributes */

/*
 * NOTE: hot_add attribute is not the usual पढ़ो-only sysfs attribute. In a
 * sense that पढ़ोing from this file करोes alter the state of your प्रणाली -- it
 * creates a new un-initialized zram device and वापसs back this device's
 * device_id (or an error code अगर it fails to create a new device).
 */
अटल sमाप_प्रकार hot_add_show(काष्ठा class *class,
			काष्ठा class_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक ret;

	mutex_lock(&zram_index_mutex);
	ret = zram_add();
	mutex_unlock(&zram_index_mutex);

	अगर (ret < 0)
		वापस ret;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ret);
पूर्ण
अटल काष्ठा class_attribute class_attr_hot_add =
	__ATTR(hot_add, 0400, hot_add_show, शून्य);

अटल sमाप_प्रकार hot_हटाओ_store(काष्ठा class *class,
			काष्ठा class_attribute *attr,
			स्थिर अक्षर *buf,
			माप_प्रकार count)
अणु
	काष्ठा zram *zram;
	पूर्णांक ret, dev_id;

	/* dev_id is gendisk->first_minor, which is `पूर्णांक' */
	ret = kstrtoपूर्णांक(buf, 10, &dev_id);
	अगर (ret)
		वापस ret;
	अगर (dev_id < 0)
		वापस -EINVAL;

	mutex_lock(&zram_index_mutex);

	zram = idr_find(&zram_index_idr, dev_id);
	अगर (zram) अणु
		ret = zram_हटाओ(zram);
		अगर (!ret)
			idr_हटाओ(&zram_index_idr, dev_id);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण

	mutex_unlock(&zram_index_mutex);
	वापस ret ? ret : count;
पूर्ण
अटल CLASS_ATTR_WO(hot_हटाओ);

अटल काष्ठा attribute *zram_control_class_attrs[] = अणु
	&class_attr_hot_add.attr,
	&class_attr_hot_हटाओ.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(zram_control_class);

अटल काष्ठा class zram_control_class = अणु
	.name		= "zram-control",
	.owner		= THIS_MODULE,
	.class_groups	= zram_control_class_groups,
पूर्ण;

अटल पूर्णांक zram_हटाओ_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	zram_हटाओ(ptr);
	वापस 0;
पूर्ण

अटल व्योम destroy_devices(व्योम)
अणु
	class_unरेजिस्टर(&zram_control_class);
	idr_क्रम_each(&zram_index_idr, &zram_हटाओ_cb, शून्य);
	zram_debugfs_destroy();
	idr_destroy(&zram_index_idr);
	unरेजिस्टर_blkdev(zram_major, "zram");
	cpuhp_हटाओ_multi_state(CPUHP_ZCOMP_PREPARE);
पूर्ण

अटल पूर्णांक __init zram_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_ZCOMP_PREPARE, "block/zram:prepare",
				      zcomp_cpu_up_prepare, zcomp_cpu_dead);
	अगर (ret < 0)
		वापस ret;

	ret = class_रेजिस्टर(&zram_control_class);
	अगर (ret) अणु
		pr_err("Unable to register zram-control class\n");
		cpuhp_हटाओ_multi_state(CPUHP_ZCOMP_PREPARE);
		वापस ret;
	पूर्ण

	zram_debugfs_create();
	zram_major = रेजिस्टर_blkdev(0, "zram");
	अगर (zram_major <= 0) अणु
		pr_err("Unable to get major number\n");
		class_unरेजिस्टर(&zram_control_class);
		cpuhp_हटाओ_multi_state(CPUHP_ZCOMP_PREPARE);
		वापस -EBUSY;
	पूर्ण

	जबतक (num_devices != 0) अणु
		mutex_lock(&zram_index_mutex);
		ret = zram_add();
		mutex_unlock(&zram_index_mutex);
		अगर (ret < 0)
			जाओ out_error;
		num_devices--;
	पूर्ण

	वापस 0;

out_error:
	destroy_devices();
	वापस ret;
पूर्ण

अटल व्योम __निकास zram_निकास(व्योम)
अणु
	destroy_devices();
पूर्ण

module_init(zram_init);
module_निकास(zram_निकास);

module_param(num_devices, uपूर्णांक, 0);
MODULE_PARM_DESC(num_devices, "Number of pre-created zram devices");

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nitin Gupta <ngupta@vflare.org>");
MODULE_DESCRIPTION("Compressed RAM Block Device");
