<शैली गुरु>
/*
 * file क्रम managing the edac_device subप्रणाली of devices क्रम EDAC
 *
 * (C) 2007 SoftwareBitMaker
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written Doug Thompson <norsk5@xmission.com>
 *
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/edac.h>

#समावेश "edac_device.h"
#समावेश "edac_module.h"

#घोषणा EDAC_DEVICE_SYMLINK	"device"

#घोषणा to_edacdev(k) container_of(k, काष्ठा edac_device_ctl_info, kobj)
#घोषणा to_edacdev_attr(a) container_of(a, काष्ठा edacdev_attribute, attr)


/*
 * Set of edac_device_ctl_info attribute store/show functions
 */

/* 'log_ue' */
अटल sमाप_प्रकार edac_device_ctl_log_ue_show(काष्ठा edac_device_ctl_info
					*ctl_info, अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", ctl_info->log_ue);
पूर्ण

अटल sमाप_प्रकार edac_device_ctl_log_ue_store(काष्ठा edac_device_ctl_info
					*ctl_info, स्थिर अक्षर *data,
					माप_प्रकार count)
अणु
	/* अगर parameter is zero, turn off flag, अगर non-zero turn on flag */
	ctl_info->log_ue = (simple_म_से_अदीर्घ(data, शून्य, 0) != 0);

	वापस count;
पूर्ण

/* 'log_ce' */
अटल sमाप_प्रकार edac_device_ctl_log_ce_show(काष्ठा edac_device_ctl_info
					*ctl_info, अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", ctl_info->log_ce);
पूर्ण

अटल sमाप_प्रकार edac_device_ctl_log_ce_store(काष्ठा edac_device_ctl_info
					*ctl_info, स्थिर अक्षर *data,
					माप_प्रकार count)
अणु
	/* अगर parameter is zero, turn off flag, अगर non-zero turn on flag */
	ctl_info->log_ce = (simple_म_से_अदीर्घ(data, शून्य, 0) != 0);

	वापस count;
पूर्ण

/* 'panic_on_ue' */
अटल sमाप_प्रकार edac_device_ctl_panic_on_ue_show(काष्ठा edac_device_ctl_info
						*ctl_info, अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", ctl_info->panic_on_ue);
पूर्ण

अटल sमाप_प्रकार edac_device_ctl_panic_on_ue_store(काष्ठा edac_device_ctl_info
						 *ctl_info, स्थिर अक्षर *data,
						 माप_प्रकार count)
अणु
	/* अगर parameter is zero, turn off flag, अगर non-zero turn on flag */
	ctl_info->panic_on_ue = (simple_म_से_अदीर्घ(data, शून्य, 0) != 0);

	वापस count;
पूर्ण

/* 'poll_msec' show and store functions*/
अटल sमाप_प्रकार edac_device_ctl_poll_msec_show(काष्ठा edac_device_ctl_info
					*ctl_info, अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", ctl_info->poll_msec);
पूर्ण

अटल sमाप_प्रकार edac_device_ctl_poll_msec_store(काष्ठा edac_device_ctl_info
					*ctl_info, स्थिर अक्षर *data,
					माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;

	/* get the value and enक्रमce that it is non-zero, must be at least
	 * one millisecond क्रम the delay period, between scans
	 * Then cancel last outstanding delay क्रम the work request
	 * and set a new one.
	 */
	value = simple_म_से_अदीर्घ(data, शून्य, 0);
	edac_device_reset_delay_period(ctl_info, value);

	वापस count;
पूर्ण

/* edac_device_ctl_info specअगरic attribute काष्ठाure */
काष्ठा ctl_info_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार(*show) (काष्ठा edac_device_ctl_info *, अक्षर *);
	sमाप_प्रकार(*store) (काष्ठा edac_device_ctl_info *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा to_ctl_info(k) container_of(k, काष्ठा edac_device_ctl_info, kobj)
#घोषणा to_ctl_info_attr(a) container_of(a,काष्ठा ctl_info_attribute,attr)

/* Function to 'show' fields from the edac_dev 'ctl_info' काष्ठाure */
अटल sमाप_प्रकार edac_dev_ctl_info_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buffer)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = to_ctl_info(kobj);
	काष्ठा ctl_info_attribute *ctl_info_attr = to_ctl_info_attr(attr);

	अगर (ctl_info_attr->show)
		वापस ctl_info_attr->show(edac_dev, buffer);
	वापस -EIO;
पूर्ण

/* Function to 'store' fields into the edac_dev 'ctl_info' काष्ठाure */
अटल sमाप_प्रकार edac_dev_ctl_info_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = to_ctl_info(kobj);
	काष्ठा ctl_info_attribute *ctl_info_attr = to_ctl_info_attr(attr);

	अगर (ctl_info_attr->store)
		वापस ctl_info_attr->store(edac_dev, buffer, count);
	वापस -EIO;
पूर्ण

/* edac_dev file operations क्रम an 'ctl_info' */
अटल स्थिर काष्ठा sysfs_ops device_ctl_info_ops = अणु
	.show = edac_dev_ctl_info_show,
	.store = edac_dev_ctl_info_store
पूर्ण;

#घोषणा CTL_INFO_ATTR(_name,_mode,_show,_store)        \
अटल काष्ठा ctl_info_attribute attr_ctl_info_##_name = अणु      \
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,   \
	.show   = _show,                                        \
	.store  = _store,                                       \
पूर्ण;

/* Declare the various ctl_info attributes here and their respective ops */
CTL_INFO_ATTR(log_ue, S_IRUGO | S_IWUSR,
	edac_device_ctl_log_ue_show, edac_device_ctl_log_ue_store);
CTL_INFO_ATTR(log_ce, S_IRUGO | S_IWUSR,
	edac_device_ctl_log_ce_show, edac_device_ctl_log_ce_store);
CTL_INFO_ATTR(panic_on_ue, S_IRUGO | S_IWUSR,
	edac_device_ctl_panic_on_ue_show,
	edac_device_ctl_panic_on_ue_store);
CTL_INFO_ATTR(poll_msec, S_IRUGO | S_IWUSR,
	edac_device_ctl_poll_msec_show, edac_device_ctl_poll_msec_store);

/* Base Attributes of the EDAC_DEVICE ECC object */
अटल काष्ठा ctl_info_attribute *device_ctrl_attr[] = अणु
	&attr_ctl_info_panic_on_ue,
	&attr_ctl_info_log_ue,
	&attr_ctl_info_log_ce,
	&attr_ctl_info_poll_msec,
	शून्य,
पूर्ण;

/*
 * edac_device_ctrl_master_release
 *
 *	called when the reference count क्रम the 'main' kobj
 *	क्रम a edac_device control काष्ठा reaches zero
 *
 *	Reference count model:
 *		One 'main' kobject क्रम each control काष्ठाure allocated.
 *		That मुख्य kobj is initially set to one AND
 *		the reference count क्रम the EDAC 'core' module is
 *		bumped by one, thus added 'keep in memory' dependency.
 *
 *		Each new पूर्णांकernal kobj (in instances and blocks) then
 *		bumps the 'main' kobject.
 *
 *		When they are released their release functions decrement
 *		the 'main' kobj.
 *
 *		When the मुख्य kobj reaches zero (0) then THIS function
 *		is called which then decrements the EDAC 'core' module.
 *		When the module reference count reaches zero then the
 *		module no दीर्घer has dependency on keeping the release
 *		function code in memory and module can be unloaded.
 *
 *		This will support several control objects as well, each
 *		with its own 'main' kobj.
 */
अटल व्योम edac_device_ctrl_master_release(काष्ठा kobject *kobj)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = to_edacdev(kobj);

	edac_dbg(4, "control index=%d\n", edac_dev->dev_idx);

	/* decrement the EDAC CORE module ref count */
	module_put(edac_dev->owner);

	/* मुक्त the control काष्ठा containing the 'main' kobj
	 * passed in to this routine
	 */
	kमुक्त(edac_dev);
पूर्ण

/* ktype क्रम the मुख्य (master) kobject */
अटल काष्ठा kobj_type ktype_device_ctrl = अणु
	.release = edac_device_ctrl_master_release,
	.sysfs_ops = &device_ctl_info_ops,
	.शेष_attrs = (काष्ठा attribute **)device_ctrl_attr,
पूर्ण;

/*
 * edac_device_रेजिस्टर_sysfs_मुख्य_kobj
 *
 *	perक्रमm the high level setup क्रम the new edac_device instance
 *
 * Return:  0 SUCCESS
 *         !0 FAILURE
 */
पूर्णांक edac_device_रेजिस्टर_sysfs_मुख्य_kobj(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा bus_type *edac_subsys;
	पूर्णांक err;

	edac_dbg(1, "\n");

	/* get the /sys/devices/प्रणाली/edac reference */
	edac_subsys = edac_get_sysfs_subsys();

	/* Poपूर्णांक to the 'edac_subsys' this instance 'reports' to */
	edac_dev->edac_subsys = edac_subsys;

	/* Init the devices's kobject */
	स_रखो(&edac_dev->kobj, 0, माप(काष्ठा kobject));

	/* Record which module 'owns' this control काष्ठाure
	 * and bump the ref count of the module
	 */
	edac_dev->owner = THIS_MODULE;

	अगर (!try_module_get(edac_dev->owner)) अणु
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* रेजिस्टर */
	err = kobject_init_and_add(&edac_dev->kobj, &ktype_device_ctrl,
				   &edac_subsys->dev_root->kobj,
				   "%s", edac_dev->name);
	अगर (err) अणु
		edac_dbg(1, "Failed to register '.../edac/%s'\n",
			 edac_dev->name);
		जाओ err_kobj_reg;
	पूर्ण
	kobject_uevent(&edac_dev->kobj, KOBJ_ADD);

	/* At this poपूर्णांक, to 'free' the control काष्ठा,
	 * edac_device_unरेजिस्टर_sysfs_मुख्य_kobj() must be used
	 */

	edac_dbg(4, "Registered '.../edac/%s' kobject\n", edac_dev->name);

	वापस 0;

	/* Error निकास stack */
err_kobj_reg:
	kobject_put(&edac_dev->kobj);
	module_put(edac_dev->owner);

err_out:
	वापस err;
पूर्ण

/*
 * edac_device_unरेजिस्टर_sysfs_मुख्य_kobj:
 *	the '..../edac/<name>' kobject
 */
व्योम edac_device_unरेजिस्टर_sysfs_मुख्य_kobj(काष्ठा edac_device_ctl_info *dev)
अणु
	edac_dbg(0, "\n");
	edac_dbg(4, "name of kobject is: %s\n", kobject_name(&dev->kobj));

	/*
	 * Unरेजिस्टर the edac device's kobject and
	 * allow क्रम reference count to reach 0 at which poपूर्णांक
	 * the callback will be called to:
	 *   a) module_put() this module
	 *   b) 'kfree' the memory
	 */
	kobject_put(&dev->kobj);
पूर्ण

/* edac_dev -> instance inक्रमmation */

/*
 * Set of low-level instance attribute show functions
 */
अटल sमाप_प्रकार instance_ue_count_show(काष्ठा edac_device_instance *instance,
				अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", instance->counters.ue_count);
पूर्ण

अटल sमाप_प्रकार instance_ce_count_show(काष्ठा edac_device_instance *instance,
				अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", instance->counters.ce_count);
पूर्ण

#घोषणा to_instance(k) container_of(k, काष्ठा edac_device_instance, kobj)
#घोषणा to_instance_attr(a) container_of(a,काष्ठा instance_attribute,attr)

/* DEVICE instance kobject release() function */
अटल व्योम edac_device_ctrl_instance_release(काष्ठा kobject *kobj)
अणु
	काष्ठा edac_device_instance *instance;

	edac_dbg(1, "\n");

	/* map from this kobj to the मुख्य control काष्ठा
	 * and then dec the मुख्य kobj count
	 */
	instance = to_instance(kobj);
	kobject_put(&instance->ctl->kobj);
पूर्ण

/* instance specअगरic attribute काष्ठाure */
काष्ठा instance_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार(*show) (काष्ठा edac_device_instance *, अक्षर *);
	sमाप_प्रकार(*store) (काष्ठा edac_device_instance *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/* Function to 'show' fields from the edac_dev 'instance' काष्ठाure */
अटल sमाप_प्रकार edac_dev_instance_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buffer)
अणु
	काष्ठा edac_device_instance *instance = to_instance(kobj);
	काष्ठा instance_attribute *instance_attr = to_instance_attr(attr);

	अगर (instance_attr->show)
		वापस instance_attr->show(instance, buffer);
	वापस -EIO;
पूर्ण

/* Function to 'store' fields into the edac_dev 'instance' काष्ठाure */
अटल sमाप_प्रकार edac_dev_instance_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा edac_device_instance *instance = to_instance(kobj);
	काष्ठा instance_attribute *instance_attr = to_instance_attr(attr);

	अगर (instance_attr->store)
		वापस instance_attr->store(instance, buffer, count);
	वापस -EIO;
पूर्ण

/* edac_dev file operations क्रम an 'instance' */
अटल स्थिर काष्ठा sysfs_ops device_instance_ops = अणु
	.show = edac_dev_instance_show,
	.store = edac_dev_instance_store
पूर्ण;

#घोषणा INSTANCE_ATTR(_name,_mode,_show,_store)        \
अटल काष्ठा instance_attribute attr_instance_##_name = अणु      \
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,   \
	.show   = _show,                                        \
	.store  = _store,                                       \
पूर्ण;

/*
 * Define attributes visible क्रम the edac_device instance object
 *	Each contains a poपूर्णांकer to a show and an optional set
 *	function poपूर्णांकer that करोes the low level output/input
 */
INSTANCE_ATTR(ce_count, S_IRUGO, instance_ce_count_show, शून्य);
INSTANCE_ATTR(ue_count, S_IRUGO, instance_ue_count_show, शून्य);

/* list of edac_dev 'instance' attributes */
अटल काष्ठा instance_attribute *device_instance_attr[] = अणु
	&attr_instance_ce_count,
	&attr_instance_ue_count,
	शून्य,
पूर्ण;

/* The 'ktype' for each edac_dev 'instance' */
अटल काष्ठा kobj_type ktype_instance_ctrl = अणु
	.release = edac_device_ctrl_instance_release,
	.sysfs_ops = &device_instance_ops,
	.शेष_attrs = (काष्ठा attribute **)device_instance_attr,
पूर्ण;

/* edac_dev -> instance -> block inक्रमmation */

#घोषणा to_block(k) container_of(k, काष्ठा edac_device_block, kobj)
#घोषणा to_block_attr(a) \
	container_of(a, काष्ठा edac_dev_sysfs_block_attribute, attr)

/*
 * Set of low-level block attribute show functions
 */
अटल sमाप_प्रकार block_ue_count_show(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *data)
अणु
	काष्ठा edac_device_block *block = to_block(kobj);

	वापस प्र_लिखो(data, "%u\n", block->counters.ue_count);
पूर्ण

अटल sमाप_प्रकार block_ce_count_show(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *data)
अणु
	काष्ठा edac_device_block *block = to_block(kobj);

	वापस प्र_लिखो(data, "%u\n", block->counters.ce_count);
पूर्ण

/* DEVICE block kobject release() function */
अटल व्योम edac_device_ctrl_block_release(काष्ठा kobject *kobj)
अणु
	काष्ठा edac_device_block *block;

	edac_dbg(1, "\n");

	/* get the container of the kobj */
	block = to_block(kobj);

	/* map from 'block kobj' to 'block->instance->controller->main_kobj'
	 * now 'release' the block kobject
	 */
	kobject_put(&block->instance->ctl->kobj);
पूर्ण


/* Function to 'show' fields from the edac_dev 'block' काष्ठाure */
अटल sमाप_प्रकार edac_dev_block_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buffer)
अणु
	काष्ठा edac_dev_sysfs_block_attribute *block_attr =
						to_block_attr(attr);

	अगर (block_attr->show)
		वापस block_attr->show(kobj, attr, buffer);
	वापस -EIO;
पूर्ण

/* Function to 'store' fields into the edac_dev 'block' काष्ठाure */
अटल sमाप_प्रकार edac_dev_block_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा edac_dev_sysfs_block_attribute *block_attr;

	block_attr = to_block_attr(attr);

	अगर (block_attr->store)
		वापस block_attr->store(kobj, attr, buffer, count);
	वापस -EIO;
पूर्ण

/* edac_dev file operations क्रम a 'block' */
अटल स्थिर काष्ठा sysfs_ops device_block_ops = अणु
	.show = edac_dev_block_show,
	.store = edac_dev_block_store
पूर्ण;

#घोषणा BLOCK_ATTR(_name,_mode,_show,_store)        \
अटल काष्ठा edac_dev_sysfs_block_attribute attr_block_##_name = अणु	\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,   \
	.show   = _show,                                        \
	.store  = _store,                                       \
पूर्ण;

BLOCK_ATTR(ce_count, S_IRUGO, block_ce_count_show, शून्य);
BLOCK_ATTR(ue_count, S_IRUGO, block_ue_count_show, शून्य);

/* list of edac_dev 'block' attributes */
अटल काष्ठा edac_dev_sysfs_block_attribute *device_block_attr[] = अणु
	&attr_block_ce_count,
	&attr_block_ue_count,
	शून्य,
पूर्ण;

/* The 'ktype' for each edac_dev 'block' */
अटल काष्ठा kobj_type ktype_block_ctrl = अणु
	.release = edac_device_ctrl_block_release,
	.sysfs_ops = &device_block_ops,
	.शेष_attrs = (काष्ठा attribute **)device_block_attr,
पूर्ण;

/* block ctor/dtor  code */

/*
 * edac_device_create_block
 */
अटल पूर्णांक edac_device_create_block(काष्ठा edac_device_ctl_info *edac_dev,
				काष्ठा edac_device_instance *instance,
				काष्ठा edac_device_block *block)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा edac_dev_sysfs_block_attribute *sysfs_attrib;
	काष्ठा kobject *मुख्य_kobj;

	edac_dbg(4, "Instance '%s' inst_p=%p  block '%s'  block_p=%p\n",
		 instance->name, instance, block->name, block);
	edac_dbg(4, "block kobj=%p  block kobj->parent=%p\n",
		 &block->kobj, &block->kobj.parent);

	/* init this block's kobject */
	स_रखो(&block->kobj, 0, माप(काष्ठा kobject));

	/* bump the मुख्य kobject's reference count क्रम this controller
	 * and this instance is dependent on the मुख्य
	 */
	मुख्य_kobj = kobject_get(&edac_dev->kobj);
	अगर (!मुख्य_kobj) अणु
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* Add this block's kobject */
	err = kobject_init_and_add(&block->kobj, &ktype_block_ctrl,
				   &instance->kobj,
				   "%s", block->name);
	अगर (err) अणु
		edac_dbg(1, "Failed to register instance '%s'\n", block->name);
		kobject_put(मुख्य_kobj);
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* If there are driver level block attributes, then added them
	 * to the block kobject
	 */
	sysfs_attrib = block->block_attributes;
	अगर (sysfs_attrib && block->nr_attribs) अणु
		क्रम (i = 0; i < block->nr_attribs; i++, sysfs_attrib++) अणु

			edac_dbg(4, "creating block attrib='%s' attrib->%p to kobj=%p\n",
				 sysfs_attrib->attr.name,
				 sysfs_attrib, &block->kobj);

			/* Create each block_attribute file */
			err = sysfs_create_file(&block->kobj,
				&sysfs_attrib->attr);
			अगर (err)
				जाओ err_on_attrib;
		पूर्ण
	पूर्ण
	kobject_uevent(&block->kobj, KOBJ_ADD);

	वापस 0;

	/* Error unwind stack */
err_on_attrib:
	kobject_put(&block->kobj);

err_out:
	वापस err;
पूर्ण

/*
 * edac_device_delete_block(edac_dev,block);
 */
अटल व्योम edac_device_delete_block(काष्ठा edac_device_ctl_info *edac_dev,
				काष्ठा edac_device_block *block)
अणु
	काष्ठा edac_dev_sysfs_block_attribute *sysfs_attrib;
	पूर्णांक i;

	/* अगर this block has 'attributes' then we need to iterate over the list
	 * and 'remove' the attributes on this block
	 */
	sysfs_attrib = block->block_attributes;
	अगर (sysfs_attrib && block->nr_attribs) अणु
		क्रम (i = 0; i < block->nr_attribs; i++, sysfs_attrib++) अणु

			/* हटाओ each block_attrib file */
			sysfs_हटाओ_file(&block->kobj,
				(काष्ठा attribute *) sysfs_attrib);
		पूर्ण
	पूर्ण

	/* unरेजिस्टर this block's kobject, SEE:
	 *	edac_device_ctrl_block_release() callback operation
	 */
	kobject_put(&block->kobj);
पूर्ण

/* instance ctor/dtor code */

/*
 * edac_device_create_instance
 *	create just one instance of an edac_device 'instance'
 */
अटल पूर्णांक edac_device_create_instance(काष्ठा edac_device_ctl_info *edac_dev,
				पूर्णांक idx)
अणु
	पूर्णांक i, j;
	पूर्णांक err;
	काष्ठा edac_device_instance *instance;
	काष्ठा kobject *मुख्य_kobj;

	instance = &edac_dev->instances[idx];

	/* Init the instance's kobject */
	स_रखो(&instance->kobj, 0, माप(काष्ठा kobject));

	instance->ctl = edac_dev;

	/* bump the मुख्य kobject's reference count क्रम this controller
	 * and this instance is dependent on the मुख्य
	 */
	मुख्य_kobj = kobject_get(&edac_dev->kobj);
	अगर (!मुख्य_kobj) अणु
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* Formally रेजिस्टर this instance's kobject under the edac_device */
	err = kobject_init_and_add(&instance->kobj, &ktype_instance_ctrl,
				   &edac_dev->kobj, "%s", instance->name);
	अगर (err != 0) अणु
		edac_dbg(2, "Failed to register instance '%s'\n",
			 instance->name);
		kobject_put(मुख्य_kobj);
		जाओ err_out;
	पूर्ण

	edac_dbg(4, "now register '%d' blocks for instance %d\n",
		 instance->nr_blocks, idx);

	/* रेजिस्टर all blocks of this instance */
	क्रम (i = 0; i < instance->nr_blocks; i++) अणु
		err = edac_device_create_block(edac_dev, instance,
						&instance->blocks[i]);
		अगर (err) अणु
			/* If any fail, हटाओ all previous ones */
			क्रम (j = 0; j < i; j++)
				edac_device_delete_block(edac_dev,
							&instance->blocks[j]);
			जाओ err_release_instance_kobj;
		पूर्ण
	पूर्ण
	kobject_uevent(&instance->kobj, KOBJ_ADD);

	edac_dbg(4, "Registered instance %d '%s' kobject\n",
		 idx, instance->name);

	वापस 0;

	/* error unwind stack */
err_release_instance_kobj:
	kobject_put(&instance->kobj);

err_out:
	वापस err;
पूर्ण

/*
 * edac_device_हटाओ_instance
 *	हटाओ an edac_device instance
 */
अटल व्योम edac_device_delete_instance(काष्ठा edac_device_ctl_info *edac_dev,
					पूर्णांक idx)
अणु
	काष्ठा edac_device_instance *instance;
	पूर्णांक i;

	instance = &edac_dev->instances[idx];

	/* unरेजिस्टर all blocks in this instance */
	क्रम (i = 0; i < instance->nr_blocks; i++)
		edac_device_delete_block(edac_dev, &instance->blocks[i]);

	/* unरेजिस्टर this instance's kobject, SEE:
	 *	edac_device_ctrl_instance_release() क्रम callback operation
	 */
	kobject_put(&instance->kobj);
पूर्ण

/*
 * edac_device_create_instances
 *	create the first level of 'instances' क्रम this device
 *	(ie  'cache' might have 'cache0', 'cache1', 'cache2', etc
 */
अटल पूर्णांक edac_device_create_instances(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	पूर्णांक i, j;
	पूर्णांक err;

	edac_dbg(0, "\n");

	/* iterate over creation of the instances */
	क्रम (i = 0; i < edac_dev->nr_instances; i++) अणु
		err = edac_device_create_instance(edac_dev, i);
		अगर (err) अणु
			/* unwind previous instances on error */
			क्रम (j = 0; j < i; j++)
				edac_device_delete_instance(edac_dev, j);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * edac_device_delete_instances(edac_dev);
 *	unरेजिस्टर all the kobjects of the instances
 */
अटल व्योम edac_device_delete_instances(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	पूर्णांक i;

	/* iterate over creation of the instances */
	क्रम (i = 0; i < edac_dev->nr_instances; i++)
		edac_device_delete_instance(edac_dev, i);
पूर्ण

/* edac_dev sysfs ctor/dtor  code */

/*
 * edac_device_add_मुख्य_sysfs_attributes
 *	add some attributes to this instance's मुख्य kobject
 */
अटल पूर्णांक edac_device_add_मुख्य_sysfs_attributes(
			काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा edac_dev_sysfs_attribute *sysfs_attrib;
	पूर्णांक err = 0;

	sysfs_attrib = edac_dev->sysfs_attributes;
	अगर (sysfs_attrib) अणु
		/* iterate over the array and create an attribute क्रम each
		 * entry in the list
		 */
		जबतक (sysfs_attrib->attr.name != शून्य) अणु
			err = sysfs_create_file(&edac_dev->kobj,
				(काष्ठा attribute*) sysfs_attrib);
			अगर (err)
				जाओ err_out;

			sysfs_attrib++;
		पूर्ण
	पूर्ण

err_out:
	वापस err;
पूर्ण

/*
 * edac_device_हटाओ_मुख्य_sysfs_attributes
 *	हटाओ any attributes to this instance's मुख्य kobject
 */
अटल व्योम edac_device_हटाओ_मुख्य_sysfs_attributes(
			काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा edac_dev_sysfs_attribute *sysfs_attrib;

	/* अगर there are मुख्य attributes, defined, हटाओ them. First,
	 * poपूर्णांक to the start of the array and iterate over it
	 * removing each attribute listed from this device's instance's kobject
	 */
	sysfs_attrib = edac_dev->sysfs_attributes;
	अगर (sysfs_attrib) अणु
		जबतक (sysfs_attrib->attr.name != शून्य) अणु
			sysfs_हटाओ_file(&edac_dev->kobj,
					(काष्ठा attribute *) sysfs_attrib);
			sysfs_attrib++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * edac_device_create_sysfs() Conकाष्ठाor
 *
 * accept a created edac_device control काष्ठाure
 * and 'export' it to sysfs. The 'main' kobj should alपढ़ोy have been
 * created. 'instance' and 'block' kobjects should be रेजिस्टरed
 * aदीर्घ with any 'block' attributes from the low driver. In addition,
 * the मुख्य attributes (अगर any) are connected to the मुख्य kobject of
 * the control काष्ठाure.
 *
 * Return:
 *	0	Success
 *	!0	Failure
 */
पूर्णांक edac_device_create_sysfs(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	पूर्णांक err;
	काष्ठा kobject *edac_kobj = &edac_dev->kobj;

	edac_dbg(0, "idx=%d\n", edac_dev->dev_idx);

	/*  go create any मुख्य attributes callers wants */
	err = edac_device_add_मुख्य_sysfs_attributes(edac_dev);
	अगर (err) अणु
		edac_dbg(0, "failed to add sysfs attribs\n");
		जाओ err_out;
	पूर्ण

	/* create a symlink from the edac device
	 * to the platक्रमm 'device' being used क्रम this
	 */
	err = sysfs_create_link(edac_kobj,
				&edac_dev->dev->kobj, EDAC_DEVICE_SYMLINK);
	अगर (err) अणु
		edac_dbg(0, "sysfs_create_link() returned err= %d\n", err);
		जाओ err_हटाओ_मुख्य_attribs;
	पूर्ण

	/* Create the first level instance directories
	 * In turn, the nested blocks beneath the instances will
	 * be रेजिस्टरed as well
	 */
	err = edac_device_create_instances(edac_dev);
	अगर (err) अणु
		edac_dbg(0, "edac_device_create_instances() returned err= %d\n",
			 err);
		जाओ err_हटाओ_link;
	पूर्ण


	edac_dbg(4, "create-instances done, idx=%d\n", edac_dev->dev_idx);

	वापस 0;

	/* Error unwind stack */
err_हटाओ_link:
	/* हटाओ the sym link */
	sysfs_हटाओ_link(&edac_dev->kobj, EDAC_DEVICE_SYMLINK);

err_हटाओ_मुख्य_attribs:
	edac_device_हटाओ_मुख्य_sysfs_attributes(edac_dev);

err_out:
	वापस err;
पूर्ण

/*
 * edac_device_हटाओ_sysfs() deकाष्ठाor
 *
 * given an edac_device काष्ठा, tear करोwn the kobject resources
 */
व्योम edac_device_हटाओ_sysfs(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	edac_dbg(0, "\n");

	/* हटाओ any मुख्य attributes क्रम this device */
	edac_device_हटाओ_मुख्य_sysfs_attributes(edac_dev);

	/* हटाओ the device sym link */
	sysfs_हटाओ_link(&edac_dev->kobj, EDAC_DEVICE_SYMLINK);

	/* walk the instance/block kobject tree, deस्थिरructing it */
	edac_device_delete_instances(edac_dev);
पूर्ण
