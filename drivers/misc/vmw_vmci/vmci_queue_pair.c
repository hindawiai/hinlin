<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uपन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/skbuff.h>

#समावेश "vmci_handle_array.h"
#समावेश "vmci_queue_pair.h"
#समावेश "vmci_datagram.h"
#समावेश "vmci_resource.h"
#समावेश "vmci_context.h"
#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"
#समावेश "vmci_route.h"

/*
 * In the following, we will distinguish between two kinds of VMX processes -
 * the ones with versions lower than VMCI_VERSION_NOVMVM that use specialized
 * VMCI page files in the VMX and supporting VM to VM communication and the
 * newer ones that use the guest memory directly. We will in the following
 * refer to the older VMX versions as old-style VMX'en, and the newer ones as
 * new-style VMX'en.
 *
 * The state transition datagram is as follows (the VMCIQPB_ prefix has been
 * हटाओd क्रम पढ़ोability) - see below क्रम more details on the transtions:
 *
 *            --------------  NEW  -------------
 *            |                                |
 *           \_/                              \_/
 *     CREATED_NO_MEM <-----------------> CREATED_MEM
 *            |    |                           |
 *            |    o-----------------------o   |
 *            |                            |   |
 *           \_/                          \_/ \_/
 *     ATTACHED_NO_MEM <----------------> ATTACHED_MEM
 *            |                            |   |
 *            |     o----------------------o   |
 *            |     |                          |
 *           \_/   \_/                        \_/
 *     SHUTDOWN_NO_MEM <----------------> SHUTDOWN_MEM
 *            |                                |
 *            |                                |
 *            -------------> gone <-------------
 *
 * In more detail. When a VMCI queue pair is first created, it will be in the
 * VMCIQPB_NEW state. It will then move पूर्णांकo one of the following states:
 *
 * - VMCIQPB_CREATED_NO_MEM: this state indicates that either:
 *
 *     - the created was perक्रमmed by a host endpoपूर्णांक, in which हाल there is
 *       no backing memory yet.
 *
 *     - the create was initiated by an old-style VMX, that uses
 *       vmci_qp_broker_set_page_store to specअगरy the UVAs of the queue pair at
 *       a later poपूर्णांक in समय. This state can be distinguished from the one
 *       above by the context ID of the creator. A host side is not allowed to
 *       attach until the page store has been set.
 *
 * - VMCIQPB_CREATED_MEM: this state is the result when the queue pair
 *     is created by a VMX using the queue pair device backend that
 *     sets the UVAs of the queue pair immediately and stores the
 *     inक्रमmation क्रम later attachers. At this poपूर्णांक, it is पढ़ोy क्रम
 *     the host side to attach to it.
 *
 * Once the queue pair is in one of the created states (with the exception of
 * the हाल mentioned क्रम older VMX'en above), it is possible to attach to the
 * queue pair. Again we have two new states possible:
 *
 * - VMCIQPB_ATTACHED_MEM: this state can be reached through the following
 *   paths:
 *
 *     - from VMCIQPB_CREATED_NO_MEM when a new-style VMX allocates a queue
 *       pair, and attaches to a queue pair previously created by the host side.
 *
 *     - from VMCIQPB_CREATED_MEM when the host side attaches to a queue pair
 *       alपढ़ोy created by a guest.
 *
 *     - from VMCIQPB_ATTACHED_NO_MEM, when an old-style VMX calls
 *       vmci_qp_broker_set_page_store (see below).
 *
 * - VMCIQPB_ATTACHED_NO_MEM: If the queue pair alपढ़ोy was in the
 *     VMCIQPB_CREATED_NO_MEM due to a host side create, an old-style VMX will
 *     bring the queue pair पूर्णांकo this state. Once vmci_qp_broker_set_page_store
 *     is called to रेजिस्टर the user memory, the VMCIQPB_ATTACH_MEM state
 *     will be entered.
 *
 * From the attached queue pair, the queue pair can enter the shutकरोwn states
 * when either side of the queue pair detaches. If the guest side detaches
 * first, the queue pair will enter the VMCIQPB_SHUTDOWN_NO_MEM state, where
 * the content of the queue pair will no दीर्घer be available. If the host
 * side detaches first, the queue pair will either enter the
 * VMCIQPB_SHUTDOWN_MEM, अगर the guest memory is currently mapped, or
 * VMCIQPB_SHUTDOWN_NO_MEM, अगर the guest memory is not mapped
 * (e.g., the host detaches जबतक a guest is stunned).
 *
 * New-style VMX'en will also unmap guest memory, अगर the guest is
 * quiesced, e.g., during a snapshot operation. In that हाल, the guest
 * memory will no दीर्घer be available, and the queue pair will transition from
 * *_MEM state to a *_NO_MEM state. The VMX may later map the memory once more,
 * in which हाल the queue pair will transition from the *_NO_MEM state at that
 * poपूर्णांक back to the *_MEM state. Note that the *_NO_MEM state may have changed,
 * since the peer may have either attached or detached in the meanसमय. The
 * values are laid out such that ++ on a state will move from a *_NO_MEM to a
 * *_MEM state, and vice versa.
 */

/* The Kernel specअगरic component of the काष्ठा vmci_queue काष्ठाure. */
काष्ठा vmci_queue_kern_अगर अणु
	काष्ठा mutex __mutex;	/* Protects the queue. */
	काष्ठा mutex *mutex;	/* Shared by producer and consumer queues. */
	माप_प्रकार num_pages;	/* Number of pages incl. header. */
	bool host;		/* Host or guest? */
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t *pas;
			व्योम **vas;
		पूर्ण g;		/* Used by the guest. */
		काष्ठा अणु
			काष्ठा page **page;
			काष्ठा page **header_page;
		पूर्ण h;		/* Used by the host. */
	पूर्ण u;
पूर्ण;

/*
 * This काष्ठाure is opaque to the clients.
 */
काष्ठा vmci_qp अणु
	काष्ठा vmci_handle handle;
	काष्ठा vmci_queue *produce_q;
	काष्ठा vmci_queue *consume_q;
	u64 produce_q_size;
	u64 consume_q_size;
	u32 peer;
	u32 flags;
	u32 priv_flags;
	bool guest_endpoपूर्णांक;
	अचिन्हित पूर्णांक blocked;
	अचिन्हित पूर्णांक generation;
	रुको_queue_head_t event;
पूर्ण;

क्रमागत qp_broker_state अणु
	VMCIQPB_NEW,
	VMCIQPB_CREATED_NO_MEM,
	VMCIQPB_CREATED_MEM,
	VMCIQPB_ATTACHED_NO_MEM,
	VMCIQPB_ATTACHED_MEM,
	VMCIQPB_SHUTDOWN_NO_MEM,
	VMCIQPB_SHUTDOWN_MEM,
	VMCIQPB_GONE
पूर्ण;

#घोषणा QPBROKERSTATE_HAS_MEM(_qpb) (_qpb->state == VMCIQPB_CREATED_MEM || \
				     _qpb->state == VMCIQPB_ATTACHED_MEM || \
				     _qpb->state == VMCIQPB_SHUTDOWN_MEM)

/*
 * In the queue pair broker, we always use the guest poपूर्णांक of view क्रम
 * the produce and consume queue values and references, e.g., the
 * produce queue size stored is the guests produce queue size. The
 * host endpoपूर्णांक will need to swap these around. The only exception is
 * the local queue pairs on the host, in which हाल the host endpoपूर्णांक
 * that creates the queue pair will have the right orientation, and
 * the attaching host endpoपूर्णांक will need to swap.
 */
काष्ठा qp_entry अणु
	काष्ठा list_head list_item;
	काष्ठा vmci_handle handle;
	u32 peer;
	u32 flags;
	u64 produce_size;
	u64 consume_size;
	u32 ref_count;
पूर्ण;

काष्ठा qp_broker_entry अणु
	काष्ठा vmci_resource resource;
	काष्ठा qp_entry qp;
	u32 create_id;
	u32 attach_id;
	क्रमागत qp_broker_state state;
	bool require_trusted_attach;
	bool created_by_trusted;
	bool vmci_page_files;	/* Created by VMX using VMCI page files */
	काष्ठा vmci_queue *produce_q;
	काष्ठा vmci_queue *consume_q;
	काष्ठा vmci_queue_header saved_produce_q;
	काष्ठा vmci_queue_header saved_consume_q;
	vmci_event_release_cb wakeup_cb;
	व्योम *client_data;
	व्योम *local_mem;	/* Kernel memory क्रम local queue pair */
पूर्ण;

काष्ठा qp_guest_endpoपूर्णांक अणु
	काष्ठा vmci_resource resource;
	काष्ठा qp_entry qp;
	u64 num_ppns;
	व्योम *produce_q;
	व्योम *consume_q;
	काष्ठा ppn_set ppn_set;
पूर्ण;

काष्ठा qp_list अणु
	काष्ठा list_head head;
	काष्ठा mutex mutex;	/* Protect queue list. */
पूर्ण;

अटल काष्ठा qp_list qp_broker_list = अणु
	.head = LIST_HEAD_INIT(qp_broker_list.head),
	.mutex = __MUTEX_INITIALIZER(qp_broker_list.mutex),
पूर्ण;

अटल काष्ठा qp_list qp_guest_endpoपूर्णांकs = अणु
	.head = LIST_HEAD_INIT(qp_guest_endpoपूर्णांकs.head),
	.mutex = __MUTEX_INITIALIZER(qp_guest_endpoपूर्णांकs.mutex),
पूर्ण;

#घोषणा INVALID_VMCI_GUEST_MEM_ID  0
#घोषणा QPE_NUM_PAGES(_QPE) ((u32) \
			     (DIV_ROUND_UP(_QPE.produce_size, PAGE_SIZE) + \
			      DIV_ROUND_UP(_QPE.consume_size, PAGE_SIZE) + 2))
#घोषणा QP_SIZES_ARE_VALID(_prod_qsize, _cons_qsize) \
	((_prod_qsize) + (_cons_qsize) >= max(_prod_qsize, _cons_qsize) && \
	 (_prod_qsize) + (_cons_qsize) <= VMCI_MAX_GUEST_QP_MEMORY)

/*
 * Frees kernel VA space क्रम a given queue and its queue header, and
 * मुक्तs physical data pages.
 */
अटल व्योम qp_मुक्त_queue(व्योम *q, u64 size)
अणु
	काष्ठा vmci_queue *queue = q;

	अगर (queue) अणु
		u64 i;

		/* Given size करोes not include header, so add in a page here. */
		क्रम (i = 0; i < DIV_ROUND_UP(size, PAGE_SIZE) + 1; i++) अणु
			dma_मुक्त_coherent(&vmci_pdev->dev, PAGE_SIZE,
					  queue->kernel_अगर->u.g.vas[i],
					  queue->kernel_अगर->u.g.pas[i]);
		पूर्ण

		vमुक्त(queue);
	पूर्ण
पूर्ण

/*
 * Allocates kernel queue pages of specअगरied size with IOMMU mappings,
 * plus space क्रम the queue काष्ठाure/kernel पूर्णांकerface and the queue
 * header.
 */
अटल व्योम *qp_alloc_queue(u64 size, u32 flags)
अणु
	u64 i;
	काष्ठा vmci_queue *queue;
	माप_प्रकार pas_size;
	माप_प्रकार vas_size;
	माप_प्रकार queue_size = माप(*queue) + माप(*queue->kernel_अगर);
	u64 num_pages;

	अगर (size > SIZE_MAX - PAGE_SIZE)
		वापस शून्य;
	num_pages = DIV_ROUND_UP(size, PAGE_SIZE) + 1;
	अगर (num_pages >
		 (SIZE_MAX - queue_size) /
		 (माप(*queue->kernel_अगर->u.g.pas) +
		  माप(*queue->kernel_अगर->u.g.vas)))
		वापस शून्य;

	pas_size = num_pages * माप(*queue->kernel_अगर->u.g.pas);
	vas_size = num_pages * माप(*queue->kernel_अगर->u.g.vas);
	queue_size += pas_size + vas_size;

	queue = vदो_स्मृति(queue_size);
	अगर (!queue)
		वापस शून्य;

	queue->q_header = शून्य;
	queue->saved_header = शून्य;
	queue->kernel_अगर = (काष्ठा vmci_queue_kern_अगर *)(queue + 1);
	queue->kernel_अगर->mutex = शून्य;
	queue->kernel_अगर->num_pages = num_pages;
	queue->kernel_अगर->u.g.pas = (dma_addr_t *)(queue->kernel_अगर + 1);
	queue->kernel_अगर->u.g.vas =
		(व्योम **)((u8 *)queue->kernel_अगर->u.g.pas + pas_size);
	queue->kernel_अगर->host = false;

	क्रम (i = 0; i < num_pages; i++) अणु
		queue->kernel_अगर->u.g.vas[i] =
			dma_alloc_coherent(&vmci_pdev->dev, PAGE_SIZE,
					   &queue->kernel_अगर->u.g.pas[i],
					   GFP_KERNEL);
		अगर (!queue->kernel_अगर->u.g.vas[i]) अणु
			/* Size excl. the header. */
			qp_मुक्त_queue(queue, i * PAGE_SIZE);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* Queue header is the first page. */
	queue->q_header = queue->kernel_अगर->u.g.vas[0];

	वापस queue;
पूर्ण

/*
 * Copies from a given buffer or iovector to a VMCI Queue.  Uses
 * kmap()/kunmap() to dynamically map/unmap required portions of the queue
 * by traversing the offset -> page translation काष्ठाure क्रम the queue.
 * Assumes that offset + size करोes not wrap around in the queue.
 */
अटल पूर्णांक qp_स_नकल_to_queue_iter(काष्ठा vmci_queue *queue,
				  u64 queue_offset,
				  काष्ठा iov_iter *from,
				  माप_प्रकार size)
अणु
	काष्ठा vmci_queue_kern_अगर *kernel_अगर = queue->kernel_अगर;
	माप_प्रकार bytes_copied = 0;

	जबतक (bytes_copied < size) अणु
		स्थिर u64 page_index =
			(queue_offset + bytes_copied) / PAGE_SIZE;
		स्थिर माप_प्रकार page_offset =
		    (queue_offset + bytes_copied) & (PAGE_SIZE - 1);
		व्योम *va;
		माप_प्रकार to_copy;

		अगर (kernel_अगर->host)
			va = kmap(kernel_अगर->u.h.page[page_index]);
		अन्यथा
			va = kernel_अगर->u.g.vas[page_index + 1];
			/* Skip header. */

		अगर (size - bytes_copied > PAGE_SIZE - page_offset)
			/* Enough payload to fill up from this page. */
			to_copy = PAGE_SIZE - page_offset;
		अन्यथा
			to_copy = size - bytes_copied;

		अगर (!copy_from_iter_full((u8 *)va + page_offset, to_copy,
					 from)) अणु
			अगर (kernel_अगर->host)
				kunmap(kernel_अगर->u.h.page[page_index]);
			वापस VMCI_ERROR_INVALID_ARGS;
		पूर्ण
		bytes_copied += to_copy;
		अगर (kernel_अगर->host)
			kunmap(kernel_अगर->u.h.page[page_index]);
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Copies to a given buffer or iovector from a VMCI Queue.  Uses
 * kmap()/kunmap() to dynamically map/unmap required portions of the queue
 * by traversing the offset -> page translation काष्ठाure क्रम the queue.
 * Assumes that offset + size करोes not wrap around in the queue.
 */
अटल पूर्णांक qp_स_नकल_from_queue_iter(काष्ठा iov_iter *to,
				    स्थिर काष्ठा vmci_queue *queue,
				    u64 queue_offset, माप_प्रकार size)
अणु
	काष्ठा vmci_queue_kern_अगर *kernel_अगर = queue->kernel_अगर;
	माप_प्रकार bytes_copied = 0;

	जबतक (bytes_copied < size) अणु
		स्थिर u64 page_index =
			(queue_offset + bytes_copied) / PAGE_SIZE;
		स्थिर माप_प्रकार page_offset =
		    (queue_offset + bytes_copied) & (PAGE_SIZE - 1);
		व्योम *va;
		माप_प्रकार to_copy;
		पूर्णांक err;

		अगर (kernel_अगर->host)
			va = kmap(kernel_अगर->u.h.page[page_index]);
		अन्यथा
			va = kernel_अगर->u.g.vas[page_index + 1];
			/* Skip header. */

		अगर (size - bytes_copied > PAGE_SIZE - page_offset)
			/* Enough payload to fill up this page. */
			to_copy = PAGE_SIZE - page_offset;
		अन्यथा
			to_copy = size - bytes_copied;

		err = copy_to_iter((u8 *)va + page_offset, to_copy, to);
		अगर (err != to_copy) अणु
			अगर (kernel_अगर->host)
				kunmap(kernel_अगर->u.h.page[page_index]);
			वापस VMCI_ERROR_INVALID_ARGS;
		पूर्ण
		bytes_copied += to_copy;
		अगर (kernel_अगर->host)
			kunmap(kernel_अगर->u.h.page[page_index]);
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Allocates two list of PPNs --- one क्रम the pages in the produce queue,
 * and the other क्रम the pages in the consume queue. Intializes the list
 * of PPNs with the page frame numbers of the KVA क्रम the two queues (and
 * the queue headers).
 */
अटल पूर्णांक qp_alloc_ppn_set(व्योम *prod_q,
			    u64 num_produce_pages,
			    व्योम *cons_q,
			    u64 num_consume_pages, काष्ठा ppn_set *ppn_set)
अणु
	u64 *produce_ppns;
	u64 *consume_ppns;
	काष्ठा vmci_queue *produce_q = prod_q;
	काष्ठा vmci_queue *consume_q = cons_q;
	u64 i;

	अगर (!produce_q || !num_produce_pages || !consume_q ||
	    !num_consume_pages || !ppn_set)
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (ppn_set->initialized)
		वापस VMCI_ERROR_ALREADY_EXISTS;

	produce_ppns =
	    kदो_स्मृति_array(num_produce_pages, माप(*produce_ppns),
			  GFP_KERNEL);
	अगर (!produce_ppns)
		वापस VMCI_ERROR_NO_MEM;

	consume_ppns =
	    kदो_स्मृति_array(num_consume_pages, माप(*consume_ppns),
			  GFP_KERNEL);
	अगर (!consume_ppns) अणु
		kमुक्त(produce_ppns);
		वापस VMCI_ERROR_NO_MEM;
	पूर्ण

	क्रम (i = 0; i < num_produce_pages; i++)
		produce_ppns[i] =
			produce_q->kernel_अगर->u.g.pas[i] >> PAGE_SHIFT;

	क्रम (i = 0; i < num_consume_pages; i++)
		consume_ppns[i] =
			consume_q->kernel_अगर->u.g.pas[i] >> PAGE_SHIFT;

	ppn_set->num_produce_pages = num_produce_pages;
	ppn_set->num_consume_pages = num_consume_pages;
	ppn_set->produce_ppns = produce_ppns;
	ppn_set->consume_ppns = consume_ppns;
	ppn_set->initialized = true;
	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Frees the two list of PPNs क्रम a queue pair.
 */
अटल व्योम qp_मुक्त_ppn_set(काष्ठा ppn_set *ppn_set)
अणु
	अगर (ppn_set->initialized) अणु
		/* Do not call these functions on शून्य inमाला_दो. */
		kमुक्त(ppn_set->produce_ppns);
		kमुक्त(ppn_set->consume_ppns);
	पूर्ण
	स_रखो(ppn_set, 0, माप(*ppn_set));
पूर्ण

/*
 * Populates the list of PPNs in the hypercall काष्ठाure with the PPNS
 * of the produce queue and the consume queue.
 */
अटल पूर्णांक qp_populate_ppn_set(u8 *call_buf, स्थिर काष्ठा ppn_set *ppn_set)
अणु
	अगर (vmci_use_ppn64()) अणु
		स_नकल(call_buf, ppn_set->produce_ppns,
		       ppn_set->num_produce_pages *
		       माप(*ppn_set->produce_ppns));
		स_नकल(call_buf +
		       ppn_set->num_produce_pages *
		       माप(*ppn_set->produce_ppns),
		       ppn_set->consume_ppns,
		       ppn_set->num_consume_pages *
		       माप(*ppn_set->consume_ppns));
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		u32 *ppns = (u32 *) call_buf;

		क्रम (i = 0; i < ppn_set->num_produce_pages; i++)
			ppns[i] = (u32) ppn_set->produce_ppns[i];

		ppns = &ppns[ppn_set->num_produce_pages];

		क्रम (i = 0; i < ppn_set->num_consume_pages; i++)
			ppns[i] = (u32) ppn_set->consume_ppns[i];
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Allocates kernel VA space of specअगरied size plus space क्रम the queue
 * and kernel पूर्णांकerface.  This is dअगरferent from the guest queue allocator,
 * because we करो not allocate our own queue header/data pages here but
 * share those of the guest.
 */
अटल काष्ठा vmci_queue *qp_host_alloc_queue(u64 size)
अणु
	काष्ठा vmci_queue *queue;
	माप_प्रकार queue_page_size;
	u64 num_pages;
	स्थिर माप_प्रकार queue_size = माप(*queue) + माप(*(queue->kernel_अगर));

	अगर (size > min_t(माप_प्रकार, VMCI_MAX_GUEST_QP_MEMORY, SIZE_MAX - PAGE_SIZE))
		वापस शून्य;
	num_pages = DIV_ROUND_UP(size, PAGE_SIZE) + 1;
	अगर (num_pages > (SIZE_MAX - queue_size) /
		 माप(*queue->kernel_अगर->u.h.page))
		वापस शून्य;

	queue_page_size = num_pages * माप(*queue->kernel_अगर->u.h.page);

	अगर (queue_size + queue_page_size > KMALLOC_MAX_SIZE)
		वापस शून्य;

	queue = kzalloc(queue_size + queue_page_size, GFP_KERNEL);
	अगर (queue) अणु
		queue->q_header = शून्य;
		queue->saved_header = शून्य;
		queue->kernel_अगर = (काष्ठा vmci_queue_kern_अगर *)(queue + 1);
		queue->kernel_अगर->host = true;
		queue->kernel_अगर->mutex = शून्य;
		queue->kernel_अगर->num_pages = num_pages;
		queue->kernel_अगर->u.h.header_page =
		    (काष्ठा page **)((u8 *)queue + queue_size);
		queue->kernel_अगर->u.h.page =
			&queue->kernel_अगर->u.h.header_page[1];
	पूर्ण

	वापस queue;
पूर्ण

/*
 * Frees kernel memory क्रम a given queue (header plus translation
 * काष्ठाure).
 */
अटल व्योम qp_host_मुक्त_queue(काष्ठा vmci_queue *queue, u64 queue_size)
अणु
	kमुक्त(queue);
पूर्ण

/*
 * Initialize the mutex क्रम the pair of queues.  This mutex is used to
 * protect the q_header and the buffer from changing out from under any
 * users of either queue.  Of course, it's only any good अगर the mutexes
 * are actually acquired.  Queue काष्ठाure must lie on non-paged memory
 * or we cannot guarantee access to the mutex.
 */
अटल व्योम qp_init_queue_mutex(काष्ठा vmci_queue *produce_q,
				काष्ठा vmci_queue *consume_q)
अणु
	/*
	 * Only the host queue has shared state - the guest queues करो not
	 * need to synchronize access using a queue mutex.
	 */

	अगर (produce_q->kernel_अगर->host) अणु
		produce_q->kernel_अगर->mutex = &produce_q->kernel_अगर->__mutex;
		consume_q->kernel_अगर->mutex = &produce_q->kernel_अगर->__mutex;
		mutex_init(produce_q->kernel_अगर->mutex);
	पूर्ण
पूर्ण

/*
 * Cleans up the mutex क्रम the pair of queues.
 */
अटल व्योम qp_cleanup_queue_mutex(काष्ठा vmci_queue *produce_q,
				   काष्ठा vmci_queue *consume_q)
अणु
	अगर (produce_q->kernel_अगर->host) अणु
		produce_q->kernel_अगर->mutex = शून्य;
		consume_q->kernel_अगर->mutex = शून्य;
	पूर्ण
पूर्ण

/*
 * Acquire the mutex क्रम the queue.  Note that the produce_q and
 * the consume_q share a mutex.  So, only one of the two need to
 * be passed in to this routine.  Either will work just fine.
 */
अटल व्योम qp_acquire_queue_mutex(काष्ठा vmci_queue *queue)
अणु
	अगर (queue->kernel_अगर->host)
		mutex_lock(queue->kernel_अगर->mutex);
पूर्ण

/*
 * Release the mutex क्रम the queue.  Note that the produce_q and
 * the consume_q share a mutex.  So, only one of the two need to
 * be passed in to this routine.  Either will work just fine.
 */
अटल व्योम qp_release_queue_mutex(काष्ठा vmci_queue *queue)
अणु
	अगर (queue->kernel_अगर->host)
		mutex_unlock(queue->kernel_अगर->mutex);
पूर्ण

/*
 * Helper function to release pages in the PageStoreAttachInfo
 * previously obtained using get_user_pages.
 */
अटल व्योम qp_release_pages(काष्ठा page **pages,
			     u64 num_pages, bool dirty)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pages; i++) अणु
		अगर (dirty)
			set_page_dirty_lock(pages[i]);

		put_page(pages[i]);
		pages[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * Lock the user pages referenced by the अणुproduce,consumeपूर्णBuffer
 * काष्ठा पूर्णांकo memory and populate the अणुproduce,consumeपूर्णPages
 * arrays in the attach काष्ठाure with them.
 */
अटल पूर्णांक qp_host_get_user_memory(u64 produce_uva,
				   u64 consume_uva,
				   काष्ठा vmci_queue *produce_q,
				   काष्ठा vmci_queue *consume_q)
अणु
	पूर्णांक retval;
	पूर्णांक err = VMCI_SUCCESS;

	retval = get_user_pages_fast((uपूर्णांकptr_t) produce_uva,
				     produce_q->kernel_अगर->num_pages,
				     FOLL_WRITE,
				     produce_q->kernel_अगर->u.h.header_page);
	अगर (retval < (पूर्णांक)produce_q->kernel_अगर->num_pages) अणु
		pr_debug("get_user_pages_fast(produce) failed (retval=%d)",
			retval);
		अगर (retval > 0)
			qp_release_pages(produce_q->kernel_अगर->u.h.header_page,
					retval, false);
		err = VMCI_ERROR_NO_MEM;
		जाओ out;
	पूर्ण

	retval = get_user_pages_fast((uपूर्णांकptr_t) consume_uva,
				     consume_q->kernel_अगर->num_pages,
				     FOLL_WRITE,
				     consume_q->kernel_अगर->u.h.header_page);
	अगर (retval < (पूर्णांक)consume_q->kernel_अगर->num_pages) अणु
		pr_debug("get_user_pages_fast(consume) failed (retval=%d)",
			retval);
		अगर (retval > 0)
			qp_release_pages(consume_q->kernel_अगर->u.h.header_page,
					retval, false);
		qp_release_pages(produce_q->kernel_अगर->u.h.header_page,
				 produce_q->kernel_अगर->num_pages, false);
		err = VMCI_ERROR_NO_MEM;
	पूर्ण

 out:
	वापस err;
पूर्ण

/*
 * Registers the specअगरication of the user pages used क्रम backing a queue
 * pair. Enough inक्रमmation to map in pages is stored in the OS specअगरic
 * part of the काष्ठा vmci_queue काष्ठाure.
 */
अटल पूर्णांक qp_host_रेजिस्टर_user_memory(काष्ठा vmci_qp_page_store *page_store,
					काष्ठा vmci_queue *produce_q,
					काष्ठा vmci_queue *consume_q)
अणु
	u64 produce_uva;
	u64 consume_uva;

	/*
	 * The new style and the old style mapping only dअगरfers in
	 * that we either get a single or two UVAs, so we split the
	 * single UVA range at the appropriate spot.
	 */
	produce_uva = page_store->pages;
	consume_uva = page_store->pages +
	    produce_q->kernel_अगर->num_pages * PAGE_SIZE;
	वापस qp_host_get_user_memory(produce_uva, consume_uva, produce_q,
				       consume_q);
पूर्ण

/*
 * Releases and हटाओs the references to user pages stored in the attach
 * काष्ठा.  Pages are released from the page cache and may become
 * swappable again.
 */
अटल व्योम qp_host_unरेजिस्टर_user_memory(काष्ठा vmci_queue *produce_q,
					   काष्ठा vmci_queue *consume_q)
अणु
	qp_release_pages(produce_q->kernel_अगर->u.h.header_page,
			 produce_q->kernel_अगर->num_pages, true);
	स_रखो(produce_q->kernel_अगर->u.h.header_page, 0,
	       माप(*produce_q->kernel_अगर->u.h.header_page) *
	       produce_q->kernel_अगर->num_pages);
	qp_release_pages(consume_q->kernel_अगर->u.h.header_page,
			 consume_q->kernel_अगर->num_pages, true);
	स_रखो(consume_q->kernel_अगर->u.h.header_page, 0,
	       माप(*consume_q->kernel_अगर->u.h.header_page) *
	       consume_q->kernel_अगर->num_pages);
पूर्ण

/*
 * Once qp_host_रेजिस्टर_user_memory has been perक्रमmed on a
 * queue, the queue pair headers can be mapped पूर्णांकo the
 * kernel. Once mapped, they must be unmapped with
 * qp_host_unmap_queues prior to calling
 * qp_host_unरेजिस्टर_user_memory.
 * Pages are pinned.
 */
अटल पूर्णांक qp_host_map_queues(काष्ठा vmci_queue *produce_q,
			      काष्ठा vmci_queue *consume_q)
अणु
	पूर्णांक result;

	अगर (!produce_q->q_header || !consume_q->q_header) अणु
		काष्ठा page *headers[2];

		अगर (produce_q->q_header != consume_q->q_header)
			वापस VMCI_ERROR_QUEUEPAIR_MISMATCH;

		अगर (produce_q->kernel_अगर->u.h.header_page == शून्य ||
		    *produce_q->kernel_अगर->u.h.header_page == शून्य)
			वापस VMCI_ERROR_UNAVAILABLE;

		headers[0] = *produce_q->kernel_अगर->u.h.header_page;
		headers[1] = *consume_q->kernel_अगर->u.h.header_page;

		produce_q->q_header = vmap(headers, 2, VM_MAP, PAGE_KERNEL);
		अगर (produce_q->q_header != शून्य) अणु
			consume_q->q_header =
			    (काष्ठा vmci_queue_header *)((u8 *)
							 produce_q->q_header +
							 PAGE_SIZE);
			result = VMCI_SUCCESS;
		पूर्ण अन्यथा अणु
			pr_warn("vmap failed\n");
			result = VMCI_ERROR_NO_MEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		result = VMCI_SUCCESS;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Unmaps previously mapped queue pair headers from the kernel.
 * Pages are unpinned.
 */
अटल पूर्णांक qp_host_unmap_queues(u32 gid,
				काष्ठा vmci_queue *produce_q,
				काष्ठा vmci_queue *consume_q)
अणु
	अगर (produce_q->q_header) अणु
		अगर (produce_q->q_header < consume_q->q_header)
			vunmap(produce_q->q_header);
		अन्यथा
			vunmap(consume_q->q_header);

		produce_q->q_header = शून्य;
		consume_q->q_header = शून्य;
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Finds the entry in the list corresponding to a given handle. Assumes
 * that the list is locked.
 */
अटल काष्ठा qp_entry *qp_list_find(काष्ठा qp_list *qp_list,
				     काष्ठा vmci_handle handle)
अणु
	काष्ठा qp_entry *entry;

	अगर (vmci_handle_is_invalid(handle))
		वापस शून्य;

	list_क्रम_each_entry(entry, &qp_list->head, list_item) अणु
		अगर (vmci_handle_is_equal(entry->handle, handle))
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Finds the entry in the list corresponding to a given handle.
 */
अटल काष्ठा qp_guest_endpoपूर्णांक *
qp_guest_handle_to_entry(काष्ठा vmci_handle handle)
अणु
	काष्ठा qp_guest_endpoपूर्णांक *entry;
	काष्ठा qp_entry *qp = qp_list_find(&qp_guest_endpoपूर्णांकs, handle);

	entry = qp ? container_of(
		qp, काष्ठा qp_guest_endpoपूर्णांक, qp) : शून्य;
	वापस entry;
पूर्ण

/*
 * Finds the entry in the list corresponding to a given handle.
 */
अटल काष्ठा qp_broker_entry *
qp_broker_handle_to_entry(काष्ठा vmci_handle handle)
अणु
	काष्ठा qp_broker_entry *entry;
	काष्ठा qp_entry *qp = qp_list_find(&qp_broker_list, handle);

	entry = qp ? container_of(
		qp, काष्ठा qp_broker_entry, qp) : शून्य;
	वापस entry;
पूर्ण

/*
 * Dispatches a queue pair event message directly पूर्णांकo the local event
 * queue.
 */
अटल पूर्णांक qp_notअगरy_peer_local(bool attach, काष्ठा vmci_handle handle)
अणु
	u32 context_id = vmci_get_context_id();
	काष्ठा vmci_event_qp ev;

	ev.msg.hdr.dst = vmci_make_handle(context_id, VMCI_EVENT_HANDLER);
	ev.msg.hdr.src = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					  VMCI_CONTEXT_RESOURCE_ID);
	ev.msg.hdr.payload_size = माप(ev) - माप(ev.msg.hdr);
	ev.msg.event_data.event =
	    attach ? VMCI_EVENT_QP_PEER_ATTACH : VMCI_EVENT_QP_PEER_DETACH;
	ev.payload.peer_id = context_id;
	ev.payload.handle = handle;

	वापस vmci_event_dispatch(&ev.msg.hdr);
पूर्ण

/*
 * Allocates and initializes a qp_guest_endpoपूर्णांक काष्ठाure.
 * Allocates a queue_pair rid (and handle) अगरf the given entry has
 * an invalid handle.  0 through VMCI_RESERVED_RESOURCE_ID_MAX
 * are reserved handles.  Assumes that the QP list mutex is held
 * by the caller.
 */
अटल काष्ठा qp_guest_endpoपूर्णांक *
qp_guest_endpoपूर्णांक_create(काष्ठा vmci_handle handle,
			 u32 peer,
			 u32 flags,
			 u64 produce_size,
			 u64 consume_size,
			 व्योम *produce_q,
			 व्योम *consume_q)
अणु
	पूर्णांक result;
	काष्ठा qp_guest_endpoपूर्णांक *entry;
	/* One page each क्रम the queue headers. */
	स्थिर u64 num_ppns = DIV_ROUND_UP(produce_size, PAGE_SIZE) +
	    DIV_ROUND_UP(consume_size, PAGE_SIZE) + 2;

	अगर (vmci_handle_is_invalid(handle)) अणु
		u32 context_id = vmci_get_context_id();

		handle = vmci_make_handle(context_id, VMCI_INVALID_ID);
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		entry->qp.peer = peer;
		entry->qp.flags = flags;
		entry->qp.produce_size = produce_size;
		entry->qp.consume_size = consume_size;
		entry->qp.ref_count = 0;
		entry->num_ppns = num_ppns;
		entry->produce_q = produce_q;
		entry->consume_q = consume_q;
		INIT_LIST_HEAD(&entry->qp.list_item);

		/* Add resource obj */
		result = vmci_resource_add(&entry->resource,
					   VMCI_RESOURCE_TYPE_QPAIR_GUEST,
					   handle);
		entry->qp.handle = vmci_resource_handle(&entry->resource);
		अगर ((result != VMCI_SUCCESS) ||
		    qp_list_find(&qp_guest_endpoपूर्णांकs, entry->qp.handle)) अणु
			pr_warn("Failed to add new resource (handle=0x%x:0x%x), error: %d",
				handle.context, handle.resource, result);
			kमुक्त(entry);
			entry = शून्य;
		पूर्ण
	पूर्ण
	वापस entry;
पूर्ण

/*
 * Frees a qp_guest_endpoपूर्णांक काष्ठाure.
 */
अटल व्योम qp_guest_endpoपूर्णांक_destroy(काष्ठा qp_guest_endpoपूर्णांक *entry)
अणु
	qp_मुक्त_ppn_set(&entry->ppn_set);
	qp_cleanup_queue_mutex(entry->produce_q, entry->consume_q);
	qp_मुक्त_queue(entry->produce_q, entry->qp.produce_size);
	qp_मुक्त_queue(entry->consume_q, entry->qp.consume_size);
	/* Unlink from resource hash table and मुक्त callback */
	vmci_resource_हटाओ(&entry->resource);

	kमुक्त(entry);
पूर्ण

/*
 * Helper to make a queue_pairAlloc hypercall when the driver is
 * supporting a guest device.
 */
अटल पूर्णांक qp_alloc_hypercall(स्थिर काष्ठा qp_guest_endpoपूर्णांक *entry)
अणु
	काष्ठा vmci_qp_alloc_msg *alloc_msg;
	माप_प्रकार msg_size;
	माप_प्रकार ppn_size;
	पूर्णांक result;

	अगर (!entry || entry->num_ppns <= 2)
		वापस VMCI_ERROR_INVALID_ARGS;

	ppn_size = vmci_use_ppn64() ? माप(u64) : माप(u32);
	msg_size = माप(*alloc_msg) +
	    (माप_प्रकार) entry->num_ppns * ppn_size;
	alloc_msg = kदो_स्मृति(msg_size, GFP_KERNEL);
	अगर (!alloc_msg)
		वापस VMCI_ERROR_NO_MEM;

	alloc_msg->hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_QUEUEPAIR_ALLOC);
	alloc_msg->hdr.src = VMCI_ANON_SRC_HANDLE;
	alloc_msg->hdr.payload_size = msg_size - VMCI_DG_HEADERSIZE;
	alloc_msg->handle = entry->qp.handle;
	alloc_msg->peer = entry->qp.peer;
	alloc_msg->flags = entry->qp.flags;
	alloc_msg->produce_size = entry->qp.produce_size;
	alloc_msg->consume_size = entry->qp.consume_size;
	alloc_msg->num_ppns = entry->num_ppns;

	result = qp_populate_ppn_set((u8 *)alloc_msg + माप(*alloc_msg),
				     &entry->ppn_set);
	अगर (result == VMCI_SUCCESS)
		result = vmci_send_datagram(&alloc_msg->hdr);

	kमुक्त(alloc_msg);

	वापस result;
पूर्ण

/*
 * Helper to make a queue_pairDetach hypercall when the driver is
 * supporting a guest device.
 */
अटल पूर्णांक qp_detatch_hypercall(काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_qp_detach_msg detach_msg;

	detach_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_QUEUEPAIR_DETACH);
	detach_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	detach_msg.hdr.payload_size = माप(handle);
	detach_msg.handle = handle;

	वापस vmci_send_datagram(&detach_msg.hdr);
पूर्ण

/*
 * Adds the given entry to the list. Assumes that the list is locked.
 */
अटल व्योम qp_list_add_entry(काष्ठा qp_list *qp_list, काष्ठा qp_entry *entry)
अणु
	अगर (entry)
		list_add(&entry->list_item, &qp_list->head);
पूर्ण

/*
 * Removes the given entry from the list. Assumes that the list is locked.
 */
अटल व्योम qp_list_हटाओ_entry(काष्ठा qp_list *qp_list,
				 काष्ठा qp_entry *entry)
अणु
	अगर (entry)
		list_del(&entry->list_item);
पूर्ण

/*
 * Helper क्रम VMCI queue_pair detach पूर्णांकerface. Frees the physical
 * pages क्रम the queue pair.
 */
अटल पूर्णांक qp_detatch_guest_work(काष्ठा vmci_handle handle)
अणु
	पूर्णांक result;
	काष्ठा qp_guest_endpoपूर्णांक *entry;
	u32 ref_count = ~0;	/* To aव्योम compiler warning below */

	mutex_lock(&qp_guest_endpoपूर्णांकs.mutex);

	entry = qp_guest_handle_to_entry(handle);
	अगर (!entry) अणु
		mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);
		वापस VMCI_ERROR_NOT_FOUND;
	पूर्ण

	अगर (entry->qp.flags & VMCI_QPFLAG_LOCAL) अणु
		result = VMCI_SUCCESS;

		अगर (entry->qp.ref_count > 1) अणु
			result = qp_notअगरy_peer_local(false, handle);
			/*
			 * We can fail to notअगरy a local queuepair
			 * because we can't allocate.  We still want
			 * to release the entry अगर that happens, so
			 * करोn't bail out yet.
			 */
		पूर्ण
	पूर्ण अन्यथा अणु
		result = qp_detatch_hypercall(handle);
		अगर (result < VMCI_SUCCESS) अणु
			/*
			 * We failed to notअगरy a non-local queuepair.
			 * That other queuepair might still be
			 * accessing the shared memory, so करोn't
			 * release the entry yet.  It will get cleaned
			 * up by VMCIqueue_pair_Exit() अगर necessary
			 * (assuming we are going away, otherwise why
			 * did this fail?).
			 */

			mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);
			वापस result;
		पूर्ण
	पूर्ण

	/*
	 * If we get here then we either failed to notअगरy a local queuepair, or
	 * we succeeded in all हालs.  Release the entry अगर required.
	 */

	entry->qp.ref_count--;
	अगर (entry->qp.ref_count == 0)
		qp_list_हटाओ_entry(&qp_guest_endpoपूर्णांकs, &entry->qp);

	/* If we didn't हटाओ the entry, this could change once we unlock. */
	अगर (entry)
		ref_count = entry->qp.ref_count;

	mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);

	अगर (ref_count == 0)
		qp_guest_endpoपूर्णांक_destroy(entry);

	वापस result;
पूर्ण

/*
 * This functions handles the actual allocation of a VMCI queue
 * pair guest endpoपूर्णांक. Allocates physical pages क्रम the queue
 * pair. It makes OS dependent calls through generic wrappers.
 */
अटल पूर्णांक qp_alloc_guest_work(काष्ठा vmci_handle *handle,
			       काष्ठा vmci_queue **produce_q,
			       u64 produce_size,
			       काष्ठा vmci_queue **consume_q,
			       u64 consume_size,
			       u32 peer,
			       u32 flags,
			       u32 priv_flags)
अणु
	स्थिर u64 num_produce_pages =
	    DIV_ROUND_UP(produce_size, PAGE_SIZE) + 1;
	स्थिर u64 num_consume_pages =
	    DIV_ROUND_UP(consume_size, PAGE_SIZE) + 1;
	व्योम *my_produce_q = शून्य;
	व्योम *my_consume_q = शून्य;
	पूर्णांक result;
	काष्ठा qp_guest_endpoपूर्णांक *queue_pair_entry = शून्य;

	अगर (priv_flags != VMCI_NO_PRIVILEGE_FLAGS)
		वापस VMCI_ERROR_NO_ACCESS;

	mutex_lock(&qp_guest_endpoपूर्णांकs.mutex);

	queue_pair_entry = qp_guest_handle_to_entry(*handle);
	अगर (queue_pair_entry) अणु
		अगर (queue_pair_entry->qp.flags & VMCI_QPFLAG_LOCAL) अणु
			/* Local attach हाल. */
			अगर (queue_pair_entry->qp.ref_count > 1) अणु
				pr_devel("Error attempting to attach more than once\n");
				result = VMCI_ERROR_UNAVAILABLE;
				जाओ error_keep_entry;
			पूर्ण

			अगर (queue_pair_entry->qp.produce_size != consume_size ||
			    queue_pair_entry->qp.consume_size !=
			    produce_size ||
			    queue_pair_entry->qp.flags !=
			    (flags & ~VMCI_QPFLAG_ATTACH_ONLY)) अणु
				pr_devel("Error mismatched queue pair in local attach\n");
				result = VMCI_ERROR_QUEUEPAIR_MISMATCH;
				जाओ error_keep_entry;
			पूर्ण

			/*
			 * Do a local attach.  We swap the consume and
			 * produce queues क्रम the attacher and deliver
			 * an attach event.
			 */
			result = qp_notअगरy_peer_local(true, *handle);
			अगर (result < VMCI_SUCCESS)
				जाओ error_keep_entry;

			my_produce_q = queue_pair_entry->consume_q;
			my_consume_q = queue_pair_entry->produce_q;
			जाओ out;
		पूर्ण

		result = VMCI_ERROR_ALREADY_EXISTS;
		जाओ error_keep_entry;
	पूर्ण

	my_produce_q = qp_alloc_queue(produce_size, flags);
	अगर (!my_produce_q) अणु
		pr_warn("Error allocating pages for produce queue\n");
		result = VMCI_ERROR_NO_MEM;
		जाओ error;
	पूर्ण

	my_consume_q = qp_alloc_queue(consume_size, flags);
	अगर (!my_consume_q) अणु
		pr_warn("Error allocating pages for consume queue\n");
		result = VMCI_ERROR_NO_MEM;
		जाओ error;
	पूर्ण

	queue_pair_entry = qp_guest_endpoपूर्णांक_create(*handle, peer, flags,
						    produce_size, consume_size,
						    my_produce_q, my_consume_q);
	अगर (!queue_pair_entry) अणु
		pr_warn("Error allocating memory in %s\n", __func__);
		result = VMCI_ERROR_NO_MEM;
		जाओ error;
	पूर्ण

	result = qp_alloc_ppn_set(my_produce_q, num_produce_pages, my_consume_q,
				  num_consume_pages,
				  &queue_pair_entry->ppn_set);
	अगर (result < VMCI_SUCCESS) अणु
		pr_warn("qp_alloc_ppn_set failed\n");
		जाओ error;
	पूर्ण

	/*
	 * It's only necessary to notअगरy the host अगर this queue pair will be
	 * attached to from another context.
	 */
	अगर (queue_pair_entry->qp.flags & VMCI_QPFLAG_LOCAL) अणु
		/* Local create हाल. */
		u32 context_id = vmci_get_context_id();

		/*
		 * Enक्रमce similar checks on local queue pairs as we
		 * करो क्रम regular ones.  The handle's context must
		 * match the creator or attacher context id (here they
		 * are both the current context id) and the
		 * attach-only flag cannot exist during create.  We
		 * also ensure specअगरied peer is this context or an
		 * invalid one.
		 */
		अगर (queue_pair_entry->qp.handle.context != context_id ||
		    (queue_pair_entry->qp.peer != VMCI_INVALID_ID &&
		     queue_pair_entry->qp.peer != context_id)) अणु
			result = VMCI_ERROR_NO_ACCESS;
			जाओ error;
		पूर्ण

		अगर (queue_pair_entry->qp.flags & VMCI_QPFLAG_ATTACH_ONLY) अणु
			result = VMCI_ERROR_NOT_FOUND;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		result = qp_alloc_hypercall(queue_pair_entry);
		अगर (result < VMCI_SUCCESS) अणु
			pr_devel("qp_alloc_hypercall result = %d\n", result);
			जाओ error;
		पूर्ण
	पूर्ण

	qp_init_queue_mutex((काष्ठा vmci_queue *)my_produce_q,
			    (काष्ठा vmci_queue *)my_consume_q);

	qp_list_add_entry(&qp_guest_endpoपूर्णांकs, &queue_pair_entry->qp);

 out:
	queue_pair_entry->qp.ref_count++;
	*handle = queue_pair_entry->qp.handle;
	*produce_q = (काष्ठा vmci_queue *)my_produce_q;
	*consume_q = (काष्ठा vmci_queue *)my_consume_q;

	/*
	 * We should initialize the queue pair header pages on a local
	 * queue pair create.  For non-local queue pairs, the
	 * hypervisor initializes the header pages in the create step.
	 */
	अगर ((queue_pair_entry->qp.flags & VMCI_QPFLAG_LOCAL) &&
	    queue_pair_entry->qp.ref_count == 1) अणु
		vmci_q_header_init((*produce_q)->q_header, *handle);
		vmci_q_header_init((*consume_q)->q_header, *handle);
	पूर्ण

	mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);

	वापस VMCI_SUCCESS;

 error:
	mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);
	अगर (queue_pair_entry) अणु
		/* The queues will be मुक्तd inside the destroy routine. */
		qp_guest_endpoपूर्णांक_destroy(queue_pair_entry);
	पूर्ण अन्यथा अणु
		qp_मुक्त_queue(my_produce_q, produce_size);
		qp_मुक्त_queue(my_consume_q, consume_size);
	पूर्ण
	वापस result;

 error_keep_entry:
	/* This path should only be used when an existing entry was found. */
	mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);
	वापस result;
पूर्ण

/*
 * The first endpoपूर्णांक issuing a queue pair allocation will create the state
 * of the queue pair in the queue pair broker.
 *
 * If the creator is a guest, it will associate a VMX भव address range
 * with the queue pair as specअगरied by the page_store. For compatibility with
 * older VMX'en, that would use a separate step to set the VMX भव
 * address range, the भव address range can be रेजिस्टरed later using
 * vmci_qp_broker_set_page_store. In that हाल, a page_store of शून्य should be
 * used.
 *
 * If the creator is the host, a page_store of शून्य should be used as well,
 * since the host is not able to supply a page store क्रम the queue pair.
 *
 * For older VMX and host callers, the queue pair will be created in the
 * VMCIQPB_CREATED_NO_MEM state, and क्रम current VMX callers, it will be
 * created in VMCOQPB_CREATED_MEM state.
 */
अटल पूर्णांक qp_broker_create(काष्ठा vmci_handle handle,
			    u32 peer,
			    u32 flags,
			    u32 priv_flags,
			    u64 produce_size,
			    u64 consume_size,
			    काष्ठा vmci_qp_page_store *page_store,
			    काष्ठा vmci_ctx *context,
			    vmci_event_release_cb wakeup_cb,
			    व्योम *client_data, काष्ठा qp_broker_entry **ent)
अणु
	काष्ठा qp_broker_entry *entry = शून्य;
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	bool is_local = flags & VMCI_QPFLAG_LOCAL;
	पूर्णांक result;
	u64 guest_produce_size;
	u64 guest_consume_size;

	/* Do not create अगर the caller asked not to. */
	अगर (flags & VMCI_QPFLAG_ATTACH_ONLY)
		वापस VMCI_ERROR_NOT_FOUND;

	/*
	 * Creator's context ID should match handle's context ID or the creator
	 * must allow the context in handle's context ID as the "peer".
	 */
	अगर (handle.context != context_id && handle.context != peer)
		वापस VMCI_ERROR_NO_ACCESS;

	अगर (VMCI_CONTEXT_IS_VM(context_id) && VMCI_CONTEXT_IS_VM(peer))
		वापस VMCI_ERROR_DST_UNREACHABLE;

	/*
	 * Creator's context ID क्रम local queue pairs should match the
	 * peer, अगर a peer is specअगरied.
	 */
	अगर (is_local && peer != VMCI_INVALID_ID && context_id != peer)
		वापस VMCI_ERROR_NO_ACCESS;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस VMCI_ERROR_NO_MEM;

	अगर (vmci_ctx_get_id(context) == VMCI_HOST_CONTEXT_ID && !is_local) अणु
		/*
		 * The queue pair broker entry stores values from the guest
		 * poपूर्णांक of view, so a creating host side endpoपूर्णांक should swap
		 * produce and consume values -- unless it is a local queue
		 * pair, in which हाल no swapping is necessary, since the local
		 * attacher will swap queues.
		 */

		guest_produce_size = consume_size;
		guest_consume_size = produce_size;
	पूर्ण अन्यथा अणु
		guest_produce_size = produce_size;
		guest_consume_size = consume_size;
	पूर्ण

	entry->qp.handle = handle;
	entry->qp.peer = peer;
	entry->qp.flags = flags;
	entry->qp.produce_size = guest_produce_size;
	entry->qp.consume_size = guest_consume_size;
	entry->qp.ref_count = 1;
	entry->create_id = context_id;
	entry->attach_id = VMCI_INVALID_ID;
	entry->state = VMCIQPB_NEW;
	entry->require_trusted_attach =
	    !!(context->priv_flags & VMCI_PRIVILEGE_FLAG_RESTRICTED);
	entry->created_by_trusted =
	    !!(priv_flags & VMCI_PRIVILEGE_FLAG_TRUSTED);
	entry->vmci_page_files = false;
	entry->wakeup_cb = wakeup_cb;
	entry->client_data = client_data;
	entry->produce_q = qp_host_alloc_queue(guest_produce_size);
	अगर (entry->produce_q == शून्य) अणु
		result = VMCI_ERROR_NO_MEM;
		जाओ error;
	पूर्ण
	entry->consume_q = qp_host_alloc_queue(guest_consume_size);
	अगर (entry->consume_q == शून्य) अणु
		result = VMCI_ERROR_NO_MEM;
		जाओ error;
	पूर्ण

	qp_init_queue_mutex(entry->produce_q, entry->consume_q);

	INIT_LIST_HEAD(&entry->qp.list_item);

	अगर (is_local) अणु
		u8 *पंचांगp;

		entry->local_mem = kसुस्मृति(QPE_NUM_PAGES(entry->qp),
					   PAGE_SIZE, GFP_KERNEL);
		अगर (entry->local_mem == शून्य) अणु
			result = VMCI_ERROR_NO_MEM;
			जाओ error;
		पूर्ण
		entry->state = VMCIQPB_CREATED_MEM;
		entry->produce_q->q_header = entry->local_mem;
		पंचांगp = (u8 *)entry->local_mem + PAGE_SIZE *
		    (DIV_ROUND_UP(entry->qp.produce_size, PAGE_SIZE) + 1);
		entry->consume_q->q_header = (काष्ठा vmci_queue_header *)पंचांगp;
	पूर्ण अन्यथा अगर (page_store) अणु
		/*
		 * The VMX alपढ़ोy initialized the queue pair headers, so no
		 * need क्रम the kernel side to करो that.
		 */
		result = qp_host_रेजिस्टर_user_memory(page_store,
						      entry->produce_q,
						      entry->consume_q);
		अगर (result < VMCI_SUCCESS)
			जाओ error;

		entry->state = VMCIQPB_CREATED_MEM;
	पूर्ण अन्यथा अणु
		/*
		 * A create without a page_store may be either a host
		 * side create (in which हाल we are रुकोing क्रम the
		 * guest side to supply the memory) or an old style
		 * queue pair create (in which हाल we will expect a
		 * set page store call as the next step).
		 */
		entry->state = VMCIQPB_CREATED_NO_MEM;
	पूर्ण

	qp_list_add_entry(&qp_broker_list, &entry->qp);
	अगर (ent != शून्य)
		*ent = entry;

	/* Add to resource obj */
	result = vmci_resource_add(&entry->resource,
				   VMCI_RESOURCE_TYPE_QPAIR_HOST,
				   handle);
	अगर (result != VMCI_SUCCESS) अणु
		pr_warn("Failed to add new resource (handle=0x%x:0x%x), error: %d",
			handle.context, handle.resource, result);
		जाओ error;
	पूर्ण

	entry->qp.handle = vmci_resource_handle(&entry->resource);
	अगर (is_local) अणु
		vmci_q_header_init(entry->produce_q->q_header,
				   entry->qp.handle);
		vmci_q_header_init(entry->consume_q->q_header,
				   entry->qp.handle);
	पूर्ण

	vmci_ctx_qp_create(context, entry->qp.handle);

	वापस VMCI_SUCCESS;

 error:
	अगर (entry != शून्य) अणु
		qp_host_मुक्त_queue(entry->produce_q, guest_produce_size);
		qp_host_मुक्त_queue(entry->consume_q, guest_consume_size);
		kमुक्त(entry);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Enqueues an event datagram to notअगरy the peer VM attached to
 * the given queue pair handle about attach/detach event by the
 * given VM.  Returns Payload size of datagram enqueued on
 * success, error code otherwise.
 */
अटल पूर्णांक qp_notअगरy_peer(bool attach,
			  काष्ठा vmci_handle handle,
			  u32 my_id,
			  u32 peer_id)
अणु
	पूर्णांक rv;
	काष्ठा vmci_event_qp ev;

	अगर (vmci_handle_is_invalid(handle) || my_id == VMCI_INVALID_ID ||
	    peer_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	/*
	 * In vmci_ctx_enqueue_datagram() we enक्रमce the upper limit on
	 * number of pending events from the hypervisor to a given VM
	 * otherwise a rogue VM could करो an arbitrary number of attach
	 * and detach operations causing memory pressure in the host
	 * kernel.
	 */

	ev.msg.hdr.dst = vmci_make_handle(peer_id, VMCI_EVENT_HANDLER);
	ev.msg.hdr.src = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					  VMCI_CONTEXT_RESOURCE_ID);
	ev.msg.hdr.payload_size = माप(ev) - माप(ev.msg.hdr);
	ev.msg.event_data.event = attach ?
	    VMCI_EVENT_QP_PEER_ATTACH : VMCI_EVENT_QP_PEER_DETACH;
	ev.payload.handle = handle;
	ev.payload.peer_id = my_id;

	rv = vmci_datagram_dispatch(VMCI_HYPERVISOR_CONTEXT_ID,
				    &ev.msg.hdr, false);
	अगर (rv < VMCI_SUCCESS)
		pr_warn("Failed to enqueue queue_pair %s event datagram for context (ID=0x%x)\n",
			attach ? "ATTACH" : "DETACH", peer_id);

	वापस rv;
पूर्ण

/*
 * The second endpoपूर्णांक issuing a queue pair allocation will attach to
 * the queue pair रेजिस्टरed with the queue pair broker.
 *
 * If the attacher is a guest, it will associate a VMX भव address
 * range with the queue pair as specअगरied by the page_store. At this
 * poपूर्णांक, the alपढ़ोy attach host endpoपूर्णांक may start using the queue
 * pair, and an attach event is sent to it. For compatibility with
 * older VMX'en, that used a separate step to set the VMX भव
 * address range, the भव address range can be रेजिस्टरed later
 * using vmci_qp_broker_set_page_store. In that हाल, a page_store of
 * शून्य should be used, and the attach event will be generated once
 * the actual page store has been set.
 *
 * If the attacher is the host, a page_store of शून्य should be used as
 * well, since the page store inक्रमmation is alपढ़ोy set by the guest.
 *
 * For new VMX and host callers, the queue pair will be moved to the
 * VMCIQPB_ATTACHED_MEM state, and क्रम older VMX callers, it will be
 * moved to the VMCOQPB_ATTACHED_NO_MEM state.
 */
अटल पूर्णांक qp_broker_attach(काष्ठा qp_broker_entry *entry,
			    u32 peer,
			    u32 flags,
			    u32 priv_flags,
			    u64 produce_size,
			    u64 consume_size,
			    काष्ठा vmci_qp_page_store *page_store,
			    काष्ठा vmci_ctx *context,
			    vmci_event_release_cb wakeup_cb,
			    व्योम *client_data,
			    काष्ठा qp_broker_entry **ent)
अणु
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	bool is_local = flags & VMCI_QPFLAG_LOCAL;
	पूर्णांक result;

	अगर (entry->state != VMCIQPB_CREATED_NO_MEM &&
	    entry->state != VMCIQPB_CREATED_MEM)
		वापस VMCI_ERROR_UNAVAILABLE;

	अगर (is_local) अणु
		अगर (!(entry->qp.flags & VMCI_QPFLAG_LOCAL) ||
		    context_id != entry->create_id) अणु
			वापस VMCI_ERROR_INVALID_ARGS;
		पूर्ण
	पूर्ण अन्यथा अगर (context_id == entry->create_id ||
		   context_id == entry->attach_id) अणु
		वापस VMCI_ERROR_ALREADY_EXISTS;
	पूर्ण

	अगर (VMCI_CONTEXT_IS_VM(context_id) &&
	    VMCI_CONTEXT_IS_VM(entry->create_id))
		वापस VMCI_ERROR_DST_UNREACHABLE;

	/*
	 * If we are attaching from a restricted context then the queuepair
	 * must have been created by a trusted endpoपूर्णांक.
	 */
	अगर ((context->priv_flags & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
	    !entry->created_by_trusted)
		वापस VMCI_ERROR_NO_ACCESS;

	/*
	 * If we are attaching to a queuepair that was created by a restricted
	 * context then we must be trusted.
	 */
	अगर (entry->require_trusted_attach &&
	    (!(priv_flags & VMCI_PRIVILEGE_FLAG_TRUSTED)))
		वापस VMCI_ERROR_NO_ACCESS;

	/*
	 * If the creator specअगरies VMCI_INVALID_ID in "peer" field, access
	 * control check is not perक्रमmed.
	 */
	अगर (entry->qp.peer != VMCI_INVALID_ID && entry->qp.peer != context_id)
		वापस VMCI_ERROR_NO_ACCESS;

	अगर (entry->create_id == VMCI_HOST_CONTEXT_ID) अणु
		/*
		 * Do not attach अगर the caller करोesn't support Host Queue Pairs
		 * and a host created this queue pair.
		 */

		अगर (!vmci_ctx_supports_host_qp(context))
			वापस VMCI_ERROR_INVALID_RESOURCE;

	पूर्ण अन्यथा अगर (context_id == VMCI_HOST_CONTEXT_ID) अणु
		काष्ठा vmci_ctx *create_context;
		bool supports_host_qp;

		/*
		 * Do not attach a host to a user created queue pair अगर that
		 * user करोesn't support host queue pair end poपूर्णांकs.
		 */

		create_context = vmci_ctx_get(entry->create_id);
		supports_host_qp = vmci_ctx_supports_host_qp(create_context);
		vmci_ctx_put(create_context);

		अगर (!supports_host_qp)
			वापस VMCI_ERROR_INVALID_RESOURCE;
	पूर्ण

	अगर ((entry->qp.flags & ~VMCI_QP_ASYMM) != (flags & ~VMCI_QP_ASYMM_PEER))
		वापस VMCI_ERROR_QUEUEPAIR_MISMATCH;

	अगर (context_id != VMCI_HOST_CONTEXT_ID) अणु
		/*
		 * The queue pair broker entry stores values from the guest
		 * poपूर्णांक of view, so an attaching guest should match the values
		 * stored in the entry.
		 */

		अगर (entry->qp.produce_size != produce_size ||
		    entry->qp.consume_size != consume_size) अणु
			वापस VMCI_ERROR_QUEUEPAIR_MISMATCH;
		पूर्ण
	पूर्ण अन्यथा अगर (entry->qp.produce_size != consume_size ||
		   entry->qp.consume_size != produce_size) अणु
		वापस VMCI_ERROR_QUEUEPAIR_MISMATCH;
	पूर्ण

	अगर (context_id != VMCI_HOST_CONTEXT_ID) अणु
		/*
		 * If a guest attached to a queue pair, it will supply
		 * the backing memory.  If this is a pre NOVMVM vmx,
		 * the backing memory will be supplied by calling
		 * vmci_qp_broker_set_page_store() following the
		 * वापस of the vmci_qp_broker_alloc() call. If it is
		 * a vmx of version NOVMVM or later, the page store
		 * must be supplied as part of the
		 * vmci_qp_broker_alloc call.  Under all circumstances
		 * must the initially created queue pair not have any
		 * memory associated with it alपढ़ोy.
		 */

		अगर (entry->state != VMCIQPB_CREATED_NO_MEM)
			वापस VMCI_ERROR_INVALID_ARGS;

		अगर (page_store != शून्य) अणु
			/*
			 * Patch up host state to poपूर्णांक to guest
			 * supplied memory. The VMX alपढ़ोy
			 * initialized the queue pair headers, so no
			 * need क्रम the kernel side to करो that.
			 */

			result = qp_host_रेजिस्टर_user_memory(page_store,
							      entry->produce_q,
							      entry->consume_q);
			अगर (result < VMCI_SUCCESS)
				वापस result;

			entry->state = VMCIQPB_ATTACHED_MEM;
		पूर्ण अन्यथा अणु
			entry->state = VMCIQPB_ATTACHED_NO_MEM;
		पूर्ण
	पूर्ण अन्यथा अगर (entry->state == VMCIQPB_CREATED_NO_MEM) अणु
		/*
		 * The host side is attempting to attach to a queue
		 * pair that करोesn't have any memory associated with
		 * it. This must be a pre NOVMVM vmx that hasn't set
		 * the page store inक्रमmation yet, or a quiesced VM.
		 */

		वापस VMCI_ERROR_UNAVAILABLE;
	पूर्ण अन्यथा अणु
		/* The host side has successfully attached to a queue pair. */
		entry->state = VMCIQPB_ATTACHED_MEM;
	पूर्ण

	अगर (entry->state == VMCIQPB_ATTACHED_MEM) अणु
		result =
		    qp_notअगरy_peer(true, entry->qp.handle, context_id,
				   entry->create_id);
		अगर (result < VMCI_SUCCESS)
			pr_warn("Failed to notify peer (ID=0x%x) of attach to queue pair (handle=0x%x:0x%x)\n",
				entry->create_id, entry->qp.handle.context,
				entry->qp.handle.resource);
	पूर्ण

	entry->attach_id = context_id;
	entry->qp.ref_count++;
	अगर (wakeup_cb) अणु
		entry->wakeup_cb = wakeup_cb;
		entry->client_data = client_data;
	पूर्ण

	/*
	 * When attaching to local queue pairs, the context alपढ़ोy has
	 * an entry tracking the queue pair, so करोn't add another one.
	 */
	अगर (!is_local)
		vmci_ctx_qp_create(context, entry->qp.handle);

	अगर (ent != शून्य)
		*ent = entry;

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * queue_pair_Alloc क्रम use when setting up queue pair endpoपूर्णांकs
 * on the host.
 */
अटल पूर्णांक qp_broker_alloc(काष्ठा vmci_handle handle,
			   u32 peer,
			   u32 flags,
			   u32 priv_flags,
			   u64 produce_size,
			   u64 consume_size,
			   काष्ठा vmci_qp_page_store *page_store,
			   काष्ठा vmci_ctx *context,
			   vmci_event_release_cb wakeup_cb,
			   व्योम *client_data,
			   काष्ठा qp_broker_entry **ent,
			   bool *swap)
अणु
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	bool create;
	काष्ठा qp_broker_entry *entry = शून्य;
	bool is_local = flags & VMCI_QPFLAG_LOCAL;
	पूर्णांक result;

	अगर (vmci_handle_is_invalid(handle) ||
	    (flags & ~VMCI_QP_ALL_FLAGS) || is_local ||
	    !(produce_size || consume_size) ||
	    !context || context_id == VMCI_INVALID_ID ||
	    handle.context == VMCI_INVALID_ID) अणु
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	अगर (page_store && !VMCI_QP_PAGESTORE_IS_WELLFORMED(page_store))
		वापस VMCI_ERROR_INVALID_ARGS;

	/*
	 * In the initial argument check, we ensure that non-vmkernel hosts
	 * are not allowed to create local queue pairs.
	 */

	mutex_lock(&qp_broker_list.mutex);

	अगर (!is_local && vmci_ctx_qp_exists(context, handle)) अणु
		pr_devel("Context (ID=0x%x) already attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		mutex_unlock(&qp_broker_list.mutex);
		वापस VMCI_ERROR_ALREADY_EXISTS;
	पूर्ण

	अगर (handle.resource != VMCI_INVALID_ID)
		entry = qp_broker_handle_to_entry(handle);

	अगर (!entry) अणु
		create = true;
		result =
		    qp_broker_create(handle, peer, flags, priv_flags,
				     produce_size, consume_size, page_store,
				     context, wakeup_cb, client_data, ent);
	पूर्ण अन्यथा अणु
		create = false;
		result =
		    qp_broker_attach(entry, peer, flags, priv_flags,
				     produce_size, consume_size, page_store,
				     context, wakeup_cb, client_data, ent);
	पूर्ण

	mutex_unlock(&qp_broker_list.mutex);

	अगर (swap)
		*swap = (context_id == VMCI_HOST_CONTEXT_ID) &&
		    !(create && is_local);

	वापस result;
पूर्ण

/*
 * This function implements the kernel API क्रम allocating a queue
 * pair.
 */
अटल पूर्णांक qp_alloc_host_work(काष्ठा vmci_handle *handle,
			      काष्ठा vmci_queue **produce_q,
			      u64 produce_size,
			      काष्ठा vmci_queue **consume_q,
			      u64 consume_size,
			      u32 peer,
			      u32 flags,
			      u32 priv_flags,
			      vmci_event_release_cb wakeup_cb,
			      व्योम *client_data)
अणु
	काष्ठा vmci_handle new_handle;
	काष्ठा vmci_ctx *context;
	काष्ठा qp_broker_entry *entry;
	पूर्णांक result;
	bool swap;

	अगर (vmci_handle_is_invalid(*handle)) अणु
		new_handle = vmci_make_handle(
			VMCI_HOST_CONTEXT_ID, VMCI_INVALID_ID);
	पूर्ण अन्यथा
		new_handle = *handle;

	context = vmci_ctx_get(VMCI_HOST_CONTEXT_ID);
	entry = शून्य;
	result =
	    qp_broker_alloc(new_handle, peer, flags, priv_flags,
			    produce_size, consume_size, शून्य, context,
			    wakeup_cb, client_data, &entry, &swap);
	अगर (result == VMCI_SUCCESS) अणु
		अगर (swap) अणु
			/*
			 * If this is a local queue pair, the attacher
			 * will swap around produce and consume
			 * queues.
			 */

			*produce_q = entry->consume_q;
			*consume_q = entry->produce_q;
		पूर्ण अन्यथा अणु
			*produce_q = entry->produce_q;
			*consume_q = entry->consume_q;
		पूर्ण

		*handle = vmci_resource_handle(&entry->resource);
	पूर्ण अन्यथा अणु
		*handle = VMCI_INVALID_HANDLE;
		pr_devel("queue pair broker failed to alloc (result=%d)\n",
			 result);
	पूर्ण
	vmci_ctx_put(context);
	वापस result;
पूर्ण

/*
 * Allocates a VMCI queue_pair. Only checks validity of input
 * arguments. The real work is करोne in the host or guest
 * specअगरic function.
 */
पूर्णांक vmci_qp_alloc(काष्ठा vmci_handle *handle,
		  काष्ठा vmci_queue **produce_q,
		  u64 produce_size,
		  काष्ठा vmci_queue **consume_q,
		  u64 consume_size,
		  u32 peer,
		  u32 flags,
		  u32 priv_flags,
		  bool guest_endpoपूर्णांक,
		  vmci_event_release_cb wakeup_cb,
		  व्योम *client_data)
अणु
	अगर (!handle || !produce_q || !consume_q ||
	    (!produce_size && !consume_size) || (flags & ~VMCI_QP_ALL_FLAGS))
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (guest_endpoपूर्णांक) अणु
		वापस qp_alloc_guest_work(handle, produce_q,
					   produce_size, consume_q,
					   consume_size, peer,
					   flags, priv_flags);
	पूर्ण अन्यथा अणु
		वापस qp_alloc_host_work(handle, produce_q,
					  produce_size, consume_q,
					  consume_size, peer, flags,
					  priv_flags, wakeup_cb, client_data);
	पूर्ण
पूर्ण

/*
 * This function implements the host kernel API क्रम detaching from
 * a queue pair.
 */
अटल पूर्णांक qp_detatch_host_work(काष्ठा vmci_handle handle)
अणु
	पूर्णांक result;
	काष्ठा vmci_ctx *context;

	context = vmci_ctx_get(VMCI_HOST_CONTEXT_ID);

	result = vmci_qp_broker_detach(handle, context);

	vmci_ctx_put(context);
	वापस result;
पूर्ण

/*
 * Detaches from a VMCI queue_pair. Only checks validity of input argument.
 * Real work is करोne in the host or guest specअगरic function.
 */
अटल पूर्णांक qp_detatch(काष्ठा vmci_handle handle, bool guest_endpoपूर्णांक)
अणु
	अगर (vmci_handle_is_invalid(handle))
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (guest_endpoपूर्णांक)
		वापस qp_detatch_guest_work(handle);
	अन्यथा
		वापस qp_detatch_host_work(handle);
पूर्ण

/*
 * Returns the entry from the head of the list. Assumes that the list is
 * locked.
 */
अटल काष्ठा qp_entry *qp_list_get_head(काष्ठा qp_list *qp_list)
अणु
	अगर (!list_empty(&qp_list->head)) अणु
		काष्ठा qp_entry *entry =
		    list_first_entry(&qp_list->head, काष्ठा qp_entry,
				     list_item);
		वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम vmci_qp_broker_निकास(व्योम)
अणु
	काष्ठा qp_entry *entry;
	काष्ठा qp_broker_entry *be;

	mutex_lock(&qp_broker_list.mutex);

	जबतक ((entry = qp_list_get_head(&qp_broker_list))) अणु
		be = (काष्ठा qp_broker_entry *)entry;

		qp_list_हटाओ_entry(&qp_broker_list, entry);
		kमुक्त(be);
	पूर्ण

	mutex_unlock(&qp_broker_list.mutex);
पूर्ण

/*
 * Requests that a queue pair be allocated with the VMCI queue
 * pair broker. Allocates a queue pair entry अगर one करोes not
 * exist. Attaches to one अगर it exists, and retrieves the page
 * files backing that queue_pair.  Assumes that the queue pair
 * broker lock is held.
 */
पूर्णांक vmci_qp_broker_alloc(काष्ठा vmci_handle handle,
			 u32 peer,
			 u32 flags,
			 u32 priv_flags,
			 u64 produce_size,
			 u64 consume_size,
			 काष्ठा vmci_qp_page_store *page_store,
			 काष्ठा vmci_ctx *context)
अणु
	अगर (!QP_SIZES_ARE_VALID(produce_size, consume_size))
		वापस VMCI_ERROR_NO_RESOURCES;

	वापस qp_broker_alloc(handle, peer, flags, priv_flags,
			       produce_size, consume_size,
			       page_store, context, शून्य, शून्य, शून्य, शून्य);
पूर्ण

/*
 * VMX'en with versions lower than VMCI_VERSION_NOVMVM use a separate
 * step to add the UVAs of the VMX mapping of the queue pair. This function
 * provides backwards compatibility with such VMX'en, and takes care of
 * रेजिस्टरing the page store क्रम a queue pair previously allocated by the
 * VMX during create or attach. This function will move the queue pair state
 * to either from VMCIQBP_CREATED_NO_MEM to VMCIQBP_CREATED_MEM or
 * VMCIQBP_ATTACHED_NO_MEM to VMCIQBP_ATTACHED_MEM. If moving to the
 * attached state with memory, the queue pair is पढ़ोy to be used by the
 * host peer, and an attached event will be generated.
 *
 * Assumes that the queue pair broker lock is held.
 *
 * This function is only used by the hosted platक्रमm, since there is no
 * issue with backwards compatibility क्रम vmkernel.
 */
पूर्णांक vmci_qp_broker_set_page_store(काष्ठा vmci_handle handle,
				  u64 produce_uva,
				  u64 consume_uva,
				  काष्ठा vmci_ctx *context)
अणु
	काष्ठा qp_broker_entry *entry;
	पूर्णांक result;
	स्थिर u32 context_id = vmci_ctx_get_id(context);

	अगर (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	/*
	 * We only support guest to host queue pairs, so the VMX must
	 * supply UVAs क्रम the mapped page files.
	 */

	अगर (produce_uva == 0 || consume_uva == 0)
		वापस VMCI_ERROR_INVALID_ARGS;

	mutex_lock(&qp_broker_list.mutex);

	अगर (!vmci_ctx_qp_exists(context, handle)) अणु
		pr_warn("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	entry = qp_broker_handle_to_entry(handle);
	अगर (!entry) अणु
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	/*
	 * If I'm the owner then I can set the page store.
	 *
	 * Or, अगर a host created the queue_pair and I'm the attached peer
	 * then I can set the page store.
	 */
	अगर (entry->create_id != context_id &&
	    (entry->create_id != VMCI_HOST_CONTEXT_ID ||
	     entry->attach_id != context_id)) अणु
		result = VMCI_ERROR_QUEUEPAIR_NOTOWNER;
		जाओ out;
	पूर्ण

	अगर (entry->state != VMCIQPB_CREATED_NO_MEM &&
	    entry->state != VMCIQPB_ATTACHED_NO_MEM) अणु
		result = VMCI_ERROR_UNAVAILABLE;
		जाओ out;
	पूर्ण

	result = qp_host_get_user_memory(produce_uva, consume_uva,
					 entry->produce_q, entry->consume_q);
	अगर (result < VMCI_SUCCESS)
		जाओ out;

	result = qp_host_map_queues(entry->produce_q, entry->consume_q);
	अगर (result < VMCI_SUCCESS) अणु
		qp_host_unरेजिस्टर_user_memory(entry->produce_q,
					       entry->consume_q);
		जाओ out;
	पूर्ण

	अगर (entry->state == VMCIQPB_CREATED_NO_MEM)
		entry->state = VMCIQPB_CREATED_MEM;
	अन्यथा
		entry->state = VMCIQPB_ATTACHED_MEM;

	entry->vmci_page_files = true;

	अगर (entry->state == VMCIQPB_ATTACHED_MEM) अणु
		result =
		    qp_notअगरy_peer(true, handle, context_id, entry->create_id);
		अगर (result < VMCI_SUCCESS) अणु
			pr_warn("Failed to notify peer (ID=0x%x) of attach to queue pair (handle=0x%x:0x%x)\n",
				entry->create_id, entry->qp.handle.context,
				entry->qp.handle.resource);
		पूर्ण
	पूर्ण

	result = VMCI_SUCCESS;
 out:
	mutex_unlock(&qp_broker_list.mutex);
	वापस result;
पूर्ण

/*
 * Resets saved queue headers क्रम the given QP broker
 * entry. Should be used when guest memory becomes available
 * again, or the guest detaches.
 */
अटल व्योम qp_reset_saved_headers(काष्ठा qp_broker_entry *entry)
अणु
	entry->produce_q->saved_header = शून्य;
	entry->consume_q->saved_header = शून्य;
पूर्ण

/*
 * The मुख्य entry poपूर्णांक क्रम detaching from a queue pair रेजिस्टरed with the
 * queue pair broker. If more than one endpoपूर्णांक is attached to the queue
 * pair, the first endpoपूर्णांक will मुख्यly decrement a reference count and
 * generate a notअगरication to its peer. The last endpoपूर्णांक will clean up
 * the queue pair state रेजिस्टरed with the broker.
 *
 * When a guest endpoपूर्णांक detaches, it will unmap and unरेजिस्टर the guest
 * memory backing the queue pair. If the host is still attached, it will
 * no दीर्घer be able to access the queue pair content.
 *
 * If the queue pair is alपढ़ोy in a state where there is no memory
 * रेजिस्टरed क्रम the queue pair (any *_NO_MEM state), it will transition to
 * the VMCIQPB_SHUTDOWN_NO_MEM state. This will also happen, अगर a guest
 * endpoपूर्णांक is the first of two endpoपूर्णांकs to detach. If the host endpoपूर्णांक is
 * the first out of two to detach, the queue pair will move to the
 * VMCIQPB_SHUTDOWN_MEM state.
 */
पूर्णांक vmci_qp_broker_detach(काष्ठा vmci_handle handle, काष्ठा vmci_ctx *context)
अणु
	काष्ठा qp_broker_entry *entry;
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	u32 peer_id;
	bool is_local = false;
	पूर्णांक result;

	अगर (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID) अणु
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	mutex_lock(&qp_broker_list.mutex);

	अगर (!vmci_ctx_qp_exists(context, handle)) अणु
		pr_devel("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	entry = qp_broker_handle_to_entry(handle);
	अगर (!entry) अणु
		pr_devel("Context (ID=0x%x) reports being attached to queue pair(handle=0x%x:0x%x) that isn't present in broker\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	अगर (context_id != entry->create_id && context_id != entry->attach_id) अणु
		result = VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
		जाओ out;
	पूर्ण

	अगर (context_id == entry->create_id) अणु
		peer_id = entry->attach_id;
		entry->create_id = VMCI_INVALID_ID;
	पूर्ण अन्यथा अणु
		peer_id = entry->create_id;
		entry->attach_id = VMCI_INVALID_ID;
	पूर्ण
	entry->qp.ref_count--;

	is_local = entry->qp.flags & VMCI_QPFLAG_LOCAL;

	अगर (context_id != VMCI_HOST_CONTEXT_ID) अणु
		bool headers_mapped;

		/*
		 * Pre NOVMVM vmx'en may detach from a queue pair
		 * beक्रमe setting the page store, and in that हाल
		 * there is no user memory to detach from. Also, more
		 * recent VMX'en may detach from a queue pair in the
		 * quiesced state.
		 */

		qp_acquire_queue_mutex(entry->produce_q);
		headers_mapped = entry->produce_q->q_header ||
		    entry->consume_q->q_header;
		अगर (QPBROKERSTATE_HAS_MEM(entry)) अणु
			result =
			    qp_host_unmap_queues(INVALID_VMCI_GUEST_MEM_ID,
						 entry->produce_q,
						 entry->consume_q);
			अगर (result < VMCI_SUCCESS)
				pr_warn("Failed to unmap queue headers for queue pair (handle=0x%x:0x%x,result=%d)\n",
					handle.context, handle.resource,
					result);

			qp_host_unरेजिस्टर_user_memory(entry->produce_q,
						       entry->consume_q);

		पूर्ण

		अगर (!headers_mapped)
			qp_reset_saved_headers(entry);

		qp_release_queue_mutex(entry->produce_q);

		अगर (!headers_mapped && entry->wakeup_cb)
			entry->wakeup_cb(entry->client_data);

	पूर्ण अन्यथा अणु
		अगर (entry->wakeup_cb) अणु
			entry->wakeup_cb = शून्य;
			entry->client_data = शून्य;
		पूर्ण
	पूर्ण

	अगर (entry->qp.ref_count == 0) अणु
		qp_list_हटाओ_entry(&qp_broker_list, &entry->qp);

		अगर (is_local)
			kमुक्त(entry->local_mem);

		qp_cleanup_queue_mutex(entry->produce_q, entry->consume_q);
		qp_host_मुक्त_queue(entry->produce_q, entry->qp.produce_size);
		qp_host_मुक्त_queue(entry->consume_q, entry->qp.consume_size);
		/* Unlink from resource hash table and मुक्त callback */
		vmci_resource_हटाओ(&entry->resource);

		kमुक्त(entry);

		vmci_ctx_qp_destroy(context, handle);
	पूर्ण अन्यथा अणु
		qp_notअगरy_peer(false, handle, context_id, peer_id);
		अगर (context_id == VMCI_HOST_CONTEXT_ID &&
		    QPBROKERSTATE_HAS_MEM(entry)) अणु
			entry->state = VMCIQPB_SHUTDOWN_MEM;
		पूर्ण अन्यथा अणु
			entry->state = VMCIQPB_SHUTDOWN_NO_MEM;
		पूर्ण

		अगर (!is_local)
			vmci_ctx_qp_destroy(context, handle);

	पूर्ण
	result = VMCI_SUCCESS;
 out:
	mutex_unlock(&qp_broker_list.mutex);
	वापस result;
पूर्ण

/*
 * Establishes the necessary mappings क्रम a queue pair given a
 * reference to the queue pair guest memory. This is usually
 * called when a guest is unquiesced and the VMX is allowed to
 * map guest memory once again.
 */
पूर्णांक vmci_qp_broker_map(काष्ठा vmci_handle handle,
		       काष्ठा vmci_ctx *context,
		       u64 guest_mem)
अणु
	काष्ठा qp_broker_entry *entry;
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	पूर्णांक result;

	अगर (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	mutex_lock(&qp_broker_list.mutex);

	अगर (!vmci_ctx_qp_exists(context, handle)) अणु
		pr_devel("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	entry = qp_broker_handle_to_entry(handle);
	अगर (!entry) अणु
		pr_devel("Context (ID=0x%x) reports being attached to queue pair (handle=0x%x:0x%x) that isn't present in broker\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	अगर (context_id != entry->create_id && context_id != entry->attach_id) अणु
		result = VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
		जाओ out;
	पूर्ण

	result = VMCI_SUCCESS;

	अगर (context_id != VMCI_HOST_CONTEXT_ID) अणु
		काष्ठा vmci_qp_page_store page_store;

		page_store.pages = guest_mem;
		page_store.len = QPE_NUM_PAGES(entry->qp);

		qp_acquire_queue_mutex(entry->produce_q);
		qp_reset_saved_headers(entry);
		result =
		    qp_host_रेजिस्टर_user_memory(&page_store,
						 entry->produce_q,
						 entry->consume_q);
		qp_release_queue_mutex(entry->produce_q);
		अगर (result == VMCI_SUCCESS) अणु
			/* Move state from *_NO_MEM to *_MEM */

			entry->state++;

			अगर (entry->wakeup_cb)
				entry->wakeup_cb(entry->client_data);
		पूर्ण
	पूर्ण

 out:
	mutex_unlock(&qp_broker_list.mutex);
	वापस result;
पूर्ण

/*
 * Saves a snapshot of the queue headers क्रम the given QP broker
 * entry. Should be used when guest memory is unmapped.
 * Results:
 * VMCI_SUCCESS on success, appropriate error code अगर guest memory
 * can't be accessed..
 */
अटल पूर्णांक qp_save_headers(काष्ठा qp_broker_entry *entry)
अणु
	पूर्णांक result;

	अगर (entry->produce_q->saved_header != शून्य &&
	    entry->consume_q->saved_header != शून्य) अणु
		/*
		 *  If the headers have alपढ़ोy been saved, we करोn't need to करो
		 *  it again, and we करोn't want to map in the headers
		 *  unnecessarily.
		 */

		वापस VMCI_SUCCESS;
	पूर्ण

	अगर (शून्य == entry->produce_q->q_header ||
	    शून्य == entry->consume_q->q_header) अणु
		result = qp_host_map_queues(entry->produce_q, entry->consume_q);
		अगर (result < VMCI_SUCCESS)
			वापस result;
	पूर्ण

	स_नकल(&entry->saved_produce_q, entry->produce_q->q_header,
	       माप(entry->saved_produce_q));
	entry->produce_q->saved_header = &entry->saved_produce_q;
	स_नकल(&entry->saved_consume_q, entry->consume_q->q_header,
	       माप(entry->saved_consume_q));
	entry->consume_q->saved_header = &entry->saved_consume_q;

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Removes all references to the guest memory of a given queue pair, and
 * will move the queue pair from state *_MEM to *_NO_MEM. It is usually
 * called when a VM is being quiesced where access to guest memory should
 * aव्योमed.
 */
पूर्णांक vmci_qp_broker_unmap(काष्ठा vmci_handle handle,
			 काष्ठा vmci_ctx *context,
			 u32 gid)
अणु
	काष्ठा qp_broker_entry *entry;
	स्थिर u32 context_id = vmci_ctx_get_id(context);
	पूर्णांक result;

	अगर (vmci_handle_is_invalid(handle) || !context ||
	    context_id == VMCI_INVALID_ID)
		वापस VMCI_ERROR_INVALID_ARGS;

	mutex_lock(&qp_broker_list.mutex);

	अगर (!vmci_ctx_qp_exists(context, handle)) अणु
		pr_devel("Context (ID=0x%x) not attached to queue pair (handle=0x%x:0x%x)\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	entry = qp_broker_handle_to_entry(handle);
	अगर (!entry) अणु
		pr_devel("Context (ID=0x%x) reports being attached to queue pair (handle=0x%x:0x%x) that isn't present in broker\n",
			 context_id, handle.context, handle.resource);
		result = VMCI_ERROR_NOT_FOUND;
		जाओ out;
	पूर्ण

	अगर (context_id != entry->create_id && context_id != entry->attach_id) अणु
		result = VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
		जाओ out;
	पूर्ण

	अगर (context_id != VMCI_HOST_CONTEXT_ID) अणु
		qp_acquire_queue_mutex(entry->produce_q);
		result = qp_save_headers(entry);
		अगर (result < VMCI_SUCCESS)
			pr_warn("Failed to save queue headers for queue pair (handle=0x%x:0x%x,result=%d)\n",
				handle.context, handle.resource, result);

		qp_host_unmap_queues(gid, entry->produce_q, entry->consume_q);

		/*
		 * On hosted, when we unmap queue pairs, the VMX will also
		 * unmap the guest memory, so we invalidate the previously
		 * रेजिस्टरed memory. If the queue pair is mapped again at a
		 * later poपूर्णांक in समय, we will need to reरेजिस्टर the user
		 * memory with a possibly new user VA.
		 */
		qp_host_unरेजिस्टर_user_memory(entry->produce_q,
					       entry->consume_q);

		/*
		 * Move state from *_MEM to *_NO_MEM.
		 */
		entry->state--;

		qp_release_queue_mutex(entry->produce_q);
	पूर्ण

	result = VMCI_SUCCESS;

 out:
	mutex_unlock(&qp_broker_list.mutex);
	वापस result;
पूर्ण

/*
 * Destroys all guest queue pair endpoपूर्णांकs. If active guest queue
 * pairs still exist, hypercalls to attempt detach from these
 * queue pairs will be made. Any failure to detach is silently
 * ignored.
 */
व्योम vmci_qp_guest_endpoपूर्णांकs_निकास(व्योम)
अणु
	काष्ठा qp_entry *entry;
	काष्ठा qp_guest_endpoपूर्णांक *ep;

	mutex_lock(&qp_guest_endpoपूर्णांकs.mutex);

	जबतक ((entry = qp_list_get_head(&qp_guest_endpoपूर्णांकs))) अणु
		ep = (काष्ठा qp_guest_endpoपूर्णांक *)entry;

		/* Don't make a hypercall क्रम local queue_pairs. */
		अगर (!(entry->flags & VMCI_QPFLAG_LOCAL))
			qp_detatch_hypercall(entry->handle);

		/* We cannot fail the निकास, so let's reset ref_count. */
		entry->ref_count = 0;
		qp_list_हटाओ_entry(&qp_guest_endpoपूर्णांकs, entry);

		qp_guest_endpoपूर्णांक_destroy(ep);
	पूर्ण

	mutex_unlock(&qp_guest_endpoपूर्णांकs.mutex);
पूर्ण

/*
 * Helper routine that will lock the queue pair beक्रमe subsequent
 * operations.
 * Note: Non-blocking on the host side is currently only implemented in ESX.
 * Since non-blocking isn't yet implemented on the host personality we
 * have no reason to acquire a spin lock.  So to aव्योम the use of an
 * unnecessary lock only acquire the mutex अगर we can block.
 */
अटल व्योम qp_lock(स्थिर काष्ठा vmci_qp *qpair)
अणु
	qp_acquire_queue_mutex(qpair->produce_q);
पूर्ण

/*
 * Helper routine that unlocks the queue pair after calling
 * qp_lock.
 */
अटल व्योम qp_unlock(स्थिर काष्ठा vmci_qp *qpair)
अणु
	qp_release_queue_mutex(qpair->produce_q);
पूर्ण

/*
 * The queue headers may not be mapped at all बार. If a queue is
 * currently not mapped, it will be attempted to करो so.
 */
अटल पूर्णांक qp_map_queue_headers(काष्ठा vmci_queue *produce_q,
				काष्ठा vmci_queue *consume_q)
अणु
	पूर्णांक result;

	अगर (शून्य == produce_q->q_header || शून्य == consume_q->q_header) अणु
		result = qp_host_map_queues(produce_q, consume_q);
		अगर (result < VMCI_SUCCESS)
			वापस (produce_q->saved_header &&
				consume_q->saved_header) ?
			    VMCI_ERROR_QUEUEPAIR_NOT_READY :
			    VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
	पूर्ण

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Helper routine that will retrieve the produce and consume
 * headers of a given queue pair. If the guest memory of the
 * queue pair is currently not available, the saved queue headers
 * will be वापसed, अगर these are available.
 */
अटल पूर्णांक qp_get_queue_headers(स्थिर काष्ठा vmci_qp *qpair,
				काष्ठा vmci_queue_header **produce_q_header,
				काष्ठा vmci_queue_header **consume_q_header)
अणु
	पूर्णांक result;

	result = qp_map_queue_headers(qpair->produce_q, qpair->consume_q);
	अगर (result == VMCI_SUCCESS) अणु
		*produce_q_header = qpair->produce_q->q_header;
		*consume_q_header = qpair->consume_q->q_header;
	पूर्ण अन्यथा अगर (qpair->produce_q->saved_header &&
		   qpair->consume_q->saved_header) अणु
		*produce_q_header = qpair->produce_q->saved_header;
		*consume_q_header = qpair->consume_q->saved_header;
		result = VMCI_SUCCESS;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Callback from VMCI queue pair broker indicating that a queue
 * pair that was previously not पढ़ोy, now either is पढ़ोy or
 * gone क्रमever.
 */
अटल पूर्णांक qp_wakeup_cb(व्योम *client_data)
अणु
	काष्ठा vmci_qp *qpair = (काष्ठा vmci_qp *)client_data;

	qp_lock(qpair);
	जबतक (qpair->blocked > 0) अणु
		qpair->blocked--;
		qpair->generation++;
		wake_up(&qpair->event);
	पूर्ण
	qp_unlock(qpair);

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Makes the calling thपढ़ो रुको क्रम the queue pair to become
 * पढ़ोy क्रम host side access.  Returns true when thपढ़ो is
 * woken up after queue pair state change, false otherwise.
 */
अटल bool qp_रुको_क्रम_पढ़ोy_queue(काष्ठा vmci_qp *qpair)
अणु
	अचिन्हित पूर्णांक generation;

	qpair->blocked++;
	generation = qpair->generation;
	qp_unlock(qpair);
	रुको_event(qpair->event, generation != qpair->generation);
	qp_lock(qpair);

	वापस true;
पूर्ण

/*
 * Enqueues a given buffer to the produce queue using the provided
 * function. As many bytes as possible (space available in the queue)
 * are enqueued.  Assumes the queue->mutex has been acquired.  Returns
 * VMCI_ERROR_QUEUEPAIR_NOSPACE अगर no space was available to enqueue
 * data, VMCI_ERROR_INVALID_SIZE, अगर any queue poपूर्णांकer is outside the
 * queue (as defined by the queue size), VMCI_ERROR_INVALID_ARGS, अगर
 * an error occured when accessing the buffer,
 * VMCI_ERROR_QUEUEPAIR_NOTATTACHED, अगर the queue pair pages aren't
 * available.  Otherwise, the number of bytes written to the queue is
 * वापसed.  Updates the tail poपूर्णांकer of the produce queue.
 */
अटल sमाप_प्रकार qp_enqueue_locked(काष्ठा vmci_queue *produce_q,
				 काष्ठा vmci_queue *consume_q,
				 स्थिर u64 produce_q_size,
				 काष्ठा iov_iter *from)
अणु
	s64 मुक्त_space;
	u64 tail;
	माप_प्रकार buf_size = iov_iter_count(from);
	माप_प्रकार written;
	sमाप_प्रकार result;

	result = qp_map_queue_headers(produce_q, consume_q);
	अगर (unlikely(result != VMCI_SUCCESS))
		वापस result;

	मुक्त_space = vmci_q_header_मुक्त_space(produce_q->q_header,
					      consume_q->q_header,
					      produce_q_size);
	अगर (मुक्त_space == 0)
		वापस VMCI_ERROR_QUEUEPAIR_NOSPACE;

	अगर (मुक्त_space < VMCI_SUCCESS)
		वापस (sमाप_प्रकार) मुक्त_space;

	written = (माप_प्रकार) (मुक्त_space > buf_size ? buf_size : मुक्त_space);
	tail = vmci_q_header_producer_tail(produce_q->q_header);
	अगर (likely(tail + written < produce_q_size)) अणु
		result = qp_स_नकल_to_queue_iter(produce_q, tail, from, written);
	पूर्ण अन्यथा अणु
		/* Tail poपूर्णांकer wraps around. */

		स्थिर माप_प्रकार पंचांगp = (माप_प्रकार) (produce_q_size - tail);

		result = qp_स_नकल_to_queue_iter(produce_q, tail, from, पंचांगp);
		अगर (result >= VMCI_SUCCESS)
			result = qp_स_नकल_to_queue_iter(produce_q, 0, from,
						 written - पंचांगp);
	पूर्ण

	अगर (result < VMCI_SUCCESS)
		वापस result;

	vmci_q_header_add_producer_tail(produce_q->q_header, written,
					produce_q_size);
	वापस written;
पूर्ण

/*
 * Dequeues data (अगर available) from the given consume queue. Writes data
 * to the user provided buffer using the provided function.
 * Assumes the queue->mutex has been acquired.
 * Results:
 * VMCI_ERROR_QUEUEPAIR_NODATA अगर no data was available to dequeue.
 * VMCI_ERROR_INVALID_SIZE, अगर any queue poपूर्णांकer is outside the queue
 * (as defined by the queue size).
 * VMCI_ERROR_INVALID_ARGS, अगर an error occured when accessing the buffer.
 * Otherwise the number of bytes dequeued is वापसed.
 * Side effects:
 * Updates the head poपूर्णांकer of the consume queue.
 */
अटल sमाप_प्रकार qp_dequeue_locked(काष्ठा vmci_queue *produce_q,
				 काष्ठा vmci_queue *consume_q,
				 स्थिर u64 consume_q_size,
				 काष्ठा iov_iter *to,
				 bool update_consumer)
अणु
	माप_प्रकार buf_size = iov_iter_count(to);
	s64 buf_पढ़ोy;
	u64 head;
	माप_प्रकार पढ़ो;
	sमाप_प्रकार result;

	result = qp_map_queue_headers(produce_q, consume_q);
	अगर (unlikely(result != VMCI_SUCCESS))
		वापस result;

	buf_पढ़ोy = vmci_q_header_buf_पढ़ोy(consume_q->q_header,
					    produce_q->q_header,
					    consume_q_size);
	अगर (buf_पढ़ोy == 0)
		वापस VMCI_ERROR_QUEUEPAIR_NODATA;

	अगर (buf_पढ़ोy < VMCI_SUCCESS)
		वापस (sमाप_प्रकार) buf_पढ़ोy;

	पढ़ो = (माप_प्रकार) (buf_पढ़ोy > buf_size ? buf_size : buf_पढ़ोy);
	head = vmci_q_header_consumer_head(produce_q->q_header);
	अगर (likely(head + पढ़ो < consume_q_size)) अणु
		result = qp_स_नकल_from_queue_iter(to, consume_q, head, पढ़ो);
	पूर्ण अन्यथा अणु
		/* Head poपूर्णांकer wraps around. */

		स्थिर माप_प्रकार पंचांगp = (माप_प्रकार) (consume_q_size - head);

		result = qp_स_नकल_from_queue_iter(to, consume_q, head, पंचांगp);
		अगर (result >= VMCI_SUCCESS)
			result = qp_स_नकल_from_queue_iter(to, consume_q, 0,
						   पढ़ो - पंचांगp);

	पूर्ण

	अगर (result < VMCI_SUCCESS)
		वापस result;

	अगर (update_consumer)
		vmci_q_header_add_consumer_head(produce_q->q_header,
						पढ़ो, consume_q_size);

	वापस पढ़ो;
पूर्ण

/*
 * vmci_qpair_alloc() - Allocates a queue pair.
 * @qpair:      Poपूर्णांकer क्रम the new vmci_qp काष्ठा.
 * @handle:     Handle to track the resource.
 * @produce_qsize:      Desired size of the producer queue.
 * @consume_qsize:      Desired size of the consumer queue.
 * @peer:       ContextID of the peer.
 * @flags:      VMCI flags.
 * @priv_flags: VMCI priviledge flags.
 *
 * This is the client पूर्णांकerface क्रम allocating the memory क्रम a
 * vmci_qp काष्ठाure and then attaching to the underlying
 * queue.  If an error occurs allocating the memory क्रम the
 * vmci_qp काष्ठाure no attempt is made to attach.  If an
 * error occurs attaching, then the काष्ठाure is मुक्तd.
 */
पूर्णांक vmci_qpair_alloc(काष्ठा vmci_qp **qpair,
		     काष्ठा vmci_handle *handle,
		     u64 produce_qsize,
		     u64 consume_qsize,
		     u32 peer,
		     u32 flags,
		     u32 priv_flags)
अणु
	काष्ठा vmci_qp *my_qpair;
	पूर्णांक retval;
	काष्ठा vmci_handle src = VMCI_INVALID_HANDLE;
	काष्ठा vmci_handle dst = vmci_make_handle(peer, VMCI_INVALID_ID);
	क्रमागत vmci_route route;
	vmci_event_release_cb wakeup_cb;
	व्योम *client_data;

	/*
	 * Restrict the size of a queuepair.  The device alपढ़ोy
	 * enक्रमces a limit on the total amount of memory that can be
	 * allocated to queuepairs क्रम a guest.  However, we try to
	 * allocate this memory beक्रमe we make the queuepair
	 * allocation hypercall.  On Linux, we allocate each page
	 * separately, which means rather than fail, the guest will
	 * thrash जबतक it tries to allocate, and will become
	 * increasingly unresponsive to the poपूर्णांक where it appears to
	 * be hung.  So we place a limit on the size of an inभागidual
	 * queuepair here, and leave the device to enक्रमce the
	 * restriction on total queuepair memory.  (Note that this
	 * करोesn't prevent all हालs; a user with only this much
	 * physical memory could still get पूर्णांकo trouble.)  The error
	 * used by the device is NO_RESOURCES, so use that here too.
	 */

	अगर (!QP_SIZES_ARE_VALID(produce_qsize, consume_qsize))
		वापस VMCI_ERROR_NO_RESOURCES;

	retval = vmci_route(&src, &dst, false, &route);
	अगर (retval < VMCI_SUCCESS)
		route = vmci_guest_code_active() ?
		    VMCI_ROUTE_AS_GUEST : VMCI_ROUTE_AS_HOST;

	अगर (flags & (VMCI_QPFLAG_NONBLOCK | VMCI_QPFLAG_PINNED)) अणु
		pr_devel("NONBLOCK OR PINNED set");
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	my_qpair = kzalloc(माप(*my_qpair), GFP_KERNEL);
	अगर (!my_qpair)
		वापस VMCI_ERROR_NO_MEM;

	my_qpair->produce_q_size = produce_qsize;
	my_qpair->consume_q_size = consume_qsize;
	my_qpair->peer = peer;
	my_qpair->flags = flags;
	my_qpair->priv_flags = priv_flags;

	wakeup_cb = शून्य;
	client_data = शून्य;

	अगर (VMCI_ROUTE_AS_HOST == route) अणु
		my_qpair->guest_endpoपूर्णांक = false;
		अगर (!(flags & VMCI_QPFLAG_LOCAL)) अणु
			my_qpair->blocked = 0;
			my_qpair->generation = 0;
			init_रुकोqueue_head(&my_qpair->event);
			wakeup_cb = qp_wakeup_cb;
			client_data = (व्योम *)my_qpair;
		पूर्ण
	पूर्ण अन्यथा अणु
		my_qpair->guest_endpoपूर्णांक = true;
	पूर्ण

	retval = vmci_qp_alloc(handle,
			       &my_qpair->produce_q,
			       my_qpair->produce_q_size,
			       &my_qpair->consume_q,
			       my_qpair->consume_q_size,
			       my_qpair->peer,
			       my_qpair->flags,
			       my_qpair->priv_flags,
			       my_qpair->guest_endpoपूर्णांक,
			       wakeup_cb, client_data);

	अगर (retval < VMCI_SUCCESS) अणु
		kमुक्त(my_qpair);
		वापस retval;
	पूर्ण

	*qpair = my_qpair;
	my_qpair->handle = *handle;

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_alloc);

/*
 * vmci_qpair_detach() - Detatches the client from a queue pair.
 * @qpair:      Reference of a poपूर्णांकer to the qpair काष्ठा.
 *
 * This is the client पूर्णांकerface क्रम detaching from a VMCIQPair.
 * Note that this routine will मुक्त the memory allocated क्रम the
 * vmci_qp काष्ठाure too.
 */
पूर्णांक vmci_qpair_detach(काष्ठा vmci_qp **qpair)
अणु
	पूर्णांक result;
	काष्ठा vmci_qp *old_qpair;

	अगर (!qpair || !(*qpair))
		वापस VMCI_ERROR_INVALID_ARGS;

	old_qpair = *qpair;
	result = qp_detatch(old_qpair->handle, old_qpair->guest_endpoपूर्णांक);

	/*
	 * The guest can fail to detach क्रम a number of reasons, and
	 * अगर it करोes so, it will cleanup the entry (अगर there is one).
	 * The host can fail too, but it won't cleanup the entry
	 * immediately, it will करो that later when the context is
	 * मुक्तd.  Either way, we need to release the qpair काष्ठा
	 * here; there isn't much the caller can do, and we don't want
	 * to leak.
	 */

	स_रखो(old_qpair, 0, माप(*old_qpair));
	old_qpair->handle = VMCI_INVALID_HANDLE;
	old_qpair->peer = VMCI_INVALID_ID;
	kमुक्त(old_qpair);
	*qpair = शून्य;

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_detach);

/*
 * vmci_qpair_get_produce_indexes() - Retrieves the indexes of the producer.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @producer_tail:      Reference used क्रम storing producer tail index.
 * @consumer_head:      Reference used क्रम storing the consumer head index.
 *
 * This is the client पूर्णांकerface क्रम getting the current indexes of the
 * QPair from the poपूर्णांक of the view of the caller as the producer.
 */
पूर्णांक vmci_qpair_get_produce_indexes(स्थिर काष्ठा vmci_qp *qpair,
				   u64 *producer_tail,
				   u64 *consumer_head)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	पूर्णांक result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		vmci_q_header_get_poपूर्णांकers(produce_q_header, consume_q_header,
					   producer_tail, consumer_head);
	qp_unlock(qpair);

	अगर (result == VMCI_SUCCESS &&
	    ((producer_tail && *producer_tail >= qpair->produce_q_size) ||
	     (consumer_head && *consumer_head >= qpair->produce_q_size)))
		वापस VMCI_ERROR_INVALID_SIZE;

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_get_produce_indexes);

/*
 * vmci_qpair_get_consume_indexes() - Retrieves the indexes of the consumer.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @consumer_tail:      Reference used क्रम storing consumer tail index.
 * @producer_head:      Reference used क्रम storing the producer head index.
 *
 * This is the client पूर्णांकerface क्रम getting the current indexes of the
 * QPair from the poपूर्णांक of the view of the caller as the consumer.
 */
पूर्णांक vmci_qpair_get_consume_indexes(स्थिर काष्ठा vmci_qp *qpair,
				   u64 *consumer_tail,
				   u64 *producer_head)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	पूर्णांक result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		vmci_q_header_get_poपूर्णांकers(consume_q_header, produce_q_header,
					   consumer_tail, producer_head);
	qp_unlock(qpair);

	अगर (result == VMCI_SUCCESS &&
	    ((consumer_tail && *consumer_tail >= qpair->consume_q_size) ||
	     (producer_head && *producer_head >= qpair->consume_q_size)))
		वापस VMCI_ERROR_INVALID_SIZE;

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_get_consume_indexes);

/*
 * vmci_qpair_produce_मुक्त_space() - Retrieves मुक्त space in producer queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 *
 * This is the client पूर्णांकerface क्रम getting the amount of मुक्त
 * space in the QPair from the poपूर्णांक of the view of the caller as
 * the producer which is the common हाल.  Returns < 0 अगर err, अन्यथा
 * available bytes पूर्णांकo which data can be enqueued अगर > 0.
 */
s64 vmci_qpair_produce_मुक्त_space(स्थिर काष्ठा vmci_qp *qpair)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	s64 result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		result = vmci_q_header_मुक्त_space(produce_q_header,
						  consume_q_header,
						  qpair->produce_q_size);
	अन्यथा
		result = 0;

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_produce_मुक्त_space);

/*
 * vmci_qpair_consume_मुक्त_space() - Retrieves मुक्त space in consumer queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 *
 * This is the client पूर्णांकerface क्रम getting the amount of मुक्त
 * space in the QPair from the poपूर्णांक of the view of the caller as
 * the consumer which is not the common हाल.  Returns < 0 अगर err, अन्यथा
 * available bytes पूर्णांकo which data can be enqueued अगर > 0.
 */
s64 vmci_qpair_consume_मुक्त_space(स्थिर काष्ठा vmci_qp *qpair)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	s64 result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		result = vmci_q_header_मुक्त_space(consume_q_header,
						  produce_q_header,
						  qpair->consume_q_size);
	अन्यथा
		result = 0;

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_consume_मुक्त_space);

/*
 * vmci_qpair_produce_buf_पढ़ोy() - Gets bytes पढ़ोy to पढ़ो from
 * producer queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 *
 * This is the client पूर्णांकerface क्रम getting the amount of
 * enqueued data in the QPair from the poपूर्णांक of the view of the
 * caller as the producer which is not the common हाल.  Returns < 0 अगर err,
 * अन्यथा available bytes that may be पढ़ो.
 */
s64 vmci_qpair_produce_buf_पढ़ोy(स्थिर काष्ठा vmci_qp *qpair)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	s64 result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		result = vmci_q_header_buf_पढ़ोy(produce_q_header,
						 consume_q_header,
						 qpair->produce_q_size);
	अन्यथा
		result = 0;

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_produce_buf_पढ़ोy);

/*
 * vmci_qpair_consume_buf_पढ़ोy() - Gets bytes पढ़ोy to पढ़ो from
 * consumer queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 *
 * This is the client पूर्णांकerface क्रम getting the amount of
 * enqueued data in the QPair from the poपूर्णांक of the view of the
 * caller as the consumer which is the normal हाल.  Returns < 0 अगर err,
 * अन्यथा available bytes that may be पढ़ो.
 */
s64 vmci_qpair_consume_buf_पढ़ोy(स्थिर काष्ठा vmci_qp *qpair)
अणु
	काष्ठा vmci_queue_header *produce_q_header;
	काष्ठा vmci_queue_header *consume_q_header;
	s64 result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	अगर (result == VMCI_SUCCESS)
		result = vmci_q_header_buf_पढ़ोy(consume_q_header,
						 produce_q_header,
						 qpair->consume_q_size);
	अन्यथा
		result = 0;

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_consume_buf_पढ़ोy);

/*
 * vmci_qpair_enqueue() - Throw data on the queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @buf:        Poपूर्णांकer to buffer containing data
 * @buf_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused).
 *
 * This is the client पूर्णांकerface क्रम enqueueing data पूर्णांकo the queue.
 * Returns number of bytes enqueued or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_enqueue(काष्ठा vmci_qp *qpair,
			   स्थिर व्योम *buf,
			   माप_प्रकार buf_size,
			   पूर्णांक buf_type)
अणु
	sमाप_प्रकार result;
	काष्ठा iov_iter from;
	काष्ठा kvec v = अणु.iov_base = (व्योम *)buf, .iov_len = buf_sizeपूर्ण;

	अगर (!qpair || !buf)
		वापस VMCI_ERROR_INVALID_ARGS;

	iov_iter_kvec(&from, WRITE, &v, 1, buf_size);

	qp_lock(qpair);

	करो अणु
		result = qp_enqueue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->produce_q_size,
					   &from);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_enqueue);

/*
 * vmci_qpair_dequeue() - Get data from the queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @buf:        Poपूर्णांकer to buffer क्रम the data
 * @buf_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused).
 *
 * This is the client पूर्णांकerface क्रम dequeueing data from the queue.
 * Returns number of bytes dequeued or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_dequeue(काष्ठा vmci_qp *qpair,
			   व्योम *buf,
			   माप_प्रकार buf_size,
			   पूर्णांक buf_type)
अणु
	sमाप_प्रकार result;
	काष्ठा iov_iter to;
	काष्ठा kvec v = अणु.iov_base = buf, .iov_len = buf_sizeपूर्ण;

	अगर (!qpair || !buf)
		वापस VMCI_ERROR_INVALID_ARGS;

	iov_iter_kvec(&to, READ, &v, 1, buf_size);

	qp_lock(qpair);

	करो अणु
		result = qp_dequeue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->consume_q_size,
					   &to, true);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_dequeue);

/*
 * vmci_qpair_peek() - Peek at the data in the queue.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @buf:        Poपूर्णांकer to buffer क्रम the data
 * @buf_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused on Linux).
 *
 * This is the client पूर्णांकerface क्रम peeking पूर्णांकo a queue.  (I.e.,
 * copy data from the queue without updating the head poपूर्णांकer.)
 * Returns number of bytes dequeued or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_peek(काष्ठा vmci_qp *qpair,
			व्योम *buf,
			माप_प्रकार buf_size,
			पूर्णांक buf_type)
अणु
	काष्ठा iov_iter to;
	काष्ठा kvec v = अणु.iov_base = buf, .iov_len = buf_sizeपूर्ण;
	sमाप_प्रकार result;

	अगर (!qpair || !buf)
		वापस VMCI_ERROR_INVALID_ARGS;

	iov_iter_kvec(&to, READ, &v, 1, buf_size);

	qp_lock(qpair);

	करो अणु
		result = qp_dequeue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->consume_q_size,
					   &to, false);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_peek);

/*
 * vmci_qpair_enquev() - Throw data on the queue using iov.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @iov:        Poपूर्णांकer to buffer containing data
 * @iov_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused).
 *
 * This is the client पूर्णांकerface क्रम enqueueing data पूर्णांकo the queue.
 * This function uses IO vectors to handle the work. Returns number
 * of bytes enqueued or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_enquev(काष्ठा vmci_qp *qpair,
			  काष्ठा msghdr *msg,
			  माप_प्रकार iov_size,
			  पूर्णांक buf_type)
अणु
	sमाप_प्रकार result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);

	करो अणु
		result = qp_enqueue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->produce_q_size,
					   &msg->msg_iter);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_enquev);

/*
 * vmci_qpair_dequev() - Get data from the queue using iov.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @iov:        Poपूर्णांकer to buffer क्रम the data
 * @iov_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused).
 *
 * This is the client पूर्णांकerface क्रम dequeueing data from the queue.
 * This function uses IO vectors to handle the work. Returns number
 * of bytes dequeued or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_dequev(काष्ठा vmci_qp *qpair,
			  काष्ठा msghdr *msg,
			  माप_प्रकार iov_size,
			  पूर्णांक buf_type)
अणु
	sमाप_प्रकार result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);

	करो अणु
		result = qp_dequeue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->consume_q_size,
					   &msg->msg_iter, true);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_dequev);

/*
 * vmci_qpair_peekv() - Peek at the data in the queue using iov.
 * @qpair:      Poपूर्णांकer to the queue pair काष्ठा.
 * @iov:        Poपूर्णांकer to buffer क्रम the data
 * @iov_size:   Length of buffer.
 * @buf_type:   Buffer type (Unused on Linux).
 *
 * This is the client पूर्णांकerface क्रम peeking पूर्णांकo a queue.  (I.e.,
 * copy data from the queue without updating the head poपूर्णांकer.)
 * This function uses IO vectors to handle the work. Returns number
 * of bytes peeked or < 0 on error.
 */
sमाप_प्रकार vmci_qpair_peekv(काष्ठा vmci_qp *qpair,
			 काष्ठा msghdr *msg,
			 माप_प्रकार iov_size,
			 पूर्णांक buf_type)
अणु
	sमाप_प्रकार result;

	अगर (!qpair)
		वापस VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);

	करो अणु
		result = qp_dequeue_locked(qpair->produce_q,
					   qpair->consume_q,
					   qpair->consume_q_size,
					   &msg->msg_iter, false);

		अगर (result == VMCI_ERROR_QUEUEPAIR_NOT_READY &&
		    !qp_रुको_क्रम_पढ़ोy_queue(qpair))
			result = VMCI_ERROR_WOULD_BLOCK;

	पूर्ण जबतक (result == VMCI_ERROR_QUEUEPAIR_NOT_READY);

	qp_unlock(qpair);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_qpair_peekv);
