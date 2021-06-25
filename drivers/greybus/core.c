<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus "Core"
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा CREATE_TRACE_POINTS
#समावेश <linux/greybus.h>
#समावेश "greybus_trace.h"

#घोषणा GB_BUNDLE_AUTOSUSPEND_MS	3000

/* Allow greybus to be disabled at boot अगर needed */
अटल bool nogreybus;
#अगर_घोषित MODULE
module_param(nogreybus, bool, 0444);
#अन्यथा
core_param(nogreybus, nogreybus, bool, 0444);
#पूर्ण_अगर
पूर्णांक greybus_disabled(व्योम)
अणु
	वापस nogreybus;
पूर्ण
EXPORT_SYMBOL_GPL(greybus_disabled);

अटल bool greybus_match_one_id(काष्ठा gb_bundle *bundle,
				 स्थिर काष्ठा greybus_bundle_id *id)
अणु
	अगर ((id->match_flags & GREYBUS_ID_MATCH_VENDOR) &&
	    (id->venकरोr != bundle->पूर्णांकf->venकरोr_id))
		वापस false;

	अगर ((id->match_flags & GREYBUS_ID_MATCH_PRODUCT) &&
	    (id->product != bundle->पूर्णांकf->product_id))
		वापस false;

	अगर ((id->match_flags & GREYBUS_ID_MATCH_CLASS) &&
	    (id->class != bundle->class))
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id *
greybus_match_id(काष्ठा gb_bundle *bundle, स्थिर काष्ठा greybus_bundle_id *id)
अणु
	अगर (!id)
		वापस शून्य;

	क्रम (; id->venकरोr || id->product || id->class || id->driver_info;
									id++) अणु
		अगर (greybus_match_one_id(bundle, id))
			वापस id;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक greybus_match_device(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा greybus_driver *driver = to_greybus_driver(drv);
	काष्ठा gb_bundle *bundle;
	स्थिर काष्ठा greybus_bundle_id *id;

	अगर (!is_gb_bundle(dev))
		वापस 0;

	bundle = to_gb_bundle(dev);

	id = greybus_match_id(bundle, driver->id_table);
	अगर (id)
		वापस 1;
	/* FIXME - Dynamic ids? */
	वापस 0;
पूर्ण

अटल पूर्णांक greybus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा gb_host_device *hd;
	काष्ठा gb_module *module = शून्य;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = शून्य;
	काष्ठा gb_control *control = शून्य;
	काष्ठा gb_bundle *bundle = शून्य;
	काष्ठा gb_svc *svc = शून्य;

	अगर (is_gb_host_device(dev)) अणु
		hd = to_gb_host_device(dev);
	पूर्ण अन्यथा अगर (is_gb_module(dev)) अणु
		module = to_gb_module(dev);
		hd = module->hd;
	पूर्ण अन्यथा अगर (is_gb_पूर्णांकerface(dev)) अणु
		पूर्णांकf = to_gb_पूर्णांकerface(dev);
		module = पूर्णांकf->module;
		hd = पूर्णांकf->hd;
	पूर्ण अन्यथा अगर (is_gb_control(dev)) अणु
		control = to_gb_control(dev);
		पूर्णांकf = control->पूर्णांकf;
		module = पूर्णांकf->module;
		hd = पूर्णांकf->hd;
	पूर्ण अन्यथा अगर (is_gb_bundle(dev)) अणु
		bundle = to_gb_bundle(dev);
		पूर्णांकf = bundle->पूर्णांकf;
		module = पूर्णांकf->module;
		hd = पूर्णांकf->hd;
	पूर्ण अन्यथा अगर (is_gb_svc(dev)) अणु
		svc = to_gb_svc(dev);
		hd = svc->hd;
	पूर्ण अन्यथा अणु
		dev_WARN(dev, "uevent for unknown greybus device \"type\"!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (add_uevent_var(env, "BUS=%u", hd->bus_id))
		वापस -ENOMEM;

	अगर (module) अणु
		अगर (add_uevent_var(env, "MODULE=%u", module->module_id))
			वापस -ENOMEM;
	पूर्ण

	अगर (पूर्णांकf) अणु
		अगर (add_uevent_var(env, "INTERFACE=%u", पूर्णांकf->पूर्णांकerface_id))
			वापस -ENOMEM;
		अगर (add_uevent_var(env, "GREYBUS_ID=%08x/%08x",
				   पूर्णांकf->venकरोr_id, पूर्णांकf->product_id))
			वापस -ENOMEM;
	पूर्ण

	अगर (bundle) अणु
		// FIXME
		// add a uevent that can "load" a bundle type
		// This is what we need to bind a driver to so use the info
		// in gmod here as well

		अगर (add_uevent_var(env, "BUNDLE=%u", bundle->id))
			वापस -ENOMEM;
		अगर (add_uevent_var(env, "BUNDLE_CLASS=%02x", bundle->class))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम greybus_shutकरोwn(काष्ठा device *dev)
अणु
	अगर (is_gb_host_device(dev)) अणु
		काष्ठा gb_host_device *hd;

		hd = to_gb_host_device(dev);
		gb_hd_shutकरोwn(hd);
	पूर्ण
पूर्ण

काष्ठा bus_type greybus_bus_type = अणु
	.name =		"greybus",
	.match =	greybus_match_device,
	.uevent =	greybus_uevent,
	.shutकरोwn =	greybus_shutकरोwn,
पूर्ण;

अटल पूर्णांक greybus_probe(काष्ठा device *dev)
अणु
	काष्ठा greybus_driver *driver = to_greybus_driver(dev->driver);
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	स्थिर काष्ठा greybus_bundle_id *id;
	पूर्णांक retval;

	/* match id */
	id = greybus_match_id(bundle, driver->id_table);
	अगर (!id)
		वापस -ENODEV;

	retval = pm_runसमय_get_sync(&bundle->पूर्णांकf->dev);
	अगर (retval < 0) अणु
		pm_runसमय_put_noidle(&bundle->पूर्णांकf->dev);
		वापस retval;
	पूर्ण

	retval = gb_control_bundle_activate(bundle->पूर्णांकf->control, bundle->id);
	अगर (retval) अणु
		pm_runसमय_put(&bundle->पूर्णांकf->dev);
		वापस retval;
	पूर्ण

	/*
	 * Unbound bundle devices are always deactivated. During probe, the
	 * Runसमय PM is set to enabled and active and the usage count is
	 * incremented. If the driver supports runसमय PM, it should call
	 * pm_runसमय_put() in its probe routine and pm_runसमय_get_sync()
	 * in हटाओ routine.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, GB_BUNDLE_AUTOSUSPEND_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	retval = driver->probe(bundle, id);
	अगर (retval) अणु
		/*
		 * Catch buggy drivers that fail to destroy their connections.
		 */
		WARN_ON(!list_empty(&bundle->connections));

		gb_control_bundle_deactivate(bundle->पूर्णांकf->control, bundle->id);

		pm_runसमय_disable(dev);
		pm_runसमय_set_suspended(dev);
		pm_runसमय_put_noidle(dev);
		pm_runसमय_करोnt_use_स्वतःsuspend(dev);
		pm_runसमय_put(&bundle->पूर्णांकf->dev);

		वापस retval;
	पूर्ण

	pm_runसमय_put(&bundle->पूर्णांकf->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक greybus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा greybus_driver *driver = to_greybus_driver(dev->driver);
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	काष्ठा gb_connection *connection;
	पूर्णांक retval;

	retval = pm_runसमय_get_sync(dev);
	अगर (retval < 0)
		dev_err(dev, "failed to resume bundle: %d\n", retval);

	/*
	 * Disable (non-offloaded) connections early in हाल the पूर्णांकerface is
	 * alपढ़ोy gone to aव्योम unceccessary operation समयouts during
	 * driver disconnect. Otherwise, only disable incoming requests.
	 */
	list_क्रम_each_entry(connection, &bundle->connections, bundle_links) अणु
		अगर (gb_connection_is_offloaded(connection))
			जारी;

		अगर (bundle->पूर्णांकf->disconnected)
			gb_connection_disable_क्रमced(connection);
		अन्यथा
			gb_connection_disable_rx(connection);
	पूर्ण

	driver->disconnect(bundle);

	/* Catch buggy drivers that fail to destroy their connections. */
	WARN_ON(!list_empty(&bundle->connections));

	अगर (!bundle->पूर्णांकf->disconnected)
		gb_control_bundle_deactivate(bundle->पूर्णांकf->control, bundle->id);

	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_put_noidle(dev);

	वापस 0;
पूर्ण

पूर्णांक greybus_रेजिस्टर_driver(काष्ठा greybus_driver *driver, काष्ठा module *owner,
			    स्थिर अक्षर *mod_name)
अणु
	पूर्णांक retval;

	अगर (greybus_disabled())
		वापस -ENODEV;

	driver->driver.bus = &greybus_bus_type;
	driver->driver.name = driver->name;
	driver->driver.probe = greybus_probe;
	driver->driver.हटाओ = greybus_हटाओ;
	driver->driver.owner = owner;
	driver->driver.mod_name = mod_name;

	retval = driver_रेजिस्टर(&driver->driver);
	अगर (retval)
		वापस retval;

	pr_info("registered new driver %s\n", driver->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(greybus_रेजिस्टर_driver);

व्योम greybus_deरेजिस्टर_driver(काष्ठा greybus_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(greybus_deरेजिस्टर_driver);

अटल पूर्णांक __init gb_init(व्योम)
अणु
	पूर्णांक retval;

	अगर (greybus_disabled())
		वापस -ENODEV;

	BUILD_BUG_ON(CPORT_ID_MAX >= (दीर्घ)CPORT_ID_BAD);

	gb_debugfs_init();

	retval = bus_रेजिस्टर(&greybus_bus_type);
	अगर (retval) अणु
		pr_err("bus_register failed (%d)\n", retval);
		जाओ error_bus;
	पूर्ण

	retval = gb_hd_init();
	अगर (retval) अणु
		pr_err("gb_hd_init failed (%d)\n", retval);
		जाओ error_hd;
	पूर्ण

	retval = gb_operation_init();
	अगर (retval) अणु
		pr_err("gb_operation_init failed (%d)\n", retval);
		जाओ error_operation;
	पूर्ण
	वापस 0;	/* Success */

error_operation:
	gb_hd_निकास();
error_hd:
	bus_unरेजिस्टर(&greybus_bus_type);
error_bus:
	gb_debugfs_cleanup();

	वापस retval;
पूर्ण
module_init(gb_init);

अटल व्योम __निकास gb_निकास(व्योम)
अणु
	gb_operation_निकास();
	gb_hd_निकास();
	bus_unरेजिस्टर(&greybus_bus_type);
	gb_debugfs_cleanup();
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण
module_निकास(gb_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Greg Kroah-Hartman <gregkh@linuxfoundation.org>");
