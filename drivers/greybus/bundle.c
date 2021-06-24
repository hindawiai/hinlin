<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus bundles
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/greybus.h>
#समावेश "greybus_trace.h"

अटल sमाप_प्रकार bundle_class_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);

	वापस प्र_लिखो(buf, "0x%02x\n", bundle->class);
पूर्ण
अटल DEVICE_ATTR_RO(bundle_class);

अटल sमाप_प्रकार bundle_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);

	वापस प्र_लिखो(buf, "%u\n", bundle->id);
पूर्ण
अटल DEVICE_ATTR_RO(bundle_id);

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);

	अगर (!bundle->state)
		वापस प्र_लिखो(buf, "\n");

	वापस प्र_लिखो(buf, "%s\n", bundle->state);
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);

	kमुक्त(bundle->state);
	bundle->state = kstrdup(buf, GFP_KERNEL);
	अगर (!bundle->state)
		वापस -ENOMEM;

	/* Tell userspace that the file contents changed */
	sysfs_notअगरy(&bundle->dev.kobj, शून्य, "state");

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(state);

अटल काष्ठा attribute *bundle_attrs[] = अणु
	&dev_attr_bundle_class.attr,
	&dev_attr_bundle_id.attr,
	&dev_attr_state.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(bundle);

अटल काष्ठा gb_bundle *gb_bundle_find(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
					u8 bundle_id)
अणु
	काष्ठा gb_bundle *bundle;

	list_क्रम_each_entry(bundle, &पूर्णांकf->bundles, links) अणु
		अगर (bundle->id == bundle_id)
			वापस bundle;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम gb_bundle_release(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);

	trace_gb_bundle_release(bundle);

	kमुक्त(bundle->state);
	kमुक्त(bundle->cport_desc);
	kमुक्त(bundle);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम gb_bundle_disable_all_connections(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_connection *connection;

	list_क्रम_each_entry(connection, &bundle->connections, bundle_links)
		gb_connection_disable(connection);
पूर्ण

अटल व्योम gb_bundle_enable_all_connections(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_connection *connection;

	list_क्रम_each_entry(connection, &bundle->connections, bundle_links)
		gb_connection_enable(connection);
पूर्ण

अटल पूर्णांक gb_bundle_suspend(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver->pm;
	पूर्णांक ret;

	अगर (pm && pm->runसमय_suspend) अणु
		ret = pm->runसमय_suspend(&bundle->dev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		gb_bundle_disable_all_connections(bundle);
	पूर्ण

	ret = gb_control_bundle_suspend(bundle->पूर्णांकf->control, bundle->id);
	अगर (ret) अणु
		अगर (pm && pm->runसमय_resume)
			ret = pm->runसमय_resume(dev);
		अन्यथा
			gb_bundle_enable_all_connections(bundle);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_bundle_resume(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	स्थिर काष्ठा dev_pm_ops *pm = dev->driver->pm;
	पूर्णांक ret;

	ret = gb_control_bundle_resume(bundle->पूर्णांकf->control, bundle->id);
	अगर (ret)
		वापस ret;

	अगर (pm && pm->runसमय_resume) अणु
		ret = pm->runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		gb_bundle_enable_all_connections(bundle);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_bundle_idle(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);
	pm_request_स्वतःsuspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gb_bundle_pm_ops = अणु
	SET_RUNTIME_PM_OPS(gb_bundle_suspend, gb_bundle_resume, gb_bundle_idle)
पूर्ण;

काष्ठा device_type greybus_bundle_type = अणु
	.name =		"greybus_bundle",
	.release =	gb_bundle_release,
	.pm =		&gb_bundle_pm_ops,
पूर्ण;

/*
 * Create a gb_bundle काष्ठाure to represent a discovered
 * bundle.  Returns a poपूर्णांकer to the new bundle or a null
 * poपूर्णांकer अगर a failure occurs due to memory exhaustion.
 */
काष्ठा gb_bundle *gb_bundle_create(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u8 bundle_id,
				   u8 class)
अणु
	काष्ठा gb_bundle *bundle;

	अगर (bundle_id == BUNDLE_ID_NONE) अणु
		dev_err(&पूर्णांकf->dev, "can't use bundle id %u\n", bundle_id);
		वापस शून्य;
	पूर्ण

	/*
	 * Reject any attempt to reuse a bundle id.  We initialize
	 * these serially, so there's no need to worry about keeping
	 * the पूर्णांकerface bundle list locked here.
	 */
	अगर (gb_bundle_find(पूर्णांकf, bundle_id)) अणु
		dev_err(&पूर्णांकf->dev, "duplicate bundle id %u\n", bundle_id);
		वापस शून्य;
	पूर्ण

	bundle = kzalloc(माप(*bundle), GFP_KERNEL);
	अगर (!bundle)
		वापस शून्य;

	bundle->पूर्णांकf = पूर्णांकf;
	bundle->id = bundle_id;
	bundle->class = class;
	INIT_LIST_HEAD(&bundle->connections);

	bundle->dev.parent = &पूर्णांकf->dev;
	bundle->dev.bus = &greybus_bus_type;
	bundle->dev.type = &greybus_bundle_type;
	bundle->dev.groups = bundle_groups;
	bundle->dev.dma_mask = पूर्णांकf->dev.dma_mask;
	device_initialize(&bundle->dev);
	dev_set_name(&bundle->dev, "%s.%d", dev_name(&पूर्णांकf->dev), bundle_id);

	list_add(&bundle->links, &पूर्णांकf->bundles);

	trace_gb_bundle_create(bundle);

	वापस bundle;
पूर्ण

पूर्णांक gb_bundle_add(काष्ठा gb_bundle *bundle)
अणु
	पूर्णांक ret;

	ret = device_add(&bundle->dev);
	अगर (ret) अणु
		dev_err(&bundle->dev, "failed to register bundle: %d\n", ret);
		वापस ret;
	पूर्ण

	trace_gb_bundle_add(bundle);

	वापस 0;
पूर्ण

/*
 * Tear करोwn a previously set up bundle.
 */
व्योम gb_bundle_destroy(काष्ठा gb_bundle *bundle)
अणु
	trace_gb_bundle_destroy(bundle);

	अगर (device_is_रेजिस्टरed(&bundle->dev))
		device_del(&bundle->dev);

	list_del(&bundle->links);

	put_device(&bundle->dev);
पूर्ण
