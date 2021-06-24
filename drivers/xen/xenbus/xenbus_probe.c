<शैली गुरु>
/******************************************************************************
 * Talks to Xen Store to figure out what devices we have.
 *
 * Copyright (C) 2005 Rusty Russell, IBM Corporation
 * Copyright (C) 2005 Mike Wray, Hewlett-Packard
 * Copyright (C) 2005, 2006 XenSource Ltd
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
#घोषणा dev_fmt pr_fmt

#घोषणा DPRINTK(fmt, args...)				\
	pr_debug("xenbus_probe (%s:%d) " fmt ".\n",	\
		 __func__, __LINE__, ##args)

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/page.h>

#समावेश <xen/hvm.h>

#समावेश "xenbus.h"


पूर्णांक xen_store_evtchn;
EXPORT_SYMBOL_GPL(xen_store_evtchn);

काष्ठा xenstore_करोमुख्य_पूर्णांकerface *xen_store_पूर्णांकerface;
EXPORT_SYMBOL_GPL(xen_store_पूर्णांकerface);

क्रमागत xenstore_init xen_store_करोमुख्य_type;
EXPORT_SYMBOL_GPL(xen_store_करोमुख्य_type);

अटल अचिन्हित दीर्घ xen_store_gfn;

अटल BLOCKING_NOTIFIER_HEAD(xenstore_chain);

/* If something in array of ids matches this device, वापस it. */
अटल स्थिर काष्ठा xenbus_device_id *
match_device(स्थिर काष्ठा xenbus_device_id *arr, काष्ठा xenbus_device *dev)
अणु
	क्रम (; *arr->devicetype != '\0'; arr++) अणु
		अगर (!म_भेद(arr->devicetype, dev->devicetype))
			वापस arr;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक xenbus_match(काष्ठा device *_dev, काष्ठा device_driver *_drv)
अणु
	काष्ठा xenbus_driver *drv = to_xenbus_driver(_drv);

	अगर (!drv->ids)
		वापस 0;

	वापस match_device(drv->ids, to_xenbus_device(_dev)) != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_match);


अटल व्योम मुक्त_otherend_details(काष्ठा xenbus_device *dev)
अणु
	kमुक्त(dev->otherend);
	dev->otherend = शून्य;
पूर्ण


अटल व्योम मुक्त_otherend_watch(काष्ठा xenbus_device *dev)
अणु
	अगर (dev->otherend_watch.node) अणु
		unरेजिस्टर_xenbus_watch(&dev->otherend_watch);
		kमुक्त(dev->otherend_watch.node);
		dev->otherend_watch.node = शून्य;
	पूर्ण
पूर्ण


अटल पूर्णांक talk_to_otherend(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenbus_driver *drv = to_xenbus_driver(dev->dev.driver);

	मुक्त_otherend_watch(dev);
	मुक्त_otherend_details(dev);

	वापस drv->पढ़ो_otherend_details(dev);
पूर्ण



अटल पूर्णांक watch_otherend(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xen_bus_type *bus =
		container_of(dev->dev.bus, काष्ठा xen_bus_type, bus);

	वापस xenbus_watch_pathfmt(dev, &dev->otherend_watch,
				    bus->otherend_will_handle,
				    bus->otherend_changed,
				    "%s/%s", dev->otherend, "state");
पूर्ण


पूर्णांक xenbus_पढ़ो_otherend_details(काष्ठा xenbus_device *xendev,
				 अक्षर *id_node, अक्षर *path_node)
अणु
	पूर्णांक err = xenbus_gather(XBT_NIL, xendev->nodename,
				id_node, "%i", &xendev->otherend_id,
				path_node, शून्य, &xendev->otherend,
				शून्य);
	अगर (err) अणु
		xenbus_dev_fatal(xendev, err,
				 "reading other end details from %s",
				 xendev->nodename);
		वापस err;
	पूर्ण
	अगर (म_माप(xendev->otherend) == 0 ||
	    !xenbus_exists(XBT_NIL, xendev->otherend, "")) अणु
		xenbus_dev_fatal(xendev, -ENOENT,
				 "unable to read other end from %s.  "
				 "missing or inaccessible.",
				 xendev->nodename);
		मुक्त_otherend_details(xendev);
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_पढ़ो_otherend_details);

व्योम xenbus_otherend_changed(काष्ठा xenbus_watch *watch,
			     स्थिर अक्षर *path, स्थिर अक्षर *token,
			     पूर्णांक ignore_on_shutकरोwn)
अणु
	काष्ठा xenbus_device *dev =
		container_of(watch, काष्ठा xenbus_device, otherend_watch);
	काष्ठा xenbus_driver *drv = to_xenbus_driver(dev->dev.driver);
	क्रमागत xenbus_state state;

	/* Protect us against watches firing on old details when the otherend
	   details change, say immediately after a resume. */
	अगर (!dev->otherend ||
	    म_भेदन(dev->otherend, path, म_माप(dev->otherend))) अणु
		dev_dbg(&dev->dev, "Ignoring watch at %s\n", path);
		वापस;
	पूर्ण

	state = xenbus_पढ़ो_driver_state(dev->otherend);

	dev_dbg(&dev->dev, "state is %d, (%s), %s, %s\n",
		state, xenbus_strstate(state), dev->otherend_watch.node, path);

	/*
	 * Ignore xenbus transitions during shutकरोwn. This prevents us करोing
	 * work that can fail e.g., when the rootfs is gone.
	 */
	अगर (प्रणाली_state > SYSTEM_RUNNING) अणु
		अगर (ignore_on_shutकरोwn && (state == XenbusStateClosing))
			xenbus_frontend_बंदd(dev);
		वापस;
	पूर्ण

	अगर (drv->otherend_changed)
		drv->otherend_changed(dev, state);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_otherend_changed);

#घोषणा XENBUS_SHOW_STAT(name)						\
अटल sमाप_प्रकार show_##name(काष्ठा device *_dev,				\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);		\
									\
	वापस प्र_लिखो(buf, "%d\n", atomic_पढ़ो(&dev->name));		\
पूर्ण									\
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

XENBUS_SHOW_STAT(event_channels);
XENBUS_SHOW_STAT(events);
XENBUS_SHOW_STAT(spurious_events);
XENBUS_SHOW_STAT(jअगरfies_eoi_delayed);

अटल sमाप_प्रकार show_spurious_threshold(काष्ठा device *_dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);

	वापस प्र_लिखो(buf, "%d\n", dev->spurious_threshold);
पूर्ण

अटल sमाप_प्रकार set_spurious_threshold(काष्ठा device *_dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार ret;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	dev->spurious_threshold = val;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(spurious_threshold, 0644, show_spurious_threshold,
		   set_spurious_threshold);

अटल काष्ठा attribute *xenbus_attrs[] = अणु
	&dev_attr_event_channels.attr,
	&dev_attr_events.attr,
	&dev_attr_spurious_events.attr,
	&dev_attr_jअगरfies_eoi_delayed.attr,
	&dev_attr_spurious_threshold.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xenbus_group = अणु
	.name = "xenbus",
	.attrs = xenbus_attrs,
पूर्ण;

पूर्णांक xenbus_dev_probe(काष्ठा device *_dev)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);
	काष्ठा xenbus_driver *drv = to_xenbus_driver(_dev->driver);
	स्थिर काष्ठा xenbus_device_id *id;
	पूर्णांक err;

	DPRINTK("%s", dev->nodename);

	अगर (!drv->probe) अणु
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	id = match_device(drv->ids, dev);
	अगर (!id) अणु
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	err = talk_to_otherend(dev);
	अगर (err) अणु
		dev_warn(&dev->dev, "talk_to_otherend on %s failed.\n",
			 dev->nodename);
		वापस err;
	पूर्ण

	अगर (!try_module_get(drv->driver.owner)) अणु
		dev_warn(&dev->dev, "failed to acquire module reference on '%s'\n",
			 drv->driver.name);
		err = -ESRCH;
		जाओ fail;
	पूर्ण

	करोwn(&dev->reclaim_sem);
	err = drv->probe(dev, id);
	up(&dev->reclaim_sem);
	अगर (err)
		जाओ fail_put;

	err = watch_otherend(dev);
	अगर (err) अणु
		dev_warn(&dev->dev, "watch_otherend on %s failed.\n",
		       dev->nodename);
		वापस err;
	पूर्ण

	dev->spurious_threshold = 1;
	अगर (sysfs_create_group(&dev->dev.kobj, &xenbus_group))
		dev_warn(&dev->dev, "sysfs_create_group on %s failed.\n",
			 dev->nodename);

	वापस 0;
fail_put:
	module_put(drv->driver.owner);
fail:
	xenbus_dev_error(dev, err, "xenbus_dev_probe on %s", dev->nodename);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_probe);

पूर्णांक xenbus_dev_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);
	काष्ठा xenbus_driver *drv = to_xenbus_driver(_dev->driver);

	DPRINTK("%s", dev->nodename);

	sysfs_हटाओ_group(&dev->dev.kobj, &xenbus_group);

	मुक्त_otherend_watch(dev);

	अगर (drv->हटाओ) अणु
		करोwn(&dev->reclaim_sem);
		drv->हटाओ(dev);
		up(&dev->reclaim_sem);
	पूर्ण

	module_put(drv->driver.owner);

	मुक्त_otherend_details(dev);

	/*
	 * If the toolstack has क्रमced the device state to closing then set
	 * the state to बंदd now to allow it to be cleaned up.
	 * Similarly, अगर the driver करोes not support re-bind, set the
	 * बंदd.
	 */
	अगर (!drv->allow_rebind ||
	    xenbus_पढ़ो_driver_state(dev->nodename) == XenbusStateClosing)
		xenbus_चयन_state(dev, XenbusStateClosed);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_हटाओ);

पूर्णांक xenbus_रेजिस्टर_driver_common(काष्ठा xenbus_driver *drv,
				  काष्ठा xen_bus_type *bus,
				  काष्ठा module *owner, स्थिर अक्षर *mod_name)
अणु
	drv->driver.name = drv->name ? drv->name : drv->ids[0].devicetype;
	drv->driver.bus = &bus->bus;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_रेजिस्टर_driver_common);

व्योम xenbus_unरेजिस्टर_driver(काष्ठा xenbus_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_unरेजिस्टर_driver);

काष्ठा xb_find_info अणु
	काष्ठा xenbus_device *dev;
	स्थिर अक्षर *nodename;
पूर्ण;

अटल पूर्णांक cmp_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा xenbus_device *xendev = to_xenbus_device(dev);
	काष्ठा xb_find_info *info = data;

	अगर (!म_भेद(xendev->nodename, info->nodename)) अणु
		info->dev = xendev;
		get_device(dev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xenbus_device *xenbus_device_find(स्थिर अक्षर *nodename,
						काष्ठा bus_type *bus)
अणु
	काष्ठा xb_find_info info = अणु .dev = शून्य, .nodename = nodename पूर्ण;

	bus_क्रम_each_dev(bus, शून्य, &info, cmp_dev);
	वापस info.dev;
पूर्ण

अटल पूर्णांक cleanup_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा xenbus_device *xendev = to_xenbus_device(dev);
	काष्ठा xb_find_info *info = data;
	पूर्णांक len = म_माप(info->nodename);

	DPRINTK("%s", info->nodename);

	/* Match the info->nodename path, or any subdirectory of that path. */
	अगर (म_भेदन(xendev->nodename, info->nodename, len))
		वापस 0;

	/* If the node name is दीर्घer, ensure it really is a subdirectory. */
	अगर ((म_माप(xendev->nodename) > len) && (xendev->nodename[len] != '/'))
		वापस 0;

	info->dev = xendev;
	get_device(dev);
	वापस 1;
पूर्ण

अटल व्योम xenbus_cleanup_devices(स्थिर अक्षर *path, काष्ठा bus_type *bus)
अणु
	काष्ठा xb_find_info info = अणु .nodename = path पूर्ण;

	करो अणु
		info.dev = शून्य;
		bus_क्रम_each_dev(bus, शून्य, &info, cleanup_dev);
		अगर (info.dev) अणु
			device_unरेजिस्टर(&info.dev->dev);
			put_device(&info.dev->dev);
		पूर्ण
	पूर्ण जबतक (info.dev);
पूर्ण

अटल व्योम xenbus_dev_release(काष्ठा device *dev)
अणु
	अगर (dev)
		kमुक्त(to_xenbus_device(dev));
पूर्ण

अटल sमाप_प्रकार nodename_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_xenbus_device(dev)->nodename);
पूर्ण
अटल DEVICE_ATTR_RO(nodename);

अटल sमाप_प्रकार devtype_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_xenbus_device(dev)->devicetype);
पूर्ण
अटल DEVICE_ATTR_RO(devtype);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s:%s\n", dev->bus->name,
		       to_xenbus_device(dev)->devicetype);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n",
			xenbus_strstate(to_xenbus_device(dev)->state));
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल काष्ठा attribute *xenbus_dev_attrs[] = अणु
	&dev_attr_nodename.attr,
	&dev_attr_devtype.attr,
	&dev_attr_modalias.attr,
	&dev_attr_state.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group xenbus_dev_group = अणु
	.attrs = xenbus_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *xenbus_dev_groups[] = अणु
	&xenbus_dev_group,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(xenbus_dev_groups);

पूर्णांक xenbus_probe_node(काष्ठा xen_bus_type *bus,
		      स्थिर अक्षर *type,
		      स्थिर अक्षर *nodename)
अणु
	अक्षर devname[XEN_BUS_ID_SIZE];
	पूर्णांक err;
	काष्ठा xenbus_device *xendev;
	माप_प्रकार stringlen;
	अक्षर *पंचांगpstring;

	क्रमागत xenbus_state state = xenbus_पढ़ो_driver_state(nodename);

	अगर (state != XenbusStateInitialising) अणु
		/* Device is not new, so ignore it.  This can happen अगर a
		   device is going away after चयनing to Closed.  */
		वापस 0;
	पूर्ण

	stringlen = म_माप(nodename) + 1 + म_माप(type) + 1;
	xendev = kzalloc(माप(*xendev) + stringlen, GFP_KERNEL);
	अगर (!xendev)
		वापस -ENOMEM;

	xendev->state = XenbusStateInitialising;

	/* Copy the strings पूर्णांकo the extra space. */

	पंचांगpstring = (अक्षर *)(xendev + 1);
	म_नकल(पंचांगpstring, nodename);
	xendev->nodename = पंचांगpstring;

	पंचांगpstring += म_माप(पंचांगpstring) + 1;
	म_नकल(पंचांगpstring, type);
	xendev->devicetype = पंचांगpstring;
	init_completion(&xendev->करोwn);

	xendev->dev.bus = &bus->bus;
	xendev->dev.release = xenbus_dev_release;

	err = bus->get_bus_id(devname, xendev->nodename);
	अगर (err)
		जाओ fail;

	dev_set_name(&xendev->dev, "%s", devname);
	sema_init(&xendev->reclaim_sem, 1);

	/* Register with generic device framework. */
	err = device_रेजिस्टर(&xendev->dev);
	अगर (err) अणु
		put_device(&xendev->dev);
		xendev = शून्य;
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	kमुक्त(xendev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_probe_node);

अटल पूर्णांक xenbus_probe_device_type(काष्ठा xen_bus_type *bus, स्थिर अक्षर *type)
अणु
	पूर्णांक err = 0;
	अक्षर **dir;
	अचिन्हित पूर्णांक dir_n = 0;
	पूर्णांक i;

	dir = xenbus_directory(XBT_NIL, bus->root, type, &dir_n);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	क्रम (i = 0; i < dir_n; i++) अणु
		err = bus->probe(bus, type, dir[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	kमुक्त(dir);
	वापस err;
पूर्ण

पूर्णांक xenbus_probe_devices(काष्ठा xen_bus_type *bus)
अणु
	पूर्णांक err = 0;
	अक्षर **dir;
	अचिन्हित पूर्णांक i, dir_n;

	dir = xenbus_directory(XBT_NIL, bus->root, "", &dir_n);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	क्रम (i = 0; i < dir_n; i++) अणु
		err = xenbus_probe_device_type(bus, dir[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	kमुक्त(dir);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_probe_devices);

अटल अचिन्हित पूर्णांक अक्षर_count(स्थिर अक्षर *str, अक्षर c)
अणु
	अचिन्हित पूर्णांक i, ret = 0;

	क्रम (i = 0; str[i]; i++)
		अगर (str[i] == c)
			ret++;
	वापस ret;
पूर्ण

अटल पूर्णांक strsep_len(स्थिर अक्षर *str, अक्षर c, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; str[i]; i++)
		अगर (str[i] == c) अणु
			अगर (len == 0)
				वापस i;
			len--;
		पूर्ण
	वापस (len == 0) ? i : -दुस्फल;
पूर्ण

व्योम xenbus_dev_changed(स्थिर अक्षर *node, काष्ठा xen_bus_type *bus)
अणु
	पूर्णांक exists, rootlen;
	काष्ठा xenbus_device *dev;
	अक्षर type[XEN_BUS_ID_SIZE];
	स्थिर अक्षर *p, *root;

	अगर (अक्षर_count(node, '/') < 2)
		वापस;

	exists = xenbus_exists(XBT_NIL, node, "");
	अगर (!exists) अणु
		xenbus_cleanup_devices(node, &bus->bus);
		वापस;
	पूर्ण

	/* backend/<type>/... or device/<type>/... */
	p = म_अक्षर(node, '/') + 1;
	snम_लिखो(type, XEN_BUS_ID_SIZE, "%.*s", (पूर्णांक)म_खोज(p, "/"), p);
	type[XEN_BUS_ID_SIZE-1] = '\0';

	rootlen = strsep_len(node, '/', bus->levels);
	अगर (rootlen < 0)
		वापस;
	root = kaप्र_लिखो(GFP_KERNEL, "%.*s", rootlen, node);
	अगर (!root)
		वापस;

	dev = xenbus_device_find(root, &bus->bus);
	अगर (!dev)
		xenbus_probe_node(bus, type, root);
	अन्यथा
		put_device(&dev->dev);

	kमुक्त(root);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_changed);

पूर्णांक xenbus_dev_suspend(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा xenbus_driver *drv;
	काष्ठा xenbus_device *xdev
		= container_of(dev, काष्ठा xenbus_device, dev);

	DPRINTK("%s", xdev->nodename);

	अगर (dev->driver == शून्य)
		वापस 0;
	drv = to_xenbus_driver(dev->driver);
	अगर (drv->suspend)
		err = drv->suspend(xdev);
	अगर (err)
		dev_warn(dev, "suspend failed: %i\n", err);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_suspend);

पूर्णांक xenbus_dev_resume(काष्ठा device *dev)
अणु
	पूर्णांक err;
	काष्ठा xenbus_driver *drv;
	काष्ठा xenbus_device *xdev
		= container_of(dev, काष्ठा xenbus_device, dev);

	DPRINTK("%s", xdev->nodename);

	अगर (dev->driver == शून्य)
		वापस 0;
	drv = to_xenbus_driver(dev->driver);
	err = talk_to_otherend(xdev);
	अगर (err) अणु
		dev_warn(dev, "resume (talk_to_otherend) failed: %i\n", err);
		वापस err;
	पूर्ण

	xdev->state = XenbusStateInitialising;

	अगर (drv->resume) अणु
		err = drv->resume(xdev);
		अगर (err) अणु
			dev_warn(dev, "resume failed: %i\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	err = watch_otherend(xdev);
	अगर (err) अणु
		dev_warn(dev, "resume (watch_otherend) failed: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_resume);

पूर्णांक xenbus_dev_cancel(काष्ठा device *dev)
अणु
	/* Do nothing */
	DPRINTK("cancel");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_cancel);

/* A flag to determine अगर xenstored is 'ready' (i.e. has started) */
पूर्णांक xenstored_पढ़ोy;


पूर्णांक रेजिस्टर_xenstore_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret = 0;

	अगर (xenstored_पढ़ोy > 0)
		ret = nb->notअगरier_call(nb, 0, शून्य);
	अन्यथा
		blocking_notअगरier_chain_रेजिस्टर(&xenstore_chain, nb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_xenstore_notअगरier);

व्योम unरेजिस्टर_xenstore_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&xenstore_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_xenstore_notअगरier);

अटल व्योम xenbus_probe(व्योम)
अणु
	xenstored_पढ़ोy = 1;

	/*
	 * In the HVM हाल, xenbus_init() deferred its call to
	 * xs_init() in हाल callbacks were not operational yet.
	 * So करो it now.
	 */
	अगर (xen_store_करोमुख्य_type == XS_HVM)
		xs_init();

	/* Notअगरy others that xenstore is up */
	blocking_notअगरier_call_chain(&xenstore_chain, 0, शून्य);
पूर्ण

/*
 * Returns true when XenStore init must be deferred in order to
 * allow the PCI platक्रमm device to be initialised, beक्रमe we
 * can actually have event channel पूर्णांकerrupts working.
 */
अटल bool xs_hvm_defer_init_क्रम_callback(व्योम)
अणु
#अगर_घोषित CONFIG_XEN_PVHVM
	वापस xen_store_करोमुख्य_type == XS_HVM &&
		!xen_have_vector_callback;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक xenbus_probe_thपढ़ो(व्योम *unused)
अणु
	DEFINE_WAIT(w);

	/*
	 * We actually just want to रुको क्रम *any* trigger of xb_रुकोq,
	 * and run xenbus_probe() the moment it occurs.
	 */
	prepare_to_रुको(&xb_रुकोq, &w, TASK_INTERRUPTIBLE);
	schedule();
	finish_रुको(&xb_रुकोq, &w);

	DPRINTK("probing");
	xenbus_probe();
	वापस 0;
पूर्ण

अटल पूर्णांक __init xenbus_probe_initcall(व्योम)
अणु
	/*
	 * Probe XenBus here in the XS_PV हाल, and also XS_HVM unless we
	 * need to रुको क्रम the platक्रमm PCI device to come up.
	 */
	अगर (xen_store_करोमुख्य_type == XS_PV ||
	    (xen_store_करोमुख्य_type == XS_HVM &&
	     !xs_hvm_defer_init_क्रम_callback()))
		xenbus_probe();

	/*
	 * For XS_LOCAL, spawn a thपढ़ो which will रुको क्रम xenstored
	 * or a xenstore-stubकरोm to be started, then probe. It will be
	 * triggered when communication starts happening, by रुकोing
	 * on xb_रुकोq.
	 */
	अगर (xen_store_करोमुख्य_type == XS_LOCAL) अणु
		काष्ठा task_काष्ठा *probe_task;

		probe_task = kthपढ़ो_run(xenbus_probe_thपढ़ो, शून्य,
					 "xenbus_probe");
		अगर (IS_ERR(probe_task))
			वापस PTR_ERR(probe_task);
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(xenbus_probe_initcall);

पूर्णांक xen_set_callback_via(uपूर्णांक64_t via)
अणु
	काष्ठा xen_hvm_param a;
	पूर्णांक ret;

	a.करोmid = DOMID_SELF;
	a.index = HVM_PARAM_CALLBACK_IRQ;
	a.value = via;

	ret = HYPERVISOR_hvm_op(HVMOP_set_param, &a);
	अगर (ret)
		वापस ret;

	/*
	 * If xenbus_probe_initcall() deferred the xenbus_probe()
	 * due to the callback not functioning yet, we can करो it now.
	 */
	अगर (!xenstored_पढ़ोy && xs_hvm_defer_init_क्रम_callback())
		xenbus_probe();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xen_set_callback_via);

/* Set up event channel क्रम xenstored which is run as a local process
 * (this is normally used only in करोm0)
 */
अटल पूर्णांक __init xenstored_local_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;
	अचिन्हित दीर्घ page = 0;
	काष्ठा evtchn_alloc_unbound alloc_unbound;

	/* Allocate Xenstore page */
	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		जाओ out_err;

	xen_store_gfn = virt_to_gfn((व्योम *)page);

	/* Next allocate a local port which xenstored can bind to */
	alloc_unbound.करोm        = DOMID_SELF;
	alloc_unbound.remote_करोm = DOMID_SELF;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound,
					  &alloc_unbound);
	अगर (err == -ENOSYS)
		जाओ out_err;

	BUG_ON(err);
	xen_store_evtchn = alloc_unbound.port;

	वापस 0;

 out_err:
	अगर (page != 0)
		मुक्त_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक xenbus_resume_cb(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक err = 0;

	अगर (xen_hvm_करोमुख्य()) अणु
		uपूर्णांक64_t v = 0;

		err = hvm_get_parameter(HVM_PARAM_STORE_EVTCHN, &v);
		अगर (!err && v)
			xen_store_evtchn = v;
		अन्यथा
			pr_warn("Cannot update xenstore event channel: %d\n",
				err);
	पूर्ण अन्यथा
		xen_store_evtchn = xen_start_info->store_evtchn;

	वापस err;
पूर्ण

अटल काष्ठा notअगरier_block xenbus_resume_nb = अणु
	.notअगरier_call = xenbus_resume_cb,
पूर्ण;

अटल पूर्णांक __init xenbus_init(व्योम)
अणु
	पूर्णांक err = 0;
	uपूर्णांक64_t v = 0;
	xen_store_करोमुख्य_type = XS_UNKNOWN;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	xenbus_ring_ops_init();

	अगर (xen_pv_करोमुख्य())
		xen_store_करोमुख्य_type = XS_PV;
	अगर (xen_hvm_करोमुख्य())
		xen_store_करोमुख्य_type = XS_HVM;
	अगर (xen_hvm_करोमुख्य() && xen_initial_करोमुख्य())
		xen_store_करोमुख्य_type = XS_LOCAL;
	अगर (xen_pv_करोमुख्य() && !xen_start_info->store_evtchn)
		xen_store_करोमुख्य_type = XS_LOCAL;
	अगर (xen_pv_करोमुख्य() && xen_start_info->store_evtchn)
		xenstored_पढ़ोy = 1;

	चयन (xen_store_करोमुख्य_type) अणु
	हाल XS_LOCAL:
		err = xenstored_local_init();
		अगर (err)
			जाओ out_error;
		xen_store_पूर्णांकerface = gfn_to_virt(xen_store_gfn);
		अवरोध;
	हाल XS_PV:
		xen_store_evtchn = xen_start_info->store_evtchn;
		xen_store_gfn = xen_start_info->store_mfn;
		xen_store_पूर्णांकerface = gfn_to_virt(xen_store_gfn);
		अवरोध;
	हाल XS_HVM:
		err = hvm_get_parameter(HVM_PARAM_STORE_EVTCHN, &v);
		अगर (err)
			जाओ out_error;
		xen_store_evtchn = (पूर्णांक)v;
		err = hvm_get_parameter(HVM_PARAM_STORE_PFN, &v);
		अगर (err)
			जाओ out_error;
		xen_store_gfn = (अचिन्हित दीर्घ)v;
		xen_store_पूर्णांकerface =
			xen_remap(xen_store_gfn << XEN_PAGE_SHIFT,
				  XEN_PAGE_SIZE);
		अवरोध;
	शेष:
		pr_warn("Xenstore state unknown\n");
		अवरोध;
	पूर्ण

	/*
	 * HVM करोमुख्यs may not have a functional callback yet. In that
	 * हाल let xs_init() be called from xenbus_probe(), which will
	 * get invoked at an appropriate समय.
	 */
	अगर (xen_store_करोमुख्य_type != XS_HVM) अणु
		err = xs_init();
		अगर (err) अणु
			pr_warn("Error initializing xenstore comms: %i\n", err);
			जाओ out_error;
		पूर्ण
	पूर्ण

	अगर ((xen_store_करोमुख्य_type != XS_LOCAL) &&
	    (xen_store_करोमुख्य_type != XS_UNKNOWN))
		xen_resume_notअगरier_रेजिस्टर(&xenbus_resume_nb);

#अगर_घोषित CONFIG_XEN_COMPAT_XENFS
	/*
	 * Create xenfs mountpoपूर्णांक in /proc क्रम compatibility with
	 * utilities that expect to find "xenbus" under "/proc/xen".
	 */
	proc_create_mount_poपूर्णांक("xen");
#पूर्ण_अगर

out_error:
	वापस err;
पूर्ण

postcore_initcall(xenbus_init);

MODULE_LICENSE("GPL");
