<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Host Device
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>

#समावेश "greybus_trace.h"

EXPORT_TRACEPOINT_SYMBOL_GPL(gb_hd_create);
EXPORT_TRACEPOINT_SYMBOL_GPL(gb_hd_release);
EXPORT_TRACEPOINT_SYMBOL_GPL(gb_hd_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(gb_hd_del);
EXPORT_TRACEPOINT_SYMBOL_GPL(gb_hd_in);
EXPORT_TRACEPOINT_SYMBOL_GPL(gb_message_submit);

अटल काष्ठा ida gb_hd_bus_id_map;

पूर्णांक gb_hd_output(काष्ठा gb_host_device *hd, व्योम *req, u16 size, u8 cmd,
		 bool async)
अणु
	अगर (!hd || !hd->driver || !hd->driver->output)
		वापस -EINVAL;
	वापस hd->driver->output(hd, req, size, cmd, async);
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_output);

अटल sमाप_प्रकार bus_id_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_host_device *hd = to_gb_host_device(dev);

	वापस प्र_लिखो(buf, "%d\n", hd->bus_id);
पूर्ण
अटल DEVICE_ATTR_RO(bus_id);

अटल काष्ठा attribute *bus_attrs[] = अणु
	&dev_attr_bus_id.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(bus);

पूर्णांक gb_hd_cport_reserve(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा ida *id_map = &hd->cport_id_map;
	पूर्णांक ret;

	ret = ida_simple_get(id_map, cport_id, cport_id + 1, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(&hd->dev, "failed to reserve cport %u\n", cport_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_cport_reserve);

व्योम gb_hd_cport_release_reserved(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा ida *id_map = &hd->cport_id_map;

	ida_simple_हटाओ(id_map, cport_id);
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_cport_release_reserved);

/* Locking: Caller guarantees serialisation */
पूर्णांक gb_hd_cport_allocate(काष्ठा gb_host_device *hd, पूर्णांक cport_id,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा ida *id_map = &hd->cport_id_map;
	पूर्णांक ida_start, ida_end;

	अगर (hd->driver->cport_allocate)
		वापस hd->driver->cport_allocate(hd, cport_id, flags);

	अगर (cport_id < 0) अणु
		ida_start = 0;
		ida_end = hd->num_cports;
	पूर्ण अन्यथा अगर (cport_id < hd->num_cports) अणु
		ida_start = cport_id;
		ida_end = cport_id + 1;
	पूर्ण अन्यथा अणु
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		वापस -EINVAL;
	पूर्ण

	वापस ida_simple_get(id_map, ida_start, ida_end, GFP_KERNEL);
पूर्ण

/* Locking: Caller guarantees serialisation */
व्योम gb_hd_cport_release(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	अगर (hd->driver->cport_release) अणु
		hd->driver->cport_release(hd, cport_id);
		वापस;
	पूर्ण

	ida_simple_हटाओ(&hd->cport_id_map, cport_id);
पूर्ण

अटल व्योम gb_hd_release(काष्ठा device *dev)
अणु
	काष्ठा gb_host_device *hd = to_gb_host_device(dev);

	trace_gb_hd_release(hd);

	अगर (hd->svc)
		gb_svc_put(hd->svc);
	ida_simple_हटाओ(&gb_hd_bus_id_map, hd->bus_id);
	ida_destroy(&hd->cport_id_map);
	kमुक्त(hd);
पूर्ण

काष्ठा device_type greybus_hd_type = अणु
	.name		= "greybus_host_device",
	.release	= gb_hd_release,
पूर्ण;

काष्ठा gb_host_device *gb_hd_create(काष्ठा gb_hd_driver *driver,
				    काष्ठा device *parent,
				    माप_प्रकार buffer_size_max,
				    माप_प्रकार num_cports)
अणु
	काष्ठा gb_host_device *hd;
	पूर्णांक ret;

	/*
	 * Validate that the driver implements all of the callbacks
	 * so that we करोn't have to every समय we make them.
	 */
	अगर ((!driver->message_send) || (!driver->message_cancel)) अणु
		dev_err(parent, "mandatory hd-callbacks missing\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (buffer_size_max < GB_OPERATION_MESSAGE_SIZE_MIN) अणु
		dev_err(parent, "greybus host-device buffers too small\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (num_cports == 0 || num_cports > CPORT_ID_MAX + 1) अणु
		dev_err(parent, "Invalid number of CPorts: %zu\n", num_cports);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Make sure to never allocate messages larger than what the Greybus
	 * protocol supports.
	 */
	अगर (buffer_size_max > GB_OPERATION_MESSAGE_SIZE_MAX) अणु
		dev_warn(parent, "limiting buffer size to %u\n",
			 GB_OPERATION_MESSAGE_SIZE_MAX);
		buffer_size_max = GB_OPERATION_MESSAGE_SIZE_MAX;
	पूर्ण

	hd = kzalloc(माप(*hd) + driver->hd_priv_size, GFP_KERNEL);
	अगर (!hd)
		वापस ERR_PTR(-ENOMEM);

	ret = ida_simple_get(&gb_hd_bus_id_map, 1, 0, GFP_KERNEL);
	अगर (ret < 0) अणु
		kमुक्त(hd);
		वापस ERR_PTR(ret);
	पूर्ण
	hd->bus_id = ret;

	hd->driver = driver;
	INIT_LIST_HEAD(&hd->modules);
	INIT_LIST_HEAD(&hd->connections);
	ida_init(&hd->cport_id_map);
	hd->buffer_size_max = buffer_size_max;
	hd->num_cports = num_cports;

	hd->dev.parent = parent;
	hd->dev.bus = &greybus_bus_type;
	hd->dev.type = &greybus_hd_type;
	hd->dev.groups = bus_groups;
	hd->dev.dma_mask = hd->dev.parent->dma_mask;
	device_initialize(&hd->dev);
	dev_set_name(&hd->dev, "greybus%d", hd->bus_id);

	trace_gb_hd_create(hd);

	hd->svc = gb_svc_create(hd);
	अगर (!hd->svc) अणु
		dev_err(&hd->dev, "failed to create svc\n");
		put_device(&hd->dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस hd;
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_create);

पूर्णांक gb_hd_add(काष्ठा gb_host_device *hd)
अणु
	पूर्णांक ret;

	ret = device_add(&hd->dev);
	अगर (ret)
		वापस ret;

	ret = gb_svc_add(hd->svc);
	अगर (ret) अणु
		device_del(&hd->dev);
		वापस ret;
	पूर्ण

	trace_gb_hd_add(hd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_add);

व्योम gb_hd_del(काष्ठा gb_host_device *hd)
अणु
	trace_gb_hd_del(hd);

	/*
	 * Tear करोwn the svc and flush any on-going hotplug processing beक्रमe
	 * removing the reमुख्यing पूर्णांकerfaces.
	 */
	gb_svc_del(hd->svc);

	device_del(&hd->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_del);

व्योम gb_hd_shutकरोwn(काष्ठा gb_host_device *hd)
अणु
	gb_svc_del(hd->svc);
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_shutकरोwn);

व्योम gb_hd_put(काष्ठा gb_host_device *hd)
अणु
	put_device(&hd->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gb_hd_put);

पूर्णांक __init gb_hd_init(व्योम)
अणु
	ida_init(&gb_hd_bus_id_map);

	वापस 0;
पूर्ण

व्योम gb_hd_निकास(व्योम)
अणु
	ida_destroy(&gb_hd_bus_id_map);
पूर्ण
