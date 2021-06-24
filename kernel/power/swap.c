<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/kernel/घातer/swap.c
 *
 * This file provides functions क्रम पढ़ोing the suspend image from
 * and writing it to a swap partition.
 *
 * Copyright (C) 1998,2001-2005 Pavel Machek <pavel@ucw.cz>
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 * Copyright (C) 2010-2012 Bojan Smojver <bojan@rexursive.com>
 */

#घोषणा pr_fmt(fmt) "PM: " fmt

#समावेश <linux/module.h>
#समावेश <linux/file.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/genhd.h>
#समावेश <linux/device.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/lzo.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/crc32.h>
#समावेश <linux/kसमय.स>

#समावेश "power.h"

#घोषणा HIBERNATE_SIG	"S1SUSPEND"

/*
 * When पढ़ोing an अणुun,पूर्णcompressed image, we may restore pages in place,
 * in which हाल some architectures need these pages cleaning beक्रमe they
 * can be executed. We करोn't know which pages these may be, so clean the lot.
 */
अटल bool clean_pages_on_पढ़ो;
अटल bool clean_pages_on_decompress;

/*
 *	The swap map is a data काष्ठाure used क्रम keeping track of each page
 *	written to a swap partition.  It consists of many swap_map_page
 *	काष्ठाures that contain each an array of MAP_PAGE_ENTRIES swap entries.
 *	These काष्ठाures are stored on the swap and linked together with the
 *	help of the .next_swap member.
 *
 *	The swap map is created during suspend.  The swap map pages are
 *	allocated and populated one at a समय, so we only need one memory
 *	page to set up the entire काष्ठाure.
 *
 *	During resume we pick up all swap_map_page काष्ठाures पूर्णांकo a list.
 */

#घोषणा MAP_PAGE_ENTRIES	(PAGE_SIZE / माप(sector_t) - 1)

/*
 * Number of मुक्त pages that are not high.
 */
अटल अंतरभूत अचिन्हित दीर्घ low_मुक्त_pages(व्योम)
अणु
	वापस nr_मुक्त_pages() - nr_मुक्त_highpages();
पूर्ण

/*
 * Number of pages required to be kept मुक्त जबतक writing the image. Always
 * half of all available low pages beक्रमe the writing starts.
 */
अटल अंतरभूत अचिन्हित दीर्घ reqd_मुक्त_pages(व्योम)
अणु
	वापस low_मुक्त_pages() / 2;
पूर्ण

काष्ठा swap_map_page अणु
	sector_t entries[MAP_PAGE_ENTRIES];
	sector_t next_swap;
पूर्ण;

काष्ठा swap_map_page_list अणु
	काष्ठा swap_map_page *map;
	काष्ठा swap_map_page_list *next;
पूर्ण;

/**
 *	The swap_map_handle काष्ठाure is used क्रम handling swap in
 *	a file-alike way
 */

काष्ठा swap_map_handle अणु
	काष्ठा swap_map_page *cur;
	काष्ठा swap_map_page_list *maps;
	sector_t cur_swap;
	sector_t first_sector;
	अचिन्हित पूर्णांक k;
	अचिन्हित दीर्घ reqd_मुक्त_pages;
	u32 crc32;
पूर्ण;

काष्ठा swsusp_header अणु
	अक्षर reserved[PAGE_SIZE - 20 - माप(sector_t) - माप(पूर्णांक) -
	              माप(u32)];
	u32	crc32;
	sector_t image;
	अचिन्हित पूर्णांक flags;	/* Flags to pass to the "boot" kernel */
	अक्षर	orig_sig[10];
	अक्षर	sig[10];
पूर्ण __packed;

अटल काष्ठा swsusp_header *swsusp_header;

/**
 *	The following functions are used क्रम tracing the allocated
 *	swap pages, so that they can be मुक्तd in हाल of an error.
 */

काष्ठा swsusp_extent अणु
	काष्ठा rb_node node;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल काष्ठा rb_root swsusp_extents = RB_ROOT;

अटल पूर्णांक swsusp_extents_insert(अचिन्हित दीर्घ swap_offset)
अणु
	काष्ठा rb_node **new = &(swsusp_extents.rb_node);
	काष्ठा rb_node *parent = शून्य;
	काष्ठा swsusp_extent *ext;

	/* Figure out where to put the new node */
	जबतक (*new) अणु
		ext = rb_entry(*new, काष्ठा swsusp_extent, node);
		parent = *new;
		अगर (swap_offset < ext->start) अणु
			/* Try to merge */
			अगर (swap_offset == ext->start - 1) अणु
				ext->start--;
				वापस 0;
			पूर्ण
			new = &((*new)->rb_left);
		पूर्ण अन्यथा अगर (swap_offset > ext->end) अणु
			/* Try to merge */
			अगर (swap_offset == ext->end + 1) अणु
				ext->end++;
				वापस 0;
			पूर्ण
			new = &((*new)->rb_right);
		पूर्ण अन्यथा अणु
			/* It alपढ़ोy is in the tree */
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Add the new node and rebalance the tree. */
	ext = kzalloc(माप(काष्ठा swsusp_extent), GFP_KERNEL);
	अगर (!ext)
		वापस -ENOMEM;

	ext->start = swap_offset;
	ext->end = swap_offset;
	rb_link_node(&ext->node, parent, new);
	rb_insert_color(&ext->node, &swsusp_extents);
	वापस 0;
पूर्ण

/**
 *	alloc_swapdev_block - allocate a swap page and रेजिस्टर that it has
 *	been allocated, so that it can be मुक्तd in हाल of an error.
 */

sector_t alloc_swapdev_block(पूर्णांक swap)
अणु
	अचिन्हित दीर्घ offset;

	offset = swp_offset(get_swap_page_of_type(swap));
	अगर (offset) अणु
		अगर (swsusp_extents_insert(offset))
			swap_मुक्त(swp_entry(swap, offset));
		अन्यथा
			वापस swapdev_block(swap, offset);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	मुक्त_all_swap_pages - मुक्त swap pages allocated क्रम saving image data.
 *	It also मुक्तs the extents used to रेजिस्टर which swap entries had been
 *	allocated.
 */

व्योम मुक्त_all_swap_pages(पूर्णांक swap)
अणु
	काष्ठा rb_node *node;

	जबतक ((node = swsusp_extents.rb_node)) अणु
		काष्ठा swsusp_extent *ext;
		अचिन्हित दीर्घ offset;

		ext = rb_entry(node, काष्ठा swsusp_extent, node);
		rb_erase(node, &swsusp_extents);
		क्रम (offset = ext->start; offset <= ext->end; offset++)
			swap_मुक्त(swp_entry(swap, offset));

		kमुक्त(ext);
	पूर्ण
पूर्ण

पूर्णांक swsusp_swap_in_use(व्योम)
अणु
	वापस (swsusp_extents.rb_node != शून्य);
पूर्ण

/*
 * General things
 */

अटल अचिन्हित लघु root_swap = 0xffff;
अटल काष्ठा block_device *hib_resume_bdev;

काष्ठा hib_bio_batch अणु
	atomic_t		count;
	रुको_queue_head_t	रुको;
	blk_status_t		error;
	काष्ठा blk_plug		plug;
पूर्ण;

अटल व्योम hib_init_batch(काष्ठा hib_bio_batch *hb)
अणु
	atomic_set(&hb->count, 0);
	init_रुकोqueue_head(&hb->रुको);
	hb->error = BLK_STS_OK;
	blk_start_plug(&hb->plug);
पूर्ण

अटल व्योम hib_finish_batch(काष्ठा hib_bio_batch *hb)
अणु
	blk_finish_plug(&hb->plug);
पूर्ण

अटल व्योम hib_end_io(काष्ठा bio *bio)
अणु
	काष्ठा hib_bio_batch *hb = bio->bi_निजी;
	काष्ठा page *page = bio_first_page_all(bio);

	अगर (bio->bi_status) अणु
		pr_alert("Read-error on swap-device (%u:%u:%Lu)\n",
			 MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)),
			 (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
	पूर्ण

	अगर (bio_data_dir(bio) == WRITE)
		put_page(page);
	अन्यथा अगर (clean_pages_on_पढ़ो)
		flush_icache_range((अचिन्हित दीर्घ)page_address(page),
				   (अचिन्हित दीर्घ)page_address(page) + PAGE_SIZE);

	अगर (bio->bi_status && !hb->error)
		hb->error = bio->bi_status;
	अगर (atomic_dec_and_test(&hb->count))
		wake_up(&hb->रुको);

	bio_put(bio);
पूर्ण

अटल पूर्णांक hib_submit_io(पूर्णांक op, पूर्णांक op_flags, pgoff_t page_off, व्योम *addr,
		काष्ठा hib_bio_batch *hb)
अणु
	काष्ठा page *page = virt_to_page(addr);
	काष्ठा bio *bio;
	पूर्णांक error = 0;

	bio = bio_alloc(GFP_NOIO | __GFP_HIGH, 1);
	bio->bi_iter.bi_sector = page_off * (PAGE_SIZE >> 9);
	bio_set_dev(bio, hib_resume_bdev);
	bio_set_op_attrs(bio, op, op_flags);

	अगर (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) अणु
		pr_err("Adding page to bio failed at %llu\n",
		       (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		bio_put(bio);
		वापस -EFAULT;
	पूर्ण

	अगर (hb) अणु
		bio->bi_end_io = hib_end_io;
		bio->bi_निजी = hb;
		atomic_inc(&hb->count);
		submit_bio(bio);
	पूर्ण अन्यथा अणु
		error = submit_bio_रुको(bio);
		bio_put(bio);
	पूर्ण

	वापस error;
पूर्ण

अटल blk_status_t hib_रुको_io(काष्ठा hib_bio_batch *hb)
अणु
	/*
	 * We are relying on the behavior of blk_plug that a thपढ़ो with
	 * a plug will flush the plug list beक्रमe sleeping.
	 */
	रुको_event(hb->रुको, atomic_पढ़ो(&hb->count) == 0);
	वापस blk_status_to_त्रुटि_सं(hb->error);
पूर्ण

/*
 * Saving part
 */

अटल पूर्णांक mark_swapfiles(काष्ठा swap_map_handle *handle, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक error;

	hib_submit_io(REQ_OP_READ, 0, swsusp_resume_block,
		      swsusp_header, शून्य);
	अगर (!स_भेद("SWAP-SPACE",swsusp_header->sig, 10) ||
	    !स_भेद("SWAPSPACE2",swsusp_header->sig, 10)) अणु
		स_नकल(swsusp_header->orig_sig,swsusp_header->sig, 10);
		स_नकल(swsusp_header->sig, HIBERNATE_SIG, 10);
		swsusp_header->image = handle->first_sector;
		swsusp_header->flags = flags;
		अगर (flags & SF_CRC32_MODE)
			swsusp_header->crc32 = handle->crc32;
		error = hib_submit_io(REQ_OP_WRITE, REQ_SYNC,
				      swsusp_resume_block, swsusp_header, शून्य);
	पूर्ण अन्यथा अणु
		pr_err("Swap header not found!\n");
		error = -ENODEV;
	पूर्ण
	वापस error;
पूर्ण

/**
 *	swsusp_swap_check - check अगर the resume device is a swap device
 *	and get its index (अगर so)
 *
 *	This is called beक्रमe saving image
 */
अटल पूर्णांक swsusp_swap_check(व्योम)
अणु
	पूर्णांक res;

	अगर (swsusp_resume_device)
		res = swap_type_of(swsusp_resume_device, swsusp_resume_block);
	अन्यथा
		res = find_first_swap(&swsusp_resume_device);
	अगर (res < 0)
		वापस res;
	root_swap = res;

	hib_resume_bdev = blkdev_get_by_dev(swsusp_resume_device, FMODE_WRITE,
			शून्य);
	अगर (IS_ERR(hib_resume_bdev))
		वापस PTR_ERR(hib_resume_bdev);

	res = set_blocksize(hib_resume_bdev, PAGE_SIZE);
	अगर (res < 0)
		blkdev_put(hib_resume_bdev, FMODE_WRITE);

	वापस res;
पूर्ण

/**
 *	ग_लिखो_page - Write one page to given swap location.
 *	@buf:		Address we're writing.
 *	@offset:	Offset of the swap page we're writing to.
 *	@hb:		bio completion batch
 */

अटल पूर्णांक ग_लिखो_page(व्योम *buf, sector_t offset, काष्ठा hib_bio_batch *hb)
अणु
	व्योम *src;
	पूर्णांक ret;

	अगर (!offset)
		वापस -ENOSPC;

	अगर (hb) अणु
		src = (व्योम *)__get_मुक्त_page(GFP_NOIO | __GFP_NOWARN |
		                              __GFP_NORETRY);
		अगर (src) अणु
			copy_page(src, buf);
		पूर्ण अन्यथा अणु
			ret = hib_रुको_io(hb); /* Free pages */
			अगर (ret)
				वापस ret;
			src = (व्योम *)__get_मुक्त_page(GFP_NOIO |
			                              __GFP_NOWARN |
			                              __GFP_NORETRY);
			अगर (src) अणु
				copy_page(src, buf);
			पूर्ण अन्यथा अणु
				WARN_ON_ONCE(1);
				hb = शून्य;	/* Go synchronous */
				src = buf;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		src = buf;
	पूर्ण
	वापस hib_submit_io(REQ_OP_WRITE, REQ_SYNC, offset, src, hb);
पूर्ण

अटल व्योम release_swap_ग_लिखोr(काष्ठा swap_map_handle *handle)
अणु
	अगर (handle->cur)
		मुक्त_page((अचिन्हित दीर्घ)handle->cur);
	handle->cur = शून्य;
पूर्ण

अटल पूर्णांक get_swap_ग_लिखोr(काष्ठा swap_map_handle *handle)
अणु
	पूर्णांक ret;

	ret = swsusp_swap_check();
	अगर (ret) अणु
		अगर (ret != -ENOSPC)
			pr_err("Cannot find swap device, try swapon -a\n");
		वापस ret;
	पूर्ण
	handle->cur = (काष्ठा swap_map_page *)get_zeroed_page(GFP_KERNEL);
	अगर (!handle->cur) अणु
		ret = -ENOMEM;
		जाओ err_बंद;
	पूर्ण
	handle->cur_swap = alloc_swapdev_block(root_swap);
	अगर (!handle->cur_swap) अणु
		ret = -ENOSPC;
		जाओ err_rel;
	पूर्ण
	handle->k = 0;
	handle->reqd_मुक्त_pages = reqd_मुक्त_pages();
	handle->first_sector = handle->cur_swap;
	वापस 0;
err_rel:
	release_swap_ग_लिखोr(handle);
err_बंद:
	swsusp_बंद(FMODE_WRITE);
	वापस ret;
पूर्ण

अटल पूर्णांक swap_ग_लिखो_page(काष्ठा swap_map_handle *handle, व्योम *buf,
		काष्ठा hib_bio_batch *hb)
अणु
	पूर्णांक error = 0;
	sector_t offset;

	अगर (!handle->cur)
		वापस -EINVAL;
	offset = alloc_swapdev_block(root_swap);
	error = ग_लिखो_page(buf, offset, hb);
	अगर (error)
		वापस error;
	handle->cur->entries[handle->k++] = offset;
	अगर (handle->k >= MAP_PAGE_ENTRIES) अणु
		offset = alloc_swapdev_block(root_swap);
		अगर (!offset)
			वापस -ENOSPC;
		handle->cur->next_swap = offset;
		error = ग_लिखो_page(handle->cur, handle->cur_swap, hb);
		अगर (error)
			जाओ out;
		clear_page(handle->cur);
		handle->cur_swap = offset;
		handle->k = 0;

		अगर (hb && low_मुक्त_pages() <= handle->reqd_मुक्त_pages) अणु
			error = hib_रुको_io(hb);
			अगर (error)
				जाओ out;
			/*
			 * Recalculate the number of required मुक्त pages, to
			 * make sure we never take more than half.
			 */
			handle->reqd_मुक्त_pages = reqd_मुक्त_pages();
		पूर्ण
	पूर्ण
 out:
	वापस error;
पूर्ण

अटल पूर्णांक flush_swap_ग_लिखोr(काष्ठा swap_map_handle *handle)
अणु
	अगर (handle->cur && handle->cur_swap)
		वापस ग_लिखो_page(handle->cur, handle->cur_swap, शून्य);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक swap_ग_लिखोr_finish(काष्ठा swap_map_handle *handle,
		अचिन्हित पूर्णांक flags, पूर्णांक error)
अणु
	अगर (!error) अणु
		pr_info("S");
		error = mark_swapfiles(handle, flags);
		pr_cont("|\n");
		flush_swap_ग_लिखोr(handle);
	पूर्ण

	अगर (error)
		मुक्त_all_swap_pages(root_swap);
	release_swap_ग_लिखोr(handle);
	swsusp_बंद(FMODE_WRITE);

	वापस error;
पूर्ण

/* We need to remember how much compressed data we need to पढ़ो. */
#घोषणा LZO_HEADER	माप(माप_प्रकार)

/* Number of pages/bytes we'll compress at one समय. */
#घोषणा LZO_UNC_PAGES	32
#घोषणा LZO_UNC_SIZE	(LZO_UNC_PAGES * PAGE_SIZE)

/* Number of pages/bytes we need क्रम compressed data (worst हाल). */
#घोषणा LZO_CMP_PAGES	DIV_ROUND_UP(lzo1x_worst_compress(LZO_UNC_SIZE) + \
			             LZO_HEADER, PAGE_SIZE)
#घोषणा LZO_CMP_SIZE	(LZO_CMP_PAGES * PAGE_SIZE)

/* Maximum number of thपढ़ोs क्रम compression/decompression. */
#घोषणा LZO_THREADS	3

/* Minimum/maximum number of pages क्रम पढ़ो buffering. */
#घोषणा LZO_MIN_RD_PAGES	1024
#घोषणा LZO_MAX_RD_PAGES	8192


/**
 *	save_image - save the suspend image data
 */

अटल पूर्णांक save_image(काष्ठा swap_map_handle *handle,
                      काष्ठा snapshot_handle *snapshot,
                      अचिन्हित पूर्णांक nr_to_ग_लिखो)
अणु
	अचिन्हित पूर्णांक m;
	पूर्णांक ret;
	पूर्णांक nr_pages;
	पूर्णांक err2;
	काष्ठा hib_bio_batch hb;
	kसमय_प्रकार start;
	kसमय_प्रकार stop;

	hib_init_batch(&hb);

	pr_info("Saving image data pages (%u pages)...\n",
		nr_to_ग_लिखो);
	m = nr_to_ग_लिखो / 10;
	अगर (!m)
		m = 1;
	nr_pages = 0;
	start = kसमय_get();
	जबतक (1) अणु
		ret = snapshot_पढ़ो_next(snapshot);
		अगर (ret <= 0)
			अवरोध;
		ret = swap_ग_लिखो_page(handle, data_of(*snapshot), &hb);
		अगर (ret)
			अवरोध;
		अगर (!(nr_pages % m))
			pr_info("Image saving progress: %3d%%\n",
				nr_pages / m * 10);
		nr_pages++;
	पूर्ण
	err2 = hib_रुको_io(&hb);
	hib_finish_batch(&hb);
	stop = kसमय_get();
	अगर (!ret)
		ret = err2;
	अगर (!ret)
		pr_info("Image saving done\n");
	swsusp_show_speed(start, stop, nr_to_ग_लिखो, "Wrote");
	वापस ret;
पूर्ण

/**
 * Structure used क्रम CRC32.
 */
काष्ठा crc_data अणु
	काष्ठा task_काष्ठा *thr;                  /* thपढ़ो */
	atomic_t पढ़ोy;                           /* पढ़ोy to start flag */
	atomic_t stop;                            /* पढ़ोy to stop flag */
	अचिन्हित run_thपढ़ोs;                     /* nr current thपढ़ोs */
	रुको_queue_head_t go;                     /* start crc update */
	रुको_queue_head_t करोne;                   /* crc update करोne */
	u32 *crc32;                               /* poपूर्णांकs to handle's crc32 */
	माप_प्रकार *unc_len[LZO_THREADS];             /* uncompressed lengths */
	अचिन्हित अक्षर *unc[LZO_THREADS];          /* uncompressed data */
पूर्ण;

/**
 * CRC32 update function that runs in its own thपढ़ो.
 */
अटल पूर्णांक crc32_thपढ़ोfn(व्योम *data)
अणु
	काष्ठा crc_data *d = data;
	अचिन्हित i;

	जबतक (1) अणु
		रुको_event(d->go, atomic_पढ़ो(&d->पढ़ोy) ||
		                  kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop()) अणु
			d->thr = शून्य;
			atomic_set(&d->stop, 1);
			wake_up(&d->करोne);
			अवरोध;
		पूर्ण
		atomic_set(&d->पढ़ोy, 0);

		क्रम (i = 0; i < d->run_thपढ़ोs; i++)
			*d->crc32 = crc32_le(*d->crc32,
			                     d->unc[i], *d->unc_len[i]);
		atomic_set(&d->stop, 1);
		wake_up(&d->करोne);
	पूर्ण
	वापस 0;
पूर्ण
/**
 * Structure used क्रम LZO data compression.
 */
काष्ठा cmp_data अणु
	काष्ठा task_काष्ठा *thr;                  /* thपढ़ो */
	atomic_t पढ़ोy;                           /* पढ़ोy to start flag */
	atomic_t stop;                            /* पढ़ोy to stop flag */
	पूर्णांक ret;                                  /* वापस code */
	रुको_queue_head_t go;                     /* start compression */
	रुको_queue_head_t करोne;                   /* compression करोne */
	माप_प्रकार unc_len;                           /* uncompressed length */
	माप_प्रकार cmp_len;                           /* compressed length */
	अचिन्हित अक्षर unc[LZO_UNC_SIZE];          /* uncompressed buffer */
	अचिन्हित अक्षर cmp[LZO_CMP_SIZE];          /* compressed buffer */
	अचिन्हित अक्षर wrk[LZO1X_1_MEM_COMPRESS];  /* compression workspace */
पूर्ण;

/**
 * Compression function that runs in its own thपढ़ो.
 */
अटल पूर्णांक lzo_compress_thपढ़ोfn(व्योम *data)
अणु
	काष्ठा cmp_data *d = data;

	जबतक (1) अणु
		रुको_event(d->go, atomic_पढ़ो(&d->पढ़ोy) ||
		                  kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop()) अणु
			d->thr = शून्य;
			d->ret = -1;
			atomic_set(&d->stop, 1);
			wake_up(&d->करोne);
			अवरोध;
		पूर्ण
		atomic_set(&d->पढ़ोy, 0);

		d->ret = lzo1x_1_compress(d->unc, d->unc_len,
		                          d->cmp + LZO_HEADER, &d->cmp_len,
		                          d->wrk);
		atomic_set(&d->stop, 1);
		wake_up(&d->करोne);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * save_image_lzo - Save the suspend image data compressed with LZO.
 * @handle: Swap map handle to use क्रम saving the image.
 * @snapshot: Image to पढ़ो data from.
 * @nr_to_ग_लिखो: Number of pages to save.
 */
अटल पूर्णांक save_image_lzo(काष्ठा swap_map_handle *handle,
                          काष्ठा snapshot_handle *snapshot,
                          अचिन्हित पूर्णांक nr_to_ग_लिखो)
अणु
	अचिन्हित पूर्णांक m;
	पूर्णांक ret = 0;
	पूर्णांक nr_pages;
	पूर्णांक err2;
	काष्ठा hib_bio_batch hb;
	kसमय_प्रकार start;
	kसमय_प्रकार stop;
	माप_प्रकार off;
	अचिन्हित thr, run_thपढ़ोs, nr_thपढ़ोs;
	अचिन्हित अक्षर *page = शून्य;
	काष्ठा cmp_data *data = शून्य;
	काष्ठा crc_data *crc = शून्य;

	hib_init_batch(&hb);

	/*
	 * We'll limit the number of thपढ़ोs क्रम compression to limit memory
	 * footprपूर्णांक.
	 */
	nr_thपढ़ोs = num_online_cpus() - 1;
	nr_thपढ़ोs = clamp_val(nr_thपढ़ोs, 1, LZO_THREADS);

	page = (व्योम *)__get_मुक्त_page(GFP_NOIO | __GFP_HIGH);
	अगर (!page) अणु
		pr_err("Failed to allocate LZO page\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण

	data = vदो_स्मृति(array_size(nr_thपढ़ोs, माप(*data)));
	अगर (!data) अणु
		pr_err("Failed to allocate LZO data\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++)
		स_रखो(&data[thr], 0, दुरत्व(काष्ठा cmp_data, go));

	crc = kदो_स्मृति(माप(*crc), GFP_KERNEL);
	अगर (!crc) अणु
		pr_err("Failed to allocate crc\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण
	स_रखो(crc, 0, दुरत्व(काष्ठा crc_data, go));

	/*
	 * Start the compression thपढ़ोs.
	 */
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++) अणु
		init_रुकोqueue_head(&data[thr].go);
		init_रुकोqueue_head(&data[thr].करोne);

		data[thr].thr = kthपढ़ो_run(lzo_compress_thपढ़ोfn,
		                            &data[thr],
		                            "image_compress/%u", thr);
		अगर (IS_ERR(data[thr].thr)) अणु
			data[thr].thr = शून्य;
			pr_err("Cannot start compression threads\n");
			ret = -ENOMEM;
			जाओ out_clean;
		पूर्ण
	पूर्ण

	/*
	 * Start the CRC32 thपढ़ो.
	 */
	init_रुकोqueue_head(&crc->go);
	init_रुकोqueue_head(&crc->करोne);

	handle->crc32 = 0;
	crc->crc32 = &handle->crc32;
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++) अणु
		crc->unc[thr] = data[thr].unc;
		crc->unc_len[thr] = &data[thr].unc_len;
	पूर्ण

	crc->thr = kthपढ़ो_run(crc32_thपढ़ोfn, crc, "image_crc32");
	अगर (IS_ERR(crc->thr)) अणु
		crc->thr = शून्य;
		pr_err("Cannot start CRC32 thread\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण

	/*
	 * Adjust the number of required मुक्त pages after all allocations have
	 * been करोne. We करोn't want to run out of pages when writing.
	 */
	handle->reqd_मुक्त_pages = reqd_मुक्त_pages();

	pr_info("Using %u thread(s) for compression\n", nr_thपढ़ोs);
	pr_info("Compressing and saving image data (%u pages)...\n",
		nr_to_ग_लिखो);
	m = nr_to_ग_लिखो / 10;
	अगर (!m)
		m = 1;
	nr_pages = 0;
	start = kसमय_get();
	क्रम (;;) अणु
		क्रम (thr = 0; thr < nr_thपढ़ोs; thr++) अणु
			क्रम (off = 0; off < LZO_UNC_SIZE; off += PAGE_SIZE) अणु
				ret = snapshot_पढ़ो_next(snapshot);
				अगर (ret < 0)
					जाओ out_finish;

				अगर (!ret)
					अवरोध;

				स_नकल(data[thr].unc + off,
				       data_of(*snapshot), PAGE_SIZE);

				अगर (!(nr_pages % m))
					pr_info("Image saving progress: %3d%%\n",
						nr_pages / m * 10);
				nr_pages++;
			पूर्ण
			अगर (!off)
				अवरोध;

			data[thr].unc_len = off;

			atomic_set(&data[thr].पढ़ोy, 1);
			wake_up(&data[thr].go);
		पूर्ण

		अगर (!thr)
			अवरोध;

		crc->run_thपढ़ोs = thr;
		atomic_set(&crc->पढ़ोy, 1);
		wake_up(&crc->go);

		क्रम (run_thपढ़ोs = thr, thr = 0; thr < run_thपढ़ोs; thr++) अणु
			रुको_event(data[thr].करोne,
			           atomic_पढ़ो(&data[thr].stop));
			atomic_set(&data[thr].stop, 0);

			ret = data[thr].ret;

			अगर (ret < 0) अणु
				pr_err("LZO compression failed\n");
				जाओ out_finish;
			पूर्ण

			अगर (unlikely(!data[thr].cmp_len ||
			             data[thr].cmp_len >
			             lzo1x_worst_compress(data[thr].unc_len))) अणु
				pr_err("Invalid LZO compressed length\n");
				ret = -1;
				जाओ out_finish;
			पूर्ण

			*(माप_प्रकार *)data[thr].cmp = data[thr].cmp_len;

			/*
			 * Given we are writing one page at a समय to disk, we
			 * copy that much from the buffer, although the last
			 * bit will likely be smaller than full page. This is
			 * OK - we saved the length of the compressed data, so
			 * any garbage at the end will be discarded when we
			 * पढ़ो it.
			 */
			क्रम (off = 0;
			     off < LZO_HEADER + data[thr].cmp_len;
			     off += PAGE_SIZE) अणु
				स_नकल(page, data[thr].cmp + off, PAGE_SIZE);

				ret = swap_ग_लिखो_page(handle, page, &hb);
				अगर (ret)
					जाओ out_finish;
			पूर्ण
		पूर्ण

		रुको_event(crc->करोne, atomic_पढ़ो(&crc->stop));
		atomic_set(&crc->stop, 0);
	पूर्ण

out_finish:
	err2 = hib_रुको_io(&hb);
	stop = kसमय_get();
	अगर (!ret)
		ret = err2;
	अगर (!ret)
		pr_info("Image saving done\n");
	swsusp_show_speed(start, stop, nr_to_ग_लिखो, "Wrote");
out_clean:
	hib_finish_batch(&hb);
	अगर (crc) अणु
		अगर (crc->thr)
			kthपढ़ो_stop(crc->thr);
		kमुक्त(crc);
	पूर्ण
	अगर (data) अणु
		क्रम (thr = 0; thr < nr_thपढ़ोs; thr++)
			अगर (data[thr].thr)
				kthपढ़ो_stop(data[thr].thr);
		vमुक्त(data);
	पूर्ण
	अगर (page) मुक्त_page((अचिन्हित दीर्घ)page);

	वापस ret;
पूर्ण

/**
 *	enough_swap - Make sure we have enough swap to save the image.
 *
 *	Returns TRUE or FALSE after checking the total amount of swap
 *	space available from the resume partition.
 */

अटल पूर्णांक enough_swap(अचिन्हित पूर्णांक nr_pages)
अणु
	अचिन्हित पूर्णांक मुक्त_swap = count_swap_pages(root_swap, 1);
	अचिन्हित पूर्णांक required;

	pr_debug("Free swap pages: %u\n", मुक्त_swap);

	required = PAGES_FOR_IO + nr_pages;
	वापस मुक्त_swap > required;
पूर्ण

/**
 *	swsusp_ग_लिखो - Write entire image and metadata.
 *	@flags: flags to pass to the "boot" kernel in the image header
 *
 *	It is important _NOT_ to umount fileप्रणालीs at this poपूर्णांक. We want
 *	them synced (in हाल something goes wrong) but we DO not want to mark
 *	fileप्रणाली clean: it is not. (And it करोes not matter, अगर we resume
 *	correctly, we'll mark प्रणाली clean, anyway.)
 */

पूर्णांक swsusp_ग_लिखो(अचिन्हित पूर्णांक flags)
अणु
	काष्ठा swap_map_handle handle;
	काष्ठा snapshot_handle snapshot;
	काष्ठा swsusp_info *header;
	अचिन्हित दीर्घ pages;
	पूर्णांक error;

	pages = snapshot_get_image_size();
	error = get_swap_ग_लिखोr(&handle);
	अगर (error) अणु
		pr_err("Cannot get swap writer\n");
		वापस error;
	पूर्ण
	अगर (flags & SF_NOCOMPRESS_MODE) अणु
		अगर (!enough_swap(pages)) अणु
			pr_err("Not enough free swap\n");
			error = -ENOSPC;
			जाओ out_finish;
		पूर्ण
	पूर्ण
	स_रखो(&snapshot, 0, माप(काष्ठा snapshot_handle));
	error = snapshot_पढ़ो_next(&snapshot);
	अगर (error < (पूर्णांक)PAGE_SIZE) अणु
		अगर (error >= 0)
			error = -EFAULT;

		जाओ out_finish;
	पूर्ण
	header = (काष्ठा swsusp_info *)data_of(snapshot);
	error = swap_ग_लिखो_page(&handle, header, शून्य);
	अगर (!error) अणु
		error = (flags & SF_NOCOMPRESS_MODE) ?
			save_image(&handle, &snapshot, pages - 1) :
			save_image_lzo(&handle, &snapshot, pages - 1);
	पूर्ण
out_finish:
	error = swap_ग_लिखोr_finish(&handle, flags, error);
	वापस error;
पूर्ण

/**
 *	The following functions allow us to पढ़ो data using a swap map
 *	in a file-alike way
 */

अटल व्योम release_swap_पढ़ोer(काष्ठा swap_map_handle *handle)
अणु
	काष्ठा swap_map_page_list *पंचांगp;

	जबतक (handle->maps) अणु
		अगर (handle->maps->map)
			मुक्त_page((अचिन्हित दीर्घ)handle->maps->map);
		पंचांगp = handle->maps;
		handle->maps = handle->maps->next;
		kमुक्त(पंचांगp);
	पूर्ण
	handle->cur = शून्य;
पूर्ण

अटल पूर्णांक get_swap_पढ़ोer(काष्ठा swap_map_handle *handle,
		अचिन्हित पूर्णांक *flags_p)
अणु
	पूर्णांक error;
	काष्ठा swap_map_page_list *पंचांगp, *last;
	sector_t offset;

	*flags_p = swsusp_header->flags;

	अगर (!swsusp_header->image) /* how can this happen? */
		वापस -EINVAL;

	handle->cur = शून्य;
	last = handle->maps = शून्य;
	offset = swsusp_header->image;
	जबतक (offset) अणु
		पंचांगp = kzalloc(माप(*handle->maps), GFP_KERNEL);
		अगर (!पंचांगp) अणु
			release_swap_पढ़ोer(handle);
			वापस -ENOMEM;
		पूर्ण
		अगर (!handle->maps)
			handle->maps = पंचांगp;
		अगर (last)
			last->next = पंचांगp;
		last = पंचांगp;

		पंचांगp->map = (काष्ठा swap_map_page *)
			   __get_मुक्त_page(GFP_NOIO | __GFP_HIGH);
		अगर (!पंचांगp->map) अणु
			release_swap_पढ़ोer(handle);
			वापस -ENOMEM;
		पूर्ण

		error = hib_submit_io(REQ_OP_READ, 0, offset, पंचांगp->map, शून्य);
		अगर (error) अणु
			release_swap_पढ़ोer(handle);
			वापस error;
		पूर्ण
		offset = पंचांगp->map->next_swap;
	पूर्ण
	handle->k = 0;
	handle->cur = handle->maps->map;
	वापस 0;
पूर्ण

अटल पूर्णांक swap_पढ़ो_page(काष्ठा swap_map_handle *handle, व्योम *buf,
		काष्ठा hib_bio_batch *hb)
अणु
	sector_t offset;
	पूर्णांक error;
	काष्ठा swap_map_page_list *पंचांगp;

	अगर (!handle->cur)
		वापस -EINVAL;
	offset = handle->cur->entries[handle->k];
	अगर (!offset)
		वापस -EFAULT;
	error = hib_submit_io(REQ_OP_READ, 0, offset, buf, hb);
	अगर (error)
		वापस error;
	अगर (++handle->k >= MAP_PAGE_ENTRIES) अणु
		handle->k = 0;
		मुक्त_page((अचिन्हित दीर्घ)handle->maps->map);
		पंचांगp = handle->maps;
		handle->maps = handle->maps->next;
		kमुक्त(पंचांगp);
		अगर (!handle->maps)
			release_swap_पढ़ोer(handle);
		अन्यथा
			handle->cur = handle->maps->map;
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक swap_पढ़ोer_finish(काष्ठा swap_map_handle *handle)
अणु
	release_swap_पढ़ोer(handle);

	वापस 0;
पूर्ण

/**
 *	load_image - load the image using the swap map handle
 *	@handle and the snapshot handle @snapshot
 *	(assume there are @nr_pages pages to load)
 */

अटल पूर्णांक load_image(काष्ठा swap_map_handle *handle,
                      काष्ठा snapshot_handle *snapshot,
                      अचिन्हित पूर्णांक nr_to_पढ़ो)
अणु
	अचिन्हित पूर्णांक m;
	पूर्णांक ret = 0;
	kसमय_प्रकार start;
	kसमय_प्रकार stop;
	काष्ठा hib_bio_batch hb;
	पूर्णांक err2;
	अचिन्हित nr_pages;

	hib_init_batch(&hb);

	clean_pages_on_पढ़ो = true;
	pr_info("Loading image data pages (%u pages)...\n", nr_to_पढ़ो);
	m = nr_to_पढ़ो / 10;
	अगर (!m)
		m = 1;
	nr_pages = 0;
	start = kसमय_get();
	क्रम ( ; ; ) अणु
		ret = snapshot_ग_लिखो_next(snapshot);
		अगर (ret <= 0)
			अवरोध;
		ret = swap_पढ़ो_page(handle, data_of(*snapshot), &hb);
		अगर (ret)
			अवरोध;
		अगर (snapshot->sync_पढ़ो)
			ret = hib_रुको_io(&hb);
		अगर (ret)
			अवरोध;
		अगर (!(nr_pages % m))
			pr_info("Image loading progress: %3d%%\n",
				nr_pages / m * 10);
		nr_pages++;
	पूर्ण
	err2 = hib_रुको_io(&hb);
	hib_finish_batch(&hb);
	stop = kसमय_get();
	अगर (!ret)
		ret = err2;
	अगर (!ret) अणु
		pr_info("Image loading done\n");
		snapshot_ग_लिखो_finalize(snapshot);
		अगर (!snapshot_image_loaded(snapshot))
			ret = -ENODATA;
	पूर्ण
	swsusp_show_speed(start, stop, nr_to_पढ़ो, "Read");
	वापस ret;
पूर्ण

/**
 * Structure used क्रम LZO data decompression.
 */
काष्ठा dec_data अणु
	काष्ठा task_काष्ठा *thr;                  /* thपढ़ो */
	atomic_t पढ़ोy;                           /* पढ़ोy to start flag */
	atomic_t stop;                            /* पढ़ोy to stop flag */
	पूर्णांक ret;                                  /* वापस code */
	रुको_queue_head_t go;                     /* start decompression */
	रुको_queue_head_t करोne;                   /* decompression करोne */
	माप_प्रकार unc_len;                           /* uncompressed length */
	माप_प्रकार cmp_len;                           /* compressed length */
	अचिन्हित अक्षर unc[LZO_UNC_SIZE];          /* uncompressed buffer */
	अचिन्हित अक्षर cmp[LZO_CMP_SIZE];          /* compressed buffer */
पूर्ण;

/**
 * Deompression function that runs in its own thपढ़ो.
 */
अटल पूर्णांक lzo_decompress_thपढ़ोfn(व्योम *data)
अणु
	काष्ठा dec_data *d = data;

	जबतक (1) अणु
		रुको_event(d->go, atomic_पढ़ो(&d->पढ़ोy) ||
		                  kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop()) अणु
			d->thr = शून्य;
			d->ret = -1;
			atomic_set(&d->stop, 1);
			wake_up(&d->करोne);
			अवरोध;
		पूर्ण
		atomic_set(&d->पढ़ोy, 0);

		d->unc_len = LZO_UNC_SIZE;
		d->ret = lzo1x_decompress_safe(d->cmp + LZO_HEADER, d->cmp_len,
		                               d->unc, &d->unc_len);
		अगर (clean_pages_on_decompress)
			flush_icache_range((अचिन्हित दीर्घ)d->unc,
					   (अचिन्हित दीर्घ)d->unc + d->unc_len);

		atomic_set(&d->stop, 1);
		wake_up(&d->करोne);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * load_image_lzo - Load compressed image data and decompress them with LZO.
 * @handle: Swap map handle to use क्रम loading data.
 * @snapshot: Image to copy uncompressed data पूर्णांकo.
 * @nr_to_पढ़ो: Number of pages to load.
 */
अटल पूर्णांक load_image_lzo(काष्ठा swap_map_handle *handle,
                          काष्ठा snapshot_handle *snapshot,
                          अचिन्हित पूर्णांक nr_to_पढ़ो)
अणु
	अचिन्हित पूर्णांक m;
	पूर्णांक ret = 0;
	पूर्णांक eof = 0;
	काष्ठा hib_bio_batch hb;
	kसमय_प्रकार start;
	kसमय_प्रकार stop;
	अचिन्हित nr_pages;
	माप_प्रकार off;
	अचिन्हित i, thr, run_thपढ़ोs, nr_thपढ़ोs;
	अचिन्हित ring = 0, pg = 0, ring_size = 0,
	         have = 0, want, need, asked = 0;
	अचिन्हित दीर्घ पढ़ो_pages = 0;
	अचिन्हित अक्षर **page = शून्य;
	काष्ठा dec_data *data = शून्य;
	काष्ठा crc_data *crc = शून्य;

	hib_init_batch(&hb);

	/*
	 * We'll limit the number of thपढ़ोs क्रम decompression to limit memory
	 * footprपूर्णांक.
	 */
	nr_thपढ़ोs = num_online_cpus() - 1;
	nr_thपढ़ोs = clamp_val(nr_thपढ़ोs, 1, LZO_THREADS);

	page = vदो_स्मृति(array_size(LZO_MAX_RD_PAGES, माप(*page)));
	अगर (!page) अणु
		pr_err("Failed to allocate LZO page\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण

	data = vदो_स्मृति(array_size(nr_thपढ़ोs, माप(*data)));
	अगर (!data) अणु
		pr_err("Failed to allocate LZO data\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++)
		स_रखो(&data[thr], 0, दुरत्व(काष्ठा dec_data, go));

	crc = kदो_स्मृति(माप(*crc), GFP_KERNEL);
	अगर (!crc) अणु
		pr_err("Failed to allocate crc\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण
	स_रखो(crc, 0, दुरत्व(काष्ठा crc_data, go));

	clean_pages_on_decompress = true;

	/*
	 * Start the decompression thपढ़ोs.
	 */
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++) अणु
		init_रुकोqueue_head(&data[thr].go);
		init_रुकोqueue_head(&data[thr].करोne);

		data[thr].thr = kthपढ़ो_run(lzo_decompress_thपढ़ोfn,
		                            &data[thr],
		                            "image_decompress/%u", thr);
		अगर (IS_ERR(data[thr].thr)) अणु
			data[thr].thr = शून्य;
			pr_err("Cannot start decompression threads\n");
			ret = -ENOMEM;
			जाओ out_clean;
		पूर्ण
	पूर्ण

	/*
	 * Start the CRC32 thपढ़ो.
	 */
	init_रुकोqueue_head(&crc->go);
	init_रुकोqueue_head(&crc->करोne);

	handle->crc32 = 0;
	crc->crc32 = &handle->crc32;
	क्रम (thr = 0; thr < nr_thपढ़ोs; thr++) अणु
		crc->unc[thr] = data[thr].unc;
		crc->unc_len[thr] = &data[thr].unc_len;
	पूर्ण

	crc->thr = kthपढ़ो_run(crc32_thपढ़ोfn, crc, "image_crc32");
	अगर (IS_ERR(crc->thr)) अणु
		crc->thr = शून्य;
		pr_err("Cannot start CRC32 thread\n");
		ret = -ENOMEM;
		जाओ out_clean;
	पूर्ण

	/*
	 * Set the number of pages क्रम पढ़ो buffering.
	 * This is complete guesswork, because we'll only know the real
	 * picture once prepare_image() is called, which is much later on
	 * during the image load phase. We'll assume the worst हाल and
	 * say that none of the image pages are from high memory.
	 */
	अगर (low_मुक्त_pages() > snapshot_get_image_size())
		पढ़ो_pages = (low_मुक्त_pages() - snapshot_get_image_size()) / 2;
	पढ़ो_pages = clamp_val(पढ़ो_pages, LZO_MIN_RD_PAGES, LZO_MAX_RD_PAGES);

	क्रम (i = 0; i < पढ़ो_pages; i++) अणु
		page[i] = (व्योम *)__get_मुक्त_page(i < LZO_CMP_PAGES ?
						  GFP_NOIO | __GFP_HIGH :
						  GFP_NOIO | __GFP_NOWARN |
						  __GFP_NORETRY);

		अगर (!page[i]) अणु
			अगर (i < LZO_CMP_PAGES) अणु
				ring_size = i;
				pr_err("Failed to allocate LZO pages\n");
				ret = -ENOMEM;
				जाओ out_clean;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	want = ring_size = i;

	pr_info("Using %u thread(s) for decompression\n", nr_thपढ़ोs);
	pr_info("Loading and decompressing image data (%u pages)...\n",
		nr_to_पढ़ो);
	m = nr_to_पढ़ो / 10;
	अगर (!m)
		m = 1;
	nr_pages = 0;
	start = kसमय_get();

	ret = snapshot_ग_लिखो_next(snapshot);
	अगर (ret <= 0)
		जाओ out_finish;

	क्रम(;;) अणु
		क्रम (i = 0; !eof && i < want; i++) अणु
			ret = swap_पढ़ो_page(handle, page[ring], &hb);
			अगर (ret) अणु
				/*
				 * On real पढ़ो error, finish. On end of data,
				 * set खातापूर्ण flag and just निकास the पढ़ो loop.
				 */
				अगर (handle->cur &&
				    handle->cur->entries[handle->k]) अणु
					जाओ out_finish;
				पूर्ण अन्यथा अणु
					eof = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (++ring >= ring_size)
				ring = 0;
		पूर्ण
		asked += i;
		want -= i;

		/*
		 * We are out of data, रुको क्रम some more.
		 */
		अगर (!have) अणु
			अगर (!asked)
				अवरोध;

			ret = hib_रुको_io(&hb);
			अगर (ret)
				जाओ out_finish;
			have += asked;
			asked = 0;
			अगर (eof)
				eof = 2;
		पूर्ण

		अगर (crc->run_thपढ़ोs) अणु
			रुको_event(crc->करोne, atomic_पढ़ो(&crc->stop));
			atomic_set(&crc->stop, 0);
			crc->run_thपढ़ोs = 0;
		पूर्ण

		क्रम (thr = 0; have && thr < nr_thपढ़ोs; thr++) अणु
			data[thr].cmp_len = *(माप_प्रकार *)page[pg];
			अगर (unlikely(!data[thr].cmp_len ||
			             data[thr].cmp_len >
			             lzo1x_worst_compress(LZO_UNC_SIZE))) अणु
				pr_err("Invalid LZO compressed length\n");
				ret = -1;
				जाओ out_finish;
			पूर्ण

			need = DIV_ROUND_UP(data[thr].cmp_len + LZO_HEADER,
			                    PAGE_SIZE);
			अगर (need > have) अणु
				अगर (eof > 1) अणु
					ret = -1;
					जाओ out_finish;
				पूर्ण
				अवरोध;
			पूर्ण

			क्रम (off = 0;
			     off < LZO_HEADER + data[thr].cmp_len;
			     off += PAGE_SIZE) अणु
				स_नकल(data[thr].cmp + off,
				       page[pg], PAGE_SIZE);
				have--;
				want++;
				अगर (++pg >= ring_size)
					pg = 0;
			पूर्ण

			atomic_set(&data[thr].पढ़ोy, 1);
			wake_up(&data[thr].go);
		पूर्ण

		/*
		 * Wait क्रम more data जबतक we are decompressing.
		 */
		अगर (have < LZO_CMP_PAGES && asked) अणु
			ret = hib_रुको_io(&hb);
			अगर (ret)
				जाओ out_finish;
			have += asked;
			asked = 0;
			अगर (eof)
				eof = 2;
		पूर्ण

		क्रम (run_thपढ़ोs = thr, thr = 0; thr < run_thपढ़ोs; thr++) अणु
			रुको_event(data[thr].करोne,
			           atomic_पढ़ो(&data[thr].stop));
			atomic_set(&data[thr].stop, 0);

			ret = data[thr].ret;

			अगर (ret < 0) अणु
				pr_err("LZO decompression failed\n");
				जाओ out_finish;
			पूर्ण

			अगर (unlikely(!data[thr].unc_len ||
			             data[thr].unc_len > LZO_UNC_SIZE ||
			             data[thr].unc_len & (PAGE_SIZE - 1))) अणु
				pr_err("Invalid LZO uncompressed length\n");
				ret = -1;
				जाओ out_finish;
			पूर्ण

			क्रम (off = 0;
			     off < data[thr].unc_len; off += PAGE_SIZE) अणु
				स_नकल(data_of(*snapshot),
				       data[thr].unc + off, PAGE_SIZE);

				अगर (!(nr_pages % m))
					pr_info("Image loading progress: %3d%%\n",
						nr_pages / m * 10);
				nr_pages++;

				ret = snapshot_ग_लिखो_next(snapshot);
				अगर (ret <= 0) अणु
					crc->run_thपढ़ोs = thr + 1;
					atomic_set(&crc->पढ़ोy, 1);
					wake_up(&crc->go);
					जाओ out_finish;
				पूर्ण
			पूर्ण
		पूर्ण

		crc->run_thपढ़ोs = thr;
		atomic_set(&crc->पढ़ोy, 1);
		wake_up(&crc->go);
	पूर्ण

out_finish:
	अगर (crc->run_thपढ़ोs) अणु
		रुको_event(crc->करोne, atomic_पढ़ो(&crc->stop));
		atomic_set(&crc->stop, 0);
	पूर्ण
	stop = kसमय_get();
	अगर (!ret) अणु
		pr_info("Image loading done\n");
		snapshot_ग_लिखो_finalize(snapshot);
		अगर (!snapshot_image_loaded(snapshot))
			ret = -ENODATA;
		अगर (!ret) अणु
			अगर (swsusp_header->flags & SF_CRC32_MODE) अणु
				अगर(handle->crc32 != swsusp_header->crc32) अणु
					pr_err("Invalid image CRC32!\n");
					ret = -ENODATA;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	swsusp_show_speed(start, stop, nr_to_पढ़ो, "Read");
out_clean:
	hib_finish_batch(&hb);
	क्रम (i = 0; i < ring_size; i++)
		मुक्त_page((अचिन्हित दीर्घ)page[i]);
	अगर (crc) अणु
		अगर (crc->thr)
			kthपढ़ो_stop(crc->thr);
		kमुक्त(crc);
	पूर्ण
	अगर (data) अणु
		क्रम (thr = 0; thr < nr_thपढ़ोs; thr++)
			अगर (data[thr].thr)
				kthपढ़ो_stop(data[thr].thr);
		vमुक्त(data);
	पूर्ण
	vमुक्त(page);

	वापस ret;
पूर्ण

/**
 *	swsusp_पढ़ो - पढ़ो the hibernation image.
 *	@flags_p: flags passed by the "frozen" kernel in the image header should
 *		  be written पूर्णांकo this memory location
 */

पूर्णांक swsusp_पढ़ो(अचिन्हित पूर्णांक *flags_p)
अणु
	पूर्णांक error;
	काष्ठा swap_map_handle handle;
	काष्ठा snapshot_handle snapshot;
	काष्ठा swsusp_info *header;

	स_रखो(&snapshot, 0, माप(काष्ठा snapshot_handle));
	error = snapshot_ग_लिखो_next(&snapshot);
	अगर (error < (पूर्णांक)PAGE_SIZE)
		वापस error < 0 ? error : -EFAULT;
	header = (काष्ठा swsusp_info *)data_of(snapshot);
	error = get_swap_पढ़ोer(&handle, flags_p);
	अगर (error)
		जाओ end;
	अगर (!error)
		error = swap_पढ़ो_page(&handle, header, शून्य);
	अगर (!error) अणु
		error = (*flags_p & SF_NOCOMPRESS_MODE) ?
			load_image(&handle, &snapshot, header->pages - 1) :
			load_image_lzo(&handle, &snapshot, header->pages - 1);
	पूर्ण
	swap_पढ़ोer_finish(&handle);
end:
	अगर (!error)
		pr_debug("Image successfully loaded\n");
	अन्यथा
		pr_debug("Error %d resuming\n", error);
	वापस error;
पूर्ण

/**
 *      swsusp_check - Check क्रम swsusp signature in the resume device
 */

पूर्णांक swsusp_check(व्योम)
अणु
	पूर्णांक error;

	hib_resume_bdev = blkdev_get_by_dev(swsusp_resume_device,
					    FMODE_READ, शून्य);
	अगर (!IS_ERR(hib_resume_bdev)) अणु
		set_blocksize(hib_resume_bdev, PAGE_SIZE);
		clear_page(swsusp_header);
		error = hib_submit_io(REQ_OP_READ, 0,
					swsusp_resume_block,
					swsusp_header, शून्य);
		अगर (error)
			जाओ put;

		अगर (!स_भेद(HIBERNATE_SIG, swsusp_header->sig, 10)) अणु
			स_नकल(swsusp_header->sig, swsusp_header->orig_sig, 10);
			/* Reset swap signature now */
			error = hib_submit_io(REQ_OP_WRITE, REQ_SYNC,
						swsusp_resume_block,
						swsusp_header, शून्य);
		पूर्ण अन्यथा अणु
			error = -EINVAL;
		पूर्ण

put:
		अगर (error)
			blkdev_put(hib_resume_bdev, FMODE_READ);
		अन्यथा
			pr_debug("Image signature found, resuming\n");
	पूर्ण अन्यथा अणु
		error = PTR_ERR(hib_resume_bdev);
	पूर्ण

	अगर (error)
		pr_debug("Image not found (code %d)\n", error);

	वापस error;
पूर्ण

/**
 *	swsusp_बंद - बंद swap device.
 */

व्योम swsusp_बंद(भ_शेषe_t mode)
अणु
	अगर (IS_ERR(hib_resume_bdev)) अणु
		pr_debug("Image device not initialised\n");
		वापस;
	पूर्ण

	blkdev_put(hib_resume_bdev, mode);
पूर्ण

/**
 *      swsusp_unmark - Unmark swsusp signature in the resume device
 */

#अगर_घोषित CONFIG_SUSPEND
पूर्णांक swsusp_unmark(व्योम)
अणु
	पूर्णांक error;

	hib_submit_io(REQ_OP_READ, 0, swsusp_resume_block,
		      swsusp_header, शून्य);
	अगर (!स_भेद(HIBERNATE_SIG,swsusp_header->sig, 10)) अणु
		स_नकल(swsusp_header->sig,swsusp_header->orig_sig, 10);
		error = hib_submit_io(REQ_OP_WRITE, REQ_SYNC,
					swsusp_resume_block,
					swsusp_header, शून्य);
	पूर्ण अन्यथा अणु
		pr_err("Cannot find swsusp signature!\n");
		error = -ENODEV;
	पूर्ण

	/*
	 * We just वापसed from suspend, we करोn't need the image any more.
	 */
	मुक्त_all_swap_pages(root_swap);

	वापस error;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init swsusp_header_init(व्योम)
अणु
	swsusp_header = (काष्ठा swsusp_header*) __get_मुक्त_page(GFP_KERNEL);
	अगर (!swsusp_header)
		panic("Could not allocate memory for swsusp_header\n");
	वापस 0;
पूर्ण

core_initcall(swsusp_header_init);
