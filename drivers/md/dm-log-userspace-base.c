<शैली गुरु>
/*
 * Copyright (C) 2006-2009 Red Hat, Inc.
 *
 * This file is released under the LGPL.
 */

#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/dm-dirty-log.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-log-userspace.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>

#समावेश "dm-log-userspace-transfer.h"

#घोषणा DM_LOG_USERSPACE_VSN "1.3.0"

#घोषणा FLUSH_ENTRY_POOL_SIZE 16

काष्ठा dm_dirty_log_flush_entry अणु
	पूर्णांक type;
	region_t region;
	काष्ठा list_head list;
पूर्ण;

/*
 * This limit on the number of mark and clear request is, to a degree,
 * arbitrary.  However, there is some basis क्रम the choice in the limits
 * imposed on the size of data payload by dm-log-userspace-transfer.c:
 * dm_consult_userspace().
 */
#घोषणा MAX_FLUSH_GROUP_COUNT 32

काष्ठा log_c अणु
	काष्ठा dm_target *ti;
	काष्ठा dm_dev *log_dev;

	अक्षर *usr_argv_str;
	uपूर्णांक32_t usr_argc;

	uपूर्णांक32_t region_size;
	region_t region_count;
	uपूर्णांक64_t luid;
	अक्षर uuid[DM_UUID_LEN];

	/*
	 * Mark and clear requests are held until a flush is issued
	 * so that we can group, and thereby limit, the amount of
	 * network traffic between kernel and userspace.  The 'flush_lock'
	 * is used to protect these lists.
	 */
	spinlock_t flush_lock;
	काष्ठा list_head mark_list;
	काष्ठा list_head clear_list;

	/*
	 * in_sync_hपूर्णांक माला_लो set when करोing is_remote_recovering.  It
	 * represents the first region that needs recovery.  IOW, the
	 * first zero bit of sync_bits.  This can be useful क्रम to limit
	 * traffic क्रम calls like is_remote_recovering and get_resync_work,
	 * but be take care in its use क्रम anything अन्यथा.
	 */
	uपूर्णांक64_t in_sync_hपूर्णांक;

	/*
	 * Workqueue क्रम flush of clear region requests.
	 */
	काष्ठा workqueue_काष्ठा *dmlog_wq;
	काष्ठा delayed_work flush_log_work;
	atomic_t sched_flush;

	/*
	 * Combine userspace flush and mark requests क्रम efficiency.
	 */
	uपूर्णांक32_t पूर्णांकegrated_flush;

	mempool_t flush_entry_pool;
पूर्ण;

अटल काष्ठा kmem_cache *_flush_entry_cache;

अटल पूर्णांक userspace_करो_request(काष्ठा log_c *lc, स्थिर अक्षर *uuid,
				पूर्णांक request_type, अक्षर *data, माप_प्रकार data_size,
				अक्षर *rdata, माप_प्रकार *rdata_size)
अणु
	पूर्णांक r;

	/*
	 * If the server isn't there, -ESRCH is वापसed,
	 * and we must keep trying until the server is
	 * restored.
	 */
retry:
	r = dm_consult_userspace(uuid, lc->luid, request_type, data,
				 data_size, rdata, rdata_size);

	अगर (r != -ESRCH)
		वापस r;

	DMERR(" Userspace log server not found.");
	जबतक (1) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(2*HZ);
		DMWARN("Attempting to contact userspace log server...");
		r = dm_consult_userspace(uuid, lc->luid, DM_ULOG_CTR,
					 lc->usr_argv_str,
					 म_माप(lc->usr_argv_str) + 1,
					 शून्य, शून्य);
		अगर (!r)
			अवरोध;
	पूर्ण
	DMINFO("Reconnected to userspace log server... DM_ULOG_CTR complete");
	r = dm_consult_userspace(uuid, lc->luid, DM_ULOG_RESUME, शून्य,
				 0, शून्य, शून्य);
	अगर (!r)
		जाओ retry;

	DMERR("Error trying to resume userspace log: %d", r);

	वापस -ESRCH;
पूर्ण

अटल पूर्णांक build_स्थिरructor_string(काष्ठा dm_target *ti,
				    अचिन्हित argc, अक्षर **argv,
				    अक्षर **ctr_str)
अणु
	पूर्णांक i, str_size;
	अक्षर *str = शून्य;

	*ctr_str = शून्य;

	/*
	 * Determine overall size of the string.
	 */
	क्रम (i = 0, str_size = 0; i < argc; i++)
		str_size += म_माप(argv[i]) + 1; /* +1 क्रम space between args */

	str_size += 20; /* Max number of अक्षरs in a prपूर्णांकed u64 number */

	str = kzalloc(str_size, GFP_KERNEL);
	अगर (!str) अणु
		DMWARN("Unable to allocate memory for constructor string");
		वापस -ENOMEM;
	पूर्ण

	str_size = प्र_लिखो(str, "%llu", (अचिन्हित दीर्घ दीर्घ)ti->len);
	क्रम (i = 0; i < argc; i++)
		str_size += प्र_लिखो(str + str_size, " %s", argv[i]);

	*ctr_str = str;
	वापस str_size;
पूर्ण

अटल व्योम करो_flush(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक r;
	काष्ठा log_c *lc = container_of(work, काष्ठा log_c, flush_log_work.work);

	atomic_set(&lc->sched_flush, 0);

	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_FLUSH, शून्य, 0, शून्य, शून्य);

	अगर (r)
		dm_table_event(lc->ti->table);
पूर्ण

/*
 * userspace_ctr
 *
 * argv contains:
 *	<UUID> [पूर्णांकegrated_flush] <other args>
 * Where 'other args' are the userspace implementation-specअगरic log
 * arguments.
 *
 * Example:
 *	<UUID> [पूर्णांकegrated_flush] clustered-disk <arg count> <log dev>
 *	<region_size> [[no]sync]
 *
 * This module strips off the <UUID> and uses it क्रम identअगरication
 * purposes when communicating with userspace about a log.
 *
 * If पूर्णांकegrated_flush is defined, the kernel combines flush
 * and mark requests.
 *
 * The rest of the line, beginning with 'clustered-disk', is passed
 * to the userspace ctr function.
 */
अटल पूर्णांक userspace_ctr(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
			 अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक r = 0;
	पूर्णांक str_size;
	अक्षर *ctr_str = शून्य;
	काष्ठा log_c *lc = शून्य;
	uपूर्णांक64_t rdata;
	माप_प्रकार rdata_size = माप(rdata);
	अक्षर *devices_rdata = शून्य;
	माप_प्रकार devices_rdata_size = DM_NAME_LEN;

	अगर (argc < 3) अणु
		DMWARN("Too few arguments to userspace dirty log");
		वापस -EINVAL;
	पूर्ण

	lc = kzalloc(माप(*lc), GFP_KERNEL);
	अगर (!lc) अणु
		DMWARN("Unable to allocate userspace log context.");
		वापस -ENOMEM;
	पूर्ण

	/* The ptr value is sufficient क्रम local unique id */
	lc->luid = (अचिन्हित दीर्घ)lc;

	lc->ti = ti;

	अगर (म_माप(argv[0]) > (DM_UUID_LEN - 1)) अणु
		DMWARN("UUID argument too long.");
		kमुक्त(lc);
		वापस -EINVAL;
	पूर्ण

	lc->usr_argc = argc;

	म_नकलन(lc->uuid, argv[0], DM_UUID_LEN);
	argc--;
	argv++;
	spin_lock_init(&lc->flush_lock);
	INIT_LIST_HEAD(&lc->mark_list);
	INIT_LIST_HEAD(&lc->clear_list);

	अगर (!strहालcmp(argv[0], "integrated_flush")) अणु
		lc->पूर्णांकegrated_flush = 1;
		argc--;
		argv++;
	पूर्ण

	str_size = build_स्थिरructor_string(ti, argc, argv, &ctr_str);
	अगर (str_size < 0) अणु
		kमुक्त(lc);
		वापस str_size;
	पूर्ण

	devices_rdata = kzalloc(devices_rdata_size, GFP_KERNEL);
	अगर (!devices_rdata) अणु
		DMERR("Failed to allocate memory for device information");
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	r = mempool_init_slab_pool(&lc->flush_entry_pool, FLUSH_ENTRY_POOL_SIZE,
				   _flush_entry_cache);
	अगर (r) अणु
		DMERR("Failed to create flush_entry_pool");
		जाओ out;
	पूर्ण

	/*
	 * Send table string and get back any खोलोed device.
	 */
	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_CTR,
				 ctr_str, str_size,
				 devices_rdata, &devices_rdata_size);

	अगर (r < 0) अणु
		अगर (r == -ESRCH)
			DMERR("Userspace log server not found");
		अन्यथा
			DMERR("Userspace log server failed to create log");
		जाओ out;
	पूर्ण

	/* Since the region size करोes not change, get it now */
	rdata_size = माप(rdata);
	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_GET_REGION_SIZE,
				 शून्य, 0, (अक्षर *)&rdata, &rdata_size);

	अगर (r) अणु
		DMERR("Failed to get region size of dirty log");
		जाओ out;
	पूर्ण

	lc->region_size = (uपूर्णांक32_t)rdata;
	lc->region_count = dm_sector_भाग_up(ti->len, lc->region_size);

	अगर (devices_rdata_size) अणु
		अगर (devices_rdata[devices_rdata_size - 1] != '\0') अणु
			DMERR("DM_ULOG_CTR device return string not properly terminated");
			r = -EINVAL;
			जाओ out;
		पूर्ण
		r = dm_get_device(ti, devices_rdata,
				  dm_table_get_mode(ti->table), &lc->log_dev);
		अगर (r)
			DMERR("Failed to register %s with device-mapper",
			      devices_rdata);
	पूर्ण

	अगर (lc->पूर्णांकegrated_flush) अणु
		lc->dmlog_wq = alloc_workqueue("dmlogd", WQ_MEM_RECLAIM, 0);
		अगर (!lc->dmlog_wq) अणु
			DMERR("couldn't start dmlogd");
			r = -ENOMEM;
			जाओ out;
		पूर्ण

		INIT_DELAYED_WORK(&lc->flush_log_work, करो_flush);
		atomic_set(&lc->sched_flush, 0);
	पूर्ण

out:
	kमुक्त(devices_rdata);
	अगर (r) अणु
		mempool_निकास(&lc->flush_entry_pool);
		kमुक्त(lc);
		kमुक्त(ctr_str);
	पूर्ण अन्यथा अणु
		lc->usr_argv_str = ctr_str;
		log->context = lc;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम userspace_dtr(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = log->context;

	अगर (lc->पूर्णांकegrated_flush) अणु
		/* flush workqueue */
		अगर (atomic_पढ़ो(&lc->sched_flush))
			flush_delayed_work(&lc->flush_log_work);

		destroy_workqueue(lc->dmlog_wq);
	पूर्ण

	(व्योम) dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_DTR,
				    शून्य, 0, शून्य, शून्य);

	अगर (lc->log_dev)
		dm_put_device(lc->ti, lc->log_dev);

	mempool_निकास(&lc->flush_entry_pool);

	kमुक्त(lc->usr_argv_str);
	kमुक्त(lc);

	वापस;
पूर्ण

अटल पूर्णांक userspace_presuspend(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r;
	काष्ठा log_c *lc = log->context;

	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_PRESUSPEND,
				 शून्य, 0, शून्य, शून्य);

	वापस r;
पूर्ण

अटल पूर्णांक userspace_postsuspend(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r;
	काष्ठा log_c *lc = log->context;

	/*
	 * Run planned flush earlier.
	 */
	अगर (lc->पूर्णांकegrated_flush && atomic_पढ़ो(&lc->sched_flush))
		flush_delayed_work(&lc->flush_log_work);

	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_POSTSUSPEND,
				 शून्य, 0, शून्य, शून्य);

	वापस r;
पूर्ण

अटल पूर्णांक userspace_resume(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r;
	काष्ठा log_c *lc = log->context;

	lc->in_sync_hपूर्णांक = 0;
	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_RESUME,
				 शून्य, 0, शून्य, शून्य);

	वापस r;
पूर्ण

अटल uपूर्णांक32_t userspace_get_region_size(काष्ठा dm_dirty_log *log)
अणु
	काष्ठा log_c *lc = log->context;

	वापस lc->region_size;
पूर्ण

/*
 * userspace_is_clean
 *
 * Check whether a region is clean.  If there is any sort of
 * failure when consulting the server, we वापस not clean.
 *
 * Returns: 1 अगर clean, 0 otherwise
 */
अटल पूर्णांक userspace_is_clean(काष्ठा dm_dirty_log *log, region_t region)
अणु
	पूर्णांक r;
	uपूर्णांक64_t region64 = (uपूर्णांक64_t)region;
	पूर्णांक64_t is_clean;
	माप_प्रकार rdata_size;
	काष्ठा log_c *lc = log->context;

	rdata_size = माप(is_clean);
	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_IS_CLEAN,
				 (अक्षर *)&region64, माप(region64),
				 (अक्षर *)&is_clean, &rdata_size);

	वापस (r) ? 0 : (पूर्णांक)is_clean;
पूर्ण

/*
 * userspace_in_sync
 *
 * Check अगर the region is in-sync.  If there is any sort
 * of failure when consulting the server, we assume that
 * the region is not in sync.
 *
 * If 'can_block' is set, वापस immediately
 *
 * Returns: 1 अगर in-sync, 0 अगर not-in-sync, -EWOULDBLOCK
 */
अटल पूर्णांक userspace_in_sync(काष्ठा dm_dirty_log *log, region_t region,
			     पूर्णांक can_block)
अणु
	पूर्णांक r;
	uपूर्णांक64_t region64 = region;
	पूर्णांक64_t in_sync;
	माप_प्रकार rdata_size;
	काष्ठा log_c *lc = log->context;

	/*
	 * We can never respond directly - even अगर in_sync_hपूर्णांक is
	 * set.  This is because another machine could see a device
	 * failure and mark the region out-of-sync.  If we करोn't go
	 * to userspace to ask, we might think the region is in-sync
	 * and allow a पढ़ो to pick up data that is stale.  (This is
	 * very unlikely अगर a device actually fails; but it is very
	 * likely अगर a connection to one device from one machine fails.)
	 *
	 * There still might be a problem अगर the mirror caches the region
	 * state as in-sync... but then this call would not be made.  So,
	 * that is a mirror problem.
	 */
	अगर (!can_block)
		वापस -EWOULDBLOCK;

	rdata_size = माप(in_sync);
	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_IN_SYNC,
				 (अक्षर *)&region64, माप(region64),
				 (अक्षर *)&in_sync, &rdata_size);
	वापस (r) ? 0 : (पूर्णांक)in_sync;
पूर्ण

अटल पूर्णांक flush_one_by_one(काष्ठा log_c *lc, काष्ठा list_head *flush_list)
अणु
	पूर्णांक r = 0;
	काष्ठा dm_dirty_log_flush_entry *fe;

	list_क्रम_each_entry(fe, flush_list, list) अणु
		r = userspace_करो_request(lc, lc->uuid, fe->type,
					 (अक्षर *)&fe->region,
					 माप(fe->region),
					 शून्य, शून्य);
		अगर (r)
			अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक flush_by_group(काष्ठा log_c *lc, काष्ठा list_head *flush_list,
			  पूर्णांक flush_with_payload)
अणु
	पूर्णांक r = 0;
	पूर्णांक count;
	uपूर्णांक32_t type = 0;
	काष्ठा dm_dirty_log_flush_entry *fe, *पंचांगp_fe;
	LIST_HEAD(पंचांगp_list);
	uपूर्णांक64_t group[MAX_FLUSH_GROUP_COUNT];

	/*
	 * Group process the requests
	 */
	जबतक (!list_empty(flush_list)) अणु
		count = 0;

		list_क्रम_each_entry_safe(fe, पंचांगp_fe, flush_list, list) अणु
			group[count] = fe->region;
			count++;

			list_move(&fe->list, &पंचांगp_list);

			type = fe->type;
			अगर (count >= MAX_FLUSH_GROUP_COUNT)
				अवरोध;
		पूर्ण

		अगर (flush_with_payload) अणु
			r = userspace_करो_request(lc, lc->uuid, DM_ULOG_FLUSH,
						 (अक्षर *)(group),
						 count * माप(uपूर्णांक64_t),
						 शून्य, शून्य);
			/*
			 * Integrated flush failed.
			 */
			अगर (r)
				अवरोध;
		पूर्ण अन्यथा अणु
			r = userspace_करो_request(lc, lc->uuid, type,
						 (अक्षर *)(group),
						 count * माप(uपूर्णांक64_t),
						 शून्य, शून्य);
			अगर (r) अणु
				/*
				 * Group send failed.  Attempt one-by-one.
				 */
				list_splice_init(&पंचांगp_list, flush_list);
				r = flush_one_by_one(lc, flush_list);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Must collect flush_entrys that were successfully processed
	 * as a group so that they will be मुक्त'd by the caller.
	 */
	list_splice_init(&पंचांगp_list, flush_list);

	वापस r;
पूर्ण

/*
 * userspace_flush
 *
 * This function is ok to block.
 * The flush happens in two stages.  First, it sends all
 * clear/mark requests that are on the list.  Then it
 * tells the server to commit them.  This gives the
 * server a chance to optimise the commit, instead of
 * करोing it क्रम every request.
 *
 * Additionally, we could implement another thपढ़ो that
 * sends the requests up to the server - reducing the
 * load on flush.  Then the flush would have less in
 * the list and be responsible क्रम the finishing commit.
 *
 * Returns: 0 on success, < 0 on failure
 */
अटल पूर्णांक userspace_flush(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा log_c *lc = log->context;
	LIST_HEAD(mark_list);
	LIST_HEAD(clear_list);
	पूर्णांक mark_list_is_empty;
	पूर्णांक clear_list_is_empty;
	काष्ठा dm_dirty_log_flush_entry *fe, *पंचांगp_fe;
	mempool_t *flush_entry_pool = &lc->flush_entry_pool;

	spin_lock_irqsave(&lc->flush_lock, flags);
	list_splice_init(&lc->mark_list, &mark_list);
	list_splice_init(&lc->clear_list, &clear_list);
	spin_unlock_irqrestore(&lc->flush_lock, flags);

	mark_list_is_empty = list_empty(&mark_list);
	clear_list_is_empty = list_empty(&clear_list);

	अगर (mark_list_is_empty && clear_list_is_empty)
		वापस 0;

	r = flush_by_group(lc, &clear_list, 0);
	अगर (r)
		जाओ out;

	अगर (!lc->पूर्णांकegrated_flush) अणु
		r = flush_by_group(lc, &mark_list, 0);
		अगर (r)
			जाओ out;
		r = userspace_करो_request(lc, lc->uuid, DM_ULOG_FLUSH,
					 शून्य, 0, शून्य, शून्य);
		जाओ out;
	पूर्ण

	/*
	 * Send पूर्णांकegrated flush request with mark_list as payload.
	 */
	r = flush_by_group(lc, &mark_list, 1);
	अगर (r)
		जाओ out;

	अगर (mark_list_is_empty && !atomic_पढ़ो(&lc->sched_flush)) अणु
		/*
		 * When there are only clear region requests,
		 * we schedule a flush in the future.
		 */
		queue_delayed_work(lc->dmlog_wq, &lc->flush_log_work, 3 * HZ);
		atomic_set(&lc->sched_flush, 1);
	पूर्ण अन्यथा अणु
		/*
		 * Cancel pending flush because we
		 * have alपढ़ोy flushed in mark_region.
		 */
		cancel_delayed_work(&lc->flush_log_work);
		atomic_set(&lc->sched_flush, 0);
	पूर्ण

out:
	/*
	 * We can safely हटाओ these entries, even after failure.
	 * Calling code will receive an error and will know that
	 * the log facility has failed.
	 */
	list_क्रम_each_entry_safe(fe, पंचांगp_fe, &mark_list, list) अणु
		list_del(&fe->list);
		mempool_मुक्त(fe, flush_entry_pool);
	पूर्ण
	list_क्रम_each_entry_safe(fe, पंचांगp_fe, &clear_list, list) अणु
		list_del(&fe->list);
		mempool_मुक्त(fe, flush_entry_pool);
	पूर्ण

	अगर (r)
		dm_table_event(lc->ti->table);

	वापस r;
पूर्ण

/*
 * userspace_mark_region
 *
 * This function should aव्योम blocking unless असलolutely required.
 * (Memory allocation is valid क्रम blocking.)
 */
अटल व्योम userspace_mark_region(काष्ठा dm_dirty_log *log, region_t region)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा log_c *lc = log->context;
	काष्ठा dm_dirty_log_flush_entry *fe;

	/* Wait क्रम an allocation, but _never_ fail */
	fe = mempool_alloc(&lc->flush_entry_pool, GFP_NOIO);
	BUG_ON(!fe);

	spin_lock_irqsave(&lc->flush_lock, flags);
	fe->type = DM_ULOG_MARK_REGION;
	fe->region = region;
	list_add(&fe->list, &lc->mark_list);
	spin_unlock_irqrestore(&lc->flush_lock, flags);

	वापस;
पूर्ण

/*
 * userspace_clear_region
 *
 * This function must not block.
 * So, the alloc can't block.  In the worst हाल, it is ok to
 * fail.  It would simply mean we can't clear the region.
 * Does nothing to current sync context, but करोes mean
 * the region will be re-sync'ed on a reload of the mirror
 * even though it is in-sync.
 */
अटल व्योम userspace_clear_region(काष्ठा dm_dirty_log *log, region_t region)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा log_c *lc = log->context;
	काष्ठा dm_dirty_log_flush_entry *fe;

	/*
	 * If we fail to allocate, we skip the clearing of
	 * the region.  This करोesn't hurt us in any way, except
	 * to cause the region to be resync'ed when the
	 * device is activated next समय.
	 */
	fe = mempool_alloc(&lc->flush_entry_pool, GFP_ATOMIC);
	अगर (!fe) अणु
		DMERR("Failed to allocate memory to clear region.");
		वापस;
	पूर्ण

	spin_lock_irqsave(&lc->flush_lock, flags);
	fe->type = DM_ULOG_CLEAR_REGION;
	fe->region = region;
	list_add(&fe->list, &lc->clear_list);
	spin_unlock_irqrestore(&lc->flush_lock, flags);

	वापस;
पूर्ण

/*
 * userspace_get_resync_work
 *
 * Get a region that needs recovery.  It is valid to वापस
 * an error क्रम this function.
 *
 * Returns: 1 अगर region filled, 0 अगर no work, <0 on error
 */
अटल पूर्णांक userspace_get_resync_work(काष्ठा dm_dirty_log *log, region_t *region)
अणु
	पूर्णांक r;
	माप_प्रकार rdata_size;
	काष्ठा log_c *lc = log->context;
	काष्ठा अणु
		पूर्णांक64_t i; /* 64-bit क्रम mix arch compatibility */
		region_t r;
	पूर्ण pkg;

	अगर (lc->in_sync_hपूर्णांक >= lc->region_count)
		वापस 0;

	rdata_size = माप(pkg);
	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_GET_RESYNC_WORK,
				 शून्य, 0, (अक्षर *)&pkg, &rdata_size);

	*region = pkg.r;
	वापस (r) ? r : (पूर्णांक)pkg.i;
पूर्ण

/*
 * userspace_set_region_sync
 *
 * Set the sync status of a given region.  This function
 * must not fail.
 */
अटल व्योम userspace_set_region_sync(काष्ठा dm_dirty_log *log,
				      region_t region, पूर्णांक in_sync)
अणु
	काष्ठा log_c *lc = log->context;
	काष्ठा अणु
		region_t r;
		पूर्णांक64_t i;
	पूर्ण pkg;

	pkg.r = region;
	pkg.i = (पूर्णांक64_t)in_sync;

	(व्योम) userspace_करो_request(lc, lc->uuid, DM_ULOG_SET_REGION_SYNC,
				    (अक्षर *)&pkg, माप(pkg), शून्य, शून्य);

	/*
	 * It would be nice to be able to report failures.
	 * However, it is easy enough to detect and resolve.
	 */
	वापस;
पूर्ण

/*
 * userspace_get_sync_count
 *
 * If there is any sort of failure when consulting the server,
 * we assume that the sync count is zero.
 *
 * Returns: sync count on success, 0 on failure
 */
अटल region_t userspace_get_sync_count(काष्ठा dm_dirty_log *log)
अणु
	पूर्णांक r;
	माप_प्रकार rdata_size;
	uपूर्णांक64_t sync_count;
	काष्ठा log_c *lc = log->context;

	rdata_size = माप(sync_count);
	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_GET_SYNC_COUNT,
				 शून्य, 0, (अक्षर *)&sync_count, &rdata_size);

	अगर (r)
		वापस 0;

	अगर (sync_count >= lc->region_count)
		lc->in_sync_hपूर्णांक = lc->region_count;

	वापस (region_t)sync_count;
पूर्ण

/*
 * userspace_status
 *
 * Returns: amount of space consumed
 */
अटल पूर्णांक userspace_status(काष्ठा dm_dirty_log *log, status_type_t status_type,
			    अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = 0;
	अक्षर *table_args;
	माप_प्रकार sz = (माप_प्रकार)maxlen;
	काष्ठा log_c *lc = log->context;

	चयन (status_type) अणु
	हाल STATUSTYPE_INFO:
		r = userspace_करो_request(lc, lc->uuid, DM_ULOG_STATUS_INFO,
					 शून्य, 0, result, &sz);

		अगर (r) अणु
			sz = 0;
			DMEMIT("%s 1 COM_FAILURE", log->type->name);
		पूर्ण
		अवरोध;
	हाल STATUSTYPE_TABLE:
		sz = 0;
		table_args = म_अक्षर(lc->usr_argv_str, ' ');
		BUG_ON(!table_args); /* There will always be a ' ' */
		table_args++;

		DMEMIT("%s %u %s ", log->type->name, lc->usr_argc, lc->uuid);
		अगर (lc->पूर्णांकegrated_flush)
			DMEMIT("integrated_flush ");
		DMEMIT("%s ", table_args);
		अवरोध;
	पूर्ण
	वापस (r) ? 0 : (पूर्णांक)sz;
पूर्ण

/*
 * userspace_is_remote_recovering
 *
 * Returns: 1 अगर region recovering, 0 otherwise
 */
अटल पूर्णांक userspace_is_remote_recovering(काष्ठा dm_dirty_log *log,
					  region_t region)
अणु
	पूर्णांक r;
	uपूर्णांक64_t region64 = region;
	काष्ठा log_c *lc = log->context;
	अटल अचिन्हित दीर्घ limit;
	काष्ठा अणु
		पूर्णांक64_t is_recovering;
		uपूर्णांक64_t in_sync_hपूर्णांक;
	पूर्ण pkg;
	माप_प्रकार rdata_size = माप(pkg);

	/*
	 * Once the mirror has been reported to be in-sync,
	 * it will never again ask क्रम recovery work.  So,
	 * we can safely say there is not a remote machine
	 * recovering अगर the device is in-sync.  (in_sync_hपूर्णांक
	 * must be reset at resume समय.)
	 */
	अगर (region < lc->in_sync_hपूर्णांक)
		वापस 0;
	अन्यथा अगर (समय_after(limit, jअगरfies))
		वापस 1;

	limit = jअगरfies + (HZ / 4);
	r = userspace_करो_request(lc, lc->uuid, DM_ULOG_IS_REMOTE_RECOVERING,
				 (अक्षर *)&region64, माप(region64),
				 (अक्षर *)&pkg, &rdata_size);
	अगर (r)
		वापस 1;

	lc->in_sync_hपूर्णांक = pkg.in_sync_hपूर्णांक;

	वापस (पूर्णांक)pkg.is_recovering;
पूर्ण

अटल काष्ठा dm_dirty_log_type _userspace_type = अणु
	.name = "userspace",
	.module = THIS_MODULE,
	.ctr = userspace_ctr,
	.dtr = userspace_dtr,
	.presuspend = userspace_presuspend,
	.postsuspend = userspace_postsuspend,
	.resume = userspace_resume,
	.get_region_size = userspace_get_region_size,
	.is_clean = userspace_is_clean,
	.in_sync = userspace_in_sync,
	.flush = userspace_flush,
	.mark_region = userspace_mark_region,
	.clear_region = userspace_clear_region,
	.get_resync_work = userspace_get_resync_work,
	.set_region_sync = userspace_set_region_sync,
	.get_sync_count = userspace_get_sync_count,
	.status = userspace_status,
	.is_remote_recovering = userspace_is_remote_recovering,
पूर्ण;

अटल पूर्णांक __init userspace_dirty_log_init(व्योम)
अणु
	पूर्णांक r = 0;

	_flush_entry_cache = KMEM_CACHE(dm_dirty_log_flush_entry, 0);
	अगर (!_flush_entry_cache) अणु
		DMWARN("Unable to create flush_entry_cache: No memory.");
		वापस -ENOMEM;
	पूर्ण

	r = dm_ulog_tfr_init();
	अगर (r) अणु
		DMWARN("Unable to initialize userspace log communications");
		kmem_cache_destroy(_flush_entry_cache);
		वापस r;
	पूर्ण

	r = dm_dirty_log_type_रेजिस्टर(&_userspace_type);
	अगर (r) अणु
		DMWARN("Couldn't register userspace dirty log type");
		dm_ulog_tfr_निकास();
		kmem_cache_destroy(_flush_entry_cache);
		वापस r;
	पूर्ण

	DMINFO("version " DM_LOG_USERSPACE_VSN " loaded");
	वापस 0;
पूर्ण

अटल व्योम __निकास userspace_dirty_log_निकास(व्योम)
अणु
	dm_dirty_log_type_unरेजिस्टर(&_userspace_type);
	dm_ulog_tfr_निकास();
	kmem_cache_destroy(_flush_entry_cache);

	DMINFO("version " DM_LOG_USERSPACE_VSN " unloaded");
	वापस;
पूर्ण

module_init(userspace_dirty_log_init);
module_निकास(userspace_dirty_log_निकास);

MODULE_DESCRIPTION(DM_NAME " userspace dirty log link");
MODULE_AUTHOR("Jonathan Brassow <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
