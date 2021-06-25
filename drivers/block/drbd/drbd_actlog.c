<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_actlog.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2003-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 2003-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2003-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#समावेश <linux/slab.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/drbd.h>
#समावेश <linux/drbd_सीमा.स>
#समावेश "drbd_int.h"


क्रमागत al_transaction_types अणु
	AL_TR_UPDATE = 0,
	AL_TR_INITIALIZED = 0xffff
पूर्ण;
/* all fields on disc in big endian */
काष्ठा __packed al_transaction_on_disk अणु
	/* करोn't we all like magic */
	__be32	magic;

	/* to identअगरy the most recent transaction block
	 * in the on disk ring buffer */
	__be32	tr_number;

	/* checksum on the full 4k block, with this field set to 0. */
	__be32	crc32c;

	/* type of transaction, special transaction types like:
	 * purge-all, set-all-idle, set-all-active, ... to-be-defined
	 * see also क्रमागत al_transaction_types */
	__be16	transaction_type;

	/* we currently allow only a few thousand extents,
	 * so 16bit will be enough क्रम the slot number. */

	/* how many updates in this transaction */
	__be16	n_updates;

	/* maximum slot number, "al-extents" in drbd.conf speak.
	 * Having this in each transaction should make reconfiguration
	 * of that parameter easier. */
	__be16	context_size;

	/* slot number the context starts with */
	__be16	context_start_slot_nr;

	/* Some reserved bytes.  Expected usage is a 64bit counter of
	 * sectors-written since device creation, and other data generation tag
	 * supporting usage */
	__be32	__reserved[4];

	/* --- 36 byte used --- */

	/* Reserve space क्रम up to AL_UPDATES_PER_TRANSACTION changes
	 * in one transaction, then use the reमुख्यing byte in the 4k block क्रम
	 * context inक्रमmation.  "Flexible" number of updates per transaction
	 * करोes not help, as we have to account क्रम the हाल when all update
	 * slots are used anyways, so it would only complicate code without
	 * additional benefit.
	 */
	__be16	update_slot_nr[AL_UPDATES_PER_TRANSACTION];

	/* but the extent number is 32bit, which at an extent size of 4 MiB
	 * allows to cover device sizes of up to 2**54 Byte (16 PiB) */
	__be32	update_extent_nr[AL_UPDATES_PER_TRANSACTION];

	/* --- 420 bytes used (36 + 64*6) --- */

	/* 4096 - 420 = 3676 = 919 * 4 */
	__be32	context[AL_CONTEXT_PER_TRANSACTION];
पूर्ण;

व्योम *drbd_md_get_buffer(काष्ठा drbd_device *device, स्थिर अक्षर *पूर्णांकent)
अणु
	पूर्णांक r;

	रुको_event(device->misc_रुको,
		   (r = atomic_cmpxchg(&device->md_io.in_use, 0, 1)) == 0 ||
		   device->state.disk <= D_FAILED);

	अगर (r)
		वापस शून्य;

	device->md_io.current_use = पूर्णांकent;
	device->md_io.start_jअगर = jअगरfies;
	device->md_io.submit_jअगर = device->md_io.start_jअगर - 1;
	वापस page_address(device->md_io.page);
पूर्ण

व्योम drbd_md_put_buffer(काष्ठा drbd_device *device)
अणु
	अगर (atomic_dec_and_test(&device->md_io.in_use))
		wake_up(&device->misc_रुको);
पूर्ण

व्योम रुको_until_करोne_or_क्रमce_detached(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev,
				     अचिन्हित पूर्णांक *करोne)
अणु
	दीर्घ dt;

	rcu_पढ़ो_lock();
	dt = rcu_dereference(bdev->disk_conf)->disk_समयout;
	rcu_पढ़ो_unlock();
	dt = dt * HZ / 10;
	अगर (dt == 0)
		dt = MAX_SCHEDULE_TIMEOUT;

	dt = रुको_event_समयout(device->misc_रुको,
			*करोne || test_bit(FORCE_DETACH, &device->flags), dt);
	अगर (dt == 0) अणु
		drbd_err(device, "meta-data IO operation timed out\n");
		drbd_chk_io_error(device, 1, DRBD_FORCE_DETACH);
	पूर्ण
पूर्ण

अटल पूर्णांक _drbd_md_sync_page_io(काष्ठा drbd_device *device,
				 काष्ठा drbd_backing_dev *bdev,
				 sector_t sector, पूर्णांक op)
अणु
	काष्ठा bio *bio;
	/* we करो all our meta data IO in aligned 4k blocks. */
	स्थिर पूर्णांक size = 4096;
	पूर्णांक err, op_flags = 0;

	device->md_io.करोne = 0;
	device->md_io.error = -ENODEV;

	अगर ((op == REQ_OP_WRITE) && !test_bit(MD_NO_FUA, &device->flags))
		op_flags |= REQ_FUA | REQ_PREFLUSH;
	op_flags |= REQ_SYNC;

	bio = bio_alloc_bioset(GFP_NOIO, 1, &drbd_md_io_bio_set);
	bio_set_dev(bio, bdev->md_bdev);
	bio->bi_iter.bi_sector = sector;
	err = -EIO;
	अगर (bio_add_page(bio, device->md_io.page, size, 0) != size)
		जाओ out;
	bio->bi_निजी = device;
	bio->bi_end_io = drbd_md_endio;
	bio_set_op_attrs(bio, op, op_flags);

	अगर (op != REQ_OP_WRITE && device->state.disk == D_DISKLESS && device->ldev == शून्य)
		/* special हाल, drbd_md_पढ़ो() during drbd_adm_attach(): no get_ldev */
		;
	अन्यथा अगर (!get_ldev_अगर_state(device, D_ATTACHING)) अणु
		/* Corresponding put_ldev in drbd_md_endio() */
		drbd_err(device, "ASSERT FAILED: get_ldev_if_state() == 1 in _drbd_md_sync_page_io()\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	bio_get(bio); /* one bio_put() is in the completion handler */
	atomic_inc(&device->md_io.in_use); /* drbd_md_put_buffer() is in the completion handler */
	device->md_io.submit_jअगर = jअगरfies;
	अगर (drbd_insert_fault(device, (op == REQ_OP_WRITE) ? DRBD_FAULT_MD_WR : DRBD_FAULT_MD_RD))
		bio_io_error(bio);
	अन्यथा
		submit_bio(bio);
	रुको_until_करोne_or_क्रमce_detached(device, bdev, &device->md_io.करोne);
	अगर (!bio->bi_status)
		err = device->md_io.error;

 out:
	bio_put(bio);
	वापस err;
पूर्ण

पूर्णांक drbd_md_sync_page_io(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev,
			 sector_t sector, पूर्णांक op)
अणु
	पूर्णांक err;
	D_ASSERT(device, atomic_पढ़ो(&device->md_io.in_use) == 1);

	BUG_ON(!bdev->md_bdev);

	dynamic_drbd_dbg(device, "meta_data io: %s [%d]:%s(,%llus,%s) %pS\n",
	     current->comm, current->pid, __func__,
	     (अचिन्हित दीर्घ दीर्घ)sector, (op == REQ_OP_WRITE) ? "WRITE" : "READ",
	     (व्योम*)_RET_IP_ );

	अगर (sector < drbd_md_first_sector(bdev) ||
	    sector + 7 > drbd_md_last_sector(bdev))
		drbd_alert(device, "%s [%d]:%s(,%llus,%s) out of range md access!\n",
		     current->comm, current->pid, __func__,
		     (अचिन्हित दीर्घ दीर्घ)sector,
		     (op == REQ_OP_WRITE) ? "WRITE" : "READ");

	err = _drbd_md_sync_page_io(device, bdev, sector, op);
	अगर (err) अणु
		drbd_err(device, "drbd_md_sync_page_io(,%llus,%s) failed with error %d\n",
		    (अचिन्हित दीर्घ दीर्घ)sector,
		    (op == REQ_OP_WRITE) ? "WRITE" : "READ", err);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा bm_extent *find_active_resync_extent(काष्ठा drbd_device *device, अचिन्हित पूर्णांक enr)
अणु
	काष्ठा lc_element *पंचांगp;
	पंचांगp = lc_find(device->resync, enr/AL_EXT_PER_BM_SECT);
	अगर (unlikely(पंचांगp != शून्य)) अणु
		काष्ठा bm_extent  *bm_ext = lc_entry(पंचांगp, काष्ठा bm_extent, lce);
		अगर (test_bit(BME_NO_WRITES, &bm_ext->flags))
			वापस bm_ext;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा lc_element *_al_get(काष्ठा drbd_device *device, अचिन्हित पूर्णांक enr, bool nonblock)
अणु
	काष्ठा lc_element *al_ext;
	काष्ठा bm_extent *bm_ext;
	पूर्णांक wake;

	spin_lock_irq(&device->al_lock);
	bm_ext = find_active_resync_extent(device, enr);
	अगर (bm_ext) अणु
		wake = !test_and_set_bit(BME_PRIORITY, &bm_ext->flags);
		spin_unlock_irq(&device->al_lock);
		अगर (wake)
			wake_up(&device->al_रुको);
		वापस शून्य;
	पूर्ण
	अगर (nonblock)
		al_ext = lc_try_get(device->act_log, enr);
	अन्यथा
		al_ext = lc_get(device->act_log, enr);
	spin_unlock_irq(&device->al_lock);
	वापस al_ext;
पूर्ण

bool drbd_al_begin_io_fastpath(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	/* क्रम bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	अचिन्हित first = i->sector >> (AL_EXTENT_SHIFT-9);
	अचिन्हित last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);

	D_ASSERT(device, first <= last);
	D_ASSERT(device, atomic_पढ़ो(&device->local_cnt) > 0);

	/* FIXME figure out a fast path क्रम bios crossing AL extent boundaries */
	अगर (first != last)
		वापस false;

	वापस _al_get(device, first, true);
पूर्ण

bool drbd_al_begin_io_prepare(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	/* क्रम bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	अचिन्हित first = i->sector >> (AL_EXTENT_SHIFT-9);
	अचिन्हित last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);
	अचिन्हित enr;
	bool need_transaction = false;

	D_ASSERT(device, first <= last);
	D_ASSERT(device, atomic_पढ़ो(&device->local_cnt) > 0);

	क्रम (enr = first; enr <= last; enr++) अणु
		काष्ठा lc_element *al_ext;
		रुको_event(device->al_रुको,
				(al_ext = _al_get(device, enr, false)) != शून्य);
		अगर (al_ext->lc_number != enr)
			need_transaction = true;
	पूर्ण
	वापस need_transaction;
पूर्ण

#अगर (PAGE_SHIFT + 3) < (AL_EXTENT_SHIFT - BM_BLOCK_SHIFT)
/* Currently BM_BLOCK_SHIFT, BM_EXT_SHIFT and AL_EXTENT_SHIFT
 * are still coupled, or assume too much about their relation.
 * Code below will not work अगर this is violated.
 * Will be cleaned up with some followup patch.
 */
# error FIXME
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक al_extent_to_bm_page(अचिन्हित पूर्णांक al_enr)
अणु
	वापस al_enr >>
		/* bit to page */
		((PAGE_SHIFT + 3) -
		/* al extent number to bit */
		 (AL_EXTENT_SHIFT - BM_BLOCK_SHIFT));
पूर्ण

अटल sector_t al_tr_number_to_on_disk_sector(काष्ठा drbd_device *device)
अणु
	स्थिर अचिन्हित पूर्णांक stripes = device->ldev->md.al_stripes;
	स्थिर अचिन्हित पूर्णांक stripe_size_4kB = device->ldev->md.al_stripe_size_4k;

	/* transaction number, modulo on-disk ring buffer wrap around */
	अचिन्हित पूर्णांक t = device->al_tr_number % (device->ldev->md.al_size_4k);

	/* ... to aligned 4k on disk block */
	t = ((t % stripes) * stripe_size_4kB) + t/stripes;

	/* ... to 512 byte sector in activity log */
	t *= 8;

	/* ... plus offset to the on disk position */
	वापस device->ldev->md.md_offset + device->ldev->md.al_offset + t;
पूर्ण

अटल पूर्णांक __al_ग_लिखो_transaction(काष्ठा drbd_device *device, काष्ठा al_transaction_on_disk *buffer)
अणु
	काष्ठा lc_element *e;
	sector_t sector;
	पूर्णांक i, mx;
	अचिन्हित extent_nr;
	अचिन्हित crc = 0;
	पूर्णांक err = 0;

	स_रखो(buffer, 0, माप(*buffer));
	buffer->magic = cpu_to_be32(DRBD_AL_MAGIC);
	buffer->tr_number = cpu_to_be32(device->al_tr_number);

	i = 0;

	drbd_bm_reset_al_hपूर्णांकs(device);

	/* Even though no one can start to change this list
	 * once we set the LC_LOCKED -- from drbd_al_begin_io(),
	 * lc_try_lock_क्रम_transaction() --, someone may still
	 * be in the process of changing it. */
	spin_lock_irq(&device->al_lock);
	list_क्रम_each_entry(e, &device->act_log->to_be_changed, list) अणु
		अगर (i == AL_UPDATES_PER_TRANSACTION) अणु
			i++;
			अवरोध;
		पूर्ण
		buffer->update_slot_nr[i] = cpu_to_be16(e->lc_index);
		buffer->update_extent_nr[i] = cpu_to_be32(e->lc_new_number);
		अगर (e->lc_number != LC_FREE)
			drbd_bm_mark_क्रम_ग_लिखोout(device,
					al_extent_to_bm_page(e->lc_number));
		i++;
	पूर्ण
	spin_unlock_irq(&device->al_lock);
	BUG_ON(i > AL_UPDATES_PER_TRANSACTION);

	buffer->n_updates = cpu_to_be16(i);
	क्रम ( ; i < AL_UPDATES_PER_TRANSACTION; i++) अणु
		buffer->update_slot_nr[i] = cpu_to_be16(-1);
		buffer->update_extent_nr[i] = cpu_to_be32(LC_FREE);
	पूर्ण

	buffer->context_size = cpu_to_be16(device->act_log->nr_elements);
	buffer->context_start_slot_nr = cpu_to_be16(device->al_tr_cycle);

	mx = min_t(पूर्णांक, AL_CONTEXT_PER_TRANSACTION,
		   device->act_log->nr_elements - device->al_tr_cycle);
	क्रम (i = 0; i < mx; i++) अणु
		अचिन्हित idx = device->al_tr_cycle + i;
		extent_nr = lc_element_by_index(device->act_log, idx)->lc_number;
		buffer->context[i] = cpu_to_be32(extent_nr);
	पूर्ण
	क्रम (; i < AL_CONTEXT_PER_TRANSACTION; i++)
		buffer->context[i] = cpu_to_be32(LC_FREE);

	device->al_tr_cycle += AL_CONTEXT_PER_TRANSACTION;
	अगर (device->al_tr_cycle >= device->act_log->nr_elements)
		device->al_tr_cycle = 0;

	sector = al_tr_number_to_on_disk_sector(device);

	crc = crc32c(0, buffer, 4096);
	buffer->crc32c = cpu_to_be32(crc);

	अगर (drbd_bm_ग_लिखो_hपूर्णांकed(device))
		err = -EIO;
	अन्यथा अणु
		bool ग_लिखो_al_updates;
		rcu_पढ़ो_lock();
		ग_लिखो_al_updates = rcu_dereference(device->ldev->disk_conf)->al_updates;
		rcu_पढ़ो_unlock();
		अगर (ग_लिखो_al_updates) अणु
			अगर (drbd_md_sync_page_io(device, device->ldev, sector, WRITE)) अणु
				err = -EIO;
				drbd_chk_io_error(device, 1, DRBD_META_IO_ERROR);
			पूर्ण अन्यथा अणु
				device->al_tr_number++;
				device->al_writ_cnt++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक al_ग_लिखो_transaction(काष्ठा drbd_device *device)
अणु
	काष्ठा al_transaction_on_disk *buffer;
	पूर्णांक err;

	अगर (!get_ldev(device)) अणु
		drbd_err(device, "disk is %s, cannot start al transaction\n",
			drbd_disk_str(device->state.disk));
		वापस -EIO;
	पूर्ण

	/* The biपंचांगap ग_लिखो may have failed, causing a state change. */
	अगर (device->state.disk < D_INCONSISTENT) अणु
		drbd_err(device,
			"disk is %s, cannot write al transaction\n",
			drbd_disk_str(device->state.disk));
		put_ldev(device);
		वापस -EIO;
	पूर्ण

	/* protects md_io_buffer, al_tr_cycle, ... */
	buffer = drbd_md_get_buffer(device, __func__);
	अगर (!buffer) अणु
		drbd_err(device, "disk failed while waiting for md_io buffer\n");
		put_ldev(device);
		वापस -ENODEV;
	पूर्ण

	err = __al_ग_लिखो_transaction(device, buffer);

	drbd_md_put_buffer(device);
	put_ldev(device);

	वापस err;
पूर्ण


व्योम drbd_al_begin_io_commit(काष्ठा drbd_device *device)
अणु
	bool locked = false;

	/* Serialize multiple transactions.
	 * This uses test_and_set_bit, memory barrier is implicit.
	 */
	रुको_event(device->al_रुको,
			device->act_log->pending_changes == 0 ||
			(locked = lc_try_lock_क्रम_transaction(device->act_log)));

	अगर (locked) अणु
		/* Double check: it may have been committed by someone अन्यथा,
		 * जबतक we have been रुकोing क्रम the lock. */
		अगर (device->act_log->pending_changes) अणु
			bool ग_लिखो_al_updates;

			rcu_पढ़ो_lock();
			ग_लिखो_al_updates = rcu_dereference(device->ldev->disk_conf)->al_updates;
			rcu_पढ़ो_unlock();

			अगर (ग_लिखो_al_updates)
				al_ग_लिखो_transaction(device);
			spin_lock_irq(&device->al_lock);
			/* FIXME
			अगर (err)
				we need an "lc_cancel" here;
			*/
			lc_committed(device->act_log);
			spin_unlock_irq(&device->al_lock);
		पूर्ण
		lc_unlock(device->act_log);
		wake_up(&device->al_रुको);
	पूर्ण
पूर्ण

/*
 * @delegate:   delegate activity log I/O to the worker thपढ़ो
 */
व्योम drbd_al_begin_io(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	अगर (drbd_al_begin_io_prepare(device, i))
		drbd_al_begin_io_commit(device);
पूर्ण

पूर्णांक drbd_al_begin_io_nonblock(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	काष्ठा lru_cache *al = device->act_log;
	/* क्रम bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	अचिन्हित first = i->sector >> (AL_EXTENT_SHIFT-9);
	अचिन्हित last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);
	अचिन्हित nr_al_extents;
	अचिन्हित available_update_slots;
	अचिन्हित enr;

	D_ASSERT(device, first <= last);

	nr_al_extents = 1 + last - first; /* worst हाल: all touched extends are cold. */
	available_update_slots = min(al->nr_elements - al->used,
				al->max_pending_changes - al->pending_changes);

	/* We want all necessary updates क्रम a given request within the same transaction
	 * We could first check how many updates are *actually* needed,
	 * and use that instead of the worst-हाल nr_al_extents */
	अगर (available_update_slots < nr_al_extents) अणु
		/* Too many activity log extents are currently "hot".
		 *
		 * If we have accumulated pending changes alपढ़ोy,
		 * we made progress.
		 *
		 * If we cannot get even a single pending change through,
		 * stop the fast path until we made some progress,
		 * or requests to "cold" extents could be starved. */
		अगर (!al->pending_changes)
			__set_bit(__LC_STARVING, &device->act_log->flags);
		वापस -ENOBUFS;
	पूर्ण

	/* Is resync active in this area? */
	क्रम (enr = first; enr <= last; enr++) अणु
		काष्ठा lc_element *पंचांगp;
		पंचांगp = lc_find(device->resync, enr/AL_EXT_PER_BM_SECT);
		अगर (unlikely(पंचांगp != शून्य)) अणु
			काष्ठा bm_extent  *bm_ext = lc_entry(पंचांगp, काष्ठा bm_extent, lce);
			अगर (test_bit(BME_NO_WRITES, &bm_ext->flags)) अणु
				अगर (!test_and_set_bit(BME_PRIORITY, &bm_ext->flags))
					वापस -EBUSY;
				वापस -EWOULDBLOCK;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Checkout the refcounts.
	 * Given that we checked क्रम available elements and update slots above,
	 * this has to be successful. */
	क्रम (enr = first; enr <= last; enr++) अणु
		काष्ठा lc_element *al_ext;
		al_ext = lc_get_cumulative(device->act_log, enr);
		अगर (!al_ext)
			drbd_info(device, "LOGIC BUG for enr=%u\n", enr);
	पूर्ण
	वापस 0;
पूर्ण

व्योम drbd_al_complete_io(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	/* क्रम bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	अचिन्हित first = i->sector >> (AL_EXTENT_SHIFT-9);
	अचिन्हित last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);
	अचिन्हित enr;
	काष्ठा lc_element *extent;
	अचिन्हित दीर्घ flags;

	D_ASSERT(device, first <= last);
	spin_lock_irqsave(&device->al_lock, flags);

	क्रम (enr = first; enr <= last; enr++) अणु
		extent = lc_find(device->act_log, enr);
		अगर (!extent) अणु
			drbd_err(device, "al_complete_io() called on inactive extent %u\n", enr);
			जारी;
		पूर्ण
		lc_put(device->act_log, extent);
	पूर्ण
	spin_unlock_irqrestore(&device->al_lock, flags);
	wake_up(&device->al_रुको);
पूर्ण

अटल पूर्णांक _try_lc_del(काष्ठा drbd_device *device, काष्ठा lc_element *al_ext)
अणु
	पूर्णांक rv;

	spin_lock_irq(&device->al_lock);
	rv = (al_ext->refcnt == 0);
	अगर (likely(rv))
		lc_del(device->act_log, al_ext);
	spin_unlock_irq(&device->al_lock);

	वापस rv;
पूर्ण

/**
 * drbd_al_shrink() - Removes all active extents क्रमm the activity log
 * @device:	DRBD device.
 *
 * Removes all active extents क्रमm the activity log, रुकोing until
 * the reference count of each entry dropped to 0 first, of course.
 *
 * You need to lock device->act_log with lc_try_lock() / lc_unlock()
 */
व्योम drbd_al_shrink(काष्ठा drbd_device *device)
अणु
	काष्ठा lc_element *al_ext;
	पूर्णांक i;

	D_ASSERT(device, test_bit(__LC_LOCKED, &device->act_log->flags));

	क्रम (i = 0; i < device->act_log->nr_elements; i++) अणु
		al_ext = lc_element_by_index(device->act_log, i);
		अगर (al_ext->lc_number == LC_FREE)
			जारी;
		रुको_event(device->al_रुको, _try_lc_del(device, al_ext));
	पूर्ण

	wake_up(&device->al_रुको);
पूर्ण

पूर्णांक drbd_al_initialize(काष्ठा drbd_device *device, व्योम *buffer)
अणु
	काष्ठा al_transaction_on_disk *al = buffer;
	काष्ठा drbd_md *md = &device->ldev->md;
	पूर्णांक al_size_4k = md->al_stripes * md->al_stripe_size_4k;
	पूर्णांक i;

	__al_ग_लिखो_transaction(device, al);
	/* There may or may not have been a pending transaction. */
	spin_lock_irq(&device->al_lock);
	lc_committed(device->act_log);
	spin_unlock_irq(&device->al_lock);

	/* The rest of the transactions will have an empty "updates" list, and
	 * are written out only to provide the context, and to initialize the
	 * on-disk ring buffer. */
	क्रम (i = 1; i < al_size_4k; i++) अणु
		पूर्णांक err = __al_ग_लिखो_transaction(device, al);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *drbd_change_sync_fname[] = अणु
	[RECORD_RS_FAILED] = "drbd_rs_failed_io",
	[SET_IN_SYNC] = "drbd_set_in_sync",
	[SET_OUT_OF_SYNC] = "drbd_set_out_of_sync"
पूर्ण;

/* ATTENTION. The AL's extents are 4MB each, जबतक the extents in the
 * resync LRU-cache are 16MB each.
 * The caller of this function has to hold an get_ldev() reference.
 *
 * Adjusts the caching members ->rs_left (success) or ->rs_failed (!success),
 * potentially pulling in (and recounting the corresponding bits)
 * this resync extent पूर्णांकo the resync extent lru cache.
 *
 * Returns whether all bits have been cleared क्रम this resync extent,
 * precisely: (rs_left <= rs_failed)
 *
 * TODO will be obsoleted once we have a caching lru of the on disk biपंचांगap
 */
अटल bool update_rs_extent(काष्ठा drbd_device *device,
		अचिन्हित पूर्णांक enr, पूर्णांक count,
		क्रमागत update_sync_bits_mode mode)
अणु
	काष्ठा lc_element *e;

	D_ASSERT(device, atomic_पढ़ो(&device->local_cnt));

	/* When setting out-of-sync bits,
	 * we करोn't need it cached (lc_find).
	 * But अगर it is present in the cache,
	 * we should update the cached bit count.
	 * Otherwise, that extent should be in the resync extent lru cache
	 * alपढ़ोy -- or we want to pull it in अगर necessary -- (lc_get),
	 * then update and check rs_left and rs_failed. */
	अगर (mode == SET_OUT_OF_SYNC)
		e = lc_find(device->resync, enr);
	अन्यथा
		e = lc_get(device->resync, enr);
	अगर (e) अणु
		काष्ठा bm_extent *ext = lc_entry(e, काष्ठा bm_extent, lce);
		अगर (ext->lce.lc_number == enr) अणु
			अगर (mode == SET_IN_SYNC)
				ext->rs_left -= count;
			अन्यथा अगर (mode == SET_OUT_OF_SYNC)
				ext->rs_left += count;
			अन्यथा
				ext->rs_failed += count;
			अगर (ext->rs_left < ext->rs_failed) अणु
				drbd_warn(device, "BAD! enr=%u rs_left=%d "
				    "rs_failed=%d count=%d cstate=%s\n",
				     ext->lce.lc_number, ext->rs_left,
				     ext->rs_failed, count,
				     drbd_conn_str(device->state.conn));

				/* We करोn't expect to be able to clear more bits
				 * than have been set when we originally counted
				 * the set bits to cache that value in ext->rs_left.
				 * Whatever the reason (disconnect during resync,
				 * delayed local completion of an application ग_लिखो),
				 * try to fix it up by recounting here. */
				ext->rs_left = drbd_bm_e_weight(device, enr);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Normally this element should be in the cache,
			 * since drbd_rs_begin_io() pulled it alपढ़ोy in.
			 *
			 * But maybe an application ग_लिखो finished, and we set
			 * something outside the resync lru_cache in sync.
			 */
			पूर्णांक rs_left = drbd_bm_e_weight(device, enr);
			अगर (ext->flags != 0) अणु
				drbd_warn(device, "changing resync lce: %d[%u;%02lx]"
				     " -> %d[%u;00]\n",
				     ext->lce.lc_number, ext->rs_left,
				     ext->flags, enr, rs_left);
				ext->flags = 0;
			पूर्ण
			अगर (ext->rs_failed) अणु
				drbd_warn(device, "Kicking resync_lru element enr=%u "
				     "out with rs_failed=%d\n",
				     ext->lce.lc_number, ext->rs_failed);
			पूर्ण
			ext->rs_left = rs_left;
			ext->rs_failed = (mode == RECORD_RS_FAILED) ? count : 0;
			/* we करोn't keep a persistent log of the resync lru,
			 * we can commit any change right away. */
			lc_committed(device->resync);
		पूर्ण
		अगर (mode != SET_OUT_OF_SYNC)
			lc_put(device->resync, &ext->lce);
		/* no race, we are within the al_lock! */

		अगर (ext->rs_left <= ext->rs_failed) अणु
			ext->rs_failed = 0;
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अगर (mode != SET_OUT_OF_SYNC) अणु
		/* be quiet अगर lc_find() did not find it. */
		drbd_err(device, "lc_get() failed! locked=%d/%d flags=%lu\n",
		    device->resync_locked,
		    device->resync->nr_elements,
		    device->resync->flags);
	पूर्ण
	वापस false;
पूर्ण

व्योम drbd_advance_rs_marks(काष्ठा drbd_device *device, अचिन्हित दीर्घ still_to_go)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ last = device->rs_mark_समय[device->rs_last_mark];
	पूर्णांक next = (device->rs_last_mark + 1) % DRBD_SYNC_MARKS;
	अगर (समय_after_eq(now, last + DRBD_SYNC_MARK_STEP)) अणु
		अगर (device->rs_mark_left[device->rs_last_mark] != still_to_go &&
		    device->state.conn != C_PAUSED_SYNC_T &&
		    device->state.conn != C_PAUSED_SYNC_S) अणु
			device->rs_mark_समय[next] = now;
			device->rs_mark_left[next] = still_to_go;
			device->rs_last_mark = next;
		पूर्ण
	पूर्ण
पूर्ण

/* It is called lazy update, so करोn't करो ग_लिखो-out too often. */
अटल bool lazy_biपंचांगap_update_due(काष्ठा drbd_device *device)
अणु
	वापस समय_after(jअगरfies, device->rs_last_bcast + 2*HZ);
पूर्ण

अटल व्योम maybe_schedule_on_disk_biपंचांगap_update(काष्ठा drbd_device *device, bool rs_करोne)
अणु
	अगर (rs_करोne) अणु
		काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
		अगर (connection->agreed_pro_version <= 95 ||
		    is_sync_target_state(device->state.conn))
			set_bit(RS_DONE, &device->flags);
			/* and also set RS_PROGRESS below */

		/* Else: rather रुको क्रम explicit notअगरication via receive_state,
		 * to aव्योम uuids-rotated-too-fast causing full resync
		 * in next handshake, in हाल the replication link अवरोधs
		 * at the most unक्रमtunate समय... */
	पूर्ण अन्यथा अगर (!lazy_biपंचांगap_update_due(device))
		वापस;

	drbd_device_post_work(device, RS_PROGRESS);
पूर्ण

अटल पूर्णांक update_sync_bits(काष्ठा drbd_device *device,
		अचिन्हित दीर्घ sbnr, अचिन्हित दीर्घ ebnr,
		क्रमागत update_sync_bits_mode mode)
अणु
	/*
	 * We keep a count of set bits per resync-extent in the ->rs_left
	 * caching member, so we need to loop and work within the resync extent
	 * alignment. Typically this loop will execute exactly once.
	 */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ count = 0;
	अचिन्हित पूर्णांक cleared = 0;
	जबतक (sbnr <= ebnr) अणु
		/* set temporary boundary bit number to last bit number within
		 * the resync extent of the current start bit number,
		 * but cap at provided end bit number */
		अचिन्हित दीर्घ tbnr = min(ebnr, sbnr | BM_BLOCKS_PER_BM_EXT_MASK);
		अचिन्हित दीर्घ c;

		अगर (mode == RECORD_RS_FAILED)
			/* Only called from drbd_rs_failed_io(), bits
			 * supposedly still set.  Recount, maybe some
			 * of the bits have been successfully cleared
			 * by application IO meanजबतक.
			 */
			c = drbd_bm_count_bits(device, sbnr, tbnr);
		अन्यथा अगर (mode == SET_IN_SYNC)
			c = drbd_bm_clear_bits(device, sbnr, tbnr);
		अन्यथा /* अगर (mode == SET_OUT_OF_SYNC) */
			c = drbd_bm_set_bits(device, sbnr, tbnr);

		अगर (c) अणु
			spin_lock_irqsave(&device->al_lock, flags);
			cleared += update_rs_extent(device, BM_BIT_TO_EXT(sbnr), c, mode);
			spin_unlock_irqrestore(&device->al_lock, flags);
			count += c;
		पूर्ण
		sbnr = tbnr + 1;
	पूर्ण
	अगर (count) अणु
		अगर (mode == SET_IN_SYNC) अणु
			अचिन्हित दीर्घ still_to_go = drbd_bm_total_weight(device);
			bool rs_is_करोne = (still_to_go <= device->rs_failed);
			drbd_advance_rs_marks(device, still_to_go);
			अगर (cleared || rs_is_करोne)
				maybe_schedule_on_disk_biपंचांगap_update(device, rs_is_करोne);
		पूर्ण अन्यथा अगर (mode == RECORD_RS_FAILED)
			device->rs_failed += count;
		wake_up(&device->al_रुको);
	पूर्ण
	वापस count;
पूर्ण

अटल bool plausible_request_size(पूर्णांक size)
अणु
	वापस size > 0
		&& size <= DRBD_MAX_BATCH_BIO_SIZE
		&& IS_ALIGNED(size, 512);
पूर्ण

/* clear the bit corresponding to the piece of storage in question:
 * size byte of data starting from sector.  Only clear a bits of the affected
 * one ore more _aligned_ BM_BLOCK_SIZE blocks.
 *
 * called by worker on C_SYNC_TARGET and receiver on SyncSource.
 *
 */
पूर्णांक __drbd_change_sync(काष्ठा drbd_device *device, sector_t sector, पूर्णांक size,
		क्रमागत update_sync_bits_mode mode)
अणु
	/* Is called from worker and receiver context _only_ */
	अचिन्हित दीर्घ sbnr, ebnr, lbnr;
	अचिन्हित दीर्घ count = 0;
	sector_t esector, nr_sectors;

	/* This would be an empty REQ_PREFLUSH, be silent. */
	अगर ((mode == SET_OUT_OF_SYNC) && size == 0)
		वापस 0;

	अगर (!plausible_request_size(size)) अणु
		drbd_err(device, "%s: sector=%llus size=%d nonsense!\n",
				drbd_change_sync_fname[mode],
				(अचिन्हित दीर्घ दीर्घ)sector, size);
		वापस 0;
	पूर्ण

	अगर (!get_ldev(device))
		वापस 0; /* no disk, no metadata, no biपंचांगap to manipulate bits in */

	nr_sectors = get_capacity(device->vdisk);
	esector = sector + (size >> 9) - 1;

	अगर (!expect(sector < nr_sectors))
		जाओ out;
	अगर (!expect(esector < nr_sectors))
		esector = nr_sectors - 1;

	lbnr = BM_SECT_TO_BIT(nr_sectors-1);

	अगर (mode == SET_IN_SYNC) अणु
		/* Round up start sector, round करोwn end sector.  We make sure
		 * we only clear full, aligned, BM_BLOCK_SIZE blocks. */
		अगर (unlikely(esector < BM_SECT_PER_BIT-1))
			जाओ out;
		अगर (unlikely(esector == (nr_sectors-1)))
			ebnr = lbnr;
		अन्यथा
			ebnr = BM_SECT_TO_BIT(esector - (BM_SECT_PER_BIT-1));
		sbnr = BM_SECT_TO_BIT(sector + BM_SECT_PER_BIT-1);
	पूर्ण अन्यथा अणु
		/* We set it out of sync, or record resync failure.
		 * Should not round anything here. */
		sbnr = BM_SECT_TO_BIT(sector);
		ebnr = BM_SECT_TO_BIT(esector);
	पूर्ण

	count = update_sync_bits(device, sbnr, ebnr, mode);
out:
	put_ldev(device);
	वापस count;
पूर्ण

अटल
काष्ठा bm_extent *_bme_get(काष्ठा drbd_device *device, अचिन्हित पूर्णांक enr)
अणु
	काष्ठा lc_element *e;
	काष्ठा bm_extent *bm_ext;
	पूर्णांक wakeup = 0;
	अचिन्हित दीर्घ rs_flags;

	spin_lock_irq(&device->al_lock);
	अगर (device->resync_locked > device->resync->nr_elements/2) अणु
		spin_unlock_irq(&device->al_lock);
		वापस शून्य;
	पूर्ण
	e = lc_get(device->resync, enr);
	bm_ext = e ? lc_entry(e, काष्ठा bm_extent, lce) : शून्य;
	अगर (bm_ext) अणु
		अगर (bm_ext->lce.lc_number != enr) अणु
			bm_ext->rs_left = drbd_bm_e_weight(device, enr);
			bm_ext->rs_failed = 0;
			lc_committed(device->resync);
			wakeup = 1;
		पूर्ण
		अगर (bm_ext->lce.refcnt == 1)
			device->resync_locked++;
		set_bit(BME_NO_WRITES, &bm_ext->flags);
	पूर्ण
	rs_flags = device->resync->flags;
	spin_unlock_irq(&device->al_lock);
	अगर (wakeup)
		wake_up(&device->al_रुको);

	अगर (!bm_ext) अणु
		अगर (rs_flags & LC_STARVING)
			drbd_warn(device, "Have to wait for element"
			     " (resync LRU too small?)\n");
		BUG_ON(rs_flags & LC_LOCKED);
	पूर्ण

	वापस bm_ext;
पूर्ण

अटल पूर्णांक _is_in_al(काष्ठा drbd_device *device, अचिन्हित पूर्णांक enr)
अणु
	पूर्णांक rv;

	spin_lock_irq(&device->al_lock);
	rv = lc_is_used(device->act_log, enr);
	spin_unlock_irq(&device->al_lock);

	वापस rv;
पूर्ण

/**
 * drbd_rs_begin_io() - Gets an extent in the resync LRU cache and sets it to BME_LOCKED
 * @device:	DRBD device.
 * @sector:	The sector number.
 *
 * This functions sleeps on al_रुको. Returns 0 on success, -EINTR अगर पूर्णांकerrupted.
 */
पूर्णांक drbd_rs_begin_io(काष्ठा drbd_device *device, sector_t sector)
अणु
	अचिन्हित पूर्णांक enr = BM_SECT_TO_EXT(sector);
	काष्ठा bm_extent *bm_ext;
	पूर्णांक i, sig;
	bool sa;

retry:
	sig = रुको_event_पूर्णांकerruptible(device->al_रुको,
			(bm_ext = _bme_get(device, enr)));
	अगर (sig)
		वापस -EINTR;

	अगर (test_bit(BME_LOCKED, &bm_ext->flags))
		वापस 0;

	/* step aside only जबतक we are above c-min-rate; unless disabled. */
	sa = drbd_rs_c_min_rate_throttle(device);

	क्रम (i = 0; i < AL_EXT_PER_BM_SECT; i++) अणु
		sig = रुको_event_पूर्णांकerruptible(device->al_रुको,
					       !_is_in_al(device, enr * AL_EXT_PER_BM_SECT + i) ||
					       (sa && test_bit(BME_PRIORITY, &bm_ext->flags)));

		अगर (sig || (sa && test_bit(BME_PRIORITY, &bm_ext->flags))) अणु
			spin_lock_irq(&device->al_lock);
			अगर (lc_put(device->resync, &bm_ext->lce) == 0) अणु
				bm_ext->flags = 0; /* clears BME_NO_WRITES and eventually BME_PRIORITY */
				device->resync_locked--;
				wake_up(&device->al_रुको);
			पूर्ण
			spin_unlock_irq(&device->al_lock);
			अगर (sig)
				वापस -EINTR;
			अगर (schedule_समयout_पूर्णांकerruptible(HZ/10))
				वापस -EINTR;
			जाओ retry;
		पूर्ण
	पूर्ण
	set_bit(BME_LOCKED, &bm_ext->flags);
	वापस 0;
पूर्ण

/**
 * drbd_try_rs_begin_io() - Gets an extent in the resync LRU cache, करोes not sleep
 * @device:	DRBD device.
 * @sector:	The sector number.
 *
 * Gets an extent in the resync LRU cache, sets it to BME_NO_WRITES, then
 * tries to set it to BME_LOCKED. Returns 0 upon success, and -EAGAIN
 * अगर there is still application IO going on in this area.
 */
पूर्णांक drbd_try_rs_begin_io(काष्ठा drbd_device *device, sector_t sector)
अणु
	अचिन्हित पूर्णांक enr = BM_SECT_TO_EXT(sector);
	स्थिर अचिन्हित पूर्णांक al_enr = enr*AL_EXT_PER_BM_SECT;
	काष्ठा lc_element *e;
	काष्ठा bm_extent *bm_ext;
	पूर्णांक i;
	bool throttle = drbd_rs_should_slow_करोwn(device, sector, true);

	/* If we need to throttle, a half-locked (only marked BME_NO_WRITES,
	 * not yet BME_LOCKED) extent needs to be kicked out explicitly अगर we
	 * need to throttle. There is at most one such half-locked extent,
	 * which is remembered in resync_wenr. */

	अगर (throttle && device->resync_wenr != enr)
		वापस -EAGAIN;

	spin_lock_irq(&device->al_lock);
	अगर (device->resync_wenr != LC_FREE && device->resync_wenr != enr) अणु
		/* in हाल you have very heavy scattered io, it may
		 * stall the syncer undefined अगर we give up the ref count
		 * when we try again and requeue.
		 *
		 * अगर we करोn't give up the refcount, but the next समय
		 * we are scheduled this extent has been "synced" by new
		 * application ग_लिखोs, we'd miss the lc_put on the
		 * extent we keep the refcount on.
		 * so we remembered which extent we had to try again, and
		 * अगर the next requested one is something अन्यथा, we करो
		 * the lc_put here...
		 * we also have to wake_up
		 */
		e = lc_find(device->resync, device->resync_wenr);
		bm_ext = e ? lc_entry(e, काष्ठा bm_extent, lce) : शून्य;
		अगर (bm_ext) अणु
			D_ASSERT(device, !test_bit(BME_LOCKED, &bm_ext->flags));
			D_ASSERT(device, test_bit(BME_NO_WRITES, &bm_ext->flags));
			clear_bit(BME_NO_WRITES, &bm_ext->flags);
			device->resync_wenr = LC_FREE;
			अगर (lc_put(device->resync, &bm_ext->lce) == 0) अणु
				bm_ext->flags = 0;
				device->resync_locked--;
			पूर्ण
			wake_up(&device->al_रुको);
		पूर्ण अन्यथा अणु
			drbd_alert(device, "LOGIC BUG\n");
		पूर्ण
	पूर्ण
	/* TRY. */
	e = lc_try_get(device->resync, enr);
	bm_ext = e ? lc_entry(e, काष्ठा bm_extent, lce) : शून्य;
	अगर (bm_ext) अणु
		अगर (test_bit(BME_LOCKED, &bm_ext->flags))
			जाओ proceed;
		अगर (!test_and_set_bit(BME_NO_WRITES, &bm_ext->flags)) अणु
			device->resync_locked++;
		पूर्ण अन्यथा अणु
			/* we did set the BME_NO_WRITES,
			 * but then could not set BME_LOCKED,
			 * so we tried again.
			 * drop the extra reference. */
			bm_ext->lce.refcnt--;
			D_ASSERT(device, bm_ext->lce.refcnt > 0);
		पूर्ण
		जाओ check_al;
	पूर्ण अन्यथा अणु
		/* करो we rather want to try later? */
		अगर (device->resync_locked > device->resync->nr_elements-3)
			जाओ try_again;
		/* Do or करो not. There is no try. -- Yoda */
		e = lc_get(device->resync, enr);
		bm_ext = e ? lc_entry(e, काष्ठा bm_extent, lce) : शून्य;
		अगर (!bm_ext) अणु
			स्थिर अचिन्हित दीर्घ rs_flags = device->resync->flags;
			अगर (rs_flags & LC_STARVING)
				drbd_warn(device, "Have to wait for element"
				     " (resync LRU too small?)\n");
			BUG_ON(rs_flags & LC_LOCKED);
			जाओ try_again;
		पूर्ण
		अगर (bm_ext->lce.lc_number != enr) अणु
			bm_ext->rs_left = drbd_bm_e_weight(device, enr);
			bm_ext->rs_failed = 0;
			lc_committed(device->resync);
			wake_up(&device->al_रुको);
			D_ASSERT(device, test_bit(BME_LOCKED, &bm_ext->flags) == 0);
		पूर्ण
		set_bit(BME_NO_WRITES, &bm_ext->flags);
		D_ASSERT(device, bm_ext->lce.refcnt == 1);
		device->resync_locked++;
		जाओ check_al;
	पूर्ण
check_al:
	क्रम (i = 0; i < AL_EXT_PER_BM_SECT; i++) अणु
		अगर (lc_is_used(device->act_log, al_enr+i))
			जाओ try_again;
	पूर्ण
	set_bit(BME_LOCKED, &bm_ext->flags);
proceed:
	device->resync_wenr = LC_FREE;
	spin_unlock_irq(&device->al_lock);
	वापस 0;

try_again:
	अगर (bm_ext) अणु
		अगर (throttle) अणु
			D_ASSERT(device, !test_bit(BME_LOCKED, &bm_ext->flags));
			D_ASSERT(device, test_bit(BME_NO_WRITES, &bm_ext->flags));
			clear_bit(BME_NO_WRITES, &bm_ext->flags);
			device->resync_wenr = LC_FREE;
			अगर (lc_put(device->resync, &bm_ext->lce) == 0) अणु
				bm_ext->flags = 0;
				device->resync_locked--;
			पूर्ण
			wake_up(&device->al_रुको);
		पूर्ण अन्यथा
			device->resync_wenr = enr;
	पूर्ण
	spin_unlock_irq(&device->al_lock);
	वापस -EAGAIN;
पूर्ण

व्योम drbd_rs_complete_io(काष्ठा drbd_device *device, sector_t sector)
अणु
	अचिन्हित पूर्णांक enr = BM_SECT_TO_EXT(sector);
	काष्ठा lc_element *e;
	काष्ठा bm_extent *bm_ext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&device->al_lock, flags);
	e = lc_find(device->resync, enr);
	bm_ext = e ? lc_entry(e, काष्ठा bm_extent, lce) : शून्य;
	अगर (!bm_ext) अणु
		spin_unlock_irqrestore(&device->al_lock, flags);
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "drbd_rs_complete_io() called, but extent not found\n");
		वापस;
	पूर्ण

	अगर (bm_ext->lce.refcnt == 0) अणु
		spin_unlock_irqrestore(&device->al_lock, flags);
		drbd_err(device, "drbd_rs_complete_io(,%llu [=%u]) called, "
		    "but refcnt is 0!?\n",
		    (अचिन्हित दीर्घ दीर्घ)sector, enr);
		वापस;
	पूर्ण

	अगर (lc_put(device->resync, &bm_ext->lce) == 0) अणु
		bm_ext->flags = 0; /* clear BME_LOCKED, BME_NO_WRITES and BME_PRIORITY */
		device->resync_locked--;
		wake_up(&device->al_रुको);
	पूर्ण

	spin_unlock_irqrestore(&device->al_lock, flags);
पूर्ण

/**
 * drbd_rs_cancel_all() - Removes all extents from the resync LRU (even BME_LOCKED)
 * @device:	DRBD device.
 */
व्योम drbd_rs_cancel_all(काष्ठा drbd_device *device)
अणु
	spin_lock_irq(&device->al_lock);

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु /* Makes sure ->resync is there. */
		lc_reset(device->resync);
		put_ldev(device);
	पूर्ण
	device->resync_locked = 0;
	device->resync_wenr = LC_FREE;
	spin_unlock_irq(&device->al_lock);
	wake_up(&device->al_रुको);
पूर्ण

/**
 * drbd_rs_del_all() - Gracefully हटाओ all extents from the resync LRU
 * @device:	DRBD device.
 *
 * Returns 0 upon success, -EAGAIN अगर at least one reference count was
 * not zero.
 */
पूर्णांक drbd_rs_del_all(काष्ठा drbd_device *device)
अणु
	काष्ठा lc_element *e;
	काष्ठा bm_extent *bm_ext;
	पूर्णांक i;

	spin_lock_irq(&device->al_lock);

	अगर (get_ldev_अगर_state(device, D_FAILED)) अणु
		/* ok, ->resync is there. */
		क्रम (i = 0; i < device->resync->nr_elements; i++) अणु
			e = lc_element_by_index(device->resync, i);
			bm_ext = lc_entry(e, काष्ठा bm_extent, lce);
			अगर (bm_ext->lce.lc_number == LC_FREE)
				जारी;
			अगर (bm_ext->lce.lc_number == device->resync_wenr) अणु
				drbd_info(device, "dropping %u in drbd_rs_del_all, apparently"
				     " got 'synced' by application io\n",
				     device->resync_wenr);
				D_ASSERT(device, !test_bit(BME_LOCKED, &bm_ext->flags));
				D_ASSERT(device, test_bit(BME_NO_WRITES, &bm_ext->flags));
				clear_bit(BME_NO_WRITES, &bm_ext->flags);
				device->resync_wenr = LC_FREE;
				lc_put(device->resync, &bm_ext->lce);
			पूर्ण
			अगर (bm_ext->lce.refcnt != 0) अणु
				drbd_info(device, "Retrying drbd_rs_del_all() later. "
				     "refcnt=%d\n", bm_ext->lce.refcnt);
				put_ldev(device);
				spin_unlock_irq(&device->al_lock);
				वापस -EAGAIN;
			पूर्ण
			D_ASSERT(device, !test_bit(BME_LOCKED, &bm_ext->flags));
			D_ASSERT(device, !test_bit(BME_NO_WRITES, &bm_ext->flags));
			lc_del(device->resync, &bm_ext->lce);
		पूर्ण
		D_ASSERT(device, device->resync->used == 0);
		put_ldev(device);
	पूर्ण
	spin_unlock_irq(&device->al_lock);
	wake_up(&device->al_रुको);

	वापस 0;
पूर्ण
