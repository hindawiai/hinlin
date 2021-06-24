<शैली गुरु>
/******************************************************************************
 * Talks to Xen Store to figure out what devices we have (backend half).
 *
 * Copyright (C) 2005 Rusty Russell, IBM Corporation
 * Copyright (C) 2005 Mike Wray, Hewlett-Packard
 * Copyright (C) 2005, 2006 XenSource Ltd
 * Copyright (C) 2007 Solarflare Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DPRINTK(fmt, ...)				\
	pr_debug("(%s:%d) " fmt "\n",			\
		 __func__, __LINE__, ##__VA_ARGS__)

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <linux/semaphore.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/features.h>

#समावेश "xenbus.h"

/* backend/<type>/<fe-uuid>/<id> => <type>-<fe-करोmid>-<id> */
अटल पूर्णांक backend_bus_id(अक्षर bus_id[XEN_BUS_ID_SIZE], स्थिर अक्षर *nodename)
अणु
	पूर्णांक करोmid, err;
	स्थिर अक्षर *devid, *type, *frontend;
	अचिन्हित पूर्णांक typelen;

	type = म_अक्षर(nodename, '/');
	अगर (!type)
		वापस -EINVAL;
	type++;
	typelen = म_खोज(type, "/");
	अगर (!typelen || type[typelen] != '/')
		वापस -EINVAL;

	devid = म_खोजप(nodename, '/') + 1;

	err = xenbus_gather(XBT_NIL, nodename, "frontend-id", "%i", &करोmid,
			    "frontend", शून्य, &frontend,
			    शून्य);
	अगर (err)
		वापस err;
	अगर (म_माप(frontend) == 0)
		err = -दुस्फल;
	अगर (!err && !xenbus_exists(XBT_NIL, frontend, ""))
		err = -ENOENT;
	kमुक्त(frontend);

	अगर (err)
		वापस err;

	अगर (snम_लिखो(bus_id, XEN_BUS_ID_SIZE, "%.*s-%i-%s",
		     typelen, type, करोmid, devid) >= XEN_BUS_ID_SIZE)
		वापस -ENOSPC;
	वापस 0;
पूर्ण

अटल पूर्णांक xenbus_uevent_backend(काष्ठा device *dev,
				 काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा xenbus_device *xdev;
	काष्ठा xenbus_driver *drv;
	काष्ठा xen_bus_type *bus;

	DPRINTK("");

	अगर (dev == शून्य)
		वापस -ENODEV;

	xdev = to_xenbus_device(dev);
	bus = container_of(xdev->dev.bus, काष्ठा xen_bus_type, bus);

	अगर (add_uevent_var(env, "MODALIAS=xen-backend:%s", xdev->devicetype))
		वापस -ENOMEM;

	/* stuff we want to pass to /sbin/hotplug */
	अगर (add_uevent_var(env, "XENBUS_TYPE=%s", xdev->devicetype))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "XENBUS_PATH=%s", xdev->nodename))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "XENBUS_BASE_PATH=%s", bus->root))
		वापस -ENOMEM;

	अगर (dev->driver) अणु
		drv = to_xenbus_driver(dev->driver);
		अगर (drv && drv->uevent)
			वापस drv->uevent(xdev, env);
	पूर्ण

	वापस 0;
पूर्ण

/* backend/<typename>/<frontend-uuid>/<name> */
अटल पूर्णांक xenbus_probe_backend_unit(काष्ठा xen_bus_type *bus,
				     स्थिर अक्षर *dir,
				     स्थिर अक्षर *type,
				     स्थिर अक्षर *name)
अणु
	अक्षर *nodename;
	पूर्णांक err;

	nodename = kaप्र_लिखो(GFP_KERNEL, "%s/%s", dir, name);
	अगर (!nodename)
		वापस -ENOMEM;

	DPRINTK("%s\n", nodename);

	err = xenbus_probe_node(bus, type, nodename);
	kमुक्त(nodename);
	वापस err;
पूर्ण

/* backend/<typename>/<frontend-करोmid> */
अटल पूर्णांक xenbus_probe_backend(काष्ठा xen_bus_type *bus, स्थिर अक्षर *type,
				स्थिर अक्षर *करोmid)
अणु
	अक्षर *nodename;
	पूर्णांक err = 0;
	अक्षर **dir;
	अचिन्हित पूर्णांक i, dir_n = 0;

	DPRINTK("");

	nodename = kaप्र_लिखो(GFP_KERNEL, "%s/%s/%s", bus->root, type, करोmid);
	अगर (!nodename)
		वापस -ENOMEM;

	dir = xenbus_directory(XBT_NIL, nodename, "", &dir_n);
	अगर (IS_ERR(dir)) अणु
		kमुक्त(nodename);
		वापस PTR_ERR(dir);
	पूर्ण

	क्रम (i = 0; i < dir_n; i++) अणु
		err = xenbus_probe_backend_unit(bus, nodename, type, dir[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	kमुक्त(dir);
	kमुक्त(nodename);
	वापस err;
पूर्ण

अटल bool frontend_will_handle(काष्ठा xenbus_watch *watch,
				 स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	वापस watch->nr_pending == 0;
पूर्ण

अटल व्योम frontend_changed(काष्ठा xenbus_watch *watch,
			     स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	xenbus_otherend_changed(watch, path, token, 0);
पूर्ण

अटल काष्ठा xen_bus_type xenbus_backend = अणु
	.root = "backend",
	.levels = 3,		/* backend/type/<frontend>/<id> */
	.get_bus_id = backend_bus_id,
	.probe = xenbus_probe_backend,
	.otherend_will_handle = frontend_will_handle,
	.otherend_changed = frontend_changed,
	.bus = अणु
		.name		= "xen-backend",
		.match		= xenbus_match,
		.uevent		= xenbus_uevent_backend,
		.probe		= xenbus_dev_probe,
		.हटाओ		= xenbus_dev_हटाओ,
		.dev_groups	= xenbus_dev_groups,
	पूर्ण,
पूर्ण;

अटल व्योम backend_changed(काष्ठा xenbus_watch *watch,
			    स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	DPRINTK("");

	xenbus_dev_changed(path, &xenbus_backend);
पूर्ण

अटल काष्ठा xenbus_watch be_watch = अणु
	.node = "backend",
	.callback = backend_changed,
पूर्ण;

अटल पूर्णांक पढ़ो_frontend_details(काष्ठा xenbus_device *xendev)
अणु
	वापस xenbus_पढ़ो_otherend_details(xendev, "frontend-id", "frontend");
पूर्ण

पूर्णांक xenbus_dev_is_online(काष्ठा xenbus_device *dev)
अणु
	वापस !!xenbus_पढ़ो_अचिन्हित(dev->nodename, "online", 0);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_is_online);

पूर्णांक __xenbus_रेजिस्टर_backend(काष्ठा xenbus_driver *drv, काष्ठा module *owner,
			      स्थिर अक्षर *mod_name)
अणु
	drv->पढ़ो_otherend_details = पढ़ो_frontend_details;

	वापस xenbus_रेजिस्टर_driver_common(drv, &xenbus_backend,
					     owner, mod_name);
पूर्ण
EXPORT_SYMBOL_GPL(__xenbus_रेजिस्टर_backend);

अटल पूर्णांक backend_probe_and_watch(काष्ठा notअगरier_block *notअगरier,
				   अचिन्हित दीर्घ event,
				   व्योम *data)
अणु
	/* Enumerate devices in xenstore and watch क्रम changes. */
	xenbus_probe_devices(&xenbus_backend);
	रेजिस्टर_xenbus_watch(&be_watch);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक backend_reclaim_memory(काष्ठा device *dev, व्योम *data)
अणु
	स्थिर काष्ठा xenbus_driver *drv;
	काष्ठा xenbus_device *xdev;

	अगर (!dev->driver)
		वापस 0;
	drv = to_xenbus_driver(dev->driver);
	अगर (drv && drv->reclaim_memory) अणु
		xdev = to_xenbus_device(dev);
		अगर (करोwn_trylock(&xdev->reclaim_sem))
			वापस 0;
		drv->reclaim_memory(xdev);
		up(&xdev->reclaim_sem);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns 0 always because we are using shrinker to only detect memory
 * pressure.
 */
अटल अचिन्हित दीर्घ backend_shrink_memory_count(काष्ठा shrinker *shrinker,
				काष्ठा shrink_control *sc)
अणु
	bus_क्रम_each_dev(&xenbus_backend.bus, शून्य, शून्य,
			backend_reclaim_memory);
	वापस 0;
पूर्ण

अटल काष्ठा shrinker backend_memory_shrinker = अणु
	.count_objects = backend_shrink_memory_count,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

अटल पूर्णांक __init xenbus_probe_backend_init(व्योम)
अणु
	अटल काष्ठा notअगरier_block xenstore_notअगरier = अणु
		.notअगरier_call = backend_probe_and_watch
	पूर्ण;
	पूर्णांक err;

	DPRINTK("");

	/* Register ourselves with the kernel bus subप्रणाली */
	err = bus_रेजिस्टर(&xenbus_backend.bus);
	अगर (err)
		वापस err;

	रेजिस्टर_xenstore_notअगरier(&xenstore_notअगरier);

	अगर (रेजिस्टर_shrinker(&backend_memory_shrinker))
		pr_warn("shrinker registration failed\n");

	वापस 0;
पूर्ण
subsys_initcall(xenbus_probe_backend_init);
