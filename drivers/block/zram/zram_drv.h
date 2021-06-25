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

#अगर_अघोषित _ZRAM_DRV_H_
#घोषणा _ZRAM_DRV_H_

#समावेश <linux/rwsem.h>
#समावेश <linux/zsदो_स्मृति.h>
#समावेश <linux/crypto.h>

#समावेश "zcomp.h"

#घोषणा SECTORS_PER_PAGE_SHIFT	(PAGE_SHIFT - SECTOR_SHIFT)
#घोषणा SECTORS_PER_PAGE	(1 << SECTORS_PER_PAGE_SHIFT)
#घोषणा ZRAM_LOGICAL_BLOCK_SHIFT 12
#घोषणा ZRAM_LOGICAL_BLOCK_SIZE	(1 << ZRAM_LOGICAL_BLOCK_SHIFT)
#घोषणा ZRAM_SECTOR_PER_LOGICAL_BLOCK	\
	(1 << (ZRAM_LOGICAL_BLOCK_SHIFT - SECTOR_SHIFT))


/*
 * The lower ZRAM_FLAG_SHIFT bits of table.flags is क्रम
 * object size (excluding header), the higher bits is क्रम
 * zram_pageflags.
 *
 * zram is मुख्यly used क्रम memory efficiency so we want to keep memory
 * footprपूर्णांक small so we can squeeze size and flags पूर्णांकo a field.
 * The lower ZRAM_FLAG_SHIFT bits is क्रम object size (excluding header),
 * the higher bits is क्रम zram_pageflags.
 */
#घोषणा ZRAM_FLAG_SHIFT 24

/* Flags क्रम zram pages (table[page_no].flags) */
क्रमागत zram_pageflags अणु
	/* zram slot is locked */
	ZRAM_LOCK = ZRAM_FLAG_SHIFT,
	ZRAM_SAME,	/* Page consists the same element */
	ZRAM_WB,	/* page is stored on backing_device */
	ZRAM_UNDER_WB,	/* page is under ग_लिखोback */
	ZRAM_HUGE,	/* Incompressible page */
	ZRAM_IDLE,	/* not accessed page since last idle marking */

	__NR_ZRAM_PAGEFLAGS,
पूर्ण;

/*-- Data काष्ठाures */

/* Allocated क्रम each disk page */
काष्ठा zram_table_entry अणु
	जोड़ अणु
		अचिन्हित दीर्घ handle;
		अचिन्हित दीर्घ element;
	पूर्ण;
	अचिन्हित दीर्घ flags;
#अगर_घोषित CONFIG_ZRAM_MEMORY_TRACKING
	kसमय_प्रकार ac_समय;
#पूर्ण_अगर
पूर्ण;

काष्ठा zram_stats अणु
	atomic64_t compr_data_size;	/* compressed size of pages stored */
	atomic64_t num_पढ़ोs;	/* failed + successful */
	atomic64_t num_ग_लिखोs;	/* --करो-- */
	atomic64_t failed_पढ़ोs;	/* can happen when memory is too low */
	atomic64_t failed_ग_लिखोs;	/* can happen when memory is too low */
	atomic64_t invalid_io;	/* non-page-aligned I/O requests */
	atomic64_t notअगरy_मुक्त;	/* no. of swap slot मुक्त notअगरications */
	atomic64_t same_pages;		/* no. of same element filled pages */
	atomic64_t huge_pages;		/* no. of huge pages */
	atomic64_t huge_pages_since;	/* no. of huge pages since zram set up */
	atomic64_t pages_stored;	/* no. of pages currently stored */
	atomic_दीर्घ_t max_used_pages;	/* no. of maximum pages stored */
	atomic64_t ग_लिखोstall;		/* no. of ग_लिखो slow paths */
	atomic64_t miss_मुक्त;		/* no. of missed मुक्त */
#अगर_घोषित	CONFIG_ZRAM_WRITEBACK
	atomic64_t bd_count;		/* no. of pages in backing device */
	atomic64_t bd_पढ़ोs;		/* no. of पढ़ोs from backing device */
	atomic64_t bd_ग_लिखोs;		/* no. of ग_लिखोs from backing device */
#पूर्ण_अगर
पूर्ण;

काष्ठा zram अणु
	काष्ठा zram_table_entry *table;
	काष्ठा zs_pool *mem_pool;
	काष्ठा zcomp *comp;
	काष्ठा gendisk *disk;
	/* Prevent concurrent execution of device init */
	काष्ठा rw_semaphore init_lock;
	/*
	 * the number of pages zram can consume क्रम storing compressed data
	 */
	अचिन्हित दीर्घ limit_pages;

	काष्ठा zram_stats stats;
	/*
	 * This is the limit on amount of *uncompressed* worth of data
	 * we can store in a disk.
	 */
	u64 disksize;	/* bytes */
	अक्षर compressor[CRYPTO_MAX_ALG_NAME];
	/*
	 * zram is claimed so खोलो request will be failed
	 */
	bool claim; /* Protected by bdev->bd_mutex */
	काष्ठा file *backing_dev;
#अगर_घोषित CONFIG_ZRAM_WRITEBACK
	spinlock_t wb_limit_lock;
	bool wb_limit_enable;
	u64 bd_wb_limit;
	काष्ठा block_device *bdev;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ nr_pages;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZRAM_MEMORY_TRACKING
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर
