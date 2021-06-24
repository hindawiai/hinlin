<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software
 * Copyright (C) 2006 Red Hat GmbH
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"

#समावेश <linux/device-mapper.h>

#समावेश <linux/bपन.स>
#समावेश <linux/completion.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dm-पन.स>

#घोषणा DM_MSG_PREFIX "io"

#घोषणा DM_IO_MAX_REGIONS	BITS_PER_LONG

काष्ठा dm_io_client अणु
	mempool_t pool;
	काष्ठा bio_set bios;
पूर्ण;

/*
 * Aligning 'struct io' reduces the number of bits required to store
 * its address.  Refer to store_io_and_region_in_bio() below.
 */
काष्ठा io अणु
	अचिन्हित दीर्घ error_bits;
	atomic_t count;
	काष्ठा dm_io_client *client;
	io_notअगरy_fn callback;
	व्योम *context;
	व्योम *vma_invalidate_address;
	अचिन्हित दीर्घ vma_invalidate_size;
पूर्ण __attribute__((aligned(DM_IO_MAX_REGIONS)));

अटल काष्ठा kmem_cache *_dm_io_cache;

/*
 * Create a client with mempool and bioset.
 */
काष्ठा dm_io_client *dm_io_client_create(व्योम)
अणु
	काष्ठा dm_io_client *client;
	अचिन्हित min_ios = dm_get_reserved_bio_based_ios();
	पूर्णांक ret;

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस ERR_PTR(-ENOMEM);

	ret = mempool_init_slab_pool(&client->pool, min_ios, _dm_io_cache);
	अगर (ret)
		जाओ bad;

	ret = bioset_init(&client->bios, min_ios, 0, BIOSET_NEED_BVECS);
	अगर (ret)
		जाओ bad;

	वापस client;

   bad:
	mempool_निकास(&client->pool);
	kमुक्त(client);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(dm_io_client_create);

व्योम dm_io_client_destroy(काष्ठा dm_io_client *client)
अणु
	mempool_निकास(&client->pool);
	bioset_निकास(&client->bios);
	kमुक्त(client);
पूर्ण
EXPORT_SYMBOL(dm_io_client_destroy);

/*-----------------------------------------------------------------
 * We need to keep track of which region a bio is करोing io क्रम.
 * To aव्योम a memory allocation to store just 5 or 6 bits, we
 * ensure the 'struct io' poपूर्णांकer is aligned so enough low bits are
 * always zero and then combine it with the region number directly in
 * bi_निजी.
 *---------------------------------------------------------------*/
अटल व्योम store_io_and_region_in_bio(काष्ठा bio *bio, काष्ठा io *io,
				       अचिन्हित region)
अणु
	अगर (unlikely(!IS_ALIGNED((अचिन्हित दीर्घ)io, DM_IO_MAX_REGIONS))) अणु
		DMCRIT("Unaligned struct io pointer %p", io);
		BUG();
	पूर्ण

	bio->bi_निजी = (व्योम *)((अचिन्हित दीर्घ)io | region);
पूर्ण

अटल व्योम retrieve_io_and_region_from_bio(काष्ठा bio *bio, काष्ठा io **io,
				       अचिन्हित *region)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)bio->bi_निजी;

	*io = (व्योम *)(val & -(अचिन्हित दीर्घ)DM_IO_MAX_REGIONS);
	*region = val & (DM_IO_MAX_REGIONS - 1);
पूर्ण

/*-----------------------------------------------------------------
 * We need an io object to keep track of the number of bios that
 * have been dispatched क्रम a particular io.
 *---------------------------------------------------------------*/
अटल व्योम complete_io(काष्ठा io *io)
अणु
	अचिन्हित दीर्घ error_bits = io->error_bits;
	io_notअगरy_fn fn = io->callback;
	व्योम *context = io->context;

	अगर (io->vma_invalidate_size)
		invalidate_kernel_vmap_range(io->vma_invalidate_address,
					     io->vma_invalidate_size);

	mempool_मुक्त(io, &io->client->pool);
	fn(error_bits, context);
पूर्ण

अटल व्योम dec_count(काष्ठा io *io, अचिन्हित पूर्णांक region, blk_status_t error)
अणु
	अगर (error)
		set_bit(region, &io->error_bits);

	अगर (atomic_dec_and_test(&io->count))
		complete_io(io);
पूर्ण

अटल व्योम endio(काष्ठा bio *bio)
अणु
	काष्ठा io *io;
	अचिन्हित region;
	blk_status_t error;

	अगर (bio->bi_status && bio_data_dir(bio) == READ)
		zero_fill_bio(bio);

	/*
	 * The bio deकाष्ठाor in bio_put() may use the io object.
	 */
	retrieve_io_and_region_from_bio(bio, &io, &region);

	error = bio->bi_status;
	bio_put(bio);

	dec_count(io, region, error);
पूर्ण

/*-----------------------------------------------------------------
 * These little objects provide an असलtraction क्रम getting a new
 * destination page क्रम io.
 *---------------------------------------------------------------*/
काष्ठा dpages अणु
	व्योम (*get_page)(काष्ठा dpages *dp,
			 काष्ठा page **p, अचिन्हित दीर्घ *len, अचिन्हित *offset);
	व्योम (*next_page)(काष्ठा dpages *dp);

	जोड़ अणु
		अचिन्हित context_u;
		काष्ठा bvec_iter context_bi;
	पूर्ण;
	व्योम *context_ptr;

	व्योम *vma_invalidate_address;
	अचिन्हित दीर्घ vma_invalidate_size;
पूर्ण;

/*
 * Functions क्रम getting the pages from a list.
 */
अटल व्योम list_get_page(काष्ठा dpages *dp,
		  काष्ठा page **p, अचिन्हित दीर्घ *len, अचिन्हित *offset)
अणु
	अचिन्हित o = dp->context_u;
	काष्ठा page_list *pl = (काष्ठा page_list *) dp->context_ptr;

	*p = pl->page;
	*len = PAGE_SIZE - o;
	*offset = o;
पूर्ण

अटल व्योम list_next_page(काष्ठा dpages *dp)
अणु
	काष्ठा page_list *pl = (काष्ठा page_list *) dp->context_ptr;
	dp->context_ptr = pl->next;
	dp->context_u = 0;
पूर्ण

अटल व्योम list_dp_init(काष्ठा dpages *dp, काष्ठा page_list *pl, अचिन्हित offset)
अणु
	dp->get_page = list_get_page;
	dp->next_page = list_next_page;
	dp->context_u = offset;
	dp->context_ptr = pl;
पूर्ण

/*
 * Functions क्रम getting the pages from a bvec.
 */
अटल व्योम bio_get_page(काष्ठा dpages *dp, काष्ठा page **p,
			 अचिन्हित दीर्घ *len, अचिन्हित *offset)
अणु
	काष्ठा bio_vec bvec = bvec_iter_bvec((काष्ठा bio_vec *)dp->context_ptr,
					     dp->context_bi);

	*p = bvec.bv_page;
	*len = bvec.bv_len;
	*offset = bvec.bv_offset;

	/* aव्योम figuring it out again in bio_next_page() */
	dp->context_bi.bi_sector = (sector_t)bvec.bv_len;
पूर्ण

अटल व्योम bio_next_page(काष्ठा dpages *dp)
अणु
	अचिन्हित पूर्णांक len = (अचिन्हित पूर्णांक)dp->context_bi.bi_sector;

	bvec_iter_advance((काष्ठा bio_vec *)dp->context_ptr,
			  &dp->context_bi, len);
पूर्ण

अटल व्योम bio_dp_init(काष्ठा dpages *dp, काष्ठा bio *bio)
अणु
	dp->get_page = bio_get_page;
	dp->next_page = bio_next_page;

	/*
	 * We just use bvec iterator to retrieve pages, so it is ok to
	 * access the bvec table directly here
	 */
	dp->context_ptr = bio->bi_io_vec;
	dp->context_bi = bio->bi_iter;
पूर्ण

/*
 * Functions क्रम getting the pages from a VMA.
 */
अटल व्योम vm_get_page(काष्ठा dpages *dp,
		 काष्ठा page **p, अचिन्हित दीर्घ *len, अचिन्हित *offset)
अणु
	*p = vदो_स्मृति_to_page(dp->context_ptr);
	*offset = dp->context_u;
	*len = PAGE_SIZE - dp->context_u;
पूर्ण

अटल व्योम vm_next_page(काष्ठा dpages *dp)
अणु
	dp->context_ptr += PAGE_SIZE - dp->context_u;
	dp->context_u = 0;
पूर्ण

अटल व्योम vm_dp_init(काष्ठा dpages *dp, व्योम *data)
अणु
	dp->get_page = vm_get_page;
	dp->next_page = vm_next_page;
	dp->context_u = offset_in_page(data);
	dp->context_ptr = data;
पूर्ण

/*
 * Functions क्रम getting the pages from kernel memory.
 */
अटल व्योम km_get_page(काष्ठा dpages *dp, काष्ठा page **p, अचिन्हित दीर्घ *len,
			अचिन्हित *offset)
अणु
	*p = virt_to_page(dp->context_ptr);
	*offset = dp->context_u;
	*len = PAGE_SIZE - dp->context_u;
पूर्ण

अटल व्योम km_next_page(काष्ठा dpages *dp)
अणु
	dp->context_ptr += PAGE_SIZE - dp->context_u;
	dp->context_u = 0;
पूर्ण

अटल व्योम km_dp_init(काष्ठा dpages *dp, व्योम *data)
अणु
	dp->get_page = km_get_page;
	dp->next_page = km_next_page;
	dp->context_u = offset_in_page(data);
	dp->context_ptr = data;
पूर्ण

/*-----------------------------------------------------------------
 * IO routines that accept a list of pages.
 *---------------------------------------------------------------*/
अटल व्योम करो_region(पूर्णांक op, पूर्णांक op_flags, अचिन्हित region,
		      काष्ठा dm_io_region *where, काष्ठा dpages *dp,
		      काष्ठा io *io)
अणु
	काष्ठा bio *bio;
	काष्ठा page *page;
	अचिन्हित दीर्घ len;
	अचिन्हित offset;
	अचिन्हित num_bvecs;
	sector_t reमुख्यing = where->count;
	काष्ठा request_queue *q = bdev_get_queue(where->bdev);
	अचिन्हित लघु logical_block_size = queue_logical_block_size(q);
	sector_t num_sectors;
	अचिन्हित पूर्णांक special_cmd_max_sectors;

	/*
	 * Reject unsupported discard and ग_लिखो same requests.
	 */
	अगर (op == REQ_OP_DISCARD)
		special_cmd_max_sectors = q->limits.max_discard_sectors;
	अन्यथा अगर (op == REQ_OP_WRITE_ZEROES)
		special_cmd_max_sectors = q->limits.max_ग_लिखो_zeroes_sectors;
	अन्यथा अगर (op == REQ_OP_WRITE_SAME)
		special_cmd_max_sectors = q->limits.max_ग_लिखो_same_sectors;
	अगर ((op == REQ_OP_DISCARD || op == REQ_OP_WRITE_ZEROES ||
	     op == REQ_OP_WRITE_SAME) && special_cmd_max_sectors == 0) अणु
		atomic_inc(&io->count);
		dec_count(io, region, BLK_STS_NOTSUPP);
		वापस;
	पूर्ण

	/*
	 * where->count may be zero अगर op holds a flush and we need to
	 * send a zero-sized flush.
	 */
	करो अणु
		/*
		 * Allocate a suitably sized-bio.
		 */
		चयन (op) अणु
		हाल REQ_OP_DISCARD:
		हाल REQ_OP_WRITE_ZEROES:
			num_bvecs = 0;
			अवरोध;
		हाल REQ_OP_WRITE_SAME:
			num_bvecs = 1;
			अवरोध;
		शेष:
			num_bvecs = bio_max_segs(dm_sector_भाग_up(reमुख्यing,
						(PAGE_SIZE >> SECTOR_SHIFT)));
		पूर्ण

		bio = bio_alloc_bioset(GFP_NOIO, num_bvecs, &io->client->bios);
		bio->bi_iter.bi_sector = where->sector + (where->count - reमुख्यing);
		bio_set_dev(bio, where->bdev);
		bio->bi_end_io = endio;
		bio_set_op_attrs(bio, op, op_flags);
		store_io_and_region_in_bio(bio, io, region);

		अगर (op == REQ_OP_DISCARD || op == REQ_OP_WRITE_ZEROES) अणु
			num_sectors = min_t(sector_t, special_cmd_max_sectors, reमुख्यing);
			bio->bi_iter.bi_size = num_sectors << SECTOR_SHIFT;
			reमुख्यing -= num_sectors;
		पूर्ण अन्यथा अगर (op == REQ_OP_WRITE_SAME) अणु
			/*
			 * WRITE SAME only uses a single page.
			 */
			dp->get_page(dp, &page, &len, &offset);
			bio_add_page(bio, page, logical_block_size, offset);
			num_sectors = min_t(sector_t, special_cmd_max_sectors, reमुख्यing);
			bio->bi_iter.bi_size = num_sectors << SECTOR_SHIFT;

			offset = 0;
			reमुख्यing -= num_sectors;
			dp->next_page(dp);
		पूर्ण अन्यथा जबतक (reमुख्यing) अणु
			/*
			 * Try and add as many pages as possible.
			 */
			dp->get_page(dp, &page, &len, &offset);
			len = min(len, to_bytes(reमुख्यing));
			अगर (!bio_add_page(bio, page, len, offset))
				अवरोध;

			offset = 0;
			reमुख्यing -= to_sector(len);
			dp->next_page(dp);
		पूर्ण

		atomic_inc(&io->count);
		submit_bio(bio);
	पूर्ण जबतक (reमुख्यing);
पूर्ण

अटल व्योम dispatch_io(पूर्णांक op, पूर्णांक op_flags, अचिन्हित पूर्णांक num_regions,
			काष्ठा dm_io_region *where, काष्ठा dpages *dp,
			काष्ठा io *io, पूर्णांक sync)
अणु
	पूर्णांक i;
	काष्ठा dpages old_pages = *dp;

	BUG_ON(num_regions > DM_IO_MAX_REGIONS);

	अगर (sync)
		op_flags |= REQ_SYNC;

	/*
	 * For multiple regions we need to be careful to शुरुआत
	 * the dp object क्रम each call to करो_region.
	 */
	क्रम (i = 0; i < num_regions; i++) अणु
		*dp = old_pages;
		अगर (where[i].count || (op_flags & REQ_PREFLUSH))
			करो_region(op, op_flags, i, where + i, dp, io);
	पूर्ण

	/*
	 * Drop the extra reference that we were holding to aव्योम
	 * the io being completed too early.
	 */
	dec_count(io, 0, 0);
पूर्ण

काष्ठा sync_io अणु
	अचिन्हित दीर्घ error_bits;
	काष्ठा completion रुको;
पूर्ण;

अटल व्योम sync_io_complete(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा sync_io *sio = context;

	sio->error_bits = error;
	complete(&sio->रुको);
पूर्ण

अटल पूर्णांक sync_io(काष्ठा dm_io_client *client, अचिन्हित पूर्णांक num_regions,
		   काष्ठा dm_io_region *where, पूर्णांक op, पूर्णांक op_flags,
		   काष्ठा dpages *dp, अचिन्हित दीर्घ *error_bits)
अणु
	काष्ठा io *io;
	काष्ठा sync_io sio;

	अगर (num_regions > 1 && !op_is_ग_लिखो(op)) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	init_completion(&sio.रुको);

	io = mempool_alloc(&client->pool, GFP_NOIO);
	io->error_bits = 0;
	atomic_set(&io->count, 1); /* see dispatch_io() */
	io->client = client;
	io->callback = sync_io_complete;
	io->context = &sio;

	io->vma_invalidate_address = dp->vma_invalidate_address;
	io->vma_invalidate_size = dp->vma_invalidate_size;

	dispatch_io(op, op_flags, num_regions, where, dp, io, 1);

	रुको_क्रम_completion_io(&sio.रुको);

	अगर (error_bits)
		*error_bits = sio.error_bits;

	वापस sio.error_bits ? -EIO : 0;
पूर्ण

अटल पूर्णांक async_io(काष्ठा dm_io_client *client, अचिन्हित पूर्णांक num_regions,
		    काष्ठा dm_io_region *where, पूर्णांक op, पूर्णांक op_flags,
		    काष्ठा dpages *dp, io_notअगरy_fn fn, व्योम *context)
अणु
	काष्ठा io *io;

	अगर (num_regions > 1 && !op_is_ग_लिखो(op)) अणु
		WARN_ON(1);
		fn(1, context);
		वापस -EIO;
	पूर्ण

	io = mempool_alloc(&client->pool, GFP_NOIO);
	io->error_bits = 0;
	atomic_set(&io->count, 1); /* see dispatch_io() */
	io->client = client;
	io->callback = fn;
	io->context = context;

	io->vma_invalidate_address = dp->vma_invalidate_address;
	io->vma_invalidate_size = dp->vma_invalidate_size;

	dispatch_io(op, op_flags, num_regions, where, dp, io, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_init(काष्ठा dm_io_request *io_req, काष्ठा dpages *dp,
		   अचिन्हित दीर्घ size)
अणु
	/* Set up dpages based on memory type */

	dp->vma_invalidate_address = शून्य;
	dp->vma_invalidate_size = 0;

	चयन (io_req->mem.type) अणु
	हाल DM_IO_PAGE_LIST:
		list_dp_init(dp, io_req->mem.ptr.pl, io_req->mem.offset);
		अवरोध;

	हाल DM_IO_BIO:
		bio_dp_init(dp, io_req->mem.ptr.bio);
		अवरोध;

	हाल DM_IO_VMA:
		flush_kernel_vmap_range(io_req->mem.ptr.vma, size);
		अगर (io_req->bi_op == REQ_OP_READ) अणु
			dp->vma_invalidate_address = io_req->mem.ptr.vma;
			dp->vma_invalidate_size = size;
		पूर्ण
		vm_dp_init(dp, io_req->mem.ptr.vma);
		अवरोध;

	हाल DM_IO_KMEM:
		km_dp_init(dp, io_req->mem.ptr.addr);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * New collapsed (a)synchronous पूर्णांकerface.
 *
 * If the IO is asynchronous (i.e. it has notअगरy.fn), you must either unplug
 * the queue with blk_unplug() some समय later or set REQ_SYNC in
 * io_req->bi_opf. If you fail to करो one of these, the IO will be submitted to
 * the disk after q->unplug_delay, which शेषs to 3ms in blk-settings.c.
 */
पूर्णांक dm_io(काष्ठा dm_io_request *io_req, अचिन्हित num_regions,
	  काष्ठा dm_io_region *where, अचिन्हित दीर्घ *sync_error_bits)
अणु
	पूर्णांक r;
	काष्ठा dpages dp;

	r = dp_init(io_req, &dp, (अचिन्हित दीर्घ)where->count << SECTOR_SHIFT);
	अगर (r)
		वापस r;

	अगर (!io_req->notअगरy.fn)
		वापस sync_io(io_req->client, num_regions, where,
			       io_req->bi_op, io_req->bi_op_flags, &dp,
			       sync_error_bits);

	वापस async_io(io_req->client, num_regions, where, io_req->bi_op,
			io_req->bi_op_flags, &dp, io_req->notअगरy.fn,
			io_req->notअगरy.context);
पूर्ण
EXPORT_SYMBOL(dm_io);

पूर्णांक __init dm_io_init(व्योम)
अणु
	_dm_io_cache = KMEM_CACHE(io, 0);
	अगर (!_dm_io_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम dm_io_निकास(व्योम)
अणु
	kmem_cache_destroy(_dm_io_cache);
	_dm_io_cache = शून्य;
पूर्ण
