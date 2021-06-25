<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * module.c - module sysfs fun क्रम drivers
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "base.h"

अटल अक्षर *make_driver_name(काष्ठा device_driver *drv)
अणु
	अक्षर *driver_name;

	driver_name = kaप्र_लिखो(GFP_KERNEL, "%s:%s", drv->bus->name, drv->name);
	अगर (!driver_name)
		वापस शून्य;

	वापस driver_name;
पूर्ण

अटल व्योम module_create_drivers_dir(काष्ठा module_kobject *mk)
अणु
	अटल DEFINE_MUTEX(drivers_dir_mutex);

	mutex_lock(&drivers_dir_mutex);
	अगर (mk && !mk->drivers_dir)
		mk->drivers_dir = kobject_create_and_add("drivers", &mk->kobj);
	mutex_unlock(&drivers_dir_mutex);
पूर्ण

व्योम module_add_driver(काष्ठा module *mod, काष्ठा device_driver *drv)
अणु
	अक्षर *driver_name;
	पूर्णांक no_warn;
	काष्ठा module_kobject *mk = शून्य;

	अगर (!drv)
		वापस;

	अगर (mod)
		mk = &mod->mkobj;
	अन्यथा अगर (drv->mod_name) अणु
		काष्ठा kobject *mkobj;

		/* Lookup built-in module entry in /sys/modules */
		mkobj = kset_find_obj(module_kset, drv->mod_name);
		अगर (mkobj) अणु
			mk = container_of(mkobj, काष्ठा module_kobject, kobj);
			/* remember our module काष्ठाure */
			drv->p->mkobj = mk;
			/* kset_find_obj took a reference */
			kobject_put(mkobj);
		पूर्ण
	पूर्ण

	अगर (!mk)
		वापस;

	/* Don't check वापस codes; these calls are idempotent */
	no_warn = sysfs_create_link(&drv->p->kobj, &mk->kobj, "module");
	driver_name = make_driver_name(drv);
	अगर (driver_name) अणु
		module_create_drivers_dir(mk);
		no_warn = sysfs_create_link(mk->drivers_dir, &drv->p->kobj,
					    driver_name);
		kमुक्त(driver_name);
	पूर्ण
पूर्ण

व्योम module_हटाओ_driver(काष्ठा device_driver *drv)
अणु
	काष्ठा module_kobject *mk = शून्य;
	अक्षर *driver_name;

	अगर (!drv)
		वापस;

	sysfs_हटाओ_link(&drv->p->kobj, "module");

	अगर (drv->owner)
		mk = &drv->owner->mkobj;
	अन्यथा अगर (drv->p->mkobj)
		mk = drv->p->mkobj;
	अगर (mk && mk->drivers_dir) अणु
		driver_name = make_driver_name(drv);
		अगर (driver_name) अणु
			sysfs_हटाओ_link(mk->drivers_dir, driver_name);
			kमुक्त(driver_name);
		पूर्ण
	पूर्ण
पूर्ण
