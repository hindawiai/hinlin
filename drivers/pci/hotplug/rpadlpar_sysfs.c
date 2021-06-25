<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Interface क्रम Dynamic Logical Partitioning of I/O Slots on
 * RPA-compliant PPC64 platक्रमm.
 *
 * John Rose <johnrose@austin.ibm.com>
 * October 2003
 *
 * Copyright (C) 2003 IBM.
 */
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश "rpaphp.h"
#समावेश "rpadlpar.h"
#समावेश "../pci.h"

#घोषणा DLPAR_KOBJ_NAME       "control"

/* Those two have no quotes because they are passed to __ATTR() which
 * stringअगरies the argument (yuck !)
 */
#घोषणा ADD_SLOT_ATTR_NAME    add_slot
#घोषणा REMOVE_SLOT_ATTR_NAME हटाओ_slot

अटल sमाप_प्रकार add_slot_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार nbytes)
अणु
	अक्षर drc_name[MAX_DRC_NAME_LEN];
	अक्षर *end;
	पूर्णांक rc;

	अगर (nbytes >= MAX_DRC_NAME_LEN)
		वापस 0;

	strscpy(drc_name, buf, nbytes + 1);

	end = म_अक्षर(drc_name, '\n');
	अगर (end)
		*end = '\0';

	rc = dlpar_add_slot(drc_name);
	अगर (rc)
		वापस rc;

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार add_slot_show(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार हटाओ_slot_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार nbytes)
अणु
	अक्षर drc_name[MAX_DRC_NAME_LEN];
	पूर्णांक rc;
	अक्षर *end;

	अगर (nbytes >= MAX_DRC_NAME_LEN)
		वापस 0;

	strscpy(drc_name, buf, nbytes + 1);

	end = म_अक्षर(drc_name, '\n');
	अगर (end)
		*end = '\0';

	rc = dlpar_हटाओ_slot(drc_name);
	अगर (rc)
		वापस rc;

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार हटाओ_slot_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल काष्ठा kobj_attribute add_slot_attr =
	__ATTR(ADD_SLOT_ATTR_NAME, 0644, add_slot_show, add_slot_store);

अटल काष्ठा kobj_attribute हटाओ_slot_attr =
	__ATTR(REMOVE_SLOT_ATTR_NAME, 0644, हटाओ_slot_show, हटाओ_slot_store);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&add_slot_attr.attr,
	&हटाओ_slot_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dlpar_attr_group = अणु
	.attrs = शेष_attrs,
पूर्ण;

अटल काष्ठा kobject *dlpar_kobj;

पूर्णांक dlpar_sysfs_init(व्योम)
अणु
	पूर्णांक error;

	dlpar_kobj = kobject_create_and_add(DLPAR_KOBJ_NAME,
					    &pci_slots_kset->kobj);
	अगर (!dlpar_kobj)
		वापस -EINVAL;

	error = sysfs_create_group(dlpar_kobj, &dlpar_attr_group);
	अगर (error)
		kobject_put(dlpar_kobj);
	वापस error;
पूर्ण

व्योम dlpar_sysfs_निकास(व्योम)
अणु
	sysfs_हटाओ_group(dlpar_kobj, &dlpar_attr_group);
	kobject_put(dlpar_kobj);
पूर्ण
