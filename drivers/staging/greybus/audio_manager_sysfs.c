<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus operations
 *
 * Copyright 2015-2016 Google Inc.
 */

#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>

#समावेश "audio_manager.h"
#समावेश "audio_manager_private.h"

अटल sमाप_प्रकार manager_sysfs_add_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gb_audio_manager_module_descriptor desc = अणु अणु0पूर्ण पूर्ण;

	पूर्णांक num = माला_पूछो(buf,
			"name=%" GB_AUDIO_MANAGER_MODULE_NAME_LEN_SSCANF
			"s vid=%d pid=%d intf_id=%d i/p devices=0x%X o/p devices=0x%X",
			desc.name, &desc.vid, &desc.pid, &desc.पूर्णांकf_id,
			&desc.ip_devices, &desc.op_devices);

	अगर (num != 7)
		वापस -EINVAL;

	num = gb_audio_manager_add(&desc);
	अगर (num < 0)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute manager_add_attribute =
	__ATTR(add, 0664, शून्य, manager_sysfs_add_store);

अटल sमाप_प्रकार manager_sysfs_हटाओ_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक id;

	पूर्णांक num = kstrtoपूर्णांक(buf, 10, &id);

	अगर (num != 1)
		वापस -EINVAL;

	num = gb_audio_manager_हटाओ(id);
	अगर (num)
		वापस num;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute manager_हटाओ_attribute =
	__ATTR(हटाओ, 0664, शून्य, manager_sysfs_हटाओ_store);

अटल sमाप_प्रकार manager_sysfs_dump_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक id;

	पूर्णांक num = kstrtoपूर्णांक(buf, 10, &id);

	अगर (num == 1) अणु
		num = gb_audio_manager_dump_module(id);
		अगर (num)
			वापस num;
	पूर्ण अन्यथा अगर (!म_भेदन("all", buf, 3)) अणु
		gb_audio_manager_dump_all();
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute manager_dump_attribute =
	__ATTR(dump, 0664, शून्य, manager_sysfs_dump_store);

अटल व्योम manager_sysfs_init_attribute(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *kattr)
अणु
	पूर्णांक err;

	err = sysfs_create_file(kobj, &kattr->attr);
	अगर (err) अणु
		pr_warn("creating the sysfs entry for %s failed: %d\n",
			kattr->attr.name, err);
	पूर्ण
पूर्ण

व्योम gb_audio_manager_sysfs_init(काष्ठा kobject *kobj)
अणु
	manager_sysfs_init_attribute(kobj, &manager_add_attribute);
	manager_sysfs_init_attribute(kobj, &manager_हटाओ_attribute);
	manager_sysfs_init_attribute(kobj, &manager_dump_attribute);
पूर्ण
