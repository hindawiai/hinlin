<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* bpf/cpumap.c
 *
 * Copyright (c) 2017 Jesper Dangaard Brouer, Red Hat Inc.
 */

/* The 'cpumap' is primarily used as a backend map क्रम XDP BPF helper
 * call bpf_redirect_map() and XDP_REसूचीECT action, like 'devmap'.
 *
 * Unlike devmap which redirects XDP frames out another NIC device,
 * this map type redirects raw XDP frames to another CPU.  The remote
 * CPU will करो SKB-allocation and call the normal network stack.
 *
 * This is a scalability and isolation mechanism, that allow
 * separating the early driver network XDP layer, from the rest of the
 * netstack, and assigning dedicated CPUs क्रम this stage.  This
 * basically allows क्रम 10G wirespeed pre-filtering via bpf.
 */
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/ptr_ring.h>
#समावेश <net/xdp.h>

#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/capability.h>
#समावेश <trace/events/xdp.h>

#समावेश <linux/netdevice.h>   /* netअगर_receive_skb_list */
#समावेश <linux/etherdevice.h> /* eth_type_trans */

/* General idea: XDP packets getting XDP redirected to another CPU,
 * will maximum be stored/queued क्रम one driver ->poll() call.  It is
 * guaranteed that queueing the frame and the flush operation happen on
 * same CPU.  Thus, cpu_map_flush operation can deduct via this_cpu_ptr()
 * which queue in bpf_cpu_map_entry contains packets.
 */

#घोषणा CPU_MAP_BULK_SIZE 8  /* 8 == one cacheline on 64-bit archs */
काष्ठा bpf_cpu_map_entry;
काष्ठा bpf_cpu_map;

काष्ठा xdp_bulk_queue अणु
	व्योम *q[CPU_MAP_BULK_SIZE];
	काष्ठा list_head flush_node;
	काष्ठा bpf_cpu_map_entry *obj;
	अचिन्हित पूर्णांक count;
पूर्ण;

/* Struct क्रम every remote "destination" CPU in map */
काष्ठा bpf_cpu_map_entry अणु
	u32 cpu;    /* kthपढ़ो CPU and map index */
	पूर्णांक map_id; /* Back reference to map */

	/* XDP can run multiple RX-ring queues, need __percpu enqueue store */
	काष्ठा xdp_bulk_queue __percpu *bulkq;

	काष्ठा bpf_cpu_map *cmap;

	/* Queue with potential multi-producers, and single-consumer kthपढ़ो */
	काष्ठा ptr_ring *queue;
	काष्ठा task_काष्ठा *kthपढ़ो;

	काष्ठा bpf_cpumap_val value;
	काष्ठा bpf_prog *prog;

	atomic_t refcnt; /* Control when this काष्ठा can be मुक्त'ed */
	काष्ठा rcu_head rcu;

	काष्ठा work_काष्ठा kthपढ़ो_stop_wq;
पूर्ण;

काष्ठा bpf_cpu_map अणु
	काष्ठा bpf_map map;
	/* Below members specअगरic क्रम map type */
	काष्ठा bpf_cpu_map_entry **cpu_map;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा list_head, cpu_map_flush_list);

अटल काष्ठा bpf_map *cpu_map_alloc(जोड़ bpf_attr *attr)
अणु
	u32 value_size = attr->value_size;
	काष्ठा bpf_cpu_map *cmap;
	पूर्णांक err = -ENOMEM;

	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	/* check sanity of attributes */
	अगर (attr->max_entries == 0 || attr->key_size != 4 ||
	    (value_size != दुरत्वend(काष्ठा bpf_cpumap_val, qsize) &&
	     value_size != दुरत्वend(काष्ठा bpf_cpumap_val, bpf_prog.fd)) ||
	    attr->map_flags & ~BPF_F_NUMA_NODE)
		वापस ERR_PTR(-EINVAL);

	cmap = kzalloc(माप(*cmap), GFP_USER | __GFP_ACCOUNT);
	अगर (!cmap)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&cmap->map, attr);

	/* Pre-limit array size based on NR_CPUS, not final CPU check */
	अगर (cmap->map.max_entries > NR_CPUS) अणु
		err = -E2BIG;
		जाओ मुक्त_cmap;
	पूर्ण

	/* Alloc array क्रम possible remote "destination" CPUs */
	cmap->cpu_map = bpf_map_area_alloc(cmap->map.max_entries *
					   माप(काष्ठा bpf_cpu_map_entry *),
					   cmap->map.numa_node);
	अगर (!cmap->cpu_map)
		जाओ मुक्त_cmap;

	वापस &cmap->map;
मुक्त_cmap:
	kमुक्त(cmap);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम get_cpu_map_entry(काष्ठा bpf_cpu_map_entry *rcpu)
अणु
	atomic_inc(&rcpu->refcnt);
पूर्ण

/* called from workqueue, to workaround syscall using preempt_disable */
अटल व्योम cpu_map_kthपढ़ो_stop(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_cpu_map_entry *rcpu;

	rcpu = container_of(work, काष्ठा bpf_cpu_map_entry, kthपढ़ो_stop_wq);

	/* Wait क्रम flush in __cpu_map_entry_मुक्त(), via full RCU barrier,
	 * as it रुकोs until all in-flight call_rcu() callbacks complete.
	 */
	rcu_barrier();

	/* kthपढ़ो_stop will wake_up_process and रुको क्रम it to complete */
	kthपढ़ो_stop(rcpu->kthपढ़ो);
पूर्ण

अटल व्योम __cpu_map_ring_cleanup(काष्ठा ptr_ring *ring)
अणु
	/* The tear-करोwn procedure should have made sure that queue is
	 * empty.  See __cpu_map_entry_replace() and work-queue
	 * invoked cpu_map_kthपढ़ो_stop(). Catch any broken behaviour
	 * gracefully and warn once.
	 */
	काष्ठा xdp_frame *xdpf;

	जबतक ((xdpf = ptr_ring_consume(ring)))
		अगर (WARN_ON_ONCE(xdpf))
			xdp_वापस_frame(xdpf);
पूर्ण

अटल व्योम put_cpu_map_entry(काष्ठा bpf_cpu_map_entry *rcpu)
अणु
	अगर (atomic_dec_and_test(&rcpu->refcnt)) अणु
		अगर (rcpu->prog)
			bpf_prog_put(rcpu->prog);
		/* The queue should be empty at this poपूर्णांक */
		__cpu_map_ring_cleanup(rcpu->queue);
		ptr_ring_cleanup(rcpu->queue, शून्य);
		kमुक्त(rcpu->queue);
		kमुक्त(rcpu);
	पूर्ण
पूर्ण

अटल पूर्णांक cpu_map_bpf_prog_run_xdp(काष्ठा bpf_cpu_map_entry *rcpu,
				    व्योम **frames, पूर्णांक n,
				    काष्ठा xdp_cpumap_stats *stats)
अणु
	काष्ठा xdp_rxq_info rxq;
	काष्ठा xdp_buff xdp;
	पूर्णांक i, nframes = 0;

	अगर (!rcpu->prog)
		वापस n;

	rcu_पढ़ो_lock_bh();

	xdp_set_वापस_frame_no_direct();
	xdp.rxq = &rxq;

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		u32 act;
		पूर्णांक err;

		rxq.dev = xdpf->dev_rx;
		rxq.mem = xdpf->mem;
		/* TODO: report queue_index to xdp_rxq_info */

		xdp_convert_frame_to_buff(xdpf, &xdp);

		act = bpf_prog_run_xdp(rcpu->prog, &xdp);
		चयन (act) अणु
		हाल XDP_PASS:
			err = xdp_update_frame_from_buff(&xdp, xdpf);
			अगर (err < 0) अणु
				xdp_वापस_frame(xdpf);
				stats->drop++;
			पूर्ण अन्यथा अणु
				frames[nframes++] = xdpf;
				stats->pass++;
			पूर्ण
			अवरोध;
		हाल XDP_REसूचीECT:
			err = xdp_करो_redirect(xdpf->dev_rx, &xdp,
					      rcpu->prog);
			अगर (unlikely(err)) अणु
				xdp_वापस_frame(xdpf);
				stats->drop++;
			पूर्ण अन्यथा अणु
				stats->redirect++;
			पूर्ण
			अवरोध;
		शेष:
			bpf_warn_invalid_xdp_action(act);
			fallthrough;
		हाल XDP_DROP:
			xdp_वापस_frame(xdpf);
			stats->drop++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stats->redirect)
		xdp_करो_flush_map();

	xdp_clear_वापस_frame_no_direct();

	rcu_पढ़ो_unlock_bh(); /* resched poपूर्णांक, may call करो_softirq() */

	वापस nframes;
पूर्ण

#घोषणा CPUMAP_BATCH 8

अटल पूर्णांक cpu_map_kthपढ़ो_run(व्योम *data)
अणु
	काष्ठा bpf_cpu_map_entry *rcpu = data;

	set_current_state(TASK_INTERRUPTIBLE);

	/* When kthपढ़ो gives stop order, then rcpu have been disconnected
	 * from map, thus no new packets can enter. Reमुख्यing in-flight
	 * per CPU stored packets are flushed to this queue.  Wait honoring
	 * kthपढ़ो_stop संकेत until queue is empty.
	 */
	जबतक (!kthपढ़ो_should_stop() || !__ptr_ring_empty(rcpu->queue)) अणु
		काष्ठा xdp_cpumap_stats stats = अणुपूर्ण; /* zero stats */
		अचिन्हित पूर्णांक kmem_alloc_drops = 0, sched = 0;
		gfp_t gfp = __GFP_ZERO | GFP_ATOMIC;
		व्योम *frames[CPUMAP_BATCH];
		व्योम *skbs[CPUMAP_BATCH];
		पूर्णांक i, n, m, nframes;
		LIST_HEAD(list);

		/* Release CPU reschedule checks */
		अगर (__ptr_ring_empty(rcpu->queue)) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			/* Recheck to aव्योम lost wake-up */
			अगर (__ptr_ring_empty(rcpu->queue)) अणु
				schedule();
				sched = 1;
			पूर्ण अन्यथा अणु
				__set_current_state(TASK_RUNNING);
			पूर्ण
		पूर्ण अन्यथा अणु
			sched = cond_resched();
		पूर्ण

		/*
		 * The bpf_cpu_map_entry is single consumer, with this
		 * kthपढ़ो CPU pinned. Lockless access to ptr_ring
		 * consume side valid as no-resize allowed of queue.
		 */
		n = __ptr_ring_consume_batched(rcpu->queue, frames,
					       CPUMAP_BATCH);
		क्रम (i = 0; i < n; i++) अणु
			व्योम *f = frames[i];
			काष्ठा page *page = virt_to_page(f);

			/* Bring काष्ठा page memory area to curr CPU. Read by
			 * build_skb_around via page_is_pfmeदो_स्मृति(), and when
			 * मुक्तd written by page_frag_मुक्त call.
			 */
			prefetchw(page);
		पूर्ण

		/* Support running another XDP prog on this CPU */
		nframes = cpu_map_bpf_prog_run_xdp(rcpu, frames, n, &stats);
		अगर (nframes) अणु
			m = kmem_cache_alloc_bulk(skbuff_head_cache, gfp, nframes, skbs);
			अगर (unlikely(m == 0)) अणु
				क्रम (i = 0; i < nframes; i++)
					skbs[i] = शून्य; /* effect: xdp_वापस_frame */
				kmem_alloc_drops += nframes;
			पूर्ण
		पूर्ण

		local_bh_disable();
		क्रम (i = 0; i < nframes; i++) अणु
			काष्ठा xdp_frame *xdpf = frames[i];
			काष्ठा sk_buff *skb = skbs[i];

			skb = __xdp_build_skb_from_frame(xdpf, skb,
							 xdpf->dev_rx);
			अगर (!skb) अणु
				xdp_वापस_frame(xdpf);
				जारी;
			पूर्ण

			list_add_tail(&skb->list, &list);
		पूर्ण
		netअगर_receive_skb_list(&list);

		/* Feedback loop via tracepoपूर्णांक */
		trace_xdp_cpumap_kthपढ़ो(rcpu->map_id, n, kmem_alloc_drops,
					 sched, &stats);

		local_bh_enable(); /* resched poपूर्णांक, may call करो_softirq() */
	पूर्ण
	__set_current_state(TASK_RUNNING);

	put_cpu_map_entry(rcpu);
	वापस 0;
पूर्ण

bool cpu_map_prog_allowed(काष्ठा bpf_map *map)
अणु
	वापस map->map_type == BPF_MAP_TYPE_CPUMAP &&
	       map->value_size != दुरत्वend(काष्ठा bpf_cpumap_val, qsize);
पूर्ण

अटल पूर्णांक __cpu_map_load_bpf_program(काष्ठा bpf_cpu_map_entry *rcpu, पूर्णांक fd)
अणु
	काष्ठा bpf_prog *prog;

	prog = bpf_prog_get_type(fd, BPF_PROG_TYPE_XDP);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (prog->expected_attach_type != BPF_XDP_CPUMAP) अणु
		bpf_prog_put(prog);
		वापस -EINVAL;
	पूर्ण

	rcpu->value.bpf_prog.id = prog->aux->id;
	rcpu->prog = prog;

	वापस 0;
पूर्ण

अटल काष्ठा bpf_cpu_map_entry *
__cpu_map_entry_alloc(काष्ठा bpf_map *map, काष्ठा bpf_cpumap_val *value,
		      u32 cpu)
अणु
	पूर्णांक numa, err, i, fd = value->bpf_prog.fd;
	gfp_t gfp = GFP_KERNEL | __GFP_NOWARN;
	काष्ठा bpf_cpu_map_entry *rcpu;
	काष्ठा xdp_bulk_queue *bq;

	/* Have map->numa_node, but choose node of redirect target CPU */
	numa = cpu_to_node(cpu);

	rcpu = bpf_map_kदो_स्मृति_node(map, माप(*rcpu), gfp | __GFP_ZERO, numa);
	अगर (!rcpu)
		वापस शून्य;

	/* Alloc percpu bulkq */
	rcpu->bulkq = bpf_map_alloc_percpu(map, माप(*rcpu->bulkq),
					   माप(व्योम *), gfp);
	अगर (!rcpu->bulkq)
		जाओ मुक्त_rcu;

	क्रम_each_possible_cpu(i) अणु
		bq = per_cpu_ptr(rcpu->bulkq, i);
		bq->obj = rcpu;
	पूर्ण

	/* Alloc queue */
	rcpu->queue = bpf_map_kदो_स्मृति_node(map, माप(*rcpu->queue), gfp,
					   numa);
	अगर (!rcpu->queue)
		जाओ मुक्त_bulkq;

	err = ptr_ring_init(rcpu->queue, value->qsize, gfp);
	अगर (err)
		जाओ मुक्त_queue;

	rcpu->cpu    = cpu;
	rcpu->map_id = map->id;
	rcpu->value.qsize  = value->qsize;

	अगर (fd > 0 && __cpu_map_load_bpf_program(rcpu, fd))
		जाओ मुक्त_ptr_ring;

	/* Setup kthपढ़ो */
	rcpu->kthपढ़ो = kthपढ़ो_create_on_node(cpu_map_kthपढ़ो_run, rcpu, numa,
					       "cpumap/%d/map:%d", cpu,
					       map->id);
	अगर (IS_ERR(rcpu->kthपढ़ो))
		जाओ मुक्त_prog;

	get_cpu_map_entry(rcpu); /* 1-refcnt क्रम being in cmap->cpu_map[] */
	get_cpu_map_entry(rcpu); /* 1-refcnt क्रम kthपढ़ो */

	/* Make sure kthपढ़ो runs on a single CPU */
	kthपढ़ो_bind(rcpu->kthपढ़ो, cpu);
	wake_up_process(rcpu->kthपढ़ो);

	वापस rcpu;

मुक्त_prog:
	अगर (rcpu->prog)
		bpf_prog_put(rcpu->prog);
मुक्त_ptr_ring:
	ptr_ring_cleanup(rcpu->queue, शून्य);
मुक्त_queue:
	kमुक्त(rcpu->queue);
मुक्त_bulkq:
	मुक्त_percpu(rcpu->bulkq);
मुक्त_rcu:
	kमुक्त(rcpu);
	वापस शून्य;
पूर्ण

अटल व्योम __cpu_map_entry_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_cpu_map_entry *rcpu;

	/* This cpu_map_entry have been disconnected from map and one
	 * RCU grace-period have elapsed.  Thus, XDP cannot queue any
	 * new packets and cannot change/set flush_needed that can
	 * find this entry.
	 */
	rcpu = container_of(rcu, काष्ठा bpf_cpu_map_entry, rcu);

	मुक्त_percpu(rcpu->bulkq);
	/* Cannot kthपढ़ो_stop() here, last put मुक्त rcpu resources */
	put_cpu_map_entry(rcpu);
पूर्ण

/* After xchg poपूर्णांकer to bpf_cpu_map_entry, use the call_rcu() to
 * ensure any driver rcu critical sections have completed, but this
 * करोes not guarantee a flush has happened yet. Because driver side
 * rcu_पढ़ो_lock/unlock only protects the running XDP program.  The
 * atomic xchg and शून्य-ptr check in __cpu_map_flush() makes sure a
 * pending flush op करोesn't fail.
 *
 * The bpf_cpu_map_entry is still used by the kthपढ़ो, and there can
 * still be pending packets (in queue and percpu bulkq).  A refcnt
 * makes sure to last user (kthपढ़ो_stop vs. call_rcu) मुक्त memory
 * resources.
 *
 * The rcu callback __cpu_map_entry_मुक्त flush reमुख्यing packets in
 * percpu bulkq to queue.  Due to caller map_delete_elem() disable
 * preemption, cannot call kthपढ़ो_stop() to make sure queue is empty.
 * Instead a work_queue is started क्रम stopping kthपढ़ो,
 * cpu_map_kthपढ़ो_stop, which रुकोs क्रम an RCU grace period beक्रमe
 * stopping kthपढ़ो, emptying the queue.
 */
अटल व्योम __cpu_map_entry_replace(काष्ठा bpf_cpu_map *cmap,
				    u32 key_cpu, काष्ठा bpf_cpu_map_entry *rcpu)
अणु
	काष्ठा bpf_cpu_map_entry *old_rcpu;

	old_rcpu = xchg(&cmap->cpu_map[key_cpu], rcpu);
	अगर (old_rcpu) अणु
		call_rcu(&old_rcpu->rcu, __cpu_map_entry_मुक्त);
		INIT_WORK(&old_rcpu->kthपढ़ो_stop_wq, cpu_map_kthपढ़ो_stop);
		schedule_work(&old_rcpu->kthपढ़ो_stop_wq);
	पूर्ण
पूर्ण

अटल पूर्णांक cpu_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_cpu_map *cmap = container_of(map, काष्ठा bpf_cpu_map, map);
	u32 key_cpu = *(u32 *)key;

	अगर (key_cpu >= map->max_entries)
		वापस -EINVAL;

	/* notice caller map_delete_elem() use preempt_disable() */
	__cpu_map_entry_replace(cmap, key_cpu, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक cpu_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			       u64 map_flags)
अणु
	काष्ठा bpf_cpu_map *cmap = container_of(map, काष्ठा bpf_cpu_map, map);
	काष्ठा bpf_cpumap_val cpumap_value = अणुपूर्ण;
	काष्ठा bpf_cpu_map_entry *rcpu;
	/* Array index key correspond to CPU number */
	u32 key_cpu = *(u32 *)key;

	स_नकल(&cpumap_value, value, map->value_size);

	अगर (unlikely(map_flags > BPF_EXIST))
		वापस -EINVAL;
	अगर (unlikely(key_cpu >= cmap->map.max_entries))
		वापस -E2BIG;
	अगर (unlikely(map_flags == BPF_NOEXIST))
		वापस -EEXIST;
	अगर (unlikely(cpumap_value.qsize > 16384)) /* sanity limit on qsize */
		वापस -EOVERFLOW;

	/* Make sure CPU is a valid possible cpu */
	अगर (key_cpu >= nr_cpumask_bits || !cpu_possible(key_cpu))
		वापस -ENODEV;

	अगर (cpumap_value.qsize == 0) अणु
		rcpu = शून्य; /* Same as deleting */
	पूर्ण अन्यथा अणु
		/* Updating qsize cause re-allocation of bpf_cpu_map_entry */
		rcpu = __cpu_map_entry_alloc(map, &cpumap_value, key_cpu);
		अगर (!rcpu)
			वापस -ENOMEM;
		rcpu->cmap = cmap;
	पूर्ण
	rcu_पढ़ो_lock();
	__cpu_map_entry_replace(cmap, key_cpu, rcpu);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल व्योम cpu_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_cpu_map *cmap = container_of(map, काष्ठा bpf_cpu_map, map);
	u32 i;

	/* At this poपूर्णांक bpf_prog->aux->refcnt == 0 and this map->refcnt == 0,
	 * so the bpf programs (can be more than one that used this map) were
	 * disconnected from events. Wait क्रम outstanding critical sections in
	 * these programs to complete. The rcu critical section only guarantees
	 * no further "XDP/bpf-side" पढ़ोs against bpf_cpu_map->cpu_map.
	 * It करोes __not__ ensure pending flush operations (अगर any) are
	 * complete.
	 */

	synchronize_rcu();

	/* For cpu_map the remote CPUs can still be using the entries
	 * (काष्ठा bpf_cpu_map_entry).
	 */
	क्रम (i = 0; i < cmap->map.max_entries; i++) अणु
		काष्ठा bpf_cpu_map_entry *rcpu;

		rcpu = READ_ONCE(cmap->cpu_map[i]);
		अगर (!rcpu)
			जारी;

		/* bq flush and cleanup happens after RCU grace-period */
		__cpu_map_entry_replace(cmap, i, शून्य); /* call_rcu */
	पूर्ण
	bpf_map_area_मुक्त(cmap->cpu_map);
	kमुक्त(cmap);
पूर्ण

अटल व्योम *__cpu_map_lookup_elem(काष्ठा bpf_map *map, u32 key)
अणु
	काष्ठा bpf_cpu_map *cmap = container_of(map, काष्ठा bpf_cpu_map, map);
	काष्ठा bpf_cpu_map_entry *rcpu;

	अगर (key >= map->max_entries)
		वापस शून्य;

	rcpu = READ_ONCE(cmap->cpu_map[key]);
	वापस rcpu;
पूर्ण

अटल व्योम *cpu_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_cpu_map_entry *rcpu =
		__cpu_map_lookup_elem(map, *(u32 *)key);

	वापस rcpu ? &rcpu->value : शून्य;
पूर्ण

अटल पूर्णांक cpu_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा bpf_cpu_map *cmap = container_of(map, काष्ठा bpf_cpu_map, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	अगर (index >= cmap->map.max_entries) अणु
		*next = 0;
		वापस 0;
	पूर्ण

	अगर (index == cmap->map.max_entries - 1)
		वापस -ENOENT;
	*next = index + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक cpu_map_redirect(काष्ठा bpf_map *map, u32 अगरindex, u64 flags)
अणु
	वापस __bpf_xdp_redirect_map(map, अगरindex, flags, __cpu_map_lookup_elem);
पूर्ण

अटल पूर्णांक cpu_map_btf_id;
स्थिर काष्ठा bpf_map_ops cpu_map_ops = अणु
	.map_meta_equal		= bpf_map_meta_equal,
	.map_alloc		= cpu_map_alloc,
	.map_मुक्त		= cpu_map_मुक्त,
	.map_delete_elem	= cpu_map_delete_elem,
	.map_update_elem	= cpu_map_update_elem,
	.map_lookup_elem	= cpu_map_lookup_elem,
	.map_get_next_key	= cpu_map_get_next_key,
	.map_check_btf		= map_check_no_btf,
	.map_btf_name		= "bpf_cpu_map",
	.map_btf_id		= &cpu_map_btf_id,
	.map_redirect		= cpu_map_redirect,
पूर्ण;

अटल व्योम bq_flush_to_queue(काष्ठा xdp_bulk_queue *bq)
अणु
	काष्ठा bpf_cpu_map_entry *rcpu = bq->obj;
	अचिन्हित पूर्णांक processed = 0, drops = 0;
	स्थिर पूर्णांक to_cpu = rcpu->cpu;
	काष्ठा ptr_ring *q;
	पूर्णांक i;

	अगर (unlikely(!bq->count))
		वापस;

	q = rcpu->queue;
	spin_lock(&q->producer_lock);

	क्रम (i = 0; i < bq->count; i++) अणु
		काष्ठा xdp_frame *xdpf = bq->q[i];
		पूर्णांक err;

		err = __ptr_ring_produce(q, xdpf);
		अगर (err) अणु
			drops++;
			xdp_वापस_frame_rx_napi(xdpf);
		पूर्ण
		processed++;
	पूर्ण
	bq->count = 0;
	spin_unlock(&q->producer_lock);

	__list_del_clearprev(&bq->flush_node);

	/* Feedback loop via tracepoपूर्णांकs */
	trace_xdp_cpumap_enqueue(rcpu->map_id, processed, drops, to_cpu);
पूर्ण

/* Runs under RCU-पढ़ो-side, plus in softirq under NAPI protection.
 * Thus, safe percpu variable access.
 */
अटल व्योम bq_enqueue(काष्ठा bpf_cpu_map_entry *rcpu, काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&cpu_map_flush_list);
	काष्ठा xdp_bulk_queue *bq = this_cpu_ptr(rcpu->bulkq);

	अगर (unlikely(bq->count == CPU_MAP_BULK_SIZE))
		bq_flush_to_queue(bq);

	/* Notice, xdp_buff/page MUST be queued here, दीर्घ enough क्रम
	 * driver to code invoking us to finished, due to driver
	 * (e.g. ixgbe) recycle tricks based on page-refcnt.
	 *
	 * Thus, incoming xdp_frame is always queued here (अन्यथा we race
	 * with another CPU on page-refcnt and reमुख्यing driver code).
	 * Queue समय is very लघु, as driver will invoke flush
	 * operation, when completing napi->poll call.
	 */
	bq->q[bq->count++] = xdpf;

	अगर (!bq->flush_node.prev)
		list_add(&bq->flush_node, flush_list);
पूर्ण

पूर्णांक cpu_map_enqueue(काष्ठा bpf_cpu_map_entry *rcpu, काष्ठा xdp_buff *xdp,
		    काष्ठा net_device *dev_rx)
अणु
	काष्ठा xdp_frame *xdpf;

	xdpf = xdp_convert_buff_to_frame(xdp);
	अगर (unlikely(!xdpf))
		वापस -EOVERFLOW;

	/* Info needed when स्थिरructing SKB on remote CPU */
	xdpf->dev_rx = dev_rx;

	bq_enqueue(rcpu, xdpf);
	वापस 0;
पूर्ण

व्योम __cpu_map_flush(व्योम)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&cpu_map_flush_list);
	काष्ठा xdp_bulk_queue *bq, *पंचांगp;

	list_क्रम_each_entry_safe(bq, पंचांगp, flush_list, flush_node) अणु
		bq_flush_to_queue(bq);

		/* If alपढ़ोy running, costs spin_lock_irqsave + smb_mb */
		wake_up_process(bq->obj->kthपढ़ो);
	पूर्ण
पूर्ण

अटल पूर्णांक __init cpu_map_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		INIT_LIST_HEAD(&per_cpu(cpu_map_flush_list, cpu));
	वापस 0;
पूर्ण

subsys_initcall(cpu_map_init);
