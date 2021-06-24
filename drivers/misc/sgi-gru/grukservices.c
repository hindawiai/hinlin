<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *              KERNEL SERVICES THAT USE THE GRU
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sync_core.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/io_apic.h>
#समावेश "gru.h"
#समावेश "grulib.h"
#समावेश "grutables.h"
#समावेश "grukservices.h"
#समावेश "gru_instructions.h"
#समावेश <यंत्र/uv/uv_hub.h>

/*
 * Kernel GRU Usage
 *
 * The following is an पूर्णांकerim algorithm क्रम management of kernel GRU
 * resources. This will likely be replaced when we better understand the
 * kernel/user requirements.
 *
 * Blade percpu resources reserved क्रम kernel use. These resources are
 * reserved whenever the the kernel context क्रम the blade is loaded. Note
 * that the kernel context is not guaranteed to be always available. It is
 * loaded on demand & can be stolen by a user अगर the user demand exceeds the
 * kernel demand. The kernel can always reload the kernel context but
 * a SLEEP may be required!!!.
 *
 * Async Overview:
 *
 * 	Each blade has one "kernel context" that owns GRU kernel resources
 * 	located on the blade. Kernel drivers use GRU resources in this context
 * 	क्रम sending messages, zeroing memory, etc.
 *
 * 	The kernel context is dynamically loaded on demand. If it is not in
 * 	use by the kernel, the kernel context can be unloaded & given to a user.
 * 	The kernel context will be reloaded when needed. This may require that
 * 	a context be stolen from a user.
 * 		NOTE: frequent unloading/reloading of the kernel context is
 * 		expensive. We are depending on batch schedulers, cpusets, sane
 * 		drivers or some other mechanism to prevent the need क्रम frequent
 *	 	stealing/reloading.
 *
 * 	The kernel context consists of two parts:
 * 		- 1 CB & a few DSRs that are reserved क्रम each cpu on the blade.
 * 		  Each cpu has it's own निजी resources & करोes not share them
 * 		  with other cpus. These resources are used serially, ie,
 * 		  locked, used & unlocked  on each call to a function in
 * 		  grukservices.
 * 		  	(Now that we have dynamic loading of kernel contexts, I
 * 		  	 may rethink this & allow sharing between cpus....)
 *
 *		- Additional resources can be reserved दीर्घ term & used directly
 *		  by UV drivers located in the kernel. Drivers using these GRU
 *		  resources can use asynchronous GRU inकाष्ठाions that send
 *		  पूर्णांकerrupts on completion.
 *		  	- these resources must be explicitly locked/unlocked
 *		  	- locked resources prevent (obviously) the kernel
 *		  	  context from being unloaded.
 *			- drivers using these resource directly issue their own
 *			  GRU inकाष्ठाion and must रुको/check completion.
 *
 * 		  When these resources are reserved, the caller can optionally
 * 		  associate a रुको_queue with the resources and use asynchronous
 * 		  GRU inकाष्ठाions. When an async GRU inकाष्ठाion completes, the
 * 		  driver will करो a wakeup on the event.
 *
 */


#घोषणा ASYNC_HAN_TO_BID(h)	((h) - 1)
#घोषणा ASYNC_BID_TO_HAN(b)	((b) + 1)
#घोषणा ASYNC_HAN_TO_BS(h)	gru_base[ASYNC_HAN_TO_BID(h)]

#घोषणा GRU_NUM_KERNEL_CBR	1
#घोषणा GRU_NUM_KERNEL_DSR_BYTES 256
#घोषणा GRU_NUM_KERNEL_DSR_CL	(GRU_NUM_KERNEL_DSR_BYTES /		\
					GRU_CACHE_LINE_BYTES)

/* GRU inकाष्ठाion attributes क्रम all inकाष्ठाions */
#घोषणा IMA			IMA_CB_DELAY

/* GRU cacheline size is always 64 bytes - even on arches with 128 byte lines */
#घोषणा __gru_cacheline_aligned__                               \
	__attribute__((__aligned__(GRU_CACHE_LINE_BYTES)))

#घोषणा MAGIC	0x1234567887654321UL

/* Default retry count क्रम GRU errors on kernel inकाष्ठाions */
#घोषणा EXCEPTION_RETRY_LIMIT	3

/* Status of message queue sections */
#घोषणा MQS_EMPTY		0
#घोषणा MQS_FULL		1
#घोषणा MQS_NOOP		2

/*----------------- RESOURCE MANAGEMENT -------------------------------------*/
/* optimized क्रम x86_64 */
काष्ठा message_queue अणु
	जोड़ gru_mesqhead	head __gru_cacheline_aligned__;	/* CL 0 */
	पूर्णांक			qlines;				/* DW 1 */
	दीर्घ 			hstatus[2];
	व्योम 			*next __gru_cacheline_aligned__;/* CL 1 */
	व्योम 			*limit;
	व्योम 			*start;
	व्योम 			*start2;
	अक्षर			data ____cacheline_aligned;	/* CL 2 */
पूर्ण;

/* First word in every message - used by mesq पूर्णांकerface */
काष्ठा message_header अणु
	अक्षर	present;
	अक्षर	present2;
	अक्षर 	lines;
	अक्षर	fill;
पूर्ण;

#घोषणा HSTATUS(mq, h)	((mq) + दुरत्व(काष्ठा message_queue, hstatus[h]))

/*
 * Reload the blade's kernel context पूर्णांकo a GRU chiplet. Called holding
 * the bs_kgts_sema क्रम READ. Will steal user contexts अगर necessary.
 */
अटल व्योम gru_load_kernel_context(काष्ठा gru_blade_state *bs, पूर्णांक blade_id)
अणु
	काष्ठा gru_state *gru;
	काष्ठा gru_thपढ़ो_state *kgts;
	व्योम *vaddr;
	पूर्णांक ctxnum, ncpus;

	up_पढ़ो(&bs->bs_kgts_sema);
	करोwn_ग_लिखो(&bs->bs_kgts_sema);

	अगर (!bs->bs_kgts) अणु
		करो अणु
			bs->bs_kgts = gru_alloc_gts(शून्य, 0, 0, 0, 0, 0);
			अगर (!IS_ERR(bs->bs_kgts))
				अवरोध;
			msleep(1);
		पूर्ण जबतक (true);
		bs->bs_kgts->ts_user_blade_id = blade_id;
	पूर्ण
	kgts = bs->bs_kgts;

	अगर (!kgts->ts_gru) अणु
		STAT(load_kernel_context);
		ncpus = uv_blade_nr_possible_cpus(blade_id);
		kgts->ts_cbr_au_count = GRU_CB_COUNT_TO_AU(
			GRU_NUM_KERNEL_CBR * ncpus + bs->bs_async_cbrs);
		kgts->ts_dsr_au_count = GRU_DS_BYTES_TO_AU(
			GRU_NUM_KERNEL_DSR_BYTES * ncpus +
				bs->bs_async_dsr_bytes);
		जबतक (!gru_assign_gru_context(kgts)) अणु
			msleep(1);
			gru_steal_context(kgts);
		पूर्ण
		gru_load_context(kgts);
		gru = bs->bs_kgts->ts_gru;
		vaddr = gru->gs_gru_base_vaddr;
		ctxnum = kgts->ts_ctxnum;
		bs->kernel_cb = get_gseg_base_address_cb(vaddr, ctxnum, 0);
		bs->kernel_dsr = get_gseg_base_address_ds(vaddr, ctxnum, 0);
	पूर्ण
	करोwngrade_ग_लिखो(&bs->bs_kgts_sema);
पूर्ण

/*
 * Free all kernel contexts that are not currently in use.
 *   Returns 0 अगर all मुक्तd, अन्यथा number of inuse context.
 */
अटल पूर्णांक gru_मुक्त_kernel_contexts(व्योम)
अणु
	काष्ठा gru_blade_state *bs;
	काष्ठा gru_thपढ़ो_state *kgts;
	पूर्णांक bid, ret = 0;

	क्रम (bid = 0; bid < GRU_MAX_BLADES; bid++) अणु
		bs = gru_base[bid];
		अगर (!bs)
			जारी;

		/* Ignore busy contexts. Don't want to block here.  */
		अगर (करोwn_ग_लिखो_trylock(&bs->bs_kgts_sema)) अणु
			kgts = bs->bs_kgts;
			अगर (kgts && kgts->ts_gru)
				gru_unload_context(kgts, 0);
			bs->bs_kgts = शून्य;
			up_ग_लिखो(&bs->bs_kgts_sema);
			kमुक्त(kgts);
		पूर्ण अन्यथा अणु
			ret++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Lock & load the kernel context क्रम the specअगरied blade.
 */
अटल काष्ठा gru_blade_state *gru_lock_kernel_context(पूर्णांक blade_id)
अणु
	काष्ठा gru_blade_state *bs;
	पूर्णांक bid;

	STAT(lock_kernel_context);
again:
	bid = blade_id < 0 ? uv_numa_blade_id() : blade_id;
	bs = gru_base[bid];

	/* Handle the हाल where migration occurred जबतक रुकोing क्रम the sema */
	करोwn_पढ़ो(&bs->bs_kgts_sema);
	अगर (blade_id < 0 && bid != uv_numa_blade_id()) अणु
		up_पढ़ो(&bs->bs_kgts_sema);
		जाओ again;
	पूर्ण
	अगर (!bs->bs_kgts || !bs->bs_kgts->ts_gru)
		gru_load_kernel_context(bs, bid);
	वापस bs;

पूर्ण

/*
 * Unlock the kernel context क्रम the specअगरied blade. Context is not
 * unloaded but may be stolen beक्रमe next use.
 */
अटल व्योम gru_unlock_kernel_context(पूर्णांक blade_id)
अणु
	काष्ठा gru_blade_state *bs;

	bs = gru_base[blade_id];
	up_पढ़ो(&bs->bs_kgts_sema);
	STAT(unlock_kernel_context);
पूर्ण

/*
 * Reserve & get poपूर्णांकers to the DSR/CBRs reserved क्रम the current cpu.
 * 	- वापसs with preemption disabled
 */
अटल पूर्णांक gru_get_cpu_resources(पूर्णांक dsr_bytes, व्योम **cb, व्योम **dsr)
अणु
	काष्ठा gru_blade_state *bs;
	पूर्णांक lcpu;

	BUG_ON(dsr_bytes > GRU_NUM_KERNEL_DSR_BYTES);
	preempt_disable();
	bs = gru_lock_kernel_context(-1);
	lcpu = uv_blade_processor_id();
	*cb = bs->kernel_cb + lcpu * GRU_HANDLE_STRIDE;
	*dsr = bs->kernel_dsr + lcpu * GRU_NUM_KERNEL_DSR_BYTES;
	वापस 0;
पूर्ण

/*
 * Free the current cpus reserved DSR/CBR resources.
 */
अटल व्योम gru_मुक्त_cpu_resources(व्योम *cb, व्योम *dsr)
अणु
	gru_unlock_kernel_context(uv_numa_blade_id());
	preempt_enable();
पूर्ण

/*
 * Reserve GRU resources to be used asynchronously.
 *   Note: currently supports only 1 reservation per blade.
 *
 * 	input:
 * 		blade_id  - blade on which resources should be reserved
 * 		cbrs	  - number of CBRs
 * 		dsr_bytes - number of DSR bytes needed
 *	output:
 *		handle to identअगरy resource
 *		(0 = async resources alपढ़ोy reserved)
 */
अचिन्हित दीर्घ gru_reserve_async_resources(पूर्णांक blade_id, पूर्णांक cbrs, पूर्णांक dsr_bytes,
			काष्ठा completion *cmp)
अणु
	काष्ठा gru_blade_state *bs;
	काष्ठा gru_thपढ़ो_state *kgts;
	पूर्णांक ret = 0;

	bs = gru_base[blade_id];

	करोwn_ग_लिखो(&bs->bs_kgts_sema);

	/* Verअगरy no resources alपढ़ोy reserved */
	अगर (bs->bs_async_dsr_bytes + bs->bs_async_cbrs)
		जाओ करोne;
	bs->bs_async_dsr_bytes = dsr_bytes;
	bs->bs_async_cbrs = cbrs;
	bs->bs_async_wq = cmp;
	kgts = bs->bs_kgts;

	/* Resources changed. Unload context अगर alपढ़ोy loaded */
	अगर (kgts && kgts->ts_gru)
		gru_unload_context(kgts, 0);
	ret = ASYNC_BID_TO_HAN(blade_id);

करोne:
	up_ग_लिखो(&bs->bs_kgts_sema);
	वापस ret;
पूर्ण

/*
 * Release async resources previously reserved.
 *
 *	input:
 *		han - handle to identअगरy resources
 */
व्योम gru_release_async_resources(अचिन्हित दीर्घ han)
अणु
	काष्ठा gru_blade_state *bs = ASYNC_HAN_TO_BS(han);

	करोwn_ग_लिखो(&bs->bs_kgts_sema);
	bs->bs_async_dsr_bytes = 0;
	bs->bs_async_cbrs = 0;
	bs->bs_async_wq = शून्य;
	up_ग_लिखो(&bs->bs_kgts_sema);
पूर्ण

/*
 * Wait क्रम async GRU inकाष्ठाions to complete.
 *
 *	input:
 *		han - handle to identअगरy resources
 */
व्योम gru_रुको_async_cbr(अचिन्हित दीर्घ han)
अणु
	काष्ठा gru_blade_state *bs = ASYNC_HAN_TO_BS(han);

	रुको_क्रम_completion(bs->bs_async_wq);
	mb();
पूर्ण

/*
 * Lock previous reserved async GRU resources
 *
 *	input:
 *		han - handle to identअगरy resources
 *	output:
 *		cb  - poपूर्णांकer to first CBR
 *		dsr - poपूर्णांकer to first DSR
 */
व्योम gru_lock_async_resource(अचिन्हित दीर्घ han,  व्योम **cb, व्योम **dsr)
अणु
	काष्ठा gru_blade_state *bs = ASYNC_HAN_TO_BS(han);
	पूर्णांक blade_id = ASYNC_HAN_TO_BID(han);
	पूर्णांक ncpus;

	gru_lock_kernel_context(blade_id);
	ncpus = uv_blade_nr_possible_cpus(blade_id);
	अगर (cb)
		*cb = bs->kernel_cb + ncpus * GRU_HANDLE_STRIDE;
	अगर (dsr)
		*dsr = bs->kernel_dsr + ncpus * GRU_NUM_KERNEL_DSR_BYTES;
पूर्ण

/*
 * Unlock previous reserved async GRU resources
 *
 *	input:
 *		han - handle to identअगरy resources
 */
व्योम gru_unlock_async_resource(अचिन्हित दीर्घ han)
अणु
	पूर्णांक blade_id = ASYNC_HAN_TO_BID(han);

	gru_unlock_kernel_context(blade_id);
पूर्ण

/*----------------------------------------------------------------------*/
पूर्णांक gru_get_cb_exception_detail(व्योम *cb,
		काष्ठा control_block_extended_exc_detail *excdet)
अणु
	काष्ठा gru_control_block_extended *cbe;
	काष्ठा gru_thपढ़ो_state *kgts = शून्य;
	अचिन्हित दीर्घ off;
	पूर्णांक cbrnum, bid;

	/*
	 * Locate kgts क्रम cb. This algorithm is SLOW but
	 * this function is rarely called (ie., almost never).
	 * Perक्रमmance करोes not matter.
	 */
	क्रम_each_possible_blade(bid) अणु
		अगर (!gru_base[bid])
			अवरोध;
		kgts = gru_base[bid]->bs_kgts;
		अगर (!kgts || !kgts->ts_gru)
			जारी;
		off = cb - kgts->ts_gru->gs_gru_base_vaddr;
		अगर (off < GRU_SIZE)
			अवरोध;
		kgts = शून्य;
	पूर्ण
	BUG_ON(!kgts);
	cbrnum = thपढ़ो_cbr_number(kgts, get_cb_number(cb));
	cbe = get_cbe(GRUBASE(cb), cbrnum);
	gru_flush_cache(cbe);	/* CBE not coherent */
	sync_core();
	excdet->opc = cbe->opccpy;
	excdet->exopc = cbe->exopccpy;
	excdet->ecause = cbe->ecause;
	excdet->exceptdet0 = cbe->idef1upd;
	excdet->exceptdet1 = cbe->idef3upd;
	gru_flush_cache(cbe);
	वापस 0;
पूर्ण

अटल अक्षर *gru_get_cb_exception_detail_str(पूर्णांक ret, व्योम *cb,
					     अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा gru_control_block_status *gen = (व्योम *)cb;
	काष्ठा control_block_extended_exc_detail excdet;

	अगर (ret > 0 && gen->istatus == CBS_EXCEPTION) अणु
		gru_get_cb_exception_detail(cb, &excdet);
		snम_लिखो(buf, size,
			"GRU:%d exception: cb %p, opc %d, exopc %d, ecause 0x%x,"
			"excdet0 0x%lx, excdet1 0x%x", smp_processor_id(),
			gen, excdet.opc, excdet.exopc, excdet.ecause,
			excdet.exceptdet0, excdet.exceptdet1);
	पूर्ण अन्यथा अणु
		snम_लिखो(buf, size, "No exception");
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक gru_रुको_idle_or_exception(काष्ठा gru_control_block_status *gen)
अणु
	जबतक (gen->istatus >= CBS_ACTIVE) अणु
		cpu_relax();
		barrier();
	पूर्ण
	वापस gen->istatus;
पूर्ण

अटल पूर्णांक gru_retry_exception(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *gen = (व्योम *)cb;
	काष्ठा control_block_extended_exc_detail excdet;
	पूर्णांक retry = EXCEPTION_RETRY_LIMIT;

	जबतक (1)  अणु
		अगर (gru_रुको_idle_or_exception(gen) == CBS_IDLE)
			वापस CBS_IDLE;
		अगर (gru_get_cb_message_queue_substatus(cb))
			वापस CBS_EXCEPTION;
		gru_get_cb_exception_detail(cb, &excdet);
		अगर ((excdet.ecause & ~EXCEPTION_RETRY_BITS) ||
				(excdet.cbrexecstatus & CBR_EXS_ABORT_OCC))
			अवरोध;
		अगर (retry-- == 0)
			अवरोध;
		gen->icmd = 1;
		gru_flush_cache(gen);
	पूर्ण
	वापस CBS_EXCEPTION;
पूर्ण

पूर्णांक gru_check_status_proc(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *gen = (व्योम *)cb;
	पूर्णांक ret;

	ret = gen->istatus;
	अगर (ret == CBS_EXCEPTION)
		ret = gru_retry_exception(cb);
	rmb();
	वापस ret;

पूर्ण

पूर्णांक gru_रुको_proc(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *gen = (व्योम *)cb;
	पूर्णांक ret;

	ret = gru_रुको_idle_or_exception(gen);
	अगर (ret == CBS_EXCEPTION)
		ret = gru_retry_exception(cb);
	rmb();
	वापस ret;
पूर्ण

अटल व्योम gru_पात(पूर्णांक ret, व्योम *cb, अक्षर *str)
अणु
	अक्षर buf[GRU_EXC_STR_SIZE];

	panic("GRU FATAL ERROR: %s - %s\n", str,
	      gru_get_cb_exception_detail_str(ret, cb, buf, माप(buf)));
पूर्ण

व्योम gru_रुको_पात_proc(व्योम *cb)
अणु
	पूर्णांक ret;

	ret = gru_रुको_proc(cb);
	अगर (ret)
		gru_पात(ret, cb, "gru_wait_abort");
पूर्ण


/*------------------------------ MESSAGE QUEUES -----------------------------*/

/* Internal status . These are NOT वापसed to the user. */
#घोषणा MQIE_AGAIN		-1	/* try again */


/*
 * Save/restore the "present" flag that is in the second line of 2-line
 * messages
 */
अटल अंतरभूत पूर्णांक get_present2(व्योम *p)
अणु
	काष्ठा message_header *mhdr = p + GRU_CACHE_LINE_BYTES;
	वापस mhdr->present;
पूर्ण

अटल अंतरभूत व्योम restore_present2(व्योम *p, पूर्णांक val)
अणु
	काष्ठा message_header *mhdr = p + GRU_CACHE_LINE_BYTES;
	mhdr->present = val;
पूर्ण

/*
 * Create a message queue.
 * 	qlines - message queue size in cache lines. Includes 2-line header.
 */
पूर्णांक gru_create_message_queue(काष्ठा gru_message_queue_desc *mqd,
		व्योम *p, अचिन्हित पूर्णांक bytes, पूर्णांक nasid, पूर्णांक vector, पूर्णांक apicid)
अणु
	काष्ठा message_queue *mq = p;
	अचिन्हित पूर्णांक qlines;

	qlines = bytes / GRU_CACHE_LINE_BYTES - 2;
	स_रखो(mq, 0, bytes);
	mq->start = &mq->data;
	mq->start2 = &mq->data + (qlines / 2 - 1) * GRU_CACHE_LINE_BYTES;
	mq->next = &mq->data;
	mq->limit = &mq->data + (qlines - 2) * GRU_CACHE_LINE_BYTES;
	mq->qlines = qlines;
	mq->hstatus[0] = 0;
	mq->hstatus[1] = 1;
	mq->head = gru_mesq_head(2, qlines / 2 + 1);
	mqd->mq = mq;
	mqd->mq_gpa = uv_gpa(mq);
	mqd->qlines = qlines;
	mqd->पूर्णांकerrupt_pnode = nasid >> 1;
	mqd->पूर्णांकerrupt_vector = vector;
	mqd->पूर्णांकerrupt_apicid = apicid;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gru_create_message_queue);

/*
 * Send a NOOP message to a message queue
 * 	Returns:
 * 		 0 - अगर queue is full after the send. This is the normal हाल
 * 		     but various races can change this.
 *		-1 - अगर mesq sent successfully but queue not full
 *		>0 - unexpected error. MQE_xxx वापसed
 */
अटल पूर्णांक send_noop_message(व्योम *cb, काष्ठा gru_message_queue_desc *mqd,
				व्योम *mesg)
अणु
	स्थिर काष्ठा message_header noop_header = अणु
					.present = MQS_NOOP, .lines = 1पूर्ण;
	अचिन्हित दीर्घ m;
	पूर्णांक substatus, ret;
	काष्ठा message_header save_mhdr, *mhdr = mesg;

	STAT(mesq_noop);
	save_mhdr = *mhdr;
	*mhdr = noop_header;
	gru_mesq(cb, mqd->mq_gpa, gru_get_tri(mhdr), 1, IMA);
	ret = gru_रुको(cb);

	अगर (ret) अणु
		substatus = gru_get_cb_message_queue_substatus(cb);
		चयन (substatus) अणु
		हाल CBSS_NO_ERROR:
			STAT(mesq_noop_unexpected_error);
			ret = MQE_UNEXPECTED_CB_ERR;
			अवरोध;
		हाल CBSS_LB_OVERFLOWED:
			STAT(mesq_noop_lb_overflow);
			ret = MQE_CONGESTION;
			अवरोध;
		हाल CBSS_QLIMIT_REACHED:
			STAT(mesq_noop_qlimit_reached);
			ret = 0;
			अवरोध;
		हाल CBSS_AMO_NACKED:
			STAT(mesq_noop_amo_nacked);
			ret = MQE_CONGESTION;
			अवरोध;
		हाल CBSS_PUT_NACKED:
			STAT(mesq_noop_put_nacked);
			m = mqd->mq_gpa + (gru_get_amo_value_head(cb) << 6);
			gru_vstore(cb, m, gru_get_tri(mesg), XTYPE_CL, 1, 1,
						IMA);
			अगर (gru_रुको(cb) == CBS_IDLE)
				ret = MQIE_AGAIN;
			अन्यथा
				ret = MQE_UNEXPECTED_CB_ERR;
			अवरोध;
		हाल CBSS_PAGE_OVERFLOW:
			STAT(mesq_noop_page_overflow);
			fallthrough;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
	*mhdr = save_mhdr;
	वापस ret;
पूर्ण

/*
 * Handle a gru_mesq full.
 */
अटल पूर्णांक send_message_queue_full(व्योम *cb, काष्ठा gru_message_queue_desc *mqd,
				व्योम *mesg, पूर्णांक lines)
अणु
	जोड़ gru_mesqhead mqh;
	अचिन्हित पूर्णांक limit, head;
	अचिन्हित दीर्घ avalue;
	पूर्णांक half, qlines;

	/* Determine अगर चयनing to first/second half of q */
	avalue = gru_get_amo_value(cb);
	head = gru_get_amo_value_head(cb);
	limit = gru_get_amo_value_limit(cb);

	qlines = mqd->qlines;
	half = (limit != qlines);

	अगर (half)
		mqh = gru_mesq_head(qlines / 2 + 1, qlines);
	अन्यथा
		mqh = gru_mesq_head(2, qlines / 2 + 1);

	/* Try to get lock क्रम चयनing head poपूर्णांकer */
	gru_gamir(cb, EOP_IR_CLR, HSTATUS(mqd->mq_gpa, half), XTYPE_DW, IMA);
	अगर (gru_रुको(cb) != CBS_IDLE)
		जाओ cberr;
	अगर (!gru_get_amo_value(cb)) अणु
		STAT(mesq_qf_locked);
		वापस MQE_QUEUE_FULL;
	पूर्ण

	/* Got the lock. Send optional NOP अगर queue not full, */
	अगर (head != limit) अणु
		अगर (send_noop_message(cb, mqd, mesg)) अणु
			gru_gamir(cb, EOP_IR_INC, HSTATUS(mqd->mq_gpa, half),
					XTYPE_DW, IMA);
			अगर (gru_रुको(cb) != CBS_IDLE)
				जाओ cberr;
			STAT(mesq_qf_noop_not_full);
			वापस MQIE_AGAIN;
		पूर्ण
		avalue++;
	पूर्ण

	/* Then flip queuehead to other half of queue. */
	gru_gamer(cb, EOP_ERR_CSWAP, mqd->mq_gpa, XTYPE_DW, mqh.val, avalue,
							IMA);
	अगर (gru_रुको(cb) != CBS_IDLE)
		जाओ cberr;

	/* If not successfully in swapping queue head, clear the hstatus lock */
	अगर (gru_get_amo_value(cb) != avalue) अणु
		STAT(mesq_qf_चयन_head_failed);
		gru_gamir(cb, EOP_IR_INC, HSTATUS(mqd->mq_gpa, half), XTYPE_DW,
							IMA);
		अगर (gru_रुको(cb) != CBS_IDLE)
			जाओ cberr;
	पूर्ण
	वापस MQIE_AGAIN;
cberr:
	STAT(mesq_qf_unexpected_error);
	वापस MQE_UNEXPECTED_CB_ERR;
पूर्ण

/*
 * Handle a PUT failure. Note: अगर message was a 2-line message, one of the
 * lines might have successfully have been written. Beक्रमe sending the
 * message, "present" must be cleared in BOTH lines to prevent the receiver
 * from prematurely seeing the full message.
 */
अटल पूर्णांक send_message_put_nacked(व्योम *cb, काष्ठा gru_message_queue_desc *mqd,
			व्योम *mesg, पूर्णांक lines)
अणु
	अचिन्हित दीर्घ m;
	पूर्णांक ret, loops = 200;	/* experimentally determined */

	m = mqd->mq_gpa + (gru_get_amo_value_head(cb) << 6);
	अगर (lines == 2) अणु
		gru_vset(cb, m, 0, XTYPE_CL, lines, 1, IMA);
		अगर (gru_रुको(cb) != CBS_IDLE)
			वापस MQE_UNEXPECTED_CB_ERR;
	पूर्ण
	gru_vstore(cb, m, gru_get_tri(mesg), XTYPE_CL, lines, 1, IMA);
	अगर (gru_रुको(cb) != CBS_IDLE)
		वापस MQE_UNEXPECTED_CB_ERR;

	अगर (!mqd->पूर्णांकerrupt_vector)
		वापस MQE_OK;

	/*
	 * Send a noop message in order to deliver a cross-partition पूर्णांकerrupt
	 * to the SSI that contains the target message queue. Normally, the
	 * पूर्णांकerrupt is स्वतःmatically delivered by hardware following mesq
	 * operations, but some error conditions require explicit delivery.
	 * The noop message will trigger delivery. Otherwise partition failures
	 * could cause unrecovered errors.
	 */
	करो अणु
		ret = send_noop_message(cb, mqd, mesg);
	पूर्ण जबतक ((ret == MQIE_AGAIN || ret == MQE_CONGESTION) && (loops-- > 0));

	अगर (ret == MQIE_AGAIN || ret == MQE_CONGESTION) अणु
		/*
		 * Don't indicate to the app to resend the message, as it's
		 * alपढ़ोy been successfully sent.  We simply send an OK
		 * (rather than fail the send with MQE_UNEXPECTED_CB_ERR),
		 * assuming that the other side is receiving enough
		 * पूर्णांकerrupts to get this message processed anyway.
		 */
		ret = MQE_OK;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Handle a gru_mesq failure. Some of these failures are software recoverable
 * or retryable.
 */
अटल पूर्णांक send_message_failure(व्योम *cb, काष्ठा gru_message_queue_desc *mqd,
				व्योम *mesg, पूर्णांक lines)
अणु
	पूर्णांक substatus, ret = 0;

	substatus = gru_get_cb_message_queue_substatus(cb);
	चयन (substatus) अणु
	हाल CBSS_NO_ERROR:
		STAT(mesq_send_unexpected_error);
		ret = MQE_UNEXPECTED_CB_ERR;
		अवरोध;
	हाल CBSS_LB_OVERFLOWED:
		STAT(mesq_send_lb_overflow);
		ret = MQE_CONGESTION;
		अवरोध;
	हाल CBSS_QLIMIT_REACHED:
		STAT(mesq_send_qlimit_reached);
		ret = send_message_queue_full(cb, mqd, mesg, lines);
		अवरोध;
	हाल CBSS_AMO_NACKED:
		STAT(mesq_send_amo_nacked);
		ret = MQE_CONGESTION;
		अवरोध;
	हाल CBSS_PUT_NACKED:
		STAT(mesq_send_put_nacked);
		ret = send_message_put_nacked(cb, mqd, mesg, lines);
		अवरोध;
	हाल CBSS_PAGE_OVERFLOW:
		STAT(mesq_page_overflow);
		fallthrough;
	शेष:
		BUG();
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Send a message to a message queue
 * 	mqd	message queue descriptor
 * 	mesg	message. ust be vaddr within a GSEG
 * 	bytes	message size (<= 2 CL)
 */
पूर्णांक gru_send_message_gpa(काष्ठा gru_message_queue_desc *mqd, व्योम *mesg,
				अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा message_header *mhdr;
	व्योम *cb;
	व्योम *dsr;
	पूर्णांक istatus, clines, ret;

	STAT(mesq_send);
	BUG_ON(bytes < माप(पूर्णांक) || bytes > 2 * GRU_CACHE_LINE_BYTES);

	clines = DIV_ROUND_UP(bytes, GRU_CACHE_LINE_BYTES);
	अगर (gru_get_cpu_resources(bytes, &cb, &dsr))
		वापस MQE_BUG_NO_RESOURCES;
	स_नकल(dsr, mesg, bytes);
	mhdr = dsr;
	mhdr->present = MQS_FULL;
	mhdr->lines = clines;
	अगर (clines == 2) अणु
		mhdr->present2 = get_present2(mhdr);
		restore_present2(mhdr, MQS_FULL);
	पूर्ण

	करो अणु
		ret = MQE_OK;
		gru_mesq(cb, mqd->mq_gpa, gru_get_tri(mhdr), clines, IMA);
		istatus = gru_रुको(cb);
		अगर (istatus != CBS_IDLE)
			ret = send_message_failure(cb, mqd, dsr, clines);
	पूर्ण जबतक (ret == MQIE_AGAIN);
	gru_मुक्त_cpu_resources(cb, dsr);

	अगर (ret)
		STAT(mesq_send_failed);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gru_send_message_gpa);

/*
 * Advance the receive poपूर्णांकer क्रम the queue to the next message.
 */
व्योम gru_मुक्त_message(काष्ठा gru_message_queue_desc *mqd, व्योम *mesg)
अणु
	काष्ठा message_queue *mq = mqd->mq;
	काष्ठा message_header *mhdr = mq->next;
	व्योम *next, *pnext;
	पूर्णांक half = -1;
	पूर्णांक lines = mhdr->lines;

	अगर (lines == 2)
		restore_present2(mhdr, MQS_EMPTY);
	mhdr->present = MQS_EMPTY;

	pnext = mq->next;
	next = pnext + GRU_CACHE_LINE_BYTES * lines;
	अगर (next == mq->limit) अणु
		next = mq->start;
		half = 1;
	पूर्ण अन्यथा अगर (pnext < mq->start2 && next >= mq->start2) अणु
		half = 0;
	पूर्ण

	अगर (half >= 0)
		mq->hstatus[half] = 1;
	mq->next = next;
पूर्ण
EXPORT_SYMBOL_GPL(gru_मुक्त_message);

/*
 * Get next message from message queue. Return शून्य अगर no message
 * present. User must call next_message() to move to next message.
 * 	rmq	message queue
 */
व्योम *gru_get_next_message(काष्ठा gru_message_queue_desc *mqd)
अणु
	काष्ठा message_queue *mq = mqd->mq;
	काष्ठा message_header *mhdr = mq->next;
	पूर्णांक present = mhdr->present;

	/* skip NOOP messages */
	जबतक (present == MQS_NOOP) अणु
		gru_मुक्त_message(mqd, mhdr);
		mhdr = mq->next;
		present = mhdr->present;
	पूर्ण

	/* Wait क्रम both halves of 2 line messages */
	अगर (present == MQS_FULL && mhdr->lines == 2 &&
				get_present2(mhdr) == MQS_EMPTY)
		present = MQS_EMPTY;

	अगर (!present) अणु
		STAT(mesq_receive_none);
		वापस शून्य;
	पूर्ण

	अगर (mhdr->lines == 2)
		restore_present2(mhdr, mhdr->present2);

	STAT(mesq_receive);
	वापस mhdr;
पूर्ण
EXPORT_SYMBOL_GPL(gru_get_next_message);

/* ---------------------- GRU DATA COPY FUNCTIONS ---------------------------*/

/*
 * Load a DW from a global GPA. The GPA can be a memory or MMR address.
 */
पूर्णांक gru_पढ़ो_gpa(अचिन्हित दीर्घ *value, अचिन्हित दीर्घ gpa)
अणु
	व्योम *cb;
	व्योम *dsr;
	पूर्णांक ret, iaa;

	STAT(पढ़ो_gpa);
	अगर (gru_get_cpu_resources(GRU_NUM_KERNEL_DSR_BYTES, &cb, &dsr))
		वापस MQE_BUG_NO_RESOURCES;
	iaa = gpa >> 62;
	gru_vload_phys(cb, gpa, gru_get_tri(dsr), iaa, IMA);
	ret = gru_रुको(cb);
	अगर (ret == CBS_IDLE)
		*value = *(अचिन्हित दीर्घ *)dsr;
	gru_मुक्त_cpu_resources(cb, dsr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gru_पढ़ो_gpa);


/*
 * Copy a block of data using the GRU resources
 */
पूर्णांक gru_copy_gpa(अचिन्हित दीर्घ dest_gpa, अचिन्हित दीर्घ src_gpa,
				अचिन्हित पूर्णांक bytes)
अणु
	व्योम *cb;
	व्योम *dsr;
	पूर्णांक ret;

	STAT(copy_gpa);
	अगर (gru_get_cpu_resources(GRU_NUM_KERNEL_DSR_BYTES, &cb, &dsr))
		वापस MQE_BUG_NO_RESOURCES;
	gru_bcopy(cb, src_gpa, dest_gpa, gru_get_tri(dsr),
		  XTYPE_B, bytes, GRU_NUM_KERNEL_DSR_CL, IMA);
	ret = gru_रुको(cb);
	gru_मुक्त_cpu_resources(cb, dsr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gru_copy_gpa);

/* ------------------- KERNEL QUICKTESTS RUN AT STARTUP ----------------*/
/* 	Temp - will delete after we gain confidence in the GRU		*/

अटल पूर्णांक quicktest0(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ word0;
	अचिन्हित दीर्घ word1;
	व्योम *cb;
	व्योम *dsr;
	अचिन्हित दीर्घ *p;
	पूर्णांक ret = -EIO;

	अगर (gru_get_cpu_resources(GRU_CACHE_LINE_BYTES, &cb, &dsr))
		वापस MQE_BUG_NO_RESOURCES;
	p = dsr;
	word0 = MAGIC;
	word1 = 0;

	gru_vload(cb, uv_gpa(&word0), gru_get_tri(dsr), XTYPE_DW, 1, 1, IMA);
	अगर (gru_रुको(cb) != CBS_IDLE) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest0: CBR failure 1\n", smp_processor_id());
		जाओ करोne;
	पूर्ण

	अगर (*p != MAGIC) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest0 bad magic 0x%lx\n", smp_processor_id(), *p);
		जाओ करोne;
	पूर्ण
	gru_vstore(cb, uv_gpa(&word1), gru_get_tri(dsr), XTYPE_DW, 1, 1, IMA);
	अगर (gru_रुको(cb) != CBS_IDLE) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest0: CBR failure 2\n", smp_processor_id());
		जाओ करोne;
	पूर्ण

	अगर (word0 != word1 || word1 != MAGIC) अणु
		prपूर्णांकk(KERN_DEBUG
		       "GRU:%d quicktest0 err: found 0x%lx, expected 0x%lx\n",
		     smp_processor_id(), word1, MAGIC);
		जाओ करोne;
	पूर्ण
	ret = 0;

करोne:
	gru_मुक्त_cpu_resources(cb, dsr);
	वापस ret;
पूर्ण

#घोषणा ALIGNUP(p, q)	((व्योम *)(((अचिन्हित दीर्घ)(p) + (q) - 1) & ~(q - 1)))

अटल पूर्णांक quicktest1(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_message_queue_desc mqd;
	व्योम *p, *mq;
	पूर्णांक i, ret = -EIO;
	अक्षर mes[GRU_CACHE_LINE_BYTES], *m;

	/* Need  1K cacheline aligned that करोes not cross page boundary */
	p = kदो_स्मृति(4096, 0);
	अगर (p == शून्य)
		वापस -ENOMEM;
	mq = ALIGNUP(p, 1024);
	स_रखो(mes, 0xee, माप(mes));

	gru_create_message_queue(&mqd, mq, 8 * GRU_CACHE_LINE_BYTES, 0, 0, 0);
	क्रम (i = 0; i < 6; i++) अणु
		mes[8] = i;
		करो अणु
			ret = gru_send_message_gpa(&mqd, mes, माप(mes));
		पूर्ण जबतक (ret == MQE_CONGESTION);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (ret != MQE_QUEUE_FULL || i != 4) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest1: unexpect status %d, i %d\n",
		       smp_processor_id(), ret, i);
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		m = gru_get_next_message(&mqd);
		अगर (!m || m[8] != i)
			अवरोध;
		gru_मुक्त_message(&mqd, m);
	पूर्ण
	अगर (i != 4) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest2: bad message, i %d, m %p, m8 %d\n",
			smp_processor_id(), i, m, m ? m[8] : -1);
		जाओ करोne;
	पूर्ण
	ret = 0;

करोne:
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक quicktest2(अचिन्हित दीर्घ arg)
अणु
	अटल DECLARE_COMPLETION(cmp);
	अचिन्हित दीर्घ han;
	पूर्णांक blade_id = 0;
	पूर्णांक numcb = 4;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ *buf;
	व्योम *cb0, *cb;
	काष्ठा gru_control_block_status *gen;
	पूर्णांक i, k, istatus, bytes;

	bytes = numcb * 4 * 8;
	buf = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = -EBUSY;
	han = gru_reserve_async_resources(blade_id, numcb, 0, &cmp);
	अगर (!han)
		जाओ करोne;

	gru_lock_async_resource(han, &cb0, शून्य);
	स_रखो(buf, 0xee, bytes);
	क्रम (i = 0; i < numcb; i++)
		gru_vset(cb0 + i * GRU_HANDLE_STRIDE, uv_gpa(&buf[i * 4]), 0,
				XTYPE_DW, 4, 1, IMA_INTERRUPT);

	ret = 0;
	k = numcb;
	करो अणु
		gru_रुको_async_cbr(han);
		क्रम (i = 0; i < numcb; i++) अणु
			cb = cb0 + i * GRU_HANDLE_STRIDE;
			istatus = gru_check_status(cb);
			अगर (istatus != CBS_ACTIVE && istatus != CBS_CALL_OS)
				अवरोध;
		पूर्ण
		अगर (i == numcb)
			जारी;
		अगर (istatus != CBS_IDLE) अणु
			prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest2: cb %d, exception\n", smp_processor_id(), i);
			ret = -EFAULT;
		पूर्ण अन्यथा अगर (buf[4 * i] || buf[4 * i + 1] || buf[4 * i + 2] ||
				buf[4 * i + 3]) अणु
			prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest2:cb %d,  buf 0x%lx, 0x%lx, 0x%lx, 0x%lx\n",
			       smp_processor_id(), i, buf[4 * i], buf[4 * i + 1], buf[4 * i + 2], buf[4 * i + 3]);
			ret = -EIO;
		पूर्ण
		k--;
		gen = cb;
		gen->istatus = CBS_CALL_OS; /* करोn't handle this CBR again */
	पूर्ण जबतक (k);
	BUG_ON(cmp.करोne);

	gru_unlock_async_resource(han);
	gru_release_async_resources(han);
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण

#घोषणा बफ_मानE 200
अटल पूर्णांक quicktest3(अचिन्हित दीर्घ arg)
अणु
	अक्षर buf1[बफ_मानE], buf2[बफ_मानE];
	पूर्णांक ret = 0;

	स_रखो(buf2, 0, माप(buf2));
	स_रखो(buf1, get_cycles() & 255, माप(buf1));
	gru_copy_gpa(uv_gpa(buf2), uv_gpa(buf1), बफ_मानE);
	अगर (स_भेद(buf1, buf2, बफ_मानE)) अणु
		prपूर्णांकk(KERN_DEBUG "GRU:%d quicktest3 error\n", smp_processor_id());
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Debugging only. User hook क्रम various kernel tests
 * of driver & gru.
 */
पूर्णांक gru_ktest(अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (arg & 0xff) अणु
	हाल 0:
		ret = quicktest0(arg);
		अवरोध;
	हाल 1:
		ret = quicktest1(arg);
		अवरोध;
	हाल 2:
		ret = quicktest2(arg);
		अवरोध;
	हाल 3:
		ret = quicktest3(arg);
		अवरोध;
	हाल 99:
		ret = gru_मुक्त_kernel_contexts();
		अवरोध;
	पूर्ण
	वापस ret;

पूर्ण

पूर्णांक gru_kservices_init(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम gru_kservices_निकास(व्योम)
अणु
	अगर (gru_मुक्त_kernel_contexts())
		BUG();
पूर्ण

