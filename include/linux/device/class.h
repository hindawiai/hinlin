<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The class-specअगरic portions of the driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (c) 2004-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2008-2009 Novell Inc.
 * Copyright (c) 2012-2019 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 * Copyright (c) 2012-2019 Linux Foundation
 *
 * See Documentation/driver-api/driver-model/ क्रम more inक्रमmation.
 */

#अगर_अघोषित _DEVICE_CLASS_H_
#घोषणा _DEVICE_CLASS_H_

#समावेश <linux/kobject.h>
#समावेश <linux/klist.h>
#समावेश <linux/pm.h>
#समावेश <linux/device/bus.h>

काष्ठा device;
काष्ठा fwnode_handle;

/**
 * काष्ठा class - device classes
 * @name:	Name of the class.
 * @owner:	The module owner.
 * @class_groups: Default attributes of this class.
 * @dev_groups:	Default attributes of the devices that beदीर्घ to the class.
 * @dev_kobj:	The kobject that represents this class and links it पूर्णांकo the hierarchy.
 * @dev_uevent:	Called when a device is added, हटाओd from this class, or a
 *		few other things that generate uevents to add the environment
 *		variables.
 * @devnode:	Callback to provide the devपंचांगpfs.
 * @class_release: Called to release this class.
 * @dev_release: Called to release the device.
 * @shutकरोwn_pre: Called at shut-करोwn समय beक्रमe driver shutकरोwn.
 * @ns_type:	Callbacks so sysfs can detemine namespaces.
 * @namespace:	Namespace of the device beदीर्घs to this class.
 * @get_ownership: Allows class to specअगरy uid/gid of the sysfs directories
 *		क्रम the devices beदीर्घing to the class. Usually tied to
 *		device's namespace.
 * @pm:		The शेष device घातer management operations of this class.
 * @p:		The निजी data of the driver core, no one other than the
 *		driver core can touch this.
 *
 * A class is a higher-level view of a device that असलtracts out low-level
 * implementation details. Drivers may see a SCSI disk or an ATA disk, but,
 * at the class level, they are all simply disks. Classes allow user space
 * to work with devices based on what they करो, rather than how they are
 * connected or how they work.
 */
काष्ठा class अणु
	स्थिर अक्षर		*name;
	काष्ठा module		*owner;

	स्थिर काष्ठा attribute_group	**class_groups;
	स्थिर काष्ठा attribute_group	**dev_groups;
	काष्ठा kobject			*dev_kobj;

	पूर्णांक (*dev_uevent)(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);
	अक्षर *(*devnode)(काष्ठा device *dev, umode_t *mode);

	व्योम (*class_release)(काष्ठा class *class);
	व्योम (*dev_release)(काष्ठा device *dev);

	पूर्णांक (*shutकरोwn_pre)(काष्ठा device *dev);

	स्थिर काष्ठा kobj_ns_type_operations *ns_type;
	स्थिर व्योम *(*namespace)(काष्ठा device *dev);

	व्योम (*get_ownership)(काष्ठा device *dev, kuid_t *uid, kgid_t *gid);

	स्थिर काष्ठा dev_pm_ops *pm;

	काष्ठा subsys_निजी *p;
पूर्ण;

काष्ठा class_dev_iter अणु
	काष्ठा klist_iter		ki;
	स्थिर काष्ठा device_type	*type;
पूर्ण;

बाह्य काष्ठा kobject *sysfs_dev_block_kobj;
बाह्य काष्ठा kobject *sysfs_dev_अक्षर_kobj;
बाह्य पूर्णांक __must_check __class_रेजिस्टर(काष्ठा class *class,
					 काष्ठा lock_class_key *key);
बाह्य व्योम class_unरेजिस्टर(काष्ठा class *class);

/* This is a #घोषणा to keep the compiler from merging dअगरferent
 * instances of the __key variable */
#घोषणा class_रेजिस्टर(class)			\
(अणु						\
	अटल काष्ठा lock_class_key __key;	\
	__class_रेजिस्टर(class, &__key);	\
पूर्ण)

काष्ठा class_compat;
काष्ठा class_compat *class_compat_रेजिस्टर(स्थिर अक्षर *name);
व्योम class_compat_unरेजिस्टर(काष्ठा class_compat *cls);
पूर्णांक class_compat_create_link(काष्ठा class_compat *cls, काष्ठा device *dev,
			     काष्ठा device *device_link);
व्योम class_compat_हटाओ_link(काष्ठा class_compat *cls, काष्ठा device *dev,
			      काष्ठा device *device_link);

बाह्य व्योम class_dev_iter_init(काष्ठा class_dev_iter *iter,
				काष्ठा class *class,
				काष्ठा device *start,
				स्थिर काष्ठा device_type *type);
बाह्य काष्ठा device *class_dev_iter_next(काष्ठा class_dev_iter *iter);
बाह्य व्योम class_dev_iter_निकास(काष्ठा class_dev_iter *iter);

बाह्य पूर्णांक class_क्रम_each_device(काष्ठा class *class, काष्ठा device *start,
				 व्योम *data,
				 पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));
बाह्य काष्ठा device *class_find_device(काष्ठा class *class,
					काष्ठा device *start, स्थिर व्योम *data,
					पूर्णांक (*match)(काष्ठा device *, स्थिर व्योम *));

/**
 * class_find_device_by_name - device iterator क्रम locating a particular device
 * of a specअगरic name.
 * @class: class type
 * @name: name of the device to match
 */
अटल अंतरभूत काष्ठा device *class_find_device_by_name(काष्ठा class *class,
						       स्थिर अक्षर *name)
अणु
	वापस class_find_device(class, शून्य, name, device_match_name);
पूर्ण

/**
 * class_find_device_by_of_node : device iterator क्रम locating a particular device
 * matching the of_node.
 * @class: class type
 * @np: of_node of the device to match.
 */
अटल अंतरभूत काष्ठा device *
class_find_device_by_of_node(काष्ठा class *class, स्थिर काष्ठा device_node *np)
अणु
	वापस class_find_device(class, शून्य, np, device_match_of_node);
पूर्ण

/**
 * class_find_device_by_fwnode : device iterator क्रम locating a particular device
 * matching the fwnode.
 * @class: class type
 * @fwnode: fwnode of the device to match.
 */
अटल अंतरभूत काष्ठा device *
class_find_device_by_fwnode(काष्ठा class *class,
			    स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस class_find_device(class, शून्य, fwnode, device_match_fwnode);
पूर्ण

/**
 * class_find_device_by_devt : device iterator क्रम locating a particular device
 * matching the device type.
 * @class: class type
 * @devt: device type of the device to match.
 */
अटल अंतरभूत काष्ठा device *class_find_device_by_devt(काष्ठा class *class,
						       dev_t devt)
अणु
	वापस class_find_device(class, शून्य, &devt, device_match_devt);
पूर्ण

#अगर_घोषित CONFIG_ACPI
काष्ठा acpi_device;
/**
 * class_find_device_by_acpi_dev : device iterator क्रम locating a particular
 * device matching the ACPI_COMPANION device.
 * @class: class type
 * @adev: ACPI_COMPANION device to match.
 */
अटल अंतरभूत काष्ठा device *
class_find_device_by_acpi_dev(काष्ठा class *class, स्थिर काष्ठा acpi_device *adev)
अणु
	वापस class_find_device(class, शून्य, adev, device_match_acpi_dev);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा device *
class_find_device_by_acpi_dev(काष्ठा class *class, स्थिर व्योम *adev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

काष्ठा class_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा class *class, काष्ठा class_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा class *class, काष्ठा class_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा CLASS_ATTR_RW(_name) \
	काष्ठा class_attribute class_attr_##_name = __ATTR_RW(_name)
#घोषणा CLASS_ATTR_RO(_name) \
	काष्ठा class_attribute class_attr_##_name = __ATTR_RO(_name)
#घोषणा CLASS_ATTR_WO(_name) \
	काष्ठा class_attribute class_attr_##_name = __ATTR_WO(_name)

बाह्य पूर्णांक __must_check class_create_file_ns(काष्ठा class *class,
					     स्थिर काष्ठा class_attribute *attr,
					     स्थिर व्योम *ns);
बाह्य व्योम class_हटाओ_file_ns(काष्ठा class *class,
				 स्थिर काष्ठा class_attribute *attr,
				 स्थिर व्योम *ns);

अटल अंतरभूत पूर्णांक __must_check class_create_file(काष्ठा class *class,
					स्थिर काष्ठा class_attribute *attr)
अणु
	वापस class_create_file_ns(class, attr, शून्य);
पूर्ण

अटल अंतरभूत व्योम class_हटाओ_file(काष्ठा class *class,
				     स्थिर काष्ठा class_attribute *attr)
अणु
	वापस class_हटाओ_file_ns(class, attr, शून्य);
पूर्ण

/* Simple class attribute that is just a अटल string */
काष्ठा class_attribute_string अणु
	काष्ठा class_attribute attr;
	अक्षर *str;
पूर्ण;

/* Currently पढ़ो-only only */
#घोषणा _CLASS_ATTR_STRING(_name, _mode, _str) \
	अणु __ATTR(_name, _mode, show_class_attr_string, शून्य), _str पूर्ण
#घोषणा CLASS_ATTR_STRING(_name, _mode, _str) \
	काष्ठा class_attribute_string class_attr_##_name = \
		_CLASS_ATTR_STRING(_name, _mode, _str)

बाह्य sमाप_प्रकार show_class_attr_string(काष्ठा class *class, काष्ठा class_attribute *attr,
                        अक्षर *buf);

काष्ठा class_पूर्णांकerface अणु
	काष्ठा list_head	node;
	काष्ठा class		*class;

	पूर्णांक (*add_dev)		(काष्ठा device *, काष्ठा class_पूर्णांकerface *);
	व्योम (*हटाओ_dev)	(काष्ठा device *, काष्ठा class_पूर्णांकerface *);
पूर्ण;

बाह्य पूर्णांक __must_check class_पूर्णांकerface_रेजिस्टर(काष्ठा class_पूर्णांकerface *);
बाह्य व्योम class_पूर्णांकerface_unरेजिस्टर(काष्ठा class_पूर्णांकerface *);

बाह्य काष्ठा class * __must_check __class_create(काष्ठा module *owner,
						  स्थिर अक्षर *name,
						  काष्ठा lock_class_key *key);
बाह्य व्योम class_destroy(काष्ठा class *cls);

/* This is a #घोषणा to keep the compiler from merging dअगरferent
 * instances of the __key variable */

/**
 * class_create - create a काष्ठा class काष्ठाure
 * @owner: poपूर्णांकer to the module that is to "own" this काष्ठा class
 * @name: poपूर्णांकer to a string क्रम the name of this class.
 *
 * This is used to create a काष्ठा class poपूर्णांकer that can then be used
 * in calls to device_create().
 *
 * Returns &काष्ठा class poपूर्णांकer on success, or ERR_PTR() on error.
 *
 * Note, the poपूर्णांकer created here is to be destroyed when finished by
 * making a call to class_destroy().
 */
#घोषणा class_create(owner, name)		\
(अणु						\
	अटल काष्ठा lock_class_key __key;	\
	__class_create(owner, name, &__key);	\
पूर्ण)


#पूर्ण_अगर	/* _DEVICE_CLASS_H_ */
