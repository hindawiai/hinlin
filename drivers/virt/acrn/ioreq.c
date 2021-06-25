<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN_HSM: Handle I/O requests
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Jason Chen CJ <jason.cj.chen@पूर्णांकel.com>
 *	Fengwei Yin <fengwei.yin@पूर्णांकel.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/acrn.h>

#समावेश "acrn_drv.h"

अटल व्योम ioreq_छोड़ो(व्योम);
अटल व्योम ioreq_resume(व्योम);

अटल व्योम ioreq_dispatcher(काष्ठा work_काष्ठा *work);
अटल काष्ठा workqueue_काष्ठा *ioreq_wq;
अटल DECLARE_WORK(ioreq_work, ioreq_dispatcher);

अटल अंतरभूत bool has_pending_request(काष्ठा acrn_ioreq_client *client)
अणु
	वापस !biपंचांगap_empty(client->ioreqs_map, ACRN_IO_REQUEST_MAX);
पूर्ण

अटल अंतरभूत bool is_destroying(काष्ठा acrn_ioreq_client *client)
अणु
	वापस test_bit(ACRN_IOREQ_CLIENT_DESTROYING, &client->flags);
पूर्ण

अटल पूर्णांक ioreq_complete_request(काष्ठा acrn_vm *vm, u16 vcpu,
				  काष्ठा acrn_io_request *acrn_req)
अणु
	bool polling_mode;
	पूर्णांक ret = 0;

	polling_mode = acrn_req->completion_polling;
	/* Add barrier() to make sure the ग_लिखोs are करोne beक्रमe completion */
	smp_store_release(&acrn_req->processed, ACRN_IOREQ_STATE_COMPLETE);

	/*
	 * To fulfill the requirement of real-समय in several industry
	 * scenarios, like स्वतःmotive, ACRN can run under the partition mode,
	 * in which User VMs and Service VM are bound to dedicated CPU cores.
	 * Polling mode of handling the I/O request is पूर्णांकroduced to achieve a
	 * faster I/O request handling. In polling mode, the hypervisor polls
	 * I/O request's completion. Once an I/O request is marked as
	 * ACRN_IOREQ_STATE_COMPLETE, hypervisor resumes from the polling poपूर्णांक
	 * to जारी the I/O request flow. Thus, the completion notअगरication
	 * from HSM of I/O request is not needed.  Please note,
	 * completion_polling needs to be पढ़ो beक्रमe the I/O request being
	 * marked as ACRN_IOREQ_STATE_COMPLETE to aव्योम racing with the
	 * hypervisor.
	 */
	अगर (!polling_mode) अणु
		ret = hcall_notअगरy_req_finish(vm->vmid, vcpu);
		अगर (ret < 0)
			dev_err(acrn_dev.this_device,
				"Notify I/O request finished failed!\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक acrn_ioreq_complete_request(काष्ठा acrn_ioreq_client *client,
				       u16 vcpu,
				       काष्ठा acrn_io_request *acrn_req)
अणु
	पूर्णांक ret;

	अगर (vcpu >= client->vm->vcpu_num)
		वापस -EINVAL;

	clear_bit(vcpu, client->ioreqs_map);
	अगर (!acrn_req) अणु
		acrn_req = (काष्ठा acrn_io_request *)client->vm->ioreq_buf;
		acrn_req += vcpu;
	पूर्ण

	ret = ioreq_complete_request(client->vm, vcpu, acrn_req);

	वापस ret;
पूर्ण

पूर्णांक acrn_ioreq_request_शेष_complete(काष्ठा acrn_vm *vm, u16 vcpu)
अणु
	पूर्णांक ret = 0;

	spin_lock_bh(&vm->ioreq_clients_lock);
	अगर (vm->शेष_client)
		ret = acrn_ioreq_complete_request(vm->शेष_client,
						  vcpu, शून्य);
	spin_unlock_bh(&vm->ioreq_clients_lock);

	वापस ret;
पूर्ण

/**
 * acrn_ioreq_range_add() - Add an iorange monitored by an ioreq client
 * @client:	The ioreq client
 * @type:	Type (ACRN_IOREQ_TYPE_MMIO or ACRN_IOREQ_TYPE_PORTIO)
 * @start:	Start address of iorange
 * @end:	End address of iorange
 *
 * Return: 0 on success, <0 on error
 */
पूर्णांक acrn_ioreq_range_add(काष्ठा acrn_ioreq_client *client,
			 u32 type, u64 start, u64 end)
अणु
	काष्ठा acrn_ioreq_range *range;

	अगर (end < start) अणु
		dev_err(acrn_dev.this_device,
			"Invalid IO range [0x%llx,0x%llx]\n", start, end);
		वापस -EINVAL;
	पूर्ण

	range = kzalloc(माप(*range), GFP_KERNEL);
	अगर (!range)
		वापस -ENOMEM;

	range->type = type;
	range->start = start;
	range->end = end;

	ग_लिखो_lock_bh(&client->range_lock);
	list_add(&range->list, &client->range_list);
	ग_लिखो_unlock_bh(&client->range_lock);

	वापस 0;
पूर्ण

/**
 * acrn_ioreq_range_del() - Del an iorange monitored by an ioreq client
 * @client:	The ioreq client
 * @type:	Type (ACRN_IOREQ_TYPE_MMIO or ACRN_IOREQ_TYPE_PORTIO)
 * @start:	Start address of iorange
 * @end:	End address of iorange
 */
व्योम acrn_ioreq_range_del(काष्ठा acrn_ioreq_client *client,
			  u32 type, u64 start, u64 end)
अणु
	काष्ठा acrn_ioreq_range *range;

	ग_लिखो_lock_bh(&client->range_lock);
	list_क्रम_each_entry(range, &client->range_list, list) अणु
		अगर (type == range->type &&
		    start == range->start &&
		    end == range->end) अणु
			list_del(&range->list);
			kमुक्त(range);
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&client->range_lock);
पूर्ण

/*
 * ioreq_task() is the execution entity of handler thपढ़ो of an I/O client.
 * The handler callback of the I/O client is called within the handler thपढ़ो.
 */
अटल पूर्णांक ioreq_task(व्योम *data)
अणु
	काष्ठा acrn_ioreq_client *client = data;
	काष्ठा acrn_io_request *req;
	अचिन्हित दीर्घ *ioreqs_map;
	पूर्णांक vcpu, ret;

	/*
	 * Lockless access to ioreqs_map is safe, because
	 * 1) set_bit() and clear_bit() are atomic operations.
	 * 2) I/O requests arrives serialized. The access flow of ioreqs_map is:
	 *	set_bit() - in ioreq_work handler
	 *	Handler callback handles corresponding I/O request
	 *	clear_bit() - in handler thपढ़ो (include ACRN userspace)
	 *	Mark corresponding I/O request completed
	 *	Loop again अगर a new I/O request occurs
	 */
	ioreqs_map = client->ioreqs_map;
	जबतक (!kthपढ़ो_should_stop()) अणु
		acrn_ioreq_client_रुको(client);
		जबतक (has_pending_request(client)) अणु
			vcpu = find_first_bit(ioreqs_map, client->vm->vcpu_num);
			req = client->vm->ioreq_buf->req_slot + vcpu;
			ret = client->handler(client, req);
			अगर (ret < 0) अणु
				dev_err(acrn_dev.this_device,
					"IO handle failure: %d\n", ret);
				अवरोध;
			पूर्ण
			acrn_ioreq_complete_request(client, vcpu, req);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For the non-शेष I/O clients, give them chance to complete the current
 * I/O requests अगर there are any. For the शेष I/O client, it is safe to
 * clear all pending I/O requests because the clearing request is from ACRN
 * userspace.
 */
व्योम acrn_ioreq_request_clear(काष्ठा acrn_vm *vm)
अणु
	काष्ठा acrn_ioreq_client *client;
	bool has_pending = false;
	अचिन्हित दीर्घ vcpu;
	पूर्णांक retry = 10;

	/*
	 * IO requests of this VM will be completed directly in
	 * acrn_ioreq_dispatch अगर ACRN_VM_FLAG_CLEARING_IOREQ flag is set.
	 */
	set_bit(ACRN_VM_FLAG_CLEARING_IOREQ, &vm->flags);

	/*
	 * acrn_ioreq_request_clear is only called in VM reset हाल. Simply
	 * रुको 100ms in total क्रम the IO requests' completion.
	 */
	करो अणु
		spin_lock_bh(&vm->ioreq_clients_lock);
		list_क्रम_each_entry(client, &vm->ioreq_clients, list) अणु
			has_pending = has_pending_request(client);
			अगर (has_pending)
				अवरोध;
		पूर्ण
		spin_unlock_bh(&vm->ioreq_clients_lock);

		अगर (has_pending)
			schedule_समयout_पूर्णांकerruptible(HZ / 100);
	पूर्ण जबतक (has_pending && --retry > 0);
	अगर (retry == 0)
		dev_warn(acrn_dev.this_device,
			 "%s cannot flush pending request!\n", client->name);

	/* Clear all ioreqs beदीर्घing to the शेष client */
	spin_lock_bh(&vm->ioreq_clients_lock);
	client = vm->शेष_client;
	अगर (client) अणु
		vcpu = find_next_bit(client->ioreqs_map,
				     ACRN_IO_REQUEST_MAX, 0);
		जबतक (vcpu < ACRN_IO_REQUEST_MAX) अणु
			acrn_ioreq_complete_request(client, vcpu, शून्य);
			vcpu = find_next_bit(client->ioreqs_map,
					     ACRN_IO_REQUEST_MAX, vcpu + 1);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&vm->ioreq_clients_lock);

	/* Clear ACRN_VM_FLAG_CLEARING_IOREQ flag after the clearing */
	clear_bit(ACRN_VM_FLAG_CLEARING_IOREQ, &vm->flags);
पूर्ण

पूर्णांक acrn_ioreq_client_रुको(काष्ठा acrn_ioreq_client *client)
अणु
	अगर (client->is_शेष) अणु
		/*
		 * In the शेष client, a user space thपढ़ो रुकोs on the
		 * रुकोqueue. The is_destroying() check is used to notअगरy user
		 * space the client is going to be destroyed.
		 */
		रुको_event_पूर्णांकerruptible(client->wq,
					 has_pending_request(client) ||
					 is_destroying(client));
		अगर (is_destroying(client))
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		रुको_event_पूर्णांकerruptible(client->wq,
					 has_pending_request(client) ||
					 kthपढ़ो_should_stop());
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_cfg_addr(काष्ठा acrn_io_request *req)
अणु
	वापस ((req->type == ACRN_IOREQ_TYPE_PORTIO) &&
		(req->reqs.pio_request.address == 0xcf8));
पूर्ण

अटल bool is_cfg_data(काष्ठा acrn_io_request *req)
अणु
	वापस ((req->type == ACRN_IOREQ_TYPE_PORTIO) &&
		((req->reqs.pio_request.address >= 0xcfc) &&
		 (req->reqs.pio_request.address < (0xcfc + 4))));
पूर्ण

/* The low 8-bit of supported pci_reg addr.*/
#घोषणा PCI_LOWREG_MASK  0xFC
/* The high 4-bit of supported pci_reg addr */
#घोषणा PCI_HIGHREG_MASK 0xF00
/* Max number of supported functions */
#घोषणा PCI_FUNCMAX	7
/* Max number of supported slots */
#घोषणा PCI_SLOTMAX	31
/* Max number of supported buses */
#घोषणा PCI_BUSMAX	255
#घोषणा CONF1_ENABLE	0x80000000UL
/*
 * A PCI configuration space access via PIO 0xCF8 and 0xCFC normally has two
 * following steps:
 *   1) ग_लिखोs address पूर्णांकo 0xCF8 port
 *   2) accesses data in/from 0xCFC
 * This function combines such paired PCI configuration space I/O requests पूर्णांकo
 * one ACRN_IOREQ_TYPE_PCICFG type I/O request and जारीs the processing.
 */
अटल bool handle_cf8cfc(काष्ठा acrn_vm *vm,
			  काष्ठा acrn_io_request *req, u16 vcpu)
अणु
	पूर्णांक offset, pci_cfg_addr, pci_reg;
	bool is_handled = false;

	अगर (is_cfg_addr(req)) अणु
		WARN_ON(req->reqs.pio_request.size != 4);
		अगर (req->reqs.pio_request.direction == ACRN_IOREQ_सूची_WRITE)
			vm->pci_conf_addr = req->reqs.pio_request.value;
		अन्यथा
			req->reqs.pio_request.value = vm->pci_conf_addr;
		is_handled = true;
	पूर्ण अन्यथा अगर (is_cfg_data(req)) अणु
		अगर (!(vm->pci_conf_addr & CONF1_ENABLE)) अणु
			अगर (req->reqs.pio_request.direction ==
					ACRN_IOREQ_सूची_READ)
				req->reqs.pio_request.value = 0xffffffff;
			is_handled = true;
		पूर्ण अन्यथा अणु
			offset = req->reqs.pio_request.address - 0xcfc;

			req->type = ACRN_IOREQ_TYPE_PCICFG;
			pci_cfg_addr = vm->pci_conf_addr;
			req->reqs.pci_request.bus =
					(pci_cfg_addr >> 16) & PCI_BUSMAX;
			req->reqs.pci_request.dev =
					(pci_cfg_addr >> 11) & PCI_SLOTMAX;
			req->reqs.pci_request.func =
					(pci_cfg_addr >> 8) & PCI_FUNCMAX;
			pci_reg = (pci_cfg_addr & PCI_LOWREG_MASK) +
				   ((pci_cfg_addr >> 16) & PCI_HIGHREG_MASK);
			req->reqs.pci_request.reg = pci_reg + offset;
		पूर्ण
	पूर्ण

	अगर (is_handled)
		ioreq_complete_request(vm, vcpu, req);

	वापस is_handled;
पूर्ण

अटल bool in_range(काष्ठा acrn_ioreq_range *range,
		     काष्ठा acrn_io_request *req)
अणु
	bool ret = false;

	अगर (range->type == req->type) अणु
		चयन (req->type) अणु
		हाल ACRN_IOREQ_TYPE_MMIO:
			अगर (req->reqs.mmio_request.address >= range->start &&
			    (req->reqs.mmio_request.address +
			     req->reqs.mmio_request.size - 1) <= range->end)
				ret = true;
			अवरोध;
		हाल ACRN_IOREQ_TYPE_PORTIO:
			अगर (req->reqs.pio_request.address >= range->start &&
			    (req->reqs.pio_request.address +
			     req->reqs.pio_request.size - 1) <= range->end)
				ret = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा acrn_ioreq_client *find_ioreq_client(काष्ठा acrn_vm *vm,
						   काष्ठा acrn_io_request *req)
अणु
	काष्ठा acrn_ioreq_client *client, *found = शून्य;
	काष्ठा acrn_ioreq_range *range;

	lockdep_निश्चित_held(&vm->ioreq_clients_lock);

	list_क्रम_each_entry(client, &vm->ioreq_clients, list) अणु
		पढ़ो_lock_bh(&client->range_lock);
		list_क्रम_each_entry(range, &client->range_list, list) अणु
			अगर (in_range(range, req)) अणु
				found = client;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock_bh(&client->range_lock);
		अगर (found)
			अवरोध;
	पूर्ण
	वापस found ? found : vm->शेष_client;
पूर्ण

/**
 * acrn_ioreq_client_create() - Create an ioreq client
 * @vm:		The VM that this client beदीर्घs to
 * @handler:	The ioreq_handler of ioreq client acrn_hsm will create a kernel
 *		thपढ़ो and call the handler to handle I/O requests.
 * @priv:	Private data क्रम the handler
 * @is_शेष:	If it is the शेष client
 * @name:	The name of ioreq client
 *
 * Return: acrn_ioreq_client poपूर्णांकer on success, शून्य on error
 */
काष्ठा acrn_ioreq_client *acrn_ioreq_client_create(काष्ठा acrn_vm *vm,
						   ioreq_handler_t handler,
						   व्योम *priv, bool is_शेष,
						   स्थिर अक्षर *name)
अणु
	काष्ठा acrn_ioreq_client *client;

	अगर (!handler && !is_शेष) अणु
		dev_dbg(acrn_dev.this_device,
			"Cannot create non-default client w/o handler!\n");
		वापस शून्य;
	पूर्ण
	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस शून्य;

	client->handler = handler;
	client->vm = vm;
	client->priv = priv;
	client->is_शेष = is_शेष;
	अगर (name)
		म_नकलन(client->name, name, माप(client->name) - 1);
	rwlock_init(&client->range_lock);
	INIT_LIST_HEAD(&client->range_list);
	init_रुकोqueue_head(&client->wq);

	अगर (client->handler) अणु
		client->thपढ़ो = kthपढ़ो_run(ioreq_task, client, "VM%u-%s",
					     client->vm->vmid, client->name);
		अगर (IS_ERR(client->thपढ़ो)) अणु
			kमुक्त(client);
			वापस शून्य;
		पूर्ण
	पूर्ण

	spin_lock_bh(&vm->ioreq_clients_lock);
	अगर (is_शेष)
		vm->शेष_client = client;
	अन्यथा
		list_add(&client->list, &vm->ioreq_clients);
	spin_unlock_bh(&vm->ioreq_clients_lock);

	dev_dbg(acrn_dev.this_device, "Created ioreq client %s.\n", name);
	वापस client;
पूर्ण

/**
 * acrn_ioreq_client_destroy() - Destroy an ioreq client
 * @client:	The ioreq client
 */
व्योम acrn_ioreq_client_destroy(काष्ठा acrn_ioreq_client *client)
अणु
	काष्ठा acrn_ioreq_range *range, *next;
	काष्ठा acrn_vm *vm = client->vm;

	dev_dbg(acrn_dev.this_device,
		"Destroy ioreq client %s.\n", client->name);
	ioreq_छोड़ो();
	set_bit(ACRN_IOREQ_CLIENT_DESTROYING, &client->flags);
	अगर (client->is_शेष)
		wake_up_पूर्णांकerruptible(&client->wq);
	अन्यथा
		kthपढ़ो_stop(client->thपढ़ो);

	spin_lock_bh(&vm->ioreq_clients_lock);
	अगर (client->is_शेष)
		vm->शेष_client = शून्य;
	अन्यथा
		list_del(&client->list);
	spin_unlock_bh(&vm->ioreq_clients_lock);

	ग_लिखो_lock_bh(&client->range_lock);
	list_क्रम_each_entry_safe(range, next, &client->range_list, list) अणु
		list_del(&range->list);
		kमुक्त(range);
	पूर्ण
	ग_लिखो_unlock_bh(&client->range_lock);
	kमुक्त(client);

	ioreq_resume();
पूर्ण

अटल पूर्णांक acrn_ioreq_dispatch(काष्ठा acrn_vm *vm)
अणु
	काष्ठा acrn_ioreq_client *client;
	काष्ठा acrn_io_request *req;
	पूर्णांक i;

	क्रम (i = 0; i < vm->vcpu_num; i++) अणु
		req = vm->ioreq_buf->req_slot + i;

		/* barrier the पढ़ो of processed of acrn_io_request */
		अगर (smp_load_acquire(&req->processed) ==
				     ACRN_IOREQ_STATE_PENDING) अणु
			/* Complete the IO request directly in clearing stage */
			अगर (test_bit(ACRN_VM_FLAG_CLEARING_IOREQ, &vm->flags)) अणु
				ioreq_complete_request(vm, i, req);
				जारी;
			पूर्ण
			अगर (handle_cf8cfc(vm, req, i))
				जारी;

			spin_lock_bh(&vm->ioreq_clients_lock);
			client = find_ioreq_client(vm, req);
			अगर (!client) अणु
				dev_err(acrn_dev.this_device,
					"Failed to find ioreq client!\n");
				spin_unlock_bh(&vm->ioreq_clients_lock);
				वापस -EINVAL;
			पूर्ण
			अगर (!client->is_शेष)
				req->kernel_handled = 1;
			अन्यथा
				req->kernel_handled = 0;
			/*
			 * Add barrier() to make sure the ग_लिखोs are करोne
			 * beक्रमe setting ACRN_IOREQ_STATE_PROCESSING
			 */
			smp_store_release(&req->processed,
					  ACRN_IOREQ_STATE_PROCESSING);
			set_bit(i, client->ioreqs_map);
			wake_up_पूर्णांकerruptible(&client->wq);
			spin_unlock_bh(&vm->ioreq_clients_lock);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ioreq_dispatcher(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acrn_vm *vm;

	पढ़ो_lock(&acrn_vm_list_lock);
	list_क्रम_each_entry(vm, &acrn_vm_list, list) अणु
		अगर (!vm->ioreq_buf)
			अवरोध;
		acrn_ioreq_dispatch(vm);
	पूर्ण
	पढ़ो_unlock(&acrn_vm_list_lock);
पूर्ण

अटल व्योम ioreq_पूर्णांकr_handler(व्योम)
अणु
	queue_work(ioreq_wq, &ioreq_work);
पूर्ण

अटल व्योम ioreq_छोड़ो(व्योम)
अणु
	/* Flush and unarm the handler to ensure no I/O requests pending */
	acrn_हटाओ_पूर्णांकr_handler();
	drain_workqueue(ioreq_wq);
पूर्ण

अटल व्योम ioreq_resume(व्योम)
अणु
	/* Schedule after enabling in हाल other clients miss पूर्णांकerrupt */
	acrn_setup_पूर्णांकr_handler(ioreq_पूर्णांकr_handler);
	queue_work(ioreq_wq, &ioreq_work);
पूर्ण

पूर्णांक acrn_ioreq_पूर्णांकr_setup(व्योम)
अणु
	acrn_setup_पूर्णांकr_handler(ioreq_पूर्णांकr_handler);
	ioreq_wq = alloc_workqueue("ioreq_wq",
				   WQ_HIGHPRI | WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!ioreq_wq) अणु
		dev_err(acrn_dev.this_device, "Failed to alloc workqueue!\n");
		acrn_हटाओ_पूर्णांकr_handler();
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम acrn_ioreq_पूर्णांकr_हटाओ(व्योम)
अणु
	अगर (ioreq_wq)
		destroy_workqueue(ioreq_wq);
	acrn_हटाओ_पूर्णांकr_handler();
पूर्ण

पूर्णांक acrn_ioreq_init(काष्ठा acrn_vm *vm, u64 buf_vma)
अणु
	काष्ठा acrn_ioreq_buffer *set_buffer;
	काष्ठा page *page;
	पूर्णांक ret;

	अगर (vm->ioreq_buf)
		वापस -EEXIST;

	set_buffer = kzalloc(माप(*set_buffer), GFP_KERNEL);
	अगर (!set_buffer)
		वापस -ENOMEM;

	ret = pin_user_pages_fast(buf_vma, 1,
				  FOLL_WRITE | FOLL_LONGTERM, &page);
	अगर (unlikely(ret != 1) || !page) अणु
		dev_err(acrn_dev.this_device, "Failed to pin ioreq page!\n");
		ret = -EFAULT;
		जाओ मुक्त_buf;
	पूर्ण

	vm->ioreq_buf = page_address(page);
	vm->ioreq_page = page;
	set_buffer->ioreq_buf = page_to_phys(page);
	ret = hcall_set_ioreq_buffer(vm->vmid, virt_to_phys(set_buffer));
	अगर (ret < 0) अणु
		dev_err(acrn_dev.this_device, "Failed to init ioreq buffer!\n");
		unpin_user_page(page);
		vm->ioreq_buf = शून्य;
		जाओ मुक्त_buf;
	पूर्ण

	dev_dbg(acrn_dev.this_device,
		"Init ioreq buffer %pK!\n", vm->ioreq_buf);
	ret = 0;
मुक्त_buf:
	kमुक्त(set_buffer);
	वापस ret;
पूर्ण

व्योम acrn_ioreq_deinit(काष्ठा acrn_vm *vm)
अणु
	काष्ठा acrn_ioreq_client *client, *next;

	dev_dbg(acrn_dev.this_device,
		"Deinit ioreq buffer %pK!\n", vm->ioreq_buf);
	/* Destroy all clients beदीर्घing to this VM */
	list_क्रम_each_entry_safe(client, next, &vm->ioreq_clients, list)
		acrn_ioreq_client_destroy(client);
	अगर (vm->शेष_client)
		acrn_ioreq_client_destroy(vm->शेष_client);

	अगर (vm->ioreq_buf && vm->ioreq_page) अणु
		unpin_user_page(vm->ioreq_page);
		vm->ioreq_buf = शून्य;
	पूर्ण
पूर्ण
