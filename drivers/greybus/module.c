<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Module code
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#समावेश <linux/greybus.h>
#समावेश "greybus_trace.h"

अटल sमाप_प्रकार eject_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_module *module = to_gb_module(dev);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	माप_प्रकार i;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (!val)
		वापस len;

	क्रम (i = 0; i < module->num_पूर्णांकerfaces; ++i) अणु
		पूर्णांकf = module->पूर्णांकerfaces[i];

		mutex_lock(&पूर्णांकf->mutex);
		/* Set flag to prevent concurrent activation. */
		पूर्णांकf->ejected = true;
		gb_पूर्णांकerface_disable(पूर्णांकf);
		gb_पूर्णांकerface_deactivate(पूर्णांकf);
		mutex_unlock(&पूर्णांकf->mutex);
	पूर्ण

	/* Tell the SVC to eject the primary पूर्णांकerface. */
	ret = gb_svc_पूर्णांकf_eject(module->hd->svc, module->module_id);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_WO(eject);

अटल sमाप_प्रकार module_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_module *module = to_gb_module(dev);

	वापस प्र_लिखो(buf, "%u\n", module->module_id);
पूर्ण
अटल DEVICE_ATTR_RO(module_id);

अटल sमाप_प्रकार num_पूर्णांकerfaces_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_module *module = to_gb_module(dev);

	वापस प्र_लिखो(buf, "%zu\n", module->num_पूर्णांकerfaces);
पूर्ण
अटल DEVICE_ATTR_RO(num_पूर्णांकerfaces);

अटल काष्ठा attribute *module_attrs[] = अणु
	&dev_attr_eject.attr,
	&dev_attr_module_id.attr,
	&dev_attr_num_पूर्णांकerfaces.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(module);

अटल व्योम gb_module_release(काष्ठा device *dev)
अणु
	काष्ठा gb_module *module = to_gb_module(dev);

	trace_gb_module_release(module);

	kमुक्त(module);
पूर्ण

काष्ठा device_type greybus_module_type = अणु
	.name		= "greybus_module",
	.release	= gb_module_release,
पूर्ण;

काष्ठा gb_module *gb_module_create(काष्ठा gb_host_device *hd, u8 module_id,
				   माप_प्रकार num_पूर्णांकerfaces)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	काष्ठा gb_module *module;
	पूर्णांक i;

	module = kzalloc(काष्ठा_size(module, पूर्णांकerfaces, num_पूर्णांकerfaces),
			 GFP_KERNEL);
	अगर (!module)
		वापस शून्य;

	module->hd = hd;
	module->module_id = module_id;
	module->num_पूर्णांकerfaces = num_पूर्णांकerfaces;

	module->dev.parent = &hd->dev;
	module->dev.bus = &greybus_bus_type;
	module->dev.type = &greybus_module_type;
	module->dev.groups = module_groups;
	module->dev.dma_mask = hd->dev.dma_mask;
	device_initialize(&module->dev);
	dev_set_name(&module->dev, "%d-%u", hd->bus_id, module_id);

	trace_gb_module_create(module);

	क्रम (i = 0; i < num_पूर्णांकerfaces; ++i) अणु
		पूर्णांकf = gb_पूर्णांकerface_create(module, module_id + i);
		अगर (!पूर्णांकf) अणु
			dev_err(&module->dev, "failed to create interface %u\n",
				module_id + i);
			जाओ err_put_पूर्णांकerfaces;
		पूर्ण
		module->पूर्णांकerfaces[i] = पूर्णांकf;
	पूर्ण

	वापस module;

err_put_पूर्णांकerfaces:
	क्रम (--i; i >= 0; --i)
		gb_पूर्णांकerface_put(module->पूर्णांकerfaces[i]);

	put_device(&module->dev);

	वापस शून्य;
पूर्ण

/*
 * Register and enable an पूर्णांकerface after first attempting to activate it.
 */
अटल व्योम gb_module_रेजिस्टर_पूर्णांकerface(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_module *module = पूर्णांकf->module;
	u8 पूर्णांकf_id = पूर्णांकf->पूर्णांकerface_id;
	पूर्णांक ret;

	mutex_lock(&पूर्णांकf->mutex);

	ret = gb_पूर्णांकerface_activate(पूर्णांकf);
	अगर (ret) अणु
		अगर (पूर्णांकf->type != GB_INTERFACE_TYPE_DUMMY) अणु
			dev_err(&module->dev,
				"failed to activate interface %u: %d\n",
				पूर्णांकf_id, ret);
		पूर्ण

		gb_पूर्णांकerface_add(पूर्णांकf);
		जाओ err_unlock;
	पूर्ण

	ret = gb_पूर्णांकerface_add(पूर्णांकf);
	अगर (ret)
		जाओ err_पूर्णांकerface_deactivate;

	ret = gb_पूर्णांकerface_enable(पूर्णांकf);
	अगर (ret) अणु
		dev_err(&module->dev, "failed to enable interface %u: %d\n",
			पूर्णांकf_id, ret);
		जाओ err_पूर्णांकerface_deactivate;
	पूर्ण

	mutex_unlock(&पूर्णांकf->mutex);

	वापस;

err_पूर्णांकerface_deactivate:
	gb_पूर्णांकerface_deactivate(पूर्णांकf);
err_unlock:
	mutex_unlock(&पूर्णांकf->mutex);
पूर्ण

अटल व्योम gb_module_deरेजिस्टर_पूर्णांकerface(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	/* Mark as disconnected to prevent I/O during disable. */
	अगर (पूर्णांकf->module->disconnected)
		पूर्णांकf->disconnected = true;

	mutex_lock(&पूर्णांकf->mutex);
	पूर्णांकf->हटाओd = true;
	gb_पूर्णांकerface_disable(पूर्णांकf);
	gb_पूर्णांकerface_deactivate(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->mutex);

	gb_पूर्णांकerface_del(पूर्णांकf);
पूर्ण

/* Register a module and its पूर्णांकerfaces. */
पूर्णांक gb_module_add(काष्ठा gb_module *module)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	ret = device_add(&module->dev);
	अगर (ret) अणु
		dev_err(&module->dev, "failed to register module: %d\n", ret);
		वापस ret;
	पूर्ण

	trace_gb_module_add(module);

	क्रम (i = 0; i < module->num_पूर्णांकerfaces; ++i)
		gb_module_रेजिस्टर_पूर्णांकerface(module->पूर्णांकerfaces[i]);

	वापस 0;
पूर्ण

/* Deरेजिस्टर a module and its पूर्णांकerfaces. */
व्योम gb_module_del(काष्ठा gb_module *module)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < module->num_पूर्णांकerfaces; ++i)
		gb_module_deरेजिस्टर_पूर्णांकerface(module->पूर्णांकerfaces[i]);

	trace_gb_module_del(module);

	device_del(&module->dev);
पूर्ण

व्योम gb_module_put(काष्ठा gb_module *module)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < module->num_पूर्णांकerfaces; ++i)
		gb_पूर्णांकerface_put(module->पूर्णांकerfaces[i]);

	put_device(&module->dev);
पूर्ण
