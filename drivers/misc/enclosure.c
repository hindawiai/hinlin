<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Enclosure Services
 *
 * Copyright (C) 2008 James Bottomley <James.Bottomley@HansenPartnership.com>
 *
**-----------------------------------------------------------------------------
**
**
**-----------------------------------------------------------------------------
*/
#समावेश <linux/device.h>
#समावेश <linux/enclosure.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

अटल LIST_HEAD(container_list);
अटल DEFINE_MUTEX(container_list_lock);
अटल काष्ठा class enclosure_class;

/**
 * enclosure_find - find an enclosure given a parent device
 * @dev:	the parent to match against
 * @start:	Optional enclosure device to start from (शून्य अगर none)
 *
 * Looks through the list of रेजिस्टरed enclosures to find all those
 * with @dev as a parent.  Returns शून्य अगर no enclosure is
 * found. @start can be used as a starting poपूर्णांक to obtain multiple
 * enclosures per parent (should begin with शून्य and then be set to
 * each वापसed enclosure device). Obtains a reference to the
 * enclosure class device which must be released with device_put().
 * If @start is not शून्य, a reference must be taken on it which is
 * released beक्रमe वापसing (this allows a loop through all
 * enclosures to निकास with only the reference on the enclosure of
 * पूर्णांकerest held).  Note that the @dev may correspond to the actual
 * device housing the enclosure, in which हाल no iteration via @start
 * is required.
 */
काष्ठा enclosure_device *enclosure_find(काष्ठा device *dev,
					काष्ठा enclosure_device *start)
अणु
	काष्ठा enclosure_device *edev;

	mutex_lock(&container_list_lock);
	edev = list_prepare_entry(start, &container_list, node);
	अगर (start)
		put_device(&start->edev);

	list_क्रम_each_entry_जारी(edev, &container_list, node) अणु
		काष्ठा device *parent = edev->edev.parent;
		/* parent might not be immediate, so iterate up to
		 * the root of the tree अगर necessary */
		जबतक (parent) अणु
			अगर (parent == dev) अणु
				get_device(&edev->edev);
				mutex_unlock(&container_list_lock);
				वापस edev;
			पूर्ण
			parent = parent->parent;
		पूर्ण
	पूर्ण
	mutex_unlock(&container_list_lock);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_find);

/**
 * enclosure_क्रम_each_device - calls a function क्रम each enclosure
 * @fn:		the function to call
 * @data:	the data to pass to each call
 *
 * Loops over all the enclosures calling the function.
 *
 * Note, this function uses a mutex which will be held across calls to
 * @fn, so it must have non atomic context, and @fn may (although it
 * should not) sleep or otherwise cause the mutex to be held क्रम
 * indefinite periods
 */
पूर्णांक enclosure_क्रम_each_device(पूर्णांक (*fn)(काष्ठा enclosure_device *, व्योम *),
			      व्योम *data)
अणु
	पूर्णांक error = 0;
	काष्ठा enclosure_device *edev;

	mutex_lock(&container_list_lock);
	list_क्रम_each_entry(edev, &container_list, node) अणु
		error = fn(edev, data);
		अगर (error)
			अवरोध;
	पूर्ण
	mutex_unlock(&container_list_lock);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_क्रम_each_device);

/**
 * enclosure_रेजिस्टर - रेजिस्टर device as an enclosure
 *
 * @dev:	device containing the enclosure
 * @name:	chosen device name
 * @components:	number of components in the enclosure
 * @cb:         platक्रमm call-backs
 *
 * This sets up the device क्रम being an enclosure.  Note that @dev करोes
 * not have to be a dedicated enclosure device.  It may be some other type
 * of device that additionally responds to enclosure services
 */
काष्ठा enclosure_device *
enclosure_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक components,
		   काष्ठा enclosure_component_callbacks *cb)
अणु
	काष्ठा enclosure_device *edev =
		kzalloc(काष्ठा_size(edev, component, components), GFP_KERNEL);
	पूर्णांक err, i;

	BUG_ON(!cb);

	अगर (!edev)
		वापस ERR_PTR(-ENOMEM);

	edev->components = components;

	edev->edev.class = &enclosure_class;
	edev->edev.parent = get_device(dev);
	edev->cb = cb;
	dev_set_name(&edev->edev, "%s", name);
	err = device_रेजिस्टर(&edev->edev);
	अगर (err)
		जाओ err;

	क्रम (i = 0; i < components; i++) अणु
		edev->component[i].number = -1;
		edev->component[i].slot = -1;
		edev->component[i].घातer_status = -1;
	पूर्ण

	mutex_lock(&container_list_lock);
	list_add_tail(&edev->node, &container_list);
	mutex_unlock(&container_list_lock);

	वापस edev;

 err:
	put_device(edev->edev.parent);
	kमुक्त(edev);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_रेजिस्टर);

अटल काष्ठा enclosure_component_callbacks enclosure_null_callbacks;

/**
 * enclosure_unरेजिस्टर - हटाओ an enclosure
 *
 * @edev:	the रेजिस्टरed enclosure to हटाओ;
 */
व्योम enclosure_unरेजिस्टर(काष्ठा enclosure_device *edev)
अणु
	पूर्णांक i;

	mutex_lock(&container_list_lock);
	list_del(&edev->node);
	mutex_unlock(&container_list_lock);

	क्रम (i = 0; i < edev->components; i++)
		अगर (edev->component[i].number != -1)
			device_unरेजिस्टर(&edev->component[i].cdev);

	/* prevent any callbacks पूर्णांकo service user */
	edev->cb = &enclosure_null_callbacks;
	device_unरेजिस्टर(&edev->edev);
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_unरेजिस्टर);

#घोषणा ENCLOSURE_NAME_SIZE	64
#घोषणा COMPONENT_NAME_SIZE	64

अटल व्योम enclosure_link_name(काष्ठा enclosure_component *cdev, अक्षर *name)
अणु
	म_नकल(name, "enclosure_device:");
	म_जोड़ो(name, dev_name(&cdev->cdev));
पूर्ण

अटल व्योम enclosure_हटाओ_links(काष्ठा enclosure_component *cdev)
अणु
	अक्षर name[ENCLOSURE_NAME_SIZE];

	enclosure_link_name(cdev, name);

	/*
	 * In odd circumstances, like multipath devices, something अन्यथा may
	 * alपढ़ोy have हटाओd the links, so check क्रम this condition first.
	 */
	अगर (cdev->dev->kobj.sd)
		sysfs_हटाओ_link(&cdev->dev->kobj, name);

	अगर (cdev->cdev.kobj.sd)
		sysfs_हटाओ_link(&cdev->cdev.kobj, "device");
पूर्ण

अटल पूर्णांक enclosure_add_links(काष्ठा enclosure_component *cdev)
अणु
	पूर्णांक error;
	अक्षर name[ENCLOSURE_NAME_SIZE];

	error = sysfs_create_link(&cdev->cdev.kobj, &cdev->dev->kobj, "device");
	अगर (error)
		वापस error;

	enclosure_link_name(cdev, name);
	error = sysfs_create_link(&cdev->dev->kobj, &cdev->cdev.kobj, name);
	अगर (error)
		sysfs_हटाओ_link(&cdev->cdev.kobj, "device");

	वापस error;
पूर्ण

अटल व्योम enclosure_release(काष्ठा device *cdev)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev);

	put_device(cdev->parent);
	kमुक्त(edev);
पूर्ण

अटल व्योम enclosure_component_release(काष्ठा device *dev)
अणु
	काष्ठा enclosure_component *cdev = to_enclosure_component(dev);

	अगर (cdev->dev) अणु
		enclosure_हटाओ_links(cdev);
		put_device(cdev->dev);
	पूर्ण
	put_device(dev->parent);
पूर्ण

अटल काष्ठा enclosure_component *
enclosure_component_find_by_name(काष्ठा enclosure_device *edev,
				स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	स्थिर अक्षर *cname;
	काष्ठा enclosure_component *ecomp;

	अगर (!edev || !name || !name[0])
		वापस शून्य;

	क्रम (i = 0; i < edev->components; i++) अणु
		ecomp = &edev->component[i];
		cname = dev_name(&ecomp->cdev);
		अगर (ecomp->number != -1 &&
		    cname && cname[0] &&
		    !म_भेद(cname, name))
			वापस ecomp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा attribute_group *enclosure_component_groups[];

/**
 * enclosure_component_alloc - prepare a new enclosure component
 * @edev:	the enclosure to add the component
 * @number:	the device number
 * @type:	the type of component being added
 * @name:	an optional name to appear in sysfs (leave शून्य अगर none)
 *
 * The name is optional क्रम enclosures that give their components a unique
 * name.  If not, leave the field शून्य and a name will be asचिन्हित.
 *
 * Returns a poपूर्णांकer to the enclosure component or an error.
 */
काष्ठा enclosure_component *
enclosure_component_alloc(काष्ठा enclosure_device *edev,
			  अचिन्हित पूर्णांक number,
			  क्रमागत enclosure_component_type type,
			  स्थिर अक्षर *name)
अणु
	काष्ठा enclosure_component *ecomp;
	काष्ठा device *cdev;
	पूर्णांक i;
	अक्षर newname[COMPONENT_NAME_SIZE];

	अगर (number >= edev->components)
		वापस ERR_PTR(-EINVAL);

	ecomp = &edev->component[number];

	अगर (ecomp->number != -1)
		वापस ERR_PTR(-EINVAL);

	ecomp->type = type;
	ecomp->number = number;
	cdev = &ecomp->cdev;
	cdev->parent = get_device(&edev->edev);

	अगर (name && name[0]) अणु
		/* Some hardware (e.g. enclosure in RX300 S6) has components
		 * with non unique names. Registering duplicates in sysfs
		 * will lead to warnings during bootup. So make the names
		 * unique by appending consecutive numbers -1, -2, ... */
		i = 1;
		snम_लिखो(newname, COMPONENT_NAME_SIZE,
			 "%s", name);
		जबतक (enclosure_component_find_by_name(edev, newname))
			snम_लिखो(newname, COMPONENT_NAME_SIZE,
				 "%s-%i", name, i++);
		dev_set_name(cdev, "%s", newname);
	पूर्ण अन्यथा
		dev_set_name(cdev, "%u", number);

	cdev->release = enclosure_component_release;
	cdev->groups = enclosure_component_groups;

	वापस ecomp;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_component_alloc);

/**
 * enclosure_component_रेजिस्टर - publishes an initialized enclosure component
 * @ecomp:	component to add
 *
 * Returns 0 on successful registration, releases the component otherwise
 */
पूर्णांक enclosure_component_रेजिस्टर(काष्ठा enclosure_component *ecomp)
अणु
	काष्ठा device *cdev;
	पूर्णांक err;

	cdev = &ecomp->cdev;
	err = device_रेजिस्टर(cdev);
	अगर (err) अणु
		ecomp->number = -1;
		put_device(cdev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_component_रेजिस्टर);

/**
 * enclosure_add_device - add a device as being part of an enclosure
 * @edev:	the enclosure device being added to.
 * @component:	the number of the component
 * @dev:	the device being added
 *
 * Declares a real device to reside in slot (or identअगरier) @num of an
 * enclosure.  This will cause the relevant sysfs links to appear.
 * This function may also be used to change a device associated with
 * an enclosure without having to call enclosure_हटाओ_device() in
 * between.
 *
 * Returns zero on success or an error.
 */
पूर्णांक enclosure_add_device(काष्ठा enclosure_device *edev, पूर्णांक component,
			 काष्ठा device *dev)
अणु
	काष्ठा enclosure_component *cdev;
	पूर्णांक err;

	अगर (!edev || component >= edev->components)
		वापस -EINVAL;

	cdev = &edev->component[component];

	अगर (cdev->dev == dev)
		वापस -EEXIST;

	अगर (cdev->dev) अणु
		enclosure_हटाओ_links(cdev);
		put_device(cdev->dev);
	पूर्ण
	cdev->dev = get_device(dev);
	err = enclosure_add_links(cdev);
	अगर (err) अणु
		put_device(cdev->dev);
		cdev->dev = शून्य;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_add_device);

/**
 * enclosure_हटाओ_device - हटाओ a device from an enclosure
 * @edev:	the enclosure device
 * @dev:	device to हटाओ/put
 *
 * Returns zero on success or an error.
 *
 */
पूर्णांक enclosure_हटाओ_device(काष्ठा enclosure_device *edev, काष्ठा device *dev)
अणु
	काष्ठा enclosure_component *cdev;
	पूर्णांक i;

	अगर (!edev || !dev)
		वापस -EINVAL;

	क्रम (i = 0; i < edev->components; i++) अणु
		cdev = &edev->component[i];
		अगर (cdev->dev == dev) अणु
			enclosure_हटाओ_links(cdev);
			put_device(dev);
			cdev->dev = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(enclosure_हटाओ_device);

/*
 * sysfs pieces below
 */

अटल sमाप_प्रकार components_show(काष्ठा device *cdev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev);

	वापस snम_लिखो(buf, 40, "%d\n", edev->components);
पूर्ण
अटल DEVICE_ATTR_RO(components);

अटल sमाप_प्रकार id_show(काष्ठा device *cdev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev);

	अगर (edev->cb->show_id)
		वापस edev->cb->show_id(edev, buf);
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल काष्ठा attribute *enclosure_class_attrs[] = अणु
	&dev_attr_components.attr,
	&dev_attr_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(enclosure_class);

अटल काष्ठा class enclosure_class = अणु
	.name			= "enclosure",
	.owner			= THIS_MODULE,
	.dev_release		= enclosure_release,
	.dev_groups		= enclosure_class_groups,
पूर्ण;

अटल स्थिर अक्षर *स्थिर enclosure_status[] = अणु
	[ENCLOSURE_STATUS_UNSUPPORTED] = "unsupported",
	[ENCLOSURE_STATUS_OK] = "OK",
	[ENCLOSURE_STATUS_CRITICAL] = "critical",
	[ENCLOSURE_STATUS_NON_CRITICAL] = "non-critical",
	[ENCLOSURE_STATUS_UNRECOVERABLE] = "unrecoverable",
	[ENCLOSURE_STATUS_NOT_INSTALLED] = "not installed",
	[ENCLOSURE_STATUS_UNKNOWN] = "unknown",
	[ENCLOSURE_STATUS_UNAVAILABLE] = "unavailable",
	[ENCLOSURE_STATUS_MAX] = शून्य,
पूर्ण;

अटल स्थिर अक्षर *स्थिर enclosure_type[] = अणु
	[ENCLOSURE_COMPONENT_DEVICE] = "device",
	[ENCLOSURE_COMPONENT_ARRAY_DEVICE] = "array device",
पूर्ण;

अटल sमाप_प्रकार get_component_fault(काष्ठा device *cdev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	अगर (edev->cb->get_fault)
		edev->cb->get_fault(edev, ecomp);
	वापस snम_लिखो(buf, 40, "%d\n", ecomp->fault);
पूर्ण

अटल sमाप_प्रकार set_component_fault(काष्ठा device *cdev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक val = simple_म_से_अदीर्घ(buf, शून्य, 0);

	अगर (edev->cb->set_fault)
		edev->cb->set_fault(edev, ecomp, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार get_component_status(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr,अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	अगर (edev->cb->get_status)
		edev->cb->get_status(edev, ecomp);
	वापस snम_लिखो(buf, 40, "%s\n", enclosure_status[ecomp->status]);
पूर्ण

अटल sमाप_प्रकार set_component_status(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक i;

	क्रम (i = 0; enclosure_status[i]; i++) अणु
		अगर (म_भेदन(buf, enclosure_status[i],
			    म_माप(enclosure_status[i])) == 0 &&
		    (buf[म_माप(enclosure_status[i])] == '\n' ||
		     buf[म_माप(enclosure_status[i])] == '\0'))
			अवरोध;
	पूर्ण

	अगर (enclosure_status[i] && edev->cb->set_status) अणु
		edev->cb->set_status(edev, ecomp, i);
		वापस count;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार get_component_active(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	अगर (edev->cb->get_active)
		edev->cb->get_active(edev, ecomp);
	वापस snम_लिखो(buf, 40, "%d\n", ecomp->active);
पूर्ण

अटल sमाप_प्रकार set_component_active(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक val = simple_म_से_अदीर्घ(buf, शून्य, 0);

	अगर (edev->cb->set_active)
		edev->cb->set_active(edev, ecomp, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार get_component_locate(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	अगर (edev->cb->get_locate)
		edev->cb->get_locate(edev, ecomp);
	वापस snम_लिखो(buf, 40, "%d\n", ecomp->locate);
पूर्ण

अटल sमाप_प्रकार set_component_locate(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक val = simple_म_से_अदीर्घ(buf, शून्य, 0);

	अगर (edev->cb->set_locate)
		edev->cb->set_locate(edev, ecomp, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार get_component_घातer_status(काष्ठा device *cdev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	अगर (edev->cb->get_घातer_status)
		edev->cb->get_घातer_status(edev, ecomp);

	/* If still uninitialized, the callback failed or करोes not exist. */
	अगर (ecomp->घातer_status == -1)
		वापस (edev->cb->get_घातer_status) ? -EIO : -ENOTTY;

	वापस snम_लिखो(buf, 40, "%s\n", ecomp->घातer_status ? "on" : "off");
पूर्ण

अटल sमाप_प्रकार set_component_घातer_status(काष्ठा device *cdev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा enclosure_device *edev = to_enclosure_device(cdev->parent);
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक val;

	अगर (म_भेदन(buf, "on", 2) == 0 &&
	    (buf[2] == '\n' || buf[2] == '\0'))
		val = 1;
	अन्यथा अगर (म_भेदन(buf, "off", 3) == 0 &&
	    (buf[3] == '\n' || buf[3] == '\0'))
		val = 0;
	अन्यथा
		वापस -EINVAL;

	अगर (edev->cb->set_घातer_status)
		edev->cb->set_घातer_status(edev, ecomp, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार get_component_type(काष्ठा device *cdev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);

	वापस snम_लिखो(buf, 40, "%s\n", enclosure_type[ecomp->type]);
पूर्ण

अटल sमाप_प्रकार get_component_slot(काष्ठा device *cdev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा enclosure_component *ecomp = to_enclosure_component(cdev);
	पूर्णांक slot;

	/* अगर the enclosure करोes not override then use 'number' as a stand-in */
	अगर (ecomp->slot >= 0)
		slot = ecomp->slot;
	अन्यथा
		slot = ecomp->number;

	वापस snम_लिखो(buf, 40, "%d\n", slot);
पूर्ण

अटल DEVICE_ATTR(fault, S_IRUGO | S_IWUSR, get_component_fault,
		    set_component_fault);
अटल DEVICE_ATTR(status, S_IRUGO | S_IWUSR, get_component_status,
		   set_component_status);
अटल DEVICE_ATTR(active, S_IRUGO | S_IWUSR, get_component_active,
		   set_component_active);
अटल DEVICE_ATTR(locate, S_IRUGO | S_IWUSR, get_component_locate,
		   set_component_locate);
अटल DEVICE_ATTR(घातer_status, S_IRUGO | S_IWUSR, get_component_घातer_status,
		   set_component_घातer_status);
अटल DEVICE_ATTR(type, S_IRUGO, get_component_type, शून्य);
अटल DEVICE_ATTR(slot, S_IRUGO, get_component_slot, शून्य);

अटल काष्ठा attribute *enclosure_component_attrs[] = अणु
	&dev_attr_fault.attr,
	&dev_attr_status.attr,
	&dev_attr_active.attr,
	&dev_attr_locate.attr,
	&dev_attr_घातer_status.attr,
	&dev_attr_type.attr,
	&dev_attr_slot.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(enclosure_component);

अटल पूर्णांक __init enclosure_init(व्योम)
अणु
	वापस class_रेजिस्टर(&enclosure_class);
पूर्ण

अटल व्योम __निकास enclosure_निकास(व्योम)
अणु
	class_unरेजिस्टर(&enclosure_class);
पूर्ण

module_init(enclosure_init);
module_निकास(enclosure_निकास);

MODULE_AUTHOR("James Bottomley");
MODULE_DESCRIPTION("Enclosure Services");
MODULE_LICENSE("GPL v2");
