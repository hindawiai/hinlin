<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.

   Thanks to Carter Burden, Bart Grantham and Gennadiy Nerubayev
   from Logicworks, Inc. क्रम making SDP replication support possible.


 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/drbd.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/types.h>
#समावेश <net/sock.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/reboot.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/workqueue.h>
#घोषणा __KERNEL_SYSCALLS__
#समावेश <linux/unistd.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/drbd_सीमा.स>
#समावेश "drbd_int.h"
#समावेश "drbd_protocol.h"
#समावेश "drbd_req.h" /* only क्रम _req_mod in tl_release and tl_clear */
#समावेश "drbd_vli.h"
#समावेश "drbd_debugfs.h"

अटल DEFINE_MUTEX(drbd_मुख्य_mutex);
अटल पूर्णांक drbd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल व्योम drbd_release(काष्ठा gendisk *gd, भ_शेषe_t mode);
अटल व्योम md_sync_समयr_fn(काष्ठा समयr_list *t);
अटल पूर्णांक w_biपंचांगap_io(काष्ठा drbd_work *w, पूर्णांक unused);

MODULE_AUTHOR("Philipp Reisner <phil@linbit.com>, "
	      "Lars Ellenberg <lars@linbit.com>");
MODULE_DESCRIPTION("drbd - Distributed Replicated Block Device v" REL_VERSION);
MODULE_VERSION(REL_VERSION);
MODULE_LICENSE("GPL");
MODULE_PARM_DESC(minor_count, "Approximate number of drbd devices ("
		 __stringअगरy(DRBD_MINOR_COUNT_MIN) "-" __stringअगरy(DRBD_MINOR_COUNT_MAX) ")");
MODULE_ALIAS_BLOCKDEV_MAJOR(DRBD_MAJOR);

#समावेश <linux/moduleparam.h>
/* thanks to these macros, अगर compiled पूर्णांकo the kernel (not-module),
 * these become boot parameters (e.g., drbd.minor_count) */

#अगर_घोषित CONFIG_DRBD_FAULT_INJECTION
पूर्णांक drbd_enable_faults;
पूर्णांक drbd_fault_rate;
अटल पूर्णांक drbd_fault_count;
अटल पूर्णांक drbd_fault_devs;
/* biपंचांगap of enabled faults */
module_param_named(enable_faults, drbd_enable_faults, पूर्णांक, 0664);
/* fault rate % value - applies to all enabled faults */
module_param_named(fault_rate, drbd_fault_rate, पूर्णांक, 0664);
/* count of faults inserted */
module_param_named(fault_count, drbd_fault_count, पूर्णांक, 0664);
/* biपंचांगap of devices to insert faults on */
module_param_named(fault_devs, drbd_fault_devs, पूर्णांक, 0644);
#पूर्ण_अगर

/* module parameters we can keep अटल */
अटल bool drbd_allow_oos; /* allow_खोलो_on_secondary */
अटल bool drbd_disable_sendpage;
MODULE_PARM_DESC(allow_oos, "DONT USE!");
module_param_named(allow_oos, drbd_allow_oos, bool, 0);
module_param_named(disable_sendpage, drbd_disable_sendpage, bool, 0644);

/* module parameters we share */
पूर्णांक drbd_proc_details; /* Detail level in proc drbd*/
module_param_named(proc_details, drbd_proc_details, पूर्णांक, 0644);
/* module parameters shared with शेषs */
अचिन्हित पूर्णांक drbd_minor_count = DRBD_MINOR_COUNT_DEF;
/* Module parameter क्रम setting the user mode helper program
 * to run. Default is /sbin/drbdadm */
अक्षर drbd_usermode_helper[80] = "/sbin/drbdadm";
module_param_named(minor_count, drbd_minor_count, uपूर्णांक, 0444);
module_param_string(usermode_helper, drbd_usermode_helper, माप(drbd_usermode_helper), 0644);

/* in 2.6.x, our device mapping and config info contains our भव gendisks
 * as member "struct gendisk *vdisk;"
 */
काष्ठा idr drbd_devices;
काष्ठा list_head drbd_resources;
काष्ठा mutex resources_mutex;

काष्ठा kmem_cache *drbd_request_cache;
काष्ठा kmem_cache *drbd_ee_cache;	/* peer requests */
काष्ठा kmem_cache *drbd_bm_ext_cache;	/* biपंचांगap extents */
काष्ठा kmem_cache *drbd_al_ext_cache;	/* activity log extents */
mempool_t drbd_request_mempool;
mempool_t drbd_ee_mempool;
mempool_t drbd_md_io_page_pool;
काष्ठा bio_set drbd_md_io_bio_set;
काष्ठा bio_set drbd_io_bio_set;

/* I करो not use a standard mempool, because:
   1) I want to hand out the pre-allocated objects first.
   2) I want to be able to पूर्णांकerrupt sleeping allocation with a संकेत.
   Note: This is a single linked list, the next poपूर्णांकer is the निजी
	 member of काष्ठा page.
 */
काष्ठा page *drbd_pp_pool;
DEFINE_SPINLOCK(drbd_pp_lock);
पूर्णांक          drbd_pp_vacant;
रुको_queue_head_t drbd_pp_रुको;

DEFINE_RATELIMIT_STATE(drbd_ratelimit_state, 5 * HZ, 5);

अटल स्थिर काष्ठा block_device_operations drbd_ops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= drbd_submit_bio,
	.खोलो		= drbd_खोलो,
	.release	= drbd_release,
पूर्ण;

#अगर_घोषित __CHECKER__
/* When checking with sparse, and this is an अंतरभूत function, sparse will
   give tons of false positives. When this is a real functions sparse works.
 */
पूर्णांक _get_ldev_अगर_state(काष्ठा drbd_device *device, क्रमागत drbd_disk_state mins)
अणु
	पूर्णांक io_allowed;

	atomic_inc(&device->local_cnt);
	io_allowed = (device->state.disk >= mins);
	अगर (!io_allowed) अणु
		अगर (atomic_dec_and_test(&device->local_cnt))
			wake_up(&device->misc_रुको);
	पूर्ण
	वापस io_allowed;
पूर्ण

#पूर्ण_अगर

/**
 * tl_release() - mark as BARRIER_ACKED all requests in the corresponding transfer log epoch
 * @connection:	DRBD connection.
 * @barrier_nr:	Expected identअगरier of the DRBD ग_लिखो barrier packet.
 * @set_size:	Expected number of requests beक्रमe that barrier.
 *
 * In हाल the passed barrier_nr or set_size करोes not match the oldest
 * epoch of not yet barrier-acked requests, this function will cause a
 * termination of the connection.
 */
व्योम tl_release(काष्ठा drbd_connection *connection, अचिन्हित पूर्णांक barrier_nr,
		अचिन्हित पूर्णांक set_size)
अणु
	काष्ठा drbd_request *r;
	काष्ठा drbd_request *req = शून्य;
	पूर्णांक expect_epoch = 0;
	पूर्णांक expect_size = 0;

	spin_lock_irq(&connection->resource->req_lock);

	/* find oldest not yet barrier-acked ग_लिखो request,
	 * count ग_लिखोs in its epoch. */
	list_क्रम_each_entry(r, &connection->transfer_log, tl_requests) अणु
		स्थिर अचिन्हित s = r->rq_state;
		अगर (!req) अणु
			अगर (!(s & RQ_WRITE))
				जारी;
			अगर (!(s & RQ_NET_MASK))
				जारी;
			अगर (s & RQ_NET_DONE)
				जारी;
			req = r;
			expect_epoch = req->epoch;
			expect_size ++;
		पूर्ण अन्यथा अणु
			अगर (r->epoch != expect_epoch)
				अवरोध;
			अगर (!(s & RQ_WRITE))
				जारी;
			/* अगर (s & RQ_DONE): not expected */
			/* अगर (!(s & RQ_NET_MASK)): not expected */
			expect_size++;
		पूर्ण
	पूर्ण

	/* first some paranoia code */
	अगर (req == शून्य) अणु
		drbd_err(connection, "BAD! BarrierAck #%u received, but no epoch in tl!?\n",
			 barrier_nr);
		जाओ bail;
	पूर्ण
	अगर (expect_epoch != barrier_nr) अणु
		drbd_err(connection, "BAD! BarrierAck #%u received, expected #%u!\n",
			 barrier_nr, expect_epoch);
		जाओ bail;
	पूर्ण

	अगर (expect_size != set_size) अणु
		drbd_err(connection, "BAD! BarrierAck #%u received with n_writes=%u, expected n_writes=%u!\n",
			 barrier_nr, set_size, expect_size);
		जाओ bail;
	पूर्ण

	/* Clean up list of requests processed during current epoch. */
	/* this extra list walk restart is paranoia,
	 * to catch requests being barrier-acked "unexpectedly".
	 * It usually should find the same req again, or some READ preceding it. */
	list_क्रम_each_entry(req, &connection->transfer_log, tl_requests)
		अगर (req->epoch == expect_epoch)
			अवरोध;
	list_क्रम_each_entry_safe_from(req, r, &connection->transfer_log, tl_requests) अणु
		अगर (req->epoch != expect_epoch)
			अवरोध;
		_req_mod(req, BARRIER_ACKED);
	पूर्ण
	spin_unlock_irq(&connection->resource->req_lock);

	वापस;

bail:
	spin_unlock_irq(&connection->resource->req_lock);
	conn_request_state(connection, NS(conn, C_PROTOCOL_ERROR), CS_HARD);
पूर्ण


/**
 * _tl_restart() - Walks the transfer log, and applies an action to all requests
 * @connection:	DRBD connection to operate on.
 * @what:       The action/event to perक्रमm with all request objects
 *
 * @what might be one of CONNECTION_LOST_WHILE_PENDING, RESEND, FAIL_FROZEN_DISK_IO,
 * RESTART_FROZEN_DISK_IO.
 */
/* must hold resource->req_lock */
व्योम _tl_restart(काष्ठा drbd_connection *connection, क्रमागत drbd_req_event what)
अणु
	काष्ठा drbd_request *req, *r;

	list_क्रम_each_entry_safe(req, r, &connection->transfer_log, tl_requests)
		_req_mod(req, what);
पूर्ण

व्योम tl_restart(काष्ठा drbd_connection *connection, क्रमागत drbd_req_event what)
अणु
	spin_lock_irq(&connection->resource->req_lock);
	_tl_restart(connection, what);
	spin_unlock_irq(&connection->resource->req_lock);
पूर्ण

/**
 * tl_clear() - Clears all requests and &काष्ठा drbd_tl_epoch objects out of the TL
 * @connection:	DRBD connection.
 *
 * This is called after the connection to the peer was lost. The storage covered
 * by the requests on the transfer माला_लो marked as our of sync. Called from the
 * receiver thपढ़ो and the worker thपढ़ो.
 */
व्योम tl_clear(काष्ठा drbd_connection *connection)
अणु
	tl_restart(connection, CONNECTION_LOST_WHILE_PENDING);
पूर्ण

/**
 * tl_पात_disk_io() - Abort disk I/O क्रम all requests क्रम a certain device in the TL
 * @device:	DRBD device.
 */
व्योम tl_पात_disk_io(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	काष्ठा drbd_request *req, *r;

	spin_lock_irq(&connection->resource->req_lock);
	list_क्रम_each_entry_safe(req, r, &connection->transfer_log, tl_requests) अणु
		अगर (!(req->rq_state & RQ_LOCAL_PENDING))
			जारी;
		अगर (req->device != device)
			जारी;
		_req_mod(req, ABORT_DISK_IO);
	पूर्ण
	spin_unlock_irq(&connection->resource->req_lock);
पूर्ण

अटल पूर्णांक drbd_thपढ़ो_setup(व्योम *arg)
अणु
	काष्ठा drbd_thपढ़ो *thi = (काष्ठा drbd_thपढ़ो *) arg;
	काष्ठा drbd_resource *resource = thi->resource;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	snम_लिखो(current->comm, माप(current->comm), "drbd_%c_%s",
		 thi->name[0],
		 resource->name);

	allow_kernel_संकेत(DRBD_SIGKILL);
	allow_kernel_संकेत(SIGXCPU);
restart:
	retval = thi->function(thi);

	spin_lock_irqsave(&thi->t_lock, flags);

	/* अगर the receiver has been "EXITING", the last thing it did
	 * was set the conn state to "StandAlone",
	 * अगर now a re-connect request comes in, conn state goes C_UNCONNECTED,
	 * and receiver thपढ़ो will be "started".
	 * drbd_thपढ़ो_start needs to set "RESTARTING" in that हाल.
	 * t_state check and assignment needs to be within the same spinlock,
	 * so either thपढ़ो_start sees EXITING, and can remap to RESTARTING,
	 * or thपढ़ो_start see NONE, and can proceed as normal.
	 */

	अगर (thi->t_state == RESTARTING) अणु
		drbd_info(resource, "Restarting %s thread\n", thi->name);
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		जाओ restart;
	पूर्ण

	thi->task = शून्य;
	thi->t_state = NONE;
	smp_mb();
	complete_all(&thi->stop);
	spin_unlock_irqrestore(&thi->t_lock, flags);

	drbd_info(resource, "Terminating %s\n", current->comm);

	/* Release mod reference taken when thपढ़ो was started */

	अगर (thi->connection)
		kref_put(&thi->connection->kref, drbd_destroy_connection);
	kref_put(&resource->kref, drbd_destroy_resource);
	module_put(THIS_MODULE);
	वापस retval;
पूर्ण

अटल व्योम drbd_thपढ़ो_init(काष्ठा drbd_resource *resource, काष्ठा drbd_thपढ़ो *thi,
			     पूर्णांक (*func) (काष्ठा drbd_thपढ़ो *), स्थिर अक्षर *name)
अणु
	spin_lock_init(&thi->t_lock);
	thi->task    = शून्य;
	thi->t_state = NONE;
	thi->function = func;
	thi->resource = resource;
	thi->connection = शून्य;
	thi->name = name;
पूर्ण

पूर्णांक drbd_thपढ़ो_start(काष्ठा drbd_thपढ़ो *thi)
अणु
	काष्ठा drbd_resource *resource = thi->resource;
	काष्ठा task_काष्ठा *nt;
	अचिन्हित दीर्घ flags;

	/* is used from state engine करोing drbd_thपढ़ो_stop_noरुको,
	 * जबतक holding the req lock irqsave */
	spin_lock_irqsave(&thi->t_lock, flags);

	चयन (thi->t_state) अणु
	हाल NONE:
		drbd_info(resource, "Starting %s thread (from %s [%d])\n",
			 thi->name, current->comm, current->pid);

		/* Get ref on module क्रम thपढ़ो - this is released when thपढ़ो निकासs */
		अगर (!try_module_get(THIS_MODULE)) अणु
			drbd_err(resource, "Failed to get module reference in drbd_thread_start\n");
			spin_unlock_irqrestore(&thi->t_lock, flags);
			वापस false;
		पूर्ण

		kref_get(&resource->kref);
		अगर (thi->connection)
			kref_get(&thi->connection->kref);

		init_completion(&thi->stop);
		thi->reset_cpu_mask = 1;
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		flush_संकेतs(current); /* otherw. may get -ERESTARTNOINTR */

		nt = kthपढ़ो_create(drbd_thपढ़ो_setup, (व्योम *) thi,
				    "drbd_%c_%s", thi->name[0], thi->resource->name);

		अगर (IS_ERR(nt)) अणु
			drbd_err(resource, "Couldn't start thread\n");

			अगर (thi->connection)
				kref_put(&thi->connection->kref, drbd_destroy_connection);
			kref_put(&resource->kref, drbd_destroy_resource);
			module_put(THIS_MODULE);
			वापस false;
		पूर्ण
		spin_lock_irqsave(&thi->t_lock, flags);
		thi->task = nt;
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		wake_up_process(nt);
		अवरोध;
	हाल EXITING:
		thi->t_state = RESTARTING;
		drbd_info(resource, "Restarting %s thread (from %s [%d])\n",
				thi->name, current->comm, current->pid);
		fallthrough;
	हाल RUNNING:
	हाल RESTARTING:
	शेष:
		spin_unlock_irqrestore(&thi->t_lock, flags);
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण


व्योम _drbd_thपढ़ो_stop(काष्ठा drbd_thपढ़ो *thi, पूर्णांक restart, पूर्णांक रुको)
अणु
	अचिन्हित दीर्घ flags;

	क्रमागत drbd_thपढ़ो_state ns = restart ? RESTARTING : EXITING;

	/* may be called from state engine, holding the req lock irqsave */
	spin_lock_irqsave(&thi->t_lock, flags);

	अगर (thi->t_state == NONE) अणु
		spin_unlock_irqrestore(&thi->t_lock, flags);
		अगर (restart)
			drbd_thपढ़ो_start(thi);
		वापस;
	पूर्ण

	अगर (thi->t_state != ns) अणु
		अगर (thi->task == शून्य) अणु
			spin_unlock_irqrestore(&thi->t_lock, flags);
			वापस;
		पूर्ण

		thi->t_state = ns;
		smp_mb();
		init_completion(&thi->stop);
		अगर (thi->task != current)
			send_sig(DRBD_SIGKILL, thi->task, 1);
	पूर्ण

	spin_unlock_irqrestore(&thi->t_lock, flags);

	अगर (रुको)
		रुको_क्रम_completion(&thi->stop);
पूर्ण

पूर्णांक conn_lowest_minor(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr = 0, minor = -1;

	rcu_पढ़ो_lock();
	peer_device = idr_get_next(&connection->peer_devices, &vnr);
	अगर (peer_device)
		minor = device_to_minor(peer_device->device);
	rcu_पढ़ो_unlock();

	वापस minor;
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * drbd_calc_cpu_mask() - Generate CPU masks, spपढ़ो over all CPUs
 *
 * Forces all thपढ़ोs of a resource onto the same CPU. This is beneficial क्रम
 * DRBD's performance. May be overwritten by user's configuration.
 */
अटल व्योम drbd_calc_cpu_mask(cpumask_var_t *cpu_mask)
अणु
	अचिन्हित पूर्णांक *resources_per_cpu, min_index = ~0;

	resources_per_cpu = kसुस्मृति(nr_cpu_ids, माप(*resources_per_cpu),
				    GFP_KERNEL);
	अगर (resources_per_cpu) अणु
		काष्ठा drbd_resource *resource;
		अचिन्हित पूर्णांक cpu, min = ~0;

		rcu_पढ़ो_lock();
		क्रम_each_resource_rcu(resource, &drbd_resources) अणु
			क्रम_each_cpu(cpu, resource->cpu_mask)
				resources_per_cpu[cpu]++;
		पूर्ण
		rcu_पढ़ो_unlock();
		क्रम_each_online_cpu(cpu) अणु
			अगर (resources_per_cpu[cpu] < min) अणु
				min = resources_per_cpu[cpu];
				min_index = cpu;
			पूर्ण
		पूर्ण
		kमुक्त(resources_per_cpu);
	पूर्ण
	अगर (min_index == ~0) अणु
		cpumask_setall(*cpu_mask);
		वापस;
	पूर्ण
	cpumask_set_cpu(min_index, *cpu_mask);
पूर्ण

/**
 * drbd_thपढ़ो_current_set_cpu() - modअगरies the cpu mask of the _current_ thपढ़ो
 * @thi:	drbd_thपढ़ो object
 *
 * call in the "main loop" of _all_ thपढ़ोs, no need क्रम any mutex, current won't die
 * prematurely.
 */
व्योम drbd_thपढ़ो_current_set_cpu(काष्ठा drbd_thपढ़ो *thi)
अणु
	काष्ठा drbd_resource *resource = thi->resource;
	काष्ठा task_काष्ठा *p = current;

	अगर (!thi->reset_cpu_mask)
		वापस;
	thi->reset_cpu_mask = 0;
	set_cpus_allowed_ptr(p, resource->cpu_mask);
पूर्ण
#अन्यथा
#घोषणा drbd_calc_cpu_mask(A) (अणुपूर्ण)
#पूर्ण_अगर

/*
 * drbd_header_size  -  size of a packet header
 *
 * The header size is a multiple of 8, so any payload following the header is
 * word aligned on 64-bit architectures.  (The biपंचांगap send and receive code
 * relies on this.)
 */
अचिन्हित पूर्णांक drbd_header_size(काष्ठा drbd_connection *connection)
अणु
	अगर (connection->agreed_pro_version >= 100) अणु
		BUILD_BUG_ON(!IS_ALIGNED(माप(काष्ठा p_header100), 8));
		वापस माप(काष्ठा p_header100);
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON(माप(काष्ठा p_header80) !=
			     माप(काष्ठा p_header95));
		BUILD_BUG_ON(!IS_ALIGNED(माप(काष्ठा p_header80), 8));
		वापस माप(काष्ठा p_header80);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक prepare_header80(काष्ठा p_header80 *h, क्रमागत drbd_packet cmd, पूर्णांक size)
अणु
	h->magic   = cpu_to_be32(DRBD_MAGIC);
	h->command = cpu_to_be16(cmd);
	h->length  = cpu_to_be16(size);
	वापस माप(काष्ठा p_header80);
पूर्ण

अटल अचिन्हित पूर्णांक prepare_header95(काष्ठा p_header95 *h, क्रमागत drbd_packet cmd, पूर्णांक size)
अणु
	h->magic   = cpu_to_be16(DRBD_MAGIC_BIG);
	h->command = cpu_to_be16(cmd);
	h->length = cpu_to_be32(size);
	वापस माप(काष्ठा p_header95);
पूर्ण

अटल अचिन्हित पूर्णांक prepare_header100(काष्ठा p_header100 *h, क्रमागत drbd_packet cmd,
				      पूर्णांक size, पूर्णांक vnr)
अणु
	h->magic = cpu_to_be32(DRBD_MAGIC_100);
	h->volume = cpu_to_be16(vnr);
	h->command = cpu_to_be16(cmd);
	h->length = cpu_to_be32(size);
	h->pad = 0;
	वापस माप(काष्ठा p_header100);
पूर्ण

अटल अचिन्हित पूर्णांक prepare_header(काष्ठा drbd_connection *connection, पूर्णांक vnr,
				   व्योम *buffer, क्रमागत drbd_packet cmd, पूर्णांक size)
अणु
	अगर (connection->agreed_pro_version >= 100)
		वापस prepare_header100(buffer, cmd, size, vnr);
	अन्यथा अगर (connection->agreed_pro_version >= 95 &&
		 size > DRBD_MAX_SIZE_H80_PACKET)
		वापस prepare_header95(buffer, cmd, size);
	अन्यथा
		वापस prepare_header80(buffer, cmd, size);
पूर्ण

अटल व्योम *__conn_prepare_command(काष्ठा drbd_connection *connection,
				    काष्ठा drbd_socket *sock)
अणु
	अगर (!sock->socket)
		वापस शून्य;
	वापस sock->sbuf + drbd_header_size(connection);
पूर्ण

व्योम *conn_prepare_command(काष्ठा drbd_connection *connection, काष्ठा drbd_socket *sock)
अणु
	व्योम *p;

	mutex_lock(&sock->mutex);
	p = __conn_prepare_command(connection, sock);
	अगर (!p)
		mutex_unlock(&sock->mutex);

	वापस p;
पूर्ण

व्योम *drbd_prepare_command(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_socket *sock)
अणु
	वापस conn_prepare_command(peer_device->connection, sock);
पूर्ण

अटल पूर्णांक __send_command(काष्ठा drbd_connection *connection, पूर्णांक vnr,
			  काष्ठा drbd_socket *sock, क्रमागत drbd_packet cmd,
			  अचिन्हित पूर्णांक header_size, व्योम *data,
			  अचिन्हित पूर्णांक size)
अणु
	पूर्णांक msg_flags;
	पूर्णांक err;

	/*
	 * Called with @data == शून्य and the size of the data blocks in @size
	 * क्रम commands that send data blocks.  For those commands, omit the
	 * MSG_MORE flag: this will increase the likelihood that data blocks
	 * which are page aligned on the sender will end up page aligned on the
	 * receiver.
	 */
	msg_flags = data ? MSG_MORE : 0;

	header_size += prepare_header(connection, vnr, sock->sbuf, cmd,
				      header_size + size);
	err = drbd_send_all(connection, sock->socket, sock->sbuf, header_size,
			    msg_flags);
	अगर (data && !err)
		err = drbd_send_all(connection, sock->socket, data, size, 0);
	/* DRBD protocol "pings" are latency critical.
	 * This is supposed to trigger tcp_push_pending_frames() */
	अगर (!err && (cmd == P_PING || cmd == P_PING_ACK))
		tcp_sock_set_nodelay(sock->socket->sk);

	वापस err;
पूर्ण

अटल पूर्णांक __conn_send_command(काष्ठा drbd_connection *connection, काष्ठा drbd_socket *sock,
			       क्रमागत drbd_packet cmd, अचिन्हित पूर्णांक header_size,
			       व्योम *data, अचिन्हित पूर्णांक size)
अणु
	वापस __send_command(connection, 0, sock, cmd, header_size, data, size);
पूर्ण

पूर्णांक conn_send_command(काष्ठा drbd_connection *connection, काष्ठा drbd_socket *sock,
		      क्रमागत drbd_packet cmd, अचिन्हित पूर्णांक header_size,
		      व्योम *data, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	err = __conn_send_command(connection, sock, cmd, header_size, data, size);
	mutex_unlock(&sock->mutex);
	वापस err;
पूर्ण

पूर्णांक drbd_send_command(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_socket *sock,
		      क्रमागत drbd_packet cmd, अचिन्हित पूर्णांक header_size,
		      व्योम *data, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	err = __send_command(peer_device->connection, peer_device->device->vnr,
			     sock, cmd, header_size, data, size);
	mutex_unlock(&sock->mutex);
	वापस err;
पूर्ण

पूर्णांक drbd_send_ping(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_socket *sock;

	sock = &connection->meta;
	अगर (!conn_prepare_command(connection, sock))
		वापस -EIO;
	वापस conn_send_command(connection, sock, P_PING, 0, शून्य, 0);
पूर्ण

पूर्णांक drbd_send_ping_ack(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_socket *sock;

	sock = &connection->meta;
	अगर (!conn_prepare_command(connection, sock))
		वापस -EIO;
	वापस conn_send_command(connection, sock, P_PING_ACK, 0, शून्य, 0);
पूर्ण

पूर्णांक drbd_send_sync_param(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_rs_param_95 *p;
	पूर्णांक size;
	स्थिर पूर्णांक apv = peer_device->connection->agreed_pro_version;
	क्रमागत drbd_packet cmd;
	काष्ठा net_conf *nc;
	काष्ठा disk_conf *dc;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);

	size = apv <= 87 ? माप(काष्ठा p_rs_param)
		: apv == 88 ? माप(काष्ठा p_rs_param)
			+ म_माप(nc->verअगरy_alg) + 1
		: apv <= 94 ? माप(काष्ठा p_rs_param_89)
		: /* apv >= 95 */ माप(काष्ठा p_rs_param_95);

	cmd = apv >= 89 ? P_SYNC_PARAM89 : P_SYNC_PARAM;

	/* initialize verअगरy_alg and csums_alg */
	स_रखो(p->verअगरy_alg, 0, 2 * SHARED_SECRET_MAX);

	अगर (get_ldev(peer_device->device)) अणु
		dc = rcu_dereference(peer_device->device->ldev->disk_conf);
		p->resync_rate = cpu_to_be32(dc->resync_rate);
		p->c_plan_ahead = cpu_to_be32(dc->c_plan_ahead);
		p->c_delay_target = cpu_to_be32(dc->c_delay_target);
		p->c_fill_target = cpu_to_be32(dc->c_fill_target);
		p->c_max_rate = cpu_to_be32(dc->c_max_rate);
		put_ldev(peer_device->device);
	पूर्ण अन्यथा अणु
		p->resync_rate = cpu_to_be32(DRBD_RESYNC_RATE_DEF);
		p->c_plan_ahead = cpu_to_be32(DRBD_C_PLAN_AHEAD_DEF);
		p->c_delay_target = cpu_to_be32(DRBD_C_DELAY_TARGET_DEF);
		p->c_fill_target = cpu_to_be32(DRBD_C_FILL_TARGET_DEF);
		p->c_max_rate = cpu_to_be32(DRBD_C_MAX_RATE_DEF);
	पूर्ण

	अगर (apv >= 88)
		म_नकल(p->verअगरy_alg, nc->verअगरy_alg);
	अगर (apv >= 89)
		म_नकल(p->csums_alg, nc->csums_alg);
	rcu_पढ़ो_unlock();

	वापस drbd_send_command(peer_device, sock, cmd, size, शून्य, 0);
पूर्ण

पूर्णांक __drbd_send_protocol(काष्ठा drbd_connection *connection, क्रमागत drbd_packet cmd)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_protocol *p;
	काष्ठा net_conf *nc;
	पूर्णांक size, cf;

	sock = &connection->data;
	p = __conn_prepare_command(connection, sock);
	अगर (!p)
		वापस -EIO;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);

	अगर (nc->tentative && connection->agreed_pro_version < 92) अणु
		rcu_पढ़ो_unlock();
		drbd_err(connection, "--dry-run is not supported by peer");
		वापस -EOPNOTSUPP;
	पूर्ण

	size = माप(*p);
	अगर (connection->agreed_pro_version >= 87)
		size += म_माप(nc->पूर्णांकegrity_alg) + 1;

	p->protocol      = cpu_to_be32(nc->wire_protocol);
	p->after_sb_0p   = cpu_to_be32(nc->after_sb_0p);
	p->after_sb_1p   = cpu_to_be32(nc->after_sb_1p);
	p->after_sb_2p   = cpu_to_be32(nc->after_sb_2p);
	p->two_primaries = cpu_to_be32(nc->two_primaries);
	cf = 0;
	अगर (nc->discard_my_data)
		cf |= CF_DISCARD_MY_DATA;
	अगर (nc->tentative)
		cf |= CF_DRY_RUN;
	p->conn_flags    = cpu_to_be32(cf);

	अगर (connection->agreed_pro_version >= 87)
		म_नकल(p->पूर्णांकegrity_alg, nc->पूर्णांकegrity_alg);
	rcu_पढ़ो_unlock();

	वापस __conn_send_command(connection, sock, cmd, size, शून्य, 0);
पूर्ण

पूर्णांक drbd_send_protocol(काष्ठा drbd_connection *connection)
अणु
	पूर्णांक err;

	mutex_lock(&connection->data.mutex);
	err = __drbd_send_protocol(connection, P_PROTOCOL);
	mutex_unlock(&connection->data.mutex);

	वापस err;
पूर्ण

अटल पूर्णांक _drbd_send_uuids(काष्ठा drbd_peer_device *peer_device, u64 uuid_flags)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_socket *sock;
	काष्ठा p_uuids *p;
	पूर्णांक i;

	अगर (!get_ldev_अगर_state(device, D_NEGOTIATING))
		वापस 0;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p) अणु
		put_ldev(device);
		वापस -EIO;
	पूर्ण
	spin_lock_irq(&device->ldev->md.uuid_lock);
	क्रम (i = UI_CURRENT; i < UI_SIZE; i++)
		p->uuid[i] = cpu_to_be64(device->ldev->md.uuid[i]);
	spin_unlock_irq(&device->ldev->md.uuid_lock);

	device->comm_bm_set = drbd_bm_total_weight(device);
	p->uuid[UI_SIZE] = cpu_to_be64(device->comm_bm_set);
	rcu_पढ़ो_lock();
	uuid_flags |= rcu_dereference(peer_device->connection->net_conf)->discard_my_data ? 1 : 0;
	rcu_पढ़ो_unlock();
	uuid_flags |= test_bit(CRASHED_PRIMARY, &device->flags) ? 2 : 0;
	uuid_flags |= device->new_state_पंचांगp.disk == D_INCONSISTENT ? 4 : 0;
	p->uuid[UI_FLAGS] = cpu_to_be64(uuid_flags);

	put_ldev(device);
	वापस drbd_send_command(peer_device, sock, P_UUIDS, माप(*p), शून्य, 0);
पूर्ण

पूर्णांक drbd_send_uuids(काष्ठा drbd_peer_device *peer_device)
अणु
	वापस _drbd_send_uuids(peer_device, 0);
पूर्ण

पूर्णांक drbd_send_uuids_skip_initial_sync(काष्ठा drbd_peer_device *peer_device)
अणु
	वापस _drbd_send_uuids(peer_device, 8);
पूर्ण

व्योम drbd_prपूर्णांक_uuids(काष्ठा drbd_device *device, स्थिर अक्षर *text)
अणु
	अगर (get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		u64 *uuid = device->ldev->md.uuid;
		drbd_info(device, "%s %016llX:%016llX:%016llX:%016llX\n",
		     text,
		     (अचिन्हित दीर्घ दीर्घ)uuid[UI_CURRENT],
		     (अचिन्हित दीर्घ दीर्घ)uuid[UI_BITMAP],
		     (अचिन्हित दीर्घ दीर्घ)uuid[UI_HISTORY_START],
		     (अचिन्हित दीर्घ दीर्घ)uuid[UI_HISTORY_END]);
		put_ldev(device);
	पूर्ण अन्यथा अणु
		drbd_info(device, "%s effective data uuid: %016llX\n",
				text,
				(अचिन्हित दीर्घ दीर्घ)device->ed_uuid);
	पूर्ण
पूर्ण

व्योम drbd_gen_and_send_sync_uuid(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_socket *sock;
	काष्ठा p_rs_uuid *p;
	u64 uuid;

	D_ASSERT(device, device->state.disk == D_UP_TO_DATE);

	uuid = device->ldev->md.uuid[UI_BITMAP];
	अगर (uuid && uuid != UUID_JUST_CREATED)
		uuid = uuid + UUID_NEW_BM_OFFSET;
	अन्यथा
		get_अक्रमom_bytes(&uuid, माप(u64));
	drbd_uuid_set(device, UI_BITMAP, uuid);
	drbd_prपूर्णांक_uuids(device, "updated sync UUID");
	drbd_md_sync(device);

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (p) अणु
		p->uuid = cpu_to_be64(uuid);
		drbd_send_command(peer_device, sock, P_SYNC_UUID, माप(*p), शून्य, 0);
	पूर्ण
पूर्ण

/* communicated अगर (agreed_features & DRBD_FF_WSAME) */
अटल व्योम
assign_p_sizes_qlim(काष्ठा drbd_device *device, काष्ठा p_sizes *p,
					काष्ठा request_queue *q)
अणु
	अगर (q) अणु
		p->qlim->physical_block_size = cpu_to_be32(queue_physical_block_size(q));
		p->qlim->logical_block_size = cpu_to_be32(queue_logical_block_size(q));
		p->qlim->alignment_offset = cpu_to_be32(queue_alignment_offset(q));
		p->qlim->io_min = cpu_to_be32(queue_io_min(q));
		p->qlim->io_opt = cpu_to_be32(queue_io_opt(q));
		p->qlim->discard_enabled = blk_queue_discard(q);
		p->qlim->ग_लिखो_same_capable = !!q->limits.max_ग_लिखो_same_sectors;
	पूर्ण अन्यथा अणु
		q = device->rq_queue;
		p->qlim->physical_block_size = cpu_to_be32(queue_physical_block_size(q));
		p->qlim->logical_block_size = cpu_to_be32(queue_logical_block_size(q));
		p->qlim->alignment_offset = 0;
		p->qlim->io_min = cpu_to_be32(queue_io_min(q));
		p->qlim->io_opt = cpu_to_be32(queue_io_opt(q));
		p->qlim->discard_enabled = 0;
		p->qlim->ग_लिखो_same_capable = 0;
	पूर्ण
पूर्ण

पूर्णांक drbd_send_sizes(काष्ठा drbd_peer_device *peer_device, पूर्णांक trigger_reply, क्रमागत dds_flags flags)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_socket *sock;
	काष्ठा p_sizes *p;
	sector_t d_size, u_size;
	पूर्णांक q_order_type;
	अचिन्हित पूर्णांक max_bio_size;
	अचिन्हित पूर्णांक packet_size;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;

	packet_size = माप(*p);
	अगर (peer_device->connection->agreed_features & DRBD_FF_WSAME)
		packet_size += माप(p->qlim[0]);

	स_रखो(p, 0, packet_size);
	अगर (get_ldev_अगर_state(device, D_NEGOTIATING)) अणु
		काष्ठा request_queue *q = bdev_get_queue(device->ldev->backing_bdev);
		d_size = drbd_get_max_capacity(device->ldev);
		rcu_पढ़ो_lock();
		u_size = rcu_dereference(device->ldev->disk_conf)->disk_size;
		rcu_पढ़ो_unlock();
		q_order_type = drbd_queue_order_type(device);
		max_bio_size = queue_max_hw_sectors(q) << 9;
		max_bio_size = min(max_bio_size, DRBD_MAX_BIO_SIZE);
		assign_p_sizes_qlim(device, p, q);
		put_ldev(device);
	पूर्ण अन्यथा अणु
		d_size = 0;
		u_size = 0;
		q_order_type = QUEUE_ORDERED_NONE;
		max_bio_size = DRBD_MAX_BIO_SIZE; /* ... multiple BIOs per peer_request */
		assign_p_sizes_qlim(device, p, शून्य);
	पूर्ण

	अगर (peer_device->connection->agreed_pro_version <= 94)
		max_bio_size = min(max_bio_size, DRBD_MAX_SIZE_H80_PACKET);
	अन्यथा अगर (peer_device->connection->agreed_pro_version < 100)
		max_bio_size = min(max_bio_size, DRBD_MAX_BIO_SIZE_P95);

	p->d_size = cpu_to_be64(d_size);
	p->u_size = cpu_to_be64(u_size);
	अगर (trigger_reply)
		p->c_size = 0;
	अन्यथा
		p->c_size = cpu_to_be64(get_capacity(device->vdisk));
	p->max_bio_size = cpu_to_be32(max_bio_size);
	p->queue_order_type = cpu_to_be16(q_order_type);
	p->dds_flags = cpu_to_be16(flags);

	वापस drbd_send_command(peer_device, sock, P_SIZES, packet_size, शून्य, 0);
पूर्ण

/**
 * drbd_send_current_state() - Sends the drbd state to the peer
 * @peer_device:	DRBD peer device.
 */
पूर्णांक drbd_send_current_state(काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_state *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->state = cpu_to_be32(peer_device->device->state.i); /* Within the send mutex */
	वापस drbd_send_command(peer_device, sock, P_STATE, माप(*p), शून्य, 0);
पूर्ण

/**
 * drbd_send_state() - After a state change, sends the new state to the peer
 * @peer_device:      DRBD peer device.
 * @state:     the state to send, not necessarily the current state.
 *
 * Each state change queues an "after_state_ch" work, which will eventually
 * send the resulting new state to the peer. If more state changes happen
 * between queuing and processing of the after_state_ch work, we still
 * want to send each पूर्णांकermediary state in the order it occurred.
 */
पूर्णांक drbd_send_state(काष्ठा drbd_peer_device *peer_device, जोड़ drbd_state state)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_state *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->state = cpu_to_be32(state.i); /* Within the send mutex */
	वापस drbd_send_command(peer_device, sock, P_STATE, माप(*p), शून्य, 0);
पूर्ण

पूर्णांक drbd_send_state_req(काष्ठा drbd_peer_device *peer_device, जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_req_state *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->mask = cpu_to_be32(mask.i);
	p->val = cpu_to_be32(val.i);
	वापस drbd_send_command(peer_device, sock, P_STATE_CHG_REQ, माप(*p), शून्य, 0);
पूर्ण

पूर्णांक conn_send_state_req(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	क्रमागत drbd_packet cmd;
	काष्ठा drbd_socket *sock;
	काष्ठा p_req_state *p;

	cmd = connection->agreed_pro_version < 100 ? P_STATE_CHG_REQ : P_CONN_ST_CHG_REQ;
	sock = &connection->data;
	p = conn_prepare_command(connection, sock);
	अगर (!p)
		वापस -EIO;
	p->mask = cpu_to_be32(mask.i);
	p->val = cpu_to_be32(val.i);
	वापस conn_send_command(connection, sock, cmd, माप(*p), शून्य, 0);
पूर्ण

व्योम drbd_send_sr_reply(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_state_rv retcode)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_req_state_reply *p;

	sock = &peer_device->connection->meta;
	p = drbd_prepare_command(peer_device, sock);
	अगर (p) अणु
		p->retcode = cpu_to_be32(retcode);
		drbd_send_command(peer_device, sock, P_STATE_CHG_REPLY, माप(*p), शून्य, 0);
	पूर्ण
पूर्ण

व्योम conn_send_sr_reply(काष्ठा drbd_connection *connection, क्रमागत drbd_state_rv retcode)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_req_state_reply *p;
	क्रमागत drbd_packet cmd = connection->agreed_pro_version < 100 ? P_STATE_CHG_REPLY : P_CONN_ST_CHG_REPLY;

	sock = &connection->meta;
	p = conn_prepare_command(connection, sock);
	अगर (p) अणु
		p->retcode = cpu_to_be32(retcode);
		conn_send_command(connection, sock, cmd, माप(*p), शून्य, 0);
	पूर्ण
पूर्ण

अटल व्योम dcbp_set_code(काष्ठा p_compressed_bm *p, क्रमागत drbd_biपंचांगap_code code)
अणु
	BUG_ON(code & ~0xf);
	p->encoding = (p->encoding & ~0xf) | code;
पूर्ण

अटल व्योम dcbp_set_start(काष्ठा p_compressed_bm *p, पूर्णांक set)
अणु
	p->encoding = (p->encoding & ~0x80) | (set ? 0x80 : 0);
पूर्ण

अटल व्योम dcbp_set_pad_bits(काष्ठा p_compressed_bm *p, पूर्णांक n)
अणु
	BUG_ON(n & ~0x7);
	p->encoding = (p->encoding & (~0x7 << 4)) | (n << 4);
पूर्ण

अटल पूर्णांक fill_biपंचांगap_rle_bits(काष्ठा drbd_device *device,
			 काष्ठा p_compressed_bm *p,
			 अचिन्हित पूर्णांक size,
			 काष्ठा bm_xfer_ctx *c)
अणु
	काष्ठा bitstream bs;
	अचिन्हित दीर्घ plain_bits;
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित दीर्घ rl;
	अचिन्हित len;
	अचिन्हित toggle;
	पूर्णांक bits, use_rle;

	/* may we use this feature? */
	rcu_पढ़ो_lock();
	use_rle = rcu_dereference(first_peer_device(device)->connection->net_conf)->use_rle;
	rcu_पढ़ो_unlock();
	अगर (!use_rle || first_peer_device(device)->connection->agreed_pro_version < 90)
		वापस 0;

	अगर (c->bit_offset >= c->bm_bits)
		वापस 0; /* nothing to करो. */

	/* use at most thus many bytes */
	bitstream_init(&bs, p->code, size, 0);
	स_रखो(p->code, 0, size);
	/* plain bits covered in this code string */
	plain_bits = 0;

	/* p->encoding & 0x80 stores whether the first run length is set.
	 * bit offset is implicit.
	 * start with toggle == 2 to be able to tell the first iteration */
	toggle = 2;

	/* see how much plain bits we can stuff पूर्णांकo one packet
	 * using RLE and VLI. */
	करो अणु
		पंचांगp = (toggle == 0) ? _drbd_bm_find_next_zero(device, c->bit_offset)
				    : _drbd_bm_find_next(device, c->bit_offset);
		अगर (पंचांगp == -1UL)
			पंचांगp = c->bm_bits;
		rl = पंचांगp - c->bit_offset;

		अगर (toggle == 2) अणु /* first iteration */
			अगर (rl == 0) अणु
				/* the first checked bit was set,
				 * store start value, */
				dcbp_set_start(p, 1);
				/* but skip encoding of zero run length */
				toggle = !toggle;
				जारी;
			पूर्ण
			dcbp_set_start(p, 0);
		पूर्ण

		/* paranoia: catch zero runlength.
		 * can only happen अगर biपंचांगap is modअगरied जबतक we scan it. */
		अगर (rl == 0) अणु
			drbd_err(device, "unexpected zero runlength while encoding bitmap "
			    "t:%u bo:%lu\n", toggle, c->bit_offset);
			वापस -1;
		पूर्ण

		bits = vli_encode_bits(&bs, rl);
		अगर (bits == -ENOBUFS) /* buffer full */
			अवरोध;
		अगर (bits <= 0) अणु
			drbd_err(device, "error while encoding bitmap: %d\n", bits);
			वापस 0;
		पूर्ण

		toggle = !toggle;
		plain_bits += rl;
		c->bit_offset = पंचांगp;
	पूर्ण जबतक (c->bit_offset < c->bm_bits);

	len = bs.cur.b - p->code + !!bs.cur.bit;

	अगर (plain_bits < (len << 3)) अणु
		/* incompressible with this method.
		 * we need to शुरुआत both word and bit position. */
		c->bit_offset -= plain_bits;
		bm_xfer_ctx_bit_to_word_offset(c);
		c->bit_offset = c->word_offset * BITS_PER_LONG;
		वापस 0;
	पूर्ण

	/* RLE + VLI was able to compress it just fine.
	 * update c->word_offset. */
	bm_xfer_ctx_bit_to_word_offset(c);

	/* store pad_bits */
	dcbp_set_pad_bits(p, (8 - bs.cur.bit) & 0x7);

	वापस len;
पूर्ण

/*
 * send_biपंचांगap_rle_or_plain
 *
 * Return 0 when करोne, 1 when another iteration is needed, and a negative error
 * code upon failure.
 */
अटल पूर्णांक
send_biपंचांगap_rle_or_plain(काष्ठा drbd_device *device, काष्ठा bm_xfer_ctx *c)
अणु
	काष्ठा drbd_socket *sock = &first_peer_device(device)->connection->data;
	अचिन्हित पूर्णांक header_size = drbd_header_size(first_peer_device(device)->connection);
	काष्ठा p_compressed_bm *p = sock->sbuf + header_size;
	पूर्णांक len, err;

	len = fill_biपंचांगap_rle_bits(device, p,
			DRBD_SOCKET_BUFFER_SIZE - header_size - माप(*p), c);
	अगर (len < 0)
		वापस -EIO;

	अगर (len) अणु
		dcbp_set_code(p, RLE_VLI_Bits);
		err = __send_command(first_peer_device(device)->connection, device->vnr, sock,
				     P_COMPRESSED_BITMAP, माप(*p) + len,
				     शून्य, 0);
		c->packets[0]++;
		c->bytes[0] += header_size + माप(*p) + len;

		अगर (c->bit_offset >= c->bm_bits)
			len = 0; /* DONE */
	पूर्ण अन्यथा अणु
		/* was not compressible.
		 * send a buffer full of plain text bits instead. */
		अचिन्हित पूर्णांक data_size;
		अचिन्हित दीर्घ num_words;
		अचिन्हित दीर्घ *p = sock->sbuf + header_size;

		data_size = DRBD_SOCKET_BUFFER_SIZE - header_size;
		num_words = min_t(माप_प्रकार, data_size / माप(*p),
				  c->bm_words - c->word_offset);
		len = num_words * माप(*p);
		अगर (len)
			drbd_bm_get_lel(device, c->word_offset, num_words, p);
		err = __send_command(first_peer_device(device)->connection, device->vnr, sock, P_BITMAP, len, शून्य, 0);
		c->word_offset += num_words;
		c->bit_offset = c->word_offset * BITS_PER_LONG;

		c->packets[1]++;
		c->bytes[1] += header_size + len;

		अगर (c->bit_offset > c->bm_bits)
			c->bit_offset = c->bm_bits;
	पूर्ण
	अगर (!err) अणु
		अगर (len == 0) अणु
			INFO_bm_xfer_stats(device, "send", c);
			वापस 0;
		पूर्ण अन्यथा
			वापस 1;
	पूर्ण
	वापस -EIO;
पूर्ण

/* See the comment at receive_biपंचांगap() */
अटल पूर्णांक _drbd_send_biपंचांगap(काष्ठा drbd_device *device)
अणु
	काष्ठा bm_xfer_ctx c;
	पूर्णांक err;

	अगर (!expect(device->biपंचांगap))
		वापस false;

	अगर (get_ldev(device)) अणु
		अगर (drbd_md_test_flag(device->ldev, MDF_FULL_SYNC)) अणु
			drbd_info(device, "Writing the whole bitmap, MDF_FullSync was set.\n");
			drbd_bm_set_all(device);
			अगर (drbd_bm_ग_लिखो(device)) अणु
				/* ग_लिखो_bm did fail! Leave full sync flag set in Meta P_DATA
				 * but otherwise process as per normal - need to tell other
				 * side that a full resync is required! */
				drbd_err(device, "Failed to write bitmap to disk!\n");
			पूर्ण अन्यथा अणु
				drbd_md_clear_flag(device, MDF_FULL_SYNC);
				drbd_md_sync(device);
			पूर्ण
		पूर्ण
		put_ldev(device);
	पूर्ण

	c = (काष्ठा bm_xfer_ctx) अणु
		.bm_bits = drbd_bm_bits(device),
		.bm_words = drbd_bm_words(device),
	पूर्ण;

	करो अणु
		err = send_biपंचांगap_rle_or_plain(device, &c);
	पूर्ण जबतक (err > 0);

	वापस err == 0;
पूर्ण

पूर्णांक drbd_send_biपंचांगap(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_socket *sock = &first_peer_device(device)->connection->data;
	पूर्णांक err = -1;

	mutex_lock(&sock->mutex);
	अगर (sock->socket)
		err = !_drbd_send_biपंचांगap(device);
	mutex_unlock(&sock->mutex);
	वापस err;
पूर्ण

व्योम drbd_send_b_ack(काष्ठा drbd_connection *connection, u32 barrier_nr, u32 set_size)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_barrier_ack *p;

	अगर (connection->cstate < C_WF_REPORT_PARAMS)
		वापस;

	sock = &connection->meta;
	p = conn_prepare_command(connection, sock);
	अगर (!p)
		वापस;
	p->barrier = barrier_nr;
	p->set_size = cpu_to_be32(set_size);
	conn_send_command(connection, sock, P_BARRIER_ACK, माप(*p), शून्य, 0);
पूर्ण

/**
 * _drbd_send_ack() - Sends an ack packet
 * @peer_device:	DRBD peer device.
 * @cmd:		Packet command code.
 * @sector:		sector, needs to be in big endian byte order
 * @blksize:		size in byte, needs to be in big endian byte order
 * @block_id:		Id, big endian byte order
 */
अटल पूर्णांक _drbd_send_ack(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
			  u64 sector, u32 blksize, u64 block_id)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_ack *p;

	अगर (peer_device->device->state.conn < C_CONNECTED)
		वापस -EIO;

	sock = &peer_device->connection->meta;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = sector;
	p->block_id = block_id;
	p->blksize = blksize;
	p->seq_num = cpu_to_be32(atomic_inc_वापस(&peer_device->device->packet_seq));
	वापस drbd_send_command(peer_device, sock, cmd, माप(*p), शून्य, 0);
पूर्ण

/* dp->sector and dp->block_id alपढ़ोy/still in network byte order,
 * data_size is payload size according to dp->head,
 * and may need to be corrected क्रम digest size. */
व्योम drbd_send_ack_dp(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
		      काष्ठा p_data *dp, पूर्णांक data_size)
अणु
	अगर (peer_device->connection->peer_पूर्णांकegrity_tfm)
		data_size -= crypto_shash_digestsize(peer_device->connection->peer_पूर्णांकegrity_tfm);
	_drbd_send_ack(peer_device, cmd, dp->sector, cpu_to_be32(data_size),
		       dp->block_id);
पूर्ण

व्योम drbd_send_ack_rp(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
		      काष्ठा p_block_req *rp)
अणु
	_drbd_send_ack(peer_device, cmd, rp->sector, rp->blksize, rp->block_id);
पूर्ण

/**
 * drbd_send_ack() - Sends an ack packet
 * @peer_device:	DRBD peer device
 * @cmd:		packet command code
 * @peer_req:		peer request
 */
पूर्णांक drbd_send_ack(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
		  काष्ठा drbd_peer_request *peer_req)
अणु
	वापस _drbd_send_ack(peer_device, cmd,
			      cpu_to_be64(peer_req->i.sector),
			      cpu_to_be32(peer_req->i.size),
			      peer_req->block_id);
पूर्ण

/* This function misuses the block_id field to संकेत अगर the blocks
 * are is sync or not. */
पूर्णांक drbd_send_ack_ex(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
		     sector_t sector, पूर्णांक blksize, u64 block_id)
अणु
	वापस _drbd_send_ack(peer_device, cmd,
			      cpu_to_be64(sector),
			      cpu_to_be32(blksize),
			      cpu_to_be64(block_id));
पूर्ण

पूर्णांक drbd_send_rs_deallocated(काष्ठा drbd_peer_device *peer_device,
			     काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_desc *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(peer_req->i.sector);
	p->blksize = cpu_to_be32(peer_req->i.size);
	p->pad = 0;
	वापस drbd_send_command(peer_device, sock, P_RS_DEALLOCATED, माप(*p), शून्य, 0);
पूर्ण

पूर्णांक drbd_send_drequest(काष्ठा drbd_peer_device *peer_device, पूर्णांक cmd,
		       sector_t sector, पूर्णांक size, u64 block_id)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_req *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(sector);
	p->block_id = block_id;
	p->blksize = cpu_to_be32(size);
	वापस drbd_send_command(peer_device, sock, cmd, माप(*p), शून्य, 0);
पूर्ण

पूर्णांक drbd_send_drequest_csum(काष्ठा drbd_peer_device *peer_device, sector_t sector, पूर्णांक size,
			    व्योम *digest, पूर्णांक digest_size, क्रमागत drbd_packet cmd)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_req *p;

	/* FIXME: Put the digest पूर्णांकo the pपुनः_स्मृतिated socket buffer.  */

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(sector);
	p->block_id = ID_SYNCER /* unused */;
	p->blksize = cpu_to_be32(size);
	वापस drbd_send_command(peer_device, sock, cmd, माप(*p), digest, digest_size);
पूर्ण

पूर्णांक drbd_send_ov_request(काष्ठा drbd_peer_device *peer_device, sector_t sector, पूर्णांक size)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_req *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(sector);
	p->block_id = ID_SYNCER /* unused */;
	p->blksize = cpu_to_be32(size);
	वापस drbd_send_command(peer_device, sock, P_OV_REQUEST, माप(*p), शून्य, 0);
पूर्ण

/* called on sndसमयo
 * वापसs false अगर we should retry,
 * true अगर we think connection is dead
 */
अटल पूर्णांक we_should_drop_the_connection(काष्ठा drbd_connection *connection, काष्ठा socket *sock)
अणु
	पूर्णांक drop_it;
	/* दीर्घ elapsed = (दीर्घ)(jअगरfies - device->last_received); */

	drop_it =   connection->meta.socket == sock
		|| !connection->ack_receiver.task
		|| get_t_state(&connection->ack_receiver) != RUNNING
		|| connection->cstate < C_WF_REPORT_PARAMS;

	अगर (drop_it)
		वापस true;

	drop_it = !--connection->ko_count;
	अगर (!drop_it) अणु
		drbd_err(connection, "[%s/%d] sock_sendmsg time expired, ko = %u\n",
			 current->comm, current->pid, connection->ko_count);
		request_ping(connection);
	पूर्ण

	वापस drop_it; /* && (device->state == R_PRIMARY) */;
पूर्ण

अटल व्योम drbd_update_congested(काष्ठा drbd_connection *connection)
अणु
	काष्ठा sock *sk = connection->data.socket->sk;
	अगर (sk->sk_wmem_queued > sk->sk_sndbuf * 4 / 5)
		set_bit(NET_CONGESTED, &connection->flags);
पूर्ण

/* The idea of sendpage seems to be to put some kind of reference
 * to the page पूर्णांकo the skb, and to hand it over to the NIC. In
 * this process get_page() माला_लो called.
 *
 * As soon as the page was really sent over the network put_page()
 * माला_लो called by some part of the network layer. [ NIC driver? ]
 *
 * [ get_page() / put_page() increment/decrement the count. If count
 *   reaches 0 the page will be मुक्तd. ]
 *
 * This works nicely with pages from FSs.
 * But this means that in protocol A we might संकेत IO completion too early!
 *
 * In order not to corrupt data during a resync we must make sure
 * that we करो not reuse our own buffer pages (EEs) to early, thereक्रमe
 * we have the net_ee list.
 *
 * XFS seems to have problems, still, it submits pages with page_count == 0!
 * As a workaround, we disable sendpage on pages
 * with page_count == 0 or PageSlab.
 */
अटल पूर्णांक _drbd_no_send_page(काष्ठा drbd_peer_device *peer_device, काष्ठा page *page,
			      पूर्णांक offset, माप_प्रकार size, अचिन्हित msg_flags)
अणु
	काष्ठा socket *socket;
	व्योम *addr;
	पूर्णांक err;

	socket = peer_device->connection->data.socket;
	addr = kmap(page) + offset;
	err = drbd_send_all(peer_device->connection, socket, addr, size, msg_flags);
	kunmap(page);
	अगर (!err)
		peer_device->device->send_cnt += size >> 9;
	वापस err;
पूर्ण

अटल पूर्णांक _drbd_send_page(काष्ठा drbd_peer_device *peer_device, काष्ठा page *page,
		    पूर्णांक offset, माप_प्रकार size, अचिन्हित msg_flags)
अणु
	काष्ठा socket *socket = peer_device->connection->data.socket;
	पूर्णांक len = size;
	पूर्णांक err = -EIO;

	/* e.g. XFS meta- & log-data is in slab pages, which have a
	 * page_count of 0 and/or have PageSlab() set.
	 * we cannot use send_page क्रम those, as that करोes get_page();
	 * put_page(); and would cause either a VM_BUG directly, or
	 * __page_cache_release a page that would actually still be referenced
	 * by someone, leading to some obscure delayed Oops somewhere अन्यथा. */
	अगर (drbd_disable_sendpage || !sendpage_ok(page))
		वापस _drbd_no_send_page(peer_device, page, offset, size, msg_flags);

	msg_flags |= MSG_NOSIGNAL;
	drbd_update_congested(peer_device->connection);
	करो अणु
		पूर्णांक sent;

		sent = socket->ops->sendpage(socket, page, offset, len, msg_flags);
		अगर (sent <= 0) अणु
			अगर (sent == -EAGAIN) अणु
				अगर (we_should_drop_the_connection(peer_device->connection, socket))
					अवरोध;
				जारी;
			पूर्ण
			drbd_warn(peer_device->device, "%s: size=%d len=%d sent=%d\n",
			     __func__, (पूर्णांक)size, len, sent);
			अगर (sent < 0)
				err = sent;
			अवरोध;
		पूर्ण
		len    -= sent;
		offset += sent;
	पूर्ण जबतक (len > 0 /* THINK && device->cstate >= C_CONNECTED*/);
	clear_bit(NET_CONGESTED, &peer_device->connection->flags);

	अगर (len == 0) अणु
		err = 0;
		peer_device->device->send_cnt += size >> 9;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक _drbd_send_bio(काष्ठा drbd_peer_device *peer_device, काष्ठा bio *bio)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;

	/* hपूर्णांक all but last page with MSG_MORE */
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		पूर्णांक err;

		err = _drbd_no_send_page(peer_device, bvec.bv_page,
					 bvec.bv_offset, bvec.bv_len,
					 bio_iter_last(bvec, iter)
					 ? 0 : MSG_MORE);
		अगर (err)
			वापस err;
		/* REQ_OP_WRITE_SAME has only one segment */
		अगर (bio_op(bio) == REQ_OP_WRITE_SAME)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _drbd_send_zc_bio(काष्ठा drbd_peer_device *peer_device, काष्ठा bio *bio)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;

	/* hपूर्णांक all but last page with MSG_MORE */
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		पूर्णांक err;

		err = _drbd_send_page(peer_device, bvec.bv_page,
				      bvec.bv_offset, bvec.bv_len,
				      bio_iter_last(bvec, iter) ? 0 : MSG_MORE);
		अगर (err)
			वापस err;
		/* REQ_OP_WRITE_SAME has only one segment */
		अगर (bio_op(bio) == REQ_OP_WRITE_SAME)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _drbd_send_zc_ee(काष्ठा drbd_peer_device *peer_device,
			    काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा page *page = peer_req->pages;
	अचिन्हित len = peer_req->i.size;
	पूर्णांक err;

	/* hपूर्णांक all but last page with MSG_MORE */
	page_chain_क्रम_each(page) अणु
		अचिन्हित l = min_t(अचिन्हित, len, PAGE_SIZE);

		err = _drbd_send_page(peer_device, page, 0, l,
				      page_chain_next(page) ? MSG_MORE : 0);
		अगर (err)
			वापस err;
		len -= l;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 bio_flags_to_wire(काष्ठा drbd_connection *connection,
			     काष्ठा bio *bio)
अणु
	अगर (connection->agreed_pro_version >= 95)
		वापस  (bio->bi_opf & REQ_SYNC ? DP_RW_SYNC : 0) |
			(bio->bi_opf & REQ_FUA ? DP_FUA : 0) |
			(bio->bi_opf & REQ_PREFLUSH ? DP_FLUSH : 0) |
			(bio_op(bio) == REQ_OP_WRITE_SAME ? DP_WSAME : 0) |
			(bio_op(bio) == REQ_OP_DISCARD ? DP_DISCARD : 0) |
			(bio_op(bio) == REQ_OP_WRITE_ZEROES ?
			  ((connection->agreed_features & DRBD_FF_WZEROES) ?
			   (DP_ZEROES |(!(bio->bi_opf & REQ_NOUNMAP) ? DP_DISCARD : 0))
			   : DP_DISCARD)
			: 0);
	अन्यथा
		वापस bio->bi_opf & REQ_SYNC ? DP_RW_SYNC : 0;
पूर्ण

/* Used to send ग_लिखो or TRIM aka REQ_OP_DISCARD requests
 * R_PRIMARY -> Peer	(P_DATA, P_TRIM)
 */
पूर्णांक drbd_send_dblock(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_socket *sock;
	काष्ठा p_data *p;
	काष्ठा p_wsame *wsame = शून्य;
	व्योम *digest_out;
	अचिन्हित पूर्णांक dp_flags = 0;
	पूर्णांक digest_size;
	पूर्णांक err;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	digest_size = peer_device->connection->पूर्णांकegrity_tfm ?
		      crypto_shash_digestsize(peer_device->connection->पूर्णांकegrity_tfm) : 0;

	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(req->i.sector);
	p->block_id = (अचिन्हित दीर्घ)req;
	p->seq_num = cpu_to_be32(atomic_inc_वापस(&device->packet_seq));
	dp_flags = bio_flags_to_wire(peer_device->connection, req->master_bio);
	अगर (device->state.conn >= C_SYNC_SOURCE &&
	    device->state.conn <= C_PAUSED_SYNC_T)
		dp_flags |= DP_MAY_SET_IN_SYNC;
	अगर (peer_device->connection->agreed_pro_version >= 100) अणु
		अगर (req->rq_state & RQ_EXP_RECEIVE_ACK)
			dp_flags |= DP_SEND_RECEIVE_ACK;
		/* During resync, request an explicit ग_लिखो ack,
		 * even in protocol != C */
		अगर (req->rq_state & RQ_EXP_WRITE_ACK
		|| (dp_flags & DP_MAY_SET_IN_SYNC))
			dp_flags |= DP_SEND_WRITE_ACK;
	पूर्ण
	p->dp_flags = cpu_to_be32(dp_flags);

	अगर (dp_flags & (DP_DISCARD|DP_ZEROES)) अणु
		क्रमागत drbd_packet cmd = (dp_flags & DP_ZEROES) ? P_ZEROES : P_TRIM;
		काष्ठा p_trim *t = (काष्ठा p_trim*)p;
		t->size = cpu_to_be32(req->i.size);
		err = __send_command(peer_device->connection, device->vnr, sock, cmd, माप(*t), शून्य, 0);
		जाओ out;
	पूर्ण
	अगर (dp_flags & DP_WSAME) अणु
		/* this will only work अगर DRBD_FF_WSAME is set AND the
		 * handshake agreed that all nodes and backend devices are
		 * WRITE_SAME capable and agree on logical_block_size */
		wsame = (काष्ठा p_wsame*)p;
		digest_out = wsame + 1;
		wsame->size = cpu_to_be32(req->i.size);
	पूर्ण अन्यथा
		digest_out = p + 1;

	/* our digest is still only over the payload.
	 * TRIM करोes not carry any payload. */
	अगर (digest_size)
		drbd_csum_bio(peer_device->connection->पूर्णांकegrity_tfm, req->master_bio, digest_out);
	अगर (wsame) अणु
		err =
		    __send_command(peer_device->connection, device->vnr, sock, P_WSAME,
				   माप(*wsame) + digest_size, शून्य,
				   bio_iovec(req->master_bio).bv_len);
	पूर्ण अन्यथा
		err =
		    __send_command(peer_device->connection, device->vnr, sock, P_DATA,
				   माप(*p) + digest_size, शून्य, req->i.size);
	अगर (!err) अणु
		/* For protocol A, we have to स_नकल the payload पूर्णांकo
		 * socket buffers, as we may complete right away
		 * as soon as we handed it over to tcp, at which poपूर्णांक the data
		 * pages may become invalid.
		 *
		 * For data-पूर्णांकegrity enabled, we copy it as well, so we can be
		 * sure that even अगर the bio pages may still be modअगरied, it
		 * won't change the data on the wire, thus अगर the digest checks
		 * out ok after sending on this side, but करोes not fit on the
		 * receiving side, we sure have detected corruption अन्यथाwhere.
		 */
		अगर (!(req->rq_state & (RQ_EXP_RECEIVE_ACK | RQ_EXP_WRITE_ACK)) || digest_size)
			err = _drbd_send_bio(peer_device, req->master_bio);
		अन्यथा
			err = _drbd_send_zc_bio(peer_device, req->master_bio);

		/* द्विगुन check digest, someबार buffers have been modअगरied in flight. */
		अगर (digest_size > 0 && digest_size <= 64) अणु
			/* 64 byte, 512 bit, is the largest digest size
			 * currently supported in kernel crypto. */
			अचिन्हित अक्षर digest[64];
			drbd_csum_bio(peer_device->connection->पूर्णांकegrity_tfm, req->master_bio, digest);
			अगर (स_भेद(p + 1, digest, digest_size)) अणु
				drbd_warn(device,
					"Digest mismatch, buffer modified by upper layers during write: %llus +%u\n",
					(अचिन्हित दीर्घ दीर्घ)req->i.sector, req->i.size);
			पूर्ण
		पूर्ण /* अन्यथा अगर (digest_size > 64) अणु
		     ... Be noisy about digest too large ...
		पूर्ण */
	पूर्ण
out:
	mutex_unlock(&sock->mutex);  /* locked by drbd_prepare_command() */

	वापस err;
पूर्ण

/* answer packet, used to send data back क्रम पढ़ो requests:
 *  Peer       -> (diskless) R_PRIMARY   (P_DATA_REPLY)
 *  C_SYNC_SOURCE -> C_SYNC_TARGET         (P_RS_DATA_REPLY)
 */
पूर्णांक drbd_send_block(काष्ठा drbd_peer_device *peer_device, क्रमागत drbd_packet cmd,
		    काष्ठा drbd_peer_request *peer_req)
अणु
	काष्ठा drbd_device *device = peer_device->device;
	काष्ठा drbd_socket *sock;
	काष्ठा p_data *p;
	पूर्णांक err;
	पूर्णांक digest_size;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);

	digest_size = peer_device->connection->पूर्णांकegrity_tfm ?
		      crypto_shash_digestsize(peer_device->connection->पूर्णांकegrity_tfm) : 0;

	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(peer_req->i.sector);
	p->block_id = peer_req->block_id;
	p->seq_num = 0;  /* unused */
	p->dp_flags = 0;
	अगर (digest_size)
		drbd_csum_ee(peer_device->connection->पूर्णांकegrity_tfm, peer_req, p + 1);
	err = __send_command(peer_device->connection, device->vnr, sock, cmd, माप(*p) + digest_size, शून्य, peer_req->i.size);
	अगर (!err)
		err = _drbd_send_zc_ee(peer_device, peer_req);
	mutex_unlock(&sock->mutex);  /* locked by drbd_prepare_command() */

	वापस err;
पूर्ण

पूर्णांक drbd_send_out_of_sync(काष्ठा drbd_peer_device *peer_device, काष्ठा drbd_request *req)
अणु
	काष्ठा drbd_socket *sock;
	काष्ठा p_block_desc *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	अगर (!p)
		वापस -EIO;
	p->sector = cpu_to_be64(req->i.sector);
	p->blksize = cpu_to_be32(req->i.size);
	वापस drbd_send_command(peer_device, sock, P_OUT_OF_SYNC, माप(*p), शून्य, 0);
पूर्ण

/*
  drbd_send distinguishes two हालs:

  Packets sent via the data socket "sock"
  and packets sent via the meta data socket "msock"

		    sock                      msock
  -----------------+-------------------------+------------------------------
  समयout           conf.समयout / 2          conf.समयout / 2
  समयout action    send a ping via msock     Abort communication
					      and बंद all sockets
*/

/*
 * you must have करोwn()ed the appropriate [m]sock_mutex अन्यथाwhere!
 */
पूर्णांक drbd_send(काष्ठा drbd_connection *connection, काष्ठा socket *sock,
	      व्योम *buf, माप_प्रकार size, अचिन्हित msg_flags)
अणु
	काष्ठा kvec iov = अणु.iov_base = buf, .iov_len = sizeपूर्ण;
	काष्ठा msghdr msg = अणु.msg_flags = msg_flags | MSG_NOSIGNALपूर्ण;
	पूर्णांक rv, sent = 0;

	अगर (!sock)
		वापस -EBADR;

	/* THINK  अगर (संकेत_pending) वापस ... ? */

	iov_iter_kvec(&msg.msg_iter, WRITE, &iov, 1, size);

	अगर (sock == connection->data.socket) अणु
		rcu_पढ़ो_lock();
		connection->ko_count = rcu_dereference(connection->net_conf)->ko_count;
		rcu_पढ़ो_unlock();
		drbd_update_congested(connection);
	पूर्ण
	करो अणु
		rv = sock_sendmsg(sock, &msg);
		अगर (rv == -EAGAIN) अणु
			अगर (we_should_drop_the_connection(connection, sock))
				अवरोध;
			अन्यथा
				जारी;
		पूर्ण
		अगर (rv == -EINTR) अणु
			flush_संकेतs(current);
			rv = 0;
		पूर्ण
		अगर (rv < 0)
			अवरोध;
		sent += rv;
	पूर्ण जबतक (sent < size);

	अगर (sock == connection->data.socket)
		clear_bit(NET_CONGESTED, &connection->flags);

	अगर (rv <= 0) अणु
		अगर (rv != -EAGAIN) अणु
			drbd_err(connection, "%s_sendmsg returned %d\n",
				 sock == connection->meta.socket ? "msock" : "sock",
				 rv);
			conn_request_state(connection, NS(conn, C_BROKEN_PIPE), CS_HARD);
		पूर्ण अन्यथा
			conn_request_state(connection, NS(conn, C_TIMEOUT), CS_HARD);
	पूर्ण

	वापस sent;
पूर्ण

/*
 * drbd_send_all  -  Send an entire buffer
 *
 * Returns 0 upon success and a negative error value otherwise.
 */
पूर्णांक drbd_send_all(काष्ठा drbd_connection *connection, काष्ठा socket *sock, व्योम *buffer,
		  माप_प्रकार size, अचिन्हित msg_flags)
अणु
	पूर्णांक err;

	err = drbd_send(connection, sock, buffer, size, msg_flags);
	अगर (err < 0)
		वापस err;
	अगर (err != size)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक drbd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा drbd_device *device = bdev->bd_disk->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	mutex_lock(&drbd_मुख्य_mutex);
	spin_lock_irqsave(&device->resource->req_lock, flags);
	/* to have a stable device->state.role
	 * and no race with updating खोलो_cnt */

	अगर (device->state.role != R_PRIMARY) अणु
		अगर (mode & FMODE_WRITE)
			rv = -EROFS;
		अन्यथा अगर (!drbd_allow_oos)
			rv = -EMEDIUMTYPE;
	पूर्ण

	अगर (!rv)
		device->खोलो_cnt++;
	spin_unlock_irqrestore(&device->resource->req_lock, flags);
	mutex_unlock(&drbd_मुख्य_mutex);

	वापस rv;
पूर्ण

अटल व्योम drbd_release(काष्ठा gendisk *gd, भ_शेषe_t mode)
अणु
	काष्ठा drbd_device *device = gd->निजी_data;
	mutex_lock(&drbd_मुख्य_mutex);
	device->खोलो_cnt--;
	mutex_unlock(&drbd_मुख्य_mutex);
पूर्ण

/* need to hold resource->req_lock */
व्योम drbd_queue_unplug(काष्ठा drbd_device *device)
अणु
	अगर (device->state.pdsk >= D_INCONSISTENT && device->state.conn >= C_CONNECTED) अणु
		D_ASSERT(device, device->state.role == R_PRIMARY);
		अगर (test_and_clear_bit(UNPLUG_REMOTE, &device->flags)) अणु
			drbd_queue_work_अगर_unqueued(
				&first_peer_device(device)->connection->sender_work,
				&device->unplug_work);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम drbd_set_शेषs(काष्ठा drbd_device *device)
अणु
	/* Beware! The actual layout dअगरfers
	 * between big endian and little endian */
	device->state = (जोड़ drbd_dev_state) अणु
		अणु .role = R_SECONDARY,
		  .peer = R_UNKNOWN,
		  .conn = C_STANDALONE,
		  .disk = D_DISKLESS,
		  .pdsk = D_UNKNOWN,
		पूर्ण पूर्ण;
पूर्ण

व्योम drbd_init_set_शेषs(काष्ठा drbd_device *device)
अणु
	/* the स_रखो(,0,) did most of this.
	 * note: only assignments, no allocation in here */

	drbd_set_शेषs(device);

	atomic_set(&device->ap_bio_cnt, 0);
	atomic_set(&device->ap_actlog_cnt, 0);
	atomic_set(&device->ap_pending_cnt, 0);
	atomic_set(&device->rs_pending_cnt, 0);
	atomic_set(&device->unacked_cnt, 0);
	atomic_set(&device->local_cnt, 0);
	atomic_set(&device->pp_in_use_by_net, 0);
	atomic_set(&device->rs_sect_in, 0);
	atomic_set(&device->rs_sect_ev, 0);
	atomic_set(&device->ap_in_flight, 0);
	atomic_set(&device->md_io.in_use, 0);

	mutex_init(&device->own_state_mutex);
	device->state_mutex = &device->own_state_mutex;

	spin_lock_init(&device->al_lock);
	spin_lock_init(&device->peer_seq_lock);

	INIT_LIST_HEAD(&device->active_ee);
	INIT_LIST_HEAD(&device->sync_ee);
	INIT_LIST_HEAD(&device->करोne_ee);
	INIT_LIST_HEAD(&device->पढ़ो_ee);
	INIT_LIST_HEAD(&device->net_ee);
	INIT_LIST_HEAD(&device->resync_पढ़ोs);
	INIT_LIST_HEAD(&device->resync_work.list);
	INIT_LIST_HEAD(&device->unplug_work.list);
	INIT_LIST_HEAD(&device->bm_io_work.w.list);
	INIT_LIST_HEAD(&device->pending_master_completion[0]);
	INIT_LIST_HEAD(&device->pending_master_completion[1]);
	INIT_LIST_HEAD(&device->pending_completion[0]);
	INIT_LIST_HEAD(&device->pending_completion[1]);

	device->resync_work.cb  = w_resync_समयr;
	device->unplug_work.cb  = w_send_ग_लिखो_hपूर्णांक;
	device->bm_io_work.w.cb = w_biपंचांगap_io;

	समयr_setup(&device->resync_समयr, resync_समयr_fn, 0);
	समयr_setup(&device->md_sync_समयr, md_sync_समयr_fn, 0);
	समयr_setup(&device->start_resync_समयr, start_resync_समयr_fn, 0);
	समयr_setup(&device->request_समयr, request_समयr_fn, 0);

	init_रुकोqueue_head(&device->misc_रुको);
	init_रुकोqueue_head(&device->state_रुको);
	init_रुकोqueue_head(&device->ee_रुको);
	init_रुकोqueue_head(&device->al_रुको);
	init_रुकोqueue_head(&device->seq_रुको);

	device->resync_wenr = LC_FREE;
	device->peer_max_bio_size = DRBD_MAX_BIO_SIZE_SAFE;
	device->local_max_bio_size = DRBD_MAX_BIO_SIZE_SAFE;
पूर्ण

व्योम drbd_set_my_capacity(काष्ठा drbd_device *device, sector_t size)
अणु
	अक्षर ppb[10];

	set_capacity_and_notअगरy(device->vdisk, size);

	drbd_info(device, "size = %s (%llu KB)\n",
		ppsize(ppb, size>>1), (अचिन्हित दीर्घ दीर्घ)size>>1);
पूर्ण

व्योम drbd_device_cleanup(काष्ठा drbd_device *device)
अणु
	पूर्णांक i;
	अगर (first_peer_device(device)->connection->receiver.t_state != NONE)
		drbd_err(device, "ASSERT FAILED: receiver t_state == %d expected 0.\n",
				first_peer_device(device)->connection->receiver.t_state);

	device->al_writ_cnt  =
	device->bm_writ_cnt  =
	device->पढ़ो_cnt     =
	device->recv_cnt     =
	device->send_cnt     =
	device->writ_cnt     =
	device->p_size       =
	device->rs_start     =
	device->rs_total     =
	device->rs_failed    = 0;
	device->rs_last_events = 0;
	device->rs_last_sect_ev = 0;
	क्रम (i = 0; i < DRBD_SYNC_MARKS; i++) अणु
		device->rs_mark_left[i] = 0;
		device->rs_mark_समय[i] = 0;
	पूर्ण
	D_ASSERT(device, first_peer_device(device)->connection->net_conf == शून्य);

	set_capacity_and_notअगरy(device->vdisk, 0);
	अगर (device->biपंचांगap) अणु
		/* maybe never allocated. */
		drbd_bm_resize(device, 0, 1);
		drbd_bm_cleanup(device);
	पूर्ण

	drbd_backing_dev_मुक्त(device, device->ldev);
	device->ldev = शून्य;

	clear_bit(AL_SUSPENDED, &device->flags);

	D_ASSERT(device, list_empty(&device->active_ee));
	D_ASSERT(device, list_empty(&device->sync_ee));
	D_ASSERT(device, list_empty(&device->करोne_ee));
	D_ASSERT(device, list_empty(&device->पढ़ो_ee));
	D_ASSERT(device, list_empty(&device->net_ee));
	D_ASSERT(device, list_empty(&device->resync_पढ़ोs));
	D_ASSERT(device, list_empty(&first_peer_device(device)->connection->sender_work.q));
	D_ASSERT(device, list_empty(&device->resync_work.list));
	D_ASSERT(device, list_empty(&device->unplug_work.list));

	drbd_set_शेषs(device);
पूर्ण


अटल व्योम drbd_destroy_mempools(व्योम)
अणु
	काष्ठा page *page;

	जबतक (drbd_pp_pool) अणु
		page = drbd_pp_pool;
		drbd_pp_pool = (काष्ठा page *)page_निजी(page);
		__मुक्त_page(page);
		drbd_pp_vacant--;
	पूर्ण

	/* D_ASSERT(device, atomic_पढ़ो(&drbd_pp_vacant)==0); */

	bioset_निकास(&drbd_io_bio_set);
	bioset_निकास(&drbd_md_io_bio_set);
	mempool_निकास(&drbd_md_io_page_pool);
	mempool_निकास(&drbd_ee_mempool);
	mempool_निकास(&drbd_request_mempool);
	kmem_cache_destroy(drbd_ee_cache);
	kmem_cache_destroy(drbd_request_cache);
	kmem_cache_destroy(drbd_bm_ext_cache);
	kmem_cache_destroy(drbd_al_ext_cache);

	drbd_ee_cache        = शून्य;
	drbd_request_cache   = शून्य;
	drbd_bm_ext_cache    = शून्य;
	drbd_al_ext_cache    = शून्य;

	वापस;
पूर्ण

अटल पूर्णांक drbd_create_mempools(व्योम)
अणु
	काष्ठा page *page;
	स्थिर पूर्णांक number = (DRBD_MAX_BIO_SIZE/PAGE_SIZE) * drbd_minor_count;
	पूर्णांक i, ret;

	/* caches */
	drbd_request_cache = kmem_cache_create(
		"drbd_req", माप(काष्ठा drbd_request), 0, 0, शून्य);
	अगर (drbd_request_cache == शून्य)
		जाओ Enomem;

	drbd_ee_cache = kmem_cache_create(
		"drbd_ee", माप(काष्ठा drbd_peer_request), 0, 0, शून्य);
	अगर (drbd_ee_cache == शून्य)
		जाओ Enomem;

	drbd_bm_ext_cache = kmem_cache_create(
		"drbd_bm", माप(काष्ठा bm_extent), 0, 0, शून्य);
	अगर (drbd_bm_ext_cache == शून्य)
		जाओ Enomem;

	drbd_al_ext_cache = kmem_cache_create(
		"drbd_al", माप(काष्ठा lc_element), 0, 0, शून्य);
	अगर (drbd_al_ext_cache == शून्य)
		जाओ Enomem;

	/* mempools */
	ret = bioset_init(&drbd_io_bio_set, BIO_POOL_SIZE, 0, 0);
	अगर (ret)
		जाओ Enomem;

	ret = bioset_init(&drbd_md_io_bio_set, DRBD_MIN_POOL_PAGES, 0,
			  BIOSET_NEED_BVECS);
	अगर (ret)
		जाओ Enomem;

	ret = mempool_init_page_pool(&drbd_md_io_page_pool, DRBD_MIN_POOL_PAGES, 0);
	अगर (ret)
		जाओ Enomem;

	ret = mempool_init_slab_pool(&drbd_request_mempool, number,
				     drbd_request_cache);
	अगर (ret)
		जाओ Enomem;

	ret = mempool_init_slab_pool(&drbd_ee_mempool, number, drbd_ee_cache);
	अगर (ret)
		जाओ Enomem;

	क्रम (i = 0; i < number; i++) अणु
		page = alloc_page(GFP_HIGHUSER);
		अगर (!page)
			जाओ Enomem;
		set_page_निजी(page, (अचिन्हित दीर्घ)drbd_pp_pool);
		drbd_pp_pool = page;
	पूर्ण
	drbd_pp_vacant = number;

	वापस 0;

Enomem:
	drbd_destroy_mempools(); /* in हाल we allocated some */
	वापस -ENOMEM;
पूर्ण

अटल व्योम drbd_release_all_peer_reqs(काष्ठा drbd_device *device)
अणु
	पूर्णांक rr;

	rr = drbd_मुक्त_peer_reqs(device, &device->active_ee);
	अगर (rr)
		drbd_err(device, "%d EEs in active list found!\n", rr);

	rr = drbd_मुक्त_peer_reqs(device, &device->sync_ee);
	अगर (rr)
		drbd_err(device, "%d EEs in sync list found!\n", rr);

	rr = drbd_मुक्त_peer_reqs(device, &device->पढ़ो_ee);
	अगर (rr)
		drbd_err(device, "%d EEs in read list found!\n", rr);

	rr = drbd_मुक्त_peer_reqs(device, &device->करोne_ee);
	अगर (rr)
		drbd_err(device, "%d EEs in done list found!\n", rr);

	rr = drbd_मुक्त_peer_reqs(device, &device->net_ee);
	अगर (rr)
		drbd_err(device, "%d EEs in net list found!\n", rr);
पूर्ण

/* caution. no locking. */
व्योम drbd_destroy_device(काष्ठा kref *kref)
अणु
	काष्ठा drbd_device *device = container_of(kref, काष्ठा drbd_device, kref);
	काष्ठा drbd_resource *resource = device->resource;
	काष्ठा drbd_peer_device *peer_device, *पंचांगp_peer_device;

	del_समयr_sync(&device->request_समयr);

	/* paranoia निश्चितs */
	D_ASSERT(device, device->खोलो_cnt == 0);
	/* end paranoia निश्चितs */

	/* cleanup stuff that may have been allocated during
	 * device (re-)configuration or state changes */

	drbd_backing_dev_मुक्त(device, device->ldev);
	device->ldev = शून्य;

	drbd_release_all_peer_reqs(device);

	lc_destroy(device->act_log);
	lc_destroy(device->resync);

	kमुक्त(device->p_uuid);
	/* device->p_uuid = शून्य; */

	अगर (device->biपंचांगap) /* should no दीर्घer be there. */
		drbd_bm_cleanup(device);
	__मुक्त_page(device->md_io.page);
	put_disk(device->vdisk);
	blk_cleanup_queue(device->rq_queue);
	kमुक्त(device->rs_plan_s);

	/* not क्रम_each_connection(connection, resource):
	 * those may have been cleaned up and disassociated alपढ़ोy.
	 */
	क्रम_each_peer_device_safe(peer_device, पंचांगp_peer_device, device) अणु
		kref_put(&peer_device->connection->kref, drbd_destroy_connection);
		kमुक्त(peer_device);
	पूर्ण
	स_रखो(device, 0xfd, माप(*device));
	kमुक्त(device);
	kref_put(&resource->kref, drbd_destroy_resource);
पूर्ण

/* One global retry thपढ़ो, अगर we need to push back some bio and have it
 * reinserted through our make request function.
 */
अटल काष्ठा retry_worker अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा worker;

	spinlock_t lock;
	काष्ठा list_head ग_लिखोs;
पूर्ण retry;

अटल व्योम करो_retry(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा retry_worker *retry = container_of(ws, काष्ठा retry_worker, worker);
	LIST_HEAD(ग_लिखोs);
	काष्ठा drbd_request *req, *पंचांगp;

	spin_lock_irq(&retry->lock);
	list_splice_init(&retry->ग_लिखोs, &ग_लिखोs);
	spin_unlock_irq(&retry->lock);

	list_क्रम_each_entry_safe(req, पंचांगp, &ग_लिखोs, tl_requests) अणु
		काष्ठा drbd_device *device = req->device;
		काष्ठा bio *bio = req->master_bio;
		bool expected;

		expected =
			expect(atomic_पढ़ो(&req->completion_ref) == 0) &&
			expect(req->rq_state & RQ_POSTPONED) &&
			expect((req->rq_state & RQ_LOCAL_PENDING) == 0 ||
				(req->rq_state & RQ_LOCAL_ABORTED) != 0);

		अगर (!expected)
			drbd_err(device, "req=%p completion_ref=%d rq_state=%x\n",
				req, atomic_पढ़ो(&req->completion_ref),
				req->rq_state);

		/* We still need to put one kref associated with the
		 * "completion_ref" going zero in the code path that queued it
		 * here.  The request object may still be referenced by a
		 * frozen local req->निजी_bio, in हाल we क्रमce-detached.
		 */
		kref_put(&req->kref, drbd_req_destroy);

		/* A single suspended or otherwise blocking device may stall
		 * all others as well.  Fortunately, this code path is to
		 * recover from a situation that "should not happen":
		 * concurrent ग_लिखोs in multi-primary setup.
		 * In a "normal" lअगरecycle, this workqueue is supposed to be
		 * destroyed without ever करोing anything.
		 * If it turns out to be an issue anyways, we can करो per
		 * resource (replication group) or per device (minor) retry
		 * workqueues instead.
		 */

		/* We are not just करोing submit_bio_noacct(),
		 * as we want to keep the start_समय inक्रमmation. */
		inc_ap_bio(device);
		__drbd_make_request(device, bio);
	पूर्ण
पूर्ण

/* called via drbd_req_put_completion_ref(),
 * holds resource->req_lock */
व्योम drbd_restart_request(काष्ठा drbd_request *req)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&retry.lock, flags);
	list_move_tail(&req->tl_requests, &retry.ग_लिखोs);
	spin_unlock_irqrestore(&retry.lock, flags);

	/* Drop the extra reference that would otherwise
	 * have been dropped by complete_master_bio.
	 * करो_retry() needs to grab a new one. */
	dec_ap_bio(req->device);

	queue_work(retry.wq, &retry.worker);
पूर्ण

व्योम drbd_destroy_resource(काष्ठा kref *kref)
अणु
	काष्ठा drbd_resource *resource =
		container_of(kref, काष्ठा drbd_resource, kref);

	idr_destroy(&resource->devices);
	मुक्त_cpumask_var(resource->cpu_mask);
	kमुक्त(resource->name);
	स_रखो(resource, 0xf2, माप(*resource));
	kमुक्त(resource);
पूर्ण

व्योम drbd_मुक्त_resource(काष्ठा drbd_resource *resource)
अणु
	काष्ठा drbd_connection *connection, *पंचांगp;

	क्रम_each_connection_safe(connection, पंचांगp, resource) अणु
		list_del(&connection->connections);
		drbd_debugfs_connection_cleanup(connection);
		kref_put(&connection->kref, drbd_destroy_connection);
	पूर्ण
	drbd_debugfs_resource_cleanup(resource);
	kref_put(&resource->kref, drbd_destroy_resource);
पूर्ण

अटल व्योम drbd_cleanup(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा drbd_device *device;
	काष्ठा drbd_resource *resource, *पंचांगp;

	/* first हटाओ proc,
	 * drbdsetup uses it's presence to detect
	 * whether DRBD is loaded.
	 * If we would get stuck in proc removal,
	 * but have netlink alपढ़ोy deरेजिस्टरed,
	 * some drbdsetup commands may रुको क्रमever
	 * क्रम an answer.
	 */
	अगर (drbd_proc)
		हटाओ_proc_entry("drbd", शून्य);

	अगर (retry.wq)
		destroy_workqueue(retry.wq);

	drbd_genl_unरेजिस्टर();

	idr_क्रम_each_entry(&drbd_devices, device, i)
		drbd_delete_device(device);

	/* not _rcu since, no other updater anymore. Genl alपढ़ोy unरेजिस्टरed */
	क्रम_each_resource_safe(resource, पंचांगp, &drbd_resources) अणु
		list_del(&resource->resources);
		drbd_मुक्त_resource(resource);
	पूर्ण

	drbd_debugfs_cleanup();

	drbd_destroy_mempools();
	unरेजिस्टर_blkdev(DRBD_MAJOR, "drbd");

	idr_destroy(&drbd_devices);

	pr_info("module cleanup done.\n");
पूर्ण

अटल व्योम drbd_init_workqueue(काष्ठा drbd_work_queue* wq)
अणु
	spin_lock_init(&wq->q_lock);
	INIT_LIST_HEAD(&wq->q);
	init_रुकोqueue_head(&wq->q_रुको);
पूर्ण

काष्ठा completion_work अणु
	काष्ठा drbd_work w;
	काष्ठा completion करोne;
पूर्ण;

अटल पूर्णांक w_complete(काष्ठा drbd_work *w, पूर्णांक cancel)
अणु
	काष्ठा completion_work *completion_work =
		container_of(w, काष्ठा completion_work, w);

	complete(&completion_work->करोne);
	वापस 0;
पूर्ण

व्योम drbd_flush_workqueue(काष्ठा drbd_work_queue *work_queue)
अणु
	काष्ठा completion_work completion_work;

	completion_work.w.cb = w_complete;
	init_completion(&completion_work.करोne);
	drbd_queue_work(work_queue, &completion_work.w);
	रुको_क्रम_completion(&completion_work.करोne);
पूर्ण

काष्ठा drbd_resource *drbd_find_resource(स्थिर अक्षर *name)
अणु
	काष्ठा drbd_resource *resource;

	अगर (!name || !name[0])
		वापस शून्य;

	rcu_पढ़ो_lock();
	क्रम_each_resource_rcu(resource, &drbd_resources) अणु
		अगर (!म_भेद(resource->name, name)) अणु
			kref_get(&resource->kref);
			जाओ found;
		पूर्ण
	पूर्ण
	resource = शून्य;
found:
	rcu_पढ़ो_unlock();
	वापस resource;
पूर्ण

काष्ठा drbd_connection *conn_get_by_addrs(व्योम *my_addr, पूर्णांक my_addr_len,
				     व्योम *peer_addr, पूर्णांक peer_addr_len)
अणु
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;

	rcu_पढ़ो_lock();
	क्रम_each_resource_rcu(resource, &drbd_resources) अणु
		क्रम_each_connection_rcu(connection, resource) अणु
			अगर (connection->my_addr_len == my_addr_len &&
			    connection->peer_addr_len == peer_addr_len &&
			    !स_भेद(&connection->my_addr, my_addr, my_addr_len) &&
			    !स_भेद(&connection->peer_addr, peer_addr, peer_addr_len)) अणु
				kref_get(&connection->kref);
				जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण
	connection = शून्य;
found:
	rcu_पढ़ो_unlock();
	वापस connection;
पूर्ण

अटल पूर्णांक drbd_alloc_socket(काष्ठा drbd_socket *socket)
अणु
	socket->rbuf = (व्योम *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!socket->rbuf)
		वापस -ENOMEM;
	socket->sbuf = (व्योम *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!socket->sbuf)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम drbd_मुक्त_socket(काष्ठा drbd_socket *socket)
अणु
	मुक्त_page((अचिन्हित दीर्घ) socket->sbuf);
	मुक्त_page((अचिन्हित दीर्घ) socket->rbuf);
पूर्ण

व्योम conn_मुक्त_crypto(काष्ठा drbd_connection *connection)
अणु
	drbd_मुक्त_sock(connection);

	crypto_मुक्त_shash(connection->csums_tfm);
	crypto_मुक्त_shash(connection->verअगरy_tfm);
	crypto_मुक्त_shash(connection->cram_hmac_tfm);
	crypto_मुक्त_shash(connection->पूर्णांकegrity_tfm);
	crypto_मुक्त_shash(connection->peer_पूर्णांकegrity_tfm);
	kमुक्त(connection->पूर्णांक_dig_in);
	kमुक्त(connection->पूर्णांक_dig_vv);

	connection->csums_tfm = शून्य;
	connection->verअगरy_tfm = शून्य;
	connection->cram_hmac_tfm = शून्य;
	connection->पूर्णांकegrity_tfm = शून्य;
	connection->peer_पूर्णांकegrity_tfm = शून्य;
	connection->पूर्णांक_dig_in = शून्य;
	connection->पूर्णांक_dig_vv = शून्य;
पूर्ण

पूर्णांक set_resource_options(काष्ठा drbd_resource *resource, काष्ठा res_opts *res_opts)
अणु
	काष्ठा drbd_connection *connection;
	cpumask_var_t new_cpu_mask;
	पूर्णांक err;

	अगर (!zalloc_cpumask_var(&new_cpu_mask, GFP_KERNEL))
		वापस -ENOMEM;

	/* silently ignore cpu mask on UP kernel */
	अगर (nr_cpu_ids > 1 && res_opts->cpu_mask[0] != 0) अणु
		err = biपंचांगap_parse(res_opts->cpu_mask, DRBD_CPU_MASK_SIZE,
				   cpumask_bits(new_cpu_mask), nr_cpu_ids);
		अगर (err == -EOVERFLOW) अणु
			/* So what. mask it out. */
			cpumask_var_t पंचांगp_cpu_mask;
			अगर (zalloc_cpumask_var(&पंचांगp_cpu_mask, GFP_KERNEL)) अणु
				cpumask_setall(पंचांगp_cpu_mask);
				cpumask_and(new_cpu_mask, new_cpu_mask, पंचांगp_cpu_mask);
				drbd_warn(resource, "Overflow in bitmap_parse(%.12s%s), truncating to %u bits\n",
					res_opts->cpu_mask,
					म_माप(res_opts->cpu_mask) > 12 ? "..." : "",
					nr_cpu_ids);
				मुक्त_cpumask_var(पंचांगp_cpu_mask);
				err = 0;
			पूर्ण
		पूर्ण
		अगर (err) अणु
			drbd_warn(resource, "bitmap_parse() failed with %d\n", err);
			/* retcode = ERR_CPU_MASK_PARSE; */
			जाओ fail;
		पूर्ण
	पूर्ण
	resource->res_opts = *res_opts;
	अगर (cpumask_empty(new_cpu_mask))
		drbd_calc_cpu_mask(&new_cpu_mask);
	अगर (!cpumask_equal(resource->cpu_mask, new_cpu_mask)) अणु
		cpumask_copy(resource->cpu_mask, new_cpu_mask);
		क्रम_each_connection_rcu(connection, resource) अणु
			connection->receiver.reset_cpu_mask = 1;
			connection->ack_receiver.reset_cpu_mask = 1;
			connection->worker.reset_cpu_mask = 1;
		पूर्ण
	पूर्ण
	err = 0;

fail:
	मुक्त_cpumask_var(new_cpu_mask);
	वापस err;

पूर्ण

काष्ठा drbd_resource *drbd_create_resource(स्थिर अक्षर *name)
अणु
	काष्ठा drbd_resource *resource;

	resource = kzalloc(माप(काष्ठा drbd_resource), GFP_KERNEL);
	अगर (!resource)
		जाओ fail;
	resource->name = kstrdup(name, GFP_KERNEL);
	अगर (!resource->name)
		जाओ fail_मुक्त_resource;
	अगर (!zalloc_cpumask_var(&resource->cpu_mask, GFP_KERNEL))
		जाओ fail_मुक्त_name;
	kref_init(&resource->kref);
	idr_init(&resource->devices);
	INIT_LIST_HEAD(&resource->connections);
	resource->ग_लिखो_ordering = WO_BDEV_FLUSH;
	list_add_tail_rcu(&resource->resources, &drbd_resources);
	mutex_init(&resource->conf_update);
	mutex_init(&resource->adm_mutex);
	spin_lock_init(&resource->req_lock);
	drbd_debugfs_resource_add(resource);
	वापस resource;

fail_मुक्त_name:
	kमुक्त(resource->name);
fail_मुक्त_resource:
	kमुक्त(resource);
fail:
	वापस शून्य;
पूर्ण

/* caller must be under adm_mutex */
काष्ठा drbd_connection *conn_create(स्थिर अक्षर *name, काष्ठा res_opts *res_opts)
अणु
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;

	connection = kzalloc(माप(काष्ठा drbd_connection), GFP_KERNEL);
	अगर (!connection)
		वापस शून्य;

	अगर (drbd_alloc_socket(&connection->data))
		जाओ fail;
	अगर (drbd_alloc_socket(&connection->meta))
		जाओ fail;

	connection->current_epoch = kzalloc(माप(काष्ठा drbd_epoch), GFP_KERNEL);
	अगर (!connection->current_epoch)
		जाओ fail;

	INIT_LIST_HEAD(&connection->transfer_log);

	INIT_LIST_HEAD(&connection->current_epoch->list);
	connection->epochs = 1;
	spin_lock_init(&connection->epoch_lock);

	connection->send.seen_any_ग_लिखो_yet = false;
	connection->send.current_epoch_nr = 0;
	connection->send.current_epoch_ग_लिखोs = 0;

	resource = drbd_create_resource(name);
	अगर (!resource)
		जाओ fail;

	connection->cstate = C_STANDALONE;
	mutex_init(&connection->cstate_mutex);
	init_रुकोqueue_head(&connection->ping_रुको);
	idr_init(&connection->peer_devices);

	drbd_init_workqueue(&connection->sender_work);
	mutex_init(&connection->data.mutex);
	mutex_init(&connection->meta.mutex);

	drbd_thपढ़ो_init(resource, &connection->receiver, drbd_receiver, "receiver");
	connection->receiver.connection = connection;
	drbd_thपढ़ो_init(resource, &connection->worker, drbd_worker, "worker");
	connection->worker.connection = connection;
	drbd_thपढ़ो_init(resource, &connection->ack_receiver, drbd_ack_receiver, "ack_recv");
	connection->ack_receiver.connection = connection;

	kref_init(&connection->kref);

	connection->resource = resource;

	अगर (set_resource_options(resource, res_opts))
		जाओ fail_resource;

	kref_get(&resource->kref);
	list_add_tail_rcu(&connection->connections, &resource->connections);
	drbd_debugfs_connection_add(connection);
	वापस connection;

fail_resource:
	list_del(&resource->resources);
	drbd_मुक्त_resource(resource);
fail:
	kमुक्त(connection->current_epoch);
	drbd_मुक्त_socket(&connection->meta);
	drbd_मुक्त_socket(&connection->data);
	kमुक्त(connection);
	वापस शून्य;
पूर्ण

व्योम drbd_destroy_connection(काष्ठा kref *kref)
अणु
	काष्ठा drbd_connection *connection = container_of(kref, काष्ठा drbd_connection, kref);
	काष्ठा drbd_resource *resource = connection->resource;

	अगर (atomic_पढ़ो(&connection->current_epoch->epoch_size) !=  0)
		drbd_err(connection, "epoch_size:%d\n", atomic_पढ़ो(&connection->current_epoch->epoch_size));
	kमुक्त(connection->current_epoch);

	idr_destroy(&connection->peer_devices);

	drbd_मुक्त_socket(&connection->meta);
	drbd_मुक्त_socket(&connection->data);
	kमुक्त(connection->पूर्णांक_dig_in);
	kमुक्त(connection->पूर्णांक_dig_vv);
	स_रखो(connection, 0xfc, माप(*connection));
	kमुक्त(connection);
	kref_put(&resource->kref, drbd_destroy_resource);
पूर्ण

अटल पूर्णांक init_submitter(काष्ठा drbd_device *device)
अणु
	/* खोलोcoded create_singlethपढ़ो_workqueue(),
	 * to be able to say "drbd%d", ..., minor */
	device->submit.wq =
		alloc_ordered_workqueue("drbd%u_submit", WQ_MEM_RECLAIM, device->minor);
	अगर (!device->submit.wq)
		वापस -ENOMEM;

	INIT_WORK(&device->submit.worker, करो_submit);
	INIT_LIST_HEAD(&device->submit.ग_लिखोs);
	वापस 0;
पूर्ण

क्रमागत drbd_ret_code drbd_create_device(काष्ठा drbd_config_context *adm_ctx, अचिन्हित पूर्णांक minor)
अणु
	काष्ठा drbd_resource *resource = adm_ctx->resource;
	काष्ठा drbd_connection *connection;
	काष्ठा drbd_device *device;
	काष्ठा drbd_peer_device *peer_device, *पंचांगp_peer_device;
	काष्ठा gendisk *disk;
	काष्ठा request_queue *q;
	पूर्णांक id;
	पूर्णांक vnr = adm_ctx->volume;
	क्रमागत drbd_ret_code err = ERR_NOMEM;

	device = minor_to_device(minor);
	अगर (device)
		वापस ERR_MINOR_OR_VOLUME_EXISTS;

	/* GFP_KERNEL, we are outside of all ग_लिखो-out paths */
	device = kzalloc(माप(काष्ठा drbd_device), GFP_KERNEL);
	अगर (!device)
		वापस ERR_NOMEM;
	kref_init(&device->kref);

	kref_get(&resource->kref);
	device->resource = resource;
	device->minor = minor;
	device->vnr = vnr;

	drbd_init_set_शेषs(device);

	q = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!q)
		जाओ out_no_q;
	device->rq_queue = q;

	disk = alloc_disk(1);
	अगर (!disk)
		जाओ out_no_disk;
	device->vdisk = disk;

	set_disk_ro(disk, true);

	disk->queue = q;
	disk->major = DRBD_MAJOR;
	disk->first_minor = minor;
	disk->fops = &drbd_ops;
	प्र_लिखो(disk->disk_name, "drbd%d", minor);
	disk->निजी_data = device;

	blk_queue_ग_लिखो_cache(q, true, true);
	/* Setting the max_hw_sectors to an odd value of 8kibyte here
	   This triggers a max_bio_size message upon first attach or connect */
	blk_queue_max_hw_sectors(q, DRBD_MAX_BIO_SIZE_SAFE >> 8);

	device->md_io.page = alloc_page(GFP_KERNEL);
	अगर (!device->md_io.page)
		जाओ out_no_io_page;

	अगर (drbd_bm_init(device))
		जाओ out_no_biपंचांगap;
	device->पढ़ो_requests = RB_ROOT;
	device->ग_लिखो_requests = RB_ROOT;

	id = idr_alloc(&drbd_devices, device, minor, minor + 1, GFP_KERNEL);
	अगर (id < 0) अणु
		अगर (id == -ENOSPC)
			err = ERR_MINOR_OR_VOLUME_EXISTS;
		जाओ out_no_minor_idr;
	पूर्ण
	kref_get(&device->kref);

	id = idr_alloc(&resource->devices, device, vnr, vnr + 1, GFP_KERNEL);
	अगर (id < 0) अणु
		अगर (id == -ENOSPC)
			err = ERR_MINOR_OR_VOLUME_EXISTS;
		जाओ out_idr_हटाओ_minor;
	पूर्ण
	kref_get(&device->kref);

	INIT_LIST_HEAD(&device->peer_devices);
	INIT_LIST_HEAD(&device->pending_biपंचांगap_io);
	क्रम_each_connection(connection, resource) अणु
		peer_device = kzalloc(माप(काष्ठा drbd_peer_device), GFP_KERNEL);
		अगर (!peer_device)
			जाओ out_idr_हटाओ_from_resource;
		peer_device->connection = connection;
		peer_device->device = device;

		list_add(&peer_device->peer_devices, &device->peer_devices);
		kref_get(&device->kref);

		id = idr_alloc(&connection->peer_devices, peer_device, vnr, vnr + 1, GFP_KERNEL);
		अगर (id < 0) अणु
			अगर (id == -ENOSPC)
				err = ERR_INVALID_REQUEST;
			जाओ out_idr_हटाओ_from_resource;
		पूर्ण
		kref_get(&connection->kref);
		INIT_WORK(&peer_device->send_acks_work, drbd_send_acks_wf);
	पूर्ण

	अगर (init_submitter(device)) अणु
		err = ERR_NOMEM;
		जाओ out_idr_हटाओ_vol;
	पूर्ण

	add_disk(disk);

	/* inherit the connection state */
	device->state.conn = first_connection(resource)->cstate;
	अगर (device->state.conn == C_WF_REPORT_PARAMS) अणु
		क्रम_each_peer_device(peer_device, device)
			drbd_connected(peer_device);
	पूर्ण
	/* move to create_peer_device() */
	क्रम_each_peer_device(peer_device, device)
		drbd_debugfs_peer_device_add(peer_device);
	drbd_debugfs_device_add(device);
	वापस NO_ERROR;

out_idr_हटाओ_vol:
	idr_हटाओ(&connection->peer_devices, vnr);
out_idr_हटाओ_from_resource:
	क्रम_each_connection(connection, resource) अणु
		peer_device = idr_हटाओ(&connection->peer_devices, vnr);
		अगर (peer_device)
			kref_put(&connection->kref, drbd_destroy_connection);
	पूर्ण
	क्रम_each_peer_device_safe(peer_device, पंचांगp_peer_device, device) अणु
		list_del(&peer_device->peer_devices);
		kमुक्त(peer_device);
	पूर्ण
	idr_हटाओ(&resource->devices, vnr);
out_idr_हटाओ_minor:
	idr_हटाओ(&drbd_devices, minor);
	synchronize_rcu();
out_no_minor_idr:
	drbd_bm_cleanup(device);
out_no_biपंचांगap:
	__मुक्त_page(device->md_io.page);
out_no_io_page:
	put_disk(disk);
out_no_disk:
	blk_cleanup_queue(q);
out_no_q:
	kref_put(&resource->kref, drbd_destroy_resource);
	kमुक्त(device);
	वापस err;
पूर्ण

व्योम drbd_delete_device(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_resource *resource = device->resource;
	काष्ठा drbd_connection *connection;
	काष्ठा drbd_peer_device *peer_device;

	/* move to मुक्त_peer_device() */
	क्रम_each_peer_device(peer_device, device)
		drbd_debugfs_peer_device_cleanup(peer_device);
	drbd_debugfs_device_cleanup(device);
	क्रम_each_connection(connection, resource) अणु
		idr_हटाओ(&connection->peer_devices, device->vnr);
		kref_put(&device->kref, drbd_destroy_device);
	पूर्ण
	idr_हटाओ(&resource->devices, device->vnr);
	kref_put(&device->kref, drbd_destroy_device);
	idr_हटाओ(&drbd_devices, device_to_minor(device));
	kref_put(&device->kref, drbd_destroy_device);
	del_gendisk(device->vdisk);
	synchronize_rcu();
	kref_put(&device->kref, drbd_destroy_device);
पूर्ण

अटल पूर्णांक __init drbd_init(व्योम)
अणु
	पूर्णांक err;

	अगर (drbd_minor_count < DRBD_MINOR_COUNT_MIN || drbd_minor_count > DRBD_MINOR_COUNT_MAX) अणु
		pr_err("invalid minor_count (%d)\n", drbd_minor_count);
#अगर_घोषित MODULE
		वापस -EINVAL;
#अन्यथा
		drbd_minor_count = DRBD_MINOR_COUNT_DEF;
#पूर्ण_अगर
	पूर्ण

	err = रेजिस्टर_blkdev(DRBD_MAJOR, "drbd");
	अगर (err) अणु
		pr_err("unable to register block device major %d\n",
		       DRBD_MAJOR);
		वापस err;
	पूर्ण

	/*
	 * allocate all necessary काष्ठाs
	 */
	init_रुकोqueue_head(&drbd_pp_रुको);

	drbd_proc = शून्य; /* play safe क्रम drbd_cleanup */
	idr_init(&drbd_devices);

	mutex_init(&resources_mutex);
	INIT_LIST_HEAD(&drbd_resources);

	err = drbd_genl_रेजिस्टर();
	अगर (err) अणु
		pr_err("unable to register generic netlink family\n");
		जाओ fail;
	पूर्ण

	err = drbd_create_mempools();
	अगर (err)
		जाओ fail;

	err = -ENOMEM;
	drbd_proc = proc_create_single("drbd", S_IFREG | 0444 , शून्य, drbd_seq_show);
	अगर (!drbd_proc)	अणु
		pr_err("unable to register proc file\n");
		जाओ fail;
	पूर्ण

	retry.wq = create_singlethपढ़ो_workqueue("drbd-reissue");
	अगर (!retry.wq) अणु
		pr_err("unable to create retry workqueue\n");
		जाओ fail;
	पूर्ण
	INIT_WORK(&retry.worker, करो_retry);
	spin_lock_init(&retry.lock);
	INIT_LIST_HEAD(&retry.ग_लिखोs);

	drbd_debugfs_init();

	pr_info("initialized. "
	       "Version: " REL_VERSION " (api:%d/proto:%d-%d)\n",
	       API_VERSION, PRO_VERSION_MIN, PRO_VERSION_MAX);
	pr_info("%s\n", drbd_buildtag());
	pr_info("registered as block device major %d\n", DRBD_MAJOR);
	वापस 0; /* Success! */

fail:
	drbd_cleanup();
	अगर (err == -ENOMEM)
		pr_err("ran out of memory\n");
	अन्यथा
		pr_err("initialization failure\n");
	वापस err;
पूर्ण

अटल व्योम drbd_मुक्त_one_sock(काष्ठा drbd_socket *ds)
अणु
	काष्ठा socket *s;
	mutex_lock(&ds->mutex);
	s = ds->socket;
	ds->socket = शून्य;
	mutex_unlock(&ds->mutex);
	अगर (s) अणु
		/* so debugfs करोes not need to mutex_lock() */
		synchronize_rcu();
		kernel_sock_shutकरोwn(s, SHUT_RDWR);
		sock_release(s);
	पूर्ण
पूर्ण

व्योम drbd_मुक्त_sock(काष्ठा drbd_connection *connection)
अणु
	अगर (connection->data.socket)
		drbd_मुक्त_one_sock(&connection->data);
	अगर (connection->meta.socket)
		drbd_मुक्त_one_sock(&connection->meta);
पूर्ण

/* meta data management */

व्योम conn_md_sync(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;

		kref_get(&device->kref);
		rcu_पढ़ो_unlock();
		drbd_md_sync(device);
		kref_put(&device->kref, drbd_destroy_device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* aligned 4kByte */
काष्ठा meta_data_on_disk अणु
	u64 la_size_sect;      /* last agreed size. */
	u64 uuid[UI_SIZE];   /* UUIDs. */
	u64 device_uuid;
	u64 reserved_u64_1;
	u32 flags;             /* MDF */
	u32 magic;
	u32 md_size_sect;
	u32 al_offset;         /* offset to this block */
	u32 al_nr_extents;     /* important क्रम restoring the AL (userspace) */
	      /* `-- act_log->nr_elements <-- ldev->dc.al_extents */
	u32 bm_offset;         /* offset to the biपंचांगap, from here */
	u32 bm_bytes_per_bit;  /* BM_BLOCK_SIZE */
	u32 la_peer_max_bio_size;   /* last peer max_bio_size */

	/* see al_tr_number_to_on_disk_sector() */
	u32 al_stripes;
	u32 al_stripe_size_4k;

	u8 reserved_u8[4096 - (7*8 + 10*4)];
पूर्ण __packed;



व्योम drbd_md_ग_लिखो(काष्ठा drbd_device *device, व्योम *b)
अणु
	काष्ठा meta_data_on_disk *buffer = b;
	sector_t sector;
	पूर्णांक i;

	स_रखो(buffer, 0, माप(*buffer));

	buffer->la_size_sect = cpu_to_be64(get_capacity(device->vdisk));
	क्रम (i = UI_CURRENT; i < UI_SIZE; i++)
		buffer->uuid[i] = cpu_to_be64(device->ldev->md.uuid[i]);
	buffer->flags = cpu_to_be32(device->ldev->md.flags);
	buffer->magic = cpu_to_be32(DRBD_MD_MAGIC_84_UNCLEAN);

	buffer->md_size_sect  = cpu_to_be32(device->ldev->md.md_size_sect);
	buffer->al_offset     = cpu_to_be32(device->ldev->md.al_offset);
	buffer->al_nr_extents = cpu_to_be32(device->act_log->nr_elements);
	buffer->bm_bytes_per_bit = cpu_to_be32(BM_BLOCK_SIZE);
	buffer->device_uuid = cpu_to_be64(device->ldev->md.device_uuid);

	buffer->bm_offset = cpu_to_be32(device->ldev->md.bm_offset);
	buffer->la_peer_max_bio_size = cpu_to_be32(device->peer_max_bio_size);

	buffer->al_stripes = cpu_to_be32(device->ldev->md.al_stripes);
	buffer->al_stripe_size_4k = cpu_to_be32(device->ldev->md.al_stripe_size_4k);

	D_ASSERT(device, drbd_md_ss(device->ldev) == device->ldev->md.md_offset);
	sector = device->ldev->md.md_offset;

	अगर (drbd_md_sync_page_io(device, device->ldev, sector, REQ_OP_WRITE)) अणु
		/* this was a try anyways ... */
		drbd_err(device, "meta data update failed!\n");
		drbd_chk_io_error(device, 1, DRBD_META_IO_ERROR);
	पूर्ण
पूर्ण

/**
 * drbd_md_sync() - Writes the meta data super block अगर the MD_सूचीTY flag bit is set
 * @device:	DRBD device.
 */
व्योम drbd_md_sync(काष्ठा drbd_device *device)
अणु
	काष्ठा meta_data_on_disk *buffer;

	/* Don't accidentally change the DRBD meta data layout. */
	BUILD_BUG_ON(UI_SIZE != 4);
	BUILD_BUG_ON(माप(काष्ठा meta_data_on_disk) != 4096);

	del_समयr(&device->md_sync_समयr);
	/* समयr may be rearmed by drbd_md_mark_dirty() now. */
	अगर (!test_and_clear_bit(MD_सूचीTY, &device->flags))
		वापस;

	/* We use here D_FAILED and not D_ATTACHING because we try to ग_लिखो
	 * metadata even अगर we detach due to a disk failure! */
	अगर (!get_ldev_अगर_state(device, D_FAILED))
		वापस;

	buffer = drbd_md_get_buffer(device, __func__);
	अगर (!buffer)
		जाओ out;

	drbd_md_ग_लिखो(device, buffer);

	/* Update device->ldev->md.la_size_sect,
	 * since we updated it on metadata. */
	device->ldev->md.la_size_sect = get_capacity(device->vdisk);

	drbd_md_put_buffer(device);
out:
	put_ldev(device);
पूर्ण

अटल पूर्णांक check_activity_log_stripe_size(काष्ठा drbd_device *device,
		काष्ठा meta_data_on_disk *on_disk,
		काष्ठा drbd_md *in_core)
अणु
	u32 al_stripes = be32_to_cpu(on_disk->al_stripes);
	u32 al_stripe_size_4k = be32_to_cpu(on_disk->al_stripe_size_4k);
	u64 al_size_4k;

	/* both not set: शेष to old fixed size activity log */
	अगर (al_stripes == 0 && al_stripe_size_4k == 0) अणु
		al_stripes = 1;
		al_stripe_size_4k = MD_32kB_SECT/8;
	पूर्ण

	/* some paranoia plausibility checks */

	/* we need both values to be set */
	अगर (al_stripes == 0 || al_stripe_size_4k == 0)
		जाओ err;

	al_size_4k = (u64)al_stripes * al_stripe_size_4k;

	/* Upper limit of activity log area, to aव्योम potential overflow
	 * problems in al_tr_number_to_on_disk_sector(). As right now, more
	 * than 72 * 4k blocks total only increases the amount of history,
	 * limiting this arbitrarily to 16 GB is not a real limitation ;-)  */
	अगर (al_size_4k > (16 * 1024 * 1024/4))
		जाओ err;

	/* Lower limit: we need at least 8 transaction slots (32kB)
	 * to not अवरोध existing setups */
	अगर (al_size_4k < MD_32kB_SECT/8)
		जाओ err;

	in_core->al_stripe_size_4k = al_stripe_size_4k;
	in_core->al_stripes = al_stripes;
	in_core->al_size_4k = al_size_4k;

	वापस 0;
err:
	drbd_err(device, "invalid activity log striping: al_stripes=%u, al_stripe_size_4k=%u\n",
			al_stripes, al_stripe_size_4k);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_offsets_and_sizes(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev)
अणु
	sector_t capacity = drbd_get_capacity(bdev->md_bdev);
	काष्ठा drbd_md *in_core = &bdev->md;
	s32 on_disk_al_sect;
	s32 on_disk_bm_sect;

	/* The on-disk size of the activity log, calculated from offsets, and
	 * the size of the activity log calculated from the stripe settings,
	 * should match.
	 * Though we could relax this a bit: it is ok, अगर the striped activity log
	 * fits in the available on-disk activity log size.
	 * Right now, that would अवरोध how resize is implemented.
	 * TODO: make drbd_determine_dev_size() (and the drbdmeta tool) aware
	 * of possible unused padding space in the on disk layout. */
	अगर (in_core->al_offset < 0) अणु
		अगर (in_core->bm_offset > in_core->al_offset)
			जाओ err;
		on_disk_al_sect = -in_core->al_offset;
		on_disk_bm_sect = in_core->al_offset - in_core->bm_offset;
	पूर्ण अन्यथा अणु
		अगर (in_core->al_offset != MD_4kB_SECT)
			जाओ err;
		अगर (in_core->bm_offset < in_core->al_offset + in_core->al_size_4k * MD_4kB_SECT)
			जाओ err;

		on_disk_al_sect = in_core->bm_offset - MD_4kB_SECT;
		on_disk_bm_sect = in_core->md_size_sect - in_core->bm_offset;
	पूर्ण

	/* old fixed size meta data is exactly that: fixed. */
	अगर (in_core->meta_dev_idx >= 0) अणु
		अगर (in_core->md_size_sect != MD_128MB_SECT
		||  in_core->al_offset != MD_4kB_SECT
		||  in_core->bm_offset != MD_4kB_SECT + MD_32kB_SECT
		||  in_core->al_stripes != 1
		||  in_core->al_stripe_size_4k != MD_32kB_SECT/8)
			जाओ err;
	पूर्ण

	अगर (capacity < in_core->md_size_sect)
		जाओ err;
	अगर (capacity - in_core->md_size_sect < drbd_md_first_sector(bdev))
		जाओ err;

	/* should be aligned, and at least 32k */
	अगर ((on_disk_al_sect & 7) || (on_disk_al_sect < MD_32kB_SECT))
		जाओ err;

	/* should fit (क्रम now: exactly) पूर्णांकo the available on-disk space;
	 * overflow prevention is in check_activity_log_stripe_size() above. */
	अगर (on_disk_al_sect != in_core->al_size_4k * MD_4kB_SECT)
		जाओ err;

	/* again, should be aligned */
	अगर (in_core->bm_offset & 7)
		जाओ err;

	/* FIXME check क्रम device grow with flex बाह्यal meta data? */

	/* can the available biपंचांगap space cover the last agreed device size? */
	अगर (on_disk_bm_sect < (in_core->la_size_sect+7)/MD_4kB_SECT/8/512)
		जाओ err;

	वापस 0;

err:
	drbd_err(device, "meta data offsets don't make sense: idx=%d "
			"al_s=%u, al_sz4k=%u, al_offset=%d, bm_offset=%d, "
			"md_size_sect=%u, la_size=%llu, md_capacity=%llu\n",
			in_core->meta_dev_idx,
			in_core->al_stripes, in_core->al_stripe_size_4k,
			in_core->al_offset, in_core->bm_offset, in_core->md_size_sect,
			(अचिन्हित दीर्घ दीर्घ)in_core->la_size_sect,
			(अचिन्हित दीर्घ दीर्घ)capacity);

	वापस -EINVAL;
पूर्ण


/**
 * drbd_md_पढ़ो() - Reads in the meta data super block
 * @device:	DRBD device.
 * @bdev:	Device from which the meta data should be पढ़ो in.
 *
 * Return NO_ERROR on success, and an क्रमागत drbd_ret_code in हाल
 * something goes wrong.
 *
 * Called exactly once during drbd_adm_attach(), जबतक still being D_DISKLESS,
 * even beक्रमe @bdev is asचिन्हित to @device->ldev.
 */
पूर्णांक drbd_md_पढ़ो(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev)
अणु
	काष्ठा meta_data_on_disk *buffer;
	u32 magic, flags;
	पूर्णांक i, rv = NO_ERROR;

	अगर (device->state.disk != D_DISKLESS)
		वापस ERR_DISK_CONFIGURED;

	buffer = drbd_md_get_buffer(device, __func__);
	अगर (!buffer)
		वापस ERR_NOMEM;

	/* First, figure out where our meta data superblock is located,
	 * and पढ़ो it. */
	bdev->md.meta_dev_idx = bdev->disk_conf->meta_dev_idx;
	bdev->md.md_offset = drbd_md_ss(bdev);
	/* Even क्रम (flexible or indexed) बाह्यal meta data,
	 * initially restrict us to the 4k superblock क्रम now.
	 * Affects the paranoia out-of-range access check in drbd_md_sync_page_io(). */
	bdev->md.md_size_sect = 8;

	अगर (drbd_md_sync_page_io(device, bdev, bdev->md.md_offset,
				 REQ_OP_READ)) अणु
		/* NOTE: can't करो normal error processing here as this is
		   called BEFORE disk is attached */
		drbd_err(device, "Error while reading metadata.\n");
		rv = ERR_IO_MD_DISK;
		जाओ err;
	पूर्ण

	magic = be32_to_cpu(buffer->magic);
	flags = be32_to_cpu(buffer->flags);
	अगर (magic == DRBD_MD_MAGIC_84_UNCLEAN ||
	    (magic == DRBD_MD_MAGIC_08 && !(flags & MDF_AL_CLEAN))) अणु
			/* btw: that's Activity Log clean, not "all" clean. */
		drbd_err(device, "Found unclean meta data. Did you \"drbdadm apply-al\"?\n");
		rv = ERR_MD_UNCLEAN;
		जाओ err;
	पूर्ण

	rv = ERR_MD_INVALID;
	अगर (magic != DRBD_MD_MAGIC_08) अणु
		अगर (magic == DRBD_MD_MAGIC_07)
			drbd_err(device, "Found old (0.7) meta data magic. Did you \"drbdadm create-md\"?\n");
		अन्यथा
			drbd_err(device, "Meta data magic not found. Did you \"drbdadm create-md\"?\n");
		जाओ err;
	पूर्ण

	अगर (be32_to_cpu(buffer->bm_bytes_per_bit) != BM_BLOCK_SIZE) अणु
		drbd_err(device, "unexpected bm_bytes_per_bit: %u (expected %u)\n",
		    be32_to_cpu(buffer->bm_bytes_per_bit), BM_BLOCK_SIZE);
		जाओ err;
	पूर्ण


	/* convert to in_core endian */
	bdev->md.la_size_sect = be64_to_cpu(buffer->la_size_sect);
	क्रम (i = UI_CURRENT; i < UI_SIZE; i++)
		bdev->md.uuid[i] = be64_to_cpu(buffer->uuid[i]);
	bdev->md.flags = be32_to_cpu(buffer->flags);
	bdev->md.device_uuid = be64_to_cpu(buffer->device_uuid);

	bdev->md.md_size_sect = be32_to_cpu(buffer->md_size_sect);
	bdev->md.al_offset = be32_to_cpu(buffer->al_offset);
	bdev->md.bm_offset = be32_to_cpu(buffer->bm_offset);

	अगर (check_activity_log_stripe_size(device, buffer, &bdev->md))
		जाओ err;
	अगर (check_offsets_and_sizes(device, bdev))
		जाओ err;

	अगर (be32_to_cpu(buffer->bm_offset) != bdev->md.bm_offset) अणु
		drbd_err(device, "unexpected bm_offset: %d (expected %d)\n",
		    be32_to_cpu(buffer->bm_offset), bdev->md.bm_offset);
		जाओ err;
	पूर्ण
	अगर (be32_to_cpu(buffer->md_size_sect) != bdev->md.md_size_sect) अणु
		drbd_err(device, "unexpected md_size: %u (expected %u)\n",
		    be32_to_cpu(buffer->md_size_sect), bdev->md.md_size_sect);
		जाओ err;
	पूर्ण

	rv = NO_ERROR;

	spin_lock_irq(&device->resource->req_lock);
	अगर (device->state.conn < C_CONNECTED) अणु
		अचिन्हित पूर्णांक peer;
		peer = be32_to_cpu(buffer->la_peer_max_bio_size);
		peer = max(peer, DRBD_MAX_BIO_SIZE_SAFE);
		device->peer_max_bio_size = peer;
	पूर्ण
	spin_unlock_irq(&device->resource->req_lock);

 err:
	drbd_md_put_buffer(device);

	वापस rv;
पूर्ण

/**
 * drbd_md_mark_dirty() - Mark meta data super block as dirty
 * @device:	DRBD device.
 *
 * Call this function अगर you change anything that should be written to
 * the meta-data super block. This function sets MD_सूचीTY, and starts a
 * समयr that ensures that within five seconds you have to call drbd_md_sync().
 */
व्योम drbd_md_mark_dirty(काष्ठा drbd_device *device)
अणु
	अगर (!test_and_set_bit(MD_सूचीTY, &device->flags))
		mod_समयr(&device->md_sync_समयr, jअगरfies + 5*HZ);
पूर्ण

व्योम drbd_uuid_move_history(काष्ठा drbd_device *device) __must_hold(local)
अणु
	पूर्णांक i;

	क्रम (i = UI_HISTORY_START; i < UI_HISTORY_END; i++)
		device->ldev->md.uuid[i+1] = device->ldev->md.uuid[i];
पूर्ण

व्योम __drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local)
अणु
	अगर (idx == UI_CURRENT) अणु
		अगर (device->state.role == R_PRIMARY)
			val |= 1;
		अन्यथा
			val &= ~((u64)1);

		drbd_set_ed_uuid(device, val);
	पूर्ण

	device->ldev->md.uuid[idx] = val;
	drbd_md_mark_dirty(device);
पूर्ण

व्योम _drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&device->ldev->md.uuid_lock, flags);
	__drbd_uuid_set(device, idx, val);
	spin_unlock_irqrestore(&device->ldev->md.uuid_lock, flags);
पूर्ण

व्योम drbd_uuid_set(काष्ठा drbd_device *device, पूर्णांक idx, u64 val) __must_hold(local)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&device->ldev->md.uuid_lock, flags);
	अगर (device->ldev->md.uuid[idx]) अणु
		drbd_uuid_move_history(device);
		device->ldev->md.uuid[UI_HISTORY_START] = device->ldev->md.uuid[idx];
	पूर्ण
	__drbd_uuid_set(device, idx, val);
	spin_unlock_irqrestore(&device->ldev->md.uuid_lock, flags);
पूर्ण

/**
 * drbd_uuid_new_current() - Creates a new current UUID
 * @device:	DRBD device.
 *
 * Creates a new current UUID, and rotates the old current UUID पूर्णांकo
 * the biपंचांगap slot. Causes an incremental resync upon next connect.
 */
व्योम drbd_uuid_new_current(काष्ठा drbd_device *device) __must_hold(local)
अणु
	u64 val;
	अचिन्हित दीर्घ दीर्घ bm_uuid;

	get_अक्रमom_bytes(&val, माप(u64));

	spin_lock_irq(&device->ldev->md.uuid_lock);
	bm_uuid = device->ldev->md.uuid[UI_BITMAP];

	अगर (bm_uuid)
		drbd_warn(device, "bm UUID was already set: %llX\n", bm_uuid);

	device->ldev->md.uuid[UI_BITMAP] = device->ldev->md.uuid[UI_CURRENT];
	__drbd_uuid_set(device, UI_CURRENT, val);
	spin_unlock_irq(&device->ldev->md.uuid_lock);

	drbd_prपूर्णांक_uuids(device, "new current UUID");
	/* get it to stable storage _now_ */
	drbd_md_sync(device);
पूर्ण

व्योम drbd_uuid_set_bm(काष्ठा drbd_device *device, u64 val) __must_hold(local)
अणु
	अचिन्हित दीर्घ flags;
	अगर (device->ldev->md.uuid[UI_BITMAP] == 0 && val == 0)
		वापस;

	spin_lock_irqsave(&device->ldev->md.uuid_lock, flags);
	अगर (val == 0) अणु
		drbd_uuid_move_history(device);
		device->ldev->md.uuid[UI_HISTORY_START] = device->ldev->md.uuid[UI_BITMAP];
		device->ldev->md.uuid[UI_BITMAP] = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ bm_uuid = device->ldev->md.uuid[UI_BITMAP];
		अगर (bm_uuid)
			drbd_warn(device, "bm UUID was already set: %llX\n", bm_uuid);

		device->ldev->md.uuid[UI_BITMAP] = val & ~((u64)1);
	पूर्ण
	spin_unlock_irqrestore(&device->ldev->md.uuid_lock, flags);

	drbd_md_mark_dirty(device);
पूर्ण

/**
 * drbd_bmio_set_n_ग_लिखो() - io_fn क्रम drbd_queue_biपंचांगap_io() or drbd_biपंचांगap_io()
 * @device:	DRBD device.
 *
 * Sets all bits in the biपंचांगap and ग_लिखोs the whole biपंचांगap to stable storage.
 */
पूर्णांक drbd_bmio_set_n_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local)
अणु
	पूर्णांक rv = -EIO;

	drbd_md_set_flag(device, MDF_FULL_SYNC);
	drbd_md_sync(device);
	drbd_bm_set_all(device);

	rv = drbd_bm_ग_लिखो(device);

	अगर (!rv) अणु
		drbd_md_clear_flag(device, MDF_FULL_SYNC);
		drbd_md_sync(device);
	पूर्ण

	वापस rv;
पूर्ण

/**
 * drbd_bmio_clear_n_ग_लिखो() - io_fn क्रम drbd_queue_biपंचांगap_io() or drbd_biपंचांगap_io()
 * @device:	DRBD device.
 *
 * Clears all bits in the biपंचांगap and ग_लिखोs the whole biपंचांगap to stable storage.
 */
पूर्णांक drbd_bmio_clear_n_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local)
अणु
	drbd_resume_al(device);
	drbd_bm_clear_all(device);
	वापस drbd_bm_ग_लिखो(device);
पूर्ण

अटल पूर्णांक w_biपंचांगap_io(काष्ठा drbd_work *w, पूर्णांक unused)
अणु
	काष्ठा drbd_device *device =
		container_of(w, काष्ठा drbd_device, bm_io_work.w);
	काष्ठा bm_io_work *work = &device->bm_io_work;
	पूर्णांक rv = -EIO;

	अगर (work->flags != BM_LOCKED_CHANGE_ALLOWED) अणु
		पूर्णांक cnt = atomic_पढ़ो(&device->ap_bio_cnt);
		अगर (cnt)
			drbd_err(device, "FIXME: ap_bio_cnt %d, expected 0; queued for '%s'\n",
					cnt, work->why);
	पूर्ण

	अगर (get_ldev(device)) अणु
		drbd_bm_lock(device, work->why, work->flags);
		rv = work->io_fn(device);
		drbd_bm_unlock(device);
		put_ldev(device);
	पूर्ण

	clear_bit_unlock(BITMAP_IO, &device->flags);
	wake_up(&device->misc_रुको);

	अगर (work->करोne)
		work->करोne(device, rv);

	clear_bit(BITMAP_IO_QUEUED, &device->flags);
	work->why = शून्य;
	work->flags = 0;

	वापस 0;
पूर्ण

/**
 * drbd_queue_biपंचांगap_io() - Queues an IO operation on the whole biपंचांगap
 * @device:	DRBD device.
 * @io_fn:	IO callback to be called when biपंचांगap IO is possible
 * @करोne:	callback to be called after the biपंचांगap IO was perक्रमmed
 * @why:	Descriptive text of the reason क्रम करोing the IO
 * @flags:	Biपंचांगap flags
 *
 * While IO on the biपंचांगap happens we मुक्तze application IO thus we ensure
 * that drbd_set_out_of_sync() can not be called. This function MAY ONLY be
 * called from worker context. It MUST NOT be used जबतक a previous such
 * work is still pending!
 *
 * Its worker function enबंदs the call of io_fn() by get_ldev() and
 * put_ldev().
 */
व्योम drbd_queue_biपंचांगap_io(काष्ठा drbd_device *device,
			  पूर्णांक (*io_fn)(काष्ठा drbd_device *),
			  व्योम (*करोne)(काष्ठा drbd_device *, पूर्णांक),
			  अक्षर *why, क्रमागत bm_flag flags)
अणु
	D_ASSERT(device, current == first_peer_device(device)->connection->worker.task);

	D_ASSERT(device, !test_bit(BITMAP_IO_QUEUED, &device->flags));
	D_ASSERT(device, !test_bit(BITMAP_IO, &device->flags));
	D_ASSERT(device, list_empty(&device->bm_io_work.w.list));
	अगर (device->bm_io_work.why)
		drbd_err(device, "FIXME going to queue '%s' but '%s' still pending?\n",
			why, device->bm_io_work.why);

	device->bm_io_work.io_fn = io_fn;
	device->bm_io_work.करोne = करोne;
	device->bm_io_work.why = why;
	device->bm_io_work.flags = flags;

	spin_lock_irq(&device->resource->req_lock);
	set_bit(BITMAP_IO, &device->flags);
	/* करोn't रुको क्रम pending application IO अगर the caller indicates that
	 * application IO करोes not conflict anyways. */
	अगर (flags == BM_LOCKED_CHANGE_ALLOWED || atomic_पढ़ो(&device->ap_bio_cnt) == 0) अणु
		अगर (!test_and_set_bit(BITMAP_IO_QUEUED, &device->flags))
			drbd_queue_work(&first_peer_device(device)->connection->sender_work,
					&device->bm_io_work.w);
	पूर्ण
	spin_unlock_irq(&device->resource->req_lock);
पूर्ण

/**
 * drbd_biपंचांगap_io() -  Does an IO operation on the whole biपंचांगap
 * @device:	DRBD device.
 * @io_fn:	IO callback to be called when biपंचांगap IO is possible
 * @why:	Descriptive text of the reason क्रम करोing the IO
 * @flags:	Biपंचांगap flags
 *
 * मुक्तzes application IO जबतक that the actual IO operations runs. This
 * functions MAY NOT be called from worker context.
 */
पूर्णांक drbd_biपंचांगap_io(काष्ठा drbd_device *device, पूर्णांक (*io_fn)(काष्ठा drbd_device *),
		अक्षर *why, क्रमागत bm_flag flags)
अणु
	/* Only suspend io, अगर some operation is supposed to be locked out */
	स्थिर bool करो_suspend_io = flags & (BM_DONT_CLEAR|BM_DONT_SET|BM_DONT_TEST);
	पूर्णांक rv;

	D_ASSERT(device, current != first_peer_device(device)->connection->worker.task);

	अगर (करो_suspend_io)
		drbd_suspend_io(device);

	drbd_bm_lock(device, why, flags);
	rv = io_fn(device);
	drbd_bm_unlock(device);

	अगर (करो_suspend_io)
		drbd_resume_io(device);

	वापस rv;
पूर्ण

व्योम drbd_md_set_flag(काष्ठा drbd_device *device, पूर्णांक flag) __must_hold(local)
अणु
	अगर ((device->ldev->md.flags & flag) != flag) अणु
		drbd_md_mark_dirty(device);
		device->ldev->md.flags |= flag;
	पूर्ण
पूर्ण

व्योम drbd_md_clear_flag(काष्ठा drbd_device *device, पूर्णांक flag) __must_hold(local)
अणु
	अगर ((device->ldev->md.flags & flag) != 0) अणु
		drbd_md_mark_dirty(device);
		device->ldev->md.flags &= ~flag;
	पूर्ण
पूर्ण
पूर्णांक drbd_md_test_flag(काष्ठा drbd_backing_dev *bdev, पूर्णांक flag)
अणु
	वापस (bdev->md.flags & flag) != 0;
पूर्ण

अटल व्योम md_sync_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा drbd_device *device = from_समयr(device, t, md_sync_समयr);
	drbd_device_post_work(device, MD_SYNC);
पूर्ण

स्थिर अक्षर *cmdname(क्रमागत drbd_packet cmd)
अणु
	/* THINK may need to become several global tables
	 * when we want to support more than
	 * one PRO_VERSION */
	अटल स्थिर अक्षर *cmdnames[] = अणु
		[P_DATA]	        = "Data",
		[P_WSAME]	        = "WriteSame",
		[P_TRIM]	        = "Trim",
		[P_DATA_REPLY]	        = "DataReply",
		[P_RS_DATA_REPLY]	= "RSDataReply",
		[P_BARRIER]	        = "Barrier",
		[P_BITMAP]	        = "ReportBitMap",
		[P_BECOME_SYNC_TARGET]  = "BecomeSyncTarget",
		[P_BECOME_SYNC_SOURCE]  = "BecomeSyncSource",
		[P_UNPLUG_REMOTE]	= "UnplugRemote",
		[P_DATA_REQUEST]	= "DataRequest",
		[P_RS_DATA_REQUEST]     = "RSDataRequest",
		[P_SYNC_PARAM]	        = "SyncParam",
		[P_SYNC_PARAM89]	= "SyncParam89",
		[P_PROTOCOL]            = "ReportProtocol",
		[P_UUIDS]	        = "ReportUUIDs",
		[P_SIZES]	        = "ReportSizes",
		[P_STATE]	        = "ReportState",
		[P_SYNC_UUID]           = "ReportSyncUUID",
		[P_AUTH_CHALLENGE]      = "AuthChallenge",
		[P_AUTH_RESPONSE]	= "AuthResponse",
		[P_PING]		= "Ping",
		[P_PING_ACK]	        = "PingAck",
		[P_RECV_ACK]	        = "RecvAck",
		[P_WRITE_ACK]	        = "WriteAck",
		[P_RS_WRITE_ACK]	= "RSWriteAck",
		[P_SUPERSEDED]          = "Superseded",
		[P_NEG_ACK]	        = "NegAck",
		[P_NEG_DREPLY]	        = "NegDReply",
		[P_NEG_RS_DREPLY]	= "NegRSDReply",
		[P_BARRIER_ACK]	        = "BarrierAck",
		[P_STATE_CHG_REQ]       = "StateChgRequest",
		[P_STATE_CHG_REPLY]     = "StateChgReply",
		[P_OV_REQUEST]          = "OVRequest",
		[P_OV_REPLY]            = "OVReply",
		[P_OV_RESULT]           = "OVResult",
		[P_CSUM_RS_REQUEST]     = "CsumRSRequest",
		[P_RS_IS_IN_SYNC]	= "CsumRSIsInSync",
		[P_COMPRESSED_BITMAP]   = "CBitmap",
		[P_DELAY_PROBE]         = "DelayProbe",
		[P_OUT_OF_SYNC]		= "OutOfSync",
		[P_RETRY_WRITE]		= "RetryWrite",
		[P_RS_CANCEL]		= "RSCancel",
		[P_CONN_ST_CHG_REQ]	= "conn_st_chg_req",
		[P_CONN_ST_CHG_REPLY]	= "conn_st_chg_reply",
		[P_PROTOCOL_UPDATE]	= "protocol_update",
		[P_RS_THIN_REQ]         = "rs_thin_req",
		[P_RS_DEALLOCATED]      = "rs_deallocated",

		/* क्रमागत drbd_packet, but not commands - obsoleted flags:
		 *	P_MAY_IGNORE
		 *	P_MAX_OPT_CMD
		 */
	पूर्ण;

	/* too big क्रम the array: 0xfffX */
	अगर (cmd == P_INITIAL_META)
		वापस "InitialMeta";
	अगर (cmd == P_INITIAL_DATA)
		वापस "InitialData";
	अगर (cmd == P_CONNECTION_FEATURES)
		वापस "ConnectionFeatures";
	अगर (cmd >= ARRAY_SIZE(cmdnames))
		वापस "Unknown";
	वापस cmdnames[cmd];
पूर्ण

/**
 * drbd_रुको_misc  -  रुको क्रम a request to make progress
 * @device:	device associated with the request
 * @i:		the काष्ठा drbd_पूर्णांकerval embedded in काष्ठा drbd_request or
 *		काष्ठा drbd_peer_request
 */
पूर्णांक drbd_रुको_misc(काष्ठा drbd_device *device, काष्ठा drbd_पूर्णांकerval *i)
अणु
	काष्ठा net_conf *nc;
	DEFINE_WAIT(रुको);
	दीर्घ समयout;

	rcu_पढ़ो_lock();
	nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस -ETIMEDOUT;
	पूर्ण
	समयout = nc->ko_count ? nc->समयout * HZ / 10 * nc->ko_count : MAX_SCHEDULE_TIMEOUT;
	rcu_पढ़ो_unlock();

	/* Indicate to wake up device->misc_रुको on progress.  */
	i->रुकोing = true;
	prepare_to_रुको(&device->misc_रुको, &रुको, TASK_INTERRUPTIBLE);
	spin_unlock_irq(&device->resource->req_lock);
	समयout = schedule_समयout(समयout);
	finish_रुको(&device->misc_रुको, &रुको);
	spin_lock_irq(&device->resource->req_lock);
	अगर (!समयout || device->state.conn < C_CONNECTED)
		वापस -ETIMEDOUT;
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

व्योम lock_all_resources(व्योम)
अणु
	काष्ठा drbd_resource *resource;
	पूर्णांक __maybe_unused i = 0;

	mutex_lock(&resources_mutex);
	local_irq_disable();
	क्रम_each_resource(resource, &drbd_resources)
		spin_lock_nested(&resource->req_lock, i++);
पूर्ण

व्योम unlock_all_resources(व्योम)
अणु
	काष्ठा drbd_resource *resource;

	क्रम_each_resource(resource, &drbd_resources)
		spin_unlock(&resource->req_lock);
	local_irq_enable();
	mutex_unlock(&resources_mutex);
पूर्ण

#अगर_घोषित CONFIG_DRBD_FAULT_INJECTION
/* Fault insertion support including अक्रमom number generator shamelessly
 * stolen from kernel/rcutorture.c */
काष्ठा fault_अक्रमom_state अणु
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ count;
पूर्ण;

#घोषणा FAULT_RANDOM_MULT 39916801  /* prime */
#घोषणा FAULT_RANDOM_ADD	479001701 /* prime */
#घोषणा FAULT_RANDOM_REFRESH 10000

/*
 * Crude but fast अक्रमom-number generator.  Uses a linear congruential
 * generator, with occasional help from get_अक्रमom_bytes().
 */
अटल अचिन्हित दीर्घ
_drbd_fault_अक्रमom(काष्ठा fault_अक्रमom_state *rsp)
अणु
	दीर्घ refresh;

	अगर (!rsp->count--) अणु
		get_अक्रमom_bytes(&refresh, माप(refresh));
		rsp->state += refresh;
		rsp->count = FAULT_RANDOM_REFRESH;
	पूर्ण
	rsp->state = rsp->state * FAULT_RANDOM_MULT + FAULT_RANDOM_ADD;
	वापस swahw32(rsp->state);
पूर्ण

अटल अक्षर *
_drbd_fault_str(अचिन्हित पूर्णांक type) अणु
	अटल अक्षर *_faults[] = अणु
		[DRBD_FAULT_MD_WR] = "Meta-data write",
		[DRBD_FAULT_MD_RD] = "Meta-data read",
		[DRBD_FAULT_RS_WR] = "Resync write",
		[DRBD_FAULT_RS_RD] = "Resync read",
		[DRBD_FAULT_DT_WR] = "Data write",
		[DRBD_FAULT_DT_RD] = "Data read",
		[DRBD_FAULT_DT_RA] = "Data read ahead",
		[DRBD_FAULT_BM_ALLOC] = "BM allocation",
		[DRBD_FAULT_AL_EE] = "EE allocation",
		[DRBD_FAULT_RECEIVE] = "receive data corruption",
	पूर्ण;

	वापस (type < DRBD_FAULT_MAX) ? _faults[type] : "**Unknown**";
पूर्ण

अचिन्हित पूर्णांक
_drbd_insert_fault(काष्ठा drbd_device *device, अचिन्हित पूर्णांक type)
अणु
	अटल काष्ठा fault_अक्रमom_state rrs = अणु0, 0पूर्ण;

	अचिन्हित पूर्णांक ret = (
		(drbd_fault_devs == 0 ||
			((1 << device_to_minor(device)) & drbd_fault_devs) != 0) &&
		(((_drbd_fault_अक्रमom(&rrs) % 100) + 1) <= drbd_fault_rate));

	अगर (ret) अणु
		drbd_fault_count++;

		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_warn(device, "***Simulating %s failure\n",
				_drbd_fault_str(type));
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

स्थिर अक्षर *drbd_buildtag(व्योम)
अणु
	/* DRBD built from बाह्यal sources has here a reference to the
	   git hash of the source code. */

	अटल अक्षर buildtag[38] = "\0uilt-in";

	अगर (buildtag[0] == 0) अणु
#अगर_घोषित MODULE
		प्र_लिखो(buildtag, "srcversion: %-24s", THIS_MODULE->srcversion);
#अन्यथा
		buildtag[0] = 'b';
#पूर्ण_अगर
	पूर्ण

	वापस buildtag;
पूर्ण

module_init(drbd_init)
module_निकास(drbd_cleanup)

EXPORT_SYMBOL(drbd_conn_str);
EXPORT_SYMBOL(drbd_role_str);
EXPORT_SYMBOL(drbd_disk_str);
EXPORT_SYMBOL(drbd_set_st_err_str);
