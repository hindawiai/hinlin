<शैली गुरु>
/* Copyright 2009 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "qman_test.h"

#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>

/*
 * Algorithm:
 *
 * Each cpu will have HP_PER_CPU "handlers" set up, each of which incorporates
 * an rx/tx pair of FQ objects (both of which are stashed on dequeue). The
 * organisation of FQIDs is such that the HP_PER_CPU*NUM_CPUS handlers will
 * shuttle a "hot potato" frame around them such that every क्रमwarding action
 * moves it from one cpu to another. (The use of more than one handler per cpu
 * is to allow enough handlers/FQs to truly test the signअगरicance of caching -
 * ie. when cache-expiries are occurring.)
 *
 * The "hot potato" frame content will be HP_NUM_WORDS*4 bytes in size, and the
 * first and last words of the frame data will undergo a transक्रमmation step on
 * each क्रमwarding action. To achieve this, each handler will be asचिन्हित a
 * 32-bit "mixer", that is produced using a 32-bit LFSR. When a frame is
 * received by a handler, the mixer of the expected sender is XOR'd पूर्णांकo all
 * words of the entire frame, which is then validated against the original
 * values. Then, beक्रमe क्रमwarding, the entire frame is XOR'd with the mixer of
 * the current handler. Apart from validating that the frame is taking the
 * expected path, this also provides some quasi-realistic overheads to each
 * क्रमwarding action - dereferencing *all* the frame data, computation, and
 * conditional branching. There is a "special" handler designated to act as the
 * instigator of the test by creating an enqueuing the "hot potato" frame, and
 * to determine when the test has completed by counting HP_LOOPS iterations.
 *
 * Init phases:
 *
 * 1. prepare each cpu's 'hp_cpu' काष्ठा using on_each_cpu(,,1) and link them
 *    पूर्णांकo 'hp_cpu_list'. Specअगरically, set processor_id, allocate HP_PER_CPU
 *    handlers and link-list them (but करो no other handler setup).
 *
 * 2. scan over 'hp_cpu_list' HP_PER_CPU बार, the first समय sets each
 *    hp_cpu's 'iterator' to poपूर्णांक to its first handler. With each loop,
 *    allocate rx/tx FQIDs and mixer values to the hp_cpu's iterator handler
 *    and advance the iterator क्रम the next loop. This includes a final fixup,
 *    which connects the last handler to the first (and which is why phase 2
 *    and 3 are separate).
 *
 * 3. scan over 'hp_cpu_list' HP_PER_CPU बार, the first समय sets each
 *    hp_cpu's 'iterator' to poपूर्णांक to its first handler. With each loop,
 *    initialise FQ objects and advance the iterator क्रम the next loop.
 *    Moreover, करो this initialisation on the cpu it applies to so that Rx FQ
 *    initialisation tarमाला_लो the correct cpu.
 */

/*
 * helper to run something on all cpus (can't use on_each_cpu(), as that invokes
 * the fn from irq context, which is too restrictive).
 */
काष्ठा bstrap अणु
	पूर्णांक (*fn)(व्योम);
	atomic_t started;
पूर्ण;
अटल पूर्णांक bstrap_fn(व्योम *bs)
अणु
	काष्ठा bstrap *bstrap = bs;
	पूर्णांक err;

	atomic_inc(&bstrap->started);
	err = bstrap->fn();
	अगर (err)
		वापस err;
	जबतक (!kthपढ़ो_should_stop())
		msleep(20);
	वापस 0;
पूर्ण
अटल पूर्णांक on_all_cpus(पूर्णांक (*fn)(व्योम))
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, cpu_online_mask) अणु
		काष्ठा bstrap bstrap = अणु
			.fn = fn,
			.started = ATOMIC_INIT(0)
		पूर्ण;
		काष्ठा task_काष्ठा *k = kthपढ़ो_create(bstrap_fn, &bstrap,
			"hotpotato%d", cpu);
		पूर्णांक ret;

		अगर (IS_ERR(k))
			वापस -ENOMEM;
		kthपढ़ो_bind(k, cpu);
		wake_up_process(k);
		/*
		 * If we call kthपढ़ो_stop() beक्रमe the "wake up" has had an
		 * effect, then the thपढ़ो may निकास with -EINTR without ever
		 * running the function. So poll until it's started beक्रमe
		 * requesting it to stop.
		 */
		जबतक (!atomic_पढ़ो(&bstrap.started))
			msleep(20);
		ret = kthपढ़ो_stop(k);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा hp_handler अणु

	/* The following data is stashed when 'rx' is dequeued; */
	/* -------------- */
	/* The Rx FQ, dequeues of which will stash the entire hp_handler */
	काष्ठा qman_fq rx;
	/* The Tx FQ we should क्रमward to */
	काष्ठा qman_fq tx;
	/* The value we XOR post-dequeue, prior to validating */
	u32 rx_mixer;
	/* The value we XOR pre-enqueue, after validating */
	u32 tx_mixer;
	/* what the hotpotato address should be on dequeue */
	dma_addr_t addr;
	u32 *frame_ptr;

	/* The following data isn't (necessarily) stashed on dequeue; */
	/* -------------- */
	u32 fqid_rx, fqid_tx;
	/* list node क्रम linking us पूर्णांकo 'hp_cpu' */
	काष्ठा list_head node;
	/* Just to check ... */
	अचिन्हित पूर्णांक processor_id;
पूर्ण ____cacheline_aligned;

काष्ठा hp_cpu अणु
	/* identअगरy the cpu we run on; */
	अचिन्हित पूर्णांक processor_id;
	/* root node क्रम the per-cpu list of handlers */
	काष्ठा list_head handlers;
	/* list node क्रम linking us पूर्णांकo 'hp_cpu_list' */
	काष्ठा list_head node;
	/*
	 * when repeatedly scanning 'hp_list', each time linking the n'th
	 * handlers together, this is used as per-cpu iterator state
	 */
	काष्ठा hp_handler *iterator;
पूर्ण;

/* Each cpu has one of these */
अटल DEFINE_PER_CPU(काष्ठा hp_cpu, hp_cpus);

/* links together the hp_cpu काष्ठाs, in first-come first-serve order. */
अटल LIST_HEAD(hp_cpu_list);
अटल DEFINE_SPINLOCK(hp_lock);

अटल अचिन्हित पूर्णांक hp_cpu_list_length;

/* the "special" handler, that starts and terminates the test. */
अटल काष्ठा hp_handler *special_handler;
अटल पूर्णांक loop_counter;

/* handlers are allocated out of this, so they're properly aligned. */
अटल काष्ठा kmem_cache *hp_handler_slab;

/* this is the frame data */
अटल व्योम *__frame_ptr;
अटल u32 *frame_ptr;
अटल dma_addr_t frame_dma;

/* needed क्रम dma_map*() */
अटल स्थिर काष्ठा qm_portal_config *pcfg;

/* the मुख्य function रुकोs on this */
अटल DECLARE_WAIT_QUEUE_HEAD(queue);

#घोषणा HP_PER_CPU	2
#घोषणा HP_LOOPS	8
/* 80 bytes, like a small ethernet frame, and bleeds पूर्णांकo a second cacheline */
#घोषणा HP_NUM_WORDS	80
/* First word of the LFSR-based frame data */
#घोषणा HP_FIRST_WORD	0xabbaf00d

अटल अंतरभूत u32 करो_lfsr(u32 prev)
अणु
	वापस (prev >> 1) ^ (-(prev & 1u) & 0xd0000001u);
पूर्ण

अटल पूर्णांक allocate_frame_data(व्योम)
अणु
	u32 lfsr = HP_FIRST_WORD;
	पूर्णांक loop;

	अगर (!qman_dma_portal) अणु
		pr_crit("portal not available\n");
		वापस -EIO;
	पूर्ण

	pcfg = qman_get_qm_portal_config(qman_dma_portal);

	__frame_ptr = kदो_स्मृति(4 * HP_NUM_WORDS, GFP_KERNEL);
	अगर (!__frame_ptr)
		वापस -ENOMEM;

	frame_ptr = PTR_ALIGN(__frame_ptr, 64);
	क्रम (loop = 0; loop < HP_NUM_WORDS; loop++) अणु
		frame_ptr[loop] = lfsr;
		lfsr = करो_lfsr(lfsr);
	पूर्ण

	frame_dma = dma_map_single(pcfg->dev, frame_ptr, 4 * HP_NUM_WORDS,
				   DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(pcfg->dev, frame_dma)) अणु
		pr_crit("dma mapping failure\n");
		kमुक्त(__frame_ptr);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम deallocate_frame_data(व्योम)
अणु
	dma_unmap_single(pcfg->dev, frame_dma, 4 * HP_NUM_WORDS,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(__frame_ptr);
पूर्ण

अटल अंतरभूत पूर्णांक process_frame_data(काष्ठा hp_handler *handler,
				     स्थिर काष्ठा qm_fd *fd)
अणु
	u32 *p = handler->frame_ptr;
	u32 lfsr = HP_FIRST_WORD;
	पूर्णांक loop;

	अगर (qm_fd_addr_get64(fd) != handler->addr) अणु
		pr_crit("bad frame address, [%llX != %llX]\n",
			qm_fd_addr_get64(fd), handler->addr);
		वापस -EIO;
	पूर्ण
	क्रम (loop = 0; loop < HP_NUM_WORDS; loop++, p++) अणु
		*p ^= handler->rx_mixer;
		अगर (*p != lfsr) अणु
			pr_crit("corrupt frame data");
			वापस -EIO;
		पूर्ण
		*p ^= handler->tx_mixer;
		lfsr = करो_lfsr(lfsr);
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result normal_dqrr(काष्ठा qman_portal *portal,
					    काष्ठा qman_fq *fq,
					    स्थिर काष्ठा qm_dqrr_entry *dqrr,
					    bool sched_napi)
अणु
	काष्ठा hp_handler *handler = (काष्ठा hp_handler *)fq;

	अगर (process_frame_data(handler, &dqrr->fd)) अणु
		WARN_ON(1);
		जाओ skip;
	पूर्ण
	अगर (qman_enqueue(&handler->tx, &dqrr->fd)) अणु
		pr_crit("qman_enqueue() failed");
		WARN_ON(1);
	पूर्ण
skip:
	वापस qman_cb_dqrr_consume;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result special_dqrr(काष्ठा qman_portal *portal,
					     काष्ठा qman_fq *fq,
					     स्थिर काष्ठा qm_dqrr_entry *dqrr,
					     bool sched_napi)
अणु
	काष्ठा hp_handler *handler = (काष्ठा hp_handler *)fq;

	process_frame_data(handler, &dqrr->fd);
	अगर (++loop_counter < HP_LOOPS) अणु
		अगर (qman_enqueue(&handler->tx, &dqrr->fd)) अणु
			pr_crit("qman_enqueue() failed");
			WARN_ON(1);
			जाओ skip;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("Received final (%dth) frame\n", loop_counter);
		wake_up(&queue);
	पूर्ण
skip:
	वापस qman_cb_dqrr_consume;
पूर्ण

अटल पूर्णांक create_per_cpu_handlers(व्योम)
अणु
	काष्ठा hp_handler *handler;
	पूर्णांक loop;
	काष्ठा hp_cpu *hp_cpu = this_cpu_ptr(&hp_cpus);

	hp_cpu->processor_id = smp_processor_id();
	spin_lock(&hp_lock);
	list_add_tail(&hp_cpu->node, &hp_cpu_list);
	hp_cpu_list_length++;
	spin_unlock(&hp_lock);
	INIT_LIST_HEAD(&hp_cpu->handlers);
	क्रम (loop = 0; loop < HP_PER_CPU; loop++) अणु
		handler = kmem_cache_alloc(hp_handler_slab, GFP_KERNEL);
		अगर (!handler) अणु
			pr_crit("kmem_cache_alloc() failed");
			WARN_ON(1);
			वापस -EIO;
		पूर्ण
		handler->processor_id = hp_cpu->processor_id;
		handler->addr = frame_dma;
		handler->frame_ptr = frame_ptr;
		list_add_tail(&handler->node, &hp_cpu->handlers);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक destroy_per_cpu_handlers(व्योम)
अणु
	काष्ठा list_head *loop, *पंचांगp;
	काष्ठा hp_cpu *hp_cpu = this_cpu_ptr(&hp_cpus);

	spin_lock(&hp_lock);
	list_del(&hp_cpu->node);
	spin_unlock(&hp_lock);
	list_क्रम_each_safe(loop, पंचांगp, &hp_cpu->handlers) अणु
		u32 flags = 0;
		काष्ठा hp_handler *handler = list_entry(loop, काष्ठा hp_handler,
							node);
		अगर (qman_retire_fq(&handler->rx, &flags) ||
		    (flags & QMAN_FQ_STATE_BLOCKOOS)) अणु
			pr_crit("qman_retire_fq(rx) failed, flags: %x", flags);
			WARN_ON(1);
			वापस -EIO;
		पूर्ण
		अगर (qman_oos_fq(&handler->rx)) अणु
			pr_crit("qman_oos_fq(rx) failed");
			WARN_ON(1);
			वापस -EIO;
		पूर्ण
		qman_destroy_fq(&handler->rx);
		qman_destroy_fq(&handler->tx);
		qman_release_fqid(handler->fqid_rx);
		list_del(&handler->node);
		kmem_cache_मुक्त(hp_handler_slab, handler);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u8 num_cachelines(u32 offset)
अणु
	u8 res = (offset + (L1_CACHE_BYTES - 1))
			 / (L1_CACHE_BYTES);
	अगर (res > 3)
		वापस 3;
	वापस res;
पूर्ण
#घोषणा STASH_DATA_CL \
	num_cachelines(HP_NUM_WORDS * 4)
#घोषणा STASH_CTX_CL \
	num_cachelines(दुरत्व(काष्ठा hp_handler, fqid_rx))

अटल पूर्णांक init_handler(व्योम *h)
अणु
	काष्ठा qm_mcc_initfq opts;
	काष्ठा hp_handler *handler = h;
	पूर्णांक err;

	अगर (handler->processor_id != smp_processor_id()) अणु
		err = -EIO;
		जाओ failed;
	पूर्ण
	/* Set up rx */
	स_रखो(&handler->rx, 0, माप(handler->rx));
	अगर (handler == special_handler)
		handler->rx.cb.dqrr = special_dqrr;
	अन्यथा
		handler->rx.cb.dqrr = normal_dqrr;
	err = qman_create_fq(handler->fqid_rx, 0, &handler->rx);
	अगर (err) अणु
		pr_crit("qman_create_fq(rx) failed");
		जाओ failed;
	पूर्ण
	स_रखो(&opts, 0, माप(opts));
	opts.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTRL |
				   QM_INITFQ_WE_CONTEXTA);
	opts.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_CTXASTASHING);
	qm_fqd_set_stashing(&opts.fqd, 0, STASH_DATA_CL, STASH_CTX_CL);
	err = qman_init_fq(&handler->rx, QMAN_INITFQ_FLAG_SCHED |
			   QMAN_INITFQ_FLAG_LOCAL, &opts);
	अगर (err) अणु
		pr_crit("qman_init_fq(rx) failed");
		जाओ failed;
	पूर्ण
	/* Set up tx */
	स_रखो(&handler->tx, 0, माप(handler->tx));
	err = qman_create_fq(handler->fqid_tx, QMAN_FQ_FLAG_NO_MODIFY,
			     &handler->tx);
	अगर (err) अणु
		pr_crit("qman_create_fq(tx) failed");
		जाओ failed;
	पूर्ण

	वापस 0;
failed:
	वापस err;
पूर्ण

अटल व्योम init_handler_cb(व्योम *h)
अणु
	अगर (init_handler(h))
		WARN_ON(1);
पूर्ण

अटल पूर्णांक init_phase2(व्योम)
अणु
	पूर्णांक loop;
	u32 fqid = 0;
	u32 lfsr = 0xdeadbeef;
	काष्ठा hp_cpu *hp_cpu;
	काष्ठा hp_handler *handler;

	क्रम (loop = 0; loop < HP_PER_CPU; loop++) अणु
		list_क्रम_each_entry(hp_cpu, &hp_cpu_list, node) अणु
			पूर्णांक err;

			अगर (!loop)
				hp_cpu->iterator = list_first_entry(
						&hp_cpu->handlers,
						काष्ठा hp_handler, node);
			अन्यथा
				hp_cpu->iterator = list_entry(
						hp_cpu->iterator->node.next,
						काष्ठा hp_handler, node);
			/* Rx FQID is the previous handler's Tx FQID */
			hp_cpu->iterator->fqid_rx = fqid;
			/* Allocate new FQID क्रम Tx */
			err = qman_alloc_fqid(&fqid);
			अगर (err) अणु
				pr_crit("qman_alloc_fqid() failed");
				वापस err;
			पूर्ण
			hp_cpu->iterator->fqid_tx = fqid;
			/* Rx mixer is the previous handler's Tx mixer */
			hp_cpu->iterator->rx_mixer = lfsr;
			/* Get new mixer क्रम Tx */
			lfsr = करो_lfsr(lfsr);
			hp_cpu->iterator->tx_mixer = lfsr;
		पूर्ण
	पूर्ण
	/* Fix up the first handler (fqid_rx==0, rx_mixer=0xdeadbeef) */
	hp_cpu = list_first_entry(&hp_cpu_list, काष्ठा hp_cpu, node);
	handler = list_first_entry(&hp_cpu->handlers, काष्ठा hp_handler, node);
	अगर (handler->fqid_rx != 0 || handler->rx_mixer != 0xdeadbeef)
		वापस 1;
	handler->fqid_rx = fqid;
	handler->rx_mixer = lfsr;
	/* and tag it as our "special" handler */
	special_handler = handler;
	वापस 0;
पूर्ण

अटल पूर्णांक init_phase3(व्योम)
अणु
	पूर्णांक loop, err;
	काष्ठा hp_cpu *hp_cpu;

	क्रम (loop = 0; loop < HP_PER_CPU; loop++) अणु
		list_क्रम_each_entry(hp_cpu, &hp_cpu_list, node) अणु
			अगर (!loop)
				hp_cpu->iterator = list_first_entry(
						&hp_cpu->handlers,
						काष्ठा hp_handler, node);
			अन्यथा
				hp_cpu->iterator = list_entry(
						hp_cpu->iterator->node.next,
						काष्ठा hp_handler, node);
			preempt_disable();
			अगर (hp_cpu->processor_id == smp_processor_id()) अणु
				err = init_handler(hp_cpu->iterator);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				smp_call_function_single(hp_cpu->processor_id,
					init_handler_cb, hp_cpu->iterator, 1);
			पूर्ण
			preempt_enable();
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_first_frame(व्योम *ignore)
अणु
	u32 *p = special_handler->frame_ptr;
	u32 lfsr = HP_FIRST_WORD;
	पूर्णांक loop, err;
	काष्ठा qm_fd fd;

	अगर (special_handler->processor_id != smp_processor_id()) अणु
		err = -EIO;
		जाओ failed;
	पूर्ण
	स_रखो(&fd, 0, माप(fd));
	qm_fd_addr_set64(&fd, special_handler->addr);
	qm_fd_set_contig_big(&fd, HP_NUM_WORDS * 4);
	क्रम (loop = 0; loop < HP_NUM_WORDS; loop++, p++) अणु
		अगर (*p != lfsr) अणु
			err = -EIO;
			pr_crit("corrupt frame data");
			जाओ failed;
		पूर्ण
		*p ^= special_handler->tx_mixer;
		lfsr = करो_lfsr(lfsr);
	पूर्ण
	pr_info("Sending first frame\n");
	err = qman_enqueue(&special_handler->tx, &fd);
	अगर (err) अणु
		pr_crit("qman_enqueue() failed");
		जाओ failed;
	पूर्ण

	वापस 0;
failed:
	वापस err;
पूर्ण

अटल व्योम send_first_frame_cb(व्योम *ignore)
अणु
	अगर (send_first_frame(शून्य))
		WARN_ON(1);
पूर्ण

पूर्णांक qman_test_stash(व्योम)
अणु
	पूर्णांक err;

	अगर (cpumask_weight(cpu_online_mask) < 2) अणु
		pr_info("%s(): skip - only 1 CPU\n", __func__);
		वापस 0;
	पूर्ण

	pr_info("%s(): Starting\n", __func__);

	hp_cpu_list_length = 0;
	loop_counter = 0;
	hp_handler_slab = kmem_cache_create("hp_handler_slab",
			माप(काष्ठा hp_handler), L1_CACHE_BYTES,
			SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!hp_handler_slab) अणु
		err = -EIO;
		pr_crit("kmem_cache_create() failed");
		जाओ failed;
	पूर्ण

	err = allocate_frame_data();
	अगर (err)
		जाओ failed;

	/* Init phase 1 */
	pr_info("Creating %d handlers per cpu...\n", HP_PER_CPU);
	अगर (on_all_cpus(create_per_cpu_handlers)) अणु
		err = -EIO;
		pr_crit("on_each_cpu() failed");
		जाओ failed;
	पूर्ण
	pr_info("Number of cpus: %d, total of %d handlers\n",
		hp_cpu_list_length, hp_cpu_list_length * HP_PER_CPU);

	err = init_phase2();
	अगर (err)
		जाओ failed;

	err = init_phase3();
	अगर (err)
		जाओ failed;

	preempt_disable();
	अगर (special_handler->processor_id == smp_processor_id()) अणु
		err = send_first_frame(शून्य);
		अगर (err)
			जाओ failed;
	पूर्ण अन्यथा अणु
		smp_call_function_single(special_handler->processor_id,
					 send_first_frame_cb, शून्य, 1);
	पूर्ण
	preempt_enable();

	रुको_event(queue, loop_counter == HP_LOOPS);
	deallocate_frame_data();
	अगर (on_all_cpus(destroy_per_cpu_handlers)) अणु
		err = -EIO;
		pr_crit("on_each_cpu() failed");
		जाओ failed;
	पूर्ण
	kmem_cache_destroy(hp_handler_slab);
	pr_info("%s(): Finished\n", __func__);

	वापस 0;
failed:
	WARN_ON(1);
	वापस err;
पूर्ण
