<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * attribute_container.c - implementation of a simple container क्रम classes
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 *
 * The basic idea here is to enable a device to be attached to an
 * aritrary numer of classes without having to allocate storage क्रम them.
 * Instead, the contained classes select the devices they need to attach
 * to via a matching function.
 */

#समावेश <linux/attribute_container.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश "base.h"

/* This is a निजी काष्ठाure used to tie the classdev and the
 * container .. it should never be visible outside this file */
काष्ठा पूर्णांकernal_container अणु
	काष्ठा klist_node node;
	काष्ठा attribute_container *cont;
	काष्ठा device classdev;
पूर्ण;

अटल व्योम पूर्णांकernal_container_klist_get(काष्ठा klist_node *n)
अणु
	काष्ठा पूर्णांकernal_container *ic =
		container_of(n, काष्ठा पूर्णांकernal_container, node);
	get_device(&ic->classdev);
पूर्ण

अटल व्योम पूर्णांकernal_container_klist_put(काष्ठा klist_node *n)
अणु
	काष्ठा पूर्णांकernal_container *ic =
		container_of(n, काष्ठा पूर्णांकernal_container, node);
	put_device(&ic->classdev);
पूर्ण


/**
 * attribute_container_classdev_to_container - given a classdev, वापस the container
 *
 * @classdev: the class device created by attribute_container_add_device.
 *
 * Returns the container associated with this classdev.
 */
काष्ठा attribute_container *
attribute_container_classdev_to_container(काष्ठा device *classdev)
अणु
	काष्ठा पूर्णांकernal_container *ic =
		container_of(classdev, काष्ठा पूर्णांकernal_container, classdev);
	वापस ic->cont;
पूर्ण
EXPORT_SYMBOL_GPL(attribute_container_classdev_to_container);

अटल LIST_HEAD(attribute_container_list);

अटल DEFINE_MUTEX(attribute_container_mutex);

/**
 * attribute_container_रेजिस्टर - रेजिस्टर an attribute container
 *
 * @cont: The container to रेजिस्टर.  This must be allocated by the
 *        callee and should also be zeroed by it.
 */
पूर्णांक
attribute_container_रेजिस्टर(काष्ठा attribute_container *cont)
अणु
	INIT_LIST_HEAD(&cont->node);
	klist_init(&cont->containers, पूर्णांकernal_container_klist_get,
		   पूर्णांकernal_container_klist_put);

	mutex_lock(&attribute_container_mutex);
	list_add_tail(&cont->node, &attribute_container_list);
	mutex_unlock(&attribute_container_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(attribute_container_रेजिस्टर);

/**
 * attribute_container_unरेजिस्टर - हटाओ a container registration
 *
 * @cont: previously रेजिस्टरed container to हटाओ
 */
पूर्णांक
attribute_container_unरेजिस्टर(काष्ठा attribute_container *cont)
अणु
	पूर्णांक retval = -EBUSY;

	mutex_lock(&attribute_container_mutex);
	spin_lock(&cont->containers.k_lock);
	अगर (!list_empty(&cont->containers.k_list))
		जाओ out;
	retval = 0;
	list_del(&cont->node);
 out:
	spin_unlock(&cont->containers.k_lock);
	mutex_unlock(&attribute_container_mutex);
	वापस retval;

पूर्ण
EXPORT_SYMBOL_GPL(attribute_container_unरेजिस्टर);

/* निजी function used as class release */
अटल व्योम attribute_container_release(काष्ठा device *classdev)
अणु
	काष्ठा पूर्णांकernal_container *ic
		= container_of(classdev, काष्ठा पूर्णांकernal_container, classdev);
	काष्ठा device *dev = classdev->parent;

	kमुक्त(ic);
	put_device(dev);
पूर्ण

/**
 * attribute_container_add_device - see अगर any container is पूर्णांकerested in dev
 *
 * @dev: device to add attributes to
 * @fn:	 function to trigger addition of class device.
 *
 * This function allocates storage क्रम the class device(s) to be
 * attached to dev (one क्रम each matching attribute_container).  If no
 * fn is provided, the code will simply रेजिस्टर the class device via
 * device_add.  If a function is provided, it is expected to add
 * the class device at the appropriate समय.  One of the things that
 * might be necessary is to allocate and initialise the classdev and
 * then add it a later समय.  To करो this, call this routine क्रम
 * allocation and initialisation and then use
 * attribute_container_device_trigger() to call device_add() on
 * it.  Note: after this, the class device contains a reference to dev
 * which is not relinquished until the release of the classdev.
 */
व्योम
attribute_container_add_device(काष्ठा device *dev,
			       पूर्णांक (*fn)(काष्ठा attribute_container *,
					 काष्ठा device *,
					 काष्ठा device *))
अणु
	काष्ठा attribute_container *cont;

	mutex_lock(&attribute_container_mutex);
	list_क्रम_each_entry(cont, &attribute_container_list, node) अणु
		काष्ठा पूर्णांकernal_container *ic;

		अगर (attribute_container_no_classdevs(cont))
			जारी;

		अगर (!cont->match(cont, dev))
			जारी;

		ic = kzalloc(माप(*ic), GFP_KERNEL);
		अगर (!ic) अणु
			dev_err(dev, "failed to allocate class container\n");
			जारी;
		पूर्ण

		ic->cont = cont;
		device_initialize(&ic->classdev);
		ic->classdev.parent = get_device(dev);
		ic->classdev.class = cont->class;
		cont->class->dev_release = attribute_container_release;
		dev_set_name(&ic->classdev, "%s", dev_name(dev));
		अगर (fn)
			fn(cont, dev, &ic->classdev);
		अन्यथा
			attribute_container_add_class_device(&ic->classdev);
		klist_add_tail(&ic->node, &cont->containers);
	पूर्ण
	mutex_unlock(&attribute_container_mutex);
पूर्ण

/* FIXME: can't अवरोध out of this unless klist_iter_निकास is also
 * called beक्रमe करोing the अवरोध
 */
#घोषणा klist_क्रम_each_entry(pos, head, member, iter) \
	क्रम (klist_iter_init(head, iter); (pos = (अणु \
		काष्ठा klist_node *n = klist_next(iter); \
		n ? container_of(n, typeof(*pos), member) : \
			(अणु klist_iter_निकास(iter) ; शून्य; पूर्ण); \
	पूर्ण)) != शून्य;)


/**
 * attribute_container_हटाओ_device - make device eligible क्रम removal.
 *
 * @dev:  The generic device
 * @fn:	  A function to call to हटाओ the device
 *
 * This routine triggers device removal.  If fn is शून्य, then it is
 * simply करोne via device_unरेजिस्टर (note that अगर something
 * still has a reference to the classdev, then the memory occupied
 * will not be मुक्तd until the classdev is released).  If you want a
 * two phase release: हटाओ from visibility and then delete the
 * device, then you should use this routine with a fn that calls
 * device_del() and then use attribute_container_device_trigger()
 * to करो the final put on the classdev.
 */
व्योम
attribute_container_हटाओ_device(काष्ठा device *dev,
				  व्योम (*fn)(काष्ठा attribute_container *,
					     काष्ठा device *,
					     काष्ठा device *))
अणु
	काष्ठा attribute_container *cont;

	mutex_lock(&attribute_container_mutex);
	list_क्रम_each_entry(cont, &attribute_container_list, node) अणु
		काष्ठा पूर्णांकernal_container *ic;
		काष्ठा klist_iter iter;

		अगर (attribute_container_no_classdevs(cont))
			जारी;

		अगर (!cont->match(cont, dev))
			जारी;

		klist_क्रम_each_entry(ic, &cont->containers, node, &iter) अणु
			अगर (dev != ic->classdev.parent)
				जारी;
			klist_del(&ic->node);
			अगर (fn)
				fn(cont, dev, &ic->classdev);
			अन्यथा अणु
				attribute_container_हटाओ_attrs(&ic->classdev);
				device_unरेजिस्टर(&ic->classdev);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&attribute_container_mutex);
पूर्ण

अटल पूर्णांक
करो_attribute_container_device_trigger_safe(काष्ठा device *dev,
					   काष्ठा attribute_container *cont,
					   पूर्णांक (*fn)(काष्ठा attribute_container *,
						     काष्ठा device *, काष्ठा device *),
					   पूर्णांक (*unकरो)(काष्ठा attribute_container *,
						       काष्ठा device *, काष्ठा device *))
अणु
	पूर्णांक ret;
	काष्ठा पूर्णांकernal_container *ic, *failed;
	काष्ठा klist_iter iter;

	अगर (attribute_container_no_classdevs(cont))
		वापस fn(cont, dev, शून्य);

	klist_क्रम_each_entry(ic, &cont->containers, node, &iter) अणु
		अगर (dev == ic->classdev.parent) अणु
			ret = fn(cont, dev, &ic->classdev);
			अगर (ret) अणु
				failed = ic;
				klist_iter_निकास(&iter);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

fail:
	अगर (!unकरो)
		वापस ret;

	/* Attempt to unकरो the work partially करोne. */
	klist_क्रम_each_entry(ic, &cont->containers, node, &iter) अणु
		अगर (ic == failed) अणु
			klist_iter_निकास(&iter);
			अवरोध;
		पूर्ण
		अगर (dev == ic->classdev.parent)
			unकरो(cont, dev, &ic->classdev);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * attribute_container_device_trigger_safe - execute a trigger क्रम each
 * matching classdev or fail all of them.
 *
 * @dev:  The generic device to run the trigger क्रम
 * @fn	  the function to execute क्रम each classdev.
 * @unकरो  A function to unकरो the work previously करोne in हाल of error
 *
 * This function is a safe version of
 * attribute_container_device_trigger. It stops on the first error and
 * unकरो the partial work that has been करोne, on previous classdev.  It
 * is guaranteed that either they all succeeded, or none of them
 * succeeded.
 */
पूर्णांक
attribute_container_device_trigger_safe(काष्ठा device *dev,
					पूर्णांक (*fn)(काष्ठा attribute_container *,
						  काष्ठा device *,
						  काष्ठा device *),
					पूर्णांक (*unकरो)(काष्ठा attribute_container *,
						    काष्ठा device *,
						    काष्ठा device *))
अणु
	काष्ठा attribute_container *cont, *failed = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&attribute_container_mutex);

	list_क्रम_each_entry(cont, &attribute_container_list, node) अणु

		अगर (!cont->match(cont, dev))
			जारी;

		ret = करो_attribute_container_device_trigger_safe(dev, cont,
								 fn, unकरो);
		अगर (ret) अणु
			failed = cont;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret && !WARN_ON(!unकरो)) अणु
		list_क्रम_each_entry(cont, &attribute_container_list, node) अणु

			अगर (failed == cont)
				अवरोध;

			अगर (!cont->match(cont, dev))
				जारी;

			करो_attribute_container_device_trigger_safe(dev, cont,
								   unकरो, शून्य);
		पूर्ण
	पूर्ण

	mutex_unlock(&attribute_container_mutex);
	वापस ret;

पूर्ण

/**
 * attribute_container_device_trigger - execute a trigger क्रम each matching classdev
 *
 * @dev:  The generic device to run the trigger क्रम
 * @fn	  the function to execute क्रम each classdev.
 *
 * This function is क्रम executing a trigger when you need to know both
 * the container and the classdev.  If you only care about the
 * container, then use attribute_container_trigger() instead.
 */
व्योम
attribute_container_device_trigger(काष्ठा device *dev,
				   पूर्णांक (*fn)(काष्ठा attribute_container *,
					     काष्ठा device *,
					     काष्ठा device *))
अणु
	काष्ठा attribute_container *cont;

	mutex_lock(&attribute_container_mutex);
	list_क्रम_each_entry(cont, &attribute_container_list, node) अणु
		काष्ठा पूर्णांकernal_container *ic;
		काष्ठा klist_iter iter;

		अगर (!cont->match(cont, dev))
			जारी;

		अगर (attribute_container_no_classdevs(cont)) अणु
			fn(cont, dev, शून्य);
			जारी;
		पूर्ण

		klist_क्रम_each_entry(ic, &cont->containers, node, &iter) अणु
			अगर (dev == ic->classdev.parent)
				fn(cont, dev, &ic->classdev);
		पूर्ण
	पूर्ण
	mutex_unlock(&attribute_container_mutex);
पूर्ण

/**
 * attribute_container_trigger - trigger a function क्रम each matching container
 *
 * @dev:  The generic device to activate the trigger क्रम
 * @fn:	  the function to trigger
 *
 * This routine triggers a function that only needs to know the
 * matching containers (not the classdev) associated with a device.
 * It is more lightweight than attribute_container_device_trigger, so
 * should be used in preference unless the triggering function
 * actually needs to know the classdev.
 */
व्योम
attribute_container_trigger(काष्ठा device *dev,
			    पूर्णांक (*fn)(काष्ठा attribute_container *,
				      काष्ठा device *))
अणु
	काष्ठा attribute_container *cont;

	mutex_lock(&attribute_container_mutex);
	list_क्रम_each_entry(cont, &attribute_container_list, node) अणु
		अगर (cont->match(cont, dev))
			fn(cont, dev);
	पूर्ण
	mutex_unlock(&attribute_container_mutex);
पूर्ण

/**
 * attribute_container_add_attrs - add attributes
 *
 * @classdev: The class device
 *
 * This simply creates all the class device sysfs files from the
 * attributes listed in the container
 */
पूर्णांक
attribute_container_add_attrs(काष्ठा device *classdev)
अणु
	काष्ठा attribute_container *cont =
		attribute_container_classdev_to_container(classdev);
	काष्ठा device_attribute **attrs = cont->attrs;
	पूर्णांक i, error;

	BUG_ON(attrs && cont->grp);

	अगर (!attrs && !cont->grp)
		वापस 0;

	अगर (cont->grp)
		वापस sysfs_create_group(&classdev->kobj, cont->grp);

	क्रम (i = 0; attrs[i]; i++) अणु
		sysfs_attr_init(&attrs[i]->attr);
		error = device_create_file(classdev, attrs[i]);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * attribute_container_add_class_device - same function as device_add
 *
 * @classdev:	the class device to add
 *
 * This perक्रमms essentially the same function as device_add except क्रम
 * attribute containers, namely add the classdev to the प्रणाली and then
 * create the attribute files
 */
पूर्णांक
attribute_container_add_class_device(काष्ठा device *classdev)
अणु
	पूर्णांक error = device_add(classdev);

	अगर (error)
		वापस error;
	वापस attribute_container_add_attrs(classdev);
पूर्ण

/**
 * attribute_container_add_class_device_adapter - simple adapter क्रम triggers
 *
 * @cont: the container to रेजिस्टर.
 * @dev:  the generic device to activate the trigger क्रम
 * @classdev:	the class device to add
 *
 * This function is identical to attribute_container_add_class_device except
 * that it is deचिन्हित to be called from the triggers
 */
पूर्णांक
attribute_container_add_class_device_adapter(काष्ठा attribute_container *cont,
					     काष्ठा device *dev,
					     काष्ठा device *classdev)
अणु
	वापस attribute_container_add_class_device(classdev);
पूर्ण

/**
 * attribute_container_हटाओ_attrs - हटाओ any attribute files
 *
 * @classdev: The class device to हटाओ the files from
 *
 */
व्योम
attribute_container_हटाओ_attrs(काष्ठा device *classdev)
अणु
	काष्ठा attribute_container *cont =
		attribute_container_classdev_to_container(classdev);
	काष्ठा device_attribute **attrs = cont->attrs;
	पूर्णांक i;

	अगर (!attrs && !cont->grp)
		वापस;

	अगर (cont->grp) अणु
		sysfs_हटाओ_group(&classdev->kobj, cont->grp);
		वापस ;
	पूर्ण

	क्रम (i = 0; attrs[i]; i++)
		device_हटाओ_file(classdev, attrs[i]);
पूर्ण

/**
 * attribute_container_class_device_del - equivalent of class_device_del
 *
 * @classdev: the class device
 *
 * This function simply हटाओs all the attribute files and then calls
 * device_del.
 */
व्योम
attribute_container_class_device_del(काष्ठा device *classdev)
अणु
	attribute_container_हटाओ_attrs(classdev);
	device_del(classdev);
पूर्ण

/**
 * attribute_container_find_class_device - find the corresponding class_device
 *
 * @cont:	the container
 * @dev:	the generic device
 *
 * Looks up the device in the container's list of class devices and वापसs
 * the corresponding class_device.
 */
काष्ठा device *
attribute_container_find_class_device(काष्ठा attribute_container *cont,
				      काष्ठा device *dev)
अणु
	काष्ठा device *cdev = शून्य;
	काष्ठा पूर्णांकernal_container *ic;
	काष्ठा klist_iter iter;

	klist_क्रम_each_entry(ic, &cont->containers, node, &iter) अणु
		अगर (ic->classdev.parent == dev) अणु
			cdev = &ic->classdev;
			/* FIXME: must निकास iterator then अवरोध */
			klist_iter_निकास(&iter);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cdev;
पूर्ण
EXPORT_SYMBOL_GPL(attribute_container_find_class_device);
