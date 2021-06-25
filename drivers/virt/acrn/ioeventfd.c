<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN HSM eventfd - use eventfd objects to संकेत expected I/O requests
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 *
 * Authors:
 *	Shuo Liu <shuo.a.liu@पूर्णांकel.com>
 *	Yakui Zhao <yakui.zhao@पूर्णांकel.com>
 */

#समावेश <linux/eventfd.h>
#समावेश <linux/slab.h>

#समावेश "acrn_drv.h"

/**
 * काष्ठा hsm_ioeventfd - Properties of HSM ioeventfd
 * @list:	Entry within &acrn_vm.ioeventfds of ioeventfds of a VM
 * @eventfd:	Eventfd of the HSM ioeventfd
 * @addr:	Address of I/O range
 * @data:	Data क्रम matching
 * @length:	Length of I/O range
 * @type:	Type of I/O range (ACRN_IOREQ_TYPE_MMIO/ACRN_IOREQ_TYPE_PORTIO)
 * @wildcard:	Data matching or not
 */
काष्ठा hsm_ioeventfd अणु
	काष्ठा list_head	list;
	काष्ठा eventfd_ctx	*eventfd;
	u64			addr;
	u64			data;
	पूर्णांक			length;
	पूर्णांक			type;
	bool			wildcard;
पूर्ण;

अटल अंतरभूत पूर्णांक ioreq_type_from_flags(पूर्णांक flags)
अणु
	वापस flags & ACRN_IOEVENTFD_FLAG_PIO ?
		       ACRN_IOREQ_TYPE_PORTIO : ACRN_IOREQ_TYPE_MMIO;
पूर्ण

अटल व्योम acrn_ioeventfd_shutकरोwn(काष्ठा acrn_vm *vm, काष्ठा hsm_ioeventfd *p)
अणु
	lockdep_निश्चित_held(&vm->ioeventfds_lock);

	eventfd_ctx_put(p->eventfd);
	list_del(&p->list);
	kमुक्त(p);
पूर्ण

अटल bool hsm_ioeventfd_is_conflict(काष्ठा acrn_vm *vm,
				      काष्ठा hsm_ioeventfd *ioeventfd)
अणु
	काष्ठा hsm_ioeventfd *p;

	lockdep_निश्चित_held(&vm->ioeventfds_lock);

	/* Either one is wildcard, the data matching will be skipped. */
	list_क्रम_each_entry(p, &vm->ioeventfds, list)
		अगर (p->eventfd == ioeventfd->eventfd &&
		    p->addr == ioeventfd->addr &&
		    p->type == ioeventfd->type &&
		    (p->wildcard || ioeventfd->wildcard ||
			p->data == ioeventfd->data))
			वापस true;

	वापस false;
पूर्ण

/*
 * Assign an eventfd to a VM and create a HSM ioeventfd associated with the
 * eventfd. The properties of the HSM ioeventfd are built from a &काष्ठा
 * acrn_ioeventfd.
 */
अटल पूर्णांक acrn_ioeventfd_assign(काष्ठा acrn_vm *vm,
				 काष्ठा acrn_ioeventfd *args)
अणु
	काष्ठा eventfd_ctx *eventfd;
	काष्ठा hsm_ioeventfd *p;
	पूर्णांक ret;

	/* Check क्रम range overflow */
	अगर (args->addr + args->len < args->addr)
		वापस -EINVAL;

	/*
	 * Currently, acrn_ioeventfd is used to support vhost. 1,2,4,8 width
	 * accesses can cover vhost's requirements.
	 */
	अगर (!(args->len == 1 || args->len == 2 ||
	      args->len == 4 || args->len == 8))
		वापस -EINVAL;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	INIT_LIST_HEAD(&p->list);
	p->addr = args->addr;
	p->length = args->len;
	p->eventfd = eventfd;
	p->type = ioreq_type_from_flags(args->flags);

	/*
	 * ACRN_IOEVENTFD_FLAG_DATAMATCH flag is set in virtio 1.0 support, the
	 * writing of notअगरication रेजिस्टर of each virtqueue may trigger the
	 * notअगरication. There is no data matching requirement.
	 */
	अगर (args->flags & ACRN_IOEVENTFD_FLAG_DATAMATCH)
		p->data = args->data;
	अन्यथा
		p->wildcard = true;

	mutex_lock(&vm->ioeventfds_lock);

	अगर (hsm_ioeventfd_is_conflict(vm, p)) अणु
		ret = -EEXIST;
		जाओ unlock_fail;
	पूर्ण

	/* रेजिस्टर the I/O range पूर्णांकo ioreq client */
	ret = acrn_ioreq_range_add(vm->ioeventfd_client, p->type,
				   p->addr, p->addr + p->length - 1);
	अगर (ret < 0)
		जाओ unlock_fail;

	list_add_tail(&p->list, &vm->ioeventfds);
	mutex_unlock(&vm->ioeventfds_lock);

	वापस 0;

unlock_fail:
	mutex_unlock(&vm->ioeventfds_lock);
	kमुक्त(p);
fail:
	eventfd_ctx_put(eventfd);
	वापस ret;
पूर्ण

अटल पूर्णांक acrn_ioeventfd_deassign(काष्ठा acrn_vm *vm,
				   काष्ठा acrn_ioeventfd *args)
अणु
	काष्ठा hsm_ioeventfd *p;
	काष्ठा eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(args->fd);
	अगर (IS_ERR(eventfd))
		वापस PTR_ERR(eventfd);

	mutex_lock(&vm->ioeventfds_lock);
	list_क्रम_each_entry(p, &vm->ioeventfds, list) अणु
		अगर (p->eventfd != eventfd)
			जारी;

		acrn_ioreq_range_del(vm->ioeventfd_client, p->type,
				     p->addr, p->addr + p->length - 1);
		acrn_ioeventfd_shutकरोwn(vm, p);
		अवरोध;
	पूर्ण
	mutex_unlock(&vm->ioeventfds_lock);

	eventfd_ctx_put(eventfd);
	वापस 0;
पूर्ण

अटल काष्ठा hsm_ioeventfd *hsm_ioeventfd_match(काष्ठा acrn_vm *vm, u64 addr,
						 u64 data, पूर्णांक len, पूर्णांक type)
अणु
	काष्ठा hsm_ioeventfd *p = शून्य;

	lockdep_निश्चित_held(&vm->ioeventfds_lock);

	list_क्रम_each_entry(p, &vm->ioeventfds, list) अणु
		अगर (p->type == type && p->addr == addr && p->length >= len &&
		    (p->wildcard || p->data == data))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक acrn_ioeventfd_handler(काष्ठा acrn_ioreq_client *client,
				  काष्ठा acrn_io_request *req)
अणु
	काष्ठा hsm_ioeventfd *p;
	u64 addr, val;
	पूर्णांक size;

	अगर (req->type == ACRN_IOREQ_TYPE_MMIO) अणु
		/*
		 * I/O requests are dispatched by range check only, so a
		 * acrn_ioreq_client need process both READ and WRITE accesses
		 * of same range. READ accesses are safe to be ignored here
		 * because virtio PCI devices ग_लिखो the notअगरy रेजिस्टरs क्रम
		 * notअगरication.
		 */
		अगर (req->reqs.mmio_request.direction == ACRN_IOREQ_सूची_READ) अणु
			/* पढ़ोing करोes nothing and वापस 0 */
			req->reqs.mmio_request.value = 0;
			वापस 0;
		पूर्ण
		addr = req->reqs.mmio_request.address;
		size = req->reqs.mmio_request.size;
		val = req->reqs.mmio_request.value;
	पूर्ण अन्यथा अणु
		अगर (req->reqs.pio_request.direction == ACRN_IOREQ_सूची_READ) अणु
			/* पढ़ोing करोes nothing and वापस 0 */
			req->reqs.pio_request.value = 0;
			वापस 0;
		पूर्ण
		addr = req->reqs.pio_request.address;
		size = req->reqs.pio_request.size;
		val = req->reqs.pio_request.value;
	पूर्ण

	mutex_lock(&client->vm->ioeventfds_lock);
	p = hsm_ioeventfd_match(client->vm, addr, val, size, req->type);
	अगर (p)
		eventfd_संकेत(p->eventfd, 1);
	mutex_unlock(&client->vm->ioeventfds_lock);

	वापस 0;
पूर्ण

पूर्णांक acrn_ioeventfd_config(काष्ठा acrn_vm *vm, काष्ठा acrn_ioeventfd *args)
अणु
	पूर्णांक ret;

	अगर (args->flags & ACRN_IOEVENTFD_FLAG_DEASSIGN)
		ret = acrn_ioeventfd_deassign(vm, args);
	अन्यथा
		ret = acrn_ioeventfd_assign(vm, args);

	वापस ret;
पूर्ण

पूर्णांक acrn_ioeventfd_init(काष्ठा acrn_vm *vm)
अणु
	अक्षर name[ACRN_NAME_LEN];

	mutex_init(&vm->ioeventfds_lock);
	INIT_LIST_HEAD(&vm->ioeventfds);
	snम_लिखो(name, माप(name), "ioeventfd-%u", vm->vmid);
	vm->ioeventfd_client = acrn_ioreq_client_create(vm,
							acrn_ioeventfd_handler,
							शून्य, false, name);
	अगर (!vm->ioeventfd_client) अणु
		dev_err(acrn_dev.this_device, "Failed to create ioeventfd ioreq client!\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(acrn_dev.this_device, "VM %u ioeventfd init.\n", vm->vmid);
	वापस 0;
पूर्ण

व्योम acrn_ioeventfd_deinit(काष्ठा acrn_vm *vm)
अणु
	काष्ठा hsm_ioeventfd *p, *next;

	dev_dbg(acrn_dev.this_device, "VM %u ioeventfd deinit.\n", vm->vmid);
	acrn_ioreq_client_destroy(vm->ioeventfd_client);
	mutex_lock(&vm->ioeventfds_lock);
	list_क्रम_each_entry_safe(p, next, &vm->ioeventfds, list)
		acrn_ioeventfd_shutकरोwn(vm, p);
	mutex_unlock(&vm->ioeventfds_lock);
पूर्ण
