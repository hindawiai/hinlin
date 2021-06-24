<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * transport_class.c - implementation of generic transport classes
 *                     using attribute_containers
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 *
 * The basic idea here is to allow any "device controller" (which
 * would most often be a Host Bus Adapter to use the services of one
 * or more tranport classes क्रम perक्रमming transport specअगरic
 * services.  Transport specअगरic services are things that the generic
 * command layer करोesn't want to know about (speed settings, line
 * condidtioning, etc), but which the user might be पूर्णांकerested in.
 * Thus, the HBA's use the routines exported by the transport classes
 * to perक्रमm these functions.  The transport classes export certain
 * values to the user via sysfs using attribute containers.
 *
 * Note: because not every HBA will care about every transport
 * attribute, there's a many to one relationship that goes like this:
 *
 * transport class<-----attribute container<----class device
 *
 * Usually the attribute container is per-HBA, but the design करोesn't
 * mandate that.  Although most of the services will be specअगरic to
 * the actual बाह्यal storage connection used by the HBA, the generic
 * transport class is framed entirely in terms of generic devices to
 * allow it to be used by any physical HBA in the प्रणाली.
 */
#समावेश <linux/export.h>
#समावेश <linux/attribute_container.h>
#समावेश <linux/transport_class.h>

अटल पूर्णांक transport_हटाओ_classdev(काष्ठा attribute_container *cont,
				     काष्ठा device *dev,
				     काष्ठा device *classdev);

/**
 * transport_class_रेजिस्टर - रेजिस्टर an initial transport class
 *
 * @tclass:	a poपूर्णांकer to the transport class काष्ठाure to be initialised
 *
 * The transport class contains an embedded class which is used to
 * identअगरy it.  The caller should initialise this काष्ठाure with
 * zeros and then generic class must have been initialised with the
 * actual transport class unique name.  There's a macro
 * DECLARE_TRANSPORT_CLASS() to करो this (declared classes still must
 * be रेजिस्टरed).
 *
 * Returns 0 on success or error on failure.
 */
पूर्णांक transport_class_रेजिस्टर(काष्ठा transport_class *tclass)
अणु
	वापस class_रेजिस्टर(&tclass->class);
पूर्ण
EXPORT_SYMBOL_GPL(transport_class_रेजिस्टर);

/**
 * transport_class_unरेजिस्टर - unरेजिस्टर a previously रेजिस्टरed class
 *
 * @tclass: The transport class to unरेजिस्टर
 *
 * Must be called prior to deallocating the memory क्रम the transport
 * class.
 */
व्योम transport_class_unरेजिस्टर(काष्ठा transport_class *tclass)
अणु
	class_unरेजिस्टर(&tclass->class);
पूर्ण
EXPORT_SYMBOL_GPL(transport_class_unरेजिस्टर);

अटल पूर्णांक anon_transport_dummy_function(काष्ठा transport_container *tc,
					 काष्ठा device *dev,
					 काष्ठा device *cdev)
अणु
	/* करो nothing */
	वापस 0;
पूर्ण

/**
 * anon_transport_class_रेजिस्टर - रेजिस्टर an anonymous class
 *
 * @atc: The anon transport class to रेजिस्टर
 *
 * The anonymous transport class contains both a transport class and a
 * container.  The idea of an anonymous class is that it never
 * actually has any device attributes associated with it (and thus
 * saves on container storage).  So it can only be used क्रम triggering
 * events.  Use prezero and then use DECLARE_ANON_TRANSPORT_CLASS() to
 * initialise the anon transport class storage.
 */
पूर्णांक anon_transport_class_रेजिस्टर(काष्ठा anon_transport_class *atc)
अणु
	पूर्णांक error;
	atc->container.class = &atc->tclass.class;
	attribute_container_set_no_classdevs(&atc->container);
	error = attribute_container_रेजिस्टर(&atc->container);
	अगर (error)
		वापस error;
	atc->tclass.setup = anon_transport_dummy_function;
	atc->tclass.हटाओ = anon_transport_dummy_function;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(anon_transport_class_रेजिस्टर);

/**
 * anon_transport_class_unरेजिस्टर - unरेजिस्टर an anon class
 *
 * @atc: Poपूर्णांकer to the anon transport class to unरेजिस्टर
 *
 * Must be called prior to deallocating the memory क्रम the anon
 * transport class.
 */
व्योम anon_transport_class_unरेजिस्टर(काष्ठा anon_transport_class *atc)
अणु
	अगर (unlikely(attribute_container_unरेजिस्टर(&atc->container)))
		BUG();
पूर्ण
EXPORT_SYMBOL_GPL(anon_transport_class_unरेजिस्टर);

अटल पूर्णांक transport_setup_classdev(काष्ठा attribute_container *cont,
				    काष्ठा device *dev,
				    काष्ठा device *classdev)
अणु
	काष्ठा transport_class *tclass = class_to_transport_class(cont->class);
	काष्ठा transport_container *tcont = attribute_container_to_transport_container(cont);

	अगर (tclass->setup)
		tclass->setup(tcont, dev, classdev);

	वापस 0;
पूर्ण

/**
 * transport_setup_device - declare a new dev क्रम transport class association but करोn't make it visible yet.
 * @dev: the generic device representing the entity being added
 *
 * Usually, dev represents some component in the HBA प्रणाली (either
 * the HBA itself or a device remote across the HBA bus).  This
 * routine is simply a trigger poपूर्णांक to see अगर any set of transport
 * classes wishes to associate with the added device.  This allocates
 * storage क्रम the class device and initialises it, but करोes not yet
 * add it to the प्रणाली or add attributes to it (you करो this with
 * transport_add_device).  If you have no need क्रम a separate setup
 * and add operations, use transport_रेजिस्टर_device (see
 * transport_class.h).
 */

व्योम transport_setup_device(काष्ठा device *dev)
अणु
	attribute_container_add_device(dev, transport_setup_classdev);
पूर्ण
EXPORT_SYMBOL_GPL(transport_setup_device);

अटल पूर्णांक transport_add_class_device(काष्ठा attribute_container *cont,
				      काष्ठा device *dev,
				      काष्ठा device *classdev)
अणु
	पूर्णांक error = attribute_container_add_class_device(classdev);
	काष्ठा transport_container *tcont = 
		attribute_container_to_transport_container(cont);

	अगर (!error && tcont->statistics)
		error = sysfs_create_group(&classdev->kobj, tcont->statistics);

	वापस error;
पूर्ण


/**
 * transport_add_device - declare a new dev क्रम transport class association
 *
 * @dev: the generic device representing the entity being added
 *
 * Usually, dev represents some component in the HBA प्रणाली (either
 * the HBA itself or a device remote across the HBA bus).  This
 * routine is simply a trigger poपूर्णांक used to add the device to the
 * प्रणाली and रेजिस्टर attributes क्रम it.
 */
पूर्णांक transport_add_device(काष्ठा device *dev)
अणु
	वापस attribute_container_device_trigger_safe(dev,
					transport_add_class_device,
					transport_हटाओ_classdev);
पूर्ण
EXPORT_SYMBOL_GPL(transport_add_device);

अटल पूर्णांक transport_configure(काष्ठा attribute_container *cont,
			       काष्ठा device *dev,
			       काष्ठा device *cdev)
अणु
	काष्ठा transport_class *tclass = class_to_transport_class(cont->class);
	काष्ठा transport_container *tcont = attribute_container_to_transport_container(cont);

	अगर (tclass->configure)
		tclass->configure(tcont, dev, cdev);

	वापस 0;
पूर्ण

/**
 * transport_configure_device - configure an alपढ़ोy set up device
 *
 * @dev: generic device representing device to be configured
 *
 * The idea of configure is simply to provide a poपूर्णांक within the setup
 * process to allow the transport class to extract inक्रमmation from a
 * device after it has been setup.  This is used in SCSI because we
 * have to have a setup device to begin using the HBA, but after we
 * send the initial inquiry, we use configure to extract the device
 * parameters.  The device need not have been added to be configured.
 */
व्योम transport_configure_device(काष्ठा device *dev)
अणु
	attribute_container_device_trigger(dev, transport_configure);
पूर्ण
EXPORT_SYMBOL_GPL(transport_configure_device);

अटल पूर्णांक transport_हटाओ_classdev(काष्ठा attribute_container *cont,
				     काष्ठा device *dev,
				     काष्ठा device *classdev)
अणु
	काष्ठा transport_container *tcont = 
		attribute_container_to_transport_container(cont);
	काष्ठा transport_class *tclass = class_to_transport_class(cont->class);

	अगर (tclass->हटाओ)
		tclass->हटाओ(tcont, dev, classdev);

	अगर (tclass->हटाओ != anon_transport_dummy_function) अणु
		अगर (tcont->statistics)
			sysfs_हटाओ_group(&classdev->kobj, tcont->statistics);
		attribute_container_class_device_del(classdev);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * transport_हटाओ_device - हटाओ the visibility of a device
 *
 * @dev: generic device to हटाओ
 *
 * This call हटाओs the visibility of the device (to the user from
 * sysfs), but करोes not destroy it.  To eliminate a device entirely
 * you must also call transport_destroy_device.  If you करोn't need to
 * करो हटाओ and destroy as separate operations, use
 * transport_unरेजिस्टर_device() (see transport_class.h) which will
 * perक्रमm both calls क्रम you.
 */
व्योम transport_हटाओ_device(काष्ठा device *dev)
अणु
	attribute_container_device_trigger(dev, transport_हटाओ_classdev);
पूर्ण
EXPORT_SYMBOL_GPL(transport_हटाओ_device);

अटल व्योम transport_destroy_classdev(काष्ठा attribute_container *cont,
				      काष्ठा device *dev,
				      काष्ठा device *classdev)
अणु
	काष्ठा transport_class *tclass = class_to_transport_class(cont->class);

	अगर (tclass->हटाओ != anon_transport_dummy_function)
		put_device(classdev);
पूर्ण


/**
 * transport_destroy_device - destroy a हटाओd device
 *
 * @dev: device to eliminate from the transport class.
 *
 * This call triggers the elimination of storage associated with the
 * transport classdev.  Note: all it really करोes is relinquish a
 * reference to the classdev.  The memory will not be मुक्तd until the
 * last reference goes to zero.  Note also that the classdev retains a
 * reference count on dev, so dev too will reमुख्य क्रम as दीर्घ as the
 * transport class device reमुख्यs around.
 */
व्योम transport_destroy_device(काष्ठा device *dev)
अणु
	attribute_container_हटाओ_device(dev, transport_destroy_classdev);
पूर्ण
EXPORT_SYMBOL_GPL(transport_destroy_device);
