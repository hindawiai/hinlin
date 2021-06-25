<शैली गुरु>
/*
 * Copyright (C) 2001-2002 Sistina Software (UK) Limited.
 * Copyright (C) 2006-2008 Red Hat GmbH
 *
 * This file is released under the GPL.
 */

#समावेश "dm-exception-store.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-bufपन.स>

#घोषणा DM_MSG_PREFIX "persistent snapshot"
#घोषणा DM_CHUNK_SIZE_DEFAULT_SECTORS 32U	/* 16KB */

#घोषणा DM_PREFETCH_CHUNKS		12

/*-----------------------------------------------------------------
 * Persistent snapshots, by persistent we mean that the snapshot
 * will survive a reboot.
 *---------------------------------------------------------------*/

/*
 * We need to store a record of which parts of the origin have
 * been copied to the snapshot device.  The snapshot code
 * requires that we copy exception chunks to chunk aligned areas
 * of the COW store.  It makes sense thereक्रमe, to store the
 * metadata in chunk size blocks.
 *
 * There is no backward or क्रमward compatibility implemented,
 * snapshots with dअगरferent disk versions than the kernel will
 * not be usable.  It is expected that "lvcreate" will blank out
 * the start of a fresh COW device beक्रमe calling the snapshot
 * स्थिरructor.
 *
 * The first chunk of the COW device just contains the header.
 * After this there is a chunk filled with exception metadata,
 * followed by as many exception chunks as can fit in the
 * metadata areas.
 *
 * All on disk काष्ठाures are in little-endian क्रमmat.  The end
 * of the exceptions info is indicated by an exception with a
 * new_chunk of 0, which is invalid since it would poपूर्णांक to the
 * header chunk.
 */

/*
 * Magic क्रम persistent snapshots: "SnAp" - Feeble isn't it.
 */
#घोषणा SNAP_MAGIC 0x70416e53

/*
 * The on-disk version of the metadata.
 */
#घोषणा SNAPSHOT_DISK_VERSION 1

#घोषणा NUM_SNAPSHOT_HDR_CHUNKS 1

काष्ठा disk_header अणु
	__le32 magic;

	/*
	 * Is this snapshot valid.  There is no way of recovering
	 * an invalid snapshot.
	 */
	__le32 valid;

	/*
	 * Simple, incrementing version. no backward
	 * compatibility.
	 */
	__le32 version;

	/* In sectors */
	__le32 chunk_size;
पूर्ण __packed;

काष्ठा disk_exception अणु
	__le64 old_chunk;
	__le64 new_chunk;
पूर्ण __packed;

काष्ठा core_exception अणु
	uपूर्णांक64_t old_chunk;
	uपूर्णांक64_t new_chunk;
पूर्ण;

काष्ठा commit_callback अणु
	व्योम (*callback)(व्योम *, पूर्णांक success);
	व्योम *context;
पूर्ण;

/*
 * The top level काष्ठाure क्रम a persistent exception store.
 */
काष्ठा pstore अणु
	काष्ठा dm_exception_store *store;
	पूर्णांक version;
	पूर्णांक valid;
	uपूर्णांक32_t exceptions_per_area;

	/*
	 * Now that we have an asynchronous kcopyd there is no
	 * need क्रम large chunk sizes, so it wont hurt to have a
	 * whole chunks worth of metadata in memory at once.
	 */
	व्योम *area;

	/*
	 * An area of zeros used to clear the next area.
	 */
	व्योम *zero_area;

	/*
	 * An area used क्रम header. The header can be written
	 * concurrently with metadata (when invalidating the snapshot),
	 * so it needs a separate buffer.
	 */
	व्योम *header_area;

	/*
	 * Used to keep track of which metadata area the data in
	 * 'chunk' refers to.
	 */
	chunk_t current_area;

	/*
	 * The next मुक्त chunk क्रम an exception.
	 *
	 * When creating exceptions, all the chunks here and above are
	 * मुक्त.  It holds the next chunk to be allocated.  On rare
	 * occasions (e.g. after a प्रणाली crash) holes can be left in
	 * the exception store because chunks can be committed out of
	 * order.
	 *
	 * When merging exceptions, it करोes not necessarily mean all the
	 * chunks here and above are मुक्त.  It holds the value it would
	 * have held अगर all chunks had been committed in order of
	 * allocation.  Consequently the value may occasionally be
	 * slightly too low, but since it's only used for 'status' and
	 * it can never reach its minimum value too early this करोesn't
	 * matter.
	 */

	chunk_t next_मुक्त;

	/*
	 * The index of next मुक्त exception in the current
	 * metadata area.
	 */
	uपूर्णांक32_t current_committed;

	atomic_t pending_count;
	uपूर्णांक32_t callback_count;
	काष्ठा commit_callback *callbacks;
	काष्ठा dm_io_client *io_client;

	काष्ठा workqueue_काष्ठा *metadata_wq;
पूर्ण;

अटल पूर्णांक alloc_area(काष्ठा pstore *ps)
अणु
	पूर्णांक r = -ENOMEM;
	माप_प्रकार len;

	len = ps->store->chunk_size << SECTOR_SHIFT;

	/*
	 * Allocate the chunk_size block of memory that will hold
	 * a single metadata area.
	 */
	ps->area = vदो_स्मृति(len);
	अगर (!ps->area)
		जाओ err_area;

	ps->zero_area = vzalloc(len);
	अगर (!ps->zero_area)
		जाओ err_zero_area;

	ps->header_area = vदो_स्मृति(len);
	अगर (!ps->header_area)
		जाओ err_header_area;

	वापस 0;

err_header_area:
	vमुक्त(ps->zero_area);

err_zero_area:
	vमुक्त(ps->area);

err_area:
	वापस r;
पूर्ण

अटल व्योम मुक्त_area(काष्ठा pstore *ps)
अणु
	vमुक्त(ps->area);
	ps->area = शून्य;
	vमुक्त(ps->zero_area);
	ps->zero_area = शून्य;
	vमुक्त(ps->header_area);
	ps->header_area = शून्य;
पूर्ण

काष्ठा mdata_req अणु
	काष्ठा dm_io_region *where;
	काष्ठा dm_io_request *io_req;
	काष्ठा work_काष्ठा work;
	पूर्णांक result;
पूर्ण;

अटल व्योम करो_metadata(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mdata_req *req = container_of(work, काष्ठा mdata_req, work);

	req->result = dm_io(req->io_req, 1, req->where, शून्य);
पूर्ण

/*
 * Read or ग_लिखो a chunk aligned and sized block of data from a device.
 */
अटल पूर्णांक chunk_io(काष्ठा pstore *ps, व्योम *area, chunk_t chunk, पूर्णांक op,
		    पूर्णांक op_flags, पूर्णांक metadata)
अणु
	काष्ठा dm_io_region where = अणु
		.bdev = dm_snap_cow(ps->store->snap)->bdev,
		.sector = ps->store->chunk_size * chunk,
		.count = ps->store->chunk_size,
	पूर्ण;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = op,
		.bi_op_flags = op_flags,
		.mem.type = DM_IO_VMA,
		.mem.ptr.vma = area,
		.client = ps->io_client,
		.notअगरy.fn = शून्य,
	पूर्ण;
	काष्ठा mdata_req req;

	अगर (!metadata)
		वापस dm_io(&io_req, 1, &where, शून्य);

	req.where = &where;
	req.io_req = &io_req;

	/*
	 * Issue the synchronous I/O from a dअगरferent thपढ़ो
	 * to aव्योम submit_bio_noacct recursion.
	 */
	INIT_WORK_ONSTACK(&req.work, करो_metadata);
	queue_work(ps->metadata_wq, &req.work);
	flush_workqueue(ps->metadata_wq);
	destroy_work_on_stack(&req.work);

	वापस req.result;
पूर्ण

/*
 * Convert a metadata area index to a chunk index.
 */
अटल chunk_t area_location(काष्ठा pstore *ps, chunk_t area)
अणु
	वापस NUM_SNAPSHOT_HDR_CHUNKS + ((ps->exceptions_per_area + 1) * area);
पूर्ण

अटल व्योम skip_metadata(काष्ठा pstore *ps)
अणु
	uपूर्णांक32_t stride = ps->exceptions_per_area + 1;
	chunk_t next_मुक्त = ps->next_मुक्त;
	अगर (sector_भाग(next_मुक्त, stride) == NUM_SNAPSHOT_HDR_CHUNKS)
		ps->next_मुक्त++;
पूर्ण

/*
 * Read or ग_लिखो a metadata area.  Remembering to skip the first
 * chunk which holds the header.
 */
अटल पूर्णांक area_io(काष्ठा pstore *ps, पूर्णांक op, पूर्णांक op_flags)
अणु
	chunk_t chunk = area_location(ps, ps->current_area);

	वापस chunk_io(ps, ps->area, chunk, op, op_flags, 0);
पूर्ण

अटल व्योम zero_memory_area(काष्ठा pstore *ps)
अणु
	स_रखो(ps->area, 0, ps->store->chunk_size << SECTOR_SHIFT);
पूर्ण

अटल पूर्णांक zero_disk_area(काष्ठा pstore *ps, chunk_t area)
अणु
	वापस chunk_io(ps, ps->zero_area, area_location(ps, area),
			REQ_OP_WRITE, 0, 0);
पूर्ण

अटल पूर्णांक पढ़ो_header(काष्ठा pstore *ps, पूर्णांक *new_snapshot)
अणु
	पूर्णांक r;
	काष्ठा disk_header *dh;
	अचिन्हित chunk_size;
	पूर्णांक chunk_size_supplied = 1;
	अक्षर *chunk_err;

	/*
	 * Use शेष chunk size (or logical_block_size, अगर larger)
	 * अगर none supplied
	 */
	अगर (!ps->store->chunk_size) अणु
		ps->store->chunk_size = max(DM_CHUNK_SIZE_DEFAULT_SECTORS,
		    bdev_logical_block_size(dm_snap_cow(ps->store->snap)->
					    bdev) >> 9);
		ps->store->chunk_mask = ps->store->chunk_size - 1;
		ps->store->chunk_shअगरt = __ffs(ps->store->chunk_size);
		chunk_size_supplied = 0;
	पूर्ण

	ps->io_client = dm_io_client_create();
	अगर (IS_ERR(ps->io_client))
		वापस PTR_ERR(ps->io_client);

	r = alloc_area(ps);
	अगर (r)
		वापस r;

	r = chunk_io(ps, ps->header_area, 0, REQ_OP_READ, 0, 1);
	अगर (r)
		जाओ bad;

	dh = ps->header_area;

	अगर (le32_to_cpu(dh->magic) == 0) अणु
		*new_snapshot = 1;
		वापस 0;
	पूर्ण

	अगर (le32_to_cpu(dh->magic) != SNAP_MAGIC) अणु
		DMWARN("Invalid or corrupt snapshot");
		r = -ENXIO;
		जाओ bad;
	पूर्ण

	*new_snapshot = 0;
	ps->valid = le32_to_cpu(dh->valid);
	ps->version = le32_to_cpu(dh->version);
	chunk_size = le32_to_cpu(dh->chunk_size);

	अगर (ps->store->chunk_size == chunk_size)
		वापस 0;

	अगर (chunk_size_supplied)
		DMWARN("chunk size %u in device metadata overrides "
		       "table chunk size of %u.",
		       chunk_size, ps->store->chunk_size);

	/* We had a bogus chunk_size. Fix stuff up. */
	मुक्त_area(ps);

	r = dm_exception_store_set_chunk_size(ps->store, chunk_size,
					      &chunk_err);
	अगर (r) अणु
		DMERR("invalid on-disk chunk size %u: %s.",
		      chunk_size, chunk_err);
		वापस r;
	पूर्ण

	r = alloc_area(ps);
	वापस r;

bad:
	मुक्त_area(ps);
	वापस r;
पूर्ण

अटल पूर्णांक ग_लिखो_header(काष्ठा pstore *ps)
अणु
	काष्ठा disk_header *dh;

	स_रखो(ps->header_area, 0, ps->store->chunk_size << SECTOR_SHIFT);

	dh = ps->header_area;
	dh->magic = cpu_to_le32(SNAP_MAGIC);
	dh->valid = cpu_to_le32(ps->valid);
	dh->version = cpu_to_le32(ps->version);
	dh->chunk_size = cpu_to_le32(ps->store->chunk_size);

	वापस chunk_io(ps, ps->header_area, 0, REQ_OP_WRITE, 0, 1);
पूर्ण

/*
 * Access functions क्रम the disk exceptions, these करो the endian conversions.
 */
अटल काष्ठा disk_exception *get_exception(काष्ठा pstore *ps, व्योम *ps_area,
					    uपूर्णांक32_t index)
अणु
	BUG_ON(index >= ps->exceptions_per_area);

	वापस ((काष्ठा disk_exception *) ps_area) + index;
पूर्ण

अटल व्योम पढ़ो_exception(काष्ठा pstore *ps, व्योम *ps_area,
			   uपूर्णांक32_t index, काष्ठा core_exception *result)
अणु
	काष्ठा disk_exception *de = get_exception(ps, ps_area, index);

	/* copy it */
	result->old_chunk = le64_to_cpu(de->old_chunk);
	result->new_chunk = le64_to_cpu(de->new_chunk);
पूर्ण

अटल व्योम ग_लिखो_exception(काष्ठा pstore *ps,
			    uपूर्णांक32_t index, काष्ठा core_exception *e)
अणु
	काष्ठा disk_exception *de = get_exception(ps, ps->area, index);

	/* copy it */
	de->old_chunk = cpu_to_le64(e->old_chunk);
	de->new_chunk = cpu_to_le64(e->new_chunk);
पूर्ण

अटल व्योम clear_exception(काष्ठा pstore *ps, uपूर्णांक32_t index)
अणु
	काष्ठा disk_exception *de = get_exception(ps, ps->area, index);

	/* clear it */
	de->old_chunk = 0;
	de->new_chunk = 0;
पूर्ण

/*
 * Registers the exceptions that are present in the current area.
 * 'full' is filled in to indicate अगर the area has been
 * filled.
 */
अटल पूर्णांक insert_exceptions(काष्ठा pstore *ps, व्योम *ps_area,
			     पूर्णांक (*callback)(व्योम *callback_context,
					     chunk_t old, chunk_t new),
			     व्योम *callback_context,
			     पूर्णांक *full)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i;
	काष्ठा core_exception e;

	/* presume the area is full */
	*full = 1;

	क्रम (i = 0; i < ps->exceptions_per_area; i++) अणु
		पढ़ो_exception(ps, ps_area, i, &e);

		/*
		 * If the new_chunk is poपूर्णांकing at the start of
		 * the COW device, where the first metadata area
		 * is we know that we've hit the end of the
		 * exceptions.  Thereक्रमe the area is not full.
		 */
		अगर (e.new_chunk == 0LL) अणु
			ps->current_committed = i;
			*full = 0;
			अवरोध;
		पूर्ण

		/*
		 * Keep track of the start of the मुक्त chunks.
		 */
		अगर (ps->next_मुक्त <= e.new_chunk)
			ps->next_मुक्त = e.new_chunk + 1;

		/*
		 * Otherwise we add the exception to the snapshot.
		 */
		r = callback(callback_context, e.old_chunk, e.new_chunk);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_exceptions(काष्ठा pstore *ps,
			   पूर्णांक (*callback)(व्योम *callback_context, chunk_t old,
					   chunk_t new),
			   व्योम *callback_context)
अणु
	पूर्णांक r, full = 1;
	काष्ठा dm_bufio_client *client;
	chunk_t prefetch_area = 0;

	client = dm_bufio_client_create(dm_snap_cow(ps->store->snap)->bdev,
					ps->store->chunk_size << SECTOR_SHIFT,
					1, 0, शून्य, शून्य);

	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	/*
	 * Setup क्रम one current buffer + desired पढ़ोahead buffers.
	 */
	dm_bufio_set_minimum_buffers(client, 1 + DM_PREFETCH_CHUNKS);

	/*
	 * Keeping पढ़ोing chunks and inserting exceptions until
	 * we find a partially full area.
	 */
	क्रम (ps->current_area = 0; full; ps->current_area++) अणु
		काष्ठा dm_buffer *bp;
		व्योम *area;
		chunk_t chunk;

		अगर (unlikely(prefetch_area < ps->current_area))
			prefetch_area = ps->current_area;

		अगर (DM_PREFETCH_CHUNKS) करो अणु
			chunk_t pf_chunk = area_location(ps, prefetch_area);
			अगर (unlikely(pf_chunk >= dm_bufio_get_device_size(client)))
				अवरोध;
			dm_bufio_prefetch(client, pf_chunk, 1);
			prefetch_area++;
			अगर (unlikely(!prefetch_area))
				अवरोध;
		पूर्ण जबतक (prefetch_area <= ps->current_area + DM_PREFETCH_CHUNKS);

		chunk = area_location(ps, ps->current_area);

		area = dm_bufio_पढ़ो(client, chunk, &bp);
		अगर (IS_ERR(area)) अणु
			r = PTR_ERR(area);
			जाओ ret_destroy_bufio;
		पूर्ण

		r = insert_exceptions(ps, area, callback, callback_context,
				      &full);

		अगर (!full)
			स_नकल(ps->area, area, ps->store->chunk_size << SECTOR_SHIFT);

		dm_bufio_release(bp);

		dm_bufio_क्रमget(client, chunk);

		अगर (unlikely(r))
			जाओ ret_destroy_bufio;
	पूर्ण

	ps->current_area--;

	skip_metadata(ps);

	r = 0;

ret_destroy_bufio:
	dm_bufio_client_destroy(client);

	वापस r;
पूर्ण

अटल काष्ठा pstore *get_info(काष्ठा dm_exception_store *store)
अणु
	वापस (काष्ठा pstore *) store->context;
पूर्ण

अटल व्योम persistent_usage(काष्ठा dm_exception_store *store,
			     sector_t *total_sectors,
			     sector_t *sectors_allocated,
			     sector_t *metadata_sectors)
अणु
	काष्ठा pstore *ps = get_info(store);

	*sectors_allocated = ps->next_मुक्त * store->chunk_size;
	*total_sectors = get_dev_size(dm_snap_cow(store->snap)->bdev);

	/*
	 * First chunk is the fixed header.
	 * Then there are (ps->current_area + 1) metadata chunks, each one
	 * separated from the next by ps->exceptions_per_area data chunks.
	 */
	*metadata_sectors = (ps->current_area + 1 + NUM_SNAPSHOT_HDR_CHUNKS) *
			    store->chunk_size;
पूर्ण

अटल व्योम persistent_dtr(काष्ठा dm_exception_store *store)
अणु
	काष्ठा pstore *ps = get_info(store);

	destroy_workqueue(ps->metadata_wq);

	/* Created in पढ़ो_header */
	अगर (ps->io_client)
		dm_io_client_destroy(ps->io_client);
	मुक्त_area(ps);

	/* Allocated in persistent_पढ़ो_metadata */
	kvमुक्त(ps->callbacks);

	kमुक्त(ps);
पूर्ण

अटल पूर्णांक persistent_पढ़ो_metadata(काष्ठा dm_exception_store *store,
				    पूर्णांक (*callback)(व्योम *callback_context,
						    chunk_t old, chunk_t new),
				    व्योम *callback_context)
अणु
	पूर्णांक r, new_snapshot;
	काष्ठा pstore *ps = get_info(store);

	/*
	 * Read the snapshot header.
	 */
	r = पढ़ो_header(ps, &new_snapshot);
	अगर (r)
		वापस r;

	/*
	 * Now we know correct chunk_size, complete the initialisation.
	 */
	ps->exceptions_per_area = (ps->store->chunk_size << SECTOR_SHIFT) /
				  माप(काष्ठा disk_exception);
	ps->callbacks = kvसुस्मृति(ps->exceptions_per_area,
				 माप(*ps->callbacks), GFP_KERNEL);
	अगर (!ps->callbacks)
		वापस -ENOMEM;

	/*
	 * Do we need to setup a new snapshot ?
	 */
	अगर (new_snapshot) अणु
		r = ग_लिखो_header(ps);
		अगर (r) अणु
			DMWARN("write_header failed");
			वापस r;
		पूर्ण

		ps->current_area = 0;
		zero_memory_area(ps);
		r = zero_disk_area(ps, 0);
		अगर (r)
			DMWARN("zero_disk_area(0) failed");
		वापस r;
	पूर्ण
	/*
	 * Sanity checks.
	 */
	अगर (ps->version != SNAPSHOT_DISK_VERSION) अणु
		DMWARN("unable to handle snapshot disk version %d",
		       ps->version);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Metadata are valid, but snapshot is invalidated
	 */
	अगर (!ps->valid)
		वापस 1;

	/*
	 * Read the metadata.
	 */
	r = पढ़ो_exceptions(ps, callback, callback_context);

	वापस r;
पूर्ण

अटल पूर्णांक persistent_prepare_exception(काष्ठा dm_exception_store *store,
					काष्ठा dm_exception *e)
अणु
	काष्ठा pstore *ps = get_info(store);
	sector_t size = get_dev_size(dm_snap_cow(store->snap)->bdev);

	/* Is there enough room ? */
	अगर (size < ((ps->next_मुक्त + 1) * store->chunk_size))
		वापस -ENOSPC;

	e->new_chunk = ps->next_मुक्त;

	/*
	 * Move onto the next मुक्त pending, making sure to take
	 * पूर्णांकo account the location of the metadata chunks.
	 */
	ps->next_मुक्त++;
	skip_metadata(ps);

	atomic_inc(&ps->pending_count);
	वापस 0;
पूर्ण

अटल व्योम persistent_commit_exception(काष्ठा dm_exception_store *store,
					काष्ठा dm_exception *e, पूर्णांक valid,
					व्योम (*callback) (व्योम *, पूर्णांक success),
					व्योम *callback_context)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pstore *ps = get_info(store);
	काष्ठा core_exception ce;
	काष्ठा commit_callback *cb;

	अगर (!valid)
		ps->valid = 0;

	ce.old_chunk = e->old_chunk;
	ce.new_chunk = e->new_chunk;
	ग_लिखो_exception(ps, ps->current_committed++, &ce);

	/*
	 * Add the callback to the back of the array.  This code
	 * is the only place where the callback array is
	 * manipulated, and we know that it will never be called
	 * multiple बार concurrently.
	 */
	cb = ps->callbacks + ps->callback_count++;
	cb->callback = callback;
	cb->context = callback_context;

	/*
	 * If there are exceptions in flight and we have not yet
	 * filled this metadata area there's nothing more to करो.
	 */
	अगर (!atomic_dec_and_test(&ps->pending_count) &&
	    (ps->current_committed != ps->exceptions_per_area))
		वापस;

	/*
	 * If we completely filled the current area, then wipe the next one.
	 */
	अगर ((ps->current_committed == ps->exceptions_per_area) &&
	    zero_disk_area(ps, ps->current_area + 1))
		ps->valid = 0;

	/*
	 * Commit exceptions to disk.
	 */
	अगर (ps->valid && area_io(ps, REQ_OP_WRITE,
				 REQ_PREFLUSH | REQ_FUA | REQ_SYNC))
		ps->valid = 0;

	/*
	 * Advance to the next area अगर this one is full.
	 */
	अगर (ps->current_committed == ps->exceptions_per_area) अणु
		ps->current_committed = 0;
		ps->current_area++;
		zero_memory_area(ps);
	पूर्ण

	क्रम (i = 0; i < ps->callback_count; i++) अणु
		cb = ps->callbacks + i;
		cb->callback(cb->context, ps->valid);
	पूर्ण

	ps->callback_count = 0;
पूर्ण

अटल पूर्णांक persistent_prepare_merge(काष्ठा dm_exception_store *store,
				    chunk_t *last_old_chunk,
				    chunk_t *last_new_chunk)
अणु
	काष्ठा pstore *ps = get_info(store);
	काष्ठा core_exception ce;
	पूर्णांक nr_consecutive;
	पूर्णांक r;

	/*
	 * When current area is empty, move back to preceding area.
	 */
	अगर (!ps->current_committed) अणु
		/*
		 * Have we finished?
		 */
		अगर (!ps->current_area)
			वापस 0;

		ps->current_area--;
		r = area_io(ps, REQ_OP_READ, 0);
		अगर (r < 0)
			वापस r;
		ps->current_committed = ps->exceptions_per_area;
	पूर्ण

	पढ़ो_exception(ps, ps->area, ps->current_committed - 1, &ce);
	*last_old_chunk = ce.old_chunk;
	*last_new_chunk = ce.new_chunk;

	/*
	 * Find number of consecutive chunks within the current area,
	 * working backwards.
	 */
	क्रम (nr_consecutive = 1; nr_consecutive < ps->current_committed;
	     nr_consecutive++) अणु
		पढ़ो_exception(ps, ps->area,
			       ps->current_committed - 1 - nr_consecutive, &ce);
		अगर (ce.old_chunk != *last_old_chunk - nr_consecutive ||
		    ce.new_chunk != *last_new_chunk - nr_consecutive)
			अवरोध;
	पूर्ण

	वापस nr_consecutive;
पूर्ण

अटल पूर्णांक persistent_commit_merge(काष्ठा dm_exception_store *store,
				   पूर्णांक nr_merged)
अणु
	पूर्णांक r, i;
	काष्ठा pstore *ps = get_info(store);

	BUG_ON(nr_merged > ps->current_committed);

	क्रम (i = 0; i < nr_merged; i++)
		clear_exception(ps, ps->current_committed - 1 - i);

	r = area_io(ps, REQ_OP_WRITE, REQ_PREFLUSH | REQ_FUA);
	अगर (r < 0)
		वापस r;

	ps->current_committed -= nr_merged;

	/*
	 * At this stage, only persistent_usage() uses ps->next_मुक्त, so
	 * we make no attempt to keep ps->next_मुक्त strictly accurate
	 * as exceptions may have been committed out-of-order originally.
	 * Once a snapshot has become merging, we set it to the value it
	 * would have held had all the exceptions been committed in order.
	 *
	 * ps->current_area करोes not get reduced by prepare_merge() until
	 * after commit_merge() has हटाओd the nr_merged previous exceptions.
	 */
	ps->next_मुक्त = area_location(ps, ps->current_area) +
			ps->current_committed + 1;

	वापस 0;
पूर्ण

अटल व्योम persistent_drop_snapshot(काष्ठा dm_exception_store *store)
अणु
	काष्ठा pstore *ps = get_info(store);

	ps->valid = 0;
	अगर (ग_लिखो_header(ps))
		DMWARN("write header failed");
पूर्ण

अटल पूर्णांक persistent_ctr(काष्ठा dm_exception_store *store, अक्षर *options)
अणु
	काष्ठा pstore *ps;
	पूर्णांक r;

	/* allocate the pstore */
	ps = kzalloc(माप(*ps), GFP_KERNEL);
	अगर (!ps)
		वापस -ENOMEM;

	ps->store = store;
	ps->valid = 1;
	ps->version = SNAPSHOT_DISK_VERSION;
	ps->area = शून्य;
	ps->zero_area = शून्य;
	ps->header_area = शून्य;
	ps->next_मुक्त = NUM_SNAPSHOT_HDR_CHUNKS + 1; /* header and 1st area */
	ps->current_committed = 0;

	ps->callback_count = 0;
	atomic_set(&ps->pending_count, 0);
	ps->callbacks = शून्य;

	ps->metadata_wq = alloc_workqueue("ksnaphd", WQ_MEM_RECLAIM, 0);
	अगर (!ps->metadata_wq) अणु
		DMERR("couldn't start header metadata update thread");
		r = -ENOMEM;
		जाओ err_workqueue;
	पूर्ण

	अगर (options) अणु
		अक्षर overflow = बड़े(options[0]);
		अगर (overflow == 'O')
			store->userspace_supports_overflow = true;
		अन्यथा अणु
			DMERR("Unsupported persistent store option: %s", options);
			r = -EINVAL;
			जाओ err_options;
		पूर्ण
	पूर्ण

	store->context = ps;

	वापस 0;

err_options:
	destroy_workqueue(ps->metadata_wq);
err_workqueue:
	kमुक्त(ps);

	वापस r;
पूर्ण

अटल अचिन्हित persistent_status(काष्ठा dm_exception_store *store,
				  status_type_t status, अक्षर *result,
				  अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;

	चयन (status) अणु
	हाल STATUSTYPE_INFO:
		अवरोध;
	हाल STATUSTYPE_TABLE:
		DMEMIT(" %s %llu", store->userspace_supports_overflow ? "PO" : "P",
		       (अचिन्हित दीर्घ दीर्घ)store->chunk_size);
	पूर्ण

	वापस sz;
पूर्ण

अटल काष्ठा dm_exception_store_type _persistent_type = अणु
	.name = "persistent",
	.module = THIS_MODULE,
	.ctr = persistent_ctr,
	.dtr = persistent_dtr,
	.पढ़ो_metadata = persistent_पढ़ो_metadata,
	.prepare_exception = persistent_prepare_exception,
	.commit_exception = persistent_commit_exception,
	.prepare_merge = persistent_prepare_merge,
	.commit_merge = persistent_commit_merge,
	.drop_snapshot = persistent_drop_snapshot,
	.usage = persistent_usage,
	.status = persistent_status,
पूर्ण;

अटल काष्ठा dm_exception_store_type _persistent_compat_type = अणु
	.name = "P",
	.module = THIS_MODULE,
	.ctr = persistent_ctr,
	.dtr = persistent_dtr,
	.पढ़ो_metadata = persistent_पढ़ो_metadata,
	.prepare_exception = persistent_prepare_exception,
	.commit_exception = persistent_commit_exception,
	.prepare_merge = persistent_prepare_merge,
	.commit_merge = persistent_commit_merge,
	.drop_snapshot = persistent_drop_snapshot,
	.usage = persistent_usage,
	.status = persistent_status,
पूर्ण;

पूर्णांक dm_persistent_snapshot_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_exception_store_type_रेजिस्टर(&_persistent_type);
	अगर (r) अणु
		DMERR("Unable to register persistent exception store type");
		वापस r;
	पूर्ण

	r = dm_exception_store_type_रेजिस्टर(&_persistent_compat_type);
	अगर (r) अणु
		DMERR("Unable to register old-style persistent exception "
		      "store type");
		dm_exception_store_type_unरेजिस्टर(&_persistent_type);
		वापस r;
	पूर्ण

	वापस r;
पूर्ण

व्योम dm_persistent_snapshot_निकास(व्योम)
अणु
	dm_exception_store_type_unरेजिस्टर(&_persistent_type);
	dm_exception_store_type_unरेजिस्टर(&_persistent_compat_type);
पूर्ण
