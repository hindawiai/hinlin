<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Link physical devices with ACPI devices support
 *
 * Copyright (c) 2005 David Shaohua Li <shaohua.li@पूर्णांकel.com>
 * Copyright (c) 2005 Intel Corp.
 */

#समावेश <linux/acpi_iort.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internal.h"

#घोषणा ACPI_GLUE_DEBUG	0
#अगर ACPI_GLUE_DEBUG
#घोषणा DBG(fmt, ...)						\
	prपूर्णांकk(KERN_DEBUG PREFIX fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा DBG(fmt, ...)						\
करो अणु								\
	अगर (0)							\
		prपूर्णांकk(KERN_DEBUG PREFIX fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#पूर्ण_अगर
अटल LIST_HEAD(bus_type_list);
अटल DECLARE_RWSEM(bus_type_sem);

#घोषणा PHYSICAL_NODE_STRING "physical_node"
#घोषणा PHYSICAL_NODE_NAME_SIZE (माप(PHYSICAL_NODE_STRING) + 10)

पूर्णांक रेजिस्टर_acpi_bus_type(काष्ठा acpi_bus_type *type)
अणु
	अगर (acpi_disabled)
		वापस -ENODEV;
	अगर (type && type->match && type->find_companion) अणु
		करोwn_ग_लिखो(&bus_type_sem);
		list_add_tail(&type->list, &bus_type_list);
		up_ग_लिखो(&bus_type_sem);
		prपूर्णांकk(KERN_INFO PREFIX "bus type %s registered\n", type->name);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_acpi_bus_type);

पूर्णांक unरेजिस्टर_acpi_bus_type(काष्ठा acpi_bus_type *type)
अणु
	अगर (acpi_disabled)
		वापस 0;
	अगर (type) अणु
		करोwn_ग_लिखो(&bus_type_sem);
		list_del_init(&type->list);
		up_ग_लिखो(&bus_type_sem);
		prपूर्णांकk(KERN_INFO PREFIX "bus type %s unregistered\n",
		       type->name);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_acpi_bus_type);

अटल काष्ठा acpi_bus_type *acpi_get_bus_type(काष्ठा device *dev)
अणु
	काष्ठा acpi_bus_type *पंचांगp, *ret = शून्य;

	करोwn_पढ़ो(&bus_type_sem);
	list_क्रम_each_entry(पंचांगp, &bus_type_list, list) अणु
		अगर (पंचांगp->match(dev)) अणु
			ret = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&bus_type_sem);
	वापस ret;
पूर्ण

#घोषणा FIND_CHILD_MIN_SCORE	1
#घोषणा FIND_शिशु_उच्च_SCORE	2

अटल पूर्णांक find_child_checks(काष्ठा acpi_device *adev, bool check_children)
अणु
	bool sta_present = true;
	अचिन्हित दीर्घ दीर्घ sta;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(adev->handle, "_STA", शून्य, &sta);
	अगर (status == AE_NOT_FOUND)
		sta_present = false;
	अन्यथा अगर (ACPI_FAILURE(status) || !(sta & ACPI_STA_DEVICE_ENABLED))
		वापस -ENODEV;

	अगर (check_children && list_empty(&adev->children))
		वापस -ENODEV;

	/*
	 * If the device has a _HID वापसing a valid ACPI/PNP device ID, it is
	 * better to make it look less attractive here, so that the other device
	 * with the same _ADR value (that may not have a valid device ID) can be
	 * matched going क्रमward.  [This means a second spec violation in a row,
	 * so whatever we करो here is best efक्रमt anyway.]
	 */
	वापस sta_present && !adev->pnp.type.platक्रमm_id ?
			FIND_शिशु_उच्च_SCORE : FIND_CHILD_MIN_SCORE;
पूर्ण

काष्ठा acpi_device *acpi_find_child_device(काष्ठा acpi_device *parent,
					   u64 address, bool check_children)
अणु
	काष्ठा acpi_device *adev, *ret = शून्य;
	पूर्णांक ret_score = 0;

	अगर (!parent)
		वापस शून्य;

	list_क्रम_each_entry(adev, &parent->children, node) अणु
		अचिन्हित दीर्घ दीर्घ addr;
		acpi_status status;
		पूर्णांक score;

		status = acpi_evaluate_पूर्णांकeger(adev->handle, METHOD_NAME__ADR,
					       शून्य, &addr);
		अगर (ACPI_FAILURE(status) || addr != address)
			जारी;

		अगर (!ret) अणु
			/* This is the first matching object.  Save it. */
			ret = adev;
			जारी;
		पूर्ण
		/*
		 * There is more than one matching device object with the same
		 * _ADR value.  That really is unexpected, so we are kind of
		 * beyond the scope of the spec here.  We have to choose which
		 * one to वापस, though.
		 *
		 * First, check अगर the previously found object is good enough
		 * and वापस it अगर so.  Second, करो the same क्रम the object that
		 * we've just found.
		 */
		अगर (!ret_score) अणु
			ret_score = find_child_checks(ret, check_children);
			अगर (ret_score == FIND_शिशु_उच्च_SCORE)
				वापस ret;
		पूर्ण
		score = find_child_checks(adev, check_children);
		अगर (score == FIND_शिशु_उच्च_SCORE) अणु
			वापस adev;
		पूर्ण अन्यथा अगर (score > ret_score) अणु
			ret = adev;
			ret_score = score;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_find_child_device);

अटल व्योम acpi_physnode_link_name(अक्षर *buf, अचिन्हित पूर्णांक node_id)
अणु
	अगर (node_id > 0)
		snम_लिखो(buf, PHYSICAL_NODE_NAME_SIZE,
			 PHYSICAL_NODE_STRING "%u", node_id);
	अन्यथा
		म_नकल(buf, PHYSICAL_NODE_STRING);
पूर्ण

पूर्णांक acpi_bind_one(काष्ठा device *dev, काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा acpi_device_physical_node *physical_node, *pn;
	अक्षर physical_node_name[PHYSICAL_NODE_NAME_SIZE];
	काष्ठा list_head *physnode_list;
	अचिन्हित पूर्णांक node_id;
	पूर्णांक retval = -EINVAL;

	अगर (has_acpi_companion(dev)) अणु
		अगर (acpi_dev) अणु
			dev_warn(dev, "ACPI companion already set\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			acpi_dev = ACPI_COMPANION(dev);
		पूर्ण
	पूर्ण
	अगर (!acpi_dev)
		वापस -EINVAL;

	acpi_dev_get(acpi_dev);
	get_device(dev);
	physical_node = kzalloc(माप(*physical_node), GFP_KERNEL);
	अगर (!physical_node) अणु
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	mutex_lock(&acpi_dev->physical_node_lock);

	/*
	 * Keep the list sorted by node_id so that the IDs of हटाओd nodes can
	 * be recycled easily.
	 */
	physnode_list = &acpi_dev->physical_node_list;
	node_id = 0;
	list_क्रम_each_entry(pn, &acpi_dev->physical_node_list, node) अणु
		/* Sanity check. */
		अगर (pn->dev == dev) अणु
			mutex_unlock(&acpi_dev->physical_node_lock);

			dev_warn(dev, "Already associated with ACPI node\n");
			kमुक्त(physical_node);
			अगर (ACPI_COMPANION(dev) != acpi_dev)
				जाओ err;

			put_device(dev);
			acpi_dev_put(acpi_dev);
			वापस 0;
		पूर्ण
		अगर (pn->node_id == node_id) अणु
			physnode_list = &pn->node;
			node_id++;
		पूर्ण
	पूर्ण

	physical_node->node_id = node_id;
	physical_node->dev = dev;
	list_add(&physical_node->node, physnode_list);
	acpi_dev->physical_node_count++;

	अगर (!has_acpi_companion(dev))
		ACPI_COMPANION_SET(dev, acpi_dev);

	acpi_physnode_link_name(physical_node_name, node_id);
	retval = sysfs_create_link(&acpi_dev->dev.kobj, &dev->kobj,
				   physical_node_name);
	अगर (retval)
		dev_err(&acpi_dev->dev, "Failed to create link %s (%d)\n",
			physical_node_name, retval);

	retval = sysfs_create_link(&dev->kobj, &acpi_dev->dev.kobj,
				   "firmware_node");
	अगर (retval)
		dev_err(dev, "Failed to create link firmware_node (%d)\n",
			retval);

	mutex_unlock(&acpi_dev->physical_node_lock);

	अगर (acpi_dev->wakeup.flags.valid)
		device_set_wakeup_capable(dev, true);

	वापस 0;

 err:
	ACPI_COMPANION_SET(dev, शून्य);
	put_device(dev);
	acpi_dev_put(acpi_dev);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bind_one);

पूर्णांक acpi_unbind_one(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(dev);
	काष्ठा acpi_device_physical_node *entry;

	अगर (!acpi_dev)
		वापस 0;

	mutex_lock(&acpi_dev->physical_node_lock);

	list_क्रम_each_entry(entry, &acpi_dev->physical_node_list, node)
		अगर (entry->dev == dev) अणु
			अक्षर physnode_name[PHYSICAL_NODE_NAME_SIZE];

			list_del(&entry->node);
			acpi_dev->physical_node_count--;

			acpi_physnode_link_name(physnode_name, entry->node_id);
			sysfs_हटाओ_link(&acpi_dev->dev.kobj, physnode_name);
			sysfs_हटाओ_link(&dev->kobj, "firmware_node");
			ACPI_COMPANION_SET(dev, शून्य);
			/* Drop references taken by acpi_bind_one(). */
			put_device(dev);
			acpi_dev_put(acpi_dev);
			kमुक्त(entry);
			अवरोध;
		पूर्ण

	mutex_unlock(&acpi_dev->physical_node_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_unbind_one);

अटल पूर्णांक acpi_device_notअगरy(काष्ठा device *dev)
अणु
	काष्ठा acpi_bus_type *type = acpi_get_bus_type(dev);
	काष्ठा acpi_device *adev;
	पूर्णांक ret;

	ret = acpi_bind_one(dev, शून्य);
	अगर (ret && type) अणु
		काष्ठा acpi_device *adev;

		adev = type->find_companion(dev);
		अगर (!adev) अणु
			DBG("Unable to get handle for %s\n", dev_name(dev));
			ret = -ENODEV;
			जाओ out;
		पूर्ण
		ret = acpi_bind_one(dev, adev);
		अगर (ret)
			जाओ out;
	पूर्ण
	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		जाओ out;

	अगर (dev_is_platक्रमm(dev))
		acpi_configure_pmsi_करोमुख्य(dev);

	अगर (type && type->setup)
		type->setup(dev);
	अन्यथा अगर (adev->handler && adev->handler->bind)
		adev->handler->bind(dev);

 out:
#अगर ACPI_GLUE_DEBUG
	अगर (!ret) अणु
		काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

		acpi_get_name(ACPI_HANDLE(dev), ACPI_FULL_PATHNAME, &buffer);
		DBG("Device %s -> %s\n", dev_name(dev), (अक्षर *)buffer.poपूर्णांकer);
		kमुक्त(buffer.poपूर्णांकer);
	पूर्ण अन्यथा
		DBG("Device %s -> No ACPI support\n", dev_name(dev));
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_device_notअगरy_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा acpi_bus_type *type;

	अगर (!adev)
		वापस 0;

	type = acpi_get_bus_type(dev);
	अगर (type && type->cleanup)
		type->cleanup(dev);
	अन्यथा अगर (adev->handler && adev->handler->unbind)
		adev->handler->unbind(dev);

	acpi_unbind_one(dev);
	वापस 0;
पूर्ण

पूर्णांक acpi_platक्रमm_notअगरy(काष्ठा device *dev, क्रमागत kobject_action action)
अणु
	चयन (action) अणु
	हाल KOBJ_ADD:
		acpi_device_notअगरy(dev);
		अवरोध;
	हाल KOBJ_REMOVE:
		acpi_device_notअगरy_हटाओ(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
