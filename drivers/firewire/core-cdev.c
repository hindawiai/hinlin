<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Char device क्रम device raw access
 *
 * Copyright (C) 2005-2007  Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bug.h>
#समावेश <linux/compat.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h> /* required क्रम linux/रुको.h */
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>


#समावेश "core.h"

/*
 * ABI version history is करोcumented in linux/firewire-cdev.h.
 */
#घोषणा FW_CDEV_KERNEL_VERSION			5
#घोषणा FW_CDEV_VERSION_EVENT_REQUEST2		4
#घोषणा FW_CDEV_VERSION_ALLOCATE_REGION_END	4
#घोषणा FW_CDEV_VERSION_AUTO_FLUSH_ISO_OVERFLOW	5

काष्ठा client अणु
	u32 version;
	काष्ठा fw_device *device;

	spinlock_t lock;
	bool in_shutकरोwn;
	काष्ठा idr resource_idr;
	काष्ठा list_head event_list;
	रुको_queue_head_t रुको;
	रुको_queue_head_t tx_flush_रुको;
	u64 bus_reset_closure;

	काष्ठा fw_iso_context *iso_context;
	u64 iso_closure;
	काष्ठा fw_iso_buffer buffer;
	अचिन्हित दीर्घ vm_start;
	bool buffer_is_mapped;

	काष्ठा list_head phy_receiver_link;
	u64 phy_receiver_closure;

	काष्ठा list_head link;
	काष्ठा kref kref;
पूर्ण;

अटल अंतरभूत व्योम client_get(काष्ठा client *client)
अणु
	kref_get(&client->kref);
पूर्ण

अटल व्योम client_release(काष्ठा kref *kref)
अणु
	काष्ठा client *client = container_of(kref, काष्ठा client, kref);

	fw_device_put(client->device);
	kमुक्त(client);
पूर्ण

अटल व्योम client_put(काष्ठा client *client)
अणु
	kref_put(&client->kref, client_release);
पूर्ण

काष्ठा client_resource;
प्रकार व्योम (*client_resource_release_fn_t)(काष्ठा client *,
					     काष्ठा client_resource *);
काष्ठा client_resource अणु
	client_resource_release_fn_t release;
	पूर्णांक handle;
पूर्ण;

काष्ठा address_handler_resource अणु
	काष्ठा client_resource resource;
	काष्ठा fw_address_handler handler;
	__u64 closure;
	काष्ठा client *client;
पूर्ण;

काष्ठा outbound_transaction_resource अणु
	काष्ठा client_resource resource;
	काष्ठा fw_transaction transaction;
पूर्ण;

काष्ठा inbound_transaction_resource अणु
	काष्ठा client_resource resource;
	काष्ठा fw_card *card;
	काष्ठा fw_request *request;
	व्योम *data;
	माप_प्रकार length;
पूर्ण;

काष्ठा descriptor_resource अणु
	काष्ठा client_resource resource;
	काष्ठा fw_descriptor descriptor;
	u32 data[];
पूर्ण;

काष्ठा iso_resource अणु
	काष्ठा client_resource resource;
	काष्ठा client *client;
	/* Schedule work and access toकरो only with client->lock held. */
	काष्ठा delayed_work work;
	क्रमागत अणुISO_RES_ALLOC, ISO_RES_REALLOC, ISO_RES_DEALLOC,
	      ISO_RES_ALLOC_ONCE, ISO_RES_DEALLOC_ONCE,पूर्ण toकरो;
	पूर्णांक generation;
	u64 channels;
	s32 bandwidth;
	काष्ठा iso_resource_event *e_alloc, *e_dealloc;
पूर्ण;

अटल व्योम release_iso_resource(काष्ठा client *, काष्ठा client_resource *);

अटल व्योम schedule_iso_resource(काष्ठा iso_resource *r, अचिन्हित दीर्घ delay)
अणु
	client_get(r->client);
	अगर (!queue_delayed_work(fw_workqueue, &r->work, delay))
		client_put(r->client);
पूर्ण

अटल व्योम schedule_अगर_iso_resource(काष्ठा client_resource *resource)
अणु
	अगर (resource->release == release_iso_resource)
		schedule_iso_resource(container_of(resource,
					काष्ठा iso_resource, resource), 0);
पूर्ण

/*
 * dequeue_event() just kमुक्त()'s the event, so the event has to be
 * the first field in a काष्ठा XYZ_event.
 */
काष्ठा event अणु
	काष्ठा अणु व्योम *data; माप_प्रकार size; पूर्ण v[2];
	काष्ठा list_head link;
पूर्ण;

काष्ठा bus_reset_event अणु
	काष्ठा event event;
	काष्ठा fw_cdev_event_bus_reset reset;
पूर्ण;

काष्ठा outbound_transaction_event अणु
	काष्ठा event event;
	काष्ठा client *client;
	काष्ठा outbound_transaction_resource r;
	काष्ठा fw_cdev_event_response response;
पूर्ण;

काष्ठा inbound_transaction_event अणु
	काष्ठा event event;
	जोड़ अणु
		काष्ठा fw_cdev_event_request request;
		काष्ठा fw_cdev_event_request2 request2;
	पूर्ण req;
पूर्ण;

काष्ठा iso_पूर्णांकerrupt_event अणु
	काष्ठा event event;
	काष्ठा fw_cdev_event_iso_पूर्णांकerrupt पूर्णांकerrupt;
पूर्ण;

काष्ठा iso_पूर्णांकerrupt_mc_event अणु
	काष्ठा event event;
	काष्ठा fw_cdev_event_iso_पूर्णांकerrupt_mc पूर्णांकerrupt;
पूर्ण;

काष्ठा iso_resource_event अणु
	काष्ठा event event;
	काष्ठा fw_cdev_event_iso_resource iso_resource;
पूर्ण;

काष्ठा outbound_phy_packet_event अणु
	काष्ठा event event;
	काष्ठा client *client;
	काष्ठा fw_packet p;
	काष्ठा fw_cdev_event_phy_packet phy_packet;
पूर्ण;

काष्ठा inbound_phy_packet_event अणु
	काष्ठा event event;
	काष्ठा fw_cdev_event_phy_packet phy_packet;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल व्योम __user *u64_to_uptr(u64 value)
अणु
	अगर (in_compat_syscall())
		वापस compat_ptr(value);
	अन्यथा
		वापस (व्योम __user *)(अचिन्हित दीर्घ)value;
पूर्ण

अटल u64 uptr_to_u64(व्योम __user *ptr)
अणु
	अगर (in_compat_syscall())
		वापस ptr_to_compat(ptr);
	अन्यथा
		वापस (u64)(अचिन्हित दीर्घ)ptr;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __user *u64_to_uptr(u64 value)
अणु
	वापस (व्योम __user *)(अचिन्हित दीर्घ)value;
पूर्ण

अटल अंतरभूत u64 uptr_to_u64(व्योम __user *ptr)
अणु
	वापस (u64)(अचिन्हित दीर्घ)ptr;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक fw_device_op_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fw_device *device;
	काष्ठा client *client;

	device = fw_device_get_by_devt(inode->i_rdev);
	अगर (device == शून्य)
		वापस -ENODEV;

	अगर (fw_device_is_shutकरोwn(device)) अणु
		fw_device_put(device);
		वापस -ENODEV;
	पूर्ण

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (client == शून्य) अणु
		fw_device_put(device);
		वापस -ENOMEM;
	पूर्ण

	client->device = device;
	spin_lock_init(&client->lock);
	idr_init(&client->resource_idr);
	INIT_LIST_HEAD(&client->event_list);
	init_रुकोqueue_head(&client->रुको);
	init_रुकोqueue_head(&client->tx_flush_रुको);
	INIT_LIST_HEAD(&client->phy_receiver_link);
	INIT_LIST_HEAD(&client->link);
	kref_init(&client->kref);

	file->निजी_data = client;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल व्योम queue_event(काष्ठा client *client, काष्ठा event *event,
			व्योम *data0, माप_प्रकार size0, व्योम *data1, माप_प्रकार size1)
अणु
	अचिन्हित दीर्घ flags;

	event->v[0].data = data0;
	event->v[0].size = size0;
	event->v[1].data = data1;
	event->v[1].size = size1;

	spin_lock_irqsave(&client->lock, flags);
	अगर (client->in_shutकरोwn)
		kमुक्त(event);
	अन्यथा
		list_add_tail(&event->link, &client->event_list);
	spin_unlock_irqrestore(&client->lock, flags);

	wake_up_पूर्णांकerruptible(&client->रुको);
पूर्ण

अटल पूर्णांक dequeue_event(काष्ठा client *client,
			 अक्षर __user *buffer, माप_प्रकार count)
अणु
	काष्ठा event *event;
	माप_प्रकार size, total;
	पूर्णांक i, ret;

	ret = रुको_event_पूर्णांकerruptible(client->रुको,
			!list_empty(&client->event_list) ||
			fw_device_is_shutकरोwn(client->device));
	अगर (ret < 0)
		वापस ret;

	अगर (list_empty(&client->event_list) &&
		       fw_device_is_shutकरोwn(client->device))
		वापस -ENODEV;

	spin_lock_irq(&client->lock);
	event = list_first_entry(&client->event_list, काष्ठा event, link);
	list_del(&event->link);
	spin_unlock_irq(&client->lock);

	total = 0;
	क्रम (i = 0; i < ARRAY_SIZE(event->v) && total < count; i++) अणु
		size = min(event->v[i].size, count - total);
		अगर (copy_to_user(buffer + total, event->v[i].data, size)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		total += size;
	पूर्ण
	ret = total;

 out:
	kमुक्त(event);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार fw_device_op_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा client *client = file->निजी_data;

	वापस dequeue_event(client, buffer, count);
पूर्ण

अटल व्योम fill_bus_reset_event(काष्ठा fw_cdev_event_bus_reset *event,
				 काष्ठा client *client)
अणु
	काष्ठा fw_card *card = client->device->card;

	spin_lock_irq(&card->lock);

	event->closure	     = client->bus_reset_closure;
	event->type          = FW_CDEV_EVENT_BUS_RESET;
	event->generation    = client->device->generation;
	event->node_id       = client->device->node_id;
	event->local_node_id = card->local_node->node_id;
	event->bm_node_id    = card->bm_node_id;
	event->irm_node_id   = card->irm_node->node_id;
	event->root_node_id  = card->root_node->node_id;

	spin_unlock_irq(&card->lock);
पूर्ण

अटल व्योम क्रम_each_client(काष्ठा fw_device *device,
			    व्योम (*callback)(काष्ठा client *client))
अणु
	काष्ठा client *c;

	mutex_lock(&device->client_list_mutex);
	list_क्रम_each_entry(c, &device->client_list, link)
		callback(c);
	mutex_unlock(&device->client_list_mutex);
पूर्ण

अटल पूर्णांक schedule_पुनः_स्मृतिations(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	schedule_अगर_iso_resource(p);

	वापस 0;
पूर्ण

अटल व्योम queue_bus_reset_event(काष्ठा client *client)
अणु
	काष्ठा bus_reset_event *e;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (e == शून्य)
		वापस;

	fill_bus_reset_event(&e->reset, client);

	queue_event(client, &e->event,
		    &e->reset, माप(e->reset), शून्य, 0);

	spin_lock_irq(&client->lock);
	idr_क्रम_each(&client->resource_idr, schedule_पुनः_स्मृतिations, client);
	spin_unlock_irq(&client->lock);
पूर्ण

व्योम fw_device_cdev_update(काष्ठा fw_device *device)
अणु
	क्रम_each_client(device, queue_bus_reset_event);
पूर्ण

अटल व्योम wake_up_client(काष्ठा client *client)
अणु
	wake_up_पूर्णांकerruptible(&client->रुको);
पूर्ण

व्योम fw_device_cdev_हटाओ(काष्ठा fw_device *device)
अणु
	क्रम_each_client(device, wake_up_client);
पूर्ण

जोड़ ioctl_arg अणु
	काष्ठा fw_cdev_get_info			get_info;
	काष्ठा fw_cdev_send_request		send_request;
	काष्ठा fw_cdev_allocate			allocate;
	काष्ठा fw_cdev_deallocate		deallocate;
	काष्ठा fw_cdev_send_response		send_response;
	काष्ठा fw_cdev_initiate_bus_reset	initiate_bus_reset;
	काष्ठा fw_cdev_add_descriptor		add_descriptor;
	काष्ठा fw_cdev_हटाओ_descriptor	हटाओ_descriptor;
	काष्ठा fw_cdev_create_iso_context	create_iso_context;
	काष्ठा fw_cdev_queue_iso		queue_iso;
	काष्ठा fw_cdev_start_iso		start_iso;
	काष्ठा fw_cdev_stop_iso			stop_iso;
	काष्ठा fw_cdev_get_cycle_समयr		get_cycle_समयr;
	काष्ठा fw_cdev_allocate_iso_resource	allocate_iso_resource;
	काष्ठा fw_cdev_send_stream_packet	send_stream_packet;
	काष्ठा fw_cdev_get_cycle_समयr2		get_cycle_समयr2;
	काष्ठा fw_cdev_send_phy_packet		send_phy_packet;
	काष्ठा fw_cdev_receive_phy_packets	receive_phy_packets;
	काष्ठा fw_cdev_set_iso_channels		set_iso_channels;
	काष्ठा fw_cdev_flush_iso		flush_iso;
पूर्ण;

अटल पूर्णांक ioctl_get_info(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_get_info *a = &arg->get_info;
	काष्ठा fw_cdev_event_bus_reset bus_reset;
	अचिन्हित दीर्घ ret = 0;

	client->version = a->version;
	a->version = FW_CDEV_KERNEL_VERSION;
	a->card = client->device->card->index;

	करोwn_पढ़ो(&fw_device_rwsem);

	अगर (a->rom != 0) अणु
		माप_प्रकार want = a->rom_length;
		माप_प्रकार have = client->device->config_rom_length * 4;

		ret = copy_to_user(u64_to_uptr(a->rom),
				   client->device->config_rom, min(want, have));
	पूर्ण
	a->rom_length = client->device->config_rom_length * 4;

	up_पढ़ो(&fw_device_rwsem);

	अगर (ret != 0)
		वापस -EFAULT;

	mutex_lock(&client->device->client_list_mutex);

	client->bus_reset_closure = a->bus_reset_closure;
	अगर (a->bus_reset != 0) अणु
		fill_bus_reset_event(&bus_reset, client);
		/* unaligned size of bus_reset is 36 bytes */
		ret = copy_to_user(u64_to_uptr(a->bus_reset), &bus_reset, 36);
	पूर्ण
	अगर (ret == 0 && list_empty(&client->link))
		list_add_tail(&client->link, &client->device->client_list);

	mutex_unlock(&client->device->client_list_mutex);

	वापस ret ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक add_client_resource(काष्ठा client *client,
			       काष्ठा client_resource *resource, gfp_t gfp_mask)
अणु
	bool preload = gfpflags_allow_blocking(gfp_mask);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (preload)
		idr_preload(gfp_mask);
	spin_lock_irqsave(&client->lock, flags);

	अगर (client->in_shutकरोwn)
		ret = -ECANCELED;
	अन्यथा
		ret = idr_alloc(&client->resource_idr, resource, 0, 0,
				GFP_NOWAIT);
	अगर (ret >= 0) अणु
		resource->handle = ret;
		client_get(client);
		schedule_अगर_iso_resource(resource);
	पूर्ण

	spin_unlock_irqrestore(&client->lock, flags);
	अगर (preload)
		idr_preload_end();

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक release_client_resource(काष्ठा client *client, u32 handle,
				   client_resource_release_fn_t release,
				   काष्ठा client_resource **वापस_resource)
अणु
	काष्ठा client_resource *resource;

	spin_lock_irq(&client->lock);
	अगर (client->in_shutकरोwn)
		resource = शून्य;
	अन्यथा
		resource = idr_find(&client->resource_idr, handle);
	अगर (resource && resource->release == release)
		idr_हटाओ(&client->resource_idr, handle);
	spin_unlock_irq(&client->lock);

	अगर (!(resource && resource->release == release))
		वापस -EINVAL;

	अगर (वापस_resource)
		*वापस_resource = resource;
	अन्यथा
		resource->release(client, resource);

	client_put(client);

	वापस 0;
पूर्ण

अटल व्योम release_transaction(काष्ठा client *client,
				काष्ठा client_resource *resource)
अणु
पूर्ण

अटल व्योम complete_transaction(काष्ठा fw_card *card, पूर्णांक rcode,
				 व्योम *payload, माप_प्रकार length, व्योम *data)
अणु
	काष्ठा outbound_transaction_event *e = data;
	काष्ठा fw_cdev_event_response *rsp = &e->response;
	काष्ठा client *client = e->client;
	अचिन्हित दीर्घ flags;

	अगर (length < rsp->length)
		rsp->length = length;
	अगर (rcode == RCODE_COMPLETE)
		स_नकल(rsp->data, payload, rsp->length);

	spin_lock_irqsave(&client->lock, flags);
	idr_हटाओ(&client->resource_idr, e->r.resource.handle);
	अगर (client->in_shutकरोwn)
		wake_up(&client->tx_flush_रुको);
	spin_unlock_irqrestore(&client->lock, flags);

	rsp->type = FW_CDEV_EVENT_RESPONSE;
	rsp->rcode = rcode;

	/*
	 * In the हाल that माप(*rsp) करोesn't align with the position of the
	 * data, and the पढ़ो is लघु, preserve an extra copy of the data
	 * to stay compatible with a pre-2.6.27 bug.  Since the bug is harmless
	 * क्रम लघु पढ़ोs and some apps depended on it, this is both safe
	 * and prudent क्रम compatibility.
	 */
	अगर (rsp->length <= माप(*rsp) - दुरत्व(typeof(*rsp), data))
		queue_event(client, &e->event, rsp, माप(*rsp),
			    rsp->data, rsp->length);
	अन्यथा
		queue_event(client, &e->event, rsp, माप(*rsp) + rsp->length,
			    शून्य, 0);

	/* Drop the idr's reference */
	client_put(client);
पूर्ण

अटल पूर्णांक init_request(काष्ठा client *client,
			काष्ठा fw_cdev_send_request *request,
			पूर्णांक destination_id, पूर्णांक speed)
अणु
	काष्ठा outbound_transaction_event *e;
	पूर्णांक ret;

	अगर (request->tcode != TCODE_STREAM_DATA &&
	    (request->length > 4096 || request->length > 512 << speed))
		वापस -EIO;

	अगर (request->tcode == TCODE_WRITE_QUADLET_REQUEST &&
	    request->length < 4)
		वापस -EINVAL;

	e = kदो_स्मृति(माप(*e) + request->length, GFP_KERNEL);
	अगर (e == शून्य)
		वापस -ENOMEM;

	e->client = client;
	e->response.length = request->length;
	e->response.closure = request->closure;

	अगर (request->data &&
	    copy_from_user(e->response.data,
			   u64_to_uptr(request->data), request->length)) अणु
		ret = -EFAULT;
		जाओ failed;
	पूर्ण

	e->r.resource.release = release_transaction;
	ret = add_client_resource(client, &e->r.resource, GFP_KERNEL);
	अगर (ret < 0)
		जाओ failed;

	fw_send_request(client->device->card, &e->r.transaction,
			request->tcode, destination_id, request->generation,
			speed, request->offset, e->response.data,
			request->length, complete_transaction, e);
	वापस 0;

 failed:
	kमुक्त(e);

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_send_request(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	चयन (arg->send_request.tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
	हाल TCODE_READ_QUADLET_REQUEST:
	हाल TCODE_READ_BLOCK_REQUEST:
	हाल TCODE_LOCK_MASK_SWAP:
	हाल TCODE_LOCK_COMPARE_SWAP:
	हाल TCODE_LOCK_FETCH_ADD:
	हाल TCODE_LOCK_LITTLE_ADD:
	हाल TCODE_LOCK_BOUNDED_ADD:
	हाल TCODE_LOCK_WRAP_ADD:
	हाल TCODE_LOCK_VENDOR_DEPENDENT:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस init_request(client, &arg->send_request, client->device->node_id,
			    client->device->max_speed);
पूर्ण

अटल अंतरभूत bool is_fcp_request(काष्ठा fw_request *request)
अणु
	वापस request == शून्य;
पूर्ण

अटल व्योम release_request(काष्ठा client *client,
			    काष्ठा client_resource *resource)
अणु
	काष्ठा inbound_transaction_resource *r = container_of(resource,
			काष्ठा inbound_transaction_resource, resource);

	अगर (is_fcp_request(r->request))
		kमुक्त(r->data);
	अन्यथा
		fw_send_response(r->card, r->request, RCODE_CONFLICT_ERROR);

	fw_card_put(r->card);
	kमुक्त(r);
पूर्ण

अटल व्योम handle_request(काष्ठा fw_card *card, काष्ठा fw_request *request,
			   पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			   पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			   व्योम *payload, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा address_handler_resource *handler = callback_data;
	काष्ठा inbound_transaction_resource *r;
	काष्ठा inbound_transaction_event *e;
	माप_प्रकार event_size0;
	व्योम *fcp_frame = शून्य;
	पूर्णांक ret;

	/* card may be dअगरferent from handler->client->device->card */
	fw_card_get(card);

	r = kदो_स्मृति(माप(*r), GFP_ATOMIC);
	e = kदो_स्मृति(माप(*e), GFP_ATOMIC);
	अगर (r == शून्य || e == शून्य)
		जाओ failed;

	r->card    = card;
	r->request = request;
	r->data    = payload;
	r->length  = length;

	अगर (is_fcp_request(request)) अणु
		/*
		 * FIXME: Let core-transaction.c manage a
		 * single reference-counted copy?
		 */
		fcp_frame = kmemdup(payload, length, GFP_ATOMIC);
		अगर (fcp_frame == शून्य)
			जाओ failed;

		r->data = fcp_frame;
	पूर्ण

	r->resource.release = release_request;
	ret = add_client_resource(handler->client, &r->resource, GFP_ATOMIC);
	अगर (ret < 0)
		जाओ failed;

	अगर (handler->client->version < FW_CDEV_VERSION_EVENT_REQUEST2) अणु
		काष्ठा fw_cdev_event_request *req = &e->req.request;

		अगर (tcode & 0x10)
			tcode = TCODE_LOCK_REQUEST;

		req->type	= FW_CDEV_EVENT_REQUEST;
		req->tcode	= tcode;
		req->offset	= offset;
		req->length	= length;
		req->handle	= r->resource.handle;
		req->closure	= handler->closure;
		event_size0	= माप(*req);
	पूर्ण अन्यथा अणु
		काष्ठा fw_cdev_event_request2 *req = &e->req.request2;

		req->type	= FW_CDEV_EVENT_REQUEST2;
		req->tcode	= tcode;
		req->offset	= offset;
		req->source_node_id = source;
		req->destination_node_id = destination;
		req->card	= card->index;
		req->generation	= generation;
		req->length	= length;
		req->handle	= r->resource.handle;
		req->closure	= handler->closure;
		event_size0	= माप(*req);
	पूर्ण

	queue_event(handler->client, &e->event,
		    &e->req, event_size0, r->data, length);
	वापस;

 failed:
	kमुक्त(r);
	kमुक्त(e);
	kमुक्त(fcp_frame);

	अगर (!is_fcp_request(request))
		fw_send_response(card, request, RCODE_CONFLICT_ERROR);

	fw_card_put(card);
पूर्ण

अटल व्योम release_address_handler(काष्ठा client *client,
				    काष्ठा client_resource *resource)
अणु
	काष्ठा address_handler_resource *r =
	    container_of(resource, काष्ठा address_handler_resource, resource);

	fw_core_हटाओ_address_handler(&r->handler);
	kमुक्त(r);
पूर्ण

अटल पूर्णांक ioctl_allocate(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_allocate *a = &arg->allocate;
	काष्ठा address_handler_resource *r;
	काष्ठा fw_address_region region;
	पूर्णांक ret;

	r = kदो_स्मृति(माप(*r), GFP_KERNEL);
	अगर (r == शून्य)
		वापस -ENOMEM;

	region.start = a->offset;
	अगर (client->version < FW_CDEV_VERSION_ALLOCATE_REGION_END)
		region.end = a->offset + a->length;
	अन्यथा
		region.end = a->region_end;

	r->handler.length           = a->length;
	r->handler.address_callback = handle_request;
	r->handler.callback_data    = r;
	r->closure   = a->closure;
	r->client    = client;

	ret = fw_core_add_address_handler(&r->handler, &region);
	अगर (ret < 0) अणु
		kमुक्त(r);
		वापस ret;
	पूर्ण
	a->offset = r->handler.offset;

	r->resource.release = release_address_handler;
	ret = add_client_resource(client, &r->resource, GFP_KERNEL);
	अगर (ret < 0) अणु
		release_address_handler(client, &r->resource);
		वापस ret;
	पूर्ण
	a->handle = r->resource.handle;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_deallocate(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	वापस release_client_resource(client, arg->deallocate.handle,
				       release_address_handler, शून्य);
पूर्ण

अटल पूर्णांक ioctl_send_response(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_send_response *a = &arg->send_response;
	काष्ठा client_resource *resource;
	काष्ठा inbound_transaction_resource *r;
	पूर्णांक ret = 0;

	अगर (release_client_resource(client, a->handle,
				    release_request, &resource) < 0)
		वापस -EINVAL;

	r = container_of(resource, काष्ठा inbound_transaction_resource,
			 resource);
	अगर (is_fcp_request(r->request))
		जाओ out;

	अगर (a->length != fw_get_response_length(r->request)) अणु
		ret = -EINVAL;
		kमुक्त(r->request);
		जाओ out;
	पूर्ण
	अगर (copy_from_user(r->data, u64_to_uptr(a->data), a->length)) अणु
		ret = -EFAULT;
		kमुक्त(r->request);
		जाओ out;
	पूर्ण
	fw_send_response(r->card, r->request, a->rcode);
 out:
	fw_card_put(r->card);
	kमुक्त(r);

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_initiate_bus_reset(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	fw_schedule_bus_reset(client->device->card, true,
			arg->initiate_bus_reset.type == FW_CDEV_SHORT_RESET);
	वापस 0;
पूर्ण

अटल व्योम release_descriptor(काष्ठा client *client,
			       काष्ठा client_resource *resource)
अणु
	काष्ठा descriptor_resource *r =
		container_of(resource, काष्ठा descriptor_resource, resource);

	fw_core_हटाओ_descriptor(&r->descriptor);
	kमुक्त(r);
पूर्ण

अटल पूर्णांक ioctl_add_descriptor(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_add_descriptor *a = &arg->add_descriptor;
	काष्ठा descriptor_resource *r;
	पूर्णांक ret;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	अगर (!client->device->is_local)
		वापस -ENOSYS;

	अगर (a->length > 256)
		वापस -EINVAL;

	r = kदो_स्मृति(माप(*r) + a->length * 4, GFP_KERNEL);
	अगर (r == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(r->data, u64_to_uptr(a->data), a->length * 4)) अणु
		ret = -EFAULT;
		जाओ failed;
	पूर्ण

	r->descriptor.length    = a->length;
	r->descriptor.immediate = a->immediate;
	r->descriptor.key       = a->key;
	r->descriptor.data      = r->data;

	ret = fw_core_add_descriptor(&r->descriptor);
	अगर (ret < 0)
		जाओ failed;

	r->resource.release = release_descriptor;
	ret = add_client_resource(client, &r->resource, GFP_KERNEL);
	अगर (ret < 0) अणु
		fw_core_हटाओ_descriptor(&r->descriptor);
		जाओ failed;
	पूर्ण
	a->handle = r->resource.handle;

	वापस 0;
 failed:
	kमुक्त(r);

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_हटाओ_descriptor(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	वापस release_client_resource(client, arg->हटाओ_descriptor.handle,
				       release_descriptor, शून्य);
पूर्ण

अटल व्योम iso_callback(काष्ठा fw_iso_context *context, u32 cycle,
			 माप_प्रकार header_length, व्योम *header, व्योम *data)
अणु
	काष्ठा client *client = data;
	काष्ठा iso_पूर्णांकerrupt_event *e;

	e = kदो_स्मृति(माप(*e) + header_length, GFP_ATOMIC);
	अगर (e == शून्य)
		वापस;

	e->पूर्णांकerrupt.type      = FW_CDEV_EVENT_ISO_INTERRUPT;
	e->पूर्णांकerrupt.closure   = client->iso_closure;
	e->पूर्णांकerrupt.cycle     = cycle;
	e->पूर्णांकerrupt.header_length = header_length;
	स_नकल(e->पूर्णांकerrupt.header, header, header_length);
	queue_event(client, &e->event, &e->पूर्णांकerrupt,
		    माप(e->पूर्णांकerrupt) + header_length, शून्य, 0);
पूर्ण

अटल व्योम iso_mc_callback(काष्ठा fw_iso_context *context,
			    dma_addr_t completed, व्योम *data)
अणु
	काष्ठा client *client = data;
	काष्ठा iso_पूर्णांकerrupt_mc_event *e;

	e = kदो_स्मृति(माप(*e), GFP_ATOMIC);
	अगर (e == शून्य)
		वापस;

	e->पूर्णांकerrupt.type      = FW_CDEV_EVENT_ISO_INTERRUPT_MULTICHANNEL;
	e->पूर्णांकerrupt.closure   = client->iso_closure;
	e->पूर्णांकerrupt.completed = fw_iso_buffer_lookup(&client->buffer,
						      completed);
	queue_event(client, &e->event, &e->पूर्णांकerrupt,
		    माप(e->पूर्णांकerrupt), शून्य, 0);
पूर्ण

अटल क्रमागत dma_data_direction iso_dma_direction(काष्ठा fw_iso_context *context)
अणु
		अगर (context->type == FW_ISO_CONTEXT_TRANSMIT)
			वापस DMA_TO_DEVICE;
		अन्यथा
			वापस DMA_FROM_DEVICE;
पूर्ण

अटल पूर्णांक ioctl_create_iso_context(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_create_iso_context *a = &arg->create_iso_context;
	काष्ठा fw_iso_context *context;
	fw_iso_callback_t cb;
	पूर्णांक ret;

	BUILD_BUG_ON(FW_CDEV_ISO_CONTEXT_TRANSMIT != FW_ISO_CONTEXT_TRANSMIT ||
		     FW_CDEV_ISO_CONTEXT_RECEIVE  != FW_ISO_CONTEXT_RECEIVE  ||
		     FW_CDEV_ISO_CONTEXT_RECEIVE_MULTICHANNEL !=
					FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL);

	चयन (a->type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		अगर (a->speed > SCODE_3200 || a->channel > 63)
			वापस -EINVAL;

		cb = iso_callback;
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE:
		अगर (a->header_size < 4 || (a->header_size & 3) ||
		    a->channel > 63)
			वापस -EINVAL;

		cb = iso_callback;
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		cb = (fw_iso_callback_t)iso_mc_callback;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	context = fw_iso_context_create(client->device->card, a->type,
			a->channel, a->speed, a->header_size, cb, client);
	अगर (IS_ERR(context))
		वापस PTR_ERR(context);
	अगर (client->version < FW_CDEV_VERSION_AUTO_FLUSH_ISO_OVERFLOW)
		context->drop_overflow_headers = true;

	/* We only support one context at this समय. */
	spin_lock_irq(&client->lock);
	अगर (client->iso_context != शून्य) अणु
		spin_unlock_irq(&client->lock);
		fw_iso_context_destroy(context);

		वापस -EBUSY;
	पूर्ण
	अगर (!client->buffer_is_mapped) अणु
		ret = fw_iso_buffer_map_dma(&client->buffer,
					    client->device->card,
					    iso_dma_direction(context));
		अगर (ret < 0) अणु
			spin_unlock_irq(&client->lock);
			fw_iso_context_destroy(context);

			वापस ret;
		पूर्ण
		client->buffer_is_mapped = true;
	पूर्ण
	client->iso_closure = a->closure;
	client->iso_context = context;
	spin_unlock_irq(&client->lock);

	a->handle = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_set_iso_channels(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_set_iso_channels *a = &arg->set_iso_channels;
	काष्ठा fw_iso_context *ctx = client->iso_context;

	अगर (ctx == शून्य || a->handle != 0)
		वापस -EINVAL;

	वापस fw_iso_context_set_channels(ctx, &a->channels);
पूर्ण

/* Macros क्रम decoding the iso packet control header. */
#घोषणा GET_PAYLOAD_LENGTH(v)	((v) & 0xffff)
#घोषणा GET_INTERRUPT(v)	(((v) >> 16) & 0x01)
#घोषणा GET_SKIP(v)		(((v) >> 17) & 0x01)
#घोषणा GET_TAG(v)		(((v) >> 18) & 0x03)
#घोषणा GET_SY(v)		(((v) >> 20) & 0x0f)
#घोषणा GET_HEADER_LENGTH(v)	(((v) >> 24) & 0xff)

अटल पूर्णांक ioctl_queue_iso(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_queue_iso *a = &arg->queue_iso;
	काष्ठा fw_cdev_iso_packet __user *p, *end, *next;
	काष्ठा fw_iso_context *ctx = client->iso_context;
	अचिन्हित दीर्घ payload, buffer_end, transmit_header_bytes = 0;
	u32 control;
	पूर्णांक count;
	काष्ठा अणु
		काष्ठा fw_iso_packet packet;
		u8 header[256];
	पूर्ण u;

	अगर (ctx == शून्य || a->handle != 0)
		वापस -EINVAL;

	/*
	 * If the user passes a non-शून्य data poपूर्णांकer, has mmap()'ed
	 * the iso buffer, and the poपूर्णांकer poपूर्णांकs inside the buffer,
	 * we setup the payload poपूर्णांकers accordingly.  Otherwise we
	 * set them both to 0, which will still let packets with
	 * payload_length == 0 through.  In other words, अगर no packets
	 * use the indirect payload, the iso buffer need not be mapped
	 * and the a->data poपूर्णांकer is ignored.
	 */
	payload = (अचिन्हित दीर्घ)a->data - client->vm_start;
	buffer_end = client->buffer.page_count << PAGE_SHIFT;
	अगर (a->data == 0 || client->buffer.pages == शून्य ||
	    payload >= buffer_end) अणु
		payload = 0;
		buffer_end = 0;
	पूर्ण

	अगर (ctx->type == FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL && payload & 3)
		वापस -EINVAL;

	p = (काष्ठा fw_cdev_iso_packet __user *)u64_to_uptr(a->packets);

	end = (व्योम __user *)p + a->size;
	count = 0;
	जबतक (p < end) अणु
		अगर (get_user(control, &p->control))
			वापस -EFAULT;
		u.packet.payload_length = GET_PAYLOAD_LENGTH(control);
		u.packet.पूर्णांकerrupt = GET_INTERRUPT(control);
		u.packet.skip = GET_SKIP(control);
		u.packet.tag = GET_TAG(control);
		u.packet.sy = GET_SY(control);
		u.packet.header_length = GET_HEADER_LENGTH(control);

		चयन (ctx->type) अणु
		हाल FW_ISO_CONTEXT_TRANSMIT:
			अगर (u.packet.header_length & 3)
				वापस -EINVAL;
			transmit_header_bytes = u.packet.header_length;
			अवरोध;

		हाल FW_ISO_CONTEXT_RECEIVE:
			अगर (u.packet.header_length == 0 ||
			    u.packet.header_length % ctx->header_size != 0)
				वापस -EINVAL;
			अवरोध;

		हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
			अगर (u.packet.payload_length == 0 ||
			    u.packet.payload_length & 3)
				वापस -EINVAL;
			अवरोध;
		पूर्ण

		next = (काष्ठा fw_cdev_iso_packet __user *)
			&p->header[transmit_header_bytes / 4];
		अगर (next > end)
			वापस -EINVAL;
		अगर (copy_from_user
		    (u.packet.header, p->header, transmit_header_bytes))
			वापस -EFAULT;
		अगर (u.packet.skip && ctx->type == FW_ISO_CONTEXT_TRANSMIT &&
		    u.packet.header_length + u.packet.payload_length > 0)
			वापस -EINVAL;
		अगर (payload + u.packet.payload_length > buffer_end)
			वापस -EINVAL;

		अगर (fw_iso_context_queue(ctx, &u.packet,
					 &client->buffer, payload))
			अवरोध;

		p = next;
		payload += u.packet.payload_length;
		count++;
	पूर्ण
	fw_iso_context_queue_flush(ctx);

	a->size    -= uptr_to_u64(p) - a->packets;
	a->packets  = uptr_to_u64(p);
	a->data     = client->vm_start + payload;

	वापस count;
पूर्ण

अटल पूर्णांक ioctl_start_iso(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_start_iso *a = &arg->start_iso;

	BUILD_BUG_ON(
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG0 != FW_ISO_CONTEXT_MATCH_TAG0 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG1 != FW_ISO_CONTEXT_MATCH_TAG1 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG2 != FW_ISO_CONTEXT_MATCH_TAG2 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG3 != FW_ISO_CONTEXT_MATCH_TAG3 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_ALL_TAGS != FW_ISO_CONTEXT_MATCH_ALL_TAGS);

	अगर (client->iso_context == शून्य || a->handle != 0)
		वापस -EINVAL;

	अगर (client->iso_context->type == FW_ISO_CONTEXT_RECEIVE &&
	    (a->tags == 0 || a->tags > 15 || a->sync > 15))
		वापस -EINVAL;

	वापस fw_iso_context_start(client->iso_context,
				    a->cycle, a->sync, a->tags);
पूर्ण

अटल पूर्णांक ioctl_stop_iso(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_stop_iso *a = &arg->stop_iso;

	अगर (client->iso_context == शून्य || a->handle != 0)
		वापस -EINVAL;

	वापस fw_iso_context_stop(client->iso_context);
पूर्ण

अटल पूर्णांक ioctl_flush_iso(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_flush_iso *a = &arg->flush_iso;

	अगर (client->iso_context == शून्य || a->handle != 0)
		वापस -EINVAL;

	वापस fw_iso_context_flush_completions(client->iso_context);
पूर्ण

अटल पूर्णांक ioctl_get_cycle_समयr2(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_get_cycle_समयr2 *a = &arg->get_cycle_समयr2;
	काष्ठा fw_card *card = client->device->card;
	काष्ठा बारpec64 ts = अणु0, 0पूर्ण;
	u32 cycle_समय;
	पूर्णांक ret = 0;

	local_irq_disable();

	cycle_समय = card->driver->पढ़ो_csr(card, CSR_CYCLE_TIME);

	चयन (a->clk_id) अणु
	हाल CLOCK_REALTIME:      kसमय_get_real_ts64(&ts);	अवरोध;
	हाल CLOCK_MONOTONIC:     kसमय_get_ts64(&ts);		अवरोध;
	हाल CLOCK_MONOTONIC_RAW: kसमय_get_raw_ts64(&ts);	अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	local_irq_enable();

	a->tv_sec      = ts.tv_sec;
	a->tv_nsec     = ts.tv_nsec;
	a->cycle_समयr = cycle_समय;

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_get_cycle_समयr(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_get_cycle_समयr *a = &arg->get_cycle_समयr;
	काष्ठा fw_cdev_get_cycle_समयr2 ct2;

	ct2.clk_id = CLOCK_REALTIME;
	ioctl_get_cycle_समयr2(client, (जोड़ ioctl_arg *)&ct2);

	a->local_समय = ct2.tv_sec * USEC_PER_SEC + ct2.tv_nsec / NSEC_PER_USEC;
	a->cycle_समयr = ct2.cycle_समयr;

	वापस 0;
पूर्ण

अटल व्योम iso_resource_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iso_resource_event *e;
	काष्ठा iso_resource *r =
			container_of(work, काष्ठा iso_resource, work.work);
	काष्ठा client *client = r->client;
	पूर्णांक generation, channel, bandwidth, toकरो;
	bool skip, मुक्त, success;

	spin_lock_irq(&client->lock);
	generation = client->device->generation;
	toकरो = r->toकरो;
	/* Allow 1000ms grace period क्रम other पुनः_स्मृतिations. */
	अगर (toकरो == ISO_RES_ALLOC &&
	    समय_beक्रमe64(get_jअगरfies_64(),
			  client->device->card->reset_jअगरfies + HZ)) अणु
		schedule_iso_resource(r, DIV_ROUND_UP(HZ, 3));
		skip = true;
	पूर्ण अन्यथा अणु
		/* We could be called twice within the same generation. */
		skip = toकरो == ISO_RES_REALLOC &&
		       r->generation == generation;
	पूर्ण
	मुक्त = toकरो == ISO_RES_DEALLOC ||
	       toकरो == ISO_RES_ALLOC_ONCE ||
	       toकरो == ISO_RES_DEALLOC_ONCE;
	r->generation = generation;
	spin_unlock_irq(&client->lock);

	अगर (skip)
		जाओ out;

	bandwidth = r->bandwidth;

	fw_iso_resource_manage(client->device->card, generation,
			r->channels, &channel, &bandwidth,
			toकरो == ISO_RES_ALLOC ||
			toकरो == ISO_RES_REALLOC ||
			toकरो == ISO_RES_ALLOC_ONCE);
	/*
	 * Is this generation outdated alपढ़ोy?  As दीर्घ as this resource sticks
	 * in the idr, it will be scheduled again क्रम a newer generation or at
	 * shutकरोwn.
	 */
	अगर (channel == -EAGAIN &&
	    (toकरो == ISO_RES_ALLOC || toकरो == ISO_RES_REALLOC))
		जाओ out;

	success = channel >= 0 || bandwidth > 0;

	spin_lock_irq(&client->lock);
	/*
	 * Transit from allocation to पुनः_स्मृतिation, except अगर the client
	 * requested deallocation in the meanसमय.
	 */
	अगर (r->toकरो == ISO_RES_ALLOC)
		r->toकरो = ISO_RES_REALLOC;
	/*
	 * Allocation or पुनः_स्मृतिation failure?  Pull this resource out of the
	 * idr and prepare क्रम deletion, unless the client is shutting करोwn.
	 */
	अगर (r->toकरो == ISO_RES_REALLOC && !success &&
	    !client->in_shutकरोwn &&
	    idr_हटाओ(&client->resource_idr, r->resource.handle)) अणु
		client_put(client);
		मुक्त = true;
	पूर्ण
	spin_unlock_irq(&client->lock);

	अगर (toकरो == ISO_RES_ALLOC && channel >= 0)
		r->channels = 1ULL << channel;

	अगर (toकरो == ISO_RES_REALLOC && success)
		जाओ out;

	अगर (toकरो == ISO_RES_ALLOC || toकरो == ISO_RES_ALLOC_ONCE) अणु
		e = r->e_alloc;
		r->e_alloc = शून्य;
	पूर्ण अन्यथा अणु
		e = r->e_dealloc;
		r->e_dealloc = शून्य;
	पूर्ण
	e->iso_resource.handle    = r->resource.handle;
	e->iso_resource.channel   = channel;
	e->iso_resource.bandwidth = bandwidth;

	queue_event(client, &e->event,
		    &e->iso_resource, माप(e->iso_resource), शून्य, 0);

	अगर (मुक्त) अणु
		cancel_delayed_work(&r->work);
		kमुक्त(r->e_alloc);
		kमुक्त(r->e_dealloc);
		kमुक्त(r);
	पूर्ण
 out:
	client_put(client);
पूर्ण

अटल व्योम release_iso_resource(काष्ठा client *client,
				 काष्ठा client_resource *resource)
अणु
	काष्ठा iso_resource *r =
		container_of(resource, काष्ठा iso_resource, resource);

	spin_lock_irq(&client->lock);
	r->toकरो = ISO_RES_DEALLOC;
	schedule_iso_resource(r, 0);
	spin_unlock_irq(&client->lock);
पूर्ण

अटल पूर्णांक init_iso_resource(काष्ठा client *client,
		काष्ठा fw_cdev_allocate_iso_resource *request, पूर्णांक toकरो)
अणु
	काष्ठा iso_resource_event *e1, *e2;
	काष्ठा iso_resource *r;
	पूर्णांक ret;

	अगर ((request->channels == 0 && request->bandwidth == 0) ||
	    request->bandwidth > BANDWIDTH_AVAILABLE_INITIAL)
		वापस -EINVAL;

	r  = kदो_स्मृति(माप(*r), GFP_KERNEL);
	e1 = kदो_स्मृति(माप(*e1), GFP_KERNEL);
	e2 = kदो_स्मृति(माप(*e2), GFP_KERNEL);
	अगर (r == शून्य || e1 == शून्य || e2 == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	INIT_DELAYED_WORK(&r->work, iso_resource_work);
	r->client	= client;
	r->toकरो		= toकरो;
	r->generation	= -1;
	r->channels	= request->channels;
	r->bandwidth	= request->bandwidth;
	r->e_alloc	= e1;
	r->e_dealloc	= e2;

	e1->iso_resource.closure = request->closure;
	e1->iso_resource.type    = FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED;
	e2->iso_resource.closure = request->closure;
	e2->iso_resource.type    = FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED;

	अगर (toकरो == ISO_RES_ALLOC) अणु
		r->resource.release = release_iso_resource;
		ret = add_client_resource(client, &r->resource, GFP_KERNEL);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		r->resource.release = शून्य;
		r->resource.handle = -1;
		schedule_iso_resource(r, 0);
	पूर्ण
	request->handle = r->resource.handle;

	वापस 0;
 fail:
	kमुक्त(r);
	kमुक्त(e1);
	kमुक्त(e2);

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_allocate_iso_resource(काष्ठा client *client,
				       जोड़ ioctl_arg *arg)
अणु
	वापस init_iso_resource(client,
			&arg->allocate_iso_resource, ISO_RES_ALLOC);
पूर्ण

अटल पूर्णांक ioctl_deallocate_iso_resource(काष्ठा client *client,
					 जोड़ ioctl_arg *arg)
अणु
	वापस release_client_resource(client,
			arg->deallocate.handle, release_iso_resource, शून्य);
पूर्ण

अटल पूर्णांक ioctl_allocate_iso_resource_once(काष्ठा client *client,
					    जोड़ ioctl_arg *arg)
अणु
	वापस init_iso_resource(client,
			&arg->allocate_iso_resource, ISO_RES_ALLOC_ONCE);
पूर्ण

अटल पूर्णांक ioctl_deallocate_iso_resource_once(काष्ठा client *client,
					      जोड़ ioctl_arg *arg)
अणु
	वापस init_iso_resource(client,
			&arg->allocate_iso_resource, ISO_RES_DEALLOC_ONCE);
पूर्ण

/*
 * Returns a speed code:  Maximum speed to or from this device,
 * limited by the device's link speed, the local node's link speed,
 * and all PHY port speeds between the two links.
 */
अटल पूर्णांक ioctl_get_speed(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	वापस client->device->max_speed;
पूर्ण

अटल पूर्णांक ioctl_send_broadcast_request(काष्ठा client *client,
					जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_send_request *a = &arg->send_request;

	चयन (a->tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Security policy: Only allow accesses to Units Space. */
	अगर (a->offset < CSR_REGISTER_BASE + CSR_CONFIG_ROM_END)
		वापस -EACCES;

	वापस init_request(client, a, LOCAL_BUS | 0x3f, SCODE_100);
पूर्ण

अटल पूर्णांक ioctl_send_stream_packet(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_send_stream_packet *a = &arg->send_stream_packet;
	काष्ठा fw_cdev_send_request request;
	पूर्णांक dest;

	अगर (a->speed > client->device->card->link_speed ||
	    a->length > 1024 << a->speed)
		वापस -EIO;

	अगर (a->tag > 3 || a->channel > 63 || a->sy > 15)
		वापस -EINVAL;

	dest = fw_stream_packet_destination_id(a->tag, a->channel, a->sy);
	request.tcode		= TCODE_STREAM_DATA;
	request.length		= a->length;
	request.closure		= a->closure;
	request.data		= a->data;
	request.generation	= a->generation;

	वापस init_request(client, &request, dest, a->speed);
पूर्ण

अटल व्योम outbound_phy_packet_callback(काष्ठा fw_packet *packet,
					 काष्ठा fw_card *card, पूर्णांक status)
अणु
	काष्ठा outbound_phy_packet_event *e =
		container_of(packet, काष्ठा outbound_phy_packet_event, p);

	चयन (status) अणु
	/* expected: */
	हाल ACK_COMPLETE:	e->phy_packet.rcode = RCODE_COMPLETE;	अवरोध;
	/* should never happen with PHY packets: */
	हाल ACK_PENDING:	e->phy_packet.rcode = RCODE_COMPLETE;	अवरोध;
	हाल ACK_BUSY_X:
	हाल ACK_BUSY_A:
	हाल ACK_BUSY_B:	e->phy_packet.rcode = RCODE_BUSY;	अवरोध;
	हाल ACK_DATA_ERROR:	e->phy_packet.rcode = RCODE_DATA_ERROR;	अवरोध;
	हाल ACK_TYPE_ERROR:	e->phy_packet.rcode = RCODE_TYPE_ERROR;	अवरोध;
	/* stale generation; cancelled; on certain controllers: no ack */
	शेष:		e->phy_packet.rcode = status;		अवरोध;
	पूर्ण
	e->phy_packet.data[0] = packet->बारtamp;

	queue_event(e->client, &e->event, &e->phy_packet,
		    माप(e->phy_packet) + e->phy_packet.length, शून्य, 0);
	client_put(e->client);
पूर्ण

अटल पूर्णांक ioctl_send_phy_packet(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_send_phy_packet *a = &arg->send_phy_packet;
	काष्ठा fw_card *card = client->device->card;
	काष्ठा outbound_phy_packet_event *e;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	अगर (!client->device->is_local)
		वापस -ENOSYS;

	e = kzalloc(माप(*e) + 4, GFP_KERNEL);
	अगर (e == शून्य)
		वापस -ENOMEM;

	client_get(client);
	e->client		= client;
	e->p.speed		= SCODE_100;
	e->p.generation		= a->generation;
	e->p.header[0]		= TCODE_LINK_INTERNAL << 4;
	e->p.header[1]		= a->data[0];
	e->p.header[2]		= a->data[1];
	e->p.header_length	= 12;
	e->p.callback		= outbound_phy_packet_callback;
	e->phy_packet.closure	= a->closure;
	e->phy_packet.type	= FW_CDEV_EVENT_PHY_PACKET_SENT;
	अगर (is_ping_packet(a->data))
			e->phy_packet.length = 4;

	card->driver->send_request(card, &e->p);

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_receive_phy_packets(काष्ठा client *client, जोड़ ioctl_arg *arg)
अणु
	काष्ठा fw_cdev_receive_phy_packets *a = &arg->receive_phy_packets;
	काष्ठा fw_card *card = client->device->card;

	/* Access policy: Allow this ioctl only on local nodes' device files. */
	अगर (!client->device->is_local)
		वापस -ENOSYS;

	spin_lock_irq(&card->lock);

	list_move_tail(&client->phy_receiver_link, &card->phy_receiver_list);
	client->phy_receiver_closure = a->closure;

	spin_unlock_irq(&card->lock);

	वापस 0;
पूर्ण

व्योम fw_cdev_handle_phy_packet(काष्ठा fw_card *card, काष्ठा fw_packet *p)
अणु
	काष्ठा client *client;
	काष्ठा inbound_phy_packet_event *e;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);

	list_क्रम_each_entry(client, &card->phy_receiver_list, phy_receiver_link) अणु
		e = kदो_स्मृति(माप(*e) + 8, GFP_ATOMIC);
		अगर (e == शून्य)
			अवरोध;

		e->phy_packet.closure	= client->phy_receiver_closure;
		e->phy_packet.type	= FW_CDEV_EVENT_PHY_PACKET_RECEIVED;
		e->phy_packet.rcode	= RCODE_COMPLETE;
		e->phy_packet.length	= 8;
		e->phy_packet.data[0]	= p->header[1];
		e->phy_packet.data[1]	= p->header[2];
		queue_event(client, &e->event,
			    &e->phy_packet, माप(e->phy_packet) + 8, शून्य, 0);
	पूर्ण

	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

अटल पूर्णांक (* स्थिर ioctl_handlers[])(काष्ठा client *, जोड़ ioctl_arg *) = अणु
	[0x00] = ioctl_get_info,
	[0x01] = ioctl_send_request,
	[0x02] = ioctl_allocate,
	[0x03] = ioctl_deallocate,
	[0x04] = ioctl_send_response,
	[0x05] = ioctl_initiate_bus_reset,
	[0x06] = ioctl_add_descriptor,
	[0x07] = ioctl_हटाओ_descriptor,
	[0x08] = ioctl_create_iso_context,
	[0x09] = ioctl_queue_iso,
	[0x0a] = ioctl_start_iso,
	[0x0b] = ioctl_stop_iso,
	[0x0c] = ioctl_get_cycle_समयr,
	[0x0d] = ioctl_allocate_iso_resource,
	[0x0e] = ioctl_deallocate_iso_resource,
	[0x0f] = ioctl_allocate_iso_resource_once,
	[0x10] = ioctl_deallocate_iso_resource_once,
	[0x11] = ioctl_get_speed,
	[0x12] = ioctl_send_broadcast_request,
	[0x13] = ioctl_send_stream_packet,
	[0x14] = ioctl_get_cycle_समयr2,
	[0x15] = ioctl_send_phy_packet,
	[0x16] = ioctl_receive_phy_packets,
	[0x17] = ioctl_set_iso_channels,
	[0x18] = ioctl_flush_iso,
पूर्ण;

अटल पूर्णांक dispatch_ioctl(काष्ठा client *client,
			  अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	जोड़ ioctl_arg buffer;
	पूर्णांक ret;

	अगर (fw_device_is_shutकरोwn(client->device))
		वापस -ENODEV;

	अगर (_IOC_TYPE(cmd) != '#' ||
	    _IOC_NR(cmd) >= ARRAY_SIZE(ioctl_handlers) ||
	    _IOC_SIZE(cmd) > माप(buffer))
		वापस -ENOTTY;

	स_रखो(&buffer, 0, माप(buffer));

	अगर (_IOC_सूची(cmd) & _IOC_WRITE)
		अगर (copy_from_user(&buffer, arg, _IOC_SIZE(cmd)))
			वापस -EFAULT;

	ret = ioctl_handlers[_IOC_NR(cmd)](client, &buffer);
	अगर (ret < 0)
		वापस ret;

	अगर (_IOC_सूची(cmd) & _IOC_READ)
		अगर (copy_to_user(arg, &buffer, _IOC_SIZE(cmd)))
			वापस -EFAULT;

	वापस ret;
पूर्ण

अटल दीर्घ fw_device_op_ioctl(काष्ठा file *file,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस dispatch_ioctl(file->निजी_data, cmd, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक fw_device_op_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा client *client = file->निजी_data;
	अचिन्हित दीर्घ size;
	पूर्णांक page_count, ret;

	अगर (fw_device_is_shutकरोwn(client->device))
		वापस -ENODEV;

	/* FIXME: We could support multiple buffers, but we करोn't. */
	अगर (client->buffer.pages != शून्य)
		वापस -EBUSY;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	अगर (vma->vm_start & ~PAGE_MASK)
		वापस -EINVAL;

	client->vm_start = vma->vm_start;
	size = vma->vm_end - vma->vm_start;
	page_count = size >> PAGE_SHIFT;
	अगर (size & ~PAGE_MASK)
		वापस -EINVAL;

	ret = fw_iso_buffer_alloc(&client->buffer, page_count);
	अगर (ret < 0)
		वापस ret;

	spin_lock_irq(&client->lock);
	अगर (client->iso_context) अणु
		ret = fw_iso_buffer_map_dma(&client->buffer,
				client->device->card,
				iso_dma_direction(client->iso_context));
		client->buffer_is_mapped = (ret == 0);
	पूर्ण
	spin_unlock_irq(&client->lock);
	अगर (ret < 0)
		जाओ fail;

	ret = vm_map_pages_zero(vma, client->buffer.pages,
				client->buffer.page_count);
	अगर (ret < 0)
		जाओ fail;

	वापस 0;
 fail:
	fw_iso_buffer_destroy(&client->buffer, client->device->card);
	वापस ret;
पूर्ण

अटल पूर्णांक is_outbound_transaction_resource(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा client_resource *resource = p;

	वापस resource->release == release_transaction;
पूर्ण

अटल पूर्णांक has_outbound_transactions(काष्ठा client *client)
अणु
	पूर्णांक ret;

	spin_lock_irq(&client->lock);
	ret = idr_क्रम_each(&client->resource_idr,
			   is_outbound_transaction_resource, शून्य);
	spin_unlock_irq(&client->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक shutकरोwn_resource(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा client_resource *resource = p;
	काष्ठा client *client = data;

	resource->release(client, resource);
	client_put(client);

	वापस 0;
पूर्ण

अटल पूर्णांक fw_device_op_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा client *client = file->निजी_data;
	काष्ठा event *event, *next_event;

	spin_lock_irq(&client->device->card->lock);
	list_del(&client->phy_receiver_link);
	spin_unlock_irq(&client->device->card->lock);

	mutex_lock(&client->device->client_list_mutex);
	list_del(&client->link);
	mutex_unlock(&client->device->client_list_mutex);

	अगर (client->iso_context)
		fw_iso_context_destroy(client->iso_context);

	अगर (client->buffer.pages)
		fw_iso_buffer_destroy(&client->buffer, client->device->card);

	/* Freeze client->resource_idr and client->event_list */
	spin_lock_irq(&client->lock);
	client->in_shutकरोwn = true;
	spin_unlock_irq(&client->lock);

	रुको_event(client->tx_flush_रुको, !has_outbound_transactions(client));

	idr_क्रम_each(&client->resource_idr, shutकरोwn_resource, client);
	idr_destroy(&client->resource_idr);

	list_क्रम_each_entry_safe(event, next_event, &client->event_list, link)
		kमुक्त(event);

	client_put(client);

	वापस 0;
पूर्ण

अटल __poll_t fw_device_op_poll(काष्ठा file *file, poll_table * pt)
अणु
	काष्ठा client *client = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &client->रुको, pt);

	अगर (fw_device_is_shutकरोwn(client->device))
		mask |= EPOLLHUP | EPOLLERR;
	अगर (!list_empty(&client->event_list))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

स्थिर काष्ठा file_operations fw_device_ops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.खोलो		= fw_device_op_खोलो,
	.पढ़ो		= fw_device_op_पढ़ो,
	.unlocked_ioctl	= fw_device_op_ioctl,
	.mmap		= fw_device_op_mmap,
	.release	= fw_device_op_release,
	.poll		= fw_device_op_poll,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;
