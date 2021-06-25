<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2019, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/uverbs_std_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "rdma_core.h"
#समावेश "uverbs.h"

अटल पूर्णांक UVERBS_HANDLER(UVERBS_METHOD_ASYNC_EVENT_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj =
		uverbs_attr_get_uobject(attrs, UVERBS_METHOD_ASYNC_EVENT_ALLOC);

	ib_uverbs_init_async_event_file(
		container_of(uobj, काष्ठा ib_uverbs_async_event_file, uobj));
	वापस 0;
पूर्ण

अटल व्योम uverbs_async_event_destroy_uobj(काष्ठा ib_uobject *uobj,
					    क्रमागत rdma_हटाओ_reason why)
अणु
	काष्ठा ib_uverbs_async_event_file *event_file =
		container_of(uobj, काष्ठा ib_uverbs_async_event_file, uobj);

	ib_unरेजिस्टर_event_handler(&event_file->event_handler);

	अगर (why == RDMA_REMOVE_DRIVER_REMOVE)
		ib_uverbs_async_handler(event_file, 0, IB_EVENT_DEVICE_FATAL,
					शून्य, शून्य);
पूर्ण

पूर्णांक uverbs_async_event_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ib_uverbs_async_event_file *event_file;
	काष्ठा ib_uobject *uobj = filp->निजी_data;
	पूर्णांक ret;

	अगर (!uobj)
		वापस uverbs_uobject_fd_release(inode, filp);

	event_file =
		container_of(uobj, काष्ठा ib_uverbs_async_event_file, uobj);

	/*
	 * The async event FD has to deliver IB_EVENT_DEVICE_FATAL even after
	 * disassociation, so cleaning the event list must only happen after
	 * release. The user knows it has reached the end of the event stream
	 * when it sees IB_EVENT_DEVICE_FATAL.
	 */
	uverbs_uobject_get(uobj);
	ret = uverbs_uobject_fd_release(inode, filp);
	ib_uverbs_मुक्त_event_queue(&event_file->ev_queue);
	uverbs_uobject_put(uobj);
	वापस ret;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	UVERBS_METHOD_ASYNC_EVENT_ALLOC,
	UVERBS_ATTR_FD(UVERBS_ATTR_ASYNC_EVENT_ALLOC_FD_HANDLE,
		       UVERBS_OBJECT_ASYNC_EVENT,
		       UVERBS_ACCESS_NEW,
		       UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(
	UVERBS_OBJECT_ASYNC_EVENT,
	UVERBS_TYPE_ALLOC_FD(माप(काष्ठा ib_uverbs_async_event_file),
			     uverbs_async_event_destroy_uobj,
			     &uverbs_async_event_fops,
			     "[infinibandevent]",
			     O_RDONLY),
	&UVERBS_METHOD(UVERBS_METHOD_ASYNC_EVENT_ALLOC));

स्थिर काष्ठा uapi_definition uverbs_def_obj_async_fd[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(UVERBS_OBJECT_ASYNC_EVENT),
	अणुपूर्ण
पूर्ण;
