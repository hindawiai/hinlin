<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus operations
 *
 * Copyright 2015-2016 Google Inc.
 */

#समावेश <linux/slab.h>

#समावेश "audio_manager.h"
#समावेश "audio_manager_private.h"

#घोषणा to_gb_audio_module_attr(x)	\
		container_of(x, काष्ठा gb_audio_manager_module_attribute, attr)
#घोषणा to_gb_audio_module(x)		\
		container_of(x, काष्ठा gb_audio_manager_module, kobj)

काष्ठा gb_audio_manager_module_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा gb_audio_manager_module *module,
			काष्ठा gb_audio_manager_module_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा gb_audio_manager_module *module,
			 काष्ठा gb_audio_manager_module_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

अटल sमाप_प्रकार gb_audio_module_attr_show(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_audio_manager_module_attribute *attribute;
	काष्ठा gb_audio_manager_module *module;

	attribute = to_gb_audio_module_attr(attr);
	module = to_gb_audio_module(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(module, attribute, buf);
पूर्ण

अटल sमाप_प्रकार gb_audio_module_attr_store(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_audio_manager_module_attribute *attribute;
	काष्ठा gb_audio_manager_module *module;

	attribute = to_gb_audio_module_attr(attr);
	module = to_gb_audio_module(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(module, attribute, buf, len);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops gb_audio_module_sysfs_ops = अणु
	.show = gb_audio_module_attr_show,
	.store = gb_audio_module_attr_store,
पूर्ण;

अटल व्योम gb_audio_module_release(काष्ठा kobject *kobj)
अणु
	काष्ठा gb_audio_manager_module *module = to_gb_audio_module(kobj);

	pr_info("Destroying audio module #%d\n", module->id);
	/* TODO -> delete from list */
	kमुक्त(module);
पूर्ण

अटल sमाप_प्रकार gb_audio_module_name_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s", module->desc.name);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute gb_audio_module_name_attribute =
	__ATTR(name, 0664, gb_audio_module_name_show, शून्य);

अटल sमाप_प्रकार gb_audio_module_vid_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d", module->desc.vid);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute gb_audio_module_vid_attribute =
	__ATTR(vid, 0664, gb_audio_module_vid_show, शून्य);

अटल sमाप_प्रकार gb_audio_module_pid_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d", module->desc.pid);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute gb_audio_module_pid_attribute =
	__ATTR(pid, 0664, gb_audio_module_pid_show, शून्य);

अटल sमाप_प्रकार gb_audio_module_पूर्णांकf_id_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d", module->desc.पूर्णांकf_id);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute
					gb_audio_module_पूर्णांकf_id_attribute =
	__ATTR(पूर्णांकf_id, 0664, gb_audio_module_पूर्णांकf_id_show, शून्य);

अटल sमाप_प्रकार gb_audio_module_ip_devices_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%X", module->desc.ip_devices);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute
					gb_audio_module_ip_devices_attribute =
	__ATTR(ip_devices, 0664, gb_audio_module_ip_devices_show, शून्य);

अटल sमाप_प्रकार gb_audio_module_op_devices_show(
	काष्ठा gb_audio_manager_module *module,
	काष्ठा gb_audio_manager_module_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%X", module->desc.op_devices);
पूर्ण

अटल काष्ठा gb_audio_manager_module_attribute
					gb_audio_module_op_devices_attribute =
	__ATTR(op_devices, 0664, gb_audio_module_op_devices_show, शून्य);

अटल काष्ठा attribute *gb_audio_module_शेष_attrs[] = अणु
	&gb_audio_module_name_attribute.attr,
	&gb_audio_module_vid_attribute.attr,
	&gb_audio_module_pid_attribute.attr,
	&gb_audio_module_पूर्णांकf_id_attribute.attr,
	&gb_audio_module_ip_devices_attribute.attr,
	&gb_audio_module_op_devices_attribute.attr,
	शून्य,   /* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा kobj_type gb_audio_module_type = अणु
	.sysfs_ops = &gb_audio_module_sysfs_ops,
	.release = gb_audio_module_release,
	.शेष_attrs = gb_audio_module_शेष_attrs,
पूर्ण;

अटल व्योम send_add_uevent(काष्ठा gb_audio_manager_module *module)
अणु
	अक्षर name_string[128];
	अक्षर vid_string[64];
	अक्षर pid_string[64];
	अक्षर पूर्णांकf_id_string[64];
	अक्षर ip_devices_string[64];
	अक्षर op_devices_string[64];

	अक्षर *envp[] = अणु
		name_string,
		vid_string,
		pid_string,
		पूर्णांकf_id_string,
		ip_devices_string,
		op_devices_string,
		शून्य
	पूर्ण;

	snम_लिखो(name_string, 128, "NAME=%s", module->desc.name);
	snम_लिखो(vid_string, 64, "VID=%d", module->desc.vid);
	snम_लिखो(pid_string, 64, "PID=%d", module->desc.pid);
	snम_लिखो(पूर्णांकf_id_string, 64, "INTF_ID=%d", module->desc.पूर्णांकf_id);
	snम_लिखो(ip_devices_string, 64, "I/P DEVICES=0x%X",
		 module->desc.ip_devices);
	snम_लिखो(op_devices_string, 64, "O/P DEVICES=0x%X",
		 module->desc.op_devices);

	kobject_uevent_env(&module->kobj, KOBJ_ADD, envp);
पूर्ण

पूर्णांक gb_audio_manager_module_create(
	काष्ठा gb_audio_manager_module **module,
	काष्ठा kset *manager_kset,
	पूर्णांक id, काष्ठा gb_audio_manager_module_descriptor *desc)
अणु
	पूर्णांक err;
	काष्ठा gb_audio_manager_module *m;

	m = kzalloc(माप(*m), GFP_ATOMIC);
	अगर (!m)
		वापस -ENOMEM;

	/* Initialize the node */
	INIT_LIST_HEAD(&m->list);

	/* Set the module id */
	m->id = id;

	/* Copy the provided descriptor */
	स_नकल(&m->desc, desc, माप(*desc));

	/* set the kset */
	m->kobj.kset = manager_kset;

	/*
	 * Initialize and add the kobject to the kernel.  All the शेष files
	 * will be created here.  As we have alपढ़ोy specअगरied a kset क्रम this
	 * kobject, we करोn't have to set a parent क्रम the kobject, the kobject
	 * will be placed beneath that kset स्वतःmatically.
	 */
	err = kobject_init_and_add(&m->kobj, &gb_audio_module_type, शून्य, "%d",
				   id);
	अगर (err) अणु
		pr_err("failed initializing kobject for audio module #%d\n", id);
		kobject_put(&m->kobj);
		वापस err;
	पूर्ण

	/*
	 * Notअगरy the object was created
	 */
	send_add_uevent(m);

	*module = m;
	pr_info("Created audio module #%d\n", id);
	वापस 0;
पूर्ण

व्योम gb_audio_manager_module_dump(काष्ठा gb_audio_manager_module *module)
अणु
	pr_info("audio module #%d name=%s vid=%d pid=%d intf_id=%d i/p devices=0x%X o/p devices=0x%X\n",
		module->id,
		module->desc.name,
		module->desc.vid,
		module->desc.pid,
		module->desc.पूर्णांकf_id,
		module->desc.ip_devices,
		module->desc.op_devices);
पूर्ण
