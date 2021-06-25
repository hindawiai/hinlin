<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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
#समावेश <linux/proc_fs.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/xen.h>

#समावेश <xen/platक्रमm_pci.h>

#समावेश "xenbus.h"



/* device/<type>/<id> => <type>-<id> */
अटल पूर्णांक frontend_bus_id(अक्षर bus_id[XEN_BUS_ID_SIZE], स्थिर अक्षर *nodename)
अणु
	nodename = म_अक्षर(nodename, '/');
	अगर (!nodename || म_माप(nodename + 1) >= XEN_BUS_ID_SIZE) अणु
		pr_warn("bad frontend %s\n", nodename);
		वापस -EINVAL;
	पूर्ण

	strlcpy(bus_id, nodename + 1, XEN_BUS_ID_SIZE);
	अगर (!म_अक्षर(bus_id, '/')) अणु
		pr_warn("bus_id %s no slash\n", bus_id);
		वापस -EINVAL;
	पूर्ण
	*म_अक्षर(bus_id, '/') = '-';
	वापस 0;
पूर्ण

/* device/<typename>/<name> */
अटल पूर्णांक xenbus_probe_frontend(काष्ठा xen_bus_type *bus, स्थिर अक्षर *type,
				 स्थिर अक्षर *name)
अणु
	अक्षर *nodename;
	पूर्णांक err;

	/* ignore console/0 */
	अगर (!म_भेदन(type, "console", 7) && !म_भेदन(name, "0", 1)) अणु
		DPRINTK("Ignoring buggy device entry console/0");
		वापस 0;
	पूर्ण

	nodename = kaप्र_लिखो(GFP_KERNEL, "%s/%s/%s", bus->root, type, name);
	अगर (!nodename)
		वापस -ENOMEM;

	DPRINTK("%s", nodename);

	err = xenbus_probe_node(bus, type, nodename);
	kमुक्त(nodename);
	वापस err;
पूर्ण

अटल पूर्णांक xenbus_uevent_frontend(काष्ठा device *_dev,
				  काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);

	अगर (add_uevent_var(env, "MODALIAS=xen:%s", dev->devicetype))
		वापस -ENOMEM;

	वापस 0;
पूर्ण


अटल व्योम backend_changed(काष्ठा xenbus_watch *watch,
			    स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	xenbus_otherend_changed(watch, path, token, 1);
पूर्ण

अटल व्योम xenbus_frontend_delayed_resume(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा xenbus_device *xdev = container_of(w, काष्ठा xenbus_device, work);

	xenbus_dev_resume(&xdev->dev);
पूर्ण

अटल पूर्णांक xenbus_frontend_dev_resume(काष्ठा device *dev)
अणु
	/*
	 * If xenstored is running in this करोमुख्य, we cannot access the backend
	 * state at the moment, so we need to defer xenbus_dev_resume
	 */
	अगर (xen_store_करोमुख्य_type == XS_LOCAL) अणु
		काष्ठा xenbus_device *xdev = to_xenbus_device(dev);

		schedule_work(&xdev->work);

		वापस 0;
	पूर्ण

	वापस xenbus_dev_resume(dev);
पूर्ण

अटल पूर्णांक xenbus_frontend_dev_probe(काष्ठा device *dev)
अणु
	अगर (xen_store_करोमुख्य_type == XS_LOCAL) अणु
		काष्ठा xenbus_device *xdev = to_xenbus_device(dev);
		INIT_WORK(&xdev->work, xenbus_frontend_delayed_resume);
	पूर्ण

	वापस xenbus_dev_probe(dev);
पूर्ण

अटल व्योम xenbus_frontend_dev_shutकरोwn(काष्ठा device *_dev)
अणु
	काष्ठा xenbus_device *dev = to_xenbus_device(_dev);
	अचिन्हित दीर्घ समयout = 5*HZ;

	DPRINTK("%s", dev->nodename);

	get_device(&dev->dev);
	अगर (dev->state != XenbusStateConnected) अणु
		pr_info("%s: %s: %s != Connected, skipping\n",
			__func__, dev->nodename, xenbus_strstate(dev->state));
		जाओ out;
	पूर्ण
	xenbus_चयन_state(dev, XenbusStateClosing);
	समयout = रुको_क्रम_completion_समयout(&dev->करोwn, समयout);
	अगर (!समयout)
		pr_info("%s: %s timeout closing device\n",
			__func__, dev->nodename);
 out:
	put_device(&dev->dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xenbus_pm_ops = अणु
	.suspend	= xenbus_dev_suspend,
	.resume		= xenbus_frontend_dev_resume,
	.मुक्तze		= xenbus_dev_suspend,
	.thaw		= xenbus_dev_cancel,
	.restore	= xenbus_dev_resume,
पूर्ण;

अटल काष्ठा xen_bus_type xenbus_frontend = अणु
	.root = "device",
	.levels = 2,		/* device/type/<id> */
	.get_bus_id = frontend_bus_id,
	.probe = xenbus_probe_frontend,
	.otherend_changed = backend_changed,
	.bus = अणु
		.name		= "xen",
		.match		= xenbus_match,
		.uevent		= xenbus_uevent_frontend,
		.probe		= xenbus_frontend_dev_probe,
		.हटाओ		= xenbus_dev_हटाओ,
		.shutकरोwn	= xenbus_frontend_dev_shutकरोwn,
		.dev_groups	= xenbus_dev_groups,

		.pm		= &xenbus_pm_ops,
	पूर्ण,
पूर्ण;

अटल व्योम frontend_changed(काष्ठा xenbus_watch *watch,
			     स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	DPRINTK("");

	xenbus_dev_changed(path, &xenbus_frontend);
पूर्ण


/* We watch क्रम devices appearing and vanishing. */
अटल काष्ठा xenbus_watch fe_watch = अणु
	.node = "device",
	.callback = frontend_changed,
पूर्ण;

अटल पूर्णांक पढ़ो_backend_details(काष्ठा xenbus_device *xendev)
अणु
	वापस xenbus_पढ़ो_otherend_details(xendev, "backend-id", "backend");
पूर्ण

अटल पूर्णांक is_device_connecting(काष्ठा device *dev, व्योम *data, bool ignore_nonessential)
अणु
	काष्ठा xenbus_device *xendev = to_xenbus_device(dev);
	काष्ठा device_driver *drv = data;
	काष्ठा xenbus_driver *xendrv;

	/*
	 * A device with no driver will never connect. We care only about
	 * devices which should currently be in the process of connecting.
	 */
	अगर (!dev->driver)
		वापस 0;

	/* Is this search limited to a particular driver? */
	अगर (drv && (dev->driver != drv))
		वापस 0;

	अगर (ignore_nonessential) अणु
		/* With older QEMU, क्रम PVonHVM guests the guest config files
		 * could contain: vfb = [ 'vnc=1, vnclisten=0.0.0.0']
		 * which is nonsensical as there is no PV FB (there can be
		 * a PVKB) running as HVM guest. */

		अगर ((म_भेदन(xendev->nodename, "device/vkbd", 11) == 0))
			वापस 0;

		अगर ((म_भेदन(xendev->nodename, "device/vfb", 10) == 0))
			वापस 0;
	पूर्ण
	xendrv = to_xenbus_driver(dev->driver);
	वापस (xendev->state < XenbusStateConnected ||
		(xendev->state == XenbusStateConnected &&
		 xendrv->is_पढ़ोy && !xendrv->is_पढ़ोy(xendev)));
पूर्ण
अटल पूर्णांक essential_device_connecting(काष्ठा device *dev, व्योम *data)
अणु
	वापस is_device_connecting(dev, data, true /* ignore PV[KBB+FB] */);
पूर्ण
अटल पूर्णांक non_essential_device_connecting(काष्ठा device *dev, व्योम *data)
अणु
	वापस is_device_connecting(dev, data, false);
पूर्ण

अटल पूर्णांक exists_essential_connecting_device(काष्ठा device_driver *drv)
अणु
	वापस bus_क्रम_each_dev(&xenbus_frontend.bus, शून्य, drv,
				essential_device_connecting);
पूर्ण
अटल पूर्णांक exists_non_essential_connecting_device(काष्ठा device_driver *drv)
अणु
	वापस bus_क्रम_each_dev(&xenbus_frontend.bus, शून्य, drv,
				non_essential_device_connecting);
पूर्ण

अटल पूर्णांक prपूर्णांक_device_status(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा xenbus_device *xendev = to_xenbus_device(dev);
	काष्ठा device_driver *drv = data;

	/* Is this operation limited to a particular driver? */
	अगर (drv && (dev->driver != drv))
		वापस 0;

	अगर (!dev->driver) अणु
		/* Inक्रमmation only: is this too noisy? */
		pr_info("Device with no driver: %s\n", xendev->nodename);
	पूर्ण अन्यथा अगर (xendev->state < XenbusStateConnected) अणु
		क्रमागत xenbus_state rstate = XenbusStateUnknown;
		अगर (xendev->otherend)
			rstate = xenbus_पढ़ो_driver_state(xendev->otherend);
		pr_warn("Timeout connecting to device: %s (local state %d, remote state %d)\n",
			xendev->nodename, xendev->state, rstate);
	पूर्ण

	वापस 0;
पूर्ण

/* We only रुको क्रम device setup after most initcalls have run. */
अटल पूर्णांक पढ़ोy_to_रुको_क्रम_devices;

अटल bool रुको_loop(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक max_delay,
		     अचिन्हित पूर्णांक *seconds_रुकोed)
अणु
	अगर (समय_after(jअगरfies, start + (*seconds_रुकोed+5)*HZ)) अणु
		अगर (!*seconds_रुकोed)
			pr_warn("Waiting for devices to initialise: ");
		*seconds_रुकोed += 5;
		pr_cont("%us...", max_delay - *seconds_रुकोed);
		अगर (*seconds_रुकोed == max_delay) अणु
			pr_cont("\n");
			वापस true;
		पूर्ण
	पूर्ण

	schedule_समयout_पूर्णांकerruptible(HZ/10);

	वापस false;
पूर्ण
/*
 * On a 5-minute समयout, रुको क्रम all devices currently configured.  We need
 * to करो this to guarantee that the fileप्रणालीs and / or network devices
 * needed क्रम boot are available, beक्रमe we can allow the boot to proceed.
 *
 * This needs to be on a late_initcall, to happen after the frontend device
 * drivers have been initialised, but beक्रमe the root fs is mounted.
 *
 * A possible improvement here would be to have the tools add a per-device
 * flag to the store entry, indicating whether it is needed at boot समय.
 * This would allow people who knew what they were करोing to accelerate their
 * boot slightly, but of course needs tools or manual पूर्णांकervention to set up
 * those flags correctly.
 */
अटल व्योम रुको_क्रम_devices(काष्ठा xenbus_driver *xendrv)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	काष्ठा device_driver *drv = xendrv ? &xendrv->driver : शून्य;
	अचिन्हित पूर्णांक seconds_रुकोed = 0;

	अगर (!पढ़ोy_to_रुको_क्रम_devices || !xen_करोमुख्य())
		वापस;

	जबतक (exists_non_essential_connecting_device(drv))
		अगर (रुको_loop(start, 30, &seconds_रुकोed))
			अवरोध;

	/* Skips PVKB and PVFB check.*/
	जबतक (exists_essential_connecting_device(drv))
		अगर (रुको_loop(start, 270, &seconds_रुकोed))
			अवरोध;

	अगर (seconds_रुकोed)
		prपूर्णांकk("\n");

	bus_क्रम_each_dev(&xenbus_frontend.bus, शून्य, drv,
			 prपूर्णांक_device_status);
पूर्ण

पूर्णांक __xenbus_रेजिस्टर_frontend(काष्ठा xenbus_driver *drv, काष्ठा module *owner,
			       स्थिर अक्षर *mod_name)
अणु
	पूर्णांक ret;

	drv->पढ़ो_otherend_details = पढ़ो_backend_details;

	ret = xenbus_रेजिस्टर_driver_common(drv, &xenbus_frontend,
					    owner, mod_name);
	अगर (ret)
		वापस ret;

	/* If this driver is loaded as a module रुको क्रम devices to attach. */
	रुको_क्रम_devices(drv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__xenbus_रेजिस्टर_frontend);

अटल DECLARE_WAIT_QUEUE_HEAD(backend_state_wq);
अटल पूर्णांक backend_state;

अटल व्योम xenbus_reset_backend_state_changed(काष्ठा xenbus_watch *w,
					स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	अगर (xenbus_म_पूछो(XBT_NIL, path, "", "%i",
			 &backend_state) != 1)
		backend_state = XenbusStateUnknown;
	prपूर्णांकk(KERN_DEBUG "XENBUS: backend %s %s\n",
	       path, xenbus_strstate(backend_state));
	wake_up(&backend_state_wq);
पूर्ण

अटल व्योम xenbus_reset_रुको_क्रम_backend(अक्षर *be, पूर्णांक expected)
अणु
	दीर्घ समयout;
	समयout = रुको_event_पूर्णांकerruptible_समयout(backend_state_wq,
			backend_state == expected, 5 * HZ);
	अगर (समयout <= 0)
		pr_info("backend %s timed out\n", be);
पूर्ण

/*
 * Reset frontend अगर it is in Connected or Closed state.
 * Wait क्रम backend to catch up.
 * State Connected happens during kdump, Closed after kexec.
 */
अटल व्योम xenbus_reset_frontend(अक्षर *fe, अक्षर *be, पूर्णांक be_state)
अणु
	काष्ठा xenbus_watch be_watch;

	prपूर्णांकk(KERN_DEBUG "XENBUS: backend %s %s\n",
			be, xenbus_strstate(be_state));

	स_रखो(&be_watch, 0, माप(be_watch));
	be_watch.node = kaप्र_लिखो(GFP_NOIO | __GFP_HIGH, "%s/state", be);
	अगर (!be_watch.node)
		वापस;

	be_watch.callback = xenbus_reset_backend_state_changed;
	backend_state = XenbusStateUnknown;

	pr_info("triggering reconnect on %s\n", be);
	रेजिस्टर_xenbus_watch(&be_watch);

	/* fall through to क्रमward backend to state XenbusStateInitialising */
	चयन (be_state) अणु
	हाल XenbusStateConnected:
		xenbus_म_लिखो(XBT_NIL, fe, "state", "%d", XenbusStateClosing);
		xenbus_reset_रुको_क्रम_backend(be, XenbusStateClosing);
		fallthrough;

	हाल XenbusStateClosing:
		xenbus_म_लिखो(XBT_NIL, fe, "state", "%d", XenbusStateClosed);
		xenbus_reset_रुको_क्रम_backend(be, XenbusStateClosed);
		fallthrough;

	हाल XenbusStateClosed:
		xenbus_म_लिखो(XBT_NIL, fe, "state", "%d", XenbusStateInitialising);
		xenbus_reset_रुको_क्रम_backend(be, XenbusStateInitWait);
	पूर्ण

	unरेजिस्टर_xenbus_watch(&be_watch);
	pr_info("reconnect done on %s\n", be);
	kमुक्त(be_watch.node);
पूर्ण

अटल व्योम xenbus_check_frontend(अक्षर *class, अक्षर *dev)
अणु
	पूर्णांक be_state, fe_state, err;
	अक्षर *backend, *frontend;

	frontend = kaप्र_लिखो(GFP_NOIO | __GFP_HIGH, "device/%s/%s", class, dev);
	अगर (!frontend)
		वापस;

	err = xenbus_म_पूछो(XBT_NIL, frontend, "state", "%i", &fe_state);
	अगर (err != 1)
		जाओ out;

	चयन (fe_state) अणु
	हाल XenbusStateConnected:
	हाल XenbusStateClosed:
		prपूर्णांकk(KERN_DEBUG "XENBUS: frontend %s %s\n",
				frontend, xenbus_strstate(fe_state));
		backend = xenbus_पढ़ो(XBT_NIL, frontend, "backend", शून्य);
		अगर (!backend || IS_ERR(backend))
			जाओ out;
		err = xenbus_म_पूछो(XBT_NIL, backend, "state", "%i", &be_state);
		अगर (err == 1)
			xenbus_reset_frontend(frontend, backend, be_state);
		kमुक्त(backend);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	kमुक्त(frontend);
पूर्ण

अटल व्योम xenbus_reset_state(व्योम)
अणु
	अक्षर **devclass, **dev;
	पूर्णांक devclass_n, dev_n;
	पूर्णांक i, j;

	devclass = xenbus_directory(XBT_NIL, "device", "", &devclass_n);
	अगर (IS_ERR(devclass))
		वापस;

	क्रम (i = 0; i < devclass_n; i++) अणु
		dev = xenbus_directory(XBT_NIL, "device", devclass[i], &dev_n);
		अगर (IS_ERR(dev))
			जारी;
		क्रम (j = 0; j < dev_n; j++)
			xenbus_check_frontend(devclass[i], dev[j]);
		kमुक्त(dev);
	पूर्ण
	kमुक्त(devclass);
पूर्ण

अटल पूर्णांक frontend_probe_and_watch(काष्ठा notअगरier_block *notअगरier,
				   अचिन्हित दीर्घ event,
				   व्योम *data)
अणु
	/* reset devices in Connected or Closed state */
	अगर (xen_hvm_करोमुख्य())
		xenbus_reset_state();
	/* Enumerate devices in xenstore and watch क्रम changes. */
	xenbus_probe_devices(&xenbus_frontend);
	रेजिस्टर_xenbus_watch(&fe_watch);

	वापस NOTIFY_DONE;
पूर्ण


अटल पूर्णांक __init xenbus_probe_frontend_init(व्योम)
अणु
	अटल काष्ठा notअगरier_block xenstore_notअगरier = अणु
		.notअगरier_call = frontend_probe_and_watch
	पूर्ण;
	पूर्णांक err;

	DPRINTK("");

	/* Register ourselves with the kernel bus subप्रणाली */
	err = bus_रेजिस्टर(&xenbus_frontend.bus);
	अगर (err)
		वापस err;

	रेजिस्टर_xenstore_notअगरier(&xenstore_notअगरier);

	वापस 0;
पूर्ण
subsys_initcall(xenbus_probe_frontend_init);

#अगर_अघोषित MODULE
अटल पूर्णांक __init boot_रुको_क्रम_devices(व्योम)
अणु
	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	पढ़ोy_to_रुको_क्रम_devices = 1;
	रुको_क्रम_devices(शून्य);
	वापस 0;
पूर्ण

late_initcall(boot_रुको_क्रम_devices);
#पूर्ण_अगर

MODULE_LICENSE("GPL");
